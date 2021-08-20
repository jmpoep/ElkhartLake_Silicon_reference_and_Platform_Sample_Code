/** @file
  This file provides services for PEI Gna policy default initialization

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
#include <Library/PeiGnaPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Register/GnaRegs.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadGnaDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GNA_CONFIG                        *GnaConfig;
  GnaConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GnaConfig->Header.GuidHob.Name = %g\n", &GnaConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GnaConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GnaConfig->Header.GuidHob.Header.HobLength));
  GnaConfig->GnaEnable    = TRUE;
}

static COMPONENT_BLOCK_ENTRY  mGnaIpBlocks = {
  &gGnaConfigGuid,    sizeof (GNA_CONFIG),    GNA_CONFIG_REVISION,    LoadGnaDefault
};

/**
  Get GNA PEI config block table total size.

  @retval     Size of Gna PEI config block table
**/
UINT16
EFIAPI
GnaGetConfigBlockTotalSize (
  VOID
  )
{
  return mGnaIpBlocks.Size;
}

/**
  GnaAddConfigBlocks add all Gna PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GnaAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mGnaIpBlocks, 1);
  return Status;
}

/**
  This function prints the Gna PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
GnaPrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS     Status;
  GNA_CONFIG     *GnaConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGnaConfigGuid, (VOID *) &GnaConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ GNA_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", GnaConfig->Header.Revision));
  ASSERT (GnaConfig->Header.Revision == GNA_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, "\n------------------------ GNA_CONFIG Print END -----------------\n"));
  return;
}