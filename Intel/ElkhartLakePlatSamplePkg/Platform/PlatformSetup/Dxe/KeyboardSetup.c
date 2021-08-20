/** @file
  Platform Initialization Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#include "PlatformSetup.h"
#include "KeyboardSetup.h"

EFI_STATUS
EFIAPI
Ps2InitHardware (
  IN  EFI_HANDLE  Handle
  )
/*++

Routine Description:

  Perform additional PS/2 hardware init.
  - Send a 0xF6 command to set the kbd in the default state. If the PS/2 keyboard driver takes a short-cut that skips the kbd
    reset command 0xff and the kbd enabling command 0xf4, then the command 0xf6 becomes mandatory to make KBD to work with Emerald Lake
    CRB EC FW. To avoid changes in the generic PS/2 keyboard driver, we send 0xF6 command in this function as a platform specific hook.
  - PS/2 Swap feature is not supported.

Arguments:

  Handle  - Handle for the protocol instance.

Returns:

  EFI_SUCCESS

--*/
{
  EFI_STATUS              Status;
  UINT8                   Buf8;
  UINT64                  Buf64;
  UINT32                  TimeOut;
  UINT32                  SumTimeOut;
  STATIC  BOOLEAN         Initialized;

  //
  // Only do once
  //
  if (!Initialized) {
    Initialized = TRUE;
  } else {
    return EFI_SUCCESS;
  }

  //
  // Based on assumption that output buffer clearing is done by Keyboard driver before calling this function,
  // we don't do output buffer clearing here to save boot time.
  // If the assumption does not hold true, we must clear output buffer here.
  //

  //
  // Wait for input buffer empty
  //
  Status = mPciRootBridgeIo->PollIo(mPciRootBridgeIo,
                                    EfiPciWidthUint8,
                                    KEYBOARD_8042_STATUS_REGISTER,
                                    KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA,
                                    0,
                                    KEYBOARD_TIMEOUT * 10,
                                    &Buf64
                                    );

  if (EFI_SUCCESS != Status) {
    goto Done;
  }

  //
  // Write the 0xF6 command
  //
  Buf8 = KEYBOARD_8048_COMMAND_SET_DEFAULT;
  Status = mPciRootBridgeIo->Io.Write (mPciRootBridgeIo,
                                     EfiPciWidthUint8,
                                     KEYBOARD_8042_DATA_REGISTER,
                                     1,
                                     &Buf8
                                     );

  //
  // Wait for ACK
  //
  TimeOut = 0;
  SumTimeOut = 0;
  while (1) {
    //
    // Read from data port
    //
    for (TimeOut = 0; TimeOut < KEYBOARD_TIMEOUT; TimeOut += 30) {
      Status = mPciRootBridgeIo->Io.Read(mPciRootBridgeIo,
                                EfiPciWidthUint8,
                                KEYBOARD_8042_STATUS_REGISTER,
                                1,
                                &Buf8
                                );
      ASSERT_EFI_ERROR (Status);
      if (Buf8 & KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA) {
        Status = mPciRootBridgeIo->Io.Read(mPciRootBridgeIo,
                                  EfiPciWidthUint8,
                                  KEYBOARD_8042_DATA_REGISTER,
                                  1,
                                  &Buf8
                                  );
        ASSERT_EFI_ERROR (Status);
        break;
      }
      gBS->Stall (30);
    }

    //
    // Is it an ACK?
    //
    if (TimeOut < KEYBOARD_TIMEOUT && Buf8 == KEYBOARD_8048_RETURN_8042_ACK) {
      Status = EFI_SUCCESS;
      break;
    }

    SumTimeOut += TimeOut;
    if (SumTimeOut >= KEYBOARD_WAITFORVALUE_TIMEOUT) {
      Status = EFI_DEVICE_ERROR;
      break;
    }
  }

Done:
  return  Status;
}
