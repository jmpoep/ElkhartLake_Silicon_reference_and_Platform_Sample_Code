/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Features/Icc/IccPlatformDxe/IccPlatform.h>
#include "IccSetup.h"
#include <Protocol/HiiConfigAccess.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeMeLib.h>
#include <Library/HiiLib.h>
#include <PlatformNvRamHookLib.h>
#include <SetupPrivate.h>
#include <IccSetupData.h>
#include "PlatformBoardId.h"
#include "OemSetup.h"
#include <Library/ConfigBlockLib.h>
#include <WdtAppVariable.h>

#define HZ_TO_10KHZ     10000

static ICC_CLOCK_SETTINGS mSettingsBclk;
static ICC_CLOCK_SETTINGS mDefaultsBclk;
static BOOLEAN            mProfileChanged = FALSE;
static BOOLEAN            gClockChanged = 0;
static HECI_PROTOCOL      *mHeci = NULL;

GLOBAL_REMOVE_IF_UNREFERENCED ICC_MBP_DATA               gIccMbpData;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_HANDLE             gHiiHandle;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                    gIccReset = FALSE;


VOID
UpdateClockData (
  IN     ICC_CLOCK_SETTINGS             ClockSettings,
     OUT ICC_SETUP_DATA                 *SetupPtr
  )
{
  SetupPtr->Frequency  = (UINT16) ( (ClockSettings.Freq + (HZ_TO_10KHZ/2)) / HZ_TO_10KHZ);
  SetupPtr->Spread = ClockSettings.SscPercent;
}

/**
  Extract clock data from ICC setup variable.

  @param[in]  IccSetupPtr              Pointer to the ICC_SETUP_DATA buffer.
  @param[out] ClockSettings            Pointer to the ICC_CLOCK_SETTINGS buffer.
**/
VOID
ExtractClockData (
  IN     ICC_SETUP_DATA          *IccSetupPtr,
     OUT ICC_CLOCK_SETTINGS      *ClockSettings
  )
{
  ClockSettings->UserFreq    = HZ_TO_10KHZ * IccSetupPtr->Frequency;
  ClockSettings->SscPercent  = IccSetupPtr->Spread;
  ClockSettings->SscMode     = ICC_SSC_DOWN;
  ClockSettings->ReqClock    = CLOCK1;
}

/**
  Reads string from Hii database. Allocates memory.
  Caller of this function is responsible for freeing it.

**/
VOID
GetStringFromHii (
  IN  EFI_STRING_ID StringId,
  OUT UINT16        **BufferPtr
  )
{
  CHAR16*    StrBuffer = 0;
  UINTN      StrLen = 0;

  HiiLibGetString(gHiiHandle, StringId, StrBuffer, &StrLen);
  StrBuffer = AllocatePool(StrLen);
  ASSERT (StrBuffer != NULL);
  if (StrBuffer != NULL) {
    HiiLibGetString(gHiiHandle, StringId, StrBuffer, &StrLen);
  }
  *BufferPtr = StrBuffer;
}

/**
  Checks if provided settings are equal to clock's defaults

**/
BOOLEAN
AreSettingsAtDefault (
  IN ICC_CLOCK_SETTINGS   *Requested
  )
{
  ICC_CLOCK_SETTINGS Default;
  CopyMem (&Default, &mDefaultsBclk, sizeof (ICC_CLOCK_SETTINGS));
  if (Requested->Freq        == Default.Freq   &&
      Requested->SscMode     == Default.SscMode     &&
      Requested->SscPercent  == Default.SscPercent ) {
    return TRUE;
  } else {
    return FALSE;
  }
}

