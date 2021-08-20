/** @file
  MPS table builder functions implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <Guid/Mps.h>
#include <Guid/Acpi.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/LegacyBiosMpTable.h>
#include <Protocol/MpService.h>
#include <Protocol/IrqBoardInfo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Register/LocalApic.h>
#include <Register/Msr.h>
#include "MpTablePlatformConfig.h"

extern IRQ_BOARD_INFO_PROTOCOL *gIrqBoardInfoProtocol;

typedef struct _ISO_PARAMETER_TABLE{
  UINT8   PicIrq;
  UINT8   Trigger;
  UINT8   Polarity;
  UINT16  ApicInt;
} ISO_PARAMETER_TABLE;

typedef struct _MP_TABLE_CPU_INFO {
  UINT8   ApicVersion;
  UINT32  CpuSignature;
  UINT32  FeatureFlags;
} MP_TABLE_CPU_INFO;

typedef struct _BUS_INFO {
  UINT8   BusId;
  UINT8   ParentBusId;
  UINT8   BusType;
  UINT8   Flags;
  UINT8   Attributes;
} BUS_INFO;

typedef struct _IO_APIC_INFO {
  UINT8   IoApicId;
  UINT8   IoApicVersion;
  UINT8   IoApicFlags;
  UINT8   MaxRedirectionEntries;
  UINT32  IoApicAddress;
} IO_APIC_INFO;

//
// Here goes Interrupt Source Override MADT entry parameter table
//
GLOBAL_REMOVE_IF_UNREFERENCED ISO_PARAMETER_TABLE mIsoTbl[]={
{ 0xFF, 0,                   0,               0              },
{ 0xFF, 0,                   0,               1              },
//just dummy entry instead of IRQ2 to keep array consistent
{ 0xFF, 0,                   0,               2              },
{ 0xFF, 0,                   0,               3              },
{ 0xFF, 0,                   0,               4              },
{ 0xFF, 0,                   0,               5              },
{ 0xFF, 0,                   0,               6              },
{ 0xFF, 0,                   0,               7              },
{ 0xFF, 0,                   0,               8              },
{ 0xFF, 0,                   0,               9              },
{ 0xFF, 0,                   0,               10             },
{ 0xFF, 0,                   0,               11             },
{ 0xFF, 0,                   0,               12             },
{ 0xFF, 0,                   0,               13             },
{ 0xFF, 0,                   0,               14             },
{ 0xFF, 0,                   0,               15             },
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_LEGACY_MP_TABLE_FLOATING_POINTER mMpsTableFloatingPointer;
GLOBAL_REMOVE_IF_UNREFERENCED VOID    *mMpsTablePointer = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED VOID    *mMpsTableCurrentPointer = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED VOID    *mMpsExTablePointer = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED VOID    *mMpsExTableCurrentPointer = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16  mBaseTableLength = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16  mBaseTableEntryCount = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16  mExtendedTableLength = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8   mOemId[8];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8   mProductId[12];

GLOBAL_REMOVE_IF_UNREFERENCED BUS_INFO mBusEntry[MP_TABLE_MAX_BUS_ENTRIES];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8    mMaxBusId = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8    mCurrentBusEntry = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8    mIsaBusId = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8    *mBusTypeString[] = {
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_CBUS,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_CBUSII,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_EISA,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_FUTURE,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_INTERN,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_ISA,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_MBI,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_MBII,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_MCA,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_MPI,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_MPSA,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_NUBUS,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_PCI,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_PCMCIA,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_TC,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_VL,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_VME,
  (UINT8 *) EFI_LEGACY_MP_TABLE_ENTRY_BUS_STRING_XPRESS
};

//
// each number represents corresponding
// number in mBusTypeString array, i.e.
// bridge subclass 0 - PCI host has number
// 12 in array, subclass 1 - ISA bridge -
// number 5 etc.
//
#define PCI_BUS_INDEX     12
#define ISA_BUS_INDEX     5
#define EISA_BUS_INDEX    2
#define MCA_BUS_INDEX     8
#define P2P_BUS_INDEX     12
#define PCMCIA_BUS_INDEX  13
#define NU_BUS_INDEX      11
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mBridgeBusTypes[] = {
  PCI_BUS_INDEX,
  ISA_BUS_INDEX,
  EISA_BUS_INDEX,
  MCA_BUS_INDEX,
  P2P_BUS_INDEX,
  PCMCIA_BUS_INDEX,
  NU_BUS_INDEX
  };
GLOBAL_REMOVE_IF_UNREFERENCED IO_APIC_INFO mIoApicEntry[MP_TABLE_MAX_IO_APIC_ENTRIES];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8        mCurrentIoApicEntry = 0;

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gCpuFlagStr[] = {
  "AP, unusable ",
  "AP, usable   ",
  "BSP, unusable",
  "BSP, usable  "
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gIoApicFlagStr[] = {
  "unusable",
  "  usable"
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gInterruptTypeStr[] = {
  "INT   ",
  "NMI   ",
  "SMI   ",
  "ExtINT"
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gPolarityStr[] = {
  " conforms",
  "active-hi",
  " reserved",
  "active-lo"
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gTriggerStr[] = {
  "conforms",
  "    edge",
  "reserved",
  "   level"
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gSystemAddressTypeStr[] = {
  "I/O address",
  "memory address",
  "prefetch address"
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *gAddressModifierStr[] = {
  "add",
  "subtract"
};

/**
  Dump Mps Table.

  @param MpTable MP table pointer
**/
VOID
DumpMpsTable (
  IN VOID *MpTable
  )
{
  EFI_LEGACY_MP_TABLE_FLOATING_POINTER                           *MpFloatingPtr;
  EFI_LEGACY_MP_TABLE_HEADER                                     *MpConfigurationTableHeader;
  CHAR8                                                          *Signature;
  UINTN                                                          Index;
  EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR                            *MpCpuEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_BUS                                  *MpBusEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC                               *MpIoApicEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_IO_INT                               *MpIntAssignEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT                            *MpLocalIntAssignEntry;
  VOID                                                           *MpExBuffer;
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING           *MpExSysAddressMapEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY                    *MpExBusHierarchyEntry;
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER   *MpExCompatBusAddressModifierEntry;

  MpFloatingPtr = (EFI_LEGACY_MP_TABLE_FLOATING_POINTER *)MpTable;

  DEBUG ((DEBUG_INFO, "===============================================================================\n"));
  DEBUG ((DEBUG_INFO, "MP Floating Pointer Structure:\n"));
  DEBUG ((DEBUG_INFO, "  physical address:             0x%08x\n", (UINTN)MpFloatingPtr));
  Signature = (CHAR8 *)&MpFloatingPtr->Signature;
  DEBUG ((DEBUG_INFO, "  signature:                    '%c%c%c%c'\n", (UINTN)Signature[0], (UINTN)Signature[1], (UINTN)Signature[2], (UINTN)Signature[3]));
  DEBUG ((DEBUG_INFO, "  length:                       %d bytes\n", (UINTN)MpFloatingPtr->Length));
  DEBUG ((DEBUG_INFO, "  version:                      1.%d\n", (UINTN)MpFloatingPtr->SpecRev));
  DEBUG ((DEBUG_INFO, "  checksum:                     0x%02x\n", (UINTN)MpFloatingPtr->Checksum));
  DEBUG ((DEBUG_INFO, "  mode:                         %a\n", (MpFloatingPtr->FeatureByte2_5.Imcr == 0) ? "Virtual Wire" : "PIC"));

  MpConfigurationTableHeader = (EFI_LEGACY_MP_TABLE_HEADER *)(UINTN)MpFloatingPtr->PhysicalAddress;
  DEBUG ((DEBUG_INFO, "-------------------------------------------------------------------------------\n"));
  DEBUG ((DEBUG_INFO, "MP Config Table Header:\n"));
  DEBUG ((DEBUG_INFO, "  physical address:             0x%08x\n", (UINTN)MpConfigurationTableHeader));
  Signature = (CHAR8 *)&MpConfigurationTableHeader->Signature;
  DEBUG ((DEBUG_INFO, "  signature:                    '%c%c%c%c'\n", (UINTN)Signature[0], (UINTN)Signature[1], (UINTN)Signature[2], (UINTN)Signature[3]));
  DEBUG ((DEBUG_INFO, "  base table length:            %d\n", (UINTN)MpConfigurationTableHeader->BaseTableLength));
  DEBUG ((DEBUG_INFO, "  version:                      1.%d\n", (UINTN)MpConfigurationTableHeader->SpecRev));
  DEBUG ((DEBUG_INFO, "  checksum:                     0x%02x\n", (UINTN)MpConfigurationTableHeader->Checksum));
  DEBUG ((DEBUG_INFO, "  OEM ID:                       '"));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[0]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[1]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[2]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[3]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[4]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[5]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[6]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemId[7]));
  DEBUG ((DEBUG_INFO, "'\n"));
  DEBUG ((DEBUG_INFO, "  Product ID:                   '"));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[0]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[1]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[2]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[3]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[4]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[5]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[6]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[7]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[8]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[9]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[10]));
  DEBUG ((DEBUG_INFO, "%c", (UINTN)MpConfigurationTableHeader->OemProductId[11]));
  DEBUG ((DEBUG_INFO, "'\n"));
  DEBUG ((DEBUG_INFO, "  OEM table pointer:            0x%08x\n", (UINTN)MpConfigurationTableHeader->OemTablePointer));
  DEBUG ((DEBUG_INFO, "  OEM table size:               %d\n", (UINTN)MpConfigurationTableHeader->OemTableSize));
  DEBUG ((DEBUG_INFO, "  entry count:                  %d\n", (UINTN)MpConfigurationTableHeader->EntryCount));
  DEBUG ((DEBUG_INFO, "  local APIC address:           0x%08x\n", (UINTN)MpConfigurationTableHeader->LocalApicAddress));
  DEBUG ((DEBUG_INFO, "  extended table length:        %d\n", (UINTN)MpConfigurationTableHeader->ExtendedTableLength));
  DEBUG ((DEBUG_INFO, "  extended table checksum:      %d\n", (UINTN)MpConfigurationTableHeader->ExtendedChecksum));

  DEBUG ((DEBUG_INFO, "-------------------------------------------------------------------------------\n"));
  DEBUG ((DEBUG_INFO, "MP Config Base Table Entries:\n"));
  DEBUG ((DEBUG_INFO, "--\n"));
  DEBUG ((DEBUG_INFO, "Processors:     APIC ID Version State           Family  Model   Step    Flags\n"));
  MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (MpCpuEntry->EntryType) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
