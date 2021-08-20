/** @file
  UEFI test application.

Copyright (c) 2017 - 2018, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#if (UEFI_APP == TRUE)
#include "osa_types.h"
#include "uefi_app.h"
#include "hogp_host.h"
#include "device_struct.h"
#include "tl.h"
#include <Library/BluetoothLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <IndustryStandard/BluetoothAssignedNumbers.h>

#define MODULE_DBG_LVL UEFI_APP_DBG_LVL

#include "log.h"

#define SET_ATTRIBUTE_TYPE(_a,_t) {(_a)->Header.Type.Length = UUID_16BIT_TYPE_LEN; (_a)->Header.Type.Data.Uuid16 = _t; }

#define IS_ATTRIBUTE_PROPERTY_READ(x)			((x & 0x02) >> 1)
#define IS_ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE(x)	((x & 0x04) >> 2)
#define IS_ATTRIBUTE_PROPERTY_WRITE(x)			((x & 0x08) >> 3)
#define IS_ATTRIBUTE_PROPERTY_NOTIFY(x)			((x & 0x10) >> 4)
#define IS_ATTRIBUTE_PROPERTY_INDICATE(x)		((x & 0x20) >> 5)
#define IS_ATTRIBUTE_PROPERTY_AUTH_SIGNED_WRITE(x)	((x & 0x40) >> 6)
#define IS_ATTRIBUTE_EXTENDED_PROPERTY(x)		((x & 0x80) >> 7)

#define ATTR_TYPE_CLIENT_CHARACTERISTIC_CONFIG_DESCRIPTOR_UUID		0x2902
#define UEFI_APP_MAX_HID_INFO_LEN					1000

#define HID_BD_ADDR_STR_LEN    24
#define HID_BDADDR_TO_STRING(str, addr, type) {register int ijk; for (ijk = 0; ijk < 6; ijk++) UnicodeSPrint(&str[ijk*2], (HID_BD_ADDR_STR_LEN - ijk*2), L"%02x", addr[ijk]); UnicodeSPrint(&str[ijk*2], (HID_BD_ADDR_STR_LEN - ijk*2), L"%02x", type); str[ijk*2 + 2] = '\0'; }


char *str_code[ATT_ERR_MAX] =
{
		"ATT_SUCCESS",
		"ATT_ERR_INVALID_HANDLE",
		"ATT_ERR_READ_NOT_PREMITTED",
		"ATT_ERR_WRITE_NOT_PERMITTED",
		"ATT_ERR_INVALID_PDU",
		"ATT_ERR_INSUFF_AUTHENTICATION",
		"ATT_ERR_REQ_NOT_SUPPORTED",
		"ATT_ERR_INVALID_OFFSET",
		"ATT_ERR_INSUFF_AUTHORIZATION",
		"ATT_ERR_PREP_QUEUE_FULL",
		"ATT_ERR_ATTRIB_NOT_FOUND",
		"ATT_ERR_ATTRIB_NOT_LONG",
		"ATT_ERR_INSUFF_ENCR_KEY_SIZE",
		"ATT_ERR_INVALID_ATTRIB_VAL_LENGTH",
		"ATT_ERR_UNLIKELY",
		"ATT_ERR_INSUFF_ENCR",
		"ATT_ERR_UNSUPPORTED_GRP_TYPE",
		"ATT_ERR_INSUFF_RESOURCE",
		"ATT_ERR_LOCAL_ERROR"
};

typedef struct {
	BLUETOOTH_LE_ADDRESS remote_addr;
	smp_bonding_key_t keys;
} uefi_app_cur_bonding_info_t;

static volatile BOOLEAN init_complete = FALSE;
static UINT8 uefi_app_handle;
static uefi_app_data_t uefi_app_data;
static BLUETOOTH_LE_ADDRESS cur_req_addr;
static uefi_app_cur_bonding_info_t cur_bonding_info;

typedef enum {
  write_request = 0x1,
  write_command,
  signed_write,
  reliable_write,
} write_type_t;

static EFI_STATUS read_attr(UINT8 conn_id, UINT16 handle, UINT16 end_handle, uuid_t *uuid, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION callback, VOID *context);

static BOOLEAN is_valid_ble_address(BLUETOOTH_LE_ADDRESS *bd_addr)
{
	BLUETOOTH_LE_ADDRESS dummy_addr;

	ASSERT (bd_addr != NULL);

	ZeroMem (&dummy_addr, sizeof(BLUETOOTH_LE_ADDRESS));
	return (BOOLEAN) (CompareMem (bd_addr, &dummy_addr, sizeof (BLUETOOTH_LE_ADDRESS)) != 0);
}

static uuid_t* uefi_uuid_to_ile_uuid(uuid_t *ile_uuid, EFI_BLUETOOTH_UUID *uefi_uuid)
{
	ile_uuid->length = uefi_uuid->Length;

	if (uefi_uuid->Length == UUID_16BIT_TYPE_LEN)
		ile_uuid->value.uuid16 = uefi_uuid->Data.Uuid16;
	if (uefi_uuid->Length == UUID_32BIT_TYPE_LEN)
		ile_uuid->value.uuid32 = uefi_uuid->Data.Uuid32;
	if (uefi_uuid->Length == UUID_128BIT_TYPE_LEN)
		CopyMem(ile_uuid->value.uuid128, uefi_uuid->Data.Uuid128, UUID_128BIT_TYPE_LEN);
	return ile_uuid;
}

static EFI_BLUETOOTH_UUID* ile_uuid_to_uefi_uuid(EFI_BLUETOOTH_UUID *uefi_uuid, uuid_t *ile_uuid)
{
	uefi_uuid->Length = ile_uuid->length;

	if (ile_uuid->length == UUID_16BIT_TYPE_LEN)
		uefi_uuid->Data.Uuid16 = ile_uuid->value.uuid16;
	if (ile_uuid->length == UUID_32BIT_TYPE_LEN)
		uefi_uuid->Data.Uuid32 = ile_uuid->value.uuid32;
	if (ile_uuid->length == UUID_128BIT_TYPE_LEN)
		CopyMem(uefi_uuid->Data.Uuid128, ile_uuid->value.uuid128, UUID_128BIT_TYPE_LEN);
	return uefi_uuid;
}

static UINT16 get_last_empty_attr_id(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	for (att_id = att_handle + 1; att_id < BT_LE_PER_DEV_ATTR; att_id ++)
	{
		if (uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[att_id])
			return att_id - 1;
	}
	return BT_LE_PER_DEV_ATTR;
}

static EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO* get_owner_prim_srv(UINT8 conn_id, UINT16 att_handle)
{
	UINT16 att_id;
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;
	for (att_id = att_handle; ; att_id --)
	{
		attr = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[att_id];
		if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypePrimaryService))
			return (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[att_id];
	}
}

char* get_string_status(UINT8 att_status)
{
	if(att_status < ATT_ERR_MAX)
		return str_code[att_status];
	return "UNKNOWN_ERROR";
}

void dump_att_db(UINT8 conn_id)
{
	char str[40];
	UINT16 idx;
	EFI_BLUETOOTH_ATTRIBUTE_HEADER *attr;
	uuid_t uuid;
	for (idx = 0; idx < BT_LE_PER_DEV_ATTR; idx++)
	{
		attr = uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[idx];
		if (attr)
		{
			ZeroMem(str, sizeof(str));
			if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(attr, BluetoothGattTypePrimaryService))
			{
				EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *val = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO*) attr;
				uefi_uuid_to_ile_uuid(&uuid, &val->ServiceUuid);
				UUID_TO_STRING(str, uuid);
				logd("index: %d handle:0x%04x attr_type:PrimaryService end_handle:0x%04x uuid:%s", idx, attr->AttributeHandle, val->EndGroupHandle, str);
			}
			if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(attr, BluetoothGattTypeInclude))
			{
				EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO *val = (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO*) attr;
				uefi_uuid_to_ile_uuid(&uuid, &val->ServiceUuid);
				UUID_TO_STRING(str, uuid);
				logd("index: %d handle:0x%04x attr_type:IncludeService start_handle:0x%04x end_handle:0x%04x uuid:%s", idx, attr->AttributeHandle, val->StartGroupHandle, val->EndGroupHandle, str);
			}
			if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(attr, BluetoothGattTypeCharacteristic))
			{
				EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *val = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO*) attr;
				uefi_uuid_to_ile_uuid(&uuid, &val->CharacteristicUuid);
				UUID_TO_STRING(str, uuid);
				logd("index: %d handle:0x%04x attr_type:Characteristic uuid:%s", idx, attr->AttributeHandle, str);
			}
			if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(attr, BluetoothGattTypeCharacteristicExtendedProperties))
			{
				EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *val = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO*) attr;
				uefi_uuid_to_ile_uuid(&uuid, &val->CharacteristicDescriptorUuid);
				UUID_TO_STRING(str, uuid);
				logd("index: %d handle:0x%04x attr_type:Descriptor uuid:%s", idx, attr->AttributeHandle, str);
			}
		}
	}
}

void uefi_app_scan_result_cb(trans_id_t trans_id, discovered_device_t *device)
{
	char bdaddr_str[BD_ADDR_STR_LEN], direct_bdaddr_str[BD_ADDR_STR_LEN];
	UINT8 AdvertisementData[BLUETOOTH_LE_ADV_DATA_MAX_SIZE];
	BLUETOOTH_LE_ADDRESS BD_ADDR, DIRECT_BD_ADDR;
	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
	BDADDR_TO_STRING(direct_bdaddr_str, device->direct_addr);
	logi("Found Device %02x:%02x:%02x:%02x:%02x:%02x  %a", device->bdaddr[0], device->bdaddr[1], device->bdaddr[2], device->bdaddr[3], device->bdaddr[4], device->bdaddr[5], device->localname);
	logi("direct_bdaddr_str: %a", device->bdaddr[0], direct_bdaddr_str);

#if 0
	EFI_BLUETOOTH_SCAN_CALLBACK_INFORMATION CallbackInfo;
	CallbackInfo.RemoteDeviceState = 0;
	memset(&CallbackInfo.ClassOfDevice, 0, sizeof(CallbackInfo.ClassOfDevice));
	memcpy(CallbackInfo.BDAddr.Address, device->bdaddr, BD_ADDR_LEN);
	memcpy(CallbackInfo.RemoteDeviceName, device->localname, sizeof(device->localname));
	uefi_app_data.BtHcDev->ScanCallBackFunc (&uefi_app_data.BtHcDev->BluetoothConfig, uefi_app_data.BtHcDev->ScanCallBackFuncContext, &CallbackInfo);
#endif

	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, device->bdaddr, device->addr_type);
	BDADDR_ARR_TO_BDADDR_STRUCT(&DIRECT_BD_ADDR, device->direct_addr, device->direct_addr_type);
	CopyMem(AdvertisementData, device->adv_data, device->adv_data_len);

	BtLeUpdateDevice(uefi_app_data.BtHcDev, &BD_ADDR, NULL, &DIRECT_BD_ADDR, device->rssi, device->tx_power, device->appearance, device->role_supported, (UINT8*) device->localname, AdvertisementData, device->adv_data_len, TRUE);
}

void uefi_app_scan_completed_cb(trans_id_t trans_id)
{
	//uefi_app_data.BtHcDev->ScanCallBackFunc (&uefi_app_data.BtHcDev->BluetoothConfig, uefi_app_data.BtHcDev->ScanCallBackFuncContext, NULL);
	//BtHciEventHandlerInquiryComplete(uefi_app_data.BtHcDev, NULL, 0);

	logd("uefi_app_scan_completed_cb");

	if (uefi_app_data.BtHcDev->LeScanCallBackFunc)
		uefi_app_data.BtHcDev->LeScanCallBackFunc(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeScanCallBackFuncContext, NULL);

    if (log_file)
    	log_file->Flush(log_file);
	//display_discovered_device_list();
}

void uefi_smp_cback(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 event, UINT8 length, UINT8* data)
{
	UINT8 uefi_event = 0;
	BLUETOOTH_LE_ADDRESS BD_ADDR;
	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, bdaddr, bdaddr_type);
	logd("%s", __func__);

	switch(event)
	{
	case SMP_AUTHORISATION_REQ_EVT:
		uefi_event = EfiBluetoothSmpAuthorizationRequestEvent;
		break;
	case SMP_KEY_READY_EVT:
		uefi_event = EfiBluetoothSmpPasskeyReadyEvent;
		break;
	case SMP_PASSKEY_REQ_EVT:
		uefi_event = EfiBluetoothSmpPasskeyRequestEvent;
		break;
	case SMP_NUMERIC_COMPARISON_EVT:
		uefi_event = EfiBluetoothSmpNumericComparisonEvent;
		break;
	}

	if (uefi_app_data.BtHcDev->LeSmpCallBack)
		uefi_app_data.BtHcDev->LeSmpCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpCallBackContext, &BD_ADDR, uefi_event, length, data);

}

void uefi_stack_initialized_cb(BOOLEAN initialized)
{
	trans_id_t new_trans_id = 0;
	LIST_ENTRY *Link;
	LIST_ENTRY *BtLePairedDevLink;
	BT_LE_PAIRED_DEV_INFO *BtLePairedDevInfo;

	logi("");
	if (initialized)
	{
		add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
		iLE_smp_register(new_trans_id, &uefi_smp_cback);

		BtLePairedDevLink = &uefi_app_data.BtHcDev->BtLePairedList;

		for (Link = BtLePairedDevLink->ForwardLink; Link != BtLePairedDevLink; Link = Link->ForwardLink)
		{
			BtLePairedDevInfo = CR (Link, BT_LE_PAIRED_DEV_INFO, Link, BT_LE_PAIRED_DEV_INFO_SIGNATURE);
			/* Add device to Auto Connect list */
			iLE_auto_connect(new_trans_id, BtLePairedDevInfo->BDAddr.Address, BtLePairedDevInfo->BDAddr.Type, TRUE);
		}

		init_complete = TRUE;
	}
	else
		init_complete = FALSE;
}

