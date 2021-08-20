/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  Register the INT1A 16bit wrapper binary.

Copyright (c) 1999 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <PiDxe.h>

#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PeCoffLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/LegacyInterruptSupportLib.h>

#include <Protocol/TcgLegacyInt1AReady.h>

#include <Guid/MemoryProfile.h>

#include "TcgLegacy.h"

/**
  Get the TCG related status and save it locally.

  @param  Event   The Event this notify function registered to.
  @param  Context Pointer to the context data.
**/
VOID
EFIAPI
TcgHandlerInit (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  );

/**
  Handler to handle the INT1A request from CSM16.

  @param RegSet  Register set context for TCG INT1A services.

  @retval EFI_SUCCESS    The INT1A request is served successfully.

**/
EFI_STATUS
EFIAPI
TcgReverseThunkDispatcher (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  );

UINT8 mSwSmi;

#define TCG_COMMON_RESERVED_BUFFER_SIZE  0x4000
UINT8 *mTcgCommonReservedBuffer;

/**
  Return if the buffer plus length is still in TcgCommonReservedBuffer area.

  @param Buffer  Buffer to be checked.
  @param Length  Length of buffer to be checked.

  @retval TRUE  the buffer is valid.
  @retval FALSE the buffer is invalid.
**/
BOOLEAN
IsTcgBufferRangValid (
  IN UINT8  *Buffer,
  IN UINTN  Length
  )
{
  if (Length > (UINTN)mTcgCommonReservedBuffer + TCG_COMMON_RESERVED_BUFFER_SIZE - (UINTN)Buffer) {
    return FALSE;
  }

  return TRUE;
}

/**
  Issue SWSMI with EFI_IA32_REGISTER_SET context.
  This is wrapper for IssueSwSmi.
  It moves buffer from normal memory to TcgCommonReservedBuffer before IssueSwSmi().
  and moves buffer from TcgCommonReservedBuffer to normal memory after IssueSwSmi().
  So that the communication data is always in reserved memory area.

  RegSet.H.AL is SwSmi number.

  @param RegSet  EFI_IA32_REGISTER_SET context.
**/
VOID
TcgIssueSwSmi (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  )
{
  UINT8                 FuncId;
  VOID                  *Buffer;
  EFI_IA32_REGISTER_SET SafeRegSet;

  FuncId = RegSet->H.AH;
  Buffer = mTcgCommonReservedBuffer;
  CopyMem (&SafeRegSet, RegSet, sizeof(EFI_IA32_REGISTER_SET));

  //
  // Move buffer from normal memory to reserved memory
  // and update corresponding pointer
  //
  switch (FuncId) {
  case TCG_MemoryOverwriteRequest:
    {
      IPB_MOR      *SafeIpb;
      IPB_MOR      *Ipb;

      //
      // Construct Ipb
      //
      Ipb = (VOID *)(UINTN)RegSet->E.EDI;
      if (!IsTcgBufferRangValid (Buffer, Ipb->IPBLength)) {
        goto Error;
      }
      SafeIpb = Buffer;
      CopyMem (SafeIpb, Ipb, Ipb->IPBLength);
      Buffer = (UINT8 *)Buffer + Ipb->IPBLength;
      SafeRegSet.E.EDI = (UINT32)(UINTN)SafeIpb;
    }
    break;

  default:
    ASSERT (FALSE);
    break;
  }

  //
  // Send Command
  //
  IssueSwSmi (&SafeRegSet);

  //
  // Sync Status
  //
  RegSet->E.EAX = SafeRegSet.E.EAX;

  //
  // Move buffer from reserved memory to normal memory
  // and update corresponding pointer
  //
  switch (FuncId) {
  case TCG_MemoryOverwriteRequest:
    break;

  default:
    ASSERT (FALSE);
    break;
  }

  return ;

Error:
  ASSERT(FALSE);
  CpuDeadLoop ();
  RegSet->E.EAX = TCG_PC_INVALID_PARAM;
  return ;
}

