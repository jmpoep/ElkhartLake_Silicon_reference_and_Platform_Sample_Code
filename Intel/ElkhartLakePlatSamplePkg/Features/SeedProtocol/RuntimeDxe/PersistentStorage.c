/** @file
  This file contains the persistent storage code for Seed Protocol DXE driver.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification

**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include "PersistentStorage.h"
#include <Guid/GlobalVariable.h>

#define UEFI_SECURE_BOOT_DISABLE                  (0)

/* Constant data */
STATIC CONST UINT32             VarAttr    = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;

/**
  Determine if UEFI secure boot is enabled

  @retval TRUE  UEFI secure boot is enabled.
  @retval FALSE UEFI secure boot is disabled.

**/
BOOLEAN
IsUEFISecureBootEnabled (
  VOID
)
{
  EFI_STATUS  Status;
  UINT8       SecureBoot;
  UINTN       VarSize = sizeof(UINT8);

  Status = gRT->GetVariable (
              EFI_SECURE_BOOT_MODE_NAME,
              &gEfiGlobalVariableGuid,
              NULL,
              &VarSize,
              &SecureBoot
              );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return (SecureBoot != UEFI_SECURE_BOOT_DISABLE);
}

/**
  Load data from variable store (persistent storage).

  @param[in]        VarName      Name of data to load.
  @param[out]       Buffer       Buffer to receive data.
  @param[in out]    BufferSize   Size of buffer receiving data.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_NOT_FOUND          The seed sault was not found in persistent storage.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
EFI_STATUS
LoadPersistentData (
  CONST IN UINT16 *VarName,
  OUT UINT8       *Buffer,
  IN OUT UINTN    *BufferSize
)
{
  EFI_STATUS Status;

  ASSERT (Buffer != NULL);

  Status = gRT->GetVariable (
      (CHAR16 *)VarName,
      &gEfiGlobalVariableGuid,
      NULL,
      BufferSize,
      Buffer
      );

  return Status;
}

/**
  Save data to to variable store (persistent storage).

  @param[in]        VarName      Name of data to store.
  @param[in]        Buffer       Buffer to data to store.
  @param[in]        BufferSize   Size of buffer data.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
EFI_STATUS
SavePersistentData (
  CONST IN UINT16 *VarName,
  IN CONST UINT8   *Buffer,
  IN CONST UINTN   BufferSize
)
{
  EFI_STATUS Status;

  ASSERT (Buffer != NULL);

  Status = gRT->SetVariable (
      (CHAR16 *)VarName,
      &gEfiGlobalVariableGuid,
      VarAttr,
      BufferSize,
      (VOID *)Buffer
      );

  return Status;
}