static void uefi_app_send_bonding_info()
{
	BT_LE_DEV_INFO *dev_info;
	UINT8 dummy_key[SMP_MAX_KEY_LEN] = { 0 };
	UINT8 dummy_rand[SMP_LTK_RAND_LEN] = { 0 };

	logd("");

	dev_info = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, &cur_bonding_info.remote_addr);
	if (!dev_info) return;

	if(cur_bonding_info.keys.keys_distributed && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpKeysDistributed, sizeof(cur_bonding_info.keys.keys_distributed), &cur_bonding_info.keys.keys_distributed);
	if(cur_bonding_info.keys.key_size && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpKeySize, sizeof(cur_bonding_info.keys.key_size), &cur_bonding_info.keys.key_size);
	if(cur_bonding_info.keys.key_type && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpKeyType, sizeof(cur_bonding_info.keys.key_type), &cur_bonding_info.keys.key_type);
	if(memcmp(cur_bonding_info.keys.peer_ltk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpPeerLTK, sizeof(cur_bonding_info.keys.peer_ltk), cur_bonding_info.keys.peer_ltk);
#if (PRIVACY_FEATURE)
	if(memcmp(cur_bonding_info.keys.peer_irk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpPeerIRK, sizeof(cur_bonding_info.keys.peer_irk), cur_bonding_info.keys.peer_irk);
#endif /* PRIVACY_FEATURE */
#if (SIGNED_WRITE)
	if(memcmp(cur_bonding_info.keys.peer_csrk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpPeerCSRK, sizeof(cur_bonding_info.keys.peer_csrk), cur_bonding_info.keys.peer_csrk);
#endif /* SIGNED_WRITE */
	if(memcmp(cur_bonding_info.keys.peer_rand, dummy_rand, SMP_LTK_RAND_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpPeerRand, sizeof(cur_bonding_info.keys.peer_rand), cur_bonding_info.keys.peer_rand);
	if(cur_bonding_info.keys.peer_ediv && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpPeerEDIV, sizeof(cur_bonding_info.keys.peer_ediv), &cur_bonding_info.keys.peer_ediv);
	if(memcmp(cur_bonding_info.keys.local_ltk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpLocalLTK, sizeof(cur_bonding_info.keys.local_ltk), cur_bonding_info.keys.local_ltk);
#if (PRIVACY_FEATURE)
	if(memcmp(cur_bonding_info.keys.local_irk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpLocalIRK, sizeof(cur_bonding_info.keys.local_irk), cur_bonding_info.keys.local_irk);
#endif /* PRIVACY_FEATURE */
#if (SIGNED_WRITE)
	if(memcmp(cur_bonding_info.keys.local_csrk, dummy_key, SMP_MAX_KEY_LEN) && uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
		uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &dev_info->IDAddr, EfiBluetoothSmpLocalCSRK, sizeof(cur_bonding_info.keys.local_csrk), cur_bonding_info.keys.local_csrk);
#endif /* SIGNED_WRITE */

	memset(&cur_bonding_info, 0, sizeof(uefi_app_cur_bonding_info_t));
}

static UINT16 att_db_get_idx_from_hdl(UINT8 conn_id, UINT16 handle)
{
	UINT16 index;
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;

	index = 0;
	while(index < BT_LE_PER_DEV_ATTR)
	{
		attr = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index];

		if (!attr)
		{
			return BT_LE_PER_DEV_ATTR;
		}

		if ((attr->Header.AttributeHandle - 1 < handle) && (attr->EndGroupHandle >= handle))
		{
			return MIN(index + handle - attr->Header.AttributeHandle, BT_LE_PER_DEV_ATTR);
		}

		// Location of Next Primary Service
		index = index + attr->EndGroupHandle - attr->Header.AttributeHandle + 1;
	}

	return BT_LE_PER_DEV_ATTR;
}

EFI_STATUS uefi_app_discover_prim_srv(UINT8 conn_id)
{
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	iLE_discover_primary_service(new_trans_id, conn_id, NULL);
	return EFI_SUCCESS;
}

/**
 * Delete HID information from persistent storage for given BD Address
 */
static void delete_hid_info(BLUETOOTH_LE_ADDRESS *bd_addr)
{
	CHAR16 hid_bd_addr_str[HID_BD_ADDR_STR_LEN];
	EFI_STATUS status;

	if (bd_addr == NULL)
		return;

	logd("");
	memset(hid_bd_addr_str, 0, sizeof(hid_bd_addr_str));
	HID_BDADDR_TO_STRING(hid_bd_addr_str, bd_addr->Address, bd_addr->Type);

	status = gRT->SetVariable(hid_bd_addr_str, &gEfiBluetoothLeConfigProtocolGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				0, NULL);
	if (EFI_ERROR (status))
		loge("Error while deleting HID Information");
}

/**
 * Store HID information in persitent storage for given connection id
 */
static void store_hid_info(UINT8 conn_id)
{
	BLUETOOTH_LE_ADDRESS remote_bd_addr;
	UINTN data_size = 0;
	UINT8 *data, *p;
	LIST_ENTRY *Link;
	uefi_app_hid_info_t *hid_info;
	BT_LE_DEV_INFO *dev_info;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];
	CHAR16 hid_bd_addr_str[HID_BD_ADDR_STR_LEN];
	EFI_STATUS status;

	logi("");
	BDADDR_ARR_TO_BDADDR_STRUCT(&remote_bd_addr, dev->bdaddr, dev->bdaddr_type);

	data = AllocateZeroPool(UEFI_APP_MAX_HID_INFO_LEN);
	if (!data)
	{
		loge("AllocateZeroPool failed for %d bytes", UEFI_APP_MAX_HID_INFO_LEN);
		return;
	}

	p = data;

	Link = GetFirstNode(&dev->hid_info);
	while (!IsNull(&dev->hid_info, Link))
	{
		if ((data_size + sizeof(hid_info->handle) + sizeof(hid_info->type) + sizeof(hid_info->uuid)) > UEFI_APP_MAX_HID_INFO_LEN)
			break;
		hid_info = UEFI_APP_HID_INFO_FROM_LINK(Link);
		UINT16_TO_STREAM(p, hid_info->handle);
		UINT16_TO_STREAM(p, hid_info->type);
		UINT16_TO_STREAM(p, hid_info->uuid);
		data_size += (sizeof(hid_info->handle) + sizeof(hid_info->type) + sizeof(hid_info->uuid));

		if (hid_info->type == BluetoothGattTypePrimaryService)
		{
			/* For Primary Service store the end handle */
			if ((data_size + sizeof(hid_info->extra_info.end_handle)) > UEFI_APP_MAX_HID_INFO_LEN)
				break;
			UINT16_TO_STREAM(p, hid_info->extra_info.end_handle);
			data_size += sizeof(hid_info->extra_info.end_handle);
		}
		else if(hid_info->type == BluetoothGattTypeCharacteristic)
		{
			/* For Characteristic store the property */
			if ((data_size + sizeof(hid_info->extra_info.property)) > UEFI_APP_MAX_HID_INFO_LEN)
				break;
			UINT8_TO_STREAM(p, hid_info->extra_info.property);
			data_size += sizeof(hid_info->extra_info.property);
		}

		/* Store data length */
		if ((data_size + sizeof(UINT16)) > UEFI_APP_MAX_HID_INFO_LEN)
			break;
		UINT16_TO_STREAM(p, (UINT16)hid_info->data_len);
		data_size += sizeof(UINT16);

		/* Store data if available */
		if (hid_info->data_len && hid_info->data)
		{
			if ((data_size + hid_info->data_len) > UEFI_APP_MAX_HID_INFO_LEN)
				break;
			memcpy(p, hid_info->data, hid_info->data_len);
			p += hid_info->data_len;
			data_size += hid_info->data_len;
		}

		Link = GetNextNode(&dev->hid_info, Link);
	}

	dev_info = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, &remote_bd_addr);
	if (!dev_info) return;

	logd("Storing HID Information size: %d", data_size);
	memset(hid_bd_addr_str, 0, sizeof(hid_bd_addr_str));
	HID_BDADDR_TO_STRING(hid_bd_addr_str, dev_info->IDAddr.Address, dev_info->IDAddr.Type);

	status = gRT->SetVariable(hid_bd_addr_str, &gEfiBluetoothLeConfigProtocolGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
				data_size, data);
	if (EFI_ERROR (status))
		loge("Error while storing HID Information");

	FreePool(data);
}

static EFI_STATUS uefi_app_disconnect(UINT8 conn_id, UINT8 reason)
{
	trans_id_t new_trans_id = 0;
	logd("Trying to disconnect from device %u", conn_id);
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	iLE_disconnect(new_trans_id, conn_id, reason);
	return EFI_SUCCESS;
}

static void discovery_completed(UINT8 conn_id)
{
	BLUETOOTH_LE_ADDRESS        BD_ADDR;
	BT_LE_PAIRED_DEV_INFO       *BtLePairedDevInfo;
	trans_id_t new_trans_id = 0;

	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, uefi_app_data.remote_device_list[conn_id].bdaddr, uefi_app_data.remote_device_list[conn_id].bdaddr_type);

	logd("");

	BtLePairedDevInfo = BtFindLePairedDevByBDAddr(uefi_app_data.BtHcDev, &BD_ADDR);

	BtInitLeSbDev (uefi_app_data.BtHcDev, uefi_app_data.remote_device_list[conn_id].BtLeSbDev);
	BtAddLeSb(uefi_app_data.BtHcDev, uefi_app_data.remote_device_list[conn_id].BtLeSbDev);

	if (BtLePairedDevInfo != NULL)
	{
		/* Send storage information to upper layer application */
		if (!(memcmp(cur_bonding_info.remote_addr.Address, BD_ADDR.Address, sizeof(BD_ADDR.Address))))
		{
			uefi_app_send_bonding_info();

			if (uefi_app_data.remote_device_list[conn_id].store_hid_info)
			{
				/* Store HID Information in Storage */
				store_hid_info(conn_id);
			}
		}

		add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
		if (is_valid_ble_address(&BtLePairedDevInfo->IDAddr))
			iLE_auto_connect(new_trans_id, BtLePairedDevInfo->IDAddr.Address, BtLePairedDevInfo->IDAddr.Type, TRUE);
		else
			iLE_auto_connect(new_trans_id, BtLePairedDevInfo->BDAddr.Address, BtLePairedDevInfo->BDAddr.Type, TRUE);
	}

	if (uefi_app_data.BtHcDev->LeConnCompCallBack)
	{
		if (BtLePairedDevInfo != NULL)
			uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeEncrypted, &BD_ADDR, NULL, 0);
		else
			uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeConnected, &BD_ADDR, NULL, 0);
	}
}

/**
 * Store HID information in local list
 */
static void store_hid_info_to_list(UINT8 conn_id, UINT16 handle, UINT16 type, UINT16 uuid16, UINT16 property, UINT8* data, UINTN data_len)
{
	uefi_app_hid_info_t *hid_info;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	hid_info = AllocateZeroPool(sizeof(uefi_app_hid_info_t));
	if (!hid_info)
	{
		loge("AllocateZeroPool failed for %d bytes", sizeof(uefi_app_hid_info_t));
		return;
	}
	hid_info->Signature = UEFI_APP_HID_INFO_SIGNATURE;
	hid_info->handle = handle;
	hid_info->type = type;
	hid_info->uuid = uuid16;
	hid_info->extra_info.end_handle = property;
	if (data && (data_len > 0))
	{
		hid_info->data = AllocateZeroPool(data_len);
		ASSERT (hid_info->data != NULL);
		memcpy(hid_info->data, data, data_len);
		hid_info->data_len = data_len;
	}
	InsertTailList(&dev->hid_info, &hid_info->Link);
}

/**
 * Find Charateristic in ATT DB for input UUID
 */
static EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *find_charateristic_from_uuid(UINT8 conn_id, UINT16 uuid16, UINTN start_index, UINT16 prev_handle, UINTN *found_index)
{
	UINTN index;
	EFI_BLUETOOTH_UUID uuid;
	EFI_BLUETOOTH_ATTRIBUTE_HEADER *attr;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *char_val;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	uuid.Length = UUID_16BIT_TYPE_LEN;
	uuid.Data.Uuid16 = uuid16;

	for (index = start_index; index < BT_LE_PER_DEV_ATTR; index++)
	{
		attr = dev->BtLeSbDev->AttrDatabase[index];
		if (attr == NULL) {
			continue;
		}

		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (attr, BluetoothGattTypeCharacteristic))
		{
			char_val = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO*) attr;
			if ((BluetoothUuidCompare(&char_val->CharacteristicUuid, &uuid)) && (char_val->Header.AttributeHandle > prev_handle))
			{
				if (found_index != NULL)
					*found_index = index;
				return char_val;
			}
		}
	}

	return NULL;
}

/**
 * Find Descriptor in ATT DB for input UUID
 */
static EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *find_descriptor_from_uuid(UINT8 conn_id, UINT16 uuid16, UINTN start_index)
{
	UINTN index;
	EFI_BLUETOOTH_UUID uuid;
	EFI_BLUETOOTH_ATTRIBUTE_HEADER *attr;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *desc_val;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	uuid.Length = UUID_16BIT_TYPE_LEN;
	uuid.Data.Uuid16 = uuid16;

	for (index = start_index; index < BT_LE_PER_DEV_ATTR; index++)
	{
		attr = dev->BtLeSbDev->AttrDatabase[index];
		if (attr == NULL) {
			continue;
		}

		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (attr, BluetoothGattTypeCharacteristicExtendedProperties))
		{
			desc_val = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO*) attr;
			if (BluetoothUuidCompare(&desc_val->CharacteristicDescriptorUuid, &uuid))
			{
				return desc_val;
			}
		}
		else
		{
			break;
		}
	}

	return NULL;
}

