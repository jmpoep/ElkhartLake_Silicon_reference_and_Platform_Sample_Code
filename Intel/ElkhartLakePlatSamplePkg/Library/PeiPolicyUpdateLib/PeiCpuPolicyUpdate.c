/** @file
  CPU PEI Policy Update & initialization.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/
#include <Library/PeiCpuPolicyUpdate.h>
#include <Library/SiPolicyLib.h>
#include <Library/Tpm2CommandLib.h>
#include <Library/Tpm12CommandLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/HobLib.h>
#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <Library/BpdtLib.h>
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#include <Library/FspCommonLib.h>
#endif
#include <Library/CpuPolicyLib.h>
#include <Ppi/SecPlatformInformation2.h>

/**
  Update Cpu Power Management Policy settings according to the related BIOS Setup options

  @param[in] SetupData             The Setup variables instance
  @param[in] CpuSetup              The Setup variables instance

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
InitCpuPmConfigBySetupValues (
  IN SETUP_DATA                    *SetupData,
  IN CPU_SETUP                     *CpuSetup
  )
{
  UINT8                            Index;
  UINT8                            MaxRatio;
  UINT8                            MinRatio;
  EFI_STATUS                       Status;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                             *FspsUpd;
#else
  SI_POLICY_PPI                    *SiPolicyPpi;
  CPU_POWER_MGMT_BASIC_CONFIG      *CpuPowerMgmtBasicConfig;
  CPU_POWER_MGMT_VR_CONFIG         *CpuPowerMgmtVrConfig;
  CPU_POWER_MGMT_CUSTOM_CONFIG     *CpuPowerMgmtCustomConfig;
  CPU_POWER_MGMT_PSYS_CONFIG       *CpuPowerMgmtPsysConfig;
#endif

  Status = EFI_SUCCESS;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
#else
  SiPolicyPpi = NULL;
  CpuPowerMgmtBasicConfig = NULL;
  CpuPowerMgmtVrConfig = NULL;
  CpuPowerMgmtCustomConfig = NULL;
  CpuPowerMgmtPsysConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtVrConfigGuid, (VOID *) &CpuPowerMgmtVrConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtCustomConfigGuid, (VOID *) &CpuPowerMgmtCustomConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtPsysConfigGuid, (VOID *) &CpuPowerMgmtPsysConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Get Maximum Efficiency ratio(Minimum Ratio) from Platform Info MSR Bits[47:40]
  //
  MinRatio  = (UINT8) ((AsmReadMsr64 (MSR_PLATFORM_INFO) >> 40) & 0xFF);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TurboMode,         CpuPowerMgmtBasicConfig->TurboMode,      CpuSetup->TurboMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit2,   CpuPowerMgmtBasicConfig->PowerLimit2,    CpuSetup->PowerLimit2);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ConfigTdpLock, CpuPowerMgmtCustomConfig->ConfigTdpLock, CpuSetup->ConfigTdpLock);
  if (CpuSetup->ConfigTdpLock == 1 || SetupData->EnableDptf == 1) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ConfigTdpBios, CpuPowerMgmtCustomConfig->ConfigTdpBios, 0);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ConfigTdpBios, CpuPowerMgmtCustomConfig->ConfigTdpBios, CpuSetup->ConfigTdpBios);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom1PowerLimit1,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1,          (UINT16) (CpuSetup->Custom1PowerLimit1Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom1PowerLimit2,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit2,          (UINT16) (CpuSetup->Custom1PowerLimit2Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom1PowerLimit1Time,      CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomPowerLimit1Time,      CpuSetup->Custom1PowerLimit1Time);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom1TurboActivationRatio, CpuPowerMgmtCustomConfig->CustomConfigTdpTable[0].CustomTurboActivationRatio, CpuSetup->Custom1TurboActivationRatio);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom2PowerLimit1,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1,          (UINT16) (CpuSetup->Custom2PowerLimit1Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom2PowerLimit2,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit2,          (UINT16) (CpuSetup->Custom2PowerLimit2Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom2PowerLimit1Time,      CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomPowerLimit1Time,      CpuSetup->Custom2PowerLimit1Time);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom2TurboActivationRatio, CpuPowerMgmtCustomConfig->CustomConfigTdpTable[1].CustomTurboActivationRatio, CpuSetup->Custom2TurboActivationRatio);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom3PowerLimit1,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1,          (UINT16) (CpuSetup->Custom3PowerLimit1Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom3PowerLimit2,          CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit2,          (UINT16) (CpuSetup->Custom3PowerLimit2Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom3PowerLimit1Time,      CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomPowerLimit1Time,      CpuSetup->Custom3PowerLimit1Time);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Custom3TurboActivationRatio, CpuPowerMgmtCustomConfig->CustomConfigTdpTable[2].CustomTurboActivationRatio, CpuSetup->Custom3TurboActivationRatio);

  //
  // Turbo Mode setting
  //
  if (CpuSetup->LongDurationPwrLimitOverride) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit1,     CpuPowerMgmtBasicConfig->PowerLimit1,     (UINT16) (CpuSetup->PowerLimit1 / 125));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit1Time, CpuPowerMgmtBasicConfig->PowerLimit1Time, CpuSetup->PowerLimit1Time);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit2Power,    CpuPowerMgmtBasicConfig->PowerLimit2Power,    (UINT16) (CpuSetup->PowerLimit2Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TurboPowerLimitLock, CpuPowerMgmtBasicConfig->TurboPowerLimitLock, CpuSetup->TurboPowerLimitLock);

  if (CpuSetup->PowerLimit3Override) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit3,          CpuPowerMgmtBasicConfig->PowerLimit3,          (UINT16) (CpuSetup->PowerLimit3 / 125));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit3Time,      CpuPowerMgmtBasicConfig->PowerLimit3Time,      CpuSetup->PowerLimit3Time);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit3DutyCycle, CpuPowerMgmtBasicConfig->PowerLimit3DutyCycle, CpuSetup->PowerLimit3DutyCycle);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit3Lock,      CpuPowerMgmtBasicConfig->PowerLimit3Lock,      CpuSetup->PowerLimit3Lock);
  }

  if (CpuSetup->PowerLimit4Override) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit4,     CpuPowerMgmtBasicConfig->PowerLimit4,     (UINT16) (CpuSetup->PowerLimit4 / 125));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PowerLimit4Lock, CpuPowerMgmtBasicConfig->PowerLimit4Lock, CpuSetup->PowerLimit4Lock);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPowerLimit1, CpuPowerMgmtPsysConfig->PsysPowerLimit1, CpuSetup->PlatformPowerLimit1Enable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPowerLimit2, CpuPowerMgmtPsysConfig->PsysPowerLimit2, CpuSetup->PlatformPowerLimit2Enable);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPowerLimit1Power, CpuPowerMgmtPsysConfig->PsysPowerLimit1Power, (UINT16) (CpuSetup->PlatformPowerLimit1Power / 125));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPowerLimit1Time , CpuPowerMgmtPsysConfig->PsysPowerLimit1Time , CpuSetup->PlatformPowerLimit1Time);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPowerLimit2Power, CpuPowerMgmtPsysConfig->PsysPowerLimit2Power, (UINT16) (CpuSetup->PlatformPowerLimit2Power / 125));

  //
  // Customize HDC
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.HdcControl, CpuPowerMgmtBasicConfig->HdcControl, CpuSetup->HdcControl);

  //
  // Thermal Function Enables / Configuration
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Hwp,                 CpuPowerMgmtBasicConfig->Hwp,                 CpuSetup->EnableHwp);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.HwpInterruptControl, CpuPowerMgmtBasicConfig->HwpInterruptControl, CpuSetup->HwpInterruptControl);

  //
  // Intel Turbo Boost Max Technology 3.0
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableItbm,       CpuPowerMgmtBasicConfig->EnableItbm,       CpuSetup->EnableItbm);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableItbmDriver, CpuPowerMgmtBasicConfig->EnableItbmDriver, CpuSetup->EnableItbmDriver);

  //
  // HwP Misc Functions
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnablePerCorePState,        CpuPowerMgmtBasicConfig->EnablePerCorePState, CpuSetup->EnablePerCorePState);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableHwpAutoPerCorePstate, CpuPowerMgmtBasicConfig->EnableHwpAutoPerCorePstate, CpuSetup->EnableHwpAutoPerCorePstate);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableHwpAutoEppGrouping,   CpuPowerMgmtBasicConfig->EnableHwpAutoEppGrouping, CpuSetup->EnableHwpAutoEppGrouping);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableEpbPeciOverride,      CpuPowerMgmtBasicConfig->EnableEpbPeciOverride, CpuSetup->EnableEpbPeciOverride);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableFastMsrHwpReq,        CpuPowerMgmtBasicConfig->EnableFastMsrHwpReq, CpuSetup->EnableFastMsrHwpReq);


  //
  // Custom VID table
  //
  if (CpuSetup->StateRatio[0] < MinRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MaxRatio, CpuPowerMgmtCustomConfig->CustomRatioTable.MaxRatio, MinRatio);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MaxRatio, CpuPowerMgmtCustomConfig->CustomRatioTable.MaxRatio, CpuSetup->StateRatio[0]);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.NumberOfEntries, CpuPowerMgmtCustomConfig->CustomRatioTable.NumberOfEntries, CpuSetup->NumOfCustomPStates);

  for (Index = 0; Index < CpuSetup->NumOfCustomPStates; Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.StateRatio[Index], CpuPowerMgmtCustomConfig->CustomRatioTable.StateRatio[Index], CpuSetup->StateRatio[Index]);
  }

  if (CpuSetup->NumOfCustomPStates > MAX_16_CUSTOM_RATIO_TABLE_ENTRIES) {
    for (Index = 0; Index < MAX_16_CUSTOM_RATIO_TABLE_ENTRIES; Index++) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.StateRatioMax16[Index], CpuPowerMgmtCustomConfig->CustomRatioTable.StateRatioMax16[Index], CpuSetup->StateRatioMax16[Index]);
    }
  }

  //
  // Update Turbo Ratio limit override table
  //
  MaxRatio  = (UINT8) ((AsmReadMsr64 (MSR_PLATFORM_INFO) >> 8) & 0xFF);

  if (CpuSetup->RatioLimit1 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.OneCoreRatioLimit,   CpuPowerMgmtBasicConfig->OneCoreRatioLimit,   CpuSetup->RatioLimit1);
  }
  if (CpuSetup->RatioLimit2 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TwoCoreRatioLimit,   CpuPowerMgmtBasicConfig->TwoCoreRatioLimit,   CpuSetup->RatioLimit2);
  }
  if (CpuSetup->RatioLimit3 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThreeCoreRatioLimit, CpuPowerMgmtBasicConfig->ThreeCoreRatioLimit, CpuSetup->RatioLimit3);
  }
  if (CpuSetup->RatioLimit4 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FourCoreRatioLimit,  CpuPowerMgmtBasicConfig->FourCoreRatioLimit,  CpuSetup->RatioLimit4);
  }
  if (CpuSetup->RatioLimit5 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FiveCoreRatioLimit,  CpuPowerMgmtBasicConfig->FiveCoreRatioLimit,  CpuSetup->RatioLimit5);
  }
  if (CpuSetup->RatioLimit6 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SixCoreRatioLimit,   CpuPowerMgmtBasicConfig->SixCoreRatioLimit,   CpuSetup->RatioLimit6);
  }
  if (CpuSetup->RatioLimit7 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SevenCoreRatioLimit, CpuPowerMgmtBasicConfig->SevenCoreRatioLimit, CpuSetup->RatioLimit7);
  }
  if (CpuSetup->RatioLimit8 >= MaxRatio) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EightCoreRatioLimit, CpuPowerMgmtBasicConfig->EightCoreRatioLimit, CpuSetup->RatioLimit8);
  }

  //
  // Update Ring Ratio limits
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MinRingRatioLimit,   CpuPowerMgmtBasicConfig->MinRingRatioLimit,    CpuSetup->MinRingRatioLimit);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MaxRingRatioLimit,   CpuPowerMgmtBasicConfig->MaxRingRatioLimit,    CpuSetup->MaxRingRatioLimit);

  //
  // VR Configuration
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysSlope,               CpuPowerMgmtVrConfig->PsysSlope,               CpuSetup->PsysSlope);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysOffset,              CpuPowerMgmtVrConfig->PsysOffset,              CpuSetup->PsysOffset);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsysPmax,            CpuPowerMgmtPsysConfig->PsysPmax,              CpuSetup->PsysPmax);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FivrRfiFrequency,        CpuPowerMgmtVrConfig->FivrRfiFrequency,        CpuSetup->FivrRfiFrequency);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FivrSpreadSpectrum,      CpuPowerMgmtVrConfig->FivrSpreadSpectrum,      CpuSetup->FivrSpreadSpectrum);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableMinVoltageOverride,CpuPowerMgmtVrConfig->EnableMinVoltageOverride,CpuSetup->EnableMinVoltageOverride);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MinVoltageRuntime,       CpuPowerMgmtVrConfig->MinVoltageRuntime,       CpuSetup->MinVoltageRuntime);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MinVoltageC8,            CpuPowerMgmtVrConfig->MinVoltageC8,            CpuSetup->MinVoltageC8);

  for (Index = 0; Index < MAX_NUM_VRS; Index++) {
    //
    // Only update if the user wants to override VR settings
    //
    if (CpuSetup->VrConfigEnable[Index] != 0) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.VrConfigEnable[Index], CpuPowerMgmtVrConfig->VrConfigEnable[Index], CpuSetup->VrConfigEnable[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Psi1Threshold[Index],  CpuPowerMgmtVrConfig->Psi1Threshold[Index],  CpuSetup->Psi1Threshold[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Psi2Threshold[Index],  CpuPowerMgmtVrConfig->Psi2Threshold[Index],  CpuSetup->Psi2Threshold[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Psi3Threshold[Index],  CpuPowerMgmtVrConfig->Psi3Threshold[Index],  CpuSetup->Psi3Threshold[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Psi3Enable[Index],     CpuPowerMgmtVrConfig->Psi3Enable[Index],     CpuSetup->Psi3Enable[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Psi4Enable[Index],     CpuPowerMgmtVrConfig->Psi4Enable[Index],     CpuSetup->Psi4Enable[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ImonSlope[Index],      CpuPowerMgmtVrConfig->ImonSlope[Index],      (UINT8) CpuSetup->ImonSlope[Index]);
      if (CpuSetup->ImonOffsetPrefix[Index] == 1) {
        //
        // Number is negative, need to convert to 2's complement representation
        //
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ImonOffset[Index], CpuPowerMgmtVrConfig->ImonOffset[Index], (~CpuSetup->ImonOffset[Index] + 1));
      } else {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ImonOffset[Index], CpuPowerMgmtVrConfig->ImonOffset[Index], (CpuSetup->ImonOffset[Index]));
      }
      //
      // Only update if IccMax is non-zero. This is to distinguish between the default EDS override.
      //
      if (CpuSetup->IccMax[Index] != 0) {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.IccMax[Index], CpuPowerMgmtVrConfig->IccMax[Index], CpuSetup->IccMax[Index]);
      }
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.VrVoltageLimit[Index], CpuPowerMgmtVrConfig->VrVoltageLimit[Index], CpuSetup->VrVoltageLimit[Index]);
      //
      // Only update TDC if current limit is non-zero. TDC Lock should be separated to allow
      // locking of TDC feature.
      //
      if (CpuSetup->TdcCurrentLimit[Index] != 0) {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TdcCurrentLimit[Index], CpuPowerMgmtVrConfig->TdcCurrentLimit[Index], CpuSetup->TdcCurrentLimit[Index]);
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TdcTimeWindow[Index], CpuPowerMgmtVrConfig->TdcTimeWindow[Index], CpuSetup->TdcTimeWindow[Index]);
      }
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TdcEnable[Index], CpuPowerMgmtVrConfig->TdcEnable[Index], CpuSetup->TdcEnable[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TdcLock[Index],   CpuPowerMgmtVrConfig->TdcLock[Index],   CpuSetup->TdcLock[Index]);
    }
    // Need to check if the user intends to override through CpuSetup to distinguish
    // between the default EDS override.
    if (CpuSetup->AcLoadline[Index] != 0) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AcLoadline[Index], CpuPowerMgmtVrConfig->AcLoadline[Index], CpuSetup->AcLoadline[Index]);
    }
    if (CpuSetup->DcLoadline[Index] != 0) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DcLoadline[Index], CpuPowerMgmtVrConfig->DcLoadline[Index], CpuSetup->DcLoadline[Index]);
    }
  }

  //
  // VR Acoustic Noise Mitigation
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AcousticNoiseMitigation, CpuPowerMgmtVrConfig->AcousticNoiseMitigation, CpuSetup->AcousticNoiseMitigation);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FastPkgCRampDisableIa,   CpuPowerMgmtVrConfig->FastPkgCRampDisableIa,   CpuSetup->FastPkgCRampDisableIa);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FastPkgCRampDisableGt,   CpuPowerMgmtVrConfig->FastPkgCRampDisableGt,   CpuSetup->FastPkgCRampDisableGt);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FastPkgCRampDisableSa,   CpuPowerMgmtVrConfig->FastPkgCRampDisableSa,   CpuSetup->FastPkgCRampDisableSa);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FastPkgCRampDisableFivr, CpuPowerMgmtVrConfig->FastPkgCRampDisableFivr, CpuSetup->FastPkgCRampDisableFivr);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SlowSlewRateForIa,       CpuPowerMgmtVrConfig->SlowSlewRateForIa,       CpuSetup->SlowSlewRateForIa);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SlowSlewRateForGt,       CpuPowerMgmtVrConfig->SlowSlewRateForGt,       CpuSetup->SlowSlewRateForGt);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SlowSlewRateForSa,       CpuPowerMgmtVrConfig->SlowSlewRateForSa,       CpuSetup->SlowSlewRateForSa);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SlowSlewRateForFivr,     CpuPowerMgmtVrConfig->SlowSlewRateForFivr,     CpuSetup->SlowSlewRateForFivr);

  return EFI_SUCCESS;
}

#if FixedPcdGet8(PcdFspModeSelection) == 1
/**
  This routine is used to get Sec Platform Information Record2 Pointer.

  @param[in] PeiServices    Pointer to the PEI services table

  @retval GetSecPlatformInformation2 - The pointer of Sec Platform Information Record2 Pointer.
**/
EFI_SEC_PLATFORM_INFORMATION_RECORD2 *
GetSecPlatformInformation2 (
  IN EFI_PEI_SERVICES **PeiServices
  )
{
  EFI_SEC_PLATFORM_INFORMATION2_PPI    *SecPlatformInformation2Ppi;
  EFI_SEC_PLATFORM_INFORMATION_RECORD2 *SecPlatformInformation2 = NULL;
  UINT64                               InformationSize;
  EFI_STATUS Status;

  //
  // Get BIST information from Sec Platform Information2 Ppi firstly
  //
  Status = PeiServicesLocatePpi (
             &gEfiSecPlatformInformation2PpiGuid,   // GUID
             0,                                     // Instance
             NULL,                                  // EFI_PEI_PPI_DESCRIPTOR
             (VOID ** ) &SecPlatformInformation2Ppi // PPI
             );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "LocatePpi SecPlatformInformationPpi2 Status - %r\n", Status));
    return NULL;
  }

  InformationSize = 0;

  Status = SecPlatformInformation2Ppi->PlatformInformation2 (
                                         (CONST EFI_PEI_SERVICES **) PeiServices,
                                         &InformationSize,
                                         SecPlatformInformation2
                                         );

  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return NULL;
  }

  SecPlatformInformation2 = AllocatePool((UINTN)InformationSize);
  ASSERT (SecPlatformInformation2 != NULL);
  if (SecPlatformInformation2 == NULL) {
    return NULL;
  }

  //
  // Retrieve BIST data from SecPlatform2
  //
  Status = SecPlatformInformation2Ppi->PlatformInformation2 (
                                         PeiServices,
                                         &InformationSize,
                                         SecPlatformInformation2
                                         );
  DEBUG((DEBUG_INFO, "SecPlatformInformation2Ppi->PlatformInformation2 Status - %r\n", Status));
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  return SecPlatformInformation2;
}