//      MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
      MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
      MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
      MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
      MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      continue;
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    DEBUG ((DEBUG_INFO, "                %2d       0x%02x    %a  %2d       %2d     %2d       0x%08x\n",
      (UINTN)MpCpuEntry->Id,
      (UINTN)MpCpuEntry->Ver,
      gCpuFlagStr[MpCpuEntry->Flags.Enabled + (MpCpuEntry->Flags.Bsp << 1)],
      (UINTN)(MpCpuEntry->Signature.Family),
      (UINTN)(MpCpuEntry->Signature.Model),
      (UINTN)(MpCpuEntry->Signature.Stepping),
      (UINTN)*(UINT32 *)&MpCpuEntry->Features
      ));
    MpCpuEntry = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *)((UINTN)MpCpuEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
  }
  DEBUG ((DEBUG_INFO, "--\n"));
  DEBUG ((DEBUG_INFO, "Bus:            Bus ID  Type\n"));
  MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (MpBusEntry->EntryType) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
      MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
//      MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
      MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
      MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
      MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      continue;
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    DEBUG ((DEBUG_INFO, "                %2d       %c%c%c%c%c%c\n",
      (UINTN)MpBusEntry->Id,
      (UINTN)MpBusEntry->TypeString[0],
      (UINTN)MpBusEntry->TypeString[1],
      (UINTN)MpBusEntry->TypeString[2],
      (UINTN)MpBusEntry->TypeString[3],
      (UINTN)MpBusEntry->TypeString[4],
      (UINTN)MpBusEntry->TypeString[5]
      ));
    MpBusEntry = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)((UINTN)MpBusEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
  }
  DEBUG ((DEBUG_INFO, "--\n"));
  DEBUG ((DEBUG_INFO, "I/O APICs:      APIC ID Version State           Address\n"));
  MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (MpIoApicEntry->EntryType) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
      MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
      MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
//      MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
      MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
      MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      continue;
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    DEBUG ((DEBUG_INFO, "                %2d       0x%02x  %a          0x%08x\n",
      (UINTN)MpIoApicEntry->Id,
      (UINTN)MpIoApicEntry->Ver,
      gIoApicFlagStr[MpIoApicEntry->Flags.Enabled],
      (UINTN)MpIoApicEntry->Address
      ));
    MpIoApicEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)((UINTN)MpIoApicEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
  }
  DEBUG ((DEBUG_INFO, "--\n"));
  DEBUG ((DEBUG_INFO, "I/O Ints:       Type    Polarity    Trigger     Bus ID   IRQ    APIC ID PIN#\n"));
  MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (MpIntAssignEntry->EntryType) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
      MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
      MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
      MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
