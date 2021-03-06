;; @file
;  This file contains the code to launch BIOS ACM functions in PEI phase
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2017 - 2018 Intel Corporation.
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
;@par Specification
;;


DEFAULT REL
SECTION .text


;
; BIOS ACM functions
;
%define TXT_FN_SCLEAN        0x0
%define TXT_FN_RESET_EST_BIT 0x1
%define TXT_FN_RESET_AUX     0x2
%define TXT_FN_SCHECK        0x4
%define TXT_FN_CLEAR_SECRETS 0x5
%define TXT_FN_LOCK_CONFIG   0x6
%define TXT_FN_ACHECK        0x7
;
; Misc
;
%define ENTERACCS            0x2
%define PARAMETERS           0x6
%define ACMOD_SIZE           24
#define PORT80_CODE_PREFIX   0xA0
;
; Instructions
;
%define _EMMS    db 0xf, 0x77
%define _GETSEC  db 0xf, 0x37
;
; MMX registers DWORD access
;
%define MOVDIN0  db 0xf, 0x6e, 0xc0  ; movd mm0, eax
%define MOVDOUT0 db 0xf, 0x7e, 0xc0  ; movd eax, mm0
%define MOVDIN1  db 0xf, 0x6e, 0xc8  ; movd mm1, eax
%define MOVDOUT1 db 0xf, 0x7e, 0xc8  ; movd eax, mm1
%define MOVDIN2  db 0xf, 0x6e, 0xd0  ; movd mm2, eax
%define MOVDOUT2 db 0xf, 0x7e, 0xd0  ; movd eax, mm2
%define MOVDIN3  db 0xf, 0x6e, 0xd8  ; movd mm3, eax
%define MOVDOUT3 db 0xf, 0x7e, 0xd8  ; movd eax, mm3
%define MOVDIN4  db 0xf, 0x6e, 0xe0  ; movd mm4, eax
%define MOVDOUT4 db 0xf, 0x7e, 0xe0  ; movd eax, mm4
%define MOVDIN5  db 0xf, 0x6e, 0xe8  ; movd mm5, eax
%define MOVDOUT5 db 0xf, 0x7e, 0xe8  ; movd eax, mm5
%define MOVDIN6  db 0xf, 0x6e, 0xf0  ; movd mm6, eax
%define MOVDOUT6 db 0xf, 0x7e, 0xf0  ; movd eax, mm6
%define MOVDIN7  db 0xf, 0x6e, 0xf8  ; movd mm7, eax
%define MOVDOUT7 db 0xf, 0x7e, 0xf8  ; movd eax, mm7
;
; MSRs
;
%define IA32_MISC_ENABLE     0x1A0
%define IA32_EFER_MSR        0xC0000080
;
; MTRRs
;
%define IA32_MTRR_PHYSBASE0  0x200
%define IA32_MTRR_PHYSMASK0  0x201
%define IA32_MTRR_PHYSBASE1  0x202
%define IA32_MTRR_PHYSMASK1  0x203
%define IA32_MTRR_PHYSBASE2  0x204
%define IA32_MTRR_PHYSMASK2  0x205
%define IA32_MTRR_PHYSBASE3  0x206
%define IA32_MTRR_PHYSMASK3  0x207
%define IA32_MTRR_PHYSBASE4  0x208
%define IA32_MTRR_PHYSMASK4  0x209
%define IA32_MTRR_PHYSBASE5  0x20A
%define IA32_MTRR_PHYSMASK5  0x20B
%define IA32_MTRR_PHYSBASE6  0x20C
%define IA32_MTRR_PHYSMASK6  0x20D
%define IA32_MTRR_PHYSBASE7  0x20E
%define IA32_MTRR_PHYSMASK7  0x20F
%define IA32_MTRR_DEF_TYPE   0x2FF
%define IA32_MTRR_CAP        0xFE
;
; Only low order bits are assumed
;
%define MTRR_MASK            0xFFFFF000
%define MTRR_ENABLE          (1 << 11)
%define MTRR_FIXED_ENABLE    (1 << 10)
%define MTRR_VALID           (1 << 11)
%define UC                   0x0
%define WB                   0x6
;
; Control register bits
;
%define CR0_NE_MASK          (1 << 5)
%define CR0_NW_MASK          (1 << 29)
%define CR0_CD_MASK          (1 << 30)
%define CR4_DE               (1 << 3)
%define CR4_OSFXSR           (1 << 9)
%define CR4_SMXE             (1 << 14)
;
; Machine check architecture MSR registers
;
%define MCG_CAP 0x179
%define MC0_STATUS 0x401

%define ACM_SIZE_TO_CACHE    xmm0
%define ACM_BASE_TO_CACHE    xmm1
%define NEXT_MTRR_INDEX      xmm2
%define NEXT_MTRR_SIZE       xmm3
%define MTRR_PHYS_MASK_HIGH  xmm4

%define BIOS_GDT [ebp-0x10]
%define BIOS_IDT [ebp-0x20]


;
; TXT register space definitions
;
#define TXT_PUBLIC_BASE      0xFED30000
#define TXT_SINIT_SIZE2      0x27C
#define BIOACM_ADDR          TXT_SINIT_SIZE2


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch BiosAcm SCLEAN
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;    invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(LaunchBiosAcmSclean)
ASM_PFX(LaunchBiosAcmSclean):
    ;
    ; Tell where we are
    ;
    mov     eax, 0x11110000
    in      ax, 0x80
    mov     ah, PORT80_CODE_PREFIX + TXT_FN_SCLEAN
    out     0x80, eax

    mov     ecx, [TXT_PUBLIC_BASE + BIOACM_ADDR]
    mov     edx, TXT_FN_SCLEAN

    jmp     LaunchBiosAcm_CommonFlow


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch BiosAcm ClearSecrets
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;    invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(LaunchBiosAcmClearSecrets)
ASM_PFX(LaunchBiosAcmClearSecrets):
    ;
    ; Tell where we are
    ;
    mov     eax, 0x11110000
    in      ax, 0x80
    mov     ah, PORT80_CODE_PREFIX + TXT_FN_CLEAR_SECRETS
    out     0x80, eax

    mov     ecx, [TXT_PUBLIC_BASE + BIOACM_ADDR]
    mov     edx, TXT_FN_CLEAR_SECRETS

    jmp     LaunchBiosAcm_CommonFlow


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Launch BiosAcm Alias Check
;
;  Setup GETSEC environment (protected mode, mtrrs, etc) and
;   invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(LaunchBiosAcmAcheck)
ASM_PFX(LaunchBiosAcmAcheck):
    ;
    ; Tell where we are
    ;
    mov     eax, 0x11110000
    in      ax, 0x80
    mov     ah, PORT80_CODE_PREFIX + TXT_FN_ACHECK
    out     0x80, eax

    mov     ecx, [TXT_PUBLIC_BASE + BIOACM_ADDR]
    mov     edx, TXT_FN_ACHECK

    jmp     LaunchBiosAcm_CommonFlow


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;
;  DoPowerCycleReset
;
;  @param[in]   None
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(DoPowerCycleReset)
ASM_PFX(DoPowerCycleReset):

ResetSystem:
    mov     dx, 0xCF8               ; Make warm system reset through port 0CF9h
    mov     eax, 0x8000FAAC         ; to be global system reset - set bit 20
    out     dx, eax                 ; of device 1F
    mov     dx, 0xCFC
    in      eax, dx
    or      eax, (1 << 20)
    out     dx, eax

    mov     dx, 0xCF9
    mov     al, 0
    out     dx, al
    mov     al, 0xE
    out     dx, al
    cli
    hlt
    jmp     $


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Save Ap Config
;
;  @param[in]  ApCfg   pointer to save area
;
;  Function is called in memory present environment on S3 resume
;    path. Saves contents of all MTRRs into table plus some registers.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(SaveApConfig)
ASM_PFX(SaveApConfig):
    ret


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;
;  Procedure:   LaunchBiosAcm
;
;  @param[in]   AcmBase   Base address of LT BIOS ACM
;  @param[in]   Function  function number to execute
;
;  Output:
;
;  Stack:       Available at beginning of routine, but routine goes 'stackless'
;
;  Registers:
;
;  Description: Setup GETSEC environment (protected mode, mtrrs, etc) and
;               invoke GETSEC:ENTERACCS with requested BIOS ACM entry point.
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(LaunchBiosAcm)
ASM_PFX(LaunchBiosAcm):
;    START_FRAME
;    MAKE_LOCAL BIOS_GDT[2]:QWORD
;    MAKE_LOCAL BIOS_IDT[2]:QWORD
;    END_FRAME

    enter  0x30,0

    mov     ecx, DWORD [ebp+0x8]
    mov     ecx, [ecx]              ; ecx = AcmBase
    mov     edx, DWORD [ebp+0xc]    ; edx = Function

    ;
    ; Save the general purpose register state
    ;
    pushf
    cli
    pushad

    ; check if the AcmBase is a good address (none zero)
    cmp     ecx, 0                  ; bad ACM address?
    je      LaunchBiosAcm_SkipLaunch              ; Yes, then exit without any further work

