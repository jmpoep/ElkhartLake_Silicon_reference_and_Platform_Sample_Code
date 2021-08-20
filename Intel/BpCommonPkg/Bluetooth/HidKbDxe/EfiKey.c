//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  HID Keyboard Driver that manages HID keyboard and produces Simple Text Input
  Protocol and Simple Text Input Ex Protocol.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "HidKbDxe.h"
#include "KeyBoard.h"

/**
  Internal function to read the next keystroke from the keyboard buffer.

  @param  HidKbDev       HID keyboard's private structure.
  @param  KeyData                 A pointer to buffer to hold the keystroke
                                  data for the key that was pressed.

  @retval EFI_SUCCESS             The keystroke information was returned.
  @retval EFI_NOT_READY           There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR        The keystroke information was not returned due to
                                  hardware errors.
  @retval EFI_INVALID_PARAMETER   KeyData is NULL.
  @retval Others                  Fail to translate keycode into EFI_INPUT_KEY

**/
EFI_STATUS
HidKbReadKeyStrokeWorker (
  IN OUT HID_KB_DEV                  *HidKbDev,
     OUT EFI_KEY_DATA               *KeyData
  )
{
  if (KeyData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (IsQueueEmpty (&HidKbDev->EfiKeyQueue)) {
    return EFI_NOT_READY;
  }

  Dequeue (&HidKbDev->EfiKeyQueue, KeyData, sizeof (*KeyData));

  return EFI_SUCCESS;
}

/**
  Reset the input device and optionally run diagnostics

  There are 2 types of reset for HID keyboard.
  For non-exhaustive reset, only keyboard buffer is cleared.
  For exhaustive reset, in addition to clearance of keyboard buffer, the hardware status
  is also re-initialized.

  @param  This                 Protocol instance pointer.
  @param  ExtendedVerification Driver may perform diagnostics on reset.

  @retval EFI_SUCCESS          The device was reset.
  @retval EFI_DEVICE_ERROR     The device is not functioning properly and could not be reset.

**/
EFI_STATUS
EFIAPI
HidKbReset (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
  IN  BOOLEAN                          ExtendedVerification
  )
{
  EFI_STATUS          Status;
  HID_KB_DEV           *HidKbDev;

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_PROTOCOL (This);

  //
  // Non-exhaustive reset:
  // only reset private data structures.
  //
  if (!ExtendedVerification) {
    //
    // Clear the key buffer of this HID keyboard
    //
    InitQueue (&HidKbDev->HidKeyQueue, sizeof (HID_KEY));
    InitQueue (&HidKbDev->EfiKeyQueue, sizeof (EFI_KEY_DATA));

    return EFI_SUCCESS;
  }

  //
  // Exhaustive reset
  //
  Status = InitHidKeyboard (HidKbDev);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  Reads the next keystroke from the input device.

  @param  This                 The EFI_SIMPLE_TEXT_INPUT_PROTOCOL instance.
  @param  Key                  A pointer to a buffer that is filled in with the keystroke
                               information for the key that was pressed.

  @retval EFI_SUCCESS          The keystroke information was returned.
  @retval EFI_NOT_READY        There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR     The keystroke information was not returned due to
                               hardware errors.

**/
EFI_STATUS
EFIAPI
HidKbReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
  OUT EFI_INPUT_KEY                    *Key
  )
{
  HID_KB_DEV    *HidKbDev;
  EFI_STATUS   Status;
  EFI_KEY_DATA KeyData;

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_PROTOCOL (This);

  //
  // Considering if the partial keystroke is enabled, there maybe a partial
  // keystroke in the queue, so here skip the partial keystroke and get the
  // next key from the queue
  //
  while (1) {
    Status = HidKbReadKeyStrokeWorker (HidKbDev, &KeyData);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // SimpleTextIn Protocol doesn't support partial keystroke;
    //
    if (KeyData.Key.ScanCode == CHAR_NULL && KeyData.Key.UnicodeChar == SCAN_NULL) {
      continue;
    }
    //
    // Translate the CTRL-Alpha characters to their corresponding control value
    // (ctrl-a = 0x0001 through ctrl-Z = 0x001A)
    //
    if ((KeyData.KeyState.KeyShiftState & (EFI_LEFT_CONTROL_PRESSED | EFI_RIGHT_CONTROL_PRESSED)) != 0) {
      if (KeyData.Key.UnicodeChar >= L'a' && KeyData.Key.UnicodeChar <= L'z') {
        KeyData.Key.UnicodeChar = (CHAR16) (KeyData.Key.UnicodeChar - L'a' + 1);
      } else if (KeyData.Key.UnicodeChar >= L'A' && KeyData.Key.UnicodeChar <= L'Z') {
        KeyData.Key.UnicodeChar = (CHAR16) (KeyData.Key.UnicodeChar - L'A' + 1);
      }
    }

    CopyMem (Key, &KeyData.Key, sizeof (EFI_INPUT_KEY));
    return EFI_SUCCESS;
  }
}


/**
  Event notification function registered for EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.WaitForKeyEx
  and EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey.

  @param  Event        Event to be signaled when a key is pressed.
  @param  Context      Points to HID_KB_DEV instance.

**/
VOID
EFIAPI
HidKbWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  HID_KB_DEV    *HidKbDev;
  EFI_KEY_DATA KeyData;
  EFI_TPL      OldTpl;

  HidKbDev = (HID_KB_DEV *) Context;

  //
  // Enter critical section
  //
  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  //
  // WaitforKey doesn't suppor the partial key.
  // Considering if the partial keystroke is enabled, there maybe a partial
  // keystroke in the queue, so here skip the partial keystroke and get the
  // next key from the queue
  //
  while (!IsQueueEmpty (&HidKbDev->EfiKeyQueue)) {
    //
    // If there is pending key, signal the event.
    //
    CopyMem (
      &KeyData,
      HidKbDev->EfiKeyQueue.Buffer[HidKbDev->EfiKeyQueue.Head],
      sizeof (EFI_KEY_DATA)
      );
    if (KeyData.Key.ScanCode == SCAN_NULL && KeyData.Key.UnicodeChar == CHAR_NULL) {
      Dequeue (&HidKbDev->EfiKeyQueue, &KeyData, sizeof (EFI_KEY_DATA));
      continue;
    }
    gBS->SignalEvent (Event);
    break;
  }
  //
  // Leave critical section and return
  //
  gBS->RestoreTPL (OldTpl);
}

