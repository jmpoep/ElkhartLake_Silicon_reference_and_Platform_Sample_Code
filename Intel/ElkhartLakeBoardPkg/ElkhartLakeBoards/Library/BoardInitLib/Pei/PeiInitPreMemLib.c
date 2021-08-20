/** @file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <PiPei.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BiosIdLib.h>
#include <Library/OobRegionLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiLib.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Library/MmioInitLib.h>
#include <PlatformBoardConfig.h>
#include <Library/SiliconInitLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Register/PmcRegs.h>
#include <Library/PmcLib.h>
#include <Library/PeiBootModeLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Library/WakeupEventLib.h>
#include <Library/GpioLib.h>
#include <Library/BoardConfigLib.h>
#include <Library/TimerLib.h>
#include <ElkhartLakeBoardConfigPatchTable.h>
#include <PlatformBoardId.h>
#include <SioRegs.h>
#include <Library/IoLib.h>
#include <Pins/GpioPinsVer3.h>
#include <Pins/GpioPinsVer1N.h>
#include <Pins/GpioPinsVer1Lp.h>
#include "Library/BfxTempRamLib.h"

#define SIO_RUNTIME_REG_BASE_ADDRESS      0x0680

/**
  Elkhartlake boards configuration init function for PEI pre-memory phase.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
EhlInitPreMem (
  VOID
  )
{
  EFI_STATUS                        Status;
  UINTN                             VariableSize;
  VOID                              *MemorySavedData;
  UINT8                             MorControl;
  VOID                              *MorControlPtr;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);
  //
  // Initialize S3 Data variable (S3DataPtr). It may be used for warm and fast boot paths.
  //
  VariableSize = 0;
  MemorySavedData = NULL;
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"MemoryConfig",
                               &gFspNonVolatileStorageHobGuid,
                               NULL,
                               &VariableSize,
                               MemorySavedData
                               );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    //
    // Set the DISB bit
    // after memory Data is saved to NVRAM.
    //
    PmcSetDramInitScratchpad ();
  }

  //
  // MOR
  //
  MorControl = 0;
  MorControlPtr = &MorControl;
  VariableSize = sizeof (MorControl);
  Status = PeiGetVariable (
             MEMORY_OVERWRITE_REQUEST_VARIABLE_NAME,
             &gEfiMemoryOverwriteControlDataGuid,
             &MorControlPtr,
             &VariableSize
             );
  DEBUG ((DEBUG_INFO, "MorControl - 0x%x (%r)\n", MorControl, Status));
  if (MOR_CLEAR_MEMORY_VALUE (MorControl)) {
    PcdSet8S (PcdCleanMemory, MorControl & MOR_CLEAR_MEMORY_BIT_MASK);
  }
#if FixedPcdGetBool(PcdBfxEnable) == 1
  PcdSet32S (PcdStackBase, BfxGetTempRamBase () + BfxGetTempRamSize () - (PcdGet32 (PcdFspTemporaryRamSize) + PcdGet32 (PcdFspReservedBufferSize)));
#else
  PcdSet32S (PcdStackBase, PcdGet32 (PcdTemporaryRamBase) + PcdGet32 (PcdTemporaryRamSize) - (PcdGet32 (PcdFspTemporaryRamSize) + PcdGet32 (PcdFspReservedBufferSize)));
#endif
  PcdSet32S (PcdStackSize, PcdGet32 (PcdFspTemporaryRamSize));

  PcdSet8S (PcdCpuRatio, 0x0);
  PcdSet8S (PcdBiosGuard, 0x0);

  return EFI_SUCCESS;
}


/**
  Updates the wakeupType.
**/
VOID
EhlWakeUpTypeUpdate (
  VOID
  )
{
  UINT8   WakeupType;
  //
  // Updates the wakeupType which will be used to update the same in Smbios table 01
  //
  GetWakeupEvent (&WakeupType);
  PcdSet8S (PcdWakeupType, WakeupType);
}

VOID
EhlMrcConfigInit (
  VOID
  );

VOID
EhlSaMiscConfigInit (
  VOID
  );

VOID
EhlSaGpioConfigInit (
  VOID
  );

VOID
EhlSaUsbConfigInit (
  VOID
  );

EFI_STATUS
EhlRootPortClkInfoInit (
  VOID
  );

VOID
EhlGpioTablePreMemInit(
  VOID
  );

VOID
EhlGpioGroupTierInit (
  VOID
  );

/**
  HSIO init function for PEI pre-memory phase.
**/
VOID
EhlHsioInit (
  VOID
  )
{
}

/**
  Board's PCD function hook init function for PEI post memory phase.
**/
VOID
EhlBoardFunctionInitPostMem (
  VOID
  )
{
  //
  // Set a null function in order to avoid PcdFunction pointer is NULL ASSERT error.
  //
}

/**
  Configure Super IO
**/
STATIC
VOID
SioInit (
  VOID
  )
{
  //
  // Program and Enable Default Super IO Configuration Port Addresses and range
  //
  PchLpcGenIoRangeSet (PcdGet16 (PcdLpcSioConfigDefaultPort) & (~0xF), 0x10);

  //
  // Enable LPC decode for KCS and mailbox SIO for iBMC communication
  //
  if (PcdGet8 (PcdPlatformFlavor) == FlavorUpServer) {
    PchLpcGenIoRangeSet (BMC_KCS_BASE_ADDRESS, 0x10);
    PchLpcGenIoRangeSet (PILOTIII_MAILBOX_BASE_ADDRESS, 0x10);
  } else {
  //
  // 128 Byte Boundary and SIO Runtime Register Range is 0x0 to 0xF;
  //
    PchLpcGenIoRangeSet (SIO_RUNTIME_REG_BASE_ADDRESS  & (~0x7F), 0x10);
  }

  //
  // We should not depend on SerialPortLib to initialize KBC for legacy USB
  // So initialize KBC for legacy USB driver explicitly here.
  // After we find how to enable mobile KBC, we will add enabling code for mobile then.
  //
  if ((PcdGet8 (PcdPlatformFlavor) == FlavorDesktop) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorWorkstation)) {
    //
    // Enable KBC for National PC8374 SIO
    //
    if (PcdGetBool (PcdPc8374SioKbcPresent)) {
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioIndexDefaultPort), 0x07);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioDataDefaultPort), 0x06);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioIndexDefaultPort), 0x30);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioDataDefaultPort), 0x01);
    }
  }

  return;
}

