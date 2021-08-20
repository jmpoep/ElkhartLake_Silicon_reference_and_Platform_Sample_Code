/** @file
  Profile manager implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "interface.h"
#include "device_struct.h"
#include "device_mgr.h"
#include "gatt.h"
#include "att.h"
#include "gap.h"
#include "smp_mgr.h"
#include "smp.h"
#include "profile_mgr.h"
#include "service_mgr.h"
#include "hci_host.h"

#define MODULE_DBG_LVL PROFILE_MGR_DBG_LVL
#include "log.h"

#define CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC	0x2AA6

/**************************************************************
 *				Static Functions
 *************************************************************/

#if (GATT_CLIENT_SUPPORTED == TRUE)

static INT8 pm_set_att_mtu_size(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size);
static INT8 pm_discover_primary_service(trans_id_t trans_id, UINT8 conn_id, uuid_t *filter_uuid);
static INT8 pm_discover_included_service(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);
static INT8 pm_discover_characteristic(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid);
static INT8 pm_discover_descriptor(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);

static INT8 pm_read_attribute_value(trans_id_t trans_id, UINT8 UINT8, gatt_attribute_read_param_t *read_param);
static INT8 pm_write_attribute_value(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t *buffer);

static INT8 pm_enqueue_req_in_pending_queue(UINT8 conn_id, interface_req_elem_t *incoming_req);
static void pm_dequeue_and_cleanup_from_pending_queue(UINT8 conn_id);
#endif /* #if (GATT_CLIENT_SUPPORTED == TRUE) */

#if 0
static void display_transac_list()
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUMBER_OF_PM_REQ; idx++)
	{
		if (g_local_adapter.pm_transac_list[idx] != NULL )
		{
			logd("app_handle:%d connected_device_idx:%d pm_operation:%d"
					, g_local_adapter.pm_transac_list[idx]->app_handle, g_local_adapter.pm_transac_list[idx]->connected_device_idx,
					g_local_adapter.pm_transac_list[idx]->pm_operation);
		}
	}
}
#endif

#if (GATT_CLIENT_SUPPORTED == TRUE || GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static UINT8 pm_find_first_free_transac_slot()
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUMBER_OF_PM_REQ; idx++)
	{
		if (g_local_adapter.pm_transac_list[idx] == NULL)
			return idx;
	}
	return MAX_NUMBER_OF_PM_REQ;
}

static UINT8 pm_find_transac_id(UINT8 pm_operation, UINT8 connected_device_idx)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUMBER_OF_PM_REQ; idx++)
	{
		if (g_local_adapter.pm_transac_list[idx] != NULL)
		{

			if (pm_operation == API_REQ_OPCODE_CONNECT && g_local_adapter.pm_transac_list[idx]->pm_operation
					== pm_operation)
				return idx;

			if ((pm_operation == (UINT8)INVALID_INDEX || g_local_adapter.pm_transac_list[idx]->pm_operation == pm_operation)
					&&
				g_local_adapter.pm_transac_list[idx]->connected_device_idx == connected_device_idx)
				return idx;
		}
	}
	return MAX_NUMBER_OF_PM_REQ;
}

static trans_id_t get_transid_from_transac_id(UINT8 transac_id)
{
	if (transac_id >= MAX_NUMBER_OF_PM_REQ)
		return INVALID_TRANS_ID;
	return g_local_adapter.pm_transac_list[transac_id]->trans_id;
}

static INT8 pm_create_transac(trans_id_t trans_id, UINT8 pm_operation, UINT8 connected_device_idx, void* additional_param)
{
	UINT8 slot;
	pm_transactions_elem_t* transac = (pm_transactions_elem_t*) alloc(sizeof(pm_transactions_elem_t));

	if (transac == NULL )
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	transac->trans_id = trans_id;
	transac->pm_operation = pm_operation;
	transac->connected_device_idx = connected_device_idx;
	if(additional_param)
		transac->additional_param = additional_param;
	if (connected_device_idx < MAX_NUM_CONNECTED_DEVICE)
	{
		connected_device_t *device = g_local_adapter.connected_device[connected_device_idx];
		if (device)
			device->pm_device_data.pm_state = PM_STATE_PROCESSING;
	}

	slot = pm_find_first_free_transac_slot();
	if (slot == MAX_NUMBER_OF_PM_REQ)
	{
		dealloc(transac);
		loge("PM request queue full");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	g_local_adapter.pm_transac_list[slot] = transac;

	return STATUS_SUCCESS;
}

static void pm_finish_transac(UINT8 transac_id, UINT8 conn_id)
{
	pm_transactions_elem_t* transac;
	UINT8 pm_operation;
#if (PARANOID_STACK == TRUE)
	if (transac_id >= MAX_NUMBER_OF_PM_REQ)
		return;
#endif
	transac = g_local_adapter.pm_transac_list[transac_id];
	pm_operation = (UINT8)INVALID_INDEX;
	if (transac != NULL )
	{
		pm_operation = transac->pm_operation;
		if(transac->additional_param)
			dealloc(transac->additional_param);
		dealloc(transac);
	}
	g_local_adapter.pm_transac_list[transac_id] = NULL;

	/* See if anything to execute from the wait queue for each device */
#if (GATT_CLIENT_SUPPORTED == TRUE)
	if (pm_operation != API_REQ_OPCODE_CONNECT && pm_operation != API_REQ_OPCODE_DISCONNECT)
	{
		connected_device_t *device = get_connected_device_by_conn_id(conn_id);
		if (device)
		{
			pm_dequeue_and_cleanup_from_pending_queue(conn_id);
			device->pm_device_data.pm_state = PM_STATE_IDLE;
		}
		pm_req_handler(NULL);
	}
#else
	USE (pm_operation);
#endif /* #if (GATT_CLIENT_SUPPORTED == TRUE) */
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

#if (TEST_CODE == FALSE)
#if 0
static void pm_bonding_complete_cb (UINT8 *bdaddr, UINT8 status)
{
	logd("status:%d", status);
/*	 Resend the request that failed.
#if (PARANOID_STACK == TRUE)
	if (!bdaddr)
		return;
#endif
	connected_device_t *device = get_connected_device_by_bdaddr(bdaddr);
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif

	if (!device->pm_device_data.saved_req)
	{
		logd ("This req was not triggered from here.");
		return;
	}

	if (status != 0)
	{
		logd("Status failed :(");
		return;
	}
	else
	{
		switch (device->pm_device_data.saved_req_opcode)
		{
		case PM_REQ_OPCODE_READ_CHARACTERISTIC_VALUE:
		{
			pm_read_characteristic_value_param_t *param = (pm_read_characteristic_value_param_t*) device->pm_device_data.saved_req;
			read_characteristic_value(param->app_handle, param->remote_bd_addr, param->characteristic, param->is_long);
			dealloc (param->remote_bd_addr);
		}
			break;
		case PM_REQ_OPCODE_WRITE_CHARACTERISTIC_VALUE:
		{
			pm_write_characteristic_value_param_t *param = (pm_write_characteristic_value_param_t*) device->pm_device_data.saved_req;
			write_characteristic_value(param->app_handle, param->remote_bd_addr, param->characteristic, param->value, param->value_len, param->need_response, param->is_signed, param->is_reliable);
			dealloc(param->remote_bd_addr);
		}
			break;
		case PM_REQ_OPCODE_WRITE_CHARACTERISTIC_DESCRIPTOR:
		{
			pm_write_characteristic_descriptor_param_t *param = (pm_write_characteristic_descriptor_param_t*) device->pm_device_data.saved_req;
			write_characteristic_descriptor(param->app_handle, param->remote_bd_addr, param->descriptor, param->value, param->value_len);
			dealloc(param->remote_bd_addr);
		}
			break;
		case PM_REQ_OPCODE_ENABLE_NOTIFICATION:
		{
			pm_enable_notification_param_t *param = (pm_enable_notification_param_t*) device->pm_device_data.saved_req;
			enable_notification(param->app_handle, param->remote_bd_addr, param->characteristic, param->is_enable, param->need_response);
			dealloc(param->remote_bd_addr);
		}
			break;
		default:
			logd("Unknown opcode.");
		}
	}
	dealloc (device->pm_device_data.saved_req);
	device->pm_device_data.saved_req = NULL;
	device->pm_device_data.saved_req_opcode = PM_REQ_OPCODE_MAX;*/
}
#endif
#endif

#if 0
static INT8 check_error_status(UINT8 conn_id, UINT8 status)
{
	INT8 ret = STATUS_SUCCESS;
#if (TEST_CODE == TRUE)
	return ret;
#else
	if (status == ATT_ERR_INSUFF_AUTHENTICATION || status == ATT_ERR_INSUFF_ENCR ||
			status == ATT_ERR_INSUFF_ENCR_KEY_SIZE)
	{
		switch (smp_mgr_check_cur_link_status(device))
		{
		case SMP_MGR_SEC_ENC_MITM:
			break; /* Most unlikely. */
		case SMP_MGR_SEC_NONE:
		case SMP_MGR_SEC_ENC_NO_MITM:
		{
			interface_req_elem_t *req = create_req_for_create_bond(INVALID_TRANS_ID, device, 5, 7, pm_bonding_complete_cb);
			smpm_req_handler(req);
		}
			break;
		}
	}
	return ret;
#endif
}
#endif

static INT8 pm_enqueue_req_in_pending_queue(UINT8 conn_id, interface_req_elem_t *incoming_req)
{
	connected_device_t *device;
	logd("");
	if (!incoming_req)
		return STATUS_ERR_INVALID_PARAM;
	device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;
	return enqueue(&device->pm_device_data.pending_req_q, (void*)incoming_req);
}

static void pm_dequeue_and_cleanup_from_pending_queue(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	interface_req_elem_t* req;
	logd("");
	if (!device)
		return;
	req = (interface_req_elem_t*)dequeue(&device->pm_device_data.pending_req_q);
	if (req)
	{
		dealloc_queue_element(req);
	}
}

static UINT8 get_pm_state(UINT8 conn_id)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);
	if (device)
	{
		return device->pm_device_data.pm_state;
	}
	return PM_STATE_INVALID;
}

