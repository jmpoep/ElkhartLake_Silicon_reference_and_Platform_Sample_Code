;;@file
;   Routine to get setup options for various features.
;
;@copyright
; Copyright (c) 2007 - 2014 Intel Corporation. All rights reserved
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
;@par Specification Reference:
;;


   .listall
   .686p
   .xmm
   .model   flat,c

.XLIST
   ; Files generated during build time...do not edit!!!
   include crc.i
   include crcoem.inc
.LIST


.const

.code

;-----------------------------------------------------------------------------
; OemStacklessStatusCode: OEM hook for status codes.
;
; Input:
;  AX = Status code
;
; Register Usage:
;  No memory exists. No stack exists.
;  All registers must be preserved.
;
; Output:
;  None
;
;-----------------------------------------------------------------------------
oemStacklessStatusCode  PROC

   ; insert OEM code here to display status code
   out   80h, ax

   test  ax, ax
   jns   exit
   jmp   $

exit:
   ret

oemStacklessStatusCode  ENDP


;-----------------------------------------------------------------------------
; OemMemoryBase: Get the NEM memory start.
;
; Input:
;  N/A
;
; Register Usage:
;  eax
;
;
; Output:
;  eax return the data stack base address.
;
;-----------------------------------------------------------------------------
OemMemoryBase  PROC

   mov eax,DATA_STACK_BASE_ADDRESS
   ret

OemMemoryBase  ENDP

END
