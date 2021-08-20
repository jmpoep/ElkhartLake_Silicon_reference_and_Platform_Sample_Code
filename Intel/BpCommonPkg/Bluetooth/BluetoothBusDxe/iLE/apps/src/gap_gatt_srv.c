/** @file
  GAP profile implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#include "gap_gatt_srv.h"

#define MODULE_DBG_LVL GAP_GATT_SRV_DBG_LVL
#include "log.h"

#define START_HANDLE							0x0001
#define END_HANDLE								0xFFFF

#if (GAP_GATT_SRV_APP == TRUE)
RETENTION_SECTION_START
static gap_gatt_srv_data_t gap_gatt_srv_data;
RETENTION_SECTION_END

/****************************************************************
 *		GAP GATT Service static utility functions
 ***************************************************************/
static buffer_t* get_buffer_from_value(UINT8 att_map_idx, UINT16 offset)
{
	buffer_t *buffer;

	if (att_map_idx == DEVICE_NAME_CHARACTERISTIC_ID)
	{
		UINT8 name[MAX_LOCAL_NAME_LEN];
		UINT8 length;
		trans_id_t new_trans_id = 0;
		add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
		length = iLE_get_local_device_name(new_trans_id, name);

		buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + length);

		if (!buffer)
			return NULL;

		buffer->offset = offset;
		buffer->length = length - offset;
		memcpy(buffer->data, name, length);
	}
	else
	{
		buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + gap_gatt_srv_data.att_val_map[att_map_idx].length);

		if (!buffer)
			return NULL;

		buffer->offset = offset;
		buffer->length = gap_gatt_srv_data.att_val_map[att_map_idx].length - offset;
		memcpy(buffer->data, gap_gatt_srv_data.att_val_map[att_map_idx].value, gap_gatt_srv_data.att_val_map[att_map_idx].length);
	}

	hex_dump("GATT GAP SERVER", buffer->data + buffer->offset, buffer->length);

	return buffer;
}

static UINT8 get_att_val_elem(UINT16 att_id)
{
	UINT8 idx;
	for (idx = 0; idx < GATT_GAP_SRV_ATT_MAX_ID; idx++)
	{
		if (gap_gatt_srv_data.att_val_map[idx].att_id == att_id)
			return idx;
	}
	return GATT_GAP_SRV_ATT_MAX_ID;
}

char *id_map_str[] = {
		"DEVICE_NAME_CHARACTERISTIC_ID",
		"APPEARANCE_CHARACTERISTIC_ID",
		"PEER_CONNECTION_PARAM_CHARACTERISTIC_ID",
		"CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID",
		"SERVICE_CHANGED_CHARACTERISTIC_ID",
		"GATT_CLIENT_CHAR_CONFIG_UUID_ID"
};

static void dump_att_map()
{
	UINT8 idx;
	for (idx = 0; idx < GATT_GAP_SRV_ATT_MAX_ID; idx++)
	{
		logd("id:%s att_id:%d", id_map_str[idx],  gap_gatt_srv_data.att_val_map[idx].att_id);
	}
}

/****************************************************************
 *  	GAP GATT Service static functions
 ***************************************************************/
static void gap_gatt_send_service_change_indication(UINT8 conn_id)
{
	logd("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
	buffer_t *buffer = get_buffer_from_value(SERVICE_CHANGED_CHARACTERISTIC_ID, 0);
	hex_dump("notification data", buffer->data + buffer->offset, buffer->length);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	iLE_send_notification(new_trans_id, conn_id, gap_gatt_srv_data.att_val_map[SERVICE_CHANGED_CHARACTERISTIC_ID].att_id, buffer, TRUE);
	dealloc (buffer);
}

static void gap_gatt_on_service_started_handler()
{
	logi("");
	/* send indication/notification to connected client */
	connected_device_t *device;
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		device = g_local_adapter.connected_device[idx];
		if (device && device->gap_connection_state == GAP_CONNECTION_STATE_ACL_CONNECTED)
		{
			if(gap_gatt_srv_data.srv_changed_notify_reg_list[idx])
			{
				gap_gatt_send_service_change_indication(idx);
			}
		}
	}
}