static interface_req_elem_t* get_req_to_process()
{
	connected_device_t *device = NULL;
	UINT8 idx = g_local_adapter.pm_device_idx_to_execute;
	interface_req_elem_t* front_req = NULL;
	UINT8 count = 0;

	if (idx < MAX_NUM_CONNECTED_DEVICE)
		device = g_local_adapter.connected_device[idx];
	if (device)
		front_req = (interface_req_elem_t*)pick_front(&device->pm_device_data.pending_req_q);

	if (!front_req)
	{
		/* No pending request found at specified index... look for one */
		for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
		{
			device = g_local_adapter.connected_device[idx];
			if (device)
			{
				front_req = (interface_req_elem_t*)pick_front(&device->pm_device_data.pending_req_q);
				if (front_req)
					break;
			}
		}
	}

	/* Set up the next device index to execute */
	for (; count < MAX_NUM_CONNECTED_DEVICE; count++)
	{
		idx = (idx + 1) % MAX_NUM_CONNECTED_DEVICE;
		device = g_local_adapter.connected_device[idx];
		if (device)
			break;
	}

	if (count != MAX_NUM_CONNECTED_DEVICE)
		g_local_adapter.pm_device_idx_to_execute = idx;

	return front_req;
}
#endif

BOOLEAN is_conn_used(app_data_t *app_data, connected_device_t *device)
{
	UINT8 idx;
	if(app_data->num_conn_used < MAX_NUM_CONNECTED_DEVICE)
	{
		for (idx = 0; idx < app_data->num_conn_used; idx++)
		{
			if (app_data->conn_used[idx] == device->idx)
				return TRUE;
		}
	}
	return FALSE;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void add_conn_used(app_data_t *app_data, connected_device_t *device)
{
	if (!is_conn_used(app_data, device))
	{
		if (app_data->num_conn_used == MAX_NUM_CONNECTED_DEVICE)
		{
			loge("Connection used exceeds maximum. Something is messed up with PM transactions!!");
			return;
		}
		app_data->conn_used[app_data->num_conn_used++] = device->idx;
	}
}

static void remove_conn_used(app_data_t *app_data, connected_device_t *device)
{
	UINT8 idx;


	if (app_data->num_conn_used > MAX_NUM_CONNECTED_DEVICE)
		return;

	for (idx = 0; idx < app_data->num_conn_used; idx++)
	{
		if (app_data->conn_used[idx] == device->idx)
			break;
	}
	if (idx == app_data->num_conn_used)
		return;
	for (; idx < app_data->num_conn_used-1; idx++)
		app_data->conn_used[idx] = app_data->conn_used[idx+1];
	app_data->num_conn_used--;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

/**************************************************************
 *				Profile Manager APIs
 *************************************************************/
INT8 pm_init()
{
	/* When we start to execute, we execute from the first device. */
	g_local_adapter.pm_device_idx_to_execute = 0;
#if ((GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE))
	return gatt_init();
#else
	return STATUS_SUCCESS;
#endif
}

void pm_cleanup()
{
	UINT8 idx;
	g_local_adapter.pm_device_idx_to_execute = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		dealloc(g_local_adapter.gap_data.autoconn_dev[idx]);
		g_local_adapter.gap_data.autoconn_dev[idx] = NULL;
	}
#if ((GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE))
	gatt_cleanup();
#endif
}

INT8 pm_req_handler(interface_req_elem_t* incoming_req)
{
#if (GATT_CLIENT_SUPPORTED == TRUE)
	INT8 req_status = STATUS_ERR_UNKNOWN;
	interface_req_elem_t* req ;
	app_data_t* app_data = NULL;
	/* enqueue this request */

	if (incoming_req)
		pm_enqueue_req_in_pending_queue(incoming_req->conn_id, incoming_req);

	req = get_req_to_process();

	if (!req)
	{
		logd("No pending request in PM wait queue.");
		return STATUS_SUCCESS;
	}
	else
	{
		if (get_pm_state(req->conn_id) != PM_STATE_IDLE)
		{
			logd("pm state is not idle");
			return STATUS_PROCESS_ONGOING;
		}
	}

	switch (req->req_opcode)
	{
	case API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE:
	{
		pm_discover_primary_service_param_t* param = (pm_discover_primary_service_param_t*)(void*)req->parameter;
		req_status = pm_discover_primary_service(param->trans_id, param->conn_id, &param->filter_uuid);

		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");
			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_primary_service_discovered_cb)
				app_data->app_gatt_cb->iLE_on_primary_service_discovered_cb(param->trans_id, req_status, param->conn_id, 0, 0, NULL, TRUE);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE:
	{
		pm_discover_included_service_param_t* param = (pm_discover_included_service_param_t*)(void*)req->parameter;
		req_status = pm_discover_included_service(param->trans_id, param->conn_id, param->start_handle, param->end_handle);

		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_included_service_discovered_cb)
				app_data->app_gatt_cb->iLE_on_included_service_discovered_cb(param->trans_id, req_status, param->conn_id, 0, 0, 0, NULL, TRUE);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_DISCOVER_CHARACTERISTIC:
	{
		pm_discover_characteristic_param_t* param = (pm_discover_characteristic_param_t*)(void*)req->parameter;
		req_status = pm_discover_characteristic(param->trans_id, param->conn_id, param->start_handle, param->end_handle, &param->filter_uuid);

		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_characteristic_discovered_cb)
				app_data->app_gatt_cb->iLE_on_characteristic_discovered_cb(param->trans_id, req_status, param->conn_id, 0, 0, 0, NULL, TRUE);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_DISCOVER_DESCRIPTOR:
	{
		pm_discover_descriptor_param_t* param = (pm_discover_descriptor_param_t*)(void*)req->parameter;
		req_status = pm_discover_descriptor(param->trans_id, param->conn_id, param->start_handle, param->end_handle);

		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_descriptor_discovered_cb)
				app_data->app_gatt_cb->iLE_on_descriptor_discovered_cb(param->trans_id, req_status, param->conn_id, 0, NULL, TRUE);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_READ_ATTRIBUTE_VALUE:
	{
		pm_read_attribute_value_param_t* param = (pm_read_attribute_value_param_t*)(void*)req->parameter;
		req_status = pm_read_attribute_value(param->trans_id, param->conn_id, &param->read_param);
		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY)
		{
			 /* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			 if(app_handle < MAX_NUMBER_OF_APP)
				 app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_read_cb)
			{
				app_data->app_gatt_cb->iLE_on_attribute_read_cb(
						param->trans_id, param->conn_id, param->read_param.att_opcode, ATT_ERR_LOCAL_ERROR,
						param->read_param.attr_read_param.read_attr.att_id, NULL);
			}

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE:
	{
		pm_write_attribute_value_param_t* param = (pm_write_attribute_value_param_t*)(void*)req->parameter;
		req_status = pm_write_attribute_value(param->trans_id, param->conn_id, param->att_opcode, param->att_id, param->offset, &param->buffer);
		if (param->att_opcode == ATT_OPCODE_WRITE_CMD)
		{
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_write_cb)
				app_data->app_gatt_cb->iLE_on_attribute_write_cb(param->trans_id, param->conn_id, param->att_opcode, ATT_SUCCESS, param->att_id, param->offset, &param->buffer);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
			break;
		}
		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_write_cb)
				app_data->app_gatt_cb->iLE_on_attribute_write_cb(param->trans_id, param->conn_id, param->att_opcode, ATT_ERR_LOCAL_ERROR, param->att_id, 0, NULL);

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_SET_ATT_MTU_SIZE:
	{
		pm_set_att_mtu_param_t* param = (pm_set_att_mtu_param_t*)(void*)req->parameter;
		req_status = pm_set_att_mtu_size(param->trans_id, param->conn_id, param->mtu_size);
		if (req_status != STATUS_SUCCESS && req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
		{
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];
			else
				logw("Invalid app handle retrieved from transaction");

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_att_mtu_changed_cb)
				app_data->app_gatt_cb->iLE_on_att_mtu_changed_cb(param->trans_id, param->conn_id, get_device_mtu(param->conn_id));

			pm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	}
	return STATUS_PROCESS_ONGOING;
#else
	return STATUS_ERR_OPERATION_NOT_SUPPORTED;
#endif /* #if (GATT_CLIENT_SUPPORTED == TRUE) */
}

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)

UINT16 pm_get_att_mtu(UINT8 conn_id)
{
	return get_device_mtu(conn_id);
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE */

INT8 pm_register_application(device_control_callbacks_t* dev_cb,
		gatt_callbacks_t* gatt_cb,
		register_application_cb_t register_application_cb)
{
	UINT8 idx;
	app_data_t *app_data = (app_data_t*) alloc(sizeof(app_data_t));
	logi("");

	if (app_data != NULL )
	{
		app_data->app_gatt_cb = gatt_cb;
		for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
		{
			if (g_local_adapter.app_list[idx] == NULL )
			{
				app_data->idx = idx;
				g_local_adapter.app_list[idx] = app_data;
				app_data->num_conn_used = 0;
				dm_register(idx, dev_cb);
				register_application_cb(idx, TRUE);
				logd("App_handle : %d", idx);
				// Call stack_initialized_cb if adapter is already enabled
				if (g_local_adapter.adapter_state == ADAPTER_STATE_ENABLED)
				{
					if (g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb)
						if (g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb)
							g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb(TRUE);
				}
				return STATUS_SUCCESS;
			}
		}
	}
	register_application_cb((UINT8)INVALID_INDEX, FALSE);
	if (app_data)
		dealloc(app_data);
	return STATUS_ERR_INSUFFICIENT_RESOURCES;
}

INT8 pm_deregister_application(UINT8 app_index)
{
	if(app_index >= MAX_NUMBER_OF_APP)
	{
		logd("app_handle is not valid");
		return STATUS_ERR_INVALID_APP_HANDLE;
	}
	dm_unregister(app_index);
	if (g_local_adapter.app_list[app_index])
		dealloc(g_local_adapter.app_list[app_index]);

	g_local_adapter.app_list[app_index] = NULL;
	return STATUS_SUCCESS;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

INT8 pm_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout)
{
	INT8 ret = STATUS_ERR_UNKNOWN;

	ret = pm_create_transac(trans_id, API_REQ_OPCODE_CONNECT, (UINT8)INVALID_INDEX, NULL);
	logi("");
	if (ret)
		return ret;

	ret = gap_create_connection(remote_bd_addr, addr_type, scan_int, scan_win, conn_int_min, conn_int_max, conn_lat, sup_timeout);

	if (ret != STATUS_SUCCESS && ret != STATUS_OPERATION_FINISHED_LOCAL_SUCCESS)
	{
		logd("Transaction finished. ret:%d", ret);
		pm_finish_transac(pm_find_transac_id(API_REQ_OPCODE_CONNECT,
				get_connected_device_idx_by_bdaddr(remote_bd_addr)), get_connected_device_idx_by_bdaddr(remote_bd_addr));
	}
	return ret;
}

INT8 pm_auto_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, BOOLEAN enable)
{
	logi("");
	if(enable)
	{
		logd("Enabling auto connect");
		if ( (get_idx_from_autoconn_list(remote_bd_addr) == MAX_NUM_CONNECTED_DEVICE))
		{
			UINT8 bdaddr[BD_ADDR_LEN];
			UINT8 *rev_bdaddr = bdaddr;
			logd("Device not present in white list");
			REVERSE_ARRAY_TO_STREAM(rev_bdaddr, remote_bd_addr, BD_ADDR_LEN);
			gap_add_to_whitelist(addr_type, bdaddr);
		}
		add_to_autoconn_list(remote_bd_addr, addr_type, trans_id);
	}
	else
	{
		remove_from_autoconn_list(remote_bd_addr, trans_id);
	}

	return STATUS_SUCCESS;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

INT8 pm_disconnect(trans_id_t trans_id, UINT8 conn_id, UINT8 reason)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT8 idx;
	UINT8 app_handle = get_appid_from_transid(trans_id);
	connected_device_t *device;
	logi("");
	if (conn_id == MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INAVALID_CONNENCTION;

	device = g_local_adapter.connected_device[conn_id];
	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	/* Remove the device from auto connect list only if
	 * disconnection is triggered by the user.
	 */
	if (reason == GAP_DISCONNECT_REASON_TERM_CONNECTION_USER)
		remove_from_autoconn_list(device->bdaddr, trans_id);// To Do: any thing to do with trans_id?
#endif
	if(app_handle < MAX_NUMBER_OF_APP)
	{
		device->usage_map[app_handle] = FALSE;

		//If there are still applications using it, do not actually disconnect
		for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
		{
			if (device->usage_map[idx])
			{
				//Send disconnect callback to the calling application
				app_data_t *app_data = g_local_adapter.app_list[app_handle];
				if (app_data)
				{
					remove_conn_used(app_data, device);
					app_data->app_device_control_cb->iLE_on_disconnected_cb(trans_id, device->idx, GAP_DISCONNECT_REASON_TERM_CONNECTION_LOCAL); /* 0x00 for Success */
				}
				return STATUS_SUCCESS;
			}
		}
	}

	ret = pm_create_transac(trans_id, API_REQ_OPCODE_DISCONNECT, conn_id, NULL);
	if (ret)
		return ret;

	ret = gap_terminate_connection(conn_id, reason);

	if (ret != STATUS_SUCCESS && ret != STATUS_ERR_BUSY)
		pm_finish_transac(pm_find_transac_id(API_REQ_OPCODE_DISCONNECT, conn_id), conn_id);

	return ret;
}

INT8 pm_conn_param_update_req(trans_id_t trans_id, UINT8 conn_id, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");

	ret = pm_create_transac(trans_id, API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE, conn_id, NULL);
	if (ret)
		return ret;

	ret = gap_req_update_conn_params(conn_id, interval_min, interval_max, conn_latency, sup_timeout);

	if (ret != STATUS_SUCCESS && ret != STATUS_ERR_BUSY)
	{
		pm_conn_param_update_cb( ret, conn_id, 0, 0, 0);
	}

	return ret;

}

void pm_conn_param_update_cb(UINT8 status, UINT8 conn_id,
								UINT16 interval, UINT16 latency, UINT16 timeout)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE, conn_id);
	trans_id_t trans_id = INVALID_TRANS_ID;
	UINT8 app_handle;
	if (transac_id != MAX_NUMBER_OF_PM_REQ)
	{
		trans_id = get_transid_from_transac_id(transac_id);
		app_handle = get_appid_from_transid(trans_id);
		if(app_handle < MAX_NUMBER_OF_APP && g_local_adapter.app_list[app_handle] &&
				g_local_adapter.app_list[app_handle]->app_device_control_cb &&
				g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_on_conn_param_update_cb)
				g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_on_conn_param_update_cb(trans_id, status, conn_id, interval, latency, timeout);
		pm_finish_transac(transac_id, conn_id);
	}
	else
	{
		for( app_handle = 0; app_handle < MAX_NUMBER_OF_APP; app_handle++)
		{
			if(g_local_adapter.app_list[app_handle] &&
					g_local_adapter.app_list[app_handle]->app_device_control_cb &&
					g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_on_conn_param_update_cb)
					g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_on_conn_param_update_cb(trans_id, status, conn_id, interval, latency, timeout);
		}
	}
}

#if (CONTROLLER_PRIVACY)
static interface_req_elem_t* create_req_for_CAR_support(UINT8 conn_id)
{
	UINT16 car_uuid_val = CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC;
	pm_read_attribute_value_param_t* param;

	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_READ_ATTRIBUTE_VALUE, conn_id, sizeof(pm_read_attribute_value_param_t));
	if(req == NULL)
		return NULL;
	param = (pm_read_attribute_value_param_t*)req->parameter;

	param->trans_id = INVALID_TRANS_ID;
	param->conn_id = conn_id;
	param->read_param.att_opcode = ATT_OPCODE_READ_BY_TYPE_REQ;
	param->read_param.attr_read_param.read_using_uuid_param.start_handle = START_HANDLE;
	param->read_param.attr_read_param.read_using_uuid_param.end_handle = END_HANDLE;
	UINT16_TO_UUID(car_uuid_val, param->read_param.attr_read_param.read_using_uuid_param.uuid);

	return req;
}
#endif /* CONTROLLER_PRIVACY */

