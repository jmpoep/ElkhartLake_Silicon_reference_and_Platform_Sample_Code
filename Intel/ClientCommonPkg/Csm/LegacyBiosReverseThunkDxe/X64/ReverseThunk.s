#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
#
# Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
#
#
# Module Name:
#
#    ReverseThunk.asm
#
# Abstract:
#
#

ASM_GLOBAL ASM_PFX(CommonReverseThunkEntry)
ASM_GLOBAL ASM_PFX(RealModeTemplate)

.equ LINEAR_SEL,      0x8
.equ LINEAR_CODE_SEL, 0x10
.equ SYS_DATA_SEL,    0x18
.equ SYS_CODE_SEL,    0x20
.equ SYS16_CODE_SEL,  0x28
.equ SYS16_DATA_SEL,  0x30
.equ SYS_CODE64_SEL,  0x38

.equ CR0_PE,      0x00000001
.equ CR0_NO_PE,   0xFFFFFFFE
.equ CR0_PG,      0x80000000
.equ CR0_NO_PG,   0x7FFFFFFF

.equ LOW_MEMORY_THUNK_CodeBuffer,           0x0
.equ LOW_MEMORY_THUNK_GdtDesc,              0x200
.equ LOW_MEMORY_THUNK_IdtDesc,              0x20A
.equ LOW_MEMORY_THUNK_FlatEsp,              0x214
.equ LOW_MEMORY_THUNK_RealModeIdtDesc,      0x21C
.equ LOW_MEMORY_THUNK_PageMapLevel4,        0x226

.equ EFI_IA32_REGISTER_SET_SIZE, 48

#------------------------------------------------------------------------------
# VOID
# EFIAPI
# RealModeTemplate (
#     OUT UINTN          *LowCodeStart, // rcx, r10
#     OUT UINTN          *LowCodeEnd,   // rdx, r9
#     IN  VOID           *IntThunk      // r8
#     )
#------------------------------------------------------------------------------
ASM_PFX(RealModeTemplate):
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        Begin Initialization Code      ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  movq    %rcx, %r10
  movq    %rdx, %r9

  #
  # Fill LowCodeStart
  #
  movq    LCS0, %rcx
  movq    %rcx, (%r10)

  #
  # Fill LowCodeEnd
  #
  movq    LCS99, %rcx
  movq    %rcx, (%r9)

  #
  # patch in the far jump to 16bit protected mode
  #
  movq    LCSP3, %rax
  movq    LCS1, %rcx
  movq    LCS0, %rdx
  subq    %rdx,%rcx
  movw    %cx, (%rax)
  movq    %r10, %rdx

  #
  # patch in the far jump to real-mode
  #
  movq    LCSP4, %rax
  movq    LCS40, %rcx
  movq    LCS0, %rdx
  subq    %rdx, %rcx
  movw    %cx, (%rax)
  movq    %r8, %rdx
  shrq    $4, %rdx
  movw    %dx, 2(%rax)

  #
  # patch in GdtDesc
  #
  movq    %r8, %rdx
  movq    $LOW_MEMORY_THUNK_GdtDesc, %rcx
  addl    %edx, %ecx
  movw    (%rcx), %ax
  movw    %ax, (LGDT0)
  movw    2(%rcx), %ax
  movw    %ax, (LGDT1)
  movw    4(%rcx), %ax
  movw    %ax, (LGDT2)

  #
  #   patch the address of CompatibilityModeVector
  #
  movq    $LOW_MEMORY_THUNK_CodeBuffer, %rax  # RAX = &(IntThunk->CodeBuffer)
  addq    %r8, %rax                      # rax:  the start address of code buffer

  movq    LCS0, %rcx
  movq    CompatibilityMode, %rdx
  subq    %rcx, %rdx
  movq    %rax, %r11
  addq    %rdx, %r11                     # r11 = IntThunk->CodeBuffer + offset of CompatibilityMode
  movl    %r11d, (CompatibilityModeVector)

  movq    Backto32BitProtectedMode, %rdx
  subq    %rcx, %rdx
  movq    %rax, %r11
  addq    %rdx, %r11
  movl    %r11d, (OffsetBackto32BitProtectedMode)

  movq    InLongMode, %rdx
  subq    %rcx, %rdx
  movq    %rax, %r11
  addq    %rdx, %r11
  movl    %r11d, (OffsetInLongMode)

  #
  # patch page table address
  #
  movq    %r8, %rdx
  movq    LOW_MEMORY_THUNK_PageMapLevel4, %rcx
  addl    %edx, %ecx
  movl    (%rcx), %edx
  movl    %edx, (TrampoleanCr3)

  #
  # patch IntThunk address
  #
  movl    %r8d, (OffsetIntThunk)

  #
  # patch done, return
  #
  ret
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        End Initialization Code        ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        Begin Reverse Thunk Code       ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  .align 16
LCS0:
  cli
  #
  # save EFI_IA32_REGISTER_SET
  #
  pushw   %sp
  pushw   %bp

  .byte      0x0f, 0xA8 # push    gs
  .byte      0x0f, 0xA0 # push    fs
  .byte      0x1e       # push    ds
  .byte      0x16       # push    ss
  .byte      0x0e       # push    cs
  .byte      0x06       # push    es
  subl    $4, %esp      # skip EFlags

  pushw   %di
  pushw   %si
  pushw   %dx
  pushw   %cx
  pushw   %bx
  pushw   %ax

  #
  # save stack point (EBP = SS:SP)
  #
  xorw    %ax, %ax
  movl    %ss, %eax
  shlw    $16, %ax
  movl    %esp, %eax
  movw    %ax, %bp

  #
  # save CRx
  #
  .byte   0x66
  movq    %cr0, %rax
  pushw   %ax
  .byte   0x66
  movq    %cr3, %rax
  pushw   %ax
  .byte   0x66
  movq    %cr4, %rax
  pushw   %ax

  #
  # Prepare GDT
  #
  .byte   0xb8                    # mov ax,
