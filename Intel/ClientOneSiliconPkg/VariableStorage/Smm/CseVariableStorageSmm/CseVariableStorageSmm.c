/** @file
  Implements CSE Variable Storage Services and installs
  an instance of the VariableStorage Runtime DXE protocol.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "CseVariableStorageInternal.h"

#include <CseVariableStorageCommandQueue.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/VariableNvmStorageLib.h>


EFI_HANDLE  mCseSmmVariableHandle = NULL;

EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL       *mVariableStorageSupportProtocol  = NULL;
extern CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL  mCseVarStorageSupportProtocol;

/**
  EDKII Variable Storage Support Protocol notification callback.

  @param   Protocol      Points to the protocol's unique identifier
  @param   Interface     Points to the interface instance
  @param   Handle        The handle on which the interface was installed

  @retval  EFI_SUCCESS   The callback function ran successfully
  @retval  EFI_NOT_FOUND The EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL could not be found
**/
EFI_STATUS
EFIAPI
VariableStorageSupportProtocolCallback (
  IN CONST EFI_GUID      *Protocol,
  IN VOID                *Interface,
  IN EFI_HANDLE          Handle
  )
{
  EFI_STATUS         Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEdkiiVariableStorageSupportProtocolGuid,
                    NULL,
                    (VOID **) &mVariableStorageSupportProtocol
                    );
  ASSERT_EFI_ERROR (Status);
  if (mVariableStorageSupportProtocol == NULL) {
    return EFI_NOT_FOUND;
  }
  CseVariableStorageUpdateCache();

  if (PcdGetBool (PcdEnableVariableConfigInCseRecoveryMode)) {
    PcdSetBool (PcdEnableCseVariableStorage, FALSE);
    PcdSetBool (PcdNvVariableEmulationMode, TRUE);
    Status = gSmst->SmmInstallProtocolInterface (
                      &Handle,
                      &gEnableEmulationModeInCseRecoveryProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      NULL
                      );
    ASSERT_EFI_ERROR (Status);
  }
  return Status;
}

/**
  Notifies the CSE variable driver that the runtime component of the driver is initialized.

**/
VOID
EFIAPI
CseVariableStorageRuntimeInitialized (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  Handle  = NULL;
  VOID        *EdkiiVariableStorageSupportProtocolRegistration;

  Status = CseVariableStorageCommonInitialize ();
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return;
  }

  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEdkiiVariableStorageSupportProtocolGuid,
                    VariableStorageSupportProtocolCallback,
                    &EdkiiVariableStorageSupportProtocolRegistration
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmInstallProtocolInterface (
                    &Handle,
                    &gEdkiiVariableStorageProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mCseVariableStorageProtocol
                    );
  ASSERT_EFI_ERROR (Status);
}

/**
  Provide SMM functionality of CSE NVM variable storage services.

  @param  ImageHandle  The image handle.
  @param  SystemTable  The system table.

  @retval EFI_SUCCESS  The protocol was installed successfully.
  @retval Others       Protocol could not be installed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageSmmInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_HANDLE    Handle  = NULL;

  if (!PcdGetBool (PcdEnableCseVariableStorage) || PcdGetBool (PcdNvVariableEmulationMode)) {
    DEBUG ((DEBUG_INFO, "CSE Variable Storage module is disabled due to variable configuration.\n"));
    return EFI_SUCCESS;
  }

  Status = gSmst->SmmInstallProtocolInterface (
                    &Handle,
                    &gCseVariableStorageSupportProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mCseVarStorageSupportProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Notify the Runtime DXE wrapper driver CSE SMM variable services are ready
  //
  DEBUG ((DEBUG_INFO, "Notifying modules CSE Variable Storage SMM services are available.\n"));
  Status = SystemTable->BootServices->InstallProtocolInterface (
                                        &mCseSmmVariableHandle,
                                        &gCseVariableSmmReadyProtocolGuid,
                                        EFI_NATIVE_INTERFACE,
                                        NULL
                                        );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
