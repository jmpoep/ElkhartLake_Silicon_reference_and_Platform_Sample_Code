/** @file
  CPU PCIe DXE/SMM Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/HobLib.h>
#include <SaConfigHob.h>
#include <Library/PciSegmentLib.h>
#include "CpuPcieInfo.h"
#include <Register/CpuPcieRegs.h>
#include <Base.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuPcieLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/IgdRegs.h>


#define LTR_VALUE_MASK (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 + BIT8 + BIT9)
#define LTR_SCALE_MASK (BIT10 + BIT11 + BIT12)
#define PEG_MPS_AUTO   0xFF

///
/// LTR related macros
///
#define LTR_LATENCY_VALUE(x)           (x & LTR_VALUE_MASK)
#define LTR_MULTIPLIER_INDEX(x)        ((UINT32)(x & LTR_SCALE_MASK) >> 10)


typedef struct {
  UINT64  BaseAddr;
  UINT32  Offset;
  UINT32  AndMask;
  UINT32  OrMask;
} BOOT_SCRIPT_REGISTER_SETTING;

typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;

///
/// SA PCI Registers to save for S3 resume
///
GLOBAL_REMOVE_IF_UNREFERENCED UINTN mSaChipsetPciRegistersTable[] = {
  R_SA_DEVEN,
};
//
// Address values for mSaChipsetPciRegistersSaveTable will be initialized at Runtime inside function
// CpuPcieInitPolicy(). The Address uses the Register Offset from table mSaChipsetPciRegistersTable
//
GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_PCI_REGISTER_SAVE mSaChipsetPciRegistersSaveTable[] = {
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_DEVEN
};

///
/// SA IGFX PCI Registers to save for S3 resume
///
GLOBAL_REMOVE_IF_UNREFERENCED UINTN mSaIgfxPciRegistersTable[] = {
  R_SA_IGD_SWSCI_OFFSET,
  R_SA_IGD_ASLS_OFFSET,
  R_SA_IGD_GTTMMADR + 4,
  R_SA_IGD_GTTMMADR,
  R_SA_IGD_GMADR + 4,
  R_SA_IGD_GMADR,
  R_SA_IGD_IOBAR,
  R_SA_IGD_CMD
};
//
// Address values for mSaIgfxPciRegistersSaveTable will be initialized at Runtime inside function
// CpuPcieInitPolicy(). The Address uses the Register Offset from table mSaIgfxPciRegistersTable
//
GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_PCI_REGISTER_SAVE mSaIgfxPciRegistersSaveTable[] = {
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_SWSCI_OFFSET
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_ASLS_OFFSET
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_GTTMMADR + 4
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_GTTMMADR
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_GMADR + 4
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_GMADR
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_IOBAR
  {0,  S3BootScriptWidthUint32,  0},  // R_SA_IGD_CMD
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT64                          mDeviceCapMmBaseSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                          mDeviceExtCapLtrOffsetSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                          mDeviceExtCapVcOffsetSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                          mDeviceBusNumberSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mDeviceAspmSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mDeviceLtrObffSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mDeviceMaxSnoopLatencySave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mDeviceMaxNoSnoopLatencySave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mDeviceTcxVc0MappingSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mCommonClock [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER] = {0, 0, 0};
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mDeviceControlRegisterSave [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER][MAX_SUPPORTED_DEVICE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mNumberOfDeviceFound [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER] = {0, 0, 0};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mPAMSave [MAX_PAM_REG_COUNT];
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                           mSaChipsetPciRegistersSave [sizeof (mSaChipsetPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE)];
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                           mSaIgfxPciRegistersSave [sizeof (mSaIgfxPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE)];

///
/// Store required policy setting in global variables.
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mDxeSaPolicyRevision;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_PCIE_ASPM_CONFIG            mPegAspmPerPort[MAX_SUPPORTED_ROOT_BRIDGE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mPegAspmL0sPerPort[MAX_SUPPORTED_ROOT_BRIDGE_NUMBER];
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                         mCridEnable;

GLOBAL_REMOVE_IF_UNREFERENCED PCIE_ASPM_OVERRIDE_LIST         *mPcieAspmDevsOverride;
GLOBAL_REMOVE_IF_UNREFERENCED PCIE_LTR_DEV_INFO               *mPcieLtrDevsOverride;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mSnoopLatencyOvrValue;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                          mNonSnoopLatencyOvrValue;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_PCIE_PWR_OPT                mPegPwrOpt[SA_PEG_MAX_FUN];

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mMaxBusNumberSupported;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STATUS                      mEnumStatus;

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

  @param[in] Bus       -   Pci Bus Number
  @param[in] Device    -   Pci Device Number
  @param[in] Function  -   Pci Function Number
  @param[in] CapId     -   CAPID to search for

  @retval 0            - CAPID not found
  @retval Other        - CAPID found, Offset of desired CAPID
**/
UINT32
LibPcieFindCapId (
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  )
{
  UINT64 DeviceBaseAddress;
  UINT8  CapHeader;

  ///
  /// Always start at Offset 0x34
  ///
  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Device, Function, 0);
  CapHeader = PciSegmentRead8 (DeviceBaseAddress + PCI_CAPBILITY_POINTER_OFFSET);
  if (CapHeader == 0xFF) {
    return 0;
  }

  while (CapHeader != 0) {
    ///
    /// Bottom 2 bits of the pointers are reserved per PCI Local Bus Spec 2.2
    ///
    CapHeader &= ~(BIT1 + BIT0);
    ///
    /// Search for desired CapID
    ///
    if (PciSegmentRead8 (DeviceBaseAddress + CapHeader) == CapId) {
      return CapHeader;
    }

    CapHeader = PciSegmentRead8 (DeviceBaseAddress + (CapHeader + 1));
  }

  return 0;
}

/**
  Search and return the offset of desired Pci Express Capability ID
  CAPID list:
    0x0001 = Advanced Error Rreporting Capability
    0x0002 = Virtual Channel Capability
    0x0003 = Device Serial Number Capability
    0x0004 = Power Budgeting Capability

  @param[in] PegBaseAddress - DeviceMmBase which points to PCIe device register space.
  @param[in] CapId          - Extended CAPID to search for

  @retval 0       - CAPID not found
  @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
LibPcieFindExtendedCapId (
  IN UINT64  PegBaseAddress,
  IN UINT16  CapId
  )
{
  UINT16  CapHeaderOffset;
  UINT16  CapHeaderId;

  ///
  /// Start to search at Offset 0x100
  /// Get Capability Header
  ///
  CapHeaderId     = 0;
  CapHeaderOffset = 0x100;

  while (CapHeaderOffset != 0 && CapHeaderId != 0xFFFF) {
    ///
    /// Search for desired CapID
    ///
    CapHeaderId = PciSegmentRead16 (PegBaseAddress + CapHeaderOffset);
    if (CapHeaderId == CapId) {
      return CapHeaderOffset;
    }

    CapHeaderOffset = (PciSegmentRead16 (PegBaseAddress + CapHeaderOffset + 2) >> 4);
  }

  return 0;
}

/**
  Enumerate all end point devices connected to root bridge ports and record their MMIO base address

  @exception EFI_UNSUPPORTED      PCIe capability structure not found
  @retval    EFI_SUCCESS          All done successfully
**/
EFI_STATUS
EnumerateAllPcieDevices (
  VOID
  )
{
  UINT32      CapOffset1;
  UINT32      CapOffset2;
  UINT64      RootPortMmBase;
  UINT8       SubBusNum;
  UINT8       BusNum;
  UINT8       PegBus;
  UINT8       PegDev;
  UINT8       PegFunc;
  UINT64      PegBaseAddress;
  UINT8       Bus;
  UINT8       Dev;
  UINT8       Func;
  UINT64      SubDeviceBaseAddress;
  UINT8       RootBridgeCompleted;
  UINT8       RootBridgeDeviceNumber [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER] = {1, 1, 1, 6};
  UINT8       RootBridgeFunctionNumber [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER] = {0, 1, 2, 0};

  mMaxBusNumberSupported = 0xFF >> ((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIEXBAR)) & B_SA_PCIEXBAR_LENGTH_MASK) >> N_SA_PCIEXBAR_LENGTH_OFFSET);

  PegBus = 0;
  for (RootBridgeCompleted = 0; RootBridgeCompleted < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; RootBridgeCompleted++) {
    PegDev  = RootBridgeDeviceNumber [RootBridgeCompleted];
    PegFunc = RootBridgeFunctionNumber [RootBridgeCompleted];
    PegBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PegBus, PegDev, PegFunc, 0);
    if (PciSegmentRead16 (PegBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }
    ///
    /// Save Bridge Bus number assignment
    ///
    mDeviceBusNumberSave [RootBridgeCompleted][0] = PciSegmentRead32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET);
    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint32,
      PcdGet64 (PcdSiPciExpressBaseAddress) + PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
      1,
      &mDeviceBusNumberSave [RootBridgeCompleted][0]
      );

    ///
    /// Get the pointer to the Port PCI Express Capability Structure.
    ///
    CapOffset1  = LibPcieFindCapId (PegBus, PegDev, PegFunc, 0x10);
    if (CapOffset1 == 0) {
      DEBUG ((DEBUG_WARN, "WARN: Cannot find Root Bridge PCIE capability structure.\n"));
      return EFI_UNSUPPORTED;
    }

    ///
    /// Save root bridge device MM base
    ///
    RootPortMmBase = PegBaseAddress;
    mDeviceCapMmBaseSave [RootBridgeCompleted][0] = RootPortMmBase + CapOffset1;
    DEBUG ((DEBUG_INFO, "Root bridge [B%X|D%X|F%X]:", PegBus, PegDev, PegFunc));
    DEBUG ((DEBUG_INFO, " mDeviceCapMmBaseSave [%d][0] = 0x%X\n", RootBridgeCompleted, mDeviceCapMmBaseSave [RootBridgeCompleted][0]));
    mNumberOfDeviceFound [RootBridgeCompleted] ++;

    ///
    /// Get Secondary bus number and Subordinate bus number for end point device enumeration
    ///
    BusNum = PciSegmentRead8 (PegBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
    SubBusNum = PciSegmentRead8 (PegBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET);
    for (Bus = SubBusNum; Bus >= BusNum; Bus--) {
      for (Dev = 0; Dev < 32; Dev++) {
        for (Func =0; Func <=7; Func++) {
          ///
          /// Read Vendor ID to check if device exists
          /// if no device exists, then check next device
          ///
          if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Dev, 0, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
            ///
            /// No other functions present if Func0 is not preset
            ///
            break;
          }
          SubDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Dev, Func, 0);
          if (PciSegmentRead16 (SubDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
            continue;
          }

          DEBUG ((DEBUG_INFO, "End point [B%X|D%X|F%X]:", Bus, Dev, Func));
          CapOffset2 = LibPcieFindCapId (Bus, Dev, Func, 0x10);
          if (CapOffset2 != 0) {
            ///
            /// Save end point device MM base
            ///
            if (mNumberOfDeviceFound [RootBridgeCompleted] >= MAX_SUPPORTED_DEVICE_NUMBER) {
              DEBUG ((DEBUG_WARN, "WARN: DeviceMmBaseSave array size not big enough.\n"));
              return EFI_BUFFER_TOO_SMALL;
            } else {
              ///
              /// Save Downstream Bus number assignment
              ///
              mDeviceBusNumberSave [RootBridgeCompleted][mNumberOfDeviceFound [RootBridgeCompleted]] = PciSegmentRead32 (SubDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET);
              S3BootScriptSaveMemWrite (
                S3BootScriptWidthUint32,
                PcdGet64 (PcdSiPciExpressBaseAddress) + SubDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
                1,
                &mDeviceBusNumberSave [RootBridgeCompleted][mNumberOfDeviceFound [RootBridgeCompleted]]
                );
              mDeviceCapMmBaseSave [RootBridgeCompleted][mNumberOfDeviceFound [RootBridgeCompleted]] = SubDeviceBaseAddress + CapOffset2;
              DEBUG ((DEBUG_INFO, " mDeviceCapMmBaseSave [%d][%d]", RootBridgeCompleted, mNumberOfDeviceFound [RootBridgeCompleted]));
              DEBUG ((DEBUG_INFO, " = 0x%X\n", mDeviceCapMmBaseSave [RootBridgeCompleted][mNumberOfDeviceFound [RootBridgeCompleted]]));
              mNumberOfDeviceFound [RootBridgeCompleted] ++;
            }
          }
        }
      }
    }
    DEBUG ((DEBUG_INFO, "mNumberOfDeviceFound [%d] = %d\n", RootBridgeCompleted, mNumberOfDeviceFound [RootBridgeCompleted]));
  }

  return EFI_SUCCESS;
}

/**
  Initialize VC0 traffic class

  @param[in] RootBridgeCompleted - The first index (point to root bridge) of the device MMIO Base array to select bridge which currently under working or completed.
  @param[in] EndpointCompleted   - The second index (point to end point devices) of the device MMIO Base array to select device which currently under working or completed.

  @exception EFI_UNSUPPORTED - VC capability ID not found
  @retval EFI_SUCCESS     - VC mapping correctly initialized
**/
EFI_STATUS
PcieInitTcxVc0 (
  IN UINT8   RootBridgeCompleted,
  IN UINT8   EndpointCompleted
  )
{
  UINT32  Offset;
  UINT8   Data8And;
  UINT8   Data8Or;
  UINT64  PegBaseAddress;
  UINT8   i;
  UINT8   CapId[2];

  Offset         = 0;
  i              = 0;
  CapId[0] = '2';
  CapId[1] = '8';
  PegBaseAddress = (UINT64) (mDeviceCapMmBaseSave [RootBridgeCompleted][EndpointCompleted] & (UINT64) ~0xFF);
  ///
  /// Set TCx-VC0 value - map all TCs to VC0
  ///
  ///
  /// Fix for ClientSW s5039821: PTC Gen3 BIOS Test : MFVC Capability test failure
  ///
  while ((Offset == 0x0) && (i < sizeof (CapId))) {
    mDeviceExtCapVcOffsetSave [RootBridgeCompleted][EndpointCompleted] |= LibPcieFindExtendedCapId (PegBaseAddress, CapId[i]);
    Offset = mDeviceExtCapVcOffsetSave [RootBridgeCompleted][EndpointCompleted];
    i++;
  }

  DEBUG ((DEBUG_INFO, "PTC CpuPcieLib.c - Offset: 0x%x\n", Offset));
  if (Offset == 0) {
    DEBUG ((DEBUG_INFO, "VC ExtCap structure not found on device [0x%08X]\n", PegBaseAddress));
    return EFI_UNSUPPORTED;
  }

  Data8And        = 0;
  Data8Or         = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
  PciSegmentAndThenOr8 (PegBaseAddress + Offset + 0x014, Data8And, Data8Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint8,
    PcdGet64 (PcdSiPciExpressBaseAddress) + PegBaseAddress + Offset + 0x014,
    &Data8Or,
    &Data8And
    );
  mDeviceTcxVc0MappingSave [RootBridgeCompleted][EndpointCompleted] = PciSegmentRead8 (PegBaseAddress + Offset + 0x014);
  return EFI_SUCCESS;
}

