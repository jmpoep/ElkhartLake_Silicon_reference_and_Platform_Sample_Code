/** @file
  This file contains VER3 specific GPIO information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Pins/GpioPinsVer3.h>
#include <Register/GpioRegs.h>

#include "GpioNativePrivateLibInternal.h"

/**
  This function provides GPIO Native Pad for a given native function

  @param[in]  PadFunction            PadFunction for a specific native signal. Please refer to GpioNativePads.h

  @retval     NativePad              GPIO pad with encoded native function
**/
GPIO_NATIVE_PAD
GpioGetNativePadByFunction (
  IN  UINT32                      PadFunction
  )
{
  if (IsPchLp ()) {
    switch (PadFunction) {
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C12, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C20, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C13, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C21, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C14, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C22, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C15, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C23, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI(0):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D12, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO(0):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D11, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D10, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(0, 0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(0, 1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B14, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(1, 0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(1, 1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B23, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(2, 0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D9,  7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS(2, 1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D15, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C17, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C19, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B10, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T1,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(7):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T3,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C16, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C18, 4, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T0,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(7):    return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T2,  3, PadFunction);
      case GPIO_FUNCTION_PSE_I2S_RX(1):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F19, 1, PadFunction);
      case GPIO_FUNCTION_PSE_I2S_TX(1):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F18, 1, PadFunction);
      case GPIO_FUNCTION_PSE_I2S_CLK(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_I2S_SFRM(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F10, 1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(0):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C2,  1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(1):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C5,  1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(2):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D4,  1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(3):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(4):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D17, 1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(5):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D18, 1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(6):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D3,  1, PadFunction);
      case GPIO_FUNCTION_PSE_PWM(7):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H20, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(3):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C16, 3, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(4):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RX(5):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H0,  4, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(3):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C17, 3, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(4):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_TX(5):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H1,  4, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H21, 2, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(2):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T14, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(3):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C4,  3, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(4):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_RTS(5):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H2,  4, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(2):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(3):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C5,  3, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(4):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_PSE_UART_CTS(5):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H3,  4, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_DE(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_DE(1):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H21, 1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_DE(2):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T14, 3, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_DE(3):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C4,  4, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_RE(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C11, 1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_RE(1):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H22, 1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_RE(2):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T10, 1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_RE(3):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C7,  3, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_EN(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C9,  1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_EN(1):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H23, 1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_EN(2):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T9,  1, PadFunction);
      case GPIO_FUNCTION_PSE_HSUART_EN(3):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C3,  3, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_A(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D0,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_A(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_A(2):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T0,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_A(3):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_B(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D1,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_B(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D14, 1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_B(2):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T1,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_B(3):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U11, 1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_I(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D2,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_I(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D16, 1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_I(2):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T2,  1, PadFunction);
      case GPIO_FUNCTION_PSE_QEP_I(3):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U19, 1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B6,  1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B8,  1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B9,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(3):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C1,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(4):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(5):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H6,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(6):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U1,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SDA(7):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U3,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B5,  1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B10, 2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(3):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C0,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(4):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(5):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H7,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(6):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U0,  2, PadFunction);
      case GPIO_FUNCTION_PSE_I2C_SCL(7):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_U2,  2, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MOSI(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MOSI(2):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B18, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MOSI(3):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B22, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MISO(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D11, 1, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MISO(2):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B17, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_MISO(3):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B21, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CLK(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D10, 1, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CLK(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B16, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CLK(3):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B20, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(0, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D9,  1, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(0, 1):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D15, 4, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(1, 1):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D4,  4, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(2, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B15, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(2, 1):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B14, 4, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(3, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B19, 3, PadFunction);
      case GPIO_FUNCTION_PSE_SPI_CS(3, 1):       return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B23, 4, PadFunction);
      case GPIO_FUNCTION_PSE_CAN_RX(0):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E16, 7, PadFunction);
      case GPIO_FUNCTION_PSE_CAN_RX(1):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E21, 7, PadFunction);
      case GPIO_FUNCTION_PSE_CAN_TX(0):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E15, 7, PadFunction);
      case GPIO_FUNCTION_PSE_CAN_TX(1):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E20, 7, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(2):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V14, 1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(3):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(4):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C8,  1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(5):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C10, 1, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(20):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H19, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(21):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H3,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(22):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T8,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(23):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E18, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(24):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E19, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(25):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B2,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(26):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B3,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(27):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B4,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(28):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_B23, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(29):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C2,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(30):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C5,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(31):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G12, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(32):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D0,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(33):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D1,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(34):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D2,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(35):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D3,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(36):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D4,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(37):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D13, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(38):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D14, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(39):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D15, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(40):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D16, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(41):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D17, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(42):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D18, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(43):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_D19, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(44):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E4,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(45):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E8,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(46):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E17, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(47):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F6,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(48):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F8,  8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(49):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F11, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(50):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F17, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(51):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H12, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(52):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H13, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(53):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H14, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(54):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H15, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(55):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H20, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(56):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H21, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(57):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H22, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(58):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H23, 8, PadFunction);
      case GPIO_FUNCTION_PSE_TGPIO(59):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T7,  8, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(0):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A0,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(1):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A1,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(2):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A2,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(3):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A3,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(4):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A4,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(5):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A5,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(6):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A6,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(7):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(8):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A8,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(9):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A9,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(10):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A10, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(11):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A23, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(12):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C3,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(13):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C4,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(14):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T4,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(15):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T5,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(16):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T6,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE0(17):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_T7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(0):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A11, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(1):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A12, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(2):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A13, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(3):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A14, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(4):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A15, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(5):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A16, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(6):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(7):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A18, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(8):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A19, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(9):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A20, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(10):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A21, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(11):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_A22, 1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(12):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C6,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(13):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_C7,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(14):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H0,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(15):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H1,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(16):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H2,  1, PadFunction);
      case GPIO_FUNCTION_PSE_GBE1(17):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H3,  1, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(0):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F11, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(1):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F12, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(2):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F13, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(3):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F14, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(4):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F15, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(5):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F16, 4, PadFunction);
      case GPIO_FUNCTION_PSE_JTAG(6):             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F17, 4, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                 return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:               return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:               return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E14, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E3,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H20, 2, PadFunction);
      case GPIO_FUNCTION_PANEL_VIO_EN(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E17, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_RESET(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E3,  1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_L_VDDEN, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER3_L_BKLTEN,1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER3_L_BKLTCTL,1, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_E17, 2, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F5,  3, PadFunction);
      case GPIO_FUNCTION_SD_PWR_EN_B:             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_H17,  1, PadFunction);
      case GPIO_FUNCTION_SD_CMD:                  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G0,  1, PadFunction);
      case GPIO_FUNCTION_SD_DATA(0):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G1,  1, PadFunction);
      case GPIO_FUNCTION_SD_DATA(1):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G2,  1, PadFunction);
      case GPIO_FUNCTION_SD_DATA(2):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G3,  1, PadFunction);
      case GPIO_FUNCTION_SD_DATA(3):              return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G4,  1, PadFunction);
      case GPIO_FUNCTION_SD_CDB:                  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G5,  1, PadFunction);
      case GPIO_FUNCTION_SD_CLK:                  return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G6,  1, PadFunction);
      case GPIO_FUNCTION_SD_WP:                   return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_G23,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_CMD:                return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V0,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V1,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V2,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(2):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V3,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(3):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V4,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(4):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V5,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(5):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V6,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(6):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V7,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_DATA(7):            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V8,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_RCLK:               return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V9,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_CLK:                return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V10,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_RESETB:             return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_V11,  1, PadFunction);
      case GPIO_FUNCTION_EMMC_HIP_MON:            return GPIO_NATIVE_PAD_DEF (GPIO_VER3_GPP_F5,  1, PadFunction);
      default: break;
    }
  }
  return GPIO_PAD_NONE;
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
  return GPIO_VER3_VGPIO39;
}

