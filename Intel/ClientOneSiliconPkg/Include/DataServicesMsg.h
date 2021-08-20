/** @file
  CSME Data Services Message Definitions.

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

#ifndef _CSME_DATA_SERVICES_MSG_H_
#define _CSME_DATA_SERVICES_MSG_H_

#include <Register/MeRegs.h>
#include <MkhiMsgs.h>

#define  CSME_DATA_SERVICE_HECI_COMM_BUFFER_PAGES  64

#pragma pack(push, 1)

///
/// Storage Command Types
///
typedef enum {
  // Storage CMD 0x0 Undefined
  BIOS_STORAGE_READ_FILE_CMD                = 0x1,
  BIOS_STORAGE_WRITE_FILE_CMD               = 0x2,
  BIOS_STORAGE_FILE_SIZE_CMD                = 0x3,
  BIOS_STORAGE_LOCK_DIR_CMD                 = 0x4,
  BIOS_STORAGE_GET_PROXY_STATE_CMD          = 0x5,
  BIOS_STORAGE_WRITE_CMD_TRUSTED_CHANNEL    = 0x6,
  BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL     = 0x7,
  BIOS_STORAGE_WRITE_CMD                    = 0x17,
  BIOS_STORAGE_READ_CMD                     = 0x18
} BIOS_STORAGE_COMMANDS;

///
/// Storage Command Status Types
///
typedef enum {
  BIOS_STORAGE_STATUS_SUCCESS               = 0x0,
  BIOS_STORAGE_STATUS_INVALID_OFFSET        = 0x1,
  BIOS_STORAGE_STATUS_INVALID_SIZE          = 0x2,
  BIOS_STORAGE_STATUS_ACCESS_DENIED         = 0x3,
  BIOS_STORAGE_STATUS_DEVICE_ERROR          = 0x4,
  BIOS_STORAGE_STATUS_PROXY_NOT_FOUND       = 0x5,
  BIOS_STORAGE_STATUS_PARTITION_NOT_PRESENT = 0x6
} BIOS_STORAGE_STATUS;

///
/// Storage Command and Request/Response Info
///
typedef struct {
  UINT8                 Id         : 7;   ///< Command ID (XXX_CMD_ID)
  UINT8                 IsResponse : 1;   ///< Request = 0, Response = 1
} BIOS_STORAGE_COMMAND;

///
/// Collection of Flags Which Extends the Command's Functionality
///
typedef struct {
  UINT32                WritePatternByte : 1;  ///< When set, the command will result in writing the same byte with the
                                               ///< value of Pattern at offset to offset+size. Buffers are ignored if set.
  UINT32                Reserved1        : 7;
  UINT32                PatternByte      : 8;  ///< The byte to write if WritePatternByte is set.
  UINT32                Reserved2        : 16;
} BIOS_STORAGE_FLAGS;

///
/// BIOS Storage Request Body
///
typedef struct {
  UINT32                Offset;
  UINT32                Length;
  UINT32                BufferAddressLow;
  UINT32                BufferAddressHigh;
  BIOS_STORAGE_FLAGS    Flags;
} BIOS_STORAGE_REQUEST_BODY;

///
/// BIOS Storage Response Body
///
typedef struct {
  UINT32                FailureSpecificData;
} BIOS_STORAGE_RESPONSE_BODY;

///
/// BIOS Storage Write
///
/// This command is sent by the BIOS to CSME for writing data to the data partition (GPP or RPMB), CSME is responsible
/// to detect the current data partition and write the data accordingly to the BIOS area in the partition.
///
/// Note: The offset field is the offset from the beginning of the BIOS area in the data partition, it is not the
/// physical address in the partition itself. The maximum size of a single write is limited to 256K.
///
///
/// BIOS Storage Read
///
/// This command is sent by the BIOS to CSME for reading content from the current data partition (GPP or RPMB), CSME
/// is responsible to detect the current data partition and read the data accordingly from the BIOS area in the partition.
///
/// Note: the offset field is the offset from the beginning of the BIOS area in the data partition, it is not the
/// physical address in the partition itself. The maximum size of a single read is limited to 256K.
///
typedef struct {
  MKHI_MESSAGE_HEADER        MkhiHeader;
  BIOS_STORAGE_REQUEST_BODY  Body;
} BIOS_STORAGE_REQUEST;

typedef struct {
  MKHI_MESSAGE_HEADER        MkhiHeader;
  BIOS_STORAGE_RESPONSE_BODY Body;
} BIOS_STORAGE_RESPONSE;

typedef union {
  BIOS_STORAGE_REQUEST       Request;
  BIOS_STORAGE_RESPONSE      Response;
} BIOS_STORAGE_BUFFER;

#pragma pack(pop)

#endif
