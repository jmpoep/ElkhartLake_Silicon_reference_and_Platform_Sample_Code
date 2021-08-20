//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The Bluetooth Bus driver, which is used to provide interfaces to scan,
 connect and access all connected bluetooth LE devices.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "uefi_app.h"
#include "BluetoothBusDxe.h"

EFI_DRIVER_BINDING_PROTOCOL gBluetoothBusDriverBinding = {
  BluetoothBusDriverBindingSupported,
  BluetoothBusDriverBindingStart,
  BluetoothBusDriverBindingStop,
  0xa,
  NULL,
  NULL
};

EFI_SERVICE_BINDING_PROTOCOL    mBluetoothLeServiceBinding = {
 BluetoothLeServiceBindingCreateChild,
 BluetoothLeServiceBindingDestroyChild
};

EFI_BLUETOOTH_LE_CONFIG_PROTOCOL mBluetoothLeConfig = {
  BluetoothLeConfigInit,
  BluetoothLeConfigScan,
  BluetoothLeConfigConnect,
  BluetoothLeConfigDisconnect,
  BluetoothLeConfigGetData,
  BluetoothLeConfigSetData,
  BluetoothLeConfigGetRemoteData,
  BluetoothLeRegisterSmpAuthCallback,
  BluetoothLeConfigSendSmpAuthData,
  BluetoothLeConfigRegisterSmpGetDataCallback,
  BluetoothLeConfigRegisterSmpSetDataCallback,
  BluetoothLeConfigRegisterConnectCompleteCallBack,
};
extern EFI_DRIVER_BINDING_PROTOCOL gBluetoothAttributeDriverBinding;
/**
  Entrypoint of BluetoothBus Driver.

  This function is the entrypoint of BluetoothBus Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
BluetoothBusDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gBluetoothBusDriverBinding,
             ImageHandle,
             &gBluetoothBusComponentName,
             &gBluetoothBusComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  Status = EfiLibInstallDriverBinding (
    ImageHandle,
    SystemTable,
    &gBluetoothAttributeDriverBinding,
    NULL
  );
  ASSERT_EFI_ERROR (Status);
  return EFI_SUCCESS;
}


/**
  Check whether BluetoothBus driver supports this device.

  @param  This                   The BluetoothBus driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothBusDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                   Status;
  EFI_BLUETOOTH_HC_PROTOCOL    *BluetoothHc;
  EFI_DEVICE_PATH_PROTOCOL     *DevicePath;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothHcProtocolGuid,
                  (VOID **) &BluetoothHc,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  if (!EFI_ERROR (Status)) {
    gBS->CloseProtocol (
           Controller,
           &gEfiBluetoothHcProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  if (!EFI_ERROR (Status)) {
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
  }
  return EFI_SUCCESS;
}


/**
  Starts the BluetoothHc device with this driver.

  This function consumes BluetoothHc Portocol, intializes BluetoothHc device,
  installs BluetoothLeConfig Protocol.

  @param  This                  The BluetoothHc driver binding instance.
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
BluetoothBusDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                  Status;
  EFI_STATUS                  HcStatus;
  EFI_STATUS                  DevicePathStatus;
  EFI_BLUETOOTH_HC_PROTOCOL   *BluetoothHc;
  BTHC_DEV                    *BtHcDevice;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;

  BtHcDevice = NULL;

  //
  // Open Bluetooth HC Protocol from BLE controller handle BY_DRIVER
  //
  HcStatus = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothHcProtocolGuid,
                  (VOID **) &BluetoothHc,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );


  //
  // Open DevicePath Protocol from BLE controller handle BY_DRIVER
  //
  DevicePathStatus = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  DEBUG ((DEBUG_ERROR, "BluetoothBusDriverBindingStart (%p) %r %r\n", Controller, HcStatus, DevicePathStatus));
  ASSERT (!EFI_ERROR (HcStatus) || (HcStatus == EFI_ALREADY_STARTED));
  ASSERT (HcStatus == DevicePathStatus);

  if (!EFI_ERROR (HcStatus)) {
    BtHcDevice = AllocateZeroPool (sizeof (BTHC_DEV));
    if (BtHcDevice == NULL) {
      DEBUG ((EFI_D_ERROR, "AllocateZeroPool failed for %d bytes", sizeof(BTHC_DEV)));
      return EFI_OUT_OF_RESOURCES;
    }

    BtHcDevice->Signature           = BTHC_DEV_SIGNATURE;
    BtHcDevice->BluetoothHc         = BluetoothHc;
    BtHcDevice->DevicePath          = DevicePath;
    BtHcDevice->ControllerHandle    = Controller;
    BtHcDevice->DriverBindingHandle = This->DriverBindingHandle;

    CopyMem (&BtHcDevice->BluetoothLeConfig, &mBluetoothLeConfig, sizeof (mBluetoothLeConfig));
    InitializeListHead (&BtHcDevice->BtLeDevInfoList);
    InitializeListHead (&BtHcDevice->BtLeSbList);
    InitializeListHead (&BtHcDevice->BtLePairedList);
    InitializeListHead (&BtHcDevice->LeDuplicateBDAddrList);

    //
    // Build the ControllerNameTable
    //
    AddUnicodeString2 (
      "eng",
      gBluetoothBusComponentName.SupportedLanguages,
      &BtHcDevice->ControllerNameTable,
      L"Generic Bluetooth Bus",
      TRUE
      );
    AddUnicodeString2 (
      "en",
      gBluetoothBusComponentName2.SupportedLanguages,
      &BtHcDevice->ControllerNameTable,
      L"Generic Bluetooth Bus",
      FALSE
      );
    //
    // Install BluetoothLeConfig in the BLE controller handle
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &Controller,
                    &gEfiBluetoothLeConfigProtocolGuid,
                    &BtHcDevice->BluetoothLeConfig,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_ERROR, "BluetoothBusDriverBindingStart (%p) Exit\n", Controller));

  return EFI_SUCCESS;
}


/**
  Stop the BluetoothHc device handled by this driver.

  @param  This                   The BluetoothBus driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        BluetoothLeConfig Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothBusDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                       Status;
  BTHC_DEV                         *BtHcDevice;
  UINTN                            Index;
  EFI_SERVICE_BINDING_PROTOCOL     *ServiceBinding;
  BT_LE_SB_DEV                     *BtLeSbDev;
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *BluetoothLeConfig;

  DEBUG ((DEBUG_ERROR, "BluetoothBusDriverBindingStop (%p, %d)\n", Controller, NumberOfChildren));

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothLeConfigProtocolGuid,
                  (VOID **) &BluetoothLeConfig,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "BluetoothBusDriverBindingStop (%p, %d) Exit %r\n", Controller, NumberOfChildren, Status));
    return Status;
  }

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL (BluetoothLeConfig);

  stack_switch_to_sync_event();

  if (NumberOfChildren == 0) {

    Status = gBS->UninstallMultipleProtocolInterfaces (
                    Controller,
                    &gEfiBluetoothLeConfigProtocolGuid,
                    &BtHcDevice->BluetoothLeConfig,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    gBS->CloseProtocol (
           Controller,
           &gEfiBluetoothHcProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    stack_cleanup();

    //
    // Free all resources.
    //

    if (BtHcDevice->ControllerNameTable != NULL) {
      FreeUnicodeStringTable (BtHcDevice->ControllerNameTable);
    }

    BtClearList (&BtHcDevice->BtLeDevInfoList, BT_LE_DEV_INFO_SIGNATURE);
    BtClearList (&BtHcDevice->BtLeSbList, BT_LE_SB_DEV_SIGNATURE);
    BtClearList (&BtHcDevice->BtLePairedList, BT_LE_PAIRED_DEV_INFO_SIGNATURE);

    FreePool (BtHcDevice);
    DEBUG ((EFI_D_ERROR, "BluetoothBusDriverBindingStop (%p, %d) Exit\n", Controller, NumberOfChildren));
    return EFI_SUCCESS;
  }

  for (Index = 0; Index < NumberOfChildren; Index++) {
    DEBUG ((EFI_D_ERROR, "BluetoothBusDriverBindingStop: Child =%p\n", ChildHandleBuffer[Index]));
    Status = gBS->HandleProtocol (ChildHandleBuffer[Index], &gEfiBluetoothAttributeServiceBindingProtocolGuid, (VOID **) &ServiceBinding);
    ASSERT_EFI_ERROR (Status);

    BtLeSbDev = BT_LE_SB_DEV_FROM_BLUETOOTH_SB_PROTOCOL(ServiceBinding);

    Status = BluetoothLeConfigDisconnect (BluetoothLeConfig, &BtLeSbDev->BtLeDevInfo->BDAddr, BluetoothDisconnectReasonTypeRemoteUserTerminatedConnection);
    ASSERT_EFI_ERROR (Status);
  }
  DEBUG ((EFI_D_ERROR, "BluetoothBusDriverBindingStop (%p, %d) Exit\n", Controller, NumberOfChildren));
  return EFI_SUCCESS;

}