//
// GPIO pins for HD Audio SSPx/I2Sx interface [SSP number][pin: SCLK/SFRM/TXD/RXD]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { // SSP0/I2S0
    {GPIO_VER3_GPP_R0,  GpioPadModeNative2},// I2S0_SCLK
    {GPIO_VER3_GPP_R1,  GpioPadModeNative2},// I2S0_SFRM
    {GPIO_VER3_GPP_R2,  GpioPadModeNative2},// I2S0_TXD
    {GPIO_VER3_GPP_R3,  GpioPadModeNative2} // I2S0_RXD
  },
  { // SSP1/I2S1
    {GPIO_VER3_GPP_G19, GpioPadModeNative1},// I2S1_SCLK
    {GPIO_VER3_GPP_R7,  GpioPadModeNative2},// I2S1_SFRM
    {GPIO_VER3_GPP_R6,  GpioPadModeNative2},// I2S1_TXD
    {GPIO_VER3_GPP_R5,  GpioPadModeNative2} // I2S1_RXD
  },
  { // SSP2/I2S2
    {GPIO_VER3_GPP_G7,  GpioPadModeNative1},// I2S2_SCLK
    {GPIO_VER3_GPP_G8,  GpioPadModeNative1},// I2S2_SFRM
    {GPIO_VER3_GPP_G9,  GpioPadModeNative1},// I2S2_TXD
    {GPIO_VER3_GPP_G10, GpioPadModeNative1} // I2S2_RXD
  },
  { // SSP3/I2S3
    {GPIO_VER3_GPP_G11, GpioPadModeNative1},// I2S3_SCLK
    {GPIO_VER3_GPP_G12, GpioPadModeNative1},// I2S3_SFRM
    {GPIO_VER3_GPP_G13, GpioPadModeNative1},// I2S3_TXD
    {GPIO_VER3_GPP_G14, GpioPadModeNative1} // I2S3_RXD
  },
  { // SSP4/I2S4
    {GPIO_VER3_GPP_F16, GpioPadModeNative2},// I2S4_SCLK
    {GPIO_VER3_GPP_F13, GpioPadModeNative2},// I2S4_SFRM
    {GPIO_VER3_GPP_F12, GpioPadModeNative2},// I2S4_TXD
    {GPIO_VER3_GPP_F14, GpioPadModeNative2} // I2S4_RXD
  },
  { // SSP5/I2S5
    {GPIO_VER3_GPP_A19, GpioPadModeNative2},// I2S5_SCLK
    {GPIO_VER3_GPP_A20, GpioPadModeNative2},// I2S5_SFRM
    {GPIO_VER3_GPP_A21, GpioPadModeNative2},// I2S5_TXD
    {GPIO_VER3_GPP_A22, GpioPadModeNative2} // I2S5_RXD
  }
};

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
    if (SspInterfaceNumber < ARRAY_SIZE (mPchLpHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchLpHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// GPIO Pin for HD Audio SSP_MCLK/I2S_MCLK
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspMasterClockGpio[] =
{
    {GPIO_VER3_GPP_D19, GpioPadModeNative1}, // I2S_MCLK1_OUT
    {GPIO_VER3_GPP_F8,  GpioPadModeNative1}  // I2S_MCLK2_INOUT
};

/**
  This function sets HDA SSP Master Clock into native mode

  @param[in]  MclkIndex       MCLK index

  @retval Status
**/
EFI_STATUS
GpioEnableHdaSspMasterClock (
  IN UINT32  MclkIndex
  )
{
    if (MclkIndex < ARRAY_SIZE (mPchLpHdaSspMasterClockGpio)) {
      return GpioSetPadMode (mPchLpHdaSspMasterClockGpio[MclkIndex].Pad, mPchLpHdaSspMasterClockGpio[MclkIndex].Mode);
    }

  return EFI_UNSUPPORTED;
}

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
  *NativePinsTable = NULL;
  return;
}

//
// GPIO SPI IO pins for Touch Host Controller [SPI1 or SPI2][pin: IO_0/IO_1/IO_2/IO_3]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpThcSpiGpioIo[][4] =
{
  {
    {GPIO_VER3_GPP_E13, GpioPadModeNative2}, // SPI1_IO_0
    {GPIO_VER3_GPP_E12, GpioPadModeNative2}, // SPI1_IO_1
    {GPIO_VER3_GPP_E1,  GpioPadModeNative2}, // SPI1_IO_2
    {GPIO_VER3_GPP_E2,  GpioPadModeNative2}  // SPI1_IO_3
  },
  {
    {GPIO_VER3_GPP_F12, GpioPadModeNative3}, // SPI2_IO_0
    {GPIO_VER3_GPP_F13, GpioPadModeNative3}, // SPI2_IO_1
    {GPIO_VER3_GPP_F14, GpioPadModeNative3}, // SPI2_IO_2
    {GPIO_VER3_GPP_F15, GpioPadModeNative3}  // SPI2_IO_3
  }
};

/**
  This function provides SPI IO pin for Touch Host Controller

  @param[in]  SpiIndex                  SPI1 or SPI2 - 0 or 1
  @param[in]  IoIndex                   IoIndex Valid from 0 (SPI_IO_0) to 3 (SPI_IO_3)

  @retval     NativePin                 Native Pin Configuration, 0 if SpiIndex or IoIndex is invalid
**/
GPIO_PAD_NATIVE_FUNCTION
GpioGetThcSpiIo (
  IN  UINT32                      SpiIndex,
  IN  UINT32                      IoIndex
  )
{
    if (SpiIndex < ARRAY_SIZE (mPchLpThcSpiGpioIo) && IoIndex < ARRAY_SIZE (mPchLpThcSpiGpioIo[SpiIndex])) {
      return mPchLpThcSpiGpioIo[SpiIndex][IoIndex];
    }

  ASSERT (FALSE);
  return (GPIO_PAD_NATIVE_FUNCTION){0};
}

/**
  This function provides SPI ChipSelect pin for Touch Host Controller

  @param[in]  SpiIndex                  SPI1 or SPI2 - 0 or 1

  @retval     NativePin                 Native Pin Configuration, 0 if SpiIndex is invalid
**/
GPIO_PAD_NATIVE_FUNCTION
GpioGetThcSpiCs (
  IN  UINT32                      SpiIndex
  )
{
  if (SpiIndex == 0) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_E10, GpioPadModeNative2}; // SPI1_CSB
  } else if (SpiIndex == 1) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_F16, GpioPadModeNative3}; // SPI2_CSB
  }

  ASSERT (FALSE);
  return (GPIO_PAD_NATIVE_FUNCTION){0};
}

