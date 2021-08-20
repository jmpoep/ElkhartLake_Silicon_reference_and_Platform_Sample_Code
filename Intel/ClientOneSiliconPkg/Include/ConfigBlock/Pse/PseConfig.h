/** @file
  PSE policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#ifndef _PSE_CONFIG_H_
#define _PSE_CONFIG_H_

#define PSE_PREMEM_CONFIG_REVISION 1
#define PSE_CONFIG_REVISION        1

#define OWNER_SHIP_NAME_MAX        16
#define INTR_DELIVERY_NAME_MAX     16

extern EFI_GUID gPsePreMemConfigGuid;
extern EFI_GUID gPseConfigGuid;

#pragma pack (push,1)

typedef enum {
  NONE_OWNED = 0,
  PSE_OWNED  = 1,
  HOST_OWNED = 2
} PSE_IP_OWNERSHIP;

typedef enum {
  NONTGPIO,
  TOP20,
  LOWER20,
  MID20
} PSE_TGPIO_PIN_ALLOCATION;

typedef struct {
  UINT8  Name[OWNER_SHIP_NAME_MAX];
  UINT8  ConfigValue;
} DEVICE_OWNERSHIP;

typedef struct {
  UINT8  Name[INTR_DELIVERY_NAME_MAX];
  UINT8  ConfigValue;
} INTR_DELIVERY_ROUTE;

/**
  SPI signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_SPIx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Mosi;                        ///< MOSI Pin mux configuration. Refer to GPIO_*_MUXING_PSE_SPIx_MOSI_*
  UINT32   Miso;                        ///< MISO Pin mux configuration. Refer to GPIO_*_MUXING_PSE_SPIx_MISO_*
  UINT32   Clk;                         ///< CLK  Pin mux configuration. Refer to GPIO_*_MUXING_PSE_SPIx_CLK_*
  UINT32   Cs[PCH_MAX_PSE_SPI_CS_PINS]; ///< CS   Pin mux configuration. Refer to GPIO_*_MUXING_PSE_SPIx_CS_*
} PSE_SPI_PIN_MUX;

/**
  UART signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_UARTx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Rx;    ///< RXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_UARTx_RXD_*
  UINT32   Tx;    ///< TXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_UARTx_TXD_*
  UINT32   Rts;   ///< RTS Pin mux configuration. Refer to GPIO_*_MUXING_PSE_UARTx_RTS_*
  UINT32   Cts;   ///< CTS Pin mux configuration. Refer to GPIO_*_MUXING_PSE_UARTx_CTS_*
} PSE_UART_PIN_MUX;

/**
  I2C signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_I2Cx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Sda;    ///< SDA Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Cx_SDA_*
  UINT32   Scl;    ///< SCL Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Cx_SCL_*
} PSE_I2C_PIN_MUX;

/**
  I2S signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_I2Sx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Rx;    ///< RXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Sx_RXD_*
  UINT32   Tx;    ///< TXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Sx_TXD_*
  UINT32   Clk;   ///< CLK Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Sx_CLK_*
  UINT32   Sfrm;  ///< SFRM Pin mux configuration. Refer to GPIO_*_MUXING_PSE_I2Sx_SFRM_*
} PSE_I2S_PIN_MUX;

/**
  HSUART signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_HSUARTx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   De;    ///< DE Pin mux configuration. Refer to GPIO_*_MUXING_PSE_HSUARTx_DE_*
  UINT32   Re;    ///< RE Pin mux configuration. Refer to GPIO_*_MUXING_PSE_HSUARTx_RE_*
  UINT32   En;    ///< EC Pin mux configuration. Refer to GPIO_*_MUXING_PSE_HSUARTx_EN_*
} PSE_HSUART_PIN_MUX;

/**
  CAN signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_CANx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Rx;    ///< RXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_CANx_RXD_*
  UINT32   Tx;    ///< TXD Pin mux configuration. Refer to GPIO_*_MUXING_PSE_CANx_TXD_*
} PSE_CAN_PIN_MUX;

/**
  QEP signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_QEPx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   QepA;    ///< QEPA Pin mux configuration. Refer to GPIO_*_MUXING_PSE_QEPx_QEPA_*
  UINT32   QepB;    ///< QEPB Pin mux configuration. Refer to GPIO_*_MUXING_PSE_QEPx_QEPB_*
  UINT32   QepI;    ///< QEPI Pin mux configuration. Refer to GPIO_*_MUXING_PSE_QEPx_QEPI_*
} PSE_QEP_PIN_MUX;

/**
  PWM signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_PWM_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Pin[PCH_MAX_PSE_PWM_CONTROLLER_PINS];   ///< Pin mux configuration. Refer to GPIO_*_MUXING_PSE_PWM_PIN[*]
} PSE_PWM_PIN_MUX;

/**
  ADC signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_ADC_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Pin[PCH_MAX_PSE_ADC_CONTROLLER_PINS];   ///< Pin mux configuration. Refer to GPIO_*_MUXING_PSE_ADC_PIN[*]
} PSE_ADC_PIN_MUX;

/**
  TGPIO signals pin muxing settings. If signal can be enabled only on a single pin
  then this parameter should be set to 0. Refer to GPIO_*_MUXING_PSE_ADC_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Pin[PCH_MAX_PSE_TGPIO_CONTROLLER_PINS];   ///< Pin mux configuration. Refer to GPIO_*_MUXING_PSE_ADC_PIN[*]
} PSE_TGPIO_PIN_MUX;

/**
  Struct contains GPIO pins assigned and Pin Muxing of I2S
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE I2S GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  PSE_I2S_PIN_MUX  PinMux;
} PSE_I2S;

/**
  Struct contains GPIO pins assigned and Pin Muxing of PWM
**/
typedef struct {
  UINT32           OwnerShip          :  2;                      ///< PSE PWM GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;                      ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;                      ///< Reserved Bits
  UINT8            PinEnable[PCH_MAX_PSE_PWM_CONTROLLER_PINS];   ///< Pin set to PWM native function
  PSE_PWM_PIN_MUX  PinMux;
} PSE_PWM;

