;------------------------------------------------------------------------------ ;
;
; This file contains a 'Sample Driver' and is licensed as such
; under the terms of your license agreement with Intel or your
; vendor.  This file may be modified by the user, subject to
; the additional terms of the license agreement
;
;
; Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
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
;   Lfence.nasm
;
; Abstract:
;
;   Performs a serializing operation on all load-from-memory instructions that
;   were issued prior to the call of this function.
;
; Notes:
;
;------------------------------------------------------------------------------

    DEFAULT REL
    SECTION .text

;------------------------------------------------------------------------------
; VOID
; EFIAPI
; InternalAsmLfence (
;   VOID
;   );
;------------------------------------------------------------------------------
global ASM_PFX(InternalAsmLfence)
ASM_PFX(InternalAsmLfence):
    lfence
    ret
