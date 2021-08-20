/** @file
  Provide polciy override functions in PostMem to enable specific silicon feature.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>

/**
  Override policies relevant to PlatformDebugConsent to enable debug in PostMem.

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
  @param[in] SiPolicyPpi               The Silicon PostMem Policy PPI instance
**/
STATIC
VOID
PlatformDebugConsentEnable (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi,
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  )
{
  EFI_STATUS                           Status;
  SI_PREMEM_CONFIG                     *SiPreMemConfig;

  SiPreMemConfig                     = NULL;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // skip policy override for manual
  //
  if (SiPreMemConfig->PlatformDebugConsent == ProbeTypeManual) {
    DEBUG ((DEBUG_INFO, "PlatformDeugConsent is Manual, DO NOT override policy!!!\n"));
    return;
  }
  //
  // Common setting for PDC enabled/disabled
  //
  switch (SiPreMemConfig->PlatformDebugConsent) {
    case ProbeTypeUsb3Dbc:
    case ProbeTypeXdp3:
    case ProbeType2WireDciOob:
    case ProbeTypeDisabled:
    case ProbeTypeUsb2Dbc:
    case ProbeTypeDciOob:
    default:
      break;
  }
  DEBUG ((DEBUG_INFO, "SiPreMemConfig->PlatformDebugConsent = %x\n", SiPreMemConfig->PlatformDebugConsent));
 }

/**
  Policy override in PostMem phase

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
  @param[in] SiPolicyPpi               The Silicon PostMem Policy PPI instance
**/
VOID
PeiSiPolicyOverride (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi,
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  )
{
  DEBUG ((DEBUG_INFO, "PeiSiPolicyOverride ()\n"));
  PlatformDebugConsentEnable (SiPreMemPolicyPpi, SiPolicyPpi);
}