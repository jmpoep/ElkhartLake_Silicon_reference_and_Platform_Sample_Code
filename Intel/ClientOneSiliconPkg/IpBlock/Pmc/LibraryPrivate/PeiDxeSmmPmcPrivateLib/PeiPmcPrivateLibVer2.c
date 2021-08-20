/** @file
  PCH private PEI PMC Library Ver2.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchPcrLib.h>
#include <Library/DciPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Register/PmcRegs.h>
#include <Register/PmcRegsVer2.h>
#include <Register/PmcRegsFivr.h>
#include <Library/BaseMemoryLib.h>
#include <Register/PchRegs.h>
#include <Library/DciPrivateLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PchInfoLib.h>
#include <Library/CpuPlatformLib.h>

#include "PmcPrivateLibInternal.h"

/**
  S0ix settings

  @param[in] PmConfig                 PmConfig
**/
VOID
PmcSlpS0Config (
  IN PCH_PM_CONFIG                    *PmConfig
  )
{
  UINT32                              PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();
  ///
  /// PWRMBASE + 0x1B1C = 0x801E
  ///
  MmioOr32 (PchPwrmBase + R_PMC_PWRM_1B1C, 0x801E);
  ///
  /// PWRMBASE + 0x1B20 = 0x00138801
  ///
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_CPPM_MISC_CFG, 0x00138801);
}

/**
  Configure Low Power Mode S0ix sub-state support

  @param[in] PmConfig                 PmConfig
**/
VOID
PmcConfigureLpmS0ixSupport (
  IN PCH_PM_CONFIG                         *PmConfig
  )
{
  UINT32                     PwrmBase;
  PMC_LPM_S0IX_SUB_STATE_EN  LpmS0ixSubStateEnable;

  PwrmBase = PmcGetPwrmBase ();
  //
  // LPM_EN[0] - LPM0 - s0i2.0
  // LPM_EN[1] - LPM1 - s0i2.1
  // LPM_EN[2] - LPM2 - s0i2.2. Requires control of v1p05-PHY FET using EXT_PWR_GATE# pin
  // LPM_EN[3] - LPM3 - s0i3.0
  // LPM_EN[4] - LPM4 - s0i3.1
  // LPM_EN[5] - LPM5 - s0i3.2
  // LPM_EN[6] - LPM6 - s0i3.3. Requires control of v1p05-PHY FET using EXT_PWR_GATE# pin
  // LPM_EN[7] - LPM7 - s0i3.4. Requires control of v1p05-IS FET using EXT_PWR_GATE2# pin
  //
  LpmS0ixSubStateEnable.Val = PmConfig->LpmS0ixSubStateEnable.Val;

  //
  // Respective S0ix sub-states need to be disabled if
  // related v1p05-PHY and v1p05-IS FETs are not supported by platform
  //
  if (!PmConfig->V1p05PhyExtFetControlEn) {
    LpmS0ixSubStateEnable.Field.S0i2p2En = 0;
    LpmS0ixSubStateEnable.Field.S0i3p3En = 0;
  }
  if (!PmConfig->V1p05IsExtFetControlEn) {
    LpmS0ixSubStateEnable.Field.S0i3p4En = 0;
  }

  MmioWrite32 (PwrmBase + R_TGL_PCH_PMC_PWRM_LPM_EN, LpmS0ixSubStateEnable.Val);

  //
  // LPM_PRI[3:0]   - LPM0 - s0i2.0
  // LPM_PRI[7:4]   - LPM1 - s0i2.1
  // LPM_PRI[11:8]  - LPM2 - s0i2.2
  // LPM_PRI[15:12] - LPM3 - s0i3.0
  // LPM_PRI[19:16] - LPM4 - s0i3.1
  // LPM_PRI[23:20] - LPM5 - s0i3.2
  // LPM_PRI[27:24] - LPM6 - s0i3.3
  // LPM_PRI[31:28] - LPM7 - s0i3.4
  //
  MmioWrite32 (PwrmBase + R_TGL_PCH_PMC_PWRM_LPM_PRI, 0x01346257);
}

/**
  Enable ModPHY SUS Power Gating
**/
VOID
EnableModPhySusWellPg (
  VOID
  )
{
  UINT32 Data32Or;
  Data32Or = 0;
  ///
  /// MODPHY_PM_CFG3 (0x10C8[30]) = 1, ModPHY Lane SUS Power Domain Dynamic Gating Enable
  /// MODPHY_PM_CFG3 (0x10C8[0]) = 1, C10 qualification for MPHY power gating Enable
  ///
  ///
  ///
  /// [TGP Z0 PM]: System hangs during VNN_Save when modPHY per lane SUS Power Gating is enabled
  ///    URL: https://hsdes.intel.com/appstore/article/#/1409198990
  ///         https://hsdes.intel.com/appstore/article/#/1409859062  -> applied only for A0 and Z0 steppings
  ///    Need to disable ModPHY Per-Lane SUS Well Dynamic Gating as WA until above sighting is root caused.
  ///
  ///
  if (IsTglPch () && IsPchLp () && ((PchStepping () >= PCH_Z0) || (PchStepping () < PCH_B0))) {
    Data32Or = (B_PMC_PWRM_MODPHY_PM_CFG3_MLSPDDGE | B_PMC_PWRM_MODPHY_PM_CFG3_C10_QUAL_MPHYPG);
  } else {
    Data32Or = (B_PMC_PWRM_MODPHY_PM_CFG3_MPLSPDDGE | B_PMC_PWRM_MODPHY_PM_CFG3_MLSPDDGE | B_PMC_PWRM_MODPHY_PM_CFG3_C10_QUAL_MPHYPG);
  }
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_MODPHY_PM_CFG3, Data32Or);
}

