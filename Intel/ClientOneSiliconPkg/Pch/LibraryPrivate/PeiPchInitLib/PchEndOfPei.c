/** @file
  Initializes PCH at end of PEI

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

#include "PchInitPei.h"
#include <Library/PostCodeLib.h>
#include <Library/PeiWdtLib.h>
#include <Library/PeiRtcLib.h>

/**
  Perform necessary lock/unlock configuration of GPIO pads.
  This function can only be called before BIOS transitions to POSTBOOT_SAI.

  @param[in] SiPolicyPpi  The SI Policy PPI instance
**/
VOID
PchConfigureGpioLock (
  IN  SI_POLICY_PPI                    *SiPolicyPpi
  )
{
  EFI_STATUS            Status;
  PCH_LOCK_DOWN_CONFIG  *LockDownConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // Unlock GPIO pads if needed
  //
  if (LockDownConfig->UnlockGpioPads) {
    GpioUnlockAllPads ();
  } else {
    //
    // PCH BWG 16.6. GPP_A_12 Special Handling
    //
    GpioA12SpecialHandling ();
  }
}

/**
  Pch End of PEI callback function. This is the last event before entering DXE and OS in S3 resume.
**/
VOID
PchOnEndOfPei (
  VOID
  )
{
  EFI_STATUS             Status;
  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy;
  SI_POLICY_PPI          *SiPolicy;

  PostCode (0xB40);
  DEBUG ((DEBUG_INFO, "PchOnEndOfPei after memory PEI module - Start\n"));

  //
  // Get Policy settings through the SiPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }

  //
  // Get Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_PREMEM_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }

  //
  // Clear RTC PWR STS in end of PEI so others won't miss the status
  //
  ///
  /// PCH BIOS Spec Section 19.8.1 RTC Resets
  /// The PCH will set the RTC_PWR_STS bit when the RTCRST# pin goes low.
  /// The System BIOS shouldn't rely on the RTC RAM contents when the RTC_PWR_STS bit is set.
  /// BIOS should clear this bit by writing a 0 to this bit position.
  /// This bit isn't cleared by any reset function.
  ///
  PmcClearRtcPowerFailureStatus ();


  //
  // Init thermal device and lock down settings.
  //
  PostCode (0xB41);
  ThermalInit (SiPolicy);

  //
  // Init Memory Throttling.
  // Memory Throttling doesn't depend on PCH thermal.
  //
  PostCode (0xB42);
  MemoryThrottlingInit (SiPolicy);

  WdtDisableBeforeS3Resume ();

  PchFiaFinalizeConfigurationAndLock (SiPolicy);

  //
  // Configure Pm timer
  // This must be done after uCode PM timer emulation.
  //
  PmcConfigurePmTimer (SiPolicy);

  //
  // Lock PMC settings
  //
  PmcLockSettings (SiPolicy);

  //
  // Lock RTC settings
  //
  RtcLock (SiPolicy);

  //
  // Handle GPIO lock settings
  //
  PchConfigureGpioLock (SiPolicy);

  //
  // HdAudio Init
  //
  HdAudioInit (SiPreMemPolicy);

  PostCode (0xB47);
  DEBUG ((DEBUG_INFO, "PchOnEndOfPei after memory PEI module - End\n"));
}


