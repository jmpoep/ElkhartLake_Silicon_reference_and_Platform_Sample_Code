;; @file
;  This is the code that goes from real-mode to protected mode.
;  it consumes the reset vector.
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 1999 - 2019 Intel Corporation.
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
;  This file contains a 'Sample Driver' and is licensed as such under the terms
;  of your license agreement with Intel or your vendor. This file may be modified
;  by the user, subject to the additional terms of the license agreement.
;
;@par Specification Reference:
;
;;


%include "PlatformNasm.inc"
%include "ChipsetNasm.inc"
%include "SecCoreNasm.inc"

#ifndef FSP_FLAG
extern   ASM_PFX(SecStartup)
#endif
extern   ASM_PFX(SecSaInit)

extern   ASM_PFX(PcdGet32 (PcdTemporaryRamBase))
extern   ASM_PFX(PcdGet32 (PcdTemporaryRamSize))
#ifndef FSP_FLAG
extern   ASM_PFX(PcdGet64 (PcdPciExpressBaseAddress))
#endif
extern   ASM_PFX(PcdGet64 (PcdMchBaseAddress))
extern   ASM_PFX(PcdGet32 (PcdFlashMicrocodeFvBase))
extern   ASM_PFX(PcdGet32 (PcdFlashMicrocodeFvSize))

extern   ASM_PFX(SearchAndLoadMicrocode)
extern   ASM_PFX(SecCarInit)

extern   ASM_PFX(PcdGet32 (PcdFlashFvPreMemoryBase))

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

SECTION .text

;_TEXT_REALMODE      SEGMENT PARA PUBLIC USE16 'CODE'
;                   ASSUME  CS:_TEXT_REALMODE, DS:_TEXT_REALMODE
global ASM_PFX(_TEXT_REALMODE)
ASM_PFX(_TEXT_REALMODE):
;------------------------------------------------------------------------------
;
;  SEC "Security" Code module.
;
;  Transition to non-paged flat-model protected mode from a
;  hard-coded GDT that provides exactly two descriptors.
;  This is a bare bones transition to protected mode only
;  used for while in PEI and possibly DXE.
;
;  IA32 specific cache as RAM modules
;
;  After enabling protected mode, a far jump is executed to
;  TransferToPEI using the newly loaded GDT.
;  This code also enables the Cache-as-RAM
;
;  RETURNS:    none
;
;  MMX Usage:
;              MM0 = BIST State
;              MM3 = Patch Revision
;              MM4 = Patch Pointer
;              MM5 = Save time-stamp counter value high32bit
;              MM6 = Save time-stamp counter value low32bit.
;              MM7 = Used in CALL_MMX & RET_ESI macro
;
;------------------------------------------------------------------------------

; Reset Boot Flow Start
#ifndef FSP_FLAG
global ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
BITS    16
  ;
  ; Save BIST state in MM0
  ;
  fninit                                ; clear any pending Floating point exceptions
  movd    mm0, eax

  ;
  ; Save time-stamp counter value
  ; rdtsc load 64bit time-stamp counter to EDX:EAX
  ;
  rdtsc
  movd    mm5, edx
  movd    mm6, eax

  ;
  ; Check INIT# is asserted by port 0xCF9
  ;
  mov dx, 0CF9h
  in  al, dx
  cmp al, 04h
  jnz NotWarmStart

  ;
  ; @note Issue warm reset, since if CPU only reset is issued not all MSRs are restored to their defaults
  ;
  mov dx, 0CF9h
  mov al, 06h
  out dx, al

