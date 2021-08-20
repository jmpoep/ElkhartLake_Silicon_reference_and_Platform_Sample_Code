/**@file
  Secure Erase Implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "SecureErase.h"
#include "Ui.h"
#include "AtaSecureErase.h"
#include "NvmeSecureErase.h"
#include "SimulatedSecureErase.h"
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include <SetupVariable.h>
#include <Protocol/AmtWrapperProtocol.h>
#include <Library/PcdLib.h>
#include <Library/DxeAsfHeciLib.h>

SETUP_DATA                                mSetupData;
UINT32                                    mSetupDataAttr = 0;

AMT_READY_TO_BOOT_PROTOCOL mSecureEraseReadyToBoot = {
  AMT_READY_TO_BOOT_PROTOCOL_REVISION,
  SecureEraseOnReadyToBoot
};

/**
  Get Setup Variable from NVM

  @retval EFI_SUCCESS      Data retrieved
  @retval Others           Data was not retrieved
**/
EFI_STATUS
GetSetupData (
  VOID
  )
{
  EFI_STATUS                           Status;
  UINTN                                VarSize = sizeof (SETUP_DATA);

  DEBUG ((DEBUG_INFO, "SecureErase::GetSetupData : "));
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &mSetupDataAttr,
                  &VarSize,
                  &mSetupData
                  );
  DEBUG ((DEBUG_INFO, "Status=%r\n", Status));
  return Status;
}

/**
  Save Setup Variable to NVM

  @retval EFI_SUCCESS      Data saved successfully
  @retval Others           Data was not retrieved
**/
EFI_STATUS
SaveSetupData (
  VOID
  )
{
  EFI_STATUS                           Status;
  UINTN                                VarSize = sizeof (SETUP_DATA);

  Status = gRT->SetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  mSetupDataAttr,
                  VarSize,
                  &mSetupData
                  );

  DEBUG ((DEBUG_INFO, "SecureErase::SaveSetupData : Status=%r\n", Status));
  return Status;
}

