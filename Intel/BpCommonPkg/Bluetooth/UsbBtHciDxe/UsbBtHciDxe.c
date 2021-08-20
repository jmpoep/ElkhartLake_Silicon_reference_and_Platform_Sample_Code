//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  This driver is used to manage usb bluetooth host controller and produce
  EFI_BLUETOOTH_HC_PROTOCOL protocol on the controller handle.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "UsbBtHciDxe.h"

//
// 1. Single Function Primary Controller
//    bDeviceClass    0xE0 Wireless Controller
//    bDeviceSubClass 0x01 RF Controller
//    bDeviceProtocol 0x01Bluetooth Primary Controller
//
// 2. Single Function AMP Controller
//    bDeviceClass    0xE0 Wireless Controller
//    bDeviceSubClass 0x01 RF Controller
//    bDeviceProtocol 0x04Bluetooth AMP Controller
//
// 3. CompositeBluetooth Primary and AMP Controller
//    bDeviceClass    0xEF Miscellaneous
//    bDeviceSubClass 0x02 Common Class
//    bDeviceProtocol 0x01 Interface Association Descriptor
//
USB_BTHCI_INFO mUsbBtHciInfo[] = {
  {0xFF, 0x01, 0x01, 0xFF, 0x01, 0x01, BtHciPrimaryControllerSingle}, // BUGBUG: TBD
  {0xE0, 0x01, 0x01, 0xE0, 0x01, 0x01, BtHciPrimaryControllerSingle},
//{0xE0, 0x01, 0x04, 0xE0, 0x01, 0x04, BtHciAMPControllerSingle},
//{0xEF, 0x02, 0x01, 0xE0, 0x01, 0x01, BtHciPrimaryControllerComposit},
//{0xEF, 0x02, 0x01, 0xE0, 0x01, 0x04, BtHciAMPControllerComposit},
};

EFI_DRIVER_BINDING_PROTOCOL gUsbBtHciDriverBinding = {
  USBBtHciDriverBindingSupported,
  USBBtHciDriverBindingStart,
  USBBtHciDriverBindingStop,
  0xa,
  NULL,
  NULL
};

EFI_BLUETOOTH_HC_PROTOCOL     mBluetoothHc = {
  UsbBtHciSendCommand,
  UsbBtHciReceiveEvent,
  UsbBtHciAsyncReceiveEvent,
  UsbBtHciSendACLData,
  UsbBtHciReceiveACLData,
  UsbBtHciAsyncReceiveACLData,
  UsbBtHciSendSCOData,
  UsbBtHciReceiveSCOData,
  UsbBtHciAsyncReceiveSCOData,
};

