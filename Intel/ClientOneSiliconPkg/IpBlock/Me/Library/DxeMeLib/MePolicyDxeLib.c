/** @file
  Implementation file for Me Policy functionality

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

#include "MeDxeLibInternals.h"

extern GUID gMeEopDoneHobGuid;
extern GUID gMeEopDoneProtocolGuid;

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED ME_PEI_PREMEM_CONFIG          *mMePeiPreMemConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED ME_PEI_CONFIG                 *mMePeiConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED ME_DXE_CONFIG                 *mMeDxeConfig = NULL;


/**
  Initialize module varialbe - mMePeiPreMemConfig for ME PEI Config Block.

  @retval EFI_SUCCESS             mMePeiPreMemConfig is initialized.
  @retval All other error conditions encountered when mMePeiPreMemConfig initialized fail.
**/
STATIC
EFI_STATUS
MePeiPreMemConfigInit (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS            HobPtr;

  if (mMePeiPreMemConfig != NULL) {
    return EFI_SUCCESS;
  }

  //
  // Get ME PreMem Policy HOB.
  //
  HobPtr.Guid  = GetFirstGuidHob (&gMePreMemPolicyHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  if (HobPtr.Guid != NULL) {
    mMePeiPreMemConfig = (ME_PEI_PREMEM_CONFIG *) GET_GUID_HOB_DATA (HobPtr.Guid);
    return EFI_SUCCESS;
  }

  return EFI_UNSUPPORTED;
}

/**
  Initialize module varialbe - mMePeiConfig for ME PEI Config Block.

  @retval EFI_SUCCESS             mMePeiConfig is initialized.
  @retval All other error conditions encountered when mMePeiConfig initialized fail.
**/
STATIC
EFI_STATUS
MePeiConfigInit (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS            HobPtr;

  if (mMePeiConfig != NULL) {
    return EFI_SUCCESS;
  }

  //
  // Get ME Policy HOB.
  //
  HobPtr.Guid  = GetFirstGuidHob (&gMePolicyHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  if (HobPtr.Guid != NULL) {
    mMePeiConfig = (ME_PEI_CONFIG *) GET_GUID_HOB_DATA (HobPtr.Guid);
    return EFI_SUCCESS;
  }

  return EFI_UNSUPPORTED;
}

/**
  Initialize module varialbe - mMeDxeConfig for ME DXE Config Block.

  @retval EFI_SUCCESS             mMeDxeConfig is initialized.
  @retval All other error conditions encountered when mMeDxeConfig initialized fail.
**/
STATIC
EFI_STATUS
MeDxeConfigInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_POLICY_PROTOCOL              *DxeMePolicy;

  if (mMeDxeConfig != NULL) {
    return EFI_SUCCESS;
  }

  DxeMePolicy = NULL;
  Status = gBS->LocateProtocol (&gDxeMePolicyGuid, NULL, (VOID **) &DxeMePolicy);
  if (EFI_ERROR (Status) || (DxeMePolicy == NULL)) {
    DEBUG ((DEBUG_ERROR, "No ME Policy Protocol available"));
    return EFI_UNSUPPORTED;
  }

  Status = GetConfigBlock ((VOID *) DxeMePolicy, &gMeDxeConfigGuid, (VOID *) &mMeDxeConfig);
  ASSERT_EFI_ERROR (Status);

  return Status;
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
  EFI_STATUS                      Status;

  Status = MePeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return TRUE;
  }

  Supported = TRUE;


  return Supported;
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

  Status = MePeiPreMemConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if (mMePeiPreMemConfig->HeciCommunication2 == 1) {
    return TRUE;
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

  Status = MePeiPreMemConfigInit ();
  if (EFI_ERROR (Status)) {
    return TRUE;
  }

  if (mMePeiPreMemConfig->DisableMessageCheck == 1) {
    return FALSE;
  }

  return TRUE;
}

/**
  Show Me Error message. This is used to support display error message on the screen for localization
  description

  @param[in] MsgId                Me error message ID for displaying on screen message

**/
VOID
MeReportError (
  IN ME_ERROR_MSG_ID              MsgId
  )
{
  EFI_STATUS                      Status;

  Status = MeDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return;
  }

  if (mMeDxeConfig->MeReportError != NULL) {
    mMeDxeConfig->MeReportError (MsgId);
  }

  return;
}