/**
  Check if Corporate firmware is installed

  @retval EFI_SUCCESS                  The firmware is Corporate
  @retval EFI_NOT_READY                Can't locate required data
  @retvak EFI_UNSUPPORTED              The firmware is NOT Corporate
**/
EFI_STATUS
IsCorporateFwInstalled (
  VOID
  )
{
  ME_BIOS_PAYLOAD_HOB                 *MbpHob = NULL;

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to obtain hob : gMeBiosPayloadHobGuid\n"));
    return EFI_NOT_READY;
  }

  if (!MbpHob->MeBiosPayload.FwPlatType.Available) {
    DEBUG ((DEBUG_INFO, "mMbpHob->MeBiosPayload.FwPlatType.Available is FALSE\n"));
    return EFI_NOT_READY;
  }

  if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeCorporateFw) {
    DEBUG ((DEBUG_INFO, "IntelMeFwImageType != INTEL_ME_CORPORATE_FW\n"));
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Checks if Secure Erase is requested by AMT

  @retval TRUE     Secure Erase was requested by AMT
  @retval FALSE    Secure Erase wasn't requested by AMT
**/
BOOLEAN
IsAmtSecureErase (
  VOID
  )
{
  EFI_STATUS                           Status;
  AMT_WRAPPER_PROTOCOL                 *AmtWrapper;

  Status = gBS->LocateProtocol (&gAmtWrapperProtocolGuid, NULL, (VOID **) &AmtWrapper);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SecureErase :: IsAmtSecureErase :: No AMT Wrapper\n"));
  } else if (AmtWrapper->IsSecureEraseEnabled ()) {
    DEBUG ((DEBUG_INFO, "SecureErase :: IsSecureEraseRequested : Requested by AMT\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Checks if Secure Erase is requested by Setup

  @retval TRUE     Secure Erase was requested by Setup
  @retval FALSE    Secure Erase wasn't requested by Setup
**/
BOOLEAN
IsSetupSecureErase (
  VOID
  )
{
  EFI_STATUS                           Status;

  Status = GetSetupData ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SecureErase :: IsSetupSecureErase :: Can't get Setup Data\n"));
  } else if (mSetupData.ForceSecureErase) {
    DEBUG ((DEBUG_INFO, "SecureErase :: IsSecureEraseRequested : Requested by SetupData\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Checks if Secure Erase has been requested

  @retval TRUE     Secure Erase was requested
  @retval FALSE    Secure Erase wasn't requested
**/
BOOLEAN
IsSecureEraseRequested (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "SecureErase :: IsSecureEraseRequested\n"));

  if (IsAmtSecureErase () ||
      IsSetupSecureErase ()) {
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "SecureErase :: IsSecureEraseRequested : Secure Erase not requested\n"));
  return FALSE;
}

/**
  Attempts to erase ATA and NVMe drives.

  @retval EFI_SUCCESS         Erase device succeed
  @retval EFI_UNSUPPORTED     The device is not supported
  @retval EFI_ACCESS_DENIED   User has entered wrong password too many times
  @retval EFI_ABORTED         The device is supported, but the system
                              has failed to erase it
**/
EFI_STATUS
EraseDevices (
  VOID
  )
{
  EFI_STATUS                           Status;
  EFI_TPL                              OldTpl;

  DEBUG ((DEBUG_INFO, "SecureErase :: EraseDevice\n"));
  OldTpl = EfiGetCurrentTpl ();

  gBS->RestoreTPL (TPL_APPLICATION);
  InitUiLib ();
  SetScreenTitle (L"Secure erase");
  ClearScreen ();

  Status = GetSetupData ();
  if ((!EFI_ERROR (Status)) && mSetupData.SecureEraseModeRealMode == TRUE) {
    DEBUG ((DEBUG_INFO, "SecureErase in progress\n"));
    Status = EraseAtaDevice ();
    DEBUG ((DEBUG_INFO, "AtaStatus = %r\n", Status));
    if (!EFI_ERROR (Status)) {
      Status = EraseNvmeDevice ();
      DEBUG ((DEBUG_INFO, "NvmeStatus = %r\n", Status));
    }
  } else {
    Status = SimulateSecureErase ();
  }

  if (Status == EFI_SUCCESS) {
    if (mSetupData.ForceSecureErase == TRUE) {
      mSetupData.ForceSecureErase = FALSE;
      SaveSetupData ();
    }
    ClearBootOptions ();
  }

  DEBUG ((DEBUG_INFO, "SecureErase :: Report Secure Erase Operation Status: %r\nSecureErase :: EraseDevices end\n", Status));
  SendRsePetAlert (Status);
  ReportBiosStatus (Status);

  if (mSetupData.SecureEraseModeRealMode == FALSE) {
    SimulateSecureEraseDone ();
    //
    // If demo mode is enabled, don't restart. Use dead loop to make sure screen keeps
    // displaying "missing operating system" message from SimulatedSecureErase.c forever.
    //
    CpuDeadLoop ();
  }

  PrintSummary (Status);

  gBS->RaiseTPL (OldTpl);
  return Status;
}


/**
  This function is executed on AMT Ready to boot and performs Secure Erase.
**/
VOID
EFIAPI
SecureEraseOnReadyToBoot (
  VOID
  )
{
  EFI_STATUS    Status;

  DEBUG ((DEBUG_INFO, "SecureErase :: SecureEraseOnReadyToBoot\n"));
  Status = EraseDevices ();
  gRT->ResetSystem (EfiResetShutdown, Status, 0, NULL);

  return;
}


/**
  Drivers entry point. Checks if secure erase has been requested via boot options,
  if so, starts the procedure.

  @param[in] ImageHandle      The firmware allocated handle for the EFI image.
  @param[in] SystemTable      A pointer to the EFI System Table.

  @retval EFI_SUCCESS         Secure erase procedure has been started
  @retval EFI_ABORTED         Failed to register ready to boot event
  @retval EFI_UNSUPPORTED     Feature is not supported by the FW
**/
EFI_STATUS
EFIAPI
SecureEraseEntryPoint (
  IN EFI_HANDLE                       ImageHandle,
  IN EFI_SYSTEM_TABLE                 *SystemTable
  )
{
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;

  DEBUG ((DEBUG_INFO, "SecureErase :: SecureEraseEntryPoint\n"));

  Status = IsCorporateFwInstalled ();
  DEBUG ((DEBUG_INFO, "IsCorporateFwInstalled -> status=%r\n",Status));
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  if (!IsSecureEraseRequested ()) {
    return EFI_ABORTED;
  }
  //
  // Secure Erase is requested, so this module will take control over HDD's
  // unlocking process
  //
  PcdSetBoolS (PcdSkipHddPasswordPrompt, TRUE);

  //
  // Install an Amt ready to boot protocol.
  //
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gAmtReadyToBootProtocolGuid,
                  &mSecureEraseReadyToBoot,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
