/** @file
  Library instance to support Seamless Recovery based system firmware update.
  The major functionalities are
  1. Save backup files to external storage used in recovery path.
  2. Get/Set/Clear update progress.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/SeamlessRecoverySupportLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SpiAccessLib.h>
#include <Library/PlatformFlashAccessLib.h>
#include <Library/CpuPlatformLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/DevicePathLib.h>
#include <Library/UfsDevicePath.h>
#include <Library/PrintLib.h>

#include <Protocol/SimpleFileSystem.h>
#include <Protocol/PciIo.h>
#include <Protocol/Spi.h>
#include <Library/PlatformFlashAccessLib.h>

#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>
#include <Guid/FmpCapsule.h>

#include <IndustryStandard/Pci.h>

#define MAX_CAPSULE_ON_DISK_FILE_INDEX 63

EFI_HANDLE                               mBackUpFileSystemHandle = NULL;
SYSTEM_FIRMWARE_UPDATE_PROGRESS          mPreviousUpdateProgress = {0};

/**
  Dump raw data.

  @param[in]  Data  raw data
  @param[in]  Size  raw data size

**/
VOID
InternalDumpData (
  IN UINT8   *Data8,
  IN UINTN   DataSize
  )
{
  DEBUG_CODE_BEGIN();

  UINTN      Index;

  for (Index = 0; Index < DataSize; Index++) {
    if (Index % 0x10 == 0) {
      DEBUG ((DEBUG_INFO, "\n%08X:", Index));
    }
    DEBUG ((DEBUG_INFO, " %02X", *Data8++));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG_CODE_END();
}

/**
  Calculate SHA256 Hash

  @param[in]  Data   data
  @param[in]  Size   data size
  @param[out] Digest SHA256 digest

**/
VOID
CreateSha256Hash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);
  Sha256Init (HashCtx);
  Sha256Update (HashCtx, Data, Size);
  Sha256Final (HashCtx, Digest);
  InternalDumpData (Digest, 32);

  FreePool (HashCtx);
}

/**
  Connect storage controllers to back up relevant files for Fault Tolerance/Seamless Recovery support.
  Currently only NVME and onboard SATA controller are supported.

**/
VOID
ConnectPlatformController (
  VOID
  )
{
  EFI_STATUS           Status;
  UINTN                Index;
  UINTN                HandleCount;
  EFI_HANDLE           *HandleBuffer;
  PCI_TYPE00           PciData;
  EFI_PCI_IO_PROTOCOL  *PciIo;
  UINTN                Segment;
  UINTN                Bus;
  UINTN                Device;
  UINTN                Function;
  EFI_HANDLE           DeviceHandle;

  //
  // The Early Init version of the UFS driver doesn't have a PciIo
  // instance attached, so the traditional method of attaching all
  // PCI Mass Storage devices doesn't work for UFS.
  //
  Status = EfiBootManagerConnectDevicePath ((EFI_DEVICE_PATH_PROTOCOL *) &gPlatformOnboardUfsDevice, &DeviceHandle);
  if (!EFI_ERROR (Status)) {
    gBS->ConnectController (DeviceHandle, NULL, NULL, TRUE);
  }

  HandleCount  = 0;
  HandleBuffer = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID *) &PciIo
                    );
    ASSERT_EFI_ERROR (Status);
    PciIo->GetLocation (PciIo, &Segment, &Bus, &Device, &Function);
    Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof (PciData),
                          &PciData
                          );
    if (Bus != 0) {
      //
      //  Locate all NVME controllers and connect them.
      //
      if ((PciData.Hdr.ClassCode[2] == PCI_CLASS_MASS_STORAGE) &&
          (PciData.Hdr.ClassCode[1] == PCI_CLASS_MASS_STORAGE_SOLID_STATE) &&
          (PciData.Hdr.ClassCode[0] == PCI_IF_MASS_STORAGE_SOLID_STATE_ENTERPRISE_NVMHCI)) {
        Status = gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "Connect NVME Controller on PCI %d/%d/%d - %r\n", Bus, Device, Function, Status));
        }
      }
    } else {
      //
      //  Locate Sata controllers and connect them.
      //
      if ((PciData.Hdr.ClassCode[2] == PCI_CLASS_MASS_STORAGE) &&
          (PciData.Hdr.ClassCode[1] == PCI_CLASS_MASS_STORAGE_SATADPA)) {
        Status = gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "Connect Sata Controller on PCI %d/%d/%d - %r\n", Bus, Device, Function, Status));
        }
      }
      if ((PciData.Hdr.ClassCode[2] == PCI_CLASS_MASS_STORAGE) &&
          (PciData.Hdr.ClassCode[1] == PCI_CLASS_MASS_STORAGE_RAID)) {
        //
        // In case that RAID controller has been connected before update function being invoked.
        //
        Status = gBS->DisconnectController (
                        HandleBuffer[Index],
                        NULL,
                        NULL
                        );
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "Disconnect RAID Controller on PCI %d/%d/%d - %r\n", Bus, Device, Function, Status));
        }
      }
    }
  }
  if (HandleBuffer) {
    FreePool (HandleBuffer);
  }
  return;
}

