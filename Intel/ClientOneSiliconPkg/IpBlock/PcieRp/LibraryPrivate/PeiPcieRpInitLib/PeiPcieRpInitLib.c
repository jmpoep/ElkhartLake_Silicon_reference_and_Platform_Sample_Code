/** @file
  This file contains functions that initializes PCI Express Root Ports of PCH.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/TimerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Ppi/SiPolicy.h>
#include <IndustryStandard/Pci30.h>
#include <PchLimits.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/PchFiaLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPolicyLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PsfLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PcdLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PchDmiLib.h>
#include <Library/PeiHsioLib.h>
#include <Library/PeiPcieRpLib.h>
#include <Library/PchInfoLib.h>
#include <PcieRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchPcieRpRegs.h>
#include <PchPcieRpInfo.h>
#include <Library/PcieHelperLib.h>
#include <PciePreMemConfig.h>
#include <Register/PchPcieRpMultiVcRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Register/PchRegsFia15.h>
#include <Register/PchPcrRegs.h>

#include "PcieRpInitInternal.h"

#define LINK_ACTIVE_POLL_INTERVAL 100     // in microseconds
#define LINK_ACTIVE_POLL_TIMEOUT  1000000 // in microseconds

#define BUS_NUMBER_FOR_IMR 0x00

/**
  Device information structure
**/
typedef struct {
  UINT16  Vid;
  UINT16  Did;
  UINT8   MaxLinkSpeed;
} PCIE_DEVICE_INFO;

/**
  PCIe controller configuration strings.
**/
GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8* mPcieControllerConfigName[] = {
  "4x1",
  "1x2-2x1",
  "2x2",
  "1x4"
};

/**
  PCIe Multi VC controller configuration strings.
**/
GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8* mPcieMVCControllerConfigName[] = {
  "1x1",
  "1x2",
  "Rsvd",
  "Rsvd"
};

/**
  Returns the PCIe controller configuration (4x1, 1x2-2x1, 2x2, 1x4)

  @param[in] ControllerIndex        Number of PCIe controller (0 based)

  @retval PCIe controller configuration
**/
PCIE_CONTROLLER_CONFIG
GetPcieControllerConfig (
  IN     UINT32        ControllerIndex
  )
{
  EFI_STATUS              Status;
  UINT32                  Data32;
  PCIE_CONTROLLER_CONFIG  Config;
  UINT32                  FirstRp;

  FirstRp = GetControllerFirstRpIndex (ControllerIndex);

  Status = PchSbiRpPciRead32 (FirstRp, R_PCH_PCIE_CFG_STRPFUSECFG, &Data32);
  if (Status != EFI_SUCCESS) {
    return 0;
  } else {
    Config = ((Data32 & B_PCH_PCIE_CFG_STRPFUSECFG_RPC) >> N_PCH_PCIE_CFG_STRPFUSECFG_RPC);
    if (IsCtrlMultiVC (ControllerIndex)) {
      DEBUG ((DEBUG_INFO, "PCIe SP%c is %a\n", (UINTN) ('A' + ControllerIndex), mPcieMVCControllerConfigName[Config]));
    } else {
      DEBUG ((DEBUG_INFO, "PCIe SP%c is %a\n", (UINTN) ('A' + ControllerIndex), mPcieControllerConfigName[Config]));
    }
    return Config;
  }
}

/**
  Programs Isolated Memory Region feature.
  PCIe IMR is programmed in a PCH rootport, based on data retrieved from CPU registers.

  @param[in] RpIndex     Root Port Number (0-based)
  @param[in] Rs3Bus      Bus number for IMR. All PCIE data on RS3 will be identified by this bus number
**/
VOID
EnablePcieImr (
  UINT8  RpIndex,
  UINT8  Rs3Bus
  )
{
  UINT32       ImrBaseLow;
  UINT32       ImrBaseHigh;
  UINT32       ImrLimitLow;
  UINT32       ImrLimitHigh;
  PCI_IMR_HOB  *PciImrHob;
  PCH_SBI_PID  ControllerPid;
  UINT32       Data32;
  UINT64       ImrLimit;

  DEBUG ((DEBUG_INFO, "EnablePcieImr: RP %d, bus %d\n", RpIndex, Rs3Bus));

  PciImrHob = NULL;
  PciImrHob = GetFirstGuidHob (&gPciImrHobGuid);
  if (PciImrHob == NULL) {
    DEBUG ((DEBUG_INFO, "EnablePcieImr: no HOB\n"));
    return;
  }
  //
  // Sanity check - don't program PCIe IMR if base address is 0
  //
  if (PciImrHob->PciImrBase == 0) {
    DEBUG ((DEBUG_ERROR, "PcieImr base address is 0, IMR programming skipped!\n"));
    return;
  }
  ImrLimit = PciImrHob->PciImrBase + (GetPcieImrSize () << 20);
  ImrBaseLow   = (UINT32) RShiftU64 ((PciImrHob->PciImrBase & 0xFFF00000), 20);
  ImrBaseHigh  = (UINT32) RShiftU64 (PciImrHob->PciImrBase, 32);
  ImrLimitLow  = (UINT32) RShiftU64 ((ImrLimit & 0xFFF00000), 20);
  ImrLimitHigh = (UINT32) RShiftU64 (ImrLimit, 32);
  //
  // PCIe IMR base & limit registers in PCH contain bits 63:20 of adress, divided into upper (64:32) and lower (31:20) parts
  // That means bits 19:10 are ignored and addresses are aligned to 1MB.
  //
  ControllerPid = PchGetPcieControllerSbiPid (GetControllerIndex (RpIndex));

  if (IsRpMultiVC (RpIndex)) {
    Data32 = Rs3Bus | (ImrBaseLow << N_SPX_MVC_PCR_IMRAMBL_IAMB) | (ImrLimitLow << N_SPX_MVC_PCR_IMRAMBL_IAML);
    PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_IMRAMBL, Data32);
    PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_IMRAMBU32, ImrBaseHigh);
    PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_IMRAMLU32, ImrLimitHigh);
    PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_IMRAMLE, (BIT0 << (GetControllerRpIndex(RpIndex))) | B_SPX_MVC_PCR_IMRAMLE_SRL);
    PsfSetRs3Bus (Rs3Bus);

    DEBUG ((DEBUG_INFO, "IMR registers: PID %x, +10=%08x, +14=%08x, +18=%08x, +1c=%08x %d\n",
      ControllerPid,
      PchPcrRead32(ControllerPid, R_SPX_MVC_PCR_IMRAMBL),
      PchPcrRead32(ControllerPid, R_SPX_MVC_PCR_IMRAMBU32),
      PchPcrRead32(ControllerPid, R_SPX_MVC_PCR_IMRAMLU32),
      PchPcrRead32(ControllerPid, R_SPX_MVC_PCR_IMRAMLE)
    ));
  } else {
    Data32 = Rs3Bus | (ImrBaseLow << N_SPX_PCR_IMRAMBL_IAMB) | (ImrLimitLow << N_SPX_PCR_IMRAMBL_IAML);
    PchPcrWrite32 (ControllerPid, R_SPX_PCR_IMRAMBL, Data32);
    PchPcrWrite32 (ControllerPid, R_SPX_PCR_IMRAMBU32, ImrBaseHigh);
    PchPcrWrite32 (ControllerPid, R_SPX_PCR_IMRAMLU32, ImrLimitHigh);
    PchPcrWrite32 (ControllerPid, R_SPX_PCR_IMRAMLE, (BIT0 << (GetControllerRpIndex(RpIndex))) | B_SPX_PCR_IMRAMLE_SRL);
    PsfSetRs3Bus (Rs3Bus);

    DEBUG ((DEBUG_INFO, "IMR registers: PID %x, +10=%08x, +14=%08x, +18=%08x, +1c=%08x %d\n",
      ControllerPid,
      PchPcrRead32(ControllerPid, R_SPX_PCR_IMRAMBL),
      PchPcrRead32(ControllerPid, R_SPX_PCR_IMRAMBU32),
      PchPcrRead32(ControllerPid, R_SPX_PCR_IMRAMLU32),
      PchPcrRead32(ControllerPid, R_SPX_PCR_IMRAMLE)
    ));
  }
}

/**
  This function assigns bus number to PCIe bus .

  @param[in] RpIndex     Root Port index
**/
VOID
AssignTemporaryBus (
  IN UINT64 RpBase,
  IN UINT8  TempPciBus
  )
{
  UINT64 EpBase;
  //
  // Assign bus numbers to the root port
  //
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
}

/**
  Clear temp bus usage.

  @param[in] RpBase     Root Port PCI base address
**/
VOID
ClearBus (
  IN UINT64 RpBase
  )
{
  PciSegmentAnd32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN
    );
}

/**
  This function sets Common Clock Mode bit in rootport and endpoint connected to it, if both sides support it.
  This bit influences rootport's Gen3 training and should be set before Gen3 software equalization is attempted.
  It does not attempt to set CCC in further links behind rootport

  @param[in] RpIndex     Root Port index
**/
VOID
EnableCommonClock (
  IN UINT32 RpIndex,
  IN UINT8  TempPciBus
  )
{
  UINTN  RpDevice;
  UINTN  RpFunction;
  UINT64 RpBase;
  UINT64 EpBase;
  UINT8  Func;
  UINT8  EpPcieCapOffset;

  //
  // If endpoint gets reset as result of Gen3 training, it will forget all its config including CCC
  // while rootport will keep CCC set. The inconsistency will fix itself slightly later in boot flow when
  // PchPcieInitRootPortDownstreamDevices() is called
  //
  GetPchPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
  RpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, RpDevice, RpFunction, 0);
  AssignTemporaryBus (RpBase, TempPciBus);
  EpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, 0, 0);
  //
  // The piece of code below used to be under "if (IsDevicePresent (EpBase))" check
  // which failed to detect Thunderbolt devices (they report DeviceID=0xFFFF)
  // That check helped readability but wasn't necessary - if endpoint is really missing,
  // PcieBaseFindCapId will return 0 and CCC programming will not execute anyway
  //
  EpPcieCapOffset = PcieBaseFindCapId (EpBase, EFI_PCI_CAPABILITY_ID_PCIEXP);
  if (GetScc (RpBase, R_PCH_PCIE_CFG_CLIST) && (EpPcieCapOffset != 0) && GetScc (EpBase, EpPcieCapOffset)) {
    EnableCcc (RpBase, R_PCH_PCIE_CFG_CLIST);
    EnableCcc (EpBase, EpPcieCapOffset);
    if (IsMultifunctionDevice (EpBase)) {
      for (Func = 1; Func <= PCI_MAX_FUNC; Func++) {
        EpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, Func, 0);
        EnableCcc (EpBase, PcieBaseFindCapId (EpBase, EFI_PCI_CAPABILITY_ID_PCIEXP));
      }
    }
    RetrainLink (RpBase, R_PCH_PCIE_CFG_CLIST, TRUE);
  }
  ClearBus (RpBase);
}
/**
  This function determines whether root port is configured in non-common clock mode.
  Result is based on the NCC soft-strap setting.

  @param[in] RpBase      Root Port pci segment base address

  @retval TRUE           Port in NCC SSC mode.
  @retval FALSE          Port not in NCC SSC mode.
**/
BOOLEAN
IsPcieNcc (
  IN     UINT64  RpBase
  )
{
  if (PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_SCC) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Determines whether PCIe link is active

  @param[in] RpBase    Root Port base address
  @retval Link Active state
**/
STATIC
BOOLEAN
IsLinkActive (
  UINT64  RpBase
  )
{
  return !! (PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA);
}

/**
  This function checks if de-emphasis needs to be changed from default for a given rootport

  @param[in] PortIndex    Root Port number
  @param[in] PcieConfig   Pointer to a PCH_PCIE_CONFIG that provides the platform setting
  @param[in] DevInfo      Information on device that is connected to rootport

  @retval TRUE            De-emphasis needs to be changed
  @retval FALSE           No need to change de-emphasis
**/
BOOLEAN
NeedDecreasedDeEmphasis (
  IN PCIE_DEVICE_INFO      DevInfo
  )
{
  //
  // Intel WiGig devices
  //
  if (DevInfo.Vid == V_PCH_INTEL_VENDOR_ID && DevInfo.Did == 0x093C) {
    return TRUE;
  }
  return FALSE;
}

/**
  Detect whether CLKREQ# is supported by the platform and device.

  Assumes device presence. Device will pull CLKREQ# low until CPM is enabled.
  Test pad state to verify that the signal is correctly connected.
  This function will change pad mode to GPIO!

  @param[in] RootPortConfig      Root port configuration
  @param[in] DevicePresent       Determines whether there is a device on the port

  @retval TRUE if supported, FALSE otherwise.
**/
BOOLEAN
PcieDetectClkreq (
  IN       UINT32          RpIndex,
  IN CONST PCH_PCIE_CONFIG *PcieConfig
  )
{
  if (!IsClkReqAssigned (PchClockUsagePchPcie0 + RpIndex)) {
    return FALSE;
  }
  if (PcieConfig->RootPort[RpIndex].ClkReqDetect &&
      EFI_ERROR (CheckClkReq (PchClockUsagePchPcie0 + RpIndex))) {
    DEBUG ((DEBUG_INFO, "CLKREQ is not Low, disabling power management for RP %d.\n", RpIndex));
    return FALSE;
  }
  return TRUE;
}

/**
  Disables the root port. Depending on 2nd param, port's PCI config space may be left visible
  to prevent function swapping

  Use sideband access unless the port is still available.

  @param[in] PortIndex          Root Port Number
  @param[in] KeepPortVisible    Should the port' interface be left visible on PCI Bus0
**/
VOID
DisablePcieRootPort (
  IN UINT8   RpIndex,
  IN BOOLEAN KeepPortVisible
  )
{
  UINT32      Data32;
  UINT32      LoopTime;
  UINT32      TargetState;
  UINT32      LinkActive;

  DEBUG ((DEBUG_INFO, "DisablePcieRootPort(%d) Start\n", RpIndex + 1));

  Data32 = 0;

  PchSbiRpPciRead32 (RpIndex, (R_PCH_PCIE_CFG_LSTS-2), &Data32);//access LSTS using dword-aligned read
  LinkActive = (Data32 >> 16) & B_PCIE_LSTS_LA;

  if (LinkActive) {
    ///
    /// If device is present disable the link.
    ///
    DEBUG ((DEBUG_INFO, "Disabling the link.\n"));
    PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_LCTL, ~0u, B_PCIE_LCTL_LD);
  } else {
    ///
    /// Otherwise if device is not present perform the following steps using sideband access:
    /// 1.  Set B0:Dxx:Fn:338h[26] = 1b
    /// 2.  Poll B0:Dxx:Fn:328h[31:24] until 0x1 with 50ms timeout
    /// 3.  Set B0:Dxx:Fn +408h[27] =1b
    ///

    DEBUG ((DEBUG_INFO, "Stopping the port.\n"));
    PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCIEALC, ~0u, B_PCH_PCIE_CFG_PCIEALC_BLKDQDA);

    TargetState = V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_DETRDY;
    for (LoopTime = 0; LoopTime < 5000; LoopTime++) {
      PchSbiRpPciRead32 (RpIndex, R_PCH_PCIE_CFG_PCIESTS1, &Data32);
      if (((Data32 & B_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE) >> N_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE) == TargetState) {
        break;
      }
      MicroSecondDelay (10);
    }

    //
    // Show polling status
    //
    if (LoopTime > 0) {
      DEBUG ((DEBUG_INFO, "Polling for DETRDY for %dus. PCIESTS1 = 0x%08x\n", LoopTime*10, Data32));
    }
  }
  ///
  /// Set offset 408h[27] to 1b to disable squelch.
  ///
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PHYCTL4, ~0u, B_PCH_PCIE_CFG_PHYCTL4_SQDIS);

  ///
  /// Make port disappear from PCI bus
  ///
  if (!KeepPortVisible) {
    DEBUG ((DEBUG_INFO, "Hiding the port\n"));
    ///
    /// PCIe RP IOSF Sideband register offset 0x00[19:16], depending on the port that is Function Disabled
    /// Access it by offset 0x02[4:0] to avoid RWO bit
    ///
    if (IsRpMultiVC (RpIndex)) {
      PchPcrAndThenOr8 (
        GetRpSbiPid (RpIndex),
        R_SPX_MVC_PCR_PCD + 0x02,
        0x0F,
        (UINT8) (1 << (RpIndex % 4))
        );
    } else {
      PchPcrAndThenOr8 (
        GetRpSbiPid (RpIndex),
        R_SPX_PCR_PCD + 0x02,
        0x0F,
        (UINT8) (1 << (RpIndex % 4))
        );
    }
    ///
    /// Then disable the port in PSF
    ///
    PsfDisablePcieRootPort (RpIndex);
  }
  ///
  /// Function disable PCIE port in PMC
  ///
  PmcDisablePcieRootPort (RpIndex);
  DisableClock (PchClockUsagePchPcie0 + RpIndex);
  DEBUG ((DEBUG_INFO, "DisablePcieRootPort() End\n"));
}

