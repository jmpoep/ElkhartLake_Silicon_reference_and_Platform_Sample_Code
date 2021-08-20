/** @file
  Implements Overclocking Interface for OS Application ie Iron city

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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

#include <OverclockInterface.h>
#include "OverClockSmiHandler.h"
#include <IccSetupData.h>

#define OVERCLOCKING_BINS                   (0x7 << 17)
#define MAX_RATIO_LIMIT_8C_OFFSET           56
#define MAX_RATIO_LIMIT_7C_OFFSET           48
#define MAX_RATIO_LIMIT_6C_OFFSET           40
#define MAX_RATIO_LIMIT_5C_OFFSET           32
#define MAX_RATIO_LIMIT_4C_OFFSET           24
#define MAX_RATIO_LIMIT_3C_OFFSET           16
#define MAX_RATIO_LIMIT_2C_OFFSET           8
#define MAX_RATIO_LIMIT_1C_OFFSET           0
#define MAX_RATIO_LIMIT_1C_MASK             0x00000000000000ff
#define MAX_RATIO_LIMIT_2C_MASK             0x000000000000ff00
#define MAX_RATIO_LIMIT_3C_MASK             0x0000000000ff0000
#define MAX_RATIO_LIMIT_4C_MASK             0x00000000ff000000
#define MAX_RATIO_LIMIT_5C_MASK             0x000000ff00000000
#define MAX_RATIO_LIMIT_6C_MASK             0x0000ff0000000000
#define MAX_RATIO_LIMIT_7C_MASK             0x00ff000000000000
#define MAX_RATIO_LIMIT_8C_MASK             0xff00000000000000
#define HZ_TO_10KHZ                         10000

#include <Protocol/AcpiTable.h>
#include <Protocol/Wdt.h>
#include <Protocol/IccOverClocking.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/MemInfo.h>
#include <Protocol/PlatformNvsArea.h>
#include <CpuAccess.h>
#include <CoreBiosMsg.h>
#include <Library/DxeMeLib.h>

#define PACKAGE_MAX_POWER_OFFSET            32
#define PACKAGE_MIN_POWER_OFFSET            16

GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_TABLE_PROTOCOL   *AcpiTable;
GLOBAL_REMOVE_IF_UNREFERENCED WDT_PROTOCOL              *gWdtDxe;
//
// For XTU 3.0
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA_PROTOCOL  *mPlatformNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA           *mPlatformNvsAreaPtr;
GLOBAL_REMOVE_IF_UNREFERENCED SA_SETUP                  mSaSetup;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_SETUP                 mCpuSetup;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA                mSetupData;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                     VariableSize;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_CPU_FEATURES        SetupCpuFeatures;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                     gDataSize;

GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gMaxTurboPowerLimit       = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gMinTurboPowerLimit       = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gPackageTdpLimit          = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                     gPowerUnit                = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gCoreCount                = 0;

GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gBclkMaxValue             = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    gBclkMinValue             = 0;

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                     gIsRatioLimitProgrammable = 0;

//
// Make sure these 2 tables are in sync with the table defined in OverclockPei.c
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8               MemoryVoltageTableMobile[8][3] = {
  //
  // Index      Value       Volts
  //
     {0x00,     0x3,        150},
     {0x01,     0x2,        155},
     {0x02,     0x1,        160},
     {0x03,     0x0,        165},
     {0x00,     0x3,        150},
     {0x01,     0x2,        155},
     {0x02,     0x1,        160},
     {0x03,     0x0,        165}
};
//
// Desktop EV / CRB
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT16              MemoryVoltageTableDesktop[11][3] = {
  //
  // Index      Value    Volts
  //
    {0x00,      0x00,    0000},
    {0x01,      0x01,    1200},
    {0x02,      0x02,    1250},
    {0x03,      0x03,    1300},
    {0x04,      0x04,    1350},
    {0x05,      0x05,    1400},
    {0x06,      0x06,    1450},
    {0x07,      0x07,    1500},
    {0x08,      0x08,    1550},
    {0x09,      0x09,    1600},
    {0x0A,      0x0A,    1650}
};

/**
  This function fills CONTROLID_DATA

  @param[in] ControlIDData       Pointer to CONTROLID_DATA
  @param[in] ControlId           Control ID
  @param[in] NumberOfValues      Number of Values
  @param[in] Precision           Precision identifier
  @param[in] Flags               Flags
  @param[in] DefaultDataValue    Default data value
  @param[in] MinDataValue        Minimum data value
  @param[in] MaxDataValue        Maximum data value
  @param[in] MinDisplayValue     Minimum display value
  @param[in] MaxDisplayValue     Maximum display value
  @param[in] Count               Value of count

  @retval EFI_SUCCESS            This function completed successfully.
**/
EFI_STATUS
AddControlBuffData (
  IN  CONTROLID_DATA  *ControlIDData,
  IN  UINT32          ControlId,
  IN  UINT16          NumberOfValues,
  IN  UINT8           Precision,
  IN  UINT8           Flags,
  IN  UINT32          DefaultDataValue,
  IN  UINT32          MinDataValue,
  IN  UINT32          MaxDataValue,
  IN  UINT32          MinDisplayValue,
  IN  UINT32          MaxDisplayValue,
  IN  UINT8           *Count
  )
{
  ControlIDData->ControlId          = ControlId;
  ControlIDData->NumberOfValues     = NumberOfValues;
  ControlIDData->Precision          = Precision;
  ControlIDData->Flags              = Flags;
  ControlIDData->DefaultDataValue   = DefaultDataValue;
  ControlIDData->MinDataValue       = MinDataValue;
  ControlIDData->MaxDataValue       = MaxDataValue;
  ControlIDData->MinDisplayValue    = MinDisplayValue;
  ControlIDData->MaxDisplayValue    = MaxDisplayValue;
  (*Count)++;

  return EFI_SUCCESS;
}

/**
  OverClocking Interface callback gets executed on ReadyToBoot Event

  @param[in] Event              Pointer to the event that triggered this Callback Function
  @param[in] Context            VOID Pointer required for Callback function

  @retval EFI_OUT_OF_RESOURCES  The function fails due to Out of Resources.
  @retval EFI_SUCCESS           The function completed successfully.
**/
VOID
EFIAPI
RegisterProtocolOverClockingInterface (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
#if FixedPcdGetBool(PcdAcpiEnable) == 1
  EFI_STATUS            Status;
  static BOOLEAN        Configure = TRUE;
  UINT64                MsrPackagePowerSku;
  UINT64                MsrPackagePowerSkuUnit;
  UINT32                Data32;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP BclkSettings;

  Status = gBS->LocateProtocol (&gPlatformNvsAreaProtocolGuid, NULL, (VOID **) &mPlatformNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "RegisterProtocolOverClockingInterface entry\n"));

  mPlatformNvsAreaPtr = mPlatformNvsAreaProtocol->Area;
  VariableSize  = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mSetupData
                  );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "Register mCpuSetup.OverclockingSupport = %X.\n", mCpuSetup.OverclockingSupport));

  //
  // Move the code from driver's entrypoint to the callback function to remove
  //  the inter-dependency of SetupVariable initialization in PlatformSetup driver
  //
  if ((mCpuSetup.OverclockingSupport == 0) || (mCpuSetup.XtuInterfaceEnable == 0)) {
    return;
  }
  if (Configure) {
    //
    // No need to stop WDT, WDT driver should disable it.
    //
    gDataSize = sizeof (SETUP_CPU_FEATURES);

    Status = gRT->GetVariable (
                    L"SetupCpuFeatures",
                    &gSetupVariableGuid,
                    NULL,
                    &gDataSize,
                    &SetupCpuFeatures
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // Read MSR for Active Core and Thread Count.
    //
    Data32      = (UINT32) AsmReadMsr64 (MSR_CORE_THREAD_COUNT);
    gCoreCount  = (UINT16) (RShiftU64 (Data32, 16) & 0xFFFF);

    //
    // Read Max and Min Turbo Power Limit values
    //
    MsrPackagePowerSku      = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU);
    gMaxTurboPowerLimit     = (UINT16) RShiftU64 ((MsrPackagePowerSku & PACKAGE_MAX_POWER_MASK), PACKAGE_MAX_POWER_OFFSET);
    gMinTurboPowerLimit     = (UINT16) RShiftU64 ((MsrPackagePowerSku & PACKAGE_MIN_POWER_MASK), PACKAGE_MIN_POWER_OFFSET);
    gPackageTdpLimit        = (UINT16) (MsrPackagePowerSku & PACKAGE_TDP_POWER_MASK);

    MsrPackagePowerSkuUnit  = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);
    gPowerUnit               = (UINT8) (MsrPackagePowerSkuUnit & PACKAGE_POWER_UNIT_MASK);
    if (gPowerUnit == 0) {
      gPowerUnit = 1;
    } else {
      gPowerUnit = (UINT8) LShiftU64 (2, (gPowerUnit - 1));
    }

    gMaxTurboPowerLimit = gMaxTurboPowerLimit / gPowerUnit;
    gMinTurboPowerLimit = gMinTurboPowerLimit / gPowerUnit;
    gPackageTdpLimit    = gPackageTdpLimit / gPowerUnit;

    if ((SetupCpuFeatures.CoreRatioLimitAvailable == 1) && (gMaxTurboPowerLimit == 0)) {
      gMaxTurboPowerLimit = (UINT16) (0x7FFF / gPowerUnit);
    }

    gIsRatioLimitProgrammable = SetupCpuFeatures.CoreRatioLimitAvailable;

    //
    // Read BCLK Max and Min Frequencies
    //
    //
    // Convert ClockRanges (unit of [1Hz]) to Bclk Value (unit of [10kHz] but rounded to 100kHz)
    //
    BclkSettings.ReqClock = 1;
    Status = HeciGetIccClockSettings(&BclkSettings);
    if (EFI_ERROR(Status)) {
      DEBUG ((DEBUG_INFO, "OverClockInterface: Get BClk Settings messge failed. Status = %X\n", Status));
    }
    gBclkMinValue = (UINT16) ( (BclkSettings.MinFreq + (HZ_TO_10KHZ/2)) / HZ_TO_10KHZ);
    gBclkMaxValue = (UINT16) ( (BclkSettings.MaxFreq + (HZ_TO_10KHZ/2)) / HZ_TO_10KHZ);

