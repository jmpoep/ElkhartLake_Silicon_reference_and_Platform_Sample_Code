//// @file
//  This file implements SEC CPU library
//
// @copyright
//  INTEL CONFIDENTIAL
//  Copyright 2014 - 2019 Intel Corporation.
//
//  The source code contained or described herein and all documents related to the
//  source code ("Material") are owned by Intel Corporation or its suppliers or
//  licensors. Title to the Material remains with Intel Corporation or its suppliers
//  and licensors. The Material may contain trade secrets and proprietary and
//  confidential information of Intel Corporation and its suppliers and licensors,
//  and is protected by worldwide copyright and trade secret laws and treaty
//  provisions. No part of the Material may be used, copied, reproduced, modified,
//  published, uploaded, posted, transmitted, distributed, or disclosed in any way
//  without Intel's prior express written permission.
//
//  No license under any patent, copyright, trade secret or other intellectual
//  property right is granted to or conferred upon you by disclosure or delivery
//  of the Materials, either expressly, by implication, inducement, estoppel or
//  otherwise. Any license under such intellectual property rights must be
//  express and approved by Intel in writing.
//
//  Unless otherwise agreed by Intel in writing, you may not remove or alter
//  this notice or any other notice embedded in Materials by Intel or
//  Intel's suppliers or licensors in any way.
//
//  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
//  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
//  the terms of your license agreement with Intel or your vendor. This file may
//  be modified by the user, subject to additional terms of the license agreement.
//
// @par Specification Reference:
////


.INCLUDE "SecCpuLib.i"

ASM_GLOBAL    ASM_PFX(_gPcd_FixedAtBuild_PcdBiosAreaBaseAddress)
ASM_GLOBAL    ASM_PFX(_gPcd_FixedAtBuild_PcdNemCodeCacheBase)
ASM_GLOBAL    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase)
ASM_GLOBAL    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize)

ASM_GLOBAL    ASM_PFX(EarlyCycleDecoding)
ASM_GLOBAL    ASM_PFX(SerialIoUartDebugConfiguration)
ASM_GLOBAL    ASM_PFX(SerialIoSpiPostCodeConfiguration)

// Load MCU path, if not already loaded from FIT table
//
// esi = Start of Microcode
// edi = End of Microcode

ASM_GLOBAL ASM_PFX(SearchAndLoadMicrocode)
ASM_PFX(SearchAndLoadMicrocode):
//
// Write 0 to MSR 08Bh and execute CPUID.(EAX = 1) before reading MSR 08Bh
//
  xorl    %eax, %eax
  xorl    %edx, %edx
  movl    $MSR_IA32_BIOS_SIGN_ID, %ecx
  wrmsr
  movl    $0x01, %eax
  cpuid
  movl    $MSR_IA32_BIOS_SIGN_ID, %ecx
  rdmsr                                      // CPU PatchID -> EDX
  cmpl    $0x00, %edx                        // If microcode has been updated
  jnz     luExit                             // Skip if patch already loaded

  movd    %edx, %mm3                         // Reset patch revision in mm3
  movl    $1, %eax                           // To get CPU signature.
  cpuid                                      // EAX = CPU signature.
  movl    %eax, %ebx                         // preserve signature

  movl    $MSR_IA32_PLATFORM_ID, %ecx        // To get Platform ID.
  rdmsr
  shrl    $18, %edx                          //EDX[0-2] = Platform ID.
  and     $7, %dx                            //DX = Platform ID.
  movl    $1, %ecx
  xchgl   %edx, %ecx
  shll    %cl, %edx
  mov     %ebx, %eax                         //eax = signature

  //
  // EAX = CPU signature.
  // EDX = Platform ID bit.
  // ESI = Abs addr of contiguous uCode blocks.
  // EDI = Abs addr of contiguous uCode blocks end.
  //

luCheckPatch:
  cmpl    %eax, %ds:(UpdateHeaderStrucdProcessorSignature)(%esi)         //Sig matched?
  jnz     luCheckUnprogrammed                // No.
  test    %edx, %ds:(UpdateHeaderStrucdProcessorFlags)(%esi)             //Platform matched?
  jnz     luFoundMatch                       // Yes.

luCheckUnprogrammed:
  movl    %ds:(UpdateHeaderStrucdDataSize)(%esi), %ebx
  cmpl    $0xFFFFFFFF, %ebx
  je      luUnprogrammed
  cmp     $0x01, %ds:(UpdateHeaderStrucdLoaderRevision)(%esi)
  je      luCheckExtdHdrs

luUnprogrammed:
  movl    $0x400, %ebx                       // Unprogrammed space, 1KB checks
  jmp     luPoinToNextBlock                  // for backword compatibility.

luCheckExtdHdrs:
  addl    $UpdateHeaderStrucLength, %ebx
  cmpl    %ds:(UpdateHeaderStrucdTotalSize)(%esi), %ebx
  jae     luTryNextPatch                     // No extd hdrs.

  movl    %ds:(%esi, %ebx), %ecx
  jcxz    luTryNextPatch                     // No extd hdrs. (OK to use CX instead of ECX).
  addl    $0x14, %ebx                        // Point to the first Extd Sig.

luNextSig:
  cmpl    %ds:(%esi, %ebx), %eax             // Sig matched?
  jne     lu_00
  test    %ds:4(%esi, %ebx), %edx            // Platform matched?
  jnz     luFoundMatch

lu_00:
  addl    $0x0C, %ebx
  loop    luNextSig

luTryNextPatch:
  movl    %ds:(UpdateHeaderStrucdTotalSize)(%esi), %ebx
  orl     %ebx, %ebx
  jnz     luPoinToNextBlock                  // Variable size uCode format.
  movl    $BLOCK_LENGTH_BYTES, %ebx          // Fixed size uCode format.

luPoinToNextBlock:
  addl    %ebx, %esi
  cmpl    %edi, %esi
  jb      luCheckPatch                       // Check with all patches.

  //
  // Check possible multiple patch
  //
  movd    %mm3, %eax
  movd    %mm4, %esi
  orl     %eax, %eax

  jnz     luLoadPatch
  jmp     luExit                             // No matching patch found.

luFoundMatch:
  //
  //   MM3 = Patch Revision
  //   MM4 = Patch Pointer
  //
  movd    %mm3, %ebx
  cmpl    %ebx, %ds:(UpdateHeaderStrucdUpdateRevision)(%esi)
  jbe     luTryNextPatch

  movl    %ds:(UpdateHeaderStrucdUpdateRevision)(%esi), %ebx

luStoreRevPtr:
  movd    %ebx, %mm3                        // save Patch Revision
  movd    %esi, %mm4                        // save Patch Pointer
  jmp     luTryNextPatch

luLoadPatch:
  movl    $MSR_IA32_BIOS_UPDT_TRIG, %ecx
  movl    %esi, %eax                         // EAX - Abs addr of uCode patch.
  addl    $UpdateHeaderStrucLength, %eax     // EAX - Abs addr of uCode data.
  xorl    %edx, %edx                         // EDX:EAX - Abs addr of uCode data.
  wrmsr                                      // Trigger uCode load.

luExit:

  //
  // Send the patch ID to port80
  //
  movl  $MSR_IA32_BIOS_SIGN_ID, %ecx
  xorl  %eax, %eax
  xorl  %edx, %edx
  wrmsr

  movl  $0x01, %eax
  cpuid

  movl  $MSR_IA32_BIOS_SIGN_ID, %ecx
  rdmsr
  movl  %edx, %eax
  out   %eax, $0x80

  RET_EBP


//-----------------------------------------------------------------------------
//
//  Section:     SecCarInit
//
//  Description: This function initializes the Cache for Data, Stack, and Code
//               as specified in the  BIOS Writer's Guide.
//
//-----------------------------------------------------------------------------
ASM_GLOBAL ASM_PFX(SecCarInit)
ASM_PFX(SecCarInit):
  //
  // Detect Boot Guard Boot
  //

DetectBootGuard:
  movl    $MSR_BOOT_GUARD_SACM_INFO, %ecx
  rdmsr
  andl    $0x01, %eax
  jnz     BootGuardNemSetup
SkipDetectBootGuard:

  //
  //  Enable cache for use as stack and for caching code
  //  Ensure that the system is in flat 32 bit protected mode.
  //
  //  Ensure that only one logical processor in the system is the BSP.
  //  (Required step for clustered systems).
  //
  //  Ensure all APs are in the Wait for SIPI state.
  //  This includes all other logical processors in the same physical processor
  //  as the BSP and all logical processors in other physical processors.
  //  If any APs are awake, the BIOS must put them back into the Wait for
  //  SIPI state by issuing a broadcast INIT IPI to all excluding self.
  //
  movl    $APIC_ICR_LO, %edi                 // 0FEE00300h - Send INIT IPI to all excluding self
  movl    $(ORALLBUTSELF + ORSELFINIT), %eax // 0000C4500h - Broadcast INIT IPI
  movl    %eax, (%edi)

SecCarInitL1:
  movl    (%edi), %eax
  btl     $0x0c, %eax                        // Check if send is in progress
  jc      SecCarInitL1                       // Loop until idle

  //   Ensure that all variable-range MTRR valid flags are clear and
  //   IA32_MTRR_DEF_TYPE MSR E flag is clear.  Note: This is the default state
  //   after hardware reset.
  //
  //   Initialize all fixed-range and variable-range MTRR register fields to 0.
  //
  movl    $IA32_MTRR_CAP, %ecx               // get variable MTRR support
  rdmsr
  movzx   %al, %ebx                          // EBX = number of variable MTRR pairs
  shl     $0x02, %ebx                        // *4 for Base/Mask pair and WORD size
  addl    $(MtrrCountFixed * 2), %ebx           // EBX = size of  Fixed and Variable MTRRs

  xorl    %eax, %eax                         // Clear the low dword to write
  xorl    %edx, %edx                         // Clear the high dword to write

InitMtrrLoop:
  addl    $(-2), %ebx                           //need to check it
  movl    $0, %ecx
  movw    %cs:(MtrrInitTable)(%ebx), %cx     // cx <- address of mtrr to zero
  wrmsr
  jnz   InitMtrrLoop                         // loop through the whole table

  //
  //   Configure the default memory type to un-cacheable (UC) in the
  //   IA32_MTRR_DEF_TYPE MSR.
  //

  movl    $MTRR_DEF_TYPE, %ecx               // Load the MTRR default type index
  rdmsr
  andl    $0xFFFFF300, %eax                  //and     eax, NOT (00000CFFh)  //Clear the enable bits and def type UC.
  wrmsr

  // Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
  // based on the physical address size supported for this processor
  // This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
  //
  // Examples:
  //  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
  //  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
  //
  movl    $0x80000008, %eax                  // Address sizes leaf
  cpuid
  sub     $0x20, %al                         // sub   al, 32
  movzx   %al, %eax
  xorl    %esi, %esi
  bts     %eax, %esi
  dec     %esi                               // esi <- MTRR_PHYS_MASK_HIGH

  //
  //   Configure the DataStack region as write-back (WB) cacheable memory type
  //   using the variable range MTRRs.
  //
  //
  // Set the base address of the DataStack cache range
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %eax
  orl     $MTRR_MEMORY_TYPE_WB, %eax
                                             // Load the write-back cache value
  xorl    %edx, %edx                         // clear upper dword
  movl    $MTRR_PHYS_BASE_0, %ecx            // Load the MTRR index
  wrmsr                                      // the value in MTRR_PHYS_BASE_0

  //
  // Set the mask for the DataStack cache range
  // Compute MTRR mask value:  Mask = NOT (Size - 1)
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %eax
  dec     %eax
  not     %eax
  orl     $MTRR_PHYS_MASK_VALID, %eax
                                             // turn on the Valid flag
  movl    %esi, %edx                         // edx <- MTRR_PHYS_MASK_HIGH
  movl    $MTRR_PHYS_MASK_0, %ecx            // For proper addressing above 4GB
  wrmsr                                      // the value in MTRR_PHYS_BASE_0

  //
  //   Configure the BIOS code region as write-protected (WP) cacheable
  //   memory type using a single variable range MTRR.
  //
  //   Ensure region to cache meets MTRR requirements for
  //   size and alignment.
  //

  //
  // Calculate NEM size
  // Determine LLC size of the code region and data region combined must not exceed the size
  // of the (Last Level Cache - 0.5MB).
  //
  // Determine Cache Parameter by CPUID Function 04h
  //
  xorl    %edi, %edi

Find_LLC_parameter:
  movl    %edi, %ecx
  movl    $0x04, %eax
  cpuid
  inc     %edi
  and     $0xE0, %al                         // EAX[7:5] = Cache Level
  cmp     $0x60, %al                         // Check to see if it is LLC
  jnz     Find_LLC_parameter

  //
  // Got L3 parameters
  //
  // This Cache Size in Bytes = (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
  //  = (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
  //
  movl    %ecx, %eax
  inc     %eax
  movl    %ebx, %edi
  shr     $0x16, %ebx                        //shr     ebx, 22
  inc     %ebx
  mul     %ebx
  movl    %edi, %ebx
  andl    $0x003FF000, %ebx                  //and     ebx, NOT 0FFC0 0FFFh
  shr     $0x0C, %ebx
  inc     %ebx
  mul     %ebx
  movl    %edi, %ebx
  andl    $0x0FFF, %ebx
  inc     %ebx
  mul     %ebx

  //
  // Maximum NEM size <= (Last Level Cache - 0.5MB)
  //
  subl    $0x80000, %eax                     //sub     eax, 512*1024

Got_NEM_size:
  //
  // Code cache size = Total NEM size - DataStack size
  //
  subl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %eax
  //
  // Round up to page size
  //
  movl    %eax, %ecx                   // Save
  andl    $0xFFFF0000, %ecx            // Number of pages in 64K
  andl    $0xFFFF, %eax                // Number of "less-than-page" bytes
  jz      Rounded
  movl    $0x10000, %eax               // Add the whole page size

Rounded:
  addl    %ecx, %eax                    // eax - rounded up code cache size

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  //
  // Set the base address of the CodeRegion cache range from PCD
  // PcdNemCodeCacheBase is set to the offset to flash base,
  // so add PcdBiosAreaBaseAddress to get the real code base address.
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdNemCodeCacheBase), %edi
  addl    ASM_PFX(_gPcd_FixedAtBuild_PcdBiosAreaBaseAddress), %edi

  movl    %edi, %ebx                    // Check if region needed for code caching is smaller than available.
  addl    %eax, %ebx                    //    or sum of base needed and available cache above 4 GB.
  jnc     NoAdjustBase                  // Check if > 4GB, or required code cache region is less than
  xorl    %edi, %edi                    // edi = 4GB
  subl    %eax, %edi                    // Base = entire available code cache region with top at 4GB.
NoAdjustBase:

#else
  movl    4(%esp), %ecx
  cmpl    $0, %ecx
  jz      InvalidParameter

  movl    CodeRegionBase(%ecx), %edi    // Code region base
  movl    CodeRegionSize(%ecx), %ecx    // Code region size
  cmpl    $0, %ecx
  jz      InvalidParameter
  jmp     CheckPass

InvalidParameter:
  movl    $0x80000002, %eax            // RETURN_INVALID_PARAMETER
  jmp     SecCarInitExit

CheckPass:

  //
  // Use LLC size if CodeRegionSize is bigger than LLC size
  //
  cmpl    %eax, %ecx                   // Compare FSP requested size with available size.
  ja      CodeSizeDone                 // If Requested is larger than available, use available and jump.
  mov     %ecx, %eax                   // Use requested size.
CodeSizeDone:

#endif
  //
  // Save MM5 into ESP before program MTRR, because program MTRR will use MM5 as the local variable.
  // And, ESP is not initialized before CAR is enabled. So, it is safe ot use ESP here.
  //

  movd %mm5, %esp
  //
  // Define "local" vars for this routine
  // @todo as these registers are overlapping with others
  // Note that mm0 is used to store BIST result for BSP,
  // mm1 is used to store the number of processor and BSP APIC ID,
  // mm6 is used to save time-stamp counter value.
  //
.equ   CODE_SIZE_TO_CACHE,      %mm3
.equ   CODE_BASE_TO_CACHE,      %mm4
.equ   NEXT_MTRR_INDEX,         %mm5
.equ   NEXT_MTRR_SIZE,          %mm2

  //
  // Initialize "locals"
  //
  subl    %ecx, %ecx
  movd    %ecx, NEXT_MTRR_INDEX              // Count from 0 but start from MTRR_PHYS_BASE_1

  //
  // Save remaining size to cache
  //
  movd    %eax, CODE_SIZE_TO_CACHE           // Size of code cache region that must be cached

  //
  // For non-FSP, sets the base from 4GB - code cache length, which is the non-FSP post validation code.
  // However, for FSP, the base is from the TempRamInit API. However, if base is 0, then use 4G - code cche lengthlength.
  //

#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  cmp     $0, %edi
  jnz     SecCarInitL2
#endif

  movl    $0xFFFFFFFF, %edi
  subl    %eax, %edi
  inc     %edi
  test    $0xFFFF, %edi
  jz      SecCarInitL2
  addl    $0x10000, %edi
  andl    $0xFFFF0000, %edi
SecCarInitL2:

  movd    %edi, CODE_BASE_TO_CACHE           // Base code cache address

NextMtrr:
  //
  // Get remaining size to cache
  //
  movd    CODE_SIZE_TO_CACHE, %eax
  andl    %eax, %eax
  jz      CodeRegionMtrrdone                 // If no left size - we are done

  //
  // Determine next size to cache.
  // We start from bottom up. Use the following algorythm:
  // 1. Get our own alignment. Max size we can cache equals to our alignment
  // 2. Determine what is bigger - alignment or remaining size to cache.
  //    If aligment is bigger - cache it.
  //      Adjust remaing size to cache and base address
  //      Loop to 1.
  //    If remaining size to cache is bigger
  //      Determine the biggest 2^N part of it and cache it.
  //      Adjust remaing size to cache and base address
  //      Loop to 1.
  // 3. End when there is no left size to cache or no left MTRRs
  //
  movd    CODE_BASE_TO_CACHE, %edi
  bsf     %edi, %ecx                         // Get index of lowest bit set in base address

  //
  // Convert index into size to be cached by next MTRR
  //
  movl    $0x01, %edx
  shl     %cl, %edx                          // Alignment is in edx
  cmpl    %eax, %edx                         // What is bigger, alignment or remaining size?
  jbe     GotSize                            // JIf aligment is less

  //
  // Remaining size is bigger. Get the biggest part of it, 2^N in size
  //
  bsr     %eax, %ecx                         // Get index of highest set bit

  //
  // Convert index into size to be cached by next MTRR
  //
  movl    $0x01, %edx
  shl     %cl, %edx                          // Size to cache

GotSize:
  movl    %edx, %eax
  movd    %eax, NEXT_MTRR_SIZE               // Save

  //
  // Compute MTRR mask value:  Mask = NOT (Size - 1)
  //
  dec     %eax                               // eax - size to cache less one byte
  not     %eax                               // eax contains low 32 bits of mask
  or      $MTRR_PHYS_MASK_VALID , %eax       // Set valid bit

  //
  // Program mask register
  //
  movl    $MTRR_PHYS_MASK_1 , %ecx           // setup variable mtrr
  movd    NEXT_MTRR_INDEX, %ebx
  addl    %ebx, %ecx

  movl    %esi, %edx                         // edx <- MTRR_PHYS_MASK_HIGH
  wrmsr

  //
  // Program mask register
  //
  subl    %edx, %edx
  movl    $MTRR_PHYS_BASE_1, %ecx            // setup variable mtrr
  addl    %ebx, %ecx                         // ebx is still NEXT_MTRR_INDEX

  movd    CODE_BASE_TO_CACHE, %eax
  orl     $MTRR_MEMORY_TYPE_WP, %eax         // set type to write protect
  wrmsr

  //
  // Advance and loop
  // Reduce remaining size to cache
  //
  movd    CODE_SIZE_TO_CACHE, %ebx
  movd    NEXT_MTRR_SIZE, %eax
  sub     %eax, %ebx
  movd    %ebx, CODE_SIZE_TO_CACHE

  //
  // Increment MTRR index
  //
  movd    NEXT_MTRR_INDEX, %ebx
  addl    $0x02, %ebx
  movd    %ebx, NEXT_MTRR_INDEX

  //
  // Increment base address to cache
  //
  movd    CODE_BASE_TO_CACHE , %ebx
  movd    NEXT_MTRR_SIZE, %eax
  addl    %eax, %ebx

  //
  //// if carry happens, means NEM base + size over 4G
  //
  jc      CodeRegionMtrrdone
  movd    %ebx, CODE_BASE_TO_CACHE

  jmp     NextMtrr

CodeRegionMtrrdone:
  //
  // Enable the MTRRs by setting the IA32_MTRR_DEF_TYPE MSR E flag.
  //
  movl    $MTRR_DEF_TYPE, %ecx               // Load the MTRR default type index
  rdmsr
  orl     $MTRR_DEF_TYPE_E, %eax             // Enable variable range MTRRs
  wrmsr

  //
  //   Enable the logical processor's (BSP) cache: execute INVD and set
  //   CR0.CD = 0, CR0.NW = 0.
  //
  movl    %cr0, %eax
  and     $(~(CR0_CACHE_DISABLE + CR0_NO_WRITE)), %eax
  invd
  movl    %eax, %cr0

  //
  //   Enable No-Eviction Mode Setup State by setting
  //   NO_EVICT_MODE  MSR 2E0h bit [0] = '1'.
  //
  movl    $NO_EVICT_MODE, %ecx
  rdmsr
  orl     $0x01, %eax
  wrmsr

  //
  // Restore MM5 from ESP after program MTRR
  //
  movd    %esp, %mm5

  //
  // Restore MM4 which is Patch Pointer.
  // Current implementation it's the same with the PcdNemCodeCacheBase + PcdBiosAreaBaseAddress
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdNemCodeCacheBase), %edi
  addl    ASM_PFX(_gPcd_FixedAtBuild_PcdBiosAreaBaseAddress), %edi
  movd    %edi, %mm4

  //
  // One location in each  line of the DataStack region
  // must be written to set all cache values to the modified state.
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %edi
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %ecx
  shr     $0x06, %ecx
  movl    $CACHE_INIT_VALUE, %eax

SecCarInitL3:
  movl    %eax, (%edi)
  sfence                                     // need to check it
  addl    $0x40, %edi                        // add  edi, 64
  loop    SecCarInitL3

  //
  // Enable No-Eviction Mode Run State by setting
  // NO_EVICT_MODE MSR 2E0h bit [1] = '1'.
  //
  movl    $NO_EVICT_MODE, %ecx
  rdmsr
  orl     $0x02, %eax
  wrmsr

  jmp     FinishedCacheConfig

  //
  // Jump to here when Boot Guard boot and NEM is initialized by Boot Guard ACM
  //
BootGuardNemSetup:
  //
  // Finished with cache configuration
  //
  //
  // Disable MTRR9
  //
  xorl  %eax, %eax                      // clear lower dword
  xorl  %edx, %edx                      // clear upper dword
  movl  $MTRR_PHYS_MASK_9, %ecx         // load the MTRR index with the value in MTRR_PHYS_MASK_9
  wrmsr

  // Configure MTRR_PHYS_MASK_HIGH for proper addressing above 4GB
  // based on the physical address size supported for this processor
  // This is based on read from CPUID EAX = 080000008h, EAX bits [7:0]
  //
  // Examples:
  //  MTRR_PHYS_MASK_HIGH = 00000000Fh  For 36 bit addressing
  //  MTRR_PHYS_MASK_HIGH = 0000000FFh  For 40 bit addressing
  //
  movl    $0x80000008, %eax                  // Address sizes leaf
  cpuid
  sub     $0x20, %al                         // sub   al, 32
  movzx   %al, %eax
  xorl    %esi, %esi
  bts     %eax, %esi
  dec     %esi                               // esi <- MTRR_PHYS_MASK_HIGH

  //
  // Configure the DataStack region as write-back (WB) cacheable memory type
  // using the variable range MTRRs.
  //
  //
  // Find available MTRR
  //
  movl    $ReturnAddress1, %ebp              //Use these code to replace CALL_EBP, Need to check it
  jmp     FindFreeMtrr
ReturnAddress1:

  //
  // Set the base address of the DataStack cache range
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %eax
  orl     $MTRR_MEMORY_TYPE_WB, %eax
                                             // Load the write-back cache value
  xorl    %edx, %edx                         // clear upper dword
  wrmsr                                      // the value in MTRR_PHYS_BASE_0

  //
  // Set the mask for the DataStack cache range
  // Compute MTRR mask value:  Mask = NOT (Size - 1)
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %eax
  dec     %eax
  not     %eax
  orl     $MTRR_PHYS_MASK_VALID, %eax
                                             // turn on the Valid flag
  movl    %esi, %edx                         // edx <- MTRR_PHYS_MASK_HIGH
  inc     %ecx
  wrmsr                                      // the value in MTRR_PHYS_BASE_0


  //
  // One location in each 64-byte cache line of the DataStack region
  // must be written to set all cache values to the modified state.
  //
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %edi
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %ecx
  shr     $0x06, %ecx
  movl    CACHE_INIT_VALUE, %eax

SecCarInitL4:
  movl    %eax, (%edi)
  sfence
  addl    $0x40, %edi                        //add  edi, 64
  loop    SecCarInitL4

  //
  // Finished with cache configuration
  //
FinishedCacheConfig:

  //
  // Optionally Test the Region
  //

  //
  // Test area by writing and reading
  //
  cld
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %edi
  movl    ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %ecx
  shrl    $0x02, %ecx
  movl    $CACHE_TEST_VALUE, %eax
TestDataStackArea:
  movl    %eax, (%edi)                       // stosd
  addl    $4, %edi

  cmp     -4(%edi), %eax
  jnz     DataStackTestFail
  loop    TestDataStackArea
  jmp     DataStackTestPass

  //
  // Cache test failed
  //
DataStackTestFail:

  STATUS_CODE(0xD0)
  jmp     .       //'$'

  //
  // Configuration test failed
  //
ConfigurationTestFailed:
  STATUS_CODE(0xD1)
  jmp     .     //'$'

DataStackTestPass:


  //
  // At this point you may continue normal execution.  Typically this would include
  // reserving stack, initializing the stack pointer, etc.
  //

  //
  // Temporary Set stack top pointer for C code usage.
  //
  movl   ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamBase), %esp
  addl   ASM_PFX(_gPcd_FixedAtBuild_PcdTemporaryRamSize), %esp
  //
  // program resource decoding
  //
  pusha
  call   ASM_PFX(EarlyCycleDecoding)
  popa
  pusha
  call   ASM_PFX(SerialIoUartDebugConfiguration)
  popa
#if FixedPcdGetBool(PcdFspBinaryEnable) == 1
  pusha
  call   ASM_PFX(SerialPortConfiguration)
  popa
#endif
  pusha
  call   ASM_PFX(SerialIoSpiPostCodeConfiguration)
  popa

//
  // After memory initialization is complete, please follow the algorithm in the BIOS
  // Writer's Guide to properly transition to a normal system configuration.
  // The algorithm covers the required sequence to properly exit this mode.
  //
  xor   %eax, %eax

SecCarInitExit:

  RET_ESI



//-----------------------------------------------------------------------------
//
//  Section:     FindFreeMtrr
//
//  Description:
//
//-----------------------------------------------------------------------------
ASM_GLOBAL ASM_PFX(FindFreeMtrr)
ASM_PFX(FindFreeMtrr):
  //
  // Find available MTRRs
  //
  movl   $MTRR_PHYS_MASK_0, %ecx

FindFreeMtrrL0:
  rdmsr
  test    $0x800, %eax
  jz      FoundFreeMtrr
  addl    $0x02, %ecx
  cmpl    $MTRR_PHYS_MASK_9, %ecx
  jbe     FindFreeMtrrL0

  //
  // No available MTRR, halt system
  //
  jmp     .     //'$'

FoundFreeMtrr:
  dec    %ecx

  RET_EBP



MtrrInitTable:
.word      MTRR_DEF_TYPE
.word      MTRR_FIX_64K_00000
.word      MTRR_FIX_16K_80000
.word      MTRR_FIX_16K_A0000
.word      MTRR_FIX_4K_C0000
.word      MTRR_FIX_4K_C8000
.word      MTRR_FIX_4K_D0000
.word      MTRR_FIX_4K_D8000
.word      MTRR_FIX_4K_E0000
.word      MTRR_FIX_4K_E8000
.word      MTRR_FIX_4K_F0000
.word      MTRR_FIX_4K_F8000

.equ MtrrCountFixed,  ((.-MtrrInitTable) / 2)

.word      MTRR_PHYS_BASE_0
.word      MTRR_PHYS_MASK_0
.word      MTRR_PHYS_BASE_1
.word      MTRR_PHYS_MASK_1
.word      MTRR_PHYS_BASE_2
.word      MTRR_PHYS_MASK_2
.word      MTRR_PHYS_BASE_3
.word      MTRR_PHYS_MASK_3
.word      MTRR_PHYS_BASE_4
.word      MTRR_PHYS_MASK_4
.word      MTRR_PHYS_BASE_5
.word      MTRR_PHYS_MASK_5
.word      MTRR_PHYS_BASE_6
.word      MTRR_PHYS_MASK_6
.word      MTRR_PHYS_BASE_7
.word      MTRR_PHYS_MASK_7
.word      MTRR_PHYS_BASE_8
.word      MTRR_PHYS_MASK_8
.word      MTRR_PHYS_BASE_9
.word      MTRR_PHYS_MASK_9

.equ       MtrrCount,       ((.-MtrrInitTable) / 2)


