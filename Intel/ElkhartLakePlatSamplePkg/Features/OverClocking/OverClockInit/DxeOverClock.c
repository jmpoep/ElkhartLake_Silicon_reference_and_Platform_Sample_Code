/** @file
  This file implements WDT timer clear and Setup features.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>
#include "DxeOverClock.h"
#include <IccSetupData.h>
#include <CpuRegs.h>
#include <CoreBiosMsg.h>
#include <Library/DxeMeLib.h>
#include <Library/BaseMemoryLib.h>
#include <OcSetupVariable.h>

GLOBAL_REMOVE_IF_UNREFERENCED SA_SETUP                  mSaSetup;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_SETUP                 mCpuSetup;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA                mSetupData;
GLOBAL_REMOVE_IF_UNREFERENCED OC_SETUP_DATA             mOcSetupData;

GLOBAL_REMOVE_IF_UNREFERENCED UINT32                    gSetupVariableAttributes;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                    gCpuSetupVariableAttributes;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                    gSaSetupVariableAttributes;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                    gOcVariableAttributes;
GLOBAL_REMOVE_IF_UNREFERENCED WDT_PROTOCOL              *gWdtDxe;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                     gWdtTimeOut = 0;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                   gResetRequired = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT                 gMemoryUpdateEvent;
GLOBAL_REMOVE_IF_UNREFERENCED VOID*                     gMemoryUpdateRegistration;

VOID
SyncOcSetupValue (
  IN BOOLEAN CopyToOcSetup
  );
#define COPY_SETUP_TO_OCSETUP TRUE
#define COPY_OCSETUP_TO_SETUP FALSE

/**
  This function is the entry point for this DXE. It programs the
  Overclocking Setup variables, if it differs from actual value programmed.
  And also it notifies a function before OS and whenever BIOS Setup gets control.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Pointer to the EFI System Table.

  @retval EFI_SUCCESS             Initialization complete.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
DxeOverClockEntry (
  IN  EFI_HANDLE         ImageHandle,
  IN  EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle;
  MEM_INFO_PROTOCOL         *MemInfoHobProtocol;
  UINTN                     VariableSize;
  UINTN                     OcVariableSize;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  &gCpuSetupVariableAttributes,
                  &VariableSize,
                  &mCpuSetup
                  );
   if (EFI_ERROR (Status)) { // If GetVariable fails, return EFI_SUCCESS asuming OC is Disabled.
    return EFI_SUCCESS;
  }

  //
  // If Overclocking is disabled, return
  //
  if (mCpuSetup.OverclockingSupport == 0) {
    return EFI_SUCCESS;
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &gSaSetupVariableAttributes,
                  &VariableSize,
                  &mSaSetup
                  );
  if (EFI_ERROR (Status)) { // If GetVariable fails, return EFI_SUCCESS asuming OC is Disabled.
    return EFI_SUCCESS;
  }

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &gSetupVariableAttributes,
                  &VariableSize,
                  &mSetupData
                  );
  if (EFI_ERROR (Status)) { // If GetVariable fails, return EFI_SUCCESS asuming OC is Disabled.
    return EFI_SUCCESS;
  }

  OcVariableSize = sizeof (OC_SETUP_DATA);
  Status = gRT->GetVariable (
                  L"OcSetup",
                  &gOcSetupVariableGuid,
                  &gOcVariableAttributes,
                  &OcVariableSize,
                  &mOcSetupData
                  );

  //
  // "OcSetup" variable can be changed by OS and therefore untrusted. Initialize OcVariableSize again to correct value.
  //
  OcVariableSize = sizeof (OC_SETUP_DATA);

  if (EFI_ERROR (Status)) {
    //
    // Create OC_SETUP_DATA default value and variable
    //
    SyncOcSetupValue (COPY_SETUP_TO_OCSETUP); // Copy mSetupData, mCpuSetupData and mSaSetupData to mOcSetupData
    gOcVariableAttributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    mOcSetupData.OcInterfaceRtUpdated = 0;
    Status = gRT->SetVariable (
                    L"OcSetup",
                    &gOcSetupVariableGuid,
                    gOcVariableAttributes,
                    OcVariableSize,
                    &mOcSetupData
                    );
  } else {
    if (mOcSetupData.OcInterfaceRtUpdated == 1) {
      //
      // OC setting has been updated during RT.
      //
      SyncOcSetupValue (COPY_OCSETUP_TO_SETUP); // Copy mOcSetupData to mSetupData, mCpuSetupData and mSaSetupData

      //
      // Update Setup variable to start new setting from next boot
      //
      Status = gRT->SetVariable (
                      L"CpuSetup",
                      &gCpuSetupVariableGuid,
                      gCpuSetupVariableAttributes,
                      sizeof (CPU_SETUP),
                      &mCpuSetup
                      );

      Status = gRT->SetVariable (
                      L"SaSetup",
                      &gSaSetupVariableGuid,
                      gSaSetupVariableAttributes,
                      sizeof (SA_SETUP),
                      &mSaSetup
                      );

      Status = gRT->SetVariable (
                      L"Setup",
                      &gSetupVariableGuid,
                      gSetupVariableAttributes,
                      sizeof (SETUP_DATA),
                      &mSetupData
                      );

      //
      // Update OcSetup variable to clear the flag
      //
      mOcSetupData.OcInterfaceRtUpdated = 0;
      Status = gRT->SetVariable (
                      L"OcSetup",
                      &gOcSetupVariableGuid,
                      gOcVariableAttributes,
                      OcVariableSize,
                      &mOcSetupData
                      );
      Status = gBS->LocateProtocol (
                    &gWdtProtocolGuid,
                    NULL,
                    (VOID **) &gWdtDxe
                    );
      if (!EFI_ERROR (Status)) {
        gWdtDxe->ReloadAndStart(WDT_TIMEOUT_VALUE);
        gWdtDxe->AllowKnownReset();
      }
      DEBUG ((DEBUG_INFO, "OverclockDxe Setting recently modified after synched with RT support. Warm Reset!\n"));
      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Fast Should not be enabled when overclocking is enabled .
  //
  if (mSetupData.FastBoot == 1) {
    mSetupData.FastBoot = 0;
    Status = gRT->SetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    gSetupVariableAttributes,
                    VariableSize,
                    &mSetupData
                    );
  }

  Status = gBS->LocateProtocol(&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoHobProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "Warning:MemInfoHobProtocol not installed, registering callback\n"));
    //
    // Update Memory timing Setup variables with the current MRC configured values
    //
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    GetCurrentMrcSettingsAndInitOcDefaults,
                    NULL,
                    &gMemoryUpdateEvent
                    );
    ASSERT_EFI_ERROR (Status);

    Status = gBS->RegisterProtocolNotify (
                    &gMemInfoProtocolGuid,
                    gMemoryUpdateEvent,
                    &gMemoryUpdateRegistration
                    );
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG ((DEBUG_INFO, "Found MemInfoHobProtocol .. \n"));
    GetCurrentMrcSettingsAndInitOcDefaults (NULL, NULL);
  }

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gOverClockProtocolGuid,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (
                  &gWdtProtocolGuid,
                  NULL,
                  (VOID **) &gWdtDxe
                  );
  ASSERT_EFI_ERROR (Status);

  gWdtTimeOut = gWdtDxe->CheckStatus ();

  if (gWdtTimeOut || (mSetupData.PlatformUnstable == 1)) {
    DEBUG ((DEBUG_WARN, "Warning: OverclockDxe WDT Timeout Detected. Reseting settings to default\n"));
    RestoreDefaultHWValues ();
  } else {
    Status = gRT->SetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    gSetupVariableAttributes,
                    VariableSize,
                    &mSetupData
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // Update BCLK Settings
    //
    BclkSettings ();
  }
  //
  // DDR frequency is updated with MemInfoHob->MrcOutputData.MCFrequency when OC is enabled in
  // Setup. This will cause S3data to differ from Setup data on first s3 resume cauisng an reset.
  // Issued an reset after OC initialisation to store the updated ddrfreq in s3data
  //
  if (gResetRequired) {
    DEBUG ((DEBUG_INFO, "Issuing cold reset to OC values with S3 data \n"));
    gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
  }

  //
  // OverclockingSupport has been enabled hence we run to here, then update OC setupdata again in case of
  // any setup token has been updated by last boot to BIOS Setup before continue booting
  //
  SyncOcSetupValue (COPY_SETUP_TO_OCSETUP); // Copy mSetupData, mCpuSetupData and mSaSetupData to mOcSetupData
  Status = gRT->SetVariable (
                  L"OcSetup",
                  &gOcSetupVariableGuid,
                  gOcVariableAttributes,
                  OcVariableSize,
                  &mOcSetupData
                  );

  return EFI_SUCCESS;
}

/**
  Updates memory timing setup variable with current MRC settings and then calls InitOCDefaultValues().

  @param[in] Event    - EFI callback parameter, not used here
  @param[in] Context  - EFI callback parameter, not used here
**/
VOID
EFIAPI
GetCurrentMrcSettingsAndInitOcDefaults (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  EFI_STATUS                Status;
  MEM_INFO_PROTOCOL         *MemInfoHobProtocol;
  MEMORY_INFO_DATA          *MemInfoData;
  MEMORY_TIMING             *MemoryTiming;

  DEBUG ((DEBUG_INFO, "In GetCurrentMrcSettingsAndInitOcDefaults.\n"));

  Status = gBS->LocateProtocol (&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoHobProtocol);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Found Mem Info Hob, updating setup.\n"));
    MemInfoData              = &MemInfoHobProtocol->MemInfoData;
    MemoryTiming             = &MemInfoData->Timing[MemInfoData->Profile];
    mSaSetup.tCL             = (UINT8) MemoryTiming->tCL;
    mSaSetup.tCWL            = (UINT8) MemoryTiming->tCWL;
    mSaSetup.tFAW            = MemoryTiming->tFAW;
    mSaSetup.tRAS            = MemoryTiming->tRAS;
    mSaSetup.tRCDtRP         = (UINT8) MemoryTiming->tRCDtRP;
    mSaSetup.tREFI           = MemoryTiming->tREFI;
    mSaSetup.tRFC            = MemoryTiming->tRFC;
    mSaSetup.tRRD            = (UINT8) MemoryTiming->tRRD;
    mSaSetup.tRTP            = (UINT8) MemoryTiming->tRTP;
    mSaSetup.tWR             = (UINT8) MemoryTiming->tWR;
    mSaSetup.tWTR            = (UINT8) MemoryTiming->tWTR;
    mSaSetup.NModeSupport    = (UINT8) MemoryTiming->NMode;
    mSaSetup.DdrRefClk       = MemInfoData->RefClk;
    mSaSetup.DdrRatio        = MemInfoData->Ratio;

    mSaSetup.MemoryVoltage = MemInfoData->VddVoltage[MemInfoData->Profile];
    mSaSetup.DdrFreqLimit  = MemInfoData->ddrFreqMax;

    DEBUG ((DEBUG_INFO, "tCL %d\n tRCD/tRP %d\n tRAS %d\n tRFC %d\n tWTR %d\n tRTP %d\n tWR %d\n tRRD %d\n tFAW %d\n",
            mSaSetup.tCL,
            mSaSetup.tRCDtRP,
            mSaSetup.tRAS,
            mSaSetup.tRFC,
            mSaSetup.tWTR,
            mSaSetup.tRTP,
            mSaSetup.tWR,
            mSaSetup.tRRD,
            mSaSetup.tFAW));

    DEBUG ((DEBUG_INFO, "DdrFreqLimit: %d, DDR RefClk = %d, Ratio = %d, VDD = %d mV\n",
      mSaSetup.DdrFreqLimit, ((mSaSetup.DdrRefClk == 1) ? 100 : 133), mSaSetup.DdrRatio, mSaSetup.MemoryVoltage));
  }

  //
  // Initalize OC defaults
  //
  Status = InitOCDefaultValues ();
}

