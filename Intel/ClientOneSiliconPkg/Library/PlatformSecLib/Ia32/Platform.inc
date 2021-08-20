;; @file
;  Platform Specific Definitions
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2008 - 2016 Intel Corporation.
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
;
;;

PEI_CORE_ENTRY_BASE           EQU 0FFFFFFE0h
FV_MAIN_BASE                  EQU 0FFFFFFFCh

PROTECTED_MODE_ENTRY_GUID1    EQU 050626249h
PROTECTED_MODE_ENTRY_GUID2    EQU 0746E456Dh
PROTECTED_MODE_ENTRY_GUID3    EQU 06F507972h
PROTECTED_MODE_ENTRY_GUID4    EQU 000746E69h

BIT0                          EQU 01h
BIT1                          EQU 02h
BIT2                          EQU 04h
BIT3                          EQU 08h
BIT4                          EQU 10h
BIT5                          EQU 20h
BIT6                          EQU 40h
BIT7                          EQU 80h
BIT8                          EQU 100h
BIT9                          EQU 200h
BIT10                         EQU 400h
BIT11                         EQU 800h
BIT12                         EQU 1000h
BIT13                         EQU 2000h
BIT14                         EQU 4000h
BIT15                         EQU 8000h
BIT16                         EQU 10000h
BIT17                         EQU 20000h
BIT18                         EQU 40000h
BIT19                         EQU 80000h
BIT23                         EQU 0800000h
BIT31                         EQU 080000000h

BspApicIdSaveStart            EQU 24

;
; Boot Device Indicator Config Register
;
TXT_PUBLIC_BASE               EQU 0FED30000h
BOOT_GUARD_BOOTSTATUS         EQU 0A0h
BLOCK_BOOT_ENABLED            EQU 1
UFS_BOOT_ENABLED              EQU 1

R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS    EQU 320h
NEM_TEMPORARY_RAM_BASE                        EQU 28h
NEM_TEMPORARY_RAM_SIZE                        EQU 2Ch
