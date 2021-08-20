/** @file
  Profile manager header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef PROFILE_MGR_H_
#define PROFILE_MGR_H_

#include "device_struct.h"
#include "gatt.h"
#include "int_interface.h"
#include "config_host.h"

#if (TEST_CODE==TRUE && LE_PING_ENABLE==TRUE)
void pm_read_authpayload_timeout_cb(UINT8 dev_idx, UINT16 authpayload_timeout);
#endif //TEST_CODE && LE_PING_ENABLE

#define PM_STATE_PROCESSING		1
#define PM_STATE_IDLE			2
#define PM_STATE_INVALID		3

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)

UINT16 pm_get_att_mtu(UINT8 conn_id);

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE */

INT8 pm_register_application(device_control_callbacks_t* dev_cb,
		gatt_callbacks_t* gatt_cb,
		register_application_cb_t register_application_cb);
typedef struct
{
	device_control_callbacks_t* dev_cb;
	gatt_callbacks_t* gatt_cb;
	register_application_cb_t register_application_cb;
} pm_register_application_param_t;

/*
 * Gatt_DeRegister(UINT8 app_index)
 */
INT8 pm_deregister_application(UINT8 app_index);
typedef struct
{
	UINT8 app_handle;
} pm_deregister_application_param_t;

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

INT8 pm_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout);

typedef struct
{
	trans_id_t trans_id;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 addr_type;
	UINT16 scan_int;
	UINT16 scan_win;
	UINT16 conn_int_min;
	UINT16 conn_int_max;
	UINT16 conn_lat;
	UINT16 sup_timeout;
} pm_connect_param_t;

INT8 pm_conn_param_update(trans_id_t trans_id, UINT8 conn_id, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);

INT8 pm_auto_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, BOOLEAN enable);
typedef struct
{
	BOOLEAN enable;
	trans_id_t trans_id;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 addr_type;
}pm_auto_connect_param_t;

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

INT8 pm_req_handler(interface_req_elem_t* req);
typedef struct
{
	UINT8 conn_id;
	trans_id_t trans_id;
	uuid_t filter_uuid;
} pm_discover_primary_service_param_t;

typedef struct
{
	UINT8 conn_id;
	UINT16 start_handle;
	UINT16 end_handle;
	trans_id_t trans_id;
	uuid_t filter_uuid;
} pm_discover_included_service_param_t;

typedef pm_discover_included_service_param_t pm_discover_characteristic_param_t;
typedef pm_discover_included_service_param_t pm_discover_descriptor_param_t;

typedef struct
{
	UINT8 conn_id;
	trans_id_t trans_id;
	gatt_attribute_read_param_t read_param;
} pm_read_attribute_value_param_t;

typedef struct
{
	UINT8 conn_id;
	UINT8 att_opcode;
	UINT16 att_id;
	UINT16 offset;
	trans_id_t trans_id;
	buffer_t buffer;
} pm_write_attribute_value_param_t;

INT8 pm_register_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, BOOLEAN is_register);
typedef struct
{
	BOOLEAN is_register;
	UINT8 conn_id;
	UINT16 att_id;
	trans_id_t trans_id;
} pm_register_notification_param_t;

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

INT8 pm_disconnect(trans_id_t trans_id, UINT8 conn_id, UINT8 reason);
typedef struct
{
	trans_id_t trans_id;
	UINT8 conn_id;
	UINT8 reason;
} pm_disconnect_param_t;

typedef struct
{
	UINT8 conn_idx;
	UINT16 interval_min;
	UINT16 interval_max;
	UINT16 conn_latency;
	UINT16 sup_timeout;
	trans_id_t trans_id;
} pm_update_conn_params_t;

INT8 pm_conn_param_update_req(trans_id_t trans_id, UINT8 conn_id, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);


#if (TEST_CODE==TRUE && LE_PING_ENABLE==TRUE)
INT8 pm_read_authpayload_timeout(trans_id_t trans_id, UINT8 conn_id);
#endif //TEST_CODE && LE_PING_ENABLE

typedef struct
{
	UINT8 conn_id;
	trans_id_t trans_id;
	UINT16 mtu_size;
} pm_set_att_mtu_param_t;

INT8 pm_init();
void pm_cleanup();

void pm_connect_error_cb(UINT8 *bdaddr, UINT8 addr_type, UINT8 status);
void pm_connect_cb(connected_device_t* device, UINT8 result);
void pm_disconnect_cb(connected_device_t* device, UINT8 result);
void pm_conn_param_update_cb(UINT8 status, UINT8 conn_id, UINT16 interval, UINT16 latency, UINT16 timeout);

BOOLEAN is_conn_used(app_data_t *app_data, connected_device_t *device);

#if (GATT_CLIENT_SUPPORTED == TRUE)

void pm_att_mtu_changed_cb(UINT8 conn_id, UINT16 updated_mtu_size);
void pm_primary_service_discovered_cb(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished);
void pm_included_service_discovered_cb(UINT8 conn_id, UINT16 inc_handle, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished);
void pm_characteristic_discovered_cb(UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished);
void pm_descriptor_discovered_cb(UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished);
void pm_on_read_attribute_cb(UINT8 conn_id, UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t *buffer);

void pm_on_attribute_write_cb(UINT8 conn_id, UINT8 opcode, UINT8 status, UINT16 att_id, UINT16 offset, buffer_t* buffer);
void pm_on_characteristic_notification_cb(UINT8 conn_id, UINT16 att_id, buffer_t* buffer, BOOLEAN is_indication);

void pm_gatt_client_timeout_cb(UINT8 conn_id);
void pm_data_signing_complete_cb(UINT8 conn_id, UINT8 status, UINT8* signed_data);
#endif /* GATT_CLIENT_SUPPORTED == TRUE */

#endif /* PROFILE_MGR_H_ */