EFI_STATUS
IccCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION Action,
  IN EFI_QUESTION_ID KeyValue,
  IN UINT8 Type,
  IN EFI_IFR_TYPE_VALUE *Value,
  OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
  )
{
  //
  // Cannot access ICC menu after EOP.
  //
  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  switch (KeyValue) {
    case KEY_ICC_FREQ2:
      if (Action >= EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
        gClockChanged = TRUE;
        Value->u16 = (UINT16)(mDefaultsBclk.Freq / HZ_TO_10KHZ);
        return EFI_SUCCESS;
      } else if (Action == EFI_BROWSER_ACTION_CHANGING) {
        gClockChanged = TRUE;
        if (Value->u16 < (UINT16)(mSettingsBclk.MinFreq / HZ_TO_10KHZ)) {
          Value->u16 = (UINT16)(mSettingsBclk.MinFreq / HZ_TO_10KHZ);
        } else if (Value->u16 > (UINT16)(mSettingsBclk.MaxFreq / HZ_TO_10KHZ)) {
          Value->u16 = (UINT16)(mSettingsBclk.MaxFreq / HZ_TO_10KHZ);
        }
        return EFI_SUCCESS;
      } else {
        return EFI_UNSUPPORTED;
      }

    case KEY_ICC_SPREAD2:
      if (Action >= EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
        gClockChanged = TRUE;
        Value->u8 = mDefaultsBclk.SscPercent;
        return EFI_SUCCESS;
      } else if (Action == EFI_BROWSER_ACTION_CHANGING) {
        gClockChanged = TRUE;
        if (Value->u8 > mSettingsBclk.MaxSscPercent) {
          Value->u8 = (UINT8) mSettingsBclk.MaxSscPercent;
        }
        return EFI_SUCCESS;
      } else {
        return EFI_UNSUPPORTED;
      }

    default:
      return EFI_UNSUPPORTED;
  }
}

VOID
UpdateSubmenuStrings (
  IN ICC_CLOCK_SETTINGS ClockSettings
  )
{
  CHAR16  *TempBuffer;
  UINT16  StrFreqRange;
  UINT16  StrMaxSpread;
  UINT16  StrSpreadAdjust;

  StrFreqRange    =  STR_ICC_CLOCK1_FREQ_RANGE_TEXT;
  StrMaxSpread    =  STR_ICC_CLOCK1_MAX_SPREAD_TEXT;
  StrSpreadAdjust =  STR_ICC_CLOCK1_SPREAD_ADJUSTMENTS_TEXT;

  //
  // Frequency Range
  //
  InitString(gHiiHandle, STRING_TOKEN(StrFreqRange), L"%d.%02d - %d.%02d MHz",
    ClockSettings.MinFreq/1000000, ClockSettings.MinFreq%1000000, ClockSettings.MaxFreq/1000000, ClockSettings.MaxFreq%1000000);

  //
  // Maximum Spread %
  //
  InitString(gHiiHandle, STRING_TOKEN(StrMaxSpread), L"%d.%02d%%", ClockSettings.MaxSscPercent/100, ClockSettings.MaxSscPercent%100);

  //
  // Spread Mode Adjustments
  //
  if(ClockSettings.SscMode != ICC_SSC_NONE) {
    GetStringFromHii (STRING_TOKEN (STR_ICC_SSC_CHANGE_ALLOWED), &TempBuffer);
  } else {
    GetStringFromHii (STRING_TOKEN (STR_ICC_SSC_NOTHING_ALLOWED), &TempBuffer);
  }
  InitString (gHiiHandle, STRING_TOKEN (StrSpreadAdjust), TempBuffer);
  FreePool (TempBuffer);
}

