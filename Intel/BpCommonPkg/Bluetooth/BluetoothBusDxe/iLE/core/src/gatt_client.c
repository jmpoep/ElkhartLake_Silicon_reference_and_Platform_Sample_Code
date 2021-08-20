/** @file
  GATT (client) leyer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "att.h"
#include "profile_mgr.h"
#include "service_mgr.h"
#include "smp_mgr.h"
#include "config_host.h"
#include "utils.h"
#include "gatt.h"

#define MODULE_DBG_LVL GATT_DBG_LVL
#include "log.h"

/****************************************************************
 *		GATT static utility functions
 ***************************************************************/
#if (GATT_CLIENT_SUPPORTED == TRUE)
static INT8 gatt_discover_all_chars(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);
static INT8 gatt_discover_prim_srv_by_uuid(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t* filter_uuid);
static INT8 gatt_desc_discovery(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);
static void gatt_discover_chars_cb(UINT8 conn_id, buffer_t *buffer);
static void gatt_read_char_using_uuid_cb(UINT8 conn_id, buffer_t* buffer);

/****************************************************************
 * 	GATT Static functions
 ***************************************************************/

static void set_device_data_uuid(UINT8 conn_id, uuid_t* uuid)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	if (uuid)
		memcpy (&device->gatt_device_data.uuid_discover, uuid, sizeof (uuid_t));
	else
		memset (&device->gatt_device_data.uuid_discover, 0, sizeof (uuid_t));
}

static uuid_t* get_device_data_uuid(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
#if (PARANOID_STACK == TRUE)
	if (!device)
		return NULL;
#endif
	return &device->gatt_device_data.uuid_discover;
}

static void set_device_data_saved_handle(UINT8 conn_id, UINT16 handle)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	device->gatt_device_data.saved_handle = handle;
}

static UINT16 get_device_data_saved_handle(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return FALSE;

	return device->gatt_device_data.saved_handle;
}

static void set_device_data_on_going_proc(UINT8 conn_id, UINT8 on_going_proc)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	device->gatt_device_data.on_going_proc = on_going_proc;
}

static UINT8 get_device_data_on_going_proc(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return FALSE;

	return device->gatt_device_data.on_going_proc;
}

static INT8 gatt_discover_prim_srv_by_uuid(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t* filter_uuid)
{
	INT8 ret;
#if (PARANOID_STACK == TRUE)
	if (start_handle > end_handle)
		return STATUS_ERR_INVALID_PARAM;
#endif
	ret = att_find_by_type_val_req(conn_id, start_handle, end_handle, GATT_UUID_PRIM_SRV, filter_uuid);
	if (ret == STATUS_SUCCESS)
		set_device_data_uuid(conn_id, filter_uuid);
	return ret;
}

static INT8 gatt_discover_all_prim_srv(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret;
	if (start_handle > end_handle)
		return STATUS_ERR_INVALID_PARAM;

	ret = att_read_by_group_type_req(conn_id, start_handle, end_handle, GATT_UUID_PRIM_SRV);
	if (ret == STATUS_SUCCESS)
		set_device_data_saved_handle(conn_id, end_handle);
	return ret;
}

static INT8 gatt_discover_all_incl_srv(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	uuid_t uuid;
	UINT16_TO_UUID(GATT_UUID_INCLUDED_SRV, uuid);
	return att_read_by_type_req(conn_id, start_handle, end_handle, &uuid);
}

/**
 * Discovery request for all characteristics of service with service_uuid.
 *
 * This service has to be discovered prior to discover the characteristics
 */
static INT8 gatt_discover_all_chars(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	uuid_t uuid;
	UINT16_TO_UUID(GATT_UUID_CHARACTERISTIC, uuid);
	return att_read_by_type_req(conn_id, start_handle, end_handle, &uuid);
}

