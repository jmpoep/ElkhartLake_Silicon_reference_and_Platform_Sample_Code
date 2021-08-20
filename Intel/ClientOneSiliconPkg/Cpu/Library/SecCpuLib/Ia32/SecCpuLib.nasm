;; @file
;  This file implements SEC CPU library
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2015 - 2019 Intel Corporation.
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
; @par Specification Reference:
;;


%include "SecCpuLibNasm.inc"

;
; EarlyCycleDecoding is a helper function configure cycle decoding
;
extern   ASM_PFX(EarlyCycleDecoding)
;
; SerialIoUartDebugConfiguration is a helper function to init SerialIoUart
;
extern   ASM_PFX(SerialIoUartDebugConfiguration)

#if FixedPcdGetBool(PcdBfxEnable) == 0
;
; SerialPortConfiguration is a helper function to init SerialPort
;
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
extern   ASM_PFX(SerialPortConfiguration)
#endif
#endif
;
; SerialIoSpiPostCodeConfiguration is a helper function to init SerialIoSpiController for PostCodes
;
extern   ASM_PFX(SerialIoSpiPostCodeConfiguration)

extern   ASM_PFX(PcdGet32 (PcdBiosAreaBaseAddress))
extern   ASM_PFX(PcdGet32 (PcdNemCodeCacheBase))
extern   ASM_PFX(PcdGet32 (PcdTemporaryRamBase))
extern   ASM_PFX(PcdGet32 (PcdTemporaryRamSize))

SECTION .text

;
; @todo: These structures are moved from SecCpuLibNasm.inc to avoid
;        build error, needs to be fixed later on.
;
struc UpdateHeaderStruc
  .dHeaderVersion:        resd  1  ; Header version#
  .dUpdateRevision:       resd  1  ; Update revision#
  .dDate:                 resd  1  ; Date in binary (08/13/07 as 0x08132007)
  .dProcessorSignature:   resd  1  ; CPU type, family, model, stepping
  .dChecksum:             resd  1  ; Checksum
  .dLoaderRevision:       resd  1  ; Update loader version#
  .dProcessorFlags:       resd  1  ; Processor Flags
  .dDataSize:             resd  1  ; Size of encrypted data
  .dTotalSize:            resd  1  ; Total size of update in bytes
  .dReserved:             resd  3  ; 12 bytes reserved
  .size:
endstruc

struc SecCarInitParams
  ; FSP_UPD_HEADER {
  .FspUpdHeader:          resd  8
  ; }
  ; FSPT_CORE_UPD {
  .MicrocodeCodeAddr:     resd  1
  .MicrocodeCodeSize:     resd  1
  .CodeRegionBase:        resd  1
  .CodeRegionSize:        resd  1
  ; }
  .size:
endstruc

%macro RET_ESI 0
  movd    esi, mm7                      ; restore ESP from MM7
  jmp     esi
%endmacro

%macro CALL_EBP 1
  mov     ebp, .ReturnAddress1
  jmp     %1
  .ReturnAddress1:
%endmacro

%macro RET_EBP 0
  jmp     ebp                           ; restore ESP from EBP
%endmacro

%macro GET_TEMP_RAM_BASE   1
    mov  %1, DWORD [ds:(TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h)]
    and  %1, BLOCK_BOOT_ENABLED
    cmp  %1, UFS_BOOT_ENABLED
    jne  %%SpiTempRamBase
    mov  %1, DWORD [ds:(TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS)]
    add  %1, NEM_TEMPORARY_RAM_BASE
    mov  %1, DWORD [%1]
    jmp  %%ExitTempRamBase
%%SpiTempRamBase:
    mov  %1, DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
%%ExitTempRamBase:
%endmacro

%macro GET_TEMP_RAM_SIZE   1
    mov  %1, DWORD [ds:(TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h)]
    and  %1, BLOCK_BOOT_ENABLED
    cmp  %1, UFS_BOOT_ENABLED
    jne  %%SpiTempRamSize
    mov  %1, DWORD [ds:(TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS)]
    add  %1, NEM_TEMPORARY_RAM_SIZE
    mov  %1, DWORD [%1]
    jmp  %%ExitTempRamSize