//    gBclkMinValue = 100;//10 * (UINT16) (Clock2Settings.MinFreq / 100000);
//    gBclkMaxValue = 10000;//10 * (UINT16) (Clock2Settings.MaxFreq / 100000);
    DEBUG ((DEBUG_INFO, "OverClockInterface: BclkSettings.MinFreq = %d\n", BclkSettings.MinFreq));
    DEBUG ((DEBUG_INFO, "OverClockInterface: BclkSettings.MaxFreq = %d\n", BclkSettings.MaxFreq));

    DEBUG ((DEBUG_INFO, "OverClockInterface: gBclkMinValue = %d kHz\n", gBclkMinValue));
    DEBUG ((DEBUG_INFO, "OverClockInterface: gBclkMaxValue = %d kHz\n", gBclkMaxValue));

    Status    = CreateControlIDs ();

    Configure = FALSE;
  }
#endif
}

/**
  This function is the entry point for this DXE driver. It implements
  necessary interace (ASPT) for the OS Application (Iron City) to work.
  It creates ASPT table and publishes it.

  @param[in] ImageHandle       Image handle of this driver.
  @param[in] SystemTable       Global system service table.

  @retval EFI_DEVICE_ERROR     Initialization fails
  @retval EFI_SUCCESS          Initialization completes successfully.

**/
EFI_STATUS
EFIAPI
OverclockingInterfaceEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                Status2;
  EFI_STATUS                Status3;
  EFI_EVENT                 BootEvent;

  DEBUG ((DEBUG_INFO, "Overclockinterface entrypoint.\n"));

  gST = SystemTable;
  ASSERT (gST != NULL);
  if (gST == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  gBS = SystemTable->BootServices;
  gRT = SystemTable->RuntimeServices;
  DEBUG ((DEBUG_INFO, "Overclock gRT = %X.\n", gRT));

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mSetupData
                  );

  VariableSize = sizeof (SA_SETUP);
  Status2 = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mSaSetup
                  );

  VariableSize = sizeof (CPU_SETUP);
  Status3 = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mCpuSetup
                  );

  if (EFI_ERROR (Status) || EFI_ERROR (Status2) || EFI_ERROR (Status3)) {
    //
    // If GetVariable fails, return EFI_SUCCESS assuming OC is Disabled.
    //
    DEBUG ((DEBUG_ERROR, "GetVariable failed, status = %r.\n", Status));
    return EFI_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "mCpuSetup.OverclockingSupport = %X.\n", mCpuSetup.OverclockingSupport));

  if ((mCpuSetup.OverclockingSupport == 0) || (mCpuSetup.XtuInterfaceEnable == 0)) {
    return EFI_SUCCESS;
  }

  Status = gBS->LocateProtocol (
                  &gWdtProtocolGuid,
                  NULL,
                  (VOID **) &gWdtDxe
                  );
  ASSERT_EFI_ERROR (Status);

  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             RegisterProtocolOverClockingInterface,
             NULL,
             &BootEvent
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Allocate MemoryType below 4G memory address.

  @param[in] Size           Size of memory to allocate.
  @param[in] Buffer         Allocated address for output.

  @retval EFI_SUCCESS       Memory successfully allocated.
  @retval Other             Other errors occur.
**/
EFI_STATUS
AllocateMemoryBelow4G (
  IN   EFI_MEMORY_TYPE MemoryType,
  IN   UINTN           Size,
  OUT  VOID           **Buffer
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;

  Pages = EFI_SIZE_TO_PAGES (Size);
  Address = 0xffffffff;

  Status  = (gBS->AllocatePages) (
                   AllocateMaxAddress,
                   MemoryType,
                   Pages,
                   &Address
                   );

  *Buffer = (VOID *) (UINTN) Address;

  return Status;
};

/**
  Create control ids table in ACPI NVS memory.

**/
EFI_STATUS
CreateControlIDs (
  VOID
  )
{
  EFI_STATUS              Status;
  MEM_INFO_PROTOCOL       *MemInfoHobProtocol;
  UINT8                   NoOfVoltages;
  MSR_REGISTER            FlexRatioMsr;
  UINT8                   OverclockingBins;
  UINT8                   OneCoreRatioLimitMax;
  UINT8                   TwoCoreRatioLimitMax;
  UINT8                   ThreeCoreRatioLimitMax;
  UINT8                   FourCoreRatioLimitMax;
  UINT8                   FiveCoreRatioLimitMax;
  UINT8                   SixCoreRatioLimitMax;
  UINT8                   SevenCoreRatioLimitMax;
  UINT8                   EightCoreRatioLimitMax;
  SETUP_VOLATILE_DATA     SetupVolatileData;
  UINTN                   DataSize;
  CONTROLID_BUFF          *ControlBuff;
  XMP_BUFF                *XmpBuff;
  UINT8                   Count;
  MEMORY_TIMING           *MemoryTiming = NULL;
  UINT8                   Profile;
  UINT8                   ControlID;

  OneCoreRatioLimitMax      = CORE1_RATIO_MAXIMUM;
  TwoCoreRatioLimitMax      = CORE2_RATIO_MAXIMUM;
  ThreeCoreRatioLimitMax    = CORE3_RATIO_MAXIMUM;
  FourCoreRatioLimitMax     = CORE4_RATIO_MAXIMUM;
  FiveCoreRatioLimitMax     = CORE5_RATIO_MAXIMUM;
  SixCoreRatioLimitMax      = CORE6_RATIO_MAXIMUM;
  SevenCoreRatioLimitMax    = CORE7_RATIO_MAXIMUM;
  EightCoreRatioLimitMax    = CORE8_RATIO_MAXIMUM;
  Count                     = 0;

  DataSize                  = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  NULL,
                  &DataSize,
                  &SetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "OverClockInterface: CreateControlID\n"));

  //
  // Get the Memory Info HOB Protocol if it exists.
  //
  Status = gBS->LocateProtocol (&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoHobProtocol);
  ASSERT_EFI_ERROR (Status);

  //
  // Manufacturing Mode supported only on mobile boards
  //
  if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
    NoOfVoltages  = sizeof (MemoryVoltageTableMobile) / sizeof (MemoryVoltageTableMobile[0]);
  } else {
    NoOfVoltages  = sizeof (MemoryVoltageTableDesktop) / sizeof (MemoryVoltageTableDesktop[0]);
  }
  //
  // Allocate memory in ACPI NVS
  //
  Status = AllocateMemoryBelow4G (EfiACPIMemoryNVS, sizeof(CONTROLID_BUFF), (VOID **) &ControlBuff);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return 0;
  }
  SetMem (ControlBuff, sizeof (CONTROLID_BUFF), 0xFE);
  mPlatformNvsAreaPtr->XTUBaseAddress = (UINT32) (UINTN) ControlBuff;
  mPlatformNvsAreaPtr->DDRReferenceFreq = mSaSetup.DdrRefClk;
  DEBUG ((DEBUG_INFO, "OverClockInterface: mPlatformNvsAreaPtr->XTUBaseAddress = 0x%X\n", mPlatformNvsAreaPtr->XTUBaseAddress));

  Status = AllocateMemoryBelow4G (EfiACPIMemoryNVS, sizeof(XMP_BUFF), (VOID **) &XmpBuff);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return 0;
  }
  SetMem (XmpBuff, sizeof (XMP_BUFF), 0);
  mPlatformNvsAreaPtr->XMPBaseAddress = (UINT32) (UINTN) XmpBuff;
  DEBUG ((DEBUG_INFO, "OverClockInterface: mPlatformNvsAreaPtr->XTUBaseAddress = 0x%X\n", mPlatformNvsAreaPtr->XMPBaseAddress));

  //
  // Processor Multiplier (Flex Ratio)
  //
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_FLEX_RATIO,
                      (( mCpuSetup.FlexRatioOverrideDefault - mCpuSetup.MaxEfficiencyRatio ) + 1),
                      0x00,
                      0x00,
                      mCpuSetup.FlexRatioOverrideDefault,
                      mCpuSetup.MaxEfficiencyRatio,
                      mCpuSetup.FlexRatioOverrideDefault,
                      mCpuSetup.MaxEfficiencyRatio,
                      mCpuSetup.FlexRatioOverrideDefault,
                      &Count );

  //
  // Host Clock Frequency
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_HOST_CLK_FREQ,
                      (((gBclkMaxValue - gBclkMinValue) / 10) + 1),
                      0x02,
                      0x00,
                      10000,
                      gBclkMinValue,
                      gBclkMaxValue,
                      gBclkMinValue,
                      gBclkMaxValue,
                      &Count );

  //
  // Core Voltage Mode
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IA_CORE_VOLTAGE_MODE,
                      0x2,
                      PRECISION_NONE,
                      ZERO,
                      mCpuSetup.CoreVoltageModeDefault,
                      0,
                      1,
                      0,
                      1,
                      &Count );

  if(mCpuSetup.CoreVoltageModeDefault == VOLTAGE_MODE_ADAPTIVE) {
    //
    // Core Voltage Override
    //
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_CPU_VOLTAGE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mCpuSetup.CoreExtraTurboVoltageDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );

  } else {
    //
    // Core Voltage Override
    //
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_CPU_VOLTAGE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mCpuSetup.CoreVoltageOverrideDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );

  }

  //
  // Core Voltage Offset
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IA_CORE_VOLTAGE_OFFSET,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL + 1,
                      PRECISION_NONE,
                      ZERO,
                      IVR_VOLTAGE_OFFSET_DEFAULT_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DISP_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DISP_VAL,
                      &Count );

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
    //
    // Update "Volts" field for ChiefRiver board for DDR3L
    //

    //
    //  Memory Voltage Continous
    //
    //
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_MEMORY_VOLTAGE,
                        ((MemoryVoltageTableMobile[NoOfVoltages - 1][2] - MemoryVoltageTableMobile[0][2]) / MEMORY_VOLTAGE_VALUE_STEP_SIZE ) + 1,
                        PRECISION_TWO,
                        ZERO,
                        mSaSetup.MemoryVoltageDefault,
                        MemoryVoltageTableMobile[0][0],
                        MemoryVoltageTableMobile[NoOfVoltages - 1][0],
                        MemoryVoltageTableMobile[0][2],
                        MemoryVoltageTableMobile[NoOfVoltages - 1][2],
                        &Count );


  } else {
    //
    // Memory Voltage Discrete
    //
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_MEMORY_VOLTAGE,
                        0xFFFF,
                        PRECISION_THREE,
                        ZERO,
                        mSaSetup.MemoryVoltageDefault,
                        0xFFFF,
                        0xFFFF,
                        0xFFFF,
                        0xFFFF,
                        &Count );
  }
  //
  // tCL
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tCL,
                      (((tCL_MAXIMUM - tCL_MINIMUM) / tCL_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tCLDefault,
                      tCL_MINIMUM,
                      tCL_MAXIMUM,
                      tCL_MINIMUM,
                      tCL_MAXIMUM,
                      &Count );
  //
  // tRCD/tRP
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tRCD_tRP,
                      (((tRCD_tRP_MAXIMUM - tRCD_tRP_MINIMUM) / tRCD_tRP_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tRCDtRPDefault,
                      tRCD_tRP_MINIMUM,
                      tRCD_tRP_MAXIMUM,
                      tRCD_tRP_MINIMUM,
                      tRCD_tRP_MAXIMUM,
                      &Count );
  //
  // tRAS
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tRAS,
                      (((tRAS_MAXIMUM - tRAS_MINIMUM) / tRAS_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tRASDefault,
                      tRAS_MINIMUM,
                      tRAS_MAXIMUM,
                      tRAS_MINIMUM,
                      tRAS_MAXIMUM,
                      &Count );
  //
  // tWR
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tWR,
                      0xFFFF,
                      PRECISION_NONE,
                      2,
                      mSaSetup.tWRDefault,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      &Count );
  //
  // tRFC
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tRFC,
                      (((tRFC_MAXIMUM - tRFC_MINIMUM) / tRFC_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tRFCDefault,
                      tRFC_MINIMUM,
                      tRFC_MAXIMUM,
                      tRFC_MINIMUM,
                      tRFC_MAXIMUM,
                      &Count );
  //
  // tRRD
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tRRD,
                      (((tRRD_MAXIMUM - tRRD_MINIMUM) / tRRD_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tRRDDefault,
                      tRRD_MINIMUM,
                      tRRD_MAXIMUM,
                      tRRD_MINIMUM,
                      tRRD_MAXIMUM,
                      &Count );
  //
  // tWTR
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tWTR,
                      (((tWTR_MAXIMUM - tWTR_MINIMUM) / tWTR_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tWTRDefault,
                      tWTR_MINIMUM,
                      tWTR_MAXIMUM,
                      tWTR_MINIMUM,
                      tWTR_MAXIMUM,
                      &Count );
  //
  // CMD Rate
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_SYSTEM_CMD_RATE,
                      ((SYSTEM_CMD_RATE_MAXIMUM - SYSTEM_CMD_RATE_MINIMUM) / SYSTEM_CMD_RATE_STEP_SIZE) + 1,
                      PRECISION_NONE,
                      2,
                      mSaSetup.NModeDefault,
                      SYSTEM_CMD_RATE_MINIMUM,
                      SYSTEM_CMD_RATE_MAXIMUM,
                      SYSTEM_CMD_RATE_MINIMUM,
                      SYSTEM_CMD_RATE_MAXIMUM,
                      &Count );
  //
  // tRTP
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tRTP,
                      (((tRTP_MAXIMUM - tRTP_MINIMUM) / tRTP_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tRTPDefault,
                      tRTP_MINIMUM,
                      tRTP_MAXIMUM,
                      tRTP_MINIMUM,
                      tRTP_MAXIMUM,
                      &Count );
  //
  // tFAW (Min Four Activate Window Delay Time (tFAWmin)
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_tFAW,
                      (((tFAW_MAXIMUM - tFAW_MINIMUM) / tFAW_STEP_SIZE) + 1),
                      PRECISION_NONE,
                      MIN_SETTING_LOW_PERFORMANCE,
                      mSaSetup.tFAWDefault,
                      tFAW_MINIMUM,
                      tFAW_MAXIMUM,
                      tFAW_MINIMUM,
                      tFAW_MAXIMUM,
                      &Count );

  //
  // Memory Clock Multiplier
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_MEMORY_CLOCK_FREQUENCY,
                      0xFFFF,
                      0x02,
                      MIN_SETTING_LOW_PERFORMANCE,
                      0x01,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      &Count );

  //
  // Turbo Power Limit MSR Lock Enable/Disable
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_TURBO_POWER_LIMIT_LOCK,
                      2,
                      PRECISION_NONE,
                      ZERO,
                      0,
                      0,
                      1,
                      0,
                      1,
                      &Count );

  //
  // GT_CPU_Turbo_UnLock
  //
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_OC_ENABLE,
                      0x02,
                      PRECISION_NONE,
                      ZERO,
                      0x0,
                      0,
                      1,
                      0,
                      1,
                      &Count );


  //
  // EIST
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_EIST,
                      0x2,
                      PRECISION_NONE,
                      ZERO,
                      mCpuSetup.EnableGvDefault,
                      0,
                      1,
                      0,
                      1,
                      &Count );

