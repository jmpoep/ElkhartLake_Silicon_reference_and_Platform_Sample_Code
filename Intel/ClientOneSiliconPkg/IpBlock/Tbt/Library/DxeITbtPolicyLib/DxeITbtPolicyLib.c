/** @file
  This file is DxeITbtPolicy library.

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
#include <DxeITbtPolicyLibrary.h>
#include <ITbtInfoHob.h>
#include <Protocol/ITbtPolicy.h>
#include <DxeITbtConfig.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>

/**
  Print DXE ITBT Policy

  @param[in]  ITbtPolicy                The pointer to get iTBT DXE Protocol instance
**/
VOID
ITbtPrintDxePolicyConfig (
  IN  ITBT_POLICY_PROTOCOL              *ITbtPolicy
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  UINT8                                 Index;
  DXE_ITBT_CONFIG                       *DxeITbtConfig;

  DEBUG ((DEBUG_INFO, "[TBT] ITbtPrintDxePolicyConfig Start\n"));

  DxeITbtConfig = NULL;
  Status = EFI_NOT_FOUND;
  Status = GetConfigBlock ((VOID *) ITbtPolicy, &gDxeITbtConfigGuid, (VOID *)&DxeITbtConfig);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "DxeITbtConfig is not created\n"));
    return;
  }
  //
  // Print ITBT Policy
  //
  if (DxeITbtConfig != NULL) {
    DEBUG ((DEBUG_INFO, "------------------ ITBT Policy (DXE) Print BEGIN ------------------\n"));
    DEBUG ((DEBUG_INFO, "Revision : 0x%x\n", DxeITbtConfig->Header.Revision));
    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtResourceConfig[%x].ITbtPcieExtraBusRsvd = %x\n", Index, DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieExtraBusRsvd));
      DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtResourceConfig[%x].ITbtPcieMemRsvd = %x\n", Index, DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemRsvd));
      DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtResourceConfig[%x].ITbtPcieMemAddrRngMax = %x\n", Index, DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemAddrRngMax));
      DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtResourceConfig[%x].ITbtPciePMemRsvd = %x\n", Index, DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemRsvd));
      DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtResourceConfig[%x].ITbtPciePMemAddrRngMax = %x\n", Index, DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemAddrRngMax));
    }
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtAspm = %x\n", DxeITbtConfig->TbtCommonConfig.TbtAspm));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtL1SubStates = %x\n", DxeITbtConfig->TbtCommonConfig.TbtL1SubStates));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtHotNotify = %x\n", DxeITbtConfig->TbtCommonConfig.TbtHotNotify));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtHotSMI = %x\n", DxeITbtConfig->TbtCommonConfig.TbtHotSMI));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtLtr = %x\n", DxeITbtConfig->TbtCommonConfig.TbtLtr));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtPtm = %x\n", DxeITbtConfig->TbtCommonConfig.TbtPtm));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtSetClkReq = %x\n", DxeITbtConfig->TbtCommonConfig.TbtSetClkReq));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->TbtCommonConfig.TbtVtdBaseSecurity = %x\n", DxeITbtConfig->TbtCommonConfig.TbtVtdBaseSecurity));

    DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtGenericConfig.ITbtRtd3 = %x\n", DxeITbtConfig->ITbtGenericConfig.ITbtRtd3));
    DEBUG ((DEBUG_INFO, "DxeITbtConfig->ITbtGenericConfig.ITbtRtd3ExitDelay = %x\n", DxeITbtConfig->ITbtGenericConfig.ITbtRtd3ExitDelay));
    DEBUG ((DEBUG_INFO, "\n------------------ITBT Policy (DXE) Print END --------------------\n"));
  }
  DEBUG_CODE_END ();
  return;
}

EFI_STATUS
EFIAPI
LoadITbtDxeDefault (
  IN VOID                               *ConfigBlockPointer
  )
{
  DXE_ITBT_CONFIG                        *DxeITbtConfig;
  UINT8                                  Index;

  DxeITbtConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "DxeITbtConfig->Header.GuidHob.Name = %g\n", &DxeITbtConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "DxeITbtConfig->Header.GuidHob.Header.HobLength = 0x%x\n", DxeITbtConfig->Header.GuidHob.Header.HobLength));

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieExtraBusRsvd   = 42;
    DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemRsvd        = 194;
    DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemAddrRngMax  = 25;  // 32 MB Allignment
    DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemRsvd       = 448;
    DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemAddrRngMax = 28;  // 256 MB Allignment
  }

  DxeITbtConfig->TbtCommonConfig.TbtVtdBaseSecurity = 0;
  DxeITbtConfig->ITbtGenericConfig.ITbtRtd3 = 0;

  return EFI_SUCCESS;
}


