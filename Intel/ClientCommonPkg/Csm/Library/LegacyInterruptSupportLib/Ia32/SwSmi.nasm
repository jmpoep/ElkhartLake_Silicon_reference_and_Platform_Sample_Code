;
; This file contains a 'Sample Driver' and is licensed as such
; under the terms of your license agreement with Intel or your
; vendor.  This file may be modified by the user, subject to
; the additional terms of the license agreement
;
;
; Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by such
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
;
;
; Module Name:
;
;    SwSmi.nasm
;
; Abstract:
;
;

SECTION .text

struc EFI_IA32_REGISTER_SET
  .RegEax:                resd            1
  .RegEbx:                resd            1
  .RegEcx:                resd            1
  .RegEdx:                resd            1
  .RegEsi:                resd            1
  .RegEdi:                resd            1
  .RegEFlags:             resd            1
  .RegEs:                 resw            1
  .RegCs:                 resw            1
  .RegSs:                 resw            1
  .RegDs:                 resw            1
  .RegFs:                 resw            1
  .RegGs:                 resw            1
  .RegEbp:                resd            1
  .RegEsp:                resd            1
endstruc

%define APMC 0xB2

%macro ASMI 0
        out     APMC , al
        WAFORIO
%endmacro

%define MAGIC_STONE (0x84)           ; An unused I/O Port
%macro WAFORIO 0                     ; Delay about a microsecond.
        out     MAGIC_STONE,al       ; Must not change CPU state.
%endmacro                            ;

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; IssueSwSmi (
;   IN OUT EFI_IA32_REGISTER_SET *RegSet // esp + 4
;   )
;------------------------------------------------------------------------------
global ASM_PFX(IssueSwSmi)
ASM_PFX(IssueSwSmi):
  push ebx
  push esi
  push edi
  push ebp

  mov  ecx, [esp+4]
  mov  eax, [ecx+0]
  mov  ebx, [ecx+4]
  mov  edx, [ecx+12]
  mov  esi, [ecx+16]
  mov  edi, [ecx+20]
  mov  ecx, [ecx+8]

  ; no need to sync EFlags, because it only records status of RealMode.

  ASMI

  push ecx
  mov  ecx, [esp+4]
  mov  [ecx+0], eax
  mov  [ecx+4], ebx
  mov  [ecx+12], edx
  mov  [ecx+16], esi
  mov  [ecx+20], edi
  pop  eax
  mov  [ecx+8], eax

  ; only sync EFlags.CF back, because only CF will be checked later.
  ; (Above MOV and OUT do not change CF.)
  pushfd
  pop  eax
  and  eax, 1
  mov  edx, [ecx+24]
  and  dl, 0xFE
  or   dl, al
  mov  [ecx+24], edx

  pop  ebp
  pop  edi
  pop  esi
  pop  ebx
  ret

