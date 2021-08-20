/** @file
 Routines for Rst remapping

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/SataLib.h>
#include <Library/PeiRstPrivateLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Library/PsfLib.h>
#include <PchPcieStorageDetectHob.h>
#include <PchRstHob.h>
#include <Library/HobLib.h>
#include <Library/PchPolicyLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiSataLib.h>
#include <Library/PeiRstPolicyLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PchInfoLib.h>
#include <Library/RstCrLib.h>
#include <Register/PchRegs.h>
#include <PcieRegs.h>
#include <Register/SataRegs.h>
#include <PchPcieRpInfo.h>
#include <Register/PchPcieRpRegs.h>
#include <Library/PcieHelperLib.h>

#define RST_PCIE_STORAGE_INTERFACE_NONE 0
#define RST_PCIE_STORAGE_INTERFACE_AHCI 1
#define RST_PCIE_STORAGE_INTERFACE_NVME 2

#define RST_STONY_BEACH_VENDOR_ID       0x8086
#define RST_STONY_BEACH_DEVICE_ID       0x2522

#define RST_TETON_GLACIER_VENDOR_ID     0x8086
#define RST_TETON_GLACIER_DEVICE_ID     0x0975

#define PCI_CLASS_MASS_STORAGE_NVME     0x08
#define PCI_CLASS_MASS_STORAGE_AHCI     PCI_CLASS_MASS_STORAGE_SATADPA

//
// Variables below indicate the memory range to be allocated to the PCIe storage device BAR usage when it is HIDDEN,
// thus it does not overlapped with the SGREG_BAR from the host perspective
//
#define PCI_CARD_PM_CAP_ID              0x01
#define PCI_CARD_MSIX_CAP_ID            0x11
#define PCI_CARD_SATA_CAP_ID            0x12
#define PCI_CARD_BAR_TOTAL              6
#define PCI_CARD_LINK_SPEED_GEN1_GEN2   0
#define PCI_CARD_LINK_SPEED_GEN3        1
#define PCI_CARD_LINK_WIDTH_1           0
#define PCI_CARD_LINK_WIDTH_2           1
#define PCI_CARD_LINK_WIDTH_4           2

#define RST_PCIE_STORAGE_MEMORY_START_RANGE         PCH_PCR_BASE_ADDRESS
#define RST_PCIE_STORAGE_MEMORY_END_RANGE           (PCH_PCR_BASE_ADDRESS + PCH_PCR_MMIO_SIZE - 1)

typedef struct {
  UINT8  BaseClassCode;
  UINT8  SubClassCode;
  UINT8  ProgrammingInterface;
} PCI_CLASS_CODE;

typedef struct {
  BOOLEAN  MsixSupported;
  UINT16   StartingVector;
  UINT16   EndingVector;
  UINT32   EndPointUniqueMsixTableBar;       // Records the PCIe storage device's MSI-X Table BAR if it supports unique MSI-X Table BAR
  UINT32   EndPointUniqueMsixTableBarValue;  // Records the PCIe storage device's MSI-X Table BAR value if it supports unique MSI-X Table BAR
  UINT32   EndPointUniqueMsixPbaBar;         // Records the PCIe storage device's MSI-X PBA BAR if it supports unique MSI-X PBA BAR
  UINT32   EndPointUniqueMsixPbaBarValue;    // Records the PCIe storage device's MSI-X PBA BAR value if it supports unique MSI-X PBA BAR
} CR_MSIX_CONFIG;

typedef struct {
  BOOLEAN         RemappingSupported;
  UINT8           RootPortNumber;
  UINT8           RootPortLaneMask;
  UINT32          EndPointBarSize;
  PCI_CLASS_CODE  ClassCode;
  CR_MSIX_CONFIG  MsixConfig;
} RST_CR_CONFIG;

typedef struct {
  PCI_CLASS_CODE  StorageClassCode;
  RST_LINK_WIDTH  StorageLinkWidth;
} RST_PCIE_STORAGE_MAP;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_PCIE_CONFIG                *mPcieRpConfig;
GLOBAL_REMOVE_IF_UNREFERENCED RST_CR_CONFIG                  mRstCrConfig[PCH_MAX_RST_PCIE_STORAGE_CR];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                          mCycleRouterMap[PCH_MAX_PCIE_CONTROLLERS];
GLOBAL_REMOVE_IF_UNREFERENCED RST_PCIE_STORAGE_MAP           mPcieStorageMap[PCH_MAX_PCIE_ROOT_PORTS];
GLOBAL_REMOVE_IF_UNREFERENCED SAVED_DEVICE_CONFIG_SPACE      mSavedConfigSpace[PCH_MAX_RST_PCIE_STORAGE_CR];

UINT32 PchRstPcieStorageCurrentMemoryRange = RST_PCIE_STORAGE_MEMORY_START_RANGE;

/**
  Checks if given cycle router is in fuse enabled state

  @param[in]  CrNumber         Cycle Router Number
  @param[in]  SataRegBase      Sata Pci Segment Base

  @retval BOOLEAN              TRUE if CR is fuse enabled
**/
STATIC
BOOLEAN
RstIsCrFuseEnabled (
  IN  UINT8                    CrNumber,
  IN  UINT64                   SataRegBase
  )
{
  if (PciSegmentRead32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_FDW0) & (BIT4 << CrNumber)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Get root port base address for a given root port

  @param[in] RpNumber  Root port number

  @retval  UINT64  Root port base address
**/
STATIC
UINT64
RstGetRpBaseAddress (
  IN UINT8  RpNumber
  )
{
  UINTN       RpDevice;
  UINTN       RpFunction;
  EFI_STATUS  Status;

  Status = GetPchPcieRpDevFun (RpNumber, &RpDevice, &RpFunction);
  ASSERT_EFI_ERROR (Status);
  return PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, (UINT32) RpDevice, (UINT32) RpFunction, 0);
}

/**
  Sets temporary bus number for a given root port
  Functions operating on end point PCIe config space require this function to be called first

  @param[in] RpNumber    Root port number
  @param[in] TempPciBus  Temporary PCI bus number
**/
STATIC
UINT64
RstSetRpTempBusNumberAndGetEpBaseAddress (
  IN UINT8   RpNumber,
  IN UINT32  TempPciBus
  )
{
  UINT64  RpBase;
  UINT64  EpBase;

  RpBase = RstGetRpBaseAddress (RpNumber);

  PciSegmentAndThenOr32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN,
    ((UINT32) (TempPciBus << 8)) | ((UINT32) (TempPciBus << 16))
    );

  //
  // A config write is required in order for the device to re-capture the Bus number,
  // according to PCI Express Base Specification, 2.2.6.2
  // Write to a read-only register VendorID to not cause any side effects.
  //
  EpBase  = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, 0, 0);
  PciSegmentWrite16 (EpBase + PCI_VENDOR_ID_OFFSET, 0);

  return EpBase;

}

/**
  Clears primary bus register of a given root port

  @param[in] RpNumber  Root port number
**/
STATIC
VOID
RstClearRpTempBusNumber (
  IN UINT8  RpNumber
  )
{
  UINT64  RpBase;

  RpBase = RstGetRpBaseAddress (RpNumber);

  //
  // Clear temporary bus number
  //
  PciSegmentAnd32 (RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN);
}

