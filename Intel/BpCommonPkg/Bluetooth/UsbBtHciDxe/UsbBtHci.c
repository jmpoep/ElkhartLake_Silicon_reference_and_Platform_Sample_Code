//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  This file implements interfaces defined in EFI_BLUETOOTH_HC_PROTOCOL.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "UsbBtHciDxe.h"
#include "IndustryStandard/BluetoothHci.h"

#define DUMP_ASCII



//
// 1. Primary Controller Descriptors
// ================ ================= ========================== ============= =========================
// Interface Number Alternate Setting Suggested Endpoint Address Endpoint Type Suggested Max Packet Size
// ================ ================= ========================== ============= =========================
// HCI Commands
//  N/A              N/A               0x00                       Control       8/16/32/64
// ================ ================= ========================== ============= =========================
// HCI Events
//  0                0                 0x81                       Interrupt(IN) 16
// ================ ================= ========================== ============= =========================
// ACL Data
//  0                0                 0x82                       Bulk (IN)     32/64
//  0                0                 0x02                       Bulk (OUT)    32/64
// ================ ================= ========================== ============= =========================
//
// 2. AMP Controller Descriptors
// ================ ================= ========================== ============= =========================
// Interface Number Alternate Setting Suggested Endpoint Address Endpoint Type Suggested Max Packet Size
// ================ ================= ========================== ============= =========================
// HCI Commands
//  N/A              N/A               0x00                       Control       64
// ================ ================= ========================== ============= =========================
// HCI Events
//  N                0                 0x81                       Interrupt(IN) 512
// ================ ================= ========================== ============= =========================
// ACL Data
//  N                0                 0x82                       Bulk (IN)     512
//  N                0                 0x02                       Bulk (OUT)    512
// ================ ================= ========================== ============= =========================
//
/**
  Send HCI command packet.

  The UsbBtHciSendCommand() function sends HCI command packet. Buffer holds the
  whole HCI command packet, including OpCode, OCF, OGF, parameter length, and
  parameters. When this function is returned, it just means the HCI command
  packet is sent, it does not mean the command is success or complete. Caller
  might need to wait a command status event to know the command status, or wait
  a command complete event to know if the command is completed.

  @param[in]      This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                              instance.
  @param[in,out]  BufferSize  On input, indicates the size, in bytes, of the
                              data buffer specified by Buffer. On output,
                              indicates the amount of data actually
                              transferred.
  @param[in]      Buffer      A pointer to the buffer of data that will be
                              transmitted to Bluetooth host controller.
  @param[in]      Timeout     Indicating the transfer should be completed
                              within this time frame. The units are in
                              milliseconds. If Timeout is 0, then the caller
                              must wait for the function to be completed until
                              EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI command packet is sent successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Sending HCI command packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Sending HCI command packet fail due to host
                                  controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciSendCommand (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  IN VOID                           *Buffer,
  IN UINTN                          Timeout
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;
  EFI_USB_DEVICE_REQUEST  Request;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);
  UsbIo = UsbBtHciDev->UsbIo;

  //
  // 1. Single Function Primary Controller
  //    bmRequestType 0x20 Host-to-device class request, device as target
  //    bRequest      0x00
  //    wValue        0x00
  //    wIndex        0x00
  //
  // 2. Primary Controller Function in a Composite Device
  //    bmRequestType 0x21 Host-to-Interface class request, interface as target
  //    bRequest      0x00
  //    wValue        0x00
  //    wIndex        IF#  This is the actual Interface number within the composite device.
  //
  // 3. AMP Controller (either in a single function device or included in a composite device)
  //    bmRequestType 0x21 Host-to-Interface class request, interface as target
  //    bRequest      0x2B Arbitrary value chosen to identify requests targeted to an AMP controller function.
  //    wValue        0x00
  //    wIndex        IF#  This is the actual Interface number within the composite device.
  //

  ZeroMem (&Request, sizeof(Request));
  switch (UsbBtHciDev->BtHciType) {
  case BtHciPrimaryControllerSingle:
    Request.RequestType = 0x20;
    Request.Request     = 0x00;
    Request.Value       = 0x0000;
    Request.Index       = 0x0000;
    break;
  case BtHciPrimaryControllerComposit:
    Request.RequestType = 0x21;
    Request.Request     = 0x00;
    Request.Value       = 0x0000;
    Request.Index       = UsbBtHciDev->InterfaceDescriptor.InterfaceNumber;
    break;
  case BtHciAMPControllerSingle:
  case BtHciAMPControllerComposit:
    Request.RequestType = 0x21;
    Request.Request     = 0x2B;
    Request.Value       = 0x0000;
    Request.Index       = UsbBtHciDev->InterfaceDescriptor.InterfaceNumber;
    break;
  }

  Request.Length      = (UINT16)*BufferSize;

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendCommand - RequestType 0x%02x\n", Request.RequestType));

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    EfiUsbDataOut,
                    (UINT32)Timeout,
                    Buffer,
                    *BufferSize,
                    &UsbStatus
                    );
  if (!EFI_ERROR (Status) && (UsbStatus != EFI_USB_NOERROR)) {
    DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendCommand - UsbStatus 0x%04x\n", UsbStatus));
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Receive HCI event packet.

  The UsbBtHciReceiveEvent() function receives HCI event packet. Buffer holds
  the whole HCI event packet, including EventCode, parameter length, and
  parameters.

  @param[in]      This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                              instance.
  @param[in,out]  BufferSize  On input, indicates the size, in bytes, of the
                              data buffer specified by Buffer. On output,
                              indicates the amount of data actually
                              transferred.
  @param[out]     Buffer      A pointer to the buffer of data that will be
                              received from Bluetooth host controller.
  @param[in]      Timeout     Indicating the transfer should be completed
                              within this time frame. The units are in
                              milliseconds. If Timeout is 0, then the caller
                              must wait for the function to be completed until
                              EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI event packet is received
                                  successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Receiving HCI event packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Receiving HCI event packet fail due to host
                                  controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciReceiveEvent (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  OUT VOID                          *Buffer,
  IN UINTN                          Timeout
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);
  UsbIo = UsbBtHciDev->UsbIo;

  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    UsbBtHciDev->IntEndpointDescriptor.EndpointAddress,
                    Buffer,
                    BufferSize,
                    Timeout,
                    &UsbStatus
                    );
  if (!EFI_ERROR (Status) && (UsbStatus != EFI_USB_NOERROR)) {
    DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveEvent - UsbStatus 0x%04x\n", UsbStatus));
    Status = EFI_DEVICE_ERROR;
  }
  if (Status == EFI_SUCCESS) {
    //DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveEvent - 0x%02x\n", UsbBtHciDev->IntEndpointDescriptor.EndpointAddress));

  }

  return Status;
}

/**
  The async callback of UsbBtHciAsyncReceiveEvent().

  @param[in]  Data        Data received via asynchronous transfer.
  @param[in]  DataLength  The length of Data in bytes, received via
                          asynchronous transfer.
  @param[in]  Context     Context passed from asynchronous transfer request.
  @param[in]  Status      The USB transfer result.

  @retval  EFI_SUCCESS    The callback does execute successfully.
  @retval  Others         The callback doesn't execute successfully.

**/
EFI_STATUS
EFIAPI
UsbBtHciAsyncReceiveEventCallback (
  IN VOID   *Data,
  IN UINTN  DataLength,
  IN VOID   *Context,
  IN UINT32 Status
  )
{
  EFI_STATUS              EfiStatus;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;

  EfiStatus = EFI_SUCCESS;

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciAsyncReceiveEventCallback - 0x%04x\n", Status));

  UsbBtHciDev = Context;
  UsbIo       = UsbBtHciDev->UsbIo;

  if (Status != EFI_USB_NOERROR) {
    //
    // Need recovery
    //
    if ((Status & EFI_USB_ERR_STALL) == EFI_USB_ERR_STALL) {
      UsbClearEndpointHalt (
        UsbIo,
        UsbBtHciDev->IntEndpointDescriptor.EndpointAddress,
        &UsbStatus
        );
    }

    //
    // Delete & Submit this interrupt again
    // Handler of DelayedRecoveryEvent triggered by timer will re-submit the interrupt.
    //
    UsbIo->UsbAsyncInterruptTransfer (
             UsbIo,
             UsbBtHciDev->IntEndpointDescriptor.EndpointAddress,
             FALSE,
             0,
             0,
             NULL,
             NULL
             );
    //
    // EFI_USB_INTERRUPT_DELAY is defined in USB standard for error handling.
    //
    gBS->SetTimer (
           UsbBtHciDev->DelayedRecoveryEvent,
           TimerRelative,
           EFI_USB_INTERRUPT_DELAY
           );
    return EFI_DEVICE_ERROR;
  }


  if (UsbBtHciDev->EventCallbackContext.Callback != NULL) {
    EfiStatus = UsbBtHciDev->EventCallbackContext.Callback (
                                                    Data,
                                                    DataLength,
                                                    UsbBtHciDev->EventCallbackContext.Context
                                                    );
  } else {
    EfiStatus = EFI_NOT_FOUND;
  }

  return EfiStatus;
}