/**
 * Find HID Report Charateristic in ATT DB and read corresponding
 * Report Reference Descriptor
 */
static void find_hid_report_charateristic(UINT8 conn_id, UINT16 prev_handle)
{
	UINTN index;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *char_val;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *desc_val;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	dev->read_hid_info_state = READ_HID_INFO_STATE_DONE;

	/* Find HID Report Characteristic */
	char_val = find_charateristic_from_uuid(conn_id, BluetoothGattTypeHidReport, dev->hid_service_handle_index[dev->cur_hid_srv] + 1, prev_handle, &index);
	if (char_val != NULL)
	{
		logd("Found HID Report Char: 0x%04x", char_val->CharacteristicValueHandle);

		/* Store data */
		store_hid_info_to_list(conn_id, char_val->CharacteristicValueHandle,
				BluetoothGattTypeCharacteristic, BluetoothGattTypeHidReport,
				char_val->CharacteristicProperties, NULL, 0);

		dev->read_hid_info_state = READ_HID_INFO_STATE_REPORT_REFER;
#if (UEFI_HOGP_PTS == TRUE)
		/* HID Report Characteristic Value is not useful in normal scenario,
		 * so read this only for PTS test cases
		 */
		read_attr(conn_id, char_val->CharacteristicValueHandle, 0, NULL, NULL, NULL);
#endif
		/* Find Client Characteristic Config Descriptor */
		desc_val = find_descriptor_from_uuid(conn_id, ATTR_TYPE_CLIENT_CHARACTERISTIC_CONFIG_DESCRIPTOR_UUID, index + 2);
		if (desc_val != NULL)
		{
			logd("Found Client Configuration Descritpor handle: 0x%04x", desc_val->Header.AttributeHandle);

			/* Store data */
			store_hid_info_to_list(conn_id, desc_val->Header.AttributeHandle,
					BluetoothGattTypeCharacteristicExtendedProperties,
					ATTR_TYPE_CLIENT_CHARACTERISTIC_CONFIG_DESCRIPTOR_UUID,
					0, NULL, 0);

			dev->read_hid_info_state = READ_HID_INFO_STATE_REPORT_REFER;
#if (UEFI_HOGP_PTS == TRUE)
		/* HID Report CCCD value is not useful in normal scenario,
		 * so read this only for PTS test cases
		 */
			read_attr(conn_id, desc_val->Header.AttributeHandle, 0, NULL, NULL, NULL);
#endif
		}

		/* Find Report Reference Descriptor */
		desc_val = find_descriptor_from_uuid(conn_id, BluetoothGattTypeDescReportRefer, index + 2);
		if (desc_val != NULL)
		{
			logd("Found Report Reference Descritpor handle: 0x%04x", desc_val->Header.AttributeHandle);
			dev->cur_hid_info.handle = desc_val->Header.AttributeHandle;
			dev->cur_hid_info.type = BluetoothGattTypeCharacteristicExtendedProperties;
			dev->cur_hid_info.uuid = BluetoothGattTypeDescReportRefer;
			dev->cur_hid_info.property = 0;
			dev->read_hid_info_state = READ_HID_INFO_STATE_REPORT_REFER;
			read_attr(conn_id, desc_val->Header.AttributeHandle, 0, NULL, NULL, NULL);
		}
	}
}

/**
 * Read Required HID Characteristic and Descriptor sequentially and
 * store the information in local database for future use
 */
static void read_hid_report_data(UINT8 conn_id, UINT16 att_handle, UINT8 *data, UINTN data_length)
{
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *char_val = NULL;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *desc_val = NULL;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	logd("");

	if ((att_handle == 0) || (att_handle != dev->cur_hid_info.handle) ||
		(data == NULL) || (data_length == 0))
		return;

	switch(dev->read_hid_info_state)
	{
	case READ_HID_INFO_STATE_REPORT_MAP:

		/* Store data */
		store_hid_info_to_list(conn_id, att_handle,
				dev->cur_hid_info.type,
				dev->cur_hid_info.uuid,
				dev->cur_hid_info.property, data, data_length);

		/* Read External Report Reference Reference Descriptor if available */
		desc_val = find_descriptor_from_uuid(conn_id, BluetoothGattTypeDescExternalReportRefer, att_db_get_idx_from_hdl(conn_id, att_handle) + 1);
		if (desc_val != NULL)
		{
			logd("Found External Report Reference handle: 0x%04x", desc_val->Header.AttributeHandle);
			dev->cur_hid_info.handle = desc_val->Header.AttributeHandle;
			dev->cur_hid_info.type = BluetoothGattTypeCharacteristicExtendedProperties;
			dev->cur_hid_info.uuid = BluetoothGattTypeDescExternalReportRefer;
			dev->cur_hid_info.property = 0;
			dev->read_hid_info_state = READ_HID_INFO_STATE_EXTERNAL_DESC;
			read_attr(conn_id, desc_val->Header.AttributeHandle, 0, NULL, NULL, NULL);
			break;
		}
		else
		{
			/* If any External Report Reference Reference Descriptor is not available,
			 * No need to read the External Report Refence Characteristic
			 */
			dev->read_hid_info_state = READ_HID_INFO_STATE_EXTERNAL_REPORT_REFER;
		}
	case READ_HID_INFO_STATE_EXTERNAL_DESC:
		if (dev->read_hid_info_state == READ_HID_INFO_STATE_EXTERNAL_DESC)
		{
			UINT16 uuid16;
			UINTN index;

			data++; //ATT Opcode
			STREAM_TO_UINT16(uuid16, data);
			logd("External Report Characteristic UUID: 0x%04x", uuid16);

			/* Read External Report Characteristic */
			char_val = find_charateristic_from_uuid(conn_id, uuid16, 0, 0, &index);
			if (char_val != NULL)
			{
				/* Find Report Reference Descriptor */
				desc_val = find_descriptor_from_uuid(conn_id, BluetoothGattTypeDescReportRefer, index + 2);
				if (desc_val != NULL)
				{
					logd("Found Report Reference Descritpor handle: 0x%04x", desc_val->Header.AttributeHandle);
					dev->cur_hid_info.handle = desc_val->Header.AttributeHandle;
					dev->cur_hid_info.type = BluetoothGattTypeCharacteristicExtendedProperties;
					dev->cur_hid_info.uuid = BluetoothGattTypeDescReportRefer;
					dev->cur_hid_info.property = 0;
					dev->read_hid_info_state = READ_HID_INFO_STATE_EXTERNAL_REPORT_REFER;
					read_attr(conn_id, desc_val->Header.AttributeHandle, 0, NULL, NULL, NULL);
					break;
				}
			}
		}
	case READ_HID_INFO_STATE_EXTERNAL_REPORT_REFER:
		/* Read PnP ID */
		char_val = find_charateristic_from_uuid(conn_id, BluetoothGattTypePnPID, 0, 0, NULL);
		if (char_val != NULL)
		{
			logd("Found PnP ID value handle: 0x%04x", char_val->CharacteristicValueHandle);
			dev->cur_hid_info.handle = char_val->CharacteristicValueHandle;
			dev->cur_hid_info.type = BluetoothGattTypeCharacteristic;
			dev->cur_hid_info.uuid = BluetoothGattTypePnPID;
			dev->cur_hid_info.property = char_val->CharacteristicProperties;
			dev->read_hid_info_state = READ_HID_INFO_STATE_PNP_ID;
			read_attr(conn_id, char_val->CharacteristicValueHandle, 0, NULL, NULL, NULL);
			break;
		}
	case READ_HID_INFO_STATE_PNP_ID:
		/* Read Battery Level */
		char_val = find_charateristic_from_uuid(conn_id, BluetoothGattTypeBatteryLevel, 0, 0, NULL);
		if (char_val != NULL)
		{
			logd("Found Battery Level value handle: 0x%04x", char_val->CharacteristicValueHandle);
			dev->cur_hid_info.handle = char_val->CharacteristicValueHandle;
			dev->cur_hid_info.type = BluetoothGattTypeCharacteristic;
			dev->cur_hid_info.uuid = BluetoothGattTypeBatteryLevel;
			dev->cur_hid_info.property = char_val->CharacteristicProperties;
			dev->read_hid_info_state = READ_HID_INFO_STATE_BATTERY_LEVEL;
			read_attr(conn_id, char_val->CharacteristicValueHandle, 0, NULL, NULL, NULL);
			break;
		}
	case READ_HID_INFO_STATE_BATTERY_LEVEL:
		find_hid_report_charateristic(conn_id, 0);
		break;
	case READ_HID_INFO_STATE_REPORT_REFER:
		/* Store data */
		store_hid_info_to_list(conn_id, att_handle,
				dev->cur_hid_info.type,
				dev->cur_hid_info.uuid,
				dev->cur_hid_info.property, data, data_length);

		find_hid_report_charateristic(conn_id, att_handle);
		break;
	default:
		break;
	}

	if(dev->read_hid_info_state == READ_HID_INFO_STATE_DONE)
	{
		/* No new report reference descritor has been found */

		/* Check for more HID services if exists*/
		if ((++dev->cur_hid_srv < UEFI_APP_MAX_HID_SRV) && (dev->hid_service_handle_index[dev->cur_hid_srv] > 0))
		{
			/* Read Report Map */
			char_val = find_charateristic_from_uuid(conn_id, BluetoothGattTypeHidReportMap, dev->hid_service_handle_index[dev->cur_hid_srv] + 1, 0, NULL);
			if (char_val != NULL)
			{
				logd("Found Report Map value handle: 0x%04x", char_val->CharacteristicValueHandle);
				dev->cur_hid_info.handle = char_val->CharacteristicValueHandle;
				dev->cur_hid_info.type = BluetoothGattTypeCharacteristic;
				dev->cur_hid_info.uuid = BluetoothGattTypeHidReportMap;
				dev->cur_hid_info.property = char_val->CharacteristicProperties;
				dev->read_hid_info_state = READ_HID_INFO_STATE_REPORT_MAP;
				read_attr(conn_id, char_val->CharacteristicValueHandle, 0, NULL, NULL, NULL);
			}
		}
		else
		{
			logd("Service Discovery completed");
			dev->is_discovery_completed = TRUE;
			discovery_completed(conn_id);
		}
	}

}

/**
 * Check if Remote device supports HID service or not. if Remote device
 * support HID service then read required HID Characteristic sequentially and
 * store the information in local database for future use.
 */
static void check_hid_support(UINT8 conn_id)
{
	UINTN index, cur_hid_srv_index = 0;
	EFI_BLUETOOTH_UUID uuid;
	EFI_BLUETOOTH_ATTRIBUTE_HEADER *attr;
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *ServiceVal;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *char_val;
	BOOLEAN is_hid_supported = FALSE;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	logd("");

	uuid.Length = UUID_16BIT_TYPE_LEN;
	uuid.Data.Uuid16 = BluetoothUuidHumanInterfaceDevice;

	for (index = 0; index < BT_LE_PER_DEV_ATTR; index++)
	{
		attr = dev->BtLeSbDev->AttrDatabase[index];
		if (attr == NULL) {
			break;
		}

		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (attr, BluetoothGattTypePrimaryService))
		{
			ServiceVal = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) attr;
			if (BluetoothUuidCompare(&ServiceVal->ServiceUuid, &uuid))
			{
				logd("Remote device supports HID service");
				if (cur_hid_srv_index < UEFI_APP_MAX_HID_SRV)
				{
					dev->hid_service_handle_index[cur_hid_srv_index++] = (UINT16)index;
					is_hid_supported = TRUE;
				}

				/* Store data */
				store_hid_info_to_list(conn_id, ServiceVal->Header.AttributeHandle,
						BluetoothGattTypePrimaryService,
						BluetoothUuidHumanInterfaceDevice,
						ServiceVal->EndGroupHandle, NULL, 0);

				if (cur_hid_srv_index >= UEFI_APP_MAX_HID_SRV)
					break;
			}
		}
	}

	if (is_hid_supported)
	{
		/* Read Report Map */
		char_val = find_charateristic_from_uuid(conn_id, BluetoothGattTypeHidReportMap, dev->hid_service_handle_index[dev->cur_hid_srv] + 1, 0, NULL);
		if (char_val != NULL)
		{
			logd("Found Report Map value handle: 0x%04x", char_val->CharacteristicValueHandle);
			dev->cur_hid_info.handle = char_val->CharacteristicValueHandle;
			dev->cur_hid_info.type = BluetoothGattTypeCharacteristic;
			dev->cur_hid_info.uuid = BluetoothGattTypeHidReportMap;
			dev->cur_hid_info.property = char_val->CharacteristicProperties;
			dev->read_hid_info_state = READ_HID_INFO_STATE_REPORT_MAP;
			read_attr(conn_id, char_val->CharacteristicValueHandle, 0, NULL, NULL, NULL);
		}
	}
	else
	{
		dev->store_hid_info = FALSE;
		dev->is_discovery_completed = TRUE;
		discovery_completed(conn_id);
	}
}

/**
 * Check if HID information is already available in persistent storage.
 * If HID information is available then map those information to Remote device
 * Attribute database
 */
