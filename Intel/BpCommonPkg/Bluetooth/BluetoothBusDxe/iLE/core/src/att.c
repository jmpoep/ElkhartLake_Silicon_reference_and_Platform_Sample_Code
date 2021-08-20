/** @file
  ATT protocol implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "gatt.h"
#include "l2cap.h"
#include "utils.h"
#include "att.h"
#include "int_interface.h"
#include "interface.h"

#define MODULE_DBG_LVL ATT_DBG_LVL
#include "log.h"

#define IS_ATT_RESPONSE(opcode) ((opcode%2)==1 ? TRUE : FALSE)


/* local function  prototypes */
#if (GATT_CLIENT_SUPPORTED == TRUE)

static void att_client_timer_expire_cb(osa_timer_arg_t arg);
static INT8 att_client_timer_stop(UINT8 conn_id);
static INT8 att_validate_response(UINT8 conn_id, UINT8 respponse_code);
static INT8 att_decode_err_response(UINT8 conn_id, buffer_t *in_buffer);

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

#if (GATT_SERVER_SUPPORTED == TRUE)

static void att_server_timer_expire_cb(osa_timer_arg_t arg);
static INT8 att_server_timer_start(UINT8 conn_id);
static INT8 att_server_timer_stop(UINT8 conn_id);

#endif /* GATT_SERVER_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

static void set_device_att_client_state(UINT8 conn_id, UINT8 state)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	device->att_device.client_att_state = state;
}

/**********************************************************************
 * @fn  att_decode_err_response
 * @brief Decode the error response received and
 *       provide to the upper layer.
 * @param  device	   - connected device structure
 * @param  buf_len - response buffer length
 * @param  buf - response buffer
 * @returns Always TRUE
 *
 *********************************************************************/
static INT8 att_decode_err_response(UINT8 conn_id, buffer_t *in_buffer)
{
	UINT8 *p = in_buffer->data + in_buffer->offset;
	UINT8 req_opcode;
	UINT16 att_handle;
	UINT8 error_code;
	logi("");
	STREAM_TO_UINT8(req_opcode, p);
	STREAM_TO_UINT16(att_handle, p);
	STREAM_TO_UINT8(error_code, p);
	/* Call to GATT layer to inform the error */
	gatt_error_resp_cb(conn_id, req_opcode, att_handle, error_code);
	return STATUS_SUCCESS;
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

/**********************************************************************
 * @fn  att_validate_response
 * @brief validate the response message by mapping request to
 *				response for the given connected device.
 * @param   device	   - connected device structure
 * @param   response_code - attribute response code
 * @returns  TRUE - if validation succeeds else FALSE
 *
 *********************************************************************/
static INT8 att_validate_response(UINT8 conn_id, UINT8 response_code)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if (!((device->att_device.client_att_state == (response_code - 1)) && (response_code != ATT_OPCODE_ERROR_RESP)))
		return STATUS_ERR_INVALID_PARAM;
	device->att_device.client_att_state = 0;
#if (GATT_CLIENT_SUPPORTED == TRUE)
	att_client_timer_stop(conn_id);
#endif /* GATT_CLIENT_SUPPORTED == TRUE */
		return STATUS_SUCCESS;
}

#if (GATT_SERVER_SUPPORTED == TRUE || GATT_CLIENT_SUPPORTED == TRUE)

/**********************************************************************
 * @fn  att_is_pdu_allowed
 * @brief  confirm to the ATT sequential execution.
 * @param  device	   - connected device structure
 * @param  opcode - attribute	 code
 * @returns  TRUE - if PDU can be sent else FALSE

 *
 *********************************************************************/
static INT8 att_is_pdu_allowed(UINT8 conn_id, BOOLEAN is_client_op, UINT8 opcode)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if (is_client_op == TRUE)
	{
		if (device->att_device.client_att_state != ATT_DEVICE_IDLE)
		{
			/* check for the allowed commands and return */
			if ((opcode == ATT_OPCODE_WRITE_CMD) ||
				(opcode == ATT_OPCODE_HANDLE_VAL_NOTIFY)||
				(opcode == ATT_OPCODE_SIGN_WRITE_CMD))
				return STATUS_SUCCESS;
			else
				return STATUS_ERR_BUSY;
		}
		else
			return STATUS_SUCCESS;
	}
	else
	{
		if (device->att_device.server_att_state != ATT_DEVICE_IDLE)
		{
			if ((device->att_device.server_att_state != ATT_OPCODE_HANDLE_VAL_IND) &&
						 (opcode == ATT_OPCODE_HANDLE_VAL_IND))
					return STATUS_SUCCESS;
			else
				return STATUS_ERR_BUSY;
		}
		else
			return STATUS_SUCCESS;
	}
}

#endif /* GATT_SERVER_SUPPORTED == TRUE || GATT_CLIENT_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

