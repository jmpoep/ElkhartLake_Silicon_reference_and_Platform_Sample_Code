/** @file
  PCH default USB OverCurrent Port mapping tables

@copyright
 Copyright (c) 2018 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the
  license agreement.
**/

#include <PlatformBoardConfig.h>

// Default USB2 OC mapping
USB_OC_MAP_TABLE mUsb2OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPinSkip,    // Port 1
  UsbOverCurrentPinSkip,    // Port 2
  UsbOverCurrentPinSkip,    // Port 3
  UsbOverCurrentPinSkip,    // Port 4
  UsbOverCurrentPinSkip,    // Port 5
  UsbOverCurrentPinSkip,    // Port 6
  UsbOverCurrentPinSkip,    // Port 7
  UsbOverCurrentPinSkip,    // Port 8
  UsbOverCurrentPinSkip,    // Port 9
  UsbOverCurrentPinSkip,    // Port 10
  UsbOverCurrentPinSkip,    // Port 11
  UsbOverCurrentPinSkip,    // Port 12
  UsbOverCurrentPinSkip,    // Port 13
  UsbOverCurrentPinSkip,    // Port 14
  UsbOverCurrentPinSkip,    // Port 15
  UsbOverCurrentPinSkip     // Port 16
);

// Default USB3 OC mapping
USB_OC_MAP_TABLE mUsb3OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPinSkip,    // Port 1
  UsbOverCurrentPinSkip,    // Port 2
  UsbOverCurrentPinSkip,    // Port 3
  UsbOverCurrentPinSkip,    // Port 4
  UsbOverCurrentPinSkip,    // Port 5
  UsbOverCurrentPinSkip,    // Port 6
  UsbOverCurrentPinSkip,    // Port 7
  UsbOverCurrentPinSkip,    // Port 8
  UsbOverCurrentPinSkip,    // Port 9
  UsbOverCurrentPinSkip     // Port 10
);