/** @file
  This file is PeiCpuPolicy library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include "PeiCpuPolicyLibrary.h"
#include <CpuAccess.h>
#include <IndustryStandard/Pci22.h>
#include <Library/PciSegmentLib.h>
#include <Library/SaPlatformLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PcdLib.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_CONFIG  *CpuConfig;
  CpuConfig  = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuConfig->Header.GuidHob.Name = %g\n", &CpuConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU configuration
  ********************************/
  CpuConfig->AesEnable             = CPU_FEATURE_ENABLE;
  CpuConfig->MicrocodePatchAddress = 0;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadBiosGuardConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  BIOS_GUARD_CONFIG  *BiosGuardConfig;
  BiosGuardConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "BiosGuardConfig->Header.GuidHob.Name = %g\n", &BiosGuardConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "BiosGuardConfig->Header.GuidHob.Header.HobLength = 0x%x\n", BiosGuardConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU BIOS Guard configuration
  ********************************/
  BiosGuardConfig->EcCmdProvisionEav  = 0xFF;
  BiosGuardConfig->EcCmdLock          = 0xFF;
  BiosGuardConfig->BiosGuardModulePtr = 0xFFFFFFFFFFFFFFFF;
  BiosGuardConfig->BiosGuardAttr      = 0xFFFFFFFF;
  BiosGuardConfig->SendEcCmd          = 0xFFFFFFFF;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuSgxConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_SGX_CONFIG  *CpuSgxConfig;
  CpuSgxConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuSgxConfig->Header.GuidHob.Name = %g\n", &CpuSgxConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuSgxConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuSgxConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU SGX configuration
  ********************************/
  CpuSgxConfig->SgxEpoch0 = 0xFFFFFFFFFFFFFFFF;
  CpuSgxConfig->SgxEpoch1 = 0xFFFFFFFFFFFFFFFF;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPowerMgmtBasicConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_POWER_MGMT_BASIC_CONFIG  *CpuPowerMgmtBasicConfig;
  CPU_SKU      CpuSku;
  MSR_REGISTER TempMsr;

  CpuPowerMgmtBasicConfig = ConfigBlockPointer;
  CpuSku                  = GetCpuSku();

  DEBUG ((DEBUG_INFO, "CpuPowerMgmtBasicConfig->Header.GuidHob.Name = %g\n", &CpuPowerMgmtBasicConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPowerMgmtBasicConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPowerMgmtBasicConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU Power Management Basic configuration
  ********************************/
  CpuPowerMgmtBasicConfig->Hwp                          = TRUE;
  CpuPowerMgmtBasicConfig->HdcControl                   = TRUE;
  CpuPowerMgmtBasicConfig->PowerLimit2                  = TRUE;
  CpuPowerMgmtBasicConfig->PowerLimit3Lock              = TRUE;
  CpuPowerMgmtBasicConfig->TccOffsetLock                = TRUE;
  CpuPowerMgmtBasicConfig->EnableItbm                   = TRUE;
  CpuPowerMgmtBasicConfig->EnableItbmDriver             = FALSE;

  ///
  /// Hwp misc functions
  ///
  CpuPowerMgmtBasicConfig->EnablePerCorePState          = TRUE;
  CpuPowerMgmtBasicConfig->EnableHwpAutoPerCorePstate   = TRUE;
  CpuPowerMgmtBasicConfig->EnableHwpAutoEppGrouping     = TRUE;
  CpuPowerMgmtBasicConfig->EnableEpbPeciOverride        = FALSE;
  CpuPowerMgmtBasicConfig->EnableFastMsrHwpReq          = TRUE;

  ///
  /// Initialize RATL (Runtime Average Temperature Limit) Config for SKL Y series.
  ///
  if (CpuSku == EnumCpuUlx) {
    CpuPowerMgmtBasicConfig->TccActivationOffset        = 10;
    CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl = 5000; // 5 sec
    CpuPowerMgmtBasicConfig->TccOffsetClamp             = CPU_FEATURE_ENABLE;
  }
  CpuPowerMgmtBasicConfig->TurboMode                    = TRUE;

  TempMsr.Qword = AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT);
  CpuPowerMgmtBasicConfig->OneCoreRatioLimit = TempMsr.Bytes.FirstByte;
  CpuPowerMgmtBasicConfig->TwoCoreRatioLimit = TempMsr.Bytes.SecondByte;
  CpuPowerMgmtBasicConfig->ThreeCoreRatioLimit = TempMsr.Bytes.ThirdByte;
  CpuPowerMgmtBasicConfig->FourCoreRatioLimit = TempMsr.Bytes.FouthByte;
  CpuPowerMgmtBasicConfig->FiveCoreRatioLimit = TempMsr.Bytes.FifthByte;
  CpuPowerMgmtBasicConfig->SixCoreRatioLimit = TempMsr.Bytes.SixthByte;
  CpuPowerMgmtBasicConfig->SevenCoreRatioLimit = TempMsr.Bytes.SeventhByte;
  CpuPowerMgmtBasicConfig->EightCoreRatioLimit = TempMsr.Bytes.EighthByte;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPowerMgmtVrConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN                     Index;
  CPU_POWER_MGMT_VR_CONFIG  *CpuPowerMgmtVrConfig;
  BOOLEAN                   OcSupport = FALSE; // @todo - add OC Support detection.

  CpuPowerMgmtVrConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuPowerMgmtVrConfig->Header.GuidHob.Name = %g\n", &CpuPowerMgmtVrConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPowerMgmtVrConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPowerMgmtVrConfig->Header.GuidHob.Header.HobLength));

  //
  // When overclocking is enabled, we need to ensure the VR defaults are
  // optimized for overclocking
  //
  if (OcSupport) {

    for (Index = 0; Index < MAX_NUM_VRS; Index++) {
      //
      // Disable VR TDC for all VR domains
      //
      CpuPowerMgmtVrConfig->TdcEnable[Index]       = 0;
      CpuPowerMgmtVrConfig->TdcCurrentLimit[Index]   = 0;
    }
    //
    // Disable noise mitigation and keep fast slew rate
    //
    CpuPowerMgmtVrConfig->AcousticNoiseMitigation = 0;
    CpuPowerMgmtVrConfig->FastPkgCRampDisableIa = 0;
    CpuPowerMgmtVrConfig->FastPkgCRampDisableGt = 0;
    CpuPowerMgmtVrConfig->FastPkgCRampDisableSa = 0;
    CpuPowerMgmtVrConfig->FastPkgCRampDisableFivr = 0;
  }
}

