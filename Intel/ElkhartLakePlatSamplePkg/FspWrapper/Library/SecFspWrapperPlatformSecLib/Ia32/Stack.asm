;; @file
; Switch the stack from temporary memory to permenent memory.
;
;@copyright
; Copyright (c) 2014 - 2016, Intel Corporation. All rights reserved.<BR>
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

    .586p
    .model  flat,C
    .code

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; SecSwitchStack (
;   UINT32   TemporaryMemoryBase,
;   UINT32   PermanentMemoryBase
;   );
;------------------------------------------------------------------------------
SecSwitchStack   PROC
    ;
    ; Save three register: eax, ebx, ecx
    ;
    push  eax
    push  ebx
    push  ecx
    push  edx

    ;
    ; !!CAUTION!! this function address's is pushed into stack after
    ; migration of whole temporary memory, so need save it to permanent
    ; memory at first!
    ;

    mov   ebx, [esp + 20]          ; Save the first parameter
    mov   ecx, [esp + 24]          ; Save the second parameter

    ;
    ; Save this function's return address into permanent memory at first.
    ; Then, Fixup the esp point to permanent memory
    ;
    mov   eax, esp
    sub   eax, ebx
    add   eax, ecx
    mov   edx, dword ptr [esp]         ; copy pushed register's value to permanent memory
    mov   dword ptr [eax], edx
    mov   edx, dword ptr [esp + 4]
    mov   dword ptr [eax + 4], edx
    mov   edx, dword ptr [esp + 8]
    mov   dword ptr [eax + 8], edx
    mov   edx, dword ptr [esp + 12]
    mov   dword ptr [eax + 12], edx
    mov   edx, dword ptr [esp + 16]    ; Update this function's return address into permanent memory
    mov   dword ptr [eax + 16], edx
    mov   esp, eax                     ; From now, esp is pointed to permanent memory

    ;
    ; Fixup the ebp point to permanent memory
    ;
    mov   eax, ebp
    sub   eax, ebx
    add   eax, ecx
    mov   ebp, eax                ; From now, ebp is pointed to permanent memory

    pop   edx
    pop   ecx
    pop   ebx
    pop   eax
    ret
SecSwitchStack   ENDP

    END
