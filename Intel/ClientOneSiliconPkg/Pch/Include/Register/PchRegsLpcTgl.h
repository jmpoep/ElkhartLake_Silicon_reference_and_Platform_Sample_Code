/** @file
  Register names for TGL PCH LPC/eSPI device

  Conventions:

  - Prefixes:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register sizes
    Definitions beginning with "N_" are the bit position
  - In general, PCH registers are denoted by "_PCH_" in register names
  - Registers / bits that are different between PCH generations are denoted by
    "_PCH_[generation_name]_" in register/bit names.
  - Registers / bits that are specific to PCH-H denoted by "_H_" in register/bit names.
    Registers / bits that are specific to PCH-LP denoted by "_LP_" in register/bit names.
    e.g., "_PCH_H_", "_PCH_LP_"
    Registers / bits names without _H_ or _LP_ apply for both H and LP.
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a PCH generation will be just named
    as "_PCH_" without [generation_name] inserted.

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
#ifndef _PCH_REGS_LPC_TGL_H_
#define _PCH_REGS_LPC_TGL_H_

#define V_LPC_CFG_DID_TGL_H                       0x4380
#define V_LPC_CFG_DID_TGL_LP                      0xA080

#define TGL_PCH_H_MIN_SUPPORTED_STEPPING          PCH_A0

//
// TGL PCH-LP Device IDs
//
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_0           0xA080        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_1           0xA081        ///< PCH LP Mobile U Super SKU (SSKU)
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_2           0xA082        ///< PCH LP Mobile U Premium
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_3           0xA083        ///< PCH LP Mobile U Base/Mainstream
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_4           0xA084        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_5           0xA085        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_6           0xA086        ///< PCH LP Mobile Y Super SKU (SSKU)
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_7           0xA087        ///< PCH LP Mobile Y Premium
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_8           0xA088        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_9           0xA089        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_10          0xA08A        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_11          0xA08B        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_12          0xA08C        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_13          0xA08D        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_14          0xA08E        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_15          0xA08F        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_16          0xA090        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_17          0xA091        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_18          0xA092        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_19          0xA093        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_20          0xA094        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_21          0xA095        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_22          0xA096        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_23          0xA097        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_24          0xA098        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_25          0xA099        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_26          0xA09A        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_27          0xA09B        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_28          0xA09C        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_29          0xA09D        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_30          0xA09E        ///< PCH LP Mobile SKU
#define V_TGL_PCH_LP_LPC_CFG_DEVICE_ID_MB_31          0xA09F        ///< PCH LP Mobile SKU

//
// TGL PCH-H Device IDs
//
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_0           0x4380        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_1           0x4381        ///< PCH H Mobile U Super SKU (SSKU)
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_2           0x4382        ///< PCH H Mobile U Premium
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_3           0x4383        ///< PCH H Mobile U Base/Mainstream
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_4           0x4384        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_5           0x4385        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_6           0x4386        ///< PCH H Mobile Y Super SKU (SSKU)
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_7           0x4387        ///< PCH H Mobile Y Premium
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_8           0x4388        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_9           0x4389        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_10          0x438A        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_11          0x438B        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_12          0x438C        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_13          0x438D        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_14          0x438E        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_15          0x438F        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_16          0x4390        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_17          0x4391        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_18          0x4392        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_19          0x4393        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_20          0x4394        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_21          0x4395        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_22          0x4396        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_23          0x4397        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_24          0x4398        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_25          0x4399        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_26          0x439A        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_27          0x439B        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_28          0x439C        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_29          0x439D        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_30          0x439E        ///< PCH H Mobile SKU
#define V_TGL_PCH_H_LPC_CFG_DEVICE_ID_MB_31          0x439F        ///< PCH H Mobile SKU

#endif
