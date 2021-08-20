/** @file
  Source code file for the Boot Mode Library

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
  of your license agreement with Intel or your vendor.This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PeiServicesLib.h>
#include <BootState.h>
#include <Ppi/Capsule.h>
#include <SetupVariable.h>
#include <SimpleBootFlag.h>
#include <Library/PmcLib.h>
#include <Register/PmcRegs.h>
#include <FastBootDataDef.h>
#include <FastBootExceptionInfoHob.h>
#include <CmosMap.h>
#include <Library/CmosAccessLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioLib.h>
#include <PlatformBoardConfig.h>
#include <Library/PeiBootModeLib.h>
#include "PeiBootModeLibInternal.h"
#include <PlatformBoardId.h>
#include <PlatformBoardType.h>
#include <PlatformNvRamHookLib.h>
#include <Library/PeiPlatformCodLib.h>
#include <Ppi/CapsuleOnDiskPpi.h>

#define FAST_BOOT_OR_MASK       0x01

EFI_STATUS
EFIAPI
LoadCapsuleFromDisk (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiListNonS3BootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiBootInNonS3ModePpiGuid,
  NULL
};

#if FixedPcdGetBool(PcdCapsuleEnable) == 1
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR mBootModeNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiCapsulePpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT)PreMemUpdateCapsuleBootMode
};
#endif

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiListRecoveryBootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiBootInRecoveryModePpiGuid,
  NULL
};

static EFI_PEI_NOTIFY_DESCRIPTOR  mLoadCapsuleFromDisk[] = {
  //
  // Use EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH flag rather than EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK
  // to ensure all VirtualBlockIoPpi notify callbacks (especially the one in FatLite) are executed
  // before invoking LoadCapsuleFromDisk().
  //
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH,
    &gEfiPeiVirtualBlockIoPpiGuid,
    (EFI_PEIM_NOTIFY_ENTRY_POINT) LoadCapsuleFromDisk
  },
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiVirtualBlockIo2PpiGuid,
    (EFI_PEIM_NOTIFY_ENTRY_POINT) LoadCapsuleFromDisk
  }
};

///
/// Priority of our boot modes, highest priority first
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_BOOT_MODE mBootModePriority[] = {
  BOOT_IN_RECOVERY_MODE,
  BOOT_WITH_DEFAULT_SETTINGS,
  BOOT_ON_FLASH_UPDATE,
  BOOT_ON_S3_RESUME,
  BOOT_ON_S4_RESUME,
  BOOT_WITH_MINIMAL_CONFIGURATION,
  BOOT_ASSUMING_NO_CONFIGURATION_CHANGES,
  BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS,
  BOOT_WITH_FULL_CONFIGURATION,
  BOOT_ON_S5_RESUME,
  BOOT_SPECIAL_MASK
};

/**
  Update boot mode if it is in capsule update boot mode.

  @retval EFI_SUCCESS             If we have a capsule available.
  @retval EFI_NOT_FOUND           No capsule detected.

**/
EFI_STATUS
EFIAPI
PreMemUpdateCapsuleBootMode (
  VOID
  )
{
  PEI_CAPSULE_PPI               *Capsule;
  EFI_STATUS                    Status;
  EFI_BOOT_MODE                 BootMode;
  EFI_PEI_SERVICES              **PeiServices = NULL;

  DEBUG ((DEBUG_INFO, "PreMemUpdateCapsuleBootMode () - Start\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR(Status);
  DEBUG ((DEBUG_INFO, " PeiServicesGetBootMode: 0x%X\n", BootMode));

  Status = PeiServicesLocatePpi (
             &gPeiCapsulePpiGuid,
             0,
             NULL,
             (VOID **) PeiServices
             );
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  ///
  /// Determine if we're in capsule update mode
  ///
  Status = PeiServicesLocatePpi (
             &gPeiCapsulePpiGuid,
             0,
             NULL,
             (VOID **) &Capsule
             );
  if (Status == EFI_SUCCESS) {
    Status = Capsule->CheckCapsuleUpdate((EFI_PEI_SERVICES **) PeiServices);
    if (Status == EFI_SUCCESS) {
      PrioritizeBootMode(&BootMode, BOOT_ON_FLASH_UPDATE);
      if (PcdGetBool(PcdUpdateCapsuleOnColdReset)) {
        PeiServicesInstallPpi (&mPpiListRecoveryBootMode);
        Status = InitializeCodPpis ();
        ASSERT_EFI_ERROR (Status);
        Status = PeiServicesNotifyPpi (mLoadCapsuleFromDisk);
        ASSERT_EFI_ERROR (Status);
      }
    }
  }
  Status = PreMemUpdateBootMode (&BootMode);
  PeiServicesSetBootMode (BootMode);
  DEBUG ((DEBUG_INFO, "PreMemUpdateCapsuleBootMode () - End, PeiServicesSetBootMode: 0x%X\n", BootMode));
  return Status;
}

/**
  Check fast boot is enabled or not

  @retval  FastBootEnabledStatus  TRUE means fast boot is enabled
                                  FALSE means fast boot is disabled
**/
BOOLEAN
EFIAPI
IsFastBootEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVarPpi;
  UINTN                           VarSize;
  SETUP_DATA                      SystemConfiguration;
  BOOLEAN                         FastBootEnabledStatus;

  FastBootEnabledStatus = FALSE;
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVarPpi
             );
  if (Status == EFI_SUCCESS) {
    VarSize = sizeof (SETUP_DATA);
    Status = PeiReadOnlyVarPpi->GetVariable (
                                  PeiReadOnlyVarPpi,
                                  L"Setup",
                                  &gSetupVariableGuid,
                                  NULL,
                                  &VarSize,
                                  &SystemConfiguration
                                  );
    if (Status == EFI_SUCCESS) {
      if (SystemConfiguration.FastBoot != 0) {
        FastBootEnabledStatus = TRUE;
      }
    }
  }

  return FastBootEnabledStatus;
}

