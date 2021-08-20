//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The file implements interfaces defined in EFI_BLUETOOTH_CONFIG_PROTOCOL.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>
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
#include <Library/BluetoothLib.h>

/**
  Gets the name of a remote BluetoothLE device.

  @param[in]      This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                            instance.
  @param[in]      BDAddr    Remote BluetoothLE device address.
  @param[in,out]  DataSize  On input, indicates the size, in bytes, of the data
                            buffer specified by Data. On output, indicates the
                            amount of data actually returned.
  @param[in,out]  Data      A pointer to the buffer of data that will be
                            returned.

  @retval  EFI_BUFFER_TOO_SMALL  Buffer to small.
  @retval  EFI_NOT_FOUND         The specified BluetoothLE device is not found.
  @retval  EFI_SUCCESS           The operation was successful.

**/
EFI_STATUS
BtLeConfigGetRemoteDeviceNameHandler (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN OUT UINTN                              *DataSize,
  IN OUT VOID                               *Data OPTIONAL
  )
{
  BTHC_DEV                                  *BtHcDevice;
  BT_LE_DEV_INFO                            *BtLeDevInfo;
  UINT8                                     *Buf;
  UINT8                                     Len;

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);

  if (*DataSize < BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE) {
    *DataSize = BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE;
    return EFI_BUFFER_TOO_SMALL;
  }

  BtLeDevInfo = BtLeFindDeviceInfo (BtHcDevice, BDAddr);
  if (BtLeDevInfo == NULL) {
    return EFI_NOT_FOUND;
  }

  Buf = BluetoothFindTypeFromAdvData (BtLeDevInfo->AdvertisementData, BtLeDevInfo->AdvertisementDataSize, BluetoothGapTypeCompleteLocalName, &Len);
  if (Buf == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Only use *DataSize bytes as the device name if the device name in ADV data is too long.
  //
  if (*DataSize > Len) {
    *DataSize = Len;
  }
  CopyMem (Data, Buf, *DataSize);
  return EFI_SUCCESS;
}

/**
  Gets the RSSI of a remote BluetoothLE device.

  @param[in]      This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                            instance.
  @param[in]      BDAddr    Remote BluetoothLE device address.
  @param[in,out]  DataSize  On input, indicates the size, in bytes, of the data
                            buffer specified by Data. On output, indicates the
                            amount of data actually returned.
  @param[in,out]  Data      A pointer to the buffer of data that will be
                            returned.

  @retval  EFI_BUFFER_TOO_SMALL  Buffer to small.
  @retval  EFI_NOT_FOUND         The specified BluetoothLE device is not found.
  @retval  EFI_SUCCESS           The operation was successful.

**/
EFI_STATUS
BtLeConfigGetRemoteRssiHandler (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *This,
  IN BLUETOOTH_LE_ADDRESS                *BDAddr,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  )
{
  BTHC_DEV                                  *BtHcDevice;
  BT_LE_DEV_INFO                               *BtLeDevInfo;

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);

  if (*DataSize < sizeof(INT8)) {
    *DataSize = sizeof(INT8);
    return EFI_BUFFER_TOO_SMALL;
  }

  BtLeDevInfo = BtLeFindDeviceInfo (BtHcDevice, BDAddr);
  if (BtLeDevInfo == NULL) {
    return EFI_NOT_FOUND;
  }

  *((UINT8*)Data) = BtLeDevInfo->RSSI;
  *DataSize = sizeof(INT8);

  return EFI_SUCCESS;
}

/**
  Gets the advertisement report data of a remote BluetoothLE device.

  @param[in]      This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                            instance.
  @param[in]      BDAddr    Remote BluetoothLE device address.
  @param[in,out]  DataSize  On input, indicates the size, in bytes, of the data
                            buffer specified by Data. On output, indicates the
                            amount of data actually returned.
  @param[in,out]  Data      A pointer to the buffer of data that will be
                            returned.

  @retval  EFI_BUFFER_TOO_SMALL  Buffer to small.
  @retval  EFI_NOT_FOUND         The specified BluetoothLE device is not found.
  @retval  EFI_SUCCESS           The operation was successful.

**/
EFI_STATUS
BtLeConfigGetRemoteAdvDataHandler (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  )
{
  BTHC_DEV                                  *BtHcDevice;
  BT_LE_DEV_INFO                               *BtLeDevInfo;

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);

  if (*DataSize < BLUETOOTH_LE_ADV_DATA_MAX_SIZE) {
    *DataSize = BLUETOOTH_LE_ADV_DATA_MAX_SIZE;
    return EFI_BUFFER_TOO_SMALL;
  }

  BtLeDevInfo = BtLeFindDeviceInfo (BtHcDevice, BDAddr);
  if (BtLeDevInfo == NULL) {
    return EFI_NOT_FOUND;
  }

  CopyMem (Data, BtLeDevInfo->AdvertisementData, BLUETOOTH_LE_ADV_DATA_MAX_SIZE);
  *DataSize = BLUETOOTH_LE_ADV_DATA_MAX_SIZE;

  return EFI_SUCCESS;
}

