/** @file
  This file contains VER2 specific GPIO information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Pins/GpioPinsVer2Lp.h>
#include <Pins/GpioPinsVer2H.h>
#include <Register/GpioRegs.h>
#include <Register/IshRegs.h>

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
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U0,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U1,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U2,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(4):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(5):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T10, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(6):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U3,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(4):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(5):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T11, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(6):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (2):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D12, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (3):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (4):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U11, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (5):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (6):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (2):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D11, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (3):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (4):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U10, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (5):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (6):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (0):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D10, 7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (4):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (5):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (6):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B14, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B23, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D9,  7, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D15, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (3, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (4, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (5, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (6, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_U16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B10, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T1,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(7):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T3,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_H8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(6):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T0,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(7):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_T2,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(0):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D0,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(1):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D1,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(2):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D2,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(3):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D3,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(4):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D17, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(5):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D18, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(6):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_E15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(7):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_E16, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D13, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D14, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C13, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D16, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_C15, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B6,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B8,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B10, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B5,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_B9,  2, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MOSI(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MISO(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CLK(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CS (0, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_D9,  1, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                 return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(1):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A19, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(2):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A20, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(3):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A14, 2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(4):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A15, 2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_E14, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A18, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_L_VDDEN,   1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_L_BKLTEN,  1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_L_BKLTCTL, 1, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_E17, 2, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPP_F18, 3, PadFunction);
      case GPIO_FUNCTION_THC_CLK_LOOPBACK(0):     return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPPE_CLK_LOOPBK, 1, PadFunction);
      case GPIO_FUNCTION_THC_CLK_LOOPBACK(1):     return GPIO_NATIVE_PAD_DEF (GPIO_VER2_LP_GPPF_CLK_LOOPBK, 3, PadFunction);
      default: break;
    }
  } else {
    switch (PadFunction) {
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (2):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G11, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (3):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (0):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (1):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (2):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G10, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (3):  return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (0):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (1):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (2):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G9,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (3):   return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B0,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_B1,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G8,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 1): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_A11, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (3, 0): return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C4,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C7,  2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I12, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I14, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C3,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(4):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I11, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(5):    return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I13, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(0):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R14, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(1):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(2):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R16, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(3):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R17, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(4):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R18, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(5):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R19, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(6):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R11, 2, PadFunction);
      case GPIO_FUNCTION_ISH_GP(7):               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R13, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C3,  1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C4,  1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C13, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_A11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C15, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_H20, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_H22, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_H19, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_H21, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(2):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_C6,  1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MOSI(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MISO(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CLK(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G9,  1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CS (0, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_G8,  1, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                 return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:               return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(1):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I1,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(2):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I2,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(3):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I3,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(4):             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_I4,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_K6,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_K7,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_K10, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_F19, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):         return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_F20, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):        return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_F21, 1, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(0):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D8,  2, PadFunction);
      case GPIO_FUNCTION_THC_SPI_INT(1):          return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D23, 2, PadFunction);
      case GPIO_FUNCTION_CNVI_RF_RESET:           return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D5,  2, PadFunction);
      case GPIO_FUNCTION_CNVI_CLKREQ:             return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_D6,  3, PadFunction);
      case GPIO_FUNCTION_DMIC_CLKA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S6,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLKA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S4,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLKB(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S2,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLKB(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S3,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S7,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_VER2_H_GPP_S5,  2, PadFunction);
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
  ASSERT (FALSE);
  return 0;
}

//
// GPIO pins for HD Audio SSPx/I2Sx interface [SSP number][pin: SCLK/SFRM/TXD/RXD]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { // SSP0/I2S0
    {GPIO_VER2_LP_GPP_R0,  GpioPadModeNative2},// I2S0_SCLK
    {GPIO_VER2_LP_GPP_R1,  GpioPadModeNative2},// I2S0_SFRM
    {GPIO_VER2_LP_GPP_R2,  GpioPadModeNative2},// I2S0_TXD
    {GPIO_VER2_LP_GPP_R3,  GpioPadModeNative2} // I2S0_RXD
  },
  { // SSP1/I2S1
    {GPIO_VER2_LP_GPP_A23, GpioPadModeNative1},// I2S1_SCLK
    {GPIO_VER2_LP_GPP_R5,  GpioPadModeNative2},// I2S1_SFRM
    {GPIO_VER2_LP_GPP_R6,  GpioPadModeNative2},// I2S1_TXD
    {GPIO_VER2_LP_GPP_R7,  GpioPadModeNative2} // I2S1_RXD
  },
  { // SSP2/I2S2
    {GPIO_VER2_LP_GPP_A7,  GpioPadModeNative1},// I2S2_SCLK
    {GPIO_VER2_LP_GPP_A8,  GpioPadModeNative1},// I2S2_SFRM
    {GPIO_VER2_LP_GPP_A9,  GpioPadModeNative1},// I2S2_TXD
    {GPIO_VER2_LP_GPP_A10, GpioPadModeNative1} // I2S2_RXD
  },
  { // SSP3/I2S3
    {GPIO_VER2_LP_GPP_A11, GpioPadModeNative3},// I2S3_SCLK
    {GPIO_VER2_LP_GPP_A12, GpioPadModeNative3},// I2S3_SFRM
    {GPIO_VER2_LP_GPP_A13, GpioPadModeNative3},// I2S3_TXD
    {GPIO_VER2_LP_GPP_A14, GpioPadModeNative3} // I2S3_RXD
  },
  { // SSP4/I2S4
    {GPIO_VER2_LP_GPP_A15, GpioPadModeNative3},// I2S4_SCLK
    {GPIO_VER2_LP_GPP_A16, GpioPadModeNative3},// I2S4_SFRM
    {GPIO_VER2_LP_GPP_A17, GpioPadModeNative3},// I2S4_TXD
    {GPIO_VER2_LP_GPP_A18, GpioPadModeNative3} // I2S4_RXD
  },
  { // SSP5/I2S5
    {GPIO_VER2_LP_GPP_A19, GpioPadModeNative3},// I2S5_SCLK
    {GPIO_VER2_LP_GPP_A20, GpioPadModeNative3},// I2S5_SFRM
    {GPIO_VER2_LP_GPP_A21, GpioPadModeNative3},// I2S5_TXD
    {GPIO_VER2_LP_GPP_A22, GpioPadModeNative3} // I2S5_RXD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { // SSP0/I2S0
    {GPIO_VER2_H_GPP_R0,  GpioPadModeNative2},// I2S0_SCLK
    {GPIO_VER2_H_GPP_R1,  GpioPadModeNative2},// I2S0_SFRM
    {GPIO_VER2_H_GPP_R2,  GpioPadModeNative2},// I2S0_TXD
    {GPIO_VER2_H_GPP_R3,  GpioPadModeNative2} // I2S0_RXD
  },
  { // SSP1/I2S1
    {GPIO_VER2_H_GPP_D11, GpioPadModeNative1},// I2S1_SCLK
    {GPIO_VER2_H_GPP_R7,  GpioPadModeNative2},// I2S1_SFRM
    {GPIO_VER2_H_GPP_R6,  GpioPadModeNative2},// I2S1_TXD
    {GPIO_VER2_H_GPP_R5,  GpioPadModeNative2} // I2S1_RXD
  },
  { // SSP2/I2S2
    {GPIO_VER2_H_GPP_D8,  GpioPadModeNative1},// I2S2_SCLK
    {GPIO_VER2_H_GPP_D5,  GpioPadModeNative1},// I2S2_SFRM
    {GPIO_VER2_H_GPP_D6,  GpioPadModeNative1},// I2S2_TXD
    {GPIO_VER2_H_GPP_D7,  GpioPadModeNative1} // I2S2_RXD
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
  if (IsPchLp ()) {
    if (SspInterfaceNumber < ARRAY_SIZE (mPchLpHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchLpHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  } else if (IsPchH ()) {
    if (SspInterfaceNumber < ARRAY_SIZE (mPchHHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchHHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// GPIO Pin for HD Audio SSP_MCLK/I2S_MCLK
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspMasterClockGpio[] =
{
    {GPIO_VER2_LP_GPP_D19, GpioPadModeNative1}, // I2S_MCLK1_OUT
    {GPIO_VER2_LP_GPP_F8,  GpioPadModeNative1}  // I2S_MCLK2_INOUT
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSspMasterClockGpio[] =
{
    {GPIO_VER2_H_GPP_B11, GpioPadModeNative1} // I2S_MCLK
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
  if (IsPchLp ()) {
    if (MclkIndex < ARRAY_SIZE (mPchLpHdaSspMasterClockGpio)) {
      return GpioSetPadMode (mPchLpHdaSspMasterClockGpio[MclkIndex].Pad, mPchLpHdaSspMasterClockGpio[MclkIndex].Mode);
    }
  } else if (IsPchH ()) {
    if (MclkIndex < ARRAY_SIZE (mPchHHdaSspMasterClockGpio)) {
      return GpioSetPadMode (mPchHHdaSspMasterClockGpio[MclkIndex].Pad, mPchHHdaSspMasterClockGpio[MclkIndex].Mode);
    }
  }

  return EFI_UNSUPPORTED;
}

//
// GPIO pins for HD Audio SoundWire interface [SNDW number][pin: CLK/DATA]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS] =
{
  { // SNDW1
    {GPIO_VER2_LP_GPP_S0, GpioPadModeNative1},// SNDW1_CLK
    {GPIO_VER2_LP_GPP_S1, GpioPadModeNative1} // SNDW1_DATA
  },
  { // SNDW2
    {GPIO_VER2_LP_GPP_S2, GpioPadModeNative1},// SNDW2_CLK
    {GPIO_VER2_LP_GPP_S3, GpioPadModeNative1} // SNDW2_DATA
  },
  { // SNDW3
    {GPIO_VER2_LP_GPP_S4, GpioPadModeNative1},// SNDW3_CLK
    {GPIO_VER2_LP_GPP_S5, GpioPadModeNative1} // SNDW3_DATA
  },
  { // SNDW4
    {GPIO_VER2_LP_GPP_S6, GpioPadModeNative1},// SNDW4_CLK
    {GPIO_VER2_LP_GPP_S7, GpioPadModeNative1} // SNDW4_DATA
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS] =
{
  { // SNDW1
    {GPIO_VER2_H_GPP_S0, GpioPadModeNative1},// SNDW1_CLK
    {GPIO_VER2_H_GPP_S1, GpioPadModeNative1} // SNDW1_DATA
  },
  { // SNDW2
    {GPIO_VER2_H_GPP_S2, GpioPadModeNative1},// SNDW2_CLK
    {GPIO_VER2_H_GPP_S3, GpioPadModeNative1} // SNDW2_DATA
  },
  { // SNDW3
    {GPIO_VER2_H_GPP_S4, GpioPadModeNative1},// SNDW3_CLK
    {GPIO_VER2_H_GPP_S5, GpioPadModeNative1} // SNDW3_DATA
  },
  { // SNDW4
    {GPIO_VER2_H_GPP_S6, GpioPadModeNative1},// SNDW4_CLK
    {GPIO_VER2_H_GPP_S7, GpioPadModeNative1} // SNDW4_DATA
  }
};

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
  } else if (IsPchH ()) {
    if (SndwInterfaceNumber < ARRAY_SIZE (mPchHHdaSndwGpio)) {
      *NativePinsTable = mPchHHdaSndwGpio[SndwInterfaceNumber];
      return;
    }
  }
  *NativePinsTable = NULL;
  ASSERT (FALSE);
}

//
// GPIO SPI IO pins for Touch Host Controller [SPI1 or SPI2][pin: IO_0/IO_1/IO_2/IO_3]
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpThcSpiGpioIo[][4] =
{
  {
    {GPIO_VER2_LP_GPP_E13, GpioPadModeNative2}, // SPI1_IO_0
    {GPIO_VER2_LP_GPP_E12, GpioPadModeNative2}, // SPI1_IO_1
    {GPIO_VER2_LP_GPP_E1,  GpioPadModeNative2}, // SPI1_IO_2
    {GPIO_VER2_LP_GPP_E2,  GpioPadModeNative2}  // SPI1_IO_3
  },
  {
    {GPIO_VER2_LP_GPP_F12, GpioPadModeNative3}, // SPI2_IO_0
    {GPIO_VER2_LP_GPP_F13, GpioPadModeNative3}, // SPI2_IO_1
    {GPIO_VER2_LP_GPP_F14, GpioPadModeNative3}, // SPI2_IO_2
    {GPIO_VER2_LP_GPP_F15, GpioPadModeNative3}  // SPI2_IO_3
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHThcSpiGpioIo[][4] =
{
  {
    {GPIO_VER2_H_GPP_D3,  GpioPadModeNative2}, // SPI1_IO_0
    {GPIO_VER2_H_GPP_D2,  GpioPadModeNative2}, // SPI1_IO_1
    {GPIO_VER2_H_GPP_D13, GpioPadModeNative2}, // SPI1_IO_2
    {GPIO_VER2_H_GPP_D14, GpioPadModeNative2}  // SPI1_IO_3
  },
  {
    {GPIO_VER2_H_GPP_D17, GpioPadModeNative2}, // SPI2_IO_0
    {GPIO_VER2_H_GPP_D18, GpioPadModeNative2}, // SPI2_IO_1
    {GPIO_VER2_H_GPP_D19, GpioPadModeNative2}, // SPI2_IO_2
    {GPIO_VER2_H_GPP_D20, GpioPadModeNative2}  // SPI2_IO_3
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
  if (IsPchLp ()) {
    if (SpiIndex < ARRAY_SIZE (mPchLpThcSpiGpioIo) && IoIndex < ARRAY_SIZE (mPchLpThcSpiGpioIo[SpiIndex])) {
      return mPchLpThcSpiGpioIo[SpiIndex][IoIndex];
    }
  } else if (IsPchH ()) {
    if (SpiIndex < ARRAY_SIZE (mPchHThcSpiGpioIo) && IoIndex < ARRAY_SIZE (mPchHThcSpiGpioIo[SpiIndex])) {
      return mPchHThcSpiGpioIo[SpiIndex][IoIndex];
    }
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
  if (IsPchLp ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_E10, GpioPadModeNative2}; // SPI1_CSB
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_F16, GpioPadModeNative3}; // SPI2_CSB
    }
  } else if (IsPchH ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D0,  GpioPadModeNative2}; // SPI1_CSB
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D21, GpioPadModeNative2}; // SPI2_CSB
    }
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
  if (IsPchLp ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_E11, GpioPadModeNative2}; // SPI1_CLK
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_F11, GpioPadModeNative3}; // SPI2_CLK
    }
  } else if (IsPchH ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D1,  GpioPadModeNative2}; // SPI1_CLK
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D16, GpioPadModeNative2}; // SPI2_CLK
    }
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
  if (IsPchLp ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_E6,  GpioPadModeNative2}; // SPI1_RESETB
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_LP_GPP_F17, GpioPadModeNative3}; // SPI2_RESETB
    }
  } else if (IsPchH ()) {
    if (SpiIndex == 0) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D7,  GpioPadModeNative2}; // SPI1_RESETB
    } else if (SpiIndex == 1) {
      return (GPIO_PAD_NATIVE_FUNCTION) {GPIO_VER2_H_GPP_D22, GpioPadModeNative2}; // SPI2_RESETB
    }
  }

  ASSERT (FALSE);
  return (GPIO_PAD_NATIVE_FUNCTION){0};
}

//
// GPIO pins for SMBUS
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_VER2_LP_GPP_C0, GpioPadModeNative1},// SMB_CLK
  {GPIO_VER2_LP_GPP_C1, GpioPadModeNative1} // SMB_DATA
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_VER2_H_GPP_C0, GpioPadModeNative1},// SMB_CLK
  {GPIO_VER2_H_GPP_C1, GpioPadModeNative1} // SMB_DATA
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
  if (IsPchLp ()) {
    *NativePinsTable = mPchLpSmbusGpio;
    return;
  } else {
    *NativePinsTable = mPchHSmbusGpio;
    return;
  }
}

//
// SMBUS Alert pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSmbusAlertGpio = {GPIO_VER2_LP_GPP_C2,  GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusAlertGpio = {GPIO_VER2_H_GPP_C2,  GpioPadModeNative1};

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

  if (IsPchLp ()) {
    SmbusAlertGpio = mPchLpSmbusAlertGpio;
  } else {
    SmbusAlertGpio = mPchHSmbusAlertGpio;
  }

  return GpioSetPadMode (SmbusAlertGpio.Pad, SmbusAlertGpio.Mode);
}

//
// SATADevSlpPin to GPIO pin mapping
// SATA_DEVSLP_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataDevSlpPinToGpioMap[] =
{
  {GPIO_VER2_LP_GPP_E4,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_E5,  GpioPadModeNative1}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataDevSlpPinToGpioMap[] =
{
  {GPIO_VER2_H_GPP_E4,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_E5,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_E6,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_F5,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_F6,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_F7,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_F8,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_F9,  GpioPadModeNative1}
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
  if (IsPchLp ()) {
    if (SataPort < ARRAY_SIZE (mPchLpSataDevSlpPinToGpioMap)) {
      *NativePin = mPchLpSataDevSlpPinToGpioMap[SataPort];
      return;
    }
  } else if (IsPchH ()) {
    if (SataPort < ARRAY_SIZE (mPchHSataDevSlpPinToGpioMap)) {
      *NativePin = mPchHSataDevSlpPinToGpioMap[SataPort];
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
  {GPIO_VER2_LP_GPP_E0,  GpioPadModeNative2},
  {GPIO_VER2_LP_GPP_A12, GpioPadModeNative2}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataGpToGpioMap[] =
{
  {GPIO_VER2_H_GPP_E0,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_E1,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_E2,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_F0,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_F1,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_F2,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_F3,  GpioPadModeNative2},
  {GPIO_VER2_H_GPP_F4,  GpioPadModeNative2}
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
  if (IsPchLp ()) {
    if (SataPort < ARRAY_SIZE (mPchLpSataGpToGpioMap)) {
      *NativePin = mPchLpSataGpToGpioMap[SataPort];
      return;
    }
  } else if (IsPchH ()) {
    if (SataPort < ARRAY_SIZE (mPchHSataGpToGpioMap)) {
      *NativePin = mPchHSataGpToGpioMap[SataPort];
      return;
    }
  }
  *NativePin = (GPIO_PAD_NATIVE_FUNCTION){0};
  ASSERT (FALSE);
}

//
// SATA LED pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataLedGpio = {GPIO_VER2_LP_GPP_E8, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataLedGpio = {GPIO_VER2_H_GPP_E8, GpioPadModeNative1};

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
  } else if (IsPchH ()) {
    SataLedGpio = mPchHSataLedGpio;
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
  {GPIO_VER2_LP_GPP_E9,  GpioPadModeNative1},// USB_OC_0
  {GPIO_VER2_LP_GPP_A14, GpioPadModeNative1},// USB_OC_1
  {GPIO_VER2_LP_GPP_A15, GpioPadModeNative1},// USB_OC_2
  {GPIO_VER2_LP_GPP_A16, GpioPadModeNative1} // USB_OC_3
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHUsbOcGpioPins[] =
{
  {GPIO_VER2_H_GPP_E9,  GpioPadModeNative1},// USB_OC_0
  {GPIO_VER2_H_GPP_E10, GpioPadModeNative1},// USB_OC_1
  {GPIO_VER2_H_GPP_E11, GpioPadModeNative1},// USB_OC_2
  {GPIO_VER2_H_GPP_E12, GpioPadModeNative1},// USB_OC_3
  {GPIO_VER2_H_GPP_I11, GpioPadModeNative1},// USB_OC_4
  {GPIO_VER2_H_GPP_I12, GpioPadModeNative1},// USB_OC_5
  {GPIO_VER2_H_GPP_I13, GpioPadModeNative1},// USB_OC_6
  {GPIO_VER2_H_GPP_I14, GpioPadModeNative1} // USB_OC_7
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

  if (IsPchLp ()) {
    if (OcPinNumber >= ARRAY_SIZE (mPchLpUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchLpUsbOcGpioPins[OcPinNumber];
  } else {
    if (OcPinNumber >= ARRAY_SIZE (mPchHUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchHUsbOcGpioPins[OcPinNumber];
  }

  return GpioSetPadMode (OcGpio.Pad, OcGpio.Mode);
}

//
// GPIO pin for PCIE SRCCLKREQB
// SRCCLKREQB_x -> GPIO pin y
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_VER2_LP_GPP_D5,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_D6,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_D7,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_D8,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_H10, GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_H11, GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_F19, GpioPadModeNative1}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_VER2_H_GPP_B5,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_B6,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_B7,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_B8,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_B9,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_B10, GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H0,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H1,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H2,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H3,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H4,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H5,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H6,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H7,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H8,  GpioPadModeNative1},
  {GPIO_VER2_H_GPP_H9,  GpioPadModeNative1}
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
  if (IsPchLp ()) {
    if (ClkreqIndex < ARRAY_SIZE (mPchLpPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchLpPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
  } else {
    if (ClkreqIndex < ARRAY_SIZE (mPchHPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchHPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
  }
}

//
// PCHHOTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpPchHotbPin = {GPIO_VER2_LP_GPP_B23,  GpioPadModeNative2};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPchHotbPin = {GPIO_VER2_H_GPP_B23,  GpioPadModeNative2};

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

  if (IsPchLp ()) {
    PchHotbPin = mPchLpPchHotbPin;
  } else {
    PchHotbPin = mPchHPchHotbPin;
  }

  return GpioSetPadMode (PchHotbPin.Pad, PchHotbPin.Mode);
}

//
// VRALERTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpVrAlertbPin = {GPIO_VER2_LP_GPP_B2, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHVrAlertbPin = {GPIO_VER2_H_GPP_B2, GpioPadModeNative1};

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

  if (IsPchLp ()) {
    VrAlertGpio = mPchLpVrAlertbPin;
  } else {
    VrAlertGpio = mPchHVrAlertbPin;
  }

  return GpioSetPadMode (VrAlertGpio.Pad, VrAlertGpio.Mode);
}

//
// CPU_C10_GATE pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuC10GatePin = {GPIO_VER2_LP_GPP_H18, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuC10GatePin = {GPIO_VER2_H_GPP_J1, GpioPadModeNative1};

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
  } else {
    CpuC10GateGpio = mPchHCpuC10GatePin;
  }

  return GpioSetPadMode (CpuC10GateGpio.Pad, CpuC10GateGpio.Mode);
}

//
// CPU GP pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_VER2_LP_GPP_E3, GpioPadModeNative1}, // CPU_GP_0
  {GPIO_VER2_LP_GPP_E7, GpioPadModeNative1}, // CPU_GP_1
  {GPIO_VER2_LP_GPP_B3, GpioPadModeNative1}, // CPU_GP_2
  {GPIO_VER2_LP_GPP_B4, GpioPadModeNative1}  // CPU_GP_3
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_VER2_H_GPP_E3, GpioPadModeNative1}, // CPU_GP_0
  {GPIO_VER2_H_GPP_E7, GpioPadModeNative1}, // CPU_GP_1
  {GPIO_VER2_H_GPP_B3, GpioPadModeNative1}, // CPU_GP_2
  {GPIO_VER2_H_GPP_B4, GpioPadModeNative1}  // CPU_GP_3
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

  if (IsPchLp ()) {
    if (CpuGpPinNum >= ARRAY_SIZE (mPchLpCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchLpCpuGpPinMap[CpuGpPinNum];
  } else {
    if (CpuGpPinNum >= ARRAY_SIZE (mPchHCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchHCpuGpPinMap[CpuGpPinNum];
  }

  return GpioSetPadMode (CpuGpPin.Pad, CpuGpPin.Mode);
}

//
// DDP1/2/3/4/A/B/C  CTRLCLK and CTRLDATA pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpDdpInterfacePins[][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {// DDP1
    {GPIO_VER2_LP_GPP_E18, GpioPadModeNative1},// DDP1_CTRLCLK
    {GPIO_VER2_LP_GPP_E19, GpioPadModeNative1} // DDP1_CTRLDATA
  },
  {// DDP2
    {GPIO_VER2_LP_GPP_E20, GpioPadModeNative1},// DDP2_CTRLCLK
    {GPIO_VER2_LP_GPP_E21, GpioPadModeNative1} // DDP2_CTRLDATA
  },
  {// DDP3
    {GPIO_VER2_LP_GPP_D9,  GpioPadModeNative2},// DDP3_CTRLCLK
    {GPIO_VER2_LP_GPP_D10, GpioPadModeNative2} // DDP3_CTRLDATA
  },
  {// DDP4
    {GPIO_VER2_LP_GPP_D11, GpioPadModeNative2},// DDP4_CTRLCLK
    {GPIO_VER2_LP_GPP_D12, GpioPadModeNative2} // DDP4_CTRLDATA
  },
  {// DDPA
    {GPIO_VER2_LP_GPP_E22, GpioPadModeNative1},// DDPA_CTRLCLK
    {GPIO_VER2_LP_GPP_E23, GpioPadModeNative1} // DDPA_CTRLDATA
  },
  {// DDPB
    {GPIO_VER2_LP_GPP_H16, GpioPadModeNative1},// DDPB_CTRLCLK
    {GPIO_VER2_LP_GPP_H17, GpioPadModeNative1} // DDPB_CTRLDATA
  },
  {// DDPC
    {GPIO_VER2_LP_GPP_A21, GpioPadModeNative2},// DDPC_CTRLCLK
    {GPIO_VER2_LP_GPP_A22, GpioPadModeNative2} // DDPC_CTRLDATA
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHDdpInterfacePins[][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {// DDP1
    {GPIO_VER2_H_GPP_G12, GpioPadModeNative1},// DDP1_CTRLCLK
    {GPIO_VER2_H_GPP_G13, GpioPadModeNative1} // DDP1_CTRLDATA
  },
  {// DDP2
    {GPIO_VER2_H_GPP_G14, GpioPadModeNative1},// DDP2_CTRLCLK
    {GPIO_VER2_H_GPP_G15, GpioPadModeNative1} // DDP2_CTRLDATA
  },
  {// DDP3
    {GPIO_VER2_H_GPP_G8,  GpioPadModeNative2},// DDP3_CTRLCLK
    {GPIO_VER2_H_GPP_G9,  GpioPadModeNative2} // DDP3_CTRLDATA
  },
  {// DDP4
    {GPIO_VER2_H_GPP_G10, GpioPadModeNative2},// DDP4_CTRLCLK
    {GPIO_VER2_H_GPP_G11, GpioPadModeNative2} // DDP4_CTRLDATA
  },
  {// DDPA
    {GPIO_VER2_H_GPP_G0, GpioPadModeNative1},// DDPA_CTRLCLK
    {GPIO_VER2_H_GPP_G1, GpioPadModeNative1} // DDPA_CTRLDATA
  },
  {// DDPB
    {GPIO_VER2_H_GPP_I5, GpioPadModeNative1},// DDPB_CTRLCLK
    {GPIO_VER2_H_GPP_I6, GpioPadModeNative1} // DDPB_CTRLDATA
  },
  {// DDPC
    {GPIO_VER2_H_GPP_I7, GpioPadModeNative1},// DDPC_CTRLCLK
    {GPIO_VER2_H_GPP_I8, GpioPadModeNative1} // DDPC_CTRLDATA
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
    case GpioDdp1:
    case GpioDdp2:
    case GpioDdp3:
    case GpioDdp4:
      if (IsPchLp () || IsPchH ()) {
        DdpInterfaceIndex = DdpInterface - GpioDdp1;
      } else {
        goto Error;
      }
      break;
    case GpioDdpA:
    case GpioDdpB:
    case GpioDdpC:
      if (IsPchLp () || IsPchH ()) {
        DdpInterfaceIndex = (DdpInterface - GpioDdpA) + 4;
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
  } else if (IsPchH ()) {
    if (DdpInterfaceIndex < ARRAY_SIZE (mPchHDdpInterfacePins)) {
      *NativePinsTable = mPchHDdpInterfacePins[DdpInterfaceIndex];
      return;
    }
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
    return GPIO_VER2_LP_VGPIO5;
  } else if (IsPchH ()) {
    return GPIO_VER2_H_VGPIO5;
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
    return GPIO_VER2_LP_VGPIO4;
  } else if (IsPchH ()) {
    return GPIO_VER2_H_VGPIO4;
  } else {
    ASSERT (FALSE);
    return 0;
  }
}

//
// TBT LSX 0/1/2/3  RX and TX pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpTbtLsxInterfacePins[][2] =
{
  {// DDI 1 TBT LSX
    {GPIO_VER2_LP_GPP_E18, GpioPadModeNative4},// TBT_LSX0_RXD
    {GPIO_VER2_LP_GPP_E19, GpioPadModeNative4} // TBT_LSX0_TXD
  },
  {// DDI 2 TBT LSX
    {GPIO_VER2_LP_GPP_E20, GpioPadModeNative4},// TBT_LSX1_RXD
    {GPIO_VER2_LP_GPP_E21, GpioPadModeNative4} // TBT_LSX1_TXD
  },
  {// DDI 3 TBT LSX
    {GPIO_VER2_LP_GPP_D9,  GpioPadModeNative4},// TBT_LSX2_RXD
    {GPIO_VER2_LP_GPP_D10, GpioPadModeNative4} // TBT_LSX2_TXD
  },
  {// DDI 4 TBT LSX
    {GPIO_VER2_LP_GPP_D11, GpioPadModeNative4},// TBT_LSX3_RXD
    {GPIO_VER2_LP_GPP_D12, GpioPadModeNative4} // TBT_LSX3_TXD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHTbtLsxInterfacePins[][2] =
{
  {// DDI 1 TBT LSX
    {GPIO_VER2_H_GPP_G12, GpioPadModeNative3},// TBT_LSX0_RXD
    {GPIO_VER2_H_GPP_G13, GpioPadModeNative3} // TBT_LSX0_TXD
  },
  {// DDI 2 TBT LSX
    {GPIO_VER2_H_GPP_G14, GpioPadModeNative3},// TBT_LSX1_RXD
    {GPIO_VER2_H_GPP_G15, GpioPadModeNative3} // TBT_LSX1_TXD
  },
  {// DDI 3 TBT LSX
    {GPIO_VER2_H_GPP_G8,  GpioPadModeNative4},// TBT_LSX2_RXD
    {GPIO_VER2_H_GPP_G9,  GpioPadModeNative4} // TBT_LSX2_TXD
  },
  {// DDI 4 TBT LSX
    {GPIO_VER2_H_GPP_G10, GpioPadModeNative4},// TBT_LSX3_RXD
    {GPIO_VER2_H_GPP_G11, GpioPadModeNative4} // TBT_LSX3_TXD
  }
};

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
  EFI_STATUS                Status;
  UINTN                     Index;
  GPIO_PAD_NATIVE_FUNCTION  *TbtLsxGpio;
  UINT32                    TbtLsxPinIndex;

  TbtLsxPinIndex = TbtLsxDdiPort - GpioTbtLsxDdi1;

  if (IsPchLp ()) {
    if (TbtLsxPinIndex >= ARRAY_SIZE (mPchLpTbtLsxInterfacePins)) {
      goto Error;
    }
    TbtLsxGpio = mPchLpTbtLsxInterfacePins[TbtLsxPinIndex];
  } else if (IsPchH ()) {
    if (TbtLsxPinIndex >= ARRAY_SIZE (mPchHTbtLsxInterfacePins)) {
      goto Error;
    }
    TbtLsxGpio = mPchHTbtLsxInterfacePins[TbtLsxPinIndex];
  } else {
    goto Error;
  }

  for (Index = 0; Index < 2; Index++) {
    Status = GpioSetPadMode (TbtLsxGpio[Index].Pad, TbtLsxGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      goto Error;
    }
  }
  return EFI_SUCCESS;

Error:
  ASSERT(FALSE);
  return EFI_UNSUPPORTED;
}

//
// CNVi Bluetooth UART pads
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_LP_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_VER2_LP_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_VER2_LP_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_VER2_LP_VGPIO9  // vCNV_BT_UART_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_VER2_H_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_VER2_H_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_VER2_H_VGPIO9  // vCNV_BT_UART_RTS_B
};

//
// vUART for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_LP_VGPIO18, // vUART0_TXD
  GPIO_VER2_LP_VGPIO19, // vUART0_RXD
  GPIO_VER2_LP_VGPIO20, // vUART0_CTS_B
  GPIO_VER2_LP_VGPIO21  // vUART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO18, // vUART0_TXD
  GPIO_VER2_H_VGPIO19, // vUART0_RXD
  GPIO_VER2_H_VGPIO20, // vUART0_CTS_B
  GPIO_VER2_H_VGPIO21  // vUART0_RTS_B
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
  } else if (IsPchH ()) {
    *VCnviBtUartPad = mPchHVCnviBtUartGpioPad;
    *VUartForCnviBtPad = mPchHVUartForCnviBtGpioPad;
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
  GPIO_VER2_LP_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_VER2_LP_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_VER2_LP_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_VER2_LP_VGPIO33  // vCNV_BT_I2S_SDI
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_VER2_H_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_VER2_H_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_VER2_H_VGPIO33  // vCNV_BT_I2S_SDI
};

//
// vSSP for Bluetooth
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_VER2_LP_VGPIO34, // vSSP2_SCLK
  GPIO_VER2_LP_VGPIO35, // vSSP2_SFRM
  GPIO_VER2_LP_VGPIO36, // vSSP2_TXD
  GPIO_VER2_LP_VGPIO37  // vSSP2_RXD
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO34, // vSSP2_SCLK
  GPIO_VER2_H_VGPIO35, // vSSP2_SFRM
  GPIO_VER2_H_VGPIO36, // vSSP2_TXD
  GPIO_VER2_H_VGPIO37  // vSSP2_RXD
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
  } else if (IsPchH ()) {
    *VCnviBtI2sPad = mPchHVCnviBtI2sGpioPad;
    *VSspForCnviBtPad = mPchHVSspForCnviBtGpioPad;
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
  GPIO_VER2_LP_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_VER2_LP_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_VER2_LP_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_VER2_LP_VGPIO13  // vCNV_MFUART1_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_VER2_H_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_VER2_H_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_VER2_H_VGPIO13  // vCNV_MFUART1_RTS_B
};

//
// vUART for MFUART1
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchLpVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_LP_VGPIO22, // vISH_UART0_TXD
  GPIO_VER2_LP_VGPIO23, // vISH_UART0_RXD
  GPIO_VER2_LP_VGPIO24, // vISH_UART0_CTS_B
  GPIO_VER2_LP_VGPIO25  // vISH_UART0_RTS_B
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_VER2_H_VGPIO22, // vISH_UART0_TXD
  GPIO_VER2_H_VGPIO23, // vISH_UART0_RXD
  GPIO_VER2_H_VGPIO24, // vISH_UART0_CTS_B
  GPIO_VER2_H_VGPIO25  // vISH_UART0_RTS_B
};

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
  } else if (IsPchH ()) {
    *VCnviMfUart1Pad = mPchHVCnviMfUart1GpioPad;
    *VUartForCnviMfUart1Pad = mPchHVUartForCnviMfUart1GpioPad;
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
    return GPIO_VER2_LP_VGPIO0;
  } else if (IsPchH ()) {
    return GPIO_VER2_H_VGPIO0;
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
  {GPIO_VER2_LP_GPP_F0,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_VER2_LP_GPP_F1,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_VER2_LP_GPP_F2,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_VER2_LP_GPP_F3,  GpioPadModeNative1}  // CNV_RGI_RSP
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS] =
{
  {GPIO_VER2_H_GPP_J2,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_VER2_H_GPP_J3,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_VER2_H_GPP_J4,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_VER2_H_GPP_J5,  GpioPadModeNative1}  // CNV_RGI_RSP
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
  } else if (IsPchH ()) {
    *NativePinsTable = mPchHCnviBriRgiGpioPad;
  } else {
    ASSERT (FALSE);
    return;
  }
}


GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpImguClkOutGpioPad[] =
{
  {GPIO_VER2_LP_GPP_D4,   GpioPadModeNative1}, // IMGCLKOUT_0
  {GPIO_VER2_LP_GPP_H20,  GpioPadModeNative1}, // IMGCLKOUT_1
  {GPIO_VER2_LP_GPP_H21,  GpioPadModeNative1}, // IMGCLKOUT_2
  {GPIO_VER2_LP_GPP_H22,  GpioPadModeNative1}, // IMGCLKOUT_3
  {GPIO_VER2_LP_GPP_H23,  GpioPadModeNative1}, // IMGCLKOUT_4
  {GPIO_VER2_LP_GPP_D15,  GpioPadModeNative3}  // IMGCLKOUT_5
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHImguClkOutGpioPad[] =
{
  {GPIO_VER2_H_GPP_A14,   GpioPadModeNative1}, // IMGCLKOUT_0
  {GPIO_VER2_H_GPP_B0,    GpioPadModeNative1}  // IMGCLKOUT_1
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
  } else {
    *NativePinsTable = mPchHImguClkOutGpioPad;
    *NoOfNativePins = ARRAY_SIZE (mPchHImguClkOutGpioPad);
  }
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
    return GPIO_VER2_LP_GPD3;
  } else {
    return GPIO_VER2_H_GPD3;
  }
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
  GPIO_VER2_LP_GPP_E18, // BSSB_LS0_RX
  GPIO_VER2_LP_GPP_E19, // BSSB_LS0_TX
  GPIO_VER2_LP_GPP_E20, // BSSB_LS1_RX
  GPIO_VER2_LP_GPP_E21, // BSSB_LS1_TX
  GPIO_VER2_LP_GPP_D9,  // BSSB_LS2_RX
  GPIO_VER2_LP_GPP_D10, // BSSB_LS2_TX
  GPIO_VER2_LP_GPP_D11, // BSSB_LS3_RX
  GPIO_VER2_LP_GPP_D12  // BSSB_LS3_TX
};


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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpFiaClkReqVwMsgBus [][20] =
{
  {
    {GPIO_VER2_LP_VGPIO_PCIE_0, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_1, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_2, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_3, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_4, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_5, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_6, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_7, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_8, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_9, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_10, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_11, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_12, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_13, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_14, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_15, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_64, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_65, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_66, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_67, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_LP_VGPIO_PCIE_16, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_17, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_18, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_19, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_20, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_21, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_22, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_23, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_24, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_25, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_26, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_27, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_28, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_29, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_30, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_31, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_68, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_69, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_70, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_71, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_LP_VGPIO_PCIE_32, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_33, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_34, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_35, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_36, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_37, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_38, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_39, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_40, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_41, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_42, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_43, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_44, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_45, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_46, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_47, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_72, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_73, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_74, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_75, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_LP_VGPIO_PCIE_48, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_49, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_50, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_51, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_52, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_53, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_54, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_55, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_56, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_57, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_58, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_59, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_60, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_61, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_62, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_63, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_76, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_77, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_78, GpioPadModeNative1},
    {GPIO_VER2_LP_VGPIO_PCIE_79, GpioPadModeNative1}
  },
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHFiaClkReqVwMsgBus [][20] =
{
  {
    {GPIO_VER2_H_VGPIO_PCIE_0, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_1, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_2, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_3, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_4, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_5, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_6, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_7, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_8, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_9, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_10, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_11, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_12, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_13, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_14, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_15, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_64, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_65, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_66, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_67, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_H_VGPIO_PCIE_16, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_17, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_18, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_19, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_20, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_21, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_22, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_23, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_24, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_25, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_26, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_27, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_28, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_29, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_30, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_31, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_68, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_69, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_70, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_71, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_H_VGPIO_PCIE_32, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_33, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_34, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_35, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_36, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_37, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_38, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_39, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_40, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_41, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_42, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_43, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_44, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_45, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_46, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_47, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_72, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_73, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_74, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_75, GpioPadModeNative1}
  },
  {
    {GPIO_VER2_H_VGPIO_PCIE_48, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_49, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_50, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_51, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_52, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_53, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_54, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_55, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_56, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_57, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_58, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_59, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_60, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_61, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_62, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_63, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_76, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_77, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_78, GpioPadModeNative1},
    {GPIO_VER2_H_VGPIO_PCIE_79, GpioPadModeNative1}
  },
};

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
  if (IsPchLp ()) {
    if (PciePortIndex <= ARRAY_SIZE (mPchLpFiaClkReqVwMsgBus)) {
      *VwBusPinsTable = mPchLpFiaClkReqVwMsgBus[PciePortIndex];
      *NoOfNativePins = ARRAY_SIZE (mPchLpFiaClkReqVwMsgBus[PciePortIndex]);
    }
  } else if (IsPchH ()) {
    if (PciePortIndex <= ARRAY_SIZE (mPchHFiaClkReqVwMsgBus)) {
      *VwBusPinsTable = mPchHFiaClkReqVwMsgBus[PciePortIndex];
      *NoOfNativePins = ARRAY_SIZE (mPchHFiaClkReqVwMsgBus[PciePortIndex]);
    }
  } else {
    return EFI_UNSUPPORTED;
  }

  if (*VwBusPinsTable != NULL) {
    return EFI_SUCCESS;
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

//
// Timed GPIO pin mapping
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpTimeSyncToGpioMap[] =
{
  {GPIO_VER2_LP_GPP_H19,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_B14,  GpioPadModeNative2}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHTimeSyncToGpioMap[] =
{
  {GPIO_VER2_LP_GPP_H23,  GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_B1,   GpioPadModeNative2}
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
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  EFI_STATUS          Status;

  if (IsPchLp ()) {
    for (Index = 0; Index < ARRAY_SIZE (mPchLpTimeSyncToGpioMap); Index++) {
      Status = GpioSetPadMode (mPchLpTimeSyncToGpioMap[Index].Pad, mPchLpTimeSyncToGpioMap[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  } else if (IsPchH ()) {
    for (Index = 0; Index < ARRAY_SIZE (mPchLpTimeSyncToGpioMap); Index++) {
      Status = GpioSetPadMode (mPchHTimeSyncToGpioMap[Index].Pad, mPchHTimeSyncToGpioMap[Index].Mode);
      if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
      }
    }
  }
#endif
  return EFI_SUCCESS;
}

//
// Tsn pin mapping
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpTsnMap[] =
{
  {GPIO_VER2_LP_GPP_F17, GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_F18, GpioPadModeNative1},
  {GPIO_VER2_LP_GPP_S0, GpioPadModeNative3},
  {GPIO_VER2_LP_GPP_S1, GpioPadModeNative3},
  {GPIO_VER2_LP_GPP_S2, GpioPadModeNative3},
  {GPIO_VER2_LP_GPP_S3, GpioPadModeNative3}
};

/**
  This function sets Tsn into native mode

  @retval Status
**/
EFI_STATUS
GpioEnableTsn (
  VOID
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
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
#endif
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
  GPIO_PAD            *GpioSbuPadTable;
  UINT32              SbuPadNum;
  UINT32              MaxIndex;
  GPIO_CONFIG         PadConfig;
  UINT32              Index;
  UINT32              SbuUnlockedPads;
  EFI_STATUS          Status;

  if ((UnlockCfgPad == NULL) || (UnlockTxPad == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  MaxIndex = 0;
  // SBU (Sideband use) pins are used as auxiliary signals for Type C connector,
  // which are hard-wired to BSSB_LS natively for debug function.
  // when USB-C needed, don't lock pins that control by PMC at runtime,
  if (IsPchLp ()) {
    GpioSbuPadTable = mPchLpTypeCSbuGpioPad;
    MaxIndex = ARRAY_SIZE (mPchLpTypeCSbuGpioPad);
  } else {
    *UnlockCfgPad = 0;
    *UnlockTxPad = 0;
    return EFI_SUCCESS;
  }
  SbuUnlockedPads = 0;

  for (Index = 0; Index < MaxIndex; Index++) {

    SbuPadNum = GpioGetPadNumberFromGpioPad (GpioSbuPadTable[Index]);

    if (Group != GpioGetGroupFromGpioPad (GpioSbuPadTable[Index])) {
      continue;
    }

    if (DwNum != GPIO_GET_DW_NUM (SbuPadNum)) {
      continue;
    }

    Status = GpioGetPadConfig (GpioSbuPadTable[Index], &PadConfig);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // GPIO, Native3, Native4 and Native5 control by PMC at runtime
    //
    if ((PadConfig.PadMode == GpioPadModeNative1) || (PadConfig.PadMode == GpioPadModeNative2)) {
      continue;
    }

    SbuUnlockedPads |= (1 << GPIO_GET_PAD_POSITION (SbuPadNum));
  }

  *UnlockCfgPad = SbuUnlockedPads;
  *UnlockTxPad = SbuUnlockedPads;
  return EFI_SUCCESS;
}
