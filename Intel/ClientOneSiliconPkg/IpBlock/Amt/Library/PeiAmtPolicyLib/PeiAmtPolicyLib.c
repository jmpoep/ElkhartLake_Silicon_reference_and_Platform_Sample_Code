/** @file
  This file is PeiAmtPolicy library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/PeiAmtPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <AmtConfig.h>

/**
  Load default settings for AMT config block in PEI phase.

  @param[in] ConfigBlockPointer                 The pointer to the config block
**/
VOID
LoadAmtPeiDefault (
  IN VOID                           *ConfigBlockPointer
  );

STATIC COMPONENT_BLOCK_ENTRY  mAmtIpBlocks [] = {
  {&gAmtPeiConfigGuid,      sizeof (AMT_PEI_CONFIG),          AMT_PEI_CONFIG_REVISION,      LoadAmtPeiDefault},
};

/**
  Get AMT config block table total size.

  @retval        Size of AMT config block table
**/
UINT16
EFIAPI
AmtGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mAmtIpBlocks[0], sizeof (mAmtIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  AmtAddConfigBlocks add all AMT config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add AMT config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
AmtAddConfigBlocks (
  IN VOID      *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "AMT AddConfigBlocks\n"));

  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mAmtIpBlocks[0], sizeof (mAmtIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Load default settings for AMT config block in PEI phase.

  @param[in] ConfigBlockPointer                 The pointer to the config block
**/
VOID
LoadAmtPeiDefault (
  IN VOID                           *ConfigBlockPointer
  )
{
  AMT_PEI_CONFIG        *AmtPeiConfig;
  AmtPeiConfig = ConfigBlockPointer;

  AmtPeiConfig->AmtEnabled = TRUE;
  AmtPeiConfig->FwProgress = TRUE;
}

/**
  Dump values of AMT config block in PEI phase.

  @param[in] AmtPeiConfig                   The pointer to the config block
**/
VOID
EFIAPI
PrintAmtPeiConfig (
  IN  AMT_PEI_CONFIG            *AmtPeiConfig
  )
{
  DEBUG ((DEBUG_INFO, "------------------------ AMT_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision          : 0x%x\n", AmtPeiConfig->Header.Revision));
  ASSERT (AmtPeiConfig->Header.Revision == AMT_PEI_CONFIG_REVISION);

  DEBUG ((DEBUG_INFO, " AmtEnabled        : 0x%x\n", AmtPeiConfig->AmtEnabled));
  DEBUG ((DEBUG_INFO, " WatchDogEnabled   : 0x%x\n", AmtPeiConfig->WatchDogEnabled));
  DEBUG ((DEBUG_INFO, " FwProgress        : 0x%x\n", AmtPeiConfig->FwProgress));
  DEBUG ((DEBUG_INFO, " WatchDogTimerOs   : 0x%x\n", AmtPeiConfig->WatchDogTimerOs));
  DEBUG ((DEBUG_INFO, " WatchDogTimerBios : 0x%x\n", AmtPeiConfig->WatchDogTimerBios));
  DEBUG ((DEBUG_INFO, " ManageabilityMode : 0x%x\n", AmtPeiConfig->ManageabilityMode));
  DEBUG ((DEBUG_INFO, " AmtSolEnabled     : 0x%x\n", AmtPeiConfig->AmtSolEnabled));
  DEBUG ((DEBUG_INFO, " RemoteAssistance  : 0x%x\n", AmtPeiConfig->RemoteAssistance));
  DEBUG ((DEBUG_INFO, " AmtKvmEnabled     : 0x%x\n", AmtPeiConfig->AmtKvmEnabled));
  DEBUG ((DEBUG_INFO, " ForcMebxSyncUp    : 0x%x\n", AmtPeiConfig->ForcMebxSyncUp));

}

/**
  Print PEI AMT Config Block

  @param[in] SiPolicyPpi The RC Policy PPI instance
**/
VOID
EFIAPI
AmtPrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                        Status;
  AMT_PEI_CONFIG                    *AmtPeiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "\n---------------------- AmtPolicyPpi Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : 0x%x\n", SiPolicyPpi->TableHeader.Header.Revision));
  ASSERT (SiPolicyPpi->TableHeader.Header.Revision == SI_POLICY_REVISION);

  PrintAmtPeiConfig (AmtPeiConfig);
  DEBUG ((DEBUG_INFO, "\n---------------------- AmtPolicyPpi Print End -------------------\n"));

  DEBUG_CODE_END ();
}