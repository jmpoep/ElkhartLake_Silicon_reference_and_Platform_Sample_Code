/** @file
  PEI Function to initialize SA PciExpress.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
  - 1) PCI Express Base Specification, www.pcisig.com
**/
#include <Library/SaPcieInitLib.h>
#include <Library/SaInitLib.h>
#include <Library/PmcPrivateLib.h>
#include <CpuRegs.h>
#include <CpuAccess.h>
#include <Library/CpuPlatformLib.h>
#include <CpuPcieInfo.h>
#include <Library/CpuPcieInfoLib.h>
#include <CpuPcieHob.h>
#include <SaConfigHob.h>
#include <ConfigBlock/SiConfig.h>
#include <IndustryStandard/Pci30.h>
#include <PcieRegs.h>




/**
  This function enumerate the bridge on the device

  @param[in]      PegBus                  - Particular Bus number
  @param[in]      PegDev                  - Particular Device number
  @param[in]      PegFunc                 - Particular Func number
  @param[in, out] PegMmioLength           - PEG MMIO length
  @param[in]      OpRomScanTempMmioBar    - Temporary BAR to MMIO map OpROMs during VGA scanning
  @param[in]      OpRomScanTempMmioLimit  - Limit address for OpROM MMIO range
  @param[in]      ScanForLegacyOpRom      - TRUE to scan for legacy only VBIOS, FALSE otherwise
  @param[out]     FoundLegacyOpRom        - If legacy only VBIOS found, returns TRUE

  @retval CardDetect : TRUE if current bridge device has a Graphics card.
  @retval CardDetect : FALSE if current bridge device has no Graphics card.
**/
BOOLEAN
EnumerateBridgeDevice (
  IN      UINT8     PegBus,
  IN      UINT8     PegDev,
  IN      UINT8     PegFunc,
  IN OUT  UINT32    *PegMmioLength,
  IN      UINT32    OpRomScanTempMmioBar,
  IN      UINT32    OpRomScanTempMmioLimit,
  IN      BOOLEAN   ScanForLegacyOpRom,
  OUT     BOOLEAN   *FoundLegacyOpRom
  )
{
  UINT64  DeviceBaseAddress;
  UINT32  MmioLength;
  UINT8   Bus;
  UINT8   Dev;
  UINT8   SubBusNum;
  UINT16  Buffer16;
  BOOLEAN CardDetect;

  CardDetect = FALSE;

  ///
  /// Temporarily program the secondary and subordinate bus numbers
  /// of PEG bridge to (1, 0xFF) so that devices behind the bridge can be seen
  ///
  Bus = 1;
  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PegBus, PegDev, PegFunc, 0);
  PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, Bus);
  PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, 0xFF);

  ///
  /// A config write is required in order for the device to re-capture the Bus number,
  /// according to PCI Express Base Specification, 2.2.6.2
  /// Write to a read-only register VendorID to not cause any side effects.
  ///
  PciSegmentWrite16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, 0, 0, PCI_VENDOR_ID_OFFSET), 0);

  SubBusNum = EnumerateDownstream (Bus);

  for (Bus = 1; Bus <= SubBusNum; Bus++) {
    for (Dev = 0; Dev < 32; Dev++) {
      ///
      /// Read Vendor ID to check if device exists
      /// if no device exists, then check next device
      ///
      if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Dev, 0, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
        continue;
      }
      ///
      /// Add the MMIO address space requirement for this device to the total
      ///
      FindPciDeviceMmioLength (Bus, Dev, 0, &MmioLength);
      (*PegMmioLength) += MmioLength;
      Buffer16 = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Dev, 0, R_PCI_SCC_OFFSET));
      ///
      /// Video cards can have Base Class 0 with Sub-class 1
      /// or Base Class 3 Sub-class 0
      ///
      if ((Buffer16 == 0x0001) || (Buffer16 == 0x0300)) {
        CardDetect = TRUE;
        if (ScanForLegacyOpRom) {
          (*FoundLegacyOpRom) = CheckForLegacyOnlyOpRom (OpRomScanTempMmioBar, OpRomScanTempMmioLimit, SA_SEG_NUM, Bus, Dev, 0);
        }
      }
    }
  }
  ///
  /// Clear bus number on all the bridges that we have opened so far.
  /// We have to do it in the reverse Bus number order.
  ///
  for (Bus = SubBusNum; Bus >= 1; Bus--) {
    for (Dev = 0; Dev < 32; Dev++) {
      ///
      /// Read Vendor ID to check if device exists
      /// if no device exists, then check next device
      ///
      DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, Bus, Dev, 0, 0);
      if (PciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        continue;
      }

      Buffer16 = PciSegmentRead16 (DeviceBaseAddress + R_PCI_SCC_OFFSET);
      ///
      /// Clear Bus Number for PCI/PCI Bridge Device
      ///
      if (Buffer16 == 0x0604) {
        PciSegmentWrite32 (DeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
      }
    }
  }
  ///
  /// Clear the bus numbers on the PEG bridge
  ///
  PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PegBus, PegDev, PegFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), 0);

  return CardDetect;
}