/**
  Configure CPPM Force Alignment Control
**/
VOID
PmcConfigureCppmForceAlignmentControl (
  VOID
  )
{
  UINT32 PwrmBase;
  UINT32 Data32Or;
  UINT32 Data32And;

  PwrmBase = PmcGetPwrmBase ();

  //
  // Recommendation on programming is delivered by IP
  // team.
  //
  Data32Or = 0xD80A8000;
  Data32And = ~0u;

  if (PchStepping () == PCH_Z0) {
    Data32And &= ~(UINT32)BIT28;
  }

  MmioAndThenOr32 (
    PwrmBase + R_PMC_PWRM_1BD0,
    Data32And,
    Data32Or
    );

  //
  // Lock PCH Forced alignment config
  //
  MmioOr32 (PwrmBase + R_PMC_PWRM_1BD0, BIT30);
}

/**
  This function is part of PMC init and configures which clock wake signals should
  set the SLOW_RING, SA, FAST_RING_CF and SLOW_RING_CF indication sent up to the CPU/PCH
**/
VOID
PmcInitClockWakeEnable (
  VOID
  )
{
  UINT32                    PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  //
  // Configure which backbone clock wake signals should set the SLOW_RING indication
  // sent up over the PM_SYNC
  // Enabled for:
  // All PCIe ports
  // All SATA ports
  // GbE
  // CNVi
  // HDA
  // USB OTG
  // VLW
  // Legacy cluster
  // P2SB
  // ISH
  // ME
  // PCIe NAND
  // SMBUS
  // CHAP
  // Thermal sensor
  // SPI
  // PMC
  // Display
  // Southport A, B, C and D
  // Primary channel
  // MEIO
  // GPIO
  // Audio DSP
  // LPSS
  // SCS
  // THC 0 and 1
  //
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SLOW_RING, 0x2F8FBB01);
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SLOW_RING2, 0x1A80C7E0);

  //
  // Configure which backbone clock wake signals should set the SA indication
  // sent up over the PM_SYNC. This configuration matches the SLOW_RING indication
  // configuration.
  //
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SA, 0x2F8FBB01);
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SA2, 0x1A80C7E0);

  //
  // Configure which clock wake signals should set the SLOW_RING_CF indication
  // sent up over the PM_SYNC
  // Enabled for:
  // Legacy cluster
  // P2SB
  //
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SLOW_RING_CF, 0x00018000);
}

/**
  Configures PM_SYNC state hysteresis according to IP recommendation
  for SoC.
**/
VOID
PmcConfigurePmSyncHysteresis (
  VOID
  )
{
  //
  // TGL CPU has a problem with achieving PkgC3 when state hysteresis
  // is set to 8us and PM team has requested to increase this value
  // to 48us for TGL U/Y A0 and TGL H/S P0 steppings
  //
  if ((GetCpuFamily () == EnumCpuTglUltUlx && GetCpuStepping () == EnumTglA0) ||
      (GetCpuFamily () == EnumCpuTglDtHalo && GetCpuStepping () == EnumTglP0)) {
    MmioWrite32 (PmcGetPwrmBase () + R_PMC_PWRM_PM_SYNC_STATE_HYS, 0x00C03180);
  } else {
    MmioWrite32 (PmcGetPwrmBase () + R_PMC_PWRM_PM_SYNC_STATE_HYS, 0x00200840);
  }
}

/**
  This function configures PCH FIVR FET Ramp time config
**/
VOID
PmcFivrFetRampTimeConfig (
  VOID
  )
{
  //
  // Lock V1p05 PHY FET Ramp Time settings
  //
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_EXT_FET_RAMP_CFG, B_PMC_PWRM_EXT_FET_RAMP_CFG_V1P05_PHY_FRT_LOCK | B_PMC_PWRM_EXT_FET_RAMP_CFG_V1P05_IS_FRT_LOCK);
}

/**
  Initialize the Intel Time Sync Gpio
**/
VOID
TimeSyncInit (
  IN  SI_POLICY_PPI                    *SiPolicy
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  PCH_PM_CONFIG     *PmConfig;
  EFI_STATUS        Status;

  DEBUG ((DEBUG_INFO, "TimeSyncInit()"));
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  if (PmConfig->EnableTimedGpio0) {
    GpioEnableTimeSync (0);
    DEBUG ((DEBUG_INFO, "Set Time Sync Gpio 0\n"));
  }
  if (PmConfig->EnableTimedGpio1) {
    GpioEnableTimeSync (1);
    DEBUG ((DEBUG_INFO, "Set Time Sync Gpio 1\n"));
  }
#endif
}

/**
  Get the CPU IOVR ramp duration POR for the SoC

  @retval Ramp duration in the unit of 10us
**/
UINT8
PmcGetCpuIovrRampDuration (
  VOID
  )
{
  return 0;
}

/**
  Pmc miscellaneous configuration at end of PEI
**/
VOID
PmcMiscConfig (
  VOID
  )
{
}