/**
  Get current CPU BCLK settings and update setup variable

**/
VOID
BclkSettings (
  VOID
  )
{
  EFI_STATUS                       Status;
  BOOLEAN                          BclkModified;
  UINT8                            ResetType;
  UINT32                           CurrentFrequency;
  UINTN                            VariableSize;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP BclkSettings;

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &gSaSetupVariableAttributes,
                  &VariableSize,
                  &mSaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  BclkModified = FALSE;
  //
  // In case there is an error, the Bclk should be at the default setting on 100 Mhz
  //
  CurrentFrequency = 100000000;

  //
  //  Get Clock 2 Settings
  //
  SetMem (&BclkSettings, sizeof (ICC_GETSET_CLOCK_SETTINGS_REQRSP), 0);

  BclkSettings.ReqClock = CLOCK1;
  Status = HeciGetIccClockSettings (&BclkSettings);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "ERROR:OverClocLibDxe Get Clock Settings messge failed, clock 2. Status = %r\n", Status));
    goto ICC_SHUTDOWN;
  }

  DEBUG ((DEBUG_INFO, "INFO:OverClockLibDxe current BCLK frequency  = %dkHz\n", BclkSettings.Freq / 1000));

  if (mSaSetup.BclkOverride) {
    BclkSettings.Freq = mSaSetup.BclkFrequency * 10000;
    DEBUG ((DEBUG_INFO, "INFO:OverClocLibDxe new BCLK frequency  = %dkHz\n", BclkSettings.Freq / 1000));
    BclkSettings.ReqClock = CLOCK1;
    Status = HeciSetIccClockSettings (&BclkSettings);

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ERROR:OverClocLibDxe failed to SetClockSettings, Status = %r\n", Status));
      goto ICC_SHUTDOWN;
    }
    //
    // if Bclk was successfully modified, change the way this function ends
    //
    BclkModified = TRUE;
  }