/**
  This function creates Capability and Extended Capability List

  @param[in] RpIndex         Root Port index
  @param[in] RpBase          Root Port pci segment base address
  @param[in] PcieRpConfig    Pointer to a PCH_PCIE_CONFIG that provides the platform setting

**/
VOID
InitCapabilityList (
  IN UINT32                           RpIndex,
  IN UINT64                           RpBase,
  IN CONST PCH_PCIE_ROOT_PORT_CONFIG  *PcieRpConfig
  )
{
  UINT32      Data32;
  UINT16      Data16;
  UINT8       Data8;
  UINT16      NextCap;

  ///
  /// Build Capability linked list
  /// 1.  Read and write back to capability registers 34h, 41h, 81h and 91h using byte access.
  /// 2.  Program NSR, A4h[3] = 0b
  ///
  Data8 = PciSegmentRead8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET);
  PciSegmentWrite8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET, Data8);

  Data16 = PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_CLIST);
  PciSegmentWrite16 (RpBase + R_PCH_PCIE_CFG_CLIST, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_MID);
  PciSegmentWrite16 (RpBase + R_PCH_PCIE_CFG_MID, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_SVCAP);
  PciSegmentWrite16 (RpBase + R_PCH_PCIE_CFG_SVCAP, Data16);

  Data32 = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_PMCS);
  Data32 &= (UINT32) ~(B_PCIE_PMCS_NSR);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_PMCS, Data32);

  /*
  a. NEXT_CAP = 0h
  */
  NextCap     = V_PCIE_EXCAP_NCO_LISTEND;


  /*
  b. If Downstream Port Containment is enabled, then
    1. Set Next Capability Offset, Dxx:Fn +250h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +250h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +250h[15:0] = 001h
    4. NEXT_CAP = 250h
    ELSE, set Dxx:Fn +250h [31:0] = 0

  */
  Data32 = 0;
  if (PcieRpConfig->DpcEnabled == TRUE) {
    Data32  = (V_PCH_PCIE_CFG_EX_DPCECH_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_DPC_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCH_PCIE_CFG_EX_DPCECH;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_DPCECH, Data32);
  /*
    Set DPC capabilities
  */
  if (PcieRpConfig->DpcEnabled == TRUE) {
    Data32 = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EX_DPCECH + R_PCIE_EX_DPC_CAP_OFFSET);
    Data32 &= ~BIT5;
    if (PcieRpConfig->RpDpcExtensionsEnabled == TRUE) {
      Data32 |= BIT5;
    }
  } else {
    Data32 = 0;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_DPCECH + R_PCIE_EX_DPC_CAP_OFFSET, Data32);

  /*
  c. If the RP is GEN3 capable (by fuse and BIOS policy), enable Secondary PCI Express Extended Capability
    1. Set Next Capability Offset, Dxx:Fn +220h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +220h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +220h[15:0] = 0019h
    4. NEXT_CAP = 220h
    ELSE, set Dxx:Fn +220h [31:0] = 0
  */

  Data32 = 0;
  if (GetMaxLinkSpeed (RpBase) >= V_PCIE_LCAP_MLS_GEN3) {
    Data32  = (V_PCH_PCIE_CFG_EX_SPEECH_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_SPE_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCH_PCIE_CFG_EX_SPEECH;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_SPEECH, Data32);

  /*
  d. If support L1 Sub-State
    1. Set Next Capability Offset, Dxx:Fn +200h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +200h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +200h[15:0] = 001Eh
    4. Read and write back to Dxx:Fn +204h
    5. Refer to section 8.3 for other requirements (Not implemented here)
    6. NEXT_CAP = 200h
    ELSE, set Dxx:Fn +200h [31:0] = 0, and read and write back to Dxx:Fn +204h
  */

  Data32 = 0;
  if (IsClkReqAssigned (PchClockUsagePchPcie0 + RpIndex) &&
      (PcieRpConfig->L1Substates != PchPcieL1SubstatesDisabled)) {
    Data32  = (V_PCH_PCIE_CFG_EX_L1S_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_L1S_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCH_PCIE_CFG_EX_L1SECH;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_L1SECH, Data32);

  Data32 = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EX_L1SCAP);
  if (PcieRpConfig->L1Substates == PchPcieL1SubstatesDisabled) {
    Data32 &= (UINT32) ~(0x1F);
  } else if (PcieRpConfig->L1Substates == PchPcieL1SubstatesL1_1) {
    Data32 &= (UINT32) ~(BIT0 | BIT2);
  }
  //
  // Set TpowerOn capability to 44us
  // [1208708498]
  //
  Data32 &= ~(B_PCIE_EX_L1SCAP_PTV | B_PCIE_EX_L1SCAP_PTPOS);
  Data32 |=  (22 << N_PCIE_EX_L1SCAP_PTV) | (V_PCIE_EX_L1SCAP_PTPOS_2us << N_PCIE_EX_L1SCAP_PTPOS) | B_PCIE_EX_L1SCAP_L1SSES;
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_L1SCAP, Data32);

  /*
  e. If It is EHL PCH, and only for Multi VC PCIe Controller: SPB, SPC and SPD
  1. Set Next Capability Offset, 0x280[31:20] = NEXT_CAP
  2. Set Capability Version, 0x280[19:16] = 1h
  3. Set Capability ID, 0x280[15:0] = 002h
  4. NEXT_CAP = 0x280
  ELSE, set 0x280 [31:0] = 0
  */
  Data32 = 0;
  if ((PchGeneration () == EHL_PCH) && IsRpMultiVC (RpIndex) && PcieRpConfig->MultiVcEnabled == TRUE) {
    Data32 = (V_PCIE_EX_VC_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_VC_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCIE_MVC_VCECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_MVC_VCECH, Data32);

  /*
  f. If support PTM
    1. Set Next Capability Offset, Dxx:Fn +150h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +140h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +140h[15:0] = 001Fh
    4. Read and write back to Dxx:Fn +144h
    5. NEXT_CAP = 140h
    ELSE, set Dxx:Fn +150h [31:0] = 0
    In both cases: read Dxx:Fn + 154h, set BIT1 and BIT2 then write it back
  */
  Data32 = 0;
  if (PcieRpConfig->PtmEnabled == TRUE) {
    Data32 = (V_PCH_PCIE_CFG_EX_PTM_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_PTM_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCH_PCIE_CFG_EX_PTMECH;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_PTMECH, Data32);
  Data32 = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EX_PTMCAPR);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_PTMCAPR, (Data32 | B_PCIE_EX_PTMCAP_PTMRC | B_PCIE_EX_PTMCAP_PTMRSPC));

  /*
  f. If support ACS
    1. Set Next Capability Offset, Dxx:Fn +140h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +140h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +140h[15:0] = 000Dh
    4. Read and write back to Dxx:Fn +144h
    5. NEXT_CAP = 140h
    ELSE, set Dxx:Fn +140h [31:0] = 0, and read and write back to Dxx:Fn +144h
  */
  Data32 = 0;
  if (PcieRpConfig->AcsEnabled == TRUE) {
    Data32 = (V_PCH_PCIE_CFG_EX_ACS_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_ACS_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCH_PCIE_CFG_EX_ACSECH;
  }
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_ACSECH, Data32);

  Data32 = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EX_ACSCAPR);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_ACSCAPR, Data32);

  /*
  g. If support Advanced Error Reporting
    1. Set Next Capability Offset, Dxx:Fn +100h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +100h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +100h[15:0] = 0001h
    ELSE
    1. Set Next Capability Offset, Dxx:Fn +100h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +100h[19:16]  = 0h
    3. Set Capability ID, Dxx:Fn +100h[15:10]  = 0000h
  */

  Data32 = 0;
  if (PcieRpConfig->AdvancedErrorReporting) {
    Data32 = (V_PCH_PCIE_CFG_EX_AEC_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_AEC_CID;
  }
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EX_AECH, Data32);

}

