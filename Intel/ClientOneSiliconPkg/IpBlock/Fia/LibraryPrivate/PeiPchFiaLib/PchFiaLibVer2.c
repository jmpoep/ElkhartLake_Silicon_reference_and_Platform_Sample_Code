/** @file
  This file contains TGL specific FIA routines

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include "PchFiaLibInternal.h"
#include <Register/PchPcrRegs.h>

#include "PchFia15.h"

/**
  Returns the FIA Instance

  @return FIA Instance
**/
FIA_INSTANCE
FiaGetInstance (
  VOID
  )
{
  FIA_INSTANCE FiaInst;
  FiaInst.SbPortId = PID_FIA;
  return FiaInst;
}

/**
  Returns a FIA lane number for a given SATA port.

  @param[in]  SataCtrlIndex  SATA controller index
  @param[in]  SataPortIndex  SATA port index
  @param[out] LaneNum        Pointer to the variable that stores lane number.
                             The output value is only valid if this function returns TRUE.

  @return TRUE if given SATA port owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetSataLaneNum (
  IN  UINT32  SataCtrlIndex,
  IN  UINT32  SataPortIndex,
  OUT UINT8   *LaneNum
  )
{
  FIA_INSTANCE FiaInst;
  FiaInst = FiaGetInstance ();
  if (IsPchLp ()) {
    switch (SataPortIndex) {
      case 0:
        *LaneNum = 10;
        break;
      case 1:
        *LaneNum = 11;
        break;
      default:
        ASSERT (FALSE);
        return FALSE;
    }
  } else {
    ASSERT (IsPchH ());
    switch (SataPortIndex) {
      case 0:
        if (PchFiaGetLaneOwner (FiaInst, 24) == PchFiaOwnerSata) {
          *LaneNum = 24;
          return TRUE;
        } else if (PchFiaGetLaneOwner (FiaInst, 26) == PchFiaOwnerSata) {
          *LaneNum = 26;
          return TRUE;
        }
        return FALSE;
      case 1:
        if (PchFiaGetLaneOwner (FiaInst, 25) == PchFiaOwnerSata) {
          *LaneNum = 25;
          return TRUE;
        } else if (PchFiaGetLaneOwner (FiaInst, 27) == PchFiaOwnerSata) {
          *LaneNum = 27;
          return TRUE;
        }
        return FALSE;
      case 2:
        *LaneNum = 28;
        break;
      case 3:
        *LaneNum = 29;
        break;
      case 4:
        *LaneNum = 30;
        break;
      case 5:
        *LaneNum = 31;
        break;
      case 6:
        *LaneNum = 32;
        break;
      case 7:
        *LaneNum = 33;
        break;
      default:
        ASSERT (FALSE);
        return FALSE;
    }
  }

  return (PchFiaGetLaneOwner (FiaInst, *LaneNum) == PchFiaOwnerSata);
}

/**
  Returns GbE over PCIe port number when GbE is enabled

  @return PCIe root port number(1- based), 0 if GbE over PCIe is disabled
**/
UINT32
PchFiaGetGbePortNumber (
  VOID
  )
{
  FIA_INSTANCE FiaInst;
  FiaInst = FiaGetInstance ();
  if (IsPchLp ()) {
    if (PchFiaGetLaneOwner (FiaInst, 6) == PchFiaOwnerGbe)  return 7;
    if (PchFiaGetLaneOwner (FiaInst, 7) == PchFiaOwnerGbe)  return 8;
    if (PchFiaGetLaneOwner (FiaInst, 8) == PchFiaOwnerGbe)  return 9;
  } else {
    ASSERT (IsPchH ());
    if (PchFiaGetLaneOwner (FiaInst, 10) == PchFiaOwnerGbe) return 5;
    if (PchFiaGetLaneOwner (FiaInst, 22) == PchFiaOwnerGbe) return 9;
    if (PchFiaGetLaneOwner (FiaInst, 25) == PchFiaOwnerGbe) return 12;
    if (PchFiaGetLaneOwner (FiaInst, 26) == PchFiaOwnerGbe) return 13;
  }

  DEBUG ((DEBUG_INFO, "No FIA lanes assigned as GbE\n"));
  return 0;
}

/**
  Checks if given lane is DMI

  @param[in]  FiaLaneNum  Fia lane num

  @return TRUE if given lane is DMI, FALSE otherwise
**/
BOOLEAN
PchFiaIsLaneDmi (
  IN UINT8  FiaLaneNum
  )
{
  if (IsPchH () && (FiaLaneNum >= 14) && (FiaLaneNum <= 21)) {
    return TRUE;
  }

  return FALSE;
}

