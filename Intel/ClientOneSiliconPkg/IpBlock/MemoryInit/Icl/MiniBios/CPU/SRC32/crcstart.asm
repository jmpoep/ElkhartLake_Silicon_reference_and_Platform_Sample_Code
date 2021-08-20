;;@file
;   CrcStart is the entry for the CPU Reference Code.
;   Do not modify CRC.H. The CPU Reference Code uses all a ROM-based
;   setup options structure which is instantiated in CRCSETUP.ASM.
;   OEM should only modify CRCOEMHOOK.ASM, CRCOEM.INC, or CRCSETUP.ASM.
;
;@copyright
; Copyright (c) 2007 - 2018 Intel Corporation. All rights reserved
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


;------------------------------------------------------------------------------
; Notes:
;
;  Input Parameters:
;    [esp]   = Return address
;    [esp+4] = ROM-based CRC setup options structure
;              Defined CRC.H and instantiated in CRCSETUP.ASM.
;              Do not modify CRC.H. The ROM-based setup options structure
;              is instantiated in CRCSETUP.ASM and should only be modified
;              in that file.
;
;  MMX Usage:
;     MM0 = Processor-specific BIST State
;     MM1 = Current Package Physical Info
;        [31:24] = Reserved
;        [23:16] = Reserved
;        [15:8]  = Reserved
;        [7:0]   = Bus number
;     MM2 = Current Platform Info
;        [31:24] = Reserved
;        [23:16] = Reserved
;        [15:8]  = Reserved
;        [7:0]   = Count CPU packages or Node BSP (NBSP) detected
;     MM3 = Processor-specific Local Barrier
;        [31]    = Local Barrier Flag
;        [30:24] = Reserved
;        [23:16] = Reserved
;        [15:8]  = Reserved
;        [7:0]   = Reserved
;     MM4 = Reserved
;     MM5 = Reserved
;     MM6 = Reserved
;     MM7 = Reserved
;
;  IOH Scratch pad register Usage:
;     IR[00] = SBSP Selection
;     SR[00] = SBSP Selection
;     SR[01] = Reset information
;        [31:2] = Reserved
;        [1]    = Powergood Reset
;        [0]    = CPU-only Reset
;     SR[02] = Store CPU0 info
;     SR[03] = Store CPU1 info
;     SR[04] = Store CPU2 info
;     SR[05] = Store CPU3 info
;     IR[06] = Get Spinlock
;     SR[06] = Test Spinlock
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
   .listall
   .686p
   .xmm
   .model   flat,c

.XLIST
   ; Files generated during build time...do not edit!!!
   include crc.i
.LIST

INCLUDE crcmacros.inc
INCLUDE crcoem.inc

EXTERN _PrintExceptionDetails:NEAR32

.data
   DD    12345678h

.const

;
; Error code flag indicating whether or not an error code will be
; pushed on the stack if an exception occurs.
; 1 means an error code will be pushed, otherwise 0
;
mErrorCodeFlag  DWORD  00027D00h

;
; List of MTRR's to zero
;
Public MtrrInitTable
MtrrInitTable LABEL BYTE
   DW    MTRR_DEF_TYPE
   DW    MTRR_FIX_64K_00000
   DW    MTRR_FIX_16K_80000
   DW    MTRR_FIX_16K_A0000
   DW    MTRR_FIX_4K_C0000
   DW    MTRR_FIX_4K_C8000
   DW    MTRR_FIX_4K_D0000
   DW    MTRR_FIX_4K_D8000
   DW    MTRR_FIX_4K_E0000
   DW    MTRR_FIX_4K_E8000
   DW    MTRR_FIX_4K_F0000
   DW    MTRR_FIX_4K_F8000
   DW    MTRR_PHYS_BASE_0
   DW    MTRR_PHYS_MASK_0
   DW    MTRR_PHYS_BASE_1
   DW    MTRR_PHYS_MASK_1
   DW    MTRR_PHYS_BASE_2
   DW    MTRR_PHYS_MASK_2
   DW    MTRR_PHYS_BASE_3
   DW    MTRR_PHYS_MASK_3
   DW    MTRR_PHYS_BASE_4
   DW    MTRR_PHYS_MASK_4
   DW    MTRR_PHYS_BASE_5
   DW    MTRR_PHYS_MASK_5
   DW    MTRR_PHYS_BASE_6
   DW    MTRR_PHYS_MASK_6
   DW    MTRR_PHYS_BASE_7
   DW    MTRR_PHYS_MASK_7

MtrrCount      EQU (($ - MtrrInitTable) / 2)

.code

Public CrcWakeNBSP
CrcWakeNBSP::
Public CrcWakeAP
CrcWakeAP::

