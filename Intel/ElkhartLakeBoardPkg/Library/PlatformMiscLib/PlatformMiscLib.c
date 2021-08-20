/** @file

  Instance of Platform Misc Library for Platform Misc Programming and APIs.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

//
// The package level header files this module uses
//
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/GpioLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformMiscLib.h>
#include <Library/DebugLib.h>

/**
  Get the Volume Up Button State that whether it is pressed or not

  @retval  True  if Volume Up Button is pressed
           False if Volume Up Button is not pressed

**/
BOOLEAN
GetVolumeUpButtonState (
  VOID
  )
{
  UINT32      GpioVolUpGpeSts = 0;
  if (PcdGet32 (PcdVolumeUpButtonInterrupt) != 0){
    GpioGetGpiIntSts (PcdGet32 (PcdVolumeUpButtonInterrupt), &GpioVolUpGpeSts);
      if ((GpioVolUpGpeSts & BIT0) == BIT0) {
      GpioClearGpiSts (PcdGet32 (PcdVolumeUpButtonInterrupt));
      return TRUE;
    } else {
      return FALSE;
    }
  }
  return FALSE;
}

/**
  Get the Volume Down Button State that whether it is pressed or not

  @retval  True  if Volume Down Button is pressed
           False if Volume Down Button is not pressed

**/
BOOLEAN
GetVolumeDownButtonState (
  VOID
  )
{
  UINT32      GpioVolDownGpeSts = 0;
  if (PcdGet32 (PcdVolumeDownButtonInterrupt) != 0) {
    GpioGetGpiIntSts (PcdGet32 (PcdVolumeDownButtonInterrupt), &GpioVolDownGpeSts);
    if ((GpioVolDownGpeSts & BIT0) == BIT0) {
      GpioClearGpiSts (PcdGet32 (PcdVolumeDownButtonInterrupt));
      return TRUE;
    } else {
      return FALSE;
    }
  }
  return FALSE;
}