/** @file
  Heart Rate Profile (client) implementation.

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
#include "hrp_collector.h"

#define MODULE_DBG_LVL HRP_APP_DBG_LVL
#include "log.h"

#if (HRP_APP == TRUE)

static hrp_col_data_t hrp_col_data;

static inline void signal_req()
{
	osa_semaphore_put(&hrp_col_data.msg_sem);
}

static UINT16 get_last_empty_attr_id(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle + 1; att_id < HRP_PER_DEV_ATTR; att_id ++)
	{
		if (hrp_col_data.attr_db[att_id].attr_type != FALSE)
			return att_id - 1;
	}
	return HRP_PER_DEV_ATTR;
}

static gatt_attribute_t* get_owner_prim_srv(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle; att_id >= 1; att_id --)
	{
		if (hrp_col_data.attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			return &hrp_col_data.attr_db[att_id];
	}
	return NULL;
}

/**
 * This is the exit point for the HRP collector profile for showing the value to
 * UI / console / HCI event.
 */
static void displayHeartRate(UINT8 heart_rate, UINT8 batt_level)
{
#if (TARGET_LINUX == TRUE)
	char heart[] = "\xe2\x99\xa5";
	int i;
	log("\r");
	for (i = 0; i < 15; i++)
		log("%s ", heart);
	log(" HEART RATE: %03d    BATTERY LEVEL: %02d%%  \a", heart_rate,
			batt_level);
	for (i = 0; i < 15; i++)
		log("%s ", heart);
	fflush(stdout);
	USE(heart[0]);
	logln("");
#else
	hrp_data_cb(heart_rate, batt_level);
#endif
}

/******************************************************
 * Callback functions
 ******************************************************/
static void hrp_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
	logi("");
	if (result == TRUE)
	{
		hrp_col_data.app_handle = app_handle;
		logi("app_handle:%d", app_handle);
	}
}

static void hrp_on_primary_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("primary_service start_handle:%u end_handle:%u", start_handle, end_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	if (is_finished == FALSE)
	{
		if (start_handle >= HRP_PER_DEV_ATTR)
			return;
		hrp_col_data.attr_db[start_handle].attr_type = ATTR_TYPE_PRIMARY_SERVICE;
		hrp_col_data.attr_db[start_handle].attr_data.srv_data.end_handle = end_handle;
		memcpy (&hrp_col_data.attr_db[start_handle].uuid, uuid, sizeof (uuid_t));
	}
	else
	{
		UINT16 att_id;
		hrp_col_data.num_of_discover_req = 0;
		for (att_id = 1; att_id < HRP_PER_DEV_ATTR; att_id ++)
		{
			if (hrp_col_data.attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				hrp_col_data.num_of_discover_req ++;
				iLE_discover_characteristic(new_trans_id, conn_id, att_id, hrp_col_data.attr_db[att_id].attr_data.srv_data.end_handle, NULL);
			}
		}
	}
}

