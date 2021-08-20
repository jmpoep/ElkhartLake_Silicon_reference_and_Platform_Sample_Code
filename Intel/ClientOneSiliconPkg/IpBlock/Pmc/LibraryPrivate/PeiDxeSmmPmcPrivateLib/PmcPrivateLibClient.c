/** @file
  PCH PMC Private Library implementation for CannonLake PCH.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/SataLib.h>
#include <Library/PchInfoLib.h>
#include <Register/PmcRegs.h>

#include "PmcPrivateLibInternal.h"

/**
  This function disables (non-static power gating) SATA and enables ModPHY SPD gating (PCH-LP only).

  @param[in]  SataCtrlIndex     SATA controller index
**/
VOID
PmcDisableSata (
  IN UINT32     SataCtrlIndex
  )
{
  UINT32 PchPwrmBase;
  PchPwrmBase = PmcGetPwrmBase ();

  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  //
  // Set PWRMBASE + NST_PG_FDIS_1 [22] = 1b to disable SATA Controller in PMC
  //
  MmioOr32 (PchPwrmBase + R_PMC_PWRM_NST_PG_FDIS_1, B_PMC_PWRM_NST_PG_FDIS_1_SATA_FDIS_PMC);

  if (PmcIsModPhySusPgSupported ()) {
    //
    // MPHY SUS PG supported on PCH-LP only:
    //
    // Set MSPDRTREQ:
    // PWRMBASE + R_PWRM_MODPHY_PM_CFG5[12] = 1 to enable ASL code trigger request for ModPHY SPD gating.
    //
    MmioOr32 (PchPwrmBase + R_PMC_PWRM_MODPHY_PM_CFG5, B_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_SATA);
  }
}

/**
  This function checks if SATA device is supported (not disabled by fuse)

  @param[in] SataCtrlIndex SATA controller index

  @retval SATA support state
**/
BOOLEAN
PmcIsSataSupported (
  UINT32  SataCtrlIndex
  )
{
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_SATA_FUSE_SS_DIS) == 0);
}
