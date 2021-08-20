/** @file
  SEC Serial Port initialization library functions with no library constructor/destructor

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
#include <Library/BaseLib.h>
#include <Library/GetFsptApiParameter.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/PchCycleDecodingLib.h>
#include "SecSerialPortInitLib.h"
#include <FspEas.h>
#include <FsptUpd.h>

#define MAX_BAUD_RATE     115200

//
// TCO register I/O map
//
#define R_TCO_IO_TCO1_CNT          0x08
#define B_TCO_IO_TCO1_CNT_TMR_HLT  BIT11

//
// UART register offsets and bitfields
//
#define RXBUF_OFFSET      0x00
#define TXBUF_OFFSET      0x00
#define BAUD_LOW_OFFSET   0x00
#define BAUD_HIGH_OFFSET  0x01
#define IER_OFFSET        0x01
#define LCR_SHADOW_OFFSET 0x01
#define FCR_SHADOW_OFFSET 0x02
#define IR_CONTROL_OFFSET 0x02
#define FCR_OFFSET        0x02
#define EIR_OFFSET        0x02
#define BSR_OFFSET        0x03
#define LCR_OFFSET        0x03
#define MCR_OFFSET        0x04
#define LSR_OFFSET        0x05
#define MSR_OFFSET        0x06

//
// ---------------------------------------------
// UART Register Bit Defines
// ---------------------------------------------
//
#define FCR_FIFOE    BIT0
#define FCR_FIFO64   BIT5
#define LSR_TXRDY    0x20
#define LSR_RXDA     0x01
#define DLAB         BIT7
#define MCR_RTS      BIT1
#define MSR_CTS      BIT4
#define MSR_DSR      BIT5

/**
  This interface gets FspInfoHeader pointer

  @return   FSP binary base address.

**/
UINT32
EFIAPI
AsmGetFspInfoHeader (
  VOID
  );

/**
  Read one byte from a Serial Port Register.

  @param[in] Offset             The offset to read.

  @retval                       The value read.

**/
UINT8
SecSerialPortReadRegister (
  UINTN  Offset
  )
{
  return IoRead8 ((UINTN) PcdGet64 (PcdFspSerialRegisterBase) + Offset);
}

/**
  Write one byte to a Serial Port Register.

  @param[in] Offset             The offset to write.
  @param[in] Value              The value to write.

  @retval                       The value written.

**/
UINT8
SecSerialPortWriteRegister (
  UINTN  Offset,
  UINT8  Value
  )
{
  return IoWrite8 ((UINTN) PcdGet64 (PcdFspSerialRegisterBase) + Offset, Value);
}

/**
  Initialize Serial Port.

  The Baud Rate Divisor registers are programmed and the LCR
  is used to configure the communications format. Hard coded
  UART config comes from globals in DebugSerialPlatform lib.

  @retval RETURN_SUCCESS        The serial device was initialized.

**/
RETURN_STATUS
EFIAPI
SecUartInitialize (
  VOID
  )
{
  UINTN          Divisor;
  UINTN          TempDivisor;
  BOOLEAN        Initialized;

  //
  // Calculate divisor for baud generator
  //
  Divisor = MAX_BAUD_RATE / PcdGet32 (PcdFspSerialBaudRate);

  //
  // See if the serial port is already initialized
  //
  Initialized = TRUE;
  if ((SecSerialPortReadRegister (FCR_OFFSET) & (FCR_FIFOE | FCR_FIFO64)) !=
      (PcdGet8 (PcdFspSerialFifoControl)      & (FCR_FIFOE | FCR_FIFO64))) {
    Initialized = FALSE;
  }
  if ((SecSerialPortReadRegister (LCR_OFFSET) & 0x3F) != (PcdGet8 (PcdFspSerialLineControl) & 0x3F)) {
    Initialized = FALSE;
  }
  SecSerialPortWriteRegister (LCR_OFFSET, (UINT8)(SecSerialPortReadRegister (LCR_OFFSET) | DLAB));
  TempDivisor = (UINTN)SecSerialPortReadRegister (BAUD_HIGH_OFFSET);
  TempDivisor = TempDivisor << 8;
  TempDivisor |= (UINTN)SecSerialPortReadRegister (BAUD_LOW_OFFSET);
  SecSerialPortWriteRegister (LCR_OFFSET, (UINT8)(SecSerialPortReadRegister (LCR_OFFSET) & ~DLAB));
  if (TempDivisor != Divisor) {
    Initialized = FALSE;
  }
  if (Initialized) {
    return RETURN_SUCCESS;
  }

  //
  // Set communications format
  //
  SecSerialPortWriteRegister (LCR_OFFSET, DLAB);

  //
  // Configure baud rate
  //
  SecSerialPortWriteRegister (BAUD_HIGH_OFFSET, (UINT8) (Divisor >> 8));
  SecSerialPortWriteRegister (BAUD_LOW_OFFSET, (UINT8) (Divisor & 0xff));

  //
  // Switch back to bank 0
  //
  SecSerialPortWriteRegister (LCR_OFFSET, (UINT8)(PcdGet8 (PcdFspSerialLineControl) & 0x3F));

  //
  // Enable and reset FIFOs
  // Strip reserved bits from PcdSerialFifoControl
  //
  SecSerialPortWriteRegister (FCR_OFFSET, (UINT8)(PcdGet8 (PcdFspSerialFifoControl) & 0x27));

  //
  // Put Modem Control Register(MCR) into its reset state of 0x00.
  //
  SecSerialPortWriteRegister (MCR_OFFSET, 0x00);

  return RETURN_SUCCESS;
}

