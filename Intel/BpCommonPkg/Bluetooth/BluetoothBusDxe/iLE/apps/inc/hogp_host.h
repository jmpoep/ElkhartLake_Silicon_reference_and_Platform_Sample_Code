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

#ifndef HOGP_HOST_H_
#define HOGP_HOST_H_

#define HUMAN_INTERFACE_DEVICE_SERIVCE_UUID 	0x1812
#define HID_REPORT_MAP_CHAR_UUID				0x2A4B
#define HID_REPORT_CHAR_UUID					0x2A4D
#define PROTOCOL_MODE_CHAR_UUID					0x2A4E
#define BOOT_KEYBOARD_INPUT_REPORT_CHAR_UUID	0x2A22
#define BOOT_KEYBOARD_OUTPUT_REPORT_CHAR_UUID	0x2A32
#define BOOT_MOUSE_INPUT_REPORT_CHAR_UUID		0x2A33

#define BATTERY_SERVICE_UUID				0x180F
#define BATTERY_LEVEL_CHAR_UUID				0x2A19

#define CHARACTERISTIC_CONFIG_DESC_UUID		0x2902
#define REPORT_REFERENCE_DESC_UUID			0x2908

#define HOGP_RES_REGISTER_APP				1
#define HOGP_RES_ADAPTER_ENABLED			2
#define HOGP_RES_DEVICE_CONNECTED			3
#define HOGP_RES_SERVICE_DISCOVERED			4
#define HOGP_RES_READ_ATTRIBUTE				5
#define HOGP_RES_WRITE_DESCRIPTOR			6
#define HOGP_RES_NOTIFICATION				7
#define HOGP_RES_NOTIFICATION_ENABLED		9
#define HOGP_RES_NOTIFICATION_REGISTERED	10
#define HOGP_RES_SCAN_COMPLETED				11
#define HOGP_RES_DEVICE_BONDED				12

#define HOGP_SCAN_TIMEOUT_SEC				5

#define HOGP_PER_DEV_ATTR					100
#define HOGP_MAX_DEV						2

#define DEVICE_BOOT_PROTOCOL_MODE			0
#define DEVICE_REPORT_PROTOCOL_MODE			1

#define MAX_NUM_REPORT_MAPS 10

#define ATT_MAX_VALUE_LEN 512

typedef struct
{
	UINT8 dev_id;
	UINT8 opcode;
	UINT8 *param;
} hogp_req_elem_t;

typedef struct
{
	UINT8 id;
	UINT16 handle;
} hogp_report_map_t;

typedef struct
{
	UINT8 conn_id;
	UINT8 protocol_mode;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	int device_fd;
	gatt_attribute_t attr_db[HOGP_PER_DEV_ATTR];
	hogp_report_map_t report_map[MAX_NUM_REPORT_MAPS];
} hogp_host_dev_data_t;

typedef struct
{
	BOOLEAN hogp_app_running;
	BOOLEAN hogp_app_closing;
	BOOLEAN hogp_app_busy;
	BOOLEAN hogp_thread_running;
	UINT8 app_handle;
	UINT8 num_discovered_devices;
	buffer_t *saved_rd_blob_value;
	queue_t hogp_res_q;
	UINT8 num_of_discover_req;
	hogp_host_dev_data_t device_list[HOGP_MAX_DEV];
	discovered_device_t discovered_list[MAX_NUM_DISCOVERED_DEVICE];
	osa_semaphore_t msg_sem;
	osa_semaphore_t thread_sem;
} hogp_host_data_t;

void hogp_start_boot_host(UINT8 *bdaddr);
void hogp_start_report_host(UINT8 *bdaddr);
void hogp_stop(UINT8 *bdaddr);

#endif /* HOGP_HOST_H_ */
