/** @file
  TXT driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

#include "TxtOneTouchDxe.h"

GLOBAL_REMOVE_IF_UNREFERENCED TXT_ONE_TOUCH_OP_PROTOCOL mTxtOneTouchOpProtocol = {
  TxtExecOperation,
  TxtConfirmationDialog,
  TxtResetState
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_TCG_PROTOCOL    *mTcgProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED TXT_ONE_TOUCH_SETUP mTxtVariable;

/**
  @param[in] ImageHandle       - A handle for this module
  @param[in] SystemTable       - A pointer to the EFI System Table

  @retval EFI_SUCCESS   - If TXT initialization succeed
  @retval EFI_UNLOAD_IMAGE   - If TXT criterias are not met
**/
EFI_STATUS
EFIAPI
DriverEntry (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;
  EFI_HANDLE Handle;

  Handle = NULL;
  ZeroMem (&mTxtVariable, sizeof (TXT_ONE_TOUCH_SETUP));

  ///
  /// Install the protocol
  ///
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gTxtOneTouchOpProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mTxtOneTouchOpProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Locate TcgProtocol
  ///
  mTcgProtocol  = NULL;
  Status        = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &mTcgProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initiate the variable if it doesn't exist.
  ///
  if (ReadWriteVariable (&mTxtVariable, FALSE) != EFI_SUCCESS) {
    ReadWriteVariable (&mTxtVariable, TRUE);
  }

  return Status;
}