static void hrp_on_characteristic_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("\t characteristic handle:%u value_handle:%u", att_handle, value_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	if (is_finished == FALSE)
	{
		if ((att_handle >= HRP_PER_DEV_ATTR) || (value_handle >= HRP_PER_DEV_ATTR))
			return;
		hrp_col_data.attr_db[att_handle].attr_type = ATTR_TYPE_CHARACTERISTIC;
		hrp_col_data.attr_db[att_handle].attr_data.char_desc_data.property = property;
		memcpy (&hrp_col_data.attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
		hrp_col_data.attr_db[value_handle].attr_type = ATTR_TYPE_CHARACTERISTIC_VALUE;
	}
	else if (hrp_col_data.num_of_discover_req)
	{
		hrp_col_data.num_of_discover_req --;
		if (!hrp_col_data.num_of_discover_req)
		{
			UINT16 start_id;
			for (start_id = 1; start_id < HRP_PER_DEV_ATTR; start_id ++)
			{
				if (hrp_col_data.attr_db[start_id].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE && start_id < (HRP_PER_DEV_ATTR - 1) && hrp_col_data.attr_db[start_id + 1].attr_type == FALSE)
				{
					UINT16 end_handle = get_last_empty_attr_id(conn_id, start_id);
					if (end_handle == HRP_PER_DEV_ATTR)
					{
						gatt_attribute_t *srv = get_owner_prim_srv(conn_id, start_id);
						if (srv)
						{
							end_handle = srv->attr_data.srv_data.end_handle;
						}
					}
					logi("start_id:%u end_handle:%u", start_id, end_handle);
					logi("iLE_discover_descriptor start:%u end:%u", start_id + 1, end_handle);
					hrp_col_data.num_of_discover_req ++;
					iLE_discover_descriptor(new_trans_id, conn_id, start_id + 1, end_handle);
				}
			}
		}
	}

}

static void hrp_on_descriptor_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	logi("\t\t descriptor handle:%u", att_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	if (is_finished == FALSE)
	{
		if (att_handle >= HRP_PER_DEV_ATTR)
			return;
		hrp_col_data.attr_db[att_handle].attr_type = ATTR_TYPE_DESCRIPTOR;
		memcpy (&hrp_col_data.attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
	}
	else
	{
		hrp_col_data.num_of_discover_req --;
		if (!hrp_col_data.num_of_discover_req)
		{
			if (COMPARE_UUID ((&hrp_col_data.current_uuid_being_discovered), (&hrp_col_data.heart_rate_monitor_service_uuid)))
			{
				hrp_col_data.current_uuid_being_discovered = hrp_col_data.battery_service_uuid;
				iLE_discover_primary_service(new_trans_id, hrp_col_data.conn_id, &hrp_col_data.battery_service_uuid);
			}
			else
			{
				hrp_req_elem_t *res_code = (hrp_req_elem_t*) alloc_queue_element(sizeof(hrp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
				if (!res_code)
					return;
#endif
				res_code->opcode = HRP_RES_SERVICE_DISCOVERED;
				enqueue(&hrp_col_data.hrp_res_q, res_code);
				signal_req();
			}
		}
	}
}

static void hrp_on_notification_cb (trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN is_indication)
{
	hrp_req_elem_t *res_code = (hrp_req_elem_t*) alloc_queue_element(sizeof(hrp_req_elem_t), APP_ALLOC);
	UINT8 *data;
#if (PARANOID_STACK == TRUE)
	if (res_code == NULL )
		return;
#endif
	res_code->opcode = HRP_RES_NOTIFICATION;
	data = buffer->data + buffer->offset;
	JUMP_CUSTOM_LEN(data, 1);
	STREAM_TO_UINT8(hrp_col_data.heart_rate, data);
	enqueue(&hrp_col_data.hrp_res_q, res_code);
	signal_req();
}

static void hrp_on_attribute_read_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t *buffer)
{
	UINT8 batt_level;
	UINT8 *data;
	logi("");
	if (status == ATT_SUCCESS)
	{
		data = buffer->data + buffer->offset;
		STREAM_TO_UINT8(batt_level, data);
		displayHeartRate(hrp_col_data.heart_rate, batt_level);
		hrp_col_data.is_hrp_read_req_pending = FALSE;
	}
}


static void hrp_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote, UINT8 *id_addr, UINT8 id_addr_type)
{
	if (memcmp(remote_bd_addr, hrp_col_data.remote_bd_addr, BD_ADDR_LEN)
			== 0 && result == STATUS_SUCCESS)
	{
		hrp_col_data.is_hrp_read_req_pending = FALSE;
		hrp_col_data.conn_id = conn_id;
		hrp_req_elem_t *res_code = (hrp_req_elem_t*) alloc_queue_element(sizeof(hrp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (res_code == NULL )
			return;
#endif
		res_code->opcode = HRP_RES_DEVICE_CONNECTED;
		enqueue(&hrp_col_data.hrp_res_q, res_code);
		signal_req();
	}
}

static void hrp_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
	logi("");
	hrp_col_data.hrp_is_connected = FALSE;
	hrp_col_data.is_hrp_read_req_pending = FALSE;
	memset(hrp_col_data.remote_bd_addr, 0, BD_ADDR_LEN);
	if (hrp_col_data.hrp_app_closing)
	{
		iLE_deregister_application(hrp_col_data.app_handle);
		cleanup_q(&hrp_col_data.hrp_res_q);
		hrp_col_data.hrp_app_running = FALSE;
		signal_req();
		osa_semaphore_get(&hrp_col_data.thread_sem);
		osa_semaphore_delete(&hrp_col_data.thread_sem);
		osa_thread_join(HRP_THREAD, NULL);
	}
}

static void hrp_scan_result_cb(trans_id_t trans_id, discovered_device_t *device)
{
	char bdaddr_str[BD_ADDR_STR_LEN];
	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
	logi("Found Device %s %s", bdaddr_str, device->localname);

	memcpy(&hrp_col_data.discovered_list[hrp_col_data.num_discovered_devices], device, sizeof(discovered_device_t));
	if (device->adv_data && device->adv_data_len)
	{
		hrp_col_data.discovered_list[hrp_col_data.num_discovered_devices].adv_data = (UINT8*) app_alloc(device->adv_data_len);
#if (PARANOID_STACK == TRUE)
		if (!hrp_col_data.discovered_list[hrp_col_data.num_discovered_devices].adv_data)
			return;
#endif
		memcpy(hrp_col_data.discovered_list[hrp_col_data.num_discovered_devices].adv_data, device->adv_data, device->adv_data_len);
	}
	hrp_col_data.num_discovered_devices++;
}

static void hrp_scan_completed_cb(trans_id_t trans_id)
{
	hrp_req_elem_t *res_code = (hrp_req_elem_t*) alloc_queue_element(sizeof(hrp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (res_code == NULL )
		return;
#endif
	res_code->opcode = HRP_RES_SCAN_COMPLETED;
	enqueue(&hrp_col_data.hrp_res_q, res_code);
	signal_req();
}

static gatt_callbacks_t hrp_gatt_cb =
{
	.iLE_on_primary_service_discovered_cb = hrp_on_primary_service_discovered_cb,
	.iLE_on_characteristic_discovered_cb = hrp_on_characteristic_discovered_cb,
	.iLE_on_descriptor_discovered_cb = hrp_on_descriptor_discovered_cb,
	.iLE_on_attribute_read_cb = hrp_on_attribute_read_cb,
	.iLE_on_notification_cb = hrp_on_notification_cb,
};

static device_control_callbacks_t hrp_dev_cb =
{
	.iLE_scan_result_cb = hrp_scan_result_cb,
	.iLE_scan_completed_cb = hrp_scan_completed_cb,
	.iLE_on_connected_cb = hrp_on_connected_cb,
	.iLE_on_disconnected_cb = hrp_on_disconnected_cb,
};

void hrp_start_discovery (UINT8 *arg)
{
	UINT8 idx;
	trans_id_t new_trans_id = 0;
		add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	for (idx = 0; idx < hrp_col_data.num_discovered_devices; idx++)
		app_dealloc(hrp_col_data.discovered_list[idx].adv_data);
	hrp_col_data.num_discovered_devices = 0;

	iLE_start_scan(new_trans_id, HRP_SCAN_TIMEOUT_SEC, TRUE, FALSE, FALSE, FALSE, 0, NULL);
}

/**
 * This entry will enter a state machine which does the following:
 * 1. Connect to a HRP device (as specified in the bdaddr / console input
 * 2. Discover HRP service and Battery level service (If any one of these are
 * 		not present in the remote the procedure fails.
 * 3. Read the client characteristic configuration for the heart rate measurement
 * 		characteristic.
 * 4. Write the descriptor to enable notification to get the heart rate.
 * 5. Continuously read the battery level of the remote device using the battery level service.
 */
void hrp_start_use_case (UINT8 *bdaddr)
{
	UINT8 idx, type = 0;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	char bdaddr_str[BD_ADDR_STR_LEN];
	if (bdaddr)
	{
		for (idx = 0; idx < hrp_col_data.num_discovered_devices; idx++)
		{
			if (!memcmp(hrp_col_data.discovered_list[idx].bdaddr, bdaddr, BD_ADDR_LEN))
			{
				type = hrp_col_data.discovered_list[idx].addr_type;
				break;
			}
		}
		iLE_connect(new_trans_id, bdaddr, type);
		memcpy(hrp_col_data.remote_bd_addr, bdaddr, BD_ADDR_LEN);
		return;
	}
	if (!hrp_col_data.num_discovered_devices)
	{
		loge("First do hrp_start_discovery operation.");
		return;
	}
	for (idx = 0; idx < hrp_col_data.num_discovered_devices; idx++)
	{
		BDADDR_TO_STRING(bdaddr_str, hrp_col_data.discovered_list[idx].bdaddr);
		logln("Device %d> %s - %s", idx, bdaddr_str, hrp_col_data.discovered_list[idx].localname);
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
	if (index < hrp_col_data.num_discovered_devices)
	{
		memcpy(hrp_col_data.remote_bd_addr, hrp_col_data.discovered_list[index].bdaddr, BD_ADDR_LEN);
		iLE_connect(new_trans_id, hrp_col_data.discovered_list[index].bdaddr, hrp_col_data.discovered_list[index].addr_type);
	}
}

/**
 * Stops the use case by only disconnecting the remote device.
 */
void hrp_stop_use_case (UINT8 *bdaddr)
{
	trans_id_t trans_id = 0;
	add_appid_to_trans_id(&trans_id, hrp_col_data.app_handle);
	if (hrp_col_data.hrp_is_connected == FALSE)
		hrp_on_disconnected_cb(trans_id, hrp_col_data.conn_id, 0x00);
	else
		iLE_disconnect(trans_id, hrp_col_data.conn_id, 0x13);
}

static const cmd_t hrp_cmd_arr[] = {
{ "start_discovery", hrp_start_discovery },
{ "start_use_case", hrp_start_use_case },
{ "stop_use_case", hrp_stop_use_case },
{ "_end_", NULL },
};


static void send_device_discovered_result()
{
#if (TARGET_THREADX == TRUE)
	UINT8 idx;
	UINT8 *disc_dev_list[MAX_NUM_DISCOVERED_DEVICE];

	for (idx=0; idx< hrp_col_data.num_discovered_devices; idx++)
		disc_dev_list[idx] = hrp_col_data.discovered_list[idx].bdaddr;
	profile_device_discovery_completed(TRUE, HRP_CLIENT_USE_CASE, disc_dev_list, hrp_col_data.num_discovered_devices);
#endif
}

static osa_thread_ret_t hrp_app_main_thread(osa_thread_arg_t arg)
{
	osa_semaphore_create(&hrp_col_data.msg_sem, 0);
	osa_semaphore_put(&hrp_col_data.thread_sem);
	while (hrp_col_data.hrp_app_running == TRUE)
	{
		hrp_req_elem_t* res_elem = (hrp_req_elem_t*) dequeue(
				&hrp_col_data.hrp_res_q);
		if (res_elem == NULL )
		{
			osa_semaphore_get(&hrp_col_data.msg_sem);
			continue;
		}
		UINT8 opcode = res_elem->opcode;
		switch (opcode)
		{
		case HRP_RES_SCAN_COMPLETED:
		{
			logd("HRP_RES_SCAN_COMPLETED");
			send_device_discovered_result();
		}
			break;
		case HRP_RES_DEVICE_CONNECTED:
		{
			logd("HRP_RES_DEVICE_CONNECTED");
			hrp_col_data.hrp_is_connected = TRUE;

			hrp_col_data.current_uuid_being_discovered = hrp_col_data.heart_rate_monitor_service_uuid;
			iLE_discover_primary_service(hrp_col_data.app_handle, hrp_col_data.conn_id, &hrp_col_data.heart_rate_monitor_service_uuid);
		}
			break;
		case HRP_RES_SERVICE_DISCOVERED:
		{
			logd("HRP_RES_SERVICE_DISCOVERED");
			//Enable notification of heart rate
			UINT16 idx, didx;
			for (idx = 1; idx < HRP_PER_DEV_ATTR; idx++)
			{
				gatt_attribute_t attribute = hrp_col_data.attr_db[idx];
				if (attribute.attr_type == ATTR_TYPE_CHARACTERISTIC && attribute.uuid.value.uuid16 == HEART_RATE_MEASUREMENT_CHAR_UUID)
				{
					iLE_register_notification(hrp_col_data.app_handle, hrp_col_data.conn_id, idx+1, TRUE);
					for (didx = idx; didx < HRP_PER_DEV_ATTR; didx++)
					{
						attribute = hrp_col_data.attr_db[didx];
						if (attribute.attr_type == ATTR_TYPE_DESCRIPTOR && attribute.uuid.value.uuid16 == CHARACTERISTIC_CONFIG_DESC_UUID)
						{
							UINT16 value = 0x0001;
							buffer_t *buffer = (buffer_t*) app_alloc (sizeof(UINT16) + sizeof (buffer_t));
#if (PARANOID_STACK == TRUE)
							if (!buffer)
								break;
#endif
							buffer->offset = 0;
							buffer->length = sizeof(UINT16);
							memcpy(buffer->data, &value, sizeof(UINT16));
							iLE_write_attribute_value(hrp_col_data.app_handle, hrp_col_data.conn_id, ATT_OPCODE_WRITE_REQ, didx, 0, buffer);
							app_dealloc(buffer);
							break;
						}
					}
					break;
				}
			}
		}
			break;
		case HRP_RES_NOTIFICATION:
		{
			logd("HRP_RES_NOTIFICATION");
			if (hrp_col_data.is_hrp_read_req_pending == FALSE)
			{
				//Read battery level value
				UINT16 idx;
				for (idx = 1; idx < HRP_PER_DEV_ATTR; idx++)
				{
					gatt_attribute_t attribute = hrp_col_data.attr_db[idx];
					if (attribute.attr_type == ATTR_TYPE_CHARACTERISTIC && attribute.uuid.value.uuid16 == BATTERY_LEVEL_CHAR_UUID)
					{
						gatt_attribute_read_param_t read_param;
						read_param.att_opcode = ATT_OPCODE_READ_REQ;
						read_param.attr_read_param.read_attr.att_id = idx+1;
						read_param.attr_read_param.read_attr.offset = 0;
						iLE_read_attribute_value(hrp_col_data.app_handle, hrp_col_data.conn_id, &read_param);
						hrp_col_data.is_hrp_read_req_pending = TRUE;
						break;
					}
				}
			}
		}
			break;
		default:
			break;
		}
		dealloc_queue_element(res_elem);
	}
	osa_semaphore_delete(&hrp_col_data.msg_sem);
	osa_semaphore_put(&hrp_col_data.thread_sem);
	osa_thread_exit(NULL);
}

void hrp_init()
{
	/* Register HRP application. */
	iLE_register_application(&hrp_dev_cb, &hrp_gatt_cb, "hrp", hrp_cmd_arr, hrp_register_application_cb);
	init_q(&hrp_col_data.hrp_res_q);
	hrp_col_data.hrp_app_running = TRUE;
	hrp_col_data.hrp_app_closing = FALSE;
	hrp_col_data.hrp_is_connected = FALSE;
	UINT16_TO_UUID (HEART_RATE_MONITOR_SERVICE_UUID, hrp_col_data.heart_rate_monitor_service_uuid);
	UINT16_TO_UUID (BATTERY_SERVICE_UUID, hrp_col_data.battery_service_uuid);
	osa_semaphore_create(&hrp_col_data.thread_sem, 0);

	osa_thread_create(HRP_THREAD, hrp_app_main_thread, PROFILE_THREAD_PRIORITY);

	osa_semaphore_get(&hrp_col_data.thread_sem);
}
void hrp_cleanup()
{
	logi("");
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hrp_col_data.app_handle);
	for (idx = 0; idx < hrp_col_data.num_discovered_devices; idx++)
		app_dealloc(hrp_col_data.discovered_list[idx].adv_data);
	hrp_col_data.num_discovered_devices = 0;
	hrp_col_data.hrp_app_closing = TRUE;
	if (hrp_col_data.hrp_is_connected == FALSE)
		hrp_on_disconnected_cb(new_trans_id, hrp_col_data.conn_id, 0x00);
	else
		iLE_disconnect(hrp_col_data.app_handle, hrp_col_data.conn_id, 0x13);
}

#endif
