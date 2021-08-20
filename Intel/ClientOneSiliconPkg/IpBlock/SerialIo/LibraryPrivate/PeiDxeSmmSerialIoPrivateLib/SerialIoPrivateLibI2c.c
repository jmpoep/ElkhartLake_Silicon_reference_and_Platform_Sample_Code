/** @file
  Common Serial IO Private Lib implementation - I2C part
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
  Checks if I2C is Hidden, and it's Pci Config space available

  @param[in] I2cNumber     Selects Serial IO I2C device

  @retval   TRUE             I2C is in hidden mode
  @retval   FALSE            I2C is not in hidden mode
**/
BOOLEAN
IsSerialIoI2cHidden (
  IN UINT8               I2cNumber
  )
{
  if (MmioRead16 (GetSerialIoI2cFixedPciCfgAddress (I2cNumber) + PCI_DEVICE_ID_OFFSET) == GetSerialIoI2cDeviceId (I2cNumber)) {
    return TRUE;
  }
  return FALSE;
}

/**
  Configures Serial IO Controller before control is passd to the OS

  @param[in] I2cNumber         I2C Number
  @param[in] I2cDeviceConfig   SerialIo I2C Config

**/
VOID
SerialIoI2cBootHandler (
  IN UINT8                      I2cNumber,
  IN SERIAL_IO_I2C_CONFIG       *I2cDeviceConfig
  )
{
  UINT64   PciCfgBase;
  BOOLEAN  TurnOff;

  TurnOff = FALSE;

  if (I2cDeviceConfig->Mode == SerialIoI2cPci) {
    TurnOff = TRUE;
  }

  if ((I2cDeviceConfig->Mode == SerialIoI2cDisabled) && (GetSerialIoI2cFunctionNumber (I2cNumber) == 0x0)) {
    if (SerialIoHigherFunctionsEnabled (GetSerialIoI2cDeviceNumber (I2cNumber))) {
      TurnOff = TRUE;
    }
  }

  if (TurnOff) {
    PciCfgBase = GetSerialIoI2cPciCfg (I2cNumber);
    SerialIoSetD3 (PciCfgBase);
    SerialIoMmioDisable (PciCfgBase, TRUE);
  }
}

/**
  Sets Pme Control Status and Command register values required for S3 Boot Script

  @param[in]     I2cNumber         I2C Number
  @param[in]     I2cDeviceConfig   SerialIo I2C Config
  @param[in/out] S3PciCfgBase      S3 Boot Script Pci Config Base
  @param[in/out] Command           Pci Command register data to save
  @param[in/out] Pme               Pci Pme Control register data to save

**/
VOID
SerialIoI2cS3Handler (
  IN     UINT8                 I2cNumber,
  IN     SERIAL_IO_I2C_CONFIG  *I2cDeviceConfig,
  IN OUT UINT64                *S3PciCfgBase,
  IN OUT UINT32                *Command,
  IN OUT UINT32                *Pme
  )
{
  BOOLEAN  TurnOff;
  UINT64   PciCfgBase;

  *S3PciCfgBase = 0;
  TurnOff       = FALSE;

  if (I2cDeviceConfig->Mode == SerialIoI2cPci) {
    TurnOff = TRUE;
  }

  if ((I2cDeviceConfig->Mode == SerialIoI2cDisabled) && (GetSerialIoI2cFunctionNumber (I2cNumber) == 0x0)) {
    if (SerialIoHigherFunctionsEnabled (GetSerialIoI2cDeviceNumber (I2cNumber))) {
      TurnOff = TRUE;
    }
  }

  if (TurnOff) {
    *S3PciCfgBase = GetSerialIoI2cS3PciBase (I2cNumber);
    PciCfgBase    = GetSerialIoI2cPciCfg (I2cNumber);
    *Pme          = PciSegmentRead32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS);
    *Pme          = *Pme | BIT0 | BIT1;
    *Command      = PciSegmentRead32 ((UINTN) PciCfgBase + PCI_COMMAND_OFFSET);
    *Command      = *Command & (UINT32)~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);
  }
}
