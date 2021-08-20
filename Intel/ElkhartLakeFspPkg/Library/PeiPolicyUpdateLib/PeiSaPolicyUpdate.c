/** @file
  Do Platform Stage System Agent initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#include <SaPolicyCommon.h>
#include <Library/DebugLib.h>
#include <FspEas.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/FspCommonLib.h>
#include <Library/DebugLib.h>
#include <FspsUpd.h>

/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization

  @param[in out] SiPolicyPpi       SI_POLICY PPI
  @param[in]     FspsUpd           The pointer of FspsUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicy (
  IN OUT SI_POLICY_PPI       *SiPolicyPpi,
  IN     FSPS_UPD            *FspsUpd
  )
{
  EFI_STATUS                    Status;
  FSP_S_CONFIG                  *FspsConfig;
  SA_MISC_PEI_CONFIG            *MiscPeiConfig;
  GRAPHICS_PEI_CONFIG           *GtConfig;
  GNA_CONFIG                    *GnaConfig;
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  CPU_PCIE_CONFIG               *CpuPcieRpConfig;
  UINT8                         RpIndex;
  UINTN                         MaxPcieRootPorts;
#endif

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiSaPolicy\n"));

  // Use direct pointers below, to reduce debug build code size
  FspsConfig           = &FspsUpd->FspsConfig;
  FspsConfig       = &FspsUpd->FspsConfig;

  MiscPeiConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *)&MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

  GtConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *)&GtConfig);
  ASSERT_EFI_ERROR (Status);

  GnaConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGnaConfigGuid, (VOID *)&GnaConfig);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  CpuPcieRpConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPcieRpConfigGuid, (VOID *)&CpuPcieRpConfig);
  ASSERT_EFI_ERROR(Status);
#endif

  if (MiscPeiConfig != NULL) {
    MiscPeiConfig->Device4Enable    = FspsConfig->Device4Enable;
    MiscPeiConfig->SkipPamLock      = FspsConfig->SkipPamLock;
    MiscPeiConfig->EdramTestMode    = FspsConfig->EdramTestMode;
  }

  if (GtConfig != NULL) {
    GtConfig->GraphicsConfigPtr   = (VOID *) FspsConfig->GraphicsConfigPtr;
    GtConfig->LogoPtr             = (VOID *) FspsConfig->LogoPtr;
    GtConfig->LogoSize            = FspsConfig->LogoSize;
    GtConfig->PavpEnable          = FspsConfig->PavpEnable;
    GtConfig->CdClock             = FspsConfig->CdClock;
    GtConfig->PeiGraphicsPeimInit = FspsConfig->PeiGraphicsPeimInit;
    GtConfig->RenderStandby       = FspsConfig->RenderStandby;
    GtConfig->PmSupport           = FspsConfig->PmSupport;
    GtConfig->CdynmaxClampEnable  = FspsConfig->CdynmaxClampEnable;
    GtConfig->GtFreqMax           = FspsConfig->GtFreqMax;
    GtConfig->DisableTurboGt      = FspsConfig->DisableTurboGt;
    GtConfig->SkipCdClockInit     = FspsConfig->SkipCdClockInit;

    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->GraphicsConfigPtr from FSP UpdatePeiSaPolicy: 0x%x\n", GtConfig->GraphicsConfigPtr));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->LogoPtr: 0x%X\n", GtConfig->LogoPtr ));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "GtConfig->LogoSize: 0x%X\n", GtConfig->LogoSize));

    GtConfig->DdiConfiguration.DdiPortAConfig = FspsConfig->DdiPortAConfig;
    GtConfig->DdiConfiguration.DdiPortBConfig = FspsConfig->DdiPortBConfig;
    GtConfig->DdiConfiguration.DdiPortCConfig = FspsConfig->DdiPortCConfig;
    GtConfig->DdiConfiguration.DdiPortAHpd = FspsConfig->DdiPortAHpd;
    GtConfig->DdiConfiguration.DdiPortBHpd = FspsConfig->DdiPortBHpd;
    GtConfig->DdiConfiguration.DdiPortCHpd = FspsConfig->DdiPortCHpd;
    GtConfig->DdiConfiguration.DdiPort1Hpd = FspsConfig->DdiPort1Hpd;
    GtConfig->DdiConfiguration.DdiPort2Hpd = FspsConfig->DdiPort2Hpd;
    GtConfig->DdiConfiguration.DdiPort3Hpd = FspsConfig->DdiPort3Hpd;
    GtConfig->DdiConfiguration.DdiPort4Hpd = FspsConfig->DdiPort4Hpd;
    GtConfig->DdiConfiguration.DdiPortADdc = FspsConfig->DdiPortADdc;
    GtConfig->DdiConfiguration.DdiPortBDdc = FspsConfig->DdiPortBDdc;
    GtConfig->DdiConfiguration.DdiPortCDdc = FspsConfig->DdiPortCDdc;
    GtConfig->DdiConfiguration.DdiPort1Ddc = FspsConfig->DdiPort1Ddc;
    GtConfig->DdiConfiguration.DdiPort2Ddc = FspsConfig->DdiPort2Ddc;
    GtConfig->DdiConfiguration.DdiPort3Ddc = FspsConfig->DdiPort3Ddc;
    GtConfig->DdiConfiguration.DdiPort4Ddc = FspsConfig->DdiPort4Ddc;

  }

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  //
  // Update PCIE RP RootPort policies
  //
  MaxPcieRootPorts = GetMaxCpuPciePortNum ();
  for (RpIndex = 0; RpIndex < MaxPcieRootPorts; RpIndex++) {
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.HotPlug                                           = FspsConfig->CpuPcieRpHotPlug[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PmSci                                             = FspsConfig->CpuPcieRpPmSci[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.TransmitterHalfSwing                              = FspsConfig->CpuPcieRpTransmitterHalfSwing[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.AdvancedErrorReporting                            = FspsConfig->CpuPcieRpAdvancedErrorReporting[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.UnsupportedRequestReport                          = FspsConfig->CpuPcieRpUnsupportedRequestReport[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.FatalErrorReport                                  = FspsConfig->CpuPcieRpFatalErrorReport[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.NoFatalErrorReport                                = FspsConfig->CpuPcieRpNoFatalErrorReport[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.CorrectableErrorReport                            = FspsConfig->CpuPcieRpCorrectableErrorReport[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.SystemErrorOnFatalError                           = FspsConfig->CpuPcieRpSystemErrorOnFatalError[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.SystemErrorOnNonFatalError                        = FspsConfig->CpuPcieRpSystemErrorOnNonFatalError[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.SystemErrorOnCorrectableError                     = FspsConfig->CpuPcieRpSystemErrorOnCorrectableError[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.MaxPayload                                        = FspsConfig->CpuPcieRpMaxPayload[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.DpcEnabled                                        = FspsConfig->CpuPcieRpDpcEnabled[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].VcEnabled                                                            = FspsConfig->CpuPcieRpVcEnabled[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.RpDpcExtensionsEnabled                            = FspsConfig->CpuPcieRpDpcExtensionsEnabled[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PtmEnabled                                        = FspsConfig->CpuPcieRpPtmEnabled[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.Gen3EqPh3Method                                   = FspsConfig->CpuPcieRpGen3EqPh3Method[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen3EqPh3Enable                                                      = FspsConfig->CpuPcieRpGen3EqPh3Enable[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen3EqPh23Enable                                                     = FspsConfig->CpuPcieRpGen3EqPh23Enable[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcetTimer                                                            = FspsConfig->CpuPciePcetTimer[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen3PresetCoeffList                                                  = FspsConfig->Gen3CpuPciePresetCoeffList[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen4PresetCoeffList                                                  = FspsConfig->Gen4CpuPciePresetCoeffList[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Px8gtswlpce                                                          = FspsConfig->CpuPciePx8gtswlpce[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Px16gtswlpce                                                         = FspsConfig->CpuPciePx16gtswlpce[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen4EqPh3Enable                                                      = FspsConfig->CpuPcieRpGen4EqPh3Enable[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen4EqPh23Enable                                                     = FspsConfig->CpuPcieRpGen4EqPh23Enable[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PhysicalSlotNumber                                = FspsConfig->CpuPcieRpPhysicalSlotNumber[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.SlotImplemented                                   = FspsConfig->CpuPcieRpSlotImplemented[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.Aspm                                              = FspsConfig->CpuPcieRpAspm[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.L1Substates                                       = FspsConfig->CpuPcieRpL1Substates[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.LtrEnable                                         = FspsConfig->CpuPcieRpLtrEnable[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.LtrConfigLock                     = FspsConfig->CpuPcieRpLtrConfigLock[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.AcsEnabled                                        = FspsConfig->CpuPcieRpAcsEnabled[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.DetectTimeoutMs                                   = FspsConfig->CpuPcieRpDetectTimeoutMs[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.EnableCpm                                         = FspsConfig->CpuPcieRpEnableCpm[RpIndex];

    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxSnoopLatency                = FspsConfig->CpuPcieRpLtrMaxSnoopLatency[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxNoSnoopLatency              = FspsConfig->CpuPcieRpLtrMaxNoSnoopLatency[RpIndex];

    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMode          = FspsConfig->CpuPcieRpSnoopLatencyOverrideMode[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMultiplier    = FspsConfig->CpuPcieRpSnoopLatencyOverrideMultiplier[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideValue         = FspsConfig->CpuPcieRpSnoopLatencyOverrideValue[RpIndex];

    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMode       = FspsConfig->CpuPcieRpNonSnoopLatencyOverrideMode[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier = FspsConfig->CpuPcieRpNonSnoopLatencyOverrideMultiplier[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideValue      = FspsConfig->PcieRpNonSnoopLatencyOverrideValue[RpIndex];

    CpuPcieRpConfig->RootPort[RpIndex].Gen3Uptp                                                             = FspsConfig->CpuPcieRpGen3Uptp[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen3Dptp                                                             = FspsConfig->CpuPcieRpGen3Dptp[RpIndex];

    CpuPcieRpConfig->RootPort[RpIndex].Gen4Uptp                                                             = FspsConfig->CpuPcieRpGen4Uptp[RpIndex];
    CpuPcieRpConfig->RootPort[RpIndex].Gen4Dptp                                                             = FspsConfig->CpuPcieRpGen4Dptp[RpIndex];
  //
  // Update PCIE RP EqPh3LaneParam policies
  //
    CpuPcieRpConfig->EqPh3LaneParam[RpIndex].Cm = FspsConfig->CpuPcieEqPh3LaneParamCm[RpIndex];
    CpuPcieRpConfig->EqPh3LaneParam[RpIndex].Cp = FspsConfig->CpuPcieEqPh3LaneParamCp[RpIndex];
  }

  //
  // Update PCIE RP HwEqCoeffList policies
  //
  for (RpIndex = 0; RpIndex < PCIE_HWEQ_COEFFS_MAX; RpIndex++) {
    CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[RpIndex].Cm = FspsConfig->CpuPcieHwEqGen3CoeffListCm[RpIndex];
    CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[RpIndex].Cp = FspsConfig->CpuPcieHwEqGen3CoeffListCp[RpIndex];
    CpuPcieRpConfig->HwEqGen4CoeffList[RpIndex].Cm                  = FspsConfig->CpuPcieHwEqGen4CoeffListCm[RpIndex];
    CpuPcieRpConfig->HwEqGen4CoeffList[RpIndex].Cp                  = FspsConfig->CpuPcieHwEqGen4CoeffListCp[RpIndex];
  }

  //
  // Update PCIE RP policies
  //
  CpuPcieRpConfig->SkipCpuFiaProgramming               = FspsConfig->CpuPcieSkipCpuFiaProgramming;
  CpuPcieRpConfig->DisableRootPortClockGating          = FspsConfig->CpuPcieDisableRootPortClockGating;
  CpuPcieRpConfig->DisableRootPortPowerGating          = FspsConfig->CpuPcieDisableRootPortPowerGating;
  CpuPcieRpConfig->PcieCommonConfig.ComplianceTestMode = FspsConfig->CpuPcieComplianceTestMode;
  CpuPcieRpConfig->PcieCommonConfig.RpFunctionSwap     = FspsConfig->CpuPcieRpFunctionSwap;
  CpuPcieRpConfig->PcieDeviceOverrideTablePtr          = FspsConfig->CpuPcieDeviceOverrideTablePtr;

#endif
  if (GnaConfig != NULL) {
    GnaConfig->GnaEnable = FspsConfig->GnaEnable;
  }

  return EFI_SUCCESS;
}
