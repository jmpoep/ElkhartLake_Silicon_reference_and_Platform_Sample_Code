/** @file
   Updates Platform Information to Setup Data

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/DxeUpdatePlatformInfoLib.h>

/**

  This function update the UEFI variable "SetupVolatileData" to reflect current platform values,
  Return out if the variable is NOT found.

**/
VOID
UpdatePlatformInfo (
  VOID
  )
{

#if FixedPcdGetBool (PcdSetupEnable) == 1
  EFI_STATUS              Status;
  SETUP_VOLATILE_DATA     SetupVolatileData;
  UINT32                  SetupVolAttributes;
  UINTN                   VariableSize;
  UINT64                  HbPciD0F0RegBase;
  BOOLEAN                 HiiDataExport;

  DEBUG ((DEBUG_INFO, "UpdatePlatformInfo Start.\n"));

  HiiDataExport = FALSE;
  SetMem (&SetupVolatileData, sizeof (SETUP_VOLATILE_DATA),0);

  VariableSize = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  &SetupVolAttributes,
                  &VariableSize,
                  &SetupVolatileData
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UpdatePlatformInfo Get Variable Error.\n"));
    return;
  }

  //
  // Get VTd status
  //
  HbPciD0F0RegBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  SetupVolatileData.VTdAvailable = (PciSegmentRead32 (HbPciD0F0RegBase + 0xe4) & BIT23) ? 0 : 1;

  SetupVolatileData.PlatformFlavor = PcdGet8 (PcdPlatformFlavor);
  SetupVolatileData.FabId          = PcdGet16 (PcdBoardRev);
  SetupVolatileData.BoardBomId     = PcdGet16 (PcdBoardBomId);
  SetupVolatileData.PlatformType   = PcdGet8 (PcdPlatformType);
  SetupVolatileData.BoardType      = PcdGet8 (PcdBoardType);
  SetupVolatileData.PlatId         = (UINT16) LibPcdGetSku ();
  SetupVolatileData.PchGeneration  = PchGeneration ();
  SetupVolatileData.DockAttached   = PcdGetBool (PcdDockAttached);

  DEBUG ((DEBUG_INFO, "SetupVolatileData.PchGeneration = %d\n", SetupVolatileData.PchGeneration));
  if (HiiDataExport) {
    SetupVolAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  } else {
    SetupVolAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
  }
  Status = gRT->SetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  SetupVolAttributes,
                  sizeof (SETUP_VOLATILE_DATA),
                  &SetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "UpdatePlatformInfo End.\n"));

#else
  //
  // No Setup Data to update
  //
  DEBUG ((DEBUG_INFO, "UpdatePlatformInfo Null Function.\n"));

#endif
  return;
}
