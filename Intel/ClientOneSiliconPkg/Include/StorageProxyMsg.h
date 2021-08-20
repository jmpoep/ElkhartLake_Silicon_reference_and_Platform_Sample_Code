/** @file
  Storage Proxy Message Definitions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

@par Specification
**/

#ifndef _STORAGE_PROXY_MSG_H_
#define _STORAGE_PROXY_MSG_H_

#include <Register/MeRegs.h>
#include <Library/RpmbLib.h>

#pragma pack(push, 1)

/// Based on definitions in CSME Host Interface 1.94

#define BOOT_PARTITION1                             0
#define BOOT_PARTITION2                             1
#define FIRMWARE_BOOT_PARTITION                     BOOT_PARTITION2
#define STORAGE_PROXY_BUFFER_DMA_SUPPORT            1
#define STORAGE_PROXY_CRITICAL_SECTION_LOCK         1
#define STORAGE_PROXY_CRITICAL_SECTION_UNLOCK       0
#define STORAGE_PROXY_HECI_COMMUNICATE_BUFFER_PAGES 32
#define STORAGE_PROXY_HECI_DEVICE                   HECI4_DEVICE
#define STORAGE_PROXY_PARTITION_ACCESSIBLE          1
#define STORAGE_PROXY_PARTITION_BOOT_INDICATOR      2
#define STORAGE_PROXY_PARTITION_GPP_INDICATOR       1
#define STORAGE_PROXY_PARTITION_INACCESSIBLE        0

///
/// Message header for all Storage Proxy messages
///
typedef union {
  UINT32  Data;
  struct {
    UINT32 Command       : 7;    ///< Storage Proxy command
    UINT32 IsResponse    : 1;    ///< Set if the message is a client response
    UINT32 Length        : 13;   ///< Message length
    UINT32 Status        : 8;    ///< Message status
    UINT32 Reserved      : 3;    ///< Reserved
  } Fields;
} STORAGE_PROXY_MESSAGE_HEADER;

///
/// Storage Proxy Capabilities
///
typedef union {
  UINT32  Capabilities;
  struct {
    UINT32 BufferDmaSupport   : 1;  ///< Indicates whether the SPD can provide a buffer address for DMA.
    UINT32 Reserved           : 31; ///< Reserved
  } Fields;
} STORAGE_PROXY_CAPABILITIES;

///
/// Storage Proxy Command Types
///
typedef enum {
  // Storage Proxy CMD 0x0 Undefined
  STORAGE_PROXY_CMD_PROXY_STOP           = 0x1,
  STORAGE_PROXY_CMD_RPMB_WRITE,
  STORAGE_PROXY_CMD_RPMB_READ,
  STORAGE_PROXY_CMD_RPMB_GET_COUNTER,
  STORAGE_PROXY_CMD_GPP_WRITE,
  STORAGE_PROXY_CMD_GPP_READ,
  // Storage Proxy CMD 0x7 Undefined
  STORAGE_PROXY_CMD_PROXY_INIT           = 0x8,
  STORAGE_PROXY_CMD_PROXY_STATUS,
  STORAGE_PROXY_CMD_ALLOC_MEMORY_BUFFER,
  STORAGE_PROXY_CMD_COMMIT_MEMORY_BUFFER,
  STORAGE_PROXY_CMD_FILL_MEMORY_BUFFER,
  STORAGE_PROXY_CMD_MANAGE_CRITICAL_SECTION
} STORAGE_PROXY_COMMAND;

///
/// Storage Proxy Status Types
///
typedef enum {
  STORAGE_PROXY_STATUS_SUCCESS          = 0,
  STORAGE_PROXY_STATUS_GENERAL_FAILURE  = 1,
  STORAGE_PROXY_STATUS_NOT_READY        = 2,
  STORAGE_PROXY_STATUS_NOT_SUPPORTED    = 3,
  STORAGE_PROXY_STATUS_INVALID_COMMAND  = 4,
  STORAGE_PROXY_STATUS_INVALID_ADDRESS  = 5
} STORAGE_PROXY_STATUS;

///
/// Storage Proxy Storage Types
///
typedef enum {
  STORAGE_PROXY_TYPE_INVALID = 0,
  STORAGE_PROXY_TYPE_EMMC,
  STORAGE_PROXY_TYPE_UFS,
  STORAGE_PROXY_TYPE_NVME
} STORAGE_PROXY_TYPE;

