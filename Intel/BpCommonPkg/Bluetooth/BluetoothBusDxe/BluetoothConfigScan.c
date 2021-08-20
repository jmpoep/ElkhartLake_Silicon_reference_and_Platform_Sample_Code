//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The file implements interfaces defined in EFI_BLUETOOTH_CONFIG_PROTOCOL.

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
#include <IndustryStandard/BluetoothAssignedNumbers.h>
#include "uefi_app.h"

/**
  Sets the validity of BluetoothLE devices.

  If a BluetoothLE device has already been discovered, the validity attribute
  will be set to TRUE. Otherwise, FALSE will be set.

  @param[in]  BtHcDev  A pointer to the BTHC_DEV structure.

**/
VOID
BtLeSetDeviceInfoInvalid (
  IN BTHC_DEV                     *BtHcDev
  )
{
  LIST_ENTRY    *BtLeDevInfoList;
  LIST_ENTRY    *Link;
  BT_LE_DEV_INFO   *BtLeDevInfo;
  BT_LE_SB_DEV     *BtLeSbDev;
  EFI_TPL       OldTpl;

  BtLeDevInfoList = &BtHcDev->BtLeDevInfoList;

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  Link = GetFirstNode(BtLeDevInfoList);
  while (!IsNull(BtLeDevInfoList, Link))
  {
    BtLeDevInfo = CR (
                  Link,
                  BT_LE_DEV_INFO,
                  Link,
                  BT_LE_DEV_INFO_SIGNATURE
                  );

    BtLeSbDev = BtFindLeSbDevByBDaddr(BtHcDev, &BtLeDevInfo->BDAddr);
    if (BtLeSbDev == NULL) {
      Link = RemoveEntryList(Link);
      if (BtLeDevInfo->AdvertisementData != NULL) {
        FreePool(BtLeDevInfo->AdvertisementData);
      }
      FreePool(BtLeDevInfo);
    } else {
      Link = GetNextNode(BtLeDevInfoList, Link);
    }
  }
  gBS->RestoreTPL (OldTpl);

  return ;
}

/**
  Gets the device information of a BluetoothLE device specified by the
  Bluetooth device address.

  @param[in]  BtHcDev  A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr   A pointer to a Bluetooth device address.

  @retval  A pointer to the BT_LE_DEV_INFO structure which contains the device
           information for the specified BluetoothLE device.
  @retval  NULL  If a BluetoothLE device with address specified by 'BDAddr'
           cannot be found.

**/
BT_LE_DEV_INFO *
BtLeFindDeviceInfo (
  IN BTHC_DEV                     *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS         *BDAddr
  )
{
  LIST_ENTRY     *BtLeDevInfoList;
  LIST_ENTRY     *Link;
  BT_LE_DEV_INFO *BtLeDevInfo;
  BtLeDevInfoList = &BtHcDev->BtLeDevInfoList;

  for (Link = BtLeDevInfoList->ForwardLink; Link != BtLeDevInfoList; Link = Link->ForwardLink) {
    BtLeDevInfo = CR (Link, BT_LE_DEV_INFO, Link, BT_LE_DEV_INFO_SIGNATURE);

    /* Currently checking only with BD Address as Stack in not returning the correct BD Address Type in case of Privacy 1.2.
     * TODO: Check with BD Address Type as well. */
    if ((CompareMem (&BtLeDevInfo->BDAddr.Address, &BDAddr->Address, sizeof(BDAddr->Address)) == 0) ||
        ((CompareMem (&BtLeDevInfo->IDAddr.Address, &BDAddr->Address, sizeof(BDAddr->Address)) == 0))) {
      return BtLeDevInfo;
    }
  }

  return NULL;
}

