/** @file
  This file provides services for PEI Graphics policy default initialization

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/PeiGraphicsPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Register/IgdRegs.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadGraphicsPeiPreMemDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GRAPHICS_PEI_PREMEM_CONFIG                         *GtPreMemConfig;

  GtPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GtPreMemConfig->Header.GuidHob.Name = %g\n", &GtPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GtPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GtPreMemConfig->Header.GuidHob.Header.HobLength));

  ///
  /// Initialize GttSize
  ///
  GtPreMemConfig->GmAdr               = 0xB0000000;
  GtPreMemConfig->GttMmAdr            = 0xAF000000;
  GtPreMemConfig->GttSize             = 3;
  GtPreMemConfig->IgdDvmt50PreAlloc   = 254;
  GtPreMemConfig->InternalGraphics    = 2;
  GtPreMemConfig->PrimaryDisplay      = 3;
  GtPreMemConfig->ApertureSize        = SA_GT_APERTURE_SIZE_256MB;
  GtPreMemConfig->PanelPowerEnable    = 1;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadGraphicsPeiDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GRAPHICS_PEI_CONFIG                         *GtConfig;

  GtConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GtConfig->Header.GuidHob.Name = %g\n", &GtConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GtConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GtConfig->Header.GuidHob.Header.HobLength));

  //
  // Initialize the Graphics configuration
  //
  GtConfig->RenderStandby       = 1;
  GtConfig->PavpEnable          = 1;
  GtConfig->PmSupport           = 1;
  GtConfig->CdynmaxClampEnable  = 0;
  GtConfig->GtFreqMax           = 0xFF;
  GtConfig->BltBufferAddress    = NULL;

  //
  // Initialize the default VBT settings
  //
  GtConfig->DdiConfiguration.DdiPortAConfig = DdiPortAEdp;
  GtConfig->DdiConfiguration.DdiPortBConfig = DdiPortBDp;
  GtConfig->DdiConfiguration.DdiPortCConfig = DdiPortCHdmi;
  GtConfig->DdiConfiguration.DdiPortAHpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPortBHpd = DdiHpdEnable;
  GtConfig->DdiConfiguration.DdiPortCHpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPort1Hpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPort2Hpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPort3Hpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPort4Hpd = DdiHpdDisable;
  GtConfig->DdiConfiguration.DdiPortADdc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPortBDdc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPortCDdc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPort1Ddc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPort2Ddc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPort3Ddc = DdiDisable;
  GtConfig->DdiConfiguration.DdiPort4Ddc = DdiDisable;

  GtConfig->CdClock    = 0xFF; // Program Max value based on reference clock frequency
}

static COMPONENT_BLOCK_ENTRY  mGraphicsIpBlocksPreMem = {
  &gGraphicsPeiPreMemConfigGuid, sizeof (GRAPHICS_PEI_PREMEM_CONFIG), GRAPHICS_PEI_PREMEM_CONFIG_REVISION, LoadGraphicsPeiPreMemDefault
};

static COMPONENT_BLOCK_ENTRY  mGraphicsIpBlocks = {
  &gGraphicsPeiConfigGuid, sizeof (GRAPHICS_PEI_CONFIG), GRAPHICS_PEI_CONFIG_REVISION, LoadGraphicsPeiDefault
};

/**
  Get Graphics PEI config block table total size.

  @retval     Size of Graphics PEI config block table
**/
UINT16
EFIAPI
GraphicsGetConfigBlockTotalSize (
  VOID
  )
{
  return mGraphicsIpBlocks.Size;
}

/**
  Get Graphics PEI Pre-Mem config block table total size.

  @retval      Size of Graphics PEI Pre-Mem config block table
**/
UINT16
EFIAPI
GraphicsGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return mGraphicsIpBlocksPreMem.Size;
}

