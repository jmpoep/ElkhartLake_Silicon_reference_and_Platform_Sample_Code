/** @file
  This file provides services for PchDmi policy function

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
#include <PchDmiConfig.h>

/**
  Print PCH_DMI_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
PchDmiPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  PCH_DMI_CONFIG    *PchDmiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPchDmiConfigGuid, (VOID *) &PchDmiConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ DMI Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " PwrOptEnable= %x\n", PchDmiConfig->PwrOptEnable));
  DEBUG ((DEBUG_INFO, " DmiAspmCtrl = %x\n", PchDmiConfig->DmiAspmCtrl));
  DEBUG ((DEBUG_INFO, " CwbEnable= %x\n", PchDmiConfig->CwbEnable));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
PchDmiLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_DMI_CONFIG   *PchDmiConfig;
  PchDmiConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PchDmiConfig->Header.GuidHob.Name = %g\n", &PchDmiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PchDmiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PchDmiConfig->Header.GuidHob.Header.HobLength));

  PchDmiConfig->DmiAspmCtrl = PchPcieAspmAutoConfig;
  PchDmiConfig->CwbEnable = 1;
}

STATIC COMPONENT_BLOCK_ENTRY  mPchDmiBlocks = {
  &gPchDmiConfigGuid,
  sizeof (PCH_DMI_CONFIG),
  PCH_DMI_CONFIG_REVISION,
  PchDmiLoadConfigDefault
};

/**
  Get PchDmi config block table size.

  @retval      Size of config block
**/
UINT16
PchDmiGetConfigBlockTotalSize (
  VOID
  )
{
  return mPchDmiBlocks.Size;
}

/**
  Add PchDmi ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PchDmiAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPchDmiBlocks, 1);
}
