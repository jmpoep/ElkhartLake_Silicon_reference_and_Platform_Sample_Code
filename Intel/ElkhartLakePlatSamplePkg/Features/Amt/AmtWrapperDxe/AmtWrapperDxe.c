/**@file
  AMT Wrapper Implementation.

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
#include "AmtWrapperDxe.h"

#define CHAR_DATA_LINK_ESCAPE        0x10
#define NUMBER_OF_HOTKEY_CTRL_P      5

GLOBAL_REMOVE_IF_UNREFERENCED AMT_WRAPPER_PROTOCOL mAmtWrapperInstance = {
  AmtWrapperGetSolDevicePath,
  AmtWrapperSet,
  AmtWrapperBootOptionExist,
  AmtWrapperEnableStorageRedir,
  AmtWrapperEnterSetup,
  AmtWrapperPauseBoot,
  AmtWrapperEnableKvm,
  AmtWrapperEnableSecureErase,
  AmtWrapperConsoleLocked,
  AmtWrapperEnableSol,
  AmtWrapperBdsBootViaAsf,
  AmtWrapperGetNextAmtSetupPrompt,
  AmtWrapperDetermineSetupHotKey,
  AmtWrapperGetSupportedHotkeys
};

GLOBAL_REMOVE_IF_UNREFERENCED UINTN                                    mEnterRemoteAssistance = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                                    mEnterMebxSetup = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                    mFwImageType;

GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH mSerialOverLanDevicePath = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8)(sizeof (PCI_DEVICE_PATH)),
        (UINT8)((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    SOL_FUNCTION_NUMBER,
    ME_DEVICE_NUMBER
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_UART_DP,
      {
        (UINT8)(sizeof (UART_DEVICE_PATH)),
        (UINT8)((sizeof (UART_DEVICE_PATH)) >> 8)
      }
    },
    0,
    115200,
    8,
    1,
    1
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_VENDOR_DP,
      {
        (UINT8)(sizeof (VENDOR_DEVICE_PATH)),
        (UINT8)((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    DEVICE_PATH_MESSAGING_PC_ANSI
  },
  gEndEntire
};

//
// Driver entry point
//

//
// Function implementations
//

BOOLEAN
IsCtrlKey (
  IN UINT32 KeyShiftState
  )
{
  if ((KeyShiftState & EFI_SHIFT_STATE_VALID) && (KeyShiftState & (EFI_LEFT_CONTROL_PRESSED | EFI_RIGHT_CONTROL_PRESSED))) {
    return TRUE;
  } else {
    return FALSE;
  }
}


BOOLEAN
IsAltKey (
  IN UINT32 KeyShiftState
  )
{
  if ((KeyShiftState & EFI_SHIFT_STATE_VALID) && (KeyShiftState & (EFI_RIGHT_ALT_PRESSED | EFI_LEFT_ALT_PRESSED))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOLEAN
IsPKey (
  IN CHAR16 UnicodeChar
  )
{
  if (UnicodeChar == L'p' || UnicodeChar == L'P') {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Update AMT DXE config block to enter MEBX.
**/
VOID
EnterMebxSetup (
  VOID
  )
{
  EFI_STATUS             Status;
  AMT_POLICY_PROTOCOL    *AmtPolicy;
  AMT_DXE_CONFIG         *AmtDxeConfig;

  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);
    AmtDxeConfig->AmtbxHotkeyPressed = 1;
    AmtDxeConfig->CiraRequest        = 0;
  }

  DEBUG ((DEBUG_INFO, "Entering MEBX Setup\n"));
}

/**
  Update AMT DXE config block to enter remote assistance.
**/
VOID
EnterRemoteAssistance (
  VOID
  )
{
  EFI_STATUS             Status;
  AMT_POLICY_PROTOCOL    *AmtPolicy;
  AMT_DXE_CONFIG         *AmtDxeConfig;

  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);
    AmtDxeConfig->AmtbxHotkeyPressed = 1;
    AmtDxeConfig->CiraRequest        = 1;
  }

  DEBUG ((DEBUG_INFO, "Entering Remote Assistance\n"));
}

