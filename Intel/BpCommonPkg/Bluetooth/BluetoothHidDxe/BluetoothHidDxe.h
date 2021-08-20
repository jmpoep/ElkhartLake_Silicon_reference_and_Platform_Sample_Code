//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The header file of Bluetooth HID Driver.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _EFI_BLUETOOTH_HID_DXE_H_
#define _EFI_BLUETOOTH_HID_DXE_H_


#include <Uefi.h>

#include <Protocol/BluetoothAttribute.h>
#include <Protocol/DevicePath.h>
#include <Protocol/Hid.h>
#include <Protocol/ServiceBinding.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/HidLib.h>
#include <Library/BluetoothLib.h>

#include <IndustryStandard/Bluetooth.h>
#include <IndustryStandard/BluetoothHid.h>
#include <IndustryStandard/BluetoothAtt.h>
#include <IndustryStandard/BluetoothAssignedNumbers.h>

#define HID_SDP_CID_LOCAL       0x0040
#define HID_CONTROL_CID_LOCAL   0x0040
#define HID_INTERRUPT_CID_LOCAL 0x0041

#define HID_REPORT_TYPE_INPUT     0x01
#define HID_REPORT_TYPE_OUTPUT    0x02
#define HID_REPORT_TYPE_FEATURE   0x03

#define BT_HID_DEV_SIGNATURE SIGNATURE_32 ('b', 't', 'k', 'b')

#define BTHID_ACL_MESSAGE_SIGNATURE SIGNATURE_32 ('b', 'k', 'a', 's')

#define BT_HID_REPORT_INFO_SIGNATURE SIGNATURE_32 ('b', 'h', 'r', 'i')

#define EFI_BLUETOOTH_HID_DEVICE_PATH_GUID \
  { 0x7dd9f903, 0xf18e, 0x4a95, { 0x9a, 0x92, 0x55, 0x5b, 0x5e, 0x4b, 0x2c, 0x9e } }

#pragma pack(1)

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  EFI_GUID                        Guid;
} EFI_BLUETOOTH_HID_DEVICE_PATH;

#pragma pack()

typedef struct {
  UINT8                         Buffer[0xFFFF];
  UINTN                         TotalBufferSize;
  UINTN                         ReceivedBufferSize;
} BTHID_ACL_MESSAGE;

typedef struct _BTHID_ACL_MESSAGE_LIST {
  UINTN                         Signature;
  LIST_ENTRY                    Link;

  UINTN                         MessageID;

  BTHID_ACL_MESSAGE              Message;
} BTHID_ACL_MESSAGE_LIST;

///
/// Information about HID Report
///
typedef struct {
  UINTN                             Signature;
  LIST_ENTRY                        Link;
  UINT16                            ReportHandle;
  UINT16                            ReportReferDescHandle;
  UINT8                             ReportID;
  UINT8                             ReportType;
} HID_REPORT_INFO;

///
/// Device instance of BT HID
///
typedef struct {
  UINTN                             Signature;

  EFI_HANDLE                        ControllerHandle;
  EFI_HANDLE                        ParentHandle;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL  *BluetoothAttribute;

  EDKII_HID_PROTOCOL                Hid;

  EFI_EVENT                         TimerEvent;

  EFI_UNICODE_STRING_TABLE          *ControllerNameTable;

  //L2cap channel handle
  EFI_HANDLE                        L2capControlHandle;
  EFI_HANDLE                        L2capInterruptHandle;

  //GATT characteristic handle
  UINT16                            LEDReportHandle;
  UINT16                            ReportMapHandle;
  LIST_ENTRY                        HidReportInfo;

  EDKII_HID_SERVICE_CALLBACK        HidControlCallback;
  VOID                              *HidControlCallbackContext;
  EDKII_HID_SERVICE_CALLBACK        HidInterruptCallback;
  VOID                              *HidInterruptCallbackContext;

  UINT16                            ReportMapLen;
  UINT8                             *ReportMap;
  LIST_ENTRY                        ReportFormatList;
} BT_HID_DEV;

#define BT_HID_DEV_FROM_HID_PROTOCOL(a) \
    CR(a, BT_HID_DEV, Hid, BT_HID_DEV_SIGNATURE)

#define BT_HID_REPORT_INFO_FROM_LINK(a) \
    CR(a, HID_REPORT_INFO, Link, BT_HID_REPORT_INFO_SIGNATURE)

//
// HID Device Path definition
//
typedef struct {
  EFI_BLUETOOTH_HID_DEVICE_PATH        HidDevicePath;
  EFI_DEVICE_PATH_PROTOCOL             EndDevicePath;
} HID_DEVICE_PATH;

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL   gBluetoothHidDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL   gBluetoothHidComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL  gBluetoothHidComponentName2;

//
// Functions of Driver Binding Protocol
//

/**
  Check whether BT HID driver supports this device.

  @param  This                   The BT HID driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothHidDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Starts the BT HID device with this driver.

  This function consumes Bluetooth I/O Portocol, intializes BT HID device,
  installs Hid Protocol.

  @param  This                  The BT HID driver binding instance.
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
BluetoothHidDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Stop the BT HID device handled by this driver.

  @param  This                   The BT HID driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        Hid Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothHidDriverBindingStop (
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
BluetoothHidComponentNameGetDriverName (
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
BluetoothHidComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );

//
// Functions of HID Protocol
//

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
  IN EDKII_HID_PROTOCOL    *This,
  OUT EDKII_HID_INFO       *HidInfo
  );

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
  );

/**
  Stops the data transmission for a Bluetooth human interface device.

  @param[in]  This  A pointer to the EDKII_HID_PROTOCOL instance.

  @retval  EFI_UNSUPPORTED  The operation is not supported.

**/
EFI_STATUS
EFIAPI
BtHidStop (
  IN EDKII_HID_PROTOCOL            *This
  );

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
  );


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
  );

#endif

