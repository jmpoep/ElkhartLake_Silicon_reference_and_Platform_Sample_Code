//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The HID Keyboard Driver is used to manage all HID KB devices.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "HidKbDxe.h"
#include "KeyBoard.h"

EFI_DRIVER_BINDING_PROTOCOL gHidKbDriverBinding = {
  HidKbDriverBindingSupported,
  HidKbDriverBindingStart,
  HidKbDriverBindingStop,
  0xa,
  NULL,
  NULL
};

EFI_SIMPLE_TEXT_INPUT_PROTOCOL     mSimpleTextIn = {
  HidKbReset,
  HidKbReadKeyStroke,
  NULL,
};

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     mSimpleTextInEx = {
  HidKbResetEx,
  HidKbReadKeyStrokeEx,
  NULL,
  HidKbSetState,
  HidKbRegisterKeyNotify,
  HidKbUnregisterKeyNotify,
};

/**
  Entrypoint of HID KB Driver.

  This function is the entrypoint of HID KB Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
HidKbDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gHidKbDriverBinding,
             ImageHandle,
             &gHidKbComponentName,
             &gHidKbComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


/**
  Check whether HID KB driver supports this device.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
HidKbDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EDKII_HID_PROTOCOL        *Hid;
  EDKII_HID_INFO            HidInfo;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEdkiiHidProtocolGuid,
                  (VOID **) &Hid,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Use the HID Protocol interface to check whether Controller is
  // a HID KB device that can be managed by this driver.
  //
  Status = Hid->GetDeviceInfo (Hid, &HidInfo);

  gBS->CloseProtocol (
        Controller,
        &gEdkiiHidProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (HidInfo.HidType != HidTypeKeyBoard) {
    return EFI_UNSUPPORTED;
  }

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_ERROR, "HidKbDriverBindingSupported: %r\n", Status));

  return Status;
}


/**
  Starts the HID KB device with this driver.

  This function consumes Hid I/O Portocol, intializes HID KB device,
  installs SimpleTextIn Protocol.

  @param  This                  The HID KB driver binding instance.
  @param  Controller            Handle of device to bind driver to.
  @param  RemainingDevicePath   Optional parameter use to pick a specific child
                                device to start.

  @retval EFI_SUCCESS           This driver supports this device.
  @retval EFI_UNSUPPORTED       This driver does not support this device.
  @retval EFI_DEVICE_ERROR      This driver cannot be started due to device Error.
  @retval EFI_OUT_OF_RESOURCES  Can't allocate memory resources.
  @retval EFI_ALREADY_STARTED   This driver has been started.

**/
EFI_STATUS
EFIAPI
HidKbDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                  Status;
  EDKII_HID_PROTOCOL          *Hid;
  HID_KB_DEV                  *HidKbDev;
  EFI_DEVICE_PATH             *DevicePath;


  DEBUG ((EFI_D_ERROR, "HidKbDriverBindingStart: Enter\n"));

  HidKbDev = NULL;

  //
  // Open Hid I/O Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEdkiiHidProtocolGuid,
                  (VOID **) &Hid,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit1;
  }

  //
  // Get the Device Path Protocol on Controller's handle
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  HidKbDev = AllocateZeroPool (sizeof (HID_KB_DEV));
  ASSERT (HidKbDev != NULL);

  HidKbDev->Signature         = HID_KB_DEV_SIGNATURE;
  HidKbDev->Hid       = Hid;
  CopyMem (&HidKbDev->SimpleTextIn, &mSimpleTextIn, sizeof(mSimpleTextIn));
  CopyMem (&HidKbDev->SimpleTextInEx, &mSimpleTextInEx, sizeof(mSimpleTextInEx));
  HidKbDev->ControllerHandle  = Controller;

  InitializeListHead (&HidKbDev->NotifyList);

  Status = Hid->Start (Hid, NULL, NULL, KeyboardHandler, HidKbDev);
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  HidKbTimerHandler,
                  HidKbDev,
                  &HidKbDev->TimerEvent
                  );
  if (!EFI_ERROR (Status)) {
    Status = gBS->SetTimer (HidKbDev->TimerEvent, TimerPeriodic, KEYBOARD_TIMER_INTERVAL);
  }
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_NOTIFY,
                  HidKbWaitForKey,
                  HidKbDev,
                  &(HidKbDev->SimpleTextInEx.WaitForKeyEx)
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_NOTIFY,
                  HidKbWaitForKey,
                  HidKbDev,
                  &(HidKbDev->SimpleTextIn.WaitForKey)
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiSimpleTextInProtocolGuid,
                  &HidKbDev->SimpleTextIn,
                  &gEfiSimpleTextInputExProtocolGuid,
                  &HidKbDev->SimpleTextInEx,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = InitKeyboardLayout (HidKbDev);
  if (EFI_ERROR (Status)) {
    gBS->UninstallMultipleProtocolInterfaces (
      Controller,
      &gEfiSimpleTextInProtocolGuid,
      &HidKbDev->SimpleTextIn,
      &gEfiSimpleTextInputExProtocolGuid,
      &HidKbDev->SimpleTextInEx,
      NULL
      );
    goto ErrorExit;
  }

  //
  // Reset HID Keyboard Device exhaustively.
  //
  Status = HidKbDev->SimpleTextInEx.Reset (
                                     &HidKbDev->SimpleTextInEx,
                                     TRUE
                                     );
  if (EFI_ERROR (Status)) {
    gBS->UninstallMultipleProtocolInterfaces (
           Controller,
           &gEfiSimpleTextInProtocolGuid,
           &HidKbDev->SimpleTextIn,
           &gEfiSimpleTextInputExProtocolGuid,
           &HidKbDev->SimpleTextInEx,
           NULL
           );
    goto ErrorExit;
  }

  //
  // Open For Child Device
  //

  HidKbDev->ControllerNameTable = NULL;
  AddUnicodeString2 (
    "eng",
    gHidKbComponentName.SupportedLanguages,
    &HidKbDev->ControllerNameTable,
    L"Generic Hid Keyboard",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gHidKbComponentName2.SupportedLanguages,
    &HidKbDev->ControllerNameTable,
    L"Generic Hid Keyboard",
    FALSE
    );

