/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  Source that will provide VariableSmi Int15 services.

Copyright (c) 2011 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#include "VariableSmiInt15Dxe.h"

UINT8 *mVariableCommonReservedBuffer;
UINTN  mVariableCommonReservedBufferSize;

/**
  Return if the buffer plus length is still in VariableCommonReservedBuffer area.

  @param Buffer  Buffer to be checked.
  @param Length  Length of buffer to be checked.

  @retval TRUE  the buffer is valid.
  @retval FALSE the buffer is invalid.
**/
BOOLEAN
IsVariableBufferRangValid (
  IN UINT8  *Buffer,
  IN UINTN  Length
  )
{
  if (Length > (UINTN) mVariableCommonReservedBuffer + mVariableCommonReservedBufferSize - (UINTN) Buffer) {
    return FALSE;
  }

  return TRUE;
}


/**
  Returns the length of a Null-terminated Unicode string.

  This function returns the number of Unicode characters in the Null-terminated
  Unicode string specified by String.

  This function does not require that String is not aligned on a 16-bit boundary.

  @param  String  Pointer to a Null-terminated Unicode string.

  @return The length of String.

**/
UINTN
EFIAPI
StrLenUnaligned (
  IN      CONST CHAR16              *String
  )
{
  UINTN                             Length;

  for (Length = 0; *String != L'\0'; String++, Length++) {
  }
  return Length;
}

/**
  Returns the size of a Null-terminated Unicode string in bytes, including the
  Null terminator.

  This function returns the size, in bytes, of the Null-terminated Unicode string
  specified by String.

  This function does not require that String is not aligned on a 16-bit boundary.

  @param  String  The pointer to a Null-terminated Unicode string.

  @return The size of String.

**/
UINTN
EFIAPI
StrSizeUnaligned (
  IN      CONST CHAR16              *String
  )
{
  return (StrLenUnaligned (String) + 1) * sizeof (*String);
}

