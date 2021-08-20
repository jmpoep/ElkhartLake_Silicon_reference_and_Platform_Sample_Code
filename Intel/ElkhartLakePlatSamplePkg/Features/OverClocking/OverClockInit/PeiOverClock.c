/** @file
  This file contains the code for CPU Overclocking and Recovery logic using TCO Timer

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#include <IccSetupData.h>
#include "PeiOverClock.h"
#include <Library/PeiPlatformLib.h>
#include <BupMsgs.h>
#include <Library/PeiMeLib.h>
#include <Library/SmbusInfoLib.h>

#ifndef MDEPKG_NDEBUG
#define WDT_TIMEOUT 120
#else
#define WDT_TIMEOUT 60
#endif

#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND 1
#endif

static EFI_PEI_PPI_DESCRIPTOR mOverClockPpiList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI |
    EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiOverClockPpiGuid,
    NULL
  }
};

/**
  This Function is called once SmbusPpi is installed. It does
  CPU Overclocking (Flex Ratio, Flex Vid and Bus Speed Override)

  @param[in] FileHandle     Pointer to the FFS file header
  @param[in] PeiServices    Pointer to the PEI services table

  @retval EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
PeiOverClockEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                      Status;
  EFI_STATUS                      Status2;
  EFI_STATUS                      Status3;
  SA_SETUP                        SaSetup;
  CPU_SETUP                       CpuSetup;
  SETUP_DATA                      SetupData;
  EFI_PEI_SMBUS2_PPI              *SmbusPpi;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
  UINTN                           VariableSize;
  UINT8                           WdtTimeOut;
  WDT_PPI                         *gWdtPei;
  BOOLEAN                         Ck505Present;
  EFI_SMBUS_DEVICE_ADDRESS        SlaveAddress;
  UINT8                           ClockAddress;
  UINTN                           Length;
  UINT8                           Data;
  EFI_SMBUS_DEVICE_COMMAND        Command;

  Status          = EFI_SUCCESS;
  Status2         = EFI_SUCCESS;
  Status3         = EFI_SUCCESS;
  WdtTimeOut      = 0;
  Ck505Present    = TRUE;

  Status = PeiServicesInstallPpi (mOverClockPpiList);
  if (EFI_ERROR (Status)){
    return Status;
  }

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &ReadOnlyVariable
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &gWdtPei
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = ReadOnlyVariable->GetVariable (
                               ReadOnlyVariable,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupData
                               );

  VariableSize = sizeof (SA_SETUP);
  Status2 = ReadOnlyVariable->GetVariable (
                               ReadOnlyVariable,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SaSetup
                               );

  VariableSize = sizeof (CPU_SETUP);
  Status3 = ReadOnlyVariable->GetVariable (
                               ReadOnlyVariable,
                               L"CpuSetup",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &CpuSetup
                               );

  if (EFI_ERROR (Status) || EFI_ERROR (Status2) || EFI_ERROR (Status3)) {
    //
    // If GetVariable fails, return EFI_SUCCESS asuming OC is Disabled.
    //
    return EFI_SUCCESS;
  }

  WdtTimeOut = gWdtPei->CheckStatus ();

  if (CpuSetup.OverclockingSupport == 0) {
    DEBUG ((DEBUG_INFO, "(OC) Overclocking is not enabled in BIOS setup.\n"));
    return EFI_SUCCESS;
  }

  //
  // Locate SMBUS PPI
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiSmbus2PpiGuid,
             0,
             NULL,
             (VOID **) &SmbusPpi
             );
  ASSERT_EFI_ERROR (Status);

  ClockAddress                    = CLOCK_CONTROLLER_SMBUS_ADDRESS;
  SlaveAddress.SmbusDeviceAddress = (UINTN)RShiftU64(ClockAddress, 1);
  Length                          = 1;
  //
  // Control Register 7 check Vendor ID
  //
  Command = 0x87;
  Status = SmbusPpi->Execute (
                      SmbusPpi,
                      SlaveAddress,
                      Command,
                      EfiSmbusReadByte,
                      FALSE,
                      &Length,
                      &Data
                      );

  if (EFI_ERROR (Status) || ((Data & 0x0F) != CK505_VENDOR_ID)) {
    Ck505Present = FALSE;
  }

  //
  // Clear SmBus Status Register
  //
  SmbusClearStatusReg ();

  ConfigFailedBootRecovery (&SetupData, &SaSetup, &CpuSetup, WdtTimeOut, Ck505Present);

  if ((!WdtTimeOut) || (SetupData.PlatformUnstable == 1)) {
    //
    // Start WDT Timer.
    //
    StartTimer (WDT_TIMEOUT);

    //
    // Program Processor Multiplier as per Setup data.
    //
    ProgramProcessorMultiplier (&CpuSetup);

    //
    // Program Processor Bus Speed as per Setup data (CK505 Programming) if Ck505 is Present.
    //
    if (Ck505Present) {
      ProgramBusSpeed (&CpuSetup, SmbusPpi);
    }

    if ((Ck505Present) && (!CpuSetup.BusSpeedEnable)) {
      DisableBusSpeedOverride (SmbusPpi);
    }
  }

  return EFI_SUCCESS;
}

/**
  This function will start the Watchdog Timer.

  @param[in] TimeoutValue       Time out value in seconds

  @retval EFI_SUCCESS           Function successfully executed.

  Appropiate failure code on error.
**/
EFI_STATUS
StartTimer (
  IN UINT32                   TimeoutValue
  )
{
  EFI_STATUS  Status;
  WDT_PPI     *gWdtPei;

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &gWdtPei
             );
  ASSERT_EFI_ERROR (Status);

  Status = gWdtPei->ReloadAndStart (TimeoutValue);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function implements the Recovery logic.

  @param[in] SetupData         Pointer to the SETUP_DATA buffer
  @param[in] SaSetup           Pointer to the SA_SETUP buffer
  @param[in] CpuSetup          Pointer to the CPU_SETUP buffer
  @param[in] WdtTimeOut        Wdt Time Out Status
  @param[in] Ck505Present      Ck505 Present Status

  @retval EFI_SUCCESS          Function successfully executed.
