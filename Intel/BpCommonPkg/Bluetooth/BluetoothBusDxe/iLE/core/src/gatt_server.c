/** @file
  GATT (server) leyer implementation.

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
#if (GATT_SERVER_SUPPORTED == TRUE)
static UINT8 check_attr_read_permission(UINT8 conn_id, UINT16 permission);
static UINT8 check_attr_write_permission(UINT8 conn_id, UINT16 permission);
#endif /* GATT_SERVER_SUPPORTED == TRUE */

/****************************************************************
 * 	GATT Static functions
 ***************************************************************/

static UINT8 get_attr_type_frm_uuid(UINT16 start_handle, UINT16 end_handle, uuid_t *uuid)
{
	uuid_t cmp_uuid;
	UINT16 att_hdl, att_idx, att_hdl_end = MIN (end_handle, MAX_NUM_ATTR - 1);
	UINT16_TO_UUID(ATTR_UUID_PRIMARY_SERVICE, cmp_uuid);
	if (uuidcmp(uuid, &cmp_uuid) == TRUE)
		return ATTR_TYPE_PRIMARY_SERVICE;
	UINT16_TO_UUID(ATTR_UUID_INCLUDE_SERCICE, cmp_uuid);
	if (uuidcmp(uuid, &cmp_uuid) == TRUE)
		return ATTR_TYPE_INCLUDED_SERVICE;
	UINT16_TO_UUID(ATTR_UUID_CHARACTERISTIC, cmp_uuid);
	if (uuidcmp(uuid, &cmp_uuid) == TRUE)
		return ATTR_TYPE_CHARACTERISTIC;

	for (att_hdl = MIN(start_handle, MAX_NUM_ATTR - 1); att_hdl <= att_hdl_end; att_hdl++)
	{
		gatt_attribute_t *attribute;
		att_idx = get_att_idx_from_hdl(att_hdl);
		if (att_idx == MAX_NUM_ATTR)
			continue;
		attribute = &g_local_adapter.attribute_list[att_idx];
		if (uuidcmp(&attribute->uuid, uuid) == TRUE)
		{
			if (attribute->attr_type == ATTR_TYPE_CHARACTERISTIC && att_idx < (MAX_NUM_ATTR - 1))
			{
				if (uuidcmp(&g_local_adapter.attribute_list[att_idx + 1].uuid, uuid) == TRUE)
					return g_local_adapter.attribute_list[att_idx + 1].attr_type;
			}
			else
			{
				return attribute->attr_type; // For value return type_char_value.
			}
		}
	}
	return ATTR_TYPE_INVALID;
}

/*
 * Checks read permission for an attribute(Characteristic Value or Characteristic Descriptor)
 * if security criteria(Encryption,Authentication) is met.
 */
static UINT8 check_attr_read_permission(UINT8 conn_id, UINT16 permission)
{
	connected_device_t* device;

	/* Read allowed without any security */
	if(permission & ATTRIBUTE_PERMISSION_READ)
	{
		return ATT_SUCCESS;
	}

    /* Check if None of the Read permissions enabled */
	if (!(permission & ATTRIBUTE_READ_PERMITTED))
	{
		return ATT_ERR_READ_NOT_PREMITTED;
	}

#if (SMP_FEATURE)
	device = g_local_adapter.connected_device[conn_id];
#if (PARANOID_STACK == TRUE)
	if (!device)
		return ATT_ERR_LOCAL_ERROR;
#endif
	if(device->link_enc_state.state < LINK_ENC_STATE_UPDATED)
	{
		/* Wait for link security info to be updated*/
		loge("Enc state Pending");
		device->link_enc_state.pending_act |= LINK_ATT_PENDING;
		return ATT_ERR_PENDING;
	}
	if(device->link_enc_state.state < LINK_ENC_STATE_ENCRYPTED)
	{
		/* Link is not encrypted */
		if(device->local_link_role && (device->link_enc_state.keys_distributed & SMP_LTK_DISTRIBUTED))
			return ATT_ERR_INSUFF_ENCR;
		if(!device->local_link_role && (device->link_enc_state.keys_distributed & SMP_LTK_RECEIVED))
			return ATT_ERR_INSUFF_ENCR;
		return ATT_ERR_INSUFF_AUTHENTICATION;
	}
	else
	{
		/* Read allowed with encryption and no authentication(MITM) */
		if(permission & ATTRIBUTE_PERMISSION_READ_ENC_NO_MITM)
		{
			if(device->link_enc_state.key_size < GET_READ_KEY_SIZE(permission))
			{
				return ATT_ERR_INSUFF_ENCR_KEY_SIZE;
			}
			return ATT_SUCCESS;
		}
		/* Read allowed with encryption and authentication(MITM) */
		if(permission & ATTRIBUTE_PERMISSION_READ_ENC_MITM)
		{
			if(device->link_enc_state.secuirty_level < 2)
			{
				return ATT_ERR_INSUFF_AUTHENTICATION;
			}
			else
			{
				if(device->link_enc_state.key_size < GET_READ_KEY_SIZE(permission))
				{
					return ATT_ERR_INSUFF_ENCR_KEY_SIZE;
				}
				return ATT_SUCCESS;
			}
		}
	}

	return ATT_ERR_LOCAL_ERROR;
#else
	return ATT_SUCCESS;
#endif /* SMP_FEATURE */
}

void gatt_server_timeout_cb(UINT8 conn_id)
{
	logi("");
}

#if (GATT_SERVER_SUPPORTED == TRUE)

static UINT16 get_prep_wr_att_id(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return 0;
	return device->gatt_device_data.prep_wr_att_id;
}

static void set_prep_wr_att_id(UINT8 conn_id, UINT16 att_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return;
	device->gatt_device_data.prep_wr_att_id = att_id;
}

static void set_indication_att_id(UINT8 conn_id, UINT16 att_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return;
	device->gatt_device_data.indication_att_id = att_id;
}

static UINT16 get_indication_att_id(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return 0;
	return device->gatt_device_data.indication_att_id;
}

/*
 * Checks write permission for an attribute(Characteristic Value or Characteristic Descriptor)
 * if security criteria(Encryption,Authentication) is met.
 */
