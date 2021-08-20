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
  Initialize BluetoothLE host controller and local device.

  The Init() function initializes BluetoothLE host controller and local device.

  @param[in]  This              Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL instance.

  @retval EFI_SUCCESS           The BluetoothLE host controller and local device is initialized successfully.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to initialize the BluetoothLE host controller
                                and local device.

**/
EFI_STATUS
EFIAPI
BluetoothLeConfigInit (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This
  )
{
  BTHC_DEV                      *BtHcDevice;

  if (EfiGetCurrentTpl() != TPL_APPLICATION) {
    return EFI_ACCESS_DENIED;
  }

  BtHcDevice = BTHC_DEV_FROM_BLUETOOTH_LE_CONFIG_PROTOCOL(This);

  // Proceed with Stack initialization
  stack_init(BtHcDevice);

  return EFI_SUCCESS;
}
