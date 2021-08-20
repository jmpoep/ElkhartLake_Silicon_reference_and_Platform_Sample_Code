/** @file
  This file provides services for TWOLM PreMem policy default initialization

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

#include <Library/DebugLib.h>
#include <Library/TwoLmPreMemPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Library/CpuPcieLib.h>
#include <TwoLmConfig.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadTwoLmPreMemDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  TWOLM_PREMEM_CONFIG   *TwoLmPreMemConfig;

  TwoLmPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "TwoLmPreMemConfig->Header.GuidHob.Name = %g\n", &TwoLmPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TwoLmPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TwoLmPreMemConfig->Header.GuidHob.Header.HobLength));
  DEBUG ((DEBUG_INFO, "Updating default 2LM policy\n"));
  TwoLmPreMemConfig->Peg3Aspm = PcieAspmL0sL1; // Enable L0L1 ASPM
  TwoLmPreMemConfig->PMemSize = 0; // Default PMemSize is zero
}

static COMPONENT_BLOCK_ENTRY  mTwoLmIpBlockPreMem = {
  &gTwoLmPreMemConfigGuid,      sizeof (TWOLM_PREMEM_CONFIG),      TWOLM_PREMEM_CONFIG_REVISION,        LoadTwoLmPreMemDefault
};

/**
  Get TWOLM PreMem config block table total size.

  @retval     Size of TWOLM PreMem config block table
**/
UINT16
EFIAPI
TwoLmGetPreMemConfigBlockTotalSize (
  VOID
  )
{
  return mTwoLmIpBlockPreMem.Size;
}

/**
  TwoLmAddConfigBlocks add TwoLm PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
TwoLmAddPreMemConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mTwoLmIpBlockPreMem, 1);
  return Status;
}

/**
  This function prints the TwoLm PreMem phase policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
TwoLmPrintPreMemPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI     *SiPolicyPreMemPpi
  )
{
  EFI_STATUS              Status;
  TWOLM_PREMEM_CONFIG     *TwoLmPreMemConfig;
  UINT32                   Index;


  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gTwoLmPreMemConfigGuid, (VOID *) &TwoLmPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  //2LM Config
  //
  DEBUG ((DEBUG_INFO, "----------------------- 2LM_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", TwoLmPreMemConfig->Header.Revision));
  ASSERT (TwoLmPreMemConfig->Header.Revision == TWOLM_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " Current Mem Boot mode : %01d\n", TwoLmPreMemConfig->MemBootMode));
  DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->FarMemorySize = %d\n", TwoLmPreMemConfig->FarMemorySize));
  DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->PMemSize = %d\n", TwoLmPreMemConfig->PMemSize));
  DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->Peg3Aspm = %d\n", TwoLmPreMemConfig->Peg3Aspm));
  DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->MfvcWrrArb = %d\n", TwoLmPreMemConfig->MfvcWrrArb));
  if (TwoLmPreMemConfig->MfvcWrrArb) { //if its 128 phase then print other details
    for (Index = 0; Index < MFVC_VC_ARB_TABLE_INDEX; Index++) {
      DEBUG ((DEBUG_INFO, " VcId[%d] 0x%x\n", Index, TwoLmPreMemConfig->VcId_7_0[Index]));
    }
  }
  DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->SetHwParameters = %d\n", TwoLmPreMemConfig->SetHwParameters));
  if (TwoLmPreMemConfig->SetHwParameters) { // Print HW parameters only if the setting is enabled
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->Ltr_L1D2_ThVal = %d\n", TwoLmPreMemConfig->Ltr_L1D2_ThVal));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->Ltr_L1D2_ThScale = %d\n", TwoLmPreMemConfig->Ltr_L1D2_ThScale));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->SysPwrState = %d\n", TwoLmPreMemConfig->SysPwrState));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->MediaDeathNotification = %d\n", TwoLmPreMemConfig->MediaDeathNotification));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->HealthLogNotification = %d\n", TwoLmPreMemConfig->HealthLogNotification));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->TempBelowThrottleNotification = %d\n", TwoLmPreMemConfig->TempBelowThrottleNotification));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->TempAboveThrottleNotification = %d\n", TwoLmPreMemConfig->TempAboveThrottleNotification));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->MissingCommitBitNotification = %d\n", TwoLmPreMemConfig->MissingCommitBitNotification));
    DEBUG ((DEBUG_INFO, " TwoLmPreMemConfig->NVMeHoldDisableBit = %d\n", TwoLmPreMemConfig->NVMeHoldDisableBit));
  }
  return;
}
