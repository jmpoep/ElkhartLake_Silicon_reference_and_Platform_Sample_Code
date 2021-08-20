/** @file
  Connectivity Setup Routines

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/CnviLib.h>

BOOLEAN mCnviIsPresent;

/**
  Initialize Platform Strings

  @param[in] HiiHandle    HiiHandle Handle to HII database
  @param[in] Class        Indicates the setup class
**/
VOID
InitConnectivityStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{

  mCnviIsPresent = CnviIsPresent ();
  if (mCnviIsPresent) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_CNVI_CURRENT_STATE),
      L"%a",
      "Yes"
      );
  } else {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_CNVI_CURRENT_STATE),
      L"%a",
      "No"
      );
  }
}

/**
  Setup callback executed when user selects a Connectivity from the BIOS UI.
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
CnvFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  PCH_SETUP  PchSetup;
  UINTN      PchVarSize;
  SETUP_DATA SetupData;
  UINTN      VarSize;
  EFI_STRING RequestString;
  EFI_STATUS Status;

  RequestString = NULL;
  Status = EFI_SUCCESS;

  if ((Action != EFI_BROWSER_ACTION_CHANGING) && (Action != EFI_BROWSER_ACTION_CHANGED)) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "CnvFormCallBackFunction ()\n"));
  PchVarSize = sizeof (PCH_SETUP);
  if (!HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchVarSize, (UINT8 *) &PchSetup)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);
  VarSize = sizeof (SETUP_DATA);
  if (!HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  switch (KeyValue) {
    case KEY_CNV_BT_AUDIO_OFFLOAD:
      if (mCnviIsPresent && PchSetup.CnviBtCore) {
        switch (PchSetup.CnviBtAudioOffload) {
          case 1: // BT Audio Offload Enabled
            // Audio DSP NHLT Endpoints Configuration - Bluetooth
            PchSetup.PchHdAudioNhltEndpointBluetooth = TRUE;
            // BT Sideband support
            PchSetup.PchHdAudioFeature[1] = TRUE;
            // BT Intel HFP SCO
            PchSetup.PchHdAudioFeature[5] = TRUE;
            // BT Intel A2DP
            PchSetup.PchHdAudioFeature[6] = TRUE;
            break;
          case 0:  // BT Audio Offload Disabled
            // Audio DSP NHLT Endpoints Configuration - Bluetooth
            PchSetup.PchHdAudioNhltEndpointBluetooth = FALSE;
            // BT Sideband support
            PchSetup.PchHdAudioFeature[1] = FALSE;
            // BT Intel HFP SCO
            PchSetup.PchHdAudioFeature[5] = FALSE;
            // BT Intel A2DP
            PchSetup.PchHdAudioFeature[6] = FALSE;
            break;
          default:
            break;
        }
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchHdAudioNhltEndpointBluetooth), sizeof (PchSetup.PchHdAudioNhltEndpointBluetooth));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchHdAudioFeature[1]), sizeof (PchSetup.PchHdAudioFeature[1]));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchHdAudioFeature[5]), sizeof (PchSetup.PchHdAudioFeature[5]));
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchHdAudioFeature[6]), sizeof (PchSetup.PchHdAudioFeature[6]));
      }
      break;
    default:
      break;
  }

  if (RequestString != NULL) {
    if (!HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchVarSize, (UINT8 *) &PchSetup, RequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
  }

  if ((SetupData.WifiPowerLimit1 > 10000) && (SetupData.WifiPowerLimit1 < 0xFFFF)) {
    SetupData.WifiPowerLimit1 = 0xFFFF;
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, WifiPowerLimit1), sizeof (SetupData.WifiPowerLimit1));
    if (RequestString != NULL) {
      if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData, RequestString)) {
        Status = EFI_NOT_FOUND;
      }
      ASSERT_EFI_ERROR (Status);
      FreePool (RequestString);
    }
  }

  return EFI_SUCCESS;
}