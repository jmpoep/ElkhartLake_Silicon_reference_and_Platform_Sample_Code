/** @file
  AMT specific functions implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include "BdsPlatform.h"
#include "AmtSupport.h"
#include <AmtConfig.h>
#include <MeBiosPayloadHob.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT mHotkeyRegisteredEvent = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED VOID      *mRegistration;

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   mModeInitialized = FALSE;

//
// Boot video resolution and text mode.
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootHorizontalResolution    = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootVerticalResolution      = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootTextModeColumn          = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootTextModeRow             = 0;
//
// BIOS setup video resolution and text mode.
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupTextModeColumn         = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupTextModeRow            = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupHorizontalResolution   = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupVerticalResolution     = 0;

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   mMebxLaunched                = FALSE;

VOID
DeleteConIn (
  VOID   **Variable,
  UINTN  *VariableSize
  )
{
  *Variable     = NULL;
  *VariableSize = 0;
}

VOID
AmtUpdateConsoleVariable (
  VOID
  )
{
  EFI_STATUS               Status;
  AMT_WRAPPER_PROTOCOL     *AmtWrapper;
  EFI_DEVICE_PATH_PROTOCOL *SolDevicePath;
  EFI_GUID                 AmtConsoleVariableGuid = {
    0xd9aaf1e5, 0xcd14, 0x4312, { 0x9c, 0xa4, 0x85, 0xc3, 0xa, 0xde, 0x43, 0xe8 }
  };

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    if (AmtWrapper->IsConsoleLocked ()) {
      UpdateEfiGlobalVariable (L"ConIn", &AmtConsoleVariableGuid, DeleteConIn);
    } else {
      UpdateEfiGlobalVariable (L"ConIn", &AmtConsoleVariableGuid, NULL);
    }

    //
    // Add/Del AMT SOL device path to/from the ConIn, ConOut and StdErr variable when SOL is enabled/disabled.
    //
    if (AmtWrapper->Get ((VOID **) &SolDevicePath)) {
      if (AmtWrapper->IsSolEnabled ()) {
        EfiBootManagerUpdateConsoleVariable (ConIn, SolDevicePath, NULL);
        EfiBootManagerUpdateConsoleVariable (ConOut, SolDevicePath, NULL);
        EfiBootManagerUpdateConsoleVariable (ErrOut, SolDevicePath, NULL);
      } else {
        EfiBootManagerUpdateConsoleVariable (ConIn, NULL, SolDevicePath);
        EfiBootManagerUpdateConsoleVariable (ConOut, NULL, SolDevicePath);
        EfiBootManagerUpdateConsoleVariable (ErrOut, NULL, SolDevicePath);
      }
    }
  }
}

/**
  Performs boot actions requested by AMT through Boot Options.
**/
VOID
AmtBdsBoot (
  VOID
  )
{
  EFI_STATUS               Status;
  AMT_WRAPPER_PROTOCOL     *AmtWrapper;
  UINTN                    EventIndex;

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (EFI_ERROR (Status)) {
    return;
  }

  if (AmtWrapper->IsPauseBootEnabled ()) {
    //
    // Wait until user presses any key when PauseBoot is requested
    //
    gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, &EventIndex);
  } else if (AmtWrapper->IsEnterSetupEnabled ()) {
    //
    // Enter to setup when SetupBoot is requested
    //
    BootUi ();
  } else if (AmtWrapper->BootOptionExist ())  {
    AmtWrapper->BdsBootViaAsf();
  }
}

/**
  AMT action when console is ready.
  Dynamically switch the output mode to 80x25 when SOL is enabled.
**/
VOID
AmtConsoleReady (
  VOID
  )
{
  EFI_STATUS              Status;
  INTN                    Index;
  AMT_WRAPPER_PROTOCOL    *AmtWrapper;
  UINTN                   Columns;
  UINTN                   Rows;
  INTN                    FailSafeMode;

  //
  // Set mode to 80 x 25
  //
  if (gST->ConOut == NULL) {
    return;
  }

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    //
    // Add AMT SOL device path to the ConIn, ConOut and StdErr variable when SOL is enabled.
    //
    FailSafeMode = gST->ConOut->Mode->MaxMode;
    if (AmtWrapper->IsSolEnabled ()) {
      for (Index = 0; Index < gST->ConOut->Mode->MaxMode; Index++) {
        Status = gST->ConOut->QueryMode (gST->ConOut, Index, &Columns, &Rows);
        if (!EFI_ERROR (Status) && (Columns == 80)) {
          if (Rows == 24) {
            break;
          }
          FailSafeMode = Index;
        }
      }

      if (Index == gST->ConOut->Mode->MaxMode) {
        //
        // When no 80x24 mode, use the 80x* mode.
        //
        Index = FailSafeMode;
      }

      if ((Index != gST->ConOut->Mode->MaxMode) && (Index != gST->ConOut->Mode->Mode)) {
        gST->ConOut->SetMode (gST->ConOut, (UINTN) Index);
      }
    }
  }
}

