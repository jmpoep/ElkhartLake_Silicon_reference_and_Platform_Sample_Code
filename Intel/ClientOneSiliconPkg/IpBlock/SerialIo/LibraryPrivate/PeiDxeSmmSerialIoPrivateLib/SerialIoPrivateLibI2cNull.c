/** @file
  Serial IO I2C Private Lib implementation.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/BaseLib.h>

/**
  Finds PCI Device Number

  @param[in] I2cNumber             Serial IO device I2C number

  @retval                          SerialIo device number
**/
UINT8
GetSerialIoI2cDeviceNumber (
  IN UINT8       I2cNumber
  )
{
  return 0;
}

/**
  Finds PCI Function Number.

  @param[in] I2cNumber               Serial IO device I2C number

  @retval                            SerialIo funciton number
**/
UINT8
GetSerialIoI2cFunctionNumber (
  IN UINT8       I2cNumber
  )
{
  return 0;
}

/**
  Gets Pci Config control offset

  @param[in] I2cNumber               Serial IO device I2C number

  @retval                            Config control offset
**/
UINT16
GetSerialIoI2cConfigControlOffset (
  IN UINT8       I2cNumber
  )
{
  return 0;
}

/**
  Gets Fixed Base Address used for BAR0

  @param[in] I2cNumber               Serial IO device I2C number

  @retval                            Config control offset
**/
UINT32
GetSerialIoI2cFixedMmioAddress (
  IN UINT8       I2cNumber
  )
{
  return 0;
}

/**
  Gets Fixed Address used for Pci Config Space manipulation

  @param[in] I2cNumber               Serial IO device I2C number

  @retval                            Pci Config Address
**/
UINT32
GetSerialIoI2cFixedPciCfgAddress (
  IN UINT8       I2cNumber
  )
{
  return 0;
}


/**
  Gets I2C Device Id

  @param[in] I2cNumber               Serial IO device I2C number

  @retval                            Device Id
**/
UINT16
GetSerialIoI2cDeviceId (
  IN UINT8       I2cNumber
  )
{
  return 0;
}
