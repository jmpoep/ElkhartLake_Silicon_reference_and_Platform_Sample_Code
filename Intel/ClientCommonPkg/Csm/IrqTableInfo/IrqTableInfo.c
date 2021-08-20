/** @file
This Driver does Board Info related Initialization.

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
#include <Library/PciLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Protocol/LegacyBiosPlatform.h>
#include <Protocol/IrqBoardInfo.h>
#include <Protocol/IrqTableInfo.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <IndustryStandard/Pci.h>

EFI_STATUS
EFIAPI
IrqTableInitialize (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  IN BOOLEAN                  PciAutoDetect
  );

EFI_STATUS
EFIAPI
IrqTableGetMpTable (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **MpTable
  );

EFI_STATUS
EFIAPI
IrqTableGetPirqTable (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **PirqTable
  );

VOID *
MpsTableBuilderInit (
  VOID
  );

VOID *
PirqTableBuilderInit (
  VOID
  );

IRQ_TABLE_INFO_PROTOCOL mIrqTableProtocol = {
  IrqTableInitialize,
  IrqTableGetMpTable,
  IrqTableGetPirqTable
  };

EFI_HANDLE  mIrqTableInfoHandle = NULL;

VOID        *mMpTable   = NULL;
VOID        *mPirqTable = NULL;

IRQ_BOARD_INFO_PROTOCOL *gIrqBoardInfoProtocol = NULL;

UINT8 mRuntimeBus[0x100];

UINT8 mPirqRoutingReg[] = {0x60, 0x61, 0x62, 0x63, 0x68, 0x69, 0x6A, 0x6B};
UINT8 mApicIntIn[] = {16, 17, 18, 19, 20, 21, 22, 23};

/**
  Get max bus number from translation table.

  @param BusXlatTable  Bus translation table
  @param BusXlatLength Bus translation table length

  @return max bus number in this translation table
**/
UINT8
GetMaxBusFromXlatTable (
  IN PCI_BUS_XLAT_HDR        *BusXlatTable,
  IN UINTN                   BusXlatLength
  )
{
  PCI_BUS_XLAT_HDR                *BusXlatEntry;
  UINT8                           *Bridge;
  UINT8                           MaxBus;

  BusXlatEntry = BusXlatTable;
  do {
    MaxBus = BusXlatEntry->BusBuild;
    //
    // Find next one
    //
    for (Bridge = (UINT8 *)(BusXlatEntry + 1); *Bridge != 0xFF; Bridge++) {
      ;
    }
    BusXlatEntry = (PCI_BUS_XLAT_HDR *)(Bridge + 1);
  } while ((UINTN)BusXlatEntry < (UINTN)BusXlatTable + BusXlatLength);

  return MaxBus;
}

/**
  Get runtime bus number from translation table.

  @param BusXlatTable  Bus translation table
  @param BusXlatLength Bus translation table length
  @param BusBuild      Build time bus number

  @return runtime bus number in this translation table
**/
UINT8
GetBusFromXlatTable (
  IN PCI_BUS_XLAT_HDR        *BusXlatTable,
  IN UINTN                   BusXlatLength,
  IN UINT8                   BusBuild
  )
{
  UINT8                           HeaderType;
  UINT8                           Bus;
  UINT8                           Device;
  UINT8                           Function;
  PCI_BUS_XLAT_HDR                *BusXlatEntry;
  UINT8                           *Bridge;

  BusXlatEntry = BusXlatTable;
  do {
    if (BusXlatEntry->BusBuild == BusBuild) {
      //
      // Find it
      //
      Bridge = (UINT8 *)(BusXlatEntry + 1);
      Bus = *Bridge;
      Bridge ++;
      do {
        Device = (UINT8)((*Bridge >> 3) & 0x1F);
        Function = (UINT8)(*Bridge & 0x7);
        Bridge ++;

        HeaderType = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_HEADER_TYPE_OFFSET));
        if ((HeaderType & HEADER_LAYOUT_CODE) != HEADER_TYPE_PCI_TO_PCI_BRIDGE) {
          BusXlatEntry->BusRun = 0xFF;
          return 0xFF;
        }

        Bus = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET));
        if (Bus == 0) {
          BusXlatEntry->BusRun = 0xFF;
          return 0xFF;
        }
      } while (*Bridge != 0xFF);

      BusXlatEntry->BusRun = Bus;
      return Bus;
    }

    //
    // Find next one
    //
    for (Bridge = (UINT8 *)(BusXlatEntry + 1); *Bridge != 0xFF; Bridge++) {
      ;
    }
    BusXlatEntry = (PCI_BUS_XLAT_HDR *)(Bridge + 1);
  } while ((UINTN)BusXlatEntry < (UINTN)BusXlatTable + BusXlatLength);

  //
  // Not found???
  //
  DEBUG ((DEBUG_ERROR, "BuildBus (%x) not found!\n", (UINTN)BusBuild));
  ASSERT (FALSE);
  return 0xFF;
}

