//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The help function prototypes of HidKbDxe driver.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _EFI_KEYBOARD_H_
#define _EFI_KEYBOARD_H_


#define HID_KEYBOARD_KEY_COUNT            105

#define HID_KEYBOARD_LANGUAGE_STR_LEN     5         // RFC4646 Language Code: "en-US"
#define HID_KEYBOARD_DESCRIPTION_STR_LEN  (16 + 1)  // Description: "English Keyboard"

#define BOOT_PROTOCOL           0
#define REPORT_PROTOCOL         1

#pragma pack (1)
typedef struct {
  //
  // This 4-bytes total array length is required by PreparePackageList()
  //
  UINT32                 Length;

  //
  // Keyboard Layout package definition
  //
  EFI_HII_PACKAGE_HEADER PackageHeader;
  UINT16                 LayoutCount;

  //
  // EFI_HII_KEYBOARD_LAYOUT
  //
  UINT16                 LayoutLength;
  EFI_GUID               Guid;
  UINT32                 LayoutDescriptorStringOffset;
  UINT8                  DescriptorCount;
  EFI_KEY_DESCRIPTOR     KeyDescriptor[HID_KEYBOARD_KEY_COUNT];
  UINT16                 DescriptionCount;
  CHAR16                 Language[HID_KEYBOARD_LANGUAGE_STR_LEN];
  CHAR16                 Space;
  CHAR16                 DescriptionString[HID_KEYBOARD_DESCRIPTION_STR_LEN];
} HID_KEYBOARD_LAYOUT_PACK_BIN;
#pragma pack()

/**
  Initialize HID keyboard device and all private data structures.

  @param  HidKbDev  The HID_KB_DEV instance.

  @retval EFI_SUCCESS        Initialization is successful.
  @retval EFI_DEVICE_ERROR   Keyboard initialization failed.

**/
EFI_STATUS
InitHidKeyboard (
  IN OUT HID_KB_DEV   *HidKbDev
  );

/**
  Initialize HID keyboard layout.

  This function initializes Key Convertion Table for the HID keyboard device.
  It first tries to retrieve layout from HII database. If failed and default
  layout is enabled, then it just uses the default layout.

  @param  HidKbDev      The HID_KB_DEV instance.

  @retval EFI_SUCCESS            Initialization succeeded.
  @retval EFI_NOT_READY          Keyboard layout cannot be retrieve from HII
                                 database, and default layout is disabled.
  @retval Other                  Fail to register event to EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID group.

**/
EFI_STATUS
InitKeyboardLayout (
  OUT HID_KB_DEV   *HidKbDev
  );

/**
  Destroy resources for keyboard layout.

  @param  HidKbDev    The HID_KB_DEV instance.

**/
VOID
ReleaseKeyboardLayoutResources (
  IN OUT HID_KB_DEV              *HidKbDev
  );

/**
  Handler function for HID keyboard's asynchronous interrupt transfer.

  This function is the handler function for HID keyboard's asynchronous interrupt transfer
  to manage the keyboard. It parses the HID keyboard input report, and inserts data to
  keyboard buffer according to state of modifer keys and normal keys. Timer for repeat key
  is also set accordingly.

  @param  Data             A pointer to a buffer that is filled with key data which is
                           retrieved via asynchronous interrupt transfer.
  @param  DataLength       Indicates the size of the data buffer.
  @param  Context          Pointing to HID_KB_DEV instance.

  @retval EFI_SUCCESS      Asynchronous interrupt transfer is handled successfully.
  @retval EFI_DEVICE_ERROR Hardware error occurs.

**/
EFI_STATUS
EFIAPI
KeyboardHandler (
  IN  VOID          *Data,
  IN  UINTN         DataLength,
  IN  VOID          *Context
  );

