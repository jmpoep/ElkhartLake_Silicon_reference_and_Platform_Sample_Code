/** @file
  Interface definition details for North Bridge Setup Routines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __SA_SETUP_H__  // To Avoid this header get compiled twice
#define __SA_SETUP_H__

#define MAX_TOLUD_DYNAMIC  0
#define MAX_TOLUD_1G       1
#define MAX_TOLUD_1_25G    2
#define MAX_TOLUD_1_5G     3
#define MAX_TOLUD_1_75G    4
#define MAX_TOLUD_2G       5
#define MAX_TOLUD_2_25G    6
#define MAX_TOLUD_2_5G     7
#define MAX_TOLUD_2_75G    8
#define MAX_TOLUD_3G       9
#define MAX_TOLUD_3_25G    10
#define MAX_TOLUD_3_5G     11

#define MEM_4GB   (0x1000)  ///< Define the 4GB size in 1MB units (1024MB = 1GB).
#define MEM_8GB   (0x2000)
#define MEM_12GB  (0x3000)
#define MEM_16GB  (0x4000)
//
// SPD Profile
//
#define DEFAULT_SPD_PROFILE 0
#define CUSTOM_PROFILE      1
#define XMP_PROFILE_1       2
#define XMP_PROFILE_2       3

//
// VMD Setup options
//
#define VMD_CFG_BAR_SIZE_DEFAULT           25
#define VMD_MEM_BAR_SIZE1_DEFAULT          25
#define VMD_MEM_BAR_SIZE2_DEFAULT          20

#define VMD_32BIT_NONPREFETCH              0
#define VMD_64BIT_NONPREFETCH              1
#define VMD_64BIT_PREFETCH                 2

//
// 2LM
//
#define BOOT_MODE_1LM              0
#define BOOT_MODE_2LM              1
#define BOOT_MODE_PROVISION        2
#define DEFAULT_PHASES             0
#define PROGRAM_128PHASES          1

#define CS_ICL_A0     0

#endif
