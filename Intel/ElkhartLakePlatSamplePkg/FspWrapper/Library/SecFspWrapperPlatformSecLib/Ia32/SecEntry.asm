;; @file
; This is the code that goes from real-mode to protected mode.
; It consumes the reset vector, calls TempRamInit API from FSP binary.
;
;@copyright
; Copyright (c) 2014 - 2020, Intel Corporation. All rights reserved.<BR>
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by the
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
; This file contains a 'Sample Driver' and is licensed as such
; under the terms of your license agreement with Intel or your
; vendor. This file may be modified by the user, subject to
; the additional terms of the license agreement.
;
;@par Specification Reference:
;;

#include "Fsp.h"

.686p
.xmm
.model small, c

EXTRN   CallPeiCoreEntryPoint:NEAR
EXTRN   FsptUpdDataPtr:FAR
EXTRN   FsptUpdDataPtrFt:FAR

; Pcds
EXTRN   PcdGet32 (PcdFsptBaseAddress):DWORD
EXTRN   PcdGet32(PcdFspTemporaryRamSize):DWORD
EXTRN   PcdGet32(PcdFaultToleranceOffset):DWORD

;
; Boot Device Indicator Config Register
;
TXT_PUBLIC_BASE               EQU 0FED30000h
BOOT_GUARD_BOOTSTATUS         EQU 0A0h
BLOCK_BOOT_ENABLED            EQU (1 SHL  0)
UFS_BOOT_ENABLED              EQU 1

_TEXT_REALMODE      SEGMENT PARA PUBLIC USE16 'CODE'
                    ASSUME  CS:_TEXT_REALMODE, DS:_TEXT_REALMODE

;----------------------------------------------------------------------------
;
; Procedure:    _ModuleEntryPoint
;
; Input:        None
;
; Output:       None
;
; Destroys:     Assume all registers
;
; Description:
;
;   Transition to non-paged flat-model protected mode from a
;   hard-coded GDT that provides exactly two descriptors.
;   This is a bare bones transition to protected mode only
;   used for a while in PEI and possibly DXE.
;
;   After enabling protected mode, a far jump is executed to
;   transfer to PEI using the newly loaded GDT.
;
; Return:       None
;
;  MMX Usage:
;              MM0 = BIST State
;              MM5 = Save time-stamp counter value high32bit
;              MM6 = Save time-stamp counter value low32bit.
;
;----------------------------------------------------------------------------