ICC_SHUTDOWN:
  //
  // Clean up
  //
  mSaSetup.BclkOverride = 0;
  if (BclkModified == FALSE) {
    mSaSetup.BclkFrequency = CurrentFrequency / 10000;
  }
  Status = gRT->SetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  gSaSetupVariableAttributes,
                  VariableSize,
                  &mSaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // If Bclk was succesfully modified, reboot platform
  //
  if (BclkModified == TRUE) {
    gWdtDxe->ReloadAndStart (2);
    gWdtDxe->AllowKnownReset ();
    DEBUG ((DEBUG_INFO, "OverclockDxe IccOverClocking Setting recently modified. Cold Reset!\n"));
    ResetType = 0xE;
    IoWrite8 (0xCF9, ResetType);
  }
}

/**
  Store the default PowerLimt2 value

  @retval EFI_SUCCESS         - The function completed successfully.
**/
EFI_STATUS
StoreDefaultPowerLimit2Value (
  VOID
  )
{
  EFI_STATUS            Status;
  UINT16                Power;
  UINT16                Current;
  UINT8                 CoreRatio1;
  UINT8                 CoreRatio2;
  UINT8                 CoreRatio3;
  UINT8                 CoreRatio4;
  UINT8                 CoreRatio5;
  UINT8                 CoreRatio6;
  UINT8                 CoreRatio7;
  UINT8                 CoreRatio8;
  UINT16                PowerLimit1;
  UINT16                PowerLimit2;
  UINT8                 PowerLimit1Time;
  UINTN                 VariableSize;

  //
  // Since BIOS cannot allow XTU to program fractional values for Power Limit 2, we need to configure Power Limit 2 to
  // Floor (1.25 * Power Limit 1) as PPM will program 1.25 * TDP
  //
  if (mCpuSetup.PowerLimit2Power == 0) {
    ReadTurboValues (
      &Power,
      &Current,
      &CoreRatio1,
      &CoreRatio2,
      &CoreRatio3,
      &CoreRatio4,
      &CoreRatio5,
      &CoreRatio6,
      &CoreRatio7,
      &CoreRatio8,
      &PowerLimit1,
      &PowerLimit2,
      &PowerLimit1Time
      );

    //
    // PowerLimit1 is stored as 1/8W value in MSR. Need to convert this value to 1.25 PL1 into milliwatts for setupdata.
    // so, PL2 = (PL1*1.25)/8 = PL2 W/1000 = PL2 mW
    //
    mCpuSetup.PowerLimit2Power = (((125*PowerLimit1)/100)/8)*1000;
    mCpuSetup.PowerLimit2Default = (UINT16) PowerLimit2;

    VariableSize = sizeof (CPU_SETUP);
    Status = gRT->SetVariable (
                    L"CpuSetup",
                    &gCpuSetupVariableGuid,
                    gCpuSetupVariableAttributes,
                    VariableSize,
                    &mCpuSetup
                    );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}


/**
  Initialize OC default setup variables.

  @retval EFI_SUCCESS         - The function completed successfully.
**/
EFI_STATUS
InitOCDefaultValues (
  VOID
  )
{
  UINT16                Power;
  UINT16                Current;
  UINT8                 FusedP0Ratio;
  UINT8                 CoreRatio1;
  UINT8                 CoreRatio2;
  UINT8                 CoreRatio3;
  UINT8                 CoreRatio4;
  UINT8                 CoreRatio5;
  UINT8                 CoreRatio6;
  UINT8                 CoreRatio7;
  UINT8                 CoreRatio8;
  UINT16                PowerLimit1;
  UINT16                PowerLimit2;
  UINT8                 PowerLimit1Time;
  MSR_REGISTER          RingRatioMsr;
  UINT8                 RingRatioMax;
  UINT8                 RingRatioMin;
  UINT8                 Index;

  //
  // Store the Factory configured values if IsOcDefaultsInitalized == 0.
  // IsOcDefaultsInitalized will be 0 :
  //    1. During first boot
  //    2. If User goes into BIOS setup and selects: Restore Defaults
  //
  if (mSetupData.IsOcDefaultsInitalized == 0) {

    mSetupData.IsOcDefaultsInitalized = 1;
    gResetRequired = TRUE;
    mSetupData.PlatformUnstable = 0;

    //Store the Factory Configured (default) Non-Turbo Mode Values.
    mCpuSetup.FlexRatioOverrideDefault = MaxNonTurboRatio_Factoryvalue();
    mCpuSetup.CpuRatio = mCpuSetup.FlexRatioOverrideDefault;

    mCpuSetup.TurboModeDefault = 1;
    mCpuSetup.EnableGvDefault = 1;

    mCpuSetup.OverclockingLockDefault = 0;

    //
    // Store the Factory Configured (default) MaxEfficiency Ratio Values.
    //
    mCpuSetup.MaxEfficiencyRatio = MaxEfficiencyRatio_factory ();
    mCpuSetup.MaxNonTurboRatio = MaxNonTurboRatio_Factoryvalue ();

    //Store the Factory Configured (default) Turbo Ratio Values.
    ReadTurboValues (
      &Power,
      &Current,
      &CoreRatio1,
      &CoreRatio2,
      &CoreRatio3,
      &CoreRatio4,
      &CoreRatio5,
      &CoreRatio6,
      &CoreRatio7,
      &CoreRatio8,
      &PowerLimit1,
      &PowerLimit2,
      &PowerLimit1Time
      );

    mCpuSetup.PowerLimit1Default = PowerLimit1;
    mCpuSetup.PowerLimit2Default = PowerLimit2;
    mCpuSetup.PowerLimit1TimeDefault = PowerLimit1Time;

    FusedP0Ratio = MaxTurboRatio_Factoryvalue();
    if ((FusedP0Ratio != 0) && (FusedP0Ratio >= CoreRatio2)) {
      CoreRatio1 = FusedP0Ratio;
    }
    mCpuSetup.RatioLimit1Default = CoreRatio1;
    mCpuSetup.RatioLimit2Default = CoreRatio2;
    mCpuSetup.RatioLimit3Default = CoreRatio3;
    mCpuSetup.RatioLimit4Default = CoreRatio4;
    mCpuSetup.RatioLimit5Default = CoreRatio5;
    mCpuSetup.RatioLimit6Default = CoreRatio6;
    mCpuSetup.RatioLimit7Default = CoreRatio7;
    mCpuSetup.RatioLimit8Default = CoreRatio8;

    mCpuSetup.OverclockingLock = 0;

    //
    // Save the current frequency and memory timing as safe settings.
    //
    mSaSetup.DdrRefClkDefault = mSaSetup.DdrRefClk;
    mSaSetup.DdrRatioDefault  = mSaSetup.DdrRatio;
    mSaSetup.tCLDefault       = mSaSetup.tCL;
    mSaSetup.tCWLDefault      = mSaSetup.tCWL;
    mSaSetup.tFAWDefault      = mSaSetup.tFAW;
    mSaSetup.tRASDefault      = mSaSetup.tRAS;
    mSaSetup.tRCDtRPDefault   = mSaSetup.tRCDtRP;
    mSaSetup.tREFIDefault     = mSaSetup.tREFI;
    mSaSetup.tRFCDefault      = mSaSetup.tRFC;
    mSaSetup.tRRDDefault      = mSaSetup.tRRD;
    mSaSetup.tRTPDefault      = mSaSetup.tRTP;
    mSaSetup.tWRDefault       = mSaSetup.tWR;
    mSaSetup.tWTRDefault      = mSaSetup.tWTR;
    //
    // Default N-mode is AUTO
    //
    mSaSetup.NModeDefault = mSaSetup.NModeSupport;

    mSaSetup.MemoryVoltageDefault = 0;  // Platform default, no override

    //
    // Save boot up OC values as safe settings
    //
    mCpuSetup.CoreMaxOcRatioDefault            = mCpuSetup.CoreMaxOcRatio;
    mCpuSetup.CoreVoltageModeDefault           = mCpuSetup.CoreVoltageMode;
    mCpuSetup.CoreVoltageOverrideDefault       = mCpuSetup.CoreVoltageOverride;
    mCpuSetup.CoreVoltageOffsetDefault         = mCpuSetup.CoreVoltageOffset;
    mCpuSetup.CoreVoltageOffsetPrefixDefault   = mCpuSetup.CoreVoltageOffsetPrefix;
    mCpuSetup.CoreExtraTurboVoltageDefault     = mCpuSetup.CoreExtraTurboVoltage;
    mCpuSetup.RingMaxOcRatioDefault            = mCpuSetup.RingMaxOcRatio;
    mCpuSetup.RingVoltageModeDefault           = mCpuSetup.RingVoltageMode;
    mCpuSetup.RingVoltageOverrideDefault       = mCpuSetup.RingVoltageOverride;
    mCpuSetup.RingVoltageOffsetDefault         = mCpuSetup.RingVoltageOffset;
    mCpuSetup.RingVoltageOffsetPrefixDefault   = mCpuSetup.RingVoltageOffsetPrefix;
    mCpuSetup.RingExtraTurboVoltageDefault     = mCpuSetup.RingExtraTurboVoltage;
    mCpuSetup.Avx2RatioOffsetDefault           = mCpuSetup.Avx2RatioOffset;

    for (Index = 0; Index < 4 ; Index++) {
      mCpuSetup.IccMaxDefault[Index]           = mCpuSetup.IccMax[Index];
    }

    //
    // Ring Ratio default is stored in Ring Ratio MSR
    //
    RingRatioMsr.Qword = AsmReadMsr64 (MSR_UNCORE_RATIO_LIMIT);
    RingRatioMax = RingRatioMsr.Bytes.FirstByte & V_MSR_RING_RATIO_LIMIT_MASK;
    mCpuSetup.MaxRingRatioLimitDefault        = RingRatioMax;
    RingRatioMin = RingRatioMsr.Bytes.SecondByte & V_MSR_RING_RATIO_LIMIT_MASK;
    mCpuSetup.MinRingRatioLimitDefault        = RingRatioMin;
    mSaSetup.UncoreVoltageOffsetDefault       = mSaSetup.UncoreVoltageOffset;
    mSaSetup.UncoreVoltageOffsetPrefixDefault = mSaSetup.UncoreVoltageOffsetPrefix;
    mSaSetup.GtMaxOcRatioDefault              = mSaSetup.GtMaxOcRatio;
    mSaSetup.GtVoltageModeDefault             = mSaSetup.GtVoltageMode;
    mSaSetup.GtVoltageOffsetDefault           = mSaSetup.GtVoltageOffset;
    mSaSetup.GtVoltageOffsetPrefixDefault     = mSaSetup.GtVoltageOffsetPrefix;
    mSaSetup.GtVoltageOverrideDefault         = mSaSetup.GtVoltageOverride;
    mSaSetup.GtExtraTurboVoltageDefault       = mSaSetup.GtExtraTurboVoltage;
    mSaSetup.GtusMaxOcRatioDefault            = mSaSetup.GtusMaxOcRatio;
    mSaSetup.GtusVoltageModeDefault           = mSaSetup.GtusVoltageMode;
    mSaSetup.GtusVoltageOffsetDefault         = mSaSetup.GtusVoltageOffset;
    mSaSetup.GtusVoltageOffsetPrefixDefault   = mSaSetup.GtusVoltageOffsetPrefix;
    mSaSetup.GtusVoltageOverrideDefault       = mSaSetup.GtusVoltageOverride;
    mSaSetup.GtusExtraTurboVoltageDefault     = mSaSetup.GtusExtraTurboVoltage;

    //
    // Update the setup data variables to save the default values
    //
    gRT->SetVariable (
           L"CpuSetup",
           &gCpuSetupVariableGuid,
           gCpuSetupVariableAttributes,
           sizeof (CPU_SETUP),
           &mCpuSetup
           );

    gRT->SetVariable (
           L"SaSetup",
           &gSaSetupVariableGuid,
           gSaSetupVariableAttributes,
           sizeof (SA_SETUP),
           &mSaSetup
           );

    gRT->SetVariable (
           L"Setup",
           &gSetupVariableGuid,
           gSetupVariableAttributes,
           sizeof (SETUP_DATA),
           &mSetupData
           );
  }

  return EFI_SUCCESS;
}


/**
  ReStore the Factory Configured Default Values to Setup. This routine
  should be called if a particular setup change causes hang.

  @retval EFI_SUCCESS         - The function completed successfully.
**/
EFI_STATUS
RestoreDefaultHWValues (
  VOID
  )
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;
  UINT8                 Index;

  mSetupData.IsOcDefaultsInitalized = 1;
  mSetupData.PlatformUnstable = 0;

  mSaSetup.BclkOverride = DISABLE_SUPPORT;
  mSaSetup.BclkFrequency = 10000; // @todo: Read current settings and store here.

  //Store the Factory Configured (default) Non-Turbo Mode Values.
  mCpuSetup.CpuRatio  = mCpuSetup.FlexRatioOverrideDefault;

  mCpuSetup.TurboMode = mCpuSetup.TurboModeDefault;
  mCpuSetup.EnableGv  = mCpuSetup.EnableGvDefault;

  //Store the Factory Configured (default) MaxEfficiency Ratio Values.
  mCpuSetup.MaxEfficiencyRatio = MaxEfficiencyRatio_factory ();
  mCpuSetup.MaxNonTurboRatio = MaxNonTurboRatio_Factoryvalue ();

  mSaSetup.MemoryVoltage  = mSaSetup.MemoryVoltageDefault;
  mSaSetup.DdrRefClk      = mSaSetup.DdrRefClkDefault;
  mSaSetup.DdrRatio       = mSaSetup.DdrRatioDefault;

  // Get the setup default of tCL, tRCD/tRP, tRAS, tWR, tRFC, tRRD, tWTR, tRTP & tFAW.
  mSaSetup.tCL      = mSaSetup.tCLDefault;
  mSaSetup.tCWL     = mSaSetup.tCWLDefault;
  mSaSetup.tFAW     = mSaSetup.tFAWDefault;
  mSaSetup.tRAS     = mSaSetup.tRASDefault;
  mSaSetup.tRCDtRP  = mSaSetup.tRCDtRPDefault;
  mSaSetup.tREFI    = mSaSetup.tREFIDefault;
  mSaSetup.tRFC     = mSaSetup.tRFCDefault;
  mSaSetup.tRRD     = mSaSetup.tRRDDefault;
  mSaSetup.tRTP     = mSaSetup.tRTPDefault;
  mSaSetup.tWR      = mSaSetup.tWRDefault;
  mSaSetup.tWTR     = mSaSetup.tWTRDefault;

  mSaSetup.NModeSupport = mSaSetup.NModeDefault;
  mSaSetup.SpdProfileSelected = 0;

  mCpuSetup.RatioLimit1 = mCpuSetup.RatioLimit1Default;
  mCpuSetup.RatioLimit2 = mCpuSetup.RatioLimit2Default;
  mCpuSetup.RatioLimit3 = mCpuSetup.RatioLimit3Default;
  mCpuSetup.RatioLimit4 = mCpuSetup.RatioLimit4Default;
  mCpuSetup.RatioLimit5 = mCpuSetup.RatioLimit5Default;
  mCpuSetup.RatioLimit6 = mCpuSetup.RatioLimit6Default;
  mCpuSetup.RatioLimit7 = mCpuSetup.RatioLimit7Default;
  mCpuSetup.RatioLimit8 = mCpuSetup.RatioLimit8Default;

  mCpuSetup.PowerLimit2Power = mCpuSetup.PowerLimit2Default;
  mCpuSetup.PowerLimit1      = mCpuSetup.PowerLimit1Default;
  mCpuSetup.LongDurationPwrLimitOverride = 0;

  mCpuSetup.OverclockingLock = mCpuSetup.OverclockingLockDefault;

  //
  // Restore default FIVR settings
  //
  mCpuSetup.CoreMaxOcRatio            = mCpuSetup.CoreMaxOcRatioDefault;
  mCpuSetup.CoreVoltageMode           = mCpuSetup.CoreVoltageModeDefault;
  mCpuSetup.CoreVoltageOverride       = mCpuSetup.CoreVoltageOverrideDefault;
  mCpuSetup.CoreVoltageOffset         = mCpuSetup.CoreVoltageOffsetDefault;
  mCpuSetup.CoreVoltageOffsetPrefix   = mCpuSetup.CoreVoltageOffsetPrefixDefault;
  mCpuSetup.CoreExtraTurboVoltage     = mCpuSetup.CoreExtraTurboVoltageDefault;
  mCpuSetup.MaxRingRatioLimit         = mCpuSetup.MaxRingRatioLimitDefault;
  mCpuSetup.MinRingRatioLimit         = mCpuSetup.MinRingRatioLimitDefault;
  mSaSetup.UncoreVoltageOffset        = mSaSetup.UncoreVoltageOffsetDefault;
  mSaSetup.UncoreVoltageOffsetPrefix  = mSaSetup.UncoreVoltageOffsetPrefixDefault;
  mSaSetup.GtMaxOcRatio               = mSaSetup.GtMaxOcRatioDefault;
  mSaSetup.GtVoltageMode              = mSaSetup.GtVoltageModeDefault;
  mSaSetup.GtVoltageOffset            = mSaSetup.GtVoltageOffsetDefault;
  mSaSetup.GtVoltageOffsetPrefix      = mSaSetup.GtVoltageOffsetPrefixDefault;
  mSaSetup.GtVoltageOverride          = mSaSetup.GtVoltageOverrideDefault;
  mSaSetup.GtExtraTurboVoltage        = mSaSetup.GtExtraTurboVoltageDefault;
  mSaSetup.GtusMaxOcRatio             = mSaSetup.GtusMaxOcRatioDefault;
  mSaSetup.GtusVoltageMode            = mSaSetup.GtusVoltageModeDefault;
  mSaSetup.GtusVoltageOffset          = mSaSetup.GtusVoltageOffsetDefault;
  mSaSetup.GtusVoltageOffsetPrefix    = mSaSetup.GtusVoltageOffsetPrefixDefault;
  mSaSetup.GtusVoltageOverride        = mSaSetup.GtusVoltageOverrideDefault;
  mSaSetup.GtusExtraTurboVoltage      = mSaSetup.GtusExtraTurboVoltageDefault;
  mCpuSetup.Avx2RatioOffset           = mCpuSetup.Avx2RatioOffsetDefault;

  for (Index = 0; Index < 4 ; Index++) {
    mCpuSetup.IccMax[Index]           = mCpuSetup.IccMaxDefault[Index];
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->SetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  gSaSetupVariableAttributes,
                  VariableSize,
                  &mSaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->SetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  gCpuSetupVariableAttributes,
                  VariableSize,
                  &mCpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Synch up value between OcSetup variable and Setup variable.
  All variable totoken accessed by XTU at RT must be listed and synched here.

  @param[in]  CopyToOcSetup     - COPY_SETUP_TO_OCSETUP (TRUE),
                                  copy data from Setup variable to OcSetup variable
                                  COPY_OCSETUP_TO_SETUP (FALSE),
                                  copy data from OcSetup variable to Setup variable
**/
VOID
SyncOcSetupValue (
  IN BOOLEAN CopyToOcSetup
  )
{
  UINT8  Index;
  if (CopyToOcSetup == COPY_SETUP_TO_OCSETUP) {
    //
    // Sync SA_SETUP token
    //
    mOcSetupData.tCL                          = mSaSetup.tCL;
    mOcSetupData.tRCDtRP                      = mSaSetup.tRCDtRP;
    mOcSetupData.tRAS                         = mSaSetup.tRAS;
    mOcSetupData.tWR                          = mSaSetup.tWR;
    mOcSetupData.tRFC                         = mSaSetup.tRFC;
    mOcSetupData.tRRD                         = mSaSetup.tRRD;
    mOcSetupData.tWTR                         = mSaSetup.tWTR;
    mOcSetupData.tRTP                         = mSaSetup.tRTP;
    mOcSetupData.tFAW                         = mSaSetup.tFAW;
    mOcSetupData.NModeSupport                 = mSaSetup.NModeSupport;
    mOcSetupData.DdrRatioDefault              = mSaSetup.DdrRatioDefault;
    mOcSetupData.DdrRatio                     = mSaSetup.DdrRatio;
    switch (mSaSetup.MemoryVoltage) {
      case 0:
        mOcSetupData.MemoryVoltage = 0;
        break;
      case 1200:
        mOcSetupData.MemoryVoltage = 1;
        break;
      case 1250:
        mOcSetupData.MemoryVoltage = 2;
        break;
      case 1300:
        mOcSetupData.MemoryVoltage = 3;
        break;
      case 1350:
        mOcSetupData.MemoryVoltage = 4;
        break;
      case 1400:
        mOcSetupData.MemoryVoltage = 5;
        break;
      case 1450:
        mOcSetupData.MemoryVoltage = 6;
        break;
      case 1500:
        mOcSetupData.MemoryVoltage = 7;
        break;
      case 1550:
        mOcSetupData.MemoryVoltage = 8;
        break;
      case 1600:
        mOcSetupData.MemoryVoltage = 9;
        break;
      case 1650:
        mOcSetupData.MemoryVoltage = 10;
        break;
      default:
        mOcSetupData.MemoryVoltage                = mSaSetup.MemoryVoltage;
        break;
    }
    mOcSetupData.BclkFrequency                = mSaSetup.BclkFrequency;
    mOcSetupData.GtMaxOcRatio                 = mSaSetup.GtMaxOcRatio;
    mOcSetupData.SpdProfileSelected           = mSaSetup.SpdProfileSelected;
    mOcSetupData.DdrRefClk                    = mSaSetup.DdrRefClk;
    mOcSetupData.GtVoltageMode                = mSaSetup.GtVoltageMode;
    mOcSetupData.GtVoltageOffset              = mSaSetup.GtVoltageOffset;
    mOcSetupData.GtVoltageOffsetPrefix        = mSaSetup.GtVoltageOffsetPrefix;
    mOcSetupData.GtVoltageOverride            = mSaSetup.GtVoltageOverride;
    mOcSetupData.GtExtraTurboVoltage          = mSaSetup.GtExtraTurboVoltage;
    mOcSetupData.UncoreVoltageOffset          = mSaSetup.UncoreVoltageOffset;
    mOcSetupData.UncoreVoltageOffsetPrefix    = mSaSetup.UncoreVoltageOffsetPrefix;
    mOcSetupData.GtusMaxOcRatio                = mSaSetup.GtusMaxOcRatio;
    mOcSetupData.GtusVoltageMode               = mSaSetup.GtusVoltageMode;
    mOcSetupData.GtusVoltageOffset             = mSaSetup.GtusVoltageOffset;
    mOcSetupData.GtusVoltageOffsetPrefix       = mSaSetup.GtusVoltageOffsetPrefix;
    mOcSetupData.GtusVoltageOverride           = mSaSetup.GtusVoltageOverride;
    mOcSetupData.GtusExtraTurboVoltage         = mSaSetup.GtusExtraTurboVoltage;
    //
    // Sync CPU_SETUP token
    //
    mOcSetupData.OverclockingSupport          = mCpuSetup.OverclockingSupport;
    mOcSetupData.EnableGv                     = mCpuSetup.EnableGv;
    mOcSetupData.CpuRatio                     = mCpuSetup.CpuRatio;
    mOcSetupData.CpuRatioOverride             = mCpuSetup.CpuRatioOverride;
    mOcSetupData.CoreVoltageMode              = mCpuSetup.CoreVoltageMode;
    mOcSetupData.CoreVoltageOverride          = mCpuSetup.CoreVoltageOverride;
    mOcSetupData.CoreExtraTurboVoltage        = mCpuSetup.CoreExtraTurboVoltage;
    mOcSetupData.CoreVoltageOffset            = mCpuSetup.CoreVoltageOffset;
    mOcSetupData.CoreVoltageOffsetPrefix      = mCpuSetup.CoreVoltageOffsetPrefix;
    mOcSetupData.PowerLimit1Time              = mCpuSetup.PowerLimit1Time;
    mOcSetupData.TurboMode                    = mCpuSetup.TurboMode;
    mOcSetupData.RatioLimit1                  = mCpuSetup.RatioLimit1;
    mOcSetupData.RatioLimit2                  = mCpuSetup.RatioLimit2;
    mOcSetupData.RatioLimit3                  = mCpuSetup.RatioLimit3;
    mOcSetupData.RatioLimit4                  = mCpuSetup.RatioLimit4;
    mOcSetupData.RatioLimit5                  = mCpuSetup.RatioLimit5;
    mOcSetupData.RatioLimit6                  = mCpuSetup.RatioLimit6;
    mOcSetupData.RatioLimit7                  = mCpuSetup.RatioLimit7;
    mOcSetupData.RatioLimit8                  = mCpuSetup.RatioLimit8;
    mOcSetupData.TurboPowerLimitLock          = mCpuSetup.TurboPowerLimitLock;
    mOcSetupData.PowerLimit1                  = mCpuSetup.PowerLimit1;
    mOcSetupData.PowerLimit1Default           = mCpuSetup.PowerLimit1Default;
    mOcSetupData.PowerLimit2                  = mCpuSetup.PowerLimit2;
    mOcSetupData.PowerLimit2Power             = mCpuSetup.PowerLimit2Power;
    mOcSetupData.PowerLimit2Default           = mCpuSetup.PowerLimit2Default;
    mOcSetupData.RingMaxOcRatio               = mCpuSetup.RingMaxOcRatio;
    mOcSetupData.RingVoltageMode              = mCpuSetup.RingVoltageMode;
    mOcSetupData.RingVoltageOverride          = mCpuSetup.RingVoltageOverride;
    mOcSetupData.RingExtraTurboVoltage        = mCpuSetup.RingExtraTurboVoltage;
    mOcSetupData.RingVoltageOffset            = mCpuSetup.RingVoltageOffset;
    mOcSetupData.RingVoltageOffsetPrefix      = mCpuSetup.RingVoltageOffsetPrefix;
    mOcSetupData.OverclockingLock             = mCpuSetup.OverclockingLock;
    mOcSetupData.LongDurationPwrLimitOverride = mCpuSetup.LongDurationPwrLimitOverride;
    mOcSetupData.WDTSupportforNextOSBoot      = mCpuSetup.WDTSupportforNextOSBoot;
    mOcSetupData.TimeforNextOSBoot            = mCpuSetup.TimeforNextOSBoot;
    mOcSetupData.Avx2RatioOffset              = mCpuSetup.Avx2RatioOffset;

    for (Index = 0; Index < 4 ; Index++) {
      mOcSetupData.IccMax[Index]              = mCpuSetup.IccMax[Index];
    }

    //
    // Sync SETUP_DATA token
    //
    mOcSetupData.PlatformUnstable             = mSetupData.PlatformUnstable;
  } else {
    //
    // Sync SA_SETUP token
    //
    mSaSetup.tCL                            = mOcSetupData.tCL;
    mSaSetup.tRCDtRP                        = mOcSetupData.tRCDtRP;
    mSaSetup.tRAS                           = mOcSetupData.tRAS;
    mSaSetup.tWR                            = mOcSetupData.tWR;
    mSaSetup.tRFC                           = mOcSetupData.tRFC;
    mSaSetup.tRRD                           = mOcSetupData.tRRD;
    mSaSetup.tWTR                           = mOcSetupData.tWTR;
    mSaSetup.tRTP                           = mOcSetupData.tRTP;
    mSaSetup.tFAW                           = mOcSetupData.tFAW;
    mSaSetup.tWRDefault                     = mOcSetupData.tWRDefault;
    mSaSetup.NModeSupport                   = mOcSetupData.NModeSupport;
    mSaSetup.DdrRatioDefault                = mOcSetupData.DdrRatioDefault;
    mSaSetup.DdrRatio                       = mOcSetupData.DdrRatio;
    mSaSetup.MemoryVoltage                  = mOcSetupData.MemoryVoltage;
    mSaSetup.BclkOverride                   = mOcSetupData.BclkOverride;
    mSaSetup.BclkFrequency                  = mOcSetupData.BclkFrequency;
    mSaSetup.GtMaxOcRatio                   = mOcSetupData.GtMaxOcRatio;
    mSaSetup.SpdProfileSelected             = mOcSetupData.SpdProfileSelected;
    mSaSetup.DdrRefClk                      = mOcSetupData.DdrRefClk;
    mSaSetup.GtVoltageMode                  = mOcSetupData.GtVoltageMode;
    mSaSetup.GtVoltageOffset                = mOcSetupData.GtVoltageOffset;
    mSaSetup.GtVoltageOffsetPrefix          = mOcSetupData.GtVoltageOffsetPrefix;
    mSaSetup.GtVoltageOverride              = mOcSetupData.GtVoltageOverride;
    mSaSetup.GtExtraTurboVoltage            = mOcSetupData.GtExtraTurboVoltage;
    mSaSetup.UncoreVoltageOffset            = mOcSetupData.UncoreVoltageOffset;
    mSaSetup.UncoreVoltageOffsetPrefix      = mOcSetupData.UncoreVoltageOffsetPrefix;
    mSaSetup.GtusMaxOcRatio                 = mOcSetupData.GtusMaxOcRatio;
    mSaSetup.GtusVoltageMode                = mOcSetupData.GtusVoltageMode;
    mSaSetup.GtusVoltageOffset              = mOcSetupData.GtusVoltageOffset;
    mSaSetup.GtusVoltageOffsetPrefix        = mOcSetupData.GtusVoltageOffsetPrefix;
    mSaSetup.GtusVoltageOverride            = mOcSetupData.GtusVoltageOverride;
    mSaSetup.GtusExtraTurboVoltage          = mOcSetupData.GtusExtraTurboVoltage;
    //
    // Sync CPU_SETUP token
    //
    mCpuSetup.OverclockingSupport           = mOcSetupData.OverclockingSupport;
    mCpuSetup.EnableGv                      = mOcSetupData.EnableGv;
    mCpuSetup.CpuRatio                      = mOcSetupData.CpuRatio;
    mCpuSetup.CpuRatioOverride              = mOcSetupData.CpuRatioOverride;
    mCpuSetup.CoreMaxOcRatio                = mOcSetupData.CoreMaxOcRatio;
    mCpuSetup.CoreVoltageMode               = mOcSetupData.CoreVoltageMode;
    mCpuSetup.CoreVoltageOverride           = mOcSetupData.CoreVoltageOverride;
    mCpuSetup.CoreExtraTurboVoltage         = mOcSetupData.CoreExtraTurboVoltage;
    mCpuSetup.CoreVoltageOffset             = mOcSetupData.CoreVoltageOffset;
    mCpuSetup.CoreVoltageOffsetPrefix       = mOcSetupData.CoreVoltageOffsetPrefix;
    mCpuSetup.PowerLimit1Time               = mOcSetupData.PowerLimit1Time;
    mCpuSetup.TurboMode                     = mOcSetupData.TurboMode;
    mCpuSetup.RatioLimit1                   = mOcSetupData.RatioLimit1;
    mCpuSetup.RatioLimit2                   = mOcSetupData.RatioLimit2;
    mCpuSetup.RatioLimit3                   = mOcSetupData.RatioLimit3;
    mCpuSetup.RatioLimit4                   = mOcSetupData.RatioLimit4;
    mCpuSetup.RatioLimit5                   = mOcSetupData.RatioLimit5;
    mCpuSetup.RatioLimit6                   = mOcSetupData.RatioLimit6;
    mCpuSetup.RatioLimit7                   = mOcSetupData.RatioLimit7;
    mCpuSetup.RatioLimit8                   = mOcSetupData.RatioLimit8;
    mCpuSetup.TurboPowerLimitLock           = mOcSetupData.TurboPowerLimitLock;
    mCpuSetup.PowerLimit1                   = mOcSetupData.PowerLimit1;
    mCpuSetup.PowerLimit1Default            = mOcSetupData.PowerLimit1Default;
    mCpuSetup.PowerLimit2                   = mOcSetupData.PowerLimit2;
    mCpuSetup.PowerLimit2Power              = mOcSetupData.PowerLimit2Power;
    mCpuSetup.PowerLimit2Default            = mOcSetupData.PowerLimit2Default;
    mCpuSetup.RingMaxOcRatio                = mOcSetupData.RingMaxOcRatio;
    mCpuSetup.RingVoltageMode               = mOcSetupData.RingVoltageMode;
    mCpuSetup.RingVoltageOverride           = mOcSetupData.RingVoltageOverride;
    mCpuSetup.RingExtraTurboVoltage         = mOcSetupData.RingExtraTurboVoltage;
    mCpuSetup.RingVoltageOffset             = mOcSetupData.RingVoltageOffset;
    mCpuSetup.RingVoltageOffsetPrefix       = mOcSetupData.RingVoltageOffsetPrefix;
    mCpuSetup.OverclockingLock              = mOcSetupData.OverclockingLock;
    mCpuSetup.LongDurationPwrLimitOverride  = mOcSetupData.LongDurationPwrLimitOverride;
    mCpuSetup.WDTSupportforNextOSBoot       = mOcSetupData.WDTSupportforNextOSBoot;
    mCpuSetup.TimeforNextOSBoot             = mOcSetupData.TimeforNextOSBoot;
    mCpuSetup.Avx2RatioOffset               = mOcSetupData.Avx2RatioOffset;

    for (Index = 0; Index < 4 ; Index++) {
      mCpuSetup.IccMax[Index]               = mOcSetupData.IccMax[Index];
    }

    //
    // Sync SETUP_DATA token
    //
    mSetupData.PlatformUnstable             = mOcSetupData.PlatformUnstable;
  }
}
