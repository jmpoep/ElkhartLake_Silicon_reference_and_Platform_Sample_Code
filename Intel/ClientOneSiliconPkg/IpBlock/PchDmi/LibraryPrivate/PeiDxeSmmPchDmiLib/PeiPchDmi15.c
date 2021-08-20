/** @file
  This file contains functions for PCH DMI configuration for SIP15

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PeiPchDmiLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchDmi15Regs.h>

/**
  Get PCH DMI SIP15 Virtual Channel Control and Status registers

  @param[in]  Vc                   The virtual channel number for programing
  @param[out] PchDmiVcCtlAddress      DMI Virtual Channel Control register address
  @param[out] PchDmiVcStsAddress      DMI Virtual Channel Status register address
**/
VOID
PchDmi15VcRegs (
  IN   PCH_DMI_VC_TYPE  Vc,
  OUT  UINT16           *PchDmiVcCtlAddress,
  OUT  UINT16           *PchDmiVcStsAddress
  )
{
  switch (Vc) {
    case PchDmiVcTypeVc0:
      *PchDmiVcCtlAddress = R_PCH_DMI15_PCR_V0CTL;
      *PchDmiVcStsAddress = R_PCH_DMI15_PCR_V0STS;
      break;

    case PchDmiVcTypeVc1:
      *PchDmiVcCtlAddress = R_PCH_DMI15_PCR_V1CTL;
      *PchDmiVcStsAddress = R_PCH_DMI15_PCR_V1STS;
      break;

    case PchDmiVcTypeVcm:
      *PchDmiVcCtlAddress = R_PCH_DMI15_PCR_VMCTL;
      *PchDmiVcStsAddress = R_PCH_DMI15_PCR_VMSTS;
      break;

    case PchDmiVcTypeMax:
      *PchDmiVcCtlAddress = 0;
      *PchDmiVcStsAddress = 0;
      ASSERT (FALSE);
  }
}

/**
  This function performs basic DMI initialization.
**/
STATIC
VOID
PchDmiBasicInit (
  VOID
  )
{
  //
  // Configure Uncorrectable Error Mask
  // Set the Completer Abort Mask, Poisoned TLP and Unsupported Request Error Mask
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_UEM,
    ~0u,
    (B_PCH_DMI15_PCR_UEM_URE | B_PCH_DMI15_PCR_UEM_CM | B_PCH_DMI15_PCR_UEM_PT)
    );

  //
  // Configure Transmit Datapath Flush Timer
  //  00b - Wait for 4 clocks prior to initiating rate or powerstate change.
  // Configure Transmit Configuration Change Wait Time
  //  00b - 128ns for GEN1 and GEN2 mode. 256ns for GEN3 mode.
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_PHYCTL2,
    (UINT8) ~(B_PCH_DMI15_PCR_PHYCTL2_TDFT | B_PCH_DMI15_PCR_PHYCTL2_TXCFGCHGWAIT),
    0
    );

  //
  // Configure Squelch Direction settings
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_PHYCTL3,
    (UINT8) ~0,
    (B_PCH_DMI15_PCR_PHYCTL3_SQDIROVREN | B_PCH_DMI15_PCR_PHYCTL3_SQDIRCTRL)
    );

  //
  // Set Recovery Upconfiguration Disable
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_MPC2,
    ~0u,
    B_PCH_DMI15_PCR_MPC2_RUD
    );

  //
  // Set De-skew Buffer Unload Pointer Increment
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PWRCTL,
    ~0u,
    B_PCH_DMI15_PCR_PWRCTL_DBUPI
    );
}

/**
  Configure DMI clock gating.
  This function must be called before ASPM is enabled
**/
STATIC
VOID
ConfigurePchDmiClockGating (
  VOID
  )
{
  //
  // Enable Dynamic Clock Gating on ISM Active
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_CCFG,
    ~0u,
    B_PCH_DMI15_PCR_CCFG_DCGEISMA
    );

  //
  // Enable below clock gating settings:
  // - Partition/Trunk Oscillator Clock Gate Enable
  // - Link CLKREQ Enable
  // - Backbone CLKREQ Enable
  // - Shared Resource Dynamic Backbone Clock Gate Enable
  // - Root Port Dynamic Link Clock Gate Enable
  // - Root Port Dynamic Backbone Clock Gate Enable
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_RPDCGEN,
    (UINT8)~0,
    (B_PCH_DMI15_PCR_PTOCGE | B_PCH_DMI15_PCR_LCLKREQEN | B_PCH_DMI15_PCR_BBCLKREQEN |
    B_PCH_DMI15_PCR_SRDBCGEN | B_PCH_DMI15_PCR_RPDLCGEN | B_PCH_DMI15_PCR_RPDBCGEN)
    );

  //
  // Enable Side Clock Partition/Trunk Clock Gating
  // Set IOSF Sideband Interface Idle Counter to 00b - Wait for
  // 32 idle clocks before allowing trunk clock gating.
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_IOSFSBCS,
    (UINT8)~B_PCH_DMI15_PCR_IOSFSBCS_SIID,
    B_PCH_DMI15_PCR_IOSFSBCS_SCPTCGE
    );

  //
  // Enable Sideband Endpoint Oscillator/Side Clock Gating
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_RPPGEN,
    (UINT8)~0,
    B_PCH_DMI15_PCR_RPPGEN_SEOSCGE
    );
}

