/** @file
  Header file for GPIO Native pads support

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
#ifndef _GPIO_NATIVE_PADS_H_
#define _GPIO_NATIVE_PADS_H_

//
// GpioPad can contain additional information used to provide data on
// native functions. Please refer to description of GPIO_NATIVE_PAD
//
// FFFF CCCC TTTG GGGG TTTT TTTP PPPP PPPP
//
// F - 2^4 = 16,  native function number
// C - 2^4 = 16,  chipset ID
// T - 2^10 = 1024 , abstract type representing native mode of a pad (e.g. SERIALIO_UART2_TX)
// G - 2^5 = 32,  group
// P - 2^9 = 512, pad number
//
// F & T contain additional optional settings used for native pads
//
#define GPIO_NATIVE_PAD_DEF(GpioNativePad, NativeMode, NativeFunction) \
  (GpioNativePad | (NativeMode << 28) | ((NativeFunction & 0x7F) << 9) | ((NativeFunction & 0x380) << 14))

#define GPIO_NATIVE_GET_FUNCTION(GpioNativePad) ((((GpioNativePad) & 0xFE00) >> 9) | (((GpioNativePad) & 0xE00000) >> 14))
#define GPIO_NATIVE_GET_PAD_FN(GpioNativePad)   (((GpioNativePad) >> 28) & 0xF)
#define GPIO_NATIVE_GET_PAD_MODE(GpioNativePad) ((GPIO_NATIVE_GET_PAD_FN(GpioNativePad) << 1) | 1)

//
// Below defines and macros are used to build abstract type
// to help encode native pin information in GPIO_PAD
//

//
// Macro used to define GPIO native function.
// <Min,Max> defines range that can be used to encode given native signal.
// Numbering must be unique and cannot overlap.
// If there are many instances of similar signal (e.g. per controller) the lower
// word will store value for a given instance in the form: Min + Instance
// Upper word (Max) is left untouched and later used for verification
//
#define GPIO_NATIVE_FUNCTION_DEF(Min, Max)             (((Max) << 16) + (Min))
#define GPIO_NATIVE_FUNCTION_GET_MAX(NativeFunction)   (((NativeFunction) >> 16) & 0xFFFF)
#define GPIO_NATIVE_FUNCTION_GET_VALUE(NativeFunction) ((NativeFunction) & 0xFFFF)

//
// GPIO native modes
// Those defines are internal to this header.
// GPIO_FUNCTION_<IP>_<signal>(index) defines should be used by other modules instead.
//
#define GPIO_SERIAL_IO_UART_RX     GPIO_NATIVE_FUNCTION_DEF(1,8)
#define GPIO_SERIAL_IO_UART_TX     GPIO_NATIVE_FUNCTION_DEF(9,16)
#define GPIO_SERIAL_IO_UART_RTS    GPIO_NATIVE_FUNCTION_DEF(17,24)
#define GPIO_SERIAL_IO_UART_CTS    GPIO_NATIVE_FUNCTION_DEF(25,31)
#define GPIO_SERIAL_IO_SPI_MOSI    GPIO_NATIVE_FUNCTION_DEF(32,39)
#define GPIO_SERIAL_IO_SPI_MISO    GPIO_NATIVE_FUNCTION_DEF(40,47)
#define GPIO_SERIAL_IO_SPI_CLK     GPIO_NATIVE_FUNCTION_DEF(48,55)
#define GPIO_SERIAL_IO_SPI_CS      GPIO_NATIVE_FUNCTION_DEF(56,71)
#define GPIO_ISH_GP                GPIO_NATIVE_FUNCTION_DEF(80,143)
#define GPIO_ISH_UART_RX           GPIO_NATIVE_FUNCTION_DEF(144,151)
#define GPIO_ISH_UART_TX           GPIO_NATIVE_FUNCTION_DEF(152,159)
#define GPIO_ISH_UART_RTS          GPIO_NATIVE_FUNCTION_DEF(160,167)
#define GPIO_ISH_UART_CTS          GPIO_NATIVE_FUNCTION_DEF(168,175)
#define GPIO_ISH_SPI_MOSI          GPIO_NATIVE_FUNCTION_DEF(184,191)
#define GPIO_ISH_SPI_MISO          GPIO_NATIVE_FUNCTION_DEF(192,199)
#define GPIO_ISH_SPI_CLK           GPIO_NATIVE_FUNCTION_DEF(200,207)
#define GPIO_ISH_SPI_CS            GPIO_NATIVE_FUNCTION_DEF(208,223)
#define GPIO_ISH_I2C_SCL           GPIO_NATIVE_FUNCTION_DEF(232,239)
#define GPIO_ISH_I2C_SDA           GPIO_NATIVE_FUNCTION_DEF(240,247)
#define GPIO_THC_SPI_INT           GPIO_NATIVE_FUNCTION_DEF(248,251)
#define GPIO_HDA_BCLK              GPIO_NATIVE_FUNCTION_DEF(252,252)
#define GPIO_HDA_RSTB              GPIO_NATIVE_FUNCTION_DEF(253,253)
#define GPIO_HDA_SYNC              GPIO_NATIVE_FUNCTION_DEF(254,254)
#define GPIO_HDA_SDO               GPIO_NATIVE_FUNCTION_DEF(255,255)
#define GPIO_HDA_SDI_0             GPIO_NATIVE_FUNCTION_DEF(256,256)
#define GPIO_HDA_SDI_1             GPIO_NATIVE_FUNCTION_DEF(257,257)
#define GPIO_DMIC_DATA             GPIO_NATIVE_FUNCTION_DEF(258,261)
#define GPIO_DMIC_CLKA             GPIO_NATIVE_FUNCTION_DEF(262,265)
#define GPIO_DMIC_CLKB             GPIO_NATIVE_FUNCTION_DEF(266,269)
#define GPIO_DDSP_HPD0             GPIO_NATIVE_FUNCTION_DEF(270,285)
#define GPIO_PANEL_AVDD_EN         GPIO_NATIVE_FUNCTION_DEF(286,289)
#define GPIO_PANEL_BKLTEN          GPIO_NATIVE_FUNCTION_DEF(290,293)
#define GPIO_PANEL_BKLTCTL         GPIO_NATIVE_FUNCTION_DEF(294,297)
#define GPIO_PANEL_RESET           GPIO_NATIVE_FUNCTION_DEF(298,301)
#define GPIO_PANEL_AVEE_EN         GPIO_NATIVE_FUNCTION_DEF(302,305)
#define GPIO_PANEL_VIO_EN          GPIO_NATIVE_FUNCTION_DEF(306,309)
#define GPIO_PANEL_HPD             GPIO_NATIVE_FUNCTION_DEF(310,313)
#define GPIO_PANEL_TE_EN           GPIO_NATIVE_FUNCTION_DEF(314,317)
#define GPIO_HDMI_GMBUS_SCL        GPIO_NATIVE_FUNCTION_DEF(318,325)
#define GPIO_HDMI_GMBUS_SDA        GPIO_NATIVE_FUNCTION_DEF(326,333)
#define GPIO_ISH_I3C_SCL           GPIO_NATIVE_FUNCTION_DEF(334,335)
#define GPIO_ISH_I3C_SDA           GPIO_NATIVE_FUNCTION_DEF(336,337)
#define GPIO_SERIAL_IO_I2C_SCL     GPIO_NATIVE_FUNCTION_DEF(338,353)
#define GPIO_SERIAL_IO_I2C_SDA     GPIO_NATIVE_FUNCTION_DEF(354,369)
#define GPIO_CNVI_RF_RESET         GPIO_NATIVE_FUNCTION_DEF(370,370)
#define GPIO_CNVI_CLKREQ           GPIO_NATIVE_FUNCTION_DEF(371,371)
#define GPIO_SD_PWR_EN_B           GPIO_NATIVE_FUNCTION_DEF(372,372)
#define GPIO_SD_CMD                GPIO_NATIVE_FUNCTION_DEF(373,373)
#define GPIO_SD_DATA               GPIO_NATIVE_FUNCTION_DEF(374,377)
#define GPIO_SD_CDB                GPIO_NATIVE_FUNCTION_DEF(378,378)
#define GPIO_SD_CLK                GPIO_NATIVE_FUNCTION_DEF(379,379)
#define GPIO_SD_WP                 GPIO_NATIVE_FUNCTION_DEF(380,380)
#define GPIO_SD_1P8_EN             GPIO_NATIVE_FUNCTION_DEF(381,381)
#define GPIO_SD_CLK_FB             GPIO_NATIVE_FUNCTION_DEF(382,382)
#define GPIO_EMMC_CMD              GPIO_NATIVE_FUNCTION_DEF(383,383)
#define GPIO_EMMC_DATA             GPIO_NATIVE_FUNCTION_DEF(384,391)
#define GPIO_EMMC_RCLK             GPIO_NATIVE_FUNCTION_DEF(392,392)
#define GPIO_EMMC_CLK              GPIO_NATIVE_FUNCTION_DEF(393,393)
#define GPIO_EMMC_RESETB           GPIO_NATIVE_FUNCTION_DEF(394,394)
#define GPIO_PSE_I2S_RX            GPIO_NATIVE_FUNCTION_DEF(395,402)
#define GPIO_PSE_I2S_TX            GPIO_NATIVE_FUNCTION_DEF(403,410)
#define GPIO_PSE_I2S_CLK           GPIO_NATIVE_FUNCTION_DEF(411,418)
#define GPIO_PSE_I2S_SFRM          GPIO_NATIVE_FUNCTION_DEF(419,426)
#define GPIO_PSE_PWM               GPIO_NATIVE_FUNCTION_DEF(427,442)
#define GPIO_PSE_UART_RX           GPIO_NATIVE_FUNCTION_DEF(443,450)
#define GPIO_PSE_UART_TX           GPIO_NATIVE_FUNCTION_DEF(451,458)
#define GPIO_PSE_UART_RTS          GPIO_NATIVE_FUNCTION_DEF(459,466)
#define GPIO_PSE_UART_CTS          GPIO_NATIVE_FUNCTION_DEF(467,474)
#define GPIO_PSE_HSUART_DE         GPIO_NATIVE_FUNCTION_DEF(475,482)
#define GPIO_PSE_HSUART_RE         GPIO_NATIVE_FUNCTION_DEF(483,490)
#define GPIO_PSE_HSUART_EN         GPIO_NATIVE_FUNCTION_DEF(491,498)
#define GPIO_PSE_QEP_A             GPIO_NATIVE_FUNCTION_DEF(499,502)
#define GPIO_PSE_QEP_B             GPIO_NATIVE_FUNCTION_DEF(503,506)
#define GPIO_PSE_QEP_I             GPIO_NATIVE_FUNCTION_DEF(507,510)
#define GPIO_PSE_I2C_SCL           GPIO_NATIVE_FUNCTION_DEF(511,518)
#define GPIO_PSE_I2C_SDA           GPIO_NATIVE_FUNCTION_DEF(519,526)
#define GPIO_PSE_SPI_MOSI          GPIO_NATIVE_FUNCTION_DEF(527,534)
#define GPIO_PSE_SPI_MISO          GPIO_NATIVE_FUNCTION_DEF(535,542)
#define GPIO_PSE_SPI_CLK           GPIO_NATIVE_FUNCTION_DEF(543,550)
#define GPIO_PSE_SPI_CS            GPIO_NATIVE_FUNCTION_DEF(551,566)
#define GPIO_PSE_ADC               GPIO_NATIVE_FUNCTION_DEF(567,582)
#define GPIO_PSE_CAN_RX            GPIO_NATIVE_FUNCTION_DEF(583,584)
#define GPIO_PSE_CAN_TX            GPIO_NATIVE_FUNCTION_DEF(585,586)
#define GPIO_PSE_TGPIO             GPIO_NATIVE_FUNCTION_DEF(587,646)
#define GPIO_EMMC_HIP_MON          GPIO_NATIVE_FUNCTION_DEF(647,647)
#define GPIO_THC_CLK_LOOPBACK      GPIO_NATIVE_FUNCTION_DEF(648,649)
#define GPIO_PSE_GBE0              GPIO_NATIVE_FUNCTION_DEF(650,667)
#define GPIO_PSE_GBE1              GPIO_NATIVE_FUNCTION_DEF(668,685)
#define GPIO_PSE_JTAG              GPIO_NATIVE_FUNCTION_DEF(686,692)

//
// Serial IO UART
//
#define GPIO_SERIAL_IO_UART_RANGE  8  // Number of SerialIo UARTx controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_SERIAL_IO_UART_RX(UartDev)  (GPIO_SERIAL_IO_UART_RX + ((UINT32)UartDev))
#define GPIO_FUNCTION_SERIAL_IO_UART_TX(UartDev)  (GPIO_SERIAL_IO_UART_TX + ((UINT32)UartDev))
#define GPIO_FUNCTION_SERIAL_IO_UART_RTS(UartDev) (GPIO_SERIAL_IO_UART_RTS + ((UINT32)UartDev))
#define GPIO_FUNCTION_SERIAL_IO_UART_CTS(UartDev) (GPIO_SERIAL_IO_UART_CTS + ((UINT32)UartDev))

//
// Serial IO SPI
//
#define GPIO_SERIAL_IO_SPI_RANGE  8  // Number of SerialIo SPIx controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_SERIAL_IO_SPI_MOSI(SpiDev)      (GPIO_SERIAL_IO_SPI_MOSI + ((UINT32)SpiDev))
#define GPIO_FUNCTION_SERIAL_IO_SPI_MISO(SpiDev)      (GPIO_SERIAL_IO_SPI_MISO + ((UINT32)SpiDev))
#define GPIO_FUNCTION_SERIAL_IO_SPI_CLK(SpiDev)       (GPIO_SERIAL_IO_SPI_CLK + ((UINT32)SpiDev))
#define GPIO_FUNCTION_SERIAL_IO_SPI_CS(SpiDev, CsNum) (GPIO_SERIAL_IO_SPI_CS + ((UINT32)SpiDev) + ((UINT32)CsNum) * GPIO_SERIAL_IO_SPI_RANGE)

//
// Serial IO I2C
//
#define GPIO_SERIAL_IO_I2C_RANGE  16  // Number of SerialIo I2Cx controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_SERIAL_IO_I2C_SCL(I2cDev) (GPIO_SERIAL_IO_I2C_SCL + ((UINT32)I2cDev))
#define GPIO_FUNCTION_SERIAL_IO_I2C_SDA(I2cDev) (GPIO_SERIAL_IO_I2C_SDA + ((UINT32)I2cDev))

//
// ISH GP
//
#define GPIO_ISH_GP_RANGE  64  // Number of ISH GP pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_ISH_GP(GpNum) (GPIO_ISH_GP + ((UINT32)GpNum))

//
// ISH UART
//
#define GPIO_ISH_UART_RANGE  8  // Number of ISH UART controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_ISH_UART_RX(UartDev)  (GPIO_ISH_UART_RX + ((UINT32)UartDev))
#define GPIO_FUNCTION_ISH_UART_TX(UartDev)  (GPIO_ISH_UART_TX + ((UINT32)UartDev))
#define GPIO_FUNCTION_ISH_UART_RTS(UartDev) (GPIO_ISH_UART_RTS + ((UINT32)UartDev))
#define GPIO_FUNCTION_ISH_UART_CTS(UartDev) (GPIO_ISH_UART_CTS + ((UINT32)UartDev))

//
// ISH SPI
//
#define GPIO_ISH_SPI_RANGE  8  // Number of ISH SPI controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_ISH_SPI_MOSI(SpiDev)      (GPIO_ISH_SPI_MOSI + ((UINT32)SpiDev))
#define GPIO_FUNCTION_ISH_SPI_MISO(SpiDev)      (GPIO_ISH_SPI_MISO + ((UINT32)SpiDev))
#define GPIO_FUNCTION_ISH_SPI_CLK(SpiDev)       (GPIO_ISH_SPI_CLK + ((UINT32)SpiDev))
#define GPIO_FUNCTION_ISH_SPI_CS(SpiDev, CsNum) (GPIO_ISH_SPI_CS + ((UINT32)SpiDev) + ((UINT32)CsNum) * GPIO_ISH_SPI_RANGE)

//
// ISH I2C
//
#define GPIO_ISH_I2C_RANGE  8  // Number of ISH I2C controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_ISH_I2C_SCL(I2cDev) (GPIO_ISH_I2C_SCL + ((UINT32)I2cDev))
#define GPIO_FUNCTION_ISH_I2C_SDA(I2cDev) (GPIO_ISH_I2C_SDA + ((UINT32)I2cDev))

//
// ISH I3C
//
#define GPIO_ISH_I3C_RANGE  2  // Number of ISH I3C controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_ISH_I3C_SCL(I3cDev) (GPIO_ISH_I3C_SCL + ((UINT32)I3cDev))
#define GPIO_FUNCTION_ISH_I3C_SDA(I3cDev) (GPIO_ISH_I3C_SDA + ((UINT32)I3cDev))

//
// SD Card
//
#define GPIO_FUNCTION_SD_PWR_EN_B           GPIO_SD_PWR_EN_B
#define GPIO_FUNCTION_SD_CMD                GPIO_SD_CMD
#define GPIO_FUNCTION_SD_DATA(Index)        (GPIO_SD_DATA + ((UINT32)Index))
#define GPIO_FUNCTION_SD_CDB                GPIO_SD_CDB
#define GPIO_FUNCTION_SD_CLK                GPIO_SD_CLK
#define GPIO_FUNCTION_SD_WP                 GPIO_SD_WP
#define GPIO_FUNCTION_SD_1P8_EN             GPIO_SD_1P8_EN
#define GPIO_FUNCTION_SD_CLK_FB             GPIO_SD_CLK_FB

//
// EMMC
//
#define GPIO_FUNCTION_EMMC_CMD              GPIO_EMMC_CMD
#define GPIO_FUNCTION_EMMC_DATA(Index)      (GPIO_EMMC_DATA + ((UINT32)Index))
#define GPIO_FUNCTION_EMMC_RCLK             GPIO_EMMC_RCLK
#define GPIO_FUNCTION_EMMC_CLK              GPIO_EMMC_CLK
#define GPIO_FUNCTION_EMMC_RESETB           GPIO_EMMC_RESETB
#define GPIO_FUNCTION_EMMC_HIP_MON          GPIO_EMMC_HIP_MON

//
// PSE I2S
//
#define GPIO_PSE_I2S_RANGE  8  // Number of PSE I2S controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_I2S_RX(I2sDev)   (GPIO_PSE_I2S_RX + ((UINT32)I2sDev))
#define GPIO_FUNCTION_PSE_I2S_TX(I2sDev)   (GPIO_PSE_I2S_TX + ((UINT32)I2sDev))
#define GPIO_FUNCTION_PSE_I2S_CLK(I2sDev)  (GPIO_PSE_I2S_CLK + ((UINT32)I2sDev))
#define GPIO_FUNCTION_PSE_I2S_SFRM(I2sDev) (GPIO_PSE_I2S_SFRM + ((UINT32)I2sDev))

//
// PSE PWM
//
#define GPIO_PSE_PWM_RANGE  16  // Number of PSE PWM pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_PWM(PwmNum) (GPIO_PSE_PWM + ((UINT32)PwmNum))

//
// PSE UART
//
#define GPIO_PSE_UART_RANGE  8  // Number of PSE UART controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_UART_RX(UartDev)  (GPIO_PSE_UART_RX + ((UINT32)UartDev))
#define GPIO_FUNCTION_PSE_UART_TX(UartDev)  (GPIO_PSE_UART_TX + ((UINT32)UartDev))
#define GPIO_FUNCTION_PSE_UART_RTS(UartDev) (GPIO_PSE_UART_RTS + ((UINT32)UartDev))
#define GPIO_FUNCTION_PSE_UART_CTS(UartDev) (GPIO_PSE_UART_CTS + ((UINT32)UartDev))

//
// PSE HSUART
//
#define GPIO_PSE_HSUART_RANGE  8  // Number of PSE HSUART controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_HSUART_DE(HsuartDev)  (GPIO_PSE_HSUART_DE + ((UINT32)HsuartDev))
#define GPIO_FUNCTION_PSE_HSUART_RE(HsuartDev)  (GPIO_PSE_HSUART_RE + ((UINT32)HsuartDev))
#define GPIO_FUNCTION_PSE_HSUART_EN(HsuartDev)  (GPIO_PSE_HSUART_EN + ((UINT32)HsuartDev))

//
// PSE QEP
//
#define GPIO_PSE_QEP_RANGE  4  // Number of PSE QEP controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_QEP_A(QepDev)  (GPIO_PSE_QEP_A + ((UINT32)QepDev))
#define GPIO_FUNCTION_PSE_QEP_B(QepDev)  (GPIO_PSE_QEP_B + ((UINT32)QepDev))
#define GPIO_FUNCTION_PSE_QEP_I(QepDev)  (GPIO_PSE_QEP_I + ((UINT32)QepDev))

//
// PSE I2C
//
#define GPIO_PSE_I2C_RANGE  8  // Number of PSE I2C controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_I2C_SCL(I2cDev) (GPIO_PSE_I2C_SCL + ((UINT32)I2cDev))
#define GPIO_FUNCTION_PSE_I2C_SDA(I2cDev) (GPIO_PSE_I2C_SDA + ((UINT32)I2cDev))

//
// PSE SPI
//
#define GPIO_PSE_SPI_RANGE  8  // Number of PSE SPI controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_SPI_MOSI(SpiDev)      (GPIO_PSE_SPI_MOSI + ((UINT32)SpiDev))
#define GPIO_FUNCTION_PSE_SPI_MISO(SpiDev)      (GPIO_PSE_SPI_MISO + ((UINT32)SpiDev))
#define GPIO_FUNCTION_PSE_SPI_CLK(SpiDev)       (GPIO_PSE_SPI_CLK + ((UINT32)SpiDev))
#define GPIO_FUNCTION_PSE_SPI_CS(SpiDev, CsNum) (GPIO_PSE_SPI_CS + ((UINT32)SpiDev) + ((UINT32)CsNum) * GPIO_PSE_SPI_RANGE)

//
// PSE ADC
//
#define GPIO_PSE_ADC_RANGE  16  // Number of PSE ADC pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_ADC(AdcNum) (GPIO_PSE_ADC + ((UINT32)AdcNum))

//
// PSE CAN
//
#define GPIO_PSE_CAM_RANGE  2  // Number of PSE CAN controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_CAN_RX(CanDev)  (GPIO_PSE_CAN_RX + ((UINT32)CanDev))
#define GPIO_FUNCTION_PSE_CAN_TX(CanDev)  (GPIO_PSE_CAN_TX + ((UINT32)CanDev))

//
// PSE TGPIO
//
#define GPIO_PSE_TGPIO_RANGE 60 // Number of PSE TGPIO controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_TGPIO(TgpioPinNum) (GPIO_PSE_TGPIO + ((UINT32)TgpioPinNum))

//
// PSE GBE0
//
#define GPIO_PSE_GBE0_RANGE 18 // Number of PSE GBE pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_GBE0(GbePinNum) (GPIO_PSE_GBE0 + ((UINT32)GbePinNum))

//
// PSE GBE1
//
#define GPIO_PSE_GBE1_RANGE 18 // Number of PSE GBE pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_GBE1(GbePinNum) (GPIO_PSE_GBE1 + ((UINT32)GbePinNum))

//
// PSE JTAG
//
#define GPIO_PSE_JTAG_RANGE 7 // Number of PSE JTAG pins supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PSE_JTAG(JtagPinNum) (GPIO_PSE_JTAG + ((UINT32)JtagPinNum))

//
// THC SPI
//
#define GPIO_THC_SPI_RANGE  4  // Number of THC SPI controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_THC_SPI_INT(SpiDev) (GPIO_THC_SPI_INT + ((UINT32)SpiDev))
#define GPIO_FUNCTION_THC_CLK_LOOPBACK(SpiDev) (GPIO_THC_CLK_LOOPBACK + ((UINT32)SpiDev))

//
// HDA
//
#define GPIO_FUNCTION_HDA_BCLK      GPIO_HDA_BCLK
#define GPIO_FUNCTION_HDA_RSTB      GPIO_HDA_RSTB
#define GPIO_FUNCTION_HDA_SYNC      GPIO_HDA_SYNC
#define GPIO_FUNCTION_HDA_SDO       GPIO_HDA_SDO
#define GPIO_FUNCTION_HDA_SDI_0     GPIO_HDA_SDI_0
#define GPIO_FUNCTION_HDA_SDI_1     GPIO_HDA_SDI_1

//
// DMIC
//
#define GPIO_DMIC_RANGE  4  // Number of DMIC controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_DMIC_DATA(DmicDev) (GPIO_DMIC_DATA  + ((UINT32)DmicDev))
#define GPIO_FUNCTION_DMIC_CLKA(DmicDev) (GPIO_DMIC_CLKA  + ((UINT32)DmicDev))
#define GPIO_FUNCTION_DMIC_CLKB(DmicDev) (GPIO_DMIC_CLKB  + ((UINT32)DmicDev))
#define GPIO_FUNCTION_DMIC_CLK(DmicDev)  (GPIO_DMIC_CLKA  + ((UINT32)DmicDev)) // If there is no split between channel A/B use A range for such Clocks


//
// DDSP HPD
//
#define GPIO_DDSP_HPD_RANGE  16  // Number of DDSP HPD supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_DDSP_HPD(HpdIndex) \
  (HpdIndex > 7) ? GPIO_DDSP_HPD0 + 8 + (HpdIndex) - 'A' : GPIO_DDSP_HPD0 + HpdIndex

//
// HDMI_GMBUS
//
#define GPIO_HDMI_GMBUS_RANGE  8  // Number of HDMI GMBUS supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_HDMI_SCL(DdiPort) (GPIO_HDMI_GMBUS_SCL + ((UINT32)DdiPort))
#define GPIO_FUNCTION_HDMI_SDA(DdiPort) (GPIO_HDMI_GMBUS_SDA + ((UINT32)DdiPort))

//
// Panel
//
#define GPIO_PANEL_RANGE  4  // Number of Panel controllers supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_PANEL_AVDD_EN(PanelDev) (GPIO_PANEL_AVDD_EN + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_BKLTEN(PanelDev)  (GPIO_PANEL_BKLTEN + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_BKLTCTL(PanelDev) (GPIO_PANEL_BKLTCTL + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_RESET(PanelDev)   (GPIO_PANEL_RESET + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_AVEE_EN(PanelDev) (GPIO_PANEL_AVEE_EN + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_VIO_EN(PanelDev)  (GPIO_PANEL_VIO_EN + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_HPD(PanelDev)     (GPIO_PANEL_HPD + ((UINT32)PanelDev))
#define GPIO_FUNCTION_PANEL_TE_EN(PanelDev)   (GPIO_PANEL_TE_EN + ((UINT32)PanelDev))

//
// CNVi RF RESET
//
#define GPIO_CNVI_RF_RESET_RANGE 1 // Number of CNVi RF RESET instances supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_CNVI_RF_RESET GPIO_CNVI_RF_RESET

//
// CNVi CLKREQ
//
#define GPIO_CNVI_CLKREQ_RANGE 1   // Number of CNVi CLKREQ instances supported in GPIO_NATIVE_PAD encoding

#define GPIO_FUNCTION_CNVI_CLKREQ GPIO_CNVI_CLKREQ

#endif // _GPIO_NATIVE_PADS_H_