LaunchBiosAcm_CommonFlow:
    ;
    ; Save the parameters passed to us
    ;
    mov     eax, ecx                ; save address of BIOS ACM in MMX0
    MOVDIN0
    mov     eax, cr3                ; save page table in MMX1
    MOVDIN1
    mov     eax, edx                ; save value of ESI for GETSEC[ENTERACCS] in MMX2
    MOVDIN2

    sgdt    BIOS_GDT                ; save gdtr
    sidt    BIOS_IDT                ; save idtr

    lea     eax, BIOS_GDT           ; eax = address of saved gdtr
    MOVDIN3                         ; mm3 = address of saved gdtr

    mov     eax, ebp
    MOVDIN4                         ; mm4 = ebp
    xor     eax, eax
    mov     ax, ss
    MOVDIN5                         ; mm5 = ss
    mov     ax, cs
    MOVDIN6                         ; mm6 = cs

    ;
    ; Save control registers
    ;
    mov     eax, cr4
    push    eax
    mov     eax, cr0
    push    eax

    ;
    ; Save IA32_MISC_ENABLES MSR
    ;
    mov     ecx, IA32_MISC_ENABLE
    rdmsr
    push    eax
    push    edx

;-----------------------------------------------------------------------------
;
;  Section:      Save variable MTRRs
;
;  Description:  All variable MTRRs are saved in local variables.
;                They will be restored after running of BIOS ACM.
;
;-----------------------------------------------------------------------------
    mov     ecx, IA32_MTRR_CAP
    rdmsr
    and     eax, 0xFF
    shl     eax, 1
    mov     ecx, eax

LaunchBiosAcm_SaveNextMtrr:
    add     ecx, IA32_MTRR_PHYSBASE0 - 1
    rdmsr
    push    edx
    push    eax
    sub     ecx, IA32_MTRR_PHYSBASE0 - 1
    loop    LaunchBiosAcm_SaveNextMtrr

    ;
    ; Save IA32_MTRR_DEF_TYPE MSR
    ;
    mov     ecx, IA32_MTRR_DEF_TYPE
    rdmsr
    push    eax
    push    edx

    ; Save the rest of the segment registers
    xor     eax, eax
    mov     ax, gs
    push    eax
    mov     ax, fs
    push    eax
    mov     ax, es
    push    eax
    mov     ax, ds
    push    eax

    ;
    ; For reloading CS
    ;
    mov     bx, cs
    push    ebx
    mov     ebx, LaunchBiosAcm_ReloadCS
    push    ebx


    ;
    ; Now that all of our state is on the stack, save esp
    ;
    mov     eax, esp
    MOVDIN7                         ; mm7 = esp

;-----------------------------------------------------------------------------
;
;  Section:      Program MTRRs
;
;  Description:  Variable MTRRs are programmed to cache ACM as WB
;
;-----------------------------------------------------------------------------
    ;
    ; Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
    ; based on the physical address size supported for this processor
    ; This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
    ;
    ; Examples:
    ;  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
    ;  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
    ;
    mov     eax, 80000008h            ; Address sizes leaf
    cpuid
    sub     al, 32
    movzx   eax, al
    xor     esi, esi
    bts     esi, eax
    dec     esi                       ; esi <- MTRR_PHYS_MASK_HIGH
    movd    MTRR_PHYS_MASK_HIGH, esi

    ;
    ; Enable SMXE, SSE and debug extensions
    ;
    mov     eax, cr4
    or      eax, CR4_OSFXSR + CR4_DE + CR4_SMXE
    mov     cr4, eax

    ;
    ; Disable cache
    ;
    mov     eax, cr0                ; set CR0:CD and CR0:NE, clear CR0:NW
    or      eax, CR0_CD_MASK | CR0_NE_MASK
    and     eax, ~CR0_NW_MASK
    mov     cr0, eax

    ;
    ; Check to see how we should invalidate the cache
    ;
    MOVDOUT2
    cmp     eax, TXT_FN_SCLEAN      ; have we been called to run SCLEAN?
    je      LaunchBiosAcm_ScleanInvd
    cmp     eax, TXT_FN_CLEAR_SECRETS ; have we been called to run CLEAR_SECRETS?
    je      LaunchBiosAcm_ScleanInvd
    cmp     eax, TXT_FN_ACHECK      ; have we been called to run ACHECK?
    je      LaunchBiosAcm_ScleanInvd
    wbinvd                          ; Writeback is necessary
    jmp     LaunchBiosAcm_OverScleanInvd

