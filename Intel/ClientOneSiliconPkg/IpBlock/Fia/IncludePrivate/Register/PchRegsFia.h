/** @file
  Register definition for FIA component

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
  Copyright 2014 - 2019 Intel Corporation.

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
#ifndef _PCH_REGS_FIA_H_
#define _PCH_REGS_FIA_H_


//
// Private chipset regsiter (Memory space) offset definition
// The PCR register defines is used for PCR MMIO programming and PCH SBI programming as well.
//

//
// PID:FIA
//
#define R_PCH_FIA_PCR_CC                                  0
#define B_PCH_FIA_PCR_CC_SRL                              BIT31
#define B_PCH_FIA_PCR_CC_PTOCGE                           BIT17
#define B_PCH_FIA_PCR_CC_OSCDCGE                          BIT16
#define B_PCH_FIA_PCR_CC_SCPTCGE                          BIT15

#define R_PCH_FIA_PCR_CLSDM                               0x18
#define B_PCH_FIA_PCR_CLSDM_DMIIPSLSD                     (BIT17 | BIT16)
#define B_PCH_FIA_PCR_CLSDM_PCIEGBEIPSLSD                 (BIT1 | BIT0)
#define R_PCH_FIA_PCR_PLLCTL                              0x20
#define B_PCH_FIA_PCR_PLLCTL_PLLCLKVADT                   (BIT30 | BIT29 | BIT28)
#define B_PCH_FIA_PCR_PLLCTL_CL0PLLWAIT                   (BIT13 | BIT12 | BIT11)
#define B_PCH_FIA_PCR_PLLCTL_PLLACBGD                     BIT31
#define B_PCH_FIA_PCR_PLLCTL_CL1PLLFO                     BIT1
#define B_PCH_FIA_PCR_PLLCTL_CL0PLLFO                     BIT0
#define N_PCH_FIA_PCR_PLLCTL_CL0PLLWAIT                   11
#define R_PCH_FIA_PCR_PMC                                 0x40
#define B_PCH_FIA_PCR_PMC_PRDPGE                          BIT3
#define R_PCH_FIA_PCR_SCDC                                0x44
#define R_PCH_FIA_PCR_PGCUC                               0x48
#define B_PCH_FIA_PCR_PGCUC_ACC_CLKGATE_DISABLED          BIT0
#define R_PCH_FIA_PCR_OCDC                                0x4C
#define R_PCH_FIA_PCR_PGCUCSOC                            0x50
#define B_PCH_FIA_PCR_PGCUCSOC_ACC_CLKGATE_DISABLED       BIT0

#define R_PCH_FIA_PCR_TREFCLKONTMR1                       0x180 // T refclkon timer 1, controls delay between CLKREQ asserted and CLKSRC
#define R_PCH_FIA_PCR_TREFCLKONTMR2                       0x184
#define R_PCH_FIA_PCR_TREFCLKONTMR3                       0x188
#define R_PCH_FIA_PCR_TREFCLKONTMR4                       0x18C
#define B_PCH_FIA_PCR_TREFCLKON_FIELD                     0xF   // each TREFCLKON field has 4 bits
#define S_PCH_FIA_PCR_TREFCLKON_FIELD                     4     // each TREFCLKON field has 4 bits
#define S_PCH_FIA_PCR_TREFCLKON_FIELDS_PER_REG            8     // there are 8 TREFCLKON fields per register
#define V_PCH_FIA_PCR_TREFCLKON_0us                       0x0
#define V_PCH_FIA_PCR_TREFCLKON_5us                       0x1
#define V_PCH_FIA_PCR_TREFCLKON_10us                      0x2
#define V_PCH_FIA_PCR_TREFCLKON_15us                      0x3
#define V_PCH_FIA_PCR_TREFCLKON_20us                      0x4
#define V_PCH_FIA_PCR_TREFCLKON_25us                      0x5
#define V_PCH_FIA_PCR_TREFCLKON_30us                      0x6
#define V_PCH_FIA_PCR_TREFCLKON_35us                      0x7
#define V_PCH_FIA_PCR_TREFCLKON_40us                      0x8
#define V_PCH_FIA_PCR_TREFCLKON_45us                      0x9
#define V_PCH_FIA_PCR_TREFCLKON_50us                      0xA
#define V_PCH_FIA_PCR_TREFCLKON_60us                      0xB
#define V_PCH_FIA_PCR_TREFCLKON_70us                      0xC
#define V_PCH_FIA_PCR_TREFCLKON_80us                      0xD
#define V_PCH_FIA_PCR_TREFCLKON_90us                      0xE
#define V_PCH_FIA_PCR_TREFCLKON_100us                     0xF

//
// PCH FIA lane owner encoding
//
#define V_PCH_FIA_PCR_LANE_OWN_PCIEDMI                    0x0
#define V_PCH_FIA_PCR_LANE_OWN_USB3                       0x1
#define V_PCH_FIA_PCR_LANE_OWN_SATA                       0x2
#define V_PCH_FIA_PCR_LANE_OWN_GBE                        0x3
#define V_PCH_FIA_PCR_LANE_OWN_MOBEXP                     0x4
#define V_PCH_FIA_PCR_LANE_OWN_SSIC                       0x5
#define V_PCH_FIA_PCR_LANE_OWN_CSI3                       0x6
#define V_PCH_FIA_PCR_LANE_OWN_UFS                        0x7
#define V_PCH_FIA_PCR_LANE_OWN_DISPLAY_PORT               0x8
#define V_PCH_FIA_PCR_LANE_OWN_THUNDERBOLT                0x9
#define V_PCH_FIA_PCR_LANE_OWN_HTI                        0xA
#define V_PCH_FIA_PCR_LANE_OWN_TSN                        0xB
#define V_PCH_FIA_PCR_LANE_OWN_PCIE2ND                    0xC

#define B_PCH_FIA_PCR_L0O                                 (BIT3 | BIT2 | BIT1 | BIT0)
#define B_PCH_FIA_PCR_L1O                                 (BIT7 | BIT6 | BIT5 | BIT4)
#define B_PCH_FIA_PCR_L2O                                 (BIT11 | BIT10 | BIT9 | BIT8)
#define B_PCH_FIA_PCR_L3O                                 (BIT15 | BIT14 | BIT13 | BIT12)
#define B_PCH_FIA_PCR_L4O                                 (BIT19 | BIT18 | BIT17 | BIT16)
#define B_PCH_FIA_PCR_L5O                                 (BIT23 | BIT22 | BIT21 | BIT20)
#define B_PCH_FIA_PCR_L6O                                 (BIT27 | BIT26 | BIT25 | BIT24)
#define B_PCH_FIA_PCR_L7O                                 (BIT31 | BIT30 | BIT29 | BIT28)
#define B_PCH_FIA_PCR_L8O                                 (BIT3 | BIT2 | BIT1 | BIT0)
#define B_PCH_FIA_PCR_L9O                                 (BIT7 | BIT6 | BIT5 | BIT4)
#define B_PCH_FIA_PCR_L10O                                (BIT11 | BIT10 | BIT9 | BIT8)
#define B_PCH_FIA_PCR_L11O                                (BIT15 | BIT14 | BIT13 | BIT12)
#define B_PCH_FIA_PCR_L12O                                (BIT19 | BIT18 | BIT17 | BIT16)
#define B_PCH_FIA_PCR_L13O                                (BIT23 | BIT22 | BIT21 | BIT20)
#define B_PCH_FIA_PCR_L14O                                (BIT27 | BIT26 | BIT25 | BIT24)
#define B_PCH_FIA_PCR_L15O                                (BIT31 | BIT30 | BIT29 | BIT28)
#define B_PCH_FIA_PCR_L16O                                (BIT3 | BIT2 | BIT1 | BIT0)
#define B_PCH_FIA_PCR_L17O                                (BIT7 | BIT6 | BIT5 | BIT4)
#define B_PCH_FIA_PCR_L18O                                (BIT11 | BIT10 | BIT9 | BIT8)
#define B_PCH_FIA_PCR_L19O                                (BIT15 | BIT14 | BIT13 | BIT12)
#define B_PCH_FIA_PCR_L20O                                (BIT19 | BIT18 | BIT17 | BIT16)
#define B_PCH_FIA_PCR_L21O                                (BIT23 | BIT22 | BIT21 | BIT20)
#define B_PCH_FIA_PCR_L22O                                (BIT27 | BIT26 | BIT25 | BIT24)
#define B_PCH_FIA_PCR_L23O                                (BIT31 | BIT30 | BIT29 | BIT28)
#define B_PCH_FIA_PCR_L24O                                (BIT3 | BIT2 | BIT1 | BIT0)
#define B_PCH_FIA_PCR_L25O                                (BIT7 | BIT6 | BIT5 | BIT4)
#define B_PCH_FIA_PCR_L26O                                (BIT11 | BIT10 | BIT9 | BIT8)
#define B_PCH_FIA_PCR_L27O                                (BIT15 | BIT14 | BIT13 | BIT12)
#define B_PCH_FIA_PCR_L28O                                (BIT19 | BIT18 | BIT17 | BIT16)
#define B_PCH_FIA_PCR_L29O                                (BIT23 | BIT22 | BIT21 | BIT20)
#define B_PCH_FIA_PCR_L30O                                (BIT27 | BIT26 | BIT25 | BIT24)
#define B_PCH_FIA_PCR_L31O                                (BIT31 | BIT30 | BIT29 | BIT28)
#define B_PCH_FIA_PCR_L32O                                (BIT3 | BIT2 | BIT1 | BIT0)
#define B_PCH_FIA_PCR_L33O                                (BIT7 | BIT6 | BIT5 | BIT4)
#define B_PCH_FIA_PCR_L34O                                (BIT11 | BIT10 | BIT9 | BIT8)
#define B_PCH_FIA_PCR_L35O                                (BIT15 | BIT14 | BIT13 | BIT12)
#define B_PCH_FIA_PCR_L36O                                (BIT19 | BIT18 | BIT17 | BIT16)
#define B_PCH_FIA_PCR_L37O                                (BIT23 | BIT22 | BIT21 | BIT20)

#endif
