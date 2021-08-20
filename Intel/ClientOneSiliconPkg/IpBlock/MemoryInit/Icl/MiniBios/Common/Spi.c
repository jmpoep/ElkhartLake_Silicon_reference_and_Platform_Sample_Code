/** @file
  This file contains the SPI related functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#include "spi.h"

/**
  Initialize SerialIo SPI for Postcode
**/
void
PchSpiInit (
  void
  )
{
  UINT8     SerialIoSpiNumber;
  UINT32    SpiMosiPinMux;
  UINT32    SpiMisoPinMux;
  UINT32    SpiClkPinMux;
  UINT32    SpiCsPinMux;

  SerialIoSpiNumber = PCH_SERIAL_SPI_NUMBER;

  SpiMosiPinMux = 0;
  SpiMisoPinMux = 0;
  SpiClkPinMux  = 0;
  SpiCsPinMux   = 0;

  ConfigureSerialIoController (SerialIoSpiNumber + PchSerialIoIndexSpi0, PchSerialIoPci, TRUE);
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (SerialIoSpiNumber), SpiMosiPinMux);
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MISO (SerialIoSpiNumber), SpiMisoPinMux);
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CLK (SerialIoSpiNumber), SpiClkPinMux);
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CS (SerialIoSpiNumber, 0), SpiCsPinMux);

  SpiControllerAndMaxLedInit ();
}