static UINT8 check_attr_write_permission(UINT8 conn_id, UINT16 permission)
{
	/* Write allowed without any security */
	if(permission & ATTRIBUTE_PERMISSION_WRITE)
	{
		return ATT_SUCCESS;
	}

    /* Check if None of the Write permissions enabled */
	if (!(permission & ATTRIBUTE_WRITE_PERMITTED))
	{
		return ATT_ERR_WRITE_NOT_PERMITTED;
	}

#if (SMP_FEATURE)
	connected_device_t* device = g_local_adapter.connected_device[conn_id];
#if (PARANOID_STACK == TRUE)
	if (!device)
		return ATT_ERR_LOCAL_ERROR;
#endif
	if(device->link_enc_state.state < LINK_ENC_STATE_UPDATED)
	{
		/* Wait for link security info to be updated*/
		device->link_enc_state.pending_act |= LINK_ATT_PENDING;
		return ATT_ERR_PENDING;
	}
	if(device->link_enc_state.state < LINK_ENC_STATE_ENCRYPTED)
	{
		/* Link is not encrypted */
		if(device->local_link_role && (device->link_enc_state.keys_distributed & SMP_LTK_DISTRIBUTED))
			return ATT_ERR_INSUFF_ENCR;
		if(!device->local_link_role && (device->link_enc_state.keys_distributed & SMP_LTK_RECEIVED))
			return ATT_ERR_INSUFF_ENCR;
		return ATT_ERR_INSUFF_AUTHENTICATION;
	}
	else
	{
		/* Write allowed with encryption and no authentication(MITM) */
			if(permission & ATTRIBUTE_PERMISSION_WRITE_ENC_NO_MITM)
			{
				if(device->link_enc_state.key_size < GET_WRITE_KEY_SIZE(permission))
				{
					return ATT_ERR_INSUFF_ENCR_KEY_SIZE;
				}
				return ATT_SUCCESS;
			}
			/* Write allowed with encryption and authentication(MITM) */
			if(permission & ATTRIBUTE_PERMISSION_WRITE_ENC_MITM)
			{
				if(device->link_enc_state.secuirty_level < 2)
				{
					return ATT_ERR_INSUFF_AUTHENTICATION;
				}
				else
				{
					if(device->link_enc_state.key_size < GET_WRITE_KEY_SIZE(permission))
					{
						return ATT_ERR_INSUFF_ENCR_KEY_SIZE;
					}
					return ATT_SUCCESS;
				}
			}
	}

	return ATT_ERR_LOCAL_ERROR;
#else
	return ATT_SUCCESS;
#endif /* SMP_FEATURE */
}

#if 0
static gatt_priv_data* get_priv_data(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
#if (PARANOID_STACK == TRUE)
	if (!device)
		return NULL;
#endif
	return device->gatt_device_data.server_priv_data;
}

/**
 * allocates the gatt_priv_data and assigns to server_priv_data
 *
 * Pass att_opcode = 0 to only remove the data.
 */
static INT8 set_priv_data(UINT8 conn_id, UINT8 att_opcode, void* priv_data)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
#if (PARANOID_STACK == TRUE)
	if (!device)
		return STATUS_SUCCESS;
#endif
	if (device->gatt_device_data.server_priv_data)
	{
		dealloc (device->gatt_device_data.server_priv_data);
		device->gatt_device_data.server_priv_data = NULL;
	}

	if(att_opcode == 0)
		return STATUS_SUCCESS;

	device->gatt_device_data.server_priv_data = (gatt_priv_data*) alloc (sizeof (gatt_priv_data));
#if (PARANOID_STACK == TRUE)
	if (!device->gatt_device_data.server_priv_data)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	device->gatt_device_data.server_priv_data->opcode = att_opcode;
	device->gatt_device_data.server_priv_data->prv_data = priv_data;
	logd("set opcode:%d device->gatt_device_data.server_priv_data:%p",
			device->gatt_device_data.server_priv_data->opcode, device->gatt_device_data.server_priv_data);
	return STATUS_SUCCESS;
}
#endif

#if (SIGNED_WRITE)
static interface_req_elem_t* prepare_sign_verify_req(connected_device_t *device, UINT8 opcode,  buffer_t* buffer)
{
	logd("");
	if (!device)
		return NULL;
	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, sizeof(smpm_sign_verify_param_t) + 1);
	interface_req_elem_t* req = (interface_req_elem_t*)get_interface_req_buffer(API_REQ_OPCODE_SIGN_VERIFY, 0, sizeof(smpm_sign_verify_param_t) + buffer->length + 1);
	if(!req)
		return NULL;
	smpm_sign_verify_param_t* param = (smpm_sign_verify_param_t*)req->parameter;
	UINT8 *p = param->data;
	param->app_handle = (UINT8) INVALID_INDEX;
	param->device =device;
	param->cback = sm_sign_verify_complete_cb;
	*p = opcode;
	memcpy(p+1, buffer->data + buffer->offset, buffer->length);
	param->data_len = buffer->length+1;
	return req;
}
#endif /* SIGNED_WRITE */
/**
 * flushes saved handles for multiple read request
 *
 * device : connected device handle
 */
static void flush_saved_multi_read_handle_list(connected_device_t* device)
{
	read_multiple_chars_value_t* cur_char;
	ll_node_t* cur_node = device->gatt_device_data.saved_multi_read_handle_list;
	device->gatt_device_data.saved_multi_read_no_of_handle = 0;
	while(cur_node != NULL)
	{
		cur_char = (read_multiple_chars_value_t*) cur_node->data;
		if(cur_char->buffer != NULL)
		{
			dealloc(cur_char->buffer);
			cur_char->buffer = NULL;
		}
		dealloc(cur_node->data);
		cur_node->data = NULL;
		cur_node = get_next_ll_node(cur_node);
	}
	delete_list(&device->gatt_device_data.saved_multi_read_handle_list);
	device->gatt_device_data.saved_multi_read_handle_list = NULL;
}

/****************************************************************
 * 			GATT Server Call backs
 ***************************************************************/

void gatt_server_connect_cb(UINT8 conn_id)
{
	logi("");
}

void gatt_server_disconnect_cb(UINT8 conn_id)
{
	logi("");
}

void gatt_read_by_group_type_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	/* Discover All primary services */
	UINT16 start_handle;
	UINT16 end_handle;
	UINT16 type_uuid;
	UINT8 attr_type = ATTR_TYPE_ANY;

	logi("");
#if (PARANOID_STACK == TRUE)
	if (in_buffer == NULL || (in_buffer && in_buffer->length < (sizeof(UINT16))))
		return;
#endif
	UINT8 *p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(start_handle, p_input);
	STREAM_TO_UINT16(end_handle, p_input);
	STREAM_TO_UINT16(type_uuid, p_input); //TODO: Extend for 128bit UUIDs
	in_buffer->length -= 6;
	in_buffer->offset += 6;

	if (type_uuid == GATT_UUID_PRIM_SRV)
		attr_type = ATTR_TYPE_PRIMARY_SERVICE;
	else if (type_uuid == GATT_UUID_SEC_SRV)
		attr_type = ATTR_TYPE_SECONDARY_SERVICE;
	else if (type_uuid == GATT_UUID_INCLUDED_SRV)
		attr_type = ATTR_TYPE_INCLUDED_SERVICE;
	else if (type_uuid == GATT_UUID_CHARACTERISTIC)
		attr_type = ATTR_TYPE_CHARACTERISTIC;
	else if (type_uuid == GATT_UUID_CLIENT_CONFIG)
		attr_type = ATTR_TYPE_DESCRIPTOR; //FIXME: All descriptors being treated as CCDs

	/* Data length for this response is (ATT_MTU - 2) */
	UINT16 mtu = get_device_mtu(conn_id) - ATT_READ_BY_GRP_TYPE_RSP_LEN;
	buffer_t *output_buffer = (buffer_t*) alloc(sizeof (buffer_t) + mtu);

	if (!output_buffer)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_UNLIKELY);
		return;
	}

	UINT8 *p_output = output_buffer->data;
	UINT8 elem_size = 0;
	UINT16 att_hdl, att_idx, att_hdl_end = MIN(end_handle, get_max_att_handle());
	for (att_hdl = start_handle; att_hdl < att_hdl_end; att_hdl ++)
	{
		att_idx = get_att_idx_from_hdl(att_hdl);
		if (att_idx == MAX_NUM_ATTR)
			continue;
		gatt_attribute_t *attribute = &g_local_adapter.attribute_list[att_idx];
		if (attribute->attr_type == attr_type)
		{
			logd("cur pkt size:%d mtu:%d", (output_buffer->length + 4 + attribute->uuid.length), mtu);
			if ((output_buffer->length + 4 + attribute->uuid.length) > mtu)
			{
				logd("packet ended for MTU.");
				break;
			}
			if (elem_size == 0)
			{
				elem_size = 4 + attribute->uuid.length;
			}
			else
			{
				if (elem_size != 4 + attribute->uuid.length)
					continue;
			}
			UINT16_TO_STREAM(p_output, att_hdl);
			UINT16_TO_STREAM(p_output, attribute->attr_data.srv_data.end_handle);
			uuid_t *p_uuid = &attribute->uuid;
			UUID_TO_STREAM(p_output, p_uuid);
			output_buffer->length += elem_size;
		}
	}
	if (output_buffer->length == 0)
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_ATTRIB_NOT_FOUND);
	else
		att_send_read_by_grp_type_rsp(conn_id, elem_size, output_buffer);
	dealloc(output_buffer);
}

