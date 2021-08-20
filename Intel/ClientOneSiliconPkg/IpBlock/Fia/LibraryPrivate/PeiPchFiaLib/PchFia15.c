/** @file
  This file contains routines used to communicate with FIA 15.0 hardware

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Library/GpioPrivateLib.h>

#include "PchFiaLibInternal.h"
#include "PchFia15.h"

/**
  Get FIA lane owner

  @param[in] FiaInst  FIA Instance
  @param[in] LaneNum  lane number

  @retval PCH_FIA_LANE_OWNER  FIA lane owner
**/
PCH_FIA_LANE_OWNER
PchFia15GetLaneOwner (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        LaneNum
  )
{
  UINT32  LosValue;
  UINT32  LosRegisterIndex;

  LosRegisterIndex = LaneNum / 8;
  //
  // Only 5 LOS registers in FIA 15.0
  //
  if (LosRegisterIndex > 4) {
    ASSERT (FALSE);
    return PchFiaOwnerInvalid;
  }

  LosValue = PchPcrRead32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_LOS1_REG_BASE + (4 * LosRegisterIndex));
  //
  // Invalid LOS register value means that we are in post boot SAI.
  // This code should not be called at this point so ASSERT.
  //
  if (LosValue == 0xFFFFFFFF) {
    ASSERT (FALSE);
    return PchFiaOwnerInvalid;
  }

  return PchFiaDecodeOwner (LosValue >> (4 * (LaneNum % 8)) & B_PCH_FIA_PCR_L0O, LaneNum);
}

/**
  Print FIA LOS registers.

  @param[in] FiaInst  FIA Instance
**/
VOID
PchFia15PrintLosRegisters (
  IN FIA_INSTANCE FiaInst
  )
{
  UINT32  Index;
  UINT32  MaxLosRegister;

  MaxLosRegister = ((PchFiaGetMaxLaneNum () - 1) / 8) + 1;
  for (Index = 0; Index < MaxLosRegister; Index++) {
    DEBUG ((DEBUG_INFO, "FIA LOS%d = 0x%08X\n", Index, PchPcrRead32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_LOS1_REG_BASE + (4 * Index))));
  }
}

/**
  Assigns CLKREQ# to PCH PCIe ports

  @param[in] FiaInst        FIA Instance
  @param[in] ClkReqMap      Mapping between PCH PCIe ports and CLKREQ#
  @param[in] ClkReqMapSize  Size of the map
**/
VOID
PchFia15AssignPchPciePortsClkReq (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        *ClkReqMap,
  IN UINT8        ClkReqMapSize
  )
{
  UINT32  RegisterValue;
  UINT8   RegisterIndex;
  UINT8   PortIndex;
  UINT8   FirstClkReqIndex;
  UINT8   LastClkReqIndex;
  UINT8   ClkReqPosition;

  ASSERT (ClkReqMapSize <= PCH_FIA_15_MAX_PCH_PCIE_CLKREQ);

  for (RegisterIndex = 0; RegisterIndex < PCH_FIA_15_MAX_PDRCRM; RegisterIndex++) {

    RegisterValue = 0;
    FirstClkReqIndex = RegisterIndex * S_PCH_FIA_15_PCR_DRCRM_FIELDS_PER_REG;
    LastClkReqIndex = FirstClkReqIndex + S_PCH_FIA_15_PCR_DRCRM_FIELDS_PER_REG;

    for (PortIndex = FirstClkReqIndex; (PortIndex < LastClkReqIndex) && (PortIndex < PCH_FIA_15_MAX_PCH_PCIE_CLKREQ); PortIndex++) {
      if ((PortIndex < ClkReqMapSize) && (ClkReqMap[PortIndex] != PCH_FIA_NO_CLKREQ)) {
        ClkReqPosition = S_PCH_FIA_15_PCR_DRCRM_BITS_PER_FIELD * (PortIndex % S_PCH_FIA_15_PCR_DRCRM_FIELDS_PER_REG);
        RegisterValue |= ClkReqMap[PortIndex] << ClkReqPosition;
      }
    }

    PchPcrWrite32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_PDRCRM1 + (RegisterIndex * 4), RegisterValue);
  }

  RegisterIndex = 0;
  RegisterValue = 0;
  for (PortIndex = 0; PortIndex < PCH_FIA_15_MAX_PCH_PCIE_CLKREQ; PortIndex++) {

    if (PortIndex < ClkReqMapSize && ClkReqMap[PortIndex] != PCH_FIA_NO_CLKREQ) {
      RegisterValue |= 1 << (PortIndex % 32);
    }

    if ((PortIndex % 32 == 31) || (PortIndex == PCH_FIA_15_MAX_PCH_PCIE_CLKREQ - 1)) {
      PchPcrWrite32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_PDRCRE1 + (RegisterIndex * 4), RegisterValue);
      RegisterValue = 0;
      RegisterIndex++;
    }
  }
}

