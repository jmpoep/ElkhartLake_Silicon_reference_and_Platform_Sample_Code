//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The header file of Bluetooth Bus driver.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _EFI_BLUETOOTH_BUS_DXE_H_
#define _EFI_BLUETOOTH_BUS_DXE_H_

#include <Uefi.h>
#include <Protocol/BluetoothHc.h>
#include <Protocol/BluetoothAttribute.h>
#include <Protocol/BluetoothConfig.h>
#include <Protocol/BluetoothLeConfig.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/DevicePath.h>
#include <IndustryStandard/Bluetooth.h>
#include <IndustryStandard/BluetoothHci.h>
#include <IndustryStandard/BluetoothAtt.h>
#include <IndustryStandard/BluetoothAssignedNumbers.h>
#include <Guid/FileInfo.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/UsbIo.h>
#include "BluetoothLeConfigX.h"

typedef struct _BTHC_DEV BTHC_DEV;
typedef struct _BT_SB_DEV BT_SB_DEV;
typedef struct _BT_LE_SB_DEV BT_LE_SB_DEV;
typedef struct _BT_DEV_INFO BT_DEV_INFO;
typedef struct _BT_LE_DEV_INFO BT_LE_DEV_INFO;

#define BLUETOOTH_LE_ADV_DATA_MAX_SIZE                       62

#define BT_HCI_INTERRUPT_TIMER_INTERVAL  10
#define BT_ACL_INTERRUPT_TIMER_INTERVAL  10
#define BT_LE_DEV_INFO_SIGNATURE SIGNATURE_32 ('b', 'l', 'i', 'f')

typedef struct _BT_LE_DEV_INFO {
  UINTN                         Signature;
  LIST_ENTRY                    Link;

  // TODO: Use EFI_BLUETOOTH_LE_DEVICE_INFO here?
  BLUETOOTH_LE_ADDRESS          BDAddr;
  BLUETOOTH_LE_ADDRESS          Direct_BD_ADDR;
  BLUETOOTH_LE_ADDRESS          IDAddr;
  INT8                          RSSI;
  UINTN                         AdvertisementDataSize;
  VOID                          *AdvertisementData;
} BT_LE_DEV_INFO;

#define BT_LE_PAIRED_DEV_INFO_SIGNATURE SIGNATURE_32 ('b', 'l', 'p', 'd')

typedef struct {
  UINTN                         Signature;
  LIST_ENTRY                    Link;
  BLUETOOTH_LE_ADDRESS          BDAddr;
  BLUETOOTH_LE_ADDRESS          IDAddr;
} BT_LE_PAIRED_DEV_INFO;

#define BT_LE_DEV_SIGNATURE SIGNATURE_32 ('b', 't', 'l', 'e')

typedef struct _BT_LE_DEV {
  UINT32                           Signature;
  LIST_ENTRY                       Link;
  EFI_HANDLE                       Handle;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL BluetoothAtt;
  BT_LE_SB_DEV                     *BtLeSbDev;
  BOOLEAN                          InDestroy;
} BT_LE_DEV;

#define BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL(a) \
    CR(a, BT_LE_DEV, BluetoothAtt, BT_LE_DEV_SIGNATURE)

#define BTHC_DEV_SIGNATURE SIGNATURE_32 ('b', 't', 'l', 'l')

typedef struct _BTHC_DEV {
  UINTN                                             Signature;

  EFI_HANDLE                                        ControllerHandle;
  EFI_HANDLE                                        DriverBindingHandle;
  EFI_DEVICE_PATH_PROTOCOL                          *DevicePath;

  EFI_BLUETOOTH_HC_PROTOCOL                         *BluetoothHc;

  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                  BluetoothLeConfig;

  EFI_UNICODE_STRING_TABLE                          *ControllerNameTable;

  LIST_ENTRY                                        BtLeDevInfoList;
  LIST_ENTRY                                        BtLeSbList;
  LIST_ENTRY                                        BtLePairedList;
  LIST_ENTRY                                        LeDuplicateBDAddrList;

  BOOLEAN                                           LeScanned;

  VOID                                              *LeScanCallBackFuncContext;
  EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION    LeScanCallBackFunc;

  VOID                                              *LeConnCompCallBackContext;
  EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK LeConnCompCallBack;

  VOID                                              *LeSmpCallBackContext;
  EFI_BLUETOOTH_LE_SMP_CALLBACK                     LeSmpCallBack;

  VOID                                              *LeSmpGetDataCallBackContext;
  EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK     LeSmpGetDataCallBack;

  VOID                                              *LeSmpSetDataCallBackContext;
  EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK     LeSmpSetDataCallBack;

} BTHC_DEV;