/**
  Check if Remote Assistance Prompt can be displayed.

  @retval TRUE           Display Remote Assistance Prompt.
  @retval FALSE          Do not display Remote Assistance Prompt.
**/
BOOLEAN
DisplayRemoteAssistancePrompt (
  VOID
  )
{
  EFI_STATUS             Status;
  AMT_POLICY_PROTOCOL    *AmtPolicy;
  AMT_DXE_CONFIG         *AmtDxeConfig;
  EFI_HOB_GUID_TYPE      *GuidHob;
  MEBX_DATA_HOB          *MebxData;

  MebxData     = NULL;
  AmtDxeConfig = NULL;
  GuidHob = GetFirstGuidHob (&gAmtMebxDataGuid);
  if (GuidHob == NULL) {
    DEBUG ((DEBUG_INFO, "Cannot find MEBX Hob, remote Assistance not supported\n"));
    return FALSE;
  }

  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Locate AmtPolicy fail, remote Assistance not supported\n"));
    return FALSE;
  }

  Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
  ASSERT_EFI_ERROR (Status);

  MebxData = (MEBX_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
  if ((AmtDxeConfig->AmtbxSelectionScreen == 0) && (MebxData->RemoteAssistanceTriggerAvailablilty == 1)) {
    return TRUE;
  }


  DEBUG ((DEBUG_INFO, "Remote Assistance not supported\n"));
  return FALSE;
}


/**
  Check if BIOS hot key can be enabled.

  @retval True           BIOS hot key can be enabled.
  @retval False          BIOS hot key can not be enabled.
**/
BOOLEAN
IsBiosHotkeyEnabled (
  VOID
  )
{
  EFI_STATUS     Status;
  HECI_PROTOCOL  *Heci;
  UINT32         MeMode;

  Heci = NULL;
  MeMode = ME_MODE_TEMP_DISABLED;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  if ((mFwImageType != IntelMeConsumerFw) && (MeMode == ME_MODE_NORMAL)) {
    return TRUE;
  }

  return FALSE;
}

/**
  Get AMT Setup Promt String.

  @param[out] String            Setup promt string.

  @retval EFI_SUCCESS           Get Setup Promt String successfully.
  @retval EFI_NOT_FOUND         Setup Promt String is not found.
  @retval EFI_UNSUPPORTED       Get Setup Promt String is not supported.
  @retval EFI_INVALID_PARAMETER One of parameters is NULL.
**/
EFI_STATUS
EFIAPI
AmtWrapperGetNextAmtSetupPrompt (
  OUT     CHAR16    **String
  )
{
  STATIC UINTN   PromptIndex = 0;
  UINTN          StringCounts;
  EFI_STRING     SetupPrompt[] = {
    L"Press [CTRL+P] to enter MEBx Setup Menu.",
    L"Press [CTRL+ALT+F1] to enter MEBx Remote Assistance."
  };

  if (String == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *String = NULL;

  if (AsfIsSolEnabled () || AsfIsKvmEnabled () || !IsBiosHotkeyEnabled ()) {
    //
    // Skip setup prompt if ASF SOL or KVM enabled.
    //
    return EFI_UNSUPPORTED;
  }

  StringCounts = DisplayRemoteAssistancePrompt ()? sizeof (SetupPrompt) / sizeof (EFI_STRING) : sizeof (SetupPrompt) / sizeof (EFI_STRING) - 1;

  if (PromptIndex < StringCounts) {
    *String = SetupPrompt [PromptIndex];
    PromptIndex++;
    return EFI_SUCCESS;
  } else {
    PromptIndex = 0;
    return EFI_NOT_FOUND;
  }
}

/**
  Determine if AMT hot key is pressed.
  Ctrl+ALT+F1  : Scan    = 0x0B, Shift = 0x3C
  Ctrl+P       : Unicode = 0x10/L'p', Shift = 0x0C

  @param[in] KeyData            Hot Key Data.

  @retval EFI_SUCCESS           AMT hot key is pressed.
  @retval EFI_NOT_FOUND         AMT hot key is not pressed.
**/
EFI_STATUS
EFIAPI
AmtWrapperDetermineSetupHotKey (
  IN EFI_KEY_DATA                       *KeyData
  )
{
  //
  // React to hotkey once per boot only
  //
  if (mEnterMebxSetup || mEnterRemoteAssistance) {
    return EFI_NOT_FOUND;
  }

  if (AsfIsSolEnabled () || AsfIsKvmEnabled () || !IsBiosHotkeyEnabled ()) {
    //
    // Skip AMT hot key check if ASF SOL or KVM enabled.
    //
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO, "<Scan=0x%X><Unicode=0x%X>\n", KeyData->Key.ScanCode, KeyData->Key.UnicodeChar));
  DEBUG ((DEBUG_INFO, "<ShiftState=0x%X><ToggleState=0x%X>\n", KeyData->KeyState.KeyShiftState, KeyData->KeyState.KeyToggleState));

  if (KeyData->Key.UnicodeChar == CHAR_DATA_LINK_ESCAPE ||
     (IsPKey (KeyData->Key.UnicodeChar) && IsCtrlKey (KeyData->KeyState.KeyShiftState))) {
    EnterMebxSetup ();
    mEnterMebxSetup = 1;
    return EFI_SUCCESS;
  } else if ((DisplayRemoteAssistancePrompt() == TRUE) &&
             (KeyData->Key.ScanCode == SCAN_F1) &&
             IsCtrlKey(KeyData->KeyState.KeyShiftState) &&
             IsAltKey(KeyData->KeyState.KeyShiftState)) {
    EnterRemoteAssistance ();
    mEnterRemoteAssistance = 1;
    return EFI_SUCCESS;
  }
  return EFI_NOT_FOUND;
}

