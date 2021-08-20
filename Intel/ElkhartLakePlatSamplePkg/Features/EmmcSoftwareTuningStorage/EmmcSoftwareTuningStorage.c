/** @file
  This module implements the ScsEmmcSoftwareTuningSaveResults protocol.
  It saves the tuned DLL values to flash after tuning is completed.

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

#include <Uefi.h>
#include <Uefi/UefiMultiPhase.h>
#include <Pi/PiMultiPhase.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HobLib.h>
#include <ScsEmmcSoftwareTuningVariable.h>
#include <Protocol/ScsEmmcSoftwareTuning.h>

/**
  Set tuning variable to new value.

  @param[in] TuningVariable  New tuning variable to save to flash
**/
STATIC
VOID
EmmcSetTuningVariable (
  IN SCS_EMMC_SOFTWARE_TUNING_VARIABLE  *TuningVariable
  )
{
  EFI_STATUS  Status;

  Status = gRT->SetVariable (
                  SCS_EMMC_SOFTWARE_TUNING_VARIABLE_NAME,
                  &gScsEmmcSoftwareTuningVariableGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof (SCS_EMMC_SOFTWARE_TUNING_VARIABLE),
                  TuningVariable
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to set Emmc tuning variable\n"));
  }
}

/**
  Locate software tuning protocol and save tuning values to flash.

  @return Status of the protocl locate.
**/
STATIC
EFI_STATUS
EmmcSaveSoftwareTuningResults (
  VOID
  )
{
  EFI_STATUS                         Status;
  SCS_EMMC_SOFTWARE_TUNING_VARIABLE  ScsEmmcTuningVariable;
  SCS_EMMC_SOFTWARE_TUNING_PROTOCOL  *SoftwareTuningProtocol;

  Status = gBS->LocateProtocol (
                  &gScsEmmcSoftwareTuningProtocolGuid,
                  NULL,
                  (VOID**) &SoftwareTuningProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CopyMem (&ScsEmmcTuningVariable.TuningResults, &SoftwareTuningProtocol->TuningResults, sizeof (SCS_EMMC_SOFTWARE_TUNING_RESULTS));

  EmmcSetTuningVariable (&ScsEmmcTuningVariable);
  return EFI_SUCCESS;
}

/**
  Clear software tuning variable.
**/
STATIC
VOID
EmmcClearSoftwareTuningVariable (
  VOID
  )
{
  SCS_EMMC_SOFTWARE_TUNING_VARIABLE  TuningVariable;

  ZeroMem (&TuningVariable, sizeof (SCS_EMMC_SOFTWARE_TUNING_VARIABLE));
  EmmcSetTuningVariable (&TuningVariable);
}

/**
  This function is executed when software tuning is finished and
  gEmmcSoftwareTuningProtocol has been installed.

  @param[in] Event    Register protocol notify event
  @param[in] Context  Event context
**/
VOID
EFIAPI
EmmcStorageOnSoftwareTuningFinished (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS  Status;

  Status = EmmcSaveSoftwareTuningResults ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcStorage: Failed to save tuning results\n"));
  }

  //
  // We assume that software tuning protocol will be installed
  // at most once during platform boot. To ignore any future installations
  // we close the event here.
  //
  Status = gBS->CloseEvent (Event);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcStorage: Failed to close the event\n"));
  }
}

/**
  Registers callback on gEmmcSoftwareTuningProtocol
  installation.

  @return Status of the callback registration
**/
STATIC
EFI_STATUS
EmmcStorageRegisterTuningFinishedEvent (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   TuningFinishedEvent;
  VOID        *ProtocolNotifyRegistration;

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  EmmcStorageOnSoftwareTuningFinished,
                  NULL,
                  &TuningFinishedEvent
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    return gBS->RegisterProtocolNotify (
                  &gScsEmmcSoftwareTuningProtocolGuid,
                  TuningFinishedEvent,
                  &ProtocolNotifyRegistration
                  );
  }
}

/**
  Integrated eMMC software tuning variable storage module
  entry point.

  @param[in] ImageHandle  This image handle
  @param[in] SystemTable  System table pointer
**/
EFI_STATUS
EFIAPI
EmmcSoftwareTuningStorageEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                         Status;

  if (GetBootModeHob () == BOOT_WITH_DEFAULT_SETTINGS) {
    DEBUG ((DEBUG_INFO, "EmmcStorage: Botting with default settings, resetting tuning variable\n"));
    EmmcClearSoftwareTuningVariable ();
    return EFI_SUCCESS;
  } else {
    Status = EmmcSaveSoftwareTuningResults ();
    if (EFI_ERROR (Status)) {
      return EmmcStorageRegisterTuningFinishedEvent ();
    } else {
      return Status;
    }
  }
}

