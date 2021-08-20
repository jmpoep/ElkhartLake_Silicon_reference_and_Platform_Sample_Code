/** @file
  ATA passthru PPI execution function.

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

#define ATA_CMD_TRUST_NON_DATA    0x5B
#define ATA_CMD_TRUST_RECEIVE     0x5C
#define ATA_CMD_TRUST_RECEIVE_DMA 0x5D
#define ATA_CMD_TRUST_SEND        0x5E
#define ATA_CMD_TRUST_SEND_DMA    0x5F

//
// Look up table (UdmaValid, IsWrite) for EFI_ATA_PASS_THRU_CMD_PROTOCOL
//
EFI_ATA_PASS_THRU_CMD_PROTOCOL mAtaPassThruCmdProtocols[][2] = {
  {
    EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN,
    EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT
  },
  {
    EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN,
    EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT,
  }
};

//
// Look up table (UdmaValid, Lba48Bit, IsIsWrite) for ATA_CMD
//
UINT8 mAtaCommands[][2][2] = {
  {
    {
      ATA_CMD_READ_SECTORS,            // 28-bit LBA; PIO read
      ATA_CMD_WRITE_SECTORS            // 28-bit LBA; PIO write
    },
    {
      ATA_CMD_READ_SECTORS_EXT,        // 48-bit LBA; PIO read
      ATA_CMD_WRITE_SECTORS_EXT        // 48-bit LBA; PIO write
    }
  },
  {
    {
      ATA_CMD_READ_DMA,                // 28-bit LBA; DMA read
      ATA_CMD_WRITE_DMA                // 28-bit LBA; DMA write
    },
    {
      ATA_CMD_READ_DMA_EXT,            // 48-bit LBA; DMA read
      ATA_CMD_WRITE_DMA_EXT            // 48-bit LBA; DMA write
    }
  }
};

//
// Look up table (UdmaValid, IsTrustSend) for ATA_CMD
//
UINT8 mAtaTrustCommands[2][2] = {
  {
    ATA_CMD_TRUST_RECEIVE,            // PIO read
    ATA_CMD_TRUST_SEND                // PIO write
  },
  {
    ATA_CMD_TRUST_RECEIVE_DMA,        // DMA read
    ATA_CMD_TRUST_SEND_DMA            // DMA write
  }
};


//
// Look up table (Lba48Bit) for maximum transfer block number
//
UINTN mMaxTransferBlockNumber[] = {
  MAX_28BIT_TRANSFER_BLOCK_NUM,
  MAX_48BIT_TRANSFER_BLOCK_NUM
};


/**
  Wrapper for EFI_ATA_PASS_THRU_PROTOCOL.PassThru().

  This function wraps the PassThru() invocation for ATA pass through function
  for an ATA device. It assembles the ATA pass through command packet for ATA
  transaction.

  @param[in, out]  AtaDevice   The ATA child device involved for the operation.
  @param[in, out]  TaskPacket  Pointer to a Pass Thru Command Packet. Optional,
                               if it is NULL, blocking mode, and use the packet
                               in AtaDevice. If it is not NULL, non blocking mode,
                               and pass down this Packet.
  @param[in, out]  Event       If Event is NULL, then blocking I/O is performed.
                               If Event is not NULL and non-blocking I/O is
                               supported,then non-blocking I/O is performed,
                               and Event will be signaled when the write
                               request is completed.

  @return The return status from EFI_ATA_PASS_THRU_PROTOCOL.PassThru().

**/
EFI_STATUS
AtaDevicePassThru (
  IN OUT ATA_DEVICE                       *AtaDevice,
  IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *TaskPacket, OPTIONAL
  IN OUT EFI_EVENT                        Event OPTIONAL
  )
{
  EFI_STATUS                              Status;
  PEI_ATA_PASS_THRU_PPI                   *AtaPassThruPpi;
  EFI_ATA_PASS_THRU_COMMAND_PACKET        *Packet;

  //
  // Assemble packet
  //
  Packet = &AtaDevice->Packet;
  Packet->Asb = AtaDevice->Asb;
  Packet->Acb = &AtaDevice->Acb;

  AtaPassThruPpi = mBlockIoInstance->AtaPassThruPpi;

  Status = AtaPassThruPpi->PassThru (
                             AtaPassThruPpi,
                             AtaDevice->Port,
                             AtaDevice->PortMultiplierPort,
                             Packet
                             );
  //
  // Ensure ATA pass through caller and callee have the same
  // interpretation of ATA pass through protocol.
  //
  ASSERT (Status != EFI_INVALID_PARAMETER);
  ASSERT (Status != EFI_BAD_BUFFER_SIZE);

  return Status;
}


