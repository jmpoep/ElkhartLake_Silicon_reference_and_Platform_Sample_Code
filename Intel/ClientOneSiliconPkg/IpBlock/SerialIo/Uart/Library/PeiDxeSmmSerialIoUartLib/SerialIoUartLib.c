/** @file
  Serial IO UART Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include "SerialIoUartPrivateLib.h"

/**
  Polls a serial device to see if there is any data waiting or pending for read.
  If there is data pending, then TRUE is returned.
  If there is no data, then FALSE is returned.

  @param[in]  UartNumber   Selects Serial IO UART device

  @retval TRUE             Data is waiting to read from the serial device.
  @retval FALSE            There is no data waiting to read from the serial device.
**/
BOOLEAN
EFIAPI
SerialIoUartPolling (
  IN  UINT8         UartNumber
  )
{
  UART_ACCESS_MODE     AccessMode;
  UINT64               BaseAddress;
  SERIAL_IO_UART_LSR   Lsr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return FALSE;
  }

  //
  // Read the serial port status
  //
  Lsr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LSR);
  return (BOOLEAN) Lsr.Fields.DR;
}

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
  )
{
  BOOLEAN           UseTimeout;
  UINTN             Timeout;
  UINT32            Index;
  UART_ACCESS_MODE  AccessMode;
  UINT64            BaseAddress;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return 0;
  }
  if ((NULL == Buffer) || (SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_USR) == 0xFF)) {
    return 0;
  }

  UseTimeout = TRUE;

  //
  // If Timeout is equal to 0, then timeout is disabled
  //
  Timeout = PcdGet32 (PcdSerialIoUartTimeOut);
  if (Timeout == 0) {
    UseTimeout = FALSE;
  }
  for (Index = 0; Index < NumberOfBytes; Index++) {
    while (!SerialIoUartTransmit (AccessMode, BaseAddress, Buffer[Index])) {
      if (UseTimeout == TRUE) {
        //
        // Unsuccessful write so check if timeout has expired, if not,
        // stall for a bit, increment time elapsed, and try again
        //
        if (Timeout == 0) {
          // If Auto Flow is already disabled, and timeout was reached return
          if (SerialIoUartGetAutoFlow (UartNumber) == FALSE) {
            return 0;
          }
          //
          // Disable AutoFlow Control if data did not come out of the FIFO in given time
          //
          SerialIoUartSetAutoFlow (UartNumber, FALSE);
          Timeout = PcdGet32 (PcdSerialIoUartTimeOut);
        }
        MicroSecondDelay (SERIALIO_UART_TIMEOUT_DELAY_INTERVAL);
        Timeout -= SERIALIO_UART_TIMEOUT_DELAY_INTERVAL;
      }
    }
  }

  return NumberOfBytes;
}

/*
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
  )
{
  UINTN                BytesReceived;
  UINT64               BaseAddress;
  UART_ACCESS_MODE     AccessMode;
  SERIAL_IO_UART_LSR   Lsr;
  UINT8                Byte;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return 0;
  }
  if ((NULL == Buffer) || (SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_USR) == 0xFF)) {
    return 0;
  }

  BytesReceived = 0;

  while (BytesReceived != NumberOfBytes) {
    Lsr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LSR);
    //
    // If there is data in the RX buffer, read it.
    //
    if (Lsr.Fields.DR != 0) {
      Byte = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_RXBUF);
      //
      // Check if the break interrupt bit is set. If set, the byte read from the
      // RX buffer is invalid and should be ignored. If not set, copy the byte into
      // the receive buffer.
      //
      if (Lsr.Fields.BI == 0) {
        *Buffer = Byte;
        Buffer++;
        BytesReceived++;
      }
    } else {
      if (!WaitUntilBufferFull) {
        //
        // If there's no data and function shouldn't wait, exit early
        //
        return BytesReceived;
      }
    }
  }
  return BytesReceived;
}

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
  )
{
  SerialIoUartFifoEnable  (UartNumber);
  SerialIoUartSetBaudRate (UartNumber, BaudRate);
  SerialIoUartSetParity   (UartNumber, Parity);
  SerialIoUartSetDataBits (UartNumber, DataBits);
  SerialIoUartSetStopBits (UartNumber, StopBits);
  SerialIoUartSetAutoFlow (UartNumber, AutoFlow);
}

/**
  Dummy Read required after setting/clearing 16550 8bit mode

  @param[in] UartNumber         UART Number
**/
VOID
SerialIoUartDummyRead (
  IN UINT8        UartNumber
  )
{
  UINT64  BaseAddress;
  UINT64  PciCfgBase;

  PciCfgBase  = GetSerialIoUartPciCfg (UartNumber);
  BaseAddress = GetSerialIoBar (PciCfgBase);
  if ((BaseAddress == 0xFFFFFFFFFFFFF000ULL) || (BaseAddress == 0xFFFFF000ULL) || (BaseAddress == 0x0)) {
    return;
  }
  MmioRead8 ((UINTN) BaseAddress + R_PCH_SERIAL_IO_32BIT_UART_CTR);
}