/**
  Checks if given root port has been disabled

  @param[in] RpNumber  Root port number

  @retval  BOOLEAN  True if root port is disabled
**/
STATIC
BOOLEAN
RstIsRpDisabled (
  IN UINT8  RpNumber
  )
{
  UINT64  RpBase;

  RpBase = RstGetRpBaseAddress (RpNumber);

  if (PciSegmentRead16 (RpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Checks if end point device is present on given root port
  This function requires earlier call to RstSetRpTempBusNumber

  @param[in]  RpNumber   Root port number
  @param[in]  TempPciBus Temporary PCI Bus number

  @retval BOOLEAN  True if device present on root port
**/
STATIC
BOOLEAN
RstIsEndPointPresent (
  IN UINT8   RpNumber,
  IN UINT32  TempPciBus
  )
{
  UINT64  EpBase;

  EpBase = RstSetRpTempBusNumberAndGetEpBaseAddress (RpNumber, TempPciBus);

  if (PciSegmentRead16 (EpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF ) {
    RstClearRpTempBusNumber (RpNumber);
    return FALSE;
  } else {
    RstClearRpTempBusNumber (RpNumber);
    return TRUE;
  }

}

/**
  Returns a Pci class code of an end point device connected to a given Root port

  @param[in]  RpNumber    Root port number
  @param[in]  TempPciBus  Temporary PCI Bus number
  @param[out] ClassCode   Pci class code of a connected device
**/
STATIC
VOID
RstGetDeviceClassCode (
  IN UINT8            RpNumber,
  IN UINT32           TempPciBus,
  OUT PCI_CLASS_CODE  *ClassCode
  )
{
  UINT64          EpBase;

  EpBase = RstSetRpTempBusNumberAndGetEpBaseAddress (RpNumber, TempPciBus);

  ClassCode->BaseClassCode = PciSegmentRead8 (EpBase + R_PCI_BCC_OFFSET);
  ClassCode->SubClassCode = PciSegmentRead8 (EpBase + R_PCI_SCC_OFFSET);
  ClassCode->ProgrammingInterface = PciSegmentRead8 (EpBase + R_PCI_PI_OFFSET);

  RstClearRpTempBusNumber (RpNumber);

}

/**
  Checks if device with given PCI config space address is Intel's Teton Glacier.

  @param[in]  RpNumber   Root port number
  @param[in]  TempPciBus Temporary PCI Bus number

  @retval BOOLEAN        TRUE if device is Intel's Teton Glacier, FALSE otherwise
**/
STATIC
BOOLEAN
RstIsTetonGlacier (
  IN UINT8            RpNumber,
  IN UINT32           TempPciBus
  )
{
  UINT16              DeviceVendorId;
  UINT16              DeviceDeviceId;
  UINT64              EpBase;

  EpBase = RstSetRpTempBusNumberAndGetEpBaseAddress (RpNumber, TempPciBus);

  DeviceVendorId = PciSegmentRead16 (EpBase + PCI_VENDOR_ID_OFFSET);
  DeviceDeviceId = PciSegmentRead16 (EpBase + PCI_DEVICE_ID_OFFSET);

  RstClearRpTempBusNumber (RpNumber);

  if (DeviceVendorId == RST_TETON_GLACIER_VENDOR_ID && DeviceDeviceId == RST_TETON_GLACIER_DEVICE_ID) {
    return TRUE;
  }

  return FALSE;
}

/**
  Check the lane occupied by certain root port according to the root port number and configuration strap
  Return 8-bit bitmap where each bit represents the lane number (e.g.: return 00000011b means the root port owns 2 lane)

  @param[in] RootPortNum            Root Port Number

  @retval UINT8                     Lane Occupied by the Root Port (bitmap)
**/
STATIC
UINT8
RstGetRpLaneOccupyMask (
  IN  UINT32                   RootPortNum
  )
{
  EFI_STATUS              Status;
  UINT32                  CtrlNum;
  UINT32                  CtrlFirstRpNum;
  UINT32                  Data32;
  UINT8                   LaneOccupied;

  LaneOccupied          = 0;

  CtrlNum = GetControllerIndex (RootPortNum);
  CtrlFirstRpNum = GetControllerFirstRpIndex (CtrlNum);

  //
  // Read the Root Port Configuration Straps for the link width, and return LaneOccupied by the Root Port accordingly
  //
  Status = PchSbiRpPciRead32 (CtrlFirstRpNum, R_PCH_PCIE_CFG_STRPFUSECFG, &Data32);
  if (Status != EFI_SUCCESS) {
    return LaneOccupied;
  } else {
    switch ((Data32 & B_PCH_PCIE_CFG_STRPFUSECFG_RPC) >> N_PCH_PCIE_CFG_STRPFUSECFG_RPC) {
      case V_PCH_PCIE_CFG_STRPFUSECFG_RPC_4:
        if (RootPortNum % 4 == 0) {
          LaneOccupied = (BIT3|BIT2|BIT1|BIT0);
        }
        break;
      case V_PCH_PCIE_CFG_STRPFUSECFG_RPC_2_2:
        if ((RootPortNum % 2 == 0)) {
          LaneOccupied = (BIT1|BIT0);
        }
        break;
      case V_PCH_PCIE_CFG_STRPFUSECFG_RPC_2_1_1:
        if (RootPortNum % 4 == 0) {
          LaneOccupied = (BIT1|BIT0);
        } else if (RootPortNum % 4 != 1) {
          LaneOccupied = BIT0;
        }
        break;
      case V_PCH_PCIE_CFG_STRPFUSECFG_RPC_1_1_1_1:
        LaneOccupied = BIT0;
        break;
      default:
        break;
    }

    return LaneOccupied;
  }
}

/**
  Checks PCH generation and returns SATA's GCR.PLS bit number according to root port number with a PCIe storage device
  connected to.

  @param[in] RootPortNum        Root port number which PCIe storage device is connected to

  @retval UINT32                Number of GCR.PLS bit representing root port
**/
STATIC
UINT32
RstPlsBitNumber (
  IN UINT32           RootPortNum
  )
{
  ASSERT (RootPortNum < GetPchMaxPciePortNum ());

  if (IsPchH () && RstGetCycleRouterNumber (RootPortNum) == RST_PCIE_STORAGE_CR_2) {
    return RootPortNum - 2 * PCH_PCIE_CONTROLLER_PORTS;
  } else {
    return RootPortNum;
  }
}

/**
  Checks if device with given PCI config space address is Intel's Stony Beach.

  @param[in] EndPointPciBase    Address of device's PCI config space

  @retval BOOLEAN               TRUE if device is Intel's Stony Beach, FALSE otherwise
**/
STATIC
BOOLEAN
RstIsStonyBeach (
  IN UINT64  EndPointPciBase
  )
{
  UINT16              DeviceVendorId;
  UINT16              DeviceDeviceId;

  DeviceVendorId = PciSegmentRead16 (EndPointPciBase + PCI_VENDOR_ID_OFFSET);
  DeviceDeviceId = PciSegmentRead16 (EndPointPciBase + PCI_DEVICE_ID_OFFSET);

  if (DeviceVendorId == RST_STONY_BEACH_VENDOR_ID && DeviceDeviceId == RST_STONY_BEACH_DEVICE_ID) {
    return TRUE;
  }

  return FALSE;
}

/**
  Check if given cycle router number is supported in the silicon

  @param[in] CrNumber  Cycle router number(0-based)

  @retval TRUE   Cycle router is supported in the silicon
  @retval FALSE  Cycle router is unsupported
**/
STATIC
BOOLEAN
RstIsCycleRouterValid (
  IN UINT8  CrNumber
  )
{
  if ((CrNumber == 0) && (IsPchLp ())) {
    return FALSE;
  }

  if (CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR) {
    return TRUE;
  }

  return FALSE;
}

/**
  Configure access to given cycle router memory space

  @param[in] SataRegBase  SATA Register Base
  @param[in] CrNumber     The RST PCIe Storage Cycle Router number

  @retval TRUE  CrNumber has been set sucessfully
  @retval FALSE Failed to set CrNumber programming is not safe
**/
STATIC
BOOLEAN
RstSetCycleRouter (
  IN UINT64            SataRegBase,
  IN UINT8             CrNumber
  )
{
  if (RstIsCycleRouterValid (CrNumber)) {
    PciSegmentWrite8 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CRGC, (UINT8) CrNumber);
    return TRUE;
  }

  return FALSE;
}

/**
  Verify Cycle router strap configuration matches corresponding PCIe controller strap
  configuration.

  @param[in] RootPortLane  Root port lane number
  @param[in] PortNum       Root Port Number
  @param[in] SataRegBase   Sata Controller Pci segment base

  @retval  TRUE   Straps configuration for given cycle router is valid
  @retval  FALSE  Straps configuration for given cycle router is invalid
**/
STATIC
BOOLEAN
RstIsRemapConfigValid (
  IN  UINT8        RootPortLane,
  IN  UINT32       PortNum,
  IN  UINT64       SataRegBase
  )
{
  UINT32    PortConfigurationCheck;
  UINT8     CycleRouterNum;

  CycleRouterNum = RstGetCycleRouterNumber (PortNum);

  if (RstSetCycleRouter (SataRegBase, CycleRouterNum)) {
    //
    // Check for mismatching configuration
    // Set "PCIe Lane Selected (PLS)" Bit[RP#], Sata PCI offset 300h[RP#] to 1
    //
    PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_GCR_PLS), (UINT32) RootPortLane << (RstPlsBitNumber (PortNum) + 1));

    //
    // Clear PCCS, Sata PCI offset 304h [30], then read the value of PCCS
    //
    PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GSR, (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_GSR_PCCS);
    PortConfigurationCheck = PciSegmentRead32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GSR) & (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_GSR_PCCS;

    //
    // Clear "PCIe Lane Selected (PLS)", Sata PCI offset 300h [20:1] to 0
    //
    PciSegmentAnd32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_GCR_PLS));

    //
    // If PCCS value is 1, a mismatch configuration has occurred
    //
    if (PortConfigurationCheck) {
      return FALSE;
    } else {
      return TRUE;
    }
  } else {
    ASSERT (FALSE);
    return FALSE;
  }
}

/**
  Pools Pcie link layer status untill condition is met or timeout exceeded

  @param[in] PollForLinkActive      Set to TRUE if polling should be for link active
  @param[in] TimeoutLimitUs         Timeout limit in microseconds
  @param[in] StatusRegisterAddress  Address of a status register
**/
STATIC
VOID
RstPollPcieLinkStateUntil (
  IN BOOLEAN  PollForLinkActive,
  IN UINT32   TimeoutLimitUs,
  IN UINT64   StatusRegisterAddress
  )
{
  UINT32   Timeout;
  UINT16   Data16;
  BOOLEAN  LinkActive;

  Timeout = 0;

  do {
    Data16 = PciSegmentRead16 (StatusRegisterAddress) & B_PCIE_LSTS_LA;
    if (Data16 == 0) {
      LinkActive = FALSE;
    } else {
      LinkActive = TRUE;
    }
    if (Timeout > TimeoutLimitUs) {
      DEBUG ((DEBUG_INFO, "PollLinkState: Timeout (exceed %d us) while polling for link %a\n", TimeoutLimitUs, PollForLinkActive ? "active" : "down"));
      break;
    }
    MicroSecondDelay (15);
    Timeout += 15;
  } while (LinkActive != PollForLinkActive);

}

/**
  Checks if class code defines a remap capable device

  @param[in] ClassCode  Class code to check

  @retval TRUE   If class code defines a remappable device
  @retval FALSE  Otherwise
**/
STATIC
BOOLEAN
RstIsDeviceRemapCapablePcieStorage (
  IN PCI_CLASS_CODE  ClassCode
  )
{
  BOOLEAN  RemapCapableDevice;

  RemapCapableDevice = FALSE;

  if (ClassCode.BaseClassCode == PCI_CLASS_MASS_STORAGE) {

    switch (ClassCode.SubClassCode) {
      case PCI_CLASS_MASS_STORAGE_AHCI:
        if (ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_AHCI) {
          RemapCapableDevice = TRUE;
        }
        break;
      case PCI_CLASS_MASS_STORAGE_NVME:
        if (ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_NVME) {
          RemapCapableDevice = TRUE;
        }
        break;
      case PCI_CLASS_MASS_STORAGE_RAID:
        RemapCapableDevice = TRUE;
        break;
      default:
        RemapCapableDevice = FALSE;
    }
  }

  return RemapCapableDevice;
}

/**
  Creates cycle router map (maps cycle router number to PCIe controller number)

  @param[in]  SataRegBase  Sata register base
  @param[out] CrMap        Pointer to cycle router map
**/
STATIC
VOID
RstCreateCycleRouterMap (
   IN   UINT64          SataRegBase,
   OUT  UINT8          *CrMap
  )
{
  UINT8                 Index;
  UINT8                 CtrlIndexMax;
  UINT8                 CycleRouterNum;

  CtrlIndexMax = GetPchMaxPcieControllerNum ();
  for (Index = 0; Index < CtrlIndexMax; Index++) {
    CycleRouterNum = RstGetCycleRouterNumber (4 * Index);
    if (CycleRouterNum == RST_PCIE_STORAGE_CR_INVALID || !RstIsCrFuseEnabled (CycleRouterNum, SataRegBase)) {
      CrMap[Index] = RST_PCIE_STORAGE_CR_INVALID;
    } else {
      CrMap[Index] = (UINT8) CycleRouterNum;
    }
    DEBUG ((DEBUG_INFO, "CrMap[%d] = %d\n", Index, CrMap[Index]));
  }

}

/**
  Detects PCIe storage devices connected to root ports

  @param[in] SataRegBase Sata register base
  @param[in] TempPciBus  Temporary Pci bus
**/
STATIC
VOID
RstDetectPcieStorageDevices (
  IN UINT64  SataRegBase,
  IN UINT8   TempPciBus
  )
{
  UINT8                        RpIndex;
  UINT8                        CurrentRpIndex;
  UINT8                        MaxPcieRootPorts;
  UINT8                        LanesOccupied;
  PCI_CLASS_CODE               ClassCode;

  DEBUG((DEBUG_INFO, "RstDetectPcieStorageDevices() Start\n"));

  MaxPcieRootPorts = GetPchMaxPciePortNum ();

  for (RpIndex = 0; RpIndex < MaxPcieRootPorts; RpIndex++) {

    CurrentRpIndex = RpIndex;

    if (RstIsRpDisabled (CurrentRpIndex)) {
      DEBUG ((DEBUG_INFO, "Rp#%d is disabled\n", CurrentRpIndex));
      continue;
    }

    if (!RstIsEndPointPresent (CurrentRpIndex, TempPciBus)) {
      DEBUG ((DEBUG_INFO, "No Device on Rp#%d\n", CurrentRpIndex));
      continue;
    }

    LanesOccupied = RstGetRpLaneOccupyMask (CurrentRpIndex);
    RstGetDeviceClassCode (CurrentRpIndex, TempPciBus, &ClassCode);

    if (RstIsTetonGlacier (CurrentRpIndex, TempPciBus)) {
      // BIOS shall not enable HW remapping for PCIe Port when TG is detected
      // TG are really two devices with link width x2 (2x2) and enabling hardware remapping on it
      // would result in loosing one x2 controller.
      continue;
    }

    if (RstIsDeviceRemapCapablePcieStorage (ClassCode)) {
      DEBUG ((DEBUG_INFO, "RstDetectPcieStorageDevices: Remap capable storage device found on Rp %d\n", CurrentRpIndex));
      DEBUG ((DEBUG_INFO, "ClassCode = %d, SubClassCode = %d, ProgrammingInterface = %d\n", ClassCode.BaseClassCode, ClassCode.SubClassCode, ClassCode.ProgrammingInterface));
      if (ClassCode.SubClassCode == PCI_CLASS_MASS_STORAGE_RAID) {
        ClassCode.ProgrammingInterface = RST_PCIE_STORAGE_INTERFACE_NVME;
      }

      if ((RstGetCycleRouterNumber (CurrentRpIndex) != RST_PCIE_STORAGE_CR_INVALID) &&
          (!RstIsRemapConfigValid (LanesOccupied, CurrentRpIndex, SataRegBase))) {
        DEBUG ((DEBUG_INFO, "RstDetectPcieStorageDevices: mismatch occured on Rp = %d\n", CurrentRpIndex));
      } else {
        mPcieStorageMap[CurrentRpIndex].StorageClassCode = ClassCode;
      }

      switch (LanesOccupied) {
        case 0x0F:
          mPcieStorageMap[CurrentRpIndex].StorageLinkWidth = RstLinkWidthX4;
          RpIndex += 3;
          break;
        case 0x03:
          mPcieStorageMap[CurrentRpIndex].StorageLinkWidth = RstLinkWidthX2;
          RpIndex += 1;
          break;
        case 0x01:
          mPcieStorageMap[CurrentRpIndex].StorageLinkWidth = RstLinkWidthX1;
          break;
      }
    }
  }

}

