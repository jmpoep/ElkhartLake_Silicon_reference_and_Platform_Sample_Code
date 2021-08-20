/** @file
  Print whole MBP_DATA_HOB and serial out.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <MeBiosPayloadData.h>
#include <Library/MeShowBufferLib.h>
#include "MbpData.h"
#if FixedPcdGetBool(PcdBfxEnable) == 0
#include <Ppi/MbpSensitivePpi.h>
#endif

/**
  Print MbpHob data

  @param[in] MbpHob             Pointer to Mbp Hob
  @param[in] MbpSensitivePpi    Pointer to Mbp Sensitive Ppi

**/
VOID
PrintMbpData (
  IN ME_BIOS_PAYLOAD_HOB *MbpHob,
#if FixedPcdGetBool(PcdBfxEnable) == 1
  IN ME_BIOS_PAYLOAD_SENSITIVE_HOB *MbpSensitiveHob
#else
  IN MBP_SENSITIVE_PPI   *MbpSensitivePpi
#endif
  )
{
  UINTN PlatformKeyNum;

#if FixedPcdGetBool(PcdBfxEnable) == 1
  if (MbpHob == NULL || MbpSensitiveHob == NULL) {
#else
  if (MbpHob == NULL || MbpSensitivePpi == NULL) {
#endif
    return;
  }
  DEBUG ((DEBUG_INFO, "\n------------------------ MeBiosPayload Data Protocol Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : 0x%x\n", MbpHob->Revision));
  DEBUG ((DEBUG_INFO, "MeBiosPayload FwVersionName ---\n"));
  DEBUG ((DEBUG_INFO, " ME FW MajorVersion  : %d\n", MbpHob->MeBiosPayload.FwVersionName.MajorVersion));
  DEBUG ((DEBUG_INFO, " ME FW MinorVersion  : %d\n", MbpHob->MeBiosPayload.FwVersionName.MinorVersion));
  DEBUG ((DEBUG_INFO, " ME FW HotfixVersion : %d\n", MbpHob->MeBiosPayload.FwVersionName.HotfixVersion));
  DEBUG ((DEBUG_INFO, " ME FW BuildVersion  : %d\n", MbpHob->MeBiosPayload.FwVersionName.BuildVersion));

  if (MbpHob->MeBiosPayload.FwCapsSku.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload FwCapabilities ---\n"));
    DEBUG ((DEBUG_INFO, " FullMng         : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.FullMng));
    DEBUG ((DEBUG_INFO, " StdMng          : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.StdMng));
    DEBUG ((DEBUG_INFO, " Amt             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.Amt));
    DEBUG ((DEBUG_INFO, " EyeRiver        : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.EyeRiver));
    DEBUG ((DEBUG_INFO, " IntegratedTouch : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntegratedTouch));
    DEBUG ((DEBUG_INFO, " IntelCLS        : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntelCLS));
    DEBUG ((DEBUG_INFO, " ISH             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.ISH));
    DEBUG ((DEBUG_INFO, " PAVP            : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.PAVP));
    DEBUG ((DEBUG_INFO, " IPV6            : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IPV6));
    DEBUG ((DEBUG_INFO, " KVM             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.KVM));
    DEBUG ((DEBUG_INFO, " DAL             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.DAL));
    DEBUG ((DEBUG_INFO, " TLS             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.TLS));
    DEBUG ((DEBUG_INFO, " WLAN            : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.WLAN));
    DEBUG ((DEBUG_INFO, " TrustedDevice   : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.TrustedDevice));
    DEBUG ((DEBUG_INFO, " PTT             : 0x%x\n", MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.PTT));
  }

  if (MbpHob->MeBiosPayload.FwFeaturesState.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload FwFeaturesState ---\n"));
    DEBUG ((DEBUG_INFO, " FullMng         : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.FullMng));
    DEBUG ((DEBUG_INFO, " StdMng          : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.StdMng));
    DEBUG ((DEBUG_INFO, " Amt             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.Amt));
    DEBUG ((DEBUG_INFO, " EyeRiver        : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.EyeRiver));
    DEBUG ((DEBUG_INFO, " IntegratedTouch : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.IntegratedTouch));
    DEBUG ((DEBUG_INFO, " IntelCLS        : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.IntelCLS));
    DEBUG ((DEBUG_INFO, " ISH             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.ISH));
    DEBUG ((DEBUG_INFO, " PAVP            : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.PAVP));
    DEBUG ((DEBUG_INFO, " IPV6            : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.IPV6));
    DEBUG ((DEBUG_INFO, " KVM             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.KVM));
    DEBUG ((DEBUG_INFO, " DAL             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.DAL));
    DEBUG ((DEBUG_INFO, " TLS             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.TLS));
    DEBUG ((DEBUG_INFO, " WLAN            : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.WLAN));
    DEBUG ((DEBUG_INFO, " TrustedDevice   : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.TrustedDevice));
    DEBUG ((DEBUG_INFO, " PTT             : 0x%x\n", MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.PTT));
  }

  if (MbpHob->MeBiosPayload.FwPlatType.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload ME Platform TYpe ---\n"));
    DEBUG ((DEBUG_INFO, " PlatformTargetUsageType : 0x%x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.PlatformTargetUsageType));
    DEBUG ((DEBUG_INFO, " SuperSku                : 0x%x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.SuperSku));
    DEBUG ((DEBUG_INFO, " IntelMeFwImageType      : 0x%x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType));
    DEBUG ((DEBUG_INFO, " PlatformBrand           : 0x%x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.PlatformBrand));
  }

  if (MbpHob->MeBiosPayload.HwaRequest.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload HwaRequest ---\n"));
    DEBUG ((DEBUG_INFO, " MediaTablePush : 0x%x\n", MbpHob->MeBiosPayload.HwaRequest.Data.Fields.MediaTablePush));
  }

  if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload UnconfigOnRtcClearState ---\n"));
    DEBUG ((DEBUG_INFO, " UnconfigOnRtcClearData : 0x%x\n", MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState));
  }

  if (MbpHob->MeBiosPayload.ArbSvnState.Available == TRUE) {
    DEBUG ((DEBUG_INFO, "MeBiosPayload ArbSvnState ---\n"));
    DEBUG ((DEBUG_INFO, " Flags         : 0x%x\n", MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.Flags));
    DEBUG ((DEBUG_INFO, " MinCseArbSvn  : 0x%x\n", MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.MinCseArbSvn));
    DEBUG ((DEBUG_INFO, " CurrCseArbSvn : 0x%x\n", MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.CurrCseArbSvn));
  }

#if FixedPcdGetBool(PcdBfxEnable) == 1
  DEBUG ((DEBUG_INFO, " Sensitive Data Revision : 0x%x\n", MbpSensitiveHob->Revision));
#else
  DEBUG ((DEBUG_INFO, " Sensitive Data Revision : 0x%x\n", MbpSensitivePpi->Revision));
#endif
  DEBUG ((DEBUG_INFO, "MeBiosPayload Platform Key ---\n"));
  for (PlatformKeyNum = 0; PlatformKeyNum < 8; PlatformKeyNum++) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
    DEBUG ((DEBUG_INFO, " Key[0x%x] : 0x%x \n", PlatformKeyNum, MbpSensitiveHob->MeBiosPayloadSensitive.PlatformKey.Key[PlatformKeyNum]));
#else
    DEBUG ((DEBUG_INFO, " Key[0x%x] : 0x%x \n", PlatformKeyNum, MbpSensitivePpi->MbpSensitiveData.PlatformKey.Key[PlatformKeyNum]));
#endif
  }

  DEBUG ((DEBUG_INFO, "\n------------------------ MeBiosPayload Data Protocol Print End -------------------\n"));
}
