/** @file
  This file contains ICL specific GPIO information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#include "GpioLib.h"
#include "GpioNativeLib.h"
#include "GpioPrivateLib.h"
#include "PchInfoLib.h"
#include "GpioPinsIclLp.h"
#include "GpioPinsIclN.h"

#include "GpioNativePrivateLibInternal.h"

//
// I2C controller pins
// I2C[controller number][pin: SDA/SCL]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpI2cGpio [][PCH_SERIAL_IO_PINS_PER_I2C_CONTROLLER]=
{
  {{GPIO_ICL_LP_GPP_C16, GpioPadModeNative1}, {GPIO_ICL_LP_GPP_C17, GpioPadModeNative1}},
  {{GPIO_ICL_LP_GPP_C18, GpioPadModeNative1}, {GPIO_ICL_LP_GPP_C19, GpioPadModeNative1}},
  {{GPIO_ICL_LP_GPP_H4,  GpioPadModeNative1}, {GPIO_ICL_LP_GPP_H5 , GpioPadModeNative1}},
  {{GPIO_ICL_LP_GPP_H6,  GpioPadModeNative1}, {GPIO_ICL_LP_GPP_H7 , GpioPadModeNative1}},
  {{GPIO_ICL_LP_GPP_H8,  GpioPadModeNative1}, {GPIO_ICL_LP_GPP_H9 , GpioPadModeNative1}},
  {{GPIO_ICL_LP_GPP_B9,  GpioPadModeNative1}, {GPIO_ICL_LP_GPP_B10, GpioPadModeNative1}}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNI2cGpio [][PCH_SERIAL_IO_PINS_PER_I2C_CONTROLLER]=
{
  {{GPIO_ICL_N_GPP_C16, GpioPadModeNative1}, {GPIO_ICL_N_GPP_C17, GpioPadModeNative1}},
  {{GPIO_ICL_N_GPP_C18, GpioPadModeNative1}, {GPIO_ICL_N_GPP_C19, GpioPadModeNative1}},
  {{GPIO_ICL_N_GPP_H4,  GpioPadModeNative1}, {GPIO_ICL_N_GPP_H5 , GpioPadModeNative1}},
  {{GPIO_ICL_N_GPP_H6,  GpioPadModeNative1}, {GPIO_ICL_N_GPP_H7 , GpioPadModeNative1}},
  {{GPIO_ICL_N_GPP_H8,  GpioPadModeNative1}, {GPIO_ICL_N_GPP_H9 , GpioPadModeNative1}},
  {{GPIO_ICL_N_GPP_D22, GpioPadModeNative1}, {GPIO_ICL_N_GPP_D23, GpioPadModeNative1}}
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION  mPchHI2cGpio [][PCH_SERIAL_IO_PINS_PER_I2C_CONTROLLER];
// @todo - update for ICL-PCH-H


/**
  This function provides SerialIo I2C controller pins

  @param[in]  SerialIoI2cControllerNumber    I2C controller

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetSerialIoI2cPins (
  IN  UINT32                      SerialIoI2cControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (SerialIoI2cControllerNumber < ARRAY_SIZE (mPchLpI2cGpio)) {
      *NativePinsTable = mPchLpI2cGpio[SerialIoI2cControllerNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (SerialIoI2cControllerNumber < ARRAY_SIZE (mPchNI2cGpio)) {
      *NativePinsTable = mPchNI2cGpio[SerialIoI2cControllerNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}
//
// UART controller pins
// UART[controller number][pin: RXD/TXD/RTSB/CTSB]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpUartGpio [][PCH_SERIAL_IO_PINS_PER_UART_CONTROLLER]=
{
  { // UART0
    {GPIO_ICL_LP_GPP_C8,  GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C9,  GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C10, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C11, GpioPadModeNative1}
  },
  { // UART1
    {GPIO_ICL_LP_GPP_C12, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C13, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C14, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C15, GpioPadModeNative1}
  },
  { // UART2
    {GPIO_ICL_LP_GPP_C20, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C21, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C22, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_C23, GpioPadModeNative1}
  },
  { // UART0 (2nd pin set)
    {GPIO_ICL_LP_GPP_F1, GpioPadModeNative2},
    {GPIO_ICL_LP_GPP_F2, GpioPadModeNative2},
    {GPIO_ICL_LP_GPP_F0, GpioPadModeNative2},
    {GPIO_ICL_LP_GPP_F3, GpioPadModeNative2}
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNUartGpio [][PCH_SERIAL_IO_PINS_PER_UART_CONTROLLER]=
{
  { // UART0
    {GPIO_ICL_N_GPP_C8,  GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C9,  GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C10, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C11, GpioPadModeNative1}
  },
  { // UART1
    {GPIO_ICL_N_GPP_C12, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C13, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C14, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C15, GpioPadModeNative1}
  },
  { // UART2
    {GPIO_ICL_N_GPP_C20, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C21, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C22, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_C23, GpioPadModeNative1}
  },
  { // UART0 (2nd pin set)
    {GPIO_ICL_N_GPP_E21, GpioPadModeNative2},
    {GPIO_ICL_N_GPP_E22, GpioPadModeNative2},
    {GPIO_ICL_N_GPP_E20, GpioPadModeNative2},
    {GPIO_ICL_N_GPP_E23, GpioPadModeNative2}
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHUartGpio [][PCH_SERIAL_IO_PINS_PER_UART_CONTROLLER];
// @todo - update for ICL-PCH-H

/**
  This function provides SerialIo UART controller pins

  @param[in]  SerialIoUartControllerNumber   UART controller
  @param[in]  HardwareFlowControl            Hardware Flow control
  @param[in]  PinMuxing                      UART controller pin muxing
                                             CNL: 0:defaut pins, 1:pins muxed with CNV_BRI/RGI
  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetSerialIoUartPins (
  IN  UINT32                      SerialIoUartControllerNumber,
  IN  BOOLEAN                     HardwareFlowControl,
  IN  UINT32                      PinMuxing,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  )
{
  UINTN                    UartGpioIndex;

  UartGpioIndex = SerialIoUartControllerNumber;

  if ((SerialIoUartControllerNumber == 0) && (PinMuxing == 1)) {
    // Last record is for UART0 second pin set
    if (IsPchLp ()) {
      UartGpioIndex = ARRAY_SIZE (mPchLpUartGpio) - 1;
    } else if (IsPchN ()) {
      UartGpioIndex = ARRAY_SIZE (mPchNUartGpio) - 1;
    }
  }

  if (HardwareFlowControl) {
    *NoOfNativePins = PCH_SERIAL_IO_PINS_PER_UART_CONTROLLER;
  } else {
    *NoOfNativePins = PCH_SERIAL_IO_PINS_PER_UART_CONTROLLER_NO_FLOW_CTRL;
  }

  if (IsPchLp ()) {
    if (UartGpioIndex < ARRAY_SIZE (mPchLpUartGpio)) {
      *NativePinsTable = mPchLpUartGpio[UartGpioIndex];
      return;
    }
  } else if (IsPchN ()) {
    if (UartGpioIndex < ARRAY_SIZE (mPchNUartGpio)) {
      *NativePinsTable = mPchNUartGpio[UartGpioIndex];
      return;
    }
  }

  *NativePinsTable = NULL;
  *NoOfNativePins = 0;
  ASSERT (FALSE);
}

//
// SPI controller pins
// SPI[controller number][pin: CSB/CLK/MISO/MOSI]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSpiGpio [][PCH_SERIAL_IO_PINS_PER_SPI_CONTROLLER]=
{
  { // SPI0
    {GPIO_ICL_LP_GPP_B15, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B16, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B17, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B18, GpioPadModeNative1}
  },
  { // SPI1
    {GPIO_ICL_LP_GPP_B19, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B20, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B21, GpioPadModeNative1},
    {GPIO_ICL_LP_GPP_B22, GpioPadModeNative1}
  },
  { // SPI2
    {GPIO_ICL_LP_GPP_D9,  GpioPadModeNative3},
    {GPIO_ICL_LP_GPP_D10, GpioPadModeNative3},
    {GPIO_ICL_LP_GPP_D11, GpioPadModeNative3},
    {GPIO_ICL_LP_GPP_D12, GpioPadModeNative3}
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSpiGpio [][PCH_SERIAL_IO_PINS_PER_SPI_CONTROLLER]=
{
  { // SPI0
    {GPIO_ICL_N_GPP_B15, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B16, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B17, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B18, GpioPadModeNative1}
  },
  { // SPI1
    {GPIO_ICL_N_GPP_B19, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B20, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B21, GpioPadModeNative1},
    {GPIO_ICL_N_GPP_B22, GpioPadModeNative1}
  },
  { // SPI2
    {GPIO_ICL_N_GPP_D8,  GpioPadModeNative2},
    {GPIO_ICL_N_GPP_D9,  GpioPadModeNative2},
    {GPIO_ICL_N_GPP_D10, GpioPadModeNative2},
    {GPIO_ICL_N_GPP_D11, GpioPadModeNative2}
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSpiGpio [][PCH_SERIAL_IO_PINS_PER_SPI_CONTROLLER];
// @todo - update for ICL-PCH-H

/**
  This function provides SerialIo SPI controller pins

  @param[in]  SerialIoSpiControllerNumber   SPI controller

  @param[out] NativePinsTable               Table with pins
**/
VOID
GpioGetSerialIoSpiPins (
  IN  UINT32                      SerialIoSpiControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (SerialIoSpiControllerNumber < ARRAY_SIZE (mPchLpSpiGpio)) {
      *NativePinsTable = mPchLpSpiGpio[SerialIoSpiControllerNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (SerialIoSpiControllerNumber < ARRAY_SIZE (mPchNSpiGpio)) {
      *NativePinsTable = mPchNSpiGpio[SerialIoSpiControllerNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// ISH GP pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpIshGPGpio[] =
{
  {GPIO_ICL_LP_GPP_D0,  GpioPadModeNative1},// ISH_GP_0
  {GPIO_ICL_LP_GPP_D1,  GpioPadModeNative1},// ISH_GP_1
  {GPIO_ICL_LP_GPP_D2,  GpioPadModeNative1},// ISH_GP_2
  {GPIO_ICL_LP_GPP_D3,  GpioPadModeNative1},// ISH_GP_3
  {GPIO_ICL_LP_GPP_D17, GpioPadModeNative1},// ISH_GP_4
  {GPIO_ICL_LP_GPP_D18, GpioPadModeNative1},// ISH_GP_5
  {GPIO_ICL_LP_GPP_E15, GpioPadModeNative1},// ISH_GP_6
  {GPIO_ICL_LP_GPP_E16, GpioPadModeNative1} // ISH_GP_7
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNIshGPGpio[] =
{
  {GPIO_ICL_N_GPP_E0,  GpioPadModeNative1},// ISH_GP_0
  {GPIO_ICL_N_GPP_E1,  GpioPadModeNative1},// ISH_GP_1
  {GPIO_ICL_N_GPP_E3,  GpioPadModeNative1},// ISH_GP_2
  {GPIO_ICL_N_GPP_E7,  GpioPadModeNative1},// ISH_GP_3
  {GPIO_ICL_N_GPP_E8,  GpioPadModeNative1},// ISH_GP_4
  {GPIO_ICL_N_GPP_E9,  GpioPadModeNative1},// ISH_GP_5
  {GPIO_ICL_N_GPP_E10, GpioPadModeNative1},// ISH_GP_6
  {GPIO_ICL_N_GPP_E11, GpioPadModeNative1} // ISH_GP_7
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHIshGPGpio[];
// @todo - update for ICL-PCH-H

/**
  This function provides ISH GP pin data

  @param[in]  IshGpPinNumber        ISH GP pin number
  @param[out] NativePin             ISH GP pin
**/
VOID
GpioGetIshGpPin (
  IN  UINT32                      IshGpPinNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    *NativePin
  )
{
  if (IsPchLp ()) {
    if (IshGpPinNumber < ARRAY_SIZE (mPchLpIshGPGpio)) {
      *NativePin = mPchLpIshGPGpio[IshGpPinNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (IshGpPinNumber < ARRAY_SIZE (mPchNIshGPGpio)) {
      *NativePin = mPchNIshGPGpio[IshGpPinNumber];
      return;
    }
  }

  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// ISH UART controller pins
// ISH UART[controller number][pin: RXD/TXD/RTSB/CTSB]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpIshUartGpio[][PCH_ISH_PINS_PER_UART_CONTROLLER] =
{
  { // UART0
    {GPIO_ICL_LP_GPP_D13, GpioPadModeNative1},// ISH_UART0_RXD
    {GPIO_ICL_LP_GPP_D14, GpioPadModeNative1},// ISH_UART0_TXD
    {GPIO_ICL_LP_GPP_D15, GpioPadModeNative1},// ISH_UART0_RTS
    {GPIO_ICL_LP_GPP_D16, GpioPadModeNative1} // ISH_UART0_CTS
  },
  { // UART1
    {GPIO_ICL_LP_GPP_C12, GpioPadModeNative2},// ISH_UART1_RXD
    {GPIO_ICL_LP_GPP_C13, GpioPadModeNative2},// ISH_UART1_TXD
    {GPIO_ICL_LP_GPP_C14, GpioPadModeNative2},// ISH_UART1_RTSB
    {GPIO_ICL_LP_GPP_C15, GpioPadModeNative2} // ISH_UART1_CTSB
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNIshUartGpio[][PCH_ISH_PINS_PER_UART_CONTROLLER] =
{
  { //UART0
    {GPIO_ICL_N_GPP_D12, GpioPadModeNative1},// ISH_UART0_RXD
    {GPIO_ICL_N_GPP_D13, GpioPadModeNative1},// ISH_UART0_TXD
    {GPIO_ICL_N_GPP_D14, GpioPadModeNative1},// ISH_UART0_RTS
    {GPIO_ICL_N_GPP_D15, GpioPadModeNative1} // ISH_UART0_CTS
  },
  { //UART1
    {GPIO_ICL_N_GPP_C12, GpioPadModeNative2},// ISH_UART1_RXD
    {GPIO_ICL_N_GPP_C13, GpioPadModeNative2},// ISH_UART1_TXD
    {GPIO_ICL_N_GPP_C14, GpioPadModeNative2},// ISH_UART1_RTSB
    {GPIO_ICL_N_GPP_C15, GpioPadModeNative2} // ISH_UART1_CTSB
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHIshUartGpio[][PCH_ISH_PINS_PER_UART_CONTROLLER];
// @todo - update for ICL-PCH-H

/**
  This function provides ISH UART controller pins

  @param[in]  IshUartControllerNumber   ISH UART controller

  @param[out] NativePinsTable           Table with pins
**/
VOID
GpioGetIshUartPins (
  IN  UINT32                      IshUartControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (IshUartControllerNumber < ARRAY_SIZE (mPchLpIshUartGpio)) {
      *NativePinsTable = mPchLpIshUartGpio[IshUartControllerNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (IshUartControllerNumber < ARRAY_SIZE (mPchNIshUartGpio)) {
      *NativePinsTable = mPchNIshUartGpio[IshUartControllerNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// ISH I2C controller pins
// ISH I2C[controller number][pin: SDA/SCL]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpIshI2cGpio[][PCH_ISH_PINS_PER_I2C_CONTROLLER] =
{
  { // I2C0
    {GPIO_ICL_LP_GPP_B5,  GpioPadModeNative1},// ISH_I2C0_SDA
    {GPIO_ICL_LP_GPP_B6,  GpioPadModeNative1} // ISH_I2C0_SCL
  },
  { // I2C1
    {GPIO_ICL_LP_GPP_B7,  GpioPadModeNative1},// ISH_I2C1_SDA
    {GPIO_ICL_LP_GPP_B8,  GpioPadModeNative1} // ISH_I2C1_SCL
  },
  { // I2C2
    {GPIO_ICL_LP_GPP_B9,  GpioPadModeNative2},// ISH_I2C2_SDA
    {GPIO_ICL_LP_GPP_B10, GpioPadModeNative2} // ISH_I2C2_SCL
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNIshI2cGpio[][PCH_ISH_PINS_PER_I2C_CONTROLLER] =
{
  { //I2C0
    {GPIO_ICL_N_GPP_D4,  GpioPadModeNative1},// ISH_I2C0_SDA
    {GPIO_ICL_N_GPP_D5,  GpioPadModeNative1} // ISH_I2C0_SCL
  },
  { //I2C1
    {GPIO_ICL_N_GPP_D6,  GpioPadModeNative1},// ISH_I2C1_SDA
    {GPIO_ICL_N_GPP_D7,  GpioPadModeNative1} // ISH_I2C1_SCL
  },
  { //I2C2
    {GPIO_ICL_N_GPP_D22, GpioPadModeNative2},// ISH_I2C2_SDA
    {GPIO_ICL_N_GPP_D23, GpioPadModeNative2} // ISH_I2C2_SCL
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHIshI2cGpio[][PCH_ISH_PINS_PER_I2C_CONTROLLER];
// @todo - update for ICL-PCH-H

/**
  This function provides ISH I2C controller pins

  @param[in]  IshI2cControllerNumber   ISH I2C controller

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetIshI2cPins (
  IN  UINT32                      IshI2cControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (IshI2cControllerNumber < ARRAY_SIZE (mPchLpIshI2cGpio)) {
      *NativePinsTable = mPchLpIshI2cGpio[IshI2cControllerNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (IshI2cControllerNumber < ARRAY_SIZE (mPchNIshI2cGpio)) {
      *NativePinsTable = mPchNIshI2cGpio[IshI2cControllerNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// ISH SPI controller pins
// ISH SPI[pin: CSB/CLK/MISO/MOSI]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpIshSpiGpio[PCH_ISH_PINS_PER_SPI_CONTROLLER] =
{
  {GPIO_ICL_LP_GPP_D9,  GpioPadModeNative1},// ISH_SPI_CSB
  {GPIO_ICL_LP_GPP_D10, GpioPadModeNative1},// ISH_SPI_CLK
  {GPIO_ICL_LP_GPP_D11, GpioPadModeNative1},// ISH_SPI_MISO
  {GPIO_ICL_LP_GPP_D12, GpioPadModeNative1} // ISH_SPI_MOSI
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNIshSpiGpio[PCH_ISH_PINS_PER_SPI_CONTROLLER] =
{
  {GPIO_ICL_N_GPP_D8,  GpioPadModeNative1},// ISH_SPI_CSB
  {GPIO_ICL_N_GPP_D9,  GpioPadModeNative1},// ISH_SPI_CLK
  {GPIO_ICL_N_GPP_D10, GpioPadModeNative1},// ISH_SPI_MISO
  {GPIO_ICL_N_GPP_D11, GpioPadModeNative1} // ISH_SPI_MOSI
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHIshSpiGpio[PCH_ISH_PINS_PER_SPI_CONTROLLER];
// @todo - update for ICL-PCH-H

/**
  This function provides ISH SPI controller pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetIshSpiPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpIshSpiGpio;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNIshSpiGpio;
  } else {
    *NativePinsTable = NULL;
    ASSERT (FALSE);
  }
}
#ifndef MRC_MINIBIOS_BUILD
//
// GPIO pins for SD controller
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpScsSdCardGpio[PCH_SCS_SD_CARD_PINS] =
{
  {GPIO_ICL_LP_GPP_H1,  GpioPadModeNative1},// SD_PWR_EN_B
  {GPIO_ICL_LP_GPP_G0,  GpioPadModeNative1},// SD_CMD
  {GPIO_ICL_LP_GPP_G1,  GpioPadModeNative1},// SD_DATA_0
  {GPIO_ICL_LP_GPP_G2,  GpioPadModeNative1},// SD_DATA_1
  {GPIO_ICL_LP_GPP_G3,  GpioPadModeNative1},// SD_DATA_2
  {GPIO_ICL_LP_GPP_G4,  GpioPadModeNative1},// SD_DATA_3
  {GPIO_ICL_LP_GPP_G5,  GpioPadModeNative1},// SD_CDB
  {GPIO_ICL_LP_GPP_G6,  GpioPadModeNative1},// SD_CLK
  {GPIO_ICL_LP_GPP_G7,  GpioPadModeNative1} // SD_WP
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNScsSdCardGpio[PCH_SCS_SD_CARD_PINS] =
{
  {GPIO_ICL_N_GPP_H1,  GpioPadModeNative1},// SD_PWR_EN_B
  {GPIO_ICL_N_GPP_G0,  GpioPadModeNative1},// SD_CMD
  {GPIO_ICL_N_GPP_G1,  GpioPadModeNative1},// SD_DATA_0
  {GPIO_ICL_N_GPP_G2,  GpioPadModeNative1},// SD_DATA_1
  {GPIO_ICL_N_GPP_G3,  GpioPadModeNative1},// SD_DATA_2
  {GPIO_ICL_N_GPP_G4,  GpioPadModeNative1},// SD_DATA_3
  {GPIO_ICL_N_GPP_G5,  GpioPadModeNative1},// SD_CDB
  {GPIO_ICL_N_GPP_G6,  GpioPadModeNative1},// SD_CLK
  {GPIO_ICL_N_GPP_G7,  GpioPadModeNative1} // SD_WP
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHScsSdCardGpio[PCH_SCS_SD_CARD_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides SCS SD CARD controller pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetScsSdCardPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpScsSdCardGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchLpScsSdCardGpio);
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNScsSdCardGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchNScsSdCardGpio);
  } else {
    ASSERT (FALSE);
    return;
  }
}

/**
  This function provides SCS SD CARD detect pin

  @retval GpioPin             SD CARD Detect pin
**/
GPIO_PAD
GpioGetScsSdCardDetectPin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_VGPIO39;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO39;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

//
// GPIO pins for eMMC controller
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpScsEmmcGpio[PCH_SCS_EMMC_PINS] =
{
  {GPIO_ICL_LP_GPP_F7,  GpioPadModeNative1},// EMMC_CMD
  {GPIO_ICL_LP_GPP_F8,  GpioPadModeNative1},// EMMC_DATA_0
  {GPIO_ICL_LP_GPP_F9,  GpioPadModeNative1},// EMMC_DATA_1
  {GPIO_ICL_LP_GPP_F10, GpioPadModeNative1},// EMMC_DATA_2
  {GPIO_ICL_LP_GPP_F11, GpioPadModeNative1},// EMMC_DATA_3
  {GPIO_ICL_LP_GPP_F12, GpioPadModeNative1},// EMMC_DATA_4
  {GPIO_ICL_LP_GPP_F13, GpioPadModeNative1},// EMMC_DATA_5
  {GPIO_ICL_LP_GPP_F14, GpioPadModeNative1},// EMMC_DATA_6
  {GPIO_ICL_LP_GPP_F15, GpioPadModeNative1},// EMMC_DATA_7
  {GPIO_ICL_LP_GPP_F16, GpioPadModeNative1},// EMMC_RCLK
  {GPIO_ICL_LP_GPP_F17, GpioPadModeNative1},// EMMC_CLK
  {GPIO_ICL_LP_GPP_F18, GpioPadModeNative1} // EMMC_RESETB
};

/**
  This function provides SCS eMMC controller pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetScsEmmcPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpScsEmmcGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchLpScsEmmcGpio);
  } else {
    ASSERT (FALSE);
    return;
  }
}

//
// GPIO pins for HD Audio Link [pin: BCLK/RSTB/SYNC/SDO/SDIx]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaLinkGpio[PCH_GPIO_HDA_LINK_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_R0, GpioPadModeNative1},// HDA_BCLK
  {GPIO_ICL_LP_GPP_R4, GpioPadModeNative1},// HDA_RSTB
  {GPIO_ICL_LP_GPP_R1, GpioPadModeNative1},// HDA_SYNC
  {GPIO_ICL_LP_GPP_R2, GpioPadModeNative1},// HDA_SDO
  {GPIO_ICL_LP_GPP_R3, GpioPadModeNative1},// HDA_SDI_0
  {GPIO_ICL_LP_GPP_R5, GpioPadModeNative1} // HDA_SDI_1
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaLinkGpio[PCH_GPIO_HDA_LINK_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_R0, GpioPadModeNative1},//HDA_BCLK
  {GPIO_ICL_N_GPP_R4, GpioPadModeNative1},//HDA_RSTB
  {GPIO_ICL_N_GPP_R1, GpioPadModeNative1},//HDA_SYNC
  {GPIO_ICL_N_GPP_R2, GpioPadModeNative1},//HDA_SDO
  {GPIO_ICL_N_GPP_R3, GpioPadModeNative1},//HDA_SDI_0
  {GPIO_ICL_N_GPP_R5, GpioPadModeNative1} //HDA_SDI_1
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaLinkGpio[PCH_GPIO_HDA_LINK_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides HD Audio Link pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetHdAudioLinkPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpHdaLinkGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchLpHdaLinkGpio);
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNHdaLinkGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchNHdaLinkGpio);
  } else {
    *NativePinsTable = mPchHHdaLinkGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchHHdaLinkGpio);
  }
}

//
// GPIO pins for HD Audio DMIC [DMIC number][pin: CLK/DATA]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaDmicGpio[][PCH_GPIO_HDA_DMIC_NUMBER_OF_PINS] =
{
  { // DMIC0
    {GPIO_ICL_LP_GPP_S6, GpioPadModeNative2},// DMIC_CLK_0
    {GPIO_ICL_LP_GPP_S7, GpioPadModeNative2} // DMIC_DATA_0
  },
  { // DMIC1
    {GPIO_ICL_LP_GPP_S4, GpioPadModeNative2},// DMIC_CLK_1
    {GPIO_ICL_LP_GPP_S5, GpioPadModeNative2} // DMIC_DATA_1
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaDmicGpio[][PCH_GPIO_HDA_DMIC_NUMBER_OF_PINS] =
{
  { //DMIC0
    {GPIO_ICL_N_GPP_S6, GpioPadModeNative2},//DMIC_CLK_0
    {GPIO_ICL_N_GPP_S7, GpioPadModeNative2} //DMIC_DATA_0
  },
  { //DMIC1
    {GPIO_ICL_N_GPP_S4, GpioPadModeNative2},//DMIC_CLK_1
    {GPIO_ICL_N_GPP_S5, GpioPadModeNative2} //DMIC_DATA_1
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaDmicGpio[][PCH_GPIO_HDA_DMIC_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides DMIC interface pins

  @param[in]  DmicNumber               DMIC interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaDmicPins (
  IN  UINT32                      DmicNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (DmicNumber < ARRAY_SIZE (mPchLpHdaDmicGpio)) {
      *NativePinsTable = mPchLpHdaDmicGpio[DmicNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (DmicNumber < ARRAY_SIZE (mPchNHdaDmicGpio)) {
      *NativePinsTable = mPchNHdaDmicGpio[DmicNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// GPIO pins for HD Audio SSPx/I2Sx interface [SSP number][pin: SCLK/SFRM/TXD/RXD]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { // SSP0/I2S0
    {GPIO_ICL_LP_GPP_R0,  GpioPadModeNative2},// I2S0_SCLK
    {GPIO_ICL_LP_GPP_R1,  GpioPadModeNative2},// I2S0_SFRM
    {GPIO_ICL_LP_GPP_R2,  GpioPadModeNative2},// I2S0_TXD
    {GPIO_ICL_LP_GPP_R3,  GpioPadModeNative2} // I2S0_RXD
  },
  { // SSP1/I2S1
    {GPIO_ICL_LP_GPP_A23, GpioPadModeNative1},// I2S1_SCLK
    {GPIO_ICL_LP_GPP_R5,  GpioPadModeNative2},// I2S1_SFRM
    {GPIO_ICL_LP_GPP_R6,  GpioPadModeNative2},// I2S1_TXD
    {GPIO_ICL_LP_GPP_R7,  GpioPadModeNative2} // I2S1_RXD
  },
  { // SSP2/I2S2
    {GPIO_ICL_LP_GPP_A7,  GpioPadModeNative1},// I2S2_SCLK
    {GPIO_ICL_LP_GPP_A8,  GpioPadModeNative1},// I2S2_SFRM
    {GPIO_ICL_LP_GPP_A9,  GpioPadModeNative1},// I2S2_TXD
    {GPIO_ICL_LP_GPP_A10, GpioPadModeNative1} // I2S2_RXD
  },
  { // SSP3/I2S3
    {GPIO_ICL_LP_GPP_A11, GpioPadModeNative3},// I2S3_SCLK
    {GPIO_ICL_LP_GPP_A12, GpioPadModeNative3},// I2S3_SFRM
    {GPIO_ICL_LP_GPP_A13, GpioPadModeNative3},// I2S3_TXD
    {GPIO_ICL_LP_GPP_A14, GpioPadModeNative3} // I2S3_RXD
  },
  { // SSP4/I2S4
    {GPIO_ICL_LP_GPP_A15, GpioPadModeNative3},// I2S4_SCLK
    {GPIO_ICL_LP_GPP_A16, GpioPadModeNative3},// I2S4_SFRM
    {GPIO_ICL_LP_GPP_A17, GpioPadModeNative3},// I2S4_TXD
    {GPIO_ICL_LP_GPP_A18, GpioPadModeNative3} // I2S4_RXD
  },
  { // SSP5/I2S5
    {GPIO_ICL_LP_GPP_A19, GpioPadModeNative3},// I2S5_SCLK
    {GPIO_ICL_LP_GPP_A20, GpioPadModeNative3},// I2S5_SFRM
    {GPIO_ICL_LP_GPP_A21, GpioPadModeNative3},// I2S5_TXD
    {GPIO_ICL_LP_GPP_A22, GpioPadModeNative3} // I2S5_RXD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { //SSP0/I2S0
    {GPIO_ICL_N_GPP_R0,  GpioPadModeNative2},//I2S0_SCLK
    {GPIO_ICL_N_GPP_R1,  GpioPadModeNative2},//I2S0_SFRM
    {GPIO_ICL_N_GPP_R2,  GpioPadModeNative2},//I2S0_TXD
    {GPIO_ICL_N_GPP_R3,  GpioPadModeNative2} //I2S0_RXD
  },
  { //SSP1/I2S1
    {GPIO_ICL_N_GPP_H15, GpioPadModeNative1},//I2S1_SCLK
    {GPIO_ICL_N_GPP_R6,  GpioPadModeNative1},//I2S1_SFRM
    {GPIO_ICL_N_GPP_R7,  GpioPadModeNative1},//I2S1_TXD
    {GPIO_ICL_N_GPP_R5,  GpioPadModeNative2} //I2S1_RXD
  },
  { //SSP2/I2S2
    {GPIO_ICL_N_GPP_H11, GpioPadModeNative1},//I2S2_SCLK
    {GPIO_ICL_N_GPP_H12, GpioPadModeNative1},//I2S2_SFRM
    {GPIO_ICL_N_GPP_H13, GpioPadModeNative1},//I2S2_TXD
    {GPIO_ICL_N_GPP_H14, GpioPadModeNative1} //I2S2_RXD
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides SSP/I2S interface pins

  @param[in]  SspInterfaceNumber       SSP/I2S interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaSspPins (
  IN  UINT32                      SspInterfaceNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (SspInterfaceNumber < ARRAY_SIZE (mPchLpHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchLpHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (SspInterfaceNumber < ARRAY_SIZE (mPchNHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchNHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// GPIO Pin for HD Audio SSP_MCLK/I2S_MCLK
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspMasterClockGpio = {GPIO_ICL_LP_GPP_D19, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaSspMasterClockGpio = {GPIO_ICL_N_GPP_D18,  GpioPadModeNative1};

/**
  This function sets HDA SSP Master Clock into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableHdaSspMasterClock (
  VOID
  )
{
  if (IsPchLp ()) {
    return GpioSetPadMode (mPchLpHdaSspMasterClockGpio.Pad, mPchLpHdaSspMasterClockGpio.Mode);
  } else if (IsPchN ()) {
    return GpioSetPadMode (mPchNHdaSspMasterClockGpio.Pad, mPchNHdaSspMasterClockGpio.Mode);
  } else {
    return EFI_UNSUPPORTED;
  }
}

//
// GPIO pins for HD Audio SoundWire interface [SNDW number][pin: CLK/DATA]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS] =
{
  { // SNDW1
    {GPIO_ICL_LP_GPP_S0, GpioPadModeNative1},// SNDW1_CLK
    {GPIO_ICL_LP_GPP_S1, GpioPadModeNative1} // SNDW1_DATA
  },
  { // SNDW2
    {GPIO_ICL_LP_GPP_S2, GpioPadModeNative1},// SNDW2_CLK
    {GPIO_ICL_LP_GPP_S3, GpioPadModeNative1} // SNDW2_DATA
  },
  { // SNDW3
    {GPIO_ICL_LP_GPP_S4, GpioPadModeNative1},// SNDW3_CLK
    {GPIO_ICL_LP_GPP_S5, GpioPadModeNative1} // SNDW3_DATA
  },
  { // SNDW4
    {GPIO_ICL_LP_GPP_S6, GpioPadModeNative1},// SNDW4_CLK
    {GPIO_ICL_LP_GPP_S7, GpioPadModeNative1} // SNDW4_DATA
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS] =
{
  { //SNDW1
    {GPIO_ICL_N_GPP_S4, GpioPadModeNative1},//SNDW1_CLK
    {GPIO_ICL_N_GPP_S5, GpioPadModeNative1} //SNDW1_DATA
  }
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides SNDW interface pins

  @param[in]  SndwInterfaceNumber      SNDWx interface number

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaSndwPins (
  IN  UINT32                      SndwInterfaceNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    if (SndwInterfaceNumber < ARRAY_SIZE (mPchLpHdaSndwGpio)) {
      *NativePinsTable = mPchLpHdaSndwGpio[SndwInterfaceNumber];
      return;
    }
  } else if (IsPchN ()) {
    if (SndwInterfaceNumber < ARRAY_SIZE (mPchNHdaSndwGpio)) {
      *NativePinsTable = mPchNHdaSndwGpio[SndwInterfaceNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}
#endif // MRC_MINIBIOS_BUILD
//
// GPIO pins for SMBUS
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_C0, GpioPadModeNative1},// SMB_CLK
  {GPIO_ICL_LP_GPP_C1, GpioPadModeNative1} // SMB_DATA
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_A7, GpioPadModeNative1},//SMB_CLK
  {GPIO_ICL_N_GPP_A8, GpioPadModeNative1} //SMB_DATA
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides SMBUS interface pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetSmbusPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpSmbusGpio;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNSmbusGpio;
  } else {
    *NativePinsTable = mPchHSmbusGpio;
  }
}

//
// SMBUS Alert pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusAlertGpio = {GPIO_ICL_LP_GPP_C2,  GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSmbusAlertGpio = {GPIO_ICL_N_GPP_A9,  GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusAlertGpio;
// @todo - update for ICL-PCH-H

/**
  This function sets SMBUS ALERT pin into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableSmbusAlert (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION SmbusAlertGpio;

  if (IsPchLp ()) {
    SmbusAlertGpio = mPchLpSmbusAlertGpio;
  } else if (IsPchN ()) {
    SmbusAlertGpio = mPchNSmbusAlertGpio;
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (SmbusAlertGpio.Pad, SmbusAlertGpio.Mode);
}

//
// SATADevSlpPin to GPIO pin mapping
// SATA_DEVSLP_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataDevSlpPinToGpioMap[] =
{
  {GPIO_ICL_LP_GPP_E4,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_E5,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_A11, GpioPadModeNative1}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSataDevSlpPinToGpioMap[] =
{
  // @todo - update for ICL-PCH-N
  {GPIO_ICL_N_GPP_E3,  GpioPadModeNative2},
  {GPIO_ICL_N_GPP_E7,  GpioPadModeNative2}
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataDevSlpPinToGpioMap[];
/// @todo - update for ICL-PCH-H

/**
  This function provides SATA DevSlp pin data

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number
  @param[out] NativePin           SATA DevSlp pin
**/
VOID
GpioGetSataDevSlpPin (
  IN  UINT32                    SataCtrlIndex,
  IN  UINTN                     SataPort,
  OUT GPIO_PAD_NATIVE_FUNCTION  *NativePin
  )
{
  if (IsPchLp ()) {
    if (SataPort < ARRAY_SIZE (mPchLpSataDevSlpPinToGpioMap)) {
      *NativePin = mPchLpSataDevSlpPinToGpioMap[SataPort];
      return;
    }
  } else if (IsPchN ()) {
    if (SataPort < ARRAY_SIZE (mPchNSataDevSlpPinToGpioMap)) {
      *NativePin = mPchNSataDevSlpPinToGpioMap[SataPort];
      return;
    }
  }
  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// SATA reset port to GPIO pin mapping
// SATAGP_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataGpToGpioMap[] =
{
  {GPIO_ICL_LP_GPP_E0,  GpioPadModeNative2},
  {GPIO_ICL_LP_GPP_A12, GpioPadModeNative2},
  {GPIO_ICL_LP_GPP_A13, GpioPadModeNative2}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSataGpToGpioMap[] =
{
  // @todo - update for ICL-PCH-N
  {GPIO_ICL_N_GPP_E8, GpioPadModeNative5},
  {GPIO_ICL_N_GPP_E9, GpioPadModeNative5}
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataGpToGpioMap[];
/// @todo - update for ICL-PCH-H

/**
  This function provides SATA GP pin data

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number
  @param[out] NativePin           SATA GP pin
**/
VOID
GpioGetSataGpPin (
  IN  UINT32                    SataCtrlIndex,
  IN  UINTN                     SataPort,
  OUT GPIO_PAD_NATIVE_FUNCTION  *NativePin
  )
{
  if (IsPchLp ()) {
    if (SataPort < ARRAY_SIZE (mPchLpSataGpToGpioMap)) {
      *NativePin = mPchLpSataGpToGpioMap[SataPort];
      return;
    }
  } else if (IsPchN ()) {
    if (SataPort < ARRAY_SIZE (mPchNSataGpToGpioMap)) {
      *NativePin = mPchNSataGpToGpioMap[SataPort];
      return;
    }
  }
  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// SATA LED pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataLedGpio = {GPIO_ICL_LP_GPP_E8, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSataLedGpio = {GPIO_ICL_N_GPP_E5, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataLedGpio;
// @todo - update for ICL-PCH-H

/**
  This function sets SATA LED pin into native mode. SATA LED indicates
  SATA controller activity

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableSataLed (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION  SataLedGpio;

  if (IsPchLp ()) {
    SataLedGpio = mPchLpSataLedGpio;
  } else if (IsPchN ()) {
    SataLedGpio = mPchNSataLedGpio;
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (SataLedGpio.Pad, SataLedGpio.Mode);
}

//
// USB2 OC pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpUsbOcGpioPins[] =
{
  {GPIO_ICL_LP_GPP_E9,  GpioPadModeNative1},// USB_OC_0
  {GPIO_ICL_LP_GPP_A14, GpioPadModeNative1},// USB_OC_1
  {GPIO_ICL_LP_GPP_A15, GpioPadModeNative1},// USB_OC_2
  {GPIO_ICL_LP_GPP_A16, GpioPadModeNative1} // USB_OC_3
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNUsbOcGpioPins[] =
{
  {GPIO_ICL_N_GPP_A18, GpioPadModeNative1},//USB_OC_0
  {GPIO_ICL_N_GPP_A12, GpioPadModeNative1},//USB_OC_1
  {GPIO_ICL_N_GPP_A13, GpioPadModeNative1},//USB_OC_2
  {GPIO_ICL_N_GPP_A14, GpioPadModeNative1} //USB_OC_3
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHUsbOcGpioPins[];
// @todo - update for ICL-PCH-H

/**
  This function enables USB OverCurrent pins by setting
  USB2 OCB pins into native mode

  @param[in]  OcPinNumber            USB OC pin number

  @retval Status
**/
EFI_STATUS
GpioEnableUsbOverCurrent (
  IN  UINTN   OcPinNumber
  )
{
  GPIO_PAD_NATIVE_FUNCTION  OcGpio;

  if (IsPchLp ()) {
    if (OcPinNumber >= ARRAY_SIZE (mPchLpUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchLpUsbOcGpioPins[OcPinNumber];
  } else if (IsPchN ()) {
    if (OcPinNumber >= ARRAY_SIZE (mPchNUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchNUsbOcGpioPins[OcPinNumber];
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (OcGpio.Pad, OcGpio.Mode);
}

/**
  This function report USB20 OverCurrent pins

  @param[out]  **OcGpioPtr            Update Gpio Pin Table address
  @param[out]  *OcPinNumber           Update PCH USB OC pin number of Count

  @retval Status
**/
EFI_STATUS
GetGpioUsbOverCurrentTableAddress (
  OUT  GPIO_PAD_NATIVE_FUNCTION **OcPinTableAddr,
  OUT  UINT32                   *MaxOcPinCount
  )
{
  if (IsPchLp ()) {
    *OcPinTableAddr = mPchLpUsbOcGpioPins;
    *MaxOcPinCount = ARRAY_SIZE (mPchLpUsbOcGpioPins);
  } else if (IsPchN ()) {
    *OcPinTableAddr = mPchNUsbOcGpioPins;
    *MaxOcPinCount = ARRAY_SIZE (mPchNUsbOcGpioPins);
  } else {
    *OcPinTableAddr = NULL;
    *MaxOcPinCount = 0;
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

//
// GPIO pin for PCIE SRCCLKREQB
// SRCCLKREQB_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_ICL_LP_GPP_D5,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_D6,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_D7,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_D8,  GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_H10, GpioPadModeNative1},
  {GPIO_ICL_LP_GPP_H11, GpioPadModeNative1}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_ICL_N_GPP_B5,  GpioPadModeNative1},
  {GPIO_ICL_N_GPP_B6,  GpioPadModeNative1},
  {GPIO_ICL_N_GPP_B7,  GpioPadModeNative1},
  {GPIO_ICL_N_GPP_B8,  GpioPadModeNative1},
  {GPIO_ICL_N_GPP_B9,  GpioPadModeNative1},
  {GPIO_ICL_N_GPP_B10, GpioPadModeNative1}
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPcieSrcClkReqbPinToGpioMap[];
// @todo - update for ICL-PCH-H

/**
  This function provides PCIe CLKREQ pin data

  @param[in]  ClkreqIndex        CLKREQ# number
  @param[out] NativePin          Native pin data
**/
VOID
GpioGetPcieClkReqPin (
  IN  UINT32                      ClkreqIndex,
  OUT GPIO_PAD_NATIVE_FUNCTION    *NativePin
  )
{
  if (IsPchLp ()) {
    if (ClkreqIndex < ARRAY_SIZE (mPchLpPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchLpPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
  } else if (IsPchN ()) {
    if (ClkreqIndex < ARRAY_SIZE (mPchNPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchNPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
  }
  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// PCHHOTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPchHotbPin = {GPIO_ICL_LP_GPP_B23,  GpioPadModeNative2};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNPchHotbPin = {GPIO_ICL_N_GPP_A19,  GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPchHotbPin;
// @todo - update for ICL-PCH-H

/**
  This function sets PCHHOT pin into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnablePchHot (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION PchHotbPin;

  if (IsPchLp ()) {
    PchHotbPin = mPchLpPchHotbPin;
  } else if (IsPchN ()) {
    PchHotbPin = mPchNPchHotbPin;
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (PchHotbPin.Pad, PchHotbPin.Mode);
}

//
// VRALERTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpVrAlertbPin = {GPIO_ICL_LP_GPP_B2, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNVrAlertbPin = {GPIO_ICL_N_GPP_B2, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHVrAlertbPin;
// @todo - update for ICL-PCH-H

//
// CPU_C10_GATE pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuC10GatePin = {GPIO_ICL_LP_GPP_H18, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCpuC10GatePin = {GPIO_ICL_N_GPP_H10, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuC10GatePin;
// @todo - update for ICL-PCH-H

/**
  This function sets VRALERTB pin into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableVrAlert (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION  VrAlertGpio;

  if (IsPchLp ()) {
    VrAlertGpio = mPchLpVrAlertbPin;
  } else if (IsPchN ()) {
    VrAlertGpio = mPchNVrAlertbPin;
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (VrAlertGpio.Pad, VrAlertGpio.Mode);
}

/**
This function sets CPU C10 Gate pins into native mode

@retval Status
**/
EFI_STATUS
GpioEnableCpuC10GatePin (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION  CpuC10GateGpio;

  if (IsPchLp ()) {
    CpuC10GateGpio = mPchLpCpuC10GatePin;
  } else if (IsPchN ()) {
    CpuC10GateGpio = mPchNCpuC10GatePin;
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (CpuC10GateGpio.Pad, CpuC10GateGpio.Mode);
}

//
// CPU GP pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_E3, GpioPadModeNative1}, // CPU_GP_0
  {GPIO_ICL_LP_GPP_E7, GpioPadModeNative1}, // CPU_GP_1
  {GPIO_ICL_LP_GPP_B3, GpioPadModeNative1}, // CPU_GP_2
  {GPIO_ICL_LP_GPP_B4, GpioPadModeNative1}, // CPU_GP_3
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_A10, GpioPadModeNative1}, // CPU_GP_0
  {GPIO_ICL_N_GPP_A11, GpioPadModeNative1}, // CPU_GP_1
  {GPIO_ICL_N_GPP_B3,  GpioPadModeNative1}, // CPU_GP_2
  {GPIO_ICL_N_GPP_B4,  GpioPadModeNative1}, // CPU_GP_3
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function sets CPU GP pins into native mode

  @param[in]  CpuGpPinNum               CPU GP pin number

  @retval Status
**/
EFI_STATUS
GpioEnableCpuGpPin (
  IN  UINT32                            CpuGpPinNum
  )
{
  GPIO_PAD_NATIVE_FUNCTION CpuGpPin;

  if (IsPchLp ()) {
    if (CpuGpPinNum >= ARRAY_SIZE (mPchLpCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchLpCpuGpPinMap[CpuGpPinNum];
  } else if (IsPchN ()) {
    if (CpuGpPinNum >= ARRAY_SIZE (mPchNCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchNCpuGpPinMap[CpuGpPinNum];
  } else {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return GpioSetPadMode (CpuGpPin.Pad, CpuGpPin.Mode);
}

//
// DDSP_HPD pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpDdspHpdPins[ICL_PCH_GPIO_DDSP_HPD_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_A19, GpioPadModeNative1},// DDSP_HPD_1
  {GPIO_ICL_LP_GPP_A20, GpioPadModeNative1},// DDSP_HPD_2
  {GPIO_ICL_LP_GPP_A14, GpioPadModeNative2},// DDSP_HPD_3
  {GPIO_ICL_LP_GPP_A15, GpioPadModeNative2},// DDSP_HPD_4
  {GPIO_ICL_LP_GPP_E14, GpioPadModeNative1},// DDSP_HPD_A
  {GPIO_ICL_LP_GPP_A18, GpioPadModeNative1},// DDSP_HPD_B
  {GPIO_ICL_LP_GPP_A17, GpioPadModeNative1} // DDSP_HPD_C
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNDdspHpdPins[] =
{
  {GPIO_ICL_N_GPP_A15, GpioPadModeNative1},//DDSP_HPD_A
  {GPIO_ICL_N_GPP_A16, GpioPadModeNative1},//DDSP_HPD_B
  {GPIO_ICL_N_GPP_A17, GpioPadModeNative1} //DDSP_HPD_C
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHDdspHpdPins[ICL_PCH_GPIO_DDSP_HPD_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function sets DDSP_HPDx pin into native mode

  @param[in]  DdspHpdPin     DDSP_HPDx pin

  @retval Status
**/
EFI_STATUS
GpioEnableDpHotPlugDetect (
  IN GPIO_DDSP_HPD  DdspHpdPin
  )
{
  GPIO_PAD_NATIVE_FUNCTION  DdspHpdGpio;
  UINT32                    DdspHpdPinIndex;

  switch (DdspHpdPin) {
    case GpioDdspHpd1:
    case GpioDdspHpd2:
    case GpioDdspHpd3:
    case GpioDdspHpd4:
      if (IsPchLp ()) {
        DdspHpdPinIndex = DdspHpdPin - GpioDdspHpd1;
      } else {
        goto Error;
      }
      break;
    case GpioDdspHpdA:
    case GpioDdspHpdB:
    case GpioDdspHpdC:
      if (IsPchLp ()) {
        DdspHpdPinIndex = (DdspHpdPin - GpioDdspHpdA) + 4;
      } else if (IsPchN ()) {
        DdspHpdPinIndex = DdspHpdPin - GpioDdspHpdA;
      } else {
        goto Error;
      }
      break;
    default:
      goto Error;
  }

  if (IsPchLp ()) {
    if (DdspHpdPinIndex >= ARRAY_SIZE (mPchLpDdspHpdPins)) {
      goto Error;
    }
    DdspHpdGpio = mPchLpDdspHpdPins[DdspHpdPinIndex];
  } else if (IsPchN ()) {
    if (DdspHpdPinIndex >= ARRAY_SIZE (mPchNDdspHpdPins)) {
      goto Error;
    }
    DdspHpdGpio = mPchNDdspHpdPins[DdspHpdPinIndex];
  } else {
    goto Error;
  }

  return GpioSetPadMode (DdspHpdGpio.Pad, DdspHpdGpio.Mode);
Error:
  ASSERT (FALSE);
  return EFI_UNSUPPORTED;
}

//
// EDP VDD and BKLT pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpEdpPins[PCH_GPIO_EDP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_E14,          GpioPadModeNative1},// DDSP_HPD_A
  {GPIO_ICL_LP_HVCMOS_L_VDDEN,   GpioPadModeNative1},// VDDEN
  {GPIO_ICL_LP_HVCMOS_L_BKLTEN,  GpioPadModeNative1},// BKLTEN
  {GPIO_ICL_LP_HVCMOS_L_BKLTCTL, GpioPadModeNative1} // BKLTCTL
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNEdpPins[PCH_GPIO_EDP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-N

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHEdpPins[PCH_GPIO_EDP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides eDP pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetEdpPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpEdpPins;
    *NoOfNativePins = ARRAY_SIZE (mPchLpEdpPins);
  } else if (IsPchN()) {
    *NativePinsTable = NULL;
    *NoOfNativePins = 0;
  } else {
    *NativePinsTable = NULL;
    *NoOfNativePins = 0;
    ASSERT (FALSE);
  }
}

//
// DDP1/2/3/4/A/B/C  CTRLCLK and CTRLDATA pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpDdpInterfacePins[ICL_PCH_GPIO_DDP_NUMBER_OF_INTERFACES][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {// DDP1
    {GPIO_ICL_LP_GPP_E18, GpioPadModeNative1},// DDP1_CTRLCLK
    {GPIO_ICL_LP_GPP_E19, GpioPadModeNative1} // DDP1_CTRLDATA
  },
  {// DDP2
    {GPIO_ICL_LP_GPP_E20, GpioPadModeNative1},// DDP2_CTRLCLK
    {GPIO_ICL_LP_GPP_E21, GpioPadModeNative1} // DDP2_CTRLDATA
  },
  {// DDP3
    {GPIO_ICL_LP_GPP_D9,  GpioPadModeNative2},// DDP3_CTRLCLK
    {GPIO_ICL_LP_GPP_D10, GpioPadModeNative2} // DDP3_CTRLDATA
  },
  {// DDP4
    {GPIO_ICL_LP_GPP_D11, GpioPadModeNative2},// DDP4_CTRLCLK
    {GPIO_ICL_LP_GPP_D12, GpioPadModeNative2} // DDP4_CTRLDATA
  },
  {// DDPA
    {GPIO_ICL_LP_GPP_E22, GpioPadModeNative1},// DDPA_CTRLCLK
    {GPIO_ICL_LP_GPP_E23, GpioPadModeNative1} // DDPA_CTRLDATA
  },
  {// DDPB
    {GPIO_ICL_LP_GPP_H16, GpioPadModeNative1},// DDPB_CTRLCLK
    {GPIO_ICL_LP_GPP_H17, GpioPadModeNative1} // DDPB_CTRLDATA
  },
  {// DDPC
    {GPIO_ICL_LP_GPP_A21, GpioPadModeNative2},// DDPC_CTRLCLK
    {GPIO_ICL_LP_GPP_A22, GpioPadModeNative2} // DDPC_CTRLDATA
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNDdpInterfacePins[][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {//DDPA
    {GPIO_ICL_N_GPP_E13, GpioPadModeNative1},//DDPA_CTRLCLK
    {GPIO_ICL_N_GPP_E14, GpioPadModeNative1} //DDPA_CTRLDATA
  },
  {//DDPB
    {GPIO_ICL_N_GPP_E15, GpioPadModeNative1},//DDPB_CTRLCLK
    {GPIO_ICL_N_GPP_E16, GpioPadModeNative1} //DDPB_CTRLDATA
  },
  {//DDPC
    {GPIO_ICL_N_GPP_E17, GpioPadModeNative1},//DDPC_CTRLCLK
    {GPIO_ICL_N_GPP_E18, GpioPadModeNative1} //DDPC_CTRLDATA
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHDdpInterfacePins[PCH_GPIO_DDP_NUMBER_OF_INTERFACES][PCH_GPIO_DDP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides DDPx interface pins

  @param[in]  DdpInterface   DDPx interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetDdpPins (
  IN  GPIO_DDP                    DdpInterface,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
  UINT32  DdpInterfaceIndex;

  switch (DdpInterface) {
    case GpioDdp1:
    case GpioDdp2:
    case GpioDdp3:
    case GpioDdp4:
      if (IsPchLp ()) {
        DdpInterfaceIndex = DdpInterface - GpioDdp1;
      } else {
        goto Error;
      }
      break;
    case GpioDdpA:
    case GpioDdpB:
    case GpioDdpC:
      if (IsPchLp ()) {
        DdpInterfaceIndex = (DdpInterface - GpioDdpA) + 4;
      } else if (IsPchN ()) {
        DdpInterfaceIndex = DdpInterface - GpioDdpA;
      } else {
        goto Error;
      }
      break;
    default:
      goto Error;
  }

  if (IsPchLp ()) {
    if (DdpInterfaceIndex < ARRAY_SIZE (mPchLpDdpInterfacePins)) {
      *NativePinsTable = mPchLpDdpInterfacePins[DdpInterfaceIndex];
      return;
    }
  } else if (IsPchN ()) {
    if (DdpInterfaceIndex < ARRAY_SIZE (mPchNDdpInterfacePins)) {
      *NativePinsTable = mPchNDdpInterfacePins[DdpInterfaceIndex];
      return;
    }
  }
Error:
  *NativePinsTable = NULL;
  ASSERT(FALSE);
}

/**
  This function enables CNVi RF Reset pin
**/
VOID
GpioEnableCnviRfResetPin (
  VOID
  )
{
  EFI_STATUS      Status;
  GPIO_PAD        GpioPad;
  GPIO_PAD_MODE   PadMode;

  if (IsPchLp ()) {
    GpioPad = GPIO_ICL_LP_GPP_A8;
    PadMode = GpioPadModeNative2;
  } else if (IsPchN ()) {
    GpioPad = GPIO_ICL_N_GPP_H12;
    PadMode = GpioPadModeNative2;
  } else {
    ASSERT (FALSE);
    return;
  }

  Status = GpioSetPadMode (GpioPad, PadMode);
  ASSERT_EFI_ERROR (Status);
}

/**
  This function enables CNVi MODEM CLKREQ pin
**/
VOID
GpioEnableCnviModemClkReqPin (
  VOID
  )
{
  EFI_STATUS      Status;
  GPIO_PAD        GpioPad;
  GPIO_PAD_MODE   PadMode;

  if (IsPchLp ()) {
    GpioPad = GPIO_ICL_LP_GPP_A9;
    PadMode = GpioPadModeNative2;
  } else if (IsPchN ()) {
    GpioPad = GPIO_ICL_N_GPP_H13;
    PadMode = GpioPadModeNative2;
  } else {
    ASSERT (FALSE);
    return;
  }

  Status = GpioSetPadMode (GpioPad, PadMode);
  ASSERT_EFI_ERROR (Status);
}


/**
  This function provides CNVi BT interface select pin

  @retval GpioPad          GPIO pad for CNVi BT interface select
**/
GPIO_PAD
GpioGetCnviBtIfSelectPin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_VGPIO5;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO5;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

/**
  This function provides CNVi BT Charging pin

  @retval GpioPad          GPIO pad for CNVi BT Charging select
**/
GPIO_PAD
GpioGetCnviBtChargingPin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_VGPIO3;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO3;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

/**
  This function provides CNVi A4WP pin

  @param[out] GpioNativePad       GPIO native pad for CNVi A4WP
**/
VOID
GpioGetCnviA4WpPin (
  OUT GPIO_PAD_NATIVE_FUNCTION  *GpioNativePad
  )
{
  if (IsPchLp ()) {
    GpioNativePad->Mode = GpioPadModeNative1;
    GpioNativePad->Pad = GPIO_ICL_LP_GPP_F19;
  } else {
    ASSERT (FALSE);
    *GpioNativePad = (GPIO_PAD_NATIVE_FUNCTION){0};
  }
}

/**
  This function provides CNVi BT host wake int pin

  @retval GpioPad          GPIO pad BT host wake int
**/
GPIO_PAD
GpioGetCnviBtHostWakeIntPin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_VGPIO4;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO4;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

//
// CNVi Bluetooth UART pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_ICL_LP_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_ICL_LP_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_ICL_LP_VGPIO9  // vCNV_BT_UART_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_ICL_N_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_ICL_N_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_ICL_N_VGPIO9  // vCNV_BT_UART_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H


//
// vUART for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO18, // vUART0_TXD
  GPIO_ICL_LP_VGPIO19, // vUART0_RXD
  GPIO_ICL_LP_VGPIO20, // vUART0_CTS_B
  GPIO_ICL_LP_VGPIO21  // vUART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO18, // vUART0_TXD
  GPIO_ICL_N_VGPIO19, // vUART0_RXD
  GPIO_ICL_N_VGPIO20, // vUART0_CTS_B
  GPIO_ICL_N_VGPIO21  // vUART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi BT UART pins

  @param[in]  ConnectionType           CNVi BT UART connection type
  @param[out] VCnviBtUartPad           Table with vCNV_BT_UARTx pads
  @param[out] VCnviBtUartPadMode       vCNV_BT_UARTx pad mode
  @param[out] VUartForCnviBtPad        Table with vUART0 pads
  @param[out] VUartForCnviBtPadMode    vUART0 pad mode
**/
VOID
GpioGetCnviBtUartPins (
  IN  VGPIO_CNVI_BT_UART_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                            **VCnviBtUartPad,
  OUT GPIO_PAD_MODE                       *VCnviBtUartPadMode,
  OUT GPIO_PAD                            **VUartForCnviBtPad,
  OUT GPIO_PAD_MODE                       *VUartForCnviBtPadMode
  )
{
  if (IsPchLp ()) {
    *VCnviBtUartPad = mPchLpVCnviBtUartGpioPad;
    *VUartForCnviBtPad = mPchLpVUartForCnviBtGpioPad;
  } else if (IsPchN ()) {
    *VCnviBtUartPad = mPchNVCnviBtUartGpioPad;
    *VUartForCnviBtPad = mPchNVUartForCnviBtGpioPad;
  } else {
    ASSERT (FALSE);
    *VCnviBtUartPad = NULL;
    *VUartForCnviBtPad = NULL;
    return;
  }

  switch (ConnectionType) {
    case GpioCnviBtUartToSerialIoUart0:
      *VCnviBtUartPadMode = GpioPadModeNative1;
      *VUartForCnviBtPadMode = GpioPadModeNative1;
      break;
    case GpioCnviBtUartToIshUart0:
      *VCnviBtUartPadMode = GpioPadModeNative2;
      *VUartForCnviBtPadMode = GpioPadModeNative1;
      break;
    case GpioCnviBtUartNotConnected:
    case GpioCnviBtUartToExternalPads:
      *VCnviBtUartPadMode = GpioPadModeGpio;
      *VUartForCnviBtPadMode = GpioPadModeGpio;
      break;
    default:
      ASSERT (FALSE);
      return;
  }
}

//
// CNVi Bluetooth UART external pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCnviBtUartExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_C8,  GpioPadModeNative2}, // CNV_BT_UART_0_RXD
  {GPIO_ICL_LP_GPP_C9,  GpioPadModeNative2}, // CNV_BT_UART_0_TXD
  {GPIO_ICL_LP_GPP_C10, GpioPadModeNative2}, // CNV_BT_UART_0_RTS
  {GPIO_ICL_LP_GPP_C11, GpioPadModeNative2}  // CNV_BT_UART_0_CTS
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCnviBtUartExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_C8,  GpioPadModeNative2}, // CNV_BT_UART_0_RXD
  {GPIO_ICL_N_GPP_C9,  GpioPadModeNative2}, // CNV_BT_UART_0_TXD
  {GPIO_ICL_N_GPP_C10, GpioPadModeNative2}, // CNV_BT_UART_0_RTS
  {GPIO_ICL_N_GPP_C11, GpioPadModeNative2}  // CNV_BT_UART_0_CTS
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBtUartExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi BT UART external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtUartExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpCnviBtUartExternalPads;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNCnviBtUartExternalPads;
  } else {
    ASSERT (FALSE);
    return;
  }
}

//
// CNVi Bluetooth I2S pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_ICL_LP_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_ICL_LP_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_ICL_LP_VGPIO33  // vCNV_BT_I2S_SDI
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_ICL_N_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_ICL_N_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_ICL_N_VGPIO33  // vCNV_BT_I2S_SDI
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H


//
// vSSP for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO34, // vSSP2_SCLK
  GPIO_ICL_LP_VGPIO35, // vSSP2_SFRM
  GPIO_ICL_LP_VGPIO36, // vSSP2_TXD
  GPIO_ICL_LP_VGPIO37  // vSSP2_RXD
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO34, // vSSP2_SCLK
  GPIO_ICL_N_VGPIO35, // vSSP2_SFRM
  GPIO_ICL_N_VGPIO36, // vSSP2_TXD
  GPIO_ICL_N_VGPIO37  // vSSP2_RXD
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi BT I2S pins

  @param[in]  ConnectionType          CNVi BT I2S connection type
  @param[out] VCnviBtI2sPad           Table with vCNV_BT_I2Sx pads
  @param[out] VCnviBtI2sPadMode       vCNV_BT_I2Sx pad mode
  @param[out] VSspForCnviBtPad        Table with vSSP2 pads
  @param[out] VSspForCnviBtPadMode    vSSP2 pad mode
**/
VOID
GpioGetCnviBtI2sPins (
  IN  VGPIO_CNVI_BT_I2S_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                 **VCnviBtI2sPad,
  OUT GPIO_PAD_MODE            *VCnviBtI2sPadMode,
  OUT GPIO_PAD                 **VSspForCnviBtPad,
  OUT GPIO_PAD_MODE            *VSspForCnviBtPadMode
  )
{
  if (IsPchLp ()) {
    *VCnviBtI2sPad = mPchLpVCnviBtI2sGpioPad;
    *VSspForCnviBtPad = mPchLpVSspForCnviBtGpioPad;
  } else if (IsPchN ()) {
    *VCnviBtI2sPad = mPchNVCnviBtI2sGpioPad;
    *VSspForCnviBtPad = mPchNVSspForCnviBtGpioPad;
  } else {
    ASSERT (FALSE);
    *VCnviBtI2sPad = NULL;
    *VSspForCnviBtPad = NULL;
    return;
  }

  switch (ConnectionType) {
    case GpioCnviBtI2sToSsp0:
      *VCnviBtI2sPadMode = GpioPadModeNative1;
      *VSspForCnviBtPadMode = GpioPadModeNative1;
      break;
    case GpioCnviBtI2sToSsp1:
      *VCnviBtI2sPadMode = GpioPadModeNative2;
      *VSspForCnviBtPadMode = GpioPadModeNative1;
      break;
    case GpioCnviBtI2sToSsp2:
      *VCnviBtI2sPadMode = GpioPadModeNative3;
      *VSspForCnviBtPadMode = GpioPadModeNative1;
      break;
    case GpioCnviBtI2sNotConnected:
    case GpioCnviBtI2sToExternalPads:
      *VCnviBtI2sPadMode = GpioPadModeGpio;
      *VSspForCnviBtPadMode = GpioPadModeGpio;
      break;
    default:
      ASSERT (FALSE);
      return;
  }
}

//
// CNVi Bluetooth I2S external pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCnviBtI2sExternalPads[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_H0,  GpioPadModeNative2}, // CNV_BT_I2S_WS_SYNC
  {GPIO_ICL_LP_GPP_H1,  GpioPadModeNative2}, // CNV_BT_I2S_BCLK
  {GPIO_ICL_LP_GPP_H2,  GpioPadModeNative2}, // CNV_BT_I2S_SDI
  {GPIO_ICL_LP_GPP_H3,  GpioPadModeNative2}  // CNV_BT_I2S_SDO
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCnviBtI2sExternalPads[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_H0,  GpioPadModeNative2}, // CNV_BT_I2S_WS_SYNC
  {GPIO_ICL_N_GPP_H1,  GpioPadModeNative2}, // CNV_BT_I2S_BCLK
  {GPIO_ICL_N_GPP_H2,  GpioPadModeNative2}, // CNV_BT_I2S_SDI
  {GPIO_ICL_N_GPP_H3,  GpioPadModeNative2}  // CNV_BT_I2S_SDO
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBtI2sExternalPads[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi BT I2S external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtI2sExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpCnviBtI2sExternalPads;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNCnviBtI2sExternalPads;
  } else {
    ASSERT (FALSE);
    return;
  }
}

//
// CNVi MFUART1 pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_ICL_LP_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_ICL_LP_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_ICL_LP_VGPIO13  // vCNV_MFUART1_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_ICL_N_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_ICL_N_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_ICL_N_VGPIO13  // vCNV_MFUART1_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H


//
// vUART for MFUART1
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_LP_VGPIO22, // vISH_UART0_TXD
  GPIO_ICL_LP_VGPIO23, // vISH_UART0_RXD
  GPIO_ICL_LP_VGPIO24, // vISH_UART0_CTS_B
  GPIO_ICL_LP_VGPIO25  // vISH_UART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_N_VGPIO22, // vISH_UART0_TXD
  GPIO_ICL_N_VGPIO23, // vISH_UART0_RXD
  GPIO_ICL_N_VGPIO24, // vISH_UART0_CTS_B
  GPIO_ICL_N_VGPIO25  // vISH_UART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi MFUART1 pins

  @param[in]  ConnectionType          CNVi MFUART1 connection type
  @param[out] VCnviBtI2sPad           Table with vCNV_MFUART1x pads
  @param[out] VCnviBtI2sPadMode       vCNV_MFUART1x pad mode
  @param[out] VSspForCnviBtPad        Table with vISH_UART0 pads
  @param[out] VSspForCnviBtPadMode    vISH_UART0 pad mode
**/
VOID
GpioGetCnviMfUart1Pins (
  IN  VGPIO_CNVI_MF_UART1_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                 **VCnviMfUart1Pad,
  OUT GPIO_PAD_MODE            *VCnviMfUart1PadMode,
  OUT GPIO_PAD                 **VUartForCnviMfUart1Pad,
  OUT GPIO_PAD_MODE            *VUartForCnviMfUart1PadMode
  )
{
  if (IsPchLp ()) {
    *VCnviMfUart1Pad = mPchLpVCnviMfUart1GpioPad;
    *VUartForCnviMfUart1Pad = mPchLpVUartForCnviMfUart1GpioPad;
  } else if (IsPchN ()) {
    *VCnviMfUart1Pad = mPchNVCnviMfUart1GpioPad;
    *VUartForCnviMfUart1Pad = mPchNVUartForCnviMfUart1GpioPad;
  } else {
    ASSERT (FALSE);
    *VCnviMfUart1Pad = NULL;
    *VUartForCnviMfUart1Pad = NULL;
    return;
  }

  switch (ConnectionType) {
    case GpioCnviMfUart1ToSerialIoUart2:
      *VCnviMfUart1PadMode = GpioPadModeNative2;
      *VUartForCnviMfUart1PadMode = GpioPadModeNative1;
      break;
    case GpioCnviMfUart1ToIshUart0:
      *VCnviMfUart1PadMode = GpioPadModeNative1;
      *VUartForCnviMfUart1PadMode = GpioPadModeNative1;
      break;
    case GpioCnviMfUart1NotConnected:
    case GpioCnviMfUart1ToExternalPads:
      *VCnviMfUart1PadMode = GpioPadModeGpio;
      *VUartForCnviMfUart1PadMode = GpioPadModeGpio;
      break;
    default:
      ASSERT (FALSE);
      return;
  }
}

//
// CNVi MFUART1 external pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCnviMfUart1ExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_C12, GpioPadModeNative3}, // CNV_MFUART1_RXD
  {GPIO_ICL_LP_GPP_C13, GpioPadModeNative3}, // CNV_MFUART1_TXD
  {GPIO_ICL_LP_GPP_C14, GpioPadModeNative3}, // CNV_MFUART1_RTS
  {GPIO_ICL_LP_GPP_C15, GpioPadModeNative3}  // CNV_MFUART1_CTS
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCnviMfUart1ExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_C12, GpioPadModeNative3}, // CNV_MFUART1_RXD
  {GPIO_ICL_N_GPP_C13, GpioPadModeNative3}, // CNV_MFUART1_TXD
  {GPIO_ICL_N_GPP_C14, GpioPadModeNative3}, // CNV_MFUART1_RTS
  {GPIO_ICL_N_GPP_C15, GpioPadModeNative3}  // CNV_MFUART1_CTS
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviMfUart1ExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi MFUART1 external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviMfUart1ExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpCnviMfUart1ExternalPads;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNCnviMfUart1ExternalPads;
  } else {
    ASSERT (FALSE);
    return;
  }
}

/**
  This function provides CNVi Bluetooth Enable pad

  @retval GpioPad           CNVi Bluetooth Enable pad
**/
GPIO_PAD
GpioGetCnviBtEnablePin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_VGPIO0;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO0;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

//
// CNVi BRI (Bluetooth Radio Interface) and RGI (Radio Generic Interface) buses from Pulsar to CRF (Companion RF)
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_F0,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_ICL_LP_GPP_F1,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_ICL_LP_GPP_F2,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_ICL_LP_GPP_F3,  GpioPadModeNative1}  // CNV_RGI_RSP
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_E20,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_ICL_N_GPP_E21,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_ICL_N_GPP_E22,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_ICL_N_GPP_E23,  GpioPadModeNative1}  // CNV_RGI_RSP
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS];
// @todo - update for ICL-PCH-H

/**
  This function provides CNVi BRI RGI GPIO pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnvBriRgiPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpCnviBriRgiGpioPad;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNCnviBriRgiGpioPad;
  } else {
    ASSERT (FALSE);
    return;
  }
}

#ifndef MRC_MINIBIOS_BUILD
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpImguClkOutGpioPad[5] =
{
  {GPIO_ICL_LP_GPP_D4,   GpioPadModeNative1}, // IMGCLKOUT_0
  {GPIO_ICL_LP_GPP_H20,  GpioPadModeNative1}, // IMGCLKOUT_1
  {GPIO_ICL_LP_GPP_H21,  GpioPadModeNative1}, // IMGCLKOUT_2
  {GPIO_ICL_LP_GPP_H22,  GpioPadModeNative1}, // IMGCLKOUT_3
  {GPIO_ICL_LP_GPP_H23,  GpioPadModeNative1}  // IMGCLKOUT_4
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNImguClkOutGpioPad[5] =
{
  {GPIO_ICL_N_GPP_E0,  GpioPadModeNative2}, // IMGCLKOUT_0
  {GPIO_ICL_N_GPP_E2,  GpioPadModeNative1}, // IMGCLKOUT_1
  {GPIO_ICL_N_GPP_E4,  GpioPadModeNative1}, // IMGCLKOUT_2
  {GPIO_ICL_N_GPP_E6,  GpioPadModeNative1}, // IMGCLKOUT_3
  {GPIO_ICL_N_GPP_E12, GpioPadModeNative1}  // IMGCLKOUT_4
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHImguClkOutGpioPad[];
// @todo - update for ICL-PCH-H

/**
  This function provides IMGCLKOUT pins

  @param[out] NativePinsTable          Table with pins
  @param[out] NoOfNativePins            Number of pins
**/
VOID
GpioGetImgClkOutPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable,
  OUT UINT32                   *NoOfNativePins
  )
{
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpImguClkOutGpioPad;
    *NoOfNativePins = ARRAY_SIZE (mPchLpImguClkOutGpioPad);
    return;
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNImguClkOutGpioPad;
    *NoOfNativePins = ARRAY_SIZE (mPchNImguClkOutGpioPad);
    return;
  }
  *NativePinsTable = NULL;
  *NoOfNativePins = 0;
  ASSERT (FALSE);
}

/**
  This function provides PWRBTN pin

  @retval GpioPad          PWRTBTN pin
**/
GPIO_PAD
GpioGetPwrBtnPin (
  VOID
  )
{
  if (IsPchLp ()) {
    return GPIO_ICL_LP_GPD3;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_GPD3;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpTypeCSbuGpioPad[] =
{
  GPIO_ICL_LP_GPP_E18, // BSSB_LS0_RX
  GPIO_ICL_LP_GPP_E19, // BSSB_LS0_TX
  GPIO_ICL_LP_GPP_E20, // BSSB_LS1_RX
  GPIO_ICL_LP_GPP_E21, // BSSB_LS1_TX
  GPIO_ICL_LP_GPP_D9,  // BSSB_LS2_RX
  GPIO_ICL_LP_GPP_D10, // BSSB_LS2_TX
  GPIO_ICL_LP_GPP_D11, // BSSB_LS3_RX
  GPIO_ICL_LP_GPP_D12  // BSSB_LS3_TX
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchNTypeCSbuGpioPad[] =
{
  GPIO_ICL_N_GPP_E13, // BSSB_LS0_RX
  GPIO_ICL_N_GPP_E14, // BSSB_LS0_TX
  GPIO_ICL_N_GPP_E15, // BSSB_LS1_RX
  GPIO_ICL_N_GPP_E16, // BSSB_LS1_TX
  GPIO_ICL_N_GPP_E17, // BSSB_LS2_RX
  GPIO_ICL_N_GPP_E18, // BSSB_LS2_TX
  GPIO_ICL_N_GPP_E11, // BSSB_LS3_RX
  GPIO_ICL_N_GPP_B12, // BSSB_LS3_TX
  GPIO_ICL_N_GPP_E20, // BSSB_LS4_RX
  GPIO_ICL_N_GPP_E21, // BSSB_LS4_TX
  GPIO_ICL_N_GPP_E22, // BSSB_LS5_RX
  GPIO_ICL_N_GPP_E23, // BSSB_LS5_TX
};

//GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHTypeCSbuGpioPad[];
// =
//{
//  GPIO_ICL_H_GPP_G12,  // BSSB_LS0_RX
//  GPIO_ICL_H_GPP_G13,  // BSSB_LS0_TX
//  GPIO_ICL_H_GPP_G14,  // BSSB_LS1_RX
//  GPIO_ICL_H_GPP_G15,  // BSSB_LS1_TX
//  GPIO_ICL_H_GPP_G10,  // BSSB_LS2_RX
//  GPIO_ICL_H_GPP_G11,  // BSSB_LS2_TX
//  GPIO_ICL_H_GPP_G12,  // BSSB_LS3_RX
//  GPIO_ICL_H_GPP_G13   // BSSB_LS3_TX
//};

/**
  The function sets VCCIOSEL

  @param[in]  GpioPad             GPIO pad
  @param[in]  VccioSel            Pad voltage

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_UNSUPPORTED         The Pin is owned by others
  @retval EFI_INVALID_PARAMETER   Invalid group or parameter
**/
EFI_STATUS
GpioSetVccLevel (
  IN  GPIO_PAD        GpioPad,
  IN  GPIO_VCCIO_SEL  VccioSel
  )
{
  if (VccioSel >= MaxVccioSel) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  if (!GpioIsPadValid (GpioPad)) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  if (!GpioIsPadHostOwned (GpioPad)) {
    return EFI_UNSUPPORTED;
  }

  GpioWritePadCfgReg (
    GpioPad,
    2,
    (UINT32)~B_GPIO_PCR_VCCIOSEL,
    VccioSel << N_GPIO_PCR_VCCIOSEL
    );
  return EFI_SUCCESS;
}

/**
  SBU (Sideband use) pins are used as auxiliary signals for Type C connector,
  which are hard-wired to BSSB_LS natively for debug function.
  when USB-C is enablde and debug not needed, disable pins (BSSB) used for debug through TypeC connector,
  program SBU pins to high-Z/open circuit per USB-C spec.

  @param[in]  UsbTcPortEnBitmap   USB Type C port enabled bitmap

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_UNSUPPORTED         SBU pads are not supported
  @retval EFI_INVALID_PARAMETER   Invalid input parameter
**/
EFI_STATUS
GpioDisableTypeCSbuDebug (
  IN UINT32           UsbTcPortEnBitmap
  )
{
  GPIO_PAD            *GpioSbuPadTable;
  GPIO_CONFIG         PadConfig;
  UINT32              Index;
  UINT32              PortIndex;

  GpioSbuPadTable   = NULL;
  Index             = 0;
  PortIndex         = 0;
  ZeroMem (&PadConfig, sizeof (GPIO_CONFIG));

  if (HighBitSet32 (UsbTcPortEnBitmap) + 1 > GetPchMaxTypeCPortNum ()) { // check if MSB exceeds max port number
    return EFI_INVALID_PARAMETER;
  }
  if (IsPchLp ()) {
    GpioSbuPadTable = mPchLpTypeCSbuGpioPad;
  } else if (IsPchN ()) {
    GpioSbuPadTable = mPchNTypeCSbuGpioPad;
  } else {
    return EFI_UNSUPPORTED;
  }
  //
  // For USB-C SBU function usage, the pins must be routed to a Type-C connector.
  // BIOS needs to configure the pin to high-Z/open circuit (select GPIO function with TX disable) if debug is disabled,
  // that would guarantees PCH GPIO is not driving to external device.
  // Having 3.3V setting in high-Z/open circuit mode is just a precaution to protect the GPIO in case the external device is driving into PCH.
  //
  for (PortIndex = 0; PortIndex < GetPchMaxTypeCPortNum (); PortIndex++) {
    if (UsbTcPortEnBitmap & (BIT0 << PortIndex)) {
      for (Index = 0; Index < 2; Index++) {
        PadConfig.PadMode   = GpioPadModeGpio;                // Set GPIO moode
        PadConfig.Direction = GpioDirNone;                    // Set High-Z
        GpioSetVccLevel (GpioSbuPadTable[PortIndex * 2 + Index], GpioVcc3v3); // Set VCCIO to High voltage
        GpioSetPadConfig (GpioSbuPadTable[PortIndex * 2 + Index], &PadConfig);
      }
    }
  }
  return EFI_SUCCESS;
}
#endif // MRC_MINIBIOS_BUILD