/**
  Configure DMI link power management.
  This function must be called before ASPM is enabled
**/
STATIC
VOID
ConfigurePchDmiLinkPowerManagement (
  VOID
  )
{
  //
  // Configure DMI L1 Preparation Latency to 4us - this is the time link layer has to
  // indicate IDLE before the link initialization and control logic enters Active State L1.
  // Be careful not to touch first byte of this register as CTRL1.PSS is RWO.
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_CTRL1 + 1,
    (UINT8)~(B_PCH_DMI15_PCR_CTRL1_L1PL >> 8),
    (V_PCH_DMI15_PCR_CTRL1_L1PL_4US << N_PCH_DMI15_PCR_CTRL1_L1PL) >> 8
    );

  //
  // Configure Gen1 and Gen2 Active State L0s Preparation Latency - time that link layer has to
  // indicate IDLE before the link initialization and control logic enters L0s
  // Set it to 0x14 clocks
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIEL0SC,
    (UINT32)~(B_PCH_DMI15_PCR_PCIEL0SC_G2ASL0SPL | B_PCH_DMI15_PCR_PCIEL0SC_G1ASL0SPL),
    ((0x14 << N_PCH_DMI15_PCR_PCIEL0SC_G2ASL0SPL) |
    (0x14 << N_PCH_DMI15_PCR_PCIEL0SC_G1ASL0SPL))
    );

  //
  // Configure Gen1 and Gen2 Common Clock N_FTS
  // - 0x38 for GEN1
  // - 0x70 for GEN2
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIENFTS,
    (UINT32)~(B_PCH_DMI15_PCR_PCIENFTS_G2CCNFTS | B_PCH_DMI15_PCR_PCIENFTS_G1CCNFTS),
    ((0x70 << N_PCH_DMI15_PCR_PCIENFTS_G2CCNFTS) |
    (0x38 << N_PCH_DMI15_PCR_PCIENFTS_G1CCNFTS))
    );

  //
  // Configure Gen3 Active State L0s Preparation Latency - time that link layer has to
  // indicate IDLE before the link initialization and control logic enters L0s
  // Set it to 0x28 clocks
  //
  // Configure Gen3 Common Clock N_FTS to 0x2c
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_G3L0SCTL,
    (UINT32)~(B_PCH_DMI15_PCR_G3L0SCTL_G3ASL0SPL | B_PCH_DMI15_PCR_G3L0SCTL_G3CCNFTS),
    ((0x28 << N_PCH_DMI15_PCR_G3L0SCTL_G3ASL0SPL) |
    (0x2c << N_PCH_DMI15_PCR_G3L0SCTL_G3CCNFTS))
    );

  //
  // Configure L0s Exit Latency to 0x3 (128ns - 256ns)
  // Configure L1s Exit Latency to 0x4 (8us - 16us)
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI_PCR_LCAP,
    (UINT32) ~(B_PCH_DMI_PCR_LCAP_EL1 | B_PCH_DMI_PCR_LCAP_EL0),
    ((V_PCH_DMI_PCR_LCAP_EL1_8US_16US << N_PCH_DMI_PCR_LCAP_EL1) |
    (V_PCH_DMI_PCR_LCAP_EL0_256NS_512NS << N_PCH_DMI_PCR_LCAP_EL0))
    );
}