BOOLEAN
AmtEnterSetup (
  VOID
  )
{
  AMT_WRAPPER_PROTOCOL          *AmtWrapper;
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    return AmtWrapper->IsEnterSetupEnabled ();
  }
  return FALSE;
}

EFI_STATUS
AmtGetSetupPrompt (
  OUT     CHAR16    **String
  )
{
  AMT_WRAPPER_PROTOCOL          *AmtWrapper;
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    Status = AmtWrapper->GetNextSetupPrompt (String);
  }
  return Status;
}

EFI_STATUS
AmtGetSupportedHotkeys (
  OUT  UINTN             *KeyCnt,
  OUT  EFI_KEY_DATA      **KeyData
  )
{
  AMT_WRAPPER_PROTOCOL          *AmtWrapper;
  EFI_STATUS                    Status;

  *KeyCnt = 0;
  *KeyData = NULL;
  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    Status = AmtWrapper->GetSupportedHotkeys (KeyCnt, KeyData);
  }
  return Status;
}

/**
  This function will change video resolution and text mode
  according to defined setup mode or defined boot mode

  @param[in]  IsSetupMode   Indicate mode is changed to setup mode or boot mode.

  @retval  EFI_SUCCESS      Mode is changed successfully.
  @retval  Others           Mode failed to be changed.

**/
EFI_STATUS
EFIAPI
BdsSetConsoleMode (
  IN BOOLEAN  IsSetupMode
  )
{
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *SimpleTextOut;
  UINTN                                 SizeOfInfo;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
  UINT32                                MaxGopMode;
  UINT32                                MaxTextMode;
  UINT32                                ModeNumber;
  UINT32                                NewHorizontalResolution;
  UINT32                                NewVerticalResolution;
  UINT32                                NewColumns;
  UINT32                                NewRows;
  UINTN                                 HandleCount;
  EFI_HANDLE                            *HandleBuffer;
  EFI_STATUS                            Status;
  UINTN                                 Index;
  UINTN                                 CurrentColumn;
  UINTN                                 CurrentRow;

  MaxGopMode  = 0;
  MaxTextMode = 0;

  //
  // Get current video resolution and text mode
  //
  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiGraphicsOutputProtocolGuid,
                  (VOID**)&GraphicsOutput
                  );
  if (EFI_ERROR (Status)) {
    GraphicsOutput = NULL;
  }

  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiSimpleTextOutProtocolGuid,
                  (VOID**)&SimpleTextOut
                  );
  if (EFI_ERROR (Status)) {
    SimpleTextOut = NULL;
  }

  if ((GraphicsOutput == NULL) || (SimpleTextOut == NULL)) {
    return EFI_UNSUPPORTED;
  }

  if (IsSetupMode) {
    //
    // The required resolution and text mode is setup mode.
    //
    NewHorizontalResolution = mSetupHorizontalResolution;
    NewVerticalResolution   = mSetupVerticalResolution;
    NewColumns              = mSetupTextModeColumn;
    NewRows                 = mSetupTextModeRow;
  } else {
    //
    // The required resolution and text mode is boot mode.
    //
    NewHorizontalResolution = mBootHorizontalResolution;
    NewVerticalResolution   = mBootVerticalResolution;
    NewColumns              = mBootTextModeColumn;
    NewRows                 = mBootTextModeRow;
  }

  if (GraphicsOutput != NULL) {
    MaxGopMode  = GraphicsOutput->Mode->MaxMode;
  }

  if (SimpleTextOut != NULL) {
    MaxTextMode = SimpleTextOut->Mode->MaxMode;
  }

  //
  // 1. If current video resolution is same with required video resolution,
  //    video resolution need not be changed.
  //    1.1. If current text mode is same with required text mode, text mode need not be changed.
  //    1.2. If current text mode is different from required text mode, text mode need be changed.
  // 2. If current video resolution is different from required video resolution, we need restart whole console drivers.
  //
  for (ModeNumber = 0; ModeNumber < MaxGopMode; ModeNumber++) {
    Status = GraphicsOutput->QueryMode (
                               GraphicsOutput,
                               ModeNumber,
                               &SizeOfInfo,
                               &Info
                               );
    if (!EFI_ERROR (Status)) {
      if ((Info->HorizontalResolution == NewHorizontalResolution) &&
          (Info->VerticalResolution == NewVerticalResolution)) {
        if ((GraphicsOutput->Mode->Info->HorizontalResolution == NewHorizontalResolution) &&
            (GraphicsOutput->Mode->Info->VerticalResolution == NewVerticalResolution)) {
          //
          // Current resolution is same with required resolution, check if text mode need be set
          //
          Status = SimpleTextOut->QueryMode (SimpleTextOut, SimpleTextOut->Mode->Mode, &CurrentColumn, &CurrentRow);
          ASSERT_EFI_ERROR (Status);
          if (CurrentColumn == NewColumns && CurrentRow == NewRows) {
            //
            // If current text mode is same with required text mode. Do nothing
            //
            FreePool (Info);
            return EFI_SUCCESS;
          } else {
            //
            // If current text mode is different from required text mode. Set new video mode
            //
            for (Index = 0; Index < MaxTextMode; Index++) {
              Status = SimpleTextOut->QueryMode (SimpleTextOut, Index, &CurrentColumn, &CurrentRow);
              if (!EFI_ERROR(Status)) {
                if ((CurrentColumn == NewColumns) && (CurrentRow == NewRows)) {
                  //
                  // Required text mode is supported, set it.
                  //
                  Status = SimpleTextOut->SetMode (SimpleTextOut, Index);
                  ASSERT_EFI_ERROR (Status);
                  //
                  // Update text mode PCD.
                  //
                  PcdSet32S (PcdConOutColumn, mSetupTextModeColumn);
                  PcdSet32S (PcdConOutRow, mSetupTextModeRow);
                  FreePool (Info);
                  return EFI_SUCCESS;
                }
              }
            }
            if (Index == MaxTextMode) {
              //
              // If required text mode is not supported, return error.
              //
              FreePool (Info);
              return EFI_UNSUPPORTED;
            }
          }
        } else {
          //
          // If current video resolution is not same with the new one, set new video resolution.
          // In this case, the driver which produces simple text out need be restarted.
          //
          Status = GraphicsOutput->SetMode (GraphicsOutput, ModeNumber);
          if (!EFI_ERROR (Status)) {
            FreePool (Info);
            break;
          }
        }
      }
      FreePool (Info);
    }
  }

  if (ModeNumber == MaxGopMode) {
    //
    // If the resolution is not supported, return error.
    //
    return EFI_UNSUPPORTED;
  }

  //
  // Set PCD to Inform GraphicsConsole to change video resolution.
  // Set PCD to Inform Consplitter to change text mode.
  //
  PcdSet32S (PcdVideoHorizontalResolution, NewHorizontalResolution);
  PcdSet32S (PcdVideoVerticalResolution, NewVerticalResolution);
  PcdSet32S (PcdConOutColumn, NewColumns);
  PcdSet32S (PcdConOutRow, NewRows);

  //
  // Video mode is changed, so restart graphics console driver and higher level driver.
  // Reconnect graphics console driver and higher level driver.
  // Locate all the handles with GOP protocol and reconnect it.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleTextOutProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < HandleCount; Index++) {
      gBS->DisconnectController (HandleBuffer[Index], NULL, NULL);
    }
    for (Index = 0; Index < HandleCount; Index++) {
      gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
    }
    if (HandleBuffer != NULL) {
      FreePool (HandleBuffer);
    }
  }

  return EFI_SUCCESS;
}

