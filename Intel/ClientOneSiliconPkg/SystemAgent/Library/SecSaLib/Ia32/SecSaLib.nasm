;; @file
;  This file implements SEC system agent library
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2014 - 2017 Intel Corporation.
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
;  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
;  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
;  the terms of your license agreement with Intel or your vendor. This file may
;  be modified by the user, subject to additional terms of the license agreement.
;
;@par Specification Reference:
;;


%include "SecSaLib.inc"

SECTION .text

#if  FixedPcdGetBool(PcdFspBinaryEnable) == 0
extern   ASM_PFX(PcdGet64 (PcdPciExpressBaseAddress))
extern   ASM_PFX(PcdGet32 (PcdTemporaryPciExpressRegionLength))
#endif
extern   ASM_PFX(PcdGet64 (PcdMchBaseAddress))

%macro RET_EBP 0

  jmp     ebp                           ; restore ESP from EBP

%endmacro

#if  FixedPcdGetBool(PcdFspBinaryEnable) == 1
FSPT_CFG_PCI_EXPRESS_BASE_OFF        EQU 048h ; FsptConfig.PcdPciExpressBaseAddress offset
FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF     EQU 050h ; FsptConfig.PcdPciExpressRegionLength offset

extern   ASM_PFX(AsmGetFspInfoHeaderNoStack)
;
;args 1:RoutineLabel
;
%macro CALL_EDI  1

  mov     edi,  %%ReturnAddress
  jmp     %1
%%ReturnAddress:

%endmacro

#endif

global ASM_PFX(SecSaInit)
ASM_PFX(SecSaInit):
#if  FixedPcdGetBool(PcdFspBinaryEnable) == 1
;
; Get FSP-T Config region offset, to get the FSP-T UPD values
;
  CALL_EDI  ASM_PFX(AsmGetFspInfoHeaderNoStack)
  mov   ecx,  DWORD [eax + 01Ch]      ; Read FsptImageBaseAddress
  add   ecx,  DWORD [eax + 024h]      ; Get Cfg Region base address = FsptImageBaseAddress + CfgRegionOffset
#endif
;
; Program PCI Express base address
;
  mov   eax,  PCIEX_BAR_REG
  mov   dx,   0CF8h
  out   dx,   eax
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  mov   eax,  DWORD [ecx + FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF]    ; Read FsptConfig.PcdPciExpressRegionLength
#else
  mov   eax,  DWORD [ASM_PFX(PcdGet32 (PcdTemporaryPciExpressRegionLength))]
#endif
  mov   dx,   04h       ; Default is PCIEXBAR length is 64MB ([2:1] = 10b)
  cmp   eax,  10000000h ; Is it 256MB length?
  jne   Check128MB
  mov   dx,   00h       ; Set PCIEXBAR length as 256MB ([2:1] = 00b)
  jmp   ProgramLength

Check128MB:
  cmp   eax,  8000000h  ; Is it 128MB length?
  jne   Check512MB
  mov   dx,   02h       ; Set PCIEXBAR length as 128MB ([2:1] = 01b)
  jmp   ProgramLength
Check512MB:
  cmp   eax,  20000000h  ; Is it 512MB length?
  jne   ProgramLength
  mov   dx,   06h        ; Set PCIEXBAR length as 512MB ([2:1] = 11b)

ProgramLength:
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  mov   eax,  DWORD [ecx + FSPT_CFG_PCI_EXPRESS_BASE_OFF]      ; Read FsptConfig.PcdPciExpressBaseAddress
#else
  mov   eax,  DWORD [ASM_PFX(PcdGet64 (PcdPciExpressBaseAddress))]
#endif
  or    ax,  dx
  or    eax,  (0 | 1)  ;  PCIEXBAREN = 1
  mov   dx,   0CFCh
  out   dx,   eax

;
; Enable MCH Bar
;
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  mov     esi, DWORD [ecx + FSPT_CFG_PCI_EXPRESS_BASE_OFF]     ; Read FsptConfig.PcdPciExpressBaseAddress
#else
  mov     esi, DWORD  [ASM_PFX(PcdGet64 (PcdPciExpressBaseAddress))]
#endif
  add     esi, MCHBAR_REG
  mov     eax, DWORD  [ASM_PFX(PcdGet64 (PcdMchBaseAddress))]
  or      eax, 1
  mov     Dword [esi], eax
  RET_EBP
