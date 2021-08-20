/** @file
PEIM to produce gEfiPeiVirtualBlockIoPpiGuid & gEfiPeiVirtualBlockIo2PpiGuid PPI for
ATA controllers in the platform.

This PPI can be consumed by PEIM which produce gEfiPeiDeviceRecoveryModulePpiGuid

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

@par Specification
**/

#include "AtaBlockIoPei.h"

//
// ATA_DEVICE template
//
ATA_DEVICE gAtaDeviceTemplate = {
  ATA_DEVICE_SIGNATURE,        // Signature
  {                            // BlockMedia
    IdeCDROM,                  // DeviceType
    TRUE,                      // MediaPresent
    0,                         // LastBlock
    0x200                      // BlockSize
  },
  0,                           // Port
  0,                           // PortMultiplierPort
  { 0, },                      // Packet
  {{ 0}, },                    // Acb
  NULL,                        // Asb
  FALSE,                       // UdmaValid
  FALSE,                       // Lba48Bit
  NULL,                        // IdentifyData
  {NULL, NULL},                // AtaTaskList
  {NULL, NULL},                // AtaSubTaskList
  FALSE                        // Abort
};

//
// Template for PEI ATA Private Data.
//
PEI_ATA_BLK_IO_INSTANCE gPeiBlockIoTemplate = {
  PEI_ATA_BLK_IO_SIGNATURE,    // Signature
  {                            // AtaBlkIoPpi
    BotGetNumberOfBlockDevices,
    BotGetMediaInfo,
    AtaReadBlocks
  },
  {                            // AtaBlkIoPpiList
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiVirtualBlockIoPpiGuid,
    NULL
  },
  NULL,                        // AtaPassThruPpi
  0,                           // DeviceCount
  {                            // DeviceInfo
    {
      0,
    },
  }
};

PEI_ATA_BLK_IO_INSTANCE           *mBlockIoInstance = NULL;

/**
  Allocates an aligned buffer for ATA device.

  This function allocates an aligned buffer for the ATA device to perform
  ATA pass through operations. The alignment requirement is from ATA pass
  through interface.

  @param  AtaDevice         The ATA child device involved for the operation.
  @param  BufferSize        The request buffer size.

  @return A pointer to the aligned buffer or NULL if the allocation fails.

**/
VOID *
AllocateAlignedBuffer (
  IN UINTN                    BufferSize
  )
{
  return AllocateAlignedPages (EFI_SIZE_TO_PAGES (BufferSize), mBlockIoInstance->AtaPassThruPpi->Mode->IoAlign);
}

/**
  Dump info of ATA device.

  This function frees an aligned buffer for the ATA device to perform
  ATA pass through operations.

  @param  Buffer            The aligned buffer to be freed.
  @param  BufferSize        The request buffer size.

**/
VOID
DumpAtaDeviceInfo (
  IN ATA_DEVICE                 *AtaDevice
  )
{
  if (AtaDevice == NULL) {
    return;
  }
  DEBUG ((DEBUG_INFO, "AtaDeviceInfo: Port = %x, PortMultiplierPort = %x\n", AtaDevice->Port, AtaDevice->PortMultiplierPort));
  DEBUG ((DEBUG_INFO, "AtaDeviceInfo: UdmaValid = %x, Lba48Bit = %x\n", AtaDevice->UdmaValid, AtaDevice->Lba48Bit));
  DEBUG ((DEBUG_INFO, "AtaDeviceInfo: LastBlock = %x, BlockSize = %x\n", AtaDevice->BlockMedia.LastBlock, AtaDevice->BlockMedia.BlockSize));
}


/**
  Gets the count of block I/O devices that one specific block driver detects.

  This function is used for getting the count of block I/O devices that one
  specific block driver detects.  To the PEI ATAPI driver, it returns the number
  of all the detected ATAPI devices it detects during the enumeration process.
  To the PEI legacy floppy driver, it returns the number of all the legacy
  devices it finds during its enumeration process. If no device is detected,
  then the function will return zero.

  @param[in]  PeiServices          - General-purpose services that are available
                                     to every PEIM.
  @param[in]  This                 - Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI
                                     instance.
  @param[out] NumberBlockDevices   - The number of block I/O devices discovered.

  @retval     EFI_SUCCESS          - Operation performed successfully.

**/
EFI_STATUS
EFIAPI
BotGetNumberOfBlockDevices (
  IN  EFI_PEI_SERVICES                         **PeiServices,
  IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI            *This,
  OUT UINTN                                    *NumberBlockDevices
  )
{
  PEI_ATA_BLK_IO_INSTANCE           *AtaBlockIo;

  AtaBlockIo = PEI_RECOVERY_PPI_FROM_BLKIO_THIS (This);
  *NumberBlockDevices = AtaBlockIo->DeviceCount;
  return EFI_SUCCESS;
}

