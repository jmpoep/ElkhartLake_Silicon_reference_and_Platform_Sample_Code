/** @file
  Touch Host Controller Absolute Pointer API

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include "ThcPrivate.h"

/**
  AbsPtr protocol's WaitForInput (called when a consumer of AbsPtr protocol waits for new data)

  @param[in]  Event              Pointer to event that triggered this callback
  @param[in]  Context            Device context
**/
VOID
EFIAPI
AbsPtrWaitForInput (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{

}

/**
  Reset touch panel
  Function required by AbsPtr protocol.

  @param[in]  This
  @param[in]  ExtendedVerification

  @retval EFI_UNSUPPORTED
**/
EFI_STATUS
EFIAPI
AbsPtrReset (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL *This,
  IN BOOLEAN                       ExtendedVerification
  )
{
  DEBUG ((DEBUG_INFO, "Thc reset attempted\n"));
  return EFI_UNSUPPORTED;
}

/**
  If not-yet-consumed touch data is available, GetState() returns it and marks it unavailable
  If such data is not available, error will be returned. User should wait until WaitForInput event gets signalled

  @param[in]      This
  @param[in/out]  State

  @retval EFI_SUCCESS     Data consumed
  @retval EFI_NOT_READY   Data not available
**/
EFI_STATUS
EFIAPI
AbsPtrGetState (
  IN      EFI_ABSOLUTE_POINTER_PROTOCOL  *This,
  IN OUT  EFI_ABSOLUTE_POINTER_STATE     *State
  )
{
  THC_DEV     *ThcDev;

  if (State == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ThcDev  = THC_CONTEXT_FROM_ABSPTR_PROTOCOL (This);

  if (ThcDev->AbsPtrDataAvailable) {
    State->CurrentX      = (ThcDev->Report.HigherXByte << 8) + ThcDev->Report.LowerXByte;
    State->CurrentY      = (ThcDev->Report.HigherYByte << 8) + ThcDev->Report.LowerYByte;
    State->CurrentZ      = 0;
    State->ActiveButtons = ThcDev->Report.TouchSts;
    THC_LOCAL_DEBUG(L"AbsPtr State | X:%d | Y:%d | ActiveButton: %d \n", State->CurrentX, State->CurrentY, State->ActiveButtons)
    ThcDev->AbsPtrDataAvailable = FALSE;
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_READY;
  }
}

/**
  Installs AbsolutePointerProtocol
  Assigns TouchPanel Guid for Virtual Keyboard support

  @param[in]  ThcDev            Context of Thc device

  @retval EFI_SUCCESS           Absolute Pointer Protocol Installed
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
ThcInstallAbsPtr (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS   Status;

  ThcDev->AbsPtrMode.AbsoluteMinX = 0;
  ThcDev->AbsPtrMode.AbsoluteMinY = 0;
  ThcDev->AbsPtrMode.AbsoluteMinZ = 0;
  ThcDev->AbsPtrMode.AbsoluteMaxX = 0x7FFF;
  ThcDev->AbsPtrMode.AbsoluteMaxY = 0x7FFF;
  ThcDev->AbsPtrMode.AbsoluteMaxZ = 0;
  ThcDev->AbsPtrMode.Attributes   = 0;

  ThcDev->AbsPtrProtocol.Reset    = AbsPtrReset;
  ThcDev->AbsPtrProtocol.GetState = AbsPtrGetState;
  ThcDev->AbsPtrProtocol.Mode     = &(ThcDev->AbsPtrMode);

  Status = gBS->CreateEvent (EVT_NOTIFY_WAIT, TPL_NOTIFY, AbsPtrWaitForInput, ThcDev, &((ThcDev->AbsPtrProtocol).WaitForInput));
  THC_LOCAL_DEBUG(L"ThcInstallAbsPtr CreateEvent WaitForInput  Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcInstallAbsPtr error, cannot create CreateEvent AbsPtrWaitForInput Status: %r\n", Status));
    return Status;
  }

  //
  // Install Absolute Pointer Protocol and TouchPanelGuid onto ImageHandle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ThcDev->ControllerHandle,
                  &gEfiAbsolutePointerProtocolGuid,
                  &ThcDev->AbsPtrProtocol,
                  &gEfiTouchPanelGuid,
                  NULL,
                  NULL
                  );
  THC_LOCAL_DEBUG(L"ThcInstallAbsPtr Install AbsPtrProtocol  Status: %r\n", Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcInstallAbsPtr ERROR - Thc failed to install AbsolutePointerProtocol, Status: %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Closes and uninstalls Absolute Pointer Protocol

  @param[in]  ThcDev            Context of Thc device

**/
VOID
EFIAPI
ThcStopAbsPtr (
  IN THC_DEV                *ThcDev
  )
{
  THC_LOCAL_DEBUG(L"ThcStopAbsPtr \n");
  ThcDev->AbsPtrDataAvailable = FALSE;
  //
  // Done with the events
  //
  if (ThcDev->PollingEvent != NULL) {
    gBS->CloseEvent (ThcDev->PollingEvent);
  }
  if (ThcDev->AbsPtrProtocol.WaitForInput != NULL) {
    gBS->CloseEvent (ThcDev->AbsPtrProtocol.WaitForInput);
  }
  //
  //  Close/Uninstall Abs Ptr Protocol
  //
  gBS->CloseProtocol (
         ThcDev->ControllerHandle,
         &gEfiPciIoProtocolGuid,
         &ThcDev->AbsPtrProtocol,
         ThcDev->ControllerHandle
         );
  gBS->UninstallMultipleProtocolInterfaces (
         ThcDev->ControllerHandle,
         &gEfiAbsolutePointerProtocolGuid,
         &ThcDev->AbsPtrProtocol,
         NULL
         );
}