void gatt_find_by_type_value_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	logi("");
	/* Discover Primary Services By Service UUID */
	UINT16 start_handle;
	UINT16 end_handle;
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(start_handle, p_input);
	in_buffer->length -= 2;
#if (PARANOID_STACK == TRUE)
	if (in_buffer->length < 6)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_INVALID_PDU);
		return;
	}
#endif
	STREAM_TO_UINT16(end_handle, p_input);
	in_buffer->length -= 2;
	uuid_t new_uuid; /* uuid_type */
	get_uuid_from_stream(p_input, UUID_16BIT_TYPE_LEN, &new_uuid);
	UINT8 attribute_type = get_attr_type_frm_uuid(start_handle, end_handle, &new_uuid);
	in_buffer->length -= UUID_16BIT_TYPE_LEN;
	p_input = p_input + UUID_16BIT_TYPE_LEN;
	uuid_t value_to_find; /* uuid_value */
	get_uuid_from_stream(p_input, (UINT8) in_buffer->length, &value_to_find);

	/* Data length for this response is (ATT_MTU - 1) */
	UINT16 mtu = get_device_mtu(conn_id) - ATT_FIND_BY_TYPE_VAL_RSP_LEN;
	buffer_t *output_buffer = (buffer_t*) alloc(sizeof (buffer_t) + mtu);

	if (!output_buffer)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_UNLIKELY);
		return;
	}

	UINT8 *p_output = output_buffer->data;
	UINT16 att_hdl, att_idx, att_hdl_end = MIN(end_handle, get_max_att_handle());

	for (att_hdl = start_handle; att_hdl <= att_hdl_end; att_hdl ++)
	{
		att_idx = get_att_idx_from_hdl(att_hdl);
		if (att_idx == MAX_NUM_ATTR)
			continue;
		gatt_attribute_t *attribute = &(g_local_adapter.attribute_list[att_idx]);
		if (attribute->attr_type == attribute_type)
		{
			if ((attribute->attr_type == ATTR_TYPE_PRIMARY_SERVICE || attribute->attr_type == ATTR_TYPE_INCLUDED_SERVICE)&&
					uuidcmp(&(attribute->uuid), &value_to_find) == TRUE)
			{
				/* Check if 4 bytes for start handle and end handle is available in the buffer */
				if ((output_buffer->length + 4) <= mtu)
				{
					UINT16_TO_STREAM(p_output, att_hdl);
					UINT16_TO_STREAM(p_output, attribute->attr_data.srv_data.end_handle);
					output_buffer->length += 4;
				}
				else
				{
					logd("packet ended for MTU.");
					break;
				}
			}
		}
	}
	if (output_buffer->length == 0)
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_ATTRIB_NOT_FOUND);
	else
		att_send_find_by_type_val_rsp(conn_id, output_buffer);
	dealloc(output_buffer);
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