#if (TEST_CODE==TRUE && LE_PING_ENABLE == TRUE)

INT8 pm_read_authpayload_timeout(trans_id_t trans_id, UINT8 conn_id)
{
	INT8 ret = gap_read_authpayload_timeout(conn_id);
	logd("[LE_PING]For book-keeping the app req");
	if (ret != STATUS_SUCCESS && ret != STATUS_ERR_BUSY && ret != STATUS_OPERATION_FINISHED_LOCAL_SUCCESS)
	{
		logd("[LE_PING]Transaction finished. ret:%d", ret);
		UINT8 app_handle = get_appid_from_transid(trans_id);

		if(app_handle >= MAX_NUMBER_OF_APP)
		{
			logd("app_handle is not valid");
			return STATUS_ERR_INVALID_APP_HANDLE;
		}

		g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_read_authpayload_timeout_cb(trans_id, conn_id, 0);
	}
	pm_create_transac(trans_id, API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT, conn_id, NULL);
	return ret;
}
#endif //TEST_CODE && LE_PING_ENABLE

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

static INT8 pm_discover_primary_service(trans_id_t trans_id, UINT8 conn_id, uuid_t *filter_uuid)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");

	if ((ret = gatt_discover_primary_service(conn_id, filter_uuid)) == STATUS_SUCCESS)
		return pm_create_transac(trans_id, API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE, conn_id, NULL);

	return ret;
}

