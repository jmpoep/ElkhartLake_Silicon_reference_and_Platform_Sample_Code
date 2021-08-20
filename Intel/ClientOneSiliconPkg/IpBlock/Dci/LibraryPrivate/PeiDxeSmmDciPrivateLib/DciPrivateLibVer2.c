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
  PchPcrWrite16 (PID_DCI, R_DCI_PCR_EMODPHY_LANE, V_DCI_PCR_EMODPHY_LANE_PG_OVR_DIS);
  PchPcrWrite16 (PID_DCI, R_DCI_PCR_EMODPHY_CMNLANE, V_DCI_PCR_EMODPHY_CMNLANE_PG_OVR_DIS);
}

/**
  Enable DCI ModPHY Power Gate Override, which prevets DCI ModPHY being power-gated. Only needed for 4-wire DCI OOB.
**/
VOID
DciEnModphyPgOverride (
  VOID
  )
{
  PchPcrWrite16 (PID_DCI, R_DCI_PCR_EMODPHY_LANE, 0);
  PchPcrWrite16 (PID_DCI, R_DCI_PCR_EMODPHY_CMNLANE, 0);
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
  if (((PchPcrRead16 (PID_DCI, R_DCI_PCR_EMODPHY_LANE) & V_DCI_PCR_EMODPHY_LANE_PG_OVR_DIS) != 0) && \
    ((PchPcrRead16 (PID_DCI, R_DCI_PCR_EMODPHY_CMNLANE) & V_DCI_PCR_EMODPHY_CMNLANE_PG_OVR_DIS) != 0)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Disable DCI clock request override. It's enabled by HW default that keeps DCI clk_req asserted and prevents low power state for debug.
**/
VOID
DciDisClkReq (
  VOID
  )
{
  PchPcrAndThenOr8 (PID_DCI, R_DCI_PCR_ESRCCLK, (UINT8)~(B_DCI_PCR_ESRCCLK_S0I3P4_OVR | B_DCI_PCR_ESRCCLK_SRCCLK_RO_FAST_CLK_OVR), (B_DCI_PCR_ESRCCLK_S0I3P4_OVR | B_DCI_PCR_ESRCCLK_SRCCLK_RO_FAST_CLK_OVR));
}

/**
  Enable DCI clock request override.
**/
VOID
DciEnClkReq (
  VOID
  )
{
  PchPcrAndThenOr8 (PID_DCI, R_DCI_PCR_ESRCCLK, (UINT8)~(B_DCI_PCR_ESRCCLK_S0I3P4_OVR | B_DCI_PCR_ESRCCLK_SRCCLK_RO_FAST_CLK_OVR), 0);
}