static void gap_gatt_on_service_removed_handler()
{
	logi("");
	/* send indication/notification to connected client */
	connected_device_t *device;
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		device = g_local_adapter.connected_device[idx];
		if (device && device->gap_connection_state == GAP_CONNECTION_STATE_ACL_CONNECTED)
		{
			if(gap_gatt_srv_data.srv_changed_notify_reg_list[idx])
			{
				gap_gatt_send_service_change_indication(idx);
			}
		}
	}
}

static void gap_gatt_on_connect_handler(UINT8 conn_id)
{
	logi("");
	if(iLE_get_service_change_config(gap_gatt_srv_data.app_handle, conn_id))
	{
		gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id] = TRUE;
		/* send indication */
		//gap_gatt_send_service_change_indication(conn_id);
	}
	else
		gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id] = FALSE;
}

static BOOLEAN gatt_add_service()
{
	logi("");
	/* Add GATT service */
	uuid_t service_changed_characteristic_uuid;
	uuid_t client_chars_config_uuid;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
	UINT16_TO_UUID(GATT_SERVICE_UUID, gap_gatt_srv_data.gatt_srv_uuid);
	UINT16_TO_UUID(SERVICE_CHANGED_CHARACTERISTIC, service_changed_characteristic_uuid);
	UINT16_TO_UUID(GATT_CLIENT_CHAR_CONFIG_UUID, client_chars_config_uuid);

	iLE_add_service(new_trans_id, &gap_gatt_srv_data.gatt_srv_uuid, ATTR_TYPE_PRIMARY_SERVICE, 0, 1, 1);

	UINT8 *p = gap_gatt_srv_data.att_val_map[SERVICE_CHANGED_CHARACTERISTIC_ID].value;
	UINT16_TO_STREAM(p, START_HANDLE);
	UINT16_TO_STREAM(p, END_HANDLE);
	gap_gatt_srv_data.att_val_map[SERVICE_CHANGED_CHARACTERISTIC_ID].fixed_len = 4;
	gap_gatt_srv_data.att_val_map[SERVICE_CHANGED_CHARACTERISTIC_ID].length = 4;

	gap_gatt_srv_data.att_val_map[GATT_CLIENT_CHAR_CONFIG_UUID_ID].fixed_len = 2;
	gap_gatt_srv_data.att_val_map[GATT_CLIENT_CHAR_CONFIG_UUID_ID].length = 2;

	iLE_add_characteristic(new_trans_id, &service_changed_characteristic_uuid, ATTRIBUTE_PROPERTY_INDICATE, 0);
	iLE_add_descriptor(new_trans_id, &client_chars_config_uuid, 0, ATTRIBUTE_PERMISSION_READ|ATTRIBUTE_PERMISSION_WRITE);
	iLE_start_service(new_trans_id);

	return TRUE;
}

