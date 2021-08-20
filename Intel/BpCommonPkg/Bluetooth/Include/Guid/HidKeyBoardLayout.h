//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  GUID and definitions for HID keyboard layout.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __HID_KEYBOARD_LAYOUT_GUID_H__
#define __HID_KEYBOARD_LAYOUT_GUID_H__

//
// GUID for HID keyboard HII package list.
//
#define HID_KEYBOARD_LAYOUT_PACKAGE_GUID \
  { \
    0x16388a95, 0x4d5c, 0x459a, { 0xa1, 0x62, 0x7e, 0x2, 0x13, 0xaa, 0xc9, 0x70 } \
  }

//
// GUID for HID keyboard layout
//
#define HID_KEYBOARD_LAYOUT_KEY_GUID \
  { \
    0xf07b4ce2, 0x2de1, 0x472d, { 0xa8, 0x52, 0x75, 0xd3, 0x3e, 0xd1, 0xd1, 0x5b } \
  }

extern EFI_GUID  gHidKeyboardLayoutPackageGuid;
extern EFI_GUID  gHidKeyboardLayoutKeyGuid;

#endif

