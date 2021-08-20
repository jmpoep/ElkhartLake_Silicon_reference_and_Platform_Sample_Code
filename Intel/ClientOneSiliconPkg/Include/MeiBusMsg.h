/** @file
  Definitions for MEI Bus message support

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _MEI_BUS_MSG_H_
#define _MEI_BUS_MSG_H_

#define HBM_MINOR_VERSION                           0
#define HBM_MAJOR_VERSION                           1

#define HOST_VERSION_REQUEST            0x01
#define HOST_STOP_REQUEST               0x02
#define HOST_ENUMERATE_REQUEST          0x04
#define HOST_CLIENT_PROPERTIES_REQUEST  0x05
#define CLIENT_CONNECT_REQUEST          0x06
#define CLIENT_DISCONNECT_REQUEST       0x07
#define FLOW_CONTROL                    0x08
#define HECI_BUS_DISABLE_OPCODE         0x0C

#pragma pack(1)

typedef union {
  UINT8 Data;
  struct {
    UINT8 Command    : 7;
    UINT8 IsResponse : 1;
  } Fields;
} HBM_COMMAND;

typedef struct {
  UINT8 MinorVersion;
  UINT8 MajorVersion;
} HBM_VERSION;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reserved;
  HBM_VERSION HostVersion;
} HBM_HOST_VERSION_REQUEST;

typedef struct {
  HBM_COMMAND Command;
  UINT8       HostVersionSupported;
  HBM_VERSION MeMaxVersion;
} HBM_HOST_VERSION_RESPONSE;

typedef union {
  HBM_HOST_VERSION_REQUEST  Request;
  HBM_HOST_VERSION_RESPONSE Response;
} HBM_HOST_VERSION_BUFFER;

#define STOP_REASON_REQUEST_FROM_DRIVER  0x00

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reason;
  UINT8       Reserved[2];
} HBM_HOST_STOP_REQUEST;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reserved[3];
} HBM_HOST_STOP_RESPONSE;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reserved[3];
} HBM_HOST_ENUMERATION_REQUEST;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reserved[3];
  UINT8       ValidAddresses[32];
} HBM_HOST_ENUMERATION_RESPONSE;

typedef union {
  HBM_HOST_ENUMERATION_REQUEST  Request;
  HBM_HOST_ENUMERATION_RESPONSE Response;
} HBM_HOST_ENUMERATION_BUFFER;

#define NUMBER_OF_VALID_ADDRESS_BITS 32*8

typedef struct {
  HBM_COMMAND Command;
  UINT8       Address;
  UINT8       Reserved[2];
} HBM_HOST_CLIENT_PROPERTIES_REQUEST;

typedef struct {
  EFI_GUID ProtocolName;
  UINT8    ProtocolVersion;
  UINT8    MaxNumberOfConnections;
  UINT8    FixedAddress;
  UINT8    SingleReceiveBuffer;
  UINT32   MaxMessageLength;
  UINT32   Reserved;
} HECI_CLIENT_PROPERTIES;

typedef struct {
  HBM_COMMAND            Command;
  UINT8                  Address;
  UINT8                  Status;
  UINT8                  Reserved;
  HECI_CLIENT_PROPERTIES ClientProperties;
} HBM_HOST_CLIENT_PROPERTIES_RESPONSE;

typedef union {
  HBM_HOST_CLIENT_PROPERTIES_REQUEST  Request;
  HBM_HOST_CLIENT_PROPERTIES_RESPONSE Response;
} HBM_HOST_CLIENT_PROPERTIES_BUFFER;

typedef struct {
  HBM_COMMAND Command;
  UINT8       MeAddress;
  UINT8       HostAddress;
  UINT8       Reserved;
} HBM_CLIENT_CONNECT_REQUEST;

typedef struct {
  HBM_COMMAND Command;
  UINT8       MeAddress;
  UINT8       HostAddress;
  UINT8       Status;
} HBM_CLIENT_CONNECT_RESPONSE;

typedef union {
  HBM_CLIENT_CONNECT_REQUEST  Request;
  HBM_CLIENT_CONNECT_RESPONSE Response;
} HBM_CLIENT_CONNECT_BUFFER;

typedef struct {
  HBM_COMMAND Command;
  UINT8       MeAddress;
  UINT8       HostAddress;
  UINT8       Reserved;
} HBM_CLIENT_DISCONNECT_REQUEST;

typedef struct {
  HBM_COMMAND Command;
  UINT8       MeAddress;
  UINT8       HostAddress;
  UINT8       Status;
} HBM_CLIENT_DISCONNECT_RESPONSE;

typedef union {
  HBM_CLIENT_DISCONNECT_REQUEST  Request;
  HBM_CLIENT_DISCONNECT_RESPONSE Response;
} HBM_CLIENT_DISCONNECT_BUFFER;

typedef struct {
  HBM_COMMAND Command;
  UINT8       MeAddress;
  UINT8       HostAddress;
  UINT8       Reserved[5];
} HBM_FLOW_CONTROL;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Reserved[3];
} HECI_BUS_DISABLE_CMD;

typedef struct {
  HBM_COMMAND Command;
  UINT8       Status;
  UINT8       Reserved[2];
} HECI_BUS_DISABLE_CMD_ACK;

#pragma pack()

#endif // _MEI_BUS_MSG_H_

