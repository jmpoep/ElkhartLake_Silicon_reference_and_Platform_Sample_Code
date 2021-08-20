/** @file

  Platform NvRam CMOS Hook Library which will provide the CMOS instances to PlatformNvRamHookLib.h.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <PlatformNvRamHookLib.h>
#include "CmosMap.h"
#include <Library/CmosAccessLib.h>
#include <Library/DebugLib.h>
#include <SetupVariable.h>
/**
  This function checks if RTC Power Failure occurred by
  reading RTC_PWR_FLR bit

  @retval RTC Power Failure state: TRUE  - Battery is always present.
                                   FALSE - CMOS is cleared.
**/
BOOLEAN
EFIAPI
PmcIsRtcBatteryGood(
  VOID
  );

/**
  CMOS test to see if Checksum is bad.

  @retval State of CMOS content : TRUE  - CMOS content is bad
                                  FALSE - CMOS content is good
**/
BOOLEAN
IsChecksumBad (
  VOID
  )
{
  if (CmosRead8((UINT8)CMOS_BAD_REG) & (BIT6 + BIT7)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Clear Diagnostic Status.
**/
VOID
ClearDiagnosticStatus (
  VOID
  )
{
  UINT8      Value;

  Value = CmosRead8((UINT8)CMOS_BAD_REG);
  CmosWrite8((UINT8)CMOS_BAD_REG, (Value & 0x3F));
}

/**
  Check to reset setup variable and Clear CMOS 0E when CMOS content is bad

  @retval Flag to Reset Setup variable :  TRUE  - When CMOS content is bad
                                          FALSE - Otherwise
**/
BOOLEAN
NeedResetBoardDefaultVariableHob(
  )
{
  //
  // Check whether the CMOS content is corrupted.
  //
  if (IsChecksumBad ()) {
    DEBUG ((DEBUG_ERROR, "CMOS battery is healthy but CMOS content is bad. Reset the SMOS 0Eh and the Setup variable.\n"));
    ClearDiagnosticStatus ();
    return TRUE;
  }
  return FALSE;
}

/**
  Load CMOS default on RTC battery failure.
**/
VOID
SecondaryNvRamInit(
  VOID
  )
{
  //
  // Perform a checksum computation and verify if the checksum is correct. If the checksum is incorrect
  // initialize all the CMOS location to their default values and recalculate the checksum.
  //
  if (PmcIsRtcBatteryGood ()) {
    CmosInit (FALSE);
  } else {
    DEBUG ((EFI_D_ERROR, "RTC battery is failure. Load CMOS default.\n"));
    CmosInit (TRUE);
  }
}

/**
  Get Boot Flag Status.

  @retval Value of current boot status
**/
UINT8
GetBootFlagStatus(
  VOID
  )
{
  return CmosRead8(CMOS_FAST_BOOT_REG);
}

/**
Update Boot Flag Status.

@param [in] BootStatus   Current Boot value which to be updated.
**/
VOID
UpdateBootFlagStatus(
  UINT8  BootStatus
  )
{
  CmosWrite8(CMOS_FAST_BOOT_REG, BootStatus);
}

/**
  Get RTC 3 Address.

  @retval Current value of RTC 3 Address
**/
UINT8
GetRtc3Address(
  VOID
  )
{
  return CmosRead8(0x4F);
}

/**
  Get Post Code Break for Port 80 and 81

  @param [out] *Port80   Pointer to return value of post code 80

  @param [out] *Port81   Pointer to return value of post code 81
**/

VOID
GetPostCodeBreak(
  UINT8 *Port80,
  UINT8 *Port81
  )
{
}

/**
  Get TXT Alias Check Request and Reset it.

  @retval TXT Alias Check Request
**/
UINT8
GetTxtAliasCheckAndReset(
  VOID
  )
{
  UINT8 TxtACheck;
  TxtACheck =  CmosRead8(CMOS_TXT_REG);
  //
  // ACheck Request needs to be reset since we do not want system to run ACheck in the same boot sequence
  //
  CmosWrite8(CMOS_TXT_REG, (UINT8)0);
  return TxtACheck;
}

/**
  Save the TXT Alias Check Request.

  @param [in] ACheckRequest   Request of TXT Alias Check.
**/
VOID
SaveTxtAliasCheck(
  UINT8  ACheckRequest
  )
{
  CmosWrite8(CMOS_TXT_REG, ACheckRequest);
}

/**
  Save the CPU Ratio.

  @param [in] CpuRatio   The Cpu ratio value to be saved.
**/
VOID
SaveCpuRatio(
  UINT8  CpuRatio
)
{
  CmosWrite8(CMOS_CPU_RATIO_OFFSET, CpuRatio);
}

/**
  Set the BCLK Ramp Flag.

  @param [in] BclkRampFlag   The BCLK Ramp Flag to be set.
**/
VOID
SetBclkRampFlag(
  UINT8  BclkRampFlag
  )
{
  CmosWrite8(CMOS_OC_SEND_BCLK_RAMP_MSG, BclkRampFlag);
}