/**
  Gets UART out of reset

  @param[in]  BaseAddress    Base address of UART MMIO space
**/
VOID
SerialIoUartGetOutOfReset (
  IN UINT64            MmioBaseAddress
  )
{
  UINT16    ResetOffset;

  ResetOffset = R_SERIAL_IO_MEM_PPR_RESETS;

  if (MmioRead32 ((UINTN) (MmioBaseAddress + R_PCH_SERIAL_IO_32BIT_UART_CTR)) != UART_COMPONENT_IDENTIFICATION_CODE) {
    ResetOffset = R_SERIAL_IO_MEM_PPR_RESETS_8BIT;
  }
  MmioOr8 ((UINTN) (MmioBaseAddress + ResetOffset),
               B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA);
}

/**
  Return whether UART is in PCI mode or not

  @param[in] UartNumber         UART Number

  @retval                       TRUE  - UART is in PCI mode
  @retval                       FALSE - UART is in Hidden mode or disabled
**/
BOOLEAN
IsSerialIoUartInPciMode (
  IN UINT8        UartNumber
  )
{
  UINT64  PciCfgBase;

  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoUartDeviceNumber (UartNumber),
                 GetSerialIoUartFunctionNumber (UartNumber),
                 0
                 );
  if (PciSegmentRead16 (PciCfgBase) != MAX_UINT16) {
    return TRUE;
  } else {
    return FALSE;
  }
}

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
  )
{
  UINT64  PciCfgBase;

  if (!IsSerialIoUartInPciMode (UartNumber)) {
    return EFI_UNSUPPORTED;
  }

  PciCfgBase  = GetSerialIoUartPciCfg (UartNumber);

  SerialIoSetD3 (PciCfgBase);
  SerialIoDisableMse (PciCfgBase);

  //
  // Assign MMIO Base Address
  //
  PciSegmentWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, MmioBaseAddress & MAX_UINT32);
  PciSegmentWrite32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + 4, RShiftU64 (MmioBaseAddress, 32) & MAX_UINT32);

  SerialIoSetD0 (PciCfgBase);
  SerialIoEnableMse (PciCfgBase, FALSE);

  return EFI_SUCCESS;
}

