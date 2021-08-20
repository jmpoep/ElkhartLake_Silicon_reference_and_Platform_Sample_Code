/** @file
  Definitions related with provision file layout.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _PROVISION_FILE_H_
#define _PROVISION_FILE_H_

#define PROVISION_FILE_NAME L"\\setup.bin"

#define MAJOR_VERSION_1  0x01
#define MAJOR_VERSION_2  0x02
#define MAJOR_VERSION_3  0x03
#define MAJOR_VERSION_4  0x04

#define MINOR_VERSION_0  0x00
#define MINOR_VERSION_1  0x01

#define FILE_TYPE_1_UUID \
  { \
    0x71FB16B5, 0xCB87, 0x4AF9, { 0xB4, 0x41, 0xCA, 0x7B, 0x38, 0x35, 0x78, 0xF9 } \
  }

#define FILE_TYPE_2_UUID \
  { \
    0x5881B296, 0x6BCF, 0x4C72, { 0x8B, 0x91, 0xA1, 0x5E, 0x51, 0x2E, 0x99, 0xC4 } \
  }

#define FILE_TYPE_3_UUID \
  { \
    0xC6F6F7A7, 0xC489, 0x47F6, { 0x93, 0xED, 0xE2, 0xE5, 0x02, 0x0D, 0xA5, 0x1D } \
  }

#define FILE_TYPE_4_UUID \
  { \
    0x5234A9AA, 0x29E1, 0x44A9, { 0x8D, 0x4D, 0x08, 0x1C, 0x07, 0xB9, 0x63, 0x53 } \
  }

#define CHUNK_SIZE  512

//
// File flags are only valid from version 2 and up
//
#define FILE_FLAGS_DONT_CONSUME_RECORDS 0x01

#pragma pack(1)

typedef struct {
  EFI_GUID  FileTypeUUID;
  UINT16    RecordChunkCount;
  UINT16    RecordHeaderByteCount;
  UINT32    RecordNumber;
  UINT8     MajorVersion;
  UINT8     MinorVersion;
  UINT16    FileFlags;
  UINT32    DataRecordCount;
  UINT32    DataRecordsConsumed;
  UINT16    DataRecordChunkCount;
  UINT16    Reserved2;
  UINT16    ModuleList[(127 - 9) * 2];
} PROVISION_FILE_HEADER;

#pragma pack()

#define DATA_RECORD_TYPE_INVALID      0
#define DATA_RECORD_TYPE_DATA_RECORD  1

#define DATA_RECORD_FLAG_VALID  1

#pragma pack(1)

typedef struct {
  UINT32  RecordTypeIdentifier;
  UINT32  RecordFlags;
  UINT32  Reserved1[2];
  UINT16  RecordChunkCount;
  UINT16  RecordHeaderByteCount;
  UINT32  RecordNumber;
} PROVISION_DATA_RECORD_HEADER;

typedef struct {
  PROVISION_DATA_RECORD_HEADER  Header;
  UINT8                         Data[];
} PROVISION_DATA_RECORD;

#pragma pack()

#define MODULE_IDENTIFIER_INVALID       0
#define MODULE_IDENTIFIER_ME_KERNEL     1
#define MODULE_IDENTIFIER_INTEL_AMT_CM  2

#define VARIABLE_IDENTIFIER_ME_KERNEL_INVALID               0
#define VARIABLE_IDENTIFIER_ME_KERNEL_CURRENT_MEBX_PASSWORD 1
#define VARIABLE_IDENTIFIER_ME_KERNEL_NEW_MEBX_PASSWORD     2

#define VARIABLE_IDENTIFIER_INTEL_AMT_CM_INVALID  0
#define VARIABLE_IDENTIFIER_INTEL_AMT_CM_PID      1
#define VARIABLE_IDENTIFIER_INTEL_AMT_CM_PPS      2

#pragma pack(1)

typedef struct {
  UINT16  ModuleIdentifier;
  UINT16  VariableIdentifier;
  UINT16  VariableLength;
  UINT16  Reserved1;
  VOID    *VariableValue;
} DATA_RECORD_ENTRY;

#pragma pack()

#endif

