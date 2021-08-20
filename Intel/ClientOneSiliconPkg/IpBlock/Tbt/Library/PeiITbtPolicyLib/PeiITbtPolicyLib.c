/** @file
  This file is PeiITbtPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <PeiITbtPolicyLibrary.h>
#include <SaRegs.h>

VOID
LoadTbtPeiDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  PEI_ITBT_CONFIG            *ITbtPeiConfig;
  UINT8                      Index;

  ITbtPeiConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "ITbtPeiConfig->Header.GuidHob.Name = %g\n", &ITbtPeiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "ITbtPeiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", ITbtPeiConfig->Header.GuidHob.Header.HobLength));

  //
  // Load iTbt default. ForcePowerOnTimeout = 500 ms, ConnectTopologyTimeout = 5 seconds
  //
  ITbtPeiConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs = 500;
  ITbtPeiConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs = 50;

  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index ++) {
    ITbtPeiConfig->ITbtDmaLtr[Index] = 0x97FF;
  }
}

static COMPONENT_BLOCK_ENTRY  mTbtIpBlocks [] = {
  {&gPeiITbtConfigGuid,       sizeof (PEI_ITBT_CONFIG),   PEI_ITBT_CONFIG_REVISION,      LoadTbtPeiDefault}
};

/**
  Get TBT config block table total size.

  @retval     Size of TBT config block table
**/
UINT16
EFIAPI
ITbtGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mTbtIpBlocks[0], sizeof (mTbtIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  ITbtAddConfigBlocks add all TBT config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add TBT config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
ITbtAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "TBT AddConfigBlocks. TotalBlockCount = 0x%x\n",  sizeof (mTbtIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY)));

  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mTbtIpBlocks[0], sizeof (mTbtIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}
