;; @file
;  Real mode thunk module
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2005 - 2017 Intel Corporation.
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

ASM_PFX(mCode16Size): DQ _Code16End - ASM_PFX(_Code16Addr)

NullSegSel: DQ 0
_16CsSegSel:
  DW      -1
  DW      0
  DB      0
  DB      0x9b
  DB      0x8f                               ; 16-bit segment
  DB      0

_16Gdtr:
  DW      $ - NullSegSel - 1
  DQ      NullSegSel

    DEFAULT REL
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

global ASM_PFX(_Thunk16)
ASM_PFX(_Thunk16):
  push    rbp
  push    rbx
  push    rsi
  push    rdi
  push    r12
  push    r13
  push    r14
  push    r15

  push    fs
  push    gs

  mov     r12d, ds
  mov     r13d, es
  mov     r14d, ss
  mov     r15, rsp
  mov     rsi, rcx
  movzx   r10, word [rsi + IA32_REGS._SS]
  xor     rdi, rdi
  mov     edi, [rsi + IA32_REGS._ESP]
  add     rdi, - IA32_REGS.size - _STK16.size
  push    rdi
  imul    rax, r10, 16
  add     rdi, rax
  push    IA32_REGS.size / 4
  pop     rcx
  rep     movsd
  pop     rbx                                ; rbx <- 16-bit stack offset
  lea     eax, [_Thunk16L01]                 ; return offset
  stosd
  mov     eax, cs                            ; return segment
  stosw
  mov     eax, edx                           ; THUNK Flags
  stosw
  sgdt    [rsp + 0x58]                       ; save GDTR
  mov     rax, [rsp + 0x58]
  stosq
  mov     rax, cr0                           ; save CR0
  mov     esi, eax                           ; esi <- CR0 to set
  stosd
  mov     rax, cr4                           ; save CR4
  stosd
  sidt    [rsp + 0x58]                       ; save IDTR
  and     esi, 0x7ffffffe                    ; NOT 080000001h          ; clear PE & PG bits
  mov     rdi, r10                           ; rdi <- 16-bit stack segment

  shl     r8, 16
  push    r8                                 ; far jmp address
  lea     eax, [@16Bit]
  push    rax
  mov     word [rsp + 4], 8
  lgdt    [_16Gdtr]
  retf
@16Bit:
  mov     cr0, rsi                           ; disable PE & PG
  DB      0x66
  mov     ecx, 0xc0000080
  rdmsr
  and     ah, ~ 1
  wrmsr                                      ; clear LME bit
  mov     rax, cr4
  and     al, ~ 0x30                         ; clear PAE & PSE
  mov     cr4, rax
  retf
_Thunk16L01:
  xor     rax, rax
  mov     eax, ss
  shl     eax, 4
  add     eax, esp                           ; rax <- address of 16-bit stack
  mov     rsp, r15
  lidt    [rsp + 0x58]                       ; restore IDTR
  mov     ds, r12d
  mov     es, r13d
  mov     ss, r14d
  pop     gs
  pop     fs
  pop     r15
  pop     r14
  pop     r13
  pop     r12
  pop     rdi
  pop     rsi
  pop     rbx
  pop     rbp
  ret

ALIGN   16

global ASM_PFX(_Code16Addr)
ASM_PFX(_Code16Addr):

global ASM_PFX(RealMode)
ASM_PFX(RealMode):
  mov     ss, edi
  mov     sp, bx                             ; set up 16-bit stack
  DB      0x2e, 0x0f, 0x01, 0x1e
  DW      _16Idtr - ASM_PFX(_Code16Addr)     ; lidt _16Idtr
  DB      0x66, 0x61                         ; popad
  DB      0x1f                               ; pop ds
  DB      0x07                               ; pop es
  pop     fs
  pop     gs

  add     esp, 8                             ; skip RFLAGS
  DB      0x67, 0xf7, 0x44, 0x24, 0xe, 1, 0  ; test [esp + 0eh], 1
  jz      .1
  pushfq                                     ; pushf, actually
.1:
  DB      0xe                                ; push cs
  DB      0x68                               ; push /iw
  DW      .3arCallRet - ASM_PFX(_Code16Addr)
  jz      .2
  DB      0x66
  jmp     [esp + 6]
.2:
  DB      0x66
  jmp     [esp + 4]
.3arCallRet:
  DB      0x66
  push    0                                  ; push a dword of zero
  pushf                                      ; pushfd, actually
  push    gs
  push    fs
  DB      6                                  ; push es
  DB      0x1e                               ; push ds
  DB      0x66, 0x60                         ; pushad
  cli

  DB      0x66
  lgdt    [esp + IA32_REGS.size + _STK16.SavedGdtr]

  DB      0x66
  mov     eax, [esp + IA32_REGS.size + _STK16.SavedCr4]

  mov     cr4, rax
  DB      0x66
  mov     ecx, 0xc0000080
  rdmsr
  or      ah, 1
  wrmsr                                      ; set LME
  DB      0x66
  mov     eax, [esp + IA32_REGS.size + _STK16.SavedCr0]

  mov     cr0, rax
  DB      0x66
  jmp     [esp + IA32_REGS.size +_STK16.RetEip]

_16Idtr:  DW  (1 << 10) - 1
          DD  0

_Code16End:

