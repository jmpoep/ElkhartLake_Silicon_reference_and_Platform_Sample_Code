/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  LegacyBios ReverseThunk Driver.

Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <PiDxe.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/UefiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PeCoffLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/LegacyInterruptSupportLib.h>

#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyRegion2.h>
#include <Protocol/LegacyBiosReverseThunk.h>

#include <Guid/MemoryProfile.h>

#define EFI_SEGMENT(_Adr)     (UINT16) ((UINT16) (((UINTN) (_Adr)) >> 4) & 0xf000)
#define EFI_OFFSET(_Adr)      (UINT16) (((UINT16) ((UINTN) (_Adr))) & 0xffff)

#define LINEAR_SEL      0x08
#define LINEAR_CODE_SEL 0x10
#define SYS_DATA_SEL    0x18
#define SYS_CODE_SEL    0x20
#define SYS16_CODE_SEL  0x28
#define SYS16_DATA_SEL  0x30
#if defined (MDE_CPU_X64)
#define SYS_CODE64_SEL  0x38
#endif

#pragma pack (1)

//
// Low stub lay out
//

#define LOW_STACK_SIZE      (8*1024)            // 8k?

typedef struct {
  //
  // Space for the code
  //
  CHAR8               Code[0x200];             // ?

  //
  // Data for the code (cs releative)
  //
  IA32_DESCRIPTOR     GdtDesc;                // native mode GDT
  IA32_DESCRIPTOR     IdtDesc;                // native mode IDT
  UINTN               FlatEsp;
  IA32_DESCRIPTOR     RealModeIdtDesc;

#if defined (MDE_CPU_X64)
  UINT64              PageMapLevel4;          // page table for X64
#endif
} LOW_MEMORY_THUNK;

#pragma pack ()

//
// Global Descriptor Table (GDT)
//
GLOBAL_REMOVE_IF_UNREFERENCED IA32_SEGMENT_DESCRIPTOR mGdtEntries[] = {
/* selector { LimitLow BaseLow BaseMid Type S  DPL P  LimitHigh AVL L  DB G  BaseHigh } */
/* 0x00 */  {{0,       0,      0,      0,   0, 0,  0, 0,        0,  0, 0, 0, 0}},
/* 0x08 */  {{0xFFFF,  0,      0,      0x3, 1, 0,  1, 0xF,      0,  0, 1, 1, 0}},
/* 0x10 */  {{0xFFFF,  0,      0,      0xB, 1, 0,  1, 0xF,      0,  0, 1, 1, 0}},
/* 0x18 */  {{0xFFFF,  0,      0,      0x3, 1, 0,  1, 0xF,      0,  0, 1, 1, 0}},
/* 0x20 */  {{0xFFFF,  0,      0,      0xB, 1, 0,  1, 0xF,      0,  0, 1, 1, 0}},
/* 0x28 */  {{0xFFFF,  0,      0,      0xB, 1, 0,  1, 0xF,      0,  0, 0, 1, 0}},
/* 0x30 */  {{0xFFFF,  0,      0,      0x3, 1, 0,  1, 0xF,      0,  0, 0, 1, 0}},
/* 0x38 */  {{0xFFFF,  0,      0,      0xB, 1, 0,  1, 0xF,      0,  1, 0, 1, 0}},
/* 0x40 */  {{0,       0,      0,      0,   0, 0,  0, 0,        0,  0, 0, 0, 0}},
};

IA32_IDT_GATE_DESCRIPTOR  mIdtEntries[32];

/**
  Prepares reverse thunk code for later use.

  @param  LowCodeStart   Start address of the code to be copied for the thunk
  @param  LowCodeEnd     End address of the code to be copied for the thunk
  @param  IntThunk       Structure containing values used to patch code
**/
VOID
EFIAPI
RealModeTemplate (
  OUT UINTN          *LowCodeStart,
  OUT UINTN          *LowCodeEnd,
  IN  VOID           *IntThunk
  );

LOW_MEMORY_THUNK        *IntThunk;

LEGACY_BIOS_REVERSE_THUNK_PROTOCOL  mLegacyBiosReverseThunk;
EFI_LEGACY_BIOS_PROTOCOL            *mLegacyBios;
EFI_LEGACY_REGION2_PROTOCOL         *mLegacyRegion2;

/**
  The interface used by assembly file to call native code.
  It is a wrapper for native code.

  This interface is called at runtime. Do not use any BS or RT services.
  Do not enable interrupt.

  @param Entrypoint   User defined native Entrypoint
  @param RegSet       Register set context for reverse thunk call.
**/
VOID
EFIAPI
CommonReverseThunkEntry (
  IN LEGACY_BIOS_REVERSE_THUNK_NATIVE_ENTRY_POINT   Entrypoint,
  IN OUT EFI_IA32_REGISTER_SET                      *RegSet
  )
{
  Entrypoint (RegSet);
}

/**
  Allocate memory below 1M memory address, and open Legacy Region.

  This function allocates reserved memory below 1M memory address.

  @param  Size         Size of memory to allocate.

  @return Allocated address for output.
**/
VOID *
AllocateUnlockMemoryBelow1M (
  IN UINTN              Size
  )
{
  EFI_STATUS  Status;
  VOID        *Buffer;
  UINT32      Granularity;

  Status = mLegacyBios->GetLegacyRegion (
                          mLegacyBios,
                          Size,
                          0,    // E or F segment
                          0x10, // 16-byte aligned
                          (VOID **) &Buffer
                          );
  ASSERT_EFI_ERROR (Status);

  Status = mLegacyRegion2->UnLock (
                             mLegacyRegion2,
                             0xE0000,
                             0x20000,
                             &Granularity
                             );
  ASSERT_EFI_ERROR (Status);

  ZeroMem (Buffer, Size);

  return Buffer;
}

/**
  Close Legacy Region.

  This function closes reserved memory below 1M memory address.
**/
VOID
LockMemoryBelow1M (
  VOID
  )
{
  EFI_STATUS  Status;
  UINT32      Granularity;

  WriteBackInvalidateDataCacheRange ((VOID *)(UINTN)0xE0000, 0x20000);

  Status = mLegacyRegion2->Lock (
                             mLegacyRegion2,
                             0xE0000,
                             0x20000,
                             &Granularity
                             );
  ASSERT_EFI_ERROR (Status);

  return ;
}

/**
  Allocate memory below 4G Reserved memory address.

  @param  Size         Size of memory to allocate.

  @return Allocated address for output.
**/
VOID*
EFIAPI
AllocateReservedMemoryBelow4G (
  IN UINTN              Size
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;
  VOID*                 Buffer;

  Pages = EFI_SIZE_TO_PAGES (Size);
  Address = 0xffffffff;

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiReservedMemoryType,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);

  Buffer = (VOID *) (UINTN) Address;
  ZeroMem (Buffer, Size);

  return Buffer;
}

#if defined (MDE_CPU_X64)
#define IA32_PG_P                   1u
#define IA32_PG_RW                  (1u << 1)
#define IA32_PG_PS                  (1u << 7)

/**
  Check if 1-GByte pages is supported by processor or not.

  @retval TRUE   1-GByte pages is supported.
  @retval FALSE  1-GByte pages is not supported.

**/
BOOLEAN
Is1GPageSupport (
  VOID
  )
{
  UINT32         RegEax;
  UINT32         RegEdx;

  AsmCpuid (0x80000000, &RegEax, NULL, NULL, NULL);
  if (RegEax >= 0x80000001) {
    AsmCpuid (0x80000001, NULL, NULL, NULL, &RegEdx);
    if ((RegEdx & BIT26) != 0) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Create 4G PageTable in ReservedMemory.
**/
UINT32
Gen4GPageTable (
  VOID
  )
{
  VOID    *PageTable;
  UINTN   Index;
  UINT64  *Pte;
  BOOLEAN Support1GPageTable;
  UINTN   Pages;

  Support1GPageTable = Is1GPageSupport ();

  //
  // Allocate the page table
  //
  if (Support1GPageTable) {
    Pages = 2;
  } else {
    Pages = 6;
  }
  PageTable = AllocateReservedMemoryBelow4G (EFI_PAGES_TO_SIZE (Pages));
  ASSERT (PageTable != NULL);

  Pte = (UINT64*)(UINTN)(PageTable);
  *Pte = ((UINTN)PageTable + SIZE_4KB) + IA32_PG_RW + IA32_PG_P;
  ZeroMem (Pte + 1, SIZE_4KB - sizeof (*Pte));
  Pte += EFI_PAGE_SIZE / sizeof (*Pte);

  if (Support1GPageTable) {
    for (Index = 0; Index < 4; Index++) {
      Pte[Index] = (Index << 30) + IA32_PG_PS + IA32_PG_RW + IA32_PG_P;
    }
  } else {
    //
    // Set Page Directory Pointers
    //
    for (Index = 0; Index < 4; Index++) {
      Pte[Index] = (UINTN)Pte + SIZE_4KB * (Index + 1) + IA32_PG_RW + IA32_PG_P;
    }
    Pte += EFI_PAGE_SIZE / sizeof (*Pte);

    //
    // Fill in Page Directory Entries
    //
    for (Index = 0; Index < EFI_PAGE_SIZE * 4 / sizeof (*Pte); Index++) {
      Pte[Index] = (Index << 21) + IA32_PG_PS + IA32_PG_RW + IA32_PG_P;
    }
  }
  return (UINT32)(UINTN)PageTable;
}
#endif

/**
  Initialize reverse thunk environment, and return back the far call
  parameter.

  @param  ReverseThunkCallSegment   Reverse thunk call segment
  @param  ReverseThunkCallOffset    Reverse thunk call offset

  @retval EFI_SUCCESS               initialize reverse thunk environment successfully
**/
EFI_STATUS
EFIAPI
InitializeBiosIntCaller (
  OUT UINT16   *ReverseThunkCallSegment,
  OUT UINT16   *ReverseThunkCallOffset
  )
{
  EFI_PHYSICAL_ADDRESS        MemPage;
  IA32_SEGMENT_DESCRIPTOR     *CodeGdt;
  UINTN                       LowCodeStart;
  UINTN                       LowCodeEnd;
  UINT32                      Base;
  UINTN                       Index;
  IA32_CR0                    Cr0;
  UINTN                       SavedCr0;

  //
  // Allocate 1 page below 1MB to put real mode thunk code in
  //
  MemPage = (EFI_PHYSICAL_ADDRESS)(UINTN)AllocateUnlockMemoryBelow1M (sizeof(*IntThunk));
  DEBUG ((EFI_D_INFO, "IntThunk - 0x%x\n", MemPage));
  ASSERT (MemPage != 0);
  IntThunk = (LOW_MEMORY_THUNK *)(UINTN)MemPage;

  //
  // Capture the flat gdt, idt, and selector values
  //
  IntThunk->GdtDesc.Base = (UINTN)mGdtEntries;
  IntThunk->GdtDesc.Limit = sizeof(mGdtEntries) - 1;
  IntThunk->IdtDesc.Base = (UINTN)mIdtEntries;
  IntThunk->IdtDesc.Limit = sizeof(mIdtEntries) - 1;
  for (Index = 0; Index < sizeof(mIdtEntries)/sizeof(mIdtEntries[0]); Index++) {
    mIdtEntries[Index].Bits.OffsetLow = (UINT16)(UINTN)CpuDeadLoop;
    mIdtEntries[Index].Bits.Selector = SYS_CODE_SEL;
    mIdtEntries[Index].Bits.Reserved_0 = 0;
    mIdtEntries[Index].Bits.GateType = IA32_IDT_GATE_TYPE_INTERRUPT_32;
    mIdtEntries[Index].Bits.OffsetHigh = (UINT16)((UINTN)CpuDeadLoop >> 16);
#if defined (MDE_CPU_X64)
    mIdtEntries[Index].Bits.Selector = SYS_CODE64_SEL;
    mIdtEntries[Index].Bits.OffsetUpper = (UINT32)RShiftU64 ((UINTN)CpuDeadLoop, 32);
    mIdtEntries[Index].Bits.Reserved_1 = 0;
#endif
  }

  //
  // Allocate 128K stack (0x20 page)
  //
  MemPage = (EFI_PHYSICAL_ADDRESS)(UINTN)AllocateReservedMemoryBelow4G (EFI_PAGES_TO_SIZE(0x20));
  ASSERT (MemPage != 0);
  IntThunk->FlatEsp = (UINTN)MemPage + EFI_PAGES_TO_SIZE(0x20);

#if defined (MDE_CPU_X64)
  IntThunk->PageMapLevel4 = Gen4GPageTable ();
#endif

  //
  // Allocate a new GDT for real-mode code
  //
  CodeGdt = (IA32_SEGMENT_DESCRIPTOR *)((UINTN)IntThunk->GdtDesc.Base + SYS16_CODE_SEL);
  Base = ((UINT32)(UINTN)IntThunk);
  CodeGdt->Bits.BaseHigh    = (Base >> 24) & 0xFF;
  CodeGdt->Bits.BaseMid     = (Base >> 16) & 0xFF;
  CodeGdt->Bits.BaseLow     = Base & 0xFFFF;

  //
  // Compute selector value
  //
  IntThunk->RealModeIdtDesc.Limit = 0xFFFF;
  IntThunk->RealModeIdtDesc.Base  = 0;

  //
  // Disable WP bit.
  //
  Cr0.UintN = AsmReadCr0();
  SavedCr0 = Cr0.UintN;
  Cr0.Bits.WP = 0;
  AsmWriteCr0 (Cr0.UintN);

  //
  // Initialize low real-mode code thunk
  //
  RealModeTemplate (&LowCodeStart, &LowCodeEnd, IntThunk);

  //
  // Restore WP bit.
  //
  AsmWriteCr0 (SavedCr0);

  CopyMem (IntThunk->Code, (VOID *) LowCodeStart, LowCodeEnd - LowCodeStart);
  DEBUG ((EFI_D_INFO, "CodeSize - 0x%x\n", LowCodeEnd - LowCodeStart));

  //
  // return Segment and Offset
  //
  *ReverseThunkCallSegment = EFI_SEGMENT (IntThunk->Code);
  *ReverseThunkCallOffset  = EFI_OFFSET (IntThunk->Code);

  LockMemoryBelow1M ();

  return EFI_SUCCESS;
}

/**
  Initialize the state information for the LegacyBiosReverseThunk driver.

  @param  ImageHandle   ImageHandle of the loaded driver.
  @param  SystemTable   Pointer to the System Table.

  @retval EFI_SUCCESS   LegacyBiosReverseThunk is successfully created.
**/
EFI_STATUS
EFIAPI
InitializeLegacyBiosReverseThunk (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &mLegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (
                  &gEfiLegacyRegion2ProtocolGuid,
                  NULL,
                  (VOID **) &mLegacyRegion2
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Prepare reverse thunk execution environment, and get far call parameter.
  //
  Status = InitializeBiosIntCaller (&mLegacyBiosReverseThunk.ReverseThunkCallSegment, &mLegacyBiosReverseThunk.ReverseThunkCallOffset);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((EFI_D_INFO, "ReverseThunkCallSegment - 0x%x\n", mLegacyBiosReverseThunk.ReverseThunkCallSegment));
  DEBUG ((EFI_D_INFO, "ReverseThunkCallOffset - 0x%x\n", mLegacyBiosReverseThunk.ReverseThunkCallOffset));

  //
  // Install thunk protocol
  //
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gLegacyBiosReverseThunkProtocolGuid,
                  &mLegacyBiosReverseThunk,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Register image to memory profile.

  @param FileName       File name of the image.
  @param ImageBase      Image base address.
  @param ImageSize      Image size.
  @param FileType       File type of the image.

**/
VOID
RegisterMemoryProfileImage (
  IN EFI_GUID                       *FileName,
  IN PHYSICAL_ADDRESS               ImageBase,
  IN UINT64                         ImageSize,
  IN EFI_FV_FILETYPE                FileType
  )
{
  EFI_STATUS                        Status;
  EDKII_MEMORY_PROFILE_PROTOCOL     *ProfileProtocol;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *FilePath;
  UINT8                             TempBuffer[sizeof (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH) + sizeof (EFI_DEVICE_PATH_PROTOCOL)];

  if ((PcdGet8 (PcdMemoryProfilePropertyMask) & BIT0) != 0) {

    FilePath = (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *)TempBuffer;
    Status = gBS->LocateProtocol (&gEdkiiMemoryProfileGuid, NULL, (VOID **) &ProfileProtocol);
    if (!EFI_ERROR (Status)) {
      EfiInitializeFwVolDevicepathNode (FilePath, FileName);
      SetDevicePathEndNode (FilePath + 1);

      Status = ProfileProtocol->RegisterImage (
                                  ProfileProtocol,
                                  (EFI_DEVICE_PATH_PROTOCOL *) FilePath,
                                  ImageBase,
                                  ImageSize,
                                  FileType
                                  );
    }
  }
}

/**
  Check if image is already in Reserved memory.

  @retval TRUE  Image is in Reserved memory.
  @retval FALSE Image is not in Reserved memory.
**/
BOOLEAN
EFIAPI
IsImgaeInReservedMemory (
  VOID
  )
{
  VOID        *Interface;
  EFI_STATUS  Status;

  //
  // Test if the gEfiCallerIdGuid of this image is already installed. if not, the entry
  // point is loaded by DXE code which is the first time loaded. or else, it is already
  // be reloaded be itself.
  //
  Status = gBS->LocateProtocol (&gEfiCallerIdGuid, NULL, &Interface);
  if (EFI_ERROR (Status)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Reload Image to below 4G Reserved Memory.

  It will run the original PE COFF entrypoint.

  In entrypoint, the driver is expected to call IsImgaeInReservedMemory()
  to know if it is 1st entry in normal memory or 2nd entry in reserved memory.

  @return Status
**/
EFI_STATUS
EFIAPI
ReloadImageToReservedMemoryBelow4G (
  VOID
  )
{
  EFI_STATUS                                    Status;
  UINT8                                         *Buffer;
  UINTN                                         BufferSize;
  EFI_HANDLE                                    NewImageHandle;
  UINTN                                         Pages;
  EFI_PHYSICAL_ADDRESS                          FfsBuffer;
  PE_COFF_LOADER_IMAGE_CONTEXT                  ImageContext;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR               MemDesc;

  //
  // A workaround: Here we install a dummy handle
  //
  NewImageHandle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &NewImageHandle,
                  &gEfiCallerIdGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Reload BootScriptExecutor image itself to RESERVED mem
  //
  Status = GetSectionFromAnyFv  (
             &gEfiCallerIdGuid,
             EFI_SECTION_PE32,
             0,
             (VOID **) &Buffer,
             &BufferSize
             );
  ASSERT_EFI_ERROR (Status);
  ImageContext.Handle    = Buffer;
  ImageContext.ImageRead = PeCoffLoaderImageReadFromMemory;
  //
  // Get information about the image being loaded
  //
  Status = PeCoffLoaderGetImageInfo (&ImageContext);
  ASSERT_EFI_ERROR (Status);
  if (ImageContext.SectionAlignment > EFI_PAGE_SIZE) {
    Pages = EFI_SIZE_TO_PAGES ((UINTN) (ImageContext.ImageSize + ImageContext.SectionAlignment));
  } else {
    Pages = EFI_SIZE_TO_PAGES ((UINTN) ImageContext.ImageSize);
  }
  FfsBuffer = 0xFFFFFFFF;
  Status = gBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiReservedMemoryType,
                  Pages,
                  &FfsBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Make sure that the buffer can be used to store code.
  //
  Status = gDS->GetMemorySpaceDescriptor (FfsBuffer, &MemDesc);
  if (!EFI_ERROR (Status) && (MemDesc.Attributes & EFI_MEMORY_XP) != 0) {
    gDS->SetMemorySpaceAttributes (
           FfsBuffer,
           EFI_PAGES_TO_SIZE (Pages),
           MemDesc.Attributes & (~EFI_MEMORY_XP)
           );
  }
  ImageContext.ImageAddress = (PHYSICAL_ADDRESS)(UINTN)FfsBuffer;
  //
  // Align buffer on section boundry
  //
  ImageContext.ImageAddress += ImageContext.SectionAlignment - 1;
  ImageContext.ImageAddress &= ~((EFI_PHYSICAL_ADDRESS)ImageContext.SectionAlignment - 1);
  //
  // Load the image to our new buffer
  //
  Status = PeCoffLoaderLoadImage (&ImageContext);
  ASSERT_EFI_ERROR (Status);

  //
  // Relocate the image in our new buffer
  //
  Status = PeCoffLoaderRelocateImage (&ImageContext);
  ASSERT_EFI_ERROR (Status);

  //
  // Free the buffer allocated by ReadSection since the image has been relocated in the new buffer
  //
  gBS->FreePool (Buffer);

  //
  // Flush the instruction cache so the image data is written before we execute it
  //
  InvalidateInstructionCacheRange ((VOID *)(UINTN)ImageContext.ImageAddress, (UINTN)ImageContext.ImageSize);

  RegisterMemoryProfileImage (
    &gEfiCallerIdGuid,
    ImageContext.ImageAddress,
    ImageContext.ImageSize,
    EFI_FV_FILETYPE_DRIVER
    );

  Status = ((EFI_IMAGE_ENTRY_POINT)(UINTN)(ImageContext.EntryPoint)) (NewImageHandle, gST);
  return Status;
}

/**
  Entrypoint for the LegacyBiosReverseThunk driver.

  @param  ImageHandle   ImageHandle of the loaded driver.
  @param  SystemTable   Pointer to the System Table.

  @retval EFI_SUCCESS   LegacyBiosReverseThunk is successfully created.
**/
EFI_STATUS
EFIAPI
InitializeLegacyBiosReverseThunkEntrypoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  if (!IsImgaeInReservedMemory()) {
    ReloadImageToReservedMemoryBelow4G ();
  } else {
    InitializeLegacyBiosReverseThunk (ImageHandle, SystemTable);
  }

  return EFI_SUCCESS;
}