/**
  This routine is used to get Sec Platform Information Record Pointer.

  @param[in] PeiServices    Pointer to the PEI services table

  @retval GetSecPlatformInformation2 - The pointer of Sec Platform Information Record Pointer.
**/
EFI_SEC_PLATFORM_INFORMATION_RECORD2 *
GetSecPlatformInformationInfoInFormat2 (
  IN EFI_PEI_SERVICES **PeiServices
  )
{
  EFI_SEC_PLATFORM_INFORMATION_PPI     *SecPlatformInformationPpi;
  EFI_SEC_PLATFORM_INFORMATION_RECORD  *SecPlatformInformation = NULL;
  EFI_SEC_PLATFORM_INFORMATION_RECORD2 *SecPlatformInformation2;
  UINT64                               InformationSize;
  EFI_STATUS                           Status;

  //
  // Get BIST information from Sec Platform Information
  //
  Status = PeiServicesLocatePpi (
             &gEfiSecPlatformInformationPpiGuid,    // GUID
             0,                                     // Instance
             NULL,                                  // EFI_PEI_PPI_DESCRIPTOR
             (VOID ** ) &SecPlatformInformationPpi  // PPI
             );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "LocatePpi SecPlatformInformationPpi Status - %r\n", Status));
    return NULL;
  }

  InformationSize = 0;
  Status = SecPlatformInformationPpi->PlatformInformation (
                                        (CONST EFI_PEI_SERVICES  **) PeiServices,
                                        &InformationSize,
                                        SecPlatformInformation
                                        );

  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return NULL;
  }

  SecPlatformInformation = AllocatePool((UINTN)InformationSize);
  ASSERT (SecPlatformInformation != NULL);
  if (SecPlatformInformation == NULL) {
    return NULL;
  }

  //
  // Retrieve BIST data from SecPlatform
  //
  Status = SecPlatformInformationPpi->PlatformInformation (
                                        PeiServices,
                                        &InformationSize,
                                        SecPlatformInformation
                                        );
  DEBUG((DEBUG_INFO, "FSP  SecPlatformInformation2Ppi->PlatformInformation Status - %r\n", Status));
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  SecPlatformInformation2 = AllocatePool(sizeof (EFI_SEC_PLATFORM_INFORMATION_RECORD2));
  ASSERT (SecPlatformInformation2 != NULL);
  if (SecPlatformInformation2 == NULL) {
    return NULL;
  }

  SecPlatformInformation2->NumberOfCpus = 1;
  SecPlatformInformation2->CpuInstance[0].CpuLocation = 0;
  SecPlatformInformation2->CpuInstance[0].InfoRecord.x64HealthFlags.Uint32 = SecPlatformInformation->x64HealthFlags.Uint32;

  FreePool(SecPlatformInformation);

  return SecPlatformInformation2;
}
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 0
/**
  Get the next microcode patch pointer.

  @param[in, out] MicrocodeData - Input is a pointer to the last microcode patch address found,
                                  and output points to the next patch address found.

  @retval EFI_SUCCESS           - Patch found.
  @retval EFI_NOT_FOUND         - Patch not found.
**/
EFI_STATUS
EFIAPI
RetrieveMicrocode (
  IN OUT CPU_MICROCODE_HEADER **MicrocodeData
  )
{
  UINTN                MicrocodeStart;
  UINTN                MicrocodeEnd;
  UINTN                TotalSize;

  if ((FixedPcdGet32 (PcdFlashMicrocodeFvBase) == 0) || (FixedPcdGet32 (PcdFlashMicrocodeFvSize) == 0)) {
    return EFI_NOT_FOUND;
  }

  ///
  /// Microcode binary in SEC
  ///
  MicrocodeStart = (UINTN) FixedPcdGet32 (PcdFlashMicrocodeFvBase) +
          ((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) FixedPcdGet32 (PcdFlashMicrocodeFvBase))->HeaderLength +
          sizeof (EFI_FFS_FILE_HEADER);

  MicrocodeEnd = (UINTN) FixedPcdGet32 (PcdFlashMicrocodeFvBase) + (UINTN) FixedPcdGet32 (PcdFlashMicrocodeFvSize);

  if (*MicrocodeData == NULL) {
    *MicrocodeData = (CPU_MICROCODE_HEADER *) (UINTN) MicrocodeStart;
  } else {
    if (*MicrocodeData < (CPU_MICROCODE_HEADER *) (UINTN) MicrocodeStart) {
      DEBUG ((DEBUG_INFO, "[CpuPolicy]*MicrocodeData < MicrocodeStart \n"));
      return EFI_NOT_FOUND;
    }

    TotalSize = (UINTN) ((*MicrocodeData)->TotalSize);
    if (TotalSize == 0) {
      TotalSize = 2048;
    }

    *MicrocodeData = (CPU_MICROCODE_HEADER *) ((UINTN)*MicrocodeData + TotalSize);
    if (*MicrocodeData >= (CPU_MICROCODE_HEADER *) (UINTN) (MicrocodeEnd) || (*MicrocodeData)->TotalSize == (UINT32) -1) {
      DEBUG ((DEBUG_INFO, "[CpuPolicy]*MicrocodeData >= MicrocodeEnd \n"));
      return EFI_NOT_FOUND;
    }
  }
  return EFI_SUCCESS;
}

/**
  Get the microcode patch pointer.

  @retval EFI_PHYSICAL_ADDRESS - Address of the microcode patch, or NULL if not found.
**/
EFI_PHYSICAL_ADDRESS
CpuLocateMicrocodePatch (
  OUT UINTN                *MicrocodeBufferSize
  )
{
  EFI_STATUS           Status;
  CPU_MICROCODE_HEADER *MicrocodeData;
  EFI_CPUID_REGISTER   Cpuid;
  UINT32               UcodeRevision;
  VOID                 *MicrocodeBuffer = NULL;

  AsmCpuid (
    CPUID_VERSION_INFO,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  UcodeRevision = GetCpuUcodeRevision ();
  MicrocodeData = NULL;

  while (TRUE) {
    ///
    /// Find the next patch address
    ///
    Status = RetrieveMicrocode (&MicrocodeData);
    DEBUG ((DEBUG_INFO, "MicrocodeData = %x\n", MicrocodeData));

    if (Status != EFI_SUCCESS) {
      break;
    } else if (CheckMicrocode (Cpuid.RegEax, MicrocodeData, &UcodeRevision)) {
      break;
    }
  }

  if (EFI_ERROR (Status)) {
    return (EFI_PHYSICAL_ADDRESS) (UINTN) NULL;
  }

  ///
  /// Check that microcode patch size is <= 128K max size,
  /// then copy the patch from FV to temp buffer for faster access.
  ///
  *MicrocodeBufferSize = (UINTN) MicrocodeData->TotalSize;

  if (*MicrocodeBufferSize <= MAX_MICROCODE_PATCH_SIZE) {
    MicrocodeBuffer = AllocatePages (EFI_SIZE_TO_PAGES (*MicrocodeBufferSize));
    if (MicrocodeBuffer != NULL) {
      DEBUG(( DEBUG_INFO, "Copying Microcode to temp buffer.\n"));
      CopyMem (MicrocodeBuffer, MicrocodeData, *MicrocodeBufferSize);

      return (EFI_PHYSICAL_ADDRESS) (UINTN) MicrocodeBuffer;
    } else {
      DEBUG(( DEBUG_ERROR, "Failed to allocate enough memory for Microcode Patch.\n"));
    }
  } else {
    DEBUG(( DEBUG_ERROR, "Microcode patch size is greater than max allowed size of 128K.\n"));
  }
  return (EFI_PHYSICAL_ADDRESS) (UINTN) NULL;
}
#endif

/**
  This function performs CPU PEI Policy initialization.

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
UpdatePeiCpuPolicy (
  VOID
  )
{
  EFI_STATUS                       Status;
  UINTN                            VariableSize;
  SETUP_DATA                       SetupData;
  CPU_SETUP                        CpuSetup;
  MSR_REGISTER                     TempMsr;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *VariableServices;
  SI_POLICY_PPI                    *SiPolicyPpi;
  CPU_SETUP_SGX_EPOCH_DATA         CpuSetupSgxEpochData;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                                 *FspsUpd;
  VOID                                 *FspmUpd;
  UINTN                                Index;
  CPU_POWER_MGMT_VR_CONFIG_EX          *CpuPowerMgmtVrConfigEx;
  EFI_SEC_PLATFORM_INFORMATION_RECORD2 *SecPlatformInformation2;
#else
  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi;
  CPU_CONFIG                       *CpuConfig;
  CPU_SGX_CONFIG                   *CpuSgxConfig;
  CPU_POWER_MGMT_BASIC_CONFIG      *CpuPowerMgmtBasicConfig;
  CPU_SECURITY_PREMEM_CONFIG       *CpuSecurityPreMemConfig;
#endif
#if FixedPcdGetBool(PcdBfxEnable) == 1
  UINT32                           DescriptorRegionOffset = 0;
  UINT32                           DescriptorRegionSize = 0;
#endif

  DEBUG ((DEBUG_INFO, "Update PeiCpuPolicyUpdate Pos-Mem Start\n"));

  SiPolicyPpi = NULL;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
  FspmUpd = NULL;
#else
  CpuConfig               = NULL;
  CpuSgxConfig            = NULL;
  SiPreMemPolicyPpi       = NULL;
  CpuPowerMgmtBasicConfig = NULL;
  CpuSecurityPreMemConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);

  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuSgxConfigGuid, (VOID *) &CpuSgxConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Make sure ReadOnlyVariablePpi is available
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Get Setup Variable
  //
  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupData
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (CPU_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"CpuSetup",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &CpuSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (CPU_SETUP_SGX_EPOCH_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"CpuSetupSgxEpochData",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &CpuSetupSgxEpochData
                               );
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdBfxEnable) == 1
  Status = GetUfsDescriptorRegion (&DescriptorRegionOffset, &DescriptorRegionSize);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UFS Soft Strap Start Address: 0x%X\n", DescriptorRegionOffset));
    UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.UfsStrapAddress, CpuConfig->UfsStrapAddress, DescriptorRegionOffset);
  }
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AesEnable, CpuConfig->AesEnable, CpuSetup.AES);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TxtEnable, CpuConfig->TxtEnable, CpuSetup.Txt);

  if (CpuSetup.PpinSupport == 0) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PpinSupport, CpuConfig->PpinSupport, 0); ///< reference code policy is disabled
  } else if ((CpuSetup.PpinSupport == 1) && (CpuSetup.PpinEnableMode == 0)) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PpinSupport, CpuConfig->PpinSupport, 2); ///< reference code policy is set to Auto. The feature is disabled if End of Manufacturing flag is set.
  } else if ((CpuSetup.PpinSupport == 1) && (CpuSetup.PpinEnableMode == 1)) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PpinSupport, CpuConfig->PpinSupport, 1); ///< reference code policy is enabled
  }

#if FixedPcdGet8(PcdFspModeSelection) == 0
  CpuConfig->MicrocodePatchAddress = CpuLocateMicrocodePatch (&CpuConfig->MicrocodePatchRegionSize);
#endif

#if (FixedPcdGetBool(PcdFspWrapperEnable) == 1) && (FixedPcdGet8(PcdFspModeSelection) == 0)
  PcdSetEx64S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuMicrocodePatchAddress,    CpuConfig->MicrocodePatchAddress);
  PcdSetEx64S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuMicrocodePatchRegionSize, CpuConfig->MicrocodePatchRegionSize);
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccActivationOffset,        CpuPowerMgmtBasicConfig->TccActivationOffset,        CpuSetup.TCCActivationOffset);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccOffsetTimeWindowForRatl, CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl, CpuSetup.TccOffsetTimeWindow);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccOffsetClamp,             CpuPowerMgmtBasicConfig->TccOffsetClamp,             CpuSetup.TccOffsetClamp);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccOffsetLock,              CpuPowerMgmtBasicConfig->TccOffsetLock,              CpuSetup.TccOffsetLock);

  TempMsr.Qword = AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.OneCoreRatioLimit,          CpuPowerMgmtBasicConfig->OneCoreRatioLimit,          TempMsr.Bytes.FirstByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TwoCoreRatioLimit,          CpuPowerMgmtBasicConfig->TwoCoreRatioLimit,          TempMsr.Bytes.SecondByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThreeCoreRatioLimit,        CpuPowerMgmtBasicConfig->ThreeCoreRatioLimit,        TempMsr.Bytes.ThirdByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FourCoreRatioLimit,         CpuPowerMgmtBasicConfig->FourCoreRatioLimit,         TempMsr.Bytes.FouthByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FiveCoreRatioLimit,         CpuPowerMgmtBasicConfig->FiveCoreRatioLimit,         TempMsr.Bytes.FifthByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SixCoreRatioLimit,          CpuPowerMgmtBasicConfig->SixCoreRatioLimit,          TempMsr.Bytes.SixthByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SevenCoreRatioLimit,        CpuPowerMgmtBasicConfig->SevenCoreRatioLimit,        TempMsr.Bytes.SeventhByte);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EightCoreRatioLimit,        CpuPowerMgmtBasicConfig->EightCoreRatioLimit,        TempMsr.Bytes.EighthByte);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // Override Power Management VR configuration
  //
  CpuPowerMgmtVrConfigEx = AllocateZeroPool (sizeof (EFI_GUID) + sizeof (UINT16) + sizeof (CPU_POWER_MGMT_VR_DATA) * MAX_NUM_VRS);
  if (CpuPowerMgmtVrConfigEx == NULL){
    return EFI_OUT_OF_RESOURCES;
  }
  ASSERT (CpuPowerMgmtVrConfigEx != NULL);

  Status = LoadCpuPowerMgmtVrConfigDefaultEx (CpuPowerMgmtVrConfigEx);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }
  for (Index = 0; Index < MAX_NUM_VRS; Index++) {
    ((FSPS_UPD *) FspsUpd)->FspsConfig.VrConfigEnable[Index]  =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->VrConfigEnable[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.TdcEnable[Index]       =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcEnable[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.TdcTimeWindow[Index]   =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcTimeWindow[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.TdcCurrentLimit[Index] =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcCurrentLimit[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.AcLoadline[Index]      =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->AcLoadline[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.DcLoadline[Index]      =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->DcLoadline[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.Psi3Enable[Index]      =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi3Enable[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.Psi4Enable[Index]      =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi4Enable[Index];
    ((FSPS_UPD *) FspsUpd)->FspsConfig.IccMax[Index]          =  CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->IccMax[Index];
  }
  FreePool (CpuPowerMgmtVrConfigEx);
#endif

  //
  // Init Power Management Policy Variables based on setup values
  //
  InitCpuPmConfigBySetupValues (&SetupData, &CpuSetup);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  if (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx == CPU_FEATURE_ENABLE) {
#else
  if (CpuSecurityPreMemConfig->EnableSgx == CPU_FEATURE_ENABLE) {
#endif
    DEBUG ((DEBUG_INFO, "SGX policy was enabled, updating SGX values \n"));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxEpoch0, CpuSgxConfig->SgxEpoch0, CpuSetupSgxEpochData.SgxEpoch0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxEpoch1, CpuSgxConfig->SgxEpoch1, CpuSetupSgxEpochData.SgxEpoch1);
  }

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // Get BIST information from Sec Platform Information
  //
  SecPlatformInformation2 = GetSecPlatformInformation2 ((EFI_PEI_SERVICES **) GetPeiServicesTablePointer ());
  if (SecPlatformInformation2 == NULL) {
    SecPlatformInformation2 = GetSecPlatformInformationInfoInFormat2 ((EFI_PEI_SERVICES **) GetPeiServicesTablePointer ());
  }

  ASSERT (SecPlatformInformation2 != NULL);

  if (SecPlatformInformation2 != NULL) {
    ((FSPS_UPD *) FspsUpd)->FspsConfig.CpuBistData = (UINT32) SecPlatformInformation2;
    DEBUG((DEBUG_INFO, "SecPlatformInformation NumberOfCpus - %x\n", SecPlatformInformation2->NumberOfCpus));
    DEBUG((DEBUG_INFO, "SecPlatformInformation BIST - %x\n", SecPlatformInformation2->CpuInstance[0].InfoRecord.x64HealthFlags.Uint32));
  }
#endif

  //
  // AC Split Lock
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AcSplitLock, CpuConfig->AcSplitLock, CpuSetup.AcSplitLock);


  return EFI_SUCCESS;
}
