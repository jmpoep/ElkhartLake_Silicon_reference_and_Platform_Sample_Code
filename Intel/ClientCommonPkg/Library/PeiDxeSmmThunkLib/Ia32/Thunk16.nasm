;; @file
;  Assembly code for real mode thunk
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2005 - 2016 Intel Corporation.
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
;  This file contains 'Framework Code' and is licensed as such under the terms
;  of your license agreement with Intel or your vendor. This file may not be 
;  modified, except as allowed by additional terms of your license agreement.
;
;@par Specification Reference:
;;

global ASM_PFX(mCode16Size)

    SECTION .data
    ALIGN   16
    
mCode16Size: DD _Code16End - _Code16Addr

NullSegSel: DQ 0
_16CsSegSel:
  DW      -1
  DW      0
  DB      0
  DB      0x9B
  DB      0x8F                               ; 16-bit segment, 4GB limit
  DB      0
;
;_16DsSegSel LABEL   QWORD
; DW      -1
; DW      0
; DB      0
; DB      93h
; DB      8Fh                                ; 16-bit segment, 4GB limit
; DB      0
;
_16Gdtr:
  DW      $ - NullSegSel - 1
  DD      NullSegSel


    SECTION .text
struc IA32_REGS
  ._EDI:    resd 1
  ._ESI:    resd 1
  ._EBP:    resd 1
  ._ESP:    resd 1
  ._EBX:    resd 1
  ._EDX:    resd 1
  ._ECX:    resd 1
  ._EAX:    resd 1
  ._DS:     resw 1
  ._ES:     resw 1
  ._FS:     resw 1
  ._GS:     resw 1
  ._RFLAGS: resq 1
  ._EIP:    resd 1
  ._CS:     resw 1
  ._SS:     resw 1
  .size:
endstruc

struc _STK16
  .RetEip:     resd 1
  .RetCs:      resw 1
  .ThunkFlags: resw 1
  .SavedGdtr:  resd 1
               resw 1
  .Resvd1:     resw 1
  .SavedCr0:   resd 1
  .SavedCr4:   resd 1
  .size:
endstruc

ORG_SS:    DW 00
ORG_ESP:   DD 00
;
; IA32_REGISTER_SET *
; EFIAPI
; _Thunk16 (
;   IN OUT  IA32_REGISTER_SET         *RegisterSet,
;   IN      UINT32                    ThunkFlags,
;   IN      UINT32                    RealModeCs
;   );
;
global ASM_PFX(_Thunk16)
ASM_PFX(_Thunk16):                           ; 10 dwords will be pushed
  push    DS
  push    ES
  push    FS
  push    GS
  push    EDI
  push    ESI
  push    EBP
  push    EBX
  push    EDX
  push    ECX
  mov     ebp, esp
  add     ebp, 40
  mov     [ORG_SS], ss                         ; preserve SS & ESP
  mov     [ORG_ESP], esp

  mov     esi, [ebp + 4]                     ; esi <- RegisterSet
  movzx   edx, word [esi + IA32_REGS._SS]    ; find 16-bit stack linear address
  shl     edx, 4
  add     edx, [esi + IA32_REGS._ESP]
  add     edx, - IA32_REGS.size - _STK16.size                        ; edx <- 16-bit stack linear address
  mov     edi, edx                           ; [RealMode.IA32_REGS] <- RegisterSet
  push    IA32_REGS.size / 4
  pop     ecx
  rep     movsd
  lea     eax, [_Thunk16L01]                 ; [RealMode._STK16.RetEip] <- ReturnOffset
  stosd
  mov     eax, cs                            ; [RealMode._STK16.RetCs] <- ReturnSegment
  stosw
  mov     eax, [ebp + 8]                     ; [RealMode._STK16.ThunkFlags] <- ThunkFlags
  stosw
  sgdt    [edi]                              ; [RealMode._STK16.SavedGdtr] <- GDTR
  add     edi, 8
  mov     eax, cr0                           ; [RealMode._STK16.SavedCr0] <- CR0
  stosd
  mov     esi, eax                           ; esi <- CR0 to set
  and     esi, 0x7FFFFFFE                    ; clear BIT[24, 0]: PE & PG bits
  mov     eax, cr4                           ; [RealMode._STK16.SavedCr4] <- CR4
  stosd

  push    word [ebp + 12]                    ; [STACK] <- RealModeCs, far jump address for into RealMode
  push    0
  push    8                                  ; transfer program control to a readable segment that has a limit of 64KB
  push    @16Bit
  mov     edi, edx                           ; edi <- 16-bit stack linear address

  sidt    [ebp + 8]                          ; save IDTR
  lgdt    [_16Gdtr]
  retf
@16Bit:
  mov     cr0, esi                           ; disable PE & PG
;
;    db      066h
;    mov     ecx, 0C0000080h
;    rdmsr
;    and     ah, NOT 1
;    wrmsr                                   ; clear LME bit
;
  mov     eax, cr4
  and     al, ~ 0x30                         ; clear PAE & PSE
  mov     cr4, eax
  retf
_Thunk16L01:
  xor     eax, eax
  mov     eax, ss
  shl     eax, 4
  add     eax, esp                           ; [EAX] <- RegisterSet after x86 call..to return the execution result
  mov     ss,  word [cs:ORG_SS]              ; restore SS & ESP
  mov     esp, dword [cs:ORG_ESP]
  lidt    [ebp + 8]                          ; restore IDTR

  pop     ECX
  pop     EDX
  pop     EBX
  pop     EBP
  pop     ESI
  pop     EDI
  pop     GS
  pop     FS
  pop     ES
  pop     DS
  ret

    ALIGN   16

; VOID
; EFIAPI
; _Code16Addr (
;   VOID
;   );
global ASM_PFX(_Code16Addr)
ASM_PFX(_Code16Addr):
;
; Input:  EDI <- 16-bit stack linear address
;
global ASM_PFX(RealMode)
ASM_PFX(RealMode):
  db      0x66                               ; movzx   esp, di
  movzx   esp, di
  db      0x33, 0xFF                         ; xor     di, di
  db      0x66                               ; shr     edi, 4
  shr     edi, 4
  mov     ss, di                             ; mov     ss, di

  db      0x2E, 0xF, 001, 0x1E               ; lidt    cs:[_16Idtr]
  dw      _16Idtr - _Code16Addr
  db      0x66                               ; popad
  popa
  pop     ds
  pop     es
  pop     fs
  pop     gs
  add     esp, 4                             ; skip EFLAGS

  ;
  ; test if EFLAGS with _THUNK_INTERRUPT
  ;
  db      0x67, 0xF7, 0x44, 0x24, 0xE, 0x1, 0x0                      ; test [esp + 0Eh]
  jz      .1
  db      0x9C                               ; pushf
.1:
  push    cs
  db      0x68                               ; pushw
  dw      .3arCallRet - _Code16Addr
  jz      .2
  db      0x66, 0x67
  jmp     [esp + 6]
.2:
  db      0x66, 0x67
  jmp     [esp + 4]
.3arCallRet:
  pushf                                      ; pushfd actually
  push    gs
  push    fs
  push    es
  push    ds
  db      0x66                               ; pushad
  pusha
  cli

  db      0x66, 0x67
  lgdt    [esp + IA32_REGS.size + _STK16.SavedGdtr]

  db      0x66, 0x67
  mov     eax, [esp + IA32_REGS.size + _STK16.SavedCr4]

  mov     cr4, eax
;
;    db      066h
;    mov     ecx, 0C0000080h
;    rdmsr
;    or      ah, 1
;    wrmsr                                   ; set LME
;
  db      0x66, 0x67
  mov     eax, [esp + IA32_REGS.size + _STK16.SavedCr0]

  mov     cr0, eax
  db      0x66, 0x67
  jmp     [esp + IA32_REGS.size +_STK16.RetEip]

_16Idtr: DW  (1 << 10) - 1
         DD  0

_Code16End:

