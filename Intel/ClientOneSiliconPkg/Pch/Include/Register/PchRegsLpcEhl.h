/** @file
  Register names for EHL PCH LPC/eSPI device

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
#ifndef _PCH_REGS_LPC_EHL_H_
#define _PCH_REGS_LPC_EHL_H_

#define V_LPC_CFG_DID_EHL                         0x4B00

#define EHL_PCH_MIN_SUPPORTED_STEPPING            PCH_A0

//
// EHL PCH Device IDs
//
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_0           0x4B00        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_1           0x4B01        ///< PCH Mobile Super SKU (SSKU)
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_2           0x4B02        ///< PCH Mobile Premium
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_3           0x4B03        ///< PCH Mobile Base/Mainstream
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_4           0x4B04        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_5           0x4B05        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_6           0x4B06        ///< PCH Mobile Super SKU (SSKU)
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_7           0x4B07        ///< PCH Mobile Premium
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_8           0x4B08        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_9           0x4B09        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_10          0x4B0A        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_11          0x4B0B        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_12          0x4B0C        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_13          0x4B0D        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_14          0x4B0E        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_15          0x4B0F        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_16          0x4B10        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_17          0x4B11        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_18          0x4B12        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_19          0x4B13        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_20          0x4B14        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_21          0x4B15        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_22          0x4B16        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_23          0x4B17        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_24          0x4B18        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_25          0x4B19        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_26          0x4B1A        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_27          0x4B1B        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_28          0x4B1C        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_29          0x4B1D        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_30          0x4B1E        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_31          0x4B1F        ///< PCH Mobile SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_8      0x4516        ///< PCH Indu SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_9      0x452C        ///< PCH Indu SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_10     0x452E        ///< PCH Indu SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_11     0x4532        ///< PCH Indu SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_12     0x4518        ///< PCH Indu SKU
#define V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_13     0x451A        ///< PCH Indu SKU

#endif