/**
  Return auto assigned IRQ fro this PCI device.
  The algo is to sum all Dev/Func number in the device path, then mod 4.

  @param Handle     PCI device handle

  @return auto assigned IRQ index
**/
UINT8
GetAutoIrqIndex (
  IN EFI_HANDLE          Handle
  )
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     IrqIndex;

  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiDevicePathProtocolGuid,
                  (VOID**)&DevicePath
                  );
  ASSERT_EFI_ERROR (Status);

  IrqIndex = 0;
  while (!IsDevicePathEnd (DevicePath)) {
    if ((DevicePathType (DevicePath) == HARDWARE_DEVICE_PATH) &&
        (DevicePathSubType (DevicePath) == HW_PCI_DP)) {
      IrqIndex += ((PCI_DEVICE_PATH *)DevicePath)->Device + ((PCI_DEVICE_PATH *)DevicePath)->Function;
    }
    DevicePath = NextDevicePathNode (DevicePath);
  }

  return (UINT8)(IrqIndex % 4);
}

/**
  Find PCI device in PIC Irq table.

  @param PicEntry   PIC Irq table
  @param EntryCount the entry count of PIC Irq table
  @param Bus        PCI bus number
  @param Device     PCI device number

  @retval TRUE  the PCI device is found in PIC Irq table
  @retval FALSE the PCI device is not found in PIC Irq table
**/
BOOLEAN
FindDeviceInPicIrqTable (
  IN PCI_IRQ_PIC_ROUTE   *PicEntry,
  IN UINTN               EntryCount,
  IN UINT8               Bus,
  IN UINT8               Device
  )
{
  UINTN   Index;

  for (Index = 0; Index < EntryCount; Index++) {
    if ((PicEntry[Index].PciBusNumber == Bus) &&
        ((PicEntry[Index].DeviceNumber >> 3) == Device)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Update PIC table.
  1) Update bus number
  2) Remove nonexistent device
  3) Add new device

  @param PciAutoDetect Pci Auto Detect
