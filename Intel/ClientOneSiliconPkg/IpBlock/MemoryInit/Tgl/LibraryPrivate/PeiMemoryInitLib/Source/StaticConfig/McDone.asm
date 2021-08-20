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

#define PRMRR_SIZE          8000000h
#define UCODE_CR_MTRRCAP    0feh
#define PRMRR_ENABLE        (1 SHL 12)
#define PRMRR_MASK_EN       800h
#define PRMRR_MASK_LOCK     400h
#define UNCORE_PRMRR_MASK   1F5H
#define UNCORE_PRMRR_BASE   2A0H

mov    ecx, UCODE_CR_MTRRCAP
rdmsr
test   eax, PRMRR_ENABLE
je     prmrr_skip

; TSEGMB
xor    edx, edx
mov    eax, DWORD PTR ds:[0e0000000h + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B8h]
out    84h, eax
and    eax, NOT 0fh
sub    eax, PRMRR_SIZE
and    eax, NOT (PRMRR_SIZE - 1)

mov    ecx, UNCORE_PRMRR_BASE
wrmsr

mov    edx, 7fh
mov    eax, 0ffffffffh
sub    eax, (PRMRR_SIZE - 1)                    ; 128 MB
or     eax, PRMRR_MASK_LOCK OR PRMRR_MASK_EN      ; Set lock bit [10] and 11
mov    ecx, UNCORE_PRMRR_MASK
wrmsr
prmrr_skip:

;
; writing to register MCDECS_CR_MC_INIT_STATE_G_0_0_0_MCHBAR_MCMAIN of MCHBAR
;
mov    DWORD PTR ds:[0fed10000h + 05030h], 00040010Ah + 81h
mov    DWORD PTR ds:[0fed10000h + 050FCh], 0000008Fh

;
; Poll MCDECS_CR_MC_INIT_STATE_G_0_0_0_MCHBAR_MCMAIN_MC_INIT_DONE_ACK  bit until is is set.
;
PollDoneACK1600:
  test   DWORD PTR ds:[0fed10000h + 05030h], 000000020h
  jz     PollDoneACK1600

;
; Enable DDR thermal test feature
; DDR_PTM_CTL_0_0_0_MCHBAR_PCU offset 0x5880
; Set CLTM_ENABLE, bit 1:1
;
mov eax, DWORD PTR ds:[0fed10000h + 05880h]
bts eax, 1
mov DWORD PTR ds:[0fed10000h + 05880h], eax

;
; Lock registers
;
mov    eax, Pciexbar
out    80h, eax    ; send a marker to port 80

or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0a0h], 1

or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0BCh], 1
or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B4h], 1
or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0B0h], 1
or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 0A8h], 1

mov    edx, DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 098h]
or     edx, 1
mov    DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 098h], edx

mov    edx, DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 090h]
or     edx, 1
mov    DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 090h], edx

or     DWORD PTR ds:[eax + (00h SHL 20) + (00h SHL 15) + (00h SHL 12) + 078h], 400h

;
; Set EDRAM Base Address
;
mov    eax, 0CF114000h
out    80h, eax
xor    edx, edx
shld   edx, eax, 6
or     eax ,1
out    80h, eax
xchg   eax, edx
out    80h, eax
xchg   eax, edx