/**
  Function to perform dump for SATA_CFG_RST_PCIE_STORAGE_DETECTION

  @param[in]        CrNumber                Cycle router number

  @retval None
**/
STATIC
VOID
RstPcieStorageRemappingDump (
  IN UINT8  CrNumber
  )
{
  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingDump() Started\n"));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].SupportRstPcieStorageRemapping   =  %x\n", CrNumber, mRstCrConfig[CrNumber].RemappingSupported));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].RootPortNum                      =  %x\n", CrNumber, mRstCrConfig[CrNumber].RootPortNumber));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].RootPortLaneMask                 =  %x\n", CrNumber, mRstCrConfig[CrNumber].RootPortLaneMask));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].DeviceInterface                  =  %x\n", CrNumber, mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].IsMsixSupported                  =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.MsixSupported));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].MsixStartingVector               =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.StartingVector));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].MsixEndingVector                 =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.EndingVector));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].EndPointBarSize                  =  %x\n", CrNumber, mRstCrConfig[CrNumber].EndPointBarSize));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].EndPointUniqueMsixTableBar       =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBar));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].EndPointUniqueMsixTableBarValue  =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBarValue));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].EndPointUniqueMsixPbaBar         =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBar));
  DEBUG ((DEBUG_INFO, "mRstCrConfig[%d].EndPointUniqueMsixPbaBarValue    =  %x\n", CrNumber, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBarValue));

  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].PmCapPtr                    =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].PmCapPtr));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].PcieCapPtr                  =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].PcieCapPtr));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].L1ssCapPtr                  =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].L1ssCapPtr));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointL1ssControl2        =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointL1ssControl2));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointL1ssControl1        =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointL1ssControl1));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].LtrCapPtr                   =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].LtrCapPtr));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointLtrData             =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointLtrData));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointLctlData16          =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointLctlData16));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointDctlData16          =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointDctlData16));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].EndpointDctl2Data16         =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].EndpointDctl2Data16));
  DEBUG ((DEBUG_INFO, "mSavedConfigSpace[%d].RootPortDctl2Data16         =  %x\n", CrNumber, mSavedConfigSpace[CrNumber].RootPortDctl2Data16));
  DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingDump() Ended\n"));
  DEBUG_CODE_END ();
}

/**
  Returns Bar size of a given BAR region

  @param[in] BarAddress  Address of a BAR

  @retval UINT32  Size of a BAR
**/
STATIC
UINT32
RstGetBarSize (
  IN UINT64  BarAddress
  )
{
  UINT32  BarSize;

  PciSegmentWrite32 (BarAddress, 0xFFFFFFFF);
  BarSize = PciSegmentRead32 (BarAddress);
  PciSegmentWrite32 (BarAddress, 0);

  BarSize &= 0xFFFFFFF0;
  BarSize = (UINT32) ~BarSize;

  return BarSize;
}

/**
  Configure the Power Management setting for RST PCIe Storage Remapping
**/
STATIC
VOID
RstConfigurePmForRemapping (
  VOID
  )
{
  UINT64               PciSataRegBase;
  UINT8                CrNumber;

  PciSataRegBase = SataRegBase (SATA_1_CONTROLLER_INDEX);

  ///
  /// For each RST PCIe Storage Cycle Router, program the "Extended General Configuration Register" field,
  ///
  for (CrNumber = 0; CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR; CrNumber++) {
    if (RstSetCycleRouter (PciSataRegBase, CrNumber)) {
      DEBUG ((DEBUG_INFO, "RstConfigurePmForRemapping: Low Power Programming - Recommanded Setting\n"));
      //
      // Program the SATA PCI offset 354h bit [20, 19, 17, 16] to [1b, 1b, 1b, 1b]
      //
      PciSegmentOr32 (PciSataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_EGCR,
        B_SATA_CFG_RST_PCIE_STORAGE_EGCR_CRDCGE | B_SATA_CFG_RST_PCIE_STORAGE_EGCR_CRTCGE | B_SATA_CFG_RST_PCIE_STORAGE_EGCR_ICAS | B_SATA_CFG_RST_PCIE_STORAGE_EGCR_TSCAS);
    }
  }
}

/**
  Configure the ASPM for Root Port and PCIe storage device before enabling RST PCIe Storage Remapping

  @param[in] CrNumber               Cycle router number
  @param[in] TempPciBusMin          The temporary minimum Bus number for root port initialization
  @param[in] TempPciBusMax          The temporary maximum Bus number for root port initialization
  @param[in] RstConfig              Rst Config
**/
STATIC
VOID
RstConfigurePcieStorageDeviceAspm (
  IN UINT8       CrNumber,
  IN UINT8       TempPciBusMin,
  IN UINT8       TempPciBusMax,
  IN RST_CONFIG  *RstConfig
  )
{
  PCH_PCIE_DEVICE_OVERRIDE                  *DevAspmOverride;
  UINT32                                    NumOfDevAspmOverride;
  UINTN                                     RpDevice;
  UINTN                                     RpFunction;
  UINT8                                     RpNumber;

  DEBUG ((DEBUG_INFO, "ConfigureRst: RstConfigurePcieStorageDeviceAspm() Started\n"));

  DevAspmOverride                   = NULL;
  NumOfDevAspmOverride              = 0;
  RpNumber                          = mRstCrConfig[CrNumber].RootPortNumber;


  GetPchPcieRpDevFun (RpNumber, &RpDevice, &RpFunction);

  //
  // Set the ASPM for both root port and PCIe storage device
  //
  RootportDownstreamPmConfiguration (
    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
    DEFAULT_PCI_BUS_NUMBER_PCH,
    (UINT8) RpDevice,
    (UINT8) RpFunction,
    TempPciBusMin,
    TempPciBusMax,
    &mPcieRpConfig->RootPort[RpNumber].PcieRpLtrConfig,
    &mPcieRpConfig->RootPort[RpNumber].PcieRpCommonConfig,
    NumOfDevAspmOverride,
    DevAspmOverride
    );

  DEBUG ((DEBUG_INFO, "ConfigureRst: RstConfigurePcieStorageDeviceAspm() Ended\n"));
}

/**
  Function to perform memory allocation for PCIe storage device that support unique BAR

  @param[in]        BarSize         The BAR size required for memory allocation
  @param[in,out]    AllocAddr       The Address that been allocated by this function

  @retval EFI_SUCCESS               The function completed successfully
  @retval EFI_OUT_OF_RESOURCES      Memory or storage is not enough
**/
STATIC
EFI_STATUS
RstPcieStorageMemAllocation (
  IN     UINT32  BarSize,
  IN OUT UINT32  *AllocAddr
  )
{
  if ((PchRstPcieStorageCurrentMemoryRange + BarSize) > RST_PCIE_STORAGE_MEMORY_END_RANGE) {
    return EFI_OUT_OF_RESOURCES;
  }

  if ((PchRstPcieStorageCurrentMemoryRange & (BarSize - 1)) != 0) {
    *AllocAddr      = (PchRstPcieStorageCurrentMemoryRange + BarSize) & ~(BarSize-1);
  } else {
    *AllocAddr      = PchRstPcieStorageCurrentMemoryRange;
  }

  PchRstPcieStorageCurrentMemoryRange       = *AllocAddr + BarSize;
  return EFI_SUCCESS;
}

/**
  Function to perform some configurations if RST PCIe Storage Remapping is Disabled

  @param[in] SataRegBase            SATA Register Base
  @param[in] CrNumber               Cycle router number

  @retval None
**/
STATIC
VOID
RstDisablePcieStorageRemapping (
  IN UINT64                      SataRegBase,
  IN UINT8                       CrNumber
  )
{
  DEBUG ((DEBUG_INFO, "RstDisablePcieStorageRemapping: RstDisablePcieStorageRemapping() Started\n"));

  if (RstSetCycleRouter (SataRegBase, CrNumber)) {
    ///
    /// Program Sata PCI offset 300h, bit[31:29] to '111b'
    ///
    PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) (B_SATA_CFG_RST_PCIE_STORAGE_GCR_CREL | B_SATA_CFG_RST_PCIE_STORAGE_GCR_RCL | B_SATA_CFG_RST_PCIE_STORAGE_GCR_PNCAIDL));
  }

  DEBUG ((DEBUG_INFO, "RstDisablePcieStorageRemapping: RstDisablePcieStorageRemapping() Ended\n"));
}

/**
  Function to perform lockdown if a RST PCIe Storage Cycle Router is unused/disabled

  @param[in] SataRegBase            SATA Register Base

  @retval None
**/
STATIC
VOID
RstLockdownUnusedPcieStorageCycleRouter (
  IN UINT64                      SataRegBase
  )
{
  UINT8              CrNumber;
  UINT8              LastEnabledCycleRouter;
  UINT32             Data32;

  DEBUG ((DEBUG_INFO, "RstLockdownUnusedPcieStorageCycleRouter: RstLockdownUnusedPcieStorageCycleRouter() Started\n"));


  ///
  /// Check if a RST PCIe Storage Cycle Router is enabled and locked or not
  /// If it is not enabled and not locked, perform the lockdown by programming the Sata PCI offset 300h, bit[31:29] to '111b'
  ///
  LastEnabledCycleRouter = 0;
  for (CrNumber = 0; CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR; CrNumber++) {
    if (RstSetCycleRouter (SataRegBase, CrNumber)) {
      Data32 = PciSegmentRead32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR) &
      (UINT32) (B_SATA_CFG_RST_PCIE_STORAGE_GCR_CREL |
                B_SATA_CFG_RST_PCIE_STORAGE_GCR_RCL |
                B_SATA_CFG_RST_PCIE_STORAGE_GCR_PNCAIDL |
                B_SATA_CFG_RST_PCIE_STORAGE_GCR_CRE);
      if (Data32 == 0) {
        DEBUG ((DEBUG_INFO, "RstLockdownUnusedPcieStorageCycleRouter: RST PCIe Storage Cycle Router %d is not used and not locked\n", CrNumber + 1));
        DEBUG ((DEBUG_INFO, "RstLockdownUnusedPcieStorageCycleRouter: Lockdown the unused RST PCIe Storage Cycle Router\n"));
        RstDisablePcieStorageRemapping (SataRegBase, CrNumber);
      } else {
        LastEnabledCycleRouter = CrNumber;
      }
    }
  }

  ///
  /// After the lockdown, set the "Cycle Router Accessibility Select", SATA PCI offset FC0h [1:0] back to an enabled Cycle Router
  ///
  RstSetCycleRouter (SataRegBase, LastEnabledCycleRouter);

  DEBUG ((DEBUG_INFO, "RstLockdownUnusedPcieStorageCycleRouter: RstLockdownUnusedPcieStorageCycleRouter() Ended\n"));
}

/**
  Program and remap the PCIe storage device Sata Capability

  @param[in] EndPointPciBase      Endpoint Base Address
  @param[in] SataRegBase          Sata Base Address
  @param[in] CapPtr               Capability Pointer to Endpoint's Sata Capability

  @retval None
**/
STATIC
VOID
RstRemapDeviceSataCap (
  IN UINT64          EndPointPciBase,
  IN UINT64          SataRegBase,
  IN UINT8           CapPtr
  )
{
  UINT32    Data32Or;
  UINT32    Data32And;

  ///
  /// Setup  and enable Sata Capability Remap
  /// Program the PCIe storage device's Sata capability offset to Sata PCI offset 338h[23:16] and set bit[31] = 1b
  ///
  Data32Or  = (UINT32) ((CapPtr << N_SATA_CFG_RST_PCIE_STORAGE_MXCRCC_TCSO) | B_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_RE);
  Data32And = (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_RE | B_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC_TCSO);
  PciSegmentAndThenOr32 (
    SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_AIDPCRC,
    Data32And,
    Data32Or
    );

  ///
  /// Setup and enable I/O BAR Remap by programming Sata PCI offset 320h[31] = 1b
  ///
  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_IOBRSC, (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_IOBRSC_RE);
}

