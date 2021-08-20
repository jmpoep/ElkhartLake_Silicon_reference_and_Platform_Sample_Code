/**@file
  HID-I2C platform support library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

@par Specification
**/


#include <Base.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <Library/GpioLib.h>
#include <SetupVariable.h>

/**
  Initializes selected device

  @param[in]  Handle               Handle of the device

  @retval TRUE      interrupt is active
  @retval FALSE     no interrupt

**/
EFI_STATUS
EFIAPI
HidI2cInitialize (
  IN EFI_HANDLE Handle
  )
{
  //
  // This is the place to add power management or reset sequence if needed
  //
  return EFI_SUCCESS;
}

/**
  Checks if device indicated by Handle has active interrupt

  @param[in]  Handle               Handle of the device whose interrupt is being checked

  @retval TRUE      interrupt is active
  @retval FALSE     no interrupt

**/
BOOLEAN
EFIAPI
HidI2cCheckInterrupt (
  IN EFI_HANDLE Handle
  )
{
  UINT32          Data32;
  static GPIO_PAD sInterruptPad = 0;

  if (sInterruptPad == 0) {
    sInterruptPad = (GPIO_PAD) PcdGet32 (PcdHidI2cIntPad);
  }

  //
  // Our platforms support only a single HID device, so no need to determine
  // device based on Handle parameter
  //

  GpioGetInputValue (sInterruptPad, &Data32);
  if (Data32 != 0) {
    return FALSE;
  }
  return TRUE;
}


/**
  Returns address of HID Descriptor Register of selected device
  device is identified by Handle. This implementation ignores handle,
  because it's for platforms that have only a single HID device

  @param[in]  Handle               Handle of the device whose HID address is needed.

  @return                          HID descriptor register's address

**/
UINT16
EFIAPI
HidI2cGetHidRegisterAddress (
  IN EFI_HANDLE Handle
  )
{
  SETUP_DATA              SetupData;
  EFI_STATUS              Status;
  UINTN                   Size;

  Size = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (L"Setup", &gSetupVariableGuid, NULL, &Size, &SetupData);
  if (EFI_ERROR(Status)) {
    return 0xFFFF;
  }
  switch(SetupData.PchI2cTouchPanelType) {
    case 1: return 0;
    case 2: return 0;
    case 3: return 1;
    case 4: return 1;
    case 5: return 1;
    case 6: return SetupData.PchI2cTouchPanelHidAddress;
    default: return 0xFFFF;
  }
}