//      MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
      MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      continue;
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    if (MpIntAssignEntry->DestApicIntIn < 16) {
      DEBUG ((DEBUG_INFO, "                %a  %a    %a      %3d    %2d        %3d   %2d\n",
        gInterruptTypeStr[MpIntAssignEntry->IntType],
        gPolarityStr[MpIntAssignEntry->Flags.Polarity],
        gTriggerStr[MpIntAssignEntry->Flags.Trigger],
        (UINTN)MpIntAssignEntry->SourceBusId,
        (UINTN)MpIntAssignEntry->SourceBusIrq.byte,
        (UINTN)MpIntAssignEntry->DestApicId,
        (UINTN)MpIntAssignEntry->DestApicIntIn
        ));
    } else {
      DEBUG ((DEBUG_INFO, "                %a  %a    %a      %3d  %2d:%c        %3d   %2d\n",
        gInterruptTypeStr[MpIntAssignEntry->IntType],
        gPolarityStr[MpIntAssignEntry->Flags.Polarity],
        gTriggerStr[MpIntAssignEntry->Flags.Trigger],
        (UINTN)MpIntAssignEntry->SourceBusId,
        (UINTN)MpIntAssignEntry->SourceBusIrq.fields.Dev,
        (UINTN)(MpIntAssignEntry->SourceBusIrq.fields.IntNo + 'A'),
        (UINTN)MpIntAssignEntry->DestApicId,
        (UINTN)MpIntAssignEntry->DestApicIntIn
        ));
    }
    MpIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)((UINTN)MpIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
  }
  DEBUG ((DEBUG_INFO, "--\n"));
  DEBUG ((DEBUG_INFO, "Local Ints:     Type    Polarity    Trigger     Bus ID   IRQ    APIC ID PIN#\n"));
  MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (MpLocalIntAssignEntry->EntryType) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
      MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
      MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
      MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
      MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      continue;
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
//      MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    DEBUG ((DEBUG_INFO, "                %a  %a    %a      %3d  %2d:%c        %3d   %2d\n",
      gInterruptTypeStr[MpLocalIntAssignEntry->IntType],
      gPolarityStr[MpLocalIntAssignEntry->Flags.Polarity],
      gTriggerStr[MpLocalIntAssignEntry->Flags.Trigger],
      (UINTN)MpLocalIntAssignEntry->SourceBusId,
      (UINTN)MpLocalIntAssignEntry->SourceBusIrq.fields.Dev,
      (UINTN)(MpLocalIntAssignEntry->SourceBusIrq.fields.IntNo + 'A'),
      (UINTN)MpLocalIntAssignEntry->DestApicId,
      (UINTN)MpLocalIntAssignEntry->DestApicIntIn
      ));
    MpLocalIntAssignEntry = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)((UINTN)MpLocalIntAssignEntry + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
  }

  MpExBuffer = (VOID *)(MpConfigurationTableHeader + 1);
  for (Index = 0; Index < MpConfigurationTableHeader->EntryCount; Index++) {
    switch (*(UINT8 *)MpExBuffer) {
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR:
      MpExBuffer = (VOID *)((UINTN)MpExBuffer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS:
      MpExBuffer = (VOID *)((UINTN)MpExBuffer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC:
      MpExBuffer = (VOID *)((UINTN)MpExBuffer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT:
      MpExBuffer = (VOID *)((UINTN)MpExBuffer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      break;
    case EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT:
      MpExBuffer = (VOID *)((UINTN)MpExBuffer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }
  DEBUG ((DEBUG_INFO, "-------------------------------------------------------------------------------\n"));
  DEBUG ((DEBUG_INFO, "MP Config Extended Table Entries:\n"));

  MpExSysAddressMapEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING *)MpExBuffer;
  for (Index = 0; Index < MpConfigurationTableHeader->ExtendedTableLength; ) {
    if (MpExSysAddressMapEntry->EntryType == EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_SYS_ADDR_SPACE_MAPPING) {
      DEBUG ((DEBUG_INFO, "--\n"));
      DEBUG ((DEBUG_INFO, "System Address Space\n"));
      DEBUG ((DEBUG_INFO, " bus ID: %d address type: %a\n",
        (UINTN)MpExSysAddressMapEntry->BusId,
        gSystemAddressTypeStr[MpExSysAddressMapEntry->AddressType]
        ));
      DEBUG ((DEBUG_INFO, " address base: 0x%lx\n", (UINTN)MpExSysAddressMapEntry->AddressBase));
      DEBUG ((DEBUG_INFO, " address range: 0x%lx\n", (UINTN)MpExSysAddressMapEntry->AddressLength));
    }
    Index += MpExSysAddressMapEntry->Length;
    MpExSysAddressMapEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING *)((UINTN)MpExSysAddressMapEntry + MpExSysAddressMapEntry->Length);
  }

  MpExBusHierarchyEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY *)MpExBuffer;
  for (Index = 0; Index < MpConfigurationTableHeader->ExtendedTableLength; ) {
    if (MpExBusHierarchyEntry->EntryType == EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_BUS_HIERARCHY) {
      DEBUG ((DEBUG_INFO, "--\n"));
      DEBUG ((DEBUG_INFO, "Bus Heirarchy\n"));
      DEBUG ((DEBUG_INFO, " bus ID: %d bus info: 0x%02x parent bus ID: %d\n",
        (UINTN)MpExBusHierarchyEntry->BusId,
        (UINTN)*(UINT8 *)&MpExBusHierarchyEntry->BusInfo,
        (UINTN)MpExBusHierarchyEntry->ParentBus
        ));
    }
    Index += MpExBusHierarchyEntry->Length;
    MpExBusHierarchyEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY *)((UINTN)MpExBusHierarchyEntry + MpExBusHierarchyEntry->Length);
  }

  MpExCompatBusAddressModifierEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER *)MpExBuffer;
  for (Index = 0; Index < MpConfigurationTableHeader->ExtendedTableLength; ) {
    if (MpExCompatBusAddressModifierEntry->EntryType == EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_COMPAT_BUS_ADDR_SPACE_MODIFIER) {
      DEBUG ((DEBUG_INFO, "--\n"));
      DEBUG ((DEBUG_INFO, "Compatibility Bus Address\n"));
      DEBUG ((DEBUG_INFO, " bus ID: %d address modifier: %a\n",
        (UINTN)MpExCompatBusAddressModifierEntry->BusId,
        gAddressModifierStr[MpExCompatBusAddressModifierEntry->AddrMode.RangeMode]
        ));
      DEBUG ((DEBUG_INFO, " predefined range: 0x%08x\n", (UINTN)MpExCompatBusAddressModifierEntry->PredefinedRangeList));
    }
    Index += MpExCompatBusAddressModifierEntry->Length;
    MpExCompatBusAddressModifierEntry = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER *)((UINTN)MpExCompatBusAddressModifierEntry + MpExCompatBusAddressModifierEntry->Length);
  }

  DEBUG ((DEBUG_INFO, "===============================================================================\n"));

}

/**
  Returns IO APIC ID and Pin number assosiated with given SysVectorNumber

  @param SysVectorNumber - SysVectorNumber
  @param IoApicId        - Io Apic Id
  @param IoApicItin      - Pin Number
**/
VOID
GetIoApicId (
  IN UINT16 SysVectorNumber,
  OUT UINT8 *IoApicId,
  OUT UINT8 *IoApicItin
  )
{
  UINT8 Index;

  for (Index = 0; Index < mCurrentIoApicEntry; Index++) {
    if (SysVectorNumber < mIoApicEntry[Index].MaxRedirectionEntries) {
      //
      // this is Apic we need
      //
      *IoApicId   = mIoApicEntry[Index].IoApicId;
      *IoApicItin = (UINT8)SysVectorNumber;
      return;
    }
    SysVectorNumber = SysVectorNumber - mIoApicEntry[Index].MaxRedirectionEntries;
  }
}

/**
  Arranges IO APIC Entries in their ID ascending order
**/
VOID
ArrangeIoApicEntries (
  VOID
  )
{
  UINT8        Index;
  BOOLEAN      Swap;
  IO_APIC_INFO Temp;

  //
  // Make sure mIoApicEntry is large enough and the index of mIoApicEntry array is valid
  //
  ASSERT (mCurrentIoApicEntry <= MP_TABLE_MAX_IO_APIC_ENTRIES);

  Swap = TRUE;
  while (Swap) {
    Swap = FALSE;
    for (Index = 0; Index < mCurrentIoApicEntry - 1; Index++) {
      if (mIoApicEntry[Index].IoApicId > mIoApicEntry[Index + 1].IoApicId) {
        Swap = TRUE;
        CopyMem (&Temp, &mIoApicEntry[Index], sizeof(IO_APIC_INFO));
        CopyMem (&mIoApicEntry[Index], &mIoApicEntry[Index + 1], sizeof(IO_APIC_INFO));
        CopyMem (&mIoApicEntry[Index + 1], &Temp, sizeof(IO_APIC_INFO));
      }
    }
  }
}

/**
  Retreive system info about IO APIC

  @param PciIoProtocol - Pointer to PciIo Protocol
  @param BaseAddress   - Base Address
**/
VOID
CollectIoApicInfo (
  IN EFI_PCI_IO_PROTOCOL *PciIoProtocol OPTIONAL,
  IN UINT32              BaseAddress OPTIONAL
  )
{
  UINT32          IoApicAddress;
  EFI_STATUS      Status;
  UINT32 volatile *IoApicMemory32;
  UINT8  volatile *IoApicMemory8;
  UINT32          Data;

  //
  // IO APIC visible as PCI device
  //
  IoApicAddress = 0;
  if (BaseAddress == 0) {
    Status = PciIoProtocol->Pci.Read (
                              PciIoProtocol,
                              EfiPciIoWidthUint32,
                              PCI_BASE_ADDRESSREG_OFFSET,
                              1,
                              (VOID*)&IoApicAddress
                              );
    if (EFI_ERROR(Status) || (IoApicAddress == 0)) {
      //
      // problem or mapped to default address range
      //
      return;
    }
  } else {
    //
    // IO APIC mapped to default range
    //
    IoApicAddress = BaseAddress;
  }

  IoApicMemory32 = (UINT32 *)(UINTN)IoApicAddress;
  IoApicMemory8 = (UINT8 *)(UINTN)IoApicAddress;

  MmioWrite8 ((UINTN)&IoApicMemory8[IO_APIC_INDEX_REG], IO_APIC_MAP_ID_REG);
  Data = MmioRead32 ((UINTN)&IoApicMemory32[IO_APIC_DATA_REG]);

  //
  // Make sure mIoApicEntry is large enough and the index of mIoApicEntry array is valid
  //
  ASSERT (mCurrentIoApicEntry < MP_TABLE_MAX_IO_APIC_ENTRIES);

  mIoApicEntry[mCurrentIoApicEntry].IoApicId = (UINT8)((Data & 0x0F000000) >> 24);

  MmioWrite8 ((UINTN)&IoApicMemory8[IO_APIC_INDEX_REG], IO_APIC_MAP_VERSION_REG);
  Data = MmioRead32 ((UINTN)&IoApicMemory32[IO_APIC_DATA_REG]);

  mIoApicEntry[mCurrentIoApicEntry].IoApicVersion         = (UINT8)(Data & 0xFF);
  mIoApicEntry[mCurrentIoApicEntry].MaxRedirectionEntries = (UINT8)(((Data & 0x00FF0000) >> 16)+1);
  mIoApicEntry[mCurrentIoApicEntry].IoApicFlags           = 1;
  mIoApicEntry[mCurrentIoApicEntry].IoApicAddress         = IoApicAddress;

  mCurrentIoApicEntry++;
}

