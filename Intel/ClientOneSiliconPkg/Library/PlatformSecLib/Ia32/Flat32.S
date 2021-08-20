//// @file
//  This is the code that goes from real-mode to protected mode.
//  it consumes the reset vector.
//
// @copyright
//  INTEL CONFIDENTIAL
//  Copyright 1999 - 2017 Intel Corporation.
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
//
////

.INCLUDE "Platform.i"
.INCLUDE "Chipset.i"
.INCLUDE "SecCore.i"

#ifndef FSP_FLAG
ASM_GLOBAL ASM_PFX(SecStartup)
#endif

ASM_GLOBAL ASM_PFX(_TEXT_REALMODE)
ASM_PFX(_TEXT_REALMODE):

//------------------------------------------------------------------------------
//
//  SEC "Security" Code module.
//
//  Transition to non-paged flat-model protected mode from a
//  hard-coded GDT that provides exactly two descriptors.
//  This is a bare bones transition to protected mode only
//  used for while in PEI and possibly DXE.
//
//  IA32 specific cache as RAM modules
//
//  After enabling protected mode, a far jump is executed to
//  TransferToPEI using the newly loaded GDT.
//  This code also enables the Cache-as-RAM
//
//  RETURNS:    none
//
//  MMX Usage:
//              MM0 = BIST State
//              MM3 = Patch Revision
//              MM4 = Patch Pointer
//              MM5 = Save time-stamp counter value high32bit
//              MM6 = Save time-stamp counter value low32bit.
//              MM7 = Used in CALL_MMX & RET_ESI macro
//
//------------------------------------------------------------------------------
  //
  // Reset Boot Flow Start
  //
#ifndef FSP_FLAG
.align 4

ASM_GLOBAL ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
  //
  // Save BIST state in MM0
  //
  fninit                                     // clear any pending Floating point exceptions
  movd    %eax, %mm0

  //
  // Save time-stamp counter value
  // rdtsc load 64bit time-stamp counter to EDX:EAX
  //
  rdtsc
  movd    %edx ,%mm5
  movd    %eax, %mm6

  //
  // Check INIT# is asserted by port 0xCF9
  //
  mov     $0x0CF9, %dx
  in      %dx, %al
  cmp     $0x04, %al
  jnz     NotWarmStart

  //
  // @note Issue warm reset, since if CPU only reset is issued not all MSRs are restored to their defaults
  //
  movw    $0xCF9, %dx
  movb    $0x06, %al
  out     %al, %dx

NotWarmStart:
  //
  // Enter Protected mode.
  //
  STATUS_CODE(0x01)                          // BSP_PROTECTED_MODE_START
  movl    $GdtDesc, %esi
  .byte   0x66
  lgdt    %cs:(%si)
  movl    %cr0 , %eax                        // Get control register 0
  orl     $00000003, %eax                    // Set PE bit (bit #0) & MP bit (bit #1)
  movl    %eax, %cr0                         // Activate protected mode
  movl    %cr4, %eax                         // Get control register 4
  orl     $0x00000600, %eax                  // Set OSFXSR bit (bit #9) & OSXMMEXCPT bit (bit #10)
  movl    %eax, %cr4

  //
  // Now we're in Protected16
  // Set up the selectors for protected mode entry
  //
  mov     $SYS_DATA_SEL, %ax
  mov     %ax, %ds
  mov     %ax, %es
  mov     %ax, %fs
  mov     %ax, %gs
  mov     %ax, %ss

  //
  // Go to Protected32
  //
  movl    $NemInitLinearAddress, %esi
  jmp     *%cs:(%si)

TightLoop:
  cli
  hlt
  jmp     TightLoop
#endif

ASM_GLOBAL ASM_PFX(_TEXT_PROTECTED_MODE)
ASM_PFX(_TEXT_PROTECTED_MODE):

#ifdef FSP_FLAG
.macro LOAD_MMX_EXT   ReturnAddress, MmxRegister
  movl    $ReturnAddress, %esi
  movd    %esi, $MmxRegister                 // save ReturnAddress into MM7
.endm

.macro CALL_MMX_EXT  RoutineLabel, MmxRegister
  //.local   ReturnAddress
  movl    $ReturnAddress, %esi
  movd    %esi, $MmxRegister                 // save ReturnAddress into MM7
  jmp     RoutineLabel
  ReturnAddress:
.endm

.macro RET_ESI_EXT   MmxRegister
  movd    $MmxRegister, %esi                 // restore ESP from MM7
  jmp     *%esi
.endm

#endif// FSP_FLAG

.macro CALL_MMX   RoutineLabel

  movl    $ReturnAddress, %esi
  movd    %esi, %mm7                         // save ReturnAddress into MM7
  jmp     RoutineLabel
  ReturnAddress:
.endm

.macro RET_ESI
  movd    %mm7, %esi                         // restore ESP from MM7
  jmp     *%esi
.endm