/**
  Notification function for keystrokes.

  @param[in] KeyData    The key that was pressed.

  @retval EFI_SUCCESS   The operation was successful.
**/
EFI_STATUS
EFIAPI
MeHotkeyCallback(
  IN EFI_KEY_DATA *KeyData
  )
{
  AMT_WRAPPER_PROTOCOL          *AmtWrapper;
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status)) {
    Status = AmtWrapper->DetermineSetupHotKey (KeyData);

    if (Status == EFI_SUCCESS) {
      mMebxLaunched = TRUE;
      BdsSetConsoleMode (TRUE);

      //
      // Trigger ReadyToBoot event to launch MEBx,
      // If we change to launch MEBx not in ReadyToBoot event, we don't need to trigger the event here
      //
      EfiSignalEventReadyToBoot ();
    }
  }
  return Status;
}

VOID
EFIAPI
MebxRestoreResolutionCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{
  if (mMebxLaunched) {
    //
    // If MEBX is launched before, switch resolution to boot resolution
    //
    BdsSetConsoleMode (FALSE);
    mMebxLaunched = FALSE;
  }

  gBS->CloseEvent (Event);
  return;
}

/**
  Callback function for SimpleTextInEx protocol install events

  @param[in] Event           the event that is signalled.
  @param[in] Context         not used here.

**/
VOID
EFIAPI
PlatformBdsTxtInExCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                         Status;
  UINTN                              BufferSize;
  EFI_HANDLE                         Handle;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *TxtInEx;
  UINTN                              Count;
  UINTN                              Index;
  EFI_KEY_DATA                       *KeyData;
  EFI_HANDLE                         NotifyHandle;
  EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *SimpleTextOut;
  UINTN                              BootTextColumn;
  UINTN                              BootTextRow;
  EFI_EVENT                          MeRestoreResolutionEvent;

  if (!mModeInitialized) {
    //
    // At this moment, ConOut has been connected by BDS core, so get current video resolution
    // and text mode before launching setup at first time.
    //
    Status = gBS->HandleProtocol (
                    gST->ConsoleOutHandle,
                    &gEfiGraphicsOutputProtocolGuid,
                    (VOID**)&GraphicsOutput
                    );
    if (EFI_ERROR (Status)) {
      GraphicsOutput = NULL;
    }

    Status = gBS->HandleProtocol (
                    gST->ConsoleOutHandle,
                    &gEfiSimpleTextOutProtocolGuid,
                    (VOID**)&SimpleTextOut
                    );
    if (EFI_ERROR (Status)) {
      SimpleTextOut = NULL;
    }

    if (GraphicsOutput != NULL) {
      //
      // Get current video resolution and text mode.
      //
      mBootHorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
      mBootVerticalResolution   = GraphicsOutput->Mode->Info->VerticalResolution;
    }

    if (SimpleTextOut != NULL) {
      Status = SimpleTextOut->QueryMode (
                                SimpleTextOut,
                                SimpleTextOut->Mode->Mode,
                                &BootTextColumn,
                                &BootTextRow
                                );
      mBootTextModeColumn = (UINT32)BootTextColumn;
      mBootTextModeRow    = (UINT32)BootTextRow;
    }

    //
    // Get user defined text mode for setup.
    //
    mSetupHorizontalResolution = PcdGet32 (PcdSetupVideoHorizontalResolution);
    mSetupVerticalResolution   = PcdGet32 (PcdSetupVideoVerticalResolution);
    mSetupTextModeColumn       = PcdGet32 (PcdSetupConOutColumn);
    mSetupTextModeRow          = PcdGet32 (PcdSetupConOutRow);
    mModeInitialized           = TRUE;

    //
    // Create callback function to restore boot resolution
    //
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    MebxRestoreResolutionCallback,
                    NULL,
                    &gMePlatformReadyToBootGuid,
                    &MeRestoreResolutionEvent
                    );
    ASSERT_EFI_ERROR (Status);
  }

  Status = AmtGetSupportedHotkeys (&Count, &KeyData);
  if (EFI_ERROR (Status)) {
    return;
  }

  while (TRUE) {
    BufferSize = sizeof (EFI_HANDLE);
    Status = gBS->LocateHandle (
                    ByRegisterNotify,
                    NULL,
                    mRegistration,
                    &BufferSize,
                    &Handle
                    );
    if (EFI_ERROR (Status)) {
      //
      // If no more notification events exist
      //
      return ;
    }

    Status = gBS->HandleProtocol (
                    Handle,
                    &gEfiSimpleTextInputExProtocolGuid,
                    (VOID **) &TxtInEx
                    );
    ASSERT_EFI_ERROR (Status);

    for (Index = 0; Index < Count; Index++) {
      Status = TxtInEx->RegisterKeyNotify (TxtInEx, &KeyData[Index], MeHotkeyCallback, &NotifyHandle);
      DEBUG ((DEBUG_INFO, "[Bds]RegisterAmtKeyNotify: %04x/%04x %r\n", KeyData[Index].Key.ScanCode, KeyData[Index].Key.UnicodeChar, Status));
      ASSERT_EFI_ERROR (Status);
    }
  }

  if (KeyData != NULL) {
    FreePool (KeyData);
  }
}

