/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  Data structure copied from TCG PC Client Specific Implementation
  Specification For Conventional BIOS

Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#ifndef _TCG_SMM_H_
#define _TCG_SMM_H_

#define LEGACY_TCG_SERVICE  0xBB

typedef enum {
  TCG_StatusCheck,
  TCG_HashLogExtendEvent,
  TCG_PassThroughToTPM,
  TCG_ShutdownPreBootInterface,
  TCG_HashLogEvent,
  TCG_HashAll,
  TCG_Tss,
  TCG_CompactHashLogExtendEvent,
  TCG_MemoryOverwriteRequest,
  TCG_DriverInit = 0x20
} TCG_FUNCTION_ID;

#define  TCG_PC_OK                   0                      // The function returned successful.
#define  TCG_PC_TPMERROR             (TCG_PC_OK + 0x01)     // TCG_PC_OK + 01h | (TPM driver error << 16)
                                                            // The TPM driver returned an error.
                                                            // The upper 16 bits contain the actual error code returned by the driver
#define  TCG_PC_LOGOVERFLOW          (TCG_PC_OK + 0x02)     // There is insufficient memory to create the log entry.
#define  TCG_PC_UNSUPPORTED          (TCG_PC_OK + 0x03)     // The requested function is not supported.
#define  TCG_PC_INVALID_PARAM        (TCG_PC_OK + 0x04)     // An invalid parameter was passed.

#define  TCG_DRIVER_ERROR(x)         (TCG_PC_TPMERROR | ((x) << 16))

#pragma pack(1)

typedef struct {
  UINT32 PCRIndex;
  UINT32 EventType;
  UINT8  Digest[20];
  UINT32 EventDataSize;
  UINT8  Event[1];
} TCG_PC_CLIENT_PCR_EVENT;

typedef struct {
  UINT16 IPBLength;
  UINT16 Reserved;
  UINT32 HashDataPtr;
  UINT32 HashDataLen;
  UINT32 AlgorithmID;
} IPB_HASH_ALL;

typedef struct {
  UINT16 IPBLength;
  UINT16 Reserved;
  UINT32 HashDataPtr;
  UINT32 HashDataLen;
  UINT32 PCRIndex;
  UINT32 LogEventType;
  UINT32 LogDataPtr; // TCG_PC_CLIENT_PCR_EVENT pointer
  UINT32 LogDataLen;
} IPB_HASH_LOG_EVENT;

typedef struct {
  UINT16 OPBLength;
  UINT16 Reserved;
  UINT32 EventNumber;
} OPB_HASH_LOG_EVENT;

// Input parameter block definition for TCG Pass Thru To TPM function
typedef struct {
  UINT16 IPBLength;
  UINT16 Reserved;
  UINT16 OPBLength;
  UINT16 Reserved2;
  UINT8 TPMOperandIn;
} IPB_PASS_THRU;

//
// Input Parameter Block Definition for TCG_HashLogExtendEvent func
//
typedef struct {
  UINT32 Reserved;
  UINT32 LogDataPtr; // TCG_PC_CLIENT_PCR_EVENT pointer
  UINT32 LogDataLen;
} LONG_LOG;

typedef struct {
  UINT32 LogDataPtr;  //TCG_PC_CLIENT_PCR_EVENT pointer
  UINT32 LogDataLen;
} SHORT_LOG;

union LogDataUnion {
  LONG_LOG  LongLog;
  SHORT_LOG ShortLog;
};

typedef struct {
  UINT16 IPBLength;
  UINT16 Reserved;
  UINT32 HashDataPtr;
  UINT32 HashDataLen;
  UINT32 PCRIndex;
  union LogDataUnion Log;
} IPB_HASH_LOG_EXTEND_EVENT;

// Output parameter block definition for TCG Pass Thru To TPM function
typedef struct {
  UINT16 OPBLength;
  UINT16 Reserved;
  UINT8 TPMOperandOut;
} OPB_PASS_THRU;

//
// Output Parameter Block Definition for TCG_HashLogExtendEvent func
//
typedef struct {
  UINT16 OPBLength;
  UINT16 Reserved;
  UINT32 EventNumber;
  UINT8  HashValue[20];
} OPB_HASH_LOG_EXTEND_EVENT;

typedef struct {
  UINT16 IPBLength;
  UINT16 Reserved;
  UINT8  MORBitValue;
} IPB_MOR;

#pragma pack()

#endif // _TCG_SMM_H_
