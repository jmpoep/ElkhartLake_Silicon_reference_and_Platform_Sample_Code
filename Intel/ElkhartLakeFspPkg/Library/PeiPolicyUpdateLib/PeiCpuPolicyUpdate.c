/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <FspsUpd.h>
#include <Library/DebugLib.h>
#include <Library/CpuPlatformLib.h>
#include <Register/Cpuid.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PcdLib.h>


/**
  Get the next microcode patch pointer.

  @param[in, out] MicrocodeData - Input is a pointer to the last microcode patch address found,
                                  and output points to the next patch address found.

  @retval EFI_SUCCESS           - Patch found.
  @retval EFI_NOT_FOUND         - Patch not found.
**/
EFI_STATUS
EFIAPI
RetrieveNextMicrocode (
  IN OUT CPU_MICROCODE_HEADER   **MicrocodeData,
  IN UINT32 MicrocodeEnd
  )
{
  UINT32  TotalSize;

  TotalSize =(UINT32)((*MicrocodeData)->TotalSize);
  if (TotalSize == 0) {
    TotalSize = 2048;
  } else if (TotalSize == (UINT32) -1) {
    //
    // Return if function tries to read from empty region (0xFFFFFFFF)
    //
    return EFI_NOT_FOUND;
  }

  *MicrocodeData = (CPU_MICROCODE_HEADER *)((UINTN)*MicrocodeData + TotalSize);
  if (*MicrocodeData >= (CPU_MICROCODE_HEADER *)(UINTN)MicrocodeEnd || *MicrocodeData == (VOID*)-1) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}