static BOOLEAN is_service_discovery_required(UINT8 conn_id)
{
	UINTN data_size;
	UINT8 *data, *p;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];
	UINT16 handle = 0;
	UINT16 type;
	UINT16 uuid;
	UINT16 index;
	UINT16 value_len = 0;
	UINT8 property = 0;
	UINT16 end_handle = 0;
	EFI_STATUS status;
	CHAR16 hid_bd_addr_str[HID_BD_ADDR_STR_LEN];

	logi("");
	data = NULL;
	data_size = 0;
	memset(hid_bd_addr_str, 0, sizeof(hid_bd_addr_str));
	HID_BDADDR_TO_STRING(hid_bd_addr_str, dev->bdaddr, dev->bdaddr_type);

	status = gRT->GetVariable(hid_bd_addr_str, &gEfiBluetoothLeConfigProtocolGuid,
				NULL, &data_size, NULL);

	if (data_size)
	{
		data = AllocateZeroPool(data_size);
		if (!data)
		{
			loge("AllocateZeroPool failed for %d bytes", data_size);
			return TRUE; //Return TRUE to force service discovery
		}

		status = gRT->GetVariable(hid_bd_addr_str, &gEfiBluetoothLeConfigProtocolGuid,
				NULL, &data_size, data);
		if(!EFI_ERROR(status))
		{
			p = data;
			if (data_size >= sizeof(handle))
			{
				STREAM_TO_UINT16(handle, p);
				data_size -= sizeof(handle);
			}

			if (handle == 0)
			{
				logd("Peer device does not support HID");
				FreePool(data);
				return TRUE;
			}

			logd("Peer HID info found in DB");
			InitializeListHead (&uefi_app_data.remote_device_list[conn_id].hid_info);

			/* Restore it to local Attribute database */
			while((handle != 0) && (data_size >= (sizeof(type) + sizeof(uuid))))
			{
				STREAM_TO_UINT16(type, p);
				STREAM_TO_UINT16(uuid, p);
				data_size -= (sizeof(type) + sizeof(uuid));

				if(type == BluetoothGattTypePrimaryService)
				{
					EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;

					if(data_size < (sizeof(end_handle) + sizeof(value_len)))
						break;

					attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO));
					if (!attr)
					{
						loge("AllocateZeroPool failure returns NULL");
						return FALSE;
					}
					SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypePrimaryService);
					attr->Header.AttributeHandle = handle;
					STREAM_TO_UINT16(end_handle, p);
					data_size -= sizeof(end_handle);
					attr->EndGroupHandle = end_handle;
					attr->ServiceUuid.Length = UUID_16BIT_TYPE_LEN;
					attr->ServiceUuid.Data.Uuid16 = uuid;
					index = dev->free_handle;
					dev->BtLeSbDev->AttrDatabase[index] = &attr->Header;
				}
				else if(type == BluetoothGattTypeCharacteristic)
				{
					EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;

					if(data_size < (sizeof(property) + sizeof(value_len)))
						break;

					attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
					ASSERT (attr != NULL);
					SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypeCharacteristic);
					attr->Header.AttributeHandle = handle - 1;
					STREAM_TO_UINT8(property, p);
					data_size -= sizeof(property);
					attr->CharacteristicProperties = property;
					attr->CharacteristicValueHandle = handle;
					attr->CharacteristicUuid.Length = UUID_16BIT_TYPE_LEN;
					attr->CharacteristicUuid.Data.Uuid16 = uuid;
					index = att_db_get_idx_from_hdl(conn_id, handle - 1);
					if (index < BT_LE_PER_DEV_ATTR)
						dev->BtLeSbDev->AttrDatabase[index] = &attr->Header;

					attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
					ASSERT (attr != NULL);
					SET_ATTRIBUTE_TYPE(attr, uuid);
					attr->Header.AttributeHandle = handle;
					attr->CharacteristicProperties = property;
					attr->CharacteristicValueHandle = handle;
					attr->CharacteristicUuid.Length = UUID_16BIT_TYPE_LEN;
					attr->CharacteristicUuid.Data.Uuid16 = uuid;
					index = att_db_get_idx_from_hdl(conn_id, handle);
					if (index < BT_LE_PER_DEV_ATTR)
						dev->BtLeSbDev->AttrDatabase[index] = &attr->Header;
				}
				else if(type == BluetoothGattTypeCharacteristicExtendedProperties)
				{
					EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *attr;

					attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO));
					ASSERT (attr != NULL);
					SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypeCharacteristicExtendedProperties);
					attr->Header.AttributeHandle = handle;
					attr->CharacteristicDescriptorUuid.Length = UUID_16BIT_TYPE_LEN;
					attr->CharacteristicDescriptorUuid.Data.Uuid16 = uuid;
					index = att_db_get_idx_from_hdl(conn_id, handle);
					if (index < BT_LE_PER_DEV_ATTR)
						dev->BtLeSbDev->AttrDatabase[index] = &attr->Header;
				}

				if(data_size >= sizeof(value_len))
				{
					STREAM_TO_UINT16(value_len, p);
					data_size -= sizeof(value_len);
				}

				if (data_size < value_len)
					break;

				/* Store Hid Info in local list */
				if (type == BluetoothGattTypePrimaryService)
					store_hid_info_to_list(conn_id, handle, type, uuid, end_handle, p, (UINTN)value_len);
				else
					store_hid_info_to_list(conn_id, handle, type, uuid, property, p, (UINTN)value_len);

				p += value_len;
				data_size -= value_len;

				/* Break the loop if full data has been read */
				if (data_size < sizeof(handle))
					break;

				/* Get Next Handle */
				STREAM_TO_UINT16(handle, p);
				data_size -= sizeof(handle);
			}
		}

		FreePool(data);
		return FALSE;
	}

	logd("Peer HID info not found in DB");

	return TRUE;
}

static void start_service_discovery(BLUETOOTH_LE_ADDRESS *BD_ADDR, UINT8 conn_id)
{
	BT_LE_DEV_INFO              *BtLeDevInfo;
	BT_LE_PAIRED_DEV_INFO       *BtLePairedDevInfo;

	BtLeDevInfo = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, BD_ADDR);
	if (!BtLeDevInfo)
	{
		BtLePairedDevInfo = BtFindLePairedDevByBDAddr(uefi_app_data.BtHcDev, BD_ADDR);
		if (BtLePairedDevInfo)
		{
			/* Add device to local list */
			if (!BtLeUpdateDevice(uefi_app_data.BtHcDev, &BtLePairedDevInfo->BDAddr, &BtLePairedDevInfo->IDAddr, NULL, 0, 0, 0, 0, NULL, NULL, 0, TRUE)) {
				loge("BtLeUpdateDevice Failed!");
				return;
			}
			BtLeDevInfo = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, BD_ADDR);
			if(!BtLeDevInfo)
			{
				loge("BtLeDevInfo is NULL");
				return;
			}
		}
		else
		{
			logd("Paired Device Info not found!");
			/* Disconnect from the remote device */
			uefi_app_disconnect(conn_id, 0x13);
			return;
		}
	}

	memcpy(uefi_app_data.remote_device_list[conn_id].idaddr, BtLeDevInfo->IDAddr.Address, BD_ADDR_LEN);
	uefi_app_data.remote_device_list[conn_id].bdaddr_type = BtLeDevInfo->IDAddr.Type;
	uefi_app_data.remote_device_list[conn_id].offset = 0;
	uefi_app_data.remote_device_list[conn_id].store_hid_info = TRUE;

	//Create BtLeSb
	uefi_app_data.remote_device_list[conn_id].BtLeSbDev = BtCreateLeSbDev(uefi_app_data.BtHcDev, BtLeDevInfo);
	InitializeListHead (&uefi_app_data.remote_device_list[conn_id].hid_info);
	uefi_app_data.remote_device_list[conn_id].BtLeSbDev->ConnectionId = conn_id;

	if (is_service_discovery_required(conn_id))
	{
#if (UEFI_HOGP_PTS == TRUE)
		/* If we do not wait before service discovery all the PTS test cases are failing,
		 * so delaying service discovery.
		 */
		gBS->Stall(1000);
#endif
		uefi_app_discover_prim_srv(conn_id);
	}
	else
	{
		uefi_app_data.remote_device_list[conn_id].store_hid_info = FALSE;
		uefi_app_data.remote_device_list[conn_id].is_discovery_completed = TRUE;
		discovery_completed(conn_id);
	}
}

void uefi_app_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, BOOLEAN from_remote, UINT8 *id_addr, UINT8 id_addr_type)
{
	BLUETOOTH_LE_ADDRESS        BD_ADDR;
	BT_LE_PAIRED_DEV_INFO       *BtLePairedDevInfo;
	trans_id_t new_trans_id = 0;

	logd(" ");
	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, remote_bd_addr, bdaddr_type);

	if (status == STATUS_SUCCESS)
	{
		memcpy(uefi_app_data.remote_device_list[conn_id].bdaddr, BD_ADDR.Address, BD_ADDR_LEN);
		uefi_app_data.remote_device_list[conn_id].bdaddr_type = BD_ADDR.Type;

		BtLePairedDevInfo = BtFindLePairedDevByBDAddr(uefi_app_data.BtHcDev, &BD_ADDR);

		if (BtLePairedDevInfo != NULL)
		{
			logd("Found device in paired device list");
			/* This is Auto Reconnect scenario */
			/* Create Bond */
			add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
			iLE_create_bond(new_trans_id, conn_id, uefi_app_data.authreq, uefi_app_data.enckeysize);
		}
		else
		{
			logd("Not found device in paired device list");
			/* User has triggered the connection */
			if (uefi_app_data.doing_bond)
			{
				/* Create Bond */
				add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
				iLE_create_bond(new_trans_id, conn_id, uefi_app_data.authreq, uefi_app_data.enckeysize);
			}
			else
			{
				start_service_discovery(&BD_ADDR, conn_id);
			}

		}

		if (from_remote)
		{
			logd("Connected as server!");
		}
		else
		{
			logd("Connected as client!");
		}
	}
	else
	{
		logd("Connection failed!");
		if (uefi_app_data.BtHcDev->LeConnCompCallBack)
			uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeDisconnected, &BD_ADDR, NULL, 0);

	}

	if (log_file)
		log_file->Flush(log_file);
}

void uefi_app_on_bonding_completed_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, UINT8 *id_addr, UINT8 id_addr_type)
{
	BLUETOOTH_LE_ADDRESS  BD_ADDR;
	BT_LE_DEV_INFO        *dev_info;
	BT_LE_PAIRED_DEV_INFO *paired_dev_info;

	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, bdaddr, bdaddr_type);
	logi("Status: %d", status);

	paired_dev_info = BtFindLePairedDevByBDAddr(uefi_app_data.BtHcDev, &BD_ADDR);

	if (status == STATUS_SUCCESS)
	{
		if (paired_dev_info == NULL)
		{
			uefi_app_data.doing_bond = FALSE;
			dev_info = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, &BD_ADDR);
			BtAddLePairedDev(uefi_app_data.BtHcDev, &dev_info->BDAddr, &dev_info->IDAddr, uefi_app_data.BtHcDev->BluetoothHc);
		}

		if (uefi_app_data.remote_device_list[conn_id].BtLeSbDev)
		{
			if (uefi_app_data.BtHcDev->LeConnCompCallBack)
				uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeEncrypted, &BD_ADDR, NULL, 0);
		}
		else
			start_service_discovery(&BD_ADDR, conn_id);
	}
	else
	{
		if ((is_valid_ble_address(&BD_ADDR)) && (uefi_app_data.BtHcDev->LeConnCompCallBack))
		{
			uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeDisconnected, &BD_ADDR, NULL, 0);
		}

		/* Disconnect from the remote device */
		uefi_app_disconnect(conn_id, 0x05);
	}
}

void uefi_app_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 status)
{
	BT_LE_SB_DEV *BtLeSbDev;
	BLUETOOTH_LE_ADDRESS BD_ADDR, ID_ADDR;
	UINTN idx;
	LIST_ENTRY *Link;
	uefi_app_hid_info_t *hid_info;

	BDADDR_ARR_TO_BDADDR_STRUCT(&BD_ADDR, uefi_app_data.remote_device_list[conn_id].bdaddr, uefi_app_data.remote_device_list[conn_id].bdaddr_type);
	BDADDR_ARR_TO_BDADDR_STRUCT(&ID_ADDR, uefi_app_data.remote_device_list[conn_id].idaddr, uefi_app_data.remote_device_list[conn_id].idaddr_type);
	logd("");

	//TODO: Take care of status

	//Delete BtLeSb
	BtLeSbDev = uefi_app_data.remote_device_list[conn_id].BtLeSbDev;
	if (BtLeSbDev)
	{
		for (idx = 0; idx < BT_LE_PER_DEV_ATTR; idx++)
			if (BtLeSbDev->AttrDatabase[idx])
				FreePool(BtLeSbDev->AttrDatabase[idx]);

		ZeroMem(BtLeSbDev->AttrDatabase, sizeof(BtLeSbDev->AttrDatabase));
		BtDelLeSb(uefi_app_data.BtHcDev, BtLeSbDev);

		Link = GetFirstNode(&uefi_app_data.remote_device_list[conn_id].hid_info);
		while (!IsNull(&uefi_app_data.remote_device_list[conn_id].hid_info, Link))
		{
			hid_info = UEFI_APP_HID_INFO_FROM_LINK(Link);
			if (hid_info->data != NULL)
			{
				FreePool(hid_info->data);
				hid_info->data = NULL;
			}
			Link = RemoveEntryList(&hid_info->Link);
			FreePool(hid_info);
		}
		ZeroMem(&uefi_app_data.remote_device_list[conn_id], sizeof(uefi_app_data.remote_device_list[conn_id]));

		if (uefi_app_data.BtHcDev->LeConnCompCallBack)
		{
			/* If disconnect is triggered by user */
			if ((is_valid_ble_address(&cur_req_addr)) &&
				((!memcmp(cur_req_addr.Address, ID_ADDR.Address, sizeof(cur_req_addr.Address))) ||
				(!memcmp(cur_req_addr.Address, BD_ADDR.Address, sizeof(cur_req_addr.Address)))))
			{
				uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeDisconnected, &cur_req_addr, NULL, 0);
				memset(&cur_req_addr, 0, sizeof(BLUETOOTH_LE_ADDRESS));
			}
			else
			{
				/* If disconnect is not triggered by the user then use Identity address if it available */
				if (is_valid_ble_address(&ID_ADDR))
					uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeDisconnected, &ID_ADDR, NULL, 0);
				else
					uefi_app_data.BtHcDev->LeConnCompCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeConnCompCallBackContext, EfiBluetoothConnCallbackTypeDisconnected, &BD_ADDR, NULL, 0);

			}

		}
	}

	if (log_file)
		log_file->Flush(log_file);
}

static void att_db_reserve_prim_srv_space(UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid)
{
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;

	UINT16 handle_index;

	handle_index = uefi_app_data.remote_device_list[conn_id].free_handle;

	attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO));
	if (!attr) return;

	SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypePrimaryService);
	attr->Header.AttributeHandle = start_handle;
	attr->EndGroupHandle = end_handle;
	ile_uuid_to_uefi_uuid(&attr->ServiceUuid, uuid);
	uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[handle_index] = &attr->Header;

	uefi_app_data.remote_device_list[conn_id].free_handle = handle_index + end_handle - start_handle + 1;
}

static UINT16 att_db_get_next_prim_srv_idx(UINT8 conn_id, UINT16 present_id)
{
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;

	attr = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[present_id];

	if (!attr) {
		return BT_LE_PER_DEV_ATTR;
	}

	present_id = present_id + attr->EndGroupHandle - attr->Header.AttributeHandle + 1;

	return present_id;
}

void uefi_app_on_primary_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	//logd("primary_service start_handle:%u end_handle:%u", start_handle, end_handle);
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *attr;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	if (is_finished == FALSE)
	{
		att_db_reserve_prim_srv_space(conn_id, start_handle, end_handle, uuid);
	}
	else
	{
		UINT16 att_id = 0;
		uefi_app_data.remote_device_list[conn_id].num_of_discover_req = 0;
		while(att_id < BT_LE_PER_DEV_ATTR)
		{
			attr = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[att_id];
			if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypePrimaryService))
			{
				uefi_app_data.remote_device_list[conn_id].num_of_discover_req ++;
				iLE_discover_included_service(new_trans_id, conn_id, attr->Header.AttributeHandle, attr->EndGroupHandle);
			}

			att_id = att_db_get_next_prim_srv_idx(conn_id, att_id);
		}
		if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
			check_hid_support(conn_id);
	}
}

void uefi_app_on_included_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 inc_handle, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	//logd("included_service start_handle:%u end_handle:%u", start_handle, end_handle);
	EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO *attr;
	EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *pattr;
	UINT16 index;

	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	if (is_finished == FALSE)
	{
		if (start_handle < BT_LE_PER_DEV_ATTR)
		{
			attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO));
			if (!attr) return;
			SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypeInclude);
			attr->Header.AttributeHandle = inc_handle;
			attr->StartGroupHandle = start_handle;
			attr->EndGroupHandle = end_handle;
			index = att_db_get_idx_from_hdl(conn_id, inc_handle);
			if (index >= BT_LE_PER_DEV_ATTR)
			{
				loge("Error\n");
				return;
			}
			uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index] = &attr->Header;
			if (uuid)
			{
				if (uuid->length == 0)
				{
					/* Read the UUID of the included service */
					gatt_attribute_read_param_t read_param;
					uefi_app_data.remote_device_list[conn_id].request_handle = inc_handle;
					read_param.att_opcode = ATT_OPCODE_READ_REQ;
					read_param.attr_read_param.read_attr.att_id = start_handle;
					iLE_read_attribute_value(new_trans_id, conn_id, &read_param);
				}
				else
				{
					ile_uuid_to_uefi_uuid(&attr->ServiceUuid, uuid);
				}
			}
		}
	}
	else
	{
		uefi_app_data.remote_device_list[conn_id].num_of_discover_req --;
		if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
		{
			//logd("Discover characteristic");
			UINT16 att_id = 0;
			while (att_id < BT_LE_PER_DEV_ATTR)
			{
				pattr = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[att_id];
				if (pattr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&pattr->Header, BluetoothGattTypePrimaryService))
				{
					uefi_app_data.remote_device_list[conn_id].num_of_discover_req ++;
					iLE_discover_characteristic(new_trans_id, conn_id, pattr->Header.AttributeHandle, pattr->EndGroupHandle, NULL);
				}

				att_id = att_db_get_next_prim_srv_idx(conn_id, att_id);
			}
		}
		if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
			check_hid_support(conn_id);
	}
}

void uefi_app_on_characteristic_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	//logd("\t characteristic handle:%u value_handle:%u", att_handle, value_handle);
	EFI_BLUETOOTH_ATTRIBUTE_HEADER *hdr;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;
	UINT16 index;
	UINT16 delta;

	trans_id_t new_trans_id = 0;
	delta = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	if (is_finished == FALSE)
	{
		if (att_handle < BT_LE_PER_DEV_ATTR || value_handle < BT_LE_PER_DEV_ATTR)
		{
			attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
			if (!attr) return;
			SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypeCharacteristic);
			attr->Header.AttributeHandle = att_handle;
			attr->CharacteristicProperties = property;
			attr->CharacteristicValueHandle = value_handle;
			ile_uuid_to_uefi_uuid(&attr->CharacteristicUuid, uuid);
			index = att_db_get_idx_from_hdl(conn_id, att_handle);
			if (index >= BT_LE_PER_DEV_ATTR)
			{
				loge("Error\n");
				return;
			}
			uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index] = &attr->Header;

			attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
			if (!attr) return;
			ile_uuid_to_uefi_uuid(&attr->Header.Type, uuid);
			attr->Header.AttributeHandle = value_handle;
			attr->CharacteristicProperties = property;
			attr->CharacteristicValueHandle = value_handle;
			ile_uuid_to_uefi_uuid(&attr->CharacteristicUuid, uuid);
			index = att_db_get_idx_from_hdl(conn_id, value_handle);
			if (index >= BT_LE_PER_DEV_ATTR)
			{
				loge("Error\n");
				return;
			}
			uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index] = &attr->Header;
		}
	}
	else if (uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
	{
		uefi_app_data.remote_device_list[conn_id].num_of_discover_req --;
		if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
		{
			UINT16 start_id, start_handle;
			for (start_id = 0; start_id < BT_LE_PER_DEV_ATTR; start_id ++)
			{
				hdr = uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[start_id];
				if (hdr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(hdr, BluetoothGattTypePrimaryService))
				{
					delta = hdr->AttributeHandle - start_id;
				}

				if (hdr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(hdr, BluetoothGattTypeCharacteristic))
				{
					start_id++;
					if (start_id < (BT_LE_PER_DEV_ATTR - 1) && !uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[start_id+1])
					{
						UINT16 end_handle = get_last_empty_attr_id(conn_id, start_id);
						if (end_handle == BT_LE_PER_DEV_ATTR)
						{
							EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *srv = get_owner_prim_srv(conn_id, start_id);
							if (srv)
							{
								end_handle = srv->EndGroupHandle;
							}
						}
						else
							end_handle += delta;
						start_handle = delta + start_id + 1;
						//logd("start_handle:%u end_handle:%u", start_handle, end_handle);
						if (end_handle >= start_handle)
						{
							//logd("iLE_discover_descriptor start:%u end:%u", start_handle, end_handle);
							uefi_app_data.remote_device_list[conn_id].num_of_discover_req ++;
							iLE_discover_descriptor(new_trans_id, conn_id, start_handle, end_handle);
						}
					}
				}
			}
			if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
				check_hid_support(conn_id);
		}
	}

}


void uefi_app_on_descriptor_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished)
{
	//logd("\t\t descriptor handle:%u", att_handle);
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *attr;
	UINT16 index;
	if (is_finished == FALSE)
	{
		if (att_handle < BT_LE_PER_DEV_ATTR)
		{
			attr = AllocateZeroPool(sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO));
			if (!attr) return;
			SET_ATTRIBUTE_TYPE(attr, BluetoothGattTypeCharacteristicExtendedProperties);
			attr->Header.AttributeHandle = att_handle;
			ile_uuid_to_uefi_uuid(&attr->CharacteristicDescriptorUuid, uuid);
			index = att_db_get_idx_from_hdl(conn_id, att_handle);
			if (index >= BT_LE_PER_DEV_ATTR)
			{
				loge("Error\n");
				return;
			}

			uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index] = &attr->Header;
		}
	}
	else
	{
		uefi_app_data.remote_device_list[conn_id].num_of_discover_req --;
		if (!uefi_app_data.remote_device_list[conn_id].num_of_discover_req)
		{
			//dump_att_db(conn_id);
			check_hid_support(conn_id);
		}
	}
}

void uefi_app_on_attribute_read_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t *buffer)
{
	EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO *attr;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];
	LIST_ENTRY *Link;
	BT_LE_DEV *BtLeDev;
	buffer_t *saved_rd_blob_value = dev->saved_rd_blob_value;
	UINT8 *data;
	UINT16 copy_len = 0;
	UINTN resp_len;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	logd("");

	if (status == ATT_SUCCESS)
	{
		if ((att_opcode != ATT_OPCODE_READ_MULTI_RESP) && ((buffer->length == (iLE_get_att_mtu(new_trans_id, conn_id)) - 1) || att_opcode == ATT_OPCODE_READ_BLOB_RESP))
		{
			if (!saved_rd_blob_value)
			{
				saved_rd_blob_value = (buffer_t*) app_alloc(sizeof(buffer_t) + ATT_MAX_VALUE_LEN);
#if (PARANOID_STACK == TRUE)
				if (!saved_rd_blob_value)
					return;
#endif

				saved_rd_blob_value->offset = 0;
				saved_rd_blob_value->length = 0;
				dev->saved_rd_blob_value = saved_rd_blob_value;
			}
			copy_len = MIN(buffer->length, ATT_MAX_VALUE_LEN - saved_rd_blob_value->length);
			memcpy(saved_rd_blob_value->data + saved_rd_blob_value->offset, buffer->data + buffer->offset, copy_len);
			saved_rd_blob_value->offset = saved_rd_blob_value->offset + copy_len;
			saved_rd_blob_value->length += copy_len;
			if (buffer->length == (iLE_get_att_mtu(new_trans_id, conn_id)) - 1)
			{
				gatt_attribute_read_param_t read_param;
				read_param.att_opcode = ATT_OPCODE_READ_BLOB_REQ;
				read_param.attr_read_param.read_attr.att_id = att_id;
				read_param.attr_read_param.read_attr.offset = saved_rd_blob_value->offset;
				iLE_read_attribute_value(new_trans_id, conn_id, &read_param);
			}
			else
			{
				if (saved_rd_blob_value) {
					hex_dump("BLOB buffer:", saved_rd_blob_value->data, saved_rd_blob_value->length);
					/* Call remote_device read_cb */
					resp_len = sizeof(UINT8) + saved_rd_blob_value->length;
					data = AllocateZeroPool(resp_len);
					if (!data) return;
					data[0] = ATT_OPCODE_READ_RESP;
					CopyMem(&data[1], saved_rd_blob_value->data, saved_rd_blob_value->length);
					if(uefi_app_data.remote_device_list[conn_id].is_discovery_completed)
					{
						/* Service Discovery is completed send the result to upper layer */
						Link = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
						BtLeDev = CR(Link, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);
						if (dev->read_cb)
						{
							dev->read_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->read_cb_context);
							dev->read_cb = NULL;
						}
					}
					else
					{
						/* Service Discovery is still going on, this is internal read */
						read_hid_report_data(conn_id, att_id, data, resp_len);
					}
					FreePool(data);
					dealloc(saved_rd_blob_value);
					dev->saved_rd_blob_value = NULL;
				}
			}
		}
		else if(dev->request_handle && att_opcode == ATT_OPCODE_READ_RESP && buffer->length == UUID_128BIT_TYPE_LEN)
		{
			UINT16 index;
			uuid_t uuid;
			index = att_db_get_idx_from_hdl(conn_id, dev->request_handle);
			if (index >= BT_LE_PER_DEV_ATTR)
			{
				loge("Error\n");
				return;
			}

			/* need to change as UUID is in little endian format */
			attr = (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO *) dev->BtLeSbDev->AttrDatabase[index];
			uuid.length = (UINT8)buffer->length;
			REVERSE_STREAM_TO_ARRAY(uuid.value.uuid128, buffer->data + (UINT8)buffer->offset, buffer->length);
			ile_uuid_to_uefi_uuid(&attr->ServiceUuid, &uuid);
			dev->request_handle = 0x0000;
		}
		else
		{
			if(buffer->length)
				hex_dump("value:", buffer->data + buffer->offset, buffer->length);
			/* Call remote_device read_cb */
			if (att_opcode == ATT_OPCODE_READ_BY_TYPE_RESP)
			{
				resp_len = 2 * sizeof(UINT8) + sizeof(UINT16) + buffer->length;
				data = AllocateZeroPool(resp_len);
				if (!data) return;
				data[0] = att_opcode;
				// FIXME: Currently we assume only one attribute is returned. Otherwise we need to pass the length field up the GATT layer.
				data[1] = (UINT8) (sizeof(UINT16) + buffer->length);
				*((UINT16*)(data + 2)) = att_id;
				CopyMem(&data[4], buffer->data + buffer->offset, buffer->length);
			}
			else
			{
				resp_len = sizeof(UINT8) + buffer->length;
				data = AllocateZeroPool(resp_len);
				if (!data) return;
				data[0] = att_opcode;
				CopyMem(&data[1], buffer->data + buffer->offset, buffer->length);
			}

			if(uefi_app_data.remote_device_list[conn_id].is_discovery_completed)
			{
				/* Service Discovery is completed send the result to upper layer */
				Link = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
				BtLeDev = CR(Link, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);
				if (dev->read_cb)
				{
					dev->read_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->read_cb_context);
					dev->read_cb = NULL;
				}
			}
			else
			{
				/* Service Discovery is still going on, this is internal read */
				read_hid_report_data(conn_id, att_id, data, resp_len);
			}
			FreePool(data);
		}
	}
	else
	{
		logd("ATT STATUS:%d (%s)", status, get_string_status(status));
		resp_len = 3 * sizeof(UINT8) + sizeof(UINT16);
		data = AllocateZeroPool(resp_len);
		if (!data) return;
		data[0] = ATT_OPCODE_ERROR_RESP;
		data[1] = att_opcode;
		*((UINT16*)(data + 2)) = att_id;
		data[4] = status;
		if(uefi_app_data.remote_device_list[conn_id].is_discovery_completed)
		{
			/* Service Discovery is completed send the result to upper layer */
			Link = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
			BtLeDev = CR(Link, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);
			if (dev->read_cb)
			{
				dev->read_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->read_cb_context);
				dev->read_cb = NULL;
			}
		}
		else
		{
			/* Service Discovery is still going on, this is internal read */
			read_hid_report_data(conn_id, att_id, data, resp_len);
		}
		FreePool(data);
	}
}


void uefi_app_on_attribute_write_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 opcode, UINT8 status, UINT16 att_id, UINT16 offset, buffer_t* buffer)
{
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];
	LIST_ENTRY *Link;
	BT_LE_DEV *BtLeDev = NULL;
	buffer_t *prep_wr_value = dev->prep_wr_value;
	UINT8 *data;
	UINTN resp_len;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	logd("ATT STATUS:%d (%s) opcode:%d", status, get_string_status(status), opcode);

	if (!IsListEmpty(&dev->BtLeSbDev->ChildrenList))
	{
		Link = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
		BtLeDev = CR(Link, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);
	}

	if (status != ATT_SUCCESS)
	{
		if (prep_wr_value)
		{
			dealloc(prep_wr_value);
			dev->prep_wr_value = NULL;
		}
		if (BtLeDev && dev->write_cb)
		{
			resp_len = 3 * sizeof(UINT8) + sizeof(UINT16);
			data = AllocateZeroPool(resp_len);
			if (!data) return;
			data[0] = ATT_OPCODE_ERROR_RESP;
			data[1] = opcode;
			*((UINT16*)(data + 2)) = att_id;
			data[4] = status;
			dev->write_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->write_cb_context);
			dev->write_cb = NULL;
			FreePool(data);
		}
		return;
	}
	if (opcode == ATT_OPCODE_PREP_WRITE_RESP && prep_wr_value)
	{
		UINT16 mtu = 0;
		buffer_t *out_buffer;
		if ((memcmp(buffer->data + buffer->offset, prep_wr_value->data + prep_wr_value->offset - buffer->length, buffer->length) != 0) || (prep_wr_value->length == 0))
		{
			UINT8 *p;
			out_buffer = (buffer_t*) app_alloc(sizeof (buffer_t) + 1);
			logd("send execute write req");
#if (PARANOID_STACK == TRUE)
			if (!out_buffer)
				return;
#endif
			p = out_buffer->data;
			if (memcmp(buffer->data + buffer->offset, prep_wr_value->data + prep_wr_value->offset - buffer->length, buffer->length) != 0)
			{
				/* send out execute write with cancel */
				UINT8_TO_STREAM(p, 0x00);
			}
			else if(prep_wr_value->length == 0)
			{
				/* send out execute write with success */
				UINT8_TO_STREAM(p, 0x01);
			}
			out_buffer->length = 1;
			out_buffer->offset = 0;
			iLE_write_attribute_value(new_trans_id, conn_id, ATT_OPCODE_EXEC_WRITE_REQ, att_id, 0, out_buffer);
			dealloc(out_buffer);
			if (prep_wr_value)
			{
				dealloc(prep_wr_value);
				dev->prep_wr_value = NULL;
			}
			return;
		}

		out_buffer = (buffer_t*) app_alloc(sizeof (buffer_t) + (mtu = iLE_get_att_mtu(new_trans_id, conn_id)) - 5);
#if (PARANOID_STACK == TRUE)
		if (!out_buffer)
		{
			if (prep_wr_value)
			{
				dealloc(prep_wr_value);
				dev->prep_wr_value = NULL;
			}
			return;
		}
#endif
		out_buffer->length = MIN ((mtu - 5), prep_wr_value->length);
		out_buffer->offset = 0;
		hex_dump("WRITE_FRM_TEST", prep_wr_value->data + prep_wr_value->offset, out_buffer->length);
		memcpy(out_buffer->data, prep_wr_value->data + prep_wr_value->offset, out_buffer->length);
		if (iLE_write_attribute_value(new_trans_id, conn_id, ATT_OPCODE_PREP_WRITE_REQ,
				att_id, prep_wr_value->offset, out_buffer) == STATUS_SUCCESS)
		{
			prep_wr_value->offset += out_buffer->length;
			prep_wr_value->length -= out_buffer->length;
		}
		dealloc(out_buffer);
		return;
	}
	if (BtLeDev && dev->write_cb)
	{
		resp_len = sizeof(UINT8) + sizeof(UINT16);
		data = AllocateZeroPool(resp_len);
		if (!data) return;
		data[0] = ATT_OPCODE_WRITE_RESP;
		*((UINT16*)(data + 1)) = att_id;
		dev->write_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->write_cb_context);
		dev->write_cb = NULL;
		FreePool(data);
	}
}

void uefi_on_notification_cb (trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN is_indication)
{
	//logd("");

	UINT8 *data;
	UINTN resp_len;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];
	LIST_ENTRY *Link = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
	BT_LE_DEV *BtLeDev = CR(Link, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);

	if (buffer)
	{
		//hex_dump("uefi_on_notification_cb:", buffer->data + buffer->offset, buffer->length);
		if (dev->notify_cb)
		{
			resp_len = sizeof(UINT8) + sizeof(UINT16) + buffer->length;
			data = AllocateZeroPool(resp_len);
			if (!data) return;
			data[0] = is_indication? BluetoothAttOpHandleValueIndication : BluetoothAttOpHandleValueNotification;
			*((UINT16*)(data + 1)) = att_id;
			CopyMem(&data[3], buffer->data + buffer->offset, buffer->length);
			dev->notify_cb(&BtLeDev->BluetoothAtt, data, resp_len, dev->notify_cb_context);
			FreePool(data);
		}
	}
}

void uefi_on_notification_registered_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, UINT8 status)
{
	logd("ATT STATUS:%d (%s)", status, get_string_status(status));
}

EFI_STATUS enable_notification_indication(UINT8 conn_id, UINT16 att_id, BOOLEAN is_indication, BOOLEAN is_register)
{
	UINT16 id;
	uuid_t ccd, uuid;
	UINT16 value;
	UINT16 index;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *attr;
	buffer_t *buffer;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	attr = NULL;

	index = att_db_get_idx_from_hdl(conn_id, att_id);
	if (index >= BT_LE_PER_DEV_ATTR)
	{
		loge("Error\n");
		return EFI_INVALID_PARAMETER;
	}

	UINT16_TO_UUID(ATTR_TYPE_CLIENT_CHARACTERISTIC_CONFIG_DESCRIPTOR_UUID, ccd);
	for (id = index; id < BT_LE_PER_DEV_ATTR; id ++)
	{
		attr = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[id];
		if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristicExtendedProperties))
		{
			uefi_uuid_to_ile_uuid(&uuid, &attr->CharacteristicDescriptorUuid);
			if (uuidcmp(&ccd, &uuid))
			{
				logd("Found at att_handle %u, 0x%04x 0x%04x", id, ccd.value.uuid16, uuid.value.uuid16);
				break;
			}
		}
	}
	if (id == BT_LE_PER_DEV_ATTR)
	{
		logw("Characteristic doesn't have Client Configuration descriptor");
		return EFI_NOT_FOUND;
	}
	iLE_register_notification(new_trans_id, conn_id, att_id + 1, is_register);
	if(is_register == FALSE)
		value = 0;
	else
	{
		if (is_indication == TRUE)
			value = 0x0002;
		else
			value = 0x0001;
	}
	buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + 2);
	if (!buffer) return EFI_OUT_OF_RESOURCES;
	buffer->offset = 0;
	buffer->length = 2;
	CopyMem(buffer->data, (UINT8*)&value, 2);
	iLE_write_attribute_value(new_trans_id, conn_id, ATT_OPCODE_WRITE_REQ, attr->Header.AttributeHandle, 0, buffer);
	app_dealloc(buffer);
	return EFI_SUCCESS;
}

void uefi_app_key_request_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type)
{
	EFI_BLUETOOTH_LE_SMP_DATA_TYPE data_type;
	BLUETOOTH_LE_ADDRESS remote_bd_addr;
	trans_id_t new_trans_id = 0;
	UINTN data_size;

	logd("");
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	memset(&remote_bd_addr, 0, sizeof(remote_bd_addr));
	if (bdaddr) {
		memcpy(remote_bd_addr.Address, bdaddr, BD_ADDR_LEN);
		remote_bd_addr.Type = bdaddr_type;
	}

	switch(key_type)
	{
#if (PRIVACY_FEATURE == TRUE)
		case LOCAL_IRK:
		{
			identity_info_t local_irk;
			UINT8 dummy_key[16];

			logd("Local IRK requested by stack");
			memset(&local_irk, 0, sizeof(identity_info_t));
			memset(dummy_key, 0, sizeof(dummy_key));
			data_size = sizeof(local_irk.irk);
			data_type = EfiBluetoothSmpLocalIRK;

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack)
			{
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, NULL, data_type, &data_size, local_irk.irk);
			}
			else
				data_size = 0;

			if(data_size && (memcmp(local_irk.irk, dummy_key, sizeof(dummy_key))))
			{
				logd("Local IRK found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &local_irk);
			}
			else
			{
				logd("Local IRK not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
				break;
			}
		}
			break;
		case PEER_IRK:
		{
			resolving_list_entry_t peer_irk;
			UINT8 dummy_bdaddr[BD_ADDR_LEN];
			UINTN count;
			UINTN no_of_peer_entries;
			UINT8 *peer_addresses;
			UINT8 *p;

			logd("List of peer IRK requested by stack");
			memset(&peer_irk, 0, sizeof(resolving_list_entry_t));
			peer_addresses = NULL;

			/* First check for Local IRK */
			data_size = sizeof(peer_irk.local_irk);
			data_type = EfiBluetoothSmpLocalIRK;

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack)
			{
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, NULL, data_type, &data_size, peer_irk.local_irk);
			}
			else
				data_size = 0;

			/* Check for Bonded Peer Address first */
			data_size = 0;
			data_type = EfiBluetoothSmpPeerAddress;

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack)
			{
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, NULL, data_type, &data_size, NULL);
				peer_addresses = AllocateZeroPool(data_size);
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, NULL, data_type, &data_size, peer_addresses);
			}
			else
				data_size = 0;

			if (data_size)
			{
				p = peer_addresses;
				no_of_peer_entries = data_size/sizeof(BLUETOOTH_LE_ADDRESS);
				logd("No of Peer entries = %d", no_of_peer_entries);
				for (count = 0; count < no_of_peer_entries; count++)
				{
					memcpy(&remote_bd_addr, p, sizeof(BLUETOOTH_LE_ADDRESS));
					p += sizeof(BLUETOOTH_LE_ADDRESS);

					/* Check for PEER IRK */
					if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack)
					{
						UINTN size;

						size = sizeof(peer_irk.peer_id_info.irk);
						data_type = EfiBluetoothSmpPeerIRK;
						uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &size, peer_irk.peer_id_info.irk);
						memcpy(peer_irk.peer_id_info.id_addr, remote_bd_addr.Address, sizeof(peer_irk.peer_id_info.id_addr));
						peer_irk.peer_id_info.id_addr_type = remote_bd_addr.Type;

						iLE_key_response(new_trans_id, peer_irk.peer_id_info.id_addr, peer_irk.peer_id_info.id_addr_type, key_type, &peer_irk);

						/* Add device to local list */
						BtLeUpdateDevice(uefi_app_data.BtHcDev, &remote_bd_addr, &remote_bd_addr, NULL, 0, 0, 0, 0, NULL, NULL, 0, TRUE);

						/* Add device to paired device list */
						BtAddLePairedDev(uefi_app_data.BtHcDev, &remote_bd_addr, &remote_bd_addr, uefi_app_data.BtHcDev->BluetoothHc);

					}
				}
			}
			if (peer_addresses != NULL) {
				FreePool(peer_addresses);
			}
			memset(dummy_bdaddr, 0, BD_ADDR_LEN);
			iLE_key_response(new_trans_id, dummy_bdaddr, 0, key_type, NULL);
		}
			break;
