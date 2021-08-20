/** @file

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
#include <Library/DebugLib.h>
#include <Protocol/SmmThunk.h>
#include <Library/DxeSmmInternalGraphicDeviceLib.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_THUNK_PROTOCOL              *mSmmThunk;

EFI_STATUS
InitializeInternalGraphicDeviceLib (
  VOID
  )
/*++

Routine Description:

  Initialize the IGD library

Arguments:

  None

Returns:

  EFI_SUCCESS     The function completed successfully

--*/
{
  DEBUG((DEBUG_ERROR, "Smm Thunk Protocol Locating failed!\n"));
  mSmmThunk = NULL;

  //
  // We don't really care if it failed at this time.
  //
  return EFI_SUCCESS;
}

VOID
GraphicsInt (
  IN EFI_IA32_REGISTER_SET   *Registers
  )
/*++

Routine Description:

  Call the internal graphics device real mode interrupt functions using the alternate int 10 entry point.

Arguments:

  Registers - Pointer to the structure containing
              information of all word registers.

Returns:

  None

--*/
{
  return;
}

VOID
GetCadl (
  IN OUT EFI_IA32_REGISTER_SET   *Registers
  )
/*++

Routine Description:

  Get the current attached device list from the internal graphics device.
  Function 5F64, BH = 2, Get display device detect.

Arguments:

  Registers   Updated with the results of the call or a defauld CADL

Returns:

  EFI_SUCCESS   The function completed successfully

--*/
{
  //
  // INT 10h, 5F64h, 2, Get Display Device Detect
  //
// Commenting out this call as there is a known issue with VBIOS
// This line should be uncommented as soon as the VBIOS which includes the
// fix for this bug is integrated into the BIOS.
/*
  Registers->X.AX = 0x5F64;
  Registers->H.BH = 2;
  Registers->H.BL = 0;
  GraphicsInt (Registers);

  //
  // If the function completes and returns that attach is not necessary
  //
  if ((Registers->X.AX == VBIOS_SUCCESS) && (Registers->H.BL & NOT_NEED_ATTACHED)) {
    return;
  }
*/
  //
  // Not supported/detected or needs to be attached so return default (static) solution
  //
  Registers->X.CX = DEVICE_DEFAULT_ALL_WORD;
  Registers->X.Flags.ZF = 0;
  return;
}

EFI_STATUS
GetNextState (
  IN OUT EFI_IA32_REGISTER_SET   *Registers
  )
/*++

Routine Description:

  Obtain the next valid state in a DID bit mask.

Arguments:

  Registers   BL  = Toggle list to use
              EDX = Display encoders present

Returns:

  EFI_SUCCESS   BX updated with the next state
  EFI_ABORTED   The function failed

--*/
{
  UINT16 AttachedDevice;

  AttachedDevice = Registers->X.DX;
  Registers->X.AX = 0x5F64;
  Registers->H.BH = 5;
  GraphicsInt (Registers);
  if (Registers->X.AX == VBIOS_SUCCESS) {

    //
    // Reduce the list for Pipe&Device to only the list of Devices of next combination
    //
    Registers->X.CX = Registers->H.CH | Registers->H.CL;
    //
    // The allowed next display must be within the scope of attached devices and return in BX
    //
    Registers->X.BX = AttachedDevice & (Registers->X.CX );

    Registers->X.Flags.CF = 0;
    return EFI_SUCCESS;
  } else {
    Registers->X.Flags.CF = 1;
    return EFI_ABORTED;
  }
}
