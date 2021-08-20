/** @file
  UEFI 2.2 User Manager Protocol definition.

  This protocol manages user profiles.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _VIRTUAL_KEYBOARD_PROTOCOL_H_
#define _VIRTUAL_KEYBOARD_PROTOCOL_H_

#include <Protocol/VirtualKeyboardLayout.h>

typedef struct  _VIRTUAL_KEYBOARD_PROTOCOL VIRTUAL_KEYBOARD_PROTOCOL;
typedef struct  _VIRTUAL_KEYBOARD_DISPLAY_PROTOCOL VIRTUAL_KEYBOARD_DISPLAY_PROTOCOL;

///
/// Provide virtual keyboard layout data
///
struct _VIRTUAL_KEYBOARD_PROTOCOL {
  ///
  /// The count of VIRTUAL_KEYBOARD_LAYOUT in VirtualKeyboardLayout buffer
  ///
  UINTN                     VirtualKeyboardCount;
  VIRTUAL_KEYBOARD_LAYOUT   *VirtualKeyboardLayout;
};

struct _VIRTUAL_KEYBOARD_DISPLAY_PROTOCOL {
  ///
  /// The count of VIRTUAL_KEYBOARD_LAYOUT in VirtualKeyboardLayout buffer
  ///
  UINTN                          VirtualKeyboardCount;
  VIRTUAL_KEYBOARD_LAYOUT_DATA   *VirtualKeyboardLayout;
};

#endif // _VIRTUAL_KEYBOARD_PROTOCOL_H_