/**
  Register Amt Hotkey.
**/
VOID
RegisterAmtHotKey (
  VOID
  )
{
  VOID          *SetupRegistration;
  EFI_STATUS    Status;
  EFI_EVENT     Event;

  //
  // Create event for registering the hotkeys on installed input consoles
  //
  mHotkeyRegisteredEvent = EfiCreateProtocolNotifyEvent (
                             &gEfiSimpleTextInputExProtocolGuid,
                             TPL_CALLBACK,
                             PlatformBdsTxtInExCallback,
                             NULL,
                             &mRegistration
                             );
  //
  // Register EnterSetup and ReadyToBoot events for removing Amt hotkeys
  //
  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  UnregisterAmtHotKey,
                  NULL,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->RegisterProtocolNotify (
                  &gSetupEnterGuid,
                  Event,
                  &SetupRegistration
                  );
  ASSERT_EFI_ERROR (Status);

  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             UnregisterAmtHotKey,
             NULL,
             &Event
             );
  ASSERT_EFI_ERROR (Status);
}


/**
  Unregister Amt Hotkey.

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.
**/
VOID
EFIAPI
UnregisterAmtHotKey (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  EFI_STATUS                            Status;
  UINTN                                 Index;
  UINTN                                 KeyIndex;
  EFI_HANDLE                            *Handles;
  UINTN                                 HandleCount;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *TxtInEx;
  EFI_HANDLE                            NotifyHandle;
  EFI_KEY_DATA                          *KeyData;
  UINTN                                 Count;

  Status = AmtGetSupportedHotkeys (&Count, &KeyData);
  if (EFI_ERROR (Status)) {
    return;
  }

  gBS->LocateHandleBuffer (
         ByProtocol,
         &gEfiSimpleTextInputExProtocolGuid,
         NULL,
         &HandleCount,
         &Handles
         );
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (Handles[Index], &gEfiSimpleTextInputExProtocolGuid, (VOID **) &TxtInEx);
    ASSERT_EFI_ERROR (Status);
    for (KeyIndex = 0; KeyIndex < Count; KeyIndex++) {
      Status = TxtInEx->RegisterKeyNotify (
                          TxtInEx,
                          &KeyData[KeyIndex],
                          MeHotkeyCallback,
                          &NotifyHandle
                          );
      if (!EFI_ERROR (Status)) {
        Status = TxtInEx->UnregisterKeyNotify (TxtInEx, NotifyHandle);
        DEBUG ((DEBUG_INFO, "[Bds]UnregisterAmtKeyNotify: %04x/%04x %r\n",
          KeyData[KeyIndex].Key.ScanCode, KeyData[KeyIndex].Key.UnicodeChar, Status));
      }
    }
  }

  //
  // Close Register and Unregister events as we're done with ME hotkeys in this boot
  //
  gBS->CloseEvent (Event);
  gBS->CloseEvent (mHotkeyRegisteredEvent);
}