#define BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(a) \
    CR(a, BTHC_DEV, BluetoothLeConfig, BTHC_DEV_SIGNATURE)

#define BT_LE_SB_DEV_SIGNATURE SIGNATURE_32 ('b', 'l', 's', 'b')

#define BT_LE_PER_DEV_ATTR          300
#define ATT_MAX_VALUE_LEN           512

typedef struct _BT_LE_SB_DEV {
  UINTN                         Signature;
  LIST_ENTRY                    Link;

  EFI_HANDLE                    DeviceHandle;
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;
  EFI_SERVICE_BINDING_PROTOCOL  ServiceBinding;
  LIST_ENTRY                    ChildrenList;
  UINTN                         ChildrenNumber;

  BT_LE_DEV_INFO                *BtLeDevInfo;

  // Parent
  BTHC_DEV                      *BtHcDev;

  BOOLEAN                       Initialized;
  UINT8                         ConnectionId;
  EFI_BLUETOOTH_ATTRIBUTE_HEADER* AttrDatabase[BT_LE_PER_DEV_ATTR];

} BT_LE_SB_DEV;

#define BT_LE_SB_DEV_FROM_BLUETOOTH_SB_PROTOCOL(a) \
    CR(a, BT_LE_SB_DEV, ServiceBinding, BT_LE_SB_DEV_SIGNATURE)

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL   gBluetoothBusDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL   gBluetoothBusComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL  gBluetoothBusComponentName2;

//
// Functions of Driver Binding Protocol
//

