/** @file
  Serial IO Private Uart Lib implementation ElkhartLake specific.
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
#include <Register/SerialIoRegsVer3.h>
#include <IndustryStandard/Pci30.h>
#include <SerialIoPrivateLibInternal.h>
#include <PchReservedResources.h>
#include <PchLimits.h>

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_BDF_NUMBERS mPchLpSerialIoUartBdf [] = {
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2}
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpSerialIoUartDevId [] = {
  V_VER3_SERIAL_IO_CFG_UART0_DEVICE_ID,
  V_VER3_SERIAL_IO_CFG_UART1_DEVICE_ID,
  V_VER3_SERIAL_IO_CFG_UART2_DEVICE_ID
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchSerialIoUartPciCfgCtrAddr [] = {
  R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART0,
  R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART1,
  R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART2
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_CONTROLLER_DESCRIPTOR mSerialIoUartFixedAddress [] = {
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x1E000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x1F000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x20000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x21000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x22000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x23000}
};

/**
  Finds PCI Device Number

  @param[in] UartNumber            Serial IO device UART number

  @retval                          SerialIo device number
**/
UINT8
GetSerialIoUartDeviceNumber (
  IN UINT8       UartNumber
  )
{
  //@todo add other EHL PCH gen
  return mPchLpSerialIoUartBdf[UartNumber].DevNum;
}

/**
  Finds PCI Function Number.

  @param[in] UartNumber              Serial IO device UART number

  @retval                            SerialIo funciton number
**/
UINT8
GetSerialIoUartFunctionNumber (
  IN UINT8       UartNumber
  )
{
  //@todo add other EHL PCH gen
  return mPchLpSerialIoUartBdf[UartNumber].FuncNum;
}

/**
  Gets Pci Config control offset

  @param[in] UartNumber              Serial IO device UART number

  @retval                            Config control offset
**/
UINT16
GetSerialIoUartConfigControlOffset (
  IN UINT8       UartNumber
  )
{
  return mPchSerialIoUartPciCfgCtrAddr[UartNumber];
}

/**
  Gets Fixed Base Address used for BAR0

  @param[in] UartNumber              Serial IO device UART number

  @retval                            Config control offset
**/
UINT32
GetSerialIoUartFixedMmioAddress (
  IN UINT8       UartNumber
  )
{
  return mSerialIoUartFixedAddress[UartNumber].Bar0;
}

/**
  Gets Fixed Address used for Pci Config Space manipulation

  @param[in] UartNumber              Serial IO device UART number

  @retval                            Pci Config Address
**/
UINT32
GetSerialIoUartFixedPciCfgAddress (
  IN UINT8       UartNumber
  )
{
  return mSerialIoUartFixedAddress[UartNumber].Bar1;
}

/**
  Gets Uarts Device Id

  @param[in] UartNumbe               Serial IO device UART number

  @retval                            Device Id
**/
UINT16
GetSerialIoUartDeviceId (
  IN UINT8       UartNumber
  )
{
  //@todo add other EHL PCH gen
  return mPchLpSerialIoUartDevId[UartNumber];
}