/**
  Assigns CLKREQ# to CPU PCIe ports

  @param[in] FiaInst        FIA Instance
  @param[in] RpIndex        CPU PCIe root port index, 0-based
  @param[in] ClkReqNum      Number of the CLKREQ
**/
VOID
PchFia15AssignCpuPciePortClkReq (
  IN FIA_INSTANCE FiaInst,
  IN UINT32       RpIndex,
  IN UINT8        ClkReqNum
  )
{
  UINT32      ClkReqPosition;
  EFI_STATUS  Status;

  ASSERT (RpIndex < PCH_FIA_15_MAX_CPU_PCIE_CLKREQ);

  ClkReqPosition = S_PCH_FIA_15_PCR_DRCRM_BITS_PER_FIELD * RpIndex;

  if (ClkReqNum != PCH_FIA_NO_CLKREQ) {
    PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRM, ~(UINT32) (0x1F << ClkReqPosition), ClkReqNum << ClkReqPosition);
    PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRES, ~(UINT32) 0x0, BIT0 << RpIndex);
    Status = GpioEnableCpuPcieVwClkReqMsgBus (RpIndex);
    ASSERT_EFI_ERROR (Status);
  } else {
    PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRES, ~(UINT32) (BIT0 << RpIndex), 0x0);
  }
}

/**
Assigns CLKREQ# to CPU PCIe ports

@param[in] FiaInst        FIA Instance
@param[in] RpIndex        CPU PCIe root port index, 0-based
@param[in] ClkReqNum      Number of the CLKREQ
**/
VOID
PchFia15EnableCpuPciePortClkReq(
IN FIA_INSTANCE FiaInst,
IN UINT32       RpIndex,
IN UINT8        ClkReqNum
)
{
  DEBUG((DEBUG_INFO, "PchFia15EnableCpuPciePortClkReq Entry\n"));
  ASSERT(RpIndex < PCH_FIA_15_MAX_CPU_PCIE_CLKREQ);
  if (ClkReqNum != PCH_FIA_NO_CLKREQ) {
    PchPcrAndThenOr32(FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRES, ~(UINT32)0x0, BIT0 << RpIndex);// Use the BIT name to clear the bitmap
  }
  else {
    PchPcrAndThenOr32(FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRES, ~(UINT32)(BIT0 << RpIndex), 0x0);
  }

  DEBUG((DEBUG_INFO, "PchFia15EnableCpuPciePortClkReq Exit\n"));
}


/**
  Get the status of the CLKREQ

  @param[in] FiaInst  FIA Instance
  @param[in] Rpindex  CPU PCIe index

  @return Status of the CLKREQ signal received by virtual wire
**/
BOOLEAN
PchFia15GetCpuPcieClkReqStatus (
  IN FIA_INSTANCE FiaInst,
  IN UINT32       RpIndex
  )
{
  UINT32  ClkReqStatus;

  ASSERT (RpIndex < PCH_FIA_15_MAX_CPU_PCIE_CLKREQ);

  ClkReqStatus = PchPcrRead32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_CPDRCRES);
  return !!(ClkReqStatus & (B_PCH_FIA_15_PCR_CP0TXCKRQS << RpIndex));
}