**/
VOID
UpdatePicTable (
  IN BOOLEAN                  PciAutoDetect
  )
{
  PCI_IRQ_PIC_ROUTE   *PicEntry;
  UINTN               Index;
  UINTN               EntryCount;
  UINT16              VendorId;
  UINT8               NewPciBusNumber;
  PCI_IRQ_PIC_ROUTE   *NewPicEntry;
  UINTN               NewIndex;
  EFI_PCI_IO_PROTOCOL *PciIoProtocol;
  EFI_HANDLE          *HandleBuffer;
  UINTN               NumberOfHandles;
  EFI_STATUS          Status;
  UINTN               SubIndex;
  UINTN               Seg;
  UINTN               Bus;
  UINTN               Dev;
  UINTN               Func;
  UINTN               IrqIndex;

  //
  // 0. Collect information
  //
  EntryCount = gIrqBoardInfoProtocol->PicRoutLength / sizeof(*PicEntry);

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    NumberOfHandles = 0;
    HandleBuffer = NULL;
  }

  NewPicEntry  = AllocateZeroPool (gIrqBoardInfoProtocol->PicRoutLength + NumberOfHandles * sizeof(*PicEntry));
  ASSERT (NewPicEntry != NULL);
  if (NewPicEntry == NULL) {
    return;
  }

  NewIndex = 0;

  //
  // 1. Remove non-existent PCI
  //
  PicEntry = gIrqBoardInfoProtocol->PicRoutTable;
  for (Index = 0; Index < EntryCount; Index++) {
    NewPciBusNumber = mRuntimeBus[PicEntry[Index].PciBusNumber];
    DEBUG ((DEBUG_INFO, "PicIrq(%d) - %x -> %x.", Index, (UINTN)PicEntry[Index].PciBusNumber, (UINTN)NewPciBusNumber));

    if (NewPciBusNumber == 0xFF) {
      DEBUG ((DEBUG_INFO, "%x not updated\n", (UINTN)PicEntry[Index].DeviceNumber >> 3));
      continue;
    }

    VendorId = PciRead16 (PCI_LIB_ADDRESS (NewPciBusNumber, PicEntry[Index].DeviceNumber >> 3, 0x0, PCI_VENDOR_ID_OFFSET));
    if (VendorId == 0xffff) {
      DEBUG ((DEBUG_INFO, "%x not found\n", (UINTN)PicEntry[Index].DeviceNumber >> 3));
      continue;
    }

    DEBUG ((DEBUG_INFO, "%x exist\n", (UINTN)PicEntry[Index].DeviceNumber >> 3));

    //
    // Save it
    //
    CopyMem (&NewPicEntry[NewIndex], &PicEntry[Index], sizeof(*PicEntry));
    NewPicEntry[NewIndex].PciBusNumber = NewPciBusNumber;
    NewIndex++;
  }

  //
  // 2. Add new PCI device
  //
  if (PciAutoDetect) {
    for (Index = 0; Index < NumberOfHandles; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID**)&PciIoProtocol
                      );
      ASSERT_EFI_ERROR (Status);

      Status = PciIoProtocol->GetLocation (PciIoProtocol, &Seg, &Bus, &Dev, &Func);
      ASSERT_EFI_ERROR (Status);

      if (FindDeviceInPicIrqTable (NewPicEntry, NewIndex, (UINT8)Bus, (UINT8)Dev)) {
        continue;
      }

      DEBUG ((DEBUG_INFO, "PicIrq - PCI (%02x.%02x.%02x) is NOT found in PIC IRQ table\n", (UINTN)Bus, (UINTN)Dev, (UINTN)Func));

      //
      // Skip bus 0, we assume bus 0 should be always assigned be developer.
      //
      if (Bus == 0) {
        continue;
      }

      //
      // New device
      //
      NewPicEntry[NewIndex].PciBusNumber = (UINT8)Bus;
      NewPicEntry[NewIndex].DeviceNumber = (UINT8)(Dev << 3);
      IrqIndex = GetAutoIrqIndex(HandleBuffer[Index]);
      for (SubIndex = 0; SubIndex < 4; SubIndex++) {
        NewPicEntry[NewIndex].PciIrq[SubIndex].ChipsetReg = mPirqRoutingReg[(IrqIndex + SubIndex) % 4];
        NewPicEntry[NewIndex].PciIrq[SubIndex].IrqMask    = gIrqBoardInfoProtocol->PciDedicatedIrqs;
      }
      NewPicEntry[NewIndex].SlotNum = (UINT8)Bus;
      NewIndex++;
    }
  }

  //
  // 3. Done
  //
  gIrqBoardInfoProtocol->PicRoutTable  = NewPicEntry;
  gIrqBoardInfoProtocol->PicRoutLength = NewIndex * sizeof(*PicEntry);
}

/**
  Find PCI device in APIC Irq table.

  @param ApicEntry  APIC Irq table
  @param EntryCount the entry count of APIC Irq table
  @param Bus        PCI bus number
  @param Device     PCI device number

  @retval TRUE  the PCI device is found in APIC Irq table
  @retval FALSE the PCI device is not found in APIC Irq table
**/
BOOLEAN
FindDeviceInApicIrqTable (
  IN PCI_IRQ_APIC_ROUTE  *ApicEntry,
  IN UINTN               EntryCount,
  IN UINT8               Bus,
  IN UINT8               Device
  )
{
  UINTN   Index;

  for (Index = 0; Index < EntryCount; Index++) {
    if ((ApicEntry[Index].PciBusNumber == Bus) &&
        (ApicEntry[Index].DeviceNumber == Device)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Update PIC table.
  1) Update bus number
  2) Remove nonexistent device
  3) Add new device

  @param PciAutoDetect Pci Auto Detect
