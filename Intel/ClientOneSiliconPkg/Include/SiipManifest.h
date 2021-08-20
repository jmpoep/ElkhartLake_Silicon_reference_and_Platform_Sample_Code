/** @file
  Header file for SIIP Manifest definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _SIIP_MANIFEST_H_
#define _SIIP_MANIFEST_H_

#include <SiipCommon.h>

#define FIRMWARE_MANIFEST_HEADER_VERSION_RSA_SHA256           0x10000
#define FIRMWARE_MANIFEST_HEADER_VERSION_RSA_SHA384           0x11000
#define FIRMWARE_MANIFEST_HEADER_VERSION_RSA_SHA512           0x12000
#define FIRMWARE_MANIFEST_HEADER_VERSION_ECDSA_SHA256         0x30000
#define FIRMWARE_MANIFEST_HEADER_VERSION_ECDSA_SHA384         0x31100

//
// Supported Hash Types
//
#define SIIP_HASHALG_RESERVED                  0x00000000
#define SIIP_HASHALG_SHA1                      0x00000001
#define SIIP_HASHALG_SHA256                    0x00000002
#define SIIP_HASHALG_SHA384                    0x00000003
#define SIIP_HASHALG_SHA512                    0x00000004

//
// EXCLUSION RANGE USED FOR SKIPPING PAYLOAD BYTES DURING SIGNING OPERATION
//
typedef struct {
  UINT16             StartIndex;
  UINT16             StopIndex;
} EXCLUSION_RANGE;

extern EXCLUSION_RANGE mFkmHdrExclusionRangeRsa[];
extern UINT8 mFkmHdrExclusionRangeRsaCount;
extern EXCLUSION_RANGE mFkmExclusionRangeRsa[];
extern UINT8 mFkmExclusionRangeRsaCount;
extern EXCLUSION_RANGE mFbmHdrExclusionRangeRsa[];
extern UINT8 mFbmHdrExclusionRangeRsaCount;
extern EXCLUSION_RANGE mFbmExclusionRangeRsa[];
extern UINT8 mFbmExclusionRangeRsaCount;
//
// EXCLUSION RANGE USED FOR SKIPPING PAYLOAD BYTES DURING SIGNING OPERATION
//
GLOBAL_REMOVE_IF_UNREFERENCED EXCLUSION_RANGE mFkmHdrExclusionRangeRsa[] = {
  {128, 511},      // PublicKey
  {512, 515},      // Exponent
  {516, 899},      // Signature
  {0xFFFF, 0x0000} // End marker
};
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mFkmHdrExclusionRangeRsaCount = sizeof(mFkmHdrExclusionRangeRsa) / sizeof(EXCLUSION_RANGE);

GLOBAL_REMOVE_IF_UNREFERENCED EXCLUSION_RANGE mFkmExclusionRangeRsa[] = {
  {0xFFFF, 0x0000} // End marker
};
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mFkmExclusionRangeRsaCount = sizeof(mFkmExclusionRangeRsa) / sizeof(EXCLUSION_RANGE);

GLOBAL_REMOVE_IF_UNREFERENCED EXCLUSION_RANGE mFbmHdrExclusionRangeRsa[] = {
  {128, 511},      // PublicKey
  {512, 515},      // Exponent
  {516, 899},      // Signature
  {0xFFFF, 0x0000} // End marker
};
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mFbmHdrExclusionRangeRsaCount = sizeof(mFbmHdrExclusionRangeRsa) / sizeof(EXCLUSION_RANGE);

GLOBAL_REMOVE_IF_UNREFERENCED EXCLUSION_RANGE mFbmExclusionRangeRsa[] = {
  {0xFFFF, 0x0000} // End marker
};
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mFbmExclusionRangeRsaCount = sizeof(mFbmExclusionRangeRsa) / sizeof(EXCLUSION_RANGE);

//
// Public Key Hash Index in TPM 2.0
//
#define TPM20_SIIP_PUK_NVINDEX              0x001C3000

//
// FIT entry - KM structure
//
#define SIIP_SIGNING_PUBKEY_DIGEST          BIT4

#define CPD_HEADER_MARKER                   SIGNATURE_32 ('$','C','P','D')
#define CPD_ENTRY_OFFSET_MASK               0x01FFFFFF
#define ENTRY_NAME_LENGTH                   12
#define CRC32_CHECKSUM_INDEX                16

#pragma pack (1)

typedef struct {
  UINT32    HeaderType;
  UINT32    HeaderLength;
  UINT32    HeaderVersion;
  UINT32    Flags;
  UINT32    Vendor;
  UINT32    Date;
  UINT32    Size;
  UINT32    HeaderId;
  UINT32    NoOfMetadataEntries;
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
  UINT32    NoOfMetadataEntries;
  UINT32    StructureVersion;
  UINT8     Reserved0[80];
  UINT32    ModulusSize;
  UINT32    ExponentSize;
  UINT8     PublicKey[MAX_MODULUS_SIZE*4];
  UINT32    Exponent;
  UINT8     Signature[MAX_MODULUS_SIZE*4];
  // End of Header
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
  UINT32    NoOfMetadataEntries;
  UINT32    StructureVersion;
  UINT8     Reserved0[80];
  UINT32    KeySize;
  UINT8     Reserved1[4];
  UINT8     PublicKeyQx[MAX_ECC_KEY_SIZE];
  UINT8     PublicKeyQy[MAX_ECC_KEY_SIZE];
  UINT8     SignatureR[MAX_ECC_KEY_SIZE];
  UINT8     SignatureS[MAX_ECC_KEY_SIZE];
  // End of Header
} FIRMWARE_MANIFEST_HEADER_ECC;

typedef struct {
  UINT8     Usage[MAX_BITMAP_USAGE];
  UINT8     Reserved[MAX_BITMAP_USAGE];
  UINT8     Policy;
  UINT8     HashAlgorithm;
  UINT16    HashSize;
  UINT8     Hash[MAX_HASH_SIZE];
} FIRMWARE_KEY_MANIFEST_KEY_INFO;

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
  FIRMWARE_KEY_MANIFEST_KEY_INFO    KeyX; // NumberOfKeys * FIRMWARE_KEY_MANIFEST_KEY_INFO
  // End of Payload
} FIRMWARE_KEY_MANIFEST;

typedef struct {
  UINT32    MetadataId;
  UINT8     Type;
  UINT8     HashAlgorithm;
  UINT16    HashSize;
  UINT8     MetadataHash[MAX_HASH_SIZE];
} FIRMWARE_BLOB_MANIFEST_METADATA_INFO;

typedef struct {
  UINT32                                ExtensionType;
  UINT32                                ExtensionLength;
  UINT32                                PackageName;
  UINT64                                VersionControlNumber;
  UINT8                                 UsageBitmap[MAX_BITMAP_USAGE];
  UINT32                                Svn;
  UINT8                                 FwType;
  UINT8                                 FwSubtype;
  UINT8                                 Reserved0[2];
  UINT32                                NumberOfDevices;
  UINT32                                DeviceAndRevisionList[MAX_NUMBER_OF_DEVICES];
  FIRMWARE_BLOB_MANIFEST_METADATA_INFO  MetadataX; // FMH.NoOfMetadataEntries * FIRMWARE_BLOB_MANIFEST_METADATA_INFO
  // End of Payload
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

typedef struct {
  UINT16              HashAlg;
  UINT16              Size;
  UINT8               *HashBuffer;
} FIT_HASH_STRUCTURE;

typedef struct {
  UINT8               Usage;
  FIT_HASH_STRUCTURE  *Digest;
} FIT_KMHASH_STRUCT;

typedef struct {
  UINT8               StructureId[8];      // '__KEYM__'. Abbreviation of Key Manifest
  UINT8               StructVersion;       // 0x21
  UINT8               Reserved0[3];        // Alignment, must be 0
  UINT16              KeySignatureOffset;  // Offset from start of KM to KeyManifestSignature
  UINT8               Reserved1[3];        // Alignment, must be 0
  UINT8               KeyManifestRevision; // Revision of the Key Manifest defined by the Platform Manufacturer
  UINT8               KmSvn;               // Bits 7:4 - Reserved, must be zero
                                           // Bits 3:0 - Key manifest Security Version Number
  UINT8               KeyManifestId;       // The key Manifest Identifier
  UINT16              KmPubKeyHashAlg;     // Hash algorithm of digest programmed into REG_BP.KEY register
  UINT16              KeyCount;            // Count of KeyHash structures
  FIT_KMHASH_STRUCT   *KeyHash;
//  FIT_KEY_AND_SIGNATURE_STRUCT  KeyManifestSignature;
} FIT_KEY_MANIFEST_STRUCTURE;

struct PARTITION_HEADER_STRUCT {
  UINT32              HeaderMarker;
  UINT32              NumberOfEntries;
  UINT8               HeaderVersion;
  UINT8               EntryVersion;
  UINT8               HeaderLength;
  UINT8               Reserved;
  UINT32              SubPartitionName;
  UINT32              Crc32Checksum;
};

typedef enum {
  FkmType       = 0,
  FbmType       = 1,
  MetadataType  = 2,
  ModuleType    = 3   ///< Code and static data
} MODULE_ENTRY_TYPE;

struct PARTITION_ENTRY_STRUCT {
  UINT8               EntryName[ENTRY_NAME_LENGTH];
  UINT32              Offset;
  UINT32              Length;
  MODULE_ENTRY_TYPE   ModuleType;
};

typedef struct PARTITION_HEADER_STRUCT CPD_HEADER_STRUCT;
typedef struct PARTITION_ENTRY_STRUCT  CPD_ENTRY_STRUCT;

typedef struct PARTITION_HEADER_STRUCT PKG_DIR_HEADER;
typedef struct PARTITION_ENTRY_STRUCT  PKG_DIR_ENTRY;

typedef struct {
  UINT32              MetadataSize;
  UINT32              MetadataId;
  UINT32              MetadataVersion;
  UINT32              NoOfModules;
} META_DATA_STRUCT1;

typedef struct {
  UINT8               Id[ENTRY_NAME_LENGTH];
  UINT32              HashSize;
  UINT32              ModuleVersion;
  UINT32              HashAlgo;
  UINT8               Hash[MAX_HASH_SIZE];
} META_DATA_STRUCT2;

typedef struct {
  UINT32              NoOfKeys;
} META_DATA_STRUCT3;

typedef struct {
  UINT8               KeyId[MAX_BITMAP_USAGE];
} META_DATA_STRUCT4;

#pragma pack ()

#endif //_SIIP_MANIFEST_H_