/**********************************************************************
 * @fn  att_client_timer_start
 * @brief  Start the ATT timer on sending the request to the
 *        Lower layers and wait for response
 * @param  device  - connected device structure
 * @returns  TRUE if timer is started else FALSE if device is not found
 *
 *********************************************************************/
static INT8 att_client_timer_start(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	logi("");
	if (!device)
		return STATUS_ERR_INVALID_PARAM;
	if (!osa_is_timer_active(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER, device->idx))
		if (osa_start_timer(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER, (ATT_TIMEOUT_VAL * 1000) , att_client_timer_expire_cb, device->idx))
			return STATUS_SUCCESS;

	return STATUS_ERR_INVALID_PARAM;
}

/**********************************************************************
 * @fn  att_client_timer_expire_handler
 * @brief  ATT timer is expired for the given request / connected
 *         device. Inform error to the upper layers
 * @param arg  connected device index
 * @returns  None
 *
 *********************************************************************/
static void att_client_timer_expire_handler(osa_timer_arg_t arg)
{
	/* report to the upper layer */
	/* No more ATT request should come for
	 * the ATT Bearer */
	UINT8 idx = (UINT8) osa_get_timer_arg_val(arg);
	connected_device_t* device = g_local_adapter.connected_device[idx];
	logi("");
	if(device)
	{
		logd("ATT timer expired for %02x opcode %02x", device->idx,	device->att_device.client_att_state);
		gatt_client_timeout_cb(idx, device->att_device.client_att_state);
		device->att_device.client_att_state = 0;
	}
	else
	{
		logw("ATT timer expired for %02x, device = NULL",idx);
	}
}

static void att_client_timer_expire_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(att_client_timer_expire_handler, arg);
}

/**********************************************************************
 * @fn att_client_timer_stop
 * @brief  Stop the ATT timer on receiving response to the
 *         request that was sent earlier.
 * @param  device - connected device structure
 * @returns  TRUE if timer is stopped, FALSE if device is not found

 *********************************************************************/
static INT8 att_client_timer_stop(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	logi("");
	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if (osa_is_timer_active(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER, device->idx))
		if (osa_stop_timer(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER, device->idx))
			return STATUS_SUCCESS;

	return STATUS_ERR_INVALID_PARAM;
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

/**********************************************************************
 * @fn att_server_timer_expire_handler
 * @brief  ATT timer is expired for the given request / connected
 *         device. Inform error to the upper layers
 * @param   arg - connected device index.
 * @returns  None
 *
 *********************************************************************/
static void att_server_timer_expire_handler(osa_timer_arg_t arg)
{
	UINT8 idx = (UINT8) osa_get_timer_arg_val(arg);
	logi("");
	gatt_server_timeout_cb(idx);
}

static void att_server_timer_expire_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(att_server_timer_expire_handler, arg);
}

/**********************************************************************
 * @fn att_server_timer_start
 * @brief  Start the ATT timer on received the request from the
 *         Lower layers and wait for response
 * @param - device - connected device structure
 * @returns  TRUE if timer is started FALSE if device is not found
 *
 *********************************************************************/
static INT8 att_server_timer_start(UINT8 conn_id)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);
	logi("");
	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if (!osa_is_timer_active(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER, device->idx))
		if (osa_start_timer(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER, (ATT_TIMEOUT_VAL * 1000), att_server_timer_expire_cb, device->idx))
			return STATUS_SUCCESS;

	return STATUS_ERR_INVALID_PARAM;
}

/**********************************************************************
 * @fn  att_server_timer_stop
 * @brief  Stop the ATT timer on sending response to the
 *         received request.
 * @param  device - connected device structure
 * @returns  TRUE if timer is stopped FALSE if device is not found
 *
 *********************************************************************/
static INT8 att_server_timer_stop(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	logi("");
	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if (osa_is_timer_active(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER, device->idx))
		if (osa_stop_timer(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER, device->idx))
			return STATUS_SUCCESS;

	return STATUS_ERR_INVALID_PARAM;
}

#if (GATT_SERVER_SUPPORTED == TRUE)

static void set_device_att_server_state(UINT8 conn_id, UINT8 state)
{
	connected_device_t* device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return;
	device->att_device.server_att_state = state;
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

/**********************************************************************
 * @fn  att_send_error_response
 * @brief  Send error response to the specified connected device.
 * @param  device	   - connected device structure
 * @param  req_opcode - requested opcode
 * @param  handle		- request handle
 * @param  reason		- error code
 * @returns  TRUE if data sent to L2CP successfully else  FALSE when
 *           failed to send error response.
 *********************************************************************/
INT8 att_send_error_response(UINT8 conn_id, UINT8 req_opcode, UINT16 handle, UINT8 reason)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT8 *p;
	UINT16 data_length = ATT_BUFFER_OFFSET + ATT_ERR_RESP_LEN;
	buffer_t *data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	logi(" reason:0x%02x", reason);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];

	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_ERROR_RESP);
	UINT8_TO_STREAM(p, req_opcode);
	UINT16_TO_STREAM(p, handle);
	UINT8_TO_STREAM(p, reason);

	if ((ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt)) == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_init
 * @brief  Initialize ATT layer.
 * @param  none
 * @returns  Always TRUE
 *
 *********************************************************************/
