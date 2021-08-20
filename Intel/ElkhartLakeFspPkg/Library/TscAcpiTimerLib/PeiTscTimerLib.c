/** @file
  A Pei Timer Library implementation which uses the Time Stamp Counter in the processor.
  This instance will use ACPI timer to calculate TSC frequency.

  Note: There will be 1ms penalty to get TSC frequency for first time call
  by waiting for 3579 clocks of the ACPI timer, or 1ms.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <PiPei.h>
#include <Library/HobLib.h>
#include "TscTimerLibInternal.h"

/**  Get TSC frequency.

  @return The number of TSC counts per second.

**/
UINT64
InternalGetTscFrequency (
  VOID
  )
{
  EFI_HOB_GUID_TYPE  *GuidHob;
  UINT64             TscFrequency;

  //
  // Get TSC frequency from FSP TSC frequency GUID HOB.
  // This is done to avoid calling InternalCalculateTscFrequency everytime, which will take 1ms.
  //
  GuidHob = GetFirstGuidHob (&gFspTscFrequencyGuid);
  if (GuidHob != NULL) {
    TscFrequency = * (UINT64 *) GET_GUID_HOB_DATA (GuidHob);
    return TscFrequency;
  }

  //
  // Build FSP TSC frequency GUID HOB by calculating it.
  //
  TscFrequency = InternalCalculateTscFrequency ();

  BuildGuidDataHob (&gFspTscFrequencyGuid, &TscFrequency, sizeof (UINT64));

  return TscFrequency;
}