/**
  Read/Write variable for enable/disable TxT one
  touch functions

  @param[in] VariableData - Point to Setup variable buffer
  @param[in] WriteData    - TRUE, write changes to Setup Variable. FALSE, not to write variable.

  @retval EFI_SUCCESS           - Operation complete successful
  @retval EFI_INVALID_PARAMETER - VariableData is NULL
**/
EFI_STATUS
ReadWriteVariable (
  IN OUT TXT_ONE_TOUCH_SETUP *VariableData,
  IN BOOLEAN                 WriteData
  )
{
  EFI_STATUS Status;
  UINTN      Size;
  UINT32     VarAttrib;

  Status    = EFI_SUCCESS;
  Size      = 0;
  VarAttrib = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;

  if (VariableData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (WriteData == TRUE) {
    ///
    /// Write TxT variable
    ///
    Size = sizeof (TXT_ONE_TOUCH_SETUP);

    Status = gRT->SetVariable (
                    TXT_ONE_TOUCH_VAR,
                    &gTxtOneTouchGuid,
                    VarAttrib,
                    Size,
                    VariableData
                    );
  } else {
    ///
    /// Read TxT variable
    ///
    Size = sizeof (TXT_ONE_TOUCH_SETUP);

    Status = gRT->GetVariable (
                    TXT_ONE_TOUCH_VAR,
                    &gTxtOneTouchGuid,
                    NULL,
                    &Size,
                    VariableData
                    );
  }

  return Status;
}

/**
  Read TxT Maintenance flag

  @retval TRUE  - TxT Maintenance Flag is TRUE
  @retval FALSE - TxT Maintenance Flag is FALSE
**/
BOOLEAN
CheckTxtMaintenanceFlag (
  VOID
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  ///
  /// TBD. Need to read TPM NV index 0x50010000
  ///
  ///
  /// Read TxT variable first
  ///
  Status = ReadWriteVariable (&mTxtVariable, FALSE);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  return mTxtVariable.NoTxtMaintenance;
}

/**
  Extend PPI operation for TxT.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

  @retval EFI_SUCCESS     - Execute the Command successful
  @retval EFI_UNSUPPORTED - Command is not supported
**/
EFI_STATUS
EFIAPI
TxtExecOperation (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  ///
  /// Read TxT variable first
  ///
  Status = ReadWriteVariable (&mTxtVariable, FALSE);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Read variable for TxT One Touch function
  /// The variable can be Setup variable
  ///
  switch (Command) {
    case DISABLE_DEACTIVATE:
      ///
      /// Disable & Deactive TPM
      /// Disable TxT
      ///
      mTxtVariable.TxtEnable = FALSE;
      break;

    case ENABLE_VT:
      ///
      /// Enable VT
      ///
      mTxtVariable.VtEnable = TRUE;
      break;

    case DISABLE_VT_TXT:
      ///
      /// Disable VT and TxT
      ///
      mTxtVariable.VtEnable   = FALSE;
      mTxtVariable.TxtEnable  = FALSE;
      break;

    case ENABLE_VTD:
      ///
      /// Enable VT-d
      ///
      mTxtVariable.VtdEnable = TRUE;
      break;

    case DISABLE_VTD_TXT:
      ///
      /// Disable VT-d and TxT
      ///
      mTxtVariable.VtdEnable = FALSE;
      break;

    case ENABLE_ACTTPM_VT_VTD_TXT_DISABLE_STM:
      ///
      /// Enable-Active TPM
      /// Enable VT, VT-d and TxT
      /// Disable STM
      ///
      TpmEnableActive (ENABLE_ACTIVATE);
      ///
      /// mTxtVariable.TpmEnable = TRUE;
      /// mTxtVariable.TpmActive = TRUE;
      ///
      mTxtVariable.VtEnable   = TRUE;
      mTxtVariable.VtdEnable  = TRUE;
      mTxtVariable.TxtEnable  = TRUE;
      mTxtVariable.StmEnable  = FALSE;
      break;

    case ENABLE_ACTTPM_VT_VTD_TXT_STM:
      ///
      /// Enable-Active TPM
      /// Enable VT, VT-d, TxT and STM
      ///
      TpmEnableActive (ENABLE_ACTIVATE);
      ///
      /// mTxtVariable.TpmEnable = TRUE;
      /// mTxtVariable.TpmActive = TRUE;
      ///
      mTxtVariable.VtEnable   = TRUE;
      mTxtVariable.VtdEnable  = TRUE;
      mTxtVariable.TxtEnable  = TRUE;
      mTxtVariable.StmEnable  = TRUE;
      break;

    case DISABLE_STM:
      ///
      /// Disable STM
      ///
      mTxtVariable.StmEnable = FALSE;
      break;

    case DISABLE_TXT_STM:
      ///
      /// Disable TxT and STM
      ///
      mTxtVariable.TxtEnable  = FALSE;
      mTxtVariable.StmEnable  = FALSE;
      break;

    case DISABLE_SENTER_VMX:
      ///
      /// Disable SENTER and VMX
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_VMX_SMX_ONLY:
      ///
      /// Enable VMX in SMX only
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_VMX_OUTSIDE_SMX:
      ///
      /// Enable VMX outside SMX Only
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_VMX:
      ///
      /// Enable VMX
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_SENTER_ONLY:
      ///
      /// Enable SENTER Only
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_SENTER_VMX_IN_SMX:
      ///
      /// Enable SENTER and VMX in SMX
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_SENTER_VMX_OUTSIDE_SMX:
      ///
      /// Enable SENTER and VMX outside SMX
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case ENABLE_SENTER_VMX:
      ///
      /// Enable SENTER and VMX
      ///
      Status = EFI_UNSUPPORTED;
      break;

    case SET_NO_TXT_MAINTENANCE_FALSE:
      ///
      /// Set NoTxtMaintenance Flag FALSE
      ///
      mTxtVariable.NoTxtMaintenance = FALSE;
      break;

    case SET_NO_TXT_MAINTENANCE_TRUE:
      ///
      /// Set NoTxtMaintenance Flag TRUE
      ///
      mTxtVariable.NoTxtMaintenance = TRUE;
      break;

    default:
      return EFI_UNSUPPORTED;
  }
  ///
  /// Validate states
  ///
  Status = ValidateTxtStates (&mTxtVariable);
  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
  } else {
    ///
    /// if settings are correct, write it to variable
    ///
    Status = ReadWriteVariable (&mTxtVariable, TRUE);
  }

  return Status;
}