/**
  Configure DMI Squelch Power Management.
**/
STATIC
VOID
ConfigurePchDmiSquelchPowerManagement (
  VOID
  )
{
  //
  // Enable Low Bandwidth Squelch Settling Timer
  // Set this before enabling any of the squelch power management
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIECFG2,
    ~0u,
    B_PCH_DMI15_PCR_PCIECFG2_LBWSSTE
    );

  //
  // Enable Squelch propagation control
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIEDBG,
    ~0u,
    B_PCH_DMI15_PCR_PCIEDBG_SPCE
    );

  //
  // Configure Root Port Squelch Exit Wait Latency to 120ns
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PWRCTL,
    (UINT32) ~B_PCH_DMI15_PCR_PWRCTL_RPSEWL,
    V_PCH_DMI15_PCR_PWRCTL_RPSEWL_120NS << N_PCH_DMI15_PCR_PWRCTL_RPSEWL
    );
}

/**
  Configure DMI PLL Shutdown.
**/
STATIC
VOID
ConfigurePchDmiPllShutdown (
  VOID
  )
{
  //
  // Configure PLL Wait to 5us.This is amount of time to wait from gating the link clock
  // before turning off the PLL.
  // Enable Gen2 PLL coupling (leave disabled for CNL-PCH-H-Ax)
  // Enable Gen3 PLL coupling
  // This needs to be done before enabling PLL shutdown
  //
  if (IsCnlPch () && (PchStepping () < PCH_B0)) {
    PchPcrAndThenOr32 (
      PID_DMI, R_PCH_DMI15_PCR_MPC2,
      (UINT32) ~(B_PCH_DMI15_PCR_MPC2_PLLWAIT | B_PCH_DMI15_PCR_MPC2_GEN2PLLC),
      ((V_PCH_DMI15_PCR_MPC2_PLLWAIT_5US << N_PCH_DMI15_PCR_MPC2_PLLWAIT) |
      B_PCH_DMI15_PCR_MPC2_GEN3PLLC)
      );
  } else {
    PchPcrAndThenOr32 (
      PID_DMI, R_PCH_DMI15_PCR_MPC2,
      (UINT32) ~B_PCH_DMI15_PCR_MPC2_PLLWAIT,
      ((V_PCH_DMI15_PCR_MPC2_PLLWAIT_5US << N_PCH_DMI15_PCR_MPC2_PLLWAIT) |
      B_PCH_DMI15_PCR_MPC2_GEN2PLLC | B_PCH_DMI15_PCR_MPC2_GEN3PLLC)
      );
  }

  //
  // Enable PCI Express GEN2 and GEN3 PLL Off
  // If enabled and no devices require the use of the PXP PLL clock outputs,
  // the PXP PLL can be shutdown.
  //
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI15_PCR_PHYCTL2,
    (UINT8)~0,
    (B_PCH_DMI15_PCR_PHYCTL2_PXPG3PLLOFFEN | B_PCH_DMI15_PCR_PHYCTL2_PXPG2PLLOFFEN)
    );
}

/**
  Configure DMI Power Gating.
  This needs to done before enabling ASPM L1
**/
STATIC
VOID
ConfigurePchDmiPowerGating (
  VOID
  )
{
  //
  // Disable the squelch circuitry for all lanes
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PHYCTL4,
    ~0u,
    B_PCH_DMI15_PCR_PHYCTL4_SQDIS
    );

  //
  // Disable IP-Accessible Context Propagation
  // Enable PHY Lane Power Gating when link resides in LTSSM Disabled, Detect or L23_Rdy state
  // Enable disabling squelch when the link resides in LTSSM Disabled, L23_Rdy state or if the lane is unconfigured
  // Enable IP-Inaccessible Entry Policy
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIEPMECTL,
    (UINT32)~B_PCH_DMI15_PCR_PCIEPMECTL_IPACPE,
    (B_PCH_DMI15_PCR_PCIEPMECTL_DLSULPPGE | B_PCH_DMI15_PCR_PCIEPMECTL_DLSULDLSD | B_PCH_DMI15_PCR_PCIEPMECTL_IPIEP)
    );

  //
  // Enable L1 State Controller Power Gating
  // Enable L1 State PHY Data Lane Power Gating
  // Enable PHY Common Lane Power Gating
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCIEPMECTL2,
    ~0u,
    B_PCH_DMI15_PCR_PCIEPMECTL2_PHYCLPGE | B_PCH_DMI15_PCR_PCIEPMECTL2_L1SPHYDLPGE | B_PCH_DMI15_PCR_PCIEPMECTL2_L1SCPGE
    );

  //
  // Set Hardware Autonomous Enable,
  // PMC Request Enable and Sleep Enable
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_PCE,
    (UINT32)~B_PCH_DMI15_PCR_PCE_PMCRE,
    B_PCH_DMI15_PCR_PCE_HAE | B_PCH_DMI15_PCR_PCE_SE
    );

  //
  // CPG Exit Link Clock Wake Disable
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_CTRL2,
    ~0u,
    B_PCH_DMI15_PCR_CTRL2_CPGEXLCWDIS
    );
}

