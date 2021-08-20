/** @file
  Implements DXE Storage Proxy Services.

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

#include "StorageProxy.h"

#include <Register/HeciRegs.h>
#include <StorageProxyMsg.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/StorageProxyLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/StorageProxyControl.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT                         mExitBootServicesEvent;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT                         mProxyTimerEvent;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HANDLE                        mImageHandle;
GLOBAL_REMOVE_IF_UNREFERENCED HECI_PROTOCOL                     *mHeciProtocol               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED STORAGE_PROXY_CONTROL_PROTOCOL    mStorageProxyControlProtocol = {
                                                                  StorageProxyControlResume,
                                                                  StorageProxyControlSuspend
                                                                  };
STATIC  STORAGE_PROXY_INFO    mStorageProxyInfo;

/**
  Resumes the storage proxy so that it handles storage proxy requests.

  @retval          EFI_SUCCESS            The storage proxy was resumed successfully.
  @retval          Others                 An error occurred resuming the storage proxy.

**/
EFI_STATUS
EFIAPI
StorageProxyControlResume (
  VOID
  )
{
  return gBS->SetTimer (
                mProxyTimerEvent,
                TimerPeriodic,
                PcdGet32 (PcdStorageProxyTimerInterval)
                );
}

/**
  Suspends the storage proxy such that it does not service requests until resumed.

  @retval          EFI_SUCCESS            The storage proxy was suspended successfully.
  @retval          Others                 An error occurred suspending the storage proxy.

**/
EFI_STATUS
EFIAPI
StorageProxyControlSuspend (
  VOID
  )
{
  return gBS->SetTimer (
                mProxyTimerEvent,
                TimerCancel,
                0
                );
}

/**
  Stops the storage proxy at Exit Boot Services.

  @param  Event                   Pointer to this event
  @param  Context                 Event handler private data

**/
VOID
EFIAPI
StorageProxyExitBootServicesCallback (
  EFI_EVENT  Event,
  VOID       *Context
  )
{
  EFI_HANDLE Handle;
  EFI_STATUS Status;

  Handle = NULL;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Preparing to close the storage proxy interface...\n"));
  Status = StorageProxyControlSuspend ();
  ASSERT_EFI_ERROR (Status);

  //
  // Notify consumers the BIOS Proxy is no longer available
  //
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gBiosStorageProxyTerminatedProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Send the one-shot Proxy Stop messge
  //
  Status = StorageProxyStop (&mStorageProxyInfo);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Storage Proxy: The proxy was stopped successfully.\n"));
  } else {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred stopping the proxy.\n"));
  }
}

/**
  Periodic timer handler that checks for any new storage proxy actions that need to be taken.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.

**/
VOID
EFIAPI
CheckStorageProxyHandler (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS   Status;
  EFI_TPL      OriginalTpl = 0;

  Status = StorageProxyControlSuspend ();
  ASSERT_EFI_ERROR (Status);

  do {
    //
    // Each action is responsible for setting the final action to CheckForRequest when done
    //
    if (mStorageProxyInfo.CurrentAction == NULL) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: Fatal Error - The storage proxy action is undefined.\n"));
      break;
    }
    if (
      (mStorageProxyInfo.CurrentAction != StorageProxyCheckForRequest) &&
      (mStorageProxyInfo.CurrentAction != StorageProxyProcessRequest) &&
      EfiGetCurrentTpl () > TPL_CALLBACK
    ) {
      //
      // Adjust TPL before invoking disk I/O
      //
      OriginalTpl = EfiGetCurrentTpl ();
      gBS->RestoreTPL (TPL_CALLBACK);
    }
    Status = mStorageProxyInfo.CurrentAction (&mStorageProxyInfo);
    if (OriginalTpl != 0) {
      gBS->RaiseTPL (OriginalTpl);
      OriginalTpl = 0;
    }
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      break;
    }
  } while (mStorageProxyInfo.CurrentAction != StorageProxyCheckForRequest);

  Status = StorageProxyControlResume ();
  ASSERT_EFI_ERROR (Status);
}

