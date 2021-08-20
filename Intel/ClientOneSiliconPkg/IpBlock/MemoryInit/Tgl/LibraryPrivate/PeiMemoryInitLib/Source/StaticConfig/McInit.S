/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

 @par Specification
**/

#define TXT_PUBLIC_BASE    0xFED30000
#define TXT_PUBLIC_BASE_1   0xFED30200
#define TXT_PUBLIC_BASE_2   0xFED30010
".equ   TXT_PUBLIC_BASE, 0xFED30000\n\t"
".equ   TXT_PUBLIC_BASE_1, 0xFED30200\n\t"
".equ   TXT_PUBLIC_BASE_2, 0xFED30010\n\t"
".equ   B_CPUID_VERSION_INFO_ECX_SME, (1 << 6)\n\t"
".equ   TPM_STATUS_REG_ADDRESS, 0xFED40000\n\t"
"movl   $0x1, %%eax\n\t"
"movl   $0x1, %%ecx\n\t"
"cpuid\n\t"
"movl   %%ecx, %%eax\n\t"
"outl   %%eax, $0x80\n\t"
"test   $B_CPUID_VERSION_INFO_ECX_SME, %%ecx\n\t"               /* is TXT processor */
"je     noTxt\n\t"
"movl   TXT_PUBLIC_BASE_1, %%eax\n\t"
"movl   TXT_PUBLIC_BASE_2, %%eax\n\t"
"testl  $0x1, TXT_PUBLIC_BASE_2\n\t"                            /* TXT Chipset */
"je     noTxt\n\t"
"xorl   %%eax, %%eax\n\t"
"movb   TPM_STATUS_REG_ADDRESS, %%al\n\t"
"outl   %%eax, $0x80\n\t"
"shll   $0x8, %%eax\n\t"
"movb   TPM_STATUS_REG_ADDRESS, %%al\n\t"
"outl   %%eax, $0x80\n\t"
"shll   $0x8, %%eax\n\t"
"movb   TPM_STATUS_REG_ADDRESS, %%al\n\t"
"outl   %%eax, $0x80\n\t"
"shll   $0x8, %%eax\n\t"
"movb   TPM_STATUS_REG_ADDRESS, %%al\n\t"
"outl   %%eax, $0x80\n\t"
"movl   $0x2E6, %%ecx\n\t"
"xorl   %%eax, %%eax\n\t"
"xorl   %%edx, %%edx\n\t"
"wrmsr\n\t"
"movl    $0xFED4FED4, %%eax\n\t"
"noTxt:\n\t"
"movl   $0x80000006, 0xfed15E00\n\t"                  /* Freq for DDR4 is 1600 */
"ddr4_freq:\n\t"
  "testl  $0x80000000, 0xfed15E00\n\t"                /* Poll RUN_BUSY bit until it becomes zero */
  "jnz    ddr4_freq\n\t"
#include "Source/StaticConfig/Ddr4.S"

