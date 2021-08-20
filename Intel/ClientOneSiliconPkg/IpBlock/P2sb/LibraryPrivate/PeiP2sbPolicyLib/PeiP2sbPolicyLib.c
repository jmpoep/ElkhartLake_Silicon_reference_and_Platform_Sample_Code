/** @file
  This file provides services for P2sb policy function

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
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <P2sbConfig.h>

/**
  Print PCH_P2SB_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
P2sbPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  PCH_P2SB_CONFIG   *P2sbConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ P2SB Config ------------------\n"));
  DEBUG ((DEBUG_INFO, "SbAccessUnlock= %x\n", P2sbConfig->SbAccessUnlock));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
P2sbLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_P2SB_CONFIG  *P2sbConfig;
  P2sbConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "P2sbConfig->Header.GuidHob.Name = %g\n", &P2sbConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "P2sbConfig->Header.GuidHob.Header.HobLength = 0x%x\n", P2sbConfig->Header.GuidHob.Header.HobLength));
}

STATIC COMPONENT_BLOCK_ENTRY  mP2sbBlocks = {
  &gP2sbConfigGuid,
  sizeof (PCH_P2SB_CONFIG),
  P2SB_CONFIG_REVISION,
  P2sbLoadConfigDefault
};

/**
  Get P2sb config block table size.

  @retval      Size of config block
**/
UINT16
P2sbGetConfigBlockTotalSize (
  VOID
  )
{
  return mP2sbBlocks.Size;
}

/**
  Add P2sb ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
P2sbAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mP2sbBlocks, 1);
}