/**
  Checks if x2Apic is enabled

  @retval true if x2Apic is enabled
  @retval false if x2Apic is disabled
**/
BOOLEAN
IsXapicEnabled (
  VOID
  )
{
  UINT64 MsrValue;

  MsrValue = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  if (MsrValue & B_EFI_MSR_IA32_APIC_BASE_G_XAPIC) {
     if (MsrValue & B_EFI_MSR_IA32_APIC_BASE_M_XAPIC) {
       return TRUE;
     } else {
       return FALSE;
     }
  } else {
    return FALSE;
  }
}

/**
  Gets Apic Version

  @return Apic Version
**/
UINT8
GetApicVersion (
  VOID
  )
{
  UINT64  ApicBaseReg;
  UINT8   LocalApicVersion;
  UINT64  LocalApicBase;
  UINTN   MsrValue;
  BOOLEAN XapicEnabled;

  XapicEnabled = IsXapicEnabled ();

  if (XapicEnabled) {
    //
    // According Nehalem BWG, if Extended XAPIC Mode
    // is enabled, legacy xAPIC is no longer working.
    // So, previous MMIO offset must be transfered
    // to MSR offset R/W.
    // MMIO Offset     MSR Offset     Register Name
    //  020h             802h         MSR_IA32_X2APIC_APICID
    //  030h             803h         MSR_IA32_X2APIC_VERSION
    //
    MsrValue = (UINTN)AsmReadMsr64 (MSR_IA32_X2APIC_VERSION);
    LocalApicVersion  = (UINT8) (MsrValue  & 0xff);
  } else {
    ApicBaseReg   = AsmReadMsr64 (MSR_IA32_APIC_BASE);
    LocalApicBase = ApicBaseReg & 0xffffff000;

    //
    // if Apic is not enabled yet, enable it here
    //
    if ((ApicBaseReg & B_EFI_MSR_IA32_APIC_BASE_G_XAPIC) == 0) {
      ApicBaseReg |= B_EFI_MSR_IA32_APIC_BASE_G_XAPIC;
      AsmWriteMsr64 (MSR_IA32_APIC_BASE, ApicBaseReg);
    }

    LocalApicVersion  = (UINT8)MmioRead32 ((UINTN) (LocalApicBase + XAPIC_VERSION_OFFSET));
  }

  return (LocalApicVersion);
}

/**
  Fills MpTable value for AP for LocalApicVersion,CpuSignature,FeatureFlags

  @param Buffer - pointer to MP_TABLE_CPU_INFO structure;

  @return LocalApicVersion,CpuSignature,FeatureFlags
**/
VOID
EFIAPI
FillMpTableValueAp (
  IN OUT VOID *Buffer
  )
{
  UINT32                  RegEax;
  UINT32                  RegEbx;
  UINT32                  RegEcx;
  UINT32                  RegEdx;
  MP_TABLE_CPU_INFO       *CpuInfo;

  CpuInfo = (MP_TABLE_CPU_INFO *)Buffer;

  //
  // Get Apic Version
  //
  CpuInfo->ApicVersion = GetApicVersion();

  //
  // Get CpuSignature and Feature flags
  //
  AsmCpuid (1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
  CpuInfo->CpuSignature = RegEax;
  CpuInfo->FeatureFlags = RegEdx;
}

/**
  Adds CPU entries to MPS table

  @return Number of entries added
**/
UINT16
MpsTableAddCpuEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR        *EntryPointer;
  MP_TABLE_CPU_INFO                          CpuInfo;
  UINT16                                     EntryCount;
  EFI_STATUS                                 Status;
  UINTN                                      Index;
  UINTN                                      NumberOfProcessors;
  UINTN                                      NumberOfEnabledProcessors;
  EFI_MP_SERVICES_PROTOCOL                   *MpServices;
  EFI_PROCESSOR_INFORMATION                  ProcContext;
  UINTN                                      MyCpuNumber;

  EntryCount    = 0;
  EntryPointer  = (EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR *) mMpsTableCurrentPointer;
  SetMem(&CpuInfo, sizeof(MP_TABLE_CPU_INFO), 0);
  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, (VOID **) &MpServices);

  //
  // If no MpService available, we've got a UniProccessor System
  //
  if (EFI_ERROR (Status)) {
    FillMpTableValueAp(&CpuInfo);

    ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
    EntryPointer->EntryType             = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR;
    EntryPointer->Id                    = 0;
    EntryPointer->Ver                   = CpuInfo.ApicVersion;
    EntryPointer->Flags.Enabled         = 1;
    EntryPointer->Flags.Bsp             = 1;
    CopyMem (&EntryPointer->Signature, &CpuInfo.CpuSignature, sizeof(EntryPointer->Signature));
    CopyMem (&EntryPointer->Features,  &CpuInfo.FeatureFlags, sizeof(EntryPointer->Features));
    //
    // just one CPU entry
    //
    return 1;
  }

  Status = MpServices->GetNumberOfProcessors (
                         MpServices,
                         &NumberOfProcessors,
                         &NumberOfEnabledProcessors
                         );
  ASSERT_EFI_ERROR (Status);

  //
  // Get current running CPU number
  //
  Status = MpServices->WhoAmI (
                        MpServices,
                        &MyCpuNumber
                        );
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < NumberOfProcessors; Index += 1) {
    Status = MpServices->GetProcessorInfo (
                           MpServices,
                           Index,
                           &ProcContext
                           );
    if (EFI_ERROR (Status)) {
      break;
    }

    if (ProcContext.Location.Thread != 0) {
      //
      // No need to add HT threads to the MP table
      //
      continue;
    }

    if (Index == MyCpuNumber) {
      //
      // Bsp
      //
      FillMpTableValueAp(&CpuInfo);
    } else {
      MpServices->StartupThisAP (
                    MpServices,
                    FillMpTableValueAp,
                    Index,
                    NULL,
                    0,
                    &CpuInfo,
                    NULL
                    );
    }

    if (ProcContext.ProcessorId <= 0xFF) {
      ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR));
      EntryPointer->EntryType             = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_PROCESSOR;
      EntryPointer->Id                    = (UINT8) ProcContext.ProcessorId;
      EntryPointer->Ver                   = CpuInfo.ApicVersion;
      EntryPointer->Flags.Enabled         = (ProcContext.StatusFlag & PROCESSOR_ENABLED_BIT) ? 1 : 0;
      EntryPointer->Flags.Bsp             = (ProcContext.StatusFlag & PROCESSOR_AS_BSP_BIT) ? 1: 0;
      CopyMem (&EntryPointer->Signature, &CpuInfo.CpuSignature, sizeof(EntryPointer->Signature));
      CopyMem (&EntryPointer->Features,  &CpuInfo.FeatureFlags, sizeof(EntryPointer->Features));

      EntryPointer++;
      EntryCount++;
    }

  }

  return EntryCount;
}

/**
  Creates Extended MPS table bus hierarchy entryies
**/
VOID
MpsExTableAddBusHierarchyEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY *EntryPointer;
  UINT8                                       Index;

  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY *)mMpsExTableCurrentPointer;

  for (Index = 0; Index < mCurrentBusEntry; Index++) {
    //
    // skip root bridge and P2P bridge
    //
    if (mBusEntry[Index].ParentBusId != 0xFF && mBusEntry[Index].BusType != PCI_BUS_INDEX) {
      ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY));
      EntryPointer->EntryType   = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_BUS_HIERARCHY;
      EntryPointer->Length      = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY);
      EntryPointer->BusId       = mBusEntry[Index].BusId;
      EntryPointer->BusInfo.SubtractiveDecode = mBusEntry[Index].Flags;
      EntryPointer->ParentBus   = mBusEntry[Index].ParentBusId;

      EntryPointer++;
      mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_BUS_HIERARCHY);
    }
  }
  mMpsExTableCurrentPointer = (VOID *)EntryPointer;
}

