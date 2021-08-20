/** @file
  This is a library to get Intel MBP Data.

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
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MbpDataLib.h>
#include <MkhiMsgs.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>

/**
  MBP gets Firmware update info from ME client

  @param[in] MeCapability         Structure of FirmwareUpdateInfo

  @retval EFI_SUCCESS             Get ME Firmware success
  @retval EFI_UNSUPPORTED         No MBP Data Protocol available
**/
EFI_STATUS
MbpGetMeFwInfo (
  IN OUT ME_CAP *MeCapability
  )
{
  MEFWCAPS_SKU          FwCapsSku;
  ME_BIOS_PAYLOAD_HOB   *MbpHob;

  MbpHob = NULL;

  //
  // Get Mbp Data HOB
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "HeciGetMeFwInfo: No MBP Data Protocol available\n"));
    return EFI_UNSUPPORTED;
  }

  MeCapability->MeEnabled = 1;

  FwCapsSku.Data          = MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Data;

  if (FwCapsSku.Fields.KVM) {
    MeCapability->IntelKVM = 1;
  }

  switch (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.PlatformBrand) {
    case IntelAmtBrand:
      MeCapability->IntelAmtFw        = 1;
      MeCapability->LocalWakeupTimer  = 1;
      break;

    case IntelStandardManageabilityBrand:
      MeCapability->IntelAmtFwStandard = 1;
      break;
  }

  MeCapability->MeMajorVer  = MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
  MeCapability->MeMinorVer  = MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
  MeCapability->MeBuildNo   = MbpHob->MeBiosPayload.FwVersionName.BuildVersion;
  MeCapability->MeHotFixNo  = MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;

  return EFI_SUCCESS;
}