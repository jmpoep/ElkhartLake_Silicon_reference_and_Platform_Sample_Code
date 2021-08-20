/** @file
  This file contains functions that initializes PCI Express Root Ports of CPU PCIe.

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
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/TimerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/CpuPcieExpressHelpersLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PsfLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuPcieRpLib.h>
#include <Library/SaPcieInitLib.h>
#include <Library/PeiPcieRpLib.h>
#include <Library/PcdLib.h>
#include <Library/PchPcrLib.h>
#include <Uefi/UefiBaseType.h>
#include <SaPolicyCommon.h>
#include <PcieRegs.h>
#include <Register/CpuPcieRegs.h>
#include <CpuPcieHob.h>
#include <Library/PciLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <Library/CpuPcieInitCommon.h>
#include <Library/PeiCpuPcieDekelInitLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/ItbtPcieRpInitLib.h>
#include <Library/PcieHelperLib.h>
#include <Library/CpuRegbarAccessLib.h>
#include <PciePreMemConfig.h>
#include <CpuSbInfo.h>
#include <Register/PchRegsFia.h>

GLOBAL_REMOVE_IF_UNREFERENCED PCIE_EQ_PARAM               mCpuPcieEqParamList[PCIE_HWEQ_COEFFS_MAX][2];
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                      List[12];
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                      mDoGen3HwEqRpMask = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                      mDoGen4HwEqRpMask = 0;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_PCIE_CONFIG             *mCpuPcieRpConfig  = NULL;

#define LTSSM_POLL_INTERVAL       10u // in microseconds, period for polling port state during SW EQ
#define RECOVERY_TIME_THRESHOLD   40  // in percent, how much time can SW EQ spend in recovery during a single step

#define LINK_ACTIVE_POLL_INTERVAL 100     // in microseconds
#define LINK_ACTIVE_POLL_TIMEOUT  1000000 // in microseconds

#define HWEQ_DONE_POLL_INTERVAL 100     // in microseconds
#define HWEQ_DONE_POLL_TIMEOUT  24000   // in microseconds

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
  Programs Isolated Memory Region feature.
  IMR is programmed in a CPU PCIe rootport, based on data retrieved from CPU registers.

  @param[in] RpIndex     Root Port Number (0-based)
**/
VOID
CpuPcieEnablePcieImr (
  UINT8 RpIndex
  )
{
  UINT32                         ImrBaseLow;
  UINT32                         ImrBaseHigh;
  UINT32                         ImrLimitLow;
  UINT32                         ImrLimitHigh;
  UINT64                         ImrLimit;
  PCI_IMR_HOB                    *PciImrHob;
  UINT32                         Data32;
  CPU_SB_DEVICE_PID              ControllerPid;

  DEBUG ((DEBUG_INFO, "EnablePcieImr: RP %d\n", RpIndex));


  if (RpIndex > GetMaxCpuPciePortNum ()){
    DEBUG ((DEBUG_INFO, "Invalid Root Port Selection\n"));
    return;
  }

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
    DEBUG ((DEBUG_ERROR, "PcieImr base address is 0, PCIe IMR programming skipped!\n"));
    return;
  }
  DEBUG ((DEBUG_ERROR, "PcieImr base address is %x\n", PciImrHob->PciImrBase));

  ImrLimit = PciImrHob->PciImrBase + LShiftU64 (GetPcieImrSize (), 20);
  ImrBaseLow = (UINT32)RShiftU64 ((PciImrHob->PciImrBase & 0xFFF00000), 20);
  ImrBaseHigh = (UINT32)RShiftU64 (PciImrHob->PciImrBase, 32);
  ImrLimitLow = (UINT32)RShiftU64 ((ImrLimit & 0xFFF00000), 20);
  ImrLimitHigh = (UINT32)RShiftU64 (ImrLimit, 32);

  //
  // PCIe IMR base & limit registers in SA contain bits 63:20 of adress, divided into upper (64:32) and lower (31:20) parts
  // That means bits 19:10 are ignored and addresses are aligned to 1MB.
  //
  ControllerPid = GetCpuPcieRpSbiPid (RpIndex);

  Data32 = (UINT32) (LShiftU64 (ImrBaseLow, N_PCIE_IMRAMBL_IAMB) | LShiftU64 (ImrLimitLow, N_PCIE_IMRAMBL_IAML));

  CpuRegbarWrite32 (ControllerPid, R_PCIE_IMRAMBL, Data32);
  CpuRegbarWrite32 (ControllerPid, R_PCIE_IMRAMBU32, ImrBaseHigh);
  CpuRegbarWrite32 (ControllerPid, R_PCIE_IMRAMLU32, ImrLimitHigh);
  CpuRegbarWrite32 (ControllerPid, R_PCIE_IMRAMLE, (UINT32) (LShiftU64 (BIT0, (RpIndex % CPU_PCIE_MAX_ROOT_PORTS)) | B_PCIE_IMRAMLE_SRL));

  DEBUG ((DEBUG_INFO, "PCIe IMR registers: PID %x, +10=%08x, +14=%08x, +18=%08x, +1c=%08x %d\n",
    ControllerPid,
    CpuRegbarRead32 (ControllerPid, R_PCIE_IMRAMBL),
    CpuRegbarRead32 (ControllerPid, R_PCIE_IMRAMBU32),
    CpuRegbarRead32 (ControllerPid, R_PCIE_IMRAMLU32),
    CpuRegbarRead32 (ControllerPid, R_PCIE_IMRAMLE)
    ));
}

/**
  This function assigns bus number to PCIe bus .

  @param[in] RpIndex     Root Port index
**/
VOID
CpuPcieAssignTemporaryBus (
  IN UINT64 RpBase,
  IN UINT8  TempPciBus
  )
{
  UINT64 EpBase;
  DEBUG((DEBUG_VERBOSE, "CpuPcieAssignTemporaryBus Start\n"));
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

  EpBase  = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TempPciBus, 0, 0, 0);
  PciSegmentWrite16 (EpBase + PCI_VENDOR_ID_OFFSET, 0);
  DEBUG ((DEBUG_VERBOSE, "CpuPcieAssignTemporaryBus End\n"));
}

/**
  Clear temp bus usage.

  @param[in] RpBase     Root Port PCI base address
**/
VOID
CpuPcieClearBus (
  IN UINT64 RpBase
  )
{
  DEBUG ((DEBUG_VERBOSE, "CpuPcieClearBus Start\n"));
  PciSegmentAnd32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN
    );
  DEBUG ((DEBUG_VERBOSE, "CpuPcieClearBus End\n"));
}

/**
  This function sets Common Clock Mode bit in rootport and endpoint connected to it, if both sides support it.
  This bit influences rootport's Gen4 training and should be set before Gen4 software equalization is attempted.
  It does not attempt to set CCC in further links behind rootport

  @param[in] RpIndex     Root Port index
**/
VOID
CpuPcieEnableCommonClock (
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

  DEBUG ((DEBUG_VERBOSE, "CpuPcieEnableCommonClock Start\n"));
  GetCpuPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
  RpBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, RpDevice, RpFunction, 0);
  CpuPcieAssignTemporaryBus (RpBase, TempPciBus);
  EpBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TempPciBus, 0, 0, 0);
  if (IsDevicePresent (EpBase)) {
    EpPcieCapOffset = PcieBaseFindCapId (EpBase, EFI_PCI_CAPABILITY_ID_PCIEXP);
    if (GetScc (RpBase, R_PCIE_CLIST) && (EpPcieCapOffset != 0) && GetScc (EpBase, EpPcieCapOffset)) {
      EnableCcc (RpBase, R_PCIE_CLIST);
      EnableCcc (EpBase, EpPcieCapOffset);
      if (IsMultifunctionDevice (EpBase)) {
        for (Func = 1; Func <= PCI_MAX_FUNC; Func++) {
          EpBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TempPciBus, 0, Func, 0);
          EnableCcc (EpBase, PcieBaseFindCapId (EpBase, EFI_PCI_CAPABILITY_ID_PCIEXP));
        }
      }
      RetrainLink (RpBase, R_PCIE_CLIST, TRUE);
    }
  }
  CpuPcieClearBus (RpBase);
  DEBUG ((DEBUG_VERBOSE, "CpuPcieEnableCommonClock End\n"));
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
CpuPcieDetectClkreq (
  IN UINT32                    RpIndex,
  IN CONST CPU_PCIE_CONFIG     *PcieConfig
  )
{
  SA_PEG_HOB                        *SaPegHob;

  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  if (!IsClkReqAssigned (PchClockUsageCpuPcie0 + RpIndex)) {
    DEBUG ((DEBUG_ERROR, "CLKREQ is not assigned, disabling power management for RP %d.\n", RpIndex));
    return FALSE;
  }
  if (SaPegHob != NULL) {
    if (SaPegHob->DisableClkReqMsg[RpIndex]) { // Check if Enable CLKREQ# MSG Status is good
      return FALSE;
    }
  } else {
    DEBUG((DEBUG_ERROR, "SaPegHob not found\n"));
    ASSERT(SaPegHob != NULL);
    return FALSE;
  }
  //
  // PcieConfig->RootPort[RpIndex].ClkReqDetect check is skipped in the below condition for SA, since ClkReqDetect is TRUE always
  // @TODO : check with PCH team and remove the 2nd parameter for both SA and PCH if not required
  //
  if (EFI_ERROR (CheckClkReq (PchClockUsageCpuPcie0 + RpIndex))) {
    DEBUG ((DEBUG_INFO, "CLKREQ is not Low, disabling power management for RP %d.\n", RpIndex));
    return FALSE;
  }
  return TRUE;
}

/**
  Disables the root port using DEV_EN bit.

  @param[in] RpIndex            Root Port Number

**/
VOID
DevEnDisablePcieRootPort (
  IN UINT8   RpIndex
)
{
  UINT64     McD0BaseAddress;
  UINT32     DevEn;
  UINTN      RpDevice;
  UINTN      RpFunction;

  DEBUG ((DEBUG_INFO, "DevEnDisablePcieRootPort Start\n"));

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DevEn = PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN);
  DEBUG ((DEBUG_VERBOSE, "DevEn = %x\n", DevEn));
  GetCpuPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);

  switch (RpDevice)
  {
   case 6:
     DevEn &= ~B_SA_DEVEN_D6EN_MASK;
     break;
   case 1:
     if (RpFunction == 1) {
       DevEn &= ~B_SA_DEVEN_D1F1EN_MASK;
     } else if (RpFunction == 2) {
       DevEn &= ~B_SA_DEVEN_D1F2EN_MASK;
     } else {
       DevEn &= ~B_SA_DEVEN_D1F0EN_MASK;
     }
     break;
  }
  PciSegmentWrite32 (McD0BaseAddress + R_SA_DEVEN, DevEn);
  DEBUG ((DEBUG_VERBOSE, "DevEn after write = %x\n", PciSegmentRead32(McD0BaseAddress + R_SA_DEVEN)));
  DEBUG ((DEBUG_INFO, "DevEnDisablePcieRootPort End\n"));
  return;
}

/**
  Disables the root port. Depending on 2nd param, port's PCI config space may be left visible
  to prevent function swapping

  @param[in] RpIndex            Root Port Number.
  @param[in] KeepPortVisible    Indicates if the port's interface should be visible on PCI Bus0.
**/
VOID
DisableCpuPcieRootPort (
  IN UINT8   RpIndex,
  IN BOOLEAN KeepPortVisible
  )
{
  UINT32      Data32;
  UINT32      LoopTime;
  UINT32      TargetState;
  UINT32      LinkActive;
  UINT64      RpBase;

  DEBUG ((DEBUG_INFO, "CPU: DisablePcieRootPort(%d) Start\n", RpIndex + 1));

  Data32 = 0;
  RpBase = CpuPcieBase(RpIndex);

  CpuPcieRpSbiRead32 (RpIndex, (R_PCIE_LSTS-2), &Data32); /// Access LSTS using dword-aligned read
  LinkActive = (Data32 >> 16) & B_PCIE_LSTS_LA;

  if (LinkActive) {
    ///
    /// If device is present disable the link.
    ///
    DEBUG ((DEBUG_INFO, "Device present. Disabling the link.\n"));
    PciSegmentAndThenOr32 (RpBase + R_PCIE_LCTL, ~0u, B_PCIE_LCTL_LD);
  } else {
    ///
    /// Otherwise if device is not present perform the following steps using sideband access:
    /// 1.  Set B0:Dxx:Fn:338h[26] = 1b
    /// 2.  Poll B0:Dxx:Fn:328h[31:24] until 0x1 with 50ms timeout
    /// 3.  Set B0:Dxx:Fn +408h[27] =1b
    ///

    DEBUG ((DEBUG_INFO, "Device is not present.Stopping the port.\n"));
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEALC, ~0u, B_PCIE_PCIEALC_BLKDQDA);

    TargetState = V_PCIE_PCIESTS1_LTSMSTATE_DETRDY;
    for (LoopTime = 0; LoopTime < 5000; LoopTime++) {
      Data32 = PciSegmentRead32(RpBase + R_PCIE_PCIESTS1);
      if (((Data32 & B_PCIE_PCIESTS1_LTSMSTATE) >> B_PCIE_PCIESTS1_LTSMSTATE_OFFSET) == TargetState) {
        break;
      }
      MicroSecondDelay (10);
    }

    ///
    ///
  }
  ///
  /// Set offset 408h[27] to 1b to disable squelch.
  ///
  DEBUG ((DEBUG_VERBOSE, "Disable squelch\n"));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PHYCTL4, ~0u, B_PCIE_PHYCTL4_SQDIS);
  ///
  /// Make port disappear from PCI bus
  ///
  if (!KeepPortVisible) {
    DEBUG ((DEBUG_INFO, "CPU: Hiding the port %d\n", RpIndex + 1));
    ///
    /// Function disable port using DEV_EN register.
    ///
    DevEnDisablePcieRootPort (RpIndex);
  }

  DisableClock (PchClockUsageCpuPcie0 + RpIndex);
  DEBUG ((DEBUG_INFO, "CPU: DisablePcieRootPort() End\n"));
}

