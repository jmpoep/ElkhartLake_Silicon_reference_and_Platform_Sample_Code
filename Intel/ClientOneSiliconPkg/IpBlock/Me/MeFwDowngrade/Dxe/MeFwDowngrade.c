/** @file
  MeFwDowngrade driver

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
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/TimerLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/DxeMeLib.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>

GLOBAL_REMOVE_IF_UNREFERENCED UINT8    mHeciHmrfpoLockResult;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8    mHeciHmrfpoEnableResult;

/**
  Tell User that we failed to lock/unlock the flash - Do this after we have graphics initialized

  @param[in] Event                The event that triggered this notification function
  @param[in] Context              Pointer to the notification functions context
**/
VOID
EFIAPI
MeFwDowngradeMsgEvent (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{
  if (mHeciHmrfpoLockResult != HMRFPO_LOCK_SUCCESS) {
    MeReportError (MSG_HMRFPO_LOCK_FAILURE);
  }

  if (mHeciHmrfpoEnableResult != HMRFPO_ENABLE_SUCCESS) {
    MeReportError (MSG_HMRFPO_UNLOCK_FAILURE);
  }

  gBS->CloseEvent (Event);
  return;
}

/**
  Send the HMRFPO_DISABLE MEI message.

  @param[in] Event                The event that triggered this notification function
  @param[in] Context              Pointer to the notification functions context
**/
VOID
EFIAPI
MeHmrfpoDisableEvent (
  IN EFI_EVENT                       Event,
  IN VOID                            *Context
  )
{
  EFI_STATUS Status;

  DEBUG ((DEBUG_INFO, "(B3) Me FW Downgrade - Send the HMRFPO_DISABLE MEI message\n"));

  Status = HeciHmrfpoDisable ();
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Me FW Downgrade Disable Msg Received Successfully\n"));
  } else {
    DEBUG ((DEBUG_ERROR, "Me FW Downgrade Disable Msg ACK not Received\n"));
  }

  ///
  /// Hide ME devices so we don't get a yellow bang in OS with disabled devices
  ///
  DisableAllMeDevices ();

  gBS->CloseEvent (Event);

  return;
}

/**
  Entry point for the MeFwDowngrade driver

  @param[in] ImageHandle          Standard entry point parameter.
  @param[in] SystemTable          Standard entry point parameter.

  @retval EFI_UNSUPPORTED         ME policy library initialization failure.
  @retval Others                  Status code returned by CreateEventEx.
**/
EFI_STATUS
EFIAPI
MeFwDowngradeEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS        Status;
  EFI_EVENT         MeFwDowngradeEvent;
  HECI_PROTOCOL     *Heci;
  UINT32            MeMode;
  UINT32            MeStatus;
  HECI_FWS_REGISTER MeFirmwareStatus;

  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  ASSERT_EFI_ERROR (Status);

  Status = Heci->GetMeMode (&MeMode);
  ASSERT_EFI_ERROR (Status);

  Status = Heci->GetMeStatus (&MeStatus);
  ASSERT_EFI_ERROR (Status);

  ///
  /// (B1) Check if ME is in normal mode.
  ///
  if (MeMode == ME_MODE_NORMAL) {
    ///
    /// (A2) Intel Me image re-flash is requested?
    ///
    if (MeFwDowngradeSupported ()) {
      ///
      /// (A4)(A5) The BIOS sends the HMRFPO ENABLE MEI message and wait for response.
      ///
      mHeciHmrfpoEnableResult  = HMRFPO_ENABLE_UNKNOWN_FAILURE;
      Status                   = HeciHmrfpoEnable (&mHeciHmrfpoEnableResult);
      if ((Status == EFI_SUCCESS) && (mHeciHmrfpoEnableResult == HMRFPO_ENABLE_SUCCESS)) {
        ///
        /// (A6) The BIOS sends the GLOBAL RESET MEI message
        ///
        DEBUG ((DEBUG_INFO, "Me FW Downgrade !!- Step A6\n"));
        HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
        CpuDeadLoop ();
      }
      ///
      /// (A8) Error Handling, HeciHmrfpoEnable include error handling.
      ///
      DEBUG ((
        DEBUG_ERROR,
        "Me FW Downgrade Error !!- Step A8, the Status is %r, The result is %x\n",
        Status,
        mHeciHmrfpoEnableResult
        ));
      IoWrite8 (0x80, 0xA8);
    } else {
      ///
      /// (A7) The BIOS sends the HMRFPO Lock MEI message and continues the normal boot
      ///
      mHeciHmrfpoLockResult = HMRFPO_LOCK_SUCCESS;

      ///
      /// The ME firmware will ignore the HMRFPO LOCK command if ME is in ME manufacturing mode
      ///
      if ((MeFirmwareStatus.r.ManufacturingMode == 0) &&
          ((ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) || (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY))) {

        DEBUG ((DEBUG_INFO, "(A7) Me FW Downgrade - The BIOS sends the HMRFPO Lock MEI message and continues the normal boot\n"));

        Status = HeciHmrfpoLock (&mHeciHmrfpoLockResult);
        if (EFI_ERROR (Status)) {
          mHeciHmrfpoLockResult = HMRFPO_LOCK_FAILURE;
        }
      }
    }

    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    MeFwDowngradeMsgEvent,
                    (VOID *) &ImageHandle,
                    &gMePlatformReadyToBootGuid,
                    &MeFwDowngradeEvent
                    );

  }
  ///
  /// (B3) Create an event that will call the HMRFPO_DISABLE
  ///
  if ((MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_HECI_MSG) &&
      (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)) {
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    MeHmrfpoDisableEvent,
                    (VOID *) &ImageHandle,
                    &gMePlatformReadyToBootGuid,
                    &MeFwDowngradeEvent
                    );
  }

  return Status;
}
