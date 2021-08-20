/** @file
  Register names for VTD block
  <b>Conventions</b>:
  - Prefixes:
    - Definitions beginning with "R_" are registers
    - Definitions beginning with "B_" are bits within registers
    - Definitions beginning with "V_" are meaningful values of bits within the registers
    - Definitions beginning with "S_" are register sizes
    - Definitions beginning with "N_" are the bit position
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
#ifndef _VTD_REGS_H_
#define _VTD_REGS_H_

#define VTD_ENGINE_NUMBER                       7
#define R_MCHBAR_VTDTRKLCK                      0x73FC
#define R_VTD_ECAP_OFFSET                       0x10
#define B_VTD_ECAP_REG_IR                       BIT3

///
/// Vt-d Engine base address.
///
#define R_MCHBAR_VTD1_OFFSET                 0x5400  ///< HW UNIT1 for IGD
#define R_MCHBAR_VTD2_LOW_OFFSET             0x7880  ///< HW UNIT2 for IPU
#define R_MCHBAR_VTD2_HIGH_OFFSET            0x7884  ///< HW UNIT2 for IPU
#define R_MCHBAR_ITBT_PCIE_0_VTD_LOW_OFFSET  0x7888  ///< HW UNIT4 for iTBT PCIE0
#define R_MCHBAR_ITBT_PCIE_0_VTD_HIGH_OFFSET 0x788C  ///< HW UNIT4 for iTBT PCIE0
#define R_MCHBAR_ITBT_PCIE_1_VTD_LOW_OFFSET  0x7890  ///< HW UNIT5 for iTBT PCIE1
#define R_MCHBAR_ITBT_PCIE_1_VTD_HIGH_OFFSET 0x7894  ///< HW UNIT5 for iTBT PCIE1
#define R_MCHBAR_ITBT_PCIE_2_VTD_LOW_OFFSET  0x7898  ///< HW UNIT6 for iTBT PCIE2
#define R_MCHBAR_ITBT_PCIE_2_VTD_HIGH_OFFSET 0x789C  ///< HW UNIT6 for iTBT PCIE2
#define R_MCHBAR_ITBT_PCIE_3_VTD_LOW_OFFSET  0x78A0  ///< HW UNIT7 for iTBT PCIE3
#define R_MCHBAR_ITBT_PCIE_3_VTD_HIGH_OFFSET 0x78A4  ///< HW UNIT7 for iTBT PCIE3
#define R_MCHBAR_ITBT_PCIE_4_VTD_LOW_OFFSET  0x78A8  ///< HW UNIT8 for iTBT PCIE4
#define R_MCHBAR_ITBT_PCIE_4_VTD_HIGH_OFFSET 0x78AC  ///< HW UNIT8 for iTBT PCIE4
#define R_MCHBAR_ITBT_PCIE_5_VTD_LOW_OFFSET  0x78B0  ///< HW UNIT9 for iTBT PCIE5
#define R_MCHBAR_ITBT_PCIE_5_VTD_HIGH_OFFSET 0x78B4  ///< HW UNIT9 for iTBT PCIE5
#define R_MCHBAR_VTD3_OFFSET                 0x5410  ///< HW UNIT3 for all other - PEG, USB, SATA etc

///
/// Protected memory registers w.r.t. VTD3 bar
///
#define R_VTD_PMEN_OFFSET                    0x64
#define R_VTD_PLMBASE_OFFSET                 0x68
#define R_VTD_PLMLIMIT_OFFSET                0x6C
#define R_VTD_PHMBASE_OFFSET                 0x70
#define R_VTD_PHM_LIMIT_OFFSET               0x78

#endif
