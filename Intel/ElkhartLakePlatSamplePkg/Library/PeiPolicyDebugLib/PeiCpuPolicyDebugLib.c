/** @file
  This file is SampleCode of the library for Intel CPU PEI Debug Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#include "PeiPolicyDebug.h"
#include <Library/CpuPlatformLib.h>
#include <Library/PcdLib.h>

/**
  This function performs CPU PEI Debug Policy initialization.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
**/
EFI_STATUS
EFIAPI
UpdatePeiCpuPolicyDebug (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  UINT8                           CpuSku;
  BOOLEAN                         C1UnDemotion;
  BOOLEAN                         C1AutoDemotion;
  CPU_SETUP                       CpuSetup;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspmUpd;
  VOID                            *FspsUpd;
#else
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  SI_POLICY_PPI                   *SiPolicyPpi;
  CPU_TEST_CONFIG                 *CpuTestConfig;
  CPU_POWER_MGMT_TEST_CONFIG      *CpuPowerMgmtTestConfig;
  CPU_CONFIG_LIB_PREMEM_CONFIG    *CpuConfigLibPreMemConfig;
#endif

  DEBUG ((DEBUG_INFO, "Update PeiCpuPolicyDebug Pos-Mem Start\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
  FspmUpd = NULL;
#else
  SiPreMemPolicyPpi        = NULL;
  SiPolicyPpi              = NULL;
  CpuTestConfig            = NULL;
  CpuPowerMgmtTestConfig   = NULL;
  CpuConfigLibPreMemConfig = NULL;
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

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &CpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtTestConfigGuid, (VOID *) &CpuPowerMgmtTestConfig);
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

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ProcessorTraceOutputScheme, CpuTestConfig->ProcessorTraceOutputScheme, CpuSetup.ProcessorTraceOutputScheme);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ProcessorTraceEnable,       CpuTestConfig->ProcessorTraceEnable,       CpuSetup.ProcessorTraceEnable);

  ProcessorTraceAllocateMemory (
    CpuSetup.ProcessorTraceMemSize,
#if FixedPcdGet8(PcdFspModeSelection) == 1
    &((FSPS_UPD *) FspsUpd)->FspsConfig.ProcessorTraceMemBase,
    &((FSPS_UPD *) FspsUpd)->FspsConfig.ProcessorTraceMemLength
#else
    &CpuTestConfig->ProcessorTraceMemBase,
    &CpuTestConfig->ProcessorTraceMemLength
#endif
    );

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MachineCheckEnable,       CpuTestConfig->MachineCheckEnable,       CpuSetup.MachineCheck);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MonitorMwaitEnable,       CpuTestConfig->MonitorMwaitEnable,       CpuSetup.MonitorMwait);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MlcStreamerPrefetcher,    CpuTestConfig->MlcStreamerPrefetcher,    CpuSetup.HwPrefetcher);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.MlcSpatialPrefetcher,     CpuTestConfig->MlcSpatialPrefetcher,     CpuSetup.AclPrefetch);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.IsFusaSupported,          CpuTestConfig->IsFusaSupported,          IsFusaSupported ());

#if (FixedPcdGetBool(PcdFspWrapperEnable) == 0) || (FixedPcdGet8(PcdFspModeSelection) == 1)
  PcdSet8S (PcdCpuApLoopMode, (UINT8) CpuSetup.ApIdleManner);
#else
  PcdSetEx8S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuApLoopMode, (UINT8) CpuSetup.ApIdleManner);