INT8 att_init()
{
	logi("");
	return STATUS_SUCCESS;
}

void att_cleanup()
{
	logi("");
	iLE_stack_cleanup();
}


#if (GATT_CLIENT_SUPPORTED == TRUE)

/**********************************************************************
 * @fn  att_mtu_xchange_req
 * @brief  Send MTU exchange request to connected peer device.
 * @param  device - connected device structure
 * @param   rx_mtu - Receive MTU size
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send error response.
 *
 *********************************************************************/
INT8 att_mtu_xchange_req(UINT8 conn_id, UINT16 rx_mtu)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p ;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_MTU_XCHANGE_REQ_LEN);
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_MTU_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*) get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_MTU_REQ);
	UINT16_TO_STREAM(p, rx_mtu);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_MTU_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_read_by_type_req
 * @brief  Read by Type request.
 * @param  device - connected device structure
 * @param  start_handle - start handle
 * @param  end_handle - End handle
 * @param  attrib_type - Attribute type
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_read_by_type_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *attrib_type)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p ;
	UINT16 data_length = ATT_BUFFER_OFFSET + 5 + attrib_type->length;
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_READ_BY_TYPE_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_BY_TYPE_REQ);
	UINT16_TO_STREAM(p, start_handle);
	UINT16_TO_STREAM(p, end_handle);
	UUID_TO_STREAM(p, attrib_type);

	if ((ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt))== STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_READ_BY_TYPE_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_read_req
 * @brief  Read the value of attribute.
 * @param  device - connected device structure
 * @param  att_handle - attribute handle
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send read request.

 *
 *********************************************************************/
INT8 att_read_req(UINT8 conn_id, UINT16 att_handle)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 data_length = (ATT_BUFFER_OFFSET + ATT_READ_REQ_LEN);
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_READ_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_REQ);
	UINT16_TO_STREAM(p, att_handle);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_READ_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_read_blob_req
 * @brief  Read part of the value of an attribute at given offset.
 * @param  device - connected device structure
 * @param  att_handle - attribute handle
 * @param  offset		- offset of byte to be read.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_read_blob_req(UINT8 conn_id, UINT16 att_handle, UINT16 offset)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 data_length = (ATT_BUFFER_OFFSET + ATT_READ_BLOB_REQ_LEN);
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_READ_BLOB_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_BLOB_REQ);
	UINT16_TO_STREAM(p, att_handle);
	UINT16_TO_STREAM(p, /*0xFF00*/ offset);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_READ_BLOB_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_read_multiple_req
 * @brief  Read two or more values of set of attributes.
 * @param  device - connected device structure
 * @param  num_handles - number of attribute handles
 * @param  handle_buf		- attribute handle buffer.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_read_multiple_req(UINT8 conn_id, UINT16 *handle_list)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT8 it = 0, num_of_characteristics = 0;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 data_length ;
	logi("");
#if (PARANOID_STACK == TRUE)
	if ((!handle_list))
		return STATUS_ERR_INVALID_PARAM;
#endif
	while (handle_list[it] != 0 && it < 12)
	{
		num_of_characteristics++;
		it++;
	}
	data_length = (ATT_BUFFER_OFFSET + (2 * num_of_characteristics) + ATT_READ_MULTI_REQ_LEN);

	if((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_READ_MULTI_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_MULTI_REQ);
	for (it = 0; it < num_of_characteristics; it ++)
	{
		UINT16_TO_STREAM(p, handle_list[it]);
	}

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_READ_MULTI_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_read_by_group_type_req
 * @brief  Read attribute values where attribute type is known
 * @param  device  - connected device structure
 * @param  start_handle - first requested handle
 * @param  end_handle - last requested handle.
 * @param  attrib_type  - attribute UUIT ( 2 bytes)
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_read_by_group_type_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, UINT16 attrib_type)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 data_length = (ATT_BUFFER_OFFSET + ATT_READ_BY_GRP_TYPE_REQ_LEN);
	buffer_t *data_pkt;
	UINT8 *p ;
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_READ_BY_GRP_TYPE_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_BY_GRP_TYPE_REQ);
	UINT16_TO_STREAM(p, start_handle);
	UINT16_TO_STREAM(p, end_handle);
	UINT16_TO_STREAM(p, attrib_type);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_READ_BY_GRP_TYPE_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_write_req
 * @brief  write the value of an attribute
 * @param  device - connected device structure
 * @param  att_handle - attribute handle to be written
 * @param  val_len - attribute value length.
 * @param  val_buf - attribute value
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_write_req(UINT8 conn_id, UINT16 att_handle, buffer_t *buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 data_length;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, ATT_BUFFER_OFFSET + ATT_WRITE_REQ_LEN);
	data_length = (ATT_BUFFER_OFFSET + ATT_WRITE_REQ_LEN + buffer->length);
	if((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_WRITE_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_WRITE_REQ);
	UINT16_TO_STREAM(p, att_handle);
	memcpy(p, buffer->data + buffer->offset, sizeof(UINT8) * buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_WRITE_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_write_command
 * @brief  write the value of an attribute typically into a
 *				control point attribute.
 * @param  device - connected device structure
 * @param  att_handle - attribute handle to be written
 * @param  val_len - attribute value length.
 * @param  val_buf - attribute value
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_write_command(UINT8 conn_id, UINT16 att_handle, buffer_t *buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 data_length;

	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_WRITE_CMD)) != STATUS_SUCCESS)
		return ret;
	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, ATT_BUFFER_OFFSET + ATT_WRITE_CMD_LEN);
	data_length = (ATT_BUFFER_OFFSET + ATT_WRITE_CMD_LEN + buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(data_length);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = data_length;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_WRITE_CMD);
	UINT16_TO_STREAM(p, att_handle);
	memcpy(p, buffer->data + buffer->offset, sizeof(UINT8) * buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	return ret;
}

