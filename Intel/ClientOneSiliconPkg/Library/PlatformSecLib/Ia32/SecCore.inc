;; @file
;  SecCore constants and macros
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 1999 - 2016 Intel Corporation.
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
;  This file contains a 'Sample Driver' and is licensed as such under the terms
;  of your license agreement with Intel or your vendor. This file may be modified
;  by the user, subject to the additional terms of the license agreement.
;
;@par Specification Reference:

;;

;
; Set to 1 to enable debug
;
NO_EVICTION_MODE_DEBUG  EQU     1

STATUS_CODE         MACRO status
IF NO_EVICTION_MODE_DEBUG
                    mov  al, status
                    out  080h, al
ENDIF
ENDM

FVHEADER_LEN_OFF    EQU 30h
FFSHEADER_LEN       EQU 18h

IMAGE_BASE_ADDRESS  EQU 0FFFF0000h

;
; Set to 1 to enable debug support for "Deterministic BSP selection"
;
AP_ENTRY_DELAY      EQU         10h
AP_EXECUTION_DELAY  EQU         1000h

;
; Define the segment used for AP start-up
; It should be on the top of the recovery FV
; Seg  = 0100h - (BlockNumber of Recovery FV)
; Here 0FCh = 0100h - 04h
;
AP_SEG                      EQU   0FFh

;
; Commands defined in the AP SIPI code
;
AP_SIPI_COLLECT_MAX_RATIO   EQU   001h
AP_SIPI_PROGRAM_MAX_RATIO   EQU   002h
AP_SIPI_SWITCH_BSP          EQU   003h
