/** @file
  Register definitions for Iosf2Ocp bridge.

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

#ifndef _SCS_IOSF2OCP_BRIDGE_REGS_H_
#define _SCS_IOSF2OCP_BRIDGE_REGS_H_
//
// SCS Iosf2Ocp bridge configuration registers
//
#define R_SCS_PCR_IOSFCTL                     0x00                          ///< IOSF Control
#define B_SCS_PCR_IOSFCTL_NSNPDIS             BIT7                          ///< Non-Snoop Disable
#define B_SCS_PCR_IOSFCTL_MAX_RD_PEND         (BIT3 | BIT2 | BIT1 | BIT0)   ///< Max upstream pending reads
#define R_SCS_PCR_OCPCTL                      0x10                          ///< OCP Control
#define B_SCS_PCR_OCPCTL_NPEN                 BIT0                          ///< Downstream non-posted memory write capability
#define R_SCS_PCR_PMCTL                       0x1D0                         ///< Power Management Control
#define R_SCS_PCR_PCICFGCTR_BASE              0x200
#define B_SCS_PCR_PCICFGCTR_BAR1DIS           BIT7                          ///< BAR 1 Disable
#define B_SCS_PCR_PCICFGCTR_PS                0x7C                          ///< PME Support
#define B_SCS_PCR_PCICFGCTR_ACPI_INT_EN       BIT1                          ///< ACPI Interrupt Enable
#define B_SCS_PCR_PCICFGCTR_PCI_CFG_DIS       BIT0                          ///< PCI Configuration Space Disable
#define B_SCS_PCR_PCICFGCTR_PCI_IRQ           0x0FF00000                    ///< PCI IRQ number
#define N_SCS_PCR_PCICFGCTR_PCI_IRQ           20
#define B_SCS_PCR_PCICFGCTR_ACPI_IRQ          0x000FF000                    ///< ACPI IRQ number
#define N_SCS_PCR_PCICFGCTR_ACPI_IRQ          12
#define B_SCS_PCR_PCICFGCTR_IPIN1             (BIT11 | BIT10 | BIT9 | BIT8) ///< Interrupt Pin
#define N_SCS_PCR_PCICFGCTR_IPIN1             8

#define R_SCS_PCR_GPPRVRW1                    0x600                         ///< Clock Gating Control
#define B_SCS_PCR_GPPRVRW1_PG_CG              0x7FFFFF                      ///< Clock and power gating control bits in GPPRVRW1
#define B_SCS_PCR_GPPRVRW1_UFS_XSOC           BIT13
#define B_SCS_PCR_GPPRVRW1_UFS0_ENABLE        BIT23
#define B_SCS_PCR_GPPRVRW1_UFS0_DUAL_LANE     BIT24
#define B_SCS_PCR_GPPRVRW1_UFS1_ENABLE        BIT25
#define B_SCS_PCR_GPPRVRW1_UFS1_DUAL_LANE     BIT26
#define B_SCS_PCR_GPPRVRW1_UFS0_IES           BIT30
#define B_SCS_PCR_GPPRVRW1_UFS1_IES           BIT31
#define R_SCS_PCR_GPPRVRW2                    0x604                         ///< Host Controller Disable
#define B_SCS_PCR_GPPRVRW2_VDD1_INVERT        BIT16                         ///< VDD1_Invert to 1 to make VDD1_POWER_ENABLE active LOW
#define R_SCS_PCR_GPPRVRW6                    0x614                         ///< 1.8V Signal Select Delay Control
#define B_SCS_PCR_GPPRVRW6_1P8_SEL_DELAY      0xFF
#define V_SCS_PCR_GPPRVRW6_1P8_SEL_DELAY      0x7F                          ///< Rcomp SDCARD 10ms delay during switch
#endif

