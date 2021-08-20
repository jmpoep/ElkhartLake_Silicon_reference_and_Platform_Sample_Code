/** @file
  CSE Variable Storage Selector Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _CSE_VARIABLE_STORAGE_SELECTOR_LIB_H_
#define _CSE_VARIABLE_STORAGE_SELECTOR_LIB_H_

#include <Uefi.h>
#include <CseVariableStorage.h>

/**
  Returns the CSE NVM storage type used for the requested variable.

  @param[in] VariableName               Name of the variable.
  @param[in] VendorGuid                 GUID of the variable.
  @param[in] CseVariableStorageInfo     An array of pointers to CSE variable storage store information.

  @retval    CSE_VARIABLE_STORAGE_TYPE  The type of CSE storage used for this variable.
**/
CSE_VARIABLE_STORAGE_TYPE
EFIAPI
GetCseVariableStoreStorageType (
  IN CONST CHAR16                      *VariableName,
  IN CONST EFI_GUID                    *VendorGuid,
  IN CONST CSE_VARIABLE_STORAGE_STORE   **CseVariableStorageInfo
  );

#endif
