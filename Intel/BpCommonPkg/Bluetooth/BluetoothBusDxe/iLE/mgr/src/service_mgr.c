/** @file
  Service manager implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "device_struct.h"
#include "gatt.h"
#include "utils.h"
#include "service_mgr.h"
#include "interface.h"

#define MODULE_DBG_LVL SERVICE_MGR_DBG_LVL
#include "log.h"

UINT16 get_att_idx_from_hdl(UINT16 att_handle)
{
	UINT16 att_idx;
	for (att_idx = 0; att_idx < MAX_NUM_ATTR; att_idx ++)
		if (g_local_adapter.attribute_list[att_idx].attr_handle == att_handle)
			return att_idx;
	return MAX_NUM_ATTR;
}

static trans_id_t get_owner_trans_id_from_hdl(UINT16 att_handle)
{
	UINT8 idx;
	trans_id_t trans_id = INVALID_TRANS_ID;
	if (att_handle > get_max_att_handle())
		return trans_id;
	for (idx = 0; ; idx++)
	{
		if (g_local_adapter.attribute_list[idx].attr_handle == att_handle)
			break;
		if (g_local_adapter.attribute_list[idx].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
				trans_id = g_local_adapter.attribute_list[idx].attr_data.srv_data.owner_trans_id;
	}
	return trans_id;
}

UINT16 get_max_att_handle()
{
	UINT16 att_idx;
	for (att_idx = 0; att_idx < MAX_NUM_ATTR; att_idx++)
		if (g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_ANY)
			return (att_idx ? g_local_adapter.attribute_list[att_idx-1].attr_handle : 0);
	return MAX_NUM_ATTR;
}

void sm_read_attribute(UINT8 conn_id, UINT8 att_opcode, UINT16 att_hdl, UINT16 offset)
{
	trans_id_t owner_trans_id = get_owner_trans_id_from_hdl(att_hdl);
	UINT8 app_idx;
	logi("");
	if(owner_trans_id == INVALID_TRANS_ID)
		app_idx = (UINT8)INVALID_INDEX;
	else
	app_idx = get_appid_from_transid(owner_trans_id);

	if ((app_idx < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_idx])
	{
		if (g_local_adapter.app_list[app_idx]->app_gatt_cb)
		{
			if (g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_attribute_read_req_cb)
			{
				g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_attribute_read_req_cb(owner_trans_id, conn_id, att_opcode, att_hdl, offset);
			}
		}
	}
}

#if (GATT_SERVER_SUPPORTED == TRUE)

static INT8 sm_send_attribute_read_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, buffer_t* buffer)
{
	return gatt_send_attr_read_rsp(conn_id, att_opcode, att_id, status, buffer);
}

static INT8 sm_send_attribute_write_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, UINT16 offset, buffer_t* buffer)
{
	logd("");
	return gatt_send_attr_write_rsp(conn_id, att_opcode, att_id, status, offset, buffer);
}

static INT8 sm_send_nofication(UINT8 conn_id, UINT16 att_id, buffer_t* buffer, BOOLEAN need_resp)
{
	if (need_resp == FALSE)
		return gatt_send_value_notification(conn_id, att_id, buffer);
	else
		return gatt_send_value_indication(conn_id, att_id, buffer);
}

static INT8 sm_set_service_change_config(UINT8 conn_id, BOOLEAN is_notify)
{
	logd("");
	return gatt_set_service_change_config(conn_id, is_notify);
}

BOOLEAN sm_get_service_change_config(UINT8 conn_id)
{
	return gatt_get_service_change_config(conn_id);
}

UINT16 get_first_free_att_handle(UINT8 app_handle)
{
	UINT16 idx;
	for (idx = 1; idx < MAX_NUM_ATTR; idx++)
	{
		if (g_local_adapter.attribute_list[idx].attr_type == FALSE)
			return idx;
	}
	return MAX_NUM_ATTR;
}

static INT8 sm_enqueue_req_in_pending_queue(interface_req_elem_t *incoming_req)
{
	if (!incoming_req)
		return STATUS_ERR_INVALID_PARAM;

	connected_device_t *device = NULL;
	device = get_connected_device_by_conn_id(incoming_req->conn_id);
	if (!device)
	{
		logd("device is NULL. req not added to pending queue");
		return STATUS_ERR_INAVALID_CONNENCTION;
	}
	return enqueue(&device->sm_device_data.pending_req_q, (void*)incoming_req);
}

static void sm_dequeue_and_cleanup_from_pending_queue(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return;
	interface_req_elem_t* req = (interface_req_elem_t*)dequeue(&device->sm_device_data.pending_req_q);
	if (req)
	{
		logd("delete req");
		dealloc_queue_element(req);
	}
}

static interface_req_elem_t* get_req_to_process()
{
	connected_device_t *device = NULL;
	UINT8 idx = g_local_adapter.sm_device_idx_to_execute;
	interface_req_elem_t* front_req = NULL;

	if (idx < MAX_NUM_CONNECTED_DEVICE)
		device = g_local_adapter.connected_device[idx];
	if (device)
		front_req = (interface_req_elem_t*)pick_front(&device->sm_device_data.pending_req_q);

	if (!front_req)
	{
		/* No pending request found at specified index... look for one */
		for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
		{
			device = g_local_adapter.connected_device[idx];
			if (device)
			{
				front_req = (interface_req_elem_t*)pick_front(&device->sm_device_data.pending_req_q);
				if (front_req)
					break;
			}
		}
	}

	/* Set up the next device index to execute */
	UINT8 count = 0;
	for (; count < MAX_NUM_CONNECTED_DEVICE; count++)
	{
		idx = (idx + 1) % MAX_NUM_CONNECTED_DEVICE;
		device = g_local_adapter.connected_device[idx];
		if (device)
			break;
	}

	if (count != MAX_NUM_CONNECTED_DEVICE)
		g_local_adapter.sm_device_idx_to_execute = idx;

	return front_req;
}

