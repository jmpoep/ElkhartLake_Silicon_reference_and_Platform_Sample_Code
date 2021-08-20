/** @file
  This file contains the tests for the SecurePchConfiguration Bit at SMM

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

@par Specification
**/

#include "HstiIhvSmm.h"

/**
  Run tests for SecureP2SBSmmConfiguration bit

  @retval   Results. If different from  0 all or some Tests Failed.
**/
UINT32
CheckSecurePchSmmConfiguration (
  VOID
  )
{
  UINT32    UnexpStatus;
  UINT32    EpMask5;
  UINT32    EpMask7;
  UINT32    EpMaskRemoveMaskRegResult;
  UINT32    EpMask5RemoveAccMaskValue;
  UINT32    EpMask7RemoveAccMaskValue;

  EpMask5                    = 5;
  EpMask7                    = 7;
  UnexpStatus                = 0;
  EpMaskRemoveMaskRegResult  = 0;
  EpMask5RemoveAccMaskValue  = BIT29 | BIT28 | BIT27 | BIT26;
  EpMask7RemoveAccMaskValue  = BIT31 | BIT30;

  DEBUG ((DEBUG_INFO, "      P2sb Remove Access EPMASK5 Verification Test\n"));
  EpMaskRemoveMaskRegResult = P2sbGetEpmask (EpMask5);

  if (EpMaskRemoveMaskRegResult != EpMask5RemoveAccMaskValue) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: EPMASK5 Reserved BITS 29-26 = %lx\n", EpMaskRemoveMaskRegResult));
    // Save HSTI P2SB Smm Unexpected error for PCH (P2sbEpMask5RemAccMaskBits29To26UnexpSts)
    UnexpStatus = P2sbEpMask5RemAccMaskBits29To26UnexpSts;
  }

  DEBUG ((DEBUG_INFO, "      P2sb Remove Access EPMASK7 Verification Test\n"));
  EpMaskRemoveMaskRegResult = P2sbGetEpmask (EpMask7);

  if (EpMaskRemoveMaskRegResult != EpMask7RemoveAccMaskValue) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: EPMASK7 Reserved BITS 31-30 = %lx\n", EpMaskRemoveMaskRegResult));
    // Save HSTI P2SB Smm Unexpected error for PCH (P2sbEpMask7RemAccMaskBits31To30UnexpSts)
    UnexpStatus = UnexpStatus | P2sbEpMask7RemAccMaskBits31To30UnexpSts;
  }

  DEBUG ((DEBUG_INFO, "      P2SB Mask Bit Locked Test\n"));

  if (!P2sbIsEpmaskLock ()) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: P2SB Mask Unlocked\n"));
    // Save HSTI P2SB Smm Unexpected error for PCH (P2sbLockMaskBitUnexpSts)
    UnexpStatus = UnexpStatus | P2sbLockMaskBitUnexpSts;

  }

  return UnexpStatus;
}
