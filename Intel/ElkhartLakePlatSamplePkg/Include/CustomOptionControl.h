/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

#ifndef _CUSTOM_OPTION_CONTROL_H_
#define _CUSTOM_OPTION_CONTROL_H_

#include <SetupVariable.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/DebugLib.h>
//#include <PchPolicyCommon.h>

extern EFI_GUID   gMsftGlobalVariableGuid;


#pragma pack(1)
typedef struct _ATTEMPT_USB_FIRST_HOTKEY_INFO {
  UINT8 RevisonId;         // Structure Revision ID
  UINT8 HotkeyTriggered;   // Hot key status
} ATTEMPT_USB_FIRST_HOTKEY_INFO;
#pragma pack()

#pragma pack(1)
typedef struct _ATTEMPT_USB_FIRST_VARIABLE {
  UINT8 UsbBootPrior;
} ATTEMPT_USB_FIRST_VARIABLE;
#pragma pack()

//
// Volatile variable definition for Attempt USB first features
//
#pragma pack(1)
typedef struct _ATTEMPT_USB_FIRST_RUNTIME_VARIABLE {
  UINT8 RevisonId;        // Structure Revision ID
  UINT8 UsbFirstEnable;   // Attempt USB First is enabled or not
} ATTEMPT_USB_FIRST_RUNTIME_VARIABLE;
#pragma pack()

//
// Volatile variable definition for Enabling Flash Tools via UEFI Variable
//
#pragma pack(1)
typedef struct _ENABLE_FLASH_TOOLS{
  UINT32 EnableFlashTools;
} ENABLE_FLASH_TOOLS;
#pragma pack()

//
// Volatile variable definition for third party Default Enabling via UEFI Variable.
//
#pragma pack(1)
typedef struct _ENABLE_CUSTOM_DEFAULTS{
  UINT32  EnableCustomDefaults;
} ENABLE_CUSTOM_DEFAULTS;
#pragma pack()

#pragma pack(1)
typedef struct _ENABLE_CUSTOM_DEFAULTS_STATE{
  UINT8  CurrentState;
} ENABLE_CUSTOM_DEFAULTS_STATE;
#pragma pack()

extern EFI_GUID gAttemptUsbFirstHotkeyInfoHobGuid;
extern EFI_GUID gAttemptUsbFirstRuntimeVarInfoGuid;

#endif // _CUSTOM_OPTION_CONTROL_H_

