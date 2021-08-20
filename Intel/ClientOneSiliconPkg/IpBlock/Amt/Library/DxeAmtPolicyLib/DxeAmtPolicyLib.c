/** @file
  This file is DxeAmtPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HobLib.h>
#include <Library/SiConfigBlockLib.h>
#include <AmtConfig.h>
#include <Protocol/AmtPolicy.h>
#include <MeBiosPayloadHob.h>
#include <MebxDataHob.h>

VOID
LoadAmtDxeConfigDefault (
  IN VOID          *ConfigBlockPointer
  );

GLOBAL_REMOVE_IF_UNREFERENCED COMPONENT_BLOCK_ENTRY   mAmtDxeIpBlocks [] = {
  {&gAmtDxeConfigGuid,       sizeof (AMT_DXE_CONFIG),           AMT_DXE_CONFIG_REVISION,       LoadAmtDxeConfigDefault},
};

/**
  Load DXE Config block default for AMT

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadAmtDxeConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  AMT_DXE_CONFIG                  *AmtDxeConfig;

  AmtDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "AmtDxeConfig->Header.GuidHob.Name = %g\n", &AmtDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "AmtDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", AmtDxeConfig->Header.GuidHob.Header.HobLength));
}


/**
  Dump values of AMT config block in DXE phase.

  @param[in] AmtDxeConfig                       The pointer to the config block
**/
VOID
EFIAPI
PrintAmtDxeConfig (
  IN  AMT_DXE_CONFIG                *AmtDxeConfig
  )
{
  DEBUG ((DEBUG_INFO, "------------------------ AMT_DXE_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision                 : 0x%x\n", AmtDxeConfig->Header.Revision));
  ASSERT (AmtDxeConfig->Header.Revision == AMT_DXE_CONFIG_REVISION);

  DEBUG ((DEBUG_INFO, " CiraRequest              : 0x%x\n", AmtDxeConfig->CiraRequest));
  DEBUG ((DEBUG_INFO, " UnConfigureMe            : 0x%x\n", AmtDxeConfig->UnConfigureMe));
  DEBUG ((DEBUG_INFO, " MebxDebugMsg             : 0x%x\n", AmtDxeConfig->MebxDebugMsg));
  DEBUG ((DEBUG_INFO, " HideUnConfigureMeConfirm : 0x%x\n", AmtDxeConfig->HideUnConfigureMeConfirm));
  DEBUG ((DEBUG_INFO, " UsbProvision             : 0x%x\n", AmtDxeConfig->UsbProvision));
  DEBUG ((DEBUG_INFO, " AmtbxHotkeyPressed       : 0x%x\n", AmtDxeConfig->AmtbxHotkeyPressed));
  DEBUG ((DEBUG_INFO, " AmtbxSelectionScreen     : 0x%x\n", AmtDxeConfig->AmtbxSelectionScreen));
  DEBUG ((DEBUG_INFO, " CiraTimeout              : 0x%x\n", AmtDxeConfig->CiraTimeout));
  DEBUG ((DEBUG_INFO, " CpuReplacementTimeout    : 0x%x\n", AmtDxeConfig->CpuReplacementTimeout));
  DEBUG ((DEBUG_INFO, " MebxNonUiTextMode        : 0x%x\n", AmtDxeConfig->MebxNonUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxUiTextMode           : 0x%x\n", AmtDxeConfig->MebxUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxGraphicsMode         : 0x%x\n", AmtDxeConfig->MebxGraphicsMode));
}

/**
  This function prints the AMT DXE phase policy.

  @param[in] DxeAmtPolicy - AMT DXE Policy protocol
**/
VOID
AmtPrintPolicyProtocol (
  IN  AMT_POLICY_PROTOCOL     *DxeAmtPolicy
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                        Status;
  AMT_DXE_CONFIG                    *AmtDxeConfig;

  Status = GetConfigBlock ((VOID *) DxeAmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "\n------------------------ AmtPolicy Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : 0x%x\n", DxeAmtPolicy->TableHeader.Header.Revision));
  ASSERT (DxeAmtPolicy->TableHeader.Header.Revision == AMT_POLICY_PROTOCOL_REVISION);

  PrintAmtDxeConfig (AmtDxeConfig);

  DEBUG ((DEBUG_INFO, "\n------------------------ AmtPolicy Print End -------------------\n"));
  DEBUG_CODE_END ();
}

/**
  CreateConfigBlocks generates the config blocksg of AMT Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeAmtPolicy          The pointer to get AMT Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
AmtCreatePolicyDefaults (
  IN OUT  AMT_POLICY_PROTOCOL       **DxeAmtPolicy
  )
{
  ME_BIOS_PAYLOAD_HOB    *MbpHob;
  UINT16                 TotalBlockSize;
  EFI_STATUS             Status;
  AMT_POLICY_PROTOCOL    *AmtPolicyInit;
  UINT16                 RequiredSize;
  EFI_HOB_GUID_TYPE      *GuidHob;
  AMT_PEI_CONFIG         *AmtPeiConfig;

  DEBUG ((DEBUG_INFO, "AMT Create Dxe Config Blocks\n"));
  AmtPolicyInit  = NULL;
  MbpHob         = NULL;
  TotalBlockSize = 0;
  RequiredSize   = 0;
  Status         = EFI_UNSUPPORTED;

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "No MBP Data Protocol available\n"));
    return EFI_UNSUPPORTED;
  }

  if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeCorporateFw) {
    DEBUG ((DEBUG_INFO, "Current ME FW is not Corporate SKU, Amt Policy protocol is not installed then.\n"));
    return EFI_UNSUPPORTED;
  }

  GuidHob = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (GuidHob == NULL) {
    return EFI_UNSUPPORTED;
  }
  AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (GuidHob);
  if (AmtPeiConfig->AmtEnabled == 0) {
    DEBUG ((DEBUG_INFO, "AMT feature is disabled from setup, Amt Policy protocol is not installed.\n"));
    return EFI_UNSUPPORTED;
  }

  TotalBlockSize = GetComponentConfigBlockTotalSize (&mAmtDxeIpBlocks[0], sizeof (mAmtDxeIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
  DEBUG ((DEBUG_INFO, "TotalBlockSize = 0x%x\n", TotalBlockSize));
  RequiredSize = sizeof (CONFIG_BLOCK_TABLE_HEADER) + TotalBlockSize;

  Status = CreateConfigBlockTable (RequiredSize, (VOID *) &AmtPolicyInit);
  ASSERT_EFI_ERROR (Status);

  //
  // General initialization
  //
  AmtPolicyInit->TableHeader.Header.Revision = AMT_POLICY_PROTOCOL_REVISION;
  //
  // Add config blocks.
  //
  Status =  AddComponentConfigBlocks ((VOID *) AmtPolicyInit, &mAmtDxeIpBlocks[0], sizeof (mAmtDxeIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
  ASSERT_EFI_ERROR (Status);

  //
  // Assignment for returning SaInitPolicy config block base address
  //
  *DxeAmtPolicy = AmtPolicyInit;
  return Status;
}

/**
  AmtInstallPolicyProtocol installs Amt Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] DxeAmtPolicy               The pointer to Amt Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
AmtInstallPolicyProtocol (
  IN  EFI_HANDLE                        ImageHandle,
  IN  AMT_POLICY_PROTOCOL               *DxeAmtPolicy
  )
{
  EFI_STATUS            Status;

  ///
  /// Print Amt DXE Policy
  ///
  AmtPrintPolicyProtocol (DxeAmtPolicy);

  ///
  /// Install protocol to allow access to this Policy.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxeAmtPolicyGuid,
                  DxeAmtPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

