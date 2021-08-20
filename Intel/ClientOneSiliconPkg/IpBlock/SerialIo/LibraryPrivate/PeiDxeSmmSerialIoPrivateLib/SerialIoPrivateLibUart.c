/** @file
  Serial IO Private Lib implementation - UART part
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <SerialIoPrivateLibInternal.h>
#include <PchLimits.h>

/**
  Checks if UART is Hidden, and it's Pci Config space available

  @param[in]      UartNumber     Selects Serial IO UART device

  @retval   TRUE             UART is in hidden mode
  @retval   FALSE            UART is not in hidden mode
**/
BOOLEAN
IsSerialIoUartHidden (
  IN UINT8               UartNumber
  )
{
  if (MmioRead16 (GetSerialIoUartFixedPciCfgAddress (UartNumber) + PCI_DEVICE_ID_OFFSET) == GetSerialIoUartDeviceId (UartNumber)) {
    return TRUE;
  }
  return FALSE;
}

/**
  Configures Serial IO Controller before control is passd to the OS

  @param[in] UartNumber         UART Number
  @param[in] UartDeviceConfig   SerialIo UART Config

**/
VOID
SerialIoUartBootHandler (
  IN UINT8                      UartNumber,
  IN SERIAL_IO_UART_CONFIG      *UartDeviceConfig
  )
{
  UINT64   PciCfgBase;
  BOOLEAN  TurnOff;

  TurnOff = FALSE;

  //
  // Even if Uart is Hidden and in D3 SerialIoUartLib is capable of setting D0 during each write/read.
  // In case it is required for Os Debug DBG2 must be set to TRUE.
  //
  if (UartDeviceConfig->Mode == SerialIoUartPci || UartDeviceConfig->Mode == SerialIoUartHidden) {
    TurnOff = TRUE;
  }

  //
  // Uart in Com mode will be placed in D3 depending on PG configuration through ACPI _PS3
  //

  if ((UartDeviceConfig->Mode == SerialIoUartDisabled) && (GetSerialIoUartFunctionNumber (UartNumber) == 0x0)) {
    if (SerialIoHigherFunctionsEnabled (GetSerialIoUartDeviceNumber (UartNumber))) {
      TurnOff = TRUE;
    }
  }

  if (UartDeviceConfig->DBG2 == TRUE) {
    TurnOff = FALSE;
  }

  if (TurnOff) {
    PciCfgBase = GetSerialIoUartPciCfg (UartNumber);
    SerialIoSetD3 (PciCfgBase);
    if ((UartDeviceConfig->Mode == SerialIoUartPci) || (UartDeviceConfig->Mode == SerialIoUartDisabled)) {
      SerialIoMmioDisable (PciCfgBase, TRUE);
    }
  }
}

/**
  Sets Pme Control Status and Command register values required for S3 Boot Script

  @param[in]     UartNumber         UART Number
  @param[in]     UartDeviceConfig   SerialIo UART Config
  @param[in/out] S3PciCfgBase       S3 Boot Script Pci Config Base
  @param[in/out] Command            Pci Command register data to save
  @param[in/out] Pme                Pci Pme Control register data to save

**/
VOID
SerialIoUartS3Handler (
  IN     UINT8                  UartNumber,
  IN     SERIAL_IO_UART_CONFIG  *UartDeviceConfig,
  IN OUT UINT64                 *S3PciCfgBase,
  IN OUT UINT32                 *Command,
  IN OUT UINT32                 *Pme
  )
{
  BOOLEAN  TurnOff;
  UINT64   PciCfgBase;

  *S3PciCfgBase = 0;
  TurnOff       = FALSE;

  if (UartDeviceConfig->Mode == SerialIoUartPci) {
    TurnOff = TRUE;
  }

  if ((UartDeviceConfig->Mode == SerialIoUartDisabled) && (GetSerialIoUartFunctionNumber (UartNumber) == 0x0)) {
    if (SerialIoHigherFunctionsEnabled (GetSerialIoUartDeviceNumber (UartNumber))) {
      TurnOff = TRUE;
    }
  }

  if (TurnOff) {
    *S3PciCfgBase = GetSerialIoUartS3PciBase (UartNumber);
    PciCfgBase    = GetSerialIoUartPciCfg (UartNumber);
    *Pme          = PciSegmentRead32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS);
    *Pme          = *Pme | BIT0 | BIT1;
    *Command      = PciSegmentRead32 ((UINTN) PciCfgBase + PCI_COMMAND_OFFSET);
    *Command      = *Command & (UINT32)~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);
  }
}