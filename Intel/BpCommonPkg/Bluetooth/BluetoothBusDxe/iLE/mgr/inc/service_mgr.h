/** @file
  Service manager header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef SERVICE_MGR_H_
#define SERVICE_MGR_H_

#include "device_struct.h"
#include "int_interface.h"
#include "config_host.h"

#define SERVICE_CHANGED_CHARACTERISTIC_UUID		0x2a05
#define SM_REQ_OPCODE_ADD_SERVICE			API_REQ_OPCODE_ADD_SERVICE
#define SM_REQ_OPCODE_ADD_CHARACTERISTIC	API_REQ_OPCODE_ADD_CHARACTERISTIC
#define SM_REQ_OPCODE_ADD_DESCRIPTOR		API_REQ_OPCODE_ADD_DESCRIPTOR
#define SM_REQ_OPCODE_START_SERVICE			API_REQ_OPCODE_START_SERVICE
#define SM_REQ_OPCODE_REMOVE_SERVICE		API_REQ_OPCODE_REMOVE_SERVICE

#define SM_REQ_OPCODE_SEND_CHARACTERISTIC_READ_RESPONSE	API_REQ_OPCODE_SEND_CHARACTERISTIC_READ_RESPONSE
#define SM_REQ_OPCODE_SEND_DESCRIPTOR_READ_RESPONSE		API_REQ_OPCODE_SEND_DESCRIPTOR_READ_RESPONSE
#define SM_REQ_OPCODE_SEND_WRITE_RESPONSE				API_REQ_OPCODE_SEND_WRITE_RESPONSE

UINT16 get_att_idx_from_hdl(UINT16 att_handle);
UINT16 get_max_att_handle();
void sm_read_attribute(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset);

#if (GATT_SERVER_SUPPORTED == TRUE)

typedef struct
{
	UINT8 service_type;
	UINT8 num_of_incl_srv;
	UINT8 num_of_char;
	UINT8 num_of_desc;
	trans_id_t trans_id;
	uuid_t uuid;
} sm_add_service_param_t;

typedef struct
{
	trans_id_t trans_id;
	UINT8 service_type;
	UINT16 start_handle;
	UINT16 end_handle;
	uuid_t uuid;
} sm_add_include_service_param_t;

typedef struct
{
	UINT8 property;
	UINT16 permission;
	trans_id_t trans_id;
	uuid_t uuid;
} sm_add_characteristic_param_t;

typedef struct
{
	trans_id_t trans_id;
	UINT16 permission;
	uuid_t uuid;
} sm_add_descriptor_param_t;

typedef struct
{
	trans_id_t trans_id;
} sm_start_service_param_t;

typedef struct
{
	trans_id_t trans_id;
	UINT16 service_handle;
} sm_remove_service_param_t;

INT8 sm_req_handler(interface_req_elem_t* req);

INT8 sm_remove_app_all_services(UINT8 app_handle);

INT8 sm_service_add_req_handler(interface_req_elem_t* req);
typedef struct
{
	UINT8 status;
	UINT8 conn_id;
	UINT8 att_opcode;
	UINT16 att_id;
	trans_id_t trans_id;
	buffer_t buffer;
} sm_send_attribute_read_rsp_param_t;

typedef struct
{
	UINT8 status;
	UINT8 conn_id;
	UINT8 att_opcode;
	UINT16 att_id;
	UINT16 offset;
	trans_id_t trans_id;
	buffer_t buffer;
} sm_send_attribute_write_rsp_param_t;



typedef struct
{
	BOOLEAN need_resp;
	UINT8 conn_id;
	UINT16 att_id;
	trans_id_t trans_id;
	buffer_t buffer;
} sm_send_notification_param_t;

typedef struct
{
	BOOLEAN is_notify;
	UINT8 conn_id;
	trans_id_t trans_id;
} sm_set_service_change_config_param_t;

void sm_write_attribute(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id,  UINT16 offset, buffer_t* buffer);
void sm_exec_write(UINT8 conn_id, BOOLEAN is_execute);
void sm_indication_confirmataion(UINT8 conn_id, UINT16 att_id);
BOOLEAN sm_get_service_change_config(UINT8 conn_id);

void sm_sign_verify_complete_cb(UINT8 conn_id, UINT8 status);
#endif /* GATT_SERVER_SUPPORTED == TRUE */

void sm_connect_cb(connected_device_t *device);
void sm_disconnect_cb(connected_device_t *device);
INT8 sm_init();
void sm_cleanup();

#endif /* DEVICE_MGR_H_ */