/**
  Entrypoint of USB BtHci Driver.

  This function is the entrypoint of USB BtHci Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gUsbBtHciDriverBinding,
             ImageHandle,
             &gUsbBtHciComponentName,
             &gUsbBtHciComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


/**
  Check whether USB BtHci driver supports this device.

  @param  This                   The USB BtHci driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS          Status;
  EFI_USB_IO_PROTOCOL *UsbIo;
  USB_BTHCI_INFO      *BtHciInfo;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiUsbIoProtocolGuid,
                  (VOID **) &UsbIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Use the USB I/O Protocol interface to check whether Controller is
  // a Bthci device that can be managed by this driver.
  //
  Status = EFI_SUCCESS;
  BtHciInfo = IsUsbBtHci (UsbIo);
  if (BtHciInfo == NULL) {
    Status = EFI_UNSUPPORTED;
  } else {
    //DEBUG ((EFI_D_ERROR, "USBBtHciDriverBindingSupported: Find - %x!\n", BtHciInfo->BtHciType));
  }

  gBS->CloseProtocol (
        Controller,
        &gEfiUsbIoProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  return Status;
}


/**
  Starts the BtHci device with this driver.

  This function consumes USB I/O Portocol, intializes USB BtHci device,
  installs Bluetooth HC Protocol.

  @param  This                  The USB BtHci driver binding instance.
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
USBBtHciDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                  Status;
  EFI_USB_IO_PROTOCOL         *UsbIo;
  USB_BTHCI_DEV               *UsbBtHciDevice;
  UINT8                       EndpointNumber;
  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDescriptor;
  UINT8                       Index;
  BOOLEAN                     FoundIn;
  BOOLEAN                     FoundOut;
  BOOLEAN                     FoundInt;
  EFI_TPL                     OldTpl;
  USB_BTHCI_INFO              *BtHciInfo;

  DEBUG ((DEBUG_INFO, "%a Enter\n", __FUNCTION__));

  UsbBtHciDevice = NULL;

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);
  //
  // Open USB I/O Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiUsbIoProtocolGuid,
                  (VOID **) &UsbIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit1;
  }

  BtHciInfo = IsUsbBtHci (UsbIo);
  ASSERT (BtHciInfo != NULL);

  UsbBtHciDevice = AllocateZeroPool (sizeof (USB_BTHCI_DEV));
  ASSERT (UsbBtHciDevice != NULL);

  UsbBtHciDevice->Signature         = USB_BTHCI_DEV_SIGNATURE;
  UsbBtHciDevice->UsbIo             = UsbIo;
  CopyMem (&UsbBtHciDevice->BluetoothHc, &mBluetoothHc, sizeof(mBluetoothHc));
  UsbBtHciDevice->ControllerHandle  = Controller;
  UsbBtHciDevice->BtHciType         = BtHciInfo->BtHciType;

  UsbIo->UsbGetDeviceDescriptor (
           UsbIo,
           &UsbBtHciDevice->DeviceDescriptor
           );

  UsbIo->UsbGetConfigDescriptor (
           UsbIo,
           &UsbBtHciDevice->ConfigurationDescriptor
           );

  //
  // Get interface & endpoint descriptor
  //
  UsbIo->UsbGetInterfaceDescriptor (
           UsbIo,
           &UsbBtHciDevice->InterfaceDescriptor
           );

  EndpointNumber = UsbBtHciDevice->InterfaceDescriptor.NumEndpoints;

  //
  // Traverse endpoints to find interrupt endpoint
  //
  FoundIn = FALSE;
  FoundOut = FALSE;
  FoundInt = FALSE;
  for (Index = 0; Index < EndpointNumber; Index++) {
    UsbIo->UsbGetEndpointDescriptor (
             UsbIo,
             Index,
             &EndpointDescriptor
             );
    //DEBUG ((EFI_D_INFO, "  Endpoint: 0x%x\n", Index));
    //DEBUG ((EFI_D_INFO, "    Address:       0x%02x\n", EndpointDescriptor.EndpointAddress));
    //DEBUG ((EFI_D_INFO, "    Attributes:    0x%02x\n", EndpointDescriptor.Attributes));
    //DEBUG ((EFI_D_INFO, "    MaxPacketSize: 0x%04x\n", EndpointDescriptor.MaxPacketSize));
    //DEBUG ((EFI_D_INFO, "    Interval:      0x%02x\n", EndpointDescriptor.Interval));
    if ((EndpointDescriptor.EndpointAddress & USB_ENDPOINT_DIR_IN) == 0) {
      if ((EndpointDescriptor.Attributes & USB_ENDPOINT_TYPE_MASK) == USB_ENDPOINT_BULK) {
        CopyMem(&UsbBtHciDevice->OutEndpointDescriptor, &EndpointDescriptor, sizeof(EndpointDescriptor));
        FoundOut = TRUE;
      }
    } else {
      if ((EndpointDescriptor.Attributes & USB_ENDPOINT_TYPE_MASK) == USB_ENDPOINT_INTERRUPT) {
        CopyMem(&UsbBtHciDevice->IntEndpointDescriptor, &EndpointDescriptor, sizeof(EndpointDescriptor));
        FoundInt = TRUE;
      } else if ((EndpointDescriptor.Attributes & USB_ENDPOINT_TYPE_MASK) == USB_ENDPOINT_BULK) {
        CopyMem(&UsbBtHciDevice->InEndpointDescriptor, &EndpointDescriptor, sizeof(EndpointDescriptor));
        FoundIn = TRUE;
      }
    }
  }

  if ((!FoundIn) || (!FoundOut) || (!FoundInt)) {
    //
    // No interrupt endpoint found, then return unsupported.
    //
    Status = EFI_UNSUPPORTED;
    goto ErrorExit;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiBluetoothHcProtocolGuid,
                  &UsbBtHciDevice->BluetoothHc,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  gBS->CreateEvent (
         EVT_TIMER | EVT_NOTIFY_SIGNAL,
         TPL_NOTIFY,
         UsbBtHciRecoveryHandler,
         UsbBtHciDevice,
         &UsbBtHciDevice->DelayedRecoveryEvent
         );

  //
  // Open For Child Device
  //

  UsbBtHciDevice->ControllerNameTable = NULL;
  AddUnicodeString2 (
    "eng",
    gUsbBtHciComponentName.SupportedLanguages,
    &UsbBtHciDevice->ControllerNameTable,
    L"Generic Usb BtHci",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gUsbBtHciComponentName2.SupportedLanguages,
    &UsbBtHciDevice->ControllerNameTable,
    L"Generic Usb BtHci",
    FALSE
    );

  gBS->RestoreTPL (OldTpl);

  //DEBUG ((EFI_D_ERROR, "USBBtHciDriverBindingStart: Exit\n"));

  return EFI_SUCCESS;

//
// Error handler
//
ErrorExit:
  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
          Controller,
          &gEfiUsbIoProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );

    if (UsbBtHciDevice != NULL) {
      if (UsbBtHciDevice->DelayedRecoveryEvent != NULL) {
        gBS->CloseEvent (UsbBtHciDevice->DelayedRecoveryEvent);
        UsbBtHciDevice->DelayedRecoveryEvent = NULL;
      }

      FreePool (UsbBtHciDevice);
      UsbBtHciDevice = NULL;
    }
  }

ErrorExit1:
  gBS->RestoreTPL (OldTpl);

  DEBUG ((DEBUG_INFO, "%a Exit %r\n", __FUNCTION__, Status));
  return Status;
}


/**
  Stop the USB BtHci device handled by this driver.

  @param  This                   The USB BtHci driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        Bluetooth HC Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
USBBtHciDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                  Status;
  USB_BTHCI_DEV               *UsbBtHciDevice;
  EFI_BLUETOOTH_HC_PROTOCOL   *BluetoothHc;

  DEBUG ((DEBUG_INFO, "%a Enter\n", __FUNCTION__));
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothHcProtocolGuid,
                  (VOID **) &BluetoothHc,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "%a Exit %r\n", __FUNCTION__, Status));
    return EFI_UNSUPPORTED;
  }

  UsbBtHciDevice = USB_BTHCI_DEV_FROM_BLUETOOTH_HC_PROTOCOL (BluetoothHc);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  Controller,
                  &gEfiBluetoothHcProtocolGuid,
                  &UsbBtHciDevice->BluetoothHc,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "%a Exit %r\n", __FUNCTION__, Status));
    return Status;
  }

  gBS->CloseEvent (UsbBtHciDevice->DelayedRecoveryEvent);

  if (UsbBtHciDevice->AclEvent != NULL) {
    gBS->CloseEvent (UsbBtHciDevice->AclEvent);
  }

  gBS->CloseProtocol (
         Controller,
         &gEfiUsbIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  //
  // Free all resources.
  //
  if (UsbBtHciDevice->ControllerNameTable != NULL) {
    FreeUnicodeStringTable (UsbBtHciDevice->ControllerNameTable);
  }

  FreePool (UsbBtHciDevice);

  DEBUG ((DEBUG_INFO, "%a Exit\n", __FUNCTION__));
  return EFI_SUCCESS;

}

/**
  Unload UsbBtHciDxe driver.

  @param[in]  ImageHandle       The drivers' driver image.

  @retval EFI_SUCCESS           The image is unloaded.
  @retval Others                Failed to unload the image.

**/
EFI_STATUS
EFIAPI
UsbBtHciDxeUnload (
  IN EFI_HANDLE    ImageHandle
  )
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        *DeviceHandleBuffer;
  UINTN                             DeviceHandleCount;
  UINTN                             Index;
  EFI_COMPONENT_NAME_PROTOCOL       *ComponentName;
  EFI_COMPONENT_NAME2_PROTOCOL      *ComponentName2;

  //
  // Get the list of all the handles in the handle database.
  // If there is an error getting the list, then the unload
  // operation fails.
  //
  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &DeviceHandleCount,
                  &DeviceHandleBuffer
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Disconnect the driver from all the devices
  // in the handle database.
  //
  for (Index = 0; Index < DeviceHandleCount; Index++) {
    Status = gBS->DisconnectController (
                    DeviceHandleBuffer[Index],
                    gUsbBtHciDriverBinding.DriverBindingHandle,
                    NULL
                    );
  }

  //
  // Free the buffer containing the list of handles from the handle database
  //
  if (DeviceHandleBuffer != NULL) {
    gBS->FreePool (DeviceHandleBuffer);
  }

  //
  // Uninstall all the protocols installed in the driver entry point
  //
  Status = gBS->UninstallProtocolInterface (
                  gUsbBtHciDriverBinding.DriverBindingHandle,
                  &gEfiDriverBindingProtocolGuid,
                  &gUsbBtHciDriverBinding
                  );
  if (EFI_ERROR (Status))
    goto Exit;

  Status = gBS->HandleProtocol (
                  gUsbBtHciDriverBinding.DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID **) &ComponentName
                  );

  if (!EFI_ERROR (Status)) {
    Status = gBS->UninstallProtocolInterface (
                    gUsbBtHciDriverBinding.DriverBindingHandle,
                    &gEfiComponentNameProtocolGuid,
                    ComponentName
                    );
    if (EFI_ERROR (Status))
      goto Exit1;
  }

  Status = gBS->HandleProtocol (
                  gUsbBtHciDriverBinding.DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID **) &ComponentName2
                  );

  if (!EFI_ERROR (Status)) {
    Status =  gBS->UninstallProtocolInterface (
                     gUsbBtHciDriverBinding.DriverBindingHandle,
                     &gEfiComponentName2ProtocolGuid,
                     ComponentName2
                     );
    if (EFI_ERROR (Status))
      goto Exit2;
  }

  return EFI_SUCCESS;

  Exit2:
    Status = gBS->InstallProtocolInterface (
                    gUsbBtHciDriverBinding.DriverBindingHandle,
                    &gEfiComponentNameProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    ComponentName
                    );
    ASSERT_EFI_ERROR (Status);

  Exit1:
    Status = gBS->InstallProtocolInterface (
                    gUsbBtHciDriverBinding.DriverBindingHandle,
                    &gEfiDriverBindingProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gUsbBtHciDriverBinding
                    );
    ASSERT_EFI_ERROR (Status);

  Exit:
    return EFI_ABORTED;
}

