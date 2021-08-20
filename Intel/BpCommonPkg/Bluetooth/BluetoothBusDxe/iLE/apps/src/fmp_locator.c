/** @file
  Find Me Locator (client) implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <stdlib.h>
#include "app_interface.h"
#include "profile_adapt.h"
#include "fmp_locator.h"

#define MODULE_DBG_LVL FMP_APP_DBG_LVL
#include "log.h"

#if (FMP_APP == TRUE)

static fmp_loc_data_t fmp_loc_data;

static inline void signal_req()
{
	osa_semaphore_put(&fmp_loc_data.msg_sem);
}

static UINT16 get_last_empty_attr_id(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle + 1; att_id < FMP_PER_DEV_ATTR; att_id ++)
	{
		if (fmp_loc_data.attr_db[att_id].attr_type != FALSE)
			return att_id - 1;
	}
	return FMP_PER_DEV_ATTR;
}

static gatt_attribute_t* get_owner_prim_srv(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle; att_id >= 1; att_id --)
	{
		if (fmp_loc_data.attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			return &fmp_loc_data.attr_db[att_id];
	}
	return NULL;
}

/******************************************************
 * Callback functions
 ******************************************************/
static void fmp_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
	logi("");
	if (result == TRUE)
	{
		fmp_loc_data.app_handle = app_handle;
		logi("app_handle:%d", app_handle);
	}
}

/**
 * Callback to be called when remote service discovery is completed.
 */
static void fmp_on_primary_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("primary_service start_handle:%u end_handle:%u", start_handle, end_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	if (start_handle >= FMP_PER_DEV_ATTR)
		return;
	if (is_finished == FALSE)
	{
		fmp_loc_data.attr_db[start_handle].attr_type = ATTR_TYPE_PRIMARY_SERVICE;
		fmp_loc_data.attr_db[start_handle].attr_data.srv_data.end_handle = end_handle;
		memcpy (&fmp_loc_data.attr_db[start_handle].uuid, uuid, sizeof (uuid_t));
	}
	else
	{
		UINT16 att_id;
		fmp_loc_data.num_of_discover_req = 0;
		for (att_id = 1; att_id < FMP_PER_DEV_ATTR; att_id ++)
		{
			if (fmp_loc_data.attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				fmp_loc_data.num_of_discover_req ++;
				iLE_discover_characteristic(new_trans_id, conn_id, att_id, fmp_loc_data.attr_db[att_id].attr_data.srv_data.end_handle, NULL);
			}
		}
	}
}

