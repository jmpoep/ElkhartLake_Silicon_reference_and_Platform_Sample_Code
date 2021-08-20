/** @file
 TCG defined values and structures used by the Tcg Core library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

#ifndef _TCG_H_
#define _TCG_H_

#include <Base.h>
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4200) // zero-sized array
#pragma warning(disable: 4201) // nameless struct/union
#pragma warning(disable: 4214) // bit field types other than int
#endif

#pragma pack(push, 1)

/// UID in host native byte order
typedef UINT64 TcgUid;

#define TCG_UID(b0, b1, b2, b3, b4, b5, b6, b7) (TcgUid)( \
    (UINT64)(b0)         | \
    ((UINT64)(b1) << 8)  | \
    ((UINT64)(b2) << 16) | \
    ((UINT64)(b3) << 24) | \
    ((UINT64)(b4) << 32) | \
    ((UINT64)(b5) << 40) | \
    ((UINT64)(b6) << 48) | \
    ((UINT64)(b7) << 56))

typedef struct _TcgComPacket {
    UINT32     Reserved_BE;
    UINT16     ComID_BE;
    UINT16     ComIDExtension_BE;
    UINT32     OutstandingData_BE;
    UINT32     MinTransfer_BE;
    UINT32     Length_BE;
    UINT8      Payload[ 0 ];
} TcgComPacket;
C_ASSERT(sizeof(TcgComPacket) == 20);

typedef struct _TcgPacket {
    UINT32     TperSessionNumber_BE;
    UINT32     HostSessionNumber_BE;
    UINT32     SequenceNumber_BE;
    UINT16     Reserved_BE;
    UINT16     AckType_BE;
    UINT32     Acknowledgement_BE;
    UINT32     Length_BE;
    UINT8      Payload[ 0 ];
} TcgPacket;
C_ASSERT(sizeof(TcgPacket) == 24);

#define TCG_SUBPACKET_ALIGNMENT 4 // 4-byte alignment per spec
//TODO CP_Assert power of 2

typedef struct _TcgSubPacket {
    UINT8      Reserved_BE[ 6 ];
    UINT16     Kind_BE;
    UINT32     Length_BE;
    UINT8      Payload[ 0 ];
} TcgSubPacket;
C_ASSERT(sizeof(TcgSubPacket) == 12);

#define SUBPACKET_KIND_DATA 0x0000
#define SUBPACKET_KIND_CREDIT_CONTROL 0x8001

#define TCG_ATOM_TYPE_INTEGER 0x0
#define TCG_ATOM_TYPE_BYTE 0x1

typedef struct _TcgSimpleTokenTinyAtom {
    union {
        UINT8 raw;
        struct {
            UINT8   data : 6;
            UINT8   sign : 1;
            UINT8   isZero : 1;
        };
    };
} TcgSimpleTokenTinyAtom;
C_ASSERT(sizeof(TcgSimpleTokenTinyAtom) == 1);

typedef struct _TcgSimpleTokenShortAtom {
    union {
        UINT8 rawHeader;
        struct {
            UINT8   length : 4;
            UINT8   signOrCont : 1;
            UINT8   byteOrInt : 1;
            UINT8   isZero : 1;
            UINT8   isOne : 1;
        };
    };
} TcgSimpleTokenShortAtom;
C_ASSERT(sizeof(TcgSimpleTokenShortAtom) == 1);

#define TCG_MEDIUM_ATOM_LENGTH_HIGH_SHIFT 8
#define TCG_MEDIUM_ATOM_LENGTH_HIGH_MASK  0x7

typedef struct _TcgSimpleTokenMediumAtom {
    union {
        UINT16 rawHeader;
        struct {
            UINT8  lengthHigh : 3;
            UINT8  signOrCont : 1;
            UINT8  byteOrInt : 1;
            UINT8  isZero : 1;
            UINT8  isOne1 : 1;
            UINT8  isOne2 : 1;
            UINT8  lengthLow;
        };
    };
} TcgSimpleTokenMediumAtom;
C_ASSERT(sizeof(TcgSimpleTokenMediumAtom) == 2);

#define TCG_LONG_ATOM_LENGTH_HIGH_SHIFT 16
#define TCG_LONG_ATOM_LENGTH_MID_SHIFT 8

typedef struct _TcgSimpleTokenLongAtom {
    union {
        UINT32 rawHeader;
        struct {
            UINT8   signOrCont : 1;
            UINT8   byteOrInt : 1;
            UINT8   reserved : 2;
            UINT8   isZero : 1;
            UINT8   isOne1 : 1;
            UINT8   isOne2 : 1;
            UINT8   isOne3 : 1;
            UINT8   lengthHigh;
            UINT8   lengthMid;
            UINT8   lengthLow;
        };
    };
} TcgSimpleTokenLongAtom;
C_ASSERT(sizeof(TcgSimpleTokenLongAtom) == 4);

// TCG Core Spec v2 - Table 04 - Token Types
typedef enum _TcgTokenType {
    TcgTokenType_Reserved,
    TcgTokenType_TinyAtom,
    TcgTokenType_ShortAtom,
    TcgTokenType_MediumAtom,
    TcgTokenType_LongAtom,
    TcgTokenType_StartList,
    TcgTokenType_EndList,
    TcgTokenType_StartName,
    TcgTokenType_EndName,
    TcgTokenType_Call,
    TcgTokenType_EndOfData,
    TcgTokenType_EndOfSession,
    TcgTokenType_StartTransaction,
    TcgTokenType_EndTransaction,
    TcgTokenType_EmptyAtom,
} TcgTokenType;

#pragma pack(pop)

#define TCG_TOKEN_SHORTATOM_MAX_BYTE_SIZE   0x0F
#define TCG_TOKEN_SHORTATOM_MAX_BYTE_SIZE   0x0F
#define TCG_TOKEN_MEDIUMATOM_MAX_BYTE_SIZE  0x7FF
#define TCG_TOKEN_LONGATOM_MAX_BYTE_SIZE    0xFFFFFF

#define TCG_TOKEN_TINYATOM_UNSIGNED_MAX_VALUE 0x3F
#define TCG_TOKEN_TINYATOM_SIGNED_MAX_VALUE 0x1F
#define TCG_TOKEN_TINYATOM_SIGNED_MIN_VALUE -32

// TOKEN TYPES
#define TCG_TOKEN_TINYATOM          0x00
#define TCG_TOKEN_TINYSIGNEDATOM    0x40
#define TCG_TOKEN_SHORTATOM         0x80
#define TCG_TOKEN_SHORTSIGNEDATOM   0x90
#define TCG_TOKEN_SHORTBYTESATOM    0xA0
#define TCG_TOKEN_MEDIUMATOM        0xC0
#define TCG_TOKEN_MEDIUMSIGNEDATOM  0xC8
#define TCG_TOKEN_MEDIUMBYTESATOM   0xD0
#define TCG_TOKEN_LONGATOM          0xE0
#define TCG_TOKEN_LONGSIGNEDATOM    0xE1
#define TCG_TOKEN_LONGBYTESATOM     0xE2
#define TCG_TOKEN_STARTLIST         0xF0
#define TCG_TOKEN_ENDLIST           0xF1
#define TCG_TOKEN_STARTNAME         0xF2
#define TCG_TOKEN_ENDNAME           0xF3
// 0xF4 - 0xF7 TCG Reserved
#define TCG_TOKEN_CALL              0xF8
#define TCG_TOKEN_ENDDATA           0xF9
#define TCG_TOKEN_ENDSESSION        0xFA
#define TCG_TOKEN_STARTTRANSACTION  0xFB
#define TCG_TOKEN_ENDTRANSACTION    0xFC
// 0xFD - 0xFE TCG Reserved
#define TCG_TOKEN_EMPTY             0xFF

// CELLBLOCK reserved Names
#define TCG_CELL_BLOCK_TABLE_NAME           (UINT8)0x00
#define TCG_CELL_BLOCK_START_ROW_NAME       (UINT8)0x01
#define TCG_CELL_BLOCK_END_ROW_NAME         (UINT8)0x02
#define TCG_CELL_BLOCK_START_COLUMN_NAME    (UINT8)0x03
#define TCG_CELL_BLOCK_END_COLUMN_NAME      (UINT8)0x04

// METHOD STATUS CODES
#define TCG_METHOD_STATUS_CODE_SUCCESS                  0x00
#define TCG_METHOD_STATUS_CODE_NOT_AUTHORIZED           0x01
#define TCG_METHOD_STATUS_CODE_OBSOLETE                 0x02
#define TCG_METHOD_STATUS_CODE_SP_BUSY                  0x03
#define TCG_METHOD_STATUS_CODE_SP_FAILED                0x04
#define TCG_METHOD_STATUS_CODE_SP_DISABLED              0x05
#define TCG_METHOD_STATUS_CODE_SP_FROZEN                0x06
#define TCG_METHOD_STATUS_CODE_NO_SESSIONS_AVAILABLE    0x07
#define TCG_METHOD_STATUS_CODE_UNIQUENESS_CONFLICT      0x08
#define TCG_METHOD_STATUS_CODE_INSUFFICIENT_SPACE       0x09
#define TCG_METHOD_STATUS_CODE_INSUFFICIENT_ROWS        0x0A
#define TCG_METHOD_STATUS_CODE_INVALID_PARAMETER        0x0C
#define TCG_METHOD_STATUS_CODE_OBSOLETE2                0x0D
#define TCG_METHOD_STATUS_CODE_OBSOLETE3                0x0E
#define TCG_METHOD_STATUS_CODE_TPER_MALFUNCTION         0x0F
#define TCG_METHOD_STATUS_CODE_TRANSACTION_FAILURE      0x10
#define TCG_METHOD_STATUS_CODE_RESPONSE_OVERFLOW        0x11
#define TCG_METHOD_STATUS_CODE_AUTHORITY_LOCKED_OUT     0x12
#define TCG_METHOD_STATUS_CODE_FAIL                     0x3F


// Feature Codes
#define TCG_FEATURE_INVALID             (UINT16)0x0000
#define TCG_FEATURE_TPER                (UINT16)0x0001
#define TCG_FEATURE_LOCKING             (UINT16)0x0002
#define TCG_FEATURE_GEOMETRY_REPORTING  (UINT16)0x0003
#define TCG_FEATURE_SINGLE_USER_MODE    (UINT16)0x0201
#define TCG_FEATURE_DATASTORE_TABLE     (UINT16)0x0202
#define TCG_FEATURE_OPAL_SSC_V1_0_0     (UINT16)0x0200
#define TCG_FEATURE_OPAL_SSC_V2_0_0     (UINT16)0x0203
#define TCG_FEATURE_OPAL_SSC_LITE       (UINT16)0x0301
#define TCG_FEATURE_PYRITE_SSC          (UINT16)0x0302

// ACE Expression values
#define TCG_ACE_EXPRESSION_AND 0x0
#define TCG_ACE_EXPRESSION_OR 0x1

/****************************************************************************
TRUSTED RECEIVE - supported security protocols list (SP_Specific = 0000h)
ATA 8 Rev6a Table 68 7.57.6.2
****************************************************************************/
// Security Protocol IDs
#define SECURITY_PROTOCOL_INFO                   0x00
#define OPAL_SECURITY_PROTOCOL_1                 0x01
#define OPAL_SECURITY_PROTOCOL_2                 0x02
#define SECURITY_PROTOCOL_TCG3                   0x03
#define SECURITY_PROTOCOL_TCG4                   0x04
#define SECURITY_PROTOCOL_TCG5                   0x05
#define SECURITY_PROTOCOL_TCG6                   0x06
#define SECURITY_PROTOCOL_CBCS                   0x07
#define SECURITY_PROTOCOL_TAPE_DATA              0x20
#define SECURITY_PROTOCOL_DATA_ENCRYPT_CONFIG    0x21
#define SECURITY_PROTOCOL_SA_CREATION_CAPS       0x40
#define SECURITY_PROTOCOL_IKEV2_SCSI             0x41
#define SECURITY_PROTOCOL_JEDEC_UFS              0xEC
#define SECURITY_PROTOCOL_SDCARD_SECURITY        0xED
#define SECURITY_PROTOCOL_IEEE_1667              0xEE
#define SECURITY_PROTOCOL_ATA_DEVICE_SERVER_PASS 0xEF

// Security Protocol Specific IDs
#define TCG_SP_SPECIFIC_PROTOCOL_LIST               0x0000
#define TCG_SP_SPECIFIC_PROTOCOL_LEVEL0_DISCOVERY   0x0001

#define TCG_RESERVED_COMID 0x0000

#pragma pack(push, 1)
typedef struct _TCG_SUPPORTED_SECURITY_PROTOCOLS {
    UINT8   reserved[6];
    UINT16  listLength_BE;  // 6 - 7
    UINT8   list[504];      // 8...
} TCG_SUPPORTED_SECURITY_PROTOCOLS;
C_ASSERT(sizeof(TCG_SUPPORTED_SECURITY_PROTOCOLS) == 512);

// Level 0 Discovery
typedef struct _TCG_LEVEL0_DISCOVERY_HEADER {
    UINT32 length_BE;    // number of valid bytes in discovery response, not including length field
    UINT16 verMajor_BE;
    UINT16 verMinor_BE;
    UINT8  reserved[8];
    UINT8  vendorUnique[32];
} TCG_LEVEL0_DISCOVERY_HEADER;
C_ASSERT(sizeof(TCG_LEVEL0_DISCOVERY_HEADER) == 48);

typedef struct _TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER {
    UINT16 featureCode_BE;
    UINT8  reserved : 4;
    UINT8  version : 4;
    UINT8  length;     // length of feature dependent data in bytes
} TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER;
C_ASSERT(sizeof(TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER) == 4);