/**
  Sets Common Clock, TCx-VC0 mapping, and Max Payload for PCIe
**/
VOID
CpuPcieConfigBeforeOpRom (
  VOID
  )
{
  UINT8       RootBridgeIndex;
  UINT8       DeviceIndex;
  UINT8       DeviceSearchIndex;
  UINT16      DeviceMaxPayload;
  UINT64      RootPortPcieCapMmBase;
  UINT64      DevicePcieCapMmBase;
  UINT64      DeviceBaseAddress;
  UINT8       SecBus;
  UINT16      Data16And;
  UINT16      Data16Or;
  UINT16      MaxPayload [MAX_SUPPORTED_ROOT_BRIDGE_NUMBER];
  UINT8       CommonClockSupported;
  UINT8       LinksToTrain [MAX_SUPPORTED_DEVICE_NUMBER];
  UINT8       LinksToTrainCount;
  UINT8       StartIndex;

  for (RootBridgeIndex = 0; RootBridgeIndex < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; RootBridgeIndex++) {
    RootPortPcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][0];
    if (RootPortPcieCapMmBase == 0) {
      continue;
    }
    ///
    /// Get the PCIE root Port Max Payload Size support.
    ///
    MaxPayload [RootBridgeIndex] = PciSegmentRead16 (RootPortPcieCapMmBase + 4) & (BIT2 | BIT1 | BIT0);

    mCommonClock[RootBridgeIndex] = 0;
    LinksToTrainCount = 0;
    ///
    /// Check the Port Slot Clock Configuration Bit for the root port.
    ///
    if ((PciSegmentRead16 (RootPortPcieCapMmBase + 0x12) & BIT12) == 0) {
      DEBUG ((DEBUG_INFO, "CommonClock not supported by root bridge [B%X|D%X|F%X|R%X]\n",
              (RootPortPcieCapMmBase >> 20)   & mMaxBusNumberSupported,
              (RootPortPcieCapMmBase >> 15)   & 0x1F,
              (RootPortPcieCapMmBase >> 12)   & 0x07,
              (RootPortPcieCapMmBase + 0x012) & 0xFFF));
    } else {
      ///
      /// Get the secondary bus and search for all functions with that bus in the list to make sure all support common clock
      ///
      CommonClockSupported = 0;
      SecBus = PciSegmentRead8 ((RootPortPcieCapMmBase & (UINT64) ~0xFFF) + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
      for (DeviceSearchIndex = 1; DeviceSearchIndex < mNumberOfDeviceFound [RootBridgeIndex]; DeviceSearchIndex++) {
        if (((mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] >> 20) & mMaxBusNumberSupported) == SecBus) {
          if ((PciSegmentRead16 (mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] + 0x12) & BIT12) == 0) {
            CommonClockSupported = FALSE;
            break;
          } else {
            CommonClockSupported++;
          }
        }
      }
      ///
      /// If all functions support common clock, enable it for all.
      ///
      if (CommonClockSupported > 0) {
        LinksToTrain[LinksToTrainCount] = 0;
        LinksToTrainCount++;
        Data16Or  = BIT6;
        Data16And = (UINT16) ~BIT6;
        PciSegmentOr8 (RootPortPcieCapMmBase + 0x10, BIT6);
        mCommonClock[RootBridgeIndex] = 1;
        S3BootScriptSaveMemReadWrite (
          S3BootScriptWidthUint8,
          PcdGet64 (PcdSiPciExpressBaseAddress) + RootPortPcieCapMmBase + 0x10,
          &Data16Or,  ///< Data to be ORed
          &Data16And  ///< Data to be ANDed
          );
        DEBUG ((DEBUG_INFO, "Set CommonClock for Root Device [B%X|D%X|F%X]\n",
                (RootPortPcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                (RootPortPcieCapMmBase >> 15)   & 0x1F,
                (RootPortPcieCapMmBase >> 12)   & 0x07,
                (RootPortPcieCapMmBase + 0x010) & 0xFFF));
        for (DeviceSearchIndex = 1; DeviceSearchIndex < mNumberOfDeviceFound[RootBridgeIndex]; DeviceSearchIndex++) {
          if (((mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] >> 20) & mMaxBusNumberSupported) == SecBus) {
            DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex];
            PciSegmentOr8 (DevicePcieCapMmBase + 0x10, BIT6);
            mCommonClock[RootBridgeIndex] = 1;
            S3BootScriptSaveMemReadWrite (
              S3BootScriptWidthUint8,
              PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x10,
              &Data16Or,  ///< Data to be ORed
              &Data16And  ///< Data to be ANDed
              );
            DEBUG ((DEBUG_INFO, "  and Link Device [B%X|D%X|F%X]\n",
                    (DevicePcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                    (DevicePcieCapMmBase >> 15)   & 0x1F,
                    (DevicePcieCapMmBase >> 12)   & 0x07,
                    (DevicePcieCapMmBase + 0x010) & 0xFFF));
          }
        }
      }
    }
    ///
    /// Configure the rest of the devices for this root port
    ///
    for (DeviceIndex = 1; DeviceIndex < mNumberOfDeviceFound [RootBridgeIndex]; DeviceIndex++) {
      ///
      /// Set TCx-VC0 mapping on Endpoint
      ///
      PcieInitTcxVc0 (RootBridgeIndex, DeviceIndex);

      DevicePcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][DeviceIndex];
      ///
      /// Get the end point function Max Payload Size support
      ///
      DeviceMaxPayload = PciSegmentRead16 (DevicePcieCapMmBase + 4) & (BIT2 | BIT1 | BIT0);
      DEBUG ((DEBUG_INFO, "CAP_MPS of [%X] = %X\n", DevicePcieCapMmBase + 4, DeviceMaxPayload));
      ///
      /// Obtain the minimum Max Payload Size between the PCIE root Port and the end point functions
      ///
      if (MaxPayload [RootBridgeIndex] > DeviceMaxPayload) {
        MaxPayload [RootBridgeIndex] = DeviceMaxPayload;
      }
      ///
      /// For Common Clock support, check only upstream for bridge or endpoints to configure both sides of the link.
      ///
      DeviceBaseAddress = DevicePcieCapMmBase & (UINT64) ~0xFFF;
      if (PciSegmentRead8 (DeviceBaseAddress + 0xE) == 1) {
        if ((PciSegmentRead8 (DevicePcieCapMmBase + 0x2) >> 4) == 0x6) {
          ///
          /// Before looking for the other side of the link, make sure the device supports common clock. If not we can skip the rest.
          ///
          if ((PciSegmentRead16 (DevicePcieCapMmBase + 0x12) & BIT12) != 0) {
            ///
            /// Get the secondary bus and search for all functions with that bus in the list to make sure all support common clock
            ///
            CommonClockSupported = 0;
            SecBus = PciSegmentRead8 (DeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
            for (DeviceSearchIndex = 1; DeviceSearchIndex < DeviceIndex; DeviceSearchIndex++) {
              if (((mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] >> 20) & mMaxBusNumberSupported) == SecBus) {
                if ((PciSegmentRead16 (mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] + 0x12) & BIT12) == 0) {
                  CommonClockSupported = FALSE;
                  break;
                } else {
                  CommonClockSupported++;
                }
              }
            }
            ///
            /// If all functions support common clock, enable it for all.
            ///
            if (CommonClockSupported > 0) {
              DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][DeviceIndex];
              LinksToTrain[LinksToTrainCount] = DeviceIndex;
              LinksToTrainCount++;
              Data16Or  = BIT6;
              Data16And = (UINT16) ~BIT6;
              mCommonClock[RootBridgeIndex] = 1;
              PciSegmentOr8 (DevicePcieCapMmBase + 0x10, BIT6);
              S3BootScriptSaveMemReadWrite (
                S3BootScriptWidthUint8,
                PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x10,
                &Data16Or,  ///< Data to be ORed
                &Data16And  ///< Data to be ANDed
                );
              DEBUG ((DEBUG_INFO, "Set CommonClock for Link between Port [B%X|D%X|F%X]\n",
                      (DevicePcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                      (DevicePcieCapMmBase >> 15)   & 0x1F,
                      (DevicePcieCapMmBase >> 12)   & 0x07
                      ));
              for (DeviceSearchIndex = 1; DeviceSearchIndex < DeviceIndex; DeviceSearchIndex++) {
                if (((mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex] >> 20) & mMaxBusNumberSupported) == SecBus) {
                  DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][DeviceSearchIndex];
                  PciSegmentOr8 (DevicePcieCapMmBase + 0x10, BIT6);
                  mCommonClock[RootBridgeIndex] = 1;
                  S3BootScriptSaveMemReadWrite (
                    S3BootScriptWidthUint8,
                    PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x10,
                    &Data16Or,  ///< Data to be ORed
                    &Data16And  ///< Data to be ANDed
                    );
                  DEBUG ((DEBUG_INFO, "  and Port [B%X|D%X|F%X]\n",
                          (DevicePcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                          (DevicePcieCapMmBase >> 15)   & 0x1F,
                          (DevicePcieCapMmBase >> 12)   & 0x07
                          ));
                }
              }
            }
          }
        }
      }
    }
    ///
    /// If common clock was set for any link, trigger a supported on root port and endpoint, retrain link
    ///
    if (LinksToTrainCount > 0) {
      DEBUG ((DEBUG_INFO, "CommonClock was set. Retrain links\n"));
      ///
      /// Retrain the Link per PCI Express Specification.
      ///
      if (LinksToTrain[0] == 0) {
        StartIndex = 1;
      } else {
        StartIndex = 0;
      }
      Data16Or = BIT5;
      Data16And = (UINT8) ~BIT5;
      for (DeviceIndex = StartIndex; DeviceIndex < LinksToTrainCount; DeviceIndex++) {
        DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][LinksToTrain[DeviceIndex]];
        DEBUG ((DEBUG_INFO, "Retrain Port [B%X|D%X|F%X]\n",
                (DevicePcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                (DevicePcieCapMmBase >> 15)   & 0x1F,
                (DevicePcieCapMmBase >> 12)   & 0x07
                ));
        PciSegmentOr8 (DevicePcieCapMmBase + 0x10, BIT5);
        S3BootScriptSaveMemReadWrite (
          S3BootScriptWidthUint8,
          PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x10,
          &Data16Or,
          &Data16And
          );
      }
      if (LinksToTrain[0] == 0) {
        DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][0];
        DEBUG ((DEBUG_INFO, "Retrain Root Port [B%X|D%X|F%X]\n",
                (DevicePcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                (DevicePcieCapMmBase >> 15)   & 0x1F,
                (DevicePcieCapMmBase >> 12)   & 0x07
                ));
        PciSegmentOr8 (DevicePcieCapMmBase + 0x10, BIT5);
        S3BootScriptSaveMemReadWrite (
          S3BootScriptWidthUint8,
          PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x10,
          &Data16Or,
          &Data16And
          );
      } else {
        DevicePcieCapMmBase = mDeviceCapMmBaseSave[RootBridgeIndex][LinksToTrain[LinksToTrainCount-1]];
      }
      ///
      /// Wait until the retraining of the last link is completed.
      ///
      while ((PciSegmentRead16 (DevicePcieCapMmBase + 0x12) & BIT11) != 0);
      ///
      /// Poll until BIT11 clear. 200 ms as polling timeout
      ///
      Data16Or  = BIT11;
      Data16And = 0;
      S3BootScriptSaveMemPoll (
        S3BootScriptWidthUint16,
        PcdGet64 (PcdSiPciExpressBaseAddress) + DevicePcieCapMmBase + 0x12,
        &Data16Or,
        &Data16And,
        1,
        200000
        );
    }

    ///
    /// Set Max Payload to all root and end point devices
    ///
    MaxPayload [RootBridgeIndex] <<= 5;
    for (DeviceIndex = 0; DeviceIndex < mNumberOfDeviceFound [RootBridgeIndex]; DeviceIndex++) {
      DevicePcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][DeviceIndex];
      DEBUG ((DEBUG_INFO, "Set MPS of [%X] to %X\n", DevicePcieCapMmBase + 0x8, MaxPayload [RootBridgeIndex]));
      PciSegmentAndThenOr16 (DevicePcieCapMmBase + 0x8, (UINT16) ~(BIT7 | BIT6 | BIT5), MaxPayload [RootBridgeIndex]);
      ///
      /// S3 Save for Device Control Register on all bridges and devices is done after the OpRom has run in EnableExtendedTag.
      ///
    }
  }
}

