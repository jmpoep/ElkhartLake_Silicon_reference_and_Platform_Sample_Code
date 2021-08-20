/** @file
  Pci Hotplug Helpers Driver : This file will perform specific PCI-EXPRESS
  Devics resource configuration.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include "PciHotPlugHelpers.h"

extern P2PB_RESOURCE_RECORD       mP2pbResourceRecord[MAX_P2PB_OF_TBT_DAISY_CHAIN];
extern NUMBER_OF_HOTPLUG_BRIDGE   mNumOfHotPlugBridge[MAX_P2PB_OF_TBT_DAISY_CHAIN];

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x10 = PCI Express Capability

  @param[in] Segment              Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT8
PcieFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  )
{
  UINT8   CapHeaderOffset;
  UINT8   CapHeaderId;
  UINT64  DeviceBase;

  DeviceBase = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, Device, Function, 0);

  if ((PciSegmentRead8 (DeviceBase + PCI_PRIMARY_STATUS_OFFSET) & EFI_PCI_STATUS_CAPABILITY) == 0x00) {
    ///
    /// Function has no capability pointer
    ///
    return 0;
  }

  ///
  /// Check the header layout to determine the Offset of Capabilities Pointer Register
  ///
  if ((PciSegmentRead8 (DeviceBase + PCI_HEADER_TYPE_OFFSET) & HEADER_LAYOUT_CODE) == (HEADER_TYPE_CARDBUS_BRIDGE)) {
    ///
    /// If CardBus bridge, start at Offset 0x14
    ///
    CapHeaderOffset = 0x14;
  } else {
    ///
    /// Otherwise, start at Offset 0x34
    ///
    CapHeaderOffset = 0x34;
  }
  ///
  /// Get Capability Header, A pointer value of 00h is used to indicate the last capability in the list.
  ///
  CapHeaderId     = 0;
  CapHeaderOffset = PciSegmentRead8 (DeviceBase + CapHeaderOffset) & ((UINT8) ~(BIT0 | BIT1));
  while (CapHeaderOffset != 0 && CapHeaderId != 0xFF) {
    CapHeaderId = PciSegmentRead8 (DeviceBase + CapHeaderOffset);
    if (CapHeaderId == CapId) {
      return CapHeaderOffset;
    }
    ///
    /// Each capability must be DWORD aligned.
    /// The bottom two bits of all pointers (including the initial pointer at 34h) are reserved
    /// and must be implemented as 00b although software must mask them to allow for future uses of these bits.
    ///
    CapHeaderOffset = PciSegmentRead8 (DeviceBase + CapHeaderOffset + 1) & ((UINT8) ~(BIT0 | BIT1));
  }

  return 0;
}

/**
  Get the Parent Pci Address

  @param[in] Segment              Segment Number
  @param[in] CurrentRpBus         P2P Bridge Bus Number

  @retval ParentP2PBridgeBase     Parent Pci Address
**/
UINT64
GetParentPciAddress (
  IN  UINT8  Segment,
  IN  UINT64 CurrentRpBus
  )
{
  UINT8   ParentRpBus;
  UINT8   ParentRpDev;
  UINT8   ParentRpFunc;
  UINT64  ParentP2PBridgeBase;
  UINT8   BaseClass;
  UINT8   SubClass;
  UINT8   CapHeaderOffset;
  PCI_REG_PCIE_CAPABILITY  PcieCap;

  for (ParentRpBus = 0; ParentRpBus <= 0xFF; ++ParentRpBus) {
    for (ParentRpDev = 0; ParentRpDev <= PCI_MAX_DEVICE; ++ParentRpDev) {
      for (ParentRpFunc = 0; ParentRpFunc <= PCI_MAX_FUNC; ++ParentRpFunc) {
        ParentP2PBridgeBase = PCI_SEGMENT_LIB_ADDRESS (Segment, ParentRpBus, ParentRpDev, ParentRpFunc, 0);
        if (PciSegmentRead16 (ParentP2PBridgeBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
          if (ParentRpFunc == 0) {
            //
            // IF Fun is zero, stop enumerating other functions of the particular bridge
            //
            break;
          }
          continue;
        }
        BaseClass = PciSegmentRead8 (ParentP2PBridgeBase + PCI_CLASSCODE_OFFSET + 2);
        if (BaseClass == PCI_CLASS_BRIDGE) {
          SubClass = PciSegmentRead8 (ParentP2PBridgeBase + PCI_CLASSCODE_OFFSET + 1);
          if (SubClass == PCI_CLASS_BRIDGE_P2P) {
            CapHeaderOffset = PcieFindCapId (Segment, ParentRpBus, ParentRpDev, ParentRpFunc, EFI_PCI_CAPABILITY_ID_PCIEXP);
            PciSegmentReadBuffer (ParentP2PBridgeBase + CapHeaderOffset + OFFSET_OF (PCI_CAPABILITY_PCIEXP, Capability), sizeof (UINT16), &PcieCap);
            if (PcieCap.Bits.DevicePortType == PCIE_DEVICE_PORT_TYPE_PCIE_ENDPOINT) {
              continue;
            }
            if (PciSegmentRead8 (ParentP2PBridgeBase + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET) == CurrentRpBus) {
              if (PcieCap.Bits.DevicePortType == PCIE_DEVICE_PORT_TYPE_UPSTREAM_PORT) {
                //
                // If the parent is a UPSTREAM_PORT, then it must inherit all resource from grand parent
                // And since UPSTREAM_PORT is not a HotPlug P2PB, so check the resoruce from grand parent.
                //
                ParentP2PBridgeBase = GetParentPciAddress (Segment, ParentRpBus);
                return ParentP2PBridgeBase;
              }
              goto Exit;
            }
          }
        }
      }
    }
  }

  Exit:
  DEBUG ((DEBUG_INFO, "Parent P2PB is Segment 0x%x, Bus 0x%x, Device 0x%x, Function 0x%x \n", Segment, ParentRpBus, ParentRpDev, ParentRpFunc));
  DEBUG ((DEBUG_INFO, "PcieCap.Bits.DevicePortType = 0x%x \n", PcieCap.Bits.DevicePortType));
  ParentP2PBridgeBase = (((UINT64)Segment << 32) | (ParentRpBus << 24) | (ParentRpDev << 16) | (ParentRpFunc << 8));
  return ParentP2PBridgeBase;
}

/**
  Get the Parent Resource

  @param[in]  HpcPciAddress       The address of the Hot Plug Controller function on the PCI bus.
  @param[out] ParentBusNum        Parent Reserved Bus resource Number.
  @param[out] ParentPcieMegaMem   Parent Reserved Alignment of MEM resource.
  @param[out] ParentPciePMegaMem  Parent Reserved Alignment of PMEM resource.
  @param[out] ParentPcieKiloIo    Parent Reserved Pcie Kilo Io Number.

  @retval     EFI_SUCCESS.
**/
EFI_STATUS
GetParentResourceSize (
  IN  UINT64 HpcPciAddress,
  OUT UINT8  *ParentBusNum,
  OUT UINT16 *ParentPcieMegaMem,
  OUT UINT16 *ParentPciePMegaMem,
  OUT UINT8  *ParentPcieKiloIo
  )
{
  UINT16  Index;
  UINTN   RpBus;
  UINTN   RpDev;
  UINTN   RpFunc;

  RpBus  = (UINTN) ((HpcPciAddress >> 24) & 0xFF);
  RpDev  = (UINTN) ((HpcPciAddress >> 16) & 0xFF);
  RpFunc = (UINTN) ((HpcPciAddress >> 8) & 0xFF);

  DEBUG ((DEBUG_INFO, "[GetParentResourceSize] Segment 0x%x, Bus 0x%x, Device 0x%x, Function 0x%x \n", ((HpcPciAddress >> 32) & 0x01), RpBus, RpDev, RpFunc));

  for (Index = 0; Index < MAX_P2PB_OF_TBT_DAISY_CHAIN; Index++) {
    if (mP2pbResourceRecord[Index].HpcPciAddress == 0) {
      continue;
    }
    if ((UINT64)HpcPciAddress == (UINT64)mP2pbResourceRecord[Index].HpcPciAddress) {
        *ParentBusNum       = mP2pbResourceRecord[Index].RsvdExtraBusNum;
        *ParentPcieMegaMem  = mP2pbResourceRecord[Index].RsvdPcieMegaMem;
        *ParentPciePMegaMem = mP2pbResourceRecord[Index].RsvdPciePMegaMem;
        *ParentPcieKiloIo   = mP2pbResourceRecord[Index].RsvdPcieKiloIo;
        break;
    }
  }
  return EFI_SUCCESS;
}

/**
  Check the HotPlug Capable of P2P bridge at the same Bus

  @param[in]  Segment             Segment Number
  @param[in]  CurrentRpBus        P2P Bridge Bus Number.
  @param[out] *StrucIndex         Indxe number of NUMBER_OF_HOTPLUG_BRIDGE struct.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid Bus number.
  @retval EFI_ABORTED             No matched P2P Bridge, exit without recorded.
**/
EFI_STATUS
GetCurrentBusP2pbHotPlug (
  IN  UINT8  Segment,
  IN  UINT8  CurrentRpBus,
  OUT UINT8  *StrucIndex
  )
{
  UINT8   CurrentRpDev;
  UINT8   CurrentRpFunc;
  UINT64  CurrentP2PBridgeBase;
  UINT8   BaseClass;
  UINT8   SubClass;
  UINT8   CapHeaderOffset;
  UINT8   Index;
  PCI_REG_PCIE_SLOT_CAPABILITY  PcieSlotCap;

  DEBUG ((DEBUG_INFO, "[GetCurrentBusP2pbHotPlug] Segment 0x%x, Bus 0x%x\n", Segment, CurrentRpBus));
  if ((CurrentRpBus == 0) | (CurrentRpBus > 0xff)) {
    DEBUG ((DEBUG_INFO, "Invalid Bus Number\n"));
    return EFI_INVALID_PARAMETER;
  }

  for (Index = 0; Index <= 0xff; Index++) {
    if (mNumOfHotPlugBridge[Index].P2pbBusNum == 0) {
      for (CurrentRpDev = 0; CurrentRpDev <= PCI_MAX_DEVICE; ++CurrentRpDev) {
        for (CurrentRpFunc = 0; CurrentRpFunc <= PCI_MAX_FUNC; ++CurrentRpFunc) {
          CurrentP2PBridgeBase = PCI_SEGMENT_LIB_ADDRESS (Segment, CurrentRpBus, CurrentRpDev, CurrentRpFunc, 0);
          if (PciSegmentRead16 (CurrentP2PBridgeBase + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
            if (CurrentRpFunc == 0) {
              //
              // IF Fun is zero, stop enumerating other functions of the particular bridge
              //
              break;
            }
            continue;
          }

          BaseClass = PciSegmentRead8 (CurrentP2PBridgeBase + PCI_CLASSCODE_OFFSET + 2);
          if (BaseClass == PCI_CLASS_BRIDGE) {
            SubClass = PciSegmentRead8 (CurrentP2PBridgeBase + PCI_CLASSCODE_OFFSET + 1);
            if (SubClass == PCI_CLASS_BRIDGE_P2P) {
              mNumOfHotPlugBridge[Index].P2pbSegNum = Segment;
              mNumOfHotPlugBridge[Index].P2pbBusNum = CurrentRpBus;
              // Check HotPlugCapable from PCI_CAPABILITY
              CapHeaderOffset = PcieFindCapId (Segment, (UINT8)CurrentRpBus, CurrentRpDev, CurrentRpFunc, EFI_PCI_CAPABILITY_ID_PCIEXP);
              PciSegmentReadBuffer (CurrentP2PBridgeBase + CapHeaderOffset + OFFSET_OF (PCI_CAPABILITY_PCIEXP, SlotCapability), sizeof (UINT16), &PcieSlotCap);
              if (PcieSlotCap.Bits.HotPlugCapable) {
                mNumOfHotPlugBridge[Index].NumOfP2pbHotPlug += 1;
              } else {
                mNumOfHotPlugBridge[Index].NumOfP2pbNonHotPlug += 1;
              }
              *StrucIndex = Index;
            }
          }
        }
      }
      DEBUG ((DEBUG_INFO, "Data structure Index: 0x%x, Number of P2PB with Hot-Plug: %x, Number of P2PB without Hot-Plug: %x\n", *StrucIndex, mNumOfHotPlugBridge[*StrucIndex].NumOfP2pbHotPlug, mNumOfHotPlugBridge[*StrucIndex].NumOfP2pbNonHotPlug));
      return EFI_SUCCESS;
    } else if ((mNumOfHotPlugBridge[Index].P2pbBusNum == CurrentRpBus) && (mNumOfHotPlugBridge[Index].P2pbSegNum == Segment)) {
      *StrucIndex = Index;
      DEBUG ((DEBUG_INFO, "The number of HotPlug Bridge of Bus already recorded in data structure Index: 0x%x\n", *StrucIndex));
      return EFI_SUCCESS;
    }
  }
  return EFI_ABORTED;
}