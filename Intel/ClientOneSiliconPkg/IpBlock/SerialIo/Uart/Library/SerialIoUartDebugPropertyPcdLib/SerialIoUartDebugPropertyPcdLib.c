/** @file

  SerialIo Uart Debug Property Pcd Library

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Protocol/SerialIo.h>
#include <SerialIoDevices.h>

/**
  Returns UART attributes

  @param[in,out] Attributes          UART Attributes
**/
VOID
SerialIoUartDebugPcdGetAttributes (
  IN OUT SERIAL_IO_UART_ATTRIBUTES  *Attributes
  )
{
  Attributes->BaudRate = PcdGet32 (PcdSerialIoUartBaudRate);
  Attributes->DataBits = PcdGet8 (PcdSerialIoUartDataBits);
  Attributes->StopBits = (EFI_STOP_BITS_TYPE) PcdGet8 (PcdSerialIoUartStopBits);
  Attributes->Parity   = (EFI_PARITY_TYPE) PcdGet8 (PcdSerialIoUartParity);
  Attributes->AutoFlow = PcdGet8 (PcdSerialIoUartAutoFlow);
}

/**
  Returns Serial Io UART Controller Number used in Debug mode

  @retval  ControllerNumber   UART Controller Number
**/
UINT8
SerialIoUartDebugPcdGetControllerNumber (
  VOID
  )
{
  return PcdGet8 (PcdSerialIoUartNumber);
}

/**
  Returns Serial Io UART Debug Enable

  @retval  0 - Disabled
  @retval  1 - Enabled
  @retval  2 - Enabled without initializng
**/
UINT8
SerialIoUartDebugPcdGetDebugEnable (
  VOID
  )
{
  return PcdGet8 (PcdSerialIoUartDebugEnable);
}

/**
  Returns Serial Io UART MMIO Base Address

  @retval  MMIO Base Address by default in PCI Mode
**/
UINT32
SerialIoUartDebugPcdGetPciDefaultMmioBase (
  VOID
  )
{
  return PcdGet32 (PcdSerialIoUartDebugMmioBase);
}

/**
  Returns Serial Io UART PinMux Rx GPIO

  @param[in,out] Uart              UART Device Configuration
  @param[in,out] UartNumber        UART Device Number

**/
VOID
SerialIoUartDebugPcdGetDeviceConfig (
  IN OUT  SERIAL_IO_UART_CONFIG   *Uart,
  IN OUT  UINT8                   *UartNumber
  )
{
  *UartNumber = SerialIoUartDebugPcdGetControllerNumber ();
  SerialIoUartDebugPcdGetAttributes (&Uart->Attributes);
  Uart->PinMux.Rx  = PcdGet32 (PcdSerialIoUartRxPinMux);
  Uart->PinMux.Tx  = PcdGet32 (PcdSerialIoUartTxPinMux);
  Uart->PinMux.Rts = PcdGet32 (PcdSerialIoUartRtsPinMux);
  Uart->PinMux.Cts = PcdGet32 (PcdSerialIoUartCtsPinMux);
  Uart->Mode       = PcdGet8 (PcdSerialIoUartMode);
}
