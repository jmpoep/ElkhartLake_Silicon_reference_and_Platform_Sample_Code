/** @file
  Header file for Serial Io Common Lib

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _SERIAL_IO_ACCESS_LIB_H_
#define _SERIAL_IO_ACCESS_LIB_H_

/**
  Returns BAR0

  @param[in] PciCfgBase         Pci Config Base

  @retval    64bit MMIO BAR Address
**/
UINT64
GetSerialIoBar (
  IN UINT64        PciCfgBase
  );

/**
  Returns I2C Pci Config Space

  @param[in] I2cNumber         I2C Number

  @retval    I2C Pci Config Space Address
**/
UINT64
GetSerialIoI2cPciCfg (
  IN UINT8        I2cNumber
  );

/**
  Returns SPI Pci Config Space

  @param[in] SpiNumber         SPI Number

  @retval    SPI Pci Config Space Address
**/
UINT64
GetSerialIoSpiPciCfg (
  IN UINT8        SpiNumber
  );

/**
  Returns UART Pci Config Space

  @param[in] UartNumber         UART Number

  @retval    UART Pci Config Space Address
**/
UINT64
GetSerialIoUartPciCfg (
  IN UINT8        UartNumber
  );

/**
  Checks if Device with given PciDeviceId is one of SerialIo I2C controllers
  If yes, its number is returned through I2cIndex parameter, otherwise I2cIndex is not updated

  @param[in]  PciDevId                  Device ID
  @param[out] I2cNumber                 Number of SerialIo I2C controller

  @retval TRUE                          yes it is a SerialIo I2C controller
  @retval FALSE                         no it isn't a SerialIo I2C controller
**/
BOOLEAN
IsSerialIoI2cDeviceId (
  IN  UINT16    PciDevId,
  OUT UINT8     *I2cNumber
  );

/**
  Checks if I2c is Function 0 Enabled

  @param[in] I2cIndex                   Number of the SerialIo I2C controller

  @retval TRUE                          Enabled
  @retval FALSE                         Disabled
**/
BOOLEAN
IsSerialIoI2cFunction0Enabled (
  IN UINT8    I2cIndex
  );

/**
  Checks if Uart is Function 0 Enabled

  @param[in] UartIndex                   Number of the SerialIo Uart controller

  @retval TRUE                          Enabled
  @retval FALSE                         Disabled
**/
BOOLEAN
IsSerialIoUartFunction0Enabled (
  IN UINT8    UartIndex
  );

/**
  Checks if Spi is Function 0 Enabled

  @param[in] SpiIndex                   Number of the SerialIo Spi controller

  @retval TRUE                          Enabled
  @retval FALSE                         Disabled
**/
BOOLEAN
IsSerialIoSpiFunction0Enabled (
  IN UINT8    SpiIndex
  );

#endif // _SERIAL_IO_ACCESS_LIB_H_