/**
  Creates Extended MPS table compatibility bus address space
  modifier entryies
**/
VOID
MpsExTableAddCompatBusAddressModifierEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER *EntryPointer;
  UINT8                                                        Index;

  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER *)mMpsExTableCurrentPointer;

  for (Index = 0; Index < mCurrentBusEntry; Index++) {
    if (mBusEntry[Index].ParentBusId == 0xFF) {
      //
      // add/subtract ISA predefined range
      //
      ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER));
      EntryPointer->EntryType   = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_COMPAT_BUS_ADDR_SPACE_MODIFIER;
      EntryPointer->Length      = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER);
      EntryPointer->BusId       = mBusEntry[Index].BusId;
      //
      // isa range list
      //
      EntryPointer->PredefinedRangeList = 0;
      EntryPointer->AddrMode.RangeMode = (mBusEntry[Index].Attributes & (EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO | EFI_PCI_ATTRIBUTE_ISA_IO)) ? 0 : 1;

      EntryPointer++;
      mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER);

      //
      // add/subtract VGA predefined range
      //
      ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER));
      EntryPointer->EntryType   = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_COMPAT_BUS_ADDR_SPACE_MODIFIER;
      EntryPointer->Length      = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER);
      EntryPointer->BusId       = mBusEntry[Index].BusId;
      //
      // vga range list
      //
      EntryPointer->PredefinedRangeList = 1;
      EntryPointer->AddrMode.RangeMode = (mBusEntry[Index].Attributes & (EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO | EFI_PCI_ATTRIBUTE_VGA_MEMORY | EFI_PCI_ATTRIBUTE_VGA_IO)) ? 0 : 1;

      EntryPointer++;
      mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_COMPAT_BUS_ADDR_SPACE_MODIFIER);
    }
  }
  mMpsExTableCurrentPointer = (VOID *)EntryPointer;
}

/**
  Creates Extended MPS table system address space map entryies

  @param PciRootBridgeIoProtocol   - Pointer to PciRootBridgeIo protocol
  @param BusId                     - Bus ID
  @param BusAttributes             - Attributes of Bus
**/
VOID
MpsExTableAddSysAddressMapEntry (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIoProtocol,
  IN UINT8                           BusId,
  IN UINT8                           BusAttributes
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING *EntryPointer;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR                    *Resources;
  BOOLEAN                                              VgaMemoryAdded;

  VgaMemoryAdded = FALSE;
  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING *)mMpsExTableCurrentPointer;

  PciRootBridgeIoProtocol->Configuration (PciRootBridgeIoProtocol, (VOID **) &Resources);

  //
  // add entries to ISA decode
  //
  if (BusAttributes & (EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO | EFI_PCI_ATTRIBUTE_ISA_IO)) {
    //
    // support ISA I/O space
    //
    EntryPointer->EntryType   = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_SYS_ADDR_SPACE_MAPPING;
    EntryPointer->Length      = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
    EntryPointer->BusId       = BusId;
    //
    // IO descriptor
    //
    EntryPointer->AddressType = EfiLegacyMpTableEntryExtSysAddrSpaceMappingIo;
    EntryPointer->AddressBase = 0;
    EntryPointer->AddressLength = 0x1000;
    EntryPointer++;
    mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
  }

  while (Resources->Desc == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    if (Resources->ResType != ACPI_ADDRESS_SPACE_TYPE_BUS  && Resources->AddrLen != 0) {
      if (Resources->ResType == ACPI_ADDRESS_SPACE_TYPE_IO) {
        //
        // IO descriptor
        //
        EntryPointer->AddressType = EfiLegacyMpTableEntryExtSysAddrSpaceMappingIo;
      } else if (Resources->SpecificFlag & EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE) {
        //
        // memory prefetch address
        //
        EntryPointer->AddressType = EfiLegacyMpTableEntryExtSysAddrSpaceMappingPrefetch;
      } else {
        //
        // memory descriptor
        //
        EntryPointer->AddressType = EfiLegacyMpTableEntryExtSysAddrSpaceMappingMemory;
      }

      //
      // VGA region should be at the beginning of Memory range
      //
      if ((EntryPointer->AddressType == EfiLegacyMpTableEntryExtSysAddrSpaceMappingMemory) &&
          (BusAttributes & (EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO | EFI_PCI_ATTRIBUTE_VGA_MEMORY | EFI_PCI_ATTRIBUTE_VGA_IO)) &&
          (!(VgaMemoryAdded))) {
        EntryPointer->EntryType   = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_SYS_ADDR_SPACE_MAPPING;
        EntryPointer->Length      = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
        EntryPointer->BusId       = BusId;
        //
        // memory descriptor
        //
        EntryPointer->AddressType   = EfiLegacyMpTableEntryExtSysAddrSpaceMappingMemory;
        EntryPointer->AddressBase   = 0xA0000;
        EntryPointer->AddressLength = 0x20000;
        EntryPointer++;
        mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
        VgaMemoryAdded = TRUE;
        //
        // memory descriptor
        //
        EntryPointer->AddressType = EfiLegacyMpTableEntryExtSysAddrSpaceMappingMemory;
      }

      EntryPointer->EntryType     = EFI_LEGACY_MP_TABLE_ENTRY_EXT_TYPE_SYS_ADDR_SPACE_MAPPING;
      EntryPointer->Length        = sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
      EntryPointer->BusId         = BusId;
      EntryPointer->AddressBase   = Resources->AddrRangeMin;
      EntryPointer->AddressLength = Resources->AddrLen;

      EntryPointer++;
      mExtendedTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_EXT_SYS_ADDR_SPACE_MAPPING);
    }
    Resources++;
  }

  mMpsExTableCurrentPointer = (VOID *)EntryPointer;

  return;
}