CrcStart PROC

  ; Inputs:
  ;   ebp -> ROM-based cpu_setup_options structure
  ;
  ; Register Usage:
  ;   All others destroyed
  ;
  ; Assumptions:
  ;   No memory available, stack is hard-coded and used for return address
  ;   Executed by SBSP and NBSP
  ;

  ; Init PCIE_BAR with value.
  mov dx, 0cf8h
  mov eax, 080000000h OR (0 SHL 16) OR (0 SHL 11) OR (0 SHL 8) OR (060h) ; PCIEBAR IO Base
  out dx, eax
  mov dx, 0cfch
  mov eax, PCIE_BAR_BASE
  inc eax          ; Set Enable bit
  out dx, eax

  ; Set MCHBAR
  mov edi, PCIE_BAR_BASE OR (0 SHL 20) OR (0 SHL 15) OR (0 SHL 12) OR 48h  ; 0:0:0:48
  mov DWORD PTR [edi], MCH_BAR_BASE OR 1  ; Set the Enable bit.

  ; Set DMIBAR
  mov edi, PCIE_BAR_BASE OR (0 SHL 20) OR (0 SHL 15) OR (0 SHL 12) OR 68h  ; 0:0:0:68
  mov DWORD PTR [edi], DMI_BAR_BASE OR 1  ; Set the Enable bit.

  ; Assume ICL PCH

  ;
  ; Program PCH SBREG Base Address
  ;
  mov  edi, PCIE_BAR_BASE + (0 SHL 20) OR (31 SHL 15) OR (1 SHL 12)  ; 0:1F:1
  mov  DWORD PTR [edi + 10h], PCH_PCR_BASE_ADDRESS
  or  BYTE PTR [edi + 4], BIT1      ; Enable the MSE bit for MMIO decode.

  ;
  ; Initialize SMBUS controller
  ;
  mov  edi, PCIE_BAR_BASE + (0 SHL 20) OR (31 SHL 15) OR (4 SHL 12)  ; 0:1F:4 - SMBus controller
  mov  DWORD PTR [edi + 20h], SMBUS_BASE OR 1  ; Program SMBUS base address, set the Enable bit.
  mov  DWORD PTR [edi + 40h], 1    ; HST_EN: When set, the SMB Host Controller interface is enabled to execute commands.
  or  WORD PTR [edi + 4h], 1      ; PCICMD - set I/O Space Enable

  mov  DWORD PTR [edi + 50h], TCO_BASE_ADDRESS  ; TCOBASE - Program TCO base address
  or  DWORD PTR [edi + 54h], BIT8    ; TCOCTL[8] - TCO base enable
  mov  edi, PCH_PCR_BASE_ADDRESS + (PID_DMI SHL 16) + 02778h  ; PID_DMI and R_PCH_PCR_DMI_TCOBASE
  mov  WORD PTR [edi], TCO_BASE_ADDRESS OR 3
  mov  ax, WORD PTR [edi]      ; Read back after a PCR write

  ;
  ; Program PCH PMC MBAR Base Address and ACPI Base Address (PMBASE)
  ;
  mov  edi, PCIE_BAR_BASE + (0 SHL 20) OR (31 SHL 15) OR (2 SHL 12)  ; 0:1F:2 - PMC controller
  mov  DWORD PTR [edi + 10h], PCH_PWRM_BASE_ADDRESS
  or  BYTE PTR [edi + 04h], BIT1    ; PWRM enable

  ; With PSF3, we no longer need to shadow PMBASE or ACPI Base
  mov  edi, PCH_PCR_BASE_ADDRESS + (0BCh SHL 16)  ; PID_PSF3
  mov  eax, 0a00h  ; CNL-H value
  mov  ebx, 1400h  ; CNL-LP value
  or  ecx, ecx     ; CNL-LP ?
  cmovz  eax, ebx  ; move if yes
  add  edi, eax
  mov  DWORD PTR [edi + 10h], ACPI_BASE_ADDRESS
  or  BYTE PTR [edi + 1Ch], BIT0      ;Enable ACPIBAR

CommonPch:
  ;
  ; Halt the TCO Timer
  ;
  mov  dx, TCO_BASE_ADDRESS + 8h
  in  ax, dx
  or  ax, (1 SHL 11)
  out  dx, ax        ; Set bit [11] in TCTL1

PchDone:
   mov   eax, CRC_START
   CALL_STACK oemStacklessStatusCode

   ; Early Microcode Update Loading
   ; (executed by all BSP)
   CALL_STACK  LoadUcode

   mov   eax, CRC_UCODE_DONE
   CALL_STACK oemStacklessStatusCode

   ; Enable cache to be used for code and data (NEM)
   CALL_STACK NemInit

   mov   eax, CRC_NEM_DONE
   CALL_STACK oemStacklessStatusCode

   ; Establish stack
   mov   esp, [ebp].cpu_setup_options.nem_data_addr
   add   esp, [ebp].cpu_setup_options.nem_data_size

   ;
   ; Set up an IDT with exception handlers
   ;
   mov   esi, OFFSET IdtInitDone
   jmp   IdtInit