///
/// Allocate Memory Buffer
///
/// CSME sends this message to the SPD to allocate a non-pageable memory buffer in DRAM
/// which will be used by CSME as part of capsule update, the SPD (BIOS or OS) shall
/// allocate the buffer and return the address to CSME which can then update and then ask
/// the SPD to the content of the buffer to a given offset in the partition.
/// The SPD should allocate a buffer in a 4K aligned address.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         Length;                 ///< Length of the buffer in bytes.
} STORAGE_PROXY_ALLOC_MEMORY_BUFFER_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;     ///< Low 32 bits of the buffer's 64 bit address in system memory.
  UINT32                         BufferAddressLow;       ///< High 32 bits of the buffer's 64 bit address in system memory.
  UINT32                         BufferAddressHigh;
} STORAGE_PROXY_ALLOC_MEMORY_BUFFER_RESPONSE;

typedef union {
  STORAGE_PROXY_ALLOC_MEMORY_BUFFER_REQUEST  Request;
  STORAGE_PROXY_ALLOC_MEMORY_BUFFER_RESPONSE Response;
} STORAGE_PROXY_ALLOC_MEMORY_BUFFER_BUFFER;

///
/// Commit Memory Buffer (Write Memory Buffer)
///
/// CSME sends this message to the SPD to write data in a provided address to a selected
/// boot partition, this will be used by CSME during FW update flows.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         StoragePartition;       ///< Logical storage partition number
                                                         ///< 1: GPP partition, 2: Boot partition
  UINT8                          DeallocateAfterCommit;  ///< Indicates that the SPD should de-allocate the buffer after
                                                         ///< commit. CSME can ask the SPD to de-allocate the buffer
                                                         ///< without associating a writh with it by setting length as 0.
  UINT8                         Reserved[3];
  UINT32                         OffsetInBuffer;         ///< Offset in the allocated buffer to start the write from.
  UINT32                         NvmOffset;              ///< Byte offset in the NVM device to write the data to.
  UINT32                         Length;                 ///< Length of the buffer to write in bytes.
} STORAGE_PROXY_COMMIT_MEMORY_BUFFER_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         BytesWritten;           ///< Number of bytes written if successful.
} STORAGE_PROXY_COMMIT_MEMORY_BUFFER_RESPONSE;

typedef union {
  STORAGE_PROXY_COMMIT_MEMORY_BUFFER_REQUEST  Request;
  STORAGE_PROXY_COMMIT_MEMORY_BUFFER_RESPONSE Response;
} STORAGE_PROXY_COMMIT_MEMORY_BUFFER_BUFFER;

///
/// Fill Memory Buffer (Read Memory Buffer)
///
/// CSME sends this message to the SPD to read data to the provided address in the buffer allocated by the
/// Allocate Memory Buffer command from the selected storage partition.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         StoragePartition;       ///< Logical storage partition number
  UINT32                         OffsetInBuffer;         ///< Offset in the allocated buffer to write the data to.
  UINT32                         NvmOffset;              ///< Byte offset in the NVM device to read the data from.
  UINT32                         Length;                 ///< Length of the buffer to read in bytes.
} STORAGE_PROXY_FILL_MEMORY_BUFFER_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         BytesRead;              ///< Number of bytes read if successful.
} STORAGE_PROXY_FILL_MEMORY_BUFFER_RESPONSE;

typedef union {
  STORAGE_PROXY_FILL_MEMORY_BUFFER_REQUEST  Request;
  STORAGE_PROXY_FILL_MEMORY_BUFFER_RESPONSE Response;
} STORAGE_PROXY_FILL_MEMORY_BUFFER_BUFFER;

///
/// GPP Read
///
/// CSME sends this message to SPD for reading data from the GPP partition which was provided at the STORAGE_PROXY_INIT
/// message.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         Offset;                 ///< Offset in GPP to write the data to.
  UINT32                         Size;                   ///< Size in bytes to read
} STORAGE_PROXY_GPP_READ_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         Reserved;
  UINT8                          Payload[];              ///< The data read by the SPD. The size of the payload is the
                                                         ///< Length field in the storage proxy message header.
} STORAGE_PROXY_GPP_READ_RESPONSE;