/**
  Receive HCI event packet in non-blocking way.

  The UsbBtHciAsyncReceiveEvent() function receives HCI event packet in
  non-blocking way. Data in Callback function holds the whole HCI event packet,
  including EventCode, parameter length, and parameters.

  @param[in]  This             Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                               instance.
  @param[in]  IsNewTransfer    If TRUE, a new transfer will be submitted. If
                               FALSE, the request is deleted.
  @param[in]  PollingInterval  Indicates the periodic rate, in milliseconds,
                               that the transfer is to be executed.
  @param[in]  DataLength       Specifies the length, in bytes, of the data to
                               be received.
  @param[in]  Callback         The callback function. This function is called
                               if the asynchronous transfer is completed.
  @param[in]  Context          Data passed into Callback function. This is
                               optional parameter and may be NULL.

  @retval  EFI_SUCCESS            The HCI asynchronous receive request is
                                  submitted successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is TRUE:
                                    DataLength is 0.
                                    If IsNewTransfer is TRUE, and an
                                    asynchronous receive request already
                                    exists.

**/
EFI_STATUS
EFIAPI
UsbBtHciAsyncReceiveEvent (
  IN EFI_BLUETOOTH_HC_PROTOCOL              *This,
  IN BOOLEAN                                IsNewTransfer,
  IN UINTN                                  PollingInterval,
  IN UINTN                                  DataLength,
  IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK   Callback,
  IN VOID                                   *Context
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);
  UsbIo = UsbBtHciDev->UsbIo;

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciAsyncReceiveEvent - 0x%02x\n", UsbBtHciDev->IntEndpointDescriptor.EndpointAddress));

  UsbBtHciDev->EventCallbackContext.Callback = Callback;
  UsbBtHciDev->EventCallbackContext.Context = Context;
  UsbBtHciDev->EventCallbackContext.PollingInterval = PollingInterval;
  UsbBtHciDev->EventCallbackContext.DataLength = DataLength;

  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    UsbBtHciDev->IntEndpointDescriptor.EndpointAddress,
                    IsNewTransfer,
                    PollingInterval,
                    DataLength,
                    UsbBtHciAsyncReceiveEventCallback,
                    UsbBtHciDev
                    );

  return Status;
}

