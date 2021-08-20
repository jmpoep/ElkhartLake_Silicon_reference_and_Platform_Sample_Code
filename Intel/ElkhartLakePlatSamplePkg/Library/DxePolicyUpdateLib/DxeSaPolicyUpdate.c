/** @file
  This file is the library for SA DXE Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <DxeSaPolicyUpdate.h>

/**
  Retrieves a custom string for the SMBIOS Type 17 Table DeviceLocator field.

  @param[in]  This                          A pointer to this instance of MEMORY_DXE_CONFIG.
  @param[in]  Controller                    Desired Controller to get a DeviceLocator string for.
  @param[in]  Dimm                          Desired DIMM to get a DeviceLocator string for.
  @param[in]  MdSocket                      0 = Memory Down, 1 = Socketed.

  @retval                                   The DeviceLocator string
  @retval     NULL                          If the return value is NULL, the default value will be used.
**/
CHAR8*
EFIAPI
GetPlatformDeviceLocatorString (
  IN CONST    MEMORY_DXE_CONFIG   *This,
  IN          UINT8               Controller,
  IN          UINT8               Dimm,
  IN          UINT8               MdSocket
  )
{
  return NULL;
}

/**
  Retrieves a custom string for the SMBIOS Type 17 Table BankLocator field.

  @param[in]  This                          A pointer to this instance of MEMORY_DXE_CONFIG.
  @param[in]  Controller                    Desired Controller to get a BankLocator string for.
  @param[in]  Dimm                          Desired DIMM to get a BankLocator string for.
  @param[in]  MdSocket                      0 = Memory Down, 1 = Socketed.

  @retval                                   The BankLocator string
  @retval     NULL                          If the return value is NULL, the default value will be used.
**/
CHAR8*
EFIAPI
GetPlatformBankLocatorString (
  IN CONST    MEMORY_DXE_CONFIG   *This,
  IN          UINT8               Controller,
  IN          UINT8               Dimm,
  IN          UINT8               MdSocket
  )
{
  return NULL;
}

/**
  Get data for platform policy from setup options.

  @param[in] SaPolicy                  The pointer to get SA Policy protocol instance

  @retval EFI_SUCCESS                  Operation success.

**/
EFI_STATUS
EFIAPI
UpdateDxeSaPolicy (
  IN OUT  SA_POLICY_PROTOCOL    *SaPolicy
  )
{
  UINTN                     VariableSize;
  SA_SETUP                  SaSetup;
  SETUP_DATA                SetupVariables;
  EFI_STATUS                Status;
  GRAPHICS_DXE_CONFIG       *GraphicsDxeConfig;
  MISC_DXE_CONFIG           *MiscDxeConfig;
  MEMORY_DXE_CONFIG         *MemoryDxeConfig;

  GraphicsDxeConfig = NULL;
  MiscDxeConfig = NULL;
  MemoryDxeConfig = NULL;
  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *)SaPolicy, &gMiscDxeConfigGuid, (VOID *)&MiscDxeConfig);
  ASSERT_EFI_ERROR (Status);


  Status = GetConfigBlock ((VOID *)SaPolicy, &gMemoryDxeConfigGuid, (VOID *)&MemoryDxeConfig);
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  ZeroMem (&SetupVariables, VariableSize);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupVariables
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );
  ASSERT_EFI_ERROR (Status);


  if (PcdGetBool (PcdSpdAddressOverride)) {
    MemoryDxeConfig->SpdAddressTable[0] = DIMM_SMB_SPD_P0C0D0_STP;
    MemoryDxeConfig->SpdAddressTable[1] = DIMM_SMB_SPD_P0C0D1_STP;
    MemoryDxeConfig->SpdAddressTable[2] = DIMM_SMB_SPD_P0C1D0_STP;
    MemoryDxeConfig->SpdAddressTable[3] = DIMM_SMB_SPD_P0C1D1_STP;
  }
  MemoryDxeConfig->GetDeviceLocatorString = GetPlatformDeviceLocatorString;
  MemoryDxeConfig->GetBankLocatorString   = GetPlatformBankLocatorString;

  if (SaSetup.EnableVtd == 0) {
    MiscDxeConfig->RmrrUsbBaseAddress[0] = 0;
    MiscDxeConfig->RmrrUsbBaseAddress[1] = 0;
  }

  if (!EFI_ERROR(Status)) {
    //
    // Global NVS Graphics configuration
    //
    GraphicsDxeConfig->AlsEnable               = SaSetup.AlsEnable;
    GraphicsDxeConfig->BacklightControlSupport = SaSetup.IgdLcdBlc;
    GraphicsDxeConfig->IgdBootType             = SaSetup.IgdBootType;
    GraphicsDxeConfig->IgdPanelType            = SaSetup.LcdPanelType;
    GraphicsDxeConfig->IgdPanelScaling         = SaSetup.LcdPanelScaling;
    GraphicsDxeConfig->IgdBlcConfig            = SaSetup.IgdLcdBlc;
    GraphicsDxeConfig->IgdDvmtMemSize          = SaSetup.IgdDvmt50TotalAlloc;
    GraphicsDxeConfig->GfxTurboIMON            = SaSetup.GfxTurboIMON;
    GraphicsDxeConfig->IuerStatusVal          |= SaSetup.SlateIndicatorRT << 6;
    GraphicsDxeConfig->IuerStatusVal          |= SaSetup.DockIndicatorRT << 7;
  }

  //
  // Initialize the Memory Configuration
  //
  MemoryDxeConfig->ChannelASlotMap    = 0x01;
  MemoryDxeConfig->ChannelBSlotMap    = 0x01;

  //
  // Initialize the Platform dependent Graphics configuration.
  // Set BIT0 & BIT1 if Platform is Connected Standby capable & it's capability field is valid respectively.
  // Please refer to IGD's ACPI Opregion spec for other bit definitions.
  //
  if (SetupVariables.LowPowerS0Idle == 0) {
    GraphicsDxeConfig->PlatformConfig |= (BIT1 | BIT0);
  } else {
    GraphicsDxeConfig->PlatformConfig &= (UINT32) (~BIT0);
  }

  GraphicsDxeConfig->IuerStatusVal = 0;

  return EFI_SUCCESS;
}