/**
  CheckAndInitializePegVga:  Check if PEG card is present and configure accordingly

  @param[in, out] PrimaryDisplay          - Primary Display - default is IGD
  @param[in]      PrimaryDisplaySelection - Primary display selection from BIOS Setup
  @param[in, out] PegMmioLength           - Total PEG MMIO length on all PEG ports
  @param[in]      OpRomScanTempMmioBar    - Temporary BAR to MMIO map OpROMs during VGA scanning
  @param[in]      OpRomScanTempMmioLimit  - Limit address for OpROM MMIO range
  @param[in]      ScanForLegacyOpRom      - TRUE to scan for legacy only VBIOS, FALSE otherwise
  @param[out]     FoundLegacyOpRom        - If legacy only VBIOS found, returns TRUE
**/
VOID
CheckAndInitializePegVga (
  IN OUT   DISPLAY_DEVICE               *PrimaryDisplay,
  IN       UINT8                        PrimaryDisplaySelection,
  IN OUT   UINT32                       *PegMmioLength,
  IN       UINT32                       OpRomScanTempMmioBar,
  IN       UINT32                       OpRomScanTempMmioLimit,
  IN       BOOLEAN                      ScanForLegacyOpRom,
  OUT      BOOLEAN                      *FoundLegacyOpRom
  )
{
  UINT16    ClassCode;
  BOOLEAN   IgdPresent;
  UINT8     PegBus;
  UINT8     PegDev;
  UINT8     PegFunc;
  UINT64    PegBaseAddress;
  UINT64    B1BaseAddress;
  UINT16    PegDevenReg;
  UINT8     PegComplete;
  UINT16    PegEnable;
  BOOLEAN   CardDetect;
  UINT32    MmioLength;
  UINT8     Func;
  UINT8     MaxFunction;
  UINT8     HeaderType;
  UINT8     PegVgaFunc;
  UINT8     MaxCpuPciePortNum;
  UINT8     PegDevenTableCount;
  PEG_DEVEN PegDevenTable[4];

  MmioLength = 0;
  CardDetect = FALSE;
  PegVgaFunc = 0xFF;
  B1BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, 0, 0, 0);

  PegDevenTableCount = (sizeof(PegDevenTable)) / (sizeof(PEG_DEVEN));
  MaxCpuPciePortNum  = GetMaxCpuPciePortNum();

  if (MaxCpuPciePortNum < PegDevenTableCount) {
    PegDevenTableCount = MaxCpuPciePortNum;
  }

  ///
  ///  Bus, Device, Function, DevenMask
  ///

  PegDevenTable[0].Bus = SA_PEG_BUS_NUM;
  PegDevenTable[0].Device = SA_PEG3_DEV_NUM;
  PegDevenTable[0].Function = SA_PEG3_FUN_NUM;
  PegDevenTable[0].DevenMask = BIT13;

  PegDevenTable[1].Bus       = SA_PEG_BUS_NUM;
  PegDevenTable[1].Device    = SA_PEG0_DEV_NUM;
  PegDevenTable[1].Function  = SA_PEG0_FUN_NUM;
  PegDevenTable[1].DevenMask = BIT3;
  PegDevenTable[2].Bus       = SA_PEG_BUS_NUM;
  PegDevenTable[2].Device    = SA_PEG1_DEV_NUM;
  PegDevenTable[2].Function  = SA_PEG1_FUN_NUM;
  PegDevenTable[2].DevenMask = BIT2;
  PegDevenTable[3].Bus       = SA_PEG_BUS_NUM;
  PegDevenTable[3].Device    = SA_PEG2_DEV_NUM;
  PegDevenTable[3].Function  = SA_PEG2_FUN_NUM;
  PegDevenTable[3].DevenMask = BIT1;


  DEBUG((DEBUG_INFO, "CheckAndInitializePegVga Entry!\n"));
  ///
  /// Read the DEVEN register for PEG 0/1/2/3 controllers configuration
  ///
  PegDevenReg = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_DEVEN)) & (BIT13 + BIT3 + BIT2 + BIT1);
  DEBUG((DEBUG_INFO, "PegDevenReg = %x\n", PegDevenReg));
  ///
  /// If IGD is disabled
  /// or not present IgdPresent is set to false
  ///
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 2, 0, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    IgdPresent = FALSE;
  } else {
    IgdPresent = TRUE;
  }
  DEBUG((DEBUG_INFO, "IgdPresent = %x\n", IgdPresent));
  ///
  /// Scan PEG device vs DEVEN register for PEG controllers configuration
  ///
  for (PegComplete = 0; PegComplete < PegDevenTableCount; PegComplete++) {

    PegBus    = PegDevenTable[PegComplete].Bus;
    PegDev    = PegDevenTable[PegComplete].Device;
    PegFunc   = PegDevenTable[PegComplete].Function;
    PegEnable = PegDevenTable[PegComplete].DevenMask;
    PegBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PegBus, PegDev, PegFunc, 0);

    if ((PegDevenReg & PegEnable) == 0) {
      continue;
    }
    ///
    /// Check for a card presence in the PEG slot.
    /// We don't know if it's a graphics card yet.
    ///
    if ((PciSegmentRead8 (PegBaseAddress + R_PCIE_SLSTS) & B_PCIE_SLSTS_PDS) == 0) {
      continue;
    }
    ///
    /// Set PEG PortBus = 1 to Read Endpoint.
    ///
    PciSegmentAndThenOr32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF, 0x00010100);

    ///
    /// A config write is required in order for the device to re-capture the Bus number,
    /// according to PCI Express Base Specification, 2.2.6.2
    /// Write to a read-only register VendorID to not cause any side effects.
    ///
    PciSegmentWrite16 (B1BaseAddress + PCI_VENDOR_ID_OFFSET, 0);

    ///
    /// Read Vendor ID to check if endpoint exists
    /// if no device exists, then check next device
    ///
    if (PciSegmentRead16 (B1BaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }
    ///
    /// Check for a multifunction device
    ///
    HeaderType = PciSegmentRead8 (B1BaseAddress + PCI_HEADER_TYPE_OFFSET);
    if ((HeaderType & HEADER_TYPE_MULTI_FUNCTION) != 0) {
      MaxFunction = 7;
    } else {
      MaxFunction = 0;
    }
    ///
    /// Calculate total PEG MMIO length on all functions of the endpoint
    ///
    for (Func = 0; Func <= MaxFunction; Func++) {
      if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, 0, Func, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
        continue;
      }

      FindPciDeviceMmioLength (1, 0, Func, &MmioLength);
      *PegMmioLength += MmioLength;
    }
    DEBUG((DEBUG_INFO, "PegMmioLength = %x\n", PegMmioLength));
    ///
    /// Perform PEG Endpoint Class Code Check.  If the Endpoint Class Code is
    /// not GFX, then the Port is being used as a standard PCI Express Port.
    ///
    ClassCode = PciSegmentRead16 (B1BaseAddress + R_PCI_SCC_OFFSET);
    if ((ClassCode == 0x0001) || (ClassCode == 0x0300)) {
      ///
      /// Disable PEG if IGD or PCI VGA take precedence.
      ///
      DEBUG((DEBUG_INFO, "Disable PEG if IGD or PCI VGA take precedence\n"));
      ///
      /// If IGD is present and selected as primary, skip the PEG VGA enabling
      ///
      if (IgdPresent && (PrimaryDisplaySelection == IGD)) {
        PciSegmentAnd32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF);
        DEBUG((DEBUG_INFO, "IGD is present and selected as primary, skip the PEG VGA enabling\n"));
        continue;
      }
      ///
      /// If PCI video card was detected, skip the PEG VGA enabling
      ///
      if (*PrimaryDisplay == PCI) {
        PciSegmentAnd32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF);
        DEBUG((DEBUG_INFO, "PCI video card was detected, skip the PEG VGA enabling\n"));
        continue;
      }
      ///
      /// Enable PEG video and Execute 16-bit address decodes on VGA I/O accesses
      ///
      /// Check if PEG VGA already detected
      ///
      if (*PrimaryDisplay != PEG) {
        PciSegmentOr16 (PegBaseAddress + R_SA_PEG_BCTRL_OFFSET, (BIT3 + BIT4));
        *PrimaryDisplay = PEG;
        PegVgaFunc = PegFunc;
        if (ScanForLegacyOpRom) {
          (*FoundLegacyOpRom) = CheckForLegacyOnlyOpRom (OpRomScanTempMmioBar, OpRomScanTempMmioLimit, SA_SEG_NUM, 1, 0, 0);
        }
        DEBUG ((DEBUG_INFO, "PCIe card on PEG%x%x (%x:%x:%x) enabled as VGA.\n", PegDev, PegFunc, PegBus, PegDev, PegFunc));
      }
    }

    if (ClassCode == 0x0604) {
      CardDetect =  EnumerateBridgeDevice (
                      PegBus,
                      PegDev,
                      PegFunc,
                      PegMmioLength,
                      OpRomScanTempMmioBar,
                      OpRomScanTempMmioLimit,
                      ScanForLegacyOpRom,
                      FoundLegacyOpRom
                      );
      if (CardDetect == TRUE) {
        ///
        /// Check if PEG VGA already detected
        ///
        if (*PrimaryDisplay != PEG) {
          PciSegmentOr16 (PegBaseAddress + R_SA_PEG_BCTRL_OFFSET, (BIT3 + BIT4));
          *PrimaryDisplay = PEG;
          PegVgaFunc = PegFunc;
          DEBUG ((DEBUG_INFO, "PCIe card on PEG%x%x (%x:%x:%x) enabled as VGA.\n", PegDev, PegFunc, PegBus, PegDev, PegFunc));
        }
      }
    }
    ///
    /// Restore bus numbers on the PEG bridge.
    ///
    PciSegmentAnd32 (PegBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF);
  } // End of the for Loop

  ///
  /// If a PEG device is used for primary graphics, set the ISAEN bit on all other PEG ports.
  ///
  if (PegVgaFunc != 0xFF) {
    for (PegComplete = 0; PegComplete < PegDevenTableCount; PegComplete++) {
      if (PegVgaFunc == PegComplete) {
        continue;
      }
      PegBus    = PegDevenTable[PegComplete].Bus;
      PegDev    = PegDevenTable[PegComplete].Device;
      PegFunc   = PegDevenTable[PegComplete].Function;
      PciSegmentOr16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PegBus, PegDev, PegFunc, R_SA_PEG_BCTRL_OFFSET), BIT2);
      DEBUG ((DEBUG_INFO, "PEG%x%x (%x:%x:%x) ISAEN has been set.\n", PegDev, PegFunc, PegBus, PegDev, PegFunc));
    }
  }
  DEBUG((DEBUG_INFO, "CheckAndInitializePegVga Exit!\n"));
}
