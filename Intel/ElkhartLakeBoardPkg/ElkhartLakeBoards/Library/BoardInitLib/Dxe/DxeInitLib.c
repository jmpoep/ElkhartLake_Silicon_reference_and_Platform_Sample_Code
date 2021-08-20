/** @file

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

#include <Uefi.h>

#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeUpdatePlatformInfoLib.h>
#include <Library/SetupInitLib.h>
#include <MemInfoHob.h>
#include <PlatformBoardConfig.h>
#include <PlatformBoardId.h>
#include <Pins/GpioPinsVer3.h>
#include <PcieRegs.h>
#include <Register/PchRegs.h>
#include <Library/PciSegmentLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BoardConfigLib.h>

#include <ElkhartLakeBoardConfigPatchTable.h>

EFI_STATUS
PatchConfigurationDataInit (
  IN CONFIG_PATCH_STRUCTURE  *ConfigPatchStruct,
  IN UINTN                   ConfigPatchStructSize
  );

VOID
EhlInitPatchConfigurationData (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16(PcdBoardId);
  UINTN     ConfigPatchStructSize;
  CONFIG_PATCH_STRUCTURE *PatchTable;
  UINTN                  PatchTableSize;

  PatchTable     = NULL;
  PatchTableSize = 0;

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdJslLp4xType4Rvp1:
      ConfigPatchStructSize = SIZE_OF_TABLE (mElkhartlakeDdr4RvpConfigPatchStruct, CONFIG_PATCH_STRUCTURE);
      UpdatePatchTable (&PatchTable, &PatchTableSize, mElkhartlakeDdr4RvpConfigPatchStruct, ConfigPatchStructSize);
      break;

    case BoardIdEhlLp4xType3Crb:
      ConfigPatchStructSize = SIZE_OF_TABLE (mElkhartlakeCRBConfigPatchStruct, CONFIG_PATCH_STRUCTURE);
      UpdatePatchTable (&PatchTable, &PatchTableSize, mElkhartlakeCRBConfigPatchStruct, ConfigPatchStructSize);
      break;

    case BoardIdJslLp4xErb:
      ConfigPatchStructSize = SIZE_OF_TABLE (mElkhartlakeDdr4RvpConfigPatchStruct, CONFIG_PATCH_STRUCTURE);
      UpdatePatchTable (&PatchTable, &PatchTableSize, mElkhartlakeDdr4RvpConfigPatchStruct, ConfigPatchStructSize);
      break;

    default:
      break;
  }
  PatchConfigurationDataInit (PatchTable, PatchTableSize);
  FreePatchTable (&PatchTable, &PatchTableSize);
}

//
// Null function for nothing GOP VBT update.
//
VOID
EhlGopVbtSpecificUpdateNull (
  VOID
  )
{

}

STATIC
EFI_STATUS
BoardHookPlatformSetup (
  VOID * Content
  )
{
  ((SETUP_VOLATILE_DATA *)Content)->PlatId = PcdGet16 (PcdBoardId);

  return RETURN_SUCCESS;
}

/**
 Init Misc Platform Board Config Block.

 @param[in]  VOID

 @retval VOID
**/
VOID
EhlBoardMiscInit (
  VOID
)
{
  PcdSet64S (PcdFuncBoardHookPlatformSetupOverride, (UINT64) (UINTN) BoardHookPlatformSetup);
}

VOID
EhlBoardSmbiosInit (
  VOID
  )
{
  PcdSet64S (PcdSmbiosFabBoardName, (UINTN) PcdGetPtr (PcdBoardName));
  //
  // @todo : Update Slot Entry Table for all the supported boards using below PCD.
  //  This PCD follows SYSTEM_SLOT_ENTRY structure in \Include\SmbiosPlatformInfoDefinition.h
  //PcdSet64S (PcdSmbiosMainSlotEntry, NULL);
}

