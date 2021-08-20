/** @file
  Install Base and Size Info Ppi for Firmware Volume Recovery.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef __RECOVERY__H__
#define __RECOVERY__H__

#include <Ppi/DeviceRecoveryModule.h>

#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>

#define COM1_BASE_ADDR              ((UINTN) PcdGet64 (PcdSerialRegisterBase)) // COM1 Address
#define SERIAL_DATA_REG             COM1_BASE_ADDR + 00
#define DIVISOR_LATCH_LSB_REG       COM1_BASE_ADDR + 00
#define DIVISOR_LATCH_MSB_REG       COM1_BASE_ADDR + 01
#define INTERRUPT_ENABLE_REG        COM1_BASE_ADDR + 01
#define FIFO_CONTROL_REG            COM1_BASE_ADDR + 02
#define LINE_CONTROL_REG            COM1_BASE_ADDR + 03
#define MODEM_CONTROL_REG           COM1_BASE_ADDR + 04
#define LINE_STATUS_REG             COM1_BASE_ADDR + 05
#define MODEM_STATUS_REG            COM1_BASE_ADDR + 06
#define BAUD_DIVISOR_LSB            0x0001
#define BAUD_DIVISOR_MSB            0x0000
#define MAX_USER_DELAY              0x1E84EC      // Wait for user response in 15 microseconds units
#define MAX_DATA_DELAY              0x1046A       // Wait for data byte in 50 microseconds units
#define MAX_DATA1_DELAY             0x28B0A
#define MAX_RESP_DELAY              0x1E          // Max Response time in 1 second units
#define XMODEM_SOH                    0x01        // Start Header
#define XMODEM_EOT                    0x04        // End of Transfer
#define XMODEM_ACK                    0x06        // Acknowledge
#define XMODEM_NAK                    0x15        // Negative Acknowledge
#define XMODEM_CAN                    0x18        // Cancel Transfer

//
// Function Prototypes
//
VOID
SendSerialChar (
  CHAR8 c
  );

BOOLEAN
GetSerialData1 (
  UINT8* ReadData
  );

BOOLEAN
GetSerialData (
  UINT8* ReadData
  );

VOID
SendSerialData (
  UINT8 d
  );

VOID
SendSerialString (
  CHAR8* Str
  );

BOOLEAN
GetSerialChar (
  CHAR8* ReadChar
  );

VOID
PrintCopyRightMessage (
  );

VOID
InitSerialPort (
);

EFI_STATUS
EFIAPI
GetNumberRecoveryCapsules (
  IN  EFI_PEI_SERVICES                      **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI    *This,
  OUT UINTN                                 *NumberRecoveryCapsules
);

EFI_STATUS
EFIAPI
GetRecoveryCapsuleInfo (
  IN  EFI_PEI_SERVICES                      **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI    *This,
  IN  UINTN                                 CapsuleInstance,
  OUT UINTN                                 *Size,
  OUT EFI_GUID                              *CapsuleType
);

EFI_STATUS
EFIAPI
SerialLoadRecoveryCapsule (
  IN  OUT EFI_PEI_SERVICES                  **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI    *This,
  IN  UINTN                                 CapsuleInstance,
  OUT VOID                                  *Buffer
);

BOOLEAN ReadFileFromSerial (
  CHAR8*  Buffer,
  UINT32* Size,
  UINT8   *Result
);

BOOLEAN ReadSerialBlock (
  UINT8*  Buffer
);

BOOLEAN SendNakAck (
  UINT8*  Data,
  UINT8   XCommand
);

#endif