#endif
		case SEC_INFO:
		{
			sec_info_t security_info;

			logd("security info requested by stack");
			hex_dump("BDADDR", bdaddr, BD_ADDR_LEN);
			memset(&security_info, 0, sizeof(sec_info_t));

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack) {
				data_size = sizeof(security_info.keys_distributed);
				data_type = EfiBluetoothSmpKeysDistributed;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &security_info.keys_distributed);

				data_size = sizeof(security_info.key_size);
				data_type = EfiBluetoothSmpKeySize;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &security_info.key_size);

				data_size = sizeof(security_info.key_type);
				data_type = EfiBluetoothSmpKeyType;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &security_info.key_type);

				/* Update Security Level */
				if (security_info.key_type & 0x01)
				{
					if (security_info.key_type & 0x02)
						security_info.security_level = 3;
					else
						security_info.security_level = 2;
				}
				else
					security_info.security_level = 1;
			}
			else
				data_size = 0;

			if(data_size)
			{
				logd("Security info found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &security_info);
			}
			else
			{
				logd("Security info not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
			}
		}
			break;
		case PEER_LTK:
		{
			enc_info_t peer_ltk;

			logd("Peer LTK requested by stack");
			hex_dump("BDADDR", bdaddr, BD_ADDR_LEN);
			memset(&peer_ltk, 0, sizeof(enc_info_t));

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack) {
				data_size = sizeof(peer_ltk.ltk);
				data_type = EfiBluetoothSmpPeerLTK;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, peer_ltk.ltk);

				data_size = sizeof(peer_ltk.rand);
				data_type = EfiBluetoothSmpPeerRand;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, peer_ltk.rand);

				data_size = sizeof(peer_ltk.ediv);
				data_type = EfiBluetoothSmpPeerEDIV;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &peer_ltk.ediv);
			}
			else
				data_size = 0;

			if(data_size)
			{
				logd("Peer LTK found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &peer_ltk);
			}
			else
			{
				logd("Peer LTK not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
			}
		}
			break;
		case LOCAL_LTK:
		{
			enc_info_t local_ltk;

			logd("Local LTK Requested by the stack");
			hex_dump("BDADDR", bdaddr, BD_ADDR_LEN);
			memset(&local_ltk, 0, sizeof(enc_info_t));

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack) {
				data_size = sizeof(local_ltk.ltk);
				data_type = EfiBluetoothSmpLocalLTK;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, local_ltk.ltk);

				/* TODO: Not storing rand and ediv for local device, check if it is required */
			}
			else
				data_size = 0;

			if(data_size)
			{
				logd("Local LTK found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &local_ltk);
			}
			else
			{
				logd("Local LTK not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
				break;
			}
			break;
		}
#if (SIGNED_WRITE)
		case PEER_CSRK:
		{
			signing_info_t peer_csrk;

			logd("Peer CSRK requested by stack");
			hex_dump("BDADDR", bdaddr, BD_ADDR_LEN);
			memset(&peer_csrk, 0, sizeof(signing_info_t));

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack) {
				data_size = sizeof(peer_csrk.csrk);
				data_type = EfiBluetoothSmpPeerCSRK;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, peer_csrk.csrk);

				data_size = sizeof(peer_csrk.counter);
				data_type = EfiBluetoothSmpPeerSignCounter;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &peer_csrk.counter);
			}
			else
				data_size = 0;

			if(data_size)
			{
				logd("Peer CSRK found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &peer_csrk);
			}
			else
			{
				logd("Peer CSRK not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
			}
		}
			break;
		case LOCAL_CSRK:
		{
			signing_info_t local_csrk;

			logd("Local CSRK Requested by the stack");
			hex_dump("BDADDR", bdaddr, BD_ADDR_LEN);
			memset(&local_csrk, 0, sizeof(signing_info_t));
			data_size = sizeof(signing_info_t);

			if (uefi_app_data.BtHcDev->LeSmpGetDataCallBack) {
				data_size = sizeof(local_csrk.csrk);
				data_type = EfiBluetoothSmpLocalCSRK;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, local_csrk.csrk);

				data_size = sizeof(local_csrk.counter);
				data_type = EfiBluetoothSmpLocalSignCounter;
				uefi_app_data.BtHcDev->LeSmpGetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpGetDataCallBackContext, &remote_bd_addr, data_type, &data_size, &local_csrk.counter);
			}
			else
				data_size = 0;

			if(data_size)
			{
				logd("Local CSRK found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, &local_csrk);
			}
			else
			{
				logd("Local CSRK not found in DB");
				iLE_key_response(new_trans_id, bdaddr, bdaddr_type, key_type, NULL);
				break;
			}
		}
			break;
#endif /* SIGNED_WRITE */
		default:
			logd("Unknown key_type %d", key_type);
			break;
	}
}

void uefi_app_key_update_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type,  UINT8 length, UINT8* key_value)
{
	BLUETOOTH_LE_ADDRESS remote_bd_addr;

	logd("");
	memset(&remote_bd_addr, 0, sizeof(remote_bd_addr));
	if (bdaddr) {
		memcpy(remote_bd_addr.Address, bdaddr, BD_ADDR_LEN);
		remote_bd_addr.Type = bdaddr_type;
	}

	switch(key_type)
	{
	case LOCAL_IRK:
		if(uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
			uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, NULL, EfiBluetoothSmpLocalIRK, length, key_value);
		break;
#if (SIGNED_WRITE)
	case LOCAL_COUNTER:
		/* TODO: Handle the scenario where bonding information is deleted by application */
		if(uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
			uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &remote_bd_addr, EfiBluetoothSmpLocalSignCounter, length, key_value);
		break;
	case PEER_COUNTER:
		/* TODO: Handle the scenario where bonding information is deleted by application */
		if(uefi_app_data.BtHcDev->LeSmpSetDataCallBack)
			uefi_app_data.BtHcDev->LeSmpSetDataCallBack(&uefi_app_data.BtHcDev->BluetoothLeConfig, uefi_app_data.BtHcDev->LeSmpSetDataCallBackContext, &remote_bd_addr, EfiBluetoothSmpPeerSignCounter, length, key_value);
		break;
#endif /* SIGNED_WRITE */
	}
}

void uefi_app_bonding_info_cb(trans_id_t trans_id, UINT8 *bdaddr, UINT8 bdaddr_type, UINT8* id_bdaddr, UINT8 id_bdaddr_type, smp_bonding_key_t *keys)
{
	BT_LE_DEV_INFO *dev_info;
	BLUETOOTH_LE_ADDRESS remote_addr;

	logd("");
	if((bdaddr == NULL) || (id_bdaddr == NULL) || (keys == NULL))
		return;

	BDADDR_ARR_TO_BDADDR_STRUCT(&remote_addr, bdaddr, bdaddr_type);

	memset(&cur_bonding_info, 0, sizeof(uefi_app_cur_bonding_info_t));
	memcpy(&cur_bonding_info.remote_addr, &remote_addr, sizeof(BLUETOOTH_LE_ADDRESS));
	memcpy(&cur_bonding_info.keys, keys, sizeof(smp_bonding_key_t));

	/* Update Remote Identity Address */
	dev_info = BtLeFindDeviceInfo(uefi_app_data.BtHcDev, &remote_addr);
	if (dev_info == NULL)
		return;
	memcpy(dev_info->IDAddr.Address, id_bdaddr, sizeof(dev_info->IDAddr.Address));
	dev_info->IDAddr.Type = id_bdaddr_type;
}

gatt_callbacks_t gatt_cb =
{
  NULL,
  uefi_app_on_primary_service_discovered_cb,
  uefi_app_on_included_service_discovered_cb,
  uefi_app_on_characteristic_discovered_cb,
  uefi_app_on_descriptor_discovered_cb,
  uefi_app_on_attribute_read_cb,
  uefi_app_on_attribute_write_cb,
  uefi_on_notification_cb,
  uefi_on_notification_registered_cb,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

static device_control_callbacks_t dev_cb =
{
  uefi_stack_initialized_cb,
  uefi_app_scan_result_cb,
  uefi_app_scan_completed_cb,
  uefi_app_on_connected_cb,
  NULL,
  uefi_app_on_bonding_completed_cb,
  uefi_app_on_disconnected_cb,
  #if (TEST_CODE==TRUE)
    #if (LE_PING_ENABLE==TRUE)
      test_app_read_authpayload_timeout_cb,
    #endif //LE_PING_ENABLE
  #endif //TEST_CODE
  NULL
};

static storage_callbacks_t storage_cb =
{
		uefi_app_key_request_cb,
		uefi_app_key_update_cb,
		uefi_app_bonding_info_cb,
		NULL
};

void uefi_app_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
	trans_id_t new_trans_id = 0;
	logi("uefi_app_register_application_cb");

	uefi_app_handle = app_handle;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	iLE_storage_register(new_trans_id, &storage_cb);

}
void uefi_app_init()
{
	uefi_app_data.authreq = 0x00;
	uefi_app_data.enckeysize = 0x07;
	iLE_register_application(&dev_cb, &gatt_cb, "test", NULL, uefi_app_register_application_cb);
}

void stack_cleanup()
{
	trans_id_t new_trans_id = 0;
	UINT8 idx;

	if (!init_complete)
		return;

	logd("Clean_up");

	for(idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
		if (uefi_app_data.remote_device_list[idx].BtLeSbDev)
			uefi_app_disconnect(idx, 0x15);

	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	iLE_storage_register(new_trans_id, NULL);

	iLE_deregister_application(uefi_app_handle);
	do {} while (init_complete == TRUE);
	logd("Cleanup Done");
}

void stack_switch_to_sync_event()
{
	if (!init_complete)
		return;

	logd("");
	// Unregister for async event during shut down
	tl_remove_async_event();
	g_local_adapter.is_sync_event = TRUE;
}

EFI_STATUS stack_init(BTHC_DEV *BtHcDev)
{
	if (init_complete)
		return EFI_SUCCESS;

	record_start_time();
    logd("Initializing BLE stack");
    uefi_app_data.BtHcDev = BtHcDev;
    ZeroMem(&cur_req_addr, sizeof(BLUETOOTH_LE_ADDRESS));
    iLE_stack_init();
    while (init_complete == FALSE) {}
    logd("Init completed");
    if (log_file)
    	log_file->Flush(log_file);
    return EFI_SUCCESS;
}

EFI_STATUS stack_scan(UINT32 Timeout, EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER *ScanParameter)
{
  BOOLEAN active = TRUE;
	BOOLEAN limited = FALSE;
	BOOLEAN use_whitelist = FALSE;
	BOOLEAN background = FALSE;
	UINT8 lidx = 0;
	UINT16 scan_interval = 0, scan_window = 0;
	UINT16 filter_uuids[MAX_NUM_SCAN_FILTER_UUIDS];
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	logd("Starting a scan");

	if (ScanParameter)
	{
		/*UINT8 num_filter_uuids = 0, idx;
		num_filter_uuids = ScanParameter->NumFilterServiceUuids;

		//Accept only 16bit UUIDs for now
		for (idx = 0; idx < num_filter_uuids; idx++)
			if (ScanParameter->FilterServiceUuids[idx].Length == UUID_16BIT_TYPE_LEN)
				filter_uuids[lidx++] = ScanParameter->FilterServiceUuids[idx].Data.Uuid16;*/

		active = ScanParameter->ScanType ? FALSE : TRUE;
		limited = ScanParameter->AdvertisementFlagFilter & 1? TRUE : FALSE;
		use_whitelist = ScanParameter->ScanningFilterPolicy & 1? TRUE : FALSE;
		scan_interval = ScanParameter->ScanInterval;
		scan_window = ScanParameter->ScanWindow;
	}

	iLE_start_scan_ex(new_trans_id, Timeout * 1000, active, limited, use_whitelist, background, scan_interval, scan_window, lidx, filter_uuids);
	return EFI_SUCCESS;
}

EFI_STATUS stack_connect(BLUETOOTH_LE_ADDRESS *bd_addr, EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER *conn_params, BOOLEAN auto_reconnect, BOOLEAN do_bonding)
{
	trans_id_t new_trans_id = 0;
	logd("Trying to connect to %02x:%02x:%02x:%02x:%02x:%02x", bd_addr->Address[0], bd_addr->Address[1], bd_addr->Address[2], bd_addr->Address[3], bd_addr->Address[4], bd_addr->Address[5]);
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	uefi_app_data.doing_bond = do_bonding;
	memcpy(&cur_req_addr, bd_addr, sizeof(BLUETOOTH_LE_ADDRESS));
	if(STATUS_SUCCESS == iLE_connect(new_trans_id, bd_addr->Address, bd_addr->Type))
		return EFI_SUCCESS;
	else
		return EFI_PROTOCOL_ERROR;
}

EFI_STATUS stack_disconnect(BLUETOOTH_LE_ADDRESS *bd_addr, UINT8 conn_id, UINT8 reason)
{
	logd("");
	memcpy(&cur_req_addr, bd_addr, sizeof(BLUETOOTH_LE_ADDRESS));
	uefi_app_disconnect(conn_id, reason);
	return EFI_SUCCESS;
}

static EFI_STATUS read_attr(UINT8 conn_id, UINT16 handle, UINT16 end_handle, uuid_t *uuid, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION callback, VOID *context)
{
	gatt_attribute_read_param_t read_param;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;
	trans_id_t new_trans_id = 0;
	uefi_app_hid_info_t *hid_info;
	LIST_ENTRY *Link;
	LIST_ENTRY *CLink;
	BT_LE_DEV *BtLeDev;
	remote_device_t *dev = &uefi_app_data.remote_device_list[conn_id];

	/* Check if we have already read that attribute */
	Link = GetFirstNode(&dev->hid_info);
	while (!IsNull(&dev->hid_info, Link))
	{
		hid_info = UEFI_APP_HID_INFO_FROM_LINK(Link);
		if (hid_info->handle == handle)
		{
			logd("Found handle(0x%04x) in local databse", handle);
			/* Found the value in local database */
			if (callback)
			{
				CLink = GetFirstNode(&dev->BtLeSbDev->ChildrenList);
				BtLeDev = CR(CLink, BT_LE_DEV, Link, BT_LE_DEV_SIGNATURE);
				callback(&BtLeDev->BluetoothAtt, hid_info->data, hid_info->data_len, context);
				return EFI_SUCCESS;
			}
		}
		Link = GetNextNode(&dev->hid_info, Link);
	}

	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);
	if (uuid)
	{
		read_param.att_opcode = ATT_OPCODE_READ_BY_TYPE_REQ;
		CopyMem(&read_param.attr_read_param.read_using_uuid_param.uuid, uuid, sizeof(uuid_t));
		read_param.attr_read_param.read_using_uuid_param.start_handle = handle;
		read_param.attr_read_param.read_using_uuid_param.end_handle = end_handle;
	}
	else
	{
		UINT16 index;
		index = att_db_get_idx_from_hdl(conn_id, handle);
		if (index == 0 || index >= BT_LE_PER_DEV_ATTR)
		{
			loge("Error\n");
			return EFI_INVALID_PARAMETER;
		}

		attr = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index-1];
		if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic))
		{
			if (IS_ATTRIBUTE_PROPERTY_READ(attr->CharacteristicProperties) == FALSE)
			{
				loge("Attribute not readable");
				return EFI_ACCESS_DENIED;
			}
		}

		read_param.att_opcode = ATT_OPCODE_READ_REQ;
		read_param.attr_read_param.read_attr.att_id = handle;
	}

	dev->read_cb = callback;
	dev->read_cb_context = context;

	iLE_read_attribute_value(new_trans_id, conn_id, &read_param);

	return EFI_SUCCESS;
}