/**
  Notifies the gPatchConfigurationDataPreMemPpiGuid has been Installed

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
EhlBoardPatchConfigurationDataPreMemCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  UINTN   ConfigPatchStructSize;
  UINT16    BoardId;
  BoardId = PcdGet16(PcdBoardId);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdJslLp4xErb:
    case BoardIdJslLp4xType4Rvp1:
      ConfigPatchStructSize = SIZE_OF_TABLE (mElkhartlakeDdr4RvpConfigPatchStruct, CONFIG_PATCH_STRUCTURE);
      PatchSetupConfigurationDataPreMem (mElkhartlakeDdr4RvpConfigPatchStruct, ConfigPatchStructSize);
      break;

    case BoardIdEhlLp4xType3Crb:
      ConfigPatchStructSize = SIZE_OF_TABLE (mElkhartlakeCRBConfigPatchStruct, CONFIG_PATCH_STRUCTURE);
      PatchSetupConfigurationDataPreMem (mElkhartlakeCRBConfigPatchStruct, ConfigPatchStructSize);
      break;

    default:
      break;
  }

  return RETURN_SUCCESS;
}

static EFI_PEI_NOTIFY_DESCRIPTOR mOtherBoardPatchConfigurationDataPreMemNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPatchConfigurationDataPreMemPpiGuid,
  EhlBoardPatchConfigurationDataPreMemCallback
};

/**
  Board Misc init function for PEI pre-memory phase.
**/
VOID
EhlBoardMiscInitPreMem (
  VOID
  )
{
  PCD64_BLOB PcdData;
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  //
  // RecoveryMode GPIO
  //
  PcdData.Blob = 0;
  PcdData.BoardGpioConfig.Type = BoardGpioTypeNotSupported;
  PcdSet64S (PcdRecoveryModeGpio, PcdData.Blob);

  //
  // OddPower Init
  //
  PcdSetBoolS (PcdOddPowerInitEnable, FALSE);

  //
  // Pc8374SioKbc Present
  //
  PcdSetBoolS (PcdPc8374SioKbcPresent, FALSE);

  //
  // Smbus Alert function Init.
  //
  PcdSetBoolS (PcdSmbusAlertEnable, TRUE);

  PeiServicesNotifyPpi (&mOtherBoardPatchConfigurationDataPreMemNotifyList);

  switch (BoardId) {
    case BoardIdJslLp4xErb:
      PcdSet32S (PcdWwanFullCardPowerOffGpio, GPIO_VER1_N_GPP_E3);
      PcdSet32S (PcdWwanBbrstGpio, GPIO_VER1_N_GPP_S0);
      PcdSet32S (PcdWwanPerstGpio, GPIO_VER1_N_GPP_C0);
      //PcdSet32S (PcdWwanWakeGpio, GPIO_VER3_GPP_C9);
      PcdSet8S  (PcdWwanPerstGpioPolarity, 1);
      PcdSetBoolS (PcdWwanFullCardPowerOffGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      PcdSetBoolS (PcdWwanBbrstGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      break;

    case BoardIdJslLp4xType4Rvp1:
      PcdSet32S (PcdWwanFullCardPowerOffGpio, GPIO_VER1_N_GPP_E5);
      PcdSet32S (PcdWwanBbrstGpio, GPIO_VER1_N_GPP_H17);
      PcdSet32S (PcdWwanPerstGpio, GPIO_VER1_N_GPP_B14);
      PcdSet8S  (PcdWwanPerstGpioPolarity, 1);
      PcdSetBoolS (PcdWwanFullCardPowerOffGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      PcdSetBoolS (PcdWwanBbrstGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      break;

    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    default:
      PcdSet32S (PcdWwanFullCardPowerOffGpio, GPIO_VER3_GPP_E0);
      PcdSet32S (PcdWwanBbrstGpio, GPIO_VER3_GPP_V13);
      PcdSet32S (PcdWwanPerstGpio, GPIO_VER3_GPP_B14);
      PcdSet32S (PcdWwanWakeGpio, GPIO_VER3_GPP_B17);
      PcdSet8S (PcdWwanPerstGpioPolarity, 0);
      PcdSetBoolS (PcdWwanFullCardPowerOffGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      PcdSetBoolS (PcdWwanBbrstGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      break;
  }
}

/**
  A hook for board-specific initialization prior to memory initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardInitBeforeMemoryInit (
  VOID
  )
{
  EFI_STATUS        Status;

  DEBUG ((DEBUG_INFO, "EhlBoardInitBeforeMemoryInit\n"));

  GetBiosId (NULL);
  GetOobRegion (NULL);
  EhlInitPreMem ();

  EhlWakeUpTypeUpdate ();

  SioInit ();

  ///
  /// Do basic PCH init
  ///
  SiliconInit ();

  EhlGpioGroupTierInit ();
  EhlGpioTablePreMemInit ();

  EhlHsioInit ();
  EhlMrcConfigInit ();
  EhlSaGpioConfigInit ();
  EhlSaMiscConfigInit ();
  Status = EhlRootPortClkInfoInit ();
  EhlBoardMiscInitPreMem ();
  EhlSaUsbConfigInit ();

  // Configure GPIO Before Memory is not ready
  GpioInit (PcdGetPtr (PcdBoardGpioTablePreMem));

  // Configure GPIO group GPE tier
  GpioGroupTierInit ();

  ASSERT(Status == EFI_SUCCESS);
  return EFI_SUCCESS;
}

/**
  A hook for board-specific initialization after memory initialization.

  @retval EFI_SUCCESS   The board initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardInitAfterMemoryInit (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardInitAfterMemoryInit\n"));
  EhlBoardFunctionInitPostMem (); // All this is doing is setiing value to a NULL PCD.
  return MmioInit ();
}

/**
  This board service initializes board-specific debug devices.

  @retval EFI_SUCCESS   Board-specific debug initialization was successful.
**/
EFI_STATUS
EFIAPI
EhlBoardDebugInit (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardDebugInit\n"));

  return EFI_SUCCESS;
}

/**
  This board service detects the boot mode.

  @retval EFI_BOOT_MODE The boot mode.
**/
EFI_BOOT_MODE
EFIAPI
EhlBoardBootModeDetect (
  VOID
  )
{
  EFI_BOOT_MODE                             BootMode;

  DEBUG ((DEBUG_INFO, "EhlBoardBootModeDetect\n"));
  BootMode = DetectBootMode ();
  DEBUG ((DEBUG_INFO, "BootMode: 0x%02X\n", BootMode));

  return BootMode;
}