/**
  Calculate ASPM Auto setting value

  @param[in] RootBridgeIndex   - Root Bridge Index to select mDeviceCapMmBaseSave array elements for ASPM capability calculation.

  @retval AspmVal - ASPM settings for RP and all EP
**/
UINT16
PcieCalcAspmSettings (
  IN  UINT8   RootBridgeIndex
  )
{
  UINT16              RootPortAspm;
  UINT16              EndPointAspm;
  UINT32              PcieAspmDev;
  UINT16              EndPointVendorId;
  UINT16              EndPointDeviceId;
  UINT8               EndPointRevId;
  UINT16              AspmVal;
  UINT32              PortLxLat;
  UINT32              EndPointLxLat;
  UINT32              LxLat;
  UINT8               EndpointCompleted;
  UINT64              RootPortPcieCapMmBase;
  UINT32              RootPortLinkCap;
  UINT64              EndPointPcieCapMmBase;
  UINT32              EndPointLinkCap;
  UINT32              EndPointDevCap;

  RootPortPcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][0];
  RootPortLinkCap       = PciSegmentRead32 (RootPortPcieCapMmBase + 0x0C);

  ///
  /// Obtain initial ASPM settings from respective port capability registers.
  ///
  RootPortAspm = (RootPortLinkCap >> 10) & 3;
  DEBUG ((DEBUG_INFO, "Root [%X] Aspm capability = %X\n", RootPortPcieCapMmBase + 0xC, RootPortAspm));
  AspmVal = RootPortAspm;
  EndpointCompleted = 1;

  while (EndpointCompleted < mNumberOfDeviceFound [RootBridgeIndex]) {
    EndPointPcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted];
    EndPointDevCap        = PciSegmentRead32 (EndPointPcieCapMmBase + 0x04);
    EndPointLinkCap       = PciSegmentRead32 (EndPointPcieCapMmBase + 0x0C);

    EndPointAspm = (EndPointLinkCap >> 10) & 3;
    DEBUG ((DEBUG_INFO, "End point [%X] Aspm capability = %X\n", EndPointPcieCapMmBase + 0xC, EndPointAspm));
    if (mPcieAspmDevsOverride != NULL) {
      ///
      /// Mask APMC with values from lookup table.
      /// RevID of 0xFF applies to all steppings.
      ///
      EndPointVendorId  = PciSegmentRead16 ((EndPointPcieCapMmBase & (UINT64) ~0xFF) + 0x000);
      EndPointDeviceId  = PciSegmentRead16 ((EndPointPcieCapMmBase & (UINT64) ~0xFF) + 0x002);
      EndPointRevId     = PciSegmentRead8  ((EndPointPcieCapMmBase & (UINT64) ~0xFF) + 0x008);
      DEBUG ((DEBUG_INFO, "End point [%X] VendorID:DeviceID = %04X:%04X RevID=%02X\n",
              EndPointPcieCapMmBase, EndPointVendorId, EndPointDeviceId, EndPointRevId));
      PcieAspmDev       = 0;
      while ((mPcieAspmDevsOverride[PcieAspmDev].VendorId != CPU_PCIE_DEV_END_OF_TABLE)
             && (PcieAspmDev < MAX_PCIE_ASPM_OVERRIDE)) {
        if ((mPcieAspmDevsOverride[PcieAspmDev].VendorId == EndPointVendorId) &&
            (mPcieAspmDevsOverride[PcieAspmDev].DeviceId == EndPointDeviceId) &&
            ((mPcieAspmDevsOverride[PcieAspmDev].RevId == 0xFF) ||
             (mPcieAspmDevsOverride[PcieAspmDev].RevId == EndPointRevId))) {
          RootPortAspm &= (UINT16) mPcieAspmDevsOverride[PcieAspmDev].RootApmcMask;
          EndPointAspm &= (UINT16) mPcieAspmDevsOverride[PcieAspmDev].EndpointApmcMask;
          break;
        }
        PcieAspmDev++;
      }
    }

    if (AspmVal > EndPointAspm) {
      AspmVal = EndPointAspm;
      ///
      /// In case L0s and L1 both can't be enabled, return the result now.
      ///
      if ((AspmVal & 0x03) == 0) {
        return AspmVal;
      }
    }
    ///
    /// Check if L1 should be enabled based on port and endpoint L1 exit latency.
    ///
    if (AspmVal & BIT1) {
      if (!(EndPointLinkCap & BIT22) && !(AspmVal & BIT0)) {
        DEBUG ((DEBUG_INFO, "\nDevice [%X] ASPM Optionality Compliance bit not set!", EndPointPcieCapMmBase));
        DEBUG ((DEBUG_INFO, "ASPM L1-Only setting is not supported!\n"));
        AspmVal = 0;
        return AspmVal;
      }
      PortLxLat = RootPortLinkCap & (BIT17 + BIT16 + BIT15);
      EndPointLxLat = EndPointLinkCap & (BIT17 + BIT16 + BIT15);
      DEBUG ((DEBUG_INFO, "Root [%X] L1 Exit Latency = %X\n", RootPortPcieCapMmBase + 0xC, PortLxLat >> 15));
      DEBUG ((DEBUG_INFO, "End  [%X] L1 Exit Latency = %X\n", EndPointPcieCapMmBase + 0xC, EndPointLxLat >> 15));
      LxLat = PortLxLat;
      if (PortLxLat < EndPointLxLat) {
        LxLat = EndPointLxLat;
      }
      ///
      /// check if the value is bigger than endpoint L1 acceptable exit latency, if it is
      /// larger than accepted value, then we should disable L1
      ///
      LxLat >>= 6;
      DEBUG ((DEBUG_INFO, "End [%X] L1 Acceptable Latency = %X\n", EndPointPcieCapMmBase + 0x4,
              (EndPointDevCap & (BIT11 + BIT10 + BIT9)) >> 9));
      if (LxLat > (EndPointDevCap & (BIT11 + BIT10 + BIT9))) {
        AspmVal &= ~BIT1;
        if ((AspmVal & 0x03) == 0) {
          return AspmVal;
        }
      }
    }
    ///
    /// Check if L0s should be enabled based on port and endpoint L0s exit latency.
    ///
    if (AspmVal & BIT0) {
      PortLxLat     = RootPortLinkCap & (BIT14 + BIT13 + BIT12);
      EndPointLxLat = EndPointLinkCap & (BIT14 + BIT13 + BIT12);
      DEBUG ((DEBUG_INFO, "Root [%X] L0s Exit Latency = %X\n", RootPortPcieCapMmBase + 0xC, PortLxLat >> 12));
      DEBUG ((DEBUG_INFO, "End  [%X] L0s Exit Latency = %X\n", EndPointPcieCapMmBase + 0xC, EndPointLxLat >> 12));
      LxLat = PortLxLat;
      if (PortLxLat < EndPointLxLat) {
        LxLat = EndPointLxLat;
      }
      ///
      /// check if the value is bigger than endpoint L0s acceptable exit latency, if it is
      /// larger than accepted value, then we should disable L0s
      ///
      LxLat >>= 6;
      DEBUG ((DEBUG_INFO, "End [%X] L0s Acceptable Latency = %X\n", EndPointPcieCapMmBase + 0x4,
              (EndPointDevCap & (BIT8 + BIT7 + BIT6)) >> 6));
      if (LxLat > (EndPointDevCap & (BIT8 + BIT7 + BIT6))) {
        AspmVal &= ~BIT0;
        if ((AspmVal & 0x03) ==0) {
          return AspmVal;
        }
      }
    }
    EndpointCompleted ++;
  }
  return AspmVal;
}

/**
  This function compares the actual latency in LatencyValue1
  with actual latency in LatencyValue2 programs the minimum
  back to LatencyValue1, in the required format.

  @param[in] LatencyValue1  - Current latency value
  @param[in] LatencyValue2  - Latency value from the Table
**/
VOID
DetermineLatencyValue (
  IN UINT16   *LatencyValue1,
  IN UINT16   *LatencyValue2
  )
{
  UINT8      Scale1;
  UINT8      Scale2;
  UINT64     ActualLatency1;
  UINT64     ActualLatency2;
  UINT32     Multiplier[6];


  Scale1 = LTR_MULTIPLIER_INDEX (*LatencyValue1);
  Scale2 = LTR_MULTIPLIER_INDEX (*LatencyValue2);
  ActualLatency1 = 0;
  ActualLatency2 = 0;
  Multiplier[0] = 1;
  Multiplier[1] = 32;
  Multiplier[2] = 1024;
  Multiplier[3] = 32768;
  Multiplier[4] = 1048576;
  Multiplier[5] = 33554432;
  if ((Scale1 <= 5) && (Scale2 <= 5)) {
    ActualLatency1 = LTR_LATENCY_VALUE (*LatencyValue1) * Multiplier[Scale1];
    ActualLatency2 = LTR_LATENCY_VALUE (*LatencyValue2) * Multiplier[Scale2];
  }

  ///
  /// Store the lower latency value and corresponding scale bits back to LatencyValue1
  /// and set the Force bit
  ///
  if ((ActualLatency1 == 0) || ActualLatency1 > ActualLatency2) {
    *LatencyValue1 = *LatencyValue2;
  }
}

/**
  This function will scan the LTR override table and update the default values for snoop and non-snoop latencies.

  @param[in] PegBaseAddress   - DeviceMmBase which points to PCIe device register space.
**/
VOID
ScanLtrOverrideTable (
  IN  UINT64  PegBaseAddress
  )
{
  UINT8               EndPointRevId;
  UINT16              EndPointVendorId;
  UINT16              EndPointDeviceId;
  UINT32              PcieLtrDev;

  EndPointVendorId  = PciSegmentRead16 (PegBaseAddress + 0x000);
  EndPointDeviceId  = PciSegmentRead16 (PegBaseAddress + 0x002);
  EndPointRevId     = PciSegmentRead8  (PegBaseAddress + 0x008);
  if (mPcieLtrDevsOverride != NULL) {
    PcieLtrDev = 0;
    while ((mPcieLtrDevsOverride[PcieLtrDev].VendorId != CPU_PCIE_DEV_END_OF_TABLE)
           && (PcieLtrDev < MAX_PCIE_LTR_OVERRIDE)) {
      if ((mPcieLtrDevsOverride[PcieLtrDev].VendorId == EndPointVendorId) &&
          (mPcieLtrDevsOverride[PcieLtrDev].DeviceId == EndPointDeviceId) &&
          ((mPcieLtrDevsOverride[PcieLtrDev].RevId == 0xFF) ||
           (mPcieLtrDevsOverride[PcieLtrDev].RevId == EndPointRevId))
          ) {
        if (mPcieLtrDevsOverride[PcieLtrDev].SnoopLatency & BIT15) {
          DetermineLatencyValue (&mSnoopLatencyOvrValue, &mPcieLtrDevsOverride[PcieLtrDev].SnoopLatency);
        }
        if (mPcieLtrDevsOverride[PcieLtrDev].NonSnoopLatency & BIT15) {
          DetermineLatencyValue (&mNonSnoopLatencyOvrValue, &mPcieLtrDevsOverride[PcieLtrDev].NonSnoopLatency);
        }
        break;
      }
      PcieLtrDev++;
    }
  }
}

/**
  Configure LTR/OBFF on end point device

  @param[in] RootBridgeIndex   - Root Bridge index number to select mDeviceCapMmBaseSave array element for end point device MmBase.
  @param[in] EndpointCompleted - End point device index number to select mDeviceCapMmBaseSave array element for end point device MmBase.
**/
VOID
PcieSetEndpointLtrObff (
  IN UINT8      RootBridgeIndex,
  IN UINT8      EndpointCompleted
  )
{

  UINT16  Data16Or;
  UINT16  Data16And;
  UINT32  DeviceCapabilities2;
  UINT64  PegBaseAddress;
  UINT64  EndpointCapMmBase;
  UINT32  ExtendedCapOffset;
  UINT16  DefaultMaxLatency;
  UINT8   PegFunc;

  PegFunc = (UINT8) ((mDeviceCapMmBaseSave [RootBridgeIndex][0] >> 12) & 0x07);
  if (PegFunc >= SA_PEG_MAX_FUN) {
    DEBUG ((DEBUG_ERROR, "PegFunc out of bound! Exit from PcieSetEndpointLtrObff()!\n"));
    ASSERT (PegFunc < SA_PEG_MAX_FUN);
    return;
  }

  EndpointCapMmBase = mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted];
  ///
  /// Scan the LTR override table
  ///
  PegBaseAddress = EndpointCapMmBase & (UINT64) ~0xFF;
  ScanLtrOverrideTable (PegBaseAddress);
  DeviceCapabilities2 = PciSegmentRead32 (EndpointCapMmBase + 0x24);
  Data16And           = (UINT16) ~(BIT10 + BIT13 + BIT14);
  Data16Or            = 0;
  ///
  /// If mSnoopLatencyOvrValue and mNonSnoopLatencyOvrValue has a value of 0, then this endpoint is not
  /// part of the override table If it supports LTR messaging then enable the capability
  ///
  if ((mSnoopLatencyOvrValue == 0) &&
      (mNonSnoopLatencyOvrValue == 0)) {
    if (DeviceCapabilities2 & BIT11) {
      // If PegPortLtrEnable set to true
      //
      if (mPegPwrOpt[PegFunc].LtrEnable == 1) {
        Data16Or |= BIT10;
      }
    }
  }
  ///
  /// Check if endpoint device is capable of OBFF using WAKE# signaling
  ///
  if ((DeviceCapabilities2 & BIT19) != 0) {
    if (mPegPwrOpt[PegFunc].ObffEnable == 1) {
      Data16Or |= BIT14 | BIT13; ///< 11b - Enable OBFF using WAKE# signaling
    }
  }
  DEBUG ((DEBUG_INFO, "Configure LTR/OBFF setting to EndPoint: [0x%x] to value 0x%x\n",
          EndpointCapMmBase + 0x28, Data16Or));
  PciSegmentAndThenOr16 (EndpointCapMmBase + 0x28, Data16And, Data16Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint16,
    PcdGet64 (PcdSiPciExpressBaseAddress) + EndpointCapMmBase + 0x28,
    &Data16Or,
    &Data16And
    );
  mDeviceLtrObffSave [RootBridgeIndex][EndpointCompleted] = PciSegmentRead16 (EndpointCapMmBase + 0x28);
  ///
  ///
  /// Program LTR Max Latencies
  ///
  if (DeviceCapabilities2 & BIT11) {
    if (mPegPwrOpt[PegFunc].LtrEnable == 1) {
      ///
      /// Get the pointer to the Endpoint PCI Express Extended Capability Structure.
      ///
      mDeviceExtCapLtrOffsetSave [RootBridgeIndex][EndpointCompleted] = LibPcieFindExtendedCapId (PegBaseAddress, 0x18);
      ExtendedCapOffset = mDeviceExtCapLtrOffsetSave [RootBridgeIndex][EndpointCompleted];
      Data16And         = (UINT16) (~0x1FFF);
      Data16Or          = mSnoopLatencyOvrValue;
      DefaultMaxLatency = mPegPwrOpt[PegFunc].LtrMaxSnoopLatency;
      if (ExtendedCapOffset != 0) {
        DetermineLatencyValue (&Data16Or, &DefaultMaxLatency);
        PciSegmentAndThenOr16 (PegBaseAddress + ExtendedCapOffset + 4, Data16And, Data16Or);
        S3BootScriptSaveMemReadWrite (
          S3BootScriptWidthUint16,
          PcdGet64 (PcdSiPciExpressBaseAddress) + PegBaseAddress + ExtendedCapOffset + 4,
          &Data16Or,  ///< Data to be ORed
          &Data16And  ///< Data to be ANDed
          );
        mDeviceMaxSnoopLatencySave [RootBridgeIndex][EndpointCompleted] = PciSegmentRead16 (PegBaseAddress + ExtendedCapOffset + 0x4);
        Data16Or           = mNonSnoopLatencyOvrValue;
        DefaultMaxLatency  = mPegPwrOpt[PegFunc].LtrMaxNoSnoopLatency;
        DetermineLatencyValue (&Data16Or, &DefaultMaxLatency);
        PciSegmentAndThenOr16 (PegBaseAddress + ExtendedCapOffset + 6, Data16And, Data16Or);
        S3BootScriptSaveMemReadWrite (
          S3BootScriptWidthUint16,
          PcdGet64 (PcdSiPciExpressBaseAddress) + PegBaseAddress + ExtendedCapOffset + 6,
          &Data16Or,  ///< Data to be ORed
          &Data16And  ///< Data to be ANDed
          );
        mDeviceMaxNoSnoopLatencySave [RootBridgeIndex][EndpointCompleted] = PciSegmentRead16 (PegBaseAddress + ExtendedCapOffset + 0x6);
      } else {
        DEBUG ((DEBUG_INFO, "LTR ExtCap structure not found on device [0x%08X]\n", PegBaseAddress));
      }
    }
  }
}

/**
  This function programs the LTR Override values
**/
VOID
PcieILtrOverride (
  VOID
  )
{
  UINT64_STRUCT  MchBar;
  UINT32         Data32And;
  UINT32         Data32Or;
  MchBar.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR + 4));
  MchBar.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  MchBar.Data       &= (UINT64) ~BIT0;
  Data32And          = 0x0;

  ///
  /// Configure Snoop Latency value
  ///
  if (mSnoopLatencyOvrValue != 0) {
    mSnoopLatencyOvrValue |= BIT14;
  }
  Data32Or = ((UINT32) (mSnoopLatencyOvrValue << 16));


  ///
  /// Configure Non-Snoop Latency value
  ///
  if (mNonSnoopLatencyOvrValue != 0) {
    mNonSnoopLatencyOvrValue |= BIT14;
  }
  Data32Or |= (UINT32) mNonSnoopLatencyOvrValue;

  ///
  /// Program ILTR_OVRD with latency values
  ///
  MmioAndThenOr32 (MchBar.Data + R_SA_MCHBAR_ILTR_OVRD_OFFSET, Data32And, Data32Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint32,
    (UINTN) (MchBar.Data + R_SA_MCHBAR_ILTR_OVRD_OFFSET),
    &Data32Or,  /// Data to be ORed
    &Data32And  /// Data to be ANDed
    );
}

/**
  This function enumerate devices to apply Peg Aspm settings.

  @param[in] RootBridgeIndex   - Root Bridge Index to select mDeviceCapMmBaseSave array elements for ASPM capability calculation.
  @param[in] AutoFlag          - ASPM AUTO calculation mode
  @param[in] RootPortAspm      - ASPM setting for Root port
  @param[in] EndPointAspm      - ASPM setting for End point
**/
VOID
PcieEnumerateDeviceToApplyASPM (
  IN UINT8      RootBridgeIndex,
  IN BOOLEAN    AutoFlag,
  IN UINT16     RootPortAspm,
  IN UINT16     EndPointAspm
  )
{
  UINT16  LinkAspmCap;
  UINT16  LinkAspmVal;
  UINT8   EndpointCompleted;
  UINT32  PegBaseAddress;
  UINT16  Data16Or;
  UINT16  Data16And;
  UINT32  DeviceCapabilities2;
  UINT8   PegFunc;

  PegFunc = (UINT8) ((mDeviceCapMmBaseSave [RootBridgeIndex][0] >> 12) & 0x07);
  if (PegFunc >= SA_PEG_MAX_FUN) {
    DEBUG ((DEBUG_ERROR, "PegFunc out of bound! Exit from PcieEnumerateDeviceToApplyASPM()!\n"));
    ASSERT (PegFunc < SA_PEG_MAX_FUN);
    return;
  }

  if (AutoFlag) {
    LinkAspmVal = PcieCalcAspmSettings (RootBridgeIndex);
    RootPortAspm = LinkAspmVal & 0xFF;
    EndPointAspm = LinkAspmVal & 0xFF;
    DEBUG ((DEBUG_INFO, "PcieCalcAspmSettings return ASPM value as: %x, apply on both RP and EP\n", RootPortAspm));
  }

  ///
  /// Apply to root port first
  ///
  PciSegmentAndThenOr16 (mDeviceCapMmBaseSave [RootBridgeIndex][0] + 0x010, (UINT16) ~3, RootPortAspm);
  DEBUG ((DEBUG_INFO, "Apply Aspm settings to Root [%X] to Aspm value: 0x%x\n", mDeviceCapMmBaseSave [RootBridgeIndex][0] + 0x010, RootPortAspm));
  ///
  /// Save register setting for S3 resume.
  ///
  mDeviceAspmSave [RootBridgeIndex][0] = PciSegmentRead8 (mDeviceCapMmBaseSave [RootBridgeIndex][0] + 0x010);
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    PcdGet64 (PcdSiPciExpressBaseAddress) + mDeviceCapMmBaseSave [RootBridgeIndex][0] + 0x010,
    1,
    &mDeviceAspmSave [RootBridgeIndex][0]
    );
  ///
  /// Apply Power Optimizer settings to PEG RootPoints.
  /// Read DCAP2 to see if LTR/OBFF is supported, program DCTL2 according to policies.
  ///
  PegBaseAddress = (UINT32) (mDeviceCapMmBaseSave [RootBridgeIndex][0] & (UINTN) ~0xFF);
  DeviceCapabilities2 = PciSegmentRead32 (PegBaseAddress + R_SA_PEG_DCAP2_OFFSET);
  Data16And           = (UINT16) ~(BIT10 + BIT13 + BIT14);
  Data16Or            = 0;

  if (DeviceCapabilities2 & BIT11) {
    if (mPegPwrOpt[PegFunc].LtrEnable == 1) {
      Data16Or |= BIT10;
    }
  }
  ///
  /// Check if root port support WAKE# signaling
  ///
  if ((DeviceCapabilities2 & BIT19) != 0) {
    if (mPegPwrOpt[PegFunc].ObffEnable == 1) {
      Data16Or |= BIT14 | BIT13; ///< 11b - Enable OBFF using WAKE#
    }
  }

  DEBUG ((DEBUG_INFO, "Configure LTR/OBFF setting to PEG root [0x%x] to value 0x%x\n",
          PegBaseAddress + R_SA_PEG_DCTL2_OFFSET, Data16Or));
  PciSegmentAndThenOr16 (PegBaseAddress + R_SA_PEG_DCTL2_OFFSET, Data16And, Data16Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint16,
    PcdGet64 (PcdSiPciExpressBaseAddress) + PegBaseAddress + R_SA_PEG_DCTL2_OFFSET,
    &Data16Or,
    &Data16And
    );
  mDeviceLtrObffSave [RootBridgeIndex][0] = PciSegmentRead16 (PegBaseAddress + R_SA_PEG_DCTL2_OFFSET);

  ///
  /// Apply to end point devices
  ///
  EndpointCompleted = 1;
  while (EndpointCompleted < mNumberOfDeviceFound [RootBridgeIndex]) {
    ///
    /// Read the Link Capability register's ASPM setting and apply ASPM setting to end point device
    ///
    LinkAspmCap = (PciSegmentRead16 (mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted] + 0x00C) >> 10) & 3;
    PciSegmentAndThenOr16 (mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted] + 0x010, (UINT16) ~3, EndPointAspm & LinkAspmCap);
    DEBUG ((DEBUG_INFO, "Apply Aspm settings to device [%X] to Aspm value: 0x%x and in fact set to 0x%x\n", mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted] + 0x10, EndPointAspm, EndPointAspm & LinkAspmCap));
    ///
    /// Save register setting for S3 resume.
    ///
    mDeviceAspmSave [RootBridgeIndex][EndpointCompleted] = PciSegmentRead8 (mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted] + 0x010);
    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint8,
      PcdGet64 (PcdSiPciExpressBaseAddress) + mDeviceCapMmBaseSave [RootBridgeIndex][EndpointCompleted] + 0x010,
      1,
      &mDeviceAspmSave [RootBridgeIndex][EndpointCompleted]
      );
    ///
    /// Power optimization on end point device
    ///
    PcieSetEndpointLtrObff (RootBridgeIndex, EndpointCompleted);
    EndpointCompleted ++;
  }
}

/**
  This function apply additional settings before ASPM enabling

  @param[in] RootBridgeIndex   - Root Bridge Index to select mDeviceCapMmBaseSave array elements for ASPM capability calculation.
**/
VOID
PcieAdditionalSettingBeforeASPM (
  IN UINT8      RootBridgeIndex
  )
{
  UINT32 Data32Or;
  UINT32 Data32And;

  if ((mPegAspmPerPort[RootBridgeIndex] != PcieAspmDisabled) && (mCommonClock [RootBridgeIndex] == 1)) {
    ///
    /// Enable support for L0s and L1 by programming the `Active State Link
    /// PM Support' field of the LCAP register at D.F.R 0ACh [11:10] = `11b'.
    ///
    PciSegmentOr32 ((mDeviceCapMmBaseSave[RootBridgeIndex][0] & (UINTN) ~0xFF) + 0x0AC, BIT11 | BIT10);
    Data32Or  = (BIT11 | BIT10);
    Data32And = (UINT32) ~(BIT11 | BIT10);
    S3BootScriptSaveMemReadWrite (
      S3BootScriptWidthUint32,
      PcdGet64 (PcdSiPciExpressBaseAddress) + (mDeviceCapMmBaseSave [RootBridgeIndex][0] & (UINT64) ~0xFF) + 0x0AC,
      &Data32Or,  ///< Data to be ORed
      &Data32And  ///< Data to be ANDed
      );

    ///
    /// Set D.F.R 0200h [27:26] to `00b'.
    ///
    PciSegmentAnd32 ((mDeviceCapMmBaseSave[RootBridgeIndex][0] & (UINTN) ~0xFF) + 0x200, (UINT32) ~(BIT27 | BIT26));
    Data32Or  = 0;
    Data32And = (UINT32) ~(BIT27 | BIT26);
    S3BootScriptSaveMemReadWrite (
      S3BootScriptWidthUint32,
      PcdGet64 (PcdSiPciExpressBaseAddress) + (mDeviceCapMmBaseSave [RootBridgeIndex][0] & (UINT64) ~0xFFu) + 0x200,
      &Data32Or,  ///< Data to be ORed
      &Data32And  ///< Data to be ANDed
      );

    ///
    /// Set D.F.R 0258 [2] to '1b' for PCI Express 2.0 compliance
    /// Note: Other fields within this register must not be changed
    /// while writing to D1.F0.R 0258h [2]
    ///
    PciSegmentOr16 ((mDeviceCapMmBaseSave [RootBridgeIndex][0] & (UINT64) ~0xFF) + R_SA_PEG_CFG4_OFFSET, BIT2);
    Data32Or  = BIT2;
    Data32And = (UINT32) ~(BIT2);
    S3BootScriptSaveMemReadWrite (
      S3BootScriptWidthUint32,
      PcdGet64 (PcdSiPciExpressBaseAddress) + (mDeviceCapMmBaseSave [RootBridgeIndex][0] & (UINT64) ~0xFF) + R_SA_PEG_CFG4_OFFSET,
      &Data32Or,  ///< Data to be ORed
      &Data32And  ///< Data to be ANDed
      );
  }
}

