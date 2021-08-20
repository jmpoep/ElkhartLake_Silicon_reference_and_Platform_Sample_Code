/** @file
  Platform Flash Access library to update different system firmware components

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PlatformFlashAccessLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/IoLib.h>
#include <Library/FWUpdateLib.h>
#include <Library/DxeMeLib.h>
#include <Library/TimerLib.h>
#include <Library/BootMediaLib.h>
#include <Library/BlockIoWrapperLib.h>
#include <Library/HobLib.h>
#include <Library/BpdtLib.h>

#include <Protocol/Spi.h>
#include <BiosGuard.h>
#include <Register/HeciRegs.h>
#include <CpuRegs.h>

//
// Used in SPI update function
//
#define UPDATE_BLOCK_SIZE                      SIZE_4KB

//
// Used in ME update function
//
#define FW_UPDATE_DISABLED                     0
#define FW_UPDATE_ENABLED                      1
#define ME_FWSTS2_TIMEOUT_COUNTER              150


PCH_SPI_PROTOCOL                               *mSpiProtocol = NULL;
//
// Use to display progress of sending ME FW
//
EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  mMeDisplayProgress = NULL;
UINTN                                          mMeSendProgressStartPercentage = 0;
UINTN                                          mMeSendProgressEndPercentage = 100;

/**
  Ufs Flash Region Type
**/
typedef enum {
  UfsFlashRegionBios,
  UfsFlashRegionMe,
  UfsFlashRegionAll,
  UfsFlashRegionMax
} UFS_FLASH_REGION_TYPE;

#define UFS_BOOT_LUN                           0x1