/**
  Returns current Msix vector for remapped devices

  @param[in] CrNumber  Cycle router number

  @retval UINT16  Current Msix vector number
**/
STATIC
UINT16
RstGetCurrentMsixVector (
  IN UINT8  CrNumber
  )
{
  UINT16  CurrentMsixVector;
  UINT32  Index;

  CurrentMsixVector = 0;

  for (Index = 0; Index < CrNumber; Index++) {
    if (CurrentMsixVector < mRstCrConfig[Index].MsixConfig.EndingVector) {
      CurrentMsixVector = mRstCrConfig[Index].MsixConfig.EndingVector;
    }
  }

  return CurrentMsixVector;
}

/**
  Program and remap the PCIe storage device MSI-X Capability

  @param[in]        EndPointPciBase         Endpoint Base Address
  @param[in]        SataRegBase             Sata Base Address
  @param[in]        CapPtr                  Capability Pointer to Endpoint's MSI-X Capability
  @param[in]        CrNumber                Cycle router number
  @param[out]       MsixConfig              Pointer to Cycle Router MSI-X Config

  @retval None
**/
STATIC
BOOLEAN
RstRemapDeviceMsixCap (
  IN UINT64          EndPointPciBase,
  IN UINT64          SataRegBase,
  IN UINT8           CapPtr,
  IN UINT8           CrNumber,
  OUT CR_MSIX_CONFIG  *MsixConfig
  )
{
  EFI_STATUS        Status;
  UINT32            Data32Or;
  UINT32            Data32And;
  UINT32            MsixBaseAddr;
  UINT32            PbaBaseAddr;
  UINT32            DeviceBarSize;
  UINT32            DeviceTableOffsetAndBir;
  UINT32            DevicePbaOffsetAndBir;
  UINT16            MsixTableSize;
  UINT16            StartingVector;
  UINT16            EndingVector;
  UINT8             TableBir;
  UINT8             PbaBir;
  BOOLEAN           IsMsixBarUnique;
  BOOLEAN           IsPbaBarUnique;

  MsixBaseAddr      = 0;
  PbaBaseAddr       = 0;
  IsMsixBarUnique   = FALSE;
  IsPbaBarUnique    = FALSE;

  ///
  /// Get the PCIe storage device MSI-X table size
  ///
  MsixTableSize     = PciSegmentRead16 (EndPointPciBase + CapPtr + 0x02) & 0x7FF;

  ///
  /// Calculate the Starting and Ending vector
  ///
  StartingVector = RstGetCurrentMsixVector (CrNumber) + 1;
  EndingVector = StartingVector + MsixTableSize;

  ///
  /// If the ending vector is overflowed (> 2047), skip this port from RST PCIe Storage Remapping
  ///
  if (EndingVector > 2047) {
    return FALSE;
  }

  ///
  /// Read the PCIe storage device's table offset, table BIR and check if it supports unique MSI-X Table BAR
  ///
  DeviceTableOffsetAndBir  = PciSegmentRead32 (EndPointPciBase + CapPtr + 0x04);
  TableBir = (UINT8) DeviceTableOffsetAndBir & (BIT2|BIT1|BIT0);
  if (((TableBir != 0) && (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_NVME)) ||
      ((TableBir != 5) && (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_AHCI))) {
    IsMsixBarUnique     = TRUE;

    ///
    /// Allocate PCH Reserved Memory Pool for PCIe storage device if it has unique MSI-X BAR
    ///
    DeviceBarSize = RstGetBarSize (EndPointPciBase + R_PCI_BAR0_OFFSET + (0x04 * TableBir));
    Status              = RstPcieStorageMemAllocation (DeviceBarSize, &MsixBaseAddr);

    ///
    /// Skip this port from RST PCIe Storage Remapping if it is running out of resource
    ///
    if (Status == EFI_OUT_OF_RESOURCES) {
      return FALSE;
    }
  }

  ///
  /// Read the PCIe storage device's PBA offset, PBA BIR and check if it supports unique MSI-X PBA BAR
  ///
  DevicePbaOffsetAndBir  = PciSegmentRead32 (EndPointPciBase + CapPtr + 0x08);
  PbaBir = (UINT8) DevicePbaOffsetAndBir & (BIT2|BIT1|BIT0);
  if ((((PbaBir != 0) && (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_NVME)) ||
       ((PbaBir != 5) && (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_AHCI))) &&
      (PbaBir != TableBir)) {
    IsPbaBarUnique      = TRUE;

    ///
    /// Allocate PCH Reserved Memory Pool for PCIe storage device if it has unique PBA BAR
    ///
    DeviceBarSize = RstGetBarSize (EndPointPciBase + R_PCI_BAR0_OFFSET + (0x04 * PbaBir));
    Status              = RstPcieStorageMemAllocation (DeviceBarSize, &PbaBaseAddr);

    ///
    /// Skip this port from RST PCIe Storage Remapping if it is running out of resource
    ///
    if (Status == EFI_OUT_OF_RESOURCES) {
      return FALSE;
    }
  }

  ///
  /// Update IsMsixSupported flag and keep the PCIe storage device Starting vector and Ending vector for later steps
  ///
  MsixConfig->MsixSupported  = TRUE;
  MsixConfig->StartingVector = StartingVector;
  MsixConfig->EndingVector   = EndingVector;

  ///
  /// If PCIe storage device supports unique MSI-X BAR, store the BAR and BIR for later step usage
  /// Program the "MSI-X Table Base Address Register", SATA PCI offset 344h[31:01] to the allocated value and set its bit[0]
  ///
  if (IsMsixBarUnique) {
    MsixConfig->EndPointUniqueMsixTableBarValue     = MsixBaseAddr;
    MsixConfig->EndPointUniqueMsixTableBar          = (UINT32) R_PCI_BAR0_OFFSET + (0x04 * TableBir);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MXTBAR, (MsixBaseAddr | B_SATA_CFG_RST_PCIE_STORAGE_MXTBAR_TBAV));
  }

  ///
  /// If PCIe storage device supports unique MSI-X PBA BAR, store the BAR and BIR for later step usage
  /// Program the "MSI-X PBA Base Address Register", SATA PCI offset 34Ch[31:01] to the allocated value and set its bit[0]
  ///
  if (IsPbaBarUnique) {
    MsixConfig->EndPointUniqueMsixPbaBarValue     = PbaBaseAddr;
    MsixConfig->EndPointUniqueMsixPbaBar          = (UINT32) R_PCI_BAR0_OFFSET + (0x04 * PbaBir);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MXPBAR, (PbaBaseAddr | B_SATA_CFG_RST_PCIE_STORAGE_MXPBAR_TBAV));
  }

  ///
  /// Program the PCIe storage device's table offset, table BIR to "MSI-X Table Remap Configuration",
  /// Sata PCI offset 340h [31:03, 2:0] accordingly
  ///
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MXTRC, DeviceTableOffsetAndBir);

  ///
  /// Program the PCIe storage device's PBA offset, PBA BIR to "MSI-X PBA Remap Configuration",
  /// Sata PCI offset 348h [31:03, 2:0] accordingly
  ///
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MXPRC, DevicePbaOffsetAndBir);

  ///
  /// Setup  and enable MSI-X Capability Remap
  /// Program the PCIe storage device's MSI-X capability offset to Sata PCI offset 33Ch[23:16] and set bit[31] = 1b
  ///
  Data32Or  = (UINT32) ((CapPtr << N_SATA_CFG_RST_PCIE_STORAGE_MXCRCC_TCSO) | B_SATA_CFG_RST_PCIE_STORAGE_MXCRC_RE);
  Data32And = (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_MXCRC_RE | B_SATA_CFG_RST_PCIE_STORAGE_MXCRCC_TCSO);
  PciSegmentAndThenOr32 (
    SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MXCRC,
    Data32And,
    Data32Or
    );

  return TRUE;
}

/**
  Marks cycle routers for remapping based of platform configuration and BIOS settings

  @param[in] RstConfig      Rst Config
**/
STATIC
VOID
RstMarkCycleRoutersForRemapping (
  IN  RST_CONFIG    *RstConfig
  )
{

  UINT32  RpNumber;
  UINT8   CrNumber;

  for (RpNumber = 0; RpNumber < GetPchMaxPciePortNum (); RpNumber++) {
    DEBUG ((DEBUG_INFO, "RstMarkCycleRoutersForRemapping: Examining Rp %d\n", RpNumber));
    CrNumber = mCycleRouterMap[RpNumber / 4];

    if (CrNumber >= PCH_MAX_RST_PCIE_STORAGE_CR) {
      DEBUG ((DEBUG_INFO, "RstMarkCycleRoutersForRemapping: cycle router not available\n"));
      RpNumber += 3 - (RpNumber % 4);
      continue;
    }

    if (mPcieStorageMap[RpNumber].StorageLinkWidth == 0) {
      DEBUG ((DEBUG_INFO, "MarCycleRoutersForRemapping: No PCIe storage device present\n"));
      continue;
    }

    if (RstConfig->HardwareRemappedStorageConfig[CrNumber].Enable == 0) {
      DEBUG ((DEBUG_INFO, "RstMarkCycleRoutersForRemapping: Cycle router %d is disabled by policy\n", CrNumber));
      RpNumber += 3 - (RpNumber % 4);
      continue;
    }

    if ((RstConfig->HardwareRemappedStorageConfig[CrNumber].RstPcieStoragePort != 0) &&
        (RstConfig->HardwareRemappedStorageConfig[CrNumber].RstPcieStoragePort != RpNumber + 1)) {
      DEBUG ((DEBUG_INFO, "RstMarkCycleRoutersForRemapping: root port %d not matched with selected root port, proceed to next port\n", RpNumber + 1));
      continue;
    }

    if (mPcieStorageMap[RpNumber].StorageClassCode.ProgrammingInterface == 0) {
      DEBUG ((DEBUG_INFO, "RstMarkCycleRoutersForRemapping: Remapping is not supported for this PCIe storage\n"));
      continue;
    }

    ///
    /// Update the remapping detail for detected PCIe storage device, and move to the root port in the next x4 lane
    ///
    DEBUG ((DEBUG_INFO, "MarkCycleRouterForRemapping: Marking CR#%d for remapping\n", CrNumber));
    mRstCrConfig[CrNumber].RemappingSupported  = TRUE;
    mRstCrConfig[CrNumber].RootPortNumber = (UINT8) RpNumber;
    mRstCrConfig[CrNumber].RootPortLaneMask = RstGetRpLaneOccupyMask (RpNumber);
    mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface = mPcieStorageMap[RpNumber].StorageClassCode.ProgrammingInterface;


    RpNumber += 3 - (RpNumber % 4);
  }
}

