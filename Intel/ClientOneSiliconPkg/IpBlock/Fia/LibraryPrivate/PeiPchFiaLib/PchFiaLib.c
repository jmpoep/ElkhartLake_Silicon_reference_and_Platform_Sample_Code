/** @file
  This file contains FIA routines

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

/**
  Checks if a given PCIe lane is assigned any FIA lane

  @param[in]  RpIndex      PCIe root port index
  @param[in]  RpLaneIndex  Root port lane index within given root port

  @return  TRUE if given PCIe lane is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsPcieRootPortLaneConnected (
  IN UINT32  RpIndex,
  IN UINT32  RpLaneIndex
  )
{
  UINT8  LaneNum;
  return PchFiaGetPcieRootPortLaneNum (RpIndex, RpLaneIndex, &LaneNum);
}

/**
  Checks if a given SATA port is assigned any FIA lane

  @param[in] SataCtrlIndex  SATA controller index
  @param[in] SataPortIndex  SATA port index

  @return TRUE if given SATA port is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsSataPortConnected (
  IN UINT32  SataCtrlIndex,
  IN UINT32  SataPortIndex
  )
{
  UINT8  LaneNum;
  return PchFiaGetSataLaneNum (SataCtrlIndex, SataPortIndex, &LaneNum);
}

/**
  Checks if a given USB3 port is assigned any FIA lane

  @param[in]  Usb3PortIndex  USB3 port index

  @return TRUE if given USB3 port is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsUsb3PortConnected (
  IN UINT32  Usb3PortIndex
  )
{
  UINT8 LaneNum;
  return PchFiaGetUsb3LaneNum (Usb3PortIndex, &LaneNum);
}

/**
  Check if UFS lane is assigned a FIA lane

  @param[in] UfsControllerIndex  UFS controller index
  @param[in] UfsLaneIndex        Lane index local to given UFS controller

  @retval TRUE  UFS lane is assigned a FIA lane
  @retval FALSE  UFS lane is not assigned any FIA lane
**/
BOOLEAN
PchFiaIsUfsLaneConnected (
  IN UINT32  UfsControllerIndex,
  IN UINT32  UfsLaneIndex
  )
{
  return PchFiaGetUfsLaneNum (UfsControllerIndex, UfsLaneIndex, NULL);
}

/**
  Returns a FIA lane number for a given PCIe root port
  This function handles PCIe lane reversal internaly.

  @param[in]  RpIndex       PCIe root port index
  @param[in]  RpLaneIndex   Root port lane index within given root port
  @param[out] LaneNum       Pointer to the variable that stores lane number.
                            The output value is only valid if this function returns TRUE.

  @return TRUE if given RpLane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetPcieRootPortLaneNum (
  IN  UINT32  RpIndex,
  IN  UINT32  RpLaneIndex,
  OUT UINT8  *LaneNum
  )
{
  return PchFiaGetPcieLaneNum (PchPciePhysicalLane (RpIndex, RpLaneIndex), LaneNum);
}

/**
  Converts FIA 14.0/15.0 lane owner encoding to version independent encoding.

  @param[in] LaneOwner  Lane owner value corresponding to the FIA 14.0/15.0 lane owner encoding
  @param[in] LaneNum    Fia lane number

  @retval PCH_FIA_LANE_OWNER  FIA lane owner in version independent format.
**/
PCH_FIA_LANE_OWNER
PchFiaDecodeOwner (
  IN UINT32  LaneOwner,
  IN UINT8   LaneNum
  )
{
  switch (LaneOwner) {
    case V_PCH_FIA_PCR_LANE_OWN_PCIEDMI:
      if (PchFiaIsLaneDmi (LaneNum)) {
        return PchFiaOwnerDmi;
      } else {
        return PchFiaOwnerPcie;
      }
    case V_PCH_FIA_PCR_LANE_OWN_USB3:
      return PchFiaOwnerUsb3;
    case V_PCH_FIA_PCR_LANE_OWN_SATA:
      return PchFiaOwnerSata;
    case V_PCH_FIA_PCR_LANE_OWN_GBE:
      return PchFiaOwnerGbe;
    case V_PCH_FIA_PCR_LANE_OWN_UFS:
      return PchFiaOwnerUfs;
    case V_PCH_FIA_PCR_LANE_OWN_TSN:
      return PchFiaOwnerTsn;
    case V_PCH_FIA_PCR_LANE_OWN_PCIE2ND:
      return PchFiaOwnerPcie2nd;
    default:
      return PchFiaOwnerInvalid;
  }
}
