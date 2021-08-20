/** @file
  Time Coordinated Computing (TCC) Setup Routines

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include "SetupPrivate.h"
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/HiiString.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/TccLib.h>
extern UINT8 AdvancedBin[];

/**
  This function looks for default value of question

  @param[in]  EFI_STRING_ID            QuestionStringId
  @param[out] UINT8                   *DefaultValue

  @retval EFI_SUCCESS        Call Back Function executed successfully
**/
EFI_STATUS
GetDefaultOneOfQuestionValue (
  EFI_STRING_ID       QuestionStringId,
  UINT8              *DefaultValue
  )
{
  EFI_HII_PACKAGE_HEADER *PackageHdr;
  CHAR8                  *BytePtr;
  EFI_IFR_OP_HEADER      *ParentIfr;
  EFI_IFR_DEFAULT        *DefaultPtr;
  EFI_IFR_ONE_OF_OPTION  *OptionPtr;
  UINTN                  PackageSize;
  EFI_IFR_ONE_OF         *OneOfPtr;

  //
  // add Array Length (UINT32) to point to package header.
  //
  PackageHdr = (EFI_HII_PACKAGE_HEADER *)(AdvancedBin + sizeof(UINT32));
  PackageSize = PackageHdr->Length;
  PackageSize = PackageSize & 0x00ffffff;
  BytePtr = (CHAR8 *) (PackageHdr + 1);

  //
  // loop to find one of op code with Question string id
  //
  while (TRUE) {
    if (BytePtr >= (CHAR8 *)PackageHdr + PackageSize) {
      DEBUG ((DEBUG_ERROR, "Couldn't find the target node to patch.\n"));
      return EFI_NOT_FOUND;
    }

    ParentIfr = (EFI_IFR_OP_HEADER *)BytePtr;
    if (ParentIfr->OpCode == EFI_IFR_ONE_OF_OP) {
      OneOfPtr = (EFI_IFR_ONE_OF *)ParentIfr;
      if(OneOfPtr->Question.Header.Prompt == QuestionStringId) {
        break;
      }
    }
    BytePtr += ParentIfr->Length;
  }

  //
  // advance to default OP code or default option.
  //
  while (TRUE) {
    if (BytePtr >= (CHAR8 *)PackageHdr + PackageSize) {
      DEBUG ((DEBUG_ERROR, "Couldn't find the target node to patch.\n"));
      return EFI_NOT_FOUND;
    }

    ParentIfr = (EFI_IFR_OP_HEADER *)BytePtr;
    if (ParentIfr->OpCode == EFI_IFR_DEFAULT_OP) {
      DefaultPtr = (EFI_IFR_DEFAULT *)ParentIfr;
      *DefaultValue = DefaultPtr->Value.u8;
      break;
    }

    if (ParentIfr->OpCode == EFI_IFR_ONE_OF_OPTION_OP) {
      OptionPtr = (EFI_IFR_ONE_OF_OPTION *) ParentIfr;
      if ((OptionPtr->Flags & EFI_IFR_OPTION_DEFAULT)  == EFI_IFR_OPTION_DEFAULT) {
        *DefaultValue = OptionPtr->Value.u8;
        break;
      }
    }

    BytePtr += ParentIfr->Length;
  }


  return EFI_SUCCESS;
}

