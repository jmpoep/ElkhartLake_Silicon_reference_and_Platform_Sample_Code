/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#include <SetupPrivate.h>
#include <Library/PchInfoLib.h>
#include <ConfigBlock.h>
#include <Ppi/SiPolicy.h>
#include <TraceHubConfig.h>

// Function Definitions

/**
  Initialize Debug strings.

  @param[in] EFI_HII_HANDLE   HiiHandle
  @param[in] UINT16           Class
**/
VOID
InitDebugStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  SI_SETUP                    SiSetup;
  UINTN                       SiVarSize;
  UINTN                       SaVarSize;
  UINT32                      SaVarAttr;
  UINTN                       PchVarSize;
  UINT32                      PchVarAttr;
  EFI_STATUS                  Status;

  SiVarSize = sizeof (SI_SETUP);
  Status = gRT->GetVariable (L"SiSetup", &gSiSetupVariableGuid, NULL, &SiVarSize, &SiSetup);
  if (EFI_ERROR (Status)) DEBUG ((DEBUG_ERROR, "Get SiSetup Fail. Status = %r\n", Status));
  //
  // Do NOT update options for PDC Manual
  //
  if (SiSetup.PlatformDebugConsent == ProbeTypeManual) {
    return;
  }

  PchVarSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (L"PchSetup", &gPchSetupVariableGuid, &PchVarAttr, &PchVarSize, &mPchSetup);
  if (EFI_ERROR (Status)) DEBUG ((DEBUG_ERROR, "Get PchSetup Fail. Status = %r\n", Status));

  SaVarSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (L"SaSetup", &gSaSetupVariableGuid, &SaVarAttr, &SaVarSize, &mSaSetup);
  if (EFI_ERROR (Status)) DEBUG ((DEBUG_ERROR, "Get SaSetup Fail. Status = %r\n", Status));

  if (Class == ADVANCED_FORM_SET_CLASS) {
    DEBUG ((DEBUG_INFO, "Init Debug defaults ()\n"));
    //
    // Common settings for PDC enabled
    //
    mPchSetup.DciEn                      = TRUE;
    mPchSetup.DciModphyPg                = TRUE;
    mPchSetup.DciDbcMode                 = DciDbcNoChange;
    mSaSetup.CpuTraceHubMode             = TraceHubModeHostDebugger;
    mPchSetup.PchTraceHubMode            = TraceHubModeHostDebugger;

    switch (SiSetup.PlatformDebugConsent) {
      case ProbeTypeDisabled:
        mPchSetup.DciEn                    = FALSE;
        mSaSetup.CpuTraceHubMode           = TraceHubModeDisabled;
        mPchSetup.PchTraceHubMode          = TraceHubModeDisabled;
        break;

      case ProbeTypeUsb2Dbc:
        mPchSetup.DciDbcMode               = DciDbcBoth;
        break;

      case ProbeTypeUsb3Dbc:
        mPchSetup.DciDbcMode               = DciDbcUsb3;
        break;

      case ProbeType2WireDciOob:
        mSaSetup.CpuTraceHubMode           = TraceHubModeDisabled;
        mPchSetup.PchTraceHubMode          = TraceHubModeDisabled;
        break;

      case ProbeTypeDciOob:
        mPchSetup.DciModphyPg              = FALSE;
        break;

      default:
        break;
    }
    Status = gRT->SetVariable (L"SaSetup", &gSaSetupVariableGuid, SaVarAttr, SaVarSize, &mSaSetup);
    if (EFI_ERROR (Status)) DEBUG ((DEBUG_ERROR, "Set SaSetup Fail. Status = %r\n", Status));

    Status = gRT->SetVariable (L"PchSetup", &gPchSetupVariableGuid, PchVarAttr, PchVarSize, &mPchSetup);
    if (EFI_ERROR (Status)) DEBUG ((DEBUG_ERROR, "Set PchSetup Fail. Status = %r\n", Status));
  }
}