/**
  Check if MeFwDowngrade is enabled in setup options.

  @retval FALSE                   MeFwDowngrade is disabled.
  @retval TRUE                    MeFwDowngrade is enabled.
**/
BOOLEAN
MeFwDowngradeSupported (
  VOID
  )
{
  EFI_STATUS                      Status;

  Status = MeDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if (mMeDxeConfig->MeFwDownGrade == 1) {
    return TRUE;
  }

  return FALSE;
}

/**
  Return BIOS setup option status of Extended CSME Measured Boot.

  @retval FALSE      Extend CSME Measured Boot is disabled in Setup.
  @retval TRUE       Extend CSME Measured Boot is enabled in Setup.
**/
BOOLEAN
IsExtendedMeasuredBootEnabled (
  VOID
  )
{
  EFI_STATUS     Status;

  Status = MeDxeConfigInit();
  if (EFI_ERROR(Status)) {
    return FALSE;
  }

  if (mMeDxeConfig->ExtendMeMeasuredBoot == 1) {
    return TRUE;
  }

  return FALSE;
}

/**
  Check if Core Bios Done Message is enabled in setup options.

  @retval FALSE                   Core Bios Done is disabled.
  @retval TRUE                    Core Bios Done is enabled.
**/

BOOLEAN
MeCoreBiosDoneEnabled (
  VOID
  )
{
  BOOLEAN                         Supported;
  EFI_STATUS                      Status;

  Status = MeDxeConfigInit ();
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Supported = FALSE;
  if (mMeDxeConfig->CoreBiosDoneEnabled == 1) {
    Supported = TRUE;
  }

  return Supported;
}

/**
  Read the ME policy to see if HECI timeouts are enabled.

  @retval FALSE                   HECI timeouts is disabled.
  @retval TRUE                    HECI timeouts is enabled.
**/
BOOLEAN
MeHeciTimeoutsEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  Status = MePeiPreMemConfigInit ();
  if (EFI_ERROR (Status)) {
    return TRUE;
  }

  if (mMePeiPreMemConfig->HeciTimeouts == 0) {
    return FALSE;
  }

  return TRUE;
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

  Status = MePeiConfigInit ();
  if (EFI_ERROR (Status)) {
    return TRUE;
  }

  if (mMePeiConfig->DisableD0I3SettingForHeci == 1) {
    return FALSE;
  }

  return TRUE;
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
  EFI_STATUS                      Status;
  EFI_PEI_HOB_POINTERS            HobPtr;
  BOOLEAN                         Done;
  VOID                            *Interface;

  Done = FALSE;

  HobPtr.Guid  = GetFirstGuidHob (&gMeEopDoneHobGuid);
  if (HobPtr.Guid != NULL) {
    Done = TRUE;
  }

  if (Done == FALSE) {
    Status = gBS->LocateProtocol (&gMeEopDoneProtocolGuid, NULL, (VOID **)&Interface);
    if (!EFI_ERROR (Status)) {
      Done = TRUE;
    }
    DEBUG ((DEBUG_INFO, "Locate MeEopDone Protocol, Status: %r\n", Status));
  }

  DEBUG ((DEBUG_INFO, "Is EndOfPost sent in DXE: %a\n", Done ? "TRUE" : "FALSE"));
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
  EFI_STATUS                      Status;
  EFI_HANDLE                      Handle;

  DEBUG ((DEBUG_INFO, "MeSetEndOfPostDone in DXE\n"));
  //
  // Install the Protocol into a new handle.
  //
  Handle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gMeEopDoneProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  ASSERT (Status == EFI_SUCCESS);
}


