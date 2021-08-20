/** @file
  This file provides services for PEI PCIe Rp policy default initialization

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
#include <Library/PeiPcieRpPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <PciePreMemConfig.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>

static COMPONENT_BLOCK_ENTRY  mPcieIpBlocksPreMem [] = {
  {&gPciePreMemConfigGuid,            sizeof (PCIE_PREMEM_CONFIG),  PCIE_PREMEM_CONFIG_REVISION,  LoadPciePreMemConfigBlockDefault}
};

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPciePreMemConfigBlockDefault (
  IN VOID              *ConfigBlockPointer
  )
{
  PCIE_PREMEM_CONFIG     *PciePreMemConfig;

  PciePreMemConfig     = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PciePreMemConfig->Header.GuidHob.Name = %g\n", &PciePreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PciePreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PciePreMemConfig->Header.GuidHob.Header.HobLength));
}

/**
  Get PCIe PreMem config block table total size.

  @retval  Size of SI PreMem config block table
**/
UINT16
PcieGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return (UINT16) sizeof (PCIE_PREMEM_CONFIG);
}

/**
  Add the PCIe PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PcieAddConfigBlocksPreMem (
  IN  VOID          *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "PCIe AddConfigBlocks\n"));
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPcieIpBlocksPreMem[0], sizeof (mPcieIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Print PCIe PreMem Config block

  @param[in] SiPreMemPolicyPpi          The RC PREMEM Policy PPI instance
**/
VOID
PciePreMemPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                        Status;
  PCIE_PREMEM_CONFIG                *PciePreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPciePreMemConfigGuid, (VOID *) &PciePreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "---------------------- PCIe Pre-Mem Config Block Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, "PcieImrEnabled = %x\n", PciePreMemConfig->PcieImr.ImrEnabled));
  DEBUG ((DEBUG_INFO, "PcieImrRpLocation = %x\n", PciePreMemConfig->PcieImr.ImrRpLocation));
  DEBUG ((DEBUG_INFO, "PcieImrSize = %x\n", PciePreMemConfig->PcieImr.ImrSize));
  DEBUG ((DEBUG_INFO, "PcieImrRpSelection = %x\n", PciePreMemConfig->PcieImr.ImrRpSelection));
  DEBUG ((DEBUG_INFO, "---------------------- PCIe Pre-Mem Config Block Print End -------------------\n"));
}