/**
  Send HCI ACL data packet.

  The UsbBtHciSendACLData() function sends HCI ACL data packet. Buffer holds
  the whole HCI ACL data packet, including Handle, PB flag, BC flag, data
  length, and data.

  The UsbBtHciSendACLData() function and UsbBtHciReceiveACLData() function just
  send and receive data payload from application layer. In order to protect the
  payload data, the Bluetooth bus is required to call
  HCI_Set_Connection_Encryption command to enable hardware based encryption
  after authentication completed, according to pairing mode and host
  capability.

  @param[in]       This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                               instance.
  @param[in, out]  BufferSize  On input, indicates the size, in bytes, of the
                               data buffer specified by Buffer. On output,
                               indicates the amount of data actually
                               transferred.
  @param[in]       Buffer      A pointer to the buffer of data that will be
                               transmitted to Bluetooth host controller.
  @param[in]       Timeout     Indicating the transfer should be completed
                               within this time frame. The units are in
                               milliseconds. If Timeout is 0, then the caller
                               must wait for the function to be completed until
                               EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI ACL data packet is sent successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Sending HCI ACL data packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Sending HCI ACL data packet fail due to host
                                  controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciSendACLData (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  IN VOID                           *Buffer,
  IN UINTN                          Timeout
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);
  UsbIo = UsbBtHciDev->UsbIo;

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendACLData - 0x%02x\n", UsbBtHciDev->OutEndpointDescriptor.EndpointAddress));

  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    UsbBtHciDev->OutEndpointDescriptor.EndpointAddress,
                    Buffer,
                    BufferSize,
                    Timeout,
                    &UsbStatus
                    );
  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendACLData - Status %r\n", Status));
  if (!EFI_ERROR (Status) && (UsbStatus != EFI_USB_NOERROR)) {
    DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendACLData - UsbStatus 0x%04x\n", UsbStatus));
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Receive HCI ACL data packet.

  The UsbBtHciReceiveACLData() function receives HCI ACL data packet. Buffer
  holds the whole HCI ACL data packet, including Handle, PB flag, BC flag, data
  length, and data.

  @param[in]       This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                               instance.
  @param[in, out]  BufferSize  On input, indicates the size, in bytes, of the
                               data buffer specified by Buffer. On output,
                               indicates the amount of data actually
                               transferred.
  @param[out]      Buffer      A pointer to the buffer of data that will be
                               received from Bluetooth host controller.
  @param[in]       Timeout     Indicating the transfer should be completed
                               within this time frame. The units are in
                               milliseconds. If Timeout is 0, then the caller
                               must wait for the function to be completed until
                               EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI ACL data packet is received
                                  successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Receiving HCI ACL data packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Receiving HCI ACL data packet fail due to
                                  host controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciReceiveACLData (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  OUT VOID                          *Buffer,
  IN UINTN                          Timeout
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);
  UsbIo = UsbBtHciDev->UsbIo;

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveACLData - 0x%02x\n", UsbBtHciDev->InEndpointDescriptor.EndpointAddress));
  //DEBUG ((EFI_D_VERBOSE, "BufferSize - 0x%08x\n", *BufferSize));
  //DEBUG ((EFI_D_VERBOSE, "Timeout - 0x%08x\n", Timeout));
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    UsbBtHciDev->InEndpointDescriptor.EndpointAddress,
                    Buffer,
                    BufferSize,
                    Timeout,
                    &UsbStatus
                    );
  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveACLData - Status %r\n", Status));
  if (!EFI_ERROR (Status) && (UsbStatus != EFI_USB_NOERROR)) {
    DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveACLData - UsbStatus 0x%04x\n", UsbStatus));
    Status = EFI_DEVICE_ERROR;
  }
  if (Status == EFI_SUCCESS) {
    //DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveACLData - 0x%02x\n", UsbBtHciDev->InEndpointDescriptor.EndpointAddress));
  }

  return Status;
}

/**
  Callback function when the periodic ACL event is signaled.

  @param[in]  Event     The Event this notify function registered to.
  @param[in]  Context   Pointer to the context data registered to the Event.

**/
VOID
EFIAPI
UsbBtACLInterruptHandler(
  IN EFI_EVENT   Event,
  IN VOID        *Context
  )
{
  EFI_STATUS              EfiStatus;
  USB_BTHCI_DEV           *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL     *UsbIo;
  UINT32                  UsbStatus;
  UINTN                   BufferSize;
  UINT8                   TempBuffer[0x40];

  UsbBtHciDev = Context;
  UsbIo = UsbBtHciDev->UsbIo;

  BufferSize = sizeof(TempBuffer);
  EfiStatus = UsbIo->UsbBulkTransfer (
                       UsbIo,
                       UsbBtHciDev->InEndpointDescriptor.EndpointAddress,
                       TempBuffer,
                       &BufferSize,
                       BT_ACL_INTERRUPT_WAIT_TIME,
                       &UsbStatus
                       );
  if (!EFI_ERROR (EfiStatus) && (UsbStatus != EFI_USB_NOERROR)) {
    DEBUG ((EFI_D_VERBOSE, "UsbBtACLInterruptHandler - UsbStatus - 0x%02x\n", UsbStatus));
    EfiStatus = EFI_DEVICE_ERROR;
  }
  if (EFI_ERROR (EfiStatus)) {
    return ;
  }

  //Print(L"Got data, Buffer size is %u\n", BufferSize);
  //DEBUG ((EFI_D_VERBOSE, "UsbBtACLInterruptHandler - 0x%02x\n", UsbBtHciDev->InEndpointDescriptor.EndpointAddress));

  if (UsbBtHciDev->AclCallbackContext.Callback != NULL) {
    EfiStatus = UsbBtHciDev->AclCallbackContext.Callback (
        TempBuffer,
        BufferSize,
        UsbBtHciDev->AclCallbackContext.Context);
  }
  return ;
}

