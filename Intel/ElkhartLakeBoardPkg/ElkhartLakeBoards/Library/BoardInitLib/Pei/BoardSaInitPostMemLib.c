/** @file
 Source code for the board SA configuration Pcd init functions in Post-Memory init phase.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "BoardSaConfigPostMem.h"
#include <PlatformBoardId.h>


//
// Display DDI settings for EHL DDR4
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mEhlDdr4RowDisplayDdiConfig[5] = {
    DdiPortAEdp,    // DDI Port A Config : DdiPortADisabled = Disabled, DdiPortAEdp = eDP, DdiPortAMipiDsi = MIPI DSI, DdiPortADp = DP
    DdiPortBDp,     // DDI Port B Config : DdiPortBDisabled = Disabled, DdiPortBDp = DP, DdiPortBMipiDsi = MIPI DSI
    DdiPortCHdmi    // DDI Port C Config : DdiPortCDisabled = Disabled, DdiPortCHdmi = HDMI, DdiPortCDp = DP
};

/**
  SA Display DDI configuration init function for PEI post-memory phase.

  @param[in]  VOID

  @retval     VOID
**/
VOID
EhlSaDisplayConfigInit (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  switch (BoardId) {
    case BoardIdJslLp4xErb:
      PcdSet32S (PcdSaDisplayConfigTable, (UINTN) mJslDdr4RowDisplayDdiConfig);
      PcdSet16S (PcdSaDisplayConfigTableSize, sizeof (mJslDdr4RowDisplayDdiConfig));
      break;
    case BoardIdJslLp4xType4Rvp1:
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
      PcdSet32S (PcdSaDisplayConfigTable, (UINTN) mEhlRvp1ErbRowDisplayDdiConfig);
      PcdSet16S (PcdSaDisplayConfigTableSize, sizeof (mEhlRvp1ErbRowDisplayDdiConfig));
      break;
    case BoardIdEhlDdr4Type3Rvp2:
      PcdSet32S (PcdSaDisplayConfigTable, (UINTN) mEhlRvp2RowDisplayDdiConfig);
      PcdSet16S (PcdSaDisplayConfigTableSize, sizeof (mEhlRvp2RowDisplayDdiConfig));
      break;
    case BoardIdEhlLp4xType3Crb:
      PcdSet32S (PcdSaDisplayConfigTable, (UINTN) mEhlCrbRowDisplayDdiConfig);
      PcdSet16S (PcdSaDisplayConfigTableSize, sizeof (mEhlCrbRowDisplayDdiConfig));
      break;
    default:
      break;
  }
  return;
}