static INT8 gatt_discover_char_by_uuid(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t* filter_uuid)
{
	INT8 ret = gatt_discover_all_chars(conn_id, start_handle, end_handle);
	if (ret == STATUS_SUCCESS)
		set_device_data_uuid(conn_id, filter_uuid);
	return ret;
}

static INT8 gatt_desc_discovery(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret;
	if (start_handle > end_handle)
		return STATUS_ERR_INVALID_PARAM;
	ret = att_find_info_req(conn_id, start_handle, end_handle);
	if (ret == STATUS_SUCCESS)
		set_device_data_saved_handle(conn_id, end_handle);
	return ret;
}

static void gatt_discover_incl_srv_cb(UINT8 conn_id, buffer_t *in_buffer)
{

	UINT16 length_of_each_inc_srv, num_of_inc_srv, i;
	UINT8 *p;
	uuid_t uuid;
	UINT16 next_handle, start_handle, end_handle, inc_handle = END_HANDLE - 1;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (in_buffer == NULL )
	{
		loge("device is null");
		return;
	}
#endif
	p = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT8(length_of_each_inc_srv, p);

	if (length_of_each_inc_srv == 0)
		return;

	in_buffer->length --;
	in_buffer->offset ++;
	num_of_inc_srv = in_buffer->length / length_of_each_inc_srv;
	for (i = 0; i < num_of_inc_srv; i++)
	{
		STREAM_TO_UINT16(inc_handle, p);
		STREAM_TO_UINT16(start_handle, p);
		STREAM_TO_UINT16(end_handle, p);
		if(length_of_each_inc_srv == 8)
		{
			/* UUID of the included service is added in response pkt
			 * so read the included service UUID else it is application
			 * responsibility to read the UUID
			 */
			UINT16 uuid16;
			STREAM_TO_UINT16(uuid16, p);
			UINT16_TO_UUID(uuid16, uuid);
		}
		else
		{
			uuid.length = 0;
		}

		/**
		 * For the next included service discovery request set the start handle as
		 * next to characteristic value handle.
		 */
		pm_included_service_discovered_cb(conn_id, inc_handle, start_handle, end_handle, &uuid, FALSE);
	}
	next_handle = inc_handle + 1;
	if (get_device_data_saved_handle(conn_id) < next_handle)
	{
		set_device_data_saved_handle(conn_id, 0);
		pm_included_service_discovered_cb(conn_id, 0, 0, 0, NULL, TRUE);
	}
	else
	{
		gatt_discover_all_incl_srv(conn_id, next_handle, get_device_data_saved_handle(conn_id));
	}
}

/**
 * called when we were performing characteristic discovery and we got a response
 * for read by type request.
 */