/**
  LoadITbtDxeConfigBlockDefault - Initialize default settings for each ITBT Config block

  @param[in] ConfigBlockPointer         The buffer pointer that will be initialized as specific config block
  @param[in] BlockId                    Request to initialize defaults of specified config block by given Block ID

  @retval EFI_SUCCESS                   The given buffer has contained the defaults of requested config block
  @retval EFI_NOT_FOUND                 Block ID is not defined so no default Config block will be initialized
**/
EFI_STATUS
EFIAPI
LoadITbtDxeConfigBlockDefault (
  IN  VOID                              *ConfigBlockPointer,
  IN  EFI_GUID                          BlockGuid
  )
{
  if (CompareGuid (&BlockGuid, &gDxeITbtConfigGuid)) {
    LoadITbtDxeDefault (ConfigBlockPointer);
  } else {
    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  CreateITbtDxeConfigBlocks generates the config blocksg of iTBT DXE Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] ITbtPolicy                The pointer to get iTBT DXE Protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CreateITbtDxeConfigBlocks (
  IN OUT  ITBT_POLICY_PROTOCOL          **ITbtPolicy
  )
{
  UINT16                                TotalBlockSize;
  UINT16                                TotalBlockCount;
  UINT16                                BlockCount;
  VOID                                  *ConfigBlockPointer;
  EFI_STATUS                            Status;
  ITBT_POLICY_PROTOCOL                  *ITbtInitPolicy;
  UINT16                                RequiredSize;
  STATIC CONFIG_BLOCK_HEADER            ITbtDxeIpBlocks [] = {
       {{{0, sizeof (DXE_ITBT_CONFIG),  0},  {0}},     DXE_ITBT_CONFIG_REVISION,         0, {0, 0}}
  };

  ITbtInitPolicy = NULL;
  TotalBlockCount = sizeof (ITbtDxeIpBlocks) / sizeof (CONFIG_BLOCK_HEADER);
  DEBUG ((DEBUG_INFO, "TotalBlockCount = 0x%x\n", TotalBlockCount));

  TotalBlockSize = 0;
  for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
    TotalBlockSize += (UINT32) ITbtDxeIpBlocks[BlockCount].GuidHob.Header.HobLength;
    DEBUG ((DEBUG_INFO, "TotalBlockSize after adding  Block[0x%x]= 0x%x\n", BlockCount, TotalBlockSize));
  }

  RequiredSize = sizeof (CONFIG_BLOCK_TABLE_HEADER) + TotalBlockSize;

  Status = CreateConfigBlockTable (RequiredSize, (VOID *)&ITbtInitPolicy);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    //
    // Initalize SklSaIpBlocks table GUID
    //
    CopyMem (&ITbtDxeIpBlocks[0].GuidHob.Name,  &gDxeITbtConfigGuid,    sizeof (EFI_GUID));
    //
    // Initialize Policy Revision
    //
    ITbtInitPolicy->TableHeader.Header.Revision = ITBT_POLICY_PROTOCOL_REVISION;
    //
    // Initialize ConfigBlockPointer to NULL
    //
    ConfigBlockPointer = NULL;
    //
    // Loop to identify each config block from ITbtDxeIpBlocks[] Table and add each of them
    //
    for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
      ConfigBlockPointer = (VOID *)&ITbtDxeIpBlocks[BlockCount];
      Status = AddConfigBlock ((VOID *) ITbtInitPolicy, (VOID *)&ConfigBlockPointer);
      ASSERT_EFI_ERROR (Status);
      if (!EFI_ERROR (Status)) {
        LoadITbtDxeConfigBlockDefault ((VOID *) ConfigBlockPointer, ITbtDxeIpBlocks[BlockCount].GuidHob.Name);
      }
    }
    //
    // Assignment for returning ITbtPolicy config block base address
    //
    *ITbtPolicy = ITbtInitPolicy;

  }
  return Status;
}

/**
  ITbtInstallPolicyProtocol installs iTBT Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] ITbtPolicy                 The pointer to TBT Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
ITbtInstallPolicyProtocol (
  IN  EFI_HANDLE                        ImageHandle,
  IN  ITBT_POLICY_PROTOCOL              *ITbtPolicy
  )
{
  EFI_STATUS                            Status;

  //
  // Print TBT DXE Policy
  //
  ITbtPrintDxePolicyConfig (ITbtPolicy);

  //
  // Install protocol to allow access to this Policy.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gITbtPolicyProtocolGuid,
                  ITbtPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
