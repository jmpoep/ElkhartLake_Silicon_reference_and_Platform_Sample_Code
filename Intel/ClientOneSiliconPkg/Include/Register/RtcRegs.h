/** @file
  Register names for RTC device

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
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _REGS_RTC_H_
#define _REGS_RTC_H_

#define R_RTC_IO_INDEX                           0x70
#define R_RTC_IO_TARGET                          0x71
#define R_RTC_IO_EXT_INDEX                       0x72
#define R_RTC_IO_EXT_TARGET                      0x73
#define R_RTC_IO_INDEX_ALT                       0x74
#define R_RTC_IO_TARGET_ALT                      0x75
#define R_RTC_IO_EXT_INDEX_ALT                   0x76
#define R_RTC_IO_EXT_TARGET_ALT                  0x77
#define R_RTC_IO_REGA                            0x0A
#define B_RTC_IO_REGA_UIP                        BIT7
#define R_RTC_IO_REGB                            0x0B
#define B_RTC_IO_REGB_SET                        0x80
#define B_RTC_IO_REGB_PIE                        0x40
#define B_RTC_IO_REGB_AIE                        0x20
#define B_RTC_IO_REGB_UIE                        0x10
#define B_RTC_IO_REGB_DM                         0x04
#define B_RTC_IO_REGB_HOURFORM                   0x02
#define R_RTC_IO_REGC                            0x0C
#define R_RTC_IO_REGD                            0x0D

//
// Private Configuration Register
// RTC PCRs (PID:RTC)
//
#define R_RTC_PCR_CONF                        0x3400               ///< RTC Configuration register
#define B_RTC_PCR_CONF_BILD                   BIT31                ///< BIOS Interface Lock-Down
#define B_RTC_PCR_CONF_HPM_HW_DIS             BIT6                 ///< RTC High Power Mode HW Disable
#define B_RTC_PCR_CONF_UCMOS_LOCK             BIT4                 ///< Upper 128 Byte Lock
#define B_RTC_PCR_CONF_LCMOS_LOCK             BIT3                 ///< Lower 128 Byte Lock
#define B_RTC_PCR_CONF_UCMOS_EN               BIT2                 ///< Upper CMOS bank enable
#define R_RTC_PCR_BUC                         0x3414               ///< Backed Up Control
#define B_RTC_PCR_BUC_DSO                     BIT4                 ///< Daylight Savings Override
#define B_RTC_PCR_BUC_TS                      BIT0                 ///< Top Swap
#define R_RTC_PCR_RTCDCG                      0x3418               ///< RTC Dynamic Clock Gating Control
#define B_RTC_PCR_RTCDCG_RTCPGCBDCGEN         BIT2                 ///< pgcb_clk (12Mhz) Dynamic Clock Gate Enable
#define B_RTC_PCR_RTCDCG_RTCPCICLKDCGEN       BIT1                 ///< ipciclk_clk (24 MHz) Dynamic Clock Gate Enable
#define B_RTC_PCR_RTCDCG_RTCROSIDEDCGEN       BIT0                 ///< rosc_side_clk (120 MHz) Dynamic Clock Gate Enable
#define R_RTC_PCR_3F00                        0x3F00
#define R_RTC_PCR_UIPSMI                      0x3F04               ///< RTC Update In Progress SMI Control

#endif