/**
  This function creates Capability and Extended Capability List

  @param[in] RpIndex         Root Port index
  @param[in] RpBase          Root Port pci segment base address
  @param[in] CpuPcieRpConfig    Pointer to a CPU_PCIE_CONFIG that provides the platform setting

**/
VOID
CpuPcieInitCapabilityList (
  IN UINT32                           RpIndex,
  IN UINT64                           RpBase,
  IN CONST CPU_PCIE_ROOT_PORT_CONFIG  *CpuPcieRpConfig
  )
{
  UINT32      Data32;
  UINT16      Data16;
  UINT8       Data8;
  UINT16      NextCap;

  DEBUG ((DEBUG_INFO, "CpuPcieInitCapabilityList start\n"));
  ///
  /// Build Capability linked list
  /// 1.  Read and write back to capability registers 34h, 41h, 81h and 91h using byte access.
  /// 2.  Program NSR, A4h[3] = 0b
  ///
  Data8 = PciSegmentRead8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET);
  PciSegmentWrite8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET, Data8);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_CLIST);
  PciSegmentWrite16 (RpBase + R_PCIE_CLIST, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_MID);
  PciSegmentWrite16 (RpBase + R_PCIE_MID, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_SVCAP);
  PciSegmentWrite16 (RpBase + R_PCIE_SVCAP, Data16);

  Data32 = PciSegmentRead32 (RpBase + R_PCIE_PMCS);
  Data32 &= (UINT32) ~(B_PCIE_PMCS_NSR);
  PciSegmentWrite32 (RpBase + R_PCIE_PMCS, Data32);

  ///
  /// II.Build PCI Extended Capability linked list
  /// 0xEDC - PL16MECH(CAPID:0027h) Physical Layer 16.0 GT/s Margining Extended Capability Header
  /// 0xA9C - PL16GECH(CAPID:0026h) Physical Layer 16.0 GT/s Extended Capability Header
  /// 0xA90 - DLFECH  (CAPID:0025h) Data Link Feature Extended Capability Header
  /// 0xA30 - SPEECH  (CAPID:0019h) Secondary PCI Express Extended Capability Header
  /// 0xA00 - DPCECH  (CAPID:001Dh)
  /// 0x280 - VCECH   (CAPID:0002h) VC capability
  /// 0x150 - PTMECH  (CAPID:001Fh) PTM Extended Capability Register
  /// 0x200 - L1SSECH (CAPID:001Eh) L1SS Capability register
  /// 0x220 - ACSECH  (CAPID:000Dh) ACS Capability register
  /// 0x100 - AECH    (CAPID:0001h) Advanced Error Reporting Capability
  ///
  /*
  a. NEXT_CAP = 0h
  */
  NextCap     = V_PCIE_EXCAP_NCO_LISTEND;

  /*
  b. Program [0xEDC] Physical Layer 16.0 GT/s Margining Extended Capability Header(PL16MECH)
    1. Set Next Capability Offset, 0xEDC[31:20] = NEXT_CAP
    2. Set Capability Version, 0xEDC[19:16] = 1h
    3. Set Capability ID, 0xEDC[15:0] = 0027h
    4. NEXT_CAP = 0xEDC
  */
  Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_PL16MECH_CID;
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  NextCap = R_PCIE_PL16MECH;
  PciSegmentWrite32 (RpBase + R_PCIE_PL16MECH, Data32);
  DEBUG ((DEBUG_VERBOSE, "Physical Layer 16.0 GT/s Margining Extended Capability Header\n"));
  DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_PL16MECH_CID));

  /*
  c. Program [0xA9C] Physical Layer 16.0 GT/s Extended Capability Header(PL16GECH)
    1. Set Next Capability Offset, 0xA9C[31:20] = NEXT_CAP
    2. Set Capability Version, 0xA9C[19:16] = 1h
    3. Set Capability ID, 0xA9C[15:0] = 0026h
    4. NEXT_CAP = 0xA9C
  */
  Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_PL16GECH_CID;
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  NextCap = R_PCIE_PL16GECH;
  PciSegmentWrite32 (RpBase + R_PCIE_PL16GECH, Data32);
  DEBUG ((DEBUG_VERBOSE, "Physical Layer 16.0 GT/s Extended Capability Header\n"));
  DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_PL16GECH_CID));

  /*
  d. Program [0xA90] Data Link Feature Extended Capability Header(DLFECH)
    1. Set Next Capability Offset, 0xA90[31:20] = NEXT_CAP
    2. Set Capability Version, 0xA90[19:16] = 1h
    3. Set Capability ID, 0xA90[15:0] = 0025h
    4.  NEXT_CAP = 0xA90
  */
  Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_DLFECH_CID;
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  NextCap = R_PCIE_DLFECH;
  PciSegmentWrite32 (RpBase + R_PCIE_DLFECH, Data32);
  DEBUG ((DEBUG_VERBOSE, "Data Link Feature Extended Capability Header\n"));
  DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_DLFECH_CID));

  /*
  e. If the RP is GEN3 capable (by fuse and BIOS policy), enable Secondary PCI Express Extended Capability
    1. Set Next Capability Offset,0xA30[31:20] = NEXT_CAP
    2. Set Capability Version, 0xA30[19:16] = 1h
    3. Set Capability ID,  0xA30[15:0] = 0019h
    4. NEXT_CAP = 0xA30
    ELSE, set 0xA30[31:0] = 0
  */
  Data32 = 0;
  if (CpuPcieGetMaxLinkSpeed(RpBase) >= V_PCIE_LCAP_MLS_GEN3) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_SPE_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "Secondary PCI Express Extended Capability\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_SPE_CID));
    NextCap = R_PCIE_SPEECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_SPEECH, Data32);

  /*
  f. If Downstream Port Containment is enabled, then
    1. Set Next Capability Offset, 0xA00[31:20] = NEXT_CAP
    2. Set Capability Version, 0xA00[19:16] = 1h
    3. Set Capability ID, 0xA00[15:0] = 001h
    4. NEXT_CAP = 0xA00
    ELSE, set 0xA00 [31:0] = 0
  */
  Data32 = 0;
  if (CpuPcieRpConfig->PcieRpCommonConfig.DpcEnabled == TRUE) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_DPC_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "Downstream port containment\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_DPC_CID));
    NextCap = R_PCIE_DPCECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_DPCECH, Data32);

  /*
  g. If VC is enabled, then
    1. Set Next Capability Offset, 0x280[31:20] = NEXT_CAP
    2. Set Capability Version, 0x280[19:16] = 1h
    3. Set Capability ID, 0x280[15:0] = 002h
    4. NEXT_CAP = 0x280
    ELSE, set 0x280 [31:0] = 0
  */
  Data32 = 0;
  if (CpuPcieRpConfig->VcEnabled == TRUE) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_VC_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "Virtual Channel\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_VC_CID));
    NextCap = R_PCIE_VCECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_VCECH, Data32);

   /*
  h. If support PTM
    1. Set Next Capability Offset, Dxx:Fn +150h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +150h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +150h[15:0] = 001Fh
    4. Read and write back to Dxx:Fn +144h
    5. NEXT_CAP = 150h
    ELSE, set Dxx:Fn +150h [31:0] = 0
    In both cases: read Dxx:Fn + 154h, set BIT1 and BIT2 then write it back
  */
  Data32 = 0;
  if (CpuPcieRpConfig->PcieRpCommonConfig.PtmEnabled == TRUE) {
    Data32 = (V_PCIE_PTMECH_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_PTM_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "PTM\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_PTM_CID));
    NextCap = R_PCIE_PTMECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_PTMECH, Data32);
  Data32 = PciSegmentRead32 (RpBase + R_PCIE_EX_PTMCAP_OFFSET);
  PciSegmentWrite32 (RpBase + R_PCIE_EX_PTMCAP_OFFSET, (Data32 | B_PCIE_EX_PTMCAP_PTMRC | B_PCIE_EX_PTMCAP_PTMRSPC));

  /*
  i. If support L1 Sub-State
    1. Set Next Capability Offset, Dxx:Fn +200h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +200h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +200h[15:0] = 001Eh
    4. Read and write back to Dxx:Fn +204h
    5. Refer to section 8.3 for other requirements (Not implemented here)
    6. NEXT_CAP = 200h
    ELSE, set Dxx:Fn +200h [31:0] = 0, and read and write back to Dxx:Fn +204h
  */
  Data32 = 0;
  if (IsClkReqAssigned (PchClockUsageCpuPcie0 + RpIndex) &&
    (CpuPcieRpConfig->PcieRpCommonConfig.L1Substates != CpuPcieL1SubstatesDisabled)) {
    Data32  = (V_PCIE_L1S_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_L1S_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "L1SS\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_L1S_CID));
    NextCap = R_PCIE_L1SECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_L1SECH, Data32);

  /*
  j. If support ACS
    1. Set Next Capability Offset, Dxx:Fn +140h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +140h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +140h[15:0] = 000Dh
    4. Read and write back to Dxx:Fn +144h
    5. NEXT_CAP = 140h
    ELSE, set Dxx:Fn +140h [31:0] = 0, and read and write back to Dxx:Fn +144h
  */
  Data32 = 0;
  if (CpuPcieRpConfig->PcieRpCommonConfig.AcsEnabled == TRUE) {
    Data32 = (V_PCIE_ACSECH_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_ACS_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    DEBUG ((DEBUG_VERBOSE, "ACS\n"));
    DEBUG ((DEBUG_VERBOSE, "NextCap = %x \t Capability ID = %x\n", NextCap, V_PCIE_EX_ACS_CID));
    NextCap = R_PCIE_ACSECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_ACSECH, Data32);

  Data32 = PciSegmentRead32 (RpBase + R_PCIE_ACSCAPR);
  PciSegmentWrite32 (RpBase + R_PCIE_ACSCAPR, Data32);

  /*
  k. If support Advanced Error Reporting
    1. Set Next Capability Offset, Dxx:Fn +100h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +100h[19:16] = 1h
    3. Set Capability ID, Dxx:Fn +100h[15:0] = 0001h
    ELSE
    1. Set Next Capability Offset, Dxx:Fn +100h[31:20] = NEXT_CAP
    2. Set Capability Version, Dxx:Fn +100h[19:16]  = 0h
    3. Set Capability ID, Dxx:Fn +100h[15:10]  = 0000h
  */
  Data32 = 0;
  if (CpuPcieRpConfig->PcieRpCommonConfig.AdvancedErrorReporting) {
    Data32 = (V_PCIE_AECH_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_AEC_CID;
  }
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  PciSegmentWrite32 (RpBase + R_PCIE_AECH, Data32);

  DEBUG ((DEBUG_INFO, "CpuPcieInitCapabilityList end\n"));

  //
  // Mask Unexpected Completion uncorrectable error
  //
  PciSegmentOr32 (RpBase + R_PCIE_UEM, B_PCIE_UEM_UC);
}

/*
Checks if given rootport has an endpoint connected

@param[in] DeviceBase       PCI segment base address of root port

@retval                     TRUE if endpoint is connected
@retval                     FALSE if no endpoint was detected
*/
BOOLEAN
CpuPcieIsEndpointConnected(
UINT64 DeviceBase
)
{
  return !!(PciSegmentRead16(DeviceBase + R_PCIE_SLSTS) & B_PCIE_SLSTS_PDS);
}

/**
Get information about the endpoint

@param[in]  RpBase      Root port pci segment base address
@param[in]  TempPciBus  Temporary bus number
@param[out] DeviceInfo  Device information structure

@raturn TRUE if device was found, FALSE otherwise
**/
BOOLEAN
CpuPcieGetDeviceInfo(
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
  DEBUG((DEBUG_INFO, "CpuPcieGetDeviceInfo Start\n"));
  //
  // Check for device presence
  //
  if (!CpuPcieIsEndpointConnected(RpBase)) {
    DEBUG((DEBUG_INFO, "Endpoint is not connected\n"));
    return FALSE;
  }

  //
  // Assign temporary bus numbers to the root port
  //
  PciSegmentAndThenOr32(
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32)~B_PCI_BRIDGE_BNUM_SBBN_SCBN,
    ((UINT32)(TempPciBus << 8)) | ((UINT32)(TempPciBus << 16))
    );

  //
  // A config write is required in order for the device to re-capture the Bus number,
  // according to PCI Express Base Specification, 2.2.6.2
  // Write to a read-only register VendorID to not cause any side effects.
  //
  EpBase = PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, TempPciBus, 0, 0, 0);
  PciSegmentWrite16(EpBase + PCI_VENDOR_ID_OFFSET, 0x8086);

  Data32 = PciSegmentRead32(EpBase + PCI_VENDOR_ID_OFFSET);
  DeviceInfo->Vid = (UINT16)(Data32 & 0xFFFF);
  DeviceInfo->Did = (UINT16)(Data32 >> 16);

  EpLinkSpeed = 0;
  if (Data32 != 0xFFFFFFFF) {
    EpPcieCapPtr = PcieFindCapId(SA_SEG_NUM, TempPciBus, 0, 0, EFI_PCI_CAPABILITY_ID_PCIEXP);
    if (EpPcieCapPtr != 0) {
      EpLinkSpeed = PciSegmentRead8(EpBase + EpPcieCapPtr + R_PCIE_LCAP_OFFSET) & B_PCIE_LCAP_MLS;
    }
    DeviceInfo->MaxLinkSpeed = EpLinkSpeed;
  }

  //
  // Clear bus numbers
  //
  PciSegmentAnd32(RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, (UINT32)~B_PCI_BRIDGE_BNUM_SBBN_SCBN);

  DEBUG((DEBUG_INFO, "VID: %04X DID: %04X  MLS: %d\n",
    DeviceInfo->Vid, DeviceInfo->Did, DeviceInfo->MaxLinkSpeed));
  DEBUG((DEBUG_INFO, "CpuPcieGetDeviceInfo End\n"));
  return (Data32 != 0xFFFFFFFF);
}

/**
  The function to change the root port speed based on policy

  @param[in] RpIndex      Port index
  @param[in] SiPolicyPpi  The SI Policy PPI instance

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_UNSUPPORTED         DEKEL Firmware Download fails.
**/
EFI_STATUS
CpuPcieRpSpeedChange (
  VOID
  )
{
  EFI_STATUS                        Status;
  UINTN                             PortIndex;
  UINTN                             MaxCpuPciePortNum;
  UINT64                            PciRootPortRegBase[CPU_PCIE_MAX_ROOT_PORTS];
  UINTN                             RpDev;
  UINTN                             RpFunc;
  UINTN                             LinkRetrainedBitmap;
  UINTN                             TimeoutCount;
  UINT32                            MaxLinkSpeed;
  SA_PEG_HOB                        *SaPegHob;
  UINT8                             TempPciBusMin;
  BOOLEAN                           DevicePresent;
  PCIE_DEVICE_INFO                  DevInfo;

  TempPciBusMin = PcdGet8(PcdSiliconInitTempPciBusMin);

  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  MaxCpuPciePortNum = GetMaxCpuPciePortNum();
  if (SaPegHob == NULL) {
    DEBUG((DEBUG_ERROR, "SaPegHob not found\n"));
    ASSERT(SaPegHob != NULL);
    return EFI_NOT_FOUND;
  }
  //
  // Since we are using the root port base many times, it is best to cache them.
  //
  for (PortIndex = 0; PortIndex < MaxCpuPciePortNum; PortIndex++) {
    PciRootPortRegBase[PortIndex] = 0;
    Status = GetCpuPcieRpDevFun (PortIndex, &RpDev, &RpFunc);
    if (EFI_ERROR (Status)) {
      ASSERT (FALSE);
      continue;
    }
    PciRootPortRegBase[PortIndex] = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, (UINT32) RpDev, (UINT32) RpFunc, 0);
  }
  ///
  /// NOTE: Detection of Non-Complaint PCI Express Devices
  ///
  LinkRetrainedBitmap = 0;
  for (PortIndex = 0; PortIndex < MaxCpuPciePortNum; PortIndex++) {
    if (PciRootPortRegBase[PortIndex] == 0) {
      continue;
    }
    if (PciSegmentRead16 (PciRootPortRegBase[PortIndex] + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }
    if (!(SaPegHob->RpEnabledMask & (BIT0 << PortIndex))) {
      continue;
    }
    MaxLinkSpeed = CpuPcieGetMaxLinkSpeed (PciRootPortRegBase[PortIndex]);
    DevicePresent = CpuPcieGetDeviceInfo(PciRootPortRegBase[PortIndex], TempPciBusMin, &DevInfo);

    if (DevicePresent && (DevInfo.MaxLinkSpeed < MaxLinkSpeed)){
      MaxLinkSpeed = DevInfo.MaxLinkSpeed;
    }

    if (MaxLinkSpeed > 1) {
      //
      // DEKEL FW should be downloaded before speed change, so check for download status before initiating a speed change.
      //
      if ((PortIndex == 0) && (DekelFwStatus(CPU_SB_PID_DEKEL_IO4) == FALSE)) { // PortIndex = 0 always corresponds to PEG 060 in BIOS
        continue;
      }
      if ((PortIndex != 0) && (DekelFwStatus(CPU_SB_PID_DEKEL_IO16) == FALSE)) { // Dekel FW status needs to be checked only once for x16 PHY
        break; // If DekelIo16FwStatus == FALSE, just break - speed change cannot happen for the rest of the ports in x16 controller
      }

      PciSegmentAndThenOr16 (
        PciRootPortRegBase[PortIndex] + R_PCIE_LCTL2,
        (UINT16) ~B_PCIE_LCTL2_TLS,
        (UINT16) MaxLinkSpeed
        );
      DEBUG((DEBUG_INFO, "Program TLS to %x \n", MaxLinkSpeed));
      if (CpuPcieIsLinkActive (PciRootPortRegBase[PortIndex])) {
        //
        // Retrain the link if device is present
        //
        PciSegmentOr16 (PciRootPortRegBase[PortIndex] + R_PCIE_LCTL, B_PCIE_LCTL_RL);
        LinkRetrainedBitmap |= (1u << PortIndex);
        DEBUG((DEBUG_INFO, "Retrain the link if device is present! \n"));
      }
    }
  }

  //
  // 100 ms timeout while checking for link active on retrained link
  //
  for (TimeoutCount = 0; ((LinkRetrainedBitmap != 0) && (TimeoutCount < 1000)); TimeoutCount++) {
    //
    // Delay 100 us
    //
    MicroSecondDelay (100);
    //
    // Check for remaining root port which was link retrained
    //
    for (PortIndex = 0; PortIndex < MaxCpuPciePortNum; PortIndex++) {
      if ((LinkRetrainedBitmap & (1u << PortIndex)) != 0) {
        //
        // If the link is active, clear the bitmap
        //
        if (PciSegmentRead16 (PciRootPortRegBase[PortIndex] + R_PCIE_LSTS) & B_PCIE_LSTS_LA) {
          LinkRetrainedBitmap &= ~(1u << PortIndex);
        }
      }
    }
  }
  //
  // If 100 ms has timeout, and some link are not active, print a message and continue execution
  //
  if (LinkRetrainedBitmap != 0) {
    for (PortIndex = 0; PortIndex < MaxCpuPciePortNum; PortIndex++) {
      Status = GetCpuPcieRpDevFun (PortIndex, &RpDev, &RpFunc);
      if ((LinkRetrainedBitmap & (1u << PortIndex)) != 0) {
        DEBUG((DEBUG_ERROR, "Link failed to train to higher speed for port %d, Dev Number %x, Func Number %x\n",PortIndex, RpDev, RpFunc));
      }
    }
  }

  return EFI_SUCCESS;
}

/*
  Some PCIe devices may take long time between they become detected and form a link.
  This function waits until all enabled, non-empty rootports form a link or until a timeout

  @param[in] MaxRootPorts      number of rootports
  @param[in] DisabledPortMask  mask of rootprots that don't need to be considered
*/
VOID
CpuPcieWaitForLinkActive (
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

  DEBUG ((DEBUG_INFO, "CpuPcieWaitForLinkActive, RP mask to wait for = 0x%08x\n", PortMask));
  while (Time < LINK_ACTIVE_POLL_TIMEOUT) {
    for (Index = 0; Index < MaxRootPorts; Index ++) {
      if (!(PortMask & (BIT0 << Index))) {
        continue;
      }
      RpBase = CpuPcieBase (Index);
      //
      // if PDS is not set or if LA is set then this rootport is done - clear it from mask
      //
      if (!CpuPcieIsEndpointConnected (RpBase) || CpuPcieIsLinkActive (RpBase)) {
        PortMask &= ~ (BIT0 << Index);
      }
    }
    if (PortMask == 0x0) {
      DEBUG ((DEBUG_INFO, "CpuPcieWaitForLinkActive, all RPs done, lost %dms waiting\n", Time/1000));
      return;
    }
    MicroSecondDelay (LINK_ACTIVE_POLL_INTERVAL);
    Time += LINK_ACTIVE_POLL_INTERVAL;
  }

  DEBUG ((DEBUG_WARN, "CpuPcieWaitForLinkActive, timeout with the following RPs still not done: 0x%08x\n", PortMask));
}

/*
  After programming the linear mode HW EQ flow, BIOS performs and link retrain
  and then polls for Hardware Equalization done bit.
  This function waits until HAED bit is set or until a timeout
*/
VOID
CpuPcieWaitForHwEqDone (
  VOID
  )
{
  UINT64 RpBase;
  UINT32 Time;
  UINT16 Haed;
  UINT16 Px16ghaed;
  UINT8  Gen3Haed;
  UINT8  Gen4Haed;
  UINT8  RpIndex;
  UINT8  MaxCpuPciePortNum;

  Time = 0;
  Gen3Haed = 0;
  Gen4Haed = 0;
  MaxCpuPciePortNum = GetMaxCpuPciePortNum();

  DEBUG ((DEBUG_INFO, "CpuPcieWaitForHwEqDone Begin:\n"));
  DEBUG((DEBUG_INFO, "mDoGen3HwEqRpMask = %x\n", mDoGen3HwEqRpMask));
  DEBUG((DEBUG_INFO, "mDoGen4HwEqRpMask = %x\n", mDoGen4HwEqRpMask));
  do {
    for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
      if ((mDoGen3HwEqRpMask & (BIT0 << RpIndex)) || (mDoGen4HwEqRpMask & (BIT0 << RpIndex))) {
        RpBase = CpuPcieBase (RpIndex);
        Haed = (PciSegmentRead16 (RpBase + R_PCIE_EQCFG1));
        Haed &= (UINT16)B_PCIE_EQCFG1_HAED;
        Px16ghaed = (PciSegmentRead16 (RpBase + R_PCIE_EQCFG4));
        Px16ghaed &= (UINT16)B_PCIE_EQCFG4_PX16GHAED;
        }
      if ((Haed == (UINT16)B_PCIE_EQCFG1_HAED) && (Px16ghaed == (UINT16)B_PCIE_EQCFG4_PX16GHAED)) {
        DEBUG ((DEBUG_INFO, "Gen3 and Gen4 hardware Equalization done bit is set for Root Port %x\n", RpIndex));
        Gen3Haed |= (BIT0 << RpIndex);
        Gen4Haed |= (BIT0 << RpIndex);
        // For H/S SKU, continue the loop
        break;
      } else if (Haed == (UINT16)B_PCIE_EQCFG1_HAED) {
        DEBUG ((DEBUG_INFO, "Gen3 Hardware Equalization Done bit is set for Root Port %x\n", RpIndex));
        Gen3Haed |= (BIT0 << RpIndex );
        // For H/S SKU, continue the loop
        break;
      } else if (Px16ghaed == (UINT16)B_PCIE_EQCFG4_PX16GHAED) {
        DEBUG ((DEBUG_ERROR, "Gen4 Hardware Equalization Done bit is set for Root Port %x without Gen3 Hardware Equalization Done bit set\n", RpIndex));
        // For H/S SKU, continue the loop
        break;
      }
    }
    if ((Gen3Haed == mDoGen3HwEqRpMask) && (Gen4Haed  == mDoGen4HwEqRpMask)) {
      break; // All the HAED bits are set, so break the do-while.
    }
    MicroSecondDelay (HWEQ_DONE_POLL_INTERVAL);
    Time += HWEQ_DONE_POLL_INTERVAL;
  } while (Time < HWEQ_DONE_POLL_TIMEOUT);
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    if (((mDoGen3HwEqRpMask & (BIT0 << RpIndex)) || (mDoGen4HwEqRpMask & (BIT0 << RpIndex))) && (((Gen3Haed & (BIT0 << RpIndex)) || (Gen4Haed & (BIT0 << RpIndex))) == 0)) {
      DEBUG ((DEBUG_INFO, "Hardware Equalization Done bit is NOT set for Root Port %x even after timeout!!!\n", RpIndex));
      if (!IsSimicsEnvironment() && (RpIndex == 0)) {
        ASSERT(FALSE);// For U/Y SKU, it should assert only for RpIndex 0
      }
    }
  }
}

/**
  Maps the index of the first port on the same controller.

  @param[in] RpIndex     Root Port Number (0-based)

  @retval Index of the first port on the first controller.
**/
UINT32
GetCpuPcieFirstPortIndex (
  IN     UINT32  RpIndex
  )
{
  switch (RpIndex)
  {
   case 0:
     RpIndex = 0; //RpIndex = 0 always maps to BDF = 060 irrespective of the SKU and there is only one Root port so return the same number
     break;
   case 1:
     RpIndex = 1; //RpIndex = 1 maps tp BDF = 010
   case 2:
   case 3:
     RpIndex = 2; //RpIndex = 2 or 3 maps to BDF = 01 1/2 for which the first root port is 2
     break;
   default:
     RpIndex = 0; //RpIndex = 0 always maps to BDF = 060 irrespective of the SKU and there is only one Root port so return the same number
     break;
  }
  return RpIndex;
}
/**
  Program controller power management settings.
  This settings are relevant to all ports including disabled ports.
  All registers are located in the first port of the controller.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex                         The root port to be initialized (zero based).
  @param[in]  TrunkClockGateEn                Indicates whether trunk clock gating is to be enabled,
                                              requieres all controller ports to have dedicated CLKREQ#
                                              or to be disabled.
  @param[in]  DisableRootPortClockGating      Indicates whether the PCI Express Clock Gating for each root port
                                              is enabled by platform modules.
  @param[in]  DisableRootPortPowerGating      Indicates whether the PCI Express Power Gating for each root port
                                              is enabled by platform modules.
**/
VOID
CpuPcieConfigureControllerBasedPowerManagement (
  IN  UINT32   RpIndex,
  IN  BOOLEAN  TrunkClockGateEn,
  IN  BOOLEAN  DisableRootPortClockGating,
  IN  BOOLEAN  DisableRootPortPowerGating
  )
{
  UINT32                    Data32And;
  UINT32                    Data32Or;
  UINT64                    RpBase;
  SA_PEG_HOB                *SaPegHob;
  CONST CPU_PCIE_ROOT_PORT_CONFIG   *RpConfig;

  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  if (SaPegHob == NULL) {
    DEBUG((DEBUG_INFO, "SaPegHob not found!\n"));
    ASSERT(SaPegHob != NULL);
    return;
  }

  RpBase = CpuPcieBase(RpIndex);

  RpConfig = &mCpuPcieRpConfig->RootPort[RpIndex];

  DEBUG ((DEBUG_INFO, "CpuPcieConfigurePortBasedPowerManagement(%d) Start\n", RpIndex + 1));

  if (!DisableRootPortClockGating) {
    DEBUG ((DEBUG_VERBOSE, "Clock gating is enabled!\n"));
    ///
    /// Program (R_PCIE_CCFG) D0h
    /// Set D0h[15] to 1b for dynamic clock gating enable when ISM is in Idle state
    ///
    PciSegmentAndThenOr32 (RpBase + R_PCIE_CCFG, ~0u, B_PCIE_CCFG_DCGEISMA);
    ///
    /// Program (R_PCIE_RPDCGEN) E1h
    /// Set E1h[7] to 1b to enable static clock gating on PCIe root ports.
    /// Set E1h[5] to 1b to enable PCIe Link clock trunk gating.
    /// Set E1h[4] to 1b to enable PCIe backbone clock trunk gating.
    /// Set E1h[2] to 1b to enable shared resource dynamic backbone clock gating.
    /// Set E1h[6] to 1b to enable Partition/Trunk Oscillator clock gating; if all ports on the controller support CLKREQ#.
    ///
    Data32Or  = (B_PCIE_RPDCGEN_RPSCGEN | B_PCIE_RPDCGEN_LCLKREQEN | B_PCIE_RPDCGEN_BBCLKREQEN | B_PCIE_RPDCGEN_SRDBCGEN);
    if (TrunkClockGateEn) {
      DEBUG ((DEBUG_INFO, "Setting PTOCGE \n"));
      Data32Or |= B_PCIE_RPDCGEN_PTOCGE;
    }
    PciSegmentAndThenOr32 (RpBase + R_PCIE_SPR, ~0u, (UINT32) (Data32Or << 8)); ///< For 32-bit boundary alignment for 0xE1 (RPDCGEN), shift by 8 bits from 0xE0
    ///
    /// Program (R_PCIE_RPPGEN) E2h
    /// Set E2h[4] to 1b to enable side clock gating.
    ///
    PciSegmentAndThenOr32 (RpBase + R_PCIE_SPR, ~0u, (UINT32) (B_PCIE_RPPGEN_SEOSCGE << 16)); ///< For 32-bit boundary alignment for 0xE1 (RPDCGEN), shift by 8 bits from 0xE0
    ///
    /// @todo: Program 434[3:2] = 11b for OSC clock gate hysteresis.
    ///
  }

  if (!DisableRootPortPowerGating) {
    DEBUG ((DEBUG_VERBOSE, "Power gating is enabled!\n"));
    ///
    /// Set F5h[1:0] to 11b  (R_PCH_PCIE_CFG_PHYCTL2)
    /// Set F7h[3:2] = 00b   (R_PCH_PCIE_CFG_IOSFSBCS)
    ///
    Data32And = (UINT32) ~(B_PCIE_IOSFSBCS_SIID_MASK << 24);  ///< For 32-bit boundary alignment, shift by 24bits from 0xF4 to reach 0xF7
    Data32Or = (B_PCIE_PHYCTL2_PXPG3PLLOFFEN | B_PCIE_PHYCTL2_PXPG2PLLOFFEN) << 8; ///< For 32-bit boundary alignment for 0xF7 ( IOSFSBCS) to offset 0xF4
    PciSegmentAndThenOr32 (RpBase + R_PCIE_F4, Data32And, Data32Or);

    ///
    /// Program (WPDMPGEP) E8h
    /// Set E8h[17] to 1b to wake PLL on exit from mod-PHY power gating in detect state.
    ///
    Data32Or = B_PCIE_PWRCTL_WPDMPGEP | B_PCIE_PWRCTL_DBUPI;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PWRCTL, ~0u, Data32Or);

    ///
    /// Program (R_PCIE_PCIEPMECTL2) 424h
    /// Set 424h[11] to 1b to enable mod-PHY common lane power gating.
    ///
    Data32Or = B_PCIE_PCIEPMECTL2_PHYCLPGE;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEPMECTL2, ~0u, Data32Or);

    ///
    /// Progarm (R_PCIE_HWSNR) 5F0h
    /// Set 5F0h[3:0] to 0101b for Bank Enable Pulse Width.
    /// Set 5F0h[7:4] to 01b for Restore Enable Pulse Width. 01b = 2 clocks.
    /// Set 5F0h[9:8] to 10b for Entry and Exit hysteresis. 10b = 16clocks.
    ///
    Data32And = (UINT32)~(B_PCIE_HWSNR_BEPW_MASK | B_PCIE_HWSNR_REPW_MASK | B_PCIE_HWSNR_EEH_MASK);
    Data32Or = B_PCIE_HWSNR_BEPW_8_CLKS | (0x1 << B_PCIE_HWSNR_REPW_OFFSET) | (0x2 << B_PCIE_HWSNR_EEH_OFFSET);
    PciSegmentAndThenOr32 (RpBase + R_PCIE_HWSNR, Data32And, Data32Or);

    ///
    /// Program (R_PCIE_PGCTRL) 5F4h
    /// Set 5F4h[2:0] to 010b for PM_REQ Block Response Time. 010b = 10micro sec.
    ///
    Data32Or = B_PCIE_PGCTRL_PMREQBLKRSPT_5MICRO_SEC;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PGCTRL, ~0u, Data32Or);

    ///
    /// Program (R_PCIE_ADVMCTRL) 5BCh
    /// Set 5BCh[18:16] to 0b for PM_REQ Clock wake control. A value of 2 requested by FV post silicon for Pkg C checkouts.
    /// Set 5BCh[14] to 0b for ClkReq Serialization Mode.
    /// Set 5BCh[11] to 0b for Reset Receiver Link Layer Common Logic.
    /// Set 5BCh[10] to 0b for Reset Link Layer in Gen1, 2 Recovery.
    /// Set 5BCh[22] to 1b for InRxL0 Control.
    /// Set 5BCh[20] to 1b for EIOS Disable DeSkew.
    /// Set 5BCh[19] to 1b for EIOS Mask Receiver Datapath.
    /// Set 5BCh[13] to 1b for Gen3 Short TLP Framing Error Reporting.
    /// Set 5BCh[7:5] to 010b for PM_REQ Block and Power Gate Response time. 010b = 10 micro sec.
    ///
    Data32And = (UINT32)~(B_PCIE_ADVMCTRL_PMREQCWC_MASK | B_PCIE_ADVMCTRL_CLKREQSM | B_PCIE_ADVMCTRL_RRLLCL | B_PCIE_ADVMCTRL_RLLG12R);
    Data32Or = (UINT32)(B_PCIE_ADVMCTRL_INRXL0CTRL | B_PCIE_ADVMCTRL_EIOSDISDS | B_PCIE_ADVMCTRL_EIOSMASKRX | B_PCIE_ADVMCTRL_G3STFER | (0x2 << B_PCIE_ADVMCTRL_PMREQBLKPGRSPT_OFFSET) | (0x2 << B_PCIE_ADVMCTRL_PMREQCWC_OFFSET));
    PciSegmentAndThenOr32 (RpBase + R_PCIE_ADVMCTRL, Data32And, Data32Or);

    ///
    /// Program (R_PCIE_PGTHRES) 5C0h.
    /// Set 5C0h[0] to 1b for L1 power gating LTR Enable.
    /// Set 5C0h[31:29] to 10b for L1 power gating LTR Threshold latency Scale value. 010b = 1024nS
    /// Set 5C0h[25:16] to 110010b for L1 power gating LTR Threshold latency value. 110010b (0x32).
    ///
    Data32Or = (0x2 << B_PCIE_PGTHRES_L1PGLTRTLSV_OFFSET) | (0x32 << B_PCIE_PGTHRES_L1PGLTRTLV_OFFSET);
    if ((SaPegHob->CpuPcieRp.L1SubStates[RpIndex] == 0) || (RpConfig->PcieRpCommonConfig.L1Substates == CpuPcieL1SubstatesDisabled)) {
      Data32Or |= (UINT32)(B_PCIE_PGTHRES_L1PGLTREN);
    }
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PGTHRES, ~0u, Data32Or);

    ///
    /// Program (R_PCIE_ACRG3) 6CCh
    /// Set 6CCh[23:22] to 10b for CPG Wake Control for 8 micro sec.
    ///
    Data32And = (UINT32) ~(B_PCIE_ACRG3_CPGWAKECTRL_MASK);
    Data32Or = V_PCIE_ACRG3_CPGWAKECTRL << B_PCIE_ACRG3_CPGWAKECTRL_OFFSET;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_ACRG3, Data32And, Data32Or);

  }
  ///
  /// @todo: Squelch and CLKREQ# programming pending. To be reviewed after MVE validation.
  ///
}