/**
  Gets ATA device Capacity according to ATA 6.

  This function returns the capacity of the ATA device if it follows
  ATA 6 to support 48 bit addressing.

  @param  AtaDevice         The ATA child device involved for the operation.

  @return The capacity of the ATA device or 0 if the device does not support
          48-bit addressing defined in ATA 6.

**/
EFI_LBA
GetAtapi6Capacity (
  IN ATA_DEVICE                 *AtaDevice
  )
{
  EFI_LBA                       Capacity;
  EFI_LBA                       TmpLba;
  UINTN                         Index;
  ATA_IDENTIFY_DATA             *IdentifyData;

  IdentifyData = AtaDevice->IdentifyData;
  if ((IdentifyData->command_set_supported_83 & BIT10) == 0) {
    //
    // The device doesn't support 48 bit addressing
    //
    return 0;
  }

  //
  // 48 bit address feature set is supported, get maximum capacity
  //
  Capacity = 0;
  for (Index = 0; Index < 4; Index++) {
    //
    // Lower byte goes first: word[100] is the lowest word, word[103] is highest
    //
    TmpLba = IdentifyData->maximum_lba_for_48bit_addressing[Index];
    Capacity |= LShiftU64 (TmpLba, 16 * Index);
  }

  return Capacity;
}


/**
  Identifies ATA device via the Identify data.

  This function identifies the ATA device and initializes the Media information in
  Block IO protocol interface.

  @param  AtaDevice         The ATA child device involved for the operation.

  @retval EFI_UNSUPPORTED   The device is not a valid ATA device (hard disk).
  @retval EFI_SUCCESS       The device is successfully identified and Media information
                            is correctly initialized.

**/
EFI_STATUS
IdentifyAtaDevice (
  IN OUT ATA_DEVICE                 *AtaDevice
  )
{
  ATA_IDENTIFY_DATA                 *IdentifyData;
  EFI_PEI_BLOCK_IO_MEDIA            *BlockMedia;
  EFI_LBA                           Capacity;
  UINT16                            PhyLogicSectorSupport;
  UINT16                            UdmaMode;

  IdentifyData = AtaDevice->IdentifyData;

  if ((IdentifyData->config & BIT15) != 0) {
    //
    // This is not an hard disk
    //
    return EFI_UNSUPPORTED;
  }

  DEBUG ((EFI_D_INFO, "AtaBlockIoPei - Identify Device: Port %x PortMultiplierPort %x\n", AtaDevice->Port, AtaDevice->PortMultiplierPort));

  //
  // Check whether the WORD 88 (supported UltraDMA by drive) is valid
  //
  if ((IdentifyData->field_validity & BIT2) != 0) {
    UdmaMode = IdentifyData->ultra_dma_mode;
    if ((UdmaMode & (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6)) != 0) {
      //
      // If BIT0~BIT6 is selected, then UDMA is supported
      //
      AtaDevice->UdmaValid = TRUE;
    }
  }

  Capacity = GetAtapi6Capacity (AtaDevice);
  if (Capacity > MAX_28BIT_ADDRESSING_CAPACITY) {
    //
    // Capacity exceeds 120GB. 48-bit addressing is really needed
    //
    AtaDevice->Lba48Bit = TRUE;
  } else {
    //
    // This is a hard disk <= 120GB capacity, treat it as normal hard disk
    //
    Capacity = ((UINT32)IdentifyData->user_addressable_sectors_hi << 16) | IdentifyData->user_addressable_sectors_lo;
    AtaDevice->Lba48Bit = FALSE;
  }

  //
  // Block Media Information:
  //
  BlockMedia = &AtaDevice->BlockMedia;
  BlockMedia->LastBlock = (UINTN) (Capacity - 1);

  //
  // Check whether Long Physical Sector Feature is supported
  //
  PhyLogicSectorSupport = IdentifyData->phy_logic_sector_support;
  DEBUG ((EFI_D_INFO, " PhyLogicSectorSupport = %x\n", PhyLogicSectorSupport));
  if ((PhyLogicSectorSupport & (BIT14 | BIT15)) == BIT14) {

    //
    // Check logical block size
    //
    if ((PhyLogicSectorSupport & BIT12) != 0) {
      BlockMedia->BlockSize = (UINT32) (((IdentifyData->logic_sector_size_hi << 16) | IdentifyData->logic_sector_size_lo) * sizeof (UINT16));
    }

  }

  return EFI_SUCCESS;
}