/**
  Setup callback executed when user selects a Debug Enable from the BIOS UI.
  Changes visibility and settings of other options.

  @param[in] This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in] Action          Specifies the type of action taken by the browser.
  @param[in] KeyValue        A unique value which is sent to the original exporting driver
                             so that it can identify the type of data to expect.
  @param[in] Type            The type of value for the question.
  @param[in] Value           A pointer to the data being sent to the original exporting driver.
  @param[out] ActionRequest  On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS        The callback successfully handled the action
  @retval EFI_UNSUPPORTED    The specified action is not supported by the callback
**/
EFI_STATUS
EFIAPI
DebugFormCallBackFunction(
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  SI_SETUP                SiSetup;
  UINTN                   SiVarSize;
  PCH_SETUP               PchSetup;
  UINTN                   PchVarSize;
  EFI_STRING              PchRequestString;
  SA_SETUP                SaSetup;
  UINTN                   SaVarSize;
  EFI_STRING              SaRequestString;

  PchRequestString       = NULL;
  SaRequestString        = NULL;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  SiVarSize = sizeof (SI_SETUP);
  if (! HiiGetBrowserData (&gSiSetupVariableGuid, L"SiSetup", SiVarSize, (UINT8 *) &SiSetup)) {
    ASSERT (FALSE);
    return EFI_SUCCESS;
  }
  //
  // Do NOT update options for PDC Manual
  //
  if (SiSetup.PlatformDebugConsent == ProbeTypeManual) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "DebugFormCallBackFunction()\n"));
  PchVarSize = sizeof (PCH_SETUP);
  if (!HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchVarSize, (UINT8 *) &PchSetup)) {
    ASSERT (FALSE);
    return EFI_SUCCESS;
  }

  SaVarSize = sizeof (SA_SETUP);
  if (!HiiGetBrowserData (&gSaSetupVariableGuid, L"SaSetup", SaVarSize, (UINT8 *) &SaSetup)) {
    ASSERT (FALSE);
    return EFI_SUCCESS;
  }
  //
  // Common settings for PDC enabled/disabled
  //
  SaSetup.CpuTraceHubMemReg0Size      = TraceBuffer8M;
  SaSetup.CpuTraceHubMemReg1Size      = TraceBuffer8M;
  PchSetup.PchTraceHubMemReg0Size     = TraceBuffer8M;
  PchSetup.PchTraceHubMemReg1Size     = TraceBuffer8M;
  //
  // Common settings for PDC enabled
  //
  PchSetup.DciEn                      = TRUE;
  PchSetup.DciModphyPg                = TRUE;
  PchSetup.DciDbcMode                 = DciDbcNoChange;
  SaSetup.CpuTraceHubMode             = TraceHubModeHostDebugger;
  PchSetup.PchTraceHubMode            = TraceHubModeHostDebugger;

  switch (KeyValue) {
    case PLATFORM_DEBUG_CONSENT_KEY:
      switch (SiSetup.PlatformDebugConsent) {
        case ProbeTypeDisabled:
          PchSetup.DciEn                    = FALSE;
          SaSetup.CpuTraceHubMode           = TraceHubModeDisabled;
          PchSetup.PchTraceHubMode          = TraceHubModeDisabled;
          break;

        case ProbeTypeUsb2Dbc:
          PchSetup.DciDbcMode               = DciDbcBoth;
          break;

        case ProbeTypeUsb3Dbc:
          PchSetup.DciDbcMode               = DciDbcUsb3;
          break;

        case ProbeType2WireDciOob:
          SaSetup.CpuTraceHubMode           = TraceHubModeDisabled;
          PchSetup.PchTraceHubMode          = TraceHubModeDisabled;
          break;

        case ProbeTypeDciOob:
          PchSetup.DciModphyPg              = FALSE;
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, DciEn), sizeof (PchSetup.DciEn));
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, DciDbcMode), sizeof (PchSetup.DciDbcMode));
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, DciModphyPg), sizeof (PchSetup.DciModphyPg));
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, PchTraceHubMode), sizeof (PchSetup.PchTraceHubMode));
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, PchTraceHubMemReg0Size), sizeof (PchSetup.PchTraceHubMemReg0Size));
  PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, PchTraceHubMemReg1Size), sizeof (PchSetup.PchTraceHubMemReg1Size));
  if (PchRequestString != NULL) {
    if (!HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchVarSize, (UINT8 *) &PchSetup, PchRequestString)) {
      ASSERT (FALSE);
    }
    FreePool (PchRequestString);
  }
  SaRequestString = HiiConstructRequestString (SaRequestString, OFFSET_OF (SA_SETUP, CpuTraceHubMode), sizeof (SaSetup.CpuTraceHubMode));
  SaRequestString = HiiConstructRequestString (SaRequestString, OFFSET_OF (SA_SETUP, CpuTraceHubMemReg0Size), sizeof (SaSetup.CpuTraceHubMemReg0Size));
  SaRequestString = HiiConstructRequestString (SaRequestString, OFFSET_OF (SA_SETUP, CpuTraceHubMemReg1Size), sizeof (SaSetup.CpuTraceHubMemReg1Size));
  if (SaRequestString != NULL) {
    if (!HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", SaVarSize, (UINT8 *) &SaSetup, SaRequestString)) {
      ASSERT (FALSE);
    }
    FreePool (SaRequestString);
  }

  return EFI_SUCCESS;
}