//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  HID Mouse Driver that manages HID mouse and produces Simple Pointer Protocol.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "HidMouseDxe.h"

EFI_DRIVER_BINDING_PROTOCOL gHidMouseDriverBinding = {
  HidMouseDriverBindingSupported,
  HidMouseDriverBindingStart,
  HidMouseDriverBindingStop,
  0xa,
  NULL,
  NULL
};

/**
  Entrypoint of BT Mouse Driver.

  This function is the entrypoint of BT Mouse Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
HidMouseDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gHidMouseDriverBinding,
             ImageHandle,
             &gHidMouseComponentName,
             &gHidMouseComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


/**
  Check whether BT mouse driver supports this device.

  @param  This                   The BT mouse driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
HidMouseDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS          Status;
  EDKII_HID_PROTOCOL  *HidProtocol;
  EDKII_HID_INFO      HidInfo;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEdkiiHidProtocolGuid,
                  (VOID **) &HidProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Use the Bluetooth HID Protocol interface to check whether Controller is
  // a mouse device that can be managed by this driver.
  //

  Status = HidProtocol->GetDeviceInfo (HidProtocol, &HidInfo);

  gBS->CloseProtocol (
        Controller,
        &gEdkiiHidProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (HidInfo.HidType != HidTypeMouse) {
    return EFI_UNSUPPORTED;
  }

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_ERROR, "HidMouseDriverBindingSupported: %r\n", Status));

  return Status;
}


/**
  Starts the mouse device with this driver.

  This function consumes Bluetooth HID Portocol, intializes BT mouse device,
  installs Simple Pointer Protocol, and submits Asynchronous Interrupt
  Transfer to manage the BT mouse device.

  @param  This                  The BT mouse driver binding instance.
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
HidMouseDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                  Status;
  EDKII_HID_PROTOCOL          *HidProtocol;
  BT_MOUSE_DEV                *BtMouseDevice;


  DEBUG ((EFI_D_ERROR, "HidMouseDriverBindingStart: Enter\n"));
  //
  // Open Bluetooth HID Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEdkiiHidProtocolGuid,
                  (VOID **) &HidProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit1;
  }

  BtMouseDevice = AllocateZeroPool (sizeof (BT_MOUSE_DEV));
  ASSERT (BtMouseDevice != NULL);

  BtMouseDevice->Signature = BT_MOUSE_DEV_SIGNATURE;
  BtMouseDevice->HidProtocol     = HidProtocol;

  //
  // Initialize and install EFI Simple Pointer Protocol.
  //
  BtMouseDevice->SimplePointerProtocol.GetState  = BtGetMouseState;
  BtMouseDevice->SimplePointerProtocol.Reset     = BtMouseReset;
  BtMouseDevice->SimplePointerProtocol.Mode      = &BtMouseDevice->Mode;

  //InitializeBtMouse (BtMouseDevice);

  Status = HidProtocol->Start (HidProtocol, NULL, NULL, OnMouseInterruptComplete, BtMouseDevice);
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = InitializeBtMouseDevice (BtMouseDevice);
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_NOTIFY,
                  BtMouseWaitForInput,
                  BtMouseDevice,
                  &((BtMouseDevice->SimplePointerProtocol).WaitForInput)
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->InstallProtocolInterface (
                  &Controller,
                  &gEfiSimplePointerProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &BtMouseDevice->SimplePointerProtocol
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  BtMouseDevice->ControllerNameTable = NULL;
  AddUnicodeString2 (
    "eng",
    gHidMouseComponentName.SupportedLanguages,
    &BtMouseDevice->ControllerNameTable,
    L"Generic Hid Mouse",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gHidMouseComponentName2.SupportedLanguages,
    &BtMouseDevice->ControllerNameTable,
    L"Generic Hid Mouse",
    FALSE
    );

//  gBS->RestoreTPL (OldTpl);

  DEBUG ((EFI_D_ERROR, "HidMouseDriverBindingStart: Exit\n"));

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

    if (BtMouseDevice != NULL) {
      if ((BtMouseDevice->SimplePointerProtocol).WaitForInput != NULL) {
        gBS->CloseEvent ((BtMouseDevice->SimplePointerProtocol).WaitForInput);
      }

      FreePool (BtMouseDevice);
      BtMouseDevice = NULL;
    }
  }

ErrorExit1:

  DEBUG ((EFI_D_ERROR, "HidMouseDriverBindingStart: Exit - %r\n", Status));
  return Status;
}


/**
  Stop the BT mouse device handled by this driver.

  @param  This                   The BT mouse driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        Simple Pointer Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
HidMouseDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                  Status;
  BT_MOUSE_DEV                *BtMouseDevice;
  EFI_SIMPLE_POINTER_PROTOCOL *SimplePointerProtocol;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSimplePointerProtocolGuid,
                  (VOID **) &SimplePointerProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  BtMouseDevice = BT_MOUSE_DEV_FROM_MOUSE_PROTOCOL (SimplePointerProtocol);

  Status = gBS->UninstallProtocolInterface (
                  Controller,
                  &gEfiSimplePointerProtocolGuid,
                  &BtMouseDevice->SimplePointerProtocol
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
  gBS->CloseEvent (BtMouseDevice->SimplePointerProtocol.WaitForInput);

  if (BtMouseDevice->ControllerNameTable != NULL) {
    FreeUnicodeStringTable (BtMouseDevice->ControllerNameTable);
  }

  FreePool (BtMouseDevice);

  return EFI_SUCCESS;

}