/**
  Gets a block device's media information.

  This function will provide the caller with the specified block device's media
  information. If the media changes, calling this function will update the media
  information accordingly.

  @param[in]  PeiServices   - General-purpose services that are available to every
                              PEIM
  @param[in]  This          - Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  DeviceIndex   - Specifies the block device to which the function wants
                              to talk. Because the driver that implements Block I/O
                              PPIs will manage multiple block devices, the PPIs that
                              want to talk to a single device must specify the
                              device index that was assigned during the enumeration
                              process. This index is a number from one to
                              NumberBlockDevices.
  @param[out] MediaInfo     - The media information of the specified block media.
                              The caller is responsible for the ownership of this
                              data structure.

  @retval EFI_SUCCESS       - Media information about the specified block device
                              was obtained successfully.
  @retval EFI_DEVICE_ERROR  - Cannot get the media information due to a hardware
                              error.

**/
EFI_STATUS
EFIAPI
BotGetMediaInfo (
  IN  EFI_PEI_SERVICES                          **PeiServices,
  IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI             *This,
  IN  UINTN                                     DeviceIndex,
  OUT EFI_PEI_BLOCK_IO_MEDIA                    *MediaInfo
  )
{
  PEI_ATA_BLK_IO_INSTANCE           *AtaBlockIo;
  ATA_DEVICE                        *AtaDevice;

  AtaBlockIo = PEI_RECOVERY_PPI_FROM_BLKIO_THIS (This);

  if(DeviceIndex <= 0 || DeviceIndex > AtaBlockIo->DeviceCount) {
    return EFI_INVALID_PARAMETER;
  }

  AtaDevice = &(AtaBlockIo->DeviceInfo[DeviceIndex - 1]);

  MediaInfo->DeviceType = AtaDevice->BlockMedia.DeviceType;
  MediaInfo->MediaPresent = AtaDevice->BlockMedia.MediaPresent;
  MediaInfo->BlockSize = AtaDevice->BlockMedia.BlockSize;
  MediaInfo->LastBlock = AtaDevice->BlockMedia.LastBlock;
  DEBUG ((DEBUG_INFO, " MediaPresent--> 0x%x\n", MediaInfo->MediaPresent));
  DEBUG ((DEBUG_INFO, " BlockSize--> 0x%x\n", MediaInfo->BlockSize));
  DEBUG ((DEBUG_INFO, " LastBlock--> 0x%x\n", MediaInfo->LastBlock));
  return EFI_SUCCESS;
}


/**
  Implements EFI_PEI_RECOVERY_BLOCK_IO_PPI.ReadBlocks() function.

  @param[in]  PeiServices -General-purpose services that are available to every
                           PEIM.
  @param[in]  This        - The EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  MediaId     - The media id that the read request is for.
  @param[in]  LBA         - The starting logical block address to read from on the device.
  @param[in]  BufferSize  - The size of the Buffer in bytes. This must be a multiple of
                            the intrinsic block size of the device.
  @param[out]  Buffer     - A pointer to the destination buffer for the data. The caller
                           is responsible for either having implicit or explicit ownership
                           of the buffer.


  @retval   EFI_INVALID_PARAMETER - Parameter is error
  @retval   EFI_SUCCESS           - Success
  @retval   EFI_DEVICE_ERROR      - Hardware Error
  @retval   EFI_NO_MEDIA          - No media
  @retval   EFI_MEDIA_CHANGED     - Media Change
  @retval   EFI_BAD_BUFFER_SIZE   - Buffer size is bad
 **/
EFI_STATUS
EFIAPI
AtaReadBlocks (
  IN   EFI_PEI_SERVICES                               **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI                  *This,
  IN   UINTN                                          MediaId,
  IN   EFI_PEI_LBA                                    LBA,
  IN   UINTN                                          BufferSize,
  OUT  VOID                                           *Buffer
  )
{
  PEI_ATA_BLK_IO_INSTANCE           *AtaBlockIo;

  AtaBlockIo = PEI_RECOVERY_PPI_FROM_BLKIO_THIS (This);

  if(MediaId <= 0 || MediaId > AtaBlockIo->DeviceCount) { // should start from 1
    return EFI_INVALID_PARAMETER;
  }

  return BlockIoReadWrite ((VOID *) This, MediaId, LBA, NULL, BufferSize, Buffer, FALSE, FALSE);
}