%%SpiTempRamSize:
    mov  %1, DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
%%ExitTempRamSize:
%endmacro

; Load MCU path, if not already loaded from FIT table
;
; esi = Start of Microcode
; edi = End of Microcode

global ASM_PFX(SearchAndLoadMicrocode)
ASM_PFX(SearchAndLoadMicrocode):
;
; Write 0 to MSR 08Bh and execute CPUID.(EAX = 1) before reading MSR 08Bh
;
    xor     eax, eax
    xor     edx, edx
    mov     ecx, MSR_IA32_BIOS_SIGN_ID
    wrmsr
    mov     eax, 01h
    cpuid
    mov     ecx, MSR_IA32_BIOS_SIGN_ID
    rdmsr                               ; CPU PatchID -> EDX
    cmp     edx, 0                      ; If microcode has been updated
    jnz     luExit                      ; Skip if patch already loaded

    movd    mm3, edx                    ; Reset patch revision in mm3

    mov     eax, 01h                    ; To get CPU signature.
    cpuid                               ; EAX = CPU signature.
    mov     ebx, eax                    ; preserve signature

    mov     ecx, MSR_IA32_PLATFORM_ID   ; To get Platform ID.
    rdmsr
    shr     edx, 18                     ; EDX[0-2] = Platform ID.
    and     dx, 07h                     ; DX = Platform ID.

    mov     ecx, 1
    xchg    ecx, edx
    shl     edx, cl

    mov     eax, ebx                    ; eax = signature

    ; EAX = CPU signature.
    ; EDX = Platform ID bit.
    ; ESI = Abs addr of contiguous uCode blocks.
    ; EDI = Abs addr of contiguous uCode blocks end.

luCheckPatch:
    cmp     DWORD [ds:esi + UpdateHeaderStruc.dProcessorSignature], eax
    jnz     luCheckUnprogrammed         ; No.
    test    DWORD [ds:esi + UpdateHeaderStruc.dProcessorFlags ], edx ;Platform matched?
    jnz     luFoundMatch                ; Yes.

luCheckUnprogrammed:
    mov     ebx, DWORD [ds:esi + UpdateHeaderStruc.dDataSize]
    cmp     ebx, 0FFFFFFFFh
    je      luUnprogrammed
    cmp     DWORD [ds:esi + UpdateHeaderStruc.dLoaderRevision], 1
    je      luCheckExtdHdrs

luUnprogrammed:
    mov     ebx, 1024                   ; Unprogrammed space, 1KB checks
    jmp     luPoinToNextBlock           ; for backword compatibility.

luCheckExtdHdrs:
    add     ebx, UpdateHeaderStruc.size
    cmp     ebx, DWORD [ds:esi + UpdateHeaderStruc.dTotalSize]
    jae     luTryNextPatch              ; No extd hdrs.

    mov     ecx, DWORD [ds:esi + ebx]
    jcxz    luTryNextPatch              ; No extd hdrs. (OK to use CX instead of ECX).
    add     ebx, 20                     ; Point to the first Extd Sig.
luNextSig:
    cmp     eax,  [ds:esi + ebx] ;Sig matched?
    jne     lu_00
    test    edx,  [ds:esi + ebx + 4] ;Platform matched?
    jnz     luFoundMatch
lu_00:
    add     ebx, 12
    loop    luNextSig

luTryNextPatch:
    mov     ebx, [ds:esi + UpdateHeaderStruc.dTotalSize]
    or      ebx, ebx
    jnz     luPoinToNextBlock           ; Variable size uCode format.
    mov     ebx, BLOCK_LENGTH_BYTES     ; Fixed size uCode format.

luPoinToNextBlock:
    add     esi, ebx
    cmp     esi, edi
    jb      luCheckPatch                ; Check with all patches.

    ;
    ; Check possible multiple patch
    ;
    movd    eax, mm3
    movd    esi, mm4
    or      eax, eax
    jnz     luLoadPatch
    jmp     luExit                      ; No matching patch found.