/**
  Starts the storage proxy.

  All dependencies for the storage proxy should be satisfied before starting the proxy.

**/
VOID
EFIAPI
StartStorageProxy (
  VOID
  )
{
  EFI_STATUS      Status;

  //
  // Send the one-shot Proxy Initialization message (initializes the StorageProxyInfo structure)
  //
  Status = StorageProxyInit (&mStorageProxyInfo);
  if (EFI_ERROR (Status)) {
    //
    // If an error occurred sending ProxyInit, do not start the polling interface.
    //
    ASSERT_EFI_ERROR (Status);
    return;
  }

  //
  // Send the one-shot Proxy Status message
  //
  Status = StorageProxyStatus (&mStorageProxyInfo);
  if (EFI_ERROR (Status)) {
    //
    // If an error occurred sending ProxyInit, do not start the polling interface.
    //
    ASSERT_EFI_ERROR (Status);
    return;
  }

  //
  // Register the timer event to check proxy status
  //
  DEBUG ((DEBUG_INFO, "Storage Proxy: Setting up the polling interface...\n"));
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  CheckStorageProxyHandler,
                  NULL,
                  &mProxyTimerEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = StorageProxyControlResume ();
  ASSERT_EFI_ERROR (Status);

  //
  // Install the Storage Proxy Control protocol
  //
  Status = gBS->InstallProtocolInterface (
                  &mImageHandle,
                  &gStorageProxyControlProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mStorageProxyControlProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Storage Proxy: The polling interface was successfully setup. The storage proxy is now active.\n"));
}

/**
  Initializes pre-requisites for the BIOS Storage Proxy.

  @retval     EFI_SUCCESS       The BIOS Storage Proxy was initialized successfully.
  @retval     EFI_NOT_FOUND     The HECI protocol could not be located.
  @retval     Others            An error occurred initializing the BIOS Storage Proxy.

**/
EFI_STATUS
EFIAPI
StartStorageProxyInitialization (
  VOID
  )
{
  EFI_STATUS    Status;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &mHeciProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "Storage Proxy: Located the HECI protocol. Attempting to initialize the storage proxy HECI device...\n"));

  //
  // Initialize the Storage Proxy HECI device
  //
  // This will ensure the storage proxy HECI device is in legacy/MSI interrupt mode,
  // that the ME_RDY bit is set, and that the H_RDY and H_IG bits are set.
  //
  DEBUG ((DEBUG_INFO, "Storage Proxy: Resetting the storage proxy HECI device...\n"));
  Status = mHeciProtocol->ResetHeci (STORAGE_PROXY_HECI_DEVICE);
  DEBUG ((DEBUG_INFO, "Storage Proxy: Status of HECI reset = %r.\n", Status));
  Status = mHeciProtocol->InitHeci (STORAGE_PROXY_HECI_DEVICE);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: HECI Protocol Error - Initializing the storage proxy HECI device.\n"));
    return Status;
  }

  DEBUG ((DEBUG_INFO, "Storage Proxy: HECI device initialization successful.\n"));

  StartStorageProxy ();

  return EFI_SUCCESS;
}

/**
  Notification event handler to start the Storage Proxy.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.

**/
VOID
EFIAPI
StartStorageProxyNotify (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS    Status;
  VOID          *Protocol;

  Status = gBS->LocateProtocol (
                  &gEfiVariableWriteArchProtocolGuid,
                  NULL,
                  &Protocol
                  );
  if (EFI_ERROR (Status)) {
    return;
  }
  gBS->CloseEvent (Event);

  Status = StartStorageProxyInitialization ();
  ASSERT_EFI_ERROR (Status);
}

/**
  Entry point the module that sets up storage proxy services.

  @param  ImageHandle  The image handle.
  @param  SystemTable  The system table.

  @retval EFI_SUCCESS  The protocol was installed successfully.
  @retval Others       Protocol could not be installed.
**/
EFI_STATUS
EFIAPI
StorageProxyEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status;
  VOID                  *Registration;
  EFI_HOB_GUID_TYPE     *GuidHob;
  HECI_FWS_REGISTER     MeFirmwareStatus;

  MeFirmwareStatus.ul = PciSegmentRead32 (
                          PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS)
                          );

  if (BootMediaIsSpi ()) {
    DEBUG ((EFI_D_INFO, "Storage Proxy: The proxy will not be established for SPI boot.\n"));
    return EFI_SUCCESS;
  }

  mImageHandle = ImageHandle;

  //
  // Register for Exit Boot Services notification
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  StorageProxyExitBootServicesCallback,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &mExitBootServicesEvent
                  );
  ASSERT_EFI_ERROR (Status);

  GuidHob = GetFirstGuidHob (&gEfiAuthenticatedVariableGuid);
  if (GuidHob == NULL) {
    GuidHob = GetFirstGuidHob (&gEfiVariableGuid);
  }

  if (GuidHob == NULL) {
    //
    // Register for Variable Architectural Write protocol notification
    // if the variable HOB does not need to be flushed
    // (HOB is flushed before gEfiVariableWriteArchProtocolGuid is installed)
    //
    EfiCreateProtocolNotifyEvent (
      &gEfiVariableWriteArchProtocolGuid,
      TPL_CALLBACK,
      StartStorageProxyNotify,
      NULL,
      &Registration
      );
  } else {
    Status = StartStorageProxyInitialization ();
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}
