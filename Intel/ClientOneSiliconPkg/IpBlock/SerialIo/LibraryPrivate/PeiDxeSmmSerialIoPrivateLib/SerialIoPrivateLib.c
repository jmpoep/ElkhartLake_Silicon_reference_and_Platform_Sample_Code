/** @file
  Serial IO Private Lib implementation.
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
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Include/PcieRegs.h>
#include <IndustryStandard/Pci30.h>
#include <PchReservedResources.h>

/**
  Checks if higher functions are enabled.
  Used for Function 0 Serial Io Device disabling

  @param[in] DeviceNum       Device Number

  @retval TRUE               At least one higher function device is enabled
          FALSE              Higher functions are disabled
**/
BOOLEAN
SerialIoHigherFunctionsEnabled (
  IN UINT8                    DeviceNum
  )
{
  UINT8 FuncNum;
  //
  // Check all other func devs(1 to 7) status except func 0.
  //
  for (FuncNum = 1; FuncNum <= PCI_MAX_FUNC; FuncNum++) {
    if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                                   DEFAULT_PCI_BUS_NUMBER_PCH,
                                                   DeviceNum,
                                                   FuncNum,
                                                   PCI_DEVICE_ID_OFFSET)
                          ) != 0xFFFF) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Places SerialIo device in D3

  @param[in] PciCfgBase       Pci Config Offset

**/
VOID
SerialIoSetD3 (
  IN UINT64                    PciCfgBase
  )
{
  if (PciCfgBase < PCH_SERIAL_IO_BASE_ADDRESS) {
    PciSegmentOr32 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, BIT1 | BIT0);
  } else {
    MmioOr8 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, BIT1 | BIT0);
  }
}

/**
  Places SerialIo device in D0

  @param[in] PciCfgBase       Pci Config Offset

**/
VOID
SerialIoSetD0 (
  IN UINT64                    PciCfgBase
  )
{
  if (PciCfgBase < PCH_SERIAL_IO_BASE_ADDRESS) {
    PciSegmentAnd32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT32) ~(BIT1 | BIT0));
  } else {
    MmioAnd32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT32) ~(BIT1 | BIT0));
  }
}

/**
  Allows memory access

  @param[in] PciCfgBase       Pci Config Offset
  @param[in] Hidden           Mode that determines access type

**/
VOID
SerialIoEnableMse (
  IN UINT64                    PciCfgBase,
  IN BOOLEAN                   Hidden
  )
{
  if (Hidden) {
    MmioOr16 ((UINTN) PciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  } else {
    PciSegmentOr16 ((UINTN) PciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }
}

/**
  Disable SerialIo memory access

  @param[in] PciCfgBase       Pci Config Offset

**/
VOID
SerialIoDisableMse (
  IN UINT64                    PciCfgBase
  )
{
  PciSegmentAnd16 ((UINTN) PciCfgBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Disable SerialIo memory encoding
  Designated for Pci modes

  @param[in] PciCfgBase       Pci Config Offset
  @param[in] RemoveTempBar    Remove temporary mem base address or not

**/
VOID
SerialIoMmioDisable (
  IN UINT64                    PciCfgBase,
  IN BOOLEAN                   RemoveBar
  )
{
  SerialIoDisableMse (PciCfgBase);

  if (RemoveBar == TRUE) {
    PciSegmentWrite32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW,  0x0);
    PciSegmentWrite32 ((UINTN) PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH,  0x0);
  }
}
