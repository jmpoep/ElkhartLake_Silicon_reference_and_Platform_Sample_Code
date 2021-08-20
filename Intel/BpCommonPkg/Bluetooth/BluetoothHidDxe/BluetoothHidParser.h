//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 The header file of Bluetooth HID Parser.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#ifndef _BLUETOOTH_HID_PAESER_H_
#define _BLUETOOTH_HID_PAESER_H_

#include "BluetoothHidDxe.h"

#define BT_HID_REPORT_MAP_LEN 512

/**
  Report Map Parser Function for the Report Mde Operation of Bluetooth HID devices

  @param[in]  BtHidDev Pointer to Bluetooth HID Device Structure.

**/
VOID
BtHidParseReportMap (
  IN  BT_HID_DEV                  *BtHidDev
  );

/**
  Fetches the Head of the Link List having the report format structures
  @param[in]  This        A pointer to the BT_HID_DEV_FROM_HID_PROTOCOL
                          instance.
  @param[out] Head Pointer to Report format linked list.

  @retval  EFI_SUCCESS  The function completes successfully.

**/
EFI_STATUS
EFIAPI
BtHidGetReportFormatList (
  IN EDKII_HID_PROTOCOL *This,
  OUT LIST_ENTRY        **Head
  );

#endif

