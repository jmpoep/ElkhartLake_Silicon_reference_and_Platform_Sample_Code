/** @file
  This file provides services for PEI Telemetry policy default initialization

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
#include <Ppi/SiPolicy.h>
#include <TelemetryPeiConfig.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TelemetryLoadPeiConfigPreMemDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  TELEMETRY_PEI_PREMEM_CONFIG   *TelemetryPreMemConfig;

  TelemetryPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "TelemetryConfig->Header.GuidHob.Name = %g\n", &TelemetryPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TelemetryConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TelemetryPreMemConfig->Header.GuidHob.Header.HobLength));

  TelemetryPreMemConfig->CpuCrashLogDevice = 1;
}

static COMPONENT_BLOCK_ENTRY  mTelemetryIpBlockPreMem = {
  &gTelemetryPeiPreMemConfigGuid,  sizeof (TELEMETRY_PEI_PREMEM_CONFIG), TELEMETRY_PEI_PREMEM_CONFIG_REVISION, TelemetryLoadPeiConfigPreMemDefault
};

/**
  Get Telemetry PEI PreMem config block table total size.

  @retval     Size of Telemetry PEI PreMem config block table
**/
UINT16
EFIAPI
TelemetryGetPeiConfigBlockTotalSizePreMem (
  VOID
  )
{
  return mTelemetryIpBlockPreMem.Size;
}

/**
  TelemetryAddPeiConfigBlockPreMem add all Telemetry PreMem PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
TelemetryAddPeiConfigBlockPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mTelemetryIpBlockPreMem, 1);
  return Status;
}

/**
  This function prints the Telemetry PreMem PEI phase policy.

  @param[in] SiPreMemPolicyPpi    Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
TelemetryPrintPeiPolicyPpiPreMem (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                    Status;
  TELEMETRY_PEI_PREMEM_CONFIG   *TelemetryPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gTelemetryPeiPreMemConfigGuid, (VOID *) &TelemetryPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "----------------------- Telemetry_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", TelemetryPreMemConfig->Header.Revision));
  ASSERT (TelemetryPreMemConfig->Header.Revision == TELEMETRY_PEI_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " Telemetry CpuCrashLogEnable : %01d\n", TelemetryPreMemConfig->CpuCrashLogDevice));
  DEBUG ((DEBUG_INFO, "\n-------------------- Telemetry_CONFIG Print END -----------------\n"));
  return;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TelemetryLoadPeiConfigDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  TELEMETRY_PEI_CONFIG   *TelemetryConfig;

  TelemetryConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "TelemetryConfig->Header.GuidHob.Name = %g\n", &TelemetryConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TelemetryConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TelemetryConfig->Header.GuidHob.Header.HobLength));

  TelemetryConfig->CpuCrashLogEnable = 1;
}

static COMPONENT_BLOCK_ENTRY  mTelemetryIpBlock = {
  &gTelemetryPeiConfigGuid,  sizeof (TELEMETRY_PEI_CONFIG), TELEMETRY_PEI_CONFIG_REVISION, TelemetryLoadPeiConfigDefault
};

/**
  Get Telemetry PEI config block table total size.

  @retval     Size of Telemetry PEI config block table
**/
UINT16
EFIAPI
TelemetryGetPeiConfigBlockTotalSize (
  VOID
  )
{
  return mTelemetryIpBlock.Size;
}

/**
  TelemetryAddConfigBlocks add all Telemetry PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
TelemetryAddPeiConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mTelemetryIpBlock, 1);
  return Status;
}

/**
  This function prints the Telemetry PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
TelemetryPrintPeiPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS             Status;
  TELEMETRY_PEI_CONFIG   *TelemetryPeiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTelemetryPeiConfigGuid, (VOID *) &TelemetryPeiConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "----------------------- Telemetry_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", TelemetryPeiConfig->Header.Revision));
  ASSERT (TelemetryPeiConfig->Header.Revision == TELEMETRY_PEI_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " Telemetry CpuCrashLogEnable : %01d\n", TelemetryPeiConfig->CpuCrashLogEnable));
  DEBUG ((DEBUG_INFO, "\n-------------------- Telemetry_CONFIG Print END -----------------\n"));
  return;
}