static void gatt_discover_chars_cb(UINT8 conn_id, buffer_t *in_buffer)
{
	UINT8 length_of_each_hdl_val_pair;
	UINT16 num_of_hdl_val_pair, i;
	uuid_t *filter_uuid;
	UINT8 *p;
	UINT8 uuid_length;
	UINT16 handle, value_handle, next_handle = END_HANDLE;
	UINT8 property;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (in_buffer == NULL )
	{
		loge("device is null");
		return;
	}
#endif
	filter_uuid = get_device_data_uuid(conn_id);
	if (!filter_uuid)
		return;

	p = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT8(length_of_each_hdl_val_pair, p);

	if (length_of_each_hdl_val_pair <= 5)
		return;

	in_buffer->length --;
	in_buffer->offset ++;
	num_of_hdl_val_pair = in_buffer->length / length_of_each_hdl_val_pair;

	uuid_length = length_of_each_hdl_val_pair - 5;
	for (i = 0; i < num_of_hdl_val_pair; i++)
	{
		uuid_t uuid;
		STREAM_TO_UINT16(handle, p);
		STREAM_TO_UINT8(property, p);
		STREAM_TO_UINT16(value_handle, p);
		/**
		 * Parse UUID depending of the length of the packet.
		 */
		switch(uuid_length)
		{
		case UUID_16BIT_TYPE_LEN:
		{
			UINT16 uuid16;
			STREAM_TO_UINT16(uuid16, p);
			UINT16_TO_UUID(uuid16, uuid);
		}
			break;
		case UUID_32BIT_TYPE_LEN:
		{
			UINT32 uuid32;
			STREAM_TO_UINT32(uuid32, p);
			UINT32_TO_UUID(uuid32, uuid);
		}
			break;
		case UUID_128BIT_TYPE_LEN:
		{
			uuid.length = UUID_128BIT_TYPE_LEN;
			REVERSE_STREAM_TO_ARRAY(uuid.value.uuid128, p, UUID_128BIT_TYPE_LEN);
		}
			break;
		default:
			return;
		}
		if ((!filter_uuid->length) || (uuidcmp(filter_uuid, &uuid)))
			pm_characteristic_discovered_cb(conn_id, property, handle, value_handle, &uuid, FALSE);
		/**
		 * For the next characteristic discovery request set the start handle as
		 * next to characteristic value handle.
		 */
		next_handle = handle + 1;
	}
	if (get_device_data_saved_handle(conn_id) < next_handle)
	{
		set_device_data_saved_handle(conn_id, 0);
		set_device_data_uuid(conn_id, NULL);
		pm_characteristic_discovered_cb(conn_id, 0, 0, 0, NULL, TRUE);
	}
	else
	{
		if (!filter_uuid->length)
			gatt_discover_all_chars(conn_id, next_handle, get_device_data_saved_handle(conn_id));
		else
			gatt_discover_char_by_uuid(conn_id, next_handle, get_device_data_saved_handle(conn_id), filter_uuid);
	}
}

static void gatt_read_char_using_uuid_cb(UINT8 conn_id, buffer_t* in_buffer)
{
	UINT16 value_handle;
	UINT8 *p;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	p = in_buffer->data + in_buffer->offset;
	//STREAM_TO_UINT8(pkt_len, p);
	JUMP_CUSTOM_LEN(p, 1);
	STREAM_TO_UINT16(value_handle, p);
	in_buffer->length -= 3;
	in_buffer->offset += 3;
	pm_on_read_attribute_cb(conn_id, ATT_OPCODE_READ_BY_TYPE_RESP, ATT_SUCCESS, value_handle, in_buffer);
}
#if (SIGNED_WRITE)
static interface_req_elem_t* prepare_sign_data_req(UINT8 conn_id, UINT16 att_id, buffer_t *in_buffer)
{
	interface_req_elem_t* req;
	smpm_sign_data_param_t* param;
	UINT8 *p;

#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return NULL;
#endif
	req = (interface_req_elem_t*)get_interface_req_buffer(API_REQ_OPCODE_SIGN_DATA, 0, sizeof(smpm_sign_data_param_t) + in_buffer->length + 3);
	if(req == NULL)
		return NULL;
	param = (smpm_sign_data_param_t*)req->parameter;
	param->app_handle = (UINT8) INVALID_INDEX;
	param->device = get_connected_device_by_conn_id(conn_id);
	param->cback = pm_data_signing_complete_cb;
	p = param->data;
	*p = ATT_OPCODE_SIGN_WRITE_CMD;
	p++;
	UINT16_TO_STREAM(p, att_id);
	memcpy(p, in_buffer->data+in_buffer->offset, in_buffer->length);
	param->data_len = (in_buffer->length+3);
	return req;
}
#endif /* SIGNED_WRITE */
/****************************************************************
 * 							GATT APIs
 ***************************************************************/

INT8 gatt_discover_primary_service(UINT8 conn_id, uuid_t *filter_uuid)
{
	INT8 ret = STATUS_ERR_UNKNOWN;

	if (filter_uuid->length == UUID_NULL_LEN)
	{
		ret = gatt_discover_all_prim_srv(conn_id, START_HANDLE, END_HANDLE);
	}
	else
	{
		ret = gatt_discover_prim_srv_by_uuid(conn_id, START_HANDLE, END_HANDLE, filter_uuid);
		if (ret == STATUS_SUCCESS)
		{
			set_device_data_uuid(conn_id, filter_uuid);
		}
	}
	return ret;
}

