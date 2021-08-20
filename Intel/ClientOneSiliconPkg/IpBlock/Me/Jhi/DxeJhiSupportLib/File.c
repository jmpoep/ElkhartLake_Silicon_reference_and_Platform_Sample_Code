/** @file
  Implementation file for functionality of file access

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include "JhiInternal.h"

/**
  Open file.

  @param[in] Filename             The file to be opened.
                                  Filename should be absolute path+filename, ie: L"\\Jhi\\TestApplet.sign"
  @param[out] FileHandle          Pointer to the file handle.

  @retval EFI_SUCCESS             File open successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval                         Others for error status code of LocateHandleBuffer, HandleProtocol,  OpenVolume, and Open functions.
**/
EFI_STATUS
FileOpen (
  IN  CHAR16 *Filename,
  OUT EFI_FILE **FileHandle
  )
{
  EFI_STATUS Status;
  UINTN Index;
  UINTN HandleCount;
  EFI_HANDLE *HandleBuffer;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFs;

  EFI_FILE *RootVol;

  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileOpen(%s)\n", Filename));

  if (Filename == NULL || FileHandle == NULL) {
    DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileOpen fail, invalid parameter\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleFileSystemProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileOpen fail, LocateHandleBuffer error: %r\n", Status));
    return Status;
  }

  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "SimpleFileProtocol: HandleCount: %x\n", HandleCount));
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer [Index],
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID **) &SimpleFs
                    );

    if (!EFI_ERROR (Status)) {
      Status = SimpleFs->OpenVolume (SimpleFs, &RootVol);
      if (!EFI_ERROR (Status)) {
        Status = RootVol->Open (RootVol, FileHandle, Filename, EFI_FILE_MODE_READ, 0);
        if (!EFI_ERROR (Status)) {
          DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileOpen success\n"));
          break;
        }
      }
    }
  }
  FreePool (HandleBuffer);
  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileOpen done, Status: %r\n", Status));

  return Status;
}

/**
  Close file and relase all allocated resource.

  @param[in] FileHandle          Pointer to the file handle.

  @retval EFI_SUCCESS             File close successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval                         Others for error status code of Close function.
**/
EFI_STATUS
FileClose (
  IN  EFI_FILE *FileHandle
  )
{
  EFI_STATUS    Status;

  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileClose\n"));
  if (FileHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = FileHandle->Close (FileHandle);
  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileClose done, Status: %r\n", Status));
  return Status;
}

/**
  Read file contents to the buffer.

  @param[in] FileHandle           Pointer to the file handle.
  @param[out] Buffer              Pointer to the buffer for read.
  @param[out] BufferSize          Pointer to the buffer size for read.

  @retval EFI_SUCCESS             File read successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES    Memory allocation fail.
  @retval                         Others for error status code of GetInfo, and Read functions.
**/
EFI_STATUS
FileRead (
  IN  EFI_FILE *FileHandle,
  OUT VOID    **Buffer,
  OUT UINTN   *BufferSize
  )
{
  EFI_STATUS    Status;
  EFI_GUID      FileInfoGuid = EFI_FILE_INFO_ID;
  UINTN         FileInfoSize;
  EFI_FILE_INFO *FileInfo;

  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileRead\n"));
  if (FileHandle == NULL || Buffer == NULL || BufferSize == NULL) {
    DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, invalid parameter\n"));
    return EFI_INVALID_PARAMETER;
  }

  FileInfoSize = 0;
  FileInfo = NULL;

  Status = FileHandle->GetInfo (
                         FileHandle,
                         &FileInfoGuid,
                         &FileInfoSize,
                         NULL
                         );

  if (EFI_ERROR (Status)) {
    if (Status != EFI_BUFFER_TOO_SMALL) {
      DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, GetInfo error, Status: %r\n", Status));
      return Status;
    }
  }

  FileInfo = AllocatePool (FileInfoSize);
  if (FileInfo == NULL) {
    DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, AllocatePool(FileInfoSize: %x) error\n", FileInfoSize));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = FileHandle->GetInfo (
                         FileHandle,
                         &FileInfoGuid,
                         &FileInfoSize,
                         FileInfo
                         );
  if (EFI_ERROR (Status)) {
    DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, GetInfo error, Status: %r\n", Status));
    goto done;
  }

  *BufferSize = (UINT32) FileInfo->FileSize;
  if (*BufferSize != 0) {
    *Buffer = AllocateZeroPool (*BufferSize);
    if (*Buffer == NULL) {
      DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, AllocatePool(FileSize: %x) error\n", *BufferSize));
      Status = EFI_OUT_OF_RESOURCES;
      goto done;
    }

    Status = FileHandle->Read (
                           FileHandle,
                           BufferSize,
                           *Buffer
                           );
    if (EFI_ERROR (Status)) {
      DEBUG_JHIHLP_LIB ((DEBUG_ERROR, "FileRead fail, Read error, Status: %r\n", Status));
      goto done;
    }

  } else {
    DEBUG_JHIHLP_LIB ((DEBUG_INFO, "File size is 0, set return Buffer to NULL.\n"));
    *Buffer = NULL;
  }

  Status = EFI_SUCCESS;

done:
  if (FileInfo != NULL) {
    FreePool (FileInfo);
  }

  DEBUG_JHIHLP_LIB_VERBOSE ((DEBUG_INFO, "FileRead done, Status: %r, BufferSize: %x\n", Status, *BufferSize));
  return Status;
}