/**
  Update boot mode

  @param[in,out] BootMode             Current System BootMode.

  @retval EFI_SUCCESS                 The boot mode was returned successfully.

**/

EFI_STATUS
EFIAPI
PreMemUpdateBootMode (
  IN OUT EFI_BOOT_MODE          *BootMode
  )
{
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;
  UINTN                             VarSize;
  BOOLEAN                           IsFastBootEnable;
  EFI_SIMPLE_BOOT_FLAG              SimpleBootFlag;
  EFI_STATUS                        Status;
  UINT8                             FastBootRegData;
  FAST_BOOT_EXCEPTION_INFO_HOB      *FastBootExceptionInfoHob;

  DEBUG ((DEBUG_INFO, "PreMemUpdateBootMode () - Start\n"));
  FastBootRegData = 0;

  IsFastBootEnable = IsFastBootEnabled ();
  ///
  /// Check Simple Boot Flag
  ///
  SimpleBootFlag.Uint8 = GetSimpleBootFlag ();
  if ((SimpleBootFlag.Bits.Booting != 0) || (SimpleBootFlag.Bits.Diag != 0)) {

    /// Don't set Diagnostics boot it will significantly impact boot performance. e.g.: MRC extensive memory test
    /// Current platform boot flow is very complex and it may reset before booting to OS.
    /// Need to design a hook machanism: bios calls PreReset() before resetting system when the BOOTING bit gets cleared.

    /// PrioritizeBootMode (&BootMode, BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS);
  }

  if (IsFastBootEnable) {
    if (IsPreviousBootSuccessful () && !IsTimeOutOccurred () && !IsPowerButtonOverride ()) {
        PrioritizeBootMode (BootMode, BOOT_WITH_MINIMAL_CONFIGURATION);
    } else {
      Status = PeiServicesCreateHob (
                 EFI_HOB_TYPE_GUID_EXTENSION,
                 sizeof (FAST_BOOT_EXCEPTION_INFO_HOB),
                 (VOID **) &FastBootExceptionInfoHob
                 );
      if (!EFI_ERROR (Status)) {
        FastBootExceptionInfoHob->Header.Name = gFastBootExceptionInfoHobGuid;
        FastBootExceptionInfoHob->FbExceptionType = ExceptionType2;
        FastBootExceptionInfoHob->FbExceptionCategory = BootFailure;
      }
      DEBUG ((DEBUG_INFO, " Exception has occurred. Prioritizing Boot mode to BOOT_WITH_FULL_CONFIGURATION\n"));
      PrioritizeBootMode (BootMode, BOOT_WITH_FULL_CONFIGURATION);
    }
  } else {
    if ((*BootMode != BOOT_ON_S5_RESUME) && IsBootWithNoChange ()) {
      PrioritizeBootMode (BootMode, BOOT_ASSUMING_NO_CONFIGURATION_CHANGES);
    } else {
      PrioritizeBootMode (BootMode, BOOT_WITH_FULL_CONFIGURATION);
    }
  }

  ///
  /// FastBoot - set boot progress bit to indicate boot is in progress
  /// bit will be cleared before booting to OS
  ///
  if (IsFastBootEnable) {
    if (*BootMode != BOOT_ON_S3_RESUME) {
      FastBootRegData = GetBootFlagStatus ();
      FastBootRegData |= FAST_BOOT_OR_MASK;
      UpdateBootFlagStatus (FastBootRegData);
    }
  }

  if (*BootMode != BOOT_ON_S3_RESUME) {
    ///
    /// If not in S3 mode, signal it.
    ///
    Status = PeiServicesInstallPpi (&mPpiListNonS3BootMode);
    ASSERT_EFI_ERROR (Status);
  }

  if (IsFastBootEnable) {
    Status = PeiServicesLocatePpi (
               &gEfiPeiReadOnlyVariable2PpiGuid,
               0,
               NULL,
               (VOID **) &VariableServices
               );
    VarSize = 0;
    if (!RETURN_ERROR (Status)) {
      Status = VariableServices->GetVariable (
                                   VariableServices,
                                   L"ConOut",
                                   &gEfiGlobalVariableGuid,
                                   NULL,
                                   &VarSize,
                                   NULL
                                   );
      if (Status == EFI_NOT_FOUND) {
        PrioritizeBootMode (BootMode, BOOT_WITH_FULL_CONFIGURATION);
      }
    }
  }

  DEBUG ((DEBUG_INFO, "PreMemUpdateBootMode () - End\n"));
  return EFI_SUCCESS;
}

/**
  Detect boot mode

  @retval EFI_BOOT_MODE  Current System BootMode.
**/

EFI_BOOT_MODE
EFIAPI
DetectBootMode (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  DEBUG ((DEBUG_INFO, "DetectBootMode () - Start\n"));

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );

  PMC_SLEEP_STATE                 SleepType;
#if FixedPcdGetBool (PcdSetupEnable) == 1
  SETUP_DATA                      Setup;
  SA_SETUP                        SaSetup;
  ME_SETUP                        MeSetup;
  CPU_SETUP                       CpuSetup;
  PCH_SETUP                       PchSetup;
  UINTN                           DataSize;
#endif
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR(Status);
  DEBUG ((DEBUG_INFO, " PeiServicesGetBootMode BootMode: 0x%X\n", BootMode));

  Status = IsRecoveryMode ();
  if (Status == EFI_SUCCESS) {
    BootMode = BOOT_IN_RECOVERY_MODE;
    DEBUG ((DEBUG_INFO, " IsRecoveryMode: BOOT_IN_RECOVERY_MODE"));
    //mPpiListRecoveryBootMode is installed by MinPlatform
  }

  SleepType = PmcGetSleepTypeAfterWake ();
  DEBUG((DEBUG_INFO, " PmcGetSleepTypeAfterWake SleepType: %d\n", SleepType));
  if (SleepType != PmcNotASleepState) {
    if (!PmcIsPowerFailureDetected () && PmcIsRtcBatteryGood()) {
      switch (SleepType) {
        case PmcS3SleepState:
          PrioritizeBootMode (&BootMode, BOOT_ON_S3_RESUME);
          DEBUG ((DEBUG_INFO, " PmcS3SleepState BootMode: 0x%X\n", BootMode));
          break;
        case PmcS4SleepState:
          PrioritizeBootMode (&BootMode, BOOT_ON_S4_RESUME);
          DEBUG ((DEBUG_INFO, " PmcS4SleepState BootMode: 0x%X\n", BootMode));
          break;
        case PmcS5SleepState:
          PrioritizeBootMode (&BootMode, BOOT_ON_S5_RESUME);
          DEBUG ((DEBUG_INFO, " PmcS5SleepState BootMode: 0x%X\n", BootMode));
          break;
        default:
          break;
      }
    }
  } else {
      ///
      /// Clear Wake Status and Sleep Type
      ///
      PmcClearWakeStatus ();
      PmcSetSleepState (PmcInS0State);
    }
    if (!PmcIsRtcBatteryGood ()) {
      DEBUG ((DEBUG_ERROR, "RTC Power failure !! Could be due to a weak or missing battery, BootMode: BOOT_WITH_DEFAULT_SETTINGS\n"));
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }

  ///
  /// Check whether Setup Variable does exist to know the first boot or not.
  ///
