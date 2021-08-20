
/** @file
  FscpMsrcommon.h


  <b>Conventions</b>
  - Definitions beginning with "MSR_" are MSRs
  - Definitions beginning with "R_" are registers
  - Definitions beginning with "B_" are bits within registers
  - Definitions beginning with "V_" are meaningful values of bits within the registers
  - Definitions beginning with "S_" are register sizes
  - Definitions beginning with "N_" are the bit position

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

#ifndef _FSCP_MSRCOMMON_h
#define _FSCP_MSRCOMMON_h
#define MSR_SMM_SAVE_CONTROL 0x0000003E

/*
*/
#define N_MSR_SMM_SAVE_CONTROL_SAVE_FP_STATE_OFFSET 0
#define S_MSR_SMM_SAVE_CONTROL_SAVE_FP_STATE_WIDTH 1
#define B_MSR_SMM_SAVE_CONTROL_SAVE_FP_STATE_MASK BIT0

/*
*/
#define N_MSR_SMM_SAVE_CONTROL_RESERVED_OFFSET 1
#define S_MSR_SMM_SAVE_CONTROL_RESERVED_WIDTH 31
#define B_MSR_SMM_SAVE_CONTROL_RESERVED_MASK (0xFFFFFFFE)

/*
*/
#define MSR_NPK_STH_ACPIBAR_BASE 0x00000080

#define N_MSR_NPK_STH_ACPIBAR_BASE_LOCK_OFFSET 0
#define S_MSR_NPK_STH_ACPIBAR_BASE_LOCK_WIDTH 1
#define B_MSR_NPK_STH_ACPIBAR_BASE_LOCK_MASK BIT0

/*
*/
#define N_MSR_NPK_STH_ACPIBAR_BASE_RSVD_OFFSET 1
#define S_MSR_NPK_STH_ACPIBAR_BASE_RSVD_WIDTH 17
#define B_MSR_NPK_STH_ACPIBAR_BASE_RSVD_MASK (0x000000000003FFFE)

/*
*/
#define N_MSR_NPK_STH_ACPIBAR_BASE_ADDRESS_OFFSET 18
#define S_MSR_NPK_STH_ACPIBAR_BASE_ADDRESS_WIDTH 46
#define B_MSR_NPK_STH_ACPIBAR_BASE_ADDRESS_MASK (0xFFFFFFFFFFFC0000ULL)

/*
*/
#define MSR_SMM_PROT_MODE_BASE 0x0000009D

/*
*/
#define N_MSR_SMM_PROT_MODE_BASE_ENABLE_OFFSET 0
#define S_MSR_SMM_PROT_MODE_BASE_ENABLE_WIDTH 1
#define B_MSR_SMM_PROT_MODE_BASE_ENABLE_MASK BIT0

/*
*/
#define N_MSR_SMM_PROT_MODE_BASE_RSVD1_OFFSET 1
#define S_MSR_SMM_PROT_MODE_BASE_RSVD1_WIDTH 11
#define B_MSR_SMM_PROT_MODE_BASE_RSVD1_MASK (0x00000FFE)

/*
*/
#define N_MSR_SMM_PROT_MODE_BASE_PHYSICAL_ADDR_OFFSET 12
#define S_MSR_SMM_PROT_MODE_BASE_PHYSICAL_ADDR_WIDTH 20
#define B_MSR_SMM_PROT_MODE_BASE_PHYSICAL_ADDR_MASK (0xFFFFF000)

/*
*/
#define MSR_PMG_IO_CAPTURE_BASE 0x000000E4

/*
*/
#define N_MSR_PMG_IO_CAPTURE_BASE_LVL2B_OFFSET 0
#define S_MSR_PMG_IO_CAPTURE_BASE_LVL2B_WIDTH 16
#define B_MSR_PMG_IO_CAPTURE_BASE_LVL2B_MASK (0x0000FFFF)

/*
*/
#define N_MSR_PMG_IO_CAPTURE_BASE_CST_RANGE_OFFSET 16
#define S_MSR_PMG_IO_CAPTURE_BASE_CST_RANGE_WIDTH 3
#define B_MSR_PMG_IO_CAPTURE_BASE_CST_RANGE_MASK (0x00070000)

/*
*/
#define N_MSR_PMG_IO_CAPTURE_BASE_RSVD_OFFSET 19
#define S_MSR_PMG_IO_CAPTURE_BASE_RSVD_WIDTH 13
#define B_MSR_PMG_IO_CAPTURE_BASE_RSVD_MASK (0xFFF80000)

#define MSR_FEATURE_CONFIG 0x0000013C

/*
*/
#define N_MSR_FEATURE_CONFIG_LOCK_OFFSET 0
#define S_MSR_FEATURE_CONFIG_LOCK_WIDTH 1
#define B_MSR_FEATURE_CONFIG_LOCK_MASK BIT0

/*
*/
#define N_MSR_FEATURE_CONFIG_AES_DISABLE_OFFSET 1
#define S_MSR_FEATURE_CONFIG_AES_DISABLE_WIDTH 1
#define B_MSR_FEATURE_CONFIG_AES_DISABLE_MASK BIT1

/*
*/
#define N_MSR_FEATURE_CONFIG_RESERVED_OFFSET 2
#define S_MSR_FEATURE_CONFIG_RESERVED_WIDTH 30
#define B_MSR_FEATURE_CONFIG_RESERVED_MASK (0xFFFFFFFC)

#define MSR_FAST_UNCORE_MSRS_CTL 0x00000657

/*
*/
#define N_MSR_FAST_UNCORE_MSRS_CTL_FAST_ACCESS_ENABLE_OFFSET 0
#define S_MSR_FAST_UNCORE_MSRS_CTL_FAST_ACCESS_ENABLE_WIDTH 4
#define B_MSR_FAST_UNCORE_MSRS_CTL_FAST_ACCESS_ENABLE_MASK (0x0000000F)

/*
*/
#define N_MSR_FAST_UNCORE_MSRS_CTL_RSVD_OFFSET 4
#define S_MSR_FAST_UNCORE_MSRS_CTL_RSVD_WIDTH 28
#define B_MSR_FAST_UNCORE_MSRS_CTL_RSVD_MASK (0xFFFFFFF0)

#define MSR_IO_MEM_ADDR_PPPE 0x0000093E

/*
*/
#define N_MSR_IO_MEM_ADDR_ALL_OFFSET 0
#define S_MSR_IO_MEM_ADDR_ALL_WIDTH 64
#define B_MSR_IO_MEM_ADDR_ALL_MASK (0xFFFFFFFFFFFFFFFFULL)

#endif
