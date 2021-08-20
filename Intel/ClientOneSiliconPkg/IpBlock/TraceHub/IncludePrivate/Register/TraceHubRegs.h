/** @file
  Register names for TraceHub device

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
  Copyright 2013 - 2019 Intel Corporation.

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

#ifndef _TRACE_HUB_REGS_H_
#define _TRACE_HUB_REGS_H_

//
// PCH TraceHub Registers (D31:F7)
//
#define PCI_DEVICE_NUMBER_PCH_TRACE_HUB                             31
#define PCI_FUNCTION_NUMBER_PCH_TRACE_HUB                           7

//
// CPU TraceHub Registers (D9:F0)
//
#define PCI_BUS_NUMBER_CPU_TRACE_HUB                                0
#define PCI_DEVICE_NUMBER_CPU_TRACE_HUB                             9
#define PCI_FUNCTION_NUMBER_CPU_TRACE_HUB                           0

#define R_TRACE_HUB_CFG_CSR_MTB_LBAR                                0x10
#define B_TRACE_HUB_CFG_CSR_MTB_RBAL                                0xFFF00000
#define R_TRACE_HUB_CFG_CSR_MTB_UBAR                                0x14
#define B_TRACE_HUB_CFG_CSR_MTB_RBAU                                0xFFFFFFFF
#define R_TRACE_HUB_CFG_SW_LBAR                                     0x18
#define B_TRACE_HUB_CFG_SW_RBAL                                     0xFF800000
#define R_TRACE_HUB_CFG_SW_UBAR                                     0x1C
#define B_TRACE_HUB_CFG_SW_RBAU                                     0xFFFFFFFF
#define R_TRACE_HUB_CFG_RTIT_LBAR                                   0x20
#define B_TRACE_HUB_CFG_RTIT_RBAL                                   0xFFFFFF00
#define R_TRACE_HUB_CFG_RTIT_UBAR                                   0x24
#define B_TRACE_HUB_CFG_RTIT_RBAU                                   0xFFFFFFFF
#define R_TRACE_HUB_CFG_MSICID                                      0x40
#define R_TRACE_HUB_CFG_MSINCP                                      0x41
#define R_TRACE_HUB_CFG_MSIMC                                       0x42
#define R_TRACE_HUB_CFG_MSILMA                                      0x44
#define R_TRACE_HUB_CFG_MSIUMA                                      0x48
#define R_TRACE_HUB_CFG_MSIMD                                       0x4C
#define R_TRACE_HUB_CFG_FW_LBAR                                     0x70
#define B_TRACE_HUB_CFG_FW_RBAL                                     0xFFE00000
#define R_TRACE_HUB_CFG_FW_UBAR                                     0x74
#define B_TRACE_HUB_CFG_FW_RBAU                                     0xFFFFFFFF
#define R_TRACE_HUB_CFG_DSC                                         0x80
#define B_TRACE_HUB_CFG_BYP                                         BIT0 //< TraceHub Bypass
#define R_TRACE_HUB_CFG_DSS                                         0x81
#define R_TRACE_HUB_CFG_ISTOT                                       0x84
#define R_TRACE_HUB_CFG_ICTOT                                       0x88
#define R_TRACE_HUB_CFG_IPAD                                        0x8C
#define R_TRACE_HUB_CFG_DSD                                         0x90
#define R_TRACE_HUB_CFG_DEVIDLEPCE                                  0xB4
#define B_TRACE_HUB_CFG_DEVIDLEPCE_HAE                              BIT5
#define B_TRACE_HUB_CFG_DEVIDLEPCE_SE                               BIT3
#define B_TRACE_HUB_CFG_DEVIDLEPCE_D3HEN                            BIT2
#define B_TRACE_HUB_CFG_DEVIDLEPCE_DEVIDLEN                         BIT1
#define B_TRACE_HUB_CFG_DEVIDLEPCE_PMCRE                            BIT0

//
// Offsets from CSR_MTB_BAR
//
#define R_TRACE_HUB_MEM_MTB_GTHOPT0                                 0x00
#define B_TRACE_HUB_MEM_MTB_GTHOPT0_P0FLUSH                         BIT7
#define B_TRACE_HUB_MEM_MTB_GTHOPT0_P1FLUSH                         BIT15
#define V_TRACE_HUB_MEM_MTB_SWDEST_PTI                              0x0A
#define V_TRACE_HUB_MEM_MTB_SWDEST_MEMEXI                           0x08
#define V_TRACE_HUB_MEM_MTB_SWDEST_DISABLE                          0x00
#define R_TRACE_HUB_MEM_MTB_SWDEST_1                                0x0C
#define B_TRACE_HUB_MEM_MTB_SWDEST_CSE_1                            0x0000000F
#define B_TRACE_HUB_MEM_MTB_SWDEST_CSE_2                            0x000000F0
#define B_TRACE_HUB_MEM_MTB_SWDEST_CSE_3                            0x00000F00
#define B_TRACE_HUB_MEM_MTB_SWDEST_ISH_1                            0x0000F000
#define B_TRACE_HUB_MEM_MTB_SWDEST_ISH_2                            0x000F0000
#define B_TRACE_HUB_MEM_MTB_SWDEST_ISH_3                            0x00F00000
#define B_TRACE_HUB_MEM_MTB_SWDEST_AUDIO                            0x0F000000
#define B_TRACE_HUB_MEM_MTB_SWDEST_PMC                              0xF0000000
#define R_TRACE_HUB_MEM_MTB_SWDEST_2                                0x10
#define B_TRACE_HUB_MEM_MTB_SWDEST_FTH                              0x0000000F
#define R_TRACE_HUB_MEM_MTB_SWDEST_3                                0x14
#define B_TRACE_HUB_MEM_MTB_SWDEST_MAESTRO                          0x00000F00
#define B_TRACE_HUB_MEM_MTB_SWDEST_MIPICAM                          0x0F000000
#define B_TRACE_HUB_MEM_MTB_SWDEST_AET                              0xF0000000
#define R_TRACE_HUB_MEM_MTB_SWDEST_4                                0x18
#define R_TRACE_HUB_MEM_MTB_80000                                   0x80000
#define V_TRACE_HUB_MEM_MTB_MSCNMODE_DCI                            0x2
#define V_TRACE_HUB_MEM_MTB_MSCNMODE_DEBUG                          0x3
#define B_TRACE_HUB_MEM_MTB_MSCNLEN                                 (BIT10 | BIT9 | BIT8)
#define B_TRACE_HUB_MEM_MTB_MSCNMODE                                (BIT5 | BIT4)
#define N_TRACE_HUB_MEM_MTB_MSCNMODE                                0x4
#define B_TRACE_HUB_MEM_MTB_MSCN_RD_HDR_OVRD                        BIT2
#define B_TRACE_HUB_MEM_MTB_WRAPENN                                 BIT1
#define B_TRACE_HUB_MEM_MTB_MSCNEN                                  BIT0
#define R_TRACE_HUB_MEM_MTB_GTHSTAT                                 0xD4
#define R_TRACE_HUB_MEM_MTB_SCR2                                    0xD8
#define B_TRACE_HUB_MEM_MTB_SCR2_FCD                                BIT0
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF2                            BIT2
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF3                            BIT3
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF4                            BIT4
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF5                            BIT5
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF6                            BIT6
#define B_TRACE_HUB_MEM_MTB_SCR2_FSEOFF7                            BIT7
#define R_TRACE_HUB_MEM_MTB_MSC0CTL                                 0xA0100
#define B_TRACE_HUB_MEM_MTB_MSCCTL_MSCEN                            BIT0
#define R_TRACE_HUB_MEM_MTB_MSC0BAR                                 0xA0108
#define R_TRACE_HUB_MEM_MTB_MSC0SIZE                                0xA010C
#define R_TRACE_HUB_MEM_MTB_MSC1CTL                                 0xA0200
#define R_TRACE_HUB_MEM_MTB_MSC1BAR                                 0xA0208
#define R_TRACE_HUB_MEM_MTB_MSC1SIZE                                0xA020C
#define R_TRACE_HUB_MEM_MSUSPARE                                    0xA00FC
#define B_TRACE_HUB_MEM_MSUAPARE_ALLOW_MEM_ACCESS                   BIT1
#define B_TRACE_HUB_MEM_MSUAPARE_MSC0_LOCK                          BIT2
#define R_TRACE_HUB_MEM_MTB_STREAMCFG1                              0xA1000
#define R_TRACE_HUB_MEM_MTB_STREAMCFG2                              0xA1004
#define V_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET                   0x5C
#define N_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET                   12
#define R_TRACE_HUB_MEM_MTB_DBCSTSCMD                               0xA1008  // DbC.Trace Status Command
#define B_TRACE_HUB_MEM_MTB_STREAMCFG1_ENABLE                       BIT28
#define R_TRACE_HUB_MEM_MTB_DBC_BASE_LO                             0xA1028
#define V_PCH_TRACE_HUB_MEM_MTB_DBC_BASE_LO                         0xFED60000
#define V_CPU_TRACE_HUB_MEM_MTB_DBC_BASE_LO                         0xFED62000
#define V_TRACE_HUB_MEM_MTB_DBC_SIZE                                0x2000
#define R_TRACE_HUB_MEM_CSR_MTB_LPP_CTL                             0x1C00
#define B_TRACE_HUB_MEM_CSR_MTB_LPP_CTL_LPMEN                       BIT24
#define R_TRACE_HUB_MEM_MTB_SCR                                     0xC8
#define R_TRACE_HUB_MEM_MTB_GTH_FREQ                                0xCC
#define V_TRACE_HUB_MEM_MTB_SCR                                     0x00130000
#define R_TRACE_HUB_MEM_CSR_MTB_SCRPD0                              0xE0     // Scratch Pad 0 Register
#define R_TRACE_HUB_MEM_CSR_MTB_SCRPD1                              0xE4
#define B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE              BIT24
#define B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_MEM_IS_PRIM_DEST             BIT0
#define V_TRACE_HUB_MEM_MTB_STHMSTR                                 0x100
#define V_TRACE_HUB_MEM_MTB_FTHMSTR                                 0x10
#define V_TRACE_HUB_MEM_MTB_CHLCNT                                  0x80
#define R_TRACE_HUB_MEM_CSR_MTB_TSUCTRL                             0x2000
#define B_TRACE_HUB_MEM_CSR_MTB_TSUCTRL_CTCRESYNC                   BIT0

#define R_TRACE_HUB_MEM_MTB_STHCAP0                                 0x4000
#define R_TRACE_HUB_MEM_MTB_STHCAP1                                 0x4004
/**
 Description of RTIT_CNT (23:16)
**/
  #define N_TRACE_HUB_MEM_MTB_STHCAP1_RTITCNT_OFFSET                0x10
  #define S_TRACE_HUB_MEM_MTB_STHCAP1_RTITCNT_WIDTH                 0x8
  #define B_TRACE_HUB_MEM_MTB_STHCAP1_RTITCNT_MASK                  0xff0000
  #define V_TRACE_HUB_MEM_MTB_STHCAP1_RTITCNT_DEFAULT               0x8

#define R_TRACE_HUB_MEM_MTB_SDC                                     0x5000
/**
 Description of CE(CHAP Enable) (15:15)
**/
  #define N_TRACE_HUB_MEM_MTB_SDC_CE_OFFSET                         0xF
  #define S_TRACE_HUB_MEM_MTB_SDC_CE_WIDTH                          0x1
  #define B_TRACE_HUB_MEM_MTB_SDC_CE_MASK                           0x8000
  #define V_TRACE_HUB_MEM_MTB_SDC_CE_DEFAULT                        0x0

#define R_TRACE_HUB_MEM_MTB_PMTCS                                   0xFFD00
#define B_TRACE_HUB_MEM_MTB_PMTCS_BLKDRNEN                          BIT0
#define B_TRACE_HUB_MEM_MTB_PMTCS_WSYNC                             BIT16

#endif