/**
  Configure ASPM settings which are applicable to both enabled and disabled ports.
  These settings are relevant to all ports including disabled ports.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex                         The root port to be initialized (zero based).
**/
VOID
CpuPcieConfigureASPM (
  IN  UINT32   RpIndex
  )
{
  UINT32         Data32And;
  UINT32         Data32Or;
  UINT64         RpBase;

  RpBase = CpuPcieBase(RpIndex);
  ///
  /// Program (R_PCIE_G4L0SCTL) 0x310
  /// Gen4 Active State L0s Preparation Latency (G4ASL0SPL) 0x310  31:24 0x28
  /// Gen4 Unique Clock N_FTS (G4UCNFTS) 0x310[15:8] 0x80
  /// Gen4 Common Clock N_FTS (G4CCNFTS) 0x310[7:0] 0x5B
  ///
  Data32And = (UINT32) ~(B_PCIE_G4L0SCTL_G4ASL0SPL_MASK | B_PCIE_G4L0SCTL_G4UCNFTS_MASK | B_PCIE_G4L0SCTL_G4CCNFTS_MASK);
  Data32Or = (UINT32) (V_PCIE_G4L0SCTL_G4ASL0SPL << B_PCIE_G4L0SCTL_G4ASL0SPL_OFFSET) | (V_PCIE_G4L0SCTL_G4UCNFTS << B_PCIE_G4L0SCTL_G4UCNFTS_OFFSET) | (V_PCIE_G4L0SCTL_G4CCNFTS << B_PCIE_G4L0SCTL_G4CCNFTS_OFFSET);
  PciSegmentAndThenOr32(RpBase + R_PCIE_G4L0SCTL, Data32And, Data32Or);

  ///
  /// Program (R_PCIE_G3L0SCTL) 0x478
  /// Gen3 Active State L0s Preparation Latency (G3ASL0SPL) 0x478  31:24 0x28
  /// Gen3 Unique Clock N_FTS (G1UCNFTS) 0x310[15:8] 0x40
  /// Gen3 Common Clock N_FTS (G1CCNFTS) 0x310[7:0] 0x2C
  ///
  Data32And = (UINT32) ~(B_PCIE_G3L0SCTL_G3ASL0SPL_MASK | B_PCIE_G3L0SCTL_G3UCNFTS_MASK | B_PCIE_G3L0SCTL_G3CCNFTS_MASK);
  Data32Or = (UINT32) (V_PCIE_G3L0SCTL_G3ASL0SPL << B_PCIE_G3L0SCTL_G3ASL0SPL_OFFSET) | (V_PCIE_G3L0SCTL_G3UCNFTS << B_PCIE_G3L0SCTL_G3UCNFTS_OFFSET) | (V_PCIE_G3L0SCTL_G3CCNFTS << B_PCIE_G3L0SCTL_G3CCNFTS_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_G3L0SCTL, Data32And, Data32Or);

  ///
  /// Program (R_PCIE_PCIEL0SC) 0x318
  /// Gen2 Active State L0s Preparation Latency (G2ASL0SPL) 0x318  31:24 0x14
  /// Gen1 Active State L0s Preparation Latency (G1ASL0SPL) 0x318  23:16 0x14
  ///
  Data32And = (UINT32) ~(UINT32)(B_PCIE_PCIEL0SC_G2ASL0SPL_MASK | B_PCIE_PCIEL0SC_G1ASL0SPL_MASK);
  Data32Or = (UINT32) (V_PCIE_PCIEL0SC_G2ASL0SPL << B_PCIE_PCIEL0SC_G2ASL0SPL_OFFSET) | (V_PCIE_PCIEL0SC_G1ASL0SPL << B_PCIE_PCIEL0SC_G1ASL0SPL_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEL0SC, Data32And, Data32Or);

  ///
  /// Program Active State Link PM control (ASPM) 0x50  1:0 0x3
  ///
  Data32And = (UINT32) ~(UINT32)(B_PCIE_LCTL_ASPM_MASK);
  Data32Or = (UINT32) (V_PCIE_LCTL_ASPM_L0S_L1 << B_PCIE_LCTL_ASPM_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_LCTL, Data32And, Data32Or);

  ///
  /// Program Gen4 L0s Entry Idle Control (ASPM) 0x310  23:22 0x0
  ///
  Data32And = (UINT32) ~(B_PCIE_G4L0SCTL_G4L0SICL_MASK);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_G4L0SCTL, Data32And, ~0u);
}

/**
  Configure LTR Subtraction settings which are applicable to both enabled and disabled ports.
  These settings are relevant to all ports including disabled ports.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex                         The root port to be initialized (zero based).
**/
VOID
CpuPcieConfigureLTRSubtraction (
  IN  UINT32   RpIndex
  )
{
  UINT32         Data32And;
  UINT32         Data32Or;
  UINT64         RpBase;

  RpBase = CpuPcieBase(RpIndex);
  //
  // LTR Subtraction for L1.Standard
  //

  ///
  /// Enable LTR Non-Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRNSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL1STD_LTRNSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRNSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL1STD_LTRNSLSSUBV << B_PCIE_LTRSUBL1STD_LTRNSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRNSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL1STD_LTRNSLSUBV << B_PCIE_LTRSUBL1STD_LTRNSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  ///
  /// Enable LTR Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL1STD_LTRSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL1STD_LTRSLSSUBV << B_PCIE_LTRSUBL1STD_LTRSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL1STD_LTRSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL1STD_LTRSLSUBV << B_PCIE_LTRSUBL1STD_LTRSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL1STD, Data32And, Data32Or);

  //
  // LTR Subtraction for L1.1
  //

  ///
  /// Enable LTR Non-Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRNSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL11_LTRNSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRNSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL11_LTRNSLSSUBV << B_PCIE_LTRSUBL11_LTRNSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRNSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL11_LTRNSLSUBV << B_PCIE_LTRSUBL11_LTRNSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  ///
  /// Enable LTR Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL11_LTRSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL11_LTRSLSSUBV << B_PCIE_LTRSUBL11_LTRSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL11_LTRSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL11_LTRSLSUBV << B_PCIE_LTRSUBL11_LTRSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL11, Data32And, Data32Or);

  //
  // LTR Subtraction for L1.2
  //

  ///
  /// Enable LTR Non-Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRNSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL12_LTRNSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRNSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL12_LTRNSLSSUBV << B_PCIE_LTRSUBL12_LTRNSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);

  ///
  /// Program LTR Non-Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRNSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL12_LTRNSLSUBV << B_PCIE_LTRSUBL12_LTRNSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);

  ///
  /// Enable LTR Snoop Latency Subtraction
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRSLSUBEN;
  Data32Or = (UINT32) B_PCIE_LTRSUBL12_LTRSLSUBEN;
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Scale Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRSLSSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL12_LTRSLSSUBV << B_PCIE_LTRSUBL12_LTRSLSSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);

  ///
  /// Program LTR Snoop Latency Subtraction Value
  ///
  Data32And = (UINT32) ~B_PCIE_LTRSUBL12_LTRSLSUBV_MASK;
  Data32Or = (UINT32) (V_PCIE_LTRSUBL12_LTRSLSUBV << B_PCIE_LTRSUBL12_LTRSLSUBV_OFFSET);
  PciSegmentAndThenOr32 (RpBase +  R_PCIE_LTRSUBL12, Data32And, Data32Or);
}

/**
  Configure 10-Bit Tag

  @param[in] RpBase     Root Port PCI base address
**/
VOID
CpuPcieConfigure10BitTag (
  IN  UINT64   RpBase
  )
{
  UINT32         Data32And;
  UINT32         Data32Or;
  //
  // Program 10-Bit Requester Supported (PX10BTRS) 0x64[17] = 0x0
  // Program 10-Bit Completer Supported (PX10BTCS) 0x64[16] = 0x1
  //
  Data32And = (UINT32) ~(B_PCIE_DCAP2_PX10BTRS | B_PCIE_DCAP2_PX10BTCS);
  Data32Or = (UINT32) (~B_PCIE_DCAP2_PX10BTRS | B_PCIE_DCAP2_PX10BTCS);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_DCAP2, Data32And, Data32Or);

  //
  // Program 10-Bit Tag Requester Enable (PX10BTRE) 0x68[11] = 0x0
  //
  Data32And = (UINT32) ~B_PCIE_DCTL2_PX10BTRE;
  PciSegmentAnd32 (RpBase + R_PCIE_DCTL2, Data32And);

  //
  // Program Fabric 10-bit Tag Support Enable (F10BTSE) 0x5BC[24] = 0x0
  //
  Data32And = (UINT32) ~B_PCIE_ADVMCTRL_F10BTSE;
  PciSegmentAnd32 (RpBase + R_PCIE_ADVMCTRL, Data32And);
}

/**
  Configure Retimer Support

  @param[in] RpBase     Root Port PCI base address
**/
VOID
CpuPcieConfigureRetimerSupport (
  IN  UINT64   RpBase
  )
{
  UINT32              Data32And;
  UINT32              Data32Or;

  //
  // Program Two Retimers Presence Detect Supported (TRPDS) 0x6C[24] = 0x1
  // Program Retimer Presence Detect Supported (RPDS) 0x6C[23] = 0x1
  // Program Lower SKP OS Generation Supported Speeds Vector (LSOSGSSV) 0x6C[15:9] = 0xF
  //
  Data32And = (UINT32) ~(B_PCIE_LCAP2_TRPDS | B_PCIE_LCAP2_RPDS | B_PCIE_LCAP2_LSOSGSSV_MASK);
  Data32Or = (UINT32) (B_PCIE_LCAP2_TRPDS | B_PCIE_LCAP2_RPDS | V_PCIE_LCAP2_LSOSGSSV);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_LCAP2, Data32And, Data32Or);
}

VOID
CpuFiaFinalizeConfigurationAndLock(
  )
 {
  //
  // Set PCR[FIA] + 0h bit [17, 16, 15] to [1, 1, 1]
  //
  CpuRegbarAndThenOr32 (
    CPU_SB_PID_PEG60FIA,
    R_PCH_FIA_PCR_CC,
    ~0u,
    B_PCH_FIA_PCR_CC_PTOCGE | B_PCH_FIA_PCR_CC_OSCDCGE | B_PCH_FIA_PCR_CC_SCPTCGE
    );
  DEBUG((DEBUG_INFO, "Offset 0x00[CC] = 0x%x\n", CpuRegbarRead32(CPU_SB_PID_PEG60FIA, R_PCH_FIA_PCR_CC)));

  //
  // Set PCR[FIA] + 20h bit [0, 1, 31] to [0, 0, 0]
  //
  CpuRegbarAndThenOr32 (
    CPU_SB_PID_PEG60FIA,
    R_PCH_FIA_PCR_PLLCTL,
    (UINT32) ~(B_PCH_FIA_PCR_PLLCTL_CL0PLLFO | B_PCH_FIA_PCR_PLLCTL_CL1PLLFO | B_PCH_FIA_PCR_PLLCTL_PLLACBGD),
    0
    );
  DEBUG((DEBUG_INFO, "Offset 0x20[PLLCTL] = 0x%x\n", CpuRegbarRead32(CPU_SB_PID_PEG60FIA, R_PCH_FIA_PCR_PLLCTL)));

  //
  // Set PCR[FIA] + 40h bit [3] to [1]
  //
  CpuRegbarAndThenOr32 (
    CPU_SB_PID_PEG60FIA,
    R_PCH_FIA_PCR_PMC,
    ~0u,
    B_PCH_FIA_PCR_PMC_PRDPGE
    );
  DEBUG((DEBUG_INFO, "Offset 0x40[PMC] = 0x%x\n", CpuRegbarRead32(CPU_SB_PID_PEG60FIA, R_PCH_FIA_PCR_PMC)));
  //
  // Set PCR[FIA] + 48h bit [0] to [0]
  //
  CpuRegbarAndThenOr32 (
    CPU_SB_PID_PEG60FIA,
    R_PCH_FIA_PCR_PGCUC,
    (UINT32) ~(B_PCH_FIA_PCR_PGCUC_ACC_CLKGATE_DISABLED),
    0
    );
  DEBUG((DEBUG_INFO, "Offset 0x48[PGCUC] = 0x%x\n", CpuRegbarRead32(CPU_SB_PID_PEG60FIA, R_PCH_FIA_PCR_PGCUC)));
}


