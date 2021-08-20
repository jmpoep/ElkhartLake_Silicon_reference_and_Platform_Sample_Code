;; @file
;  Assembly code of Cpu
;
;@copyright
; Copyright (c) 2017 - 2018 Intel Corporation. All rights reserved.
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution.  The full text of the license may be found at
; http://opensource.org/licenses/bsd-license.php.
;  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
;  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;;

IA32_CR4_OSFXSR           equ        200h
IA32_CR4_OSXMMEXCPT       equ        400h
IA32_CR0_MP               equ        2h

IA32_CPUID_SSE2           equ        02000000h
IA32_CPUID_SSE2_B         equ        26

SECTION .text

;------------------------------------------------------------------------------
;   Set up flags in CR4 for XMM instruction enabling
;------------------------------------------------------------------------------
global ASM_PFX(InitXmm)
ASM_PFX(InitXmm):
    push    ebx

    ; Check whether SSE2 is supported
    mov     eax, 1
    cpuid
    bt      edx, IA32_CPUID_SSE2_B
    jnc     .skipxmm

    ; Enable XMM
    mov     eax, cr0
    or      eax, IA32_CR0_MP
    mov     cr0, eax
    mov     eax, cr4
    or      eax, IA32_CR4_OSFXSR
    or      eax, IA32_CR4_OSXMMEXCPT
    mov     cr4, eax

.skipxmm:
    pop     ebx
    ret

;------------------------------------------------------------------------------
;   Invalidate cache
;------------------------------------------------------------------------------
global ASM_PFX(CacheInvd)
ASM_PFX(CacheInvd):
    invd
    ret
