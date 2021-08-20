/** @file
  This file contains definitions to describe ACM firmware.

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

@par Specification
**/

#ifndef _ACM_H_
#define _ACM_H_

#include <Base.h>

///
/// ACM Header
///
#define ACM_HEADER_VERSION_3  (3 << 16)
#define ACM_PKCS_1_5_RSA_SIGNATURE_SHA256_SIZE          256
#define ACM_PKCS_1_5_RSA_SIGNATURE_SHA384_SIZE          384

#pragma pack(push, 1)

//
// ACM definition
//
#define ACM_MODULE_TYPE_CHIPSET_ACM                     2
#define ACM_MODULE_SUBTYPE_CAPABLE_OF_EXECUTE_AT_RESET  0x1
#define ACM_MODULE_SUBTYPE_ANC_MODULE                   0x2
#define ACM_HEADER_FLAG_DEBUG_SIGNED                    BIT15
#define ACM_NPW_SVN                                     0x2

typedef struct _ACM_HEADER {
  UINT16 ModuleType;         ///< Module type
  UINT16 ModuleSubType;
  UINT32 HeaderLen;          ///< 4 4 Header length (in multiples of four bytes) (161 for version 0.0)
  UINT32 HeaderVersion;      ///< 8 4 Module format version
  UINT16 ChipsetId;          ///< 12 4 Module release identifier
  UINT16 Flags;
  UINT32 ModuleVendor;       ///< 16 4 Module vendor identifier
  UINT32 Date;               ///< 20 4 Creation date (BCD format: year.month.day)
  UINT32 Size;               ///< 24 4 Module size (in multiples of four bytes)
  UINT16 AcmSvn;             ///< 28 2 ACM-SVN Number
  UINT16 SeSvn;              ///< 30 2 SE-SVN number
  UINT32 CodeControl;        ///< 32 4 Authenticated code control flags
  UINT32 ErrorEntryPoint;    ///< 36 4 Error response entry point offset (bytes)
  UINT32 GdtLimit;           ///< 40 4 GDT limit (defines last byte of GDT)
  UINT32 GdtBasePtr;         ///< 44 4 GDT base pointer offset (bytes)
  UINT32 SegSel;             ///< 48 4 Segment selector initializer
  UINT32 EntryPoint;         ///< 52 4 Authenticated code entry point offset (bytes)
  UINT32 Reserved2[16];      ///< 56 64 Reserved for future extensions
  UINT32 KeySize;            ///< 120 4 Module public key size less the exponent  (in multiples of four bytes - 64 for version 0.0)
  UINT32 ScratchSize;        ///< 124 4 Scratch field size (in multiples of four bytes - 2 * KeySize + 15 for version 0.0)
  UINT8  Rsa2048PubKey[256];
  UINT32 RsaPubExp;
  UINT8  Rsa2048Sig[256];
  UINT8  Scratch[572];       ///< 143 DWORDS = 572 BYTES Scratch Size
} ACM_HEADER;

typedef struct {
  UINT16     ModuleType;
  UINT16     ModuleSubType;
  UINT32     HeaderLen;
  UINT32     HeaderVersion;
  UINT16     ChipsetId;
  UINT16     Flags;
  UINT32     ModuleVendor;
  UINT32     Date;
  UINT32     Size;
  UINT16     AcmSvn;
  UINT16     SeAcmSvn;
  UINT32     CodeControl;
  UINT32     ErrorEntryPoint;
  UINT32     GdtLimit;
  UINT32     GdtBasePtr;
  UINT32     SegSel;
  UINT32     EntryPoint;
  UINT8      Rsvd2[64];
  UINT32     KeySize;            // 96 DWORDS in the Key
  UINT32     ScratchSize;
  UINT8      Rsa3072PubKey[384];
  UINT8      Rsa3072Sig[384];
  UINT8      Scratch[832];       // 208 DWORDS = 832 BYTES Scratch Size
} ACM_HEADER_3;

#pragma pack(pop)

typedef struct {
  EFI_GUID Guid;
  UINT8   ChipsetAcmType;
  UINT8   AitVersion;
  UINT16  AitLength;
  UINT32  ChipsetIdList;
  UINT32  OsSinitTblVer;
  UINT32  MinMleHeaderVer;
  UINT32  SinitCaps;
  UINT8   SinitVersion;
  UINT8   AitRevision[3];
  UINT32  ProcessorIdList;
  UINT32  TpmInfoList;
} ACM_INFO_TABLE;

#endif
