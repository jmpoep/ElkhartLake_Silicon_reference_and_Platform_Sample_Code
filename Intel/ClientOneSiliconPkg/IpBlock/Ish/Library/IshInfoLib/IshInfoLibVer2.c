/** @file
  Ish Info Library

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
// General includes
#include <Uefi/UefiBaseType.h>
#include <Library/PchInfoLib.h>
#include <Register/IshRegsVer2.h>

/**
  Check if given Device Id belongs to ISH on current PCH

  @param[in] DevId  ISH Device Id

  @retval TRUE   DevId belongs to ISH
  @retval FALSE  DevId does not belong to ISH
**/
BOOLEAN
IsIshDev (
  UINT16 DevId
  )
{
  //@todo: fill for TGL-H
  switch (DevId) {
    case (V_TGL_LP_ISH_DEVICE_ID) :
      return TRUE;
      break;
    default:
      break;
  }
  return FALSE;
}

/**
  Get ISH Device Number

  @retval  ISH Device Number
**/
UINT8
IshGetDeviceNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_TGL_PCH_ISH;
}

/**
  Get ISH Function Number

  @retval  ISH Function Number
**/
UINT8
IshGetFunctionNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_TGL_PCH_ISH;
}
