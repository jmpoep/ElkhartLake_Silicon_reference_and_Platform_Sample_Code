/** @file
  Implements HECI Runtime Services

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/HeciRuntimeLib.h>
#include <Protocol/HeciProtocol.h>

STATIC EFI_EVENT            mVirtualAddressChangeEvent;

HECI_PROTOCOL mHeciRuntimeProtocol = {
  HeciSendwAck,
  HeciReceive,
  HeciSend,
  ResetHeciInterface,
  HeciInitialize,
  MeResetWait,
  HeciReInitialize,
  HeciGetMeStatus,
  HeciGetMeMode
};

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
HeciAddressChangeEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.SendwAck);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.ReadMsg);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.SendMsg);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.ResetHeci);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.InitHeci);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.MeResetWait);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.ReInitHeci);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.GetMeStatus);
  EfiConvertPointer (0x0, (VOID **) &mHeciRuntimeProtocol.GetMeMode);
}

/**
  Install a HECI Protocol Interfaces for OS Runtime access

  @param[in]  ImageHandle  The image handle.
  @param[in]  SystemTable  The system table.

  @retval     EFI_SUCCESS  The protocol was installed successfully.
  @retval     Others       Protocol could not be installed.
**/
EFI_STATUS
EFIAPI
HeciRuntimeDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  Handle;

  DEBUG ((EFI_D_INFO, "HeciRuntimeDxeInitialize() Entry\n"));

  Status = gBS->CreateEventEx(
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciAddressChangeEvent,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mVirtualAddressChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Handle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gHeciRuntimeProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mHeciRuntimeProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}