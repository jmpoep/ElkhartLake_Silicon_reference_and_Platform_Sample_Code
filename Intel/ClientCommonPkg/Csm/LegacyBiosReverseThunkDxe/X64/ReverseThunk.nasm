;
; This file contains a 'Sample Driver' and is licensed as such
; under the terms of your license agreement with Intel or your
; vendor.  This file may be modified by the user, subject to
; the additional terms of the license agreement
;
;
; Copyright (c) 2016 - 2018, Intel Corporation. All rights reserved.<BR>
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by such
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
;
;
; Module Name:
;
;    ReverseThunk.nasm
;
; Abstract:
;
;

DEFAULT REL
SECTION .text

%define LINEAR_SEL 0x8
%define LINEAR_CODE_SEL 0x10
%define SYS_DATA_SEL 0x18
%define SYS_CODE_SEL 0x20
%define SYS16_CODE_SEL 0x28
%define SYS16_DATA_SEL 0x30
%define SYS_CODE64_SEL 0x38

%define CR0_PE 0x1
%define CR0_NO_PE 0xFFFFFFFE
%define CR0_PG 0x80000000
%define CR0_NO_PG 0x7FFFFFFF

struc GDT_ENTRY
  .LimitLow:    resw     1
  .BaseLow:     resw     1
  .BaseMid:     resb     1
  .Attribute:   resb     1
  .LimitHi:     resb     1
  .BaseHi:      resb     1
endstruc

struc DESCRIPTOR
  .Limit:       resw      1
  .Base:        resq      1
endstruc

struc LOW_MEMORY_THUNK
  .CodeBuffer:            resb 0x200
  .GdtDesc:               resb DESCRIPTOR_size
  .IdtDesc:               resb DESCRIPTOR_size
  .FlatEsp                resq 1
  .RealModeIdtDesc:       resb DESCRIPTOR_size
  .PageMapLevel4:         resq 1
endstruc

struc EFI_IA32_REGISTER_SET
  .RegEax:                resd            1
  .RegEbx:                resd            1
  .RegEcx:                resd            1
  .RegEdx:                resd            1
  .RegEsi:                resd            1
  .RegEdi:                resd            1
  .RegEFlags:             resd            1
  .RegEs:                 resw            1
  .RegCs:                 resw            1
  .RegSs:                 resw            1
  .RegDs:                 resw            1
  .RegFs:                 resw            1
  .RegGs:                 resw            1
  .RegEbp:                resd            1
  .RegEsp:                resd            1
endstruc

extern ASM_PFX(CommonReverseThunkEntry)

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; RealModeTemplate (
;     OUT UINTN          *LowCodeStart, // rcx, r10
;     OUT UINTN          *LowCodeEnd,   // rdx, r9
;     IN  VOID           *IntThunk      // r8
;     )
;------------------------------------------------------------------------------
global ASM_PFX(RealModeTemplate)
ASM_PFX(RealModeTemplate):
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        Begin Initialization Code      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS    64
  mov     r10, rcx
  mov     r9, rdx

  ;
  ; Fill LowCodeStart
  ;
  lea     rcx, [LCS0]
  mov     [r10], rcx

  ;
  ; Fill LowCodeEnd
  ;
  lea     rcx, [LCS99]
  mov     [r9], rcx

  ;
  ; patch in the far jump to 16bit protected mode
  ;
  lea     rax, [LCSP3 + 1]
  lea     rcx, [LCS1]
  lea     rdx, [LCS0]
  sub     rcx, rdx
  mov     [rax], cx
  mov     rdx, r10

  ;
  ; patch in the far jump to real-mode
  ;
  lea     rax, [LCSP4 + 1]
  lea     rcx, [LCS40]
  lea     rdx, [LCS0]
  sub     rcx, rdx
  mov     [rax], cx
  mov     rdx, r8
  shr     rdx, 4
  mov     [rax+2], dx

  ;
  ; patch in GdtDesc
  ;
  mov     rdx, r8
  mov     rcx, dword LOW_MEMORY_THUNK.GdtDesc
  add     ecx, edx
  mov     ax, [rcx]
  mov     word [LGDT0 + 1], ax
  mov     ax, [rcx + 2]
  mov     word [LGDT1 + 1], ax
  mov     ax, [rcx + 4]
  mov     word [LGDT2 + 1], ax

  ;
  ;   patch the address of CompatibilityModeVector
  ;
  mov     rax, dword LOW_MEMORY_THUNK.CodeBuffer  ; RAX = &(IntThunk->CodeBuffer)
  add     rax, r8                      ; rax:  the start address of code buffer

  lea     rcx, [LCS0]
  lea     rdx, [CompatibilityMode]
  sub     rdx, rcx
  mov     r11, rax
  add     r11, rdx                     ; r11 = IntThunk->CodeBuffer + of CompatibilityMode
  mov     dword [CompatibilityModeVector], r11d

  lea     rdx, [Backto32BitProtectedMode]
  sub     rdx, rcx
  mov     r11, rax
  add     r11, rdx
  mov     dword [OffsetBackto32BitProtectedMode + 2], r11d

  lea     rdx, [InLongMode]
  sub     rdx, rcx
  mov     r11, rax
  add     r11, rdx
  mov     dword[OffsetInLongMode + 2], r11d

  ;
  ; patch page table address
  ;
  mov     rdx, r8
  mov     rcx, dword LOW_MEMORY_THUNK.PageMapLevel4
  add     ecx, edx
  mov     edx, [rcx]
  mov     dword[TrampoleanCr3 + 1], edx

  ;
  ; patch IntThunk address
  ;
  mov     dword[OffsetIntThunk + 3], r8d

  ;
  ; patch done, return
  ;
  ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        End Initialization Code        ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        Begin Reverse Thunk Code       ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  align 16
