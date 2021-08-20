//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Internal data structures and function prototype definitions.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _EFI_USB_BTHCI_DXE_H_
#define _EFI_USB_BTHCI_DXE_H_


#include <Uefi.h>

#include <Protocol/UsbIo.h>
#include <Protocol/BluetoothHc.h>
#include <Protocol/DevicePath.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiUsbLib.h>
#include <Library/DebugLib.h>

#include <IndustryStandard/Usb.h>
#include <IndustryStandard/Bluetooth.h>

#define BT_ACL_INTERRUPT_WAIT_TIME       1 // 500us

#define USB_BTHCI_DEV_SIGNATURE SIGNATURE_32 ('u', 'b', 't', 'h')

typedef enum {
  BtHciPrimaryControllerSingle,
  BtHciPrimaryControllerComposit,
  BtHciAMPControllerSingle,
  BtHciAMPControllerComposit,
} BTHCI_TYPE;

typedef struct {
  UINT8           DeviceClass;
  UINT8           DeviceSubClass;
  UINT8           DeviceProtocol;

  UINT8           InterfaceClass;
  UINT8           InterfaceSubClass;
  UINT8           InterfaceProtocol;

  BTHCI_TYPE      BtHciType;
} USB_BTHCI_INFO;

///
/// Device instance of USB BtHci.
///

typedef struct {
  EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK    Callback;
  VOID                                    *Context;
  UINTN                                   PollingInterval;
  UINTN                                   DataLength;
} USB_BTHCI_CALLBACK_CONTEXT;

typedef struct {
  UINTN                         Signature;

  EFI_HANDLE                    ControllerHandle;
  EFI_EVENT                     DelayedRecoveryEvent;

  EFI_USB_IO_PROTOCOL           *UsbIo;
  EFI_USB_DEVICE_DESCRIPTOR     DeviceDescriptor;
  EFI_USB_CONFIG_DESCRIPTOR     ConfigurationDescriptor;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDescriptor;
  EFI_USB_ENDPOINT_DESCRIPTOR   InEndpointDescriptor;
  EFI_USB_ENDPOINT_DESCRIPTOR   OutEndpointDescriptor;
  EFI_USB_ENDPOINT_DESCRIPTOR   IntEndpointDescriptor;

  BTHCI_TYPE                    BtHciType;

  EFI_BLUETOOTH_HC_PROTOCOL     BluetoothHc;

  USB_BTHCI_CALLBACK_CONTEXT    EventCallbackContext;
  USB_BTHCI_CALLBACK_CONTEXT    AclCallbackContext;
  // ACL Event is NOT needed if USB protocol support AsyncBulk
  EFI_EVENT                     AclEvent;

  EFI_UNICODE_STRING_TABLE      *ControllerNameTable;

  //
  // Used for ACL buffer
  //
  UINTN                          MaxAclDataSize;
  UINT8                          *PendingAclData;
  UINTN                          PendingAclDataSize;
  UINTN                          RemainingAclDataSize;

} USB_BTHCI_DEV;

#define USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL(a) \
    CR(a, USB_BTHCI_DEV, BluetoothHc, USB_BTHCI_DEV_SIGNATURE)

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL   gUsbBtHciDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL   gUsbBtHciComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL  gUsbBtHciComponentName2;

//
// Functions of Driver Binding Protocol
//

