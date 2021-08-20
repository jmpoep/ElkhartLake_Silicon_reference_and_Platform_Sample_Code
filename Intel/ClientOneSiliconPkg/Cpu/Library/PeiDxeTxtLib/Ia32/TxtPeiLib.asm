;; @file
;  This file contains the code to determine Processor/Chipset TXT capaiblity
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
;  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
;  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
;  the terms of your license agreement with Intel or your vendor. This file may
;  be modified by the user, subject to additional terms of the license agreement.
;
;@par Specification Reference:
;;

    .XLIST
    include txt.inc
    .LIST

    .686p
    .MMX
    .XMM
    .MODEL FLAT,C
    .CODE

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:   CheckSmxCapabilities
;
;  Input:       None
;
;  Output:      None
;
;  Registers:   None are preserved
;
;  Description: Execute GETSEC[CAPABILITIES] to report the SMX capabilities
;
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------

CheckSmxCapabilities PROC PUBLIC USES ebx

    ;
    ; Check whether SMX is supported
    ;
    mov     eax, 1
    cpuid
    bt      ecx, IA32_CPUID_SMX_B

    .IF !CARRY?
        mov     eax, 0
        jmp     @F
    .ENDIF

    ;
    ; Save cr4
    ;
    mov     edx, CR4

    ;
    ; Enable SMXE
    ;
    mov     eax, CR4
    or      eax, CR4_SMXE
    mov     CR4, eax

    ;
    ; Call GETSEC[CAPABILITIES]
    ;
    mov     eax, CAPABILITIES        ; eax = CAPABILITIES
    mov     ebx, 0
    _GETSEC

    ;
    ; Restore cr4
    ;
    mov     CR4, edx

@@:
    ret
CheckSmxCapabilities ENDP

END
