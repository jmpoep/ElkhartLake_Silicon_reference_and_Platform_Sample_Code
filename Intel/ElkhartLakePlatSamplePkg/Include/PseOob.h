/** @file
Defines Pse Oob offsets used by Oob driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

#ifndef _PSE_OOB_FEATURE_H_
#define _PSE_OOB_FEATURE_H_

#include <Pi/PiHob.h>

// OOB Header Revision
#define OOB_HEADER_REVISION   1
#define OOB_PROTOCOL_VERSION  2
#define OOB_HEADER_SIZE       4
#define HECI_HEADER_SIZE      4

// Oob region commands

// Read command: This command is issued from bios to Oob driver to initiate the Batch read operation from PSE to Oob opregion
// Write command: This command is issued from bios to Oob driver to initiate the Batch write operation from Oob opregion to PSE
#define OOB_READ_COMMAND    1
#define OOB_WRITE_COMMAND   2
#define OOB_MAX_COMMAND     255

// Size definition

#define  OOB_BYTES_COUNT_0   0
#define  OOB_BYTES_COUNT_1   1
#define  OOB_BYTES_COUNT_2   2
#define  OOB_BYTES_COUNT_3   3
#define  OOB_BYTES_COUNT_4   4
#define  OOB_BYTES_COUNT_5   5
#define  OOB_BYTES_COUNT_6   6
#define  OOB_BYTES_COUNT_7   7
#define  OOB_BYTES_COUNT_8   8
#define  OOB_BYTES_COUNT_9   9
#define  OOB_BYTES_COUNT_10  10
#define  OOB_BYTES_COUNT_11  11
#define  OOB_BYTES_COUNT_12  12
#define  OOB_BYTES_COUNT_13  13
#define  OOB_BYTES_COUNT_14  14
#define  OOB_BYTES_COUNT_15  15
#define  OOB_BYTES_COUNT_16  16
#define  OOB_BYTES_COUNT_17  17
#define  OOB_BYTES_COUNT_18  18
#define  OOB_BYTES_COUNT_19  19
#define  OOB_BYTES_COUNT_20  20
#define  OOB_BYTES_COUNT_21  21
#define  OOB_BYTES_COUNT_22  22
#define  OOB_BYTES_COUNT_23  23
#define  OOB_BYTES_COUNT_24  24
#define  OOB_BYTES_COUNT_25  25
#define  OOB_BYTES_COUNT_26  26
#define  OOB_BYTES_COUNT_27  27
#define  OOB_BYTES_COUNT_28  28
#define  OOB_BYTES_COUNT_29  29
#define  OOB_BYTES_COUNT_30  30
#define  OOB_BYTES_COUNT_31  31
#define  OOB_BYTES_COUNT_32  32
#define  OOB_BYTES_COUNT_256 256
#define  OOB_MAX_BYTES_SUPPORTED 384

#define  OOB_DEFAULT_UPDATE     000 // PSE Firmware Ignores the Command completion notfication if it is 0
#define  OOB_DEFAULT_OFFSET     0   // 000: Default
#define  MAX_HECI_PACKAGE       4096
#define  MAX_HECI_BUF_SIZE      MAX_HECI_PACKAGE - (OOB_HEADER_SIZE + HECI_HEADER_SIZE)

// Get FW version
#pragma pack(1)

#define ISH_SET_FILE_CMD  0x1

#define PDT_UNLOCK_DATA_DATA_TYPE     0x1
#define PDT_UNLOCK_DATA_PAYLOAD_SIZE  0x0
#define PDT_UPDATE_DATA_DATA_TYPE     0x2

#define PSE_GET_VERSION 1

//Message Header
typedef struct
{
  UINT8  Command      : 7;
  UINT8  IsResponse   : 1;
  UINT16 HasNext      : 1;
  UINT16 Reserved     : 15;
  UINT8  Status;
} SMHI_MSG_HEADER;

typedef struct
{
  UINT16             Major;
  UINT16             Minor;
  UINT16             Hotfix;
  UINT16             Build;
} PSE_VERSION;

typedef struct
{
  SMHI_MSG_HEADER   Header;
  PSE_VERSION       Version;
} SMHI_GET_VERSION_RES;

typedef enum{
  /* BIOS_OOB Commands */
  BIOS_OOB_OOB                    = 0x0,
  BIOS_OOB_BIOS                   = 0x1
} BIOS_OOB_SOURCE;

typedef enum{
  /* BIOS_OOB Commands */
  BIOS_OOB_MSG_INCOM              = 0x0,
  BIOS_OOB_MSG_COM                = 0x1
} BIOS_OOB_MESSAGE_COMPLETE;

