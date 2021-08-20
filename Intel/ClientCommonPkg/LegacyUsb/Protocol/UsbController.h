/** @file
  This file contains USB Driver Protocol definition

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _USB_CONTROLLER_H_
#define _USB_CONTROLLER_H_

extern EFI_GUID gLegacyUsbProtocolGuid;

#include <Protocol/BlockIo.h>

typedef struct {
    UINT8   NumUsbKbds;
    UINT8   NumUsbMice;
    UINT8   NumUsbPoint;
    UINT8   NumUsbMass;
    UINT8   NumUsbHubs;
    UINT8   NumUsbCcids;
    UINT8   NumUhcis;
    UINT8   NumOhcis;
    UINT8   NumEhcis;
    UINT8   NumXhcis;
} CONNECTED_USB_DEVICES_NUM;

typedef VOID (EFIAPI *EFI_USB_REPORT_DEVICES ) (
  CONNECTED_USB_DEVICES_NUM *);

typedef struct _EFI_USB_HOTPLUG_DEVS {
    BOOLEAN cdrom;
    BOOLEAN floppy;
} EFI_USB_HOTPLUG_DEVS;

typedef EFI_STATUS (EFIAPI *EFI_USB_GET_HOTPLUG_DEVS ) (
  EFI_USB_HOTPLUG_DEVS *);

typedef EFI_STATUS (EFIAPI *EFI_USB_GET_RUNTIME_REGION ) (
  EFI_PHYSICAL_ADDRESS *,
  EFI_PHYSICAL_ADDRESS *);

typedef UINT8 (EFIAPI *EFI_USB_GET_NEXT_MASS_DEVICE_NAME ) (
  UINT8*, UINT8, UINT8);

typedef struct
{
    EFI_BLOCK_IO_PROTOCOL   BlockIoProtocol;
    EFI_BLOCK_IO_MEDIA      *Media;
    VOID                    *DevInfo;
    UINT16                  LogicalAddress;
    EFI_HANDLE              Handle;
    UINT16                  PciBDF;
    UINT8                   *DevString;
    UINT8                   StorageType;
} USB_MASS_DEV;

//----------------------------------------------------------------------------
// Name:        USB_SKIP_LIST
//
//
// Description:    If your roothub port 4 insert a hub.You want to skip hub's port 2.
//                 Set bRootPort = 4,  dRoutePath =2
//                 If your roothub port 4 insert a hub1.And hub1 port 2 insert a hub2.
//                 You want to skip hub2's port 1.
//                 Set bRootPort = 4,  dRoutePath =21
// Fields:   Name       Type        Description
//      ------------------------------------------------------------
//      bSkipType   BYTE        Skip by which Type
//      bSkipAll   	BYTE        If this flag is 1 than skip all ports.
//      wBDF        WORD        Bus Dev Function
//      bRootPort   BYTE        Root port path
//      dRoutePath  DWORD       Hub route path. See description.
//      bBaseClass  BYTE        Device Type
//
//----------------------------------------------------------------------------
#define SKIP_FOR_ALLCONTROLLER                  0x1

#define SKIP_FLAG_SKIP_PORT                     0x0
#define SKIP_FLAG_KEEP_PORT                     0x1
#define SKIP_FLAG_SKIP_LEVEL                    0x2

typedef struct _USB_SKIP_LIST{
    UINT8   bSkipType;
    UINT8   bFlag;
    UINT16  wBDF;
    UINT8   bRootPort;
    UINT32  dRoutePath;
    UINT8   bBaseClass;
} USB_SKIP_LIST;

//----------------------------------------------------------------------------
//      USB Mass Storage Related Data Structures and Equates
//----------------------------------------------------------------------------
#define USB_EMU_NONE            0
#define USB_EMU_FLOPPY_ONLY     1
#define USB_EMU_HDD_ONLY        2
#define USB_EMU_HDD_OR_FDD      3
#define USB_EMU_FORCED_FDD      4

#define BAID_TYPE_HDD           1
#define BAID_TYPE_RMD_HDD       2
#define BAID_TYPE_CDROM	        3
#define BAID_TYPE_RMD_FDD       4
#define BAID_TYPE_FDD           5

// Values for Mass Storage Device type
//-------------------------------------
#define USB_MASS_DEV_UNKNOWN    0
#define USB_MASS_DEV_HDD        1
#define USB_MASS_DEV_CDROM      2
#define USB_MASS_DEV_ARMD       3
#define USB_MASS_DEV_FDD        4
#define USB_MASS_DEV_MO         5


#define STOP_USB_CONTROLLER     0
#define START_USB_CONTROLLER    1

typedef VOID (EFIAPI *EFI_USB_CHANGE_EFI_TO_LEGACY) (UINT8);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_USB_LEGACY_BOOT_DEVICES)(VOID);
typedef EFI_STATUS (EFIAPI *EFI_USB_INSTALL_LEGACY_DEVICE)(USB_MASS_DEV*);
typedef EFI_STATUS (EFIAPI *EFI_USB_UNINSTALL_LEGACY_DEVICE)(USB_MASS_DEV*);
typedef EFI_STATUS (EFIAPI *EFI_GET_ASSIGN_USB_BOOT_PORT)(UINT8*, UINT8*);
typedef VOID (EFIAPI *EFI_KBC_ACCESS_CONTROL)(UINT8);
typedef EFI_STATUS (EFIAPI *EFI_USB_RT_LEGACY_CONTROL)(VOID *);
typedef VOID (EFIAPI *EFI_USB_STOP_UNSUPPORTED_HC)(VOID);
typedef VOID (EFIAPI *EFI_USB_SHUTDOWN_LEGACY)(VOID);
typedef VOID (EFIAPI *EFI_USB_COPY_SKIP_TABLE)(USB_SKIP_LIST*, UINT8);
typedef VOID (EFIAPI *EFI_USB_RT_STOP_CONTROLLER)(UINT16);
typedef VOID (EFIAPI *EFI_USB_INVOKE_API)(VOID*);
typedef struct _EFI_USB_PROTOCOL {
    UINT32                          Signature;
    VOID                            *USBDataPtr;
    EFI_USB_REPORT_DEVICES          UsbReportDevices;
    EFI_USB_GET_NEXT_MASS_DEVICE_NAME  UsbGetNextMassDeviceName;
    EFI_USB_CHANGE_EFI_TO_LEGACY    UsbChangeEfiToLegacy;
    EFI_USB_GET_RUNTIME_REGION      UsbGetRuntimeRegion;
    EFI_INSTALL_USB_LEGACY_BOOT_DEVICES InstallUsbLegacyBootDevices;
    EFI_USB_INSTALL_LEGACY_DEVICE   UsbInstallLegacyDevice;
    EFI_USB_UNINSTALL_LEGACY_DEVICE UsbUninstallLegacyDevice;
    EFI_GET_ASSIGN_USB_BOOT_PORT    UsbGetAssignBootPort;
    EFI_KBC_ACCESS_CONTROL          UsbRtKbcAccessControl;
    EFI_USB_RT_LEGACY_CONTROL       UsbLegacyControl;
    EFI_USB_STOP_UNSUPPORTED_HC     UsbStopUnsupportedHc;
    EFI_USB_SHUTDOWN_LEGACY         UsbRtShutDownLegacy;
    EFI_USB_COPY_SKIP_TABLE         UsbCopySkipTable;
    EFI_USB_RT_STOP_CONTROLLER      UsbRtStopController;
    EFI_USB_INVOKE_API              UsbInvokeApi;
} EFI_USB_PROTOCOL;

typedef struct {
    EFI_USB_STOP_UNSUPPORTED_HC     UsbStopUnsupportedHc;
} USB_SMM_PROTOCOL;

#endif // _USB_CONTROLLER_H_
