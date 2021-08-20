/** @file
  This driver will set 8254 timer period to 1ms when Timer Arch Protocol is installed.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/Timer.h>

VOID
EFIAPI
SetTimerPeriodCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS               Status;
  UINT64                   TimerPeriod;
  EFI_TIMER_ARCH_PROTOCOL  *TimerProtocol;
  
  TimerProtocol = NULL;
  Status = gBS->LocateProtocol (&gEfiTimerArchProtocolGuid, NULL, (VOID **) &TimerProtocol);
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Set system timer period
  //
  TimerPeriod = PcdGet64 (PcdSystemTimerPeriod);
  if (PcdGetBool (PcdCsmEnable)) {
    TimerPeriod = 550000;
  }
  Status = TimerProtocol->SetTimerPeriod (
                    TimerProtocol,
                    TimerPeriod
                    );
  ASSERT_EFI_ERROR (Status);

  gBS->CloseEvent (Event);
  return;
}

/**
  Driver entry point to register Timer Arch Protocol callback.

  ImageHandle - Handle of image
  SystemTable - Pointer to System Table

  EFI_SUCCESS - Legacy Bios Platform protocol installed

**/
EFI_STATUS
EFIAPI
SetTimerPeriodEntrypoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  VOID                             *Registration;
  
  EfiCreateProtocolNotifyEvent (
    &gEfiTimerArchProtocolGuid,
    TPL_CALLBACK,
    SetTimerPeriodCallBack,
    NULL,
    &Registration
    );  

  return EFI_SUCCESS;
}
