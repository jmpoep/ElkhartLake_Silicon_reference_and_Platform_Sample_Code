//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The header file contains definitions/structures that are not
  defined in UEFI Spec but are used by current BLE stack.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __EFI_BLUETOOTH_LE_CONFIG_X_H__
#define __EFI_BLUETOOTH_LE_CONFIG_X_H__

#include <Protocol/BluetoothLeConfig.h>

enum {
  EfiBluetoothSmpPeerAddress = EfiBluetoothSmpLocalDIV + 1,
};

#endif