luFoundMatch:
;   MM3 = Patch Revision
;   MM4 = Patch Pointer
    movd    ebx, mm3
    cmp      [ds:esi + UpdateHeaderStruc.dUpdateRevision], ebx
    jbe     luTryNextPatch

    mov     ebx,  [ds:esi + UpdateHeaderStruc.dUpdateRevision]

luStoreRevPtr:
    movd    mm3, ebx                    ; save Patch Revision
    movd    mm4, esi                    ; save Patch Pointer
    jmp     luTryNextPatch

luLoadPatch:
    mov     ecx, MSR_IA32_BIOS_UPDT_TRIG
    mov     eax, esi                        ; EAX - Abs addr of uCode patch.
    add     eax, UpdateHeaderStruc.size     ; EAX - Abs addr of uCode data.
    xor     edx, edx                        ; EDX:EAX - Abs addr of uCode data.
    wrmsr                                   ; Trigger uCode load.

luExit:

  ;
  ; Send the patch ID to port80
  ;
  mov   ecx, MSR_IA32_BIOS_SIGN_ID
  xor   eax, eax
  xor   edx, edx
  wrmsr

  mov   eax, 1
  cpuid

  mov   ecx, MSR_IA32_BIOS_SIGN_ID
  rdmsr
  mov   eax, edx
  out   80h, eax
  RET_EBP


;-----------------------------------------------------------------------------
;
;  Section:     SecCarInit
;
;  Description: This function initializes the Cache for Data, Stack, and Code
;               as specified in the  BIOS Writer's Guide.
;
;-----------------------------------------------------------------------------
global ASM_PFX(SecCarInit)
ASM_PFX(SecCarInit):
  ;
  ; Detect Boot Guard Boot
  ;
DetectBootGuard:
  mov     ecx, MSR_BOOT_GUARD_SACM_INFO
  rdmsr
  and     eax, 01h
  jnz     BootGuardNemSetup
SkipDetectBootGuard:

  ;
  ;  Enable cache for use as stack and for caching code
  ;  Ensure that the system is in flat 32 bit protected mode.
  ;
  ;  Ensure that only one logical processor in the system is the BSP.
  ;  (Required step for clustered systems).
  ;
  ;  Ensure all APs are in the Wait for SIPI state.
  ;  This includes all other logical processors in the same physical processor
  ;  as the BSP and all logical processors in other physical processors.
  ;  If any APs are awake, the BIOS must put them back into the Wait for
  ;  SIPI state by issuing a broadcast INIT IPI to all excluding self.
  ;
  mov     edi, APIC_ICR_LO               ; 0FEE00300h - Send INIT IPI to all excluding self
  mov     eax, (ORALLBUTSELF + ORSELFINIT ); 0000C4500h - Broadcast INIT IPI
  mov     [edi], eax

SecCarInitL1:
  mov     eax, [edi]
  bt      eax, 12                       ; Check if send is in progress
  jc      SecCarInitL1                            ; Loop until idle

  ;   Ensure that all variable-range MTRR valid flags are clear and
  ;   IA32_MTRR_DEF_TYPE MSR E flag is clear.  Note: This is the default state
  ;   after hardware reset.
  ;
  ;   Initialize all fixed-range and variable-range MTRR register fields to 0.
  ;
   mov   ecx, IA32_MTRR_CAP             ; get variable MTRR support
   rdmsr
   movzx ebx, al                        ; EBX = number of variable MTRR pairs
   shl   ebx, 2                         ; *4 for Base/Mask pair and WORD size
   add   ebx, (MtrrCountFixed * 2)        ; EBX = size of  Fixed and Variable MTRRs

   xor   eax, eax                       ; Clear the low dword to write
   xor   edx, edx                       ; Clear the high dword to write