EFI_GUID gEfiBdpTypeSystemPartGuid =  { 0xebd0a0a2, 0xb9e5, 0x4433, { 0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7 }};

/**
  Find out the file system of EFI System partition to save backup files into storeage.

  @param[out] FileSystemHandle    Pointer to the file system handle would be used to keep
                                  Seamless Recovery backup files.

  @retval EFI_SUCCESS             The file system is found.
  @retval Others                  Cannot find an available file system.

**/
EFI_STATUS
SearchBackupFileSystem (
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

  DEBUG ((DEBUG_INFO, "SearchBackupFileSystem - entry\n"));

  *FileSystemHandle = NULL;
  HandleArray       = NULL;
  //
  // Search all EFI system partitions
  //
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
  Initialize mBackUpFileSystemHandle module variable

  @retval EFI_SUCCESS             Backup file system is found and assign to mBackUpFileSystemHandle
  @retval Others                  Cannot find an available file system to initialize mBackUpFileSystemHandle.

**/
EFI_STATUS
InitializeBackupFileSystem (
  VOID
  )
{
  EFI_STATUS             Status;

  if (mBackUpFileSystemHandle != NULL) {
    //
    // BackupFilesystem has been initialized.
    //
    return EFI_SUCCESS;
  }

  //
  // Connect storage and check free space.
  //
  ConnectPlatformController ();
  Status = SearchBackupFileSystem (&mBackUpFileSystemHandle);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Cannot find storage file system to support seamless recovery. Status = %r\n", Status));
  }

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

  DEBUG ((DEBUG_INFO, "DeleteBackupFile - entry\n"));

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
  Delete backup BIOS Images from the external storage.

**/
VOID
DeleteBackupBiosImages (
  VOID
  )
{
  EFI_STATUS               Status;

  Status = InitializeBackupFileSystem ();

  if (Status == EFI_SUCCESS) {
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_CURRENT_BIOS_FILE_NAME);
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_NEW_BIOS_FILE_NAME);
  }

  // Delete digest variables
  gRT->SetVariable (
         SYSFW_UPDATE_CURRENT_BIOS_DIGEST_VARIABLE_NAME,
         &gSysFwUpdateProgressGuid,
         0,
         0,
         NULL
         );

  gRT->SetVariable (
         SYSFW_UPDATE_NEW_BIOS_DIGEST_VARIABLE_NAME,
         &gSysFwUpdateProgressGuid,
         0,
         0,
         NULL
         );

}

/**
  Delete backup FvMian files from the external storage.

**/
VOID
DeleteBackupFvAdvanceds (
  VOID
  )
{
  EFI_STATUS               Status;

  Status = InitializeBackupFileSystem ();

  if (Status == EFI_SUCCESS) {
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_CURRENT_FVADV_BACKUP_FILE_NAME);
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_NEW_FVADV_BACKUP_FILE_NAME);
  }
}

