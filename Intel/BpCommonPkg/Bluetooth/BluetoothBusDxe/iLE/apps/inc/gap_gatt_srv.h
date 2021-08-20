/** @file
  GAP profile header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef GAP_GATT_SRV_H_
#define GAP_GATT_SRV_H_

/* GAP Service */
#define GAP_SERVICE_UUID						0x1800
#define DEVICE_NAME_CHARACTERISTIC				0x2a00
#define APPEARANCE_CHARACTERISTIC				0x2a01
#define PEER_CONNECTION_PARAM_CHARACTERISTIC	0x2A04
#define CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC	0x2AA6
/* GATT Service */
#define GATT_SERVICE_UUID						0x1801
#define SERVICE_CHANGED_CHARACTERISTIC			0x2a05
#define GATT_CLIENT_CHAR_CONFIG_UUID			0x2902
/* Device Info service */
#define DEVICE_INFO_SERVICE_UUID				0x180a
#define MANUFACTURER_NAME_STRING_CHAR			0x2a29
#define MODEL_NUMBER_STRING_CHAR				0x2a24

/* att id value index */
typedef enum
{
	DEVICE_NAME_CHARACTERISTIC_ID,
	APPEARANCE_CHARACTERISTIC_ID,
	PEER_CONNECTION_PARAM_CHARACTERISTIC_ID,
	CENTRAL_ADDR_RESOLUTION_CHARACTERISTIC_ID,
	SERVICE_CHANGED_CHARACTERISTIC_ID,
	GATT_CLIENT_CHAR_CONFIG_UUID_ID,
	GATT_GAP_SRV_ATT_MAX_ID,
} att_value_index_t;

/*GAP connection interval service data */
#define GAP_CONN_INT_100MS						0x0050
#define GAP_CONN_INT_200MS						0x00A0
#define GAP_CONN_PREF_SLAVE_LATENCY				0x0000
#define GAP_CONN_INT_10000MS					0x03E8

#define GAP_CONNECTION_STATE_ACL_CONNECTED		2	/* This value should be same as value defined in gap.h */

#define GAP_GATT_SERVICE_QUEUE_LEN				2

#define GAP_GATT_SRV_APP_REGISTERED				0
#define GAP_GATT_READ_REQ						1
#define GAP_GATT_WRITE_REQ						2
#define GAP_GATT_CHAR_ADDED						3

#define CLIENT_CFG_VALUE_IND_ENABLE				0x0002
#define CLIENT_CFG_VALUE_NOTIFY_ENABLE			0x0001
#define CLIENT_CFG_VALUE_DISABLE				0x0000

#define SERVICE_CHANGED_CHARACTERISTIC_VALUE_LEN	4

typedef struct
{
	UINT8 remote_bdaddr[BD_ADDR_LEN];
	UINT16 att_id;
} service_changed_notification_reg_elem_t;

#define GAP_GATT_SRV_MAX_VALUE_LENGTH 10
typedef struct
{
	UINT16 att_id;
	UINT16 fixed_len; /* = 0 for variable length */
	UINT8 length;
	UINT8 value[GAP_GATT_SRV_MAX_VALUE_LENGTH];
} att_val_elem_t;

typedef struct
{
	UINT8 app_handle;
	BOOLEAN srv_changed_notify_reg_list[MAX_NUM_CONNECTED_DEVICE];
	UINT16 gap_srv_handle;
	UINT16 gatt_srv_handle;
	uuid_t gap_srv_uuid;
	uuid_t gatt_srv_uuid;
	att_val_elem_t att_val_map[GATT_GAP_SRV_ATT_MAX_ID]; /* Note: Adjust this number with number of char and desc */
}gap_gatt_srv_data_t;

void send_service_changed_notification(UINT16 start_handle, UINT16 end_handle);

#endif /* GAP_GATT_SRV_H_ */
