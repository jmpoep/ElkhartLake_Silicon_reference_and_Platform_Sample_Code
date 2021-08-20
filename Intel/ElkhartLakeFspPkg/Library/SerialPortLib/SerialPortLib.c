/** @file
  Serial I/O Port library functions with no library constructor/destructor

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#include <Library/PlatformHookLib.h>
#include <Library/DebugLib.h>
#include <Library/FspSerialIoUartDebugHelperLib.h>
#include <Library/FspCommonLib.h>
#include <FspmUpd.h>
#include <SerialIoDevices.h>

//---------------------------------------------
// UART Register Offsets
//---------------------------------------------
#define BAUD_LOW_OFFSET         0x00
#define BAUD_HIGH_OFFSET        0x01
#define IER_OFFSET              0x01
#define LCR_SHADOW_OFFSET       0x01
#define FCR_SHADOW_OFFSET       0x02
#define IR_CONTROL_OFFSET       0x02
#define FCR_OFFSET              0x02
#define EIR_OFFSET              0x02
#define BSR_OFFSET              0x03
#define LCR_OFFSET              0x03
#define MCR_OFFSET              0x04
#define LSR_OFFSET              0x05
#define MSR_OFFSET              0x06

//---------------------------------------------
// UART Register Bit Defines
//---------------------------------------------
#define LSR_TXRDY               0x20
#define LSR_RXDA                0x01
#define DLAB                    0x01

#define COM1_BASE 0x3f8
#define COM2_BASE 0x2f8

#define MAX_BAUD_RATE 115200

//---------------------------------------------
// Serial Debug Interfaces
//---------------------------------------------
#define STATUS_CODE_USE_RAM        BIT0
#define STATUS_CODE_USE_ISA_SERIAL BIT1
#define STATUS_CODE_USE_USB        BIT2
#define STATUS_CODE_USE_USB3       BIT3
#define STATUS_CODE_USE_SERIALIO   BIT4
#define STATUS_CODE_USE_TRACEHUB   BIT5

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN    mIsaSerialUartBaseInited = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16     mIsaSerialUartBase = 0xffff;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN    mDebugInterfaceFlagsInited = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8      mDebugInterfaceFlags = 0xff;

UINT16
GetComBase (
  VOID
  )
{
  FSPM_UPD        *FspmUpd;
  UINT16          IsaSerialUartBase;
  FSP_GLOBAL_DATA *FspData;

  if (mIsaSerialUartBaseInited == TRUE) {
    return mIsaSerialUartBase;
  }

  FspData = GetFspGlobalDataPointer ();
  if (((UINTN)FspData == 0x00 || (UINTN)FspData == 0xFFFFFFFF) ||
     (FspData->Signature != FSP_GLOBAL_DATA_SIGNATURE)) {
    mIsaSerialUartBase = (UINT16) PcdGet64 (PcdSerialRegisterBase);
    mIsaSerialUartBaseInited = TRUE;
    return mIsaSerialUartBase;

  } else if ((FspData->FspMode == FSP_IN_API_MODE) && (FspData->MemoryInitUpdPtr != NULL)) {
    FspmUpd = FspData->MemoryInitUpdPtr;
    IsaSerialUartBase = ((FspmUpd->FspmConfig.PcdIsaSerialUartBase == 0) ? COM1_BASE : COM2_BASE);
    mIsaSerialUartBase = IsaSerialUartBase;
    mIsaSerialUartBaseInited = TRUE;
    return IsaSerialUartBase;

  } else {
    return (UINT16) PcdGet64 (PcdSerialRegisterBase);
  }
}

/**
  Get Debug Interface Flags through FSPM UPD.
**/
UINT8
EFIAPI
GetDebugInterfaceFlags (
  VOID
  )
{
  FSPM_UPD        *FspmUpd;
  UINT8           DebugInterfaceFlags;
  FSP_GLOBAL_DATA *FspData;

  if (mDebugInterfaceFlagsInited == TRUE) {
    return mDebugInterfaceFlags;
  }

  FspData = GetFspGlobalDataPointer ();
  if (((UINTN)FspData == 0x00 || (UINTN)FspData == 0xFFFFFFFF) ||
     (FspData->Signature != FSP_GLOBAL_DATA_SIGNATURE)) {
    mDebugInterfaceFlags = PcdGet8 (PcdStatusCodeFlags);
    mDebugInterfaceFlagsInited = TRUE;
    return mDebugInterfaceFlags;

  } else if ((FspData->FspMode == FSP_IN_API_MODE) && (FspData->MemoryInitUpdPtr != NULL)) {
    FspmUpd = FspData->MemoryInitUpdPtr;
    DebugInterfaceFlags = FspmUpd->FspmConfig.PcdDebugInterfaceFlags;
    mDebugInterfaceFlags = DebugInterfaceFlags;
    mDebugInterfaceFlagsInited = TRUE;
    return DebugInterfaceFlags;

  } else {
    return PcdGet8 (PcdStatusCodeFlags);
  }
}