/**
  Delete backup Capsule files from the external storage plus the associated NV variable.

**/
VOID
DeleteBackupCapsules (
  VOID
  )
{
  EFI_STATUS               Status;
  CHAR16                   CodFileName[30];
  UINTN                    FileIndex;

  FileIndex = 0;

  Status = InitializeBackupFileSystem ();

  if (Status == EFI_SUCCESS) {
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_CAPSULE_BACKUP_FILE_NAME);
    DeleteFile (mBackUpFileSystemHandle, SYSFW_UPDATE_WINDOWS_UX_CAPSULE_FILE_NAME);

    //
    // Delete capsules (COD.cap, COD1.cap, COD2.cap) processed from disk after cold boot here
    // Remove this code after DeleteFile is available from FatPei Driver.
    //
    StrCpyS (CodFileName, sizeof(CodFileName)/sizeof(CHAR16), L"COD.cap");
    while (TRUE) {
      if (FileIndex > 0) {
        ZeroMem (CodFileName,  sizeof (CodFileName));
        UnicodeSPrint (
          CodFileName,
          sizeof (CodFileName),
          L"COD%d.cap",
          FileIndex
          );
      }

      Status = DeleteFile (mBackUpFileSystemHandle, CodFileName);

      if ((Status == EFI_NOT_FOUND) || (FileIndex >= MAX_CAPSULE_ON_DISK_FILE_INDEX)) {
        //
        // There is no COD files, quit
        //
        Status = EFI_SUCCESS;
        break;
      }
      FileIndex++;
    }
  }

  gRT->SetVariable (
         SYSFW_UPDATE_CAPSULE_DIGEST_VARIABLE_NAME,
         &gSysFwUpdateProgressGuid,
         0,
         0,
         NULL
         );

}

/**
  Delete all backup files from the external storage plus the associated NV variable.

**/
VOID
DeleteBackupFiles (
  VOID
  )
{
  DeleteBackupFvAdvanceds ();
  DeleteBackupBiosImages();
  DeleteBackupCapsules ();
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
WriteBackupFile (
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

  DEBUG ((DEBUG_INFO, "WriteBackupFile - entry\n"));

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
  Save both current and new BIOS images to external storages.

  @param[in] BiosImage         Pointer to the new BIOS image to be written to flash.
  @param[in] BiosImageSize     The size of new BIOS image.

  @retval  EFI_SUCCESS         Successfully backed up necessary files on external storage.
  @retval  Others              Failed to back up necessary files.

**/
EFI_STATUS
SaveBiosImageToStorage (
  IN      VOID                          *BiosImage,
  IN      UINTN                         BiosImageSize
  )
{
  UINT32                  RegionOffset;
  UINT32                  RegionSize;
  UINT8                   *CurBiosBuffer;
  UINT8                   Sha256[SHA256_DIGEST_SIZE];
  EFI_STATUS              Status;

  CurBiosBuffer = NULL;

  DEBUG ((DEBUG_INFO, "SaveBiosImageToStorage - entry\n"));

  Status = InitializeBackupFileSystem ();

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 1. Delete previous backup files before creating new one
  //
  DeleteBackupBiosImages ();

  //
  // 2. Get the current BIOS info.
  //
  Status = GetUfsBiosRegion (&RegionOffset, &RegionSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read the BIOS Region information\n"));
    return Status;
  }

  if (RegionSize != BiosImageSize) {
    DEBUG ((DEBUG_ERROR, "BIOS size mismatch between current image and new image\n"));
    return EFI_DEVICE_ERROR;
  }

  //
  // 3. Save current image from flash to external storage
  //

  CurBiosBuffer = AllocateZeroPool (RegionSize);
  if (CurBiosBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "Ran out of memory resource.\n"));
    Status = EFI_OUT_OF_RESOURCES;
    return Status;
  }

  Status = GetUfsBiosImageFromFlash(CurBiosBuffer);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read current BIOS image from flash.\n"));
    goto Done;
  }

  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_CURRENT_BIOS_FILE_NAME,
             (UINT8 *) CurBiosBuffer,
             (UINTN) RegionSize
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write CurBios.fd(%r)\n", Status));
    goto Done;
  }

  //
  // 3-1. Also keep the message digest of the saved image in NV variable for integrity check.
  //
  ZeroMem (Sha256, SHA256_DIGEST_SIZE);
  DEBUG ((DEBUG_INFO, "Create Hash for current BIOS image\n"));
  CreateSha256Hash ((UINT8 *) (UINTN) CurBiosBuffer, RegionSize, Sha256);
  Status = gRT->SetVariable (
                  SYSFW_UPDATE_CURRENT_BIOS_DIGEST_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  SHA256_DIGEST_SIZE,
                  Sha256
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to keep message digest of the current BIOS image.\n"));
    goto Done;
  }

  //
  // 4. Save BIOS region of Capsule to storage.
  //
  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_NEW_BIOS_FILE_NAME,
             (UINT8 *) (UINTN) BiosImage,
             (UINTN) BiosImageSize
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write NewBios.fd(%r)\n", Status));
    DeleteBackupBiosImages ();
    goto Done;
  }

  //
  // 4-1. Also keep the message digest of the saved image in NV variable for integrity check.
  //
  ZeroMem (Sha256, SHA256_DIGEST_SIZE);
  DEBUG ((DEBUG_INFO, "Create Hash for new BIOS image\n"));
  CreateSha256Hash ((UINT8 *) (UINTN) BiosImage, BiosImageSize, Sha256);
  Status = gRT->SetVariable (
                  SYSFW_UPDATE_NEW_BIOS_DIGEST_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  SHA256_DIGEST_SIZE,
                  Sha256
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to keep message digest of the new BIOS image.\n"));
    goto Done;
  }