typedef struct _TCG_LOCKING_FEATURE_DESCRIPTOR {
    TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER header;
    UINT8 lockingSupported : 1;
    UINT8 lockingEnabled : 1;   // means the locking security provider (SP) is enabled
    UINT8 locked : 1;   // means at least 1 locking range is enabled
    UINT8 mediaEncryption : 1;
    UINT8 mbrEnabled : 1;
    UINT8 mbrDone : 1;
    UINT8 reserved : 2;
    UINT8 reserved5_15[11];
} TCG_LOCKING_FEATURE_DESCRIPTOR;
C_ASSERT(sizeof(TCG_LOCKING_FEATURE_DESCRIPTOR) == 16);

typedef struct _TCG_TPER_FEATURE_DESCRIPTOR {
    TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER header;
    UINT8 SyncSupported : 1;
    UINT8 AsyncSupported : 1;
    UINT8 AckNakSupported : 1;
    UINT8 BufferMgmtSupported : 1;
    UINT8 StreamingSupported : 1;
    UINT8 Reserved4b5 : 1;
    UINT8 ComIdMgmtSupported : 1;
    UINT8 Reserved4b7 : 1;
    UINT8 Reserved5_15[11];
} TCG_TPER_FEATURE_DESCRIPTOR;
C_ASSERT(sizeof(TCG_TPER_FEATURE_DESCRIPTOR) == 16);

#pragma pack(pop)


// Special Purpose UIDs
#define TCG_UID_NULL                            TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
#define TCG_UID_THIS_SP                         TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01)
#define TCG_UID_SMUID                           TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF)

// Session Manager Method UIDS
#define TCG_UID_SM_PROPERTIES                   TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01)
#define TCG_UID_SM_START_SESSION                TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x02)
#define TCG_UID_SM_SYNC_SESSION                 TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03)
#define TCG_UID_SM_START_TRUSTED_SESSION        TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x04)
#define TCG_UID_SM_SYNC_TRUSTED_SESSION         TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x05)
#define TCG_UID_SM_CLOSE_SESSION                TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x06)

// MethodID UIDs
#define TCG_UID_METHOD_DELETE_SP                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01)
#define TCG_UID_METHOD_CREATE_TABLE             TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02)
#define TCG_UID_METHOD_DELETE                   TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x03)
#define TCG_UID_METHOD_CREATE_ROW               TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04)
#define TCG_UID_METHOD_DELETE_ROW               TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05)
#define TCG_UID_METHOD_NEXT                     TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08)
#define TCG_UID_METHOD_GET_FREE_SPACE           TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09)
#define TCG_UID_METHOD_GET_FREE_ROWS            TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0A)
#define TCG_UID_METHOD_DELETE_METHOD            TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0B)
#define TCG_UID_METHOD_GET_ACL                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0D)
#define TCG_UID_METHOD_ADD_ACE                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0E)
#define TCG_UID_METHOD_REMOVE_ACE               TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0F)
#define TCG_UID_METHOD_GEN_KEY                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10)
#define TCG_UID_METHOD_GET_PACKAGE              TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x12)
#define TCG_UID_METHOD_SET_PACKAGE              TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x13)
#define TCG_UID_METHOD_GET                      TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16)
#define TCG_UID_METHOD_SET                      TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x17)
#define TCG_UID_METHOD_AUTHENTICATE             TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1C)
#define TCG_UID_METHOD_ISSUE_SP                 TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x01)
#define TCG_UID_METHOD_GET_CLOCK                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x01)
#define TCG_UID_METHOD_RESET_CLOCK              TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x02)
#define TCG_UID_METHOD_SET_CLOCK_HIGH           TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x03)
#define TCG_UID_METHOD_SET_LAG_HIGH             TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x04)
#define TCG_UID_METHOD_SET_CLOCK_LOW            TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x05)
#define TCG_UID_METHOD_SET_LAG_LOW              TCG_UID(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x06)
#define TCG_UID_METHOD_INCREMENT_COUNTER        TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x07)
#define TCG_UID_METHOD_RANDOM                   TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x01)
#define TCG_UID_METHOD_SALT                     TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x02)
#define TCG_UID_METHOD_DECRYPT_INIT             TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x03)
#define TCG_UID_METHOD_DECRYPT                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x04)
#define TCG_UID_METHOD_DECRYPT_FINALIZE         TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x05)
#define TCG_UID_METHOD_ENCRYPT_INIT             TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x06)
#define TCG_UID_METHOD_ENCRYPT                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x07)
#define TCG_UID_METHOD_ENCRYPT_FINALIZE         TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x08)
#define TCG_UID_METHOD_HMAC_INIT                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x09)
#define TCG_UID_METHOD_HMAC                     TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0A)
#define TCG_UID_METHOD_HMAC_FINALIZE            TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0B)
#define TCG_UID_METHOD_HASH_INIT                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0C)
#define TCG_UID_METHOD_HASH                     TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0D)
#define TCG_UID_METHOD_HASH_FINALIZE            TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0E)
#define TCG_UID_METHOD_SIGN                     TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x0F)
#define TCG_UID_METHOD_VERIFY                   TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x10)
#define TCG_UID_METHOD_XOR                      TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x11)
#define TCG_UID_METHOD_ADD_LOG                  TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0A, 0x01)
#define TCG_UID_METHOD_CREATE_LOG               TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0A, 0x02)
#define TCG_UID_METHOD_CLEAR_LOG                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0A, 0x03)
#define TCG_UID_METHOD_FLUSH_LOG                TCG_UID(0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0A, 0x04)

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef __cplusplus
}
#endif

#endif // TCG_H_
