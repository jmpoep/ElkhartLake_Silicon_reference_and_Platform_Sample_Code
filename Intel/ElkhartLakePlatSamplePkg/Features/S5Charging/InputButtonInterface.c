/** @file
  This file is meant to be configurable by the user.
  Initialize whatever buttons are needed for user input.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

/**
 * Note:
 * The button used as input event for displaying the icon depends on the mapping of the button.
 * The button could be mapped to the SOC. Therefore this abstraction is required to
 * be able to resolve this problem.
 */
#include "HardwareInterface.h"
#include "S5Charging.h"

BOOLEAN
InputButtonCheckPowerButtonStatus (
  VOID
  )
/*++

Routine Description:
   Check the status of power button

Arguments:
   None

Returns:
   TRUE:  Button released
   FALSE: Button pressed
--*/
{
  volatile UINT32  GpioValuePowerButton;

  GpioValuePowerButton   = 0;

  //
  // TODO: Implement check on Power button press from GPIO
  //
  return FALSE;
}

BOOLEAN
InputButtonCheckAltButtonStatus (
  VOID
  )
/*++

Routine Description:
   Check the status of alternate buttons

Arguments:
   None

Returns:
   TRUE:  Button released
   FALSE: Button pressed
--*/
{
  volatile UINT32  GpioValueUp;
  volatile UINT32  GpioValueDown;

  GpioValueUp   = 0;
  GpioValueDown = 0;

  //
  // TODO: Implement check on UP/DOWN button press from GPIO
  //
  return FALSE;
}


EFI_STATUS
InitializeInputButtonInterface (
  VOID
  )
/*++

Routine Description:
   Initialize the Button interface.

Arguments:
   None

Returns:

--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  mInputButtonInterface.CheckPowerButtonStatus = InputButtonCheckPowerButtonStatus;
  mInputButtonInterface.CheckInputButtonStatus = InputButtonCheckAltButtonStatus;

  return Status;
}
