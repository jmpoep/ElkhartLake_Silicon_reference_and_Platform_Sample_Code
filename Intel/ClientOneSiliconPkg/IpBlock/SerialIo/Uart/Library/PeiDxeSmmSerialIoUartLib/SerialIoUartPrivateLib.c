/** @file

  Serial IO UART private Lib implementation.

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
#include <Library/SerialIoUartLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>

/**
  Enables UART in Hidden mode

  @param[in]      UartNumber     Selects Serial IO UART device
  @param[in]      PciCfgBase     Pci Config Space Address
  @param[in/out]  BaseAddress    Base address of UART MMIO space

  @retval   TRUE             UART has BAR assigned
  @retval   FALSE            Unable to access UART's MMIO
**/
BOOLEAN
STATIC
SerialIoUartEnableHidden (
  IN     UINT8       UartNumber,
  IN     UINTN       PciCfgBase,
  IN OUT UINT64      *BaseAddress
  )
{
  PciCfgBase   = GetSerialIoUartFixedPciCfgAddress (UartNumber);
  *BaseAddress = GetSerialIoBar (PciCfgBase);
  if ((*BaseAddress == 0xFFFFFFFFFFFFF000ULL) || (*BaseAddress == 0xFFFFF000ULL) || (*BaseAddress == 0x0)) {
    return FALSE;
  }
  if ((MmioRead8 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS) & (BIT0 | BIT1)) != 0x0) { //Check PG only
    MmioAndThenOr8 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT8)~B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST, 0x0); // Place device in D0
    MmioRead8 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS); // Dummy Read after modifying PME
    SerialIoUartGetOutOfReset (*BaseAddress);
  }
  return TRUE;
}

/**
  Enables UART in Pci mode

  @param[in]      UartNumber     Selects Serial IO UART device
  @param[in]      PciCfgBase     Pci Config Space Address
  @param[in/out]  BaseAddress    Base address of UART MMIO space

  @retval   TRUE             UART has BAR assigned
  @retval   FALSE            Unable to access UART's MMIO
**/
BOOLEAN
STATIC
SerialIoUartEnablePci (
  IN UINT8           UartNumber,
  IN UINTN           PciCfgBase,
  IN OUT UINT64      *BaseAddress
  )
{
  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoUartDeviceNumber (UartNumber),
                 GetSerialIoUartFunctionNumber (UartNumber),
                 0
                 );
  if (MmioRead32 (PciCfgBase) == 0xFFFFFFFF) {
    return FALSE;
  }
  *BaseAddress = GetSerialIoBar (PciCfgBase);
  if ((*BaseAddress == 0xFFFFFFFFFFFFF000ULL) || (*BaseAddress == 0xFFFFF000ULL) || (*BaseAddress == 0x0)) {
    return FALSE;
  }
  if ((PciSegmentRead8 (PciCfgBase + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) != EFI_PCI_COMMAND_MEMORY_SPACE) {
    PciSegmentOr8 (PciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE); // Enable MSE
    PciSegmentAndThenOr8 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT8)~B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST, 0x0); // Place device in D0
    PciSegmentRead8 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS); // Dummy Read after modifying PME
    SerialIoUartGetOutOfReset (*BaseAddress);
  }
  return TRUE;
}

/**
  Enables UART regardless of the current mode 8/32bit
  - Places device in D0
  - Enables MSE
  - Gets Controller out of Reset

  @param[in]      UartNumber     Selects Serial IO UART device
  @param[in/out]  BaseAddress    Base address of UART MMIO space
  @param[in/out]  AccessMode     Selects between 8bit access to 1-byte aligned registers or 32bit access to 4-byte algined

  @retval   TRUE             UART is Enabled, Out Of reset, MMIO is available
  @retval   FALSE            Unable to access UART's MMIO
**/
BOOLEAN
SerialIoUartEnable (
  IN UINT8                 UartNumber,
  IN OUT UINT64            *BaseAddress,
  IN OUT UART_ACCESS_MODE  *AccessMode
  )
{
  UINTN     PciCfgBase;
  PciCfgBase = 0;

  *BaseAddress = 0;
  if (PcdGetBool (PcdSerialIoUartLibSkipMmioCheck)) {
    PciCfgBase = GetSerialIoUartFixedPciCfgAddress (UartNumber);
    *BaseAddress = (MmioRead32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFF000) + LShiftU64 (MmioRead32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + 4), 32);
  } else {
    if (IsSerialIoUartHidden (UartNumber)) {
      if (!SerialIoUartEnableHidden (UartNumber, PciCfgBase, BaseAddress)) {
        return FALSE;
      }
    } else {
      if (!SerialIoUartEnablePci (UartNumber, PciCfgBase, BaseAddress)) {
        return FALSE;
      }
    }
  }
  //
  // Device is still not enabled, or there is no BAR assigned
  //
  if ((*BaseAddress == 0xFFFFFFFFFFFFF000ULL) || (*BaseAddress == 0x0)) {
    return FALSE;
  }
  if (MmioRead32 ((UINTN) *BaseAddress + R_PCH_SERIAL_IO_32BIT_UART_CTR) == UART_COMPONENT_IDENTIFICATION_CODE) {
    *AccessMode = AccessMode32bit;
  } else {
    *AccessMode = AccessMode8bit;
  }

  return TRUE;
}

/**
  Register access helper. Depending on SerialIO UART mode,
  its registers are aligned to 1 or 4 bytes and have 8 or 32bit size

  @param[in]  AccessMode     Selects between 8bit access to 1-byte aligned registers or 32bit access to 4-byte algined
  @param[in]  BaseAddress    Base address of UART MMIO space
  @param[in]  Offset         Register offset in 8bit mode
  @param[in]  Data           Data to be written
**/
VOID
SerialIoUartWriteRegister (
  IN UART_ACCESS_MODE Mode,
  IN UINT64           BaseAddress,
  IN UINTN            Offset,
  IN UINT8            Data
  )
{
  if (Mode == AccessMode32bit) {
    MmioWrite32 ((UINTN) BaseAddress + 4 * Offset, Data);
  } else {
    MmioWrite8 ((UINTN) BaseAddress + Offset, Data);
  }
}

/**
  Register access helper. Depending on SerialIO UART mode,
  its registers are aligned to 1 or 4 bytes and have 8 or 32bit size

  @param[in]  AccessMode     Selects between 8bit access to 1-byte aligned registers or 32bit access to 4-byte algined
  @param[in]  BaseAddress    Base address of UART MMIO space
  @param[in]  Offset         Register offset in 8bit mode

  @retval                    retrieved register value, always 8bit regardless of access mode
**/
UINT8
SerialIoUartReadRegister (
  IN UART_ACCESS_MODE Mode,
  IN UINT64           BaseAddress,
  IN UINTN            Offset
  )
{
  if (Mode == AccessMode32bit) {
    return (UINT8) (0xFF & MmioRead32 ((UINTN) BaseAddress + 4*Offset));
  }
  return MmioRead8 ((UINTN) BaseAddress + Offset);
}

/**
  Checks if Tx Fifo is not full

  @param[in]  AccessMode       8bit/32bit register layout
  @param[in]  BaseAddress      Base Address Regiser offset (BAR0)

  @retval TRUE                 Fifo is not full
          FALSE                Fifo is full
**/
BOOLEAN
STATIC
SerialIoUartIsTxFifoNotFull (
  IN UART_ACCESS_MODE AccessMode,
  IN UINT64           BaseAddress
  )
{
  SERIAL_IO_UART_USR  Usr;
  Usr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_USR);
  return (BOOLEAN) Usr.Fields.TFNF;
}