#if FixedPcdGetBool (PcdSetupEnable) == 1

  DataSize = sizeof (SETUP_DATA);
  Status  = VariableServices->GetVariable (VariableServices, L"Setup", &gSetupVariableGuid, NULL, &DataSize, &Setup);
  if (Status == EFI_NOT_FOUND) {
    BootMode = BOOT_WITH_DEFAULT_SETTINGS;
  }
  if (Status != EFI_NOT_FOUND) {
    DataSize = sizeof (SA_SETUP);
    Status = VariableServices->GetVariable (VariableServices, L"SaSetup", &gSaSetupVariableGuid, NULL, &DataSize, &SaSetup);
    if (Status == EFI_NOT_FOUND) {
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
  }
  if (Status != EFI_NOT_FOUND) {
    DataSize = sizeof (ME_SETUP);
    Status = VariableServices->GetVariable (VariableServices, L"MeSetup", &gMeSetupVariableGuid, NULL, &DataSize, &MeSetup);
    if (Status == EFI_NOT_FOUND) {
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
  }
  if (Status != EFI_NOT_FOUND) {
    DataSize = sizeof (CPU_SETUP);
    Status = VariableServices->GetVariable (VariableServices, L"CpuSetup", &gCpuSetupVariableGuid, NULL, &DataSize, &CpuSetup);
    if (Status == EFI_NOT_FOUND) {
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
  }
  if (Status != EFI_NOT_FOUND) {
    DataSize = sizeof (PCH_SETUP);
    Status = VariableServices->GetVariable (VariableServices, L"PchSetup", &gPchSetupVariableGuid, NULL, &DataSize, &PchSetup);
    if (Status == EFI_NOT_FOUND) {
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
  }

  if (Status != EFI_NOT_FOUND) {
    DataSize = sizeof (SETUP_DATA);
    Status  = VariableServices->GetVariable (VariableServices, L"InitSetupVariable", &gSetupVariableGuid, NULL, &DataSize, &Setup);
    if (Status == EFI_NOT_FOUND) {
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
  }
#endif
  DEBUG ((DEBUG_ERROR, " After setup variables check, BootMode: 0x%X\n", BootMode));
  PeiServicesSetBootMode (BootMode);
#if FixedPcdGetBool (PcdCapsuleEnable) == 1
  ///
  /// Register notify to update BootMode later
  ///
  Status = PeiServicesNotifyPpi (&mBootModeNotifyList);
  ASSERT_EFI_ERROR(Status);
#else
  Status = PreMemUpdateBootMode (&BootMode);
  PeiServicesSetBootMode (BootMode);
#endif
  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "DetectBootMode () - End, BootMode: 0x%X\n", BootMode));
  return BootMode;
}

/**
  Check Boot Flag Status to determine if previous boot was successful

  @retval  TRUE   Previous Boot was success.
  @retval  FALSE  Previous Boot wasn't success.
**/

BOOLEAN
EFIAPI
IsPreviousBootSuccessful (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT8                           PreviousBootCompletionFlag;
  BOOLEAN                         BootState;
  UINTN                           DataSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiVar;

  DEBUG ((DEBUG_INFO, "IsPreviousBootSuccessful () - Start\n"));
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiVar
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get last Boot State Variable to confirm that it is not a first boot.
  ///
  DataSize = sizeof (BOOLEAN);
  Status = PeiVar->GetVariable (
                     PeiVar,
                     BOOT_STATE_VARIABLE_NAME,
                     &gBootStateGuid,
                     NULL,
                     &DataSize,
                     &BootState
                     );

  if (EFI_ERROR (Status)) {
    return FALSE;
  }
  PreviousBootCompletionFlag = 0;
  PreviousBootCompletionFlag = GetBootFlagStatus ();
  PreviousBootCompletionFlag &= FAST_BOOT_OR_MASK;

  if (PreviousBootCompletionFlag) {
    DEBUG ((DEBUG_INFO, " Previous boot was not successful to boot to OS\n"));
    return FALSE;
  }
  DEBUG ((DEBUG_INFO, " Previous boot cycle successfully completed handover to OS\n"));
  return TRUE;
}

/**
  Query PCH to determine if Intrusion Detection set

  @retval  TRUE   No Change.
  @retavl  FALSE  Change.
**/
BOOLEAN
EFIAPI
IsBootWithNoChange (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT16                          TcoBase;
  UINT16                          Tco2Status;
  BOOLEAN                         BoxOpen;
  BOOLEAN                         BootState;
  UINTN                           DataSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiVar;

  DEBUG ((DEBUG_INFO, "IsBootWithNoChange () - Start\n"));
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiVar
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get last Boot State Variable From NVRAM
  ///
  DataSize = sizeof (BOOLEAN);
  Status = PeiVar->GetVariable (
                     PeiVar,
                     BOOT_STATE_VARIABLE_NAME,
                     &gBootStateGuid,
                     NULL,
                     &DataSize,
                     &BootState
                     );
  if (EFI_ERROR (Status)) {
    // If there's no variable, just report the state of the hardware
    BootState = TRUE;
  }

  ///
  /// Read the TCO registers
  ///
  TcoBase     = (UINT16)PcdGet16 (PcdTcoBaseAddress);
  Tco2Status  = IoRead16 (TcoBase + R_TCO_IO_TCO2_STS);

  ///
  /// This is the state of the hardware
  ///
  BoxOpen = (BOOLEAN) (Tco2Status & B_TCO_IO_TCO2_STS_INTRD_DET);
  if (BoxOpen) {
    ///
    /// Clear the bit for next boot.
    ///
    Tco2Status |= B_TCO_IO_TCO2_STS_INTRD_DET;
    IoWrite16 (TcoBase + R_TCO_IO_TCO2_STS, Tco2Status);

    ///
    /// Since it was OPEN, return that it cannot be in "no config change boot"
    ///
    DEBUG ((DEBUG_INFO, " BoxOpen\n"));
    return FALSE;
  } else {
    ///
    /// Since it was CLOSED, return that can be "no config change boot"
    /// Need variable to know that memory was tested AT LEAST one time!
    ///
    if (!BootState) {
      DEBUG ((DEBUG_INFO, " BootState TRUE\n"));
      return TRUE;
    } else {
      DEBUG ((DEBUG_INFO, " BootState FALSE\n"));
      return FALSE;
    }
  }
}

/**
  Given the current boot mode, and a proposed new boot mode, determine
  which has priority. If the new boot mode has higher priority, then
  make it the current boot mode.

  @param[in][out] CurrentBootMode Pointer to current planned boot mode
  @param[in][out] NewBootMode     Proposed boot mode.

  @retval         EFI_NOT_FOUND   If either boot mode is not recognized.
  @retval         EFI_SUCCESS     If both boot mode values were
                                  recognized and were processed.
**/
EFI_STATUS
EFIAPI
PrioritizeBootMode (
  IN OUT EFI_BOOT_MODE    *CurrentBootMode,
  IN EFI_BOOT_MODE        NewBootMode
  )
{
  UINT32 CurrentIndex;
  UINT32 NewIndex;

  DEBUG ((DEBUG_INFO, "PrioritizeBootMode () - Start\n"));
  ///
  /// Find the position of the current boot mode in our priority array
  ///
  for ( CurrentIndex = 0;
        CurrentIndex < sizeof (mBootModePriority) / sizeof (mBootModePriority[0]);
        CurrentIndex++) {
    if (mBootModePriority[CurrentIndex] == *CurrentBootMode) {
      break;
    }
  }
  if (CurrentIndex >= sizeof (mBootModePriority) / sizeof (mBootModePriority[0])) {
    return EFI_NOT_FOUND;
  }
  ///
  /// Find the position of the new boot mode in our priority array
  ///
  for ( NewIndex = 0;
        NewIndex < sizeof (mBootModePriority) / sizeof (mBootModePriority[0]);
        NewIndex++) {
    if (mBootModePriority[NewIndex] == NewBootMode) {
      ///
      /// If this new boot mode occurs before the current boot mode in the
      /// priority array, then take it.
      ///
      if (NewIndex < CurrentIndex) {
        *CurrentBootMode = NewBootMode;
        DEBUG ((DEBUG_INFO, " CurrentBootMode: 0x%X\n", *CurrentBootMode));
      } else {
        DEBUG ((DEBUG_INFO, " CurrentBootMode 0x%X\n", *CurrentBootMode));
      }
      return EFI_SUCCESS;
    }
  }
  DEBUG ((DEBUG_INFO, "PrioritizeBootMode () - End\n"));
  return EFI_NOT_FOUND;
}

/**
  Get simple boot flag

  @retval  LegacyValue
  @retval  EfiValue
**/
UINT8
EFIAPI
GetSimpleBootFlag (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiVar;
  UINTN                           BufferSize;
  UINT8                           EfiValue;
  UINT8                           LegacyValue;

  ///
  /// Read EFI variable
  ///
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiVar
             );
  ASSERT_EFI_ERROR (Status);
  EfiValue = 0;
  BufferSize = sizeof (EfiValue);
  Status = PeiVar->GetVariable (
                     PeiVar,
                     SIMPLE_BOOT_FLAG_VARIABLE_NAME,
                     &gEfiGlobalVariableGuid,
                     NULL,
                     &BufferSize,
                     &EfiValue
                     );
  if (!EFI_ERROR (Status)) {
    if (!CheckOddParity (EfiValue)) {
      EfiValue = 0;
    }
  }

  /// @todo check if GetRtc3Address needs to be internal only and should be abstacted
  /// Read legacy simple boot flag

  LegacyValue = GetRtc3Address ();

  if (!CheckOddParity (LegacyValue)) {
    LegacyValue = 0;
  }
  return (LegacyValue != 0) ? LegacyValue : EfiValue;
}

/**
  Check if this system boot is due to 4sec power button override has occurred

  @retval  TRUE   Power Button Override occurred in last system boot
  @retval  FALSE  Power Button Override didnt occur
**/
BOOLEAN
EFIAPI
IsPowerButtonOverride (
  VOID
  )
{
  if (PmcIsPowerButtonOverrideDetected ()) {
    DEBUG ((DEBUG_INFO, "IsPowerButtonOverride TRUE\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Check Fast Boot 30-second WDT (TCO Timer) timeout has occurred

  @retval  TRUE   Timeout has occurred
  @retval  FALSE  Timeout didnt occur
**/
BOOLEAN
IsTimeOutOccurred (
  VOID
  )
{
  if (IoRead8 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TWDS) == FAST_BOOT_WDT_RESET_SIGNATURE) {
    IoWrite8 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TWDS, 0);
    DEBUG ((DEBUG_INFO, "IsTimeOutOccurred TRUE\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Check if the value is of ODD parity.

  @param[in]  Value  The 8 bits value

  @retval     TRUE   The value is of ODD parity
  @retval     FALSE  The value is not of ODD parity
**/
BOOLEAN
CheckOddParity (
  IN  UINT8 Value
  )
{
  UINT8                           OddNum;
  UINT8                           Index;

  OddNum = 0;
  for (Index = 0; Index < 8; Index++) {
    if (Value & (1 << Index)) {
      OddNum++;
    }
  }
  return (BOOLEAN) (OddNum % 2 != 0);
}

/**
  Detect recovery mode

  Detect Jumper to determine if recovery mode is set

  @retval  EFI_SUCCESS       System in Recovery Mode
  @retval  EFI_UNSUPPORTED   System doesn't support Recovery Mode
  @retval  EFI_NOT_FOUND     System is not in Recovery Mode
**/

EFI_STATUS
EFIAPI
IsRecoveryMode (
  VOID
  )
{
  BOOLEAN               RecJumperFlag;
  UINT32                BitMask;
  EFI_STATUS            Status;
  UINT32                RecoveryModeGpio;
  PCD64_BLOB            Pcd64;

  if (PcdGet8 (PcdBoardType) == BoardTypeSv ||
      PcdGet8 (PcdBoardType) == BoardTypeRvpErb ||
      PcdGet8 (PcdPlatformFlavor) == FlavorUpServer) {
    return RETURN_UNSUPPORTED; /* No Recovery Jumper*/
  }

  RecoveryModeGpio = 0;
  Pcd64.Blob = PcdGet64 (PcdRecoveryModeGpio);
  if (Pcd64.Blob != 0 && Pcd64.BoardGpioConfig.Type == BoardGpioTypePch) {
    Status = GpioGetInputValue (Pcd64.BoardGpioConfig.u.Pin, &RecoveryModeGpio);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "Invalid Recovery GPIO, PcdRecoveryModeGpio: 0x%x\n", PcdGet64 (PcdRecoveryModeGpio)));
    return EFI_NOT_FOUND;
  }

  BitMask = BIT0;
  RecJumperFlag = ((BOOLEAN)(!(RecoveryModeGpio & BitMask)));
  if (RecJumperFlag) {
    DEBUG ((DEBUG_INFO, "RecJumperFlag SET\n"));
    return EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, "RecJumperFlag NOT SET\n"));
    return EFI_NOT_FOUND;
  }
}

/**
  Load Capsule binary from external storage (such as UFS or NVMe).

  @param[in]  PeiServices       General purpose services available to every PEIM.

  @param[in]  NotifyDescriptor  The typedef structure of the notification
                                descriptor. Not used in this function.

  @param[in]  Ppi               The typedef structure of the PPI descriptor.
                                Not used in this function.

  @retval EFI_SUCCESS           The function completed successfully

**/
EFI_STATUS
EFIAPI
LoadCapsuleFromDisk (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  EFI_STATUS                                 Status;
  PEI_CAPSULE_ON_DISK_PPI                    *PeiCapsuleOnDisk;

  DEBUG ((DEBUG_INFO, "LoadCapsuleFromDisk Entry\n"));

  Status = PeiServicesLocatePpi (
             &gEfiPeiCapsuleOnDiskPpiGuid,
             0,
             NULL,
             (VOID **) &PeiCapsuleOnDisk
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate Pei CapsuleOnDisk  Ppi Failed.(Status = %r)\n", Status));
    return Status;
  }

  Status = PeiCapsuleOnDisk->GetCapsuleFromDisk ((EFI_PEI_SERVICES **)PeiServices, PeiCapsuleOnDisk);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Load Capsule from disk Failed.(Status = %r)\n", Status));
  }

  return Status;
#else
  return EFI_UNSUPPORTED;
#endif
}