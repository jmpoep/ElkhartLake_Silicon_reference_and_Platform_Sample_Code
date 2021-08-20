/** @file
  Performs USB Key Provisioning for AMT.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2018 Intel Corporation.

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
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Guid/FileInfo.h>
#include <Protocol/BlockIo.h>
#include "UsbProvision.h"
#include "ProvisionFile.h"

/**
  Prints data record entries information.

  @param[in] ProvisionRecordHandle  Pointer to provision record
**/
STATIC
VOID
PrintDataRecordInfo (
  IN PROVISION_RECORD_HANDLE  *ProvisionRecordHandle
  )
{
  DATA_RECORD_ENTRY      *DataRecordEntry;
  PROVISION_DATA_RECORD  *DataRecord;
  UINT32                 DataRecordEntryCount;
  UINT16                 Padding;
  UINT32                 DataRecordSize;

  DataRecordSize       = (UINT32) (ProvisionRecordHandle->ProvisionRecordSize);
  DataRecord           = ProvisionRecordHandle->ProvisionRecordBuffer;
  DataRecordEntry      = (DATA_RECORD_ENTRY*) ((UINTN) DataRecord + DataRecord->Header.RecordHeaderByteCount);
  DataRecordEntryCount = 0;
  do {
    switch (DataRecordEntry->ModuleIdentifier) {
      case MODULE_IDENTIFIER_INVALID:
        break;

      case MODULE_IDENTIFIER_ME_KERNEL:
        DEBUG ((DEBUG_INFO, "MODULE_IDENTIFIER_ME_KERNEL\n"));
        switch (DataRecordEntry->VariableIdentifier) {
          case VARIABLE_IDENTIFIER_ME_KERNEL_INVALID:
            DEBUG ((DEBUG_ERROR, "Invalid variable identifier\n"));
              return;

          case VARIABLE_IDENTIFIER_ME_KERNEL_CURRENT_MEBX_PASSWORD:
            DataRecordEntryCount++;
            DEBUG ((DEBUG_INFO, "VARIABLE_IDENTIFIER_ME_KERNEL_CURRENT_MEBX_PASSWORD\n"));
            break;

          case VARIABLE_IDENTIFIER_ME_KERNEL_NEW_MEBX_PASSWORD:
            DataRecordEntryCount++;
            DEBUG ((DEBUG_INFO, "VARIABLE_IDENTIFIER_ME_KERNEL_NEW_MEBX_PASSWORD\n"));
            break;
        }
        break;

      case MODULE_IDENTIFIER_INTEL_AMT_CM:
        DEBUG ((DEBUG_INFO, "MODULE_IDENTIFIER_INTEL_AMT_CM\n"));
        switch (DataRecordEntry->VariableIdentifier) {
          case VARIABLE_IDENTIFIER_INTEL_AMT_CM_INVALID:
            DEBUG ((DEBUG_ERROR, "Invalid variable identifier\n"));
            return;

          case VARIABLE_IDENTIFIER_INTEL_AMT_CM_PID:
            DataRecordEntryCount++;
            DEBUG ((DEBUG_INFO, "VARIABLE_IDENTIFIER_INTEL_AMT_CM_PID\n"));
            break;

          case VARIABLE_IDENTIFIER_INTEL_AMT_CM_PPS:
            DataRecordEntryCount++;
            DEBUG ((DEBUG_INFO, "VARIABLE_IDENTIFIER_INTEL_AMT_CM_PPS\n"));
            break;
        }
        break;
    }

    Padding = (4 - (DataRecordEntry->VariableLength % 4)) % 4;
    DataRecordEntry = (DATA_RECORD_ENTRY *) (((UINTN) &DataRecordEntry->VariableValue) + DataRecordEntry->VariableLength + Padding);
  } while ((UINTN) DataRecordEntry < ((UINTN) DataRecord + DataRecordSize));

  DEBUG ((DEBUG_INFO, "Found total of %d entries\n", DataRecordEntryCount));
}

