/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

.text
ASM_FUNCTION_REMOVE_IF_UNREFERENCED

.macro GETSEC
.byte 0x0F, 0x37
.endm

.set IA32_CPUID_SMX_B,  6
.set CAPABILITIES,      0

.set CR4_SMXE,          (1 << 14)


ASM_GLOBAL ASM_PFX(CheckSmxCapabilities)

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  CheckSmxCapabilities
//
//  Input:  None
//
//  Output: None
//
//  Registers:  None are preserved
//
//  Description:  Execute GETSEC[CAPABILITIES] to report the SMX capabilities
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ASM_PFX(CheckSmxCapabilities):

    //
    // Check whether SMX is supported, bail if not
    //
    push    %ebx
    mov     $1, %eax
    cpuid
    bt      $IA32_CPUID_SMX_B, %ecx
    jb      L_CarryFlagSet
    mov     $0, %eax
    jmp     1f

L_CarryFlagSet:

    //
    // Save CR4
    //
    mov     %cr4, %edx

    //
    // Enable SMXE
    //
    mov     %cr4, %eax
    or      $CR4_SMXE, %eax
    mov     %eax, %cr4

    //
    // Call GETSEC[CAPABILITIES]
    //
    mov     $CAPABILITIES, %eax
    mov     $0, %ebx
    GETSEC

    //
    // Restore CR4
    //
    mov     %edx, %cr4

1:
    pop     %ebx
    ret