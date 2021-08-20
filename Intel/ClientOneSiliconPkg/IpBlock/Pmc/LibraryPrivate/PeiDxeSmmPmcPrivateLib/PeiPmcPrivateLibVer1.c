/** @file
  PCH private PEI PMC Library Ver1.

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
#include <Library/BaseMemoryLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/DciPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Register/PmcRegs.h>
#include <Library/PchInfoLib.h>
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
  UINT32                              Data32And;
  UINT32                              Data32Or;
  UINT32                              PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();
  ///
  ///
  /// If SLP_S0 is enabled apply below configuration:
  ///  PWRMBASE + 0x1B1C [29,25,24,23,22,15,13,12] = all 1s
  ///  PWRMBASE + 0x1B1C [14] = 0
  ///  PWRMBASE + 0x1B1C [8:0] to 0x1E
  ///
  /// Other fields in 0x1B1C - HW default
  ///
  Data32And = (UINT32) ~(BIT14 | 0x000001FF);
  Data32Or  = BIT29 | BIT25 | BIT24 | BIT23 | BIT22 | BIT15 | BIT13 | BIT12 | 0x1E;

  MmioAndThenOr32 (
    PchPwrmBase + R_PMC_PWRM_1B1C,
    Data32And,
    Data32Or
    );
  ///
  /// PWRMBASE + 0x1B20 = 0x0005DB01
  ///
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_CPPM_MISC_CFG, 0x0005DB01);

  ///
  ///
  /// If SLP_S0 is enabled apply below configuration:
  ///  PWRMBASE + 0x1B4C [31,30,28,26,19] = all 1s
  ///  PWRMBASE + 0x1B4C [18,20,21,22,25,27] = 0
  ///  PWRMBASE + 0x1B4C [21] = 1b if debug via 4-wire DCI OOB is desired or connected.
  /// For PCH-H and PS_ON Enabled apply below configuration:
  ///  PWRMBASE + 0x1B4C [30] = 0
  ///
  Data32And = (UINT32) ~(BIT30 | BIT27 | BIT25 | BIT22 | BIT21 | BIT20 | BIT18);
  Data32Or  = BIT31 | BIT28 | BIT26 | BIT19;

  if (!(IsPchH () && PmConfig->PsOnEnable)) {
    Data32Or |= BIT30;
  }
  if (!IsDciModphyPgEnabled () || Is4wireDciOobConnected ()) {
    Data32Or |= BIT21;
  }
  MmioAndThenOr32 (
    PchPwrmBase + R_PMC_PWRM_1B4C,
    Data32And,
    Data32Or
    );

  ///
  ///
  /// If SLP_S0 is enabled apply below configuration:
  ///  PWRMBASE + 0x1E4C [22,20,17,15,3] = all 1s
  ///  PWRMBASE + 0x1E4C [0] = 0b
  ///
  Data32Or  = BIT22 | BIT20 | BIT17 | BIT15 | BIT3;
  Data32And = (UINT32)~(BIT0);

  MmioAndThenOr32 (
    PchPwrmBase + R_PMC_PWRM_1E4C,
    Data32And,
    Data32Or
    );
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
  //
  // Not supported on ICL
  //
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
  UINT32 Data32And;

  ///
  /// ModPHY Lane SUS Power Domain Dynamic Gating Enable
  /// MODPHY_PM_CFG3 (0x10C8[30]) = 1
  ///
  Data32Or = B_PMC_PWRM_MODPHY_PM_CFG3_MLSPDDGE;
  Data32And = (UINT32) ~B_PMC_PWRM_MODPHY_PM_CFG3_EFRT;

  ///
  /// If DCI is enabled, skip external ModPHY FET control programming
  ///
  if (!IsDciDebugEnabled ()) {
    ///
    /// MODPHY_PM_CFG3 (0x10C8[29:24]) = 101010, External FET Ramp Time (EFRT)
    /// MODPHY_PM_CFG3 (0x10C8[28]) - 1b, Enable ModPHY FET Control
    ///
    Data32Or  |= (B_PMC_PWRM_MODPHY_PM_CFG3_EMFC | (V_PMC_PWRM_MODPHY_PM_CFG3_EFRT_200US << N_PMC_PWRM_MODPHY_PM_CFG3_EFRT));
  }

  MmioAndThenOr32 (
    PmcGetPwrmBase () + R_PMC_PWRM_MODPHY_PM_CFG3,
    Data32And,
    Data32Or
    );
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
  //
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SLOW_RING, 0x2F8FBB01);
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SLOW_RING2, 0x0280C7E1);

  //
  // Configure which backbone clock wake signals should set the SA indication
  // sent up over the PM_SYNC. This configuration matches the SLOW_RING indication
  // configuration.
  //
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SA, 0x2F8FBB01);
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_EN_CW_SA2, 0x0280C7E1);

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
  // Configure hysteresis for each state indication on PM_SYNC
  // This is recommendation from PMC IP team.
  //
  MmioWrite32 (PmcGetPwrmBase () + R_PMC_PWRM_PM_SYNC_STATE_HYS, 0x00200840);
}

/**
  Configure CPPM Force Alignment Control
**/
VOID
PmcConfigureCppmForceAlignmentControl (
  VOID
  )
{
  UINT32 PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();
  ///
  /// PWRMBASE + 0x1BD0 [31,28,27,15] = 1b, 1b, 1b, 1b, 1b
  /// PWRMBASE + 0x1BD0 [21:16] = 0Ah
  /// PWRMBASE + 0x1BD0 [30] = 1b, done in a separate programming
  ///
  MmioAndThenOr32 (
    PchPwrmBase + R_PMC_PWRM_1BD0,
    (UINT32) ~(0x3F << 16),
    BIT31 | BIT28 | BIT27 | BIT15 | (0x0A << 16)
    );
  MmioOr32 (PchPwrmBase + R_PMC_PWRM_1BD0, BIT30);
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
  // Setting not available in Ver1
  //
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
  return 24;
}


