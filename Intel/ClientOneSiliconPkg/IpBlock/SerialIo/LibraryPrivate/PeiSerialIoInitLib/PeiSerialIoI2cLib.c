/** @file
  Initializes Serial IO I2C Controllers.

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
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <Library/PchSbiAccessLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Register/SerialIoI2cRegs.h>
#include <Register/PchPcrRegs.h>
#include <Ppi/SiPolicy.h>
#include "PeiSerialIoInitPrivateLib.h"

/**
  Configure Sda Hold

  @param[in] Base              I2C MMIO BAR0

  @todo move to policy, replace with AndThenOr32
**/
VOID
STATIC
SerialIoI2cSetSdaHold (
  IN UINT64                    MmioBase
  )
{
  MmioOr32 ((UINTN) MmioBase + R_SERIAL_IO_I2C_MEM_SDA_HOLD, V_SERIAL_IO_I2C_MEM_SDA_HOLD_VALUE);
}

/**
  Configures GPIO for each Serial IO I2C Controller

  @param[in] I2cNumber         I2C Number
  @param[in] PadTermination    I2C Pad Termination

**/
VOID
STATIC
SerialIoI2cGpioConfiguration (
  IN UINT8                 I2cNumber,
  IN UINT8                 PadTermination
  )
{
  UINT32           SdaPinMux;
  UINT32           SclPinMux;
  GPIO_CONFIG      GpioConfig;
  GPIO_NATIVE_PAD  GpioNativePad;

  SdaPinMux = 0;
  SclPinMux = 0;

  switch (PadTermination) {
    case GpioTermDefault:
    case GpioTermNone:
    case GpioTermWpu1K:
    case GpioTermWpu5K:
    case GpioTermWpu20K:
      break;
    default:
      DEBUG ((DEBUG_ERROR, "Gpio Pad Termination must be set as Default, None, None with 1v8 tolerance, 1k, 2k, 5k or 20k WPU\n"));
      ASSERT (FALSE);
  }

  ZeroMem(&GpioConfig, sizeof(GPIO_CONFIG));
  GpioConfig.ElectricalConfig = PadTermination;

  GpioNativePad = GpioGetNativePadByFunctionAndPinMux (GPIO_FUNCTION_SERIAL_IO_I2C_SCL (I2cNumber), SclPinMux);
  GpioConfig.PadMode = GPIO_NATIVE_GET_PAD_MODE (GpioNativePad);
  GpioSetPadConfig (GpioNativePad, &GpioConfig);
  GpioSetInputInversion (GpioNativePad, 0);

  GpioNativePad = GpioGetNativePadByFunctionAndPinMux (GPIO_FUNCTION_SERIAL_IO_I2C_SDA (I2cNumber), SdaPinMux);
  GpioConfig.PadMode = GPIO_NATIVE_GET_PAD_MODE (GpioNativePad);
  GpioSetPadConfig (GpioNativePad, &GpioConfig);
  GpioSetInputInversion (GpioNativePad, 0);
}

