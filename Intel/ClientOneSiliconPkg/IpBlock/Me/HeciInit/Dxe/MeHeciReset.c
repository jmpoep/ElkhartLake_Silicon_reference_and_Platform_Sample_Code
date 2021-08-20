/** @file
  Provide the ME reset system handler

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
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/ResetSystemLib.h>
#include <PchResetPlatformSpecific.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/DxeMeLib.h>
#include <Library/PmcLib.h>
#include <Register/PmcRegs.h>
#include <Protocol/PlatformSpecificResetHandler.h>
#include <Library/PmcPrivateLib.h>


/**
  Print reset message for debug build readability
**/
VOID
PrintResetMessage (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "******************************\n"));
  DEBUG ((DEBUG_INFO, "**    SYSTEM REBOOT !!!     **\n"));
  DEBUG ((DEBUG_INFO, "******************************\n"));
}

/**
  Sent HECI command to ME for GlobalReset

  @param[in] ResetType            Warm or cold
  @param[in] ResetStatus          Possible cause of reset
  @param[in] DataSize             Size of ResetData in bytes
  @param[in] ResetData            Optional Unicode string
**/
VOID
EFIAPI
PlatformResetSystem (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  EFI_GUID            *GuidPtr;

  PrintResetMessage ();
  if (ResetType != EfiResetPlatformSpecific) {
    return;
  }
  if (ResetData == NULL) {
    return;
  }

  GuidPtr = (EFI_GUID *) ((UINT8 *) ResetData + DataSize - sizeof (EFI_GUID));
  if (CompareGuid (GuidPtr, &gPchGlobalResetGuid)) {
    //
    // PCH BIOS Spec Section 4.6 GPIO Reset Requirement
    //
    DEBUG ((DEBUG_INFO,"Enable CF9 Global Reset - DXE\n"));
    PmcEnableCf9GlobalReset ();

    //
    // Let ME do global reset if Me Fw is available
    //
    DEBUG ((DEBUG_INFO, "Send HECI command CBM_HRR_GLOBAL_RESET\n"));
    ResetStatus = HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
    if (!EFI_ERROR (ResetStatus)) {
      MicroSecondDelay (1000000);
    }
  }
}

/**
  Hook the system reset to properly reset function with ME system.

  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
VOID
EFIAPI
OnResetHandlerInstall (
  IN EFI_EVENT                      Event,
  IN VOID                           *Context
  )
{
  EFI_STATUS                                     Status;
  EDKII_PLATFORM_SPECIFIC_RESET_HANDLER_PROTOCOL *ResetHandler;

  Status = gBS->LocateProtocol (
              &gEdkiiPlatformSpecificResetHandlerProtocolGuid,
              NULL,
              (VOID **) &ResetHandler
              );

  if (!EFI_ERROR (Status)) {
    ResetHandler->RegisterResetNotify (ResetHandler, PlatformResetSystem);
    gBS->CloseEvent (Event);
  }
}


/**
  Register ME reset handler.

**/
VOID
RegisterMeReset (
  VOID
  )
{
  VOID                            *Registration;

  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));
  EfiCreateProtocolNotifyEvent (
    &gEdkiiPlatformSpecificResetHandlerProtocolGuid,
    TPL_CALLBACK,
    OnResetHandlerInstall,
    NULL,
    &Registration
    );
}

