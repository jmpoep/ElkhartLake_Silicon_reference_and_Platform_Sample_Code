/** @file
  Initializes Serial IO Uart Controllers.

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

#include <Ppi/SiPolicy.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <Library/SerialIoUartLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Register/SerialIoUartRegs.h>
#include <Register/PchPcrRegs.h>
#include "PeiSerialIoInitPrivateLib.h"

/**
  Configures GPIO for each Serial IO UART Controller

  @param[in] UartNumber         UART Number
  @param[in] UartDeviceConfig   SerialIo UART Config

**/
VOID
STATIC
SerialIoUartGpioConfiguration (
  IN UINT8                  UartNumber,
  IN SERIAL_IO_UART_CONFIG  *UartDeviceConfig
  )
{
  GPIO_PAD GpioPad;
  GpioPad = 0;
  // RX
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_RX (UartNumber), UartDeviceConfig->PinMux.Rx);
  GpioPad = UartDeviceConfig->PinMux.Rx;
  if (GpioPad == 0) { GpioPad = GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_RX (UartNumber)); }
  GpioSetInputInversion (GpioPad, 0);
  // TX
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_TX (UartNumber), UartDeviceConfig->PinMux.Tx);
  GpioPad = UartDeviceConfig->PinMux.Tx;
  if (GpioPad == 0) { GpioPad = GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_TX (UartNumber)); }
  GpioSetInputInversion (GpioPad, 0);

  if (UartDeviceConfig->Attributes.AutoFlow) {
    // RTS
    GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_RTS (UartNumber), UartDeviceConfig->PinMux.Rts);
    GpioPad = (GPIO_PAD) UartDeviceConfig->PinMux.Rts;
    if (GpioPad == 0) { GpioPad = GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_RTS (UartNumber)); }
    GpioSetInputInversion (GpioPad, 0);
    // CTS
    GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_CTS (UartNumber), UartDeviceConfig->PinMux.Cts);
    GpioPad = UartDeviceConfig->PinMux.Cts;
    if (GpioPad == 0) { GpioPad = GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_UART_CTS (UartNumber)); }
    GpioSetInputInversion (GpioPad, 0);
  }
}

/**
  Enable 16550 8bit Mode

  @param[in] UartNumber         UART Number

**/
VOID
SerialIoUartEnable16550Mode (
  IN UINT8        UartNumber
  )
{
  PchPcrAndThenOr32 (PID_SERIALIO, R_SERIAL_IO_PCR_GPPRVRW7, MAX_UINT32, (BIT0 << UartNumber));
  SerialIoUartDummyRead (UartNumber);
}

/**
  Disable 16550 8bit Mode

  @param[in] UartNumber         UART Number

**/
VOID
SerialIoUartDisable16550Mode (
  IN UINT8        UartNumber
  )
{
  PchPcrAndThenOr32 (PID_SERIALIO, R_SERIAL_IO_PCR_GPPRVRW7, (UINT32) ~ (B_SERIAL_IO_PCR_GPPRVRW7_UART0_BYTE_ADDR_EN << UartNumber), 0x0);
  SerialIoUartDummyRead (UartNumber);
}

