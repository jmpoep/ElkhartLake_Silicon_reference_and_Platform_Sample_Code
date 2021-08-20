/** @file
  This library migrates Capsules on memory to disk for the system which needs a
  cold reset to perform Capsule update.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>

#include <Protocol/SimpleFileSystem.h>
#include <Protocol/DevicePath.h>

#include <Guid/FileSystemInfo.h>
#include <Guid/CapsuleVendor.h>

#define  MAX_CAPSULE_ON_DISK_FILE_INDEX      63

UINTN                     mCodTimes = 0;

EFI_GUID gEfiBdpTypeSystemPartGuid =  { \
    0xebd0a0a2, 0xb9e5, 0x4433, { 0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7 } \
  };
/**
  Find out the file system of EFI System partition to save Capsule files into storeage.

  @param[out] FileSystemHandle    Pointer to the file system handle would be used to keep
                                  Seamless Recovery backup files.

  @retval EFI_SUCCESS             The file system is found.
  @retval Others                  Cannot find an available file system.

**/
EFI_STATUS
SearchCapsuleOnDiskFileSystem (
  OUT   EFI_HANDLE       *FileSystemHandle
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleArray;
  UINTN                                 HandleArrayCount;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  UINTN                                 Index;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *Fs;
  EFI_FILE                              *Root;
  EFI_FILE_SYSTEM_INFO                  *SysInfo;
  UINTN                                 SysInfoSize;

  DEBUG ((DEBUG_INFO, "SearchCapsuleOnDiskFileSystem - entry\n"));

  *FileSystemHandle = NULL;
  HandleArray       = NULL;
  //
  // Search all EFI system partitions
  //
  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiPartTypeSystemPartGuid, NULL, &HandleArrayCount, &HandleArray);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot find ESP partition. Status = %r\n", Status));
    // W/A to detect BDP partition
    Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBdpTypeSystemPartGuid, NULL, &HandleArrayCount, &HandleArray);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot find BDP partition. Status = %r\n", Status));
      return Status;
    }
  }

  DEBUG ((DEBUG_INFO, "ESP handle count is: %d\n", HandleArrayCount));

  for (Index = 0; (Index < HandleArrayCount) && (*FileSystemHandle == NULL); Index++) {
    Status = gBS->HandleProtocol (HandleArray[Index], &gEfiDevicePathProtocolGuid, (VOID **)&DevicePath);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot locate DevicePath protocol. Status = %r\n", Status));
      continue;
    }

    //
    // Get the SFS protocol from the handle
    //
    Status = gBS->HandleProtocol (HandleArray[Index], &gEfiSimpleFileSystemProtocolGuid, (VOID **)&Fs);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot locate SFS protocol. Status = %r\n", Status));
      continue;
    }

    //
    // Open the root directory, get EFI_FILE_PROTOCOL
    //
    Status = Fs->OpenVolume (Fs, &Root);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot open volume. Status = %r\n", Status));
      continue;
    }

    SysInfo     = NULL;
    SysInfoSize = 0;
    Status = Root->GetInfo (Root, &gEfiFileSystemInfoGuid, &SysInfoSize, SysInfo);
    if (Status == EFI_BUFFER_TOO_SMALL) {
      SysInfo = AllocateZeroPool (SysInfoSize);
      if (SysInfo == NULL) {
        DEBUG ((DEBUG_ERROR, "System memory is out of resource to allocate file system info buffer.\n"));
        Root->Close (Root);
        break;
      }
      Status = Root->GetInfo (Root, &gEfiFileSystemInfoGuid, &SysInfoSize, SysInfo);
      if (Status == EFI_SUCCESS) {
        DEBUG ((DEBUG_INFO, "File system info:\n"));
        DEBUG ((DEBUG_INFO, "FreeSpace:0x%x bytes\n", SysInfo->FreeSpace));
        DEBUG ((DEBUG_INFO, "BlockSize:0x%x bytes\n", SysInfo->BlockSize));
        DEBUG ((DEBUG_INFO, "ReadOnly:%x\n", SysInfo->ReadOnly));
        if ((SysInfo->FreeSpace >= SIZE_64MB) && (!SysInfo->ReadOnly)) {
          DEBUG ((DEBUG_INFO, "Available ESP found\n"));
          *FileSystemHandle = HandleArray[Index];
          Status = EFI_SUCCESS;
        }
      }
      FreePool (SysInfo);
    }

    Root->Close (Root);
  }

  if (*FileSystemHandle == NULL) {
    Status = EFI_NOT_FOUND;
  }

  FreePool (HandleArray);
  return Status;
}