/**
  The function to change the root port speed

  @retval EFI_SUCCESS             Succeeds.
**/
EFI_STATUS
PcieRpSpeedChange (
  VOID
  )
{
  EFI_STATUS            Status;
  UINTN                 PortIndex;
  UINTN                 PchMaxPciePortNum;
  UINT64                PciRootPortRegBase[PCH_MAX_PCIE_ROOT_PORTS];
  UINTN                 RpDev;
  UINTN                 RpFunc;
  UINTN                 LinkRetrainedBitmap;
  UINTN                 TimeoutCount;
  UINT32                MaxLinkSpeed;

  PchMaxPciePortNum = GetPchMaxPciePortNum ();
  //
  // Since we are using the root port base many times, it is best to cache them.
  //
  for (PortIndex = 0; PortIndex < PchMaxPciePortNum; PortIndex++) {
    PciRootPortRegBase[PortIndex] = 0;
    Status = GetPchPcieRpDevFun (PortIndex, &RpDev, &RpFunc);
    if (EFI_ERROR (Status)) {
      ASSERT (FALSE);
      continue;
    }
    PciRootPortRegBase[PortIndex] = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, (UINT32) RpDev, (UINT32) RpFunc, 0);
  }

  ///
  /// PCH BIOS Spec Section 8.14 Additional PCI Express* Programming Steps
  /// NOTE: Detection of Non-Complaint PCI Express Devices
  ///
  LinkRetrainedBitmap = 0;
  for (PortIndex = 0; PortIndex < PchMaxPciePortNum; PortIndex++) {
    if (PciRootPortRegBase[PortIndex] == 0) {
      continue;
    }
    if (PciSegmentRead16 (PciRootPortRegBase[PortIndex] + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }

    MaxLinkSpeed = GetMaxLinkSpeed (PciRootPortRegBase[PortIndex]);

    if (MaxLinkSpeed > 1) {
      PciSegmentAndThenOr16 (
        PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LCTL2,
        (UINT16) ~B_PCIE_LCTL2_TLS,
        (UINT16) MaxLinkSpeed
        );
      if (IsLinkActive (PciRootPortRegBase[PortIndex])) {
        //
        // Retrain the link if device is present
        //
        PciSegmentOr16 (PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LCTL, B_PCIE_LCTL_RL);
        LinkRetrainedBitmap |= (1u << PortIndex);
      }
    }
  }

  //
  // 15 ms timeout while checking for link active on retrained link
  //
  for (TimeoutCount = 0; ((LinkRetrainedBitmap != 0) && (TimeoutCount < 150)); TimeoutCount++) {
    //
    // Delay 100 us
    //
    MicroSecondDelay (100);
    //
    // Check for remaining root port which was link retrained
    //
    for (PortIndex = 0; PortIndex < PchMaxPciePortNum; PortIndex++) {
      if ((LinkRetrainedBitmap & (1u << PortIndex)) != 0) {
        //
        // If the link is active, clear the bitmap
        //
        if (PciSegmentRead16 (PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA) {
          LinkRetrainedBitmap &= ~(1u << PortIndex);
        }
      }
    }
  }

  //
  // If 15 ms has timeout, and some link are not active, train to gen1
  //
  if (LinkRetrainedBitmap != 0) {
    for (PortIndex = 0; PortIndex < PchMaxPciePortNum; PortIndex++) {
      if ((LinkRetrainedBitmap & (1u << PortIndex)) != 0) {
        //
        // Set TLS to gen1
        //
        PciSegmentAndThenOr16 (PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LCTL2,
          (UINT16) ~(B_PCIE_LCTL2_TLS),
          V_PCIE_LCTL2_TLS_GEN1);
        //
        // Retrain link
        //
        PciSegmentOr16 (PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LCTL, B_PCIE_LCTL_RL);
      }
    }

    //
    // Wait for retrain completion or timeout in 15ms. Do not expect failure as
    // port was detected and trained as Gen1 earlier
    //
    for (TimeoutCount = 0; ((LinkRetrainedBitmap != 0) && (TimeoutCount < 150)); TimeoutCount++) {
      //
      // Delay 100 us
      //
      MicroSecondDelay (100);
      //
      // Check for remaining root port which was link retrained
      //
      for (PortIndex = 0; PortIndex < PchMaxPciePortNum; PortIndex++) {
        if ((LinkRetrainedBitmap & (1u << PortIndex)) != 0) {
          //
          // If the link is active, clear the bitmap
          //
          if (PciSegmentRead16 (PciRootPortRegBase[PortIndex] + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA) {
            LinkRetrainedBitmap &= ~(1u << PortIndex);
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}

/*
  Checks if given rootport has an endpoint connected

  @param[in] DeviceBase       PCI segment base address of root port

  @retval                     TRUE if endpoint is connected
  @retval                     FALSE if no endpoint was detected
*/
BOOLEAN
IsEndpointConnected (
  UINT64 DeviceBase
  )
{
  return !!(PciSegmentRead16 (DeviceBase + R_PCH_PCIE_CFG_SLSTS) & B_PCIE_SLSTS_PDS);
}

/*
  Some PCIe devices may take long time between they become detected and form a link.
  This function waits until all enabled, non-empty rootports form a link or until a timeout

  @param[in] MaxRootPorts      number of rootports
  @param[in] DisabledPortMask  mask of rootprots that don't need to be considered
*/
VOID
WaitForLinkActive (
  UINT32 MaxRootPorts,
  UINT32 DisabledPortMask
  )
{
  UINT32 PortMask;
  UINT32 Index;
  UINT32 Time;
  UINT64 RpBase;

  Time = 0;
  //
  // Set a bit in PortMask for each rootport that exists and isn't going to be disabled
  //
  PortMask = (0x1 << MaxRootPorts) - 1;
  PortMask &= ~DisabledPortMask;

  DEBUG ((DEBUG_INFO, "WaitForLinkActive, RP mask to wait for = 0x%08x\n", PortMask));
  while (Time < LINK_ACTIVE_POLL_TIMEOUT) {
    for (Index = 0; Index < MaxRootPorts; Index ++) {
      if (!(PortMask & (BIT0 << Index))) {
        continue;
      }
      RpBase = PchPcieBase (Index);
      if ((PciSegmentRead16 (RpBase) == 0xFFFF)) {
        continue;
      }
      //
      // if PDS is not set or if LA is set then this rootport is done - clear it from mask
      //
      if (!IsEndpointConnected (RpBase) || IsLinkActive (RpBase)) {
        PortMask &= ~ (BIT0 << Index);
      }
    }
    if (PortMask == 0x0) {
      DEBUG ((DEBUG_INFO, "WaitForLinkActive, all RPs done, lost %dms waiting\n", Time/1000));
      return;
    }
    MicroSecondDelay (LINK_ACTIVE_POLL_INTERVAL);
    Time += LINK_ACTIVE_POLL_INTERVAL;
  }

  DEBUG ((DEBUG_WARN, "WaitForLinkActive, timeout with the following RPs still not done: 0x%08x\n", PortMask));
}

/**
  Get information about the endpoint

  @param[in]  RpBase      Root port pci segment base address
  @param[in]  TempPciBus  Temporary bus number
  @param[out] DeviceInfo  Device information structure

  @raturn TRUE if device was found, FALSE otherwise
**/
BOOLEAN
GetDeviceInfo (
  IN  UINT64            RpBase,
  IN  UINT8             TempPciBus,
  OUT PCIE_DEVICE_INFO  *DeviceInfo
  )
{
  UINT64                  EpBase;
  UINT32                  Data32;
  UINT8                   EpPcieCapPtr;
  UINT8                   EpLinkSpeed;

  DeviceInfo->Vid = 0xFFFF;
  DeviceInfo->Did = 0xFFFF;
  DeviceInfo->MaxLinkSpeed = 0;

  //
  // Check for device presence
  //
  if (!IsEndpointConnected (RpBase)) {
    return FALSE;
  }

  //
  // Assign temporary bus numbers to the root port
  //
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

  Data32 = PciSegmentRead32 (EpBase + PCI_VENDOR_ID_OFFSET);
  DeviceInfo->Vid = (UINT16) (Data32 & 0xFFFF);
  DeviceInfo->Did = (UINT16) (Data32 >> 16);

  EpLinkSpeed = 0;
  EpPcieCapPtr = PcieFindCapId (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, 0, EFI_PCI_CAPABILITY_ID_PCIEXP);
  if (EpPcieCapPtr != 0) {
    EpLinkSpeed = PciSegmentRead8 (EpBase + EpPcieCapPtr + R_PCIE_LCAP_OFFSET) & B_PCIE_LCAP_MLS;
  }
  DeviceInfo->MaxLinkSpeed = EpLinkSpeed;

  //
  // Clear bus numbers
  //
  PciSegmentAnd32 (RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN);

  DEBUG ((DEBUG_INFO, "VID: %04X DID: %04X  MLS: %d\n",
          DeviceInfo->Vid, DeviceInfo->Did, DeviceInfo->MaxLinkSpeed));

  return (Data32 != 0xFFFFFFFF);
}

/**
  Program controller power management settings.
  This settings are relevant to all ports including disabled ports.
  All registers are located in the first port of the controller.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex               The root port to be initialized (zero based).
  @param[in]  TrunkClockGateEn      Indicates whether trunk clock gating is to be enabled,
                                    requieres all controller ports to have dedicated CLKREQ#
                                    or to be disabled.
**/
VOID
PcieConfigureControllerBasePowerManagement (
  IN  UINT32   RpIndex,
  IN  BOOLEAN  TrunkClockGateEn
  )
{
  UINT32      Data32And;
  UINT32      Data32Or;

  DEBUG ((DEBUG_INFO, "PcieConfigureControllerBasePowerManagement(%d)\n", RpIndex + 1));

  ASSERT ((GetControllerRpIndex (RpIndex)) == 0);

  ///
  /// Set E1h[7,5,4,2] to 1111b   (R_PCH_PCIE_CFG_RPDCGEN)
  /// Set E2h[4] to 1b            (R_PCH_PCIE_CFG_RPPGEN)
  /// Set E1h[6] to 1b if all ports on the controller support CLKREQ#   (R_PCH_PCIE_CFG_RPDCGEN)
  ///
  Data32Or  = (B_PCH_PCIE_CFG_RPDCGEN_RPSCGEN | B_PCH_PCIE_CFG_RPDCGEN_LCLKREQEN |
               B_PCH_PCIE_CFG_RPDCGEN_BBCLKREQEN | B_PCH_PCIE_CFG_RPDCGEN_SRDBCGEN) << 8;
  Data32Or |= B_PCH_PCIE_CFG_RPPGEN_SEOSCGE << 16;
  if (TrunkClockGateEn) {
    DEBUG ((DEBUG_INFO, "Setting PTOCGE\n"));
    Data32Or |= (B_PCH_PCIE_CFG_RPDCGEN_PTOCGE << 8);
  }
  PchSbiRpPciAndThenOr32 (RpIndex, 0xE0, ~0u, Data32Or);

  ///
  /// Set E8h[17,15] to [1,1]
  ///
  Data32Or = B_PCH_PCIE_CFG_PWRCTL_WPDMPGEP | B_PCH_PCIE_CFG_PWRCTL_DBUPI;
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PWRCTL, ~0u, Data32Or);
  ///
  /// Set F5h[1:0] to 11b  (R_PCH_PCIE_CFG_PHYCTL2)
  /// Set F7h[3:2] = 00b   (R_PCH_PCIE_CFG_IOSFSBCS)
  ///
  Data32And = (UINT32) ~(B_PCH_PCIE_CFG_IOSFSBCS_SIID << 24);
  Data32Or = (B_PCH_PCIE_CFG_PHYCTL2_PXPG3PLLOFFEN | B_PCH_PCIE_CFG_PHYCTL2_PXPG2PLLOFFEN) << 8;
  PchSbiRpPciAndThenOr32 (RpIndex, 0xF4, Data32And, Data32Or);

  ///
  /// Set 424h[11] to 1b
  ///
  Data32Or = B_PCH_PCIE_CFG_PCIEPMECTL2_PHYCLPGE;
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCIEPMECTL2, ~0u, Data32Or);

  ///
  /// Set 428h[5] to 1b
  /// Set 428h[0] to 0b
  Data32And = (UINT32) ~B_PCH_PCIE_CFG_PCE_PMCRE;
  Data32Or = B_PCH_PCIE_CFG_PCE_HAE;
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCE, Data32And, Data32Or);

  ///
  /// Set 42Ch[11:10] to 0x3
  ///
  Data32Or = BIT11 | BIT10;
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PGCBCTL1, ~0u, Data32Or);
}


/**
  Configure power management settings whcih are applicable to both enabled and disabled ports.
  This settings are relevant to all ports including disabled ports.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex               The root port to be initialized (zero based).
  @param[in]  PhyLanePgEnable       Indicates whether PHY lane power gating is to be enabled,
                                    requires CLKREQ# to supported by the port or the port to be disabled.
**/
VOID
PcieConfigurePortBasePowerManagement (
  IN  UINT32   RpIndex,
  IN  BOOLEAN  PhyLanePgEnable
  )
{

  UINT32      Data32;
  UINT32      Data32And;
  UINT32      Data32Or;

  DEBUG ((DEBUG_INFO, "PchPcieConfigureBasePowerManagement(%d) Start\n", RpIndex + 1));

  ///
  /// Set E1h[1:0] = 11b    (R_PCH_PCIE_CFG_RPDCGEN)
  ///
  Data32Or = (B_PCH_PCIE_CFG_RPDCGEN_RPDLCGEN | B_PCH_PCIE_CFG_RPDCGEN_RPDBCGEN) << 8;
  PchSbiRpPciAndThenOr32 (RpIndex, 0xE0, ~0u, Data32Or);

  ///
  /// Set F7h[6] to 1b     (R_PCH_PCIE_CFG_IOSFSBCS)
  ///
  Data32Or = B_PCH_PCIE_CFG_IOSFSBCS_SCPTCGE << 24;
  PchSbiRpPciAndThenOr32 (RpIndex, 0xF4, ~0u, Data32Or);

  DEBUG_CODE_BEGIN ();
  //
  // Ensure PHYCLPGE is set before DLSULPPGE and FDPPGE
  //
  PchSbiRpPciRead32 (PchGetPcieFirstPortIndex (RpIndex), R_PCH_PCIE_CFG_PCIEPMECTL2, &Data32);
  DEBUG_CODE_END ();

  ///
  /// Set 420h[31] = 1b
  /// If CLKREQ# is supported or port is disabled set 420h[30,29] to 11b.
  /// 420h[29] (DLSULDLSD) and 420h[0] must be set if DLSULPPGE is set or PTOCGE is set.
  /// Assume that if PTOCGE is set CLKREQ is supported on this port.
  /// L1.LOW is disabled; if all conditions are met, it will be enabled later.
  ///
  Data32Or  = B_PCH_PCIE_CFG_PCIEPMECTL_FDPPGE;
  Data32And = (UINT32) ~(B_PCH_PCIE_CFG_PCIEPMECTL_L1LE);
  if (PhyLanePgEnable) {
    DEBUG ((DEBUG_INFO, "Setting DLSULPPGE+DLSULDLSD.\n"));
    Data32Or |= B_PCH_PCIE_CFG_PCIEPMECTL_DLSULPPGE | B_PCH_PCIE_CFG_PCIEPMECTL_DLSULDLSD | B_PCH_PCIE_CFG_PCIEPMECTL_L1FSOE;
  }
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCIEPMECTL, Data32And, Data32Or);

  ///
  /// Set 424h[8,7] to 11b
  ///
  Data32Or = B_PCH_PCIE_CFG_PCIEPMECTL2_FDCPGE | B_PCH_PCIE_CFG_PCIEPMECTL2_DETSCPGE | B_PCH_PCIE_CFG_PCIEPMECTL2_DISSCPGE;
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCIEPMECTL2, ~0u, Data32Or);

  ///
  /// Vnn Removal register programming
  ///
  Data32Or = (B_PCH_PCIE_CFG_VNNREMCTL_FDVNNRE | B_PCH_PCIE_CFG_VNNREMCTL_HPVNNRE | B_PCH_PCIE_CFG_VNNREMCTL_DNPVNNRE
              | B_PCH_PCIE_CFG_VNNREMCTL_RTD3VNNRE | B_PCH_PCIE_CFG_VNNREMCTL_LDVNNRE
              | (V_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE_16_OSC_CLK << N_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE) | (V_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE_8_OSC_CLK));
  PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_VNNREMCTL, ~0u, Data32Or);
}