/**********************************************************************
 * @fn  att_find_info_req
 * @brief  obtain the mapping of attribute handles with
 *				their associated types on the server.
 * @param  device - connected device structure
 * @param  start_handle - first requested handle
 * @param  end_handle - last requested handle.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_find_info_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	buffer_t *data_pkt;
	UINT8 *p;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_FIND_INFO_REQ_LEN);
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_FIND_INFO_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_FIND_INFO_REQ);
	UINT16_TO_STREAM(p, start_handle);
	UINT16_TO_STREAM(p, end_handle);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_FIND_INFO_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_find_by_type_val_req
 * @brief  obtain the handles of attributes that have a UUID
 *				type and attribute values. Range of handles associated
 *				with a give attribute to be discovered.
 * @param  device - connected device structure
 * @param  start_handle - first requested handle
 * @param  end_handle - last requested handle.
 * @param  att_type - attribute UUID ( 2 bytes)
 * @param  val_len - attribute value length
 * @param  att_val - attribute value.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_find_by_type_val_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, UINT16 att_type, uuid_t* uuid_to_find)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!uuid_to_find)
		return STATUS_ERR_INVALID_PARAM;
#endif

	buf_len = (ATT_BUFFER_OFFSET + ATT_FIND_BY_TYP_VAL_REQ_LEN + uuid_to_find->length);
	if((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_FIND_BY_TYPE_VAL_REQ)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_FIND_BY_TYPE_VAL_REQ);
	UINT16_TO_STREAM(p, start_handle);
	UINT16_TO_STREAM(p, end_handle);
	UINT16_TO_STREAM(p, att_type);
	UUID_TO_STREAM(p, uuid_to_find);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_FIND_BY_TYPE_VAL_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_prepare_write_req
 * @brief  prepare and send queued write request to server
 * @param  device - connected device structure
 * @param  att_handle - attribute handle
 * @param  val_offset - offset of first octet to be written
 * @param  length - length of buffer
 * @param  att_value - buffer containing attribute to be written
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_prepare_write_req(UINT8 conn_id,UINT16 att_handle, UINT16 val_offset, buffer_t *buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	if((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_PREP_WRITE_REQ)) != STATUS_SUCCESS)
		return ret;
	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, ATT_BUFFER_OFFSET + ATT_PREPARE_WRITE_REQ_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_PREPARE_WRITE_REQ_LEN + buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_PREP_WRITE_REQ);
	UINT16_TO_STREAM(p, att_handle);
	UINT16_TO_STREAM(p, /* 0xFF00 */val_offset);
	memcpy(p, buffer->data + buffer->offset, sizeof(UINT8) * buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_PREP_WRITE_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_execute_write_req
 * @brief  Request the server to write or cancel all of the
 * 				prepared values.
 * @param  device - connected device structure
 * @param  flags - 0x00 - cancel all prepared writes\
 *	   	   	   	   	 0x01-  write immediately all pending prepared value
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_execute_write_req(UINT8 conn_id, UINT8 flags)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;

	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_EXEC_WRITE_REQ)) != STATUS_SUCCESS)
		return ret;
	buf_len = (ATT_BUFFER_OFFSET + ATT_EXEC_WRITE_REQ_LEN);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_EXEC_WRITE_REQ);
	UINT8_TO_STREAM(p, flags);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_client_state(conn_id, ATT_OPCODE_EXEC_WRITE_REQ);
		att_client_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_signed_write_cmd
 * @brief  Request the server to write the values of an
 * 				attribute with an authentication signature.
 * @param  device - connected device structure
 * @param  att_handle - The handle of the attribute to be set
 * @param  att_val_len - Length of attribute value buffer
 * @param  att_val - Attribute value buffer
 * @param  auth_signature - Authentication signature for the
 *   	   	   	   	   	  attribute upload,attribute handle and
 *   	   	   	   	   	  attribute value parameters.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_signed_write_cmd(UINT8 conn_id, UINT16 att_handle, buffer_t* buffer, UINT8 *auth_signature)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len ;
	buffer_t *data_pkt;
	UINT8 *p ;

	logi("");