/**
  Gets the state of a remote BluetoothLE device.

  @param[in]      This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                            instance.
  @param[in]      BDAddr    Remote BluetoothLE device address.
  @param[in,out]  DataSize  On input, indicates the size, in bytes, of the data
                            buffer specified by Data. On output, indicates the
                            amount of data actually returned.
  @param[in,out]  Data      A pointer to the buffer of data that will be
                            returned.

  @retval  EFI_BUFFER_TOO_SMALL   Buffer to small.
  @retval  EFI_INVALID_PARAMETER  Data is NULL.
  @retval  EFI_NOT_FOUND          The specified BluetoothLE device is not
                                  found.
  @retval  EFI_SUCCESS            The operation was successful.

**/
EFI_STATUS
BtLeConfigGetRemoteDeviceStateHandler (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  )
{
  UINT8                                           RemoteDevState;
  BTHC_DEV                                        *BtHcDevice;
  BT_LE_DEV_INFO                                     *BtLeDevInfo;
  BT_LE_SB_DEV                                       *BtLeSbDev;
  BT_LE_PAIRED_DEV_INFO                         *BtLePairedDevList;

  RemoteDevState = 0;

  if (*DataSize < sizeof(UINT8)) {
    *DataSize = sizeof(UINT8);
    return EFI_BUFFER_TOO_SMALL;
  }

  if (Data == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);
  BtLeDevInfo = BtLeFindDeviceInfo(BtHcDevice, BDAddr);
  if (BtLeDevInfo == NULL) {
    return  EFI_NOT_FOUND;
  }

  BtLeSbDev = BtFindLeSbDevByBDaddr(BtHcDevice, BDAddr);
  if (BtLeSbDev != NULL) {
    RemoteDevState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
  }

  BtLePairedDevList = BtFindLePairedDevByBDAddr(BtHcDevice, BDAddr);
  if (BtLePairedDevList != NULL) {
    RemoteDevState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED;
  }

  *((UINT8*)Data) = RemoteDevState;
  *DataSize = sizeof(UINT8);

  return EFI_SUCCESS;
}

/**
  Get remove BluetoothLE device configuration data.

  The GetRemoteData() function returns remote BluetoothLE device configuration data.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  DataType          Configuration data type.
  @param[in]  BDAddr            Remote BluetoothLE device address.
  @param[in, out] DataSize      On input, indicates the size, in bytes, of the data buffer specified by Data.
                                On output, indicates the amount of data actually returned.
  @param[in, out] Data          A pointer to the buffer of data that will be returned.

  @retval EFI_SUCCESS           The remote BluetoothLE device configuration data is returned successfully.
  @retval EFI_INVALID_PARAMETER One or more of the following conditions is TRUE:
                                - DataSize is NULL.
                                - *DataSize is 0.
                                - Data is NULL.
  @retval EFI_UNSUPPORTED       The DataType is unsupported.
  @retval EFI_NOT_FOUND         The DataType is not found.
  @retval EFI_BUFFER_TOO_SMALL  The buffer is too small to hold the buffer.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigGetRemoteData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE         DataType,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN OUT UINTN                              *DataSize,
  IN OUT VOID                               *Data OPTIONAL
  )
{
  switch (DataType) {
    case EfiBluetoothConfigDataTypeDeviceName:
      return BtLeConfigGetRemoteDeviceNameHandler (This, BDAddr, DataSize, Data);
    case EfiBluetoothConfigDataTypeRemoteDeviceState:
      return BtLeConfigGetRemoteDeviceStateHandler (This, BDAddr, DataSize, Data);
    case EfiBluetoothConfigDataTypeRSSI:
    return BtLeConfigGetRemoteRssiHandler (This, BDAddr, DataSize, Data);
    case EfiBluetoothConfigDataTypeAdvertisementData:
    return BtLeConfigGetRemoteAdvDataHandler (This, BDAddr, DataSize, Data);
    case EfiBluetoothConfigDataTypeRandomAddress:
    // TODO: Implement in stack
    default:
      return EFI_INVALID_PARAMETER;
  }
}

