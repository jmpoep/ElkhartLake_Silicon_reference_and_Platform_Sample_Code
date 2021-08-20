/** @file
 UsbPolicy definitions.

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

#ifndef _USB_POLICY_PROTOCOL_H_
#define _USB_POLICY_PROTOCOL_H_

#ifndef VFRCOMPILE
typedef enum {
  USBMASS_EMU_AUTO,
  USBMASS_EMU_FDD,
  USBMASS_EMU_FORCED_FDD,
  USBMASS_EMU_HDD,
  USBMASS_EMU_CD
} USBMASS_EMU_TYPE;
#endif

#define USB_DEVPLCY_STATUS_PRESENT  1

#ifndef TYPEDEF_USB_SUPPORT_SETUP
#define TYPEDEF_USB_SUPPORT_SETUP
typedef struct {
  UINT8  UsbMainSupport;
  UINT8  UsbLegacySupport;
  UINT8  UsbEhciHandoff;
  UINT8  UsbOhciHandoff;
  UINT8  UsbHotplugFddSupport;
  UINT8  UsbHotplugHddSupport;
  UINT8  UsbHotplugCdromSupport;
  UINT8  UsbEmul6064;
  UINT8  UsbMassResetDelay;
  UINT8  UsbControlTimeOut;
  UINT8  UsbEmu1;
  UINT8  UsbEmu2;
  UINT8  UsbEmu3;
  UINT8  UsbEmu4;
  UINT8  UsbEmu5;
  UINT8  UsbEmu6;
  UINT8  UsbEmu7;
  UINT8  UsbEmu8;
  UINT8  UsbEmu9;
  UINT8  UsbEmu10;
  UINT8  UsbEmu11;
  UINT8  UsbEmu12;
  UINT8  UsbEmu13;
  UINT8  UsbEmu14;
  UINT8  UsbEmu15;
  UINT8  UsbEmu16;
  UINT8  UsbXhciSupport;
  UINT8  UsbXhciHandoff;
  UINT8  PowerGoodDeviceDelay;
  UINT8  PowerGoodDeviceNumDelay;
  UINT8  UsbHiSpeedSupport;
  UINT8  UsbMassDriverSupport;
  UINT8  UsbS5WakeupSupport;
  UINT8  UsbOddLegacyBootSupport;
  UINT8  LegacyFreeDosSupport;
} USB_SUPPORT_SETUP;
#endif

#ifndef TYPEDEF_USB_MASS_DEV_VALID
#define TYPEDEF_USB_MASS_DEV_VALID
typedef struct{
  UINT8  UsbEmu1Valid;
  UINT8  UsbEmu2Valid;
  UINT8  UsbEmu3Valid;
  UINT8  UsbEmu4Valid;
  UINT8  UsbEmu5Valid;
  UINT8  UsbEmu6Valid;
  UINT8  UsbEmu7Valid;
  UINT8  UsbEmu8Valid;
  UINT8  UsbEmu9Valid;
  UINT8  UsbEmu10Valid;
  UINT8  UsbEmu11Valid;
  UINT8  UsbEmu12Valid;
  UINT8  UsbEmu13Valid;
  UINT8  UsbEmu14Valid;
  UINT8  UsbEmu15Valid;
  UINT8  UsbEmu16Valid;
} USB_MASS_DEV_VALID;
#endif

#define MAX_USB_MASS                8
#define SETUP_DATA_HOTPLUG_ENABLED  1
#define SETUP_DATA_HOTPLUG_DISABLED 2
#define SETUP_DATA_HOTPLUG_AUTO     3
#define SETUP_DATA_RESETDELAY_20S   1

#ifndef VFRCOMPILE

#define     USB_HC_UHCI                 0x10
#define     USB_HC_OHCI                 0x20
#define     USB_HC_EHCI                 0x30
#define     USB_HC_XHCI                 0x40

typedef struct {
  UINT8                         Type;
  EFI_DEVICE_PATH_PROTOCOL      *Device;
  EFI_HANDLE                    HwSmiHandle;
} USB_HW_SMI_HC_CONTEXT;

typedef struct{
  UINT8                  HcCount;
  USB_HW_SMI_HC_CONTEXT  **HcContext;
} USB_HW_SMI_HC_TABLE;

typedef struct _USB_POLICY_PROTOCOL {
  USB_SUPPORT_SETUP    *UsbDevPlcy;
  USB_HW_SMI_HC_TABLE  UsbHwSmiHcTable;
} EFI_USB_POLICY_PROTOCOL;

#endif

#define EMULATION_FAKE_INTERFACE  1

#ifndef TYPEDEF_USB_MASS_DEV_NUM
#define TYPEDEF_USB_MASS_DEV_NUM
typedef struct {
  UINT8  UsbMassDevNum;
  UINT8  IsInteractionAllowed;
} USB_MASS_DEV_NUM;
#endif

#ifndef TYPEDEF_USB_CONTROLLER_NUM
#define TYPEDEF_USB_CONTROLLER_NUM
typedef struct {
    UINT8   UhciNum;
    UINT8   OhciNum;
    UINT8   EhciNum;
    UINT8   XhciNum;
} USB_CONTROLLER_NUM;
#endif

typedef struct {
  UINT16  UsbTimingPolicyRevision;
  UINT16  UsbTimingPolicyLength;
  UINT16  EhciPortPowerOnDelay;
  UINT16  EhciPortConnect;
  UINT16  EhciPortReset;
  UINT16  OhciHcResetDelay;
  UINT16  OhciPortEnable;
  UINT16  OhciHcReset;
  UINT16  UhciGlobalReset;
  UINT16  UhciPortEnable;
  UINT16  HubPortConnect;
  UINT16  HubPortEnable;
  UINT16  MassDeviceComeUp;
  UINT16  RmhPowerOnDelay;
} USB_TIMING_POLICY;
#endif // _USB_POLICY_PROTOCOL_H_
