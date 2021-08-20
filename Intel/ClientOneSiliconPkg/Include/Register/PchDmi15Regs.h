/** @file
  Register names for PCH DMI and OP-DMI

Conventions:

  - Register definition format:
    Prefix_[GenerationName]_[ComponentName]_SubsystemName_RegisterSpace_RegisterName
  - Prefix:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register size
    Definitions beginning with "N_" are the bit position
  - [GenerationName]:
    Three letter acronym of the generation is used (e.g. SKL,KBL,CNL etc.).
    Register name without GenerationName applies to all generations.
  - [ComponentName]:
    This field indicates the component name that the register belongs to (e.g. PCH, SA etc.)
    Register name without ComponentName applies to all components.
    Register that is specific to -H denoted by "_PCH_H_" in component name.
    Register that is specific to -LP denoted by "_PCH_LP_" in component name.
  - SubsystemName:
    This field indicates the subsystem name of the component that the register belongs to
    (e.g. PCIE, USB, SATA, GPIO, PMC etc.).
  - RegisterSpace:
    MEM - MMIO space register of subsystem.
    IO  - IO space register of subsystem.
    PCR - Private configuration register of subsystem.
    CFG - PCI configuration space register of subsystem.
  - RegisterName:
    Full register name.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _PCH_DMI15_REGS_H_
#define _PCH_DMI15_REGS_H_

//
// DMI Chipset Configuration Registers (PID:DMI)
//
#define R_PCH_DMI15_PCR_LCAP                       0x204C                      ///< Link Capabilities

#define R_PCH_DMI15_PCR_LCTL                       0x2050                      ///< Link Control
#define B_PCH_DMI15_PCR_LCTL_ES                    BIT7                        ///< Extended Synch
#define B_PCH_DMI15_PCR_LCTL_ASPM                  (BIT1 | BIT0)               ///< Active State Link PM Control
#define V_PCH_DMI15_PCR_LCTL_ASPM_DIS              0x0                         ///< ASPM Disabled
#define V_PCH_DMI15_PCR_LCTL_ASPM_L0S              0x1                         ///< L0s Entry Enabled
#define V_PCH_DMI15_PCR_LCTL_ASPM_L1               0x2                         ///< L1 Entry Enabled
#define V_PCH_DMI15_PCR_LCTL_ASPM_L0SL1            0x3                         ///< L0s and L1 Entry Enabled

#define R_PCH_DMI15_PCR_LSTS                       0x2052                      ///< Link Status

#define R_PCH_DMI15_PCR_LCTL2                      0x2070                      ///< Link Control 2
#define B_PCH_DMI15_PCR_LCTL2_TLS                  0xF                         ///< Target Link Speed

#define R_PCH_DMI15_PCR_CCFG                       0x20D0                      ///< Channel Configuration
#define B_PCH_DMI15_PCR_CCFG_DCGEISMA              BIT15                       ///< Dynamic Clock Gating Enable on ISM Active

#define R_PCH_DMI15_PCR_MPC2                       0x20D4                      ///< Miscellaneous Port Configuration 2
#define B_PCH_DMI15_PCR_MPC2_PLLWAIT               (BIT26 | BIT25 | BIT24)     ///< PLL Wait
#define N_PCH_DMI15_PCR_MPC2_PLLWAIT               24                          ///< PLL Wait
#define V_PCH_DMI15_PCR_MPC2_PLLWAIT_5US           0x1                         ///< PLL Wait = 5us
#define B_PCH_DMI15_PCR_MPC2_RUD                   BIT23                       ///< Recovery Upconfiguration Disable
#define B_PCH_DMI15_PCR_MPC2_GEN2PLLC              BIT21                       ///< GEN2 PLL Coupling
#define B_PCH_DMI15_PCR_MPC2_GEN3PLLC              BIT20                       ///< GEN3 PLL Coupling
#define B_PCH_DMI15_PCR_MPC2_ORCE                  (BIT15 | BIT14)             ///< Offset Re-Calibration Enable
#define N_PCH_DMI15_PCR_MPC2_ORCE                  14                          ///< Offset Re-Calibration Enable
#define V_PCH_DMI15_PCR_MPC2_ORCE_EN_GEN2_GEN3     1                           ///< Enable offset re-calibration for Gen 2 and Gen 3 data rate only.
#define B_PCH_DMI15_PCR_MPC2_TLPF                  BIT9                        ///< Transaction Layer Packet Fast Transmit Mode
#define B_PCH_DMI15_PCR_MPC2_CAM                   BIT8                        ///< DMI Credit Allocated Update Mode


#define R_PCH_DMI15_PCR_MPC                        0x20D8                      ///< Miscellaneous Port Configuration
#define B_PCH_DMI15_PCR_MPC_SRL                    BIT23                       ///< Secured register lock

#define R_PCH_DMI15_PCR_RPDCGEN                    0x20E1                      ///< Root Port Dynamic Clock Gate Enable
#define B_PCH_DMI15_PCR_PTOCGE                     BIT6                        ///< Partition/Trunk Oscillator Clock Gate Enable
#define B_PCH_DMI15_PCR_LCLKREQEN                  BIT5                        ///< Link CLKREQ Enable
#define B_PCH_DMI15_PCR_BBCLKREQEN                 BIT4                        ///< Backbone CLKREQ Enable
#define B_PCH_DMI15_PCR_SRDBCGEN                   BIT2                        ///< Shared Resource Dynamic Backbone Clock Gate Enable
#define B_PCH_DMI15_PCR_RPDLCGEN                   BIT1                        ///< Root Port Dynamic Link Clock Gate Enable
#define B_PCH_DMI15_PCR_RPDBCGEN                   BIT0                        ///< Root Port Dynamic Backbone Clock Gate Enable

#define R_PCH_DMI15_PCR_RPPGEN                     0x20E2                      ///< Root Port Power Gating Enable
#define B_PCH_DMI15_PCR_RPPGEN_SEOSCGE             BIT4                        ///< Sideband Endpoint Oscillator/Side Clock Gating Enable

#define R_PCH_DMI15_PCR_PWRCTL                     0x20E8                      ///< Power Control
#define B_PCH_DMI15_PCR_PWRCTL_DBUPI               BIT15                       ///< De-skew Buffer Unload Pointer Increment
#define B_PCH_DMI15_PCR_PWRCTL_RPSEWL              (BIT3 | BIT2)               ///< Root Port Squelch Exit Wait Latency
#define N_PCH_DMI15_PCR_PWRCTL_RPSEWL              2                           ///< Root Port Squelch Exit Wait Latency
#define V_PCH_DMI15_PCR_PWRCTL_RPSEWL_120NS        0x1                         ///< Root Port Squelch Exit Wait Latency = 120 ns

#define R_PCH_DMI15_PCR_PHYCTL2                    0x20F5                      ///< Physical Layer And AFE Control 2
#define B_PCH_DMI15_PCR_PHYCTL2_TDFT               (BIT7 | BIT6)               ///< Transmit Datapath Flush Timer
#define B_PCH_DMI15_PCR_PHYCTL2_TXCFGCHGWAIT       (BIT5 | BIT4)               ///< Transmit Configuration Change Wait Time
#define B_PCH_DMI15_PCR_PHYCTL2_PXPG3PLLOFFEN      BIT1                        ///< PCI Express GEN3 PLL Off Enable
#define B_PCH_DMI15_PCR_PHYCTL2_PXPG2PLLOFFEN      BIT0                        ///< PCI Express GEN2 PLL Off Enable

#define R_PCH_DMI15_PCR_PHYCTL3                    0x20F6                      ///< Physical Layer And AFE Control 3
#define B_PCH_DMI15_PCR_PHYCTL3_SQDIROVREN         BIT2                        ///< Squelch Direction Override Enable
#define B_PCH_DMI15_PCR_PHYCTL3_SQDIRCTRL          BIT1                        ///< Squelch Direction

#define R_PCH_DMI15_PCR_IOSFSBCS                   0x20F7                      ///< IOSF Sideband Control And Status
#define B_PCH_DMI15_PCR_IOSFSBCS_SCPTCGE           BIT6                        ///< Side Clock Partition/Trunk Clock Gating Enable
#define B_PCH_DMI15_PCR_IOSFSBCS_SIID              (BIT3 | BIT2)               ///< IOSF Sideband Interface Idle Counter

#define R_PCH_DMI15_PCR_UEM                        0x2108                      ///< Uncorrectable Error Mask
#define B_PCH_DMI15_PCR_UEM_URE                    BIT20                       ///< Unsupported Request Error Mask
#define B_PCH_DMI15_PCR_UEM_CM                     BIT15                       ///< Completer Abort Mask
#define B_PCH_DMI15_PCR_UEM_PT                     BIT12                       ///< Poisoned TLP Mask

#define R_PCH_DMI15_PCR_V0CTL                      0x2284                      ///< Virtual channel 0 resource control
#define R_PCH_DMI15_PCR_V0STS                      0x228A                      ///< Virtual channel 0 status

#define R_PCH_DMI15_PCR_V1CTL                      0x2290                      ///< Virtual channel 1 resource control
#define R_PCH_DMI15_PCR_V1STS                      0x2296                      ///< Virtual channel 1 status

#define R_PCH_DMI15_PCR_VMCTL                      0x22B0                      ///< ME Virtual Channel (VCm) resource control
#define R_PCH_DMI15_PCR_VMSTS                      0x22B6                      ///< ME Virtual Channel Resource Status

#define R_PCH_DMI15_PCR_PCIENFTS                   0x2314                      ///< PCI Express NFTS
#define B_PCH_DMI15_PCR_PCIENFTS_G2CCNFTS          0xFF0000                    ///< Gen2 Common Clock N_FTS
#define N_PCH_DMI15_PCR_PCIENFTS_G2CCNFTS          16                          ///< Gen2 Common Clock N_FTS
#define B_PCH_DMI15_PCR_PCIENFTS_G1CCNFTS          0xFF                        ///< Gen1 Common Clock N_FTS
#define N_PCH_DMI15_PCR_PCIENFTS_G1CCNFTS          0                           ///< Gen1 Common Clock N_FTS

#define R_PCH_DMI15_PCR_PCIEL0SC                   0x2318                      ///< PCI Express L0s Control
#define B_PCH_DMI15_PCR_PCIEL0SC_G2ASL0SPL         0xFF000000                  ///< Gen2 Active State L0s Preparation Latency
#define N_PCH_DMI15_PCR_PCIEL0SC_G2ASL0SPL         24                          ///< Gen2 Active State L0s Preparation Latency
#define B_PCH_DMI15_PCR_PCIEL0SC_G1ASL0SPL         0x00FF0000                  ///< Gen1 Active State L0s Preparation Latency
#define N_PCH_DMI15_PCR_PCIEL0SC_G1ASL0SPL         16                          ///< Gen1 Active State L0s Preparation Latency

#define R_PCH_DMI15_PCR_PCIECFG2                   0x2320                      ///< PCI Express Configuration 2
#define B_PCH_DMI15_PCR_PCIECFG2_LBWSSTE           BIT30                       ///< Low Bandwidth Squelch Settling Timer Enable
#define B_PCH_DMI15_PCR_PCIECFG2_CROAOV            BIT24                       ///< Completion Relaxed Ordering Attribute Override Value
#define B_PCH_DMI15_PCR_PCIECFG2_CROAOE            BIT23                       ///< Completion Relaxed Ordering Attribute Override Enable

#define R_PCH_DMI15_PCR_PCIEDBG                    0x2324                      ///< PCI Express Debug And Configuration
#define B_PCH_DMI15_PCR_PCIEDBG_SPCE               BIT5                        ///< Squelch Propagation Control Enable

#define R_PCH_DMI15_PCR_PHYCTL4                    0x2408                      ///< Physical Layer And AFE Control 4
#define B_PCH_DMI15_PCR_PHYCTL4_SQDIS              BIT27                       ///< Squelch Disable

#define R_PCH_DMI15_PCR_PCIEPMECTL                 0x2420                      ///< PCIe PM Extension Control
#define B_PCH_DMI15_PCR_PCIEPMECTL_DLSULPPGE       BIT30                       ///< Disabled, Detect and L23_Rdy State PHY Lane Power Gating Enable
#define B_PCH_DMI15_PCR_PCIEPMECTL_DLSULDLSD       BIT29                       ///< Disabled, Detect, L23_Rdy State,Un-Configured Lane and Down-Configured Lane Squelch Disable
#define B_PCH_DMI15_PCR_PCIEPMECTL_IPIEP           BIT21                       ///< IP-Inaccessible Entry Policy
#define B_PCH_DMI15_PCR_PCIEPMECTL_IPACPE          BIT20                       ///< IP-Accessible Context Propagation Enable

#define R_PCH_DMI15_PCR_PCIEPMECTL2                0x2424                      ///< PCIe PM Extension Control 2
#define B_PCH_DMI15_PCR_PCIEPMECTL2_PHYCLPGE       BIT11                       ///< PHY Common Lane Power Gating Enable
#define B_PCH_DMI15_PCR_PCIEPMECTL2_L1SPHYDLPGE    BIT9                        ///< L1 State PHY Data Lane Power Gating Enable
#define B_PCH_DMI15_PCR_PCIEPMECTL2_L1SCPGE        BIT4                        ///< L1 State Controller Power Gating Enable

#define R_PCH_DMI15_PCR_PCE                        0x2428                      ///< Power Control Enable
#define B_PCH_DMI15_PCR_PCE_HAE                    BIT5                        ///< Hardware Autonomous Enable
#define B_PCH_DMI15_PCR_PCE_SE                     BIT3                        ///< Sleep Enable
#define B_PCH_DMI15_PCR_PCE_PMCRE                  BIT0                        ///< PMC Request Enable

#define R_PCH_DMI15_PCR_EQCFG1                     0x2450                      ///< Equalization Configuration 1
#define B_PCH_DMI15_PCR_EQCFG1_RTLEPCEB            BIT16                       ///< Remote Transmit Link Equalization Preset/Coefficient Evaluation Bypass

#define R_PCH_DMI15_PCR_LTCO1                      0x2470                      ///< Local Transmitter Coefficient Override 1
#define R_PCH_DMI15_PCR_LTCO2                      0x2474                      ///< Local Transmitter Coefficient Override 2
#define B_PCH_DMI15_PCR_L1357TCOE                  BIT25                       ///< Lane 1/3 Transmitter Coefficient Override Enable
#define B_PCH_DMI15_PCR_L0246TCOE                  BIT24                       ///< Lane 0/2 Transmitter Coefficient Override Enable
#define B_PCH_DMI15_PCR_L1357TPOSTCO               0x00FC0000                  ///< Lane 1/3 Transmitter Post-Cursor Coefficient Override mask
#define N_PCH_DMI15_PCR_L1357TPOSTCO               18                          ///< Lane 1/3 Transmitter Post-Cursor Coefficient Override value offset
#define B_PCH_DMI15_PCR_L1357TPRECO                0x0003F000                  ///< Lane 1/3 Transmitter Pre-Cursor Coefficient Override mask
#define N_PCH_DMI15_PCR_L1357TPRECO                12                          ///< Lane 1/3 Transmitter Pre-Cursor Coefficient Override value offset
#define B_PCH_DMI15_PCR_L0246TPOSTCO               0x00000FC0                  ///< Lane 0/2 Transmitter Post-Cursor Coefficient Override mask
#define N_PCH_DMI15_PCR_L0246TPOSTCO               6                           ///< Lane 0/2 Transmitter Post-Cursor Coefficient Override value offset
#define B_PCH_DMI15_PCR_L0246TPRECO                0x0000003F                  ///< Lane 0/2 Transmitter Pre-Cursor Coefficient Override mask
#define N_PCH_DMI15_PCR_L0246TPRECO                0                           ///< Lane 0/2 Transmitter Pre-Cursor Coefficient Override value offset

#define R_PCH_DMI15_PCR_G3L0SCTL                   0x2478                      ///< GEN3 L0s Control
#define B_PCH_DMI15_PCR_G3L0SCTL_G3ASL0SPL         0xFF000000                  ///< Gen3 Active State L0s Preparation Latency
#define N_PCH_DMI15_PCR_G3L0SCTL_G3ASL0SPL         24                          ///< Gen3 Active State L0s Preparation Latency
#define B_PCH_DMI15_PCR_G3L0SCTL_G3CCNFTS          0xFF                        ///< Gen3 Common Clock N_FTS
#define N_PCH_DMI15_PCR_G3L0SCTL_G3CCNFTS          0                           ///< Gen3 Common Clock N_FTS

#define R_PCH_DMI15_PCR_UPHWAWC                    0x249C                      ///< Upstream Port HW Autonomous Width Control
#define B_PCH_DMI15_PCR_UPHWAWC_TS3TW              (BIT15 | BIT14 | BIT13)     ///< Thermal Sensor 3 Target Width
#define N_PCH_DMI15_PCR_UPHWAWC_TS3TW              13                          ///< Thermal Sensor 3 Target Width
#define B_PCH_DMI15_PCR_UPHWAWC_TS2TW              (BIT12 | BIT11 | BIT10)     ///< Thermal Sensor 2 Target Width
#define N_PCH_DMI15_PCR_UPHWAWC_TS2TW              10                          ///< Thermal Sensor 2 Target Width
#define B_PCH_DMI15_PCR_UPHWAWC_TS1TW              (BIT9 | BIT8 | BIT7)        ///< Thermal Sensor 1 Target Width
#define N_PCH_DMI15_PCR_UPHWAWC_TS1TW              7                           ///< Thermal Sensor 1 Target Width
#define B_PCH_DMI15_PCR_UPHWAWC_TS0TW              (BIT6 | BIT5 | BIT4)        ///< Thermal Sensor 0 Target Width
#define N_PCH_DMI15_PCR_UPHWAWC_TS0TW              4                           ///< Thermal Sensor 0 Target Width
#define B_PCH_DMI15_PCR_UPHWAWC_TSAWEN             BIT0                        ///< Thermal Sensor Autonomous Width Enable

#define R_PCH_DMI15_PCR_CTRL1                      0x24A0                      ///< Control 1
#define B_PCH_DMI15_PCR_CTRL1_MRSCDIS              BIT21                       ///< MEUMA Root Space Check Disable
#define B_PCH_DMI15_PCR_CTRL1_L0SPFCUF             (BIT16 | BIT15)             ///< L0s Periodic Flow Control Update Frequency
#define B_PCH_DMI15_PCR_CTRL1_L1PL                 (BIT11 | BIT10 | BIT9)      ///< DMI L1 Preparation Latency
#define N_PCH_DMI15_PCR_CTRL1_L1PL                 9                           ///< DMI L1 Preparation Latency
#define V_PCH_DMI15_PCR_CTRL1_L1PL_4US             0x3                         ///< DMI L1 Preparation Latency = 1us
#define B_PCH_DMI15_PCR_CTRL1_TCUAPF               BIT6                        ///< Transaction Credit Update Arbitration Performance Fix
#define B_PCH_DMI15_PCR_CTRL1_PSS                  BIT3                        ///< IOSF Primary SAI Select
#define B_PCH_DMI15_PCR_CTRL1_UTPB                 BIT0                        ///< Unsupported Transaction Policy Bit

#define R_PCH_DMI15_PCR_CTRL2                      0x24A4                      ///< Control 2
#define B_PCH_DMI15_PCR_CTRL2_DLDRSP               BIT13                       ///< DMI Link Data Rate Sustain Policy
#define B_PCH_DMI15_PCR_CTRL2_CPGEXLCWDIS          BIT5                        ///< CPG Exit Link Clock Wake Disable

#define R_PCH_DMI15_PCR_L0P0P1PCM                  0x2500                      ///< Lane 0 P0 And P1 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P1P2P3PCM                0x2504                      ///< Lane 0 P1, P2 And P3 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P3P4PCM                  0x2508                      ///< Lane 0 P3 And P4 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P5P6PCM                  0x250C                      ///< Lane 0 P5 And P6 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P6P7P8PCM                0x2510                      ///< Lane 0 P6, P7 And P8 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P8P9PCM                  0x2514                      ///< Lane 0 P8 And P9 Preset-Coefficient Mapping
#define R_PCH_DMI15_PCR_L0P10PCM                   0x2518                      ///< Lane 0 P10 Preset-Coefficient Mapping ()
#define R_PCH_DMI15_PCR_L0LFFS                     0x251C                      ///< Lane 0 LF And FS

#define R_PCH_DMI15_PCR_LTCO3                      0x2598                      ///< Local Transmitter Coefficient Override 3
#define R_PCH_DMI15_PCR_LTCO4                      0x259C                      ///< Local Transmitter Coefficient Override 4

#define R_PCH_DMI15_PCR_CWBCTL                     0x2820                      ///< Central Write Buffer Control
#define B_PCH_DMI15_PCR_CWBCTL_CWBE                BIT0                        ///< Central Write Buffer Enable

#define R_PCH_DMI15_PCR_L01EC                      0x2A3C                      ///< Lane 0 and Lane 1 Equalization Control
#define R_PCH_DMI15_PCR_L23EC                      0x2A40                      ///< Lane 2 and Lane 3 Equalization Control
#define R_PCH_DMI15_PCR_L45EC                      0x2A44                      ///< Lane 4 and Lane 5 Equalization Control
#define R_PCH_DMI15_PCR_L67EC                      0x2A48                      ///< Lane 6 and Lane 7 Equalization Control
#define B_PCH_DMI15_PCR_UPL1357TP                  0x0F000000                  ///< Upstream Port Lane 1/3/5/7 Transmitter Preset mask
#define N_PCH_DMI15_PCR_UPL1357TP                  24                          ///< Upstream Port Lane 1/3/5/7 Transmitter Preset value offset
#define B_PCH_DMI15_PCR_UPL0246TP                  0x00000F00                  ///< Upstream Port Lane 0/2/4/6 Transmitter Preset mask
#define N_PCH_DMI15_PCR_UPL0246TP                  8                           ///< Upstream Port Lane 0/2/4/6 Transmitter Preset value offset
#define V_PCH_DMI15_PCR_UPL0TP                     7                           ///< Upstream Port Lane 0 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL1TP                     7                           ///< Upstream Port Lane 1 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL2TP                     7                           ///< Upstream Port Lane 2 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL3TP                     7                           ///< Upstream Port Lane 3 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL4TP                     7                           ///< Upstream Port Lane 4 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL5TP                     7                           ///< Upstream Port Lane 5 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL6TP                     7                           ///< Upstream Port Lane 6 Transmitter Preset value
#define V_PCH_DMI15_PCR_UPL7TP                     7                           ///< Upstream Port Lane 7 Transmitter Preset value


#endif