/**
  Function to perform late configuration for RST PCIe Storage Remapping

  @param[in] SataRegBase                SATA Register Base
  @param[in] AhciBar                    AHCI Base Address
  @param[in] CrNumber                   Cycle router number
  @param[in,out] RemapDeviceLinkInfo    Variable to store link info (link speed, link width) for remapped device
  @param[in] RstConfig                  RST Config
**/
STATIC
VOID
RstPcieStorageRemappingLateConfig (
  IN UINT64                                 SataRegBase,
  IN UINT32                                 AhciBar,
  IN UINT8                                  CrNumber,
  IN OUT UINT16                             *RemapDeviceLinkInfo,
  IN RST_CONFIG                             *RstConfig
  )
{
  UINT64                BarIndex;
  UINT32                BaseAddr;
  UINT32                Data32;
  UINT16                Data16;

  DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingLateConfig: Started\nCycle router number = %d", CrNumber));

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "=====================================================\n"));
  DEBUG ((DEBUG_INFO, "ConfigureRst: RstPcieStorageRemappingLateConfig() Dump\n"));
  RstPcieStorageRemappingDump (CrNumber);
  DEBUG ((DEBUG_INFO, "=====================================================\n"));
  DEBUG_CODE_END ();

  //
  // This function shouldn't be called with invalid cycle router number
  //
  if (!RstSetCycleRouter (SataRegBase, CrNumber)) {
    ASSERT (FALSE);
    return;
  }

  ///
  /// Clear all BARs within endpoint to 0
  ///
  BaseAddr = R_PCI_BAR0_OFFSET;
  for (BarIndex = 0; BarIndex < PCI_CARD_BAR_TOTAL; BarIndex++) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, BaseAddr);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, 0x0);
    BaseAddr += 0x4;
  }

  ///
  /// After the link reenabled and the 100ms (tunable) delay,
  /// If L1 Sub-Stated is supported, restore saved endpoint's L1 Sub-States Extended Capability, offset 0x0C and 0x08
  ///
  if (mSavedConfigSpace[CrNumber].L1ssCapPtr != 0) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, (UINT32) mSavedConfigSpace[CrNumber].L1ssCapPtr + 0x0C);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, (UINT32) mSavedConfigSpace[CrNumber].EndpointL1ssControl2);

    Data32 = mSavedConfigSpace[CrNumber].EndpointL1ssControl1 & ~ (0xF);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, (UINT32) mSavedConfigSpace[CrNumber].L1ssCapPtr + 0x08);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, (UINT32) Data32);

    Data32 = mSavedConfigSpace[CrNumber].EndpointL1ssControl1;
    PciSegmentWrite32 ((UINT64) (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR), (UINT32) Data32);
  }

  ///
  /// After the link reenabled and the 100ms (tunable) delay,
  /// If LTR is supported, restore saved endpoint's LTR Extended Capability, offset 0x04 [31:0]
  ///
  if (mSavedConfigSpace[CrNumber].LtrCapPtr != 0) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, (UINT32) mSavedConfigSpace[CrNumber].LtrCapPtr + 0x04);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, (UINT32) mSavedConfigSpace[CrNumber].EndpointLtrData);
  }

  ///
  /// Restore the following endpoint's registers
  /// i.)   endpoint's Link Control's "Enable Clock Power Management" field and "Common Clock Configuration" field
  /// ii.)  endpoint's Device Control 2 for "LTR Mechanism Enable" field
  /// iii.) endpoint's Device Control for "Max Payload Size" field
  ///
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mSavedConfigSpace[CrNumber].PcieCapPtr + 0x10);
  PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR,
    (UINT32) ~(BIT6 | BIT8),
    (UINT32) (mSavedConfigSpace[CrNumber].EndpointLctlData16 & (~B_PCIE_LCTL_ASPM)));

  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mSavedConfigSpace[CrNumber].PcieCapPtr + 0x28);
  PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR,
    (UINT32) ~(BIT10),
    (UINT32) (mSavedConfigSpace[CrNumber].EndpointDctl2Data16));

  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mSavedConfigSpace[CrNumber].PcieCapPtr + 0x8);
  PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR,
    (UINT32) ~(BIT5 | BIT6 | BIT7),
    (UINT32) (mSavedConfigSpace[CrNumber].EndpointDctlData16));

  ///
  /// Restore the root port's Device Control 2  "LTR Mechanism Enable" field, offset 68h[10]
  ///
  PciSegmentAndThenOr32 (SataRegBase + R_PCH_PCIE_CFG_DCTL2 + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET,
    (UINT32) ~(B_PCIE_DCTL2_LTREN),
    (UINT32) (mSavedConfigSpace[CrNumber].RootPortDctl2Data16));

  ///
  /// If the "Common Clock Configuration" field is set, perform link retrain by setting the "Retrain Link" bit, Sata PCI offset 150h[5] to 1b
  ///
  if ((mSavedConfigSpace[CrNumber].EndpointLctlData16 & B_PCIE_LCTL_CCC) == B_PCIE_LCTL_CCC) {

    PciSegmentOr16 (SataRegBase + R_PCH_PCIE_CFG_LCTL + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, (UINT16) (B_PCIE_LCTL_RL));

    RstPollPcieLinkStateUntil (TRUE, 30000, SataRegBase + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET + R_PCH_PCIE_CFG_LSTS);
  }


  ///
  /// Restore the endpoint's Link Control's "Active State Link PM Control" field
  ///
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mSavedConfigSpace[CrNumber].PcieCapPtr + 0x10);
  PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR,
    (UINT32) ~(BIT0 | BIT1),
    (UINT32) (mSavedConfigSpace[CrNumber].EndpointLctlData16 & B_PCIE_LCTL_ASPM));

  ///
  /// Disable MSE, read and write back ABAR, then enable MSE
  ///
  PciSegmentAnd16 (SataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);

  Data32 = PciSegmentRead32 (SataRegBase + R_SATA_CFG_AHCI_BAR);
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_AHCI_BAR, (UINT32) Data32);

  PciSegmentOr16 (SataRegBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// If endpoint supports MSI-X, perform the following:
  /// i.)  program endpoint starting and ending vector to AHCIBar + offset 808h + n*80h, bit[10:0] and bit[26:16]
  /// ii.) enable MSI-X Interrupt delivery by programming "Interrupt Delivery", AHCIBar + offset 808h + n*80h + 4h, bit[31:30]
  if (mRstCrConfig[CrNumber].MsixConfig.MsixSupported) {
    Data32 = (mRstCrConfig[CrNumber].MsixConfig.EndingVector << N_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC_MXEV) | mRstCrConfig[CrNumber].MsixConfig.StartingVector;
    MmioWrite32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR), Data32);
    MmioOr32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR) + 0x04, BIT31);
  } else {
    ///
    ///  Else, program "Device MSI-X Configuration", AHCIBar + offset 808h + n*80h, bit [31:0], and
    /// AHCIBar + offset 808h bit [31:0], and n*80h + 4h, bit [31:0] = 0;
    ///
    MmioWrite32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR), 0);
    MmioWrite32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMXC + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR) + 0x04, 0);
  }

  ///
  /// Setup a 32-bit data for RWO usage later
  /// Refer to CC, SCC, PI from step 7.d, set up bit[23:0] accordingly
  /// If an AHCI device is detected, also set the "Device Type" (bit31)
  ///
  Data32 = (mRstCrConfig[CrNumber].ClassCode.BaseClassCode << N_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_BCC) | (mRstCrConfig[CrNumber].ClassCode.SubClassCode << N_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_SCC) | (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface);
  if (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_AHCI) {
    Data32 |= B_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC_DT;
  }

  ///
  /// Program the endpoint "Device Class Code", AHCIBar + offset 800h + n*80h with the 32-bit data
  ///
  MmioWrite32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DCC + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR), Data32);

  ///
  ///  Read the remapped root ports Link Status, and update the RemapDeviceLinkInfo according on the "Negotiated Link Width" and "Current Link Speed"
  /// 9 bits are allocated to record these links info (3 bits per Cycle Router) as below:
  /// i.)   BIT[2:0] for Cycle Router 1
  /// ii.)  BIT[5:3] for Cycle Router 2
  /// iii.) BIT[8:6] for Cycle Router 3
  ///
  /// The bits definition is as below:
  /// i.)  Link Width (2 bits): 0 = x1, 1 = x2, 2 = x4
  /// ii.) Link Speed (1 bit) : 0 = GEN1/GEN2, 1 = GEN3
  ///
  Data16 = PciSegmentRead16 (SataRegBase + R_PCH_PCIE_CFG_LSTS + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET);

  ///
  /// Check the link speed and update the following bit in RemapDeviceLinkInfo:
  /// i.)   BIT[0] for Cycle Router 1
  /// ii.)  BIT[3] for Cycle Router 2
  /// iii.) BIT[6] for Cycle Router 3
  ///
  switch (Data16 & B_PCIE_LSTS_CLS) {
    case V_PCIE_LSTS_CLS_GEN1:
    case V_PCIE_LSTS_CLS_GEN2:
      *RemapDeviceLinkInfo |= PCI_CARD_LINK_SPEED_GEN1_GEN2 << (CrNumber * 3);
      break;

    case V_PCIE_LSTS_CLS_GEN3:
      *RemapDeviceLinkInfo |= PCI_CARD_LINK_SPEED_GEN3 << (CrNumber * 3);
      break;

    default:
      break;
  }

  ///
  /// Check the link width and update the following bits in RemapDeviceLinkInfo:
  /// i.)   BIT[2:1] for Cycle Router 1
  /// ii.)  BIT[5:4] for Cycle Router 2
  /// iii.) BIT[8:7] for Cycle Router 3
  ///
  switch (Data16 & B_PCIE_LSTS_NLW) {
    case V_PCIE_LSTS_NLW_1:
      *RemapDeviceLinkInfo |= PCI_CARD_LINK_WIDTH_1 << (CrNumber * 3 + 1);
      break;

    case V_PCIE_LSTS_NLW_2:
      *RemapDeviceLinkInfo |= PCI_CARD_LINK_WIDTH_2 << (CrNumber * 3 + 1);
      break;

    case V_PCIE_LSTS_NLW_4:
      *RemapDeviceLinkInfo |= PCI_CARD_LINK_WIDTH_4 << (CrNumber * 3 + 1);
      break;

    default:
      break;
  }

  ///
  /// Program the endpoint MBAR length into the "Device Memory BAR Length", AHCIBar offset 804h + n*80h
  ///
  MmioWrite32 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_CR1_DMBL + (CrNumber * V_SATA_MEM_RST_PCIE_STORAGE_REMAP_CONFIG_CR), mRstCrConfig[CrNumber].EndPointBarSize);

  ///
  /// If the device supports unique MSI-X Table BAR, program the related PCIe storage device BAR with the same BAR value that been allocated early
  /// Program 0 to the higher memory BAR if it is 64 bit BAR
  ///
  if ((mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBarValue != 0)) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBar);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBarValue);
  }

  ///
  /// If the device supports unique MSI-X PBA BAR, program the related PCIe storage device BAR with the same BAR value that been allocated early
  /// Program 0 to the higher memory BAR if it is 64 bit BAR
  ///
  if ((mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBarValue != 0)) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CAIR, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBar);
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_CADR, mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBarValue);
  }

  ///
  /// Lockdown the Remap Configuration and RST PCIe Storage Cycle Router
  ///
  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) (B_SATA_CFG_RST_PCIE_STORAGE_GCR_CREL | B_SATA_CFG_RST_PCIE_STORAGE_GCR_RCL));

  DEBUG ((DEBUG_INFO, "ConfigureRst: RstPcieStorageRemappingLateConfig() Ended\n"));
}

/**
  Configures remap BAR and returns its size

  @param[in] EndPointPciBase  End point PCI base address
  @param[in] SataRegBase      PCI SATA base address
  @param[in] CrNumber         Cycle router number

  @retval UINT32  Remap BAR size
**/
STATIC
UINT32
RstProgramRemapBarAndGetItsSize (
  IN  UINT64  EndPointPciBase,
  IN  UINT64  SataRegBase,
  IN  UINT8   CrNumber
  )
{

  UINT64  RemapBarAddress;


  if (mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface == RST_PCIE_STORAGE_INTERFACE_AHCI) {
    ///
    /// If the PCIe storage device is using AHCI register interface, map its BAR5 by setting
    /// the Sata PCI offset 310h[31, 20, 19:16] to [1, 0, 1001b]
    ///
    PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MBRC,
      (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_MBRC_RE | B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TT | B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB),
      (B_SATA_CFG_RST_PCIE_STORAGE_MBRC_RE | (V_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB_BAR5 << N_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB)));

    RemapBarAddress = EndPointPciBase + R_PCI_BAR5_OFFSET;

  } else {
    ///
    /// Else the PCIe storage device is using NVMe register interface, map its BAR0 by setting
    /// the Sata PCI offset 310h[31, 20, 19:16] to [1, 1, 0100b]
    ///
    PciSegmentAndThenOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_MBRC,
      (UINT32) ~(B_SATA_CFG_RST_PCIE_STORAGE_MBRC_RE | B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TT | B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB),
      (B_SATA_CFG_RST_PCIE_STORAGE_MBRC_RE | B_SATA_CFG_RST_PCIE_STORAGE_MBRC_TT | (V_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB_BAR0 << N_SATA_CFG_RST_PCIE_STORAGE_MBRC_TMB)));

    RemapBarAddress = EndPointPciBase + R_PCI_BAR0_OFFSET;

  }

  return RstGetBarSize (RemapBarAddress);

}

