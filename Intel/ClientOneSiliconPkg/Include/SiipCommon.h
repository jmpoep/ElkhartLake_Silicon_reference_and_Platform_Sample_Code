/**@file
  Siip common header file

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

#ifndef _SIIP_COMMON_H_
#define _SIIP_COMMON_H_

#define VERIFIER_DONE_WAIT_TIME   100         ///< Wait Time = 100 microseconds
#define VERIFIER_DONE_PERIOD      10          ///< Wait Period = 10 microseconds

typedef enum {
  NULL_IP = 0,
  PSE_IP = 1,
  ACE_IP = 2,
  PCIE_IP = 3,
  UNKNOWN_IP = 0xFF // Valid IP but don't wanted to mention name
} SIIP_IP_NAME;

typedef enum {
  READ = 0,
  WRITE = 1
} SIIP_OP_TYPE;

typedef enum {
  LOADER = 0,
  VERIFIER = 1
} SIIP_REG_TYPE;

typedef enum {
  NOT_FOUND = 0,
  AUTHENTICITY_FAILED = 1
} SIIP_ERROR_CODE;

typedef enum {
  TWO_BYTES = 2,
  FOUR_BYTES = 4,
  EIGHT_BYTES = 8
} SIIP_NUM_BYTES;

typedef enum {
  FW_BLOB_0 = 0,
  FW_BLOB_1 = 1,
  FW_BLOB_2 = 2,
  FW_BLOB_3 = 3,
  MAX_FW_BLOB = 4,
  NOT_APPLICABLE = 0xFF
} SIIP_FW_BLOB_INDEX;

typedef enum {
  KEY_BLOB_0 = 0,
  KEY_BLOB_1 = 1,
  KEY_BLOB_2 = 2,
  KEY_BLOB_3 = 3
} SIIP_KEY_BLOB_INDEX;

typedef enum {
  FW_1 = 1,
  FW_2 = 2,
  FW_3 = 3,
  FW_4 = 4
} SIIP_FW_INDEX;

typedef enum {
  LOADER_1 = 1,
  LOADER_2 = 2,
  LOADER_3 = 3,
  LOADER_4 = 4,
  NULL_LOADER = 0
} SIIP_LOADER_INDEX;

typedef enum {
  VERIFIER_1 = 1,
  VERIFIER_2 = 2,
  VERIFIER_3 = 3,
  VERIFIER_4 = 4,
  NULL_VERIFIER = 0
} SIIP_VERIFIER_INDEX;

typedef enum {
  MATERIAL_1 = 1,
  MATERIAL_2 = 2,
  MATERIAL_3 = 3,
  MATERIAL_4 = 4,
  NULL_MATERIAL = 0
} SIIP_VERIFICATION_MATERIAL_INDEX;

typedef enum {
  FW_KEYMANIFEST_BLOB = 0,
  FW_MANIFEST_BLOB = 1,
  FW_CODE_BLOB = 2,
  FW_DATA_BLOB = 3
} SIIP_GUID_TYPE;

typedef enum {
  OEM_FW_MANIFEST = 0,
  INTEL_FW_MANIFEST = 1
} SIIP_FW_KEY_MANIFEST_TYPE;

typedef enum {
  KeyManifestReserved = 0,
  KeyManifestCseRot   = 1,
  KeyManifestCseOem   = 2,
  KeyManifestOemFw    = 3,
  KeyManifestIntelFw  = 4
} SIIP_KEY_MANIFEST_TYPE;

typedef enum {
  FwManifestTypeUnknown = 0,
  FwManifestTypeRSA     = 1,
  FwManifestTypeECDSA   = 2
} SIIP_FW_MANIFEST_HDR_TYPE;

typedef enum {
  IMR_1 = 1,
  IMR_2 = 2,
  REQUEST_FREE_IMR = 0xFFFE,
  NO_IMR = 0xFFFF
} SIIP_IP_IMR_INDEX;

//
// SIIP CONFIGURATION REGISTER OFFSETS
//
#define SIIP_IP_CAP             0x18      // IP Loader and Verifier Cap0 Register
#define IP_LOAD_OFFSET          4         // Loader Capabilities is IP
#define IP_VERIFIER_OFFSET      8         // Verifier Capabilities is IP
#define BIOS_LOAD_OFFSET        12        // Loader Capabilities is BIOS
#define BIOS_VERIFIER_OFFSET    16        // Verifier Capabilities is BIOS
#define IASW_LOAD_OFFSET        20        // Loader Capabilities is IA SW/TEE
#define IASW_VERIFIER_OFFSET    24        // Verifier Capabilities is IA SW/TEE
#define SOCIP_LOAD_OFFSET       28        // Loader Capabilities is another SOC IP
#define SOCIP_VERIFIER_OFFSET   32        // Verifier Capabilities is another SOC IP
#define SIIP_LOAD_ERROR         0x30      // Loader Error Status
#define SIIP_VERIFY_ERROR       0x30      // Verifier Error Status
#define SIIP_GP3_0              0x140     // Verifier General Purpose 3 - 0
#define SIIP_GP3_1              0x144     // Verifier General Purpose 3 - 1
#define IP_IS_CAPABLE           BIT0      // IP as the loader
#define BIOS_IS_CAPABLE         BIT1      // BIOS as the loader
#define IASW_TEE_IS_CAPABLE     BIT2      // IASW as the loader
#define SOCIP_IS_CAPABLE        BIT3      // SOCIP as the loader

//
// SIIP CONFIGURATION REGISTER MASKS
//
#define LOAD_CAP_MASK           0xF
#define VERIFY_CAP_MASK         0xF
#define LOAD_ERR_BIT            4
#define VERIFY_ERR_BIT          4
#define LOAD_ADDRESS_MASK       0xFFFFFFFF
#define VERIFY_ADDRESS_MASK     0xFFFFFFFF
#define IMR_ADDRESS_MASK        0xFFFFFFFF
#define IMR_SIZE_MASK           0xFFFFFFF0
#define RS_IMR_MASK             BIT2 | BIT1
#define IMR_SIZE_LOW_OFFSET     4
#define IMR_SIZE_HIGH_OFFSET    28
#define LOAD_DONE_OFFSET        0x8
#define VERIFY_DONE_OFFSET      0x8
#define HW_DEV_ID_MASK          0x0000FFFF
#define HW_REV_ID_BIT_OFFSET    16
#define HW_REV_ID_MASK          0x00FF0000

//
// SUPPORTED HASH TYPES
//
#define HASHALG_SHA1            0x00000000
#define HASHALG_SHA224          0x00000001
#define HASHALG_SHA256          0x00000002
#define HASHALG_SHA384          0x00000003
#define HASHALG_SHA512          0x00000004
#define HASHALG_MAX             0x00000005

//
// SIIP LOADER FILE INDEX AND OFFSETS
//
#define LOADER_1_OFFSET         0x40
#define LOADER_2_OFFSET         0x50
#define LOADER_3_OFFSET         0x60
#define LOADER_4_OFFSET         0x70

//
// SIIP VERIFIER FILE INDEX AND OFFSETS
//
#define VERIFIER_1_OFFSET       0x40
#define VERIFIER_2_OFFSET       0x50
#define VERIFIER_3_OFFSET       0x60
#define VERIFIER_4_OFFSET       0x70

//
// SIIP IMR ADDRESS OFFSET
//
#define IMR_1_ADDRESS_OFFSET    0x80
#define IMR_2_ADDRESS_OFFSET    0x90
//
// SIIP IMR SIZE OFFSET
//
#define IMR_1_SIZE_OFFSET       0x88
#define IMR_2_SIZE_OFFSET       0x98

//
// SIIP IMR
//
#define MAX_IMRS_PER_SOC        32

//
// SIIP Manifest
//
#define FIRMWARE_MANIFEST_HEADER_VERSION_RSA           0x10000
#define FIRMWARE_MANIFEST_HEADER_VERSION_ECDSA_P256    0x30000
#define FIRMWARE_MANIFEST_HEADER_VERSION_ECDSA_P384    0x31100

//#pragma pack(1)
#define MAX_MODULUS_SIZE         96
#define MAX_BITMAP_USAGE         16
#define MAX_HASH_SIZE            64
#define MAX_NUMBER_OF_DEVICES    8
#define MAX_METADATA_HASH_SIZE   32
#define MAX_ECC_KEY_SIZE         48

//
// Siip Fw - Common
//

// {00000000-0000-0000-0000-000000000000}
#define SIIP_IP_FIRMWARE_NULL_ENTRY_GUID \
  { \
    0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
  }

// {44285127-BDC8-48FB-BF59-5F49EC6A0CB0}
#define SIIP_FIRMWARE_KEY_MANIFEST_GUID \
  { \
    0x44285127, 0xbdc8, 0x48fb, 0xbf, 0x59, 0x5f, 0x49, 0xec, 0x6a, 0x0c, 0xb0 \
  }

//
// Siip Fw - Pse Ip
//

// {8AFFBA0F-C312-4717-9DD5-6AB1FE5FCB47}
#define SIIP_PSE_FIRMWARE_BLOB_MANIFEST_GUID \
  { \
    0x8affba0f, 0xc312, 0x4717, 0x9d, 0xd5, 0x6a, 0xb1, 0xfe, 0x5f, 0xcb, 0x47 \
  }

// {EBA4A247-42C0-4C11-A167-A4058BC9D423}
#define SIIP_PSE_FIRMWARE_CODE_BLOB0_GUID \
  { \
    0xeba4a247, 0x42c0, 0x4c11, 0xa1, 0x67, 0xa4, 0x05, 0x8b, 0xc9, 0xd4, 0x23 \
  }

// {AEFD206E-0633-4719-92DC-F64151006798}
#define SIIP_PSE_FIRMWARE_DATA_BLOB0_GUID \
  { \
    0xaefd206e, 0x0633, 0x4719, 0x92, 0xdc, 0xf6, 0x41, 0x51, 0x00, 0x67, 0x98 \
  }

#endif // _SIIP_COMMON_H_
