/** @file
  Cpu driver, which initializes ACPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

@par Specification
**/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Cpu/IncludePrivate/PowerMgmtNvsStruct.h>
#include <Protocol/CpuNvsArea.h>
#include "CpuInitDxe.h"
#include <Protocol/BiosGuardNvsArea.h>

GLOBAL_REMOVE_IF_UNREFERENCED CPU_NVS_AREA_PROTOCOL       mCpuNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG                  *mCpuConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED BIOSGUARD_NVS_AREA_PROTOCOL BiosGuardNvsAreaProtocol;

/**
  Initialize Cpu Nvs Area Protocol

  @param[in] ImageHandle - Image handle of the loaded driver

  @retval EFI_SUCCESS           - thread can be successfully created
**/
EFI_STATUS
EFIAPI
CpuAcpiInit (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS                 Status;
  EFI_PHYSICAL_ADDRESS       Area;
  MSR_REGISTER               TempMsr;
  UINT8                      MaxRefTemp;
  UINT8                      Index;
  CPU_INIT_DATA_HOB          *CpuInitDataHob;
  CPU_CONFIG_DATA            *CpuConfigData;
  VOID                       *Hob;
  UINTN                      Pages;
  UINT16                     C6Latency = 0;
  UINT16                     C7Latency = 0;
  UINT16                     C8Latency = 0;
  UINT16                     C9Latency = 0;
  UINT16                     C10Latency = 0;
  CPU_SKU                    CpuSku;

  ///
  /// Get CPU Init Data Hob
  ///
  Hob = GetFirstGuidHob (&gCpuInitDataHobGuid);
  if (Hob == NULL) {
      DEBUG ((DEBUG_ERROR, "CPU Data HOB not available\n"));
      ASSERT (Hob != NULL);
      return EFI_NOT_FOUND;
  }
  CpuInitDataHob = (CPU_INIT_DATA_HOB *)((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
  CpuConfigData = (CPU_CONFIG_DATA *)(UINTN) CpuInitDataHob->CpuConfigData;
  CpuSku = GetCpuSku ();

  ///
  /// Allocated ACPI NVS type memory for Cpu Nvs Configuration.
  ///
  Pages = EFI_SIZE_TO_PAGES (sizeof (CPU_NVS_AREA));
  Area = 0xffffffff; // allocate address below 4G.

  Status = gBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiACPIMemoryNVS,
                  Pages,
                  &Area
                  );
  ASSERT_EFI_ERROR (Status);

  mCpuNvsAreaProtocol.Area = (CPU_NVS_AREA *)(UINTN) Area;
  ZeroMem ((VOID *)mCpuNvsAreaProtocol.Area, sizeof (CPU_NVS_AREA));
  mCpuNvsAreaProtocol.Area->Cpuid = GetCpuFamily() | GetCpuStepping();
  mCpuNvsAreaProtocol.Area->Revision = CPU_NVS_AREA_REVISION;

  ///
  /// Calculate the number of Oc bins supported. Read in MSR 194h FLEX_RATIO bits (19:17)
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_FLEX_RATIO);
  mCpuNvsAreaProtocol.Area->OcBins = (UINT8)RShiftU64((TempMsr.Dwords.Low & B_MSR_FLEX_RATIO_OC_BINS_MASK), N_MSR_FLEX_RATIO_OC_BINS_OFFSET);

  ///
  /// Update NVS ASL items.
  ///

  ///
  /// Intel Turbo Boost Max Technology 3.0
  ///
  mCpuNvsAreaProtocol.Area->ItbmSmi = (UINTN)PcdGet8 (PcdItbmSmi); ///< SMI for resuming the periodic SMM if the OS supports frequency re-read.

  ///
  /// Automatic Thermal Reporting for Thermal Management
  ///
  if (CpuConfigData->AutoThermalReporting) {
    ///
    /// Thermal Reporting for Critical trip
    /// MSR 1A2 bits 23:16 define the temperature that this specific processor can
    /// function upto. It is recommended that this value + 5  be used as default Critical trip point
    /// _CRT.
    ///
    TempMsr.Qword = AsmReadMsr64 (MSR_TEMPERATURE_TARGET);
    TempMsr.Qword &= (UINT64)B_MSR_TEMPERATURE_TARGET_REF_TEMP_MASK;
    MaxRefTemp = (UINT8)RShiftU64(TempMsr.Qword, N_MSR_TEMPERATURE_TARGET_REF_TEMP_OFFSET);
    mCpuNvsAreaProtocol.Area->AutoCriticalTripPoint = MaxRefTemp + 5;

    ///
    /// Thermal Reporting for Active Thermal Management
    /// It is recommended that the processor specific value in MSR 1A2 bits 15:8
    /// be used as the highest Active trip point i.e. _AC0.
    ///
    TempMsr.Qword = AsmReadMsr64 (MSR_TEMPERATURE_TARGET);
    TempMsr.Qword &= (UINT64)B_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFST_MASK;
    mCpuNvsAreaProtocol.Area->AutoActiveTripPoint = MaxRefTemp - (UINT8)RShiftU64 (
        TempMsr.Qword,
        N_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFST_OFFSET
        );

    ///
    /// Thermal Reporting for Passive Thermal Management
    /// On all turbo enabled systems, it is recommended that the ACPI _PSV point be
    /// set to a temperature above the Active cooling temperature and Tcc activation
    /// temperature.
    /// If platform embedded controller will issue PECI commands to reduce power as a
    /// passive thermal action, then it is recommended to use the package's max temperature
    /// for passive thermal control.
    ///
    TempMsr.Qword = AsmReadMsr64 (MSR_TEMPERATURE_TARGET);
    TempMsr.Qword &= B_MSR_TEMPERATURE_TARGET_TJ_MAX_TCC_OFFSET_MASK;
    mCpuNvsAreaProtocol.Area->AutoPassiveTripPoint = mCpuNvsAreaProtocol.Area->AutoCriticalTripPoint + 3;
  }

  ///
  ///  Update the PPM NVS area PPM flags
  ///
  mCpuNvsAreaProtocol.Area->PpmFlags = CpuInitDataHob->PpmFlags;

  ///
  /// For U/Y, hard coded latency values are used instead of calculations. Set values here.
  ///
  switch (CpuSku) {
    case EnumCpuUlt:
      C6Latency = 127;
      C7Latency = 253;
      C8Latency = 260;
      C9Latency = 487;
      C10Latency = 1048;
    break;

    case EnumCpuUlx:
      C6Latency = 126;
      C7Latency = 230;
      C8Latency = 239;
      C9Latency = 398;
      C10Latency = 993;
    break;

    default:
    break;
  }


  ///
  /// Update PPM NVRAM Values for C6
  ///
  if (mCpuNvsAreaProtocol.Area->PpmFlags & C6_LONG_LATENCY_ENABLE) {
      mCpuNvsAreaProtocol.Area->C6MwaitValue = MWAIT_C6_1;
  } else {
      mCpuNvsAreaProtocol.Area->C6MwaitValue = MWAIT_C6;
  }


  ///
  /// Update PPM NVRAM Values for C7 - select the C-state supported among- C7 / C7S
  ///
  if (mCpuNvsAreaProtocol.Area->PpmFlags & PPM_C7) { // Is C7 supported ?
      if (mCpuNvsAreaProtocol.Area->PpmFlags & C7_LONG_LATENCY_ENABLE) {
      mCpuNvsAreaProtocol.Area->C7MwaitValue = MWAIT_C7_1;
      } else {
          mCpuNvsAreaProtocol.Area->C7MwaitValue = MWAIT_C7;
      }
  }
  if (mCpuNvsAreaProtocol.Area->PpmFlags & PPM_C7S) { // Is C7S supported ?
      if (mCpuNvsAreaProtocol.Area->PpmFlags & C7s_LONG_LATENCY_ENABLE) {
          mCpuNvsAreaProtocol.Area->C7MwaitValue = MWAIT_C7_3;
      } else {
          mCpuNvsAreaProtocol.Area->C7MwaitValue = MWAIT_C7_2;
      }
  }

  ///
  /// For ICL, hard coded values are used instead of calculations. Reinitialize here to simplify the code for C6 and C7.
  ///

  if (C6Latency != 0) {
      mCpuNvsAreaProtocol.Area->C6Latency = LATENCY_C6;
  }

  if (C7Latency != 0) {
      mCpuNvsAreaProtocol.Area->C7Latency = LATENCY_C7;
  }
  ///
  /// Update PPM NVRAM Values for CD - select the deepest C-state supported among- C8 / C9 / C10
  ///
  if (mCpuNvsAreaProtocol.Area->PpmFlags & PPM_C10) { // C10 supported
      mCpuNvsAreaProtocol.Area->CDIOLevel = PCH_ACPI_LV7;
      mCpuNvsAreaProtocol.Area->CDPowerValue = C10_POWER;
      mCpuNvsAreaProtocol.Area->CDMwaitValue = MWAIT_CD_2;
      if (C10Latency != 0) {
        mCpuNvsAreaProtocol.Area->CDLatency = LATENCY_C10;
      }
  } else if (mCpuNvsAreaProtocol.Area->PpmFlags & PPM_C9) { // C9 supported
      mCpuNvsAreaProtocol.Area->CDIOLevel = PCH_ACPI_LV6;
      mCpuNvsAreaProtocol.Area->CDPowerValue = C9_POWER;
      mCpuNvsAreaProtocol.Area->CDMwaitValue = MWAIT_CD_1;
      if (C9Latency != 0) {
          mCpuNvsAreaProtocol.Area->CDLatency = LATENCY_C9;
      }
  } else if (mCpuNvsAreaProtocol.Area->PpmFlags & PPM_C8) { // C8 supported
      mCpuNvsAreaProtocol.Area->CDIOLevel = PCH_ACPI_LV5;
      mCpuNvsAreaProtocol.Area->CDPowerValue = C8_POWER;
      mCpuNvsAreaProtocol.Area->CDMwaitValue = MWAIT_CD;
      if (C8Latency != 0) {
           mCpuNvsAreaProtocol.Area->CDLatency = LATENCY_C8;
      }
  }

  mCpuNvsAreaProtocol.Area->CtdpLevelsSupported =CpuInitDataHob->CtdpLevelsSupported;                        /// ConfigTdp Number Of Levels.
  mCpuNvsAreaProtocol.Area->ConfigTdpBootModeIndex = CpuInitDataHob->ConfigTdpBootModeIndex;                 /// CTDP Boot Mode Index
  for (Index = 0; Index < 3; Index++) {
    mCpuNvsAreaProtocol.Area->CtdpTar [Index] = CpuInitDataHob->CtdpTar [Index];                             /// CTDP Levels TAR
    mCpuNvsAreaProtocol.Area->CtdpPowerLimit1 [Index] = CpuInitDataHob->CtdpPowerLimit1 [Index];             /// CTDP Levels Power Limit1
    mCpuNvsAreaProtocol.Area->CtdpPowerLimit2 [Index] = CpuInitDataHob->CtdpPowerLimit2 [Index];             /// CTDP Levels Power Limit2
    mCpuNvsAreaProtocol.Area->CtdpPowerLimitWindow [Index] =CpuInitDataHob->CtdpPowerLimitWindow [Index];    /// CTDP Levels Power Limit1 Time Window
    mCpuNvsAreaProtocol.Area->CtdpCtc [Index] = CpuInitDataHob->CtdpCtc [Index];                             /// CTDP Levels CTC
    mCpuNvsAreaProtocol.Area->CtdpPpc [Index] = CpuInitDataHob->CtdpPpc [Index];                             /// CTDP Levels PPC
  }
  mCpuNvsAreaProtocol.Area->EnableItbm = CpuInitDataHob->EnableItbm;                                         /// Enable/Disable Intel Turbo Boost Max Technology 3.0.
  mCpuNvsAreaProtocol.Area->EnableItbmDriver = CpuInitDataHob->EnableItbmDriver;                             /// Enable/Disable Intel Turbo Boost Max Technology 3.0 Driver.
  mCpuNvsAreaProtocol.Area->LowestMaxPerf = CpuInitDataHob->LowestMaxPerf;                                   /// Max ratio of the slowest core.
  mCpuNvsAreaProtocol.Area->ConfigurablePpc = CpuInitDataHob->ConfigurablePpc;                               /// Max ratio of the slowest core.
  mCpuNvsAreaProtocol.Area->DtsIoTrapAddress = DTS_IO_TRAP_ADDRESS;
  mCpuNvsAreaProtocol.Area->DtsIoTrapLength = DTS_IO_TRAP_LENGTH;
  mCpuNvsAreaProtocol.Area->DtsAcpiEnable = DTS_ACPI_DISABLE;

  ///
  /// Install Cpu Power management GlobalNVS Area protocol
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gCpuNvsAreaProtocolGuid,
                  &mCpuNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Initialize BIOS Guard Nvs Area Protocol

  @param[in] ImageHandle - Image handle of the loaded driver

  @retval EFI_SUCCESS           - thread can be successfully created
**/
EFI_STATUS
EFIAPI
BiosGuardAcpiInit (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS        Status;

  ///
  /// Install BIOS Guard NVS Area protocol
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gBiosGuardNvsAreaProtocolGuid,
                  &BiosGuardNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}