INT8 gatt_discover_included_service(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret = gatt_discover_all_incl_srv(conn_id, start_handle, end_handle);
	if (ret == STATUS_SUCCESS)
	{
		set_device_data_saved_handle(conn_id, end_handle);
		set_device_data_on_going_proc(conn_id, GATT_OPERATION_DISCOVER_INCLUDED_SERVICE);
	}
	return ret;
}

INT8 gatt_discover_characteristic(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid)
{
	INT8 ret = STATUS_ERR_UNKNOWN;

	if (filter_uuid->length == UUID_NULL_LEN)
	{
		set_device_data_uuid(conn_id, NULL);
		ret = gatt_discover_all_chars(conn_id, start_handle, end_handle);
	}
	else
	{
		ret = gatt_discover_char_by_uuid(conn_id, start_handle, end_handle, filter_uuid);
		if (ret == STATUS_SUCCESS)
		{
			set_device_data_uuid(conn_id, filter_uuid);
		}
	}
	if (ret == STATUS_SUCCESS)
	{
		set_device_data_saved_handle(conn_id, end_handle);
		set_device_data_on_going_proc(conn_id, GATT_OPERATION_DISCOVER_CHARACTERISTIC);
	}
	return ret;
}

INT8 gatt_discover_descriptor(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret = STATUS_ERR_UNKNOWN;

	ret = gatt_desc_discovery(conn_id, start_handle, end_handle);
	if (ret == STATUS_SUCCESS)
	{
		set_device_data_saved_handle(conn_id, end_handle);
	}
	return ret;
}

INT8 gatt_read_attribute_value(UINT8 conn_id, UINT16 att_opcode, UINT16 att_id, UINT16 offset)
{
	INT8 ret = STATUS_ERR_INVALID_PARAM;
	if (att_opcode == ATT_OPCODE_READ_REQ)
	{
		ret = att_read_req(conn_id, att_id);
	}
	else if (att_opcode == ATT_OPCODE_READ_BLOB_REQ)
	{
		ret = att_read_blob_req(conn_id, att_id, offset);
	}
	if (ret == STATUS_SUCCESS)
	{
		set_device_data_saved_handle(conn_id, att_id);
	}
	return ret;
}

INT8 gatt_read_characteristic_value_using_uuid(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *char_uuid)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
#if (PARANOID_STACK == TRUE)
	if (start_handle > end_handle)
		return STATUS_ERR_INVALID_PARAM;
#endif
	ret = att_read_by_type_req(conn_id, start_handle, end_handle, char_uuid);
	if (ret == STATUS_SUCCESS)
	{
		set_device_data_on_going_proc(conn_id, GATT_OPERATION_READ_ATTRIBUTE);
	}
	return ret;
}

INT8 gatt_read_multiple_characteristic_value(UINT8 conn_id, UINT16 *handle_list)
{

		INT8 ret;
	#if (PARANOID_STACK == TRUE)
		if (!handle_list)
			return STATUS_ERR_INVALID_PARAM;
	#endif

		ret = att_read_multiple_req(conn_id, handle_list);

		if (ret == STATUS_SUCCESS)
		{
			set_device_data_on_going_proc(conn_id, GATT_OPERATION_READ_MULTIPLE_CHARACTERISTIC);
		}
		return ret;
}

INT8 gatt_write_attribute_command(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, buffer_t* buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif
	switch (att_opcode)
	{
		case ATT_OPCODE_WRITE_CMD:
			ret = att_write_command(conn_id, att_id, buffer);
			break;
		case ATT_OPCODE_SIGN_WRITE_CMD:
		{
#if (SIGNED_WRITE)
			 /*Call SMPM layer to generate the signature*/
			ret = smpm_req_handler(prepare_sign_data_req(conn_id, att_id, buffer));
#endif /* SIGNED_WRITE */
		}
			break;
	}
	return ret;
}