static INT8 pm_discover_included_service(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");

	if ((ret = gatt_discover_included_service(conn_id, start_handle, end_handle)) == STATUS_SUCCESS)
		return pm_create_transac(trans_id, API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE, conn_id, NULL);

	return STATUS_SUCCESS;
}

static INT8 pm_discover_characteristic(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");

	if ((ret = gatt_discover_characteristic(conn_id, start_handle, end_handle, filter_uuid)) == STATUS_SUCCESS)
		return pm_create_transac(trans_id, API_REQ_OPCODE_DISCOVER_CHARACTERISTIC, conn_id, NULL);

	return ret;
}

static INT8 pm_discover_descriptor(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("start_handle:%u end_handle:%u", start_handle, end_handle);

	if ((ret = gatt_discover_descriptor(conn_id, start_handle, end_handle)) == STATUS_SUCCESS)
		return pm_create_transac(trans_id, API_REQ_OPCODE_DISCOVER_DESCRIPTOR, conn_id, NULL);

	return ret;
}

static INT8 pm_read_attribute_value(trans_id_t trans_id, UINT8 conn_id, gatt_attribute_read_param_t *read_param)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
#if (PARANOID_STACK == TRUE)
	if (conn_id == MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	switch (read_param->att_opcode)
	{
	case ATT_OPCODE_READ_REQ:
	case ATT_OPCODE_READ_BLOB_REQ:
		ret = gatt_read_attribute_value(conn_id, read_param->att_opcode, read_param->attr_read_param.read_attr.att_id,
				read_param->attr_read_param.read_attr.offset);
		break;
	case ATT_OPCODE_READ_BY_TYPE_REQ:
		ret = gatt_read_characteristic_value_using_uuid(conn_id,
				read_param->attr_read_param.read_using_uuid_param.start_handle,
				read_param->attr_read_param.read_using_uuid_param.end_handle,
				&read_param->attr_read_param.read_using_uuid_param.uuid);
		break;
	case ATT_OPCODE_READ_MULTI_REQ:
		ret = gatt_read_multiple_characteristic_value(conn_id, read_param->attr_read_param.multi_att_id_list);
		break;
	}
	if (ret == STATUS_SUCCESS)
	{
		return pm_create_transac(trans_id, API_REQ_OPCODE_READ_ATTRIBUTE_VALUE, conn_id, NULL);
	}
	return ret;
}

