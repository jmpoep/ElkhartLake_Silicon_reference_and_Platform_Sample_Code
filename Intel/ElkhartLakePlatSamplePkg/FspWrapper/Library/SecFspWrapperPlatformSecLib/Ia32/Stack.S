//// @file
// Switch the stack from temporary memory to permenent memory.
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

//------------------------------------------------------------------------------
// VOID
// EFIAPI
// SecSwitchStack (
//   UINT32   TemporaryMemoryBase,
//   UINT32   PermanentMemoryBase
//   )
//------------------------------------------------------------------------------
ASM_GLOBAL ASM_PFX (SecSwitchStack)
ASM_PFX(SecSwitchStack):
    //
    // Save standard registers so they can be used to change stack
    //
    pushl %eax
    pushl %ebx
    pushl %ecx
    pushl %edx

    //
    // !!CAUTION!! this function address's is pushed into stack after
    // migration of whole temporary memory, so need save it to permanent
    // memory at first!
    //
    movl  20(%esp), %ebx         // Save the first parameter
    movl  24(%esp), %ecx         // Save the second parameter

    //
    // Save this function's return address into permanent memory at first.
    // Then, Fixup the esp point to permanent memory
    //
    movl  %esp, %eax
    subl  %ebx, %eax
    addl  %ecx, %eax
    movl  0(%esp), %edx          // copy pushed register's value to permanent memory
    movl  %edx, 0(%eax)
    movl  4(%esp), %edx
    movl  %edx, 4(%eax)
    movl  8(%esp), %edx
    movl  %edx, 8(%eax)
    movl  12(%esp), %edx
    movl  %edx, 12(%eax)
    movl  16(%esp), %edx        // Update this function's return address into permanent memory
    movl  %edx, 16(%eax)
    movl  %eax, %esp            // From now, esp is pointed to permanent memory

    //
    // Fixup the ebp point to permanent memory
    //
    movl  %ebp, %eax
    subl  %ebx, %eax
    addl  %ecx, %eax
    movl  %eax, %ebp            // From now, ebp is pointed to permanent memory

    popl  %edx
    popl  %ecx
    popl  %ebx
    popl  %eax
    ret

