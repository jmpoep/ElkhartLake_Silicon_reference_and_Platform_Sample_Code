//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Helper functions for HID Keyboard Driver.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>
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

#define HI_BYTE(x)  (x & 0xff00)  // Extracts the Most Significant byte of UINT16
#define LO_BYTE(x)  (x & 0x00ff)  // Extracts the Least Significant byte of UINT16

HID_KEYBOARD_LAYOUT_PACK_BIN  mHidKeyboardLayoutBin = {
  sizeof (HID_KEYBOARD_LAYOUT_PACK_BIN),   // Binary size

  //
  // EFI_HII_PACKAGE_HEADER
  //
  {
    sizeof (HID_KEYBOARD_LAYOUT_PACK_BIN) - sizeof (UINT32),
    EFI_HII_PACKAGE_KEYBOARD_LAYOUT
  },
  1,  // LayoutCount
  sizeof (HID_KEYBOARD_LAYOUT_PACK_BIN) - sizeof (UINT32) - sizeof (EFI_HII_PACKAGE_HEADER) - sizeof (UINT16), // LayoutLength
  HID_KEYBOARD_LAYOUT_KEY_GUID,  // KeyGuid
  sizeof (UINT16) + sizeof (EFI_GUID) + sizeof (UINT32) + sizeof (UINT8) + (HID_KEYBOARD_KEY_COUNT * sizeof (EFI_KEY_DESCRIPTOR)), // LayoutDescriptorStringOffset
  HID_KEYBOARD_KEY_COUNT, // DescriptorCount
  {
    //
    // EFI_KEY_DESCRIPTOR (total number is HID_KEYBOARD_KEY_COUNT)
    //
    {EfiKeyC1,         'a',      'A',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB5,         'b',      'B',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB3,         'c',      'C',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC3,         'd',      'D',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD3,         'e',      'E',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC4,         'f',      'F',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC5,         'g',      'G',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC6,         'h',      'H',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD8,         'i',      'I',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC7,         'j',      'J',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC8,         'k',      'K',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC9,         'l',      'L',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB7,         'm',      'M',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB6,         'n',      'N',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD9,         'o',      'O',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD10,        'p',      'P',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD1,         'q',      'Q',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD4,         'r',      'R',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyC2,         's',      'S',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD5,         't',      'T',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD7,         'u',      'U',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB4,         'v',      'V',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD2,         'w',      'W',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB2,         'x',      'X',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyD6,         'y',      'Y',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyB1,         'z',      'Z',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_CAPS_LOCK},
    {EfiKeyE1,         '1',      '!',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE2,         '2',      '@',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE3,         '3',      '#',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE4,         '4',      '$',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE5,         '5',      '%',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE6,         '6',      '^',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE7,         '7',      '&',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE8,         '8',      '*',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE9,         '9',      '(',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE10,        '0',      ')',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyEnter,      0x0d,     0x0d, 0, 0,  EFI_NULL_MODIFIER,   0},
    {EfiKeyEsc,        0x1b,     0x1b, 0, 0,  EFI_NULL_MODIFIER,   0},
    {EfiKeyBackSpace,  0x08,     0x08, 0, 0,  EFI_NULL_MODIFIER,   0},
    {EfiKeyTab,        0x09,     0x09, 0, 0,  EFI_NULL_MODIFIER,   0},
    {EfiKeySpaceBar,   ' ',      ' ',  0, 0,  EFI_NULL_MODIFIER,   0},
    {EfiKeyE11,        '-',      '_',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE12,        '=',      '+',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyD11,        '[',      '{',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyD12,        ']',      '}',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyD13,        '\\',     '|',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyC12,        '\\',     '|',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyC10,        ';',      ':',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyC11,        '\'',     '"',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyE0,         '`',      '~',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyB8,         ',',      '<',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyB9,         '.',      '>',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyB10,        '/',      '?',  0, 0,  EFI_NULL_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT},
    {EfiKeyCapsLock,   0x00,     0x00, 0, 0,  EFI_CAPS_LOCK_MODIFIER,            0},
    {EfiKeyF1,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_ONE_MODIFIER,     0},
    {EfiKeyF2,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_TWO_MODIFIER,     0},
    {EfiKeyF3,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_THREE_MODIFIER,   0},
    {EfiKeyF4,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_FOUR_MODIFIER,    0},
    {EfiKeyF5,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_FIVE_MODIFIER,    0},
    {EfiKeyF6,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_SIX_MODIFIER,     0},
    {EfiKeyF7,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_SEVEN_MODIFIER,   0},
    {EfiKeyF8,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_EIGHT_MODIFIER,   0},
    {EfiKeyF9,         0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_NINE_MODIFIER,    0},
    {EfiKeyF10,        0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_TEN_MODIFIER,     0},
    {EfiKeyF11,        0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_ELEVEN_MODIFIER,  0},
    {EfiKeyF12,        0x00,     0x00, 0, 0,  EFI_FUNCTION_KEY_TWELVE_MODIFIER,  0},
    {EfiKeyPrint,      0x00,     0x00, 0, 0,  EFI_PRINT_MODIFIER,                0},
    {EfiKeySLck,       0x00,     0x00, 0, 0,  EFI_SCROLL_LOCK_MODIFIER,          0},
    {EfiKeyPause,      0x00,     0x00, 0, 0,  EFI_PAUSE_MODIFIER,                0},
    {EfiKeyIns,        0x00,     0x00, 0, 0,  EFI_INSERT_MODIFIER,               0},
    {EfiKeyHome,       0x00,     0x00, 0, 0,  EFI_HOME_MODIFIER,                 0},
    {EfiKeyPgUp,       0x00,     0x00, 0, 0,  EFI_PAGE_UP_MODIFIER,              0},
    {EfiKeyDel,        0x00,     0x00, 0, 0,  EFI_DELETE_MODIFIER,               0},
    {EfiKeyEnd,        0x00,     0x00, 0, 0,  EFI_END_MODIFIER,                  0},
    {EfiKeyPgDn,       0x00,     0x00, 0, 0,  EFI_PAGE_DOWN_MODIFIER,            0},
    {EfiKeyRightArrow, 0x00,     0x00, 0, 0,  EFI_RIGHT_ARROW_MODIFIER,          0},
    {EfiKeyLeftArrow,  0x00,     0x00, 0, 0,  EFI_LEFT_ARROW_MODIFIER,           0},
    {EfiKeyDownArrow,  0x00,     0x00, 0, 0,  EFI_DOWN_ARROW_MODIFIER,           0},
    {EfiKeyUpArrow,    0x00,     0x00, 0, 0,  EFI_UP_ARROW_MODIFIER,             0},
    {EfiKeyNLck,       0x00,     0x00, 0, 0,  EFI_NUM_LOCK_MODIFIER,             0},
    {EfiKeySlash,      '/',      '/',  0, 0,  EFI_NULL_MODIFIER,                 0},
    {EfiKeyAsterisk,   '*',      '*',  0, 0,  EFI_NULL_MODIFIER,                 0},
    {EfiKeyMinus,      '-',      '-',  0, 0,  EFI_NULL_MODIFIER,                 0},
    {EfiKeyPlus,       '+',      '+',  0, 0,  EFI_NULL_MODIFIER,                 0},
    {EfiKeyEnter,      0x0d,     0x0d, 0, 0,  EFI_NULL_MODIFIER,                 0},
    {EfiKeyOne,        '1',      '1',  0, 0,  EFI_END_MODIFIER,         EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyTwo,        '2',      '2',  0, 0,  EFI_DOWN_ARROW_MODIFIER,  EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyThree,      '3',      '3',  0, 0,  EFI_PAGE_DOWN_MODIFIER,   EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyFour,       '4',      '4',  0, 0,  EFI_LEFT_ARROW_MODIFIER,  EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyFive,       '5',      '5',  0, 0,  EFI_NULL_MODIFIER,        EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeySix,        '6',      '6',  0, 0,  EFI_RIGHT_ARROW_MODIFIER, EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeySeven,      '7',      '7',  0, 0,  EFI_HOME_MODIFIER,        EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyEight,      '8',      '8',  0, 0,  EFI_UP_ARROW_MODIFIER,    EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyNine,       '9',      '9',  0, 0,  EFI_PAGE_UP_MODIFIER,     EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyZero,       '0',      '0',  0, 0,  EFI_INSERT_MODIFIER,      EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyPeriod,     '.',      '.',  0, 0,  EFI_DELETE_MODIFIER,      EFI_AFFECTED_BY_STANDARD_SHIFT | EFI_AFFECTED_BY_NUM_LOCK},
    {EfiKeyA4,         0x00,     0x00, 0, 0,  EFI_MENU_MODIFIER,            0},
    {EfiKeyLCtrl,      0,        0,    0, 0,  EFI_LEFT_CONTROL_MODIFIER,    0},
    {EfiKeyLShift,     0,        0,    0, 0,  EFI_LEFT_SHIFT_MODIFIER,      0},
    {EfiKeyLAlt,       0,        0,    0, 0,  EFI_LEFT_ALT_MODIFIER,        0},
    {EfiKeyA0,         0,        0,    0, 0,  EFI_LEFT_LOGO_MODIFIER,       0},
    {EfiKeyRCtrl,      0,        0,    0, 0,  EFI_RIGHT_CONTROL_MODIFIER,   0},
    {EfiKeyRShift,     0,        0,    0, 0,  EFI_RIGHT_SHIFT_MODIFIER,     0},
    {EfiKeyA2,         0,        0,    0, 0,  EFI_RIGHT_ALT_MODIFIER,       0},
    {EfiKeyA3,         0,        0,    0, 0,  EFI_RIGHT_LOGO_MODIFIER,      0},
  },
  1,                          // DescriptionCount
  {'e', 'n', '-', 'U', 'S'},  // RFC4646 language code
  ' ',                        // Space
  {'E', 'n', 'g', 'l', 'i', 's', 'h', ' ', 'K', 'e', 'y', 'b', 'o', 'a', 'r', 'd', '\0'}, // DescriptionString[]
};