/**
  Setup callback executed when user selects a ICC Profile from the BIOS UI.
  Changes visibility of other options

  @param This                   Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action                 Specifies the type of action taken by the browser.
  @param QuestionId             A unique value which is sent to the original exporting driver
                                so that it can identify the type of data to expect.
  @param Type                   The type of value for the question.
  @param Value                  A pointer to the data being sent to the original exporting driver.
  @param ActionRequest          On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS           The callback successfully handled the action.
  @retval EFI_OUT_OF_RESOURCES  Not enough storage is available to hold the variable and its data.
  @retval EFI_DEVICE_ERROR      The variable could not be saved.
  @retval EFI_UNSUPPORTED       The specified Action is not supported by the callback.
  @retval EFI_INVALID_PARAMETER The parameter of Value or ActionRequest is invalid.
**/
EFI_STATUS
EFIAPI
IccProfileCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  UINTN          Size = sizeof(ICC_SETUP_DATA);
  ICC_SETUP_DATA IccSetup;
  EFI_STRING     RequestString = NULL;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action < EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
    return EFI_UNSUPPORTED;
  }

  if (MeIsAfterEndOfPost ()) {
    return EFI_UNSUPPORTED;
  }

  if (Action >= EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
    if (gIccMbpData.ProfileSelectionAllowed) {
      //
      // Perform change only if profile is selectable by BIOS
      //
      Value->u8 = 0;
    }
  }

  //
  // sanity check: can't choose profile that doesn't exist
  //
  if (Value->u8 > gIccMbpData.NumProfiles - 1) {
    Value->u8 = gIccMbpData.NumProfiles - 1;
  }

  //
  // when profile is changed, most other icc options can't be changed before reboot. hide those options.
  //
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (ICC_SETUP_DATA, AllowAdvancedOptions), sizeof (IccSetup.AllowAdvancedOptions));
  if (mProfileChanged || (Value->u8 != gIccMbpData.Profile)) {
    HiiGetBrowserData (&gIccGuid, ICC_SETUP_DATA_C_NAME, Size, (UINT8*)&IccSetup);
    IccSetup.AllowAdvancedOptions= DONT_DISPLAY;
    HiiSetBrowserData(&gIccGuid, ICC_SETUP_DATA_C_NAME, sizeof(ICC_SETUP_DATA), (UINT8 *)&IccSetup, RequestString);
  } else if (!mProfileChanged && (Value->u8 == gIccMbpData.Profile)) {
    HiiGetBrowserData (&gIccGuid, ICC_SETUP_DATA_C_NAME, Size, (UINT8*)&IccSetup);
    IccSetup.AllowAdvancedOptions= DISPLAY;
    HiiSetBrowserData(&gIccGuid, ICC_SETUP_DATA_C_NAME, sizeof(ICC_SETUP_DATA), (UINT8 *)&IccSetup, RequestString);
  }
  FreePool(RequestString);
  return EFI_SUCCESS;
}

/**
  Allows protocol's clients to request that WDT be turned on and periodically kicked
  during BIOS execution during next boot.  Sets a nonvolatile variable that will be
  read by WdtAppPei during next boot.

  @retval     EFI_SUCCESS
  @retval     other
**/
EFI_STATUS
EFIAPI
RequestWdtAfterReboot (
  VOID
  )
{
  EFI_STATUS           Status;
  WDT_PERSISTENT_DATA  WdtPersistentData;

  WdtPersistentData.Enable = 1;
  Status = gRT->SetVariable(
                  L"WdtPersistentData",
                  &gWdtPersistentDataGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof (WDT_PERSISTENT_DATA),
                  &WdtPersistentData
                  );

  return Status;
}

/**
  Executed by setup calback function
  Based on data entered by user, sends clock change requests to ICC OverClocking
  Writing to susram or flash requires that old susram and flash contents be invalidated
  In case of any problem, messagebox is displayed so user can know what corrective action is required

  @param[in] RequestedClockSettings initial clock divider value

**/
VOID
ApplyClockSettings (
  IN ICC_CLOCK_SETTINGS   *RequestedClockSettings
  )
{
  EFI_STATUS          Status;
  UINTN               VariableSize;
  UINT32              VariableAttributes;

  Status = HeciSetIccClockSettings(RequestedClockSettings);
  DEBUG ((DEBUG_INFO, "(ICC) HeciSetIccClockSettings, Status = %r\n", Status));

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &VariableAttributes,
                  &VariableSize,
                  &mSaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  if (Status == EFI_SUCCESS) {
    //
    // Update the BclkFrequency setup option to sync with MRC and XTU
    //
    mSaSetup.BclkFrequency = RequestedClockSettings->UserFreq / HZ_TO_10KHZ;
    Status = gRT->SetVariable (
                    L"SaSetup",
                    &gSaSetupVariableGuid,
                    VariableAttributes,
                    VariableSize,
                    &mSaSetup
                    );
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, "(ICC) BclkFrequency = %d\n", mSaSetup.BclkFrequency));
    DEBUG ((DEBUG_INFO, "(ICC) BclkOverride  = %d\n", mSaSetup.BclkOverride));

    if (!AreSettingsAtDefault(RequestedClockSettings)) {
      RequestWdtAfterReboot();
    }
  }
}