IdtInitDone:
   ;
   ; Using a local stack frame to simplify the changes to this routine
   ; First save address of ROM-based options structure
   ; Then create a new stack frame
   ; Finally make room for local variables on the stack
   push  ebp
   mov   ebp, esp
   sub   esp, 4 + sizeof cpu_setup_options

   rom_options_ptr   TEXTEQU <dword ptr [ebp]>
   nem_options_ptr   TEXTEQU <dword ptr [ebp-4]>
   nem_options       TEXTEQU <dword ptr [ebp-4-sizeof cpu_setup_options]>

   ; At this point all code is 32-bit C-based routines which expect pointers
   ; to the CPU setup options structure. For example, EBP now contains a
   ; pointer to the ROM location of the CPU options structure and not actual
   ; ROM location. Remember to dereference this pointer if a register needs
   ; to point directly at the CPU options structure.

   ; Note:  Assembly macros and procedures which expect a register which
   ; references the ROM-based, nem-based, or memory-based CPU options
   ; structure should must ensure a dereferenced pointer is used and not the
   ; pointer itself.

   ; Create pointer for NEM-based memory options structure
   lea   ebx, nem_options
   mov   nem_options_ptr, ebx

   ; Copy ROM-based cpu options structure to stack-based cpu options structure
   ; Push parameters from right to left (stack-based then ROM-based addresses)
   push  nem_options_ptr
   push  rom_options_ptr
   extern InitCpuOptions:NEAR32
   call  InitCpuOptions
   add   esp, 8

   ; Move any information from chipset scratch pad registers
   ; into the cpu options structure in NEM-based memory
   ;lea   ebx, nem_options
   ;GET_RESET_FLAGS   eax, ebx
   ;mov   nem_options.cpu_setup_options.resets_required, eax

   ; (Optional) Validation BIOS Hook

   ; Force Max Ratio
   ; (executed by SBSP only)
   ;extern cForceMaxRatio:NEAR32
   ;call  cForceMaxRatio


IFDEF CONFIG_MEMORY
   mov   eax, CRC_MRC
   call  oemStacklessStatusCode

   ; Setup for Memory Reference Code (MRC)
   ; Call Memory Reference Code (MRC)
   push  nem_options_ptr
   extern _prepareToCallMemRefCode:NEAR32
   call _prepareToCallMemRefCode
   add   esp, 4

ENDIF

   mov   eax, CRC_RESET_CHECK
   call  oemStacklessStatusCode

   ; Now go check how much of NEM data/stack region memory we have used up.
   ; The procedure returns with EAX = number of bytes of stack
   push  rom_options_ptr
   call  _CheckNemDataStackDepth
   add   esp, 4                     ; Clear input parameter


   ; Make preparations since NEM memory is going away
   ; Move stack's location into physical memory
   ; Save address of NEM memory-based options structure in ebp
   mov   esp, nem_options.cpu_setup_options.mem_data_addr;
   lea   ebp, nem_options

   ; Using a local stack frame to simplify the changes to this routine
   ; First save address of NEM memory-based options structure
   ; Then create a new stack frame
   ; Finally make room for local variables on the stack
   push  ebp
   mov   ebp, esp
   sub   esp, 4 + sizeof cpu_setup_options

   nem_options_ptr   TEXTEQU <dword ptr [ebp]>
   mem_options_ptr   TEXTEQU <dword ptr [ebp-4]>
   mem_options       TEXTEQU <dword ptr [ebp-4-sizeof cpu_setup_options]>

   ; At this point all code is 32-bit C-based routines which expect pointers
   ; to the CPU setup options structure. For example, EBP now contains a
   ; pointer to the ROM location of the CPU options structure and not actual
   ; ROM location. Remember to dereference this pointer if a register needs
   ; to point directly at the CPU options structure.

   ; Note:  Assembly macros and procedures which expect a register which
   ; references the ROM-based, nem-based, or memory-based CPU options
   ; structure should must ensure a dereferenced pointer is used and not the
   ; pointer itself.

   ; Create pointer for mem-based options structure
   lea   ebx, mem_options
   mov   mem_options_ptr, ebx

   ; Copy NEM-based options structure to the memory-based options structure
   ; Push parameters from right to left (mem-based then nem-based addresses)
   push  mem_options_ptr
   push  nem_options_ptr
   externdef InitCpuOptions:NEAR32
   call  InitCpuOptions
   add   esp, 8

   ; Disable No-Eviction Mode (NEM)
   externdef NemExit:NEAR32
   call  NemExit

   mov   eax, CRC_EXIT
   call  oemStacklessStatusCode

   jmp   mem_options.cpu_setup_options.crc_exit_addr

CrcStart ENDP

;------------------------------------------------------------------------------
LoadUcode   PROC

   ; Inputs:
   ;   esp -> stack with return address
   ;   ebp -> ROM-based cpu_setup_options structure
   ; Register Usage:
   ;   esp  Preserved
   ;   ebp  Preserved
   ;   All others destroyed
   ; Assumptions:
   ;   No memory available, stack is hard-coded and used for return address
   ;   Executed by SBSP and NBSP
   ;   Beginning of microcode update region starts on paragraph boundary

   ; Start at OEM ucode region address
   mov   esi, [ebp].cpu_setup_options.ucode_region_addr

   ; Get processor signature and platform ID from the installed processor
   ; and save into registers for later use
   ; ebx = processor signature
   ; edx = platform ID
   mov   eax, 1
   cpuid
   mov   ebx, eax
   mov   ecx, MSR_IA32_PLATFORM_ID
   rdmsr
   mov   ecx, edx
   shr   ecx, 50-32
   and   ecx, 7h
   mov   edx, 1
   shl   edx, cl

   ; Current register usage
   ; esp -> stack with return address
   ; ebp -> ROM-based cpu_setup_options structure
   ; esi -> microcode update to check
   ; ebx = processor signature
   ; edx = platform ID

check_main_header:
   ; Check for valid microcode header
   ; Minimal test checking for header version and loader version as 1
   mov   eax, dword ptr 1
   cmp   [esi].ucode_hdr.version, eax
   jne   advance_fixed_size
   cmp   [esi].ucode_hdr.loader, eax
   jne   advance_fixed_size

   ; Check if signature and plaform ID match
   cmp   ebx, [esi].ucode_hdr.processor
   jne   @f
   test  edx, [esi].ucode_hdr.flags
   jnz   load_check  ; Jif signature and platform ID match

@@:
   ; Check if extended header exists
   ; First check if total_size and data_size are valid
   xor   eax, eax
   cmp   [esi].ucode_hdr.total_size, eax
   je    next_microcode
   cmp   [esi].ucode_hdr.data_size, eax
   je    next_microcode

   ; Then verify total size - sizeof header > data size
   mov   ecx, [esi].ucode_hdr.total_size
   sub   ecx, sizeof ucode_hdr
   cmp   ecx, [esi].ucode_hdr.data_size
   jbe   next_microcode    ; Jif extended header does not exist

   ; Check if total size fits in microcode region
   mov   edi, esi
   add   edi, [esi].ucode_hdr.total_size
   mov   ecx, [ebp].cpu_setup_options.ucode_region_addr
   add   ecx, [ebp].cpu_setup_options.ucode_region_size
   cmp   edi, ecx
   ja    exit              ; Jif address is outside of ucode region

   ; Set edi -> extended header
   mov   edi, esi
   add   edi, sizeof ucode_hdr
   add   edi, [esi].ucode_hdr.data_size

   ; Get count of extended structures
   mov   ecx, [edi].ext_sig_hdr.count

   ; Move pointer to first signature structure
   add   edi, sizeof ext_sig_hdr

check_ext_sig:
   ; Check if extended signature and platform ID match
   cmp   [edi].ext_sig.processor, ebx
   jne   @f
   test  [edi].ext_sig.flags, edx
   jnz   load_check     ; Jif signature and platform ID match
@@:
   ; Check if any more extended signatures exist
   add   edi, sizeof ext_sig
   loop  check_ext_sig

next_microcode:
   ; Advance just after end of this microcode
   xor   eax, eax
   cmp   [esi].ucode_hdr.total_size, eax
   je    @f
   add   esi, [esi].ucode_hdr.total_size
   jmp   check_address
@@:
   add   esi, dword ptr 2048
   jmp   check_address

advance_fixed_size:
   ; Advance by 4X dwords
   add   esi, dword ptr 1024

check_address:
   ; Address >= microcode region address + microcode region size?
   mov   eax, [ebp].cpu_setup_options.ucode_region_addr
   add   eax, [ebp].cpu_setup_options.ucode_region_size
   cmp   esi, eax
   jae   exit        ;Jif address is outside of ucode region
   jmp   check_main_header

load_check:
   ; Get the revision of the current microcode update loaded
   mov   ecx, MSR_IA32_BIOS_SIGN_ID
   xor   eax, eax               ; Clear EAX
   xor   edx, edx               ; Clear EDX
   wrmsr                        ; Load 0 to MSR at 8Bh

   mov   eax, 1
   cpuid
   mov   ecx, MSR_IA32_BIOS_SIGN_ID
   rdmsr                         ; Get current microcode signature

   ; Verify this microcode update is not already loaded
   cmp   [esi].ucode_hdr.revision, edx
   je    exit

load_microcode:
   ; EAX contains the linear address of the start of the Update Data
   ; EDX contains zero
   ; ECX contains 79h (IA32_BIOS_UPDT_TRIG)
   ; Start microcode load with wrmsr
   mov   eax, esi
   add   eax, sizeof ucode_hdr
   xor   edx, edx
   mov   ecx, MSR_IA32_BIOS_UPDT_TRIG
   wrmsr

exit:
   ret

LoadUcode   ENDP

;----------------------------------------------------------------------------
;
;  NemInit
;
;  Purpose:
;  Enable cache for use as stack and for caching code
;  Initializes the cache configuration as specified in
;  the BIOS Writer's Guide for No-Eviction Mode (NEM).
;
;  Assumptions:
;  (1) System is in flat 32 bit protected mode.
;  (2) Microcode update has been loaded into the SBSP and NBSP
;  (3) Only one logical processor in the system is the BSP (called the SBSP)
;  (4) Only SBSP executes this routine
;  (5) Stack is not available
;
;  Inputs:
;     EBP -> ROM-based cpu_setup_options structure
;     ESP -> return address to calling code
;
;  Outputs:
;     Preserved: esp, ebp
;     Destroyed: all other registers
;
;----------------------------------------------------------------------------
NemInit   PROC

   ;
   ;  Check if NEM is already enabled in NO_EVICT_MODE MSR 2E0h bits [1:0]
   ;  This is the case when MiniBios is loaded via NEM
   ;
   mov   ecx, MSR_NO_EVICT_MODE
   rdmsr
   test  eax, 3
   jnz   DataStackInit

   ;  Ensure all APs are in the Wait for SIPI state.
   ;  This includes all other logical processors in the same physical processor
   ;  as the BSP and all logical processors in other physical processors.
   ;  If any APs are awake, the BIOS must put them back into the Wait for
   ;  SIPI state by issuing a broadcast INIT IPI to all excluding self.
;   mov   ecx, MSR_APIC_BASE
;   rdmsr
;   and   eax, dword ptr not 0FFFh
;   add   eax, APIC_ICR_LO
;   mov   esi, eax
;   mov   [esi], dword ptr 0000C4500h   ; Broadcast INIT IPI

;@@:
   ; Wait until broadcast INIT IPI has completed
;   mov   eax, [esi]
;   bt    eax, 12         ; Check if send is in progress
;   jc    @B              ; Loop until idle

   ;   Ensure that all variable-range MTRR valid flags are clear and
   ;   IA32_MTRR_DEF_TYPE MSR E flag is clear.  Note: This is the default state
   ;   after hardware reset.
   ;
   ;   Platform Specific - MTRR are usually in default state.

   ;   Initialize all fixed-range and variable-range MTRR register fields to 0.
   ;
   xor   eax, eax                   ; Clear the low dword to write
   xor   edx, edx                   ; Clear the high dword to write
   mov   ebx, MtrrCount * 2         ; ebx <- sizeof MtrrInitTable
InitMtrrLoop:
   add   ebx, -2
   movzx ecx, word ptr MtrrInitTable[ebx] ; ecx <- address of mtrr to zero
   wrmsr
   jnz   InitMtrrLoop               ; loop through the whole table

   ; Configure the default memory type to un-cacheable (UC) in the
   ; IA32_MTRR_DEF_TYPE MSR.
   ;
   mov   ecx, MTRR_DEF_TYPE         ; Load the MTRR default type index
   rdmsr
   and   eax, NOT (00000CFFh)       ; Clear the enable bits and def type UC.
   wrmsr

   ; Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
   ; based on the physical address size supported for this processor
   ; This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
   ;
   ; Examples:
   ;  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
   ;  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
   ;
   mov   eax, 80000008h             ; Address sizes leaf
   cpuid
   sub   al, 32
   movzx eax, al
   xor   esi, esi
   bts   esi, eax
   dec   esi                        ; esi <- MTRR_PHYS_MASK_HIGH

   ;  Configure the DataStack region as write-back (WB) cacheable memory type
   ;  using the variable range MTRRs.
   ;

   ; Set the base address of the DataStack cache range
   ;
   mov   eax, [ebp].cpu_setup_options.nem_data_addr
   or    eax, MTRR_MEMORY_TYPE_WB
                                    ; Load the write-back cache value
   xor   edx, edx                   ; clear upper dword
   mov   ecx, MTRR_PHYS_BASE_0      ; Load the MTRR index
   wrmsr                            ; the value in MTRR_PHYS_BASE_0

   ;  Set the mask for the DataStack cache range
   ;  Use the DATA_STACK_SIZE_MASK which is (NOT (DATA_STACK_SIZE - 1))
   ;
   mov   eax, [ebp].cpu_setup_options.nem_data_size
   dec   eax
   not   eax
   or    eax, MTRR_PHYS_MASK_VALID
                                    ; turn on the Valid flag
   mov   edx, esi                   ; edx <- MTRR_PHYS_MASK_HIGH
   mov   ecx, MTRR_PHYS_MASK_0      ; Load the MTRR index
   wrmsr                            ; the value in MTRR_PHYS_BASE_0

   ;  Configure the BIOS code region as write-protected (WP) cacheable
   ;  memory type using a single variable range MTRR.
   ;
   ;  Platform Specific - ensure region to cache meets MTRR requirements for
   ;  size and alignment.

   ;  Set the base address of the CodeRegion cache range
   ;
   mov   eax, [ebp].cpu_setup_options.nem_code_addr
   or    eax, MTRR_MEMORY_TYPE_WP   ; Load the write-protected cache value
;   or    eax, MTRR_MEMORY_TYPE_UC

   xor   edx, edx                   ; Clear upper dword
   mov   ecx, MTRR_PHYS_BASE_1      ; Load the MTRR index
   wrmsr                            ; the value in MTRR_PHYS_BASE_1

   ;  Set the mask for the CodeRegion cache range
   ;  Use the CODE_SIZE_MASK which is (NOT (CODE_SIZE - 1))
   ;
   mov   eax, [ebp].cpu_setup_options.nem_code_size
   dec   eax
   not   eax
   or    eax, MTRR_PHYS_MASK_VALID
                                    ; turn on the Valid flag
   mov   edx, esi                   ; edx <- MTRR_PHYS_MASK_HIGH
   mov   ecx, MTRR_PHYS_MASK_1      ; Load the MTRR index
   wrmsr                            ; the value in MTRR_PHYS_MASK_1

   ;  Enable the MTRRs by setting the IA32_MTRR_DEF_TYPE MSR E flag.
   ;
   mov   ecx, MTRR_DEF_TYPE               ; Load the MTRR default type index
   rdmsr
   or    eax, MTRR_DEF_TYPE_E             ; Enable variable range MTRRs
   wrmsr

   ;  Enable the logical processor's (BSP) cache: execute INVD and set
   ;  CR0.CD = 0, CR0.NW = 0.
   ;
   mov   eax, cr0
   and   eax, NOT (CR0_CACHE_DISABLE + CR0_NO_WRITE)
   invd
   mov   cr0, eax

   ;  Enable No-Eviction Mode Setup State by setting
   ;  NO_EVICT_MODE MSR 2E0h bit [0] = '1'.
   ;
   mov   ecx, MSR_NO_EVICT_MODE
   rdmsr
   or    eax, 1
   wrmsr

