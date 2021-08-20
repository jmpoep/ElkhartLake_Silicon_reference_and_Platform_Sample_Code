/** @file
  ME Initialize implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/S3BootScriptLib.h>
#include <Protocol/AmtReadyToBoot.h>
#include <Library/DxeMeLib.h>
#include <Register/HeciRegs.h>
#include <Library/HeciInitLib.h>
#include "HeciInit.h"
#include <Library/PciSegmentLib.h>
#include "MeInit.h"
#include <Protocol/Wdt.h>
#include <PchResetPlatformSpecific.h>
#include <Library/PmcPrivateLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN               mEopSentInFsp;

/**
  Signal a event to save Me relevant registers and check if EOP is sent inside FSP Dispatch.
  This event must be run before ExitPmAuth.

  @param[in] Event                The event that triggered this notification function
  @param[in] ParentImageHandle    Pointer to the notification functions context

**/
VOID
EFIAPI
MeEndOfDxeEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *ParentImageHandle
  )
{
  EFI_STATUS                      Status;
  VOID                            *Interface;
  EFI_HANDLE                      Handle;
  HECI_PROTOCOL                   *Heci;
  UINT32                          MeMode;
  HECI_FWS_REGISTER               MeFirmwareStatus;

  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));

  Handle = NULL;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return;
  }
  ///
  /// Check ME Status
  ///
  Status = Heci->GetMeMode (&MeMode);
  ASSERT_EFI_ERROR (Status);

  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));

  ///
  /// PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
  /// Step 2
  ///   Set "Power Management Initialization Register (ETR3) Field 1", D31:F2:ACh[31] = 1b
  ///   for production machine according to "RS - PCH Intel Management Engine
  ///  (Intel(r) ME) BIOS Writer's Guide".
  ///
  /// PCH ME BWG section 4.5.1
  /// The IntelR FPT tool /GRST option uses CF9GR bit to trigger global reset.
  /// Based on above reason, the BIOS should not lock down CF9GR bit during Manufacturing and
  /// Re-manufacturing environment.
  ///
  /// ETR3 is a resume well register and has no script save for it.
  /// System may go through S3 resume path from G3 if DeepSleep is enabled,
  /// that means all resume well registers will be reset to defaults.
  /// Save boot script for ETR3 register if DeepSleep is enabled.
  ///
  if (((MeMode == ME_MODE_NORMAL) || (MeMode == ME_MODE_TEMP_DISABLED)) && !(MeFirmwareStatus.r.ManufacturingMode)) {
    ///
    /// PCH ME BWG section 4.4.1
    /// BIOS must also ensure that CF9GR is cleared and locked (via bit31 of the same register) before
    /// handing control to the OS in order to prevent the host from issuing global resets and resetting
    /// Intel Management Engine.
    ///
    PmcDisableCf9GlobalResetWithLockInS3BootScript ();
  } else {
    PmcDisableCf9GlobalResetInS3BootScript ();
  }

  //
  // Sending notification that BIOS is starting to run 3rd party code.
  //
  if (MeCoreBiosDoneEnabled ()) {
    HeciCoreBiosDoneMsg ();
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gMeCoreBiosDoneProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }


  ///
  /// The protocol needs to be checked in EndOfDxe to prevent 3rd party installing it to skip EOP
  /// If the protocol located successfully, it indicates EOP should be sent in FSP Dispatch; otherwise, in wrapper.
  ///
  Status = gBS->LocateProtocol (&gMeSendEopInFspProtocolGuid, NULL, (VOID **)&Interface);
  mEopSentInFsp = (!EFI_ERROR (Status))? TRUE: FALSE;

  gBS->CloseEvent (Event);
}

/**
  Signal Me Ready To Boot Event
  Perform tasks below in the following order:
  1. Signal AmtReadyToBoot events for AMT platform hooks.
  2. Signal MePlatformReadyToBoot event for platform hooks.
  3. Report FWSTS and save to SMBIOS.
  4. Send EOP message.
  5. Lock config for manufacturing mode.
  6. Disable ME devices if particular ME-BIOS boot path requires this
     and this has not been done in PEI phase.

  @param[in] Event            The event that triggered this notification function
  @param[in] Context          Pointer to the notification functions context
**/
VOID
EFIAPI
MeReadyToBootEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));

  if (!mEopSentInFsp) {
    MeReadyToBoot ();
  }

  gBS->CloseEvent (Event);
}