static INT8 pm_write_attribute_value(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t *buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");
	switch (att_opcode)
	{
		case ATT_OPCODE_WRITE_CMD:
		case ATT_OPCODE_SIGN_WRITE_CMD:
		{
			ret = gatt_write_attribute_command(conn_id, att_opcode, att_id, buffer);
			if (ret == STATUS_PROCESS_ONGOING)
			{
				ret = pm_create_transac(trans_id, API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE, conn_id, NULL);
			}
		}
			break;
		case ATT_OPCODE_WRITE_REQ:
		case ATT_OPCODE_PREP_WRITE_REQ:
		case ATT_OPCODE_EXEC_WRITE_REQ:
		{
			ret = gatt_write_attribute_value(conn_id, att_opcode, att_id, offset, buffer);
			if (ret == STATUS_SUCCESS)
			{
				pm_create_transac(trans_id, API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE, conn_id, NULL);
			}
		}
			break;
	}
	return ret;
}

static INT8 pm_set_att_mtu_size(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	if ((ret = gatt_request_mtu(conn_id, mtu_size)) == STATUS_SUCCESS)
	{
		return pm_create_transac(trans_id, API_REQ_OPCODE_SET_ATT_MTU_SIZE, conn_id, NULL);
	}
	return ret;
}

INT8 pm_register_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, BOOLEAN is_enable)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);
	UINT8 app_handle;
	app_data_t* app_data = NULL;
	UINT8 idx, status = ATT_ERR_LOCAL_ERROR;
	logi("");

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	app_handle = get_appid_from_transid(trans_id);
	if(app_handle < MAX_NUMBER_OF_APP)
		app_data = g_local_adapter.app_list[app_handle];
	if (!app_data)
		return STATUS_ERR_INVALID_APP_HANDLE;
	for (idx = 0; idx < MAX_NUM_REG_NOTIFY_CHAR; idx ++)
	{
		if (is_enable == TRUE)
		{
			if (device->pm_device_data.reg_notify_list[idx].att_id == 0)
			{
				device->pm_device_data.reg_notify_list[idx].att_id = att_id;
				device->pm_device_data.reg_notify_list[idx].trans_id = trans_id;
				status = ATT_SUCCESS;
				break;
			}
		}
		else
		{
			UINT8 owner_app = get_appid_from_transid(device->pm_device_data.reg_notify_list[idx].trans_id);
			if (device->pm_device_data.reg_notify_list[idx].att_id == att_id &&
					owner_app == app_handle)
			{
				device->pm_device_data.reg_notify_list[idx].att_id = 0;
				device->pm_device_data.reg_notify_list[idx].trans_id = 0;
				status = ATT_SUCCESS;
				break;
			}
		}
	}
	if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_notification_registered_cb)
		app_data->app_gatt_cb->iLE_on_notification_registered_cb(trans_id, conn_id, att_id, status);
	return STATUS_SUCCESS;
}

#if 0
static INT8 pm_send_indication_response(UINT8 app_handle, UINT8 conn_id)
{
	logi("");
	if (conn_id == MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INAVALID_CONNENCTION;
	/* Send frame depending on the Profile Manager state
	 * Only Indication response can be sent from GATT client.
	 * Other responses are handled by Service Manager.
	 */
	return gatt_send_indication_confirmation(conn_id);
}
#endif

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

/*********************************************************************
 *					CALL BACKS FROM LOWER LAYERS
 *********************************************************************/
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void pm_connect_inform_apps(connected_device_t* device, UINT8 status)
{
	UINT8 idx;
	app_data_t* app_data = NULL;
	trans_id_t trans_id;

	/* Locate the transaction */
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_CONNECT, (UINT8)INVALID_INDEX);
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		/* No transaction found... peer device must have initiated the connection */
		logd("No transaction registered for this!");

		//Remote initiated connection - call conn cbs for all apps
		for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
		{
			app_data = g_local_adapter.app_list[idx];
			if (app_data && app_data->app_device_control_cb && app_data->app_device_control_cb->iLE_on_connected_cb)
			{
				if (status == STATUS_SUCCESS)
					add_conn_used(app_data, device);
				app_data->app_device_control_cb->iLE_on_connected_cb(INVALID_TRANS_ID, device->bdaddr, device->bdaddr_type, device->idx, status, TRUE, device->id_addr.bdaddr, device->id_addr.type);
			}
		}
		return;
	}

	/* Connection transaction found */
	logd("transac found");

	/* Locate the app which created the transaction */
	trans_id = get_transid_from_transac_id(transac_id);

	if (trans_id != INVALID_TRANS_ID)
	{
		/* App found... call the registered client callback */
		UINT8 app_handle = get_appid_from_transid(trans_id);
		if(app_handle < MAX_NUMBER_OF_APP)
			app_data = g_local_adapter.app_list[app_handle];

		if (app_data != NULL )
		{
			if (status == STATUS_SUCCESS)
			{
				add_conn_used(app_data, device);
				device->usage_map[app_handle] = TRUE;
			}
			if (app_data->app_device_control_cb && app_data->app_device_control_cb->iLE_on_connected_cb)
				app_data->app_device_control_cb->iLE_on_connected_cb(trans_id, device->bdaddr, device->bdaddr_type, device->idx, status, FALSE, device->id_addr.bdaddr, device->id_addr.type);
		}
	}
	else
	{
		/* Trans_id not found... probably this was an auto-connection... search the auto-connection list */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
		UINT8 aidx = get_idx_from_autoconn_list(device->id_addr.bdaddr);
		if ((aidx != MAX_NUM_CONNECTED_DEVICE) && (status == STATUS_SUCCESS))
		{
			logd("device in auto connect list");
			/* Device is in auto-connection list - call conn cbs of relevant apps */
			//Iterate over all the tras_id registered for autoconnect.
			for (idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
			{
				if (g_local_adapter.gap_data.autoconn_dev[aidx]->notify_list[idx] != INVALID_TRANS_ID)
				{
					UINT8 app_handle = get_appid_from_transid(g_local_adapter.gap_data.autoconn_dev[aidx]->notify_list[idx]);
					if(app_handle < MAX_NUMBER_OF_APP)
						app_data = g_local_adapter.app_list[app_handle];

					if (app_data && app_data->app_device_control_cb && app_data->app_device_control_cb->iLE_on_connected_cb)
					{
						add_conn_used(app_data, device);
						device->usage_map[app_handle] = TRUE;
						app_data->app_device_control_cb->iLE_on_connected_cb(g_local_adapter.gap_data.autoconn_dev[aidx]->notify_list[idx], device->bdaddr, device->bdaddr_type, device->idx, status, FALSE, device->id_addr.bdaddr, device->id_addr.type);
					}
				}
			}
		}
#endif
	}

#if (GAP_GATT_SRV_APP == TRUE)
	/* Inform GATT service about new connection */
	if (g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE] && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_connected_cb)
		g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_connected_cb(INVALID_TRANS_ID, device->bdaddr, device->bdaddr_type, device->idx, status, FALSE, device->id_addr.bdaddr, device->id_addr.type);
