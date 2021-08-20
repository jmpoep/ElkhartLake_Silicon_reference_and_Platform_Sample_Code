/** @file
  This files contains Pch XHCI library for RCs usage

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <PchReservedResources.h>
#include <IndustryStandard/Pci30.h>
#include <Register/UsbRegs.h>
#include <Register/PchRegs.h>

/**
  Get XHCI USB legacy SMI control setting.

  @retval     return XHCI USB legacy SMI setting.
**/
UINT32
EFIAPI
PchXhciLegacySmiEnGet (
  VOID
  )
{
  UINT64          XhciPciMmBase;
  UINT64          XhciMmioBase;
  UINT64          OrgXhciMmioBase;
  UINT8           OrgCmd;
  UINT32          XhciLegacySmiEn;

  XhciPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_XHCI,
                    PCI_FUNCTION_NUMBER_PCH_XHCI,
                    0
                    );
  if (PciSegmentRead32 (XhciPciMmBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    return 0;
  }
  OrgCmd           = PciSegmentRead8 (XhciPciMmBase + PCI_COMMAND_OFFSET);
  OrgXhciMmioBase  = PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0) & ~(UINT32)B_XHCI_CFG_ALIGN_MASK;
  OrgXhciMmioBase |= LShiftU64 (PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0 + 4), 32);
  XhciMmioBase     = OrgXhciMmioBase;

  if (OrgXhciMmioBase == 0) {
    XhciMmioBase = PCH_TEMP_BASE_ADDRESS;
    PciSegmentWrite32 (XhciPciMmBase + R_XHCI_CFG_BAR0, (UINT32) XhciMmioBase);
  }
  if ((OrgCmd & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentWrite8 (XhciPciMmBase + PCI_COMMAND_OFFSET, OrgCmd | EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  XhciLegacySmiEn = MmioRead32 ((UINTN) (XhciMmioBase + R_XHCI_MEM_USBLEGCTLSTS)) & 0xFFFF;

  if ((OrgCmd & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentWrite8 (XhciPciMmBase + PCI_COMMAND_OFFSET, OrgCmd);
  }
  if (OrgXhciMmioBase == 0) {
    PciSegmentWrite32 (XhciPciMmBase + R_XHCI_CFG_BAR0, 0);
  }

  return XhciLegacySmiEn;
}

/**
  Set XHCI USB legacy SMI control setting.

  @param[in]  UsbLegacySmiEn            Set XHCI USB legacy SMI
**/
VOID
EFIAPI
PchXhciLegacySmiEnSet (
  UINT32                                UsbLegacySmiEn
  )
{
  UINT64          XhciPciMmBase;
  UINT64          XhciMmioBase;
  UINT64          OrgXhciMmioBase;
  UINT8           OrgCmd;

  XhciPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_XHCI,
                    PCI_FUNCTION_NUMBER_PCH_XHCI,
                    0
                    );
  if (PciSegmentRead32 (XhciPciMmBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    return;
  }
  OrgCmd           = PciSegmentRead8 (XhciPciMmBase + PCI_COMMAND_OFFSET);
  OrgXhciMmioBase  = PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0) & ~(UINT32)B_XHCI_CFG_ALIGN_MASK;
  OrgXhciMmioBase |= LShiftU64 (PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0 + 4), 32);
  XhciMmioBase     = OrgXhciMmioBase;

  if (OrgXhciMmioBase == 0) {
    XhciMmioBase = PCH_TEMP_BASE_ADDRESS;
    PciSegmentWrite32 (XhciPciMmBase + R_XHCI_CFG_BAR0, (UINT32) XhciMmioBase);
  }
  if ((OrgCmd & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentWrite8 (XhciPciMmBase + PCI_COMMAND_OFFSET, OrgCmd | EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  MmioWrite32 ((UINTN)(XhciMmioBase + R_XHCI_MEM_USBLEGCTLSTS), UsbLegacySmiEn & 0xFFFF);

  if ((OrgCmd & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentWrite8 (XhciPciMmBase + PCI_COMMAND_OFFSET, OrgCmd);
  }
  if (OrgXhciMmioBase == 0) {
    PciSegmentWrite32 (XhciPciMmBase + R_XHCI_CFG_BAR0, 0);
  }
}

