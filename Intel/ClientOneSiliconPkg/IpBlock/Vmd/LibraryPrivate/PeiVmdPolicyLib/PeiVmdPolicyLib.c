/** @file
  This file provides services for PEI VMD policy default initialization

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
#include <Library/PeiVmdPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <VmdPeiConfig.h>
/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
VmdLoadPeiConfigDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  VMD_PEI_CONFIG   *VmdConfig;

  VmdConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "VmdConfig->Header.GuidHob.Name = %g\n", &VmdConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "VmdConfig->Header.GuidHob.Header.HobLength = 0x%x\n", VmdConfig->Header.GuidHob.Header.HobLength));

  VmdConfig->VmdCfgBarSz = 25;
  VmdConfig->VmdCfgBarAttr = 2;
  VmdConfig->VmdMemBarSz1 = 25;
  VmdConfig->VmdMemBar1Attr = 0;
  VmdConfig->VmdMemBarSz2 = 20;
  VmdConfig->VmdMemBar2Attr = 0;
}

static COMPONENT_BLOCK_ENTRY  mVmdIpBlock = {
  &gVmdPeiConfigGuid,  sizeof (VMD_PEI_CONFIG), VMD_PEI_CONFIG_REVISION, VmdLoadPeiConfigDefault
};

/**
  Get VMD PEI config block table total size.

  @retval     Size of VMD PEI config block table
**/
UINT16
EFIAPI
VmdGetPeiConfigBlockTotalSize (
  VOID
  )
{
  return mVmdIpBlock.Size;
}

/**
  VmdAddConfigBlocks add all Vmd PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
VmdAddPeiConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mVmdIpBlock, 1);
  return Status;
}

/**
  This function prints the Vmd PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
VmdPrintPeiPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS       Status;
  VMD_PEI_CONFIG   *VmdPeiConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gVmdPeiConfigGuid, (VOID *) &VmdPeiConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "----------------------- VMD_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", VmdPeiConfig->Header.Revision));
  ASSERT (VmdPeiConfig->Header.Revision == VMD_PEI_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " VMD Enable : %01d\n", VmdPeiConfig->VmdEnable));
  DEBUG ((DEBUG_INFO, " VMD VmdCfgBarSz : %01d\n", VmdPeiConfig->VmdCfgBarSz));
  DEBUG ((DEBUG_INFO, " VMD VmdMemBarSz1 : %01d\n", VmdPeiConfig->VmdMemBarSz1));
  DEBUG ((DEBUG_INFO, " VMD VmdMemBarSz2 : %01d\n", VmdPeiConfig->VmdMemBarSz2));
  DEBUG ((DEBUG_INFO, " VMD VmdCfgBarAttr : %01d\n", VmdPeiConfig->VmdCfgBarAttr));
  DEBUG ((DEBUG_INFO, " VMD VmdMemBar1Attr : %01d\n", VmdPeiConfig->VmdMemBar1Attr));
  DEBUG ((DEBUG_INFO, " VMD VmdMemBar2Attr : %01d\n", VmdPeiConfig->VmdMemBar2Attr));
  DEBUG ((DEBUG_INFO, "\n-------------------- VMD_CONFIG Print END -----------------\n"));
  return;
}