UINT8
SerialPortReadRegister (
  UINTN Offset
  )
{
  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) {
    return IoRead8 ((GetComBase () + Offset));
  }
  return 0;
}

UINT8
SerialPortWriteRegister (
  UINTN Offset,
  UINT8 Value
  )
{
  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) {
    return IoWrite8 ((GetComBase () + Offset), Value);
  }
  return 0;
}

/**
  Initialize Legacy UART Serial Port

  The Baud Rate Divisor registers are programmed and the LCR
  is used to configure the communications format. Hard coded
  UART config comes from globals in DebugSerialPlatform lib.

**/
RETURN_STATUS
EFIAPI
UartInitialize (
  VOID
  )
{
  UINTN           Divisor;
  UINT8           OutputData;
  FSP_GLOBAL_DATA *FspData;
  UINT16          ComBase;
  FSPM_UPD        *FspmUpd;
  UINT32          BaudRate;

  FspData = GetFspGlobalDataPointer ();
  if (((UINTN)FspData == 0x00 || (UINTN)FspData == 0xFFFFFFFF) ||
     (FspData->Signature != FSP_GLOBAL_DATA_SIGNATURE)) {
    ComBase = (UINT16) PcdGet64 (PcdSerialRegisterBase);
    Divisor = MAX_BAUD_RATE / PcdGet32 (PcdSerialBaudRate);

  } else if ((FspData->FspMode == FSP_IN_API_MODE) && (FspData->MemoryInitUpdPtr != NULL)) {
    //
    // Check the initialization of FSP Global Data Pointer before using it
    // Constructor will call this first time before FSP Global Data pointer is initialized
    // skip initialization that time. It will be reinitialized by FSP, once FSP Gloabl Data pointer
    // is ready
    //
    FspmUpd = FspData->MemoryInitUpdPtr;
    if ((FspmUpd == NULL) || !(FspmUpd->FspmConfig.PcdDebugInterfaceFlags & STATUS_CODE_USE_ISA_SERIAL)) {
      return EFI_SUCCESS;
    }

    ComBase = GetComBase ();
    //
    // Calculate divisor for baud generator
    // PcdGet32 (PcdSerialBoudRate);

    //
    // Calculate divisor for baud generator
    //
    BaudRate = MAX_BAUD_RATE;
    if (FspmUpd != NULL) {
      switch (FspmUpd->FspmConfig.PcdSerialDebugBaudRate) {
      case 3:
        BaudRate = 9600;
        break;
      case 4:
        BaudRate = 19200;
        break;
      case 6:
        BaudRate = 57600;
        break;
      default:
        BaudRate = 115200;
      }
    }
    Divisor = MAX_BAUD_RATE / BaudRate;
  } else {
    ComBase = (UINT16) PcdGet64 (PcdSerialRegisterBase);
    Divisor = MAX_BAUD_RATE / PcdGet32 (PcdSerialBaudRate);
  }

  //
  // Set communications format
  //
  OutputData = (UINT8) (0x83);
  IoWrite8 ((UINTN) (ComBase + LCR_OFFSET), OutputData);

  //
  // Configure baud rate
  //
  IoWrite8 ((UINTN) (ComBase + BAUD_HIGH_OFFSET), (UINT8) (Divisor >> 8));
  IoWrite8 ((UINTN) (ComBase + BAUD_LOW_OFFSET),  (UINT8) (Divisor & 0xff));

  //
  // Switch back to bank 0
  //
  OutputData = (UINT8) (0x03);
  IoWrite8 ((UINTN) (ComBase + LCR_OFFSET), OutputData);
  IoWrite8 ((UINTN) (ComBase + 2), 0xc1);

  return RETURN_SUCCESS;
}