InitMtrrLoop:
   add   ebx, -2
   movzx ecx, WORD [cs:(MtrrInitTable + ebx)]  ; ecx <- address of mtrr to zero
   wrmsr
   jnz   InitMtrrLoop                   ; loop through the whole table

  ;
  ;   Configure the default memory type to un-cacheable (UC) in the
  ;   IA32_MTRR_DEF_TYPE MSR.
  ;
  mov     ecx, MTRR_DEF_TYPE            ; Load the MTRR default type index
  rdmsr
  and     eax, ~(00000CFFh)             ;Clear the enable bits and def type UC.
  wrmsr

  ; Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
  ; based on the physical address size supported for this processor
  ; This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
  ;
  ; Examples:
  ;  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
  ;  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
  ;
  mov   eax, 80000008h                  ; Address sizes leaf
  cpuid
  sub   al, 32
  movzx eax, al
  xor   esi, esi
  bts   esi, eax
  dec   esi                             ; esi <- MTRR_PHYS_MASK_HIGH

  ;
  ;   Configure the DataStack region as write-back (WB) cacheable memory type
  ;   using the variable range MTRRs.
  ;
  ;
  ; Set the base address of the DataStack cache range
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  eax
#else
  mov     eax, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
#endif
  or      eax, MTRR_MEMORY_TYPE_WB
                                        ; Load the write-back cache value
  xor     edx, edx                      ; clear upper dword
  mov     ecx, MTRR_PHYS_BASE_0         ; Load the MTRR index
  wrmsr                                 ; the value in MTRR_PHYS_BASE_0

  ;
  ; Set the mask for the DataStack cache range
  ; Compute MTRR mask value:  Mask = NOT (Size - 1)
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_SIZE  eax
#else
  mov  eax, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  dec  eax
  not  eax
  or   eax, MTRR_PHYS_MASK_VALID
                                        ; turn on the Valid flag
  mov  edx, esi                         ; edx <- MTRR_PHYS_MASK_HIGH
  mov  ecx, MTRR_PHYS_MASK_0            ; For proper addressing above 4GB
  wrmsr                                 ; the value in MTRR_PHYS_BASE_0

  ;
  ;   Configure the BIOS code region as write-protected (WP) cacheable
  ;   memory type using a single variable range MTRR.
  ;
  ;   Ensure region to cache meets MTRR requirements for
  ;   size and alignment.
  ;

  ;
  ; Calculate NEM size
  ; Determine LLC size of the code region and data region combined must not exceed the size
  ; of the (Last Level Cache - 0.5MB).
  ;
  ; Determine Cache Parameter by CPUID Function 04h
  ;
  xor     edi, edi
;