NotWarmStart:

  ;
  ; Enter Protected mode.
  ;
  STATUS_CODE (01h)                     ; BSP_PROTECTED_MODE_START
  mov     esi,   GdtDesc
  DB      66h
  lgdt   [cs:si]     ;fword
  mov     eax, cr0                      ; Get control register 0
  or      eax, 00000003h                ; Set PE bit (bit #0) & MP bit (bit #1)
  mov     cr0, eax                      ; Activate protected mode
  mov     eax, cr4                      ; Get control register 4
  or      eax, 00000600h                ; Set OSFXSR bit (bit #9) & OSXMMEXCPT bit (bit #10)
  mov     cr4, eax

  ;
  ; Now we're in Protected16
  ; Set up the selectors for protected mode entry
  ;
  mov     ax, SYS_DATA_SEL
  mov     ds, ax
  mov     es, ax
  mov     fs, ax
  mov     gs, ax
  mov     ss, ax

  ;
  ; Go to Protected32
  ;
  mov     esi, ASM_PFX(NemInitLinearAddress)
  jmp     far dword [cs:si]

TightLoop:
  cli
  hlt
  jmp     TightLoop
#endif

;_TEXT_PROTECTED_MODE      SEGMENT PARA PUBLIC USE32 'CODE'
;                          ASSUME  CS:_TEXT_PROTECTED_MODE, DS:_TEXT_PROTECTED_MODE
global ASM_PFX(_TEXT_PROTECTED_MODE)
ASM_PFX(_TEXT_PROTECTED_MODE):

;
;args 1:ReturnAddress 2: MmxRegister
;
#ifdef FSP_FLAG
%macro LOAD_MMX_EXT  2
  mov     esi, %1
  movd    %2, esi              ; save ReturnAddress into MM7
%endmacro


;
;args 1:RoutineLabel 2:MmxRegister
;
%macro CALL_MMX_EXT    2
  mov     esi,  %%ReturnAddress
  movd    %2, esi              ; save ReturnAddress into MM7
  jmp     %1
%%ReturnAddress:
%endmacro

;
;args 1:MmxRegister
;
%macro RET_ESI_EXT 1
  movd    esi, %1              ; restore ESP from MM7
  jmp     esi
%endmacro
#endif; FSP_FLAG


;
;args 1:RoutineLabel
;
%macro CALL_MMX 1

  mov     esi,  %%ReturnAddress
  movd    mm7, esi                      ; save ReturnAddress into MM7
  jmp     %1
%%ReturnAddress:

%endmacro


;
;args none
;
%macro RET_ESI 0

  movd    esi, mm7                      ; restore ESP from MM7
  jmp     esi

%endmacro


;
;args 1:RoutineLabel
;
%macro CALL_EBP  1

  mov     ebp,  %%ReturnAddress
  jmp     %1
%%ReturnAddress:

%endmacro


;
;args none
;
%macro RET_EBP  0

  jmp     ebp                           ; restore ESP from EBP

%endmacro

align 4
#ifndef FSP_FLAG
DD PROTECTED_MODE_ENTRY_GUID1
DD PROTECTED_MODE_ENTRY_GUID2
DD PROTECTED_MODE_ENTRY_GUID3
DD PROTECTED_MODE_ENTRY_GUID4
#endif
global ASM_PFX(ProtectedModeSecStart)
ASM_PFX(ProtectedModeSecStart):
BITS    32
#ifndef FSP_FLAG
#if FixedPcdGetBool(PcdBfxEnable) == 1
  ;
  ; For UFS boot, BIOS has to reload the GDT back what it has and switch to long mode
  ;
  xor  ebx, ebx
  mov  ebx, DWORD [ds:(TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h)]
  and  ebx, BLOCK_BOOT_ENABLED
  cmp  ebx, UFS_BOOT_ENABLED
  jne  SkipGdtLoad
  ;
  ; Save BIST state in MM0
  ;
  movd   mm0, eax
  ;
  ; Load GdtDesc offset in the gdt register
  ;
  mov   esi, GdtDesc
  lgdt [cs:esi]

  mov   esi, ASM_PFX(ReloadGdtFarJumpAddress)
  jmp   far [cs:esi]

global ASM_PFX(ReloadGdtFarJumpStart)
ASM_PFX(ReloadGdtFarJumpStart):

  mov   ax, SYS_DATA_SEL
  mov   ds, ax
  mov   es, ax
  mov   fs, ax
  mov   gs, ax
  mov   ss, ax

SkipGdtLoad:
#endif
  STATUS_CODE (02h)
  CALL_MMX  ASM_PFX(EarlyMicrocodeUpdate)

  STATUS_CODE (03h)
  CALL_MMX  ASM_PFX(SecPlatformInit)

  STATUS_CODE (04h)
  CALL_MMX  ASM_PFX(SecCarInit)

  STATUS_CODE (05h)
  CALL_MMX  ASM_PFX(EstablishStack)

  STATUS_CODE (06h)
  jmp  ASM_PFX(CallPeiCoreEntryPoint)
#endif ;FSP_FLAG

;
; Perform early platform initialization
;

global ASM_PFX(SecPlatformInit)
ASM_PFX(SecPlatformInit):

  CALL_EBP  ASM_PFX(SecSaInit)

  ;
  ; Enable HPET decode in PCH.
  ;
#ifdef FSP_FLAG
  ;
  ; Read PCI Express base address
  ;
  mov     eax,  PCIEX_BAR_REG
  mov     dx,   0CF8h
  out     dx,   eax
  mov     dx,   0CFCh
  in      eax,  dx
  and     eax,  0xFC000000
  mov     esi,  eax
#else
  mov     esi, DWORD  [ASM_PFX(PcdGet64(PcdPciExpressBaseAddress))]
#endif
  add     esi, PCH_HPET_REG
  mov     al,  PCH_HPET_AE
  mov     Byte  [esi], al
  mov     al,  Byte [esi]                     ; read back
  xor     eax, eax
  mov     esi, HPET_COMP_1
  mov     Dword [esi], eax
  mov     esi, HPET_COMP_2
  mov     Dword  [esi], eax
  RET_ESI


;
; Establish Stack
;

global ASM_PFX(EstablishStack)
ASM_PFX(EstablishStack):
  ;
  ; Enable STACK
  ;
  RET_ESI


;
; This is the entry point to PEI phase
;

global ASM_PFX(CallPeiCoreEntryPoint)
ASM_PFX(CallPeiCoreEntryPoint):
  ;
  ; Set stack top pointer
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  esp
  GET_TEMP_RAM_SIZE  ecx
  add     esp, ecx;
#else
  mov     esp, DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
  add     esp, DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif

  ;
  ; Push CPU count to stack first, then AP's (if there is one)
  ; BIST status, and then BSP's
  ;
  mov     ch, 01 ; for client we have only one BSP
  movzx   ecx, ch

  ; Save number of BSPs
  push  ecx

GetSbspBist:
  ; Save SBSP BIST
  movd  eax, mm0
  push  eax

  ; Save SBSP APIC ID
  movd  eax, mm1
  shr   eax, BspApicIdSaveStart               ; Resume APIC ID
  push  eax

  ; Save Time-Stamp Counter
  movd eax, mm5
  push eax

  movd eax, mm6
  push eax

TransferToSecStartup:

  ; Switch to "C" code
  STATUS_CODE (0Ch)

  ;
  ; SecStartup () in UefiCpuPkg/SecCore/SecMain.c
  ; requires only 3 parameters.
  ;

  ;
  ; Pass BFV (*BootFirmwareVolume) into the PEI Core
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  mov     edi, DWORD [ASM_PFX(PcdGet32 (PcdFlashFvPreMemoryBase))]
  push    edi
#else
  mov     edi, FV_MAIN_BASE             ; 0FFFFFFFCh
  push    DWORD  [ds:edi]
#endif

#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE  edi
  push     edi
#else
  push    DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamBase))]
#endif

  ;
  ; Pass stack base (TempRamBase) into the PEI Core
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_SIZE  edi
  push     edi
#else
  push    DWORD [ASM_PFX(PcdGet32 (PcdTemporaryRamSize))]
#endif
  ;
  ; Pass Control into the PEI Core
  ;
#ifndef FSP_FLAG
  call ASM_PFX(SecStartup)
#endif

;
; Load MCU path, if not already loaded from FIT table
;

global ASM_PFX(EarlyMicrocodeUpdate)
ASM_PFX(EarlyMicrocodeUpdate):
    mov     esi, DWORD [ASM_PFX(PcdGet32 (PcdFlashMicrocodeFvBase))]
    movzx   ebx, WORD  [esi + FVHEADER_LEN_OFF]
    add     esi, ebx
    add     esi,  FFSHEADER_LEN ; add FFS header

    mov     edi, DWORD [ASM_PFX(PcdGet32 (PcdFlashMicrocodeFvBase))]
    mov     ebx, DWORD [ASM_PFX(PcdGet32 (PcdFlashMicrocodeFvSize))]
    add     edi, ebx                    ; End addr of uCodes.

    CALL_EBP  ASM_PFX(SearchAndLoadMicrocode)

    RET_ESI

align 16

;
; GDT[0]: 0x00: Null entry, never used.
;
NULL_SEL        EQU $ - GDT_BASE        ; Selector [0]
GDT_BASE:
BootGdtTable        DD  0
                    DD  0
;
; Linear data segment descriptor
;
LINEAR_SEL      EQU $ - GDT_BASE        ; Selector [0x8]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  092h                            ; present, ring 0, data, expand-up, writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; Linear code segment descriptor
;
LINEAR_CODE_SEL EQU $ - GDT_BASE        ; Selector [0x10]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  09Bh                            ; present, ring 0, data, expand-up, not-writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; System data segment descriptor
;
SYS_DATA_SEL    EQU $ - GDT_BASE        ; Selector [0x18]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  093h                            ; present, ring 0, data, expand-up, not-writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0

;
; System code segment descriptor
;
SYS_CODE_SEL    EQU $ - GDT_BASE        ; Selector [0x20]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  09Ah                            ; present, ring 0, data, expand-up, writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; Spare segment descriptor
;
SYS16_CODE_SEL  EQU $ - GDT_BASE        ; Selector [0x28]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0Eh                             ; Changed from F000 to E000.
    DB  09Bh                            ; present, ring 0, code, expand-up, writable
    DB  00h                             ; byte-granular, 16-bit
    DB  0
;
; Spare segment descriptor
;
SYS16_DATA_SEL  EQU $ - GDT_BASE        ; Selector [0x30]
    DW  0FFFFh                          ; limit 0xFFFF
    DW  0                               ; base 0
    DB  0
    DB  093h                            ; present, ring 0, data, expand-up, not-writable
    DB  00h                             ; byte-granular, 16-bit
    DB  0

;
; Spare segment descriptor
;
SPARE5_SEL      EQU $ - GDT_BASE        ; Selector [0x38]
    DW  0                               ; limit 0
    DW  0                               ; base 0
    DB  0
    DB  0                               ; present, ring 0, data, expand-up, writable
    DB  0                               ; page-granular, 32-bit
    DB  0
GDT_SIZE        EQU $ - BootGdtTable    ; Size, in bytes

GdtDesc:                                ; GDT descriptor
    DW  GDT_SIZE - 1                    ; GDT limit
    DD  BootGdtTable                    ; GDT base address

ASM_PFX(NemInitLinearAddress):
NemInitLinearOffset:
    DD  ASM_PFX(ProtectedModeSecStart)  ; Offset of our 32 bit code
    DW  LINEAR_CODE_SEL

#ifndef FSP_FLAG
#if FixedPcdGetBool(PcdBfxEnable) == 1
ASM_PFX(ReloadGdtFarJumpAddress):
ReloadGdtFarJumpOffset:
    DD  ASM_PFX(ReloadGdtFarJumpStart)  ; Offset of our 32 bit code
    DW  LINEAR_CODE_SEL
#endif
#endif
