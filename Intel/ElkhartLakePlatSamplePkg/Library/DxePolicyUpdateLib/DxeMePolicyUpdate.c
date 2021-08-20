/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2019 Intel Corporation.

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

#include <PiDxe.h>
#include <SetupVariable.h>
#include <Setup/MeSetup.h>
#include <Guid/EventGroup.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/MePolicy.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/ConfigBlockLib.h>
#include <MePeiConfig.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DxeMeLib.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>

#define HECI_MSG_DELAY                 2000000  ///< show warning msg and stay for 2 seconds.

/**
  This is to display localized message in the console. This is
  used to display message strings in local language. To display
  the message, the routine will check the message ID and ConOut
  the message strings.

  @param[in] MsgId                Me error message ID for displaying on screen message

**/
VOID
ShowMeReportError (
  IN ME_ERROR_MSG_ID              MsgId
  )
{
  UINTN            MsgDelay;

  MsgDelay = HECI_MSG_DELAY;
  gST->ConOut->ClearScreen (gST->ConOut);

  switch (MsgId) {
    case MSG_EOP_ERROR:
      gST->ConOut->OutputString (gST->ConOut, L"Error sending End Of Post message to ME: HECI disabled, proceeding with boot!\n");
      break;

    case MSG_ME_FW_UPDATE_FAILED:
      gST->ConOut->OutputString (gST->ConOut, L"ME FW Update Failed, please try again!\n");
      break;

    case MSG_HMRFPO_LOCK_FAILURE:
      gST->ConOut->OutputString (gST->ConOut, L"(A7) Me FW Downgrade - Request MeSpiLock Failed\n");
      break;

    case MSG_HMRFPO_UNLOCK_FAILURE:
      gST->ConOut->OutputString (gST->ConOut, L"(A7) Me FW Downgrade - Request MeSpiEnable Failed\n");
      break;

    case MSG_ME_FW_UPDATE_WAIT:
      gST->ConOut->OutputString (gST->ConOut, L"Intel(R) Firmware Update is in progress. It may take up to 90 seconds. Please wait.\n");
      break;

    case MSG_ILLEGAL_CPU_PLUGGED_IN:
      gST->ConOut->OutputString (gST->ConOut, L"\n\n\rAn unsupported CPU/PCH configuration has been identified.\n");
      gST->ConOut->OutputString (gST->ConOut, L"\rPlease refer to the Platform Validation Matrix\n\rfor supported CPU/PCH combinations.");
      break;

    case MSG_PLAT_DISABLE_WAIT:
      gST->ConOut->OutputString (gST->ConOut, L"WARNING! Firmware encountered errors and will reboot the platform in 30 minutes.");
      MsgDelay = 5 * HECI_MSG_DELAY;
      break;

    default:
      DEBUG ((DEBUG_ERROR, "This Message Id hasn't been defined yet, MsgId = %x\n", MsgId));
      break;
  }

  gBS->Stall (MsgDelay);
}