DataStackInit:
   ;  One location in each 64-byte cache line of the DataStack region
   ;  must be written to set all cache values to the modified state.
   ;
   mov   edi, [ebp].cpu_setup_options.nem_data_addr
   mov   ecx, [ebp].cpu_setup_options.nem_data_size
   shr   ecx, 6      ; Divide by 64
   mov   eax, CACHE_INIT_VALUE
@@:
   mov   [edi], eax
   add   edi, 64
   loopd   @b

   ;  Enable No-Eviction Mode Run State by setting
   ;  NO_EVICT_MODE MSR 2E0h bit [1] = '1'.
   ;
   mov     ecx, MSR_NO_EVICT_MODE
   rdmsr
   or      eax, 2
   wrmsr

   ;
   ;  Finished with cache configuration
   ;

   ;
   ;  Optionally Test the Region...
   ;

   ;
   ;  Test area by writing and reading
   ;
   cld
   mov   edi, [ebp].cpu_setup_options.nem_data_addr
   mov   ecx, [ebp].cpu_setup_options.nem_data_size
   shr   ecx, 2      ; Divide by 4
   mov   eax, CACHE_TEST_VALUE
TestDataStackArea:
   stosd
   cmp   eax, DWORD PTR [edi-4]
   jnz   DataStackTestFail
   loop  TestDataStackArea

   ;
   ; Test the inverse pattern
   ;
   mov   edi, [ebp].cpu_setup_options.nem_data_addr
   mov   ecx, [ebp].cpu_setup_options.nem_data_size
   shr   ecx, 2      ; Divide by 4
   mov   eax, NOT (CACHE_TEST_VALUE)
TestDataStackArea2:
   stosd
   cmp   eax, DWORD PTR [edi-4]
   jnz   DataStackTestFail2
   loop  TestDataStackArea2
   jmp   DataStackTestPass

   ;
   ; Cache test failed
   ;
DataStackTestFail:
   mov eax, 0D0h ; CRC_NEM_FAILURE
   ;mov eax, 0D0h
   CALL_STACK oemStacklessStatusCode
   jmp     $

DataStackTestFail2:
   mov eax, 0D1h ;
   CALL_STACK oemStacklessStatusCode
   jmp     $

DataStackTestPass:

   ;
   ; At this point you may continue normal execution.  Typically this would include
   ; reserving stack, initializing the stack pointer, etc.
   ;

   ;
   ; After memory initialization is complete, please follow the algorithm in the BIOS
   ; Writer's Guide to properly transition to a normal system configuration.
   ; The algorithm covers the required sequence to properly exit this mode.
   ;

   ret

NemInit   ENDP

;----------------------------------------------------------------------------
;
;  NemExit
;
;  Purpose:
;   Exits the cache configuration as specified in
;   the BIOS Writer's Guide for No-Eviction Mode (NEM).
;
;  Assumptions:
;  (1) Processor operating mode is flat 32-bit protected mode.
;  (2) Only SBSP executes this routine
;  (3) Stack is available
;  (4) Any NEM-based data required by the BIOS must be copied to the initial
;      system memory.  The initial system memory must be in the un-cacheable
;      (UC) state.
;
;  Inputs:
;     ebp -> memory-based cpu_setup_options structure
;     esp -> return address to calling code
;
;  Outputs:
;     Preserved: esp, ebp, esi
;     Destroyed: all other registers
;
;----------------------------------------------------------------------------
NemExit   PROC

   ;  Disable the MTRRs by clearing the IA32_MTRR_DEF_TYPE MSR E flag.
   ;
   mov   ecx, MTRR_DEF_TYPE            ; Load the MTRR default type index
   rdmsr
   and   eax, NOT (DWORD PTR MTRR_DEF_TYPE_E)   ; Disable all MTRRs
   wrmsr

   ;  Disable No-Eviction Mode Run State by clearing
   ;  NO_EVICT_MODE MSR 2E0h bit [1] = 0.
   ;
   mov   ecx, MSR_NO_EVICT_MODE
   rdmsr
   btr   eax, 1
   wrmsr

   ;  Disable No-Eviction Mode Setup State by clearing
   ;  NO_EVICT_MODE MSR 2E0h bit [0] = 0.
   ;
   rdmsr
   btr   eax, 0
   wrmsr

   ;  Invalidate the cache.  Execute the INVD instruction to flush the cache.
   ;  After this point, cache data is no longer valid.
   ;
   invd

   ;  Configure system memory and cache as specified in the IA-32 Intel (R) Architecture
   ;  Software Developer's Manual, Volume 3: System Programming Guide.  E.G. initialize
   ;  any remaining memory and MTRRs and enable cache by setting CR0.CD = 0.
   ;

   ;  Continue with POST.
   ;
   ret

NemExit  ENDP