Done:
  if (CurBiosBuffer !=  NULL) {
    FreePool (CurBiosBuffer);
  }

  return Status;
}

EFI_STATUS
ReadBackupFile (
  IN  EFI_FILE *FileSystemHandle,
  IN  CHAR16   *FileName,
  OUT VOID     **Buffer,
  OUT UINTN    *BufferSize
  )
{
  EFI_STATUS                            Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *FileSystem;
  EFI_FILE                              *Root;
  EFI_FILE                              *FileHandle;
  UINTN                                 FileInfoSize;
  EFI_FILE_INFO                         *FileInfo;
  EFI_GUID                              FileInfoGuid = EFI_FILE_INFO_ID;

  DEBUG ((DEBUG_INFO, "WriteBackupFile - entry\n"));

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
    DEBUG ((DEBUG_ERROR, "Failed to open root dir on partition for reading. Stautus = %r\n", Status));
    return Status;
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
      return Status;
    }
  }

  if (Buffer == NULL || BufferSize == NULL) {
    DEBUG ((DEBUG_INFO, "FileInfoRead only, FileInfo Status:\r\n", Status));
    return Status;
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
    goto done;
  }

  *BufferSize = (UINT32) FileInfo->FileSize;
  if (*BufferSize != 0) {
    *Buffer = AllocateZeroPool (*BufferSize);
    if (*Buffer == NULL) {
      DEBUG ((DEBUG_ERROR, "FileRead fail, AllocatePool(FileSize: %x) error\n", *BufferSize));
      Status = EFI_OUT_OF_RESOURCES;
      goto done;
    }

    Status = FileHandle->Read (
                           FileHandle,
                           BufferSize,
                           *Buffer
                           );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "FileRead fail, Read error, Status: %r\n", Status));
      goto done;
    }

  } else {
    DEBUG ((DEBUG_INFO, "File size is 0, set return Buffer to NULL.\n"));
    *Buffer = NULL;
  }

  Status = EFI_SUCCESS;

done:
  if (FileInfo != NULL) {
    FreePool (FileInfo);
  }

  DEBUG ((DEBUG_INFO, "FileRead done, Status: %r, BufferSize: %x\n", Status, *BufferSize));
  return Status;
}