/**
  Timer handler to convert the key from HID.

  @param  Event                    Indicates the event that invoke this function.
  @param  Context                  Indicates the calling context.
**/
VOID
EFIAPI
HidKbTimerHandler (
  IN  EFI_EVENT                 Event,
  IN  VOID                      *Context
  )
{
  EFI_STATUS                    Status;
  HID_KB_DEV                     *HidKbDev;
  UINT8                         KeyCode;
  EFI_KEY_DATA                  KeyData;

  HidKbDev = (HID_KB_DEV *) Context;

  //
  // Fetch raw data from the HID keyboard buffer,
  // and translate it into HID keycode.
  //
  Status = HidParseKey (HidKbDev, &KeyCode);
  if (EFI_ERROR (Status)) {
    return ;
  }

  //
  // Translate saved HID keycode into EFI_INPUT_KEY
  //
  Status = HidKeyCodeToEfiInputKey (HidKbDev, KeyCode, &KeyData);
  if (EFI_ERROR (Status)) {
    return ;
  }

  //
  // Insert to the EFI Key queue
  //
  Enqueue (&HidKbDev->EfiKeyQueue, &KeyData, sizeof (KeyData));
}

/**
  Free keyboard notify list.

  @param  NotifyList              The keyboard notify list to free.

  @retval EFI_SUCCESS             Free the notify list successfully.
  @retval EFI_INVALID_PARAMETER   NotifyList is NULL.

**/
EFI_STATUS
KbdFreeNotifyList (
  IN OUT LIST_ENTRY           *NotifyList
  )
{
  KEYBOARD_CONSOLE_IN_EX_NOTIFY *NotifyNode;
  LIST_ENTRY                    *Link;

  if (NotifyList == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  while (!IsListEmpty (NotifyList)) {
    Link = GetFirstNode (NotifyList);
    NotifyNode = CR (Link, KEYBOARD_CONSOLE_IN_EX_NOTIFY, NotifyEntry, HID_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE);
    RemoveEntryList (Link);
    FreePool (NotifyNode);
  }

  return EFI_SUCCESS;
}

/**
  Check whether the pressed key matches a registered key or not.

  @param  RegsiteredData    A pointer to keystroke data for the key that was registered.
  @param  InputData         A pointer to keystroke data for the key that was pressed.

  @retval TRUE              Key pressed matches a registered key.
  @retval FLASE             Key pressed does not matches a registered key.

**/
BOOLEAN
IsKeyRegistered (
  IN EFI_KEY_DATA  *RegsiteredData,
  IN EFI_KEY_DATA  *InputData
  )
{
  ASSERT (RegsiteredData != NULL && InputData != NULL);

  if ((RegsiteredData->Key.ScanCode    != InputData->Key.ScanCode) ||
      (RegsiteredData->Key.UnicodeChar != InputData->Key.UnicodeChar)) {
    return FALSE;
  }

  //
  // Assume KeyShiftState/KeyToggleState = 0 in Registered key data means these state could be ignored.
  //
  if (RegsiteredData->KeyState.KeyShiftState != 0 &&
      RegsiteredData->KeyState.KeyShiftState != InputData->KeyState.KeyShiftState) {
    return FALSE;
  }
  if (RegsiteredData->KeyState.KeyToggleState != 0 &&
      RegsiteredData->KeyState.KeyToggleState != InputData->KeyState.KeyToggleState) {
    return FALSE;
  }

  return TRUE;
}

//
// Simple Text Input Ex protocol functions
//
/**
  Resets the input device hardware.

  The Reset() function resets the input device hardware. As part
  of initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is functioning.
  If the ExtendedVerification flag is TRUE the firmware may take
  an extended amount of time to verify the device is operating on
  reset. Otherwise the reset operation is to occur as quickly as
  possible. The hardware verification process is not defined by
  this specification and is left up to the platform firmware or
  driver to implement.

  @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL instance.

  @param ExtendedVerification Indicates that the driver may perform a more exhaustive
                              verification operation of the device during reset.

  @retval EFI_SUCCESS         The device was reset.
  @retval EFI_DEVICE_ERROR    The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
HidKbResetEx (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN BOOLEAN                            ExtendedVerification
  )
{
  EFI_STATUS                Status;
  HID_KB_DEV                *HidKbDev;

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_EX_PROTOCOL (This);

  Status = HidKbDev->SimpleTextIn.Reset (&HidKbDev->SimpleTextIn, ExtendedVerification);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  HidKbDev->KeyState.KeyShiftState  = EFI_SHIFT_STATE_VALID;
  HidKbDev->KeyState.KeyToggleState = EFI_TOGGLE_STATE_VALID;

  return EFI_SUCCESS;

}

/**
  Reads the next keystroke from the input device.

  @param  This                   Protocol instance pointer.
  @param  KeyData                A pointer to a buffer that is filled in with the keystroke
                                 state data for the key that was pressed.

  @retval EFI_SUCCESS            The keystroke information was returned.
  @retval EFI_NOT_READY          There was no keystroke data available.
  @retval EFI_DEVICE_ERROR       The keystroke information was not returned due to
                                 hardware errors.
  @retval EFI_INVALID_PARAMETER  KeyData is NULL.

**/
EFI_STATUS
EFIAPI
HidKbReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  OUT EFI_KEY_DATA                      *KeyData
  )
{
  HID_KB_DEV                         *HidKbDev;

  if (KeyData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_EX_PROTOCOL (This);

  return HidKbReadKeyStrokeWorker (HidKbDev, KeyData);

}

/**
  Set certain state for the input device.

  @param  This                    Protocol instance pointer.
  @param  KeyToggleState          A pointer to the EFI_KEY_TOGGLE_STATE to set the
                                  state for the input device.

  @retval EFI_SUCCESS             The device state was set appropriately.
  @retval EFI_DEVICE_ERROR        The device is not functioning correctly and could
                                  not have the setting adjusted.
  @retval EFI_UNSUPPORTED         The device does not support the ability to have its state set.
  @retval EFI_INVALID_PARAMETER   KeyToggleState is NULL.

**/
EFI_STATUS
EFIAPI
HidKbSetState (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_TOGGLE_STATE               *KeyToggleState
  )
{
  HID_KB_DEV                         *HidKbDev;

  if (KeyToggleState == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_EX_PROTOCOL (This);

  if (((HidKbDev->KeyState.KeyToggleState & EFI_TOGGLE_STATE_VALID) != EFI_TOGGLE_STATE_VALID) ||
      ((*KeyToggleState & EFI_TOGGLE_STATE_VALID) != EFI_TOGGLE_STATE_VALID)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Update the status light
  //

  HidKbDev->LedKeyState[LED_KEY_CAPSLOCK]   = FALSE;
  HidKbDev->LedKeyState[LED_KEY_NUMLOCK]    = FALSE;
  HidKbDev->LedKeyState[LED_KEY_SCROLL]     = FALSE;
  HidKbDev->IsSupportPartialKey   = FALSE;

  if ((*KeyToggleState & EFI_SCROLL_LOCK_ACTIVE) == EFI_SCROLL_LOCK_ACTIVE) {
    HidKbDev->LedKeyState[LED_KEY_SCROLL] = TRUE;
  }
  if ((*KeyToggleState & EFI_NUM_LOCK_ACTIVE) == EFI_NUM_LOCK_ACTIVE) {
    HidKbDev->LedKeyState[LED_KEY_NUMLOCK] = TRUE;
  }
  if ((*KeyToggleState & EFI_CAPS_LOCK_ACTIVE) == EFI_CAPS_LOCK_ACTIVE) {
    HidKbDev->LedKeyState[LED_KEY_CAPSLOCK] = TRUE;
  }
  if ((*KeyToggleState & EFI_KEY_STATE_EXPOSED) == EFI_KEY_STATE_EXPOSED) {
    HidKbDev->IsSupportPartialKey = TRUE;
  }

  SetKeyLED (HidKbDev);

  HidKbDev->KeyState.KeyToggleState = *KeyToggleState;

  return EFI_SUCCESS;

}

/**
  Register a notification function for a particular keystroke for the input device.

  @param  This                        Protocol instance pointer.
  @param  KeyData                     A pointer to a buffer that is filled in with the keystroke
                                      information data for the key that was pressed.
  @param  KeyNotificationFunction     Points to the function to be called when the key
                                      sequence is typed specified by KeyData.
  @param  NotifyHandle                Points to the unique handle assigned to the registered notification.

  @retval EFI_SUCCESS                 The notification function was registered successfully.
  @retval EFI_OUT_OF_RESOURCES        Unable to allocate resources for necessary data structures.
  @retval EFI_INVALID_PARAMETER       KeyData or NotifyHandle or KeyNotificationFunction is NULL.

**/
EFI_STATUS
EFIAPI
HidKbRegisterKeyNotify (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  EFI_KEY_DATA                       *KeyData,
  IN  EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
  OUT EFI_HANDLE                         *NotifyHandle
  )
{
  HID_KB_DEV                         *HidKbDev;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *NewNotify;
  LIST_ENTRY                        *Link;
  LIST_ENTRY                        *NotifyList;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *CurrentNotify;

  if (KeyData == NULL || NotifyHandle == NULL || KeyNotificationFunction == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_EX_PROTOCOL (This);

  //
  // Return EFI_SUCCESS if the (KeyData, NotificationFunction) is already registered.
  //
  NotifyList = &HidKbDev->NotifyList;

  for (Link = GetFirstNode (NotifyList);
       !IsNull (NotifyList, Link);
       Link = GetNextNode (NotifyList, Link)) {
    CurrentNotify = CR (
                      Link,
                      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
                      NotifyEntry,
                      HID_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
                      );
    if (IsKeyRegistered (&CurrentNotify->KeyData, KeyData)) {
      if (CurrentNotify->KeyNotificationFn == KeyNotificationFunction) {
        *NotifyHandle = CurrentNotify->NotifyHandle;
        return EFI_SUCCESS;
      }
    }
  }

  //
  // Allocate resource to save the notification function
  //
  NewNotify = (KEYBOARD_CONSOLE_IN_EX_NOTIFY *) AllocateZeroPool (sizeof (KEYBOARD_CONSOLE_IN_EX_NOTIFY));
  if (NewNotify == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  NewNotify->Signature         = HID_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE;
  NewNotify->KeyNotificationFn = KeyNotificationFunction;
  NewNotify->NotifyHandle      = (EFI_HANDLE) NewNotify;
  CopyMem (&NewNotify->KeyData, KeyData, sizeof (EFI_KEY_DATA));
  InsertTailList (&HidKbDev->NotifyList, &NewNotify->NotifyEntry);


  *NotifyHandle = NewNotify->NotifyHandle;

  return EFI_SUCCESS;
}

/**
  Remove a registered notification function from a particular keystroke.

  @param  This                      Protocol instance pointer.
  @param  NotificationHandle        The handle of the notification function being unregistered.

  @retval EFI_SUCCESS              The notification function was unregistered successfully.
  @retval EFI_INVALID_PARAMETER    The NotificationHandle is invalid

**/
EFI_STATUS
EFIAPI
HidKbUnregisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_HANDLE                         NotificationHandle
  )
{
  HID_KB_DEV                         *HidKbDev;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *CurrentNotify;
  LIST_ENTRY                        *Link;
  LIST_ENTRY                        *NotifyList;

  if (NotificationHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HidKbDev = HID_KB_DEV_FROM_SIMPLE_TEXT_IN_EX_PROTOCOL (This);

  //
  // Traverse notify list of HID keyboard and remove the entry of NotificationHandle.
  //
  NotifyList = &HidKbDev->NotifyList;
  for (Link = GetFirstNode (NotifyList);
       !IsNull (NotifyList, Link);
       Link = GetNextNode (NotifyList, Link)) {
    CurrentNotify = CR (
                      Link,
                      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
                      NotifyEntry,
                      HID_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
                      );
    if (CurrentNotify->NotifyHandle == NotificationHandle) {
      //
      // Remove the notification function from NotifyList and free resources
      //
      RemoveEntryList (&CurrentNotify->NotifyEntry);

      FreePool (CurrentNotify);
      return EFI_SUCCESS;
    }
  }

  //
  // Cannot find the matching entry in database.
  //
  return EFI_INVALID_PARAMETER;
}