align 4
_ModuleEntryPoint PROC NEAR C PUBLIC
  fninit                                ; clear any pending Floating point exceptions
  ;
  ; Store the BIST value in mm0
  ;
  movd    mm0, eax
  cli

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
  ; Save time-stamp counter value
  ; rdtsc load 64bit time-stamp counter to EDX:EAX
  ;
  rdtsc
  movd    mm5, edx
  movd    mm6, eax

  ;
  ; Load the GDT table in GdtDesc
  ;
  mov     esi,  OFFSET GdtDesc
  DB      66h
  lgdt    fword ptr cs:[si]

  ;
  ; Transition to 16 bit protected mode
  ;
  mov     eax, cr0                   ; Get control register 0
  or      eax, 00000003h             ; Set PE bit (bit #0) & MP bit (bit #1)
  mov     cr0, eax                   ; Activate protected mode

  mov     eax, cr4                   ; Get control register 4
  or      eax, 00000600h             ; Set OSFXSR bit (bit #9) & OSXMMEXCPT bit (bit #10)
  mov     cr4, eax

  ;
  ; Now we're in 16 bit protected mode
  ; Set up the selectors for 32 bit protected mode entry
  ;
  mov     ax, SYS_DATA_SEL
  mov     ds, ax
  mov     es, ax
  mov     fs, ax
  mov     gs, ax
  mov     ss, ax

  ;
  ; Transition to Flat 32 bit protected mode
  ; The jump to a far pointer causes the transition to 32 bit mode
  ;
  mov esi, offset ProtectedModeEntryLinearAddress
  jmp     fword ptr cs:[si]
TightLoop:
  cli
  hlt
  jmp     TightLoop

_ModuleEntryPoint   ENDP
_TEXT_REALMODE      ENDS

_TEXT_PROTECTED_MODE      SEGMENT PARA PUBLIC USE32 'CODE'
                          ASSUME  CS:_TEXT_PROTECTED_MODE, DS:_TEXT_PROTECTED_MODE

;----------------------------------------------------------------------------
;
; Procedure:    ProtectedModeEntryPoint
;
; Input:        None
;
; Output:       None
;
; Destroys:     Assume all registers
;
; Description:
;
; This function handles:
;   Call two basic APIs from FSP binary
;   Initializes stack with some early data (BIST, PEI entry, etc)
;
; Return:       None
;
;----------------------------------------------------------------------------

align 4
DD PROTECTED_MODE_ENTRY_POINT_GUID_DWORD1
DD PROTECTED_MODE_ENTRY_POINT_GUID_DWORD2
DD PROTECTED_MODE_ENTRY_POINT_GUID_DWORD3
DD PROTECTED_MODE_ENTRY_POINT_GUID_DWORD4
ProtectedModeEntryPoint PROC NEAR PUBLIC
#if FixedPcdGetBool(PcdBfxEnable) == 1
  ;
  ; For UFS boot, BIOS has to reload the GDT back what it has and switch to long mode
  ;
  xor  ebx, ebx
  mov  ebx, dword ptr ds:[ TXT_PUBLIC_BASE + BOOT_GUARD_BOOTSTATUS + 04h]
  and  ebx, BLOCK_BOOT_ENABLED
  cmp  ebx, UFS_BOOT_ENABLED
  jne   SkipGdtLoad
  ;
  ; Save BIST state in MM0
  ;
  movd   mm0, eax
  ;
  ; Load GdtDesc offset in the gdt register
  ;
  mov     esi,  OFFSET GdtDesc
  lgdt    fword ptr[esi]
  mov     esi, offset ReloadGdtFarJumpAddress
  jmp     fword ptr [esi]

ReloadGdtFarJumpStart::
  mov     ax, SYS_DATA_SEL
  mov     ds, ax
  mov     es, ax
  mov     fs, ax
  mov     gs, ax
  mov     ss, ax

SkipGdtLoad:
#endif
  ; Find the fsp info header
  mov  edi, PcdGet32 (PcdFsptBaseAddress)

  ; Check TopSwap bit to determine current FspT base address on ROM
  mov     eax,  8000FDDCh ; PCH Register B0:D1F:F5:RDC BIOS Control
  mov     dx,   0CF8h
  out     dx,   eax
  mov     dx,   0CFCh
  in      eax,  dx
  and     eax,  00000010h ; bit 4 TopSwap status
  jz      TopSwapBitNotSet

TopSwapBitSet:
  mov  ebx, PcdGet32 (PcdFaultToleranceOffset)
  sub  edi, ebx

TopSwapBitNotSet:
  mov  eax, dword ptr [edi + FVH_SIGINATURE_OFFSET]
  cmp  eax, FVH_SIGINATURE_VALID_VALUE
  jnz  FspHeaderNotFound

  xor  eax, eax
  mov  ax, word ptr [edi + FVH_EXTHEADER_OFFSET_OFFSET]
  cmp  ax, 0
  jnz  FspFvExtHeaderExist

  xor  eax, eax
  mov  ax, word ptr [edi + FVH_HEADER_LENGTH_OFFSET]   ; Bypass Fv Header
  add  edi, eax
  jmp  FspCheckFfsHeader

FspFvExtHeaderExist:
  add  edi, eax
  mov  eax, dword ptr [edi + FVH_EXTHEADER_SIZE_OFFSET]  ; Bypass Ext Fv Header
  add  edi, eax

  ; Round up to 8 byte alignment
  mov  eax, edi
  and  al,  07h
  jz FspCheckFfsHeader

  and  edi, 0FFFFFFF8h
  add  edi, 08h

FspCheckFfsHeader:
  ; Check the ffs guid
  mov  eax, dword ptr [edi]
  cmp  eax, FSP_HEADER_GUID_DWORD1
  jnz FspHeaderNotFound

  mov  eax, dword ptr [edi + 4]
  cmp  eax, FSP_HEADER_GUID_DWORD2
  jnz FspHeaderNotFound

  mov  eax, dword ptr [edi + 8]
  cmp  eax, FSP_HEADER_GUID_DWORD3
  jnz FspHeaderNotFound

  mov  eax, dword ptr [edi + 0Ch]
  cmp  eax, FSP_HEADER_GUID_DWORD4
  jnz FspHeaderNotFound

  add  edi, FFS_HEADER_SIZE_VALUE       ; Bypass the ffs header

  ; Check the section type as raw section
  mov  al, byte ptr [edi + SECTION_HEADER_TYPE_OFFSET]
  cmp  al, 019h
  jnz FspHeaderNotFound

  add  edi, RAW_SECTION_HEADER_SIZE_VALUE ; Bypass the section header
  jmp FspHeaderFound

FspHeaderNotFound:
  jmp  $

FspHeaderFound:
  ; Get the fsp TempRamInit Api address
  mov eax, dword ptr [edi + FSP_HEADER_IMAGEBASE_OFFSET]
  add eax, dword ptr [edi + FSP_HEADER_TEMPRAMINIT_OFFSET]

  ; If edi is less than PcdFsptBaseAddress, it means TopSwap is enabled and detected above.
  cmp edi, PcdGet32 (PcdFsptBaseAddress)
  jb SetFtTempRamInitParam ; edi is less than PcdFsptBaseAddress, set different TempRamInitParameter for fault tolerant boot.

  ; Setup the hardcode stack
  mov esp, OFFSET TempRamInitStack
  jmp CallTempRamInitApi

SetFtTempRamInitParam:
  ; Setup the hardcode stack
  mov esp, OFFSET TempRamInitStackFt

CallTempRamInitApi:
  ; Call the fsp TempRamInit Api
  jmp eax

TempRamInitDone:
  cmp eax, 8000000Eh      ;Check if EFI_NOT_FOUND returned. Error code for Microcode Update not found.
  je  CallSecFspInit      ;If microcode not found, don't hang, but continue.

  cmp eax, 0              ;Check if EFI_SUCCESS retuned.
  jnz FspApiFailed

  ;   ECX: start of range
  ;   EDX: end of range
CallSecFspInit:
#if FixedPcdGet8(PcdFspModeSelection) == 1
  sub     edx, PcdGet32 (PcdFspTemporaryRamSize) ; TemporaryRam for FSP Api mode
#endif
  xor     eax, eax
  mov     esp, edx

  ; Align the stack at DWORD
  add  esp,  3
  and  esp, 0FFFFFFFCh

  push    edx
  push    ecx
  push    eax ; zero - no hob list yet
  call    CallPeiCoreEntryPoint

FspApiFailed:
  jmp $

align 10h
TempRamInitStack:
    DD  OFFSET TempRamInitDone
    DD  OFFSET FsptUpdDataPtr ; TempRamInitParams

align 10h
TempRamInitStackFt:
    DD  OFFSET TempRamInitDone
    DD  OFFSET FsptUpdDataPtrFt ; TempRamInitParams for Fault Tolerance boot

ProtectedModeEntryPoint ENDP

;
; ROM-based Global-Descriptor Table for the Tiano PEI Phase
;
align 16
PUBLIC  BootGdtTable

;
; GDT[0]: 0x00: Null entry, never used.
;
NULL_SEL            EQU $ - GDT_BASE    ; Selector [0]
GDT_BASE:
BootGdtTable        DD  0
                    DD  0
;
; Linear data segment descriptor
;
LINEAR_SEL          EQU $ - GDT_BASE    ; Selector [0x8]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  092h                            ; present, ring 0, data, expand-up, writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; Linear code segment descriptor
;
LINEAR_CODE_SEL     EQU $ - GDT_BASE    ; Selector [0x10]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  09Bh                            ; present, ring 0, data, expand-up, not-writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; System data segment descriptor
;
SYS_DATA_SEL        EQU $ - GDT_BASE    ; Selector [0x18]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  093h                            ; present, ring 0, data, expand-up, not-writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0

;
; System code segment descriptor
;
SYS_CODE_SEL        EQU $ - GDT_BASE    ; Selector [0x20]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0
    DB  09Ah                            ; present, ring 0, data, expand-up, writable
    DB  0CFh                            ; page-granular, 32-bit
    DB  0
;
; Spare segment descriptor
;
SYS16_CODE_SEL      EQU $ - GDT_BASE    ; Selector [0x28]
    DW  0FFFFh                          ; limit 0xFFFFF
    DW  0                               ; base 0
    DB  0Eh                             ; Changed from F000 to E000.
    DB  09Bh                            ; present, ring 0, code, expand-up, writable
    DB  00h                             ; byte-granular, 16-bit
    DB  0
;
; Spare segment descriptor
;
SYS16_DATA_SEL      EQU $ - GDT_BASE    ; Selector [0x30]
    DW  0FFFFh                          ; limit 0xFFFF
    DW  0                               ; base 0
    DB  0
    DB  093h                            ; present, ring 0, data, expand-up, not-writable
    DB  00h                             ; byte-granular, 16-bit
    DB  0

;
; Spare segment descriptor
;
SPARE5_SEL          EQU $ - GDT_BASE    ; Selector [0x38]
    DW  0                               ; limit 0
    DW  0                               ; base 0
    DB  0
    DB  0                               ; present, ring 0, data, expand-up, writable
    DB  0                               ; page-granular, 32-bit
    DB  0
GDT_SIZE            EQU $ - BootGdtTable    ; Size, in bytes

;
; GDT Descriptor
;
GdtDesc:                                ; GDT descriptor
    DW  GDT_SIZE - 1                    ; GDT limit
    DD  OFFSET BootGdtTable             ; GDT base address


ProtectedModeEntryLinearAddress   LABEL   FWORD
ProtectedModeEntryLinearOffset    LABEL   DWORD
  DD      OFFSET ProtectedModeEntryPoint  ; Offset of our 32 bit code
  DW      LINEAR_CODE_SEL

#if FixedPcdGetBool(PcdBfxEnable) == 1
ReloadGdtFarJumpAddress   LABEL   FWORD
ReloadGdtFarJumpOffset    LABEL   DWORD
    DD  OFFSET ReloadGdtFarJumpStart    ; Offset of our 32 bit code
    DW  LINEAR_CODE_SEL
#endif
_TEXT_PROTECTED_MODE    ENDS
END