LaunchBiosAcm_ScleanInvd:
    invd                            ; SCLEAN or ACHECK. Invalidate the cache.

LaunchBiosAcm_OverScleanInvd:

    ;
    ; Disable MTRRs, set Default Type to UC
    ;
    mov     ecx, IA32_MTRR_DEF_TYPE
    xor     eax, eax
    xor     edx, edx
    wrmsr

    ;
    ; Clear all of the Variable MTRRs
    ;
    mov     ecx, IA32_MTRR_CAP
    rdmsr
    and     eax, 0xFF
    shl     eax, 1
    mov     ecx, eax
    xor     eax, eax
    xor     edx, edx
LaunchBiosAcm_ClearMtrrContinue:
    add     ecx, IA32_MTRR_PHYSBASE0 - 1
    wrmsr
    sub     ecx, IA32_MTRR_PHYSBASE0 - 1
    loop    LaunchBiosAcm_ClearMtrrContinue

    ;
    ; Determine size of AC module
    ;
    MOVDOUT0                        ; eax = AcmBase
    mov     esi, eax                ; esi = AcmBase
    mov     eax, [esi+ACMOD_SIZE]   ; eax = size of ACM
    shl     eax, 2                  ;  ...in bytes (ACM header has size in dwords)

    ;
    ; Round up to page size
    ;
    mov     ecx, eax                ; Save
    and     ecx, 0xFFFFF000         ; Number of pages in AC module
    and     eax, 0xFFF              ; Number of "less-than-page" bytes
    jz      LaunchBiosAcm_rounded_2
    mov     eax, 0x1000             ; Add the whole page size

LaunchBiosAcm_rounded_2:
    add     eax, ecx                ; rax = rounded up AC module size
    mov     ebx, eax                ; rbx = rounded up AC module size

    ;
    ; Program MTRRs to cover BIOS ACM
    ;
    xor     ecx, ecx
    movd    NEXT_MTRR_INDEX, ecx    ; Start from MTRR0

    ;
    ; Save remaining size to cache
    ;
    movd    ACM_SIZE_TO_CACHE, eax  ; Size of ACM that must be cached
    movd    ACM_BASE_TO_CACHE, esi  ; Base ACM address

LaunchBiosAcm_nextMtrr_2:
    ;
    ; Get remaining size to cache
    ;
    xor     eax, eax
    movd    eax, ACM_SIZE_TO_CACHE
    and     eax, eax
    jz      LaunchBiosAcm_mtrr_done  ; If no left size - we are done
    ;
    ; Determine next size to cache.
    ; We start from bottom up. Use the following algorythm:
    ; 1. Get our own alignment. Max size we can cache equals to our alignment
    ; 2. Determine what is bigger - alignment or remaining size to cache.
    ;    If aligment is bigger - cache it.
    ;      Adjust remaing size to cache and base address
    ;      Loop to 1.
    ;    If remaining size to cache is bigger
    ;      Determine the biggest 2^N part of it and cache it.
    ;      Adjust remaing size to cache and base address
    ;      Loop to 1.
    ; 3. End when there is no left size to cache or no left MTRRs
    ;
    xor     esi, esi
    movd    esi, ACM_BASE_TO_CACHE
    bsf     ecx, esi                ; Get index of lowest bit set in base address
    ;
    ; Convert index into size to be cached by next MTRR
    ;
    mov     edx, 0x1
    shl     edx, cl                 ; Alignment is in edx
    cmp     edx, eax                ; What is bigger, alignment or remaining size?
    jbe     LaunchBiosAcm_gotSize_2               ; JIf aligment is less
    ;
    ; Remaining size is bigger. Get the biggest part of it, 2^N in size
    ;
    bsr     ecx, eax                ; Get index of highest set bit
    ;
    ; Convert index into size to be cached by next MTRR
    ;
    mov     edx, 1
    shl     edx, cl                 ; Size to cache

LaunchBiosAcm_gotSize_2:
    mov     eax, edx
    movd    NEXT_MTRR_SIZE, eax     ; Save

    ;
    ; Compute MTRR mask value:  Mask = NOT (Size - 1)
    ;
    dec     eax                     ; eax - size to cache less one byte
    not     eax                     ; eax contains low 32 bits of mask
    or      eax, MTRR_VALID         ; Set valid bit

    ;
    ; Program mask register
    ;
    mov     ecx, IA32_MTRR_PHYSMASK0  ; setup variable mtrr
    xor     ebx, ebx
    movd    ebx, NEXT_MTRR_INDEX
    add     ecx, ebx
    movd    edx, MTRR_PHYS_MASK_HIGH   ; edx <- MTRR_PHYS_MASK_HIGH
    wrmsr
    ;
    ; Program base register
    ;
    xor     edx, edx
    mov     ecx, IA32_MTRR_PHYSBASE0  ; setup variable mtrr
    add     ecx, ebx                ; ebx is still NEXT_MTRR_INDEX

    xor     eax, eax
    movd    eax, ACM_BASE_TO_CACHE
    or      eax, WB                 ; set type to write back
    wrmsr
    ;
    ; Advance and loop
    ; Reduce remaining size to cache
    ;
    movd    ebx, ACM_SIZE_TO_CACHE
    movd    eax, NEXT_MTRR_SIZE
    sub     ebx, eax
    movd    ACM_SIZE_TO_CACHE, ebx

    ;
    ; Increment MTRR index
    ;
    movd    ebx, NEXT_MTRR_INDEX
    add     ebx, 2
    movd    NEXT_MTRR_INDEX, ebx
    ;
    ; Increment base address to cache
    ;
    movd    ebx, ACM_BASE_TO_CACHE
    movd    eax, NEXT_MTRR_SIZE
    add     ebx, eax
    movd    ACM_BASE_TO_CACHE, ebx

    jmp     LaunchBiosAcm_nextMtrr_2

LaunchBiosAcm_mtrr_done:
    ;
    ; Re-enable Variable MTRRs
    ;
    xor     edx, edx
    mov     eax, MTRR_ENABLE        ; enable mtrrs (but not fixed ones)
    mov     ecx, IA32_MTRR_DEF_TYPE
    wrmsr

    ;
    ; Re-enable cache
    ;
    mov     eax, cr0                ; Enable caching - WB (NW stays clear)
    and     eax, ~CR0_CD_MASK
    mov     cr0, eax

    ;
    ; Clean all MCi_STATUS MSR registers
    ; SCLEAN will generate GPF otherwise
    ;
    ;mov    ecx, MCG_CAP
    ;rdmsr
    mov     al, 5                   ; skl only supports clear mc0-4 early PEI phase
    movzx   ebx, al                 ; ebx = MCR bank count
    xor     eax, eax                ; Write 0 into all MCi_STATUS registers
    xor     edx, edx
    mov     ecx, MC0_STATUS

LaunchBiosAcm_McaErrorCleanLoopStart:
    wrmsr
    dec     ebx
    jz      LaunchBiosAcm_CallGetsec
    add     ecx, 4                  ; Number of MSRs per bank
    jmp     LaunchBiosAcm_McaErrorCleanLoopStart