/**
  Native entrypoint for ReverseThunk call.

  The reverse thunk saves register set at entry, and restores them at exit.
  The native code may update them, and the update will be applied when reverse thunk return.

  This interface is called at runtime. Do not use any BS or RT services.
  Do not enable interrupt.

  @param RegSet  Register set context for reverse thunk call.
**/
VOID
EFIAPI
TcgLegacyNativeHandle (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  )
{
  EFI_IA32_REGISTER_SET NativeRegSet;
  UINT8                 FuncId;

  FuncId = RegSet->H.AL;
  if (FuncId == TCG_StatusCheck) {
    RegSet->H.AH = RegSet->H.AL;
    RegSet->H.AL = mSwSmi;
    TcgReverseThunkDispatcher (RegSet);
    RegSet->E.EFlags.CF = 0;
    return ;
  }

  if (RegSet->E.EBX != 0x41504354) {
    RegSet->E.EFlags.CF = 1;
    RegSet->H.AH = 0x86;
    return ;
  }

  if (FuncId == TCG_CompactHashLogExtendEvent) {
    RegSet->H.AH = FuncId;
    RegSet->H.AL = mSwSmi;
    CopyMem (&NativeRegSet, RegSet, sizeof(NativeRegSet));
    //
    // ES:DI points to the buffer to be hashed.  In preperation for the SMI
    // call to the TPM driver interface put the flat ES:DI pointer into EDI
    // then make the SMI call.
    //
    NativeRegSet.E.EDI = RegSet->X.DI + (RegSet->X.ES << 4);
    TcgReverseThunkDispatcher (&NativeRegSet);
    RegSet->E.EAX = NativeRegSet.E.EAX;
    RegSet->E.EDX = NativeRegSet.E.EDX;
    RegSet->E.EFlags.CF = 0;
    return ;
  }

  else if (FuncId == TCG_MemoryOverwriteRequest) {
    RegSet->H.AH = FuncId;
    RegSet->H.AL = mSwSmi;
    CopyMem (&NativeRegSet, RegSet, sizeof(NativeRegSet));
    //
    // For most TCG INT 1Ah calls, ES:DI points to an input buffer and
    // DS:SI points to an output buffer.  In preparation for the SMI
    // call to the TPM driver interface put the flat ES:DI pointer into
    // EDI and the flat DS:SI pointer int ESI
    //
    NativeRegSet.E.EDI = RegSet->X.DI + (RegSet->X.ES << 4);
    NativeRegSet.E.ESI = RegSet->X.SI + (RegSet->X.DS << 4);
    TcgIssueSwSmi (&NativeRegSet);
    RegSet->E.EAX = NativeRegSet.E.EAX;
    RegSet->E.EFlags.CF = 0;
    return ;
  }

  else {
    RegSet->H.AH = FuncId;
    RegSet->H.AL = mSwSmi;
    CopyMem (&NativeRegSet, RegSet, sizeof(NativeRegSet));
    //
    // For most TCG INT 1Ah calls, ES:DI points to an input buffer and
    // DS:SI points to an output buffer.  In preparation for the SMI
    // call to the TPM driver interface put the flat ES:DI pointer into
    // EDI and the flat DS:SI pointer int ESI
    //
    NativeRegSet.E.EDI = RegSet->X.DI + (RegSet->X.ES << 4);
    NativeRegSet.E.ESI = RegSet->X.SI + (RegSet->X.DS << 4);
    TcgReverseThunkDispatcher (&NativeRegSet);
    RegSet->E.EAX = NativeRegSet.E.EAX;
    RegSet->E.EFlags.CF = 0;
    return ;
  }
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

/**
  Initialize TcgLegacyInstallInt1A.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
TcgLegacyInstallInt1A (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                        Status;
  TCG_LEGACY_INT1A_READY_PROTOCOL   *Int1AReady;

  Status = gBS->LocateProtocol (&gTcgLegacyInt1AReadyProtocolGuid, NULL, (VOID **) &Int1AReady);
  ASSERT_EFI_ERROR (Status);

  //
  // Update the SMI Command value
  //
  mSwSmi = Int1AReady->SwSmiInputValue;

  DEBUG ((EFI_D_ERROR, "Load TCG Int1A SwSmi - 0x%x\n", mSwSmi));
  Status = InstallLegacyInterruptWithReverseThunk (0x1A, LEGACY_TCG_SERVICE, LegacyRegisterAH, TcgLegacyNativeHandle);
  ASSERT_EFI_ERROR (Status);

  mTcgCommonReservedBuffer = AllocateReservedMemoryBelow4G (TCG_COMMON_RESERVED_BUFFER_SIZE);
  ASSERT (mTcgCommonReservedBuffer != NULL);

  //
  // Assuming TCG Protocol has been installed.
  //
  TcgHandlerInit (NULL, NULL);

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
  Entrypoint for TcgLegacyInstallInt1A.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
TcgLegacyInstallInt1AEntrypoint (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  if (!IsImgaeInReservedMemory()) {
    ReloadImageToReservedMemoryBelow4G ();
  } else {
    TcgLegacyInstallInt1A (ImageHandle, SystemTable);
  }

  return EFI_SUCCESS;
}