//
// Keyboard LED Indexes
//
enum {
  EFI_KEY_NUM_LOCK = 0x01,
  EFI_KEY_CAPS_LOCK,
  EFI_KEY_SCROLL_LOCK,
};

//
// EFI_KEY to HID Keycode conversion table
// EFI_KEY is defined in UEFI spec.
// HID Keycode is defined in HID HID Firmware spec.
//
UINT8 EfiKeyToHidKeyCodeConvertionTable[] = {
  0xe0,  //  EfiKeyLCtrl
  0xe3,  //  EfiKeyA0
  0xe2,  //  EfiKeyLAlt
  0x2c,  //  EfiKeySpaceBar
  0xe6,  //  EfiKeyA2
  0xe7,  //  EfiKeyA3
  0x65,  //  EfiKeyA4
  0xe4,  //  EfiKeyRCtrl
  0x50,  //  EfiKeyLeftArrow
  0x51,  //  EfiKeyDownArrow
  0x4F,  //  EfiKeyRightArrow
  0x62,  //  EfiKeyZero
  0x63,  //  EfiKeyPeriod
  0x28,  //  EfiKeyEnter
  0xe1,  //  EfiKeyLShift
  0x64,  //  EfiKeyB0
  0x1D,  //  EfiKeyB1
  0x1B,  //  EfiKeyB2
  0x06,  //  EfiKeyB3
  0x19,  //  EfiKeyB4
  0x05,  //  EfiKeyB5
  0x11,  //  EfiKeyB6
  0x10,  //  EfiKeyB7
  0x36,  //  EfiKeyB8
  0x37,  //  EfiKeyB9
  0x38,  //  EfiKeyB10
  0xe5,  //  EfiKeyRShift
  0x52,  //  EfiKeyUpArrow
  0x59,  //  EfiKeyOne
  0x5A,  //  EfiKeyTwo
  0x5B,  //  EfiKeyThree
  0x39,  //  EfiKeyCapsLock
  0x04,  //  EfiKeyC1
  0x16,  //  EfiKeyC2
  0x07,  //  EfiKeyC3
  0x09,  //  EfiKeyC4
  0x0A,  //  EfiKeyC5
  0x0B,  //  EfiKeyC6
  0x0D,  //  EfiKeyC7
  0x0E,  //  EfiKeyC8
  0x0F,  //  EfiKeyC9
  0x33,  //  EfiKeyC10
  0x34,  //  EfiKeyC11
  0x32,  //  EfiKeyC12
  0x5C,  //  EfiKeyFour
  0x5D,  //  EfiKeyFive
  0x5E,  //  EfiKeySix
  0x57,  //  EfiKeyPlus
  0x2B,  //  EfiKeyTab
  0x14,  //  EfiKeyD1
  0x1A,  //  EfiKeyD2
  0x08,  //  EfiKeyD3
  0x15,  //  EfiKeyD4
  0x17,  //  EfiKeyD5
  0x1C,  //  EfiKeyD6
  0x18,  //  EfiKeyD7
  0x0C,  //  EfiKeyD8
  0x12,  //  EfiKeyD9
  0x13,  //  EfiKeyD10
  0x2F,  //  EfiKeyD11
  0x30,  //  EfiKeyD12
  0x31,  //  EfiKeyD13
  0x4C,  //  EfiKeyDel
  0x4D,  //  EfiKeyEnd
  0x4E,  //  EfiKeyPgDn
  0x5F,  //  EfiKeySeven
  0x60,  //  EfiKeyEight
  0x61,  //  EfiKeyNine
  0x35,  //  EfiKeyE0
  0x1E,  //  EfiKeyE1
  0x1F,  //  EfiKeyE2
  0x20,  //  EfiKeyE3
  0x21,  //  EfiKeyE4
  0x22,  //  EfiKeyE5
  0x23,  //  EfiKeyE6
  0x24,  //  EfiKeyE7
  0x25,  //  EfiKeyE8
  0x26,  //  EfiKeyE9
  0x27,  //  EfiKeyE10
  0x2D,  //  EfiKeyE11
  0x2E,  //  EfiKeyE12
  0x2A,  //  EfiKeyBackSpace
  0x49,  //  EfiKeyIns
  0x4A,  //  EfiKeyHome
  0x4B,  //  EfiKeyPgUp
  0x53,  //  EfiKeyNLck
  0x54,  //  EfiKeySlash
  0x55,  //  EfiKeyAsterisk
  0x56,  //  EfiKeyMinus
  0x29,  //  EfiKeyEsc
  0x3A,  //  EfiKeyF1
  0x3B,  //  EfiKeyF2
  0x3C,  //  EfiKeyF3
  0x3D,  //  EfiKeyF4
  0x3E,  //  EfiKeyF5
  0x3F,  //  EfiKeyF6
  0x40,  //  EfiKeyF7
  0x41,  //  EfiKeyF8
  0x42,  //  EfiKeyF9
  0x43,  //  EfiKeyF10
  0x44,  //  EfiKeyF11
  0x45,  //  EfiKeyF12
  0x46,  //  EfiKeyPrint
  0x47,  //  EfiKeySLck
  0x48   //  EfiKeyPause
};