EFI_STATUS
SaveBackupBiosToFlash (
  VOID
  )
{

  return EFI_SUCCESS;
}
/**
  Save compact FvAdvanced image from both current/new BIOS to external storages.

  @param[in] FvAdvancedImage       Pointers to the compact FvAdvanced in new BIOS to be written to flash.
  @param[in] FvAdvancedImageSize   The size of FvAdvancedImage.

  @retval  EFI_SUCCESS         Successfully backed up necessary files on external storage.
  @retval  Others              Failed to back up necessary files.

**/
EFI_STATUS
SaveFvAdvancedToStorage (
  IN VOID                         *FvAdvancedImage,
  IN UINTN                        FvAdvancedImageSize,
  IN VOID                         *FvUefiBootImage,
  IN UINTN                        FvUefiBootImageSize,
  IN VOID                         *FvOsBootImage,
  IN UINTN                        FvOsBootImageSize
  )
{
  EFI_STATUS                            Status;

  DEBUG ((DEBUG_INFO, "SaveFvAdvancedToStorage - entry\n"));

  if ((FvAdvancedImage == NULL) || (FvAdvancedImageSize == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = InitializeBackupFileSystem ();

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 1. Delete previous backup files before creating new one
  //
  DeleteBackupFvAdvanceds ();

  //
  // 2. Save FvAdvanced from current flash to external storage
  //
  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_CURRENT_FVADV_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FixedPcdGet32 (PcdFlashFvAdvancedBase),
             (UINTN) FixedPcdGet32 (PcdFlashFvAdvancedSize)
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvAdvanced.fv(%r)\n", Status));
    return Status;
  }

  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_CURRENT_FVUEFI_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FixedPcdGet32 (PcdFlashFvUefiBootBase),
             (UINTN) FixedPcdGet32 (PcdFlashFvUefiBootSize)
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvUefiBoot.fv(%r)\n", Status));
    return Status;
  }

  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_CURRENT_FVOS_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FixedPcdGet32 (PcdFlashFvOsBootBase),
             (UINTN) FixedPcdGet32 (PcdFlashFvOsBootSize)
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvOsBoot.fv(%r)\n", Status));
    return Status;
  }


  //
  // 3. Save FvAdvanced from new image to external storage
  //
  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_NEW_FVADV_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FvAdvancedImage,
             FvAdvancedImageSize
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvAdvancedN.fv(%r)\n", Status));
    DeleteBackupFvAdvanceds ();
  }

  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_NEW_FVUEFI_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FvUefiBootImage,
             FvAdvancedImageSize
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvUefiBootN.fv(%r)\n", Status));
    DeleteBackupFvAdvanceds ();
  }

  Status = WriteBackupFile (
             mBackUpFileSystemHandle,
             SYSFW_UPDATE_NEW_FVOS_BACKUP_FILE_NAME,
             (UINT8 *) (UINTN) FvOsBootImage,
             FvAdvancedImageSize
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to write FvOsBootN.fv(%r)\n", Status));
    DeleteBackupFvAdvanceds ();
  }

  return Status;
}