/**
  Delete a file from an assigned file system.

  @param[in] FileSystemHandle    Handle of the file system that file would be deleted from.
  @param[in] FileName            Pointer to file name.

  @retval EFI_SUCCESS            File does not exist or deleted the file successfully.
  @retval Others                 Failed to delete the file.

**/
EFI_STATUS
DeleteFile (
  IN   EFI_HANDLE       FileSystemHandle,
  IN   CHAR16           *FileName
  )
{
  EFI_STATUS                            Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *FileSystem;
  EFI_FILE                              *Root;
  EFI_FILE                              *FileHandle;

  DEBUG ((DEBUG_INFO, "DeleteFile - entry\n"));

  Status = gBS->HandleProtocol (FileSystemHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&FileSystem);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot locate SFS protocol. Status = %r\n", Status));
    return Status;
  }

  //
  // Open the root directory, get EFI_FILE_PROTOCOL
  //
  Status = FileSystem->OpenVolume (FileSystem, &Root);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot open volume. Status = %r\n", Status));
    return Status;
  }

  Status = Root->Open (Root, &FileHandle, FileName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((DEBUG_INFO, "File %s does not exist. No need to delete\n", FileName));
    return Status;
  } else if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot open file: %s. Status = %r\n", FileName, Status));
    return Status;
  }

  if (FileHandle == NULL) {
    Status = EFI_UNSUPPORTED;
    DEBUG ((DEBUG_ERROR, "Failed to open root dir on partition for writing. Stautus = %r\n", Status));
    return Status;
  }

  Status = FileHandle->Delete (FileHandle);
  DEBUG ((DEBUG_INFO, "Delete %s %r\n", FileName, Status));

  Root->Close (Root);

  return Status;
}

