/** @file
  This file provides PSTH Public Library implementation

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PsthLib.h>
#include <Register/PchRegsPsth.h>

/**
  Get address from IOTRAP low dword.

  @param[in] IoTrapRegLowDword    IOTRAP register low dword

  @retval                         Address of IOTRAP setting.
**/
STATIC
UINT16
AddressFromLowDword (
  UINT32  IoTrapRegLowDword
  )
{
  return (UINT16) (IoTrapRegLowDword & B_PSTH_PCR_TRPREG_AD);
}

/**
  Get length from IOTRAP low dword.

  @param[in] IoTrapRegLowDword    IOTRAP register low dword

  @retval                         Length of IOTRAP setting.
**/
STATIC
UINT16
LengthFromLowDword (
  UINT32  IoTrapRegLowDword
  )
{
  return (UINT16) (((IoTrapRegLowDword >> 16) & 0xFC) + 4);
}

/**
  Get IOTRAP resource settings

  @param[in out] IoTrapResource  Point to IOTRAP_RESOURCE_SETTING.
**/
VOID
PsthGetIoTrapResourceSetting (
  IN OUT    IOTRAP_RESOURCE_SETTING  *IoTrapResources
  )
{
  UINT32 Index;
  UINT32 IoTrapRegLowDword;

  for (Index = 0; Index < IOTRAP_ENTRY_MAX; Index++) {
    IoTrapRegLowDword = PchPcrRead32 (PID_PSTH, R_PSTH_PCR_TRPREG0 + Index * 8);
    IoTrapResources->IoTrapResourceEntry[Index].Base = AddressFromLowDword (IoTrapRegLowDword);
    IoTrapResources->IoTrapResourceEntry[Index].Length = LengthFromLowDword (IoTrapRegLowDword);
  }
}