/**
  Get Supported Hot Keys.

  @param[out] KeyCnt            Supported Hot Key Count.
  @param[out] KeyData           Supported Hot Key Data.

  @retval EFI_SUCCESS           Get Supported Hot Keys Successfully.
  @retval EFI_OUT_OF_RESOURCES  Out of memory.
  @retval EFI_NOT_FOUND         No Supported Hot Keys.
**/
EFI_STATUS
EFIAPI
AmtWrapperGetSupportedHotkeys (
  OUT  UINTN             *KeyCnt,
  OUT  EFI_KEY_DATA      **KeyData
  )
{
  EFI_KEY_DATA MeHotKeyTables[] = {
    //
    // Ctrl + P
    //
    { {CHAR_NULL, CHAR_DATA_LINK_ESCAPE}, {0, 0} },
    { {CHAR_NULL, L'p'}, {EFI_SHIFT_STATE_VALID | EFI_RIGHT_CONTROL_PRESSED, 0} },
    { {CHAR_NULL, L'p'}, {EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED,  0} },
    { {CHAR_NULL, L'P'}, {EFI_SHIFT_STATE_VALID | EFI_RIGHT_CONTROL_PRESSED, 0} },
    { {CHAR_NULL, L'P'}, {EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED,  0} },
    //
    // Ctrl + Alt + F1
    //
    { {SCAN_F1, CHAR_NULL}, {EFI_SHIFT_STATE_VALID | EFI_RIGHT_CONTROL_PRESSED | EFI_RIGHT_ALT_PRESSED, 0} },
    { {SCAN_F1, CHAR_NULL}, {EFI_SHIFT_STATE_VALID | EFI_RIGHT_CONTROL_PRESSED | EFI_LEFT_ALT_PRESSED,  0} },
    { {SCAN_F1, CHAR_NULL}, {EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED  | EFI_RIGHT_ALT_PRESSED, 0} },
    { {SCAN_F1, CHAR_NULL}, {EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED  | EFI_LEFT_ALT_PRESSED,  0} }
  };

  *KeyCnt = 0;
  *KeyData = NULL;

  if (IsBiosHotkeyEnabled ()) {
    if (DisplayRemoteAssistancePrompt ()) {
      //
      // CTRL + P and CTRL + ALT + F1 hotkey
      //
      *KeyCnt = sizeof (MeHotKeyTables) / sizeof (MeHotKeyTables[0]);
    } else {
      //
      // CTRL + P hotkey
      //
      *KeyCnt = NUMBER_OF_HOTKEY_CTRL_P;
    }

    *KeyData = AllocateZeroPool (sizeof (EFI_KEY_DATA) * (*KeyCnt));
    if (*KeyData == NULL){
      return EFI_OUT_OF_RESOURCES;
    }

    CopyMem (*KeyData, MeHotKeyTables, sizeof (EFI_KEY_DATA) * (*KeyCnt));
    return EFI_SUCCESS;

  }
  return EFI_NOT_FOUND;
}