static void fmp_on_characteristic_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("\t characteristic handle:%u value_handle:%u", att_handle, value_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	if (is_finished == FALSE)
	{
		if ((att_handle >= FMP_PER_DEV_ATTR) || (value_handle >= FMP_PER_DEV_ATTR))
			return;
		fmp_loc_data.attr_db[att_handle].attr_type = ATTR_TYPE_CHARACTERISTIC;
		fmp_loc_data.attr_db[att_handle].attr_data.char_desc_data.property = property;
		memcpy (&fmp_loc_data.attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
		fmp_loc_data.attr_db[value_handle].attr_type = ATTR_TYPE_CHARACTERISTIC_VALUE;
	}
	else if (fmp_loc_data.num_of_discover_req)
	{
		fmp_loc_data.num_of_discover_req --;
		if (!fmp_loc_data.num_of_discover_req)
		{
			UINT16 start_id;
			for (start_id = 1; start_id < FMP_PER_DEV_ATTR - 1; start_id ++)
			{
				if (fmp_loc_data.attr_db[start_id].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE &&
						fmp_loc_data.attr_db[start_id + 1].attr_type == FALSE)
				{
					UINT16 end_handle = get_last_empty_attr_id(conn_id, start_id);
					if (end_handle == FMP_PER_DEV_ATTR)
					{
						gatt_attribute_t *srv = get_owner_prim_srv(conn_id, start_id);
						if (srv)
						{
							end_handle = srv->attr_data.srv_data.end_handle;
						}
					}
					logi("start_id:%u end_handle:%u", start_id, end_handle);
					logi("iLE_discover_descriptor start:%u end:%u", start_id + 1, end_handle);
					fmp_loc_data.num_of_discover_req ++;
					iLE_discover_descriptor(new_trans_id, conn_id, start_id + 1, end_handle);
				}
			}
		}
	}
}

static void fmp_on_descriptor_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("\t\t descriptor handle:%u", att_handle);
	if (is_finished == FALSE)
	{
		if (att_handle >= FMP_PER_DEV_ATTR)
			return;
		fmp_loc_data.attr_db[att_handle].attr_type = ATTR_TYPE_DESCRIPTOR;
		memcpy (&fmp_loc_data.attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
	}
	else
	{
		fmp_loc_data.num_of_discover_req --;
		if (!fmp_loc_data.num_of_discover_req)
		{
			fmp_req_elem_t *res_code = (fmp_req_elem_t*)alloc_queue_element(sizeof(fmp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
			if (!res_code)
				return;
#endif
			res_code->opcode = FMP_RES_SERVICE_DISCOVERED;
			enqueue(&fmp_loc_data.fmp_res_q, res_code);
			signal_req();
		}
	}
}

/**
 * Callback is called when a remote device is connected. (we are master device)
 */

static void fmp_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote, UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
{
	if (from_remote)
		return;

	if (memcmp(remote_bd_addr, fmp_loc_data.remote_bd_addr, BD_ADDR_LEN)
			== 0 && result == STATUS_SUCCESS)
	{
		fmp_loc_data.conn_id = conn_id;
		fmp_req_elem_t *res_code = (fmp_req_elem_t*) alloc_queue_element(sizeof(fmp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (res_code == NULL )
			return;
#endif
		res_code->opcode = FMP_RES_DEVICE_CONNECTED;
		enqueue(&fmp_loc_data.fmp_res_q, res_code);
		signal_req();
	}
}

/**
 * Callback is called when a device is disconnected.
 */
static void fmp_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
	logi("");
	fmp_loc_data.is_connected = FALSE;
	memset(fmp_loc_data.remote_bd_addr, 0, BD_ADDR_LEN);
	if (fmp_loc_data.app_closing)
	{
		iLE_deregister_application(fmp_loc_data.app_handle);
		cleanup_q(&fmp_loc_data.fmp_res_q);
		fmp_loc_data.app_running = FALSE;
		signal_req();
		osa_semaphore_get(&fmp_loc_data.thread_sem);
		osa_semaphore_delete(&fmp_loc_data.thread_sem);
		osa_thread_join(FMP_THREAD, NULL);
	}
}

/**
 * Callback is called when scan results come to the application
 */
static void fmp_scan_result_cb(trans_id_t trans_id, discovered_device_t *device)
{
	char bdaddr_str[BD_ADDR_STR_LEN];
	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
	logi("Found Device %s %s", bdaddr_str, device->localname);

	memcpy(&fmp_loc_data.discovered_list[fmp_loc_data.num_discovered_devices], device, sizeof(discovered_device_t));
	if (device->adv_data && device->adv_data_len)
	{
		fmp_loc_data.discovered_list[fmp_loc_data.num_discovered_devices].adv_data = (UINT8*) app_alloc(device->adv_data_len);
#if (PARANOID_STACK == TRUE)
		if (!fmp_loc_data.discovered_list[fmp_loc_data.num_discovered_devices].adv_data)
			return;
#endif
		memcpy(fmp_loc_data.discovered_list[fmp_loc_data.num_discovered_devices].adv_data, device->adv_data, device->adv_data_len);
	}
	fmp_loc_data.num_discovered_devices++;
}

static void fmp_scan_completed_cb(trans_id_t trans_id)
{
	fmp_req_elem_t *res_code = (fmp_req_elem_t*) alloc_queue_element(sizeof(fmp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (res_code == NULL )
		return;
#endif
	res_code->opcode = FMP_RES_SCAN_COMPLETED;
	enqueue(&fmp_loc_data.fmp_res_q, res_code);
	signal_req();
}

static gatt_callbacks_t fmp_gatt_cb =
{
	.iLE_on_primary_service_discovered_cb = fmp_on_primary_service_discovered_cb,
	.iLE_on_characteristic_discovered_cb = fmp_on_characteristic_discovered_cb,
	.iLE_on_descriptor_discovered_cb = fmp_on_descriptor_discovered_cb,
};

device_control_callbacks_t fmp_dev_cb =
{
	.iLE_scan_result_cb = fmp_scan_result_cb,
	.iLE_scan_completed_cb = fmp_scan_completed_cb,
	.iLE_on_connected_cb		= fmp_on_connected_cb,
	.iLE_on_disconnected_cb			= fmp_on_disconnected_cb,
};

void fmp_start_discovery (UINT8 *arg)
{
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	for (idx = 0; idx < fmp_loc_data.num_discovered_devices; idx++)
		app_dealloc(fmp_loc_data.discovered_list[idx].adv_data);
	fmp_loc_data.num_discovered_devices = 0;

	iLE_start_scan(new_trans_id, FMP_SCAN_TIMEOUT_SEC, TRUE, FALSE, FALSE, FALSE, 0, NULL);
}

/**
 * This starts the use case with connection and then writing alert level to the
 * remote device specified in the argument.
 */
void fmp_start_use_case (UINT8 *bdaddr)
{
	UINT8 idx, type = 0;
	char bdaddr_str[BD_ADDR_STR_LEN];
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	if (bdaddr)
	{
		for (idx = 0; idx < fmp_loc_data.num_discovered_devices; idx++)
		{
			if (!memcmp(fmp_loc_data.discovered_list[idx].bdaddr, bdaddr, BD_ADDR_LEN))
			{
				type = fmp_loc_data.discovered_list[idx].addr_type;
				break;
			}
		}
		iLE_connect(new_trans_id, bdaddr, type);
		memcpy(fmp_loc_data.remote_bd_addr, bdaddr, BD_ADDR_LEN);
		return;
	}
	if (!fmp_loc_data.num_discovered_devices)
	{
		loge("First do fmp_start_discovery operation.");
		return;
	}
	for (idx = 0; idx < fmp_loc_data.num_discovered_devices; idx++)
	{
		BDADDR_TO_STRING(bdaddr_str, fmp_loc_data.discovered_list[idx].bdaddr);
		logln("Device %d> %s - %s", idx, bdaddr_str, fmp_loc_data.discovered_list[idx].localname);
	}
#if (TARGET_LINUX == TRUE)
	char *ret;
	char cmd[5];
	log("Enter index:");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	UINT8 index = (UINT8) atoi(cmd);
#else
	UINT8 index = 0;
#endif
	if (index < fmp_loc_data.num_discovered_devices)
	{
		memcpy(fmp_loc_data.remote_bd_addr, fmp_loc_data.discovered_list[index].bdaddr, BD_ADDR_LEN);
		iLE_connect(new_trans_id, fmp_loc_data.discovered_list[index].bdaddr, fmp_loc_data.discovered_list[index].addr_type);
	}
}

/**
 * Function is to be called when we want to send alert level to the remote device.
 * Prior to this function it is expected that the device is connected and services
 * are discovered.
 */

void fmp_write_alert_level(UINT8* arg)
{
	if (!fmp_loc_data.is_connected)
	{
		loge("Please connect to FMP device first!");
		return;
	}

	UINT8 idx, alert_level = 0;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);

	if (arg)
		alert_level = *arg;

#if (TARGET_LINUX == TRUE)
	char *ret;
	char cmd[5];
	log("Enter alert level:");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	alert_level = (UINT8) atoi(cmd);
#endif

	for (idx = 1; idx < FMP_PER_DEV_ATTR; idx++)
	{
		gatt_attribute_t attribute = fmp_loc_data.attr_db[idx];
		if (attribute.attr_type == ATTR_TYPE_CHARACTERISTIC && attribute.uuid.value.uuid16 == ALERT_LEVEL_UUID)
		{
			UINT8 gatt_write_type = IS_ATTRIBUTE_PROPERTY_WRITE (attribute.attr_data.char_desc_data.property) ? ATT_OPCODE_WRITE_REQ : ATT_OPCODE_WRITE_CMD;
			buffer_t *buffer = (buffer_t*) app_alloc (sizeof(UINT8) + sizeof (buffer_t));
#if (PARANOID_STACK == TRUE)
			if( !buffer)
				return;
#endif
			buffer->offset = 0;
			buffer->length = sizeof(UINT8);
			memcpy(buffer->data, &alert_level, sizeof(UINT8));
			iLE_write_attribute_value(new_trans_id, fmp_loc_data.conn_id, gatt_write_type, idx+1, 0, buffer);
			app_dealloc(buffer);
			break;
		}
	}
}

void fmp_stop_use_case (UINT8 *arg)
{
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	if (fmp_loc_data.is_connected == FALSE)
		fmp_on_disconnected_cb(new_trans_id, fmp_loc_data.conn_id, 0x00);
	else
	iLE_disconnect(new_trans_id, fmp_loc_data.conn_id, 0x13);
}

static const cmd_t fmp_cmd_arr[] = {
{ "start_discovery", fmp_start_discovery },
{ "start_use_case", fmp_start_use_case },
{ "write_alert_level", fmp_write_alert_level },
{ "stop_use_case", fmp_stop_use_case },
{ "_end_", NULL },
};


static void send_device_discovered_result()
{
#if (TARGET_THREADX == TRUE)
		UINT8 idx;
		UINT8 *disc_dev_list[MAX_NUM_DISCOVERED_DEVICE];

		for (idx=0; idx< fmp_loc_data.num_discovered_devices; idx++)
			disc_dev_list[idx] = fmp_loc_data.discovered_list[idx].bdaddr;
		profile_device_discovery_completed(TRUE, FMP_CLIENT_USE_CASE, disc_dev_list, fmp_loc_data.num_discovered_devices);
#endif
}

static osa_thread_ret_t fmp_app_main_thread(osa_thread_arg_t arg)
{
	osa_semaphore_create(&fmp_loc_data.msg_sem, 0);
	osa_semaphore_put(&fmp_loc_data.thread_sem);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	while (fmp_loc_data.app_running == TRUE)
	{
		fmp_req_elem_t* res_elem = (fmp_req_elem_t*) dequeue(
				&fmp_loc_data.fmp_res_q);
		if (res_elem == NULL )
		{
			osa_semaphore_get(&fmp_loc_data.msg_sem);
			continue;
		}
		UINT8 opcode = res_elem->opcode;
		switch (opcode)
		{
		case FMP_RES_SCAN_COMPLETED:
		{
			logd("FMP_RES_SCAN_COMPLETED");
			send_device_discovered_result();
		}
			break;
		case FMP_RES_DEVICE_CONNECTED:
		{
			logd("FMP_RES_DEVICE_CONNECTED");
			fmp_loc_data.is_connected = TRUE;
			iLE_discover_primary_service(new_trans_id, fmp_loc_data.conn_id, &fmp_loc_data.immediate_alert_uuid);
		}
			break;
		case FMP_RES_SERVICE_DISCOVERED:
		{
			logd("FMP_RES_SERVICE_DISCOVERED");
		}
			break;
		default:
			break;
		}
		dealloc_queue_element(res_elem);
	}
	osa_semaphore_delete(&fmp_loc_data.msg_sem);
	osa_semaphore_put(&fmp_loc_data.thread_sem);
	osa_thread_exit(NULL);
}

void fmp_init()
{
	/* Register FMP application. */
	iLE_register_application(&fmp_dev_cb, &fmp_gatt_cb, "fmp", fmp_cmd_arr, fmp_register_application_cb);
	init_q(&fmp_loc_data.fmp_res_q);
	fmp_loc_data.app_running = TRUE;
	fmp_loc_data.is_connected = FALSE;
	fmp_loc_data.app_closing = FALSE;
	UINT16_TO_UUID (IMMEDIATE_ALERT_UUID, fmp_loc_data.immediate_alert_uuid);
	osa_semaphore_create(&fmp_loc_data.thread_sem, 0);

	osa_thread_create(FMP_THREAD, fmp_app_main_thread, PROFILE_THREAD_PRIORITY);

	osa_semaphore_get(&fmp_loc_data.thread_sem);
}

void fmp_cleanup()
{
	logi("");
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_loc_data.app_handle);
	for (idx = 0; idx < fmp_loc_data.num_discovered_devices; idx++)
		app_dealloc(fmp_loc_data.discovered_list[idx].adv_data);
	fmp_loc_data.num_discovered_devices = 0;
	fmp_loc_data.app_closing = TRUE;
	if (fmp_loc_data.is_connected == FALSE)
		fmp_on_disconnected_cb(new_trans_id, fmp_loc_data.conn_id, 0x00);
	else
		iLE_disconnect(new_trans_id, fmp_loc_data.conn_id, 0x13);
}

#endif