/**
  Configure power management settings which are applicable to both enabled and disabled ports.
  These settings are relevant to all ports including disabled ports.
  Use sideband access since primary may not be available.

  @param[in]  RpIndex                         The root port to be initialized (zero based).
  @param[in]  PhyLanePgEnable                 Indicates whether PHY lane power gating is to be enabled,
                                              requires CLKREQ# to supported by the port or the port to be disabled.
  @param[in]  DisableRootPortClockGating      Indicates whether the PCI Express Clock Gating for each root port
                                              is enabled by platform modules.
  @param[in]  DisableRootPortPowerGating      Indicates whether the PCI Express Power Gating for each root port
                                              is enabled by platform modules.
**/
VOID
CpuPcieConfigurePortBasedPowerManagement (
  IN  UINT32   RpIndex,
  IN  BOOLEAN  PhyLanePgEnable,
  IN  BOOLEAN  DisableRootPortClockGating,
  IN  BOOLEAN  DisableRootPortPowerGating
  )
{
  UINT32                            Data32;
  UINT32                            Data32Or;
  UINT32                            Data32And;
  SA_PEG_HOB                        *SaPegHob;
  CONST CPU_PCIE_ROOT_PORT_CONFIG   *RpConfig;
  UINT64                            RpBase;

  SaPegHob = NULL;
  RpBase   = CpuPcieBase(RpIndex);
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  if (SaPegHob == NULL) {
    DEBUG ((DEBUG_INFO, "SaPegHob not found!\n"));
    ASSERT (SaPegHob != NULL);
    return;
  }

  RpConfig = &mCpuPcieRpConfig->RootPort[RpIndex];


  DEBUG ((DEBUG_INFO, "CpuPcieConfigurePortBasedPowerManagement(%d) Start\n", RpIndex + 1));

  ///
  /// Section 4.30 LTR
  ///
  CpuPcieConfigureLTRSubtraction (RpIndex);

  if (RpConfig->PcieRpCommonConfig.Aspm != FALSE) {
    ///
    /// Section 4.4.2 ASPM
    ///
    CpuPcieConfigureASPM (RpIndex);
  }

  if (!DisableRootPortClockGating) {
    DEBUG ((DEBUG_VERBOSE, "Root port Clock gating is enabled!\n"));
    ///
    /// Program (R_PCH_PCIE_CFG_PCIEPMECTL3) 434h
    /// Set 434h[4] to 1b to enable L1 Auto power gating only if L1SS is disabled
    /// Set 434h[3:2] to 01b to program OSC Clock gate hysteresis to 1us.
    /// Set 434h[1:0] t0 01b to Program Power Gating Exit Hysteresis to 5us.
    ///
    Data32And = (UINT32) ~(B_PCIE_PCIEPMECTL3_PMREQCPGEXH_MASK | B_PCIE_PCIEPMECTL3_OSCCGH_MASK | B_PCIE_PCIEPMECTL3_L1PGAUTOPGEN);
    Data32Or = (UINT32) ((V_PCIE_PCIEPMECTL3_OSCCGH_1US << B_PCIE_PCIEPMECTL3_OSCCGH_OFFSET) | (V_PCIE_PCIEPMECTL3_PMREQCPGEXH << B_PCIE_PCIEPMECTL3_PMREQCPGEXH_OFFSET));
    if ((SaPegHob->CpuPcieRp.L1SubStates[RpIndex] == 0) || (RpConfig->PcieRpCommonConfig.L1Substates == CpuPcieL1SubstatesDisabled)) {
      Data32Or |= (UINT32) (B_PCIE_PCIEPMECTL3_L1PGAUTOPGEN);
    }
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEPMECTL3, Data32And, Data32Or);
    ///
    /// Program (R_PCIE_RPDCGEN) E1h
    /// Set E1h[1] to 1b to enable dynamic link clock gating.
    /// Set E1h[0] to 1b to enable dynamic bbackbone clock gating.
    ///
    Data32Or = (UINT32) ((B_PCIE_RPDCGEN_RPDLCGEN | B_PCIE_RPDCGEN_RPDBCGEN) << 8); ///< For 32-bit boundary alignment for 0xE1 (RPDCGEN), shift by 8bits from 0xE0 to reach 0xE1
    PciSegmentAndThenOr32 (RpBase + R_PCIE_SPR, ~0u, Data32Or);
    ///
    /// Program (R_PCIE_IOSFSBCS) F7h
    /// Set F7h[6] to 1b to enable side clock partition/ trunk clock gating.
    ///
    Data32Or = (UINT32) (B_PCIE_IOSFSBCS_SCPTCGE << 24); ///< For 32-bit boundary alignment for 0xF7 ( IOSFSBCS), shift by 24bits from 0xF4 to reach 0xF7
    PciSegmentAndThenOr32 (RpBase + R_PCIE_F4, ~0u, Data32Or);
  }
  DEBUG_CODE_BEGIN ();
  ///
  /// Ensure PHYCLPGE is set before DLSULPPGE and FDPPGE.
  /// PHYCLPGE is programmed in CpuPcieConfigureControllerBasedPowerManagement()
  ///
  CpuPcieRpSbiRead32 (GetCpuPcieFirstPortIndex (RpIndex), R_PCIE_PCIEPMECTL2, &Data32);
  DEBUG_CODE_END ();

  if (!DisableRootPortPowerGating) {
    DEBUG ((DEBUG_VERBOSE, "Root port Power gating is enabled!\n"));

    ///
    /// Program (R_PCIE_TNPT) 418h
    /// Set 418h[31:24] Throttle Period (TP) to 0x2
    /// Set 418h[23:16] Throttle Time (TT) to 0x0
    /// Set 418h[1] Dynamic RX Link Throttling Enable (DRXLTE) to 0b
    /// Set 418h[0] Dynamic TX Link Throttling Enable (DTXLTE) to 0b
    ///
    Data32And = (UINT32) ~(B_PCIE_TNPT_TP_MASK | B_PCIE_TNPT_TT_MASK | B_PCIE_TNPT_DRXLTE | B_PCIE_TNPT_DTXLTE);
    Data32Or = (UINT32)(V_PCIE_TNPT_TP << B_PCIE_TNPT_TP_OFFSET);
    CpuPcieRpSbiAndThenOr32 (RpIndex, R_PCIE_TNPT, Data32And, Data32Or);

    ///
    /// Set 420h[31] = 1b to enable function disable PHY power gating.
    /// If CLKREQ# is supported or port is disabled set 420h[30,29] to 11b.
    /// 420h[29] (DLSULDLSD) and 420h[0] must be set if DLSULPPGE is set or PTOCGE is set.
    /// Assume that if PTOCGE is set CLKREQ is supported on this port.
    /// L1.LOW is disabled; if all conditions are met, it will be enabled later.
    ///
    Data32Or  = B_PCIE_PCIEPMECTL_FDPPGE;
    if (PhyLanePgEnable) {
      DEBUG ((DEBUG_INFO, "Setting DLSULPPGE+DLSULDLSD.\n"));
      Data32And = (UINT32) ~(B_PCIE_PCIEPMECTL_L1FSOE);
      Data32Or |= B_PCIE_PCIEPMECTL_DLSULPPGE | B_PCIE_PCIEPMECTL_DLSULDLSD;
    }
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEPMECTL, Data32And, Data32Or);

    ///
    /// Program (R_PCIE_PCIEPMECTL2) 424h
    /// Set 424h[8] to 1b to enable dynamic controller power gating in detect state when port is function disabled.
    /// Set 424h[7] to 1b to enable dynamic controller power gating in detect state when CLKREQ# is de-asserted.
    /// Set 424h[6] to 1b to enable dynamic controller power gating in L23_Rdy state.
    /// Set 424h[5] to 1b to enable dynamic controller power gating in disabled state.
    /// Set 424h[4] to 1b to enable dynamic controller power gating in L1 sub states.
    /// Set 424h[27] to 0b to enable Chassis PMC save and restore enable.
    ///
    Data32Or = B_PCIE_PCIEPMECTL2_FDCPGE | B_PCIE_PCIEPMECTL2_DETSCPGE | B_PCIE_PCIEPMECTL2_L23RDYSCPGE
               | B_PCIE_PCIEPMECTL2_DISSCPGE | B_PCIE_PCIEPMECTL2_L1SCPGE;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEPMECTL2, ~0u, Data32Or);
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEPMECTL2, (UINT32)(~B_PCIE_PCIEPMECTL2_CPMCSRE), 0u);

    ///
    /// Program (R_PCIE_PCE) 428h
    /// Set 428h[0] to for PMC Request Enable.
    /// Set 428h[3] to 1b for Sleep Enable.
    /// Set 428h[5] to 0b. Hardware Autonomous Enable (HAE).
    ///
    Data32And = (UINT32) ~(B_PCIE_PCE_HAE);
    Data32Or = B_PCIE_PCE_PMCRE | B_PCIE_PCE_SE;
    PciSegmentAndThenOr32(RpBase + R_PCIE_PCE, Data32And, Data32Or);
  }
  ///
  /// Section 3.1.8  L1 Substate
  ///

  ///
  ///L1PM Substates Supported (L1SSES) 0x204  5 1
  /// L1PM Substates Supported (L1PSS) 0x204  4 0
  /// ASPM L1.1 Supported (AL11S) 0x204  3 0
  /// ASPM L1.2 Supported (AL12S) 0x204  2 0
  /// PCI-PM L1.1 Supported (PPL11S) 0x204  1 0
  /// PCI-PM L1.2 Supported (PPL12S) 0x204  0 0
  ///
  /// NOTE!!!!!!!!!!!!
  /// Port Tpower_on Value (PTV) using from PCH
  /// Need to be characterized during post silicon
  /// Port Tpower_on Scale (PTPOS) 0x204  17:16 0x2
  /// Port Tpower_on Value (PTV) 0x204  23:19 0x4
  /// Port Common Mode Restore Time (PCMRT) 0x204  15:8 0x6E
  ///

  Data32And = (UINT32)~(B_PCIE_L1SCAP_PTV_MASK | B_PCIE_L1SCAP_PTPOS_MASK | B_PCIE_L1SCAP_PCMRT_MASK);
  Data32Or = (UINT32)(B_PCIE_L1SCAP_L1SSES | (V_PCIE_L1SCAP_PTV << B_PCIE_L1SCAP_PTV_OFFSET) | (V_PCIE_L1SCAP_PTPOS << B_PCIE_L1SCAP_PTPOS_OFFSET) | (V_PCIE_L1SCAP_PCMRT << B_PCIE_L1SCAP_PCMRT_OFFSET));

  ///
  /// Program L1SS Capability based on setup option
  ///
  if ((RpConfig->PcieRpCommonConfig.L1Substates == CpuPcieL1SubstatesDisabled) || (SaPegHob->CpuPcieRp.L1SubStates[RpIndex] == 0)) {
    Data32And &= (UINT32)~(0x1F);
  }
  else if (RpConfig->PcieRpCommonConfig.L1Substates == CpuPcieL1SubstatesL1_1) {
    Data32And &= (UINT32)~(B_PCIE_L1SCAP_PPL12S | B_PCIE_L1SCAP_AL12S);
    Data32Or |= (UINT32)(B_PCIE_L1SCAP_PPL11S | B_PCIE_L1SCAP_AL11S | B_PCIE_L1SCAP_L1PSS);
  }
  else {
    Data32Or |= (UINT32)(B_PCIE_L1SCAP_PPL12S | B_PCIE_L1SCAP_PPL11S | B_PCIE_L1SCAP_AL12S | B_PCIE_L1SCAP_AL11S | B_PCIE_L1SCAP_L1PSS);
  }

  PciSegmentAndThenOr32 (RpBase + R_PCIE_L1SCAP, Data32And, Data32Or);

  ///
  /// CLKREQ# Acceleration Interrupt Enable (L1SSEIE) 0x208  4 1
  /// L1.2 LTR Threshold Latency Value (L12LTRTLV) 0x208[25:16] 0xFA
  /// Common Mode Restore Time (CMRT) 0x208[15:8] 0x6E
  ///
  Data32And = (UINT32)~(B_PCIE_L1SCTL1_L1SSEIE | B_PCIE_L1SCAP_L12LTRTLV_MASK | B_PCIE_L1SCAP_CMRT_MASK);
  Data32Or = (UINT32)(B_PCIE_L1SCTL1_L1SSEIE | (V_PCIE_L1SCAP_L12LTRTLV << B_PCIE_L1SCAP_L12LTRTLV_OFFSET) | (V_PCIE_L1SCAP_L12LTRTLSV << B_PCIE_L1SCAP_L12LTRTLSV_OFFSET) | (V_PCIE_L1SCAP_CMRT << B_PCIE_L1SCAP_CMRT_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L1SCTL1, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L1SCTL2_POWT_MASK | B_PCIE_L1SCTL2_TPOS_MASK);
  Data32Or = (UINT32)((V_PCIE_L1SCTL2_TPOS << B_PCIE_L1SCTL2_TPOS_OFFSET) | (V_PCIE_L1SCTL2_POWT << B_PCIE_L1SCTL2_POWT_OFFSET));
  PciSegmentAndThenOr32(RpBase + R_PCIE_L1SCTL2, Data32And, Data32Or);

  /// L1 Substate Exit SCI Enable (L1SSESE) 0xD4  30 1
  PciSegmentAndThenOr32 (RpBase + R_PCIE_MPC2, ~0u, B_PCIE_MPC2_L1SSESE);

  ///
  /// @todo: Squelch and CLKREQ# programming pending. To be reviewed after MVE validation.
  ///
}

/**
  Set Gen3 coefficient list entry.

  @param[in] RpBase      Root Port pci segment base address
  @param[in] ListEntry   ListEntry (0-9)
  @param[in] Cm          C-1
  @param[in] Cp          C+1
**/
VOID
CpuPcieSetGen3Presets (
  UINT64 RpBase,
  UINT32 ListEntry,
  UINT32 Cm,
  UINT32 Cp
  )
{
  UINT32  PreReg;
  UINT32  PostReg;
  UINT32  PreField;
  UINT32  PostField;
  UINT32  Data32And;
  UINT32  Data32Or;

  DEBUG ((DEBUG_VERBOSE, "CpuPcieSetGen3Presets Start!\n"));

  ASSERT (ListEntry < 10);
  ASSERT ((Cm & ~0x3F) == 0);
  ASSERT ((Cp & ~0x3F) == 0);
  ///
  /// CPU PCIe has 5 pairs of coefficients Cm (Co-efficient minus) and Cp (Co-efficient Plus) which is stored in RTPCL registers.
  /// Each of this is stored in 5 bitfields in RTPCL and is covered in 2 registers.
  ///
  PreReg    = ((ListEntry * 2)) / 5;
  PreField  = ((ListEntry * 2)) % 5;
  PostReg   = ((ListEntry * 2) + 1) / 5;
  PostField = ((ListEntry * 2) + 1) % 5;

  ASSERT (PreReg  < 2);
  ASSERT (PostReg < 2);

  Data32And = (UINT32) ~(0x3F << (6 * PreField));
  Data32Or  = (Cm << (6 * PreField));
  ASSERT ((Data32And & Data32Or) == 0);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_RTPCL1 + (PreReg  * 4), Data32And, Data32Or);

  Data32And = (UINT32) ~(0x3F << (6 * PostField));
  Data32Or  = (Cp << (6 * PostField));
  ASSERT ((Data32And & Data32Or) == 0);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_RTPCL1 + (PostReg * 4), Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "Port %d list %d: (%d,%d)\n",
          PciePortNum (RpBase), ListEntry, Cm, Cp));
  DEBUG ((DEBUG_VERBOSE, "CpuPcieSetGen3Presets End!\n"));
}

/**
  Set Gen4 Preset entry.

  @param[in] RpBase      Root Port pci segment base address
  @param[in] ListEntry   ListEntry (0-9)
  @param[in] Cm          C-1
  @param[in] Cp          C+1
**/
VOID
CpuPcieSetGen4Presets (
  UINT64 RpBase,
  UINT32 ListEntry,
  UINT32 Cm,
  UINT32 Cp
  )
{
  UINT32  PreReg;
  UINT32  PostReg;
  UINT32  PreField;
  UINT32  PostField;
  UINT32  Data32And;
  UINT32  Data32Or;

  DEBUG ((DEBUG_VERBOSE, "CpuPcieSetGen4Presets Start!\n"));

  ASSERT (ListEntry < 10);
  ASSERT ((Cm & ~0x3F) == 0);
  ASSERT ((Cp & ~0x3F) == 0);
  ///
  /// CPU PCIe has 5 pairs of coefficients Cm (Co-efficient minus) and Cp (Co-efficient Plus) which is stored in RTPCL registers.
  /// Each of this is stored in 5 bitfields in RTPCL and is covered in 2 registers.
  ///
  PreReg    = ((ListEntry * 2)) / 5;
  PreField  = ((ListEntry * 2)) % 5;
  PostReg   = ((ListEntry * 2) + 1) / 5;
  PostField = ((ListEntry * 2) + 1) % 5;

  ASSERT (PreReg  < 2);
  ASSERT (PostReg < 2);

  Data32And = (UINT32) ~(0x3F << (6 * PreField));
  Data32Or  = (Cm << (6 * PreField));
  ASSERT ((Data32And & Data32Or) == 0);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PX16GRTPCL1 + (PreReg  * 4), Data32And, Data32Or);

  Data32And = (UINT32) ~(0x3F << (6 * PostField));
  Data32Or  = (Cp << (6 * PostField));
  ASSERT ((Data32And & Data32Or) == 0);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PX16GRTPCL1 + (PostReg * 4), Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "Port %d list %d: (%d,%d)\n",
          PciePortNum (RpBase), ListEntry, Cm, Cp));

  DEBUG ((DEBUG_VERBOSE, "CpuPcieSetGen4Presets End!\n"));
}


/**
  Reset and enable Recovery Entry and Idle Framing Error Count

  @param[in] RpBase    Root Port base address
**/
STATIC
VOID
CpuPcieResetErrorCounts (
  UINT64 RpBase
  )
{
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32) ~B_PCIE_EQCFG1_REIFECE);
  PciSegmentOr32 (RpBase + R_PCIE_EQCFG1, B_PCIE_EQCFG1_REIFECE);
}

VOID
CpuPcieGen3PresetToCoeff (
  UINT64 RpBase
  )
{
  //
  // Before training to GEN3/GEN4 Configure Lane0 P0-P10 Preset Coefficient mapping based on recommendation for CPU PCIE
  //
  DEBUG ((DEBUG_VERBOSE, "CpuPcieGen3PresetToCoeff!\n"));
  PciSegmentWrite32 (RpBase + R_PCIE_L0P0P1PCM, 0x00D1002F);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P1P2P3PCM, 0x37340C8B);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P3P4PCM, 0x0003F200);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P5P6PCM, 0x08DC01B9);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P6P7P8PCM, 0x2F346B00);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P8P9PCM, 0x002F4208);
  PciSegmentWrite32 (RpBase + R_PCIE_L0P10PCM, 0x0001502A);
  PciSegmentWrite32 (RpBase + R_PCIE_L0LFFS, 0x00003F15);
}

VOID
CpuPcieGen4PresetToCoeff (
  UINT64 RpBase
  )
{
  //
  // Before training to GEN3/GEN4 Configure Lane0 P0-P10 Preset Coefficient mapping based on recommendation for CPU PCIE
  //
  DEBUG ((DEBUG_VERBOSE, "CpuPcieGen4PresetToCoeff!\n"));
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP0P1PCM, 0x00D1002F);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP1P2P3PCM, 0x37340C8B);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP3P4PCM, 0x0003F200);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP5P6PCM, 0x08DC01B9);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP6P7P8PCM, 0x2F346B00);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP8P9PCM, 0x002F4208);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GP10PCM, 0x0001502A);
  PciSegmentWrite32 (RpBase + R_PCIE_PX16GLFFS, 0x00003F15);
}

/**
  Populate HW EQ coefficient search list.
  @param[in] RpBase    Root Port base address
  @param[in] Params    Equalization parameters
**/
VOID
CpuPcieInitializePresets (
  UINT64                 RpBase,
  CONST CPU_PCIE_CONFIG  *CpuPcieRpConfig,
  UINT8                  CpuPcieSpeed
  )
{
  UINT32     Index;
  UINT32     Register;

  DEBUG ((DEBUG_INFO, "CpuPcieInitializePresets Start!\n"));
  if (CpuPcieSpeed == CpuPcieGen3) {
    Register = R_PCIE_RTPCL1;
  } else if (CpuPcieSpeed == CpuPcieGen4) {
    Register = R_PCIE_PX16GRTPCL1;
  }
  for (Index = 0; Index < PCIE_HWEQ_COEFFS_MAX; ++Index) {
    if (CpuPcieSpeed == CpuPcieGen3) {
      CpuPcieSetGen3Presets (
        RpBase,
        Index,
        CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[Index].Cm,
        CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[Index].Cp
        );
    } else if (CpuPcieSpeed == CpuPcieGen4){
      CpuPcieSetGen4Presets (
        RpBase,
        Index,
        CpuPcieRpConfig->HwEqGen4CoeffList[Index].Cm,
        CpuPcieRpConfig->HwEqGen4CoeffList[Index].Cp
        );
    }
  }
  for (Index = 0; Index < 4; ++Index) {
    DEBUG ((DEBUG_INFO, "RTPCL%d = 0x%08x\n", Index, PciSegmentRead32 (RpBase + Register + (Index * 4))));
  }
  DEBUG ((DEBUG_INFO, "CpuPcieInitializePresets End!\n"));
}