static BOOLEAN gap_add_service()
{
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
	BOOLEAN car_supported = iLE_is_controller_privacy_supported(new_trans_id);

	/* Appearance characteristic = Generic phone */
	gap_gatt_srv_data.att_val_map[APPEARANCE_CHARACTERISTIC_ID].fixed_len = 2;
	gap_gatt_srv_data.att_val_map[APPEARANCE_CHARACTERISTIC_ID].length = 2;
	gap_gatt_srv_data.att_val_map[APPEARANCE_CHARACTERISTIC_ID].value[0] = 0x40;

	/*device name W>*/
	gap_gatt_srv_data.att_val_map[DEVICE_NAME_CHARACTERISTIC_ID].length = 1;
	gap_gatt_srv_data.att_val_map[DEVICE_NAME_CHARACTERISTIC_ID].value[0] = 0x65;

	/* Connection parameters characteristic = Default value */
	struct
	{
		UINT16 connect_int_min;
		UINT16 connect_int_max;
		UINT16 slave_latency;
		UINT16 Connect_supervision_mul;
	}gap_connection_param = {GAP_CONN_INT_100MS,GAP_CONN_INT_200MS,
			GAP_CONN_PREF_SLAVE_LATENCY,GAP_CONN_INT_10000MS};
	gap_gatt_srv_data.att_val_map[PEER_CONNECTION_PARAM_CHARACTERISTIC_ID].fixed_len = sizeof(gap_connection_param);
	gap_gatt_srv_data.att_val_map[PEER_CONNECTION_PARAM_CHARACTERISTIC_ID].length = sizeof(gap_connection_param);
	memcpy (gap_gatt_srv_data.att_val_map[PEER_CONNECTION_PARAM_CHARACTERISTIC_ID].value, &gap_connection_param, sizeof (gap_connection_param));

	/* Central Address Resolution characteristic = 1 */
	gap_gatt_srv_data.att_val_map[CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID].fixed_len = 1;
	gap_gatt_srv_data.att_val_map[CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID].length = 1;
	if (car_supported)
		gap_gatt_srv_data.att_val_map[CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID].value[0] = 1;
	else
		gap_gatt_srv_data.att_val_map[CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID].value[0] = 0;

	/* Add GAP service */
	uuid_t device_name_characteristic_uuid;
	uuid_t appearance_characteristic_uuid;
	uuid_t peer_connection_param_characteristic_uuid;
	uuid_t central_addr_resolution_characteristic_uuid;

	UINT16_TO_UUID(GAP_SERVICE_UUID, gap_gatt_srv_data.gap_srv_uuid);
	UINT16_TO_UUID(DEVICE_NAME_CHARACTERISTIC, device_name_characteristic_uuid);
	UINT16_TO_UUID(APPEARANCE_CHARACTERISTIC, appearance_characteristic_uuid);
	UINT16_TO_UUID(PEER_CONNECTION_PARAM_CHARACTERISTIC, peer_connection_param_characteristic_uuid);
	UINT16_TO_UUID(CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC, central_addr_resolution_characteristic_uuid);

	if (car_supported)
		iLE_add_service(new_trans_id, &gap_gatt_srv_data.gap_srv_uuid, ATTR_TYPE_PRIMARY_SERVICE, 0, 4, 0);
	else
		iLE_add_service(new_trans_id, &gap_gatt_srv_data.gap_srv_uuid, ATTR_TYPE_PRIMARY_SERVICE, 0, 3, 0);
	iLE_add_characteristic(new_trans_id, &device_name_characteristic_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);
	iLE_add_characteristic(new_trans_id, &appearance_characteristic_uuid, ATTRIBUTE_PROPERTY_READ | ATTRIBUTE_PROPERTY_WRITE, ATTRIBUTE_PERMISSION_READ | ATTRIBUTE_PERMISSION_WRITE);
	iLE_add_characteristic(new_trans_id, &peer_connection_param_characteristic_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);
	if (car_supported)
		iLE_add_characteristic(new_trans_id, &central_addr_resolution_characteristic_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);
	iLE_start_service(gap_gatt_srv_data.app_handle);
	return TRUE;
}

/****************************************************************
 * 			GAP GATT Service Call backs
 ***************************************************************/
static void gap_gatt_srv_app_register_cb(UINT8 app_handle, BOOLEAN result)
{
	logd("app_handle = %d, result = %d", app_handle, result);
	if(result && app_handle == GAP_GATT_SRV_APP_HANDLE)
	{
		gap_gatt_srv_data.app_handle = app_handle;
	}
	else
		logw("Wrong app handle received for GAP GATT service, app handle = %d, expecting %d", app_handle, GAP_GATT_SRV_APP_HANDLE);
}
static void gap_gatt_srv_stack_initialized_cb(BOOLEAN initialized)
{
	if (initialized)
	{
		gap_add_service();
		gatt_add_service();
	}
}

static void gap_gatt_srv_on_attribute_read_req_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset)
{
	logi("");
	UINT8 map_id = get_att_val_elem(att_id);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
#if (PARANOID_STACK == TRUE)
	if (map_id == GATT_GAP_SRV_ATT_MAX_ID)
	{
		iLE_send_attribute_read_rsp(new_trans_id, conn_id, att_opcode, att_id,  ATT_ERR_ATTRIB_NOT_FOUND, NULL);
	}
	else if (offset >= gap_gatt_srv_data.att_val_map[map_id].length)
	{
		iLE_send_attribute_read_rsp(new_trans_id, conn_id, att_opcode, att_id, ATT_ERR_INVALID_OFFSET, NULL);
	}
	else
#endif
	{
		logd("map_id:%d", map_id);
		buffer_t *buffer = get_buffer_from_value(map_id, offset);
#if (PARANOID_STACK == TRUE)
		if (!buffer)
		{
			iLE_send_attribute_read_rsp(new_trans_id, conn_id, att_opcode, att_id, ATT_ERR_UNLIKELY, NULL);
			return;
		}
#endif
		iLE_send_attribute_read_rsp(new_trans_id, conn_id, att_opcode, att_id, ATT_SUCCESS, buffer);
		app_dealloc (buffer);
	}
}

