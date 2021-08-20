/** @file
  Platform-specific Wdt code.  Offers more convenient and foolproof API for
  manipulating WDT than low-level WDT driver which is part of Reference Code.
  WdtApp is too platform-specific to be included in reference code.  However,
  it is expected that each client will need to write something similar on his own.
  This implementation uses EFI timers to kick WDT periodically.  There are other
  possibilities.  For example, a more robust way would be to kick WDT at certain
  milestones of BIOS code execution.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>

#include <WdtAppVariable.h>
#include <Protocol/Wdt.h>


VOID
EFIAPI
FeedWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
);


EFI_STATUS
EFIAPI
RequestWdtNow (
  VOID
);


EFI_EVENT  mFeedEvent;


/**

  @param[in] ImageHandle
  @param[in] SystemTable

  @retval    EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
WdtAppDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS           Status;
  WDT_PROTOCOL         *WdtProtocol;
  UINTN                VariableSize;
  UINT32               Attributes;
  WDT_PERSISTENT_DATA  WdtPersistentData;
  UINT8                WdtRequiredByOs;
  UINT8                WdtRunning;

  DEBUG ((DEBUG_INFO, "(WdtApp) Entry Point to WdtAppDxe\n"));

  Status = gBS->LocateProtocol(&gWdtProtocolGuid, NULL, (VOID **) &WdtProtocol);
  if ( EFI_ERROR(Status) ) {
    DEBUG ((DEBUG_ERROR, "(WdtApp) Failed to locate Wdt protocol, Status = %r\n",Status));
    return EFI_SUCCESS;
  }

  VariableSize  = sizeof (WDT_PERSISTENT_DATA);

  Status = gRT->GetVariable (
                  L"WdtPersistentData",
                  &gWdtPersistentDataGuid,
                  &Attributes,
                  &VariableSize,
                  &WdtPersistentData
                  );
  if (EFI_ERROR (Status)) {
    //
    // If variable doesn't exist, it is treated as if it was equal to 0
    //
    WdtPersistentData.Enable = 0;
  }

  WdtRequiredByOs = WdtProtocol->IsWdtRequired();
  WdtRunning      = WdtProtocol->IsWdtEnabled();

  if (WdtRequiredByOs == TRUE || WdtRunning == TRUE || WdtPersistentData.Enable == 1) {
    RequestWdtNow();
  }

  WdtPersistentData.Enable = 0;
  gRT->SetVariable(
         L"WdtPersistentData",
         &gWdtPersistentDataGuid,
         EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
         sizeof (WDT_PERSISTENT_DATA),
         &WdtPersistentData
         );


  return EFI_SUCCESS;
}


/**
  Allows protocol's clients to request that WDT be turned on and periodically kicked.
  If called for the 1st time, starts WDT and installs timer-based event that will kick WDT.
  If called again, does nothing - the event for kicking Wdt is already there.

  @retval     EFI_SUCCESS
  @retval     other
**/
EFI_STATUS
EFIAPI
RequestWdtNow (
  VOID
  )
{
  EFI_STATUS    Status;
  WDT_PROTOCOL* WdtProtocol;
  static UINT8  AlreadyTurnedOn = 0;

  DEBUG ((DEBUG_INFO, "(WdtApp) Wdt turned on\n"));
  if (AlreadyTurnedOn != 0) {
    return EFI_SUCCESS;
  }
  AlreadyTurnedOn = 1;

  Status = gBS->LocateProtocol(&gWdtProtocolGuid, NULL, (VOID **) &WdtProtocol);
  ASSERT_EFI_ERROR(Status);

  Status = WdtProtocol->ReloadAndStart(PcdGet8 (PcdWdtTimeoutValue));
  ASSERT_EFI_ERROR(Status);

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  FeedWatchdog,
                  NULL,
                  &mFeedEvent
                  );
  ASSERT_EFI_ERROR (Status);
  Status = gBS->SetTimer (
                  mFeedEvent,
                  TimerPeriodic,
                  PcdGet32 (PcdWdtReloadTimer)
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
};




/**
  Prevents WDT timeout by restarting it.
  If WDT protocol can't be located - which means it was uninstalled - this function
  unregisters the event that triggers it periodically.
  This function executes with highest prority on timer interrupt.  Interrupt may
  fire just between some other lower-priority module disabling WDT and resetting
  platform.  To prevent such flow, this function checks if WDT is currently enabled,
  and skips reloading it when it is disabled.

  @param[in] Event
  @param[in] Context

  @retval    EFI_SUCCESS
  @retval    other
**/
VOID
EFIAPI
FeedWatchdog (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  WDT_PROTOCOL* WdtProtocol;
  UINT8         Enabled;

  Status = gBS->LocateProtocol(&gWdtProtocolGuid, NULL, (VOID **) &WdtProtocol);
  if ( EFI_ERROR(Status) ) {
    DEBUG ((DEBUG_ERROR, "(WdtApp) Wdt protocol was uninstalled. Disabling FeedWatchdog.\n",Status));
    Status = gBS->SetTimer (mFeedEvent, TimerCancel, 0);
    ASSERT_EFI_ERROR(Status);
    Status = gBS->CloseEvent (mFeedEvent);
    ASSERT_EFI_ERROR(Status);
    return;
  }
  Enabled = WdtProtocol->IsWdtEnabled();
  ASSERT_EFI_ERROR(Status);
  if (Enabled == TRUE) {
    Status = WdtProtocol->ReloadAndStart(PcdGet8 (PcdWdtTimeoutValue));
  }
}