/**
  This function configures ASPM on DMI

  @param[in] SiPolicyPpi The PCH Policy PPI instance
**/
STATIC
VOID
ConfigurePchDmiAspm (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  )
{
  UINT16                        Data16And;
  UINT16                        Data16Or;
  PCH_PCIE_ASPM_CONTROL         DmiAspmCtrl;
  EFI_STATUS                    Status;
  PCH_DMI_CONFIG                *PchDmiConfig;
  PCH_GENERAL_CONFIG            *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPchDmiConfigGuid, (VOID *) &PchDmiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Enable DMI ASPM
  //
  if (PchGeneralConfig->LegacyIoLowLatency) {
    DmiAspmCtrl = PchPcieAspmDisabled;
  } else {
    DmiAspmCtrl = PchDmiConfig->DmiAspmCtrl;
  }

  Data16And = (UINT16)~B_PCH_DMI15_PCR_LCTL_ASPM;

  if ((DmiAspmCtrl == PchPcieAspmAutoConfig) || (DmiAspmCtrl == PchPcieAspmL0sL1)) {
    //
    // Enable L0s/L1 on DMI
    //
    Data16Or = V_PCH_DMI15_PCR_LCTL_ASPM_L0SL1;
  } else if (DmiAspmCtrl == PchPcieAspmL0s) {
    //
    // Enable L0s Entry only
    //
    Data16Or = V_PCH_DMI15_PCR_LCTL_ASPM_L0S;

  } else if (DmiAspmCtrl == PchPcieAspmL1) {
    //
    // Enable L1 Entry only
    //
    Data16Or = V_PCH_DMI15_PCR_LCTL_ASPM_L1;
  } else {
    //
    // ASPM Disabled
    //
    Data16Or  = V_PCH_DMI15_PCR_LCTL_ASPM_DIS;
  }

  //
  // Configue DMI ASPM
  //
  PchPcrAndThenOr16 (
    PID_DMI, R_PCH_DMI15_PCR_LCTL,
    Data16And,
    Data16Or
    );

}

/**
  This function performs early PCH-H DMI SIP15 init.
  It must be called before any upstream bus master transactions are enabled
**/
VOID
PchDmi15EarlyInit (
  VOID
  )
{
  //
  // Enable Transaction Layer Packet Fast Transmit Mode and
  // DMI Credit Allocated Update Mode
  //
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_MPC2,
    ~0u,
    B_PCH_DMI15_PCR_MPC2_TLPF | B_PCH_DMI15_PCR_MPC2_CAM
    );
}


/**
  This function configures DMI SIP15.

  @param[in] SiPolicyPpi The PCH Policy PPI instance
**/
VOID
PchDmi15Init (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  )
{
  PchDmiBasicInit ();
  ConfigurePchDmiClockGating ();
  ConfigurePchDmiLinkPowerManagement ();
  // DMI Thermal Throttling is configure in Thermal module (ThermalInit())
  ConfigurePchDmiSquelchPowerManagement ();
  ConfigurePchDmiPllShutdown ();
  ConfigurePchDmiPowerGating ();
  ConfigurePchDmiAspm (SiPolicyPpi);
}