/**
 * adds service to attribute db and sends back the handle
 * Returns status, 0 on success and Non Zero on Error
 */
static INT8 add_service(UINT16 next_free_handle, trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT8 num_of_incl_srv, UINT8 num_of_char, UINT8 num_of_desc, UINT16 *service_handle)
{
	if (next_free_handle) /* This should be 0. Otherwise the app is adding another service */
	{
		loge("Please start previous service before adding new service!");
		return STATUS_ERR_GATT_PREV_SVC_NOT_STARTED;
	}
	if (!g_local_adapter.last_attr_idx)
	{
		/* First service */
		next_free_handle = 1;
	}
	else
	{
		next_free_handle = g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle + 1;
		g_local_adapter.last_attr_idx++;
	}

	UINT16 end_handle = next_free_handle + num_of_incl_srv + num_of_char * 2 + num_of_desc;
	if (g_local_adapter.last_attr_idx + (end_handle - next_free_handle) >= MAX_NUM_ATTR)
	{
		loge("Attribute database size is not enough");
		if (g_local_adapter.last_attr_idx)
			g_local_adapter.last_attr_idx--;
		return STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED;
	}

	g_local_adapter.last_srv_end_handle = end_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.srv_data.owner_trans_id = trans_id;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_type = service_type;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid = *uuid;
	if (uuid->length == UUID_32BIT_TYPE_LEN)
		 util_convert_uuid_to_uuid128(&g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid);
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle = next_free_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.srv_data.end_handle = end_handle;
	*service_handle = next_free_handle;
	return STATUS_SUCCESS;
}

/*
 * Helper function to get the last added primary service uuid
 * */