BITS    16
LCS0:
  cli
  ;
  ; save EFI_IA32_REGISTER_SET
  ;
  push    esp
  push    ebp

  push    gs
  push    fs
  push    ds
  push    ss
  push    cs
  push    es
  sub     sp, 4    ; skip EFlags

  push    edi
  push    esi
  push    edx
  push    ecx
  push    ebx
  push    eax

  ;
  ; save stack point (EBP = SS:SP)
  ;
  xor     eax, eax
  mov     ax, ss
  shl     eax, 16
  mov     ax, sp
  mov     ebp, eax

  ;
  ; save CRx
  ;
o32 mov     eax, cr0
  push    eax
o32 mov     eax, cr3
  push    eax
o32 mov     eax, cr4
  push    eax

  ;
  ; Prepare GDT
  ;
LGDT2:
  mov ax, 0
  push    ax

LGDT1:
  mov ax, 0
  push    ax

LGDT0:
  mov ax, 0
  push    ax

  push    ss
  pop     ds
  mov     bx,sp

  pop     ax
  pop     ax
  pop     ax

  ;
  ; load GDT
  ;
o32  lgdt    [bx]

  ;
  ; Turn protected mode on
  ;
o32  mov     eax, cr0
  or      eax, CR0_PE
o32  mov     cr0, eax

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         16-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;
  ; Return to 32 bit flat mode
  ; Put flat DS in ax
  ;
  mov ax, SYS_DATA_SEL

  ;
  ; Enter to 32 bit cs
  ;
OffsetBackto32BitProtectedMode:
  jmp     dword SYS_CODE_SEL : 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         32-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS    32
Backto32BitProtectedMode:
  ;
  ; Go Long Mode HERE!!!!!
  ;

  ;
  ; Enable the 64-bit page-translation-table entries by
  ; setting CR4.PAE=1 (this is _required_ before activating
  ; long mode). Paging is not enabled until after long mode
  ; is enabled.
  ;
  mov eax, cr4
  bts eax, 5
  mov cr4, eax

  ;
  ; This is the Trapolean Page Tables that are guarenteed
  ;  under 4GB.
  ;
TrampoleanCr3:
  mov eax, 0
  mov cr3, eax

  ;
  ; Enable long mode (set EFER.LME=1).
  ;
  mov   ecx, 0xc0000080 ; EFER MSR number.
  rdmsr                 ; Read EFER.
  bts   eax, 8          ; Set LME=1.
  wrmsr                 ; Write EFER.

  ;
  ; Enable paging to activate long mode (set CR0.PG=1)
  ;
  mov   eax, cr0        ; Read CR0.
  bts   eax, 31         ; Set PG=1.
  mov   cr0, eax        ; Write CR0.

  ;
  ; This is the next instruction after enabling paging.  Jump to long mode
  ;
OffsetInLongMode:
a16  jmp   dword SYS_CODE64_SEL:00000009

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         64-bit long mode              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS    64
InLongMode:
  mov     rax, dword SYS_DATA_SEL

o16  mov     es, ax
o16  mov     ds, ax
o16  mov     fs, ax
o16  mov     gs, ax
o16  mov     ss, ax

  ;
  ; Restore 64bit Idt
  ;
