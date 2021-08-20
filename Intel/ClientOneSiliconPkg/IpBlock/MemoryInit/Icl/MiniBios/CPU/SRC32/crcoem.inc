;;@file
;   Contains equates which are implementation specific.
;
;@copyright
; Copyright (c) 2010 - 2018 Intel Corporation. All rights reserved
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


IFNDEF CRCOEM_INC
CRCOEM_INC EQU   1

;
; Define the CodeRegion - using 64KB code area below 4GB
; See BWG - chapter "Restrictions to Using Cache for Stack and Code"
;
IF ROM_SIZE EQ 1
CODE_REGION_BASE_ADDRESS  EQU  0FFF00000h
CODE_REGION_SIZE          EQU  (1024 * 1024)
ELSE
CODE_REGION_BASE_ADDRESS  EQU  0FFE00000h
CODE_REGION_SIZE          EQU  (2 * 1024 * 1024)
ENDIF

;
; Define the DataStack - using 32KB data area at least 4KB away from code
; This must be in an address range the chipset decodes
; See BWG - chapter "Restrictions to Using Cache for Stack and Code"
;
DATA_STACK_BASE_ADDRESS EQU  0FEF80000h
DATA_STACK_SIZE         EQU  (256 * 1024)     ;(192 * 1024)
DATA_HEAP_SIZE          EQU  (4 * 1024)

;MCH_BAR_BASE            EQU  0FED10000h
MCH_BAR_BASE            EQU  0FEC80000h
DMI_BAR_BASE            EQU  0FEDA0000h
;PCIE_BAR_BASE           EQU  0E0000000h
PCIE_BAR_BASE           EQU  0C0000000h
SMBUS_BASE              EQU  0EFA0h
ACPI_BASE_ADDRESS       EQU  01800h
RCBA_BASE               EQU  0FED1C000h
GDXC_BASE               EQU  0FED80000h
PCH_PWRM_BASE_ADDRESS   EQU  0FE000000h  ; PMC MBAR MMIO base address
PCH_PCR_BASE_ADDRESS    EQU  0FD000000h  ; SBREG MMIO base address
TCO_BASE_ADDRESS        EQU  0400h       ; SPT TCO base address

MEMORY_STACK_ADDR       EQU (DATA_STACK_BASE_ADDRESS + DATA_STACK_SIZE)

ENDIF    ;IFNDEF CRCOEM_INC