/**
  This function does all SA ASPM initialization
**/
VOID
SaAspm (
  VOID
  )
{
  BOOLEAN                         AutoFlag;
  UINT16                          RootPortAspm;
  UINT16                          EndPointAspm;
  UINT8                           PegComplete;
  CPU_PCIE_ASPM_CONFIG            PegAspmSetup;
  UINT8                           PegAspmL0sSetup;

  ///
  /// Scan PEG devices and program ASPM
  ///
  for (PegComplete = 0; PegComplete < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; PegComplete++) {
    if (mDeviceCapMmBaseSave [PegComplete][0] == 0) {
      continue;
    }
    PegAspmSetup      = mPegAspmPerPort[PegComplete];
    PegAspmL0sSetup   = mPegAspmL0sPerPort[PegComplete];
    RootPortAspm      = 0;
    EndPointAspm      = 0;
    AutoFlag          = FALSE;

    PcieAdditionalSettingBeforeASPM (PegComplete);
    DEBUG ((DEBUG_INFO, "PegAspmSetup[%x]=%x\n", PegComplete, PegAspmSetup));
    DEBUG ((DEBUG_INFO, "PegAspmL0sSetup[%x]=%x\n", PegComplete, PegAspmL0sSetup));
    if ((PegAspmSetup != PcieAspmDisabled) && (mCommonClock [PegComplete] == 1)) {
      ///
      /// Select L1/L0 programming based on setup questions
      ///
      switch (PegAspmSetup) {
        case PcieAspmL1:///<2
        case PcieAspmL0sL1:///<3
          RootPortAspm = L1_SET;
          EndPointAspm = L1_SET;

          ///
          /// If L1's only then break, else also program L0's
          ///
          if (PegAspmSetup == PcieAspmL1 ) {
            break;
          }
        case PcieAspmL0s:///<1
          RootPortAspm |= (PegAspmL0sSetup & L0_SET );
          EndPointAspm |= ((PegAspmL0sSetup >> 1 ) & L0_SET );
          break;
        case PcieAspmAutoConfig: ///<4
        case PcieAspmMax: ///<5
          AutoFlag = TRUE;
          break;
        case PcieAspmDisabled:
        default:
          break;
      }
    }
    DEBUG ((DEBUG_INFO, "RootPortAspm=%x\n", RootPortAspm ));
    DEBUG ((DEBUG_INFO, "EndPointAspm=%x\n", EndPointAspm ));
    PcieEnumerateDeviceToApplyASPM (PegComplete, AutoFlag, RootPortAspm, EndPointAspm);
  }
  ///
  /// Program override register with final latency values.
  ///
  PcieILtrOverride ();
  return;
}

/**
  This function checks PEG end point device for extended tag capability and enables them if they are.
**/
VOID
EnableExtendedTag (
  VOID
  )
{
  UINT8       RootBridgeCompleted;
  UINT8       EndpointCompleted;
  UINTN       RootPortPcieCapMmBase;
  UINTN       EndPointPcieCapMmBase;
  UINTN       PcieCapMmBase;

  ///
  /// Scan PEG devices
  ///
  for (RootBridgeCompleted = 0; RootBridgeCompleted < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; RootBridgeCompleted++) {
    RootPortPcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeCompleted][0];
    if (RootPortPcieCapMmBase == 0) {
      continue;
    }
    for (EndpointCompleted = 0; EndpointCompleted < mNumberOfDeviceFound [RootBridgeCompleted]; EndpointCompleted++) {
      if (EndpointCompleted != 0) {
        EndPointPcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeCompleted][EndpointCompleted];
        DEBUG ((DEBUG_INFO, "Extended tag scan End Point [B%X|D%X|F%X|R%X]\n",
                (EndPointPcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                (EndPointPcieCapMmBase >> 15)   & 0x1F,
                (EndPointPcieCapMmBase >> 12)   & 0x07,
                (EndPointPcieCapMmBase + 0x010) & 0xFFF));
        ///
        /// If extended tag is supported, enable it.
        ///
        if (((PciSegmentRead32 (EndPointPcieCapMmBase + 0x4)) & BIT5) != 0) {
          PciSegmentOr16 (EndPointPcieCapMmBase + 0x8, BIT8);
          DEBUG ((DEBUG_INFO, "Extended tag enabled [B%X|D%X|F%X|R%X]\n",
                  (EndPointPcieCapMmBase >> 20)   & mMaxBusNumberSupported,
                  (EndPointPcieCapMmBase >> 15)   & 0x1F,
                  (EndPointPcieCapMmBase >> 12)   & 0x07,
                  (EndPointPcieCapMmBase + 0x010) & 0xFFF));
        }
      }
      ///
      /// Save Device Control Register value on all bridges and devices for S3 resume
      ///
      PcieCapMmBase = mDeviceCapMmBaseSave [RootBridgeCompleted][EndpointCompleted];
      mDeviceControlRegisterSave [RootBridgeCompleted][EndpointCompleted] = PciSegmentRead16 (PcieCapMmBase + 0x8);
      S3BootScriptSaveMemWrite (
        S3BootScriptWidthUint16,
        PcdGet64 (PcdSiPciExpressBaseAddress) + PcieCapMmBase + 0x8,
        1,
        &mDeviceControlRegisterSave [RootBridgeCompleted][EndpointCompleted]
        );
    }
  }
  return;
}

/**
  This function saves/restores Chipset registers

  @param[in] IsSaving                  - TRUE for saving and FALSE for restoring
  @param[in] PciRegistersSaveTable[]   - The register table that has to be saved/restored
  @param[in] PciRegistersSaveTableSize - Size of above table
  @param[in] PciRegistersSaveBuffer    - A saving/restoring buffer for those register settings.
**/
VOID
SaSaveRestoreChipset (
  IN     BOOLEAN                       IsSaving,
  IN     BOOT_SCRIPT_PCI_REGISTER_SAVE PciRegistersSaveTable[],
  IN     UINTN                         PciRegistersSaveTableSize,
  IN OUT UINTN                         *PciRegistersSaveBuffer
  )
{
  UINT8    Index;

  if (IsSaving == TRUE) {
    DEBUG ((DEBUG_INFO, "SA Save PCI register settings\n"));
    ///
    /// Save SA PCI Registers for S3 resume
    ///
    for (Index = 0; Index < PciRegistersSaveTableSize; Index++) {
      PciRegistersSaveBuffer[Index] = PciSegmentRead32 (PciRegistersSaveTable[Index].Address);
      S3BootScriptSaveMemWrite (
        S3BootScriptWidthUint32,
        PcdGet64 (PcdSiPciExpressBaseAddress) + PciRegistersSaveTable[Index].Address,
        1,
        &PciRegistersSaveBuffer[Index]
        );
      DEBUG ((DEBUG_INFO, "SA Register = %X, SaPciRegSave = %08X\n", PciRegistersSaveTable[Index].Address, PciRegistersSaveBuffer[Index]));
    }
  } else {
    DEBUG ((DEBUG_INFO, "SA Restore PCI register settings\n"));
    ///
    /// Restore SA PCI Registers for S3 resume
    ///
    for (Index = 0; Index < PciRegistersSaveTableSize; Index++) {
      PciSegmentWrite32 (PciRegistersSaveTable[Index].Address, (UINT32) PciRegistersSaveBuffer[Index]);
      DEBUG ((DEBUG_INFO, "SA Register = %X, SaPciRegSave = %08X\n", PciRegistersSaveTable[Index].Address, PciRegistersSaveBuffer[Index]));
    }
  }
}

/**
  This function saves/restores platform relative registers

  @param[in] IsSaving                  - TRUE for saving and FALSE for restoring
**/
VOID
SaSaveRestorePlatform (
  IN BOOLEAN        IsSaving
  )
{
  UINTN    McBaseAddress;
  UINT8    Index;

  ///
  /// Save (or restore) IGFX registers
  /// When saving, it has to be done after all BAR/Command registers have been assigned.
  ///
  if (PciSegmentRead16 ( PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_VENDOR_ID_OFFSET)) != 0xFFFF) {
    SaSaveRestoreChipset (IsSaving, mSaIgfxPciRegistersSaveTable, sizeof (mSaIgfxPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE), mSaIgfxPciRegistersSave);
  }

  McBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  if (IsSaving == TRUE) {
    DEBUG ((DEBUG_INFO, "SA Save platform register settings\n"));
    ///
    /// Save PAM register
    ///
    for (Index = 0; Index < MAX_PAM_REG_COUNT; Index++) {
      mPAMSave[Index] = PciSegmentRead8 (McBaseAddress + (PAM_REG_BASE + Index));
      S3BootScriptSaveMemWrite (
        S3BootScriptWidthUint8,
        PcdGet64 (PcdSiPciExpressBaseAddress) + McBaseAddress + (PAM_REG_BASE + Index),
        1,
        &mPAMSave[Index]
        );
    }
  } else {
    DEBUG ((DEBUG_INFO, "SA Restore platform register settings\n"));
    ///
    /// Restore PAM register
    ///
    for (Index = 0; Index < MAX_PAM_REG_COUNT; Index++) {
      PciSegmentWrite8 (McBaseAddress + (PAM_REG_BASE + Index), mPAMSave [Index]);
    }
  }

}