/**
  Check whether BluetoothBus driver supports this device.

  @param  This                   The BluetoothBus driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothBusDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Starts the BluetoothHc device with this driver.

  This function consumes BluetoothHc Portocol, intializes BluetoothHc device,
  installs BluetoothLeConfig Protocol.

  @param  This                  The BluetoothHc driver binding instance.
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
BluetoothBusDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Stop the BluetoothHc device handled by this driver.

  @param  This                   The BluetoothBus driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        BluetoothLeConfig Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothBusDriverBindingStop (
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
BluetoothBusComponentNameGetDriverName (
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
BluetoothBusComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );

/**
  Initialize BluetoothLE host controller and local device.

  The Init() function initializes BluetoothLE host controller and local device.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.

  @retval EFI_SUCCESS           The BluetoothLE host controller and local device is initialized successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to initialize the BluetoothLE host controller
                                and local device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigInit (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This
  );

/**
  Scan BluetoothLE device.

  The Scan() function scans BluetoothLE device. When this function is returned, it just means scan
  request is submitted. It does not mean scan process is started or finished. Whenever there is a
  BluetoothLE device is found, the Callback function will be called. Callback function might be
  called before this function returns or after this function returns

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  ReScan            If TRUE, a new scan request is submitted no matter there is scan result before.
                                If FALSE and there is scan result, the previous scan result is returned and no scan request
                                is submitted.
  @param[in]  Timeout           Duration in milliseconds for which to scan.
  @param[in]  ScanParameter     If it is not NULL, the ScanParameter is used to perform a scan by the BluetoothLE bus driver.
                                If it is NULL, the default parameter is used.
  @param[in]  Callback          The callback function. This function is called if a BluetoothLE device is found during
                                scan process.
  @param[in]  Context           Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The Bluetooth scan request is submitted.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to scan the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigScan (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL               *This,
  IN BOOLEAN                                        ReScan,
  IN UINT32                                         Timeout,
  IN EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER         *ScanParameter, OPTIONAL
  IN EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION Callback,
  IN VOID                                           *Context
  );

/**
  Connect a BluetoothLE device.

  The Connect() function connects a Bluetooth device. When this function is returned successfully,
  a new EFI_BLUETOOTH_IO_PROTOCOL is created.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  AutoReconnect     If TRUE, the BluetoothLE host controller needs to do an auto
                                reconnect. If FALSE, the BluetoothLE host controller does not do
                                an auto reconnect.
  @param[in]  DoBonding         If TRUE, the BluetoothLE host controller needs to do a bonding.
                                If FALSE, the BluetoothLE host controller does not do a bonding.
  @param[in]  ConnectParameter  If it is not NULL, the ConnectParameter is used to perform a
                                scan by the BluetoothLE bus driver. If it is NULL, the default
                                parameter is used.
  @param[in]  BD_ADDR           The address of the BluetoothLE device to be connected.

  @retval EFI_SUCCESS           The BluetoothLE device is connected successfully.
  @retval EFI_ALREADY_STARTED   The BluetoothLE device is already connected.
  @retval EFI_NOT_FOUND         The BluetoothLE device is not found.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to connect the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigConnect (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL            *This,
  IN  BOOLEAN                                     AutoReconnect,
  IN  BOOLEAN                                     DoBonding,
  IN  EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER   *ConnectParameter, OPTIONAL
  IN  BLUETOOTH_LE_ADDRESS                        *BD_ADDR
  );

/**
  Disconnect a BluetoothLE device.

  The Disconnect() function disconnects a BluetoothLE device. When this function is returned
  successfully, the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL associated with this device is
  destroyed and all services associated are stopped.

  @param[in]  This          Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  BD_ADDR       The address of BluetoothLE device to be connected.
  @param[in]  Reason        Bluetooth disconnect reason. See Bluetooth specification for detail.

  @retval EFI_SUCCESS           The BluetoothLE device is disconnected successfully.
  @retval EFI_NOT_STARTED       The BluetoothLE device is not connected.
  @retval EFI_NOT_FOUND         The BluetoothLE device is not found.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to disconnect the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigDisconnect (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
  IN BLUETOOTH_LE_ADDRESS              *BD_ADDR,
  IN UINT8                          Reason
  );

/**
  Get BluetoothLE configuration data.

  The GetData() function returns BluetoothLE configuration data. For remote BluetoothLE device
  configuration data, please use GetRemoteData() function with valid BD_ADDR.

  @param[in]       This         Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]       DataType     Configuration data type.
  @param[in, out]  DataSize     On input, indicates the size, in bytes, of the data buffer specified by Data.
                                On output, indicates the amount of data actually returned.
  @param[in, out]  Data         A pointer to the buffer of data that will be returned.

  @retval EFI_SUCCESS           The BluetoothLE configuration data is returned successfully.
  @retval EFI_INVALID_PARAMETER One or more of the following conditions is TRUE:
                                - DataSize is NULL.
                                - *DataSize is 0.
                                - Data is NULL.
  @retval EFI_UNSUPPORTED       The DataType is unsupported.
  @retval EFI_NOT_FOUND         The DataType is not found.
  @retval EFI_BUFFER_TOO_SMALL  The buffer is too small to hold the buffer.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigGetData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE      DataType,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  );

/**
  Get remove BluetoothLE device configuration data.

  The GetRemoteData() function returns remote BluetoothLE device configuration data.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  DataType          Configuration data type.
  @param[in]  BDAddr            Remote BluetoothLE device address.
  @param[in, out] DataSize      On input, indicates the size, in bytes, of the data buffer specified by Data.
                                On output, indicates the amount of data actually returned.
  @param[in, out] Data          A pointer to the buffer of data that will be returned.

  @retval EFI_SUCCESS           The remote BluetoothLE device configuration data is returned successfully.
  @retval EFI_INVALID_PARAMETER One or more of the following conditions is TRUE:
                                - DataSize is NULL.
                                - *DataSize is 0.
                                - Data is NULL.
  @retval EFI_UNSUPPORTED       The DataType is unsupported.
  @retval EFI_NOT_FOUND         The DataType is not found.
  @retval EFI_BUFFER_TOO_SMALL  The buffer is too small to hold the buffer.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigGetRemoteData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE         DataType,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN OUT UINTN                              *DataSize,
  IN OUT VOID                               *Data OPTIONAL
  );

/**
  Set BluetoothLE configuration data.

  The SetData() function sets local BluetoothLE device configuration data. Not all DataType can be
  set.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  DataType          Configuration data type.
  @param[in]  DataSize          Indicates the size, in bytes, of the data buffer specified by Data.
  @param[in]  Data              A pointer to the buffer of data that will be set.

  @retval EFI_SUCCESS           The BluetoothLE configuration data is set successfully.
  @retval EFI_INVALID_PARAMETER One or more of the following conditions is TRUE:
                                - DataSize is 0.
                                - Data is NULL.
  @retval EFI_UNSUPPORTED       The DataType is unsupported.
  @retval EFI_WRITE_PROTECTED   Cannot set configuration data.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigSetData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE         DataType,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  );

/**
  Send user authentication/authorization to remote device.

  The SendSmpAuthData() function sends user authentication/authorization to remote device. It
  should be used to send these information after the caller gets the request data from the callback
  function by RegisterSmpAuthCallback().

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  BDAddr          Remote BluetoothLE device address.
  @param[in]  EventDataType   Event data type in EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE.
  @param[in]  DataSize        The size of Data in bytes, of the data buffer specified by Data.
  @param[in]  Data            A pointer to the buffer of data that will be sent. The data format
                              depends on the type of SMP event data being responded to.

  @retval EFI_SUCCESS         The SMP authorization data is sent successfully.
  @retval EFI_NOT_READY       SMP is not in the correct state to receive the auth data.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigSendSmpAuthData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE   EventDataType,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  );

/**
  Register link connect complete callback function.

  The RegisterLinkConnectCompleteCallback() function registers Bluetooth link connect
  complete callback function. The Bluetooth Configuration driver may call
  RegisterLinkConnectCompleteCallback() to register a callback function. During pairing,
  Bluetooth bus driver must trigger this callback function to report device state, if it is registered.
  Then Bluetooth Configuration driver will get information on device connection, according to
  CallbackType defined by EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  Callback        The callback function. NULL means unregister.
  @param[in]  Context         Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS         The link connect complete callback function is registered successfully.
  @retval EFI_ALREADY_STARTED A callback function is already registered on the same attribute
                              opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED     A callback function is not registered on the same attribute opcode
                              and attribute handle, when the Callback is NULL
**/
EFI_STATUS
EFIAPI
BluetoothLeConfigRegisterConnectCompleteCallBack (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                                        *This,
  IN EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK                    Callback, // NULL means unregister
  IN VOID                                                                 *Context
  );