/**
  Assigns CLKREQ# to GbE

  @param[in] FiaInst    FIA Instance
  @param[in] ClkReqNum  CLKREQ# number
**/
VOID
PchFia15AssignGbeClkReq (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        ClkReqNum
  )
{
  UINT32  GdrcremValue;

  if (ClkReqNum == PCH_FIA_NO_CLKREQ) {
    PchPcrAndThenOr32 (
      FiaInst.SbPortId,
      R_PCH_FIA_15_PCR_GDRCREM,
      ~(UINT32) B_PCH_FIA_15_PCR_GDRCREM_ENABLE,
      0);
  } else {
    GdrcremValue = (ClkReqNum << N_PCH_FIA_15_PCR_GDRCREM_NUMBER) & B_PCH_FIA_15_PCR_GDRCREM_NUMBER;
    GdrcremValue |= B_PCH_FIA_15_PCR_GDRCREM_ENABLE;
    PchPcrWrite32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_GDRCREM, GdrcremValue);
  }
}

/**
  Configures lower bound of delay between ClkReq assertion and driving RefClk.
  The delay is hardcoded to 15us, due to hardware design. Clocks may not be stable earlier.

  @param[in] FiaInst     FIA Instance
**/
VOID
PchFia15SetClockOutputDelay (
  IN FIA_INSTANCE FiaInst
  )
{
  UINT32 Data32Or;
  UINT32 Data32And;
  UINT32 Index;

  Data32Or = 0;
  Data32And = 0xFFFFFFFF;
  for (Index = 0; Index < S_PCH_FIA_PCR_TREFCLKON_FIELDS_PER_REG; Index++) {
    Data32Or |= (V_PCH_FIA_PCR_TREFCLKON_15us << (Index * S_PCH_FIA_PCR_TREFCLKON_FIELD));
    Data32And &= ~(B_PCH_FIA_PCR_TREFCLKON_FIELD << (Index * S_PCH_FIA_PCR_TREFCLKON_FIELD));
  }
  PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_PCR_TREFCLKONTMR1, Data32And, Data32Or);
  PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_PCR_TREFCLKONTMR2, Data32And, Data32Or);
  PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_PCR_TREFCLKONTMR3, Data32And, Data32Or);
  PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_PCR_TREFCLKONTMR4, Data32And, Data32Or);
}

/**
  Configure Orientation Muxing for Type-C Connectors
  N-th and (N+1)-th Lane can be flipped

  @param[in] FiaInst       FIA Instance
  @param[in] LaneMask      Mask for Lane Pairs which need to be swapped. Bit0 for pair 2&3 and Bit4 for pair 10&11
**/
VOID
PchFia15ConfigureOrientationMuxing (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        LaneMask
  )
{
  UINT32 Data32Or;
  UINT32 Data32And;
  UINT8  ConnectorIndex;
  UINT8  LaneIndex;

  Data32And = 0xFFFFFFFF;
  Data32Or = 0;
  Data32Or |= (UINT32) LaneMask;

  for (ConnectorIndex = 0; ConnectorIndex < PCH_FIA_15_MAX_ORM_CONNECTOR; ConnectorIndex ++) {
    LaneIndex = (ConnectorIndex * 2) + PCH_FIA_15_ORM_CONNECTOR_FIRST_LANE;
    if ((LaneMask & ( 1 << ConnectorIndex )) != 0) {
      DEBUG ((DEBUG_INFO, "FIA Lane %d and %d Swap\n", LaneIndex, LaneIndex + 1 ));
    } else {
      DEBUG ((DEBUG_INFO, "FIA Lane %d and %d Not Swap\n", LaneIndex, LaneIndex + 1 ));
    }
  }
  PchPcrAndThenOr32 (FiaInst.SbPortId, R_PCH_FIA_15_PCR_DFLEXORM, Data32And, Data32Or);
}