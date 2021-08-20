/** @file
  This is the Fsp driver that initializes the Intel System Agent.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/UefiBootServicesTableLib.h>
#include "SaInit.h"
#include <SaConfigHob.h>
#include <Protocol/PciEnumerationComplete.h>

/**
  This function gets registered as a callback to perform SA configuration security lock

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SaOnPciEnumerationCompleteDxeFsp (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

/**
  This function locks the PAM register as part of the SA Security requirements.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.

**/
VOID
EFIAPI
SaPamLockDxeFsp (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

///
/// Global Variables
///
extern SA_CONFIG_HOB                *mSaConfigHob;

/**
  SystemAgent Fsp Initialization.

  @param[in] ImageHandle             Handle for the image of this driver
  @param[in] SystemTable             Pointer to the EFI System Table

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
EFIAPI
SaInitEntryPointDxeFsp (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                Status;
  VOID                      *Registration;
  EFI_EVENT                 Event;

  DEBUG ((DEBUG_INFO, "SaInitEntryPointDxeFsp Start\n"));

  SaInitEntryPoint ();

  ///
  /// Create PCI Enumeration Completed callback for SA
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    SaOnPciEnumerationCompleteDxeFsp,
    NULL,
    &Registration
    );

  DEBUG ((DEBUG_INFO, "RegisterForExitBootService() to set PAM lock before OS handoff\n"));
  Status = EfiCreateEventLegacyBootEx (
             TPL_CALLBACK,
             SaPamLockDxeFsp,
             NULL,
             &Event
             );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_CALLBACK,
                  SaPamLockDxeFsp,
                  NULL,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SaInitEntryPointDxeFsp End\n"));

  return EFI_SUCCESS;
}

/**
  This function gets registered as a callback to perform SA configuration security lock

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
SaOnPciEnumerationCompleteDxeFsp (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  return;
}

/**
  This function locks the PAM register as part of the SA Security requirements.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.

**/
VOID
EFIAPI
SaPamLockDxeFsp (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  DEBUG ((DEBUG_INFO, "SaPamLockDxeFsp Start\n"));

  SaPamLock ();

  DEBUG ((DEBUG_INFO, "SaPamLockDxeFsp End\n"));
}