static void gap_gatt_srv_on_attribute_write_req_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer)

{
	logi("");
	UINT8 map_id = get_att_val_elem(att_id);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
#if (PARANOID_STACK == TRUE)
	if(map_id == GATT_GAP_SRV_ATT_MAX_ID || conn_id >= MAX_NUM_CONNECTED_DEVICE || !buffer ||
		(buffer && ((buffer->length > GAP_GATT_SRV_MAX_VALUE_LENGTH) ||
			(gap_gatt_srv_data.att_val_map[map_id].fixed_len && (buffer->length != gap_gatt_srv_data.att_val_map[map_id].fixed_len)))))
	{
		iLE_send_attribute_write_rsp(new_trans_id, conn_id, att_opcode, att_id, 0, ATT_ERR_INVALID_ATTRIB_VAL_LENGTH, NULL);
	}
	else
#endif
	{
		gap_gatt_srv_data.att_val_map[map_id].length = MIN(GAP_GATT_SRV_MAX_VALUE_LENGTH,buffer->length);
		memcpy(&gap_gatt_srv_data.att_val_map[map_id].value, buffer->data + buffer->offset, gap_gatt_srv_data.att_val_map[map_id].length);
		if(map_id == GATT_CLIENT_CHAR_CONFIG_UUID_ID)
		{
			if(gap_gatt_srv_data.att_val_map[map_id].value[0] == CLIENT_CFG_VALUE_IND_ENABLE)
			{
				logd("Enable indication for service change characteristic");
				gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id] = TRUE;
				iLE_set_service_change_config(new_trans_id, conn_id, TRUE);
			}
			else
			{
				logd("Disable indication for service change characteristic");
				gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id] = FALSE;
				iLE_set_service_change_config(new_trans_id, conn_id, FALSE);
			}
		}
		iLE_send_attribute_write_rsp(new_trans_id, conn_id, att_opcode, att_id, 0, ATT_SUCCESS, NULL);
	}
}

static void gap_gatt_srv_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote, UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
{
	logi("");
	if (result == STATUS_SUCCESS)
		gap_gatt_on_connect_handler(conn_id);
}

static void gap_gatt_srv_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
	logi("");
	if(result == 0x00)
		gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id] = FALSE;
}