/**
  Writes data to the serial device only if Fifo is ready for it

  @param[in]  AccessMode       8bit/32bit register layout
  @param[in]  BaseAddress      Base Address Regiser offset (BAR0)
  @param[in]  Data             Data to transmit

  @retval TRUE             Data was sent out
          FALSE            No data transmitted
**/
BOOLEAN
SerialIoUartTransmit (
  IN UART_ACCESS_MODE  AccessMode,
  IN UINT64            BaseAddress,
  IN UINT8             Data
  )
{
  if (SerialIoUartIsTxFifoNotFull (AccessMode, BaseAddress)) {
    SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_TXBUF, Data);
    return TRUE;
  }
  return FALSE;
}

/**
  Sets BaudRate along with adjusted Clock M/N divider

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  BaudRate         Baud Rate

**/
VOID
SerialIoUartSetBaudRate (
  IN UINT8   UartNumber,
  IN UINT64  BaudRate
  )
{
  UART_ACCESS_MODE      AccessMode;
  UINT64                BaseAddress;
  SERIAL_IO_UART_CLOCK  Clock;
  SERIAL_IO_UART_LCR    Lcr;
  UINT64                ComputedDivisor;
  UINT32                ClockRate;
  UINT16                ClockOffset;

  ClockOffset = R_SERIAL_IO_MEM_PPR_CLK;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }
  if (AccessMode == AccessMode8bit) {
    ClockOffset = ClockOffset / 4;
  }

  //
  // Default 115200 settings
  //
  ComputedDivisor = 1;
  ClockRate       = 1843200;

  //
  //  Set default Baudrate based on Pcd
  //
  if (BaudRate == 0) {
    BaudRate = PcdGet64 (PcdUartDefaultBaudRate);
  }

  if (BaudRate > MAX_BAUDRATE) {
    return;
  }

  //
  // Clock defaults
  //
  Clock.Data              = MmioRead32 ((UINTN) BaseAddress + ClockOffset);
  Clock.Fields.N          = V_SERIAL_IO_MEM_PPR_CLK_N_DIV;
  Clock.Fields.M          = V_SERIAL_IO_MEM_PPR_CLK_M_DIV;
  Clock.Fields.CLK_EN     = 1;
  Clock.Fields.CLK_UPDATE = 1;

  //
  //  Low Speed mode
  //
  if (BaudRate < 115200) {
    //
    // Compute divisor use to program the baud rate using a round determination
    // Divisor = ClockRate / 16 / BaudRate = ClockRate / (16 * BaudRate)
    //         = ClockRate / (BaudRate << 4)
    //
    ComputedDivisor = DivU64x64Remainder (ClockRate, LShiftU64 (BaudRate, 4), NULL);
    //
    // If the computed divisor is 0, then use a computed divisor of 1, which will select
    // the maximum supported baud rate.
    //
    if (ComputedDivisor == 0) {
      ComputedDivisor = 1;
    }
    //
    // If the computed divisor is larger than the maximum value that can be programmed
    // into the UART, then the requested baud rate can not be supported.
    //
    if (ComputedDivisor > MAX_UINT16) {
      return;
    }
  }

  //
  //  High Speed mode
  //
  if (BaudRate > 115200) {
    Clock.Fields.N = 32767;
    ClockRate = SOURCE_CLOCK;
    //  M = ((N * 16) * BaudRate) / ClockRate;
    Clock.Fields.M = (UINT16) DivU64x64Remainder (MultU64x32 (BaudRate, Clock.Fields.N << (UINT32) 4), ClockRate, NULL);
  }

  //
  // Update Clock
  //
  MmioWrite32 ((UINTN) BaseAddress + ClockOffset, Clock.Data);

  //
  // Disable Clock update
  //
  Clock.Data = MmioRead32 ((UINTN) BaseAddress + ClockOffset);
  Clock.Fields.CLK_UPDATE = 0;
  MmioWrite32 ((UINTN) BaseAddress + ClockOffset, Clock.Data);

  //
  // Open Divisor Latch
  //
  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);
  Lcr.Fields.DLAB = 1;
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
  //
  // Update Baud Rate
  //
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_BAUD_HIGH, (UINT8)(RShiftU64 (ComputedDivisor & 0xFF00, 8)));
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_BAUD_LOW, (UINT8)(ComputedDivisor & 0xFF));
  //
  // Close Divisor Latch
  //
  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);
  Lcr.Fields.DLAB = 0;
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
}

