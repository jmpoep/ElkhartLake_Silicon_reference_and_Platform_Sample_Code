/** @file
  FMP locator header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef FMP_LOCATOR_H_
#define FMP_LOCATOR_H_

#include "bt_types.h"

#define IMMEDIATE_ALERT_UUID 	0x1802
#define ALERT_LEVEL_UUID 		0x2A06

#define FMP_RES_REGISTER_APP				1
#define FMP_RES_ADAPTER_ENABLED				2
#define FMP_RES_DEVICE_CONNECTED			3
#define FMP_RES_SERVICE_DISCOVERED			4
#define FMP_RES_SCAN_COMPLETED				5

#define FMP_SCAN_TIMEOUT_SEC				5

#define IS_ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE(x)		((x & 0x04) >> 2)
#define IS_ATTRIBUTE_PROPERTY_WRITE(x)					((x & 0x08) >> 3)

#define FMP_PER_DEV_ATTR			128

typedef struct
{
	UINT8 opcode;
	UINT8 *param;
} fmp_req_elem_t;

typedef struct
{
	BOOLEAN app_running;
	BOOLEAN is_connected;
	BOOLEAN app_closing;
	UINT8 app_handle;
	UINT8 fmp_res_code;
	UINT8 num_discovered_devices;
	queue_t fmp_res_q;
	UINT8 num_of_discover_req;
	gatt_attribute_t attr_db[FMP_PER_DEV_ATTR];
	discovered_device_t discovered_list[MAX_NUM_DISCOVERED_DEVICE];
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 conn_id;
	uuid_t immediate_alert_uuid;
	osa_semaphore_t msg_sem;
	osa_semaphore_t thread_sem;
} fmp_loc_data_t;

#endif /* FMP_LOCATOR_H_ */
