/** @file
  This file provides services for Overclocking PEI policy function

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
#include <OverclockingConfig.h>

/**
  Print OVERCLOCKING_PREMEM_CONFIG settings.

  @param[in] SiPolicyPreMemPpi  Instance of SI_PREMEM_POLICY_PPI
**/
VOID
OcPreMemPrintConfig (
  IN CONST SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  EFI_STATUS  Status;
  OVERCLOCKING_PREMEM_CONFIG *OverClockingPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPreMemPpi, &gOverclockingPreMemConfigGuid, (VOID *) &OverClockingPreMemConfig);
  ASSERT_EFI_ERROR (Status);


  DEBUG ((DEBUG_INFO, "------------------ OverClocking PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: OcSupport : 0x%X\n", OverClockingPreMemConfig->OcSupport));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: OcLock : 0x%X\n", OverClockingPreMemConfig->OcLock));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CoreVoltageMode : 0x%X\n", OverClockingPreMemConfig->CoreVoltageMode));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CoreMaxOcRatio : 0x%X\n", OverClockingPreMemConfig->CoreMaxOcRatio));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CoreVoltageOverride : 0x%X\n", OverClockingPreMemConfig->CoreVoltageOverride));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CoreVoltageAdaptive : 0x%X\n", OverClockingPreMemConfig->CoreVoltageAdaptive));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CoreVoltageOffset : 0x%X\n", OverClockingPreMemConfig->CoreVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingVoltageMode : 0x%X\n", OverClockingPreMemConfig->RingVoltageMode));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingVoltageOverride : 0x%X\n", OverClockingPreMemConfig->RingVoltageOverride));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingVoltageAdaptive : 0x%X\n", OverClockingPreMemConfig->RingVoltageAdaptive));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingVoltageOffset : 0x%X\n", OverClockingPreMemConfig->RingVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingMaxOcRatio : 0x%X\n", OverClockingPreMemConfig->RingMaxOcRatio));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingDownBin : 0x%X\n", OverClockingPreMemConfig->RingDownBin));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: Avx2RatioOffset : 0x%X\n", OverClockingPreMemConfig->Avx2RatioOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: Avx3RatioOffset : 0x%X\n", OverClockingPreMemConfig->Avx3RatioOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: BclkAdaptiveVoltage : 0x%X\n", OverClockingPreMemConfig->BclkAdaptiveVoltage));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: CorePllVoltageOffset : 0x%X\n", OverClockingPreMemConfig->CorePllVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtPllVoltageOffset : 0x%X\n", OverClockingPreMemConfig->GtPllVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RingPllVoltageOffset : 0x%X\n", OverClockingPreMemConfig->RingPllVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: SaPllVoltageOffset : 0x%X\n", OverClockingPreMemConfig->SaPllVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: McPllVoltageOffset : 0x%X\n", OverClockingPreMemConfig->McPllVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: TjMaxOffset : 0x%X\n", OverClockingPreMemConfig->TjMaxOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: FivrFaults : 0x%X\n", OverClockingPreMemConfig->FivrFaults));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: FivrEfficiency : 0x%X\n", OverClockingPreMemConfig->FivrEfficiency));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtMaxOcRatio : 0x%x\n", OverClockingPreMemConfig->GtMaxOcRatio));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtVoltageMode : 0x%x\n", OverClockingPreMemConfig->GtVoltageMode));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtVoltageOffset : 0x%x\n", OverClockingPreMemConfig->GtVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtVoltageOverride : 0x%x\n", OverClockingPreMemConfig->GtVoltageOverride));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: GtExtraTurboVoltage : 0x%x\n", OverClockingPreMemConfig->GtExtraTurboVoltage));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: SaVoltageOffset : 0x%x\n", OverClockingPreMemConfig->SaVoltageOffset));
  DEBUG ((DEBUG_INFO, " OVERCLOCKING_PREMEM_CONFIG:: RealtimeMemoryTiming : 0x%x\n", OverClockingPreMemConfig->RealtimeMemoryTiming));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer  Pointer to config block
**/
VOID
OcLoadConfigDefault (
  IN VOID *ConfigBlockPointer
  )
{
  OVERCLOCKING_PREMEM_CONFIG *OverClockingPreMemConfig;

  OverClockingPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "OverClockingPreMemConfig->Header.GuidHob.Name = %g\n", &OverClockingPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "OverClockingPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", OverClockingPreMemConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Overclocking configuration.
  ********************************/

}

STATIC COMPONENT_BLOCK_ENTRY mOverclockingBlock = {
  &gOverclockingPreMemConfigGuid,
  sizeof (OVERCLOCKING_PREMEM_CONFIG),
  OVERCLOCKING_CONFIG_REVISION,
  OcLoadConfigDefault
};

/**
  Get Overclocking config block table size.

  @retval Size of config block
**/
UINT16
OcPreMemGetConfigBlockTotalSize (
  VOID
  )
{
  return mOverclockingBlock.Size;
}

/**
  Add Overclocking ConfigBlock.

  @param[in] ConfigBlockTableAddress The pointer to config block table

  @retval EFI_SUCCESS                The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES       Insufficient resources to create buffer
**/
EFI_STATUS
OcPreMemAddConfigBlock (
  IN VOID *ConfigBlockTableAddress
  )
{
  EFI_STATUS Status;

  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mOverclockingBlock, 1);
  return Status;
}