/**
  Checks PCIe storage device BAR size

  @param[in] DeviceBarSize   Size of a device BAR
  @param[in] CrNumber        Cycle router number
  @param[in] EndPointPciBase Address of device's PCI config space

  @retval  BOOLEAN  TRUE if Device bar size is < 16KB, FALSE otherwise
**/
STATIC
BOOLEAN
RstCheckDeviceBarSize (
  IN UINT32  DeviceBarSize,
  IN UINT8   CrNumber,
  IN UINT64  EndPointPciBase
  )
{
  if (DeviceBarSize < 0x4000 || RstIsStonyBeach (EndPointPciBase)) {
    return TRUE;
  } else {
    return FALSE;
  }

}

/**
  Function to perform early configuration for RST PCIe Storage Remapping

  @param[in] SataRegBase                SATA Register Base
  @param[in] AhciBar                    AHCI Base Address
  @param[in] CrNumber                   Cycle router number
  @param[in] SataPortsEnabled           SATA Port Implemented
  @param[in] RemapBarEnabled            Boolean to indicate Is AHCI Remapped BAR bit is set or not
  @param[in] TempPciBusMin              The temporary minimum Bus number for root port initialization
  @param[in] RstConfig                  RST Config
**/
STATIC
VOID
RstPcieStorageRemappingEarlyConfig (
  IN UINT64                                 SataRegBase,
  IN UINT32                                 AhciBar,
  IN UINT8                                  CrNumber,
  IN UINT16                                 SataPortsEnabled,
  IN OUT BOOLEAN                            *RemapBarEnabled,
  IN UINT8                                  TempPciBusMin,
  IN RST_CONFIG                             *RstConfig
  )
{
  UINT64                PciRootPortRegBase;
  UINT64                EndPointPciBase;
  UINT32                Data32;
  UINT8                 Data8;
  UINT32                DeviceBarSize;
  UINT8                 TempRootPortBusNum;
  UINT16                CapRegs;
  UINT8                 CapPtr;
  UINT8                 CapId;

  DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: Started\nCycle router number = %d", CrNumber));

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "=====================================================\n"));
  DEBUG ((DEBUG_INFO, "ConfigureRst: RstPcieStorageRemappingEarlyConfig() Dump\n"));
  RstPcieStorageRemappingDump (CrNumber);
  DEBUG ((DEBUG_INFO, "=====================================================\n"));
  DEBUG_CODE_END ();

  TempRootPortBusNum        = TempPciBusMin;

  //
  // This function should not be called with unsupported cycle router number
  //
  if (!RstSetCycleRouter (SataRegBase, CrNumber)) {
    ASSERT (FALSE);
    return;
  }

  PciRootPortRegBase = RstGetRpBaseAddress (mRstCrConfig[CrNumber].RootPortNumber);
  EndPointPciBase = RstSetRpTempBusNumberAndGetEpBaseAddress (mRstCrConfig[CrNumber].RootPortNumber, TempRootPortBusNum);
  DeviceBarSize = RstProgramRemapBarAndGetItsSize (EndPointPciBase,
                                                   SataRegBase,
                                                   CrNumber
                                                   );

  if (!RstCheckDeviceBarSize (DeviceBarSize,
                              CrNumber,
                              EndPointPciBase
                              ))
  {
    DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device BAR size exceed 16KB\n"));
    DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: Skip this device and continue to next CR#\n"));
    mRstCrConfig[CrNumber].RemappingSupported = FALSE;
    RstClearRpTempBusNumber (mRstCrConfig[CrNumber].RootPortNumber);
    return;
  } else {
    mRstCrConfig[CrNumber].EndPointBarSize = DeviceBarSize;
  }

  //
  // Program SATA PCI offset 368h [7:3, 2:0] to [SATA device number, SATA function number] (D23:F0).
  //
  PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_RHDF, 0xB8);

  ///
  /// Get the endpoint first capability pointer
  ///
  CapPtr = PciSegmentRead8 (EndPointPciBase + PCI_CAPBILITY_POINTER_OFFSET);

  while (CapPtr) {
    CapRegs = PciSegmentRead16 (EndPointPciBase + CapPtr);
    CapId  = (UINT8) (CapRegs & 0x00FF);

    switch (CapId) {
      case PCI_CARD_PM_CAP_ID:
        //
        // Save the Capability Pointer for the device's Power Management Capability to NVS for RTD3 usage
        //
        DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device supports Power Management Capability\n"));
        mSavedConfigSpace[CrNumber].PmCapPtr = CapPtr;
        break;
      case PCI_CARD_MSIX_CAP_ID:
        DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device supports MSI-X Capability\n"));
        if (!RstRemapDeviceMsixCap (EndPointPciBase, SataRegBase, CapPtr, CrNumber, &(mRstCrConfig[CrNumber].MsixConfig))) {
          mRstCrConfig[CrNumber].RemappingSupported = FALSE;
        }
        break;
      case PCI_CARD_SATA_CAP_ID:
        DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device supports Sata Capability\n"));
        RstRemapDeviceSataCap (EndPointPciBase,SataRegBase,CapPtr);
        break;
      default:
        break;
    }
    CapPtr = (CapRegs & 0xFF00) >> 8;
  }

  ///
  /// Re-check SupportRstPcieStorageRemapping Flag after configurating PCIe storage device's MSI-X Cap
  /// If the flag return FALSE due to table size overflowed, skip the current device and proceed to next device
  ///
  if (mRstCrConfig[CrNumber].RemappingSupported == FALSE) {
    DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: skip remapping @ CR#%x due to MSI-X table size overflowed\n", CrNumber + 1));
    return;
  }

  //
  // Read the PCIe storage device's Extended Capability Pointer
  // If it supports ARI, clear "NVM Remapping Device:Function", Sata PCI offset 350h to 0h
  //
  if (PcieFindExtendedCapId (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempRootPortBusNum, 0, 0, 0xE) != 0) {
    PciSegmentWrite32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_NRDF, 0x0);
  }

  ///
  /// Read and keep PCIe storage device's BCC, SCC and PI
  ///
  mRstCrConfig[CrNumber].ClassCode.BaseClassCode = PciSegmentRead8 (EndPointPciBase + R_PCI_BCC_OFFSET);
  mRstCrConfig[CrNumber].ClassCode.SubClassCode = PciSegmentRead8 (EndPointPciBase + R_PCI_SCC_OFFSET);
  mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface  = PciSegmentRead8 (EndPointPciBase + R_PCI_PI_OFFSET);

  ///
  /// Set PCIe storage device discovered root port respectively to "PCIe Lane Selected", Sata PCI offset 300h [20:1]
  ///
  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) mRstCrConfig[CrNumber].RootPortLaneMask << (RstPlsBitNumber (mRstCrConfig[CrNumber].RootPortNumber) + 1));

  ///
  /// Clear PCCS, Sata PCI offset 304h [30] by writing 1 to it
  ///
  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GSR, (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_GSR_PCCS);

  ///
  /// Check the endpoint extended Capability ID
  /// If the endpoint supports L1 Substates, perform the following:
  /// i.)  Store the endpoint's L1 Sub-States Extended Capability offset + 0x0C[7:0]
  /// ii.) Store the endpoint's L1 Sub-States Extended Capability offset + 0x08[31:0]
  ///
  mSavedConfigSpace[CrNumber].L1ssCapPtr = PcieFindExtendedCapId (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempRootPortBusNum , 0, 0, V_PCIE_EX_L1S_CID);
  if (mSavedConfigSpace[CrNumber].L1ssCapPtr != 0) {
    DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device supports L1SS Capability\n"));
    mSavedConfigSpace[CrNumber].EndpointL1ssControl2   = PciSegmentRead8 (EndPointPciBase + mSavedConfigSpace[CrNumber].L1ssCapPtr + 0x0C);
    mSavedConfigSpace[CrNumber].EndpointL1ssControl1   = PciSegmentRead32 (EndPointPciBase + mSavedConfigSpace[CrNumber].L1ssCapPtr + 0x08);
  }

  ///
  /// Check the endpoint extended Capability ID
  /// If the endpoint supports LTR, store the endpoint's LTR Extended Capability offset + 0x04[31:0]
  ///
  mSavedConfigSpace[CrNumber].LtrCapPtr = PcieFindExtendedCapId (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempRootPortBusNum , 0, 0, 0x18);
  if (mSavedConfigSpace[CrNumber].LtrCapPtr != 0) {
    DEBUG ((DEBUG_INFO, "RstPcieStorageRemappingEarlyConfig: PCIe storage device supports LTR Capability\n"));
    mSavedConfigSpace[CrNumber].EndpointLtrData     = PciSegmentRead32 (EndPointPciBase + mSavedConfigSpace[CrNumber].LtrCapPtr + 0x04);
  }

  ///
  /// Store the following endpoint's registers
  /// i.)   endpoint's Link Control for "Active State Link PM Control" field, "Enable Clock Power Management" field and "Common Clock Configuration" field
  /// ii.)  endpoint's Device Control 2 for "LTR Mechanism Enable" field
  /// iii.) endpoint's Device Control for "Max Payload Size" field
  ///
  mSavedConfigSpace[CrNumber].PcieCapPtr            = PcieFindCapId (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempRootPortBusNum , 0, 0, 0x10);
  mSavedConfigSpace[CrNumber].EndpointLctlData16    = PciSegmentRead16 (EndPointPciBase + mSavedConfigSpace[CrNumber].PcieCapPtr + 0x10) & (BIT0 | BIT1 | BIT6 | BIT8);
  mSavedConfigSpace[CrNumber].EndpointDctl2Data16   = PciSegmentRead16 (EndPointPciBase + mSavedConfigSpace[CrNumber].PcieCapPtr + 0x28) & BIT10;
  mSavedConfigSpace[CrNumber].EndpointDctlData16    = PciSegmentRead16 (EndPointPciBase + mSavedConfigSpace[CrNumber].PcieCapPtr + 0x8) & (BIT5 | BIT6 | BIT7);

  RstClearRpTempBusNumber (mRstCrConfig[CrNumber].RootPortNumber);

  ///
  /// Store the root port's Device Control 2 "LTR Mechanism Enable" field
  ///
  mSavedConfigSpace[CrNumber].RootPortDctl2Data16   = PciSegmentRead16 (PciRootPortRegBase + R_PCH_PCIE_CFG_DCTL2) & B_PCIE_DCTL2_LTREN;

  ///
  /// BIOS sets the link disable bit in the Link Control register within the associated PCIe root port
  /// to place the link in the disabled state
  ///
  PciSegmentOr16 (PciRootPortRegBase + R_PCH_PCIE_CFG_LCTL, (UINT16) (B_PCIE_LCTL_LD));

  RstPollPcieLinkStateUntil (FALSE, 50000, PciRootPortRegBase + R_PCH_PCIE_CFG_LSTS);

  ///
  /// Disable Root Port at PSF
  ///
  PsfDisablePcieRootPort (mRstCrConfig[CrNumber].RootPortNumber);

  ///
  /// Mirror the "Ports Implemented" captured in previous step,
  /// program it to the shadowed AHCI Ports Implemented field, SATA PCI offset 358h
  ///
  PciSegmentWrite16 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_SAPI, SataPortsEnabled);

  ///
  /// Program "NVM Remap Memory Offset", "Memory Space Limit" and "NVM Remap Memory BAR Enable"
  /// Set AHCIBar offset A4h [27:16, 12:1, 0] to [10h, 1EFh, '1b']
  /// Only program it once
  ///
  if (!(*RemapBarEnabled)) {
    Data32 = (V_SATA_MEM_VS_CAP_NRMO << N_SATA_MEM_VS_CAP_NRMO) | (B_SATA_MEM_VS_CAP_NRMBE) | (V_SATA_MEM_VS_CAP_MSL << N_SATA_MEM_VS_CAP_MSL);
    MmioWrite32 (AhciBar + R_SATA_MEM_VS_CAP, Data32);
    *RemapBarEnabled = TRUE;
  }

  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_EGCR, (DeviceBarSize >> 14) << 26);

  ///
  /// Enable RST PCIe Storage Cycle Router
  /// BIOS then writes to the RST PCIe Storage's Cycle Router Enable (CRE) bit in the GCR register to enable
  /// the register remapping.
  ///
  PciSegmentOr32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR, (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_GCR_CRE);

  ///
  /// Assert if RST PCIe Storage Cycle Router failed to enable
  ///
  Data32 = PciSegmentRead32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR) & (UINT32) B_SATA_CFG_RST_PCIE_STORAGE_GCR_CRE;
  if (Data32 == 0) {
    DEBUG ((DEBUG_ERROR, "RstPcieStorageRemappingEarlyConfig: CRE not able to set, Sata + 300h = %x, Sata + 304h = %x\n", PciSegmentRead32 ((UINT64) (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GCR)), PciSegmentRead32 ((UINT64) (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_GSR))));
    ASSERT (FALSE);
  }

  ///
  /// Read and write back "ASSEL" and "MSS" field , SATA PCI offset 9Ch[4:3,2:0] using byte access
  ///
  Data8 = PciSegmentRead8 (SataRegBase + R_SATA_CFG_SATAGC);
  PciSegmentWrite8 (SataRegBase + R_SATA_CFG_SATAGC, Data8);

  ///
  /// Set BME of root port
  ///
  PciSegmentOr32 (SataRegBase + PCI_COMMAND_OFFSET + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, EFI_PCI_COMMAND_BUS_MASTER);

  ///
  /// Set all "Memory Base" bits in MBL, PBML and PMBU32 to 1
  ///
  PciSegmentOr32 (SataRegBase + R_PCI_BRIDGE_MBL + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, B_PCI_BRIDGE_MBL_MB);
  PciSegmentOr32 (SataRegBase + R_PCI_BRIDGE_PMBL + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, B_PCI_BRIDGE_PMBL_PMB);
  PciSegmentOr32 (SataRegBase + R_PCI_BRIDGE_PMBU32 + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, B_PCI_BRIDGE_PMBU32);

  ///
  /// Re-enable PCIe link
  ///
  PciSegmentAnd32 (SataRegBase + R_PCH_PCIE_CFG_LCTL + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET, (UINT32) ~(B_PCIE_LCTL_LD));
  DEBUG ((DEBUG_INFO, "ConfigureRst: RstPcieStorageRemappingEarlyConfig() Ended\n"));
}