LaunchBiosAcm_CallGetsec:
    ;
    ; Call GETSEC[ENTERACCS]
    ;
    MOVDOUT2                        ; eax = ACM function
    mov     esi, eax                ; esi = ACM function
    MOVDOUT0                        ; eax = AcmBase
    mov     ebx, eax                ; ebx = AcmBase
    mov     ecx, DWORD [ebx+ACMOD_SIZE]  ; ecx = size of ACM in dwords
    shl     ecx, 2                  ; ecx = size of ACM in bytes
    xor     edx, edx
    xor     edi, edi
    mov     eax, ENTERACCS          ; eax = ENTERACCS
    _GETSEC

    ;
    ; Return point after ACEXIT.
    ;

    ;
    ; Check if we need to restore BIOS state and configuration
    ;
    MOVDOUT2
    cmp     eax, TXT_FN_SCLEAN      ; Have we been called to run SCLEAN?
    je      ResetSystem             ; No-need to restore state, because system will reset.
    cmp     eax, TXT_FN_CLEAR_SECRETS ; Have we been called to run CLEAR_SECRETS?
    je      ResetSystem             ; No-need to restore state, because system will reset.
    cmp     eax, TXT_FN_ACHECK      ; Have we been called to run ACHECK?
    je      ResetSystem             ; No-need to restore state, because system will reset.

    ;
    ; Reload the GDTR
    ;
    MOVDOUT3                        ; eax = the address of our local variable
    lgdt    [eax]

    ;
    ; Restore the stack
    ;
    MOVDOUT4
    mov     ebp, eax                ; restore ebp
    MOVDOUT7
    mov     esp, eax                ; restore esp
    MOVDOUT5
    mov     ss, ax                  ; restore ss

    ;
    ; Reload cs register
    ;
    retf
LaunchBiosAcm_ReloadCS:

    ;
    ; Restore the rest of the segment registers
    ;
    pop     eax
    mov     ds, ax
    pop     eax
    mov     es, ax
    pop     eax
    mov     fs, ax
    pop     eax
    mov     gs, ax

;-----------------------------------------------------------------------------
;
;  Section:  Restore MTRRs
;
;  Description:  BIOS MTRR values are restored.
;
;-----------------------------------------------------------------------------
    ;
    ; Clear out the cache
    ;
    mov     eax, cr0                ; Set CR0:CD and CR0:NE, clear CR0:NW
    or      eax, CR0_CD_MASK | CR0_NE_MASK
    and     eax, ~CR0_NW_MASK
    mov     cr0, eax
    wbinvd                          ; Flush and invalidate the cache

    ;
    ; Restore def MTRR type
    ;
    mov     ecx, IA32_MTRR_DEF_TYPE
    pop     edx
    pop     eax
    wrmsr

    ;
    ; Reset Variable MTRRs to Pre-GETSEC state
    ;
    mov     ecx, IA32_MTRR_CAP
    rdmsr
    and     eax, 0xFF
    shl     eax, 1
    mov     ecx, eax
    mov     ebx, eax
    shl     ebx, 3                  ; ebx = the total length for MTRR register
    add     esp, ebx                ; adjust esp to skip MTRR register
    mov     ebx, esp
    sub     ebx, 4                  ; let ebx point to head of MTRR register now

LaunchBiosAcm_RestoreNextMtrr:
    add     ecx, IA32_MTRR_PHYSBASE0 - 1
    mov     edx, [ebx]
    mov     eax, [ebx - 4]
    wrmsr
    sub     ecx, IA32_MTRR_PHYSBASE0 - 1
    sub     ebx, 8
    loop    LaunchBiosAcm_RestoreNextMtrr

    ;
    ; Restore MISC ENABLE MSR
    ;
    pop     edx
    pop     eax
    mov     ecx, IA32_MISC_ENABLE
    wrmsr

;-----------------------------------------------------------------------------
;
;  Section:      Restore registers, stack and exit.
;
;  Description:  Previously saved registers are restored. Stack is restored
;                by execution leave instruction and control is returned to
;                caller.
;
;         NOTE!
;         This section ends differences between programmed and executed code.
;
;-----------------------------------------------------------------------------
    ;
    ; Restore control registers
    ;
    pop     eax
    mov     cr0, eax
    pop     eax
    mov     cr4, eax

    wbinvd                          ; Flush and invalidate the cache

LaunchBiosAcm_SkipLaunch:
    popad
    popf

    _EMMS

    leave
    ret 0


;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Restore Mtrr Programming
;    Function is executed on BSP in memory present environment on S3
;    resume path. Restores contents of all MTRRs from table
;
;  @param[in]   ApMtrrTab    pointer to save area
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global ASM_PFX(RestoreMtrrProgramming)
ASM_PFX(RestoreMtrrProgramming):
    ret
