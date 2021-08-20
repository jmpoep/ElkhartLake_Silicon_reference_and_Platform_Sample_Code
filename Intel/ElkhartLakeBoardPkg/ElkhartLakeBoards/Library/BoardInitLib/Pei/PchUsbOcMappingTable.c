/** @file
  PCH USB OverCurrent Port mapping tables

@copyright
 Copyright (c) 2018 - 2019 Intel Corporation. All rights reserved
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

#include "PchUsbOcMappingTable.h"

// ElkhartLake ERB and RVP board specific USB2 OC mapping
USB_OC_MAP_TABLE mEhlErbRvpUsb2OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin3,       // Port 1
  UsbOverCurrentPin3,       // Port 2
  UsbOverCurrentPin3,       // Port 3
  UsbOverCurrentPin3,       // Port 4
  UsbOverCurrentPinSkip,    // Port 5
  UsbOverCurrentPin2,       // Port 6
  UsbOverCurrentPin2,       // Port 7
  UsbOverCurrentPin2,       // Port 8
  UsbOverCurrentPin2,       // Port 9
  UsbOverCurrentPinSkip     // Port 10
);

// ElkhartLake ERB and RVP board specific USB3 OC mapping
USB_OC_MAP_TABLE mEhlErbRvpUsb3OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin3,       // Port 1
  UsbOverCurrentPin3,       // Port 2
  UsbOverCurrentPin3,       // Port 3
  UsbOverCurrentPin3        // Port 4
);

// ElkhartLake CRB board specific USB2 OC mapping
USB_OC_MAP_TABLE mEhlCrbUsb2OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin3,       // Port 1
  UsbOverCurrentPin3,       // Port 2
  UsbOverCurrentPinSkip,    // Port 3
  UsbOverCurrentPin3,       // Port 4
  UsbOverCurrentPin3,       // Port 5
  UsbOverCurrentPinSkip,    // Port 6
  UsbOverCurrentPinSkip,    // Port 7
  UsbOverCurrentPinSkip,    // Port 8
  UsbOverCurrentPinSkip,    // Port 9
  UsbOverCurrentPinSkip     // Port 10
);

// ElkhartLake CRB board specific USB3 OC mapping
USB_OC_MAP_TABLE mEhlCrbUsb3OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin3,       // Port 1
  UsbOverCurrentPin3,       // Port 2
  UsbOverCurrentPin3,       // Port 3
  UsbOverCurrentPin3        // Port 4
);

// JasperLake specific USB2 OC mapping
USB_OC_MAP_TABLE mJslUsb2OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin0,       // Port 1
  UsbOverCurrentPin2,       // Port 2
  UsbOverCurrentPin0,       // Port 3
  UsbOverCurrentPinSkip,    // Port 4
  UsbOverCurrentPinSkip,    // Port 5
  UsbOverCurrentPin3,       // Port 6
  UsbOverCurrentPin2,       // Port 7
  UsbOverCurrentPin3,       // Port 8
);

// JasperLake specific USB3 OC mapping
USB_OC_MAP_TABLE mJslUsb3OverCurrentMappingTable = USB_OC_MAP_TABLE_INIT (
  UsbOverCurrentPin0,       // Port 1
  UsbOverCurrentPin0,       // Port 2
  UsbOverCurrentPin2,       // Port 3
  UsbOverCurrentPin3,       // Port 4
  UsbOverCurrentPin3,       // Port 5
  UsbOverCurrentPin2        // Port 6
);