static uuid_t* get_last_added_service_uuid(UINT16 last_added_handle)
{
	for (;last_added_handle > 0; last_added_handle --)
	{
		if (g_local_adapter.attribute_list[last_added_handle].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			return &g_local_adapter.attribute_list[last_added_handle].uuid;
	}
	return NULL;
}

/**
 * adds include service to attribute db and sends back the handle
 * Returns status, 0 on success and Non Zero on Error
 */
static INT8 add_include_service(UINT16 next_free_handle, trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT16 start_handle, UINT16 end_handle, UINT16 *include_service_handle)
{
	if (!next_free_handle)
	{
		loge("No Primary Service added for this Included Service");
		return STATUS_ERR_GATT_NO_PRIM_SVC_ADDED;
	}
	if (g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle >= g_local_adapter.last_srv_end_handle)
	{
		loge("Attribute entry exceeded for this Service");
		return STATUS_ERR_GATT_SVC_ADD_ATTR_EXCEEDED;
	}
	if (g_local_adapter.last_attr_idx + 1 >= MAX_NUM_ATTR)
	{
		loge("Attribute database size is not enough");
		return STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED;
	}
	g_local_adapter.last_attr_idx++;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.inc_srv_data.start_handle = start_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.inc_srv_data.end_handle = end_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_type = service_type;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle = next_free_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid = *uuid;
	if (uuid->length == UUID_32BIT_TYPE_LEN)
		 util_convert_uuid_to_uuid128(&g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid);

	*include_service_handle = next_free_handle;
	return STATUS_SUCCESS;
}

/*
* Returns status, 0 on success and Non Zero on Error
* */
static INT8 add_char_desc(UINT16 next_free_handle, UINT8 attr_type, UINT8 property, UINT16 permission, uuid_t *uuid, UINT16 *handle)
{
	if (!next_free_handle)
	{
		loge("No Primary Service added for this Characteristic/Descriptor");
		return STATUS_ERR_GATT_NO_PRIM_SVC_ADDED;
	}
	if (g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle >= g_local_adapter.last_srv_end_handle)
	{
		loge("Attribute entry exceeded for this Service");
		return STATUS_ERR_GATT_SVC_ADD_ATTR_EXCEEDED;
	}
	if ((attr_type == ATTR_TYPE_CHARACTERISTIC) && (g_local_adapter.last_attr_idx + 2 >= MAX_NUM_ATTR))
	{
		loge("Attribute database size is not enough");
		return STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED;
	}
	if ((attr_type == ATTR_TYPE_DESCRIPTOR) && (g_local_adapter.last_attr_idx + 1 >= MAX_NUM_ATTR))
	{
		loge("Attribute database size is not enough");
		return STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED;
	}
	g_local_adapter.last_attr_idx++;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.char_desc_data.property = property;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_data.char_desc_data.permission = permission;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_type = attr_type;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle = next_free_handle;
	g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid = *uuid;
	if (uuid->length == UUID_32BIT_TYPE_LEN)
		 util_convert_uuid_to_uuid128(&g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid);

	if (attr_type == ATTR_TYPE_CHARACTERISTIC)
	{
		g_local_adapter.last_attr_idx++;
		g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_type = ATTR_TYPE_CHARACTERISTIC_VALUE;
		g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle = next_free_handle + 1;
		g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid = *uuid;
		if (uuid->length == UUID_32BIT_TYPE_LEN)
			 util_convert_uuid_to_uuid128(&g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].uuid);
	}
	*handle = next_free_handle;
	return STATUS_SUCCESS;
}

static void sm_dump_att_db()
{
#if (MODULE_DBG_LVL >= DBG_LVL_DEBUG)
	UINT16 idx;
	char *attribute_type_string[] = {
			"ATTR_TYPE_ANY",
			"ATTR_TYPE_PRIMARY_SERVICE",
			"ATTR_TYPE_SECONDARY_SERVICE",
			"ATTR_TYPE_INCLUDED_SERVICE",
			"ATTR_TYPE_CHARACTERISTIC",
			"ATTR_TYPE_DESCRIPTOR",
			"ATTR_TYPE_CHARACTERISTIC_VALUE"
	};

	for (idx = 0; idx < MAX_NUM_ATTR; idx++)
	{
		if (g_local_adapter.attribute_list[idx].attr_type == ATTR_TYPE_ANY)
			break;
		if (g_local_adapter.attribute_list[idx].attr_type != ATTR_TYPE_INVALID)
		{
			char str[40];
			UUID_TO_STRING(str, g_local_adapter.attribute_list[idx].uuid);
			if (g_local_adapter.attribute_list[idx].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				logd("(%u) : handle:%u(0x%04x) %s end_handle:%u(%04x) uuid:%s", idx, g_local_adapter.attribute_list[idx].attr_handle, g_local_adapter.attribute_list[idx].attr_handle,
						attribute_type_string[g_local_adapter.attribute_list[idx].attr_type],
						g_local_adapter.attribute_list[idx].attr_data.srv_data.end_handle,
						g_local_adapter.attribute_list[idx].attr_data.srv_data.end_handle,
						str);
			}
			else if (g_local_adapter.attribute_list[idx].attr_type == ATTR_TYPE_INCLUDED_SERVICE)
			{
				logd("(%u) : handle:%u(0x%04x) %s inc_srv_start_handle:%u(%04x) inc_srv_end_handle:%u(%04x) uuid:%s", idx, g_local_adapter.attribute_list[idx].attr_handle, g_local_adapter.attribute_list[idx].attr_handle,
						attribute_type_string[g_local_adapter.attribute_list[idx].attr_type],
						g_local_adapter.attribute_list[idx].attr_data.inc_srv_data.start_handle,
						g_local_adapter.attribute_list[idx].attr_data.inc_srv_data.start_handle,
						g_local_adapter.attribute_list[idx].attr_data.inc_srv_data.end_handle,
						g_local_adapter.attribute_list[idx].attr_data.inc_srv_data.end_handle,
						str);
			}
			else
			{
				logd("(%u) : handle:%u(0x%04x) %s uuid:%s", idx, g_local_adapter.attribute_list[idx].attr_handle, g_local_adapter.attribute_list[idx].attr_handle,
						attribute_type_string[g_local_adapter.attribute_list[idx].attr_type], str);
			}
		}
	}
#endif
}