#endif

	pm_finish_transac(transac_id, device->idx);
}

/* This function should be used only in case of error and
 * when there is no (connected_device_t) device object exists for the failed connection */
void pm_connect_error_cb(UINT8 *bdaddr, UINT8 addr_type, UINT8 status)
{
	UINT8 transac_id, idx = MAX_NUM_CONNECTED_DEVICE;

	/* Check if pm transaction exists for Connect request */
	transac_id = pm_find_transac_id(API_REQ_OPCODE_CONNECT, (UINT8)INVALID_INDEX);
	if (transac_id != MAX_NUMBER_OF_PM_REQ) /* pm transaction found */
	{
		/* Locate the app that created the transaction */
		trans_id_t trans_id = get_transid_from_transac_id(transac_id);
		if (trans_id != INVALID_TRANS_ID)
		{
			UINT8 app_handle = get_appid_from_transid(trans_id);
			if (app_handle < MAX_NUMBER_OF_APP)
			{
				app_data_t* app_data = g_local_adapter.app_list[app_handle];
				if (app_data != NULL )
				{
					if (app_data->app_device_control_cb && app_data->app_device_control_cb->iLE_on_connected_cb)
						app_data->app_device_control_cb->iLE_on_connected_cb(trans_id, bdaddr, addr_type, idx, status, FALSE, bdaddr, addr_type);
				}
			}
		}
		pm_finish_transac(transac_id, idx);
	}
}

void pm_connect_cb(connected_device_t* device, UINT8 result)
{
	UINT8 rev_bdaddr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr_ptr;
	UINT8 auto_idx;

	if (!device)
		return;

	/* Let the relevant layers know that a connection has been established */
	if (result == STATUS_SUCCESS)
	{
		logd("device->pm_device_data.init_done :%d", device->pm_device_data.init_done);
		if (device->pm_device_data.init_done == FALSE)
		{
			logd("Call sm_connect_cb");
			att_l2cap_connect_cb(device);
			sm_connect_cb(device);
			device->pm_device_data.init_done = TRUE;

			/* Initialise pending request queue for this device */
			init_no_guard_q(&device->pm_device_data.pending_req_q);
			device->pm_device_data.pm_state = PM_STATE_IDLE;

		}


		auto_idx = get_idx_from_autoconn_list(device->id_addr.bdaddr);
		if (auto_idx != MAX_NUM_CONNECTED_DEVICE)
		{
			rev_bdaddr_ptr = rev_bdaddr;
			REVERSE_ARRAY_TO_STREAM(rev_bdaddr_ptr, g_local_adapter.gap_data.autoconn_dev[auto_idx]->idaddr, BD_ADDR_LEN);
			gap_add_to_whitelist(g_local_adapter.gap_data.autoconn_dev[auto_idx]->idaddr_type, rev_bdaddr);
		}

		smp_l2cap_connect_cb(device);

#if (GATT_CLIENT_SUPPORTED == TRUE)
	/* FIXME: This should happen even for servers */
	/* If Privacy 1.2 is supported, read the Central Address Resolution characteristic of the peer */
#if (CONTROLLER_PRIVACY)
		if (LL_PRIVACY_IS_SUPPORTED && (device->car_supported == PEER_CAR_SUPPORT_UNKNOWN))
		{
			pm_req_handler(create_req_for_CAR_support(device->idx));
		}
#endif /* CONTROLLER_PRIVACY */
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

	}

	if(result == STATUS_SUCCESS)
	{
		if(device->link_enc_state.state == LINK_ENC_STATE_NONE)
		{
			if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb)
			{
				device->link_enc_state.state = LINK_ENC_STATE_UPDATING;
				g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->id_addr.bdaddr, device->id_addr.type, SEC_INFO);
			}
			else
			{
				device->link_enc_state.state = LINK_ENC_STATE_UPDATED;
				device->link_enc_state.key_size = 0;
				device->link_enc_state.key_type = 0;
				device->link_enc_state.keys_distributed = 0;
			}
		}
	}
	pm_connect_inform_apps(device, result);
}