/**
  Dump HW EQ Registers.
  @param[in] RpBase       Equaliztion context structure
**/
VOID
CpuPcieDumpHwEqRegs (
  UINT64 RpBase,
  UINT8  CpuPcieSpeed
  )
{
  if (CpuPcieSpeed == CpuPcieGen3) {
    DEBUG ((DEBUG_VERBOSE, "EQCFG1: 0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_EQCFG1)));
    DEBUG ((DEBUG_VERBOSE, "EQCFG2: 0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_EQCFG2)));
  } else {
    DEBUG ((DEBUG_VERBOSE, "EQCFG4: 0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_EQCFG4)));
    DEBUG ((DEBUG_VERBOSE, "EQCFG5: 0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_EQCFG5)));
  }
  DEBUG ((DEBUG_VERBOSE, "HAEQ:   0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_HAEQ)));
  DEBUG ((DEBUG_VERBOSE, "L01EC:  0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_L01EC)));
  DEBUG ((DEBUG_VERBOSE, "L23EC:  0x%08x\n", PciSegmentRead32(RpBase + R_PCIE_L23EC)));
}

/**
  Configures rootport for hardware Gen3 link equalization.
  @param[in] RpIndex              Root Port Index for which HW EQ is to be performed
  @param[in] RpBase               Root Port Base
  @param[in] Params               Equalization parameters
**/
VOID
CpuPcieDoGen3HardwareEq (
  UINT32                      RpIndex,
  UINT64                      RpBase,
  CONST CPU_PCIE_CONFIG       *Params
  )
{
  UINT32                            Data32Or;
  UINT32                            Data32And;
  UINT32                            Gen3Uptp;
  UINT32                            Gen3Dptp;
  UINT8                             CpuPcieSpeed;
  UINT8                             TimeOut;
  UINT8                             PresetCoeffList;
  UINT8                             Px8gtswlpce;

  CpuPcieSpeed = CpuPcieGen3;

  DEBUG ((DEBUG_INFO, "CpuPcieDoGen3HardwareEq Start!\n"));
  mDoGen3HwEqRpMask |= BIT0 << RpIndex;
  DEBUG ((DEBUG_INFO, "LSTS2: 0x%04x\n", PciSegmentRead16 (RpBase + R_PCIE_LSTS2)));

  //
  // Programming done as per section 5.3.1.2 Linear Mode Hardware Flow ( Gen3 )
  // SIP16 Converge PCIe BWG r0.92
  //

  //
  // Step1: Program all the preset-coeff mapping registers - done in CpuPcieTxPresetOverride() fn
  //
  if (RpIndex < 3){ // Preset Overrides are per controller registers, so skip it for the last port
    CpuPcieGen3PresetToCoeff (RpBase);
  }
  //
  // Step2:
  // If endpoint supports only GEN3
  // Program LCTL2.TLS to 8.0 GT/s
  //
  //PciSegmentAndThenOr16 (RpBase + R_PCIE_LCTL2, (UINT16)~B_PCIE_LCTL2_TLS, V_PCIE_LCAP_MLS_GEN3);
  //
  // Step3:Program RTPCL1.PCM = 0 to enable Preset mode
  //
  PciSegmentAnd32 (RpBase + R_PCIE_RTPCL1, ~B_PCIE_RTPCL1_PCM);
  //
  // Step4:Program the Presets
  // Note : Requires silicon characterization
  //
  CpuPcieInitializePresets (RpBase, Params, CpuPcieSpeed);
  //
  // Step5:Program EQCFG1.LEB to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~(B_PCIE_EQCFG1_LEB));
  //
  // Step6:Program EQCFG1.LEP23B to 0 so that Phase 2 and Phase 3 EQ is not bypass
  //
  if (Params->RootPort[RpIndex].Gen3EqPh23Enable == 0) {
    PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1,  (UINT32)~(B_PCIE_EQCFG1_LEP23B));
  } else {
    PciSegmentOr32 (RpBase + R_PCIE_EQCFG1,  (UINT32)(B_PCIE_EQCFG1_LEP23B));
  }
  //
  // Step7:Program EQCFG1.LEP3B to 0 so that Phase 3 EQ is not bypass
  //
  if (Params->RootPort[RpIndex].Gen3EqPh3Enable == 0) {
    PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1,  (UINT32)~(B_PCIE_EQCFG1_LEP3B));
  } else {
    PciSegmentOr32 (RpBase + R_PCIE_EQCFG1,  (UINT32)(B_PCIE_EQCFG1_LEP3B));
  }
  //
  // Step8:Program EQCFG1 RTLEPCEB to 0 to enable HWEQ
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_RTLEPCEB);
  //
  // Step9:Program EQCFG1.RTPCOE to 0 enable Hardware Search Algorithm
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_RTPCOE);
  //
  // Step10:Clear EQCFG1.HPCMQE to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_HPCMQE);
  //
  // Step11:Rx wait time for each new eq should be configured to 1us
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_RWTNEVE_MASK, (UINT32)V_PCIE_EQCFG1_RWTNEVE_1US << B_PCIE_EQCFG1_RWTNEVE_OFFSET);
  //
  // Step12: For Linear Mode, BIOS needs to program the EQCFG1.MFLNTL to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_MFLNTL);
  //
  // Step13: Program EQCFG4.PX8GTSWLPCE to 3 as per post silicon charecterization
  //
  switch (Params->RootPort[RpIndex].Px8gtswlpce) {
    case CpuPciePx8gtswlpce1us:
      Px8gtswlpce = 0;
      break;
    case CpuPciePx8gtswlpce2us:
      Px8gtswlpce = 1;
      break;
    case CpuPciePx8gtswlpce3us:
      Px8gtswlpce = 2;
      break;
    case CpuPciePx8gtswlpce4us:
      Px8gtswlpce = 3;
      break;
    case CpuPciePx8gtswlpce10us:
      Px8gtswlpce = 4;
      break;
    case CpuPciePx8gtswlpce12us:
      Px8gtswlpce = 5;
      break;
    case CpuPciePx8gtswlpce14us:
      Px8gtswlpce = 6;
      break;
    case CpuPciePx8gtswlpce16us:
      Px8gtswlpce = 7;
      break;
    default:
      Px8gtswlpce = 3;
      break;
  }
  DEBUG((DEBUG_INFO, "Presets/Coefficients Evaluation for Gen3 = %d\n", Px8gtswlpce));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX8GTSWLPCE_MASK , ((UINT32)Px8gtswlpce<< B_PCIE_EQCFG4_PX8GTSWLPCE_OFFSET));
  //
  // Step14: Program EQCFG1.TUPP to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_TUPP);
  //
  // Step15: Program EQCFG1.RUPP to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~B_PCIE_EQCFG1_RUPP);
  //
  // Step16: BIOS would program the Receiver Eye Margin Error Threshold and Multiplier to 4 errors; in
  // which the EQCFG2.REWMETM would be set to 00b and EQCFG2.REWMET would be set
  //  to 10h
  //
  Data32And = (UINT32)~(B_PCIE_EQCFG2_REWMETM |
                         B_PCIE_EQCFG2_REWMET);
  Data32Or = (0 << B_PCIE_EQCFG2_REWMETM_OFFSET) | 0x02; // REWMET = 2 (4 errors)
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG2, Data32And, Data32Or);
  //
  // Step17,18: Program EQCFG2.NTIC,EQCFG2.EMD  to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG2, (UINT32)~(B_PCIE_EQCFG2_NTIC | B_PCIE_EQCFG2_EMD));
  //
  // Step19: Program EQCFG2.PECT as below
  //

  switch (Params->RootPort[RpIndex].PcetTimer) {
    case CpuPciePcet2ms:
      TimeOut = 2;
      break;
    case CpuPciePcet3ms:
      TimeOut = 3;
      break;
    case CpuPciePcet4ms:
      TimeOut = 4;
      break;
    case CpuPciePcet5ms:
      TimeOut = 5;
      break;
    case CpuPciePcet6ms:
      TimeOut = 6;
      break;
    case CpuPciePcet7ms:
      TimeOut = 7;
      break;
    case CpuPciePcet8ms:
      TimeOut = 8;
      break;
    case CpuPciePcet9ms:
      TimeOut = 9;
      break;
    case CpuPciePcet10ms:
      TimeOut = 10;
      break;
    case CpuPciePcet11ms:
      TimeOut = 11;
      break;
    case CpuPciePcet21ms:
      TimeOut = 21;
      break;
    case CpuPciePcet22ms:
      TimeOut = 22;
      break;
    case CpuPciePcet23ms:
      TimeOut = 23;
      break;
    default:
      TimeOut = 0;
      break;
  }
  DEBUG ((DEBUG_INFO, "PCET timeout = %d ms\n", TimeOut));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG2, (UINT32)~(B_PCIE_EQCFG2_PCET), (TimeOut << B_PCIE_EQCFG2_PCET_OFFSET));
  //
  // Step20: Program EQCFG2.HAPCSB as below and clear HAPCCPIE
  //
  switch (Params->RootPort[RpIndex].Gen3PresetCoeffList) {
    case CpuPciePresetCoeffList0:
      PresetCoeffList = 0;
      break;
    case CpuPciePresetCoeffList1:
      PresetCoeffList = 1;
      break;
    case CpuPciePresetCoeffList2:
      PresetCoeffList = 2;
      break;
    case CpuPciePresetCoeffList3:
      PresetCoeffList = 3;
      break;
    case CpuPciePresetCoeffList4:
      PresetCoeffList = 4;
      break;
    case CpuPciePresetCoeffList5:
      PresetCoeffList = 5;
      break;
    case CpuPciePresetCoeffList6:
      PresetCoeffList = 6;
      break;
    case CpuPciePresetCoeffList7:
      PresetCoeffList = 7;
      break;
    case CpuPciePresetCoeffList8:
      PresetCoeffList = 8;
      break;
    case CpuPciePresetCoeffList9:
      PresetCoeffList = 9;
      break;
    case CpuPciePresetCoeffList10:
      PresetCoeffList = 0xA;
      break;
    default:
      PresetCoeffList = 0;
      break;
  }
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG2, (UINT32)~B_PCIE_EQCFG2_HAPCSB, PresetCoeffList << B_PCIE_EQCFG2_HAPCSB_OFFSET);
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~(B_PCIE_EQCFG1_HAPCCPIE));
  //
  // Step21,22: Program EQCFG2.NTEME and EQCFG2.MPEME to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG2, (UINT32)~(B_PCIE_EQCFG2_NTEME | B_PCIE_EQCFG2_MPEME));
  //
  // Step23,24: Program EQCFG1.MEQSMMFLNTL and EQCFG1.MFLNTL to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG1, (UINT32)~(B_PCIE_EQCFG1_MEQSMMFLNTL | B_PCIE_EQCFG1_MFLNTL));
  //
  // Step25: Program EQCFG1.REIC - value TBD in BWG - @TODO follow up with Arch to get the value and program it here
  //

  //
  // Step26: Program the HAEQ.HAPCCPI 0 to allow 1 iteration of Recovery.Equalization entry
  //
  PciSegmentAndThenOr32(RpBase + R_PCIE_HAEQ, (UINT32)~B_PCIE_HAEQ_HAPCCPI, 0 << B_PCIE_HAEQ_HAPCCPI_OFFSET);
  //
  // Step27-31: Program HAEQ.FOMEM to 0 | HAEQ.MACFOMC to 0 | HAEQ.SL to 0 | HAEQ.DL to 0xE | HAEQ.SFOMFM to 0
  //
  Data32And = (UINT32)~(B_PCIE_HAEQ_FOMEM |
                        B_PCIE_HAEQ_MACFOMC |
                        B_PCIE_HAEQ_SL |
                        B_PCIE_HAEQ_DL |
                        B_PCIE_HAEQ_SFOMFM);

  Data32Or = (0xE << B_PCIE_HAEQ_DL_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_HAEQ, Data32And, Data32Or);

  //
  // Step32: Program the following register for the Downstream Port Transmitter Preset value to P7
  //
  ///
  /// Configure Transmitter Preset for each Upstream and Downstream Port Lane:
  /// 1.  Set L01EC.DPL0TP, Dxx:Fn + 22Ch[3:0]    = 7
  /// 2.  Set L01EC.UPL0TP, Dxx:Fn + 22Ch[11:8]   = 7
  /// 3.  Set L01EC.DPL1TP, Dxx:Fn + 22Ch[19:16]  = 7
  /// 4.  Set L01EC.UPL1TP, Dxx:Fn + 22Ch[27:24]  = 7
  /// 5.  Set L23EC.DPL2TP, Dxx:Fn + 230h[3:0]    = 7
  /// 6.  Set L23EC.UPL2TP, Dxx:Fn + 230h[11:8]   = 7
  /// 7.  Set L23EC.DPL3TP, Dxx:Fn + 230h[19:16]  = 7
  /// 8.  Set L23EC.UPL3TP, Dxx:Fn + 230h[27:24]  = 7
  ///    Upto L23EC.UPL3TP, Dxx:Fn + 258h[27:24]  = 7
  ///
  Gen3Uptp = Params->RootPort[RpIndex].Gen3Uptp;
  Gen3Dptp = Params->RootPort[RpIndex].Gen3Dptp;
  Data32And = (UINT32) ~(B_PCIE_L01EC_UPL1TP_MASK | B_PCIE_L01EC_DPL1TP_MASK | B_PCIE_L01EC_UPL0TP_MASK | B_PCIE_L01EC_DPL0TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L01EC_UPL1TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L01EC_DPL1TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L01EC_UPL0TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L01EC_DPL0TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L01EC, Data32And, Data32Or);

  Data32And = (UINT32) ~(B_PCIE_L23EC_UPL3TP_MASK | B_PCIE_L23EC_DPL3TP_MASK | B_PCIE_L23EC_UPL2TP_MASK | B_PCIE_L23EC_DPL2TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L23EC_UPL3TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L23EC_DPL3TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L23EC_UPL2TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L23EC_DPL2TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L23EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L45EC_UPL5TP_MASK | B_PCIE_L45EC_DPL5TP_MASK | B_PCIE_L45EC_UPL4TP_MASK | B_PCIE_L45EC_DPL4TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L45EC_UPL5TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L45EC_DPL5TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L45EC_UPL4TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L45EC_DPL4TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L45EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L67EC_UPL7TP_MASK | B_PCIE_L67EC_DPL7TP_MASK | B_PCIE_L67EC_UPL6TP_MASK | B_PCIE_L67EC_DPL6TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L67EC_UPL7TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L67EC_DPL7TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L67EC_UPL6TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L67EC_DPL6TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L67EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L89EC_UPL9TP_MASK | B_PCIE_L89EC_DPL9TP_MASK | B_PCIE_L89EC_UPL8TP_MASK | B_PCIE_L89EC_DPL8TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L89EC_UPL9TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L89EC_DPL9TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L89EC_UPL8TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L89EC_DPL8TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L89EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L1011EC_UPL11TP_MASK | B_PCIE_L1011EC_DPL11TP_MASK | B_PCIE_L1011EC_UPL10TP_MASK | B_PCIE_L1011EC_DPL10TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L1011EC_UPL11TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1011EC_DPL11TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L1011EC_UPL10TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1011EC_DPL10TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L1011EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L1213EC_UPL13TP_MASK | B_PCIE_L1213EC_DPL13TP_MASK | B_PCIE_L1213EC_UPL12TP_MASK | B_PCIE_L1213EC_DPL12TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L1213EC_UPL13TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1213EC_DPL13TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L1213EC_UPL12TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1213EC_DPL12TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L1213EC, Data32And, Data32Or);

  Data32And = (UINT32)~(B_PCIE_L1415EC_UPL15TP_MASK | B_PCIE_L1415EC_DPL15TP_MASK | B_PCIE_L1415EC_UPL14TP_MASK | B_PCIE_L1415EC_DPL14TP_MASK);
  Data32Or = ((Gen3Uptp << B_PCIE_L1415EC_UPL15TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1415EC_DPL15TP_OFFSET) |
              (Gen3Uptp << B_PCIE_L1415EC_UPL14TP_OFFSET) |
              (Gen3Dptp << B_PCIE_L1415EC_DPL14TP_OFFSET));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_L1415EC, Data32And, Data32Or);
  //
  // Step33-34: Program Perform EQ LCTL3.PE to 1 and LCTL.RL = 1 = these steps will be done by the caller if endpoint supports only upto Gen3, otherwise SaDoGen4HardwareEq will be called
  //

  DEBUG ((DEBUG_INFO, "CpuPcieDoGen3HardwareEq End!\n"));
}

/**
  Configures rootport for hardware Gen4 link equalization.
  @param[in] RpIndex              Root Port Index for which HW EQ is to be performed
  @param[in] RpBase               Root Port Base
  @param[in] Params               Equalization parameters
**/
VOID
CpuPcieDoGen4HardwareEq (
  UINT32                      RpIndex,
  UINT64                      RpBase,
  CONST CPU_PCIE_CONFIG       *Params
  )
{
  UINT32                            Data32Or;
  UINT32                            Data32And;
  UINT32                            Gen4Uptp;
  UINT32                            Gen4Dptp;
  UINT8                             CpuPcieSpeed;
  UINT8                             Px16gtswlpce;

  CpuPcieSpeed = CpuPcieGen4;

  DEBUG ((DEBUG_INFO, "CpuPcieDoGen4HardwareEq Start!\n"));
  mDoGen4HwEqRpMask |= BIT0 << RpIndex;
  DEBUG ((DEBUG_INFO, "LSTS2: 0x%04x\n", PciSegmentRead16 (RpBase + R_PCIE_LSTS2)));

  //
  // Programming done as per section 5.3.1.2 Linear Mode Hardware Flow ( Gen3 )
  // SIP16 Converge PCIe BWG r0.92
  //

  //
  // Step1: Program all the preset-coeff mapping registers - done in CpuPcieTxPresetOverride() fn
  //
  if (RpIndex < 3){ // Preset Overrides are per controller registers, so skip it for the last port
    CpuPcieGen4PresetToCoeff (RpBase);
  }
  //
  // Step2:
  // Program LCTL2.TLS to 16.0 GT/s
  //
  PciSegmentAndThenOr16 (RpBase + R_PCIE_LCTL2, (UINT16)~B_PCIE_LCTL2_TLS, V_PCIE_LCAP_MLS_GEN4);
  //
  // Step3:Program RTPCL4.PCM = 0 to enable Preset mode
  //
  PciSegmentAnd32 (RpBase + R_PCIE_RTPCL1, ~B_PCIE_RTPCL1_PCM);
  //
  // Step4:Program the Presets
  // Note : Requires silicon characterization
  //
  CpuPcieInitializePresets (RpBase, Params, CpuPcieSpeed);
  //
  // Step5:Program EQCFG4.LEP23B to 0 so that Phase 2 and Phase 3 EQ is not bypass
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~(B_PCIE_EQCFG4_PX16GLEP23B));
  //
  // Step6:Program EQCFG4.LEP3B to 0 so that Phase 3 EQ is not bypass
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~(B_PCIE_EQCFG4_PX16GLEP3B));
  //
  // Step7:Program EQCFG4 RTLEPCEB to 0 to enable HWEQ
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GLEPCEB);
  //
  // Step8:Program EQCFG4.RTPCOE to 0 enable Hardware Search Algorithm
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GRTPCOE);
  //
  // Step9,10:Rx wait time for each new eq should be configured to 1us
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GRWTNEVE_MASK, ((UINT32)V_PCIE_EQCFG4_PX16GRWTNEVE_1US << B_PCIE_EQCFG4_PX16GRWTNEVE_OFFSET));  //
  // Step11: For Linear Mode, BIOS needs to program the EQCFG4.MFLNTL to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GMFLNTL);
  //
  // Step12: Program EQCFG4.PX8GTSWLPCE to 0 // Program it to 4 (5us) as per post silicon recommendation
  //
  switch (Params->RootPort[RpIndex].Px16gtswlpce) {
    case CpuPciePx16gtswlpce500ns:
      Px16gtswlpce = 0;
      break;
    case CpuPciePx16gtswlpce1us:
      Px16gtswlpce = 1;
      break;
    case CpuPciePx16gtswlpce1_5us:
      Px16gtswlpce = 2;
      break;
    case CpuPciePx16gtswlpce2us:
      Px16gtswlpce = 3;
      break;
    case CpuPciePx16gtswlpce5us:
      Px16gtswlpce = 4;
      break;
    case CpuPciePx16gtswlpce6us:
      Px16gtswlpce = 5;
      break;
    case CpuPciePx16gtswlpce7us:
      Px16gtswlpce = 6;
      break;
    case CpuPciePx16gtswlpce8us:
      Px16gtswlpce = 7;
      break;
    default:
      Px16gtswlpce = 4;
      break;
  }
  DEBUG((DEBUG_INFO, "Presets/Coefficients Evaluation for Gen4 = %d\n", Px16gtswlpce));
  PciSegmentAndThenOr32(RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GTSWLPCE_MASK, ((UINT32)Px16gtswlpce << B_PCIE_EQCFG4_PX16GTSWLPCE_OFFSET));
  //
  // Step13:Rx wait time for each new eq should be configured to 3us
  // @ TODO : Check with MVE if this step is required
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GRWTNEVE_MASK, ((UINT32)V_PCIE_EQCFG4_PX16GRWTNEVE_3US << B_PCIE_EQCFG4_PX16GRWTNEVE_OFFSET));
  //
  // Step14: Program the HAEQ.HAPCCPI 0 to allow 1 iteration of Recovery.Equalization entry
  // @ TODO : Follow up with IP team on the value
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG4, (UINT32)~B_PCIE_EQCFG4_PX16GHAPCCPI_MASK, 2 << B_PCIE_EQCFG4_PX16GHAPCCPI_OFFSET);
  //
  // Step15: Program EQCFG5.HAPCSB as below and clear HAPCCPIE
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG5, (UINT32)~B_PCIE_EQCFG5_HAPCSB_MASK, Params->RootPort[RpIndex].Gen4PresetCoeffList << B_PCIE_EQCFG5_HAPCSB_OFFSET);
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~(B_PCIE_EQCFG4_PX16GHAPCCPIE));
  //
  // Step16,17: Program EQCFG4.MEQSMMFLNTL and EQCFG4.MFLNTL to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG4, (UINT32)~(B_PCIE_EQCFG4_PX16GMEQSMMFLNTL | B_PCIE_EQCFG4_PX16GMFLNTL));
  //
  // Step18: Program EQCFG4.REIC - value TBD in BWG - @TODO follow up with Arch to get the value and program it here
  //

  //
  // Step19,20: Program EQCFG5.NTIC,EQCFG5.EMD  to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG5, (UINT32)~(B_PCIE_EQCFG5_NTIC_MASK | B_PCIE_EQCFG5_EMD));

  //
  // Step21: To support 5 coefficient PECT needs to program to 4h to allow 4ms
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_EQCFG5, (UINT32)~(B_PCIE_EQCFG5_PCET_MASK), (4 << B_PCIE_EQCFG5_PCET_OFFSET));
  //
  // Step22,23: Program EQCFG5.NTEME and EQCFG5.MPEME to 0
  //
  PciSegmentAnd32 (RpBase + R_PCIE_EQCFG5, (UINT32)~(B_PCIE_EQCFG5_NTEME | B_PCIE_EQCFG5_MPEME));
  //
  // Step24: Program the following register for the Downstream Port Transmitter Preset value to P7
  //
  ///
  /// Configure Transmitter Preset for each Upstream and Downstream Port Lane:
  /// 1.  Set PL16L01EC.DPL0TP, Dxx:Fn + ABCh[3:0]    = 7
  /// 2.  Set PL16L01EC.UPL0TP, Dxx:Fn + ABCh[11:8]   = 7
  /// 3.  Set PL16L01EC.DPL1TP, Dxx:Fn + ABCh[19:16]  = 7
  /// 4.  Set PL16L01EC.UPL1TP, Dxx:Fn + ABCh[27:24]  = 7
  /// 5.  Set PL16L23EC.DPL2TP, Dxx:Fn + AC0h[3:0]    = 7
  /// 6.  Set PL16L23EC.UPL2TP, Dxx:Fn + AC0h[11:8]   = 7
  /// 7.  Set PL16L23EC.DPL3TP, Dxx:Fn + AC0h[19:16]  = 7
  /// 8.  Set PL16L23EC.UPL3TP, Dxx:Fn + AC0h[27:24]  = 7
  ///    Upto PL16L23EC.UPL3TP, Dxx:Fn + AC8h[27:24]  = 7
  ///
  Gen4Uptp = Params->RootPort[RpIndex].Gen4Uptp;
  Gen4Dptp = Params->RootPort[RpIndex].Gen4Dptp;
  DEBUG ((DEBUG_INFO, "Gen4Uptp = %x, Gen4Dptp = %x!\n", Gen4Uptp, Gen4Dptp));
  Data32And = (UINT32) ~(B_PCIE_PL16L01EC_UP16L1TP_MASK | B_PCIE_PL16L01EC_DP16L1TP_MASK | B_PCIE_PL16L01EC_UP16L0TP_MASK | B_PCIE_PL16L01EC_DP16L0TP_MASK);
  Data32Or = ((Gen4Uptp << B_PCIE_PL16L01EC_UP16L1TP_OFFSET) |
    (Gen4Dptp << B_PCIE_PL16L01EC_DP16L1TP_OFFSET) |
    (Gen4Uptp << B_PCIE_PL16L01EC_UP16L0TP_OFFSET) |
    (Gen4Dptp << B_PCIE_PL16L01EC_DP16L0TP_OFFSET));

  Data32And &= (UINT32) (~((B_PCIE_PL16L23EC_UP16L3TP_MASK | B_PCIE_PL16L23EC_DP16L3TP_MASK | B_PCIE_PL16L23EC_UP16L2TP_MASK | B_PCIE_PL16L23EC_DP16L2TP_MASK) << 16));
  Data32Or |= (((Gen4Uptp << B_PCIE_PL16L23EC_UP16L3TP_OFFSET) |
    (Gen4Dptp << B_PCIE_PL16L23EC_DP16L3TP_OFFSET) |
    (Gen4Uptp << B_PCIE_PL16L23EC_UP16L2TP_OFFSET) |
    (Gen4Dptp << B_PCIE_PL16L23EC_DP16L2TP_OFFSET)) << 16);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PL16L01EC, Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "CpuPcieDoGen4HardwareEq End!\n"));
}

