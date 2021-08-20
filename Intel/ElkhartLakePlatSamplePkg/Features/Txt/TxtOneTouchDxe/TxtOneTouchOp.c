/** @file
  TXT one touch driver.

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
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Register/Cpuid.h>
#include <CpuAccess.h>
#include <IndustryStandard/Tpm12.h>
#if FixedPcdGetBool(PcdTxtEnable) == 1
#include <SetupVariable.h>
#endif
extern EFI_TCG_PROTOCOL *mTcgProtocol;

/**
  Execute TPM command

  @param[in] TcgProtocol             - Point to EFI_TCG_PROTOCOL
  @param[in] Ordinal                 - TPM Command code
  @param[in] AdditionalParameterSize - Size of additional parameters
  @param[in] AdditionalParameters    - Point to the buffer saves additional parameters

  @retval EFI_SUCCESS                - TPM command lunch success
  @retval TPM_PP_BIOS_FAILURE        - BIOS fail to execute TPM command
**/
TPM_RESULT
TpmCommandNoReturnData (
  IN EFI_TCG_PROTOCOL *TcgProtocol,
  IN TPM_COMMAND_CODE Ordinal,
  IN UINTN            AdditionalParameterSize,
  IN VOID             *AdditionalParameters
  )
{
  EFI_STATUS          Status;
  TPM_RQU_COMMAND_HDR *TpmRqu;
  TPM_RSP_COMMAND_HDR TpmRsp;
  UINT32              Size;

  TpmRqu = (TPM_RQU_COMMAND_HDR *) AllocatePool (sizeof (*TpmRqu) + AdditionalParameterSize);
  if (TpmRqu == NULL) {
    return TPM_PP_BIOS_FAILURE;
  }

  TpmRqu->tag       = H2NS (TPM_TAG_RQU_COMMAND);
  Size              = (UINT32) (sizeof (*TpmRqu) + AdditionalParameterSize);
  TpmRqu->paramSize = H2NL (Size);
  TpmRqu->ordinal   = H2NL (Ordinal);
  CopyMem (TpmRqu + 1, AdditionalParameters, AdditionalParameterSize);

  Status = TcgProtocol->PassThroughToTpm (
                  TcgProtocol,
                  Size,
                  (UINT8 *) TpmRqu,
                  (UINT32) sizeof (TpmRsp),
                  (UINT8 *) &TpmRsp
                  );
  FreePool (TpmRqu);
  if (EFI_ERROR (Status) || (TpmRsp.tag != H2NS (TPM_TAG_RSP_COMMAND))) {
    return TPM_PP_BIOS_FAILURE;
  }

  return H2NL (TpmRsp.returnCode);
}

/**
  Enable/Active TPM

  @param[in] Command  - The operation code for TxT One Touch function

  @retval EFI_SUCCESS        - TPM command lunch success
  @retval EFI_UNSUPPORTED    - The Command is not supported
  @retval EFI_DEVICE_ERROR   - Faile to lunch TPM command
**/
EFI_STATUS
TpmEnableActive (
  IN UINT8 Command
  )
{
  TPM_RESULT TpmResponse;
  EFI_STATUS Status;
  BOOLEAN    BoolVal;

  BoolVal     = FALSE;
  TpmResponse = 0;
  Status      = EFI_SUCCESS;

  switch (Command) {
    case ENABLE:
      TpmResponse = TpmCommandNoReturnData (
                      mTcgProtocol,
                      TPM_ORD_PhysicalEnable,
                      0,
                      NULL
                      );
      break;

    case ACTIVATE:
      BoolVal = FALSE;
      TpmResponse = TpmCommandNoReturnData (
                      mTcgProtocol,
                      TPM_ORD_PhysicalSetDeactivated,
                      sizeof (BoolVal),
                      &BoolVal
                      );
      break;

    case ENABLE_ACTIVATE:
      Status = TpmEnableActive (ENABLE);
      if (Status == EFI_SUCCESS) {
        Status = TpmEnableActive (ACTIVATE);
      }

      return Status;

    default:
      Status = EFI_UNSUPPORTED;
      break;
  }

  if (TpmResponse != 0) {
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Verify the status of Chipset capability and Setup settings

  @param[in] Data  - Point to TXT_ONE_TOUCH_SETUP

  @exception EFI_UNSUPPORTED - The system is not able to launch TxT
  @retval EFI_SUCCESS - The system is able to launch TxT
**/
EFI_STATUS
ValidateTxtStates (
  IN TXT_ONE_TOUCH_SETUP *Data
  )
{
  CPUID_VERSION_INFO_ECX Ecx;

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);

  if (Data->VtEnable) {
    ///
    /// Check if VMX supported
    ///
    if (Ecx.Bits.VMX == 0) {
      return EFI_UNSUPPORTED;
    }
  }

  if (Data->TxtEnable) {
    ///
    /// Check if TxT & VMX supported
    ///
    if ((Ecx.Bits.VMX == 0) ||
        (Ecx.Bits.SMX == 0)) {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

#if FixedPcdGetBool(PcdTxtEnable) == 1
/**
  Update TxT Setup settings to Setup Variable

  @param[in] VariableData  - Point to TXT_ONE_TOUCH_SETUP

  @retval EFI_SUCCESS      - Update Setup variable successful
**/
EFI_STATUS
UpdateSetupVar (
  IN OUT TXT_ONE_TOUCH_SETUP *VariableData
  )
{
  EFI_STATUS           Status;
  SA_SETUP             SaSetup;
  CPU_SETUP            CpuSetup;
  SETUP_DATA           SetupData;
  UINTN                VariableSize;
  UINT32               VarAttributes;

  ///
  /// Get configuration from Setup Data
  ///
  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &VarAttributes,
                  &VariableSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &VarAttributes,
                  &VariableSize,
                  &SaSetup
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  &VarAttributes,
                  &VariableSize,
                  &CpuSetup
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SetupData.VT        = VariableData->VtEnable;
  SaSetup.EnableVtd   = VariableData->VtdEnable;
  CpuSetup.Txt        = VariableData->TxtEnable;
  if (VariableData->TxtEnable) {
    SetupData.ActiveCoreCount = 0;
    SetupData.HyperThreading  = 1;
  }


  ///
  /// Write data back
  ///
  Status = gRT->SetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  VarAttributes,
                  sizeof (SETUP_DATA),
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gRT->SetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  VarAttributes,
                  sizeof (SA_SETUP),
                  &SaSetup
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gRT->SetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  VarAttributes,
                  sizeof (CPU_SETUP),
                  &CpuSetup
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
#endif
