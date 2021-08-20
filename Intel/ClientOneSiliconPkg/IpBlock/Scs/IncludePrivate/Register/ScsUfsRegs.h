/** @file
  Register definitions for UFS controllers on SCS.

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

#ifndef _SCS_UFS_REGS_H_
#define _SCS_UFS_REGS_H_
//
// UFS Mmio Registers
//
#define R_SCS_MEM_UFS_EN                                             0x34
#define B_SCS_MEM_UFS_EN                                             BIT0
#define R_SCS_MEM_UFS_UIC_CMD                                        0x90
#define V_SCS_MEM_UFS_UIC_CMD_DME_SET                                0x2
#define R_SCS_MEM_UFS_UCMD_ARG1                                      0x94
#define R_SCS_MEM_UFS_UCMD_ARG2                                      0x98
#define R_SCS_MEM_UFS_UCMD_ARG3                                      0x9C
#define R_SCS_MEM_UFS_IS                                             0x20
#define B_SCS_MEM_UFS_IS_UCCS                                        BIT10
#define R_SCS_MEM_UFS_HC_STATUS                                      0x30
#define B_SCS_MEM_UFS_HCS_UCRDY                                      BIT3
#define R_SCS_MEM_UFS_AUTO_LTR_VALUE                                 0x808
#define R_SCS_MEM_UFS_REF_CLK                                        0x85C
#define V_SCS_MEM_UFS_REF_CLK                                        0x3

//
// MMP_UFS registers
//
#define R_SCS_PCR_MMPUFS_DLANE0                          0x0
#define R_SCS_PCR_MMPUFS_DLANE1                          0x2000

#define R_SCS_PCR_MMPUFS_DLANEX_TX3_SYNC_LEN             0x28
#define R_SCS_PCR_MMPUFS_DLANEX_IMP8                     0x101C
#define R_SCS_PCR_MMPUFS_DLANEX_IMP8_PWRGT               0x101F
#define R_SCS_PCR_MMPUFS_DLANEX_IMP24_TX_TOB_EXTN        0x105E
#define R_SCS_PCR_MMPUFS_DLANEX_IMP25_MK0_DETECT_LSB     0x1062
#define R_SCS_PCR_MMPUFS_DLANEX_IMP25_MK0_DETECT_MSB     0x1063
#define R_SCS_PCR_MMPUFS_DLANEX_RX3_HS_G1_SYNC_LEN_CAP   0x8B
#define R_SCS_PCR_MMPUFS_DLANEX_RX6_HS_G2_SYNC_LEN_CAP   0x94
#define R_SCS_PCR_MMPUFS_DLANEX_RX6_HS_G3_SYNC_LEN_CAP   0x95
#define R_SCS_PCR_MMPUFS_DLANEX_IMP23_INTFILTER          0x105B
#define R_SCS_PCR_MMPUFS_DLANEX_IMP21_RX_SQUELCH_ENABLE  0x1050
#define R_SCS_PCR_MMPUFS_DLANEX_TX4_LCC_ENABLE           0x102C
#define R_SCS_PCR_MMPUFS_DLANEX_IMP22                    0x1054
#define B_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD            (BIT26 | BIT25 | BIT24)
#define N_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD            24
#define V_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD            0x7

#endif
