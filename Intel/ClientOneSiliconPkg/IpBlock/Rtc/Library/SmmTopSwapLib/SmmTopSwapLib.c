/** @file
  Top Swap SMM library.

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
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/RtcRegs.h>

/**
  Get TopSwap Status

  @retval TRUE  TopSwap is set
  @retval FALSE TopSwap is clear
**/
BOOLEAN
TopSwapStatus (
  VOID
  )
{
  return (PchPcrRead32 (PID_RTC_HOST, R_RTC_PCR_BUC) & B_RTC_PCR_BUC_TS) != 0;
}

/**
  Set TopSwap Status

  @param[in]  TopSwapEnable     Enable TopSwap or Disable it.

  @retval     EFI_SUCCESS       TopSwap set successfully
  @retval     EFI_DEVICE_ERROR  SBI command error
**/
EFI_STATUS
TopSwapSet (
  IN BOOLEAN  TopSwapEnable
  )
{
  if (TopSwapEnable) {
    PchPcrAndThenOr32 (PID_RTC_HOST, R_RTC_PCR_BUC, ~0u, B_RTC_PCR_BUC_TS);
  } else {
    PchPcrAndThenOr32 (PID_RTC_HOST, R_RTC_PCR_BUC, (UINT32) ~B_RTC_PCR_BUC_TS, 0);
  }
  return EFI_SUCCESS;
}
