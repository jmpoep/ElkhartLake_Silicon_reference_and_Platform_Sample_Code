/** @file
  This file provides services for PEI VTD policy default initialization

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
#include <Library/PeiVtdPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Library/VtdInfoLib.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadVtdDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  VTD_CONFIG   *Vtd;
  UINT8        Index;

  Vtd = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "Vtd->Header.GuidHob.Name = %g\n", &Vtd->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "Vtd->Header.GuidHob.Header.HobLength = 0x%x\n", Vtd->Header.GuidHob.Header.HobLength));

  //
  // Initialize the Vtd Configuration
  //
  for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
    Vtd->BaseAddress[Index] = GetVtdBaseAddress (Index);
  }
}


static COMPONENT_BLOCK_ENTRY  mVtdIpBlock = {
  &gVtdConfigGuid, sizeof (VTD_CONFIG), VTD_CONFIG_REVISION, LoadVtdDefault
};

/**
  Get VTD PEI config block table total size.

  @retval     Size of VTD PEI config block table
**/
UINT16
EFIAPI
VtdGetConfigBlockTotalSize (
  VOID
  )
{
  return mVtdIpBlock.Size;
}

/**
  VtdAddConfigBlocks add VTD PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
VtdAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mVtdIpBlock, 1);
  return Status;
}


/**
  This function prints the PEI phase VTD policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
VtdPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS    Status;
  VTD_CONFIG    *Vtd;
  UINT8         Index;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPreMemPpi, &gVtdConfigGuid, (VOID *) &Vtd);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ VTD_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", Vtd->Header.Revision));
  ASSERT (Vtd->Header.Revision == VTD_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " VtdDisable : 0x%x\n", Vtd->VtdDisable));
  DEBUG ((DEBUG_INFO, " X2ApicOptOut : 0x%x\n", Vtd->X2ApicOptOut));
  DEBUG ((DEBUG_INFO, " DmaControlGuarantee : 0x%x\n", Vtd->DmaControlGuarantee));
  DEBUG ((DEBUG_INFO, " VtdIgdEnable : 0x%x\n", Vtd->VtdIgdEnable));
  DEBUG ((DEBUG_INFO, " VtdIopEnable : 0x%x\n", Vtd->VtdIopEnable));
  for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
    DEBUG ((DEBUG_INFO, " VtdBaseAddress[%d] : 0x%x\n", Index, Vtd->BaseAddress[Index]));
  }
  DEBUG_CODE_END ();
  return;
}