/**
  This function provides SPI Clock pin for Touch Host Controller

  @param[in]  SpiIndex                  SPI1 or SPI2 - 0 or 1

  @retval     NativePin                 Native Pin Configuration, 0 if SpiIndex is invalid
**/
GPIO_PAD_NATIVE_FUNCTION
GpioGetThcSpiClk (
  IN  UINT32                      SpiIndex
  )
{
  if (SpiIndex == 0) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_E11, GpioPadModeNative2}; // SPI1_CLK
  } else if (SpiIndex == 1) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_F11, GpioPadModeNative3}; // SPI2_CLK
  }

  ASSERT (FALSE);
  return (GPIO_PAD_NATIVE_FUNCTION){0};
}

/**
  This function provides SPI Reset pin for Touch Host Controller

  @param[in]  SpiIndex                  SPI1 or SPI2 - 0 or 1

  @retval     NativePin                 Native Pin Configuration, 0 if SpiIndex is invalid
**/
GPIO_PAD_NATIVE_FUNCTION
GpioGetThcSpiReset (
  IN  UINT32                      SpiIndex
  )
{
  if (SpiIndex == 0) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_E6,  GpioPadModeNative2}; // SPI1_RESETB
  } else if (SpiIndex == 1) {
    return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER3_GPP_F17, GpioPadModeNative3}; // SPI2_RESETB
  }

  ASSERT (FALSE);
  return (GPIO_PAD_NATIVE_FUNCTION){0};
}

//
// GPIO pins for SMBUS
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_VER3_GPP_C0, GpioPadModeNative1},// SMB_CLK
  {GPIO_VER3_GPP_C1, GpioPadModeNative1} // SMB_DATA
};

/**
  This function provides SMBUS interface pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetSmbusPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  )
{
    *NativePinsTable = mPchLpSmbusGpio;
    return;
}

//
// SMBUS Alert pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusAlertGpio = {GPIO_VER3_GPP_C2,  GpioPadModeNative2};

/**
  This function sets SMBUS ALERT pin into native mode

  @retval Status
**/
EFI_STATUS
GpioEnableSmbusAlert (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION SmbusAlertGpio;

    SmbusAlertGpio = mPchLpSmbusAlertGpio;

  return GpioSetPadMode (SmbusAlertGpio.Pad, SmbusAlertGpio.Mode);
}

//
// SATADevSlpPin to GPIO pin mapping
// SATA_DEVSLP_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataDevSlpPinToGpioMap[] =
{
  {GPIO_VER3_GPP_E4,  GpioPadModeNative1}, // SATA_DEVSLP_0
  {GPIO_VER3_GPP_E8,  GpioPadModeNative2}  // SATA_DEVSLP_1
};

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
    if (SataPort < ARRAY_SIZE (mPchLpSataDevSlpPinToGpioMap)) {
      *NativePin = mPchLpSataDevSlpPinToGpioMap[SataPort];
      return;
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
  {GPIO_VER3_GPP_E0,  GpioPadModeNative7}, // SATAGP_0
  {GPIO_VER3_GPP_G12, GpioPadModeNative2}  // SATAGP_1
};

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

    if (SataPort < ARRAY_SIZE (mPchLpSataGpToGpioMap)) {
      *NativePin = mPchLpSataGpToGpioMap[SataPort];
      return;
    }

  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// SATA LED pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataLedGpio = {GPIO_VER3_GPP_E0, GpioPadModeNative1};

/**
  This function sets SATA LED pin into native mode. SATA LED indicates
  SATA controller activity

  @param[in]  SataCtrlIndex       SATA controller index
  @retval     Status
**/
EFI_STATUS
GpioEnableSataLed (
  IN  UINT32                    SataCtrlIndex
  )
{
  GPIO_PAD_NATIVE_FUNCTION  SataLedGpio;

  if (IsPchLp ()) {
    SataLedGpio = mPchLpSataLedGpio;
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
  {GPIO_VER3_GPP_E9,  GpioPadModeNative1},// USB_OC_0
  {GPIO_VER3_GPP_T6, GpioPadModeNative2},// USB_OC_1
  {GPIO_VER3_GPP_T8, GpioPadModeNative1},// USB_OC_2
  {GPIO_VER3_GPP_T11, GpioPadModeNative1} // USB_OC_3
};

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

    if (OcPinNumber >= ARRAY_SIZE (mPchLpUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchLpUsbOcGpioPins[OcPinNumber];

  return GpioSetPadMode (OcGpio.Pad, OcGpio.Mode);
}

//
// GPIO pin for PCIE SRCCLKREQB
// SRCCLKREQB_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_VER3_GPP_D5,  GpioPadModeNative1}, // SRCCLKREQB_0
  {GPIO_VER3_GPP_D6,  GpioPadModeNative1}, // SRCCLKREQB_1
  {GPIO_VER3_GPP_D7,  GpioPadModeNative1}, // SRCCLKREQB_2
  {GPIO_VER3_GPP_D8,  GpioPadModeNative1}, // SRCCLKREQB_3
  {GPIO_VER3_GPP_H10, GpioPadModeNative1}, // SRCCLKREQB_4
  {GPIO_VER3_GPP_H11, GpioPadModeNative3}  // SRCCLKREQB_5
};

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
    if (ClkreqIndex < ARRAY_SIZE (mPchLpPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchLpPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
}

//
// PCHHOTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPchHotbPin = {GPIO_VER3_GPP_B23,  GpioPadModeNative2};

/**
  This function sets PCHHOT pin into native mode

  @retval Status
**/
EFI_STATUS
GpioEnablePchHot (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION PchHotbPin;

    PchHotbPin = mPchLpPchHotbPin;

  return GpioSetPadMode (PchHotbPin.Pad, PchHotbPin.Mode);
}

//
// VRALERTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpVrAlertbPin = {GPIO_VER3_GPP_B2, GpioPadModeNative1};

/**
  This function sets VRALERTB pin into native mode

  @retval Status
**/
EFI_STATUS
GpioEnableVrAlert (
  VOID
  )
{
  GPIO_PAD_NATIVE_FUNCTION  VrAlertGpio;

    VrAlertGpio = mPchLpVrAlertbPin;

  return GpioSetPadMode (VrAlertGpio.Pad, VrAlertGpio.Mode);
}

//
// CPU_C10_GATE pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuC10GatePin = {GPIO_VER3_GPP_H18, GpioPadModeNative1};

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

    CpuC10GateGpio = mPchLpCpuC10GatePin;

  return GpioSetPadMode (CpuC10GateGpio.Pad, CpuC10GateGpio.Mode);
}

//
// CPU GP pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_VER3_GPP_E3, GpioPadModeNative7}, // CPU_GP_0
  {GPIO_VER3_GPP_E7, GpioPadModeNative7}, // CPU_GP_1
  {GPIO_VER3_GPP_B3, GpioPadModeNative1}, // CPU_GP_2
  {GPIO_VER3_GPP_B4, GpioPadModeNative1}  // CPU_GP_3
};

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

    if (CpuGpPinNum >= ARRAY_SIZE (mPchLpCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchLpCpuGpPinMap[CpuGpPinNum];

  return GpioSetPadMode (CpuGpPin.Pad, CpuGpPin.Mode);
}

//
// DDP A/B/C  CTRLCLK and CTRLDATA pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpDdpInterfacePins[][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {// DDPA
    {GPIO_VER3_GPP_E19, GpioPadModeNative1},// DDPA_CTRLCLK
    {GPIO_VER3_GPP_E18, GpioPadModeNative1} // DDPA_CTRLDATA
  },
  {// DDPB
    {GPIO_VER3_GPP_E7, GpioPadModeNative1}, // DDPB_CTRLCLK
    {GPIO_VER3_GPP_E5, GpioPadModeNative1}  // DDPB_CTRLDATA
  },
  {// DDPC
    {GPIO_VER3_GPP_H16, GpioPadModeNative2},// DDPC_CTRLCLK
    {GPIO_VER3_GPP_H19, GpioPadModeNative2} // DDPC_CTRLDATA
  }
};

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
    case GpioDdpA:
    case GpioDdpB:
    case GpioDdpC:
      if (IsPchLp ()) {
        DdpInterfaceIndex = (DdpInterface - GpioDdpA);
      } else {
        goto Error;
      }
      break;
    default:
      goto Error;
  }

    if (DdpInterfaceIndex < ARRAY_SIZE (mPchLpDdpInterfacePins)) {
      *NativePinsTable = mPchLpDdpInterfacePins[DdpInterfaceIndex];
      return;
    }