/**
  Check whether do full configuration enumeration for media asset table

  @param[in, out]   BootMode        A pointer to BootMode to be updated.

**/
VOID
AmtUpdateBootMode (
  IN OUT EFI_BOOT_MODE  *BootMode
  )
{
  EFI_STATUS            Status;
  AMT_WRAPPER_PROTOCOL  *AmtWrapper;
  ME_BIOS_PAYLOAD_HOB   *MbpHob;
  AMT_POLICY_PROTOCOL   *AmtPolicy;
  AMT_DXE_CONFIG        *AmtDxeConfig;

  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);
    if ((BOOLEAN) AmtDxeConfig->UsbProvision == TRUE) {
      *BootMode = BOOT_WITH_FULL_CONFIGURATION;
      DEBUG ((DEBUG_INFO, "Boot exception raised for ME Usb Provision, do full media discovery.\n"));
      return;
    }
  }

  //
  // Get Mbp Hob
  //
  MbpHob = NULL;
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    //
    // During FastBoot, when the BIOS detects an Indication from the ME Firmware,the BIOS shall
    // enumerate all media devices and send all asset tables to the ME Firmware.
    //
    if ((MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType == IntelMeCorporateFw) &&
        (MbpHob->MeBiosPayload.HwaRequest.Available == TRUE) &&
        (MbpHob->MeBiosPayload.HwaRequest.Data.Fields.MediaTablePush == TRUE)) {
      *BootMode = BOOT_WITH_FULL_CONFIGURATION;
      DEBUG ((DEBUG_INFO, "Boot exception raised for ME MediaTablePush, do full media discovery.\n"));
      return;
    }
  }

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);
  if (!EFI_ERROR (Status) && AmtWrapper->BootOptionExist ()) {
    *BootMode = BOOT_WITH_FULL_CONFIGURATION;
  }
}