/**
  Get the microcode patch pointer.

  @retval EFI_PHYSICAL_ADDRESS - Address of the microcode patch, or NULL if not found.
**/
EFI_PHYSICAL_ADDRESS
PlatformCpuLocateMicrocodePatch (
    IN UINT32 MicrocodeRegionBase,
    IN UINT32 MicrocodeRegionLength
  )
{
  EFI_STATUS              Status;
  CPU_MICROCODE_HEADER    *MicrocodeData = (CPU_MICROCODE_HEADER *)MicrocodeRegionBase;
  UINT32                  MicrocodeEnd = MicrocodeRegionBase + MicrocodeRegionLength;
  EFI_CPUID_REGISTER      Cpuid;
  UINT32                  UcodeRevision;


  AsmCpuid (
    CPUID_VERSION_INFO,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  UcodeRevision = GetCpuUcodeRevision ();

  Status = EFI_SUCCESS;   //Initialize to EFI_SUCCESS, so first microcode is successful.
  while (TRUE) {
    if (CheckMicrocode (Cpuid.RegEax, MicrocodeData, &UcodeRevision)) break;

    //
    // Find the next patch address
    //
    Status = RetrieveNextMicrocode (&MicrocodeData, MicrocodeEnd);
    if (Status != EFI_SUCCESS) {
      break;
    }

  }

  if (EFI_ERROR (Status)) {
    return 0;
  }

  return (EFI_PHYSICAL_ADDRESS)(UINTN)MicrocodeData;
}

/**
  This function performs CPU PEI Policy initialization.

  @param[in] SiPolicyPpi           The SI Policy PPI instance
  @param[in] FspsUpd               The pointer of FspsUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiCpuPolicy (
  IN OUT SI_POLICY_PPI        *SiPolicyPpi,
  IN FSPS_UPD                 *FspsUpd
  )
{
  EFI_STATUS                       Status;
  UINT32                           MicrocodeRegionBase;
  UINT32                           MicrocodeRegionSize;
  CPU_CONFIG                       *CpuConfig;
  CPU_POWER_MGMT_BASIC_CONFIG      *CpuPowerMgmtBasicConfig;
  CPU_POWER_MGMT_VR_CONFIG         *CpuPowerMgmtVrConfig;
  CPU_POWER_MGMT_CUSTOM_CONFIG     *CpuPowerMgmtCustomConfig;
  CPU_POWER_MGMT_PSYS_CONFIG       *CpuPowerMgmtPsysConfig;
  CPU_TEST_CONFIG                  *CpuTestConfig;
  CPU_POWER_MGMT_TEST_CONFIG       *CpuPowerMgmtTestConfig;
  UINTN                             Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtVrConfigGuid, (VOID *) &CpuPowerMgmtVrConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtCustomConfigGuid, (VOID *) &CpuPowerMgmtCustomConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtPsysConfigGuid, (VOID *) &CpuPowerMgmtPsysConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &CpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtTestConfigGuid, (VOID *) &CpuPowerMgmtTestConfig);
  ASSERT_EFI_ERROR (Status);
  MicrocodeRegionBase = FspsUpd->FspsConfig.MicrocodeRegionBase;
  MicrocodeRegionSize = FspsUpd->FspsConfig.MicrocodeRegionSize;

  CpuConfig->MicrocodePatchAddress = 0; //This must be initialized, since if statement below may not initialize.

  if (MicrocodeRegionBase != 0 && MicrocodeRegionSize != 0) {
    DEBUG((DEBUG_INFO, "Searching for microcode updates in region UPD MicrocodeRegionBase = 0x%x, UPD MicrocodeRegionSize = 0x%x.\n",
      MicrocodeRegionBase, MicrocodeRegionSize
      ));

    CpuConfig->MicrocodePatchAddress = PlatformCpuLocateMicrocodePatch(MicrocodeRegionBase, MicrocodeRegionSize);

    if (CpuConfig->MicrocodePatchAddress == 0) {
      DEBUG((DEBUG_ERROR, "Microcode update not available in UPD region.\n"));
    }
  }

  if (CpuConfig->MicrocodePatchAddress == 0) {
    FSP_GLOBAL_DATA * FspGlobalData = GetFspGlobalDataPointer ();

    MicrocodeRegionBase = FspGlobalData->PlatformData.MicrocodeRegionBase;
    MicrocodeRegionSize = FspGlobalData->PlatformData.MicrocodeRegionSize;

    DEBUG((DEBUG_INFO, "Searching for microcode updates in region passed in TempRamInit API MicrocodeRegionBase = 0x%x, MicrocodeRegionSize = 0x%x.\n",
      MicrocodeRegionBase, MicrocodeRegionSize
      ));

    CpuConfig->MicrocodePatchAddress = PlatformCpuLocateMicrocodePatch(MicrocodeRegionBase, MicrocodeRegionSize);
    if (CpuConfig->MicrocodePatchAddress == 0)
      DEBUG((DEBUG_INFO, "Microcode update not available in FSP_TEMP_RAM_INIT_PARAMS region.\n"));
  }

  if (CpuConfig->MicrocodePatchAddress != 0) {
    DEBUG((DEBUG_INFO, "Microcode update found at 0x%x\n", CpuConfig->MicrocodePatchAddress));

    PcdSetEx64S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuMicrocodePatchAddress, MicrocodeRegionBase);
    PcdSetEx64S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuMicrocodePatchRegionSize, MicrocodeRegionSize);
  }

  CpuConfig->TxtEnable = FspsUpd->FspsConfig.TxtEnable;

  CpuConfig->AcSplitLock = FspsUpd->FspsConfig.AcSplitLock;

  ///
  ///Production RC Policies
  ///

  CpuConfig->AesEnable                 = FspsUpd->FspsConfig.AesEnable;
  CpuConfig->TxtEnable                 = FspsUpd->FspsConfig.TxtEnable;
  CpuConfig->SkipMpInit                = FspsUpd->FspsConfig.SkipMpInit;
  CpuConfig->PpinSupport               = FspsUpd->FspsConfig.PpinSupport;
  CpuConfig->UfsStrapAddress           = FspsUpd->FspsConfig.UfsStrapAddress;

  CpuPowerMgmtBasicConfig->TurboMode   = FspsUpd->FspsConfig.TurboMode;

  for (Index = 0; Index < MAX_NUM_VRS; Index++) {
      CpuPowerMgmtVrConfig->Psi3Enable[Index]      = FspsUpd->FspsConfig.Psi3Enable[Index];
      CpuPowerMgmtVrConfig->Psi4Enable[Index]      = FspsUpd->FspsConfig.Psi4Enable[Index];
      CpuPowerMgmtVrConfig->ImonSlope[Index]       = FspsUpd->FspsConfig.ImonSlope[Index];
      CpuPowerMgmtVrConfig->ImonOffset[Index]      = FspsUpd->FspsConfig.ImonOffset[Index];
      CpuPowerMgmtVrConfig->VrConfigEnable[Index]  = FspsUpd->FspsConfig.VrConfigEnable[Index];
      CpuPowerMgmtVrConfig->TdcEnable[Index]       = FspsUpd->FspsConfig.TdcEnable[Index];
      CpuPowerMgmtVrConfig->TdcTimeWindow[Index]   = FspsUpd->FspsConfig.TdcTimeWindow[Index];
      CpuPowerMgmtVrConfig->TdcLock[Index]         = FspsUpd->FspsConfig.TdcLock[Index];
      CpuPowerMgmtVrConfig->TdcCurrentLimit[Index] = FspsUpd->FspsConfig.TdcCurrentLimit[Index];
      CpuPowerMgmtVrConfig->AcLoadline[Index]      = FspsUpd->FspsConfig.AcLoadline[Index];
      CpuPowerMgmtVrConfig->DcLoadline[Index]      = FspsUpd->FspsConfig.DcLoadline[Index];
      CpuPowerMgmtVrConfig->Psi1Threshold[Index]   = FspsUpd->FspsConfig.Psi1Threshold[Index];
      CpuPowerMgmtVrConfig->Psi2Threshold[Index]   = FspsUpd->FspsConfig.Psi2Threshold[Index];
      CpuPowerMgmtVrConfig->Psi3Threshold[Index]   = FspsUpd->FspsConfig.Psi3Threshold[Index];
      CpuPowerMgmtVrConfig->IccMax[Index]          = FspsUpd->FspsConfig.IccMax[Index];
      CpuPowerMgmtVrConfig->VrVoltageLimit[Index]  = FspsUpd->FspsConfig.VrVoltageLimit[Index];
  }

  CpuPowerMgmtVrConfig->PsysSlope                  = FspsUpd->FspsConfig.PsysSlope;
  CpuPowerMgmtVrConfig->PsysOffset                 = FspsUpd->FspsConfig.PsysOffset;
  CpuPowerMgmtVrConfig->AcousticNoiseMitigation    = FspsUpd->FspsConfig.AcousticNoiseMitigation;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableIa      = FspsUpd->FspsConfig.FastPkgCRampDisableIa;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableGt      = FspsUpd->FspsConfig.FastPkgCRampDisableGt;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableSa      = FspsUpd->FspsConfig.FastPkgCRampDisableSa;
  CpuPowerMgmtVrConfig->FastPkgCRampDisableFivr    = FspsUpd->FspsConfig.FastPkgCRampDisableFivr;
  CpuPowerMgmtVrConfig->SlowSlewRateForIa          = FspsUpd->FspsConfig.SlowSlewRateForIa;
  CpuPowerMgmtVrConfig->SlowSlewRateForGt          = FspsUpd->FspsConfig.SlowSlewRateForGt;
  CpuPowerMgmtVrConfig->SlowSlewRateForSa          = FspsUpd->FspsConfig.SlowSlewRateForSa;
  CpuPowerMgmtVrConfig->SlowSlewRateForFivr        = FspsUpd->FspsConfig.SlowSlewRateForFivr;
  CpuPowerMgmtVrConfig->SendVrMbxCmd               = FspsUpd->FspsConfig.SendVrMbxCmd;
  CpuPowerMgmtVrConfig->FivrRfiFrequency           = FspsUpd->FspsConfig.FivrRfiFrequency;
  CpuPowerMgmtVrConfig->FivrSpreadSpectrum         = FspsUpd->FspsConfig.FivrSpreadSpectrum;
  CpuPowerMgmtVrConfig->EnableMinVoltageOverride   = FspsUpd->FspsConfig.EnableMinVoltageOverride;
  CpuPowerMgmtVrConfig->MinVoltageC8               = FspsUpd->FspsConfig.MinVoltageC8;
  CpuPowerMgmtVrConfig->MinVoltageRuntime          = FspsUpd->FspsConfig.MinVoltageRuntime;

  ///
  ///Test RC Policies
  ///
  CpuTestConfig->MlcStreamerPrefetcher      = FspsUpd->FspsConfig.MlcStreamerPrefetcher;
  CpuTestConfig->MlcSpatialPrefetcher       = FspsUpd->FspsConfig.MlcSpatialPrefetcher;
  CpuTestConfig->MonitorMwaitEnable         = FspsUpd->FspsConfig.MonitorMwaitEnable;
  CpuTestConfig->ProcessorTraceOutputScheme = FspsUpd->FspsConfig.ProcessorTraceOutputScheme;
  CpuTestConfig->ProcessorTraceEnable       = FspsUpd->FspsConfig.ProcessorTraceEnable;
  CpuTestConfig->ProcessorTraceMemBase      = FspsUpd->FspsConfig.ProcessorTraceMemBase;
  CpuTestConfig->ProcessorTraceMemLength    = FspsUpd->FspsConfig.ProcessorTraceMemLength;
  CpuTestConfig->VoltageOptimization        = FspsUpd->FspsConfig.VoltageOptimization;
  CpuTestConfig->ThreeStrikeCounterDisable  = FspsUpd->FspsConfig.ThreeStrikeCounterDisable;
  CpuTestConfig->MachineCheckEnable         = FspsUpd->FspsConfig.MachineCheckEnable;
  CpuTestConfig->IsFusaSupported            = FspsUpd->FspsConfig.IsFusaSupported;

  PcdSetEx8S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuApLoopMode, FspsUpd->FspsConfig.ApIdleManner);

  CpuPowerMgmtBasicConfig->OneCoreRatioLimit          = FspsUpd->FspsConfig.OneCoreRatioLimit;
  CpuPowerMgmtBasicConfig->TwoCoreRatioLimit          = FspsUpd->FspsConfig.TwoCoreRatioLimit;
  CpuPowerMgmtBasicConfig->ThreeCoreRatioLimit        = FspsUpd->FspsConfig.ThreeCoreRatioLimit;
  CpuPowerMgmtBasicConfig->FourCoreRatioLimit         = FspsUpd->FspsConfig.FourCoreRatioLimit;
  CpuPowerMgmtBasicConfig->FiveCoreRatioLimit         = FspsUpd->FspsConfig.FiveCoreRatioLimit;
  CpuPowerMgmtBasicConfig->SixCoreRatioLimit          = FspsUpd->FspsConfig.SixCoreRatioLimit;
  CpuPowerMgmtBasicConfig->SevenCoreRatioLimit        = FspsUpd->FspsConfig.SevenCoreRatioLimit;
  CpuPowerMgmtBasicConfig->EightCoreRatioLimit        = FspsUpd->FspsConfig.EightCoreRatioLimit;
  CpuPowerMgmtBasicConfig->Hwp                        = FspsUpd->FspsConfig.Hwp;
  CpuPowerMgmtBasicConfig->HdcControl                 = FspsUpd->FspsConfig.HdcControl;
  CpuPowerMgmtBasicConfig->PowerLimit1Time            = FspsUpd->FspsConfig.PowerLimit1Time;
  CpuPowerMgmtBasicConfig->PowerLimit2                = FspsUpd->FspsConfig.PowerLimit2;
  CpuPowerMgmtBasicConfig->TurboPowerLimitLock        = FspsUpd->FspsConfig.TurboPowerLimitLock;
  CpuPowerMgmtBasicConfig->PowerLimit3Time            = FspsUpd->FspsConfig.PowerLimit3Time;
  CpuPowerMgmtBasicConfig->PowerLimit3DutyCycle       = FspsUpd->FspsConfig.PowerLimit3DutyCycle;
  CpuPowerMgmtBasicConfig->PowerLimit3Lock            = FspsUpd->FspsConfig.PowerLimit3Lock;
  CpuPowerMgmtBasicConfig->PowerLimit4Lock            = FspsUpd->FspsConfig.PowerLimit4Lock;
  CpuPowerMgmtBasicConfig->TccActivationOffset        = FspsUpd->FspsConfig.TccActivationOffset;
  CpuPowerMgmtBasicConfig->TccOffsetClamp             = FspsUpd->FspsConfig.TccOffsetClamp;
  CpuPowerMgmtBasicConfig->TccOffsetLock              = FspsUpd->FspsConfig.TccOffsetLock;
  CpuPowerMgmtBasicConfig->PowerLimit1                = (UINT16) (FspsUpd->FspsConfig.PowerLimit1);
  CpuPowerMgmtBasicConfig->PowerLimit2Power           = (UINT16) (FspsUpd->FspsConfig.PowerLimit2Power);
  CpuPowerMgmtBasicConfig->PowerLimit3                = (UINT16) (FspsUpd->FspsConfig.PowerLimit3);
  CpuPowerMgmtBasicConfig->PowerLimit4                = (UINT16) (FspsUpd->FspsConfig.PowerLimit4);
  CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl = FspsUpd->FspsConfig.TccOffsetTimeWindowForRatl;
  CpuPowerMgmtBasicConfig->HwpInterruptControl        = FspsUpd->FspsConfig.HwpInterruptControl;
  CpuPowerMgmtBasicConfig->EnableItbm                 = FspsUpd->FspsConfig.EnableItbm;
  CpuPowerMgmtBasicConfig->EnableItbmDriver           = FspsUpd->FspsConfig.EnableItbmDriver;

  CpuPowerMgmtBasicConfig->EnablePerCorePState        = FspsUpd->FspsConfig.EnablePerCorePState;
  CpuPowerMgmtBasicConfig->EnableHwpAutoPerCorePstate = FspsUpd->FspsConfig.EnableHwpAutoPerCorePstate;
  CpuPowerMgmtBasicConfig->EnableHwpAutoEppGrouping   = FspsUpd->FspsConfig.EnableHwpAutoEppGrouping;
  CpuPowerMgmtBasicConfig->EnableEpbPeciOverride      = FspsUpd->FspsConfig.EnableEpbPeciOverride;
  CpuPowerMgmtBasicConfig->EnableFastMsrHwpReq        = FspsUpd->FspsConfig.EnableFastMsrHwpReq;
  CpuPowerMgmtBasicConfig->MinRingRatioLimit          = FspsUpd->FspsConfig.MinRingRatioLimit;
  CpuPowerMgmtBasicConfig->MaxRingRatioLimit          = FspsUpd->FspsConfig.MaxRingRatioLimit;

  CpuPowerMgmtCustomConfig->CustomRatioTable.NumberOfEntries                                      = FspsUpd->FspsConfig.NumberOfEntries;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1Time      = FspsUpd->FspsConfig.Custom1PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1Time      = FspsUpd->FspsConfig.Custom2PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1Time      = FspsUpd->FspsConfig.Custom3PowerLimit1Time;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomTurboActivationRatio = FspsUpd->FspsConfig.Custom1TurboActivationRatio;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomTurboActivationRatio = FspsUpd->FspsConfig.Custom2TurboActivationRatio;
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomTurboActivationRatio = FspsUpd->FspsConfig.Custom3TurboActivationRatio;
  CpuPowerMgmtCustomConfig->ConfigTdpLock                                                         = FspsUpd->FspsConfig.ConfigTdpLock;
  CpuPowerMgmtCustomConfig->ConfigTdpBios                                                         = FspsUpd->FspsConfig.ConfigTdpBios;
  CpuPowerMgmtCustomConfig->CustomRatioTable.MaxRatio                                             = FspsUpd->FspsConfig.MaxRatio;
  for (Index = 0; Index < CpuPowerMgmtCustomConfig->CustomRatioTable.NumberOfEntries; Index++) {
      CpuPowerMgmtCustomConfig->CustomRatioTable.StateRatio[Index]                                = FspsUpd->FspsConfig.StateRatio[Index];
  }
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsConfig.Custom1PowerLimit1);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsConfig.Custom1PowerLimit2);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsConfig.Custom2PowerLimit1);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsConfig.Custom2PowerLimit2);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1          = (UINT16) (FspsUpd->FspsConfig.Custom3PowerLimit1);
  CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit2          = (UINT16) (FspsUpd->FspsConfig.Custom3PowerLimit2);

  CpuPowerMgmtPsysConfig->PsysPowerLimit1      = FspsUpd->FspsConfig.PsysPowerLimit1;
  CpuPowerMgmtPsysConfig->PsysPowerLimit1Time  = FspsUpd->FspsConfig.PsysPowerLimit1Time;
  CpuPowerMgmtPsysConfig->PsysPowerLimit2      = FspsUpd->FspsConfig.PsysPowerLimit2;
  CpuPowerMgmtPsysConfig->PsysPmax             = FspsUpd->FspsConfig.PsysPmax;
  CpuPowerMgmtPsysConfig->PsysPowerLimit1Power = (UINT16) (FspsUpd->FspsConfig.PsysPowerLimit1Power);
  CpuPowerMgmtPsysConfig->PsysPowerLimit2Power = (UINT16) (FspsUpd->FspsConfig.PsysPowerLimit2Power);

  CpuPowerMgmtTestConfig->Eist                          = FspsUpd->FspsConfig.Eist;
  CpuPowerMgmtTestConfig->EnergyEfficientPState         = FspsUpd->FspsConfig.EnergyEfficientPState;
  CpuPowerMgmtTestConfig->EnergyEfficientTurbo          = FspsUpd->FspsConfig.EnergyEfficientTurbo;
  CpuPowerMgmtTestConfig->TStates                       = FspsUpd->FspsConfig.TStates;
  CpuPowerMgmtTestConfig->BiProcHot                     = FspsUpd->FspsConfig.BiProcHot;
  CpuPowerMgmtTestConfig->DisableProcHotOut             = FspsUpd->FspsConfig.DisableProcHotOut;
  CpuPowerMgmtTestConfig->ProcHotResponse               = FspsUpd->FspsConfig.ProcHotResponse;
  CpuPowerMgmtTestConfig->DisableVrThermalAlert         = FspsUpd->FspsConfig.DisableVrThermalAlert;
  CpuPowerMgmtTestConfig->EnableAllThermalFunctions     = FspsUpd->FspsConfig.EnableAllThermalFunctions;
  CpuPowerMgmtTestConfig->ThermalMonitor                = FspsUpd->FspsConfig.ThermalMonitor;
  CpuPowerMgmtTestConfig->Cx                            = FspsUpd->FspsConfig.Cx;
  CpuPowerMgmtTestConfig->PmgCstCfgCtrlLock             = FspsUpd->FspsConfig.PmgCstCfgCtrlLock;
  CpuPowerMgmtTestConfig->C1e                           = FspsUpd->FspsConfig.C1e;
  CpuPowerMgmtTestConfig->C1AutoDemotion                = FspsUpd->FspsConfig.C1StateAutoDemotion;
  CpuPowerMgmtTestConfig->C1UnDemotion                  = FspsUpd->FspsConfig.C1StateUnDemotion;
  CpuPowerMgmtTestConfig->PkgCStateDemotion             = FspsUpd->FspsConfig.PkgCStateDemotion;
  CpuPowerMgmtTestConfig->PkgCStateUnDemotion           = FspsUpd->FspsConfig.PkgCStateUnDemotion;
  CpuPowerMgmtTestConfig->CStatePreWake                 = FspsUpd->FspsConfig.CStatePreWake;
  CpuPowerMgmtTestConfig->TimedMwait                    = FspsUpd->FspsConfig.TimedMwait;
  CpuPowerMgmtTestConfig->CstCfgCtrIoMwaitRedirection   = FspsUpd->FspsConfig.CstCfgCtrIoMwaitRedirection;
  CpuPowerMgmtTestConfig->PkgCStateLimit                = FspsUpd->FspsConfig.PkgCStateLimit;
  CpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit = FspsUpd->FspsConfig.CstateLatencyControl1TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit = FspsUpd->FspsConfig.CstateLatencyControl2TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit = FspsUpd->FspsConfig.CstateLatencyControl3TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit = FspsUpd->FspsConfig.CstateLatencyControl4TimeUnit;
  CpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit = FspsUpd->FspsConfig.CstateLatencyControl5TimeUnit;
  CpuPowerMgmtTestConfig->PpmIrmSetting                 = FspsUpd->FspsConfig.PpmIrmSetting;
  CpuPowerMgmtTestConfig->ProcHotLock                   = FspsUpd->FspsConfig.ProcHotLock;
  CpuPowerMgmtTestConfig->RaceToHalt                    = FspsUpd->FspsConfig.RaceToHalt;
  CpuPowerMgmtTestConfig->ConfigTdpLevel                = FspsUpd->FspsConfig.ConfigTdpLevel;
  CpuPowerMgmtTestConfig->CstateLatencyControl1Irtl     = FspsUpd->FspsConfig.CstateLatencyControl1Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl2Irtl     = FspsUpd->FspsConfig.CstateLatencyControl2Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl3Irtl     = FspsUpd->FspsConfig.CstateLatencyControl3Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl4Irtl     = FspsUpd->FspsConfig.CstateLatencyControl4Irtl;
  CpuPowerMgmtTestConfig->CstateLatencyControl5Irtl     = FspsUpd->FspsConfig.CstateLatencyControl5Irtl;

  return EFI_SUCCESS;
}