/**
  Write data to serial device.

  If the buffer is NULL, then return 0;
  if NumberOfBytes is zero, then return 0.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Write data failed.
  @retval >0               Actual number of bytes writed to serial device.

**/
UINTN
EFIAPI
SecUartDebugOut (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
  )
{
  UINTN Result;
  UINTN FifoSize;
  UINTN Index;

  if (NULL == Buffer) {
    return 0;
  }

  //
  // Compute the maximum size of the Tx FIFO
  //
  FifoSize = 1;
  if ((PcdGet8 (PcdFspSerialFifoControl) & FCR_FIFOE) != 0) {
    if ((PcdGet8 (PcdFspSerialFifoControl) & FCR_FIFO64) == 0) {
      FifoSize = 16;
    } else {
      FifoSize = 64;
    }
  }

  Result = NumberOfBytes;

  while (NumberOfBytes != 0) {
    //
    // Wait for the serial port to be ready, to make sure both the transmit FIFO
    // and shift register empty.
    //
    while ((SecSerialPortReadRegister (LSR_OFFSET) & LSR_TXRDY) == 0);

    //
    // Fill then entire Tx FIFO
    //
    for (Index = 0; Index < FifoSize && NumberOfBytes != 0; Index++, NumberOfBytes--, Buffer++) {
      if (PcdGetBool (PcdFspSerialUseHardwareFlowControl)) {
        if (PcdGetBool (PcdFspSerialDetectCable)) {
          //
          // Wait for both DSR and CTS to be set
          //   DSR is set if a cable is connected.
          //   CTS is set if it is ok to transmit data
          //
          //   DSR  CTS  Description                               Action
          //   ===  ===  ========================================  ========
          //    0    0   No cable connected.                       Wait
          //    0    1   No cable connected.                       Wait
          //    1    0   Cable connected, but not clear to send.   Wait
          //    1    1   Cable connected, and clear to send.       Transmit
          //
          while ((SecSerialPortReadRegister (MSR_OFFSET) & (MSR_DSR | MSR_CTS)) != (MSR_DSR | MSR_CTS));
        } else {
          //
          // Wait for both DSR and CTS to be set OR for DSR to be clear.
          //   DSR is set if a cable is connected.
          //   CTS is set if it is ok to transmit data
          //
          //   DSR  CTS  Description                               Action
          //   ===  ===  ========================================  ========
          //    0    0   No cable connected.                       Transmit
          //    0    1   No cable connected.                       Transmit
          //    1    0   Cable connected, but not clear to send.   Wait
          //    1    1   Cable connected, and clar to send.        Transmit
          //
          while ((SecSerialPortReadRegister (MSR_OFFSET) & (MSR_DSR | MSR_CTS)) == (MSR_DSR));
        }
      }

      //
      // Write byte to the transmit buffer.
      //
      SecSerialPortWriteRegister (TXBUF_OFFSET, *Buffer);
    }
  }

  return Result;
}

/**
  Initialize Serial Port configuration, and print message once debug enabled.
**/
VOID
EFIAPI
SerialPortConfiguration (
  VOID
  )
{
  CHAR8             CarInitBuffer[32];
  UINT8             LpcUartDebugEnable;
  FSP_INFO_HEADER   *FspInfoHeader;
  FSPT_UPD          *FsptUpd;

  FsptUpd = (FSPT_UPD *) *((UINT32 *) (SecGetFsptApiParameter () + 0x4));
  if (FsptUpd->FspUpdHeader.Signature != FSPT_UPD_SIGNATURE) {
    FspInfoHeader = (FSP_INFO_HEADER *) AsmGetFspInfoHeader ();
    FsptUpd = (FSPT_UPD *) (FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
  }
  LpcUartDebugEnable = FsptUpd->FsptConfig.PcdLpcUartDebugEnable;

  if (LpcUartDebugEnable == 1) {
    //
    // Halt the TCO timer as early as possible
    //
    IoWrite16 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT, B_TCO_IO_TCO1_CNT_TMR_HLT);
    //
    // Enable I/O decoding for COM1(3F8h-3FFh), COM2(2F8h-2FFh), I/O port 2Eh/2Fh, 4Eh/4Fh, 60h/64Fh and 62h/66h.
    //
    PchLpcIoDecodeRangesSet (PcdGet16 (PcdLpcIoDecodeRange));
    PchLpcIoEnableDecodingSet (PcdGet16 (PcdLpcIoEnableDecoding));

    AsciiSPrint (CarInitBuffer, sizeof (CarInitBuffer), "FSP-T: CAR Init\n");
    //
    // Initialize LPC UART for debug message
    //
    SecUartInitialize ();
    SecUartDebugOut ((UINT8 *)CarInitBuffer, AsciiStrLen(CarInitBuffer));
  }
}