#if (PARANOID_STACK == TRUE)
	if (!buffer || !auth_signature)
		return STATUS_ERR_INVALID_PARAM;
#endif

	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_SIGN_WRITE_CMD)) != STATUS_SUCCESS)
		return ret;
	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, ATT_BUFFER_OFFSET + ATT_SIGN_WRITE_CMD_LEN + ATT_AUTH_SIGNATURE_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_SIGN_WRITE_CMD_LEN + buffer->length + ATT_AUTH_SIGNATURE_LEN);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_SIGN_WRITE_CMD);
	UINT16_TO_STREAM(p, att_handle);
	memcpy(p, buffer->data + buffer->offset, sizeof(UINT8) * buffer->length);
	p += buffer->length;
	memcpy(p, auth_signature, sizeof(UINT8)* ATT_AUTH_SIGNATURE_LEN);

	return l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
}

/**********************************************************************
 * @fn  att_send_handle_val_cfm
 * @brief  This is sent in response to a received indication
 *				and confirms that the client has received attribute.
 * @param  device - connected device structure
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_send_handle_val_cfm(UINT8 conn_id)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_HANDLE_VAL_CFM_LEN);
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
	if ((ret = att_is_pdu_allowed(conn_id, TRUE, ATT_OPCODE_HANDLE_VAL_CFM)) != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_HANDLE_VAL_CFM);

	return l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
}
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

/**********************************************************************
 * @fn  att_send_read_by_type_rsp
 * @brief  Response to read by type request that contains
 * 				the handles of the attributes that have been read.
 * @param  device - connected device structure
 * @param  hndle_val_len - size of each attribute handle value pair
 * @param  att_data_len - length of attribute data list
 * @param  att_data - A list of attribute data
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_read_by_type_rsp(UINT8 conn_id, UINT8 hndle_val_len, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_READ_BY_TYPE_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_READ_BY_TYPE_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_READ_BY_TYPE_RESP);
	UINT8_TO_STREAM(p, hndle_val_len)
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

#if (GATT_SERVER_SUPPORTED == TRUE)
/**********************************************************************
 * @fn  att_send_handle_val_indication
 * @brief  send an indication of an attribute value to client.
 * @param  device - connected device structure
 * @param  att_handle - attribute handle
 * @param  val_len - attribute value length
 * @param  val_buf - attribute value.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *
 *********************************************************************/
INT8 att_send_handle_val_indication(UINT8 conn_id, UINT16 att_handle, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;

	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
	if ((ret =att_is_pdu_allowed(conn_id, FALSE, ATT_OPCODE_HANDLE_VAL_IND)) != STATUS_SUCCESS)
		return ret;
	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_HANDLE_VAL_IND_LEN);
	buf_len = ATT_BUFFER_OFFSET + ATT_HANDLE_VAL_IND_LEN + in_buffer->length;
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_HANDLE_VAL_IND);
	UINT16_TO_STREAM(p, att_handle);
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * (in_buffer->length));

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
	{
		set_device_att_server_state(conn_id, ATT_OPCODE_HANDLE_VAL_IND);
		att_server_timer_start(conn_id);
	}
	return ret;
}

