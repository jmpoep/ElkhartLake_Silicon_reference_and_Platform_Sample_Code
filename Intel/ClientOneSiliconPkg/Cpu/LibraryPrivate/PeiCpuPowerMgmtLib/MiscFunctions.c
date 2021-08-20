/** @file
  This file contains Processor Power Management ACPI related functions for
  processors.

  <b>Acronyms:</b>
     - PPM: Processor Power Management
     - TM:  Thermal Monitor
     - IST: Intel(R) Speedstep technology
     - HT:  Hyper-Threading Technology

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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
  This will perform Miscellaneous Power Management related programming.

  @param[in] CtdpSupport  Status of InitializeConfigurableTdp funtion
**/
VOID
InitMiscFeatures (
  EFI_STATUS CtdpSupport
  )
{
  if (mCpuConfig->SkipMpInit == 0) {

    ///
    /// Configure Package Turbo Power Limits
    ///
    if (CtdpSupport == EFI_SUCCESS) {
      ConfigureCtdp ();
    } else {
      ConfigurePowerLimitsNonConfigTdpSkus ();
    }


    ///
    /// Configure PL3 limits
    ///
    ConfigurePl3PowerLimits ();

    ///
    /// Configure PL4 limits
    ///
    ConfigurePl4PowerLimits ();

    ///
    /// Configure DDR RAPL PowerLimits
    ///
    ConfigureDdrPowerLimits ();
  }
  ///
  /// Configure Platform Power Limits
  ///
  ConfigurePlatformPowerLimits ();
}

/**
  Locks down all settings.

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
PpmLockDown (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  )
{
  MSR_REGISTER TempMsr;

  ///
  /// Program PMG_CST_CONFIG MSR [15] (CFG lock bit)
  ///
  ApSafeLockDown (gCpuPowerMgmtTestConfig);
  gMpServicesPpi->StartupAllAPs (
                    PeiServices,
                    gMpServicesPpi,
                    (EFI_AP_PROCEDURE) ApSafeLockDown,
                    FALSE,
                    0,
                    (VOID *) gCpuPowerMgmtTestConfig
                    );
  ///
  /// Lock Package power limit MSR
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_PACKAGE_POWER_LIMIT);
  TempMsr.Dwords.High &= ~(B_POWER_LIMIT_LOCK);
  if (gCpuPowerMgmtBasicConfig->TurboPowerLimitLock) {
    TempMsr.Dwords.High |= B_POWER_LIMIT_LOCK;
  }
  AsmWriteMsr64 (MSR_PACKAGE_POWER_LIMIT, TempMsr.Qword);
  ///
  /// Program the PROCHOT_Lock
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_POWER_CTL1);
  TempMsr.Dwords.Low &= ~(B_MSR_POWER_CTL1_PROCHOT_LOCK_MASK);
  if (gCpuPowerMgmtTestConfig->ProcHotLock) {
    TempMsr.Dwords.Low |= B_MSR_POWER_CTL1_PROCHOT_LOCK_MASK;
  }
  AsmWriteMsr64 (MSR_POWER_CTL1, TempMsr.Qword);
  ///
  /// Program Ddr RAPL LIMIT Lock
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_DDR_RAPL_LIMIT);
  TempMsr.Dwords.High &= ~(B_POWER_LIMIT_LOCK);
  if (gCpuPowerMgmtBasicConfig->TurboPowerLimitLock) {
    TempMsr.Dwords.High |= B_POWER_LIMIT_LOCK;
  }
  AsmWriteMsr64 (MSR_DDR_RAPL_LIMIT, TempMsr.Qword);

  return;
}

/**
  Lock MSR_BROADWELL_PKG_CST_CONFIG_CONTROL.
  This function must be MP safe.

  @param[in] Buffer    Pointer to the function parameters passed in.
**/
VOID
EFIAPI
ApSafeLockDown (
  IN OUT VOID *Buffer
  )
{
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER Msr;
  CPU_POWER_MGMT_TEST_CONFIG                    *CpuPowerMgmtTestConfig;
  UINT8                                         CfgLock;

  CfgLock = TRUE;

  CpuPowerMgmtTestConfig = (CPU_POWER_MGMT_TEST_CONFIG *) Buffer;
  if (CpuPowerMgmtTestConfig != NULL) {
    CfgLock = (UINT8) CpuPowerMgmtTestConfig->PmgCstCfgCtrlLock;
  }
  Msr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
  Msr.Bits.CFGLock = CfgLock;
  AsmWriteMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL, Msr.Uint64);

  return;
}