//
// Keyboard modifier value to EFI Scan Code convertion table
// EFI Scan Code and the modifier values are defined in UEFI spec.
//
UINT8 ModifierValueToEfiScanCodeConvertionTable[] = {
  SCAN_NULL,       // EFI_NULL_MODIFIER
  SCAN_NULL,       // EFI_LEFT_CONTROL_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_CONTROL_MODIFIER
  SCAN_NULL,       // EFI_LEFT_ALT_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_ALT_MODIFIER
  SCAN_NULL,       // EFI_ALT_GR_MODIFIER
  SCAN_INSERT,     // EFI_INSERT_MODIFIER
  SCAN_DELETE,     // EFI_DELETE_MODIFIER
  SCAN_PAGE_DOWN,  // EFI_PAGE_DOWN_MODIFIER
  SCAN_PAGE_UP,    // EFI_PAGE_UP_MODIFIER
  SCAN_HOME,       // EFI_HOME_MODIFIER
  SCAN_END,        // EFI_END_MODIFIER
  SCAN_NULL,       // EFI_LEFT_SHIFT_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_SHIFT_MODIFIER
  SCAN_NULL,       // EFI_CAPS_LOCK_MODIFIER
  SCAN_NULL,       // EFI_NUM_LOCK_MODIFIER
  SCAN_LEFT,       // EFI_LEFT_ARROW_MODIFIER
  SCAN_RIGHT,      // EFI_RIGHT_ARROW_MODIFIER
  SCAN_DOWN,       // EFI_DOWN_ARROW_MODIFIER
  SCAN_UP,         // EFI_UP_ARROW_MODIFIER
  SCAN_NULL,       // EFI_NS_KEY_MODIFIER
  SCAN_NULL,       // EFI_NS_KEY_DEPENDENCY_MODIFIER
  SCAN_F1,         // EFI_FUNCTION_KEY_ONE_MODIFIER
  SCAN_F2,         // EFI_FUNCTION_KEY_TWO_MODIFIER
  SCAN_F3,         // EFI_FUNCTION_KEY_THREE_MODIFIER
  SCAN_F4,         // EFI_FUNCTION_KEY_FOUR_MODIFIER
  SCAN_F5,         // EFI_FUNCTION_KEY_FIVE_MODIFIER
  SCAN_F6,         // EFI_FUNCTION_KEY_SIX_MODIFIER
  SCAN_F7,         // EFI_FUNCTION_KEY_SEVEN_MODIFIER
  SCAN_F8,         // EFI_FUNCTION_KEY_EIGHT_MODIFIER
  SCAN_F9,         // EFI_FUNCTION_KEY_NINE_MODIFIER
  SCAN_F10,        // EFI_FUNCTION_KEY_TEN_MODIFIER
  SCAN_F11,        // EFI_FUNCTION_KEY_ELEVEN_MODIFIER
  SCAN_F12,        // EFI_FUNCTION_KEY_TWELVE_MODIFIER
  //
  // For Partial Keystroke support
  //
  SCAN_NULL,       // EFI_PRINT_MODIFIER
  SCAN_NULL,       // EFI_SYS_REQUEST_MODIFIER
  SCAN_NULL,       // EFI_SCROLL_LOCK_MODIFIER
  SCAN_PAUSE,      // EFI_PAUSE_MODIFIER
  SCAN_NULL,       // EFI_BREAK_MODIFIER
  SCAN_NULL,       // EFI_LEFT_LOGO_MODIFIER
  SCAN_NULL,       // EFI_RIGHT_LOGO_MODIFER
  SCAN_NULL,       // EFI_MENU_MODIFER
};


