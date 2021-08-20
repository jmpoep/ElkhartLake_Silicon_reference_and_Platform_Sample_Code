/** @file
  Block IO Wrapper Library.

  Provides a standard offset/size interface to a BlockIo device.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#include <Library/BlockIoWrapperLib.h>

#include <IndustryStandard/TcgStorageCore.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/StorageSecurityCommand.h>

#define UFS_APPLICATION_RPMB_PROTOCOL 0x0001
#define UFS_WLUN_RPMB 0xC4

STATIC PROTOCOL_LIST_ENTRY *mBlockIoProtocolList  = NULL;
STATIC PROTOCOL_LIST_ENTRY *mSecurityProtocolList = NULL;

/**
  Initializes a protocol list.

  @param[out] ProtocolList            A pointer to a list of PROTOCOL_LIST_ENTRY structs.

  @retval     EFI_SUCCESS             At least one ProtocolGuid protocol was found.
  @retval     EFI_INVALID_PARAMETER   Invalid parameter.
  @retval     EFI_OUT_OF_RESOURCES    Couldn't allocate a buffer for the protocol list.
  @retval     EFI_NOT_FOUND           The protocol interface was not found.

**/
EFI_STATUS
EFIAPI
InitProtocolList (
  IN  PROTOCOL_LIST_ENTRY   **ProtocolList,
  IN  EFI_GUID              *ProtocolGuid
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINTN                     ValidHandleCount;
  UINTN                     HandleCount;
  EFI_HANDLE                *HandleBuffer;
  VOID                      *Protocol;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UFS_DEVICE_PATH           *UfsDevice;

  if ((ProtocolList == NULL) || (ProtocolGuid == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  ProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  *ProtocolList = AllocateZeroPool ((HandleCount + 1) * sizeof (PROTOCOL_LIST_ENTRY));
  if (*ProtocolList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ValidHandleCount = 0;
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (HandleBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID **) &DevicePath);
    if (EFI_ERROR (Status)) {
      continue;
    }

    while (!IsDevicePathEnd (NextDevicePathNode (DevicePath))) {
      DevicePath = NextDevicePathNode (DevicePath);
    }

    if ((DevicePath->Type == MESSAGING_DEVICE_PATH && DevicePath->SubType == MSG_UFS_DP)) {
      UfsDevice = (UFS_DEVICE_PATH *) DevicePath;

      Status = gBS->HandleProtocol (HandleBuffer[Index], ProtocolGuid, &Protocol);
      if (EFI_ERROR (Status)) {
        continue;
      } else {
        DEBUG ((DEBUG_INFO, "  UFS LUN 0x%02X\n", UfsDevice->Lun));
        (*ProtocolList)[ValidHandleCount].Protocol = Protocol;
        (*ProtocolList)[ValidHandleCount].Lun = UfsDevice->Lun;
        ValidHandleCount++;
      }
    }
  }

  if (ValidHandleCount != 0) {
    return EFI_SUCCESS;
  }

  FreePool (*ProtocolList);
  return EFI_NOT_FOUND;
}

/**
  Find an instance of ProtocolGuid for the provided LUN in the provided ProtocolList.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A protocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found OR invalid argument.

**/
VOID *
EFIAPI
GetProtocolByLun (
  IN  UINT32                  Lun,
  IN  PROTOCOL_LIST_ENTRY     *ProtocolList,
  IN  EFI_GUID                *ProtocolGuid
  )
{
  UINT32      Index;

  if ((ProtocolList == NULL) || (ProtocolGuid == NULL)) {
    return NULL;
  }

  Index = 0;
  while (ProtocolList[Index].Protocol != NULL) {
    if (ProtocolList[Index].Lun == Lun) {
      return ProtocolList[Index].Protocol;
    }
    Index++;
  }

  return NULL;
}

/**
  Find a BlockIoProtocol instance for the provided LUN.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A BlockIoProtocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found.

**/
EFI_BLOCK_IO_PROTOCOL *
EFIAPI
GetBlockIoProtocol (
  IN  UINT32                  Lun
  )
{
  if (mBlockIoProtocolList == NULL) {
    DEBUG ((DEBUG_INFO, "Locating BlockIoProtocol instances:\n"));
    InitProtocolList (&mBlockIoProtocolList, &gEfiBlockIoProtocolGuid);
  }

  if (mBlockIoProtocolList != NULL) {
    return GetProtocolByLun (Lun, mBlockIoProtocolList, &gEfiBlockIoProtocolGuid);
  }

  return NULL;
}

/**
  Find a StorageSecurityCommandProtocol instance for the provided LUN.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A StorageSecurityCommandProtocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found.

**/
EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *
EFIAPI
GetStorageSecurityCommandProtocol (
  IN  UINT32                  Lun
  )
{
  if (mSecurityProtocolList == NULL) {
    DEBUG ((DEBUG_INFO, "Locating StorageSecurityCommandProtocol instances:\n"));
    InitProtocolList (&mSecurityProtocolList, &gEfiStorageSecurityCommandProtocolGuid);
  }

  if (mSecurityProtocolList != NULL) {
    return GetProtocolByLun (Lun, mSecurityProtocolList, &gEfiStorageSecurityCommandProtocolGuid);
  }

  return NULL;
}

/**
  Check if the Security LUN is supported.

  @retval     TRUE        The Security LUN is supported.
  @retval     FALSE       The Security LUN is not supported.

**/
BOOLEAN
EFIAPI
SecurityLunSupported (
  VOID
  )
{
  return GetStorageSecurityCommandProtocol (UFS_WLUN_RPMB) != NULL;
}

/**
  Interacts with StorageSecurityCommandProtocol.

  @param[in]      PayloadBufferSize   The number of bytes to transfer.
  @param[in,out]  PayloadBuffer       A buffer with data to read into or write from.
  @param[in]      Receive             TRUE for Read, FALSE for Write.

  @retval         EFI_SUCCESS             The StorageSecurity transaction was successful.
  @retval         EFI_INVALID_PARAMETER   The PayloadBuffer pointer is NULL.
  @retval         EFI_NOT_FOUND           The RPMB BlockIo or StorageSecurityCommandProtocol is not found.
  @retval         EFI_BAD_BUFFER_SIZE     Transfer Size returned did not match provided Buffer Size.
  @retval         Other                   An error occurred in the BlocStorageSecuritykIo transaction.
**/
EFI_STATUS
EFIAPI
SecurityProtocolTransaction (
  IN      UINTN       PayloadBufferSize,
  IN OUT  VOID        *PayloadBuffer,
  IN      BOOLEAN     Receive
  )
{
  EFI_STATUS                              Status;
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL   *StorageSecurity;
  UINTN                                   PayloadTransferSize;
  UINT64                                  Timeout;

  Timeout = EFI_TIMER_PERIOD_SECONDS (1);

  if (PayloadBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "PayloadBuffer is NULL!\n"));
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  StorageSecurity = GetStorageSecurityCommandProtocol (UFS_WLUN_RPMB);
  if (StorageSecurity == NULL) {
    Status = EFI_NOT_FOUND;
    goto Exit;
  }

  Status = StorageSecurity->SendData (
                              StorageSecurity,
                              0,
                              Timeout,
                              TCG_SECURITY_PROTOCOL_JEDEC_UFS,
                              UFS_APPLICATION_RPMB_PROTOCOL,
                              PayloadBufferSize,
                              PayloadBuffer
                              );
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  if (Receive) {
    Status = StorageSecurity->ReceiveData (
                                StorageSecurity,
                                0,
                                Timeout,
                                TCG_SECURITY_PROTOCOL_JEDEC_UFS,
                                UFS_APPLICATION_RPMB_PROTOCOL,
                                PayloadBufferSize,
                                PayloadBuffer,
                                &PayloadTransferSize
                                );
    if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ReceiveData failed!\n"));
      goto Exit;
    } else if (PayloadBufferSize < PayloadTransferSize) {
      DEBUG ((DEBUG_WARN,
              "SecurityProtocol needs 0x%X bytes, buffer is only 0x%X bytes\n",
              PayloadTransferSize,
              PayloadBufferSize));
      Status = EFI_WARN_BUFFER_TOO_SMALL;
      goto Exit;
    }
  }

