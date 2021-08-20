//// @file
//  Assembly code of Cpu
//
// @copyright
//  INTEL CONFIDENTIAL
//  Copyright 2006 - 2018 Intel Corporation.
//
//  The source code contained or described herein and all documents related to the
//  source code ("Material") are owned by Intel Corporation or its suppliers or
//  licensors. Title to the Material remains with Intel Corporation or its suppliers
//  and licensors. The Material may contain trade secrets and proprietary and
//  confidential information of Intel Corporation and its suppliers and licensors,
//  and is protected by worldwide copyright and trade secret laws and treaty
//  provisions. No part of the Material may be used, copied, reproduced, modified,
//  published, uploaded, posted, transmitted, distributed, or disclosed in any way
//  without Intel's prior express written permission.
//
//  No license under any patent, copyright, trade secret or other intellectual
//  property right is granted to or conferred upon you by disclosure or delivery
//  of the Materials, either expressly, by implication, inducement, estoppel or
//  otherwise. Any license under such intellectual property rights must be
//  express and approved by Intel in writing.
//
//  Unless otherwise agreed by Intel in writing, you may not remove or alter
//  this notice or any other notice embedded in Materials by Intel or
//  Intel's suppliers or licensors in any way.
//
//  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
//  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
//  the terms of your license agreement with Intel or your vendor. This file may
//  be modified by the user, subject to additional terms of the license agreement.
//
// @par Specification
////

.equ IA32_CR4_OSFXSR,              0x200
.equ IA32_CR4_OSXMMEXCPT,          0x400
.equ IA32_CR0_MP,                  0x02

.equ IA32_CPUID_SSE2,              0x2000000
.equ IA32_CPUID_SSE2_B,            0x1A      //26


//------------------------------------------------------------------------------
//   Set up flags in CR4 for XMM instruction enabling
//------------------------------------------------------------------------------
ASM_GLOBAL ASM_PFX(InitXmm)
ASM_PFX(InitXmm):
  push    %ebx

  //
  // Check whether SSE2 is supported
  //
  mov     $0x01, %eax
  cpuid
  bt      $IA32_CPUID_SSE2_B, %edx
  jnc     InitXmmL0

  //
  // Enable XMM
  //
  movl    %cr0, %eax
  or      $IA32_CR0_MP, %eax
  movl    %eax, %cr0
  movl    %cr4, %eax
  or      $IA32_CR4_OSFXSR, %eax
  or      $IA32_CR4_OSXMMEXCPT, %eax
  movl    %eax, %cr4

InitXmmL0:
  pop     %ebx
  ret

ASM_GLOBAL ASM_PFX(CacheInvd)
ASM_PFX(CacheInvd):
  invd
  ret