/**
  Perform link equaliztion (coefficient search).
  @param[in] RpIndex      Port index
  @param[in] SiPolicy     The SI Policy
  @param[in] TempPciBus   Temp bus number
**/
VOID
CpuPcieLinkEqualization (
  UINT32                     RpIndex,
  CONST SI_POLICY_PPI        *SiPolicy,
  UINT8                      TempPciBus,
  CPU_PCIE_RP_PREMEM_CONFIG  *CpuPcieRpPreMemConfig
  )
{
  UINT64                            RpBase;
  CONST CPU_PCIE_ROOT_PORT_CONFIG   *RpConfig;

  DEBUG ((DEBUG_INFO, "CpuPcieLinkEqualization Start!\n"));

  RpBase = CpuPcieBase (RpIndex);

  DEBUG ((DEBUG_INFO, "Link Speed = %x\n", GetLinkSpeed(RpBase)));

  RpConfig = &mCpuPcieRpConfig->RootPort[RpIndex];

  //
  // If both rootport and endpoint support Common Clock config, set it before equalization
  //
  CpuPcieEnableCommonClock (RpIndex, TempPciBus);
  //
  // Gen3 HW Equalization
  //
  if ((RpConfig->PcieRpCommonConfig.Gen3EqPh3Method == CpuPcieEqHardware || RpConfig->PcieRpCommonConfig.Gen3EqPh3Method == CpuPcieEqDefault) && (CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] >= 3 || CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] == 0)) {
    DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
    DEBUG ((DEBUG_VERBOSE, "Dumping Registers before Gen3 HW Equalization\n"));
    CpuPcieDumpHwEqRegs (RpBase, CpuPcieGen3);
    DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
    DEBUG ((DEBUG_INFO, "CpuPcieDoGen3HardwareEq\n"));
    CpuPcieDoGen3HardwareEq (RpIndex, RpBase, mCpuPcieRpConfig);
    if (CpuPcieGetMaxLinkSpeed (RpBase) >= V_PCIE_LCAP_MLS_GEN3) {
      DEBUG ((DEBUG_VERBOSE, "Root port is capable of Gen3, so retrain the link to Gen3"));
      PciSegmentOr32 (RpBase + R_PCIE_LCTL3, B_PCIE_LCTL3_PE);
      DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
      DEBUG ((DEBUG_VERBOSE, "Dumping Registers after Gen3 HW Equalization\n"));
      CpuPcieDumpHwEqRegs (RpBase, CpuPcieGen3);
      DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
    }
    //
    // Gen4 HW Equalization
    //
    if (CpuPcieGetMaxLinkSpeed (RpBase) == V_PCIE_LCAP_MLS_GEN4 && (CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] > 3 || CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] == 0)) {
      DEBUG ((DEBUG_INFO, "CpuPcieDoGen4HardwareEq\n"));
      DEBUG((DEBUG_VERBOSE, "Root port is capable of Gen4, so retrain the link to Gen4"));
      DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
      DEBUG ((DEBUG_VERBOSE, "Dumping Registers before Gen4 HW Equalization\n"));
      CpuPcieDumpHwEqRegs (RpBase, CpuPcieGen4);
      DEBUG ((DEBUG_VERBOSE, "*****************************************\n"));
      CpuPcieDoGen4HardwareEq (RpIndex, RpBase, mCpuPcieRpConfig);
      PciSegmentOr32(RpBase + R_PCIE_LCTL3, B_PCIE_LCTL3_PE);
      DEBUG((DEBUG_VERBOSE, "*****************************************\n"));
      DEBUG((DEBUG_VERBOSE, "Dumping Registers after Gen4 HW Equalization\n"));
      CpuPcieDumpHwEqRegs(RpBase, CpuPcieGen4);
      DEBUG((DEBUG_VERBOSE, "*****************************************\n"));
    }
    if (RpConfig->PcieRpCommonConfig.Gen3EqPh3Method != CpuPcieEqHardware) {
      DEBUG((DEBUG_INFO, "Invalid EqMethod %d\n", RpConfig->PcieRpCommonConfig.Gen3EqPh3Method));
      ASSERT(FALSE);
    }
  }
  CpuPcieResetErrorCounts (RpBase);
  DEBUG ((DEBUG_INFO, "CpuPcieLinkEqualization End!\n"));
}