/**
  GraphicsAddConfigBlocksPreMem add all Graphics PEI PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GraphicsAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mGraphicsIpBlocksPreMem, 1);
  return Status;
}

/**
  GraphicsAddConfigBlocks add all Graphics PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GraphicsAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mGraphicsIpBlocks, 1);
  return Status;
}


/**
  This function prints the PEI phase Graphics PreMem policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
GraphicsPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  GRAPHICS_PEI_PREMEM_CONFIG            *GtPreMemConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ GRAPHICS_PEI_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", GtPreMemConfig->Header.Revision));
  ASSERT (GtPreMemConfig->Header.Revision == GRAPHICS_PEI_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " PanelPowerEnable : 0x%x\n", GtPreMemConfig->PanelPowerEnable));
  DEBUG ((DEBUG_INFO, " GttSize : %d MB\n", (GtPreMemConfig->GttSize == 3)? 8:(((GtPreMemConfig->GttSize == 2)? 4:2))));
  DEBUG ((DEBUG_INFO, " IgdDvmt50PreAlloc : 0x%x\n", GtPreMemConfig->IgdDvmt50PreAlloc));
  DEBUG ((DEBUG_INFO, " InternalGraphics : 0x%x\n", GtPreMemConfig->InternalGraphics));
  DEBUG ((DEBUG_INFO, " PrimaryDisplay : 0x%x\n", GtPreMemConfig->PrimaryDisplay));
  DEBUG ((DEBUG_INFO, " ApertureSize : 0x%x\n", GtPreMemConfig->ApertureSize));
  DEBUG ((DEBUG_INFO, " GtPsmiSupport : 0x%x\n", GtPreMemConfig->GtPsmiSupport));
  DEBUG ((DEBUG_INFO, " PsmiRegionSize : 0x%x\n", GtPreMemConfig->PsmiRegionSize));
  DEBUG ((DEBUG_INFO, " DismSize : 0x%x\n", GtPreMemConfig->DismSize));
  DEBUG ((DEBUG_INFO, " GttMmAdr : 0x%x\n", GtPreMemConfig->GttMmAdr));
  DEBUG ((DEBUG_INFO, " GmAdr : 0x%x\n", GtPreMemConfig->GmAdr));
  DEBUG ((DEBUG_INFO, "\n------------------------ GRAPHICS_PEI_PREMEM_CONFIG Print END -----------------\n"));
  DEBUG_CODE_END ();
  return;
}

/**
  This function prints the Graphics PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
GraphicsPrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  GRAPHICS_PEI_CONFIG                   *GtConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ GRAPHICS_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", GtConfig->Header.Revision));
  ASSERT (GtConfig->Header.Revision == GRAPHICS_PEI_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " RenderStandby : 0x%x\n", GtConfig->RenderStandby));
  DEBUG ((DEBUG_INFO, " PmSupport : 0x%x\n", GtConfig->PmSupport));
  DEBUG ((DEBUG_INFO, " PavpEnable : 0x%x\n", GtConfig->PavpEnable));
  DEBUG ((DEBUG_INFO, " CdClock : 0x%x\n", GtConfig->CdClock));
  DEBUG ((DEBUG_INFO, " SkipCdClockInit : 0x%x\n", GtConfig->SkipCdClockInit));
  DEBUG ((DEBUG_INFO, " PeiGraphicsPeimInit : 0x%x\n", GtConfig->PeiGraphicsPeimInit));
  DEBUG ((DEBUG_INFO, " LogoPtr : 0x%x\n", GtConfig->LogoPtr));
  DEBUG ((DEBUG_INFO, " LogoSize : 0x%x\n", GtConfig->LogoSize));
  DEBUG ((DEBUG_INFO, " BltBufferAdress : 0x%x\n", GtConfig->BltBufferAddress));
  DEBUG ((DEBUG_INFO, " BltBufferSize : 0x%x\n", GtConfig->BltBufferSize));
  DEBUG ((DEBUG_INFO, " GraphicsConfigPtr : 0x%x\n", GtConfig->GraphicsConfigPtr));
  DEBUG ((DEBUG_INFO, " CdynmaxClampEnable : 0x%x\n", GtConfig->CdynmaxClampEnable));
  DEBUG ((DEBUG_INFO, " GtFreqMax : 0x%x\n", GtConfig->GtFreqMax));
  DEBUG ((DEBUG_INFO, " DisableTurboGt : 0x%x\n", GtConfig->DisableTurboGt));
  DEBUG ((DEBUG_INFO, " DdiPortAConfig : 0x%x\n", GtConfig->DdiConfiguration.DdiPortAConfig));
  DEBUG((DEBUG_INFO, " DdiPortBConfig : 0x%x\n", GtConfig->DdiConfiguration.DdiPortBConfig));
  DEBUG((DEBUG_INFO, " DdiPortCConfig : 0x%x\n", GtConfig->DdiConfiguration.DdiPortCConfig));
  DEBUG ((DEBUG_INFO, " DdiPortAHpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPortAHpd));
  DEBUG ((DEBUG_INFO, " DdiPortBHpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPortBHpd));
  DEBUG ((DEBUG_INFO, " DdiPortCHpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPortCHpd));
  DEBUG ((DEBUG_INFO, " DdiPort1Hpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPort1Hpd));
  DEBUG ((DEBUG_INFO, " DdiPort2Hpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPort2Hpd));
  DEBUG ((DEBUG_INFO, " DdiPort3Hpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPort3Hpd));
  DEBUG ((DEBUG_INFO, " DdiPort4Hpd : 0x%x\n", GtConfig->DdiConfiguration.DdiPort4Hpd));
  DEBUG ((DEBUG_INFO, " DdiPortADdc : 0x%x\n", GtConfig->DdiConfiguration.DdiPortADdc));
  DEBUG ((DEBUG_INFO, " DdiPortBDdc : 0x%x\n", GtConfig->DdiConfiguration.DdiPortBDdc));
  DEBUG ((DEBUG_INFO, " DdiPortCDdc : 0x%x\n", GtConfig->DdiConfiguration.DdiPortCDdc));
  DEBUG ((DEBUG_INFO, " DdiPort1Ddc : 0x%x\n", GtConfig->DdiConfiguration.DdiPort1Ddc));
  DEBUG ((DEBUG_INFO, " DdiPort2Ddc : 0x%x\n", GtConfig->DdiConfiguration.DdiPort2Ddc));
  DEBUG ((DEBUG_INFO, " DdiPort3Ddc : 0x%x\n", GtConfig->DdiConfiguration.DdiPort3Ddc));
  DEBUG ((DEBUG_INFO, " DdiPort4Ddc : 0x%x\n", GtConfig->DdiConfiguration.DdiPort4Ddc));
  DEBUG ((DEBUG_INFO, "\n------------------------ GRAPHICS_PEI_CONFIG Print END -----------------\n"));

  DEBUG_CODE_END ();
  return;
}