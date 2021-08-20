/** @file
  Initializes PSE TGPIO controller block.

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

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiPseInitLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PchInfoLib.h>
#include <Register/PchRegs.h>
#include <Register/PseRegs.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Include/PcieRegs.h>

GLOBAL_REMOVE_IF_UNREFERENCED PSE_CONFIG               *mPseConfig = NULL;

/**
  Sets corresponding GPIO pins to native function as PSE TGPIO

  @param[in]  PseTgpioIndex       Index of PSE TGPIO controler block
  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
VOID
PseSetTgpioPad (
  IN  UINT8            PseTgpioIndex,
  IN  SI_POLICY_PPI    *SiPolicy
)
{
  UINT8          PinIndex;
  UINT8          PinIndexBase;

  PinIndexBase = 0;

  if (PseTgpioIndex == 0) {
    PinIndexBase = 0;
  } else if (PseTgpioIndex == 1) {
    PinIndexBase = 30;
  }
  DEBUG ((DEBUG_INFO, "PSE TimedGpio%d pins set to Native Mode\n", PseTgpioIndex));

  /* Do a TGPIO pin pad configuration for all the pins if the pin is enabled */
  for (PinIndex = PinIndexBase; PinIndex < PinIndexBase + 30; PinIndex++) {
    if (mPseConfig->TimedGpioPinEnable[PinIndex]) {
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_TGPIO (PinIndex), mPseConfig->TimedGpioPinMux.Pin[PinIndex]);
    }
  }
}

/**
  Gets the device and function number of PSE TGPIO controller block

  @param[in]  PseTgpioIndex       Index of PSE TGPIO controler block
  @param[out] DeviceNum           Pointer to the variable to store device number
  @param[out] FunctionNum         Pointer to the variable to store function number
**/
VOID
PseGetTgpioBdf (
  IN  UINT8  PseTgpioIndex,
  OUT UINT8  *DeviceNum,
  OUT UINT8  *FunctionNum
  )
{
  switch (PseTgpioIndex) {
    case 0:
      *DeviceNum = PCI_DEVICE_NUMBER_PCH_PSE_GPIO0;
      *FunctionNum = PCI_FUNCTION_NUMBER_PCH_PSE_GPIO0;
      break;
    case 1:
      *DeviceNum = PCI_DEVICE_NUMBER_PCH_PSE_GPIO1;
      *FunctionNum = PCI_FUNCTION_NUMBER_PCH_PSE_GPIO1;
      break;
    default:
      ASSERT (FALSE);
  }
}

/**
  Configure PSE TGPIO controller block

  @param[in]  PciBaseAddress       PCI config base address of the controller
  @param[in]  MmioBase             MMIO base address
  @param[in]  TgpioPinMuxSel       20 pins allocation for this PSE TGPIO controller blcok
**/
VOID
PseTgpioInitMmioRegisters (
  IN UINT8   PseTgpioIndex,
  IN UINT64  PciBaseAddress,
  IN UINTN   MmioBase,
  IN UINT8   TgpioPinMuxSel
  )
{
  //
  // Configure LH2PSE_MEM_TGPIO_MUX_SEL register based on setup menu option
  //
  switch (PseTgpioIndex) {
    case 0:
      MmioWrite32 (MmioBase + R_PSE_LH2PSE_MEM_TGPIO_MUX_SEL0, (UINT32) TgpioPinMuxSel);
      break;
    case 1:
      MmioWrite32 (MmioBase + R_PSE_LH2PSE_MEM_TGPIO_MUX_SEL1, (UINT32) TgpioPinMuxSel);
      break;
    default:
      break;
  }
}

/**
  Enables PSE TGPIO controller block.

  @param[in]  PseTgpioIndex       Index of PSE TGPIO controler block
  @param[in]  TgpioPinMuxSel      20 pins allocation for this PSE TGPIO controller blcok
  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
VOID
PseTgpioEnable (
  IN  UINT8           PseTgpioIndex,
  IN  UINT8           TgpioPinMuxSel,
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  UINT64         PseLh2PsePciBase;
  UINT64         PseLh2PseMmioBase;

  DEBUG ((DEBUG_INFO, "Enabling PSE TGPIO controller block, index = %d\n", PseTgpioIndex));

  PseLh2PsePciBase = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_PSE_LH2PSE,
                      PCI_FUNCTION_NUMBER_PCH_PSE_LH2PSE,
                      0
                      );

  PseLh2PseMmioBase = (((UINT64)PciSegmentRead32 (PseLh2PsePciBase + PCI_BASE_ADDRESSREG_OFFSET + 4)) << 32)
                      | (PciSegmentRead32 (PseLh2PsePciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFF000);

  DEBUG ((DEBUG_INFO, "PSE LH2PSE MMIO base address = 0x%016lx\n", PseLh2PseMmioBase));

  PseTgpioInitMmioRegisters (PseTgpioIndex, PseLh2PsePciBase, (UINTN) PseLh2PseMmioBase, TgpioPinMuxSel);

  PseSetTgpioPad (PseTgpioIndex, SiPolicy);
}

/**
  Enables or disables PSE TGPIO controller block.

  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
  @param[in]  PseTgpioIndex       Index of PSE TGPIO controler block
**/
VOID
PseTgpioInit (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT8           PseTgpioIndex
  )
{
  EFI_STATUS            Status;
  UINT8                 TgpioPinMuxSel;

  DEBUG ((DEBUG_INFO, "PSE TGPIO init start\n"));

  if (PseTgpioIndex >= GetPchMaxPseTimedGpioControllersNum ()) {
    ASSERT (FALSE);
    return;
  }

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &mPseConfig);
  ASSERT_EFI_ERROR (Status);

  TgpioPinMuxSel = (UINT8) mPseConfig->TimedGpio[PseTgpioIndex].PinAllocation;
  PseTgpioEnable (PseTgpioIndex, TgpioPinMuxSel, SiPolicy);
  DEBUG ((DEBUG_INFO, "PSE TGPIO init finished\n"));
}