/**
  Retreive system info about buses and bus ierarchy and fills
  BUS_INFO structure. Also creates MPS table extended entries
**/
VOID
QueryBusInfo (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        *HandleBuffer;
  UINTN                             NumberOfHandles;
  UINTN                             Index;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *PciRootBridgeIoProtocol;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *AddressDescriptor;
  EFI_PCI_IO_PROTOCOL               *PciIoProtocol;
  UINT8                             PciData[4];
  UINTN                             BusNumber;
  UINTN                             Dummy[3];
  UINT64                            SupportedAttributes;

  //
  // First detect and retreive bus Id for PCI host (root) buses
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    return;
  }

  for (Index = 0; Index < NumberOfHandles; Index++) {
    if (mCurrentBusEntry >= MP_TABLE_MAX_BUS_ENTRIES) {
      break;
    }

    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciRootBridgeIoProtocolGuid,
                    (VOID**)&PciRootBridgeIoProtocol
                    );

    Status = PciRootBridgeIoProtocol->Configuration (
                                        PciRootBridgeIoProtocol,
                                        (VOID **) &AddressDescriptor
                                        );
    Status = PciRootBridgeIoProtocol->GetAttributes (
                                        PciRootBridgeIoProtocol,
                                        &SupportedAttributes,
                                        NULL
                                        );

    //
    // find bus range decoding - the min will be host PCI bus Id
    //
    while ((AddressDescriptor->Desc == ACPI_ADDRESS_SPACE_DESCRIPTOR) &&
           (AddressDescriptor->ResType != ACPI_ADDRESS_SPACE_TYPE_BUS)) {
      AddressDescriptor++;
    }

    mBusEntry[mCurrentBusEntry].BusId       = (UINT8)AddressDescriptor->AddrRangeMin;
    //
    // host bus has no parent
    //
    mBusEntry[mCurrentBusEntry].ParentBusId = 0xFF;
    mBusEntry[mCurrentBusEntry].BusType     = mBridgeBusTypes[0];
    //
    // for host we save ISA/VGA support values
    //
    mBusEntry[mCurrentBusEntry].Attributes  = (UINT8)SupportedAttributes;

    mMaxBusId = (mMaxBusId > mBusEntry[mCurrentBusEntry].BusId) ? mMaxBusId : mBusEntry[mCurrentBusEntry].BusId;

    MpsExTableAddSysAddressMapEntry (
      PciRootBridgeIoProtocol,
      mBusEntry[mCurrentBusEntry].BusId,
      mBusEntry[mCurrentBusEntry].Attributes
      );
    mCurrentBusEntry++;
  }
  gBS->FreePool (HandleBuffer);

  //
  // Second detect all other buses via PCI bridges
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    return;
  }

  for (Index = 0; Index < NumberOfHandles; Index++) {
    if (mCurrentBusEntry >= MP_TABLE_MAX_BUS_ENTRIES) {
      break;
    }

    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIoProtocol
                    );

    //
    // read class code information at 0x8 offset in PCI header
    //
    Status = PciIoProtocol->Pci.Read (
                              PciIoProtocol,
                              EfiPciIoWidthUint32,
                              PCI_REVISION_ID_OFFSET,
                              1,
                              (VOID*)PciData
                              );

    //
    // if IO APIC device collect info, we will need it later
    //
    if ((PciData[3] == PCI_CLASS_SYSTEM_PERIPHERAL) && (PciData[2] == PCI_SUBCLASS_PIC) && (PciData[1] >= PCI_IF_APIC_CONTROLLER)) {
      CollectIoApicInfo (PciIoProtocol, 0);
      continue;
    }

    //
    // not bridge device
    //
    if (PciData[3] != PCI_CLASS_BRIDGE) {
      continue;
    }

    //
    // PCI host bridge we already know, so skip it
    // or unknown bridge - skip it also
    //
    if ((PciData[2] == PCI_CLASS_BRIDGE_HOST) || (PciData[2] > PCI_CLASS_BRIDGE_NUBUS)) {
      continue;
    }

    mBusEntry[mCurrentBusEntry].BusType = mBridgeBusTypes[(PciData[2])];

    //
    // PCI to PCI bridge
    //
    if (PciData[2] == PCI_CLASS_BRIDGE_P2P) {
      mBusEntry[mCurrentBusEntry].Flags = 0;
      if (PciData[1] == PCI_IF_BRIDGE_P2P_SUBTRACTIVE) {
        mBusEntry[mCurrentBusEntry].Flags = PCI_IF_BRIDGE_P2P_SUBTRACTIVE;
      }
      //
      // read primary and secondary bus numbers
      //
      Status = PciIoProtocol->Pci.Read (
                                PciIoProtocol,
                                EfiPciIoWidthUint32,
                                PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
                                1,
                                (VOID*)PciData
                                );

      //
      // bus Id prodused by this bridge
      //
      mBusEntry[mCurrentBusEntry].BusId = PciData[1];
      mBusEntry[mCurrentBusEntry].ParentBusId = PciData[0];
      mMaxBusId = (mMaxBusId > mBusEntry[mCurrentBusEntry].BusId) ? mMaxBusId : mBusEntry[mCurrentBusEntry].BusId;
    } else {
      //
      // any other bridge
      //

      //
      // all other buses has this feature
      //
      mBusEntry[mCurrentBusEntry].Flags = PCI_IF_BRIDGE_P2P_SUBTRACTIVE;
      //
      // we will assign Id after enumerating PCI buses
      //
      mBusEntry[mCurrentBusEntry].BusId = 0xFF;
      //
      // get bridge location to determine parent bus Id
      //
      Status = PciIoProtocol->GetLocation (
                                PciIoProtocol,
                                &Dummy[0],
                                &BusNumber,
                                &Dummy[1],
                                &Dummy[2]
                                );
      mBusEntry[mCurrentBusEntry].ParentBusId = (UINT8)BusNumber;
    }
    mCurrentBusEntry++;
  }
  gBS->FreePool (HandleBuffer);

  //
  // Third enumerate all other buses
  //
  for (Index = 0; Index < mCurrentBusEntry; Index++) {
    if (mBusEntry[Index].BusId == 0xFF) {
      mBusEntry[Index].BusId = mMaxBusId + 1;
      mMaxBusId++;
      if (mBusEntry[Index].BusType == ISA_BUS_INDEX) {
        //
        // save ISA bus Id for interrupt assign procedure
        //
        mIsaBusId = mMaxBusId;
      }
    }
  }

  MpsExTableAddBusHierarchyEntry();
  MpsExTableAddCompatBusAddressModifierEntry();
}

/**
  Adds Bus entries to MPS table

  @return Number of entries added
**/
UINT16
MpsTableAddBusEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_BUS *EntryPointer;
  UINT16                        EntryCount;
  UINT16                        Index;

  EntryCount = 0;
  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_BUS *)mMpsTableCurrentPointer;

  QueryBusInfo();

  for (Index = 0; Index < mCurrentBusEntry; Index++) {
    EntryPointer->EntryType = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_BUS;
    EntryPointer->Id = mBusEntry[Index].BusId;

    CopyMem ((VOID *)EntryPointer->TypeString, (VOID *)mBusTypeString[(mBusEntry[Index].BusType)], sizeof(EntryPointer->TypeString));

    EntryPointer++;
    EntryCount++;
  }
  return EntryCount;
}

/**
  Adds IO Apic entries to MPS table

  @return Number of entries added
**/
UINT16
MpsTableAddIoApicEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *EntryPointer;
  UINT16                           EntryCount;
  UINT64                           SearchAddress;
  UINT8                            Index;

  EntryCount = 0;
  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC *)mMpsTableCurrentPointer;

  //
  // first we detect IO APICS mapped into default address range
  //
  for (SearchAddress = IO_APIC_BASE_ADDRESS_BOTTOM;
       SearchAddress < IO_APIC_BASE_ADDRESS_TOP;
       SearchAddress += IO_APIC_SEARCH_STEP) {
    if (MmioRead8 ((UINTN)SearchAddress) != 0xFF) {
      CollectIoApicInfo (NULL, (UINT32)SearchAddress);
    }
  }

  //
  // second we arrange IO APIC in their ID ascending order (if there more than one)
  //
  if (mCurrentIoApicEntry > 1) {
    ArrangeIoApicEntries();
  }

  //
  // now we are ready to create MPS table IO APIC entries
  //
  for (Index = 0; Index < mCurrentIoApicEntry; Index++) {
    ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC));
    EntryPointer->EntryType     = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IOAPIC;
    EntryPointer->Id            = mIoApicEntry[Index].IoApicId;
    EntryPointer->Ver           = mIoApicEntry[Index].IoApicVersion;
    CopyMem (&EntryPointer->Flags, &mIoApicEntry[Index].IoApicFlags, sizeof(EntryPointer->Flags));
    EntryPointer->Address       = mIoApicEntry[Index].IoApicAddress;

    EntryPointer++;
    EntryCount++;
  }

  return EntryCount;
}

/**
  Get RSDP ACPI table by Guid.

  @return RSDP pointer.
**/
VOID *
GetRsdpByGuid (
  IN EFI_GUID  *AcpiTableGuid
  )
{
  UINTN   Index;

  for (Index = 0; Index < gST->NumberOfTableEntries; Index++) {
    if (CompareGuid (&(gST->ConfigurationTable[Index].VendorGuid), AcpiTableGuid)) {
      return gST->ConfigurationTable[Index].VendorTable;
    }
  }

  return NULL;
}

/**
  Get RSDP ACPI table.

  @return RSDP pointer.
**/
VOID *
GetRsdp (
  VOID
  )
{
  VOID    *Rsdp;

  Rsdp = GetRsdpByGuid (&gEfiAcpi20TableGuid);
  if (Rsdp != NULL) {
    return Rsdp;
  }
  return GetRsdpByGuid (&gEfiAcpi10TableGuid);
}

