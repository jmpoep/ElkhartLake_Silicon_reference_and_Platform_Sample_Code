;
; This file contains a 'Sample Driver' and is licensed as such
; under the terms of your license agreement with Intel or your
; vendor.  This file may be modified by the user, subject to
; the additional terms of the license agreement
;
;
; Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
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


%define LINEAR_SEL 0x8
%define LINEAR_CODE_SEL 0x10
%define SYS_DATA_SEL 0x18
%define SYS_CODE_SEL 0x20
%define SYS16_CODE_SEL 0x28
%define SYS16_DATA_SEL 0x30

%define CR0_PE 0x1
%define CR0_NO_PE 0xFFFFFFFE
%define CR0_PG 0x80000000
%define CR0_NO_PG 0x7FFFFFFF

struc DESCRIPTOR
  .Limit:       resw      1
  .Base:        resd      1
endstruc

struc LOW_MEMORY_THUNK
  .CodeBuffer:            resb 0x200
  .GdtDesc:               resb DESCRIPTOR_size
  .IdtDesc:               resb DESCRIPTOR_size
  .FlatEsp                resd 1
  .RealModeIdtDesc:       resb DESCRIPTOR_size
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

SECTION .text

extern ASM_PFX(CommonReverseThunkEntry)

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; RealModeTemplate (
;   OUT UINTN          *LowCodeStart, // esp + 4
;   OUT UINTN          *LowCodeEnd,   // esp + 8
;   IN  VOID           *IntThunk      // esp + 0ch
;   )
;------------------------------------------------------------------------------
global ASM_PFX(RealModeTemplate)
ASM_PFX(RealModeTemplate):
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        Begin Initialization Code      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS 32
  ;
  ; Fill LowCodeStart
  ;
  mov     eax, [esp + 4]
  mov     ecx, LCS0
  mov     [eax], ecx

  ;
  ; Fill LowCodeEnd
  ;
  mov     eax, [esp + 8]
  mov     ecx, LCS99
  mov     [eax], ecx

  ;
  ; patch in the far jump to 16bit protected mode
  ;
  mov     eax, (LCSP3 + 1)
  mov     ecx, LCS1
  sub     ecx, LCS0
  mov     [eax], ecx
  mov     ecx, [esp + 0xc]

  ;
  ; patch in the far jump to real-mode
  ;
  mov     eax, (LCSP4 + 1)
  mov     ecx, LCS40
  sub     ecx, LCS0
  mov     [eax], cx
  mov     edx, [esp + 0xc]
  shr     edx, 4
  mov     [eax+2], dx

  ;
  ; patch in the far jump back to flat mode
  ;
  mov     eax, (LCSP1 + 2)
  mov     ecx, LCS90
  sub     ecx, LCS0
  mov     edx, [esp + 0xc]
  add     ecx, edx
  mov     [eax], ecx
  mov     cx, cs
  mov     [eax+4], cx

  ;
  ; patch in GdtDesc
  ;
  mov     ecx, [esp + 0xc]
  mov     ax, [ecx + LOW_MEMORY_THUNK.GdtDesc]
  mov     word [LGDT0 + 1], ax
  mov     ax, [ecx + 2 + LOW_MEMORY_THUNK.GdtDesc]
  mov     word [LGDT1 + 1], ax
  mov     ax, [ecx + 4 + LOW_MEMORY_THUNK.GdtDesc]
  mov     word [LGDT2 + 1], ax

  ;
  ; patch IntThunk address
  ;
  mov     dword[OffsetIntThunk + 1], ecx

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
BITS 16
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
LGDT2:                     ; GDTR
  mov ax, 0
  push    ax

LGDT1:                     ; GDTR
  mov ax, 0
  push    ax

LGDT0:                     ; GDTR
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
o32 lgdt [bx]

  ;
  ; Turn protected mode on
  ;
o32 mov     eax, cr0
o32 or      eax, CR0_PE
o32 mov     cr0, eax

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         16-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;
  ; Return to 32 bit flat mode
  ; Put flat DS in ax
  ;
  mov   ax, SYS_DATA_SEL

  ;
  ; Enter to 32 bit cs
  ;
LCSP1:
  jmp     dword SYS_CODE_SEL : 0  ; jmp far 16:32

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         32-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS 32
LCS90:
  ;
  ; restore data selector
  ;
o16 mov     ds, ax
o16 mov     es, ax
o16 mov     fs, ax
o16 mov     gs, ax
o16 mov     ss, ax

  ;
  ; Restore 32bit Idt
  ;
OffsetIntThunk:
  mov esi, 0x0

  lidt     [esi + LOW_MEMORY_THUNK.IdtDesc]

  ;
  ; Restore 32bit stack
  ;
  mov     esp, [esi + LOW_MEMORY_THUNK.FlatEsp]
  ;
  ; adjust stack (for 4 byte aligned)
  ;
  and     esp, 0xfffffffc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         Call into native code         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;
  ; prepare parameter (EBP=SS:SP)
  ;
  mov   eax, ebp
  mov   edx, eax
  and   eax, 0xffff0000
  shr   eax, 12
  and   edx, 0xffff
  add   eax, edx

  mov   ebx, eax    ; EBX = EFI_IA32_REGISTER_SET ptr

  ; sync EFlags from IRET
  ;                SEG:OFF Entry SEG:OFF
  mov   cx, [ebx  +   4   +  8  +   4   + EFI_IA32_REGISTER_SET_size]  ; CX is old Flags
  movzx eax, cx
  mov   [ebx + 4 * 6], eax ; update new Flags

  mov   edx, ebx    ; EFI_IA32_REGISTER_SET ptr
  push  edx
  ;              SEG:OFF
  mov   ecx, [ebx + 4 + EFI_IA32_REGISTER_SET_size]       ; Entrypoint
  push  ecx
  mov   eax, ASM_PFX(CommonReverseThunkEntry)
  call  eax
  add   esp, 8

  ; sync EFlags to IRET
  mov   eax, [ebx + 4 * 6]  ; EAX is new Flags
  ;            SEG:OFF Entry SEG:OFF
  mov   [ebx  +   4   +  8  +   4   + EFI_IA32_REGISTER_SET_size], ax  ; update old Flags

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         Return from native code       ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  cli

  ;
  ; ESI is still IntThunk now.
  ;

  ;
  ; Set idt for real mode IVT
  ;
  lidt     [esi + LOW_MEMORY_THUNK.RealModeIdtDesc]

  ;
  ; NOTE: We should not update segment value here for big real mode consideration
  ;
LCSP3:
  jmp SYS16_CODE_SEL:0x0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         16-bit protected mode         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BITS 16
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
  jmp  0:0

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
o32 mov     cr4, eax
  pop     eax
o32 mov     cr3, eax
  pop     eax
o32 mov     cr0, eax

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
LCS99:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        End Reverse Thunk Code         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  nop