INT8 gatt_write_attribute_value(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer)
{
	UINT16 mtu_size;
	INT8 ret;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif
	mtu_size = get_device_mtu(conn_id);
	switch (att_opcode)
	{
		case ATT_OPCODE_WRITE_REQ:
		{
			/* If applicaion sent more than mtu. Send only MTU bytes */
			buffer->length = (buffer->length > (mtu_size - ATT_WRITE_REQ_LEN)) ? (mtu_size - ATT_WRITE_REQ_LEN) : buffer->length;
			if((ret = att_write_req(conn_id, att_id, buffer)) == STATUS_SUCCESS)
			{
				set_device_data_saved_handle(conn_id, att_id);
				return ret;
			}
		}
			break;
		case ATT_OPCODE_PREP_WRITE_REQ:
		{
			/* If applicaion sent more than mtu. Send only MTU bytes */
			buffer->length = (buffer->length > (mtu_size - ATT_PREPARE_WRITE_REQ_LEN)) ? (mtu_size - ATT_PREPARE_WRITE_REQ_LEN) : buffer->length;
			return att_prepare_write_req(conn_id, att_id, offset, buffer);
		}
		case ATT_OPCODE_EXEC_WRITE_REQ:
		{
			return att_execute_write_req(conn_id, *(buffer->data));
		}
	}

	return STATUS_ERR_UNKNOWN;
}

INT8 gatt_send_signed_write(UINT8 conn_id, UINT16 att_id, buffer_t* buffer, UINT8* signature)
{
	/*UINT16 handle = (attribute.attr_type == ATTR_TYPE_CHARACTERISTIC) ? attribute.attr.characteristic->value_handle :
			attribute.attr.descriptor->handle;*/
	return att_signed_write_cmd(conn_id, att_id, buffer, signature);
}

INT8 gatt_send_indication_confirmation(UINT8 conn_id)
{
	return att_send_handle_val_cfm(conn_id);
}

INT8 gatt_request_mtu(UINT8 conn_id, UINT16 mtu_size)
{
	if ((mtu_size >= ATT_MIN_MTU_LEN) && (mtu_size <= ATT_MAX_MTU_LEN))
	{
		connected_device_t *device = get_connected_device_by_conn_id(conn_id);

		if (!device)
			return STATUS_ERR_INVALID_PARAM;

		if((!device->att_device.mtu_exchange_done) ||
				(device->att_device.mtu_exchange_done && (mtu_size < device->att_device.att_mtu_size)))
		{
			device->att_device.att_request_mtu_size = mtu_size;
			device->att_device.mtu_exchange_done = TRUE;
			return att_mtu_xchange_req(conn_id, mtu_size);
		}
	}
	return STATUS_ERR_LAYER_SPECIFIC;
}

/****************************************************************
 * 							GATT Client call backs
 ***************************************************************/
void gatt_client_connect_cb(connected_device_t* device)
{
	uuid_t empty_uuid;
	logi("");
	/* Initialise the device data structures */
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
	UINT16_TO_UUID(0, empty_uuid);
	memcpy (&device->gatt_device_data.uuid_discover, &empty_uuid, sizeof(uuid_t));
}

void gatt_client_disconnect_cb(connected_device_t* device)
{

}