/**
  Initialize PCH SpiProtocol interface module pointer

  @param EFI_SUCCESS      PCH SpiProtocol interface module pointer is initialized successfully
  @param Others           Fail to locate PCH SpiProtocol interface

**/
EFI_STATUS
InitializeSpiProtocolInterface (
  VOID
  )
{
  EFI_STATUS                   Status;

  Status = EFI_SUCCESS;

  if (mSpiProtocol == NULL) {
    Status = gBS->LocateProtocol (
                    &gPchSpiProtocolGuid,
                    NULL,
                    (VOID **)&mSpiProtocol
                    );
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Erase a block (with UPDATE_BLOCK_SIZE) on SPI flash.

  This function erases one block to FlashRegionType region with give Address.

  @param[in]  FlashRegionType          The flash region to be updated.
  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
  @param[in]  Buffer                   A pointer to a buffer contains the update data.

  @retval     EFI_SUCCESS.             Operation is successful.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashEraseBlock (
  IN FLASH_REGION_TYPE                 FlashRegionType,
  IN UINT32                            FlashAddress
  )
{
  EFI_STATUS                           Status;
  UINT32                               NumBytes;

  Status = InitializeSpiProtocolInterface ();
  if (EFI_ERROR (Status)) {
    return EFI_NOT_READY;
  }

  NumBytes = UPDATE_BLOCK_SIZE;

  //
  // Erase the block
  //
  Status = mSpiProtocol->FlashErase (
                           mSpiProtocol,
                           FlashRegionType,
                           FlashAddress,
                           NumBytes
                           );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashEraseBlock: FlashErase failed at Region %d, Address 0x%x\n", FlashRegionType, FlashAddress));
    goto Done;
  }

Done:
  return Status;
}

/**
  Update a block (with UPDATE_BLOCK_SIZE) on SPI flash.

  This function updates one block to FlashRegionType region with give Address in below steps:
  1. Read one block from the destination and compare it with Buffer.
     If the content is identical, no further action is needed. Return EFI_SUCCESS directly.
  2. Erase one block from the destination.
  3. Write one block to the destination with Buffer.
  4. Read the block back from destination and compare it to ensure the write operation is successful.

  @param[in]  FlashRegionType          The flash region to be updated.
  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
  @param[in]  Buffer                   A pointer to a buffer contains the update data.

  @retval     EFI_SUCCESS.             Operation is successful.
  @retval     EFI_OUT_OF_RESOURCES     Failed to allocate needed memory buffer.
  @retval     EFI_VOLUME_CORRUPTED     The block is not updated as expected.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashUpdateBlock (
  IN FLASH_REGION_TYPE                 FlashRegionType,
  IN UINT32                            FlashAddress,
  IN UINT8                             *Buffer
  )
{
  EFI_STATUS                           Status;
  UINT32                               NumBytes;
  UINT8                                *CompareBuffer;

  Status = InitializeSpiProtocolInterface ();
  if (EFI_ERROR (Status)) {
    return EFI_NOT_READY;
  }

  NumBytes = UPDATE_BLOCK_SIZE;
  CompareBuffer = NULL;

  CompareBuffer = AllocateZeroPool (NumBytes);
  if (CompareBuffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  //
  // Compare Buffer block with the destination
  //
  Status = mSpiProtocol->FlashRead (
                           mSpiProtocol,
                           FlashRegionType,
                           FlashAddress,
                           NumBytes,
                           CompareBuffer
                           );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashUpdateBlock: FlashRead failed at Region %d, Address 0x%x\n", FlashRegionType, FlashAddress));
    goto Done;
  }

  if (CompareMem (CompareBuffer, Buffer, NumBytes) == 0) {
    //
    // No need to update this block
    //
    Status = EFI_SUCCESS;
    goto Done;
  }

  //
  // Erase the block
  //
  Status = mSpiProtocol->FlashErase (
                           mSpiProtocol,
                           FlashRegionType,
                           FlashAddress,
                           NumBytes
                           );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashUpdateBlock: FlashErase failed at Region %d, Address 0x%x\n", FlashRegionType, FlashAddress));
    goto Done;
  }

  //
  // Wrtie the block
  //
  Status = mSpiProtocol->FlashWrite (
                           mSpiProtocol,
                           FlashRegionType,
                           FlashAddress,
                           NumBytes,
                           Buffer
                           );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashUpdateBlock: FlashErase failed at Region %d, Address 0x%x\n", FlashRegionType, FlashAddress));
    goto Done;
  }

  //
  // Read buffer back to verify udpate status
  //
  ZeroMem (CompareBuffer, NumBytes);
  Status = mSpiProtocol->FlashRead (
                           mSpiProtocol,
                           FlashRegionType,
                           FlashAddress,
                           NumBytes,
                           CompareBuffer
                           );

  if (CompareMem (CompareBuffer, Buffer, NumBytes) != 0) {
    //
    // Block is not updated as expected.
    //
    Status = EFI_VOLUME_CORRUPTED;
    DEBUG ((DEBUG_ERROR, "SpiFlashUpdateBlock: Update failed at Region %d, Address 0x%x\n", FlashRegionType, FlashAddress));
  }

Done:
  if (CompareBuffer !=  NULL) {
    FreePool (CompareBuffer);
  }

  return Status;
}

/**
  Erase a buffer to SPI flash.
  The size of the buffer must be aligned to UPDATE_BLOCK_SIZE.

  @param[in]  FlashRegionType          The flash region to be updated.
  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
                                       It must be 4K aligned.
  @param[in]  Length                   Number of bytes in Buffer.
                                       It must be aligned to UPDATE_BLOCK_SIZE.
  @param[in]  Progress                 A function used report the progress of the
                                       firmware update.  This is an optional parameter
                                       that may be NULL.
  @param[in]  StartPercentage          The start completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.
  @param[in]  EndPercentage            The end completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.

  @retval     EFI_SUCCESS              Operation is successful.
  @retval     EFI_INVALID_PARAMETER    Buffer is NULL or FlashAddress/Length is not well aligned.
  @retval     EFI_OUT_OF_RESOURCES     Failed to allocate needed memory buffer.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashErase (
  IN FLASH_REGION_TYPE                              FlashRegionType,
  IN UINT32                                         FlashAddress,
  IN UINT32                                         Length,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                           Status;
  UINTN                                Index;
  EFI_PHYSICAL_ADDRESS                 Address;
  UINTN                                CountOfBlocks;

  DEBUG ((DEBUG_INFO, "SpiFlashErase - Region  %d\n", (UINTN)FlashRegionType));
  DEBUG ((DEBUG_INFO, "SpiFlashErase - Address 0x%x\n", FlashAddress));
  DEBUG ((DEBUG_INFO, "SpiFlashErase - Length  0x%x(%d)\n", Length));

  if (((Length % UPDATE_BLOCK_SIZE) != 0) || ((FlashAddress % SIZE_4KB) != 0)) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status        = EFI_SUCCESS;
  Index         = 0;
  CountOfBlocks = (UINTN) (Length / UPDATE_BLOCK_SIZE);
  Address       = FlashAddress;

  for (Index = 0; Index < CountOfBlocks; Index++) {
    if (Progress != NULL) {
      Progress (StartPercentage + ((Index * (EndPercentage - StartPercentage)) / CountOfBlocks));
    }

    Status = SpiFlashEraseBlock (FlashRegionType, (UINT32) Address);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashErase failed (%r) at Region %d - 0x%x\n", Status, FlashRegionType, Address));
      break;
    }

    Address += UPDATE_BLOCK_SIZE;
  }

  if (Progress != NULL) {
    Progress (EndPercentage);
  }

  return Status;
}

/**
  Update a buffer to SPI flash.
  The size of the buffer must be aligned to UPDATE_BLOCK_SIZE.

  @param[in]  FlashRegionType          The flash region to be updated.
  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
                                       It must be 4K aligned.
  @param[in]  Buffer                   A pointer to a buffer contains the update data.
  @param[in]  Length                   Number of bytes in Buffer.
                                       It must be aligned to UPDATE_BLOCK_SIZE.
  @param[in]  Progress                 A function used report the progress of the
                                       firmware update.  This is an optional parameter
                                       that may be NULL.
  @param[in]  StartPercentage          The start completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.
  @param[in]  EndPercentage            The end completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.

  @retval     EFI_SUCCESS              Operation is successful.
  @retval     EFI_INVALID_PARAMETER    Buffer is NULL or FlashAddress/Length is not well aligned.
  @retval     EFI_OUT_OF_RESOURCES     Failed to allocate needed memory buffer.
  @retval     EFI_VOLUME_CORRUPTED     SPI flash is not updated as expected.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashUpdate (
  IN FLASH_REGION_TYPE                              FlashRegionType,
  IN UINT32                                         FlashAddress,
  IN UINT8                                          *Buffer,
  IN UINT32                                         Length,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                           Status;
  UINTN                                Index;
  EFI_PHYSICAL_ADDRESS                 Address;
  UINTN                                CountOfBlocks;
  UINT8                                *Buf;

  DEBUG ((DEBUG_INFO, "SpiFlashUpdate - Region  %d\n", (UINTN)FlashRegionType));
  DEBUG ((DEBUG_INFO, "SpiFlashUpdate - Address 0x%x\n", FlashAddress));
  DEBUG ((DEBUG_INFO, "SpiFlashUpdate - Length  0x%x(%d)\n", Length));

  if ((Buffer == NULL) || ((Length % UPDATE_BLOCK_SIZE) != 0) || ((FlashAddress % SIZE_4KB) != 0)) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status        = EFI_SUCCESS;
  Index         = 0;
  CountOfBlocks = (UINTN) (Length / UPDATE_BLOCK_SIZE);
  Address       = FlashAddress;
  Buf           = Buffer;

  for (Index = 0; Index < CountOfBlocks; Index++) {
    if (Progress != NULL) {
      Progress (StartPercentage + ((Index * (EndPercentage - StartPercentage)) / CountOfBlocks));
    }

    Status = SpiFlashUpdateBlock (FlashRegionType, (UINT32) Address, Buf);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashUpdate failed (%r) at Region %d - 0x%x\n", Status, FlashRegionType, Address));
      break;
    }

    Address += UPDATE_BLOCK_SIZE;
    Buf += UPDATE_BLOCK_SIZE;
  }

  if (Progress != NULL) {
    Progress (EndPercentage);
  }

  return Status;
}

/**
  Update/Read a block (with UPDATE_BLOCK_SIZE) on UFS flash.

  This function updates/reads one block to FlashRegionType region with given Address in below steps:
  1. Read one block from the destination and compare it with Buffer.
     If the content is identical, no further action is needed. Return EFI_SUCCESS directly.
  2. Write the block to the destination with Buffer if destination content is not same.
  3. Read the block back from destination and compare it to ensure the write operation is successful.
  4. If Update == FALSE, read the block twice and compare, return EFI_VOLUME_CORRUPTED if comparison fails.

  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
  @param[in]  Buffer                   A pointer to a buffer contains the update data.
  @param[in]  NumBytes                 Size of the Data buffer to be updated.
  @param[in]  Update                   TRUE to Update the region, FALSE to Read only.

  @retval     EFI_SUCCESS.             Operation is successful.
  @retval     EFI_OUT_OF_RESOURCES     Failed to allocate needed memory buffer.
  @retval     EFI_VOLUME_CORRUPTED     The block is not updated as expected.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
UfsFlashUpdateBlock (
  IN UINT32                            FlashAddress,
  IN UINT8                             *Buffer,
  IN UINT32                            NumBytes,
  IN BOOLEAN                           Update
  )
{
  EFI_STATUS                           Status;
  UINT8                                *CompareBuffer;

  CompareBuffer = NULL;

  CompareBuffer = AllocateZeroPool (NumBytes);
  if (CompareBuffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  //
  // Compare Buffer block with the destination
  //
  Status = BlockIoTransaction (UFS_BOOT_LUN, FlashAddress, (UINT32) NumBytes, CompareBuffer, TRUE);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsFlashUpdateBlock: FlashRead failed at Address 0x%x\n", FlashAddress));
    goto Done;
  }
  if (Update) {
    if (CompareMem (CompareBuffer, Buffer, NumBytes) == 0) {
      //
      // No need to update this block
      //
      Status = EFI_SUCCESS;
      goto Done;
    }

    //
    // Write the block
    //
    Status = BlockIoTransaction (UFS_BOOT_LUN, FlashAddress, (UINT32) NumBytes, Buffer, FALSE);

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "UfsFlashUpdateBlock: FlashWrite failed at Address 0x%x\n", FlashAddress));
      goto Done;
    }

    //
    // Read buffer back to verify update status
    //
    ZeroMem (CompareBuffer, NumBytes);
    Status = BlockIoTransaction (UFS_BOOT_LUN, FlashAddress, (UINT32) NumBytes, CompareBuffer, TRUE);

    if (CompareMem (CompareBuffer, Buffer, NumBytes) != 0) {
      //
      // Block is not updated as expected.
      //
      Status = EFI_VOLUME_CORRUPTED;
      DEBUG ((DEBUG_ERROR, "UfsFlashUpdateBlock: Update failed at Address 0x%x\n", FlashAddress));
    }
  } else {
    Status = BlockIoTransaction (UFS_BOOT_LUN, FlashAddress, (UINT32) NumBytes, Buffer, TRUE);

    if (CompareMem (CompareBuffer, Buffer, NumBytes) != 0) {
      //
      // First read and second read are not matching, corrupted data.
      //
      Status = EFI_VOLUME_CORRUPTED;
      DEBUG ((DEBUG_ERROR, "UfsFlashUpdateBlock: FlashRead failed at Address 0x%x\n", FlashAddress));
    }
  }

Done:
  if (CompareBuffer !=  NULL) {
    FreePool (CompareBuffer);
  }

  return Status;
}

/**
  Update/Read a buffer to/from UFS flash.
  The size of the buffer must be aligned to UPDATE_BLOCK_SIZE.

  @param[in]  FlashRegionType          The flash region to be updated.
  @param[in]  Address                  Starting address within the FlashRegionType region to be updated.
  @param[in]  Buffer                   A pointer to a buffer contains the update data.
  @param[in]  Length                   Number of bytes in Buffer.
                                       It must be aligned to UPDATE_BLOCK_SIZE.
  @param[in]  Update                   TRUE to Update the region, FALSE to Read only.
  @param[in]  Progress                 A function used report the progress of the
                                       firmware update.  This is an optional parameter
                                       that may be NULL.
  @param[in]  StartPercentage          The start completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.
  @param[in]  EndPercentage            The end completion percentage value that may
                                       be used to report progress during the flash
                                       write operation.

  @retval     EFI_SUCCESS              Operation is successful.
  @retval     EFI_INVALID_PARAMETER    Buffer is NULL or FlashAddress/Length is not well aligned.
  @retval     EFI_OUT_OF_RESOURCES     Failed to allocate needed memory buffer.
  @retval     EFI_VOLUME_CORRUPTED     UFS flash is not updated as expected.
  @retval     Others                   If there is any device errors.

**/
EFI_STATUS
EFIAPI
UfsFlashUpdate (
  IN UFS_FLASH_REGION_TYPE                          FlashRegionType,
  IN UINT32                                         FlashAddress,
  IN UINT8                                          *Buffer,
  IN UINT32                                         Length,
  IN BOOLEAN                                        Update,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                           Status;
  UINTN                                Index;
  EFI_PHYSICAL_ADDRESS                 Address;
  UINTN                                CountOfBlocks;
  UINT8                                *Buf;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  UINT32                               BlockSize;
  UINT32                               RegionOffset;
  UINT32                               RegionSize;

  DEBUG ((DEBUG_INFO, "UfsFlashUpdate - Region  %d\n", (UINTN)FlashRegionType));
  DEBUG ((DEBUG_INFO, "UfsFlashUpdate - Address 0x%x, Length  0x%x\n", FlashAddress, Length));
  DEBUG ((DEBUG_INFO, "UfsFlashUpdate - Operation - %s\n", (Update ? L"Write":L"Read")));

  //
  // Get Base and Size of the region to be updated.
  //
  switch (FlashRegionType) {
    case UfsFlashRegionBios:
      Status = GetUfsBiosRegion (&RegionOffset, &RegionSize);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to read the Bios Region information\n"));
        return Status;
      }
      Address = RegionOffset + (UINT32) FlashAddress;
      break;

    default:
      return EFI_UNSUPPORTED;
  }

  //
  // Get the block size of the Flash device.
  //
  BlockIo = GetBlockIoProtocol (UFS_BOOT_LUN);
  if (BlockIo == NULL) {
    DEBUG ((DEBUG_INFO, "UfsFlashUpdate - BlockIo instance not found, abort update\n"));
    return EFI_NOT_FOUND;
  }

  BlockSize = BlockIo->Media->BlockSize;
  DEBUG ((DEBUG_INFO, "Update BlockSize - 0x%X bytes\n", BlockSize));

  if ((Buffer == NULL) || ((Length % BlockSize) != 0) || ((Address % BlockSize) != 0)) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status        = EFI_SUCCESS;
  Index         = 0;
  CountOfBlocks = (UINTN) (Length / BlockSize);
  Buf           = Buffer;

  //
  // Update block by block.
  //
  for (Index = 0; Index < CountOfBlocks; Index++) {
    if (Progress != NULL) {
      Progress (StartPercentage + ((Index * (EndPercentage - StartPercentage)) / CountOfBlocks));
    }

    Status = UfsFlashUpdateBlock ((UINT32) Address, Buf, BlockSize, Update);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "UfsFlashUpdate failed (%r) at 0x%x\n", Status, Address));
      break;
    }

    Address += BlockSize;
    Buf += BlockSize;
  }

  if (Progress != NULL) {
    Progress (EndPercentage);
  }

  return Status;
}