/**
  Uses USB I/O to check whether the device is a USB BtHci device.

  @param  UsbIo    Pointer to a USB I/O protocol instance.

  @retval Not NULL Device is a USB BtHci device.
  @retval NULL     Device is a not USB BtHci device.

**/
USB_BTHCI_INFO *
IsUsbBtHci (
  IN  EFI_USB_IO_PROTOCOL     *UsbIo
  )
{
  EFI_STATUS                    Status;
  EFI_USB_INTERFACE_DESCRIPTOR  InterfaceDescriptor;
  EFI_USB_DEVICE_DESCRIPTOR     DeviceDescriptor;
  UINTN                         Index;

  //DEBUG ((EFI_D_INFO, "IsUsbBtHci:\n"));

  //
  // Get the default interface descriptor
  //
  Status = UsbIo->UsbGetInterfaceDescriptor (
                    UsbIo,
                    &InterfaceDescriptor
                    );

  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //
  // Get the default interface descriptor
  //
  Status = UsbIo->UsbGetDeviceDescriptor (
                    UsbIo,
                    &DeviceDescriptor
                    );

  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //DEBUG ((EFI_D_INFO, "  IdVendor:  0x%04x\n", DeviceDescriptor.IdVendor));
  //DEBUG ((EFI_D_INFO, "  IdProduct: 0x%04x\n", DeviceDescriptor.IdProduct));
  //DEBUG ((EFI_D_INFO, "  DeviceClass:    0x%02x\n", DeviceDescriptor.DeviceClass));
  //DEBUG ((EFI_D_INFO, "  DeviceSubClass: 0x%02x\n", DeviceDescriptor.DeviceSubClass));
  //DEBUG ((EFI_D_INFO, "  DeviceProtocol: 0x%02x\n", DeviceDescriptor.DeviceProtocol));
  //DEBUG ((EFI_D_INFO, "  InterfaceClass:    0x%02x\n", InterfaceDescriptor.InterfaceClass));
  //DEBUG ((EFI_D_INFO, "  InterfaceSubClass: 0x%02x\n", InterfaceDescriptor.InterfaceSubClass));
  //DEBUG ((EFI_D_INFO, "  InterfaceProtocol: 0x%02x\n", InterfaceDescriptor.InterfaceProtocol));

  for (Index = 0; Index < sizeof(mUsbBtHciInfo)/sizeof(mUsbBtHciInfo[0]); Index++) {
    if ((DeviceDescriptor.DeviceClass == mUsbBtHciInfo[Index].DeviceClass) &&
        (DeviceDescriptor.DeviceSubClass == mUsbBtHciInfo[Index].DeviceSubClass) &&
        (DeviceDescriptor.DeviceProtocol == mUsbBtHciInfo[Index].DeviceProtocol) &&
        (InterfaceDescriptor.InterfaceClass == mUsbBtHciInfo[Index].InterfaceClass) &&
        (InterfaceDescriptor.InterfaceSubClass == mUsbBtHciInfo[Index].InterfaceSubClass) &&
        (InterfaceDescriptor.InterfaceProtocol == mUsbBtHciInfo[Index].InterfaceProtocol)
        ) {
      return &mUsbBtHciInfo[Index];
    }
  }

  return NULL;
}