OffsetIntThunk:
  mov     rsi, dword 0x0
  mov     rcx, dword LOW_MEMORY_THUNK.IdtDesc
  add     ecx, esi

  lidt    [rcx]

  ;
  ; Restore 64bit stack
  ;
  mov     rcx, dword LOW_MEMORY_THUNK.FlatEsp
  add     ecx, esi
  mov     rsp, [rcx]
  ;
  ; adjust stack
  ;
  and   esp, 0xfffffff0
  sub   rsp, 0x20

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         Call into native code         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;
  ; prepare parameter (EBP=SS:SP)
  ;
  mov   rax, rbp
  mov   rdx, rax
  and   eax, 0xffff0000
  shr   eax, 12
  and   edx, 0xffff
  add   eax, edx

  mov   rbx, rax    ; RBX = EFI_IA32_REGISTER_SET ptr

  ; sync EFlags from IRET
  ;                SEG:OFF Entry SEG:OFF
  mov   cx, [rbx  +   4   +  8  +   4   + EFI_IA32_REGISTER_SET_size]  ; CX is old Flags
  movzx eax, cx
  mov   [rbx + 4 * 6], eax ; update new Flags

  mov   rdx, rbx    ; EFI_IA32_REGISTER_SET ptr
  ;              SEG:OFF
  mov   rcx, [rbx + 4 + EFI_IA32_REGISTER_SET_size]       ; Entrypoint
  call   ASM_PFX(CommonReverseThunkEntry)

  ; sync EFlags to IRET
  mov   eax, [rbx + 4 * 6]  ; EAX is new Flags
  ;            SEG:OFF Entry SEG:OFF
  mov   [rbx  +   4   +  8  +   4   + EFI_IA32_REGISTER_SET_size], ax  ; update old Flags

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         Return from native code       ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  cli

  ;
  ; RSI is still IntThunk now.
  ;
  mov    rax, rsi
  add    rax, LOW_MEMORY_THUNK.CodeBuffer
  lea    rcx, [CompatibilityModeVector]
  lea    rdi, [LCS0]
  sub    rcx, rdi
  add    rcx, rax          ; RCX = IntThunk->CodeBuffer + of CompatibilityModeVector

  ;
  ; jmp into cmpatibility mode
  ;
  jmp  dword far [rcx]  ; qword

CompatibilityMode:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         64-bit compatibility mode     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;
  ; disable paging
  ;
  mov    rax, cr0
  btr    eax, 31    ; set PG=0
  mov    cr0, rax

  ;
  ;  set EFER.LME = 0 to leave long mode
  ;
  mov     ecx, 0xc0000080 ; EFER MSR number.
  rdmsr                   ; Read EFER.
  btr     eax, 8          ; Set LME=0.
  wrmsr                   ; Write EFER.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         32-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS    32
  ;
  ; Set idt for real mode IVT
  ;
  mov     ecx, LOW_MEMORY_THUNK.RealModeIdtDesc
  add     ecx, esi

  lidt    [ecx]

  ;
  ; NOTE: We should not update segment value here for big real mode consideration
  ;

  ;
  ; Disable PAE, because 16bit code may enter 32bit protected mode with paging
  ; without awaring PAE.
  ;
  mov eax, cr4
  btr eax, 5
  mov cr4, eax

  ;
  ; Go to 16-bit protected mode using a jump.
  ;   The and selector below were patched by the one-time code.
  ;
LCSP3:
  jmp SYS16_CODE_SEL:0x0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         16-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS    16
LCS1:
  mov     ax, SYS16_DATA_SEL
  mov     ds, ax
  mov     es, ax
  mov     fs, ax
  mov     gs, ax
  mov     ss, ax

  ;
  ; Turn protected mode off
  ;
o32  mov     eax, cr0
  and     eax, CR0_NO_PE
o32  mov     cr0, eax

LCSP4:
  jmp 0x0:0x0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         16-bit real mode              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LCS40:
  ;
  ; Fix real mode stack (EBP=SS:SP)
  ;
  mov     eax, ebp
  xor     esp, esp
  mov     sp, ax
  shr     eax, 16
  mov     ss, ax

  sub     sp, 12    ; point to CRx

  ;
  ; restore CRx
  ;
  pop     eax
o32  mov     cr4, eax
  pop     eax
o32  mov     cr3, eax
  pop     eax
o32  mov     cr0, eax

  ;
  ; restore EFI_IA32_REGISTER_SET
  ;
  pop     eax
  pop     ebx
  pop     ecx
  pop     edx
  pop     esi
  pop     edi

  add     sp, 4    ; skip EFlags
  pop     es
  add     sp, 2    ; skip    cs
  pop     ss
  pop     ds
  pop     fs
  pop     gs
  pop     ebp
  pop     esp

  ;
  ; back to caller
  ;
  retf

  align    16
CompatibilityModeVector:
  DD    0
  DW    SYS_CODE_SEL
LCS99:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        End Reverse Thunk Code         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  nop

