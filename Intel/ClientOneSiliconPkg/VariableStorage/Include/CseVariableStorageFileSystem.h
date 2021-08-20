/** @file
  CSE Variable Storage File System Declarations

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017-2018 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_FILE_SYSTEM_H_
#define _CSE_VARIABLE_STORAGE_FILE_SYSTEM_H_

#include <Base.h>
#include <Uefi.h>

//
// CSE Variable Storage File System Definitions
//
#define CSE_VARIABLE_STORAGE_FILE_SYSTEM_ENABLED                FALSE
#define CSE_VARIABLE_STORAGE_FILE_SYSTEM_MAX_FILE_SIZE          SIZE_64KB
#define CSE_VARIABLE_STORAGE_FILE_SYSTEM_MAX_DATA_LENGTH        SIZE_512KB
#define CSE_VARIABLE_STORAGE_MAX_FILE_NAME_LENGTH               25

#define CSE_VARIABLE_STORAGE_FILE_SYSTEM_MAX_FILES              256
#define CSE_PRIMARY_INDEX_FILE_NAME                             L"NVS/INDEX"
#define CSE_PRIMARY_NVM_DATA_FILE_PREFIX                        "NVS/VAR_"
#define CSE_VARIABLE_STORAGE_FILE_SYSTEM_STORE_OFFSET           0

typedef struct {
  CHAR8         *IndexFileName;      ///< The index file name (ASCII)
  EFI_GUID      *IndexFileHobGuid;   ///< Pointer to the GUID of the HOB that contains the index file data
} CSE_VARIABLE_STORAGE_FILE_SYSTEM_INFO;

#endif
