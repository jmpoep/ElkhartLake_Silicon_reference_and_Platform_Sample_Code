/** @file
  Heart Rate Profile (client) header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef HRP_COLLECTOR_H_
#define HRP_COLLECTOR_H_

#define HEART_RATE_MONITOR_SERVICE_UUID 	0x180D
#define HEART_RATE_MEASUREMENT_CHAR_UUID	0x2A37

#define BATTERY_SERVICE_UUID				0x180F
#define BATTERY_LEVEL_CHAR_UUID				0x2A19

#define CHARACTERISTIC_CONFIG_DESC_UUID		0x2902

#define HRP_RES_REGISTER_APP				1
#define HRP_RES_ADAPTER_ENABLED				2
#define HRP_RES_DEVICE_CONNECTED			3
#define HRP_RES_SERVICE_DISCOVERED			4
#define HRP_RES_READ_ATTRIBUTE				5
#define HRP_RES_WRITE_DESCRIPTOR			6
#define HRP_RES_NOTIFICATION				7
#define HRP_RES_NOTIFICATION_ENABLED		9
#define HRP_RES_NOTIFICATION_REGISTERED		10
#define HRP_RES_SCAN_COMPLETED				11

#define HRP_SCAN_TIMEOUT_SEC				5

#define HRP_PER_DEV_ATTR			128

typedef struct
{
	UINT8 opcode;
	UINT8 *param;
} hrp_req_elem_t;

typedef struct
{
	UINT16 value_length;
	UINT8 *value;
	gatt_attribute_t attribute;
} hrp_attr_read_cb_param_t;

typedef struct
{
	UINT8 value_len;
	UINT8* value;
	//gatt_characteristic_t *characteristic;
} hrp_notification_cb_param_t;

typedef struct
{
	BOOLEAN hrp_app_running;
	BOOLEAN hrp_app_closing;
	BOOLEAN hrp_is_connected;
	BOOLEAN is_hrp_read_req_pending;
	UINT8 heart_rate;
	UINT8 hrp_res_code;
	UINT8 app_handle;
	UINT8 num_discovered_devices;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 conn_id;
	gatt_attribute_t attr_db[HRP_PER_DEV_ATTR];
	queue_t hrp_res_q;
	UINT8 num_of_discover_req;
	discovered_device_t discovered_list[MAX_NUM_DISCOVERED_DEVICE];
	uuid_t heart_rate_monitor_service_uuid;
	uuid_t battery_service_uuid;
	uuid_t current_uuid_being_discovered;
	osa_semaphore_t msg_sem;
	osa_semaphore_t thread_sem;
} hrp_col_data_t;

#endif /* HRP_COLLECTOR_H_ */
