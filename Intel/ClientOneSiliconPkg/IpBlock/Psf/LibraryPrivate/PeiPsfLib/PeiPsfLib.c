/** @file
  Initilize PSF device in PEI

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
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PsfLib.h>
#include <Ppi/SiPolicy.h>
#include <PsfConfig.h>
#include <Register/PchRegsPsf.h>


/**
  Configure PSF power management.
  Must be called after all PSF configuration is completed.

  @param[in] SiPolicyPpi        The SI Policy PPI instance
**/
VOID
PsfConfigurePowerManagement (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  UINT32              PsfTableIndex;
  PSF_SEGMENT         *PsfTable;
  UINT32              PsfTableSize;
  UINT32              DataAnd32;
  UINT32              DataOr32;
  PSF_CONFIG          *PsfConfig;
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  DataAnd32 = ~0u;
  DataOr32 = B_PCH_PSF_PCR_GLOBAL_CONFIG_ENLCG;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPsfConfigGuid, (VOID *) &PsfConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  if (PsfConfig->TccEnable) {
    // Configure PSF for TCC by reducing transaction latency.  This will disable some power saving features:
    // PSF Local Clock Enable = 0
    DataAnd32 = (UINT32) ~B_PCH_PSF_PCR_GLOBAL_CONFIG_ENLCG;
  }

  DataOr32 |= B_PCH_PSF_PCR_GLOBAL_CONFIG_ENPCG;

  PsfSegments (&PsfTable, &PsfTableSize);

  // There in an ordering requirement to program enTCG before enLCG.

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    if (PchGeneralConfig->PchMasterClockGating != 0) {
      PchPcrAndThenOr32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG, ~0u, B_PCH_PSF_PCR_GLOBAL_CONFIG_ENTCG);
      PchPcrAndThenOr32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG, DataAnd32, DataOr32);
    } else {
      PchPcrAndThenOr32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG, (UINT32)~B_PCH_PSF_PCR_GLOBAL_CONFIG_ENTCG, 0);
      PchPcrAndThenOr32 (
        PsfTable[PsfTableIndex].SbPid,
        R_PCH_PSF_PCR_GLOBAL_CONFIG,
        (UINT32)~(B_PCH_PSF_PCR_GLOBAL_CONFIG_ENPCG | B_PCH_PSF_PCR_GLOBAL_CONFIG_ENLCG),
        (B_PCH_PSF_PCR_GLOBAL_CONFIG_IDLENAK | B_PCH_PSF_PCR_GLOBAL_CONFIG_ENEEI)
        );
    }
  }

}