/**
  Register Security Manager Protocol callback function for user authentication/authorization.

  The RegisterSmpAuthCallback() function register Security Manager Protocol callback
  function for user authentication/authorization.

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  Callback        Callback function for user authentication/authorization.
  @param[in]  Context         Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS         The SMP callback function is registered successfully.
  @retval EFI_ALREADY_STARTED A callback function is already registered on the same attribute
                              opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED     A callback function is not registered on the same attribute opcode
                              and attribute handle, when the Callback is NULL.

**/
EFI_STATUS
EFIAPI
BluetoothLeRegisterSmpAuthCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
  IN EFI_BLUETOOTH_LE_SMP_CALLBACK     Callback,
  IN VOID                              *Context
  );

/**
  Register a callback function to get SMP related data.

  The RegisterSmpGetDataCallback() function registers a callback function to get SMP related data.

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  Callback        Callback function for SMP get data.
  @param[in]  Context         Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS         The SMP get data callback function is registered successfully.
  @retval EFI_ALREADY_STARTED A callback function is already registered on the same attribute
                              opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED     A callback function is not registered on the same attribute opcode
                              and attribute handle, when the Callback is NULL
**/
EFI_STATUS
EFIAPI
BluetoothLeConfigRegisterSmpGetDataCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                                        *This,
  IN EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK                    Callback, // NULL means unregister
  IN VOID                                                                 *Context
  );

/**
  Register a callback function to set SMP related data.

  The RegisterSmpSetDataCallback() function registers a callback function to set SMP related data.

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  Callback        Callback function for SMP set data.
  @param[in]  Context         Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS         The SMP set data callback function is registered successfully.
  @retval EFI_ALREADY_STARTED A callback function is already registered on the same attribute
                              opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED     A callback function is not registered on the same attribute opcode
                              and attribute handle, when the Callback is NULL
**/
EFI_STATUS
EFIAPI
BluetoothLeConfigRegisterSmpSetDataCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                                        *This,
  IN EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK                    Callback, // NULL means unregister
  IN VOID                                                                 *Context
  );

/**
  Creates a BluetoothLE Service Binding device.

  @param[in]  BtHcDev      A pointer to the BTHC_DEV structure.
  @param[in]  BtLeDevInfo  A pointer to the BT_LE_DEV_INFO structure, which
                           contains the BluetoothLE device information.

  @retval  A pointer to the BT_LE_SB_DEV structure or NULL if memory allocation
           fails.

**/
BT_LE_SB_DEV*
BtCreateLeSbDev (
  IN BTHC_DEV                   *BtHcDev,
  IN BT_LE_DEV_INFO             *BtLeDevInfo
  );

/**
  Initializes the given BluetoothLE Service Binding device.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         initialize.

  @retval  EFI_SUCCESS  The initialization succeeds.
  @retval  Others       The initialization fails.

**/
EFI_STATUS
BtInitLeSbDev (
  IN  BTHC_DEV        *BtHcDev,
  IN  BT_LE_SB_DEV    *BtLeSbDev
  );

/**
  Removes a given BluetoothLE Service Binding device to the BluetoothLE Service
  Binding device list.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         remove from the list.

  @retval  FALSE  The specified BluetoothLE Service Binding device has not been
                  removed from the list.
  @retval  TRUE   The specified BluetoothLE Service Binding device has been
                  removed from the list.

**/
BOOLEAN
BtDelLeSb (
  IN BTHC_DEV                     *BtHcDev,
  IN BT_LE_SB_DEV                 *BtLeSbDev
  );

/**
  Adds a given BluetoothLE Service Binding device to the BluetoothLE Service
  Binding device list.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         add into the list.

  @retval  TRUE  This function always return TRUE.

**/
BOOLEAN
BtAddLeSb (
  IN BTHC_DEV                     *BtHcDev,
  IN BT_LE_SB_DEV                 *BtLeSbDev
  );

/**
  Adds a BluetoothLE device into the paired device list.

  @param[in]  BtHcDev      A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr       A pointer to a Bluetooth device address.
  @param[in]  IDAddr       A pointer to a device identity address.
  @param[in]  BluetoothHc  A pointer to a EFI_BLUETOOTH_HC_PROTOCOL instance.

  @retval  EFI_SUCCESS  This function always returns EFI_SUCCESS.

**/
EFI_STATUS
BtAddLePairedDev (
  IN BTHC_DEV                   *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS       *BDAddr,
  IN BLUETOOTH_LE_ADDRESS       *IDAddr,
  IN EFI_BLUETOOTH_HC_PROTOCOL  *BluetoothHc
  );

/**
  Removes all the nodes in a doubly-linked list.

  The list is specified by the head node and the corresponding signature of the
  list.

  @param[in]  Link       The pointer to the head node of a doubly-linked list.
  @param[in]  Signature  The signature for the doubly-linked list.

  @retval TRUE  The function always returns TRUE.

**/
BOOLEAN
BtClearList (
  IN LIST_ENTRY                  *Link,
  IN UINTN                       Signature
  );

/**
  Updates the device information of a BluetoothLE device.

  @param[in]  BtHcDev                A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr                 A pointer to a Bluetooth device address.
  @param[in]  IDAddr                 A pointer to a device identity address.
  @param[in]  Direct_BD_ADDR         A pointer to a direct Bluetooth device
                                     address.
  @param[in]  RSSI                   The Bluetooth RSSI.
  @param[in]  TxPower                The transmitted power level of the packet
                                     containing the data type.
  @param[in]  Appearance             The external appearance of the device.
  @param[in]  RoleSupported          The LE role capabilities of the device.
  @param[in]  LocalReadableName      The local name assigned to the device.
  @param[in]  AdvertisementData      A pointer to the BluetoothLE advertisement
                                     data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.
  @param[in]  NeedAdd                Add the BluetoothLE device to the device
                                     information list or not.

  @retval  TRUE   Device information of the specific BluetoothLE device has
                  been updated successfully.
  @retval  FALSE  Device information of the specific BluetoothLE device has not
                  been updated.

**/
BOOLEAN
BtLeUpdateDevice (
  IN BTHC_DEV                      *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS          *BDAddr,
  IN BLUETOOTH_LE_ADDRESS          *IDAddr,
  IN BLUETOOTH_LE_ADDRESS          *Direct_BD_ADDR,
  IN INT8                          RSSI,
  IN UINT8                         TxPower,
  IN UINT16                        Appearance,
  IN UINT8                         RoleSupported,
  IN UINT8                         *LocalReadableName,
  IN UINT8                         *AdvertisementData,
  IN UINT8                         AdvertisementDataSize, OPTIONAL
  IN BOOLEAN                       NeedAdd
  );

/**
  Creates a new device path by appending a Bluetooth device node to a given
  base device path.

  @param[in,out]  DevPtr      A pointer to the generated device path if
                              EFI_SUCCESS is returned. Or NULL if
                              EFI_OUT_OF_RESOURCES is returned.
  @param[in]      BaseDevPtr  A pointer to a device path data structure.
  @param[in]      BDAddr      A pointer to a Bluetooth device address.

  @retval  EFI_SUCCESS           The new device path is created.
  @retval  EFI_OUT_OF_RESOURCES  The creation of the new device path fails due
                                 to memory allocation failure.

**/
EFI_STATUS
BtAppendBtLeDevPath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL **DevPtr,
  IN EFI_DEVICE_PATH_PROTOCOL     *BaseDevPtr,
  IN BLUETOOTH_LE_ADDRESS         *BDAddr
  );

/**
  Gets the device information of a BluetoothLE device specified by the
  Bluetooth device address.

  @param[in]  BtHcDev  A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr   A pointer to a Bluetooth device address.

  @retval  A pointer to the BT_LE_DEV_INFO structure which contains the device
           information for the specified BluetoothLE device.
  @retval  NULL  If a BluetoothLE device with address specified by 'BDAddr'
           cannot be found.

**/
BT_LE_DEV_INFO *
BtLeFindDeviceInfo (
  IN BTHC_DEV                     *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS         *BDAddr
  );

/**
  Finds a paired BluetoothLE device with given Bluetooth device address.

  @param[in]  BtHcDev  A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr   A pointer to a Bluetooth device address to search.

  @retval  A pointer to the BT_LE_PAIRED_DEV_INFO structure, if the given
           Bluetooth device address matches a device in the BluetoothLE paired
           device list.
  @retval  NULL, if the given Bluetooth device address does not match any
           device in the BluetoothLE paired device list.

**/
BT_LE_PAIRED_DEV_INFO*
BtFindLePairedDevByBDAddr(
  IN BTHC_DEV                     *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS         *BDAddr
  );

/**
  Finds a BluetoothLE Service Binding device with given Bluetooth device
  address.

  @param[in]  BtHcDev  A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr   A pointer to a Bluetooth device address to search.

  @retval  A pointer to the BT_LE_SB_DEV structure, if the given Bluetooth
           device address matches a device in the BluetoothLE Service Binding
           device list.
  @retval  NULL, if the given Bluetooth device address does not match any
           device in the BluetoothLE Service Binding device list.

**/
BT_LE_SB_DEV*
BtFindLeSbDevByBDaddr(
  IN BTHC_DEV                   *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS       *BDAddr
  );

/**
  Creates a child handle and installs a protocol.

  The CreateChild() function installs a protocol on ChildHandle.
  If ChildHandle is a pointer to NULL, then a new handle is created and
  returned in ChildHandle.
  If ChildHandle is not a pointer to NULL, then the protocol installs on the
  existing ChildHandle.

  @param[in]      This         Pointer to the EFI_SERVICE_BINDING_PROTOCOL
                               instance.
  @param[in,out]  ChildHandle  Pointer to the handle of the child to create.
                               If it is a pointer to NULL, then a new handle is
                               created.
                               If it is a pointer to an existing UEFI handle,
                               then the protocol is added to the existing UEFI
                               handle.

  @retval  EFI_SUCCESS            The protocol was added to ChildHandle.
  @retval  EFI_INVALID_PARAMETER  ChildHandle is NULL.

**/
EFI_STATUS
EFIAPI
BluetoothLeServiceBindingCreateChild (
  IN     EFI_SERVICE_BINDING_PROTOCOL    *This,
  IN OUT EFI_HANDLE                      *ChildHandle
  );

/**
  Destroys a child handle with a protocol installed on it.

  The DestroyChild() function does the opposite of CreateChild(). It removes a
  protocol that was installed by CreateChild() from ChildHandle. If the removed
  protocol is the last protocol on ChildHandle, then ChildHandle is destroyed.

  @param[in]  This         Pointer to the EFI_SERVICE_BINDING_PROTOCOL
                           instance.
  @param[in]  ChildHandle  Handle of the child to destroy.

  @retval  EFI_SUCCESS            The protocol was removed from ChildHandle.
  @retval  EFI_UNSUPPORTED        ChildHandle does not support the protocol
                                  that is being removed.
  @retval  EFI_INVALID_PARAMETER  Child handle is NULL.
  @retval  EFI_ACCESS_DENIED      The protocol could not be removed from the
                                  ChildHandle because its services are being
                                  used.
  @retval  other                  The child handle was not destroyed.

**/
EFI_STATUS
EFIAPI
BluetoothLeServiceBindingDestroyChild (
  IN EFI_SERVICE_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                      ChildHandle
  );

