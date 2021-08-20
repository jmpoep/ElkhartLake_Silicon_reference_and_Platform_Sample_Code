/** @file
  USB2 PHY configuration policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _USB2_PHY_CONFIG_H_
#define _USB2_PHY_CONFIG_H_

#include <UsbConfig.h>

#define USB2_PHY_CONFIG_REVISION 1
extern EFI_GUID gUsb2PhyConfigGuid;

#pragma pack (push,1)

/**
  This structure configures per USB2 AFE settings.
  It allows to setup the port electrical parameters.
**/
typedef struct {
/** Per Port HS Preemphasis Bias (PERPORTPETXISET)
  000b - 0mV
  001b - 11.25mV
  010b - 16.9mV
  011b - 28.15mV
  100b - 28.15mV
  101b - 39.35mV
  110b - 45mV
  111b - 56.3mV
**/
  UINT8   Petxiset;
/** Per Port HS Transmitter Bias (PERPORTTXISET)
  000b - 0mV
  001b - 11.25mV
  010b - 16.9mV
  011b - 28.15mV
  100b - 28.15mV
  101b - 39.35mV
  110b - 45mV
  111b - 56.3mV
**/
  UINT8   Txiset;
/**
  Per Port HS Transmitter Emphasis (IUSBTXEMPHASISEN)
  00b - Emphasis OFF
  01b - De-emphasis ON
  10b - Pre-emphasis ON
  11b - Pre-emphasis & De-emphasis ON
**/
  UINT8   Predeemp;
/**
  Per Port Half Bit Pre-emphasis (PERPORTTXPEHALF)
  1b - half-bit pre-emphasis
  0b - full-bit pre-emphasis
**/
  UINT8   Pehalfbit;
} USB2_PHY_PARAMETERS;

/**
  This structure holds info on how to tune electrical parameters of USB2 ports based on board layout

  <b>Revision 1</b>:
  - Initial version.

**/
typedef struct {
  CONFIG_BLOCK_HEADER     Header;                   ///< Config Block Header
  /**
    This structure configures per USB2 port physical settings.
    It allows to setup the port location and port length, and configures the port strength accordingly.
    Changing this policy values from default ones may require disabling USB2 PHY Sus Well Power Gating
    through Usb2PhySusPgEnable on PCH-LP
  **/
  USB2_PHY_PARAMETERS          Port[MAX_USB2_PORTS];
} USB2_PHY_CONFIG;

#pragma pack (pop)

#endif // _USB2_PHY_CONFIG_H_