static INT8 remove_service(trans_id_t trans_id, UINT16 start_handle)
{
	logd("");
	UINT8 app_handle = get_appid_from_transid(trans_id);

	if (app_handle >= MAX_NUMBER_OF_APP || g_local_adapter.app_list[app_handle] == NULL)
	{
		loge("Invalid app handle:%u !!!",app_handle);
		return STATUS_ERR_INVALID_APP_HANDLE;
	}


	UINT16 start_idx = get_att_idx_from_hdl(start_handle);
	if (start_idx == MAX_NUM_ATTR) /* Arribute Handle not found */
	{
		if (g_local_adapter.app_list[app_handle] && g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb)
			g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb(trans_id, STATUS_ERR_INVALID_ATTRIBUTE, 0, 0);
		return STATUS_ERR_INVALID_ATTRIBUTE;
	}

	if (!(g_local_adapter.attribute_list[start_idx].attr_type == ATTR_TYPE_PRIMARY_SERVICE))
	{
		logd("No service at handle 0x%04x", start_handle);
		UINT8 app_handle = get_appid_from_transid(trans_id);
		if (g_local_adapter.app_list[app_handle] && g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb)
			g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb(trans_id, STATUS_ERR_INVALID_ATTRIBUTE, 0, 0);

		return STATUS_ERR_INVALID_ATTRIBUTE;
	}

	if (g_local_adapter.attribute_list[start_idx].attr_data.srv_data.owner_trans_id != trans_id)
	{
		logd("Service at 0x%04x not owned by app id %u, trans id 0x%04X", start_handle, app_handle, trans_id);

		if (g_local_adapter.app_list[app_handle] && g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb)
			g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb(trans_id, STATUS_ERR_INVALID_APP_HANDLE, 0, 0);

		return STATUS_ERR_INVALID_APP_HANDLE;
	}

	UINT16 end_handle = g_local_adapter.attribute_list[start_idx].attr_data.srv_data.end_handle;
	UINT16 end_idx = get_att_idx_from_hdl(end_handle) + 1;
	if (end_idx >= MAX_NUM_ATTR)
	{
		/* Check if remove service performed on incomplete service. */
		if (end_handle == g_local_adapter.last_srv_end_handle)
		{
			logd("Remove Incomplete Service.");
			end_idx = start_idx + 1;
			/* set end_idx to first free entry of att db */
			while( end_idx < MAX_NUM_ATTR && g_local_adapter.attribute_list[end_idx].attr_type != ATTR_TYPE_ANY)
				++end_idx;
			end_handle = g_local_adapter.attribute_list[end_idx - 1].attr_handle;
			/* Reset back to success state as incomplete service is being removed */
    		g_local_adapter.last_srv_end_handle = 0;
            g_local_adapter.next_free_handle = 0;
		}
		else
		{
			loge("Service end handle not found for handle: %u !!!",start_handle);
			return STATUS_ERR_INVALID_ATTRIBUTE;
		}
	}

	/* Move up existing entries */
	for (; end_idx < MAX_NUM_ATTR; start_idx++, end_idx++)
	{
		if (g_local_adapter.attribute_list[end_idx].attr_type == ATTR_TYPE_ANY)
			break;
		memcpy(&g_local_adapter.attribute_list[start_idx], &g_local_adapter.attribute_list[end_idx], sizeof(gatt_attribute_t));
	}

	/* Reset last_attr_idx */
	g_local_adapter.last_attr_idx = start_idx - 1;

	/* Reset service entries to free */
	for (; start_idx < end_idx; start_idx++)
		memset(&g_local_adapter.attribute_list[start_idx], 0, sizeof(gatt_attribute_t));


	if (g_local_adapter.app_list[app_handle] && g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb)
		g_local_adapter.app_list[app_handle]->app_gatt_cb->iLE_on_service_removed_cb(trans_id, STATUS_SUCCESS, start_handle, end_handle);

#if (GAP_GATT_SRV_APP == TRUE)
	/* Inform GATT service about removed service */
	if (g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE] && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb->iLE_on_service_removed_cb)
		g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb->iLE_on_service_removed_cb(trans_id, STATUS_SUCCESS, start_handle, end_handle);