//  gBS->RestoreTPL (OldTpl);

  DEBUG ((EFI_D_ERROR, "HidKbDriverBindingStart: Exit\n"));

  return EFI_SUCCESS;

//
// Error handler
//
ErrorExit:
  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
          Controller,
          &gEdkiiHidProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );

    if (HidKbDev != NULL) {
      if (HidKbDev->TimerEvent != NULL) {
        gBS->CloseEvent (HidKbDev->TimerEvent);
      }
      if (HidKbDev->SimpleTextIn.WaitForKey != NULL) {
        gBS->CloseEvent (HidKbDev->SimpleTextIn.WaitForKey);
      }
      if (HidKbDev->SimpleTextInEx.WaitForKeyEx != NULL) {
        gBS->CloseEvent (HidKbDev->SimpleTextInEx.WaitForKeyEx);
      }
      if (HidKbDev->KeyboardLayoutEvent != NULL) {
        ReleaseKeyboardLayoutResources (HidKbDev);
        gBS->CloseEvent (HidKbDev->KeyboardLayoutEvent);
      }
      FreePool (HidKbDev);
      HidKbDev = NULL;
    }
  }

ErrorExit1:
//  gBS->RestoreTPL (OldTpl);

  DEBUG ((EFI_D_ERROR, "HidKbDriverBindingStart: Exit - %r\n", Status));
  return Status;
}


/**
  Stop the HID KB device handled by this driver.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        SimpleTextIn Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
HidKbDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                  Status;
  HID_KB_DEV                   *HidKbDev;
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *SimpleTextIn;

  DEBUG ((DEBUG_INFO, "%a: Enter\n", __FUNCTION__));

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSimpleTextInProtocolGuid,
                  (VOID **) &SimpleTextIn,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSimpleTextInputExProtocolGuid,
                  NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_PROTOCOL (SimpleTextIn);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  Controller,
                  &gEfiSimpleTextInProtocolGuid,
                  &HidKbDev->SimpleTextIn,
                  &gEfiSimpleTextInputExProtocolGuid,
                  &HidKbDev->SimpleTextInEx,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBS->CloseProtocol (
         Controller,
         &gEdkiiHidProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );
  //
  // Free all resources.
  //
  gBS->CloseEvent (HidKbDev->TimerEvent);
  gBS->CloseEvent (HidKbDev->RepeatTimer);
  gBS->CloseEvent (HidKbDev->SimpleTextIn.WaitForKey);
  gBS->CloseEvent (HidKbDev->SimpleTextInEx.WaitForKeyEx);
  KbdFreeNotifyList (&HidKbDev->NotifyList);

  ReleaseKeyboardLayoutResources (HidKbDev);
  gBS->CloseEvent (HidKbDev->KeyboardLayoutEvent);

  if (HidKbDev->ControllerNameTable != NULL) {
    FreeUnicodeStringTable (HidKbDev->ControllerNameTable);
  }

  DestroyQueue (&HidKbDev->HidKeyQueue);
  DestroyQueue (&HidKbDev->EfiKeyQueue);

  FreePool (HidKbDev);

  DEBUG ((DEBUG_INFO, "%a: Exit\n", __FUNCTION__));
  return EFI_SUCCESS;

}



