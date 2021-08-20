/** @file
  KeyboardLedsLib implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/KeyboardLedsLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/KeyboardLeds.h>

KEYBOARD_LEDS   *KeyboardLedsProtocol = NULL;

RETURN_STATUS
EFIAPI
DxeKeyboardLedsConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  RETURN_STATUS   Status;
  EFI_HANDLE      Handle;

  Status = gBS->LocateProtocol (
                  &gKeyboardLedsProtocolGuid,
                  NULL,
                  (VOID **) &KeyboardLedsProtocol
                  );
  if (RETURN_ERROR (Status)) {
    KeyboardLedsProtocol = AllocatePool (sizeof (KEYBOARD_LEDS));
    if (KeyboardLedsProtocol == NULL) {
      DEBUG ((DEBUG_ERROR, "Fail to AllocatePool(), Status unknown\n"));
      return RETURN_OUT_OF_RESOURCES;
    }
    KeyboardLedsProtocol->NumLockOn = FALSE;
    KeyboardLedsProtocol->CapsOn = FALSE;
    KeyboardLedsProtocol->ScrollOn = FALSE;

    Handle = NULL;
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gKeyboardLedsProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    (VOID *) KeyboardLedsProtocol
                    );
    if (RETURN_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Fail to Install gKeyboardLedsProtocolGuid, Status = %r\n", Status));
      return RETURN_ABORTED;
    }
  }

  return RETURN_SUCCESS;
}

RETURN_STATUS
EFIAPI
GetKeyboardLedsStatus (
  IN OUT BOOLEAN    *NumLockOn,
  IN OUT BOOLEAN    *CapsOn,
  IN OUT BOOLEAN    *ScrollOn,
  OUT    BOOLEAN    *LedsStatusChanged
  )
{
  if (KeyboardLedsProtocol == NULL) {
    return RETURN_NOT_READY;
  }

  if (*NumLockOn != KeyboardLedsProtocol->NumLockOn ||
      *CapsOn != KeyboardLedsProtocol->CapsOn ||
      *ScrollOn != KeyboardLedsProtocol->ScrollOn) {
    *LedsStatusChanged = TRUE;
    *NumLockOn = KeyboardLedsProtocol->NumLockOn;
    *CapsOn = KeyboardLedsProtocol->CapsOn;
    *ScrollOn = KeyboardLedsProtocol->ScrollOn;
  } else {
    *LedsStatusChanged = FALSE;
  }

  return RETURN_SUCCESS;
}

RETURN_STATUS
EFIAPI
SetKeyboardLedsStatus (
  IN     BOOLEAN    NumLockOn,
  IN     BOOLEAN    CapsOn,
  IN     BOOLEAN    ScrollOn
  )
{
  if (KeyboardLedsProtocol == NULL) {
    return RETURN_NOT_READY;
  }

  KeyboardLedsProtocol->NumLockOn = NumLockOn;
  KeyboardLedsProtocol->CapsOn = CapsOn;
  KeyboardLedsProtocol->ScrollOn = ScrollOn;

  return RETURN_SUCCESS;
}