Exit:
  DEBUG ((DEBUG_INFO, "SecurityProtocolTransaction - %r\n", Status));
  return Status;
}

/**
  Interacts with BlockIoProtocol.

  @param[in]      Lun       The LUN on which to run the transaction.
  @param[in]      Offset    The data offset within the BlockIo device.
  @param[in]      Length    The number of bytes to transfer.
  @param[in,out]  Data      A buffer with data to read into or write from.
  @param[in]      Read      TRUE for Read, FALSE for Write.

  @retval         EFI_SUCCESS             The BlockIo transaction was successful.
  @retval         EFI_INVALID_PARAMETER   The Data pointer is NULL.
  @retval         EFI_NOT_FOUND           The requested LUN BlockIoProtocol is not found.
  @retval         EFI_OUT_OF_RESOURCES    Couldn't allocate a buffer for the transaction.
  @retval         Other                   An error occurred in the BlockIo transaction.
**/
EFI_STATUS
EFIAPI
BlockIoTransaction (
  IN      UINT32      Lun,
  IN      UINT32      Offset,
  IN      UINT32      Length,
  IN OUT  VOID        *Data,
  IN      BOOLEAN     Read
  )
{
  EFI_STATUS                Status;
  EFI_BLOCK_IO_PROTOCOL     *BlockIo;
  EFI_LBA                   Lba;
  UINTN                     BufferSize;
  VOID                      *Buffer;
  VOID                      *BufferData;
  UINT32                    BlockOffset;
  UINT32                    BlockSize;

  Buffer = NULL;
  if (Length == 0) {
    Status = EFI_SUCCESS;
    goto Exit;
  }

  if (Data == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  BlockIo = GetBlockIoProtocol (Lun);
  if (BlockIo == NULL) {
    Status = EFI_NOT_FOUND;
    goto Exit;
  }

  BlockSize = BlockIo->Media->BlockSize;

  Lba = Offset / BlockSize;
  BlockOffset = Offset % BlockSize;
  BufferSize = ((BlockOffset + Length) / BlockSize) * BlockSize;
  if ((BlockOffset + Length) % BlockSize) {
    BufferSize += BlockSize;
  }

  Buffer = AllocatePool (BufferSize);
  if (Buffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  BufferData = (VOID *) ((UINTN) Buffer + BlockOffset);

  Status = BlockIo->ReadBlocks (
                      BlockIo,
                      BlockIo->Media->MediaId,
                      Lba,
                      BufferSize,
                      Buffer
                      );
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  if (Read) {
    CopyMem (Data, BufferData, Length);
  } else {
    CopyMem (BufferData, Data, Length);

    Status = BlockIo->WriteBlocks (
                        BlockIo,
                        BlockIo->Media->MediaId,
                        Lba,
                        BufferSize,
                        Buffer
                        );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

    if (BlockIo->Media->WriteCaching) {
      Status = BlockIo->FlushBlocks (BlockIo);
    }
  }

Exit:
  if (Buffer != NULL) {
    FreePool (Buffer);
  }
  DEBUG ((DEBUG_INFO, "BlockIoTransaction - %r\n", Status));
  return Status;
}