typedef enum{
  /* BIOS_OOB Commands */
  BIOS_OOB_PROV_INIT_OOB          = 0x00,
  BIOS_OOB_PROV_INIT_TPM          = 0x01,
  BIOS_OOB_PROV_INIT_ACK          = 0x02,
  BIOS_OOB_PROV_INIT_ACK2         = 0x03,
  BIOS_OOB_INIT_OOB               = 0x10,
  BIOS_OOB_INIT_TPM               = 0x11,
  BIOS_OOB_INIT_OOB2              = 0x12,
  BIOS_OOB_INIT_ACK               = 0x13,
  BIOS_OOB_INIT_ACK2              = 0x14,
  BIOS_OOB_RPROV_REQ              = 0x20,
  BIOS_OOB_RPROV_RES              = 0x21,
  BIOS_OOB_RPROV_ACK              = 0x22,
  BIOS_OOB_RPROV_ACK2             = 0x23,
  BIOS_OOB_TESTING                = 0xFF
} BIOS_OOB_COMMAND_ID;

typedef enum{
  /* BIOS_OOB Commands */
  BIOS_OOB_OK                     = 0x0,
  BIOS_OOB_ERROR                  = 0x1
} BIOS_OOB_ERROR_FLAG;

typedef enum{
  /* BIOS_OOB Commands */
  BIOS_OOB_TYPE_STATUS                  = 0x00,
  BIOS_OOB_TYPE_ROOTCA                  = 0x01,
  BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY    = 0x02,
  BIOS_OOB_TYPE_HKDF_32B_TPM_SALT       = 0x03,
  BIOS_OOB_TYPE_HKDF_32B_PSE_SALT       = 0x04,
  BIOS_OOB_TYPE_UNENCRYPTED_TOKEN_ID    = 0x05,
  BIOS_OOB_TYPE_UNENCRYPTED_DEVICE_ID   = 0x06,
  BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID      = 0x07,
  BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG  = 0x08,
  BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV   = 0x09,
  BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID     = 0x0A,
  BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG = 0x0B,
  BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV  = 0x0C,
  BIOS_OOB_TYPE_CLOUD_URL               = 0x0D,
  BIOS_OOB_TYPE_CLOUD_PORT              = 0x0E,
  BIOS_OOB_TYPE_PROXY_URL               = 0x0F,
  BIOS_OOB_TYPE_PROXY_PORT              = 0x10,
  BIOS_OOB_TYPE_PROVISIONING_STATE      = 0x11,
  BIOS_OOB_TYPE_PSE_SEED_1              = 0x12,
  BIOS_OOB_TYPE_PSE_SEED_2              = 0x13,
  BIOS_OOB_TYPE_PSE_SEED_3              = 0x14,
  BIOS_OOB_TYPE_PSE_SEED_4              = 0x15,
  BIOS_OOB_TYPE_TPM_NV_PWD              = 0x16,
  BIOS_OOB_TYPE_CLD_ADAPTER             = 0x17
} BIOS_OOB_DATA_TYPE;

typedef struct
{
  UINT16             Data1;
  UINT16             Data2;
  UINT16             Data3;
  UINT16             Data4;
} OOB_RESPONSE;

//
// OOB Related
//
//Message Header
typedef struct
{
  UINT32  MessageComplete     : 1;
  UINT32  Reserved            : 2;
  UINT32  Status              : 1;
  UINT32  ProtocolVersioning  : 4;
  UINT32  Source              : 4;
  UINT32  Length              : 12;
  UINT32  Command             : 8;
} OOB_MSG_HEADER;

typedef struct {
  BIOS_OOB_DATA_TYPE  Type      : 8;
  UINT32              Length    : 12;
  UINT32              Reserved  : 12;
} HECI_BIOS_PSE_MSG;

typedef struct {
  OOB_MSG_HEADER      OobHeader;
  HECI_BIOS_PSE_MSG   OobMsg;
  UINT8               Data[MAX_HECI_BUF_SIZE];
} HECI_BIOS_PSE_MSG_PACKAGE;

typedef struct
{
  OOB_MSG_HEADER   Header;
  OOB_RESPONSE     Response;
} OOB_GET_PWD_RES;

#define OOB_DISABLED 0
#define OOB_ENABLED  1