#endif

  if (CpuSetup.VoltageOptimization == 2) { // AUTO
    CpuSku = GetCpuSku();
    if ((CpuSku == EnumCpuUlx) || (CpuSku == EnumCpuUlt)) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.VoltageOptimization, CpuTestConfig->VoltageOptimization, TRUE);
    } else {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.VoltageOptimization, CpuTestConfig->VoltageOptimization, FALSE);
    }
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.VoltageOptimization, CpuTestConfig->VoltageOptimization, CpuSetup.VoltageOptimization);
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThreeStrikeCounterDisable,   CpuTestConfig->ThreeStrikeCounterDisable,            CpuSetup.ThreeStrikeCounterDisable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstCfgCtrIoMwaitRedirection, CpuPowerMgmtTestConfig->CstCfgCtrIoMwaitRedirection, CpuSetup.PmgCstCfgCtrIoMwaitRedirection);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PpmIrmSetting,               CpuPowerMgmtTestConfig->PpmIrmSetting,               CpuSetup.InterruptRedirectMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Cx,                          CpuPowerMgmtTestConfig->Cx,                          CpuSetup.EnableCx);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Eist,                        CpuPowerMgmtTestConfig->Eist,                        CpuSetup.EnableGv);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnergyEfficientPState,       CpuPowerMgmtTestConfig->EnergyEfficientPState,       CpuSetup.EnergyEfficientPState);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CStatePreWake,               CpuPowerMgmtTestConfig->CStatePreWake,               CpuSetup.CStatePreWake);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TimedMwait,                  CpuPowerMgmtTestConfig->TimedMwait,                  CpuSetup.TimedMwait);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmgCstCfgCtrlLock,           CpuPowerMgmtTestConfig->PmgCstCfgCtrlLock,           CpuSetup.PmgCstCfgCtrlLock);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ProcHotLock,                 CpuPowerMgmtTestConfig->ProcHotLock,                 CpuSetup.ProcHotLock);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.BiProcHot,                   CpuPowerMgmtTestConfig->BiProcHot,                   CpuSetup.EnableProcHot);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DisableProcHotOut,           CpuPowerMgmtTestConfig->DisableProcHotOut,           CpuSetup.DisableProcHotOut);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DisableVrThermalAlert,       CpuPowerMgmtTestConfig->DisableVrThermalAlert,       CpuSetup.DisableVrThermalAlert);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ProcHotResponse,             CpuPowerMgmtTestConfig->ProcHotResponse,             CpuSetup.ProcHotResponse);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableAllThermalFunctions,   CpuPowerMgmtTestConfig->EnableAllThermalFunctions,    CpuSetup.EnableAllThermalFunctions);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TStates,                     CpuPowerMgmtTestConfig->TStates,                     CpuSetup.TStatesEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThermalMonitor,              CpuPowerMgmtTestConfig->ThermalMonitor,              CpuSetup.EnableThermalMonitor);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ConfigTdpLevel,              CpuPowerMgmtTestConfig->ConfigTdpLevel,              CpuSetup.ConfigTdpLevel);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnergyEfficientTurbo,        CpuPowerMgmtTestConfig->EnergyEfficientTurbo,        CpuSetup.EnergyEfficientTurbo);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.RaceToHalt,                  CpuPowerMgmtTestConfig->RaceToHalt,                  CpuSetup.RaceToHalt);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PkgCStateLimit,              CpuPowerMgmtTestConfig->PkgCStateLimit,              CpuSetup.PkgCStateLimit);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  if (((FSPS_UPD *) FspsUpd)->FspsConfig.Cx) {
#else
  if (CpuPowerMgmtTestConfig->Cx) {
#endif
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.C1e, CpuPowerMgmtTestConfig->C1e, CpuSetup.EnableC1e);

    //
    // Core C-State AutoDemotion/UnDemotion
    //
    C1AutoDemotion = CpuSetup.CStateAutoDemotion;
    C1UnDemotion   = CpuSetup.CStateUnDemotion;

    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.C1StateUnDemotion,   CpuPowerMgmtTestConfig->C1UnDemotion,   C1UnDemotion);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.C1StateAutoDemotion, CpuPowerMgmtTestConfig->C1AutoDemotion, C1AutoDemotion);
    //
    // Pkg C-state Demotion/Un Demotion
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PkgCStateDemotion,   CpuPowerMgmtTestConfig->PkgCStateDemotion,   CpuSetup.PkgCStateDemotion);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PkgCStateUnDemotion, CpuPowerMgmtTestConfig->PkgCStateUnDemotion, CpuSetup.PkgCStateUnDemotion);

    //
    // Update the Latency values for msr 0x60b, 0x60c
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl1TimeUnit, CpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit, CpuSetup.CstateLatencyControl1TimeUnit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl2TimeUnit, CpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit, CpuSetup.CstateLatencyControl2TimeUnit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl1Irtl,     CpuPowerMgmtTestConfig->CstateLatencyControl1Irtl,     CpuSetup.CstateLatencyControl1Irtl);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl2Irtl,     CpuPowerMgmtTestConfig->CstateLatencyControl2Irtl,     CpuSetup.CstateLatencyControl2Irtl);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl3TimeUnit, CpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit, CpuSetup.CstateLatencyControl3TimeUnit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl4TimeUnit, CpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit, CpuSetup.CstateLatencyControl4TimeUnit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl5TimeUnit, CpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit, CpuSetup.CstateLatencyControl5TimeUnit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl3Irtl,     CpuPowerMgmtTestConfig->CstateLatencyControl3Irtl,     CpuSetup.CstateLatencyControl3Irtl);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl4Irtl,     CpuPowerMgmtTestConfig->CstateLatencyControl4Irtl,     CpuSetup.CstateLatencyControl4Irtl);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CstateLatencyControl5Irtl,     CpuPowerMgmtTestConfig->CstateLatencyControl5Irtl,     CpuSetup.CstateLatencyControl5Irtl);
  }

  return EFI_SUCCESS;
}
