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

;
; 8GB RAM, 6 GB remapped NO GFX
;

;
; Show the DDR size in GB on port80
;
mov    eax, 0C00A0008h
out    80h, eax

mov    ebx, Pciexbar

; NO GFX
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 050h], 02h

; MESEG_BASE
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 070h], 0fe000000h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 074h], 000000001h

; MESEG_MASK
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 078h], 0fef00800h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 07Ch], 000000001h

; REMAPBASE = 4GB
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 090h], 0fe000000h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 094h], 000000001h

; REMAPLIMIT
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 098h], 07df00000h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 09Ch], 000000002h

; TOM  = 8GB
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0A0h], 000000000h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0A4h], 000000002h

; TOUUD to min(TOM-stolen mem for ME OR min PCI mem addr)
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0A8h], 07f000000h
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0ACh], 000000002h

; BDSM
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B0h], 080000000h

; BGSM
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B4h], 080000000h

; TSEGMB
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B8h], 07f000000h

; TOLUD to TOM-stolen mem for ME
mov    DWORD PTR ds:[ebx + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0BCh], 080000000h

