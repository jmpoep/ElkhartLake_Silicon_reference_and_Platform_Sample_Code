//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The header file of Bluetooth LE Connection Manager.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#ifndef __BLUETOOTH_CONFIG_DXE_H__
#define __BLUETOOTH_CONFIG_DXE_H__

#include <Uefi.h>
#include <IndustryStandard/Bluetooth.h>
#include <IndustryStandard/BluetoothHci.h>
#include <IndustryStandard/BluetoothAssignedNumbers.h>

#include <Guid/MdeModuleHii.h>

#include <Protocol/BluetoothLeConfig.h>
#include <Protocol/SerialIo.h>
#include <Protocol/HiiPackageList.h>
#include <Protocol/HiiConfigAccess.h>

#include <Library/DevicePathLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiHiiServicesLib.h>
#include <Library/HiiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/BluetoothLib.h>

#include <Library/MemoryAllocationLib.h>

#include "BluetoothLeConfigX.h"
#include "BluetoothConnectionManagerVfr.h"
#include "BluetoothConnectionManagerHii.h"

#pragma pack(1)
///
/// HII specific Vendor Device Path definition.
///
typedef struct {
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} HII_VENDOR_DEVICE_PATH;

#define MAX_DEVICE_NAME_LEN    248
#define BT_REMOTE_DEVICE_SIGNATURE  SIGNATURE_32 ('B', 'T', 'S', 'G')

typedef struct {
  UINTN                       Signature;
  LIST_ENTRY                  Link;
  UINT8                       LocalName[MAX_DEVICE_NAME_LEN];
  INT8                        RSSI;
  UINT8                       RemoteDeviceState;
  UINT16                      Appearance;
  BLUETOOTH_LE_ADDRESS        AdvAddr;        // Save Advertisememt Address here.
  BLUETOOTH_LE_ADDRESS        IDAddr;        // Save Identify Address here.
} BT_REMOTE_DEVICE_ATTRIBUTE;


#define BT_REMOTE_DEVICE_FROM_LINK(a)  CR (a, BT_REMOTE_DEVICE_ATTRIBUTE, Link, BT_REMOTE_DEVICE_SIGNATURE)
#define BT_DEFAULT_NAME "UEFI Bluetooth"

#define  EFI_BLUETOOTH_LE_MAX_BONDED_DEV    3

typedef struct {
  UINT8                KeyIrk[16];
  BLUETOOTH_LE_ADDRESS RemoteIDAddr[EFI_BLUETOOTH_LE_MAX_BONDED_DEV];    // Save Identify Address here.
  UINT8                LocalName[MAX_DEVICE_NAME_LEN];
} BT_LE_LOCAL_DEV_STORAGE;

typedef struct {
  UINT8  KeysDistributed;
  UINT8  KeySize;
  UINT8  AuthReq;
  UINT8  PeerLtk[16];
  UINT8  PeerIrk[16];
  UINT8  PeerCsrk[16];
  UINT8  PeerRand[8];
  UINT16 PeerEdiv;
  UINT32 PeerSignCounter;
  UINT8  LocalLtk[16];
  UINT8  LocalIrk[16];
  UINT8  LocalCsrk[16];
  UINT32 LocalSignCounter;
  UINT8  PeerName[MAX_DEVICE_NAME_LEN];
} BT_LE_REMOTE_DEV_STORAGE;

#pragma pack()

#define   MAX_UI_DEVICE_NAME_FIELD           45
#define   MAX_STRING_LEN                     200
//
// Character definitions
//
#define UPPER_LOWER_CASE_OFFSET 0x20

#define MAX_PASSKEY_SIZE        0x6

//
//
// Time definitions
//
#define ONE_SECOND  10000000

///
/// BLUETOOTH_CONFIG_STATE.
///
typedef enum {
  StateIdle,
  StateConnecting,
  StateDisconnecting
} BLUETOOTH_CONNECT_STATE;

///
/// EFI_BLUETOOTH_ERROR_TYPE.
///
typedef enum {
  ResultConnectFail,
  ResultDisconnectFail,
  ResultExceedMaxPairedDevices,
  ResultErrorMax
} EFI_BLUETOOTH_ERROR_TYPE;

///
/// EFI_BLUETOOTH_ADDRESS_TYPE.
///
typedef enum {
  EfiIdentifyAddressType,
  EfiAdvertisementAddressType,
  EfiAnyAddressType,
  EfiInvalidAddressType
} EFI_BLUETOOTH_ADDRESS_TYPE;

#define LE_BD_ADDR_STR_LEN    24
#define LE_BDADDR_TO_STRING(str, addr, type) {register int ijk; for (ijk = 0; ijk < 6; ijk++) UnicodeSPrint(&str[ijk*3], (LE_BD_ADDR_STR_LEN - ijk*3), L"%02x:", addr[ijk]); UnicodeSPrint(&str[ijk*3], (LE_BD_ADDR_STR_LEN - ijk*3), L"%02x", type); str[ijk*3 + 3] = '\0'; }

#define BTCONFIG_DEV_SIGNATURE SIGNATURE_32 ('b', 't', 'c', 's')

typedef struct _BT_CONFIG_DEV {
  UINTN                               Signature;

  EFI_HANDLE                          ControllerHandle;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *BluetoothLeConfig;
  EFI_UNICODE_STRING_TABLE            *ControllerNameTable;
  EFI_HII_CONFIG_ACCESS_PROTOCOL      ConfigAccess;
  EFI_HII_HANDLE                      HiiHandle;

  EFI_EVENT                           PasskeyInputEvent;
  EFI_EVENT                           RefreshRemoteDevEvent;
  EFI_EVENT                           ConnectDriverEvent;

  EFI_LOCK                            DeviceListLock;

  UINTN                               PairedDevCount;
  BOOLEAN                             PairedDevDataSaved[EFI_BLUETOOTH_LE_MAX_BONDED_DEV];
  BT_LE_REMOTE_DEV_STORAGE            PairedDevData[EFI_BLUETOOTH_LE_MAX_BONDED_DEV];
  BT_LE_LOCAL_DEV_STORAGE             ControllerData;

  LIST_ENTRY                          RemoteDeviceList;
  BT_REMOTE_DEVICE_ATTRIBUTE          *CurrentBondingDev;
  BOOLEAN                             CurrentBondingIDAddress; // FALSE indicate to use ADV address in CurrentBondingDev;

  BOOLEAN                             FinishHostInit;
  BOOLEAN                             UpdateScanMenu;
  BOOLEAN                             FoundNewDevice;

  volatile BLUETOOTH_CONNECT_STATE    ConnectState;
  volatile BOOLEAN                    InScanning;
} BT_CONFIG_DEV;

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL   gBluetoothConfigDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL   gBluetoothConfigComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL  gBluetoothConfigComponentName2;
extern BT_CONFIG_DEV                 *mBtConfigDevice;

/**
  Check whether HID KB driver supports this device.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Starts the HID KB device with this driver.

  This function consumes Hid I/O Portocol, intializes HID KB device,
  installs SimpleTextIn Protocol.

  @param  This                  The HID KB driver binding instance.
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
BluetoothConfigDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

/**
  Stop the HID KB device handled by this driver.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        SimpleTextIn Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  );

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
BluetoothConfigComponentNameGetDriverName (
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
BluetoothConfigComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );

#endif

