/** @file
  Userial layer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "config_host.h"
#include "tl.h"
#include "error_code.h"

#include "osa_types.h"
#include "hci_host.h"
#include "int_interface.h"
#include "utils.h"

#include "BluetoothBusDxe.h"

#define MODULE_DBG_LVL USERIAL_DBG_LVL
#include "log.h"
static BTHC_DEV *bt_hc_device = NULL;
static EFI_EVENT bt_tl_evt = NULL;

void EFIAPI process_data(EFI_EVENT event, VOID *context)
{
    logd("");
    interface_handler();
}

EFI_STATUS EFIAPI tl_hci_event_cback(VOID *data, UINTN len, VOID *context)
{
    UINT8 *buffer = (UINT8*)alloc((UINT8)len + 1);
    if (!buffer)
        return EFI_OUT_OF_RESOURCES;

    buffer[0] = HCI_EVT;
    logd("HCI Event Received");
    hex_dump("---> 04 ",data, len);
    CopyMem(buffer + 1, data, len);
    rx_req_hci_evt_msg(buffer, (UINT8)len + 1);
#if (RX_PROCESSING_IN_TIMER_THREAD == TRUE)
    if(!g_local_adapter.thread_busy)
    {
    	logd("Signaling event");
		gBS->SignalEvent(bt_tl_evt);
    }
    else
    {
    	logd("Event already signaled");
    }
#endif
    dealloc(buffer);
    return EFI_SUCCESS;
}

EFI_STATUS  EFIAPI tl_hci_acl_data_cback(VOID *data, UINTN len, VOID *context)
{
    UINT8 *buffer = (UINT8*)alloc((UINT8)len + 1);
    if (!buffer)
        return EFI_OUT_OF_RESOURCES;

    logd("HCI ACL data received \n");
    hex_dump("---> ",data, len);

    buffer[0] = HCI_ACL;

    CopyMem(buffer + 1, data, len);
    rx_req_hci_evt_msg(buffer, (UINT8)len + 1);
#if (RX_PROCESSING_IN_TIMER_THREAD == TRUE)
    if(!g_local_adapter.thread_busy)
    {
    	logd("Signaling event");
    	gBS->SignalEvent(bt_tl_evt);
    }
    else
    {
    	logd("Event already signaled");
    }
#endif
    dealloc(buffer);
    return EFI_SUCCESS;
}

INT8 tl_init(char* device, int ispeed)
{
    EFI_STATUS status;
    EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *mBluetoothLeConfig;

	if (!bt_hc_device)
	{
		status = gBS->LocateProtocol (&gEfiBluetoothLeConfigProtocolGuid, NULL, (void**)&mBluetoothLeConfig);
		if (EFI_ERROR (status))
		{
			loge("ERROR: Bluetooth driver not loaded!\n");
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
		}
		bt_hc_device = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(mBluetoothLeConfig);
	}

	status = bt_hc_device->BluetoothHc->AsyncReceiveEvent( bt_hc_device->BluetoothHc, TRUE, BT_HCI_INTERRUPT_TIMER_INTERVAL, 1024, tl_hci_event_cback, bt_hc_device);
	if(EFI_ERROR (status))
	{
		loge("AsyncReceiveEvent: %x!\n", status);
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	status = bt_hc_device->BluetoothHc->AsyncReceiveACLData( bt_hc_device->BluetoothHc, TRUE, BT_ACL_INTERRUPT_TIMER_INTERVAL, 0x40, tl_hci_acl_data_cback, bt_hc_device);
	if(EFI_ERROR (status))
	{
		loge("AsyncReceiveACLData: %x!\n", status);
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, process_data, bt_hc_device, &bt_tl_evt);
	if(EFI_ERROR (status))
	{
		loge("CreateEvent: %x!\n", status);
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	return STATUS_SUCCESS;
}

INT8 tl_write(UINT8 *buffer, UINT16 len)
{
    UINT8 type = buffer[0];
    EFI_STATUS status;
    UINTN length;
    switch(type)
    {
        case HCI_CMD :
          //  logd("Writing command to controller");
            hex_dump("<--- ", buffer, len);
            length = (UINTN)len-1;
            status = bt_hc_device->BluetoothHc->SendCommand(bt_hc_device->BluetoothHc, (&length), buffer + 1, 0);
            if (EFI_ERROR (status))
            {
                if (status == EFI_DEVICE_ERROR) {
                    loge("HCI_CMD: Write Failed!. Device Error!");
                    return STATUS_ERR_DEVICE_ERROR;
                }
                loge("Sending Falied %d\n", status);
                return STATUS_SUCCESS;
            }
            break;
        case HCI_ACL :
          //  logd("Writing ACL data to controller");
            hex_dump("<--- ", buffer, len);
            length = (UINTN)len-1;
            status = bt_hc_device->BluetoothHc->SendACLData(bt_hc_device->BluetoothHc, (&length), buffer + 1, 0);
            if (EFI_ERROR (status))
            {
                if (status == EFI_DEVICE_ERROR) {
                    loge("HCI_ACL: Write Failed!. Device Error!");
                    return STATUS_ERR_DEVICE_ERROR;
                }
                loge("Sending Falied %d\n", status);
            }
                return STATUS_SUCCESS;
            break;

    }
    return STATUS_SUCCESS;
}

void tl_recv_msg(UINT8 *buffer)
{
    EFI_STATUS status;
    EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *mBluetoothLeConfig;
    UINTN len = HCI_CMD_EVT_MAX_SIZE - 1;

    logd("");

    if (!bt_hc_device)
    {
        status = gBS->LocateProtocol (&gEfiBluetoothLeConfigProtocolGuid, NULL, (void**)&mBluetoothLeConfig);
        if (EFI_ERROR (status))
        {
            loge("ERROR: Bluetooth driver not loaded!\n");
            return;
        }
        bt_hc_device = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(mBluetoothLeConfig);
    }
    bt_hc_device->BluetoothHc->ReceiveEvent(bt_hc_device->BluetoothHc, &len, buffer + 1, 0);
    buffer[0] = HCI_EVT;

    hex_dump("---> ", buffer, len + 1);
    rx_req_hci_evt_msg(buffer, (UINT8)len + 1);
    process_data(NULL, NULL);

    if (buffer[1] == HCI_EVENT_CMD_STATUS)
    {
        len = HCI_CMD_EVT_MAX_SIZE - 1;
        bt_hc_device->BluetoothHc->ReceiveEvent(bt_hc_device->BluetoothHc, &len, buffer + 1, 0);
        buffer[0] = HCI_EVT;

        hex_dump("---> ", buffer, len + 1);
        rx_req_hci_evt_msg(buffer, (UINT8)len + 1);
        process_data(NULL, NULL);
    }
}

void tl_close()
{
	bt_tl_evt = NULL;
	bt_hc_device = NULL;
}

void tl_remove_async_event()
{
	EFI_STATUS status;
	loge("");
	if (bt_tl_evt != NULL)
		gBS->CloseEvent (bt_tl_evt);
	status = bt_hc_device->BluetoothHc->AsyncReceiveEvent( bt_hc_device->BluetoothHc, FALSE, 0, 0, NULL, bt_hc_device);
	loge("Cancel AsyncReceiveEvent: %x!\n", status);
}