static EFI_STATUS multi_read_attr(UINT8 conn_id, UINT16 *handles, UINT8 num_handles, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION callback, VOID *context)
{
	gatt_attribute_read_param_t read_param;
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;
	UINT8 it;
	UINT16 index;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	if (num_handles > 10)
		num_handles = 10;

	for (it = 0; it < num_handles; it++)
	{
		index = att_db_get_idx_from_hdl(conn_id, handles[it]);
		if (index == 0 || index >= BT_LE_PER_DEV_ATTR)
		{
			loge("Error\n");
			return EFI_INVALID_PARAMETER;
		}
		attr = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index-1];
		if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic))
		{
			if (IS_ATTRIBUTE_PROPERTY_READ(attr->CharacteristicProperties) == FALSE)
			{
				loge("Attribute not readable");
				return EFI_ACCESS_DENIED;
			}
		}
	}

	read_param.att_opcode = ATT_OPCODE_READ_MULTI_REQ;
	ZeroMem(&read_param.attr_read_param.multi_att_id_list, sizeof (read_param.attr_read_param.multi_att_id_list));
	CopyMem(&read_param.attr_read_param.multi_att_id_list, handles, num_handles * sizeof(UINT16));

	uefi_app_data.remote_device_list[conn_id].read_cb = callback;
	uefi_app_data.remote_device_list[conn_id].read_cb_context = context;

	iLE_read_attribute_value(new_trans_id, conn_id, &read_param);

	return EFI_SUCCESS;
}

static EFI_STATUS write_attr(UINT8 conn_id, UINT16 handle, write_type_t write_type, UINT16 data_size, VOID *data, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION callback, void *context)
{
	UINT8 opcode;
	UINT16 mtu = 0;
	trans_id_t new_trans_id = 0;
	buffer_t *buffer;
	UINT16 index = att_db_get_idx_from_hdl(conn_id, handle);
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;

	if (index == 0 || index >= BT_LE_PER_DEV_ATTR)
	{
		loge("Error\n");
		return EFI_INVALID_PARAMETER;
	}
	attr = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index-1];

	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	switch (write_type)
	{
	case write_request:
	case reliable_write:
		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic) && (IS_ATTRIBUTE_PROPERTY_WRITE(attr->CharacteristicProperties) == FALSE))
		{
			loge("Attribute not writable");
			return EFI_ACCESS_DENIED;
		}
		if ((data_size > (mtu = iLE_get_att_mtu(new_trans_id, conn_id)) - 3) || (write_type == reliable_write))
		{
			opcode = ATT_OPCODE_PREP_WRITE_REQ;
			uefi_app_data.remote_device_list[conn_id].prep_wr_value = (buffer_t*) app_alloc(sizeof(buffer_t) + data_size);
			uefi_app_data.remote_device_list[conn_id].prep_wr_value->length = (data_size > mtu - 5) ? (data_size - (mtu - 5)) : 0;
			memcpy(uefi_app_data.remote_device_list[conn_id].prep_wr_value->data, data, data_size);
			data_size = MIN((mtu - 5), data_size);
			uefi_app_data.remote_device_list[conn_id].prep_wr_value->offset = data_size;
		}
		else
			opcode = ATT_OPCODE_WRITE_REQ;
		break;
	case write_command:
		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic) && (IS_ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE(attr->CharacteristicProperties) == FALSE))
		{
			loge("Attribute not writable");
			return EFI_ACCESS_DENIED;
		}
		opcode = ATT_OPCODE_WRITE_CMD;
		break;
	case signed_write:
		if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic) && (IS_ATTRIBUTE_PROPERTY_AUTH_SIGNED_WRITE(attr->CharacteristicProperties) == FALSE))
		{
			loge("Attribute not writable");
			return EFI_ACCESS_DENIED;
		}
		opcode = ATT_OPCODE_SIGN_WRITE_CMD;
		break;
	default:
		return EFI_INVALID_PARAMETER;
	}

	uefi_app_data.remote_device_list[conn_id].write_cb = callback;
	uefi_app_data.remote_device_list[conn_id].write_cb_context = context;

	buffer = (buffer_t*) app_alloc (data_size + sizeof (buffer_t));
	if (!buffer) return EFI_OUT_OF_RESOURCES;
	buffer->offset = 0;
	buffer->length = data_size;
	memcpy(buffer->data + buffer->offset, data, data_size);
	iLE_write_attribute_value(new_trans_id, conn_id, opcode, handle, 0, buffer);
	app_dealloc(buffer);

	return EFI_SUCCESS;
}

EFI_STATUS stack_send_att_req(UINT8 conn_id, UINT16 DataSize, VOID *Data, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback, VOID *Context)
{
	uuid_t uuid;
	UINT16 handle, end_handle;
	UINT8 *buffer = Data;
	UINT8 opcode = *buffer;

	buffer++;
	DataSize--;

	switch (opcode)
	{
		case ATT_OPCODE_READ_BY_TYPE_REQ:
			handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			end_handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			uuid.length = (UINT8) DataSize;
			if (uuid.length == UUID_16BIT_TYPE_LEN)
				uuid.value.uuid16 = *((UINT16*)buffer);
			if (uuid.length == UUID_32BIT_TYPE_LEN)
				uuid.value.uuid32 = *((UINT32*)buffer);
			if (uuid.length == UUID_128BIT_TYPE_LEN)
				CopyMem(uuid.value.uuid128, buffer, UUID_128BIT_TYPE_LEN);
			return read_attr(conn_id, handle, end_handle, &uuid, Callback, Context);
		case ATT_OPCODE_READ_REQ:
			handle = *((UINT16*)buffer);
			return read_attr(conn_id, handle, handle, 0, Callback, Context);
		case ATT_OPCODE_READ_MULTI_REQ:
			return multi_read_attr(conn_id, (UINT16*)buffer, (UINT8)(DataSize/sizeof(UINT16)), Callback, Context);
		case ATT_OPCODE_WRITE_REQ:
			handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			return write_attr(conn_id, handle, write_request, DataSize, buffer, Callback, Context);
		case ATT_OPCODE_PREP_WRITE_REQ:
			handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			return write_attr(conn_id, handle, reliable_write, DataSize, buffer, Callback, Context);
		case ATT_OPCODE_WRITE_CMD:
			handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			return write_attr(conn_id, handle, write_command, DataSize, buffer, Callback, Context);
		case ATT_OPCODE_SIGN_WRITE_CMD:
			handle = *((UINT16*)buffer);
			buffer += 2;
			DataSize -= 2;
			return write_attr(conn_id, handle, signed_write, DataSize, buffer, Callback, Context);
	}

	loge("Invalid ATT opcode %x", opcode);
	return EFI_INVALID_PARAMETER;
}

EFI_STATUS stack_register_notification_indication(UINT8 conn_id, UINT16 Handle, BOOLEAN IsIndication, EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback, VOID *Context)
{
	UINT16 index = att_db_get_idx_from_hdl(conn_id, Handle);
	EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *attr;
	if (index >= BT_LE_PER_DEV_ATTR)
	{
		loge("Error\n");
		return EFI_INVALID_PARAMETER;
	}

	if (Callback)
	{
		attr = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO *) uefi_app_data.remote_device_list[conn_id].BtLeSbDev->AttrDatabase[index];

		if (!IsIndication)
		{
			if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic))
			{
				if (IS_ATTRIBUTE_PROPERTY_NOTIFY(attr->CharacteristicProperties) == FALSE)
				{
					loge("Attribute does not support notification");
					return EFI_ACCESS_DENIED;
				}
			}
		}
		else
		{
			if (attr && BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(&attr->Header, BluetoothGattTypeCharacteristic))
			{
				if (IS_ATTRIBUTE_PROPERTY_INDICATE(attr->CharacteristicProperties) == FALSE)
				{
					loge("Attribute does not support indication");
					return EFI_ACCESS_DENIED;
				}
			}
		}
	}

	uefi_app_data.remote_device_list[conn_id].notify_cb = Callback;
	uefi_app_data.remote_device_list[conn_id].notify_cb_context = Context;

	return enable_notification_indication(conn_id, Handle, IsIndication, Callback ? TRUE:FALSE);
}

EFI_STATUS stack_get_local_data(EFI_BLUETOOTH_CONFIG_DATA_TYPE data_type, UINTN *data_size, VOID *data)
{
	trans_id_t new_trans_id = 0;
	BLUETOOTH_LE_ADDRESS *Address;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	switch (data_type)
	{
	case EfiBluetoothConfigDataTypeIoCapability:
		if (*data_size < 1)
		{
			*data_size = 1;
			return EFI_BUFFER_TOO_SMALL;
		}
		*((UINT8*)data) = uefi_app_data.iocap;
		break;
	case EfiBluetoothConfigDataTypeOOBDataFlag:
		if (*data_size < 1)
		{
			*data_size = 1;
			return EFI_BUFFER_TOO_SMALL;
		}
		*((UINT8*)data) = uefi_app_data.oobflag;
		break;
	case EfiBluetoothConfigDataTypeKeyType:
		if (*data_size < 1)
		{
			*data_size = 1;
			return EFI_BUFFER_TOO_SMALL;
		}
		*((UINT8*)data) = uefi_app_data.authreq;
		break;
	case EfiBluetoothConfigDataTypeEncKeySize:
		if (*data_size < 1)
		{
			*data_size = 1;
			return EFI_BUFFER_TOO_SMALL;
		}
		*((UINT8*)data) = uefi_app_data.enckeysize;
		break;
	case EfiBluetoothConfigDataTypeDeviceName:
		if (*data_size < MAX_LOCAL_NAME_LEN)
		{
			*data_size = MAX_LOCAL_NAME_LEN;
			return EFI_BUFFER_TOO_SMALL;
		}
		memset(data, 0, *data_size);
		*data_size = iLE_get_local_device_name(new_trans_id, data);
		break;
	case EfiBluetoothConfigDataTypeBDADDR:
		if (*data_size < sizeof(BLUETOOTH_LE_ADDRESS))
		{
			*data_size = sizeof(BLUETOOTH_LE_ADDRESS);
			return EFI_BUFFER_TOO_SMALL;
		}
		Address = data;
		*data_size = sizeof(BLUETOOTH_LE_ADDRESS);
		Address->Type = iLE_get_bdaddr(new_trans_id, Address->Address);
		break;
    default:
		return EFI_INVALID_PARAMETER;
	}
	return EFI_SUCCESS;
}

EFI_STATUS stack_set_local_data(EFI_BLUETOOTH_CONFIG_DATA_TYPE data_type, UINTN data_size, VOID *data)
{
	EFI_STATUS status = EFI_SUCCESS;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	switch (data_type)
	{
	case EfiBluetoothConfigDataTypeDeviceName:
		status = iLE_set_local_device_name(new_trans_id, (UINT8)data_size, data);
		break;
	case EfiBluetoothConfigDataTypeIoCapability:
		status = iLE_smp_set_io_capabilities(new_trans_id, *((UINT8*)data));
		if (!status)
			uefi_app_data.iocap = *((UINT8*)data);
		break;
	case EfiBluetoothConfigDataTypeOOBDataFlag:
		uefi_app_data.oobflag = *((UINT8*)data);
		break;
	case EfiBluetoothConfigDataTypeKeyType:
		uefi_app_data.authreq = *((UINT8*)data);
		break;
	case EfiBluetoothConfigDataTypeEncKeySize:
		uefi_app_data.enckeysize = *((UINT8*)data);
		break;
	default:
		status = EFI_INVALID_PARAMETER;
	}
	return status;
}

EFI_STATUS stack_smp_auth(BLUETOOTH_LE_ADDRESS *bd_addr, EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE data_type, UINTN length, VOID* data)
{
	INT8 status;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	switch(data_type)
	{
	case EfiBluetoothSmpAuthorizationRequestEvent:
		status = iLE_send_authorization(new_trans_id, bd_addr->Address, bd_addr->Type, *((UINT8*)data),
				uefi_app_data.authreq, uefi_app_data.enckeysize);
		break;
	case EfiBluetoothSmpPasskeyRequestEvent:
		status = iLE_send_passkey(new_trans_id, bd_addr->Address, bd_addr->Type, *((UINT32*)data));
		break;
#if (SECURE_CONNECTION == TRUE)
	case EfiBluetoothSmpNumericComparisonEvent:
		status = iLE_smp_send_nc_result(new_trans_id, bd_addr->Address, bd_addr->Type, *((UINT8*)data));
		break;
#endif
	case EfiBluetoothSmpOOBDataRequestEvent:
		loge("EfiBlutoothSmpOOBDataRequestEvent not supported!");
		status = STATUS_ERR_OPERATION_NOT_SUPPORTED;
		break;
	default:
		status = STATUS_ERR_INVALID_PARAM;
	}

	if (status)
	{
		loge("Status %d", status);
		return EFI_DEVICE_ERROR;
	}

	return EFI_SUCCESS;
}

EFI_STATUS stack_remove_device(BLUETOOTH_LE_ADDRESS *bd_addr)
{
	trans_id_t new_trans_id = 0;

	logd("");

	add_appid_to_trans_id(&new_trans_id, uefi_app_handle);

	/* Remove the device from Auto Connect list if exist */
	iLE_auto_connect(new_trans_id, bd_addr->Address, bd_addr->Type, FALSE);

#if (CONTROLLER_PRIVACY)
	/* Remove device from Resolving list */
	iLE_remove_from_resolvinglist(new_trans_id, bd_addr->Type, bd_addr->Address);
#endif /* CONTROLLER_PRIVACY */

	/* Remove HID Information from persistent storage */
	delete_hid_info(bd_addr);

	return EFI_SUCCESS;
}

#endif