/**
  Struct contains GPIO pins assigned and Pin Muxing of UART
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE UART GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  PSE_UART_PIN_MUX PinMux;
} PSE_UART;

/**
  Struct contains GPIO pins assigned and Pin Muxing of HSUART
**/
typedef struct {
  UINT32             OwnerShip          :  2;   ///< PSE HSUART GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32             SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32             RsvdBits0          : 29;   ///< Reserved Bits
  PSE_HSUART_PIN_MUX PinMux;
} PSE_HSUART;

/**
  Struct contains GPIO pins assigned and Pin Muxing of QEP
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE QEP GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  PSE_QEP_PIN_MUX  PinMux;
} PSE_QEP;

/**
  Struct contains GPIO pins assigned and Pin Muxing of I2C
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE I2C GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  PSE_I2C_PIN_MUX  PinMux;
} PSE_I2C;

/**
  Struct contains GPIO pins assigned and Pin Muxing of DMA
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE I2C GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
} PSE_DMA;

/**
  Struct contains GPIO pins assigned and Pin Muxing of GBE
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE I2C GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
} PSE_GBE;

/**
  Struct contains GPIO pins assigned and Pin Muxing of SPI
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE SPI GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  UINT32           CsEnable[PCH_MAX_PSE_SPI_CS_PINS]; ///< PSE SPI CS pins assigned: <b>0: False</b> 1: True
  UINT32           RsvdField0;                        ///< Reserved field
  PSE_SPI_PIN_MUX  PinMux;
} PSE_SPI;

/**
  Struct contains GPIO pins assigned and Pin Muxing of ADC
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE ADC GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
} PSE_ADC;

/**
  Struct contains interrupt of LH2PSE
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE LH2PSE Ownership assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
} PSE_LH2PSE;

/**
  Struct contains GPIO pins assigned and Pin Muxing of CAN
**/
typedef struct {
  UINT32           OwnerShip          :  2;   ///< PSE CAN GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32           SbInterruptEnable  :  1;   ///< PSE interrupt: <b>0: MSI</b> 1: SB
  UINT32           RsvdBits0          : 29;   ///< Reserved Bits
  PSE_CAN_PIN_MUX  PinMux;
} PSE_CAN;

/**
  Struct contains GPIO pins assigned and Pin Muxing of Timed GPIO
**/
typedef struct {
  UINT32             OwnerShip      :  2;   ///< PSE TIMED GPIO pins assigned: <b>0: none PSE</b> 1: PSE owned, 2: Host owned
  UINT32             RsvdBits0      : 30;   ///< Reserved Bits
  UINT32             PinAllocation  :  2;   ///< PSE TIMED GPIO lower/mid/top 20 pins
  UINT32             RsvdBits1      : 30;   ///< Reserved Bits
} PSE_TGPIO;

///
/// The PSE_CONFIG block describes Programmable Service Engine device.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;               ///< Config Block Header

  PSE_I2S               I2s[PCH_MAX_PSE_I2S_CONTROLLERS];
  PSE_PWM               Pwm;
  PSE_UART              Uart[PCH_MAX_PSE_UART_CONTROLLERS];
  PSE_HSUART            Hsuart[PCH_MAX_PSE_HSUART_PINS];
  PSE_QEP               Qep[PCH_MAX_PSE_QEP_CONTROLLERS];
  PSE_I2C               I2c[PCH_MAX_PSE_I2C_CONTROLLERS];
  PSE_SPI               Spi[PCH_MAX_PSE_SPI_CONTROLLERS];
  PSE_GBE               Gbe[PCH_MAX_PSE_GBE_CONTROLLERS];
  PSE_DMA               Dma[PCH_MAX_PSE_DMA_CONTROLLERS];
  PSE_ADC               Adc;
  PSE_LH2PSE            Lh2Pse;
  PSE_CAN               Can[PCH_MAX_PSE_CAN_CONTROLLERS];
  PSE_TGPIO             TimedGpio[PCH_MAX_PSE_TGPIO_CONTROLLERS];
  PSE_TGPIO_PIN_MUX     TimedGpioPinMux;
  UINT8                 TimedGpioPinEnable[PCH_MAX_PSE_TGPIO_CONTROLLER_PINS];   ///< Pin set to TGPIO native function
  UINT8                 Rsvd[4];                                                 ///< Reserved for DWORD alignment
  UINT32                PseLogOutputChannel;
  UINT16                PseLogOutputSize;
  UINT16                PseLogOutputOffset;
  UINT32                PseJtagEnabled;
  UINT32                PseJtagPinMux;
} PSE_CONFIG;

///
/// Premem Policy for Programmable Service Engine device.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;     ///< Config Block Header
  /**
    PSE Controler 0: Disable; <b>1: Enable</b>.
  **/
  UINT32    Enable          :  1;
  UINT32    RsvdBits0       : 31;   ///< Reserved Bits
} PSE_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _PSE_CONFIG_H_