INT8 gatt_handle_mtu_resp_cb(UINT8 conn_id, buffer_t *in_buffer)
{
	UINT8 *p_input_buffer;
	UINT16 remote_mtu;
	connected_device_t *device;
#if (PARANOID_STACK == TRUE)
	if(!in_buffer || (in_buffer && in_buffer->length < 2))
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif
	p_input_buffer = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(remote_mtu, p_input_buffer);

	device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	/*
	 * Same strategy is applicable as specified in above function.
	 */
	remote_mtu = (remote_mtu < ATT_MIN_MTU_LEN) ? ATT_MIN_MTU_LEN : remote_mtu;

	/* We had sent the max mtu in the request. So store whatever is minimum. */
	device->att_device.att_mtu_size = (device->att_device.att_request_mtu_size < remote_mtu) ? device->att_device.att_request_mtu_size : remote_mtu;

	pm_att_mtu_changed_cb(conn_id, device->att_device.att_mtu_size);

	return STATUS_SUCCESS;
}

void gatt_error_resp_cb(UINT8 conn_id, UINT8 req_opcode, UINT16 att_handle, UINT8 err_code)
{
	switch (req_opcode)
	{
	case ATT_OPCODE_FIND_BY_TYPE_VAL_REQ:
	{
		pm_primary_service_discovered_cb(conn_id, 0, 0, NULL, TRUE);
		set_device_data_uuid(conn_id, NULL);
	}
		break;
	case ATT_OPCODE_READ_BY_TYPE_REQ:
	{
		UINT8 on_going_proc = get_device_data_on_going_proc(conn_id);
		set_device_data_on_going_proc(conn_id, GATT_OPERATION_IDLE);

		if (on_going_proc == GATT_OPERATION_DISCOVER_CHARACTERISTIC)
		{
			set_device_data_saved_handle(conn_id, 0);
			set_device_data_uuid(conn_id, NULL);
			pm_characteristic_discovered_cb(conn_id, 0, 0, 0, NULL, TRUE);
		}
		else if (on_going_proc == GATT_OPERATION_READ_ATTRIBUTE)
		{
			pm_on_read_attribute_cb(conn_id, req_opcode, err_code, att_handle, NULL);
		}
		else if (on_going_proc == GATT_OPERATION_DISCOVER_INCLUDED_SERVICE)
		{
			pm_included_service_discovered_cb(conn_id, 0, 0, 0, NULL, TRUE);
		}
	}
		break;
	case ATT_OPCODE_FIND_INFO_REQ:
	{
		set_device_data_on_going_proc(conn_id, GATT_OPERATION_IDLE);
		pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
	}
		break;
	case ATT_OPCODE_READ_REQ:
	case ATT_OPCODE_READ_BLOB_REQ:
	case ATT_OPCODE_READ_MULTI_REQ:
	{
		pm_on_read_attribute_cb(conn_id, req_opcode, err_code, att_handle, NULL);
	}
		break;
	case ATT_OPCODE_WRITE_REQ:
	case ATT_OPCODE_PREP_WRITE_REQ:
	case ATT_OPCODE_EXEC_WRITE_REQ:
	{
		logd("err_code:%d", err_code);
		pm_on_attribute_write_cb(conn_id, req_opcode, err_code, att_handle, 0, NULL);
	}
		break;
	case ATT_OPCODE_READ_BY_GRP_TYPE_REQ:
	{
		pm_primary_service_discovered_cb(conn_id, 0, 0, NULL, TRUE);
	}
	break;
	case ATT_OPCODE_WRITE_CMD:
	case ATT_OPCODE_SIGN_WRITE_CMD:
	default:
	{
		logw("Unknown req opcode:%x", req_opcode);
	}
		break;
	}
}

void gatt_discover_prim_srv_by_uuid_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	INT16 i, num_of_handles ;
	UINT8* p ;
	UINT16 next_handle;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	num_of_handles = (in_buffer->length) / GATT_ELEM_LEN_PRIM_SRV_BY_UUID_DISC;
	next_handle = END_HANDLE;
	p = in_buffer->data + in_buffer->offset;
	for (i = 0; i < num_of_handles; i++)
	{
		UINT16 start_handle, end_handle;
		STREAM_TO_UINT16(start_handle, p);
		STREAM_TO_UINT16(end_handle, p);
		next_handle = end_handle + 1; // Set the handle for the next request
		pm_primary_service_discovered_cb(conn_id, start_handle, end_handle, get_device_data_uuid(conn_id), FALSE);
	}
	if (next_handle != END_HANDLE)
		gatt_discover_prim_srv_by_uuid(conn_id, next_handle, END_HANDLE, get_device_data_uuid(conn_id));
	else
	{
		pm_primary_service_discovered_cb(conn_id, 0, 0, NULL, TRUE);
		set_device_data_uuid(conn_id, NULL);
	}
}