Find_LLC_parameter:
  mov     ecx, edi
  mov     eax, 4
  cpuid
  inc     edi
  and     al, 0E0h                       ; EAX[7:5] = Cache Level
  cmp     al, 60h                        ; Check to see if it is LLC
  jnz     Find_LLC_parameter
  ;
  ; Got L3 parameters
  ;
  ; This Cache Size in Bytes = (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
  ;  = (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
  ;
  mov     eax, ecx
  inc     eax
  mov     edi, ebx
  shr     ebx, 22
  inc     ebx
  mul     ebx
  mov     ebx, edi
  and     ebx, ~(0FFC00FFFh)
  shr     ebx, 12
  inc     ebx
  mul     ebx
  mov     ebx, edi
  and     ebx, 0FFFh
  inc     ebx
  mul     ebx

  ;
  ; Maximum NEM size <= (Last Level Cache - 0.5MB)
  ;
  sub     eax, (512*1024)
Got_NEM_size:
  ;
  ; Code cache size = Total NEM size - DataStack size
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  ecx
  sub     eax, ecx
#else
  sub     eax, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
;
  ;
  ; Round up to page size
  ;
  mov     ecx, eax                      ; Save
  and     ecx, 0FFFF0000h               ; Number of pages in 64K
  and     eax, 0FFFFh                   ; Number of "less-than-page" bytes
  jz      Rounded
  mov     eax, 10000h                   ; Add the whole page size

Rounded:
  add     eax, ecx                      ; eax - rounded up code cache size

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0

  ;
  ; Set the base address of the CodeRegion cache range from PCD
  ; PcdNemCodeCacheBase is set to the offset to flash base,
  ; so add PcdBiosAreaBaseAddress to get the real code base address.
  ;
  mov     edi, [ASM_PFX(PcdGet32 (PcdNemCodeCacheBase))]
  add     edi, [ASM_PFX(PcdGet32 (PcdBiosAreaBaseAddress))]

  mov     ebx, edi                      ; Check if region needed for code caching is smaller than available.
  add     ebx, eax                      ;    or sum of base needed and available cache above 4 GB.
  jnc     SecCarInitL2                            ;Check if > 4GB, or required code cache region is less than
  xor     edi, edi                      ; edi = 4GB
  sub     edi, eax                      ; Base = entire available code cache region with top at 4GB.
SecCarInitL2:

#else

  mov     ecx, dword [esp + 04h]
  cmp     ecx, 0
  jz      InvalidParameter

  mov     edi, dword [ecx + SecCarInitParams.CodeRegionBase]   ; Code region base

  mov     ecx, dword [ecx + SecCarInitParams.CodeRegionSize]   ; Code region size
  cmp     ecx,  0
  jz      InvalidParameter
  jmp     SecCarInitL3

InvalidParameter:
  mov     eax, 080000002h              ; RETURN_INVALID_PARAMETER
  jmp     SecCarInitExit
SecCarInitL3:

  ;
  ; Use LLC size if CodeRegionSize is bigger than LLC size
  ;
  cmp     ecx, eax                     ; Compare FSP requested size with available size.
  ja      CodeSizeDone                 ; If Requested is larger than available, use available and jump.
  mov     eax, ecx                     ; Use requested size.
CodeSizeDone:

#endif

  ;
  ; Save MM5 into ESP before program MTRR, because program MTRR will use MM5 as the local variable.
  ; And, ESP is not initialized before CAR is enabled. So, it is safe ot use ESP here.
  ;

  movd esp, mm5

  ;
  ; Define "local" vars for this routine
  ; @todo as these registers are overlapping with others
  ; Note that mm0 is used to store BIST result for BSP,
  ; mm1 is used to store the number of processor and BSP APIC ID,
  ; mm6 is used to save time-stamp counter value.
  ;
  %define CODE_SIZE_TO_CACHE      mm3
  %define CODE_BASE_TO_CACHE      mm4
  %define NEXT_MTRR_INDEX         mm5
  %define NEXT_MTRR_SIZE          mm2
  ;
  ; Initialize "locals"
  ;
  sub     ecx, ecx
  movd    NEXT_MTRR_INDEX, ecx          ; Count from 0 but start from MTRR_PHYS_BASE_1

  ;
  ; Save remaining size to cache
  ;
  movd    CODE_SIZE_TO_CACHE, eax       ; Size of code cache region that must be cached

  ;
  ; For non-FSP, sets the base from 4GB - code cache length, which is the non-FSP post validation code.
  ; However, for FSP, the base is from the TempRamInit API. However, if base is 0, then use 4G - code cche lengthlength.
  ;

#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  cmp     edi, 0
  jnz     SecCarInitL4
#endif

  mov     edi, 0xFFFFFFFF
  sub     edi, eax
  inc     edi
  test    edi, 0xFFFF
  jz      SecCarInitL4
  add     edi, 0x10000
  and     edi, 0xFFFF0000
SecCarInitL4:

  movd    CODE_BASE_TO_CACHE, edi       ; Base code cache address

NextMtrr:
  ;
  ; Get remaining size to cache
  ;
  movd    eax, CODE_SIZE_TO_CACHE
  and     eax, eax
  jz      CodeRegionMtrrdone            ; If no left size - we are done
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
  movd    edi, CODE_BASE_TO_CACHE
  bsf     ecx, edi                      ; Get index of lowest bit set in base address
  ;
  ; Convert index into size to be cached by next MTRR
  ;
  mov     edx, 1h
  shl     edx, cl                       ; Alignment is in edx
  cmp     edx, eax                      ; What is bigger, alignment or remaining size?
  jbe     GotSize                       ; JIf aligment is less
  ;
  ; Remaining size is bigger. Get the biggest part of it, 2^N in size
  ;
  bsr     ecx, eax                      ; Get index of highest set bit
  ;
  ; Convert index into size to be cached by next MTRR
  ;
  mov     edx, 1
  shl     edx, cl                       ; Size to cache

GotSize:
  mov     eax, edx
  movd    NEXT_MTRR_SIZE, eax           ; Save

  ;
  ; Compute MTRR mask value:  Mask = NOT (Size - 1)
  ;
  dec     eax                           ; eax - size to cache less one byte
  not     eax                           ; eax contains low 32 bits of mask
  or      eax, MTRR_PHYS_MASK_VALID     ; Set valid bit

  ;
  ; Program mask register
  ;
  mov     ecx, MTRR_PHYS_MASK_1         ; setup variable mtrr
  movd    ebx, NEXT_MTRR_INDEX
  add     ecx, ebx

  mov     edx, esi                      ; edx <- MTRR_PHYS_MASK_HIGH
  wrmsr
  ;
  ; Program base register
  ;
  sub     edx, edx
  mov     ecx, MTRR_PHYS_BASE_1         ; setup variable mtrr
  add     ecx, ebx                      ; ebx is still NEXT_MTRR_INDEX

  movd    eax, CODE_BASE_TO_CACHE
  or      eax, MTRR_MEMORY_TYPE_WP      ; set type to write protect
  wrmsr
  ;
  ; Advance and loop
  ; Reduce remaining size to cache
  ;
  movd    ebx, CODE_SIZE_TO_CACHE
  movd    eax, NEXT_MTRR_SIZE
  sub     ebx, eax
  movd    CODE_SIZE_TO_CACHE, ebx

  ;
  ; Increment MTRR index
  ;
  movd    ebx, NEXT_MTRR_INDEX
  add     ebx, 2
  movd    NEXT_MTRR_INDEX, ebx
  ;
  ; Increment base address to cache
  ;
  movd    ebx, CODE_BASE_TO_CACHE
  movd    eax, NEXT_MTRR_SIZE
  add     ebx, eax
  ;
  ; if carry happens, means NEM base + size over 4G
  ;
  jc      CodeRegionMtrrdone
  movd    CODE_BASE_TO_CACHE, ebx

  jmp     NextMtrr

CodeRegionMtrrdone:
  ;
  ; Enable the MTRRs by setting the IA32_MTRR_DEF_TYPE MSR E flag.
  ;
  mov     ecx, MTRR_DEF_TYPE            ; Load the MTRR default type index
  rdmsr
  or      eax, MTRR_DEF_TYPE_E          ; Enable variable range MTRRs
  wrmsr

  ;
  ; Enable the logical processor's (BSP) cache: execute INVD and set
  ; CR0.CD = 0, CR0.NW = 0.
  ;
  mov     eax, cr0
  and     eax, ~(CR0_CACHE_DISABLE + CR0_NO_WRITE)
  invd
  mov     cr0, eax
  ;
  ; Enable No-Eviction Mode Setup State by setting
  ; NO_EVICT_MODE  MSR 2E0h bit [0] = '1'.
  ;
  mov     ecx, NO_EVICT_MODE
  rdmsr
  or      eax, 1
  wrmsr

  ;
  ; Restore MM5 from ESP after program MTRR
  ;
  movd mm5, esp

  ;
  ; Restore MM4 which is Patch Pointer.
  ; Current implementation it's the same with the PcdNemCodeCacheBase + PcdBiosAreaBaseAddress
  ;
  mov     edi, [ASM_PFX(PcdGet32 (PcdNemCodeCacheBase))]
  add     edi, [ASM_PFX(PcdGet32 (PcdBiosAreaBaseAddress))]
  movd    mm4, edi

  ;
  ; One location in each 64-byte cache line of the DataStack region
  ; must be written to set all cache values to the modified state.
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  edi
  GET_TEMP_RAM_SIZE  ecx
#else
  mov     edi, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
  mov     ecx, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  shr     ecx, 6
  mov     eax, CACHE_INIT_VALUE
SecCarInitL5:
  mov  [edi], eax
  sfence
  add  edi, 64
  loop  SecCarInitL5, ecx

  ;
  ; Enable No-Eviction Mode Run State by setting
  ; NO_EVICT_MODE MSR 2E0h bit [1] = '1'.
  ;
  mov     ecx, NO_EVICT_MODE
  rdmsr
  or      eax, 2
  wrmsr

  jmp     FinishedCacheConfig

  ;
  ; Jump to here when Boot Guard boot and NEM is initialized by Boot Guard ACM
  ;
BootGuardNemSetup:
  ;
  ; Finished with cache configuration
  ;

  ;
  ; For UFS boot, MTRRs and NEM is already set up by ACM so Disable MTRR9 and jump to FinishedCacheConfig
  ;
  xor  eax, eax
  mov  eax, DWORD [ds:(TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h)]
  and  eax, BLOCK_BOOT_ENABLED
  cmp  eax, UFS_BOOT_ENABLED
  jne  ContinueCacheConfig

  ;
  ; Disable MTRR9
  ;
  xor     eax, eax                      ; clear lower dword
  xor     edx, edx                      ; clear upper dword
  mov     ecx, MTRR_PHYS_MASK_9         ; load the MTRR index with the value in MTRR_PHYS_MASK_9
  wrmsr

  jmp FinishedCacheConfig

ContinueCacheConfig:

  ;
  ; Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
  ; based on the physical address size supported for this processor
  ; This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
  ;
  ; Examples:
  ;  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
  ;  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
  ;
  mov   eax, 80000008h                  ; Address sizes leaf
  cpuid
  sub   al, 32
  movzx eax, al
  xor   esi, esi
  bts   esi, eax
  dec   esi                             ; esi <- MTRR_PHYS_MASK_HIGH

  ;
  ; Configure the DataStack region as write-back (WB) cacheable memory type
  ; using the variable range MTRRs.
  ;
  ;
  ; Find available MTRR
  ;
  CALL_EBP     ASM_PFX(FindFreeMtrr)

  ;
  ; Set the base address of the DataStack cache range
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  eax
#else
  mov     eax, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
#endif
  or      eax, MTRR_MEMORY_TYPE_WB
                                        ; Load the write-back cache value
  xor     edx, edx                      ; clear upper dword
  wrmsr                                 ; the value in MTRR_PHYS_BASE_0

  ;
  ; Set the mask for the DataStack cache range
  ; Compute MTRR mask value:  Mask = NOT (Size - 1)
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_SIZE  eax
#else
  mov  eax, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  dec  eax
  not  eax
  or   eax, MTRR_PHYS_MASK_VALID
                                        ; turn on the Valid flag
  mov  edx, esi                         ; edx <- MTRR_PHYS_MASK_HIGH
  inc  ecx
  wrmsr                                 ; the value in MTRR_PHYS_BASE_0

  ;
  ; One location in each 64-byte cache line of the DataStack region
  ; must be written to set all cache values to the modified state.
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  edi
  GET_TEMP_RAM_SIZE  ecx
#else
  mov     edi, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
  mov     ecx, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  shr     ecx, 6
  mov     eax, CACHE_INIT_VALUE
SecCarInitL6:
  mov  [edi], eax
  sfence
  add  edi, 64
  loop  SecCarInitL6, ecx

  ;
  ; Finished with cache configuration
  ;
FinishedCacheConfig:

  ;
  ; Optionally Test the Region
  ;

  ;
  ; Test area by writing and reading
  ;
  cld
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  edi
  GET_TEMP_RAM_SIZE  ecx
#else
  mov     edi, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
  mov     ecx, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  shr     ecx, 2
  mov     eax, CACHE_TEST_VALUE
TestDataStackArea:
  stosd
  cmp     eax, DWORD [edi-4]
  jnz     DataStackTestFail
  loop    TestDataStackArea,ecx
;
  jmp     DataStackTestPass

  ;
  ; Cache test failed
  ;
DataStackTestFail:

  STATUS_CODE (0D0h)
;
  jmp     $

  ;
  ; Configuration test failed
  ;
ConfigurationTestFailed:
  STATUS_CODE (0D1h)
  jmp     $

DataStackTestPass:

  ;
  ; At this point you may continue normal execution.  Typically this would include
  ; reserving stack, initializing the stack pointer, etc.
  ;

  ;
  ; Temporary set stack top pointer for C code usage.
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  esp
  GET_TEMP_RAM_SIZE  ecx
  add     esp, ecx
#else
  mov     esp, [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
  add     esp, [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  ;
  ; program resource decoding
  ;
  pushad
  call    ASM_PFX(EarlyCycleDecoding)
  popad
  pushad
  call    ASM_PFX(SerialIoUartDebugConfiguration)
  popad
#if FixedPcdGetBool(PcdBfxEnable) == 0
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  pushad
  call    ASM_PFX(SerialPortConfiguration)
  popad
#endif
#endif
  pushad
  call    ASM_PFX(SerialIoSpiPostCodeConfiguration)
  popad

;
  ;
  ; After memory initialization is complete, please follow the algorithm in the BIOS
  ; Writer's Guide to properly transition to a normal system configuration.
  ; The algorithm covers the required sequence to properly exit this mode.
  ;
  xor    eax, eax

SecCarInitExit:

  RET_ESI


;
; Find available MTRRs
;
global ASM_PFX(FindFreeMtrr)
ASM_PFX(FindFreeMtrr):
  mov    ecx, MTRR_PHYS_MASK_0

L8:
  rdmsr
  test   eax, 800h
  jz     FoundFreeMtrr
  add    ecx, 2
  cmp    ecx, MTRR_PHYS_MASK_9
  jbe    L8
  ;
  ; No available MTRR, halt system
  ;
  jmp    $

FoundFreeMtrr:
  dec    ecx

  RET_EBP

MtrrInitTable:
    DW  MTRR_DEF_TYPE
    DW  MTRR_FIX_64K_00000
    DW  MTRR_FIX_16K_80000
    DW  MTRR_FIX_16K_A0000
    DW  MTRR_FIX_4K_C0000
    DW  MTRR_FIX_4K_C8000
    DW  MTRR_FIX_4K_D0000
    DW  MTRR_FIX_4K_D8000
    DW  MTRR_FIX_4K_E0000
    DW  MTRR_FIX_4K_E8000
    DW  MTRR_FIX_4K_F0000
    DW  MTRR_FIX_4K_F8000

MtrrCountFixed EQU (($ - MtrrInitTable) / 2)

    DW  MTRR_PHYS_BASE_0
    DW  MTRR_PHYS_MASK_0
    DW  MTRR_PHYS_BASE_1
    DW  MTRR_PHYS_MASK_1
    DW  MTRR_PHYS_BASE_2
    DW  MTRR_PHYS_MASK_2
    DW  MTRR_PHYS_BASE_3
    DW  MTRR_PHYS_MASK_3
    DW  MTRR_PHYS_BASE_4
    DW  MTRR_PHYS_MASK_4
    DW  MTRR_PHYS_BASE_5
    DW  MTRR_PHYS_MASK_5
    DW  MTRR_PHYS_BASE_6
    DW  MTRR_PHYS_MASK_6
    DW  MTRR_PHYS_BASE_7
    DW  MTRR_PHYS_MASK_7
    DW  MTRR_PHYS_BASE_8
    DW  MTRR_PHYS_MASK_8
    DW  MTRR_PHYS_BASE_9
    DW  MTRR_PHYS_MASK_9
MtrrCount      EQU (($ - MtrrInitTable) / 2)



