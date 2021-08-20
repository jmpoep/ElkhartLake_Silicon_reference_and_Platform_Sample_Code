/** @file

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

#ifndef _AMT_SUPPORT_H_
#define _AMT_SUPPORT_H_

#include <Protocol/SimpleTextInEx.h>
#include <Protocol/AmtWrapperProtocol.h>
#include <MeBiosPayloadData.h>
#include <Protocol/AmtPolicy.h>

VOID
AmtBdsBoot (
  VOID
  );

VOID
AmtUpdateConsoleVariable (
  VOID
  );

BOOLEAN
AmtEnterSetup (
  VOID
  );

/**
  AMT action when console is ready.
  Dynamically switch the output mode to 80x25 when SOL is enabled.
**/
VOID
AmtConsoleReady (
  VOID
  );

EFI_STATUS
AmtGetSetupPrompt (
  OUT     CHAR16    **String
  );

EFI_STATUS
AmtDetermineSetupHotKey (
  IN  EFI_KEY_DATA  *KeyData
  );

EFI_STATUS
AmtGetSupportedHotkeys (
  OUT  UINTN             *KeyCnt,
  OUT  EFI_KEY_DATA      **KeyData
  );

/**
  Register Amt Hotkey.
**/
VOID
RegisterAmtHotKey (
  VOID
  );

/**
  Unregister Ant Hotkey.

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.
**/
VOID
EFIAPI
UnregisterAmtHotKey (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  );

/**
  Check whether do full configuration enumeration for media asset table

  @param[in, out]   BootMode        A pointer to BootMode to be updated.

**/
VOID
AmtUpdateBootMode (
  IN OUT EFI_BOOT_MODE *BootMode
  );
#endif //_AMT_SUPPORT_H_