//@todo: Add PrimaryPlaneCurrentLimit support
//@todo: Add SecondaryPlaneCurrentLimit support
  //
  // Internal Graphics Freq Limit
  //
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_FREQUENCY,
                      (((IGD_FREQ_RATIO_LIMIT_MAXIMUM - IGD_FREQ_RATIO_LIMIT_MINIMUM) / IGD_FREQ_RATIO_LIMIT_STEP_SIZE) + 1),
                      PRECISION_ONE,
                      ZERO,
                      mSaSetup.GtMaxOcRatioDefault,
                      IGD_FREQ_RATIO_LIMIT_MINIMUM,
                      IGD_FREQ_RATIO_LIMIT_MAXIMUM,
                      IGD_FREQ_RATIO_LIMIT_MINIMUM,
                      IGD_FREQ_RATIO_DISPLAY_MAX,
                      &Count );

  //
  // Turbo Mode
  //
  if (SetupCpuFeatures.TurboModeAvailable) {
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_TURBO_MODE,
                        0x02,
                        PRECISION_NONE,
                        ZERO,
                        0x01,
                        0,
                        1,
                        0,
                        1,
                        &Count );

    if (((AsmReadMsr64(MSR_PLATFORM_INFO)) & BIT29) == BIT29) {

      if (SetupCpuFeatures.XETdcTdpLimitAvailable) {
        //
        // Extended Window Package TDP Limit
        //
        if (gIsRatioLimitProgrammable) {
          AddControlBuffData(&ControlBuff->ControlIDData[Count],
                              BIOS_DEVICE_EXTENDED_TDP_LIMIT,
                              ((gMaxTurboPowerLimit - gMinTurboPowerLimit) / STEP_SIZE_1) + 1,
                              PRECISION_THREE,
                              MIN_SETTING_LOW_PERFORMANCE,
                              mCpuSetup.PowerLimit1Default * 1000,
                              gMinTurboPowerLimit * 1000,
                              gMaxTurboPowerLimit * 1000,
                              gMinTurboPowerLimit * 1000,
                              gMaxTurboPowerLimit * 1000,
                              &Count );
        } else {
          AddControlBuffData(&ControlBuff->ControlIDData[Count],
                              BIOS_DEVICE_EXTENDED_TDP_LIMIT,
                              ((gPackageTdpLimit - gMinTurboPowerLimit) / STEP_SIZE_1) + 1,
                              PRECISION_THREE,
                              MIN_SETTING_LOW_PERFORMANCE,
                              mCpuSetup.PowerLimit1Default * 1000,
                              gMinTurboPowerLimit * 1000,
                              gPackageTdpLimit * 1000,
                              gMinTurboPowerLimit * 1000,
                              gPackageTdpLimit * 1000,
                              &Count );
        }

        //
        // Short Window Package Power Limit Enable/Disable
        //
        AddControlBuffData(&ControlBuff->ControlIDData[Count],
                            BIOS_DEVICE_SHORT_WINDOW_POWER_ENABLE,
                            2,
                            PRECISION_NONE,
                            ZERO,
                            mCpuSetup.PowerLimit2,
                            0,
                            1,
                            0,
                            1,
                            &Count );

        //
        // Short Window Package TDP Limit
        // gMaxTurboPowerLimit;
        //
        AddControlBuffData(&ControlBuff->ControlIDData[Count],
                            BIOS_DEVICE_SHORT_WINDOW_TDP_LIMIT,
                            ((((0x7FFF/gPowerUnit) - gMinTurboPowerLimit) / STEP_SIZE_1) + 1),
                            PRECISION_THREE,
                            MIN_SETTING_LOW_PERFORMANCE,
                            mCpuSetup.PowerLimit2Default * 1000,
                            gMinTurboPowerLimit * 1000,
                            (0x7fff/gPowerUnit) * 1000,
                            gMinTurboPowerLimit * 1000,
                            (0x7fff/gPowerUnit) * 1000,
                            &Count );


      }
    }

    if (SetupCpuFeatures.CoreRatioLimitAvailable) {
      //
      // If Lock-Limited CPU, set the maximum
      //
      if (((AsmReadMsr64 (MSR_PLATFORM_INFO)) & BIT28) == BIT28) {

        FlexRatioMsr.Qword    = AsmReadMsr64 (MSR_FLEX_RATIO);
        OverclockingBins      = (UINT8) RShiftU64 ((FlexRatioMsr.Dwords.Low & OVERCLOCKING_BINS), 17);
        if ( (OverclockingBins > 0) && (OverclockingBins < MAX_OVERCLOCKING_BINS)) {
          OneCoreRatioLimitMax  = OverclockingBins + mCpuSetup.RatioLimit1Default;
          TwoCoreRatioLimitMax  = OverclockingBins + mCpuSetup.RatioLimit2Default;
          if (gCoreCount > 2) {
            ThreeCoreRatioLimitMax  = OverclockingBins + mCpuSetup.RatioLimit3Default;
            FourCoreRatioLimitMax   = OverclockingBins + mCpuSetup.RatioLimit4Default;
            FiveCoreRatioLimitMax   = OverclockingBins + mCpuSetup.RatioLimit5Default;
            SixCoreRatioLimitMax    = OverclockingBins + mCpuSetup.RatioLimit6Default;
            SevenCoreRatioLimitMax  = OverclockingBins + mCpuSetup.RatioLimit7Default;
            EightCoreRatioLimitMax  = OverclockingBins + mCpuSetup.RatioLimit8Default;
          }
        }
        //
        // 1 Core Ratio Limit
        //
        AddControlBuffData(&ControlBuff->ControlIDData[Count],
                            BIOS_DEVICE_1_CORE_RATIO_LIMIT,
                            ((OneCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE1_RATIO_STEP_SIZE) + 1,
                            PRECISION_NONE,
                            MIN_SETTING_LOW_PERFORMANCE,
                            mCpuSetup.RatioLimit1Default,
                            mCpuSetup.CpuRatio,
                            OneCoreRatioLimitMax,
                            mCpuSetup.CpuRatio,
                            OneCoreRatioLimitMax,
                            &Count );

        //
        // 2 Core Ratio Limit
        //
        AddControlBuffData(&ControlBuff->ControlIDData[Count],
                            BIOS_DEVICE_2_CORE_RATIO_LIMIT,
                            ((TwoCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE2_RATIO_STEP_SIZE) + 1,
                            PRECISION_NONE,
                            MIN_SETTING_LOW_PERFORMANCE,
                            mCpuSetup.RatioLimit2Default,
                            mCpuSetup.CpuRatio,
                            TwoCoreRatioLimitMax,
                            mCpuSetup.CpuRatio,
                            TwoCoreRatioLimitMax,
                            &Count );



        if (gCoreCount > 2) {
          //
          // 3 Core Ratio Limit
          //
          AddControlBuffData(&ControlBuff->ControlIDData[Count],
                              BIOS_DEVICE_3_CORE_RATIO_LIMIT,
                              ((ThreeCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE3_RATIO_STEP_SIZE) + 1,
                              PRECISION_NONE,
                              MIN_SETTING_LOW_PERFORMANCE,
                              mCpuSetup.RatioLimit3Default,
                              mCpuSetup.CpuRatio,
                              ThreeCoreRatioLimitMax,
                              mCpuSetup.CpuRatio,
                              ThreeCoreRatioLimitMax,
                              &Count );


          //
          //  4 Core Ratio Limit
          //
          AddControlBuffData(&ControlBuff->ControlIDData[Count],
                              BIOS_DEVICE_4_CORE_RATIO_LIMIT,
                              ((FourCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE4_RATIO_STEP_SIZE) + 1,
                              PRECISION_NONE,
                              MIN_SETTING_LOW_PERFORMANCE,
                              mCpuSetup.RatioLimit4Default,
                              mCpuSetup.CpuRatio,
                              FourCoreRatioLimitMax,
                              mCpuSetup.CpuRatio,
                              FourCoreRatioLimitMax,
                              &Count );
          if (gCoreCount > 4) {
            //
            // 5 Core Ratio Limit
            //
            AddControlBuffData(&ControlBuff->ControlIDData[Count],
                                BIOS_DEVICE_5_CORE_RATIO_LIMIT,
                                ((FiveCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE5_RATIO_STEP_SIZE) + 1,
                                PRECISION_NONE,
                                MIN_SETTING_LOW_PERFORMANCE,
                                mCpuSetup.RatioLimit5Default,
                                mCpuSetup.CpuRatio,
                                FiveCoreRatioLimitMax,
                                mCpuSetup.CpuRatio,
                                FiveCoreRatioLimitMax,
                                &Count );


            //
            //  6 Core Ratio Limit
            //
            AddControlBuffData(&ControlBuff->ControlIDData[Count],
                                BIOS_DEVICE_6_CORE_RATIO_LIMIT,
                                ((SixCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE6_RATIO_STEP_SIZE) + 1,
                                PRECISION_NONE,
                                MIN_SETTING_LOW_PERFORMANCE,
                                mCpuSetup.RatioLimit6Default,
                                mCpuSetup.CpuRatio,
                                SixCoreRatioLimitMax,
                                mCpuSetup.CpuRatio,
                                SixCoreRatioLimitMax,
                                &Count );
            if (gCoreCount > 6) {
              //
              // 7 Core Ratio Limit
              //
              AddControlBuffData(&ControlBuff->ControlIDData[Count],
                                  BIOS_DEVICE_7_CORE_RATIO_LIMIT,
                                  ((SevenCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE7_RATIO_STEP_SIZE) + 1,
                                  PRECISION_NONE,
                                  MIN_SETTING_LOW_PERFORMANCE,
                                  mCpuSetup.RatioLimit7Default,
                                  mCpuSetup.CpuRatio,
                                  SevenCoreRatioLimitMax,
                                  mCpuSetup.CpuRatio,
                                  SevenCoreRatioLimitMax,
                                  &Count );


              //
              //  8 Core Ratio Limit
              //
              AddControlBuffData(&ControlBuff->ControlIDData[Count],
                                  BIOS_DEVICE_8_CORE_RATIO_LIMIT,
                                  ((EightCoreRatioLimitMax - mCpuSetup.CpuRatio) / CORE8_RATIO_STEP_SIZE) + 1,
                                  PRECISION_NONE,
                                  MIN_SETTING_LOW_PERFORMANCE,
                                  mCpuSetup.RatioLimit8Default,
                                  mCpuSetup.CpuRatio,
                                  EightCoreRatioLimitMax,
                                  mCpuSetup.CpuRatio,
                                  EightCoreRatioLimitMax,
                                  &Count );
            }
          }
        }
        //
        // end if (gCoreCount > 2)
        //
      }
    }
  }

  //
  // XMP profile selection setting
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_XMP_PROFILE,
                      4,
                      PRECISION_NONE,
                      ZERO,
                      0,
                      0,
                      3,
                      0,
                      3,
                      &Count );
  //
  // XMP Profile data Display
  //
  for (Profile = 0; Profile < 2; Profile++) {

    switch (Profile) {
      case 0:
        MemoryTiming  = &MemInfoHobProtocol->MemInfoData.Timing[1];
        break;

      case 1:
        MemoryTiming  = &MemInfoHobProtocol->MemInfoData.Timing[2];
        break;

      default:
        break;
    }

    for (ControlID = 0; ControlID < 9; ControlID++) {

      XmpBuff->XmpProfile[Profile].Control[ControlID].Reserved     = ZERO;
      XmpBuff->XmpProfile[Profile].Control[ControlID].Precision    = PRECISION_NONE;

      switch (ControlID) {
        case 0:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tCL;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tCL;
          break;

        case 1:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tRCD_tRP;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tRCDtRP;
          break;

        case 2:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tRAS;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tRAS;
          break;

        case 3:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tFAW;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tFAW;
          break;

        case 4:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tRFC;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tRFC;
          break;

        case 5:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tRRD;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tRRD;
          break;

        case 6:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tRTP;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tRTP;
          break;

        case 7:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tWR;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tWR;
          break;

        case 8:
          XmpBuff->XmpProfile[Profile].Control[ControlID].ControlID    = BIOS_DEVICE_tWTR;
          XmpBuff->XmpProfile[Profile].Control[ControlID].DisplayValue = MemoryTiming->tWTR;
          break;

        default:
          break;
      }
    }
  }

  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_DDR_MULTIPLIER,
                      0xFFFF,
                      PRECISION_TWO,
                      ZERO,
                      mSaSetup.DdrFreqLimit,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      0xFFFF,
                      &Count );

  //
  // Ring Ratio
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_RING_RATIO,
                      RING_RATIO_MAXIMUM + 1,
                      PRECISION_NONE,
                      ZERO,
                      mCpuSetup.RingMaxOcRatioDefault,
                      RING_RATIO_MINIMUM,
                      RING_RATIO_MAXIMUM,
                      RING_RATIO_MINIMUM,
                      RING_RATIO_MAXIMUM,
                      &Count );

  //
  // iGfx Voltage Override
  //
  if(mSaSetup.GtVoltageModeDefault == VOLTAGE_MODE_ADAPTIVE) {
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mSaSetup.GtExtraTurboVoltageDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );
  } else {
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mSaSetup.GtVoltageOverrideDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );
  }

  //
  // iGfx Voltage Mode
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_VOLTAGE_MODE,
                      0x2,
                      PRECISION_NONE,
                      ZERO,
                      mSaSetup.GtVoltageModeDefault,
                      0,
                      1,
                      0,
                      1,
                      &Count );

  //
  // iGfx Voltage Offset
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_VOLTAGE_OFFSET,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL + 1,
                      PRECISION_NONE,
                      ZERO,
                      IVR_VOLTAGE_OFFSET_DEFAULT_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DISP_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DISP_VAL,
                      &Count );


  //
  // iGfx UNSLICE Voltage Override
  //
  if(mSaSetup.GtusVoltageModeDefault == VOLTAGE_MODE_ADAPTIVE) {
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mSaSetup.GtusExtraTurboVoltageDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );
  } else {
    AddControlBuffData(&ControlBuff->ControlIDData[Count],
                        BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE,
                        IVR_VOLTAGE_MAXIMUM + 1,
                        PRECISION_THREE,
                        ZERO,
                        mSaSetup.GtusVoltageOverrideDefault,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        IVR_VOLTAGE_MINIMUM,
                        IVR_VOLTAGE_MAXIMUM,
                        &Count );
  }

  //
  // iGfx UNSLICE Voltage Mode
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_MODE,
                      0x2,
                      PRECISION_NONE,
                      ZERO,
                      mSaSetup.GtusVoltageModeDefault,
                      0,
                      1,
                      0,
                      1,
                      &Count );

  //
  // iGfx UNSLICE Voltage Offset
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OFFSET,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL + 1,
                      PRECISION_NONE,
                      ZERO,
                      IVR_VOLTAGE_OFFSET_DEFAULT_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DISP_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DISP_VAL,
                      &Count );

  //
  // iGfx UNSLICE Freq Limit
  //
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_IGFX_UNSLICE_FREQUENCY,
                      (((IGD_FREQ_RATIO_LIMIT_MAXIMUM - IGD_FREQ_RATIO_LIMIT_MINIMUM) / IGD_FREQ_RATIO_LIMIT_STEP_SIZE) + 1),
                      PRECISION_ONE,
                      ZERO,
                      mSaSetup.GtusMaxOcRatioDefault,
                      IGD_FREQ_RATIO_LIMIT_MINIMUM,
                      IGD_FREQ_RATIO_LIMIT_MAXIMUM,
                      IGD_FREQ_RATIO_LIMIT_MINIMUM,
                      IGD_FREQ_RATIO_DISPLAY_MAX,
                      &Count );

  //
  // SA Voltage Offset
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                      BIOS_DEVICE_SA_VOLTAGE_OFFSET,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL + 1,
                      PRECISION_NONE,
                      ZERO,
                      IVR_VOLTAGE_OFFSET_DEFAULT_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DATA_VAL,
                      IVR_VOLTAGE_OFFSET_MIN_DISP_VAL,
                      IVR_VOLTAGE_OFFSET_MAX_DISP_VAL,
                      &Count );

  //
  // VR Settings ( SA = 0, IA = 1, GTUS = 2, GTS = 3, Ring = 4)
  //
  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                    BIOS_DEVICE_SA_CURRENT_LIMIT_MAX,
                    0x2000,
                    PRECISION_TWO,
                    ZERO,
                    mCpuSetup.IccMaxDefault[0],
                    0,
                    8191,
                    0,
                    8191,
                    &Count );

  AddControlBuffData(&ControlBuff->ControlIDData[Count],
                    BIOS_DEVICE_IA_CURRENT_LIMIT_MAX,
                    0x2000,
                    PRECISION_TWO,
                    ZERO,
                    mCpuSetup.IccMaxDefault[1],
                    0,
                    8191,
                    0,
                    8191,
                    &Count );

   AddControlBuffData(&ControlBuff->ControlIDData[Count],
                     BIOS_DEVICE_GTUS_CURRENT_LIMIT_MAX,
                     0x2000,
                     PRECISION_TWO,
                     ZERO,
                     mCpuSetup.IccMaxDefault[2],
                     0,
                     8191,
                     0,
                     8191,
                     &Count );

   AddControlBuffData(&ControlBuff->ControlIDData[Count],
                     BIOS_DEVICE_GTS_CURRENT_LIMIT_MAX,
                     0x2000,
                     PRECISION_TWO,
                     ZERO,
                     mCpuSetup.IccMaxDefault[3],
                     0,
                     8191,
                     0,
                     8191,
                     &Count );

   AddControlBuffData(&ControlBuff->ControlIDData[Count],
                     BIOS_DEVICE_RING_CURRENT_LIMIT_MAX,
                     0x2000,
                     PRECISION_TWO,
                     ZERO,
                     mCpuSetup.IccMaxDefault[4],
                     0,
                     8191,
                     0,
                     8191,
                     &Count );

   AddControlBuffData(&ControlBuff->ControlIDData[Count],
                     BIOS_DEVICE_IA_AVX2_CORE_RATIO_OFFSET,
                     32,
                     PRECISION_NONE,
                     ZERO,
                     mCpuSetup.Avx2RatioOffsetDefault,
                     0,
                     31,
                     0,
                     31,
                     &Count );

   AddControlBuffData(&ControlBuff->ControlIDData[Count],
                     BIOS_DEVICE_IA_AVX3_CORE_RATIO_OFFSET,
                     32,
                     PRECISION_NONE,
                     ZERO,
                     mCpuSetup.Avx3RatioOffsetDefault,
                     0,
                     31,
                     0,
                     31,
                     &Count );

  //Update the XTU entries size to asl code for dynamic buffer allocation
  mPlatformNvsAreaPtr->XTUSize = sizeof(CONTROLID_DATA)*(Count);
  DEBUG ((DEBUG_INFO, "mPlatformNvsAreaPtr->XTUSize = %X Count=%d\n", mPlatformNvsAreaPtr->XTUSize, Count));

  return EFI_SUCCESS;
}

