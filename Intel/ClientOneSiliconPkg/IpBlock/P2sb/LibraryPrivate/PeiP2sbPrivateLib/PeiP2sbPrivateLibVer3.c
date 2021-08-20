/** @file
  Initializes PCH Primary To Sideband Bridge (P2SB VER3) Device in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Register/P2sbRegs.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiP2sbPrivateLib.h>
#include <Register/PchPcrRegs.h>

/**
  The function configures P2SB power management

  @param[in] BOOLEAN         PchMasterClockGating
  @param[in] BOOLEAN         PchMasterPowerGating
  @param[in] BOOLEAN         Enable low latency of legacy IO
**/
VOID
P2sbPowerGatingConfigure (
  IN  BOOLEAN  PchMasterClockGating,
  IN  BOOLEAN  PchMasterPowerGating,
  IN  UINT32   LegacyIoLowLatency
  )
{
  UINT64                      P2sbBase;

  P2sbBase = P2sbPciBase ();

  if (PchMasterClockGating) {
    ///
    /// Set PGCB clock gating enable (PGCBCGE)
    /// P2SB PCI offset 0xE0[16] = 1
    ///
    PciSegmentOr8 (P2sbBase + R_P2SB_CFG_E0 + 2, BIT0);
  } else {
    PciSegmentAnd8 (P2sbBase + R_P2SB_CFG_E0 + 2, (UINT8)~(BIT0));
  }
  if (PchMasterPowerGating) {
    ///
    /// Set Hardware Autonomous Enable (HAE) and PMC Power Gating Enable (PMCPG_EN)
    /// P2SB PCI offset 0xE4[5,2,1,0] = 0's
    ///
    PciSegmentAnd8 (P2sbBase + R_P2SB_CFG_E4,  (UINT8) ~(BIT5 | BIT2 | BIT1 | BIT0));
  } else {
    PciSegmentAnd8 (P2sbBase + R_P2SB_CFG_E4,  (UINT8) ~(BIT5 | BIT3 | BIT2 | BIT1 | BIT0));
  }
}


GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mEndpointMaskPort[] =
{
  PID_PSF1,
  PID_PSF2,
  PID_PSF3,
  PID_CSME_PSF,
  PID_PSF5,
  PID_PSF6,
  PID_PSF7,
  PID_PSF8,
  PID_PSF9
};

/**
  Get list of P2sb Endpoint Masked PIDs

  @param[out] EndpointMaskTable        Endpoint Masked PIDs
  @param[out] EndpointMaskTableLength  Length of EndpointMaskTable
**/
VOID
P2sbGetEndpointMaskedPids (
  OUT UINT16   **EndpointMaskTable,
  OUT UINT32   *EndpointMaskTableLength
  )
{
  *EndpointMaskTable = mEndpointMaskPort;
  *EndpointMaskTableLength = ARRAY_SIZE (mEndpointMaskPort);
}
