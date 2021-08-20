/** @file
  DCI private library.
  All functions from this library are available in PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/DciRegs.h>


/**
  Disable DCI ModPHY Power Gate Override, which allows DCI ModPHY being power-gated.
**/
VOID
DciDisModphyPgOverride (
  VOID
  )
{
  PchPcrAndThenOr32 (PID_DCI, R_DCI_PCR_ECKPWRCTL, ~0u, B_DCI_PCR_ECKPWRCTL_ROSC_SLOW_CLK_GATE_DISABLE);
}

/**
  Enable DCI ModPHY Power Gate Override, which prevets DCI ModPHY being power-gated. Only needed for 4-wire DCI OOB.
**/
VOID
DciEnModphyPgOverride (
  VOID
  )
{
  PchPcrAndThenOr32 (PID_DCI, R_DCI_PCR_ECKPWRCTL, (UINT32)~B_DCI_PCR_ECKPWRCTL_ROSC_SLOW_CLK_GATE_DISABLE, 0);
}

/**
  Return DCI ModPHY Power Gate Enabled status.

  @retval TRUE   DCI ModPHY Power Gate is enabled
  @retval FALSE  DCI ModPHY Power Gate is disabled
**/
BOOLEAN
IsDciModphyPgEnabled (
  VOID
  )
{
  return ((PchPcrRead32 (PID_DCI, R_DCI_PCR_ECKPWRCTL) & B_DCI_PCR_ECKPWRCTL_ROSC_SLOW_CLK_GATE_DISABLE) != 0);
}


/**
  Disable DCI clock request override.
**/
VOID
DciDisClkReq (
  VOID
  )
{
}

/**
  Enable DCI clock request override.
**/
VOID
DciEnClkReq (
  VOID
  )
{
}