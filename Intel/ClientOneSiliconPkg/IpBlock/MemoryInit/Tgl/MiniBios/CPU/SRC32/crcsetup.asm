;;@file
;   This routine is only required to instantiate CRC setup options structure
;   and then call the CRC Entry Point (CrcStart) with the CRC setup options
;   structure as a parameter on the stack. Since no memory exists, the CRC
;   setup options structure and the stack are both hard-coded in the ROM.
;
;@copyright
; Copyright (c) 2010 - 2019 Intel Corporation. All rights reserved
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
.LIST

INCLUDE crcoem.inc

.data

platform_initializers   TEXTEQU  <MCH_BAR_BASE,\
                                  PCIE_BAR_BASE,\
                                  SMBUS_BASE,\
                                  HPET_BASE>

nem_initializers        TEXTEQU  <CODE_REGION_BASE_ADDRESS,\
                                 CODE_REGION_SIZE,\
                                 DATA_STACK_BASE_ADDRESS,\
                                 DATA_STACK_SIZE,\
                                 DATA_HEAP_SIZE>

ucode_initializers      TEXTEQU  <microcode_start,\
                                 microcode_size>

runtime_initializers    TEXTEQU  <CrcExitAddress,\
                                 MEMORY_STACK_ADDR>


; This is the ROM-based CRC setup options structure.
; Do not change the format of this structure since it is shared
; by the CPU reference code via the file CRC.H. The values can
; be changed above or by changing the underlying definitions from
; the file CRCOEM.INC.

rom_options cpu_setup_options    <platform_initializers,\
                                 nem_initializers,\
                                 ucode_initializers,\
                                 runtime_initializers>
                                 ;wdb_initializers,\
;
; Microcode updates must be aligned on a paragraph boundary. If more
; than microcode update is included in the microcode storage block,
; each microcode update be forced to to align on paragraph boundary.
align 16
PUBLIC microcode_start
PUBLIC microcode_size
; This is the microcode update region that will be searched and loaded
; CPU reference code.
microcode_start label byte
   ; The OEM is required to specify the microcode updates here
   ;
   ; INCLUDE CpuMicrocodeUpdate.inc ; Example line for Microcode Update inclusion
microcode_size EQU ($-microcode_start)

.code

CrcSetup PROC

externdef   CrcStart:NEAR32

   mov   ebp, offset rom_options    ; Set pointer to default options structure
   jmp   CrcStart                   ; Call CPU reference code

  ; Label for the return address
CrcExitAddress::
   jmp   $

CrcSetup ENDP

END
