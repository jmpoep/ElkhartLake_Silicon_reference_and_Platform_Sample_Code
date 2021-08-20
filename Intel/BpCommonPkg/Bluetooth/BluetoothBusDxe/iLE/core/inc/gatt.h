/** @file
  GATT profile header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef GATT_H_
#define GATT_H_

#include "bt_types.h"
#include "att.h"
#include "l2cap.h"
#include "config_host.h"

#define GATT_PRIMARY_SERVICE_TYPE_USING_UUID	1
#define GATT_INCLUDED_SERVICE_TYPE_USING_UUID	2
#define GATT_PRIMARY_SERVICE_TYPE_ALL			3

#define GATT_UUID_PRIM_SRV 			0x2800
#define GATT_UUID_SEC_SRV 			0x2801
#define GATT_UUID_INCLUDED_SRV		0x2802
#define GATT_UUID_CHARACTERISTIC 	0x2803
#define GATT_UUID_CLIENT_CONFIG		0x2902

#define GATT_STATE_INVALID    0x00
#define GATT_STATE_IDLE       0x01
#define GATT_STATE_CONNECTED  0x02
#define GATT_STATE_PROCESSING 0x03

#define GATT_CONNECTED    0x01
#define GATT_DISCONNECTED 0x02

#define GATT_OPERATION_IDLE										0
#define GATT_OPERATION_DISCOVER_PRIMARY_SERVICE					1
#define GATT_OPERATION_DISCOVER_ALL_PRIMARY_SERVICE				2
#define GATT_OPERATION_DISCOVER_INCLUDED_SERVICE				3
#define GATT_OPERATION_DISCOVER_CHARACTERISTIC					4
#define GATT_OPERATION_DISCOVER_DESCRIPTOR						5

#define GATT_OPERATION_READ_ATTRIBUTE	 						50
#define GATT_OPERATION_READ_LONG_ATTRIBUTE		 				51
#define GATT_OPERATION_READ_UUID_CHARACTERISTIC 				52
#define GATT_OPERATION_READ_MULTIPLE_CHARACTERISTIC 			53

#define GATT_OPERATION_WRITE_ATTRIBUTE		 					60
#define GATT_OPERATION_WRITE_LONG_ATTRIBUTE		 				61
#define GATT_OPERATION_WRITE_RELIABLE_CHARACTERISTIC 			62

#define GATT_SERVER_OPERATION_INDICATION 						20
#define GATT_SERVER_OPERATION_READ_CHARACTERISTIC				21
#define GATT_SERVER_OPERATION_READ_ATTRIBUTE_USING_UUID			22
#define GATT_SERVER_OPERATION_READ_LONG_CHARACTERISTIC			23
#define GATT_SERVER_OPERATION_READ_MULTIPLE_CHARACTERISTIC		24
#define GATT_SERVER_OPERATION_READ_DESCRIPTOR					25
#define GATT_SERVER_OPERATION_READ_LONG_DESCRIPTOR				26

#define GATT_SERVER_OPERATION_WRITE_CHARACTERISTIC				27
#define GATT_SERVER_OPERATION_WRITE_LONG_CHARACTERISTIC			28
#define GATT_SERVER_OPERATION_WRITE_DESCRIPTOR					29
#define GATT_SERVER_OPERATION_WRITE_LONG_DESCRIPTOR				30
#define GATT_SERVER_OPERATION_WRITE_EXECUTE						31

#define VALUE_NOTIFY_PROPERTY	0x10
#define VALUE_INDICATE_PROPERTY	0x20

#define VALUE_CHARACTERISTIC_CONFIGURE_NOTIFICATION 0x0001
#define VALUE_CHARACTERISTIC_CONFIGURE_INDICATION 0x0002
#define VALUE_ENABLE_NOTIFY(x)		(x | 0x01)
#define VALUE_ENABLE_INDICATE(x)	(x | 0x02)
#define VALUE_DISABLE_NOTIFY(x)		(x & 0xFE)
#define VALUE_DISABLE_INDICATE(x)	(x & 0xFC)
#define IS_ATTRIBUTE_PROPERTY_READ(x)					((x & 0x02) >> 1)
#define IS_ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE(x)		((x & 0x04) >> 2)
#define IS_ATTRIBUTE_PROPERTY_WRITE(x)					((x & 0x08) >> 3)
#define IS_ATTRIBUTE_PROPERTY_NOTIFY(x)				((x & 0x10) >> 4)
#define IS_ATTRIBUTE_PROPERTY_INDICATE(x)				((x & 0x20) >> 5)
#define IS_ATTRIBUTE_PROPERTY_AUTH_SIGNED_WRITE(x)		((x & 0x40) >> 6)
#define IS_ATTRIBUTE_EXTENDED_PROPERTY(x)				((x & 0x80) >> 7)

#define START_HANDLE 								1
#define END_HANDLE 									0xFFFF
#define	BT_16_BIT_UUID_FORMAT						1
#define	BT_128_BIT_UUID_FORMAT						2

#define GATT_ELEM_LEN_PRIM_SRV_BY_UUID_DISC			4
#define GATT_ELEM_LEN_PRIM_SRV_DISC					6
#define GATT_ELEM_LEN_CHAR_DISC						7

/*********************************************************************
 * 				GATT APIs
 *********************************************************************/