/**
  Initialize Key Convention Table by using default keyboard layout.

  @param  HidKbDev    The HID_KB_DEV instance.

  @retval EFI_SUCCESS          The default keyboard layout was installed successfully
  @retval Others               Failure to install default keyboard layout.
**/
EFI_STATUS
InstallDefaultKeyboardLayout (
   IN OUT HID_KB_DEV           *HidKbDev
  )
{
  EFI_STATUS                   Status;
  EFI_HII_DATABASE_PROTOCOL    *HiiDatabase;
  EFI_HII_HANDLE               HiiHandle;

  //
  // Locate Hii database protocol
  //
  Status = gBS->LocateProtocol (
                  &gEfiHiiDatabaseProtocolGuid,
                  NULL,
                  (VOID **) &HiiDatabase
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install Keyboard Layout package to HII database
  //
  HiiHandle = HiiAddPackages (
                &gHidKeyboardLayoutPackageGuid,
                HidKbDev->ControllerHandle,
                &mHidKeyboardLayoutBin,
                NULL
                );
  if (HiiHandle == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Set current keyboard layout
  //
  Status = HiiDatabase->SetKeyboardLayout (HiiDatabase, &gHidKeyboardLayoutKeyGuid);

  return Status;
}

/**
  Get current keyboard layout from HII database.

  @return Pointer to HII Keyboard Layout.
          NULL means failure occurred while trying to get keyboard layout.

**/
EFI_HII_KEYBOARD_LAYOUT *
GetCurrentKeyboardLayout (
  VOID
  )
{
  EFI_STATUS                Status;
  EFI_HII_DATABASE_PROTOCOL *HiiDatabase;
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  UINT16                    Length;

  //
  // Locate HII Database Protocol
  //
  Status = gBS->LocateProtocol (
                  &gEfiHiiDatabaseProtocolGuid,
                  NULL,
                  (VOID **) &HiiDatabase
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  //
  // Get current keyboard layout from HII database
  //
  Length = 0;
  KeyboardLayout = NULL;
  Status = HiiDatabase->GetKeyboardLayout (
                          HiiDatabase,
                          NULL,
                          &Length,
                          KeyboardLayout
                          );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    KeyboardLayout = AllocatePool (Length);
    ASSERT (KeyboardLayout != NULL);

    Status = HiiDatabase->GetKeyboardLayout (
                            HiiDatabase,
                            NULL,
                            &Length,
                            KeyboardLayout
                            );
    if (EFI_ERROR (Status)) {
      FreePool (KeyboardLayout);
      KeyboardLayout = NULL;
    }
  }

  return KeyboardLayout;
}

/**
  Find Key Descriptor in Key Convertion Table given its HID keycode.

  @param  HidKbDev             The HID_KB_DEV instance.
  @param  KeyCode             HID Keycode.

  @return The Key Descriptor in Key Convertion Table.
          NULL means not found.

**/
EFI_KEY_DESCRIPTOR *
GetKeyDescriptor (
  IN HID_KB_DEV         *HidKbDev,
  IN UINT8             KeyCode
  )
{
  UINT8  Index;

  //
  // Make sure KeyCode is in the range of [0x4, 0x65] or [0xe0, 0xe7]
  //
  if ((!HIDKBD_VALID_KEYCODE (KeyCode)) || ((KeyCode > 0x65) && (KeyCode < 0xe0)) || (KeyCode > 0xe7)) {
    return NULL;
  }

  //
  // Calculate the index of Key Descriptor in Key Convertion Table
  //
  if (KeyCode <= 0x65) {
    Index = (UINT8) (KeyCode - 4);
  } else {
    Index = (UINT8) (KeyCode - 0xe0 + NUMBER_OF_VALID_NON_MODIFIER_HID_KEYCODE);
  }

  return &HidKbDev->KeyConvertionTable[Index];
}

/**
  Find Non-Spacing key for given Key descriptor.

  @param  HidKbDev              The HID_KB_DEV instance.
  @param  KeyDescriptor        Key descriptor.

  @return The Non-Spacing key corresponding to KeyDescriptor
          NULL means not found.

**/
HID_NS_KEY *
FindHidNsKey (
  IN HID_KB_DEV           *HidKbDev,
  IN EFI_KEY_DESCRIPTOR  *KeyDescriptor
  )
{
  LIST_ENTRY      *Link;
  LIST_ENTRY      *NsKeyList;
  HID_NS_KEY      *HidNsKey;

  NsKeyList = &HidKbDev->NsKeyList;
  Link = GetFirstNode (NsKeyList);
  while (!IsNull (NsKeyList, Link)) {
    HidNsKey = HID_NS_KEY_FORM_FROM_LINK (Link);

    if (HidNsKey->NsKey[0].Key == KeyDescriptor->Key) {
      return HidNsKey;
    }

    Link = GetNextNode (NsKeyList, Link);
  }

  return NULL;
}

/**
  Find physical key definition for a given key descriptor.

  For a specified non-spacing key, there are a list of physical
  keys following it. This function traverses the list of
  physical keys and tries to find the physical key matching
  the KeyDescriptor.

  @param  HidNsKey           The non-spacing key information.
  @param  KeyDescriptor     The key descriptor.

  @return The physical key definition.
          If no physical key is found, parameter KeyDescriptor is returned.

**/
EFI_KEY_DESCRIPTOR *
FindPhysicalKey (
  IN HID_NS_KEY           *HidNsKey,
  IN EFI_KEY_DESCRIPTOR  *KeyDescriptor
  )
{
  UINTN               Index;
  EFI_KEY_DESCRIPTOR  *PhysicalKey;

  PhysicalKey = &HidNsKey->NsKey[1];
  for (Index = 0; Index < HidNsKey->KeyCount; Index++) {
    if (KeyDescriptor->Key == PhysicalKey->Key) {
      return PhysicalKey;
    }

    PhysicalKey++;
  }

  //
  // No children definition matched, return original key
  //
  return KeyDescriptor;
}

/**
  The notification function for EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID.

  This function is registered to event of EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID
  group type, which will be triggered by EFI_HII_DATABASE_PROTOCOL.SetKeyboardLayout().
  It tries to get curent keyboard layout from HII database.

  @param  Event        Event being signaled.
  @param  Context      Points to HID_KB_DEV instance.

**/
VOID
EFIAPI
SetKeyboardLayoutEvent (
  IN EFI_EVENT              Event,
  IN VOID                   *Context
  )
{
  HID_KB_DEV                *HidKbDev;
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  EFI_KEY_DESCRIPTOR        TempKey;
  EFI_KEY_DESCRIPTOR        *KeyDescriptor;
  EFI_KEY_DESCRIPTOR        *TableEntry;
  EFI_KEY_DESCRIPTOR        *NsKey;
  HID_NS_KEY                *HidNsKey;
  UINTN                     Index;
  UINTN                     Index2;
  UINTN                     KeyCount;
  UINT8                     KeyCode;

  HidKbDev = (HID_KB_DEV *) Context;
  if (HidKbDev->Signature != HID_KB_DEV_SIGNATURE) {
    return;
  }

  //
  // Try to get current keyboard layout from HII database
  //
  KeyboardLayout = GetCurrentKeyboardLayout ();
  if (KeyboardLayout == NULL) {
    return;
  }

  //
  // Re-allocate resource for KeyConvertionTable
  //
  ReleaseKeyboardLayoutResources (HidKbDev);
  HidKbDev->KeyConvertionTable = AllocateZeroPool ((NUMBER_OF_VALID_HID_KEYCODE) * sizeof (EFI_KEY_DESCRIPTOR));
  ASSERT (HidKbDev->KeyConvertionTable != NULL);

  //
  // Traverse the list of key descriptors following the header of EFI_HII_KEYBOARD_LAYOUT
  //
  KeyDescriptor = (EFI_KEY_DESCRIPTOR *) (((UINT8 *) KeyboardLayout) + sizeof (EFI_HII_KEYBOARD_LAYOUT));
  for (Index = 0; Index < KeyboardLayout->DescriptorCount; Index++) {
    //
    // Copy from HII keyboard layout package binary for alignment
    //
    CopyMem (&TempKey, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

    //
    // Fill the key into KeyConvertionTable, whose index is calculated from HID keycode.
    //
    KeyCode = EfiKeyToHidKeyCodeConvertionTable [(UINT8) (TempKey.Key)];
    TableEntry = GetKeyDescriptor (HidKbDev, KeyCode);
    if (TableEntry == NULL) {
      ReleaseKeyboardLayoutResources (HidKbDev);
      FreePool (KeyboardLayout);
      return;
    }
    CopyMem (TableEntry, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

    //
    // For non-spacing key, create the list with a non-spacing key followed by physical keys.
    //
    if (TempKey.Modifier == EFI_NS_KEY_MODIFIER) {
      HidNsKey = AllocateZeroPool (sizeof (HID_NS_KEY));
      ASSERT (HidNsKey != NULL);

      //
      // Search for sequential children physical key definitions
      //
      KeyCount = 0;
      NsKey = KeyDescriptor + 1;
      for (Index2 = (UINT8) Index + 1; Index2 < KeyboardLayout->DescriptorCount; Index2++) {
        CopyMem (&TempKey, NsKey, sizeof (EFI_KEY_DESCRIPTOR));
        if (TempKey.Modifier == EFI_NS_KEY_DEPENDENCY_MODIFIER) {
          KeyCount++;
        } else {
          break;
        }
        NsKey++;
      }

      HidNsKey->Signature = HID_NS_KEY_SIGNATURE;
      HidNsKey->KeyCount = KeyCount;
      HidNsKey->NsKey = AllocateCopyPool (
                          (KeyCount + 1) * sizeof (EFI_KEY_DESCRIPTOR),
                          KeyDescriptor
                          );
      InsertTailList (&HidKbDev->NsKeyList, &HidNsKey->Link);

      //
      // Skip over the child physical keys
      //
      Index += KeyCount;
      KeyDescriptor += KeyCount;
    }

    KeyDescriptor++;
  }

  //
  // There are two EfiKeyEnter, duplicate its key descriptor
  //
  TableEntry = GetKeyDescriptor (HidKbDev, 0x58);
  KeyDescriptor = GetKeyDescriptor (HidKbDev, 0x28);
  CopyMem (TableEntry, KeyDescriptor, sizeof (EFI_KEY_DESCRIPTOR));

  FreePool (KeyboardLayout);
}

/**
  Destroy resources for keyboard layout.

  @param  HidKbDev    The HID_KB_DEV instance.

**/
VOID
ReleaseKeyboardLayoutResources (
  IN OUT HID_KB_DEV              *HidKbDev
  )
{
  HID_NS_KEY      *HidNsKey;
  LIST_ENTRY      *Link;

  if (HidKbDev->KeyConvertionTable != NULL) {
    FreePool (HidKbDev->KeyConvertionTable);
  }
  HidKbDev->KeyConvertionTable = NULL;

  while (!IsListEmpty (&HidKbDev->NsKeyList)) {
    Link = GetFirstNode (&HidKbDev->NsKeyList);
    HidNsKey = HID_NS_KEY_FORM_FROM_LINK (Link);
    RemoveEntryList (&HidNsKey->Link);

    FreePool (HidNsKey->NsKey);
    FreePool (HidNsKey);
  }
}

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
  )
{
  EFI_HII_KEYBOARD_LAYOUT   *KeyboardLayout;
  EFI_STATUS                Status;

  HidKbDev->KeyConvertionTable = AllocateZeroPool ((NUMBER_OF_VALID_HID_KEYCODE) * sizeof (EFI_KEY_DESCRIPTOR));
  ASSERT (HidKbDev->KeyConvertionTable != NULL);

  InitializeListHead (&HidKbDev->NsKeyList);
  HidKbDev->CurrentNsKey = NULL;
  HidKbDev->KeyboardLayoutEvent = NULL;

  //
  // Register event to EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID group,
  // which will be triggered by EFI_HII_DATABASE_PROTOCOL.SetKeyboardLayout().
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  SetKeyboardLayoutEvent,
                  HidKbDev,
                  &gEfiHiiKeyBoardLayoutGuid,
                  &HidKbDev->KeyboardLayoutEvent
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  KeyboardLayout = GetCurrentKeyboardLayout ();
  if (KeyboardLayout != NULL) {
    //
    // If current keyboard layout is successfully retrieved from HII database,
    // force to initialize the keyboard layout.
    //
    gBS->SignalEvent (HidKbDev->KeyboardLayoutEvent);
  } else {
    if (FeaturePcdGet (PcdDisableDefaultKeyboardLayoutInHidKbDriver)) {
      //
      // If no keyboard layout can be retrieved from HII database, and default layout
      // is disabled, then return EFI_NOT_READY.
      //
      return EFI_NOT_READY;
    }
    //
    // If no keyboard layout can be retrieved from HII database, and default layout
    // is enabled, then load the default keyboard layout.
    //
    InstallDefaultKeyboardLayout (HidKbDev);
  }

  return EFI_SUCCESS;
}


/**
  Initialize HID keyboard device and all private data structures.

  @param  HidKbDev  The HID_KB_DEV instance.

  @retval EFI_SUCCESS        Initialization is successful.
  @retval EFI_DEVICE_ERROR   Keyboard initialization failed.

**/
EFI_STATUS
InitHidKeyboard (
  IN OUT HID_KB_DEV   *HidKbDev
  )
{
  UINT8               ReportId;
  UINT8               Duration;

  InitQueue (&HidKbDev->HidKeyQueue, sizeof (HID_KEY));
  InitQueue (&HidKbDev->EfiKeyQueue, sizeof (EFI_KEY_DATA));

  //
  // ReportId is zero, which means the idle rate applies to all input reports.
  //
  ReportId = 0;
  //
  // Duration is zero, which means the duration is infinite.
  // so the endpoint will inhibit reporting forever,
  // and only reporting when a change is detected in the report data.
  //
  Duration = 0;
  HidSetIdleRequest (
    HidKbDev->Hid,
    ReportId,
    Duration
    );

  HidKbDev->CtrlOn     = FALSE;
  HidKbDev->AltOn      = FALSE;
  HidKbDev->LedKeyState[LED_KEY_SHIFT]    = FALSE;
  HidKbDev->LedKeyState[LED_KEY_NUMLOCK]  = FALSE;
  HidKbDev->LedKeyState[LED_KEY_CAPSLOCK] = FALSE;
  HidKbDev->LedKeyState[LED_KEY_SCROLL]   = FALSE;

  HidKbDev->LeftCtrlOn   = FALSE;
  HidKbDev->LeftAltOn    = FALSE;
  HidKbDev->LeftShiftOn  = FALSE;
  HidKbDev->LeftLogoOn   = FALSE;
  HidKbDev->RightCtrlOn  = FALSE;
  HidKbDev->RightAltOn   = FALSE;
  HidKbDev->RightShiftOn = FALSE;
  HidKbDev->RightLogoOn  = FALSE;
  HidKbDev->MenuKeyOn    = FALSE;
  HidKbDev->SysReqOn     = FALSE;

  HidKbDev->AltGrOn      = FALSE;

  HidKbDev->CurrentNsKey = NULL;

  //
  // Sync the initial state of lights on keyboard.
  //
  SetKeyLED (HidKbDev);

  ZeroMem (HidKbDev->LastKeyCodeArray, sizeof (UINT8) * 8);

  //
  // Create event for repeat keys' generation.
  //
  if (HidKbDev->RepeatTimer != NULL) {
    gBS->CloseEvent (HidKbDev->RepeatTimer);
    HidKbDev->RepeatTimer = NULL;
  }

  gBS->CreateEvent (
         EVT_TIMER | EVT_NOTIFY_SIGNAL,
         TPL_CALLBACK,
         HidKbRepeatHandler,
         HidKbDev,
         &HidKbDev->RepeatTimer
         );

  HidStartNotification (HidKbDev->Hid);

  return EFI_SUCCESS;
}

/**

  Checks whether a key is in Key buffer.

  @param[in]  Key           The Key code.
  @param[in]  KeyBuffer     Point to the key buffer.
  @param[in]  Size          The size of key buffer.

  @retval  TRUE   If Key is found in buffer.
  @retval  FALSE  If key is not found in the buffer.

**/
BOOLEAN
EFIAPI
IsKeyInBuffer(
  IN UINT8    Key,
  IN UINT8    KeyBuffer[],
  IN UINT32   Size)
{
  UINT8 Index;

  for (Index = 0; Index < Size; Index++){
    // Ignore the 0x00 codes
    if (KeyBuffer[Index] == 0) {
      continue;
    }

    // If found in key buffer then return True
    if (Key == KeyBuffer[Index]) {
      return TRUE;
    }
  }

  return FALSE;
}

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
  )
{
  HID_KB_DEV         *HidKbDev;
  HID_KEY            HidKey;
  UINT8              ReportId;
  UINT16             Buffer;
  UINT8              *DataPtr;
  UINT8              SaveData[MAX_KEYCODE_BUFF_SIZE];
  UINT8              SaveDataIndex;
  LIST_ENTRY         *Link;
  LIST_ENTRY         *Cur;
  UINT32             BitsRemaning;
  UINT32             Limit;
  HID_REPORT_FMT     *ReportItem;
  UINT16             Index;
  EFI_KEY_DESCRIPTOR *KeyDescriptor;

  ZeroMem (SaveData, sizeof (SaveData));
  SaveDataIndex = 0;

  ASSERT (Context != NULL);
  BitsRemaning = 8;
  DataPtr = (UINT8*)Data;

  // Extract the ReportId
  ReportId = DataPtr[0];
  DataPtr ++;
  DataLength --;

  HidKbDev = (HID_KB_DEV *) Context;

  // Workaround: Belkin Mobile Wireless Keyboard and Microsoft Universal Foldable Keyboard
  // Consumer Page(0x0C) USAGE instead of Keyboard/Keypad Page(0x07) to send ESCAPE key
  // So for above two keyboards converting USAGE ID from Consumer Page to Keyboard/Keypad Page
  // for ESCAPE key.
  if (DataLength == 2) {
    if (((DataPtr[0] == 0x40) && (DataPtr[1] == 0x00)) || ((DataPtr[0] == 0x23) && (DataPtr[1] == 0x02))) {
          HidKey.KeyCode = 0x29;
          HidKey.Down    = TRUE;
          Enqueue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));

          return EFI_SUCCESS;
        }
  }

  HidKbDev->Hid->GetReportFormatList(HidKbDev->Hid, &Link);

  Cur  = GetFirstNode (Link);

  HidKbDev->RepeatKey = 0x00;

  Buffer = (UINT16)DataPtr[0];
  BitsRemaning = 8;

  while (!IsNull (Link, Cur)) {

    ReportItem = ITEM_FROM_LINK(Cur);

    // Check if the item is of the input type
    if ( ReportItem->ReportId != ReportId || ReportItem->Type != BT_HID_ITEM_TYPE_INPUT || ReportItem->UsagePage != BT_HID_KEYBOARD_USAGE_PAGE ) {
      Cur = GetNextNode (Link, Cur);
      continue;
    }

    switch (ReportItem->ArrVar) {
      case BT_HID_ITEM_TYPE_VARIABLE:
        // This section is for parsing the modifier keys
        for (Index = 0; Index < ReportItem->ReportCount; Index++) {
          if (BitsRemaning < ReportItem->ReportSize) {
            Buffer = Buffer << BitsRemaning;
            DataPtr ++;

            // Refill the lower byte of the Buffer
            // and retain the higer byte as is
            Buffer |= (UINT16)DataPtr[0];

            Buffer = Buffer << (ReportItem->ReportSize - BitsRemaning);
            BitsRemaning = 8 - (ReportItem->ReportSize - BitsRemaning);
          } else {
            Buffer = Buffer << ReportItem->ReportSize;
            BitsRemaning -= ReportItem->ReportSize;
          }

          // Bit position is same as the indexing, so substract from 7
          HidKey.KeyCode = (UINT8)(ReportItem->UsageMin + 7 - Index);
          if (HI_BYTE(Buffer) != 0)
            HidKey.Down = TRUE;
          else
            HidKey.Down = FALSE;

          // Skip if it's constant
          if (ReportItem->DatConst == 0)
            Enqueue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));
          Buffer &= 0x00ff;
        }

      break;

      case BT_HID_ITEM_TYPE_ARRAY:
        // This section is for handling the normal keycodes
        Limit = (ReportItem->ReportCount < MAX_KEYCODE_BUFF_SIZE) ? ReportItem->ReportCount : MAX_KEYCODE_BUFF_SIZE;

        for (Index=0; Index < ReportItem->ReportCount; Index++) {

          if (BitsRemaning < ReportItem->ReportSize) {
            Buffer = Buffer << BitsRemaning;
            DataPtr ++;

            // Refill the lower byte of the Buffer
            // and retain the higer byte as is
            Buffer |= (UINT16)DataPtr[0];

            Buffer = Buffer << (ReportItem->ReportSize - BitsRemaning);
            BitsRemaning = 8 - (ReportItem->ReportSize - BitsRemaning);
          } else {
            Buffer = Buffer << ReportItem->ReportSize;
            BitsRemaning -= ReportItem->ReportSize;
          }

          //
          // Constant bits may exist for certain OEM specific usage. Don't care it here.
          //
          if (ReportItem->DatConst == 0) {
            HidKey.KeyCode = (UINT8)(ReportItem->UsageMin + (Buffer >> 8));

            if (SaveDataIndex < MAX_KEYCODE_BUFF_SIZE) {
              SaveData[SaveDataIndex++] = (Buffer >> 8);
            }

            // The basic key detection algorithm is:
            // A key is pressed if it's not in old buffer but in new buffer.
            // A key is released if it's in old buffer but not in new buffer.
            if (HidKey.KeyCode != 0) {
              if (!IsKeyInBuffer (HidKey.KeyCode, HidKbDev->OldKeyBuffer, Limit)) {
                HidKbDev->RepeatKey = HidKey.KeyCode;
                HidKey.Down = TRUE;
              }
            }

            // Skip adding the key if it's a constant. Add only if it's a new key!
            if (HidKbDev->RepeatKey != HidKbDev->PreviousKey) {
              Enqueue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));
            }
          }

          Buffer &= 0x00ff;
        }

        // Check if the old key was released
        for ( Index = 0; Index < Limit; Index++ ){
          // Ignore the 0x00 codes
          if (HidKbDev->OldKeyBuffer[Index] == 0) {
            continue;
          }

          // Check if Old key is present in incoming New key input buffer.
          // Release it if it's not present.
          if (!IsKeyInBuffer (HidKbDev->OldKeyBuffer[Index], SaveData, Limit)){
            HidKey.KeyCode = HidKbDev->OldKeyBuffer[Index];
            HidKey.Down = FALSE;
            Enqueue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));
          }
        }

        // Update the old KeyBuffer
        for ( Index = 0; Index < MAX_KEYCODE_BUFF_SIZE; Index ++ ) {
          HidKbDev->OldKeyBuffer[Index] = SaveData[Index];
        }

      break;
    }

    Cur = GetNextNode (Link, Cur);
  }

  // Stop the timer in case there is no repeat key and the timer is running
  if ( HidKbDev->RepeatKey == 0x00 && HidKbDev->TimerSet == TRUE ) {
    gBS->SetTimer (
             HidKbDev->RepeatTimer,
             TimerCancel,
             HIDKBD_REPEAT_RATE
             );

    HidKbDev->PreviousKey = 0x00;
    HidKbDev->TimerSet = FALSE;
  }

  // Set or Clear the Repeat Key
  if ( HidKbDev->RepeatKey != HidKbDev->PreviousKey ) {

    // Check to see if CAPSLOCK or NUMLOCK is pressed.
    KeyDescriptor = GetKeyDescriptor (HidKbDev,HidKbDev->RepeatKey);
    if (KeyDescriptor != NULL) {
      if (KeyDescriptor->Modifier == EFI_NUM_LOCK_MODIFIER || KeyDescriptor->Modifier == EFI_CAPS_LOCK_MODIFIER) {
        return EFI_SUCCESS;
      }
    }

    // Start a timer
    gBS->SetTimer (
             HidKbDev->RepeatTimer,
             TimerRelative,
             HIDKBD_REPEAT_DELAY
             );

    HidKbDev->PreviousKey = HidKbDev->RepeatKey;
    HidKbDev->TimerSet = TRUE;
  }

  return EFI_SUCCESS;
}


