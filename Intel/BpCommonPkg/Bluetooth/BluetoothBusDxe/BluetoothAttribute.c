//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The Miscellaneous Routines for Bluetooth LE Service Binding Protocol
 and Bluetooth Attribute Protocol.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "BluetoothBusDxe.h"
#include "uefi_app.h"

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
BluetoothAttributeDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

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
BluetoothAttributeDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

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
BluetoothAttributeDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  );

EFI_DRIVER_BINDING_PROTOCOL gBluetoothAttributeDriverBinding = {
  BluetoothAttributeDriverBindingSupported,
  BluetoothAttributeDriverBindingStart,
  BluetoothAttributeDriverBindingStop,
  0xa,
  NULL,
  NULL
};
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
BluetoothAttributeDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                   Status;
  EFI_DEVICE_PATH_PROTOCOL     *DevicePath;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothAttributeServiceBindingProtocolGuid,
                  NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
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
BluetoothAttributeDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                   Status;
  EFI_DEVICE_PATH_PROTOCOL     *DevicePath;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothAttributeServiceBindingProtocolGuid,
                  NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  ASSERT (!EFI_ERROR (Status) || (Status == EFI_ALREADY_STARTED));

  DEBUG ((DEBUG_ERROR, "BluetoothAttributeDriverBindingStart (%p) Exit - %r\n", Controller, Status));

  return Status;
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
BluetoothAttributeDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                       Status;
  UINTN                            Index;
  EFI_SERVICE_BINDING_PROTOCOL     *ServiceBinding;
  BOOLEAN                          AllChildrenStopped;

  DEBUG ((DEBUG_ERROR, "BluetoothAttributeDriverBindingStop (%p, %d)\n", Controller, NumberOfChildren));

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothAttributeServiceBindingProtocolGuid,
                  (VOID **) &ServiceBinding,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (NumberOfChildren == 0) {
    return gBS->CloseProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  This->DriverBindingHandle,
                  Controller
                  );
  }

  AllChildrenStopped = TRUE;
  for (Index = 0; Index < NumberOfChildren; Index++) {
    Status = ServiceBinding->DestroyChild (ServiceBinding, ChildHandleBuffer[Index]);
    if (EFI_ERROR (Status)) {
      AllChildrenStopped = FALSE;
    }
  }

  return AllChildrenStopped ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

/**
  Creates a child handle and installs a protocol.

  The CreateChild() function installs a protocol on ChildHandle.
  If ChildHandle is a pointer to NULL, then a new handle is created and
  returned in ChildHandle.
  If ChildHandle is not a pointer to NULL, then the protocol installs on the
  existing ChildHandle.

  @param[in]      This         Pointer to the EFI_SERVICE_BINDING_PROTOCOL
                               instance.
  @param[in,out]  ChildHandle  Pointer to the handle of the child to create.
                               If it is a pointer to NULL, then a new handle is
                               created.
                               If it is a pointer to an existing UEFI handle,
                               then the protocol is added to the existing UEFI
                               handle.

  @retval  EFI_SUCCESS            The protocol was added to ChildHandle.
  @retval  EFI_INVALID_PARAMETER  ChildHandle is NULL.

**/
EFI_STATUS
EFIAPI
BluetoothLeServiceBindingCreateChild (
  IN     EFI_SERVICE_BINDING_PROTOCOL    *This,
  IN OUT EFI_HANDLE                      *ChildHandle
  )
{
  EFI_STATUS          Status;
  BT_LE_DEV           *BtLeDev;
  BT_LE_SB_DEV        *BtLeSbDev;
  EFI_TPL             OldTpl;
  EFI_DEVICE_PATH     *DevicePath;


  ASSERT ((ChildHandle != NULL));
  DEBUG ((EFI_D_INFO, "BUSDXE:BluetoothLeServiceBindingCreateChild enter, ChildHandle = %x\n", *ChildHandle));

  BtLeSbDev = BT_LE_SB_DEV_FROM_BLUETOOTH_SB_PROTOCOL (This);

  BtLeDev = AllocateZeroPool (sizeof (BT_LE_DEV));
  if (BtLeDev == NULL) {
    DEBUG ((EFI_D_ERROR, "AllocateZeroPool failed for %d bytes", sizeof(BT_LE_DEV)));
    return EFI_OUT_OF_RESOURCES;
  }
  BtLeDev->Signature    = BT_LE_DEV_SIGNATURE;
  BtLeDev->BtLeSbDev    = BtLeSbDev;
  CopyMem (&BtLeDev->BluetoothAtt, &mBluetoothAttribute, sizeof (EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL));

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &BtLeDev->Handle,
                  &gEfiBluetoothAttributeProtocolGuid, &BtLeDev->BluetoothAtt,
                  NULL
                  );

  DEBUG ((EFI_D_ERROR, "BluetoothLeServiceBindingCreateChild Status - %r!\n", Status));

  *ChildHandle = BtLeDev->Handle;
  //
  // Open the Parent Handle for the child handle
  //
  Status = gBS->OpenProtocol (
                  BtLeSbDev->DeviceHandle,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  gBluetoothAttributeDriverBinding.DriverBindingHandle,
                  BtLeDev->Handle,
                  EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                  );
  DEBUG ((EFI_D_ERROR, "BUSDXE:EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER , Status - %x %x %x %r!\n", BtLeSbDev->DeviceHandle, BtLeSbDev->BtHcDev->DriverBindingHandle, BtLeDev->Handle, Status));

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  InsertTailList (&BtLeSbDev->ChildrenList, &BtLeDev->Link);
  BtLeSbDev->ChildrenNumber++;
  gBS->RestoreTPL (OldTpl);

  DEBUG ((EFI_D_INFO, "BUSDXE:BluetoothLeServiceBindingCreateChild exit, ChildHandle = %x\n", *ChildHandle));
  return EFI_SUCCESS;
}

/**
  Destroys a child handle with a protocol installed on it.

  The DestroyChild() function does the opposite of CreateChild(). It removes a
  protocol that was installed by CreateChild() from ChildHandle. If the removed
  protocol is the last protocol on ChildHandle, then ChildHandle is destroyed.

  @param[in]  This         Pointer to the EFI_SERVICE_BINDING_PROTOCOL
                           instance.
  @param[in]  ChildHandle  Handle of the child to destroy.

  @retval  EFI_SUCCESS            The protocol was removed from ChildHandle.
  @retval  EFI_UNSUPPORTED        ChildHandle does not support the protocol
                                  that is being removed.
  @retval  EFI_INVALID_PARAMETER  Child handle is NULL.
  @retval  EFI_ACCESS_DENIED      The protocol could not be removed from the
                                  ChildHandle because its services are being
                                  used.
  @retval  other                  The child handle was not destroyed.

**/
EFI_STATUS
EFIAPI
BluetoothLeServiceBindingDestroyChild (
  IN EFI_SERVICE_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                      ChildHandle
  )
{
  EFI_STATUS         Status;
  BT_LE_DEV          *BtLeDev;
  BT_LE_SB_DEV       *BtLeSbDev;
  EFI_TPL            OldTpl;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL *BlueAttribute;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "BUSDXE:BluetoothLeServiceBindingDestroyChild enter, ChildHandle = %x\n", ChildHandle));

  BtLeSbDev = BT_LE_SB_DEV_FROM_BLUETOOTH_SB_PROTOCOL (This);

  Status = gBS->OpenProtocol (
                  ChildHandle,
                  &gEfiBluetoothAttributeProtocolGuid,
                  (VOID **) &BlueAttribute,
                  gBluetoothAttributeDriverBinding.DriverBindingHandle,
                  ChildHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }
  BtLeDev = BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL (BlueAttribute);
  if (BtLeDev->InDestroy) {
    return EFI_SUCCESS;
  }

  BtLeDev->InDestroy = TRUE;
  Status = gBS->CloseProtocol (
                  BtLeSbDev->DeviceHandle,
                  &gEfiDevicePathProtocolGuid,
                  gBluetoothAttributeDriverBinding.DriverBindingHandle,
                  BtLeDev->Handle
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  BtLeDev->Handle,
                  &gEfiBluetoothAttributeProtocolGuid,
                  &BtLeDev->BluetoothAtt,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    gBS->OpenProtocol (
      BtLeSbDev->DeviceHandle,
      &gEfiDevicePathProtocolGuid,
      (VOID **)&DevicePath,
      gBluetoothAttributeDriverBinding.DriverBindingHandle,
      BtLeDev->Handle,
      EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
    );
  }

  if (EFI_ERROR (Status)) {
    BtLeDev->InDestroy = FALSE;
  } else {
    OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
    RemoveEntryList (&BtLeDev->Link);
    BtLeSbDev->ChildrenNumber--;
    gBS->RestoreTPL (OldTpl);
    FreePool (BtLeDev);
  }

  DEBUG ((EFI_D_INFO, "BUSDXE:BluetoothLeServiceBindingDestroyChild exit - %r\n", Status));

  return Status;
}

/****************************************************************************/
/********************************* BLE APIs *********************************/
/****************************************************************************/

/**
  Get Bluetooth device information.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[out] DeviceInfoSize    A pointer to the size, in bytes, of the DeviceInfo buffer.
  @param[out] DeviceInfo        A pointer to a callee allocated buffer that returns Bluetooth
                                device information. Callee allocates this buffer by using EFI Boot
                                Service AllocatePool(). If this device is Bluetooth classic
                                device, EFI_BLUETOOTH_DEVICE_INFO should be used. If
                                this device is Bluetooth LE device, EFI_BLUETOOTH_LE_DEVICE_INFO
                                should be used.

  @retval EFI_SUCCESS           The Bluetooth device information is returned successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the Bluetooth device
                                information

**/
EFI_STATUS
EFIAPI
BluetoothAttributeGetDeviceInfo (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL  *This,
  OUT UINTN                             *DeviceInfoSize,
  OUT VOID                              **DeviceInfo
  )
{
  BT_LE_DEV                       *BtLeDev;
  BT_LE_SB_DEV                    *BtLeSbDev;
  BT_LE_DEV_INFO                  *BtLeDevInfo;
  EFI_BLUETOOTH_LE_DEVICE_INFO    *Info;

  BtLeDev = BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL(This);
  BtLeSbDev = BtLeDev->BtLeSbDev;
  BtLeDevInfo = BtLeSbDev->BtLeDevInfo;

  Info = NULL;
  Info = AllocateZeroPool (sizeof (EFI_BLUETOOTH_LE_DEVICE_INFO));
  if (Info == NULL) {
    DEBUG ((EFI_D_ERROR, "AllocateZeroPool failed for %d bytes", sizeof(EFI_BLUETOOTH_LE_DEVICE_INFO)));
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (&Info->BD_ADDR, &BtLeDevInfo->BDAddr, sizeof(BtLeDevInfo->BDAddr));
  CopyMem (&Info->DirectAddress, &BtLeDevInfo->Direct_BD_ADDR, sizeof(BtLeDevInfo->Direct_BD_ADDR));
  Info->RSSI = BtLeDevInfo->RSSI;
  CopyMem (&Info->AdvertisementData, &BtLeDevInfo->AdvertisementData, sizeof(BtLeDevInfo->AdvertisementData));

  *DeviceInfoSize = sizeof (EFI_BLUETOOTH_LE_DEVICE_INFO);
  *DeviceInfo     = Info;

  return EFI_SUCCESS;
}

/**
  Get Bluetooth discovered service information.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[out] ServiceInfoSize   A pointer to the size, in bytes, of the ServiceInfo buffer.
  @param[out] ServiceInfo       A pointer to a callee allocated buffer that returns Bluetooth
                                discovered service information. Callee allocates this buffer by
                                using EFI Boot Service AllocatePool().

  @retval EFI_SUCCESS           The Bluetooth discovered service information is returned successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the Bluetooth discovered
                                service information.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeGetServiceInfo (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL      *This,
  OUT UINTN                                *ServiceInfoSize,
  OUT VOID                                 **ServiceInfo
  )
{
  UINTN                   Size;
  UINTN                   Index;
  BT_LE_DEV               *BtLeDev;
  EFI_BLUETOOTH_ATTRIBUTE_HEADER *Attr;
  UINT8                   *Attributes;

  Size    = 0;
  BtLeDev = BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL (This);

  for (Index = 0; Index < BT_LE_PER_DEV_ATTR; Index++) {
    Attr = BtLeDev->BtLeSbDev->AttrDatabase[Index];
    if (Attr == NULL) {
     continue;
    }

    if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypePrimaryService)) {
      Size += sizeof (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeInclude)) {
      Size += sizeof (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeCharacteristic)) {
      Size += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeCharacteristicExtendedProperties)) {
      Size += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO);
    } else /* Characteristic Value */ {
      Size += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
    }
  }

  Attributes = NULL;
  Attributes = AllocateZeroPool(Size);
  ASSERT (Attributes != NULL);
  *ServiceInfoSize = Size;
  *ServiceInfo = Attributes;

  for (Index = 0; Index < BT_LE_PER_DEV_ATTR; Index++) {
    Attr = BtLeDev->BtLeSbDev->AttrDatabase[Index];
    if (Attr == NULL) {
      continue;
    }

    if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypePrimaryService)) {
      CopyMem (Attributes, Attr, sizeof (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO));
      Attributes += sizeof (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeInclude)) {
      CopyMem (Attributes, Attr, sizeof (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO));
      Attributes += sizeof (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeCharacteristic)) {
      CopyMem (Attributes, Attr, sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
      Attributes += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
    } else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE (Attr, BluetoothGattTypeCharacteristicExtendedProperties)) {
      CopyMem (Attributes, Attr, sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO));
      Attributes += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO);
    } else /* Characteristic Value */ {
      CopyMem (Attributes, Attr, sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
      Attributes += sizeof (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
    }
  }

  return EFI_SUCCESS;
}

/**
  Send a "REQUEST" or "COMMAND" message to remote server and receive a "RESPONSE" message
  for "REQUEST" from remote server according to Bluetooth attribute protocol data unit(PDU).

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[in]  Data              Data of a REQUEST or COMMAND message. The first byte is the attribute PDU
                                related opcode, followed by opcode specific fields. See Bluetooth specification,
                                Vol 3, Part F, Attribute Protocol.
  @param[in]  DataLength        The length of Data in bytes.
  @param[in]  Callback          Callback function to notify the RESPONSE is received to the caller, with the
                                response buffer. Caller must check the response buffer content to know if the
                                request action is success or fail. It may be NULL if the data is a COMMAND.
  @param[in]  Context           Data passed into Callback function. It is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The request is sent successfully.
  @retval EFI_INVALID_PARAMETER One or more parameters are invalid due to following conditions:
                                - The Buffer is NULL.
                                - The BufferLength is 0.
                                - The opcode in Buffer is not a valid OPCODE according to Bluetooth specification.
                                - The Callback is NULL.
  @retval EFI_DEVICE_ERROR      Sending the request failed due to the host controller or the device error.
  @retval EFI_NOT_READY         A GATT operation is already underway for this device.
  @retval EFI_UNSUPPORTED       The attribute does not support the corresponding operation.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeSendRequest (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL            *This,
  IN VOID                                        *Data,
  IN UINTN                                       DataLength,
  IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION   Callback,
  IN VOID                                        *Context
  )
{
  BT_LE_DEV *BtLeDev;

  BtLeDev = BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL (This);

  return stack_send_att_req (BtLeDev->BtLeSbDev->ConnectionId, (UINT16)DataLength, Data, Callback, Context);
}

/**
  Register or unregister a server initiated message, such as NOTIFICATION or INDICATION, on a
  characteristic value on remote server.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL instance.
  @param[in]  CallbackParameter The parameter of the callback.
  @param[in]  Callback          Callback function for server initiated attribute protocol. NULL callback
                                function means unregister the server initiated callback.
  @param[in]  Context           Data passed into Callback function. It is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The callback function is registered or unregistered successfully
  @retval EFI_INVALID_PARAMETER The attribute opcode is not server initiated message opcode. See
                                Bluetooth specification, Vol 3, Part F, Attribute Protocol.
  @retval EFI_ALREADY_STARTED   A callback function is already registered on the same attribute
                                opcode and attribute handle, when the Callback is not NULL.
  @retval EFI_NOT_STARTED       A callback function is not registered on the same attribute opcode
                                and attribute handle, when the Callback is NULL.
  @retval EFI_NOT_READY         A GATT operation is already underway for this device.
  @retval EFI_UNSUPPORTED       The attribute does not support notification.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeRegisterForServerNotification (
  IN  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL           *This,
  IN  EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_PARAMETER *CallbackParameter,
  IN  EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION  Callback,
  IN  VOID                                       *Context
  )
{
  BT_LE_DEV *BtLeDev;
  BtLeDev = BT_LE_DEV_FROM_BLUETOOTH_ATTRIBUTE_PROTOCOL (This);

  if (Callback == NULL) {
    return stack_register_notification_indication (BtLeDev->BtLeSbDev->ConnectionId, CallbackParameter->Parameter.Notification.AttributeHandle, FALSE, Callback, Context);
  }

  switch (CallbackParameter->AttributeOpCode) {
    case BluetoothAttOpHandleValueNotification:
      return stack_register_notification_indication (BtLeDev->BtLeSbDev->ConnectionId, CallbackParameter->Parameter.Notification.AttributeHandle, FALSE, Callback, Context);
    case BluetoothAttOpHandleValueIndication:
      return stack_register_notification_indication (BtLeDev->BtLeSbDev->ConnectionId, CallbackParameter->Parameter.Indication.AttributeHandle, TRUE, Callback, Context);
  }

  return EFI_INVALID_PARAMETER;
}

