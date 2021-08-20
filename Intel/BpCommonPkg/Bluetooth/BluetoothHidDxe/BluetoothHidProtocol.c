//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 This file implements the interfaces defined in EDKII_HID_PROTOCOL.

Copyright (c) 2013 - 2019, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "BluetoothHidDxe.h"

typedef struct {
  VOID            *Command;
  UINTN           CommandSize;
  UINT8           StopResponseCode;
  VOID            *Payload;
  UINTN           PayloadSize;
} BLUETOOTH_L2CAP_COMMAND_STRUCTURE;

UINT8  gHid1[] = {0xa2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
UINT8  gHid2[] = {0xa2, 0x02, 0x00, 0x00, 0x00, 0x00};
UINT8  gHid3[] = {0xa2, 0x03, 0x00};
UINT8  gHid4[] = {0xa2, 0x04, 0x00};
UINT8  gHid5[] = {0xa2, 0x05, 0x00};
UINT8  gHid6[] = {0xa2, 0xff, 0x00};
UINT8  gHidC7[] = {0x41, 0x03};
UINT8  gHidC8[] = {0x41, 0x03};

UINT8  mHidr1[] = {0x41, 0x03};

BLUETOOTH_L2CAP_COMMAND_STRUCTURE   mCommandHidInit3[] = {
  {&gHid1,  sizeof(gHid1),},
  {&gHid2,  sizeof(gHid2),},
  {&gHid3,  sizeof(gHid3),},
  {&gHid4,  sizeof(gHid4),},
  {&gHid5,  sizeof(gHid5),},
  {&gHid6,  sizeof(gHid6),},
};

BLUETOOTH_L2CAP_COMMAND_STRUCTURE   mCommandHidInit4[] = {
  {&gHidC7,  sizeof(gHidC7),},
  {&gHidC8,  sizeof(gHidC8),},
};

STATIC volatile BOOLEAN RequestOngoing = FALSE;
STATIC VOID *ResponseData = NULL;
STATIC UINTN ResponseDataLength= 0;

/**
  Retrieves the information of a Bluetooth human interface device.

  @param[in]   This     A pointer to the EDKII_HID_PROTOCOL instance.
  @param[out]  HidInfo  A pointer to the EDKII_HID_INFO structure.

  @retval  EFI_SUCCESS  The information of a Bluetooth human interface device
                        has been retrieved.

**/
EFI_STATUS
EFIAPI
BtHidGetDeviceInfo (
  IN  EDKII_HID_PROTOCOL    *This,
  OUT EDKII_HID_INFO        *HidInfo
  )
{
  BT_HID_DEV       *BtHidDev;
  LIST_ENTRY       *Link;
  HID_REPORT_FMT   *ReportFormatList;

  BtHidDev = BT_HID_DEV_FROM_HID_PROTOCOL (This);

  Link  = GetFirstNode (&BtHidDev->ReportFormatList);
  while (!IsNull (&BtHidDev->ReportFormatList, Link)) {
    ReportFormatList = ITEM_FROM_LINK(Link);

    if ( ReportFormatList->UsagePage == BT_HID_BUTTON_USAGE_PAGE && ReportFormatList->Usage == BT_HID_POINTER_USAGE ) {
      HidInfo->HidType = HidTypeMouse;
      break;
    } else if ( ReportFormatList->UsagePage == BT_HID_KEYBOARD_USAGE_PAGE && ReportFormatList->Usage == BT_HID_KEYBOARD_USAGE ) {
      HidInfo->HidType = HidTypeKeyBoard;
    }

    Link = GetNextNode (&ReportFormatList->Link, Link);
  }

  return EFI_SUCCESS;
}

/**
  Starts the data transmission for a Bluetooth human interface device.

  @param[in]  This                        A pointer to the EDKII_HID_PROTOCOL
                                          interface.
  @param[in]  HidControlCallback          The callback function for data
                                          transferred via control transfer.
  @param[in]  HidControlCallbackContext   Data passed into the control transfer
                                          callback function.
  @param[in]  HidInterruptCallback        The callback function for data
                                          transferred via interrupt transfer.
  @param[in]  HidInterrupCallbackContext  Data passed into the interrupt
                                          transfer callback function.

  @retval  EFI_SUCCESS  The operation succeeds.

**/
EFI_STATUS
EFIAPI
BtHidStart (
  IN EDKII_HID_PROTOCOL           *This,
  IN EDKII_HID_SERVICE_CALLBACK   HidControlCallback,
  IN VOID                         *HidControlCallbackContext,
  IN EDKII_HID_SERVICE_CALLBACK   HidInterruptCallback,
  IN VOID                         *HidInterrupCallbackContext
  )
{
  BT_HID_DEV                      *BtHidDev;

  BtHidDev    = BT_HID_DEV_FROM_HID_PROTOCOL (This);

  BtHidDev->HidInterruptCallback        = HidInterruptCallback;
  BtHidDev->HidInterruptCallbackContext = HidInterrupCallbackContext;

  return EFI_SUCCESS;
}

/**
  Stops the data transmission for a Bluetooth human interface device.

  @param[in]  This  A pointer to the EDKII_HID_PROTOCOL instance.

  @retval  EFI_UNSUPPORTED  The operation is not supported.

**/
EFI_STATUS
EFIAPI
BtHidStop (
  IN EDKII_HID_PROTOCOL            *This
  )
{
  BT_HID_DEV                       *BtHidDev;

  BtHidDev = BT_HID_DEV_FROM_HID_PROTOCOL (This);

  BtHidDev->HidInterruptCallback = NULL;
  BtHidDev->HidInterruptCallbackContext = NULL;

  return EFI_UNSUPPORTED;
}

/**
  The callback function to a read attribute request.

  @param[in]  This        A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                          instance.
  @param[in]  Data        Data received. The first byte is the attribute
                          opcode, followed by opcode specific fields.
                          See Bluetooth specification, Vol 3, Part F, Attribute
                          Protocol. It might be a normal RESPONSE message, or
                          ERROR RESPONSE message.
  @param[in]  DataLength  The length of Data in bytes.
  @param[in]  Context     The context passed from the callback registration
                          request.

  @retval  EFI_SUCCESS  The callback function completes successfully.

**/
EFI_STATUS
EFIAPI
ReadCallback (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL *This,
  IN VOID                             *Data,
  IN UINTN                            DataLength,
  IN VOID                             *Context
  )
{
  UINT8  *Buffer;
  UINT8  OpCode;
  UINT16 Handle;
  UINTN  CopyLength;

  Buffer = Data;
  OpCode = *Buffer;
  Handle = Context != NULL ? *((UINT16*)Context) : 0;

  DEBUG ((EFI_D_INFO, "Got opcode 0x%02x for handle 0x%04x\n", OpCode, Handle));

  Buffer++;
  DataLength--;
  CopyLength = MIN(DataLength, ResponseDataLength);

  switch (OpCode) {
    case BluetoothAttOpReadResponse:
      CopyMem (ResponseData, Buffer, CopyLength);
      break;
    case BluetoothAttOpReadByTypeResponse:
    case BluetoothAttOpReadMultipleResponse:
    case BluetoothAttOpErrorResponse:
    default:
      DEBUG ((EFI_D_ERROR, "Invalid opcode\n"));
  }

  RequestOngoing = FALSE;

  return EFI_SUCCESS;
}

/**
  Submit a request to a Bluetooth human interface device over the Bluetooth
  L2CAP layer.

  @param[in]      This     A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                           instance.
  @param[in]      Request  A pointer to the EDKII_HID_REQUEST_TYPE structure that
                           specifies the type of the request.
  @param[in]      Value    Value to set for the Bluetooth human interface
                           device.
  @param[in]      Length   The length of Data in bytes.
  @param[in,out]  Data     A pointer to the buffer for data transmission.

  @retval  EFI_UNSUPPORTED  The type of request is not supported.
  @retval  Other            A value from other functions.

**/
EFI_STATUS
EFIAPI
BtHidSendRequest (
  IN EDKII_HID_PROTOCOL      *This,
  IN EDKII_HID_REQUEST_TYPE  Request,
  IN UINT16                  Value,
  IN UINT16                  Length,
  IN OUT VOID                *Data
  )
{
  BT_HID_DEV                             *BtHidDev;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL       *BluetoothAttribute;
  EFI_STATUS                             Status;
  LIST_ENTRY                             *Link;
  HID_REPORT_INFO                        *ReportInfo;
  HID_REPORT_FMT                         *ReportItem;
  UINT8                                  LedReportId;
  UINT8                                  *Buffer;

  BtHidDev           = BT_HID_DEV_FROM_HID_PROTOCOL (This);
  BluetoothAttribute = BtHidDev->BluetoothAttribute;
  LedReportId        = 0;

  //DEBUG ((EFI_D_INFO, "HidSendRequest!\n"));
  Status = EFI_SUCCESS;
  switch (Request) {
  case EdkiiHidRequestSetReport:
    if (BtHidDev->LEDReportHandle > 0) {
      Status = BluetoothAttributeWrite(BluetoothAttribute, BtHidDev->LEDReportHandle + 1, EfiBluetoothAttributeWriteCommand, Length, Data, NULL, NULL);
    }
    break;
  case EdkiiHidRequestGetReportMap:
    RequestOngoing = TRUE;
    ResponseData = Data;
    ResponseDataLength = Length;
    Status = BluetoothAttributeRead(BluetoothAttribute, BtHidDev->ReportMapHandle + 1, 0, 0, ReadCallback, &BtHidDev->ReportMapHandle);
    do {} while (RequestOngoing);
    break;
  case EdkiiHidRequestGetReportReferDesc:
    Link  = GetFirstNode (&BtHidDev->ReportFormatList);
    while (!IsNull (&BtHidDev->ReportFormatList, Link)) {
      ReportItem = ITEM_FROM_LINK(Link);

      if (ReportItem->UsagePage == BT_HID_LED_USAGE_PAGE) {
        LedReportId = ReportItem->ReportId;
        break;
      }

      Link  = GetNextNode (&BtHidDev->ReportFormatList, Link);
    }

    Link  = GetFirstNode (&BtHidDev->HidReportInfo);
    while (!IsNull (&BtHidDev->HidReportInfo, Link)) {
      ReportInfo = BT_HID_REPORT_INFO_FROM_LINK(Link);
      RequestOngoing = TRUE;
      ResponseDataLength = 10;
      ResponseData = AllocateZeroPool(ResponseDataLength);
      ASSERT (ResponseData != NULL);
      Status = BluetoothAttributeRead(BluetoothAttribute, ReportInfo->ReportReferDescHandle, 0, 0, ReadCallback, &ReportInfo->ReportHandle);
      do {} while (RequestOngoing);
      Buffer = ResponseData;
      ReportInfo->ReportID = Buffer[0];
      ReportInfo->ReportType = Buffer[1];

      // If the Output report is for setting the LEDs, set the handle correctly
      if ((ReportInfo->ReportType == HID_REPORT_TYPE_OUTPUT) && (ReportInfo->ReportID == LedReportId)) {
        BtHidDev->LEDReportHandle = ReportInfo->ReportHandle;
      }
      FreePool(ResponseData);
      Link  = GetNextNode (&BtHidDev->HidReportInfo, Link);
    }
    break;
  case EdkiiHidRequestGetReport:
  case EdkiiHidRequestGetIdle:
  case EdkiiHidRequestSetIdle:
  default:
    return EFI_UNSUPPORTED;
  }

  return Status;
}


/**
  The callback function to the SetNotification request.

  @param[in]  This        A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                          instance.
  @param[in]  Data        Data received. The first byte is the attribute
                          opcode, followed by opcode specific fields.
                          See Bluetooth specification, Vol 3, Part F, Attribute
                          Protocol. It might be a normal RESPONSE message, or
                          ERROR RESPONSE message.
  @param[in]  DataLength  The length of Data in bytes.
  @param[in]  Context     The context passed from the callback registration
                          request.

  @retval  EFI_SUCCESS            The callback function completes successfully.
  @retval  EFI_INVALID_PARAMETER  The input parameters are invalid.

**/
EFI_STATUS
EFIAPI
NotificationCallback (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL *This,
  IN VOID                             *Data,
  IN UINTN                            DataLength,
  IN VOID                             *Context
  )
{
  UINT8           *Buffer;
  UINT8           OpCode;
  BT_HID_DEV      *BtHidDev;
  LIST_ENTRY      *Link;
  HID_REPORT_INFO *ReportInfo;
  UINT16          ReportHandle;

  //
  // Within this function, the first 3 bytes of 'Data' will be explicitly
  // consumed. Byte 0 is the opcode, bytes 1-2 are used for report handle.
  //
  if ((Data == NULL) || (DataLength < 3)) {
    return EFI_INVALID_PARAMETER;
  }

  Buffer    = Data;
  OpCode    = *Buffer;
  BtHidDev  = (BT_HID_DEV *)Context;

  Buffer++;
  DataLength--;

  ReportHandle = *(UINT16 *)Buffer;

  switch (OpCode) {
    case BluetoothAttOpHandleValueNotification:

      /* Zero filling the byte since it will not be used further */
      Buffer[0] = 0;

      /* The buffer that we plan to pass to the callback needs
       * to have the report id appended before the buffer. We are using the lower byte of the opcode field to store this value.
       * Thus, Advancing the buffer pointer by 1 and decrementing the length by 1.
       */
      Buffer += 1;
      DataLength -= 1;
      Link  = GetFirstNode (&BtHidDev->HidReportInfo);
      // Populate the report ID correctly and proceed
      while (!IsNull (&BtHidDev->HidReportInfo, Link)) {
        ReportInfo = BT_HID_REPORT_INFO_FROM_LINK(Link);

        if ( ReportInfo->ReportHandle + 1 == ReportHandle ) {
          Buffer[0] = ReportInfo->ReportID;
          break;
        }

        Link  = GetNextNode (&BtHidDev->HidReportInfo, Link);
      }

      BtHidDev->HidInterruptCallback(Buffer, DataLength, BtHidDev->HidInterruptCallbackContext);
      break;
    case BluetoothAttOpHandleValueIndication:
      break;
  }

  return EFI_SUCCESS;
}

/**
  Registers or unregisters a server initiated message on a characteristic value
  on remote server.

  @param[in]  This   A pointer to the EDKII_HID_PROTOCOL instance.
  @param[in]  Value  Type of notification for server initiated attribute
                     protocol. A value of zero means unregister the server
                     initiated callback.

  @retval  EFI_UNSUPPORTED  The operation is not supported
  @retval  Other            A value from other functions.

**/
EFI_STATUS
EFIAPI
BtHidSetNotification (
  IN EDKII_HID_PROTOCOL    *This,
  IN UINT8                 Value
  )
{
  BT_HID_DEV                                 *BtHidDev;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL           *BluetoothAttribute;
  EFI_STATUS                                 Status;
  EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER NotifyParam;
  LIST_ENTRY                                 *Link;
  HID_REPORT_INFO                            *ReportInfo;

  BtHidDev    = BT_HID_DEV_FROM_HID_PROTOCOL (This);
  BluetoothAttribute = BtHidDev->BluetoothAttribute;
  Status      = EFI_UNSUPPORTED;

  if (BluetoothAttribute == NULL) {
    return EFI_UNSUPPORTED;
  }

  //DEBUG ((EFI_D_INFO, "SetNotification!\n"));

  NotifyParam.AttributeOpCode = Value;

  Link  = GetFirstNode (&BtHidDev->HidReportInfo);
  while (!IsNull (&BtHidDev->HidReportInfo, Link)) {
    ReportInfo = BT_HID_REPORT_INFO_FROM_LINK(Link);
    // Register for all Input Reports
    if (ReportInfo->ReportType == HID_REPORT_TYPE_INPUT) {
      NotifyParam.Parameter.Notification.AttributeHandle = ReportInfo->ReportHandle;
      if (Value != 0) {
        Status = BluetoothAttribute->RegisterForServerNotification(BluetoothAttribute, &NotifyParam, NotificationCallback, BtHidDev);
      } else {
        Status = BluetoothAttribute->RegisterForServerNotification(BluetoothAttribute, &NotifyParam, 0, 0);
      }
    }
    Link  = GetNextNode (&BtHidDev->HidReportInfo, Link);
  }

  DEBUG ((EFI_D_INFO, "RegisterForServerNotification - %r\n", Status));

  return Status;
}


