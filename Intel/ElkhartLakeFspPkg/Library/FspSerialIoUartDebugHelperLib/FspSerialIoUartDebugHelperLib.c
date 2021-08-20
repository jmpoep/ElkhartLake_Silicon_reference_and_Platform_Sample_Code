/** @file
  Implementation of FspSerialIoUartDebugHelperLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoUartLib.h>
#include <Library/SerialIoUartDebugPropertyPcdLib.h>
#include <Library/FspCommonLib.h>
#include <Protocol/SerialIo.h>
#include <SerialIoDevices.h>
#include <FspEas.h>
#include <FspmUpd.h>

/**
  Get FSPM Config

  @param[out] Fspm        FSPM Config

  @retval TRUE if FSPM exists
  @retval FALSE unable to locate FSP
**/
BOOLEAN
STATIC
GetFspmConfig (
  OUT FSP_M_CONFIG  **Fspm
  )
{
  FSP_GLOBAL_DATA *FspData;
  FSPM_UPD        *FspmUpd;

  FspData = GetFspGlobalDataPointer ();

  if (((UINTN)FspData == 0x00 || (UINTN)FspData == 0xFFFFFFFF) ||
     (FspData->Signature != FSP_GLOBAL_DATA_SIGNATURE)) {
    return FALSE;
  } else if ((FspData->FspMode == FSP_IN_API_MODE) && (FspData->MemoryInitUpdPtr != NULL)) {
    FspmUpd = FspData->MemoryInitUpdPtr;
    *Fspm = &FspmUpd->FspmConfig;
    return TRUE;
  }
  return FALSE;
}

/**
  Returns UART attributes

  @param[in,out] Attributes          UART Attributes
**/
VOID
STATIC
FspmSerialIoUartDebugGetAttributes (
  IN OUT SERIAL_IO_UART_ATTRIBUTES  *Attributes
  )
{
  FSP_M_CONFIG    *FspmConfig;
  FspmConfig = NULL;

  if (GetFspmConfig (&FspmConfig)) {
    Attributes->BaudRate = FspmConfig->SerialIoUartDebugBaudRate;
    Attributes->Parity   = FspmConfig->SerialIoUartDebugParity;
    Attributes->DataBits = FspmConfig->SerialIoUartDebugDataBits;
    Attributes->StopBits = FspmConfig->SerialIoUartDebugStopBits;
    Attributes->AutoFlow = FspmConfig->SerialIoUartDebugAutoFlow;
  } else {
    SerialIoUartDebugPcdGetAttributes (Attributes);
  }
}

/**
  Returns Serial Io UART Controller Number used in Debug mode

  @retval  ControllerNumber   UART Controller Number
**/
UINT8
STATIC
FspmSerialIoUartDebugGetControllerNumber (
  VOID
  )
{
  FSP_M_CONFIG    *FspmConfig;
  STATIC UINT8    ControllerNumber = 0xFF;
  FspmConfig = NULL;

  if (ControllerNumber == 0xFF) {
    if (GetFspmConfig (&FspmConfig)) {
      ControllerNumber = FspmConfig->SerialIoUartDebugControllerNumber;
      return FspmConfig->SerialIoUartDebugControllerNumber;
    } else {
      return SerialIoUartDebugPcdGetControllerNumber ();
    }
  }
  return ControllerNumber;
}

/**
  Returns Serial Io UART MMIO Base Address in Debug mode

  @retval  MMIO Base Address by default in PCI Mode
**/
UINT32
STATIC
FspmSerialIoUartDebugGetPciDefaultMmioBase (
  VOID
  )
{
  FSP_M_CONFIG    *FspmConfig;
  FspmConfig = NULL;

  if (GetFspmConfig (&FspmConfig)) {
    return FspmConfig->SerialIoUartDebugMmioBase;
  } else {
    return SerialIoUartDebugPcdGetPciDefaultMmioBase ();
  }
}

/**
  Initialize SerialIo UART for debug.

**/
VOID
EFIAPI
SerialIoUartDebugInit (
  VOID
  )
{
  UINT64                    PciCfgBase;
  UINT64                    Bar0;
  SERIAL_IO_UART_ATTRIBUTES UartAttributes;
  UINT8                     UartNumber;
  EFI_STATUS                Status;

  UartNumber = FspmSerialIoUartDebugGetControllerNumber ();
  PciCfgBase = GetSerialIoUartPciCfg (UartNumber);
  Bar0       = GetSerialIoBar (PciCfgBase);
  FspmSerialIoUartDebugGetAttributes (&UartAttributes);

  //
  // Check BAR0 whether is assigned value in either Hidden or PCI Mode.
  //
  if ((Bar0 !=  0x0) && (Bar0 != 0xFFFFF000)) {
    SerialIoUartSetAttributes (
      UartNumber,
      UartAttributes.BaudRate,
      UartAttributes.Parity,
      UartAttributes.DataBits,
      UartAttributes.StopBits,
      UartAttributes.AutoFlow
      );
    return;
  }

  //
  // Assign MMIO for HS-UART used in PCI Mode.
  //
  if (!IsSerialIoUartInPciMode (UartNumber)) {
    return;
  }
  Bar0 = FspmSerialIoUartDebugGetPciDefaultMmioBase ();
  Status = SerialIoUartSetMmioInPciMode (UartNumber, Bar0);
  if (Status == EFI_UNSUPPORTED) {
    return;
  }

  //
  // UART Reset
  //
  SerialIoUartGetOutOfReset (Bar0);

  //
  // Initialize UART Attributes
  //
  SerialIoUartSetAttributes (
    UartNumber,
    UartAttributes.BaudRate,
    UartAttributes.Parity,
    UartAttributes.DataBits,
    UartAttributes.StopBits,
    UartAttributes.AutoFlow
    );
}

/**
  Write data to serial device.

  If the buffer is NULL, then return 0;
  if NumberOfBytes is zero, then return 0.

  @param[in]  Buffer           Data pointer
  @param[in]  NumberOfBytes    Number of output bytes which are cached in Buffer.

  @retval                      Actual number of bytes written to serial device.
**/
UINTN
EFIAPI
SerialIoUartDebugWrite (
  IN UINT8            *Buffer,
  IN UINTN            NumberOfBytes
  )
{
  return SerialIoUartWrite (FspmSerialIoUartDebugGetControllerNumber (), Buffer, NumberOfBytes);
}