typedef struct {
  UINT32      RegOffset;
  UINT32      BitMask;
} GCR_REG;

/**
  Lock PMC GCR (General Configuration Registers)
**/
VOID
PmcGcrRegLock (
  VOID
  )
{
  EFI_STATUS                Status;
  PMC_IPC_COMMAND_BUFFER    Wbuf;
  UINT32                    PchPwrmBase;
  UINT8                     Index;
  STATIC GCR_REG            GcrReg[] = {
                                        {R_PMC_PWRM_EXT_V1P05_VR_CONFIG, ~0u},
                                        {R_PMC_PWRM_EXT_VNN_VR_CONFIG0,  ~0u},
                                        {R_PMC_PWRM_VCCIN_AUX_CFG1, ~0u},
                                        {R_PMC_PWRM_VCCIN_AUX_CFG2, ~0u},
                                        {R_PMC_PWRM_CFG4, B_PMC_PWRM_CFG4_VCCST_TMR},
                                        {R_PMC_PWRM_CFG4, B_PMC_PWRM_CFG4_CPU_IOVR_RAMP_DUR}
                                       };

  PchPwrmBase = PmcGetPwrmBase ();

  for (Index = 0; Index < (sizeof (GcrReg) / sizeof (GCR_REG)); Index++) {
    ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
    Wbuf.Buf0 = Index;
    Wbuf.Buf1 = (MmioRead32 (PchPwrmBase + GcrReg[Index].RegOffset)) & GcrReg[Index].BitMask;
    Status = PmcSendCommand (V_PMC_PWRM_IPC_GCR_REG_LOCK_CMD, 0, 4, &Wbuf, NULL);
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  Pmc miscellaneous configuration at end of PEI
**/
VOID
PmcMiscConfig (
  VOID
  )
{
  //
  // Lock PMC GCR registers
  //
  PmcGcrRegLock ();
}
