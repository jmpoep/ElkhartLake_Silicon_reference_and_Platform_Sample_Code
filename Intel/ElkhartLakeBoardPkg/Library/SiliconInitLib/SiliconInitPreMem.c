/** @file
  Source code file for Silicon Init Pre-Memory Library

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <PiPei.h>

#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Register/PchRegsLpc.h>
#include <Register/PchRegs.h>

/**
  Early Platform PCH initialization
**/
VOID
EarlySiliconInit (
  VOID
  )
{
  UINT16                            LpcIoe;
  UINT16                            LpcIoeOrg;
  UINT64                            LpcBaseAddress;

  ///
  /// LPC I/O Configuration
  ///
  PchLpcIoDecodeRangesSet (
    (V_LPC_CFG_IOD_LPT_378  << N_LPC_CFG_IOD_LPT)  |
    (V_LPC_CFG_IOD_COMB_3E8 << N_LPC_CFG_IOD_COMB) |
    (V_LPC_CFG_IOD_COMA_3F8 << N_LPC_CFG_IOD_COMA)
    );

  PchLpcIoEnableDecodingSet (
    B_LPC_CFG_IOE_ME2  |
    B_LPC_CFG_IOE_SE   |
    B_LPC_CFG_IOE_ME1  |
    B_LPC_CFG_IOE_KE   |
    B_LPC_CFG_IOE_HGE  |
    B_LPC_CFG_IOE_LGE  |
    B_LPC_CFG_IOE_FDE  |
    B_LPC_CFG_IOE_PPE  |
    B_LPC_CFG_IOE_CBE  |
    B_LPC_CFG_IOE_CAE
    );

  ///
  /// Enable LPC IO decode for EC access
  ///
  LpcBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_LPC,
                     PCI_FUNCTION_NUMBER_PCH_LPC,
                     0
                     );
  LpcIoeOrg = PciSegmentRead16 (LpcBaseAddress + R_LPC_CFG_IOE);
  LpcIoe = LpcIoeOrg | B_LPC_CFG_IOE_ME1;
#if FixedPcdGet8(PcdEmbeddedEnable) == 1
  // Enable LPC IO decode for SIO (0x2e) access.
  LpcIoe = LpcIoeOrg | B_LPC_CFG_IOE_SE;
  LpcIoeOrg |= B_LPC_CFG_IOE_SE;
#endif

  PchLpcIoEnableDecodingSet (LpcIoe);

  if (PcdGetBool (PcdEcPresent) == FALSE) {
    ///
    /// Restore LPC IO decode setting
    ///
    PchLpcIoEnableDecodingSet (LpcIoeOrg);
  }

}

// @todo: It should be moved Policy Init.
/**
  Initialize the GPIO IO selection, GPIO USE selection, and GPIO signal inversion registers

**/
VOID
SiliconInit (
  VOID
  )
{
}