/**
  Read/Write BufferSize bytes from Lba from/into Buffer.

  @param[in]       This       Indicates a pointer to the calling context. Either be
                              block I/O or block I/O2.
  @param[in]       MediaId    The media ID that the read/write request is for.
  @param[in]       Lba        The starting logical block address to be read/written.
                              The caller is responsible for reading/writing to only
                              legitimate locations.
  @param[in, out]  Token      A pointer to the token associated with the transaction.
  @param[in]       BufferSize Size of Buffer, must be a multiple of device block size.
  @param[out]      Buffer     A pointer to the destination/source buffer for the data.
  @param[in]       IsBlockIo2 Indicate the calling is from BlockIO or BlockIO2. TRUE is
                              from BlockIO2, FALSE is for BlockIO.
  @param[in]       IsWrite    Indicates whether it is a write operation.

  @retval EFI_SUCCESS           The data was read/written correctly to the device.
  @retval EFI_WRITE_PROTECTED   The device can not be read/written to.
  @retval EFI_DEVICE_ERROR      The device reported an error while performing the read/write.
  @retval EFI_NO_MEDIA          There is no media in the device.
  @retval EFI_MEDIA_CHNAGED     The MediaId does not matched the current device.
  @retval EFI_BAD_BUFFER_SIZE   The Buffer was not a multiple of the block size of the device.
  @retval EFI_INVALID_PARAMETER The read/write request contains LBAs that are not valid,
                                or the buffer is not on proper alignment.

**/
EFI_STATUS
BlockIoReadWrite (
  IN     VOID                    *This,
  IN     UINT32                  MediaId,
  IN     EFI_LBA                 Lba,
  IN OUT EFI_BLOCK_IO2_TOKEN     *Token,
  IN     UINTN                   BufferSize,
  OUT    VOID                    *Buffer,
  IN     BOOLEAN                 IsBlockIo2,
  IN     BOOLEAN                 IsWrite
  )
{
  PEI_ATA_BLK_IO_INSTANCE           *AtaBlockIoInstance;
  ATA_DEVICE                        *AtaDevice;
  EFI_STATUS                        Status;
  EFI_PEI_BLOCK_IO_MEDIA            *Media;
  UINTN                             BlockSize;
  UINTN                             NumberOfBlocks;

  DEBUG ((DEBUG_BLKIO, "BlockIoReadWrite begin\n"));

  AtaBlockIoInstance = PEI_RECOVERY_PPI_FROM_BLKIO_THIS (This);
  AtaDevice = &(AtaBlockIoInstance->DeviceInfo[MediaId - 1]);   // only check first one.
  Media = &(AtaDevice->BlockMedia);

  //
  // Check parameters.
  //
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  BlockSize = Media->BlockSize;
  if ((BufferSize % BlockSize) != 0) {
    return EFI_BAD_BUFFER_SIZE;
  }

  NumberOfBlocks  = BufferSize / BlockSize;
  if ((Lba + NumberOfBlocks - 1) > Media->LastBlock) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Invoke low level AtaDevice Access Routine.
  //
  Status = AccessAtaDevice (AtaDevice, Buffer, Lba, NumberOfBlocks, IsWrite, Token);

  return Status;
}

