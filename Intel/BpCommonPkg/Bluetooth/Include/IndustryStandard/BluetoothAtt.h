//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Definitions for Bluetooth ATT.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __BLUETOOTH_ATT_H__
#define __BLUETOOTH_ATT_H__

#pragma pack(1)

//
// Attribute Protocol
//

//
// SDP data element type descriptor: Type(5bits) + SizeIndex(3bits)
//
typedef enum {
  BluetoothAttOpErrorResponse = 0x01,
  BluetoothAttOpExchangeMTURequest = 0x02,
  BluetoothAttOpExchangeMTUResponse = 0x03,
  BluetoothAttOpFindInformationRequest = 0x04,
  BluetoothAttOpFindInformationResponse = 0x05,
  BluetoothAttOpFindByTypeValueRequest = 0x06,
  BluetoothAttOpFindByTypeValueResponse = 0x07,
  BluetoothAttOpReadByTypeRequest = 0x08,
  BluetoothAttOpReadByTypeResponse = 0x09,
  BluetoothAttOpReadRequest = 0x0A,
  BluetoothAttOpReadResponse = 0x0B,
  BluetoothAttOpReadBlobRequest = 0x0C,
  BluetoothAttOpReadBlobResponse = 0x0D,
  BluetoothAttOpReadMultipleRequest = 0x0E,
  BluetoothAttOpReadMultipleResponse = 0x0F,
  BluetoothAttOpReadByGroupTypeRequest = 0x10,
  BluetoothAttOpReadByGroupTypeResponse = 0x11,
  BluetoothAttOpWriteRequest = 0x12,
  BluetoothAttOpWriteResponse = 0x13,
  BluetoothAttOpWriteCommand = 0x52,
  BluetoothAttOpSignedWriteCommand= 0xD2,
  BluetoothAttOpPrepareWriteRequest = 0x16,
  BluetoothAttOpPrepareWriteResponse = 0x17,
  BluetoothAttOpExecuteWriteRequest = 0x18,
  BluetoothAttOpExecuteWriteResponse = 0x19,
  BluetoothAttOpHandleValueNotification = 0x1B,
  BluetoothAttOpHandleValueIndication = 0x1D,
  BluetoothAttOpHandleValueConfirmation = 0x1E,
  BluetoothAttOp,
} BLUETOOTH_ATT_OPCODE;

typedef struct {
  UINT8             Opcode;
  UINT8             RequestOpcodeInError;
  UINT16            AttributeHandleInError;
  UINT8             ErrorCode;
} BLUETOOTH_ATT_ERROR_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            ClientRxMTU;
} BLUETOOTH_ATT_EXCHANGE_MTU_REQUEST;

typedef struct {
  UINT8             Opcode;
  UINT16            ServerRxMTU;
} BLUETOOTH_ATT_EXCHANGE_MTU_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            StartingHandle;
  UINT16            EndingHandle;
} BLUETOOTH_ATT_FIND_INFORMATION_REQUEST;

typedef struct {
  UINT8             Opcode;
  UINT8             Format;
//union {
//  BLUETOOTH_ATT_INFORMATION_HANDLE_UUID16   InformationData[];
//  BLUETOOTH_ATT_INFORMATION_HANDLE_UUID128  InformationData[];
//}
} BLUETOOTH_ATT_FIND_INFORMATION_RESPONSE;

typedef enum {
  BluetoothAttInformationFormatHandleUuid16 = 0x01,
  BluetoothAttInformationFormatHandleUuid128 = 0x02,
} BLUETOOTH_ATT_INFORMATION_FORMAT;

typedef struct {
  UINT16            Handle;
  UINT16            Uuid16;
} BLUETOOTH_ATT_INFORMATION_HANDLE_UUID16;

typedef struct {
  UINT16            Handle;
  UINT8             Uuid128[16];
} BLUETOOTH_ATT_INFORMATION_HANDLE_UUID128;

typedef struct {
  UINT8             Opcode;
  UINT16            StartingHandle;
  UINT16            EndingHandle;
  UINT16            AttributeType;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_FIND_BY_TYPE_VALUE_REQUEST;

typedef struct {
  UINT8             Opcode;
//BLUETOOTH_ATT_HANDLES_INFORMATION  HandlesInformationList[];
} BLUETOOTH_ATT_FIND_BY_TYPE_VALUE_RESPONSE;

typedef struct {
  UINT16            FoundAttributeHandle;
  UINT16            GroupEndHandle;
} BLUETOOTH_ATT_HANDLES_INFORMATION;

typedef struct {
  UINT8             Opcode;
  UINT16            StartingHandle;
  UINT16            EndingHandle;
  UINT8             AttributeType[16]; // 16 octet or 2 octet
} BLUETOOTH_ATT_READ_BY_TYPE_REQUEST;

typedef struct {
  UINT8             Opcode;
  UINT8             Legnth;
//BLUETOOTH_ATT_ATTRIBUTE_DATA  AttributeDataList[];
} BLUETOOTH_ATT_READ_BY_TYPE_RESPONSE;

typedef struct {
  UINT16            AttributeHandle;
//UINT8             AttributeValue[Legnth - 2];
} BLUETOOTH_ATT_ATTRIBUTE_DATA;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
} BLUETOOTH_ATT_READ_REQUEST;

typedef struct {
  UINT8             Opcode;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_READ_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
  UINT16            ValueOffset;
} BLUETOOTH_ATT_READ_BLOB_REQUEST;

typedef struct {
  UINT8             Opcode;
//UINT8             PartAttributeValue[];
} BLUETOOTH_ATT_READ_BLOB_RESPONSE;

typedef struct {
  UINT8             Opcode;
//UINT8             SetOfHandles[];
} BLUETOOTH_ATT_READ_MULTIPLE_REQUEST;

typedef struct {
  UINT8             Opcode;
//UINT8             SetOfValues[];
} BLUETOOTH_ATT_READ_MULTIPLE_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            StartingHandle;
  UINT16            EndingHandle;
  UINT8             AttributeGroupType[16]; // 16 octet or 2 octet
} BLUETOOTH_ATT_READ_BY_GROUP_TYPE_REQUEST;

typedef struct {
  UINT8             Opcode;
  UINT8             Length;
//BLUETOOTH_ATT_ATTRIBUTE_GROUP_DATA  AttributeDataList[];
} BLUETOOTH_ATT_READ_BY_GROUP_TYPE_RESPONSE;

typedef struct {
  UINT16            AttributeHandle;
  UINT16            EndGroupHandle;
//UINT8             AttributeValue[Legnth - 4];
} BLUETOOTH_ATT_ATTRIBUTE_GROUP_DATA;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_WRITE_REQUEST;

typedef struct {
  UINT8             Opcode;
} BLUETOOTH_ATT_WRITE_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_WRITE_COMMAND;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
//UINT8             AttributeValue[];
//UINT8             AuthenticationSignature[12];
} BLUETOOTH_ATT_SIGNED_WRITE_COMMAND;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
  UINT16            ValueOffset;
//UINT8             PartAttributeValue[];
} BLUETOOTH_ATT_PREPARE_WRITE_REQUEST;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
  UINT16            ValueOffset;
//UINT8             PartAttributeValue[];
} BLUETOOTH_ATT_PREPARE_WRITE_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT8             Flags;
} BLUETOOTH_ATT_EXECUTE_WRITE_REQUEST;

typedef enum {
  BluetoothAttExecuteWriteRequestFlagsCancel = 0x00,
  BluetoothAttExecuteWriteRequestFlagsImmediatelyWrite = 0x01,
} BLUETOOTH_ATT_EXECUTE_WRITE_REQUEST_FLAGS;

typedef struct {
  UINT8             Opcode;
} BLUETOOTH_ATT_EXECUTE_WRITE_RESPONSE;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_HANDLE_VALUE_NOTIFICATION;

typedef struct {
  UINT8             Opcode;
  UINT16            AttributeHandle;
//UINT8             AttributeValue[];
} BLUETOOTH_ATT_HANDLE_VALUE_INDICACATION;

typedef struct {
  UINT8             Opcode;
} BLUETOOTH_ATT_HANDLE_VALUE_CONFIRMATION;

#pragma pack()

#endif