void gatt_read_by_type_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	/*
	 * Find Included Services
	 * Discover All Characteristic of a service
	 * Discover Characteristic by UUID
	 * Read Using Characteristic UUID
	 */
	UINT16 start_handle;
	UINT16 end_handle;
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	uuid_t attribute_type_uuid;
	UINT8 attribute_type;
	UINT8 elem_length = 0, prev_elem_length = 0;
	UINT16 att_hdl, att_idx;
	UINT16 mtu;
	UINT8 *p_output;
	UINT16 att_hdl_end ;
	buffer_t *output_buffer;

	STREAM_TO_UINT16(start_handle, p_input);
	if (in_buffer->length < (3 * (sizeof(UINT16))))
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_INVALID_PDU);
		return;
	}
	STREAM_TO_UINT16(end_handle, p_input);
	if (start_handle > end_handle || start_handle == 0x0000)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_INVALID_HANDLE);
		return;
	}
	in_buffer->length -= 4;
	get_uuid_from_stream(p_input, (UINT8) in_buffer->length, &attribute_type_uuid);
	attribute_type = get_attr_type_frm_uuid(start_handle, end_handle, &attribute_type_uuid);

	/* Data length for this response is (ATT_MTU - 2) */
	mtu = get_device_mtu(conn_id) - ATT_READ_BY_TYPE_RSP_LEN;
	output_buffer = (buffer_t*) alloc(sizeof(buffer_t) + mtu);

	if (!output_buffer)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_UNLIKELY);
		return;
	}

	p_output = output_buffer->data;
	output_buffer->length = 0;
	att_hdl_end = MIN(end_handle, get_max_att_handle());

	for (att_hdl = start_handle; att_hdl <= att_hdl_end; att_hdl ++)
	{
		gatt_attribute_t *attribute;
		att_idx = get_att_idx_from_hdl(att_hdl);
		if (att_idx == MAX_NUM_ATTR)
			continue;
		attribute = &g_local_adapter.attribute_list[att_idx];
		if (attribute->attr_type == attribute_type)
		{
			switch (attribute->attr_type)
			{
			case ATTR_TYPE_PRIMARY_SERVICE:
			{
				if(attribute->uuid.length == 2)	/* send the UUID only if it is 2 bytes */
					elem_length = sizeof(UINT16) + attribute->uuid.length;
				else
					elem_length = sizeof(UINT16);
				if (!prev_elem_length)
					prev_elem_length = elem_length;
				else if (prev_elem_length != elem_length)
					break;
				if (output_buffer->length + elem_length > mtu)
					break;
				UINT16_TO_STREAM(p_output, attribute->attr_handle);
				if(attribute->uuid.length == 2)	/* send the UUID only if it is 2 bytes */
				{
					uuid_t *p_uuid = &attribute->uuid;
					UUID_TO_STREAM(p_output, p_uuid);
				}
				output_buffer->length += elem_length;
			}
				break;
			case ATTR_TYPE_INCLUDED_SERVICE:
			{
				if(attribute->uuid.length == 2)	/* send the UUID only if it is 2 bytes */
					elem_length = 3 * sizeof(UINT16) + attribute->uuid.length;
				else
					elem_length = 3 * sizeof(UINT16);
				if (!prev_elem_length)
					prev_elem_length = elem_length;
				else if (prev_elem_length != elem_length)
					break;
				if (output_buffer->length + elem_length > mtu)
					break;
				UINT16_TO_STREAM(p_output, att_hdl);
				UINT16_TO_STREAM(p_output, attribute->attr_data.inc_srv_data.start_handle);
				UINT16_TO_STREAM(p_output, attribute->attr_data.inc_srv_data.end_handle);
				if(attribute->uuid.length == 2)	/* send the UUID only if it is 2 bytes */
				{
					uuid_t *p_uuid = &attribute->uuid;
					UUID_TO_STREAM(p_output, p_uuid);
				}
				output_buffer->length += elem_length;
			}
				break;
			case ATTR_TYPE_CHARACTERISTIC:
			{
				uuid_t *p_uuid ;
				elem_length = sizeof(UINT16) + 3 * sizeof(UINT8) + attribute->uuid.length;
				if (!prev_elem_length)
					prev_elem_length = elem_length;
				else if (prev_elem_length != elem_length)
					break;
				if ((output_buffer->length + elem_length) > mtu)
					break;
				UINT16_TO_STREAM(p_output, att_hdl);
				UINT8_TO_STREAM(p_output, attribute->attr_data.char_desc_data.property);
				UINT16_TO_STREAM(p_output, att_hdl + 1);
				p_uuid = &attribute->uuid;
				UUID_TO_STREAM(p_output, p_uuid);
				output_buffer->length += (sizeof(UINT16) + 3 * sizeof(UINT8) + attribute->uuid.length);
			}
				break;
			case ATTR_TYPE_CHARACTERISTIC_VALUE:
			{
				if (uuidcmp(&attribute->uuid, &attribute_type_uuid) == TRUE)
				{
					UINT8 error_code = ATT_SUCCESS;
					if(att_idx > 0)
					{
						if (IS_ATTRIBUTE_PROPERTY_READ(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
							error_code = ATT_ERR_READ_NOT_PREMITTED;
						else
							error_code = check_attr_read_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
					}
					else
						error_code = ATT_ERR_ATTRIB_NOT_FOUND;

					if (error_code == ATT_SUCCESS)
					{
						//set_priv_data(conn_id, opcode, NULL);
						sm_read_attribute(conn_id, opcode, att_hdl, 0);
					}
					else if (error_code == ATT_ERR_PENDING)
					{
						g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
						in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
						g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
						memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
						g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
					}
					else
					{
						att_send_error_response(conn_id, opcode, att_hdl, error_code);
					}
					dealloc(output_buffer);
					return;
				}
			}
				break;

			case ATTR_TYPE_DESCRIPTOR:
			{
				if (uuidcmp(&attribute->uuid, &attribute_type_uuid) == TRUE)
				{
					UINT8 error_code = check_attr_read_permission(conn_id, attribute->attr_data.char_desc_data.permission);
					if (error_code == ATT_SUCCESS)
					{
						//set_priv_data(conn_id, opcode, NULL);
						sm_read_attribute(conn_id, opcode, att_hdl, 0);
					}
					else if (error_code == ATT_ERR_PENDING)
					{
						g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
						in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
						g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
						memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
						g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
					}
					else
					{
						att_send_error_response(conn_id, opcode, att_hdl, error_code);
					}
					dealloc(output_buffer);
					return;
				}
			}
				break;
			}
		}
	}
	if (output_buffer->length == 0)
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_ATTRIB_NOT_FOUND);
	else
		att_send_read_by_type_rsp(conn_id, prev_elem_length, output_buffer);
	dealloc(output_buffer);
}

#if (GATT_SERVER_SUPPORTED == TRUE)

void gatt_find_info_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	/* General usage: Discover All Characteristic Descriptors */
	UINT16 start_handle;
	UINT16 end_handle;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(start_handle, p_input);
	STREAM_TO_UINT16(end_handle, p_input);

	UINT16 att_hdl, att_idx;

	/* Data length for this response is (ATT_MTU - 2) */
	UINT16 mtu = get_device_mtu(conn_id) - ATT_FIND_INFO_RSP_LEN;
	buffer_t *output_buffer = (buffer_t*) alloc(sizeof(buffer_t) + mtu);


	if (!output_buffer)
	{
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_UNLIKELY);
		return;
	}


	UINT8 *p_output = output_buffer->data;
	UINT8 elem_format = 0;
	UINT16 att_hdl_end = MIN(end_handle, get_max_att_handle());
	for (att_hdl = start_handle; att_hdl <= att_hdl_end; att_hdl ++)
	{
		att_idx = get_att_idx_from_hdl(att_hdl);
		if (att_idx == MAX_NUM_ATTR)
			continue;
		gatt_attribute_t *attribute = &g_local_adapter.attribute_list[att_idx];
		UINT8 cur_elem_format;
		if (attribute->uuid.length == UUID_16BIT_TYPE_LEN)
			cur_elem_format = BT_16_BIT_UUID_FORMAT;
		else if (attribute->uuid.length == UUID_128BIT_TYPE_LEN)
			cur_elem_format = BT_128_BIT_UUID_FORMAT;
		else
			break;
		if (elem_format == 0)
			elem_format = cur_elem_format;
		else if (elem_format != cur_elem_format)
			break;
		if ((output_buffer->length + attribute->uuid.length + sizeof (UINT16)) > mtu)
			break;
		UINT16_TO_STREAM(p_output, att_hdl);
		if (attribute->attr_type == ATTR_TYPE_PRIMARY_SERVICE)
		{
			uuid_t temp_uuid;
			UINT16_TO_UUID(ATTR_UUID_PRIMARY_SERVICE, temp_uuid);
			uuid_t *p_uuid = &temp_uuid;
			UUID_TO_STREAM(p_output, p_uuid);
			output_buffer->length += 2 + sizeof (UINT16);
		}
		else if (attribute->attr_type == ATTR_TYPE_INCLUDED_SERVICE)
		{
			uuid_t temp_uuid;
			UINT16_TO_UUID(ATTR_UUID_INCLUDE_SERCICE, temp_uuid);
			uuid_t *p_uuid = &temp_uuid;
			UUID_TO_STREAM(p_output, p_uuid);
			output_buffer->length += 2 + sizeof (UINT16);
		}
		else if (attribute->attr_type == ATTR_TYPE_CHARACTERISTIC)
		{
			uuid_t temp_uuid;
			UINT16_TO_UUID(ATTR_UUID_CHARACTERISTIC, temp_uuid);
			uuid_t *p_uuid = &temp_uuid;
			UUID_TO_STREAM(p_output, p_uuid);
			output_buffer->length += 2 + sizeof (UINT16);
		}
		else
		{
			uuid_t *p_uuid = &attribute->uuid;
			UUID_TO_STREAM(p_output, p_uuid);
			output_buffer->length += attribute->uuid.length + sizeof (UINT16);
		}
	}

	if (output_buffer->length == 0)
		att_send_error_response(conn_id, opcode, start_handle, ATT_ERR_ATTRIB_NOT_FOUND);
	else
		att_send_find_info_rsp(conn_id, elem_format, output_buffer);
	dealloc(output_buffer);
}