/**
  Delete all capsule files on disk.

  @param[out] FileSystemHandle    Pointer to the file system handle would be used to keep

  @retval EFI_SUCCESS             The file system is found.
  @retval Others                  Cannot find an available file system.

**/
EFI_STATUS
DeleteAllCapsulesOnDisk (
  IN   EFI_HANDLE       FileSystemHandle
  )
{
  EFI_STATUS                     Status;
  UINTN                          Index;
  CHAR16                         CodFileName[30];

  DEBUG ((DEBUG_INFO, "Delete old Capsule images on disk\n"));

  if (FileSystemHandle == NULL) {
    DEBUG ((DEBUG_ERROR, "Invalid file system handle\n"));
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (CodFileName,  sizeof (CodFileName));
  StrCpyS (CodFileName, sizeof (CodFileName) / sizeof (CHAR16), L"COD.cap");

  Index = 0;
  while (TRUE) {
    if (Index > 0) {
      ZeroMem (CodFileName,  sizeof (CodFileName));
      UnicodeSPrint (
        CodFileName,
        sizeof (CodFileName),
        L"COD%d.cap",
        Index
        );
    }

    Status = DeleteFile (FileSystemHandle, CodFileName);

    if ((Status == EFI_NOT_FOUND) || (Index >= MAX_CAPSULE_ON_DISK_FILE_INDEX)) {
      //
      // There is no COD files, quit
      //
      Status = EFI_SUCCESS;
      break;
    }
    Index++;
  }

  return Status;
}

/**
  Write a file to an assigned file system.

  @param[in] FileSystemHandle    Handle of the file system that file would be write into.
  @param[in] FileName            Pointer to file name.
  @param[in] FileBuffer          The buffer to be written into file system.
  @param[in] FileSize            The size of FileBuffer.

  @retval EFI_SUCCESS            Wrote the file successfully.
  @retval Others                 Failed to write the file.

**/
EFI_STATUS
WriteCapsuleFile (
  IN   EFI_HANDLE       FileSystemHandle,
  IN   CHAR16           *FileName,
  IN   UINT8            *FileBuffer,
  IN   UINTN            FileSize
  )
{
  EFI_STATUS                            Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *FileSystem;
  EFI_FILE                              *Root;
  EFI_FILE                              *FileHandle;
  UINTN                                 WriteSize;

  DEBUG ((DEBUG_INFO, "WriteCapsuleFile - entry\n"));

  Status = gBS->HandleProtocol (FileSystemHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&FileSystem);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot locate SFS protocol. Status = %r\n", Status));
    return Status;
  }

  //
  // Open the root directory, get EFI_FILE_PROTOCOL
  //
  Status = FileSystem->OpenVolume (FileSystem, &Root);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot open volume. Status = %r\n", Status));
    return Status;
  }

  Status = Root->Open (Root, &FileHandle, FileName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Cannot open file: %s. Status = %r\n", FileName, Status));
    return Status;
  }

  if (FileHandle == NULL) {
    Status = EFI_UNSUPPORTED;
    DEBUG ((DEBUG_ERROR, "Failed to open root dir on partition for writing. Stautus = %r\n", Status));
    return Status;
  }

  do {
    WriteSize = (FileSize > SIZE_4KB) ? SIZE_4KB : FileSize;
    Status = FileHandle->Write (FileHandle, &WriteSize, FileBuffer);
    if (EFI_ERROR (Status)) {
      break;
    }
    FileSize = FileSize - WriteSize;
    FileBuffer = FileBuffer + WriteSize;
  } while (FileSize > 0);

  DEBUG ((DEBUG_INFO, "Write %s %r\n", FileName, Status));
  FileHandle->Close (FileHandle);
  Root->Close (Root);

  return Status;
}

/**
  Save a capsule in memory to disk

  @param[in] FileSystemHandle    Handle of the file system that file would be write into.
  @param[in] CapsuleHeader       Pointer to capsule image buffer

  @retval EFI_SUCCESS     Save the capsule to disk successfully.
  @retval Others          Save the capsule to disk unsuccessfully.

**/

EFI_STATUS
EFIAPI
SaveCapsuleToDisk (
  IN EFI_HANDLE          FileSystemHandle,
  IN EFI_CAPSULE_HEADER  *CapsuleHeader
  )
{
  CHAR16                               CodFileName[30];
  EFI_STATUS                           Status;

  DEBUG ((DEBUG_INFO, "Save Capsule image to disk\n"));

  if (FileSystemHandle == NULL) {
    DEBUG ((DEBUG_ERROR, "Invalid file system handle\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (CapsuleHeader == NULL) {
    DEBUG ((DEBUG_ERROR, "Invalid CapsuleHeader\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (mCodTimes > MAX_CAPSULE_ON_DISK_FILE_INDEX) {
    DEBUG ((DEBUG_ERROR, "Capsule number exceeds the max file number supported\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  ZeroMem (CodFileName,  sizeof (CodFileName));

  if (mCodTimes > 0) {
    UnicodeSPrint (
      CodFileName,
      sizeof (CodFileName),
      L"COD%d.cap",
      mCodTimes
      );
  } else {
    StrCpyS (CodFileName, sizeof (CodFileName) / sizeof (CHAR16), L"COD.cap");
  }

  //
  // Delete the old file if exists.
  //
  DeleteFile (FileSystemHandle, CodFileName);
  Status = WriteCapsuleFile (
             FileSystemHandle,
             CodFileName,
             (UINT8 *) CapsuleHeader,
             CapsuleHeader->CapsuleImageSize
             );
  if (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "Write Capsule on disc with file name %s\n", CodFileName));
    mCodTimes++;
  } else {
    DEBUG ((DEBUG_INFO, "Failed to write Capsule on disc (%s) with status %r\n", CodFileName, Status));
  }

  return Status;
}