/**
  Configures Serial IO Controller

  @param[in] I2cNumber         I2C Number
  @param[in] I2cDeviceConfig   SerialIo I2C Config
  @param[in] PsfDisable        Applies only for SerialIoI2cDisabled devices.
                               TRUE  - Device will be disabled in PSF, and will no longer enumerate on PCI.
                               FALSE - PSF configuration is left unmodified.
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoI2cConfiguration (
  IN UINT8                      I2cNumber,
  IN SERIAL_IO_I2C_CONFIG       *I2cDeviceConfig,
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
  if (I2cNumber >= PCH_MAX_SERIALIO_I2C_CONTROLLERS) {
    return;
  }

  //
  // Override previous I2C configuration
  //
  SerialIoPciPsfEnable (GetSerialIoI2cConfigControlOffset (I2cNumber), PsfSerialIoI2cPort (I2cNumber));

  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoI2cDeviceNumber (I2cNumber),
                 GetSerialIoI2cFunctionNumber (I2cNumber),
                 0
                 );
  if (PciSegmentRead32 (PciCfgBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    return;
  }
  SerialIoEnablePowerGating (PciCfgBase, PchMasterPowerGating);

  switch (I2cDeviceConfig->Mode) {
    case SerialIoI2cDisabled:
      SerialIoSetD3 (PciCfgBase);
      if (PsfDisable) {
        PsfDisableDevice (PsfSerialIoI2cPort (I2cNumber));
      }
      return;
    case SerialIoI2cHidden:
      SerialIoSetFixedMmio (PciCfgBase,
                            GetSerialIoI2cFixedMmioAddress (I2cNumber),
                            GetSerialIoI2cFixedPciCfgAddress (I2cNumber),
                            GetSerialIoI2cConfigControlOffset (I2cNumber),
                            PsfSerialIoI2cPort (I2cNumber)
                            );
      PciCfgBase = GetSerialIoI2cFixedPciCfgAddress (I2cNumber);
      Hidden     = TRUE;
      break;
    case SerialIoI2cPci:
      SerialIoPciSave (PciCfgBase, &PciState);
      SerialIoPciEnable (GetSerialIoI2cConfigControlOffset (I2cNumber), PsfSerialIoI2cPort (I2cNumber));
      TempBar = TRUE;
      break;
    default:
      return;
  }

  if (SerialIoMmioEnable (PciCfgBase, TempBar, Hidden, &Base)) {
    SerialIoI2cSetSdaHold (Base);
    if (I2cDeviceConfig->Mode == SerialIoI2cPci) {
      if (PciState.PciCfgBar0 == 0x0) {
        SerialIoSetD3 (PciCfgBase);
        SerialIoMmioDisable (PciCfgBase, TempBar);
      } else {
        SerialIoPciRestore (PciCfgBase, &PciState);
      }
    }
  }

  SerialIoI2cGpioConfiguration (I2cNumber, I2cDeviceConfig->PadTermination);
}

/**
  Configures Serial IO I2c Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoI2cInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8               I2cNumber;
  UINT8               InterruptPin;
  UINT8               Irq;
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SerialIoI2cInit() Start\n"));

  for (I2cNumber = 0; I2cNumber < GetPchMaxSerialIoI2cControllersNum (); I2cNumber++) {
    if ((SerialIoConfig->I2cDeviceConfig[I2cNumber].Mode == SerialIoI2cDisabled) &&
        (GetSerialIoI2cFunctionNumber (I2cNumber) == 0x0)) {
      continue;
    }
    if (SerialIoConfig->I2cDeviceConfig[I2cNumber].Mode != SerialIoI2cDisabled) {
      ItssGetDevIntConfig (SiPolicy, GetSerialIoI2cDeviceNumber (I2cNumber), GetSerialIoI2cFunctionNumber (I2cNumber), &InterruptPin, &Irq);
      SerialIoInterruptSet (GetSerialIoI2cConfigControlOffset (I2cNumber), InterruptPin, Irq);
    }
    SerialIoI2cConfiguration (I2cNumber, &SerialIoConfig->I2cDeviceConfig[I2cNumber], TRUE, (BOOLEAN) PchGeneralConfig->PchMasterPowerGating);
  }

  DEBUG ((DEBUG_INFO, "SerialIoI2cInit() End\n"));
}

/**
  Check if given Serial IO I2C controller is supported by silicon

  @param[in] I2cNumber                  Serial IO I2C number

  @retval                               TRUE if SerialIo I2C controller is not supported
                                        FALSE if SerialIo I2C controller is supported
**/
BOOLEAN
STATIC
IsSerialIoI2cUnsupportedDevice (
  IN UINT8    I2cNumber
  )
{
  if (IsPchH ()) {
    if ((I2cNumber == 4) || (I2cNumber == 5)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Configures Serial IO I2c Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoI2cFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8    I2cNumber;
  BOOLEAN  PsfDisable;
  UINT8    InterruptPin;
  UINT8    Irq;

  for (I2cNumber = 0; I2cNumber < GetPchMaxSerialIoI2cControllersNum (); I2cNumber++) {
    PsfDisable = TRUE;
    if ((SerialIoConfig->I2cDeviceConfig[I2cNumber].Mode == SerialIoI2cDisabled) &&
        (GetSerialIoI2cFunctionNumber (I2cNumber) == 0x0)) {
      //
      // If I2C device is not supported from silicon, always disable it from PCI space.
      //
      if (IsSerialIoI2cUnsupportedDevice (I2cNumber)) {
        SerialIoI2cConfiguration (I2cNumber, &SerialIoConfig->I2cDeviceConfig[I2cNumber], TRUE, TRUE);
        continue;
      }
      if (SerialIoHigherFunctionsEnabled (GetSerialIoI2cDeviceNumber (I2cNumber))) {
        SerialIoBar1Disable (GetSerialIoI2cConfigControlOffset (I2cNumber), PsfSerialIoI2cPort (I2cNumber));
        ItssGetDevIntConfig (SiPolicy, GetSerialIoI2cDeviceNumber (I2cNumber), GetSerialIoI2cFunctionNumber (I2cNumber), &InterruptPin, &Irq);
        SerialIoInterruptSet (GetSerialIoI2cConfigControlOffset (I2cNumber), InterruptPin, Irq);
        PsfDisable = FALSE;
      }
      SerialIoI2cConfiguration (I2cNumber, &SerialIoConfig->I2cDeviceConfig[I2cNumber], PsfDisable, TRUE);
    }
  }
}

/**
  Performs Early disable for Serial Io I2C Controller

  @param[in] I2cNumber     Serial IO I2C number

**/
VOID
SerialIoI2cEarlyDisable (
  IN UINT8 I2cNumber
  )
{
  UINT32 Data32;
  UINT8  Response;

  Data32 = B_SERIAL_IO_CFG_D0I3MAXDEVPG_PGE | B_SERIAL_IO_CFG_D0I3MAXDEVPG_I3E | B_SERIAL_IO_CFG_D0I3MAXDEVPG_PMCRE;

  PchSbiExecutionEx (
    PID_SERIALIO,
    R_SERIAL_IO_CFG_D0I3MAXDEVPG,
    PciConfigWrite,
    FALSE,
    0xF,
    0,
    ((GetSerialIoI2cDeviceNumber (I2cNumber) << 3) | GetSerialIoI2cFunctionNumber (I2cNumber)),
    &Data32,
    &Response
    );

  Data32 = B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST;
  PchSbiExecutionEx (
    PID_SERIALIO,
    R_SERIAL_IO_CFG_PME_CTRL_STS,
    PciConfigWrite,
    FALSE,
    0xF,
    0,
    ((GetSerialIoI2cDeviceNumber (I2cNumber) << 3) | GetSerialIoI2cFunctionNumber (I2cNumber)),
    &Data32,
    &Response
    );

  //
  // perform a read to avoid ordering and noncoherency problems
  //
  PchSbiExecutionEx (
    PID_SERIALIO,
    R_SERIAL_IO_CFG_PME_CTRL_STS,
    PciConfigRead,
    FALSE,
    0xF,
    0,
    ((GetSerialIoI2cDeviceNumber (I2cNumber) << 3) | GetSerialIoI2cFunctionNumber (I2cNumber)),
    &Data32,
    &Response
    );
}
