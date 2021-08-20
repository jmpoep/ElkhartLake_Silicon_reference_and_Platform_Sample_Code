/** @file
  This is the Common driver that initializes the Intel System Agent.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include "SaInit.h"
#include <Library/PciSegmentLib.h>
#include <SaConfigHob.h>
#include <Protocol/PciEnumerationComplete.h>

///
/// Global Variables
///
GLOBAL_REMOVE_IF_UNREFERENCED SA_CONFIG_HOB                          *mSaConfigHob;
BOOLEAN                                                              mSkipPamLock = FALSE;


/**
  SystemAgent Initialization Common Function.

  @retval EFI_SUCCESS   - Always.
**/

VOID
SaInitEntryPoint (
  VOID
  )
{
  ///
  /// Get SaConfigHob HOB
  ///
  mSaConfigHob              = NULL;
  mSaConfigHob              = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (mSaConfigHob != NULL) {
    mSkipPamLock = mSaConfigHob->SkipPamLock;
  }

  return;
}



/**
  Common function locks the PAM register as part of the SA Security requirements.

  @retval EFI_SUCCESS   - Always.
**/

VOID
SaPamLock (
  VOID
  )
{
  UINT32 MchBar;

  MchBar = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0) + R_SA_MCHBAR) & ~BIT0;

  if (mSkipPamLock == FALSE) {
    //
    // Lock PAM by removing POSTBOOT_SAI from the PAM_W_PG WAC/CP
    //
    DEBUG ((DEBUG_INFO, "PAM_LOCK!!\n"));
    MmioAnd64 (MchBar + R_SA_MCHBAR_PAM_W_PG_CP, (UINT64) ~(B_SA_MCHBAR_PAM_W_PG_HOSTIA_POSTBOOT_SAI));
    MmioAnd64 (MchBar + R_SA_MCHBAR_PAM_W_PG_WAC, (UINT64) ~(B_SA_MCHBAR_PAM_W_PG_HOSTIA_POSTBOOT_SAI));
  }
}