typedef union {
  STORAGE_PROXY_GPP_READ_REQUEST     Request;
  STORAGE_PROXY_GPP_READ_RESPONSE    Response;
} STORAGE_PROXY_GPP_READ_BUFFER;

///
/// GPP Write
///
/// CSME sends this message to SPD for writing data to the GPP partition which was provided at the STORAGE_PROXY_INIT
/// message. The SPD performs the write to the GPP and returns the response.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         Offset;                 ///< Offset in GPP to write the data to.
  UINT8                          Payload[];              ///< Data to write to GPP. Size of the payload is the Length
                                                         ///< field in the storage proxy message header - header size -
                                                         ///< offset size.
} STORAGE_PROXY_GPP_WRITE_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT8                          Reserved[8];
} STORAGE_PROXY_GPP_WRITE_RESPONSE;

typedef union {
  STORAGE_PROXY_GPP_WRITE_REQUEST  Request;
  STORAGE_PROXY_GPP_WRITE_RESPONSE Response;
} STORAGE_PROXY_GPP_WRITE_BUFFER;

///
/// Manage Critical Section
///
/// CSE sends this message prior to entering a critical sequence of write requests to inform the SPD to lock SPD
/// shutdown. If the SPD has not entered the Storage Proxy Done procedure it will respond with a Storage Proxy Status
/// command to indicate the storage proxy was successfully locked. CSE will send the Manage Critical Section message to
/// the SPD again to indicate to unlock the storage proxy after the critical section is completed in CSE. If BIOS has
/// already entered the Storage Proxy Done procedure the SPD will not respond indicating CSE should not proceed with
/// its critical section until OS runtime.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         Command;                ///< 0: Unlock Storage Proxy shutdown
                                                         ///< 1: Lock Storage Proxy shutdown
} STORAGE_PROXY_MANAGE_CRITICAL_SECTION_REQUEST;

///
/// There is not a Manage Critical Section response message.
///

///
/// Storage Proxy Initialize
///
/// SPD sends this message to CSME to retrieve information regarding the device which the SPD should work with, CSME
/// responds back with the card’s serial number and the GPP ID to be used on future GPP related requests. This is the
/// first message which the proxy sends to CSME.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER     StorageProxyHeader;
} STORAGE_PROXY_INIT_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER     StorageProxyHeader;
  UINT32                           GppPartitionId;       ///< ID of the GPP partition used by CSME.
                                                         ///<   E.g. UFS LUN Number (0 - 7) or EMMC Partition 1 - 4
  UINT32                           RpmbPartitionId;      ///< ID of the RPMB partition ID used by CSME.
                                                         ///<   E.g. UFS LUN Number (0 - 7) or EMMC Partition 1 - 4
  UINT8                            Reserved[8];
  STORAGE_PROXY_TYPE               StorageType;          ///< Type of storage (e.g. eMMC, UFS, NVMe, etc.)
  UINT32                           SerialNumberSize;     ///< Length in bytes of the device's serial number.
  UINT8                            SerialNumber[];       ///< The device's serial number. Length is SerialNumberSize bytes.
                                                         ///< UFS: The result of the READ_DESC command with SERIAL_NUMBER
                                                         ///<      index.
                                                         ///< EMMC: The content of the CID register.
} STORAGE_PROXY_INIT_RESPONSE;

typedef union {
  STORAGE_PROXY_INIT_REQUEST       Request;
  STORAGE_PROXY_INIT_RESPONSE      Response;
} STORAGE_PROXY_INIT_BUFFER;

///
/// RPMB Read Counter Request
///
/// CSME sends this message to SPD for reading the current value of the RPMB Write Counter, in general CSME should read
/// the counter during its initialization while CSME still owns the device and manage the counter value with every write
/// request, this reduces the number of calls for this command, CSME will use this command in case of internal CSME
/// resets or any other scenario where CSME reinitializes and doesn’t have card ownership.
///
/// The SPD sends the RPMB frame to the card, the SPD then reads the response and sends it back to CSME, CSME then
/// validates the RPMB response and consumes the counter value.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Read Counter Request Frame.
} STORAGE_PROXY_RPMB_GET_COUNTER_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Read Counter Response Frame.
} STORAGE_PROXY_RPMB_GET_COUNTER_RESPONSE;

