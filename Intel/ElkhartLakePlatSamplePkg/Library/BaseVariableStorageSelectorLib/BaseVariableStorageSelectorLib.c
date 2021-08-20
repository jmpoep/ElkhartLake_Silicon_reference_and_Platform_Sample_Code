/** @file
  Base Variable Storage Selector Library

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#include <Library/PcdLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/VariableStorageSelectorLib.h>

#include "BaseVariableStorageSelectorLib.h"

//
// NOTE: Dynamic PCDs cannot be consumed in this library due to
//       lock conflicts with the variable driver.
//

/**
  Gets the variable storage instance type for the variable storage instance
  that is used to store a given variable

  @param[in]  VariableName        A pointer to a null-terminated string that is
                                  the variable's name.
  @param[in]  VariableGuid        A pointer to an EFI_GUID that is the variable's
                                  GUID. The combination of VariableGuid and
                                  VariableName must be unique.
  @param[out] VariableStorageType The type for the variable storage instance that
                                  stores a given variable

  @retval EFI_SUCCESS           Variable storage instance type was retrieved
**/
EFI_STATUS
EFIAPI
GetVariableStorageType (
  IN  CONST  CHAR16                 *VariableName,
  IN  CONST  EFI_GUID               *VendorGuid,
  OUT        VARIABLE_STORAGE_TYPE  *VariableStorageType
  )
{
  if (!BootMediaIsKnown ()) {
    DEBUG ((DEBUG_ERROR, "The boot media unknown! Variable storage is unknown!\n"));
    ASSERT (FALSE);
    CpuDeadLoop ();
  } else if (BootMediaIsSpi ()) {
    *VariableStorageType = VariableStorageFvb;
  } else {
    *VariableStorageType = VariableStorageCse;
  }

  return EFI_SUCCESS;
}
