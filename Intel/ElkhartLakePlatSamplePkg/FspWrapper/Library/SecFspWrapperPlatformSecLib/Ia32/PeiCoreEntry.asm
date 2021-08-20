;; @file
; Find and call SecStartup
;
;@copyright
; Copyright (c) 2014 - 2019, Intel Corporation. All rights reserved.<BR>
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


.686p
.xmm
.model flat, c
.code

EXTRN   SecStartup:NEAR
EXTRN   PlatformInit:NEAR

;
; Boot Device Indicator Config Register
;
TXT_PUBLIC_BASE               EQU 0FED30000h
BOOT_GUARD_BOOTSTATUS         EQU 0A0h
BLOCK_BOOT_ENABLED            EQU (1 SHL  0)
UFS_BOOT_ENABLED              EQU 1

; Pcds
EXTRN   PcdGet32 (PcdFlashFvPreMemoryBase):DWORD

CallPeiCoreEntryPoint   PROC PUBLIC
  ;
  ; Obtain the hob list pointer
  ;
  mov     eax, [esp+4]
  ;
  ; Obtain the stack information
  ;   ECX: start of range
  ;   EDX: end of range
  ;
  mov     ecx, [esp+8]
  mov     edx, [esp+0Ch]

  ;
  ; Platform init
  ;
  pushad
  push edx
  push ecx
  push eax
  call PlatformInit
  pop  eax
  pop  eax
  pop  eax
  popad

  ;
  ; Set stack top pointer
  ;
  mov     esp, edx

  ;
  ; Push the hob list pointer
  ;
  push    eax

  ;
  ; Save the value
  ;   ECX: start of range
  ;   EDX: end of range
  ;
  mov     ebp, esp
  push    ecx
  push    edx

  ;
  ; Push processor count to stack first, then BIST status (AP then BSP)
  ;
  mov     eax, 1
  cpuid
  shr     ebx, 16
  and     ebx, 0000000FFh
  cmp     bl, 1
  jae     PushProcessorCount

  ;
  ; Some processors report 0 logical processors.  Effectively 0 = 1.
  ; So we fix up the processor count
  ;
  inc     ebx

PushProcessorCount:
  push    ebx

  ;
  ; We need to implement a long-term solution for BIST capture.  For now, we just copy BSP BIST
  ; for all processor threads
  ;
  xor     ecx, ecx
  mov     cl, bl
PushBist:
  movd    eax, mm0
  push    eax
  loop    PushBist

  ; Save Time-Stamp Counter
  movd eax, mm5
  push eax

  movd eax, mm6
  push eax

  ;
  ; SecStartup () in ElkhartLakePlatSamplePkg/Override/UefiCpuPkg/SecCore/SecMain.c
  ; requires only 3 parameters.
  ;

  ;
  ; Pass BFV (*BootFirmwareVolume) into the PEI Core
  ;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  mov     edi, PcdGet32 (PcdFlashFvPreMemoryBase)
  push    edi
#else
  mov     edi, 0FFFFFFFCh
  push    DWORD PTR ds:[edi]
#endif

  ;
  ; Pass stack base (TempRamBase) into the PEI Core
  ;
  mov     ecx, [ebp - 4]
  mov     edx, [ebp - 8]
  push    ecx       ; RamBase
  ;
  ; Pass stack size (SizeOfRam) into the PEI Core
  ;
  sub     edx, ecx
  push    edx       ; RamSize

  ;
  ; Pass Control into the PEI Core
  ;
  call SecStartup
CallPeiCoreEntryPoint   ENDP

END