void gatt_read_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* input_buffer)
{
	UINT16 handle = 0, offset = 0;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!input_buffer)
		return;
#endif
	UINT8* p_input = input_buffer->data + input_buffer->offset;
	if (input_buffer->length < (sizeof(UINT16)))
	{
		/* FIXME: if handle is not there in the packet. How to form error msg? */
		att_send_error_response(conn_id, opcode, handle, ATT_ERR_INVALID_PDU);
		return;
	}
	STREAM_TO_UINT16(handle, p_input);
	if (opcode == ATT_OPCODE_READ_BLOB_REQ)
	{
		STREAM_TO_UINT16(offset, p_input);
	}
	logd("handle:0x%04x offset:%d opcode:0x%x", handle, offset, opcode);

	UINT8 error_code = ATT_SUCCESS;
	UINT16 att_idx = get_att_idx_from_hdl(handle);
	if (att_idx == MAX_NUM_ATTR)
		error_code = ATT_ERR_INVALID_HANDLE;

	if (error_code == ATT_SUCCESS)
	{
		gatt_attribute_t *attribute = &g_local_adapter.attribute_list[att_idx];
		switch(attribute->attr_type)
		{
			case ATTR_TYPE_CHARACTERISTIC_VALUE:
			{
				if (att_idx > 0)
				{
					/* Verify Property and Permission from Characteristic Declaration Entry */
					if(IS_ATTRIBUTE_PROPERTY_READ(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
						error_code = ATT_ERR_READ_NOT_PREMITTED;
					else
						error_code = check_attr_read_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
				}
				else
					error_code = ATT_ERR_ATTRIB_NOT_FOUND;
			}
			break;
			case ATTR_TYPE_DESCRIPTOR:
			{
				error_code = check_attr_read_permission(conn_id, attribute->attr_data.char_desc_data.permission);
			}
			break;
			/* Handle special cases like:
			 * Read Service(Primary/Secondary) Declaration Entry,
			 * Read Include Service Declaration Entry
			 * Read Characteristic Declaration Entry */
			case ATTR_TYPE_PRIMARY_SERVICE:
			case ATTR_TYPE_SECONDARY_SERVICE:
			{
				buffer_t *buffer = (buffer_t *)app_alloc((sizeof(buffer_t) + attribute->uuid.length));

				if (!buffer)
				{
					loge("Buffer allocation failed");
					return;
				}

				buffer->length = attribute->uuid.length;
				buffer->offset = 0;
				UINT8 *p = buffer->data;
				uuid_t *p_uuid = &attribute->uuid;
				UUID_TO_STREAM(p, p_uuid);
				gatt_send_attr_read_rsp(conn_id, opcode, handle, ATT_SUCCESS, buffer);
				app_dealloc(buffer);
				return;
			}
			case ATTR_TYPE_INCLUDED_SERVICE:
			{
				/* Allocate memory for start handle , end handle and service uuid */
				UINT16 attribute_value_len = (2 * sizeof(UINT16)) + attribute->uuid.length;
				buffer_t *buffer = (buffer_t *)app_alloc(sizeof(buffer_t) + attribute_value_len);

				if (!buffer)
				{
					loge("Buffer allocation failed");
					return;
				}

				UINT8 *p = buffer->data;
				buffer->length = attribute_value_len;
				buffer->offset = 0;
				UINT16_TO_STREAM(p, attribute->attr_data.inc_srv_data.start_handle);
				UINT16_TO_STREAM(p, attribute->attr_data.inc_srv_data.end_handle);
				uuid_t *p_uuid = &attribute->uuid;
				UUID_TO_STREAM(p, p_uuid);
				gatt_send_attr_read_rsp(conn_id, opcode, handle, ATT_SUCCESS, buffer);
				app_dealloc(buffer);
				return;
			}
			case ATTR_TYPE_CHARACTERISTIC:
			{
				/* Allocate memory for characteristic property , characteristic value handle and characteristic uuid */
				UINT16 attribute_value_len = sizeof(UINT8) + sizeof(UINT16) + attribute->uuid.length;
				buffer_t *buffer = (buffer_t *)app_alloc(sizeof(buffer_t) + attribute_value_len);

				if (!buffer)
				{
					loge("Buffer allocation failed");
					return;
				}

				if (att_idx >= MAX_NUM_ATTR - 1)
					return;
				UINT16 char_value_handle = g_local_adapter.attribute_list[att_idx+1].attr_handle; /* Get value handle from next entry */
				UINT8 *p = buffer->data;
				buffer->length = attribute_value_len;
				buffer->offset = 0;
				UINT8_TO_STREAM(p, attribute->attr_data.char_desc_data.property);
				UINT16_TO_STREAM(p, char_value_handle);
				uuid_t *p_uuid = &attribute->uuid;
				UUID_TO_STREAM(p, p_uuid);
				gatt_send_attr_read_rsp(conn_id, opcode, handle, ATT_SUCCESS, buffer);
				app_dealloc(buffer);
				return;
			}
			default:
			{
				error_code = ATT_ERR_UNLIKELY;
			}
			break;
		}
	}
	if (error_code == ATT_SUCCESS)
	{
		//set_priv_data(conn_id, opcode, NULL);
		sm_read_attribute(conn_id, opcode, handle, offset);
	}
	else if (error_code == ATT_ERR_PENDING)
	{
		g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
		input_buffer->length = TRUNCATE_TO_16BIT_LENGTH(input_buffer->length, sizeof(buffer_t));
		g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + input_buffer->length);
		memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, input_buffer, sizeof(buffer_t) + input_buffer->length);
		g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
	}
	else
	{
		att_send_error_response(conn_id, opcode, handle, error_code);
	}
}