/**
  Confirmation dialog for TxT PPI

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT
  @param[in] Confirm - User confirm

  @retval EFI_SUCCESS     - Execute the Command successful
  @retval EFI_UNSUPPORTED - Command is not supported
**/
EFI_STATUS
EFIAPI
TxtConfirmationDialog (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command,
  IN OUT BOOLEAN               *Confirm
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  if (CheckTxtMaintenanceFlag ()) {
    *Confirm = FALSE;
  }

  switch (Command) {
    case DISABLE_DEACTIVATE:
      ///
      /// Disable & Deactive TPM
      /// Disable TxT
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable TxT\n\n\r"
              );
      break;

    case ENABLE_VT:
      ///
      /// Enable VT
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable VT\n\n\r"
              );
      break;

    case DISABLE_VT_TXT:
      ///
      /// Disable VT and TxT
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable VT and TxT\n\n\r"
              );
      break;

    case ENABLE_VTD:
      ///
      /// Enable VT-d
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable VT-d\n\n\r"
              );
      break;

    case DISABLE_VTD_TXT:
      ///
      /// Disable VT-d and TxT
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable VT-d and TxT\n\n\r"
              );
      break;

    case ENABLE_ACTTPM_VT_VTD_TXT_DISABLE_STM:
      ///
      /// Enable-Active TPM
      /// Enable VT, VT-d and TxT
      /// Disable STM
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable/Active TPM and Enable VT/VT-d/TxT, and Disable STM\n\n\r"
              );
      break;

    case ENABLE_ACTTPM_VT_VTD_TXT_STM:
      ///
      /// Enable-Active TPM
      /// Enable VT, VT-d, TxT and STM
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable/Active TPM and Enable VT/VT-d/TxT/STM\n\n\r"
              );
      break;

    case DISABLE_STM:
      ///
      /// Disable STM
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable STM\n\n\r"
              );
      break;

    case DISABLE_TXT_STM:
      ///
      /// Disable TxT and STM
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable TxT and STM\n\n\r"
              );
      break;

    case DISABLE_SENTER_VMX:
      ///
      /// Disable SENTER and VMX
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Disable SENTER and VMX\n\n\r"
              );
      break;

    case ENABLE_VMX_SMX_ONLY:
      ///
      /// Enable VMX in SMX only
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable VMX in SMX only\n\n\r"
              );
      break;

    case ENABLE_VMX_OUTSIDE_SMX:
      ///
      /// Enable VMX outside SMX Only
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable VMX outside SMX Only\n\n\r"
              );
      break;

    case ENABLE_VMX:
      ///
      /// Enable VMX
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable VMX\n\n\r"
              );
      break;

    case ENABLE_SENTER_ONLY:
      ///
      /// Enable SENTER Only
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable SENTER only\n\n\r"
              );
      break;

    case ENABLE_SENTER_VMX_IN_SMX:
      ///
      /// Enable SENTER and VMX in SMX
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable SENTER and VMX in SMX\n\n\r"
              );
      break;

    case ENABLE_SENTER_VMX_OUTSIDE_SMX:
      ///
      /// Enable SENTER and VMX outside SMX
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable SENTER and VMX outside SMX\n\n\r"
              );
      break;

    case ENABLE_SENTER_VMX:
      ///
      /// Enable SENTER and VMX
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Enable SENTER and VMX\n\n\r"
              );
      break;

    case SET_NO_TXT_MAINTENANCE_FALSE:
      ///
      /// Set NoTxtMaintenance Flag FALSE
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Set TxT Maintenance Flag to FALSE\n\n\r"
              );
      break;

    case SET_NO_TXT_MAINTENANCE_TRUE:
      ///
      /// Set NoTxtMaintenance Flag TRUE
      ///
      gST->ConOut->OutputString (
              gST->ConOut,
              L"\nA configuration change was requested to Set TxT Maintenance Flag to TRUE\n\n\r"
              );
      break;

    default:
      return EFI_UNSUPPORTED;
  }

  return Status;
}

/**
  Reset system.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

  @retval EFI_SUCCESS - Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
TxtResetState (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  )
{
  PCH_RESET_DATA     ResetData;

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  gRT->ResetSystem (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);

  return EFI_SUCCESS;
}