.macro    CALL_EBP   RoutineLabel
  //local   ReturnAddress
  movl    $ReturnAddress, %ebp
  jmp     RoutineLabel

ReturnAddress:
.endm

.macro RET_EBP
  jmp     *%ebp                              // restore ESP from EBP
.endm


.align 4
.long PROTECTED_MODE_ENTRY_GUID1
.long PROTECTED_MODE_ENTRY_GUID2
.long PROTECTED_MODE_ENTRY_GUID3
.long PROTECTED_MODE_ENTRY_GUID4
ASM_GLOBAL ASM_PFX(ProtectedModeSecStart)
ASM_PFX(ProtectedModeSecStart):

#ifndef FSP_FLAG
  STATUS_CODE(0x02)
  movl    $ProtectedModeSecStartL0, %esi     // CALL_MMX  EarlyMicrocodeUpdate
  movd    %esi, %mm7
  jmp     EarlyMicrocodeUpdate
ProtectedModeSecStartL0:
  STATUS_CODE(0x03)
  movl    $ProtectedModeSecStartL1, %esi     // CALL_MMX  SecPlatformInit
  movd    %esi, %mm7
  jmp     SecPlatformInit
ProtectedModeSecStartL1:


  STATUS_CODE(0x04)
  movl    $ProtectedModeSecStartL2, %esi     // CALL_MMX  SecCarInit
  movd    %esi, %mm7
  jmp     SecCarInit
ProtectedModeSecStartL2:


  STATUS_CODE(0x05)
  movl    $ProtectedModeSecStartL3, %esi     // CALL_MMX  EstablishStack
  movd    %esi, %mm7
  jmp     EstablishStack
ProtectedModeSecStartL3:

  STATUS_CODE(0x06)
  jmp  CallPeiCoreEntryPoint

#endif //FSP_FLAG

//
// Perform early platform initialization
//
ASM_GLOBAL ASM_PFX(SecPlatformInit)
ASM_PFX(SecPlatformInit):

  movl    $SecPlatformInitL0, %ebp           // CALL_EBP  SecSaInit
  jmp     SecSaInit
SecPlatformInitL0:

  //
  // Enable HPET decode in PCH.
  //
#ifdef FSP_FLAG
  //
  // Read PCI Express base address
  //
  movl    $PCIEX_BAR_REG, %eax               // B0:D0:F0:R60
  mov     $0x0CF8, %dx
  out     %eax, %dx
  mov     $0x0CFC, %dx
  in      %dx, %eax
  and     $0xFC000000, %eax
  movl    %eax, %esi
#else
  movl    PcdGet64 (PcdPciExpressBaseAddress), %esi
#endif
  addl    $PCH_HPET_REG, %esi
  mov     $PCH_HPET_AE, %al
  mov     %al, (%esi)
  mov     (%esi), %al
  xorl    %eax, %eax
  movl    $HPET_COMP_1, %esi                 // read back
  movl    %eax, (%esi)
  movl    $HPET_COMP_2, %esi
  movl    %eax, (%esi)

  RET_ESI


  //
  // Establish Stack
  //
ASM_GLOBAL ASM_PFX(EstablishStack)
ASM_PFX(EstablishStack):
  //
  // Enable STACK
  //
  RET_ESI



  //
  // This is the entry point to PEI phase
  //
ASM_GLOBAL ASM_PFX(CallPeiCoreEntryPoint)
ASM_PFX(CallPeiCoreEntryPoint):
  //
  // Set stack top pointer
  //
  movl    PcdGet32 (PcdTemporaryRamBase), %esp
  addl    PcdGet32 (PcdTemporaryRamSize), %esp

  //
  // Push CPU count to stack first, then AP's (if there is one)
  // BIST status, and then BSP's
  //
  mov     $0x01, %ch                         // for client we have only one BSP
  movzx   %ch, %ecx

  //
  // Save number of BSPs
  //
  pushl   %ecx

GetSbspBist:
  //
  // Save SBSP BIST
  //
  movd    %mm0, %eax
  pushl   %eax

  //
  // Save SBSP APIC ID
  //
  movd    %mm1, %eax
  shrl    $0x18, %eax                        // Resume APIC ID
  pushl   %eax

  //
  // Save Time-Stamp Counter
  //
  movd    %mm5, %eax
  pushl   %eax

  movd    %mm6, %eax
  pushl   %eax

TransferToSecStartup:

  //
  // Switch to "C" code
  //
  STATUS_CODE(0x0C)

  //
  // Pass entry point of the PEI core
  //
  movl    $PEI_CORE_ENTRY_BASE, %edi         // 0FFFFFFE0h
  pushl   %ds:(%edi)

  //
  // Pass BFV into the PEI Core
  //
  movl    $FV_MAIN_BASE, %edi                // 0FFFFFFFCh
  pushl   %ds:(%edi)

  //
  // @todo ECPoverride: SecStartup entry point needs 4 parameters
  //
  pushl   PcdGet32 (PcdTemporaryRamBase)

  //
  // Pass stack size into the PEI Core
  //
  pushl   PcdGet32 (PcdTemporaryRamSize)

  //
  // Pass Control into the PEI Core
  //