/**
  Returns UART's currently active access mode, 8 or 32 bit

  @param[in]  BaseAddress    Base address of UART MMIO space

  @retval     AccessMode8bit
  @retval     AccessMode32bit
**/
STATIC
UART_ACCESS_MODE
DetectAccessMode (
  IN UINT64  BaseAddress
  )
{
  if (MmioRead32 ((UINTN) BaseAddress + R_PCH_SERIAL_IO_32BIT_UART_CTR) == UART_COMPONENT_IDENTIFICATION_CODE) {
    return AccessMode32bit;
  } else {
    return AccessMode8bit;
  }
}

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
  )
{
  UINT64           Base;
  UINTN            Divisor;
  UART_ACCESS_MODE AccessMode;
  UINT64           PciCfgBase;

  PciCfgBase  = GetSerialIoUartPciCfg (UartNumber);
  Base        = GetSerialIoBar (PciCfgBase);

  if ((Base == 0xFFFFFFFFFFFFF000ULL) || (Base == 0xFFFFF000ULL) || (Base == 0x0)) {
    //
    // Base is not programmed, skip it.
    //
    return;
  }
  SerialIoEnableMse (PciCfgBase, IsSerialIoUartHidden (UartNumber));
  AccessMode = DetectAccessMode (Base);

  Divisor = 115200 / BaudRate;

  //
  // Configure baud rate
  //
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_LCR, B_PCH_SERIAL_IO_UART_LCR_DLAB);
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_BAUD_HIGH, (UINT8) (Divisor >> 8));
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_BAUD_LOW, (UINT8) (Divisor & 0xff));
  //
  //  Configure Line control and switch back to bank 0
  //
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_LCR, LineControl & 0x1F);
  //
  // Enable and reset FIFOs
  //
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_FCR, FifoEnable?B_PCH_SERIAL_IO_UART_FCR_FCR:0 );
  //
  // Put Modem Control Register(MCR) into its reset state of 0x00.
  //
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_MCR, B_PCH_SERIAL_IO_UART_MCR_RTS | (HardwareFlowControl?B_PCH_SERIAL_IO_UART_MCR_AFCE:0));
}

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
  )
{
  UINT64           Base;
  UART_ACCESS_MODE AccessMode;

  UINT8            Mcr;
  UINT64           PciCfgBase;

  //
  // First determine the parameter is invalid.
  //
  if ((Control & (~(EFI_SERIAL_REQUEST_TO_SEND | EFI_SERIAL_DATA_TERMINAL_READY |
                    EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE))) != 0) {
    return EFI_UNSUPPORTED;
  }

  PciCfgBase  = GetSerialIoUartPciCfg (UartNumber);
  Base        = GetSerialIoBar (PciCfgBase);

  if ((Base == 0xFFFFFFFFFFFFF000ULL) || (Base == 0xFFFFF000ULL) || (Base == 0x0)) {
    return EFI_UNSUPPORTED;
  }

  SerialIoEnableMse (PciCfgBase, IsSerialIoUartHidden (UartNumber));
  AccessMode = DetectAccessMode (Base);

  //
  // Read the Modem Control Register.
  //

  Mcr = SerialIoUartReadRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_MCR);

  Mcr &= (~(B_PCH_SERIAL_IO_UART_MCR_DTRC | B_PCH_SERIAL_IO_UART_MCR_RTS));

  if ((Control & EFI_SERIAL_DATA_TERMINAL_READY) == EFI_SERIAL_DATA_TERMINAL_READY) {
    Mcr |= B_PCH_SERIAL_IO_UART_MCR_DTRC;
  }

  if ((Control & EFI_SERIAL_REQUEST_TO_SEND) == EFI_SERIAL_REQUEST_TO_SEND) {
    Mcr |= B_PCH_SERIAL_IO_UART_MCR_RTS;
  }

  //
  // Write the Modem Control Register.
  //
  SerialIoUartWriteRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_MCR, Mcr);

  return EFI_SUCCESS;
}

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
  )
{
  UINT64            Base;
  UART_ACCESS_MODE AccessMode;

  UINT8            Msr;
  UINT8            Mcr;
  UINT8            Lsr;
  UINT64           PciCfgBase;

  PciCfgBase  = GetSerialIoUartPciCfg (UartNumber);
  Base        = GetSerialIoBar (PciCfgBase);

  if ((Base == 0xFFFFFFFFFFFFF000ULL) || (Base == 0xFFFFF000ULL) || (Base == 0x0)) {
    return EFI_UNSUPPORTED;
  }

  SerialIoEnableMse (PciCfgBase, IsSerialIoUartHidden (UartNumber));
  AccessMode = DetectAccessMode (Base);

  *Control = 0;

  //
  // Read the Modem Status Register.
  //

  Msr = SerialIoUartReadRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_MSR);

  if ((Msr & B_PCH_SERIAL_IO_UART_MSR_CTS) == B_PCH_SERIAL_IO_UART_MSR_CTS) {
    *Control |= EFI_SERIAL_CLEAR_TO_SEND;
  }

  if ((Msr & B_PCH_SERIAL_IO_UART_MSR_DSR) == B_PCH_SERIAL_IO_UART_MSR_DSR) {
    *Control |= EFI_SERIAL_DATA_SET_READY;
  }

  if ((Msr & B_PCH_SERIAL_IO_UART_MSR_RI) == B_PCH_SERIAL_IO_UART_MSR_RI) {
    *Control |= EFI_SERIAL_RING_INDICATE;
  }

  if ((Msr & B_PCH_SERIAL_IO_UART_MSR_DCD) == B_PCH_SERIAL_IO_UART_MSR_DCD) {
    *Control |= EFI_SERIAL_CARRIER_DETECT;
  }

  //
  // Read the Modem Control Register.
  //
  Mcr = SerialIoUartReadRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_MCR);

  if ((Mcr & B_PCH_SERIAL_IO_UART_MCR_DTRC) == B_PCH_SERIAL_IO_UART_MCR_DTRC) {
    *Control |= EFI_SERIAL_DATA_TERMINAL_READY;
  }

  if ((Mcr & B_PCH_SERIAL_IO_UART_MCR_RTS) == B_PCH_SERIAL_IO_UART_MCR_RTS) {
    *Control |= EFI_SERIAL_REQUEST_TO_SEND;
  }

  if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
    *Control |= EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE;
  }

  //
  // Read the Line Status Register.
  //
  Lsr = SerialIoUartReadRegister (AccessMode, Base, R_PCH_SERIAL_IO_8BIT_UART_LSR);

  if ((Lsr & (B_PCH_SERIAL_IO_UART_LSR_TEMT | B_PCH_SERIAL_IO_UART_LSR_TXRDY)) == (B_PCH_SERIAL_IO_UART_LSR_TEMT | B_PCH_SERIAL_IO_UART_LSR_TXRDY)) {
    *Control |= EFI_SERIAL_OUTPUT_BUFFER_EMPTY;
  }

  if ((Lsr & B_PCH_SERIAL_IO_UART_LSR_RXDA) == 0) {
    *Control |= EFI_SERIAL_INPUT_BUFFER_EMPTY;
  }

  return EFI_SUCCESS;
}