/**
  Search for a FMP capsule corredspnding to current FMP driver.

  @retval Pointer to the capsule hob found.
          NULL means no such capsules there.

**/
EFI_HOB_UEFI_CAPSULE *
SearchThisFmpCapsule (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS                          HobPointer;
  EFI_CAPSULE_HEADER                            *CapsuleHeader;
  EFI_FIRMWARE_MANAGEMENT_CAPSULE_HEADER        *FmpCapsuleHeader;
  EFI_FIRMWARE_MANAGEMENT_CAPSULE_IMAGE_HEADER  *ImageHeader;
  UINTN                                         Index;
  UINT64                                        *ItemOffsetList;

  //
  // Search all capsule images from hob
  //
  HobPointer.Raw = GetHobList ();
  while ((HobPointer.Raw = GetNextHob (EFI_HOB_TYPE_UEFI_CAPSULE, HobPointer.Raw)) != NULL) {
    CapsuleHeader = (EFI_CAPSULE_HEADER *) (UINTN) HobPointer.Capsule->BaseAddress;

    //
    // Must be a nested FMP capsule or FMP capsule with PcdSystemFmpCapsuleImageTypeIdGuid
    //
    if (CompareGuid (&CapsuleHeader->CapsuleGuid, &gEfiCallerIdGuid)) {
      CapsuleHeader = (EFI_CAPSULE_HEADER *)((UINT8 *)CapsuleHeader + CapsuleHeader->HeaderSize);
    }

    if (!CompareGuid (&gEfiFmpCapsuleGuid, &CapsuleHeader->CapsuleGuid)) {
      HobPointer.Raw = GET_NEXT_HOB (HobPointer);
      continue;
    }

    FmpCapsuleHeader = (EFI_FIRMWARE_MANAGEMENT_CAPSULE_HEADER *)((UINT8 *)CapsuleHeader + CapsuleHeader->HeaderSize);
    ItemOffsetList = (UINT64 *)(FmpCapsuleHeader + 1);
    for (Index = FmpCapsuleHeader->EmbeddedDriverCount; Index < (UINT32)FmpCapsuleHeader->EmbeddedDriverCount + FmpCapsuleHeader->PayloadItemCount; Index++) {
      ImageHeader = (EFI_FIRMWARE_MANAGEMENT_CAPSULE_IMAGE_HEADER *)((UINT8 *)FmpCapsuleHeader + ItemOffsetList[Index]);
      if (CompareGuid (&ImageHeader->UpdateImageTypeId, &gEfiCallerIdGuid)) {
        DEBUG ((DEBUG_INFO, "Target FMP capsule is detected(%g).\n", &gEfiCallerIdGuid));
        return HobPointer.Capsule;
      }
    }

    HobPointer.Raw = GET_NEXT_HOB (HobPointer);
  }

  return NULL;
}

/**
  Search for Windows UX Capsule

  @retval Pointer to the capsule hob found.
          NULL means no such capsules there.

**/
EFI_HOB_UEFI_CAPSULE *
SearchWindowsUxCapsule (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS                          HobPointer;
  EFI_CAPSULE_HEADER                            *CapsuleHeader;

  //
  // Search all capsule images from hob
  //
  HobPointer.Raw = GetHobList ();
  while ((HobPointer.Raw = GetNextHob (EFI_HOB_TYPE_UEFI_CAPSULE, HobPointer.Raw)) != NULL) {
    CapsuleHeader = (EFI_CAPSULE_HEADER *) (UINTN) HobPointer.Capsule->BaseAddress;

    if (CompareGuid (&CapsuleHeader->CapsuleGuid, &gWindowsUxCapsuleGuid)) {
      DEBUG ((DEBUG_INFO, "Windows UX capsule is detected\n"));
      return HobPointer.Capsule;
    }

    HobPointer.Raw = GET_NEXT_HOB (HobPointer);
  }

  return NULL;
}

