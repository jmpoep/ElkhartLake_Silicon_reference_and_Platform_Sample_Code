/** @file
  Implementation file for Watchdog Timer functionality

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#include <PiDxe.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ConfigBlockLib.h>
#include <Protocol/Wdt.h>
#include <Library/WdtCommonLib.h>
#include <Register/PmcRegs.h>
#include <Library/UefiLib.h>
#include <Protocol/ResetNotification.h>

VOID
EFIAPI
WdtRunBeforeOsBoot (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );


VOID
EFIAPI
WdtPchResetCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  );

#define TIMEOUT_AFTER_POST_MULTIPLIER 16
#define MINIMUM_TIMEOUT_AT_S4_EXIT    600 ///< 10 minutes
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HANDLE                  mImageHandle;
GLOBAL_REMOVE_IF_UNREFERENCED WDT_PROTOCOL                mWdtProtocol = {
  WdtReloadAndStart,
  WdtCheckStatus,
  WdtDisable,
  WdtAllowKnownReset,
  IsWdtRequired,
  IsWdtEnabled
};

/**
  Hook to reset notification protocol to properly reset function with Wdt.

  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
VOID
EFIAPI
OnResetNotifyInstall (
  IN EFI_EVENT                      Event,
  IN VOID                           *Context
  )
{
  EFI_STATUS  Status;
  EFI_RESET_NOTIFICATION_PROTOCOL   *ResetNotify;

  Status = gBS->LocateProtocol (&gEfiResetNotificationProtocolGuid, NULL, (VOID **) &ResetNotify);
  if (!EFI_ERROR (Status)) {
    Status = ResetNotify->RegisterResetNotify (ResetNotify, WdtPchResetCallback);
    DEBUG ((DEBUG_INFO, "WdtPchResetCallback() installed\n"));
    if (Event) gBS->CloseEvent (Event);
  }
}


/**
  <b>WDT DXE Module Entry Point</b>\n
  - <b>Introduction</b>\n
    The WDT DXE provides a standard way for other modules to use the Watch dog timer Interface.
    This also registers a callback function to enable WDT if an OS application requested that
    just before booting to OS.

  - @pre
    - PCH PMIO Base configured
    - WDT driver needs to be executed before PCH Reset driver, so please update
      the FDF file accordingly to use APRIORI list to make sure that.

  - @result
    The WDT DXE module produces @link Include/Protocol/Wdt.h WDT_PROTOCOL @endlink.

  @param[in] ImageHandle          Image handle for this driver image
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_SUCCESS             WDT DXE driver initialization completed successfully
**/
EFI_STATUS
EFIAPI
WdtDxeEntryPoint (
  IN  EFI_HANDLE       ImageHandle,
  IN  EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                        Status;
  EFI_EVENT                         Event;
  VOID                              *Registration;

  DEBUG ((DEBUG_INFO, "(Wdt) Entry Point to WdtDxe\n"));

  mImageHandle = ImageHandle;

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_CALLBACK,
                  WdtRunBeforeOsBoot,
                  NULL,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);

  Status = EfiCreateEventLegacyBootEx (
             TPL_CALLBACK,
             WdtRunBeforeOsBoot,
             NULL,
             &Event
             );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "(Wdt) WDT event registration; Status = %r\n", Status));

  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gWdtProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mWdtProtocol
                  );
  ASSERT_EFI_ERROR (Status);


  EfiCreateProtocolNotifyEvent ( &gEfiResetNotificationProtocolGuid,
                                 TPL_CALLBACK,
                                 OnResetNotifyInstall,
                                 NULL,
                                 &Registration
                                 );
  return EFI_SUCCESS;
}

/**
  Turns on watchdog timer just before booting to OS, if an OS application requested that.
  Clears request status.
  Uninstalls Wdt protocol to prevent other modules from interfering with actions described above.

  @param[in] Event                useless here, but required in functions invoked by events
  @param[in] Context              useless here, but required in functions invoked by events

  @retval    None
**/
VOID
EFIAPI
WdtRunBeforeOsBoot (
  IN  EFI_EVENT Event,
  IN  VOID      *Context
  )
{
  UINT32                            ReloadValue;
  UINT32                            Readback;
  EFI_STATUS                        Status;
  EFI_RESET_NOTIFICATION_PROTOCOL   *ResetNotify;

  gBS->CloseEvent (Event);

  DEBUG ((DEBUG_INFO, "(Wdt) RunWdtBeforeOsBoot\n"));
  gBS->UninstallProtocolInterface (
         mImageHandle,
         &gWdtProtocolGuid,
         &mWdtProtocol
         );

  Status = gBS->LocateProtocol (&gEfiResetNotificationProtocolGuid, NULL, (VOID **) &ResetNotify);
  if (!EFI_ERROR (Status)) {
    Status = ResetNotify->UnregisterResetNotify (ResetNotify, WdtPchResetCallback);
    ASSERT_EFI_ERROR (Status);
  }



  Readback    = IoRead32 (WdtGetAddress ());
  ReloadValue = TIMEOUT_AFTER_POST_MULTIPLIER * ((Readback & B_ACPI_IO_OC_WDT_CTL_AFTER_POST) >> 16);

  if (ReloadValue != 0) {
    ///
    /// start WDT with TimeoutValueAfterPost and clear that value from register
    ///
    Readback &= ~(B_ACPI_IO_OC_WDT_CTL_AFTER_POST);
    IoWrite32 (WdtGetAddress (), Readback);
    WdtReloadAndStart (ReloadValue);
  } else {
    WdtDisable ();
  }

  return;

}

/**
  WDT call back function for Reset notification.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.
**/
VOID
EFIAPI
WdtPchResetCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  WdtAllowKnownReset ();
}
