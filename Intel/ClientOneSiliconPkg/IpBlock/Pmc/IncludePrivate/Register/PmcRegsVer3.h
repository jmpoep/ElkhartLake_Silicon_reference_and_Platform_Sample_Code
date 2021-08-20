/** @file
  Register names for Ver3 PCH PMC device

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
  Copyright 2017 - 2020 Intel Corporation.

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
#ifndef _PCH_REGS_PMC_EHL_H_
#define _PCH_REGS_PMC_EHL_H_

//
// PWRM Registers
//
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_B     0x0
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_T     0x1
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_A     0x2
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_R     0x3
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPD       0x4 // DSW
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_V     0x5
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_H     0x6
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_D     0x7
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_U     0x8
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_VGPIO     0x9
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_F     0xA
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_C     0xB
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_E     0xC
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_G     0xD
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_GPP_S     0xE
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_SPI       0xF
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_HVCMOS    0xF
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_JTAG      0xF
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_CPU       0xF
#define V_EHL_PCH_PMC_PWRM_GPIO_CFG_VGPIO_3   0xF

#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_B     0x0
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_T     0x1
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_D     0x2
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_A     0x3 // Will redirect to GPP_V
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_R     0x4 // Will redirect to GPP_V
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_V     0x5
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPD       0x6 // DSW
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_H     0x7 // Will redirect to HVCMOS
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_U     0x8 // Will redirect to GPP_E
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_VGPIO     0x9
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_F     0xA
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_C     0xB
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_E     0xC
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_G     0xD
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_GPP_S     0xE
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_SPI       0xF
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_HVCMOS    0xF
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_JTAG      0xF
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_CPU       0xF
#define V_EHL_PCH_A0_PMC_PWRM_GPIO_CFG_VGPIO_3   0xF

#define R_EHL_PCH_PMC_PWRM_LPM_STS_LATCH_EN   0x1704 ///< Low Power Mode Status Latch Enable
#define R_EHL_PCH_PMC_PWRM_LPM_EN             0x179C ///< Low Power Mode Enable
#define R_EHL_PCH_PMC_PWRM_LPM_PRI            0x17A0 ///< Low Power Mode Priority

#endif // _PCH_REGS_PMC_EHL_H_