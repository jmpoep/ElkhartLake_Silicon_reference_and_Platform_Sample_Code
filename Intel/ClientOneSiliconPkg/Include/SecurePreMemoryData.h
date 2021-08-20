/** @file
  Common Secure Pre-Memory Data Definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#ifndef _SECURE_PRE_MEMORY_DATA_H_
#define _SECURE_PRE_MEMORY_DATA_H_

#pragma pack(push, 1)

typedef struct _SECURE_PRE_MEMORY_DATA_TABLE SECURE_PRE_MEMORY_DATA_TABLE;

#define SECURE_PRE_MEMORY_DATA_TABLE_SIGNATURE                  SIGNATURE_32('S','P','M','D')
#define SECURE_PRE_MEMORY_DATA_UEFI_VAR_STORE_STRUCT_SIGNATURE  SIGNATURE_32('M','R','C','D')

#define SECURE_PRE_MEMORY_DATA_NOT_PRESENT_STRING    "_NO_PREMEM_DATA_"
#define SECURE_PRE_MEMORY_DATA_FIT_ENTRY_RSVD_TYPE   0x6

#define SECURE_PRE_MEMORY_DATA_MAX_TOTAL_LENGTH      SIZE_64KB
#define SECURE_PRE_MEMORY_DATA_HOB_FIT_SIZE          0x20
#define SECURE_PRE_MEMORY_DATA_MAX_DATA_LENGTH       (SECURE_PRE_MEMORY_DATA_MAX_TOTAL_LENGTH - \
                                                       sizeof (SECURE_PRE_MEMORY_DATA_TABLE) - \
                                                       SECURE_PRE_MEMORY_DATA_HOB_FIT_SIZE)

#define SECURE_PRE_MEMORY_DATA_UEFI_VAR_STORE_AREA_DATA_OFFSET  (sizeof (SECURE_PRE_MEMORY_DATA_TABLE))

typedef struct {
  UINT32        Signature;                       ///< Signature ID of the table
  UINT32        NumberOfSubStructures;           ///< Number of structures following this header
} SECURE_PRE_MEMORY_DATA_TABLE_HEADER;

typedef struct {
  UINT32        Signature;                       ///< Signature ID of the structure
  UINT32        Offset;                          ///< Offset from the beginning of the table
  UINT32        Length;                          ///< Length, in bytes, of the data represented by this structure
} SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE;

//
// Definition of the current Secure Pre-Memory Data Table
//
struct _SECURE_PRE_MEMORY_DATA_TABLE {
  SECURE_PRE_MEMORY_DATA_TABLE_HEADER   Header;               ///< Table header
  SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE  UefiVariableStore;    ///< UEFI variable pre-memory data structure
};

#pragma pack(pop)

#endif
