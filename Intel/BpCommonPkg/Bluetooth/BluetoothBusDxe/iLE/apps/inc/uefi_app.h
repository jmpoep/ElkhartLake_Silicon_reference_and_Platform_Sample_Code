/** @file
  UEFI application header functions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef UEFI_APP_H_
#define UEFI_APP_H_
#define UEFI_APP_PER_DEV_ATTR 65535
#include "device_struct.h"
#include "BluetoothBusDxe.h"
#define BDADDR_ARR_TO_BDADDR_STRUCT(s,a,t) memcpy((s)->Address, (a), BD_ADDR_LEN); (s)->Type = t;

#define UEFI_APP_HID_INFO_SIGNATURE SIGNATURE_32 ('u', 'a', 'h', 'i')

#define UEFI_APP_MAX_HID_SRV 2

typedef enum {
	READ_HID_INFO_STATE_INIT,
	READ_HID_INFO_STATE_REPORT_MAP,
	READ_HID_INFO_STATE_PNP_ID,
	READ_HID_INFO_STATE_BATTERY_LEVEL,
	READ_HID_INFO_STATE_EXTERNAL_DESC,
	READ_HID_INFO_STATE_EXTERNAL_REPORT_REFER,
	READ_HID_INFO_STATE_REPORT_REFER,
	READ_HID_INFO_STATE_DONE
} read_hid_info_state_t;

typedef struct {
	UINTN Signature;
	LIST_ENTRY Link;
	UINT16 handle;
	UINT16 uuid;
	UINT16 type;
	UINTN data_len;
	UINT8 *data;
	union {
		UINT16 end_handle;
		UINT8 property;
	} extra_info;
} uefi_app_hid_info_t;

typedef struct {
	UINT16 handle;
	UINT16 uuid;
	UINT16 type;
	UINT8 property;
} cur_hid_info_t;

typedef struct
{
	UINT8 num_of_discover_req;
	UINT16 offset;
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 bdaddr_type;
	UINT8 idaddr[BD_ADDR_LEN];
	UINT8 idaddr_type;
	UINT16 request_handle;
	UINT16 free_handle;
	buffer_t *saved_rd_blob_value;
	buffer_t *prep_wr_value;
	BT_LE_SB_DEV *BtLeSbDev;
	EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION read_cb;
	VOID *read_cb_context;
	EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION write_cb;
	VOID *write_cb_context;
	EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION notify_cb;
	VOID *notify_cb_context;
	LIST_ENTRY hid_info;
	read_hid_info_state_t read_hid_info_state;
	cur_hid_info_t cur_hid_info;
	UINT16 hid_service_handle_index[UEFI_APP_MAX_HID_SRV];
	UINT8 cur_hid_srv;
	BOOLEAN is_discovery_completed;
	BOOLEAN store_hid_info;
}remote_device_t;

typedef struct
{
	remote_device_t remote_device_list[MAX_NUM_CONNECTED_DEVICE];
	BTHC_DEV *BtHcDev;
	UINT8 iocap, oobflag, authreq, enckeysize;
	BOOLEAN doing_bond;
} uefi_app_data_t;

#define UEFI_APP_HID_INFO_FROM_LINK(a) \
	CR(a, uefi_app_hid_info_t, Link, UEFI_APP_HID_INFO_SIGNATURE)

EFI_STATUS stack_init(BTHC_DEV *BtHcDev);
EFI_STATUS stack_scan(UINT32 Timeout, EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER *ScanParameter);
EFI_STATUS stack_connect(BLUETOOTH_LE_ADDRESS *bd_addr, EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER *conn_params, BOOLEAN auto_reconnect, BOOLEAN do_bonding);
EFI_STATUS stack_disconnect(BLUETOOTH_LE_ADDRESS *bd_addr, UINT8 conn_id, UINT8 reason);
EFI_STATUS stack_get_local_data(EFI_BLUETOOTH_CONFIG_DATA_TYPE data_type, UINTN *data_size, VOID *data);
EFI_STATUS stack_set_local_data(EFI_BLUETOOTH_CONFIG_DATA_TYPE data_type, UINTN data_size, VOID *data);
EFI_STATUS stack_smp_auth(BLUETOOTH_LE_ADDRESS *bd_addr, EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE data_type, UINTN length, VOID* data);
EFI_STATUS stack_send_att_req(UINT8 conn_id, UINT16 DataSize, VOID *Data, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback, VOID *Context);
EFI_STATUS stack_register_notification_indication(UINT8 conn_id, UINT16 Handle, BOOLEAN IsIndication, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback, VOID *Context);
void stack_cleanup();
void stack_switch_to_sync_event();
EFI_STATUS stack_remove_device(BLUETOOTH_LE_ADDRESS *bd_addr);

#endif
