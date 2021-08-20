/** @file
  Private Include file for AtaBlockIo PEI.

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

#ifndef _PEI_ATA_BLOCK_IO_H_
#define _PEI_ATA_BLOCK_IO_H_

#include <Uefi.h>
#include <PiPei.h>

#include <Ppi/BlockIo.h>
#include <Ppi/AtaPassThruPpi.h>

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Atapi.h>

#define ATA_TASK_SIGNATURE                SIGNATURE_32 ('A', 'T', 'S', 'K')
#define ATA_DEVICE_SIGNATURE              SIGNATURE_32 ('A', 'B', 'I', 'D')
#define ATA_SUB_TASK_SIGNATURE            SIGNATURE_32 ('A', 'S', 'T', 'S')
#define IS_ALIGNED(addr, size)            (((UINTN) (addr) & (size - 1)) == 0)

#define MAX_DEVICES     8  //


//
// Time out value for ATA pass through protocol
//
#define ATA_TIMEOUT                       EFI_TIMER_PERIOD_SECONDS (3)

//
// Maximum number of times to retry ATA command
//
#define MAX_RETRY_TIMES                   3

//
// The maximum total sectors count in 28 bit addressing mode
//
#define MAX_28BIT_ADDRESSING_CAPACITY     0xfffffff

//
// The maximum ATA transaction sector count in 28 bit addressing mode.
//
#define MAX_28BIT_TRANSFER_BLOCK_NUM      0x100

//
// The maximum ATA transaction sector count in 48 bit addressing mode.
//
//#define MAX_48BIT_TRANSFER_BLOCK_NUM      0x10000

//
// BugBug: if the TransferLength is equal with 0x10000 (the 48bit max length),
// there is a bug that even the register interrupt bit has been sit, the buffer
// seems not ready. Change the Maximum Sector Numbers to 0xFFFF to work round
// this issue.
//
#define MAX_48BIT_TRANSFER_BLOCK_NUM      0xFFFF

/**
  The struct of Block IO2 Token.
**/
typedef struct {

  ///
  /// If Event is NULL, then blocking I/O is performed.If Event is not NULL and
  /// non-blocking I/O is supported, then non-blocking I/O is performed, and
  /// Event will be signaled when the read request is completed.
  ///
  EFI_EVENT               Event;

  ///
  /// Defines whether or not the signaled event encountered an error.
  ///
  EFI_STATUS              TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

//
// ATA device data structure for each child device
//
typedef struct {
  UINT32                                Signature;

  EFI_PEI_BLOCK_IO_MEDIA                BlockMedia;
  UINT16                                Port;
  UINT16                                PortMultiplierPort;

  //
  // Buffer for the execution of ATA pass through protocol
  //
  EFI_ATA_PASS_THRU_COMMAND_PACKET      Packet;
  EFI_ATA_COMMAND_BLOCK                 Acb;
  EFI_ATA_STATUS_BLOCK                  *Asb;

  BOOLEAN                               UdmaValid;
  BOOLEAN                               Lba48Bit;

  //
  // Cached data for ATA identify data
  //
  ATA_IDENTIFY_DATA                     *IdentifyData;

  LIST_ENTRY                            AtaTaskList;
  LIST_ENTRY                            AtaSubTaskList;
  BOOLEAN                               Abort;
} ATA_DEVICE;

///////

#define PEI_ATA_BLK_IO_SIGNATURE  SIGNATURE_32 ('a', 'b', 'i', 'o')
typedef struct {
  UINTN                           Signature;
  EFI_PEI_RECOVERY_BLOCK_IO_PPI   AtaBlkIoPpi;
  EFI_PEI_PPI_DESCRIPTOR          AtaBlkIoPpiList;
  PEI_ATA_PASS_THRU_PPI           *AtaPassThruPpi;
  UINTN                           DeviceCount;
  ATA_DEVICE                      DeviceInfo[MAX_DEVICES];
} PEI_ATA_BLK_IO_INSTANCE;

//
// Sub-Task for the non blocking I/O
//
typedef struct {
  UINT32                            Signature;
  ATA_DEVICE                        *AtaDevice;
  EFI_BLOCK_IO2_TOKEN               *Token;
  UINTN                             *UnsignalledEventCount;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  Packet;
  BOOLEAN                           *IsError;// Indicate whether meeting error during source allocation for new task.
  LIST_ENTRY                        TaskEntry;
} ATA_BUS_ASYN_SUB_TASK;

//
// Task for the non blocking I/O
//
typedef struct {
  UINT32                            Signature;
  EFI_BLOCK_IO2_TOKEN               *Token;
  ATA_DEVICE                        *AtaDevice;
  UINT8                             *Buffer;
  EFI_LBA                           StartLba;
  UINTN                             NumberOfBlocks;
  BOOLEAN                           IsWrite;
  LIST_ENTRY                        TaskEntry;
} ATA_BUS_ASYN_TASK;

#define PEI_RECOVERY_PPI_FROM_BLKIO_THIS(a) CR (a, PEI_ATA_BLK_IO_INSTANCE, AtaBlkIoPpi, PEI_ATA_BLK_IO_SIGNATURE)

extern PEI_ATA_BLK_IO_INSTANCE           *mBlockIoInstance;

/**
  Gets the count of block I/O devices that one specific block driver detects.

  This function is used for getting the count of block I/O devices that one
  specific block driver detects.  To the PEI ATAPI driver, it returns the number
  of all the detected ATAPI devices it detects during the enumeration process.
  To the PEI legacy floppy driver, it returns the number of all the legacy
  devices it finds during its enumeration process. If no device is detected,
  then the function will return zero.

  @param[in]  PeiServices          General-purpose services that are available
                                   to every PEIM.
  @param[in]  This                 Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI
                                   instance.
  @param[out] NumberBlockDevices   The number of block I/O devices discovered.

  @retval     EFI_SUCCESS          Operation performed successfully.

**/
EFI_STATUS
EFIAPI
BotGetNumberOfBlockDevices (
  IN   EFI_PEI_SERVICES                  **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI     *This,
  OUT  UINTN                             *NumberBlockDevices
  );

/**
  Gets a block device's media information.

  This function will provide the caller with the specified block device's media
  information. If the media changes, calling this function will update the media
  information accordingly.

  @param[in]  PeiServices   General-purpose services that are available to every
                            PEIM
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, the PPIs that
                            want to talk to a single device must specify the
                            device index that was assigned during the enumeration
                            process. This index is a number from one to
                            NumberBlockDevices.
  @param[out] MediaInfo     The media information of the specified block media.
                            The caller is responsible for the ownership of this
                            data structure.

  @retval EFI_SUCCESS           Media information about the specified block device
                                was obtained successfully.
  @retval EFI_DEVICE_ERROR      Cannot get the media information due to a hardware
                                error.
  @retval Others                Other failure occurs.

**/
EFI_STATUS
EFIAPI
BotGetMediaInfo (
  IN   EFI_PEI_SERVICES                     **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI        *This,
  IN   UINTN                                DeviceIndex,
  OUT  EFI_PEI_BLOCK_IO_MEDIA               *MediaInfo
  );

/**
  Reads the requested number of blocks from the specified block device.

  The function reads the requested number of blocks from the device. All the
  blocks are read, or an error is returned. If there is no media in the device,
  the function returns EFI_NO_MEDIA.

  @param[in]  PeiServices   General-purpose services that are available to
                            every PEIM.
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, the PPIs that
                            want to talk to a single device must specify the device
                            index that was assigned during the enumeration process.
                            This index is a number from one to NumberBlockDevices.
  @param[in]  StartLBA      The starting logical block address (LBA) to read from
                            on the device
  @param[in]  BufferSize    The size of the Buffer in bytes. This number must be
                            a multiple of the intrinsic block size of the device.
  @param[out] Buffer        A pointer to the destination buffer for the data.
                            The caller is responsible for the ownership of the
                            buffer.

  @retval EFI_SUCCESS             The data was read correctly from the device.
  @retval EFI_DEVICE_ERROR        The device reported an error while attempting
                                  to perform the read operation.
  @retval EFI_INVALID_PARAMETER   The read request contains LBAs that are not
                                  valid, or the buffer is not properly aligned.
  @retval EFI_NO_MEDIA            There is no media in the device.
  @retval EFI_BAD_BUFFER_SIZE     The BufferSize parameter is not a multiple of
                                  the intrinsic block size of the device.

**/
EFI_STATUS
EFIAPI
AtaReadBlocks (
  IN   EFI_PEI_SERVICES                  **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI     *This,
  IN   UINTN                             DeviceIndex,
  IN   EFI_PEI_LBA                       StartLBA,
  IN   UINTN                             BufferSize,
  OUT  VOID                              *Buffer
  );

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
  );

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
  );

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
  );

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
  );

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
  );

#endif