#ifndef FSP_FLAG
  call    ASM_PFX(SecStartup)
#endif
//CallPeiCoreEntryPoint   ENDP

//
// Load MCU path, if not already loaded from FIT table
//

//-----------------------------------------------------------------------------
//
//  Section:     EarlyMicrocodeUpdate
//
//  Description:
//
//-----------------------------------------------------------------------------
ASM_GLOBAL ASM_PFX(EarlyMicrocodeUpdate)
ASM_PFX(EarlyMicrocodeUpdate):
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdFlashMicrocodeFvSize), %edi
  or      %edi, %edi
  jz      SearchAndLoadMicrocodeReturn

  addl    PcdGet32 (PcdFlashMicrocodeFvBase), %edi // End addr of uCodes.

  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdFlashMicrocodeFvBase), %esi
  movzxw  (FVHEADER_LEN_OFF), %ebx
  addl    %ebx, %esi
  addl    $FFSHEADER_LEN, %esi               //add FFS header

  movl    $SearchAndLoadMicrocodeReturn, %ebp
  jmp     SearchAndLoadMicrocode

SearchAndLoadMicrocodeReturn:
  RET_ESI
.align 0x10

  //
  // GDT[0]: 0x00: Null entry, never used.
  //
.equ NULL_SEL,          .-GDT_BASE           // Selector [0]
GDT_BASE:
BootGdtTable:
    .long  0
    .long  0

  //
  // Linear data segment descriptor
  //
.equ LINEAR_SEL,        .-GDT_BASE           // Selector [0x8]
    .word 0x0FFFF                            // limit0x0xFFFFF
    .word  0                                 // base 0
    .byte  0
    .byte 0x092                              // present, ring0x0, data, expand-up, writable
    .byte 0x0CF                              // page-granular, 32-bit
    .byte  0

  //
  // Linear code segment descriptor
  //
.equ LINEAR_CODE_SEL,   .-GDT_BASE           // Selector [0x10]
    .word 0x0FFFF                            // limit 0xFFFFF
    .word  0                                 // base 0
    .byte  0
    .byte 0x09B                              // present, ring 0, data, expand-up, not-writable
    .byte 0x0CF                              // page-granular, 32-bit
    .byte  0

  //
  // System data segment descriptor
  //
.equ SYS_DATA_SEL,     .-GDT_BASE            // Selector [0x18]
    .word 0x0FFFF                            // limit0x0xFFFFF
    .word  0                                 // base 0
    .byte  0
    .byte 0x093                              // present, ring0x0, data, expand-up, not-writable
    .byte 0x0CF                              // page-granular, 32-bit
    .byte  0

  //
  // System code segment descriptor
  //
.equ SYS_CODE_SEL,     .-GDT_BASE            // Selector [0x20]
    .word  0x0FFFF                           // limit 0xFFFFF
    .word  0                                 // base 0
    .byte  0
    .byte  0x09A                             // present, ring 0, data, expand-up, writable
    .byte  0x0CF                             // page-granular, 32-bit
    .byte  0

  //
  // Spare segment descriptor
  //
.equ SYS16_CODE_SEL,   .-GDT_BASE            // Selector [0x28]
    .word  0x0FFFF                           // limit 0x0xFFFFF
    .word  0                                 // base 0
    .byte  0x0E                              // Changed from F000 to E000.
    .byte  0x09B                             // present, ring 0x0, code, expand-up, writable
    .byte  0x00                              // byte-granular, 16-bit
    .byte  0

  //
  // Spare segment descriptor
  //
.equ SYS16_DATA_SEL,   .-GDT_BASE            // Selector [0x30]
    .word  0x0FFFF                           // limit 0xFFFF
    .word  0                                 // base 0
    .byte  0
    .byte  0x093                             // present, ring 0, data, expand-up, not-writable
    .byte  0x00                              // byte-granular, 16-bit
    .byte  0

  //
  // Spare segment descriptor
  //
.equ SPARE5_SEL,       .-GDT_BASE            // Selector [0x38]
    .word  0                                 // limit 0
    .word  0                                 // base 0
    .byte  0
    .byte  0                                 // present, ring 0, data, expand-up, writable
    .byte  0                                 // page-granular, 32-bit
    .byte  0
.equ GDT_SIZE,         .-BootGdtTable        // Size, in bytes

#ifndef FSP_FLAG
GdtDesc:                                     // GDT descriptor
.equ OffsetGDTDesc,  .-_ModuleEntryPoint
    .word  GDT_SIZE - 1                      // GDT limit
    .long  BootGdtTable                      // GDT base address
#endif
ASM_PFX(NemInitLinearAddress):
NemInitLinearOffset:
    .long  ProtectedModeSecStart             // Offset of our 32 bit code
    .word  LINEAR_CODE_SEL