VOID
DebugDumpConfig (
  IN ICC_SETUP_DATA  IccSetup
  )
{
  DEBUG ((DEBUG_INFO, "Frequency           : %d\n", IccSetup.Frequency));
  DEBUG ((DEBUG_INFO, "Spread              : %d\n", IccSetup.Spread));
  DEBUG ((DEBUG_INFO, "ShowFrequency       : %d\n", IccSetup.ShowFrequency));
  DEBUG ((DEBUG_INFO, "ShowSpread          : %d\n", IccSetup.ShowSpread));
  DEBUG ((DEBUG_INFO, "ShowProfile         : %d\n",    IccSetup.ShowProfile));
  DEBUG ((DEBUG_INFO, "Profile             : %d\n",    IccSetup.Profile));
  DEBUG ((DEBUG_INFO, "AllowAdvancedOptions: %d\n",    IccSetup.AllowAdvancedOptions));
}

VOID
InitIccStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  if(Class != ADVANCED_FORM_SET_CLASS) {return;}
  gHiiHandle = HiiHandle;
}

VOID
GetClockSettings (
  VOID
  )
{
  EFI_STATUS            Status;
  static BOOLEAN        StringInit = FALSE;

  if (MeIsAfterEndOfPost () || StringInit) {
    return;
  }

  //
  //  Get BCLK Settings
  //
  ZeroMem (&mSettingsBclk, sizeof (ICC_CLOCK_SETTINGS));

  mSettingsBclk.ReqClock = CLOCK1;
  Status = HeciGetIccClockSettings (&mSettingsBclk);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "(ICC) Get Clock Settings message failed, clock 1. Status = %r\n", Status));
    return;
  }

  StringInit = TRUE;
}

VOID
UpdateVisibility (
  ICC_SETUP_DATA* SetupPtr
  )
{
  UINT32              MeMode;
  SETUP_VOLATILE_DATA SysCfg;
  UINTN               Size;
  EFI_STATUS          Status;
  BOOLEAN             EopSent;

  Size = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (L"SetupVolatileData", &gSetupVariableGuid, NULL, &Size, &SysCfg);
  ASSERT_EFI_ERROR (Status);

  EopSent = MeIsAfterEndOfPost ();
  mHeci->GetMeMode (&MeMode);

  if (EopSent || (MeMode != ME_MODE_NORMAL)) {
    SetupPtr->AllowAdvancedOptions = DONT_DISPLAY;
  } else {
    SetupPtr->AllowAdvancedOptions = DISPLAY;
  }
  if (EopSent || gIccMbpData.ProfileSelectionAllowed == DONT_DISPLAY || (MeMode != ME_MODE_NORMAL)) {
    SetupPtr->ShowProfile = DONT_DISPLAY;
  } else {
    SetupPtr->ShowProfile = DISPLAY;
  }
  if (EopSent || mSettingsBclk.MaxFreq == mSettingsBclk.MinFreq) {
    SetupPtr->ShowFrequency= DONT_DISPLAY;
  } else {
    SetupPtr->ShowFrequency = DISPLAY;
  }
  if (EopSent || mSettingsBclk.SscMode == ICC_SSC_NONE) {
    SetupPtr->ShowSpread = DONT_DISPLAY;
  } else {
    SetupPtr->ShowSpread = DISPLAY;
  }
}

VOID
MaybeChangeProfile (
  IN UINT8 Profile
  )
{
  static UINT8 LastSavedProfile;

  if (!mProfileChanged) {
    LastSavedProfile = gIccMbpData.Profile;
  }
  if (Profile != LastSavedProfile) {
    DEBUG ((DEBUG_INFO, "(ICC) Changing profile: old %d, new %d\n", LastSavedProfile, Profile));
    HeciSetIccProfile (Profile);
    LastSavedProfile = Profile;
    mProfileChanged = TRUE;
    gIccReset = TRUE;
  }
}

