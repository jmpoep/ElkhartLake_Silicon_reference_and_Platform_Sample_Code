/** @file
  Common USB policy shared between PCH and CPU
  Contains general features settings for xHCI and xDCI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _USB_CONFIG_H_
#define _USB_CONFIG_H_

#define USB_CONFIG_REVISION 1
extern EFI_GUID gUsbConfigGuid;

#define MAX_USB2_PORTS  16
#define MAX_USB3_PORTS  10

#pragma pack (push,1)

#define PCH_USB_OC_PINS_MAX  4  ///< Maximal possible number of USB Over Current pins

///
/// Overcurrent pins, the values match the setting of EDS, please refer to EDS for more details
///
typedef enum {
  UsbOverCurrentPin0 = 0,
  UsbOverCurrentPin1,
  UsbOverCurrentPin2,
  UsbOverCurrentPin3,
  UsbOverCurrentPin4,
  UsbOverCurrentPin5,
  UsbOverCurrentPin6,
  UsbOverCurrentPin7,
  UsbOverCurrentPinMax,
  UsbOverCurrentPinSkip = 0xFF
} USB_OVERCURRENT_PIN;

/**
  This structure configures per USB2.0 port settings like enabling and overcurrent protection
**/
typedef struct {
  /**
    These members describe the specific over current pin number of USB 2.0 Port N.
    It is SW's responsibility to ensure that a given port's bit map is set only for
    one OC pin Description. USB2 and USB3 on the same combo Port must use the same
    OC pin (see: USB_OVERCURRENT_PIN).
  **/
  UINT32     OverCurrentPin     :  8;
  UINT32     Enable             :  1;     ///< 0: Disable; <b>1: Enable</b>.
  UINT32     RsvdBits0          : 23;     ///< Reserved bits
} USB2_PORT_CONFIG;

/**
  This structure configures per USB3.x port settings like enabling and overcurrent protection
**/
typedef struct {
  /**
    These members describe the specific over current pin number of USB 3.x Port N.
    It is SW's responsibility to ensure that a given port's bit map is set only for
    one OC pin Description. USB2 and USB3 on the same combo Port must use the same
    OC pin (see: USB_OVERCURRENT_PIN).
  **/
  UINT32  OverCurrentPin               :  8;
  UINT32  Enable                       :  1; ///< 0: Disable; <b>1: Enable</b>.
  UINT32  RsvdBits0                    : 23; ///< Reserved bits
} USB3_PORT_CONFIG;

/**
  The XDCI_CONFIG block describes the configurations
  of the xDCI Usb Device controller.
**/
typedef struct {
  /**
    This member describes whether or not the xDCI controller should be enabled.
    0: Disable; <b>1: Enable</b>.
  **/
  UINT32  Enable              :  1;
  UINT32  RsvdBits0           : 31;     ///< Reserved bits
} XDCI_CONFIG;


/**
  This member describes the expected configuration of the USB controller,
  Platform modules may need to refer Setup options, schematic, BIOS specification to update this field.
  The Usb20OverCurrentPins and Usb30OverCurrentPins field must be updated by referring the schematic.

  <b>Revision 1</b>:
  - Initial version.

**/
typedef struct {
  CONFIG_BLOCK_HEADER     Header;                   ///< Config Block Header
  /**
    This policy setting controls state of Compliance Mode enabling.
    Compliance Mode can be enabled for testing through this option but default setting is Disabled.
    <b>0:Disable</b>, 1: Enable
  **/
  UINT32                  EnableComplianceMode         :  1;
  /**
    This policy option when set will make BIOS program Port Disable Override register during PEI phase.
    When disabled BIOS will not program the PDO during PEI phase and leave PDO register unlocked for later programming.
    If this is disabled, platform code MUST set it before booting into OS.
    <b>1: Enable</b>
    0: Disable
  **/
  UINT32                  PdoProgramming               :  1;
  /**
    This option allows for control whether USB should program the Overcurrent Pins mapping into xHCI.
    Disabling this feature will disable overcurrent detection functionality.
    Overcurrent Pin mapping data is contained in respective port structures (i.e. USB30_PORT_CONFIG) in OverCurrentPin field.
    By default this Overcurrent functionality should be enabled and disabled only for OBS debug usage.
    <b>1: Will program USB OC pin mapping in respective xHCI controller registers</b>
    0: Will clear OC pin mapping allow for OBS usage of OC pins
  **/
  UINT32                  OverCurrentEnable            :  1;
  /**
    <b>(Test)</b>
    If this policy option is enabled then BIOS will program OCCFDONE bit in xHCI meaning that OC mapping data will be
    consumed by xHCI and OC mapping registers will be locked. OverCurrent mapping data is taken from respective port data
    structure from OverCurrentPin field.
    If EnableOverCurrent policy is enabled this also should be enabled, otherwise xHCI won't consume OC mapping data.
    <b>1: Program OCCFDONE bit and make xHCI consume OverCurrent mapping data</b>
    0: Do not program OCCFDONE bit making it possible to use OBS debug on OC pins.
  **/
  UINT32                  XhciOcLock                   :  1;
  /**
    Enabling this feature will allow for overriding LTR values for xHCI controller.
    Values used for programming will be taken from this config block and BIOS will disregard recommended ones.
    <b>0: disable - do not override recommended LTR values</b>
    1: enable - override recommended LTR values
  **/
  UINT32                  LtrOverrideEnable            :  1;
  UINT32                  UsbClockGatingEnable         :  1;
  UINT32                  UsbPowerGatingEnable         :  1;
  /**
    This setting enable LBPM GEN1 speed
    0: GEN2;
    1: GEN1;
  **/
  UINT32                  USB3LinkSpeed                : 1;
  UINT32                  RsvdBits0                    : 26;     ///< Reserved bits
  /**
    High Idle Time Control override value
    This setting is used only if LtrOverrideEnable is enabled
  **/
  UINT32                  LtrHighIdleTimeOverride;
  /**
    Medium Idle Time Control override value
    This setting is used only if LtrOverrideEnable is enabled
  **/
  UINT32                  LtrMediumIdleTimeOverride;
  /**
    Low Idle Time Control override value
    This setting is used only if LtrOverrideEnable is enabled
  **/
  UINT32                  LtrLowIdleTimeOverride;
  /**
    These members describe whether the USB2 Port N of PCH is enabled by platform modules.
  **/
  USB2_PORT_CONFIG        PortUsb20[MAX_USB2_PORTS];
  /**
    These members describe whether the USB3 Port N of PCH is enabled by platform modules.
  **/
  USB3_PORT_CONFIG        PortUsb30[MAX_USB3_PORTS];
  /**
    This setting enable or disable USB2 Port N OTG of PCH.
  **/
  UINT32                  USB20Otg[MAX_USB2_PORTS];
  /**
    This setting enable or disable USB3 Port N OTG of PCH.
  **/
  UINT32                  USB30Otg[MAX_USB3_PORTS];
  /**
    This member describes whether or not the xDCI controller should be enabled.
  **/
  XDCI_CONFIG             XdciConfig;

} USB_CONFIG;

#pragma pack (pop)

#endif // _USB_CONFIG_H_
