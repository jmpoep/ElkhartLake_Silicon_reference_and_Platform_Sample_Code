/** @file
  HECI driver services for SMM.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "HeciRuntime.h"
#include <Library/SmmServicesTableLib.h>

#include <Protocol/SmmExitBootServices.h>
#include <Protocol/SmmReadyToLock.h>

BOOLEAN                     mAtRuntime;
HECI_RUNTIME_DEVICE_CONTEXT mHeciDeviceContext[HeciMax];

/**
  SMM Exit Boot Services event notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler runs successfully.
**/
EFI_STATUS
EFIAPI
HeciSmmExitBootServicesEventNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  mAtRuntime = TRUE;

  return EFI_SUCCESS;
}

/**
  SMM Ready To Lock event notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler runs successfully.
**/
EFI_STATUS
EFIAPI
HeciSmmReadyToLockEventNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  UINT32  DeviceIndex;

  ///
  /// Update global HECI device context (post-PCI enumeration)
  ///
  DEBUG ((DEBUG_INFO, "HECI device status at SMM Ready to Lock.\n"));
  for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
    CheckAndFixHeciForAccess (DeviceIndex);

    DEBUG ((DEBUG_INFO, "HECI Device: HECI%d.\n", (DeviceIndex + 1)));
    DEBUG ((DEBUG_INFO, "HECI Base Address: 0x%x.\n", mHeciDeviceContext[DeviceIndex].BaseAddress));
    DEBUG ((DEBUG_INFO, "HECI BAR Address: 0x%x.\n", mHeciDeviceContext[DeviceIndex].Bar0Address));
  }

  return EFI_SUCCESS;
}

/**
  Constructor for the SMM HECI Runtime library.

  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
HeciRuntimeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  VOID       *SmmExitBootServicesRegistration;
  VOID       *SmmReadyToLockRegistration;

  InitializeHeciDeviceContext ();

  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmReadyToLockProtocolGuid,
                    HeciSmmReadyToLockEventNotify,
                    &SmmReadyToLockRegistration
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEdkiiSmmExitBootServicesProtocolGuid,
                    HeciSmmExitBootServicesEventNotify,
                    &SmmExitBootServicesRegistration
                    );
  ASSERT_EFI_ERROR (Status);

  return Status;
}