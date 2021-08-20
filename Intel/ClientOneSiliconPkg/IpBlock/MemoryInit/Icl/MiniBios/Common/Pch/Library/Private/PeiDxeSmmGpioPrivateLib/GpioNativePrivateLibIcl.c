/** @file
  This file contains ICL specific GPIO information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PchInfoLib.h>
#include <Private/Library/GpioPrivateLib.h>
#include <Private/GpioNativePads.h>
#include <GpioPinsIclLp.h>
#include <GpioPinsIclN.h>
#include <GpioPinsIclH.h>
#include <Register/PchRegsGpio.h>
#include <Register/PchRegsGpioIcl.h>
#include <Register/PchRegsSerialIo.h>
#include <Register/PchRegsIsh.h>

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
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (0):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (1):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (2):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D12, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (0):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (1):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (2):  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D11, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (2):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D10, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 0): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 1): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B14, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 0): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 1): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B23, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 0): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D9,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 1): return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D15, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(4):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(5):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B10, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(4):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_H8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(5):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B9,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(0):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D0,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(1):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D1,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(2):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D2,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(3):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D3,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(4):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D17, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(5):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D18, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(6):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_E15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(7):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_E16, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D13, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D14, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(1):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C13, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D16, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(1):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_C15, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B6,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(1):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B8,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(2):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B10, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B5,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(1):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(2):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_B9,  2, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MOSI(0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MISO(0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CLK(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CS (0, 0):       return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_D9,  1, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(0):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_S6, 2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_S7, 2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(1):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_S4, 2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_S5, 2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(1):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A19, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(2):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A20, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(3):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A14, 2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(4):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A15, 2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_E14, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A18, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):        return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_HVCMOS_L_VDDEN,   1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_HVCMOS_L_BKLTEN,  1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):        return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_HVCMOS_L_BKLTCTL, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_HPD(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_E14, 1, PadFunction);
      case GPIO_FUNCTION_CNVI_RF_RESET:           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A8, 2, PadFunction);
      case GPIO_FUNCTION_CNVI_MODEM_CLKREQ:       return GPIO_NATIVE_PAD_DEF (GPIO_ICL_LP_GPP_A9, 2, PadFunction);
      default: break;
    }
  } else if (IsPchN ()) {
    switch (PadFunction) {
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C20, 1, PadFunction); // JSL REV1 / EHLZ0
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C21, 1, PadFunction); // JSL REV1 / EHLZ0
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D11, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D10, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (0):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D9,  2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_B23, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D8,  2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D9,  2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H5,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H7,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(4):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H9,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(5):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H4,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H6,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(4):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H8,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(5):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D22, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(0):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E0,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(1):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E1,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(2):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E3,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(3):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(4):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E8,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(5):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E9,  1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(6):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(7):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_E11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D13, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C13, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D14, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(1):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D15, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(1):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_C15, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D5,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(2):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D23, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D4,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D6,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(2):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D22, 2, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MOSI(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MISO(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CLK(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D9,  1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CS (0, 0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_D8,  1, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(0):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_S6,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(0):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_S7,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(1):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_S4,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(1):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_S5,  2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_A16, 1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_A15, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_HVCMOS_L_VDDEN,  1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_HVCMOS_L_BKLTEN, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_HVCMOS_L_BKLTCTL,1, PadFunction);
      case GPIO_FUNCTION_PANEL_HPD(0):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_CNVI_RF_RESET:             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H12, 2, PadFunction);
      case GPIO_FUNCTION_CNVI_MODEM_CLKREQ:         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_N_GPP_H13, 2, PadFunction);

      default: break;
    }
  } else {
    switch (PadFunction) {
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C12, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RX(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C13, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_TX(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C14, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_RTS(2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_UART_CTS(2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C23, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B22, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G11, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (0):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (1):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B21, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_MISO (2):    return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G10, 3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (0):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (1):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B20, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CLK (2):     return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G9,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B15, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (0, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B0,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (1, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_B1,  1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 0):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G8,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_SPI_CS (2, 1):   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A11, 2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(0):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C17, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C19, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C4,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SCL(3):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C7,  2, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(0):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C16, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(1):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C18, 1, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(2):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C3,  3, PadFunction);
      case GPIO_FUNCTION_SERIAL_IO_I2C_SDA(3):      return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C6,  2, PadFunction);
      case GPIO_FUNCTION_ISH_GP(0):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A18, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(1):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A19, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(2):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A20, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(3):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A21, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(4):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A22, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(5):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A23, 1, PadFunction);
      case GPIO_FUNCTION_ISH_GP(6):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_GP(7):                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A17, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C3,  1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RX(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C12, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C4,  1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_TX(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C13, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_A11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_RTS(1):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C14, 2, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_D12, 1, PadFunction);
      case GPIO_FUNCTION_ISH_UART_CTS(1):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C15, 2, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_H20, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_H22, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SCL(2):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C7,  1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_H19, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(1):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_H21, 1, PadFunction);
      case GPIO_FUNCTION_ISH_I2C_SDA(2):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_C6,  1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MOSI(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G11, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_MISO(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G10, 1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CLK(0):            return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G9,  1, PadFunction);
      case GPIO_FUNCTION_ISH_SPI_CS (0, 0):         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_G8,  1, PadFunction);
      case GPIO_FUNCTION_HDA_BCLK:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R0,  1, PadFunction);
      case GPIO_FUNCTION_HDA_RSTB:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R4,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SYNC:                  return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R1,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDO:                   return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R2,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_0:                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R3,  1, PadFunction);
      case GPIO_FUNCTION_HDA_SDI_1:                 return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_R5,  1, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(0):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_S6,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(0):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_S7,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_CLK(1):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_S4,  2, PadFunction);
      case GPIO_FUNCTION_DMIC_DATA(1):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_S5,  2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(1):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_I1,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(2):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_I2,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(3):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_I3,  2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD(4):               return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_I4,  2, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('A'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_K6,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('B'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_K7,  1, PadFunction);
      case GPIO_FUNCTION_DDSP_HPD('C'):             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_K10, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_AVDD_EN(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_F19, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTEN(0):           return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_F20, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_BKLTCTL(0):          return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_F21, 1, PadFunction);
      case GPIO_FUNCTION_PANEL_HPD(0):              return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_K6,  1, PadFunction);
      case GPIO_FUNCTION_CNVI_RF_RESET:             return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_D5, 3, PadFunction);
      case GPIO_FUNCTION_CNVI_MODEM_CLKREQ:         return GPIO_NATIVE_PAD_DEF (GPIO_ICL_H_GPP_D6, 3, PadFunction);
      default: break;
    }
  }

  return GPIO_PAD_NONE;
}

#ifndef MRC_MINIBIOS_BUILD
//
// GPIO pins for SD controller
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpScsSdCardGpio[] =
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNScsSdCardGpio[] =
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHScsSdCardGpio[] =
{
  {GPIO_ICL_H_GPP_K11, GpioPadModeNative1},// SD_PWR_EN_B
  {GPIO_ICL_H_GPP_G0,  GpioPadModeNative1},// SD_CMD
  {GPIO_ICL_H_GPP_G1,  GpioPadModeNative1},// SD_DATA_0
  {GPIO_ICL_H_GPP_G2,  GpioPadModeNative1},// SD_DATA_1
  {GPIO_ICL_H_GPP_G3,  GpioPadModeNative1},// SD_DATA_2
  {GPIO_ICL_H_GPP_G4,  GpioPadModeNative1},// SD_DATA_3
  {GPIO_ICL_H_GPP_G5,  GpioPadModeNative1},// SD_CDB
  {GPIO_ICL_H_GPP_G6,  GpioPadModeNative1},// SD_CLK
  {GPIO_ICL_H_GPP_G7,  GpioPadModeNative1} // SD_WP
};

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
    *NativePinsTable = mPchHScsSdCardGpio;
    *NoOfNativePins = ARRAY_SIZE (mPchHScsSdCardGpio);
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
    return GPIO_ICL_H_VGPIO39;
  }
}

//
// GPIO pins for eMMC controller
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpScsEmmcGpio[12] =
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSspInterfaceGpio[][PCH_GPIO_HDA_SSP_NUMBER_OF_PINS] =
{
  { //SSP0/I2S0
    {GPIO_ICL_H_GPP_R0,  GpioPadModeNative2},//I2S0_SCLK
    {GPIO_ICL_H_GPP_R1,  GpioPadModeNative2},//I2S0_SFRM
    {GPIO_ICL_H_GPP_R2,  GpioPadModeNative2},//I2S0_TXD
    {GPIO_ICL_H_GPP_R3,  GpioPadModeNative2} //I2S0_RXD
  },
  { //SSP1/I2S1
    {GPIO_ICL_H_GPP_D11, GpioPadModeNative1},//I2S1_SCLK
    {GPIO_ICL_H_GPP_R7,  GpioPadModeNative2},//I2S1_SFRM
    {GPIO_ICL_H_GPP_R6,  GpioPadModeNative2},//I2S1_TXD
    {GPIO_ICL_H_GPP_R5,  GpioPadModeNative2} //I2S1_RXD
  },
  { //SSP2/I2S2
    {GPIO_ICL_H_GPP_D8, GpioPadModeNative1},//I2S2_SCLK
    {GPIO_ICL_H_GPP_D5, GpioPadModeNative1},//I2S2_SFRM
    {GPIO_ICL_H_GPP_D6, GpioPadModeNative1},//I2S2_TXD
    {GPIO_ICL_H_GPP_D7, GpioPadModeNative1} //I2S2_RXD
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
  } else if (IsPchN ()) {
    if (SspInterfaceNumber < ARRAY_SIZE (mPchNHdaSspInterfaceGpio)) {
      *NativePinsTable = mPchNHdaSspInterfaceGpio[SspInterfaceNumber];
      return;
    }
  } else {
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
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpHdaSspMasterClockGpio = {GPIO_ICL_LP_GPP_D19, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNHdaSspMasterClockGpio = {GPIO_ICL_N_GPP_D18,  GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSspMasterClockGpio = {GPIO_ICL_H_GPP_B11,  GpioPadModeNative1};

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
  ASSERT (MclkIndex == 0);

  if (IsPchLp ()) {
    return GpioSetPadMode (mPchLpHdaSspMasterClockGpio.Pad, mPchLpHdaSspMasterClockGpio.Mode);
  } else if (IsPchN ()) {
    return GpioSetPadMode (mPchNHdaSspMasterClockGpio.Pad, mPchNHdaSspMasterClockGpio.Mode);
  } else {
    return GpioSetPadMode (mPchHHdaSspMasterClockGpio.Pad, mPchHHdaSspMasterClockGpio.Mode);

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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHHdaSndwGpio[][PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS] =
{
  { // SNDW1
    {GPIO_ICL_H_GPP_S0, GpioPadModeNative1},// SNDW1_CLK
    {GPIO_ICL_H_GPP_S1, GpioPadModeNative1} // SNDW1_DATA
  },
  { // SNDW2
    {GPIO_ICL_H_GPP_S2, GpioPadModeNative1},// SNDW2_CLK
    {GPIO_ICL_H_GPP_S3, GpioPadModeNative1} // SNDW2_DATA
  },
  { // SNDW3
    {GPIO_ICL_H_GPP_S4, GpioPadModeNative1},// SNDW3_CLK
    {GPIO_ICL_H_GPP_S5, GpioPadModeNative1} // SNDW3_DATA
  },
  { // SNDW4
    {GPIO_ICL_H_GPP_S6, GpioPadModeNative1},// SNDW4_CLK
    {GPIO_ICL_H_GPP_S7, GpioPadModeNative1} // SNDW4_DATA
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
  } else if (IsPchN ()) {
    if (SndwInterfaceNumber < ARRAY_SIZE (mPchNHdaSndwGpio)) {
      *NativePinsTable = mPchNHdaSndwGpio[SndwInterfaceNumber];
      return;
    }
  } else {
    if (SndwInterfaceNumber < ARRAY_SIZE (mPchHHdaSndwGpio)) {
      *NativePinsTable = mPchHHdaSndwGpio[SndwInterfaceNumber];
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusGpio[PCH_GPIO_SMBUS_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_C0, GpioPadModeNative1},// SMB_CLK
  {GPIO_ICL_H_GPP_C1, GpioPadModeNative1} // SMB_DATA
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
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSmbusAlertGpio = {GPIO_ICL_H_GPP_C2,  GpioPadModeNative1};

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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataDevSlpPinToGpioMap[] =
{
  {GPIO_ICL_H_GPP_E4, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_E5, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_E6, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_F5, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_F6, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_F7, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_F8, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_F9, GpioPadModeNative1}
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
  } else if (IsPchN ()) {
    if (SataPort < ARRAY_SIZE (mPchNSataDevSlpPinToGpioMap)) {
      *NativePin = mPchNSataDevSlpPinToGpioMap[SataPort];
      return;
    }
  } else {
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataGpToGpioMap[] =
{
  {GPIO_ICL_H_GPP_E0, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_E1, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_E2, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_F0, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_F1, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_F2, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_F3, GpioPadModeNative2},
  {GPIO_ICL_H_GPP_F4, GpioPadModeNative2}
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
  } else if (IsPchN ()) {
    if (SataPort < ARRAY_SIZE (mPchNSataGpToGpioMap)) {
      *NativePin = mPchNSataGpToGpioMap[SataPort];
      return;
    }
  } else {
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
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpSataLedGpio = {GPIO_ICL_LP_GPP_E8, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNSataLedGpio = {GPIO_ICL_N_GPP_E5, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHSataLedGpio = {GPIO_ICL_H_GPP_E8, GpioPadModeNative1};

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
    SataLedGpio = mPchHSataLedGpio;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHUsbOcGpioPins[] =
{
  {GPIO_ICL_H_GPP_E9,  GpioPadModeNative1},// USB_OC_0
  {GPIO_ICL_H_GPP_E10, GpioPadModeNative1},// USB_OC_1
  {GPIO_ICL_H_GPP_E11, GpioPadModeNative1},// USB_OC_2
  {GPIO_ICL_H_GPP_E12, GpioPadModeNative1} // USB_OC_3
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
  } else if (IsPchN ()) {
    if (OcPinNumber >= ARRAY_SIZE (mPchNUsbOcGpioPins)) {
      ASSERT(FALSE);
      return EFI_UNSUPPORTED;
    }
    OcGpio = mPchNUsbOcGpioPins[OcPinNumber];
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPcieSrcClkReqbPinToGpioMap[] =
{
  {GPIO_ICL_H_GPP_B5,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_B6,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_B7,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_B8,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_B9,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_B10, GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H0,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H1,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H2,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H3,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H4,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H5,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H6,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H7,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H8,  GpioPadModeNative1},
  {GPIO_ICL_H_GPP_H9,  GpioPadModeNative1}
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
  } else if (IsPchN ()) {
    if (ClkreqIndex < ARRAY_SIZE (mPchNPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchNPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
      return;
    }
  } else {
    if (ClkreqIndex < ARRAY_SIZE (mPchHPcieSrcClkReqbPinToGpioMap)) {
      *NativePin = mPchHPcieSrcClkReqbPinToGpioMap[ClkreqIndex];
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
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHPchHotbPin = {GPIO_ICL_H_GPP_B23,  GpioPadModeNative2};

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
    PchHotbPin = mPchHPchHotbPin;
  }

  return GpioSetPadMode (PchHotbPin.Pad, PchHotbPin.Mode);
}

//
// VRALERTB pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpVrAlertbPin = {GPIO_ICL_LP_GPP_B2, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNVrAlertbPin = {GPIO_ICL_N_GPP_B2, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHVrAlertbPin= {GPIO_ICL_H_GPP_B2, GpioPadModeNative1};

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
    VrAlertGpio = mPchHVrAlertbPin;
  }

  return GpioSetPadMode (VrAlertGpio.Pad, VrAlertGpio.Mode);
}

//
// CPU_C10_GATE pin
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpCpuC10GatePin = {GPIO_ICL_LP_GPP_H18, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNCpuC10GatePin = {GPIO_ICL_N_GPP_H10, GpioPadModeNative1};
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuC10GatePin = {GPIO_ICL_H_GPP_J1, GpioPadModeNative1};

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
    CpuC10GateGpio = mPchHCpuC10GatePin;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCpuGpPinMap[PCH_GPIO_CPU_GP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_E3, GpioPadModeNative1}, // CPU_GP_0
  {GPIO_ICL_H_GPP_E7, GpioPadModeNative1}, // CPU_GP_1
  {GPIO_ICL_H_GPP_B3, GpioPadModeNative1}, // CPU_GP_2
  {GPIO_ICL_H_GPP_B4, GpioPadModeNative1}, // CPU_GP_3
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
  } else if (IsPchN ()) {
    if (CpuGpPinNum >= ARRAY_SIZE (mPchNCpuGpPinMap)) {
      ASSERT (FALSE);
      return EFI_UNSUPPORTED;
    }
    CpuGpPin = mPchNCpuGpPinMap[CpuGpPinNum];
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

//
// DDP1/2/3/4/A/B/C  CTRLCLK and CTRLDATA pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHDdpInterfacePins[][PCH_GPIO_DDP_NUMBER_OF_PINS] =
{
  {// DDP1
    {GPIO_ICL_H_GPP_G12, GpioPadModeNative1},// DDP1_CTRLCLK
    {GPIO_ICL_H_GPP_G13, GpioPadModeNative1} // DDP1_CTRLDATA
  },
  {// DDP2
    {GPIO_ICL_H_GPP_G14, GpioPadModeNative1},// DDP2_CTRLCLK
    {GPIO_ICL_H_GPP_G15, GpioPadModeNative1} // DDP2_CTRLDATA
  },
  {// DDP3
    {GPIO_ICL_H_GPP_G8,  GpioPadModeNative2},// DDP3_CTRLCLK
    {GPIO_ICL_H_GPP_G9, GpioPadModeNative2}  // DDP3_CTRLDATA
  },
  {// DDP4
    {GPIO_ICL_H_GPP_G10, GpioPadModeNative2},// DDP4_CTRLCLK
    {GPIO_ICL_H_GPP_G11, GpioPadModeNative2} // DDP4_CTRLDATA
  },
  {// DDPA
    {GPIO_ICL_H_GPP_F22, GpioPadModeNative1},// DDPA_CTRLCLK
    {GPIO_ICL_H_GPP_F23, GpioPadModeNative1} // DDPA_CTRLDATA
  },
  {// DDPB
    {GPIO_ICL_H_GPP_I5, GpioPadModeNative1},// DDPB_CTRLCLK
    {GPIO_ICL_H_GPP_I6, GpioPadModeNative1} // DDPB_CTRLDATA
  },
  {// DDPC
    {GPIO_ICL_H_GPP_I7, GpioPadModeNative2},// DDPC_CTRLCLK
    {GPIO_ICL_H_GPP_I8, GpioPadModeNative2} // DDPC_CTRLDATA
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
      if (!IsPchN ()) {
        DdpInterfaceIndex = DdpInterface - GpioDdp1;
      } else {
        goto Error;
      }
      break;
    case GpioDdpA:
    case GpioDdpB:
    case GpioDdpC:
      if (IsPchN ()) {
        DdpInterfaceIndex = DdpInterface - GpioDdpA;
      } else {
        DdpInterfaceIndex = (DdpInterface - GpioDdpA) + 4;
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
  } else {
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
    return GPIO_ICL_LP_VGPIO5;
  } else if (IsPchN ()) {
    return GPIO_ICL_N_VGPIO5;
  } else {
    return GPIO_ICL_H_VGPIO5;
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
    return GPIO_ICL_H_VGPIO3;
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
  } else if (IsPchH ()) {
    GpioNativePad->Mode = GpioPadModeNative1;
    GpioNativePad->Pad = GPIO_ICL_H_GPP_J9;
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
    return GPIO_ICL_H_VGPIO4;
  }
}

//
// TBT LSX 0/1/2/3  RX and TX pins
//
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpTbtLsxInterfacePins[][2] =
{
  {// DDI 1 TBT LSX
    {GPIO_ICL_LP_GPP_E18, GpioPadModeNative4},// TBT_LSX0_RXD
    {GPIO_ICL_LP_GPP_E19, GpioPadModeNative4} // TBT_LSX0_TXD
  },
  {// DDI 2 TBT LSX
    {GPIO_ICL_LP_GPP_E20, GpioPadModeNative4},// TBT_LSX1_RXD
    {GPIO_ICL_LP_GPP_E21, GpioPadModeNative4} // TBT_LSX1_TXD
  },
  {// DDI 3 TBT LSX
    {GPIO_ICL_LP_GPP_D9,  GpioPadModeNative4},// TBT_LSX2_RXD
    {GPIO_ICL_LP_GPP_D10, GpioPadModeNative4} // TBT_LSX2_TXD
  },
  {// DDI 4 TBT LSX
    {GPIO_ICL_LP_GPP_D11, GpioPadModeNative4},// TBT_LSX3_RXD
    {GPIO_ICL_LP_GPP_D12, GpioPadModeNative4} // TBT_LSX3_TXD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNTbtLsxInterfacePins[][2] =
{
  {// DDI 1 TBT LSX
    {GPIO_ICL_N_GPP_E13, GpioPadModeNative2},// TBT_LSX0_RXD
    {GPIO_ICL_N_GPP_E14, GpioPadModeNative2} // TBT_LSX0_TXD
  },
  {// DDI 2 TBT LSX
    {GPIO_ICL_N_GPP_E15, GpioPadModeNative2},// TBT_LSX1_RXD
    {GPIO_ICL_N_GPP_E16, GpioPadModeNative2} // TBT_LSX1_TXD
  },
  {// DDI 3 TBT LSX
    {GPIO_ICL_N_GPP_E17, GpioPadModeNative2},// TBT_LSX2_RXD
    {GPIO_ICL_N_GPP_E18, GpioPadModeNative2} // TBT_LSX2_TXD
  },
  {// DDI 4 TBT LSX
    {GPIO_ICL_N_GPP_E11, GpioPadModeNative2},// TBT_LSX3_RXD
    {GPIO_ICL_N_GPP_E12, GpioPadModeNative2} // TBT_LSX3_TXD
  },
  {// DDI 5 TBT LSX
    {GPIO_ICL_N_GPP_E20, GpioPadModeNative2},// TBT_LSX4_RXD
    {GPIO_ICL_N_GPP_E21, GpioPadModeNative2} // TBT_LSX4_TXD
  },
  {// DDI 6 TBT LSX
    {GPIO_ICL_N_GPP_E22, GpioPadModeNative2},// TBT_LSX5_RXD
    {GPIO_ICL_N_GPP_E23, GpioPadModeNative2} // TBT_LSX5_TXD
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHTbtLsxInterfacePins[][2] =
{
  {// DDI 1 TBT LSX
    {GPIO_ICL_H_GPP_G12, GpioPadModeNative3},// TBT_LSX0_RXD
    {GPIO_ICL_H_GPP_G13, GpioPadModeNative3} // TBT_LSX0_TXD
  },
  {// DDI 2 TBT LSX
    {GPIO_ICL_H_GPP_G14, GpioPadModeNative3},// TBT_LSX1_RXD
    {GPIO_ICL_H_GPP_G15, GpioPadModeNative3} // TBT_LSX1_TXD
  },
  {// DDI 3 TBT LSX
    {GPIO_ICL_H_GPP_G8,  GpioPadModeNative4},// TBT_LSX2_RXD
    {GPIO_ICL_H_GPP_G9,  GpioPadModeNative4} // TBT_LSX2_TXD
  },
  {// DDI 4 TBT LSX
    {GPIO_ICL_H_GPP_G10, GpioPadModeNative4},// TBT_LSX3_RXD
    {GPIO_ICL_H_GPP_G11, GpioPadModeNative4} // TBT_LSX3_TXD
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
  } else if (IsPchN ()) {
    if (TbtLsxPinIndex >= ARRAY_SIZE (mPchNTbtLsxInterfacePins)) {
      goto Error;
    }
    TbtLsxGpio = mPchNTbtLsxInterfacePins[TbtLsxPinIndex];
  } else {
    if (TbtLsxPinIndex >= ARRAY_SIZE (mPchHTbtLsxInterfacePins)) {
      goto Error;
    }
    TbtLsxGpio = mPchHTbtLsxInterfacePins[TbtLsxPinIndex];
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtUartGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO6, // vCNV_BT_UART_TXD
  GPIO_ICL_H_VGPIO7, // vCNV_BT_UART_RXD
  GPIO_ICL_H_VGPIO8, // vCNV_BT_UART_CTS_B
  GPIO_ICL_H_VGPIO9  // vCNV_BT_UART_RTS_B
};


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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviBtGpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO18, // vUART0_TXD
  GPIO_ICL_H_VGPIO19, // vUART0_RXD
  GPIO_ICL_H_VGPIO20, // vUART0_CTS_B
  GPIO_ICL_H_VGPIO21  // vUART0_RTS_B
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
  } else if (IsPchN ()) {
    *VCnviBtUartPad = mPchNVCnviBtUartGpioPad;
    *VUartForCnviBtPad = mPchNVUartForCnviBtGpioPad;
  } else {
    *VCnviBtUartPad = mPchHVCnviBtUartGpioPad;
    *VUartForCnviBtPad = mPchHVUartForCnviBtGpioPad;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBtUartExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_C8,  GpioPadModeNative2}, // CNV_BT_UART_0_RXD
  {GPIO_ICL_H_GPP_C9,  GpioPadModeNative2}, // CNV_BT_UART_0_TXD
  {GPIO_ICL_H_GPP_C10, GpioPadModeNative2}, // CNV_BT_UART_0_RTS
  {GPIO_ICL_H_GPP_C11, GpioPadModeNative2}  // CNV_BT_UART_0_CTS
};

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
    *NativePinsTable = mPchHCnviBtUartExternalPads;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviBtI2sGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO30, // vCNV_BT_I2S_BCLK
  GPIO_ICL_H_VGPIO31, // vCNV_BT_I2S_WS_SYNC
  GPIO_ICL_H_VGPIO32, // vCNV_BT_I2S_SDO
  GPIO_ICL_H_VGPIO33  // vCNV_BT_I2S_SDI
};


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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVSspForCnviBtGpioPad[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO34, // vSSP2_SCLK
  GPIO_ICL_H_VGPIO35, // vSSP2_SFRM
  GPIO_ICL_H_VGPIO36, // vSSP2_TXD
  GPIO_ICL_H_VGPIO37  // vSSP2_RXD
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
  } else if (IsPchN ()) {
    *VCnviBtI2sPad = mPchNVCnviBtI2sGpioPad;
    *VSspForCnviBtPad = mPchNVSspForCnviBtGpioPad;
  } else {
    *VCnviBtI2sPad = mPchHVCnviBtI2sGpioPad;
    *VSspForCnviBtPad = mPchHVSspForCnviBtGpioPad;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBtI2sExternalPads[PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_D5,  GpioPadModeNative2}, // CNV_BT_I2S_WS_SYNC
  {GPIO_ICL_H_GPP_D6,  GpioPadModeNative2}, // CNV_BT_I2S_BCLK
  {GPIO_ICL_H_GPP_D7,  GpioPadModeNative2}, // CNV_BT_I2S_SDI
  {GPIO_ICL_H_GPP_D8,  GpioPadModeNative2}  // CNV_BT_I2S_SDO
};

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
    *NativePinsTable = mPchHCnviBtI2sExternalPads;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO10, // vCNV_MFUART1_TXD
  GPIO_ICL_H_VGPIO11, // vCNV_MFUART1_RXD
  GPIO_ICL_H_VGPIO12, // vCNV_MFUART1_CTS_B
  GPIO_ICL_H_VGPIO13  // vCNV_MFUART1_RTS_B
};


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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHVUartForCnviMfUart1GpioPad[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  GPIO_ICL_H_VGPIO22, // vISH_UART0_TXD
  GPIO_ICL_H_VGPIO23, // vISH_UART0_RXD
  GPIO_ICL_H_VGPIO24, // vISH_UART0_CTS_B
  GPIO_ICL_H_VGPIO25  // vISH_UART0_RTS_B
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
  } else if (IsPchN ()) {
    *VCnviMfUart1Pad = mPchNVCnviMfUart1GpioPad;
    *VUartForCnviMfUart1Pad = mPchNVUartForCnviMfUart1GpioPad;
  } else {
    *VCnviMfUart1Pad = mPchHVCnviMfUart1GpioPad;
    *VUartForCnviMfUart1Pad = mPchHVUartForCnviMfUart1GpioPad;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviMfUart1ExternalPads[PCH_GPIO_CNVI_UART_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_C12, GpioPadModeNative3}, // CNV_MFUART1_RXD
  {GPIO_ICL_H_GPP_C13, GpioPadModeNative3}, // CNV_MFUART1_TXD
  {GPIO_ICL_H_GPP_C14, GpioPadModeNative3}, // CNV_MFUART1_RTS
  {GPIO_ICL_H_GPP_C15, GpioPadModeNative3}  // CNV_MFUART1_CTS
};

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
    *NativePinsTable = mPchHCnviMfUart1ExternalPads;
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
    return GPIO_ICL_H_VGPIO0;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchHCnviBriRgiGpioPad[PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS] =
{
  {GPIO_ICL_H_GPP_J2,  GpioPadModeNative1}, // CNV_BRI_DT
  {GPIO_ICL_H_GPP_J3,  GpioPadModeNative1}, // CNV_BRI_RSP
  {GPIO_ICL_H_GPP_J4,  GpioPadModeNative1}, // CNV_RGI_DT
  {GPIO_ICL_H_GPP_J5,  GpioPadModeNative1}  // CNV_RGI_RSP
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
  } else if (IsPchN ()) {
    *NativePinsTable = mPchNCnviBriRgiGpioPad;
  } else {
    *NativePinsTable = mPchHCnviBriRgiGpioPad;
  }
}

#ifndef MRC_MINIBIOS_BUILD
GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchLpImguClkOutGpioPad[SA_GPIO_IMGUCLK_NUMBER_OF_PINS] =
{
  {GPIO_ICL_LP_GPP_D4,   GpioPadModeNative1}, // IMGCLKOUT_0
  {GPIO_ICL_LP_GPP_H20,  GpioPadModeNative1}, // IMGCLKOUT_1
  {GPIO_ICL_LP_GPP_H21,  GpioPadModeNative1}, // IMGCLKOUT_2
  {GPIO_ICL_LP_GPP_H22,  GpioPadModeNative1}, // IMGCLKOUT_3
  {GPIO_ICL_LP_GPP_H23,  GpioPadModeNative1}  // IMGCLKOUT_4
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD_NATIVE_FUNCTION mPchNImguClkOutGpioPad[SA_GPIO_IMGUCLK_NUMBER_OF_PINS] =
{
  {GPIO_ICL_N_GPP_E0,  GpioPadModeNative2}, // IMGCLKOUT_0
  {GPIO_ICL_N_GPP_E2,  GpioPadModeNative1}, // IMGCLKOUT_1
  {GPIO_ICL_N_GPP_E4,  GpioPadModeNative1}, // IMGCLKOUT_2
  {GPIO_ICL_N_GPP_E6,  GpioPadModeNative1}, // IMGCLKOUT_3
  {GPIO_ICL_N_GPP_E12, GpioPadModeNative1}  // IMGCLKOUT_4
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
    return GPIO_ICL_H_GPD3;
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

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_PAD mPchHTypeCSbuGpioPad[] =
{
  GPIO_ICL_H_GPP_G12, // BSSB_LS0_RX
  GPIO_ICL_H_GPP_G13, // BSSB_LS0_TX
  GPIO_ICL_H_GPP_G14, // BSSB_LS1_RX
  GPIO_ICL_H_GPP_G15, // BSSB_LS1_TX
  GPIO_ICL_H_GPP_G8,  // BSSB_LS2_RX
  GPIO_ICL_H_GPP_G9,  // BSSB_LS2_TX
  GPIO_ICL_H_GPP_G10, // BSSB_LS3_RX
  GPIO_ICL_H_GPP_G11  // BSSB_LS3_TX
};

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
  UINT32              SbuPadNum;
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
    SbuPadNum = ARRAY_SIZE (mPchLpTypeCSbuGpioPad) / 2;
  } else if (IsPchN ()) {
    GpioSbuPadTable = mPchNTypeCSbuGpioPad;
    SbuPadNum = ARRAY_SIZE (mPchNTypeCSbuGpioPad) / 2;
  } else {
    GpioSbuPadTable = mPchHTypeCSbuGpioPad;
    SbuPadNum = ARRAY_SIZE (mPchHTypeCSbuGpioPad) / 2;
  }
  //
  // For USB-C SBU function usage, the pins must be routed to a Type-C connector.
  // BIOS needs to configure the pin to high-Z/open circuit (select GPIO function with TX disable) if debug is disabled,
  // that would guarantees PCH GPIO is not driving to external device.
  // Having 3.3V setting in high-Z/open circuit mode is just a precaution to protect the GPIO in case the external device is driving into PCH.
  //
  for (PortIndex = 0; PortIndex < SbuPadNum; PortIndex++) {
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