/**********************************************************************
 * @fn  att_send_mtu_xchange_rsp
 * @brief  Server response to MTU exchange request
 * @param  device - connected device structure
 * @param  rx_mtu - server receive MTU size
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_mtu_xchange_rsp(UINT8 conn_id,UINT16 rx_mtu)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_MTU_XCHANGE_RSP_LEN );
	buffer_t *data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	UINT8 *p;
	logi("");
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p, ATT_OPCODE_MTU_RESP);
	UINT16_TO_STREAM(p, rx_mtu);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_read_rsp
 * @brief  Response to read request that contains
 * 				the value of the attribute that has been read.
 * @param  device - connected device structure
 * @param  length - length of attribute value data
 * @param  att_val - The value of attribute with the handle givenret
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_read_rsp(UINT8 conn_id, buffer_t *in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer->data)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_READ_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_READ_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_READ_RESP);
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * (in_buffer->length));
	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);

	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_read_blob_rsp
 * @brief  Response to read blob request that contains part of
 * 				the value of the attribute that has been read.
 * @param  device - connected device structure
 * @param  length - length of part attribute  data
 * @param  att_val_part - Part of the value of attribute with
 *	   					the handle given.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_read_blob_rsp(UINT8 conn_id, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_READ_BLOB_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_READ_BLOB_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_READ_BLOB_RESP);
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_read_multi_rsp
 * @brief  Response to read multiple request that contains
 * 				the values of the attribute that have been read.
 * @param  device - connected device structure
 * @param  length - length of  attribute  values
 * @param  set_of_values - set of two or more values.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_read_multi_rsp(UINT8 conn_id, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt ;
	UINT8 *p ;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_READ_MULTI_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_READ_MULTI_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_READ_MULTI_RESP);
	memcpy(p, in_buffer->data + in_buffer->offset,sizeof(UINT8) * in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_read_by_grp_type_rsp
 * @brief  Response to read by group type request that contains
 * 			the handles and values of the attribute that have been read.
 * @param  device - connected device structure
 * @param  att_len - The size of each attribute data
 * @param  length - length of  attribute  data list
 * @param  att_data_list - list of attribute data.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_read_by_grp_type_rsp(UINT8 conn_id, UINT8 att_len, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p ;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_READ_BY_GRP_TYPE_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_READ_BY_GRP_TYPE_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_READ_BY_GRP_TYPE_RESP);
	UINT8_TO_STREAM(p,att_len);

	memcpy(p, in_buffer->data + in_buffer->offset,sizeof(UINT8) * in_buffer->length);
	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);

	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_write_rspdevice
 * @brief  Response to write  request and acknowledges
 * 				that the attribute has been successfully written.
 * @param  device - connected device structure
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_write_rsp(UINT8 conn_id)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_WRITE_RSP_LEN);
	buffer_t *data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	UINT8 *p;
	logi("");
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_WRITE_RESP);
	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_find_info_rsp
 * @brief  Response Find information request and contains
 * 				information about the server.
 * @param  device - connected device structure
 * @param  format - The format of information data.
 *	   				 0x01 - Handles and 16 bit Bluetooth UUIDs
 *	   				 0x02 - Handles and 128 bit Bluetooth UUIDs
 * @param  info_len - Information data length
 * @param  info_data - The information data whose format is determined
 *	   				  by the format field.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_find_info_rsp(UINT8 conn_id, UINT8 format, buffer_t* in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len ;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_FIND_INFO_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_FIND_INFO_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_FIND_INFO_RESP);
	UINT8_TO_STREAM(p,format);
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_find_by_type_val_rsp
 * @brief  Response to Find by type value request and contains
 * 				information about the server.
 * @param  device - connected device structure
 * @param  len - length of one or more handle Information.
 * @param  handle_info_list - A list of one or more handle information.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_find_by_type_val_rsp(UINT8 conn_id, buffer_t *in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_FIND_BY_TYPE_VAL_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_FIND_BY_TYPE_VAL_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_FIND_BY_TYPE_VAL_RESP);
	memcpy(p, in_buffer->data + in_buffer->offset,sizeof(UINT8) * in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_prepare_write_rsp
 * @brief  Response to Prepare write request and acknowledges that
 * 			value has been successfully received and placed in the
 * 			prepare write queue.
 * @param  device - connected device structure
 * @param  att_handle - The handle of attribute to be written
 * @param  val_offset - The offset of first octet to be written
 * @param  len - length of attribute to be written
 * @param  att_val - Attribute value buffer.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_prepare_write_rsp(UINT8 conn_id,UINT16 att_handle, buffer_t *in_buffer, UINT16 offset)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len ;
	buffer_t *data_pkt;
	UINT8 *p;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_PREPARE_WRITE_RSP_LEN);
	buf_len = (ATT_BUFFER_OFFSET + ATT_PREPARE_WRITE_RSP_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_PREP_WRITE_RESP);
	UINT16_TO_STREAM(p, att_handle);
	UINT16_TO_STREAM(p, offset);
	memcpy(p, in_buffer->data + in_buffer->offset, in_buffer->length);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_prepare_write_rsp
 * @brief  Response to execute write request sent after the
 * 				attributes are written.
 * @param  device - connected device structure
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_execute_write_rsp(UINT8 conn_id)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 buf_len = (ATT_BUFFER_OFFSET + ATT_EXEC_WRITE_RSP_LEN);
	buffer_t *data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	UINT8 *p;
	logi("");
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_EXEC_WRITE_RESP);

	ret = l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
	if (ret == STATUS_SUCCESS)
		att_server_timer_stop(conn_id);
	return ret;
}

/**********************************************************************
 * @fn  att_send_value_notification
 * @brief  Response to execute write request sent after the
 * 			attributes are written.
 * @param  device - connected device structure
 * @param  att_handle - Handle of attribute
 * @param  att_val - Current value of attribute
 * @param  len - length of att_val buffer.
 * @returns  TRUE - if data sent to L2CP successfully
 *					  FALSE - failure to send request.
 *********************************************************************/