void gatt_read_multiple_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	UINT8 num_of_handles = (UINT8)(in_buffer->length / 2);
	UINT8 it;

	connected_device_t* device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	device->gatt_device_data.saved_multi_read_no_of_handle = num_of_handles;

	logd("No of handles for multiple read : %d", device->gatt_device_data.saved_multi_read_no_of_handle);

	/* We first iterate over the handles to figure out if any of the attributes lack sufficient permission */
	for (it = 0; it < num_of_handles; it++)
	{
		UINT16 value_handle;
		STREAM_TO_UINT16(value_handle, p_input);

		UINT8 error_code = ATT_SUCCESS;
		UINT16 att_idx = get_att_idx_from_hdl(value_handle);
		if (att_idx == MAX_NUM_ATTR)
			error_code = ATT_ERR_INVALID_HANDLE;

		if (error_code == ATT_SUCCESS)
		{
			switch(g_local_adapter.attribute_list[att_idx].attr_type)
			{
				case ATTR_TYPE_CHARACTERISTIC_VALUE:
					if (att_idx > 0)
					{
						/* Verify Property and Permission from Characteristic Declaration Entry */
						if(IS_ATTRIBUTE_PROPERTY_READ(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
							error_code = ATT_ERR_READ_NOT_PREMITTED;
						else
							error_code = check_attr_read_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
					}
					else
						error_code = ATT_ERR_ATTRIB_NOT_FOUND;

					break;
				case ATTR_TYPE_DESCRIPTOR:
					error_code = check_attr_read_permission(conn_id, g_local_adapter.attribute_list[att_idx].attr_data.char_desc_data.permission);
					break;
				default:
					error_code = ATT_ERR_READ_NOT_PREMITTED;
					/* TODO: Allow read on below attribute types
					 * ATTR_TYPE_PRIMARY_SERVICE
					 * ATTR_TYPE_SECONDARY_SERVICE
					 * ATTR_TYPE_INCLUDED_SERVICE
					 * ATTR_TYPE_CHARACTERISTIC
					 * */
					break;
			}
		}
		if(error_code == ATT_ERR_PENDING)
		{
			g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
			in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
			g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
			memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
			g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
			return;
		}
		if (error_code != ATT_SUCCESS)
		{
			logd("Discarding multi-read since handle 0x%04x doesnt have sufficient permissions", value_handle);
			flush_saved_multi_read_handle_list(device);
			att_send_error_response(conn_id, opcode, value_handle, error_code);
			return;
		}
	}

	p_input = in_buffer->data + in_buffer->offset;

	/* The next iteration actually sends read_cbs to the corresponding apps */
	for (it = 0; it < num_of_handles; it++)
	{
		/* Call all the applications who are all responsible for the requested list of characteristics */
		UINT16 value_handle;
		STREAM_TO_UINT16(value_handle, p_input);

		/* store the value handle to global list */
		read_multiple_chars_value_t *read_char = (read_multiple_chars_value_t*) alloc(sizeof(read_multiple_chars_value_t));

		if (!read_char)
			return;

		read_char->handle = value_handle;
		read_char->buffer = NULL;
		logd("handle value = %x", read_char->handle);
		append_ll_node(&device->gatt_device_data.saved_multi_read_handle_list, read_char, 0);
		sm_read_attribute(conn_id, opcode, value_handle, 0);
	}
}

/*
 * Write without response
 */
void gatt_write_command_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	UINT16 handle;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer || (in_buffer && in_buffer->length < (sizeof(UINT16))))
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(handle, p_input);
	in_buffer->length -= 2;
	in_buffer->offset += 2;

	UINT8 error_code = ATT_SUCCESS;
	UINT16 att_idx = get_att_idx_from_hdl(handle);
	if (att_idx == MAX_NUM_ATTR)
		error_code = ATT_ERR_INVALID_HANDLE;

	if (error_code == ATT_SUCCESS)
	{
		/* Write without response is allowed on Characteristic Value only */
		if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
		{
			/* Verify Property and Permission from Characteristic Declaration Entry */
			if(IS_ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
				error_code = ATT_ERR_WRITE_NOT_PERMITTED;
			else
				error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
		}
		else
			error_code = ATT_ERR_INVALID_HANDLE;
	}

	logd("error_code:%d handle:%d in_buffer[offset + 0]:%d", error_code, handle, in_buffer->data[in_buffer->offset + 0]);
	if (error_code == ATT_SUCCESS)
	{
		sm_write_attribute(conn_id, opcode, handle, 0, in_buffer);
	}
	else if (error_code == ATT_ERR_PENDING)
	{
		g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
		in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
		g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
		memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
		g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
	}
}
void gatt_signed_write_execute_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	UINT16 handle;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer || (in_buffer && in_buffer->length < (sizeof(UINT16))))
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(handle, p_input);
	in_buffer->length -= 2;
	in_buffer->offset += 2;

	UINT8 error_code = ATT_SUCCESS;
	UINT16 att_idx = get_att_idx_from_hdl(handle);
	if (att_idx == MAX_NUM_ATTR)
		error_code = ATT_ERR_INVALID_HANDLE;

	if (error_code == ATT_SUCCESS)
	{
		/* Signed Write is allowed on Characteristic Value only */
		if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
		{
			/* Verify Property and Permission from Characteristic Declaration Entry */
			if(IS_ATTRIBUTE_PROPERTY_AUTH_SIGNED_WRITE(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
				error_code = ATT_ERR_WRITE_NOT_PERMITTED;
			else
				error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
		}else
			error_code = ATT_ERR_INVALID_HANDLE;
	}

	logd("error_code:%d handle:%d in_buffer[offset + 0]:%d", error_code, handle, in_buffer->data[in_buffer->offset + 0]);
	if (error_code == ATT_SUCCESS)
	{
		sm_write_attribute(conn_id, opcode, handle, 0, in_buffer);
	}
	else if (error_code == ATT_ERR_PENDING)
	{
		g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
		in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
		g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
		memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
		g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
	}
}

void gatt_signed_write_command_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer)
{
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
#if (SIGNED_WRITE)
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	if (buffer->length <= SMP_MAC_LEN)
		return;

	device->gatt_device_data.saved_buffer = (buffer_t*)alloc(sizeof(buffer_t) + sizeof(UINT8) * (buffer->length - SMP_MAC_LEN));

	if (!device->gatt_device_data.saved_buffer)
		return;

	device->gatt_device_data.saved_buffer->offset = 0;
	memcpy(device->gatt_device_data.saved_buffer->data, buffer->data + buffer->offset, (buffer->length- SMP_MAC_LEN));
	device->gatt_device_data.saved_buffer->length = (buffer->length - SMP_MAC_LEN);
	smpm_req_handler(prepare_sign_verify_req(device, opcode, buffer));
#else
	logd("Signed write not supported with current device security level");
#endif /* SIGNED_WRITE */
}

/*
 * GATT write request
 */
void gatt_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	UINT16 handle;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer || (in_buffer && in_buffer->length < (sizeof(UINT16))))
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(handle, p_input);
	in_buffer->length -= 2;
	in_buffer->offset += 2;

	UINT8 error_code = ATT_SUCCESS;
	UINT16 att_idx = get_att_idx_from_hdl(handle);
	if (att_idx == MAX_NUM_ATTR)
		error_code = ATT_ERR_INVALID_HANDLE;

	if (error_code == ATT_SUCCESS)
	{
		if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
		{
			/* Verify Property and Permission from Characteristic Declaration Entry */
			if (IS_ATTRIBUTE_PROPERTY_WRITE(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
				error_code = ATT_ERR_WRITE_NOT_PERMITTED;
			else
				error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
		}
		else if(g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_DESCRIPTOR)
		{
			error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx].attr_data.char_desc_data.permission);
		}
		else
			error_code = ATT_ERR_WRITE_NOT_PERMITTED;
	}
	if (error_code == ATT_SUCCESS)
	{
		sm_write_attribute(conn_id, opcode, handle, 0, in_buffer);
	}
	else if (error_code == ATT_ERR_PENDING)
	{
		g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
		in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
		g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
		memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
		g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
	}
	else
	{
		att_send_error_response(conn_id, opcode, handle, error_code);
	}
}

void gatt_prepare_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	UINT16 value_handle;
	UINT16 offset;

#if (PARANOID_STACK == TRUE)
	if (!in_buffer || (in_buffer && in_buffer->length< 2 * (sizeof(UINT16))))
		return;