#pragma pack(1)
//
// OOB REGION DATA described below as sample
//
typedef struct {
  UINT32    ProvState;
  UINT32    DeviceIdSize;
  CHAR8     DeviceId[512];
  UINT32    TokenIdSize;
  CHAR8     TokenId[512];
  UINT32    CloudTypeSize;
  CHAR8     CloudType[16];
  UINT32    CloudHostUrlSize;
  CHAR8     CloudHostUrl[512];
  UINT32    CloudHostPort;
  UINT32    ProxyHostUrlSize;
  CHAR8     ProxyHostUrl[512];
  UINT32    ProxyHostPort;
  UINT32    BiosPasswordSize;
  CHAR8     BiosPassword[512];
} OOB_DATA;

typedef struct {
  UINT32     Size;
  VOID      *Buffer;
} OOB_ROOTCA;

typedef struct {
  EFI_HOB_GUID_TYPE   GuidType;
  OOB_DATA            OobData;
} OOB_REGION_HOB;

#pragma pack()

// #define HECI_CLIENT_BIOS_GUID { 0x892D1D46,		   \
				// 0x6B91, 0x4B62,		   \
				// { 0x8A, 0x99, 0xEB, 0xF7,  \
				  // 0x28, 0x78, 0x66, 0x7E } }

extern EFI_GUID gPseOobHeciClientInterfaceGuid;

// #define HECI_CLIENT_SMHI_GUID { 0xbb579a2e,                \
                                // 0xcc54, 0x4450,            \
                                // { 0xb1, 0xd0, 0x5e, 0x75,  \
                                  // 0x20, 0xdc, 0xad, 0x25 } }
extern EFI_GUID gPseSmhiClientInterfaceGuid;

CONST CHAR8 TPM_SALT[] = "HKDF_32B_TPM_SALT_FOR_BIOS_OOB_";
CONST CHAR8 PSE_SALT[] = "HKDF_32B_PSE_SALT_HKDF_32B_PSE_";
CONST CHAR8 PUBLIC_KEY[] = "106aBqEo";

CONST CHAR8 ENCRYPTED_TOKEN_ID_TAG[] = "6sPUu4ZNqkPqO";
CONST CHAR8 ENCRYPTED_TOKEN_ID_IV[] = "yvu426eqjxvIz";
CONST CHAR8 ENCRYPTED_DEVICE_ID_TAG[] = "PNhoJKOAqjmoZ";
CONST CHAR8 ENCRYPTED_DEVICE_ID_IV[] = "CYlrho6EQznOQ";

#define TPM_PASSWORD_SIZE             64
#define PSE_SALT_SIZE                 32
#define ENCRYPTED_TOKEN_ID_SIZE       64
#define ENCRYPTED_TOKEN_ID_TAG_SIZE   64
#define ENCRYPTED_TOKEN_ID_IV_SIZE    64
#define ENCRYPTED_DEVICE_ID_SIZE      64
#define ENCRYPTED_DEVICE_ID_TAG_SIZE  64
#define ENCRYPTED_DEVICE_ID_IV_SIZE   64
#define OOB_VARIABLE_NAME  L"OobPayloads"

typedef struct {
  UINT8     TpmNvPassword[TPM_PASSWORD_SIZE];
  UINT32    TpmNvPasswordSize;
  UINT8     PseSalt[PSE_SALT_SIZE];
  UINT32    PseSaltSize;
  UINT8     EncryptedTokenId[ENCRYPTED_TOKEN_ID_SIZE];
  UINT32    EncryptedTokenIdSize;
  UINT8     EncryptedTokenIdTag[ENCRYPTED_TOKEN_ID_TAG_SIZE];
  UINT32    EncryptedTokenIdTagSize;
  UINT8     EncryptedTokenIdIv[ENCRYPTED_TOKEN_ID_IV_SIZE];
  UINT32    EncryptedTokenIdIvSize;
  UINT8     EncryptedDeviceId[ENCRYPTED_DEVICE_ID_SIZE];
  UINT32    EncryptedDeviceIdSize;
  UINT8     EncryptedDeviceIdTag[ENCRYPTED_DEVICE_ID_TAG_SIZE];
  UINT32    EncryptedDeviceIdTagSize;
  UINT8     EncryptedDeviceIdIv[ENCRYPTED_DEVICE_ID_IV_SIZE];
  UINT32    EncryptedDeviceIdIvSize;
} OOB_VARIABLE;

#define OOB_VARIABLES_GUID \
  { \
    0x5f33e5af, 0x7b9b, 0x454d, { 0xa2, 0x29, 0x8d, 0x1c, 0xcd, 0x0f, 0x9b, 0x34 } \
  }
extern EFI_GUID gOobVariablesGuid;

#endif // _PSE_OOB_FEATURE_H_