/**
  Check for device presence with timeout.

  @param[in]     RpBase      Root Port base address
  @param[in]     TimeoutUs   Timeout in microseconds
  @param[in,out] Timer       Timer value, must be initialized to zero
                             before the first call of this function.
**/
BOOLEAN
IsCpuPcieDevicePresent(
  IN     UINT64  RpBase,
  IN     UINT32  TimeoutUs,
  IN OUT UINT32  *Timer
  )
{
  while (TRUE) {
    if (CpuPcieIsEndpointConnected (RpBase)) {
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
CpuPcieIsPortForceVisible (
  IN UINT8                 RpIndex,
  IN UINT32                RpDisableMask,
  IN CONST CPU_PCIE_CONFIG *PciExpressConfig
  )
{
  UINT32                            RpEnabledMask;

  RpEnabledMask = (1u << GetMaxCpuPciePortNum ()) - 1;
  RpEnabledMask &= (~RpDisableMask);

  //
  // Only PEG010 needs to be kept force visible if Function swap is disabled, PEG010 is disabled and PEG011 and PEG012 are enabled
  //
  if ((RpIndex == 1) && (PciExpressConfig->PcieCommonConfig.RpFunctionSwap == 0)){
    if ((RpEnabledMask & (BIT0 << (RpIndex+1))) || (RpEnabledMask & (BIT0 << (RpIndex+2)))) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Configure root port function number mapping

**/
VOID
CpuPcieRpConfigureRpfnMapping (
  IN CPU_PCIE_CONFIG           *CpuPcieRpConfig
  )
{
  UINT8                                 PortIndex;
  UINT8                                 MaxPciePortNum;
  UINTN                                 DevNum;
  UINTN                                 FuncNum;
  UINT64                                RpBase;
  BOOLEAN                               PcieRootPortEnabled[CPU_PCIE_MAX_ROOT_PORTS];
  UINTN                                 FunctionNumber;
  UINT32                                Data32Or;
  UINT32                                Data32And;

  DEBUG ((DEBUG_INFO, "CpuPcieRpConfigureRpfnMapping () Start!\n"));
  FunctionNumber = 0;
  MaxPciePortNum = GetMaxCpuPciePortNum ();
  for (PortIndex = 0; PortIndex < CPU_PCIE_MAX_ROOT_PORTS; PortIndex++) {
    PcieRootPortEnabled[PortIndex] = FALSE;
  }
  //
  // Condition check for RpFunctionSwap Setup option - if it is disabled, do nothing and return from this function
  //
  if (!(CpuPcieRpConfig->PcieCommonConfig.RpFunctionSwap)) {
    DEBUG ((DEBUG_VERBOSE, "Function swap is disabled in setup - return!\n"));
    return;
  }
  ///
  /// Configure root port function number mapping
  ///
  for (PortIndex = 1; PortIndex < MaxPciePortNum; PortIndex++) {
    GetCpuPcieRpDevFun (PortIndex, &DevNum, &FuncNum);
    RpBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, DevNum, FuncNum, 0);
    //
    // Search for the enabled functions
    //
    if ((PciSegmentRead16 (RpBase) != 0xFFFF)) {
      PcieRootPortEnabled[PortIndex] = TRUE;
    }
  }
  //
  // 1. Check if Function 0 is enabled on Device 1, if yes do nothing
  //
  if (PcieRootPortEnabled[1] == TRUE) {
    DEBUG ((DEBUG_VERBOSE, "Function 0 is enabled - return!\n"));
    return;
  }
  //
  // 2.Check if all the functions in Device 1 is disabled. If yes, do nothing
  //
  else if ((PcieRootPortEnabled[2] == FALSE) && (PcieRootPortEnabled[3] == FALSE)) {
    DEBUG ((DEBUG_VERBOSE, "All functions in the device is disabled - return!\n"));
    return;
  }
  else {
  //
  // 3.Otherwise, switch Function numbers of the RP which was Func0 and one RP that won't be disabled.
  //
  ///
  /// According to each SA PCIe RP enable status to update Function Map.
  ///
    for (PortIndex = 1; PortIndex < MaxPciePortNum; PortIndex++) {
      RpBase = CpuPcieBase(PortIndex);
      if (PcieRootPortEnabled[PortIndex]) {
          ///
          /// Program RP0FN for first enabled SA PCIE Root Port then lock the register.
          ///
          Data32And = (UINT32)~(B_SA_SPX_PCR_PCD_RP0FN);
          Data32Or = FunctionNumber;
          PciSegmentAndThenOr32 (RpBase +  R_SA_SPX_PCR_PCD, Data32And, Data32Or);
          GetCpuPcieRpDevFun (PortIndex, &DevNum, &FuncNum);
          FunctionNumber = FuncNum;
          break;
      }
    }
  ///
  /// Program RP0FN for first Root Port then lock the register.
  ///
    PortIndex = 1;
    Data32And = (UINT32)~(B_SA_SPX_PCR_PCD_RP0FN);
    Data32Or = FunctionNumber;
    RpBase = CpuPcieBase(PortIndex);
    PciSegmentAndThenOr32 (RpBase +  R_SA_SPX_PCR_PCD, Data32And, Data32Or);
    DEBUG ((DEBUG_VERBOSE, "Function %x is swapped with Function 0\n", FunctionNumber));
  }
  DEBUG ((DEBUG_INFO, "CpuPcieRpConfigureRpfnMapping () End!\n"));
}

/**
  Lock SRL bits - lock it for all root ports

**/
VOID
CpuPcieRpSetSecuredRegisterLock (
  VOID
  )
{
  UINT32                                Data32Or;
  UINT32                                Data32And;
  UINT64                                RpBase;
  UINT8                                 PortIndex;
  UINT8                                 MaxCpuPciePortNum;

  DEBUG ((DEBUG_INFO, "CpuPcieRpSetSecuredRegisterLock () Start!\n"));
  MaxCpuPciePortNum = GetMaxCpuPciePortNum();
  for (PortIndex = 0; PortIndex < MaxCpuPciePortNum; PortIndex++) {
    RpBase = CpuPcieBase(PortIndex);
    Data32And = (UINT32)~B_SA_SPX_PCR_PCD_SRL;
    Data32Or = (UINT32) B_SA_SPX_PCR_PCD_SRL;
    PciSegmentAndThenOr32 (RpBase +  R_SA_SPX_PCR_SRL, Data32And, Data32Or);
    ///Secure Register Lock (SRL) 0xC8C[0]: 1
    ///Secure Equalization Register Lock (SERL) 0XC8C[8]: 1
    ///LTR Configuration Lock (LTRCFGLOCK) 0xC8C[16]: 1
    ///Device ID Override Lock (DIDOVR_LOCK) 0xC8C[24]: 1
    Data32Or = (B_PCIE_LPCR_SRL | B_PCIE_LPCR_SERL | B_PCIE_LPCR_DIDOVR_LOCK);
    PciSegmentOr32 (RpBase + R_PCIE_LPCR, Data32Or);
    DEBUG ((DEBUG_VERBOSE, "R_PCIE_LPCR after setting SRL = %x\n", PciSegmentRead32(RpBase + R_PCIE_LPCR)));
  //
  // Check if SRL bit actually got programmed. If not, then it means some code accessed MPC register earlier and locked it
  //
  }

  ASSERT((PciSegmentRead32(RpBase + R_PCIE_LPCR) & B_PCIE_LPCR_SRL) == B_PCIE_LPCR_SRL);


  DEBUG ((DEBUG_INFO, "CpuPcieRpSetSecuredRegisterLock () End!\n"));
}

/**
  Checks integrity of Policy settings for all rootports.
  Triggers assert if anything is wrong. For debug builds only

  @param[in] PciExpressConfig     Pointer to CPU_PCIE_CONFIG instance
**/
VOID
CpuPciePolicySanityCheck (
  IN OUT CPU_PCIE_CONFIG *PciExpressConfig
  )
{
  UINT8                       RpIndex;
  CPU_PCIE_ROOT_PORT_CONFIG   *RpConfig;

  for (RpIndex = 0; RpIndex < GetMaxCpuPciePortNum (); RpIndex++) {
    RpConfig  = &PciExpressConfig->RootPort[RpIndex];
    //
    // Ports with hotplug support must have SlotImplemented bit set
    //
    ASSERT (!RpConfig->PcieRpCommonConfig.HotPlug || RpConfig->PcieRpCommonConfig.SlotImplemented);
  }
}

/**
  Performs mandatory Root Port Initialization.
  This function is silicon-specific and configures proprietary registers.

  @param[in]  PortIndex               The root port to be initialized (zero based)
  @param[in]  SiPolicy                The SI Policy PPI
  @param[in]  SiPreMemPolicyPpi       The SI PreMem Policy PPI
  @param[in]  TempPciBus              The temporary Bus number for root port initialization
  @param[out] Gen4DeviceFound         Reports if there's Gen3 capable endpoint connected to this rootport
**/
STATIC
VOID
InitCpuPcieSingleRootPort(
  IN  UINT8                                     PortIndex,
  IN  CONST SI_POLICY_PPI                       *SiPolicy,
  IN  SI_PREMEM_POLICY_PPI                      *SiPreMemPolicyPpi,
  IN  UINT8                                     TempPciBus,
  OUT BOOLEAN                                   *Gen4DeviceFound,
  CPU_PCIE_RP_PREMEM_CONFIG                     *CpuPcieRpPreMemConfig
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
  CONST CPU_PCIE_ROOT_PORT_CONFIG   *RootPortConfig;
  VTD_CONFIG                        *VtdConfig;
  BOOLEAN                           DeviceFound;
  UINT32                            Tls;
  PCIE_DEVICE_INFO                  DevInfo;
  UINT8                             RpLinkSpeed;
  UINT32                            RpMaxPayloadCapability;
  BOOLEAN                           RpGen34Capable;
  UINT8                             RpIndex;

  DEBUG ((DEBUG_INFO, "InitCpuPcieSingleRootPort (%d) Start \n", PortIndex + 1));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gVtdConfigGuid, (VOID *) &VtdConfig);
  ASSERT_EFI_ERROR (Status);

  RootPortConfig = &mCpuPcieRpConfig->RootPort[PortIndex];
  RpBase = CpuPcieBase (PortIndex);
  RpGen34Capable = FALSE;

  Tls = PciSegmentRead16 (RpBase + R_PCIE_LCTL2) & B_PCIE_LCTL2_TLS;
  DEBUG ((DEBUG_INFO, "Target Link Speed = %x \n", Tls));
  ASSERT (Tls < V_PCIE_LCTL2_TLS_GEN4);

  /// Following reset it is possible for a device to terminate the
  /// configuration request but indicate that it is temporarily unable to process it,
  /// but in the future. The device will return the Configuration Request Retry Status.
  /// By setting the Completion Retry Status Replay Enable, Dxx:Fn + 320h[22],
  /// the RP will re-issue the request on receiving such status.
  /// The BIOS shall set this bit before first configuration access to the endpoint.
  DEBUG ((DEBUG_INFO, "Set the Completion Retry Status Replay Enable, Dxx:Fn + 320h[22]\n"));
  PciSegmentOr32 (RpBase + R_PCIE_PCIECFG2, B_PCIE_PCIECFG2_CRSREN);

  DeviceFound = CpuPcieGetDeviceInfo (RpBase, TempPciBus, &DevInfo);
  if (DeviceFound){
    *Gen4DeviceFound = ((GetMaxLinkSpeed (RpBase) >= 4) && DeviceFound && (DevInfo.MaxLinkSpeed >= 4));
    DEBUG ((DEBUG_INFO, "End point detected with Gen%x capability!!!\n", DevInfo.MaxLinkSpeed));
    }
  else{
    DEBUG ((DEBUG_INFO, "No endpoint connected to root port\n", PortIndex + 1));
    DevInfo.MaxLinkSpeed = 0;
  }
  //
  // Some features are incompatible with Gen4 and should not be enabled if rootport is capable of Gen4.
  // As an optimization we consider RP as Gen4 capable only if it supports hotplug or has Gen4 device connected.
  // It makes those features available when RP is Gen4 capable but a slower device is connected.
  // This optimization can be deleted if accessing endpoint in early boot is undesired.
  //
  if ((GetMaxLinkSpeed (RpBase) >= 3) && (RootPortConfig->PcieRpCommonConfig.HotPlug || DeviceFound)) {
    RpGen34Capable = TRUE;
    DEBUG ((DEBUG_INFO, "Root port is Gen3/4 capable!!!\n"));
  }
  ///
  /// If only 128B max payload is supported set CCFG.UNRS to 0.
  ///
  /// If peer writes are supported set max payload size supported to 64B due to CPU PSF limitation, clear CCFG.UPMWPD
  /// and program all the CPU PCIe Root Ports such that upstream posted writes and upstream non-posted requests
  /// are split at 128B boundary by setting CCFG fields: UPSD to 0, CCFG.UPRS to 000b and UNSD to 0, UNRS to 000b
  ///
  Data32And = ~0u;
  Data32Or  = 0;
  ///
  /// UPRS and UNRS needs to be programmed to 64B irrespective of any condition for CPU PCIe
  ///
  RpMaxPayloadCapability = CpuPcieMaxPayload256;
  Data32And &= (UINT32) ~(B_PCIE_CCFG_UNSD | B_PCIE_CCFG_UNRS_MASK);
  Data32Or  |= (UINT32)  (V_PCIE_CCFG_UNRS_64B << B_PCIE_CCFG_UNRS_OFFSET);
  Data32And &= (UINT32) ~( B_PCIE_CCFG_UPSD | B_PCIE_CCFG_UPRS_MASK); // @TODO B_PCIE_CCFG_UPMWPD  - clear this bit only if P2P is enabled
  Data32Or  |= (UINT32)  (V_PCIE_CCFG_UPRS_64B << B_PCIE_CCFG_UPRS_OFFSET);

  DEBUG ((DEBUG_INFO, "CpuPcieMaxPayloadMax = %x\n", CpuPcieMaxPayloadMax));
  ASSERT (RootPortConfig->PcieRpCommonConfig.MaxPayload < CpuPcieMaxPayloadMax);

  ///
  /// Set B0:Dxx:Fn + D0h [13:12] to 01b
  ///
  DEBUG ((DEBUG_INFO, "Upstream Non-Posted Request Delay set to 01b which puts delay of 4 clocks\n"));
  Data32And &= (UINT32)~(B_PCIE_CCFG_UNRD); // @TODO B_PCIE_CCFG_UMRPD - clear this bit only if P2P is enabled
  Data32Or  |= (1u << B_PCIE_CCFG_UNRD_OFFSET);

  PciSegmentAndThenOr32 (RpBase + R_PCIE_CCFG, Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "Set R_PCIE_DCAP[B_PCIE_DCAP_MPS] = %x\n", RpMaxPayloadCapability));
  PciSegmentAndThenOr16 (RpBase + R_PCIE_DCAP, (UINT16) ~B_PCIE_DCAP_MPS, (UINT16)RpMaxPayloadCapability);

  ///
  /// Program VC0CTL [7:1] to 1111111b
  ///
  Data32And = (UINT32)~B_PCIE_VC0CTL_TVM_MASK;
  Data32Or = (UINT32)(V_PCIE_VC0CTL_TVM_NO_VC << B_PCIE_VC0CTL_TVM_OFFSET);
  PciSegmentAndThenOr32(RpBase + R_PCIE_VC0CTL, Data32And, Data32Or);

  ///
  /// Coalescing Start
  ///
  DEBUG ((DEBUG_INFO, "Coalescing Start\n"));
  ///
  /// Program COCTL.PWCE 594h [0] = 1b
  /// Program COCTL.DDCE 594h [1] = 1b
  /// Program COCTL.CT 594h [9:2] = 3b
  /// Program COCTL.CTE 594h [10] = 1b
  /// Program COCTL.ROAOP 594h [11] = 0b
  /// Program COCTL.PCLM 594h [14:13] = 3b
  /// Program COCTL.NPCLM 594h [16:15] = 3b

  Data32And = ~(UINT32)(B_PCIE_COCTL_CT_MASK | B_PCIE_COCTL_ROAOP | B_PCIE_COCTL_PCLM_MASK | B_PCIE_COCTL_NPCLM_MASK);
  Data32Or = B_PCIE_COCTL_PWCE | B_PCIE_COCTL_DDCE | (3 << B_PCIE_COCTL_CT_OFFSET) |
               B_PCIE_COCTL_CTE | (0x3 << B_PCIE_COCTL_PCLM_OFFSET) | (0x3 << B_PCIE_COCTL_NPCLM_OFFSET);

  PciSegmentAndThenOr32 (RpBase + R_PCIE_COCTL, Data32And, Data32Or);
  DEBUG((DEBUG_INFO, "COCTL = %x\n", PciSegmentRead32(RpBase + R_PCIE_COCTL)));
  ///
  /// Chain Bit Generation Mode(CBGM) 0x6CC 21 1
  ///
  Data32And = ~(UINT32)B_PCIE_ACRG3_CBGM;
  Data32Or  = B_PCIE_ACRG3_CBGM;
  PciSegmentAndThenOr32 (RpBase + R_PCIE_ACRG3, Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "R_PCIE_ACRG3 = %x\n", PciSegmentRead32(RpBase + R_PCIE_ACRG3)));
  DEBUG ((DEBUG_INFO, "Coalescing End\n"));
  ///
  /// Coalescing End
  ///

  ///
  /// Power Optimizer Configuration
  /// If B0:Dxx:Fn + 400h is programmed, BIOS will also program B0:Dxx:Fn + 404h [1:0] = 11b,
  /// to enable these override values.
  /// - Fn refers to the function number of the root port that has a device attached to it.
  /// - Default override value for B0:Dxx:Fn + 400h should be 880F880Fh
  /// - Also set 404h[2] to lock down the configuration
  /// - Refer to table below for the 404h[3] policy bit behavior.
  /// Done in PcieSetPm()
  ///
  /// Program B0:Dxx:Fn + 64h [11] = 1b
  ///
  if (RootPortConfig->PcieRpCommonConfig.Aspm != FALSE) {
    Data32Or = 0;
    Data32And = ~0u;
    if (RootPortConfig->PcieRpCommonConfig.LtrEnable == TRUE) {
      Data32Or |= B_PCIE_DCAP2_LTRMS;
    } else {
      Data32And &= (UINT32) ~(B_PCIE_DCAP2_LTRMS);
    }
    ///
    /// Optimized Buffer Flush/Fill (OBFF) is not supported.
    /// Program B0:Dxx:Fn + 64h [19:18] = 2h
    /// BIOS: Program this field to 10. Note that this register is not required to be program if there is no PCIe Device attached for non-Hot Pluggable Port.
    /// @ TODO : Add condition to check if end point is connected for non-Hot Pluggable Port, if not then this register need not be programmed
    ///
    Data32And &= (UINT32) ~B_PCIE_DCAP2_OBFFS;
    Data32Or = (V_PCIE_DCAP2_OBFFS_WAKE_ONLY << B_PCIE_DCAP2_OBFFS_OFFSET);
    PciSegmentAndThenOr32 (RpBase + R_PCIE_DCAP2, Data32And, Data32Or);
    DEBUG ((DEBUG_INFO, "R_PCIE_DCAP2 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_DCAP2)));

    ///
    /// Latency Tolerance Reporting Override (LTROVR) 0x400  31:0 0x880F880F
    ///
    Data32And = 0xFFFFFFFF;
    Data32Or = 0x880F880F;
    PciSegmentAndThenOr32 (RpBase + R_PCIE_LTROVR, Data32And, Data32Or);

    ///
    /// LTR Non-Snoop Override Enable (LTRNSOVREN) 0x404  1 1
    /// LTR Snoop Override Enable (LTRSOVREN) 0x404  0 1
    ///
    Data32And = (UINT32) ~(B_PCIE_LTROVR2_LTRNSOVREN | B_PCIE_LTROVR2_LTRSOVREN);
    Data32Or = (UINT32) (B_PCIE_LTROVR2_LTRNSOVREN | B_PCIE_LTROVR2_LTRSOVREN);
    PciSegmentAndThenOr32 (RpBase + R_PCIE_LTROVR2, Data32And, Data32Or);

    ///
    /// Program B0:Dxx:Fn + 68h [10] = 1b
    ///
    Data16 = PciSegmentRead16 (RpBase + R_PCIE_DCTL2);
    if (RootPortConfig->PcieRpCommonConfig.LtrEnable == TRUE) {
      Data16 |= B_PCIE_DCTL2_LTREN;
    } else {
      Data16 &= (UINT16) ~(B_PCIE_DCTL2_LTREN);
    }
    PciSegmentWrite16 (RpBase + R_PCIE_DCTL2, Data16);
    DEBUG ((DEBUG_INFO, "R_PCIE_DCTL2 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_DCTL2)));
  } /// End of ASPM enable check
  ///
  /// PCH BIOS Spec Section 8.15.1 Power Optimizer Configuration
  /// Step 3 done in SaPciexpressHelpersLibrary.c ConfigureLtr
  /// @TODO : Review PciExpressHelpersLibrary
  ///

  ///
  /// Set Dxx:Fn + 300h[23:00] = 00B799AAh if LCTL.ES = 1 else program it to 0x00B7F6CC
  /// Set Dxx:Fn + 304h[11:00] = 0C97h
  ///

  if (PciSegmentRead16 (RpBase + R_PCIE_LCTL) & B_PCIE_LCTL_ES) {
    PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIERTP1, ~0x00FFFFFFu, 0x00B799AA);
  } else{
      PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIERTP1, ~0x00FFFFFFu, 0x00B7F6CC);
    }
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIERTP2, ~0x00000FFFu, 0x00000C97);
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIERTP1 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIERTP1)));
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIERTP2 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIERTP2)));
  ///
  /// Set Dxx:Fn + 0xC50[5] = 1 (ACGR3S2.SRL = 1)
  ///
  PciSegmentOr32 (RpBase + R_PCIE_ACGR3S2, B_PCIE_ACGR3S2_SRL);
  DEBUG ((DEBUG_INFO, "R_PCIE_ACGR3S2 after setting SRL = %x\n", PciSegmentRead32(RpBase + R_PCIE_ACGR3S2)));
  ///
  /// Set Dxx:Fn + 0xC80[2] = 0x1 (AECR1G3.CRMTDDE)
  ///
  Data32And = ~(UINT32)(B_PCIE_AECR1G3_CRMTDDE | B_PCIE_AECR1G3_L1OFFRDYHEWT_MASK);
  Data32Or = B_PCIE_AECR1G3_L1OFFRDYHEWTEN | (V_PCIE_AECR1G3_L1OFFRDYHEWT << B_PCIE_AECR1G3_L1OFFRDYHEWT_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_AECR1G3, Data32And , Data32Or);
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set Dxx:Fn + 318h [31:16] = 1414h (Gen2 and Gen1 Active State L0s Preparation Latency)
  ///
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEL0SC, ~0xFFFF0000u, 0x14140000);
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIEL0SC after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIEL0SC)));
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// 1.
  /// Root Port L1 Squelch Polling (RPL1SQPOL) 0xE8  1 0
  /// Root Port Detect Squelch Polling (RPDTSQPOL) 0xE8  0 0
  ///
  Data32And = ~ (UINT32) (B_PCIE_PWRCTL_RPDTSQPOL | B_PCIE_PWRCTL_RPL1SQPOL);
  PciSegmentAnd32 (RpBase + R_PCIE_PWRCTL, Data32And);
  DEBUG ((DEBUG_INFO, "R_PCIE_PWRCTL after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PWRCTL)));
  ///
  /// 2.  Program Dxx:Fn + 320h[27, 30] to [0,1]
  /// Enable PCIe Relaxed Order to always allow downstream completions to pass posted writes,
  /// 3.  Set B0:Dxx:Fn:320h[24:23] = 11b
  /// Set PME timeout to 10ms, by
  /// 4.  Set B0:Dxx:Fn:320h[21:20] = 01b
  ///

  Data32And = (UINT32) ~(B_PCIE_PCIECFG2_PMET | B_PCIE_PCIECFG2_RLLG3R);
  Data32Or  = B_PCIE_PCIECFG2_LBWSSTE |
    B_PCIE_PCIECFG2_CROAOV |
    B_PCIE_PCIECFG2_CROAOE |
    (V_PCIE_PCIECFG2_PMET << B_PCIE_PCIECFG2_PMET_OFFSET);

  PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIECFG2, Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIECFG2 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIECFG2)));
  ///
  /// Squelch Propagation Control Enable (SPCE) 0x324  5 1
  /// Squelch Off in L0 (SQOL0) 0x324  7 0
  /// Link Down SWQ Reset Policy 0x324  13 0
  /// Un-Squelch Sampling Period(USSP):0x324  27:26 10b
  /// B_PCIE_PCIEDBG_CTONFAE 1
  /// B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS_MASK 00
  ///
  Data32And = (UINT32)~(B_PCIE_PCIEDBG_SPCE | B_PCIE_PCIEDBG_SQOL0 | B_PCIE_PCIEDBG_LDSWQRP | B_PCIE_PCIEDBG_USSP_MASK | B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS_MASK);
  Data32Or = B_PCIE_PCIEDBG_SPCE | (V_PCIE_PCIEDBG_USSP_32NS << B_PCIE_PCIEDBG_USSP_OFFSET) | B_PCIE_PCIEDBG_CTONFAE;
  PciSegmentAndThenOr32 (RpBase + R_PCIE_PCIEDBG, Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIEDBG after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIEDBG)));
  ///
  /// Program Dxx:Fn + 424h [6, 5, 4] = [1, 1, 1]
  ///
  PciSegmentOr32 (
    RpBase + R_PCIE_PCIEPMECTL2,
    (B_PCIE_PCIEPMECTL2_L23RDYSCPGE |
     B_PCIE_PCIEPMECTL2_L1SCPGE)
    );
  DEBUG ((DEBUG_INFO, "R_PCIE_PCIEPMECTL2 after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIEPMECTL2)));
  ///
  /// If Dxx:Fn + F5h[0] = 1b or step 3 is TRUE, set Dxx:Fn + 4Ch[17:15] = 4h
  /// Else set Dxx:Fn + 4Ch[17:15] = 010b
  ///
  ///

  Data32And = (UINT32) (~B_PCIE_LCAP_EL1_MASK);
  Data32Or = 4 << B_PCIE_LCAP_EL1_OFFSET;

  ///
  /// Set LCAP APMS according to platform policy.
  ///
  DEBUG ((DEBUG_INFO, "Set LCAP APMS according to platform policy %x\n", RootPortConfig->PcieRpCommonConfig.Aspm));
  if (RootPortConfig->PcieRpCommonConfig.Aspm < CpuPcieAspmAutoConfig) {
    Data32And &= (UINT32) ~B_PCIE_LCAP_APMS_MASK;
    Data32Or  |= RootPortConfig->PcieRpCommonConfig.Aspm << B_PCIE_LCAP_APMS_OFFSET;
  } else {
    Data32Or  |= B_PCIE_LCAP_APMS_L0S | B_PCIE_LCAP_APMS_L1;
  }

  //
  // Force disable L0s for Gen3 capable rootports
  //
  if (RpGen34Capable) {
    DEBUG ((DEBUG_INFO, "Turn off L0S\n"));
    Data32And &= (UINT32) ~B_PCIE_LCAP_APMS_L0S;
    Data32Or  &= (UINT32) ~B_PCIE_LCAP_APMS_L0S;
  }
  //
  // The EL1, ASPMOC and APMS of LCAP are RWO, must program all together.
  //
  PciSegmentAndThenOr32 (RpBase + R_PCIE_LCAP, Data32And, Data32Or);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Configure PCI Express Number of Fast Training Sequence for each port
  /// 1.  Set Dxx:Fn + 314h [31:24, 23:16, 15:8, 7:0] to [7Eh, 5Bh, 3Fh, 2Ch]
  /// 2.  Set Dxx:Fn + 478h [31:24, 15:8, 7:0] to [28h, 40h, 2Ch]
  ///
  PciSegmentWrite32 (RpBase + R_PCIE_PCIENFTS, 0x7E5B3F2C);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_G3L0SCTL, ~0xFF00FFFFu, 0x2800402C);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set MPC.IRRCE, Dxx:Fn + D8h[25] = 1b using byte access
  /// For system that support MCTP over PCIE set
  /// Set PCIE RP PCI offset D8h[27] = 1b
  /// Set PCIE RP PCI offset D8h[3] = 1b
  ///
  Data8And = (UINT8) (~(B_PCIE_MPC_IRRCE | B_PCIE_MPC_MMBNCE) >> 24);
  Data8Or = B_PCIE_MPC_MMBNCE >> 24;
  if (VtdConfig->VtdDisable) {
    DEBUG ((DEBUG_INFO, "Enable IRRCE\n"));
    Data8Or |= B_PCIE_MPC_IRRCE >> 24;
  }
  PciSegmentAndThenOr8 (RpBase + R_PCIE_MPC + 3, Data8And, Data8Or);

  Data8And = (UINT8) ~(B_PCIE_MPC_MCTPSE);
  Data8Or  = B_PCIE_MPC_MCTPSE;
  PciSegmentAndThenOr8 (RpBase + R_PCIE_MPC, Data8And, Data8Or);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set PCIE RP PCI offset F5h[7:4] = 0000b
  ///
  PciSegmentAnd8 (RpBase + R_PCIE_PHYCTL2, (UINT8) ~(B_PCIE_PHYCTL2_TDFT_MASK | B_PCIE_PHYCTL2_TXCFGCHGWAIT_MASK));

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Enable PME_TO Time-Out Policy, Dxx:Fn + E2h[6] =1b
  ///
  PciSegmentOr8 (RpBase + R_PCIE_RPPGEN, B_PCIE_RPPGEN_PTOTOP);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Enable EQ TS2 in Recovery Receiver Config, Dxx:Fn + 450h[7]= 1b
  ///

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// If there is no IOAPIC behind the root port, set EOI Forwarding Disable bit (PCIE RP PCI offset D4h[1]) to 1b.
  /// For Empty Hot Plug Slot, set is done in InitCpuPcieSingleRootPort ()
  ///

  ///
  /// System bios should initiate link retrain for all slots that has card populated after register restoration.
  /// Done in SaPciexpressHelpersLibrary.c CpuPcieInitRootPortDownstreamDevices ()
  ///

  ///
  /// Configure Completion Timeout
  ///
  Data16And = (UINT16) ~(B_PCIE_DCTL2_CTD | B_PCIE_DCTL2_CTV_MASK);
  Data16Or  = 0;
  if (RootPortConfig->PcieRpCommonConfig.CompletionTimeout == CpuPcieCompletionTO_Disabled) {
    DEBUG((DEBUG_INFO, "Completion timeout disabled\n"));
    Data16Or = B_PCIE_DCTL2_CTD;
  } else {
    switch (RootPortConfig->PcieRpCommonConfig.CompletionTimeout) {
      case CpuPcieCompletionTO_Default:
        Data16Or = V_PCIE_DCTL2_CTV_DEFAULT;
        break;

      case CpuPcieCompletionTO_16_55ms:
        Data16Or = V_PCIE_DCTL2_CTV_40MS_50MS;
        break;

      case CpuPcieCompletionTO_65_210ms:
        Data16Or = V_PCIE_DCTL2_CTV_160MS_170MS;
        break;

      case CpuPcieCompletionTO_260_900ms:
        Data16Or = V_PCIE_DCTL2_CTV_400MS_500MS;
        break;

      case CpuPcieCompletionTO_1_3P5s:
        Data16Or = V_PCIE_DCTL2_CTV_1P6S_1P7S;
        break;

      default:
        Data16Or = 0;
        break;
    }
  }
  DEBUG ((DEBUG_INFO, "Completion timeout = %x\n", Data16Or));
  PciSegmentAndThenOr16 (RpBase + R_PCIE_DCTL2, Data16And, Data16Or);

  ///
  /// For Root Port Slots Numbering on the CRBs.
  ///
  Data32Or  = 0;
  Data32And = (UINT32) (~(B_PCIE_SLCAP_SLV_MASK | B_PCIE_SLCAP_SLS_MASK | B_PCIE_SLCAP_PSN_MASK));
  ///
  /// PCH BIOS Spec section 8.8.2.1
  /// Note: If Hot Plug is supported, then write a 1 to the Hot Plug Capable (bit6) and Hot Plug
  /// Surprise (bit5) in the Slot Capabilities register, PCIE RP PCI offset 54h. Otherwise,
  /// write 0 to the bits PCIe Hot Plug SCI Enable
  ///
  Data32And &= (UINT32) (~(B_PCIE_SLCAP_HPC | B_PCIE_SLCAP_HPS));
  if (RootPortConfig->PcieRpCommonConfig.HotPlug) {
    DEBUG ((DEBUG_INFO, "Write a 1 to the Hot Plug Capable (bit6) and Hot PlugSurprise (bit5)\n"));
    Data32Or |= B_PCIE_SLCAP_HPC | B_PCIE_SLCAP_HPS;
  }
  //the recommended values are SLV = 75 and SLS = 1
  Data32Or |= (UINT32) (75 << B_PCIE_SLCAP_SLV_OFFSET);
  Data32Or |= (UINT32) (1 << B_PCIE_SLCAP_SLS_OFFSET);

  ///
  /// PCH BIOS Spec section 8.2.4
  /// Initialize Physical Slot Number for Root Ports
  ///
  Data32Or |= (UINT32)(RootPortConfig->PcieRpCommonConfig.PhysicalSlotNumber << B_PCIE_SLCAP_PSN_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_SLCAP, Data32And, Data32Or);

  CpuPcieInitCapabilityList (PortIndex, RpBase, RootPortConfig);
  //
  // All actions involving LinkDisable must finish before anything is programmed on endpoint side
  // because LinkDisable resets endpoint
  //

  ///
  /// Perform equalization for Gen3/Gen4 capable ports
  ///
  if ((RpGen34Capable && (DevInfo.MaxLinkSpeed >= 3)) || mCpuPcieRpConfig->PcieCommonConfig.ComplianceTestMode) {
    DEBUG ((DEBUG_INFO, "Perform equalization for Gen3/Gen4 capable ports\n"));
    CpuPcieLinkEqualization (PortIndex, SiPolicy, TempPciBus, CpuPcieRpPreMemConfig);
  }
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set "Link Speed Training Policy", Dxx:Fn + D4h[6] to 1.
  /// Make sure this is after mod-PHY related programming is completed.
  /// C50h[3:0] "LSTP Target Link Speed" doesn't need to program because LSTP is set to 1
  PciSegmentOr32 (RpBase + R_PCIE_MPC2, B_PCIE_MPC2_LSTP);

  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Step 29 If Transmitter Half Swing is enabled, program the following sequence
  /// a. Ensure that the link is in L0.
  /// b. Program the Link Disable bit (0x50[4]) to 1b.
  /// c. Program the Analog PHY Transmitter Voltage Swing bit (0xE8[13]) to set the transmitter swing to half/full swing
  /// d. Program the Link Disable bit (0x50[4]) to 0b.
  /// BIOS can only enable this on SKU where GEN3 capability is disabled on that port
  RpLinkSpeed   = PciSegmentRead8 (RpBase + R_PCIE_LCAP) & B_PCIE_LCAP_MLS;
  if (RpLinkSpeed < V_PCIE_LCAP_MLS_GEN3 && RootPortConfig->PcieRpCommonConfig.TransmitterHalfSwing) {
    PciSegmentOr8 (RpBase + R_PCIE_LCTL, B_PCIE_LCTL_LD);
    while (CpuPcieIsLinkActive (RpBase)) {
      // wait until link becomes inactive before changing swing
    }
    DEBUG ((DEBUG_INFO, "Program Tx Swing\n"));
    PciSegmentOr16 (RpBase + R_PCIE_PWRCTL, B_PCIE_PWRCTL_TXSWING);
    PciSegmentAnd8 (RpBase + R_PCIE_LCTL, (UINT8) ~(B_PCIE_LCTL_LD));
  }
  ///
  /// PCH BIOS Spec Section 8.15 Additional PCI Express* Programming Steps
  /// Set "Poisoned TLP Non-Fatal Advisory Error Enable", Dxx:Fn + D4h[12] to 1
  ///
  Data32Or = B_PCIE_MPC2_PTNFAE;
  PciSegmentOr32 (RpBase + R_PCIE_MPC2, Data32Or);

  //
  // L1LOW LTR threshold latency value
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCIE_PCIEPMECTL,
    (UINT32) ~B_PCIE_PCIEPMECTL_L1LTRTLV_MASK,
    (V_PCIE_PCIEPMECTL_L1LTRTLV << B_PCIE_PCIEPMECTL_L1LTRTLV_OFFSET)
    );
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_PCIEPMECTL after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_PCIEPMECTL)));
  ///
  /// Additional configurations
  ///
  ///
  /// Configure Error Reporting policy in the Device Control Register
  ///
  Data16And = (UINT16) (~(B_PCIE_DCTL_URE | B_PCIE_DCTL_FEE | B_PCIE_DCTL_NFE | B_PCIE_DCTL_CEE));
  Data16Or  = 0;

  if (RootPortConfig->PcieRpCommonConfig.UnsupportedRequestReport) {
    Data16Or |= B_PCIE_DCTL_URE;
  }

  if (RootPortConfig->PcieRpCommonConfig.FatalErrorReport) {
    Data16Or |= B_PCIE_DCTL_FEE;
  }

  if (RootPortConfig->PcieRpCommonConfig.NoFatalErrorReport) {
    Data16Or |= B_PCIE_DCTL_NFE;
  }

  if (RootPortConfig->PcieRpCommonConfig.CorrectableErrorReport) {
    Data16Or |= B_PCIE_DCTL_CEE;
  }

  PciSegmentAndThenOr16 (RpBase + R_PCIE_DCTL, Data16And, Data16Or);
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_DCTL after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_DCTL)));
  ///
  /// Configure Interrupt / Error reporting in R_PCIE_RCTL
  ///
  Data16And = (UINT16) (~(B_PCIE_RCTL_SFE | B_PCIE_RCTL_SNE | B_PCIE_RCTL_SCE));
  Data16Or  = 0;

  if (RootPortConfig->PcieRpCommonConfig.SystemErrorOnFatalError) {
    Data16Or |= B_PCIE_RCTL_SFE;
  }

  if (RootPortConfig->PcieRpCommonConfig.SystemErrorOnNonFatalError) {
    Data16Or |= B_PCIE_RCTL_SNE;
  }

  if (RootPortConfig->PcieRpCommonConfig.SystemErrorOnCorrectableError) {
    Data16Or |= B_PCIE_RCTL_SCE;
  }

  PciSegmentAndThenOr16 (RpBase + R_PCIE_RCTL, Data16And, Data16Or);
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_RCTL after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_RCTL)));
  ///
  /// Root PCI-E Powermanagement SCI Enable
  ///
  DEBUG ((DEBUG_INFO, "Root PCI-E Powermanagement SCI Enable\n"));
  if (RootPortConfig->PcieRpCommonConfig.PmSci) {
    ///
    /// PCH BIOS Spec section 8.7.3 BIOS Enabling of Intel PCH PCI Express* PME SCI Generation
    /// Step 1
    /// Make sure that PME Interrupt Enable bit, Dxx:Fn:Reg 5Ch[3] is cleared
    ///
    PciSegmentAnd16 (RpBase + R_PCIE_RCTL, (UINT16) (~B_PCIE_RCTL_PIE));
    DEBUG ((DEBUG_VERBOSE, "R_PCIE_RCTL after clearing PIE = %x\n", PciSegmentRead32(RpBase + R_PCIE_RCTL)));
    ///
    /// Step 2
    /// Program Misc Port Config (MPC) register at PCI config space offset
    /// D8h as follows:
    /// Set Power Management SCI Enable bit, Dxx:Fn:Reg D8h[31]
    /// Clear Power Management SMI Enable bit, Dxx:Fn:Reg D8h[0]
    /// Use Byte Access to avoid RWO bit
    ///
    PciSegmentAnd8 (RpBase + R_PCIE_MPC, (UINT8) (~B_PCIE_MPC_PMME));
    PciSegmentOr8 ((RpBase + R_PCIE_MPC + 3), (UINT8) (B_PCIE_MPC_PMCE >> 24));
    DEBUG ((DEBUG_VERBOSE, "R_PCIE_MPC after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_MPC)));
  }
  if (RootPortConfig->PcieRpCommonConfig.HotPlug) {
    DEBUG ((DEBUG_INFO, "HotPlug is enabled in setup!\n"));
    ///
    /// PCH BIOS Spec section 8.8.2.1
    /// Step 1
    /// Clear following status bits, by writing 1b to them, in the Slot
    /// Status register at offset 1Ah of PCI Express Capability structure:
    /// Presence Detect Changed (bit3)
    ///
    PciSegmentAnd16 (RpBase + R_PCIE_SLSTS, B_PCIE_SLSTS_PDC);
    DEBUG ((DEBUG_VERBOSE, "Slot Status = %x\n", PciSegmentRead16(RpBase + R_PCIE_SLSTS)));
    ///
    /// Step 2
    /// Program the following bits in Slot Control register at offset 18h
    /// of PCI Express* Capability structure:
    /// Presence Detect Changed Enable (bit3) = 1b
    /// Hot Plug Interrupt Enable (bit5) = 0b
    ///
    PciSegmentAndThenOr16 (RpBase + R_PCIE_SLCTL, (UINT16) (~B_PCIE_SLCTL_HPE), B_PCIE_SLCTL_PDE);
    DEBUG ((DEBUG_VERBOSE, "Slot Control = %x\n", PciSegmentRead16(RpBase + R_PCIE_SLCTL)));
    ///
    /// Step 3
    /// Program Misc Port Config (MPC) register at PCI config space offset
    /// D8h as follows:
    /// Hot Plug SCI Enable (HPCE, bit30) = 1b
    /// Hot Plug SMI Enable (HPME, bit1) = 0b
    /// Use byte access to avoid premature locking BIT23, SRL
    ///
    PciSegmentAnd8 (RpBase + R_PCIE_MPC, (UINT8)(~B_PCIE_MPC_HPME) );
    PciSegmentOr8 (RpBase + R_PCIE_MPC + 3, B_PCIE_MPC_HPCE >> 24);
    DEBUG ((DEBUG_VERBOSE, "R_PCIE_MPC after write = %x\n", PciSegmentRead8(RpBase + R_PCIE_MPC)));
    ///
    /// PCH BIOS Spec section 8.9
    /// BIOS should mask the reporting of Completion timeout (CT) errors by setting
    /// the uncorrectable Error Mask register PCIE RP PCI offset 108h[14].
    ///
    PciSegmentOr32 (RpBase + R_PCIE_UEM, B_PCIE_UEM_CT);
    DEBUG ((DEBUG_VERBOSE, "R_PCIE_UEM after write = %x\n", PciSegmentRead32(RpBase + R_PCIE_UEM)));
  }

  ///
  /// PCH BIOS Spec Section 8.10 PCI Bus Emulation & Port80 Decode Support
  /// The I/O cycles within the 80h-8Fh range can be explicitly claimed
  /// by the PCIe RP by setting MPC.P8XDE, PCI offset D8h[26] = 1 (using byte access)
  /// BIOS must also configure the corresponding DMI registers GCS.RPR and GCS.RPRDID
  /// to enable DMI to forward the Port8x cycles to the corresponding PCIe RP
  ///

  /// @ TODO : EnablePort8xhDecode can be enabled only in one port(CPU + PCH) for a given platform so need to have a common setup option for this as well

  //if (mCpuPcieRpConfig->EnablePort8xhDecode && (PortIndex == (UINT8) mCpuPcieRpConfig->CpuPciePort8xhDecodePortIndex)) {
  //  PciSegmentOr8 (RpBase + R_PCIE_MPC + 3, (UINT8) (B_PCIE_MPC_P8XDE >> 24));
  //  PchIoPort80DecodeSet (PortIndex);
  //}

  ///
  /// Program registers to enable Atomics
  /// Program B0:Dxx:Fn + 64h [8] = 1h
  /// Program B0:Dxx:Fn + 64h [7] = 1h
  /// Program B0:Dxx:Fn + 64h [6] = 1h
  /// Program B0:Dxx:Fn + 68h [7] = 1h
  /// Program B0:Dxx:Fn + 68h [6] = 1h
  ///
  Data32And = (UINT32)~(B_PCIE_DCAP2_AC64BS | B_PCIE_DCAP2_AC32BS | B_PCIE_DCAP2_ARS);
  Data32Or = (B_PCIE_DCAP2_AC64BS | B_PCIE_DCAP2_AC32BS | B_PCIE_DCAP2_ARS);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_DCAP2, Data32And, Data32Or);
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_DCAP2 after programming Atomics = %x\n", PciSegmentRead32(RpBase + R_PCIE_DCAP2)));

  Data32And = (UINT32)~(B_PCIE_DCTL2_AEB | B_PCIE_DCTL2_ARE);
  Data32Or = (B_PCIE_DCTL2_AEB | B_PCIE_DCTL2_ARE);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_DCTL2, Data32And, Data32Or);
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_DCTL2 after programming Atomics = %x\n", PciSegmentRead32(RpBase + R_PCIE_DCTL2)));

  ///
  /// Program registers to Support 10-bit Tag.
  ///
  CpuPcieConfigure10BitTag (RpBase);

  ///
  /// Program registers for Retimer Support.
  ///
  CpuPcieConfigureRetimerSupport (RpBase);

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
  Data32And = ~(UINT32) (B_PCIE_MPC_UCEL | B_PCIE_MPC_CCEL);
  Data32Or  = (7 << B_PCIE_MPC_UCEL_OFFSET) | (4<< B_PCIE_MPC_CCEL_OFFSET);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_MPC, Data32And, Data32Or);
  DEBUG ((DEBUG_VERBOSE, "R_PCIE_MPC = %x\n", PciSegmentRead32(RpBase + R_PCIE_MPC)));


  //
  // Note : BIOS maps RpIndex = 0 to PEG060 to be consistent across all SKUs
  // Set Dxx:Fn +0xFC[26]=1 for RootPort  0
  // Set Dxx:Fn +0xFC[24]=1 for RootPort  1
  // Set Dxx:Fn +0xFC[25]=1 for RootPort  2
  // Set Dxx:Fn +0xFC[25:24]=11b for RootPort  3
  //

  Data32Or = 0;
  for (RpIndex = 0; RpIndex < GetMaxCpuPciePortNum (); RpIndex++) {
    RpBase = CpuPcieBase (RpIndex);
    switch (RpIndex) {
      case 0:
        Data32Or |= V_PCIE_STRPFUSECFG_PXIP_INTD;
        break;
      case 1:
        Data32Or |= V_PCIE_STRPFUSECFG_PXIP_INTA;
        break;
      case 2:
        Data32Or |= V_PCIE_STRPFUSECFG_PXIP_INTB;
        break;
      case 3:
        Data32Or |= V_PCIE_STRPFUSECFG_PXIP_INTC;
        break;
      default:
        ASSERT (FALSE);
        return;
    }
  }
  PciSegmentAndThenOr32 (RpBase + R_PCIE_STRPFUSECFG, (UINT32) ~B_PCIE_STRPFUSECFG_PXIP_MASK, Data32Or);
}

