//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Definitions for Bluetooth HID layer.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __BLUETOOTH_HID_H__
#define __BLUETOOTH_HID_H__

#pragma pack(1)

//
// Human Interface Device
//

typedef enum {
  BluetoothHidTransactionHandshake = 0x0,
  BluetoothHidTransactionHidControl = 0x1,
  BluetoothHidTransactionGetReport = 0x4,
  BluetoothHidTransactionSetReport = 0x5,
  BluetoothHidTransactionGetProtocol = 0x6,
  BluetoothHidTransactionSetProtocol = 0x7,
  BluetoothHidTransactionGetIdle = 0x8,
  BluetoothHidTransactionSetIdle = 0x9,
  BluetoothHidTransactionData = 0xA,
  BluetoothHidTransactionDataContinue = 0xB,
} BLUETOOTH_HID_TRANSACTION_TYPE;

typedef enum {
  BluetoothHidBootProtocol = 0x0,
  BluetoothHidReportProtocol = 0x1,
} BLUETOOTH_HID_PROTOCOL;

typedef enum {
  BluetoothHidInputReport = 0x1,
  BluetoothHidOutputReport = 0x2,
  BluetoothHidFeatureReport = 0x3,
} BLUETOOTH_HID_REPORT_TYPE;

typedef enum {
  BluetoothHidReportIdKeyboard = 0x1,
  BluetoothHidReportIdMouse = 0x2,
} BLUETOOTH_HID_REPORT_ID;

typedef struct {
  UINT8    TransactionType:4;
  UINT8    Parameter:4;
} BLUETOOTH_HID_TRANSACTION_HEADER;

typedef struct {
  BLUETOOTH_HID_TRANSACTION_HEADER  Header;
  UINT8                             ReportId;
  UINT16                            BufferSize;
} BLUETOOTH_HID_TRANSACTION_GET_REPORT;

typedef struct {
  BLUETOOTH_HID_TRANSACTION_HEADER  Header;
  UINT8                             ReportId;
  UINT16                            BufferSize;
//UINT8                             Buffer[];
} BLUETOOTH_HID_TRANSACTION_SET_REPORT;

typedef struct {
  BLUETOOTH_HID_TRANSACTION_HEADER  Header;
} BLUETOOTH_HID_TRANSACTION_GET_PROTOCOL;

typedef struct {
  BLUETOOTH_HID_TRANSACTION_HEADER  Header;
} BLUETOOTH_HID_TRANSACTION_SET_PROTOCOL;

#pragma pack()

#endif

