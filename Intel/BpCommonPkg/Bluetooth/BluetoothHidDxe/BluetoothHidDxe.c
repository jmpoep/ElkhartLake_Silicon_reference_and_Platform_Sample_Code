//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 Bluetooth HID Driver which is used to produce EDKII_HID_PROTOCOL for upper
 layer use.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "BluetoothHidParser.h"
#include "BluetoothHidDxe.h"

EFI_DRIVER_BINDING_PROTOCOL gBluetoothHidDriverBinding = {
  BluetoothHidDriverBindingSupported,
  BluetoothHidDriverBindingStart,
  BluetoothHidDriverBindingStop,
  0xa,
  NULL,
  NULL
};

EDKII_HID_PROTOCOL     mHid = {
  BtHidGetDeviceInfo,
  BtHidStart,
  BtHidStop,
  BtHidSendRequest,
  BtHidSetNotification,
  BtHidGetReportFormatList
};

HID_DEVICE_PATH mBluetoothHidDevicePath = {
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_VENDOR_DP,
      {
        (UINT8) (sizeof (EFI_BLUETOOTH_HID_DEVICE_PATH)),
        (UINT8) ((sizeof (EFI_BLUETOOTH_HID_DEVICE_PATH)) >> 8)
      }
    },
    EFI_BLUETOOTH_HID_DEVICE_PATH_GUID,
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      END_DEVICE_PATH_LENGTH,
      0
    }
  }
};

/**
  Entrypoint of BT HID Driver.

  This function is the entrypoint of BT HID Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
BluetoothHidDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gBluetoothHidDriverBinding,
             ImageHandle,
             &gBluetoothHidComponentName,
             &gBluetoothHidComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Updates the GATT characteristic handle information of a Bluetooth human
  interface device.

  @param[in]  BtHidDev  A pointer to the BT_HID_DEV structure.

  @retval  EFI_UNSUPPORTED  The EFI Bluetooth attribute protocol is not
                            supported.
  @retval  Other            A value from other functions.

**/
STATIC
EFI_STATUS
UpdateHogpHandles (
  IN  BT_HID_DEV                  *BtHidDev
  )
{
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL       *BluetoothAttribute;
  EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO Attr;
  EFI_BLUETOOTH_UUID                     Uuid;
  EFI_STATUS                             Status;
  HID_REPORT_INFO                        *HidReportInfo;

  //DEBUG ((EFI_D_INFO, "UpdateHogpHandles:\n"));

  BluetoothAttribute = BtHidDev->BluetoothAttribute;

  if (BluetoothAttribute == NULL)
    return EFI_UNSUPPORTED;

  Uuid.Length = UUID_16BIT_TYPE_LEN;

  InitializeListHead (&BtHidDev->HidReportInfo);

  //
  // Read Report Map first.
  //
  Uuid.Data.Uuid16 = BluetoothGattTypeHidReportMap;
  Status = BluetoothAttributeSearch (BluetoothAttribute, BluetoothGattTypeCharacteristic, &Uuid, 0, &Attr.Header);
  if (!EFI_ERROR(Status)) {
    BtHidDev->ReportMapHandle = Attr.Header.AttributeHandle;
    BtHidDev->ReportMapLen = BT_HID_REPORT_MAP_LEN;
    BtHidDev->ReportMap = AllocateZeroPool (BtHidDev->ReportMapLen);
    Status = HidGetReportMap(
               &BtHidDev->Hid,
               &BtHidDev->ReportMapLen,
               BtHidDev->ReportMap
             );

    // Parse the report map
    if (!EFI_ERROR(Status)) {
      BtHidParseReportMap(BtHidDev);
    }

    //
    // Read Report Reference Descriptor
    //
    ZeroMem(&Attr, sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO));
    do {
      Uuid.Data.Uuid16 = BluetoothGattTypeHidReport;
      Status = BluetoothAttributeSearch (BluetoothAttribute, BluetoothGattTypeCharacteristic, &Uuid, Attr.Header.AttributeHandle, &Attr.Header);
      if (!EFI_ERROR(Status)) {
        HidReportInfo = AllocateZeroPool (sizeof(HID_REPORT_INFO));
        ASSERT (HidReportInfo != NULL);
        HidReportInfo->Signature = BT_HID_REPORT_INFO_SIGNATURE;
        HidReportInfo->ReportHandle = Attr.Header.AttributeHandle;

        Uuid.Data.Uuid16 = BluetoothGattTypeDescReportRefer;
        Status = BluetoothAttributeSearch (BluetoothAttribute, BluetoothGattTypeCharacteristicExtendedProperties, &Uuid, Attr.Header.AttributeHandle, &Attr.Header);
        if (!EFI_ERROR(Status)) {
          HidReportInfo->ReportReferDescHandle = Attr.Header.AttributeHandle;
          InsertTailList (&BtHidDev->HidReportInfo, &HidReportInfo->Link);
        } else {
          FreePool(HidReportInfo);
        }
      }
    } while(!EFI_ERROR(Status));

    HidGetReportReferDesc(
      &BtHidDev->Hid
    );
  }
  return Status;
}

/**
  Creates a Bluetooth attribute child handle.

  @param[in]      Controller          The handle for the EFI Bluetooth
                                      attribute service binding protocol
                                      interface that is being opened.
  @param[in]      Image               The handle of the agent that is opening
                                      the EFI Bluetooth attribute service
                                      binding protocol interface.
  @param[in]      ServiceBindingGuid  The published unique identifier of the
                                      EFI Bluetooth attribute service binding
                                      protocol.
  @param[in,out]  ChildHandle         Pointer to the handle of the child to
                                      create. If it is NULL, then a new handle
                                      is created. If it is a pointer to an
                                      existing UEFI handle, then the protocol
                                      is added to the existing UEFI handle.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothCreateServiceChild (
  IN  EFI_HANDLE            Controller,
  IN  EFI_HANDLE            Image,
  IN  EFI_GUID              *ServiceBindingGuid,
  IN  OUT EFI_HANDLE        *ChildHandle
  )
{
  EFI_STATUS                    Status;
  EFI_SERVICE_BINDING_PROTOCOL  *Service;


  ASSERT ((ServiceBindingGuid != NULL) && (ChildHandle != NULL));

  //
  // Get the ServiceBinding Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  ServiceBindingGuid,
                  (VOID **) &Service,
                  Image,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Create a child
  //
  Status = Service->CreateChild (Service, ChildHandle);
  return Status;
}

/**
  Destroys a Bluetooth attribute child handle.

  @param[in]  Controller          The handle for the EFI Bluetooth attribute
                                  service binding protocol interface that is
                                  being opened.
  @param[in]  Image               The handle of the agent that is opening the
                                  EFI Bluetooth attribute service binding
                                  protocol interface.
  @param[in]  ServiceBindingGuid  The published unique identifier of the EFI
                                  Bluetooth attribute service binding protocol.
  @param[in]  ChildHandle         Handle of the child to destroy.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothDestroyServiceChild (
  IN  EFI_HANDLE            Controller,
  IN  EFI_HANDLE            Image,
  IN  EFI_GUID              *ServiceBindingGuid,
  IN  EFI_HANDLE            ChildHandle
  )
{
  EFI_STATUS                    Status;
  EFI_SERVICE_BINDING_PROTOCOL  *Service;

  ASSERT (ServiceBindingGuid != NULL);

  //
  // Get the ServiceBinding Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  ServiceBindingGuid,
                  (VOID **) &Service,
                  Image,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // destroy the child
  //
  Status = Service->DestroyChild (Service, ChildHandle);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Check whether BT HID driver supports this device.

  @param  This                   The BT HID driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothHidDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                        Status;
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }
  return gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothAttributeServiceBindingProtocolGuid,
                  NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
}


/**
  Starts the BT HID device with this driver.

  This function consumes Bluetooth I/O Portocol, intializes BT HID device,
  installs Hid Protocol.

  @param  This                  The BT HID driver binding instance.
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
BluetoothHidDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                       Status;
  EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL *BluetoothAttribute;
  BT_HID_DEV                       *BtHidDev;
  EFI_DEVICE_PATH_PROTOCOL         *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL         *Node;
  EFI_BLUETOOTH_UUID               Uuid;
  EFI_HANDLE                       ChildHandle;

  DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStart: %p %p \n", Controller, This->DriverBindingHandle));
  BtHidDev    = NULL;
  ChildHandle = NULL;
  BluetoothAttribute = NULL;
  DevicePath         = NULL;

  //
  // Get Device Path from Controller (It's Ble device)
  // The DevicePath is opened BY_DRIVER by BluetoothAttributeDriverBinding
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  ASSERT_EFI_ERROR (Status);
  DevicePath = AppendDevicePath (DevicePath, (EFI_DEVICE_PATH_PROTOCOL *)&mBluetoothHidDevicePath);
  ASSERT (DevicePath != NULL);

  Node = DevicePath;
  Status = gBS->LocateDevicePath (&gEfiDevicePathProtocolGuid, &Node, &ChildHandle);
  if (!EFI_ERROR (Status) && IsDevicePathEnd (Node)) {
    //
    // The HID child is already created.
    //
    FreePool (DevicePath);
    return EFI_ALREADY_STARTED;
  }

  //
  // Create a Bluetooth Attribute child instance.
  //
  Status = BluetoothCreateServiceChild (
             Controller,
             This->DriverBindingHandle,
             &gEfiBluetoothAttributeServiceBindingProtocolGuid,
             &ChildHandle
             );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->OpenProtocol (
                  ChildHandle,
                  &gEfiBluetoothAttributeProtocolGuid,
                  (VOID**)&BluetoothAttribute,
                  This->DriverBindingHandle,
                  ChildHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  ASSERT_EFI_ERROR (Status);

  Uuid.Length = UUID_16BIT_TYPE_LEN;
  Uuid.Data.Uuid16 = BluetoothUuidHumanInterfaceDevice;
  Status = BluetoothAttributeSearch (BluetoothAttribute, BluetoothGattTypePrimaryService, &Uuid, 0, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStart: %r\n", Status));
    FreePool (DevicePath);
    goto ErrorExit;
  } else {
    DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStart: Find HID service\n"));
  }

  BtHidDev = AllocateZeroPool (sizeof (BT_HID_DEV));
  ASSERT (BtHidDev != NULL);

  BtHidDev->Signature         = BT_HID_DEV_SIGNATURE;
  BtHidDev->BluetoothAttribute = BluetoothAttribute;
  CopyMem (&BtHidDev->Hid, &mHid, sizeof(mHid));
  BtHidDev->DevicePath        = DevicePath;
  BtHidDev->ControllerHandle  = ChildHandle;
  BtHidDev->ParentHandle      = Controller;

  UpdateHogpHandles(BtHidDev);

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &BtHidDev->ControllerHandle,
                  &gEfiDevicePathProtocolGuid, BtHidDev->DevicePath,
                  &gEdkiiHidProtocolGuid, &BtHidDev->Hid,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  BtHidDev->ControllerNameTable = NULL;
  AddUnicodeString2 (
    "eng",
    gBluetoothHidComponentName.SupportedLanguages,
    &BtHidDev->ControllerNameTable,
    L"Generic Bluetooth HID",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gBluetoothHidComponentName2.SupportedLanguages,
    &BtHidDev->ControllerNameTable,
    L"Generic Bluetooth HID",
    FALSE
    );

  DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStart: ctrl = %x, child = %x, Exit - %r\n", Controller, ChildHandle, Status));
  return Status;

//
// Error handler
//
ErrorExit:
  Status = gBS->CloseProtocol (
                  ChildHandle,
                  &gEfiBluetoothAttributeProtocolGuid,
                  This->DriverBindingHandle,
                  ChildHandle
                  );

  Status = BluetoothDestroyServiceChild (
             Controller,
             This->DriverBindingHandle,
             &gEfiBluetoothAttributeServiceBindingProtocolGuid,
             ChildHandle
             );

  DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStart: Exit - %r\n", Status));
  return EFI_DEVICE_ERROR;
}


/**
  Stop the BT HID device handled by this driver.

  @param  This                   The BT HID driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        Hid Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothHidDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                  Status;
  BT_HID_DEV                  *BtHidDev;
  EDKII_HID_PROTOCOL          *Hid;
  LIST_ENTRY                  *Link;
  HID_REPORT_INFO             *ReportInfo;
  HID_REPORT_FMT              *ReportFormatList;

  DEBUG ((EFI_D_ERROR, "BluetoothHidDriverBindingStop: ctrl = %x, no = %x\n", Controller, NumberOfChildren));

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEdkiiHidProtocolGuid,
                  (VOID **) &Hid,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  BtHidDev = BT_HID_DEV_FROM_HID_PROTOCOL (Hid);

  HidStopNotification (Hid);
  FreePool(BtHidDev->ReportMap);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  BtHidDev->ControllerHandle,
                  &gEfiDevicePathProtocolGuid, BtHidDev->DevicePath,
                  &gEdkiiHidProtocolGuid, &BtHidDev->Hid,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBS->CloseProtocol (
         Controller,
         &gEfiBluetoothAttributeProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  Status = BluetoothDestroyServiceChild (
             BtHidDev->ParentHandle,
             This->DriverBindingHandle,
             &gEfiBluetoothAttributeServiceBindingProtocolGuid,
             BtHidDev->ControllerHandle
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Free all resources.
  //
  if (BtHidDev->ControllerNameTable != NULL) {
    FreeUnicodeStringTable (BtHidDev->ControllerNameTable);
  }

  Link  = GetFirstNode (&BtHidDev->HidReportInfo);
  while (!IsNull (&BtHidDev->HidReportInfo, Link)) {
    ReportInfo = BT_HID_REPORT_INFO_FROM_LINK (Link);
    Link = RemoveEntryList (&ReportInfo->Link);
    FreePool (ReportInfo);
  }

  Link  = GetFirstNode (&BtHidDev->ReportFormatList);
  while (!IsNull (&BtHidDev->ReportFormatList, Link)) {
    ReportFormatList = ITEM_FROM_LINK(Link);
    Link = RemoveEntryList (&ReportFormatList->Link);
    FreePool (ReportFormatList);
  }

  FreePool (BtHidDev);

  return EFI_SUCCESS;

}