VOID
EFIAPI
AsfWatchDogStopOnSetupEntry (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  AmtWrapperSet (SET_WDT_STOP);
}


/**
  Entry point for the Active Management Driver.

  @param[in] ImageHandle        Image handle of this driver.
  @param[in] SystemTable        Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @retval EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
AmtWrapperDxeEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS             Status;
  ME_BIOS_PAYLOAD_HOB    *MbpHob;
  EFI_EVENT              PlatformSetupEvent;
  VOID                   *Registration;

  MbpHob       = NULL;
  mFwImageType = IntelMeConsumerFw;

  ManageSecureBootState ();

  //
  // Get Mbp Protocol
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    mFwImageType = (UINT8)MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType;
  }

  //
  // Install the AMT_WRAPPER_PROTOCOL interface
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gAmtWrapperProtocolGuid,
                  &mAmtWrapperInstance,
                  NULL
                  );

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  AsfWatchDogStopOnSetupEntry,
                  NULL,
                  &PlatformSetupEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->RegisterProtocolNotify (
                  &gSetupEnterGuid,
                  PlatformSetupEvent,
                  &Registration
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Check if ASF boot options is present.

  @retval True                    ASF boot option is present.
  @retval False                   ASF boot option is not present
**/
BOOLEAN
EFIAPI
AmtWrapperBootOptionExist (
  VOID
  )
{
  return AsfIsBootOptionsPresent ();
}

/**
  Get Serial Over Lan Device Path

  @param[in, out] DevicePath      Device Path of Serial Over Lan

  @retval True                    Get SOL Device Path Successful.
**/
BOOLEAN
EFIAPI
AmtWrapperGetSolDevicePath (
  IN OUT VOID  *DevicePath
  )
{
  *((PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH **)DevicePath) = &mSerialOverLanDevicePath;
  return TRUE;
}

/**
  Setting for AMT wrapper

  @param[in] Index                Setting index

  @retval True                    Required setting is supported.
  @retval False                   Required setting is not supported.
**/
BOOLEAN
EFIAPI
AmtWrapperSet (
  IN UINTN     Index
  )
{
  EFI_HOB_GUID_TYPE    *GuidHob;
  AMT_PEI_CONFIG       *AmtPeiConfig;

  GuidHob = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (GuidHob == NULL) {
    return FALSE;
  }
  AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (GuidHob);
  if (AmtPeiConfig->WatchDogEnabled == 0) {
    return FALSE;
  }

  if (Index == SET_BIOS_WDT_START) {
    AsfStartWatchDog (ASF_START_BIOS_WDT);
    return TRUE;
  } else if (Index == SET_OS_WDT_START) {
    AsfStartWatchDog (ASF_START_OS_WDT);
    return TRUE;
  } else if (Index == SET_WDT_STOP) {
    AsfStopWatchDog ();
    return TRUE;
  }
  return FALSE;
}

/**
  This will return Console Lock Boot Option.
  True if the option is enabled.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperConsoleLocked (
  VOID
  )
{
  return AsfIsConsoleLocked ();
}

/**
  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableSecureErase (
  VOID
  )
{
  return AsfIsSecureEraseEnabled ();
}

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableSol (
  VOID
  )
{
  return AsfIsSolEnabled ();
}

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableStorageRedir (
  VOID
  )
{
  return AsfIsStorageRedirectionEnabled ();
}

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperPauseBoot (
  VOID
  )
{
  return AsfIsPauseBootEnabled ();
}

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnterSetup (
  VOID
  )
{
  return AsfIsEnterSetupEnabled ();
}

/**
  Process ASF boot options and if available, attempt the boot

  @retval EFI_SUCCESS    The command completed successfully
**/
EFI_STATUS
EFIAPI
AmtWrapperBdsBootViaAsf (
  VOID
  )
{
  return BdsBootViaAsf ();
}

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableKvm (
  VOID
  )
{
  return AsfIsKvmEnabled ();
}
