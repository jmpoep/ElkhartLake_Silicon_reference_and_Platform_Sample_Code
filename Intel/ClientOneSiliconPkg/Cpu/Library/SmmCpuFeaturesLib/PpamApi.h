/** @file
  PPAM API definition

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

#ifndef _PPAM_API_H_
#define _PPAM_API_H_

#define PPAM_SPEC_VERSION_MAJOR 1
#define PPAM_SPEC_VERSION_MINOR 0

#pragma pack (push, 1)

#define HARDWARE_FIELD_FILL_TO_2K (2048 - sizeof(UINT32) * 8)
typedef struct {
  UINT32         HardwareHeaderRevision;
  UINT32         MonitorFeatures;
  UINT32         GdtrLimit;
  UINT32         GdtrBaseOffset;
  UINT32         CsSelector;
  UINT32         EipOffset;
  UINT32         EspOffset;
  UINT32         Cr3Offset;
  UINT8          Reserved[HARDWARE_FIELD_FILL_TO_2K];
} HARDWARE_PPAM_HEADER;

#define PPAM_FEATURES_IA32E 0x1

typedef struct {
  UINT32         Reserved; // must be 0
} PPAM_FEAT;

typedef UINT64 PPAM_PHYSICAL_RESOURCE_BITMAP;
//
// Bit definitions
// All other bits reserved for future use and must be 0.
//
#define PPAM_MEM_RESOURCE  0x1
// All other physical resource types are TBD and reserved.

typedef UINT64 PPAM_META_RESOURCE_BITMAP;
//
// Bit definitions
// All other bits reserved for future use and must be 0.
//
#define PPAM_CR0_WRITE_DISABLED                   0x00000001ull
#define PPAM_CR3_WRITE_DISABLED                   0x00000002ull
#define PPAM_CR4_WRITE_DISABLED                   0x00000004ull
#define PPAM_IA32_EFER_WRITE_DIABLED              0x00000008ull
#define PPAM_IA32_MISC_ENABLE_WRITE_DISABLED      0x00000010ull
#define PPAM_SMRR_WRITE_DISABLED                  0x00000020ull
#define PPAM_TASK_SWITCH_DISABLED                 0x00000040ull
#define PPAM_SMBASE_RELOAD_DISABLED               0x00000080ull
#define PPAM_SMM_MONITOR_CTRL_WRITE_DISABLED      0x00000100ull

#define PPAM_PAGE_TABLE_WITHIN_SMRAM              0x00000200ull
#define PPAM_PAGE_TABLE_WRITE_DISABLED            0x00000400ull
#define PPAM_ALL_CODE_PAGES_WRITE_DISABLED        0x00000800ull
#define PPAM_ALL_CODE_PAGES_WITHIN_SMRAM          0x00001000ull

#define PPAM_SMM_ENTRY_CODE_ON_A_CODE_PAGE        0x00004000ull
#define PPAM_SMM_ENTRY_POINT_TABLE_WITHIN_SMRAM   0x00008000ull
#define PPAM_SMM_ENTRY_POINT_TABLE_WRITE_DISABLED 0x00010000ull
#define PPAM_GDT_WITHIN_SMRAM                     0x00020000ull
#define PPAM_GDT_WRITE_DISABLED                   0x00040000ull
#define PPAM_IDT_WITHIN_SMRAM                     0x00080000ull
#define PPAM_IDT_WRITE_DISABLED                   0x00100000ull
#define PPAM_STACK_WITHIN_SMRAM                   0x00200000ull
#define PPAM_SMRAM_PROPERLY_LOCKED                0x00400000ull

typedef struct {
  UINT8                             PpamSpecVerMajor;
  UINT8                             PpamSpecVerMinor;
  UINT16                            Reserved; // must be zero
  UINT32                            StaticImageSize;
  UINT32                            PerProcDynamicMemorySize;
  UINT32                            AdditionalDynamicMemorySize;
  PPAM_FEAT                         PpamFeatures;
  UINT32                            Reserved1; // must be 1
  UINT32                            Reserved2; // must be 0
  UINT32                            Reserved3; // must be 0
  //
  // Fields unique to PPAM not included in STM
  //
  GUID                              Identifier;
  PPAM_PHYSICAL_RESOURCE_BITMAP     CapabilityPhysicalResourceBitmap;
  PPAM_META_RESOURCE_BITMAP         CapabilityMetaResourceBitmap;
  UINT32                            ImageVersion;
  UINT32                            Reserved4;
  UINT32                            Reserved5;
  UINT32                            Reserved6;
  //
  // The total PPAM_HEADER should be 4K.
  //
} SOFTWARE_PPAM_HEADER;

typedef struct {
  HARDWARE_PPAM_HEADER HwPpamHdr;
  SOFTWARE_PPAM_HEADER SwPpamHdr;
} PPAM_HEADER;

// API parameter

typedef struct {
  UINT64                            CapabilityAddress;
  UINT32                            CapabilitySize;
} PPAM_GENERAL_FUNC_GET_CAPABILITY_PARAMETER;

#define PPAM_CAPABILITY_STRUCT_VERSION 0x10000
typedef struct {
  GUID                              Identifier;
  UINT32                            Version;
  UINT32                            Length;
  UINT64                            CapabilityPhysicalResourceBitmap;
  UINT64                            CapabilityMetaResourceBitmap;
} PPAM_CAPABILITY_STRUCT;

typedef struct {
  UINT64                            ResourceAddress;
  UINT32                            ResourceSize;
} PPAM_GENERAL_FUNC_GET_RESOURCES_PARAMETER;

//
// PPAM_RESOURCE_LIST
//
// resource descriptor types are given below
// all undefined values are reserved
//

//
// 0x00000000 .. 0x000000FF  : Special descriptors
//
#define PPAM_END_OF_RESOURCES              0x00000000
#define PPAM_RSC_VALID_INDICATOR           0x00000001
#define PPAM_SCRATCH_RESOURCE              0x00000002

// 0x00000100 .. 0x000001FF : Physical resource types
#define PPAM_PHYS_MEM_RANGE                0x00000100

// 0x00000200 .. 0x000002FF : meta resource types
#define PPAM_META_SMM_ENTRY_HASH           0x00000200
#define PPAM_META_PROPERTY_BITMAP          0x00000201

typedef struct {
  UINT32 RscType;
  UINT16 Length;
  UINT16 Reserved;
} PPAM_RSC_DESC_HEADER;

typedef struct {
  PPAM_RSC_DESC_HEADER Hdr;
  UINT64              Reserved;
} PPAM_RSC_END;

typedef struct {
  PPAM_RSC_DESC_HEADER Hdr;
  UINT64               Base;
  UINT64               Length;
  UINT32               RWXAttributes:3;
  UINT32               Reserved:29;
  UINT32               Reserved_2;
} PPAM_RSC_MEM_DESC;
#define PPAM_RSC_MEM_R    0x1
#define PPAM_RSC_MEM_W    0x2
#define PPAM_RSC_MEM_X    0x4

typedef struct {
  UINT8     SMM_SHA1[20];
  UINT8     SMM_SHA256[32];
  UINT8     SMM_SHA384[48];
  UINT8     SMM_SM3_256[32];
  UINT8     SMM_Reserved[64];
} PPAM_META_RSC_SMM_ENTRY_HASH_DATA;

typedef struct {
  PPAM_RSC_DESC_HEADER                 Hdr;
  PPAM_META_RSC_SMM_ENTRY_HASH_DATA    Data;
} PPAM_META_RSC_SMM_ENTRY_HASH_DESC;

typedef PPAM_META_RESOURCE_BITMAP PPAM_PROPERTY_BITMAP;
typedef struct {
  PPAM_RSC_DESC_HEADER        Hdr;
  PPAM_PROPERTY_BITMAP        Properties;
} PPAM_META_RSC_PROPERTY_BITMAP_DESC;

typedef struct {
  UINT32                      Valid:1;
  UINT32                      Reserved:31;
} PPAM_META_RSC_VALID_INDICATOR_FLAG;

typedef struct {
  PPAM_RSC_DESC_HEADER                 Hdr;
  PPAM_META_RSC_VALID_INDICATOR_FLAG   Flags;
  UINT32                               ApicId;
} PPAM_META_RSC_VALID_INDICATOR_DESC;

typedef struct {
  PPAM_RSC_DESC_HEADER        Hdr;
//UINT8                       Data[Hdr.Length - sizeof(Hdr)];
} PPAM_SCRATCH_RESOURCE_DESC;

typedef union {
  PPAM_RSC_DESC_HEADER                Header;
  PPAM_RSC_END                        End;
  PPAM_RSC_MEM_DESC                   Mem;
  PPAM_META_RSC_SMM_ENTRY_HASH_DESC   SmmEntryHash;
  PPAM_META_RSC_PROPERTY_BITMAP_DESC  PropertyBitmap;
  PPAM_META_RSC_VALID_INDICATOR_DESC  ValidIndicator;
  PPAM_SCRATCH_RESOURCE_DESC          Scratch;
} PPAM_RSC;

//
// VMCALL API Numbers
//

// API number convention: MLE facing VMCALL interfaces have bit 16 set
#define PPAM_GET_CAPABILITY_VMCALL                 0x00010009
#define PPAM_GET_RESOURCES_VMCALL                  0x0001000A

//
// Return codes
//
typedef UINT32  PPAM_STATUS;

#define PPAM_SUCCESS 0x00000000
// all error codes have bit 31 set
// PPAM errors have bit 16 set
#define ERROR_PPAM_SECURITY_VIOLATION              0x80010001
#define ERROR_PPAM_NON_SMX_OPERATION               0x80010002
#define ERROR_PPAM_BUFFER_TOO_SMALL                0x8001000B
#define ERROR_PPAM_OUT_OF_RESOURCES                0x80010015
#define ERROR_PPAM_FUNCTION_NOT_SUPPORTED          0x80010016
#define ERROR_PPAM_UNSUPPORTED_SMM_ENTRYPOINT      0x80010019
#define ERROR_PPAM_UNKNOWN_SMM_ENTRYPOINT          0x8001001A


//
// SMM EntryPoint info table
//
typedef struct {
  UINT8             JmpInstruction[2]; // 0xEB 0x04
  UINT32            InfoTableAddress;
} SMM_ENTRY_POINT_HEADER;

#define SMM_ENTRY_POINT_INFORMATION_TABLE_SIGNATURE  SIGNATURE_64('S', 'M', 'M', '_', 'I', 'N', 'F', 'O')
#define SMM_ENTRY_POINT_INFORMATION_TABLE_VERSION    0x00010000
typedef struct {
  //
  // Signature to identify this data structure
  //
  UINT64    Signature; // 'SMM_INFO'
  //
  // Structure version
  //
  UINT32    Version;
  //
  // The length in bytes, from SmmEntryPoint.
  //
  // PPAM should measure [SmmEntryPoint, SmmEntryPoint + Length] to see
  // if it matches the pre-defined value.
  //
  UINT32    SmmEntryPointSize;
  //
  // A list of information entry ended with TPYE_END
  //
//SMM_ENTRY_POINT_INFORMATION_ENTRY  SmmEntryPointInformationEntry[];
} SMM_ENTRY_POINT_INFORMATION_TABLE;

#define SMM_ENTRY_POINT_INFO_NULL               0x0
#define SMM_ENTRY_POINT_INFO_GDT                0x1
#define SMM_ENTRY_POINT_INFO_IDT                0x2
#define SMM_ENTRY_POINT_INFO_CR3                0x3

#define SMM_ENTRY_POINT_INFO_SUPOVR_STATE_LOCK  0x5
#define SMM_ENTRY_POINT_INFO_STACK              0x6
#define SMM_ENTRY_POINT_INFO_STACK_SIZE         0x7
#define SMM_ENTRY_POINT_INFO_END                0xFF

typedef struct {
  // SMM_ENTRY_POINT_INFORMATION_ENTRY_TYPE_XXX
  UINT8     Type;
  // Size of data.
  UINT8     DataSize;
  // Offset to the SMM entrypoint
  UINT16    DataOffset;
} SMM_ENTRY_POINT_INFORMATION_ENTRY;

//
// PPAM Manifest
//

#define PPAM_MANIFEST_NAME    "PPAM_MANIFEST"
#define PPAM_MANIFEST_VERSION 0x1

typedef struct {
  //
  // "PPAM_MANIFEST"
  //
  UINT8     Name[14];
  //
  // Version of the structure
  //
  UINT16    Version;
  //
  // GUID representing PPAM vendor.
  // For Intel, this value is INTEL_PPAM_VENDOR_GUID.
  // Domain of PPAM_ID is defined by PPAM_VENDOR.
  //
  GUID      PPAM_VENDOR;
  //
  // PPAM_ID defines the domain of PPAM_VER and PPAM_SVN
  //
  UINT32    PPAM_ID;
  UINT32    PPAM_VER;
  UINT32    PPAM_SVN;
  //
  // BIT0: 0 = Production, 1 = Preproduction
  // BIT1: 0 = Production, 1 = Debug
  //
  UINT16    Flags;
  UINT16    Reserved;
  //
  // PPAM hash
  //
  UINT8     PPAM_SHA1[20];
  UINT8     PPAM_SHA256[32];
  UINT8     PPAM_SHA384[48];
  UINT8     PPAM_SM3_256[32];
  UINT8     PPAM_Reserved[64];
  //
  // SMM hash (SMM entrypoint and SMM info table)
  //
  UINT8     SMM_SHA1[20];
  UINT8     SMM_SHA256[32];
  UINT8     SMM_SHA384[48];
  UINT8     SMM_SM3_256[32];
  UINT8     SMM_Reserved[64];
} PPAM_MANIFEST;

#pragma pack (pop)

#define  PPAM_MANIFEST_TABLE_GUID { \
  0x1878f400, 0xdcdb, 0x4f5e, 0x8b, 0x2d, 0x85, 0x71, 0x4a, 0xca, 0x2c, 0x90 \
  }

#define  INTEL_PPAM_VENDOR_GUID { \
  0x5aaea57d, 0x1c7e, 0x48ee, 0x8e, 0xdb, 0x5d, 0x28, 0x31, 0xf7, 0x8c, 0xee \
  }

#endif