#endif

	return STATUS_SUCCESS;
}

INT8 sm_remove_app_all_services(UINT8 app_handle)
{
	logd("");
	UINT8 idx;
	UINT8 owner_app;
	do
	{
		for (idx = 0; idx < MAX_NUM_ATTR; idx++)
		{
			if (g_local_adapter.attribute_list[idx].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				trans_id_t owner_trans_id = g_local_adapter.attribute_list[idx].attr_data.srv_data.owner_trans_id;
				owner_app = get_appid_from_transid(owner_trans_id);
				if ( owner_app == app_handle)
				{
					remove_service(owner_trans_id, g_local_adapter.attribute_list[idx].attr_handle);
					break;
				}
			}
		}
	} while (idx < MAX_NUM_ATTR);

	return STATUS_SUCCESS;
}

INT8 sm_service_add_req_handler(interface_req_elem_t* req)
{
#if (PARANOID_STACK == TRUE)
	if (!req)
		return STATUS_ERR_INVALID_PARAM;
#endif

	switch (req->req_opcode)
	{
	case API_REQ_OPCODE_ADD_SERVICE:
	{
		UINT8 status = STATUS_SUCCESS;
		sm_add_service_param_t* param = (sm_add_service_param_t*)(void*)req->parameter;
		UINT8 app_handle = get_appid_from_transid(param->trans_id);
		logd("Adding service by app_handle : %d trans_id: 0x%04X", app_handle, param->trans_id);

		if (app_handle >= MAX_NUMBER_OF_APP)
		{
			loge("op_code:%u, Invalid app handle:%u !!!",req->req_opcode, app_handle);
			return STATUS_ERR_INVALID_APP_HANDLE;
		}

		app_data_t* app_data = g_local_adapter.app_list[app_handle];
#if (PARANOID_STACK == TRUE)
		if (!app_data)
			return STATUS_ERR_INVALID_APP_HANDLE; //FIXME: possible memory loss here.
#endif
		UINT16 service_handle = 0;
		status = (UINT8)add_service(g_local_adapter.next_free_handle, param->trans_id, &param->uuid,
				param->service_type, param->num_of_incl_srv, param->num_of_char, param->num_of_desc, &service_handle);
		if(status == STATUS_SUCCESS)
			g_local_adapter.next_free_handle = service_handle + 1;

		if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_service_added_cb)
			app_data->app_gatt_cb->iLE_on_service_added_cb(param->trans_id, status, &param->uuid, service_handle);
	}
		break;
	case API_REQ_OPCODE_ADD_INCLUDED_SERVICE:
		{
			UINT8 status = STATUS_SUCCESS;
			sm_add_include_service_param_t* param = (sm_add_include_service_param_t*)(void*)req->parameter;
			UINT8 app_handle = get_appid_from_transid(param->trans_id);

			if (app_handle >= MAX_NUMBER_OF_APP)
			{
				loge("op_code:%u, Invalid app handle:%u !!!",req->req_opcode, app_handle);
				return STATUS_ERR_INVALID_APP_HANDLE;
			}


			app_data_t* app_data = g_local_adapter.app_list[app_handle];
#if (PARANOID_STACK == TRUE)
			if (!app_data)
				return STATUS_ERR_INVALID_APP_HANDLE; //FIXME: possible memory loss here.
	#endif
			UINT16 include_service_handle = 0;
			status = (UINT8)add_include_service(g_local_adapter.next_free_handle, param->trans_id, &param->uuid,
					param->service_type, param->start_handle, param->end_handle, &include_service_handle);
			if(status == STATUS_SUCCESS)
				g_local_adapter.next_free_handle = include_service_handle + 1;

			if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_include_service_added_cb)
				app_data->app_gatt_cb->iLE_on_include_service_added_cb(param->trans_id, status, &param->uuid, include_service_handle);
		}
			break;
	case API_REQ_OPCODE_ADD_CHARACTERISTIC:
	{
		UINT8 status = STATUS_SUCCESS;
		sm_add_characteristic_param_t* param = (sm_add_characteristic_param_t*)(void*)req->parameter;
		UINT8 app_handle = get_appid_from_transid(param->trans_id);

		if (app_handle >= MAX_NUMBER_OF_APP)
		{
			loge("op_code:%u, Invalid app handle:%u !!!",req->req_opcode, app_handle);
			return STATUS_ERR_INVALID_APP_HANDLE;
		}


		app_data_t* app_data = g_local_adapter.app_list[app_handle];
#if (PARANOID_STACK == TRUE)
		if (!app_data)
			return STATUS_ERR_INVALID_APP_HANDLE; //FIXME: possible memory loss here.
#endif
		UINT16 char_handle = 0;
		status = (UINT8)add_char_desc(g_local_adapter.next_free_handle, ATTR_TYPE_CHARACTERISTIC, param->property, param->permission, &param->uuid, &char_handle);
		if(status == STATUS_SUCCESS)
			g_local_adapter.next_free_handle = char_handle + 2;

		if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_characteristic_added_cb)
			app_data->app_gatt_cb->iLE_on_characteristic_added_cb(param->trans_id, status, &param->uuid, char_handle);
	}
		break;
	case API_REQ_OPCODE_ADD_DESCRIPTOR:
	{
		UINT8 status = STATUS_SUCCESS;
		sm_add_descriptor_param_t* param = (sm_add_descriptor_param_t*)(void*)req->parameter;
		UINT8 app_handle = get_appid_from_transid(param->trans_id);

		if (app_handle >= MAX_NUMBER_OF_APP)
		{
			loge("op_code:%u, Invalid app handle:%u !!!",req->req_opcode, app_handle);
			return STATUS_ERR_INVALID_APP_HANDLE;
		}


		app_data_t* app_data = g_local_adapter.app_list[app_handle];
#if (PARANOID_STACK == TRUE)
		if (!app_data)
			return STATUS_ERR_INVALID_APP_HANDLE; //FIXME: possible memory loss here.
#endif
		UINT16 desc_handle = 0;
		status = (UINT8)add_char_desc(g_local_adapter.next_free_handle, ATTR_TYPE_DESCRIPTOR, 0, param->permission, &param->uuid, &desc_handle);
		if(status == STATUS_SUCCESS)
			g_local_adapter.next_free_handle = desc_handle + 1;

		if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_descriptor_added_cb)
			app_data->app_gatt_cb->iLE_on_descriptor_added_cb(param->trans_id, status, &param->uuid, desc_handle);
	}
		break;
	case API_REQ_OPCODE_START_SERVICE:
	{
		sm_start_service_param_t* param = (sm_start_service_param_t*)(void*)req->parameter;
		UINT8 app_handle = get_appid_from_transid(param->trans_id);

		if (app_handle >= MAX_NUMBER_OF_APP)
		{
			loge("op_code:%u, Invalid app handle:%u !!!",req->req_opcode, app_handle);
			return STATUS_ERR_INVALID_APP_HANDLE;
		}


		app_data_t* app_data = g_local_adapter.app_list[app_handle];
#if (PARANOID_STACK == TRUE)
		if (!app_data)
			return STATUS_ERR_INVALID_APP_HANDLE; //FIXME: possible memory loss here.
#endif
		if (g_local_adapter.attribute_list[g_local_adapter.last_attr_idx].attr_handle != g_local_adapter.last_srv_end_handle)
		{
			uuid_t *service_uuid = get_last_added_service_uuid(g_local_adapter.next_free_handle);
			loge("Not all pre-declared attributes have been added to the service. Can't start!");
			if (service_uuid && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_service_started_cb)
				app_data->app_gatt_cb->iLE_on_service_started_cb(param->trans_id, STATUS_ERR_GATT_SVC_ADD_ATTR_INCOMPLETE, service_uuid, 0x00);
			return STATUS_ERR_GATT_SVC_ADD_ATTR_INCOMPLETE;
		}

		UINT16 last_attr_idx = g_local_adapter.last_attr_idx;
		g_local_adapter.last_srv_end_handle = 0;
		g_local_adapter.next_free_handle = 0; /* service is added successfully. */
		sm_dump_att_db();
		for (;last_attr_idx > 0; last_attr_idx --)
		{
			if (g_local_adapter.attribute_list[last_attr_idx].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				if (app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_service_started_cb)
				{
					app_data->app_gatt_cb->iLE_on_service_started_cb(param->trans_id, STATUS_SUCCESS, &g_local_adapter.attribute_list[last_attr_idx].uuid, g_local_adapter.attribute_list[last_attr_idx].attr_handle);
				}
				break;
			}
		}
#if (GAP_GATT_SRV_APP == TRUE)
		/* Inform GATT service about new added service */
		if (g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE] && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb && g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb->iLE_on_service_started_cb)
			g_local_adapter.app_list[GAP_GATT_SRV_APP_HANDLE]->app_gatt_cb->iLE_on_service_started_cb(param->trans_id, STATUS_SUCCESS, &g_local_adapter.attribute_list[last_attr_idx].uuid, g_local_adapter.attribute_list[last_attr_idx].attr_handle);
