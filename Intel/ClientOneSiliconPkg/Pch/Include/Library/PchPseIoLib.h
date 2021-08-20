/** @file
  Header file for PCH PSE IO Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _PCH_PSE_IO_LIB_H_
#define _PCH_PSE_IO_LIB_H_

typedef enum {
  PchPseIoIndexI2C0,
  PchPseIoIndexI2C1,
  PchPseIoIndexI2C2,
  PchPseIoIndexI2C3,
  PchPseIoIndexI2C4,
  PchPseIoIndexI2C5,
  PchPseIoIndexI2C6,
  PchPseIoIndexI2C7,
  PchPseIoIndexUart0,
  PchPseIoIndexUart1,
  PchPseIoIndexUart2,
  PchPseIoIndexUart3,
  PchPseIoIndexUart4,
  PchPseIoIndexUart5,
  PchPseIoIndexSpi0,
  PchPseIoIndexSpi1,
  PchPseIoIndexSpi2,
  PchPseIoIndexSpi3,
  PchPseIoIndexGbe0,
  PchPseIoIndexGbe1,
  PchPseIoIndexCan0,
  PchPseIoIndexCan1,
  PchPseIoIndexTGpio0,
  PchPseIoIndexTGpio1,
  PchPseIoIndexDma0,
  PchPseIoIndexDma1,
  PchPseIoIndexDma2,
  PchPseIoIndexQep0,
  PchPseIoIndexQep1,
  PchPseIoIndexQep2,
  PchPseIoIndexQep3,
  PchPseIoIndexI2S0,
  PchPseIoIndexI2S1,
  PchPseIoIndexPwm,
  PchPseIoIndexAdc,
  PchPseIoIndexLh2Pse,
  PchPseIoIndexMax
} PCH_PSE_IO_CONTROLLER;

typedef enum {
  PchPseIoDisabled,
  PchPseIoPci,
  PchPseIoAcpi,
  PchPseIoHidden
} PCH_PSE_IO_MODE;

typedef enum  {
  PSE_IO_UNKNOWN = 0,
  PSE_IO_I2C,
  PSE_IO_SPI,
  PSE_IO_UART
} PCH_PSE_IO_CONTROLLER_TYPE;

/**
  Finds PCI Device Number of PseIo devices.
  PseIo devices' BDF is configurable

  @param[in] PseIoNumber             Serial IO device

  @retval                               PseIo device number
**/
UINT8
GetPseIoDeviceNumber (
  IN PCH_PSE_IO_CONTROLLER  PseIoNumber
  );

/**
  Finds PCI Function Number of PseIo devices.
  PseIo devices' BDF is configurable

  @param[in] PseIoNumber             Serial IO device

  @retval                               PseIo funciton number
**/
UINT8
GetPseIoFunctionNumber (
  IN PCH_PSE_IO_CONTROLLER  PseIoNumber
  );

/**
  Gets Pci Config control offset

  @param[in] DeviceNumber               device number
  @param[in] FunctionNumber             function number

  @retval    CfgCtrAddr                 Offset of Pci config control
                                        0 if Device and Function do not correspond to Serial IO
**/
UINT16
GetPseIoConfigControlOffset (
  IN UINT8  DeviceNumber,
  IN UINT8  FunctionNumber
  );

/**
  Check Pse Gbe0 Enabled.

  @retval                               TRUE/FALSE
**/
UINT8
IsPseGbe0Enabled (
  VOID
  );

/**
  Check Pse Gbe1 Enabled.

  @retval                               TRUE/FALSE
**/
UINT8
IsPseGbe1Enabled (
  VOID
  );

#endif