/**
  Get BIOS region base and size on UFS flash.

  @param[out] BiosRegionOffset   The address of BIOS region in flash.
  @param[out] BiosRegionSize     The size of BIOS region in bytes.

  @retval EFI_SUCCESS            The operation returns successfully.
  @retval EFI_INVALID_PARAMETER  The input parameter is not valid.

**/
EFI_STATUS
EFIAPI
GetUfsBiosRegion (
  OUT UINT32 *BiosRegionOffset,
  OUT UINT32 *BiosRegionSize
  )
{
  VOID                *GuidHobPtr;
  CSE_LAYOUT_POINTERS *CseLayoutPointers;

  GuidHobPtr = GetFirstGuidHob (&gIfwiCseLayoutPointersHobGuid);
  if (GuidHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "IfwiCseLayoutPointerHob Error: IFWI CSE Layout Pointer HOB does not exist!\n"));
    return EFI_INVALID_PARAMETER;
  }
  CseLayoutPointers = (CSE_LAYOUT_POINTERS *) GET_GUID_HOB_DATA (GuidHobPtr);
  *BiosRegionOffset = CseLayoutPointers->Lbp4Offset;
  *BiosRegionSize   = CseLayoutPointers->Lbp4Size;

  return EFI_SUCCESS;
}

/**
  Update BPDT signature with given value.

  @param[in] BpdtNum                     BPDT table number (0 or 1).
  @param[in] BpdtSignature               Value to be updated.
                                          Green       0x000055AA    //Normal Boot
                                          Yellow      0x00AA55AA    //Recovery Boot
                                          Red         0xFFFFFFFF    //any other value, ie !(GREEN || YELLOW)

  @retval EFI_SUCCESS                    The BPDT signature is updated successfully.
  @retval Others                         The update operation fails.

**/
EFI_STATUS
EFIAPI
UpdateBpdtSignature (
  IN UINT8  BpdtNum,
  IN UINT32 BpdtSignature
  )
{

  EFI_STATUS              Status;
  EFI_PHYSICAL_ADDRESS    BpdtTableAddress;
  UINT8                   *BpdtBuffer;
  BPDT_HEADER             *Bpdt4;

  DEBUG ((DEBUG_INFO, "UpdateBpdtSignature\n"));

  // Allocate buffer to read IBB FVs.
  BpdtBuffer = AllocateZeroPool (BPDT_TABLE_SIZE);
  if (BpdtBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "UpdateBpdtSignature: Failed to allocate buffer for BPDT table.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  BpdtTableAddress = BpdtNum * BPDT_TABLE_SIZE;

  // Read BPDT table to buffer.
  Status = UfsFlashUpdate (
             UfsFlashRegionBios,
             (UINT32) BpdtTableAddress,
             (UINT8 *) BpdtBuffer,
             BPDT_TABLE_SIZE,
             FALSE,
             NULL,
             0,
             0
             );

  Bpdt4 = (BPDT_HEADER *) BpdtBuffer;
  if (Bpdt4 == NULL) {
    return EFI_NOT_FOUND;
  }


  // Update with BPDT signature.
  DEBUG ((DEBUG_INFO, "Current BPDT4 signature = 0x%08X\n", Bpdt4->Signature));
  Bpdt4->Signature = BpdtSignature;
  DEBUG ((DEBUG_INFO, "New BPDT4 signature = 0x%08X\n", Bpdt4->Signature));

  // Write back BPDT to Flash.
  Status = UfsFlashUpdate (
             UfsFlashRegionBios,
             (UINT32) BpdtTableAddress,
             (UINT8 *) BpdtBuffer,
             BPDT_TABLE_SIZE,
             TRUE,
             NULL,
             0,
             0
             );
  FreePool (BpdtBuffer);

  return Status;
}

/**
  Reads BIOS image from flash and copies to an input Buffer.

  @param[in] Buffer                      Pointer to the buffer to which image is copied.

  @retval EFI_SUCCESS                    Successfully copied image to buffer.
  @retval EFI_INVALID_PARAMETER          The input buffer is invalid.
  @retval Others                         Failed to get BIOS region.

**/
EFI_STATUS
EFIAPI
GetUfsBiosImageFromFlash (
  IN UINT8           *Buffer
  )
{
  EFI_PHYSICAL_ADDRESS      StartAddress;
  UINT32                    BiosRegionSize;
  EFI_STATUS                Status;

  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  StartAddress = 0x0;
  BiosRegionSize = FixedPcdGet32 (PcdBiosSize) + (2 * BPDT_TABLE_SIZE);

  // Read the BIOS region from Flash.
  Status = UfsFlashUpdate (
             UfsFlashRegionBios,
             (UINT32) StartAddress,
             (UINT8 *) Buffer,
             BiosRegionSize,
             FALSE,
             NULL,
             0,
             0
             );

  return Status;
}

/**
  Return UFS TopSwap region size from PCD
**/
UINT32
GetUfsTopSwapBlockSize (
  VOID
  )
{
  return FixedPcdGet32 (PcdUfsTopSwapSize);
}

/**
  Update TopSwap region with the current IBB block on flash.

  @param[in] Progress                    A function used report the progress of the
                                         firmware update.  This is an optional parameter
                                         that may be NULL.
  @param[in] StartPercentage             The start completion percentage value that may
                                         be used to report progress during the flash
                                         write operation.
  @param[in] EndPercentage               The end completion percentage value that may
                                         be used to report progress during the flash
                                         write operation.

  @retval EFI_SUCCESS                    The flash region is updated successfully.
  @retval Others                         The update operation fails.

**/
EFI_STATUS
EFIAPI
UpdateUfsTopSwapArea (
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                 Status;
  UINT32                     BiosRegionSize;
  UINT32                     TopSwapLength;
  EFI_PHYSICAL_ADDRESS       FlashAddress;
  EFI_PHYSICAL_ADDRESS       IbbStartAddress;
  UINT8                      *IbbBuffer;

  // Allocate buffer to read IBB FVs.
  IbbBuffer = AllocateZeroPool (GetUfsTopSwapBlockSize ());
  if (IbbBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "UpdateUfsTopSwapArea: Failed to allocate buffer for IBB.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  BiosRegionSize = FixedPcdGet32 (PcdBiosSize) + (2 * BPDT_TABLE_SIZE);
  TopSwapLength = GetUfsTopSwapBlockSize ();
  FlashAddress = BiosRegionSize - (2 * TopSwapLength);
  IbbStartAddress = BiosRegionSize - TopSwapLength;

  // Read IBB FVs to buffer from Flash.
  DEBUG ((DEBUG_INFO, "UpdateBiosFirmware: Read IBB region - 0x%x - 0x%x\n", (UINTN)IbbStartAddress, TopSwapLength));
  Status = UfsFlashUpdate (
             UfsFlashRegionBios,
             (UINT32) IbbStartAddress,
             (UINT8 *) IbbBuffer,
             (UINT32) TopSwapLength,
             FALSE,
             Progress,
             StartPercentage,
             (StartPercentage + EndPercentage ) / 2
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to get IBB FVs from flash\n"));
    FreePool (IbbBuffer);
    return Status;
  }

  // Update IBB FVs to TopSwap area.
  DEBUG ((DEBUG_INFO, "UpdateBiosFirmware: Update UFS TopSwap Area - 0x%x - 0x%x\n", (UINTN)FlashAddress, TopSwapLength));
  Status = UfsFlashUpdate (
             UfsFlashRegionBios,
             (UINT32) FlashAddress,
             (UINT8 *) IbbBuffer,
             (UINT32) TopSwapLength,
             TRUE,
             Progress,
             (StartPercentage + EndPercentage ) / 2,
             EndPercentage
             );

  FreePool (IbbBuffer);

  return Status;
}

/**
  Perform EC firmware update.

  @param[in] Offset                  Offset relative to EC region to be programmed.
  @param[in] EcBinPtr                Pointer to EC FW binary.
  @param[in] EcBinSize               Size of EC FW binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                EC FW is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateEcFirmware (
  IN UINT32                                         Offset,
  IN UINT8                                          *EcBinPtr,
  IN UINTN                                          EcBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  DEBUG ((DEBUG_INFO, "UpdateEcFirmware: Direct SPI.\n"));

  return SpiFlashUpdate (
           FlashRegionEC,
           Offset,
           EcBinPtr,
           (UINT32) EcBinSize,
           Progress,
           StartPercentage,
           EndPercentage
           );

}

/**
  Display the ME update progress.

  @param BytesSent               Bytes already sent to ME
  @param BytestobeSent           Bytes to be sent to ME

**/
VOID DisplaySendMeFwStatus (
  UINT32                                BytesSent,
  UINT32                                BytestobeSent
  )
{
  UINTN  Percentage;

  Percentage = (BytesSent * (mMeSendProgressEndPercentage - mMeSendProgressStartPercentage)) / BytestobeSent;

  if (mMeDisplayProgress != NULL) {
    mMeDisplayProgress (Percentage);
  } else {
    Print(L"Sending the update image to FW for verification:  [ %d%% ]\r", Percentage);
  }
}

/**
  Update ME Firmware by HECI interface.
  Use the ME FW Update API (FWUpdateLib.lib) provided by ME team to perform the update.

  @param[in] ImageBuffer             Pointer to ME FWU FwImage.
  @param[in] ImageLength             Size of FwImage.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                ME FW is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateMeByHeci (
  IN UINT8                                          *ImageBuffer,
  IN UINTN                                          ImageLength,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                           Status;
  UINT32                               FwUpdateApiStatus;
  UINT16                               EnabledState;
  BOOLEAN                              InProgress;
  UINT32                               CurrentPercent;
  UINT32                               FwUpdateStatus;
  UINT32                               NeededResetType;
  UINT32                               UpdateTimer;
  UINT32                               PreviousPercent;

  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: ME Image Length %d(%xh)\n", ImageLength, ImageLength));

  EnabledState    = 0;
  InProgress      = FALSE;
  CurrentPercent  = 0;
  FwUpdateStatus  = 0;
  NeededResetType = 0;
  UpdateTimer     = 0;
  PreviousPercent = 0;

  //
  // Check FWU enabled state
  //
  FwUpdateApiStatus = FwuEnabledState (&EnabledState);
  if (FwUpdateApiStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "UpdateMeByHeci: FwuEnabledState failed: %r.\n", FwUpdateApiStatus));
    return EFI_DEVICE_ERROR;
  }

  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: FwuEnabledState is 0x%x.\n", EnabledState));

  switch (EnabledState) {
    case FW_UPDATE_DISABLED:
      DEBUG ((DEBUG_ERROR, "UpdateMeByHeci: FWUpdate is disabled.\n"));
      return EFI_DEVICE_ERROR;

    case FW_UPDATE_ENABLED:
      break;

    default:
      break;
  }

  if (Progress != NULL) {
    mMeDisplayProgress = Progress;
    mMeSendProgressStartPercentage = StartPercentage;
    //
    // Assign 1/5 of progress bar to SendProgress
    //
    mMeSendProgressEndPercentage = StartPercentage + ((EndPercentage - StartPercentage) / 5);
  }

  //
  // Starting FWU full update. Send image to FW Update Client
  //
  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: Executing Full FW Update.\n"));
  FwUpdateApiStatus = FwuFullUpdateFromBuffer (ImageBuffer, (UINT32) ImageLength, NULL, &DisplaySendMeFwStatus);
  if (FwUpdateApiStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "UpdateMeByHeci: FwuFullUpdateFromBuffer failed: %r.\n", FwUpdateApiStatus));
    return EFI_DEVICE_ERROR;
  }

  //
  // Image was sent to FW Update client
  // Poll the FW Update progress until finished
  //
  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: Waiting for FW Update progress to be finished.\n"));
  do {
    FwUpdateApiStatus = FwuCheckUpdateProgress (
                          &InProgress,
                          &CurrentPercent,
                          &FwUpdateStatus,
                          &NeededResetType
                          );
    if (FwUpdateApiStatus != EFI_SUCCESS) {
      DEBUG ((DEBUG_ERROR, "UpdateMeByHeci: FwuCheckUpdateProgress failed: %r.\n", FwUpdateApiStatus));
      break;
    }

    if (!InProgress) {
      DEBUG ((DEBUG_INFO, "UpdateMeByHeci: FWU Update finished successfully: %r.\n", FwUpdateApiStatus));
      if (Progress != NULL) {
        Progress (EndPercentage);
      } else {
        Print (L"Update in progress:  [ COMPLETE ]\n");
      }
      break;
    }

    // Update is in progress
    DEBUG ((DEBUG_INFO, "UpdateMeByHeci: Current percent: %d\n", CurrentPercent));
    gBS->Stall (250000); // wait 250 milliseconds before polling again

    // If 30 seconds passed
    if (UpdateTimer >= 30000) {
      // If percent didn't change in 30 seconds
      if (CurrentPercent == PreviousPercent) {
        DEBUG ((DEBUG_ERROR, "UpdateMeByHeci: FwuCheckUpdateProgress timeout.\n"));
        Status = EFI_TIMEOUT;
        break;
      }
      // Percent changed
      PreviousPercent = CurrentPercent;
      UpdateTimer = 0;
    } else {
      // Increase timer
      UpdateTimer += 250;
    }

    if (Progress != NULL) {
      Progress (mMeSendProgressEndPercentage + (CurrentPercent * (EndPercentage - mMeSendProgressEndPercentage)) / 100);
    } else {
      Print (L"Update in progress:  [ %d%% ]\r", CurrentPercent);
    }
  } while (TRUE);


  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: FwUpdateApiStatus: 0x%x (%d).\n", FwUpdateApiStatus, FwUpdateApiStatus));
  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: FwUpdateStatus   : 0x%x (%d).\n", FwUpdateStatus, FwUpdateStatus));
  DEBUG ((DEBUG_INFO, "UpdateMeByHeci: NeededResetType  : 0x%x.\n", NeededResetType));
  if ((FwUpdateApiStatus != EFI_SUCCESS) || (FwUpdateStatus != EFI_SUCCESS)) {
    Status = EFI_DEVICE_ERROR;
  } else {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  Perform ME firmware update.

  @param[in] MeBinPtr                Pointer to ME FW binary.
  @param[in] MeBinSize               Size of ME FW binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                ME FW is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateMeFirmware (
  IN UINT8                                          *MeBinPtr,
  IN UINTN                                          MeBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS                      Status;

  DEBUG ((DEBUG_INFO, "UpdateMeFirmware: MeBinSize = %x\n", MeBinSize));

  DEBUG ((DEBUG_INFO, "UpdateMeFirmware: Update ME firmware with HECI interface\n"));
  //
  // Use the HECI method to perform Me update.
  //
  Status = UpdateMeByHeci (
             MeBinPtr,
             MeBinSize,
             Progress,
             StartPercentage,
             EndPercentage
             );

  return Status;
}

/**
  Perform ISH PDT configuration update

  @param[in] PdtBinPtr               Pointer to PDT binary.
  @param[in] PdtBinSize              Size of PDT binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                PDT is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateIshPdt (
  IN UINT8                                          *PdtBinPtr,
  IN UINTN                                          PdtBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS              Status;
  UINT8                   *PaddedPayload;
  UINTN                   PaddedPayloadSize;
  UINT32                  FwUpdateApiStatus;

  DEBUG ((DEBUG_INFO, "UpdateIshPdt: PdtBinSize = 0x%x\n", PdtBinSize));
  ASSERT (PdtBinSize <= SIZE_4KB);

  PaddedPayload = NULL;

  //
  // Payload size must be word aligned and padded with zero byte if size is not even.
  //
  PaddedPayloadSize = ALIGN_VALUE (PdtBinSize, 2);
  DEBUG ((DEBUG_INFO, "UpdateIshPdt: Padded PdtBinSize = 0x%x\n", PaddedPayloadSize));

  PaddedPayload = AllocateZeroPool (PaddedPayloadSize);
  if (PaddedPayload == NULL) {
    DEBUG ((DEBUG_ERROR, "UpdateIshPdt: Ran out of memory resource.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (PaddedPayload, PdtBinPtr, PdtBinSize);

  if (Progress != NULL) {
    Progress (StartPercentage);
  }

  FwUpdateApiStatus = FwuSetIshConfig (PaddedPayload, (UINT32) PaddedPayloadSize);
  DEBUG ((DEBUG_INFO, "UpdateIshPdt FwuStatus = 0x%x\n", FwUpdateApiStatus));

  if (FwUpdateApiStatus != EFI_SUCCESS) {
    Status = EFI_DEVICE_ERROR;
  } else {
    Status = EFI_SUCCESS;
  }

  if (Progress != NULL) {
    Progress (EndPercentage);
  }

  FreePool (PaddedPayload);

  return Status;
}

/**
  Perform BIOS region update.

  This function is intended to support both non-BiosGuard and BiosGuard cases.
  When BiosGuard is supported and enabled on the platform, BiosGuardUpdate argument
  is supposed to be TRUE and BgupImage is the Bios Guard Update Package along with
  input BIOS data buffer.
  Considering BIOS region might be updated by stage, the input argument FlashAddress
  indicates the relative or absolute BIOS region address (depends on FlashAddressType)
  to be flashed.

  @param[in] FlashAddress      The offset relative to BIOS region to be accessed.
  @param[in] Buffer            The pointer to the data buffer.
  @param[in] Length            The length of data buffer in bytes.
  @param[in] BiosGuardUpdate   Indicates if this update should be performed by
                               BiosGuard service or not.
  @param[in] BgupImage         If BiosGuardUpdate is TRUE, the pointer to the
                               BGUP image corresponding to Buffer used in
                               BiosGuard Update.
  @param[in] BgupImageSize     The length of BgupImage in bytes.
  @param[in] Progress          A function used report the progress of the
                               firmware update.  This is an optional parameter
                               that may be NULL.
  @param[in] StartPercentage   The start completion percentage value that may
                               be used to report progress during the flash
                               write operation.
  @param[in] EndPercentage     The end completion percentage value that may
                               be used to report progress during the flash
                               write operation.

  @retval EFI_SUCCESS           The operation returns successfully.
  @retval EFI_WRITE_PROTECTED   The flash device is read only.
  @retval EFI_DEVICE_ERROR      The flash update fails.
  @retval EFI_UNSUPPORTED       The flash device access is unsupported.
  @retval EFI_INVALID_PARAMETER The input parameter is not valid.
  @retval Others                Flash update failure

**/
EFI_STATUS
EFIAPI
UpdateBiosFirmware (
  IN EFI_PHYSICAL_ADDRESS                           FlashAddress,
  IN VOID                                           *Buffer,
  IN UINTN                                          Length,
  IN BOOLEAN                                        BiosGuardUpdate,
  IN VOID                                           *BgupImage,
  IN UINTN                                          BgupImageSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  )
{
  EFI_STATUS          Status;

  DEBUG ((DEBUG_INFO, "UpdateBiosFirmware - 0x%x - 0x%x\n", (UINTN)FlashAddress, Length));

  if (BiosGuardUpdate) {
    DEBUG ((DEBUG_INFO, "Update via BiosGuard is not supported on this platform\n"));
    return EFI_UNSUPPORTED;
  }

  if (BootMediaIsSpi ()) {
    DEBUG ((DEBUG_INFO, "Update via PCH SPI protocol\n"));
    Status = SpiFlashUpdate (
               FlashRegionBios,
               (UINT32) FlashAddress,
               (UINT8 *) Buffer,
               (UINT32) Length,
               Progress,
               StartPercentage,
               EndPercentage
               );
  } else if (BootMediaIsUfs ()) {
    DEBUG ((DEBUG_INFO, "Update via UFS Block IO protocol\n"));
    Status = UfsFlashUpdate (
               UfsFlashRegionBios,
               (UINT32) FlashAddress,
               (UINT8 *) Buffer,
               (UINT32) Length,
               TRUE,
               Progress,
               StartPercentage,
               EndPercentage
               );
  } else {
    DEBUG ((DEBUG_INFO, "Unsupported boot media\n"));
    return EFI_UNSUPPORTED;
  }

  return Status;
}