Error:
  *NativePinsTable = NULL;
  ASSERT(FALSE);
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
    return GPIO_VER3_VGPIO5;
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
  ASSERT (FALSE);
  return 0;
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
  ASSERT (FALSE);
  *GpioNativePad = (GPIO_PAD_NATIVE_FUNCTION){0};
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
    return GPIO_VER3_VGPIO4;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

/**
  This function sets TBT_LSx pin into native mode

  @param[in]  TbtLsxDdiPort     TBT_LSx for DDI Port Number

  @retval     Status
**/
EFI_STATUS
GpioEnableTbtLsxInterface (
  IN GPIO_TBT_LSX  TbtLsxDdiPort
  )
{
  ASSERT(FALSE);
  return 0;
}

//
// CNVi Bluetooth UART pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_VER3_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_VER3_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_VER3_VGPIO9  // vCNV_BT_UART_RTS_B
};

//
// vUART for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO18, // vUART0_TXD
  GPIO_VER3_VGPIO19, // vUART0_RXD
  GPIO_VER3_VGPIO20, // vUART0_CTS_B
  GPIO_VER3_VGPIO21  // vUART0_RTS_B
};

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
    case GpioCnviBtUartToPseUart0:
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

/**
  This function provides CNVi BT UART external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtUartExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  ASSERT (FALSE);
  return;
}

//
// CNVi Bluetooth I2S pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_VER3_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_VER3_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_VER3_VGPIO33  // vCNV_BT_I2S_SDI
};

//
// vSSP for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO34, // vSSP2_SCLK
  GPIO_VER3_VGPIO35, // vSSP2_SFRM
  GPIO_VER3_VGPIO36, // vSSP2_TXD
  GPIO_VER3_VGPIO37  // vSSP2_RXD
};

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

/**
  This function provides CNVi BT I2S external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtI2sExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  ASSERT (FALSE);
  return;
}

//
// CNVi MFUART1 pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_VER3_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_VER3_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_VER3_VGPIO13  // vCNV_MFUART1_RTS_B
};

//
// vUART for MFUART1
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER3_VGPIO22, // vOSE_UART0_TXD
  GPIO_VER3_VGPIO23, // vOSE_UART0_RXD
  GPIO_VER3_VGPIO24, // vOSE_UART0_CTS_B
  GPIO_VER3_VGPIO25  // vOSE_UART0_RTS_B
};

/**
  This function provides CNVi MFUART1 pins

  @param[in]  ConnectionType          CNVi MFUART1 connection type
  @param[out] VCnviBtI2sPad           Table with vCNV_MFUART1x pads
  @param[out] VCnviBtI2sPadMode       vCNV_MFUART1x pad mode
  @param[out] VSspForCnviBtPad        Table with vOSE_UART0 pads
  @param[out] VSspForCnviBtPadMode    vOSE_UART0 pad mode
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
    case GpioCnviMfUart1ToPseUart0:
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

/**
  This function provides CNVi MFUART1 external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviMfUart1ExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  )
{
  ASSERT (FALSE);
  return;
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
    return GPIO_VER3_VGPIO0;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

//
// CNVi BRI(Bluetooth Radio Interface) and RGI(Radio Generic Interface) buses from PCH to CRF(Companion RF) module
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS] =
{
  {GPIO_VER3_GPP_F0,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_VER3_GPP_F1,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_VER3_GPP_F2,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_VER3_GPP_F3,  GpioPadModeNative1}  // CNV_RGI_RSP
};

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
  } else {
    ASSERT (FALSE);
    return;
  }
}


GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpImguClkOutGpioPad[] =
{
  {GPIO_VER3_GPP_D4,   GpioPadModeNative3}, // IMGCLKOUT_0
  {GPIO_VER3_GPP_H20,  GpioPadModeNative4}, // IMGCLKOUT_1
  {GPIO_VER3_GPP_H21,  GpioPadModeNative4}, // IMGCLKOUT_2
  {GPIO_VER3_GPP_H22,  GpioPadModeNative4}, // IMGCLKOUT_3
  {GPIO_VER3_GPP_H23,  GpioPadModeNative4}, // IMGCLKOUT_4
  {GPIO_VER3_GPP_D15,  GpioPadModeNative3}  // IMGCLKOUT_5
};

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
  return GPIO_VER3_GPD3;
}

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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpTypeCSbuGpioPad[] =
{
  GPIO_VER3_GPP_E18, // BSSB_LS0_RX
  GPIO_VER3_GPP_E19  // BSSB_LS0_TX
};

/**
  SBU (Sideband use) pins are used as auxiliary signals for Type C connector,
  which are hard-wired to BSSB_LS natively for debug function.
  when USB-C is enabled and debug not needed, disable pins (BSSB) used for debug through TypeC connector,
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

    GpioSbuPadTable = mPchLpTypeCSbuGpioPad;

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

/**
  Get the pins used for VW CLKREQ messages between FIA and GPIO controller.

  @param[in]  PciePortIndex       Index of the CPU PCIe root port
  @param[out] VwBusPinsTable      Pointer to table describing VW bus GPIO pins
  @param[out] NoOfNativePins      Size of the table with VW bus GPIO pins

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_UNSUPPORTED         Current GPIO controller doesn't support this functionality
  @retval EFI_INVALID_PARAMETER   Invalid group or parameter
**/
EFI_STATUS
GpioGetCpuPcieVwMsgBusPins (
  IN  UINT32                    PciePortIndex,
  OUT GPIO_PAD_NATIVE_FUNCTION  **VwBusPinsTable,
  OUT UINT32                    *NoOfNativePins
  )
{
  *VwBusPinsTable = NULL;
  *NoOfNativePins = 0;

  if (*VwBusPinsTable != NULL) {
    return EFI_SUCCESS;
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

//
// Pch Pmc Timed GPIO pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchTimeSyncToGpioMap[] =
{
  {GPIO_VER3_GPP_H19,  GpioPadModeNative4}, // TIME_SYNC_0
  {GPIO_VER3_GPP_B14,  GpioPadModeNative2}  // TIME_SYNC_1
};

/**
  This function sets Time Sync Gpio into native mode

  @param[in]  Index       index

  @retval Status
**/
EFI_STATUS
GpioEnableTimeSync (
  IN UINT32  Index
  )
{
  EFI_STATUS          Status;

  if (Index >= (sizeof (mPchTimeSyncToGpioMap) / sizeof (mPchTimeSyncToGpioMap[0]))) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status = GpioSetPadMode (mPchTimeSyncToGpioMap[Index].Pad, mPchTimeSyncToGpioMap[Index].Mode);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

//
// Pch Tsn pin mapping
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpTsnMap[] =
{
  {GPIO_VER3_GPP_C16, GpioPadModeNative1},   // RGMII2_MDIO
  {GPIO_VER3_GPP_C17, GpioPadModeNative1},   // RGMII2_MDC
  {GPIO_VER3_GPP_U0,  GpioPadModeNative1},   // RGMII2_INT
  {GPIO_VER3_GPP_U1,  GpioPadModeGpio},      // RGMII2_RESETB
  {GPIO_VER3_GPP_U2,  GpioPadModeNative1},   // RGMII2_PPS
  {GPIO_VER3_GPP_U3,  GpioPadModeNative1}    // RGMII2_AUXTS
};

/**
  This function sets Pch Tsn Gpio into native mode

  @retval Status
**/
EFI_STATUS
GpioEnablePchTsn (
  VOID
  )
{
  EFI_STATUS          Status;
  UINT32              Index;

  if (IsPchLp ()) {
    for (Index = 0; Index < ARRAY_SIZE (mPchLpTsnMap); Index++) {
      Status = GpioSetPadMode (mPchLpTsnMap[Index].Pad, mPchLpTsnMap[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  }
  return EFI_SUCCESS;
}

//
// Pse Tsn0/1 Gpio pin mapping
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPseTsnMap[][6] =
{
  {
    {GPIO_VER3_GPP_C3,  GpioPadModeNative1},   // RGMII0_MDC
    {GPIO_VER3_GPP_C4,  GpioPadModeNative1},   // RGMII0_MDIO
    {GPIO_VER3_GPP_T4,  GpioPadModeNative1},   // RGMII0_INT
    {GPIO_VER3_GPP_T5,  GpioPadModeNative1},   // RGMII0_RESETB
    {GPIO_VER3_GPP_T6,  GpioPadModeNative1},   // RGMII0_AUXTS
    {GPIO_VER3_GPP_T7,  GpioPadModeNative1},   // RGMII0_PPS
  },
  {
    {GPIO_VER3_GPP_C6,  GpioPadModeNative1},   // RGMII1_MDC
    {GPIO_VER3_GPP_C7,  GpioPadModeNative1},   // RGMII1_MDIO
    {GPIO_VER3_GPP_H0,  GpioPadModeNative1},   // RGMII1_INT
    {GPIO_VER3_GPP_H1,  GpioPadModeNative1},   // RGMII1_RESETB
    {GPIO_VER3_GPP_H2,  GpioPadModeNative1},   // RGMII1_AUXTS
    {GPIO_VER3_GPP_H3,  GpioPadModeNative1}    // RGMII1_PPS
  }
};

/**
  This function sets Pse Tsn Gpio into native mode

  @retval Status
**/
EFI_STATUS
GpioEnablePseTsn (
  IN UINT32       PseTsnIndex
  )
{
  EFI_STATUS          Status;
  UINT32              Index;

  if (IsPchLp ()) {
    for (Index = 0; Index < ARRAY_SIZE (mPseTsnMap[PseTsnIndex]); Index++) {
      Status = GpioSetPadMode (mPseTsnMap[PseTsnIndex][Index].Pad, mPseTsnMap[PseTsnIndex][Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  }
  return EFI_SUCCESS;
}

//
// Sci pin mapping
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mSciMap[] =
{
  {GPIO_VER3_GPP_F11,  GpioPadModeNative5},   // SCI_TRACECLK
  {GPIO_VER3_GPP_F12,  GpioPadModeNative5},   // SCI_TRACESWO
  {GPIO_VER3_GPP_F13,  GpioPadModeNative5},   // SCI_SWDIO
  {GPIO_VER3_GPP_F14,  GpioPadModeNative5},   // SCI_TRACEDATA_1
  {GPIO_VER3_GPP_F15,  GpioPadModeNative5},   // SCI_TRACEDATA_2
  {GPIO_VER3_GPP_F16,  GpioPadModeNative5},   // SCI_SWCLK
  {GPIO_VER3_GPP_F17,  GpioPadModeNative5}    // SCI_TRACEDATA_3
};

/**
  This function sets Sci Gpio into native mode

  @retval Status
**/
EFI_STATUS
GpioEnableSci (
  VOID
  )
{
  EFI_STATUS          Status;
  UINT32              Index;

    for (Index = 0; Index < ARRAY_SIZE (mSciMap); Index++) {
      Status = GpioSetPadMode (mSciMap[Index].Pad, mSciMap[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  return EFI_SUCCESS;
}

/**
  This function is to be used In GpioLockPads() to override a lock request by SOC code.

  @param[in]  Group               GPIO group
  @param[in]  DwNum               Register number for current group (parameter applicable in accessing whole register).
                                  For group which has less then 32 pads per group DwNum must be 0.
  @param[out] *UnlockCfgPad       DWORD bitmask for pads which are going to be left unlocked
                                  Bit position - PadNumber
                                  Bit value - 0: to be locked, 1: Leave unlocked
  @param[out] *UnlockTxPad        DWORD bitmask for pads which are going to be left unlocked
                                  Bit position - PadNumber
                                  Bit value - 0: to be locked, 1: Leave unlocked

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid input parameter
**/
EFI_STATUS
GpioUnlockOverride (
  IN  GPIO_GROUP  Group,
  IN  UINT32      DwNum,
  OUT UINT32      *UnlockCfgPad,
  OUT UINT32      *UnlockTxPad
  )
{

  if ((UnlockCfgPad == NULL) || (UnlockTxPad == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *UnlockCfgPad = 0;
  *UnlockTxPad = 0;
  return EFI_SUCCESS;
}