;------------------------------------------------------------------------------
; _CheckNemDataStackDepth
;
; Check how much of NEM data/stack region memory we have used up.
; Do not enable stack check except in test environment!
;
; Input:
;       Processor Operating Mode: 32-bit flat mode,
;       32-bit addressability from 0 thru 4GB.
;       CS = Flat-mode segment address of the segment this code is executing out of.
;       DS = Selector that points to a descriptor with
;               Base  = 000000000h
;               Limit = 0FFFFFFFFh
;               Present, DPL = 0, Expand-up, Read-Write, Granularity = 4K
;       ES, SS, FS, GS = Same settings as DS.
;
; Output:
;       EAX = Amount of stack consumed
;       Hangs with jmp $ if stack overflow is detected.
;
; Destroys:
;       EAX, EBX, ECX, EDX, ESI, EDI, EBP.
;       Processor MTRRs as needed.
;
; Note:
;------------------------------------------------------------------------------
_CheckNemDataStackDepth  PROC    NEAR    PUBLIC
   extern _printStackDepth:NEAR32

   mov   ebx, dword ptr [esp+4]  ; Get input parameter
   ;
   ; Inputs:  EBP points to ROM- or memory-based cpu_setup_options structure
   ;

   mov   esi, [ebx].cpu_setup_options.nem_data_addr
   add   esi, [ebx].cpu_setup_options.nem_data_size
   cld
   mov   edi, [ebx].cpu_setup_options.nem_data_addr
   add   edi, 0ch         ; BIOS stores number of reads and writes at DATA_BASE
   mov   ecx, [ebx].cpu_setup_options.nem_data_size
   shr   ecx, 2      ; Divide by 4
   mov   eax, CACHE_TEST_VALUE    ; Stack was filled with this value in NemInit
   repe  scas DWORD PTR es:[edi]

   sub   edi, 4        ; EDI was incremented after the mismatch.

   mov   eax, edi                       ; Debug purposes
;   out   80h, eax                       ; Debug purposes

   mov   eax, esi
;   out   80h, eax                       ; Debug purposes
   sub   eax, edi

   ;
   ; Stack depth in EAX
   ;

   cmp   eax, [ebx].cpu_setup_options.nem_data_size - 0ch ; Doesn't account for heap usage
   jb    Exit        ; Jump if stack overflow not detected

   ; Display stack usage across debug
   push  eax
   call  _printStackDepth
   add   esp, 4

   mov   ax, 0BADFh
   out   80h, ax
   jmp   $        ; Stack overflow detected!

Exit:
;   out   80h, ax      ; Show stack usage on Port80

; Display stack usage across debug
   push  eax
   call  _printStackDepth
   add   esp, 4

;   mov   dx, 0CF9h
;   mov   al, 0Eh
;   out   dx, al

   mov   ecx, MTRR_DEF_TYPE            ; Load the MTRR default type index
   rdmsr
   or    eax, MTRR_MEMORY_TYPE_WB               ; Set default to Write-Back
   wrmsr

   mov   ax, 0055h
   out   80h, ax
   jmp   $        ; MRC done !

   ret

_CheckNemDataStackDepth  ENDP

;------------------------------------------------------------------------------
;
; Create IDT on the stack and set IDTR.
; Must be called without using "call" instruction because IDT stays on the stack.
;
; Input:
;       Processor Operating Mode: 32-bit flat mode
;       32-bit addressability from 0 thru 4GB.
;  Stack is available.
;       CS = Flat-mode segment address of the segment this code is executing out of.
;       DS = Selector that points to a descriptor with
;               Base  = 000000000h
;               Limit = 0FFFFFFFFh
;               Present, DPL = 0, Expand-up, Read-Write, Granularity = 4K
;       ES, SS, FS, GS = Same settings as DS.
;  ESI - Return address
;
;------------------------------------------------------------------------------
IdtInit PROC
  and  esp, 0FFFFFFF8h    ; Align IDT on 8 bytes boundary

  mov  edi, OFFSET IdtHandlerTable
  mov  ecx, IDT_ENTRY_COUNT  ; IDT has 20 entries

NextHandler:
  mov  eax, [edi]    ; Current interrupt handler offset
  mov  ebx, eax
  mov  ax, 8E00h    ; 32-bit Interrupt Gate descriptor
  push  eax      ; High DWORD
  ror  ebx, 16
  mov  bx, 8      ; LINEAR_CODE_SEL
  ror  ebx, 16
  push  ebx      ; Low DWORD

  add  edi, 4
  loop  NextHandler

  mov  eax, esp    ; IDT base address
  push  eax
  mov  eax, ((IDT_ENTRY_COUNT * 8) - 1) SHL 16  ; IDT limit = 0x9F, put it into high word
  push  eax

  lidt  FWORD PTR [esp + 2]
  jmp  esi
IdtInit ENDP

;IdtDescriptor LABEL WORD
;  DW  IDT_SIZE - 1      ; IDT limit
;  DD      OFFSET IdtTable      ; IDT base address

IdtHandlerTable LABEL DWORD
DWORD  OFFSET Int19
DWORD  OFFSET Int18
DWORD  OFFSET Int17
DWORD  OFFSET Int16
DWORD  OFFSET Int15
DWORD  OFFSET Int14
DWORD  OFFSET Int13
DWORD  OFFSET Int12
DWORD  OFFSET Int11
DWORD  OFFSET Int10
DWORD  OFFSET Int9
DWORD  OFFSET Int8
DWORD  OFFSET Int7
DWORD  OFFSET Int6
DWORD  OFFSET Int5
DWORD  OFFSET Int4
DWORD  OFFSET Int3
DWORD  OFFSET Int2
DWORD  OFFSET Int1
DWORD  OFFSET Int0