/**
  Retrieves a HID keycode after parsing the raw data in keyboard buffer.

  This function parses keyboard buffer. It updates state of modifier key for
  HID_KB_DEV instancem, and returns keycode for output.

  @param  HidKbDev              The HID_KB_DEV instance.
  @param  KeyCode              Pointer to the HID keycode for output.

  @retval EFI_SUCCESS          Keycode successfully parsed.
  @retval EFI_NOT_READY        Keyboard buffer is not ready for a valid keycode

**/
EFI_STATUS
HidParseKey (
  IN OUT  HID_KB_DEV   *HidKbDev,
     OUT  UINT8       *KeyCode
  )
{
  HID_KEY              HidKey;
  EFI_KEY_DESCRIPTOR  *KeyDescriptor;

  *KeyCode = 0;

  while (!IsQueueEmpty (&HidKbDev->HidKeyQueue)) {
    //
    // Pops one raw data off.
    //
    Dequeue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));

    KeyDescriptor = GetKeyDescriptor (HidKbDev, HidKey.KeyCode);
    if (KeyDescriptor == NULL)
      continue;

    if (!HidKey.Down) {
      //
      // Key is released.
      //
      switch (KeyDescriptor->Modifier) {

      //
      // Ctrl release
      //
      case EFI_LEFT_CONTROL_MODIFIER:
        HidKbDev->LeftCtrlOn = FALSE;
        break;
      case EFI_RIGHT_CONTROL_MODIFIER:
        HidKbDev->RightCtrlOn = FALSE;
        break;

      //
      // Shift release
      //
      case EFI_LEFT_SHIFT_MODIFIER:
        HidKbDev->LeftShiftOn = FALSE;
        break;
      case EFI_RIGHT_SHIFT_MODIFIER:
        HidKbDev->RightShiftOn = FALSE;
        break;

      //
      // Alt release
      //
      case EFI_LEFT_ALT_MODIFIER:
        HidKbDev->LeftAltOn = FALSE;
        break;
      case EFI_RIGHT_ALT_MODIFIER:
        HidKbDev->RightAltOn = FALSE;
        break;

      //
      // Left Logo release
      //
      case EFI_LEFT_LOGO_MODIFIER:
        HidKbDev->LeftLogoOn = FALSE;
        break;

      //
      // Right Logo release
      //
      case EFI_RIGHT_LOGO_MODIFIER:
        HidKbDev->RightLogoOn = FALSE;
        break;

      //
      // Menu key release
      //
      case EFI_MENU_MODIFIER:
        HidKbDev->MenuKeyOn = FALSE;
        break;

      //
      // SysReq release
      //
      case EFI_PRINT_MODIFIER:
      case EFI_SYS_REQUEST_MODIFIER:
        HidKbDev->SysReqOn = FALSE;
        break;

      //
      // AltGr release
      //
      case EFI_ALT_GR_MODIFIER:
        HidKbDev->AltGrOn = FALSE;
        break;

      default:
        break;
      }

      if ((HidKbDev->LeftShiftOn == FALSE) && (HidKbDev->RightShiftOn == FALSE))
        HidKbDev->LedKeyState[LED_KEY_SHIFT] = FALSE;

      if ((HidKbDev->LeftCtrlOn == FALSE) && (HidKbDev->RightCtrlOn == FALSE))
        HidKbDev->CtrlOn = FALSE;

      if ((HidKbDev->LeftAltOn == FALSE) && (HidKbDev->RightAltOn == FALSE))
        HidKbDev->AltOn = FALSE;

      continue;
    }

    //
    // Analyzes key pressing situation
    //
    switch (KeyDescriptor->Modifier) {

    //
    // Ctrl press
    //
    case EFI_LEFT_CONTROL_MODIFIER:
      HidKbDev->LeftCtrlOn = TRUE;
      HidKbDev->CtrlOn = TRUE;
      break;
    case EFI_RIGHT_CONTROL_MODIFIER:
      HidKbDev->RightCtrlOn = TRUE;
      HidKbDev->CtrlOn = TRUE;
      break;

    //
    // Shift press
    //
    case EFI_LEFT_SHIFT_MODIFIER:
      HidKbDev->LeftShiftOn = TRUE;
      HidKbDev->LedKeyState[LED_KEY_SHIFT] = TRUE;
      break;
    case EFI_RIGHT_SHIFT_MODIFIER:
      HidKbDev->RightShiftOn = TRUE;
      HidKbDev->LedKeyState[LED_KEY_SHIFT] = TRUE;
      break;

    //
    // Alt press
    //
    case EFI_LEFT_ALT_MODIFIER:
      HidKbDev->LeftAltOn = TRUE;
      HidKbDev->AltOn = TRUE;
      break;
    case EFI_RIGHT_ALT_MODIFIER:
      HidKbDev->RightAltOn = TRUE;
      HidKbDev->AltOn = TRUE;
      break;

    //
    // Left Logo press
    //
    case EFI_LEFT_LOGO_MODIFIER:
      HidKbDev->LeftLogoOn = TRUE;
      break;

    //
    // Right Logo press
    //
    case EFI_RIGHT_LOGO_MODIFIER:
      HidKbDev->RightLogoOn = TRUE;
      break;

    //
    // Menu key press
    //
    case EFI_MENU_MODIFIER:
      HidKbDev->MenuKeyOn = TRUE;
      break;

    //
    // SysReq press
    //
    case EFI_PRINT_MODIFIER:
    case EFI_SYS_REQUEST_MODIFIER:
      HidKbDev->SysReqOn = TRUE;
      break;

    //
    // AltGr press
    //
    case EFI_ALT_GR_MODIFIER:
      HidKbDev->AltGrOn = TRUE;
      break;

    case EFI_NUM_LOCK_MODIFIER:
      //
      // Toggle NumLock
      //
      HidKbDev->LedKeyState[LED_KEY_NUMLOCK] = (BOOLEAN) (!(HidKbDev->LedKeyState[LED_KEY_NUMLOCK]));
      HidKbDev->LedKeyState[EFI_KEY_NUM_LOCK] = (HidKbDev->LedKeyState[LED_KEY_NUMLOCK] == TRUE ) ? TRUE : FALSE;
      SetKeyLED (HidKbDev);
      break;

    case EFI_CAPS_LOCK_MODIFIER:
      //
      // Toggle CapsLock
      //
      HidKbDev->LedKeyState[LED_KEY_CAPSLOCK] = (BOOLEAN) (!(HidKbDev->LedKeyState[LED_KEY_CAPSLOCK]));
      HidKbDev->LedKeyState[EFI_KEY_CAPS_LOCK] = (HidKbDev->LedKeyState[LED_KEY_CAPSLOCK] == TRUE ) ? TRUE : FALSE;
      SetKeyLED (HidKbDev);
      break;

    case EFI_SCROLL_LOCK_MODIFIER:
      //
      // Toggle ScrollLock
      //
      HidKbDev->LedKeyState[LED_KEY_SCROLL] = (BOOLEAN) (!(HidKbDev->LedKeyState[LED_KEY_SCROLL]));
      HidKbDev->LedKeyState[EFI_KEY_SCROLL_LOCK] = (HidKbDev->LedKeyState[LED_KEY_SCROLL] == TRUE ) ? TRUE : FALSE;
      SetKeyLED (HidKbDev);
      break;

    default:
      break;
    }

    //
    // When encountering Ctrl + Alt + Del, then warm reset.
    //
    if (KeyDescriptor->Modifier == EFI_DELETE_MODIFIER) {
      if ((HidKbDev->CtrlOn) && (HidKbDev->AltOn)) {
        gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
      }
    }

    *KeyCode = HidKey.KeyCode;
    return EFI_SUCCESS;
  }

  return EFI_NOT_READY;
}


