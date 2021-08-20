;; @file
;  Static Memory Configuration file
;
; @copyright
; Copyright (c) 2015 Intel Corporation. All rights reserved
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by the
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
; This file contains an 'Intel Peripheral Driver' and is uniquely
; identified as "Intel Reference Module" and is licensed for Intel
; CPUs and chipsets under the terms of your license agreement with
; Intel or your vendor. This file may be modified by the user, subject
; to additional terms of the license agreement.
;
; @par Specification Reference:
;;

mov    eax, 1
mov    ecx, 0
cpuid
mov    eax, ecx
out    80h, eax
test   ecx, MRC_BIT6                                    ; is TXT processor
je     noTxt

mov    eax, dword ptr ds:[TXT_PUBLIC_BASE + 200h]
mov    eax, dword ptr ds:[TXT_PUBLIC_BASE + 10h]

test   dword ptr ds:[TXT_PUBLIC_BASE + 10h], 1          ; TXT Chipset
je     noTxt

xor    eax, eax
mov    al, byte PTR ds:[TPM_STATUS_REG_ADDRESS]
out    80h, eax
shl    eax, 8
mov    al, byte PTR ds:[TPM_STATUS_REG_ADDRESS]
out    80h, eax
shl    eax, 8
mov    al, byte PTR ds:[TPM_STATUS_REG_ADDRESS]
out    80h, eax
shl    eax, 8
mov    al, byte PTR ds:[TPM_STATUS_REG_ADDRESS]
out    80h, eax

mov    ecx, 02e6h
mov    eax, 0
mov    edx, 0
wrmsr
mov    eax, 0FED4FED4h
noTxt:

mov    DWORD PTR ds:[0fed10000h + 5E00h], 080000006h  ; Freq for DDR4 is 1600
ddr4_freq:
  test   DWORD PTR ds:[0fed10000h + 5E00h], 080000000h  ; Poll RUN_BUSY bit until it becomes zero
  jnz    ddr4_freq

#include "Source/StaticConfig/Ddr4.asm"

