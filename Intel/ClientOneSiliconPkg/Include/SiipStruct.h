/**@file
  Siip common struct header file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#ifndef _SIIP_STRUCT_H_
#define _SIIP_STRUCT_H_

typedef struct {
  UINT32    HeaderType;
  UINT32    HeaderLength;
  UINT32    HeaderVersion;
  UINT32    Flags;
  UINT32    Vendor;
  UINT32    Date;
  UINT32    Size;
  UINT32    HeaderId;
  UINT32    NumModuleEntries;
  UINT32    StructureVersion;
} FIRMWARE_MANIFEST_HEADER_COMMON;

typedef struct {
  UINT32    HeaderType;
  UINT32    HeaderLength;
  UINT32    HeaderVersion;
  UINT32    Flags;
  UINT32    Vendor;
  UINT32    Date;
  UINT32    Size;
  UINT32    HeaderId;
  UINT32    NumModuleEntries;
  UINT32    StructureVersion;
  UINT8     Reserved0[80];
  UINT32    ModulusSize;
  UINT32    ExponentSize;
  UINT8     PublicKey[MAX_MODULUS_SIZE*4];
  UINT32    Exponent;
  UINT8     Signature[MAX_MODULUS_SIZE*4];
} FIRMWARE_MANIFEST_HEADER_RSA;

typedef struct {
  UINT32    HeaderType;
  UINT32    HeaderLength;
  UINT32    HeaderVersion;
  UINT32    Flags;
  UINT32    Vendor;
  UINT32    Date;
  UINT32    Size;
  UINT32    HeaderId;
  UINT32    NumModuleEntries;
  UINT32    StructureVersion;
  UINT8     Reserved0[80];
  UINT32    KeySize;
  UINT8     Reserved1[4];
  UINT8     PublicKeyQx[MAX_ECC_KEY_SIZE*4];
  UINT8     PublicKeyQy[MAX_ECC_KEY_SIZE*4];
  UINT8     SignatureR[MAX_ECC_KEY_SIZE*4];
  UINT8     SignatureS[MAX_ECC_KEY_SIZE*4];
} FIRMWARE_MANIFEST_HEADER_ECC;

typedef struct {
  UINT32    ExtensionType;
  UINT32    ExtensionLength;
  UINT32    KeyManifestType;
  UINT32    KeyManifestSecurityVersionNumber;
  UINT16    OemId;
  UINT8     KeyManifestId;
  UINT8     Reserved0;
  UINT8     Reserved1[12];
  UINT32    NumberOfKeys;
  UINT8     Key0Usage[MAX_BITMAP_USAGE];
  UINT8     Key0Reserved[MAX_BITMAP_USAGE];
  UINT8     Key0Policy;
  UINT8     Key0HashAlgorithm;
  UINT16    Key0HashSize;
  UINT8     Key0Hash[MAX_HASH_SIZE];
} FIRMWARE_KEY_MANIFEST;

typedef struct {
  UINT32    ExtensionType;
  UINT32    ExtensionLength;
  UINT32    PackageName;
  UINT32    VersionControlNumber;
  UINT8     UsageBitmap[MAX_BITMAP_USAGE];
  UINT32    Svn;
  UINT8     FwType;
  UINT8     FwSubtype;
  UINT8     Reserved0[2];
  UINT32    NumberOfDevices;
  UINT32    DeviceAndRevisionList[MAX_NUMBER_OF_DEVICES];
  UINT8     Module0Type;
  UINT8     Module0HashAlgorithm;
  UINT16    Module0HashSize;
  UINT32    Module0MetadataSize;
  UINT8     Module0MetadataHash[MAX_METADATA_HASH_SIZE];
} FIRMWARE_BLOB_MANIFEST;

typedef struct {
  FIRMWARE_MANIFEST_HEADER_RSA  FkmHdr;
  FIRMWARE_KEY_MANIFEST         Fkm;
} FIRMWARE_KEY_MANIFEST_STRUCT_RSA;

typedef struct {
  FIRMWARE_MANIFEST_HEADER_ECC  FkmHdr;
  FIRMWARE_KEY_MANIFEST         Fkm;
} FIRMWARE_KEY_MANIFEST_STRUCT_ECC;

typedef struct {
  FIRMWARE_MANIFEST_HEADER_RSA  FbmHdr;
  FIRMWARE_BLOB_MANIFEST        Fbm;
} FIRMWARE_BLOB_MANIFEST_STRUCT_RSA;

typedef struct {
  FIRMWARE_MANIFEST_HEADER_ECC  FbmHdr;
  FIRMWARE_BLOB_MANIFEST        Fbm;
} FIRMWARE_BLOB_MANIFEST_STRUCT_ECC;
//#pragma pack()

typedef struct {
  UINT8              IpName;
  EFI_GUID           SiipIpFirmwareBlobManifestGuid;
  EFI_GUID           SiipIpFirmwareCodeBlob0Guid;
  EFI_GUID           SiipIpFirmwareCodeBlob1Guid;
  EFI_GUID           SiipIpFirmwareCodeBlob2Guid;
  EFI_GUID           SiipIpFirmwareCodeBlob3Guid;
  EFI_GUID           SiipIpFirmwareDataBlob0Guid;
  EFI_GUID           SiipIpFirmwareDataBlob1Guid;
  EFI_GUID           SiipIpFirmwareDataBlob2Guid;
  EFI_GUID           SiipIpFirmwareDataBlob3Guid;
} SIIP_FW_IP_FILES;

SIIP_FW_IP_FILES mSiipFwIpFiles[] = {
  //
  // PSE IP
  //
  {
    PSE_IP,
    SIIP_PSE_FIRMWARE_BLOB_MANIFEST_GUID, // gSiipPseFirmwareBlobManifestGuid
    SIIP_PSE_FIRMWARE_CODE_BLOB0_GUID,    // gSiipPseFirmwareCodeBlob0Guid
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_PSE_FIRMWARE_DATA_BLOB0_GUID,    // gSiipPseFirmwareDataBlob0Guid
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID
  },

  //
  // ACE IP
  //
  {
    ACE_IP,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID
  },

  //
  // DEFAULT IP
  //
  {
    NULL_IP,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID,
    SIIP_IP_FIRMWARE_NULL_ENTRY_GUID
  }
};


typedef struct {
  UINT16             StartIndex;
  UINT16             StopIndex;
} EXCLUSION_RANGE_FOR_SIGNING;

EXCLUSION_RANGE_FOR_SIGNING mFirmwareKeyManifestHeaderExclusionRangeRsa[] = {
  {128, 515}
};

EXCLUSION_RANGE_FOR_SIGNING mFirmwareKeyManifestRsaExclusionRangeRsa[] = {
  {128, 515}
};

EXCLUSION_RANGE_FOR_SIGNING mFirmwareBlobManifestHeaderExclusionRangeRsa[] = {
  {128, 515}
};

EXCLUSION_RANGE_FOR_SIGNING mFirmwareBlobManifestRsaExclusionRangeRsa[] = {
  {128, 515}
};

#endif // _SIIP_STRUCT_H_