#endif
	}
		break;
	case API_REQ_OPCODE_REMOVE_SERVICE:
	{
		sm_remove_service_param_t* param = (sm_remove_service_param_t*)(void*)req->parameter;
		logd("param->service_handle:%d", param->service_handle);
		remove_service(param->trans_id, param->service_handle);
	}
		break;
	}
	return STATUS_ERR_UNKNOWN; /* Don't free up in interface. We'll freeup when time comes */
}

void sm_write_attribute(UINT8 conn_id, UINT8 att_opcode, UINT16 att_hdl,  UINT16 offset, buffer_t* buffer)
{
	logi("");
	trans_id_t owner_trans_id = get_owner_trans_id_from_hdl(att_hdl);
	UINT8 app_idx;
	if(owner_trans_id == INVALID_TRANS_ID)
		app_idx = (UINT8)INVALID_INDEX;
	else
	app_idx = get_appid_from_transid(owner_trans_id);

	if ((app_idx < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_idx])
	{
		if (g_local_adapter.app_list[app_idx]->app_gatt_cb)
		{
			if (g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_attribute_write_req_cb)
			{
				g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_attribute_write_req_cb(owner_trans_id, conn_id, att_opcode, att_hdl, offset, buffer);
			}
			else
			{
				logw("No call back registered by app: %d", app_idx);
			}
		}
	}
}