LGDT2:
  .word   0x00                    # GDTR
  pushq   %rax

  .byte   0xb8                    # mov ax,
LGDT1:
  .word   0x00                    # GDTR
  pushq   %rax

  .byte   0xb8                    # mov ax,
LGDT0:
  .word   0x00                    # GDTR
  pushq   %rax

  .byte   0x16 # push    ss
  .byte   0x1F # pop     ds
  movl    %esp, %ebx

  popq    %rax
  popq    %rax
  popq    %rax

  #
  # load GDT
  #
  .byte   0x66
  .byte   0x0f, 0x01, 0x17        # lgdt    fword ptr [bx]

  #
  # Turn protected mode on
  #
  .byte   0x66
  movq    %cr0, %rax
  .byte   0x66
  orl     $CR0_PE, %eax
  .byte   0x66
  movq    %rax, %cr0

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         16-bit protected mode         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  #
  # Return to 32 bit flat mode
  # Put flat DS in ax
  #
  .byte  0xB8                         # 'mov ax,imm16' opcode
  .word  SYS_DATA_SEL                 # flat DS (imm16)

  #
  # Enter to 32 bit cs
  #
  .byte   0x66
  .byte   0xEA                        # jmp far 16:32
OffsetBackto32BitProtectedMode:
  .long   0x0000008                   # offset $+8   (Backto32BitProtectedMode)
  .word   SYS_CODE_SEL                # selector  (flat CS)

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         32-bit protected mode         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Backto32BitProtectedMode:

  #
  # Go Long Mode HERE!!!!!
  #

  #
  # Enable the 64-bit page-translation-table entries by
  # setting CR4.PAE=1 (this is _required_ before activating
  # long mode). Paging is not enabled until after long mode
  # is enabled.
  #
  movq %cr4, %rax
  btsl $5, %eax
  movq %rax, %cr4

  #
  # This is the Trapolean Page Tables that are guarenteed
  #  under 4GB.
  #
#;; mov eax, imm32
  .byte   0xB8                        # 'mov eax,imm32' opcode
TrampoleanCr3:
  .long   0x0                         # imm32
  movq %rax, %cr3

  #
  # Enable long mode (set EFER.LME=1).
  #
  movl  $0xc0000080, %ecx # EFER MSR number.
  rdmsr                   # Read EFER.
  btsl  $8, %eax          # Set LME=1.
  wrmsr                   # Write EFER.

  #
  # Enable paging to activate long mode (set CR0.PG=1)
  #
  movq  %cr0, %rax        # Read CR0.
  btsl  $31, %eax         # Set PG=1.
  movq  %rax, %cr0        # Write CR0.

  #
  # This is the next instruction after enabling paging.  Jump to long mode
  #
  .byte      0x67
  .byte      0xea                # Far Jump $+9:Selector to reload CS
OffsetInLongMode:
  .long      0x0000009           #   $+9 Offset is ensuing instruction boundary
PatchLongModeCS:
  .word      SYS_CODE64_SEL      #   Selector is our code selector, 10h

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         64-bit long mode              ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

InLongMode:
  .byte      0x48                # mov ax, imm16
  .byte      0xB8
  .quad      SYS_DATA_SEL

  movw    %ax, %es
  movw    %ax, %ds
  movw    %ax, %fs
  movw    %ax, %gs
  movw    %ax, %ss

  #
  # Restore 64bit Idt
  #
  .byte      0x48                # mov     rsi, imm32
  .byte      0xBE
