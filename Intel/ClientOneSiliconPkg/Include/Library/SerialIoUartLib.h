/** @file
  Header file for Serial IO UART Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _SERIAL_IO_UART_LIB_H_
#define _SERIAL_IO_UART_LIB_H_

#include <Protocol/SerialIo.h>

/**
  Polls a serial device to see if there is any data waiting or pending for read.
  If there is data pending, then TRUE is returned.
  If there is no data, then FALSE is returned.

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval TRUE             Data is waiting to read from the serial device.
  @retval FALSE            There is no data waiting to read from the serial device.
**/
BOOLEAN
EFIAPI
SerialIoUartPolling (
  IN  UINT8         UartNumber
  );

/**
  Write data to serial device.

  If the buffer is NULL, then return 0;
  if NumberOfBytes is zero, then return 0.

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  Buffer           Data pointer
  @param[in]  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval                      Actual number of bytes written to serial device.
**/
UINTN
EFIAPI
SerialIoUartWrite (
  IN UINT8            UartNumber,
  IN UINT8            *Buffer,
  IN UINTN            NumberOfBytes
  );

/**
  Read data from serial device and save the data in buffer.

  If the buffer is NULL, then return 0;
  if NumberOfBytes is 0, then return 0.

  @param[in]   UartNumber           Selects Serial IO UART device
  @param[out]  Buffer               Pointer to the buffer that will contain the return data
  @param[in]   NumberOfBytes        Number of input bytes to read
  @param[in]   WaitUntilBufferFull  TRUE  - function waits until whole buffer is filled.
                                    FALSE - function returns as soon as no new characters are available.

  @retval                           Actual number of bytes raed to serial device.
**/
UINTN
EFIAPI
SerialIoUartRead (
  IN  UINT8            UartNumber,
  OUT UINT8            *Buffer,
  IN  UINTN            NumberOfBytes,
  IN  BOOLEAN          WaitUntilBufferFull
  );


/**
  Sets the baud rate, parity, data bits, flow control and stop bits on a serial device.

  @param[in]  UartNumber   Selects Serial IO UART device
  @param[in]  BaudRate     The requested baud rate. A BaudRate value of 0 will use the the
                           device's default interface speed.
  @param[in]  Parity       The type of parity to use on this serial device. A Parity value of
                           DefaultParity will use the device's default parity value.
  @param[in]  DataBits     The number of data bits to use on the serial device. A DataBits
                           value of 0 will use the device's default data bit setting.
  @param[in]  StopBits     The number of stop bits to use on this serial device. A StopBits
                           value of DefaultStopBits will use the device's default number of
                           stop bits.
  @param[in]  AutoFlow     Enable/Disable Auto Flow Control
**/
VOID
SerialIoUartSetAttributes (
  IN UINT8               UartNumber,
  IN UINT64              BaudRate,
  IN EFI_PARITY_TYPE     Parity,
  IN UINT8               DataBits,
  IN EFI_STOP_BITS_TYPE  StopBits,
  IN BOOLEAN             AutoFlow
  );

/**
  Dummy Read required after setting/clearing 16550 8bit mode

  @param[in] UartNumber         UART Number
**/
VOID
SerialIoUartDummyRead (
  IN UINT8        UartNumber
  );

/**
  Gets UART out of reset

  @param[in]  BaseAddress    Base address of UART MMIO space
**/
VOID
SerialIoUartGetOutOfReset (
  IN UINT64       MmioBaseAddress
  );

/**
  Return whether UART is in PCI mode or not

  @param[in] UartNumber         UART Number

  @retval                       TRUE  - UART is in PCI mode
  @retval                       FALSE - UART is in Hidden mode or disabled
**/
BOOLEAN
IsSerialIoUartInPciMode (
  IN UINT8        UartNumber
  );

/**
  Assign MMIO Resource in PCI Mode.

  @param[in] UartNumber         UART Number
  @param[in] MmioBaseAddress    Base address of UART MMIO space

  @retval EFI_UNSUPPORTED       SerialIo UART isn't in PCI mode.
  @retval EFI_SUCCESS           Finish to set SerialIo UART MMIO in PCI mode.

**/
EFI_STATUS
SerialIoUartSetMmioInPciMode (
  IN UINT8        UartNumber,
  IN UINT64       MmioBaseAddress
  );

/**
  Initialize selected SerialIo UART.
  This init function MUST be used prior any SerialIo UART functions to init serial io controller if platform is going use serialio UART as debug output.

  @param  UartNumber           Selects Serial IO UART device (0-2)
  @param  FifoEnable           When TRUE, enables 64-byte FIFOs.
  @param  BaudRate             Baud rate.
  @param  LineControl          Data length, parity, stop bits.
  @param  HardwareFlowControl  Automated hardware flow control. If TRUE, hardware automatically checks CTS when sending data, and sets RTS when receiving data.
**/
VOID
EFIAPI
PchSerialIoUartInit (
  UINT8            UartNumber,
  BOOLEAN          FifoEnable,
  UINT32           BaudRate,
  UINT8            LineControl,
  BOOLEAN          HardwareFlowControl
  );

/**
  Sets the control bits on a serial device.

  @param Control                Sets the bits of Control that are settable.

  @retval EFI_SUCCESS           The new control bits were set on the serial device.
  @retval EFI_UNSUPPORTED       The serial device does not support this operation.
  @retval EFI_DEVICE_ERROR      The serial device is not functioning correctly.

**/
EFI_STATUS
EFIAPI
SerialIoUartSetControl (
  IN UINT8  UartNumber,
  IN UINT32 Control
  );

/**
  Retrieve the status of the control bits on a serial device.

  @param Control                A pointer to return the current control signals from the serial device.

  @retval EFI_SUCCESS           The control bits were read from the serial device.
  @retval EFI_UNSUPPORTED       The serial device does not support this operation.
  @retval EFI_DEVICE_ERROR      The serial device is not functioning correctly.

**/
EFI_STATUS
EFIAPI
SerialIoUartGetControl (
  IN  UINT8  UartNumber,
  OUT UINT32 *Control
  );

#endif // _SERIAL_IO_UART_LIB_H_