INT8 gatt_init();
void gatt_cleanup();

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)
INT8 gatt_request_mtu(UINT8 conn_id, UINT16 mtu_size);
void gatt_mtu_exchange_req_cb(UINT8 conn_id, buffer_t *buffer);
INT8 gatt_handle_mtu_resp_cb(UINT8 conn_id, buffer_t *buffer);
UINT16 get_device_mtu(UINT8 conn_id);
buffer_t* get_att_buffer(UINT16 value_length);
#endif

#if (GATT_CLIENT_SUPPORTED == TRUE)
INT8 gatt_discover_primary_service(UINT8 conn_id, uuid_t *filter_uuid);
INT8 gatt_discover_included_service(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);
INT8 gatt_discover_characteristic(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid);
INT8 gatt_discover_descriptor(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);

INT8 gatt_read_attribute_value(UINT8 conn_id, UINT16 att_opcode, UINT16 att_id, UINT16 offset);
INT8 gatt_read_characteristic_value_using_uuid(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *char_uuid);
INT8 gatt_read_multiple_characteristic_value(UINT8 conn_id, UINT16 *handle_list);
INT8 gatt_write_attribute_command(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, buffer_t* buffer);
INT8 gatt_write_attribute_value(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer);
INT8 gatt_send_indication_confirmation(UINT8 conn_id);
INT8 gatt_send_signed_write(UINT8 conn_id, UINT16 att_id, buffer_t* buffer, UINT8* signature);
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

#if (GATT_SERVER_SUPPORTED == TRUE)
INT8 gatt_send_attr_read_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, buffer_t* buffer);
INT8 gatt_send_attr_write_rsp(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, UINT16 offset, buffer_t* in_buffer);
INT8 gatt_send_value_notification(UINT8 conn_id, UINT16 att_id, buffer_t* in_buffer);
INT8 gatt_send_value_indication(UINT8 conn_id, UINT16 att_id, buffer_t* in_buffer);
INT8 gatt_set_service_change_config(UINT8 conn_id, BOOLEAN is_notify);
BOOLEAN gatt_get_service_change_config(UINT8 conn_id);
#endif /* GATT_SERVER_SUPPORTED == TRUE */

/*********************************************************************
 * 				ATT -> GATT Callbacks
 *********************************************************************/
#if (GATT_CLIENT_SUPPORTED == TRUE)
void gatt_client_connect_cb(connected_device_t* device);
void gatt_client_disconnect_cb(connected_device_t* device);
void gatt_error_resp_cb(UINT8 conn_id, UINT8 req_opcode, UINT16 att_handle, UINT8 err_code);
void gatt_discover_prim_srv_by_uuid_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_read_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_read_multiple_rsp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_prep_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_exec_write_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_discover_desc_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_read_by_type_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_read_by_group_type_resp_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_notify_cb(UINT8 conn_id, UINT8 att_opcode, buffer_t *in_buffer);
void gatt_client_timeout_cb(UINT8 conn_id, UINT8 state);
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

void gatt_read_by_type_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_server_timeout_cb(UINT8 conn_id);

#if (GATT_SERVER_SUPPORTED == TRUE)
void gatt_server_connect_cb(UINT8 conn_id);
void gatt_server_disconnect_cb(UINT8 conn_id);
void gatt_read_by_group_type_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_find_by_type_value_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_find_info_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_read_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_read_blob_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_read_multiple_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_write_command_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_signed_write_execute_cb(UINT8 conn_id, UINT8 opcode, buffer_t* in_buffer);
void gatt_signed_write_command_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_prepare_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_execute_write_req_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
void gatt_handle_value_confirmation_cb(UINT8 conn_id, UINT8 opcode, buffer_t* buffer);
#endif /* GATT_SERVER_SUPPORTED == TRUE */

#endif /* GATT_H_ */