/**
  Find and return first unconsumed data record offset in provision file.

  @param[in]  ProvisionFileHeader        Pointer to provision file header
  @param[out] DataRecordSize             On output Data Record size.
                                         Valid only if function returned TRUE
  @param[out] ProvisionDataRecordOffset  On output first unconsumed Data Record offset.
                                         Valid only if function returned TRUE

  @retval TRUE   Found unconsumed data record
  @retval FALSE  Couldn't find unconsumed data record
**/
STATIC
BOOLEAN
GetFirstUnconsumedDataRecordOffset (
  IN  PROVISION_FILE_HEADER  *ProvisionFileHeader,
  OUT UINTN                  *DataRecordSize,
  OUT UINT64                 *ProvisionDataRecordOffset
  )
{
  UINTN  FileHeaderSize;
  UINTN  ConsumedDataRecordsSize;

  //
  // If all data records have been consumed then there is nothing left to do provision with
  //
  if (ProvisionFileHeader->DataRecordsConsumed == ProvisionFileHeader->DataRecordCount) {
    return FALSE;
  }

  *DataRecordSize            = ProvisionFileHeader->DataRecordChunkCount * CHUNK_SIZE;
  ConsumedDataRecordsSize    = ProvisionFileHeader->DataRecordsConsumed  * (*DataRecordSize);
  FileHeaderSize             = ProvisionFileHeader->RecordChunkCount     * CHUNK_SIZE;
  *ProvisionDataRecordOffset = (UINT64) (FileHeaderSize + ConsumedDataRecordsSize);
  return TRUE;
}

typedef struct {
  EFI_GUID  Guid;
  UINT8     MajorVersion;
  UINT8     MinorVersion;
} PROVISION_FILE_VERSION;