OffsetIntThunk:
  .quad      0x0

  movq    $LOW_MEMORY_THUNK_IdtDesc, %rcx
  addl    %esi, %ecx

  .byte      0xf, 0x1, 0x19      # lidt    FWORD PTR [ecx]

  #
  # Restore 64bit stack
  #
  movq    $LOW_MEMORY_THUNK_FlatEsp, %rcx
  addl    %esi, %ecx
  movq    (%rcx), %rsp
  #
  # adjust stack
  #
  andl  $0xfffffff0, %esp
  subq  $0x20, %rsp

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         Call into native code         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  #
  # prepare parameter (EBP=SS:SP)
  #
  movq  %rbp, %rax
  movq  %rax, %rdx
  andl  $0xffff0000, %eax
  shrl  $12, %eax
  andl  $0xffff, %eax
  addl  %edx, %eax

  movq  %rax, %rbx    # RBX = EFI_IA32_REGISTER_SET ptr

  # sync EFlags from IRET
  #   SEG:OFF Entry SEG:OFF
  movw  (4   +  8  +   4   + EFI_IA32_REGISTER_SET_SIZE)(%rbx), %cx  # CX is old Flags
  movzx %cx, %eax
  movl  %eax, 24(%rbx) # update new Flags

  movq  %rbx, %rdx    # EFI_IA32_REGISTER_SET ptr
  #   SEG:OFF
  movq  (4 + EFI_IA32_REGISTER_SET_SIZE)(%rbx), %rcx       # Entrypoint
  movq  CommonReverseThunkEntry, %rax
  call  *%rax

  # sync EFlags to IRET
  movl  24(%rbx), %eax  # EAX is new Flags
  #        SEG:OFF Entry SEG:OFF
  movw  %ax, (4   +  8  +   4   + EFI_IA32_REGISTER_SET_SIZE)(%rbx)  # update old Flags

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         Return from native code       ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  cli

  #
  # RSI is still IntThunk now.
  #
  movq   %rsi, %rax
  addq   $LOW_MEMORY_THUNK_CodeBuffer, %rax
  movq   CompatibilityModeVector, %rcx
  movq   LCS0, %rdi
  subq   %rdi, %rcx
  addq   %rax, %rcx          # RCX = IntThunk->CodeBuffer + offset of CompatibilityModeVector

  #
  # jmp into cmpatibility mode
  #
  jmp    *(%rcx)

CompatibilityMode:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         64-bit compatibility mode     ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  #
  # disable paging
  #
  movq   %cr0, %rax
  btrl   $31, %eax    # set PG=0
  movq   %rax, %cr0

  #
  #  set EFER.LME = 0 to leave long mode
  #
  movl    $0xc0000080, %ecx # EFER MSR number.
  rdmsr                     # Read EFER.
  btrl    $8, %eax          # Set LME=0.
  wrmsr                     # Write EFER.

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         32-bit protected mode         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  #
  # Set idt for real mode IVT
  #
  movl    $LOW_MEMORY_THUNK_RealModeIdtDesc, %ecx
  addl    %esi, %ecx

  .byte      0xf, 0x1, 0x19      # lidt    FWORD PTR [ecx]

  #
  # NOTE: We should not update segment value here for big real mode consideration
  #

  #
  # Disable PAE, because 16bit code may enter 32bit protected mode with paging
  # without awaring PAE.
  #
  movq %cr4, %rax
  btrl $5, %eax
  movq %rax, %cr4

  #
  # Go to 16-bit protected mode using a jump.
  #   The offset and selector below were patched by the one-time code.
  #
  .byte   0xEA                    # jmp far 16:32
LCSP3:
  .long   0x0                     # offset(LCS1)
  .word   SYS16_CODE_SEL

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         16-bit protected mode         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LCS1:
  .byte  0xB8                         # 'mov ax,imm16' opcode
  .word  SYS16_DATA_SEL               # flat DS (imm16)

  movl    %eax, %es
  movl    %eax, %ds
  movl    %eax, %fs
  movl    %eax, %gs
  movl    %eax, %ss

  #
  # Turn protected mode off
  #
  .byte   0x66
  movq    %cr0, %rax
  .byte   0x66
  andl    $CR0_NO_PE, %eax
  .byte   0x66
  movq    %rax, %cr0

  .byte   0xEA                    # jmp far 16:16
LCSP4:
  .word   0x0                     # offset(LCS40)
  .word   0x0                     # segment(realmode cs)

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         16-bit real mode              ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LCS40:
  #
  # Fix real mode stack (EBP=SS:SP)
  #
  movw    %bp, %ax
  xorw    %sp, %sp
  movl    %eax,%esp
  shrw    $16, %ax
  .byte   0x8e                    # mov ss, ax
  .byte   0xd0

  subl    $12, %esp    # point to CRx

  #
  # restore CRx
  #
  popw    %ax
  .byte   0x66
  movq    %rax, %cr4
  popw    %ax
  .byte   0x66
  movq    %rax, %cr3
  popw    %ax
  .byte   0x66
  movq    %rax, %cr0

  #
  # restore EFI_IA32_REGISTER_SET
  #
  popw    %ax
  popw    %bx
  popw    %cx
  popw    %dx
  popw    %si
  popw    %di

  addl    $4, %esp    # skip EFlags
  .byte   0x7         # pop     es
  addl    $2, %esp    # skip    cs
  .byte   0x17        # pop     ss
  .byte   0x1f        # pop     ds
  .byte   0xf, 0xA1   # pop     fs
  .byte   0xf, 0xA9   # pop     gs

  popw    %bp
  popw    %sp

  #
  # back to caller
  #
  retf

  .align    16
CompatibilityModeVector:
  .space    4
  .word     SYS_CODE_SEL
LCS99:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        End Reverse Thunk Code         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