/**
  Converts HID Keycode ranging from 0x4 to 0x65 to EFI_INPUT_KEY.

  @param  HidKbDev               The HID_KB_DEV instance.
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
  IN  HID_KB_DEV                *HidKbDev,
  IN  UINT8                     KeyCode,
  OUT EFI_KEY_DATA              *KeyData
  )
{
  EFI_KEY_DESCRIPTOR            *KeyDescriptor;
  LIST_ENTRY                    *Link;
  LIST_ENTRY                    *NotifyList;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY *CurrentNotify;

  //
  // KeyCode must in the range of  [0x4, 0x65] or [0xe0, 0xe7].
  //
  KeyDescriptor = GetKeyDescriptor (HidKbDev, KeyCode);
  ASSERT (KeyDescriptor != NULL);

  if (KeyDescriptor->Modifier == EFI_NS_KEY_MODIFIER) {
    //
    // If this is a dead key with EFI_NS_KEY_MODIFIER, then record it and return.
    //
    HidKbDev->CurrentNsKey = FindHidNsKey (HidKbDev, KeyDescriptor);
    return EFI_NOT_READY;
  }

  if (HidKbDev->CurrentNsKey != NULL) {
    //
    // If this keystroke follows a non-spacing key, then find the descriptor for corresponding
    // physical key.
    //
    KeyDescriptor = FindPhysicalKey (HidKbDev->CurrentNsKey, KeyDescriptor);
    HidKbDev->CurrentNsKey = NULL;
  }

  //
  // Make sure modifier of Key Descriptor is in the valid range according to UEFI spec.
  //
  if (KeyDescriptor->Modifier >= (sizeof (ModifierValueToEfiScanCodeConvertionTable) / sizeof (UINT8))) {
    return EFI_DEVICE_ERROR;
  }

  KeyData->Key.ScanCode    = ModifierValueToEfiScanCodeConvertionTable[KeyDescriptor->Modifier];
  KeyData->Key.UnicodeChar = KeyDescriptor->Unicode;

  if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_STANDARD_SHIFT)!= 0) {
    if (HidKbDev->LedKeyState[LED_KEY_SHIFT]) {
      KeyData->Key.UnicodeChar = KeyDescriptor->ShiftedUnicode;

      //
      // Need not return associated shift state if a class of printable characters that
      // are normally adjusted by shift modifiers. e.g. Shift Key + 'f' key = 'F'
      //
      if ((KeyDescriptor->Unicode != CHAR_NULL) && (KeyDescriptor->ShiftedUnicode != CHAR_NULL) &&
          (KeyDescriptor->Unicode != KeyDescriptor->ShiftedUnicode)) {
        HidKbDev->LeftShiftOn = FALSE;
        HidKbDev->RightShiftOn = FALSE;
      }

      if (HidKbDev->AltGrOn) {
        KeyData->Key.UnicodeChar = KeyDescriptor->ShiftedAltGrUnicode;
      }
    } else {
      //
      // Shift off
      //
      KeyData->Key.UnicodeChar = KeyDescriptor->Unicode;

      if (HidKbDev->AltGrOn) {
        KeyData->Key.UnicodeChar = KeyDescriptor->AltGrUnicode;
      }
    }
  }

  if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_CAPS_LOCK) != 0) {
    if (HidKbDev->LedKeyState[LED_KEY_CAPSLOCK]) {
      if (KeyData->Key.UnicodeChar == KeyDescriptor->Unicode) {
        KeyData->Key.UnicodeChar = KeyDescriptor->ShiftedUnicode;
      } else if (KeyData->Key.UnicodeChar == KeyDescriptor->ShiftedUnicode) {
        KeyData->Key.UnicodeChar = KeyDescriptor->Unicode;
      }
    }
  }

  if ((KeyDescriptor->AffectedAttribute & EFI_AFFECTED_BY_NUM_LOCK) != 0) {
    //
    // For key affected by NumLock, if NumLock is on and Shift is not pressed, then it means
    // normal key, instead of original control key. So the ScanCode should be cleaned.
    // Otherwise, it means control key, so preserve the EFI Scan Code and clear the unicode keycode.
    //
    if ((HidKbDev->LedKeyState[LED_KEY_NUMLOCK]) && (!(HidKbDev->LedKeyState[LED_KEY_SHIFT]))) {
      KeyData->Key.ScanCode = SCAN_NULL;
    } else {
      KeyData->Key.UnicodeChar = CHAR_NULL;
    }
  }

  //
  // Translate Unicode 0x1B (ESC) to EFI Scan Code
  //
  if (KeyData->Key.UnicodeChar == 0x1B && KeyData->Key.ScanCode == SCAN_NULL) {
    KeyData->Key.ScanCode = SCAN_ESC;
    KeyData->Key.UnicodeChar = CHAR_NULL;
  }

  //
  // Not valid for key without both unicode key code and EFI Scan Code.
  //
  if (KeyData->Key.UnicodeChar == 0 && KeyData->Key.ScanCode == SCAN_NULL) {
    if (!HidKbDev->IsSupportPartialKey) {
    return EFI_NOT_READY;
    }
  }

  //
  // Save Shift/Toggle state
  //
  KeyData->KeyState.KeyShiftState  = EFI_SHIFT_STATE_VALID;
  KeyData->KeyState.KeyToggleState = EFI_TOGGLE_STATE_VALID;

  if (HidKbDev->LeftCtrlOn) {
    KeyData->KeyState.KeyShiftState |= EFI_LEFT_CONTROL_PRESSED;
  }
  if (HidKbDev->RightCtrlOn) {
    KeyData->KeyState.KeyShiftState |= EFI_RIGHT_CONTROL_PRESSED;
  }
  if (HidKbDev->LeftAltOn) {
    KeyData->KeyState.KeyShiftState |= EFI_LEFT_ALT_PRESSED;
  }
  if (HidKbDev->RightAltOn) {
    KeyData->KeyState.KeyShiftState |= EFI_RIGHT_ALT_PRESSED;
  }
  if (HidKbDev->LeftShiftOn) {
    KeyData->KeyState.KeyShiftState |= EFI_LEFT_SHIFT_PRESSED;
  }
  if (HidKbDev->RightShiftOn) {
    KeyData->KeyState.KeyShiftState |= EFI_RIGHT_SHIFT_PRESSED;
  }
  if (HidKbDev->LeftLogoOn) {
    KeyData->KeyState.KeyShiftState |= EFI_LEFT_LOGO_PRESSED;
  }
  if (HidKbDev->RightLogoOn) {
    KeyData->KeyState.KeyShiftState |= EFI_RIGHT_LOGO_PRESSED;
  }
  if (HidKbDev->MenuKeyOn) {
    KeyData->KeyState.KeyShiftState |= EFI_MENU_KEY_PRESSED;
  }
  if (HidKbDev->SysReqOn) {
    KeyData->KeyState.KeyShiftState |= EFI_SYS_REQ_PRESSED;
  }

  if (HidKbDev->LedKeyState[LED_KEY_SCROLL]) {
    KeyData->KeyState.KeyToggleState |= EFI_SCROLL_LOCK_ACTIVE;
  }
  if (HidKbDev->LedKeyState[LED_KEY_NUMLOCK]) {
    KeyData->KeyState.KeyToggleState |= EFI_NUM_LOCK_ACTIVE;
  }
  if (HidKbDev->LedKeyState[LED_KEY_CAPSLOCK]) {
    KeyData->KeyState.KeyToggleState |= EFI_CAPS_LOCK_ACTIVE;
  }
  if (HidKbDev->IsSupportPartialKey) {
    KeyData->KeyState.KeyToggleState |= EFI_KEY_STATE_EXPOSED;
  }
  //
  // Invoke notification functions if the key is registered.
  //
  NotifyList = &HidKbDev->NotifyList;
  for (Link = GetFirstNode (NotifyList); !IsNull (NotifyList, Link); Link = GetNextNode (NotifyList, Link)) {
    CurrentNotify = CR (Link, KEYBOARD_CONSOLE_IN_EX_NOTIFY, NotifyEntry, HID_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE);
    if (IsKeyRegistered (&CurrentNotify->KeyData, KeyData)) {
      CurrentNotify->KeyNotificationFn (KeyData);
    }
  }

  return EFI_SUCCESS;
}


/**
  Create the queue.

  @param  Queue     Points to the queue.
  @param  ItemSize  Size of the single item.

**/
VOID
InitQueue (
  IN OUT  HID_SIMPLE_QUEUE    *Queue,
  IN      UINTN              ItemSize
  )
{
  UINTN                      Index;

  Queue->ItemSize  = ItemSize;
  Queue->Head      = 0;
  Queue->Tail      = 0;

  if (Queue->Buffer[0] != NULL) {
    FreePool (Queue->Buffer[0]);
  }

  Queue->Buffer[0] = AllocatePool (sizeof (Queue->Buffer) / sizeof (Queue->Buffer[0]) * ItemSize);
  ASSERT (Queue->Buffer[0] != NULL);

  for (Index = 1; Index < sizeof (Queue->Buffer) / sizeof (Queue->Buffer[0]); Index++) {
    Queue->Buffer[Index] = ((UINT8 *) Queue->Buffer[Index - 1]) + ItemSize;
  }
}

