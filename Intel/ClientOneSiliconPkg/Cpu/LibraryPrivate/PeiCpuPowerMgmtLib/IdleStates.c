/** @file
  This file contains power management C State configuration functions for
  processors.

  Acronyms:
  - PPM: Processor Power Management
  - TM:  Thermal Monitor
  - IST: Intel(R) Speedstep technology
  - HT:  Hyper-Threading Technology

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include "PowerMgmtCommon.h"

/**
  Initializes C States Power management features

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitCState (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  )
{
  ///
  /// Initialize C states, some are general, some are processor specific.
  ///
  /// AcpiIoBase + 0x14 (PM_CST_LVL2) register no longer exists in PCH.
  /// When the IO in this range is read, the CPU puts itself into a mwait
  /// and does not forward this IO to the PCH. MSR_PMG_IO_CAPTURE_BASE was created because
  /// the functionality was moved from the PCH to the CPU.
  ///
  EnableCStates (PeiServices, PmcGetAcpiBase () + PM_CST_LVL2);

  InitCstatePreWake ();
}

/**
  Disable/Enable the CState Pre-Wake Feature
**/
VOID
InitCstatePreWake (
  VOID
  )
{
  MSR_REGISTER TempMsr;

  TempMsr.Qword = AsmReadMsr64 (MSR_POWER_CTL1);
  TempMsr.Dwords.Low &= ~(B_MSR_POWER_CTL1_CSTATE_PREWAKE_DISABLE_MASK);
  if (gCpuPowerMgmtTestConfig->CStatePreWake == FALSE) {
    TempMsr.Dwords.Low |= B_MSR_POWER_CTL1_CSTATE_PREWAKE_DISABLE_MASK;
  }
  AsmWriteMsr64 (MSR_POWER_CTL1, TempMsr.Qword);

  return;
}

