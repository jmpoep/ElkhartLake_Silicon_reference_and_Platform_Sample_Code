/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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
#include <Base.h>
#include <Library/AslUpdateLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <SetupPrivate.h>

/**
  This function initializes the Acpi related setup option values

  @param[in] HiiHandle  HiiHandle Handle to HII database
  @param[in] Class      Indicates the setup class

**/
VOID
InitAcpiStrings (
  IN EFI_HII_HANDLE      HiiHandle,
  IN UINT16              Class
  )
{
  EFI_STATUS             Status;
  CHAR8                  *FadtVersionStr;
  UINTN                  VariableSize;
  UINT32                 VariableAttributes;

  DEBUG ((DEBUG_INFO, "<InitAcpiStrings>\n"));
  FadtVersionStr = "1.0";

  if (Class == ADVANCED_FORM_SET_CLASS) {
    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    &VariableAttributes,
                    &VariableSize,
                    &mSetupData
                    );
    if (EFI_ERROR (Status)) {
      return;
    }

    switch (mSetupData.AcpiTableRevision) {
      case EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION:
        FadtVersionStr = "2.0";
        break;
      case EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION:
        FadtVersionStr = "3.0";
        break;
      case EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION:
        FadtVersionStr = "5.0";
        break;
      case EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE_REVISION:
        FadtVersionStr = "6.1";
        break;
      default:
        break;
    }
  }

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_ACPI_VERSION_VALUE),
    L"%a",
    FadtVersionStr
  );

#ifdef ACPI_DEBUG_FLAG
  InitString (
    HiiHandle,
    STRING_TOKEN (STR_ACPI_DEBUG_ADDRESS_VALUE),
    L"0x%x",
    PcdGet32 (PcdAcpiDebugAddress)
  );
#endif //ACPI_DEBUG_FLAG
}

//
// Callback routine for LowPowerS0Idle Enable
//
EFI_STATUS
EFIAPI
LowPowerS0IdleEnableCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  SETUP_DATA              SetupData;
  UINTN                   VarSize;
  EFI_STATUS              Status;
  EFI_STRING              RequestString;

  RequestString = NULL;
  Status = EFI_SUCCESS;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  ASSERT (KeyValue == KEY_LOW_POWER_S0_IDLE);
  DEBUG ((DEBUG_INFO, "LowPowerS0IdleEnableCallback()\n"));

  VarSize = sizeof (SETUP_DATA);
  if (!HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status) && (SetupData.LowPowerS0Idle == 1)) {
    SetupData.OpRomPost = OPROM_EFI;
    SetupData.CsmControl = EFI_CSM_CONTROL_ALWAYS_OFF;
    SetupData.HidEventFilterDriverEnable = 1;
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, CsmControl), sizeof (SetupData.CsmControl));
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, OpRomPost), sizeof (SetupData.OpRomPost));
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, HidEventFilterDriverEnable), sizeof (SetupData.HidEventFilterDriverEnable));
    VarSize = sizeof (SETUP_DATA);
    if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData, RequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
  }

  return EFI_SUCCESS;
}