/**
  Save current FMP Capsule and UX Capsule to external storages.

  @param[in] PayloadImage       Pointer to FMP payload image (FMP image header is stripped off).
  @param[in] PayloadImageSize   The size of PayloadImage.

  @retval  EFI_SUCCESS    Successfully backed up necessary files on external storage.
  @retval  Others         Failed to back up necessary files.

**/
EFI_STATUS
SaveCurrentCapsuleToStorage (
  IN VOID                         *PayloadImage,
  IN UINTN                        PayloadImageSize
  )
{
  EFI_STATUS                            Status;
  EFI_HOB_UEFI_CAPSULE                  *CurrentFmpCapsule;
  EFI_HOB_UEFI_CAPSULE                  *WindowsUxCapsule;
  UINT8                                 Sha256[SHA256_DIGEST_SIZE];

  DEBUG ((DEBUG_INFO, "SaveCurrentCapsuleToStorage - entry\n"));

  if ((PayloadImage == NULL) || (PayloadImageSize == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = InitializeBackupFileSystem ();

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 1. Delete previous backup files before creating new one
  //
  DeleteBackupCapsules ();

  //
  // 2. Save current Capsule (including Capsule/FMP header) to external storage
  //
  CurrentFmpCapsule = SearchThisFmpCapsule ();
  if (CurrentFmpCapsule == NULL) {
    DEBUG ((DEBUG_ERROR, "Cannot find Capsule image(%g)\n", &gEfiCallerIdGuid));
    return EFI_NOT_FOUND;
  }

  //
  // Make sure it's the right capsule.
  //
  if (((UINT64) PayloadImage < CurrentFmpCapsule->BaseAddress) || ((UINT64) PayloadImage > (CurrentFmpCapsule->BaseAddress + CurrentFmpCapsule->Length))) {
    DEBUG ((DEBUG_INFO, "PayloadImage = 0x%x\n", PayloadImage));
    DEBUG ((DEBUG_INFO, "CapsuleAddress = 0x%x to 0x%x\n", CurrentFmpCapsule->BaseAddress, CurrentFmpCapsule->BaseAddress + CurrentFmpCapsule->Length));
    DEBUG ((DEBUG_ERROR, "Cannot find corresponding Capsule image.\n"));
    return EFI_NOT_FOUND;
  }

  Status = WriteBackupFile (mBackUpFileSystemHandle, SYSFW_UPDATE_CAPSULE_BACKUP_FILE_NAME, (UINT8 *) (UINTN) CurrentFmpCapsule->BaseAddress, CurrentFmpCapsule->Length);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 2-1. Also keep the messag digest of the saved capsule image in NV variable for integrity check.
  //
  ZeroMem (Sha256, SHA256_DIGEST_SIZE);
  DEBUG ((DEBUG_INFO, "Create Capsule digest:\n"));
  CreateSha256Hash ((UINT8 *) (UINTN) CurrentFmpCapsule->BaseAddress, CurrentFmpCapsule->Length, Sha256);
  Status = gRT->SetVariable (
                  SYSFW_UPDATE_CAPSULE_DIGEST_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  SHA256_DIGEST_SIZE,
                  Sha256
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to keep message digest of the saved Capsule image.\n"));
    goto ClearBackup;
  }

  //
  // 3. Save Windows UX Capsule to external storage if there is one.
  //
  WindowsUxCapsule = SearchWindowsUxCapsule ();
  if (WindowsUxCapsule != NULL) {
    DEBUG ((DEBUG_INFO, "Save Windows UX Capsule to external storage.\n"));
    WriteBackupFile (
      mBackUpFileSystemHandle,
      SYSFW_UPDATE_WINDOWS_UX_CAPSULE_FILE_NAME,
      (UINT8 *) (UINTN) WindowsUxCapsule->BaseAddress,
      WindowsUxCapsule->Length
      );
  }

ClearBackup:
  if (EFI_ERROR (Status)) {
    DeleteBackupCapsules ();
  }

  return Status;
}

/**
  Check platform capability to support Fault tolerance based system firmware update.

  @retval TRUE  Current platform is capable of supporting Fault tolerance based system firmware update.
  @retval FALSE Current platform is incapable of supporting Fault tolerance based system firmware update.

**/
BOOLEAN
IsBiosFaultTolerantUpdateSupported (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Check PlatformCheckFtSupported.\n"));

  return TRUE;
}

/**
  Check if system firmware update got interrupted last time.

  @param[in,out] PreviousUpdateProgress      Pointers to the progress where updating process got
                                             interrupted last time.

  @retval TRUE   Previous update process got interrupted.
  @retval FALSE  There is no indication that update was in progress.

**/
BOOLEAN
IsPreviousUpdateUnfinished (
  IN OUT SYSTEM_FIRMWARE_UPDATE_PROGRESS       *PreviousUpdateProgress
  )
{
  if (PreviousUpdateProgress != NULL) {
    PreviousUpdateProgress->Component = mPreviousUpdateProgress.Component;
    PreviousUpdateProgress->Progress  = mPreviousUpdateProgress.Progress;
  }

  return (mPreviousUpdateProgress.Component != NotStarted) ? TRUE : FALSE;
}

/**
  Record the current update progress

  @param[in] UpdatingComponent      The FW component being updated now.
  @param[in] UpdatingProgress       The updating stage associated to UpdatingComponent

  @retval EFI_SUCCESS   Update progress is recorded to NV storage successfully.
  @retval Others        Update progress is not recorded.

**/
EFI_STATUS
SetUpdateProgress (
  IN SYSTEM_FIRMWARE_COMPONENT  UpdatingComponent,
  IN UINT32                     UpdatingProgress
  )
{
  EFI_STATUS                            Status;
  SYSTEM_FIRMWARE_UPDATE_PROGRESS       UpdateProgress;

  UpdateProgress.Component = UpdatingComponent;
  UpdateProgress.Progress  = UpdatingProgress;

  Status = gRT->SetVariable (
                  SYSFW_UPDATE_PROGRESS_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof (SYSTEM_FIRMWARE_UPDATE_PROGRESS),
                  &UpdateProgress
                  );

  return Status;
}

/**
  Clear update progress in NV storage. This indicates that no FW update process is happening.

**/
VOID
ClearUpdateProgress (
  VOID
  )
{
  EFI_STATUS         Status;

  //
  // Delete progress variable
  //
  Status = gRT->SetVariable (
                  SYSFW_UPDATE_PROGRESS_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  0,
                  0,
                  NULL
                  );

  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
FindFileByGuid (
  IN  EFI_GUID                     *FileGuid,
  IN  UINT32                       FvBase,
  IN  UINT32                       FvSize,
  OUT VOID                         **Buffer,
  OUT UINTN                        *Length
  )
{
  EFI_STATUS                         Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL      *Fv;
  UINT32                             AuthenticationStatus;
  UINTN                              Size;
  UINTN                              Index;
  UINTN                              FvHandleCount;
  EFI_HANDLE                         *FvHandleBuffer;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &FvHandleCount,
                  &FvHandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < FvHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    FvHandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **)&Fv
                    );
    if (EFI_ERROR (Status)) {
      break;
    }

    *Buffer = NULL;
    Size = 0;
    Status = Fv->ReadSection (
                   Fv,
                   FileGuid,
                   EFI_SECTION_RAW,
                   0,
                   Buffer,
                   &Size,
                   &AuthenticationStatus
                   );
    if (!EFI_ERROR(Status)) {
      break;
    }
  }

  FreePool (FvHandleBuffer);
  if (Index == FvHandleCount) {
    return EFI_NOT_FOUND;
  }
  return Status;
}

