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

.equ CR0_PE,      0x00000001
.equ CR0_NO_PE,   0xFFFFFFFE
.equ CR0_PG,      0x80000000
.equ CR0_NO_PG,   0x7FFFFFFF

.equ LOW_MEMORY_THUNK_CodeBuffer,           0x0
.equ LOW_MEMORY_THUNK_GdtDesc,              0x200
.equ LOW_MEMORY_THUNK_IdtDesc,              0x206
.equ LOW_MEMORY_THUNK_FlatEsp,              0x20C
.equ LOW_MEMORY_THUNK_RealModeIdtDesc,      0x210
.equ LOW_MEMORY_THUNK_PageMapLevel4,        0x216

.equ EFI_IA32_REGISTER_SET_SIZE, 48

#------------------------------------------------------------------------------
# VOID
# EFIAPI
# RealModeTemplate (
#   OUT UINTN          *LowCodeStart, // esp + 4
#   OUT UINTN          *LowCodeEnd,   // esp + 8
#   IN  VOID           *IntThunk      // esp + 0ch
#   )
#------------------------------------------------------------------------------
ASM_PFX(RealModeTemplate):
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        Begin Initialization Code      ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  #
  # Fill LowCodeStart
  #
  movl    4(%esp), %eax
  movl    LCS0, %ecx
  movl    %ecx, (%eax)

  #
  # Fill LowCodeEnd
  #
  movl    8(%esp), %eax
  movl    LCS99, %ecx
  movl    %ecx, (%eax)

  #
  # patch in the far jump to 16bit protected mode
  #
  movl    LCSP3, %eax
  movl    LCS1, %ecx
  subl    LCS0, %ecx
  movl    %ecx,(%eax)
  movl    0xc(%esp), %ecx

  #
  # patch in the far jump to real-mode
  #
  movl    LCSP4, %eax
  movl    LCS40, %ecx
  subl    LCS0, %ecx
  movw    %cx, (%eax)
  movl    0xc(%esp), %edx
  shrl    $4, %edx
  movw    %dx, 2(%eax)

  #
  # patch in the far jump back to flat mode
  #
  movl    LCSP1, %eax
  movl    LCS90, %ecx
  subl    LCS0, %ecx
  movl    0xc(%esp), %edx
  addl    %edx, %ecx
  movl    %ecx, (%eax)
  movw    %cs, %cx
  movw    %cx, 4(%eax)

  #
  # patch in GdtDesc
  #
  movl    0xc(%esp), %ecx
  movl    $LOW_MEMORY_THUNK_GdtDesc, %edx
  addl    %ecx, %edx
  movw    (%edx), %ax
  movw    %ax, (LGDT0)
  movw    2(%edx), %ax
  movw    %ax, (LGDT1)
  movw    4(%edx), %ax
  movw    %ax, (LGDT2)

  #
  # patch IntThunk address
  #
  movl    %ecx, (OffsetIntThunk)

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
  movl    %cr0, %eax
  pushw   %ax
  .byte   0x66
  movl    %cr3, %eax
  pushw   %ax
  .byte   0x66
  movl    %cr4, %eax
  pushw   %ax

  #
  # Prepare GDT
  #
  .byte   0xb8                    # mov ax,
LGDT2:
  .word   0x00                    # GDTR
  pushl   %eax

  .byte   0xb8                    # mov ax,
LGDT1:
  .word   0x00                    # GDTR
  pushl   %eax

  .byte   0xb8                    # mov ax,
LGDT0:
  .word   0x00                    # GDTR
  pushl   %eax

  pushw   %ss
  popw    %ds
  movl    %esp, %ebx

  popl    %eax
  popl    %eax
  popl    %eax

  #
  # load GDT
  #
  .byte   0x66
  .byte   0x0f, 0x01, 0x17        # lgdt    fword ptr [bx]

  #
  # Turn protected mode on
  #
  .byte   0x66
  movl    %cr0, %eax
  .byte   0x66
  orl     $CR0_PE, %eax
  .byte   0x66
  movl    %eax, %cr0

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
LCSP1:
  .long   0x0                         # offset (LCS90)
  .word   SYS_CODE_SEL                # selector  (flat CS)

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         32-bit protected mode         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LCS90:
  #
  # restore data selector
  #
  movw    %ax, %ds
  movw    %ax, %es
  movw    %ax, %fs
  movw    %ax, %gs
  movw    %ax, %ss

  #
  # Restore 32bit Idt
  #
  .byte 0xBE                      #  mov         esi,imm32
OffsetIntThunk:
  .long 0x0                       # offset of IntThunk

  movl    $LOW_MEMORY_THUNK_IdtDesc, %ecx
  addl    %esi, %ecx

  lidt    (%ecx)

  #
  # Restore 32bit stack
  #
  movl    $LOW_MEMORY_THUNK_FlatEsp, %ecx
  addl    %esi, %ecx
  movl    (%ecx), %esp
  #
  # adjust stack (for 4 byte aligned)
  #
  andl    $0xfffffffc, %esp

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         Call into native code         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  #
  # prepare parameter (EBP=SS:SP)
  #
  movl   %ebp, %eax
  movl   %eax, %edx
  andl   $0xffff0000, %eax
  shrl   $12, %eax
  andl   $0xffff, %edx
  addl   %edx, %eax

  movl   %eax, %ebx    # EBX = EFI_IA32_REGISTER_SET ptr

  # sync EFlags from IRET
  #   SEG:OFF Entry SEG:OFF
  movw  (4   +  8  +   4   + EFI_IA32_REGISTER_SET_SIZE)(%ebx), %cx  # CX is old Flags
  movzx %cx, %eax
  movl  %eax, 24(%ebx) # update new Flags

  movl   %ebx, %edx    # EFI_IA32_REGISTER_SET ptr
  pushl  %edx
  #   SEG:OFF
  movl  (4 + EFI_IA32_REGISTER_SET_SIZE)(%ebx), %ecx       # Entrypoint
  pushl %ecx
  movl  ASM_PFX(CommonReverseThunkEntry), %eax
  call  *%eax
  addl  $8, %esp

  # sync EFlags to IRET
  movl  24(%ebx), %eax  # EAX is new Flags
  #        SEG:OFF Entry SEG:OFF
  movw  %ax, (4   +  8  +   4   + EFI_IA32_REGISTER_SET_SIZE)(%ebx)  # update old Flags

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;         Return from native code       ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  cli

  #
  # ESI is still IntThunk now.
  #

  #
  # Set idt for real mode IVT
  #
  movl    $LOW_MEMORY_THUNK_RealModeIdtDesc, %ecx
  addl    %esi, %ecx
  lidt    (%esi)

  #
  # NOTE: We should not update segment value here for big real mode consideration
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
  movl    %cr0, %eax
  .byte   0x66
  andl    $CR0_NO_PE, %eax
  .byte   0x66
  movl    %eax, %cr0

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
  movl    %eax, %cr4
  popw    %ax
  .byte   0x66
  movl    %eax, %cr3
  popw    %ax
  .byte   0x66
  movl    %eax, %cr0

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
LCS99:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;        End Reverse Thunk Code         ;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