/**
  This function sets CPU, PCH, and SA configuration
  base off TCC mode.

  @param[in] CPU_SETUP               *CpuSetup
  @param[in] PCH_SETUP               *PchSetup
  @param[in] SA_SETUP                *SaSetup
  @param[in] SETUP_DATA              *SetupData
**/
VOID
GetTccModeConfig (
  CPU_SETUP  *CpuSetup,
  PCH_SETUP  *PchSetup,
  SA_SETUP   *SaSetup,
  SETUP_DATA *SetupData
  )
{
  UINT8                 Index;
  UINT8                 MaxPchPciePorts;
  UINT8                 DefaultMultiVc;
  MaxPchPciePorts = GetPchMaxPciePortNum ();

  if (SetupData->TccMode == 1) {
    CpuSetup->EnableGv = 0;
    CpuSetup->EnableHwp = 0;
    CpuSetup->EnableCx = 0;
    CpuSetup->EnableItbm = 0;
    CpuSetup->AcSplitLock = 0;
    CpuSetup->VT = 1;

    PchSetup->PsfTccEnable = 1;
    PchSetup->PchDmiAspm = 0;
    PchSetup->PchLegacyIoLowLatency = 1;
    PchSetup->PchTsnGbeMultiVcEnable = 1;
    PchSetup->PseTsnGbeMultiVcEnable[0] = 1;
    PchSetup->PseTsnGbeMultiVcEnable[1] = 1;

    for (Index = 0; Index < MaxPchPciePorts; Index++) {
      PchSetup->PcieRootPortAspm[Index] = 0;
      PchSetup->PcieRootPortL1SubStates[Index] = 0;
      PchSetup->PcieRootPortPTM[Index] = 1;
      if (PchSetup->PcieRootPortMVCESupported[Index] == 1) {
        PchSetup->PcieRootPortMVCE[Index] = 1;
      }
    }

    SaSetup->SaGv = 0;
    SaSetup->PowerDownMode = 0;
    SaSetup->EnableRenderStandby = 0;
    SaSetup->DisPgCloseIdleTimeout = 1;
    SaSetup->RaplLim1Ena = 0;
    SaSetup->RaplLim2Ena = 0;
    SaSetup->PowerDownMode = 0;
    SaSetup->EnableRenderStandby = 0;
    SaSetup->PmSupport = 0;
    SaSetup->EnableVtd = 1;


    SetupData->Rtd3Support = 0;
    SetupData->LowPowerS0Idle = 0;
  } else {
        // Get Deafult values for TCC Mode Setting
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_CPU_IST_PROMPT), &CpuSetup->EnableGv);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_CPU_ISST_PROMPT), &CpuSetup->EnableHwp);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_CX_PROMPT), &CpuSetup->EnableCx);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_CPU_ITBM_PROMPT), &CpuSetup->EnableItbm);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_AC_SPLIT_LOCK_PROMPT), &CpuSetup->AcSplitLock);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_VT_PROMPT), &CpuSetup->VT);

    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PSF_TCC_PROMPT), &PchSetup->PsfTccEnable);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCH_DMI_ASPM_PROMPT), &PchSetup->PchDmiAspm);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCH_LEGACY_IO_LOW_LATENCY), &PchSetup->PchLegacyIoLowLatency);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCH_TSN_GBE_MULTI_VC), &PchSetup->PchTsnGbeMultiVcEnable);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PSE_TSN_GBE0_MULTI_VC), &PchSetup->PseTsnGbeMultiVcEnable[0]);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PSE_TSN_GBE1_MULTI_VC), &PchSetup->PseTsnGbeMultiVcEnable[1]);

    // Same Default value is used for all PCH PCIe RP
    if (MaxPchPciePorts > 0) {
      GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCH_PCIE_ASPM_PROMPT0), PchSetup->PcieRootPortAspm);
      GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCIE_L1SUB_PROMPT0), PchSetup->PcieRootPortL1SubStates);
      GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCIE_PTM_PROMPT0), PchSetup->PcieRootPortPTM);
      GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PCIE_MVCE_PROMPT0), &DefaultMultiVc);
      if (PchSetup->PcieRootPortMVCESupported[0] == 1) {
        PchSetup->PcieRootPortMVCE[0] = DefaultMultiVc;
      }
    }
    for (Index = 1; Index < MaxPchPciePorts; Index++) {
      PchSetup->PcieRootPortAspm[Index] = PchSetup->PcieRootPortAspm[0];
      PchSetup->PcieRootPortL1SubStates[Index] = PchSetup->PcieRootPortL1SubStates[0];
      PchSetup->PcieRootPortPTM[Index] = PchSetup->PcieRootPortPTM[0];
      if (PchSetup->PcieRootPortMVCESupported[Index] == 1) {
        PchSetup->PcieRootPortMVCE[Index] = DefaultMultiVc;
      }
    }

    GetDefaultOneOfQuestionValue (STRING_TOKEN (STR_SA_GV_PROMPT), &SaSetup->SaGv);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PAGE_IDLE_TIMEOUT_PROMPT), &SaSetup->DisPgCloseIdleTimeout);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_POWER_DOWN_MODE_PROMPT), &SaSetup->PowerDownMode);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_VIDEO_RS2_PROMPT), &SaSetup->EnableRenderStandby);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_PM_SUPPORT), &SaSetup->PmSupport);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_SA_VTD_PROMPT), &SaSetup->EnableVtd);


    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_RTD3), &SetupData->Rtd3Support);
    GetDefaultOneOfQuestionValue (STRING_TOKEN(STR_LOW_POWER_S0_IDLE), &SetupData->LowPowerS0Idle);
  }

}

