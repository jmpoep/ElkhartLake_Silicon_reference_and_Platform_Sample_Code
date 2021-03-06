;; @file
;  Provide FSP API entry points.
;
; Copyright (c) 2016 - 2019, Intel Corporation. All rights reserved.<BR>
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution.  The full text of the license may be found at
; http://opensource.org/licenses/bsd-license.php.
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;;

    SECTION .text

;
; Following are fixed PCDs
;
extern   ASM_PFX(PcdGet32(PcdTemporaryRamBase))
extern   ASM_PFX(PcdGet32(PcdTemporaryRamSize))
extern   ASM_PFX(PcdGet32(PcdFspTemporaryRamSize))
;
; FSPO-0010: OverrideBegin
;
extern   ASM_PFX(PcdGet8 (PcdFspHeapSizePercentage))
;
; FSPO-0010: OverrideEnd
;

struc FSPM_UPD_COMMON
    ; FSP_UPD_HEADER {
    .FspUpdHeader:            resd    8
    ; }
    ; FSPM_ARCH_UPD {
    .Revision:                resb    1
    .Reserved:                resb    3
    .NvsBufferPtr:            resd    1
    .StackBase:               resd    1
    .StackSize:               resd    1
    .BootLoaderTolumSize:     resd    1
    .BootMode:                resd    1
    .Reserved1:               resb    8
    ; }
    .size:
endstruc

;
; Following functions will be provided in C
;
extern ASM_PFX(SecStartup)
extern ASM_PFX(FspApiCommon)

;
; Following functions will be provided in PlatformSecLib
;
extern ASM_PFX(AsmGetFspBaseAddress)
extern ASM_PFX(AsmGetFspInfoHeader)

API_PARAM1_OFFSET            EQU   34h  ; ApiParam1 [ sub esp,8 + pushad + pushfd + push eax + call]
FSP_HEADER_IMGBASE_OFFSET    EQU   1Ch
FSP_HEADER_CFGREG_OFFSET     EQU   24h

;----------------------------------------------------------------------------
; FspMemoryInit API
;
; This FSP API is called after TempRamInit and initializes the memory.
;
;----------------------------------------------------------------------------
global ASM_PFX(FspMemoryInitApi)
ASM_PFX(FspMemoryInitApi):
  mov    eax,  3 ; FSP_API_INDEX.FspMemoryInitApiIndex
  jmp    ASM_PFX(FspApiCommon)

;----------------------------------------------------------------------------
; TempRamExitApi API
;
; This API tears down temporary RAM
;
;----------------------------------------------------------------------------
global ASM_PFX(TempRamExitApi)
ASM_PFX(TempRamExitApi):
  mov    eax,  4 ; FSP_API_INDEX.TempRamExitApiIndex
  jmp    ASM_PFX(FspApiCommon)

