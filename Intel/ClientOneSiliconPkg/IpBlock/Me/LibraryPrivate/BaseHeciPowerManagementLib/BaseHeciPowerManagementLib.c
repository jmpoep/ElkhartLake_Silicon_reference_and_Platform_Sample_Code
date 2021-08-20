/** @file
  HECI Power Management Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <Uefi.h>

#include <Library/HeciPowerManagementLib.h>
#include <Library/IoLib.h>

/**
  Returns whether the HECI device is idle (D0i3).

  @param[in]  HeciMemoryBarAddress    The HECI device's BAR address.

  @retval  TRUE     The HECI device is idle
  @retval  FALSE    The HECI device is not idle

**/
BOOLEAN
EFIAPI
IsHeciIdle (
  IN  UINTN     HeciMemoryBarAddress
  )
{
  return ((MmioRead32 (HeciMemoryBarAddress + R_ME_DEVIDLEC) & B_ME_DEVIDLEC_DEVIDLE) == B_ME_DEVIDLEC_DEVIDLE);
}

/**
  Places a HECI device into the active state (D0).

  @param[in]  HeciMemoryBarAddress    The HECI device's BAR address.
  @param[in]  AtRuntime               Indicates if at runtime.

**/
VOID
EFIAPI
SetHeciActive (
  IN  UINTN     HeciMemoryBarAddress,
  IN  BOOLEAN   AtRuntime
  )
{

  if (!HECI_PM_ALLOW_PM_IN_PRE_RUNTIME && !AtRuntime) {
    return;
  }

  ///
  /// 1. If CIP=1, wait until cleared (if host is not using interrupts - poll on the bit value until cleared)
  ///
  while ((MmioRead32 (HeciMemoryBarAddress + R_ME_DEVIDLEC) & B_ME_DEVIDLEC_CIP) == B_ME_DEVIDLEC_CIP);

  ///
  /// 2. Read the DEVIDLEC register value. Exit if already in active state.
  ///
  if (!IsHeciIdle (HeciMemoryBarAddress)) {
    return;
  }

  ///
  /// 3. Set DEVIDLE = 0 and write the DEVIDLEC register value (RR [3:3] is cleared by SW by writing '1')
  ///
  MmioAnd32 (HeciMemoryBarAddress + R_ME_DEVIDLEC, (UINT32) (~(B_ME_DEVIDLEC_DEVIDLE | B_ME_DEVIDLEC_RR)));

  ///
  /// 4. Read the DEVIDLEC register value
  /// 5. If CIP=1, wait until cleared (if host is not using interrupts - poll on the bit value until cleared)
  while ((MmioRead32 (HeciMemoryBarAddress + R_ME_DEVIDLEC) & B_ME_DEVIDLEC_CIP) == B_ME_DEVIDLEC_CIP);
}

/**
  Places a HECI device into the idle state (D0i3).

  @param[in]  HeciMemoryBarAddress    The HECI device's BAR address.
  @param[in]  AtRuntime               Indicates if at runtime.

**/
VOID
EFIAPI
SetHeciIdle (
  IN  UINTN     HeciMemoryBarAddress,
  IN  BOOLEAN   AtRuntime
  )
{
  if (!HECI_PM_ALLOW_PM_IN_PRE_RUNTIME && !AtRuntime) {
    return;
  }

  ///
  /// 1. If CIP=1, wait until cleared (if host is not using interrupts - poll on the bit value until cleared)
  ///
  while ((MmioRead32 (HeciMemoryBarAddress + R_ME_DEVIDLEC) & B_ME_DEVIDLEC_CIP) == B_ME_DEVIDLEC_CIP);

  ///
  /// 2. Read the DEVIDLEC register value. Exit if already in idle state.
  ///
  if (IsHeciIdle (HeciMemoryBarAddress)) {
    return;
  }

  ///
  /// 3. Set DEVIDLE bit in the DEVIDLEC register
  ///
  MmioOr32 (HeciMemoryBarAddress + R_ME_DEVIDLEC, B_ME_DEVIDLEC_DEVIDLE);
}