/**
  Gets the data needed for the scan callback function call of a BluetoothLE
  device.

  @param[in]   BtHcDev             A pointer to the BTHC_DEV structure.
  @param[in]   BDAddr              A pointer to a Bluetooth device address.
  @param[out]  LeScanCallbackInfo  A pointer to store the scan callback
                                   function data of the a BluetoothLE device.

  @retval  FALSE  Fail to get the scan callback function data.
  @retval  TRUE   Successfully get the scan callback function data.

**/
BOOLEAN
BtLeGetScanCallBackInformation(
  IN  BTHC_DEV                                    *BtHcDev,
  IN  BLUETOOTH_LE_ADDRESS                        *BDAddr,
  OUT EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION  *LeScanCallbackInfo
)
{
  BT_LE_DEV_INFO             *BtLeDevInfo;
  BT_LE_SB_DEV               *BtLeSbDev;
  BT_LE_PAIRED_DEV_INFO      *BtLePairedDev;
  BtLeDevInfo = BtLeFindDeviceInfo(BtHcDev, BDAddr);
  if (BtLeDevInfo == NULL){
    return FALSE;
  }

  ZeroMem (LeScanCallbackInfo, sizeof (EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION));
  CopyMem (&LeScanCallbackInfo->BDAddr, &BtLeDevInfo->BDAddr, sizeof(BLUETOOTH_LE_ADDRESS));
  CopyMem (&LeScanCallbackInfo->DirectAddress, &BtLeDevInfo->Direct_BD_ADDR, sizeof(BLUETOOTH_LE_ADDRESS));
  LeScanCallbackInfo->RSSI = BtLeDevInfo->RSSI;
  LeScanCallbackInfo->AdvertisementDataSize = BtLeDevInfo->AdvertisementDataSize;
  LeScanCallbackInfo->AdvertisementData = AllocateZeroPool (BtLeDevInfo->AdvertisementDataSize);
  ASSERT (LeScanCallbackInfo->AdvertisementData != NULL);
  CopyMem (LeScanCallbackInfo->AdvertisementData, BtLeDevInfo->AdvertisementData, BtLeDevInfo->AdvertisementDataSize);

  LeScanCallbackInfo->RemoteDeviceState = 0x00;
  BtLeSbDev = BtFindLeSbDevByBDaddr(BtHcDev, BDAddr);
  if (BtLeSbDev != NULL) {
    (LeScanCallbackInfo->RemoteDeviceState) |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
  }
  BtLePairedDev = BtFindLePairedDevByBDAddr(BtHcDev, BDAddr);
  if (BtLePairedDev != NULL) {
    (LeScanCallbackInfo->RemoteDeviceState) |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED;
  }

  return TRUE;

}

/**
  Add the device information of a BluetoothLE device to the device information
  list.

  @param[in]  BtHcDev                A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr                 A pointer to a Bluetooth device address.
  @param[in]  IDAddr                 A pointer to a device identity address.
  @param[in]  Direct_BD_ADDR         A pointer to a direct Bluetooth device
                                     address.
  @param[in]  RSSI                   The Bluetooth RSSI.
  @param[in]  TxPower                The transmitted power level of the packet
                                     containing the data type.
  @param[in]  Appearance             The external appearance of the device.
  @param[in]  RoleSupported          The LE role capabilities of the device.
  @param[in]  LocalReadableName      The local name assigned to the device.
  @param[in]  AdvertisementData      A pointer to the BluetoothLEadvertisement
                                     data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.

  @retval  TRUE   Device information of the specific BluetoothLE device has
                  been added successfully.
  @retval  FALSE  Device information of the specific BluetoothLE device has not
                  been added.

**/
BOOLEAN
BtLeAddDevice (
  IN BTHC_DEV                      *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS          *BDAddr,
  IN BLUETOOTH_LE_ADDRESS          *IDAddr,
  IN BLUETOOTH_LE_ADDRESS          *Direct_BD_ADDR,
  IN INT8                          RSSI,
  IN UINT8                         TxPower,
  IN UINT16                        Appearance,
  IN UINT8                         RoleSupported,
  IN UINT8                         *LocalReadableName,
  IN UINT8                         *AdvertisementData,
  IN UINT8                         AdvertisementDataSize
  )
{
  BT_LE_DEV_INFO                                 *BtLeDevInfo;
  EFI_TPL                                        OldTpl;
  EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION     LeScanCallbackInfo;

  ASSERT (BDAddr != NULL);
  BtLeDevInfo = AllocateZeroPool (sizeof(*BtLeDevInfo));
  if (BtLeDevInfo == NULL) {
    DEBUG ((EFI_D_ERROR, "AllocateZeroPool failed for %d bytes", sizeof(*BtLeDevInfo)));
    return FALSE;
  }
  BtLeDevInfo->Signature = BT_LE_DEV_INFO_SIGNATURE;
  CopyMem (&BtLeDevInfo->BDAddr, BDAddr, sizeof(BtLeDevInfo->BDAddr));
  if (IDAddr != NULL) {
    CopyMem (&BtLeDevInfo->IDAddr, IDAddr, sizeof(BtLeDevInfo->IDAddr));
  }
  CopyMem (&BtLeDevInfo->Direct_BD_ADDR, Direct_BD_ADDR, sizeof(BtLeDevInfo->Direct_BD_ADDR));
  BtLeDevInfo->RSSI = RSSI;

  BtLeDevInfo->AdvertisementDataSize = AdvertisementDataSize;
  BtLeDevInfo->AdvertisementData = AllocateZeroPool (AdvertisementDataSize);
  ASSERT (BtLeDevInfo->AdvertisementData != NULL);
  CopyMem (BtLeDevInfo->AdvertisementData, AdvertisementData, AdvertisementDataSize);

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  InsertTailList (&BtHcDev->BtLeDevInfoList, &BtLeDevInfo->Link);
  gBS->RestoreTPL (OldTpl);

  if (BtHcDev->LeScanCallBackFunc != NULL) {
    BtLeGetScanCallBackInformation (BtHcDev, BDAddr, &LeScanCallbackInfo);
    BtHcDev->LeScanCallBackFunc (&BtHcDev->BluetoothLeConfig, BtHcDev->LeScanCallBackFuncContext, &LeScanCallbackInfo);
  }
  return TRUE;
}

/**
  Updates the device information of a BluetoothLE device.

  @param[in]  BtHcDev                A pointer to the BTHC_DEV structure.
  @param[in]  BDAddr                 A pointer to a Bluetooth device address.
  @param[in]  IDAddr                 A pointer to a device identity address.
  @param[in]  Direct_BD_ADDR         A pointer to a direct Bluetooth device
                                     address.
  @param[in]  RSSI                   The Bluetooth RSSI.
  @param[in]  TxPower                The transmitted power level of the packet
                                     containing the data type.
  @param[in]  Appearance             The external appearance of the device.
  @param[in]  RoleSupported          The LE role capabilities of the device.
  @param[in]  LocalReadableName      The local name assigned to the device.
  @param[in]  AdvertisementData      A pointer to the BluetoothLE advertisement
                                     data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.
  @param[in]  NeedAdd                Add the BluetoothLE device to the device
                                     information list or not.

  @retval  TRUE   Device information of the specific BluetoothLE device has
                  been updated successfully.
  @retval  FALSE  Device information of the specific BluetoothLE device has not
                  been updated.

**/
BOOLEAN
BtLeUpdateDevice (
  IN BTHC_DEV                      *BtHcDev,
  IN BLUETOOTH_LE_ADDRESS          *BDAddr,
  IN BLUETOOTH_LE_ADDRESS          *IDAddr,
  IN BLUETOOTH_LE_ADDRESS          *Direct_BD_ADDR,
  IN INT8                          RSSI,
  IN UINT8                         TxPower,
  IN UINT16                        Appearance,
  IN UINT8                         RoleSupported,
  IN UINT8                         *LocalReadableName,
  IN UINT8                         *AdvertisementData,
  IN UINT8                         AdvertisementDataSize,
  IN BOOLEAN                       NeedAdd
  )
{
  BT_LE_DEV_INFO                                *BtLeDevInfo;
  EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION    LeScanCallbackInfo;
  UINT8                                         *TempAdvData;
  UINTN                                         TempAdvDataSize;

  BtLeDevInfo = BtLeFindDeviceInfo (BtHcDev, BDAddr);
  if (BtLeDevInfo == NULL) {
    //
    // Not found
    //
    if (!NeedAdd) {
      return FALSE;
    }
    //
    // Add
    //
    return BtLeAddDevice (
             BtHcDev,
             BDAddr,
             IDAddr,
             Direct_BD_ADDR,
             RSSI,
             TxPower,
             Appearance,
             RoleSupported,
             LocalReadableName,
             AdvertisementData,
             AdvertisementDataSize
           );
  }

  //
  // Update
  // Note: Do not update the Identity Address here
  //
  CopyMem (&BtLeDevInfo->BDAddr, BDAddr, sizeof(BtLeDevInfo->BDAddr));
  CopyMem (&BtLeDevInfo->Direct_BD_ADDR, Direct_BD_ADDR, sizeof(BtLeDevInfo->Direct_BD_ADDR));
  BtLeDevInfo->RSSI = RSSI;

  if (BtLeDevInfo->AdvertisementData != NULL) {
    // This is scan reponse packet, append the advertisement data
    TempAdvDataSize = BtLeDevInfo->AdvertisementDataSize + AdvertisementDataSize;
    TempAdvData = AllocateZeroPool (TempAdvDataSize);
    ASSERT (TempAdvData != NULL);
    if (BtLeDevInfo->AdvertisementData != NULL) {
      CopyMem (&TempAdvData[0], BtLeDevInfo->AdvertisementData, BtLeDevInfo->AdvertisementDataSize);
    }
    CopyMem (&TempAdvData[BtLeDevInfo->AdvertisementDataSize], AdvertisementData, AdvertisementDataSize);
  } else {
    // First time receiving the advertisement report during current scanning
    TempAdvDataSize = AdvertisementDataSize;
    TempAdvData = AllocateZeroPool (TempAdvDataSize);
    ASSERT (TempAdvData != NULL);
    CopyMem (TempAdvData, AdvertisementData, AdvertisementDataSize);
  }

  // Free previous advertisement data
  if (BtLeDevInfo->AdvertisementData != NULL) {
    FreePool(BtLeDevInfo->AdvertisementData);
  }

  BtLeDevInfo->AdvertisementDataSize = TempAdvDataSize;
  BtLeDevInfo->AdvertisementData = TempAdvData;

  if (BtHcDev->LeScanCallBackFunc != NULL) {
    BtLeGetScanCallBackInformation (BtHcDev, BDAddr, &LeScanCallbackInfo);
    BtHcDev->LeScanCallBackFunc (&BtHcDev->BluetoothLeConfig, BtHcDev->LeScanCallBackFuncContext, &LeScanCallbackInfo);
  }

  return TRUE;
}

/**
  Scans BluetoothLE devices.

  @param[in]  BtHcDev        A pointer to the BTHC_DEV structure.
  @param[in]  BluetoothHc    A pointer to the EFI_BLUETOOTH_HC_PROTOCOL
                             instance.
  @param[in]  Timeout        The timeout, in millisecond units, to use for the
                             execution of the scan. A Timeout value of 0 means
                             that this function will wait indefinitely for the
                             scan to complete.
  @param[in]  ScanParameter  If ScanParameter is not NULL, it is used to
                             perform a scan by the BluetoothLE bus driver.
                             Otherwise, the default parameter is used.

**/
VOID
BtLeScan (
  IN BTHC_DEV                                 *BtHcDev,
  IN EFI_BLUETOOTH_HC_PROTOCOL                *BluetoothHc,
  IN UINTN                                    Timeout,
  IN EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER   *ScanParameter OPTIONAL
  )
{

  BtLeSetDeviceInfoInvalid (BtHcDev);
  stack_scan ((UINT32)Timeout, ScanParameter);
}

/**
  Scan BluetoothLE device.

  The Scan() function scans BluetoothLE device. When this function is returned, it just means scan
  request is submitted. It does not mean scan process is started or finished. Whenever there is a
  BluetoothLE device is found, the Callback function will be called. Callback function might be
  called before this function returns or after this function returns

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  ReScan            If TRUE, a new scan request is submitted no matter there is scan result before.
                                If FALSE and there is scan result, the previous scan result is returned and no scan request
                                is submitted.
  @param[in]  Timeout           Duration in milliseconds for which to scan.
  @param[in]  ScanParameter     If it is not NULL, the ScanParameter is used to perform a scan by the BluetoothLE bus driver.
                                If it is NULL, the default parameter is used.
  @param[in]  Callback          The callback function. This function is called if a BluetoothLE device is found during
                                scan process.
  @param[in]  Context           Data passed into Callback function. This is optional parameter and may be NULL.

  @retval EFI_SUCCESS           The Bluetooth scan request is submitted.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to scan the BluetoothLE device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigScan (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL               *This,
  IN BOOLEAN                                        ReScan,
  IN UINT32                                         Timeout,
  IN EFI_BLUETOOTH_LE_CONFIG_SCAN_PARAMETER         *ScanParameter, OPTIONAL
  IN EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION Callback,
  IN VOID                                           *Context
  )
{
  BTHC_DEV                                    *BtHcDev;
  LIST_ENTRY                                  *Link;
  BT_LE_DEV_INFO                              *BtLeDevInfo;
  EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION  LeScanCallbackInfo;

  BtHcDev = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);
  BtHcDev->LeScanCallBackFunc = Callback;
  BtHcDev->LeScanCallBackFuncContext = Context;

  DEBUG ((EFI_D_INFO, "BluetoothLeConfigScan\n"));
  if ((!ReScan) && (BtHcDev->LeScanned)) {
    for ( Link = BtHcDev->BtLeDevInfoList.ForwardLink;
          Link != &BtHcDev->BtLeDevInfoList;
          Link = Link->ForwardLink
          ) {
      BtLeDevInfo = CR (Link, BT_LE_DEV_INFO, Link, BT_LE_DEV_INFO_SIGNATURE);
      BtLeGetScanCallBackInformation(BtHcDev, &BtLeDevInfo->BDAddr, &LeScanCallbackInfo);
      BtHcDev->LeScanCallBackFunc (&BtHcDev->BluetoothLeConfig, BtHcDev->LeScanCallBackFuncContext, &LeScanCallbackInfo);
    }
    BtHcDev->LeScanCallBackFunc (&BtHcDev->BluetoothLeConfig, BtHcDev->LeScanCallBackFuncContext, NULL);
    return EFI_SUCCESS;
  } else {
    BtLeScan (BtHcDev, BtHcDev->BluetoothHc, Timeout, ScanParameter);
    BtHcDev->LeScanned = TRUE;
  }

  return EFI_SUCCESS;
}

