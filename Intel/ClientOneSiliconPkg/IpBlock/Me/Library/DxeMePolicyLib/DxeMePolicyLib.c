/** @file
  This file is DxeMePolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include "DxeMePolicyLibrary.h"

/**
  Load default settings for ME config block in DXE phase.

  @param[in] ConfigBlockPointer                 The pointer to the config block
**/
VOID
LoadMeDxeDefault (
  IN VOID                           *ConfigBlockPointer
  );

STATIC COMPONENT_BLOCK_ENTRY  mMeIpBlocks [] = {
  {&gMeDxeConfigGuid,        sizeof (ME_DXE_CONFIG),            ME_DXE_CONFIG_REVISION,        LoadMeDxeDefault},
};

/**
  Get total size of IP list for the config block.

  @param[in] IpBlocks                   The pointer to the IP list
  @param[in] TotalIpSize                The size of IP list

  @retval                               Size of config block table
**/
STATIC
UINT16
EFIAPI
GetConfigBlockTotalSize (
  IN COMPONENT_BLOCK_ENTRY  IpBlocks [],
  IN UINTN                  TotalIpSize
  )
{
  UINT16            TotalBlockCount;
  UINT16            TotalBlockSize;
  UINT16            ConfigBlockHdrSize;
  UINT16            BlockCount;

  TotalBlockCount = (UINT16) (TotalIpSize / sizeof (COMPONENT_BLOCK_ENTRY));
  TotalBlockSize = 0;
  for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
    TotalBlockSize += (UINT32) IpBlocks[BlockCount].Size;
    DEBUG ((DEBUG_INFO, "TotalBlockSize after adding Block[0x%x]= 0x%x\n", BlockCount, TotalBlockSize));
  }
  ConfigBlockHdrSize = sizeof (CONFIG_BLOCK_TABLE_HEADER);

  return ConfigBlockHdrSize + TotalBlockSize;
}

/**
  CreateConfigBlocksByIpBlocks generates the config blocks for IP list.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in] IpBlocks                     The pointer to the IP list
  @param[in] TotalIpSize                  The size of IP list
  @param[in, out] ConfigBlockTableHeader  The pointer to the config block

  @retval EFI_SUCCESS                     The config block for IP list is created and initialized.
  @retval EFI_OUT_OF_RESOURCES            Insufficient resources to create buffer
**/
STATIC
EFI_STATUS
EFIAPI
CreateConfigBlocksByIpBlocks (
  IN COMPONENT_BLOCK_ENTRY          IpBlocks [],
  IN UINTN                          TotalIpSize,
  IN OUT CONFIG_BLOCK_TABLE_HEADER  **ConfigBlockTableHeader
  )
{
  UINT16            TotalBlockCount;
  UINT16            BlockCount;
  VOID              *ConfigBlockPointer;
  CONFIG_BLOCK      ConfigBlockBuf;
  EFI_STATUS        Status;
  UINT16            RequiredSize;
  CONFIG_BLOCK_TABLE_HEADER      *TableHeader;

  DEBUG ((DEBUG_INFO, "CreateConfigBlocksByIpBlocks\n"));

  TotalBlockCount = (UINT16) (TotalIpSize / sizeof (COMPONENT_BLOCK_ENTRY));
  DEBUG ((DEBUG_INFO, "TotalBlockCount = 0x%x\n", TotalBlockCount));

  RequiredSize = GetConfigBlockTotalSize (IpBlocks, TotalIpSize);

  Status = CreateConfigBlockTable (RequiredSize, (VOID *)&TableHeader);
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    //
    // Initialize ConfigBlockPointer to NULL
    //
    ConfigBlockPointer = NULL;
    //
    // Loop to identify each config block from IpBlocks[] Table and add each of them
    //
    for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
      CopyMem (&(ConfigBlockBuf.Header.GuidHob.Name), IpBlocks[BlockCount].Guid, sizeof (EFI_GUID));
      ConfigBlockBuf.Header.GuidHob.Header.HobLength = IpBlocks[BlockCount].Size;
      ConfigBlockBuf.Header.Revision        = IpBlocks[BlockCount].Revision;
      ConfigBlockPointer = (VOID *)&ConfigBlockBuf;
      Status = AddConfigBlock ((VOID *) TableHeader, (VOID *)&ConfigBlockPointer);
      ASSERT_EFI_ERROR (Status);
      if (IpBlocks[BlockCount].LoadDefault != NULL) {
        IpBlocks[BlockCount].LoadDefault (ConfigBlockPointer);
      }
    }
    //
    // Assignment for returning config block base address
    //
    *ConfigBlockTableHeader = TableHeader;
    return EFI_SUCCESS;
  }

  return Status;
}