void pm_disconnect_cb(connected_device_t* device, UINT8 reason)
{
	pm_transactions_elem_t* transac;
	app_data_t* app_data = NULL;
	UINT8 idx;
	UINT8 transac_id;
	if (!device)
		return;
	logi("");
	if (reason) /* Non Zero = success with reason code, 0 = failed with no reason*/
	{
		smp_l2cap_disconnect_cb(device);
		sm_disconnect_cb(device);

		/* Cleanup pending request q */
		device->pm_device_data.pm_state = PM_STATE_IDLE;
#if (GATT_CLIENT_SUPPORTED == TRUE)
			for (idx = 0; idx < MAX_NUMBER_OF_PM_REQ; idx++)
			{
				pm_dequeue_and_cleanup_from_pending_queue(device->idx);
			}
#endif /* #if (GATT_CLIENT_SUPPORTED == TRUE) */
			cleanup_q(&device->pm_device_data.pending_req_q); /* FIXME: if there is a pending req. Cleanup all the memory consumed by the request. */
	}

	transac_id = pm_find_transac_id(API_REQ_OPCODE_DISCONNECT, device->idx);
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		UINT8 aidx = get_idx_from_autoconn_list(device->id_addr.bdaddr);
		logd("No transaction registered for this!");
		if (aidx != MAX_NUM_CONNECTED_DEVICE) //TODO: This is redundant. Else part already covers this.
		{
			UINT8 app_handle;

			//Device is in auto-connection list - call cbs of relevant apps
			for (idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
			{
				if (g_local_adapter.gap_data.autoconn_dev[aidx]->notify_list[idx] != INVALID_TRANS_ID)
				{
					app_handle = get_appid_from_transid(g_local_adapter.gap_data.autoconn_dev[aidx]->notify_list[idx]);
					if(app_handle < MAX_NUMBER_OF_APP)
						app_data = g_local_adapter.app_list[app_handle];
					if (app_data && is_conn_used(app_data, device) && app_data->app_device_control_cb)
					{
/*						for(chr_idx = 0 ; chr_idx < MAX_NUMBER_OF_CHAR_PER_SERV; chr_idx ++)
							app_data->reg_notification_chars[chr_idx] = 0;*/
						remove_conn_used(app_data, device);
						if (app_data->app_device_control_cb->iLE_on_disconnected_cb)
							app_data->app_device_control_cb->iLE_on_disconnected_cb(INVALID_TRANS_ID, device->idx, reason);// To Do : what trans_id to be put here
					}
				}
			}
#if (GAP_GATT_SRV_APP == TRUE)
			/* Inform GATT service about disconnection */
			if (g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE] && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_disconnected_cb)
				g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_disconnected_cb(INVALID_TRANS_ID, device->idx, reason);
#endif
		}
		else
		{
			UINT8 app_idx;
			//Remote device was client - call cbs for all apps
			for (app_idx = 0; app_idx < MAX_NUMBER_OF_APP; app_idx++)
			{
				app_data = g_local_adapter.app_list[app_idx];
				if (app_data && is_conn_used(app_data, device) && app_data->app_gatt_cb)
				{
/*					for(chr_idx = 0 ; chr_idx < MAX_NUMBER_OF_CHAR_PER_SERV; chr_idx ++)
						app_data->reg_notification_chars[chr_idx] = 0;*/
					remove_conn_used(app_data, device);
					if (app_data->app_device_control_cb->iLE_on_disconnected_cb)
						app_data->app_device_control_cb->iLE_on_disconnected_cb(INVALID_TRANS_ID, device->idx, reason);// To Do : what trans_id needs to be added here?
				}
			}
		}
	}
	else
	{
		trans_id_t trans_id = get_transid_from_transac_id(transac_id);
		UINT8 app_handle = get_appid_from_transid(trans_id);
		if (app_handle < MAX_NUMBER_OF_APP)
		{
			app_data = g_local_adapter.app_list[app_handle];
			if (app_data != NULL )
			{
	/*			for(chr_idx = 0 ; chr_idx < MAX_NUMBER_OF_CHAR_PER_SERV; chr_idx ++)
					app_data->reg_notification_chars[chr_idx] = 0;*/
				remove_conn_used(app_data, device);
				if(app_data->app_device_control_cb && app_data->app_device_control_cb->iLE_on_disconnected_cb)
					app_data->app_device_control_cb->iLE_on_disconnected_cb(trans_id, device->idx, reason);
			}
		}
		pm_finish_transac(transac_id, device->idx);
	}

	/* Finish any pending transaction for disconnected device */
	for (idx = 0; idx < MAX_NUMBER_OF_PM_REQ; idx++)
	{
		transac = g_local_adapter.pm_transac_list[idx];
		if ((transac != NULL) && (transac->connected_device_idx == device->idx))
		{
			if(transac->additional_param)
				dealloc(transac->additional_param);
			dealloc(transac);

			g_local_adapter.pm_transac_list[idx] = NULL;
		}
	}

#if (GAP_GATT_SRV_APP == TRUE)
	/* Inform GATT service about disconnection */
	if (g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE] && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_disconnected_cb)
		g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_device_control_cb->iLE_on_disconnected_cb(INVALID_TRANS_ID, device->idx, reason);
#endif
}

#if (TEST_CODE == TRUE && LE_PING_ENABLE == TRUE)
void pm_read_authpayload_timeout_cb(UINT8 conn_id, UINT16 authpayload_timeout)
{

	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT, conn_id);
	logd("[LE_PING]CB auth_payload_timeout = %x", authpayload_timeout);
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
		return;
	trans_id_t trans_id = get_transid_from_transac_id(transac_id);
	UINT8 app_handle = get_appid_from_transid(trans_id);

	if(app_handle < MAX_NUMBER_OF_APP)
	{
		if(g_local_adapter.app_list[app_handle] &&
				g_local_adapter.app_list[app_handle]->app_device_control_cb &&
				g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_read_authpayload_timeout_cb)
				g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_read_authpayload_timeout_cb(trans_id, conn_id, authpayload_timeout * 10);
	}
	pm_finish_transac(transac_id, conn_id);
}
#endif //TEST_CODE && LE_PING_ENABLE
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE || GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

void pm_att_mtu_changed_cb(UINT8 conn_id, UINT16 updated_mtu_size)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_SET_ATT_MTU_SIZE, conn_id);
	UINT8 app_handle = MAX_NUMBER_OF_APP;
	trans_id_t trans_id = INVALID_TRANS_ID;
	UINT8 app_idx;

	if (transac_id != MAX_NUMBER_OF_PM_REQ)
	{
		trans_id = get_transid_from_transac_id(transac_id);
		if (trans_id != INVALID_TRANS_ID)
			app_handle = get_appid_from_transid(trans_id);

		pm_finish_transac(transac_id, conn_id);
	}

	//call cbs of all the apps
	for (app_idx = 0; app_idx < MAX_NUMBER_OF_APP; app_idx++)
	{

		if(g_local_adapter.app_list[app_idx]&&
			g_local_adapter.app_list[app_idx]->app_gatt_cb && g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_att_mtu_changed_cb)
		{
			if (app_idx == app_handle)
				g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_att_mtu_changed_cb(trans_id, conn_id, updated_mtu_size);
			else
				g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_att_mtu_changed_cb(INVALID_TRANS_ID, conn_id, updated_mtu_size);
		}
	}
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)
void pm_primary_service_discovered_cb(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE, conn_id);
	trans_id_t trans_id ;
	UINT8 app_handle;
	logi("");
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		loge("No transaction registered for this!");
		return;
	}
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		if (app_data)
			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_primary_service_discovered_cb)
				app_data->app_gatt_cb->iLE_on_primary_service_discovered_cb(trans_id, STATUS_SUCCESS, conn_id, start_handle, end_handle, uuid, is_finished);
	}
	if (is_finished == TRUE)
		pm_finish_transac(transac_id, conn_id);
}

void pm_included_service_discovered_cb(UINT8 conn_id, UINT16 inc_handle, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE, conn_id);
	trans_id_t trans_id;
	UINT8 app_handle;
	logi("");
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		loge("No transaction registered for this!");
		return;
	}
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		if (app_data)
			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_included_service_discovered_cb)
				app_data->app_gatt_cb->iLE_on_included_service_discovered_cb(trans_id, STATUS_SUCCESS, conn_id, inc_handle, start_handle, end_handle, uuid, is_finished);
	}
	if (is_finished == TRUE)
		pm_finish_transac(transac_id, conn_id);
}

void pm_characteristic_discovered_cb(UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_DISCOVER_CHARACTERISTIC, conn_id);
	trans_id_t trans_id;
	UINT8 app_handle;
	logi("");
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		loge("No transaction registered for this!");
		return;
	}
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		if (app_data)
			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_characteristic_discovered_cb)
				app_data->app_gatt_cb->iLE_on_characteristic_discovered_cb(trans_id, STATUS_SUCCESS, conn_id, property, att_handle, value_handle, uuid, is_finished);
	}
	if (is_finished == TRUE)
		pm_finish_transac(transac_id, conn_id);
}

void pm_descriptor_discovered_cb(UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_DISCOVER_DESCRIPTOR, conn_id);
	trans_id_t trans_id;
	UINT8 app_handle;
	logi("");
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		loge("No transaction registered for this!");
		return;
	}
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		if (app_data)
			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_descriptor_discovered_cb)
				app_data->app_gatt_cb->iLE_on_descriptor_discovered_cb(trans_id, STATUS_SUCCESS, conn_id, att_handle, uuid, is_finished);
	}
	if (is_finished == TRUE)
		pm_finish_transac(transac_id, conn_id);
}

