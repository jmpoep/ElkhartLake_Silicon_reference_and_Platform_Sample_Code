//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Platform status code implementation.

Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "PlatformStatusCodeHandlerRuntimeDxe.h"

EFI_RSC_HANDLER_PROTOCOL  *mRscHandlerProtocol       = NULL;
EFI_EVENT                 mExitBootServicesEvent     = NULL;

/**
  Unregister status code callback functions only available at boot time from
  report status code router when exiting boot services.

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.

**/
VOID
EFIAPI
UnregisterBootTimeHandlers (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  if (PcdGetBool (PcdStatusCodeUseRam)) {
    mRscHandlerProtocol->Unregister (RamStatusCodeReportWorker);
  }

  if (PcdGetBool (PcdStatusCodeUseUsb3)) {
    mRscHandlerProtocol->Unregister (Usb3StatusCodeReportWorker);
  }

  if (PcdGetBool (PcdStatusCodeUseSerialIoUart)) {
    mRscHandlerProtocol->Unregister (SerialIoUartStatusCodeReportWorker);
  }
}

/**
  Entry point of DXE Status Code Driver.

  This function is the entry point of this DXE Status Code Driver.
  It initializes registers status code handlers, and registers event for EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
StatusCodeHandlerRuntimeDxeEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                 Status;
  UINT8                      StatusCodeFlags;

  Status = gBS->LocateProtocol (
                  &gEfiRscHandlerProtocolGuid,
                  NULL,
                  (VOID **) &mRscHandlerProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  StatusCodeFlags = GetDebugInterface ();

  if (PcdGetBool (PcdStatusCodeUseRam)) {
    if (StatusCodeFlags & STATUS_CODE_USE_RAM) {
      RamDebugInitialize ();
    }
    mRscHandlerProtocol->Register (RamStatusCodeReportWorker, TPL_HIGH_LEVEL);
  }

  if (PcdGetBool (PcdStatusCodeUseUsb3)) {
    if (StatusCodeFlags & STATUS_CODE_USE_USB3) {
      Status = Usb3DebugPortInitialize ();
      ASSERT_EFI_ERROR (Status);
    }
    mRscHandlerProtocol->Register (Usb3StatusCodeReportWorker, TPL_HIGH_LEVEL);
  }

  if (PcdGetBool (PcdStatusCodeUseSerialIoUart)) {
    if (StatusCodeFlags & STATUS_CODE_USE_SERIALIO) {
      SerialIoUartDebugInit ();
    }
    mRscHandlerProtocol->Register (SerialIoUartStatusCodeReportWorker, TPL_HIGH_LEVEL);
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  UnregisterBootTimeHandlers,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &mExitBootServicesEvent
                  );

  return EFI_SUCCESS;
}