**/
VOID
UpdateApicTable (
  IN BOOLEAN                  PciAutoDetect
  )
{
  PCI_IRQ_APIC_ROUTE  *ApicEntry;
  UINTN               Index;
  UINTN               EntryCount;
  UINT16              VendorId;
  UINT8               NewPciBusNumber;
  PCI_IRQ_APIC_ROUTE  *NewApicEntry;
  UINTN               NewIndex;
  EFI_PCI_IO_PROTOCOL *PciIoProtocol;
  EFI_HANDLE          *HandleBuffer;
  UINTN               NumberOfHandles;
  EFI_STATUS          Status;
  UINTN               SubIndex;
  UINTN               Seg;
  UINTN               Bus;
  UINTN               Dev;
  UINTN               Func;
  UINTN               IrqIndex;

  //
  // 0. Collect information
  //
  EntryCount = gIrqBoardInfoProtocol->ApicRoutLength / sizeof(*ApicEntry);

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    NumberOfHandles = 0;
    HandleBuffer = NULL;
  }

  NewApicEntry  = AllocateZeroPool (gIrqBoardInfoProtocol->ApicRoutLength + NumberOfHandles * sizeof(*ApicEntry));
  ASSERT (NewApicEntry != NULL);
  if (NewApicEntry == NULL) {
    return;
  }

  NewIndex = 0;

  //
  // 1. Remove non-existent PCI
  //
  ApicEntry = gIrqBoardInfoProtocol->ApicRoutTable;
  for (Index = 0; Index < EntryCount; Index++) {
    NewPciBusNumber = mRuntimeBus[ApicEntry[Index].PciBusNumber];
    DEBUG ((DEBUG_INFO, "ApicIrq(%d) - %x -> %x.", Index, (UINTN)ApicEntry[Index].PciBusNumber, (UINTN)NewPciBusNumber));

    if (NewPciBusNumber == 0xFF) {
      DEBUG ((DEBUG_INFO, "%x not updated\n", (UINTN)ApicEntry[Index].DeviceNumber));
      continue;
    }

    VendorId = PciRead16 (PCI_LIB_ADDRESS (NewPciBusNumber, ApicEntry[Index].DeviceNumber, 0x0, PCI_VENDOR_ID_OFFSET));
    if (VendorId == 0xffff) {
      DEBUG ((DEBUG_INFO, "%x not found\n", (UINTN)ApicEntry[Index].DeviceNumber));
      continue;
    }

    DEBUG ((DEBUG_INFO, "%x exist\n", (UINTN)ApicEntry[Index].DeviceNumber));

    //
    // Save it
    //
    CopyMem (&NewApicEntry[NewIndex], &ApicEntry[Index], sizeof(*ApicEntry));
    NewApicEntry[NewIndex].PciBusNumber = NewPciBusNumber;
    NewIndex++;
  }

  //
  // 2. Add new PCI device
  //
  if (PciAutoDetect) {
    for (Index = 0; Index < NumberOfHandles; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID**)&PciIoProtocol
                      );
      ASSERT_EFI_ERROR (Status);

      Status = PciIoProtocol->GetLocation (PciIoProtocol, &Seg, &Bus, &Dev, &Func);
      ASSERT_EFI_ERROR (Status);

      if (FindDeviceInApicIrqTable (NewApicEntry, NewIndex, (UINT8)Bus, (UINT8)Dev)) {
        continue;
      }

      DEBUG ((DEBUG_INFO, "ApicIrq - PCI (%02x.%02x.%02x) is NOT found in PIC IRQ table\n", (UINTN)Bus, (UINTN)Dev, (UINTN)Func));

      //
      // Skip bus 0, we assume bus 0 should be always assigned be developer.
      //
      if (Bus == 0) {
        continue;
      }

      //
      // New device
      //
      NewApicEntry[NewIndex].PciBusNumber = (UINT8)Bus;
      NewApicEntry[NewIndex].DeviceNumber = (UINT8)Dev;
      IrqIndex = GetAutoIrqIndex(HandleBuffer[Index]);
      for (SubIndex = 0; SubIndex < 4; SubIndex++) {
        NewApicEntry[NewIndex].IntIn[SubIndex].IoApicIntIn = mApicIntIn[(IrqIndex + SubIndex) % 4];
        NewApicEntry[NewIndex].IntIn[SubIndex].IoApicId    = gIrqBoardInfoProtocol->ApicInfoTable[0].ApicIdBuild;
      }
      NewIndex++;
    }
  }

  //
  // 3. Done
  //
  gIrqBoardInfoProtocol->ApicRoutTable  = NewApicEntry;
  gIrqBoardInfoProtocol->ApicRoutLength = NewIndex * sizeof(*ApicEntry);
}

