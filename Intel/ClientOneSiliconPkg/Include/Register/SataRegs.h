/** @file
  Register names for SATA controllers

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
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _SATA_REGS_H_
#define _SATA_REGS_H_

//
//  SATA Controller Common Registers
//
#define R_SATA_CFG_AHCI_BAR                 0x24
#define B_SATA_CFG_AHCI_BAR_BA              0xFFFFF800
#define V_SATA_CFG_AHCI_BAR_LENGTH          0x800
#define N_SATA_CFG_AHCI_BAR_ALIGNMENT       11
#define V_SATA_CFG_AHCI_BAR_LENGTH_512K     0x80000
#define N_SATA_CFG_AHCI_BAR_ALIGNMENT_512K  19
#define R_SATA_CFG_PID                      0x70
#define V_SATA_CFG_PID_NEXT_0               0xB000
#define V_SATA_CFG_PID_NEXT_1               0xA800
#define R_SATA_CFG_PMCS                     0x74
#define R_SATA_CFG_MAP                      0x90
#define B_SATA_CFG_MAP_PCD                  0xFF
#define N_SATA_CFG_MAP_SPD                  16
#define B_SATA_CFG_MAP_SPD7                 BIT23
#define B_SATA_CFG_MAP_SPD6                 BIT22
#define B_SATA_CFG_MAP_SPD5                 BIT21
#define B_SATA_CFG_MAP_SPD4                 BIT20
#define B_SATA_CFG_MAP_SPD3                 BIT19
#define B_SATA_CFG_MAP_SPD2                 BIT18
#define B_SATA_CFG_MAP_SPD1                 BIT17
#define B_SATA_CFG_MAP_SPD0                 BIT16
#define B_SATA_CFG_MAP_PORT7_PCD            BIT7
#define B_SATA_CFG_MAP_PORT6_PCD            BIT6
#define B_SATA_CFG_MAP_PORT5_PCD            BIT5
#define B_SATA_CFG_MAP_PORT4_PCD            BIT4
#define B_SATA_CFG_MAP_PORT3_PCD            BIT3
#define B_SATA_CFG_MAP_PORT2_PCD            BIT2
#define B_SATA_CFG_MAP_PORT1_PCD            BIT1
#define B_SATA_CFG_MAP_PORT0_PCD            BIT0
#define R_SATA_CFG_PCS                      0x94
#define B_SATA_CFG_PCS_P7P                  BIT23
#define B_SATA_CFG_PCS_P6P                  BIT22
#define B_SATA_CFG_PCS_P5P                  BIT21
#define B_SATA_CFG_PCS_P4P                  BIT20
#define B_SATA_CFG_PCS_P3P                  BIT19
#define B_SATA_CFG_PCS_P2P                  BIT18
#define B_SATA_CFG_PCS_P1P                  BIT17
#define B_SATA_CFG_PCS_P0P                  BIT16
#define B_SATA_CFG_PCS_P7E                  BIT7
#define B_SATA_CFG_PCS_P6E                  BIT6
#define B_SATA_CFG_PCS_P5E                  BIT5
#define B_SATA_CFG_PCS_P4E                  BIT4
#define B_SATA_CFG_PCS_P3E                  BIT3
#define B_SATA_CFG_PCS_P2E                  BIT2
#define B_SATA_CFG_PCS_P1E                  BIT1
#define B_SATA_CFG_PCS_P0E                  BIT0
#define B_SATA_CFG_PCS_PXE_MASK             0xFF
#define R_SATA_CFG_SATAGC                   0x9C
#define B_SATA_CFG_SATAGC_SMS_MASK          BIT16
#define N_SATA_CFG_SATAGC_SMS_MASK          16
#define V_SATA_CFG_SATAGC_SMS_AHCI          0x0
#define V_SATA_CFG_SATAGC_SMS_RAID          0x1
#define B_SATA_CFG_SATAGC_AIE               BIT7
#define B_SATA_CFG_SATAGC_AIES              BIT6
#define B_SATA_CFG_SATAGC_MSS               (BIT4 | BIT3)
#define V_SATA_CFG_SATAGC_MSS_8K            0x2
#define N_SATA_CFG_SATAGC_MSS               3
#define B_SATA_CFG_SATAGC_ASSEL             (BIT2 | BIT1 | BIT0)
#define V_SATA_CFG_SATAGC_ASSEL_2K          0x0
#define V_SATA_CFG_SATAGC_ASSEL_16K         0x1
#define V_SATA_CFG_SATAGC_ASSEL_32K         0x2
#define V_SATA_CFG_SATAGC_ASSEL_64K         0x3
#define V_SATA_CFG_SATAGC_ASSEL_128K        0x4
#define V_SATA_CFG_SATAGC_ASSEL_256K        0x5
#define V_SATA_CFG_SATAGC_ASSEL_512K        0x6

#define R_SATA_CFG_SIRI                     0xA0
#define R_SATA_CFG_SIRD                     0xA4
#define R_SATA_CFG_SIR_0C                   0x0C
#define R_SATA_CFG_SIR_50                   0x50
#define R_SATA_CFG_SIR_54                   0x54
#define R_SATA_CFG_SIR_58                   0x58
#define R_SATA_CFG_SIR_5C                   0x5C
#define R_SATA_CFG_SIR_60                   0x60
#define R_SATA_CFG_SIR_64                   0x64
#define R_SATA_CFG_SIR_68                   0x68
#define R_SATA_CFG_SIR_6C                   0x6C
#define R_SATA_CFG_SIR_70                   0x70
#define R_SATA_CFG_SIR_80                   0x80
#define R_SATA_CFG_SIR_84                   0x84
#define R_SATA_CFG_SIR_8C                   0x8C
#define R_SATA_CFG_SIR_90                   0x90
#define R_SATA_CFG_SIR_98                   0x98
#define R_SATA_CFG_SIR_9C                   0x9C
#define R_SATA_CFG_SIR_A0                   0xA0
#define B_SATA_CFG_SIR_A0_CWICBRLMAX        0x1F
#define N_SATA_CFG_SIR_A0_CWICBRLMAX        24
#define B_SATA_CFG_SIR_A0_CWCIBRUMIN        0x3F
#define N_SATA_CFG_SIR_A0_CWCIBRUMIN        18
#define R_SATA_CFG_SIR_A4                   0xA4
#define R_SATA_CFG_SIR_A8                   0xA8
#define R_SATA_CFG_SIR_C4                   0xC4
#define B_SATA_CFG_SIR_C4_TCLKSNACK_CP      (BIT27 | BIT26)
#define R_SATA_CFG_SIR_C8                   0xC8
#define R_SATA_CFG_SIR_CC                   0xCC
#define R_SATA_CFG_SIR_D0                   0xD0
#define R_SATA_CFG_SIR_D4                   0xD4
#define B_SATA_CFG_SIR_D4_CIGMAX            0x3F
#define N_SATA_CFG_SIR_D4_CIGMAX            24
#define B_SATA_CFG_SIR_D4_CIGMIN            0x3F
#define N_SATA_CFG_SIR_D4_CIGMIN            16
#define B_SATA_CFG_SIR_D4_CWGMAX            0x1F
#define N_SATA_CFG_SIR_D4_CWGMAX            8
#define B_SATA_CFG_SIR_D4_CWGMIN            0x1F
#define N_SATA_CFG_SIR_D4_CWGMIN            0
#define R_SATA_CFG_CR0                      0xA8
#define R_SATA_CFG_CR1                      0xAC
#define B_SATA_CFG_CR1_BAROFST              0xFFF0
#define B_SATA_CFG_CR1_BARLOC               0x000F
#define R_SATA_CFG_FLR_CID                  0xB0
#define B_SATA_CFG_FLR_CID                  0x00FF
#define V_SATA_CFG_FLR_CID_1                0x0009
#define V_SATA_CFG_FLR_CID_0                0x0013
#define R_SATA_CFG_FLR_CLV                  0xB2
#define B_SATA_CFG_FLR_CLV_FLRC_FLRCSSEL_0  BIT9
#define B_SATA_CFG_FLR_CLV_TXPC_FLRCSSEL_0  BIT8
#define V_SATA_CFG_FLR_CLV_VSCID_FLRCSSEL   0x0006
#define R_SATA_CFG_FLRC                     0xB4
#define B_SATA_CFG_FLRC_TXP                 BIT8
#define B_SATA_CFG_FLRC_INITFLR             BIT0
#define R_SATA_CFG_MXID                     0xD0
#define N_SATA_CFG_MXID_NEXT                8

#define R_SATA_MEM_VS_CAP                   0xA4
#define B_SATA_MEM_VS_CAP_NRMBE             BIT0                            ///< NVM Remap Memory BAR Enable
#define N_SATA_MEM_VS_CAP_MSL               1
#define V_SATA_MEM_VS_CAP_MSL               0x1EF                           ///< Memory Space Limit Field Value
#define N_SATA_MEM_VS_CAP_NRMO              16
#define V_SATA_MEM_VS_CAP_NRMO              0x10                            ///< NVM Remapped Memory Offset Field Value

//
// RST PCIe Storage Remapping Registers
//
#define R_SATA_MEM_RST_PCIE_STORAGE_RCR                 0x800                           ///< Remap Capability Register
#define B_SATA_MEM_RST_PCIE_STORAGE_RCR_NRS             (BIT2|BIT1|BIT0)                ///< Number of Remapping Supported
#define B_SATA_MEM_RST_PCIE_STORAGE_RCR_NRS_CR1         BIT0                            ///< Number of Remapping Supported (RST PCIe Storage Cycle Router #1)
#define R_SATA_MEM_RST_PCIE_STORAGE_AMXC                0x808                           ///< AHCI MSI-X Configuration
#define B_SATA_MEM_RST_PCIE_STORAGE_AMXC_AMXV           0x7FF                           ///< AHCI MSI-X Vector
#define R_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC             0x880                           ///< CR#1 Device Class Code
#define N_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_SCC         8
#define N_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_BCC         16
#define B_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_DT          BIT31                           ///< Device Type
#define R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMBL            0x884                           ///< CR#1 Device Memory BAR Length
#define R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC            0x888                           ///< CR#1 Device MSI-X Configuration
#define N_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC_MXEV       16
#define V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR     0x80                            ///< Remapped Configuration for RST PCIe Storage Cycle Router #n
#define V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET     0x100                           ///< Remapped Root Port Offset Value
#define R_SATA_CFG_RST_PCIE_STORAGE_GCR                 0x300                           ///< General Configuration Register
#define B_SATA_CFG_RST_PCIE_STORAGE_GCR_CRE             BIT0                            ///< RST PCIe Storage Cycle Router Enable
#define B_SATA_CFG_RST_PCIE_STORAGE_GCR_PLS             0x1FFFFE                        ///< PCIe Lane Selected Field
#define B_SATA_CFG_RST_PCIE_STORAGE_GCR_PNCAIDL         BIT29                           ///< Configuration Access Index/Data Lockdown
#define B_SATA_CFG_RST_PCIE_STORAGE_GCR_RCL             BIT30                           ///< Remapping Configuration Lockdown
#define B_SATA_CFG_RST_PCIE_STORAGE_GCR_CREL            BIT31                           ///< RST PCIe Storage Cycle Router Enable Lockdown
#define R_SATA_CFG_RST_PCIE_STORAGE_GSR                 0x304                           ///< General Status Register
#define B_SATA_CFG_RST_PCIE_STORAGE_GSR_PLRC            0x1FFFFE                        ///< PCIe Lane Remap Capable Field
#define B_SATA_CFG_RST_PCIE_STORAGE_GSR_PCCS            BIT30                           ///< Port Configuration Check Status
#define B_SATA_CFG_RST_PCIE_STORAGE_GSR_PCCD            BIT31                           ///< Port Configuration Check Disable
#define R_SATA_CFG_RST_PCIE_STORAGE_CAIR                0x308                           ///< Configuration Access Index Register
#define R_SATA_CFG_RST_PCIE_STORAGE_CADR                0x30C                           ///< Configuration Access Data Register
#define R_SATA_CFG_RST_PCIE_STORAGE_MBRC                0x310                           ///< Memory BAR Remap Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB            (BIT19|BIT18|BIT17|BIT16)       ///< Memory BAR Remap Configuration Target Memory BAR
#define N_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB            16
#define V_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB_BAR0       0x4                             ///< Memory BAR Remap Configuration Target Memory BAR - BAR0
#define V_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB_BAR5       0x9                             ///< Memory BAR Remap Configuration Target Memory BAR - BAR5
#define B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TT             BIT20                           ///< Remap Configuration Target Type
#define B_SATA_CFG_RST_PCIE_STORAGE_MBRC_RE             BIT31                           ///< Remap Configuration Remap Enable
#define R_SATA_CFG_RST_PCIE_STORAGE_IOBRSC              0x320       ///< I/O BAR Remap Source Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_IOBRSC_RE           BIT31       ///< I/O BAR Remap Source Configuration Remap Enable
#define R_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC             0x338       ///< AHCI Index/Data Pair Capability Remap Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_TCSO        0xFF0000    ///< AHCI Index/Data Pair Capability Remap Configuration Target Capability Structure OffsBet
#define N_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_TCSO        16
#define B_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_RE          BIT31       ///< AHCI Index/Data Pair Capability Remap Configuration Remap Enable
#define R_SATA_CFG_RST_PCIE_STORAGE_MXCRC               0x33C       ///< MSI-X Capability Remap Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_MXCRCC_TCSO         0xFF0000    ///< MSI-X Capability Remap Configuration Target Capability Structure Offset
#define N_SATA_CFG_RST_PCIE_STORAGE_MXCRCC_TCSO         16
#define B_SATA_CFG_RST_PCIE_STORAGE_MXCRC_RE            BIT31       ///< MSI-X Capability Remap Configuration Remap Enable
#define R_SATA_CFG_RST_PCIE_STORAGE_MXTRC               0x340       ///< MSI-X Table Remap Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_MXTRC_TBIR          0x07        ///< MSI-X Table Remap Configuration Table BIR
#define B_SATA_CFG_RST_PCIE_STORAGE_MXTRC_TO            0xFFFFFFF8  ///< MSI-X Table Remap Configuration Table Offset
#define R_SATA_CFG_RST_PCIE_STORAGE_MXTBAR              0x344       ///< MSI-X Table Base Address Register
#define B_SATA_CFG_RST_PCIE_STORAGE_MXTBAR_TBAV         BIT0        ///< MSI-X Table Base Address Register Table Base Address Valid
#define R_SATA_CFG_RST_PCIE_STORAGE_MXPRC               0x348       ///< MSI-X PBA Remap Configuration
#define B_SATA_CFG_RST_PCIE_STORAGE_MXPRC_TBIR          0x07        ///< MSI-X PBA Remap Configuration Table BIR
#define B_SATA_CFG_RST_PCIE_STORAGE_MXPRC_TO            0xFFFFFFF8  ///< MSI-X PBA Remap Configuration Table Offset
#define R_SATA_CFG_RST_PCIE_STORAGE_MXPBAR              0x34C       ///< MSI-X PBA Base Address Register
#define B_SATA_CFG_RST_PCIE_STORAGE_MXPBAR_TBAV         BIT0        ///< MSI-X PBA Base Address Register Table Base Address Valid
#define R_SATA_CFG_RST_PCIE_STORAGE_NRDF                0x350       ///< NVM Remapping Device:Function
#define R_SATA_CFG_RST_PCIE_STORAGE_EGCR                0x354       ///< Extended General Configuration Register
#define B_SATA_CFG_RST_PCIE_STORAGE_EGCR_CRDCGE         BIT16       ///< RST PCIe Storage Cycle Router Dynamic Clock Gating Enable
#define B_SATA_CFG_RST_PCIE_STORAGE_EGCR_CRTCGE         BIT17       ///< RST PCIe Storage Cycle Router Trunk Clock Gating Enable
#define B_SATA_CFG_RST_PCIE_STORAGE_EGCR_ICAS           BIT19       ///< IOSF CLKREQ Assertion Select
#define B_SATA_CFG_RST_PCIE_STORAGE_EGCR_TSCAS          BIT20       ///< To SATA CLKREQ Assertion Select
#define R_SATA_CFG_RST_PCIE_STORAGE_SAPI                0x358       ///< Shadowed AHCI Ports Implemented
#define R_SATA_CFG_RST_PCIE_STORAGE_RHDF                0x368       ///< Remapping Host Device Function
#define R_SATA_CFG_RST_PCIE_STORAGE_CRGC                0xFC0       ///< RST PCIe Storage Cycle Router Global Control
#define B_SATA_CFG_RST_PCIE_STORAGE_CRGC_CRAS           (BIT1|BIT0) ///< RST PCIe Storage Cycle Router Global Control Cycle Router Accessibility Select
#define R_SATA_CFG_RST_PCIE_STORAGE_FDW0                0xFC4       ///< Fuse DW0

//
// AHCI BAR Area related Registers
//
#define R_SATA_MEM_AHCI_CAP                 0x0
#define B_SATA_MEM_AHCI_CAP_SMPS            BIT28 ///< Supports Interlock Switch
#define B_SATA_MEM_AHCI_CAP_SSS             BIT27 ///< Supports Stagger Spin-up
#define B_SATA_MEM_AHCI_CAP_SALP            BIT26
#define B_SATA_MEM_AHCI_CAP_SAL             BIT25
#define B_SATA_MEM_AHCI_CAP_SCLO            BIT24 ///< Supports Command List Override
#define B_SATA_MEM_AHCI_CAP_ISS_MASK        (BIT23 | BIT22 | BIT21 | BIT20)
#define N_SATA_MEM_AHCI_CAP_ISS             20    ///< Interface Speed Support
#define V_SATA_MEM_AHCI_CAP_ISS_1_5_G       0x01
#define V_SATA_MEM_AHCI_CAP_ISS_3_0_G       0x02
#define V_SATA_MEM_AHCI_CAP_ISS_6_0_G       0x03
#define B_SATA_MEM_AHCI_CAP_SNZO            BIT19
#define B_SATA_MEM_AHCI_CAP_SAM             BIT18
#define B_SATA_MEM_AHCI_CAP_SPM             BIT17 ///< Supports Port Multiplier
#define B_SATA_MEM_AHCI_CAP_PMD             BIT15 ///< PIO Multiple DRQ Block
#define B_SATA_MEM_AHCI_CAP_SSC             BIT14
#define B_SATA_MEM_AHCI_CAP_PSC             BIT13
#define B_SATA_MEM_AHCI_CAP_NCS             0x1F00
#define B_SATA_MEM_AHCI_CAP_CCCS            BIT7
#define B_SATA_MEM_AHCI_CAP_EMS             BIT6
#define B_SATA_MEM_AHCI_CAP_SXS             BIT5  ///< External SATA is supported
#define B_SATA_MEM_AHCI_CAP_NPS             0x001F

#define R_SATA_MEM_AHCI_GHC                 0x04
#define B_SATA_MEM_AHCI_GHC_AE              BIT31
#define B_SATA_MEM_AHCI_GHC_MRSM            BIT2
#define B_SATA_MEM_AHCI_GHC_IE              BIT1
#define B_SATA_MEM_AHCI_GHC_HR              BIT0

#define R_SATA_MEM_AHCI_IS                  0x08
#define B_SATA_MEM_AHCI_IS_PORT7            BIT7
#define B_SATA_MEM_AHCI_IS_PORT6            BIT6
#define B_SATA_MEM_AHCI_IS_PORT5            BIT5
#define B_SATA_MEM_AHCI_IS_PORT4            BIT4
#define B_SATA_MEM_AHCI_IS_PORT3            BIT3
#define B_SATA_MEM_AHCI_IS_PORT2            BIT2
#define B_SATA_MEM_AHCI_IS_PORT1            BIT1
#define B_SATA_MEM_AHCI_IS_PORT0            BIT0
#define R_SATA_MEM_AHCI_PI                  0x0C
#define B_SATA_MEM_AHCI_PI_PORT_MASK        0xFF
#define B_SATA_MEM_PORT7_IMPLEMENTED        BIT7
#define B_SATA_MEM_PORT6_IMPLEMENTED        BIT6
#define B_SATA_MEM_PORT5_IMPLEMENTED        BIT5
#define B_SATA_MEM_PORT4_IMPLEMENTED        BIT4
#define B_SATA_MEM_PORT3_IMPLEMENTED        BIT3
#define B_SATA_MEM_PORT2_IMPLEMENTED        BIT2
#define B_SATA_MEM_PORT1_IMPLEMENTED        BIT1
#define B_SATA_MEM_PORT0_IMPLEMENTED        BIT0
#define R_SATA_MEM_AHCI_EM_LOC              0x1C
#define B_SATA_MEM_AHCI_EM_LOC_OFST         0xFFFF0000
#define B_SATA_MEM_AHCI_EM_LOC_SZ           0x0000FFFF
#define R_SATA_MEM_AHCI_CAP2                0x24
#define B_SATA_MEM_AHCI_CAP2_DESO           BIT5
#define B_SATA_MEM_AHCI_CAP2_SADM           BIT4
#define B_SATA_MEM_AHCI_CAP2_SDS            BIT3
#define B_SATA_MEM_AHCI_CAP2_APST           BIT2  ///< Automatic Partial to Slumber Transitions
#define R_SATA_MEM_AHCI_SFM                 0xC8  ///< RST Feature Capabilities
#define B_SATA_MEM_AHCI_SFM_CPU_STORAGE     BIT14
#define B_SATA_MEM_AHCI_SFM_OMA             BIT13
#define B_SATA_MEM_AHCI_SFM_LEGACY          BIT12
#define B_SATA_MEM_AHCI_SFM_OUD             (BIT11 | BIT10)
#define N_SATA_MEM_AHCI_SFM_OUD             10
#define B_SATA_MEM_AHCI_SFM_SEREQ           BIT9
#define B_SATA_MEM_AHCI_SFM_IROES           BIT8
#define B_SATA_MEM_AHCI_SFM_LEDL            BIT7
#define B_SATA_MEM_AHCI_SFM_HDDLK           BIT6
#define B_SATA_MEM_AHCI_SFM_IRSTOROM        BIT5
#define B_SATA_MEM_AHCI_SFM_RSTE            BIT4
#define B_SATA_MEM_AHCI_SFM_R5E             BIT3
#define B_SATA_MEM_AHCI_SFM_R10E            BIT2
#define B_SATA_MEM_AHCI_SFM_R1E             BIT1
#define B_SATA_MEM_AHCI_SFM_R0E             BIT0
#define B_SATA_MEM_AHCI_SFM_LOWBYTES        0x1FF
#define R_SATA_MEM_AHCI_P0CMD               0x118
#define R_SATA_MEM_AHCI_P1CMD               0x198
#define R_SATA_MEM_AHCI_P2CMD               0x218
#define R_SATA_MEM_AHCI_P3CMD               0x298
#define R_SATA_MEM_AHCI_P4CMD               0x318
#define R_SATA_MEM_AHCI_P5CMD               0x398
#define R_SATA_MEM_AHCI_P6CMD               0x418
#define R_SATA_MEM_AHCI_P7CMD               0x498
#define R_SATA_MEM_AHCI_P0DEVSLP            0x144
#define R_SATA_MEM_AHCI_P1DEVSLP            0x1C4
#define R_SATA_MEM_AHCI_P2DEVSLP            0x244
#define R_SATA_MEM_AHCI_P3DEVSLP            0x2C4
#define R_SATA_MEM_AHCI_P4DEVSLP            0x344
#define R_SATA_MEM_AHCI_P5DEVSLP            0x3C4
#define R_SATA_MEM_AHCI_P6DEVSLP            0x444
#define R_SATA_MEM_AHCI_P7DEVSLP            0x4C4
#define B_SATA_MEM_AHCI_PxDEVSLP_DSP        BIT1
#define B_SATA_MEM_AHCI_PxDEVSLP_ADSE       BIT0
#define B_SATA_MEM_AHCI_PxDEVSLP_DITO_MASK  0x01FF8000
#define V_SATA_MEM_AHCI_PxDEVSLP_DITO_625   0x01388000
#define B_SATA_MEM_AHCI_PxDEVSLP_DM_MASK    0x1E000000
#define V_SATA_MEM_AHCI_PxDEVSLP_DM_16      0x1E000000
#define B_SATA_MEM_AHCI_PxCMD_ICC           (BIT31 | BIT30 | BIT29 | BIT28)
#define B_SATA_MEM_AHCI_PxCMD_MASK          (BIT27 | BIT26 | BIT22 | BIT21 | BIT19 | BIT18)
#define B_SATA_MEM_AHCI_PxCMD_ASP           BIT27
#define B_SATA_MEM_AHCI_PxCMD_ALPE          BIT26
#define B_SATA_MEM_AHCI_PxCMD_DLAE          BIT25
#define B_SATA_MEM_AHCI_PxCMD_ATAPI         BIT24
#define B_SATA_MEM_AHCI_PxCMD_APSTE         BIT23
#define B_SATA_MEM_AHCI_PxCMD_ESP           BIT21 ///< Used with an external SATA device
#define B_SATA_MEM_AHCI_PxCMD_MPSP          BIT19 ///< Mechanical Switch Attached to Port
#define B_SATA_MEM_AHCI_PxCMD_HPCP          BIT18 ///< Hotplug capable
#define B_SATA_MEM_AHCI_PxCMD_CR            BIT15
#define B_SATA_MEM_AHCI_PxCMD_FR            BIT14
#define B_SATA_MEM_AHCI_PxCMD_ISS           BIT13
#define B_SATA_MEM_AHCI_PxCMD_CCS           0x00001F00
#define B_SATA_MEM_AHCI_PxCMD_FRE           BIT4
#define B_SATA_MEM_AHCI_PxCMD_CLO           BIT3
#define B_SATA_MEM_AHCI_PxCMD_POD           BIT2
#define B_SATA_MEM_AHCI_PxCMD_SUD           BIT1
#define B_SATA_MEM_AHCI_PxCMD_ST            BIT0
#define R_SATA_MEM_AHCI_P0SCTL              0x12C
#define R_SATA_MEM_AHCI_P1SCTL              0x1AC
#define R_SATA_MEM_AHCI_P2SCTL              0x22C
#define R_SATA_MEM_AHCI_P3SCTL              0x2AC
#define R_SATA_MEM_AHCI_P4SCTL              0x32C
#define R_SATA_MEM_AHCI_P5SCTL              0x3AC
#define R_SATA_MEM_AHCI_P6SCTL              0x42C
#define B_SATA_MEM_AHCI_PXSCTL_IPM          0x00000F00
#define V_SATA_MEM_AHCI_PXSCTL_IPM_0        0x00000000
#define V_SATA_MEM_AHCI_PXSCTL_IPM_1        0x00000100
#define V_SATA_MEM_AHCI_PXSCTL_IPM_2        0x00000200
#define V_SATA_MEM_AHCI_PXSCTL_IPM_3        0x00000300
#define B_SATA_MEM_AHCI_PXSCTL_SPD          0x000000F0
#define V_SATA_MEM_AHCI_PXSCTL_SPD_0        0x00000000
#define V_SATA_MEM_AHCI_PXSCTL_SPD_1        0x00000010
#define V_SATA_MEM_AHCI_PXSCTL_SPD_2        0x00000020
#define V_SATA_MEM_AHCI_PXSCTL_SPD_3        0x00000030
#define B_SATA_MEM_AHCI_PXSCTL_DET          0x0000000F
#define V_SATA_MEM_AHCI_PXSCTL_DET_0        0x00000000
#define V_SATA_MEM_AHCI_PXSCTL_DET_1        0x00000001
#define V_SATA_MEM_AHCI_PXSCTL_DET_4        0x00000004
#endif