**/
EFI_STATUS
ConfigFailedBootRecovery (
  IN SETUP_DATA               *SetupData,
  IN SA_SETUP                 *SaSetup,
  IN CPU_SETUP                *CpuSetup,
  IN BOOLEAN                  WdtTimeOut,
  IN BOOLEAN                  Ck505Present
  )
{
  //
  // PlatformUnstable also needs to be treated as WDT Reset.
  //
  if ((WdtTimeOut) || (SetupData->PlatformUnstable == 1)) {
    //
    // Set the current override values (Hang Boot Value) to Dxe Phase through Hob,
    // in Dxe Phase we store these variable to Corresponding SetupHangValue Variable.
    //
    CpuSetup->CpuRatioOverride = 0;
    if (Ck505Present) {
      CpuSetup->BusSpeedEnable = 0;
    }

    //
    // Boot with Default Configuration Mode values. .
    //
    CpuSetup->CpuRatio = CpuSetup->FlexRatioOverrideDefault;
    if (Ck505Present) {
      CpuSetup->ProcessorBusSpeedOverride = CpuSetup->ProcessorBusSpeedOverrideDefault;
    }

    SaSetup->MemoryVoltage = SaSetup->MemoryVoltageDefault;
  }

  return EFI_SUCCESS;
}

/**
  Programs CPU Bus speed based on Setup variable.

  @param[in] CpuSetup          Pointer to the CPU_SETUP buffer
  @param[in] SmBusPpi          Pointer to the EFI_PEI_SMBUS2_PPI

  @retval EFI_SUCCESS          Function successfully executed.
**/
EFI_STATUS
ProgramBusSpeed (
  IN  CPU_SETUP                *CpuSetup,
  IN  EFI_PEI_SMBUS2_PPI       *SmbusPpi
  )
{
  EFI_STATUS                Status;
  EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress;
  UINTN                     Length;
  UINT8                     Data;
  UINT16                    NDividerValue;
  UINT16                    MDividerValue;
  UINT8                     Reg15;
  UINT8                     Reg16;
  UINT16                    CpuFrequencyMode;
  UINT16                    FrequencyResolution;
  UINT16                    TargetFrequency;
  EFI_SMBUS_DEVICE_COMMAND  Command;
  UINT8                     ClockAddress;

  if (!CpuSetup->BusSpeedEnable) {
    return EFI_SUCCESS;
  }

  MDividerValue                   = MDIVIDER_VALUE_13;

  CpuFrequencyMode                = CPU_FREQUENCY_MODE_100;
  FrequencyResolution             = FREQUENCY_RESOLUTION_3182;

  ClockAddress                    = CLOCK_CONTROLLER_SMBUS_ADDRESS;
  TargetFrequency                 = CpuFrequencyMode + (UINT16) (CpuSetup->ProcessorBusSpeedOverride * CpuFrequencyMode) / 100;
  NDividerValue                   = (10000 * (TargetFrequency - CpuFrequencyMode) / FrequencyResolution) + NDIVIDER_BASE_VALUE;
  Reg15 = (UINT8) (MDividerValue & 0x3F) | (UINT8) LShiftU64(NDividerValue, 6);
  Reg16 = (UINT8) RShiftU64(NDividerValue, 2);

  Data = Reg15;
  SlaveAddress.SmbusDeviceAddress = (UINTN)RShiftU64(ClockAddress, 1);
  Length = 1;
  Command = 0x8f;

  Status = SmbusPpi->Execute (
                      SmbusPpi,
                      SlaveAddress,
                      Command,
                      EfiSmbusWriteByte,
                      FALSE,
                      &Length,
                      &Data
                      );
  ASSERT_EFI_ERROR (Status);

  Data  = Reg16;
  SlaveAddress.SmbusDeviceAddress = (UINTN)RShiftU64(ClockAddress, 1);
  Length                          = 1;
  Command                         = 0x90;

  Status = SmbusPpi->Execute (
                      SmbusPpi,
                      SlaveAddress,
                      Command,
                      EfiSmbusWriteByte,
                      FALSE,
                      &Length,
                      &Data
                      );
  ASSERT_EFI_ERROR (Status);

  Data  = 0x80;
  SlaveAddress.SmbusDeviceAddress = (UINTN)RShiftU64(ClockAddress, 1);
  Length                          = 1;
  Command                         = 0x91;

  Status = SmbusPpi->Execute (
                      SmbusPpi,
                      SlaveAddress,
                      Command,
                      EfiSmbusWriteByte,
                      FALSE,
                      &Length,
                      &Data
                      );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Disables Bus Speed override.

  @param[in] SmBusPpi         Pointer to the EFI_PEI_SMBUS2_PPI

  @retval EFI_SUCCESS         Function successfully executed.

  @todo need to check if this fn needed
**/
EFI_STATUS
DisableBusSpeedOverride (
  IN  EFI_PEI_SMBUS2_PPI       *SmbusPpi
  )
{
  EFI_STATUS                Status;
  EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress;
  UINTN                     Length;
  UINT8                     Data;
  EFI_SMBUS_DEVICE_COMMAND  Command;
  UINT8                     ClockAddress;

  ClockAddress                    = CLOCK_CONTROLLER_SMBUS_ADDRESS;

  SlaveAddress.SmbusDeviceAddress = (UINTN)RShiftU64(ClockAddress, 1);
  Length                          = 1;
  Command                         = 0x91;

  Status = SmbusPpi->Execute (
                      SmbusPpi,
                      SlaveAddress,
                      Command,
                      EfiSmbusReadByte,
                      FALSE,
                      &Length,
                      &Data
                      );
  ASSERT_EFI_ERROR (Status);

  //
  // Disable CPU Speed override if it is enabled
  //
  if (Data & 0x80) {
    Data = Data & 0x7F;

    Status = SmbusPpi->Execute (
                        SmbusPpi,
                        SlaveAddress,
                        Command,
                        EfiSmbusWriteByte,
                        FALSE,
                        &Length,
                        &Data
                        );
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Programs Processor Multiplier using FLEX_RATIO MSR(0x194).
  This ProgramProcessorMultiplier Override needs a CPU Only Reset.
  Flex Override in Flex Ratio MSR assuming the OverclockPei Driver will
  always get called before Memroy.

  @param[in] CpuSetup        Pointer to the CPU_SETUP buffer
**/
VOID
ProgramProcessorMultiplier (
  IN  CPU_SETUP              *CpuSetup
  )
{
  UINT64  ClockFlexMax;
  UINT8   SetFlex;

  if (!CpuSetup->CpuRatioOverride) {
    return ;
  }

  ClockFlexMax = AsmReadMsr64 (MSR_FLEX_RATIO);
  ClockFlexMax &= ~((UINT64)(FLEX_RATIO) | (UINT64)(ENABLE_FLEX));
  SetFlex = CpuSetup->CpuRatio;
  ClockFlexMax |= (LShiftU64(SetFlex, 8) | ENABLE_FLEX);
  AsmWriteMsr64 (MSR_FLEX_RATIO, ClockFlexMax);
}

