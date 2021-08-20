/** @file
  Header file for VMD IP specific Registers.

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
#ifndef _VMD_REGS_H_
#define _VMD_REGS_H_

/**
* VMD device will be assigned with (Segment/Bus/Device/Function) equals to (0/0/14/0)
**/

#define SA_VMD_DEV_NUM            0xE // Device   #14
#define SA_VMD_FUNC_NUM           0x0 // Function #0
#define VMD_DID_LSB               0x0B

//
// VMD Setup options
//
#define VMD_CFG_BAR_SIZE_DEFAULT           25
#define VMD_MEM_BAR_SIZE1_DEFAULT          25
#define VMD_MEM_BAR_SIZE2_DEFAULT          20

#define VMD_32BIT_NONPREFETCH              0
#define VMD_64BIT_NONPREFETCH              1
#define VMD_64BIT_PREFETCH                 2


/* All Configuration space registers of VMD should be added with
 * suffix _0_14_0_PCI to follow clients naming convention.
 */
#define R_CFGBAR_N0_0_14_0_PCI_VMD_REG_OFFSET     0x10
#define R_CFGBAR_N1_0_14_0_PCI_VMD_REG_OFFSET     0x14
#define R_MEMBAR1_N0_0_14_0_PCI_VMD_REG_OFFSET    0x18
#define R_MEMBAR1_N1_0_14_0_PCI_VMD_REG_OFFSET    0x1C
#define R_MEMBAR2_N0_0_14_0_PCI_VMD_REG_OFFSET    0x20
#define R_MEMBAR2_N1_0_14_0_PCI_VMD_REG_OFFSET    0x24
#define R_VMCAP_0_14_0_PCI_VMD_REG_OFFSET         0x40
#define R_VMCONFIG_0_14_0_PCI_VMD_REG_OFFSET      0x44
#define R_VMASSIGN_0_14_0_PCI_VMD_REG_OFFSET      0x48
#define R_CFGBARSZ_0_14_0_PCI_VMD_REG_OFFSET      0x4C
#define R_MEMBAR1SZ_0_14_0_PCI_VMD_REG_OFFSET     0x4D
#define R_MEMBAR2SZ_0_14_0_PCI_VMD_REG_OFFSET     0x4E
#define R_ROOTBUS_0_14_0_PCI_VMD_REG_OFFSET       0x4F
#define R_FN0_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x50
#define R_FN1_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x54
#define R_FN2_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x58
#define R_FN3_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x5C
#define R_FN4_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x60
#define R_FN5_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x64
#define R_FN6_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x68
#define R_FN7_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET    0x6C

#endif /* _VMD_REGS_H_ */
