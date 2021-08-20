//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The file implements some interfaces of EFI_BLUETOOTH_CONFIG_PROTOCOL.

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
  Set BluetoothLE configuration data.

  The SetData() function sets local BluetoothLE device configuration data. Not all DataType can be
  set.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.
  @param[in]  DataType          Configuration data type.
  @param[in]  DataSize          Indicates the size, in bytes, of the data buffer specified by Data.
  @param[in]  Data              A pointer to the buffer of data that will be set.

  @retval EFI_SUCCESS           The BluetoothLE configuration data is set successfully.
  @retval EFI_INVALID_PARAMETER One or more of the following conditions is TRUE:
                                - DataSize is 0.
                                - Data is NULL.
  @retval EFI_UNSUPPORTED       The DataType is unsupported.
  @retval EFI_WRITE_PROTECTED   Cannot set configuration data.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigSetData (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN EFI_BLUETOOTH_CONFIG_DATA_TYPE         DataType,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
)
{
  switch (DataType) {
    case EfiBluetoothConfigDataTypeDeviceName:
    case EfiBluetoothConfigDataTypeIoCapability:
    case EfiBluetoothConfigDataTypeOOBDataFlag:
    case EfiBluetoothConfigDataTypeKeyType:
    case EfiBluetoothConfigDataTypeEncKeySize:
      return stack_set_local_data(DataType, DataSize, Data);
    default:
      return EFI_INVALID_PARAMETER;
  }
}