void sm_indication_confirmataion(UINT8 conn_id, UINT16 att_hdl)
{
	logd("");
	trans_id_t owner_trans_id = get_owner_trans_id_from_hdl(att_hdl);
	UINT8 app_idx;
	if(owner_trans_id == INVALID_TRANS_ID)
		app_idx = (UINT8)INVALID_INDEX;
	else
	app_idx = get_appid_from_transid(owner_trans_id);

	if ((app_idx < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_idx])
	{
		if (g_local_adapter.app_list[app_idx]->app_gatt_cb)
		{
			if (g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_indication_confirmation_cb)
			{
				g_local_adapter.app_list[app_idx]->app_gatt_cb->iLE_on_indication_confirmation_cb(owner_trans_id, conn_id, att_hdl);
			}
		}
	}
	sm_dequeue_and_cleanup_from_pending_queue(conn_id);
	sm_req_handler(NULL);
}

INT8 sm_req_handler(interface_req_elem_t* incoming_req)
{
	INT8 req_status = STATUS_ERR_UNKNOWN;
	/* enqueue this request */

	sm_enqueue_req_in_pending_queue(incoming_req);

	interface_req_elem_t* req = get_req_to_process();

	if (!req)
	{
		logd("No pending request in SM wait queue.");
		return STATUS_SUCCESS;
	}

	switch (req->req_opcode)
	{
	case API_REQ_OPCODE_SEND_ATTRIBUTE_READ_RESPONSE:
	{
		sm_send_attribute_read_rsp_param_t* param = (sm_send_attribute_read_rsp_param_t*)(void*)req->parameter;
		req_status = sm_send_attribute_read_rsp(param->conn_id, param->att_opcode, param->att_id, param->status, &param->buffer);

		if (req_status != STATUS_ERR_BUSY)
		{
			sm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_SEND_ATTRIBUTE_WRITE_RESPONSE:
	{
		sm_send_attribute_write_rsp_param_t* param = (sm_send_attribute_write_rsp_param_t*)(void*)req->parameter;
		req_status = sm_send_attribute_write_rsp(param->conn_id, param->att_opcode, param->att_id, param->status, param->offset, &param->buffer);
		if (req_status != STATUS_ERR_BUSY)
		{
			sm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_SEND_NOTIFICATION:
	{
		sm_send_notification_param_t* param = (sm_send_notification_param_t*)(void*)req->parameter;
		req_status = sm_send_nofication(param->conn_id, param->att_id, &param->buffer, param->need_resp);

		if (req_status == STATUS_SUCCESS) /* Notification. */
		{
			BOOLEAN need_resp = param->need_resp;
			sm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
			if (need_resp == FALSE)
			{
				sm_req_handler(NULL);
				logd("return STATUS_PROCESS_ONGOING in need_resp = FALSE");
				return STATUS_PROCESS_ONGOING;
			}
			else
				break;
		}
		if (req_status != STATUS_ERR_BUSY && param->need_resp)
		{
			/* call the callback for the failure */
			UINT8 app_handle = get_appid_from_transid(param->trans_id);
			if (app_handle < MAX_NUMBER_OF_APP)
			{
				app_data_t* app_data = g_local_adapter.app_list[app_handle];
				if (app_data && app_data->app_gatt_cb && app_data->app_gatt_cb->iLE_on_indication_confirmation_cb)
					app_data->app_gatt_cb->iLE_on_indication_confirmation_cb(param->trans_id, param->conn_id, param->att_id);
			}
			sm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	case API_REQ_OPCODE_SET_SERVICE_CHANGE_CONFIG:
	{
		sm_set_service_change_config_param_t* param = (sm_set_service_change_config_param_t*)(void*)req->parameter;
		req_status = sm_set_service_change_config(param->conn_id, param->is_notify);
		if (req_status != STATUS_ERR_BUSY)
		{
			sm_dequeue_and_cleanup_from_pending_queue(param->conn_id);
		}
	}
		break;
	}
	logd("return STATUS_PROCESS_ONGOING");
	return STATUS_PROCESS_ONGOING;
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

void sm_connect_cb(connected_device_t *device)
{
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
	g_local_adapter.sm_device_idx_to_execute = 0;
	init_no_guard_q(&device->sm_device_data.pending_req_q);
	device->sm_device_data.prepared_wr_app_handle = (UINT8)INVALID_INDEX;
}

void sm_disconnect_cb(connected_device_t *device)
{
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
	g_local_adapter.sm_device_idx_to_execute = 0;
#if (GATT_SERVER_SUPPORTED == TRUE)
		sm_dequeue_and_cleanup_from_pending_queue(device->idx);
#endif /* GATT_SERVER_SUPPORTED == TRUE */
		cleanup_q(&device->sm_device_data.pending_req_q); /* FIXME: if there is a pending req. Cleanup all the memory consumed by the request. */
}

INT8 sm_init()
{
	logi("");
	/* Skip the attribute handle 0 */
	g_local_adapter.attribute_list[0].attr_type = ATTR_TYPE_ANY;
	g_local_adapter.last_attr_idx = g_local_adapter.last_srv_end_handle = 0;
	return STATUS_SUCCESS;
}

void sm_cleanup()
{
#if (GATT_SERVER_SUPPORTED == TRUE)
	memset(g_local_adapter.attribute_list, 0, sizeof(g_local_adapter.attribute_list));
	iLE_stack_cleanup();
#endif /* GATT_SERVER_SUPPORTED == TRUE */
}

#if (GATT_SERVER_SUPPORTED == TRUE)

void sm_sign_verify_complete_cb(UINT8 conn_id, UINT8 status)
{
	logi(" Status:%d", status);
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if(!device)
		return;
	if(status == STATUS_SUCCESS)
	{
		gatt_signed_write_execute_cb(conn_id, ATT_OPCODE_SIGN_WRITE_CMD, device->gatt_device_data.saved_buffer);
	}
	dealloc(device->gatt_device_data.saved_buffer);
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */
