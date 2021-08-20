;; @file
;  SEC CPU Library constants and macros
;
; @copyright
;  INTEL CONFIDENTIAL
;  Copyright 2014 - 2018 Intel Corporation.
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
; @par Specification Reference:
;;


;
; Set to 1 to enable debug
;
NO_EVICTION_MODE_DEBUG  EQU     1

;
;arg 1:Status
;
%macro STATUS_CODE   1
%if NO_EVICTION_MODE_DEBUG
                    mov  al, %1
                    out  080h, al
%endif
%endmacro

;
; MSR definitions
;
MSR_IA32_PLATFORM_ID          EQU 0017h
MSR_IA32_BIOS_UPDT_TRIG       EQU 0079h
MSR_IA32_BIOS_SIGN_ID         EQU 008Bh
MSR_IA32_DEBUG_INTERFACE      EQU 0C80h
MSR_APIC_BASE                 EQU 001Bh
MSR_BOOT_GUARD_SACM_INFO      EQU 013Ah

;
; MTRR definitions
;
IA32_MTRR_CAP                 EQU 0FEh
MTRR_PHYS_BASE_0              EQU 0200h
MTRR_PHYS_MASK_0              EQU 0201h
MTRR_PHYS_BASE_1              EQU 0202h
MTRR_PHYS_MASK_1              EQU 0203h
MTRR_PHYS_BASE_2              EQU 0204h
MTRR_PHYS_MASK_2              EQU 0205h
MTRR_PHYS_BASE_3              EQU 0206h
MTRR_PHYS_MASK_3              EQU 0207h
MTRR_PHYS_BASE_4              EQU 0208h
MTRR_PHYS_MASK_4              EQU 0209h
MTRR_PHYS_BASE_5              EQU 020Ah
MTRR_PHYS_MASK_5              EQU 020Bh
MTRR_PHYS_BASE_6              EQU 020Ch
MTRR_PHYS_MASK_6              EQU 020Dh
MTRR_PHYS_BASE_7              EQU 020Eh
MTRR_PHYS_MASK_7              EQU 020Fh
MTRR_PHYS_BASE_8              EQU 0210h
MTRR_PHYS_MASK_8              EQU 0211h
MTRR_PHYS_BASE_9              EQU 0212h
MTRR_PHYS_MASK_9              EQU 0213h
MTRR_FIX_64K_00000            EQU 0250h
MTRR_FIX_16K_80000            EQU 0258h
MTRR_FIX_16K_A0000            EQU 0259h
MTRR_FIX_4K_C0000             EQU 0268h
MTRR_FIX_4K_C8000             EQU 0269h
MTRR_FIX_4K_D0000             EQU 026Ah
MTRR_FIX_4K_D8000             EQU 026Bh
MTRR_FIX_4K_E0000             EQU 026Ch
MTRR_FIX_4K_E8000             EQU 026Dh
MTRR_FIX_4K_F0000             EQU 026Eh
MTRR_FIX_4K_F8000             EQU 026Fh

MTRR_DEF_TYPE                 EQU 02FFh
MTRR_DEF_TYPE_E               EQU 0800h
MTRR_DEF_TYPE_FE              EQU 0400h

;
; Define the high 32 bits of MTRR masking
; This should be read from CPUID EAX = 080000008h, EAX bits [7:0]
; But for most platforms this will be a fixed supported size so it is
; fixed to save space.
;
MTRR_PHYS_MASK_VALID          EQU 0800h
MTRR_MEMORY_TYPE_UC           EQU 00h
MTRR_MEMORY_TYPE_WC           EQU 01h
MTRR_MEMORY_TYPE_WT           EQU 04h
MTRR_MEMORY_TYPE_WP           EQU 05h
MTRR_MEMORY_TYPE_WB           EQU 06h

NO_EVICT_MODE                 EQU 2E0h

CR0_CACHE_DISABLE             EQU 040000000h
CR0_NO_WRITE                  EQU 020000000h

;
; Cache init and test values
; These are inverted to flip each bit at least once
;
CACHE_INIT_VALUE              EQU 0A5A5A5A5h
CACHE_TEST_VALUE              EQU 05aa55aa5h

;
; Local APIC Register Equates
;
APIC_ICR_LO                   EQU 0FEE00300h
ORSELFINIT                    EQU 000004500h      ; OR mask to send INIT IPI to itself
ORALLBUTSELF                  EQU 0000C0000h      ; OR mask to set dest field = "All But Self"

FVHEADER_LEN_OFF              EQU 30h
FFSHEADER_LEN                 EQU 18h

BLOCK_LENGTH_BYTES            EQU  2048

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