/**
  Checks if provision file is valid and supported base
  on File UUID and major and minor version.

  @param[in] ProvisionFileHeader  Pointer to provision file header.

  @retval TRUE   Provision file is valid and supported
  @retval FALSE  Provision file is not valid.
**/
STATIC
BOOLEAN
IsProvisionFileValid (
    IN PROVISION_FILE_HEADER  *ProvisionFileHeader
  )
{
  UINT32                  Index;
  PROVISION_FILE_VERSION  SupportedVersions[] = {
    {FILE_TYPE_1_UUID, MAJOR_VERSION_1, MINOR_VERSION_0},
    {FILE_TYPE_2_UUID, MAJOR_VERSION_2, MINOR_VERSION_0},
    {FILE_TYPE_2_UUID, MAJOR_VERSION_2, MINOR_VERSION_1},
    {FILE_TYPE_3_UUID, MAJOR_VERSION_3, MINOR_VERSION_0},
    {FILE_TYPE_4_UUID, MAJOR_VERSION_4, MINOR_VERSION_0}
  };

  for (Index = 0; Index < ARRAY_SIZE (SupportedVersions); Index++) {
    if (CompareGuid ((EFI_GUID*) &ProvisionFileHeader->FileTypeUUID, &SupportedVersions[Index].Guid) &&
        ProvisionFileHeader->MajorVersion == SupportedVersions[Index].MajorVersion &&
        ProvisionFileHeader->MinorVersion == SupportedVersions[Index].MinorVersion) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Read provision data file header, and fill
  provided buffer with data.

  @param[in]   ProvisionFileHandle    File handle of the provision file
  @param[out]  ProvisionFileHeader    Pointer to Provision File Header

  @retval TRUE   Operation carried out successfuly
  @retval FALSE  Reading process failed
**/
STATIC
BOOLEAN
ReadProvisionFileHeader (
  IN   EFI_FILE_HANDLE         ProvisionFileHandle,
  OUT  PROVISION_FILE_HEADER   *ProvisionFileHeader
)
{
  EFI_STATUS  Status;
  UINT64      ProvisionFileHeaderSize;

  Status = ProvisionFileHandle->SetPosition (
                                  ProvisionFileHandle,
                                  0
                                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to set file handle position\n"));
    return FALSE;
  }
  ProvisionFileHeaderSize = sizeof (PROVISION_FILE_HEADER);
  Status = ProvisionFileHandle->Read (
                                  ProvisionFileHandle,
                                  (UINTN*) &ProvisionFileHeaderSize,
                                  ProvisionFileHeader
                                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read provision file header\n"));
    return FALSE;
  }
  return TRUE;
}

/**
  Build provision record

  @param[in]  ProvisionFileHandle        File handle of the provision file
  @param[in]  ProvisionDataRecordSize    Data record size
  @param[in]  ProvisionDataRecordOffset  Data record offset
  @param[out] ProvisionRecordHandle      Handle of the provision record

  @retval TRUE   Operation carried out successfuly
  @retval FALSE  Reading process failed
**/
STATIC
BOOLEAN
BuildProvisionRecordHandle (
    IN  EFI_FILE_HANDLE         ProvisionFileHandle,
    IN  UINTN                   ProvisionDataRecordSize,
    IN  UINT64                  ProvisionDataRecordOffset,
    OUT PROVISION_RECORD_HANDLE *ProvisionRecordHandle
)
{
    EFI_STATUS  Status;
    ProvisionRecordHandle->ProvisionRecordSize   = (UINT32) (ProvisionDataRecordSize);
    ProvisionRecordHandle->ProvisionRecordBuffer = AllocatePool ((UINTN) ProvisionDataRecordSize);
    if (ProvisionRecordHandle->ProvisionRecordBuffer == NULL) {
      DEBUG ((DEBUG_ERROR, "Failed to allocate provision file buffer\n"));
      return FALSE;
    }
    Status = ProvisionFileHandle->SetPosition (
                                    ProvisionFileHandle,
                                    ProvisionDataRecordOffset
                                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set file handle position\n"));
      return FALSE;
    }
    Status = ProvisionFileHandle->Read (
                                    ProvisionFileHandle,
                                    (UINTN*) &ProvisionDataRecordSize,
                                    ProvisionRecordHandle->ProvisionRecordBuffer
                                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to read provision file\n"));
      return FALSE;
    }
    //
    // Save the file handle for the remove record run.
    // We leave the file handle open for the time being, it is
    // closed later on after record has been removed.
    //
    ProvisionRecordHandle->ProvisionFileHandle = ProvisionFileHandle;
    ProvisionRecordHandle->HandleValid         = TRUE;
    return TRUE;
}

/**
  Find a valid provision data record and constructs a
  provision record handle to return to user code.

  @param[in]  ProvisionFileHandle    File handle of the provision file
  @param[out] ProvisionRecordHandle  On output handle of the valid provision record

  @retval TRUE   Valid provision record found
  @retval FALSE  Couldn't find valid provision record
**/
STATIC
BOOLEAN
FindValidDataRecordForProvision (
  IN  EFI_FILE_HANDLE          ProvisionFileHandle,
  OUT PROVISION_RECORD_HANDLE  *ProvisionRecordHandle
  )
{
  PROVISION_FILE_HEADER  ProvisionFileHeader;
  UINT64                 ProvisionDataRecordOffset;
  UINTN                  ProvisionDataRecordSize;

  if (!ReadProvisionFileHeader (ProvisionFileHandle, &ProvisionFileHeader)) {
    DEBUG ((DEBUG_INFO, "Failed reading provision file header!\n"));
    return FALSE;
  }
  if (!IsProvisionFileValid (&ProvisionFileHeader)) {
    DEBUG ((DEBUG_INFO, "Provision file unsupported!\n"));
    return FALSE;
  }
  if (GetFirstUnconsumedDataRecordOffset (&ProvisionFileHeader, &ProvisionDataRecordSize, &ProvisionDataRecordOffset)) {
    if (!BuildProvisionRecordHandle (ProvisionFileHandle, ProvisionDataRecordSize, ProvisionDataRecordOffset, ProvisionRecordHandle)) {
      DEBUG ((DEBUG_INFO, "Failed building provision data record!\n"));
      return FALSE;
    }
    DEBUG_CODE_BEGIN ();
    PrintDataRecordInfo (ProvisionRecordHandle);
    DEBUG_CODE_END ();
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Returns EFI_FILE_HANDLE of the provision file on the file system
  if present. Provisioning file search is limited to the root directory.

  This function opens file handle to provision file it is a caller responsibility
  to close it later on.

  @param[in]  FileSystemHandle     File system handle
  @param[out] ProvisionFileHandle  On output file handle to provision file.
                                   Valid only if this function returned TRUE.

  @retval TRUE   Provision file found
  @retval FALSE  Provision file not present
**/
STATIC
BOOLEAN
GetProvisionFileHandle (
  IN  EFI_HANDLE       FileSystemHandle,
  OUT EFI_FILE_HANDLE  *ProvisionFileHandle
  )
{
  EFI_STATUS                       Status;
  EFI_FILE_HANDLE                  RootFileHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *ProvisionFileVolume;

  Status = gBS->HandleProtocol (
                   FileSystemHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID **) &ProvisionFileVolume
                   );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Status = ProvisionFileVolume->OpenVolume (ProvisionFileVolume, &RootFileHandle);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Status = RootFileHandle->Open (
                             RootFileHandle,
                             ProvisionFileHandle,
                             PROVISION_FILE_NAME,
                             EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
                             0
                             );
  RootFileHandle->Close (RootFileHandle);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }
  return TRUE;
}

/**
  Checks if file system is located on USB mass storage.

  @param[in] FileSystemHandle  File system handle

  @retval TRUE  File system is located on USB mass storage
  @retval FALSE File system is not located on USB mass storage
**/
STATIC
BOOLEAN
IsFileSystemOnUsbMassStorage (
  IN EFI_HANDLE  FileSystemHandle
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;

  DevicePath = DevicePathFromHandle (FileSystemHandle);
  if (DevicePath == NULL) {
    return FALSE;
  }

  while (!IsDevicePathEnd (DevicePath)) {
    if (DevicePath->Type == MESSAGING_DEVICE_PATH && DevicePath->SubType == MSG_USB_DP) {
      return TRUE;
    } else {
      DevicePath = NextDevicePathNode (DevicePath);
    }
  }

  return FALSE;
}

/**
  This function searches file system for valid provision file
  and extract first valid provision record.

  @param[out] ProvisionRecord  Pointer to provision record.

  @retval TRUE  provision record found
  @retval FALSE provision record not found
**/
BOOLEAN
GetUsbProvisionRecord (
  OUT PROVISION_RECORD_HANDLE  *ProvisionRecordHandle
  )
{
  EFI_STATUS       Status;
  UINTN            FileSystemHandlesNum;
  EFI_HANDLE       *FileSystemHandles;
  EFI_FILE_HANDLE  ProvisionFileHandle;
  UINTN            Index;
  BOOLEAN          ProvisionRecordFound;

  ZeroMem (ProvisionRecordHandle, sizeof (PROVISION_RECORD_HANDLE));

  FileSystemHandles = NULL;
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleFileSystemProtocolGuid,
                  NULL,
                  &FileSystemHandlesNum,
                  &FileSystemHandles
                  );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  ProvisionRecordFound = FALSE;
  for (Index = 0; Index < FileSystemHandlesNum; Index++) {
    if (!IsFileSystemOnUsbMassStorage (FileSystemHandles[Index])) {
      continue;
    }

    if (!GetProvisionFileHandle (FileSystemHandles[Index], &ProvisionFileHandle)) {
      continue;
    }

    if (!FindValidDataRecordForProvision (ProvisionFileHandle, ProvisionRecordHandle)) {
      ProvisionFileHandle->Close (ProvisionFileHandle);
      continue;
    } else {
      //
      // In case we did find a valid record we leave the file handle open since
      // it will be used during record remove which is run after MEBx invocation.
      //
      ProvisionRecordFound = TRUE;
      break;
    }
  }

  if (FileSystemHandles) {
    FreePool (FileSystemHandles);
  }
  return ProvisionRecordFound;
}

/**
  Frees up all of the resources allocated for the purpose of ProvisionRecord.
  After call to this function provision record object is no longer valid.

  @param[in] ProvisionRecord  Provision record to clean up.
**/
STATIC
VOID
CleanupProvisionRecordResources (
  IN PROVISION_RECORD_HANDLE  *ProvisionRecordHandle
  )
{
  ProvisionRecordHandle->HandleValid = FALSE;
  ProvisionRecordHandle->ProvisionFileHandle->Close (ProvisionRecordHandle->ProvisionFileHandle);
  FreePool (ProvisionRecordHandle->ProvisionRecordBuffer);
}

/**
  Check if record removal is required.

  @param[in] ProvisionFileBuffer  pointer to memory with provision file
  @param[in] ReturnedDataRecord   data record as returned from MEBx

  @retval TRUE   Data record should be removed
  @retval FALSE  Data record should not be removed
**/
STATIC
BOOLEAN
IsRecordConsumptionRequired (
  IN PROVISION_FILE_HEADER  *ProvisionFileHeader,
  IN PROVISION_DATA_RECORD  *ReturnedDataRecord
  )
{
  //
  // MEBx will clear the record valid flag if record has been consumed.
  // If flag has not been cleared it means that MEBx encountered an error during
  // provisioning flow and didn't consume the record.
  //
  if (ReturnedDataRecord->Header.RecordFlags & DATA_RECORD_FLAG_VALID) {
    DEBUG ((DEBUG_ERROR, "MEBx failed to consume data record\n"));
    return FALSE;
  }

  if (ProvisionFileHeader->MajorVersion >= MAJOR_VERSION_2 &&
      (ProvisionFileHeader->FileFlags & FILE_FLAGS_DONT_CONSUME_RECORDS)) {
    DEBUG ((DEBUG_INFO, "Provision file doesn't support record consumption\n"));
    return FALSE;
  }
  return TRUE;
}

/**
  Removes consumed provision record from provision file if neccessary.

  @param[in] ProvisionRecordHandle  Consumed provision record
  @param[in] ReturnedDataRecord     Data record returned from MEBx
**/
STATIC
VOID
RemoveProvisionRecordFromFile (
  IN PROVISION_RECORD_HANDLE  *ProvisionRecordHandle,
  IN PROVISION_DATA_RECORD    *ReturnedDataRecord
  )
{
  EFI_STATUS             Status;
  PROVISION_FILE_HEADER  ProvisionFileHeader;
  UINT64                 ProvisionDataRecordOffset;
  PROVISION_DATA_RECORD  *ProvisionDataRecord;
  UINTN                  ProvisionDataRecordSize;
  UINT32                 ConsumedRecordsNumberSize;

  Status              = EFI_SUCCESS;
  ProvisionDataRecord = ProvisionRecordHandle->ProvisionRecordBuffer;

  if (!ReadProvisionFileHeader (ProvisionRecordHandle->ProvisionFileHandle, &ProvisionFileHeader)) {
    DEBUG ((DEBUG_INFO, "Failed reading provision file header!\n"));
    return;
  }

  if (IsRecordConsumptionRequired (&ProvisionFileHeader, ReturnedDataRecord)) {
    if (GetFirstUnconsumedDataRecordOffset (&ProvisionFileHeader, &ProvisionDataRecordSize, &ProvisionDataRecordOffset)) {
      ProvisionFileHeader.DataRecordsConsumed++;
      ZeroMem (
        (VOID*) (((UINTN)ProvisionDataRecord) + ProvisionDataRecord->Header.RecordHeaderByteCount),
        ProvisionDataRecordSize - ProvisionDataRecord->Header.RecordHeaderByteCount
        );
      ProvisionDataRecord->Header.RecordFlags &= ~DATA_RECORD_FLAG_VALID;
      Status = ProvisionRecordHandle->ProvisionFileHandle->SetPosition (
                                                             ProvisionRecordHandle->ProvisionFileHandle,
                                                             ProvisionDataRecordOffset
                                                             );
      if (!EFI_ERROR (Status)) {
        Status = ProvisionRecordHandle->ProvisionFileHandle->Write (
                                                               ProvisionRecordHandle->ProvisionFileHandle,
                                                               (UINTN *) &ProvisionDataRecordSize,
                                                               ProvisionRecordHandle->ProvisionRecordBuffer
                                                               );
        if (!EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "Failed writing provision file data record!\n"));
        }
      }
      //
      // Updating field Header.DataRecordsConsumed in Provision File
      //
      ConsumedRecordsNumberSize   = sizeof (ProvisionFileHeader.DataRecordsConsumed);
      Status = ProvisionRecordHandle->ProvisionFileHandle->SetPosition (
                                                             ProvisionRecordHandle->ProvisionFileHandle,
                                                             OFFSET_OF (PROVISION_FILE_HEADER, DataRecordsConsumed)
                                                             );
      if (!EFI_ERROR (Status)) {
        Status = ProvisionRecordHandle->ProvisionFileHandle->Write (
                                                               ProvisionRecordHandle->ProvisionFileHandle,
                                                               (UINTN *) &ConsumedRecordsNumberSize,
                                                               &ProvisionFileHeader.DataRecordsConsumed
                                                               );
        if (!EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "Failed writing provision file header!\n"));
        }
      }
    }
  }

  ASSERT_EFI_ERROR (Status);
}

/**
  Mark provision record as consumed if provision file
  allows consuming and MEBx consumed the record.
  This function should be called after MEBx invocation.

  This function is also responsible for cleanup of all of the
  resources allocated during initial data record discovery.
  After call to this function ProvisionRecord is no longer valid and
  shouldn't be used.

  @param[in] ProvisionRecordHandle  Provision record to consume
  @param[in] ReturnedDataRecord     Provision data record as returned from MEBx.
**/
VOID
RemoveUsbProvisionRecord (
  IN PROVISION_RECORD_HANDLE  *ProvisionRecordHandle,
  IN VOID                     *ReturnedDataRecord
  )
{
  if (ProvisionRecordHandle->HandleValid) {
    RemoveProvisionRecordFromFile (ProvisionRecordHandle, (PROVISION_DATA_RECORD *) ReturnedDataRecord);
    CleanupProvisionRecordResources (ProvisionRecordHandle);
  }
}

