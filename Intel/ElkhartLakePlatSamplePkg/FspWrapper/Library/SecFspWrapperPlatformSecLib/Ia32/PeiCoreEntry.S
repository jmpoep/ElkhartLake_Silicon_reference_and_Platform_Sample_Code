//// @file
// Find and call SecStartup
//
//@copyright
//  INTEL CONFIDENTIAL
//  Copyright 2014 - 2017 Intel Corporation.
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
//  This file contains a 'Sample Driver' and is licensed as such under the terms
//  of your license agreement with Intel or your vendor. This file may be modified
//  by the user, subject to the additional terms of the license agreement.
//
//@par Specification Reference:
////

ASM_GLOBAL    ASM_PFX(SecStartup)
ASM_GLOBAL    ASM_PFX(PlatformInit)

ASM_GLOBAL ASM_PFX(CallPeiCoreEntryPoint)
ASM_PFX(CallPeiCoreEntryPoint):
  //
  // Obtain the hob list pointer
  //
  movl    0x04(%esp), %eax
  //
  // Obtain the stack information
  //   ECX: start of range
  //   EDX: end of range
  //
  movl    0x08(%esp), %ecx
  movl    0x0C(%esp), %edx

  //
  // Platform init
  //
  pushal
  pushl   %edx
  pushl   %ecx
  pushl   %eax
  call    ASM_PFX(PlatformInit)
  popl    %eax
  popl    %eax
  popl    %eax
  popal

  //
  // Set stack top pointer
  //
  movl    %edx, %esp

  //
  // Push the hob list pointer
  //
  pushl   %eax

  //
  // Save the value
  //   ECX: start of range
  //   EDX: end of range
  //
  movl    %esp, %ebp
  pushl   %ecx
  pushl   %edx

  //
  // Push processor count to stack first, then BIST status (AP then BSP)
  //
  movl    $0x01, %eax
  cpuid
  shr     $0x10, %ebx
  andl    $0x000000FF, %ebx
  cmp     $0x01, %bl
  jae     PushProcessorCount

  //
  // Some processors report 0 logical processors.  Effectively 0 = 1.
  // So we fix up the processor count
  //
  inc     %ebx

PushProcessorCount:
  pushl   %ebx

  //
  // We need to implement a long-term solution for BIST capture.  For now, we just copy BSP BIST
  // for all processor threads
  //
  xorl    %ecx, %ecx
  movb    %bl, %cl
PushBist:
  movd    %mm0, %eax
  pushl   %eax
  loop    PushBist

  //
  // Save Time-Stamp Counter
  //
  movd    %mm5, %eax
  pushl   %eax

  movd    %mm6, %eax
  pushl   %eax

  //
  // Pass entry point of the PEI core
  //
  movl    $0xFFFFFFE0, %edi
  pushl   %ds:(%edi)

  //
  // Pass BFV into the PEI Core
  //
  movl    $0xFFFFFFFC, %edi
  pushl   %ds:(%edi)

  //
  // Pass stack size into the PEI Core
  //
  movl    -0x04(%ebp), %ecx
  movl    -0x08(%ebp), %edx
  pushl   %ecx                           // RamBase

  subl    %ecx, %edx
  pushl   %edx                           // RamSize

  //
  // Pass Control into the PEI Core
  //
  call ASM_PFX(SecStartup)