#endif
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(value_handle, p_input);
	STREAM_TO_UINT16(offset, p_input);
	in_buffer->length -= 4;
	in_buffer->offset += 4;

	UINT8 error_code = ATT_SUCCESS;
	UINT16 att_idx = get_att_idx_from_hdl(value_handle);
	if (att_idx == MAX_NUM_ATTR)
		error_code = ATT_ERR_INVALID_HANDLE;

	if (error_code == ATT_SUCCESS)
	{
		if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
		{
			/* Verify Property and Permission from Characteristic Declaration Entry */
			if(IS_ATTRIBUTE_PROPERTY_WRITE(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == FALSE)
				error_code = ATT_ERR_WRITE_NOT_PERMITTED;
			else
				error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.permission);
		}
		else if(g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_DESCRIPTOR)
		{
			error_code = check_attr_write_permission(conn_id, g_local_adapter.attribute_list[att_idx].attr_data.char_desc_data.permission);
		}
		else
			error_code = ATT_ERR_WRITE_NOT_PERMITTED;
	}

	if (error_code == ATT_SUCCESS)
	{
		UINT16 att_id;
		if ((att_id = get_prep_wr_att_id(conn_id)) == 0)
			set_prep_wr_att_id(conn_id, value_handle);
#if (TEST_CODE == FALSE) /* This violation is done by PTS! */
		if (value_handle != get_prep_wr_att_id(conn_id))
		{
			loge("Nested prepared write not supported by GATT");
			att_send_error_response(conn_id, opcode, value_handle, ATT_ERR_INSUFF_RESOURCE);
			return;
		}
#endif
		sm_write_attribute(conn_id, opcode, value_handle, offset, in_buffer);
	}
	else if (error_code == ATT_ERR_PENDING)
	{
		g_local_adapter.connected_device[conn_id]->pending_att_packet.opcode = opcode;
		in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
		g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer = (buffer_t*)alloc(sizeof(buffer_t) + in_buffer->length);
		memcpy(g_local_adapter.connected_device[conn_id]->pending_att_packet.in_buffer, in_buffer, sizeof(buffer_t) + in_buffer->length);
		g_local_adapter.connected_device[conn_id]->att_device.client_att_state = opcode - 1;
	}
	else
	{
		att_send_error_response(conn_id, opcode, value_handle, error_code);
	}
}

void gatt_execute_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	if (!in_buffer)
		return;

	if (!get_prep_wr_att_id(conn_id))
	{
		att_send_execute_write_rsp(conn_id);
		return;
	}

	sm_write_attribute(conn_id, opcode, get_prep_wr_att_id(conn_id), 0, in_buffer);
	set_prep_wr_att_id(conn_id, 0); /* Reset back to 0 */
}

void gatt_handle_value_confirmation_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer)
{
	/* send the confirmation up to the application
	 * Save the att_id while sending the indication. */

	sm_indication_confirmataion(conn_id, get_indication_att_id(conn_id));
}

/****************************************************************
 *			GATT Server API's
 ***************************************************************/

INT8 gatt_send_attr_read_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, buffer_t* in_buffer)
{
	logi("");

	if (status != ATT_SUCCESS)
		return att_send_error_response(conn_id, att_opcode, att_id, status);

	UINT16 mtu = get_device_mtu(conn_id);
	if (att_opcode == ATT_OPCODE_READ_REQ)
	{

		if (!in_buffer)
			return STATUS_ERR_INVALID_PARAM;

		in_buffer->length = (in_buffer->length > (mtu - 1))? (mtu - 1) : in_buffer->length;
		return att_send_read_rsp(conn_id, in_buffer);
	}
	else if (att_opcode == ATT_OPCODE_READ_BLOB_REQ)
	{
		if (!in_buffer)
			return STATUS_ERR_INVALID_PARAM;
		in_buffer->length = (in_buffer->length > (mtu - 1))? (mtu - 1) : in_buffer->length;
		return att_send_read_blob_rsp(conn_id, in_buffer);
	}
	else if (att_opcode == ATT_OPCODE_READ_BY_TYPE_REQ)
	{
#if (PARANOID_STACK == TRUE)
		if (!in_buffer)
			return STATUS_ERR_INVALID_PARAM;
#endif
		UINT16 max_payload_len = mtu - ATT_READ_BY_TYPE_RSP_LEN;
		UINT16 cur_payload_len = in_buffer->length + 2 /* handle size */;
		UINT16 pkt_len = (cur_payload_len > max_payload_len)? max_payload_len : cur_payload_len;
		pkt_len = TRUNCATE_TO_16BIT_LENGTH(pkt_len, sizeof(buffer_t));
		buffer_t* p_buf = (buffer_t*) alloc(sizeof(buffer_t) + pkt_len);

		if (!p_buf)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;

		logd("p_buf:%p", p_buf);
		p_buf->length = pkt_len;
		p_buf->offset = 0;
		UINT8 *p = p_buf->data;
		UINT8 elem_length = (UINT8) pkt_len;
		UINT16_TO_STREAM(p, att_id);
		memcpy(p, in_buffer->data + in_buffer->offset, p_buf->length - 2);
		INT8 ret = att_send_read_by_type_rsp(conn_id, elem_length, p_buf);
		logd("p_buf:%p", p_buf);

		dealloc(p_buf);
		return ret;
	}
	else if (att_opcode == ATT_OPCODE_READ_MULTI_REQ)
	{
		UINT16 res_length = 0;
		INT8 ret;
		UINT8 *p_res;
		buffer_t *p_res_saved;
		read_multiple_chars_value_t *cur_char = NULL;
		connected_device_t* device = get_connected_device_by_conn_id(conn_id);

		if (!device)
			return STATUS_ERR_INVALID_PARAM;

		ll_node_t *cur_node = device->gatt_device_data.saved_multi_read_handle_list;

		logd("opcode : ATT_READ_MULTI_REQ, att_id:%u(0x%X)", att_id, att_id);

		while(cur_node != NULL)
		{
			cur_char = (read_multiple_chars_value_t*) cur_node->data;
			if(cur_char->handle == att_id && !cur_char->buffer) /* Handles duplicate att_id read scenario */
			{
				/* handle is found in saved handle list */
				logi("att_id:%u found in saved handle list",att_id);
				in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, sizeof(buffer_t));
				cur_char->buffer = (buffer_t*) alloc(sizeof(buffer_t) + in_buffer->length);

				if (!cur_char->buffer)
					return STATUS_ERR_INVALID_PARAM;

				cur_char->buffer->length = in_buffer->length;
				cur_char->buffer->offset = 0;
				memcpy(cur_char->buffer->data, in_buffer->data + in_buffer->offset, in_buffer->length);
				hex_dump("in_buffer", in_buffer->data + in_buffer->offset, in_buffer->length);
				device->gatt_device_data.saved_multi_read_no_of_handle--;
				break;
			}
			cur_node = get_next_ll_node(cur_node);
			logi("get_next_ll_node");
		}

		if (device->gatt_device_data.saved_multi_read_handle_list && (device->gatt_device_data.saved_multi_read_no_of_handle == 0))
		{
			/* received values for all the handles, send the response */

			cur_node = device->gatt_device_data.saved_multi_read_handle_list;

			/* get the total length for the response value */
			while(cur_node != NULL)
			{
				cur_char = (read_multiple_chars_value_t*) cur_node->data;
				if((res_length + cur_char->buffer->length) < (mtu - 1))
				{
					res_length += cur_char->buffer->length;
				}
				else
				{
					res_length = mtu - 1;
					break;
				}
				cur_node = get_next_ll_node(cur_node);
			}

			logd("mutiple read res_length = %d", res_length);

			/* get the buffer for response */
			res_length = TRUNCATE_TO_16BIT_LENGTH(res_length, sizeof(buffer_t));
			p_res_saved = (buffer_t*) alloc(res_length + sizeof (buffer_t));

			if (!p_res_saved)
				return STATUS_ERR_INVALID_PARAM;

			p_res_saved->offset = 0;
			p_res_saved->length = res_length;
			p_res = p_res_saved->data;
			cur_node = device->gatt_device_data.saved_multi_read_handle_list;

			UINT16 min_len = 0;
			/* get the total length for the response value */
			while((cur_node != NULL) && (res_length > 0))
			{
				cur_char = (read_multiple_chars_value_t*) cur_node->data;
				min_len = MIN(cur_char->buffer->length, res_length);
				memcpy(p_res, cur_char->buffer->data, min_len);
				res_length -= min_len;
				p_res += min_len;
				cur_node = get_next_ll_node(cur_node);
				hex_dump("multiple read res buffer to send", p_res_saved->data + p_res_saved->offset, p_res_saved->length);
			}

			flush_saved_multi_read_handle_list(device);

			hex_dump("multiple read res buffer to send", p_res_saved->data + p_res_saved->offset, p_res_saved->length);
			ret = att_send_read_multi_rsp(conn_id, p_res_saved);
			dealloc(p_res_saved);
			p_res_saved = NULL;
			return ret;
		}
	}
	return STATUS_ERR_UNKNOWN;
}

