/** @file
  Time Sensitive Network (TSN) GbE Setup Routines

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

typedef enum {
  PSE_GBE0 = 0,
  PSE_GBE1,
  MCC_GBE
} TSN_GBE_FIA_LANE_ARRAY_INDEX;

/**
  This function checks the link speed and lane assignments
  of TSN GBE ports. GBE Ports using the same PLL common lane must
  use the same link speed.

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
TsnGbeLinkSpeedCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  EFI_STATUS           Status;
  UINTN                VariableSize;
  UINT32               PchSetupSize;
  PCH_SETUP            *PchSetup;
  SETUP_VOLATILE_DATA  VolatileData;
  UINT32               SetupVolVarAttr;
  EFI_STRING           RequestString;

  DEBUG ((DEBUG_INFO, "TsnGbeLinkSpeedCallBack Start.\n"));

  RequestString = NULL;
  PchSetup      = NULL;

  ///
  /// No action to perform on Action Changing
  ///
  if (Action == EFI_BROWSER_ACTION_CHANGING) {
    return EFI_SUCCESS;
  }

  if (Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  VariableSize = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  &SetupVolVarAttr,
                  &VariableSize,
                  &VolatileData
                  );
  ASSERT_EFI_ERROR (Status);

  PchSetupSize  = sizeof (PCH_SETUP);
  PchSetup = AllocatePool (PchSetupSize);
  if (PchSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (!HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchSetupSize,  (UINT8 *) PchSetup)) {
    return EFI_NOT_FOUND;
  }

  switch (KeyValue) {
    case KEY_PSE_TSN_GBE0_LINK_SPEED:
      if (!PchSetup->PseTsnGbeSgmiiEnable[0]) {
        return EFI_SUCCESS;
      }

      if (VolatileData.TsnGbeLaneNum[PSE_GBE0] == PCH_PSE_TSN_GBE0_COM1_FIALANE) {
        if (VolatileData.TsnGbeLaneNum[PSE_GBE1] == PCH_PSE_TSN_GBE1_COM1_FIALANE && PchSetup->PseTsnGbeSgmiiEnable[1]) {
          PchSetup->PseTsnGbeLinkSpeed[1] = PchSetup->PseTsnGbeLinkSpeed[0];
        }
        if (VolatileData.TsnGbeLaneNum[MCC_GBE] == PCH_TSN_GBE_COM1_FIALANE && PchSetup->PchTsnGbeSgmiiEnable) {
          PchSetup->PchTsnGbeLinkSpeed = PchSetup->PseTsnGbeLinkSpeed[0];
        }
      }
      break;
    case KEY_PSE_TSN_GBE1_LINK_SPEED:
      if (!PchSetup->PseTsnGbeSgmiiEnable[1]) {
        return EFI_SUCCESS;
      }

      if (VolatileData.TsnGbeLaneNum[PSE_GBE1] == PCH_PSE_TSN_GBE1_COM1_FIALANE) {
        if (VolatileData.TsnGbeLaneNum[PSE_GBE0] == PCH_PSE_TSN_GBE0_COM1_FIALANE && PchSetup->PseTsnGbeSgmiiEnable[0]) {
          PchSetup->PseTsnGbeLinkSpeed[0] = PchSetup->PseTsnGbeLinkSpeed[1];
        }
        if (VolatileData.TsnGbeLaneNum[MCC_GBE] == PCH_TSN_GBE_COM1_FIALANE && PchSetup->PchTsnGbeSgmiiEnable) {
          PchSetup->PchTsnGbeLinkSpeed = PchSetup->PseTsnGbeLinkSpeed[1];
        }
      }

      if (VolatileData.TsnGbeLaneNum[PSE_GBE1] == PCH_PSE_TSN_GBE1_COM3_FIALANE) {
        if (VolatileData.TsnGbeLaneNum[MCC_GBE] == PCH_TSN_GBE_COM3_FIALANE && PchSetup->PchTsnGbeSgmiiEnable) {
          PchSetup->PchTsnGbeLinkSpeed = PchSetup->PseTsnGbeLinkSpeed[1];
        }
      }
      break;
    case KEY_MCC_TSN_GBE_LINK_SPEED:
      if (!PchSetup->PchTsnGbeSgmiiEnable) {
        return EFI_SUCCESS;
      }

      if (VolatileData.TsnGbeLaneNum[MCC_GBE] == PCH_TSN_GBE_COM1_FIALANE) {
        if (VolatileData.TsnGbeLaneNum[PSE_GBE0] == PCH_PSE_TSN_GBE0_COM1_FIALANE && PchSetup->PseTsnGbeSgmiiEnable[0]) {
          PchSetup->PseTsnGbeLinkSpeed[0] = PchSetup->PchTsnGbeLinkSpeed;
        }
        if (VolatileData.TsnGbeLaneNum[PSE_GBE1] == PCH_PSE_TSN_GBE1_COM1_FIALANE && PchSetup->PseTsnGbeSgmiiEnable[1]) {
          PchSetup->PseTsnGbeLinkSpeed[1] = PchSetup->PchTsnGbeLinkSpeed;
        }
      }

      if (VolatileData.TsnGbeLaneNum[MCC_GBE] == PCH_TSN_GBE_COM3_FIALANE) {
        if (VolatileData.TsnGbeLaneNum[PSE_GBE1] == PCH_PSE_TSN_GBE1_COM3_FIALANE && PchSetup->PseTsnGbeSgmiiEnable[1]) {
          PchSetup->PseTsnGbeLinkSpeed[1] = PchSetup->PchTsnGbeLinkSpeed;
        }
      }
      break;
    default:
      return EFI_UNSUPPORTED;
  }

  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PchTsnGbeLinkSpeed), sizeof (PchSetup->PchTsnGbeLinkSpeed));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PseTsnGbeLinkSpeed[0]), sizeof (PchSetup->PseTsnGbeLinkSpeed[0]));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (PCH_SETUP, PseTsnGbeLinkSpeed[1]), sizeof (PchSetup->PseTsnGbeLinkSpeed[1]));
  if (HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", PchSetupSize, (UINT8 *) PchSetup, RequestString)) {
    Status = EFI_NOT_FOUND;
  }
  FreePool (RequestString);

  if (PchSetup != NULL) {
    FreePool (PchSetup);
  }

  return Status;
}
