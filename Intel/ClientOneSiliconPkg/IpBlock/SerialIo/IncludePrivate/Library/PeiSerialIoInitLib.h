/** @file
  Initializes Serial IO Controllers.

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
#ifndef _PEI_SERIALIO_INIT_LIB_H_
#define _PEI_SERIALIO_INIT_LIB_H_

#include <Ppi/SiPolicy.h>

/**
  Initializes Serial IO Controllers

  @param[in] SiPolicy

**/
VOID
SerialIoInit (
  IN SI_POLICY_PPI           *SiPolicy
  );

/**
  Configures Serial IO Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicone policy

**/
VOID
SerialIoFunction0Disable (
  IN SI_POLICY_PPI           *SiPolicy
  );

/**
  Enable 16550 8bit Mode

  @param[in] UartNumber         UART Number

**/
VOID
SerialIoUartEnable16550Mode (
  IN UINT8        UartNumber
  );

/**
  Disable 16550 8bit Mode

  @param[in] UartNumber         UART Number

**/
VOID
SerialIoUartDisable16550Mode (
  IN UINT8        UartNumber
  );

/**
  Configures Serial IO Controller

  @param[in] UartNumber        UART Number
  @param[in] UartDeviceConfig  SerialIo UART Config
  @param[in] PsfDisable        Applies only for SerialIoUartDisabled devices.
                               TRUE  - Device will be disabled in PSF, and will no longer enumerate on PCI.
                               FALSE - PSF configuration is left unmodified.
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoUartConfiguration (
  IN UINT8                      UartNumber,
  IN SERIAL_IO_UART_CONFIG      *UartDeviceConfig,
  IN BOOLEAN                    PsfDisable,
  IN BOOLEAN                    PchMasterPowerGating
  );

/**
  Performs Early disable for Serial Io I2C Controller

  @param[in] I2cNumber     Serial IO I2C number

**/
VOID
SerialIoI2cEarlyDisable (
  IN UINT8 I2cNumber
  );

/**
  Configures Serial IO Controller

  @param[in] SpiNumber         SPI Number
  @param[in] SpiDeviceConfig   SerialIo SPI Config
  @param[in] PsfDisable        Applies only for SerialIoSpiDisabled devices.
                               TRUE  - Device will be disabled in PSF, and will no longer enumerate on PCI.
                               FALSE - PSF configuration is left unmodified.
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoSpiConfiguration (
  IN UINT8                      SpiNumber,
  IN SERIAL_IO_SPI_CONFIG       *SpiDeviceConfig,
  IN BOOLEAN                    PsfDisable,
  IN BOOLEAN                    PchMasterPowerGating
  );

#endif // _PEI_SERIALIO_INIT_LIB_H_