/**
  Functions performs HECI exchange with FW to update MePolicy settings.

  @param[in] Event         A pointer to the Event that triggered the callback.
  @param[in] Context       A pointer to private data registered with the callback function.

**/
VOID
EFIAPI
UpdateMeSetupCallback (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  EFI_STATUS                      Status;
  ME_SETUP                        MeSetup;
  ME_INFO_SETUP_DATA              MeInfoSetupData;
  EFI_HOB_GUID_TYPE               *GuidHob;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;
  HECI_PROTOCOL                   *Heci;
  UINTN                           Size;
  UINT32                          SetupAttr;
  UINT32                          MeMode;
  ME_PEI_CONFIG                   *MePeiConfig;
  UINT32                          UnconfigOnRtcClear;

  DEBUG ((DEBUG_INFO, "UpdateMeSetup event start\n"));

  //
  // Default ME Mode
  //
  MeMode             = ME_MODE_FAILED;
  MbpHob             = NULL;
  GuidHob            = NULL;
  UnconfigOnRtcClear = 0;

  ZeroMem (&MeInfoSetupData, sizeof(MeInfoSetupData));
  //
  // Get Mbp Hob
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    MeInfoSetupData.MeMajor      = MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
    MeInfoSetupData.MeMinor      = MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
    MeInfoSetupData.MeHotFix     = MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;
    MeInfoSetupData.MeBuildNo    = MbpHob->MeBiosPayload.FwVersionName.BuildVersion;
  }

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (!EFI_ERROR (Status)) {
    Status = Heci->GetMeMode (&MeMode);
    ASSERT_EFI_ERROR(Status);
  }

  MeInfoSetupData.MeFirmwareInfo = (UINT8) MeMode;

  Status = gRT->SetVariable (L"MeInfoSetup", &gMeInfoSetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, sizeof(MeInfoSetupData), &MeInfoSetupData);
  ASSERT_EFI_ERROR(Status);

  SetupAttr = 0;
  Size = sizeof (ME_SETUP);
  Status = gRT->GetVariable (L"MeSetup", &gMeSetupVariableGuid, &SetupAttr, &Size, &MeSetup);

  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR(Status)) {
    //
    // FW Downgrade BIOS Setup Option is only valid for one boot
    //
    MeSetup.MeFwDowngrade = 0;

    //
    // Reset Firmware Info
    //
    MeSetup.MeFirmwareInfo = MeInfoSetupData.MeFirmwareInfo;

    MeSetup.UnconfigOnRtcAvailable = 0;
    MeSetup.MeImageType            = 0;
    MeSetup.Heci3Enabled           = 0;

    if (MbpHob != NULL) {
      //
      // Set Image Type for MEBx disposition
      //
      MeSetup.MeImageType = (UINT8) MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType;

      //
      // Update ME Unconfig on RTC Clear availability
      //
      if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available) {
        MeSetup.UnconfigOnRtcAvailable = 1;
        GuidHob = GetFirstGuidHob (&gMePolicyHobGuid);
        if (GuidHob != NULL) {
          MePeiConfig = GET_GUID_HOB_DATA (GuidHob);
          if (MePeiConfig->MeUnconfigOnRtcClear == 2) {
            //
            // ME Unconfig item in setup menu could be destroyed because of Secondary NvRam Init.
            // If item is not valid, restore it from DisUnconfigOnRtcClearState.
            //
            UnconfigOnRtcClear = MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState;
            MeSetup.MeUnconfigOnRtcClear = (UnconfigOnRtcClear == EnableState)? 1 : 0;
          }
        }
      } else {
        Status = HeciGetUnconfigOnRtcClearDisableMsg (&UnconfigOnRtcClear);
        if (!EFI_ERROR (Status)) {
          MeSetup.MeUnconfigOnRtcClear = (UnconfigOnRtcClear == EnableState)? 1 : 0;
        }
      }

      //
      // Retrieve IntegratedTouch capability to report whether HECI3 should be enabled for S3 boot mode.
      //
      if ((MbpHob->MeBiosPayload.FwCapsSku.Available == 1) &&
          (MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntegratedTouch == 1)) {
        MeSetup.Heci3Enabled = 1;
      }

      //
      // Auto commit Anti-Rollback SVN enabled
      //
      if ((MbpHob->MeBiosPayload.ArbSvnState.Available == 1) && (MeSetup.AutoArbSvnCommit == 1)) {
        if ((MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.Flags && BIT0) ||
            (MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.MinCseArbSvn < MbpHob->MeBiosPayload.ArbSvnState.ArbSvnData.CurrCseArbSvn)) {
          Status = HeciArbSvnCommitMsg ();
        }
      }
    }

    //
    // Update AMT settings
    //
    MeSetup.UnConfigureMe  = 0;
    MeSetup.AmtCiraRequest = 0;
    if (MeSetup.MeImageType != ME_IMAGE_CORPORATE_SKU_FW && MeMode == ME_MODE_NORMAL) {
      MeSetup.Amt = 0;
    }

    Status = gRT->SetVariable (L"MeSetup", &gMeSetupVariableGuid, SetupAttr, sizeof (ME_SETUP), &MeSetup);

    ASSERT_EFI_ERROR (Status);
  }
  gBS->CloseEvent (Event);
}

/**
  Update the ME Policy Library

  @param[in] DxeMePolicy          ME Policy in DXE phase

  @retval EFI_SUCCESS             Initialization complete.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
UpdateDxeMePolicy (
  IN OUT  ME_POLICY_PROTOCOL *DxeMePolicy
  )
{
  EFI_STATUS    Status;
  ME_DXE_CONFIG *MeDxeConfig;
  ME_SETUP      MeSetup;
  UINTN         Size;
  EFI_EVENT     EndOfDxeEvent;

  DEBUG ((DEBUG_INFO, "%a\n", __FUNCTION__));

  Size = sizeof (ME_SETUP);
  Status = gRT->GetVariable (L"MeSetup", &gMeSetupVariableGuid, NULL, &Size, &MeSetup);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) DxeMePolicy, &gMeDxeConfigGuid, (VOID *) &MeDxeConfig);
    ASSERT_EFI_ERROR (Status);

    MeDxeConfig->MeFwDownGrade        = MeSetup.MeFwDowngrade;
    MeDxeConfig->MeJhiSupport         = MeSetup.MeJhiSupport;
    MeDxeConfig->CoreBiosDoneEnabled  = MeSetup.CoreBiosDoneEnabled;
    MeDxeConfig->ExtendMeMeasuredBoot = MeSetup.ExtendMeMeasuredBoot;
    MeDxeConfig->MeReportError        = ShowMeReportError;
  }

  //
  // Register End of DXE event
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  UpdateMeSetupCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "%a done\n", __FUNCTION__));
  return Status;
}

