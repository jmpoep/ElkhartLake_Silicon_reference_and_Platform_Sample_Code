/** @file
  Serial IO policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _SERIAL_IO_DEVICES_H_
#define _SERIAL_IO_DEVICES_H_

#include <Protocol/SerialIo.h>
#include <PchLimits.h>

#pragma pack (push,1)

/**
  Available working modes for SerialIo SPI Host Controller

       0: SerialIoSpiDisabled;
          - Device is placed in D3
          - Gpio configuration is skipped
          - PSF:
          !important! If given device is Function 0 and other higher functions on given device
                      are enabled, PSF disabling is skipped. PSF default will remain and device PCI CFG Space will still be visible.
                      This is needed to allow PCI enumerator access functions above 0 in a multifunction device.
    <b>1: SerialIoSpiPci;</b>
          - Gpio pin configuration in native mode for each assigned pin
          - Device will be enabled in PSF
          - Only BAR0 will be enabled
       2: SerialIoSpiHidden;
          - Gpio pin configuration in native mode for each assigned pin
          - Device disabled in the PSF
          - Both BARs are enabled, BAR1 becomes devices Pci Config Space
          - BAR0 assigned from the global PCH reserved memory range, reported as motherboard resource by SIRC
       @note
           If this controller is located at function 0 and it's mode is set to hidden it will not be visible in the PCI space.
**/
typedef enum {
  SerialIoSpiDisabled,
  SerialIoSpiPci,
  SerialIoSpiHidden
} SERIAL_IO_SPI_MODE;

/**
  Used to set Hardware Flow Control Enable/Disable of Serial IO
**/
typedef enum  {
  PchSerialIoHwFlowControlDisabled = 0,
  PchSerialIoHwFlowControlEnabled = 1
} SERIAL_IO_HW_FLOW_CTRL;

/**
  Used to set Inactive/Idle polarity of Spi Chip Select
**/
typedef enum {
  SerialIoSpiCsActiveLow  = 0,
  SerialIoSpiCsActiveHigh = 1
} SERIAL_IO_CS_POLARITY;

/**
  The SERIAL_IO_SPI_CONFIG provides the configurations to set the Serial IO SPI controller
**/
typedef struct {
  UINT8 Mode;                                          ///< <b>SerialIoSpiPci </b> see SERIAL_IO_SPI_MODE
  UINT8 DefaultCsOutput;                               ///< <b>0 = CS0</b> CS1, CS2, CS3. Default CS used by the SPI HC
  UINT8 CsPolarity[PCH_MAX_SERIALIO_SPI_CHIP_SELECTS]; ///< Selects SPI ChipSelect signal polarity, 0 = low <b>1 = High</b>
  UINT8 CsEnable[PCH_MAX_SERIALIO_SPI_CHIP_SELECTS];   ///< <b>0 = Enable</b> 1 = Disable. Based on this setting GPIO for given SPIx CSx will be configured in Native mode
  UINT8 CsMode;                                        ///< <b>0 = HW Control</b> 1 = SW Control. Sets Chip Select Control mode Hardware or Software.
  UINT8 CsState;                                       ///< <b>0 = CS is set to low</b> 1 = CS is set to high
  UINT8 MisoEnable;                                    ///< <b>1=Enable </b> 0=Disable. Based on this setting GPIO for SPIx MISO will be configured in Native mode
  UINT8 Reserved[3];
} SERIAL_IO_SPI_CONFIG;

/**
  Available working modes for SerialIo UART Host Controller

       0: SerialIoUartDisabled;
          - Device is placed in D3
          - Gpio configuration is skipped
          - PSF:
          !important! If given device is Function 0 and other higher functions on given device
                      are enabled, PSF disabling is skipped. PSF default will remain and device PCI CFG Space will still be visible.
                      This is needed to allow PCI enumerator access functions above 0 in a multifunction device.
    <b>1: SerialIoUartPci;</b>
          - Designated for Serial IO UART OS driver usage
          - Gpio pin configuration in native mode for each assigned pin
          - Device will be enabled in PSF
          - Only BAR0 will be enabled
       2: SerialIoUartHidden;
          - Designated for BIOS and/or DBG2 OS kernel debug
          - Gpio pin configuration in native mode for each assigned pin
          - Device disabled in the PSF
          - Both BARs are enabled, BAR1 becomes devices Pci Config Space
          - BAR0 assigned from the global PCH reserved memory range, reported as motherboard resource by SIRC
       @note
           If this controller is located at function 0 and it's mode is set to hidden it will not be visible in the PCI space.
       3: SerialIoUartCom;
          - Designated for 16550/PNP0501 compatible COM device
          - Gpio pin configuration in native mode for each assigned pin
          - Device disabled in the PSF
          - Both BARs are enabled, BAR1 becomes devices Pci Config Space
          - BAR0 assigned from the global PCH reserved memory range, reported as motherboard resource by SIRC
       4: SerialIoUartSkipInit;
          - Gpio configuration is skipped
          - PSF configuration is skipped
          - BAR assignemnt is skipped
          - D-satate setting is skipped

**/
typedef enum {
  SerialIoUartDisabled = 0,
  SerialIoUartPci,
  SerialIoUartHidden,
  SerialIoUartCom,
  SerialIoUartSkipInit
} SERIAL_IO_UART_MODE;

typedef struct {
  UINT32      BaudRate;    ///< <b> 115200 </b> Max 6000000  MdePkg.dec  PcdUartDefaultBaudRate
  UINT8       Parity;      ///< <b> 1 - No Parity</b> see EFI_PARITY_TYPE MdePkg.dec PcdUartDefaultParity
  UINT8       DataBits;    ///< <b>8</b> MdePkg.dec PcdUartDefaultDataBits
  UINT8       StopBits;    ///< <b>1 - One Stop Bit</b> see EFI_STOP_BITS_TYPE  MdePkg.dec  PcdUartDefaultStopBits
  UINT8       AutoFlow;    ///< <b>FALSE</b>  IntelFrameworkModulePkg.dsc PcdIsaBusSerialUseHalfHandshake
} SERIAL_IO_UART_ATTRIBUTES;

/**
  UART signals pin muxing settings. If signal can be enable only on a single pin
  then this parameter is ignored by RC. Refer to GPIO_*_MUXING_SERIALIO_UARTx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32 Rx;  ///< RXD Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_UARTx_RXD_*
  UINT32 Tx;  ///< TXD Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_UARTx_TXD_*
  UINT32 Rts; ///< RTS Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_UARTx_RTS_*
  UINT32 Cts; ///< CTS Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_UARTx_CTS_*
} UART_PIN_MUX;

typedef struct {
  SERIAL_IO_UART_ATTRIBUTES Attributes;  ///< see SERIAL_IO_UART_ATTRIBUTES
  UART_PIN_MUX              PinMux;      ///< UART pin mux configuration
  UINT8                     Mode;        ///< <b> SerialIoUartPci </b> see SERIAL_IO_UART_MODE
  UINT8                     DBG2;        ///< <b> FALSE </b> If TRUE adds UART to DBG2 table and overrides UartPg to SerialIoUartPgDisabled
  UINT8                     PowerGating; ///< <b> SerialIoUartPgAuto </b> Applies to Hidden/COM/SkipInit see SERIAL_IO_UART_PG
  UINT8                     DmaEnable;   ///< <b> TRUE </b> Applies to SerialIoUartPci only. Informs OS driver to use DMA, if false it will run in PIO mode
} SERIAL_IO_UART_CONFIG;

typedef enum {
  SerialIoUartPgDisabled,  ///< No _PS0/_PS3 support, device left in D0, after initialization
/**
  In mode: SerialIoUartCom;
           _PS0/_PS3  that supports getting device out of reset
  In mode: SerialIoUartPci
           Keeps UART in D0 and assigns Fixed MMIO for SEC/PEI usage only
**/
  SerialIoUartPgEnabled,
  SerialIoUartPgAuto       ///< _PS0 and _PS3, detection through ACPI if device was initialized prior to first PG. If it was used (DBG2) PG is disabled,
} SERIAL_IO_UART_PG;

/**
  Available working modes for SerialIo I2C Host Controller

       0: SerialIoI2cDisabled;
          - Device is placed in D3
          - Gpio configuration is skipped
          - PSF:
          !important! If given device is Function 0 and other higher functions on given device
                      are enabled, PSF disabling is skipped. PSF default will remain and device PCI CFG Space will still be visible.
                      This is needed to allow PCI enumerator access functions above 0 in a multifunction device.
    <b>1: SerialIoI2cPci;</b>
          - Gpio pin configuration in native mode for each assigned pin
          - Device will be enabled in PSF
          - Only BAR0 will be enabled
       2: SerialIoI2cHidden;
          - Gpio pin configuration in native mode for each assigned pin
          - Device disabled in the PSF
          - Both BARs are enabled, BAR1 becomes devices Pci Config Space
          - BAR0 assigned from the global PCH reserved memory range, reported as motherboard resource by SIRC
       @note
           If this controller is located at function 0 and it's mode is set to hidden it will not be visible in the PCI space.
**/
typedef enum {
  SerialIoI2cDisabled = 0,
  SerialIoI2cPci,
  SerialIoI2cHidden
} SERIAL_IO_I2C_MODE;

/**
  I2C signals pin muxing settings. If signal can be enable only on a single pin
  then this parameter is ignored by RC. Refer to GPIO_*_MUXING_SERIALIO_I2Cx_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32   Sda;   ///< SDA Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_I2Cx_SDA_*
  UINT32   Scl;   ///< SCL Pin mux configuration. Refer to GPIO_*_MUXING_SERIALIO_I2Cx_SCL_*
} I2C_PIN_MUX;

typedef struct {
  UINT8        Mode;        /// <b>SerialIoI2cPci <b> see SERIAL_IO_I2C_MODE
  /**
    I2C Pads Internal Termination.
    For more information please see Platform Design Guide.
    Supported values (check GPIO_ELECTRICAL_CONFIG for reference):
    <b>GpioTermNone: No termination</b>,
    GpioTermWpu1K: 1kOhm weak pull-up,
    GpioTermWpu5K: 5kOhm weak pull-up,
    GpioTermWpu20K: 20kOhm weak pull-up
  **/
  UINT8        PadTermination;
  UINT8        Reserved[2];
  I2C_PIN_MUX  PinMux;      ///< I2C pin mux configuration
} SERIAL_IO_I2C_CONFIG;

#pragma pack (pop)

#endif // _SERIAL_IO_DEVICES_H_
