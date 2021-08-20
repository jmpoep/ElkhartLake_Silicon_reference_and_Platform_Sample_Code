/** @file
  PCH PSE IO Lib implementation ElkhartLake specific.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/MmPciLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PcdLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PsfLib.h>
#include <PchLimits.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>

#include <Register/PseRegs.h>
#include "PchPseIoLibInternal.h"

GLOBAL_REMOVE_IF_UNREFERENCED PSE_IO_BDF_NUMBERS mPchLpPchHPseIoBdf [PCH_MAX_PSE_CONTROLLERS] =
{
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C0,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C0},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C1,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C1},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C2,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C2},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C3,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C3},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C4,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C4},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C5,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C5},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C6,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C6},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2C7,   PCI_FUNCTION_NUMBER_PCH_PSE_I2C7},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART0,  PCI_FUNCTION_NUMBER_PCH_PSE_UART0},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART1,  PCI_FUNCTION_NUMBER_PCH_PSE_UART1},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART2,  PCI_FUNCTION_NUMBER_PCH_PSE_UART2},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART3,  PCI_FUNCTION_NUMBER_PCH_PSE_UART3},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART4,  PCI_FUNCTION_NUMBER_PCH_PSE_UART4},
  {PCI_DEVICE_NUMBER_PCH_PSE_UART5,  PCI_FUNCTION_NUMBER_PCH_PSE_UART5},
  {PCI_DEVICE_NUMBER_PCH_PSE_SPI0,   PCI_FUNCTION_NUMBER_PCH_PSE_SPI0},
  {PCI_DEVICE_NUMBER_PCH_PSE_SPI1,   PCI_FUNCTION_NUMBER_PCH_PSE_SPI1},
  {PCI_DEVICE_NUMBER_PCH_PSE_SPI2,   PCI_FUNCTION_NUMBER_PCH_PSE_SPI2},
  {PCI_DEVICE_NUMBER_PCH_PSE_SPI3,   PCI_FUNCTION_NUMBER_PCH_PSE_SPI3},
  {PCI_DEVICE_NUMBER_PCH_PSE_GBE0,   PCI_FUNCTION_NUMBER_PCH_PSE_GBE0},
  {PCI_DEVICE_NUMBER_PCH_PSE_GBE1,   PCI_FUNCTION_NUMBER_PCH_PSE_GBE1},
  {PCI_DEVICE_NUMBER_PCH_PSE_CAN0,   PCI_FUNCTION_NUMBER_PCH_PSE_CAN0},
  {PCI_DEVICE_NUMBER_PCH_PSE_CAN1,   PCI_FUNCTION_NUMBER_PCH_PSE_CAN1},
  {PCI_DEVICE_NUMBER_PCH_PSE_GPIO0,  PCI_FUNCTION_NUMBER_PCH_PSE_GPIO0},
  {PCI_DEVICE_NUMBER_PCH_PSE_GPIO1,  PCI_FUNCTION_NUMBER_PCH_PSE_GPIO1},
  {PCI_DEVICE_NUMBER_PCH_PSE_DMA0,   PCI_FUNCTION_NUMBER_PCH_PSE_DMA0},
  {PCI_DEVICE_NUMBER_PCH_PSE_DMA1,   PCI_FUNCTION_NUMBER_PCH_PSE_DMA1},
  {PCI_DEVICE_NUMBER_PCH_PSE_DMA2,   PCI_FUNCTION_NUMBER_PCH_PSE_DMA2},
  {PCI_DEVICE_NUMBER_PCH_PSE_QEP0,   PCI_FUNCTION_NUMBER_PCH_PSE_QEP0},
  {PCI_DEVICE_NUMBER_PCH_PSE_QEP1,   PCI_FUNCTION_NUMBER_PCH_PSE_QEP1},
  {PCI_DEVICE_NUMBER_PCH_PSE_QEP2,   PCI_FUNCTION_NUMBER_PCH_PSE_QEP2},
  {PCI_DEVICE_NUMBER_PCH_PSE_QEP3,   PCI_FUNCTION_NUMBER_PCH_PSE_QEP3},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2S0,   PCI_FUNCTION_NUMBER_PCH_PSE_I2S0},
  {PCI_DEVICE_NUMBER_PCH_PSE_I2S1,   PCI_FUNCTION_NUMBER_PCH_PSE_I2S1},
  {PCI_DEVICE_NUMBER_PCH_PSE_PWM,    PCI_FUNCTION_NUMBER_PCH_PSE_PWM},
  {PCI_DEVICE_NUMBER_PCH_PSE_ADC,    PCI_FUNCTION_NUMBER_PCH_PSE_ADC},
  {PCI_DEVICE_NUMBER_PCH_PSE_LH2PSE, PCI_FUNCTION_NUMBER_PCH_PSE_LH2PSE}
};

/**
  Finds PCI Device Number of PseIo devices.

  @param[in] PseIoNumber             Serial IO device

  @retval                               PseIo device number
**/
UINT8
GetPseIoDeviceNumber (
  IN PCH_PSE_IO_CONTROLLER  PseIoNumber
  )
{
  return mPchLpPchHPseIoBdf[PseIoNumber].DevNum;
}