/**
  Returns a FIA lane number for a given PCIe lane.

  @param[in]  PciePhysicalLane  Index of the PCIe lane
  @param[out] LaneNum           Pointer to the variable that stores lane number.
                                The output value is only valid if this function returns TRUE.

  @return TRUE if given PciePhysicalLane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetPcieLaneNum (
  IN  UINT32  PciePhysicalLane,
  OUT UINT8   *LaneNum
  )
{
  static UINT8 FirstLaneH[]  = { 6, 10, 22, 26, 30, 34 };
  UINT32  ControllerIndex;
  UINT32  ControllerPhyLane;

  if (IsPchLp ()) {
    *LaneNum = (UINT8) PciePhysicalLane;
  } else {
    ASSERT (IsPchH ());
    ControllerIndex = PciePhysicalLane / 4;
    ControllerPhyLane = PciePhysicalLane % 4;
    *LaneNum = FirstLaneH[ControllerIndex] + (UINT8) ControllerPhyLane;
  }

  return (PchFiaGetLaneOwner (FiaGetInstance (), *LaneNum) == PchFiaOwnerPcie);
}

/**
  Returns a FIA lane number for a given USB3 port.
  This function assumes that for ICP-Lp and ICP-H USB3 ports to FIA lane mapping is 1:1

  @param[in]  Usb3PortIndex  USB3 port index
  @param[out] LaneNum        Pointer to the variable that stores lane number.
                             The output value is only valid if this function returns TRUE.

  @return TRUE if given USB3 port owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetUsb3LaneNum (
  IN  UINT32  Usb3PortIndex,
  OUT UINT8   *LaneNum
  )
{
  ASSERT (Usb3PortIndex < GetPchXhciMaxUsb3PortNum ());
  *LaneNum = (UINT8) Usb3PortIndex;
  return (PchFiaGetLaneOwner (FiaGetInstance (), *LaneNum) == PchFiaOwnerUsb3);
}

/**
  Returns a FIA lane number for a given UFS lane.

  @param[in]  UfsControllerIndex  Index of the UFS controller
  @param[in]  UfsLaneIndex        Index of the UFS lane on given controller
  @param[out] LaneNum             Optional. Pointer to the variable that stores lane number.
                                  The output value is only valid if this function returns TRUE.

 @return TRUE if given UFS lane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetUfsLaneNum (
  IN  UINT32  UfsControllerIndex,
  IN  UINT32  UfsLaneIndex,
  OUT UINT8   *LaneNum
  )
{
  UINT8 LaneNumLocal;

  if (IsPchLp ()) {
    switch (UfsControllerIndex) {
      case 0:
        switch (UfsLaneIndex) {
          case 0:
            LaneNumLocal = 6;
            break;
          case 1:
            LaneNumLocal = 7;
            break;
          default:
            ASSERT (FALSE);
            return FALSE;
        };
        break;
      case 1:
        switch (UfsLaneIndex) {
          case 0:
            LaneNumLocal = 8;
            break;
          case 1:
            LaneNumLocal = 9;
            break;
          default:
            ASSERT (FALSE);
            return FALSE;
        };
        break;
      default:
        ASSERT (FALSE);
        return FALSE;
    }
  } else if (IsPchH ()) {
    switch (UfsControllerIndex) {
      case 0:
        switch (UfsLaneIndex) {
          case 0:
            LaneNumLocal = 30;
            break;
          case 1:
            LaneNumLocal = 31;
            break;
          default:
            ASSERT (FALSE);
            return FALSE;
        };
        break;
      case 1:
        switch (UfsLaneIndex) {
          case 0:
            LaneNumLocal = 32;
            break;
          case 1:
            LaneNumLocal = 33;
            break;
          default:
            ASSERT (FALSE);
            return FALSE;
        };
        break;
      default:
        ASSERT (FALSE);
        return FALSE;
    }
  } else {
    ASSERT (FALSE);
    return FALSE;
  }

  if (LaneNum != NULL) {
    *LaneNum = LaneNumLocal;
  }
  return (PchFiaGetLaneOwner (FiaGetInstance (), LaneNumLocal) == PchFiaOwnerUfs);
}

/**
  Returns number of FIA lanes

  @return Number of FIA lanes
**/
UINT8
PchFiaGetMaxLaneNum (
  VOID
  )
{
  if (IsPchLp ()) {
    return 12;
  } else {
    ASSERT (IsPchH ());
    return 38;
  }
}

/**
  Return FIA lane owner.

  @param[in] FiaInst  FIA Instance
  @param[in] LaneNum  FIA lane number

  @return  Code of the FIA lane owner, PchFiaOwnerInvalid if lane number wasn't valid
**/
PCH_FIA_LANE_OWNER
PchFiaGetLaneOwner (
  IN  FIA_INSTANCE FiaInst,
  IN  UINT8        LaneNum
  )
{
  if (LaneNum >= PchFiaGetMaxLaneNum ()) {
    ASSERT (FALSE);
    return PchFiaOwnerInvalid;
  }
  return PchFia15GetLaneOwner (FiaInst, LaneNum);
}

