;; @file
;  This is the code that goes from real-mode to protected mode.
;  it consumes the reset vector.
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 1999 - 2017 Intel Corporation.
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

  INCLUDE Platform.inc
  INCLUDE Chipset.inc
  INCLUDE SecCore.inc

.686p
.xmm
.model small, c

IFNDEF FSP_FLAG
EXTRN   SecStartup:NEAR
ENDIF
EXTRN   SecSaInit:NEAR

EXTRN   PcdGet32 (PcdTemporaryRamBase):DWORD
EXTRN   PcdGet32 (PcdTemporaryRamSize):DWORD
IFNDEF FSP_FLAG
EXTRN   PcdGet64 (PcdPciExpressBaseAddress):QWORD
ENDIF
EXTRN   PcdGet64 (PcdMchBaseAddress):QWORD
EXTRN   PcdGet32 (PcdFlashMicrocodeFvBase):DWORD
EXTRN   PcdGet32 (PcdFlashMicrocodeFvSize):DWORD

EXTERN   SearchAndLoadMicrocode:NEAR
EXTERN   SecCarInit:NEAR

GET_TEMP_RAM_BASE MACRO   TempRamBase
    mov  eax, DWORD PTR ds:[TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h]
    and  eax, BLOCK_BOOT_ENABLED
    cmp  eax, UFS_BOOT_ENABLED
    jne  SpiTempRamBase
    mov  eax, DWORD PTR ds:[TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS]
    add  eax, NEM_TEMPORARY_RAM_BASE
    mov  TempRamBase, DWORD PTR ds:[eax]
    jmp  ExitTempRamBase
SpiTempRamBase:
    mov  TempRamBase, PcdGet32 (PcdTemporaryRamBase)
ExitTempRamBase:
ENDM

GET_TEMP_RAM_SIZE MACRO   TempRamSize
    mov  eax, DWORD PTR ds:[TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h]
    and  eax, BLOCK_BOOT_ENABLED
    cmp  eax, UFS_BOOT_ENABLED
    jne  SpiTempRamSize
    mov  eax, DWORD PTR ds:[TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS]
    add  eax, NEM_TEMPORARY_RAM_SIZE
    mov  TempRamSize, DWORD PTR ds:[eax]
    jmp  ExitTempRamSize
SpiTempRamSize:
    mov  eax, PcdGet32 (PcdTemporaryRamSize)
ExitTempRamSize:
ENDM

_TEXT_REALMODE      SEGMENT PARA PUBLIC USE16 'CODE'
                    ASSUME  CS:_TEXT_REALMODE, DS:_TEXT_REALMODE

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
IFNDEF FSP_FLAG
align 4
_ModuleEntryPoint PROC NEAR C PUBLIC
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
  mov     esi,  OFFSET GdtDesc
  DB      66h
  lgdt    fword ptr cs:[si]
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
  mov     esi, offset NemInitLinearAddress
  jmp     fword ptr cs:[si]

TightLoop:
  cli
  hlt
  jmp     TightLoop

_ModuleEntryPoint ENDP
ENDIF
_TEXT_REALMODE      ENDS

_TEXT_PROTECTED_MODE      SEGMENT PARA PUBLIC USE32 'CODE'
                          ASSUME  CS:_TEXT_PROTECTED_MODE, DS:_TEXT_PROTECTED_MODE

IFDEF FSP_FLAG
LOAD_MMX_EXT MACRO   ReturnAddress, MmxRegister
  mov     esi, ReturnAddress
  movd    MmxRegister, esi              ; save ReturnAddress into MM7
ENDM

CALL_MMX_EXT MACRO   RoutineLabel, MmxRegister
  local   ReturnAddress
  mov     esi, offset ReturnAddress
  movd    MmxRegister, esi              ; save ReturnAddress into MM7
  jmp     RoutineLabel
ReturnAddress:
ENDM

RET_ESI_EXT  MACRO   MmxRegister
  movd    esi, MmxRegister              ; restore ESP from MM7
  jmp     esi
ENDM
ENDIF; FSP_FLAG

CALL_MMX MACRO   RoutineLabel

  local   ReturnAddress
  mov     esi, offset ReturnAddress
  movd    mm7, esi                      ; save ReturnAddress into MM7
  jmp     RoutineLabel
ReturnAddress:

ENDM

RET_ESI  MACRO

  movd    esi, mm7                      ; restore ESP from MM7
  jmp     esi

ENDM

CALL_EBP MACRO   RoutineLabel

  local   ReturnAddress
  mov     ebp, offset ReturnAddress
  jmp     RoutineLabel
ReturnAddress:

ENDM

RET_EBP  MACRO

  jmp     ebp                           ; restore ESP from EBP