IDT_ENTRY_COUNT  EQU ($ - IdtHandlerTable) / SIZEOF DWORD

Int0:  push  0      ; #DE - Divide Error
  jmp  CommonInterruptEntry

Int1:  push  1      ; #DB - Reserved
  jmp  CommonInterruptEntry

Int2:  push  2      ; NMI Interrupt
  jmp  CommonInterruptEntry

Int3:  push  3      ; #BP - Breakpoint
  jmp  CommonInterruptEntry

Int4:  push  4      ; #OF - Overflow
  jmp  CommonInterruptEntry

Int5:  push  5      ; #BR - BOUND Range Exceeded
  jmp  CommonInterruptEntry

Int6:  push  6      ; #UD - Invalid Opcode (Undefined  Opcode)
  jmp  CommonInterruptEntry

Int7:  push  7      ; #NM - Device Not Available (No Math Coprocessor)
  jmp  CommonInterruptEntry

Int8:  push  8      ; #DF - Double Fault
  jmp  CommonInterruptEntry

Int9:  push  9      ; Coprocessor Segment Overrun (reserved)
  jmp  CommonInterruptEntry

Int10:  push  10      ; #TS - Invalid TSS
  jmp  CommonInterruptEntry

Int11:  push  11      ; #NP - Segment Not Present
  jmp  CommonInterruptEntry

Int12:  push  12      ; #SS - Stack-Segment Fault
  jmp  CommonInterruptEntry

Int13:  push  13      ; #GP - General Protection Fault
  jmp  CommonInterruptEntry

Int14:  push  14      ; #PF - Page Fault
  jmp  CommonInterruptEntry

Int15:  push  15      ; Reserved
  jmp  CommonInterruptEntry

Int16:  push  16      ; #MF - x87 FPU Floating-Point Error (Math Fault)
  jmp  CommonInterruptEntry

Int17:  push  17      ; #AC - Alignment Check
  jmp  CommonInterruptEntry

Int18:  push  18      ; #MC - Machine Check
  jmp  CommonInterruptEntry

Int19:  push  19      ; #XM - SIMD floating point exception
  jmp  CommonInterruptEntry

;----------------------------------------------------------------------------;
; CommonInterruptEntry                                                               ;
;----------------------------------------------------------------------------;
; The follow algorithm is used for the common interrupt routine.
; Entry from each interrupt with a push eax and eax=interrupt number
; Stack:
; +---------------------+
; +    EFlags           +
; +---------------------+
; +    CS               +
; +---------------------+
; +    EIP              +
; +---------------------+
; + Possible Error Code +
; +---------------------+
; +    Vector Number    +
; +---------------------+ <-- ESP
;
CommonInterruptEntry PROC
    cli
    ;
    ; Get vector number from top of stack
    ;
    xchg    ecx, [esp]
    and     ecx, 0FFh       ; Vector number should be less than 256
    cmp     ecx, 32         ; Intel reserved vector for exceptions?
    jae     NoErrorCode
    bt      mErrorCodeFlag, ecx
    jc      HasErrorCode

NoErrorCode:
    ;
    ; Stack:
    ; +---------------------+
    ; +    EFlags           +
    ; +---------------------+
    ; +    CS               +
    ; +---------------------+
    ; +    EIP              +
    ; +---------------------+
    ; +    ECX              +
    ; +---------------------+ <-- ESP
    ;
    ; Registers:
    ;   ECX - Vector Number
    ;

    ;
    ; Put Vector Number on stack
    ;
    push    ecx

    ;
    ; Put 0 (dummy) error code on stack, and restore ECX
    ;
    xor     ecx, ecx  ; ECX = 0
    xchg    ecx, [esp + 4]

    jmp     ErrorCodeAndVectorOnStack

HasErrorCode:
    ;
    ; Stack:
    ; +---------------------+
    ; +    EFlags           +
    ; +---------------------+
    ; +    CS               +
    ; +---------------------+
    ; +    EIP              +
    ; +---------------------+
    ; +    Error Code       +
    ; +---------------------+
    ; +    ECX              +
    ; +---------------------+ <-- ESP
    ;
    ; Registers:
    ;   ECX - Vector Number
    ;

    ;
    ; Put Vector Number on stack and restore ECX
    ;
    xchg    ecx, [esp]

ErrorCodeAndVectorOnStack:
  push  ebp
  mov  ebp, esp
  mov  ax, 0EEEEh
  out  80h, ax
  ;
  ; Stack:
  ; +---------------------+
  ; +    EFlags           +
  ; +---------------------+
  ; +    CS               + +0x10
  ; +---------------------+
  ; +    EIP              + +0x0C
  ; +---------------------+
  ; +    Error Code       + +8
  ; +---------------------+
  ; +    Vector Number    + +4
  ; +---------------------+
  ; +    EBP              +
  ; +---------------------+ <-- EBP
  push  [ebp + 0Ch]    ; EIP
  push  [ebp + 10h]    ; CS
  push  [ebp + 04h]    ; Vector
  call  _PrintExceptionDetails  ; void _PrintExceptionDetails (Exception, RegCs, RegEip)

  jmp  $      ; We stop here

  add  esp, 24
  iretd
CommonInterruptEntry ENDP

MAKE_STACKS

END