/**
  Checks if any of the cycle routers has been marked for remapping

  @retval TRUE   If any of the cycle routers needs to be configured
  @retval FALSE  Otherwise
**/
STATIC
BOOLEAN
RstIsRemappingRequired (
  VOID
  )
{
  UINT8 CrNumber;

  for (CrNumber = 0; CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR; CrNumber++) {
    if (mRstCrConfig[CrNumber].RemappingSupported == TRUE) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Checks if BIOS configuration allows for remapping

  @param[in] RemapEnabled       Indicates if remapped is enabled by policy
  @param[in] SataRegBase        Sata register base
  @param[in] SataEnablePolicy   Sata controller enabled by policy

  @retval TRUE   If configuration allowes for remapping
  @retval FALSE  Otherwise
**/
STATIC
BOOLEAN
RstIsRemappingPossible (
  BOOLEAN  RemapEnabled,
  UINT64   SataRegBase,
  UINT32   SataEnablePolicy
  )
{

  ///
  /// Assert if Sata Controller is Disabled and RST PCIe Storage Remapping is Enabled
  ///
  if (!SataEnablePolicy && RemapEnabled) {
    DEBUG ((DEBUG_ERROR, "ConfigureRst: Can't perform RST PCIe Storage Remapping when Sata Controller is Disabled\n"));
    ASSERT (FALSE);
    return FALSE;
  }

  ///
  /// Assert if Sata Controller mode is not RAID mode and RST PCIe Storage Remapping is Enabled
  ///
  if ((RemapEnabled == TRUE) && (PciSegmentRead8 (SataRegBase + R_PCI_SCC_OFFSET) != PCI_CLASS_MASS_STORAGE_RAID)) {
    DEBUG ((DEBUG_ERROR, "Can't perform RST PCIe Storage remapping when Sata Controller mode is not RAID mode\n"));
    ASSERT (FALSE);
    return FALSE;
  }

  return TRUE;
}

/**
  Initializes PcieStorageInfoHob used later by platform code
**/
STATIC
VOID
RstInitPcieStorageInfoHob (
  VOID
  )
{

  UINT8                  Index;
  PCIE_STORAGE_INFO_HOB  PcieStorageInfoHob;
  UINT8                  PortIndexMax;

  PcieStorageInfoHob.Revision = PCIE_STORAGE_INFO_HOB_REVISION;

  PortIndexMax = GetPchMaxPciePortNum ();
  for (Index = 0; Index < PortIndexMax; Index++) {
    PcieStorageInfoHob.PcieStorageLinkWidth[Index] = mPcieStorageMap[Index].StorageLinkWidth;
    PcieStorageInfoHob.PcieStorageProgrammingInterface[Index] = (UINT8) mPcieStorageMap[Index].StorageClassCode.ProgrammingInterface;
  }

  CopyMem (PcieStorageInfoHob.RstCycleRouterMap, mCycleRouterMap, sizeof (PcieStorageInfoHob.RstCycleRouterMap));

  BuildGuidDataHob (&gPchPcieStorageDetectHobGuid, (VOID*) &PcieStorageInfoHob, sizeof (PCIE_STORAGE_INFO_HOB));

}

/**
  Initializes SATA_PCR_RST_HOB used in DXE to fill ACPI tables
**/
STATIC
VOID
RstInitRstHob (
  VOID
  )
{

  UINT8 CrNumber;
  PCH_RST_HOB  RstHob;

  for (CrNumber = 0; CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR; CrNumber++) {
    RstHob.RstCrConfiguration[CrNumber].DeviceInterface = mRstCrConfig[CrNumber].ClassCode.ProgrammingInterface;
    RstHob.RstCrConfiguration[CrNumber].RootPortNum = mRstCrConfig[CrNumber].RootPortNumber;
    RstHob.RstCrConfiguration[CrNumber].EndPointUniqueMsixTableBar = mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBar;
    RstHob.RstCrConfiguration[CrNumber].EndPointUniqueMsixTableBarValue = mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixTableBarValue;
    RstHob.RstCrConfiguration[CrNumber].EndPointUniqueMsixPbaBar = mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBar;
    RstHob.RstCrConfiguration[CrNumber].EndPointUniqueMsixPbaBarValue = mRstCrConfig[CrNumber].MsixConfig.EndPointUniqueMsixPbaBarValue;
  }

  CopyMem(RstHob.SavedRemapedDeviceConfigSpace, &mSavedConfigSpace, sizeof(SAVED_DEVICE_CONFIG_SPACE) * PCH_MAX_RST_PCIE_STORAGE_CR);

  BuildGuidDataHob (&gPchRstHobGuid, (VOID*) &RstHob, sizeof (PCH_RST_HOB));

}

/**
  Reenables PCIe link for remapped devices

  @param[in]  SataRegBase  Sata register base
  @param[in]  RstConfig    RST Config
**/
STATIC
VOID
RstReenablePcieLinkForRemapedDevices (
  IN UINT64      SataRegBase,
  IN RST_CONFIG  *RstConfig
  )
{
  UINT32  MaxDeviceResetDelay;
  UINT8   CrNumber;

  ///
  /// Poll PCIe Link Active status till it is active for every remapped port(s)
  ///
  MaxDeviceResetDelay = 0;
  for (CrNumber = 0; CrNumber < PCH_MAX_RST_PCIE_STORAGE_CR; CrNumber++) {
    ///
    /// Proceed to next RST PCIe Storage Cycle Router if remapping isn't enabled on cycle router
    ///
    if (mRstCrConfig[CrNumber].RemappingSupported == FALSE) {
      continue;
    }

    //
    // Get the highest delay time based on the delay policy for each RST PCIe Storage Cycle Router that is enabled
    //
    if (RstConfig->HardwareRemappedStorageConfig[CrNumber].DeviceResetDelay > MaxDeviceResetDelay) {
      MaxDeviceResetDelay = RstConfig->HardwareRemappedStorageConfig[CrNumber].DeviceResetDelay;
    }

    if (RstSetCycleRouter (SataRegBase, CrNumber)) {
      RstPollPcieLinkStateUntil (TRUE, 1000 * 1000, SataRegBase + V_SATA_MEM_RST_PCIE_STORAGE_REMAP_RP_OFFSET + R_PCH_PCIE_CFG_LSTS);
    }
  }

  ///
  /// Stall for a delay based on policy after enable PCIE link
  ///
  MicroSecondDelay (MaxDeviceResetDelay * 1000);

}

/**
  Disable the RST remap address decoding range while RST is disabled.

  @param[in] AhciBar                ABAR address
**/
STATIC
VOID
RstDisableRemapDecoding (
  UINT32                            AhciBar
  )
{
  UINT64                            PciSataRegBase;
  UINT32                            OrgAhciBar;
  UINT8                             OrgCmd;

  if (AhciBar == 0) {
    DEBUG ((DEBUG_ERROR, "RstDisableRemapDecoding: Invalid AHCI BAR address.\n"));
    ASSERT (FALSE);
    return;
  }

  PciSataRegBase  = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      SataDevNumber (SATA_1_CONTROLLER_INDEX),
                      SataFuncNumber (SATA_1_CONTROLLER_INDEX),
                      0
                      );
  OrgCmd          = PciSegmentRead8 (PciSataRegBase + PCI_COMMAND_OFFSET);
  OrgAhciBar      = PciSegmentRead32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR);

  if (AhciBar != OrgAhciBar) {
    PciSegmentWrite8 (PciSataRegBase + PCI_COMMAND_OFFSET, 0);
    PciSegmentWrite32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR, AhciBar);
  }
  PciSegmentWrite8 (PciSataRegBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Program "NVM Remap Memory BAR Enable",  AHCIBar offset A4h [0] to ['0b']
  // Also set NRMO AHCIBar offset A4h [27:16] to 0x00F, and MSL AHCIBar offset A4h [12:1] to 0.
  //
  DEBUG ((DEBUG_INFO, "RstDisableRemapDecoding: Program AHCIBar offset A4h [27:16, 12:1, 0] to [0x00F, 0, 0] to disable remap decoding\n"));
  MmioWrite32 (AhciBar + R_SATA_MEM_VS_CAP, (0x00F << N_SATA_MEM_VS_CAP_NRMO));

  if (AhciBar != OrgAhciBar) {
    PciSegmentWrite8 (PciSataRegBase + PCI_COMMAND_OFFSET, 0);
    PciSegmentWrite32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR, OrgAhciBar);
  }
  PciSegmentWrite8 (PciSataRegBase + PCI_COMMAND_OFFSET, OrgCmd);
}

/**
  Enables legacy pin based interrupts servicing in SATA controller

  @param[in]  SataRegBase  SATA controller register base
**/
STATIC
VOID
RstEnableLegacyInterruptServicing (
  IN UINT64  SataRegBase
  )
{
  UINT8 Index;

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    if (RstSetCycleRouter (SataRegBase, Index)) {
      PciSegmentAnd32 (SataRegBase + R_SATA_CFG_RST_PCIE_STORAGE_EGCR, (UINT32) ~B_SATA_CFG_RST_PCIE_STORAGE_EGCR_TSCAS);
    }
  }
}