/**
  Retrieves a HID keycode after parsing the raw data in keyboard buffer.

  This function parses keyboard buffer. It updates state of modifier key for
  HID_KB_DEV instancem, and returns keycode for output.

  @param  HidKbDev    The HID_KB_DEV instance.
  @param  KeyCode              Pointer to the HID keycode for output.

  @retval EFI_SUCCESS          Keycode successfully parsed.
  @retval EFI_NOT_READY        Keyboard buffer is not ready for a valid keycode

**/
EFI_STATUS
HidParseKey (
  IN OUT  HID_KB_DEV  *HidKbDev,
  OUT     UINT8       *KeyCode
  );

/**
  Converts HID Keycode ranging from 0x4 to 0x65 to EFI_INPUT_KEY.

  @param  HidKbDev     The HID_KB_DEV instance.
  @param  KeyCode               Indicates the key code that will be interpreted.
  @param  KeyData               A pointer to a buffer that is filled in with
                                the keystroke information for the key that
                                was pressed.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER KeyCode is not in the range of 0x4 to 0x65.
  @retval EFI_INVALID_PARAMETER Translated EFI_INPUT_KEY has zero for both ScanCode and UnicodeChar.
  @retval EFI_NOT_READY         KeyCode represents a dead key with EFI_NS_KEY_MODIFIER
  @retval EFI_DEVICE_ERROR      Keyboard layout is invalid.

**/
EFI_STATUS
HidKeyCodeToEfiInputKey (
  IN  HID_KB_DEV      *HidKbDev,
  IN  UINT8           KeyCode,
  OUT EFI_KEY_DATA    *KeyData
  );


/**
  Create the queue.

  @param  Queue     Points to the queue.
  @param  ItemSize  Size of the single item.

**/
VOID
InitQueue (
  IN OUT  HID_SIMPLE_QUEUE   *Queue,
  IN      UINTN              ItemSize
  );

/**
  Destroy the queue

  @param Queue    Points to the queue.
**/
VOID
DestroyQueue (
  IN OUT HID_SIMPLE_QUEUE   *Queue
  );


/**
  Check whether the queue is empty.

  @param  Queue     Points to the queue.

  @retval TRUE      Queue is empty.
  @retval FALSE     Queue is not empty.

**/
BOOLEAN
IsQueueEmpty (
  IN  HID_SIMPLE_QUEUE   *Queue
  );


/**
  Check whether the queue is full.

  @param  Queue     Points to the queue.

  @retval TRUE      Queue is full.
  @retval FALSE     Queue is not full.

**/
BOOLEAN
IsQueueFull (
  IN  HID_SIMPLE_QUEUE   *Queue
  );


/**
  Enqueue the item to the queue.

  @param  Queue     Points to the queue.
  @param  Item      Points to the item to be enqueued.
  @param  ItemSize  Size of the item.
**/
VOID
Enqueue (
  IN OUT  HID_SIMPLE_QUEUE *Queue,
  IN      VOID             *Item,
  IN      UINTN            ItemSize
  );


/**
  Dequeue a item from the queue.

  @param  Queue     Points to the queue.
  @param  Item      Receives the item.
  @param  ItemSize  Size of the item.

  @retval EFI_SUCCESS        Item was successfully dequeued.
  @retval EFI_DEVICE_ERROR   The queue is empty.

**/
EFI_STATUS
Dequeue (
  IN OUT  HID_SIMPLE_QUEUE *Queue,
     OUT  VOID             *Item,
  IN      UINTN            ItemSize
  );

/**
  Handler for Repeat Key event.

  This function is the handler for Repeat Key event triggered
  by timer.
  After a repeatable key is pressed, the event would be triggered
  with interval of HIDKBD_REPEAT_DELAY. Once the event is triggered,
  following trigger will come with interval of HIDKBD_REPEAT_RATE.

  @param  Event              The Repeat Key event.
  @param  Context            Points to the HID_KB_DEV instance.

**/
VOID
EFIAPI
HidKbRepeatHandler (
  IN    EFI_EVENT    Event,
  IN    VOID         *Context
  );

/**
  Sets HID keyboard LED state.

  @param  HidKbDev  The HID_KB_DEV instance.

**/
VOID
SetKeyLED (
  IN  HID_KB_DEV    *HidKbDev
  );

#endif

