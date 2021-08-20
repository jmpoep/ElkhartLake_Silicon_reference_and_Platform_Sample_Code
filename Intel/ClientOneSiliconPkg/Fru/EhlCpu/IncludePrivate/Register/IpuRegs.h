/** @file
  Register names for IPU block
  <b>Conventions</b>:
  - Prefixes:
    - Definitions beginning with "R_" are registers
    - Definitions beginning with "B_" are bits within registers
    - Definitions beginning with "V_" are meaningful values of bits within the registers
    - Definitions beginning with "S_" are register sizes
    - Definitions beginning with "N_" are the bit position
  - IPU registers are denoted by "_IPU_" in register names
  - Registers / bits that are different between IPU generations are denoted by
    "_IPU_[generation_name]_" in register/bit names. e.g., "_IPU_TGL_"
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a IPU generation will be just named
    as "_IPU_" without [generation_name] inserted.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _IPU_REGS_H_
#define _IPU_REGS_H_

//
// Device 5 Equates
//
#define IPU_BUS_NUM    0x00
#define IPU_DEV_NUM    0x05
#define IPU_FUN_NUM    0x00


#define R_IPU_LBAR      (0x10)
#define R_IPU_UBAR      (0x14)
#define B_IPU_LBAR_MASK (0xff000000)
#define R_IPUBAR_FUSA_IPU_OVERRIDE   (0xB6C)
#define IPUBAR_BASE_ADDRESS   (0xF7000000)     ///< Temporary BAR address at PEI phase


#define R_VTD_IPU_LBAR  (0xf0)
#define R_VTD_IPU_UBAR  (0xf4)

#endif  // _IPU_REGS_H_
