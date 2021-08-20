/** @file
  This file provide services for DXE phase Graphics policy default initialization.

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

#include <Library/DxeGraphicsPolicyLib.h>

/**
  This function prints the Graphics DXE phase policy.

  @param[in] SaPolicy - SA DXE Policy protocol
**/
VOID
GraphicsDxePolicyPrint (
  IN  SA_POLICY_PROTOCOL      *SaPolicy
  )
{
  EFI_STATUS                  Status;
  GRAPHICS_DXE_CONFIG         *GraphicsDxeConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);


  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "\n------------------------ Graphics Policy (DXE) print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", GraphicsDxeConfig->Header.Revision));
  ASSERT (GraphicsDxeConfig->Header.Revision == GRAPHICS_DXE_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, "\n------------------------ Graphics Policy (DXE) print END -----------------\n"));
  DEBUG_CODE_END ();

  return;
}


/**
  This function Load default Graphics DXE policy.

  @param[in] ConfigBlockPointer    The pointer to add Graphics config block
**/
VOID
LoadIgdDxeDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  GRAPHICS_DXE_CONFIG        *GraphicsDxeConfig;

  GraphicsDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "GraphicsDxeConfig->Header.GuidHob.Name = %g\n", &GraphicsDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GraphicsDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GraphicsDxeConfig->Header.GuidHob.Header.HobLength));
  ///
  /// Initialize the Graphics configuration
  ///
  GraphicsDxeConfig->PlatformConfig           = 1;
  GraphicsDxeConfig->AlsEnable                = 2;
  GraphicsDxeConfig->BacklightControlSupport  = 2;
  GraphicsDxeConfig->IgdBlcConfig             = 2;
  GraphicsDxeConfig->IgdDvmtMemSize           = 1;
  GraphicsDxeConfig->GfxTurboIMON             = 31;
  ///
  /// <EXAMPLE> Create a static Backlight Brightness Level Duty cycle Mapping Table
  /// Possible 20 entries (example used 11), each 16 bits as follows:
  /// [15] = Field Valid bit, [14:08] = Level in Percentage (0-64h), [07:00] = Desired duty cycle (0 - FFh).
  ///
  GraphicsDxeConfig->BCLM[0] = (0x0000 + WORD_FIELD_VALID_BIT);  ///< 0%
  GraphicsDxeConfig->BCLM[1] = (0x0A19 + WORD_FIELD_VALID_BIT);  ///< 10%
  GraphicsDxeConfig->BCLM[2] = (0x1433 + WORD_FIELD_VALID_BIT);  ///< 20%
  GraphicsDxeConfig->BCLM[3] = (0x1E4C + WORD_FIELD_VALID_BIT);  ///< 30%
  GraphicsDxeConfig->BCLM[4] = (0x2866 + WORD_FIELD_VALID_BIT);  ///< 40%
  GraphicsDxeConfig->BCLM[5] = (0x327F + WORD_FIELD_VALID_BIT);  ///< 50%
  GraphicsDxeConfig->BCLM[6] = (0x3C99 + WORD_FIELD_VALID_BIT);  ///< 60%
  GraphicsDxeConfig->BCLM[7] = (0x46B2 + WORD_FIELD_VALID_BIT);  ///< 70%
  GraphicsDxeConfig->BCLM[8] = (0x50CC + WORD_FIELD_VALID_BIT);  ///< 80%
  GraphicsDxeConfig->BCLM[9] = (0x5AE5 + WORD_FIELD_VALID_BIT);  ///< 90%
  GraphicsDxeConfig->BCLM[10] = (0x64FF + WORD_FIELD_VALID_BIT);  ///< 100%
}

static COMPONENT_BLOCK_ENTRY  mGraphicsDxeIpBlocks = {
  &gGraphicsDxeConfigGuid, sizeof (GRAPHICS_DXE_CONFIG), GRAPHICS_DXE_CONFIG_REVISION, LoadIgdDxeDefault};


/**
  Get DXE Graphics config block table total size.

  @retval     Size of DXE Graphics config block table
**/
UINT16
EFIAPI
GraphicsGetConfigBlockTotalSizeDxe (
  VOID
  )
{
  return mGraphicsDxeIpBlocks.Size;
}

/**
  GraphicsAddConfigBlocksDxe add all DXE Graphics config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GraphicsAddConfigBlocksDxe (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mGraphicsDxeIpBlocks, 1);
  return Status;
}