/**
  The constructor function of SeamlessRecoverySupportLib.

  @param[in]  ImageHandle   The firmware allocated handle for the EFI image.
  @param[in]  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor successfully .
**/
EFI_STATUS
EFIAPI
SeamlessRecoverySupportLibConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                                      Status;
  UINTN                                           VariableSize;

  //
  // Check if system is continuing from an interrupted update.
  //
  ZeroMem (&mPreviousUpdateProgress, sizeof (SYSTEM_FIRMWARE_UPDATE_PROGRESS));
  VariableSize = sizeof (SYSTEM_FIRMWARE_UPDATE_PROGRESS);

  Status = gRT->GetVariable (
                  SYSFW_UPDATE_PROGRESS_VARIABLE_NAME,
                  &gSysFwUpdateProgressGuid,
                  NULL,
                  &VariableSize,
                  &mPreviousUpdateProgress
                  );

  if ((Status != EFI_NOT_FOUND) && (Status != EFI_SUCCESS)) {
    DEBUG ((DEBUG_INFO, "Get UpdateProgress variable = %r.\n", Status));
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "Last boot UpdateProgress component = 0x%x.\n", mPreviousUpdateProgress.Component));
  DEBUG ((DEBUG_INFO, "Last boot UpdateProgress progress  = 0x%x.\n", mPreviousUpdateProgress.Progress));

  return EFI_SUCCESS;
}
