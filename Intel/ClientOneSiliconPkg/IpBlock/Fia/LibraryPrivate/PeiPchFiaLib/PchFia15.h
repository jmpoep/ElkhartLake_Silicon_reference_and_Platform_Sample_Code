/** @file
  Header file for PchFia15

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

#include <Register/PchRegsFia15.h>

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
  );

/**
  Print FIA LOS registers.

  @param[in] FiaInst  FIA Instance
**/
VOID
PchFia15PrintLosRegisters (
  IN FIA_INSTANCE FiaInst
  );

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
  );

/**
  Assigns CLKREQ# to CPU PCIe ports

  @param[in] FiaInst        FIA Instance
  @param[in] RpIndex        Rootport index
  @param[in] ClkReqNum      Number of the clock
**/
VOID
PchFia15AssignCpuPciePortClkReq (
  IN FIA_INSTANCE FiaInst,
  IN UINT32       RpIndex,
  IN UINT8        ClkReqNum
  );

/**
Enables CLKREQ# to CPU PCIe ports

@param[in] FiaInst        FIA Instance
@param[in] RpIndex        Rootport index
@param[in] ClkReqNum      Number of the clock
**/
VOID
PchFia15EnableCpuPciePortClkReq(
IN FIA_INSTANCE FiaInst,
IN UINT32       RpIndex,
IN UINT8        ClkReqNum
);

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
  );

/**
  Assigns CLKREQ# to GbE

  @param[in] FiaInst    FIA Instance
  @param[in] ClkReqNum  CLKREQ# number
**/
VOID
PchFia15AssignGbeClkReq (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        ClkReqNum
  );

/**
  Configures lower bound of delay between ClkReq assertion and driving RefClk.
  The delay is hardcoded to 15us, due to hardware design. Clocks may not be stable earlier.

  @param[in] FiaInst     FIA Instance
**/
VOID
PchFia15SetClockOutputDelay (
  IN FIA_INSTANCE FiaInst
  );

/**
  Configure Orientation Muxing for Type-C Connectors
  N-th and (N+1)-th Lane can be flipped

  @param[in] FiaInst       FIA Instance
  @param[in] LaneSwapMask  Mask for Lane Pairs which need to be swapped. Bit0 for pair 2&3 and Bit4 for pair 10&11
**/
VOID
PchFia15ConfigureOrientationMuxing (
  IN FIA_INSTANCE FiaInst,
  IN UINT8        LaneMask
  );