/**
  Enables C-State support as specified by the input flags on all logical
  processors and sets associated timing requirements in the chipset.

  @param[in] PeiServices    Pointer to PEI Services Table
  @param[in] C3IoAddress  IO address to generate C3 states (PM base + 014 usually)
**/
VOID
EnableCStates (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN UINT16                   C3IoAddress
  )
{
  MSR_REGISTER PowerCtl;
  MSR_REGISTER TempMsr;
  UINT32       LCR1Latency;
  UINT32       LCR2Latency;
  UINT32       LCR3Latency;
  UINT32       LCR4Latency;
  UINT32       LCR5Latency;
  UINT16       EnableCStateParameters;

  ///
  /// Load the C-State parameters to pass to the core function.
  ///
  EnableCStateParameters = C3IoAddress;
  ///
  /// Enable C-States on all logical processors.
  ///
  ApSafeEnableCStates(&EnableCStateParameters);
  gMpServicesPpi->StartupAllAPs (
                    PeiServices,
                    gMpServicesPpi,
                    (EFI_AP_PROCEDURE) ApSafeEnableCStates,
                    FALSE,
                    0,
                    (VOID *) &EnableCStateParameters
                    );
  ///
  /// If C-states are disabled or not supported, Disable C1e  and retrun
  ///
  if ((mPpmFlags & PPM_C_STATES) == 0) {
    PowerCtl.Qword = AsmReadMsr64 (MSR_POWER_CTL1);
    PowerCtl.Dwords.Low &= ~B_MSR_POWER_CTL1_C1E_ENABLE_MASK;
    AsmWriteMsr64 (MSR_POWER_CTL1, PowerCtl.Qword);
    DEBUG (
      (DEBUG_INFO,
       "Setup C state disabled.Disable C1e. MSR(1FC) : %X %X\n",
       PowerCtl.Dwords.High,
       PowerCtl.Dwords.Low)
      );
    return;
  }
  ///
  /// Configure supported enhanced C-states
  ///
  /// Read Power Ctl MSR
  ///
  PowerCtl.Qword = AsmReadMsr64 (MSR_POWER_CTL1);
  DEBUG ((DEBUG_INFO, "MSR(1FC) before configuring C1E: %X %X\n", PowerCtl.Dwords.High, PowerCtl.Dwords.Low));
  ///
  /// Enable supported states
  ///
  if (mPpmFlags & PPM_C1E) {
    PowerCtl.Dwords.Low |= B_MSR_POWER_CTL1_C1E_ENABLE_MASK;
  } else {
    PowerCtl.Dwords.Low &= ~B_MSR_POWER_CTL1_C1E_ENABLE_MASK;
  }
  ///
  /// Update Power Control MSR
  ///
  AsmWriteMsr64 (MSR_POWER_CTL1, PowerCtl.Qword);
  DEBUG ((DEBUG_INFO, "MSR(1FC) after configuring C1E: %X %X\n", PowerCtl.Dwords.High, PowerCtl.Dwords.Low));
  ///
  /// Program Interrupt response time limits used by processor to decided when to get into
  /// package C6 and C7
  ///
  DEBUG ((DEBUG_INFO, "Programming the C6/C7 (MSR 0x60B, 0x60C) Latencies \n"));
  ///
  /// Package C6/C7 short Interrupt response time
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_1);
  DEBUG ((DEBUG_INFO, "MSR(60B) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_MSR_C_STATE_LATENCY_CONTROL_1_VALUE_MASK | B_MSR_C_STATE_LATENCY_CONTROL_1_MULTIPLIER_MASK | B_MSR_C_STATE_LATENCY_CONTROL_1_VALID_MASK);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x60B
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl1Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit, N_MSR_C_STATE_LATENCY_CONTROL_1_MULTIPLIER_OFFSET);
  TempMsr.Dwords.Low |= B_MSR_C_STATE_LATENCY_CONTROL_1_VALID_MASK;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_1, TempMsr.Qword);
  ///
  /// Package C6/C7 long Interrupt response time
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_2);
  DEBUG ((DEBUG_INFO, "MSR(60C) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_MSR_C_STATE_LATENCY_CONTROL_2_VALUE_MASK | B_MSR_C_STATE_LATENCY_CONTROL_2_MULTIPLIER_MASK | B_MSR_C_STATE_LATENCY_CONTROL_2_VALID_MASK);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x60C
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl2Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit, N_MSR_C_STATE_LATENCY_CONTROL_2_MULTIPLIER_OFFSET);
  TempMsr.Dwords.Low |= B_MSR_C_STATE_LATENCY_CONTROL_2_VALID_MASK;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_2, TempMsr.Qword);

  ///
  /// Package C8 Interrupt response time
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_3);
  DEBUG ((DEBUG_INFO, "MSR(633) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_MSR_C_STATE_LATENCY_CONTROL_3_VALUE_MASK | B_MSR_C_STATE_LATENCY_CONTROL_3_MULTIPLIER_MASK | B_MSR_C_STATE_LATENCY_CONTROL_3_VALID_MASK);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x633
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl3Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit, N_MSR_C_STATE_LATENCY_CONTROL_3_MULTIPLIER_OFFSET);
  TempMsr.Dwords.Low |= B_MSR_C_STATE_LATENCY_CONTROL_3_VALID_MASK;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_3, TempMsr.Qword);
  ///
  /// Package C9 Interrupt response time
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_4);
  DEBUG ((DEBUG_INFO, "MSR(634) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_MSR_C_STATE_LATENCY_CONTROL_4_VALUE_MASK | B_MSR_C_STATE_LATENCY_CONTROL_4_MULTIPLIER_MASK | B_MSR_C_STATE_LATENCY_CONTROL_4_VALID_MASK);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x634
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl4Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit, N_MSR_C_STATE_LATENCY_CONTROL_4_MULTIPLIER_OFFSET);
  TempMsr.Dwords.Low |= B_MSR_C_STATE_LATENCY_CONTROL_4_VALID_MASK;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_4, TempMsr.Qword);
  ///
  /// Package C10 Interrupt response time
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_5);
  DEBUG ((DEBUG_INFO, "MSR(635) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_MSR_C_STATE_LATENCY_CONTROL_5_VALUE_MASK | B_MSR_C_STATE_LATENCY_CONTROL_5_MULTIPLIER_MASK | B_MSR_C_STATE_LATENCY_CONTROL_5_VALID_MASK);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x635
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl5Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit, N_MSR_C_STATE_LATENCY_CONTROL_5_MULTIPLIER_OFFSET);
  TempMsr.Dwords.Low |= B_MSR_C_STATE_LATENCY_CONTROL_5_VALID_MASK;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_5, TempMsr.Qword);
  ///
  /// Update the PPM Global NVS Area
  ///
  LCR1Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit * 5));
  LCR1Latency = (LCR1Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl1Irtl) / 1000;
  if (LCR1Latency > 0xFFFF) {
    LCR1Latency = 0xFFFF;
  }
  LCR2Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit * 5));
  LCR2Latency = (LCR2Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl2Irtl) / 1000;
  if (LCR2Latency > 0xFFFF) {
    LCR2Latency = 0xFFFF;
  }

  LCR3Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit * 5));
  LCR3Latency = (LCR3Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl3Irtl) / 1000;
  if (LCR3Latency > 0xFFFF) {
    LCR3Latency = 0xFFFF;
  }

  LCR4Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit * 5));
  LCR4Latency = (LCR4Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl4Irtl) / 1000;
  if (LCR4Latency > 0xFFFF) {
    LCR4Latency = 0xFFFF;
  }

  LCR5Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit * 5));
  LCR5Latency = (LCR5Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl5Irtl) / 1000;
  if (LCR5Latency > 0xFFFF) {
    LCR5Latency = 0xFFFF;
  }





  return;
}