void gap_gatt_srv_on_bonding_completed_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, UINT8 *id_addr, UINT8 id_addr_type)
{
	logd("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
	if (!status) /* SMP_SUCCESS */
	{
		/* update the NVM database about service change indication configuration */
		iLE_set_service_change_config(new_trans_id, conn_id, gap_gatt_srv_data.srv_changed_notify_reg_list[conn_id]);
	}
}

static void gap_gatt_on_service_started_cb(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 service_handle)
{
	logi("");
	if (uuidcmp(uuid, &gap_gatt_srv_data.gap_srv_uuid) == TRUE)
		gap_gatt_srv_data.gap_srv_handle = service_handle;
	else if (uuidcmp(uuid, &gap_gatt_srv_data.gatt_srv_uuid) == TRUE)
		gap_gatt_srv_data.gatt_srv_handle = service_handle;
	else
	{
		/* Send service change indication */
		gap_gatt_on_service_started_handler();
	}
}

static void gap_gatt_on_service_removed_cb(trans_id_t trans_id, UINT8 status, UINT16 start_handle, UINT16 end_handle)
{
	gap_gatt_on_service_removed_handler();
}

static void gatt_gap_on_attribute_added_cb(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
{
	logi("");
	uuid_t compare_uuid;
	UINT16_TO_UUID(DEVICE_NAME_CHARACTERISTIC, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[DEVICE_NAME_CHARACTERISTIC_ID].att_id = att_id + 1;
	UINT16_TO_UUID(APPEARANCE_CHARACTERISTIC, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[APPEARANCE_CHARACTERISTIC_ID].att_id = att_id + 1;
	UINT16_TO_UUID(PEER_CONNECTION_PARAM_CHARACTERISTIC, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[PEER_CONNECTION_PARAM_CHARACTERISTIC_ID].att_id = att_id + 1;
	UINT16_TO_UUID(CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID].att_id = att_id + 1;
	UINT16_TO_UUID(SERVICE_CHANGED_CHARACTERISTIC, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[SERVICE_CHANGED_CHARACTERISTIC_ID].att_id = att_id + 1;
	UINT16_TO_UUID(GATT_CLIENT_CHAR_CONFIG_UUID, compare_uuid);
	if (uuidcmp(&compare_uuid, uuid) == TRUE)
		gap_gatt_srv_data.att_val_map[GATT_CLIENT_CHAR_CONFIG_UUID_ID].att_id = att_id;
	dump_att_map();
}

static device_control_callbacks_t dev_ctl_cb = {
	.iLE_stack_initialized_cb = gap_gatt_srv_stack_initialized_cb,
	.iLE_scan_result_cb = NULL,
	.iLE_scan_completed_cb = NULL,
	.iLE_on_link_enc_changed_cb = NULL,
	.iLE_bonding_completed_cb = gap_gatt_srv_on_bonding_completed_cb,
	.iLE_on_connected_cb = gap_gatt_srv_on_connected_cb,
	.iLE_on_disconnected_cb = gap_gatt_srv_on_disconnected_cb,
#if (TEST_CODE==TRUE)
#if (LE_PING_ENABLE==TRUE)
	.iLE_read_authpayload_timeout_cb = NULL,
#endif
#endif
	.iLE_data_len_change_evt_cb = NULL,
};


static gatt_callbacks_t gap_gatt_cb =
{
		.iLE_on_att_mtu_changed_cb = NULL,
		.iLE_on_primary_service_discovered_cb = NULL,
		.iLE_on_included_service_discovered_cb = NULL,
		.iLE_on_characteristic_discovered_cb = NULL,
		.iLE_on_descriptor_discovered_cb = NULL,
		.iLE_on_attribute_read_cb = NULL,
		.iLE_on_attribute_write_cb = NULL,
		.iLE_on_service_added_cb = NULL,
		.iLE_on_include_service_added_cb = gap_gatt_on_service_started_cb,
		.iLE_on_service_removed_cb = gap_gatt_on_service_removed_cb,
		.iLE_on_characteristic_added_cb = gatt_gap_on_attribute_added_cb,
		.iLE_on_descriptor_added_cb = gatt_gap_on_attribute_added_cb,
		.iLE_on_notification_cb = NULL,
		.iLE_on_notification_registered_cb = NULL,
		.iLE_on_indication_confirmation_cb = NULL,
		.iLE_on_attribute_read_req_cb = gap_gatt_srv_on_attribute_read_req_cb,
		.iLE_on_attribute_write_req_cb = gap_gatt_srv_on_attribute_write_req_cb,
		.iLE_on_service_started_cb = gap_gatt_on_service_started_cb,
};


/****************************************************************
 *			GAP GATT Service API's
 ***************************************************************/
void gap_gatt_service_init(char *arg)
{
	logi("");
	memset(&gap_gatt_srv_data, 0, sizeof (gap_gatt_srv_data_t));
	memset (&gap_gatt_srv_data.att_val_map, 0, sizeof (gap_gatt_srv_data.att_val_map));
	memset (&gap_gatt_srv_data.srv_changed_notify_reg_list, 0, sizeof (gap_gatt_srv_data.srv_changed_notify_reg_list));

	if (iLE_register_application(&dev_ctl_cb,&gap_gatt_cb,NULL,NULL,gap_gatt_srv_app_register_cb))
	{
		logd("GAP service application registered");
		return;
	}
}

void gap_gatt_service_cleanup(char *arg)
{
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, gap_gatt_srv_data.app_handle);
	iLE_remove_service(new_trans_id, gap_gatt_srv_data.gap_srv_handle);
	iLE_remove_service(new_trans_id, gap_gatt_srv_data.gatt_srv_handle);
	iLE_deregister_application(gap_gatt_srv_data.app_handle);
}
#endif // GAP_GATT_SRV_APP == TRUE