/**
  Print FIA LOS registers.
**/
VOID
PchFiaPrintLosRegisters (
  VOID
  )
{
  PchFia15PrintLosRegisters (FiaGetInstance ());
}

/**
  Assigns CLKREQ# to PCH PCIe ports

  @param[in] ClkReqMap      Mapping between PCH PCIe ports and CLKREQ#
  @param[in] ClkReqMapSize  Size of the map
**/
VOID
PchFiaAssignPchPciePortsClkReq (
  IN UINT8  *ClkReqMap,
  IN UINT8  ClkReqMapSize
  )
{
  PchFia15AssignPchPciePortsClkReq (FiaGetInstance (), ClkReqMap, ClkReqMapSize);
}

/**
  Assigns CLKREQ# to CPU PCIe ports

  @param[in] RpIndex        CPU PCIe root port index
  @param[in] ClkReqNum      Number of the CLKREQ
**/
VOID
PchFiaAssignCpuPciePortClkReq (
  IN UINT32  RpIndex,
  IN UINT8   ClkReqNum
  )
{
  PchFia15AssignCpuPciePortClkReq (FiaGetInstance (), RpIndex, ClkReqNum);
}

/**
Enable CLKREQ# to CPU PCIe ports

@param[in] RpIndex        CPU PCIe root port index
@param[in] ClkReqNum      Number of the CLKREQ
**/
VOID
PchFiaEnableCpuPciePortClkReq (
  IN UINT32  RpIndex,
  IN UINT8   ClkReqNum
)
{
  DEBUG ((DEBUG_INFO, "PchFiaEnableCpuPciePortClkReq Entry\n"));
  PchFia15EnableCpuPciePortClkReq (FiaGetInstance(), RpIndex, ClkReqNum);
  DEBUG ((DEBUG_INFO, "PchFiaEnableCpuPciePortClkReq Exit\n"));
}

/**
  Return the status of the CLKREQ state received with VW msg.

  @param[in] RpIndex  CPU PCIe index.

  @return Status of the CLKREQ.
**/
BOOLEAN
PchFiaGetCpuPcieClkReqStatus (
  IN UINT32  RpIndex
  )
{
  return PchFia15GetCpuPcieClkReqStatus (FiaGetInstance (), RpIndex);
}

/**
  Assigns CLKREQ# to GbE

  @param[in]  ClkReqNum  CLKREQ# number
**/
VOID
PchFiaAssignGbeClkReq (
  IN UINT8  ClkReqNum
  )
{
  PchFia15AssignGbeClkReq (FiaGetInstance (), ClkReqNum);
}

/**
  Configures lower bound of delay between ClkReq assertion and driving RefClk.
**/
VOID
PchFiaSetClockOutputDelay (
  VOID
  )
{
  PchFia15SetClockOutputDelay (FiaGetInstance ());
}

/**
  Performs FIA programming required at the end of configuration and locks lockable FIA registers
**/
VOID
PchFiaFinalizeConfigurationAndLock (
  IN SI_POLICY_PPI  *SiPolicy
  )
{
  FIA_INSTANCE FiaInst;
  FiaInst = FiaGetInstance ();
  //
  // Program PCR[FIA] + 20h bit [13:11] to 001, bit [30:28] to [000]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_PLLCTL,
    (UINT32) ~(B_PCH_FIA_PCR_PLLCTL_CL0PLLWAIT | B_PCH_FIA_PCR_PLLCTL_PLLCLKVADT),
    (UINT32) (1 << N_PCH_FIA_PCR_PLLCTL_CL0PLLWAIT)
    );

  //
  // Program PCR[FIA] + 18h bit [17:16, 1:0] to [00, 00]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_CLSDM,
    (UINT32) ~(B_PCH_FIA_PCR_CLSDM_DMIIPSLSD | B_PCH_FIA_PCR_CLSDM_PCIEGBEIPSLSD),
    0
    );

  //
  // Set PCR[FIA] + 0h bit [17, 16, 15] to [1, 1, 1]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_CC,
    ~0u,
    B_PCH_FIA_PCR_CC_PTOCGE | B_PCH_FIA_PCR_CC_OSCDCGE | B_PCH_FIA_PCR_CC_SCPTCGE
    );

  //
  // Set PCR[FIA] + 40h bit [3] to [1]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_PMC,
    ~0u,
    B_PCH_FIA_PCR_PMC_PRDPGE
    );

  //
  // Set PCR[FIA] + 48h bit [0] to [0]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_PGCUC,
    (UINT32) ~(B_PCH_FIA_PCR_PGCUC_ACC_CLKGATE_DISABLED),
    0
    );

  //
  // Set PCR[FIA] + 50h bit [0] to [0]
  //
  PchPcrAndThenOr32 (
    FiaInst.SbPortId,
    R_PCH_FIA_PCR_PGCUCSOC,
    (UINT32) ~(B_PCH_FIA_PCR_PGCUCSOC_ACC_CLKGATE_DISABLED),
    0
    );
}