/**
  This function will perform necessary programming before changing PCH DMI link speed to Gen2 or Gen3.

  @param[in] DmiSpeedGen              PCH DMI speed Gen (1-Gen1, 2-Gen2, 3-Gen3) to which link is going to be trained
**/
STATIC
VOID
PchDmiBeforeLinkSpeedChange (
  UINT8    DmiSpeedGen
  )
{
  UINT32            Data32Or;
  UINT32            Data32And;
  UINTN             LaneIndex;

  static CONST UINT8  DmiUpPortTranPreset[] = {
    V_PCH_DMI15_PCR_UPL0TP,
    V_PCH_DMI15_PCR_UPL1TP,
    V_PCH_DMI15_PCR_UPL2TP,
    V_PCH_DMI15_PCR_UPL3TP,
    V_PCH_DMI15_PCR_UPL4TP,
    V_PCH_DMI15_PCR_UPL5TP,
    V_PCH_DMI15_PCR_UPL6TP,
    V_PCH_DMI15_PCR_UPL7TP
  };
  static CONST UINT16 DmiLaneEqualCntrReg[] = {
    R_PCH_DMI15_PCR_L01EC,
    R_PCH_DMI15_PCR_L23EC,
    R_PCH_DMI15_PCR_L45EC,
    R_PCH_DMI15_PCR_L67EC
  };
  if (DmiSpeedGen > 2) {
    for (LaneIndex = 0; LaneIndex < PCH_MAX_DMI_LANES; LaneIndex += 2) {
      Data32And = ~(UINT32) (B_PCH_DMI15_PCR_UPL0246TP | B_PCH_DMI15_PCR_UPL1357TP);
      Data32Or = (((UINT32)DmiUpPortTranPreset[LaneIndex] << N_PCH_DMI15_PCR_UPL0246TP) |
                  ((UINT32)DmiUpPortTranPreset[LaneIndex + 1] << N_PCH_DMI15_PCR_UPL1357TP));

      PchPcrAndThenOr32 (PID_DMI, DmiLaneEqualCntrReg[LaneIndex/2], Data32And, Data32Or);
    }

    //
    // Set Remote Transmit Link Equalization Preset/Coefficient Evaluation Bypass
    //
    PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI15_PCR_EQCFG1, ~0u, B_PCH_DMI15_PCR_EQCFG1_RTLEPCEB);
    //
    // Before training to GEN3 Configure Lan0 P0-P10 Preset Coefficient mapping
    // based on recommendation for PCH DMI
    //
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P0P1PCM, 0x6C8018);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P1P2P3PCM, 0x1C180685);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P3P4PCM, 0x20100);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P5P6PCM, 0x47000DD);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P6P7P8PCM, 0x181835C0);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P8P9PCM, 0x15B104);
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0P10PCM, 0xA016);
    //
    // Configure Lane0 Local PHY Full Swing and Low Frequency Value
    //
    PchPcrWrite32 (PID_DMI, R_PCH_DMI15_PCR_L0LFFS, 0x200A);
  }

  ///
  /// Set  DMI Link Data Rate Sustain Policy (DLDRSP)
  /// When set, DMI will always train to the highest supported link speed common to both sides of the link.
  /// DLDRSP should be set to 1 when the Target Link Speed is still indicating GEN1
  ///
  PchPcrAndThenOr32 (
    PID_DMI, R_PCH_DMI15_PCR_CTRL2,
    ~0u,
    B_PCH_DMI15_PCR_CTRL2_DLDRSP
    );
}

/**
  The function set the Target Link Speed in PCH-H to DMI GEN 3.

  @param[in] TargetLinkSpeed        Target Link Speed
                                    2: GEN2
                                    3: GEN3
**/
VOID
PchDmi15SetTargetLinkSpeed (
  IN  UINT8                 TargetLinkSpeed
  )
{

  if ((TargetLinkSpeed < 2) || (TargetLinkSpeed > 3)) {
    ASSERT (FALSE);
    return;
  }

  ASSERT (IsPchWithPdmi ());

  DEBUG ((DEBUG_INFO, "PchDmi15SetTargetLinkSpeed(%d) Start\n", TargetLinkSpeed));

  PchDmiBeforeLinkSpeedChange (TargetLinkSpeed);

  ///
  /// PCH BIOS Spec, Section 7
  /// Configure DMI Link Speed (for PCH With DMI ONLY)
  /// Please refer to the System Agent BIOS Writer's Guide on Supported Link Speed
  /// field in Link Capabilities register in CPU complex. (Done in SA code)
  /// If target link speed is GEN2, it can be configured as early as possible.
  /// Else if the target link speed is GEN3, refer to PCH BIOS spec for further programming requirement
  ///
  /// Link speed can be set to GEN2/3 if both LCAP in CPU complex (Done in SA code)
  /// and on PCH side indicates such capability.
  /// DMI Target Link Speed (TLS) is configurable on PCH side in Link Control 2 register (LCTL2)
  ///
  if ((PchPcrRead32 (PID_DMI, R_PCH_DMI_PCR_LCAP) & B_PCH_DMI_PCR_LCAP_MLS) >= TargetLinkSpeed) {
    ///
    /// Set Target Link Speed (TLS)
    ///
    PchPcrAndThenOr8 (PID_DMI, R_PCH_DMI15_PCR_LCTL2, (UINT8)~B_PCH_DMI15_PCR_LCTL2_TLS, TargetLinkSpeed);
    ///
    /// Please refer to the System Agent BIOS Writer's Guide to perform DMI Link Retrain after
    /// configures new DMI Link Speed. (Done in SA code)
    ///
  }
  DEBUG ((DEBUG_INFO, "PchDmi15SetTargetLinkSpeed(%d) End\n", TargetLinkSpeed));
}
