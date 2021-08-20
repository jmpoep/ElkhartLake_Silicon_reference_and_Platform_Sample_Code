/** @file
  Register names for PCH Serial IO Controllers

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

@par Specification Reference:
**/
#ifndef _SERIAL_IO_REGS_H_
#define _SERIAL_IO_REGS_H_

//
// Serial IO Controllers PCI Configuration Registers
// registers accessed using PciD21FxRegBase + offset
//
#define R_SERIAL_IO_CFG_BAR0_LOW                            0x10
#define R_SERIAL_IO_CFG_BAR0_HIGH                           0x14
#define R_SERIAL_IO_CFG_BAR1_LOW                            0x18
#define R_SERIAL_IO_CFG_BAR1_HIGH                           0x1C

#define R_SERIAL_IO_CFG_PME_CTRL_STS                        0x84
#define B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST                 (BIT1| BIT0)

#define R_SERIAL_IO_CFG_D0I3MAXDEVPG                        0xA0
#define B_SERIAL_IO_CFG_D0I3MAXDEVPG_PMCRE                  BIT16
#define B_SERIAL_IO_CFG_D0I3MAXDEVPG_I3E                    BIT17
#define B_SERIAL_IO_CFG_D0I3MAXDEVPG_PGE                    BIT18

//
// Serial IO Controllers MMIO Registers
// registers accessed : BAR0 + offset
//
#define R_SERIAL_IO_MEM_SSCR0                               0x00
#define B_SERIAL_IO_MEM_SSCR0_TIM                           BIT23
#define B_SERIAL_IO_MEM_SSCR0_RIM                           BIT22
#define B_SERIAL_IO_MEM_SSCR0_SSE                           BIT7
#define B_SERIAL_IO_MEM_SSCR0_DSS_16_32                     0x0F

#define R_SERIAL_IO_MEM_SSCR1                               0x04
#define B_SERIAL_IO_MEM_SSCR1_IFS                           BIT16

#define R_SERIAL_IO_MEM_SSITR                               0x0C

#define R_SERIAL_IO_MEM_SSSR                                0x08
#define B_SERIAL_IO_MEM_SSSR_BSY                            BIT4
#define B_SERIAL_IO_MEM_SSSR_TNF                            BIT2
#define B_SERIAL_IO_MEM_SSSR_RNE                            BIT3

#define R_SERIAL_IO_MEM_SSDR                                0x10

#define R_SERIAL_IO_MEM_SIRF                                0x48

#define R_SERIAL_IO_MEM_PPR_RESETS_8BIT                     0x81
#define R_SERIAL_IO_MEM_PPR_CLK                             0x200
#define B_SERIAL_IO_MEM_PPR_CLK_EN                          BIT0
#define B_SERIAL_IO_MEM_PPR_CLK_UPDATE                      BIT31
#define V_SERIAL_IO_MEM_PPR_CLK_M_VAL                       BIT16
#define V_SERIAL_IO_MEM_PPR_CLK_N_VAL                       BIT1
#define V_SERIAL_IO_MEM_PPR_CLK_M_DIV                       0x25A
#define V_SERIAL_IO_MEM_PPR_CLK_N_DIV                       0x7FFF

#define R_SERIAL_IO_MEM_PPR_RESETS                          0x204
#define B_SERIAL_IO_MEM_PPR_RESETS_FUNC                     BIT0
#define B_SERIAL_IO_MEM_PPR_RESETS_APB                      BIT1
#define B_SERIAL_IO_MEM_PPR_RESETS_IDMA                     BIT2

#define R_SERIAL_IO_MEM_SPI_CS_CONTROL                      0x224

//
// Bridge Private Configuration Registers
// accessed only through SB messaging. SB access = SerialIo IOSF2OCP Bridge Port ID + offset
//
#define R_SERIAL_IO_PCR_PMCTL                               0x1D0
#define V_SERIAL_IO_PCR_PMCTL_PWR_GATING                    0x3F
//
//  PCI Config Control
//
#define B_SERIAL_IO_PCR_PCICFGCTRL_PCI_CFG_DIS              BIT0
#define B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_INTR_EN             BIT1
#define B_SERIAL_IO_PCR_PCICFGCTRL_BAR1_DIS                 BIT7
#define B_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN                  (BIT11 | BIT10 | BIT9 | BIT8)
#define N_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN                  8
#define V_SERIAL_IO_PCR_PCICFGCTRL_INTA                     0x01
#define V_SERIAL_IO_PCR_PCICFGCTRL_INTB                     0x02
#define V_SERIAL_IO_PCR_PCICFGCTRL_INTC                     0x03
#define V_SERIAL_IO_PCR_PCICFGCTRL_INTD                     0x04
#define B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_IRQ                 0x000FF000
#define N_SERIAL_IO_PCR_PCICFGCTRL_ACPI_IRQ                 12
#define B_SERIAL_IO_PCR_PCICFGCTRL_PCI_IRQ                  0x0FF00000
#define N_SERIAL_IO_PCR_PCICFGCTRL_PCI_IRQ                  20
//
//  General Purpose
//
#define R_SERIAL_IO_PCR_GPPRVRW2                            0x604
#define B_SERIAL_IO_PCR_GPPRVRW2_PGCB_FRC_CLK_CP_EN         BIT1
#define B_SERIAL_IO_PCR_GPPRVRW2_CDC_SIDE_CFG_CG_EN         BIT5
#define B_SERIAL_IO_PCR_GPPRVRW2_CDC_SIDE_CFG_CLKREQ_CTL_EN BIT11
#define V_SERIAL_IO_PCR_GPPRVRW2_CLK_GATING                 (B_SERIAL_IO_PCR_GPPRVRW2_PGCB_FRC_CLK_CP_EN | B_SERIAL_IO_PCR_GPPRVRW2_CDC_SIDE_CFG_CG_EN | B_SERIAL_IO_PCR_GPPRVRW2_CDC_SIDE_CFG_CLKREQ_CTL_EN)

#endif //_SERIAL_IO_REGS_H_
