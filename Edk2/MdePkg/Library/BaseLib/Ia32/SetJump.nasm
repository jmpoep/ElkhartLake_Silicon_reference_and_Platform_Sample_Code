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
;   SetJump.Asm
;
; Abstract:
;
;   Implementation of SetJump() on IA-32.
;
;------------------------------------------------------------------------------

%include "Nasm.inc" ; CCEO-0016: RoyalParkOverrideContent

    SECTION .text

extern ASM_PFX(InternalAssertJumpBuffer)
extern ASM_PFX(PcdGet32 (PcdControlFlowEnforcementPropertyMask)) ; CCEO-0016: RoyalParkOverrideContent

;------------------------------------------------------------------------------
; UINTN
; EFIAPI
; SetJump (
;   OUT     BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer
;   );
;------------------------------------------------------------------------------
global ASM_PFX(SetJump)
ASM_PFX(SetJump):
    push    DWORD [esp + 4]
    call    ASM_PFX(InternalAssertJumpBuffer)    ; To validate JumpBuffer
    pop     ecx
    pop     ecx                         ; ecx <- return address
    mov     edx, [esp]

;
; CCEO-0016: RoyalParkOverrideBegin
;
    xor     eax, eax
    mov     [edx + 24], eax        ; save 0 to SSP

    mov     eax, [ASM_PFX(PcdGet32 (PcdControlFlowEnforcementPropertyMask))]
    test    eax, eax
    jz      CetDone
    mov     eax, cr4
    bt      eax, 23                ; check if CET is enabled
    jnc     CetDone

    mov     eax, 1
    INCSSP_EAX                     ; to read original SSP
    READSSP_EAX
    mov     [edx + 0x24], eax      ; save SSP

CetDone:
;
; CCEO-0016: RoyalParkOverrideEnd
;
    mov     [edx], ebx
    mov     [edx + 4], esi
    mov     [edx + 8], edi
    mov     [edx + 12], ebp
    mov     [edx + 16], esp
    mov     [edx + 20], ecx             ; eip value to restore in LongJump
    xor     eax, eax
    jmp     ecx