INT8 gatt_send_attr_write_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, UINT16 offset, buffer_t* in_buffer)
{
	logd("");
	if (status != ATT_SUCCESS)
	{
		return att_send_error_response(conn_id, att_opcode, att_id, status);
	}
	else
	{
		if (att_opcode == ATT_OPCODE_PREP_WRITE_REQ)
		{
#if (PARANOID_STACK == TRUE)
			if (!in_buffer)
				return STATUS_ERR_INVALID_PARAM;
#endif
			return att_send_prepare_write_rsp(conn_id, att_id, in_buffer, offset);
		}
		else if (att_opcode == ATT_OPCODE_WRITE_REQ)
		{
			return att_send_write_rsp(conn_id);
		}
		if (att_opcode == ATT_OPCODE_EXEC_WRITE_REQ)
		{
			return att_send_execute_write_rsp(conn_id);
		}
	}
	return STATUS_ERR_UNKNOWN;
}

INT8 gatt_send_value_notification(UINT8 conn_id, UINT16 att_id, buffer_t* in_buffer)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	UINT16 att_idx = get_att_idx_from_hdl(att_id);
	if (att_idx == MAX_NUM_ATTR)
	{
		loge("Invalid attribute id: %u !!!", att_id);
		return STATUS_ERR_UNKNOWN;
	}

	if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
	{
		if(IS_ATTRIBUTE_PROPERTY_NOTIFY(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == TRUE)
			return att_send_value_notification(conn_id, att_id, in_buffer);
		else
			loge("Send Notification failed. Notification not supported, Attribute Handle: %u, property: %u !!!", \
					att_idx-1, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property);
	}
	else
		loge("Send Notification failed. Attribute type is not of type CHARACTERISTIC_VALUE !!!");

	return STATUS_ERR_UNKNOWN;
}

INT8 gatt_send_value_indication(UINT8 conn_id, UINT16 att_id, buffer_t* in_buffer)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	UINT16 att_idx = get_att_idx_from_hdl(att_id);
	if (att_idx == MAX_NUM_ATTR)
	{
		loge("Invalid attribute id: %u !!!", att_id);
		return STATUS_ERR_UNKNOWN;
	}

	if(att_idx > 0 && g_local_adapter.attribute_list[att_idx].attr_type == ATTR_TYPE_CHARACTERISTIC_VALUE)
	{
		if(IS_ATTRIBUTE_PROPERTY_INDICATE(g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property) == TRUE)
		{
			INT8 ret = att_send_handle_val_indication(conn_id, att_id, in_buffer);
			if (ret == STATUS_SUCCESS)
				set_indication_att_id(conn_id, att_id);
			return ret;
		}
		else
			loge("Send Indication failed. Indication not supported, Attribute Handle: %u, property: %u !!!", \
					att_idx-1, g_local_adapter.attribute_list[att_idx-1].attr_data.char_desc_data.property);
	}
	else
		loge("Send Indication failed. Attribute type is not of type CHARACTERISTIC_VALUE !!!");

	return STATUS_ERR_UNKNOWN;
}

INT8 gatt_set_service_change_config(UINT8 conn_id, BOOLEAN is_notify)
{
	//TO DO enable service change notification
#if 0
	logd("is_notify = %d", is_notify);
#if (GAP_GATT_SRV_APP == TRUE)
#if (SMP_FEATURE)
	if (conn_id != MAX_NUM_CONNECTED_DEVICE)
	{
		connected_device_t *device = g_local_adapter.connected_device[conn_id];
		if (device != NULL)
		{
			logd("is_bonded = %d", device->is_bonded);
			if(device->is_bonded)
			{
				remote_device_storage_t device_storage;
				get_remote_device_entry(g_local_adapter.bonded_device[device->bonded_idx]->bdaddr, &device_storage);
				device_storage.is_notify_for_service_change = is_notify;
				logd("Setting NVM entry with = %d for conn_id = %d", is_notify, conn_id);
				set_remote_device_entry(&device_storage);
				return STATUS_SUCCESS;
			}
		}
	}
#endif /*SMP_FEATURE*/
#endif /* GAP_GATT_SRV_APP == TRUE */
#endif
	return STATUS_ERR_LAYER_SPECIFIC;
}

BOOLEAN gatt_get_service_change_config(UINT8 conn_id)
{
	//TO DO : service change notification to be enabled
#if 0
	logd("");
#if (GAP_GATT_SRV_APP == TRUE)
#if (SMP_FEATURE)
	if (conn_id != MAX_NUM_CONNECTED_DEVICE)
	{
		connected_device_t *device = g_local_adapter.connected_device[conn_id];
		if (device != NULL)
		{
			logd("is_bonded = %d", device->is_bonded);
			if(device->is_bonded)
			{
				remote_device_storage_t device_storage;
				get_remote_device_entry(g_local_adapter.bonded_device[device->bonded_idx]->bdaddr, &device_storage);
				logd("NVM entry for service change indication = %d", device_storage.is_notify_for_service_change);
				return device_storage.is_notify_for_service_change;
			}
		}
	}
#endif /* SMP_FEATURE */
#endif /* GAP_GATT_SRV_APP == TRUE */
#endif
	return FALSE;
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */
