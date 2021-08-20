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

#include "app_interface.h"
#include "profile_adapt.h"
#include "hogp_host.h"
#include "uhid_host.h"

#if (TARGET_LINUX == TRUE)
#include <stdlib.h>
#endif

#define MODULE_DBG_LVL HOGP_APP_DBG_LVL
#include "log.h"

#if (HOGP_APP == TRUE)

static hogp_host_data_t hogp_host_data;
static UINT8 invalid_bd_addr[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

static inline void signal_req()
{
	osa_semaphore_put(&hogp_host_data.msg_sem);
}

static void display_discovered_device_list()
{
	UINT8 idx = 0;
	char bdaddr_str[BD_ADDR_STR_LEN];
	if (!hogp_host_data.discovered_list)
		return;
	log("LIST OF DISCOVERED DEVICES...\n");
	for (idx = 0; idx < hogp_host_data.num_discovered_devices; idx++)
	{
		BDADDR_TO_STRING(bdaddr_str, hogp_host_data.discovered_list[idx].bdaddr);
		log("%u -> %s - %s\n", idx, bdaddr_str, hogp_host_data.discovered_list[idx].localname);
	}
}

static UINT16 get_last_empty_attr_id(UINT8 dev_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle + 1; att_id < HOGP_PER_DEV_ATTR; att_id ++)
		if (hogp_host_data.device_list[dev_id].attr_db[att_id].attr_type != FALSE)
			return att_id - 1;
	return HOGP_PER_DEV_ATTR;
}

static gatt_attribute_t* get_owner_prim_srv(UINT8 dev_id, UINT16 att_handle)
{
	UINT16 att_id;
	if (att_handle >= HOGP_PER_DEV_ATTR)
		return NULL;
	for (att_id = att_handle; att_id >= 1; att_id --)
	{
		if (hogp_host_data.device_list[dev_id].attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			return &hogp_host_data.device_list[dev_id].attr_db[att_id];
	}
	return NULL;
}

static gatt_attribute_t* get_owner_characteristic(UINT8 dev_id, UINT16 att_handle)
{
	UINT16 att_id;
	if (att_handle >= HOGP_PER_DEV_ATTR)
		return NULL;
	for (att_id = att_handle; att_id >= 1; att_id --)
	{
		if (hogp_host_data.device_list[dev_id].attr_db[att_id].attr_type == ATTR_TYPE_CHARACTERISTIC)
			return &hogp_host_data.device_list[dev_id].attr_db[att_id];
	}
	return NULL;
}

static UINT16 get_ccd_hdl_from_char(UINT8 dev_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle; att_id < HOGP_PER_DEV_ATTR; att_id++)
		if (hogp_host_data.device_list[dev_id].attr_db[att_id].attr_type == ATTR_TYPE_DESCRIPTOR && hogp_host_data.device_list[dev_id].attr_db[att_id].uuid.value.uuid16 == CHARACTERISTIC_CONFIG_DESC_UUID)
			return hogp_host_data.device_list[dev_id].attr_db[att_id].attr_handle;
	return 0;
}

static void add_report_id(UINT8 dev_id, UINT8 report_id, UINT16 att_handle)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_REPORT_MAPS; idx++)
	{
		if (!hogp_host_data.device_list[dev_id].report_map[idx].handle)
		{
			hogp_host_data.device_list[dev_id].report_map[idx].handle = att_handle;
			hogp_host_data.device_list[dev_id].report_map[idx].id = report_id;
			break;
		}
	}
}

static UINT8 get_report_id_from_hdl(UINT8 dev_id, UINT16 att_handle)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_REPORT_MAPS; idx++)
		if (hogp_host_data.device_list[dev_id].report_map[idx].handle == att_handle)
			return hogp_host_data.device_list[dev_id].report_map[idx].id;
	return MAX_NUM_REPORT_MAPS;
}

static UINT8 add_hogp_dev(UINT8 *bdaddr, UINT8 type, UINT8 protocol_mode)
{
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	for (idx = 0; idx < HOGP_MAX_DEV; idx++)
	{
		if (!memcmp(hogp_host_data.device_list[idx].remote_bd_addr, invalid_bd_addr, BD_ADDR_LEN))
		{
			logd("Adding at %u", idx);
			hogp_host_data.hogp_app_busy = TRUE;
			hogp_host_data.device_list[idx].protocol_mode = protocol_mode;
			memcpy(hogp_host_data.device_list[idx].remote_bd_addr, bdaddr, BD_ADDR_LEN);
			iLE_connect(new_trans_id, bdaddr, type);
			break;
		}
	}
	return idx;
}

static UINT8 update_hogp_dev(UINT8 *bdaddr, UINT8 conn_id)
{
	UINT8 idx;
	for (idx = 0; idx < HOGP_MAX_DEV; idx++)
	{
		if (!memcmp(hogp_host_data.device_list[idx].remote_bd_addr, bdaddr, BD_ADDR_LEN))
		{
			logd("Updating %u at %u", conn_id, idx);
			hogp_host_data.device_list[idx].conn_id = conn_id;
			break;
		}
	}
	return idx;
}

static UINT8 get_hogp_dev(UINT8 conn_id)
{
	UINT8 idx;
	for (idx = 0; idx < HOGP_MAX_DEV; idx++)
		if (hogp_host_data.device_list[idx].conn_id == conn_id)
			break;
	return idx;
}

static BOOLEAN remove_hogp_dev(UINT8 conn_id)
{
	BOOLEAN is_last_device = TRUE;
	UINT8 idx;
	if (conn_id == 0xFF)
		return TRUE;
	for (idx = 0; idx < HOGP_MAX_DEV; idx++)
	{
		if (hogp_host_data.device_list[idx].conn_id == conn_id)
		{
			uhid_close(hogp_host_data.device_list[idx].device_fd);
			memset(&hogp_host_data.device_list[idx], 0xFF, sizeof(hogp_host_dev_data_t));
		}
		else if (hogp_host_data.device_list[idx].conn_id != 0xFF)
			is_last_device = FALSE;
	}
	hogp_host_data.hogp_app_busy = FALSE;
	return is_last_device;
}

static BOOLEAN is_any_hogp_dev_present()
{
	UINT8 idx;
	for (idx = 0; idx < HOGP_MAX_DEV; idx++)
		if (hogp_host_data.device_list[idx].conn_id != 0xFF)
			return TRUE;
	return FALSE;
}

static void hogp_discover_services(UINT8 dev_id)
{
    trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	memset(hogp_host_data.device_list[dev_id].attr_db, 0, sizeof(hogp_host_data.device_list[dev_id].attr_db));
	memset(hogp_host_data.device_list[dev_id].report_map, 0, sizeof(hogp_host_data.device_list[dev_id].report_map));
	uuid_t hid_service_uuid;
	UINT16_TO_UUID(HUMAN_INTERFACE_DEVICE_SERIVCE_UUID, hid_service_uuid);
	iLE_discover_primary_service(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, &hid_service_uuid);
}

static void hogp_start_state_machine(UINT8 dev_id)
{
    trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	if (hogp_host_data.device_list[dev_id].protocol_mode == DEVICE_BOOT_PROTOCOL_MODE)
	{
		/* For Boot host, we do the following:
		 * 1. Set protocol mode to boot mode
		 * 2. Prepare UHID driver to accept reports
		 * 3. Enable notification of boot input report
		 */

		/* Write Protocol mode char value to boot mode */
		UINT16 idx;
		for (idx = 1; idx < HOGP_PER_DEV_ATTR; idx++)
		{
			if (hogp_host_data.device_list[dev_id].attr_db[idx].attr_type == ATTR_TYPE_CHARACTERISTIC && hogp_host_data.device_list[dev_id].attr_db[idx].uuid.value.uuid16 == PROTOCOL_MODE_CHAR_UUID)
			{
				buffer_t *buffer = (buffer_t*) app_alloc (1 + sizeof (buffer_t));
#if (PARANOID_STACK == TRUE)
				if (!buffer)
					return;
#endif
				buffer->offset = 0;
				buffer->length = 1;
				buffer->data[0] = hogp_host_data.device_list[dev_id].protocol_mode;
				iLE_write_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, ATT_OPCODE_WRITE_CMD, hogp_host_data.device_list[dev_id].attr_db[idx].attr_handle + 1, 0, buffer);
				dealloc(buffer);
				break;
			}
		}

		/* Open UHID port for sending reports */
		hogp_host_data.device_list[dev_id].device_fd = uhid_open(BT_UHID_PORT_NAME, NULL, 0);
		hogp_host_data.hogp_app_busy = FALSE;

		/* Enable notification of boot input report */
		UINT16 didx;
		for (idx = 1; idx < HOGP_PER_DEV_ATTR; idx++)
		{
			gatt_attribute_t attribute = hogp_host_data.device_list[dev_id].attr_db[idx];
			if (attribute.attr_type == ATTR_TYPE_CHARACTERISTIC)
			{
				if ((attribute.uuid.value.uuid16 == BOOT_MOUSE_INPUT_REPORT_CHAR_UUID) || (attribute.uuid.value.uuid16 == BOOT_KEYBOARD_INPUT_REPORT_CHAR_UUID))
				{
					if (attribute.uuid.value.uuid16 == BOOT_MOUSE_INPUT_REPORT_CHAR_UUID)
						add_report_id(dev_id, MOUSE_DEFAULT_REPORT_ID, idx);
					if (attribute.uuid.value.uuid16 == BOOT_KEYBOARD_INPUT_REPORT_CHAR_UUID)
						add_report_id(dev_id, KEYBOARD_DEFAULT_REPORT_ID, idx);
					iLE_register_notification(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, idx+1, TRUE);
					for (didx = idx; didx < HOGP_PER_DEV_ATTR; didx++)
					{
						attribute = hogp_host_data.device_list[dev_id].attr_db[didx];
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
							iLE_write_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, ATT_OPCODE_WRITE_CMD, didx, 0, buffer);
							app_dealloc(buffer);
							break;
						}
					}
					break;
				}
			}
		}
	}

	if (hogp_host_data.device_list[dev_id].protocol_mode == DEVICE_REPORT_PROTOCOL_MODE)
	{
		/* For Report host, we do the following:
		 * 1. Read all report reference descriptors
		 * 2. Read report map characteristic
		 * 3. Set protocol mode to report mode
		 * 4. Prepare UHID driver to accept reports
		 * 5. Enable notification for all Hid reports
		 */

		/* Read all report reference descriptors */
		UINT16 idx;
		for (idx = 1; idx < HOGP_PER_DEV_ATTR; idx++)
		{
			if (hogp_host_data.device_list[dev_id].attr_db[idx].attr_type == ATTR_TYPE_DESCRIPTOR && hogp_host_data.device_list[dev_id].attr_db[idx].uuid.value.uuid16 == REPORT_REFERENCE_DESC_UUID)
			{
				gatt_attribute_read_param_t read_param;
				read_param.att_opcode = ATT_OPCODE_READ_REQ;
				read_param.attr_read_param.read_attr.att_id = idx;
				iLE_read_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, &read_param);
			}
		}

		/* Read report map characteristic */
		for (idx = 1; idx < HOGP_PER_DEV_ATTR; idx++)
		{
			if (hogp_host_data.device_list[dev_id].attr_db[idx].attr_type == ATTR_TYPE_CHARACTERISTIC && hogp_host_data.device_list[dev_id].attr_db[idx].uuid.value.uuid16 == HID_REPORT_MAP_CHAR_UUID)
			{
				gatt_attribute_read_param_t read_param;
				read_param.att_opcode = ATT_OPCODE_READ_REQ;
				read_param.attr_read_param.read_attr.att_id = idx+1;
				iLE_read_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, &read_param);
				break;
			}
		}

		/* Set protocol mode to report mode */
		for (idx = 1; idx < HOGP_PER_DEV_ATTR; idx++)
		{
			if (hogp_host_data.device_list[dev_id].attr_db[idx].attr_type == ATTR_TYPE_CHARACTERISTIC && hogp_host_data.device_list[dev_id].attr_db[idx].uuid.value.uuid16 == PROTOCOL_MODE_CHAR_UUID)
			{
				buffer_t *buffer = (buffer_t*) app_alloc (1 + sizeof (buffer_t));
#if (PARANOID_STACK == TRUE)
				if (!buffer)
					return;
#endif
				buffer->offset = 0;
				buffer->length = 1;
				buffer->data[0] = hogp_host_data.device_list[dev_id].protocol_mode;
				iLE_write_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, ATT_OPCODE_WRITE_CMD, hogp_host_data.device_list[dev_id].attr_db[idx].attr_handle + 1, 0, buffer);
				dealloc(buffer);
				break;
			}
		}
	}
}

void hogp_enable_notifications(UINT8 dev_id)
{
	/* Finished reading Report Map Characteristic */
	UINT8 *map = hogp_host_data.saved_rd_blob_value->data;
	UINT16 map_len = hogp_host_data.saved_rd_blob_value->length;
	hex_dump("Report map", map, map_len);
	hogp_host_data.device_list[dev_id].device_fd = uhid_open(BT_UHID_PORT_NAME, map, map_len);

	/* Enable notification for all input reports */
	UINT8 idx;
    trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	for (idx = 0; idx < MAX_NUM_REPORT_MAPS; idx++)
	{
		if (hogp_host_data.device_list[dev_id].report_map[idx].handle)
		{
			iLE_register_notification(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, hogp_host_data.device_list[dev_id].report_map[idx].handle + 1, TRUE);
			UINT16 ccd_hdl = get_ccd_hdl_from_char(dev_id, hogp_host_data.device_list[dev_id].report_map[idx].handle);
			UINT16 value = 0x0001;
			buffer_t *wr_buffer = (buffer_t*) app_alloc (sizeof(UINT16) + sizeof (buffer_t));
#if (PARANOID_STACK == TRUE)
			if (!wr_buffer)
				break;
#endif
			wr_buffer->offset = 0;
			wr_buffer->length = sizeof(UINT16);
			memcpy(wr_buffer->data, &value, sizeof(UINT16));
			iLE_write_attribute_value(new_trans_id, hogp_host_data.device_list[dev_id].conn_id, ATT_OPCODE_WRITE_CMD, ccd_hdl, 0, wr_buffer);
			app_dealloc(wr_buffer);
		}
	}

	dealloc(hogp_host_data.saved_rd_blob_value);
	hogp_host_data.saved_rd_blob_value = NULL;
	hogp_host_data.hogp_app_busy = FALSE;
}

/******************************************************
 * Callback functions
 ******************************************************/
static void hogp_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
	logi("");
	if (result == TRUE)
	{
		hogp_host_data.app_handle = app_handle;
		logi("app_handle:%d", app_handle);
	}
}

static void hogp_on_primary_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 dev_id = get_hogp_dev(conn_id);
	logi("primary_service start_handle:%u end_handle:%u", start_handle, end_handle);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	if (is_finished == FALSE)
	{
		if (start_handle >= HOGP_PER_DEV_ATTR)
			return;
		hogp_host_data.device_list[dev_id].attr_db[start_handle].attr_type = ATTR_TYPE_PRIMARY_SERVICE;
		hogp_host_data.device_list[dev_id].attr_db[start_handle].attr_data.srv_data.end_handle = end_handle;
		memcpy (&hogp_host_data.device_list[dev_id].attr_db[start_handle].uuid, uuid, sizeof (uuid_t));
	}
	else
	{
		UINT16 att_id;
		hogp_host_data.num_of_discover_req = 0;
		for (att_id = 1; att_id < HOGP_PER_DEV_ATTR; att_id ++)
		{
			if (hogp_host_data.device_list[dev_id].attr_db[att_id].attr_type == ATTR_TYPE_PRIMARY_SERVICE)
			{
				hogp_host_data.num_of_discover_req ++;
				iLE_discover_characteristic(new_trans_id, conn_id, att_id, hogp_host_data.device_list[dev_id].attr_db[att_id].attr_data.srv_data.end_handle, NULL);
			}
		}
	}
}

static void hogp_on_characteristic_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 dev_id = get_hogp_dev(conn_id);
	logi("\t characteristic handle:%u value_handle:%u, is_finished:%u", att_handle, value_handle, is_finished);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	if (is_finished == FALSE)
	{
		if ((att_handle >= HOGP_PER_DEV_ATTR) || (value_handle >= HOGP_PER_DEV_ATTR))
			return;
		hogp_host_data.device_list[dev_id].attr_db[att_handle].attr_type = ATTR_TYPE_CHARACTERISTIC;
		hogp_host_data.device_list[dev_id].attr_db[att_handle].attr_data.char_desc_data.property = property;
		memcpy (&hogp_host_data.device_list[dev_id].attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
		hogp_host_data.device_list[dev_id].attr_db[att_handle].attr_handle = att_handle;
		hogp_host_data.device_list[dev_id].attr_db[value_handle].attr_type = ATTR_TYPE_CHARACTERISTIC_VALUE;
	}
	else if (hogp_host_data.num_of_discover_req)
	{
		hogp_host_data.num_of_discover_req --;
		if (!hogp_host_data.num_of_discover_req)
		{
			UINT16 start_id;
			for (start_id = 1; start_id < HOGP_PER_DEV_ATTR; start_id ++)
			{
				if (hogp_host_data.device_list[dev_id].attr_db[start_id].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE && start_id < (HOGP_PER_DEV_ATTR - 1) && hogp_host_data.device_list[dev_id].attr_db[start_id + 1].attr_type == FALSE)
				{
					UINT16 end_handle = get_last_empty_attr_id(dev_id, start_id);
					if (end_handle == HOGP_PER_DEV_ATTR)
					{
						gatt_attribute_t *srv = get_owner_prim_srv(dev_id, start_id);
						if (srv)
							end_handle = srv->attr_data.srv_data.end_handle;
					}
					logi("start_id:%u end_handle:%u", start_id, end_handle);
					logi("iLE_discover_descriptor start:%u end:%u", start_id + 1, end_handle);
					hogp_host_data.num_of_discover_req ++;
					iLE_discover_descriptor(new_trans_id, conn_id, start_id + 1, end_handle);
				}
			}
		}
	}
}

static void hogp_on_descriptor_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	UINT8 dev_id = get_hogp_dev(conn_id);
	logi("\t\t descriptor handle:%u", att_handle);
	if (is_finished == FALSE)
	{
		if (att_handle >= HOGP_PER_DEV_ATTR)
			return;
		hogp_host_data.device_list[dev_id].attr_db[att_handle].attr_type = ATTR_TYPE_DESCRIPTOR;
		memcpy (&hogp_host_data.device_list[dev_id].attr_db[att_handle].uuid, uuid, sizeof (uuid_t));
		hogp_host_data.device_list[dev_id].attr_db[att_handle].attr_handle = att_handle;
	}
	else
	{
		hogp_host_data.num_of_discover_req --;
		if (!hogp_host_data.num_of_discover_req)
		{
			if (!hogp_host_data.hogp_thread_running)
			{
				hogp_start_state_machine(dev_id);
				return;
			}
			hogp_req_elem_t *res_code = (hogp_req_elem_t*) alloc_queue_element(sizeof(hogp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
			if (!res_code)
				return;
#endif
			res_code->dev_id = dev_id;
			res_code->opcode = HOGP_RES_SERVICE_DISCOVERED;
			enqueue(&hogp_host_data.hogp_res_q, res_code);
			signal_req();
		}
	}
}

static void hogp_on_notification_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN is_indication)
{
	UINT8 dev_id = get_hogp_dev(conn_id);
	UINT8 *data;

	gatt_attribute_t *characteristic = get_owner_characteristic(dev_id, att_id);
	logd("dev_id = %u, conn_id = %u, characteristic = %p", dev_id, conn_id, characteristic);
	data = buffer->data + buffer->offset;
	logd("length = %d and buffer->offset = %d and att_id = %d", buffer->length, buffer->offset, att_id);
	hex_dump("Received report", data, buffer->length);

	if (!hogp_host_data.device_list[dev_id].device_fd)
		return;

	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, 1 + sizeof (buffer_t));
	buffer_t *wr_buffer = (buffer_t*) app_alloc (buffer->length + 1 + sizeof (buffer_t));
	wr_buffer->offset = 0;
	wr_buffer->length = buffer->length + 1;
	wr_buffer->data[0] = get_report_id_from_hdl(dev_id, characteristic->attr_handle);
	memcpy(wr_buffer->data + 1, data, buffer->length);
	uhid_send(hogp_host_data.device_list[dev_id].device_fd, wr_buffer);
	app_dealloc(wr_buffer);
}

static void hogp_on_attribute_read_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t *buffer)
{
	UINT8 dev_id = get_hogp_dev(conn_id);
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	if (status == ATT_SUCCESS)
	{
		if ((buffer->length == (iLE_get_att_mtu(new_trans_id, conn_id)) - 1) || att_opcode == ATT_OPCODE_READ_BLOB_RESP)
		{
			/* Report Map Characteristic */
			if (!hogp_host_data.saved_rd_blob_value)
			{
				hogp_host_data.saved_rd_blob_value = (buffer_t*) app_alloc(sizeof(buffer_t) + ATT_MAX_VALUE_LEN);
#if (PARANOID_STACK == TRUE)
				if (!hogp_host_data.saved_rd_blob_value)
					return;
#endif

				hogp_host_data.saved_rd_blob_value->offset = 0;
				hogp_host_data.saved_rd_blob_value->length = 0;
			}
			if (hogp_host_data.saved_rd_blob_value->length + buffer->length >= ATT_MAX_VALUE_LEN)
				buffer->length = ATT_MAX_VALUE_LEN - hogp_host_data.saved_rd_blob_value->length; // Truncate buffer if length exceeds
			memcpy(hogp_host_data.saved_rd_blob_value->data + hogp_host_data.saved_rd_blob_value->offset, buffer->data + buffer->offset, buffer->length);
			hogp_host_data.saved_rd_blob_value->offset = hogp_host_data.saved_rd_blob_value->offset + buffer->length;
			hogp_host_data.saved_rd_blob_value->length += buffer->length;
			if (buffer->length == (iLE_get_att_mtu(new_trans_id, conn_id)) - 1)
			{
				gatt_attribute_read_param_t read_param;
				read_param.att_opcode = ATT_OPCODE_READ_BLOB_REQ;
				read_param.attr_read_param.read_attr.att_id = att_id;
				read_param.attr_read_param.read_attr.offset = hogp_host_data.saved_rd_blob_value->offset;
				iLE_read_attribute_value(new_trans_id, conn_id, &read_param);
			}
			else
			{
				if (hogp_host_data.saved_rd_blob_value)
				{
					/* Finished reading Report Map Characteristic */
					if (!hogp_host_data.hogp_thread_running)
					{
						hogp_enable_notifications(dev_id);
						return;
					}
					hogp_req_elem_t *res_code = (hogp_req_elem_t*) alloc_queue_element(sizeof(hogp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
					if (res_code == NULL )
						return;
#endif
					res_code->dev_id = dev_id;
					res_code->opcode = HOGP_RES_READ_ATTRIBUTE;
					enqueue(&hogp_host_data.hogp_res_q, res_code);
					signal_req();
				}
			}
		}
		else if(att_opcode == ATT_OPCODE_READ_RESP)
		{
			/* Report Reference Descriptor */
			UINT8 report_id, report_type, *data = buffer->data + buffer->offset;
			STREAM_TO_UINT8(report_id, data);
			STREAM_TO_UINT8(report_type, data);
			/* If input report, save */
			if (report_type == 0x01)
				add_report_id(dev_id, report_id, get_owner_characteristic(dev_id, att_id)->attr_handle);
		}
	}
}

static void hogp_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, BOOLEAN from_remote, UINT8 *id_addr, UINT8 id_addr_type)
{
	logd("status : %d", status);
	if (status == STATUS_SUCCESS)
	{
		UINT8 dev_id;
		trans_id_t new_trans_id = 0;
		add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);

		hex_dump("BD addr", bdaddr, BD_ADDR_LEN);
		dev_id = update_hogp_dev(remote_bd_addr, conn_id);
		if (dev_id == HOGP_MAX_DEV)
			return;
		iLE_create_bond(new_trans_id, conn_id, 0x00, 0x07);
	}
	else
		hogp_host_data.hogp_app_busy = FALSE;

}

static void hogp_bonding_completed_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
{
	logd("status : %d", status);
	if (status == STATUS_SUCCESS)
	{
		hex_dump("BD addr", bdaddr, BD_ADDR_LEN);
		UINT8 dev_id = get_hogp_dev(conn_id);
		if (dev_id == HOGP_MAX_DEV)
			return;
		if (!hogp_host_data.hogp_thread_running)
		{
			hogp_discover_services(dev_id);
			return;
		}
		hogp_req_elem_t *res_code = (hogp_req_elem_t*) alloc_queue_element(sizeof(hogp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (res_code == NULL )
			return;
#endif
		res_code->dev_id = dev_id;
		res_code->opcode = HOGP_RES_DEVICE_BONDED;
		enqueue(&hogp_host_data.hogp_res_q, res_code);
		signal_req();
	}
	else
		hogp_host_data.hogp_app_busy = FALSE;
}


static void hogp_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
	logi("");
    trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	BOOLEAN is_last_device = remove_hogp_dev(conn_id);
	if (hogp_host_data.hogp_app_closing)
	{
		if (is_last_device)
		{
			iLE_deregister_application(hogp_host_data.app_handle);
			cleanup_q(&hogp_host_data.hogp_res_q);
			hogp_host_data.hogp_app_running = FALSE;
			signal_req();
			osa_semaphore_get(&hogp_host_data.thread_sem);
			osa_semaphore_delete(&hogp_host_data.thread_sem);
			osa_thread_join(HOGP_THREAD, NULL);
		}
		else
		{
			UINT8 idx;
			for (idx = 0; idx < HOGP_MAX_DEV; idx++)
			{
				if (hogp_host_data.device_list[idx].conn_id != 0xFF)
				{
					iLE_disconnect(new_trans_id, hogp_host_data.device_list[idx].conn_id, 0x13);
					break;
				}
			}
		}
	}
}

static void hogp_scan_result_cb(trans_id_t trans_id, discovered_device_t *device)
{
	char bdaddr_str[BD_ADDR_STR_LEN];
	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
	logd("Found Device %s %s", bdaddr_str, device->localname);

	memcpy(&hogp_host_data.discovered_list[hogp_host_data.num_discovered_devices], device, sizeof(discovered_device_t));
	if (device->adv_data && device->adv_data_len)
	{
		hogp_host_data.discovered_list[hogp_host_data.num_discovered_devices].adv_data = (UINT8*) app_alloc(device->adv_data_len);
#if (PARANOID_STACK == TRUE)
		if (!hogp_host_data.discovered_list[hogp_host_data.num_discovered_devices].adv_data)
			return;
#endif
		memcpy(hogp_host_data.discovered_list[hogp_host_data.num_discovered_devices].adv_data, device->adv_data, device->adv_data_len);
	}
	hogp_host_data.num_discovered_devices++;
}

static void hogp_scan_completed_cb(trans_id_t trans_id)
{
	if (!hogp_host_data.hogp_thread_running)
	{
		display_discovered_device_list();
		return;
	}
	hogp_req_elem_t *res_code = (hogp_req_elem_t*) alloc_queue_element(sizeof(hogp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (res_code == NULL )
		return;
#endif
	res_code->opcode = HOGP_RES_SCAN_COMPLETED;
	enqueue(&hogp_host_data.hogp_res_q, res_code);
	signal_req();
}

static gatt_callbacks_t hogp_gatt_cb =
{
	.iLE_on_primary_service_discovered_cb = hogp_on_primary_service_discovered_cb,
	.iLE_on_characteristic_discovered_cb = hogp_on_characteristic_discovered_cb,
	.iLE_on_descriptor_discovered_cb = hogp_on_descriptor_discovered_cb,
	.iLE_on_attribute_read_cb = hogp_on_attribute_read_cb,
	.iLE_on_notification_cb = hogp_on_notification_cb,
};

static device_control_callbacks_t hogp_dev_cb =
{
	.iLE_scan_result_cb = hogp_scan_result_cb,
	.iLE_scan_completed_cb = hogp_scan_completed_cb,
	.iLE_on_connected_cb = hogp_connected_cb,
	.iLE_bonding_completed_cb = hogp_bonding_completed_cb,
	.iLE_on_disconnected_cb = hogp_on_disconnected_cb,
};

void hogp_start_discovery(UINT8 *arg)
{
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	for (idx = 0; idx < hogp_host_data.num_discovered_devices; idx++)
		app_dealloc(hogp_host_data.discovered_list[idx].adv_data);
	hogp_host_data.num_discovered_devices = 0;

	iLE_start_scan(new_trans_id, HOGP_SCAN_TIMEOUT_SEC, TRUE, FALSE, FALSE, FALSE, 0, NULL);
}

static void hogp_start(UINT8 *bdaddr, UINT8 protocol_mode)
{
	UINT8 idx, type = 1;
	char bdaddr_str[BD_ADDR_STR_LEN];
	if (hogp_host_data.hogp_app_busy)
	{
		loge("HOGP app is busy. Please try later...");
		return;
	}
	if (bdaddr)
	{
		for (idx = 0; idx < hogp_host_data.num_discovered_devices; idx++)
		{
			if (!memcmp(hogp_host_data.discovered_list[idx].bdaddr, bdaddr, BD_ADDR_LEN))
			{
				type = hogp_host_data.discovered_list[idx].addr_type;
				break;
			}
		}
		idx = add_hogp_dev(bdaddr, type, protocol_mode);
		if (idx == HOGP_MAX_DEV)
		{
			loge("Reached max no. of HOGP devices");
			return;
		}
	}
	if (!hogp_host_data.num_discovered_devices)
	{
		loge("First do hogp_start_discovery operation.");
		return;
	}
	for (idx = 0; idx < hogp_host_data.num_discovered_devices; idx++)
	{
		BDADDR_TO_STRING(bdaddr_str, hogp_host_data.discovered_list[idx].bdaddr);
		logln("Device %d> %s - %s", idx, bdaddr_str, hogp_host_data.discovered_list[idx].localname);
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
	if (index < hogp_host_data.num_discovered_devices)
	{
		idx = add_hogp_dev(hogp_host_data.discovered_list[index].bdaddr, hogp_host_data.discovered_list[index].addr_type, protocol_mode);
		if (idx == HOGP_MAX_DEV)
		{
			loge("Reached max no. of HOGP devices");
			return;
		}
	}
}

void hogp_start_boot_host(UINT8 *bdaddr)
{
	hogp_start(bdaddr, DEVICE_BOOT_PROTOCOL_MODE);
}

void hogp_start_report_host(UINT8 *bdaddr)
{
	hogp_start(bdaddr, DEVICE_REPORT_PROTOCOL_MODE);
}

/**
 * Stops the use case by only disconnecting the remote device.
 */
void hogp_stop(UINT8 *bdaddr)
{
	if (!is_any_hogp_dev_present())
		hogp_on_disconnected_cb(INVALID_TRANS_ID, 0xFF, 0x00);
	else
	{
		UINT8 idx;
        trans_id_t new_trans_id = 0;
	    add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
		for (idx = 0; idx < HOGP_MAX_DEV; idx++)
		{
			if (hogp_host_data.device_list[idx].conn_id != 0xFF)
			{
				iLE_disconnect(new_trans_id, hogp_host_data.device_list[idx].conn_id, 0x13);
				break;
			}
		}
	}
}

static const cmd_t hogp_cmd_arr[] = {
{ "start_discovery", hogp_start_discovery },
{ "start_boot_host", hogp_start_boot_host },
{ "start_report_host", hogp_start_report_host },
{ "stop", hogp_stop },
{ "_end_", NULL },
};


static osa_thread_ret_t hogp_app_main_thread(osa_thread_arg_t arg)
{
	hogp_host_data.hogp_thread_running = TRUE;
	osa_semaphore_create(&hogp_host_data.msg_sem, 0);
	osa_semaphore_put(&hogp_host_data.thread_sem);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	while (hogp_host_data.hogp_app_running == TRUE)
	{
		hogp_req_elem_t* res_elem = (hogp_req_elem_t*) dequeue(&hogp_host_data.hogp_res_q);
		if (res_elem == NULL )
		{
			osa_semaphore_get(&hogp_host_data.msg_sem);
			continue;
		}
		switch (res_elem->opcode)
		{
		case HOGP_RES_SCAN_COMPLETED:
		{
			logd("HOGP_RES_SCAN_COMPLETED");
			display_discovered_device_list();
		}
			break;
		case HOGP_RES_DEVICE_BONDED:
		{
			logd("HOGP_RES_DEVICE_BONDED");
			hogp_discover_services(res_elem->dev_id);
		}
			break;
		case HOGP_RES_SERVICE_DISCOVERED:
		{
			logd("HOGP_RES_SERVICE_DISCOVERED");
			hogp_start_state_machine(res_elem->dev_id);
		}
			break;
		case HOGP_RES_READ_ATTRIBUTE:
		{
			logd("HOGP_RES_READ_ATTRIBUTE");
			hogp_enable_notifications(res_elem->dev_id);
		}
			break;
		}
		dealloc_queue_element(res_elem);
	}
	osa_semaphore_delete(&hogp_host_data.msg_sem);
	osa_semaphore_put(&hogp_host_data.thread_sem);
	hogp_host_data.hogp_thread_running = FALSE;
	osa_thread_exit(NULL);
}

void hogp_init()
{
	/* Register hogp application. */
	iLE_register_application(&hogp_dev_cb, &hogp_gatt_cb, "hogp", hogp_cmd_arr, hogp_register_application_cb);
	init_q(&hogp_host_data.hogp_res_q);
	hogp_host_data.hogp_app_running = TRUE;
	hogp_host_data.hogp_thread_running = FALSE;
	memset(hogp_host_data.device_list, 0xFF, sizeof(hogp_host_data.device_list));
	osa_semaphore_create(&hogp_host_data.thread_sem, 0);
	osa_thread_create(HOGP_THREAD, hogp_app_main_thread, PROFILE_THREAD_PRIORITY);
	osa_semaphore_get(&hogp_host_data.thread_sem);
}

void hogp_cleanup()
{
	logi("");
	UINT8 idx;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, hogp_host_data.app_handle);
	for (idx = 0; idx < hogp_host_data.num_discovered_devices; idx++)
		app_dealloc(hogp_host_data.discovered_list[idx].adv_data);
	hogp_host_data.num_discovered_devices = 0;
	hogp_host_data.hogp_app_closing = TRUE;
	hogp_stop(NULL);
}

#endif