/**
  Get max link width.

  @param[in] RpBase    Root Port base address
  @retval Max link width
**/
UINT8
GetMaxLinkWidth (
  UINT64  RpBase
  )
{
  UINT8  LinkWidth;
  LinkWidth = (UINT8) ((PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_LCAP) & B_PCIE_LCAP_MLW) >> N_PCIE_LCAP_MLW);
  ASSERT (LinkWidth <= 4);
  if (LinkWidth > 4) {
    LinkWidth = 4;
  }
  return LinkWidth;
}

/**
  Initialize non-common clock port.
  Ports with NCC configuration need to have their mPHY lanes reconfigured by BIOS before
  endpoint detection can start. Reconfiguration is instant, but detection may take up to
  100ms. In order to save as much time as possible, this reconfiguration should be executed
  in PEI pre-mem, so that detection happens in parallel with memory init
  @param[in] RpIndex    Root Port index
**/
VOID
PcieInitNccPort (
  IN UINT32   RpIndex
  )
{
  UINT64     RpBase;
  UINT32     RpLaneIndex;
  UINT32     MaxLinkWidth;
  HSIO_LANE  HsioLane;
  UINT8      FiaLane;

  DEBUG ((DEBUG_INFO, "PcieInitNccPort(%d)\n", RpIndex+1));

  RpBase = PchPcieBase (RpIndex);
  MaxLinkWidth = GetMaxLinkWidth (RpBase);
  for (RpLaneIndex = 0; RpLaneIndex < MaxLinkWidth; ++RpLaneIndex) {
    if (PchFiaGetPcieRootPortLaneNum (RpIndex, RpLaneIndex, &FiaLane)) {
      HsioGetLane (FiaLane, &HsioLane);
      HsioPcieNccLaneInit (&HsioLane);
    }
  }
  PciSegmentAnd32 (RpBase + R_PCH_PCIE_CFG_PCIEALC, (UINT32) ~B_PCH_PCIE_CFG_PCIEALC_BLKDQDA);
}

/**
  Verify whether the PCIe port does own all lanes according to the port width.
  @param[in] RpBase    Root Port base address
**/
BOOLEAN
IsPciePortOwningLanes (
  IN     UINT64   RpBase
  )
{
  UINT32     MaxLinkWidth;
  UINT32     RpLaneIndex;
  UINT32     RpIndex;
  UINT32     FiaLanesFlip;

  RpIndex      = PciePortIndex (RpBase);

  if (IsRpMultiVC(RpIndex)) {
    FiaLanesFlip = PchPcrRead32(PID_FIA, R_PCH_FIA_15_PCR_DFLEXORM);
    RpLaneIndex = 0;

    //
    // To check the FIA lane reverse condition
    //
    switch (RpIndex) {
      case 4:  // Multi VC Controller 1
        if ((FiaLanesFlip & BIT4) || (FiaLanesFlip & BIT5)) {  // Lane 8,9 or Lane 10,11
          RpLaneIndex = 1;
        }
        break;
      case 5:  // Multi VC Controller 2
        if ((FiaLanesFlip & BIT1) || (FiaLanesFlip & BIT2)) {  // Lane 2,3 or Lane 4,5
          RpLaneIndex = 1;
        }
        break;
      case 6:  // Multi VC Controller 3
        if ((FiaLanesFlip & BIT3)) {  // Lane 6,7
          RpLaneIndex = 1;
        }
        break;
      default:
        RpLaneIndex = 0;
        break;
    }

    //
    // Just check for 1 lane since Multi VC is only x2. As long as a lane
    // is PCIe, it is connected.
    //
    if (!PchFiaIsPcieRootPortLaneConnected (RpIndex, RpLaneIndex)) {
      return FALSE;
    }
  }
  else {
    MaxLinkWidth = GetMaxLinkWidth(RpBase);
    for (RpLaneIndex = 0; RpLaneIndex < MaxLinkWidth; ++RpLaneIndex) {
      if (!PchFiaIsPcieRootPortLaneConnected (RpIndex, RpLaneIndex)) {
        return FALSE;
      }
    }
  }

  return TRUE;
}

/**
  Check for device presence with timeout.

  @param[in]     RpBase      Root Port base address
  @param[in]     TimeoutUs   Timeout in microseconds
  @param[in,out] Timer       Timer value, must be initialized to zero
                             before the first call of this function.
**/
BOOLEAN
IsPcieDevicePresent (
  IN     UINT64  RpBase,
  IN     UINT32  TimeoutUs,
  IN OUT UINT32  *Timer
  )
{
  while (TRUE) {
    if (IsEndpointConnected (RpBase)) {
      return TRUE;
    }
    if (*Timer < TimeoutUs) {
      MicroSecondDelay (10);
      *Timer += 10;
    } else {
      break;
    }
  }
  return FALSE;
}

/**
  Checks if given rootport should be left visible even though disabled, in order to avoid PCIE rootport swapping

  @param[in] RpIndex           rootport number
  @param[in] RpDisableMask     bitmask of all disabled rootports
  @param[in] PciExpressConfig  PCIe policy configuration

  @retval TRUE  port should be kept visible despite being disabled
  @retval FALSE port should be disabled and hidden

**/
BOOLEAN
IsPortForceVisible (
  IN UINT8                 RpIndex,
  IN UINT32                RpDisableMask,
  IN CONST PCH_PCIE_CONFIG *PciExpressConfig
  )
{
  UINT32 FunctionsEnabledPerDevice;
  UINT32 RpEnabledMask;

  //
  // only rootports mapped to Function0 are relevant for preventing rootport swap
  //
  if ((PciExpressConfig->RpFunctionSwap == 1) || (RpIndex % 8 != 0)) {
    return FALSE;
  }
  //
  // set a bit for each port that exists and isn't disabled
  //
  RpEnabledMask = (1u << GetPchMaxPciePortNum ()) - 1;
  RpEnabledMask &= (~RpDisableMask);

  FunctionsEnabledPerDevice = (RpEnabledMask >> ((RpIndex/8)*8)) & 0xFF;
  if (FunctionsEnabledPerDevice != 0) {
    return TRUE;
  }
  return FALSE;
}

/**
  Configure root port function number mapping

**/
VOID
PcieRpConfigureRpfnMapping (
  VOID
  )
{
  UINT8                                 PortIndex;
  UINT8                                 OriginalFuncZeroRp;
  UINT8                                 MaxPciePortNum;
  UINTN                                 DevNum;
  UINTN                                 FuncNum;
  UINT64                                RpBase;
  UINT32                                ControllerPcd[PCH_MAX_PCIE_CONTROLLERS];
  UINT32                                PcieControllers;
  UINT32                                ControllerIndex;
  UINT32                                FirstController;
  PCH_SBI_PID                           ControllerPid;

  DEBUG ((DEBUG_INFO,"PcieRpConfigureRpfnMapping () Start\n"));
  ZeroMem (ControllerPcd, sizeof (ControllerPcd));
  MaxPciePortNum = GetPchMaxPciePortNum ();

  PcieControllers = GetPchMaxPcieControllerNum ();

  for (ControllerIndex = 0; ControllerIndex < PcieControllers; ++ControllerIndex) {
    if (IsCtrlMultiVC (ControllerIndex)) {
      ControllerPcd[ControllerIndex] = PchPcrRead32 (PchGetPcieControllerSbiPid (ControllerIndex), R_SPX_MVC_PCR_PCD);
    } else {
      ControllerPcd[ControllerIndex] = PchPcrRead32 (PchGetPcieControllerSbiPid (ControllerIndex), R_SPX_PCR_PCD);
    }
    DEBUG ((DEBUG_INFO, "SP%c = 0x%08x\n", 'A' + ControllerIndex, ControllerPcd[ControllerIndex]));
  }

  ///
  /// Configure root port function number mapping
  ///
  for (PortIndex = 0; PortIndex < MaxPciePortNum; ) {
    GetPchPcieRpDevFun (PortIndex, &DevNum, &FuncNum);
    RpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, DevNum, FuncNum, 0);
    //
    // Search for first enabled function
    //
    if (PciSegmentRead16 (RpBase) != 0xFFFF) {
      if (FuncNum != 0) {
        //
        // First enabled root port that is not function zero will be swapped with function zero on the same device
        // RP PCD register must sync with PSF RP function config register
        //
        ControllerIndex    = GetControllerIndex (PortIndex);
        OriginalFuncZeroRp = (PortIndex / 8) * 8;
        FirstController    = OriginalFuncZeroRp / 4;
        //
        // The enabled root port becomes function zero
        //
        if (IsCtrlMultiVC (ControllerIndex)) {
          ControllerPcd[ControllerIndex] &= (UINT32) ~(B_SPX_MVC_PCR_PCD_RP1FN << (GetControllerRpIndex (PortIndex) * S_SPX_MVC_PCR_PCD_RP_FIELD));
        } else {
          ControllerPcd[ControllerIndex] &= (UINT32) ~(B_SPX_PCR_PCD_RP1FN << (GetControllerRpIndex (PortIndex) * S_SPX_PCR_PCD_RP_FIELD));
        }
        ControllerPcd[ControllerIndex] |= 0u;
        //
        // Origianl function zero on the same device takes the numer of the current port
        //
        if (IsCtrlMultiVC (FirstController)) {
          ControllerPcd[FirstController] &= (UINT32) ~B_SPX_MVC_PCR_PCD_RP1FN;
        } else {
          ControllerPcd[FirstController] &= (UINT32) ~B_SPX_PCR_PCD_RP1FN;
        }
        ControllerPcd[FirstController] |= (UINT32) FuncNum;
        //
        // Program PSF1 RP function config register.
        //
        PsfSetPcieFunction (OriginalFuncZeroRp, (UINT32) FuncNum);
        PsfSetPcieFunction (PortIndex, 0);
      }
      //
      // Once enabled root port was found move to next PCI device
      //
      PortIndex = ((PortIndex / 8) + 1) * 8;
      continue;
    }
    //
    // Continue search for first enabled root port
    //
    PortIndex++;
  }

  //
  // Write to PCD and lock the register
  //
  for (ControllerIndex = 0; ControllerIndex < PcieControllers; ++ControllerIndex) {
    ControllerPid = PchGetPcieControllerSbiPid (ControllerIndex);
    if (IsCtrlMultiVC (ControllerIndex)) {
      PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_PCD, ControllerPcd[ControllerIndex]);
      PchPcrWrite32 (ControllerPid, R_SPX_MVC_PCR_SRL, B_SPX_MVC_PCR_PCD_SRL);
    } else {
      PchPcrWrite32 (ControllerPid, R_SPX_PCR_PCD, ControllerPcd[ControllerIndex] | B_SPX_PCR_PCD_SRL);
    }
    DEBUG ((DEBUG_INFO, "SP%c = 0x%08x\n", 'A' + ControllerIndex, PchPcrRead32 (ControllerPid, R_SPX_PCR_PCD)));
  }
}

