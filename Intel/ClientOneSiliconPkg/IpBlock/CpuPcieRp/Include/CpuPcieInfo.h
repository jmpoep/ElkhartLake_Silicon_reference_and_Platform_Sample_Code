/** @file
  This file contains definitions of PCIe controller information

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
#ifndef _CPU_PCIE_INFO_H_
#define _CPU_PCIE_INFO_H_

#define PCIE_HWEQ_COEFFS_MAX    5

/**
PCIe controller configuration.
**/

#define CPU_PCIE_1x16       7
#define CPU_PCIE_1x8_2x4    6
#define CPU_PCIE_2x8        5
#define CPU_PCIE_1x4        0

//
// Device 1 Memory Mapped IO Register Offset Equates
//
#define SA_PEG_BUS_NUM     0x00
#define SA_PEG_DEV_NUM     0x01
#define SA_PEG0_DEV_NUM    SA_PEG_DEV_NUM
#define SA_PEG0_FUN_NUM    0x00
#define SA_PEG1_DEV_NUM    SA_PEG_DEV_NUM
#define SA_PEG1_FUN_NUM    0x01
#define SA_PEG2_DEV_NUM    SA_PEG_DEV_NUM
#define SA_PEG2_FUN_NUM    0x02
#define SA_PEG3_DEV_NUM    0x06
#define SA_PEG3_FUN_NUM    0x00

#define V_SA_PEG_VID       0x8086

#define V_PH3_FS_CR_OVR       0x3E
#define B_PH3_FS_CR_OVR_EN    BIT8
#define V_PH3_LF_CR_OVR       0x14
#define B_PH3_LF_CR_OVR_EN    BIT16

//
// Temporary Device & Function Number used for Switchable Graphics DGPU
//
#define SA_TEMP_DGPU_DEV   0x00
#define SA_TEMP_DGPU_FUN   0x00

//
// SA PCI Express* Port configuration
//

#define CPU_PCIE_MAX_ROOT_PORTS            4
#define CPU_PCIE_MAX_CONTROLLERS           3

#define SA_PEG_MAX_FUN     0x04
#define SA_PEG_MAX_LANE    0x14
#define SA_PEG_MAX_BUNDLE  0x0A

#define SA_PEG0_CNT_MAX_LANE     0x10
#define SA_PEG0_CNT_MAX_BUNDLE   0x08
#define SA_PEG0_CNT_FIRST_LANE   0x00
#define SA_PEG0_CNT_FIRST_BUNDLE 0x00
#define SA_PEG0_CNT_LAST_LANE    0x0F
#define SA_PEG0_CNT_LAST_BUNDLE  0x07

#define SA_PEG3_CNT_MAX_LANE     0x04
#define SA_PEG3_CNT_MAX_BUNDLE   0x02
#define SA_PEG3_CNT_FIRST_LANE   0x00
#define SA_PEG3_CNT_FIRST_BUNDLE 0x00
#define SA_PEG3_CNT_LAST_LANE    0x03
#define SA_PEG3_CNT_LAST_BUNDLE  0x01
//
// Silicon and SKU- specific MAX defines
//
#define SA_PEG_CNL_H_MAX_FUN           SA_PEG_MAX_FUN      // CNL-H- SKU supports 4 controllers with 20 PEG lanes and 10 bundles
#define SA_PEG_CNL_H_MAX_LANE          SA_PEG_MAX_LANE
#define SA_PEG_CNL_H_MAX_BUNDLE        SA_PEG_MAX_BUNDLE
#define SA_PEG_NON_CNL_H_MAX_FUN       0x03                // All non-CNL-H- SKU supports 3 controllers with 16 PEG lanes and 8 bundles
#define SA_PEG_NON_CNL_H_MAX_LANE      0x10
#define SA_PEG_NON_CNL_H_MAX_BUNDLE    0x08

#define DMI_AUTO              0
#define DMI_GEN1              1
#define DMI_GEN2              2
#define DMI_GEN3              3

#define PH3_METHOD_AUTO       0x0
#define PH3_METHOD_HWEQ       0x1
#define PH3_METHOD_SWEQ       0x2
#define PH3_METHOD_STATIC     0x3
#define PH3_METHOD_DISABLED   0x4

#define MAX_PRESETS           9
#define BEST_PRESETS          4

//
// The PEG Disable Mask BIT0 ~ BIT3 for PEG0 ~ PEG3
//
#define V_PEG_DISABLE_MASK    0x0F
#define B_PEG0_DISABLE_MASK   BIT0
#define B_PEG1_DISABLE_MASK   BIT1
#define B_PEG2_DISABLE_MASK   BIT2
#define B_PEG3_DISABLE_MASK   BIT3

#define CPU_PCIE_CTRL_060       0
#define CPU_PCIE_CTRL_010       1
#define CPU_PCIE_CTRL_011_012   2

#endif
