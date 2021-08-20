/** @file
  Include for Serial Io Uart Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _SERIAL_IO_UART_DRIVER_H_
#define _SERIAL_IO_UART_DRIVER_H_

#include <Protocol/SerialIo.h>
#include <Protocol/DriverBinding.h>
#include <Library/UefiLib.h>

#define SERIAL_IO_UART_DEV_SIGNATURE    SIGNATURE_32 ('S', 'E', 'R', 'U')
#define SERIAL_IO_UART_NAME L"Serial IO UART Driver Controller #%d"
#define SERIAL_IO_UART_DEV_FROM_THIS(a) CR (a, SERIAL_IO_UART_DEV, SerialIoProtocol, SERIAL_IO_UART_DEV_SIGNATURE)

typedef struct {
  ACPI_EXTENDED_HID_DEVICE_PATH   AcpiExtendedPath;
  CHAR8                           HidString[8];
  UINT16                          DeviceId;
  UINT8                           UartIndex;
} SERIAL_IO_UART_ACPI_EXTENDED_DEVICE_PATH;

typedef struct {
  UINTN                     Signature;
  EFI_HANDLE                Handle;
  EFI_SERIAL_IO_PROTOCOL    SerialIoProtocol;
  EFI_SERIAL_IO_MODE        SerialIoMode;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *ParentDevicePath;
  UART_DEVICE_PATH          UartDevicePath;
  UINT8                     UartIndex;
  BOOLEAN                   AutoFlow;
  EFI_UNICODE_STRING_TABLE  *ControllerNameTable;
} SERIAL_IO_UART_DEV;

#endif // _SERIAL_IO_UART_DRIVER_H_
