/** @file
  This file provides definitions for functions that locate SCS controllers
  on PCI bus.

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

#include <Library/DebugLib.h>
#include <Register/ScsVer3Regs.h>

/**
  Gets the device and function number of the SdCard.

  @param[out] DeviceNum    Pointer to the variable to store device number
  @param[out] FunctionNum  Pointer to the variable to store function number
**/
VOID
ScsGetSdCardBdf (
  OUT UINT8  *DeviceNum,
  OUT UINT8  *FunctionNum
  )
{
  *DeviceNum = PCI_DEVICE_NUMBER_PCH_EHL_SCS_SDCARD;
  *FunctionNum = PCI_FUNCTION_NUMBER_PCH_EHL_SCS_SDCARD;
}

/**
  Gets the device and function number of the eMMC.

  @param[out] DeviceNum    Pointer to the variable to store device number
  @param[out] FunctionNum  Pointer to the variable to store function number
**/
VOID
ScsGetEmmcBdf (
  OUT UINT8  *DeviceNum,
  OUT UINT8  *FunctionNum
  )
{
  *DeviceNum = PCI_DEVICE_NUMBER_PCH_EHL_SCS_EMMC;
  *FunctionNum = PCI_FUNCTION_NUMBER_PCH_EHL_SCS_EMMC;
}

/**
  Gets the device and function number of the UFS

  @param[in]  UfsIndex     Index of the UFS controller
  @param[out] DeviceNum    Pointer to the variable to store device number
  @param[out] FunctionNum  Pointer to the variable to store function number
**/
VOID
ScsGetUfsBdf (
  IN  UINT8  UfsIndex,
  OUT UINT8  *DeviceNum,
  OUT UINT8  *FunctionNum
  )
{
  switch (UfsIndex) {
    case 0:
      *DeviceNum = PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS0;
      *FunctionNum = PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS0;
      break;
    case 1:
      *DeviceNum = PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS1;
      *FunctionNum = PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS1;
      break;
    default:
      ASSERT (FALSE);
  }
}