/**
  Checks integrity of Policy settings for all rootports.
  Triggers assert if anything is wrong. For debug builds only

  @param[in] PciExpressConfig     Pointer to PCH_PCIE_CONFIG instance
**/
VOID
PciePolicySanityCheck (
  IN OUT PCH_PCIE_CONFIG *PciExpressConfig
  )
{
  UINT8                       RpIndex;
  PCH_PCIE_ROOT_PORT_CONFIG   *RpConfig;

  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    RpConfig  = &PciExpressConfig->RootPort[RpIndex];
    //
    // Ports with hotplug support must have SlotImplemented bit set
    //
    ASSERT (!RpConfig->HotPlug || RpConfig->SlotImplemented);
  }
}

/**
  Performs mandatory Root Port Initialization.
  This function is silicon-specific and configures proprietary registers.

  @param[in]  PortIndex               The root port to be initialized (zero based)
  @param[in]  SiPolicy                The SI Policy PPI
  @param[in]  TempPciBus              The temporary Bus number for root port initialization
  @param[out] Gen3DeviceFound         Reports if there's Gen3 capable endpoint connected to this rootport
**/
STATIC
VOID
InitPcieSingleRootPort (
  IN  UINT8                                     PortIndex,
  IN  CONST SI_POLICY_PPI                       *SiPolicy,
  IN  SI_PREMEM_POLICY_PPI                      *SiPreMemPolicyPpi,
  IN  UINT8                                     TempPciBus,
  OUT BOOLEAN                                   *Gen3DeviceFound
  )
{
  EFI_STATUS                        Status;
  UINT64                            RpBase;
  UINT32                            Data32Or;
  UINT32                            Data32And;
  UINT16                            Data16;
  UINT16                            Data16Or;
  UINT16                            Data16And;
  UINT8                             Data8Or;
  UINT8                             Data8And;
  UINT32                            Data32;
  PCH_PCIE_CONFIG                   *PcieRpConfig;
  CONST PCH_PCIE_ROOT_PORT_CONFIG   *RootPortConfig;
  VTD_CONFIG                        *VtdConfig;
  UINT32                            Tls;
  PCIE_DEVICE_INFO                  DevInfo;
  UINT8                             RpLinkSpeed;
  UINT32                            RpMaxPayloadCapability;
  BOOLEAN                           RpGen3Capable;
  UINT8                             InterruptPin;
  UINTN                             RpDevice;
  UINTN                             RpFunction;
  PCIE_LINK_EQ_SETTINGS             PcieLinkEqSettings;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gVtdConfigGuid, (VOID *) &VtdConfig);
  ASSERT_EFI_ERROR (Status);

  RootPortConfig  = &PcieRpConfig->RootPort[PortIndex];

  DEBUG ((DEBUG_INFO, "InitPcieSingleRootPort (%d) Start \n", PortIndex + 1));
  RpBase = PchPcieBase (PortIndex);
  GetPchPcieRpDevFun (PortIndex, &RpDevice, &RpFunction);
  RpGen3Capable = FALSE;

  Tls = PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LCTL2) & B_PCIE_LCTL2_TLS;
  ASSERT (Tls <= V_PCIE_LCTL2_TLS_GEN3);

  /// PCH BIOS Spec Section 8.2.10 Completion Retry Status Replay Enable
  /// Following reset it is possible for a device to terminate the
  /// configuration request but indicate that it is temporarily unable to process it,
  /// but in the future. The device will return the Configuration Request Retry Status.
  /// By setting the Completion Retry Status Replay Enable, Dxx:Fn + 320h[22],
  /// the RP will re-issue the request on receiving such status.
  /// The BIOS shall set this bit before first configuration access to the endpoint.
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_PCIECFG2, B_PCH_PCIE_CFG_PCIECFG2_CRSREN);
  //
  // Set speed capability in rootport
  //
  Data8And = (UINT8)(~((UINT8)(B_PCH_PCIE_CFG_MPC_PCIESD >> 8)));
  Data8Or = 0;

  switch (RootPortConfig->PcieSpeed) {
    case PchPcieGen1:
      Data8Or |= (V_PCH_PCIE_CFG_MPC_PCIESD_GEN1 << (N_PCH_PCIE_CFG_MPC_PCIESD - 8));
      break;
    case PchPcieGen2:
      Data8Or |= (V_PCH_PCIE_CFG_MPC_PCIESD_GEN2 << (N_PCH_PCIE_CFG_MPC_PCIESD - 8));
      break;
    case PchPcieGen3:
    case PchPcieAuto:
      break;
  }
  PciSegmentAndThenOr8 (RpBase + R_PCH_PCIE_CFG_MPC + 1, Data8And, Data8Or);

  GetDeviceInfo (RpBase, TempPciBus, &DevInfo);
  *Gen3DeviceFound = ((GetMaxLinkSpeed (RpBase) >= 3) && (DevInfo.MaxLinkSpeed >= 3));
  //
  // Some features are incompatible with Gen3 and should not be enabled if rootport is capable of Gen3.
  // As an optimization we consider RP as Gen3 capable only if it supports hotplug or has Gen3 device connected.
  // It makes those features available when RP is Gen3 capable but a slower device is connected.
  // This optimization can be deleted if accessing endpoint in early boot is undesired.
  //
  if ((GetMaxLinkSpeed (RpBase) >= 3) && (RootPortConfig->HotPlug || *Gen3DeviceFound)) {
    RpGen3Capable = TRUE;
  }

  if ( NeedDecreasedDeEmphasis (DevInfo)) {
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_LCTL2, B_PCIE_LCTL2_SD);
  }

  ///
  /// If only 128B max payload is supported set CCFG.UNRS to 0.
  ///
  /// If peer writes are supported set max payload size supported to 128B, clear CCFG.UPMWPD
  /// and program all the PCH Root Ports such that upstream posted writes and upstream non-posted requests
  /// are split at 128B boundary by setting CCFG fields: UPSD to 0, CCFG.UPRS to 000b and UNSD to 0, UNRS to 000b
  ///
  Data32And = ~0u;
  Data32Or  = 0;
  RpMaxPayloadCapability = PchPcieMaxPayload256;
  if (RootPortConfig->MaxPayload == PchPcieMaxPayload128 ||
      PcieRpConfig->EnablePeerMemoryWrite) {
    RpMaxPayloadCapability = PchPcieMaxPayload128;

    Data32And &= (UINT32) ~(B_PCH_PCIE_CFG_CCFG_UNSD | B_PCH_PCIE_CFG_CCFG_UNRS);
    Data32Or  |= (UINT32)  (V_PCH_PCIE_CFG_CCFG_UNRS_128B << N_PCH_PCIE_CFG_CCFG_UNRS);

    if (PcieRpConfig->EnablePeerMemoryWrite) {
      Data32And &= (UINT32) ~(B_PCH_PCIE_CFG_CCFG_UPMWPD |
                              B_PCH_PCIE_CFG_CCFG_UPSD | B_PCH_PCIE_CFG_CCFG_UPRS);
      Data32Or  |= (UINT32)  (V_PCH_PCIE_CFG_CCFG_UPRS_128B << N_PCH_PCIE_CFG_CCFG_UPRS);
    }
  }
  ASSERT (RootPortConfig->MaxPayload < PchPcieMaxPayloadMax);
  ///
  /// Set B0:Dxx:Fn + D0h [13:12] to 01b
  ///
  Data32And &= (UINT32) ~B_PCH_PCIE_CFG_CCFG_UNRD;
  Data32Or  |=  (1u << N_PCH_PCIE_CFG_CCFG_UNRD);
  Data32Or  |=  B_PCH_PCIE_CFG_CCFG_DCGEISMA;

  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_CCFG, Data32And, Data32Or);

  PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_DCAP, (UINT16) ~B_PCIE_DCAP_MPS, (UINT16)RpMaxPayloadCapability);

  /*
  Configuration for Multi VC PCIe Controller: SPB, SPC and SPD
  */
  if ((PchGeneration () == EHL_PCH) && IsRpMultiVC (PortIndex) && PcieRpConfig->RootPort[PortIndex].MultiVcEnabled == TRUE) {
    //
    // Program PVCCR1.EVCC [2:0] to 01b
    //
    Data32 = PciSegmentRead32 (RpBase + R_PCIE_MVC_PVCCR1);
    Data32 |= (UINT32)(V_PCIE_MVC_PVCCR1_EVCC_2_VC << B_PCIE_MVC_PVCCR1_EVCC_OFFSET);
    PciSegmentWrite32(RpBase + R_PCIE_MVC_PVCCR1, Data32);
  }
  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// If B0:Dxx:Fn + 400h is programmed, BIOS will also program B0:Dxx:Fn + 404h [1:0] = 11b,
  /// to enable these override values.
  /// - Fn refers to the function number of the root port that has a device attached to it.
  /// - Default override value for B0:Dxx:Fn + 400h should be 880F880Fh
  /// - Also set 404h[2] to lock down the configuration
  /// - Refer to table below for the 404h[3] policy bit behavior.
  /// Done in PcieSetPm()
  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// Program B0:Dxx:Fn + 64h [11] = 1b
  ///
  Data32Or = 0;
  Data32And = ~0u;
  if (RootPortConfig->LtrEnable == TRUE) {
    Data32Or |= B_PCIE_DCAP2_LTRMS;
  } else {
    Data32And &= (UINT32) ~(B_PCIE_DCAP2_LTRMS);
  }
  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// Optimized Buffer Flush/Fill (OBFF) is not supported.
  /// Program B0:Dxx:Fn + 64h [19:18] = 0h
  ///
  Data32And &= (UINT32) ~B_PCIE_DCAP2_OBFFS;
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_DCAP2, Data32And, Data32Or);
  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// Program B0:Dxx:Fn + 68h [10] = 1b
  ///
  Data16 = PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_DCTL2);
  if (RootPortConfig->LtrEnable == TRUE) {
    Data16 |= B_PCIE_DCTL2_LTREN;
  } else {
    Data16 &= (UINT16) ~(B_PCIE_DCTL2_LTREN);
  }
  PciSegmentWrite16 (RpBase + R_PCH_PCIE_CFG_DCTL2, Data16);

  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// Step 3 done in PciExpressHelpersLibrary.c ConfigureLtr
  ///

  ///
  /// Set Dxx:Fn + 300h[23:00] = 0B75FA7h
  /// Set Dxx:Fn + 304h[11:00] = 0C97h
  ///
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_PCIERTP1, ~0x00FFFFFFu, 0x00B75FA7);
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_PCIERTP2, ~0x00000FFFu, 0x00000C97);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set Dxx:Fn + 318h [31:16] = 1414h (Gen2 and Gen1 Active State L0s Preparation Latency)
  ///
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_PCIEL0SC, ~0xFFFF0000u, 0x14140000);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// 1.  Program Dxx:Fn + E8h[20, 1] to [1, 1]
  ///
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_PWRCTL, B_PCH_PCIE_CFG_PWRCTL_LTSSMRTC |
                  B_PCH_PCIE_CFG_PWRCTL_RPL1SQPOL);
  ///
  /// 2.  Program Dxx:Fn + 320h[27, 30] to [1,1]
  /// Enable PCIe Relaxed Order to always allow downstream completions to pass posted writes,
  /// 3.  Set B0:Dxx:Fn:320h[24:23] = 11b
  /// Set PME timeout to 10ms, by
  /// 4.  Set B0:Dxx:Fn:320h[21:20] = 01b
  ///

  Data32And = (UINT32) ~B_PCH_PCIE_CFG_PCIECFG2_PMET;
  Data32Or  = B_PCH_PCIE_CFG_PCIECFG2_LBWSSTE |
    B_PCH_PCIE_CFG_PCIECFG2_RLLG3R |
    B_PCH_PCIE_CFG_PCIECFG2_CROAOV |
    B_PCH_PCIE_CFG_PCIECFG2_CROAOE |
    (V_PCH_PCIE_CFG_PCIECFG2_PMET << N_PCH_PCIE_CFG_PCIECFG2_PMET);

  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_PCIECFG2, Data32And, Data32Or);

  ///
  /// Enable squelch by programming Dxx:Fn + 324h[25, 24, 5] to [0, 0, 1]
  /// Enable Completion Time-Out Non-Fatal Advisory Error, Dxx:Fn + 324h[14] = 1b
  /// Set LDSWQRP Dxx:Fn + 324h[13] = 0
  ///
  Data32And = (UINT32) ~(B_PCH_PCIE_CFG_PCIEDBG_LGCLKSQEXITDBTIMERS | B_PCH_PCIE_CFG_PCIEDBG_LDSWQRP);
  Data32Or  = B_PCH_PCIE_CFG_PCIEDBG_CTONFAE | B_PCH_PCIE_CFG_PCIEDBG_SPCE;
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_PCIEDBG, Data32And, Data32Or);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Program Dxx:Fn + 424h [6, 5, 4] = [1, 1, 1]
  ///
  PciSegmentOr32 (
    RpBase + R_PCH_PCIE_CFG_PCIEPMECTL2,
    (B_PCH_PCIE_CFG_PCIEPMECTL2_L23RDYSCPGE |
     B_PCH_PCIE_CFG_PCIEPMECTL2_L1SCPGE)
    );
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// If Dxx:Fn + F5h[0] = 1b or step 3 is TRUE, set Dxx:Fn + 4Ch[17:15] = 4h
  /// Else set Dxx:Fn + 4Ch[17:15] = 010b
  ///
  Data32And = (UINT32) (~B_PCIE_LCAP_EL1);
  Data32Or = 4 << N_PCIE_LCAP_EL1;

  ///
  /// Set LCAP APMS according to platform policy.
  ///
  if (RootPortConfig->Aspm < PchPcieAspmAutoConfig) {
    Data32And &= (UINT32) ~B_PCIE_LCAP_APMS;
    Data32Or  |= RootPortConfig->Aspm << N_PCIE_LCAP_APMS;
  } else {
    Data32Or  |= B_PCIE_LCAP_APMS_L0S | B_PCIE_LCAP_APMS_L1;
  }

  //
  // Force disable L0s for Gen3 capable rootports
  //
  if (RpGen3Capable) {
    Data32And &= (UINT32) ~B_PCIE_LCAP_APMS_L0S;
    Data32Or  &= (UINT32) ~B_PCIE_LCAP_APMS_L0S;
  }
  //
  // The EL1, ASPMOC and APMS of LCAP are RWO, must program all together.
  //
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_LCAP, Data32And, Data32Or);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Configure PCI Express Number of Fast Training Sequence for each port
  /// 1.  Set Dxx:Fn + 314h [31:24, 23:16, 15:8, 7:0] to [7Eh, 70h, 3Fh, 38h]
  /// 2.  Set Dxx:Fn + 478h [31:24, 15:8, 7:0] to [28h, 3Dh, 2Ch]
  ///
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_PCIENFTS, 0x7E703F38);
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_G3L0SCTL, 0x00FF0000u, 0x28003D2C);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set MPC.IRRCE, Dxx:Fn + D8h[25] = 1b using byte access
  /// For system that support MCTP over PCIE set
  /// Set PCIE RP PCI offset D8h[27] = 1b
  /// Set PCIE RP PCI offset D8h[3] = 1b
  ///
  Data8And = (UINT8) (~(B_PCH_PCIE_CFG_MPC_IRRCE | B_PCH_PCIE_CFG_MPC_MMBNCE) >> 24);
  Data8Or = B_PCH_PCIE_CFG_MPC_MMBNCE >> 24;
  if (VtdConfig->VtdDisable) {
    Data8Or |= B_PCH_PCIE_CFG_MPC_IRRCE >> 24;
  }
  PciSegmentAndThenOr8 (RpBase + R_PCH_PCIE_CFG_MPC + 3, Data8And, Data8Or);

  Data8And = (UINT8) ~(B_PCH_PCIE_CFG_MPC_MCTPSE);
  Data8Or  = B_PCH_PCIE_CFG_MPC_MCTPSE;
  PciSegmentAndThenOr8 (RpBase + R_PCH_PCIE_CFG_MPC, Data8And, Data8Or);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set PCIE RP PCI offset F5h[7:4] = 0000b
  ///
  PciSegmentAnd8 (RpBase + R_PCH_PCIE_CFG_PHYCTL2, (UINT8) ~(B_PCH_PCIE_CFG_PHYCTL2_TDFT | B_PCH_PCIE_CFG_PHYCTL2_TXCFGCHGWAIT));

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Enable PME_TO Time-Out Policy, Dxx:Fn + E2h[6] =1b
  ///
  PciSegmentOr8 (RpBase + R_PCH_PCIE_CFG_RPPGEN, B_PCH_PCIE_CFG_RPPGEN_PTOTOP);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// If there is no IOAPIC behind the root port, set EOI Forwarding Disable bit (PCIE RP PCI offset D4h[1]) to 1b.
  /// For Empty Hot Plug Slot, set is done in InitPcieSingleRootPort ()
  ///

  ///
  /// System bios should initiate link retrain for all slots that has card populated after register restoration.
  /// Done in PchPciExpressHelpersLibrary.c PchPcieInitRootPortDownstreamDevices ()
  ///

  ///
  /// Configure Completion Timeout
  ///
  Data16And = (UINT16) ~(B_PCIE_DCTL2_CTD | B_PCIE_DCTL2_CTV);
  Data16Or  = 0;
  if (RootPortConfig->CompletionTimeout == PchPcieCompletionTO_Disabled) {
    Data16Or = B_PCIE_DCTL2_CTD;
  } else {
    switch (RootPortConfig->CompletionTimeout) {
      case PchPcieCompletionTO_Default:
        Data16Or = V_PCIE_DCTL2_CTV_DEFAULT;
        break;

      case PchPcieCompletionTO_16_55ms:
        Data16Or = V_PCIE_DCTL2_CTV_40MS_50MS;
        break;

      case PchPcieCompletionTO_65_210ms:
        Data16Or = V_PCIE_DCTL2_CTV_160MS_170MS;
        break;

      case PchPcieCompletionTO_260_900ms:
        Data16Or = V_PCIE_DCTL2_CTV_400MS_500MS;
        break;

      case PchPcieCompletionTO_1_3P5s:
        Data16Or = V_PCIE_DCTL2_CTV_1P6S_1P7S;
        break;

      default:
        Data16Or = 0;
        break;
    }
  }

  PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_DCTL2, Data16And, Data16Or);

  ///
  /// For Root Port Slots Numbering on the CRBs.
  ///
  Data32Or  = 0;
  Data32And = (UINT32) (~(B_PCIE_SLCAP_SLV | B_PCIE_SLCAP_SLS | B_PCIE_SLCAP_PSN));
  ///
  /// PCH BIOS Spec section 8.8.2.1
  /// Note: If Hot Plug is supported, then write a 1 to the Hot Plug Capable (bit6) and Hot Plug
  /// Surprise (bit5) in the Slot Capabilities register, PCIE RP PCI offset 54h. Otherwise,
  /// write 0 to the bits PCIe Hot Plug SCI Enable
  ///
  Data32And &= (UINT32) (~(B_PCIE_SLCAP_HPC | B_PCIE_SLCAP_HPS));
  if (RootPortConfig->HotPlug) {
    Data32Or |= B_PCIE_SLCAP_HPC | B_PCIE_SLCAP_HPS;
  }
  ///
  /// Get the width from LCAP
  /// Slot Type  X1  X2/X4/X8/X16
  /// Default     10W   25W
  /// The slot power consumption and allocation is platform specific. Please refer to the
  /// "PCI Express* Card Electromechanical (CEM) Spec" for details.
  ///
  if (RootPortConfig->SlotPowerLimitValue != 0) {
    Data32Or |= (UINT32) (RootPortConfig->SlotPowerLimitValue << N_PCIE_SLCAP_SLV);
    Data32Or |= (UINT32) (RootPortConfig->SlotPowerLimitScale << N_PCIE_SLCAP_SLS);
  } else {
    if (GetMaxLinkWidth (RpBase) == 1) {
      Data32Or |= (UINT32) (100 << N_PCIE_SLCAP_SLV);
      Data32Or |= (UINT32) (1 << N_PCIE_SLCAP_SLS);
    } else if (GetMaxLinkWidth (RpBase) >= 2) {
      Data32Or |= (UINT32) (250 << N_PCIE_SLCAP_SLV);
      Data32Or |= (UINT32) (1 << N_PCIE_SLCAP_SLS);
    }
  }

  ///
  /// PCH BIOS Spec section 8.2.4
  /// Initialize Physical Slot Number for Root Ports
  ///
  Data32Or |= (UINT32) (RootPortConfig->PhysicalSlotNumber << N_PCIE_SLCAP_PSN);
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_SLCAP, Data32And, Data32Or);

  InitCapabilityList (PortIndex, RpBase, RootPortConfig);

  //
  // All actions involving LinkDisable must finish before anything is programmed on endpoint side
  // because LinkDisable resets endpoint
  //

  ///
  /// Perform equalization for Gen3 capable ports
  ///
  if (GetMaxLinkSpeed (RpBase) >= 3) {
    ZeroMem (&PcieLinkEqSettings, sizeof (PCIE_LINK_EQ_SETTINGS));
    PcieGetProjectDefaultEqConfiguration (PortIndex, &PcieLinkEqSettings);
    if (PcieRpConfig->OverrideEqualizationDefaults) {
      CopyMem (&PcieLinkEqSettings.PlatformSettings, &PcieRpConfig->PcieLinkEqPlatformSettings, sizeof (PCIE_LINK_EQ_PLATFORM_SETTINGS));
    }
    //
    // Link EQ has to be performed with CCC set if supported.
    //
    EnableCommonClock (PortIndex, TempPciBus);
    PcieLinkEqualize (RpBase, *Gen3DeviceFound, &PcieLinkEqSettings);
  }
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set "Link Speed Training Policy", Dxx:Fn + D4h[6] to 1.
  /// Make sure this is after mod-PHY related programming is completed.
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_MPC2, B_PCH_PCIE_CFG_MPC2_LSTP);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Step 29 If Transmitter Half Swing is enabled, program the following sequence
  /// a. Ensure that the link is in L0.
  /// b. Program the Link Disable bit (0x50[4]) to 1b.
  /// c. Program the Analog PHY Transmitter Voltage Swing bit (0xE8[13]) to set the transmitter swing to half/full swing
  /// d. Program the Link Disable bit (0x50[4]) to 0b.
  /// BIOS can only enable this on SKU where GEN3 capability is disabled on that port
  RpLinkSpeed   = PciSegmentRead8 (RpBase + R_PCH_PCIE_CFG_LCAP) & B_PCIE_LCAP_MLS;
  if (RpLinkSpeed < V_PCIE_LCAP_MLS_GEN3 && RootPortConfig->TransmitterHalfSwing) {
    PciSegmentOr8 (RpBase + R_PCH_PCIE_CFG_LCTL, B_PCIE_LCTL_LD);
    while (IsLinkActive (RpBase)) {
      // wait until link becomes inactive before changing swing
    }
    PciSegmentOr16 (RpBase + R_PCH_PCIE_CFG_PWRCTL, B_PCH_PCIE_CFG_PWRCTL_TXSWING);
    PciSegmentAnd8 (RpBase + R_PCH_PCIE_CFG_LCTL, (UINT8) ~(B_PCIE_LCTL_LD));
  }
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set "Poisoned TLP Non-Fatal Advisory Error Enable", Dxx:Fn + D4h[12] to 1
  /// Set "L1 Substate Exit SCI Enable (L1SSESE)", Dxx:Fn + D4[30] to 1
  /// Set "Disable PLL Early Wake on L1 Substate Exit (DISPLLEWL1SE)", Dxx:Fn + D4[16] to 1
  ///
  Data32Or = B_PCH_PCIE_CFG_MPC2_PTNFAE | B_PCH_PCIE_CFG_MPC2_L1SSESE | B_PCH_PCIE_CFG_MPC2_DISPLLEWL1SE;
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_MPC2, Data32Or);

  //
  // L1LOW LTR threshold latency value
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_PCIEPMECTL,
    (UINT32) ~B_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV,
    (V_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV << N_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV)
    );

  ///
  /// Additional configurations
  ///
  ///
  /// Configure Error Reporting policy in the Device Control Register
  ///
  Data16And = (UINT16) (~(B_PCIE_DCTL_URE | B_PCIE_DCTL_FEE | B_PCIE_DCTL_NFE | B_PCIE_DCTL_CEE));
  Data16Or  = 0;

  if (RootPortConfig->UnsupportedRequestReport) {
    Data16Or |= B_PCIE_DCTL_URE;
  }

  if (RootPortConfig->FatalErrorReport) {
    Data16Or |= B_PCIE_DCTL_FEE;
  }

  if (RootPortConfig->NoFatalErrorReport) {
    Data16Or |= B_PCIE_DCTL_NFE;
  }

  if (RootPortConfig->CorrectableErrorReport) {
    Data16Or |= B_PCIE_DCTL_CEE;
  }

  PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_DCTL, Data16And, Data16Or);

  ///
  /// Configure Interrupt / Error reporting in R_PCH_PCIE_CFG_RCTL
  ///
  Data16And = (UINT16) (~(B_PCIE_RCTL_SFE | B_PCIE_RCTL_SNE | B_PCIE_RCTL_SCE));
  Data16Or  = 0;

  if (RootPortConfig->SystemErrorOnFatalError) {
    Data16Or |= B_PCIE_RCTL_SFE;
  }

  if (RootPortConfig->SystemErrorOnNonFatalError) {
    Data16Or |= B_PCIE_RCTL_SNE;
  }

  if (RootPortConfig->SystemErrorOnCorrectableError) {
    Data16Or |= B_PCIE_RCTL_SCE;
  }

  PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_RCTL, Data16And, Data16Or);

  ///
  /// Root PCI-E Powermanagement SCI Enable
  ///
  if (RootPortConfig->PmSci) {
    ///
    /// PCH BIOS Spec section 8.7.3 BIOS Enabling of Intel PCH PCI Express* PME SCI Generation
    /// Step 1
    /// Make sure that PME Interrupt Enable bit, Dxx:Fn:Reg 5Ch[3] is cleared
    ///
    PciSegmentAnd16 (RpBase + R_PCH_PCIE_CFG_RCTL, (UINT16) (~B_PCIE_RCTL_PIE));

    ///
    /// Step 2
    /// Program Misc Port Config (MPC) register at PCI config space offset
    /// D8h as follows:
    /// Set Power Management SCI Enable bit, Dxx:Fn:Reg D8h[31]
    /// Clear Power Management SMI Enable bit, Dxx:Fn:Reg D8h[0]
    /// Use Byte Access to avoid RWO bit
    ///
    PciSegmentAnd8 (RpBase + R_PCH_PCIE_CFG_MPC, (UINT8) (~B_PCH_PCIE_CFG_MPC_PMME));
    PciSegmentOr8 ((RpBase + R_PCH_PCIE_CFG_MPC + 3), (UINT8) (B_PCH_PCIE_CFG_MPC_PMCE >> 24));
  }
  if (RootPortConfig->HotPlug) {
    ///
    /// PCH BIOS Spec section 8.8.2.1
    /// Step 1
    /// Clear following status bits, by writing 1b to them, in the Slot
    /// Status register at offset 1Ah of PCI Express Capability structure:
    /// Presence Detect Changed (bit3)
    ///
    PciSegmentAnd16 (RpBase + R_PCH_PCIE_CFG_SLSTS, B_PCIE_SLSTS_PDC);
    ///
    /// Step 2
    /// Program the following bits in Slot Control register at offset 18h
    /// of PCI Express* Capability structure:
    /// Presence Detect Changed Enable (bit3) = 1b
    /// Hot Plug Interrupt Enable (bit5) = 0b
    ///
    PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_SLCTL, (UINT16) (~B_PCIE_SLCTL_HPE), B_PCIE_SLCTL_PDE);
    ///
    /// Step 3
    /// Program Misc Port Config (MPC) register at PCI config space offset
    /// D8h as follows:
    /// Hot Plug SCI Enable (HPCE, bit30) = 1b
    /// Hot Plug SMI Enable (HPME, bit1) = 0b
    /// Use byte access to avoid premature locking BIT23, SRL
    ///
    PciSegmentAnd8 (RpBase + R_PCH_PCIE_CFG_MPC, (UINT8)(~B_PCH_PCIE_CFG_MPC_HPME));
    PciSegmentOr8 (RpBase + R_PCH_PCIE_CFG_MPC + 3, B_PCH_PCIE_CFG_MPC_HPCE >> 24);
    ///
    /// PCH BIOS Spec section 8.9
    /// BIOS should mask the reporting of Completion timeout (CT) errors by setting
    /// the uncorrectable Error Mask register PCIE RP PCI offset 108h[14].
    ///
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_EX_UEM, B_PCIE_EX_UEM_CT);
  }

  ///
  /// PCH BIOS Spec Section 8.10 PCI Bus Emulation & Port80 Decode Support
  /// The I/O cycles within the 80h-8Fh range can be explicitly claimed
  /// by the PCIe RP by setting MPC.P8XDE, PCI offset D8h[26] = 1 (using byte access)
  /// BIOS must also configure the corresponding DMI registers GCS.RPR and GCS.RPRDID
  /// to enable DMI to forward the Port8x cycles to the corresponding PCIe RP
  ///
  if (PcieRpConfig->EnablePort8xhDecode && (PortIndex == (UINT8)PcieRpConfig->PchPciePort8xhDecodePortIndex)) {
    PciSegmentOr8 (RpBase + R_PCH_PCIE_CFG_MPC + 3, (UINT8) (B_PCH_PCIE_CFG_MPC_P8XDE >> 24));
    PchIoPort80DecodeSet (PortIndex);
  }
  //
  // Initialize R/WO Registers that described in PCH BIOS Spec
  //
  ///
  /// SRL bit is write-once and lock, so SRL, UCEL and CCEL must be programmed together
  /// otherwise UCEL/CCEL programming would lock SRL prematurely in wrong state
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set Common Clock Exit Latency,      Dxx:Fn + D8h[17:15] = 4h
  /// Set Non-common Clock Exit Latency,  Dxx:Fn + D8h[20:18] = 7h
  ///
  Data32And = ~(UINT32) (B_PCH_PCIE_CFG_MPC_UCEL | B_PCH_PCIE_CFG_MPC_CCEL);
  Data32Or  = (7 << N_PCH_PCIE_CFG_MPC_UCEL) | (4<< N_PCH_PCIE_CFG_MPC_CCEL);
    if (!IsRpMultiVC(PortIndex)) {
      Data32Or |= B_PCH_PCIE_CFG_MPC_SRL;
    }
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_MPC, Data32And, Data32Or);

  if (IsRpMultiVC (PortIndex)) {
    Data32Or = B_PCIE_MVC_LPCR_SRL | B_PCIE_MVC_LPCR_SERL | B_PCIE_MVC_LPCR_LTRCFGLOCK | B_PCIE_MVC_LPCR_DIDOVR_LOCK;
    PciSegmentOr32 (RpBase + R_PCIE_MVC_LPCR, Data32Or);
  }

    //
    // Check if SRL bit actually got programmed. If not, then it means some code accessed MPC register earlier and locked it
    //
    if (!IsRpMultiVC(PortIndex)) {
      ASSERT ((PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_MPC) & B_PCH_PCIE_CFG_MPC_SRL) == B_PCH_PCIE_CFG_MPC_SRL);
    }
  if (IsRpMultiVC (PortIndex)) {
    Data32Or = B_PCIE_MVC_LPCR_SRL | B_PCIE_MVC_LPCR_SERL | B_PCIE_MVC_LPCR_LTRCFGLOCK | B_PCIE_MVC_LPCR_DIDOVR_LOCK;
    ASSERT ((PciSegmentRead32 (RpBase + R_PCIE_MVC_LPCR) & Data32Or) == Data32Or);
  }
  ///
  /// Configure Root Port interrupt
  ///
  InterruptPin = ItssGetDevIntPin (SiPolicy, (UINT8)RpDevice, (UINT8)RpFunction);

  Data32And = (UINT32) ~B_PCH_PCIE_CFG_STRPFUSECFG_PXIP;
  Data32Or = (UINT32) (InterruptPin << N_PCH_PCIE_CFG_STRPFUSECFG_PXIP);
  PciSegmentAndThenOr32 (RpBase + R_PCH_PCIE_CFG_STRPFUSECFG, Data32And, Data32Or);

  //
  // Set Gpio Assertion on Link Down      Dxx:Fn + 0x690h[10] = 1
  //
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_GDR, B_PCH_PCIE_CFG_GDR_GPIOALD);

  ///
  /// Dynamic Link Throttling
  ///
  Data32Or = (V_PCH_PCIE_CFG_TNPT_TP_3_MS << N_PCH_PCIE_CFG_TNPT_TP);
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_TNPT, Data32Or);
}

