/** @file
  The implementation about Me ReadyToBootEvent for FSP support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DxeMeLib.h>
#include <Library/HeciInitLib.h>
#include "MeInit.h"

EFI_EVENT mExitBootServicesEvent     = NULL;

/**
  The notification registered as a callback to perform Me event prior to boot

  @param[in] Event            The event that triggered this notification function
  @param[in] Context          Pointer to the notification functions context
**/
VOID
EFIAPI
MeReadyToBootEventDxeFsp (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));
  MeReadyToBoot ();

  gBS->CloseEvent (Event);
}

/**
  The notification registered as a callback to perform Me ExitBootServices event prior to boot.

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.
**/
VOID
EFIAPI
MeEndOfFirmwareEventDxeFsp (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  UINT32 HeciBars[PCI_MAX_BAR];
  UINT8  MeDevFunction;

  ///
  /// Don't set D0I3 if disabled by policy
  ///
  if (MeHeciD0I3Enabled () == FALSE) {
    DEBUG ((DEBUG_INFO, "MeEndOfFirmwareEventFsp - SKIP setting D0I3 bits for HECI devices on boot time\n"));
    return;
  }

  DEBUG ((DEBUG_INFO, "MeEndOfFirmwareEventFsp - setting D0I3 bits for HECI devices on boot time\n"));

  //
  // 1. Save MMIO BAR addresses for all HECI devices.
  // 2. Set to default (32-bit) BAR addresses for all HECI devices.
  // 3. Set D0i3 bit
  // 4. Restore MMIO BAR addresses for all HECI devices.
  //
  for (MeDevFunction = HECI1; MeDevFunction <= HECI4; MeDevFunction++) {
    if (!IsHeciDeviceFunction (MeDevFunction)) {
      continue;
    }
    MeSaveBars (MeDevFunction, HeciBars);
    MeDeviceInit (MeDevFunction, PcdGet32 (PcdSiliconInitTempMemBaseAddr), 0);
    SetD0I3Bit (MeDevFunction);
    MeRestoreBars (MeDevFunction, HeciBars);
  }

  return;
}

/**
  FSP HeciInit Module Entry Point for signal ReadyToBoot FSP event

  @param[in] ImageHandle          Handle for the image of this driver
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
MeInitEntryPointDxeFsp (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_EVENT     Event;
  EFI_HANDLE    EopInFspHandle;

  DEBUG ((DEBUG_INFO, "Fsp MeInitEntryPointDxeFsp() Start\n"));

  ///
  /// Create a Ready to Boot event.
  ///
  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             MeReadyToBootEventDxeFsp,
             (VOID *) &ImageHandle,
             &Event
             );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    //
    // Install the protocol to prevent duplicated EOP sent outside FSP.
    //
    EopInFspHandle = NULL;
    Status = gBS->InstallProtocolInterface (
                    &EopInFspHandle,
                    &gMeSendEopInFspProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  MeEndOfFirmwareEventDxeFsp,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &mExitBootServicesEvent
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Fsp MeInitEntryPointDxeFsp() End\n"));

  return EFI_SUCCESS;
}