void gatt_read_by_group_type_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	UINT8 *p ;
	UINT16 next_handle;
	UINT8 length_of_each_elem;
	UINT8 attr_val_len;
	UINT16 i, num_of_attr_data;

#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	p = in_buffer->data + in_buffer->offset;
	next_handle = END_HANDLE;
	STREAM_TO_UINT8(length_of_each_elem, p);
	in_buffer->length --;
	in_buffer->offset ++;
	num_of_attr_data = in_buffer->length / length_of_each_elem;
	attr_val_len = length_of_each_elem - 4; /* sizeof (start_handle) + sizeof (end_handle) */
	for (i = 0; i < num_of_attr_data; i++)
	{
		UINT16 start_handle, end_handle;
		uuid_t uuid;
		STREAM_TO_UINT16(start_handle, p);
		STREAM_TO_UINT16(end_handle, p);
		uuid.length = attr_val_len;
		/**
		 * Parse the UUID according to the length.
		 */
		switch(uuid.length)
		{
		case UUID_16BIT_TYPE_LEN:
			STREAM_TO_UINT16(uuid.value.uuid16, p);
			break;
		case UUID_32BIT_TYPE_LEN:
			STREAM_TO_UINT32(uuid.value.uuid32, p);
			break;
		case UUID_128BIT_TYPE_LEN:
			REVERSE_STREAM_TO_ARRAY(uuid.value.uuid128, p, UUID_128BIT_TYPE_LEN)
			break;
		}
		if (end_handle < start_handle)
			continue;

		pm_primary_service_discovered_cb(conn_id, start_handle, end_handle, &uuid, FALSE);

		if (end_handle != END_HANDLE)
			next_handle = end_handle + 1; // Set handle for the next service discovery request
		else
			next_handle = END_HANDLE; // Service discovery done.
	}
	if (next_handle != END_HANDLE)
		gatt_discover_all_prim_srv(conn_id, next_handle, END_HANDLE); // Send another service discovery request.
	else
		pm_primary_service_discovered_cb(conn_id, 0, 0, NULL, TRUE);
}

void gatt_read_by_type_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	if (get_device_data_on_going_proc(conn_id) == GATT_OPERATION_DISCOVER_CHARACTERISTIC)
		gatt_discover_chars_cb(conn_id, in_buffer);
	else if (get_device_data_on_going_proc(conn_id) == GATT_OPERATION_READ_ATTRIBUTE)
		gatt_read_char_using_uuid_cb(conn_id, in_buffer);
	else if (get_device_data_on_going_proc(conn_id) == GATT_OPERATION_DISCOVER_INCLUDED_SERVICE)
		gatt_discover_incl_srv_cb(conn_id, in_buffer);
}

