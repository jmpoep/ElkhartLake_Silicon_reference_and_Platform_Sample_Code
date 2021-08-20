/** @file
  Real Time Register File Library

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <PiDxe.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include "UfsDevicePath.h"
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>


#define RT_FILE       L"RT.bin"

EFI_GUID gEfiBdpTypeSystemPartGuid =  { 0xebd0a0a3, 0xb9e5, 0x4433, { 0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7 }};

EFI_STATUS
GetRtFile (
  OUT VOID     **Buffer,
  OUT UINTN    *BufferSize
  )
{
  UINT8                                 Index;
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleArray;
  UINTN                                 HandleArrayCount;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *FileSystem;
  EFI_FILE                              *Root;
  EFI_FILE                              *FileHandle;
  UINTN                                 FileInfoSize;
  EFI_FILE_INFO                         *FileInfo;
  EFI_GUID                              FileInfoGuid = EFI_FILE_INFO_ID;

  DEBUG ((DEBUG_INFO, "GetRtFile - entry\n"));

  HandleArray = NULL;

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiPartTypeSystemPartGuid, NULL, &HandleArrayCount, &HandleArray);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot find ESP partition. Status = %r\n", Status));
    Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBdpTypeSystemPartGuid, NULL, &HandleArrayCount, &HandleArray);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot find BDP partition. Status = %r\n", Status));
      return Status;
    }
  }

  DEBUG ((DEBUG_INFO, "ESP handle count is: %d\n", HandleArrayCount));

  for (Index = 0; Index < HandleArrayCount; Index++) {
    Status = gBS->HandleProtocol (HandleArray[Index], &gEfiDevicePathProtocolGuid, (VOID **)&DevicePath);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot locate DevicePath protocol. Status = %r\n", Status));
      continue;
    }

    //
    // Get the SFS protocol from the handle
    //
    Status = gBS->HandleProtocol (HandleArray[Index], &gEfiSimpleFileSystemProtocolGuid, (VOID **) &FileSystem);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot locate SFS protocol. Status = %r\n", Status));
      continue;
    }

    //
    // Open the root directory, get EFI_FILE_PROTOCOL
    //
    Status = FileSystem->OpenVolume (FileSystem, &Root);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Cannot open volume. Status = %r\n", Status));
      return Status;
    }

    Status = Root->Open (Root, &FileHandle, RT_FILE, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Cannot open file: %s. Status = %r\n", RT_FILE, Status));
      continue;
    }

    if (FileHandle == NULL) {
      Status = EFI_UNSUPPORTED;
      DEBUG ((DEBUG_ERROR, "Failed to open root dir on partition for reading. Stautus = %r\n", Status));
      continue;
    }

    DEBUG ((DEBUG_INFO, "FileInfoRead\n"));

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
        DEBUG ((DEBUG_ERROR, "FileRead fail, GetInfo error, Status: %r\n", Status));
        continue;
      }
    }

    if (Buffer == NULL || BufferSize == NULL) {
      DEBUG ((DEBUG_INFO, "FileInfoRead only, FileInfo Status:\r\n", Status));
      continue;
    }

    DEBUG ((DEBUG_INFO, "FileRead\n"));
    FileInfo = AllocatePool (FileInfoSize);
    if (FileInfo == NULL) {
      DEBUG ((DEBUG_ERROR, "FileRead fail, AllocatePool(FileInfoSize: %x) error\n", FileInfoSize));
      return EFI_OUT_OF_RESOURCES;
    }

    Status = FileHandle->GetInfo (
                          FileHandle,
                          &FileInfoGuid,
                          &FileInfoSize,
                          FileInfo
                          );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "FileRead fail, GetInfo error, Status: %r\n", Status));
      continue;
    }

    *BufferSize = (UINT32) FileInfo->FileSize;
    if (*BufferSize != 0) {
      *Buffer = AllocateZeroPool (*BufferSize);
      if (*Buffer == NULL) {
        DEBUG ((DEBUG_ERROR, "FileRead fail, AllocatePool(FileSize: %x) error\n", *BufferSize));
        Status = EFI_OUT_OF_RESOURCES;
        continue;
      }

      Status = FileHandle->Read (
                            FileHandle,
                            BufferSize,
                            *Buffer
                            );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "FileRead fail, Read error, Status: %r\n", Status));
        continue;
      } else {
        break;
      }
    } else {
      DEBUG ((DEBUG_INFO, "File size is 0, set return Buffer to NULL.\n"));
      *Buffer = NULL;
    }

    Status = EFI_SUCCESS;
  }

  if (FileInfo != NULL) {
    FreePool (FileInfo);
  }

  DEBUG ((DEBUG_INFO, "RT File read done, Status: %r, BufferSize: %x\n", Status, *BufferSize));
  return Status;
}
