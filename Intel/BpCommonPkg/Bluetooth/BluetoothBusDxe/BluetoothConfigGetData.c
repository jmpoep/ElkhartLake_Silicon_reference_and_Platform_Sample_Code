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
#include "uefi_app.h"

/**
  Gets a list of local available Bluetooth devices.

  @param[in]      This      Protocol instance pointer..
  @param[in,out]  DataSize  On input, indicates the size, in bytes, of
                            the data buffer specified by Data.
                            On output, indicates the amount of data
                            actually transferred.
  @param[in,out]  Data      A pointer to the buffer that will hold the returned
                            device address and address type information of all
                            local available Bluetooth devices.

  @retval EFI_INVALID_PARAMETER   The parameter Datasize was NULL.
  @retval EFI_BUFFER_TOO_SMALL    DataSize not big enough.
  @retval EFI_SUCCESS             The operation was successful.

**/
EFI_STATUS
BtLeConfigGetAvailableDeviceListHandler (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  )
{
  BTHC_DEV        *BtHcDevice;
  UINTN           Counter;
  LIST_ENTRY      *BtLeDevInfoList;
  LIST_ENTRY      *Link;
  BT_LE_DEV_INFO     *BtLeDevInfo;
  UINT8           *BD_Walker;

  if (DataSize == NULL){
    return EFI_INVALID_PARAMETER;
  }

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);
  BtLeDevInfoList = &BtHcDevice->BtLeDevInfoList;
  Counter = 0;

  for (Link = BtLeDevInfoList->ForwardLink;
       Link != BtLeDevInfoList;
       Link = Link->ForwardLink) {
        BtLeDevInfo = CR (
                  Link,
                  BT_LE_DEV_INFO,
                  Link,
                  BT_LE_DEV_INFO_SIGNATURE
                  );
          Counter++;
  }

  if (Counter == 0) {
    *DataSize = 0;
    return EFI_SUCCESS;
  }

  if (*DataSize < (Counter * sizeof(BLUETOOTH_LE_ADDRESS))) {
    *DataSize = Counter * sizeof(BLUETOOTH_LE_ADDRESS);
    return EFI_BUFFER_TOO_SMALL;
  }

  Counter = 0;
  BD_Walker = (UINT8*)Data;

  for (Link = BtLeDevInfoList->ForwardLink;
       Link != BtLeDevInfoList;
       Link = Link->ForwardLink) {
    BtLeDevInfo = CR (
                  Link,
                  BT_LE_DEV_INFO,
                  Link,
                  BT_LE_DEV_INFO_SIGNATURE
                  );
      CopyMem (BD_Walker + Counter * sizeof(BLUETOOTH_LE_ADDRESS),
             &BtLeDevInfo->BDAddr,
             sizeof(BLUETOOTH_LE_ADDRESS)
             );
      Counter++;
  }

  *DataSize = Counter * sizeof(BLUETOOTH_LE_ADDRESS);

  return EFI_SUCCESS;
}

/**
  Get BluetoothLE configuration data.

  The GetData() function returns BluetoothLE configuration data. For remote BluetoothLE device
  configuration data, please use GetRemoteData() function with valid BD_ADDR.

  @param[in]       This         Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]       DataType     Configuration data type.
  @param[in, out]  DataSize     On input, indicates the size, in bytes, of the data buffer specified by Data.
                                On output, indicates the amount of data actually returned.
  @param[in, out]  Data         A pointer to the buffer of data that will be returned.

  @retval EFI_SUCCESS           The BluetoothLE configuration data is returned successfully.
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
BluetoothLeConfigGetData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE      DataType,
  IN OUT UINTN                           *DataSize,
  IN OUT VOID                            *Data OPTIONAL
  )
{
  switch (DataType) {
    case EfiBluetoothConfigDataTypeAvailableDeviceList:
      return BtLeConfigGetAvailableDeviceListHandler (This, DataSize, Data);
    case EfiBluetoothConfigDataTypeBDADDR:
    case EfiBluetoothConfigDataTypeDeviceName:
    case EfiBluetoothConfigDataTypeIoCapability:
    case EfiBluetoothConfigDataTypeOOBDataFlag:
    case EfiBluetoothConfigDataTypeKeyType:
    case EfiBluetoothConfigDataTypeEncKeySize:
      return stack_get_local_data(DataType, DataSize, Data);
    default:
      return EFI_INVALID_PARAMETER;
  }

}