/**
  Finds PCI Function Number of PseIo devices.

  @param[in] PseIoNumber             Serial IO device

  @retval                               PseIo funciton number
**/
UINT8
GetPseIoFunctionNumber (
  IN PCH_PSE_IO_CONTROLLER  PseIoNumber
  )
{
  return mPchLpPchHPseIoBdf[PseIoNumber].FuncNum;
}

/**
  Check Pse Gbe0 Enabled.

  @retval                               TRUE/FALSE
**/
UINT8
IsPseGbe0Enabled (
  VOID
  )
{
  UINTN  PchPseGbeBase;
  UINT16 DeviceId;
  UINT16 VendorId;

  PchPseGbeBase = 0;
  DeviceId      = 0;
  VendorId      = 0;

  PchPseGbeBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_PSE_GBE0,
                   PCI_FUNCTION_NUMBER_PCH_PSE_GBE0,
                   0
                   );
  DeviceId = PciSegmentRead16 (PchPseGbeBase + PCI_DEVICE_ID_OFFSET);
  VendorId = PciSegmentRead16 (PchPseGbeBase + PCI_VENDOR_ID_OFFSET);

  DEBUG ((DEBUG_INFO, "Pse Gbe 0 Device: Device Id: 0x%4X, Vendor Id: 0x%4X\n", DeviceId, VendorId));
  if ((DeviceId == 0xFFFF) || (VendorId == 0xFFFF)) {
    return FALSE;
  }

  return TRUE;
}


/**
  Check Pse Gbe1 Enabled.

  @retval                               TRUE/FALSE
**/
UINT8
IsPseGbe1Enabled (
  VOID
  )
{
  UINTN  PchPseGbeBase;
  UINT16 DeviceId;
  UINT16 VendorId;

  PchPseGbeBase = 0;
  DeviceId      = 0;
  VendorId      = 0;

  PchPseGbeBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_PSE_GBE1,
                   PCI_FUNCTION_NUMBER_PCH_PSE_GBE1,
                   0
                   );
  DeviceId = PciSegmentRead16 (PchPseGbeBase + PCI_DEVICE_ID_OFFSET);
  VendorId = PciSegmentRead16 (PchPseGbeBase + PCI_VENDOR_ID_OFFSET);

  DEBUG ((DEBUG_INFO, "Pse Gbe 1 Device: Device Id: 0x%4X, Vendor Id: 0x%4X\n", DeviceId, VendorId));
  if ((DeviceId == 0xFFFF) || (VendorId == 0xFFFF)) {
    return FALSE;
  }

  return TRUE;
}