/**
  Common function to initialize UART Serial device.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
  //
  // EC/LPC UART
  //
  UartInitialize ();

  //
  // Serial Io Uart
  //
  SerialIoUartDebugInit ();

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
UartDebugOut (
  IN UINT8 *Buffer,
  IN UINTN NumberOfBytes
  )
{
  UINTN Result;
  UINT8 Data;
  UINT16 ComBase;

  if (NULL == Buffer) {
    return 0;
  }

  ComBase = GetComBase();
  Result = NumberOfBytes;

  while (NumberOfBytes--) {
    //
    // Wait for the serail port to be ready.
    //
    do {
      Data = IoRead8 ((UINT16) ComBase + LSR_OFFSET);
    } while ((Data & LSR_TXRDY) == 0);
    IoWrite8 ((UINT16) ComBase, *Buffer++);
  }

  return Result;
}

/**
  Common function to write data to UART Serial device.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8 *Buffer,
  IN UINTN NumberOfBytes
  )
{
  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) {
    UartDebugOut (Buffer, NumberOfBytes);
  }

  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_SERIALIO) {
    SerialIoUartDebugWrite (Buffer, NumberOfBytes);
  }

  return RETURN_SUCCESS;
}

/**
  Read data from serial device and save the datas in buffer.

  If the buffer is NULL, then return 0;
  if NumberOfBytes is zero, then return 0.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Read data failed.
  @retval >0               Actual number of bytes raed to serial device.

**/
UINTN
EFIAPI
UartDebugIn (
  OUT UINT8 *Buffer,
  IN UINTN  NumberOfBytes
  )
{
  UINTN Result;
  UINT8 Data;
  UINT16 ComBase;

  if (NULL == Buffer) {
    return 0;
  }

  ComBase = GetComBase();
  Result = NumberOfBytes;

  while (NumberOfBytes--) {
    //
    // Wait for the serial port to be ready.
    //
    do {
      Data = IoRead8 ((UINT16) ComBase + LSR_OFFSET);
    } while ((Data & LSR_RXDA) == 0);

    *Buffer++ = IoRead8 ((UINT16) ComBase);
  }

  return Result;
}

/**
  Common function to Read data from UART serial device and save the datas in buffer.

  @param  Buffer           Point of data buffer which need to be writed.
  @param  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval 0                Read data failed.
  @retval >0               Actual number of bytes raed to serial device.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8 *Buffer,
  IN UINTN  NumberOfBytes
  )
{
  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) {
    return UartDebugIn (Buffer, NumberOfBytes);
  }
  return 0;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls a serial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
UartDebugPoll (
  VOID
  )
{
  //
  // Read the serial port status
  //
  if ((SerialPortReadRegister (LSR_OFFSET) & LSR_RXDA) != 0) {
    return TRUE;
  }

  return FALSE;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls a serial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  BOOLEAN    Status;

  Status = FALSE;
  if (GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) {
    Status |= UartDebugPoll ();
  }

  return Status;
}
