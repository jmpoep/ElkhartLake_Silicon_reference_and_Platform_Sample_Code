/** @file
  Touch Host Controller Library.
  All functions from this library are available in PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/GpioLib.h>
#include <Library/DebugLib.h>
#include <Library/ThcLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/GpioPrivateLib.h>
#include <Register/ThcRegs.h>
#include <Register/PchRegs.h>
#include <IndustryStandard/Pci30.h>

/**
  Checks if GPIO Pads are availalbe for BIOS to configure

  @param[in] PortNum  Port Number

  @retval    TRUE     Gpio Pads are owned by the Host, and BIOS is able to configure them
             FALSE    BIOS is unable to configure Gpio Pad settings for THC
**/
STATIC
BOOLEAN
ThcArePinsHostOwned (
  IN UINT8          PortNum
  )
{
  UINT8  Index;

  if (!GpioIsPadHostOwned ((GpioGetThcSpiClk (PortNum)).Pad) ||
       !GpioIsPadHostOwned ((GpioGetThcSpiCs (PortNum)).Pad) ||
       !GpioIsPadHostOwned ((GpioGetThcSpiReset (PortNum)).Pad)) {
    return FALSE;
  }
  for (Index = 0; Index <= 3; Index++) {
    if (!GpioIsPadHostOwned ((GpioGetThcSpiIo (PortNum, Index)).Pad)) {return FALSE;}
  }

  return TRUE;
}

/**
  Returns Pci Config Base for THC

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval    THC Pci base address
**/
UINT64
ThcGetPciConfigSpace (
  IN UINT8          ThcNumber
  )
{
  if (ThcNumber >= GetPchMaxThcCount ()) {
    ASSERT (FALSE);
    return 0;
  }

  return PCI_SEGMENT_LIB_ADDRESS (
               DEFAULT_PCI_SEGMENT_NUMBER_PCH,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               ThcGetDeviceNumber (ThcNumber),
               ThcGetFunctionNumber (ThcNumber),
               0
               );
}

/**
  Checks if the Intel Touch Host Controller is Enabled

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval TRUE                    THC is enabled
  @retval FALSE                   THC PCI device not found
**/
BOOLEAN
ThcIsEnabled (
  IN UINT8          ThcNumber
  )
{
  UINT64  PciBase;

  if (ThcNumber >= GetPchMaxThcCount ()) {
    ASSERT (FALSE);
    return FALSE;
  }

  PciBase = ThcGetPciConfigSpace (ThcNumber);

  if (PciSegmentRead16 (PciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "THC%d: PCI Device not found!\n", ThcNumber));
    return FALSE;
  }
  return TRUE;
}

/**
  Checks if it is possible to enable Intel Touch Host Controller

  Thc Port 0 could be used by THC or Integrated Touch.
  If Integrated Touch is enabled, CSME will take over its GPIO.
  Based on the pad ownership BIOS decides if it is possible to enable THC

  @retval TRUE                    BIOS is capable of enabling THC
  @retval FALSE                   THC pins are taken over by some other IP. BIOS is unable to configure THC
**/
BOOLEAN
ThcIsSupported (
  VOID
  )
{
  return FALSE;
}