/**
  Discovers whether it is a valid ATA device.

  This function issues ATA_CMD_IDENTIFY_DRIVE command to the ATA device to identify it.
  If the command is executed successfully, it then identifies it and initializes
  the Media information in Block IO protocol interface.

  @param  AtaDevice         The ATA child device involved for the operation.

  @retval EFI_SUCCESS       The device is successfully identified and Media information
                            is correctly initialized.
  @return others            Some error occurs when discovering the ATA device.

**/
EFI_STATUS
DiscoverAtaDevice (
  IN OUT ATA_DEVICE                       *AtaDevice
  )
{
  EFI_STATUS                        Status;
  EFI_ATA_COMMAND_BLOCK             *Acb;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  *Packet;
  UINTN                             Retry;

  //
  // Prepare for ATA command block.
  //
  Acb = ZeroMem (&AtaDevice->Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb->AtaCommand = ATA_CMD_IDENTIFY_DRIVE;
  Acb->AtaDeviceHead = (UINT8) (BIT7 | BIT6 | BIT5 | (AtaDevice->PortMultiplierPort == 0xFFFF ? 0 : (AtaDevice->PortMultiplierPort << 4)));

  //
  // Prepare for ATA pass through packet.
  //
  Packet = ZeroMem (&AtaDevice->Packet, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  Packet->InDataBuffer = AtaDevice->IdentifyData;
  Packet->InTransferLength = sizeof (ATA_IDENTIFY_DATA);
  Packet->Protocol = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet->Length   = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet->Timeout  = ATA_TIMEOUT;

  Retry = MAX_RETRY_TIMES;
  do {
    Status = AtaDevicePassThru (AtaDevice, NULL, NULL);
    if (!EFI_ERROR (Status)) {
      //
      // The command is issued successfully
      //
      Status = IdentifyAtaDevice (AtaDevice);
      return Status;
    }
  } while (Retry-- > 0);

  return Status;
}

/**
  Transfer data from ATA device.

  This function performs one ATA pass through transaction to transfer data from/to
  ATA device. It chooses the appropriate ATA command and protocol to invoke PassThru
  interface of ATA pass through.

  @param[in, out]  AtaDevice       The ATA child device involved for the operation.
  @param[in, out]  TaskPacket      Pointer to a Pass Thru Command Packet. Optional,
                                   if it is NULL, blocking mode, and use the packet
                                   in AtaDevice. If it is not NULL, non blocking mode,
                                   and pass down this Packet.
  @param[in, out]  Buffer          The pointer to the current transaction buffer.
  @param[in]       StartLba        The starting logical block address to be accessed.
  @param[in]       TransferLength  The block number or sector count of the transfer.
  @param[in]       IsWrite         Indicates whether it is a write operation.
  @param[in]       Event           If Event is NULL, then blocking I/O is performed.
                                   If Event is not NULL and non-blocking I/O is
                                   supported,then non-blocking I/O is performed,
                                   and Event will be signaled when the write
                                   request is completed.

  @retval EFI_SUCCESS       The data transfer is complete successfully.
  @return others            Some error occurs when transferring data.

**/
EFI_STATUS
TransferAtaDevice (
  IN OUT ATA_DEVICE                       *AtaDevice,
  IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *TaskPacket, OPTIONAL
  IN OUT VOID                             *Buffer,
  IN EFI_LBA                              StartLba,
  IN UINT32                               TransferLength,
  IN BOOLEAN                              IsWrite,
  IN EFI_EVENT                            Event OPTIONAL
  )
{
  EFI_ATA_COMMAND_BLOCK             *Acb;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  *Packet;

  //
  // Ensure AtaDevice->UdmaValid, AtaDevice->Lba48Bit and IsWrite are valid boolean values
  //
  ASSERT ((UINTN) AtaDevice->UdmaValid < 2);
  ASSERT ((UINTN) AtaDevice->Lba48Bit < 2);
  ASSERT ((UINTN) IsWrite < 2);
  //
  // Prepare for ATA command block.
  //
  Acb = ZeroMem (&AtaDevice->Acb, sizeof (EFI_ATA_COMMAND_BLOCK));
  Acb->AtaCommand = mAtaCommands[AtaDevice->UdmaValid][AtaDevice->Lba48Bit][IsWrite];
  Acb->AtaSectorNumber = (UINT8) StartLba;
  Acb->AtaCylinderLow = (UINT8) RShiftU64 (StartLba, 8);
  Acb->AtaCylinderHigh = (UINT8) RShiftU64 (StartLba, 16);
  Acb->AtaDeviceHead = (UINT8) (BIT7 | BIT6 | BIT5 | (AtaDevice->PortMultiplierPort == 0xFFFF ? 0 : (AtaDevice->PortMultiplierPort << 4)));
  Acb->AtaSectorCount = (UINT8) TransferLength;
  if (AtaDevice->Lba48Bit) {
    Acb->AtaSectorNumberExp = (UINT8) RShiftU64 (StartLba, 24);
    Acb->AtaCylinderLowExp = (UINT8) RShiftU64 (StartLba, 32);
    Acb->AtaCylinderHighExp = (UINT8) RShiftU64 (StartLba, 40);
    Acb->AtaSectorCountExp = (UINT8) (TransferLength >> 8);
  } else {
    Acb->AtaDeviceHead = (UINT8) (Acb->AtaDeviceHead | RShiftU64 (StartLba, 24));
  }

  //
  // Prepare for ATA pass through packet.
  //
  if (TaskPacket != NULL) {
    Packet = ZeroMem (TaskPacket, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  } else {
    Packet = ZeroMem (&AtaDevice->Packet, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  }

  if (IsWrite) {
    Packet->OutDataBuffer = Buffer;
    Packet->OutTransferLength = TransferLength;
  } else {
    Packet->InDataBuffer = Buffer;
    Packet->InTransferLength = TransferLength;
  }

  Packet->Protocol = mAtaPassThruCmdProtocols[AtaDevice->UdmaValid][IsWrite];
  Packet->Length = EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  //
  // |------------------------|-----------------|------------------------|-----------------|
  // | ATA PIO Transfer Mode  |  Transfer Rate  | ATA DMA Transfer Mode  |  Transfer Rate  |
  // |------------------------|-----------------|------------------------|-----------------|
  // |       PIO Mode 0       |  3.3Mbytes/sec  | Single-word DMA Mode 0 |  2.1Mbytes/sec  |
  // |------------------------|-----------------|------------------------|-----------------|
  // |       PIO Mode 1       |  5.2Mbytes/sec  | Single-word DMA Mode 1 |  4.2Mbytes/sec  |
  // |------------------------|-----------------|------------------------|-----------------|
  // |       PIO Mode 2       |  8.3Mbytes/sec  | Single-word DMA Mode 2 |  8.4Mbytes/sec  |
  // |------------------------|-----------------|------------------------|-----------------|
  // |       PIO Mode 3       | 11.1Mbytes/sec  | Multi-word DMA Mode 0  |  4.2Mbytes/sec  |
  // |------------------------|-----------------|------------------------|-----------------|
  // |       PIO Mode 4       | 16.6Mbytes/sec  | Multi-word DMA Mode 1  | 13.3Mbytes/sec  |
  // |------------------------|-----------------|------------------------|-----------------|
  //
  // As AtaBus is used to manage ATA devices, we have to use the lowest transfer rate to
  // calculate the possible maximum timeout value for each read/write operation.
  // The timout value is rounded up to nearest integar and here an additional 30s is added
  // to follow ATA spec in which it mentioned that the device may take up to 30s to respond
  // commands in the Standby/Idle mode.
  //
  if (AtaDevice->UdmaValid) {
    //
    // Calculate the maximum timeout value for DMA read/write operation.
    //
    Packet->Timeout  = EFI_TIMER_PERIOD_SECONDS (DivU64x32 (MultU64x32 (TransferLength, AtaDevice->BlockMedia.BlockSize), 2100000) + 31);
  } else {
    //
    // Calculate the maximum timeout value for PIO read/write operation
    //
    Packet->Timeout  = EFI_TIMER_PERIOD_SECONDS (DivU64x32 (MultU64x32 (TransferLength, AtaDevice->BlockMedia.BlockSize), 3300000) + 31);
  }

  return AtaDevicePassThru (AtaDevice, TaskPacket, Event);
}

/**
  Read or write a number of blocks from ATA device.

  This function performs ATA pass through transactions to read/write data from/to
  ATA device. It may separate the read/write request into several ATA pass through
  transactions.

  @param[in, out]  AtaDevice       The ATA child device involved for the operation.
  @param[in, out]  Buffer          The pointer to the current transaction buffer.
  @param[in]       StartLba        The starting logical block address to be accessed.
  @param[in]       NumberOfBlocks  The block number or sector count of the transfer.
  @param[in]       IsWrite         Indicates whether it is a write operation.
  @param[in, out]  Token           A pointer to the token associated with the transaction.

  @retval EFI_SUCCESS       The data transfer is complete successfully.
  @return others            Some error occurs when transferring data.

**/
EFI_STATUS
AccessAtaDevice(
  IN OUT ATA_DEVICE                 *AtaDevice,
  IN OUT UINT8                      *Buffer,
  IN EFI_LBA                        StartLba,
  IN UINTN                          NumberOfBlocks,
  IN BOOLEAN                        IsWrite,
  IN OUT EFI_BLOCK_IO2_TOKEN        *Token
  )
{
  EFI_STATUS                        Status;
  UINTN                             MaxTransferBlockNumber;
  UINTN                             TransferBlockNumber;
  UINTN                             BlockSize;
  UINTN                             Index;

  Status = EFI_SUCCESS;
  Index  = 0;

  //
  // Ensure AtaDevice->Lba48Bit is a valid boolean value
  //
  ASSERT ((UINTN) AtaDevice->Lba48Bit < 2);
  MaxTransferBlockNumber = mMaxTransferBlockNumber[AtaDevice->Lba48Bit];
  BlockSize              = AtaDevice->BlockMedia.BlockSize;

  while (!IsListEmpty (&AtaDevice->AtaTaskList) || !IsListEmpty (&AtaDevice->AtaSubTaskList)) {
    //
    // Stall for 100us.
    //
    MicroSecondDelay (100);
  }

  do {
    if (NumberOfBlocks > MaxTransferBlockNumber) {
      TransferBlockNumber = MaxTransferBlockNumber;
      NumberOfBlocks     -= MaxTransferBlockNumber;
    } else  {
      TransferBlockNumber = NumberOfBlocks;
      NumberOfBlocks      = 0;
    }

    //
    // Blocking Mode.
    //
    DEBUG ((DEBUG_BLKIO, "Blocking AccessAtaDevice, TransferBlockNumber=%x; StartLba = %x\n", TransferBlockNumber, StartLba));
    Status = TransferAtaDevice (AtaDevice, NULL, Buffer, StartLba, (UINT32) TransferBlockNumber, IsWrite, NULL);

    if (EFI_ERROR (Status)) {
      goto EXIT;
    }

    Index++;
    StartLba += TransferBlockNumber;
    Buffer   += TransferBlockNumber * BlockSize;
  } while (NumberOfBlocks > 0);

EXIT:

  return Status;
}