void pm_on_read_attribute_cb(UINT8 conn_id, UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t *buffer)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_READ_ATTRIBUTE_VALUE, conn_id);
	trans_id_t trans_id ;
	UINT8 app_handle;

#if (CONTROLLER_PRIVACY)
	connected_device_t *device = g_local_adapter.connected_device[conn_id];

	if ((device->car_supported == PEER_CAR_SUPPORT_UNKNOWN) && (transac_id == MAX_NUMBER_OF_PM_REQ))
	{
		/* Assume this is a stack initiated request for the Central Address Resolution characteristic value */
		logd("CAR support read");

		if (att_opcode == ATT_OPCODE_READ_BY_TYPE_RESP)
		{
			if ((status == ATT_SUCCESS) && buffer)
				device->car_supported = buffer->data[buffer->offset];
			else
				device->car_supported = PEER_CAR_SUPPORT_ABSENT;
			logd("Remote device CAR support = %u", device->car_supported);
			// TO DO : Add CAR Supported value to the storage
		}
		pm_req_handler(NULL);
		return;
	}
#endif /* CONTROLLER_PRIVACY */
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_read_cb)
			app_data->app_gatt_cb->iLE_on_attribute_read_cb(trans_id, conn_id, att_opcode, status, att_id, buffer);
	}
	pm_finish_transac(transac_id, conn_id);
}

void pm_on_attribute_write_cb(UINT8 conn_id, UINT8 opcode, UINT8 status, UINT16 att_id, UINT16 offset, buffer_t* buffer)
{
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE, conn_id);
	trans_id_t trans_id;
	UINT8 app_handle;
	if (transac_id == MAX_NUMBER_OF_PM_REQ)
	{
		loge("No transaction registered for this!");
		return;
	}
	trans_id = get_transid_from_transac_id(transac_id);
	app_handle = get_appid_from_transid(trans_id);
	if (app_handle < MAX_NUMBER_OF_APP)
	{
		app_data_t* app_data = g_local_adapter.app_list[app_handle];
		logd("status:%d", status);
		if (app_data)
			if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_write_cb)
				app_data->app_gatt_cb->iLE_on_attribute_write_cb(trans_id, conn_id, opcode, status, att_id, offset, buffer);
	}
	pm_finish_transac(transac_id, conn_id);
}

void pm_on_characteristic_notification_cb(UINT8 conn_id, UINT16 att_id, buffer_t* buffer, BOOLEAN is_indication)
{
	/* Find out the application(s) to which this notification should go */
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	UINT8 idx;
	app_data_t* app_data = NULL;
#if (PARANOID_STACK == TRUE)
	if (!buffer || !device)
		return;
#endif
	for (idx = 0; idx < MAX_NUM_REG_NOTIFY_CHAR; idx++)
	{
		if (device->pm_device_data.reg_notify_list[idx].att_id == att_id)
		{
			UINT8 app_handle = get_appid_from_transid(device->pm_device_data.reg_notify_list[idx].trans_id);
			if(app_handle < MAX_NUMBER_OF_APP)
				app_data = g_local_adapter.app_list[app_handle];

			if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_notification_cb)
			{
				app_data->app_gatt_cb->iLE_on_notification_cb(device->pm_device_data.reg_notify_list[idx].trans_id, conn_id, att_id, buffer, is_indication);
			}
			return;
		}
	}
	loge("Characteristic notification(att_id: %d) not registered. NOTE: Register with characteristic value handle.", att_id);
}

void pm_gatt_client_timeout_cb(UINT8 conn_id)
{
	UINT8              app_handle;
	trans_id_t         trans_id;
	connected_device_t *device;
	UINT8              transac_id;

	device = get_connected_device_by_conn_id(conn_id);
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
	loge("");
	app_handle = (UINT8)INVALID_INDEX;
	transac_id = pm_find_transac_id((UINT8)INVALID_INDEX, device->idx);
	if (transac_id != MAX_NUMBER_OF_PM_REQ)
	{
		trans_id = get_transid_from_transac_id(transac_id);
		if(trans_id == INVALID_TRANS_ID)
			app_handle = (UINT8)INVALID_INDEX;
		else
			app_handle = get_appid_from_transid(trans_id);
	}
	if (app_handle == MAX_NUMBER_OF_APP)
		app_handle = (UINT8)INVALID_INDEX;
	if (transac_id != MAX_NUMBER_OF_PM_REQ)
		pm_finish_transac(transac_id, conn_id);

#if (CONTROLLER_PRIVACY)
	/* Check if the ATT read request for CAR support timed out */
	if (app_handle == (UINT8)INVALID_INDEX && transac_id == MAX_NUMBER_OF_PM_REQ && device->car_supported == PEER_CAR_SUPPORT_UNKNOWN)
	{
		/* Since CAR support read goes only for the very first app who tries to connect to the
		 * device, the usage_map of the device should have only one valid entry at this stage.
		 */
		UINT8 idx;
		for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
			if (device->usage_map[idx])
				break;
		app_handle = idx;
	}
#endif /* CONTROLLER_PRIVACY */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	iLE_disconnect(transac_id, device->idx, GAP_DISCONNECT_REASON_TERM_CONNECTION_RESOURCE);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	USE(app_handle);
}

#if (SIGNED_WRITE)
void pm_data_signing_complete_cb(UINT8 conn_id, UINT8 status, UINT8* signed_data)
{
	/* For a GATT signed write the signature generation is completed. */
	UINT8 transac_id = pm_find_transac_id(API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE, conn_id);
	interface_req_elem_t* req = get_req_to_process();
	pm_write_attribute_value_param_t* param;
	INT8 ret = ATT_ERR_UNLIKELY;
	UINT8 app_handle;
	app_data_t* app_data = NULL;
	logi("");
	if(!req)
	{
		logw("No request found");
		return;
	}
#if (PARANOID_STACK == TRUE)
	if (!req || req->req_opcode != API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE)
		return;  //this should never happen.
#endif
	param = (pm_write_attribute_value_param_t*)(void*)req->parameter;

	if (status == STATUS_SUCCESS)
		ret = gatt_send_signed_write(param->conn_id, param->att_id, &param->buffer, signed_data);
	app_handle = get_appid_from_transid(param->trans_id);
	if(app_handle < MAX_NUMBER_OF_APP)
		app_data = g_local_adapter.app_list[app_handle];

	if (ret == STATUS_SUCCESS)
	{
		if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_write_cb)
			app_data->app_gatt_cb->iLE_on_attribute_write_cb(param->trans_id, param->conn_id, param->att_opcode, ATT_SUCCESS, param->att_id, param->offset, &param->buffer);
	}
	else
	{
		if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_attribute_write_cb)
			app_data->app_gatt_cb->iLE_on_attribute_write_cb(param->trans_id, param->conn_id, param->att_opcode, ATT_ERR_UNLIKELY, param->att_id, param->offset, &param->buffer);
	}
	pm_finish_transac(transac_id, conn_id);
}
#endif /* SMP_SECURITY_LVL > DEVICE_SECURITY_LVL_3 */
#endif /* GATT_CLIENT_SUPPORTED == TRUE */