/**
  Enable C-State support as specified by the input flags on a logical processor.
    Configure BIOS C1 Coordination (SMI coordination)
    Enable IO redirection coordination
    Choose proper coordination method
    Configure extended C-States

  This function must be MP safe.

  @param[in out] Buffer    Pointer to a ENABLE_CSTATE_PARAMS containing the necessary
                           information to enable C-States

  @retval EFI_SUCCESS  Processor C-State support configured successfully.
**/
VOID
EFIAPI
ApSafeEnableCStates (
  IN OUT VOID *Buffer
  )
{
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER PmCfgCtrlMsr;
  MSR_REGISTER                                  IoCaptAddr;
  MSR_IA32_MISC_ENABLE_REGISTER                 MiscEnable;
  UINT16                                        C3IoAddress;

  ///
  /// Extract parameters from the buffer
  ///
  C3IoAddress = *((UINT16 *) Buffer);
  ///
  /// If C-states are disabled in setup, disable C-states
  ///
  if (!(mPpmFlags & PPM_C_STATES)) {
    PmCfgCtrlMsr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
    PmCfgCtrlMsr.Bits.Limit = 0;
    AsmWriteMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL, PmCfgCtrlMsr.Uint64);
    return;
  }
  ///
  /// Set C-state package limit to the highest C-state enabled
  ///
  PmCfgCtrlMsr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
  if (gCpuPowerMgmtTestConfig->PkgCStateLimit != PkgCpuDefault) {
    PmCfgCtrlMsr.Bits.Limit = 0;

    if (gCpuPowerMgmtTestConfig->PkgCStateLimit < PkgCMax) {
      PmCfgCtrlMsr.Bits.Limit = gCpuPowerMgmtTestConfig->PkgCStateLimit;
    } else if ((mPpmFlags & PPM_C10) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C10;
    } else if ((mPpmFlags & PPM_C9) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C9;
    } else if ((mPpmFlags & PPM_C8) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C8;
    } else if ((mPpmFlags & PPM_C7S) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C7S;
    } else if ((mPpmFlags & PPM_C7) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C7;
    } else if (mPpmFlags & PPM_C6) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C6;
    } else if (mPpmFlags & PPM_C1) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C1;
    }
  }

  ///
  /// Configure C State IO redirection
  ///
  if (gCpuPowerMgmtTestConfig->CstCfgCtrIoMwaitRedirection) {
    PmCfgCtrlMsr.Bits.IO_MWAIT = 1;
  }

  //
  // Enable TimedMwait
  //
  if (mPpmFlags & PPM_TIMED_MWAIT) {
    PmCfgCtrlMsr.Uint32 |= B_TIMED_MWAIT_ENABLE;                   ///< @todo Use bitfield definition when available.
  }

  ///
  /// Configure C-state auto-demotion
  ///
  PmCfgCtrlMsr.Bits.C1AutoDemotion = 0;
  if (gCpuPowerMgmtTestConfig->C1AutoDemotion) {
    ///
    /// Enable C6/C7 Auto-demotion to C1
    ///
    PmCfgCtrlMsr.Bits.C1AutoDemotion = 1;
  }
  ///
  /// Configure C-state un-demotion
  ///
  PmCfgCtrlMsr.Bits.C1Undemotion = 0;
  if (gCpuPowerMgmtTestConfig->C1UnDemotion) {
    ///
    /// Enable un-demotion from demoted C1
    ///
    PmCfgCtrlMsr.Bits.C1Undemotion = 1;
  }
  ///
  /// Configure Package C-state Demotion / un-demotion
  ///
  PmCfgCtrlMsr.Bits.CStateAutoDemotion = 0;
  PmCfgCtrlMsr.Bits.CStateUndemotion = 0;
  if (gCpuPowerMgmtTestConfig->PkgCStateDemotion) {
    ///
    /// Enable Package C-state Demotion
    ///
    PmCfgCtrlMsr.Bits.CStateAutoDemotion = 1;
  }
  if (gCpuPowerMgmtTestConfig->PkgCStateUnDemotion) {
    ///
    /// Enable Package C-state un-demotion
    ///
    PmCfgCtrlMsr.Bits.CStateUndemotion = 1;
  }
  AsmWriteMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL, PmCfgCtrlMsr.Uint64);
  ///
  /// Enable MONITOR/MWAIT support
  /// (already done on BSP, but must be done on all components.)
  ///
  MiscEnable.Uint64 = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);
  MiscEnable.Bits.MONITOR = 1;
  AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, MiscEnable.Uint64);
  ///
  /// Configuration of I/O capture and I/O coordination SMI MSR.
  /// Configure the base port and range in the MSR to match LVL_X settings in ACPI tables
  /// Set I/O capture base port and range
  ///
  IoCaptAddr.Qword = AsmReadMsr64 (MSR_PMG_IO_CAPTURE_BASE);
  ///
  /// Mask off CST range and set the CST range
  ///
  IoCaptAddr.Dwords.Low &= ~B_MSR_PMG_IO_CAPTURE_BASE_CST_RANGE_MASK;
  if (mPpmFlags & PPM_C10) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL7;
  } else if (mPpmFlags & PPM_C9) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL6;
  } else if (mPpmFlags & PPM_C8) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL5;
  } else if (mPpmFlags & PPM_C7) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL4;
  } else if (mPpmFlags & PPM_C6) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL3;
  }
  ///
  /// Set the base CST address
  ///
  IoCaptAddr.Dwords.Low &= ~B_MSR_PMG_IO_CAPTURE_BASE_LVL2B_MASK;
  IoCaptAddr.Dwords.Low |= (UINT32) C3IoAddress;
  AsmWriteMsr64 (MSR_PMG_IO_CAPTURE_BASE, IoCaptAddr.Qword);
  return;
}