/**
  Get MADT ACPI table.

  @return MADT pointer.
**/
VOID *
GetMadt (
  VOID
  )
{
  EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                   *Rsdt;
  EFI_ACPI_DESCRIPTION_HEADER                   *Xsdt;
  UINTN                                         Index;
  UINTN                                         TableCount;
  EFI_ACPI_DESCRIPTION_HEADER                   *Table;
  UINT32                                        *EntryPtr;
  UINT64                                        *Entry64Ptr;
  UINT64                                        TempEntry;

  Rsdp = GetRsdp ();
  if (Rsdp == NULL) {
    return NULL;
  }

  Rsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->RsdtAddress;
  TableCount = (Rsdt->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER)) / sizeof(UINT32);
  EntryPtr = (UINT32 *)((UINTN)Rsdt + sizeof(EFI_ACPI_DESCRIPTION_HEADER));
  for (Index = 0; Index < TableCount; Index++, EntryPtr++) {
    Table = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)*EntryPtr;
    if (Table->Signature == EFI_ACPI_1_0_APIC_SIGNATURE) {
      return Table;
    }
  }

  Xsdt = NULL;
  if (Rsdp->Revision >= 2) {
    Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->XsdtAddress;
  }
  if (Xsdt == NULL) {
    return NULL;
  }
  TableCount = (Xsdt->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER)) / sizeof(UINT64);
  Entry64Ptr = (UINT64 *)((UINTN)Xsdt + sizeof(EFI_ACPI_DESCRIPTION_HEADER));
  for (Index = 0; Index < TableCount; Index++, Entry64Ptr++) {
    CopyMem(&TempEntry, Entry64Ptr, sizeof(UINT64));
    Table = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)TempEntry;
    if (Table->Signature == EFI_ACPI_1_0_APIC_SIGNATURE) {
      return Table;
    }
  }
  return NULL;
}

/**
  Fill info in Iso Entry.
**/
VOID
FillIsoEntry (
  VOID
  )
{
  EFI_ACPI_1_0_MULTIPLE_APIC_DESCRIPTION_TABLE_HEADER  *Madt;
  EFI_ACPI_1_0_INTERRUPT_SOURCE_OVERRIDE_STRUCTURE     *MadtIso;

  Madt = GetMadt ();
  if (Madt == NULL) {
    return ;
  }

  MadtIso = (EFI_ACPI_1_0_INTERRUPT_SOURCE_OVERRIDE_STRUCTURE *)(Madt + 1);
  while ((UINTN)MadtIso < (UINTN)Madt + Madt->Header.Length) {
    if ((MadtIso->Type == EFI_ACPI_1_0_INTERRUPT_SOURCE_OVERRIDE) && (MadtIso->Bus == 0) && (MadtIso->Source < sizeof(mIsoTbl)/sizeof(mIsoTbl[0]))) {
      mIsoTbl[MadtIso->Source].PicIrq   = 0;
      mIsoTbl[MadtIso->Source].Trigger  = (UINT8)((MadtIso->Flags >> 2) & 0x3);
      mIsoTbl[MadtIso->Source].Polarity = (UINT8)(MadtIso->Flags & 0x3);
      mIsoTbl[MadtIso->Source].ApicInt  = (UINT16)MadtIso->GlobalSystemInterruptVector;
    }

    MadtIso = (EFI_ACPI_1_0_INTERRUPT_SOURCE_OVERRIDE_STRUCTURE *)((UINTN)MadtIso + MadtIso->Length);
  }
}

/**
  Adds Interrupt assignment entries to MPS table

  @return Number of entries added
**/
UINT16
MpsTableAddIntAssignEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *EntryPointer;
  UINT16                           EntryCount;
  UINT16                           IrqMask;
  PCI_IRQ_APIC_ROUTE               *RouteTable;
  UINTN                            IrqTableEntry;
  UINTN                            Index;
  UINTN                            SubIndex;

  EntryCount = 0;
  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_IO_INT *)mMpsTableCurrentPointer;

  //
  // Patch IsoEntry from MADT
  //
  FillIsoEntry ();

  //
  // First assign ISA IRQ interrupts
  //
  IrqMask = ISA_IRQ_MASK;
  for (Index = 0; Index < 16; Index++) {
    //
    // create entry only if IRQ is used
    // and it isn't IRQ2
    //
    if ((IrqMask & 1) && (Index != 2)) {
      ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
      EntryPointer->EntryType              = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT;
      EntryPointer->IntType                = EfiLegacyMpTableEntryIoIntTypeInt;
      EntryPointer->Flags.Polarity         = mIsoTbl[Index].Polarity;
      EntryPointer->Flags.Trigger          = mIsoTbl[Index].Trigger;
      EntryPointer->SourceBusId            = mIsaBusId;
      EntryPointer->SourceBusIrq.byte      = (UINT8)Index;
      //
      // define Apic ID and Itin depends of GLobal sys vector
      //
      GetIoApicId (
        mIsoTbl[Index].ApicInt,
        &EntryPointer->DestApicId,
        &EntryPointer->DestApicIntIn
        );

      EntryPointer++;
      EntryCount++;
    }
    IrqMask >>= 1;
  }

  //
  // Second assign PCI IRQ Entries
  //
  IrqTableEntry = gIrqBoardInfoProtocol->ApicRoutLength / sizeof(PCI_IRQ_APIC_ROUTE);
  RouteTable = gIrqBoardInfoProtocol->ApicRoutTable;

  for (Index = 0; Index < IrqTableEntry; Index++) {
    for (SubIndex = 0; SubIndex < 4; SubIndex++) {
      if (RouteTable[Index].IntIn[SubIndex].IoApicIntIn != 0) {
        ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT));
        EntryPointer->EntryType     = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_IO_INT;
        EntryPointer->IntType       = EfiLegacyMpTableEntryIoIntTypeInt;
        //
        // always conforms PCI bus specs
        //
        EntryPointer->Flags.Polarity = EfiLegacyMpTableEntryIoIntFlagsPolarityActiveLow;
        EntryPointer->Flags.Trigger  = EfiLegacyMpTableEntryIoIntFlagsTriggerLevel;
        EntryPointer->SourceBusId               = RouteTable[Index].PciBusNumber;
        EntryPointer->SourceBusIrq.fields.IntNo = (UINT8)SubIndex;
        EntryPointer->SourceBusIrq.fields.Dev   = RouteTable[Index].DeviceNumber;
        //
        //define Apic ID and Itin depends of GLobal sys vector
        //
        GetIoApicId (
          RouteTable[Index].IntIn[SubIndex].IoApicIntIn,
          &EntryPointer->DestApicId,
          &EntryPointer->DestApicIntIn
          );

        EntryPointer++;
        EntryCount++;
      }
    }
  }

  return EntryCount;
}

/**
  Adds Local interrupt assignment entries to MPS table

  @return Number of entries added
**/
UINT16
MpsTableAddLocalIntAssignEntry (
  VOID
  )
{
  EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *EntryPointer;
  UINT16                              EntryCount;

  EntryCount = 0;
  EntryPointer = (EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT *)mMpsTableCurrentPointer;

  ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
  EntryPointer->EntryType                   = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT;
  EntryPointer->IntType                     = EfiLegacyMpTableEntryLocalIntTypeInt;
  EntryPointer->Flags.Polarity              = EfiLegacyMpTableEntryLocalIntFlagsPolaritySpec;
  EntryPointer->Flags.Trigger               = EfiLegacyMpTableEntryLocalIntFlagsTriggerSpec;
  EntryPointer->DestApicId                  = 0xFF;
  EntryPointer->DestApicIntIn               = 0;

  EntryPointer++;
  EntryCount++;

  ZeroMem (EntryPointer, sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT));
  EntryPointer->EntryType                   = EFI_LEGACY_MP_TABLE_ENTRY_TYPE_LOCAL_INT;
  EntryPointer->IntType                     = EfiLegacyMpTableEntryLocalIntTypeNmi;
  EntryPointer->Flags.Polarity              = EfiLegacyMpTableEntryLocalIntFlagsPolaritySpec;
  EntryPointer->Flags.Trigger               = EfiLegacyMpTableEntryLocalIntFlagsTriggerSpec;
  EntryPointer->DestApicId                  = 0xFF;
  EntryPointer->DestApicIntIn               = 1;

  EntryPointer++;
  EntryCount++;

  return EntryCount;
}

/**
  Adds Extended table entries to base table
**/
VOID
MpsTableAddExtendedTable (
  VOID
  )
{
  CopyMem (mMpsTableCurrentPointer, mMpsExTablePointer, mExtendedTableLength);
  mMpsExTablePointer = mMpsTableCurrentPointer;
  return;
}

/**
  Fill OemId and ProductId in MP table.

  @param HeaderPointer MP table header pointer.
**/
VOID
GetOemProductId (
  IN EFI_LEGACY_MP_TABLE_HEADER    *HeaderPointer
  )
{
  EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                   *Rsdt;

  Rsdp = GetRsdp ();
  if (Rsdp == NULL) {
    return ;
  }

  Rsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->RsdtAddress;
  CopyMem (HeaderPointer->OemId, Rsdt->OemId, sizeof(Rsdt->OemId));
  CopyMem (HeaderPointer->OemProductId, &Rsdt->OemTableId, sizeof(Rsdt->OemTableId));
}

