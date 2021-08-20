/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _BIOS_INFO_H_
#define _BIOS_INFO_H_

//
// BIOS INFO data structure
// This is self contained data structure for BIOS info for TXT
//
#pragma pack (1)
#define BIOS_INFO_SIGNATURE  SIGNATURE_64 ('$', 'B', 'I', 'O', 'S', 'I', 'F', '$')
typedef struct {
  UINT64            Signature;
  UINT32            EntryCount;
  UINT32            Reserved;
//BIOS_INFO_STRUCT  Struct[EntryCount];
} BIOS_INFO_HEADER;

//
// BIOS_INFO_STRUCT attributes
// bits[0:3] means general attributes
// bits[4:7] means type specific attributes
//
#define BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT  0x01
#define BIOS_INFO_STRUCT_ATTRIBUTE_MICROCODE_WHOLE_REGION    0x10
#define BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB             0x10
#define BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_NON_IBB              0x20

typedef struct {
  //
  // FitTable entry type
  //
  UINT8    Type;
  //
  // BIOS_INFO_STRUCT attributes
  //
  UINT8    Attributes;
  //
  // FitTable entry version
  //
  UINT16   Version;
  //
  // FitTable entry real size
  //
  UINT32   Size;
  //
  // FitTable entry address
  //
  UINT64   Address;
} BIOS_INFO_STRUCT;

#pragma pack ()

#endif