VOID
IccExtractConfig (
  VOID
  )
{
  ICC_SETUP_DATA  IccSetup;
  EFI_STATUS      Status;
  UINTN           Size;

  ZeroMem ((VOID *) &IccSetup, sizeof (ICC_SETUP_DATA));
  if (!mHeci) {
    Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &mHeci);
    if (EFI_ERROR(Status)) {
      IccSetup.AllowAdvancedOptions = DONT_DISPLAY;
      IccSetup.ShowProfile = DONT_DISPLAY;
      gRT->SetVariable (
             ICC_SETUP_DATA_C_NAME,
             &gIccGuid,
             EFI_VARIABLE_BOOTSERVICE_ACCESS,
             sizeof(IccSetup),
             &IccSetup
             );
      return;
    }
  }

  Size = sizeof (IccSetup);
  Status = gRT->GetVariable (ICC_SETUP_DATA_C_NAME, &gIccGuid, NULL, &Size, &IccSetup);
  if (!EFI_ERROR (Status)) {
    //
    // if the variable exists, it means init was completed. Check for EoP only and hide everything if it's after EoP.
    //
    if (MeIsAfterEndOfPost ()) {
      IccSetup.AllowAdvancedOptions = DONT_DISPLAY;
      IccSetup.ShowProfile = DONT_DISPLAY;
      gRT->SetVariable (
             ICC_SETUP_DATA_C_NAME,
             &gIccGuid,
             EFI_VARIABLE_BOOTSERVICE_ACCESS,
             sizeof(IccSetup),
             &IccSetup
             );
    }
    return;
  }

  GetClockSettings ();

  //
  // Use data retrieved from MBP
  //
  Size = sizeof (gIccMbpData);
  Status = gRT->GetVariable (ICC_MBP_DATA_NAME, &gIccGuid, NULL, &Size, &gIccMbpData);

  IccSetup.Profile = gIccMbpData.Profile;

  UpdateClockData (mSettingsBclk, &IccSetup);
  UpdateSubmenuStrings (mSettingsBclk);
  UpdateVisibility (&IccSetup);

  gRT->SetVariable (
         ICC_SETUP_DATA_C_NAME,
         &gIccGuid,
         EFI_VARIABLE_BOOTSERVICE_ACCESS,
         sizeof(IccSetup),
         &IccSetup
         );

  DebugDumpConfig (IccSetup);

}

VOID
IccRouteConfig (
  VOID
  )
{
  EFI_STATUS                        Status;
  ICC_SETUP_DATA                    IccSetup;
  UINTN                             Size = sizeof(ICC_SETUP_DATA);
  UINTN                             VariableSize = sizeof(SA_SETUP);
  ICC_CLOCK_SETTINGS                ClockSettings;
  UINT32                            VariableAttributes;

  ZeroMem ((VOID *) &IccSetup, sizeof (ICC_SETUP_DATA));
  if (MeIsAfterEndOfPost () || mHeci == NULL) {
    return;
  }

  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &VariableAttributes,
                  &VariableSize,
                  &mSaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  gRT->GetVariable (ICC_SETUP_DATA_C_NAME, &gIccGuid, NULL, &Size, &IccSetup);
  MaybeChangeProfile (IccSetup.Profile);

  ZeroMem (&ClockSettings, sizeof (ICC_CLOCK_SETTINGS));
  if (!mProfileChanged && IccSetup.AllowAdvancedOptions) {
    //
    //  Update BCLK settings if needed
    //
    if (IccSetup.AllowAdvancedOptions && gClockChanged) {
      gIccReset = TRUE;
      gClockChanged = FALSE;
      ExtractClockData (&IccSetup, &ClockSettings);

      ///
      /// Set permanent and applied on warm reset flags based on BclkChangeType
      ///
      if (mSaSetup.BclkChangeWarmReset) {
        ClockSettings.CurrentFlags.Flags.Type = 0;
        ClockSettings.CurrentFlags.Flags.ForcePowerFlow = 1;
        gIccReset = TRUE;
      } else {
        switch (mSaSetup.BclkChangeContinues) {
          case ICC_BCLK_PERM_NO_WR:
            ClockSettings.CurrentFlags.Flags.Type = 0;
            ClockSettings.CurrentFlags.Flags.ForcePowerFlow = 0;
            gIccReset = FALSE;
            break;

          case ICC_BCLK_REAL_TIME:
            ClockSettings.CurrentFlags.Flags.Type = 1;
            ClockSettings.CurrentFlags.Flags.ForcePowerFlow = 0;
            gIccReset = FALSE;
            break;

           default:
            break;
        }
      }
      ApplyClockSettings (&ClockSettings);
    }
  }

}