/**
  Creates MPS table header, allocates space and copies entire
  table into Reserved memory

  @return EFI_STATUS
**/
EFI_STATUS
MpsTableAddHeader (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_LEGACY_MP_TABLE_HEADER    *HeaderPointer;
  EFI_PHYSICAL_ADDRESS          AllocationPointerAddress;

  HeaderPointer = (EFI_LEGACY_MP_TABLE_HEADER *) mMpsTablePointer;
  ZeroMem (mMpsTablePointer, sizeof(EFI_LEGACY_MP_TABLE_HEADER));

  HeaderPointer->Signature            = EFI_LEGACY_MP_TABLE_HEADER_SIGNATURE;
  HeaderPointer->BaseTableLength      = mBaseTableLength;
  HeaderPointer->SpecRev              = EFI_LEGACY_MP_TABLE_REV_1_4;

  //
  // Get Oem ID and Product ID from ACPI table
  //
  GetOemProductId (HeaderPointer);

  HeaderPointer->OemTablePointer      = 0;
  HeaderPointer->OemTableSize         = 0;
  HeaderPointer->EntryCount           = mBaseTableEntryCount;
  HeaderPointer->LocalApicAddress     = (UINT32)(AsmReadMsr64 (MSR_IA32_APIC_BASE) & 0xffffff000);
  HeaderPointer->ExtendedTableLength  = mExtendedTableLength;

  HeaderPointer->ExtendedChecksum     = CalculateCheckSum8(mMpsExTablePointer, mExtendedTableLength);
  HeaderPointer->Checksum             = CalculateCheckSum8(mMpsTablePointer, mBaseTableLength);

  AllocationPointerAddress = 0xFFFFFFFF;
  Status = gBS->AllocatePages(
                  AllocateMaxAddress,
                  EfiReservedMemoryType,
                  EFI_SIZE_TO_PAGES(mBaseTableLength + mExtendedTableLength),
                  &AllocationPointerAddress
                  );
  ASSERT_EFI_ERROR(Status);
  ZeroMem ((VOID *)(UINTN)AllocationPointerAddress, mBaseTableLength + mExtendedTableLength);

  //
  // memory allocated - copy MPS table to new location
  //
  CopyMem (
    (VOID *)(UINTN)AllocationPointerAddress,
    mMpsTablePointer,
    (UINTN) (mBaseTableLength + mExtendedTableLength)
    );
  FreePool (mMpsTablePointer);
  mMpsTablePointer = (VOID *)(UINTN)AllocationPointerAddress;
  DEBUG ((DEBUG_INFO, "mMpsTablePointer (Reserved) - %x\n", mMpsTablePointer));

  return EFI_SUCCESS;
}

/**
  Allocates space and creates MPS table

  @return EFI_STATUS
**/
EFI_STATUS
MpsTableCreate (
  VOID
  )
{
  EFI_STATUS               Status;
  UINT16                   EntryCount;
  if(PcdGetBool(PcdTbtSupport)) {
    mMpsTablePointer = AllocateZeroPool (MP_TABLE_MAX_LEN*8); // Allocate Enough Space for Tbt
    mMpsExTablePointer = (VOID *)((UINTN)mMpsTableCurrentPointer + (MP_EX_TABLE_MAX_LEN*8));
  } else {
    mMpsTablePointer = AllocateZeroPool (MP_TABLE_MAX_LEN);
    mMpsExTablePointer = (VOID *)((UINTN)mMpsTableCurrentPointer + (MP_EX_TABLE_MAX_LEN));
  }
  mMpsTableCurrentPointer = mMpsTablePointer;

  //
  // split buffer onto two parts for base and extended tables
  //
  mMpsExTableCurrentPointer = mMpsExTablePointer;

  //
  // Leave placeholder for header
  //
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_HEADER));
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_HEADER);

  //
  // add CPU Entry
  //
  EntryCount = MpsTableAddCpuEntry();
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR) * EntryCount);
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_PROCESSOR) * EntryCount;
  mBaseTableEntryCount = mBaseTableEntryCount + EntryCount;

  //
  // add Bus Entry
  //
  EntryCount = MpsTableAddBusEntry();
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS) * EntryCount);
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_BUS) * EntryCount;
  mBaseTableEntryCount = mBaseTableEntryCount + EntryCount;

  //
  // add IO Apic Entry
  //
  EntryCount = MpsTableAddIoApicEntry();
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC) * EntryCount);
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IOAPIC) * EntryCount;
  mBaseTableEntryCount = mBaseTableEntryCount + EntryCount;

  //
  // add Interrupt assignment Entry
  //
  EntryCount = MpsTableAddIntAssignEntry();
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT) * EntryCount);
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_IO_INT) * EntryCount;
  mBaseTableEntryCount = mBaseTableEntryCount + EntryCount;

  //
  // add Local interrupt assignment Entry
  //
  EntryCount = MpsTableAddLocalIntAssignEntry();
  mMpsTableCurrentPointer = (VOID *)((UINTN)mMpsTableCurrentPointer + sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT) * EntryCount);
  mBaseTableLength += sizeof(EFI_LEGACY_MP_TABLE_ENTRY_LOCAL_INT) * EntryCount;
  mBaseTableEntryCount = mBaseTableEntryCount + EntryCount;

  MpsTableAddExtendedTable();

  Status = MpsTableAddHeader();

  return Status;
}

/**
  Fills MP_FLOATING_POINTER structure with actual data
  and places it to Reserved memory.
  It will be copy to E/F segment later.

  @return MpTable pointer
--*/
VOID *
MpsTableFloatPointerModify (
  VOID
  )
{
  EFI_STATUS           Status;
  EFI_PHYSICAL_ADDRESS MpsTableAddress;
  VOID                 *MpsTable;

  ZeroMem (&mMpsTableFloatingPointer, sizeof(EFI_LEGACY_MP_TABLE_FLOATING_POINTER));
  mMpsTableFloatingPointer.Signature             = EFI_LEGACY_MP_TABLE_FLOATING_POINTER_SIGNATURE;
  mMpsTableFloatingPointer.PhysicalAddress       = (UINT32)(UINTN) mMpsTablePointer;
  mMpsTableFloatingPointer.Length                = sizeof(EFI_LEGACY_MP_TABLE_FLOATING_POINTER)/0x10;
  mMpsTableFloatingPointer.SpecRev               = EFI_LEGACY_MP_TABLE_REV_1_4;

  //
  // now we are ready to calculate checksum
  //
  mMpsTableFloatingPointer.Checksum = CalculateCheckSum8((UINT8 *)&mMpsTableFloatingPointer, sizeof(EFI_LEGACY_MP_TABLE_FLOATING_POINTER));

  MpsTableAddress = 0xFFFFFFFF;
  Status = gBS->AllocatePages(
                  AllocateMaxAddress,
                  EfiReservedMemoryType,
                  EFI_SIZE_TO_PAGES(sizeof(mMpsTableFloatingPointer)),
                  &MpsTableAddress
                  );
  ASSERT_EFI_ERROR(Status);

  MpsTable = (VOID *)(UINTN)MpsTableAddress;
  CopyMem (MpsTable, &mMpsTableFloatingPointer, sizeof(mMpsTableFloatingPointer));
  DEBUG ((DEBUG_INFO, "mMpsTableFloatingPointer (Reserved) - %x\n", MpsTable));

  Status = gBS->InstallConfigurationTable (&gEfiMpsTableGuid, MpsTable);
  ASSERT_EFI_ERROR(Status);

  return MpsTable;
}

/**
  MPS table builder entry point

  @return MpTable pointer
**/
VOID *
MpsTableBuilderInit (
  VOID
  )
{
  EFI_STATUS Status;
  VOID       *MpTable;

  Status = MpsTableCreate();
  if (EFI_ERROR(Status)) {
    return NULL;
  }

  MpTable = MpsTableFloatPointerModify();
  if (MpTable == NULL) {
    return NULL;
  }

  DumpMpsTable (MpTable);

  return MpTable;
}