/**
  Load default settings for ME config block in DXE phase.

  @param[in] ConfigBlockPointer                 The pointer to the config block
**/
VOID
LoadMeDxeDefault (
  IN VOID                           *ConfigBlockPointer
  )
{
  ME_DXE_CONFIG         *MeDxeConfig;

  MeDxeConfig = ConfigBlockPointer;

  MeDxeConfig->CoreBiosDoneEnabled        = 1;
  MeDxeConfig->ExtendMeMeasuredBoot       = 1;
}

/**
  Dump values of ME config block in DXE phase.

  @param[in] MeDxeConfig                        The pointer to the config block
**/
VOID
EFIAPI
PrintMeDxeConfig (
  IN ME_DXE_CONFIG                  *MeDxeConfig
  )
{
  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "------------------------ ME_DXE_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision            : 0x%x\n", MeDxeConfig->Header.Revision));
  ASSERT (MeDxeConfig->Header.Revision == ME_DXE_CONFIG_REVISION);

  DEBUG ((DEBUG_INFO, " MeFwDownGrade       : 0x%x\n", MeDxeConfig->MeFwDownGrade));
  DEBUG ((DEBUG_INFO, " MeJhiSupport        : 0x%x\n", MeDxeConfig->MeJhiSupport));
  DEBUG ((DEBUG_INFO, " CoreBiosDoneEnabled : 0x%x\n", MeDxeConfig->CoreBiosDoneEnabled));
  DEBUG ((DEBUG_INFO, " ExtendMeMeasuredBoot : 0x%x\n", MeDxeConfig->ExtendMeMeasuredBoot));
  DEBUG_CODE_END ();
}

/**
  This function prints the ME DXE phase policy.

  @param[in] DxeMePolicy - ME DXE Policy protocol
**/
VOID
EFIAPI
MePrintPolicyProtocol (
  IN  ME_POLICY_PROTOCOL            *DxeMePolicy
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                        Status;
  ME_DXE_CONFIG                     *MeDxeConfig;

  Status = GetConfigBlock ((VOID *) DxeMePolicy, &gMeDxeConfigGuid, (VOID *) &MeDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "\n---------------------- DxeMePolicy Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : 0x%x\n", DxeMePolicy->TableHeader.Header.Revision));
  ASSERT (DxeMePolicy->TableHeader.Header.Revision == ME_POLICY_PROTOCOL_REVISION);

  PrintMeDxeConfig (MeDxeConfig);

  DEBUG ((DEBUG_INFO, "\n---------------------- DxeMePolicy Print End -------------------\n"));
  DEBUG_CODE_END ();
}

/**
  CreateConfigBlocks generates the config blocksg of ME Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeMePolicy           The pointer to get ME Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
MeDxeCreateConfigBlocks (
  IN OUT  ME_POLICY_PROTOCOL            **DxeMePolicy
  )
{
  EFI_STATUS        Status;

  DEBUG ((DEBUG_INFO, "MeDxeCreateConfigBlocks\n"));
  Status = EFI_NOT_FOUND;

  Status = CreateConfigBlocksByIpBlocks (mMeIpBlocks, sizeof (mMeIpBlocks), (CONFIG_BLOCK_TABLE_HEADER **) DxeMePolicy);
  if (!EFI_ERROR (Status)) {
    //
    // Initialize Policy Revision
    //
    (*DxeMePolicy)->TableHeader.Header.Revision = ME_POLICY_PROTOCOL_REVISION;
  }

  DEBUG ((DEBUG_INFO, "MeDxeCreateConfigBlocks done, Status: %r\n", Status));
  return Status;
}

/**
  MeCreatePolicyDefaults creates the default setting of ME Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeMePolicy           The pointer to get ME Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
MeCreatePolicyDefaults (
  IN OUT  ME_POLICY_PROTOCOL            **DxeMePolicy
  )
{
  return MeDxeCreateConfigBlocks (DxeMePolicy);
}

/**
  MeInstallPolicyProtocol installs ME Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] DxeMePolicy                The pointer to ME Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
MeInstallPolicyProtocol (
  IN  EFI_HANDLE                    ImageHandle,
  IN  ME_POLICY_PROTOCOL            *DxeMePolicy
  )
{
  EFI_STATUS            Status;

  ///
  /// Print ME DXE Policy
  ///
  MePrintPolicyProtocol (DxeMePolicy);

  ///
  /// Install protocol to allow access to this Policy.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxeMePolicyGuid,
                  DxeMePolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

