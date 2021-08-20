/** @file
  Library instance to lock Seamless Recovery relative variables

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/
#include <Library/SeamlessRecoverySupportLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/VariableLock.h>

/**
  The constructor function of SeamlessRecoveryVarLockLib.

  @param[in]  ImageHandle   The firmware allocated handle for the EFI image.
  @param[in]  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor successfully .
**/
EFI_STATUS
EFIAPI
SeamlessRecoveryVarLockLibConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                                      Status;
  EDKII_VARIABLE_LOCK_PROTOCOL                    *VariableLock;

  //
  // Lock variables related to update progress and backup file.
  //
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **)&VariableLock);
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, SYSFW_UPDATE_PROGRESS_VARIABLE_NAME, &gSysFwUpdateProgressGuid);
    ASSERT_EFI_ERROR (Status);
    Status = VariableLock->RequestToLock (VariableLock, SYSFW_UPDATE_CAPSULE_DIGEST_VARIABLE_NAME, &gSysFwUpdateProgressGuid);
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