INT8 att_send_value_notification(UINT8 conn_id, UINT16 att_handle, buffer_t* in_buffer)
{
	UINT16   buf_len;
	buffer_t *data_pkt;
	UINT8    *p;
#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif

	logi("");
	in_buffer->length = TRUNCATE_TO_16BIT_LENGTH(in_buffer->length, ATT_BUFFER_OFFSET + ATT_NOTIFY_LEN);
	buf_len   = (ATT_BUFFER_OFFSET + ATT_NOTIFY_LEN + in_buffer->length);
	data_pkt = (buffer_t*)get_l2cap_free_buffer(buf_len);
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	JUMP_CUSTOM_LEN(p, ATT_BUFFER_OFFSET);
	UINT8_TO_STREAM(p,ATT_OPCODE_HANDLE_VAL_NOTIFY);
	UINT16_TO_STREAM(p,att_handle);
	memcpy(p, in_buffer->data + in_buffer->offset, sizeof(UINT8) * in_buffer->length);

	return l2cap_data_send(conn_id, L2CAP_ATT_CID, data_pkt);
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

/**********************************************************************
 * @fn  att_l2cap_recv_data_cb
 * @brief  ATT call back function to receive asynchronous
 *				data, response and indications from L2CAP.
 * @param  device - connected device structure
 * @param  data - L2CAP data buffer
 * @param  data_lne - L2CAP data length.
 * @returns  TRUE - if data processed successfully
 *					  FALSE - failure to process the request.
 *********************************************************************/
INT8 att_l2cap_recv_data_cb(UINT8 conn_id, buffer_t* in_buffer)
{
	UINT8 opcode;
	UINT8* p_input;

#if (PARANOID_STACK == TRUE)
	if (!in_buffer)
		return STATUS_ERR_INVALID_PARAM;
#endif
	logi("");
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_ATT_RECV_DATA);
#endif
	p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT8(opcode, p_input);
	in_buffer->length--;
	in_buffer->offset++;
	if (IS_ATT_RESPONSE(opcode) && att_validate_response(conn_id, opcode) != STATUS_SUCCESS)
	{
		if (opcode == ATT_OPCODE_ERROR_RESP)
		{
#if (GATT_CLIENT_SUPPORTED == TRUE)
			/* Inform the upper layer about the failure */
			set_device_att_client_state(conn_id, ATT_DEVICE_IDLE);
			att_client_timer_stop(conn_id);
			return att_decode_err_response(conn_id, in_buffer);
#else
			return STATUS_ERR_OPERATION_NOT_SUPPORTED;
#endif /* GATT_CLIENT_SUPPORTED == TRUE */
		}
		else
		{
			/* This is ATT response packet is not a result of any req we sent.
			 * Don't stop client timer if it is running. We'll wait for the proper response.
			 */
			if (opcode != ATT_OPCODE_HANDLE_VAL_NOTIFY && opcode != ATT_OPCODE_HANDLE_VAL_IND)
			{
				logw("Unaligned ATT response packet. discard");
				return STATUS_ERR_INVALID_ATTRIBUTE;
			}
		}
	}
	return att_process_packet(opcode, conn_id, in_buffer);
}
INT8 att_process_packet(UINT8 opcode, UINT8 conn_id, buffer_t *in_buffer)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	UINT16 handle = 0;
	UINT8* p_input;
	switch (opcode)
	{
#if (GATT_CLIENT_SUPPORTED == TRUE)
		case ATT_OPCODE_MTU_RESP:
		{
			ret = gatt_handle_mtu_resp_cb(conn_id, in_buffer);
		}
		break;
		case ATT_OPCODE_READ_BY_TYPE_RESP:
		{
			logd("ATT_READ_BY_TYPE_RESP");
			gatt_read_by_type_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_RESP:
		{
			logd("ATT_READ_RESP");
			gatt_read_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_BLOB_RESP:
		{
			logd("ATT_READ_BLOB_RESP");
			gatt_read_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
		}
		break;
		case ATT_OPCODE_READ_MULTI_RESP:
		{
			logd("ATT_READ_MULTI_RESP");
			gatt_read_multiple_rsp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_BY_GRP_TYPE_RESP:
		{
			logd("ATT_READ_BY_GRP_TYPE_RESP");
			gatt_read_by_group_type_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_WRITE_RESP:
		{
			logd("ATT_WRITE_RESP");
			gatt_write_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_FIND_INFO_RESP:
		{
			logd("ATT_FIND_INFO_RESP");
			gatt_discover_desc_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_FIND_BY_TYPE_VAL_RESP:
		{
			logd("ATT_FIND_BY_TYPE_VAL_RESP");
			gatt_discover_prim_srv_by_uuid_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_HANDLE_VAL_IND:
		{
			logd("ATT_HANDLE_VAL_IND");
			gatt_notify_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_HANDLE_VAL_NOTIFY:
		{
			logd("ATT_HANDLE_VAL_NOTIFY");
			gatt_notify_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
			break;
		case ATT_OPCODE_PREP_WRITE_RESP:
		{
			logd("ATT_PREP_WRITE_RESP");
			gatt_prep_write_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_EXEC_WRITE_RESP:
		{
			logd("ATT_EXEC_WRITE_RESP");
			gatt_exec_write_resp_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

		case ATT_OPCODE_READ_BY_TYPE_REQ:
		{
			logd("ATT_READ_BY_TYPE_REQ");
			att_server_timer_start(conn_id);
			gatt_read_by_type_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;

#if (GATT_SERVER_SUPPORTED == TRUE)
		case ATT_OPCODE_MTU_REQ:
		{
			logd("ATT_MTU_REQ");
			att_server_timer_start(conn_id);
			gatt_mtu_exchange_req_cb(conn_id, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_REQ:
		{
			logd("ATT_READ_REQ");
			att_server_timer_start(conn_id);
			gatt_read_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_BLOB_REQ:
		{
			logd("ATT_READ_BLOB_REQ");
			att_server_timer_start(conn_id);
			gatt_read_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_MULTI_REQ:
		{
			logd("ATT_READ_MULTI_REQ");
			att_server_timer_start(conn_id);
			gatt_read_multiple_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_READ_BY_GRP_TYPE_REQ:
		{
			logd("ATT_READ_BY_GRP_TYPE_REQ");
			att_server_timer_start(conn_id);
			gatt_read_by_group_type_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_FIND_INFO_REQ:
		{
			logd("ATT_FIND_INFO_REQ");
			att_server_timer_start(conn_id);
			gatt_find_info_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_FIND_BY_TYPE_VAL_REQ:
		{
			logd("ATT_FIND_BY_TYPE_VAL_REQ");
			att_server_timer_start(conn_id);
			gatt_find_by_type_value_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_WRITE_REQ:
		{
			logd("ATT_WRITE_REQ");
			att_server_timer_start(conn_id);
			gatt_write_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_WRITE_CMD:
		{
			logd("ATT_WRITE_CMD");
			gatt_write_command_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_SIGN_WRITE_CMD:
		{
			logd("ATT_SIGN_WRITE_CMD");
			gatt_signed_write_command_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_PREP_WRITE_REQ:
		{
			att_server_timer_start(conn_id);
			logd("ATT_PREP_WRITE_REQ");
			gatt_prepare_write_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
		case ATT_OPCODE_EXEC_WRITE_REQ:
		{
			att_server_timer_start(conn_id);
			logd("ATT_EXEC_WRITE_REQ");
			gatt_execute_write_req_cb(conn_id, opcode, in_buffer);
			ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
		}
		break;
		case ATT_OPCODE_HANDLE_VAL_CFM:
		{
			logd("ATT_HANDLE_VAL_CFM");
			att_server_timer_stop(conn_id);
			set_device_att_server_state(conn_id, ATT_DEVICE_IDLE);
			gatt_handle_value_confirmation_cb(conn_id, opcode, in_buffer);
			ret = STATUS_SUCCESS;
		}
		break;
#endif /* GATT_SERVER_SUPPORTED == TRUE */
		default:
		{
			logw("Invalid Opcode %02x",opcode);
			if (in_buffer)
			{
				p_input = in_buffer->data + in_buffer->offset;
				if (in_buffer->length < sizeof(handle))
					handle = 0;
				else
					STREAM_TO_UINT16(handle, p_input);
			}
			att_send_error_response(conn_id, opcode, handle, ATT_ERR_REQ_NOT_SUPPORTED);
			ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
		}
		break;
	}
	return ret;
}

/**********************************************************************
 * @fn  att_l2cap_connect_cb
 * @brief  ATT call back function from L2CAP layer to receive
 *				notification when new device is connected.
 * @param  device - connected device structure
 * @returns  None
 *
 *********************************************************************/
void att_l2cap_connect_cb(connected_device_t* device)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
#if (GATT_CLIENT_SUPPORTED == TRUE)
	osa_create_timer(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER, ATT_CLNT_TIMER_ISR, sizeof(ATT_CLNT_TIMER)/sizeof(osa_timer_static_t), att_client_timer_expire_cb, device->idx);
#endif
#if (GATT_SERVER_SUPPORTED == TRUE)
	osa_create_timer(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER, ATT_SRVR_TIMER_ISR, sizeof(ATT_SRVR_TIMER)/sizeof(osa_timer_static_t), att_server_timer_expire_cb, device->idx);
#endif
	device->att_device.att_mtu_size = ATT_MIN_MTU_LEN;
#if ((GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE))
	gatt_connect_cb(device);
#endif /* (GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE) */
}

/**********************************************************************
 * @fn  att_l2cap_disconnect_cb
 * @brief  ATT call back function from L2CAP layer to receive
 *				when device is disconnected.
 * @param  device - connected device structure
 * @returns  None
 *
 *********************************************************************/
void att_l2cap_disconnect_cb(connected_device_t* device)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
		return;
#endif
#if (GATT_CLIENT_SUPPORTED == TRUE)
	osa_delete_timer(&(device->att_device.att_client_timer_id), ATT_CLNT_TIMER);
#endif
#if (GATT_SERVER_SUPPORTED == TRUE)
	osa_delete_timer(&(device->att_device.att_server_timer_id), ATT_SRVR_TIMER);
#endif
	device->att_device.att_mtu_size = 0;
#if ((GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE))
	gatt_disconnect_cb(device);
#endif /* (GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE) */
}