/**
  Create SPTT table in ACPI NVS memory. SPTT table includes
  Device descripion data tables for various devices.

  @retval UINT64 Pointer to SpttTable

**/
UINT64
CreateSpttTable (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT16                          Length;
  UINT8                           Index;
  SPTT                            *Sptt;
  DDDT                            *Dddt;
  DDDT                            *DddtEnd;
  DSD_GPIO_VOLTAGE_DEVICE         *MemoryVoltageDevice;
  DSD_CONTINUOUS_LBS              *ContLogicalBiosSetting;
  DSD_LBS                         *LogicalBiosSetting;
  DSD_HP_LBS                      *HPLogicalBiosSetting;
  LBS_SETTINGS_ENTRY              *SettingsEntry;
  VOLTAGE_DEVICE_SETTING_ENTRY    *MemoryVoltageSettingEntry;
  VOLTAGE_DEVICE_SETTING_ENTRY_2  *MemoryVoltageSettingEntry2;
  UINT8                           NoOfVoltages;
  MSR_REGISTER                    FlexRatioMsr;
  MSR_REGISTER                    TurboRatioLimit;
  UINT8                           OverclockingBins;
  UINT8                           OneCoreRatioLimitMax;
  UINT8                           TwoCoreRatioLimitMax;
  UINT8                           ThreeCoreRatioLimitMax;
  UINT8                           FourCoreRatioLimitMax;
  UINT8                           FiveCoreRatioLimitMax;
  UINT8                           SixCoreRatioLimitMax;
  UINT8                           SevenCoreRatioLimitMax;
  UINT8                           EightCoreRatioLimitMax;

  OneCoreRatioLimitMax        = CORE1_RATIO_MAXIMUM;
  TwoCoreRatioLimitMax        = CORE2_RATIO_MAXIMUM;
  ThreeCoreRatioLimitMax      = CORE3_RATIO_MAXIMUM;
  FourCoreRatioLimitMax       = CORE4_RATIO_MAXIMUM;
  FiveCoreRatioLimitMax       = CORE5_RATIO_MAXIMUM;
  SixCoreRatioLimitMax        = CORE6_RATIO_MAXIMUM;
  SevenCoreRatioLimitMax      = CORE7_RATIO_MAXIMUM;
  EightCoreRatioLimitMax      = CORE8_RATIO_MAXIMUM;
  Length                      = 0;
  MemoryVoltageSettingEntry   = NULL;
  MemoryVoltageSettingEntry2  = NULL;
  //
  // Manufacturing Mode supported only on mobile boards
  //
  if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
    NoOfVoltages  = sizeof (MemoryVoltageTableMobile) / sizeof (MemoryVoltageTableMobile[0]);
    NoOfVoltages  = NoOfVoltages - 4;
    Length        = sizeof (DSD_HP_LBS);
  } else {
    NoOfVoltages  = sizeof (MemoryVoltageTableDesktop) / sizeof (MemoryVoltageTableDesktop[0]);
    Length        = sizeof (DSD_LBS) + sizeof (LBS_SETTINGS_ENTRY) * NoOfVoltages;
  }
  //
  // For EL Fab 2 we use VOLTAGE_DEVICE_SETTING_ENTRY_2
  //
  Length = Length + NoOfVoltages * sizeof (VOLTAGE_DEVICE_SETTING_ENTRY_2);

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorDesktop) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorWorkstation)) {
    Length = Length + NoOfVoltages * sizeof (VOLTAGE_DEVICE_SETTING_ENTRY) - NoOfVoltages *
    sizeof (VOLTAGE_DEVICE_SETTING_ENTRY_2);
  }
  //
  // Calculate the length of SPTT Table
  //
  Length = Length +
    sizeof (SPTT) +
    (sizeof (DDDT) * DDDT_COUNT) +
    sizeof (DSD_LBS) *
    DSD_DISCRETE_LBS_COUNT +
    sizeof (DSD_CONTINUOUS_LBS) *
      DSD_CONTINUOUS_LBS_COUNT +
      sizeof (LBS_SETTINGS_ENTRY) *
      LBS_SETTINGS_ENTRY_COUNT +
      sizeof (DSD_GPIO_VOLTAGE_DEVICE) +
      sizeof (DSD_HP_LBS) *
      DSD_HP_LBS_COUNT;

  if (SetupCpuFeatures.TurboModeAvailable) {
    Length = Length + sizeof (DDDT) + sizeof (DSD_LBS) + sizeof (LBS_SETTINGS_ENTRY) * TURBO_MODE_SETTING_ENTRY_COUNT;
    if (SetupCpuFeatures.XETdcTdpLimitAvailable) {
      Length = Length + sizeof (DDDT) * 4 + sizeof (DSD_CONTINUOUS_LBS) * 2 + 2 * sizeof (DSD_LBS) + 2 *
      sizeof (LBS_SETTINGS_ENTRY) * ENABLE_DISABLE_SETTING_ENTRY_COUNT;
    }

    if (SetupCpuFeatures.CoreRatioLimitAvailable) {
      Length = Length + sizeof (DDDT) * 3 + sizeof (DSD_CONTINUOUS_LBS) * 2 + sizeof (DSD_HP_LBS);
      if (gCoreCount > 2) {
        Length = Length + sizeof (DDDT) * 2 + sizeof (DSD_CONTINUOUS_LBS) * 2;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "Length = %x\n", Length));
  //
  // Allocate memory in ACPI NVS for SPTT table
  //
  Status = AllocateMemoryBelow4G (EfiACPIMemoryNVS, Length, (VOID **) &Sptt);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return 0;
  }

  (gBS->SetMem) (Sptt, Length, 0);

  //
  // Fill SPTT table entries
  //
  Sptt->Signature     = SPTT_SIG;
  Sptt->Length        = Length;
  Sptt->MajorVer      = SPTT_MAJORVER;
  Sptt->MinorVer      = SPTT_MINORVER;
  Sptt->SmiPort       = 0xB2;
  Sptt->SmiCmdValue   = PcdGet8 (PcdOverClockingInterfaceSwSmi);
  Sptt->FeatureFlags  = 0;

  Dddt                = (DDDT *) (Sptt + 1);

  //
  // Memory Voltage device (GPIO based)
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE1, CONTROL_TYPE2, IMPLEMENTATION_TYPE4, VERSION_1);

  MemoryVoltageDevice                       = (DSD_GPIO_VOLTAGE_DEVICE *) (Dddt + 1);
  MemoryVoltageDevice->Signature            = IOVX_SIG;
  MemoryVoltageDevice->IoType               = LEGACY_IO_TYPE;
  MemoryVoltageDevice->UseIndexPort         = FALSE;
  MemoryVoltageDevice->IndexPort            = DONT_CARE_TYPE;
  MemoryVoltageDevice->VoltageSettingCount  = NoOfVoltages;

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
    //
    // Use Memory Voltage Setting Entry table with 2 Voltage Setting Entries
    //
    //MemoryVoltageDevice->BaseAddress  = GPIO_BASE_ADDRESS;
    MemoryVoltageDevice->DataSize     = MEMORY_VOLTAGE_DATA_SIZE_GPIO;

    MemoryVoltageSettingEntry2        = (VOLTAGE_DEVICE_SETTING_ENTRY_2 *) (MemoryVoltageDevice + 1);
  } else {
    //MemoryVoltageDevice->BaseAddress  = GPIO_BASE_ADDRESS;
    MemoryVoltageDevice->DataSize     = MEMORY_VOLTAGE_DATA_SIZE_GPIO;

    MemoryVoltageSettingEntry         = (VOLTAGE_DEVICE_SETTING_ENTRY *) (MemoryVoltageDevice + 1);

  }

  for (Index = 0; Index < NoOfVoltages; Index++) {
    if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
        (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
      //
      // Memory voltage table for Emrald Lake Fab 2
      //
      MemoryVoltageSettingEntry2[Index].SettingValue                = MEMORY_VOLTAGE_BASE + (Index * 5);
      MemoryVoltageSettingEntry2[Index].SettingPrecision            = PRECISION_TWO;
      MemoryVoltageSettingEntry2[Index].VoltageValueEntryCount      = MEMORY_VOLTAGE_VALUE_COUNT_EL_FAB2;
//
// @todo OC: SKL PCH GPIO: update library to access.
//
//       MemoryVoltageSettingEntry2[Index].VoltageValueEntry[0].Offset = R_PCH_GPIO_LVL;
      MemoryVoltageSettingEntry2[Index].VoltageValueEntry[0].AndMask = (UINT32) PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_1_EL_FAB2;
      MemoryVoltageSettingEntry2[Index].VoltageValueEntry[0].OrMask =
        (
          ((MemoryVoltageTableMobile[Index][1]) & 0x1) <<
          8
        );
//
// @todo OC: SKL PCH GPIO: update library to access.
//
//       MemoryVoltageSettingEntry2[Index].VoltageValueEntry[1].Offset = R_PCH_GPIO_LVL2;
      MemoryVoltageSettingEntry2[Index].VoltageValueEntry[1].AndMask = (UINT32) PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_2_EL_FAB2;
      MemoryVoltageSettingEntry2[Index].VoltageValueEntry[1].OrMask =
        (
          ((MemoryVoltageTableMobile[Index][1]) & 0x2) <<
          13
        );
    } else {
      MemoryVoltageSettingEntry[Index].SettingValue                 = MemoryVoltageTableDesktop[Index][2];
      MemoryVoltageSettingEntry[Index].SettingPrecision             = PRECISION_THREE;
      MemoryVoltageSettingEntry[Index].VoltageValueEntryCount       = MEMORY_VOLTAGE_VALUE_COUNT;
//
// @todo OC: SKL PCH GPIO: update library to access.
//
//       MemoryVoltageSettingEntry[Index].VoltageValueEntry[0].Offset  = R_PCH_GPIO_LVL2;
      MemoryVoltageSettingEntry[Index].VoltageValueEntry[0].AndMask = (UINT32) PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_DESKTOP;
      MemoryVoltageSettingEntry[Index].VoltageValueEntry[0].OrMask = (UINT32)
        (
          ((MemoryVoltageTableDesktop[Index][1] & 0x1) ? BIT13 : 0) |
            ((MemoryVoltageTableDesktop[Index][1] & 0x2) ? BIT14 : 0) |
              ((MemoryVoltageTableDesktop[Index][1] & 0x4) ? BIT28 : 0)
        );
    }
  }
  //
  // For EML Fab 2 -> we use Memory Voltage Setting Entry table with 2 Voltage Setting Entries
  //
  Dddt = (DDDT *) (MemoryVoltageSettingEntry2 + NoOfVoltages);

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorDesktop) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorWorkstation)){
    Dddt = (DDDT *) (MemoryVoltageSettingEntry + NoOfVoltages);
  }

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorMobile) ||
        (PcdGet8 (PcdPlatformFlavor) == FlavorEmbedded)) {
    //
    // Logical BIOS Settings Device (High Precision): Memory Voltage
    // Device description data
    //
    INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE2, IMPLEMENTATION_TYPE5, VERSION_0);

    HPLogicalBiosSetting                      = (DSD_HP_LBS *) (Dddt + 1);
    HPLogicalBiosSetting->Signature           = HLBC_SIG;
    HPLogicalBiosSetting->MinimumSettingValue = MemoryVoltageTableMobile[0][2];
    HPLogicalBiosSetting->MaximumSettingValue = MemoryVoltageTableMobile[NoOfVoltages - 1][2];
    HPLogicalBiosSetting->ValueStepSize       = MEMORY_VOLTAGE_VALUE_STEP_SIZE;
    HPLogicalBiosSetting->SettingPrecision    = PRECISION_TWO;
    HPLogicalBiosSetting->MinimumSettingData  = MemoryVoltageTableMobile[0][0];
    HPLogicalBiosSetting->MaximumSettingData  = MemoryVoltageTableMobile[NoOfVoltages - 1][0];
    HPLogicalBiosSetting->DataStepSize        = MEMORY_VOLTAGE_DATA_STEP_SIZE;
    HPLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_VOLTS;
    HPLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
    HPLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
    HPLogicalBiosSetting->DefaultSettingData  = mSaSetup.MemoryVoltageDefault;
    Dddt = (DDDT *) (HPLogicalBiosSetting + 1);

  } else {
    //
    // Discrete Logical BIOS Settings Device: Memory Voltage
    // Device description data
    //
    INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE5, VERSION_1);

    LogicalBiosSetting                  = (DSD_LBS *) (Dddt + 1);
    LogicalBiosSetting->Signature       = LBS_SIG;
    LogicalBiosSetting->AutoModeSupport = NOT_SUPPORTED;
    LogicalBiosSetting->DefaultSetting  = mSaSetup.MemoryVoltageDefault;
    LogicalBiosSetting->LBSEntryCount   = NoOfVoltages;

    SettingsEntry                       = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

    for (Index = 0; Index < NoOfVoltages; Index++) {
      SettingsEntry[Index].SettingValue         = MemoryVoltageTableDesktop[Index][2];
      SettingsEntry[Index].SettingPrecision     = PRECISION_THREE;
      SettingsEntry[Index].DataTypeEnumeration  = DATA_TYPE_VOLTS;
      SettingsEntry[Index].BiosSettingsValue    = Index;
    }

    Dddt = (DDDT *) (SettingsEntry + NoOfVoltages);
  }
  //
  // Continuous Logical BIOS Settings Device: Processor Multiplier (Flex Ratio)
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE0, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.MaxEfficiencyRatio;
  ContLogicalBiosSetting->MaximumSettingValue = mCpuSetup.MaxNonTurboRatio;
  ContLogicalBiosSetting->StepSize            = FLEX_RATIO_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.FlexRatioOverrideDefault;
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

  //
  // Discrete Logical BIOS Settings Device (Continuous): Host Clock Frequency (Bus Speed)
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE1, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = gBclkMinValue;
  ContLogicalBiosSetting->MaximumSettingValue = gBclkMaxValue;
  ContLogicalBiosSetting->StepSize            = 10;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_MHZ;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = 10000;
  ContLogicalBiosSetting->SettingPrecision    = 2;
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

  //
  // Discrete Logical BIOS Settings Device: tCL (CAS Latency)
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE7, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tCL_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tCL_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tCL_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tCLDefault;

  //
  // Discrete Logical BIOS Settings Device: tRCD / tRP (RAS to CAS Delay and Bank Precharge time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE8, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tRCD_tRP_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tRCD_tRP_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tRCD_tRP_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tRCDtRPDefault;

  //
  // Continuous Logical BIOS Settings Device: tRAS (Row Active Time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE10, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tRAS_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tRAS_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tRAS_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tRASDefault;

  //
  // High Precision BIOS Settings Device: tWR Multiplier
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE11, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tWR_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tWR_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tWR_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tWRDefault;

  //
  // Continuous Logical BIOS Settings Device: tRFC (Min Refresh Recovery Delay Time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE21, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tRFC_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tRFC_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tRFC_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tRFCDefault;

  //
  // Continuous Logical BIOS Settings Device: tRRD (Min Row Active to Row Active Delay Time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE22, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tRRD_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tRRD_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tRRD_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tRRDDefault;

  //
  // Continuous Logical BIOS Settings Device: tWTR (Min Internal Write to Read Command Delay Time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE23, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tWTR_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tWTR_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tWTR_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tWTRDefault;

  //
  // Continuous Logical BIOS Settings Device: System CMD Rate (NMode)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE24, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = SYSTEM_CMD_RATE_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = SYSTEM_CMD_RATE_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = SYSTEM_CMD_RATE_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = ZERO; // Auto

  //
  // Continuous Logical BIOS Settings Device: tRTP (Min Internal Read to Precharge Command Delay Time)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE25, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tRTP_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tRTP_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tRTP_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tRTPDefault;

  //
  // Continuous Logical BIOS Settings Device: tFAW (Min Four Activate Window Delay Time (tFAWmin)
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE40, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = tFAW_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = tFAW_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = tFAW_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.tFAWDefault;

  //
  // High Precision BIOS Settings Device: DDR Multiplier
  // Device description data
  //
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE19, VERSION_1);

  //
  // Device Specific data
  //
  LogicalBiosSetting                  = (DSD_LBS *) (Dddt + 1);
  LogicalBiosSetting->Signature       = LBS_SIG;
  LogicalBiosSetting->AutoModeSupport = SUPPORTED;
  //
  // Default setting is an index into the Setting Entry Array. Since DDR ratio are from 3 - 10, subtract 3 to indicate the setting entry.
  //
  LogicalBiosSetting->DefaultSetting    = (mSaSetup.DdrRatioDefault - 3);
  LogicalBiosSetting->LBSEntryCount     = DDR_MODE_SETTING_ENTRY_COUNT;

  SettingsEntry                         = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

  SettingsEntry[0].SettingValue         = MEMORY_FREQ_1067;
  SettingsEntry[0].SettingPrecision     = PRECISION_TWO;
  SettingsEntry[0].DataTypeEnumeration  = DATA_TYPE_NONE;
  SettingsEntry[0].BiosSettingsValue    = MEMORY_FREQ_1067_VALUE;

  SettingsEntry[1].SettingValue         = MEMORY_FREQ_1333;
  SettingsEntry[1].SettingPrecision     = PRECISION_TWO;
  SettingsEntry[1].DataTypeEnumeration  = DATA_TYPE_NONE;
  SettingsEntry[1].BiosSettingsValue    = MEMORY_FREQ_1333_VALUE;

  SettingsEntry[2].SettingValue         = MEMORY_FREQ_1600;
  SettingsEntry[2].SettingPrecision     = PRECISION_TWO;
  SettingsEntry[2].DataTypeEnumeration  = DATA_TYPE_NONE;
  SettingsEntry[2].BiosSettingsValue    = MEMORY_FREQ_1600_VALUE;

  SettingsEntry[3].SettingValue         = MEMORY_FREQ_1867;
  SettingsEntry[3].SettingPrecision     = PRECISION_TWO;
  SettingsEntry[3].DataTypeEnumeration  = DATA_TYPE_NONE;
  SettingsEntry[3].BiosSettingsValue    = MEMORY_FREQ_1867_VALUE;

  SettingsEntry[4].SettingValue         = MEMORY_FREQ_2133;
  SettingsEntry[4].SettingPrecision     = PRECISION_TWO;
  SettingsEntry[4].DataTypeEnumeration  = DATA_TYPE_NONE;
  SettingsEntry[4].BiosSettingsValue    = MEMORY_FREQ_2133_VALUE;

  Dddt = (DDDT *) (SettingsEntry + DDR_MODE_SETTING_ENTRY_COUNT);

  //
  // EIST - Discreet Logical BIOS Setting Device
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE41, VERSION_1);

  LogicalBiosSetting                    = (DSD_LBS *) (Dddt + 1);
  LogicalBiosSetting->Signature         = LBS_SIG;
  LogicalBiosSetting->AutoModeSupport   = NOT_SUPPORTED;
  LogicalBiosSetting->DefaultSetting    = mCpuSetup.EnableGvDefault;
  LogicalBiosSetting->LBSEntryCount     = ENABLE_DISABLE_SETTING_ENTRY_COUNT;

  SettingsEntry                         = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

  SettingsEntry[0].SettingValue         = 0;
  SettingsEntry[0].SettingPrecision     = PRECISION_NONE;
  SettingsEntry[0].DataTypeEnumeration  = DATA_TYPE_DISABLE;
  SettingsEntry[0].BiosSettingsValue    = 0;

  SettingsEntry[1].SettingValue         = 1;
  SettingsEntry[1].SettingPrecision     = PRECISION_NONE;
  SettingsEntry[1].DataTypeEnumeration  = DATA_TYPE_ENABLE;
  SettingsEntry[1].BiosSettingsValue    = 1;

  Dddt = (DDDT *) (SettingsEntry + TURBO_MODE_SETTING_ENTRY_COUNT);

  //
  // Logical BIOS Settings Device: Primary Plane Current Limit
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE2, IMPLEMENTATION_TYPE57, VERSION_0);

  //
  // Device Specific data
  //
  HPLogicalBiosSetting                      = (DSD_HP_LBS *) (Dddt + 1);
  HPLogicalBiosSetting->Signature           = HLBC_SIG;
  HPLogicalBiosSetting->MinimumSettingValue = PRIMARY_PLANE_CURRENT_LIMIT_MINIMUM;
  HPLogicalBiosSetting->MaximumSettingValue = PRIMARY_PLANE_CURRENT_LIMIT_MAXIMUM;
  HPLogicalBiosSetting->ValueStepSize       = PRIMARY_PLANE_CURRENT_LIMIT_STEP_SIZE;
  HPLogicalBiosSetting->SettingPrecision    = PRECISION_THREE;
  HPLogicalBiosSetting->MinimumSettingData  = PRIMARY_PLANE_CURRENT_LIMIT_MINIMUM_DATA;
  HPLogicalBiosSetting->MaximumSettingData  = PRIMARY_PLANE_CURRENT_LIMIT_MAXIMUM_DATA;
  HPLogicalBiosSetting->DataStepSize        = STEP_SIZE_1;
  HPLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_AMPS;
  HPLogicalBiosSetting->AutoModeSupport     = SUPPORTED;
  HPLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  HPLogicalBiosSetting->DefaultSettingData  = ZERO;
  Dddt = (DDDT *) (HPLogicalBiosSetting + 1);

  //
  // Logical BIOS Settings Device: Secondary Plane Current Limit
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE2, IMPLEMENTATION_TYPE58, VERSION_0);

  //
  // Device Specific data
  //
  HPLogicalBiosSetting                      = (DSD_HP_LBS *) (Dddt + 1);
  HPLogicalBiosSetting->Signature           = HLBC_SIG;
  HPLogicalBiosSetting->MinimumSettingValue = SECONDARY_PLANE_CURRENT_LIMIT_MINIMUM;
  HPLogicalBiosSetting->MaximumSettingValue = SECONDARY_PLANE_CURRENT_LIMIT_MAXIMUM;
  HPLogicalBiosSetting->ValueStepSize       = SECONDARY_PLANE_CURRENT_LIMIT_STEP_SIZE;
  HPLogicalBiosSetting->SettingPrecision    = PRECISION_THREE;
  HPLogicalBiosSetting->MinimumSettingData  = SECONDARY_PLANE_CURRENT_LIMIT_MINIMUM_DATA;
  HPLogicalBiosSetting->MaximumSettingData  = SECONDARY_PLANE_CURRENT_LIMIT_MAXIMUM_DATA;
  HPLogicalBiosSetting->DataStepSize        = STEP_SIZE_1;
  HPLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_AMPS;
  HPLogicalBiosSetting->AutoModeSupport     = SUPPORTED;
  HPLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  Dddt = (DDDT *) (HPLogicalBiosSetting + 1);

  //
  // Logical BIOS Settings Device: Internal Graphics Freq Limit
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE59, VERSION_0);

  //
  // Device Specific data
  //
  ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
  ContLogicalBiosSetting->Signature           = LBC_SIG;
  ContLogicalBiosSetting->MinimumSettingValue = IGD_FREQ_RATIO_LIMIT_MINIMUM;
  ContLogicalBiosSetting->MaximumSettingValue = IGD_FREQ_RATIO_LIMIT_MAXIMUM;
  ContLogicalBiosSetting->StepSize            = IGD_FREQ_RATIO_LIMIT_STEP_SIZE;
  ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
  ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  ContLogicalBiosSetting->DefaultSetting      = mSaSetup.GtMaxOcRatioDefault;
  Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

  //
  // Logical BIOS Settings Device: Internal Graphics Voltage Limit
  // Device description data
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE2, IMPLEMENTATION_TYPE60, VERSION_0);

  //
  // Device Specific data
  //
  HPLogicalBiosSetting                      = (DSD_HP_LBS *) (Dddt + 1);
  HPLogicalBiosSetting->Signature           = HLBC_SIG;
  HPLogicalBiosSetting->MinimumSettingValue = IGD_VOLTAGE_LIMIT_MINIMUM;
  HPLogicalBiosSetting->MaximumSettingValue = IGD_VOLTAGE_LIMIT_MAXIMUM;
  HPLogicalBiosSetting->ValueStepSize       = IGD_VOLTAGE_LIMIT_STEP_SIZE;
  HPLogicalBiosSetting->SettingPrecision    = PRECISION_EIGHT;
  HPLogicalBiosSetting->MinimumSettingData  = IGD_VOLTAGE_LIMIT_MINIMUM_DATA;
  HPLogicalBiosSetting->MaximumSettingData  = IGD_VOLTAGE_LIMIT_MAXIMUM_DATA;
  HPLogicalBiosSetting->DataStepSize        = STEP_SIZE_1;
  HPLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_VOLTS;
  HPLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
  HPLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
  HPLogicalBiosSetting->DefaultSettingData  = ZERO;
  Dddt = (DDDT *) (HPLogicalBiosSetting + 1);

  //
  // Continuous Logical BIOS Settings Device: Turbo Mode
  // Device description data
  //
  if (SetupCpuFeatures.TurboModeAvailable) {

    INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE26, VERSION_1);
    //
    // Device Specific data
    //
    LogicalBiosSetting                    = (DSD_LBS *) (Dddt + 1);
    LogicalBiosSetting->Signature         = LBS_SIG;
    LogicalBiosSetting->AutoModeSupport   = NOT_SUPPORTED;
    LogicalBiosSetting->DefaultSetting    = mCpuSetup.TurboModeDefault;
    LogicalBiosSetting->LBSEntryCount     = TURBO_MODE_SETTING_ENTRY_COUNT;

    SettingsEntry                         = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

    SettingsEntry[0].SettingValue         = 0;
    SettingsEntry[0].SettingPrecision     = PRECISION_NONE;
    SettingsEntry[0].DataTypeEnumeration  = DATA_TYPE_DISABLE;
    SettingsEntry[0].BiosSettingsValue    = 0;

    SettingsEntry[1].SettingValue         = 1;
    SettingsEntry[1].SettingPrecision     = PRECISION_NONE;
    SettingsEntry[1].DataTypeEnumeration  = DATA_TYPE_ENABLE;
    SettingsEntry[1].BiosSettingsValue    = 1;

    Dddt = (DDDT *) (SettingsEntry + TURBO_MODE_SETTING_ENTRY_COUNT);

    if (SetupCpuFeatures.XETdcTdpLimitAvailable) {
      //
      // logical BIOS Settings Device: Turbo Power Limit MSR Lock Enable/Disable
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE50, VERSION_1);
      //
      // Device Specific data
      //
      LogicalBiosSetting                    = (DSD_LBS *) (Dddt + 1);
      LogicalBiosSetting->Signature         = LBS_SIG;
      LogicalBiosSetting->AutoModeSupport   = NOT_SUPPORTED;
      LogicalBiosSetting->DefaultSetting    = 0;
      LogicalBiosSetting->LBSEntryCount     = ENABLE_DISABLE_SETTING_ENTRY_COUNT;

      SettingsEntry                         = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

      SettingsEntry[0].SettingValue         = 0;
      SettingsEntry[0].SettingPrecision     = PRECISION_NONE;
      SettingsEntry[0].DataTypeEnumeration  = DATA_TYPE_DISABLE;
      SettingsEntry[0].BiosSettingsValue    = 0;

      SettingsEntry[1].SettingValue         = 1;
      SettingsEntry[1].SettingPrecision     = PRECISION_NONE;
      SettingsEntry[1].DataTypeEnumeration  = DATA_TYPE_ENABLE;
      SettingsEntry[1].BiosSettingsValue    = 1;

      Dddt = (DDDT *) (SettingsEntry + ENABLE_DISABLE_SETTING_ENTRY_COUNT);

      //
      // logical BIOS Settings Device: Extended Window Package TDP Limit
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE48, VERSION_0);

      //
      // Device Specific data
      //
      ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
      ContLogicalBiosSetting->Signature           = LBC_SIG;
      ContLogicalBiosSetting->MinimumSettingValue = gMinTurboPowerLimit;
      if (gIsRatioLimitProgrammable) {
        ContLogicalBiosSetting->MaximumSettingValue = gMaxTurboPowerLimit;
      } else {
        ContLogicalBiosSetting->MaximumSettingValue = gPackageTdpLimit;
      }

      ContLogicalBiosSetting->StepSize            = STEP_SIZE_1;
      ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_WATTS;
      ContLogicalBiosSetting->AutoModeSupport     = SUPPORTED;
      ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
      ContLogicalBiosSetting->DefaultSetting      = (UINT16)mCpuSetup.PowerLimit1Default/1000;
      Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

      //
      // logical BIOS Settings Device: Short Window Package Power Limit Enable/Disable
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE0, IMPLEMENTATION_TYPE49, VERSION_1);
      //
      // Device Specific data
      //
      LogicalBiosSetting                    = (DSD_LBS *) (Dddt + 1);
      LogicalBiosSetting->Signature         = LBS_SIG;
      LogicalBiosSetting->AutoModeSupport   = NOT_SUPPORTED;
      LogicalBiosSetting->DefaultSetting    = mCpuSetup.PowerLimit2;
      LogicalBiosSetting->LBSEntryCount     = ENABLE_DISABLE_SETTING_ENTRY_COUNT;

      SettingsEntry                         = (LBS_SETTINGS_ENTRY *) (LogicalBiosSetting + 1);

      SettingsEntry[0].SettingValue         = 0;
      SettingsEntry[0].SettingPrecision     = PRECISION_NONE;
      SettingsEntry[0].DataTypeEnumeration  = DATA_TYPE_DISABLE;
      SettingsEntry[0].BiosSettingsValue    = 0;

      SettingsEntry[1].SettingValue         = 1;
      SettingsEntry[1].SettingPrecision     = PRECISION_NONE;
      SettingsEntry[1].DataTypeEnumeration  = DATA_TYPE_ENABLE;
      SettingsEntry[1].BiosSettingsValue    = 1;

      Dddt = (DDDT *) (SettingsEntry + ENABLE_DISABLE_SETTING_ENTRY_COUNT);

      //
      // logical BIOS Settings Device: Short Window Package TDP Limit
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE47, VERSION_0);

      //
      // Device Specific data
      //
      ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
      ContLogicalBiosSetting->Signature           = LBC_SIG;
      ContLogicalBiosSetting->MinimumSettingValue = gMinTurboPowerLimit;
      ContLogicalBiosSetting->MaximumSettingValue = gMaxTurboPowerLimit;
      ContLogicalBiosSetting->StepSize            = STEP_SIZE_1;
      ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_WATTS;
      ContLogicalBiosSetting->AutoModeSupport     = SUPPORTED;
      ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
      ContLogicalBiosSetting->DefaultSetting      = (UINT16)mCpuSetup.PowerLimit2Default/1000;
      Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

    }

    if (SetupCpuFeatures.CoreRatioLimitAvailable) {
      //
      // logical BIOS Settings Device: XE Extra Voltage
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE2, IMPLEMENTATION_TYPE46, VERSION_0);

      //
      // Device Specific data
      //
      HPLogicalBiosSetting                      = (DSD_HP_LBS *) (Dddt + 1);
      HPLogicalBiosSetting->Signature           = HLBC_SIG;
      HPLogicalBiosSetting->MinimumSettingValue = XE_EXTRA_VOLTAGE_MINIMUM;
      HPLogicalBiosSetting->MaximumSettingValue = XE_EXTRA_VOLTAGE_MAXIMUM;
      HPLogicalBiosSetting->ValueStepSize       = XE_EXTRA_VOLTAGE_STEP_SIZE;
      HPLogicalBiosSetting->SettingPrecision    = PRECISION_EIGHT;
      HPLogicalBiosSetting->MinimumSettingData  = XE_EXTRA_VOLTAGE_MINIMUM_DATA;
      HPLogicalBiosSetting->MaximumSettingData  = XE_EXTRA_VOLTAGE_MAXIMUM_DATA;
      HPLogicalBiosSetting->DataStepSize        = STEP_SIZE_1;
      HPLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_VOLTS;
      HPLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
      HPLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
      HPLogicalBiosSetting->DefaultSettingData  = ZERO;
      Dddt = (DDDT *) (HPLogicalBiosSetting + 1);

      //
      // If Lock-Limited CPU, set the maximum
      //
      FlexRatioMsr.Qword    = AsmReadMsr64 (MSR_FLEX_RATIO);
      OverclockingBins      = (UINT8) RShiftU64 ((FlexRatioMsr.Dwords.Low & OVERCLOCKING_BINS), 17);
      if ((OverclockingBins > 0) && (OverclockingBins < MAX_OVERCLOCKING_BINS)) {
        TurboRatioLimit.Qword = AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT);
        OneCoreRatioLimitMax  = (UINT8)(OverclockingBins + (TurboRatioLimit.Qword & MAX_RATIO_LIMIT_1C_MASK));
        TwoCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_2C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
        if (gCoreCount > 2) {
          ThreeCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_3C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
          FourCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_4C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
          if (gCoreCount > 4) {
            FiveCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_5C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
            SixCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_6C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
            if (gCoreCount > 6) {
              SevenCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_7C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
              EightCoreRatioLimitMax = OverclockingBins + ((UINT8) (RShiftU64(TurboRatioLimit.Qword, MAX_RATIO_LIMIT_8C_OFFSET) & MAX_RATIO_LIMIT_1C_MASK));
            }
          }
        }
      }
      //
      // logical BIOS Settings Device: 1 Core Ratio Limit
      // Device description data
      //
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE29, VERSION_0);

      //
      // Device Specific data
      //
      ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
      ContLogicalBiosSetting->Signature           = LBC_SIG;
      ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
      ContLogicalBiosSetting->MaximumSettingValue = (UINT16) OneCoreRatioLimitMax;
      ContLogicalBiosSetting->StepSize            = CORE1_RATIO_STEP_SIZE;
      ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
      ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
      ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
      ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit1Default;

      //
      // logical BIOS Settings Device: 2 Core Ratio Limit
      // Device description data
      //
      Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
      INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE30, VERSION_0);

      //
      // Device Specific data
      //
      ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
      ContLogicalBiosSetting->Signature           = LBC_SIG;
      ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
      ContLogicalBiosSetting->MaximumSettingValue = (UINT16) TwoCoreRatioLimitMax;
      ContLogicalBiosSetting->StepSize            = CORE2_RATIO_STEP_SIZE;
      ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
      ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
      ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
      ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit2Default;

      Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

      if (gCoreCount > 2) {
        //
        // logical BIOS Settings Device: 3 Core Ratio Limit
        // Device description data
        //
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE31, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) ThreeCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE3_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit3Default;

        //
        // logical BIOS Settings Device: 4 Core Ratio Limit
        // Device description data
        //
        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE32, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) FourCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE4_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit4Default;

        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

        //
        // logical BIOS Settings Device: 5 Core Ratio Limit
        // Device description data
        //
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE33, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) FiveCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE5_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit5Default;

        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

        //
        // logical BIOS Settings Device: 6 Core Ratio Limit
        // Device description data
        //
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE34, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) SixCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE6_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit6Default;

        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

        //
        // logical BIOS Settings Device: 7 Core Ratio Limit
        // Device description data
        //
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE35, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) SevenCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE7_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit7Default;

        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);

        //
        // logical BIOS Settings Device: 8 Core Ratio Limit
        // Device description data
        //
        INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE4, CONTROL_TYPE1, IMPLEMENTATION_TYPE61, VERSION_0);

        //
        // Device Specific data
        //
        ContLogicalBiosSetting                      = (DSD_CONTINUOUS_LBS *) (Dddt + 1);
        ContLogicalBiosSetting->Signature           = LBC_SIG;
        ContLogicalBiosSetting->MinimumSettingValue = mCpuSetup.CpuRatio;
        ContLogicalBiosSetting->MaximumSettingValue = (UINT16) EightCoreRatioLimitMax;
        ContLogicalBiosSetting->StepSize            = CORE8_RATIO_STEP_SIZE;
        ContLogicalBiosSetting->DataTypeEnumeration = DATA_TYPE_NONE;
        ContLogicalBiosSetting->AutoModeSupport     = NOT_SUPPORTED;
        ContLogicalBiosSetting->PerformanceFlag     = MIN_SETTING_LOW_PERFORMANCE;
        ContLogicalBiosSetting->DefaultSetting      = mCpuSetup.RatioLimit8Default;

        Dddt = (DDDT *) (ContLogicalBiosSetting + 1);
      }
      //
      // end if (gCoreCount > 2)
      //
    }
  }
  //
  // End of Device list
  //
  INIT_DDDT (Dddt, DDDT_SIG, DEVICE_TYPE0, CONTROL_TYPE0, IMPLEMENTATION_TYPE0, VERSION_0);
  DddtEnd = (DDDT *) (Dddt + 1);
  //
  // Calculate checksum for entire SPTT table
  //
  Sptt->Checksum = ChecksumTable ((UINT8 *) Sptt, Sptt->Length);

  //
  // Assert the code if the SPTT table created size is greater than the allocated size
  //
  if ((UINT8 *) DddtEnd > ((UINT8 *) Sptt + Sptt->Length)) {
    ASSERT (0);
    (gBS->FreePool) (Sptt);
    return 0;
  }

  return (UINT64) Sptt;
}

/**
  Calculates checksum for table.

  @param[in] TblStart        Start Address of the Table
  @param[in] BytesCount      Number of Bytes Count

  @retval Checksum           Return to the Checksum value of the table
**/
UINT8
ChecksumTable (
  IN  UINT8     *TblStart,
  IN  UINT32    BytesCount
  )
{
  UINTN i;
  UINT8 CheckSum;

  CheckSum = *TblStart;
  for (i = 1; i < BytesCount; i++) {
    CheckSum = CheckSum + TblStart[i];
  }

  CheckSum = 0 - CheckSum;
  return CheckSum;
}

/**
  This function will start the Watchdog Timer.

  @param[in] TimeoutValue     Time out value in seconds

  @retval EFI_SUCCESS         Start the Watchdog Timer successfully

  Appropiate failure code on error.

**/
EFI_STATUS
StartTimer (
  IN  UINT32  TimeoutValue
  )
{
  EFI_STATUS  Status;

  DEBUG_CODE(TimeoutValue = 180;);

  Status = gWdtDxe->ReloadAndStart (TimeoutValue);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