typedef union {
  STORAGE_PROXY_RPMB_GET_COUNTER_REQUEST  Request;
  STORAGE_PROXY_RPMB_GET_COUNTER_RESPONSE Response;
} STORAGE_PROXY_RPMB_GET_COUNTER_BUFFER;

///
/// RPMB Read
///
/// CSME sends this message to SPD for reading the current value of the RPMB Write Counter, in general CSME should
/// read the counter during its initialization while CSME still owns the device and manages the counter value with every
/// write request, this reduces the number of calls for this command, CSME will use this command in case of internal
/// CSME resets or any other scenario where CSME reinitializes and doesn’t have card ownership.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Read Request Frame.
} STORAGE_PROXY_RPMB_READ_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Read Response Frame.
} STORAGE_PROXY_RPMB_READ_RESPONSE;

typedef union {
  STORAGE_PROXY_RPMB_READ_REQUEST        Request;
  STORAGE_PROXY_RPMB_READ_RESPONSE       Response;
} STORAGE_PROXY_RPMB_READ_BUFFER;

///
/// RPMB Write
///
/// CSME sends this message to SPD for writing to the RPMB device, the SPD processes the request and sends the RPMB
/// frame to the card, the SPD is also responsible to create the ResultRequest RPMB message which follows an RPMB Write
/// frame and send it to the card, the SPD then reads the response and sends the response back to CSME which then
/// validates and processes the RPMB response.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Write Request Frame.
} STORAGE_PROXY_RPMB_WRITE_REQUEST;

typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  RPMB_FRAME                     RpmbFrame; ///< RPMB Write Response Frame.
} STORAGE_PROXY_RPMB_WRITE_RESPONSE;

typedef union {
  STORAGE_PROXY_RPMB_WRITE_REQUEST       Request;
  STORAGE_PROXY_RPMB_WRITE_RESPONSE      Response;
} STORAGE_PROXY_RPMB_WRITE_BUFFER;

///
/// Storage Proxy Stop
///
/// SPD sends this message to indicate CSME that the Proxy has stopped and CSME should stop sending requests accordingly,
/// there is no response for this message. Since BIOS communicates with CSME over fixed HECI connection then the absence
/// of flow control messages could result in having CSME blocked on waiting on a response message which is expected but
/// never come since the proxy is no longer present, therefore this message is also used to get CSME out of the blocking
/// state.
///
/// If BIOS has to perform a platform reset as part of error handling and the storage proxy is currently running then
/// BIOS MUST send this message to CSE before initiating the reset, this will ensure the CSE storage stack is unblocked
/// in case it is waiting for a pending response expected from BIOS.
///
/// To prevent BIOS from stopping the proxy while CSE in a middle of a transaction which includes multiple fragments, it
/// BIOS must only terminate the storage proxy when CSE has no pending storage operations. This is detected by the
/// Storage Operation in Progress bit.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT8                          ProxyState;             ///< 0: Proxy Stopped
  UINT8                          Reserved[3];
} STORAGE_PROXY_STOP_REQUEST;

///
/// There is not a Proxy Stop response message.
///

///
/// Storage Proxy Status
///
/// SPD sends this message to CSME to indicate CSME it can access the RPMB and the GPP partitions, this serves as an
/// indication to CSME it can use the proxy to write to RPMB and GPP. There is no response from CSME for this message.
/// state.
///
typedef struct {
  STORAGE_PROXY_MESSAGE_HEADER   StorageProxyHeader;
  UINT32                         GppPartitionState;      ///< 0: GPP partition is inaccessible.
                                                         ///< 1: GPP partition is accessible.
  UINT32                         RpmbPartitionState;     ///< 0: RPMB partition is inaccessible.
                                                         ///< 1: RPMB partition is accessible.
  UINT32                         BootPartitionState;     ///< 0: Boot partition is inaccessible.
                                                         ///< 1: Boot partition is accessible.
  UINT8                          Reserved[8];
  UINT32                         CriticalSection;        ///< 0: Critical section is off.
                                                         ///< 1: Critical section is on.
  STORAGE_PROXY_CAPABILITIES     Capabilities;
} STORAGE_PROXY_STATUS_REQUEST;

///
/// There is not a Proxy Status response message.
///

#pragma pack(pop)

#endif
