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

#ifndef ATT_H_
#define ATT_H_

#include "bt_types.h"
#include "device_struct.h"
#include "config_host.h"

#define ATT_MIN_MTU_LEN					23
#define ATT_MAX_MTU_LEN					240

#define ATT_TIMEOUT_VAL                 30

#define ATT_BUFFER_OFFSET               0 /*(UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE) */

#define ATT_DEVICE_IDLE                 0x00

#define ATT_INVALID_STATE	                    0xFF

/* Attribute payload Header length */
#define ATT_ERR_RESP_LEN                        0x05
#define ATT_MTU_XCHANGE_REQ_LEN                 0x03
#define ATT_READ_BY_GRP_TYPE_REQ_LEN            0x07
#define ATT_FIND_INFO_REQ_LEN                   0x05
#define ATT_FIND_BY_TYP_VAL_REQ_LEN             0x07
#define ATT_READ_BY_TYPE_REQ_LEN                0x07
#define ATT_READ_REQ_LEN                        0x03
#define ATT_READ_BLOB_REQ_LEN                   0x05
#define ATT_READ_MULTI_REQ_LEN                  0x01
#define ATT_WRITE_REQ_LEN                       0x03
#define ATT_WRITE_CMD_LEN                       0x03
#define ATT_PREPARE_WRITE_REQ_LEN               0x05
#define ATT_EXEC_WRITE_REQ_LEN                  0x02
#define ATT_HANDLE_VAL_CFM_LEN                  0x01
#define ATT_HANDLE_VAL_IND_LEN                  0x03
#define ATT_SIGN_WRITE_CMD_LEN                  0x03
#define ATT_NOTIFY_LEN                          0x03

#define ATT_MTU_XCHANGE_RSP_LEN                 0x03
#define ATT_READ_BY_TYPE_RSP_LEN                0x02
#define ATT_READ_RSP_LEN                        0x01
#define ATT_READ_BLOB_RSP_LEN                   0x01
#define ATT_READ_MULTI_RSP_LEN                  0x01
#define ATT_READ_BY_GRP_TYPE_RSP_LEN            0x02
#define ATT_WRITE_RSP_LEN                       0x01
#define ATT_FIND_INFO_RSP_LEN                   0x02
#define ATT_FIND_BY_TYPE_VAL_RSP_LEN            0x01
#define ATT_PREPARE_WRITE_RSP_LEN               0x05
#define ATT_EXEC_WRITE_RSP_LEN                  0x01

#define ATT_AUTH_SIGNATURE_LEN                  0x0C

/*********************************************************************
 *				ATT APIs
 ********************************************************************/


#if (GATT_CLIENT_SUPPORTED == TRUE)

INT8 att_read_by_type_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *attrib_type);
INT8 att_read_req(UINT8 conn_id, UINT16 att_handle);
INT8 att_read_blob_req(UINT8 conn_id, UINT16 att_handle, UINT16 offset);
INT8 att_read_multiple_req(UINT8 conn_id, UINT16 *handle_list);
INT8 att_read_by_group_type_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, UINT16 attrib_type);
INT8 att_write_req(UINT8 conn_id, UINT16 att_handle, buffer_t *buffer);
INT8 att_write_command(UINT8 conn_id, UINT16 att_handle, buffer_t *buffer);
INT8 att_find_info_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);
INT8 att_find_by_type_val_req(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, UINT16 att_type, uuid_t* uuid_to_find);
INT8 att_prepare_write_req(UINT8 conn_id,UINT16 att_handle, UINT16 val_offset, buffer_t *buffer);
INT8 att_execute_write_req(UINT8 conn_id, UINT8 flags);
INT8 att_signed_write_cmd(UINT8 conn_id, UINT16 att_handle, buffer_t* buffer, UINT8 *auth_signature);
INT8 att_send_handle_val_cfm(UINT8 conn_id);

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

INT8 att_mtu_xchange_req(UINT8 conn_id, UINT16 rx_mtu);

INT8 att_send_error_response(UINT8 conn_id, UINT8 req_opcode, UINT16 handle, UINT8 reason);
INT8 att_send_read_by_type_rsp(UINT8 conn_id ,UINT8 elem_len, buffer_t *buffer);

#if (GATT_SERVER_SUPPORTED == TRUE)
INT8 att_send_handle_val_indication(UINT8 conn_id, UINT16 att_handle, buffer_t* buffer);
/* ATT Response APIs */
INT8 att_send_mtu_xchange_rsp(UINT8 conn_id,UINT16 RxMtu);
INT8 att_send_read_rsp(UINT8 conn_id, buffer_t *buffer);
INT8 att_send_read_blob_rsp(UINT8 conn_id, buffer_t *buffer);
INT8 att_send_read_multi_rsp(UINT8 conn_id, buffer_t* buffer);
INT8 att_send_read_by_grp_type_rsp(UINT8 conn_id, UINT8 elem_len, buffer_t *buffer);
INT8 att_send_write_rsp(UINT8 conn_id);
INT8 att_send_find_info_rsp(UINT8 conn_id, UINT8 format, buffer_t *buffer);
INT8 att_send_find_by_type_val_rsp(UINT8 conn_id, buffer_t *buffer);
INT8 att_send_prepare_write_rsp(UINT8 conn_id,UINT16 att_handle, buffer_t *in_buffer, UINT16 offset);
INT8 att_send_execute_write_rsp(UINT8 conn_id);
INT8 att_send_value_notification(UINT8 conn_id, UINT16 att_handle, buffer_t *buffer);

#endif /* GATT_SERVER_SUPPORTED == TRUE */

/*********************************************************************
 *				Call back methods from L2CAP
 ********************************************************************/
/**
 * This method will be called from the l2cap layer when a connection to
 * a remote device is completed.
 */
void att_l2cap_connect_cb(connected_device_t *device);
void gatt_connect_cb(connected_device_t* device);
/**
 * This method is called when a link disconnection is completed.
 */
void att_l2cap_disconnect_cb(connected_device_t *device);
void gatt_disconnect_cb(connected_device_t* device);

/**
 * This method is called when data is received for ATT channel
 */
INT8 att_l2cap_recv_data_cb(UINT8 conn_id, buffer_t* in_buffer);
INT8 att_process_packet(UINT8 opcode, UINT8 conn_id, buffer_t *in_buffer);

INT8 att_init();
void att_cleanup();

#endif /* ATT_H_ */
