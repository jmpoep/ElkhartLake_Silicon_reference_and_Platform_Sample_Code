/** @file
  Iosf2Ocp bridge helper functions.

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

#include "PeiIosf2OcpInternal.h"
#include <Register/PchPcrRegs.h>

IOSF2OCP_PORT  mUfsPort = {
  PID_UFSX2,
  0
};

/**
  Get UFS controller location on Iosf2Ocp bridge.

  @param[in] UfsIndex  Global index identifying UFS controller instance

  @return IOSF2OCP_PORT  Structure describing UFS controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetUfsPort (
  IN UINT8  UfsIndex
  )
{
  switch (UfsIndex) {
    case 0:
      return &mUfsPort;
    default:
      ASSERT (FALSE);
      return NULL;
  }
}

IOSF2OCP_PORT  mEmmcPort = {
  PID_EMMC,
  0
};

IOSF2OCP_PORT  mV1p1EmmcPort = {
  PID_EMMC_V1_1,
  0
};

/**
  Get eMMC controller location on Iosf2Ocp bridge.

  @return  IOSF2OCP_PORT  Structure describing eMMC controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetEmmcPort (
  VOID
  )
{
  if (IsJslPch ()) {
    return &mV1p1EmmcPort;
  } else {
    return &mEmmcPort;
  }
}

IOSF2OCP_PORT  mSdCardPort = {
  PID_SDX,
  0
};

/**
  Get SdCard controller port on Iosf2Ocp bridge.

  @return IOSF2OCP_PORT  Structure describing SdCard controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetSdCardPort (
  VOID
  )
{
  return &mSdCardPort;
}

/**
  Initializes Iosf2Ocp bridges.
**/
VOID
Iosf2OcpInitializeBridges (
  VOID
  )
{
  IOSF2OCP_PORT  *Iosf2OcpPort;
  //
  // On ICL SCS has 3 bridges. One with SdCard controller,
  // one with eMMC and one with UFS.
  //
  Iosf2OcpPort = Iosf2OcpGetSdCardPort ();
  Iosf2OcpConfigurePowerAndClockGating (Iosf2OcpPort->BridgePortId, 0x81DE17);
  Iosf2OcpEnableSnoopedTransactions (Iosf2OcpPort->BridgePortId);

  Iosf2OcpPort = Iosf2OcpGetEmmcPort ();
  if (IsJslPch ()) {
    Iosf2OcpConfigurePowerAndClockGating (Iosf2OcpPort->BridgePortId, 0x1D847);
    Iosf2OcpEnableSnoopedTransactions (Iosf2OcpPort->BridgePortId);
  } else {
    if (IsPchLp ()) {
      Iosf2OcpConfigurePowerAndClockGating (Iosf2OcpPort->BridgePortId, 0x1D847);
      Iosf2OcpEnableSnoopedTransactions (Iosf2OcpPort->BridgePortId);
    }
  }

  if (IsPchLp () || IsPchN ()) {
    Iosf2OcpConfigurePowerAndClockGating (PID_UFSX2, 0xDFF80F);
    Iosf2OcpEnableSnoopedTransactions (PID_UFSX2);
  }
}