/**
  Creates a periodic event to check for ACL data.

  @param[in]  UsbBtHciDev  A pointer to the USB_BTHCI_DEV structure.

  @retval  EFI_SUCCESS  A periodic event is created.
  @retval  Other        A value from other functions.

**/
EFI_STATUS
UsbBtInitACLEvent (
  IN USB_BTHCI_DEV           *UsbBtHciDev
  )
{
  EFI_STATUS  Status;

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  UsbBtACLInterruptHandler,
                  UsbBtHciDev,
                  &UsbBtHciDev->AclEvent
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_VERBOSE, "Call CreateEvent Error Status - %r", Status));
    return Status;
  }

  Status = gBS->SetTimer (
                  UsbBtHciDev->AclEvent,
                  TimerPeriodic,
                  100 * 1000 * 10 // 1 millis VS 100ns
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_VERBOSE, "Call SetTimer Error Status - %r", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

/**
  Receive HCI ACL data packet in non-blocking way.

  The UsbBtHciAsyncReceiveACLData() function receives HCI ACL data packet in
  non-blocking way. Data in Callback holds the whole HCI ACL data packet,
  including Handle, PB flag, BC flag, data length, and data.

  @param[in]  This             Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                               instance.
  @param[in]  IsNewTransfer    If TRUE, a new transfer will be submitted. If
                               FALSE, the request is deleted.
  @param[in]  PollingInterval  Indicates the periodic rate, in milliseconds,
                               that the transfer is to be executed.
  @param[in]  DataLength       Specifies the length, in bytes, of the data to
                               be received.
  @param[in]  Callback         The callback function. This function is called
                               if the asynchronous transfer is completed.
  @param[in]  Context          Data passed into Callback function. This is
                               optional parameter and may be NULL.

  @retval  EFI_SUCCESS            The HCI asynchronous receive request is
                                  submitted successfully.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    DataLength is 0.
                                    If IsNewTransfer is TRUE, and an
                                    asynchronous receive request already
                                    exists.

**/
EFI_STATUS
EFIAPI
UsbBtHciAsyncReceiveACLData (
  IN EFI_BLUETOOTH_HC_PROTOCOL              *This,
  IN BOOLEAN                                IsNewTransfer,
  IN UINTN                                  PollingInterval,
  IN UINTN                                  DataLength,
  IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK   Callback,
  IN VOID                                   *Context
  )
{
  EFI_STATUS              Status;
  USB_BTHCI_DEV           *UsbBtHciDev;

  UsbBtHciDev = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(This);

  //DEBUG ((EFI_D_VERBOSE, "UsbBtHciAsyncReceiveACLData - 0x%02x\n", UsbBtHciDev->InEndpointDescriptor.EndpointAddress));

  UsbBtHciDev->AclCallbackContext.Callback = Callback;
  UsbBtHciDev->AclCallbackContext.Context = Context;
  UsbBtHciDev->AclCallbackContext.PollingInterval = PollingInterval;
  UsbBtHciDev->AclCallbackContext.DataLength = DataLength;

  Status = EFI_SUCCESS;
  if (UsbBtHciDev->AclEvent == NULL) {
    Status = UsbBtInitACLEvent (UsbBtHciDev);
  }

  return Status;
}

/**
  Send HCI SCO data packet.

  The UsbBtHciSendSCOData() function sends HCI SCO data packet. Buffer holds
  the whole HCI SCO data packet, including ConnectionHandle, PacketStatus flag,
  data length, and data.

  @param[in]      This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                              instance.
  @param[in,out]  BufferSize  On input, indicates the size, in bytes, of the
                              data buffer specified by Buffer. On output,
                              indicates the amount of data actually
                              transferred.
  @param[in]      Buffer      A pointer to the buffer of data that will be
                              transmitted to Bluetooth host controller.
  @param[in]      Timeout     Indicating the transfer should be completed
                              within this time frame. The units are in
                              milliseconds. If Timeout is 0, then the caller
                              must wait for the function to be completed until
                              EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI SCO data packet is sent successfully.
  @retval  EFI_UNSUPPORTED        The implementation does not support HCI SCO
                                  transfer.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Sending HCI SCO data packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Sending HCI SCO data packet fail due to host
                                  controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciSendSCOData (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  IN VOID                           *Buffer,
  IN UINTN                          Timeout
  )
{
  DEBUG ((EFI_D_VERBOSE, "UsbBtHciSendSCOData - %r\n", EFI_UNSUPPORTED));
  // ISO transfer is NOT supported at this moment.
  return EFI_UNSUPPORTED;
}

/**
  Receive HCI SCO data packet.

  The UsbBtHciReceiveSCOData() function receives HCI SCO data packet. Buffer
  holds the whole HCI SCO data packet, including ConnectionHandle, PacketStatus
  flag, data length, and data.

  @param[in]      This        Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                              instance.
  @param[in,out]  BufferSize  On input, indicates the size, in bytes, of the
                              data buffer specified by Buffer. On output,
                              indicates the amount of data actually
                              transferred.
  @param[out]     Buffer      A pointer to the buffer of data that will be
                              received from Bluetooth host controller.
  @param[in]      Timeout     Indicating the transfer should be completed
                              within this time frame. The units are in
                              milliseconds. If Timeout is 0, then the caller
                              must wait for the function to be completed until
                              EFI_SUCCESS or EFI_DEVICE_ERROR is returned.

  @retval  EFI_SUCCESS            The HCI SCO data packet is received
                                  successfully.
  @retval  EFI_UNSUPPORTED        The implementation does not support HCI SCO
                                  transfer.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    BufferSize is NULL.
                                    *BufferSize is 0.
                                    Buffer is NULL.
  @retval  EFI_TIMEOUT            Receiving HCI SCO data packet fail due to
                                  timeout.
  @retval  EFI_DEVICE_ERROR       Receiving HCI SCO data packet fail due to
                                  host controller or device error.

**/
EFI_STATUS
EFIAPI
UsbBtHciReceiveSCOData (
  IN EFI_BLUETOOTH_HC_PROTOCOL      *This,
  IN OUT UINTN                      *BufferSize,
  OUT VOID                          *Buffer,
  IN UINTN                          Timeout
  )
{
  DEBUG ((EFI_D_VERBOSE, "UsbBtHciReceiveSCOData - %r\n", EFI_UNSUPPORTED));
  // ISO transfer is NOT supported at this moment.
  return EFI_UNSUPPORTED;
}

/**
  Receive HCI SCO data packet in non-blocking way.

  The UsbBtHciAsyncReceiveSCOData() function receives HCI SCO data packet in
  non-blocking way. Data in Callback holds the whole HCI SCO data packet,
  including ConnectionHandle, PacketStatus flag, data length, and data.

  @param[in]  This             Pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                               instance.
  @param[in]  IsNewTransfer    If TRUE, a new transfer will be submitted. If
                               FALSE, the request is deleted.
  @param[in]  PollingInterval  Indicates the periodic rate, in milliseconds,
                               that the transfer is to be executed.
  @param[in]  DataLength       Specifies the length, in bytes, of the data to
                               be received.
  @param[in]  Callback         The callback function. This function is called
                               if the asynchronous transfer is completed.
  @param[in]  Context          Data passed into Callback function. This is
                               optional parameter and may be NULL.

  @retval  EFI_SUCCESS            The HCI asynchronous receive request is
                                  submitted successfully.
  @retval  EFI_UNSUPPORTED        The implementation does not support HCI SCO
                                  transfer.
  @retval  EFI_INVALID_PARAMETER  One or more of the following conditions is
                                  TRUE:
                                    DataLength is 0.
                                    If IsNewTransfer is TRUE, and an asynchronous receive
                                    request already exists.

**/
EFI_STATUS
EFIAPI
UsbBtHciAsyncReceiveSCOData (
  IN EFI_BLUETOOTH_HC_PROTOCOL              *This,
  IN BOOLEAN                                IsNewTransfer,
  IN UINTN                                  PollingInterval,
  IN UINTN                                  DataLength,
  IN EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK   Callback,
  IN VOID                                   *Context
  )
{
  DEBUG ((EFI_D_VERBOSE, "UsbBtHciAsyncReceiveSCOData - %r\n", EFI_UNSUPPORTED));
  // ISO transfer is NOT supported at this moment.
  return EFI_UNSUPPORTED;
}

/**
  Handler for Delayed Recovery event.

  This function is the handler for Delayed Recovery event triggered
  by timer.
  After a device error occurs, the event would be triggered
  with interval of EFI_USB_INTERRUPT_DELAY. EFI_USB_INTERRUPT_DELAY
  is defined in USB standard for error handling.

  @param  Event              The Delayed Recovery event.
  @param  Context            Points to the USB_KB_DEV instance.

**/
VOID
EFIAPI
UsbBtHciRecoveryHandler (
  IN    EFI_EVENT    Event,
  IN    VOID         *Context
  )
{
  USB_BTHCI_DEV       *UsbBtHciDev;
  EFI_USB_IO_PROTOCOL *UsbIo;

  UsbBtHciDev = (USB_BTHCI_DEV *) Context;

  UsbIo             = UsbBtHciDev->UsbIo;

  //
  // Re-submit Asynchronous Interrupt Transfer for recovery.
  //
  UsbIo->UsbAsyncInterruptTransfer (
           UsbIo,
           UsbBtHciDev->IntEndpointDescriptor.EndpointAddress,
           TRUE,
           UsbBtHciDev->EventCallbackContext.PollingInterval,
           UsbBtHciDev->EventCallbackContext.DataLength,
           UsbBtHciAsyncReceiveEventCallback,
           UsbBtHciDev
           );
}

