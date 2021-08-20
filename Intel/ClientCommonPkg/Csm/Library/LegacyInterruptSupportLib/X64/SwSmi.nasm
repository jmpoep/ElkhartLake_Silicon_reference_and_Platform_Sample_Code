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

DEFAULT REL
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
;   IN OUT EFI_IA32_REGISTER_SET *RegSet // rcx, r10
;   )
;------------------------------------------------------------------------------
global ASM_PFX(IssueSwSmi)
ASM_PFX(IssueSwSmi):
  push rbx
  push rsi
  push rdi
  push rbp

  mov  r10, rcx
  mov  eax, [r10+0]
  mov  ebx, [r10+4]
  mov  ecx, [r10+8]
  mov  edx, [r10+12]
  mov  esi, [r10+16]
  mov  edi, [r10+20]

  ; no need to sync EFlags, because it only records status of RealMode.

  ASMI

  mov  [r10+0], eax
  mov  [r10+4], ebx
  mov  [r10+8], ecx
  mov  [r10+12], edx
  mov  [r10+16], esi
  mov  [r10+20], edi

  ; only sync EFlags.CF back, because only CF will be checked later.
  ; (Above MOV and OUT do not change CF.)
  pushfq
  pop  rax
  and  eax, 1
  mov  edx, [r10+24]
  and  dl, 0xFE
  or   dl, al
  mov  [r10+24], edx

  pop  rbp
  pop  rdi
  pop  rsi
  pop  rbx
  ret

