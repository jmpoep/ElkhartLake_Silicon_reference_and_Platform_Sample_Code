/** @file
  Implementation file for Me Policy functionality for PEIM

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2020 Intel Corporation.

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

#include "MePeiLibInternals.h"

extern GUID gMeEopDoneHobGuid;

/**
  Initialize ME PEI PreMem Config Block.

  @retval EFI_SUCCESS             ME PEI PreMem Config Block is initialized.
  @retval All other error conditions encountered when ME PEI PreMem Config Block initialized fail.
**/
STATIC
EFI_STATUS
MePeiPreMemConfigInit (
  IN OUT ME_PEI_PREMEM_CONFIG **MePeiPreMemConfig
  )
{
  EFI_STATUS                      Status;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;

  ///
  /// Get Policy settings through the SiPreMemPolicy PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) MePeiPreMemConfig);
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Initialize ME PEI Config Block.

  @retval EFI_SUCCESS             ME PEI Config Block is initialized.
  @retval All other error conditions encountered when ME PEI Config Block initialized fail.
**/
STATIC
EFI_STATUS
MePeiConfigInit (
  IN OUT ME_PEI_CONFIG **MePeiConfig
  )
{
  EFI_STATUS                      Status;
  SI_POLICY_PPI                   *SiPolicyPpi;

  ///
  /// Get Policy settings through the SiPolicy PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) MePeiConfig);
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}


/**
  Read the ME policy to see if HECI timeouts are enabled.

  @retval TRUE             Timeout is enabled
  @retval FALSE            Timeout is disabled
**/
BOOLEAN
MeHeciTimeoutsEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  Status = MePeiPreMemConfigInit (&MePeiPreMemConfig);
  if (!EFI_ERROR (Status)) {
    if (MePeiPreMemConfig->HeciTimeouts == 0) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Check if HECI2 should be removed from PCI space or not

  @retval FALSE                   HECI2 should be Disabled and removed from PCI space
  @retval TRUE                    HECI2 should be enabled and not removed from PCI space
**/
BOOLEAN
MeHeci2Enabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  Status = MePeiPreMemConfigInit (&MePeiPreMemConfig);
  if (!EFI_ERROR (Status)) {
    if (MePeiPreMemConfig->HeciCommunication2 == 1) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Read the ME policy to see if HECI message check is enabled for Bios Boot Path.

  @retval TRUE             HECI message check is enabled
  @retval FALSE            HECI message check is disabled
**/
BOOLEAN
MeHeciMessageCheckEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  Status = MePeiPreMemConfigInit (&MePeiPreMemConfig);
  if (!EFI_ERROR (Status)) {
    if (MePeiPreMemConfig->DisableMessageCheck == 1) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Read the ME policy to see if MBP HOB is skipped.

  @retval TRUE             MBP HOB is skipped
  @retval FALSE            MBP HOB is not skipped
**/
BOOLEAN
MeMbpHobSkipped (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  Status = MePeiPreMemConfigInit (&MePeiPreMemConfig);
  if (!EFI_ERROR (Status)) {
    if (MePeiPreMemConfig->SkipMbpHob == 1) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Get default Heci1 BAR address from policy.

  @param[in] MeDev         The ME device to be accessed.

  @retval                  32-bit BAR address
**/
UINT32
MeGetHeciBarAddress (
  IN ME_DEVICE                    MeDev
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  Status = MePeiPreMemConfigInit (&MePeiPreMemConfig);
  if (!EFI_ERROR (Status)) {
    switch (MeDev) {
      case HECI1:
        return MePeiPreMemConfig->Heci1BarAddress;

      case HECI2:
        return MePeiPreMemConfig->Heci2BarAddress;

      case HECI3:
        return MePeiPreMemConfig->Heci3BarAddress;

      case HECI4:
        return MePeiPreMemConfig->Heci4BarAddress;

      default:
        DEBUG ((DEBUG_ERROR, "MeGetHeciBarAddress fail, invalid MeDev: %x.\n", MeDev));
        return 0;
    }
  }

  return 0;
}

/**
  Read the ME policy to see if D0I3 for HECI devices are enabled.

  @retval TRUE             D0I3 for HECI devices are enabled
  @retval FALSE            D0I3 for HECI devices are disabled
**/
BOOLEAN
MeHeciD0I3Enabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_PEI_CONFIG                   *MePeiConfig;

  Status = MePeiConfigInit (&MePeiConfig);
  if (!EFI_ERROR (Status)) {
    if (MePeiConfig->DisableD0I3SettingForHeci == 1) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Check if End of Post Message is enabled in setup options.

  @retval FALSE                   EndOfPost is disabled.
  @retval TRUE                    EndOfPost is enabled.
**/
BOOLEAN
MeEndOfPostEnabled (
  VOID
  )
{
  BOOLEAN                         Supported;


  Supported = TRUE;


  return Supported;
}

/**
  Checks if EndOfPost event already happened

  @retval TRUE                    End of post already happened
  @retval FALSE                   End of post did not happen yet
**/
BOOLEAN
MeIsAfterEndOfPost (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS            HobPtr;
  BOOLEAN                         Done;

  Done = FALSE;
  HobPtr.Guid  = GetFirstGuidHob (&gMeEopDoneHobGuid);
  if (HobPtr.Guid != NULL) {
    Done = TRUE;
  }

  DEBUG ((DEBUG_INFO, "Is EndOfPost sent in PEI: %a\n", Done ? "TRUE" : "FALSE"));
  return Done;
}

/**
  Set EndOfPost done
**/
VOID
MeSetEndOfPostDone (
  VOID
  )
{
  VOID                            *HobPtr;
  UINT32                          EopDone;

  DEBUG ((DEBUG_INFO, "MeSetEndOfPostDone in PEI\n"));
  EopDone = 1;
  HobPtr = BuildGuidDataHob (&gMeEopDoneHobGuid, &EopDone, sizeof (EopDone));
  ASSERT (HobPtr != 0);
}