/**
  Configures Serial IO Controller

  @param[in] UartNumber        UART Number
  @param[in] UartDeviceConfig  SerialIo UART Config
  @param[in] PsfDisable        Applies only for SerialIoUartDisabled devices.
                               TRUE  - Device will be disabled in PSF, and will no longer enumerate on PCI.
                               FALSE - PSF configuration is left unmodified.
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoUartConfiguration (
  IN UINT8                      UartNumber,
  IN SERIAL_IO_UART_CONFIG      *UartDeviceConfig,
  IN BOOLEAN                    PsfDisable,
  IN BOOLEAN                    PchMasterPowerGating
  )
{
  SERIAL_IO_PCI_DEVICE_STATE  PciState;
  UINT64                      PciCfgBase;
  UINT64                      Base;
  BOOLEAN                     TempBar;
  BOOLEAN                     Hidden;

  PciState.PciCfgBar0 = 0x0;
  TempBar             = FALSE;
  Hidden              = FALSE;
  Base                = 0x0;

  //
  // This is to prevent from overflow of array access.
  //
  if (UartNumber >= PCH_MAX_SERIALIO_UART_CONTROLLERS) {
    return;
  }

  //
  // Override previous UART configuration
  //
  SerialIoPciPsfEnable (GetSerialIoUartConfigControlOffset (UartNumber), PsfSerialIoUartPort (UartNumber));

  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoUartDeviceNumber (UartNumber),
                 GetSerialIoUartFunctionNumber (UartNumber),
                 0
                 );
  if (PciSegmentRead32 (PciCfgBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    return;
  }
  SerialIoEnablePowerGating (PciCfgBase, PchMasterPowerGating);

  switch (UartDeviceConfig->Mode) {
    case SerialIoUartDisabled:
      SerialIoUartDisable16550Mode (UartNumber);
      SerialIoSetD3 (PciCfgBase);
      SerialIoMmioDisable (PciCfgBase, TempBar);
      if (PsfDisable) {
        PsfDisableDevice (PsfSerialIoUartPort (UartNumber));
      }
      return;
    case SerialIoUartHidden:
    case SerialIoUartCom:
      SerialIoSetFixedMmio (PciCfgBase,
                            GetSerialIoUartFixedMmioAddress (UartNumber),
                            GetSerialIoUartFixedPciCfgAddress (UartNumber),
                            GetSerialIoUartConfigControlOffset (UartNumber),
                            PsfSerialIoUartPort (UartNumber)
                            );
      PciCfgBase = GetSerialIoUartFixedPciCfgAddress (UartNumber);
      Hidden     = TRUE;
      break;
    case SerialIoUartPci:
      SerialIoPciSave (PciCfgBase, &PciState);
      SerialIoPciEnable (GetSerialIoUartConfigControlOffset (UartNumber), PsfSerialIoUartPort (UartNumber));
      TempBar = TRUE;
      //
      // Uart in Pci mode does not have any resources assigned through SEC/PEI, except tremporary MMIO BAR.
      // To enable it in that stage set PowerGating to Enabled.
      // It will assign UART fixed MMIO and leave it in D0 after initial configuration.
      //
      if (UartDeviceConfig->PowerGating == SerialIoUartPgEnabled) {
        SerialIoPciSetFixedMmio (PciCfgBase, GetSerialIoUartFixedMmioAddress (UartNumber));
        TempBar = FALSE;
      }
      break;
    default:
      return;
  }

  if (SerialIoMmioEnable (PciCfgBase, TempBar, Hidden, &Base)) {
    SerialIoUartGetOutOfReset (Base);
    SerialIoUartSetAttributes (
      UartNumber,
      UartDeviceConfig->Attributes.BaudRate,
      UartDeviceConfig->Attributes.Parity,
      UartDeviceConfig->Attributes.DataBits,
      UartDeviceConfig->Attributes.StopBits,
      UartDeviceConfig->Attributes.AutoFlow
    );
    if (UartDeviceConfig->Mode == SerialIoUartHidden ||
      UartDeviceConfig->Mode == SerialIoUartCom) {
      SerialIoUartEnable16550Mode (UartNumber);
    } else {
      SerialIoUartDisable16550Mode (UartNumber);
    }
    if ((UartDeviceConfig->Mode == SerialIoUartPci) && (UartDeviceConfig->PowerGating != SerialIoUartPgEnabled)) {
      if (PciState.PciCfgBar0 == 0x0) {
        SerialIoSetD3 (PciCfgBase);
        SerialIoMmioDisable (PciCfgBase, TempBar);
      } else {
        SerialIoPciRestore (PciCfgBase, &PciState);
      }
    }
  }
  SerialIoUartGpioConfiguration (UartNumber, UartDeviceConfig);
}

/**
  Configures Serial IO Uart Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoUartInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8               UartNumber;
  UINT8               InterruptPin;
  UINT8               Irq;
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SerialIoUartInit() Start\n"));

  for (UartNumber = 0; UartNumber < GetPchMaxSerialIoUartControllersNum (); UartNumber++) {
    if (SerialIoConfig->UartDeviceConfig[UartNumber].Mode != SerialIoUartDisabled) {
      ItssGetDevIntConfig (SiPolicy, GetSerialIoUartDeviceNumber (UartNumber), GetSerialIoUartFunctionNumber (UartNumber), &InterruptPin, &Irq);
      if (SerialIoConfig->UartDeviceConfig[UartNumber].Mode == SerialIoUartCom) {
        SerialIoAcpiInterruptSet (GetSerialIoUartConfigControlOffset (UartNumber), InterruptPin, Irq);
      }
      SerialIoInterruptSet (GetSerialIoUartConfigControlOffset (UartNumber), InterruptPin, Irq);
    }
    if (SerialIoConfig->UartDeviceConfig[UartNumber].Mode == SerialIoUartSkipInit) {
      continue;
    }
    if ((SerialIoConfig->UartDeviceConfig[UartNumber].Mode == SerialIoUartDisabled) &&
        (GetSerialIoUartFunctionNumber (UartNumber) == 0x0)) {
      continue;
    }
    SerialIoUartConfiguration (UartNumber, &SerialIoConfig->UartDeviceConfig[UartNumber], TRUE, (BOOLEAN) PchGeneralConfig->PchMasterPowerGating);
  }

  DEBUG ((DEBUG_INFO, "SerialIoUartInit() End\n"));
}

/**
  Configures Serial IO Uart Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoUartFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8    UartNumber;
  BOOLEAN  PsfDisable;
  UINT8    InterruptPin;
  UINT8    Irq;

  for (UartNumber = 0; UartNumber < GetPchMaxSerialIoUartControllersNum (); UartNumber++) {
    PsfDisable = TRUE;
    if ((SerialIoConfig->UartDeviceConfig[UartNumber].Mode == SerialIoUartDisabled) &&
        (GetSerialIoUartFunctionNumber (UartNumber) == 0x0)) {
      if (SerialIoHigherFunctionsEnabled (GetSerialIoUartDeviceNumber (UartNumber))) {
        SerialIoBar1Disable (GetSerialIoUartConfigControlOffset (UartNumber), PsfSerialIoUartPort (UartNumber));
        ItssGetDevIntConfig (SiPolicy, GetSerialIoUartDeviceNumber (UartNumber), GetSerialIoUartFunctionNumber (UartNumber), &InterruptPin, &Irq);
        SerialIoInterruptSet (GetSerialIoUartConfigControlOffset (UartNumber), InterruptPin, Irq);
        PsfDisable = FALSE;
      }
      SerialIoUartConfiguration (UartNumber, &SerialIoConfig->UartDeviceConfig[UartNumber], PsfDisable, TRUE);
    }
  }
}

