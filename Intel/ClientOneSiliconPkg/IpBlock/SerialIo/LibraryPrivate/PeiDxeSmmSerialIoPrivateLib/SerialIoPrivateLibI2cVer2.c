/** @file
  Serial IO I2C Private Lib implementation TigerLake specific.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/PchInfoLib.h>
#include <Register/SerialIoRegsVer2.h>
#include <IndustryStandard/Pci30.h>
#include <SerialIoPrivateLibInternal.h>
#include <PchReservedResources.h>
#include <PchLimits.h>

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchSerialIoI2cBdf [] = {
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C6, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C6},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C7, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C7}
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpSerialIoI2cDevId [] = {
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C0_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C1_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C2_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C3_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C4_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C5_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C6_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_I2C7_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchHSerialIoI2cDevId [] = {
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C0_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C1_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C2_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C3_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C4_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C5_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C6_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_I2C7_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchSerialIoI2cPciCfgCtrAddr [] = {
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C0,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C1,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C2,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C3,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C4,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C5,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C6,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_I2C7
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_CONTROLLER_DESCRIPTOR mSerialIoI2cFixedAddress [] = {
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x0000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x1000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x2000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x3000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x4000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x5000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x6000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x7000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x8000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x9000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0xA000,  PCH_SERIAL_IO_BASE_ADDRESS + 0xB000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0xC000,  PCH_SERIAL_IO_BASE_ADDRESS + 0xD000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0xE000,  PCH_SERIAL_IO_BASE_ADDRESS + 0xF000}
};

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
  return mPchSerialIoI2cBdf[I2cNumber].DevNum;
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
  return mPchSerialIoI2cBdf[I2cNumber].FuncNum;
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
  return mPchSerialIoI2cPciCfgCtrAddr[I2cNumber];
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
  return mSerialIoI2cFixedAddress[I2cNumber].Bar0;
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
  return mSerialIoI2cFixedAddress[I2cNumber].Bar1;
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
  if (IsPchH ()) {
    return mPchHSerialIoI2cDevId[I2cNumber];
  }
  return mPchLpSerialIoI2cDevId[I2cNumber];
}
