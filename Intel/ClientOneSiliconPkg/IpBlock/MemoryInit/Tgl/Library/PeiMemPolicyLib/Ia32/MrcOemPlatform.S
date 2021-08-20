//// @file
//
// @copyright
//  INTEL CONFIDENTIAL
//  Copyright 2015 - 2017 Intel Corporation.
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

//-----------------------------------------------------------------------------
//
//  Section:     SaMmioRead64
//
//  Description: Read 64 bits from the Memory Mapped I/O space.
//  Use MMX instruction for atomic access, because some MC registers have side effect.
//
//  @param[in] Address - Memory mapped I/O address.
//
//-----------------------------------------------------------------------------
//UINT64
//SaMmioRead64 (
//  IN  UINTN Address
//  )

ASM_GLOBAL ASM_PFX(SaMmioRead64)
ASM_PFX(SaMmioRead64):
   subl    $16, %esp
   movq    %mm0, (%esp)       //Save mm0 on stack
   movl    20(%esp), %edx     //edx = Address
   movq    (%edx), %mm0       //mm0 = [Address]
   movq    %mm0, 8(%esp)      //Store mm0 on Stack
   movq    (%esp), %mm0       //Restore mm0
   emms
   movl    8(%esp), %eax      //eax = [Address][31:0]
   movl    12(%esp), %edx     //edx = [Address][64:32]
   addl    $16, %esp
   ret

//-----------------------------------------------------------------------------
//
//  Section:     SaMmioWrite64
//
//  Description: Write 64 bits to the Memory Mapped I/O space.
//  Use MMX instruction for atomic access, because some MC registers have side effect.
//
//  @param[in] Address - Memory mapped I/O address.
//  @param[in] Value   - The value to write.
//
//-----------------------------------------------------------------------------

//UINT64
//SaMmioWrite64 (
//  IN UINTN Address,
//  IN UINT64 Value
//  )

ASM_GLOBAL ASM_PFX(SaMmioWrite64)
ASM_PFX(SaMmioWrite64):
   subl    $8, %esp
   movq    %mm0, (%esp)       //Save mm0 on Stack
   movl    12(%esp), %edx     //edx = Address
   movq    16(%esp), %mm0     //mm0 = Value
   movq    %mm0, (%edx)       //[Address] = Value
   movq    (%esp), %mm0       //Restore mm0
   emms
   movl     16(%esp), %eax    //eax = Value[31:0]
   movl     20(%esp), %edx    //edx = Value[64:32]
   addl     $8, %esp
   ret

//-----------------------------------------------------------------------------
//  Intel Silicon View Technology check point interface based on IO port reading
//
//  @param CheckPoint        Check point AH value.
//                           AH = 0x10:  End of MRC State
//                           AH = 0x20:  End of DXE State
//                           AH = 0x30:  Ready to boot before INT-19h or UEFI boot
//                           AH = 0x40:  After OS booting, need a timer SMI trigger to implement (TBD);
//
//  @param PortReading       IO port reading address used for breakpoints
//-----------------------------------------------------------------------------

//VOID
//EFIAPI
//IsvtCheckPoint (
//  IN UINT32          CheckPoint,
//  IN UINT32          PortReading
//  )

ASM_GLOBAL ASM_PFX(IsvtCheckPoint)
ASM_PFX(IsvtCheckPoint):
   pushl    %eax
   pushl    %edx

   // Stack layout at this point:
   //-------------
   // PortReading     ESP + 16
   //-------------
   // CheckPoint      ESP + 12
   //-------------
   // EIP             ESP + 8
   //-------------
   // EAX             ESP + 4
   //-------------
   // EDX         <-- ESP
   //-------------

   mov      12(%esp), %ah    // CheckPoint
   mov      16(%esp), %dx    // PortReading
   in       %dx, %al         // signal debugger

   popl     %edx
   popl     %eax
   ret