/**
  Issue SWSMI with EFI_IA32_REGISTER_SET context.
  This is wrapper for IssueSwSmi.
  It moves buffer from normal memory to VariableCommonReservedBuffer before IssueSwSmi().
  and moves buffer from VariableCommonReservedBuffer to normal memory after IssueSwSmi().
  So that the communication data is always in reserved memory area.

  RegSet.H.AL is SwSmi number.

  @param RegSet  EFI_IA32_REGISTER_SET context.
**/
VOID
VariableIssueSwSmi (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  )
{
  UINT8                 FuncId;
  VOID                  *Buffer;
  EFI_IA32_REGISTER_SET SafeRegSet;

  FuncId = RegSet->H.AH;
  Buffer = mVariableCommonReservedBuffer;
  CopyMem (&SafeRegSet, RegSet, sizeof (EFI_IA32_REGISTER_SET));

  //
  // Move buffer from normal memory to reserved memory
  // and update corresponding pointer
  //
  switch (FuncId) {
    case GET_VARIABLE_SUBFUNCTION:
    case SET_VARIABLE_SUBFUNCTION:
    {
      VARIABLE_BLOCK       *SafeVariableBlock;
      ASM_VARIABLE_BLOCK   *AsmVariableBlock;
      UINTN                VariableNameSize;
      CHAR16               *VariableName;
      VOID                 *Data;

      AsmVariableBlock = (VOID *) (UINTN) RegSet->E.EBX;
      if (!IsVariableBufferRangValid (Buffer, sizeof (*SafeVariableBlock))) {
        goto Error;
      }
      SafeVariableBlock = Buffer;
      Buffer = (UINT8 *) Buffer + sizeof (*SafeVariableBlock);
      CopyGuid (&SafeVariableBlock->VendorGuid, &AsmVariableBlock->VendorGuid);
      VariableName = (CHAR16*) ((UINTN) (AsmVariableBlock->VariableNameSegment << 4) | AsmVariableBlock->VariableNameOffset);
      VariableNameSize = StrSizeUnaligned (VariableName);
      if (!IsVariableBufferRangValid (Buffer, VariableNameSize)) {
        goto Error;
      }
      SafeVariableBlock->VariableName = (UINT32) (UINTN) Buffer;
      Buffer = (UINT8 *) Buffer + VariableNameSize;
      CopyMem ((VOID *) (UINTN) SafeVariableBlock->VariableName, VariableName, VariableNameSize);
      SafeVariableBlock->Attributes = AsmVariableBlock->Attributes;
      SafeVariableBlock->DataSize = AsmVariableBlock->DataSize;
      if (!IsVariableBufferRangValid (Buffer, SafeVariableBlock->DataSize)) {
        goto Error;
      }
      SafeVariableBlock->Data = (UINT32) (UINTN) Buffer;
      Buffer = (UINT8 *) Buffer + SafeVariableBlock->DataSize;
      if (FuncId == SET_VARIABLE_SUBFUNCTION) {
        Data = (VOID *) ((UINTN) (AsmVariableBlock->DataSegment << 4) | AsmVariableBlock->DataOffset);
        CopyMem ((VOID *) (UINTN) SafeVariableBlock->Data, Data, SafeVariableBlock->DataSize);
      }

      SafeRegSet.E.EBX = (UINT32) (UINTN) SafeVariableBlock;
    }
    break;

    case GET_NEXT_VARIABLE_SUBFUNCTION:
    {
      GET_NEXT_VARIABLE_BLOCK       *SafeGetNextVariableBlock;
      ASM_GET_NEXT_VARIABLE_BLOCK   *AsmGetNextVariableBlock;
      CHAR16                        *VariableName;

      AsmGetNextVariableBlock = (VOID *) (UINTN) RegSet->E.EBX;
      if (!IsVariableBufferRangValid (Buffer, sizeof (*SafeGetNextVariableBlock))) {
        goto Error;
      }
      SafeGetNextVariableBlock = Buffer;
      Buffer = (UINT8 *) Buffer + sizeof (*SafeGetNextVariableBlock);
      CopyGuid (&SafeGetNextVariableBlock->VendorGuid, &AsmGetNextVariableBlock->VendorGuid);
      VariableName = (CHAR16*) ((UINTN) (AsmGetNextVariableBlock->VariableNameSegment << 4) | AsmGetNextVariableBlock->VariableNameOffset);
      if (!IsVariableBufferRangValid (Buffer, AsmGetNextVariableBlock->VariableNameSize)) {
        goto Error;
      }
      SafeGetNextVariableBlock->VariableName = (UINT32) (UINTN) Buffer;
      Buffer = (UINT8 *) Buffer + AsmGetNextVariableBlock->VariableNameSize;
      CopyMem ((VOID *) (UINTN) SafeGetNextVariableBlock->VariableName, VariableName, AsmGetNextVariableBlock->VariableNameSize);
      SafeRegSet.E.EBX = (UINT32) (UINTN) SafeGetNextVariableBlock;
    }
    break;
  }

  //
  // Send Command
  //
  IssueSwSmi (&SafeRegSet);

  //
  // Sync Status
  //
  RegSet->H.AH = SafeRegSet.H.AH;
  RegSet->E.EFlags.CF = SafeRegSet.E.EFlags.CF;

  //
  // Move buffer from reserved memory to normal memory
  // and update corresponding pointer
  //
  switch (FuncId) {
    case GET_VARIABLE_SUBFUNCTION:
    {
      VARIABLE_BLOCK       *SafeVariableBlock;
      ASM_VARIABLE_BLOCK   *AsmVariableBlock;
      VOID                 *Data;

      SafeVariableBlock = (VOID *) (UINTN) SafeRegSet.E.EBX;
      AsmVariableBlock = (VOID *) (UINTN) RegSet->E.EBX;
      AsmVariableBlock->DataSize = SafeVariableBlock->DataSize;
      Data = (CHAR16*) ((UINTN) (AsmVariableBlock->DataSegment << 4) | AsmVariableBlock->DataOffset);
      CopyMem (Data, (VOID *) (UINTN) SafeVariableBlock->Data, SafeVariableBlock->DataSize);
    }
    break;

    case GET_NEXT_VARIABLE_SUBFUNCTION:
    {
      GET_NEXT_VARIABLE_BLOCK       *SafeGetNextVariableBlock;
      ASM_GET_NEXT_VARIABLE_BLOCK   *AsmGetNextVariableBlock;
      CHAR16                        *VariableName;

      SafeGetNextVariableBlock = (VOID *) (UINTN) SafeRegSet.E.EBX;
      AsmGetNextVariableBlock = (VOID *) (UINTN) RegSet->E.EBX;
      CopyMem (&AsmGetNextVariableBlock->VendorGuid, &SafeGetNextVariableBlock->VendorGuid, sizeof (SafeGetNextVariableBlock->VendorGuid));
      AsmGetNextVariableBlock->VariableNameSize = SafeGetNextVariableBlock->VariableNameSize;
      VariableName = (CHAR16*) ((UINTN) (AsmGetNextVariableBlock->VariableNameSegment << 4) | AsmGetNextVariableBlock->VariableNameOffset);
      CopyMem (VariableName, (VOID *) (UINTN) SafeGetNextVariableBlock->VariableName, SafeGetNextVariableBlock->VariableNameSize);
    }
    break;

    case EXPORT_HII_DB_SUBFUNCTION:
      RegSet->X.DX = SafeRegSet.X.DX;
      RegSet->X.BX = SafeRegSet.X.BX;
      break;
  }

  return;

Error:
  RegSet->H.AH = INVALID_VALUE;
  RegSet->E.EFlags.CF = 1;
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
VariableSmiNativeHandle (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  )
{
  EFI_IA32_REGISTER_SET NativeRegSet;

  RegSet->H.AH = RegSet->H.AL;
  RegSet->H.AL = SW_SMI_VARIABLE_SERVICES;

  switch (RegSet->H.AH) {
    case GET_VARIABLE_SUBFUNCTION:
    case GET_NEXT_VARIABLE_SUBFUNCTION:
    case SET_VARIABLE_SUBFUNCTION:
      CopyMem (&NativeRegSet, RegSet, sizeof (NativeRegSet));
      //
      // ES:DI points to the parameter block. In preperation for the SMI
      // call to the Variable driver interface put the flat ES:DI pointer into EBX
      // then make the SMI call.
      //
      NativeRegSet.E.EBX = RegSet->X.DI + (RegSet->X.ES << 4);
      VariableIssueSwSmi (&NativeRegSet);
      RegSet->H.AH = NativeRegSet.H.AH;
      RegSet->E.EFlags.CF = NativeRegSet.E.EFlags.CF;
      break;

    case EXPORT_HII_DB_SUBFUNCTION:
      CopyMem (&NativeRegSet, RegSet, sizeof (NativeRegSet));
      VariableIssueSwSmi (&NativeRegSet);
      RegSet->H.AH = NativeRegSet.H.AH;
      RegSet->E.EFlags.CF = NativeRegSet.E.EFlags.CF;
      //
      // DX:BX points to the Export Table.
      //
      RegSet->X.DX = NativeRegSet.X.DX;
      RegSet->X.BX = NativeRegSet.X.BX;
      break;

    default:
      RegSet->H.AH = NOT_SUPPORTED;
      RegSet->E.EFlags.CF = 1;
      break;
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
  Check if image is already in Reserved memory.

  @retval TRUE  Image is in Reserved memory.
  @retval FALSE Image is not in Reserved memory.
**/
BOOLEAN
EFIAPI
IsImageInReservedMemory (
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
  Reload Image to below 4G Reserved Memory.

  It will run the original PE COFF entrypoint.

  In entrypoint, the driver is expected to call IsImageInReservedMemory()
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
  This code gets variable payload size.

  @retval Variable payload size.
**/
UINTN
GetVariablePayloadSize (
  VOID
  )
{
  EFI_STATUS                                Status;
  EFI_SMM_COMMUNICATION_PROTOCOL            *SmmCommunication;
  SMM_VARIABLE_COMMUNICATE_GET_PAYLOAD_SIZE *SmmGetPayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_VARIABLE_COMMUNICATE_HEADER           *SmmVariableFunctionHeader;
  UINTN                                     CommSize;
  UINT8                                     CommBuffer[
    SMM_COMMUNICATE_HEADER_SIZE + SMM_VARIABLE_COMMUNICATE_HEADER_SIZE
    + sizeof (SMM_VARIABLE_COMMUNICATE_GET_PAYLOAD_SIZE)
  ];

  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
  ASSERT_EFI_ERROR (Status);

  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommBuffer;
  CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gEfiSmmVariableProtocolGuid);
  SmmCommunicateHeader->MessageLength = sizeof (CommBuffer) - SMM_COMMUNICATE_HEADER_SIZE;

  SmmVariableFunctionHeader = (SMM_VARIABLE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data;
  SmmVariableFunctionHeader->Function = SMM_VARIABLE_FUNCTION_GET_PAYLOAD_SIZE;
  SmmGetPayloadSize = (SMM_VARIABLE_COMMUNICATE_GET_PAYLOAD_SIZE *) SmmVariableFunctionHeader->Data;

  //
  // Send data to SMM.
  //
  CommSize = sizeof (CommBuffer);
  Status = SmmCommunication->Communicate (SmmCommunication, CommBuffer, &CommSize);
  ASSERT_EFI_ERROR (Status);

  Status = SmmVariableFunctionHeader->ReturnStatus;
  ASSERT_EFI_ERROR (Status);

  return SmmGetPayloadSize->VariablePayloadSize;
}

/**
  Initialize SmiVariableInstallInt15.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
VariableSmiInt15 (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                        Status;

  DEBUG ((EFI_D_INFO, "Load VariableSmi Int15 binary code ...\n"));
  Status = InstallLegacyInterruptWithReverseThunk (0x15, SW_SMI_VARIABLE_SERVICES, LegacyRegisterAH, VariableSmiNativeHandle);
  ASSERT_EFI_ERROR (Status);

  //
  // Need reserved memory to hold MAX variable size
  //
  mVariableCommonReservedBufferSize = ALIGN_VALUE (GetVariablePayloadSize () + sizeof (VARIABLE_BLOCK), EFI_PAGE_SIZE);
  mVariableCommonReservedBuffer     = AllocateReservedMemoryBelow4G (mVariableCommonReservedBufferSize);
  ASSERT (mVariableCommonReservedBuffer != NULL);
  return Status;
}

/**
  Entrypoint for SmiVariableInt15.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
VariableSmiInt15Entrypoint (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  if (!IsImageInReservedMemory()) {
    ReloadImageToReservedMemoryBelow4G ();
  } else {
    VariableSmiInt15 (ImageHandle, SystemTable);
  }

  return EFI_SUCCESS;
}
