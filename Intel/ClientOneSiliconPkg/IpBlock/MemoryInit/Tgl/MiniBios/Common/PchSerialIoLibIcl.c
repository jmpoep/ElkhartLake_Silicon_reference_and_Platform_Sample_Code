/** @file
  PCH Serial IO Lib implementation IceLake specific.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include "MrcOemPlatform.h"
#include "PchAccess.h"
#include "PchSerialIoLib.h"
#include "PchSerialIoUartLib.h"
#include "PchPcrLib.h"
#include "PchInfoLib.h"
#include "PsfLib.h"
#include "PchSerialIoLibInternal.h"

// #include <Private/Library/GpioPrivateLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 mIclAcpiHid[PCH_MAX_SERIALIO_CONTROLLERS][SERIALIO_HID_LENGTH] =
{
  "INT34B2",
  "INT34B3",
  "INT34B4",
  "INT34B5",
  "INT34B6",
  "INT34B7",
  "INT34B0",
  "INT34B1",
  "INT34BC",
  "INT34B8",
  "INT34B9",
  "INT34BA"
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mIclPchLpSerialIoId [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C0_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C1_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C2_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C3_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C4_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_I2C5_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_SPI0_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_SPI1_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_SPI2_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_UART0_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_UART1_DEVICE_ID,
  V_ICL_PCH_LP_SERIAL_IO_CFG_UART2_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mIclPchNSerialIoId [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C0_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C1_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C2_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C3_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C4_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_I2C5_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_SPI0_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_SPI1_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_SPI2_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_UART0_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_UART1_DEVICE_ID,
  V_ICL_PCH_N_SERIAL_IO_CFG_UART2_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mIclPchHSerialIoId [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  V_ICL_PCH_H_SERIAL_IO_CFG_I2C0_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_I2C1_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_I2C2_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_I2C3_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_SPI0_DEVICE_ID,
                                         0,
                                         0,
  V_ICL_PCH_H_SERIAL_IO_CFG_SPI1_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_SPI2_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_UART0_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_UART1_DEVICE_ID,
  V_ICL_PCH_H_SERIAL_IO_CFG_UART2_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchLpPchHSerialIoBdf [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI2,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2}
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchNSerialIoBdf [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI2,  PCI_FUNCTION_NUMBER_PCH_N_SERIAL_IO_SPI2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2}
};

/**
  Returns index of the last i2c controller

  @param[in] Number                     Number of SerialIo controller

  @retval                               Index of I2C controller
**/
PCH_SERIAL_IO_CONTROLLER
GetMaxI2cNumber (
  VOID
  )
{
  if (IsPchH ()) {
    return PchSerialIoIndexI2C3;
  } else {
    return PchSerialIoIndexI2C5;
  }
}

/**
  Checks if Device with given PciDeviceId is one of SerialIo controllers
  If yes, its number is returned through Number parameter, otherwise Number is not updated

  @param[in]  PciDevId                  Device ID
  @param[out] Number                    Number of SerialIo controller

  @retval TRUE                          Yes it is a SerialIo controller
  @retval FALSE                         No it isn't a SerialIo controller
**/
BOOLEAN
IsSerialIoPciDevId (
  IN  UINT16                    PciDevId,
  OUT PCH_SERIAL_IO_CONTROLLER  *Number
  )
{
  PCH_SERIAL_IO_CONTROLLER Controller;

  for (Controller = 0; Controller < GetPchMaxSerialIoControllersNum (); Controller++) {
    if ((IsPchLp () && (PciDevId == mIclPchLpSerialIoId[Controller])) ||
        (IsPchN () && (PciDevId == mIclPchNSerialIoId[Controller])) ||
        (IsPchH () && (PciDevId == mIclPchHSerialIoId[Controller])))
    {
      *Number = Controller;
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Finds PCI Device Number of SerialIo devices.

  @param[in] SerialIoNumber             Serial IO device

  @retval                               SerialIo device number
**/
UINT8
GetSerialIoDeviceNumber (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoNumber
  )
{
  if (IsPchN ()) {
    return mPchNSerialIoBdf[SerialIoNumber].DevNum;
  }
  return mPchLpPchHSerialIoBdf[SerialIoNumber].DevNum;
}

/**
  Finds PCI Function Number of SerialIo devices.

  @param[in] SerialIoNumber             Serial IO device

  @retval                               SerialIo funciton number
**/
UINT8
GetSerialIoFunctionNumber (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoNumber
  )
{
  if (IsPchN ()) {
    return mPchNSerialIoBdf[SerialIoNumber].FuncNum;
  }
  return mPchLpPchHSerialIoBdf[SerialIoNumber].FuncNum;
}

/**
  Returns string with AcpiHid assigned to selected SerialIo controller

  @param[in] Number                     Number of SerialIo controller

  @retval                               pointer to 8-byte string
**/
CHAR8*
GetSerialIoAcpiHid (
  IN PCH_SERIAL_IO_CONTROLLER Number
  )
{
  return mIclAcpiHid[Number];
}