/**
  External call for loading Config block default

  @param[in/out] CpuPowerMgmtVrConfigEx   Pointer to CPU_POWER_MGMT_VR_CONFIG_EX array.

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
LoadCpuPowerMgmtVrConfigDefaultEx (
  IN OUT CPU_POWER_MGMT_VR_CONFIG_EX     *CpuPowerMgmtVrConfigEx
  )
{
  UINTN                           Index;
  CPU_POWER_MGMT_VR_CONFIG        *CpuPowerMgmtVrConfig = NULL;

  CpuPowerMgmtVrConfig = AllocateZeroPool (sizeof (CPU_POWER_MGMT_VR_CONFIG));
  if (CpuPowerMgmtVrConfig == NULL) {
    ASSERT (CpuPowerMgmtVrConfig != NULL);
    return EFI_OUT_OF_RESOURCES;
  }
  LoadCpuPowerMgmtVrConfigDefault (CpuPowerMgmtVrConfig);

  for (Index = 0; Index < MAX_NUM_VRS; Index++) {
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->VrConfigEnable[Index]  = CpuPowerMgmtVrConfig->VrConfigEnable[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcEnable[Index]       = CpuPowerMgmtVrConfig->TdcEnable[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcTimeWindow[Index]   = CpuPowerMgmtVrConfig->TdcTimeWindow[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->TdcCurrentLimit[Index] = CpuPowerMgmtVrConfig->TdcCurrentLimit[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->AcLoadline[Index]      = CpuPowerMgmtVrConfig->AcLoadline[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->DcLoadline[Index]      = CpuPowerMgmtVrConfig->DcLoadline[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi1Threshold[Index]   = CpuPowerMgmtVrConfig->Psi1Threshold[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi2Threshold[Index]   = CpuPowerMgmtVrConfig->Psi2Threshold[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi3Threshold[Index]   = CpuPowerMgmtVrConfig->Psi3Threshold[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi3Enable[Index]      = CpuPowerMgmtVrConfig->Psi3Enable[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->Psi4Enable[Index]      = CpuPowerMgmtVrConfig->Psi4Enable[Index];
    CpuPowerMgmtVrConfigEx->CpuPowerMgmtVrData->IccMax[Index]          = CpuPowerMgmtVrConfig->IccMax[Index];
  }
  FreePool (CpuPowerMgmtVrConfig);
  return EFI_SUCCESS;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPowerMgmtCustomConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_POWER_MGMT_CUSTOM_CONFIG  *CpuPowerMgmtCustomConfig;
  CpuPowerMgmtCustomConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuPowerMgmtCustomConfig->Header.GuidHob.Name = %g\n", &CpuPowerMgmtCustomConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPowerMgmtCustomConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPowerMgmtCustomConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU Power Management Custom configuration
  ********************************/
  CpuPowerMgmtCustomConfig->CustomRatioTable.Cpuid = (UINT16) ((GetCpuFamily() | GetCpuStepping()) & (0x0FFF));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPowerMgmtPsysConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_POWER_MGMT_PSYS_CONFIG  *CpuPowerMgmtPsysConfig;
  CPU_SKU                   CpuSku;

  CpuSku = GetCpuSku();
  CpuPowerMgmtPsysConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuPowerMgmtPsysConfig->Header.GuidHob.Name = %g\n", &CpuPowerMgmtPsysConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPowerMgmtPsysConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPowerMgmtPsysConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU Power Management Psys configuration
  ********************************/
  //
  // Identify whether SKU has EDRAM support
  //

  //
  // Update Psys Pmax on psys enabled skus
  //
  switch(CpuSku) {
     case EnumCpuUlx:
     case EnumCpuUlt:
      //
      //  Update for Cannonlake Silicon
      //
    default:
        break;
   }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuTestConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_TEST_CONFIG  *CpuTestConfig;
  CPU_SKU          CpuSku;
  CpuTestConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuTestConfig->Header.GuidHob.Name = %g\n", &CpuTestConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuTestConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuTestConfig->Header.GuidHob.Header.HobLength));

  CpuSku = GetCpuSku();
  /********************************
    CPU Test configuration
  ********************************/

  CpuTestConfig->MlcStreamerPrefetcher    = CPU_FEATURE_ENABLE;
  CpuTestConfig->MlcSpatialPrefetcher     = CPU_FEATURE_ENABLE;
  CpuTestConfig->MonitorMwaitEnable       = CPU_FEATURE_ENABLE;
  CpuTestConfig->MachineCheckEnable       = CPU_FEATURE_ENABLE;
  CpuTestConfig->IsFusaSupported          = IsFusaSupported ();

  if ((CpuSku == EnumCpuUlx) || (CpuSku == EnumCpuUlt)){
    /**
    This policy should be used to enable or disable Voltage Optimization feature. Recommended defaults:
     Enable  - For Mobile SKUs(U/Y)
     Disable - Rest of all SKUs other than Mobile.
    **/
    CpuTestConfig->VoltageOptimization      = CPU_FEATURE_ENABLE;
  }
  else {
    CpuTestConfig->VoltageOptimization      = CPU_FEATURE_DISABLE;
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPidTestConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_PID_TEST_CONFIG  *CpuPidTestConfig;
  CpuPidTestConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuPidTestConfig->Header.GuidHob.Name = %g\n", &CpuPidTestConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPidTestConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPidTestConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU PID Test configuration
  ********************************/
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPowerMgmtTestConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_POWER_MGMT_TEST_CONFIG  *CpuPowerMgmtTestConfig;
  CpuPowerMgmtTestConfig = ConfigBlockPointer;
  CPU_GENERATION  CpuGeneration;

  DEBUG ((DEBUG_INFO, "CpuPowerMgmtTestConfig->Header.GuidHob.Name = %g\n", &CpuPowerMgmtTestConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPowerMgmtTestConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPowerMgmtTestConfig->Header.GuidHob.Header.HobLength));

  /********************************
    CPU Power Management Test configuration
  ********************************/
  CpuPowerMgmtTestConfig->Eist                          = TRUE;
  CpuPowerMgmtTestConfig->EnergyEfficientPState         = TRUE;
  CpuPowerMgmtTestConfig->EnergyEfficientTurbo          = TRUE;
  CpuPowerMgmtTestConfig->BiProcHot                     = TRUE;
  CpuPowerMgmtTestConfig->DisableProcHotOut             = TRUE;
  CpuPowerMgmtTestConfig->EnableAllThermalFunctions     = TRUE;
  CpuPowerMgmtTestConfig->ThermalMonitor                = TRUE;
  CpuPowerMgmtTestConfig->Cx                            = TRUE;
  CpuPowerMgmtTestConfig->PmgCstCfgCtrlLock             = TRUE;
  CpuPowerMgmtTestConfig->C1e                           = TRUE;
  CpuPowerMgmtTestConfig->C1AutoDemotion                = TRUE;
  CpuPowerMgmtTestConfig->C1UnDemotion                  = TRUE;
  CpuGeneration = GetCpuGeneration();
  if(CpuGeneration == EnumCflCpu){
    CpuPowerMgmtTestConfig->C3AutoDemotion                = TRUE;
    CpuPowerMgmtTestConfig->C3UnDemotion                  = TRUE;
  }
  CpuPowerMgmtTestConfig->PkgCStateDemotion             = TRUE;
  CpuPowerMgmtTestConfig->PkgCStateUnDemotion           = TRUE;
  CpuPowerMgmtTestConfig->CStatePreWake                 = TRUE;
  CpuPowerMgmtTestConfig->RaceToHalt                    = TRUE;
  CpuPowerMgmtTestConfig->CstateLatencyControl1Irtl     = C6_C7_SHORT_LATENCY;
  CpuPowerMgmtTestConfig->CstateLatencyControl2Irtl     = C6_C7_LONG_LATENCY;
  CpuPowerMgmtTestConfig->CstateLatencyControl3Irtl     = C8_LATENCY;
  CpuPowerMgmtTestConfig->CstateLatencyControl4Irtl     = C9_LATENCY;
  //
  // If PS4 is disabled, program 2750us to MSR_C_STATE_LATENCY_CONTROL_5
  //
  CpuPowerMgmtTestConfig->CstateLatencyControl5Irtl     = C10_LATENCY;
  CpuPowerMgmtTestConfig->PkgCStateLimit                = PkgAuto;
  CpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit = TimeUnit1024ns;
  CpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit = TimeUnit1024ns;
  CpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit = TimeUnit1024ns;
  CpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit = TimeUnit1024ns;
  CpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit = TimeUnit1024ns;
  CpuPowerMgmtTestConfig->CustomPowerUnit               = PowerUnit125MilliWatts;
  CpuPowerMgmtTestConfig->PpmIrmSetting                 = PpmIrmFixedPriority;
}

