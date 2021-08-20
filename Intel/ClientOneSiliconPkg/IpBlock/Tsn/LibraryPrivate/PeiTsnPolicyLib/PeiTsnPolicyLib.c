/** @file
  This file provides services for TSN policy function

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <TsnConfig.h>

/**
  Print TSN_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
TsnPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  TSN_CONFIG        *TsnConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTsnConfigGuid, (VOID *) &TsnConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ TSN Sub Region Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Tsn Mac Address Sub Region   - Base Address = %x\n", TsnConfig->TsnSubRegion[0].BaseAddress));
  DEBUG ((DEBUG_INFO, " Tsn Mac Address Sub Region   - Size = %x\n", TsnConfig->TsnSubRegion[0].Size));
  DEBUG ((DEBUG_INFO, " Pse Tsn Ip Config Sub Region - Base Address = %x\n", TsnConfig->TsnSubRegion[1].BaseAddress));
  DEBUG ((DEBUG_INFO, " Pse Tsn Ip Config Sub Region - Size = %x\n", TsnConfig->TsnSubRegion[1].Size));
  DEBUG ((DEBUG_INFO, " Tsn Config Sub Region        - Base Address = %x\n", TsnConfig->TsnSubRegion[2].BaseAddress));
  DEBUG ((DEBUG_INFO, " Tsn Config Sub Region        - Size = %x\n", TsnConfig->TsnSubRegion[2].Size));
  DEBUG ((DEBUG_INFO, " PchTsnEnable = %x\n",          TsnConfig->PchTsnEnable));
  DEBUG ((DEBUG_INFO, " PchTsnGbeMultiVcEnable    = %d\n",    TsnConfig->PchTsnGbeMultiVcEnable));
  DEBUG ((DEBUG_INFO, " PseTsnGbeMultiVcEnable[0] = %d\n",    TsnConfig->PseTsnGbeMultiVcEnable[0]));
  DEBUG ((DEBUG_INFO, " PseTsnGbeMultiVcEnable[1] = %d\n",    TsnConfig->PseTsnGbeMultiVcEnable[1]));
  DEBUG ((DEBUG_INFO, " PchTsnGbeLinkSpeed = %d\n",    TsnConfig->PchTsnGbeLinkSpeed));
  DEBUG ((DEBUG_INFO, " PseTsnGbeLinkSpeed = %d\n",    TsnConfig->PseTsnGbeLinkSpeed[0]));
  DEBUG ((DEBUG_INFO, " PseTsnGbeLinkSpeed = %d\n",    TsnConfig->PseTsnGbeLinkSpeed[1]));
  DEBUG ((DEBUG_INFO, " PchTsnGbeSgmiiEnable = %d\n",  TsnConfig->PchTsnGbeSgmiiEnable));
  DEBUG ((DEBUG_INFO, " PseTsnGbeSgmiiEnable = %d\n",  TsnConfig->PseTsnGbeSgmiiEnable[0]));
  DEBUG ((DEBUG_INFO, " PseTsnGbeSgmiiEnable = %d\n",  TsnConfig->PseTsnGbeSgmiiEnable[1]));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TsnLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  TSN_CONFIG      *TsnConfig;
  UINT8           Index = 0;

  TsnConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "TsnConfig->Header.GuidHob.Name = %g\n", &TsnConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TsnConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TsnConfig->Header.GuidHob.Header.HobLength));

  for (Index = 0; Index < TSN_MAX_SUB_REGIONS; Index++) {
    TsnConfig->TsnSubRegion[Index].BaseAddress = 0;
    TsnConfig->TsnSubRegion[Index].Size = (UINT32) 0x0;
  }

  TsnConfig->PchTsnEnable = TRUE;
  TsnConfig->PchTsnGbeMultiVcEnable    = FALSE;
  TsnConfig->PseTsnGbeMultiVcEnable[0] = FALSE;
  TsnConfig->PseTsnGbeMultiVcEnable[1] = FALSE;
  TsnConfig->PchTsnGbeLinkSpeed        = TSN_LINK_SPEED_2_5G_34MHZ;
  TsnConfig->PseTsnGbeLinkSpeed[0]     = TSN_LINK_SPEED_1G_34MHZ;
  TsnConfig->PseTsnGbeLinkSpeed[1]     = TSN_LINK_SPEED_1G_34MHZ;
  TsnConfig->PchTsnGbeSgmiiEnable      = FALSE;
  TsnConfig->PseTsnGbeSgmiiEnable[0]   = FALSE;
  TsnConfig->PseTsnGbeSgmiiEnable[1]   = FALSE;

}

STATIC COMPONENT_BLOCK_ENTRY  mTsnBlocks = {
  &gTsnConfigGuid,
  sizeof (TSN_CONFIG),
  TSN_CONFIG_REVISION,
  TsnLoadConfigDefault
};

/**
  Get Tsn config block table size.

  @retval      Size of config block
**/
UINT16
TsnGetConfigBlockTotalSize (
  VOID
  )
{
  return mTsnBlocks.Size;
}

/**
  Add Tsn ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
TsnAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mTsnBlocks, 1);
}
