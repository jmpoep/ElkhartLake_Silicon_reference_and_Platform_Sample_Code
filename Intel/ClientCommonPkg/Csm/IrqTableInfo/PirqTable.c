/** @file
PIRQ table builder function implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

#include <IndustryStandard/Pci.h>
#include <Protocol/IrqBoardInfo.h>
#include <Protocol/LegacyInterrupt.h>
#include <Protocol/LegacyBiosPlatform.h>

extern IRQ_BOARD_INFO_PROTOCOL *gIrqBoardInfoProtocol;

/**
  Dump Pirq Table.

  @param PirqTable PIRQ table pointer
**/
VOID
DumpPirqTable (
  IN VOID *PirqTable
  )
{
  EFI_LEGACY_PIRQ_TABLE_HEADER  *PirqTableHeader;
  EFI_LEGACY_IRQ_ROUTING_ENTRY  *IrqRoutingEntry;
  UINTN                         Index;
  UINTN                         Slot;

  PirqTableHeader = (EFI_LEGACY_PIRQ_TABLE_HEADER *)PirqTable;
  IrqRoutingEntry = (EFI_LEGACY_IRQ_ROUTING_ENTRY *)(PirqTableHeader + 1);

  DEBUG ((DEBUG_INFO, "==============================================================================="));
  DEBUG ((DEBUG_INFO, "\nPIRQ table:\n"));
  DEBUG ((DEBUG_INFO, "  Version:       %d.%d\n", (UINTN)PirqTableHeader->MajorVersion, (UINTN)PirqTableHeader->MinorVersion));
  DEBUG ((DEBUG_INFO, "  Size:          %d bytes\n", (UINTN)PirqTableHeader->TableSize));
  DEBUG ((DEBUG_INFO, "  PCI Router:    %02x:%02x\n", (UINTN)PirqTableHeader->Bus, (UINTN)(PirqTableHeader->DevFun >> 3)));
  DEBUG ((DEBUG_INFO, "  PCI IRQs:      0x%04x\n", (UINTN)PirqTableHeader->PciOnlyIrq));
  DEBUG ((DEBUG_INFO, "  Compat Vendor: 0x%04x\n", (UINTN)PirqTableHeader->CompatibleVid));
  DEBUG ((DEBUG_INFO, "  Compat Device: 0x%04x\n", (UINTN)PirqTableHeader->CompatibleDid));
  DEBUG ((DEBUG_INFO, "  Miniport data: 0x%08x\n", (UINTN)PirqTableHeader->Miniport));
  Slot = (PirqTableHeader->TableSize - sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER))/sizeof(EFI_LEGACY_IRQ_ROUTING_ENTRY);
  DEBUG ((DEBUG_INFO, "  Slots:         %d\n", (UINTN)Slot));
  DEBUG ((DEBUG_INFO, "-------------------------------------------------------------------------------"));
  DEBUG ((DEBUG_INFO, "\n    PCIDev  Slot   INT A    INT B    INT C    INT D\n"));
  for (Index = 0; Index < Slot; Index++) {
    DEBUG ((DEBUG_INFO, "%3d", Index));
    DEBUG ((DEBUG_INFO, " %02x", (UINTN)IrqRoutingEntry[Index].Bus));
    DEBUG ((DEBUG_INFO, ":%02x", (UINTN)(IrqRoutingEntry[Index].Device >> 3)));
    DEBUG ((DEBUG_INFO, "    %2x", (UINTN)IrqRoutingEntry[Index].Slot));
    DEBUG ((DEBUG_INFO, "   %02x", (UINTN)IrqRoutingEntry[Index].PirqEntry[0].Pirq));
    DEBUG ((DEBUG_INFO, "/%04x", (UINTN)IrqRoutingEntry[Index].PirqEntry[0].IrqMask));
    DEBUG ((DEBUG_INFO, "  %02x", (UINTN)IrqRoutingEntry[Index].PirqEntry[1].Pirq));
    DEBUG ((DEBUG_INFO, "/%04x", (UINTN)IrqRoutingEntry[Index].PirqEntry[1].IrqMask));
    DEBUG ((DEBUG_INFO, "  %02x", (UINTN)IrqRoutingEntry[Index].PirqEntry[2].Pirq));
    DEBUG ((DEBUG_INFO, "/%04x", (UINTN)IrqRoutingEntry[Index].PirqEntry[2].IrqMask));
    DEBUG ((DEBUG_INFO, "  %02x", (UINTN)IrqRoutingEntry[Index].PirqEntry[3].Pirq));
    DEBUG ((DEBUG_INFO, "/%04x", (UINTN)IrqRoutingEntry[Index].PirqEntry[3].IrqMask));
  }
  DEBUG ((DEBUG_INFO, "==============================================================================="));
  DEBUG ((DEBUG_INFO, "\n"));
  return ;
}

/**
  Create Pirq table.
**/
VOID *
CreatePirqTable (
  VOID
  )
{
  EFI_STATUS                       Status;
  UINT8                            Bus;
  UINT8                            Device;
  UINT8                            Function;
  EFI_LEGACY_INTERRUPT_PROTOCOL    *LegacyInterrupt;
  EFI_LEGACY_PIRQ_TABLE_HEADER     *PirqTable;
  UINT16                           TableSize;

  TableSize   = (UINT16)(sizeof (EFI_LEGACY_PIRQ_TABLE_HEADER) + gIrqBoardInfoProtocol->PicRoutLength);

  PirqTable = (EFI_LEGACY_PIRQ_TABLE_HEADER *) AllocateZeroPool (TableSize);
  ASSERT (PirqTable != NULL);
  if (PirqTable == NULL) {
    return NULL;
  }

  Status = gBS->LocateProtocol (&gEfiLegacyInterruptProtocolGuid, NULL, (VOID **) &LegacyInterrupt);
  ASSERT_EFI_ERROR (Status);

  Status = LegacyInterrupt->GetLocation (
                              LegacyInterrupt,
                              &Bus,
                              &Device,
                              &Function
                              );
  ASSERT_EFI_ERROR (Status);

  //
  // Update fields in $PIR table header
  //
  PirqTable->Signature     = EFI_LEGACY_PIRQ_TABLE_SIGNATURE;
  PirqTable->MajorVersion  = 1;
  PirqTable->MinorVersion  = 0;
  PirqTable->TableSize     = TableSize;
  PirqTable->Bus           = Bus;
  PirqTable->DevFun        = (UINT8) ((Device << 3) + Function);
  PirqTable->CompatibleVid = PciRead16 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_VENDOR_ID_OFFSET));
  PirqTable->CompatibleDid = PciRead16 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_DEVICE_ID_OFFSET));
  PirqTable->Miniport      = 0;

  CopyMem ((VOID *)(PirqTable + 1), gIrqBoardInfoProtocol->PicRoutTable, gIrqBoardInfoProtocol->PicRoutLength);

  PirqTable->Checksum = CalculateCheckSum8((VOID *)PirqTable, PirqTable->TableSize);

  return PirqTable;
}

/**
  PIRQ table builder entry point

  @return PirqTable pointer
**/
VOID *
PirqTableBuilderInit (
  VOID
  )
{
  VOID       *PirqTable;

  PirqTable = CreatePirqTable ();
  if (PirqTable == NULL) {
    return NULL;
  }

  DumpPirqTable (PirqTable);

  return PirqTable;
}
