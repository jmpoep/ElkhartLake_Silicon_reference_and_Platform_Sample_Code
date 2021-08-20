/** @file
  Register names for ICL GPIO

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
  Copyright 2016 - 2017 Intel Corporation.

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
#ifndef _PCH_REGS_GPIO_ICL_H_
#define _PCH_REGS_GPIO_ICL_H_

//
// PCH-LP GPIO
//
#define ICL_PCH_LP_GPIO_GPP_A_PAD_MAX         25
#define ICL_PCH_LP_GPIO_GPP_B_PAD_MAX         26
#define ICL_PCH_LP_GPIO_GPP_C_PAD_MAX         24
#define ICL_PCH_LP_GPIO_GPP_D_PAD_MAX         21
#define ICL_PCH_LP_GPIO_GPP_E_PAD_MAX         24
#define ICL_PCH_LP_GPIO_GPP_F_PAD_MAX         20
#define ICL_PCH_LP_GPIO_GPP_G_PAD_MAX         8
#define ICL_PCH_LP_GPIO_GPP_H_PAD_MAX         24
#define ICL_PCH_LP_GPIO_GPP_R_PAD_MAX         8
#define ICL_PCH_LP_GPIO_GPP_S_PAD_MAX         8
#define ICL_PCH_LP_GPIO_GPD_PAD_MAX           17
#define ICL_PCH_LP_GPIO_VGPIO_PAD_MAX         29
#define ICL_PCH_LP_GPIO_SPI_PAD_MAX           9
#define ICL_PCH_LP_GPIO_CPU_PAD_MAX           15
#define ICL_PCH_LP_GPIO_JTAG_PAD_MAX          9
#define ICL_PCH_LP_GPIO_HVCMOS_PAD_MAX        6

#define ICL_PCH_LP_GPIO_GROUP_MAX             16

//
// PCH-N GPIO
//
#define ICL_PCH_N_GPIO_GPP_A_PAD_MAX         21
#define ICL_PCH_N_GPIO_GPP_B_PAD_MAX         26
#define ICL_PCH_N_GPIO_GPP_C_PAD_MAX         24
#define ICL_PCH_N_GPIO_GPP_D_PAD_MAX         26
#define ICL_PCH_N_GPIO_GPP_E_PAD_MAX         24
#define ICL_PCH_N_GPIO_GPP_G_PAD_MAX         8
#define ICL_PCH_N_GPIO_GPP_H_PAD_MAX         24
#define ICL_PCH_N_GPIO_GPP_R_PAD_MAX         8
#define ICL_PCH_N_GPIO_GPP_S_PAD_MAX         8
#define ICL_PCH_N_GPIO_GPD_PAD_MAX           15
#define ICL_PCH_N_GPIO_VGPIO_PAD_MAX         29
#define ICL_PCH_N_GPIO_VGPIO_3_PAD_MAX       92
#define ICL_PCH_N_GPIO_VGPIO_4_PAD_MAX       4
#define ICL_PCH_N_GPIO_SPI_PAD_MAX           9
#define ICL_PCH_N_GPIO_CPU_PAD_MAX           15
#define ICL_PCH_N_GPIO_JTAG_PAD_MAX          9
#define ICL_PCH_N_GPIO_HVCMOS_PAD_MAX        6

#define ICL_PCH_N_GPIO_GROUP_MAX             17

//
// GPIO Community Common Private Configuration Registers
//
#define B_ICL_PCH_GPIO_PCR_MISCCFG_IRQ_ROUTE         0xFF000000
#define N_ICL_PCH_GPIO_PCR_MISCCFG_IRQ_ROUTE         24

//
// PCH-LP GPIO registers
//
//
// GPIO Community Common Private Configuration Registers
//
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_A     0x2
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_B     0x1
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_C     0xA
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_D     0x7
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_E     0xB
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_F     0x8
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_G     0x0
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_H     0x6
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_R     0x3
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPP_S     0x4
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_GPD       0x5
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_VGPIO     0x9
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_SPI       0xF
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_CPU       0xF
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_JTAG      0xF
#define V_ICL_PCH_LP_GPIO_PCR_MISCCFG_GPE0_HVCMOS    0xF

//
// GPIO Community 0 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_PAD_OWN        0x20
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_PAD_OWN        0x24
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_PAD_OWN        0x34

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_PADCFGLOCK     0x80
#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_PADCFGLOCKTX   0x84
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_PADCFGLOCK     0x88
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_PADCFGLOCK     0x90
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_PADCFGLOCKTX   0x94

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_HOSTSW_OWN     0xB0
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_HOSTSW_OWN     0xB4
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_HOSTSW_OWN     0xB8

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_GPI_IS         0x0100
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_GPI_IS         0x0104
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_GPI_IS         0x0108

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_GPI_IE         0x0110
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_GPI_IE         0x0114
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_GPI_IE         0x0118

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_GPI_GPE_STS    0x0130
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_GPI_GPE_STS    0x0134
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_GPI_GPE_STS    0x0138

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_GPI_GPE_EN     0x0150
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_GPI_GPE_EN     0x0154
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_GPI_GPE_EN     0x0158

//#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_SMI_STS        0x0170  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_SMI_STS        0x0174
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_SMI_STS        0x0178  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_SMI_EN         0x0190  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_SMI_EN         0x0194
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_SMI_EN         0x0198  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_NMI_STS        0x01B0  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_NMI_STS        0x01B4
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_NMI_STS        0x01B8  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_NMI_EN         0x01D0  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_NMI_EN         0x01D4
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_NMI_EN         0x01D8  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_G_PADCFG_OFFSET  0x600
#define R_ICL_PCH_LP_GPIO_PCR_GPP_B_PADCFG_OFFSET  0x680
#define R_ICL_PCH_LP_GPIO_PCR_GPP_A_PADCFG_OFFSET  0x820

//
// GPIO Community 1 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_PAD_OWN        0x20
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_PAD_OWN        0x2C
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_PAD_OWN        0x38
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_PAD_OWN        0x44

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_PADCFGLOCK     0x80
#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_PADCFGLOCKTX   0x84
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_PADCFGLOCK     0x88
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_PADCFGLOCK     0x90
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_PADCFGLOCKTX   0x94
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_0_PADCFGLOCK   0x98
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_0_PADCFGLOCKTX 0x9C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_HOSTSW_OWN     0xB0
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_HOSTSW_OWN     0xB4
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_HOSTSW_OWN     0xB8
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_HOSTSW_OWN     0xBC

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_GPI_IS         0x0100
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_GPI_IS         0x0104
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_GPI_IS         0x0108
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_GPI_IS         0x010C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_GPI_IE         0x0110
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_GPI_IE         0x0114
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_GPI_IE         0x0118
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_GPI_IE         0x011C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_GPI_GPE_STS    0x0130
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_GPI_GPE_STS    0x0134
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_GPI_GPE_STS    0x0138
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_GPI_GPE_STS    0x013C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_GPI_GPE_EN     0x0150
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_GPI_GPE_EN     0x0154
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_GPI_GPE_EN     0x0158
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_GPI_GPE_EN     0x015C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_SMI_STS        0x0170
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_SMI_STS        0x0174  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_SMI_STS        0x0178  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_SMI_STS        0x017C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_SMI_EN         0x0190
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_SMI_EN         0x0194  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_SMI_EN         0x0198  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_SMI_EN         0x019C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_NMI_STS        0x01B0
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_NMI_STS        0x01B4  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_NMI_STS        0x01B8  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_NMI_STS        0x01BC  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_NMI_EN         0x01D0
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_NMI_EN         0x01D4  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_NMI_EN         0x01D8  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_NMI_EN         0x01DC  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_H_PADCFG_OFFSET  0x600
#define R_ICL_PCH_LP_GPIO_PCR_GPP_D_PADCFG_OFFSET  0x780
#define R_ICL_PCH_LP_GPIO_PCR_GPP_F_PADCFG_OFFSET  0x8D0
#define R_ICL_PCH_LP_GPIO_PCR_VGPIO_PADCFG_OFFSET  0xA10

//
// GPIO Community 2 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_GPD_PAD_OWN          0x20

#define R_ICL_PCH_LP_GPIO_PCR_GPD_PADCFGLOCK       0x80
#define R_ICL_PCH_LP_GPIO_PCR_GPD_PADCFGLOCKTX     0x84

#define R_ICL_PCH_LP_GPIO_PCR_GPD_HOSTSW_OWN       0xB0

#define R_ICL_PCH_LP_GPIO_PCR_GPD_GPI_IS           0x0100
#define R_ICL_PCH_LP_GPIO_PCR_GPD_GPI_IE           0x0110

#define R_ICL_PCH_LP_GPIO_PCR_GPD_GPI_GPE_STS      0x0130
#define R_ICL_PCH_LP_GPIO_PCR_GPD_GPI_GPE_EN       0x0150

//#define R_ICL_PCH_LP_GPIO_PCR_GPD_SMI_STS        0x0170  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPD_SMI_EN         0x0190  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_GPD_NMI_STS        0x01B0  // Not supported setting for this group
//#define R_ICL_PCH_LP_GPIO_PCR_GPD_NMI_EN         0x01D0  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPD_PADCFG_OFFSET    0x600

//
// GPIO Community 3 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_CPU_PAD_OWN          0x20

#define R_ICL_PCH_LP_GPIO_PCR_CPU_PADCFGLOCK       0x80
#define R_ICL_PCH_LP_GPIO_PCR_CPU_PADCFGLOCKTX     0x84

#define R_ICL_PCH_LP_GPIO_PCR_CPU_HOSTSW_OWN       0xB0

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_GPI_IS           0x0100  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_GPI_IE           0x0110  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_GPI_GPE_STS      0x0130  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_GPI_GPE_EN       0x0150  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_SMI_STS          0x0170  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_SMI_EN           0x0190  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_NMI_STS          0x01B0  // Not supported setting for this group

//#define R_ICL_PCH_LP_GPIO_PCR_CPU_NMI_EN           0x01D0  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_CPU_PADCFG_OFFSET    0x600

//
// GPIO Community 4 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_PAD_OWN        0x20
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_PAD_OWN       0x2C
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_PAD_OWN        0x30
#define R_ICL_PCH_LP_GPIO_PCR_JTAG_PAD_OWN         0x3C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_PADCFGLOCK     0x80
#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_PADCFGLOCKTX   0x84
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_PADCFGLOCK    0x88
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_PADCFGLOCKTX  0x8C
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_PADCFGLOCK     0x90
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_PADCFGLOCKTX   0x94
#define R_ICL_PCH_LP_GPIO_PCR_JTAG_PADCFGLOCK      0x98
#define R_ICL_PCH_LP_GPIO_PCR_JTAG_PADCFGLOCKTX    0x9C

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_HOSTSW_OWN     0xB0
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_HOSTSW_OWN    0xB4
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_HOSTSW_OWN     0xB8
#define R_ICL_PCH_LP_GPIO_PCR_JTAG_HOSTSW_OWN      0xBC

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_GPI_IS         0x0100
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_GPI_IS        0x0104
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_GPI_IS         0x0108
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_GPI_IS          0x010C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_GPI_IE         0x0110
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_GPI_IE        0x0114
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_GPI_IE         0x0118
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_GPI_IE          0x011C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_GPI_GPE_STS    0x0130
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_GPI_GPE_STS   0x0134
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_GPI_GPE_STS    0x0138
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_GPI_GPE_STS     0x013C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_GPI_GPE_EN     0x0150
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_GPI_GPE_EN    0x0154
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_GPI_GPE_EN     0x0158
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_GPI_GPE_EN      0x015C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_SMI_STS        0x0170
//#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_SMI_STS       0x0174  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_SMI_STS        0x0178
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_SMI_STS         0x017C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_SMI_EN         0x0190
//#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_SMI_EN        0x0194  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_SMI_EN         0x0198
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_SMI_EN          0x019C  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_NMI_STS        0x01B0
//#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_NMI_STS       0x01B4  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_NMI_STS        0x01B8
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_NMI_STS         0x01BC  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_NMI_EN         0x01D0
//#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_NMI_EN        0x01D4  // Not supported setting for this group
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_NMI_EN         0x01D8
//#define R_ICL_PCH_LP_GPIO_PCR_JTAG_NMI_EN          0x01DC  // Not supported setting for this group

#define R_ICL_PCH_LP_GPIO_PCR_GPP_C_PADCFG_OFFSET  0x600
#define R_ICL_PCH_LP_GPIO_PCR_HVCMOS_PADCFG_OFFSET 0x780
#define R_ICL_PCH_LP_GPIO_PCR_GPP_E_PADCFG_OFFSET  0x7E0
#define R_ICL_PCH_LP_GPIO_PCR_JTAG_PADCFG_OFFSET   0x960

//
// GPIO Community 5 Private Configuration Registers
//
#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_PAD_OWN        0x20
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_PAD_OWN        0x30
#define R_ICL_PCH_LP_GPIO_PCR_SPI_PAD_OWN          0x40

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_PADCFGLOCK     0x80
#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_PADCFGLOCKTX   0x84
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_PADCFGLOCK     0x88
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_LP_GPIO_PCR_SPI_PADCFGLOCK       0x90
#define R_ICL_PCH_LP_GPIO_PCR_SPI_PADCFGLOCKTX     0x94

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_HOSTSW_OWN     0xB0
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_HOSTSW_OWN     0xB4
#define R_ICL_PCH_LP_GPIO_PCR_SPI_HOSTSW_OWN       0xB8

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_GPI_IS         0x0100
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_GPI_IS         0x0104
#define R_ICL_PCH_LP_GPIO_PCR_SPI_GPI_IS           0x0108

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_GPI_IE         0x0110
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_GPI_IE         0x0114
#define R_ICL_PCH_LP_GPIO_PCR_SPI_GPI_IE           0x0118

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_GPI_GPE_STS    0x0130
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_GPI_GPE_STS    0x0134
#define R_ICL_PCH_LP_GPIO_PCR_SPI_GPI_GPE_STS      0x0138

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_GPI_GPE_EN     0x0150
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_GPI_GPE_EN     0x0154
#define R_ICL_PCH_LP_GPIO_PCR_SPI_GPI_GPE_EN       0x0158

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_SMI_STS        0x0170
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_SMI_STS        0x0174
#define R_ICL_PCH_LP_GPIO_PCR_SPI_SMI_STS          0x0178

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_SMI_EN         0x0190
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_SMI_EN         0x0194
#define R_ICL_PCH_LP_GPIO_PCR_SPI_SMI_EN           0x0198

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_NMI_STS        0x01B0
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_NMI_STS        0x01B4
#define R_ICL_PCH_LP_GPIO_PCR_SPI_NMI_STS          0x01B8

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_NMI_EN         0x01D0
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_NMI_EN         0x01D4
#define R_ICL_PCH_LP_GPIO_PCR_SPI_NMI_EN           0x01D8

#define R_ICL_PCH_LP_GPIO_PCR_GPP_R_PADCFG_OFFSET  0x600
#define R_ICL_PCH_LP_GPIO_PCR_GPP_S_PADCFG_OFFSET  0x790
#define R_ICL_PCH_LP_GPIO_PCR_SPI_PADCFG_OFFSET    0x930

//
// PCH-N GPIO registers
//
//
// GPIO Community Common Private Configuration Registers
//
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_A     0x0
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_B     0x1
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_C     0x3
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_D     0x5
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_E     0xD
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_G     0x2
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_H     0x7
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_R     0x4
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPP_S     0x6
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_GPD       0xA
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_VGPIO     0x8
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_VGPIO_3   0xF
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_VGPIO_4   0xF
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_SPI       0xF
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_CPU       0xF
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_JTAG      0xF
#define V_ICL_PCH_N_GPIO_PCR_MISCCFG_GPE0_HVCMOS    0xF

//
// GPIO Community 0 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_SPI_PAD_OWN          0x20
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_PAD_OWN        0x28
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_PAD_OWN        0x38
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_PAD_OWN        0x44
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_PAD_OWN        0x48

#define R_ICL_PCH_N_GPIO_PCR_SPI_PADCFGLOCK       0x80
#define R_ICL_PCH_N_GPIO_PCR_SPI_PADCFGLOCKTX     0x84
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_PADCFGLOCK     0x88
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_PADCFGLOCK     0x90
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_PADCFGLOCKTX   0x94
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_PADCFGLOCK     0x98
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_PADCFGLOCKTX   0x9C
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_PADCFGLOCK     0xA0
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_PADCFGLOCKTX   0xA4

#define R_ICL_PCH_N_GPIO_PCR_SPI_HOSTSW_OWN       0xB0
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_HOSTSW_OWN     0xB4
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_HOSTSW_OWN     0xB8
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_HOSTSW_OWN     0xBC
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_HOSTSW_OWN     0xC0

#define R_ICL_PCH_N_GPIO_PCR_SPI_GPI_IS           0x0100
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_GPI_IS         0x0104
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_GPI_IS         0x0108
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_GPI_IS         0x010C
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_GPI_IS         0x0110

#define R_ICL_PCH_N_GPIO_PCR_SPI_GPI_IE           0x0120
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_GPI_IE         0x0124
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_GPI_IE         0x0128
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_GPI_IE         0x012C
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_GPI_IE         0x0130

#define R_ICL_PCH_N_GPIO_PCR_SPI_GPI_GPE_STS      0x0140
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_GPI_GPE_STS    0x0144
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_GPI_GPE_STS    0x0148
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_GPI_GPE_STS    0x014C
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_GPI_GPE_STS    0x0150

#define R_ICL_PCH_N_GPIO_PCR_SPI_GPI_GPE_EN       0x0160
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_GPI_GPE_EN     0x0164
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_GPI_GPE_EN     0x0168
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_GPI_GPE_EN     0x016C
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_GPI_GPE_EN     0x0170

//#define R_ICL_PCH_N_GPIO_PCR_SPI_SMI_STS          0x0180  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_SMI_STS        0x0184
//#define R_ICL_PCH_N_GPIO_PCR_GPP_A_SMI_STS        0x0188  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_S_SMI_STS        0x018C  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_R_SMI_STS        0x0190  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_SPI_SMI_EN           0x01A0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_SMI_EN         0x01A4
//#define R_ICL_PCH_N_GPIO_PCR_GPP_A_SMI_EN         0x01A8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_S_SMI_EN         0x01AC  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_R_SMI_EN         0x01B0  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_SPI_NMI_STS          0x01C0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_NMI_STS        0x01C4
//#define R_ICL_PCH_N_GPIO_PCR_GPP_A_NMI_STS        0x01C8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_S_NMI_STS        0x01CC  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_R_NMI_STS        0x01D0  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_SPI_NMI_EN           0x01E0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_NMI_EN         0x01E4
//#define R_ICL_PCH_N_GPIO_PCR_GPP_A_NMI_EN         0x01E8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_S_NMI_EN         0x01EC  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPP_R_NMI_EN         0x01F0  // Not supported setting for this group

#define R_ICL_PCH_N_GPIO_PCR_SPI_PADCFG_OFFSET    0x600
#define R_ICL_PCH_N_GPIO_PCR_GPP_B_PADCFG_OFFSET  0x690
#define R_ICL_PCH_N_GPIO_PCR_GPP_A_PADCFG_OFFSET  0x830
#define R_ICL_PCH_N_GPIO_PCR_GPP_S_PADCFG_OFFSET  0x980
#define R_ICL_PCH_N_GPIO_PCR_GPP_R_PADCFG_OFFSET  0xA00

//
// GPIO Community 1 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_GPP_H_PAD_OWN        0x20
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_PAD_OWN        0x2C
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_PAD_OWN        0x3C
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_PAD_OWN        0x4C

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_PADCFGLOCK     0x80
#define R_ICL_PCH_N_GPIO_PCR_GPP_H_PADCFGLOCKTX   0x84
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_PADCFGLOCK     0x88
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_PADCFGLOCK     0x90
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_PADCFGLOCKTX   0x94
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_PADCFGLOCK     0x98
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_PADCFGLOCKTX   0x9C

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_HOSTSW_OWN     0xB0
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_HOSTSW_OWN     0xB4
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_HOSTSW_OWN     0xB8
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_HOSTSW_OWN     0xBC

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_GPI_IS         0x0100
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_GPI_IS         0x0104
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_GPI_IS         0x0108
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_GPI_IS         0x010C

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_GPI_IE         0x0120
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_GPI_IE         0x0124
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_GPI_IE         0x0128
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_GPI_IE         0x012C

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_GPI_GPE_STS    0x0140
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_GPI_GPE_STS    0x0144
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_GPI_GPE_STS    0x0148
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_GPI_GPE_STS    0x014C

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_GPI_GPE_EN     0x0160
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_GPI_GPE_EN     0x0164
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_GPI_GPE_EN     0x0168
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_GPI_GPE_EN     0x016C

//#define R_ICL_PCH_N_GPIO_PCR_GPP_H_SMI_STS        0x0180  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_SMI_STS        0x0184
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_SMI_STS        0x0188  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_SMI_STS        0x018C

//#define R_ICL_PCH_N_GPIO_PCR_GPP_H_SMI_EN         0x01A0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_SMI_EN         0x01A4
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_SMI_EN         0x01A8  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_SMI_EN         0x01AC

//#define R_ICL_PCH_N_GPIO_PCR_GPP_H_NMI_STS        0x01C0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_NMI_STS        0x01C4
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_NMI_STS        0x01C8  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_NMI_STS        0x01CC

//#define R_ICL_PCH_N_GPIO_PCR_GPP_H_NMI_EN         0x01E0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_NMI_EN         0x01E4
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_NMI_EN         0x01E8  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_NMI_EN         0x01EC

#define R_ICL_PCH_N_GPIO_PCR_GPP_H_PADCFG_OFFSET  0x600
#define R_ICL_PCH_N_GPIO_PCR_GPP_D_PADCFG_OFFSET  0x780
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_PADCFG_OFFSET  0x920
#define R_ICL_PCH_N_GPIO_PCR_GPP_C_PADCFG_OFFSET  0xAF0

//
// GPIO Community 2 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_GPD_PAD_OWN          0x20

#define R_ICL_PCH_N_GPIO_PCR_GPD_PADCFGLOCK       0x80
#define R_ICL_PCH_N_GPIO_PCR_GPD_PADCFGLOCKTX     0x84

#define R_ICL_PCH_N_GPIO_PCR_GPD_HOSTSW_OWN       0xB0

#define R_ICL_PCH_N_GPIO_PCR_GPD_GPI_IS           0x0100
#define R_ICL_PCH_N_GPIO_PCR_GPD_GPI_IE           0x0120

#define R_ICL_PCH_N_GPIO_PCR_GPD_GPI_GPE_STS      0x0140
#define R_ICL_PCH_N_GPIO_PCR_GPD_GPI_GPE_EN       0x0160

//#define R_ICL_PCH_N_GPIO_PCR_GPD_SMI_STS        0x0180  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPD_SMI_EN         0x01A0  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_GPD_NMI_STS        0x01C0  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_GPD_NMI_EN         0x01E0  // Not supported setting for this group

#define R_ICL_PCH_N_GPIO_PCR_GPD_PADCFG_OFFSET    0x600

//
// GPIO Community 3 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_CPU_PAD_OWN          0x20
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_PAD_OWN      0x28

#define R_ICL_PCH_N_GPIO_PCR_CPU_PADCFGLOCK       0x80
#define R_ICL_PCH_N_GPIO_PCR_CPU_PADCFGLOCKTX     0x84
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_PADCFGLOCK   0x88
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_PADCFGLOCKTX 0x8C

#define R_ICL_PCH_N_GPIO_PCR_CPU_HOSTSW_OWN       0xB0
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_HOSTSW_OWN   0xB4

//#define R_ICL_PCH_N_GPIO_PCR_CPU_GPI_IS           0x0100  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_GPI_IS       0x0104  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_GPI_IE           0x0120  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_GPI_IE       0x0124  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_GPI_GPE_STS      0x0140  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_GPI_GPE_STS  0x0144  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_GPI_GPE_EN       0x0160  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_GPI_GPE_EN   0x0164  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_SMI_STS          0x0180  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_SMI_STS      0x0184  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_SMI_EN           0x01A0  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_SMI_EN       0x01A4  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_NMI_STS          0x01C0  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_NMI_STS      0x01C4  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_CPU_NMI_EN           0x01E0  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_NMI_EN       0x01E4  // Not supported setting for this group

#define R_ICL_PCH_N_GPIO_PCR_CPU_PADCFG_OFFSET      0x600
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_3_PADCFG_OFFSET  0x6F0

//
// GPIO Community 4 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_PAD_OWN       0x20
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_PAD_OWN        0x24
#define R_ICL_PCH_N_GPIO_PCR_JTAG_PAD_OWN         0x30
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_PAD_OWN      0x38

#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_PADCFGLOCK    0x80
#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_PADCFGLOCKTX  0x84
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_PADCFGLOCK     0x88
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_PADCFGLOCKTX   0x8C
#define R_ICL_PCH_N_GPIO_PCR_JTAG_PADCFGLOCK      0x90
#define R_ICL_PCH_N_GPIO_PCR_JTAG_PADCFGLOCKTX    0x94
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_PADCFGLOCK   0x98
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_PADCFGLOCKTX 0x9C

#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_HOSTSW_OWN    0xB0
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_HOSTSW_OWN     0xB4
#define R_ICL_PCH_N_GPIO_PCR_JTAG_HOSTSW_OWN      0xB8
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_HOSTSW_OWN   0xBC

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_GPI_IS        0x0100  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_GPI_IS         0x0104
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_GPI_IS          0x0108  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_GPI_IS       0x010C  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_GPI_IE        0x0120  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_GPI_IE         0x0124
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_GPI_IE          0x0128  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_GPI_IE       0x012C  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_GPI_GPE_STS   0x0140  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_GPI_GPE_STS    0x0144
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_GPI_GPE_STS     0x0148  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_GPI_GPE_STS  0x014C  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_GPI_GPE_EN    0x0160  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_GPI_GPE_EN     0x0164
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_GPI_GPE_EN      0x0168  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_GPI_GPE_EN   0x016C  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_SMI_STS       0x0180  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_SMI_STS        0x0184
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_SMI_STS         0x0188  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_SMI_STS      0x018C  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_SMI_EN        0x01A0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_SMI_EN         0x01A4
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_SMI_EN          0x01A8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_SMI_EN       0x01AC  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_NMI_STS       0x01C0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_NMI_STS        0x01C4
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_NMI_STS         0x01C8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_NMI_STS      0x01CC  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_NMI_EN        0x01E0  // Not supported setting for this group
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_NMI_EN         0x01E4
//#define R_ICL_PCH_N_GPIO_PCR_JTAG_NMI_EN          0x01E8  // Not supported setting for this group
//#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_NMI_EN       0x01EC  // Not supported setting for this group

#define R_ICL_PCH_N_GPIO_PCR_HVCMOS_PADCFG_OFFSET 0x600
#define R_ICL_PCH_N_GPIO_PCR_GPP_E_PADCFG_OFFSET  0x660
#define R_ICL_PCH_N_GPIO_PCR_JTAG_PADCFG_OFFSET   0x7E0
#define R_ICL_PCH_N_GPIO_PCR_VGPIO_4_PADCFG_OFFSET 0x870

//
// GPIO Community 5 Private Configuration Registers
//
#define R_ICL_PCH_N_GPIO_PCR_GPP_G_PAD_OWN        0x20

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_PADCFGLOCK     0x80
#define R_ICL_PCH_N_GPIO_PCR_GPP_G_PADCFGLOCKTX   0x84

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_HOSTSW_OWN     0xB0

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_GPI_IS         0x0100

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_GPI_IE         0x0120

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_GPI_GPE_STS    0x0140

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_GPI_GPE_EN     0x0160

//#define R_ICL_PCH_N_GPIO_PCR_GPP_G_SMI_STS        0x0180  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_GPP_G_SMI_EN         0x01A0  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_GPP_G_NMI_STS        0x01C0  // Not supported setting for this group

//#define R_ICL_PCH_N_GPIO_PCR_GPP_G_NMI_EN         0x01E0  // Not supported setting for this group

#define R_ICL_PCH_N_GPIO_PCR_GPP_G_PADCFG_OFFSET  0x600

//
// GPIO native features pins data
//
#define ICL_PCH_GPIO_DDSP_HPD_NUMBER_OF_PINS           7
#define ICL_PCH_GPIO_DDP_NUMBER_OF_INTERFACES          7
#endif
