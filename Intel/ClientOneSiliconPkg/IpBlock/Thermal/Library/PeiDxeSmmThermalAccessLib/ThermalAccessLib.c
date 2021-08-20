/** @file
  Thermal Access Lib.

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

#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PmcLib.h>
#include <Register/ThermalRegs.h>

/**
  Check thermal throttle level is locked

  @retval TRUE  Thermal throttle level is locked
          FALSE Thermal throttle level is not locked
**/
BOOLEAN
ThermalIsThrottleLock (
  VOID
  )
{
  return !!(MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_THERMAL_TL) & B_PMC_PWRM_THERMAL_TL_TLLOCK);
}

/**
  Check thermal EC thermal report is locked

  @retval TRUE  EC thermal report is locked
          FALSE EC thermal report is not locked
**/
BOOLEAN
ThermalIsEcThermalReportLock (
  VOID
  )
{
  return !!(MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_THERMAL_ECRPTEN) & B_PMC_PWRM_THERMAL_ECRPTEN_ECRPTENLOCK);
}

/**
  Check thermal PCH HOT is locked

  @retval TRUE  PCH HOT is locked
          FALSE PCH HOT is not locked
**/
BOOLEAN
ThermalIsPchHotLock (
  VOID
  )
{
  return !!(MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_THERMAL_PHLC) & B_PMC_PWRM_THERMAL_PHLC_PHLCLOCK);
}

/**
  Check thermal PMC throttle is locked

  @retval TRUE  PMC throttle is locked
          FALSE PMC throttle is not locked
**/
BOOLEAN
ThermalIsPmcThrottleLock  (
  VOID
  )
{
  return !!(MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_THERMAL_TLEN) & B_PMC_PWRM_THERMAL_TLEN_TLENLOCK);
}