/**
  Initialize legacy IRQ table - MP table, and PIRQ table environment.

  @param  This                 A pointer to the calling context.
  @param  PciAutoDetect        TRUE means BIOS will automatically detect all PCI
                                 devices in system and add IRQ entry to MP table
                                 and PIRQ table. If so, IRQ information of all
                                 PCI devices can be found in final table,
                                 including the one in slot.
                               FALSE means BIOS will just use the IRQ table
                                 created at build phase. If so, only on-board PCI
                                 devices will have IRQ information, because
                                 addin-card IRQ info is not assigned at build time.

  @retval EFI_SUCCESS          The function completed successfully
**/
EFI_STATUS
EFIAPI
IrqTableInitialize (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  IN BOOLEAN                  PciAutoDetect
  )
{
  STATIC BOOLEAN  Initialized = FALSE;
  UINTN           Index;
  UINT8           NewBus;
  UINT8           MaxBus;
  VOID            *Dummy;

  DEBUG ((DEBUG_INFO, "IrqTableInitialize (%x)\n", (UINTN)PciAutoDetect));

  if (Initialized) {
    return EFI_SUCCESS;
  }
  Initialized = TRUE;
  ASSERT (!gIrqBoardInfoProtocol->Updated);

  SetMem (mRuntimeBus, sizeof(mRuntimeBus), 0xFF);

  MaxBus = GetMaxBusFromXlatTable (gIrqBoardInfoProtocol->BusXlatTable, gIrqBoardInfoProtocol->BusXlatLength);
  DEBUG ((DEBUG_INFO, "MaxBus (In translation table) - %x\n", (UINTN)MaxBus));

  //
  // Reassign bus number
  //
  mRuntimeBus[0] = 0;
  for (Index = 1; Index <= MaxBus; Index++) {
    NewBus = GetBusFromXlatTable (
               gIrqBoardInfoProtocol->BusXlatTable,
               gIrqBoardInfoProtocol->BusXlatLength,
               (UINT8)Index
               );
    if ((NewBus != 0xFF) && (NewBus != 0x0)) {
      DEBUG ((DEBUG_INFO, "Bus %x -> %x\n", Index, (UINTN)NewBus));
      mRuntimeBus[Index] = NewBus;
    } else {
      DEBUG ((DEBUG_INFO, "Bus %x -> ??\n", Index));
    }
  }

  //
  // Update PCI and APIC table.
  //
  UpdatePicTable (PciAutoDetect);
  if (FeaturePcdGet (PcdMpTableSupport)) {
    UpdateApicTable (PciAutoDetect);
  }
  gIrqBoardInfoProtocol->Updated = TRUE;

  //
  // Create IRQ table one time.
  //
  IrqTableGetPirqTable (This, &Dummy);
  if (FeaturePcdGet (PcdMpTableSupport)) {
    IrqTableGetMpTable (This, &Dummy);
  }

  return EFI_SUCCESS;
}

/**
  Return MP table.

  @param  This                 A pointer to the calling context.
  @param  MpTable              Mp table header pointer.

  @retval EFI_SUCCESS          The function completed successfully
  @retval EFI_NOT_FOUND        Table not found
**/
EFI_STATUS
EFIAPI
IrqTableGetMpTable (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **MpTable
  )
{
  if (FeaturePcdGet (PcdMpTableSupport)) {
    DEBUG ((DEBUG_INFO, "IrqTableGetMpTable\n"));
    if (mMpTable != NULL) {
      *MpTable = mMpTable;
      return EFI_SUCCESS;
    }

    //
    // Create MpTable
    //
    mMpTable = MpsTableBuilderInit ();
    *MpTable = mMpTable;
    if (mMpTable == NULL) {
      return EFI_NOT_FOUND;
    }
    return EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, "IrqTableGetMpTable Unsupported!\n"));
    return EFI_UNSUPPORTED;
  }
}

/**
  Return PIRQ table.

  @param  This                 A pointer to the calling context.
  @param  PirqTable            Pirq table header pointer.

  @retval EFI_SUCCESS          The function completed successfully
  @retval EFI_NOT_FOUND        Table not found
**/
EFI_STATUS
EFIAPI
IrqTableGetPirqTable (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **PirqTable
  )
{
  DEBUG ((DEBUG_INFO, "IrqTableGetPirqTable\n"));
  if (mPirqTable != NULL) {
    *PirqTable = mPirqTable;
    return EFI_SUCCESS;
  }

  //
  // Create PirqTable
  //
  mPirqTable = PirqTableBuilderInit ();
  *PirqTable = mPirqTable;
  if (mPirqTable == NULL) {
    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  Irq Table Info Protocol Handle.

  @param ImageHandle - ImageHandle
  @param SystemTable - Efi SystemTable Pointer

  @return EFI_STATUS
**/
EFI_STATUS
EFIAPI
IrqTableEntryPoint(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gBS->LocateProtocol(&gIrqBoardInfoProtocolGuid, NULL,(VOID**)&gIrqBoardInfoProtocol);
  ASSERT_EFI_ERROR(Status);

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mIrqTableInfoHandle,
                  &gIrqTableInfoProtocolGuid,
                  &mIrqTableProtocol,
                  NULL
                  );

  return Status;
}
