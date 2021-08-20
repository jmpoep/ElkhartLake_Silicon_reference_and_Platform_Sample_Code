/** @file
  The implementation about Me ReadyToBoot common functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2020 Intel Corporation.

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
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/DxeMeLib.h>
#include <Library/HobLib.h>
#include <Library/HeciInitLib.h>
#include "MeInit.h"
#include <Protocol/Wdt.h>
#include <PchResetPlatformSpecific.h>
#include <Library/PmcPrivateLib.h>
#include <Protocol/AmtReadyToBoot.h>
#include <MeBiosPayloadHob.h>
#include <Library/BootMediaLib.h>
#include <MePeiConfig.h>

/**
  Dummy return for Me signal event use

  @param[in] Event                The event that triggered this notification function
  @param[in] Context              Pointer to the notification functions context
**/
VOID
EFIAPI
MeEmptyEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  gBS->CloseEvent (Event);
}


/**
  Performs End of Post related actions.

  @retval TRUE    Error has occured, need to disable HECI1
  @retval FALSE   HECI1 interface needs to remain enabled
**/
BOOLEAN
SendEndOfPost (
  VOID
  )
{
  EFI_STATUS     Status;
  UINT32         RequestedActions;
  WDT_PROTOCOL   *WdtProtocol;
  PCH_RESET_DATA ResetData;

  RequestedActions = HeciEopStatusSuccess;
  Status = MeEndOfPostEvent (&RequestedActions);
  MeSetEndOfPostDone ();
  if (EFI_ERROR (Status)) {
    MeReportError (MSG_EOP_ERROR);
    return TRUE;
  } else if (RequestedActions == HeciEopPerformGlobalReset) {
    Status = gBS->LocateProtocol (&gWdtProtocolGuid, NULL, (VOID **) &WdtProtocol);
    if (!EFI_ERROR (Status)) {
      WdtProtocol->AllowKnownReset ();
    }
    DEBUG ((DEBUG_INFO, "%a - Global Reset requested by FW EOP ACK %r\n", __FUNCTION__, Status));
    CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
    gRT->ResetSystem (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);
  }
  return FALSE;
}

/**
  Send Optional Heci Command.
**/
VOID
SendOptionalHeciCommand (
  VOID
  )
{
  ME_PEI_CONFIG             *MePeiConfig;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  EFI_HOB_GUID_TYPE         *GuidHob;
  UINT32                    UnconfigOnRtcClear = 0;

  DEBUG ((DEBUG_INFO, "SendOptionalHeciCommand\n"));

  MbpHob  = NULL;
  GuidHob = NULL;

  MbpHob  = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  GuidHob = GetFirstGuidHob (&gMePolicyHobGuid);
  if (MbpHob != NULL && GuidHob != NULL) {
    MePeiConfig = GET_GUID_HOB_DATA (GuidHob);
    if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available == 1) {
      UnconfigOnRtcClear = MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState;
      if ((MePeiConfig->MeUnconfigOnRtcClear == 1) && (UnconfigOnRtcClear == DisableState)) {
        UnconfigOnRtcClear = EnableState;
        HeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      } else if ((MePeiConfig->MeUnconfigOnRtcClear == 0) && (UnconfigOnRtcClear == EnableState)) {
        UnconfigOnRtcClear = DisableState;
        HeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      }
    }
  }
}

/**
  To perform Me ReadyToBoot event function.
**/
VOID
MeReadyToBoot (
  VOID
  )
{
  ME_BIOS_BOOT_PATH               MeBiosPath;
  BOOLEAN                         MeDisable;
  EFI_STATUS                      Status;
  EFI_EVENT                       MePlatformReadyToBootEvent;
  EFI_HANDLE                      *Handles;
  UINTN                           Index;
  UINTN                           Count;
  AMT_READY_TO_BOOT_PROTOCOL      *AmtReadyToBoot;
  UINT32                          MeStatus;

  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));

  ///
  /// We will trigger all events in order
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gAmtReadyToBootProtocolGuid,
                  NULL,
                  &Count,
                  &Handles
                  );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < Count; Index++) {
      Status = gBS->HandleProtocol (Handles[Index], &gAmtReadyToBootProtocolGuid, (VOID **) &AmtReadyToBoot);
      ASSERT_EFI_ERROR (Status);
      AmtReadyToBoot->Signal ();
    }
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  MeEmptyEvent,
                  NULL,
                  &gMePlatformReadyToBootGuid,
                  &MePlatformReadyToBootEvent
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    gBS->SignalEvent (MePlatformReadyToBootEvent);
  }

  ///
  /// Check for ME Error before HECI1 gets disabled
  ///
  HeciGetMeStatus (&MeStatus);
  if (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_DISABLE_WAIT) {
    MeReportError (MSG_PLAT_DISABLE_WAIT);
  }

  MeDisable = FALSE;
  MeBiosPath = CheckMeBootPath ();
  switch (MeBiosPath) {
    case SecoverJmprPath:
    case SecoverMeiMsgPath:
    case SwTempDisablePath:
      ///
      /// If ME is running in those ME-BIOS paths - hide HECI1 prior to boot
      ///
      MeDisable = TRUE;
      break;
    case NormalPath:
      ///
      /// Send EoP message for paths where HECI1 remains enabled - this is crucial for platform security
      ///
      if (MeEndOfPostEnabled ()) {
        if (BootMediaIsUfs ()) {
          SendOptionalHeciCommand ();
        }
        MeDisable = SendEndOfPost ();
      }
      break;
    case RecoveryPath:
    case ErrorPath:
      ///
      /// Send EoP message for paths where HECI1 remains enabled - this is crucial for platform security
      ///
      if (MeEndOfPostEnabled ()) {
        MeDisable = SendEndOfPost ();
      }
      break;
    default:
      ///
      /// In other ME-BIOS paths HECI1 has already been disabled in PEI Post Mem
      ///
      break;
  }

#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  ///
  /// PMIR Configuration
  ///
  LockConfig ();
#endif

  if (MeDisable) {
    SetD0I3Bit (HECI1);
  }
  PmcDisableMeDevices (MeDisable);
}
