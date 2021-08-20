/** @file
  Serial IO Spi Private Lib implementation TigerLake specific.
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

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchLpSerialIoSpiBdf [] = {
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI3, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI3},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI4, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI4},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI5, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI5},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI6, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI6}
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchHSerialIoSpiBdf [] = {
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI2},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI3, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI3},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI4, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI4},
  {PCI_DEVICE_NUMBER_PCH_H_SERIAL_IO_SPI5, PCI_FUNCTION_NUMBER_PCH_H_SERIAL_IO_SPI5},
  {PCI_DEVICE_NUMBER_PCH_H_SERIAL_IO_SPI6, PCI_FUNCTION_NUMBER_PCH_H_SERIAL_IO_SPI6}
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpSerialIoSpiDevId [] = {
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI0_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI1_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI2_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI3_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI4_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI5_DEVICE_ID,
  V_VER2_PCH_LP_SERIAL_IO_CFG_SPI6_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchHSerialIoSpiDevId [] = {
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI0_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI1_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI2_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI3_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI4_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI5_DEVICE_ID,
  V_VER2_PCH_H_SERIAL_IO_CFG_SPI6_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchSerialIoSpiPciCfgCtrAddr [] = {
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI0,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI1,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI2,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI3,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI4,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI5,
  R_VER2_SERIAL_IO_PCR_PCICFGCTRL_SPI6
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_CONTROLLER_DESCRIPTOR mSerialIoSpiFixedAddress [] = {
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x10000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x11000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x12000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x13000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x14000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x15000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x16000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x17000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x18000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x19000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x1A000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x1B000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x1C000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x1D000}
};

/**
  Finds PCI Device Number

  @param[in] SpiNumber             Serial IO device SPI number

  @retval                          SerialIo device number
**/
UINT8
GetSerialIoSpiDeviceNumber (
  IN UINT8       SpiNumber
  )
{
  if (IsPchH ()) {
    return mPchHSerialIoSpiBdf[SpiNumber].DevNum;
  }
  return mPchLpSerialIoSpiBdf[SpiNumber].DevNum;
}

/**
  Finds PCI Function Number.

  @param[in] SpiNumber               Serial IO device SPI number

  @retval                            SerialIo funciton number
**/
UINT8
GetSerialIoSpiFunctionNumber (
  IN UINT8       SpiNumber
  )
{
  if (IsPchH ()) {
    return mPchHSerialIoSpiBdf[SpiNumber].FuncNum;
  }
  return mPchLpSerialIoSpiBdf[SpiNumber].FuncNum;
}

/**
  Gets Pci Config control offset

  @param[in] SpiNumber               Serial IO device SPI number

  @retval                            Config control offset
**/
UINT16
GetSerialIoSpiConfigControlOffset (
  IN UINT8       SpiNumber
  )
{
  return mPchSerialIoSpiPciCfgCtrAddr[SpiNumber];
}

/**
  Gets Fixed Base Address used for BAR0

  @param[in] SpiNumber               Serial IO device SPI number

  @retval                            Config control offset
**/
UINT32
GetSerialIoSpiFixedMmioAddress (
  IN UINT8       SpiNumber
  )
{
  return mSerialIoSpiFixedAddress[SpiNumber].Bar0;
}

/**
  Gets Fixed Address used for Pci Config Space manipulation

  @param[in] SpiNumber               Serial IO device SPI number

  @retval                            Pci Config Address
**/
UINT32
GetSerialIoSpiFixedPciCfgAddress (
  IN UINT8       SpiNumber
  )
{
  return mSerialIoSpiFixedAddress[SpiNumber].Bar1;
}

/**
  Gets Spi Device Id

  @param[in] SpiNumber               Serial IO device SPI number

  @retval                            Device Id
**/
UINT16
GetSerialIoSpiDeviceId (
  IN UINT8       SpiNumber
  )
{
  if (IsPchH ()) {
    return mPchHSerialIoSpiDevId[SpiNumber];
  }
  return mPchLpSerialIoSpiDevId[SpiNumber];
}

