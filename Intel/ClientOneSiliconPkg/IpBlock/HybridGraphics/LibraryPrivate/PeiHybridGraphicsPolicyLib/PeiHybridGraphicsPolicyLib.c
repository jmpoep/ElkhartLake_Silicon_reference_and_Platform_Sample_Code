/** @file
  This file provides services for PEI HybridGraphics policy default initialization

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
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadHybridGraphichsDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  HYBRID_GRAPHICS_CONFIG        *HgConfig;
  HgConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "HgConfig->Header.GuidHob.Name = %g\n", &HgConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "HgConfig->Header.GuidHob.Header.HobLength = 0x%x\n", HgConfig->Header.GuidHob.Header.HobLength));
  HgConfig->CpuPcie0Rtd3Gpio.GpioSupport    = NotSupported;
  HgConfig->HgDelayAfterHoldReset = 100; //100ms
  HgConfig->HgDelayAfterPwrEn = 300; //300ms
}

static COMPONENT_BLOCK_ENTRY  mHybridGraphicsIpBlocks = {
  &gHybridGraphicsConfigGuid, sizeof (HYBRID_GRAPHICS_CONFIG), HYBRID_GRAPHICS_CONFIG_REVISION, LoadHybridGraphichsDefault
};

/**
  Get Hybrid Graphics PEI config block table total size.

  @retval      Size of HybridGraphics PEI Pre-Mem config block table
**/
UINT16
EFIAPI
HybridGraphicsGetConfigBlockTotalSize (
  VOID
  )
{
  return mHybridGraphicsIpBlocks.Size;
}

/**
  HybridGraphicsAddConfigBlocks add all Hybrid Graphics PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
HybridGraphicsAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mHybridGraphicsIpBlocks, 1);
  return Status;
}

/**
  This function prints the Hybrid Graphics PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
HybridGraphicsPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  HYBRID_GRAPHICS_CONFIG                *HgConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //

  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gHybridGraphicsConfigGuid, (VOID *)&HgConfig);
  ASSERT_EFI_ERROR(Status);

  DEBUG((DEBUG_INFO, "------------------------ HYBRID_GRAPHICS_CONFIG -----------------\n"));
  DEBUG((DEBUG_INFO, " Revision : %d\n", HgConfig->Header.Revision));
  ASSERT(HgConfig->Header.Revision == HYBRID_GRAPHICS_CONFIG_REVISION);
  DEBUG((DEBUG_INFO, " HgConfig->CpuPcie0Rtd3Gpio.GpioSupport : 0x%x\n", HgConfig->CpuPcie0Rtd3Gpio.GpioSupport));
  DEBUG((DEBUG_INFO, " HgMode     : %d\n", HgConfig->HgMode));
  DEBUG((DEBUG_INFO, "------------------------ HG_DELAY_OPTIMIZATION_DATA -----------------\n"));
  DEBUG((DEBUG_INFO, " SaRtd3.HgDelayAfterHoldReset : 0x%x\n", HgConfig->HgDelayAfterHoldReset));
  DEBUG((DEBUG_INFO, " SaRtd3.HgDelayAfterPwrEn     : 0x%x\n", HgConfig->HgDelayAfterPwrEn));
  DEBUG((DEBUG_INFO, "------------------------ HYBRID_GRAPHICS_CONFIG print END -----------------\n"));

  DEBUG_CODE_END ();
  return;
}