/**
  Configures PTM in PCIe controller

  @param[in] ControllerIndex  Index of the PCIe controller
**/
STATIC
VOID
PcieConfigurePtm (
  IN UINT32  ControllerIndex
  )
{
  UINT32                  RpIndex;
  UINT64                  RpBase;
  PCIE_PTM_CONFIGURATION  PtmConfig;
  UINT32                  Index;

  PcieGetProjectPtmConfiguration (ControllerIndex, &PtmConfig);

  RpIndex = GetControllerFirstRpIndex (ControllerIndex);
  RpBase = PchPcieBase (RpIndex);
  if ((PciSegmentRead16 (RpBase) != 0xFFFF)) {
    for (Index = 0; Index < PTM_DELAY_REGISTERS_NUM; Index++) {
      PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PTMPSDC1 + (4 * Index), 0x0, PtmConfig.PtmPipeStageDelay[Index]);
    }
    PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PTMECFG,  0x0, PtmConfig.PtmConfig);
  }
}

/**
  Perform initialization for all PCIe registers as required by FuSa
**/
STATIC
VOID
InitFusaPcieRegs (
  UINT8 FuncIndex
  )
{
  UINT64  RpBase;

  DEBUG ((DEBUG_INFO, "Initialize FuSa PCIe registers\n"));

  RpBase = PCI_SEGMENT_LIB_ADDRESS (
             DEFAULT_PCI_SEGMENT_NUMBER_PCH,
			 DEFAULT_PCI_BUS_NUMBER_PCH,
             PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1,
			 (UINT32) FuncIndex,
			 0
			 );
  //
  // Interrupt Information and Bridge Configuration. For function 0 to 3
  //
  if (FuncIndex < 4) {
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_INTR_BCTRL, (UINT32) (BIT17));
  }
  //
  // Device Control and Device Status. For function 0 to 3
  //
  if (FuncIndex < 4) {
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_DCTL_DSTS, (UINT32) (BIT3 | BIT2 | BIT1 | BIT0));
  }
  //
  // Root Control
  //
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_RCTL, (UINT32) (BIT3 | BIT2 | BIT1 | BIT0));
  //
  // Device Control 2 and Device Status 2. For function 0 to 3
  //
  if (FuncIndex < 4) {
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_DCTL2_DSTS2, (UINT32) (BIT3 | BIT2 | BIT1 | BIT0));
  }
  //
  // Uncorrectable Error Mask
  //
  PciSegmentAnd32 (
    RpBase + R_PCH_PCIE_CFG_UEM,
    (UINT32)~((BIT26 | BIT21 | BIT20 | BIT18 | BIT17 | BIT16 | BIT15 | BIT14 | BIT12 | BIT4))
	);
  //
  // Correctable Error Mask
  //
  PciSegmentAnd32 (RpBase + R_PCH_PCIE_CFG_CEM, (UINT32)~((BIT13 | BIT12 | BIT8 | BIT7 | BIT6 | BIT0)));
}