void gatt_discover_desc_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	UINT8 *p;
	UINT8 uuid_format;
	UINT16 num_of_desc = 0, iterator;
	UINT16 next_handle = 0;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	p = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT8(uuid_format, p);
	in_buffer->length --;
	in_buffer->offset ++;
	if (uuid_format == BT_16_BIT_UUID_FORMAT)
	{
		if (in_buffer->length < 4)
		{
			pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
			return;
		}
		num_of_desc = in_buffer->length / 4; /* Size of (handle): 2 + Size of (UUID): 2 */
	}
	else if (uuid_format == BT_128_BIT_UUID_FORMAT)
	{
		if (in_buffer->length < 18)
		{
			pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
			return;
		}
		num_of_desc = in_buffer->length / 18; /* Size of (handle): 2 + Size of (UUID): 16 */
	}
	else
	{
		pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
		return;
	}
	logd("num_of_desc: %d", num_of_desc);
	for (iterator = 0; iterator < num_of_desc; iterator++)
	{
		/**
		 * Parse the descriptors present in the packet.
		 */
		UINT16 handle;
		uuid_t uuid;
		STREAM_TO_UINT16(handle, p);
		switch (uuid_format)
		{
		case BT_16_BIT_UUID_FORMAT:
		{
			UINT16 uuid16;
			STREAM_TO_UINT16(uuid16, p);
			UINT16_TO_UUID(uuid16, uuid);
		}
			break;
		case BT_128_BIT_UUID_FORMAT:
		{
			uuid.length = UUID_128BIT_TYPE_LEN;
			REVERSE_STREAM_TO_ARRAY(uuid.value.uuid128, p, UUID_128BIT_TYPE_LEN);
			p += UUID_128BIT_TYPE_LEN;
		}
			break;
		default:
		{
			logw("Unknown uuid format.");
			pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
			return;
		}
		}
		pm_descriptor_discovered_cb(conn_id, handle, &uuid, FALSE);
		next_handle = handle + 1;
	}
	/* Find out the handle for next discriptor discovery request */
	if (gatt_desc_discovery(conn_id, next_handle, get_device_data_saved_handle(conn_id)) == STATUS_ERR_INVALID_PARAM)
	{
		pm_descriptor_discovered_cb(conn_id, 0, NULL, TRUE);
	}
}

void gatt_read_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	pm_on_read_attribute_cb(conn_id, att_opcode, ATT_SUCCESS, get_device_data_saved_handle(conn_id), in_buffer);
}

void gatt_read_multiple_rsp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{

	if (get_device_data_on_going_proc(conn_id) == GATT_OPERATION_READ_MULTIPLE_CHARACTERISTIC)
	{
		/* Read multiple attribute completed. Let profile manager know.*/

		set_device_data_on_going_proc(conn_id, GATT_OPERATION_IDLE);
		pm_on_read_attribute_cb(conn_id, att_opcode, ATT_SUCCESS, get_device_data_saved_handle(conn_id), in_buffer);
	}
}

void gatt_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	pm_on_attribute_write_cb(conn_id, att_opcode, ATT_SUCCESS, get_device_data_saved_handle(conn_id), 0, in_buffer);
}

void gatt_prep_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	UINT8 *p;
	UINT16 att_handle, value_offset;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	p = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(att_handle, p);
	STREAM_TO_UINT16(value_offset, p);
	in_buffer->length -= 4;
	in_buffer->offset += 4;

	pm_on_attribute_write_cb(conn_id, att_opcode, ATT_SUCCESS, att_handle, value_offset, in_buffer);
}

void gatt_exec_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	pm_on_attribute_write_cb(conn_id, att_opcode, ATT_SUCCESS, 0, 0, NULL);
}

void gatt_notify_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer)
{
	UINT8 *p ;
	UINT16 att_handle;

#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	p = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(att_handle, p);
	in_buffer->offset += 2;
	in_buffer->length -= 2;

	if (att_opcode == ATT_OPCODE_HANDLE_VAL_IND)
		gatt_send_indication_confirmation(conn_id);

	/* We received a notification. Let profile manager know this. */
	pm_on_characteristic_notification_cb(conn_id, att_handle, in_buffer, (att_opcode == ATT_OPCODE_HANDLE_VAL_IND) ? TRUE : FALSE);
}

void gatt_client_timeout_cb(UINT8 conn_id, UINT8 state)
{
	/*
	 * GATT client timeout. Disconnect this ATT channel.
	 */
	logi("");
	pm_gatt_client_timeout_cb(conn_id);
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE */
