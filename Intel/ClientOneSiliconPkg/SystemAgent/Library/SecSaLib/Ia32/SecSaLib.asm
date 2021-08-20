;; @file
;  This file implements SEC system agent library
;
;@copyright
;  Copyright (c) 2014 - 2017 Intel Corporation. All rights reserved
;  This software and associated documentation (if any) is furnished
;  under a license and may only be used or copied in accordance
;  with the terms of the license. Except as permitted by the
;  license, no part of this software or documentation may be
;  reproduced, stored in a retrieval system, or transmitted in any
;  form or by any means without the express written consent of
;  Intel Corporation.
;  This file contains an 'Intel Peripheral Driver' and is uniquely
;  identified as "Intel Reference Module" and is licensed for Intel
;  CPUs and chipsets under the terms of your license agreement with
;  Intel or your vendor. This file may be modified by the user, subject
;  to additional terms of the license agreement.
;
;@par Specification Reference:
;;


INCLUDE SecSaLib.inc

.686p
.xmm
.model small, c

    .CODE

IF FixedPcdGetBool(PcdFspBinaryEnable) EQ 0
EXTRN   PcdGet64 (PcdPciExpressBaseAddress):QWORD
EXTRN   PcdGet32 (PcdTemporaryPciExpressRegionLength):DWORD
ENDIF
EXTRN   PcdGet64 (PcdMchBaseAddress):QWORD
RET_EBP  MACRO

  jmp     ebp                           ; restore ESP from EBP

ENDM

IF FixedPcdGetBool(PcdFspBinaryEnable) EQ 1
FSPT_CFG_PCI_EXPRESS_BASE_OFF        EQU 048h ; FsptConfig.PcdPciExpressBaseAddress offset
FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF     EQU 050h ; FsptConfig.PcdPciExpressRegionLength offset

EXTRN   AsmGetFspInfoHeaderNoStack:NEAR
CALL_EDI MACRO   RoutineLabel

  local   ReturnAddress
  mov     edi, offset ReturnAddress
  jmp     RoutineLabel
ReturnAddress:

ENDM
ENDIF

SecSaInit  PROC

IF FixedPcdGetBool(PcdFspBinaryEnable) EQ 1
;
; Get FSP-T Config region offset, to get the FSP-T UPD values
;
  CALL_EDI  AsmGetFspInfoHeaderNoStack
  mov   ecx,  DWORD PTR [eax + 01Ch]      ; Read FsptImageBaseAddress
  add   ecx,  DWORD PTR [eax + 024h]      ; Get Cfg Region base address = FsptImageBaseAddress + CfgRegionOffset
ENDIF
;
; Program PCI Express base address
;
  mov   eax,  PCIEX_BAR_REG
  mov   dx,   0CF8h
  out   dx,   eax
IF FixedPcdGetBool(PcdFspBinaryEnable) EQ 1
  mov   eax,  DWORD PTR [ecx + FSPT_CFG_PCI_EXPRESS_LENGHTH_OFF]    ; Read FsptConfig.PcdPciExpressRegionLength
ELSE
  mov   eax,  DWORD PTR PcdGet32 (PcdTemporaryPciExpressRegionLength)
ENDIF
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
IF FixedPcdGetBool(PcdFspBinaryEnable) EQ 1
  mov   eax,  DWORD PTR [ecx + FSPT_CFG_PCI_EXPRESS_BASE_OFF]      ; Read FsptConfig.PcdPciExpressBaseAddress
ELSE
  mov   eax,  DWORD PTR PcdGet64 (PcdPciExpressBaseAddress)
ENDIF
  or    ax,  dx
  or    eax,  (0 OR 1)  ;  PCIEXBAREN = 1
  mov   dx,   0CFCh
  out   dx,   eax

;
; Enable MCH Bar
;
IF FixedPcdGetBool(PcdFspBinaryEnable) eq 1
  mov     esi, DWORD PTR [ecx + FSPT_CFG_PCI_EXPRESS_BASE_OFF]     ; Read FsptConfig.PcdPciExpressBaseAddress
ELSE
  mov     esi, DWORD PTR PcdGet64 (PcdPciExpressBaseAddress)
ENDIF
  add     esi, MCHBAR_REG
  mov     eax, DWORD PTR PcdGet64 (PcdMchBaseAddress)
  or      eax, 1
  mov     Dword Ptr [esi], eax
  RET_EBP
SecSaInit  ENDP

END