ENDM

align 4
; For BPMGEN2 IBB Entry Point
IFNDEF FSP_FLAG
DD PROTECTED_MODE_ENTRY_GUID1
DD PROTECTED_MODE_ENTRY_GUID2
DD PROTECTED_MODE_ENTRY_GUID3
DD PROTECTED_MODE_ENTRY_GUID4
ENDIF
ProtectedModeSecStart PROC NEAR PUBLIC

IFNDEF FSP_FLAG
  STATUS_CODE (02h)
  CALL_MMX  EarlyMicrocodeUpdate

  STATUS_CODE (03h)
  CALL_MMX  SecPlatformInit

  STATUS_CODE (04h)
  CALL_MMX  SecCarInit

  STATUS_CODE (05h)
  CALL_MMX  EstablishStack

  STATUS_CODE (06h)
  jmp  CallPeiCoreEntryPoint
ENDIF

ProtectedModeSecStart ENDP

;
; Perform early platform initialization
;
SecPlatformInit    PROC    NEAR    PUBLIC

  CALL_EBP  SecSaInit

  ;
  ; Enable HPET decode in PCH.
  ;
IFDEF FSP_FLAG
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
ELSE
  mov     esi,  DWORD PTR PcdGet64 (PcdPciExpressBaseAddress)
ENDIF
  add     esi, PCH_HPET_REG
  mov     al,  PCH_HPET_AE
  mov     Byte Ptr [esi], al
  mov     al,  Byte Ptr [esi]                     ; read back
  xor     eax, eax
  mov     esi, HPET_COMP_1
  mov     Dword Ptr [esi], eax
  mov     esi, HPET_COMP_2
  mov     Dword ptr [esi], eax
  RET_ESI

SecPlatformInit    ENDP

;
; Establish Stack
;
EstablishStack    PROC    NEAR    PRIVATE

  ;
  ; Enable STACK
  ;
  RET_ESI

EstablishStack    ENDP

;
; This is the entry point to PEI phase
;
CallPeiCoreEntryPoint   PROC    NEAR    PRIVATE
  ;
  ; Set stack top pointer
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE esp
  GET_TEMP_RAM_SIZE ecx
  add     esp, ecx
#else
  mov     esp, PcdGet32 (PcdTemporaryRamBase)
  add     esp, PcdGet32 (PcdTemporaryRamSize)
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
  ; Pass entry point of the PEI core
  ;
  mov     edi, PEI_CORE_ENTRY_BASE      ; 0FFFFFFE0h
  push    DWORD PTR ds:[edi]

  ;
  ; Pass BFV into the PEI Core
  ;
  mov     edi, FV_MAIN_BASE             ; 0FFFFFFFCh
  push    DWORD PTR ds:[edi]

  ; @todo ECPoverride: SecStartup entry point needs 4 parameters
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_BASE eax
  push    eax
#else
  push    PcdGet32 (PcdTemporaryRamBase)
#endif

  ;
  ; Pass stack size into the PEI Core
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  GET_TEMP_RAM_SIZE eax
  push    eax
#else
  push    PcdGet32 (PcdTemporaryRamSize)
#endif

  ;
  ; Pass Control into the PEI Core
  ;
IFNDEF FSP_FLAG
  call SecStartup
ENDIF
CallPeiCoreEntryPoint   ENDP

;
; Load MCU path, if not already loaded from FIT table
;
EarlyMicrocodeUpdate    PROC    NEAR    PUBLIC
    mov     edi, PcdGet32 (PcdFlashMicrocodeFvSize)
    or      edi, edi
    jz      @f

    add     edi, PcdGet32 (PcdFlashMicrocodeFvBase)  ; End addr of uCodes.

    mov     esi, PcdGet32 (PcdFlashMicrocodeFvBase)
    movzx   ebx, WORD PTR [esi + FVHEADER_LEN_OFF]
    add     esi, ebx
    add     esi, FFSHEADER_LEN ; add FFS header

    CALL_EBP  SearchAndLoadMicrocode
@@:
    RET_ESI
EarlyMicrocodeUpdate    ENDP

align 10h
PUBLIC  BootGdtTable

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
OffsetGDTDesc   EQU $ - _ModuleEntryPoint
    DW  GDT_SIZE - 1                    ; GDT limit
    DD  OFFSET BootGdtTable             ; GDT base address

NemInitLinearAddress   LABEL   FWORD
NemInitLinearOffset    LABEL   DWORD
    DD  OFFSET ProtectedModeSecStart    ; Offset of our 32 bit code
    DW  LINEAR_CODE_SEL

_TEXT_PROTECTED_MODE    ENDS
END
