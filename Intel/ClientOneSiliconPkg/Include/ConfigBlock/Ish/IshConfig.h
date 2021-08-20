/** @file
  ISH policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _ISH_CONFIG_H_
#define _ISH_CONFIG_H_

#define ISH_PREMEM_CONFIG_REVISION 1
#define ISH_CONFIG_REVISION 1
extern EFI_GUID gIshPreMemConfigGuid;
extern EFI_GUID gIshConfigGuid;

#pragma pack (push,1)

/**
  ISH GPIO settings
**/
typedef struct {
  /**
    GPIO signals pin muxing settings. If signal can be enable only on a single pin
    then this parameter should be set to 0. Refer to GPIO_*_MUXING_ISH_*x_* in GpioPins*.h
    for supported settings on a given platform
  **/
  UINT32   PinMux;                      ///< GPIO Pin mux configuration. Refer to GPIO_*_MUXING_ISH_*x_MOSI_*
  /**
    GPIO Pads Internal Termination.
    For more information please see Platform Design Guide.
    Check GPIO_ELECTRICAL_CONFIG for reference
  **/
  UINT32   PadTermination;
} ISH_GPIO_CONFIG;

/**
  SPI signals settings.
**/
typedef struct {
  ISH_GPIO_CONFIG   Mosi;                        ///< MOSI Pin configuration.
  ISH_GPIO_CONFIG   Miso;                        ///< MISO Pin configuration.
  ISH_GPIO_CONFIG   Clk;                         ///< CLK  Pin configuration.
  ISH_GPIO_CONFIG   Cs[PCH_MAX_ISH_SPI_CS_PINS]; ///< CS   Pin configuration.
} ISH_SPI_PIN_CONFIG;


/**
  UART signals settings.
**/
typedef struct {
  ISH_GPIO_CONFIG   Rx;    ///< RXD Pin configuration.
  ISH_GPIO_CONFIG   Tx;    ///< TXD Pin configuration.
  ISH_GPIO_CONFIG   Rts;   ///< RTS Pin configuration.
  ISH_GPIO_CONFIG   Cts;   ///< CTS Pin configuration.
} ISH_UART_PIN_CONFIG;


/**
  I2C signals settings.
**/
typedef struct {
  ISH_GPIO_CONFIG   Sda;    ///< SDA Pin configuration.
  ISH_GPIO_CONFIG   Scl;    ///< SCL Pin configuration.
} ISH_I2C_PIN_CONFIG;


/**
  Struct contains GPIO pins assigned and signal settings of SPI
**/
typedef struct {
  UINT8               Enable;                            ///< ISH SPI GPIO pins assigned: <b>0: False</b> 1: True
  UINT8               CsEnable[PCH_MAX_ISH_SPI_CS_PINS]; ///< ISH SPI CS pins assigned: <b>0: False</b> 1: True
  UINT16              RsvdField0;                        ///< Reserved field
  ISH_SPI_PIN_CONFIG  PinConfig;
} ISH_SPI;


/**
  Struct contains GPIO pins assigned and signal settings of UART
**/
typedef struct {
  UINT32              Enable      :  1;   ///< ISH UART GPIO pins assigned: <b>0: False</b> 1: True
  UINT32              RsvdBits0   : 31;   ///< Reserved Bits
  ISH_UART_PIN_CONFIG PinConfig;
} ISH_UART;

/**
  Struct contains GPIO pins assigned and signal settings of I2C
**/
typedef struct {
  UINT32              Enable      :  1;   ///< ISH I2C GPIO pins assigned: <b>0: False</b> 1: True
  UINT32              RsvdBits0   : 31;   ///< Reserved Bits
  ISH_I2C_PIN_CONFIG  PinConfig;
} ISH_I2C;

/**
  Struct contains GPIO pins assigned and signal settings of GP
**/
typedef struct {
  UINT32           Enable      :  1;   ///< ISH GP GPIO pins assigned: <b>0: False</b> 1: True
  UINT32           RsvdBits0   : 31;   ///< Reserved Bits
  ISH_GPIO_CONFIG  PinConfig;
} ISH_GP;

///
/// The ISH_CONFIG block describes Integrated Sensor Hub device.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;               ///< Config Block Header
  ISH_SPI  Spi[PCH_MAX_ISH_SPI_CONTROLLERS];
  ISH_UART Uart[PCH_MAX_ISH_UART_CONTROLLERS];
  ISH_I2C  I2c[PCH_MAX_ISH_I2C_CONTROLLERS];
  ISH_GP   Gp[PCH_MAX_ISH_GP_PINS];

  UINT32   PdtUnlock            :  1;         ///< ISH PDT Unlock Msg: <b>0: False</b> 1: True
  UINT32   RsvdBits0            : 31;         ///< Reserved Bits

} ISH_CONFIG;

///
/// Premem Policy for Integrated Sensor Hub device.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;     ///< Config Block Header
  /**
    ISH Controler 0: Disable; <b>1: Enable</b>.
    For Desktop sku, the ISH POR should be disabled. <b> 0:Disable </b>.
  **/
  UINT32    Enable          :  1;
  UINT32    RsvdBits0       : 31;   ///< Reserved Bits
} ISH_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _ISH_CONFIG_H_
