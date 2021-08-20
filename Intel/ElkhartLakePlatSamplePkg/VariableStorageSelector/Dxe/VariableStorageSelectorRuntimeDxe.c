/** @file
  Variable Storage Selector DXE Module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/VariableStorageSelectorLib.h>
#include <Protocol/VariableStorageSelectorProtocol.h>

#include <Guid/CseVariableStorageProtocolInstanceGuid.h>
#include <Guid/FvbVariableStorageProtocolInstanceGuid.h>

//
// NOTE: Dynamic PCDs cannot be consumed in the CSE Variable Storage
//       Selector Protocol due to lock conflicts with the variable driver.
//
STATIC BOOLEAN     mEnableFvbVariableStorage;
STATIC BOOLEAN     mEnableCseVariableStorage;

/**
  Gets the variable storage instance ID for the variable storage instance
  that is used to store a given variable

  @param[in]  VariableName      A pointer to a null-terminated string that is
                                the variable's name.
  @param[in]  VariableGuid      A pointer to an EFI_GUID that is the variable's
                                GUID. The combination of VariableGuid and
                                VariableName must be unique.
  @param[out] VariableStorageId The ID for the variable storage instance that
                                stores a given variable

  @retval EFI_SUCCESS           Variable storage instance id was retrieved
**/
EFI_STATUS
EFIAPI
GetVariableStorageId (
  IN  CONST  CHAR16       *VariableName,
  IN  CONST  EFI_GUID     *VendorGuid,
  OUT        EFI_GUID     *VariableStorageId
  )
{
  EFI_STATUS              Status;
  VARIABLE_STORAGE_TYPE   VariableStorageType;

  Status = GetVariableStorageType (VariableName, VendorGuid, &VariableStorageType);
  if (!EFI_ERROR (Status)) {
    if (VariableStorageType == VariableStorageFvb) {
      if (!mEnableFvbVariableStorage) {
        DEBUG ((DEBUG_ERROR, "FVB variable storage is disabled with variable dependencies.\n"));
        Status = EFI_NOT_FOUND;
      } else {
        CopyMem (VariableStorageId, &gFvbVariableStorageProtocolInstanceGuid, sizeof (EFI_GUID));
      }
    } else if (VariableStorageType == VariableStorageCse) {
      if (!mEnableCseVariableStorage) {
        DEBUG ((DEBUG_ERROR, "CSE variable storage is disabled with variable dependencies.\n"));
        Status = EFI_NOT_FOUND;
      } else {
        CopyMem (VariableStorageId, &gCseVariableStorageProtocolInstanceGuid, sizeof (EFI_GUID));
      }
    } else {
      Status = EFI_NOT_FOUND;
    }
  }

  return Status;
}

EDKII_VARIABLE_STORAGE_SELECTOR_PROTOCOL mVariableStorageSelectorProtocol = {
  GetVariableStorageId
};

/**
  Installs Variable Storage Selector services.

  The Variable Storage Selector Protocol is consumed by the Variable DXE driver. It
  controls which specific Variable Storage Protocol is used to store a variable.

  @param      None

  @retval     EFI_SUCCESS  Variable Storage Selector services were sucessfully installed / reinstalled.
  @retval     EFI_ERROR    Variable Storage Selector services were not installed / reinstalled.
**/
EFI_STATUS
EFIAPI
VariableStorageSelectorRuntimeDxeInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  mEnableCseVariableStorage = PcdGetBool (PcdEnableCseVariableStorage);
  mEnableFvbVariableStorage = PcdGetBool (PcdEnableFvbVariableStorage);

  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gEdkiiVariableStorageSelectorProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mVariableStorageSelectorProtocol
                );
}