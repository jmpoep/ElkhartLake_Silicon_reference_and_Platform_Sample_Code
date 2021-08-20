/** @file
  Register definition for VER2 PSF component

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
#ifndef _PSF_REGS_VER2_H_
#define _PSF_REGS_VER2_H_

//
// Private chipset register (Memory space) offset definition
// The PCR register defines is used for PCR MMIO programming and PCH SBI programming as well.
//

//
// PSFx segment registers
//
#define R_VER2_PCH_PSF_PCR_PORT_CONFIG_PG0_PORT0         0x4020                  ///< PSF Segment Port Configuration Register
#define R_VER2_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT0         0x4024
#define R_VER2_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT1         0x4028
#define R_VER2_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT2         0x402C
#define R_VER2_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT3         0x4030

//
// PSFx PCRs definitions
//
#define V_VER2_PCH_LP_PSFX_PCR_PSF_MC_AGENT_MCAST_TGT_P2SB   0x38B00
#define V_VER2_PCH_H_PSFX_PCR_PSF_MC_AGENT_MCAST_TGT_P2SB    0x38C00
#define V_VER2_PCH_PSFX_PSF_PCR_MC_AGENT_MCAST_TGT_DMI       0x10000

//
// PSF1 PCRs
//
// PSF1 PCH-LP Specific Base Address
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_HECI1_REG_BASE        0x0180                  ///< D22F0 PSF base address (CSME: HECI1)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_HECI2_REG_BASE        0x0200                  ///< D22F1 PSF base address (CSME: HECI2)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_HECI3_REG_BASE        0x0280                  ///< D22F4 PSF base address (CSME: HECI3)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_HECI4_REG_BASE        0x0300                  ///< D22F5 PSF base address (CSME: HECI4)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_IDER_REG_BASE         0x0600                  ///< D22F2 PSF base address (CSME: IDER)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_KT_REG_BASE           0x0680                  ///< D22F3 PSF base address (CSME: KT)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_FPAK_REG_BASE         0x0D00                  ///< PCH-LP D16F3 PSF base address (FPAK)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_GBE_REG_BASE          0x0D80                  ///< D31F6 PSF base address (GBE)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_NPK_PHANTOM_REG_BASE  0x0E80                  ///< D21F7 PSF base address (Northpeak Phantom (ACPI) Function)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_TRACEHUB_REG_BASE     0x0F00                  ///< D31F7 PSF base address (TraceHub)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_XHCI_REG_BASE         0x0F80                  ///< D20F0 PSF base address (XHCI)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_SATA_REG_BASE         0x1080                  ///< PCH-LP D23F0 PSF base address (SATA)

#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE   0x2000                  ///< PCH-LP D28F0 PSF base address (PCIE PORT 01)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE02_RS0_REG_BASE   0x2080                  ///< PCH-LP D28F1 PSF base address (PCIE PORT 02)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE03_RS0_REG_BASE   0x2100                  ///< PCH-LP D28F2 PSF base address (PCIE PORT 03)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE04_RS0_REG_BASE   0x2180                  ///< PCH-LP D28F3 PSF base address (PCIE PORT 04)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE05_RS0_REG_BASE   0x2200                  ///< PCH-LP D28F4 PSF base address (PCIE PORT 05)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE06_RS0_REG_BASE   0x2280                  ///< PCH-LP D28F5 PSF base address (PCIE PORT 06)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE07_RS0_REG_BASE   0x2300                  ///< PCH-LP D28F6 PSF base address (PCIE PORT 07)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE08_RS0_REG_BASE   0x2380                  ///< PCH-LP D28F7 PSF base address (PCIE PORT 08)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE09_RS0_REG_BASE   0x2400                  ///< PCH-LP D29F0 PSF base address (PCIE PORT 09)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE10_RS0_REG_BASE   0x2480                  ///< PCH-LP D29F1 PSF base address (PCIE PORT 10)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE11_RS0_REG_BASE   0x2500                  ///< PCH-LP D29F2 PSF base address (PCIE PORT 11)
#define R_VER2_PCH_LP_PSF1_PCR_T1_SHDW_PCIE12_RS0_REG_BASE   0x2580                  ///< PCH-LP D29F3 PSF base address (PCIE PORT 12)

#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE01_RS3_REG_BASE   0x0700                  ///< PCH-LP D28F0 PSF base address (PCIE PORT 01)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE02_RS3_REG_BASE   0x0780                  ///< PCH-LP D28F1 PSF base address (PCIE PORT 02)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE03_RS3_REG_BASE   0x0800                  ///< PCH-LP D28F2 PSF base address (PCIE PORT 03)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE04_RS3_REG_BASE   0x0880                  ///< PCH-LP D28F3 PSF base address (PCIE PORT 04)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE05_RS3_REG_BASE   0x0900                  ///< PCH-LP D28F4 PSF base address (PCIE PORT 05)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE06_RS3_REG_BASE   0x0980                  ///< PCH-LP D28F5 PSF base address (PCIE PORT 06)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE07_RS3_REG_BASE   0x0A00                  ///< PCH-LP D28F6 PSF base address (PCIE PORT 07)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE08_RS3_REG_BASE   0x0A80                  ///< PCH-LP D28F7 PSF base address (PCIE PORT 08)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE09_RS3_REG_BASE   0x0B00                  ///< PCH-LP D29F0 PSF base address (PCIE PORT 09)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE10_RS3_REG_BASE   0x0B80                  ///< PCH-LP D29F1 PSF base address (PCIE PORT 10)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE11_RS3_REG_BASE   0x0C00                  ///< PCH-LP D29F2 PSF base address (PCIE PORT 11)
#define R_VER2_PCH_LP_PSF1_PCR_T0_SHDW_PCIE12_RS3_REG_BASE   0x0C80                  ///< PCH-LP D29F3 PSF base address (PCIE PORT 12)

// PSF1 PCH-H Specific Base Address
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_HECI1_REG_BASE         0x0180                  ///< D22F0 PSF base address (CSME: HECI1)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_HECI2_REG_BASE         0x0200                  ///< D22F1 PSF base address (CSME: HECI2)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_HECI3_REG_BASE         0x0280                  ///< D22F4 PSF base address (CSME: HECI3)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_HECI4_REG_BASE         0x0300                  ///< D22F5 PSF base address (CSME: HECI4)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_IDER_REG_BASE          0x0600                  ///< D22F2 PSF base address (CSME: IDER)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_KT_REG_BASE            0x0680                  ///< D22F3 PSF base address (CSME: KT)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_NPK_PHANTOM_REG_BASE   0x0700                  ///< D21F7 PSF base address (Northpeak Phantom (ACPI))
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_TRACEHUB_REG_BASE      0x0780                  ///< D31F7 PSF base address (Tracehub)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_XHCI_REG_BASE          0x0800                  ///< D20F0 PSF base address (xHCI)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_SATA_REG_BASE          0x1500                  ///< D23F0 PSF base address (SATA)

#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE    0x2000                  ///< PCH-H D28F0 PSF base address (PCIE PORT 01)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE02_RS0_REG_BASE    0x2080                  ///< PCH-H D28F1 PSF base address (PCIE PORT 02)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE03_RS0_REG_BASE    0x2100                  ///< PCH-H D28F2 PSF base address (PCIE PORT 03)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE04_RS0_REG_BASE    0x2180                  ///< PCH-H D28F3 PSF base address (PCIE PORT 04)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE09_RS0_REG_BASE    0x2200                  ///< PCH-H D29F0 PSF base address (PCIE PORT 09)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE10_RS0_REG_BASE    0x2280                  ///< PCH-H D29F1 PSF base address (PCIE PORT 10)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE11_RS0_REG_BASE    0x2300                  ///< PCH-H D29F2 PSF base address (PCIE PORT 11)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE12_RS0_REG_BASE    0x2380                  ///< PCH-H D29F3 PSF base address (PCIE PORT 12)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE13_RS0_REG_BASE    0x2400                  ///< PCH-H D29F4 PSF base address (PCIE PORT 13)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE14_RS0_REG_BASE    0x2480                  ///< PCH-H D29F5 PSF base address (PCIE PORT 14)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE15_RS0_REG_BASE    0x2500                  ///< PCH-H D29F6 PSF base address (PCIE PORT 15)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE16_RS0_REG_BASE    0x2580                  ///< PCH-H D29F7 PSF base address (PCIE PORT 16)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE17_RS0_REG_BASE    0x2600                  ///< PCH-H D27F0 PSF base address (PCIE PORT 17)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE18_RS0_REG_BASE    0x2680                  ///< PCH-H D27F1 PSF base address (PCIE PORT 18)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE19_RS0_REG_BASE    0x2700                  ///< PCH-H D27F2 PSF base address (PCIE PORT 19)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE20_RS0_REG_BASE    0x2780                  ///< PCH-H D27F3 PSF base address (PCIE PORT 20)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE05_RS0_REG_BASE    0x2800                  ///< PCH-H D28F4 PSF base address (PCIE PORT 05)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE06_RS0_REG_BASE    0x2880                  ///< PCH-H D28F5 PSF base address (PCIE PORT 06)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE07_RS0_REG_BASE    0x2900                  ///< PCH-H D28F6 PSF base address (PCIE PORT 07)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE08_RS0_REG_BASE    0x2980                  ///< PCH-H D28F7 PSF base address (PCIE PORT 08)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE21_RS0_REG_BASE    0x2A00                  ///< PCH-H D27F4 PSF base address (PCIE PORT 21)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE22_RS0_REG_BASE    0x2A80                  ///< PCH-H D27F5 PSF base address (PCIE PORT 22)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE23_RS0_REG_BASE    0x2B00                  ///< PCH-H D27F6 PSF base address (PCIE PORT 23)
#define R_VER2_PCH_H_PSF1_PCR_T1_SHDW_PCIE24_RS0_REG_BASE    0x2B80                  ///< PCH-H D27F7 PSF base address (PCIE PORT 24)

#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE01_RS3_REG_BASE    0x0900                  ///< PCH-H D28F0 PSF base address (PCIE PORT 01)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE02_RS3_REG_BASE    0x0980                  ///< PCH-H D28F1 PSF base address (PCIE PORT 02)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE03_RS3_REG_BASE    0x0A00                  ///< PCH-H D28F2 PSF base address (PCIE PORT 03)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE04_RS3_REG_BASE    0x0A80                  ///< PCH-H D28F3 PSF base address (PCIE PORT 04)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE09_RS3_REG_BASE    0x0B00                  ///< PCH-H D29F0 PSF base address (PCIE PORT 09)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE10_RS3_REG_BASE    0x0B80                  ///< PCH-H D29F1 PSF base address (PCIE PORT 10)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE11_RS3_REG_BASE    0x0C00                  ///< PCH-H D29F2 PSF base address (PCIE PORT 11)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE12_RS3_REG_BASE    0x0C80                  ///< PCH-H D29F3 PSF base address (PCIE PORT 12)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE13_RS3_REG_BASE    0x0D00                  ///< PCH-H D29F4 PSF base address (PCIE PORT 13)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE14_RS3_REG_BASE    0x0D80                  ///< PCH-H D29F5 PSF base address (PCIE PORT 14)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE15_RS3_REG_BASE    0x0E00                  ///< PCH-H D29F6 PSF base address (PCIE PORT 15)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE16_RS3_REG_BASE    0x0E80                  ///< PCH-H D29F7 PSF base address (PCIE PORT 16)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE17_RS3_REG_BASE    0x0F00                  ///< PCH-H D27F0 PSF base address (PCIE PORT 17)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE18_RS3_REG_BASE    0x0F80                  ///< PCH-H D27F1 PSF base address (PCIE PORT 18)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE19_RS3_REG_BASE    0x1000                  ///< PCH-H D27F2 PSF base address (PCIE PORT 19)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE20_RS3_REG_BASE    0x1080                  ///< PCH-H D27F3 PSF base address (PCIE PORT 20)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE05_RS3_REG_BASE    0x1100                  ///< PCH-H D28F4 PSF base address (PCIE PORT 05)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE06_RS3_REG_BASE    0x1180                  ///< PCH-H D28F5 PSF base address (PCIE PORT 06)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE07_RS3_REG_BASE    0x1200                  ///< PCH-H D28F6 PSF base address (PCIE PORT 07)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE08_RS3_REG_BASE    0x1280                  ///< PCH-H D28F7 PSF base address (PCIE PORT 08)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE21_RS3_REG_BASE    0x1300                  ///< PCH-H D27F4 PSF base address (PCIE PORT 21)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE22_RS3_REG_BASE    0x1380                  ///< PCH-H D27F5 PSF base address (PCIE PORT 22)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE23_RS3_REG_BASE    0x1400                  ///< PCH-H D27F6 PSF base address (PCIE PORT 23)
#define R_VER2_PCH_H_PSF1_PCR_T0_SHDW_PCIE24_RS3_REG_BASE    0x1480                  ///< PCH-H D27F7 PSF base address (PCIE PORT 24)

// Other PSF1 PCRs definition

//PSF 1 Multicast Message Configuration
#define R_VER2_PCH_LP_PSF1_PCR_MC_CONTROL_MCAST0_EOI                     0x4040      ///< Multicast Control Register
#define R_VER2_PCH_LP_PSF1_PCR_MC_AGENT_MCAST0_TGT0_EOI                  0x4058      ///< Destination ID

#define R_VER2_PCH_H_PSF1_PCR_MC_CONTROL_MCAST0_EOI                      0x4040      ///< Multicast Control Register
#define R_VER2_PCH_H_PSF1_PCR_MC_AGENT_MCAST0_TGT0_EOI                   0x4058      ///< Destination ID

#define R_VER2_PCH_LP_PSF1_PCR_MC_CONTROL_MCAST1_RS0_MCTP1               0x404C      ///< Multicast Control Register
#define R_VER2_PCH_LP_PSF1_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1            0x4094      ///< Destination ID

#define R_VER2_PCH_H_PSF1_PCR_MC_CONTROL_MCAST1_RS0_MCTP1                0x4050      ///< Multicast Control Register
#define R_VER2_PCH_H_PSF1_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1             0x4098      ///< Destination ID

//
// controls the PCI configuration header of a PCI function
//
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F3   0x436C   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F2   0x4370   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F1   0x4374   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F0   0x4378   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F7   0x437C   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F6   0x4380   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F5   0x4384   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F4   0x4388   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F3   0x438C   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F2   0x4390   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F1   0x4394   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F0   0x4398   ///< SPA

#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F3   0x430C   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F2   0x4310   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F1   0x4314   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F0   0x4318   ///< SPC
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F7   0x431C   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F6   0x4320   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F5   0x4324   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F4   0x4328   ///< SPB
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F3   0x432C   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F2   0x4330   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F1   0x4334   ///< SPA
#define R_VER2_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F0   0x4338   ///< SPA

#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_RS0_D27_F7    0x4360   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_RS0_D27_F6    0x4364   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_RS0_D27_F5    0x4368   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_RS0_D27_F4    0x436C   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F7    0x4370   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F6    0x4374   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F5    0x4378   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F4    0x437C   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_RS0_D27_F3    0x4380   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_RS0_D27_F2    0x4384   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_RS0_D27_F1    0x4388   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_RS0_D27_F0    0x438C   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D29_F7    0x4390   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D29_F6    0x4394   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D29_F5    0x4398   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D29_F4    0x439C   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F3    0x43A0   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F2    0x43A4   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F1    0x43A8   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D29_F0    0x43AC   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F3    0x43B0   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F2    0x43B4   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F1    0x43B8   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F0    0x43BC   ///< SPA

#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPF_RS3_D27_F7    0x42C0   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPF_RS3_D27_F6    0x42C4   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPF_RS3_D27_F5    0x42C8   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPF_RS3_D27_F4    0x42CC   ///< SPF
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F7    0x42D0   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F6    0x42D4   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F5    0x42D8   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F4    0x42DC   ///< SPB
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPE_RS3_D27_F3    0x42E0   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPE_RS3_D27_F2    0x42E4   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPE_RS3_D27_F1    0x42E8   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPE_RS3_D27_F0    0x42EC   ///< SPE
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D29_F7    0x42F0   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D29_F6    0x42F4   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D29_F5    0x42F8   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D29_F4    0x42FC   ///< SPD
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F3    0x4300   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F2    0x4304   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F1    0x4308   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D29_F0    0x430C   ///< SPC
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F3    0x4310   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F2    0x4314   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F1    0x4318   ///< SPA
#define R_VER2_PCH_H_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F0    0x431C   ///< SPA

//
// PSF1 grant count registers
//
#define R_VER2_PCH_LP_PSF1_PCR_DEV_GNTCNT_RELOAD_DGCR0           0x43A0
#define R_VER2_PCH_LP_PSF1_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0     0x456C

#define R_VER2_PCH_H_PSF1_PCR_DEV_GNTCNT_RELOAD_DGCR0            0x43C4
#define R_VER2_PCH_H_PSF1_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0      0x44F4

//
// PSF2 PCRs (PID:PSF2)
//
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_GBETSN_REG_BASE          0x0100               ///< D30F4 PSF base address (GBE TSN)
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_THC0_REG_BASE            0x0180               ///< D16F6 PSF base address (THC#0)
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_THC1_REG_BASE            0x0200               ///< D16F7 PSF base address (THC#1)
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_UFS1_REG_BASE            0x0280               ///< D18F5 PSF base address (SCC: UFS#1)
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_UFS2_REG_BASE            0x0300               ///< D18F7 PSF base address (SCC: UFS#2)
#define R_VER2_PCH_LP_PSF2_PCR_T0_SHDW_XDCI_REG_BASE            0x0400               ///< D20F1 PSF base address (XDCI)

#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_AUD_REG_BASE              0x0100               ///< D31F3 PSF base address (cAVS)
#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_TSN0_REG_BASE             0x0200               ///< D30F4 PSF base address (GBE TSN0)
#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_TSN1_REG_BASE             0x0280               ///< D30F5 PSF base address (GBE TSN1)
#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_UFS1_REG_BASE             0x0300               ///< D18F5 PSF base address (UFS #1)
#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_UFS2_REG_BASE             0x0380               ///< D18F7 PSF base address (UFS #2)
#define R_VER2_PCH_H_PSF2_PCR_T0_SHDW_XDCI_REG_BASE             0x0400               ///< D20F1 PSF base address (XDCI)

#define R_VER2_PCH_H_PSF2_PCR_DEV_GNTCNT_RELOAD_DGCR0           0x4248               ///< Grant Count Reload Register
#define R_VER2_PCH_H_PSF2_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0     0x434C

//
// PSF3 PCRs (PID:PSF3)
//
// PSF3 PCH-LP Specific Base Address
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_AUD_REG_BASE             0x0100                  ///< D31F3 PSF base address (HDAudio)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_BTCORE_REG_BASE          0x0200                  ///< D16F2 PSF base address (CNVi: BT)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_ISH_REG_BASE             0x0300                  ///< D18F0 PSF base address (ISH)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C0_REG_BASE            0x0500                  ///< D21F0 PSF base address (I2C #0)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C1_REG_BASE            0x0580                  ///< D21F1 PSF base address (I2C #1)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C2_REG_BASE            0x0600                  ///< D21F2 PSF base address (I2C #2)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C3_REG_BASE            0x0680                  ///< D21F3 PSF base address (I2C #3)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C4_REG_BASE            0x0700                  ///< D25F0 PSF base address (I2C #4)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C5_REG_BASE            0x0780                  ///< D25F1 PSF base address (I2C #5)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C6_REG_BASE            0x0800                  ///< D16F0 PSF base address (I2C #6)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_I2C7_REG_BASE            0x0880                  ///< D16F1 PSF base address (I2C #7)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI0_REG_BASE            0x0900                  ///< D30F2 PSF base address (SPI #0)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI1_REG_BASE            0x0980                  ///< D30F3 PSF base address (SPI #1)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI2_REG_BASE            0x0A00                  ///< D18F6 PSF base address (SPI #2)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI3_REG_BASE            0x0A80                  ///< D19F0 PSF base address (SPI #3)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI4_REG_BASE            0x0B00                  ///< D19F1 PSF base address (SPI #4)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI5_REG_BASE            0x0B80                  ///< D19F2 PSF base address (SPI #5)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI6_REG_BASE            0x0C00                  ///< D19F3 PSF base address (SPI #6)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART0_REG_BASE           0x0C80                  ///< D30F0 PSF base address (UART #0)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART1_REG_BASE           0x0D00                  ///< D30F1 PSF base address (UART #1)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART2_REG_BASE           0x0D80                  ///< D25F2 PSF base address (UART #2)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART3_REG_BASE           0x0E00                  ///< D17F0 PSF base address (UART #3)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART4_REG_BASE           0x0E80                  ///< D17F1 PSF base address (UART #4)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART5_REG_BASE           0x0F00                  ///< D17F2 PSF base address (UART #5)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_UART6_REG_BASE           0x0F80                  ///< D17F3 PSF base address (UART #6)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_P2S_REG_BASE             0x1080                  ///< D31F1 PSF base address (P2SB)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_PMC_REG_BASE             0x1100                  ///< D31F2 PSF base address (PMC)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SHARED_SRAM_REG_BASE     0x1180                  ///< D20F2 PSF base address (Shared SRAM)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SMBUS_REG_BASE           0x1280                  ///< D31F4 PSF base address (SMBus)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_SPI_REG_BASE             0x1300                  ///< D31F5 PSF base address (SPI Controller)
#define R_VER2_PCH_LP_PSF3_PCR_T0_SHDW_CNVI_REG_BASE            0x1500                  ///< D20F3 PSF base address (CNVi: WiFi)

// PSF3 PCH-H Specific Base Address
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_GBE_REG_BASE              0x0100                  ///< D31F6 PSF base address (GBE)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_ISH_REG_BASE              0x0200                  ///< D18F0 PSF base address (ISH)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C0_REG_BASE             0x0400                  ///< D21F0 PSF base address (I2C #0)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C1_REG_BASE             0x0480                  ///< D21F1 PSF base address (I2C #1)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C2_REG_BASE             0x0500                  ///< D21F2 PSF base address (I2C #2)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C3_REG_BASE             0x0580                  ///< D21F3 PSF base address (I2C #3)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C4_REG_BASE             0x0600                  ///< D25F0 PSF base address (I2C #4)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C5_REG_BASE             0x0680                  ///< D25F1 PSF base address (I2C #5)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C6_REG_BASE             0x0700                  ///< D16F0 PSF base address (I2C #6)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_I2C7_REG_BASE             0x0780                  ///< D16F1 PSF base address (I2C #7)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI0_REG_BASE             0x0800                  ///< D30F2 PSF base address (SPI #0)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI1_REG_BASE             0x0880                  ///< D30F3 PSF base address (SPI #1)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI2_REG_BASE             0x0900                  ///< D18F6 PSF base address (SPI #2)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI3_REG_BASE             0x0980                  ///< D19F0 PSF base address (SPI #3)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI4_REG_BASE             0x0A00                  ///< D19F1 PSF base address (SPI #4)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI5_REG_BASE             0x0A80                  ///< D19F2 PSF base address (SPI #5)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI6_REG_BASE             0x0B00                  ///< D19F3 PSF base address (SPI #6)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART0_REG_BASE            0x0B80                  ///< D30F0 PSF base address (UART #0)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART1_REG_BASE            0x0C00                  ///< D30F1 PSF base address (UART #1)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART2_REG_BASE            0x0C80                  ///< D25F2 PSF base address (UART #2)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART3_REG_BASE            0x0D00                  ///< D17F0 PSF base address (UART #3)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART4_REG_BASE            0x0D80                  ///< D17F1 PSF base address (UART #4)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART5_REG_BASE            0x0E00                  ///< D17F2 PSF base address (UART #5)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_UART6_REG_BASE            0x0E80                  ///< D17F3 PSF base address (UART #6)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_P2S_REG_BASE              0x0F80                  ///< D31F1 PSF base address (P2SB)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_PMC_REG_BASE              0x1000                  ///< D31F2 PSF base address (PMC)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SHARED_SRAM_REG_BASE      0x1080                  ///< D20F2 PSF base address (Shared SRAM)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SMBUS_REG_BASE            0x1180                  ///< D31F4 PSF base address (SMBUS)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_SPI_REG_BASE              0x1200                  ///< D31F5 PSF base address (SPI)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_THC0_REG_BASE             0x1400                  ///< D16F6 PSF base address (THC0)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_THC1_REG_BASE             0x1480                  ///< D16F7 PSF base address (THC1)
#define R_VER2_PCH_H_PSF3_PCR_T0_SHDW_CNVI_REG_BASE             0x1500                  ///< D20F3 PSF base address (CMVi: WiFi)

#define R_VER2_PCH_LP_PSF3_PCR_MC_CONTROL_MCAST0_EOI            0x4054                  ///< Multicast Control Register
#define R_VER2_PCH_LP_PSF3_PCR_MC_AGENT_MCAST0_TGT0_EOI         0x4060                  ///< Destination ID

#define R_VER2_PCH_H_PSF3_PCR_MC_CONTROL_MCAST0_EOI             0x4058                  ///< Multicast Control Register
#define R_VER2_PCH_H_PSF3_PCR_MC_AGENT_MCAST0_TGT0_EOI          0x4064                  ///< Destination ID


//
// PSF4 PCRs (PID:PSF4)
//
//
// PSF4 grant count registers
//
#define R_VER2_PCH_LP_PSF4_PCR_DEV_GNTCNT_RELOAD_DGCR0       0x4064                  ///< Grant Count Reload Register
#define R_VER2_PCH_H_PSF4_PCR_DEV_GNTCNT_RELOAD_DGCR0        0x40AC                  ///< Grant Count Reload Register

//
// PSF7 PCRs (PID:PSF7)
//
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE01_REG_BASE        0x2000        ///< PCH-H D28F0 PSF base address (PCIE PORT 01)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE02_REG_BASE        0x2080        ///< PCH-H D28F1 PSF base address (PCIE PORT 02)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE03_REG_BASE        0x2100        ///< PCH-H D28F2 PSF base address (PCIE PORT 03)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE04_REG_BASE        0x2180        ///< PCH-H D28F3 PSF base address (PCIE PORT 04)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE09_REG_BASE        0x2200        ///< PCH-H D29F0 PSF base address (PCIE PORT 09)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE10_REG_BASE        0x2280        ///< PCH-H D29F1 PSF base address (PCIE PORT 10)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE11_REG_BASE        0x2300        ///< PCH-H D29F2 PSF base address (PCIE PORT 11)
#define R_VER2_PCH_H_PSF7_PCR_T1_SHDW_PCIE12_REG_BASE        0x2380        ///< PCH-H D29F3 PSF base address (PCIE PORT 12)

#define R_VER2_PCH_H_PSF7_PCR_MC_CONTROL_MCAST0_EOI                  0x4030          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF7_PCR_MC_AGENT_MCAST0_TGT0_EOI               0x4048          ///< Destination ID
#define R_VER2_PCH_H_PSF7_PCR_MC_CONTROL_MCAST1_RS0_MCTP1            0x403C          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF7_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1         0x4070          ///< Destination ID

#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_D29_F3    0x4098          ///< SPC
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_D29_F2    0x409C          ///< SPC
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_D29_F1    0x40A0          ///< SPC
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_D29_F0    0x40A4          ///< SPC
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_D28_F3    0x40A8          ///< SPA
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_D28_F2    0x40AC          ///< SPA
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_D28_F1    0x40B0          ///< SPA
#define R_VER2_PCH_H_PSF7_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_D28_F0    0x40B4          ///< SPA

#define R_VER2_PCH_H_PSF7_PCR_DEV_GNTCNT_RELOAD_DGCR0        0x40BC
#define R_VER2_PCH_H_PSF7_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0  0x4178

//
// PSF8 PCRs (PID:PSF8)
//
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE13_REG_BASE        0x2000                  ///< PCH-H D29F4 PSF base address (PCIE PORT 13)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE14_REG_BASE        0x2080                  ///< PCH-H D29F5 PSF base address (PCIE PORT 14)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE15_REG_BASE        0x2100                  ///< PCH-H D29F6 PSF base address (PCIE PORT 15)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE16_REG_BASE        0x2180                  ///< PCH-H D29F7 PSF base address (PCIE PORT 16)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE17_REG_BASE        0x2200                  ///< PCH-H D27F0 PSF base address (PCIE PORT 17)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE18_REG_BASE        0x2280                  ///< PCH-H D27F1 PSF base address (PCIE PORT 18)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE19_REG_BASE        0x2300                  ///< PCH-H D27F2 PSF base address (PCIE PORT 19)
#define R_VER2_PCH_H_PSF8_PCR_T1_SHDW_PCIE20_REG_BASE        0x2380                  ///< PCH-H D27F3 PSF base address (PCIE PORT 20)

#define R_VER2_PCH_H_PSF8_PCR_MC_CONTROL_MCAST0_EOI                  0x4030          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF8_PCR_MC_AGENT_MCAST0_TGT0_EOI               0x4048          ///< Destination ID
#define R_VER2_PCH_H_PSF8_PCR_MC_CONTROL_MCAST1_RS0_MCTP1            0x403C          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF8_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1         0x4070          ///< Destination ID

#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_D27_F3    0x4098          ///< SPE
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_D27_F2    0x409C          ///< SPE
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_D27_F1    0x40A0          ///< SPE
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPE_D27_F0    0x40A4          ///< SPE
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_D29_F7    0x40A8          ///< SPD
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_D29_F6    0x40AC          ///< SPD
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_D29_F5    0x40B0          ///< SPD
#define R_VER2_PCH_H_PSF8_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_D29_F4    0x40B4          ///< SPD

#define R_VER2_PCH_H_PSF8_PCR_DEV_GNTCNT_RELOAD_DGCR0        0x40BC
#define R_VER2_PCH_H_PSF8_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0  0x4178

//
// PSF9 PCRs (PID:PSF9)
//
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE05_REG_BASE        0x2000                  ///< PCH-H D28F4 PSF base address (PCIE PORT 05)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE06_REG_BASE        0x2080                  ///< PCH-H D28F5 PSF base address (PCIE PORT 06)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE07_REG_BASE        0x2100                  ///< PCH-H D28F6 PSF base address (PCIE PORT 07)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE08_REG_BASE        0x2180                  ///< PCH-H D28F7 PSF base address (PCIE PORT 08)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE21_REG_BASE        0x2200                  ///< PCH-H D27F4 PSF base address (PCIE PORT 21)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE22_REG_BASE        0x2280                  ///< PCH-H D27F5 PSF base address (PCIE PORT 22)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE23_REG_BASE        0x2300                  ///< PCH-H D27F6 PSF base address (PCIE PORT 23)
#define R_VER2_PCH_H_PSF9_PCR_T1_SHDW_PCIE24_REG_BASE        0x2380                  ///< PCH-H D27F7 PSF base address (PCIE PORT 24)

#define R_VER2_PCH_H_PSF9_PCR_MC_CONTROL_MCAST0_EOI                  0x4030          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF9_PCR_MC_AGENT_MCAST0_TGT0_EOI               0x4048          ///< Destination ID
#define R_VER2_PCH_H_PSF9_PCR_MC_CONTROL_MCAST1_RS0_MCTP1            0x403C          ///< Multicast Control Register
#define R_VER2_PCH_H_PSF9_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1         0x4070          ///< Destination ID

#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_D27_F7    0x4098          ///< SPF
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_D27_F6    0x409C          ///< SPF
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_D27_F5    0x40A0          ///< SPF
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPF_D27_F4    0x40A4          ///< SPF
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_D28_F7    0x40A8          ///< SPB
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_D28_F6    0x40AC          ///< SPB
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_D28_F5    0x40B0          ///< SPB
#define R_VER2_PCH_H_PSF9_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_D28_F4    0x40B4          ///< SPB

#define R_VER2_PCH_H_PSF9_PCR_DEV_GNTCNT_RELOAD_DGCR0        0x40BC
#define R_VER2_PCH_H_PSF9_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0  0x4178

#endif