/**
  Returns current BaudRate

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     BaudRate         Baud Rate
**/
UINT64
SerialIoUartGetBaudRate (
  IN UINT8   UartNumber
  )
{
  UART_ACCESS_MODE      AccessMode;
  UINT64                BaseAddress;
  SERIAL_IO_UART_CLOCK  Clock;
  SERIAL_IO_UART_LCR    Lcr;
  UINT64                Divisor;
  UINT32                ClockRate;
  UINT16                ClockOffset;

  Divisor     = 1;
  ClockRate   = 1843200;
  ClockOffset = R_SERIAL_IO_MEM_PPR_CLK;;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return 0;
  }

  if (AccessMode == AccessMode8bit) {
    ClockOffset = ClockOffset / 4;
  }
  //
  // Open Divisor Latch
  //
  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);
  Lcr.Fields.DLAB = 1;
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
  //
  // Read BAUD_HIGH and BUAD_LOW
  //
  Divisor = ((SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_BAUD_HIGH) << 8)
               | ((SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_BAUD_LOW) & 0xFF)));
  //
  // Close Divisor Latch
  //
  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);
  Lcr.Fields.DLAB = 0;
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);

  if (Divisor == 0) {
    return 0;
  }

  if (Divisor > 1) {
    return ClockRate / (Divisor << 4);
  }

  Clock.Data = MmioRead32 ((UINTN) BaseAddress + ClockOffset);
  ClockRate = SOURCE_CLOCK;

  // BaudRate = (SourceClock * M)/(N * 16);
  return DivU64x32 (MultU64x32 (ClockRate, Clock.Fields.M), Clock.Fields.N << 4);
}

/**
  Sets Stop Bits

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  StopBits         Stop Bits

**/
VOID
SerialIoUartSetStopBits (
  IN UINT8               UartNumber,
  IN EFI_STOP_BITS_TYPE  StopBits
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }

  if (StopBits > TwoStopBits) {
    return;
  }
  if (StopBits == DefaultStopBits) {
    StopBits = (EFI_STOP_BITS_TYPE) PcdGet8 (PcdUartDefaultStopBits);
  }

  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);
  switch (StopBits) {
    default:
    case OneStopBit:
      Lcr.Fields.STOP = 0;
      break;
    case OneFiveStopBits:
    case TwoStopBits:
      Lcr.Fields.STOP = 1;
      break;
  }
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
}

/**
  Returns Stop Bits

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     StopBits         Default/One/OneFive/Two
**/
EFI_STOP_BITS_TYPE
SerialIoUartGetStopBits (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return DefaultStopBits;
  }

  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);

  if (Lcr.Fields.STOP == 1) {
    if (Lcr.Fields.DLS == 0) { // DLS = 5 bits
      return OneFiveStopBits;
    }
    return TwoStopBits;
  }

  return OneStopBit;
}

/**
  Sets Data Bits

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  DataBits         Data Bits 5/6/7/8

**/
VOID
SerialIoUartSetDataBits (
  IN UINT8               UartNumber,
  IN UINT8               DataBits
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }

  if (DataBits == 0) {
    DataBits = PcdGet8 (PcdUartDefaultDataBits);
  }

  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);

  if ((DataBits < 5) || (DataBits > 8)) {
    return;
  }
  // Map 5..8 to 0..3
  Lcr.Fields.DLS = (UINT8) (DataBits - (UINT8) 5);
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
}