static COMPONENT_BLOCK_ENTRY  mCpuIpBlocks [] = {
  {&gCpuConfigGuid,                     sizeof (CPU_CONFIG),                         CPU_CONFIG_REVISION,                        LoadCpuConfigDefault},
  {&gCpuSgxConfigGuid,                  sizeof (CPU_SGX_CONFIG),                     CPU_SGX_CONFIG_REVISION,                    LoadCpuSgxConfigDefault},
  {&gCpuPowerMgmtBasicConfigGuid,       sizeof (CPU_POWER_MGMT_BASIC_CONFIG),        CPU_POWER_MGMT_BASIC_CONFIG_REVISION,       LoadCpuPowerMgmtBasicConfigDefault},
  {&gCpuPowerMgmtVrConfigGuid,          sizeof (CPU_POWER_MGMT_VR_CONFIG),           CPU_POWER_MGMT_VR_CONFIG_REVISION,          LoadCpuPowerMgmtVrConfigDefault},
  {&gCpuPowerMgmtCustomConfigGuid,      sizeof (CPU_POWER_MGMT_CUSTOM_CONFIG),       CPU_POWER_MGMT_CUSTOM_CONFIG_REVISION,      LoadCpuPowerMgmtCustomConfigDefault},
  {&gCpuPowerMgmtPsysConfigGuid,        sizeof (CPU_POWER_MGMT_PSYS_CONFIG),         CPU_POWER_MGMT_PSYS_CONFIG_REVISION,        LoadCpuPowerMgmtPsysConfigDefault},
  {&gCpuTestConfigGuid,                 sizeof (CPU_TEST_CONFIG),                    CPU_TEST_CONFIG_REVISION,                   LoadCpuTestConfigDefault},
  {&gCpuPidTestConfigGuid,              sizeof (CPU_PID_TEST_CONFIG),                CPU_PID_TEST_CONFIG_REVISION,               LoadCpuPidTestConfigDefault},
  {&gCpuPowerMgmtTestConfigGuid,        sizeof (CPU_POWER_MGMT_TEST_CONFIG),         CPU_POWER_MGMT_TEST_CONFIG_REVISION,        LoadCpuPowerMgmtTestConfigDefault},
};

/**
  Get CPU config block table total size.

  @retval Size of CPU config block table
**/
UINT16
EFIAPI
CpuGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mCpuIpBlocks[0], sizeof (mCpuIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  CpuAddConfigBlocks add all Cpu config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add CPU config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuAddConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  )
{
  EFI_STATUS Status;
  DEBUG((DEBUG_INFO, "CPU Post-Mem Entry \n"));
  PostCode (0xC00);

  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mCpuIpBlocks[0], sizeof (mCpuIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
  DEBUG ((DEBUG_INFO, "CpuAddConfigBlocks Done \n"));
  PostCode (0xC09);

  return Status;
}
