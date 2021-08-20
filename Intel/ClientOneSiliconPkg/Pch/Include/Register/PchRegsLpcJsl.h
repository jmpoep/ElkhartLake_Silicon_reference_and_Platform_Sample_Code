/** @file
  Register names for JSL PCH LPC/eSPI device

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
  Copyright 2019 Intel Corporation.

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
#ifndef _PCH_REGS_LPC_JSL_H_
#define _PCH_REGS_LPC_JSL_H_

#define V_LPC_CFG_DID_JSL_N                       0x4D80
#define JSL_PCH_N_MIN_SUPPORTED_STEPPING          PCH_A0

//
// JSL PCH-N Device IDs
//
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_0            0x4D80        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_1            0x4D81        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_2            0x4D82        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_3            0x4D83        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_4            0x4D84        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_5            0x4D85        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_6            0x4D86        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_7            0x4D87        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_8            0x4D88        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_9            0x4D89        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_10           0x4D8A        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_11           0x4D8B        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_12           0x4D8C        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_13           0x4D8D        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_14           0x4D8E        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_15           0x4D8F        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_16           0x4D90        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_17           0x4D91        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_18           0x4D92        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_19           0x4D93        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_20           0x4D94        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_21           0x4D95        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_22           0x4D96        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_23           0x4D97        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_24           0x4D98        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_25           0x4D99        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_26           0x4D9A        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_27           0x4D9B        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_28           0x4D9C        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_29           0x4D9D        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_30           0x4D9E        ///< PCH Atom SKU
#define V_JSL_PCH_N_LPC_CFG_DEVICE_ID_MB_31           0x4D9F        ///< PCH Atom SKU

#endif