/**
  Programms the Intel RST Feature Capabilities register to inform the RST driver which
  features are supported.
  Caller of this function is responsible for making sure that AHCI BAR has been set.

  @param[in] AhciBar     AHCI BAR
  @param[in] SataMode    SATA Mode
  @param[in] RstConfig   RST Config
**/
STATIC
VOID
RstInitializeRstFeatures (
  IN UINT32            AhciBar,
  IN SATA_MODE         SataMode,
  IN RST_CONFIG        *RstConfig
  )
{
  UINT16  WordReg;

  // PCH BIOS Spec Section 14.1.5.2 Enable Flexible RAID OROM Features
  // RST features can be customized by programming
  // SW Feature Mask (SFM) register before loading the RAID Option ROM. The RAID
  // OROM will enable the desired features based on the setting in that register, please refer to
  // PCH EDS for more details.
  // For example, if the platform desired features are RAID0, RAID1, RAID5, RAID10 and
  // RST Smart Storage caching. System BIOS should set RSTF (ABAR + C8h [15:0]) to 022Fh before
  // loading RAID OROM.
  //
  WordReg = 0;

  if (RstConfig->HddUnlock == TRUE) {
    //
    // If set to "1", indicates that the HDD password unlock in the OS is enabled
    //
    WordReg |= B_SATA_MEM_AHCI_SFM_HDDLK;
  }

  if (RstConfig->LedLocate == TRUE) {
    //
    // If set to "1", indicates that the LED/SGPIO hardware is attached
    //
    WordReg |= B_SATA_MEM_AHCI_SFM_LEDL;
  }

  if (SataMode == SataModeRaid) {
    if (RstConfig->LegacyOrom == TRUE) {
      //
      // If set to "1", then Legacy OROM is enabled
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_LEGACY;
    }

    if (RstConfig->Raid0 == TRUE) {
      //
      // If set to "1", then RAID0 is enabled in Flexible RAID Option ROM.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_R0E;
    }

    if (RstConfig->Raid1 == TRUE) {
      //
      // If set to "1", then RAID1 is enabled in FD-OROM.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_R1E;
    }

    if (RstConfig->Raid10 == TRUE) {
      //
      // If set to "1", then RAID10 is enabled in FD-OROM.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_R10E;
    }

    if (RstConfig->Raid5 == TRUE) {
      //
      // If set to "1", then RAID5 is enabled in FD-OROM.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_R5E;
    }

    if (RstConfig->Irrt == TRUE) {
      //
      // If set to "1", then Intel Rapid Recovery Technology is enabled.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_RSTE;
    }

    if (RstConfig->OromUiBanner == TRUE) {
      //
      // If set to "1" then the OROM UI is shown.  Otherwise, no OROM banner or information
      // will be displayed if all disks and RAID volumes are Normal.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_IRSTOROM;
    }

    if (RstConfig->IrrtOnly == TRUE) {
      //
      // If set to "1", then only IRRT volumes can span internal and eSATA drives. If cleared
      // to "0", then any RAID volume can span internal and eSATA drives.
      //
      WordReg |= B_SATA_MEM_AHCI_SFM_IROES;
    }
    //
    // Enable the RST Smart Storage caching bit to support Smart Storage caching.
    //
    if (RstConfig->SmartStorage == TRUE) {
      WordReg |= B_SATA_MEM_AHCI_SFM_SEREQ;
    }
    //
    // Program the delay of the OROM UI Splash Screen in a normal status.
    //
    WordReg |= (UINT16) (RstConfig->OromUiDelay << N_SATA_MEM_AHCI_SFM_OUD);

    if (RstConfig->OptaneMemory == TRUE) {
      ///
      /// If set to "1", then Optane(TM) Memory Acceleration is enabled
      ///
      WordReg |= B_SATA_MEM_AHCI_SFM_OMA;
    }

    if (RstConfig->CpuAttachedStorage == TRUE) {
      ///
      /// If set to "1", then CPU Attached Storage feature is enabled
      ///
      WordReg |= B_SATA_MEM_AHCI_SFM_CPU_STORAGE;
    }
  }

  //
  // SW Feature Mask (SFM) is a Write-Once register.
  //
  MmioWrite16 (AhciBar + R_SATA_MEM_AHCI_SFM, WordReg);
}

/**
  Program AHCI Bar

  @param[in]      PciSataRegBase        SATA controller address
  @param[in]      AhciBar               AHCI BAR
**/
STATIC
VOID
RstSetAhciBar (
  IN     UINT64       PciSataRegBase,
  IN     UINT32       AhciBar
  )
{
  ///
  /// Disable command register memory space decoding
  ///
  PciSegmentAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// Set the AHCI BAR
  ///

  PciSegmentWrite32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR, AhciBar);

  ///
  /// Enable command register memory space decoding
  ///
  PciSegmentOr16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Clear AHCI Bar

  @param[in]      PciSataRegBase        SATA controller address
**/
STATIC
VOID
RstClearAhciBar (
  IN     UINT64       PciSataRegBase
  )
{
  ///
  /// Disable command register memory space decoding
  ///
  PciSegmentAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// Set Ahci Bar to zero
  ///
  PciSegmentWrite32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR, 0);
}

/**
  Function to configure RST PCIe Storage Remapping (Intel RST Driver is required)

  @param[in] SiPolicy         The Silicon Policy PPI instance
  @param[in] PciSataRegBase   SATA controller address
  @param[in] AhciBar          AHCI BAR
  @param[in] SataConfig       Sata Config instance
  @param[in] RstConfig        RST Config instance
**/
STATIC
VOID
RstConfigurePcieStorageRemapping (
  IN SI_POLICY_PPI    *SiPolicy,
  IN UINT64           PciSataRegBase,
  IN UINT32           AhciBar,
  IN SATA_CONFIG      *SataConfig,
  IN RST_CONFIG       *RstConfig
  )
{
  EFI_STATUS            Status;
  UINT8                 TempPciBusMin;
  UINT16                SataPortsEnabled;
  UINT8                 Index;
  UINT16                RemapDeviceLinkInfo;
  UINT8                 RemapCapReg;
  BOOLEAN               RemapBarEnabled;
  PCH_PCIE_CONFIG       *PcieRpConfig;

  DEBUG ((DEBUG_INFO, "RstConfigurePcieStorageRemapping (): Started\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  mPcieRpConfig               = PcieRpConfig;

  RemapDeviceLinkInfo = 0;
  RemapCapReg = 0;
  RemapBarEnabled = FALSE;
  TempPciBusMin = PcdGet8 (PcdSiliconInitTempPciBusMin);


  RstCreateCycleRouterMap (PciSataRegBase, mCycleRouterMap);
  RstDetectPcieStorageDevices (PciSataRegBase, TempPciBusMin);

  RstInitPcieStorageInfoHob ();

  RstConfigurePmForRemapping ();

  if (!RstIsRemappingPossible (RstIsPcieStorageRemapEnabled (SiPolicy), PciSataRegBase, SataConfig->Enable)) {
    return;
  }

  RstMarkCycleRoutersForRemapping (RstConfig);

  ///
  /// If remapping isn't enabled on any cycle router, perform the disabling steps
  ///
  if (!RstIsRemappingRequired ()) {
    DEBUG ((DEBUG_INFO, "RstConfigurePcieStorageRemapping: No PCIe storage device is detected\n"));
    DEBUG ((DEBUG_INFO, "RstConfigurePcieStorageRemapping: Disabling RST PCIe Storage Remapping\n"));

    ///
    /// Program "NVM Remap Memory BAR Enable",  AHCIBar offset A4h [0] to ['0b']
    /// Also set NRMO AHCIBar offset A4h [27:16] to 0x00F, and MSL AHCIBar offset A4h [12:1] to 0.
    ///
    RstDisableRemapDecoding (AhciBar);

    ///
    /// Perform disable flow for each RST PCIe Storage Cycle Router Instance
    ///
    for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
      RstDisablePcieStorageRemapping (PciSataRegBase, Index);
    }
    return;
  }

  ///
  /// Read and store Port Implemented, AHCIBar offset 0Ch for later step usage
  ///
  SataPortsEnabled = MmioRead16 (AhciBar + R_SATA_MEM_AHCI_PI);

  ///
  /// Perform the early configuration for every RST PCIe Storage Cycle Router(s)
  ///
  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    if (mRstCrConfig[Index].RemappingSupported == FALSE) {
      continue;
    }

    ///
    /// Configure the ASPM for Root Port and PCIe storage device before enabling RST PCIe Storage Remapping
    ///
    RstConfigurePcieStorageDeviceAspm (Index, TempPciBusMin, PcdGet8 (PcdSiliconInitTempPciBusMax), RstConfig);

    ///
    /// Perform Early Configuration for remapping if the RST PCIe Storage Cycle Router contains PCIe storage device for remapping
    /// This early configuration contains steps to be performed for fast S3/S4/S5,
    /// while the remaining steps can be splitted for late exeuction
    ///
    RstPcieStorageRemappingEarlyConfig (PciSataRegBase, AhciBar, Index, SataPortsEnabled, &RemapBarEnabled, TempPciBusMin, RstConfig);
  }

  RstReenablePcieLinkForRemapedDevices (PciSataRegBase, RstConfig);

  ///
  /// Perform the remaining remapping configuration steps for every RST PCIe Storage Cycle Router(s)
  ///
  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {

    if (mRstCrConfig[Index].RemappingSupported == FALSE) {
      continue;
    }

    ///
    /// Perform remaining (Late) Configuration for RST PCIe Storage Remapping after the delay required after re-enable PCIe lnik
    ///
    RstPcieStorageRemappingLateConfig (PciSataRegBase, AhciBar, Index, &RemapDeviceLinkInfo, RstConfig);

    ///
    /// Store enabled CR information to be used by "Remap Capability Register" later
    ///
    RemapCapReg |= B_SATA_MEM_RST_PCIE_STORAGE_RCR_NRS_CR1 << Index;
  }

  ///
  ///  Program "Remap Capability Register", AHCIBar offset 800h [2:0] based on enabled CR
  ///
  MmioWrite8 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_RCR, RemapCapReg);

  ///
  /// Program MSI-X Vector, "AHCI MSI-X Configuration", AHCIBar offset 808h [8:0]
  /// with the remapped devices' link info captured in previous step
  ///
  MmioWrite16 (AhciBar + R_SATA_MEM_RST_PCIE_STORAGE_AMXC, RemapDeviceLinkInfo);

  RstEnableLegacyInterruptServicing (PciSataRegBase);

  ///
  /// Perform lockdown programming for unused Cycle Router
  ///
  RstLockdownUnusedPcieStorageCycleRouter (PciSataRegBase);

  RstInitRstHob ();

  DEBUG ((DEBUG_INFO, "RstConfigurePcieStorageRemapping: RstConfigurePcieStorageRemapping() Ended\n"));
}

/**
  Function to configure RST (Intel RST Driver is required)

  @param[in] SiPolicy         The Silicon Policy PPI instance

**/
VOID
ConfigureRst (
  IN SI_POLICY_PPI    *SiPolicy
  )
{
  UINT64                PciSataRegBase;
  UINT32                AhciBar;
  SATA_CONFIG           *SataConfig;
  RST_CONFIG            *RstConfig;
  BOOLEAN               SataHardwareEnabled;

  DEBUG ((DEBUG_INFO, "ConfigureRst (): Started\n"));

  SataConfig                  = GetPchSataConfig (SiPolicy, SATA_1_CONTROLLER_INDEX);
  RstConfig                   = GetRstConfig (SiPolicy);
  PciSataRegBase              = SataRegBase (SATA_1_CONTROLLER_INDEX);
  ZeroMem (&mRstCrConfig, sizeof (RST_CR_CONFIG) * PCH_MAX_RST_PCIE_STORAGE_CR);

  AhciBar = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  SataHardwareEnabled = (PciSegmentRead16 (PciSataRegBase + PCI_DEVICE_ID_OFFSET) != 0xFFFF);

  if (SataHardwareEnabled) {
    RstSetAhciBar (PciSataRegBase, AhciBar);

    RstInitializeRstFeatures (AhciBar, SataConfig->SataMode, RstConfig);
    RstConfigurePcieStorageRemapping (SiPolicy, PciSataRegBase, AhciBar, SataConfig, RstConfig);

    RstClearAhciBar (PciSataRegBase);
  }

  ConfigureSataAfterRst (SiPolicy, SATA_1_CONTROLLER_INDEX);

  DEBUG ((DEBUG_INFO, "ConfigureRst: ConfigureRst() Ended\n"));
}

