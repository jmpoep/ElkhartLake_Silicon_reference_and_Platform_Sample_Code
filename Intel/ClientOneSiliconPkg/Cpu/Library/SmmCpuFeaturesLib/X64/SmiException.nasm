;; @file
;  Exception handlers used in SMM mode
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2016 - 2018 Intel Corporation.
;
;  The source code contained or described herein and all documents related to the
;  source code ("Material") are owned by Intel Corporation or its suppliers or
;  licensors. Title to the Material remains with Intel Corporation or its suppliers
;  and licensors. The Material may contain trade secrets and proprietary and
;  confidential information of Intel Corporation and its suppliers and licensors,
;  and is protected by worldwide copyright and trade secret laws and treaty
;  provisions. No part of the Material may be used, copied, reproduced, modified,
;  published, uploaded, posted, transmitted, distributed, or disclosed in any way
;  without Intel's prior express written permission.
;
;  No license under any patent, copyright, trade secret or other intellectual
;  property right is granted to or conferred upon you by disclosure or delivery
;  of the Materials, either expressly, by implication, inducement, estoppel or
;  otherwise. Any license under such intellectual property rights must be
;  express and approved by Intel in writing.
;
;  Unless otherwise agreed by Intel in writing, you may not remove or alter
;  this notice or any other notice embedded in Materials by Intel or
;  Intel's suppliers or licensors in any way.
;
;  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
;  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
;  the terms of your license agreement with Intel or your vendor. This file may
;  be modified by the user, subject to additional terms of the license agreement.
;
;@par Specification Reference:
;;

SECTION .data

global   ASM_PFX(gSmiExceptionCr3)
extern   ASM_PFX(mMceHandlerLongMode)
extern   ASM_PFX(gSmmFeatureSmiHandlerIdtr)

ASM_PFX(gSmiExceptionCr3) EQU gSmiExceptionCr3Patch - 4
;
; BUGBUG: Need to figure out how to get these values from GDT
; established in SMM module
;
%define CODE_SEL 0x38
%define DATA_SEL 0x20
%define CODE32_SEL 0x8

    DEFAULT REL
    SECTION .text

global ASM_PFX(PMIdtHandler)
ASM_PFX(PMIdtHandler):
    jmp    $
    retf

global ASM_PFX(PMIdtHandlerMachineCheck)
ASM_PFX(PMIdtHandlerMachineCheck):
    sub     esp, 8
    sidt    [rsp]            ; save 32bit IDTR
    push    rax
    push    rdx
    push    rcx

    mov eax, strict dword 0
gSmiExceptionCr3Patch:
    mov     cr3, rax

    mov     eax, 0x668                  ; as cr4.PGE is not set here, refresh cr3
    mov     cr4, rax                   ; in PreModifyMtrrs() to flush TLB.

; save old ss:esp
    mov     eax, ss
    push    rax
    push    rsp
    cmp     eax, DATA_SEL              ; check if ss:esp have been updated
    jz      Skip                       ; if not, update ss:esp

; change ss:esp
    sgdt    [rsp - 8]
    mov     ecx, dword [rsp - 6]
    add     ecx, eax

    xor     eax, eax
    mov     ax, word [rcx + 2]
    xor     edx, edx
    mov     dl, byte [rcx + 4]
    mov     dh, byte [rcx + 7]
    shl     edx, 0x10
    or      eax, edx
    add     esp, eax
    mov     eax, DATA_SEL
o16 mov     ss, ax

Skip:
    mov     rax, cr4
    push    rax                         ; save cr4
    mov     ecx, 0xC0000080
    rdmsr
    push    rax                         ; save MSR(0xc0000080)
    mov     rax, cr0
    push    rax                         ; save cr0

    mov     eax, CODE_SEL
    push    rax                         ; push cs hardcore
    call    Base                       ; push reture address for retf later
Base:
    add     dword [rsp], LongMode - Base ; offset for far retf, seg is the 1st arg
    mov     rax, cr4
    or      al, (1 << 5)
    mov     cr4, rax                    ; enable PAE

;
; Need to test for XD support
;
    mov     eax, 0x80000000
    cpuid
    cmp     eax, 0x80000000
    jbe     .0
    mov     eax, 0x80000001
    cpuid
    test    edx, BIT20
    jz      .0
    mov     ecx, 0xc0000080
    rdmsr
    or      ah, 8                      ; enable NXE
    wrmsr
.0:
    mov     ecx, 0xc0000080
    rdmsr
    or      ah, 1                      ; enable LME
    wrmsr

    mov     rbx, cr0
    or      ebx, 0x80010023            ; enable paging + WP + NE + MP + PE
    mov     cr0, rbx                    ; enable paging
    retf
LongMode:                               ; long mode starts here
    lea     rax, [ASM_PFX(gSmmFeatureSmiHandlerIdtr)] ; load long mode IDT table to handle the exception
    lidt    [rax]             ; that maybe issued in 64bit MC exception handler
    mov     rcx, rsp
    and     rsp, qword 0xfffffff0
    xor     rax, rax
    mov     ax,  ss
    push    rax
    push    rcx
    add     rcx, 32
    mov     eax, dword [rcx + 8]
    push    rax                         ; old eflags
    xor     rax, rax
    mov     ax,  cs                     ; cs
    push    rax
    lea     rax, [BackPmIdtHandler]     ; return EIP
    push    rax
    lea     rax, [ASM_PFX(mMceHandlerLongMode)]
    push    qword [rax]                       ; long mode MCA handle
    mov     eax, dword [rcx - 8]
    mov     edx, dword [rcx - 12]
    mov     ecx, dword [rcx - 16]

    add     rsp, 8
    jmp     qword [rsp - 8]         ; jmp to long mode MCA handle

BackPmIdtHandler:
    ;
    ; let rax save DS
    ;
    mov     rax, dword DATA_SEL

    ;
    ; Change to Compatible Segment
    ;
    mov     rcx, dword CODE32_SEL             ; load compatible mode selector
    shl     rcx, 32
    lea     rdx, [Compatible]      ; assume address < 4G
    or      rcx, rdx
    push    rcx
    retf

Compatible:
    pop     rax
    mov     cr0, rax                    ; restore cr0 to disable paging.

    mov     ecx, 0xC0000080
    rdmsr
    pop     rax
    wrmsr                               ; restore MSR (0xc0000080) to clear EFER.LME

    pop     rax
    mov     cr4, rax                    ; restore cr4 to clear PAE

    lss     esp, [rsp]        ; restore ss:esp

    add     esp, 4                      ; skip old ss
    pop     rcx
    pop     rdx
    pop     rax
    lidt    [rsp]             ; load saved 32bit IDTR
    add     esp, 12 + 8
    ;
    ; retf maybe used for MCE
    ;
    push    qword [rsp - 8]
    push    qword [rsp - 8]
    retf