/**
  Registers an ATA device.

  This function allocates an ATA device structure for the ATA device specified by
  Port and PortMultiplierPort if the ATA device is identified as a valid one.

  @param  Port                  The port number of the ATA device.
  @param  PortMultiplierPort    The port multiplier port number of the ATA device.

  @retval EFI_SUCCESS           The ATA device is successfully registered.
  @retval EFI_OUT_OF_RESOURCES  There is not enough memory to allocate the ATA device
                                and related data structures.
  @return Others                Some error occurs when registering the ATA device.

**/
EFI_STATUS
RegisterAtaDevice (
  IN     UINT16                     Port,
  IN     UINT16                     PortMultiplierPort
  )
{
  EFI_STATUS                        Status;
  ATA_DEVICE                        *AtaDevice;

  DEBUG ((DEBUG_INFO, "RegisterAtaDevice: Port = %x, PortMultiplierPort = %x\n", Port, PortMultiplierPort));
  AtaDevice = &(mBlockIoInstance->DeviceInfo[mBlockIoInstance->DeviceCount]);

  //
  // Initializes ATA device structures and allocates the required buffer.
  //
  CopyMem (AtaDevice, &gAtaDeviceTemplate, sizeof (ATA_DEVICE));
  AtaDevice->Port               = Port;
  AtaDevice->PortMultiplierPort = PortMultiplierPort;
  AtaDevice->Asb = AllocateAlignedBuffer (sizeof (EFI_ATA_STATUS_BLOCK));
  if (AtaDevice->Asb == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }
  AtaDevice->IdentifyData = AllocateAlignedBuffer (sizeof (ATA_IDENTIFY_DATA));
  if (AtaDevice->IdentifyData == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  //
  // Initial Ata Task List
  //
  InitializeListHead (&AtaDevice->AtaTaskList);
  InitializeListHead (&AtaDevice->AtaSubTaskList);

  DEBUG ((DEBUG_INFO, "AtaDevice: Port = %x, PortMultiplierPort = %x\n", AtaDevice->Port, AtaDevice->PortMultiplierPort));
  DEBUG ((DEBUG_INFO, "AtaDevice: UdmaValid = %x, Lba48Bit = %x\n", AtaDevice->UdmaValid, AtaDevice->Lba48Bit));
  DEBUG ((DEBUG_INFO, "AtaDevice: LastBlock = %x, BlockSize = %x\n", AtaDevice->BlockMedia.LastBlock, AtaDevice->BlockMedia.BlockSize));
  DEBUG ((DEBUG_INFO, "AtaDevice: signature = %x, \n", AtaDevice->Signature));

  //
  // Try to identify the ATA device via the ATA pass through command.
  //
  Status = DiscoverAtaDevice (AtaDevice);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  DumpAtaDeviceInfo(AtaDevice);
  mBlockIoInstance->DeviceCount ++;
Done:

  if (EFI_ERROR (Status) && (AtaDevice != NULL)) {
    //ReleaseAtaResources (AtaDevice);
    DEBUG ((DEBUG_ERROR, "RegisterAtaDevice: Failed to initialize Port %x PortMultiplierPort %x, status = %r\n", Port, PortMultiplierPort, Status));
  }
  return Status;
}

/**
  Initializes the Ata Block Io PPI.

  @param[in]  FileHandle           Handle of the file being invoked.
  @param[in]  PeiServices          Describes the list of possible PEI Services.

  @retval     EFI_SUCCESS          Operation performed successfully.
  @retval     EFI_OUT_OF_RESOURCES Not enough memory to allocate.

**/
EFI_STATUS
EFIAPI
InitializeAtaBlockIo (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{

  PEI_ATA_PASS_THRU_PPI             *AtaPassThruPpi;
  EFI_STATUS                        Status;
  UINT16                            Port;
  UINT16                            PortMultiplierPort;

  //Status = PeiServicesRegisterForShadow (FileHandle);
  //if (!EFI_ERROR (Status)) {
  //  return Status;
  //}

  Status = PeiServicesLocatePpi (
              &gPeiAtaPassThruPpiGuid,
              0,
              NULL,
              (VOID **) &AtaPassThruPpi
              );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "InitializeAtaBlockIo: failed to locate AtaPassThruPeiPpi.\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Prepare private data
  //
  mBlockIoInstance = AllocateCopyPool (sizeof (PEI_ATA_BLK_IO_INSTANCE), &gPeiBlockIoTemplate);
  if (mBlockIoInstance == NULL) {
    DEBUG ((DEBUG_ERROR, "InitializeAtaBlockIo: failed to allocate private instance.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  mBlockIoInstance->AtaPassThruPpi = AtaPassThruPpi;
  mBlockIoInstance->AtaBlkIoPpiList.Ppi  = (VOID*)&mBlockIoInstance->AtaBlkIoPpi;

  //
  // Enumerate ATA device
  //
  Port = 0xFFFF;
  while (TRUE) {
    Status = AtaPassThruPpi->GetNextPort (AtaPassThruPpi, &Port);
    if (EFI_ERROR (Status)) {
      //
      // We cannot find more legal port then we are done.
      //
      break;
    }

    PortMultiplierPort = 0xFFFF;
    while (TRUE) {
      Status = AtaPassThruPpi->GetNextDevice (AtaPassThruPpi, Port, &PortMultiplierPort);
      if (EFI_ERROR (Status)) {
        //
        // We cannot find more legal port multiplier port number for ATA device
        // on the port, then we are done.
        //
        break;
      }
      RegisterAtaDevice (Port, PortMultiplierPort);
    }
  }
  Status = EFI_SUCCESS;

  if (mBlockIoInstance->DeviceCount != 0) {
    PeiServicesInstallPpi (&mBlockIoInstance->AtaBlkIoPpiList);
  }

  return Status;
}
