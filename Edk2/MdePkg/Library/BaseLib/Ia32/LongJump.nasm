;------------------------------------------------------------------------------
;
; Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution.  The full text of the license may be found at
; http://opensource.org/licenses/bsd-license.php.
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;
; Module Name:
;
;   LongJump.Asm
;
; Abstract:
;
;   Implementation of _LongJump() on IA-32.
;
;------------------------------------------------------------------------------

%include "Nasm.inc" ; CCEO-0016: RoyalParkOverrideContent

    SECTION .text

extern ASM_PFX(PcdGet32 (PcdControlFlowEnforcementPropertyMask)) ; CCEO-0016: RoyalParkOverrideContent

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; InternalLongJump (
;   IN      BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer,
;   IN      UINTN                     Value
;   );
;------------------------------------------------------------------------------
global ASM_PFX(InternalLongJump)
ASM_PFX(InternalLongJump):

;
; CCEO-0016: RoyalParkOverrideBegin
;
    mov     eax, [ASM_PFX(PcdGet32 (PcdControlFlowEnforcementPropertyMask))]
    test    eax, eax
    jz      CetDone
    mov     eax, cr4
    bt      eax, 23                ; check if CET is enabled
    jnc     CetDone

    mov     edx, [esp + 4]         ; edx = JumpBuffer
    mov     edx, [edx + 24]        ; edx = target SSP
    READSSP_EAX
    sub     edx, eax               ; edx = delta
    mov     eax, edx               ; eax = delta

    shr     eax, 2                 ; eax = delta/sizeof(UINT32)
    INCSSP_EAX

CetDone:
;
; CCEO-0016: RoyalParkOverrideEnd
;
    pop     eax                         ; skip return address
    pop     edx                         ; edx <- JumpBuffer
    pop     eax                         ; eax <- Value
    mov     ebx, [edx]
    mov     esi, [edx + 4]
    mov     edi, [edx + 8]
    mov     ebp, [edx + 12]
    mov     esp, [edx + 16]
    jmp     dword [edx + 20]        ; restore "eip"

