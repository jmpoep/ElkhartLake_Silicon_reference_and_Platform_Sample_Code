/** @file
  This file contains information about Hybrid Graphics.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _HG_INFO_HOB_H_
#define _HG_INFO_HOB_H_

#include "HybridGraphicsInfo.h"

extern EFI_GUID gHybridGraphicsInfoHobGuid;

#pragma pack (1)

///
/// SA GPIO Data Structure
///
typedef struct {
  UINT8   ExpanderNo; ///< =Expander No For I2C based GPIO
  UINT32  GpioNo;     ///< GPIO pad
  BOOLEAN Active;     ///< 0=Active Low; 1=Active High
} PCIE_GPIO;

///
/// SA PCIE RTD3 GPIO Data Structure
///
typedef struct {
  UINT8              GpioSupport;      ///< 0=Not Supported; 1=PCH based; 2=I2C Based
  PCIE_GPIO          HoldRst;          ///< Offset 8 This field contain PCIe HLD RESET GPIO value and level information
  PCIE_GPIO          PwrEnable;        ///< This field contain PCIe PWR Enable GPIO value and level information
  UINT32             WakeGpioNo;       ///< This field contain PCIe RTD3 Device Wake GPIO number
} PCIE_RTD3_GPIO;

///
/// HG Info HOB
///
typedef struct {
  HG_MODE           HgMode;
  UINT8             RootPortIndex;
  PCIE_RTD3_GPIO    Rtd3Pcie0Gpio;
  UINT16            DelayAfterPwrEn;
  UINT16            DelayAfterHoldReset;
} HG_INFO;

//
// VMD Info Hob
//
typedef struct {
  EFI_HOB_GUID_TYPE      EfiHobGuidType;
  HG_INFO                HgInfo;
} HG_INFO_HOB;

#pragma pack ()


#endif