/**
  Destroy the queue

  @param Queue    Points to the queue.
**/
VOID
DestroyQueue (
  IN OUT HID_SIMPLE_QUEUE   *Queue
  )
{
  FreePool (Queue->Buffer[0]);
}


/**
  Check whether the queue is empty.

  @param  Queue     Points to the queue.

  @retval TRUE      Queue is empty.
  @retval FALSE     Queue is not empty.

**/
BOOLEAN
IsQueueEmpty (
  IN  HID_SIMPLE_QUEUE   *Queue
  )
{
  //
  // Meet FIFO empty condition
  //
  return (BOOLEAN) (Queue->Head == Queue->Tail);
}


/**
  Check whether the queue is full.

  @param  Queue     Points to the queue.

  @retval TRUE      Queue is full.
  @retval FALSE     Queue is not full.

**/
BOOLEAN
IsQueueFull (
  IN  HID_SIMPLE_QUEUE   *Queue
  )
{
  return (BOOLEAN) (((Queue->Tail + 1) % (MAX_KEY_ALLOWED + 1)) == Queue->Head);
}


/**
  Enqueue the item to the queue.

  @param  Queue     Points to the queue.
  @param  Item      Points to the item to be enqueued.
  @param  ItemSize  Size of the item.
**/
VOID
Enqueue (
  IN OUT  HID_SIMPLE_QUEUE  *Queue,
  IN      VOID             *Item,
  IN      UINTN            ItemSize
  )
{
  ASSERT (ItemSize == Queue->ItemSize);
  //
  // If keyboard buffer is full, throw the
  // first key out of the keyboard buffer.
  //
  if (IsQueueFull (Queue)) {
    Queue->Head = (Queue->Head + 1) % (MAX_KEY_ALLOWED + 1);
  }

  CopyMem (Queue->Buffer[Queue->Tail], Item, ItemSize);

  //
  // Adjust the tail pointer of the FIFO keyboard buffer.
  //
  Queue->Tail = (Queue->Tail + 1) % (MAX_KEY_ALLOWED + 1);
}


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
  IN OUT  HID_SIMPLE_QUEUE  *Queue,
     OUT  VOID             *Item,
  IN      UINTN            ItemSize
  )
{
  ASSERT (Queue->ItemSize == ItemSize);

  if (IsQueueEmpty (Queue)) {
    return EFI_DEVICE_ERROR;
  }

  CopyMem (Item, Queue->Buffer[Queue->Head], ItemSize);

  //
  // Adjust the head pointer of the FIFO keyboard buffer.
  //
  Queue->Head = (Queue->Head + 1) % (MAX_KEY_ALLOWED + 1);

  return EFI_SUCCESS;
}


