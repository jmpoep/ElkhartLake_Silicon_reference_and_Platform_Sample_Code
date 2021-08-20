/** @file
  Register names for ICL PCH LPC/eSPI device

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
  Copyright 2017 Intel Corporation.

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
#ifndef _PCH_REGS_LPC_ICL_H_
#define _PCH_REGS_LPC_ICL_H_

#define V_LPC_CFG_DID_ICL_H                       0x3D80
#define V_LPC_CFG_DID_ICL_LP                      0x3480
#define V_LPC_CFG_DID_ICL_N                       0x3880

#define ICL_PCH_H_MIN_SUPPORTED_STEPPING          PCH_A0
#define ICL_PCH_LP_MIN_SUPPORTED_STEPPING         PCH_A0
#define ICL_PCH_N_MIN_SUPPORTED_STEPPING          PCH_A0

//
// ICL PCH-LP Device IDs
//
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_0           0x3480        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_1           0x3481        ///< PCH LP Mobile U Super SKU (SSKU)
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_2           0x3482        ///< PCH LP Mobile U Premium
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_3           0x3483        ///< PCH LP Mobile U Base/Mainstream
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_4           0x3484        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_5           0x3485        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_6           0x3486        ///< PCH LP Mobile Y Super SKU (SSKU)
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_7           0x3487        ///< PCH LP Mobile Y Premium
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_8           0x3488        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_9           0x3489        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_10          0x348A        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_11          0x348B        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_12          0x348C        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_13          0x348D        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_14          0x348E        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_15          0x348F        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_16          0x3490        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_17          0x3491        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_18          0x3492        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_19          0x3493        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_20          0x3494        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_21          0x3495        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_22          0x3496        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_23          0x3497        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_24          0x3498        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_25          0x3499        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_26          0x349A        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_27          0x349B        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_28          0x349C        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_29          0x349D        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_30          0x349E        ///< PCH LP Mobile SKU
#define V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_31          0x349F        ///< PCH LP Mobile SKU

//
// ICL PCH-N Device IDs
//
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_0            0x3880        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_1            0x3881        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_2            0x3882        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_3            0x3883        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_4            0x3884        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_5            0x3885        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_6            0x3886        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_7            0x3887        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_8            0x3888        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_9            0x3889        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_10           0x388A        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_11           0x388B        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_12           0x388C        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_13           0x388D        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_14           0x388E        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_15           0x388F        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_16           0x3890        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_17           0x3891        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_18           0x3892        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_19           0x3893        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_20           0x3894        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_21           0x3895        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_22           0x3896        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_23           0x3897        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_24           0x3898        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_25           0x3899        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_26           0x389A        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_27           0x389B        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_28           0x389C        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_29           0x389D        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_30           0x389E        ///< PCH Atom SKU
#define V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_31           0x389F        ///< PCH Atom SKU

//
// ICL PCH-H Device IDs
//
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_0            0x3D80        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_1            0x3D81        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_2            0x3D82        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_3            0x3D83        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_4            0x3D84        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_5            0x3D85        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_6            0x3D86        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_7            0x3D87        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_8            0x3D88        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_9            0x3D89        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_10           0x3D8A        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_11           0x3D8B        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_12           0x3D8C        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_13           0x3D8D        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_14           0x3D8E        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_15           0x3D8F        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_16           0x3D90        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_17           0x3D91        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_18           0x3D92        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_19           0x3D93        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_20           0x3D94        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_21           0x3D95        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_22           0x3D96        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_23           0x3D97        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_24           0x3D98        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_25           0x3D99        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_26           0x3D9A        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_27           0x3D9B        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_28           0x3D9C        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_29           0x3D9D        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_30           0x3D9E        ///< PCH Desktop SKU
#define V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_31           0x3D9F        ///< PCH Desktop SKU

#endif