/**
  This function handles SA S3 resume
**/
VOID
SaS3Resume (
  VOID
  )
{
  UINT8                           PegComplete;
  UINT8                           EndpointCompleted;
  UINT32                          PegBaseAddress;

  DEBUG ((DEBUG_INFO, "SA S3 resume\n"));
  if (mEnumStatus == EFI_SUCCESS) {
    ///
    /// Restore Bus number assignment first
    ///
    for (PegComplete = 0; PegComplete < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; PegComplete++) {
      if (mDeviceCapMmBaseSave [PegComplete][0] == 0) {
        continue;
      }
      EndpointCompleted = 0;
      while (EndpointCompleted < mNumberOfDeviceFound [PegComplete]) {
        PegBaseAddress = (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] & (UINTN) ~0xFF);
        PciSegmentWrite32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, mDeviceBusNumberSave [PegComplete][EndpointCompleted]);
        DEBUG ((DEBUG_INFO, " Restore Bus number [%X] = %08X\n", PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, PciSegmentRead32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET)));
        EndpointCompleted ++;
      }
    }
    for (PegComplete = 0; PegComplete < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; PegComplete++) {
      if (mDeviceCapMmBaseSave [PegComplete][0] == 0) {
        continue;
      }
      PcieAdditionalSettingBeforeASPM (PegComplete);
      EndpointCompleted = 0;
      while (EndpointCompleted < mNumberOfDeviceFound [PegComplete]) {
        PegBaseAddress = (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] & (UINTN) ~0xFF);
        ///
        /// Restore Max Pay Load and Extended Tag
        ///
        PciSegmentWrite16 (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x8, mDeviceControlRegisterSave [PegComplete][EndpointCompleted]);
        DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] DCTL=%X\n",
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 20)  & mMaxBusNumberSupported,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 15)  & 0x1F,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 12)  & 0x07,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x08) & 0xFFF,
                mDeviceControlRegisterSave [PegComplete][EndpointCompleted]));
        ///
        /// Restore ASPM and Common Clock
        ///
        PciSegmentWrite8 ((mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x010), mDeviceAspmSave [PegComplete][EndpointCompleted]);
        DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] ASPM/CommonClock=%X\n",
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 20)  & mMaxBusNumberSupported,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 15)  & 0x1F,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 12)  & 0x07,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x10) & 0xFFF,
                mDeviceAspmSave [PegComplete][EndpointCompleted]));
        ///
        /// Restore PEG power optimization.
        ///
        PciSegmentAndThenOr16 (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x28, (UINT16) ~(BIT10 + BIT13 + BIT14), mDeviceLtrObffSave [PegComplete][EndpointCompleted]);
        DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] LTR/OBFF=%X\n",
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 20)  & mMaxBusNumberSupported,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 15)  & 0x1F,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] >> 12)  & 0x07,
                (mDeviceCapMmBaseSave [PegComplete][EndpointCompleted] + 0x28) & 0xFFF,
                mDeviceLtrObffSave [PegComplete][EndpointCompleted]));

        if (mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] != 0) {
          PciSegmentAndThenOr16 (PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] + 0x4, (UINT16) (~0x1FFF), mDeviceMaxSnoopLatencySave [PegComplete][EndpointCompleted]);
          DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] Max snoop latency=%X\n",
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 20)  & mMaxBusNumberSupported,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 15)  & 0x1F,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 12)  & 0x07,
                  (PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] + 0x4) & 0xFFF,
                  mDeviceMaxSnoopLatencySave [PegComplete][EndpointCompleted]));

          PciSegmentAndThenOr16 ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] + 0x6), (UINT16) (~0x1FFF), mDeviceMaxNoSnoopLatencySave [PegComplete][EndpointCompleted]);
          DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] Max No-snoop latency=%X\n",
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 20)  & mMaxBusNumberSupported,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 15)  & 0x1F,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 12)  & 0x07,
                  (PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] + 0x6) & 0xFFF,
                  mDeviceMaxNoSnoopLatencySave [PegComplete][EndpointCompleted]));
        }
        if (mDeviceExtCapVcOffsetSave [PegComplete][EndpointCompleted]) {
          PciSegmentAndThenOr8 ((mDeviceExtCapVcOffsetSave [PegComplete][EndpointCompleted] + 0x14), 0, mDeviceTcxVc0MappingSave [PegComplete][EndpointCompleted]);
          DEBUG ((DEBUG_INFO, "[B%X|D%X|F%X|R%X] TCx/VC0 mapping=%X\n",
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 20)  & mMaxBusNumberSupported,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 15)  & 0x1F,
                  ((PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted]) >> 12)  & 0x07,
                  (PegBaseAddress + mDeviceExtCapLtrOffsetSave [PegComplete][EndpointCompleted] + 0x14) & 0xFFF,
                  mDeviceTcxVc0MappingSave [PegComplete][EndpointCompleted]));
        }
        EndpointCompleted ++;
      }
      ///
      /// If common clock supported on root port and endpoint, retrain link
      ///
      if (mCommonClock [PegComplete] == 1) {
        DEBUG ((DEBUG_INFO, "Retrain Link for Common Clock\n"));
        ///
        /// Retrain the Link per PCI Express Specification.
        ///
        PciSegmentOr8 (mDeviceCapMmBaseSave [PegComplete][0] + 0x010, BIT5);

        ///
        /// Wait until Re-Training has completed.
        ///
        while ((PciSegmentRead16 (mDeviceCapMmBaseSave [PegComplete][0] + 0x012) & BIT11) != 0) {
        }
      }
    }
  }
  ///
  /// Re-do this during S3 resume
  ///
  PcieILtrOverride ();
}

/**
  Wrapper function for all SA S3 resume tasks which can be a callback function.
**/
VOID
SaS3ResumeCallback (
  VOID
  )
{
  SaS3Resume ();
  SaSaveRestoreChipset (FALSE, mSaChipsetPciRegistersSaveTable, sizeof (mSaChipsetPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE), mSaChipsetPciRegistersSave);
  SaSaveRestorePlatform (FALSE);
}

/**
  Wrapper function for all SA ASPM tasks and extended tag which can be a callback function.
**/
VOID
CpuPcieConfigAfterOpRom (
  VOID
  )
{

  DEBUG ((DEBUG_INFO, "SA ASPM\n"));
  if (mEnumStatus == EFI_SUCCESS) {
    SaAspm ();
    ///
    /// Device Control Register on all endpoint devices is saved after the OpRom has run in EnableExtendedTag (DXE phase will still use ExitPmAuth)
    /// This is to prevent duplication of saving this register in different phases.
    ///
    EnableExtendedTag ();
  }
}

/**
  Wrapper function for all SA enumeration tasks which can be a callback function.
**/
VOID
CpuPcieEnumCallback (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "SA PCIe enumeration\n"));
  ///
  /// Expected to execute in ExitPmAuth point (before OROM)
  ///
  mEnumStatus = EnumerateAllPcieDevices ();
  if (mEnumStatus == EFI_SUCCESS) {
    CpuPcieConfigBeforeOpRom ();
  }
  ///
  /// Save Chipset registers
  ///
  SaSaveRestoreChipset (TRUE, mSaChipsetPciRegistersSaveTable, sizeof (mSaChipsetPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE), mSaChipsetPciRegistersSave);
}

/**
  This function will initialize all required policy into global veriables so no need to locate policy protocol during runtime.
**/
VOID
CpuPcieInitPolicy (
  IN SA_POLICY_PROTOCOL *SaPolicy
  )
{
  UINT8                   RootPortCount;
  UINT8                   Index;
  SA_CONFIG_HOB           *SaConfigHob;
  EFI_STATUS              Status;
  PCIE_DXE_CONFIG         *PcieDxeConfig;

  Status = GetConfigBlock ((VOID *) SaPolicy, &gPcieDxeConfigGuid, (VOID *)&PcieDxeConfig);
  ASSERT_EFI_ERROR (Status);

  SaConfigHob = NULL;

  SaConfigHob = GetFirstGuidHob (&gSaConfigHobGuid);
  ///
  /// Initialize module global variables - Stepping ID and Policy
  ///
  for (Index = 0; (Index < (sizeof (mSaChipsetPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE))) && (Index < (sizeof (mSaChipsetPciRegistersTable) / sizeof (UINTN))); Index++) {
    mSaChipsetPciRegistersSaveTable[Index].Address = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, mSaChipsetPciRegistersTable[Index]);
  }

  for (Index = 0; (Index < (sizeof (mSaIgfxPciRegistersSaveTable) / sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE))) && (Index < (sizeof (mSaIgfxPciRegistersTable) / sizeof (UINTN))); Index++) {
    mSaIgfxPciRegistersSaveTable[Index].Address = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, mSaIgfxPciRegistersTable[Index]);
  }

  for (RootPortCount = 0; RootPortCount < MAX_SUPPORTED_ROOT_BRIDGE_NUMBER; RootPortCount++) {
    mPegAspmPerPort[RootPortCount]    = PcieDxeConfig->PegAspm[RootPortCount];
    mPegAspmL0sPerPort[RootPortCount] = PcieDxeConfig->PegAspmL0s[RootPortCount];
    mPegPwrOpt[RootPortCount]         = PcieDxeConfig->PegPwrOpt[RootPortCount];
  }
  mPcieAspmDevsOverride = PcieDxeConfig->PcieAspmDevsOverride;
  mPcieLtrDevsOverride  = PcieDxeConfig->PcieLtrDevsOverride;

  mCridEnable = SaConfigHob->CridEnable;


  ///
  /// Initialize Snoop and Non-Snoop Latencies
  ///
  mSnoopLatencyOvrValue        = 0;
  mNonSnoopLatencyOvrValue     = 0;

}