/**
  This function toggles TCC mode on the platform by
  modifying CPU, SA, and PCH settings related with TCC.

  @param[in] EFI_HII_CONFIG_ACCESS_PROTOCOL   *This
  @param[in] EFI_BROWSER_ACTION               Action
  @param[in] EFI_QUESTION_ID                  KeyValue
  @param[in] UINT8                            Type
  @param[in] EFI_IFR_TYPE_VALUE               *Value
  @param[in] OUT EFI_BROWSER_ACTION_REQUEST   *ActionRequest

  @retval EFI_SUCCESS        Call Back Function executed successfully
**/
EFI_STATUS
EFIAPI
TccModeCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  CPU_SETUP               *CpuSetup;
  PCH_SETUP               *PchSetup;
  SA_SETUP                *SaSetup;
  SETUP_DATA              *SetupData;
  SYSTEM_ACCESS           *SystemAccess;
  UINTN                   CpuSetupSize;
  UINTN                   PchSetupSize;
  UINTN                   SaSetupSize;
  UINTN                   SetupDataSize;
  UINTN                   SystemAccessSize;
  EFI_STATUS              EfiStatus;
  BOOLEAN                 HiiStatus;
  EFI_STRING              RequestString;
  UINT8                   MaxPchPciePorts;
  UINT8                   Index;

  RequestString = NULL;
  CpuSetup = NULL;
  PchSetup = NULL;
  SaSetup = NULL;
  SetupData = NULL;
  SystemAccess = NULL;
  MaxPchPciePorts = GetPchMaxPciePortNum ();

  ///
  /// No action to perform on Action Changing
  ///
  if (Action == EFI_BROWSER_ACTION_CHANGING) {
    return EFI_SUCCESS;
  }

  if (Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  switch (KeyValue) {
    case KEY_TCC_MODE:
      CpuSetupSize     = sizeof (CPU_SETUP);
      PchSetupSize     = sizeof (PCH_SETUP);
      SaSetupSize      = sizeof (SA_SETUP);
      SetupDataSize    = sizeof (SETUP_DATA);
      SystemAccessSize = sizeof (SYSTEM_ACCESS);
      CpuSetup = AllocatePool (CpuSetupSize);
      if (CpuSetup == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        break;
      }
      PchSetup = AllocatePool (PchSetupSize);
      if (PchSetup == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        break;
      }
      SaSetup  = AllocatePool (SaSetupSize);
      if (SaSetup == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        break;
      }
      SetupData = AllocatePool (SetupDataSize);
      if (SetupData == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        break;
      }
      SystemAccess = AllocatePool (SystemAccessSize);
      if (SystemAccess == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        break;
      }

      ///
      /// GetBrowserData by VarStore Name (Setup)
      ///
      HiiStatus =  HiiGetBrowserData (&gCpuSetupVariableGuid, L"CpuSetup",     CpuSetupSize,     (UINT8 *) CpuSetup);
      HiiStatus &= HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup",     PchSetupSize,     (UINT8 *) PchSetup);
      HiiStatus &= HiiGetBrowserData (&gSaSetupVariableGuid,  L"SaSetup",      SaSetupSize,      (UINT8 *) SaSetup);
      HiiStatus &= HiiGetBrowserData (&gSetupVariableGuid,    L"Setup",        SetupDataSize,    (UINT8 *) SetupData);
      HiiStatus &= HiiGetBrowserData (&gSystemAccessGuid,     L"SystemAccess", SystemAccessSize, (UINT8 *) SystemAccess);
      if (HiiStatus != TRUE) {
        EfiStatus = EFI_NOT_FOUND;
        break;
      }

      GetTccModeConfig (CpuSetup, PchSetup, SaSetup, SetupData);

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, EnableGv), sizeof (CpuSetup->EnableGv));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, EnableHwp), sizeof (CpuSetup->EnableHwp));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, EnableCx), sizeof (CpuSetup->EnableCx));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, EnableItbm), sizeof (CpuSetup->EnableItbm));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, AcSplitLock), sizeof (CpuSetup->AcSplitLock));
      if (SystemAccess->Access != SYSTEM_PASSWORD_USER) {
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, VT), sizeof (CpuSetup->VT));
      }
      HiiStatus = HiiSetBrowserData (&gCpuSetupVariableGuid, L"CpuSetup", CpuSetupSize, (UINT8 *) CpuSetup, RequestString);
      FreePool (RequestString);
      RequestString = NULL;

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchDmiAspm), sizeof (PchSetup->PchDmiAspm));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchLegacyIoLowLatency), sizeof (PchSetup->PchLegacyIoLowLatency));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PsfTccEnable), sizeof (PchSetup->PsfTccEnable));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchTsnGbeMultiVcEnable), sizeof (PchSetup->PchTsnGbeMultiVcEnable));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PseTsnGbeMultiVcEnable[0]), sizeof (PchSetup->PseTsnGbeMultiVcEnable[0]));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PseTsnGbeMultiVcEnable[1]), sizeof (PchSetup->PseTsnGbeMultiVcEnable[1]));
      for (Index = 0; Index < MaxPchPciePorts; Index++) {
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PcieRootPortAspm[Index]), sizeof (PchSetup->PcieRootPortAspm[Index]));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PcieRootPortL1SubStates[Index]), sizeof (PchSetup->PcieRootPortL1SubStates[Index]));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PcieRootPortMVCE[Index]), sizeof (PchSetup->PcieRootPortMVCE[Index]));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PcieRootPortPTM[Index]), sizeof (PchSetup->PcieRootPortPTM[Index]));
      }
      HiiStatus = HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchSetupSize, (UINT8 *) PchSetup, RequestString);
      FreePool (RequestString);
      RequestString = NULL;

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, SaGv), sizeof (SaSetup->SaGv));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, PowerDownMode), sizeof (SaSetup->PowerDownMode));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, EnableRenderStandby), sizeof (SaSetup->EnableRenderStandby));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, DisPgCloseIdleTimeout), sizeof (SaSetup->DisPgCloseIdleTimeout));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, RaplLim1Ena), sizeof (SaSetup->RaplLim1Ena));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, RaplLim2Ena), sizeof (SaSetup->RaplLim2Ena));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, PowerDownMode), sizeof (SaSetup->PowerDownMode));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, EnableRenderStandby), sizeof (SaSetup->EnableRenderStandby));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, PmSupport), sizeof (SaSetup->PmSupport));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, EnableVtd), sizeof (SaSetup->EnableVtd));
      HiiStatus = HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", SaSetupSize, (UINT8 *) SaSetup, RequestString);
      FreePool (RequestString);
      RequestString = NULL;

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, Rtd3Support), sizeof (SetupData->Rtd3Support));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, LowPowerS0Idle), sizeof (SetupData->LowPowerS0Idle));
      HiiStatus = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", SetupDataSize, (UINT8 *) SetupData, RequestString);
      FreePool (RequestString);
      RequestString = NULL;

      EfiStatus = EFI_SUCCESS;
      break;
    default:
      EfiStatus = EFI_UNSUPPORTED;
  }

  if (CpuSetup != NULL) {
    FreePool (CpuSetup);
  }
  if (PchSetup != NULL) {
    FreePool (PchSetup);
  }
  if (SaSetup != NULL) {
    FreePool (SaSetup);
  }
  if (SetupData != NULL) {
    FreePool (SetupData);
  }
  if (SystemAccess != NULL) {
    FreePool (SystemAccess);
  }

  return EfiStatus;
}
