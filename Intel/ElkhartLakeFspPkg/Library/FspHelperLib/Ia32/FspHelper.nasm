;; @file
;  Provide FSP helper function.
;
; Copyright (c) 2015 - 2018, Intel Corporation. All rights reserved.<BR>
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution.  The full text of the license may be found at
; http://opensource.org/licenses/bsd-license.php.
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;;

    SECTION .text

global ASM_PFX(SiFspInfoHeaderRelativeOff)
ASM_PFX(SiFspInfoHeaderRelativeOff):
   DD    0x12345678               ; This value must be patched by the build script

global ASM_PFX(SiAsmGetFspBaseAddress)
ASM_PFX(SiAsmGetFspBaseAddress):
   call  ASM_PFX(SiAsmGetFspInfoHeader)
   add   eax, 0x1C
   mov   eax, dword [eax]
   ret

global ASM_PFX(SiAsmGetFspInfoHeader)
ASM_PFX(SiAsmGetFspInfoHeader):
   call  ASM_PFX(NextInstruction)
ASM_PFX(NextInstruction):
   pop   eax
   sub   eax, ASM_PFX(NextInstruction)
   add   eax, ASM_PFX(SiAsmGetFspInfoHeader)
   sub   eax, dword [eax - ASM_PFX(SiAsmGetFspInfoHeader) + ASM_PFX(SiFspInfoHeaderRelativeOff)]
   ret

global ASM_PFX(SiAsmGetFspInfoHeaderNoStack)
ASM_PFX(SiAsmGetFspInfoHeaderNoStack):
   mov   eax, ASM_PFX(SiAsmGetFspInfoHeader)
   sub   eax, dword [ASM_PFX(SiFspInfoHeaderRelativeOff)]
   jmp   edi