/**
  Check whether USB BtHci driver supports this device.

  @param  This                   The USB BtHci driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Starts the BtHci device with this driver.

  This function consumes USB I/O Portocol, intializes USB BtHci device,
  installs Bluetooth HC Protocol.

  @param  This                  The USB BtHci driver binding instance.
  @param  Controller            Handle of device to bind driver to.
  @param  RemainingDevicePath   Optional parameter use to pick a specific child
                                device to start.

  @retval EFI_SUCCESS           This driver supports this device.
  @retval EFI_UNSUPPORTED       This driver does not support this device.
  @retval EFI_DEVICE_ERROR      This driver cannot be started due to device Error.
  @retval EFI_OUT_OF_RESOURCES  Can't allocate memory resources.
  @retval EFI_ALREADY_STARTED   This driver has been started.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Stop the USB BtHci device handled by this driver.

  @param  This                   The USB BtHci driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        Bluetooth HC Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  );

//
// EFI Component Name Functions
//

/**
  Retrieves a Unicode string that is the user readable name of the driver.

  This function retrieves the user readable name of a driver in the form of a
  Unicode string. If the driver specified by This has a user readable name in
  the language specified by Language, then a pointer to the driver name is
  returned in DriverName, and EFI_SUCCESS is returned. If the driver specified
  by This does not support the language specified by Language,
  then EFI_UNSUPPORTED is returned.

  @param  This                  A pointer to the EFI_COMPONENT_NAME2_PROTOCOL or
                                EFI_COMPONENT_NAME_PROTOCOL instance.
  @param  Language              A pointer to a Null-terminated ASCII string
                                array indicating the language. This is the
                                language of the driver name that the caller is
                                requesting, and it must match one of the
                                languages specified in SupportedLanguages. The
                                number of languages supported by a driver is up
                                to the driver writer. Language is specified
                                in RFC 4646 or ISO 639-2 language code format.
  @param  DriverName            A pointer to the Unicode string to return.
                                This Unicode string is the name of the
                                driver specified by This in the language
                                specified by Language.

  @retval EFI_SUCCESS           The Unicode string for the Driver specified by
                                This and the language specified by Language was
                                returned in DriverName.
  @retval EFI_INVALID_PARAMETER Language is NULL.
  @retval EFI_INVALID_PARAMETER DriverName is NULL.
  @retval EFI_UNSUPPORTED       The driver specified by This does not support
                                the language specified by Language.

**/
EFI_STATUS
EFIAPI
UsbBtHciComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  );

/**
  Retrieves a Unicode string that is the user readable name of the controller
  that is being managed by a driver.

  This function retrieves the user readable name of the controller specified by
  ControllerHandle and ChildHandle in the form of a Unicode string. If the
  driver specified by This has a user readable name in the language specified by
  Language, then a pointer to the controller name is returned in ControllerName,
  and EFI_SUCCESS is returned.  If the driver specified by This is not currently
  managing the controller specified by ControllerHandle and ChildHandle,
  then EFI_UNSUPPORTED is returned.  If the driver specified by This does not
  support the language specified by Language, then EFI_UNSUPPORTED is returned.

  @param  This                  A pointer to the EFI_COMPONENT_NAME2_PROTOCOL or
                                EFI_COMPONENT_NAME_PROTOCOL instance.
  @param  ControllerHandle      The handle of a controller that the driver
                                specified by This is managing.  This handle
                                specifies the controller whose name is to be
                                returned.
  @param  ChildHandle           The handle of the child controller to retrieve
                                the name of.  This is an optional parameter that
                                may be NULL.  It will be NULL for device
                                drivers.  It will also be NULL for a bus drivers
                                that wish to retrieve the name of the bus
                                controller.  It will not be NULL for a bus
                                driver that wishes to retrieve the name of a
                                child controller.
  @param  Language              A pointer to a Null-terminated ASCII string
                                array indicating the language.  This is the
                                language of the driver name that the caller is
                                requesting, and it must match one of the
                                languages specified in SupportedLanguages. The
                                number of languages supported by a driver is up
                                to the driver writer. Language is specified in
                                RFC 4646 or ISO 639-2 language code format.
  @param  ControllerName        A pointer to the Unicode string to return.
                                This Unicode string is the name of the
                                controller specified by ControllerHandle and
                                ChildHandle in the language specified by
                                Language from the point of view of the driver
                                specified by This.

  @retval EFI_SUCCESS           The Unicode string for the user readable name in
                                the language specified by Language for the
                                driver specified by This was returned in
                                DriverName.
  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.
  @retval EFI_INVALID_PARAMETER ChildHandle is not NULL and it is not a valid
                                EFI_HANDLE.
  @retval EFI_INVALID_PARAMETER Language is NULL.
  @retval EFI_INVALID_PARAMETER ControllerName is NULL.
  @retval EFI_UNSUPPORTED       The driver specified by This is not currently
                                managing the controller specified by
                                ControllerHandle and ChildHandle.
  @retval EFI_UNSUPPORTED       The driver specified by This does not support
                                the language specified by Language.

**/
EFI_STATUS
EFIAPI
UsbBtHciComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );

//
// Internal worker functions
//

/**
  Uses USB I/O to check whether the device is a USB BtHci device.

  @param  UsbIo    Pointer to a USB I/O protocol instance.

  @retval Not NULL Device is a USB BtHci device.
  @retval NULL     Device is a not USB BtHci device.

**/
USB_BTHCI_INFO *
IsUsbBtHci (
  IN  EFI_USB_IO_PROTOCOL     *UsbIo
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );


#endif