/**
  Returns Data Bits

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     DataBits         5/6/7/8
**/
UINT8
SerialIoUartGetDataBits (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return 0;
  }
  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);

  return (Lcr.Fields.DLS + (UINT8) 5);
}

/**
  Sets Parity

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  Parity           Parity
**/
VOID
SerialIoUartSetParity (
  IN UINT8               UartNumber,
  IN EFI_PARITY_TYPE     Parity
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }

  if (Parity == DefaultParity) {
    Parity = (EFI_PARITY_TYPE) PcdGet8 (PcdUartDefaultParity);
  }
  if (Parity > OddParity) { // Not supported
    return;
  }

  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);

  switch (Parity) {
    default:
    case NoParity:
      Lcr.Fields.PEN = 0;
      Lcr.Fields.EPS = 0;
      break;
    case EvenParity:
      Lcr.Fields.PEN = 1;
      Lcr.Fields.EPS = 0;
      break;
    case OddParity:
      Lcr.Fields.PEN = 1;
      Lcr.Fields.EPS = 1;
      break;
  }

  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR, Lcr.Data);
}

/**
  Returns Parity

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     Parity           Even/Odd/None
**/
EFI_PARITY_TYPE
SerialIoUartGetParity (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_LCR  Lcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return DefaultParity;
  }

  Lcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_LCR);

  if ((Lcr.Fields.PEN == 1) && (Lcr.Fields.EPS == 1)) {
    return OddParity;
  } else if ((Lcr.Fields.PEN == 1) && (Lcr.Fields.EPS == 0)) {
    return EvenParity;
  }
  return NoParity; // PEN =0/EPS = 0
}

/**
  Enables Fifo

  @param[in]  UartNumber       Selects Serial IO UART device

**/
VOID
SerialIoUartFifoEnable (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE     AccessMode;
  UINT64               BaseAddress;
  SERIAL_IO_UART_FCR   Fcr;
  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }

  Fcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_FCR);
  Fcr.Fields.FIFOE = 1;
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_FCR, Fcr.Data);
}

/**
  Returns FIFOE state

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     TRUE             Fifo Enabled
  @retval     FALSE            Fifo Disabled
**/
BOOLEAN
SerialIoUartIsFifoEnabled (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_FCR  Fcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return FALSE;
  }

  Fcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_FCR);
  return (BOOLEAN) Fcr.Fields.FIFOE;
}

/**
  Enables/Disables Auto Flow Control

  @param[in]  UartNumber       Selects Serial IO UART device
  @param[in]  AutoFlow         TRUE - Enable, FALSE - Disable

**/
VOID
SerialIoUartSetAutoFlow (
  IN UINT8               UartNumber,
  IN BOOLEAN             AutoFlow
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_MCR  Mcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return;
  }

  Mcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_MCR);
  Mcr.Fields.RTS  = 1;
  Mcr.Fields.AFCE = (AutoFlow ? 1 : 0);
  SerialIoUartWriteRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_MCR, Mcr.Data);
}

/**
  Returns Auto Flow Control state

  @param[in]  UartNumber       Selects Serial IO UART device

  @retval     TRUE             AutoFlow Enabled
  @retval     FALSE            AutoFlow Disabled
**/
BOOLEAN
SerialIoUartGetAutoFlow (
  IN UINT8               UartNumber
  )
{
  UART_ACCESS_MODE    AccessMode;
  UINT64              BaseAddress;
  SERIAL_IO_UART_MCR  Mcr;

  if (!SerialIoUartEnable (UartNumber, &BaseAddress, &AccessMode)) {
    return FALSE;
  }

  Mcr.Data = SerialIoUartReadRegister (AccessMode, BaseAddress, R_PCH_SERIAL_IO_8BIT_UART_MCR);
  return (BOOLEAN) Mcr.Fields.AFCE;
}
