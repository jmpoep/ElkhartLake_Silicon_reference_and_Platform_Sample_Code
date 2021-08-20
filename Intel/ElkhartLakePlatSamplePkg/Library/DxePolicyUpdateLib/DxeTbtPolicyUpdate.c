/** @file
  This file is the library for TBT DXE Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <DxeTbtPolicyUpdate.h>

/**
  Get data for platform policy from setup options.

  @param[in] ITbtPolicy                The pointer to get ITBT Policy protocol instance

  @retval EFI_SUCCESS                  Operation success.

**/
EFI_STATUS
EFIAPI
UpdateDxeTbtPolicy (
  IN OUT  ITBT_POLICY_PROTOCOL   *ITbtPolicy
  )
{
  EFI_STATUS                     Status;
  UINTN                          DataSize;
  SETUP_DATA                     SetupData;
  UINT8                          Index;
  DXE_ITBT_CONFIG                *DxeITbtConfig;
  DXE_DTBT_POLICY_PROTOCOL       *DxeDTbtConfig;

  DxeITbtConfig = NULL;
  DxeDTbtConfig = NULL;
  Status = EFI_NOT_FOUND;
  DEBUG ((DEBUG_INFO, "UpdateTbtPolicyCallback\n"));

  DataSize = sizeof (SetupData);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &DataSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR(Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)ITbtPolicy, &gDxeITbtConfigGuid, (VOID *)&DxeITbtConfig);
  Status = gBS->LocateProtocol (
                &gDxeDTbtPolicyProtocolGuid,
                NULL,
                (VOID **) &DxeDTbtConfig
                );

  if (DxeDTbtConfig == NULL) {
    DEBUG ((DEBUG_ERROR, " DxeITbtConfig is not created!!!\n"));
  } else {
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieExtraBusRsvd   = SetupData.DTbtPcieExtraBusRsvd[Index];
      DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieMemRsvd        = SetupData.DTbtPcieMemRsvd[Index];
      DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieMemAddrRngMax  = SetupData.DTbtPcieMemAddrRngMax[Index];
      DxeDTbtConfig->DTbtResourceConfig[Index].TbtPciePMemRsvd       = SetupData.DTbtPciePMemRsvd[Index];
      DxeDTbtConfig->DTbtResourceConfig[Index].TbtPciePMemAddrRngMax = SetupData.DTbtPciePMemAddrRngMax[Index];
    }
    DxeDTbtConfig->TbtCommonConfig.TbtAspm            = SetupData.TbtAspm;
    DxeDTbtConfig->TbtCommonConfig.TbtL1SubStates     = SetupData.TbtL1SubStates;
    DxeDTbtConfig->TbtCommonConfig.TbtHotNotify       = SetupData.TBTHotNotify;
    DxeDTbtConfig->TbtCommonConfig.TbtHotSMI          = SetupData.TBTHotSMI;
    DxeDTbtConfig->TbtCommonConfig.TbtLtr             = SetupData.TbtLtr;
    DxeDTbtConfig->TbtCommonConfig.TbtPtm             = SetupData.TbtPtm;
    DxeDTbtConfig->TbtCommonConfig.TbtSetClkReq       = SetupData.TBTSetClkReq;
    DxeDTbtConfig->TbtCommonConfig.TbtVtdBaseSecurity = SetupData.TbtVtdBaseSecurity;
    DxeDTbtConfig->DTbtGenericConfig.TbtWakeupSupport = SetupData.TbtWakeupSupport;
    DxeDTbtConfig->DTbtGenericConfig.SecurityMode     = SetupData.SecurityMode;
    DxeDTbtConfig->DTbtGenericConfig.Gpio5Filter      = SetupData.Gpio5Filter;
    DxeDTbtConfig->DTbtGenericConfig.TrA0OsupWa       = SetupData.TrOsup;
    DxeDTbtConfig->DTbtGenericConfig.TbtAcDcSwitch    = SetupData.TbtAcDcSwitch;
  }

  DTbtPrintDxePolicyConfig();
  if (DxeITbtConfig == NULL) {
    DEBUG ((DEBUG_ERROR, " DxeITbtConfig is not created!!!\n"));
  } else {
    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieExtraBusRsvd   = SetupData.ITbtPcieExtraBusRsvd[Index];
      DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemRsvd        = SetupData.ITbtPcieMemRsvd[Index];
      DxeITbtConfig->ITbtResourceConfig[Index].TbtPcieMemAddrRngMax  = SetupData.ITbtPcieMemAddrRngMax[Index];
      DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemRsvd       = SetupData.ITbtPciePMemRsvd[Index];
      DxeITbtConfig->ITbtResourceConfig[Index].TbtPciePMemAddrRngMax = SetupData.ITbtPciePMemAddrRngMax[Index];
    }
    DxeITbtConfig->TbtCommonConfig.TbtAspm              = SetupData.TbtAspm;
    DxeITbtConfig->TbtCommonConfig.TbtL1SubStates       = SetupData.TbtL1SubStates;
    DxeITbtConfig->TbtCommonConfig.TbtHotNotify         = SetupData.TBTHotNotify;
    DxeITbtConfig->TbtCommonConfig.TbtHotSMI            = SetupData.TBTHotSMI;
    DxeITbtConfig->TbtCommonConfig.TbtLtr               = SetupData.TbtLtr;
    DxeITbtConfig->TbtCommonConfig.TbtPtm               = SetupData.TbtPtm;
    DxeITbtConfig->TbtCommonConfig.TbtSetClkReq         = SetupData.TBTSetClkReq;
    DxeITbtConfig->TbtCommonConfig.TbtVtdBaseSecurity   = SetupData.TbtVtdBaseSecurity;
    DxeITbtConfig->ITbtGenericConfig.ITbtRtd3           = SetupData.ITbtRtd3;
    DxeITbtConfig->ITbtGenericConfig.ITbtRtd3ExitDelay  = SetupData.ITbtRtd3ExitDelay;
    DxeITbtConfig->OsNativeResourceBalance              = SetupData.OsNativeResourceBalance;
  }

  return EFI_SUCCESS;
}