/**
  Perform Initialization of the Downstream Root Ports.

  @param[in] SiPolicy             The SI Policy PPI
**/
VOID
PcieRpInit (
  IN CONST SI_POLICY_PPI     *SiPolicy
  )
{
  PCH_PCIE_CONFIG                   *PciExpressConfig;
  SI_PREMEM_POLICY_PPI              *SiPreMemPolicyPpi;
  CONST PCH_PCIE_ROOT_PORT_CONFIG   *PcieRpConfig;
  EFI_STATUS                        Status;
  UINT8                             RpIndex;
  UINT64                            RpBase;
  UINTN                             RpDevice;
  UINTN                             RpFunction;
  SBDF                              RpSbdf;
  UINT8                             MaxPciePortNum;
  UINT32                            RpDisableMask;
  UINT32                            RpClkreqMask;
  UINT32                            Timer;
  UINT32                            DetectTimeoutUs;
  BOOLEAN                           Gen3DeviceFound[PCH_MAX_PCIE_ROOT_PORTS];
  BOOLEAN                           KeepPortVisible;
  UINT8                             TempPciBusMin;
  UINT8                             TempPciBusMax;
  UINT32                            ControllerIndex;
  UINT32                            MaxPcieControllerNum;
  MULTI_VC_SUPPORT                  ExtVcSupport;

  DEBUG ((DEBUG_INFO, "PcieRpInit() Start\n"));

  TempPciBusMin = PcdGet8 (PcdSiliconInitTempPciBusMin);
  TempPciBusMax = PcdGet8 (PcdSiliconInitTempPciBusMax);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PciExpressConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG_CODE_BEGIN ();
  PciePolicySanityCheck (PciExpressConfig);
  DEBUG_CODE_END ();

  Timer            = 0;
  MaxPciePortNum   = GetPchMaxPciePortNum ();
  MaxPcieControllerNum = GetPchMaxPcieControllerNum ();
  RpDisableMask    = 0;
  RpClkreqMask     = 0;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  PchFiaSetClockOutputDelay ();

  if (GetPcieImrPortLocation () == ImrRpLocationPch) {
    EnablePcieImr (GetPcieImrPortNumber (), BUS_NUMBER_FOR_IMR);
  }

  for (RpIndex = 0; RpIndex < MaxPciePortNum; RpIndex++) {
    RpBase = PchPcieBase (RpIndex);

    //
    // Enable CLKREQ# regardless of port being available/enabled to allow clock gating.
    //
    if (IsClkReqAssigned (PchClockUsagePchPcie0 + RpIndex)) {
      RpClkreqMask |= (BIT0 << RpIndex);
    }

    //
    // Determine available ports based on lane ownership and port configuration (x1/x2/x4)
    // Root ports can be already disabled by PchEarlyDisabledDeviceHandling
    //
    if ((PciSegmentRead16 (RpBase) == 0xFFFF)
        || (IsPciePortOwningLanes (RpBase) == FALSE)
        ) {
      RpDisableMask |= (BIT0 << RpIndex);
      continue;
    }

    ///
    /// Set the Slot Implemented Bit.
    /// PCH BIOS Spec section 8.2.3, The System BIOS must
    /// initialize the "Slot Implemented" bit of the PCI Express* Capabilities Register,
    /// XCAP Dxx:Fn:42h[8] of each available and enabled downstream root port.
    /// Ports with hotplug capability must have SI bit set
    /// The register is write-once so must be written even if we're not going to set SI, in order to lock it.
    ///
    /// This must happen before code reads PresenceDetectState, because PDS is invalid unless SI is set
    ///
    if (PciExpressConfig->RootPort[RpIndex].SlotImplemented || PciExpressConfig->RootPort[RpIndex].HotPlug) {
      PciSegmentOr16 (RpBase + R_PCH_PCIE_CFG_XCAP, B_PCIE_XCAP_SI);
    } else {
      PciSegmentAnd16 (RpBase + R_PCH_PCIE_CFG_XCAP, (UINT16)(~B_PCIE_XCAP_SI));
    }

    ///
    /// For non-hotplug ports disable the port if there is no device present.
    ///
    DetectTimeoutUs = PciExpressConfig->RootPort[RpIndex].DetectTimeoutMs * 1000;
    if (IsPcieDevicePresent (RpBase, DetectTimeoutUs, &Timer)) {
      DEBUG ((DEBUG_INFO, "Port %d has a device attached.\n", RpIndex + 1));
      //
      // At this point in boot, CLKREQ pad is still configured as GP input and doesnt' block clock generation
      // regardless of input state. Before switching it to native mode when it will start gating clock, we
      // verify if CLKREQ is really connected. If not, pad will not switch and power management
      // will be disabled in rootport.
      // By the time this code runs device can't have CPM or L1 substates enabled, so it is guaranteed to pull ClkReq down.
      // If ClkReq is detected to be high anyway, it means ClkReq is not connected correctly.
      // Checking pad's input value is primarily a measure to prevent problems with long cards inserted into short
      // open-ended PCIe slots on motherboards which route PRSNT signal to CLKREQ. Such config causes CLKREQ signal to float.
      //
      if (!PcieDetectClkreq (RpIndex, PciExpressConfig)) {
        RpClkreqMask &= ~(BIT0 << RpIndex);
      }
    } else {
      if (PciExpressConfig->RootPort[RpIndex].HotPlug == FALSE) {
        RpDisableMask |= (BIT0 << RpIndex);
      }
    }
  }

  for (RpIndex = 0; RpIndex < MaxPciePortNum; RpIndex++) {
    if (RpClkreqMask & (BIT0 << RpIndex)) {
      //
      // Enabled CLKREQ# pad if supported to allow clock gating regardless of port being enabled.
      //
      EnableClkReq (PchClockUsagePchPcie0 + RpIndex);
    }

    ///
    /// Configure power management applicable to all port including disabled ports.
    ///
    if ((GetControllerRpIndex (RpIndex)) == 0) {
      //
      // TrunkClockGateEn depends on each of the controller ports supporting CLKREQ# or being disabled.
      //
      PcieConfigureControllerBasePowerManagement (
        RpIndex,
        (((RpClkreqMask | RpDisableMask) & (BIT0 << RpIndex)) != 0)
        );
    }
    //
    // PhyLanePgEnable depends on the port supporting CLKREQ# or being disabled.
    //
    PcieConfigurePortBasePowerManagement (
      RpIndex,
      (((RpClkreqMask | RpDisableMask) & (BIT0 << RpIndex)) != 0)
     );
  }

  //
  // Wait for all ports with PresenceDetect=1 to form a link
  // Having an active link is necessary to access and configure the endpoint
  // We cannot use results of IsPcieDevicePresent() because it checks PDS only and may include
  // PCIe cards that never form a link, such as compliance load boards.
  //
  WaitForLinkActive (MaxPciePortNum, RpDisableMask);
  ///
  /// For each controller set Initialize Transaction Layer Receiver Control on Link Down
  /// and Initialize Link Layer Receiver Control on Link Down.
  /// Use sideband access in case 1st port of a controller is disabled
  ///
  for (RpIndex = 0; RpIndex < MaxPciePortNum; ++RpIndex) {
    RpBase = PchPcieBase (RpIndex);
    if ((PciSegmentRead16 (RpBase) == 0xFFFF)) {
      continue;
    }
    if ((GetControllerRpIndex (RpIndex)) == 0) {
      PchSbiRpPciAndThenOr32 (RpIndex, R_PCH_PCIE_CFG_PCIEALC, ~0u, B_PCH_PCIE_CFG_PCIEALC_ITLRCLD | B_PCH_PCIE_CFG_PCIEALC_ILLRCLD | B_PCH_PCIE_CFG_PCIEALC_RTD3PDSP);
    }
  }

  //
  // PTM settings are global per PCIe controller.
  //
  for (ControllerIndex = 0; ControllerIndex < MaxPcieControllerNum; ControllerIndex++) {
    PcieConfigurePtm (ControllerIndex);
  }

  for (RpIndex = 0; RpIndex < MaxPciePortNum; ++RpIndex) {
    RpBase = PchPcieBase (RpIndex);
    if ((PciSegmentRead16 (RpBase) == 0xFFFF)) {
      continue;
    }
    if (RpDisableMask & (BIT0 << RpIndex)) {
      KeepPortVisible = IsPortForceVisible (RpIndex, RpDisableMask, PciExpressConfig);
      DisablePcieRootPort (RpIndex, KeepPortVisible);
    } else {
      InitPcieSingleRootPort (
        RpIndex,
        SiPolicy,
        SiPreMemPolicyPpi,
        TempPciBusMin,
        &Gen3DeviceFound[RpIndex]
        );
      ///
      /// Initialize downstream devices
      ///
      GetPchPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
      RootportDownstreamConfiguration (
        DEFAULT_PCI_SEGMENT_NUMBER_PCH,
        DEFAULT_PCI_BUS_NUMBER_PCH,
        (UINT8) RpDevice,
        (UINT8) RpFunction,
        TempPciBusMin,
        TempPciBusMax,
        EnumPchPcie
        );

      RpBase = PCI_SEGMENT_LIB_ADDRESS (
        DEFAULT_PCI_SEGMENT_NUMBER_PCH,
        DEFAULT_PCI_BUS_NUMBER_PCH,
        (UINT8) RpDevice,
        (UINT8) RpFunction,
        0);
      if (!(IsDevicePresent (RpBase))) {
        return;
      }

      RpSbdf.Seg  = DEFAULT_PCI_SEGMENT_NUMBER_PCH;
      RpSbdf.Bus  = DEFAULT_PCI_BUS_NUMBER_PCH;
      RpSbdf.Dev  = (UINT8) RpDevice;
      RpSbdf.Func = (UINT8)  RpFunction;
      RpSbdf.PcieCap = PcieBaseFindCapId (RpBase, EFI_PCI_CAPABILITY_ID_PCIEXP);
      PcieRpConfig   = &PciExpressConfig->RootPort[RpIndex];

      if ((PchGeneration () == EHL_PCH) && IsRpMultiVC (RpIndex) && PcieRpConfig->MultiVcEnabled == TRUE) {
        ExtVcSupport = RecursiveMultiVcConfiguration (RpSbdf);
        if (ExtVcSupport.ExtVcCount) {
          DEBUG ((DEBUG_INFO, "RootPort %x supports %x ExtendedVC",RpIndex,ExtVcSupport.ExtVcCount));
        }
      }
    }
  }
  //
  // Registers init for FuSa
  //
  if (IsFusaSupported ()) {
    for (RpIndex = 0; RpIndex < MaxPciePortNum; ++RpIndex) {
      RpBase = PchPcieBase (RpIndex);
      if ((PciSegmentRead16 (RpBase) == 0xFFFF)) {
        continue;
      }
      InitFusaPcieRegs (RpIndex);
    }
  }
  ///
  /// Clear GPE0 Register PCI_EXP_STS and HOT_PLUG_STS by writing 1
  ///
  IoWrite32 (
    PmcGetAcpiBase () + R_ACPI_IO_GPE0_STS_127_96,
    B_ACPI_IO_GPE0_STS_127_96_PCI_EXP | B_ACPI_IO_GPE0_STS_127_96_HOT_PLUG
    );

  ///
  /// If SCI is enabled in any port, Set BIOS_PCI_EXP_EN bit, PMC PCI offset A0h[10],
  /// to globally enable the setting of the PCI_EXP_STS bit by a PCI Express* PME event.
  ///
  for (RpIndex = 0; RpIndex < MaxPciePortNum; RpIndex++) {
    RpBase = PchPcieBase (RpIndex);
    if ((PciSegmentRead16 (RpBase) == 0xFFFF)) {
      continue;
    }
    if (PciExpressConfig->RootPort[RpIndex].PmSci) {
      PmcEnablePciExpressPmeEvents ();
      break;
    }
  }

  ///
  /// PCH BIOS Spec Section 8.2.9
  /// Enable PCIe Relaxed Order to always allow downstream completions to pass posted writes.
  /// To enable this feature configure DMI and PSF:
  ///
  PchDmiEnablePcieRelaxedOrder ();
  PsfEnablePcieRelaxedOrder ();

  //
  // Program the root port target link speed.
  //
  Status = PcieRpSpeedChange ();
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PcieRpInit() End\n"));
}

