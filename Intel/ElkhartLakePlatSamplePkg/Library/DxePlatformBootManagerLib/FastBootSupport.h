/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#ifndef _FAST_BOOT_SUPPORT_H_
#define _FAST_BOOT_SUPPORT_H_

#include <Protocol/FastBootException.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/TcgPhysicalPresenceLib.h>
#include <Library/Tcg2PhysicalPresenceLib.h>

#define NORMAL_BOOT           0x00
#define QUIET_BOOT            0x01
#define SILENT_BOOT           0x02

#define KBC_INPBUF_VIA60_KBECHO         0xEE
#define KEYBOARD_8042_DATA_REGISTER     0x60
#define KEYBOARD_8042_STATUS_REGISTER   0x64

#define PS2_CONSOLE                        0x00
#define RECONNECT_LAST_GOOD_INPUT_CONSOLE  0x01
#define WINDOWS_CONSOLE                    0x02

#define PS2_KEYBOARD_TIMEOUT                65536   // 0.07s
#define PS2_KEYBOARD_WAITFORVALUE_TIMEOUT   1000000 // 1s
#define PS2_KEYBOARD_KBEN                   0xF4
#define PS2_KEYBOARD_CMDECHO_ACK            0xFA

VOID
FastBootUpdateConsoleVariable (
  VOID
  );

VOID
FastBootUpdateTimeoutVariable (
  VOID
  );

BOOLEAN
FastBootEnabled (
  VOID
  );

UINT8
GetDisplayBootMode (
  VOID
  );

BOOLEAN
IsPs2KeyboardConnected (
  VOID
  );
VOID
FastBootGenericVariablesInit (
  VOID
  );

BOOLEAN
IsExceptionType2Detected (
  VOID
  );

EFI_STATUS
RaiseFastBootException (
  FAST_BOOT_EXCEPTION_TYPE      ExceptionType,
  FAST_BOOT_EXCEPTION_CATEGORY  ExceptionCategory
  );

EFI_STATUS
FastBootEnumConInDevice (
  VOID
  );

VOID
FastBootHookConOut (
  VOID
  );

VOID
FastBootRestoreConOut (
  VOID
  );

VOID
FastBootUpdateBootMode (
  EFI_BOOT_MODE *BootMode
  );

VOID
FastBootBootOptionPatch (
  EFI_BOOT_MODE                 BootMode
  );

#endif //_FAST_BOOT_SUPPORT_H_