/**
  Perform Initialization of the Downstream Root Ports.

  @param[in] SiPolicy             The SI Policy PPI
**/
VOID
CpuPcieRpInit (
  IN CONST SI_POLICY_PPI     *SiPolicy
  )
{
  CPU_PCIE_RP_PREMEM_CONFIG  *CpuPcieRpPreMemConfig;
  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi;
  EFI_STATUS                 Status;
  UINT8                      RpIndex;
  UINT64                     RpBase;
  UINTN                      RpDevice;
  UINTN                      RpFunction;
  UINT8                      MaxCpuPciePortNum;
  UINT32                     RpDisableMask;
  UINT32                     RpClkreqMask;
  UINT32                     Timer;
  UINT32                     DetectTimeoutUs;
  BOOLEAN                    Gen4DeviceFound[CPU_PCIE_MAX_ROOT_PORTS];
  BOOLEAN                    KeepPortVisible;
  UINT8                      TempPciBusMin;
  UINT8                      TempPciBusMax;
  UINT32                     Data32Or;
  UINT32                     Data32And;
  SA_PEG_HOB                 *SaPegHob;

  DEBUG ((DEBUG_INFO, "CPU PcieRpInit() Start\n"));

  TempPciBusMin = PcdGet8 (PcdSiliconInitTempPciBusMin);
  TempPciBusMax = PcdGet8 (PcdSiliconInitTempPciBusMax);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gCpuPcieRpConfigGuid, (VOID *) &mCpuPcieRpConfig);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuPcieRpPrememConfigGuid, (VOID *) &CpuPcieRpPreMemConfig);
  ASSERT_EFI_ERROR(Status);
  DEBUG_CODE_BEGIN ();
  CpuPciePolicySanityCheck (mCpuPcieRpConfig);
  DEBUG_CODE_END ();

  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  if (SaPegHob == NULL) {
    DEBUG ((DEBUG_ERROR, "ERROR: SaPegHob not found so return from post mem RpInit\n"));
    ASSERT (SaPegHob != NULL);
    return;
  }
  if (SaPegHob->RpEnMaskFromDevEn == 0) {
    DEBUG ((DEBUG_ERROR, "All CPU PCIe root ports are fused off!!\n"));
    return;
  } else if (SaPegHob->RpEnabledMask == 0) {
    DEBUG ((DEBUG_ERROR, "All CPU PCIe root ports are disabled!!\n"));
  }

  Timer            = 0;
  MaxCpuPciePortNum = GetMaxCpuPciePortNum ();
  RpDisableMask    = ~(SaPegHob->RpEnabledMask);
  RpClkreqMask     = 0;

  DEBUG ((DEBUG_INFO, "----    RpIndex mapping    ----\n"));
  DEBUG ((DEBUG_INFO, "---- RpIndex = 0 ; PortId = 1 => PEG060 ----\n"));

  DEBUG ((DEBUG_INFO, "MaxCpuPciePortNum = %x\n", MaxCpuPciePortNum));

  if (GetPcieImrPortLocation () == ImrRpLocationSa) {
    CpuPcieEnablePcieImr (GetPcieImrPortNumber ());
  }

  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    RpBase = CpuPcieBase (RpIndex);
    DEBUG ((DEBUG_INFO, "**** RpIndex = %x ****\n", RpIndex));
    //
    // Enable CLKREQ# regardless of port being available/enabled to allow clock gating.
    //
    if (IsClkReqAssigned (PchClockUsageCpuPcie0 + RpIndex)) {
      DEBUG ((DEBUG_INFO, "ClkReqAssigned, set RpClkreqMask\n"));
      RpClkreqMask |= (BIT0 << RpIndex);
    }

    ///
    /// Set the Slot Implemented Bit.
    /// The System BIOS must initialize the "Slot Implemented" bit of the PCI Express* Capabilities Register,
    /// XCAP Dxx:Fn:42h[8] of each available and enabled downstream root port.
    /// Ports with hotplug capability must have SI bit set
    /// The register is write-once so must be written even if we're not going to set SI, in order to lock it.
    ///
    /// This must happen before code reads PresenceDetectState, because PDS is invalid unless SI is set
    ///
    if (mCpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.SlotImplemented || mCpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.HotPlug) {
      PciSegmentOr16 (RpBase + R_PCIE_XCAP, B_PCIE_XCAP_SI);
    } else {
      PciSegmentAnd16 (RpBase + R_PCIE_XCAP, (UINT16)(~B_PCIE_XCAP_SI));
    }
    if ((PciSegmentRead16 (RpBase + R_PCIE_XCAP)) & B_PCIE_XCAP_SI){
      DEBUG ((DEBUG_INFO, "Slot implemented bit is set!\n"));
    }
    ///
    /// For non-hotplug ports disable the port if there is no device present.
    ///
    DetectTimeoutUs = mCpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.DetectTimeoutMs * 1000;
    if (IsCpuPcieDevicePresent (RpBase, DetectTimeoutUs, &Timer)) {
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
      if (!CpuPcieDetectClkreq (RpIndex, mCpuPcieRpConfig)) {
        DEBUG ((DEBUG_INFO, "CLKREQ is not connected, clear RpClkreqMask!\n"));
        RpClkreqMask &= ~(BIT0 << RpIndex);
      }
    } else {
      if (mCpuPcieRpConfig->RootPort[RpIndex].PcieRpCommonConfig.HotPlug == FALSE) {
        DEBUG ((DEBUG_INFO, "Port %d neither has Endpoint connected not HotPlug enabled!\n", RpIndex + 1));
        DEBUG ((DEBUG_INFO, "Set RpDisableMask for Port %d\n", RpIndex + 1));
        RpDisableMask |= (BIT0 << RpIndex);
      }
    }
  }
  if (SaPegHob->RpEnMaskFromDevEn != 0) {
    DEBUG ((DEBUG_INFO, "Configure power management applicable to all port including disabled ports!\n"));
    for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
     ///
     /// Configure power management applicable to all port including disabled ports.
     ///
      if (RpIndex != 3) {
        ///
        /// TrunkClockGateEn depends on each of the controller ports supporting CLKREQ# or being disabled.
        /// power management done only on RP controllers.
        ///
        CpuPcieConfigureControllerBasedPowerManagement (
          RpIndex,
          (((RpClkreqMask | RpDisableMask) & (0xFu << RpIndex)) == (0xFu << RpIndex)),
          ((mCpuPcieRpConfig->DisableRootPortClockGating) ? TRUE:FALSE),
          ((mCpuPcieRpConfig->DisableRootPortPowerGating) ? TRUE:FALSE)
        );
      }
      ///
      /// PhyLanePgEnable depends on the port supporting CLKREQ# or being disabled.
      ///
      CpuPcieConfigurePortBasedPowerManagement (
        RpIndex,
        (((RpClkreqMask | RpDisableMask) & (BIT0 << RpIndex)) != 0),
        ((mCpuPcieRpConfig->DisableRootPortClockGating) ? TRUE:FALSE),
        ((mCpuPcieRpConfig->DisableRootPortPowerGating) ? TRUE:FALSE)
      );
    }
  }
  //
  // Lock Fia Configuration
  //
  if (!IsSimicsEnvironment()) {
    if (!mCpuPcieRpConfig->SkipCpuFiaProgramming) {
      CpuFiaFinalizeConfigurationAndLock();
    }
  }
  //
  // Wait for all ports with PresenceDetect=1 to form a link
  // Having an active link is necessary to access and configure the endpoint
  // We cannot use results of IsCpuPcieDevicePresent() because it checks PDS only and may include
  // PCIe cards that never form a link, such as compliance load boards.
  //
  CpuPcieWaitForLinkActive (MaxCpuPciePortNum, RpDisableMask);
  // For each controller set Initialize Transaction Layer Receiver Control on Link Down
  // and Initialize Link Layer Receiver Control on Link Down.
  // Use sideband access in case 1st port of a controller is disabled
  ///
  /// Set 338h[29] to 0b for Initialize Transaction Layer Receiver Control on Link Down.
  /// Set 338h[28] to 0b for Initialize Link Layer Receiver Control on Link Down.
  /// Set 338h[21] to 1b for RTD3 Present Detect State Policy.
  ///
  Data32And = (UINT32)~(B_PCIE_PCIEALC_ITLRCLD | B_PCIE_PCIEALC_ILLRCLD);
  Data32Or = (UINT32) (B_PCIE_PCIEALC_RTD3PDSP);

  for (RpIndex = 0; RpIndex<MaxCpuPciePortNum && RpIndex<3; ++RpIndex) {
    RpBase = CpuPcieBase (RpIndex);
    PciSegmentAndThenOr32 (RpBase +  R_PCIE_PCIEALC, Data32And, Data32Or);
  }
  //
  // PTM programming happens per controller
  // BWG recommended values for SIP16 TGL Brooks controller are programmed here
  //
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; ++RpIndex) {
    RpBase = CpuPcieBase(RpIndex);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC1, 0x0, 0x321A3D26);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC2, 0x0, 0x21172D13);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC3, 0x0, 0x190C1B10);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC4, 0x0, 0x26162D1D);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC5, (UINT32)0xFFFF0000, 0x00002413);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC9, 0x0, 0x301C372F);
    PciSegmentAndThenOr32 (RpBase +  R_SA_PCIE_CFG_PTMPSDC10, (UINT32)0xFFFF0000, 0x00002E18);
    PciSegmentAndThenOr32 (RpBase +  R_PCIE_PTMECFG, (UINT32)0xFFE00000, 0x00040250);
    PciSegmentAndThenOr32 (RpBase +  R_PCIE_PTMCAPR, (UINT32)~(B_PCIE_PTMCAPR_PTMRC | B_PCIE_PTMCAPR_PTMRSPC | B_PCIE_PTMCAPR_PTMREQC), 0x00000007);
    PciSegmentAndThenOr32 (RpBase +  R_PCIE_PTMCTLR, (UINT32)~(B_PCIE_PTMCTLR_RS), 0x00000002);
    PciSegmentAndThenOr32 (RpBase +  R_PCIE_ACRG3, (UINT32)~(B_PCIE_ACRG3_PPTMTMUCF_MASK | B_PCIE_ACRG3_PPTMTMUCFE), 0x00000000);
  }
  RpBase = CpuPcieBase(RpIndex);
  ///
  /// Set ECh[13] to 1b for Initialize Link Layer Receiver Control on Link Down.
  ///
  PciSegmentAndThenOr32 (RpBase + R_PCIE_DC, (UINT32)~B_PCIE_DC_COM, (UINT32)B_PCIE_DC_COM);
  ///
  /// Set 3BC[3] to 1b for DPC Trigger SCI Enable.
  /// Set 3BC[2] to 1b for DPC Trigger SMI Enable.
  /// Set 3BC[1] to 1b for RP PIO Error SCI Enable.
  /// Set 3BC[0] to 1b for RP PIO Error SMI Enable.
  ///
  Data32And = (UINT32)~(B_PCIE_DPCECTL_RPPIOERRSMIEN | B_PCIE_DPCECTL_RPPIOERRSCIEN | B_PCIE_DPCECTL_DPCTSMIEN | B_PCIE_DPCECTL_DPCTSCIEN);
  Data32Or = (UINT32)(B_PCIE_DPCECTL_RPPIOERRSMIEN | B_PCIE_DPCECTL_RPPIOERRSCIEN | B_PCIE_DPCECTL_DPCTSMIEN | B_PCIE_DPCECTL_DPCTSCIEN);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_DPCECTL, Data32And, Data32Or);

  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; ++RpIndex) {
    if (RpDisableMask & (BIT0 << RpIndex)) {
      KeepPortVisible = CpuPcieIsPortForceVisible (RpIndex, RpDisableMask, mCpuPcieRpConfig);
      DEBUG ((DEBUG_INFO, "Disable mask is set for Portid %d\n", RpIndex + 1));
      DEBUG ((DEBUG_INFO, "KeepPortVisible = %x\n", KeepPortVisible));
      DisableCpuPcieRootPort (RpIndex, KeepPortVisible);
    } else {
      DEBUG ((DEBUG_INFO, "Call InitCpuPcieSingleRootPort for Portid %d\n", RpIndex + 1));
      InitCpuPcieSingleRootPort (
        RpIndex,
        SiPolicy,
        SiPreMemPolicyPpi,
        TempPciBusMin,
        &Gen4DeviceFound[RpIndex],
        CpuPcieRpPreMemConfig
        );
      ///
      /// Initialize downstream devices
      ///
      DEBUG ((DEBUG_INFO, "Initialize downstream devices\n"));
      GetCpuPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
      RootportDownstreamConfiguration (
        SA_SEG_NUM,
        SA_MC_BUS,
        (UINT8) RpDevice,
        (UINT8) RpFunction,
        TempPciBusMin,
        TempPciBusMax,
        EnumCpuPcie
        );
    }
  }
  //
  // Rx margin programming as per BWG
  //
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; ++RpIndex) {
    /// Program R_PCIE_RXMC1[C90]
    /// Set C90[26:31] MSRVS to 0x1F
    /// Set C90[20:25] MSRTS to 0x3F
    /// Set C90[13:14] TMSLOP to 0x1
    /// Set C90[11:12] VMSLOP to 0x1
    /// Set C90[4:8] MMNOLS to 0x1
    ///
    Data32And = (UINT32) ~(B_PCIE_RXMC1_MMNOLS_MASK | B_PCIE_RXMC1_VMSLOP_MASK | B_PCIE_RXMC1_TMSLOP_MASK | B_PCIE_RXMC1_MSRTS_MASK | B_PCIE_RXMC1_MSRVS_MASK);
    Data32Or = ((V_PCIE_RXMC1_MMNOLS << B_PCIE_RXMC1_MMNOLS_OFFSET) | (V_PCIE_RXMC1_VMSLOP << B_PCIE_RXMC1_VMSLOP_OFFSET) | (V_PCIE_RXMC1_TMSLOP << B_PCIE_RXMC1_TMSLOP_OFFSET) | (V_PCIE_RXMC1_MSRTS << B_PCIE_RXMC1_MSRTS_OFFSET) | (V_PCIE_RXMC1_MSRVS << B_PCIE_RXMC1_MSRVS_OFFSET));
    CpuPcieRpSbiAndThenOr32 (RpIndex, R_PCIE_RXMC1, Data32And, Data32Or);
    ///
    /// Program R_PCIE_RXMC2[C94]
    /// Set C94[19:24] MNOTSS to 0x20
    ///
    Data32And = (UINT32) ~(B_PCIE_RXMC2_MNOTSS_MASK);
    Data32Or = (V_PCIE_RXMC2_MNOTSS << B_PCIE_RXMC2_MNOTSS_OFFSET);
    CpuPcieRpSbiAndThenOr32 (RpIndex, R_PCIE_RXMC2, Data32And, Data32Or);
  }
  //
  // Program the root port target link speed.
  //
  Status = CpuPcieRpSpeedChange();
  ASSERT_EFI_ERROR(Status);
  //
  // We should not wait for HwEq done bit to get set because compliance load boards never form a link and does not complete HwEq flow
  //
  if (!mCpuPcieRpConfig->PcieCommonConfig.ComplianceTestMode){
    if (((CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] >= 3) || (CpuPcieRpPreMemConfig->PcieSpeed[RpIndex] == 0)) && ((RpDisableMask & BIT0) == 0)) {
      ///
      /// check for hardware equalization done bit set in parallel for all rootports to optimize the wait time
      ///
      CpuPcieWaitForHwEqDone();
    }
  }
  //
  // Read the DEKEL FW version and populate in HOB to be printed in BIOS setup
  //
  if ((SaPegHob != NULL) && !IsSimicsEnvironment()) {
    SaPegHob->DekelFwVersion = GetDekelFwVersion(CPU_SB_PID_DEKEL_IO4);
    DEBUG ((DEBUG_INFO, "Dekel FW version : %x\n", SaPegHob->DekelFwVersion));
  }

  //
  // Lock SRL bits after function remapping - lock it for all root ports
  //
  if (mCpuPcieRpConfig->SetSecuredRegisterLock){
    DEBUG((DEBUG_INFO, "Lock the registers\n"));
    CpuPcieRpSetSecuredRegisterLock();
  }
  DEBUG ((DEBUG_INFO, "CPU PcieRpInit() End\n"));
}