/**
  Hide rootports disabled by policy. This needs to be done in premem,
  because graphics init from SystemAgent code depends on those ports
  being already hidden

  @param[in] PcieRpPreMemConfig   Platform policy
**/
VOID
PcieRpEarlyDisabling (
  IN PCH_PCIE_RP_PREMEM_CONFIG *PcieRpPreMemConfig
  )
{
  UINT32 RpIndex;
  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    if ((PcieRpPreMemConfig->RpEnabledMask & (UINT32) (1 << RpIndex)) == 0) {
      PsfDisablePcieRootPort (RpIndex);
    }
  }
}

/**
  Initializes ports with NonCommonClock configuration. Such ports can't detect endpoints
  before NCC init ends. To prevent boot delays, NCC handling should happen in pre-mem
  rather than just before endpoint detection in post-mem
**/
VOID
PcieRpEarlyNccHandling (
  VOID
  )
{
  UINT32 RpIndex;

  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    if (IsPcieNcc (PchPcieBase (RpIndex))) {
      PcieInitNccPort (RpIndex);
    }
  }
}

/**
  Configure PCIe Grant Counts
**/
VOID
PcieRpConfigureGrantCounts (
  VOID
  )
{
   UINT32                ControllerMax;
   UINT32                Controller;
   PSF_PCIE_CTRL_CONFIG  PsfPcieCtrlConfigTable[PCH_MAX_PCIE_CONTROLLERS];

   ControllerMax = GetPchMaxPcieControllerNum ();

  for (Controller = 0; Controller < ControllerMax; Controller++) {
    if (IsCtrlMultiVC (Controller)) {
      PsfPcieCtrlConfigTable[Controller] = PsfPcieCtrl1x1;
    } else {
      switch (GetPcieControllerConfig (Controller)) {
        case Pcie4x1: //Pcie4x1
          PsfPcieCtrlConfigTable[Controller] = PsfPcieCtrl4x1;
          break;
        case Pcie1x2_2x1: //Pcie1x2_2x1
          PsfPcieCtrlConfigTable[Controller] = PsfPcieCtrl1x2_2x1;
          break;
        case Pcie2x2: //Pcie2x2
          PsfPcieCtrlConfigTable[Controller] = PsfPcieCtrl2x2;
          break;
        case Pcie1x4: //Pcie1x4
          PsfPcieCtrlConfigTable[Controller] = PsfPcieCtrl1x4;
          break;
        default:
          ASSERT (FALSE);
      }
    }
  }

  PsfConfigurePcieGrantCounts (PsfPcieCtrlConfigTable, ControllerMax);
}