/**
  Sets HID keyboard LED state.

  @param  HidKbDev  The HID_KB_DEV instance.

**/
VOID
SetKeyLED (
  IN  HID_KB_DEV    *HidKbDev
  )
{
  UINT32         ReportItemSize;
  UINT8          *Data;
  UINT32         Index;
  UINT8          BitMask;
  UINT32         ByteIndex;
  UINT32         BitIndex;
  LIST_ENTRY     *Link;
  LIST_ENTRY     *Cur;
  HID_REPORT_FMT *ReportItem;

  HidKbDev->Hid->GetReportFormatList(HidKbDev->Hid, &Link);
  Cur = GetFirstNode (Link);

  ByteIndex = 0;
  BitIndex  = 0;

  // Find the total size of all output
  // reports corresponding to the LED
  if (HidKbDev->OutLedReportSize == 0){
    while (!IsNull (Link, Cur)) {
      ReportItem = ITEM_FROM_LINK(Cur);

      if (ReportItem->UsagePage == BT_HID_LED_USAGE_PAGE)
        HidKbDev->OutLedReportSize = HidKbDev->OutLedReportSize + (ReportItem->ReportCount * ReportItem->ReportSize);

      Cur = GetNextNode (Link, Cur);
    }

    Cur = GetFirstNode (Link);
  }

  Data = (UINT8 *)AllocateZeroPool(HidKbDev->OutLedReportSize/8);
  ASSERT (Data != NULL);

  while (!IsNull (Link, Cur)) {
    ReportItem = ITEM_FROM_LINK(Cur);

    if (ReportItem->UsagePage == BT_HID_LED_USAGE_PAGE) {
      // If it's of the constant type skip it!
      if (ReportItem->DatConst){
        ReportItemSize = ReportItem->ReportCount * ReportItem->ReportSize;
        ByteIndex += ReportItemSize / 8;
        BitIndex = BitIndex + ReportItemSize;

        if (BitIndex >= 7) {
          ByteIndex += 1;
          BitIndex = BitIndex % 7;
        }
      }

      for (Index = ReportItem->UsageMin; Index <= ReportItem->UsageMax; Index++) {
        if (HidKbDev->LedKeyState[Index] == TRUE) {
          BitMask = Data[ByteIndex];
          BitMask = BitMask | (1 << BitIndex);
          Data[ByteIndex] = BitMask;
        }

        BitIndex += ReportItem->ReportSize;

        if (BitIndex == 7){
          ByteIndex ++;
          BitIndex = 0;
        }
      }
    }

    Cur = GetNextNode (Link, Cur);
  }

  //
  // Call Set_Report Request to lighten the LED.
  //
  HidSetReportRequest (
    HidKbDev->Hid,
    0,
    BluetoothHidOutputReport,
    (UINT16)(HidKbDev->OutLedReportSize/8),
    Data
    );

  FreePool(Data);
}


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
  )
{
  HID_KB_DEV  *HidKbDev;
  HID_KEY     HidKey;

  HidKbDev = (HID_KB_DEV *) Context;

  //
  // Do nothing when there is no repeat key.
  //
  if (HidKbDev->RepeatKey != 0) {
    //
    // Inserts the repeat key into keyboard buffer,
    //
    HidKey.KeyCode = HidKbDev->RepeatKey;
    HidKey.Down    = TRUE;
    Enqueue (&HidKbDev->HidKeyQueue, &HidKey, sizeof (HidKey));

    //
    // Set repeat rate for next repeat key generation.
    //
    gBS->SetTimer (
           HidKbDev->RepeatTimer,
           TimerRelative,
           HIDKBD_REPEAT_RATE
           );
  }
}