;----------------------------------------------------------------------------
; FspApiCommonContinue API
;
; This is the FSP API common entry point to resume the FSP execution
;
;----------------------------------------------------------------------------
global ASM_PFX(FspApiCommonContinue)
ASM_PFX(FspApiCommonContinue):
  ;
  ; EAX holds the API index
  ;

  ;
  ; FspMemoryInit API setup the initial stack frame
  ;

  ;
  ; Place holder to store the FspInfoHeader pointer
  ;
  push   eax

  ;
  ; Update the FspInfoHeader pointer
  ;
  push   eax
  call   ASM_PFX(AsmGetFspInfoHeader)
  mov    [esp + 4], eax
  pop    eax

  ;
  ; Create a Task Frame in the stack for the Boot Loader
  ;
  pushfd     ; 2 pushf for 4 byte alignment
  cli
  pushad

  ; Reserve 8 bytes for IDT save/restore
  sub     esp, 8
  sidt    [esp]


  ;  Get Stackbase and StackSize from FSPM_UPD Param
  mov    edx, [esp + API_PARAM1_OFFSET]
  cmp    edx, 0
  jnz    FspStackSetup

  ; Get UPD default values if FspmUpdDataPtr (ApiParam1) is null
  push   eax
  call   ASM_PFX(AsmGetFspInfoHeader)
  mov    edx, [eax + FSP_HEADER_IMGBASE_OFFSET]
  add    edx, [eax + FSP_HEADER_CFGREG_OFFSET]
  pop    eax

  FspStackSetup:
  ;
  ; FSPO-0010: OverrideBegin
  ;
  ;keep using bootloader stack if heap size % is 0
  mov    bl, BYTE [ASM_PFX(PcdGet8 (PcdFspHeapSizePercentage))]
  cmp    bl, 0
  jnz    TempRamStackSetup

  ;StackBase = temp memory base, StackSize = temp memory size
  mov    ebx, [edx + FSPM_UPD_COMMON.StackBase]
  mov    ecx, [edx + FSPM_UPD_COMMON.StackSize]

  ;
  ; Add FSP SecMain parameters to the stack
  ;
  mov     edi, esp

  ;
  ; Pass the API Idx to SecStartup
  ;
  push    eax

  ;
  ; Pass the BootLoader stack pointer to SecStartup
  ;
  push    edi

  ;
  ; Pass entry point of the PEI core
  ;
  call    ASM_PFX(AsmGetFspBaseAddress)
  mov     edi, eax
  call    ASM_PFX(AsmGetPeiCoreOffset)
  add     edi, eax
  push    edi

  ;
  ; Pass BFV into the PEI Core
  ; It uses relative address to calucate the actual boot FV base
  ; For FSP implementation with single FV, PcdFspBootFirmwareVolumeBase and
  ; PcdFspAreaBaseAddress are the same. For FSP with mulitple FVs,
  ; they are different. The code below can handle both cases.
  ;
  call    ASM_PFX(AsmGetFspBaseAddress)
  push    eax

  ;
  ; Pass stack base and size into the PEI Core
  ;
  push    ebx ; temp memory base
  push    ecx ; temp memory size

  jmp StackSetupDone

TempRamStackSetup:
  ;
  ; FSPO-0010: OverrideEnd
  ;

  mov    edi, [edx + FSPM_UPD_COMMON.StackBase]
  mov    ecx, [edx + FSPM_UPD_COMMON.StackSize]
  add    edi, ecx
  ;
  ; Setup new FSP stack
  ;
  xchg    edi, esp                                ; Exchange edi and esp, edi will be assigned to the current esp pointer and esp will be Stack base + Stack size
  mov     ebx, esp                                ; Put Stack base + Stack size in ebx

  ;
  ; Pass the API Idx to SecStartup
  ;
  push    eax

  ;
  ; Pass the BootLoader stack to SecStartup
  ;
  push    edi

  ;
  ; Pass entry point of the PEI core
  ;
  call    ASM_PFX(AsmGetFspBaseAddress)
  mov     edi, eax
  call    ASM_PFX(AsmGetPeiCoreOffset)
  add     edi, eax
  push    edi

  ;
  ; Pass BFV into the PEI Core
  ; It uses relative address to calucate the actual boot FV base
  ; For FSP implementation with single FV, PcdFspBootFirmwareVolumeBase and
  ; PcdFspAreaBaseAddress are the same. For FSP with mulitple FVs,
  ; they are different. The code below can handle both cases.
  ;
  call    ASM_PFX(AsmGetFspBaseAddress)
  push    eax

  ;
  ; Pass stack base and size into the PEI Core
  ;
  sub     ebx, ecx            ; Stack base + Stack size - Stack size
  push    ebx
  push    ecx
;
; FSPO-0010: OverrideBegin
;
StackSetupDone:
;
; FSPO-0010: OverrideEnd
;
  ;
  ; Pass Control into the PEI Core
  ;
  call    ASM_PFX(SecStartup)
  add     esp, 4
exit:
  ret

global ASM_PFX(FspPeiCoreEntryOff)
ASM_PFX(FspPeiCoreEntryOff):
   ;
   ; This value will be pached by the build script
   ;
   DD    0x12345678

global ASM_PFX(AsmGetPeiCoreOffset)
ASM_PFX(AsmGetPeiCoreOffset):
   mov   eax, dword [ASM_PFX(FspPeiCoreEntryOff)]
   ret

;----------------------------------------------------------------------------
; TempRamInit API
;
; Empty function for WHOLEARCHIVE build option
;
;----------------------------------------------------------------------------
global ASM_PFX(TempRamInitApi)
ASM_PFX(TempRamInitApi):
  jmp $
  ret

;----------------------------------------------------------------------------
; Module Entrypoint API
;----------------------------------------------------------------------------
global ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
  jmp $
