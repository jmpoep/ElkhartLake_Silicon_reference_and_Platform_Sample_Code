/** @file
  Register names for TraceHub block
  <b>Conventions</b>:
  - Prefixes:
    - Definitions beginning with "R_" are registers
    - Definitions beginning with "B_" are bits within registers
    - Definitions beginning with "V_" are meaningful values of bits within the registers
    - Definitions beginning with "S_" are register sizes
    - Definitions beginning with "N_" are the bit position
  - In general, SA registers are denoted by "_SA_" in register names
  - Registers / bits that are different between SA generations are denoted by
    "_SA_[generation_name]_" in register/bit names. e.g., "_SA_HSW_"
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a SA generation will be just named
    as "_SA_" without [generation_name] inserted.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _SA_REGS_TRACEHUB_H_
#define _SA_REGS_TRACEHUB_H_

//
// DEVICE 9 (North TraceHub)
//
#define SA_TH_BUS                   (0x00)
#define SA_TH_DEV                   (0x09)
#define SA_TH_FUN                   (0x00)

#define R_SA_MTB_LBAR                  (0x10)
#define R_SA_MTB_UBAR                  (0x14)

#define R_SA_SW_LBAR                   (0x18)
#define R_SA_SW_UBAR                   (0x1C)

#define R_SA_RTIT_LBAR                 (0x20)
#define R_SA_RTIT_UBAR                 (0x24)

#define R_SA_FW_LBAR                   (0x70)
#define R_SA_FW_UBAR                   (0x74)
/**
 Description of SPTY [Space Type] (0:0)
**/
  #define N_SA_SPTY_OFFSET   (0x0)
  #define S_SA_SPTY_WIDTH    (0x1)
  #define B_SA_SPTY_MASK     (0x1)
  #define V_SA_SPTY_DEFAULT  (0x0)
/**
 Description of ADRNG [Address Range] (2:1)
 - When set to 10b, this BAR can be located anywhere in memory.
**/
  #define N_SA_ADRNG_OFFSET  (0x1)
  #define S_SA_ADRNG_WIDTH   (0x2)
  #define B_SA_ADRNG_MASK    (0x6)
  #define V_SA_ADRNG_DEFAULT (0x2)
/**
 Description of PF [Prefechable] (3:3)
 - When set to 0b, data in this BAR cannot be prefeched.
**/
  #define N_SA_PF_OFFSET     (0x3)
  #define S_SA_PF_WIDTH      (0x1)
  #define B_SA_PF_MASK       (0x8)
  #define V_SA_PF_DEFAULT    (0x0)

#define R_SA_TRACE_HUB_ISTOT         (0x84)

/**
 Offsets from CSR_MTB_BAR
**/

#define R_SA_SCRPD0                  (0xE0)
/**
 Description of DEBUGGER_IN_USE (24:24)
 - When set to 1b, this bit will lock all bits in this register.
**/
  #define N_SA_DEBUGGER_IN_USE_OFFSET   (0x18)
  #define S_SA_DEBUGGER_IN_USE_WIDTH    (0x1)
  #define B_SA_DEBUGGER_IN_USE_MASK     (0x1000000)
  #define V_SA_DEBUGGER_IN_USE_DEFAULT  (0x0)

#define R_SA_SCRPD1                  (0xE4)
#define R_SA_SCRPD2                  (0xE8)
#define R_SA_SCRPD3                  (0xEC)

#define R_SA_TRACE_HUB_LPP_CTL       (0x1C00)
#define B_SA_TRACE_HUB_LPP_CTL_LPMEN BIT24

#define R_SA_STHCAP0                 (0x4000)
#define R_SA_STHCAP1                 (0x4004)
/**
 Description of RTIT_CNT (23:16)
**/
  #define N_SA_STHCAP1_RTITCNT_OFFSET   (0x10)
  #define S_SA_STHCAP1_RTITCNT_WIDTH    (0x8)
  #define B_SA_STHCAP1_RTITCNT_MASK     (0xff0000)
  #define V_SA_STHCAP1_RTITCNT_DEFAULT  (0x8)

#define R_SA_SDC                     (0x5000)
/**
 Description of CE(CHAP Enable) (15:15)
**/
  #define N_SA_SDC_CE_OFFSET   (0xF)
  #define S_SA_SDC_CE_WIDTH    (0x1)
  #define B_SA_SDC_CE_MASK     (0x8000)
  #define V_SA_SDC_CE_DEFAULT  (0x0)

#define R_SA_VISACTLADDR             (0x20000)
#define R_SA_VISACTLDATA             (0x20004)

#define R_SA_MTB_MSC0CTL             (0xA0100)
#define B_SA_MTB_MSC0CTL_MSCNEN      BIT0

#define R_SA_MTB_MSC0BAR             (0xA0108)
#define R_SA_MTB_MSC1BAR             (0xA0208)

#define R_SA_MTB_MSC0DESTSZ          (0xA010C)
#define R_SA_MTB_MSC1DESTSZ          (0xA020C)

#define R_SA_MTB_STREAMCFG2              (0xA1004)
#define V_SA_MTB_STREAMCFG2_DBC_OFFSET   (0x5C)
#define N_SA_MTB_STREAMCFG2_DBC_OFFSET   (12)

#define R_SA_MTB_DBC_BASE_LO             (0xA1028)
#define V_SA_MTB_DBC_BASE_LO             (0xFED62000)
#define V_SA_MTB_DBC_SIZE                (0x2000)

#define R_SA_MTB_PMTCS               (0xFFD00)
#define B_SA_MTB_PMTCS_BLKDRNEN      BIT0
#define B_SA_MTB_PMTCS_WSYNC         BIT16
#endif
