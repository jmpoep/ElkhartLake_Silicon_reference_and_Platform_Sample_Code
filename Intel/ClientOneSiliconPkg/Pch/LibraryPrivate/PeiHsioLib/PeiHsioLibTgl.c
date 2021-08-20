/** @file
  Pei HSIO Library for TGL-PCH

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
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PeiHsioLib.h>
#include <PchHsio.h>
#include <Register/PchPcrRegs.h>

/**
  Get HSIO lane representation needed to perform any operation on the lane.

  @param[in]  LaneIndex  Number of the HSIO lane
  @param[out] HsioLane   HSIO lane representation
**/
VOID
HsioGetLane (
  IN   UINT8       LaneIndex,
  OUT  HSIO_LANE   *HsioLane
  )
{
  // PCH-LP
  // iolane  0 -  3 : 0xAB - 000, 400, 800, c00
  // iolane  4 -  7 : 0xAA - 000, 400, 800, c00
  // iolane  8 - 11 : 0xA9 - 000, 400, 800, c00
  // PCH-H
  // iolane  0 -  9 : 0xAB - 000, 400, 800, c00, 1000, 1400, 1800, 1c00, 2000, 2400
  // iolane 10 - 21 : 0xAA - 000, 400, 800, c00, 1000, 1400, 1800, 1c00, 2000, 2400, 2800, 2c00
  // iolane 22 - 29 : 0xA9 - 000, 400, 800, c00, 1000, 1400, 1800, 1c00
  // iolane 30 - 37 : 0xA8 - 000, 400, 800, c00, 1000, 1400, 1800, 1c00
  // PCH-N
  // iolane  0 -  1 : 0xAB - 000, 400
  // iolane  2 -  9 : 0xAA - 000, 400, 800, c00, 1000, 1400, 1800, 1c00

  static UINT8 IoLanesLp[] = { 0, 4, 8, 12 };
  static UINT8 PidsLp[] = { PID_MODPHY0, PID_MODPHY1, PID_MODPHY2 };

  static UINT8 IoLanesH[] = { 0, 10, 22, 30, 38 };
  static UINT8 PidsH[] = { PID_MODPHY0, PID_MODPHY1, PID_MODPHY2, PID_MODPHY3 };

  static UINT8 IoLanesN[] = { 0, 2, 10};
  static UINT8 PidsN[] = { PID_MODPHY0, PID_MODPHY1 };

  UINT8  *IoLanes;
  UINT8  *Pids;
  UINT8  PidMax;
  UINT32 Index;

  ASSERT (HsioLane != NULL);

    if (IsPchN ()) {
      IoLanes = IoLanesN;
      Pids    = PidsN;
      PidMax  = (sizeof (IoLanesN) / sizeof(UINT8)) - 1;
    } else
  if (IsPchLp ()) {
    IoLanes = IoLanesLp;
    Pids    = PidsLp;
    PidMax  = (sizeof (IoLanesLp) / sizeof (UINT8)) - 1;
  } else {
    IoLanes = IoLanesH;
    Pids    = PidsH;
    PidMax  = (sizeof (IoLanesH) / sizeof (UINT8)) - 1;
  }
  ASSERT (LaneIndex < IoLanes[PidMax]);

  for (Index = 0; Index < PidMax; ++Index) {
    if (LaneIndex < IoLanes[Index + 1]) {
      HsioLane->Index = LaneIndex;
      HsioLane->Pid   = Pids[Index];
      HsioLane->Base  = (LaneIndex - IoLanes[Index]) * 0x400;
      return;
    }
  }
  ASSERT (FALSE);
}
