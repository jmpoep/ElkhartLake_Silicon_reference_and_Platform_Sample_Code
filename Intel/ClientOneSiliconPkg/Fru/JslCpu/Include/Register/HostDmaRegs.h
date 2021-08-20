/** @file
  Register names for Host DMA Block
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
#ifndef _SA_REGS_HOST_DMA_H_
#define _SA_REGS_HOST_DMA_H_

#define SA_MAX_HOST_ITBT_DMA_NUMBER     2
//
// Device 13 (decimal) Function 2/3 Equates (Host DMAx , x=0/1)
//
#define SA_HOST_DMA_BUS_NUM        0x00
#define SA_HOST_DMA_DEV_NUM        0x0D

#define SA_HOST_DMA0_FUN_NUM       0x02
#define SA_HOST_DMA1_FUN_NUM       0x03

#define R_SA_HOST_DMA_LBAR         0x10
#define R_SA_HOST_DMA_UBAR         0x14

#define R_SA_HOST_DMA_CFG_PM_CAP_1                   0x84
#define B_SA_HOST_DMA_PME_EN                         BIT8
#define B_SA_HOST_DMA_PME_STATUS                     BIT15
#define R_SA_HOST_DMA_ITBT_NVM_FW_REVISION           0XC8
#define R_SA_HOST_DMA_ITBT_SECURITY_LEVEL            0xCC
#define R_SA_HOST_DMA_ITBT_TBT2PCIE_LC               0XEC
#define R_SA_HOST_DMA_ITBT_PCIE2TBT_LC               0xF0
#define R_SA_HOST_DMA_RTD3_FORCEPOWER                0XFC
#define B_SA_HOST_DMA_RTD3_EN                        BIT0
#define B_SA_HOST_DMA_FORCEPOWER_EN                  BIT1
#define N_SA_HOST_DMA_DMA_ACTIVE_DELAY_OFFSET        24
#define B_SA_HOST_DMA_DMA_ACTIVE_DELAY_MASK          0xFF000000
#define V_SA_HOST_DMA_DMA_ACTIVE_DELAY_VALUE         0x22
#define R_SA_HOST_DMA_UUID                           0xD0
#define R_SA_HOST_DMA_CFG_LTR_CAP                    0xE4

#endif
