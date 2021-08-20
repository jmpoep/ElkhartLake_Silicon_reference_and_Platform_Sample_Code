/** @file
  Implements Platform Trust Technology (PTT) HECI SkuMgr Interface Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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

#include <PiDxe.h>
#include <Library/DebugLib.h>

#include <Library/DxeMeLib.h>
#include <Library/PttHeciLib.h>

#include <MeBiosPayloadHob.h>
#include <Library/HobLib.h>

/**
  Checks whether ME FW has the Platform Trust Technology capability.

  @param[out] PttCapability      TRUE if PTT is supported, FALSE otherwise.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciGetCapability (
  OUT BOOLEAN   *PttCapability
  )
{
  ME_BIOS_PAYLOAD_HOB       *MbpHob;

  *PttCapability = FALSE;
  MbpHob         = NULL;

  //
  // Get the MBP Data.
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if (MbpHob != NULL) {
    if (MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.PTT) {
      *PttCapability = TRUE;
    }
  } else {
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO, "PTT SkuMgr: PttCapability = %d\n", *PttCapability));

  return EFI_SUCCESS;
}

/**
  Checks Platform Trust Technology enablement state.

  @param[out] IsPttEnabledState  TRUE if PTT is enabled, FALSE otherwise.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciGetState (
  OUT BOOLEAN   *IsPttEnabledState
  )
{
  EFI_STATUS      Status;
  MEFWCAPS_SKU    CurrentFeatures;

  *IsPttEnabledState = FALSE;

  Status = HeciGetFwFeatureStateMsg (&CurrentFeatures);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CurrentFeatures.Fields.PTT) {
    *IsPttEnabledState = TRUE;
  }

  DEBUG ((DEBUG_INFO, "PTT SkuMgr: PttState = %d\n", *IsPttEnabledState));

  return EFI_SUCCESS;
}

/**
  Changes current Platform Trust Technology state.

  @param[in] PttEnabledState     TRUE to enable, FALSE to disable.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciSetState (
  IN  BOOLEAN   PttEnabledState
  )
{
  EFI_STATUS      Status;
  UINT32          EnableBitmap;
  UINT32          DisableBitmap;

  if (PttEnabledState) {
    //
    // Enable PTT
    //
    DEBUG ((DEBUG_INFO, "PTT SkuMgr: Enable PTT\n"));
    EnableBitmap  = PTT_BITMASK;
    DisableBitmap = CLEAR_FEATURES_BITMASK;
  } else {
    //
    // Disable PTT
    //
    DEBUG ((DEBUG_INFO, "PTT SkuMgr: Disable PTT\n"));
    EnableBitmap  = CLEAR_FEATURES_BITMASK;
    DisableBitmap = PTT_BITMASK;
  }
  Status = HeciFwFeatureStateOverride (EnableBitmap, DisableBitmap);

  return Status;
}