/******************** LE functions ********************/

/**
  Get Bluetooth device information.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[out] DeviceInfoSize    A pointer to the size, in bytes, of the DeviceInfo buffer.
  @param[out] DeviceInfo        A pointer to a callee allocated buffer that returns Bluetooth
                                device information. Callee allocates this buffer by using EFI Boot
                                Service AllocatePool(). If this device is Bluetooth classic
                                device, EFI_BLUETOOTH_DEVICE_INFO should be used. If
                                this device is Bluetooth LE device, EFI_BLUETOOTH_LE_DEVICE_INFO
                                should be used.

  @retval EFI_SUCCESS           The Bluetooth device information is returned successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the Bluetooth device
                                information

**/
EFI_STATUS
EFIAPI
BluetoothAttributeGetDeviceInfo (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL  *This,
  OUT UINTN                             *DeviceInfoSize,
  OUT VOID                              **DeviceInfo
  );

/**
  Get Bluetooth discovered service information.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[out] ServiceInfoSize   A pointer to the size, in bytes, of the ServiceInfo buffer.
  @param[out] ServiceInfo       A pointer to a callee allocated buffer that returns Bluetooth
                                discovered service information. Callee allocates this buffer by
                                using EFI Boot Service AllocatePool().

  @retval EFI_SUCCESS           The Bluetooth discovered service information is returned successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the Bluetooth discovered
                                service information.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeGetServiceInfo (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL      *This,
  OUT UINTN                                *ServiceInfoSize,
  OUT VOID                                 **ServiceInfo
  );

/**
  Send a "REQUEST" or "COMMAND" message to remote server and receive a "RESPONSE" message
  for "REQUEST" from remote server according to Bluetooth attribute protocol data unit(PDU).

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[in]  Data              Data of a REQUEST or COMMAND message. The first byte is the attribute PDU
                                related opcode, followed by opcode specific fields. See Bluetooth specification,
                                Vol 3, Part F, Attribute Protocol.
  @param[in]  DataLength        The length of Data in bytes.
  @param[in]  Callback          Callback function to notify the RESPONSE is received to the caller, with the
                                response buffer. Caller must check the response buffer content to know if the
                                request action is success or fail. It may be NULL if the data is a COMMAND.
  @param[in]  Context           Data passed into Callback function. It is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The request is sent successfully.
  @retval EFI_INVALID_PARAMETER One or more parameters are invalid due to following conditions:
                                - The Buffer is NULL.
                                - The BufferLength is 0.
                                - The opcode in Buffer is not a valid OPCODE according to Bluetooth specification.
                                - The Callback is NULL.
  @retval EFI_DEVICE_ERROR      Sending the request failed due to the host controller or the device error.
  @retval EFI_NOT_READY         A GATT operation is already underway for this device.
  @retval EFI_UNSUPPORTED       The attribute does not support the corresponding operation.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeSendRequest (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL            *This,
  IN VOID                                        *Data,
  IN UINTN                                       DataLength,
  IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION   Callback,
  IN VOID                                        *Context
  );

/**
  Register or unregister a server initiated message, such as NOTIFICATION or INDICATION, on a
  characteristic value on remote server.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[in]  CallbackParameter The parameter of the callback.
  @param[in]  Callback          Callback function for server initiated attribute protocol. NULL callback
                                function means unregister the server initiated callback.
  @param[in]  Context           Data passed into Callback function. It is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The callback function is registered or unregistered successfully
  @retval EFI_INVALID_PARAMETER The attribute opcode is not server initiated message opcode. See
                                Bluetooth specification, Vol 3, Part F, Attribute Protocol.
  @retval EFI_ALREADY_STARTED   A callback function is already registered on the same attribute
                                opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED       A callback function is not registered on the same attribute opcode
                                and attribute handle, when the Callback is NULL.
  @retval EFI_NOT_READY         A GATT operation is already underway for this device.
  @retval EFI_UNSUPPORTED       The attribute does not support notification.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeRegisterForServerNotification (
  IN  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL           *This,
  IN  EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER *CallbackParameter,
  IN  EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION  Callback,
  IN  VOID                                       *Context
  );

/******************** HCI helpers to update structures ********************/

extern EFI_SERVICE_BINDING_PROTOCOL     mBluetoothLeServiceBinding;
extern EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL mBluetoothAttribute;

#endif