VOID
EhlUpdateDimmPopulation (
  VOID
  )
{
  MEMORY_INFO_DATA_HOB    *MemInfo;
  UINT8                   Slot0;
  UINT8                   Slot1;
  UINT8                   Slot2;
  UINT8                   Slot3;
  CONTROLLER_INFO         *ControllerInfo;
  EFI_HOB_GUID_TYPE       *GuidHob;

  GuidHob = NULL;
  MemInfo = NULL;
  GuidHob = GetFirstGuidHob (&gSiMemoryInfoDataGuid);
  ASSERT (GuidHob != NULL);
  if (GuidHob != NULL) {
    MemInfo = (MEMORY_INFO_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
  }
  if (MemInfo != NULL) {
    if ( PcdGet8 (PcdPlatformFlavor) == FlavorDesktop ||
         PcdGet8 (PcdPlatformFlavor) == FlavorUpServer ||
         PcdGet8 (PcdPlatformFlavor) == FlavorWorkstation
        ) {
        ControllerInfo = &MemInfo->Controller[0];
        Slot0 = ControllerInfo->ChannelInfo[0].DimmInfo[0].Status;
        Slot1 = ControllerInfo->ChannelInfo[0].DimmInfo[1].Status;
        Slot2 = ControllerInfo->ChannelInfo[1].DimmInfo[0].Status;
        Slot3 = ControllerInfo->ChannelInfo[1].DimmInfo[1].Status;

      //
      // Channel 0          Channel 1
      // Slot0   Slot1      Slot0   Slot1      - Population            AIO board
      // 0          0          0          0          - Invalid        - Invalid
      // 0          0          0          1          - Valid          - Invalid
      // 0          0          1          0          - Invalid        - Valid
      // 0          0          1          1          - Valid          - Valid
      // 0          1          0          0          - Valid          - Invalid
      // 0          1          0          1          - Valid          - Invalid
      // 0          1          1          0          - Invalid        - Invalid
      // 0          1          1          1          - Valid          - Invalid
      // 1          0          0          0          - Invalid        - Valid
      // 1          0          0          1          - Invalid        - Invalid
      // 1          0          1          0          - Invalid        - Valid
      // 1          0          1          1          - Invalid        - Valid
      // 1          1          0          0          - Valid          - Valid
      // 1          1          0          1          - Valid          - Invalid
      // 1          1          1          0          - Invalid        - Valid
      // 1          1          1          1          - Valid          - Valid
      //
      if ((Slot0 && (Slot1 == 0)) || (Slot2 && (Slot3 == 0))) {
        PcdSetBoolS (PcdDimmPopulationError, TRUE);
      }
    }
  }
}

/**
  Enable Tier2 GPIO Sci wake capability.

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
EhlTier2GpioWakeSupport (
  VOID
  )
{
  BOOLEAN Tier2GpioWakeEnable;

  Tier2GpioWakeEnable = FALSE;

  //
  // Root port #03: M.2 WLAN
  //
  if (IsPcieEndPointPresent (2)) {
   Tier2GpioWakeEnable = TRUE;
  }
  PcdSetBoolS (PcdGpioTier2WakeEnable, Tier2GpioWakeEnable);

  return EFI_SUCCESS;
}


/**
  This protocol is used by PlatSamplePkg Setup modules to trigger
  dynamic HII population.

@todo Remove this when the PlatSamplePkg Setup modules have been replaced
  with BoardPkg modules that don't depend on this Protocol.
**/
VOID
EhlSignalAllDriversConnected (
  VOID
  )
{
  EFI_HANDLE                 Handle;
  EFI_STATUS                 Status;

  Handle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gBdsAllDriversConnectedProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);
}

/**
  Configure GPIO power button
**/
VOID
EhlConfigureGpioPowerButton (
  VOID
  )
{
  GPIO_CONFIG  GpioConfig;

  DEBUG ((EFI_D_INFO, "EhlConfigureGpioPowerButton\n"));
  ZeroMem (&GpioConfig, sizeof (GPIO_CONFIG));

  GpioConfig.PadMode = GpioPadModeGpio;
  GpioConfig.HostSoftPadOwn = GpioHostOwnAcpi;
  GpioConfig.Direction = GpioDirInInv;
  GpioConfig.OutputState = GpioOutDefault;
  GpioConfig.InterruptConfig = GpioIntBothEdge | GpioIntSci;
  GpioConfig.PowerConfig = GpioHostDeepReset;
  GpioConfig.ElectricalConfig = GpioTermNone;
  GpioConfig.LockConfig = GpioPadConfigUnlock;

  GpioSetPadConfig (GPIO_VER3_GPD2, &GpioConfig);
}

/**
  A hook for board-specific initialization after PCI enumeration.

  @retval EFI_SUCCESS   The board initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardInitAfterPciEnumeration (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardInitAfterPciEnumeration\n"));

  EhlInitPatchConfigurationData ();

  EhlTier2GpioWakeSupport ();

  EhlBoardMiscInit();

  EhlBoardSmbiosInit ();

  UpdatePlatformInfo ();

  return EFI_SUCCESS;
}

/**
  A hook for board-specific functionality for the ReadyToBoot event.

  @retval EFI_SUCCESS   The board initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardInitReadyToBoot (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardInitReadyToBoot\n"));

  EhlUpdateDimmPopulation ();

  EhlSignalAllDriversConnected ();

  return EFI_SUCCESS;
}

/**
  A hook for board-specific functionality for the ExitBootServices event.

  @retval EFI_SUCCESS   The board initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardInitEndOfFirmware (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardInitEndOfFirmware\n"));

  EhlConfigureGpioPowerButton ();

  return EFI_SUCCESS;
}
