//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The file provides some help functions which are used in device connection.

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

EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL mBluetoothAttribute = {
  BluetoothAttributeSendRequest,
  BluetoothAttributeRegisterForServerNotification,
  BluetoothAttributeGetServiceInfo,
  BluetoothAttributeGetDeviceInfo
};

/**
  Creates a BluetoothLE Service Binding device.

  @param[in]  BtHcDev      A pointer to the BTHC_DEV structure.
  @param[in]  BtLeDevInfo  A pointer to the BT_LE_DEV_INFO structure, which
                           contains the BluetoothLE device information.

  @retval  A pointer to the BT_LE_SB_DEV structure or NULL if memory allocation
           fails.

**/
BT_LE_SB_DEV*
BtCreateLeSbDev (
  IN BTHC_DEV                   *BtHcDev,
  IN BT_LE_DEV_INFO             *BtLeDevInfo
  )
{
  BT_LE_SB_DEV            *BtLeSbDev;
  BLUETOOTH_LE_ADDRESS    DummyAddr;
  BtLeSbDev = AllocateZeroPool (sizeof(BT_LE_SB_DEV));
  if (BtLeSbDev == NULL) {
    return BtLeSbDev;
  }

  BtLeSbDev->Signature = BT_LE_SB_DEV_SIGNATURE;
  ZeroMem(&DummyAddr, sizeof(BLUETOOTH_LE_ADDRESS));
  if (CompareMem(&BtLeDevInfo->IDAddr, &DummyAddr, sizeof(BLUETOOTH_LE_ADDRESS))) {
    BtAppendBtLeDevPath (
                        &BtLeSbDev->DevicePath,
                        BtHcDev->DevicePath,
                        &BtLeDevInfo->IDAddr
                       );
  } else {
    BtAppendBtLeDevPath (
                        &BtLeSbDev->DevicePath,
                        BtHcDev->DevicePath,
                        &BtLeDevInfo->BDAddr
                       );
  }

  CopyMem (&BtLeSbDev->ServiceBinding, &mBluetoothLeServiceBinding, sizeof (mBluetoothLeServiceBinding));
  BtLeSbDev->BtLeDevInfo = BtLeDevInfo;
  BtLeSbDev->BtHcDev = BtHcDev;
  InitializeListHead (&BtLeSbDev->Link);
  InitializeListHead (&BtLeSbDev->ChildrenList);
  BtLeSbDev->Initialized = FALSE;

  return BtLeSbDev;
}

/**
  Initializes the given BluetoothLE Service Binding device.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         initialize.

  @retval  EFI_SUCCESS  The initialization succeeds.
  @retval  Others       The initialization fails.

**/
EFI_STATUS
BtInitLeSbDev (
  IN  BTHC_DEV        *BtHcDev,
  IN  BT_LE_SB_DEV    *BtLeSbDev
  )
{
  EFI_STATUS                 Status;
  EFI_BLUETOOTH_HC_PROTOCOL  *BluetoothHc;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &BtLeSbDev->DeviceHandle,
                  &gEfiDevicePathProtocolGuid, BtLeSbDev->DevicePath,
                  &gEfiBluetoothAttributeServiceBindingProtocolGuid, &BtLeSbDev->ServiceBinding,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);
  Status =  gBS->OpenProtocol (
                   BtHcDev->ControllerHandle,
                   &gEfiBluetoothHcProtocolGuid,
                   (VOID **)&BluetoothHc,
                   BtHcDev->DriverBindingHandle,
                   BtLeSbDev->DeviceHandle,
                   EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                   );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_ERROR, "BleBus: BtInitLeSbDev %p\n", BtLeSbDev->DeviceHandle));
  BtLeSbDev->Initialized = TRUE;
  return Status;
}

/**
  Creates a new device path by appending a Bluetooth device node to a given
  base device path.

  @param[in,out]  DevPtr      A pointer to the generated device path if
                              EFI_SUCCESS is returned. Or NULL if
                              EFI_OUT_OF_RESOURCES is returned.
  @param[in]      BaseDevPtr  A pointer to a device path data structure.
  @param[in]      BDAddr      A pointer to a Bluetooth device address.

  @retval  EFI_SUCCESS           The new device path is created.
  @retval  EFI_OUT_OF_RESOURCES  The creation of the new device path fails due
                                 to memory allocation failure.

**/
EFI_STATUS
BtAppendBtLeDevPath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL **DevPtr,
  IN EFI_DEVICE_PATH_PROTOCOL     *BaseDevPtr,
  IN BLUETOOTH_LE_ADDRESS         *BDAddr
  )
{
  BLUETOOTH_LE_DEVICE_PATH     BtLeAddrNode;
  EFI_DEVICE_PATH_PROTOCOL     *EndNode;
  UINT16                       TotalPathLen;
  UINT16                       BasePathLen;
  UINT8                        *DevicePtr;

  ZeroMem (&BtLeAddrNode, sizeof (BtLeAddrNode));

  CopyMem (&BtLeAddrNode.Address, BDAddr, sizeof(BLUETOOTH_LE_ADDRESS));

  BtLeAddrNode.Header.Type       = MESSAGING_DEVICE_PATH;
  BtLeAddrNode.Header.SubType    = MSG_BLUETOOTH_LE_DP;
  SetDevicePathNodeLength (&BtLeAddrNode.Header, sizeof (BLUETOOTH_LE_DEVICE_PATH));

  //
  // find the size of the base dev path.
  //
  EndNode = BaseDevPtr;
  while (!IsDevicePathEnd (EndNode)) {
    EndNode = NextDevicePathNode (EndNode);
  }

  BasePathLen = (UINT16) ((UINTN) (EndNode) - (UINTN) (BaseDevPtr));

  //
  // create space for full dev path
  //
  TotalPathLen = (UINT16) (BasePathLen + sizeof (BtLeAddrNode) + sizeof (EFI_DEVICE_PATH_PROTOCOL));

  DevicePtr = AllocatePool (TotalPathLen);
  if (DevicePtr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // copy the base path, BT addr and end_dev_path nodes
  //
  *DevPtr = (EFI_DEVICE_PATH_PROTOCOL *) DevicePtr;
  CopyMem (DevicePtr, (VOID *) BaseDevPtr, BasePathLen);
  DevicePtr += BasePathLen;
  CopyMem (DevicePtr, (VOID *) &BtLeAddrNode, sizeof (BtLeAddrNode));
  DevicePtr += sizeof (BtLeAddrNode);
  CopyMem (DevicePtr, (VOID *) EndNode, sizeof (EFI_DEVICE_PATH_PROTOCOL));

  return EFI_SUCCESS;
}

/**
  Adds a given BluetoothLE Service Binding device to the BluetoothLE Service
  Binding device list.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         add into the list.

  @retval  TRUE  This function always return TRUE.

**/
BOOLEAN
BtAddLeSb (
  IN BTHC_DEV                     *BtHcDev,
  IN BT_LE_SB_DEV                 *BtLeSbDev
  )
{
  EFI_TPL       OldTpl;

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  InsertTailList (&BtHcDev->BtLeSbList, &BtLeSbDev->Link);
  gBS->RestoreTPL (OldTpl);

  return TRUE;
}

/**
  Removes a given BluetoothLE Service Binding device to the BluetoothLE Service
  Binding device list.

  @param[in]  BtHcDev    A pointer to the BTHC_DEV structure.
  @param[in]  BtLeSbDev  A pointer to the BT_LE_SB_DEV structure, which
                         specifies the BluetoothLE Service Binding device to
                         remove from the list.

  @retval  FALSE  The specified BluetoothLE Service Binding device has not been
                  removed from the list.
  @retval  TRUE   The specified BluetoothLE Service Binding device has been
                  removed from the list.

**/
BOOLEAN
BtDelLeSb (
  IN BTHC_DEV                     *BtHcDev,
  IN BT_LE_SB_DEV                 *BtLeSbDev
)
{
  EFI_TPL                   OldTpl;
  EFI_STATUS                Status;
  EFI_BLUETOOTH_HC_PROTOCOL *BluetoothHc;

  DEBUG ((DEBUG_ERROR, "BleBusDxe: BtDelLeSb (%p, %p)\n", BtHcDev, BtLeSbDev));
  if (BtHcDev == NULL || BtLeSbDev == NULL) {
    return FALSE;
  }

  if (BtLeSbDev->Initialized) {
    //
    // Close the OPEN_BY_CHILD_CONTROLLER
    //
    Status = gBS->CloseProtocol (
                         BtHcDev->ControllerHandle,
                         &gEfiBluetoothHcProtocolGuid,
                         BtHcDev->DriverBindingHandle,
                         BtLeSbDev->DeviceHandle
                        );
    ASSERT_EFI_ERROR (Status);

    //
    // Destroy the Ble device handle.
    // It will call BluetoothAttributeDriverBindingStop()
    //
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    BtLeSbDev->DeviceHandle,
                    &gEfiDevicePathProtocolGuid, BtLeSbDev->DevicePath,
                    &gEfiBluetoothAttributeServiceBindingProtocolGuid, &BtLeSbDev->ServiceBinding,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      Status =  gBS->OpenProtocol (
                       BtHcDev->ControllerHandle,
                       &gEfiBluetoothHcProtocolGuid,
                       (VOID **)&BluetoothHc,
                       BtHcDev->DriverBindingHandle,
                       BtLeSbDev->DeviceHandle,
                       EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                       );
      ASSERT_EFI_ERROR (Status);
      return FALSE;
      //
      // TODO: iLE stack should take care of the return status. Currently not!
      //
    }

    OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
    RemoveEntryList (&BtLeSbDev->Link);
    gBS->RestoreTPL (OldTpl);
  }

  FreePool (BtLeSbDev->DevicePath);
  FreePool (BtLeSbDev);

  return TRUE;
}

/**
  Connect a BluetoothLE device.

  The Connect() function connects a Bluetooth device. When this function is returned successfully,
  a new EFI_BLUETOOTH_IO_PROTOCOL is created.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  AutoReconnect     If TRUE, the BluetoothLE host controller needs to do an auto
                                reconnect. If FALSE, the BluetoothLE host controller does not do
                                an auto reconnect.
  @param[in]  DoBonding         If TRUE, the BluetoothLE host controller needs to do a bonding.
                                If FALSE, the BluetoothLE host controller does not do a bonding.
  @param[in]  ConnectParameter  If it is not NULL, the ConnectParameter is used to perform a
                                scan by the BluetoothLE bus driver. If it is NULL, the default
                                parameter is used.
  @param[in]  BD_ADDR           The address of the BluetoothLE device to be connected.

  @retval EFI_SUCCESS           The BluetoothLE device is connected successfully.
  @retval EFI_ALREADY_STARTED   The BluetoothLE device is already connected.
  @retval EFI_NOT_FOUND         The BluetoothLE device is not found.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to connect the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigConnect (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL            *This,
  IN  BOOLEAN                                     AutoReconnect,
  IN  BOOLEAN                                     DoBonding,
  IN  EFI_BLUETOOTH_LE_CONFIG_CONNECT_PARAMETER   *ConnectParameter, OPTIONAL
  IN  BLUETOOTH_LE_ADDRESS                        *BD_ADDR
  )
{
  BTHC_DEV                        *BtHcDev;
  BT_LE_SB_DEV                    *BtLeSbDev;
  BT_LE_DEV_INFO                  *BtLeDevInfo;
  BT_LE_PAIRED_DEV_INFO           *BtLePairedDevInfo;
  EFI_STATUS                      Status;

  BtHcDev = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL (This);

  DEBUG ((EFI_D_INFO, "BluetoothLeConfigConnect\n"));

  BtLeDevInfo = BtLeFindDeviceInfo (BtHcDev, BD_ADDR);
  if (BtLeDevInfo == NULL) {
    BtLePairedDevInfo = BtFindLePairedDevByBDAddr(BtHcDev, BD_ADDR);
    if (BtLePairedDevInfo != NULL) {
      /* Add device to local list */
      if (!BtLeUpdateDevice(BtHcDev, &BtLePairedDevInfo->BDAddr, &BtLePairedDevInfo->IDAddr,
                        NULL, 0, 0, 0, 0, NULL, NULL, 0, TRUE)) {
        return EFI_PROTOCOL_ERROR;
      }
    } else {
      DEBUG ((EFI_D_INFO, "BluetoothLeConfigConnect - DevInfo NOT FOUND\n"));
      return EFI_NOT_FOUND;
    }
  }

  BtLeSbDev = BtFindLeSbDevByBDaddr (BtHcDev, BD_ADDR);
  if (BtLeSbDev != NULL) {
    DEBUG ((EFI_D_INFO, "BluetoothLeConfigConnect - BtSbDev already exist\n"));
    return EFI_ALREADY_STARTED;
  }

  Status = stack_connect (BD_ADDR, ConnectParameter, AutoReconnect, DoBonding);
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_INFO, "BluetoothLeConfigConnect - Enter BtDelIoDev\n"));
    BtLeSbDev = BtFindLeSbDevByBDaddr (BtHcDev, BD_ADDR);
    if (BtLeSbDev != NULL) {
      BtDelLeSb (BtHcDev, BtLeSbDev);
    }
    DEBUG ((EFI_D_INFO, "BluetoothLeConfigConnect - %r\n", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

/**
  Adds a BluetoothLE device into the paired device list.

  @param[in]  BtHcDev      A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr       A pointer to a Bluetooth device address.
  @param[in]  IDAddr       A pointer to a device identity address.
  @param[in]  BluetoothHc  A pointer to a EFI_BLUETOOTH_HC_PROTOCOL instance.

  @retval  EFI_SUCCESS  This function always returns EFI_SUCCESS.

**/
EFI_STATUS
BtAddLePairedDev (
  IN BTHC_DEV                   *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS       *BDAddr,
  IN BLUETOOTH_LE_ADDRESS       *IDAddr,
  IN EFI_BLUETOOTH_HC_PROTOCOL  *BluetoothHc
  )
{
  BT_LE_PAIRED_DEV_INFO         *LePairedDevInfo;

  ASSERT (BDAddr != NULL);
  ASSERT (IDAddr != NULL);
  LePairedDevInfo = BtFindLePairedDevByBDAddr (BtHcDev, BDAddr);
  if(LePairedDevInfo == NULL){
    LePairedDevInfo = AllocateZeroPool (sizeof (BT_LE_PAIRED_DEV_INFO));
    if (LePairedDevInfo == NULL) {
      DEBUG ((EFI_D_ERROR, "AllocateZeroPool failed for %d bytes", sizeof(BT_LE_PAIRED_DEV_INFO)));
      return EFI_OUT_OF_RESOURCES;
    }
    LePairedDevInfo->Signature = BT_LE_PAIRED_DEV_INFO_SIGNATURE;
    CopyMem (&LePairedDevInfo->BDAddr, BDAddr, sizeof (BLUETOOTH_LE_ADDRESS));
    CopyMem (&LePairedDevInfo->IDAddr, IDAddr, sizeof (BLUETOOTH_LE_ADDRESS));
    InsertTailList (&BtHcDev->BtLePairedList, &LePairedDevInfo->Link);
  }
  return EFI_SUCCESS;
}

/**
  Disconnect a BluetoothLE device.

  The Disconnect() function disconnects a BluetoothLE device. When this function is returned
  successfully, the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL associated with this device is
  destroyed and all services associated are stopped.

  @param[in]  This          Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  BD_ADDR       The address of BluetoothLE device to be connected.
  @param[in]  Reason        Bluetooth disconnect reason. See Bluetooth specification for detail.

  @retval EFI_SUCCESS           The BluetoothLE device is disconnected successfully.
  @retval EFI_NOT_STARTED       The BluetoothLE device is not connected.
  @retval EFI_NOT_FOUND         The BluetoothLE device is not found.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to disconnect the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigDisconnect (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
  IN BLUETOOTH_LE_ADDRESS              *BD_ADDR,
  IN UINT8                             Reason
  )
{
  BTHC_DEV                           *BtHcDev;
  EFI_STATUS                         Status;
  BT_LE_SB_DEV                       *BtLeSbDev;

  Status = EFI_NOT_FOUND;
  BtHcDev = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);
  BtLeSbDev = BtFindLeSbDevByBDaddr(BtHcDev, BD_ADDR);

  if (Reason == BluetoothDisconnectReasonTypeRemoteDeviceTerminatedConnectionDueToLowResources) {
    /* User has Deleted device bonding information */
    stack_remove_device(BD_ADDR);
  }

  if (BtLeSbDev != NULL) {
    Status = stack_disconnect(BD_ADDR, BtLeSbDev->ConnectionId, Reason);
  }

  DEBUG ((EFI_D_INFO, "BluetoothLeConfigDisconnect\n"));

  return Status;
}

/**
  Send user authentication/authorization to remote device.

  The SendSmpAuthData() function sends user authentication/authorization to remote device. It
  should be used to send these information after the caller gets the request data from the callback
  function by RegisterSmpAuthCallback().

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  BDAddr          Remote BluetoothLE device address.
  @param[in]  EventDataType   Event data type in EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE.
  @param[in]  DataSize        The size of Data in bytes, of the data buffer specified by Data.
  @param[in]  Data            A pointer to the buffer of data that will be sent. The data format
                              depends on the type of SMP event data being responded to.

  @retval EFI_SUCCESS         The SMP authorization data is sent successfully.
  @retval EFI_NOT_READY       SMP is not in the correct state to receive the auth data.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigSendSmpAuthData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE   EventDataType,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  )
{
  return stack_smp_auth(BDAddr, EventDataType, DataSize, Data);
}
