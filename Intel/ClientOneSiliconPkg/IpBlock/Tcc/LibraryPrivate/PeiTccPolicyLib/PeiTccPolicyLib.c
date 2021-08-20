/** @file
  This file provides services for TCC policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <TccConfig.h>

/**
  Print TCC_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
TccPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  TCC_CONFIG        *TccConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTccConfigGuid, (VOID *) &TccConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ TCC Sub Region Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Tcc Tuning Enabled           = %x\n", TccConfig->TccTuningEnable));
  DEBUG ((DEBUG_INFO, " Tcc Sub Region   - Base Address = %x\n", TccConfig->TccSubRegion.BaseAddress));
  DEBUG ((DEBUG_INFO, " Tcc Sub Region   - Size = %x\n", TccConfig->TccSubRegion.Size));
}

VOID
TccPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS        Status;
  TCC_CONFIG        *TccConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gTccPreMemConfigGuid, (VOID *) &TccConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ TCC Sub Region Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Tcc Tuning Enabled           = %x\n", TccConfig->TccTuningEnable));
  DEBUG ((DEBUG_INFO, " Tcc Sub Region   - Base Address = %x\n", TccConfig->TccSubRegion.BaseAddress));
  DEBUG ((DEBUG_INFO, " Tcc Sub Region   - Size = %x\n", TccConfig->TccSubRegion.Size));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TccLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  TCC_CONFIG      *TccConfig;

  TccConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "TccConfig->Header.GuidHob.Name = %g\n", &TccConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TccConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TccConfig->Header.GuidHob.Header.HobLength));

  TccConfig->TccTuningEnable = 0;
  TccConfig->TccSubRegion.BaseAddress = 0;
  TccConfig->TccSubRegion.Size = (UINT32) 0x0;

}

STATIC COMPONENT_BLOCK_ENTRY  mTccBlocks = {
  &gTccConfigGuid,
  sizeof (TCC_CONFIG),
  TCC_CONFIG_REVISION,
  TccLoadConfigDefault
};

STATIC COMPONENT_BLOCK_ENTRY  mPreMemTccBlocks = {
  &gTccPreMemConfigGuid,
  sizeof (TCC_CONFIG),
  TCC_CONFIG_REVISION,
  TccLoadConfigDefault
};

/**
  Get Tcc config block table size.

  @retval      Size of config block
**/
UINT16
TccGetConfigBlockTotalSize (
  VOID
  )
{
  return mTccBlocks.Size;
}

/**
  Add Tcc ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
TccAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mTccBlocks, 1);
}

/**
  Add Tcc ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
TccPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPreMemTccBlocks, 1);
}