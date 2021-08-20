/** @file
  The driver is to create and publish the Connectivity UEFI variables.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "CnvUefiVariables.h"

/**
  Initialize Connectivity Conigurations

  @param[in, out] CnvConfig               Pointer to Connectivity Conigurations
  @param[in]      SystemConfiguration     Pointer to Setup data

**/
VOID
CnvConfigInit (
  IN OUT UEFI_CNV_CONFIG        *CnvConfig,
  IN SETUP_DATA                 *SystemConfiguration
  )
{
  if (SystemConfiguration != NULL) {
    CnvConfig->WifiDomainType1                    = SystemConfiguration->WifiDomainType1;
    CnvConfig->WifiPowerLimit1                    = SystemConfiguration->WifiPowerLimit1;
    CnvConfig->WifiTimeWindow1                    = SystemConfiguration->WifiTimeWindow1;

    CnvConfig->TRxDelay0                          = SystemConfiguration->TRxDelay0;
    CnvConfig->TRxCableLength0                    = SystemConfiguration->TRxCableLength0;
    CnvConfig->TRxDelay1                          = SystemConfiguration->TRxDelay1;
    CnvConfig->TRxCableLength1                    = SystemConfiguration->TRxCableLength1;

    CnvConfig->WrddDomainType1                    = SystemConfiguration->WrddDomainType1;
    CnvConfig->WrddCountryIndentifier1            = SystemConfiguration->WrddCountryIndentifier1;

    CnvConfig->WrdsWiFiSarEnable                  = SystemConfiguration->WrdsWiFiSarEnable;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit1       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit1;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit2       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit2;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit3       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit3;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit4       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit4;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit5       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit5;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit6       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit6;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit7       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit7;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit8       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit8;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit9       = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit9;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit10      = SystemConfiguration->WrdsWiFiSarTxPowerSet1Limit10;

    CnvConfig->EwrdWiFiDynamicSarEnable           = SystemConfiguration->EwrdWiFiDynamicSarEnable;
    CnvConfig->EwrdWiFiDynamicSarRangeSets        = SystemConfiguration->EwrdWiFiDynamicSarRangeSets;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit1       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit1;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit2       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit2;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit3       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit3;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit4       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit4;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit5       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit5;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit6       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit6;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit7       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit7;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit8       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit8;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit9       = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit9;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit10      = SystemConfiguration->EwrdWiFiSarTxPowerSet2Limit10;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit1       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit1;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit2       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit2;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit3       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit3;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit4       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit4;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit5       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit5;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit6       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit6;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit7       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit7;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit8       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit8;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit9       = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit9;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit10      = SystemConfiguration->EwrdWiFiSarTxPowerSet3Limit10;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit1       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit1;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit2       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit2;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit3       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit3;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit4       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit4;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit5       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit5;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit6       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit6;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit7       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit7;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit8       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit8;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit9       = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit9;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit10      = SystemConfiguration->EwrdWiFiSarTxPowerSet4Limit10;

    CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax1    = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerMax1;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA1 = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerChainA1;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB1 = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerChainB1;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax2    = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerMax2;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA2 = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerChainA2;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB2 = SystemConfiguration->WgdsWiFiSarDeltaGroup1PowerChainB2;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax1    = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerMax1;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA1 = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerChainA1;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB1 = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerChainB1;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax2    = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerMax2;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA2 = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerChainA2;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB2 = SystemConfiguration->WgdsWiFiSarDeltaGroup2PowerChainB2;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax1    = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerMax1;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA1 = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerChainA1;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB1 = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerChainB1;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax2    = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerMax2;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA2 = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerChainA2;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB2 = SystemConfiguration->WgdsWiFiSarDeltaGroup3PowerChainB2;

    CnvConfig->AntennaDiversity                   = SystemConfiguration->AntennaDiversity;

    CnvConfig->Enable                             = SystemConfiguration->BluetoothSar;
    CnvConfig->BluetoothSarBr                     = SystemConfiguration->BluetoothSarBr;
    CnvConfig->BluetoothSarEdr2                   = SystemConfiguration->BluetoothSarEdr2;
    CnvConfig->BluetoothSarEdr3                   = SystemConfiguration->BluetoothSarEdr3;
    CnvConfig->BluetoothSarLe                     = SystemConfiguration->BluetoothSarLe;
    CnvConfig->BluetoothSarLe2Mhz                 = SystemConfiguration->BluetoothSarLe2Mhz;
    CnvConfig->BluetoothSarLeLr                   = SystemConfiguration->BluetoothSarLeLr;
  } else {
    CnvConfig->WifiDomainType1                    = 0x07;
    CnvConfig->WifiPowerLimit1                    = 2000;
    CnvConfig->WifiTimeWindow1                    = 30000;

    CnvConfig->TRxDelay0                          = 50;
    CnvConfig->TRxCableLength0                    = 50;
    CnvConfig->TRxDelay1                          = 50;
    CnvConfig->TRxCableLength1                    = 50;

    CnvConfig->WrddDomainType1                    = 0x7;
    CnvConfig->WrddCountryIndentifier1            = 0x4150;

    CnvConfig->WrdsWiFiSarEnable                  = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit1       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit2       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit3       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit4       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit5       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit6       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit7       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit8       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit9       = 0;
    CnvConfig->WrdsWiFiSarTxPowerSet1Limit10      = 0;

    CnvConfig->EwrdWiFiDynamicSarEnable           = 0;
    CnvConfig->EwrdWiFiDynamicSarRangeSets        = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit1       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit2       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit3       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit4       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit5       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit6       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit7       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit8       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit9       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet2Limit10      = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit1       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit2       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit3       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit4       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit5       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit6       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit7       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit8       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit9       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet3Limit10      = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit1       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit2       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit3       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit4       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit5       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit6       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit7       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit8       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit9       = 0;
    CnvConfig->EwrdWiFiSarTxPowerSet4Limit10      = 0;

    CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax1    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax2    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA2 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB2 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax1    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax2    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA2 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB2 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax1    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB1 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax2    = 0xFF;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA2 = 0;
    CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB2 = 0;

    CnvConfig->AntennaDiversity                   = 0x2;

    CnvConfig->Enable                             = 0;
    CnvConfig->BluetoothSarBr                     = 0;
    CnvConfig->BluetoothSarEdr2                   = 0;
    CnvConfig->BluetoothSarEdr3                   = 0;
    CnvConfig->BluetoothSarLe                     = 0;
    CnvConfig->BluetoothSarLe2Mhz                 = 0;
    CnvConfig->BluetoothSarLeLr                   = 0;
  }
}

/**
  Update/Create Connectivity UEFI variable

  @param[in] CnvVarSize      Connectivity variable size
  @param[in] VariableName    Pointer to variable name
  @param[in] VendorGuid      Pointer to variable vendor guid
  @param[in] NewData         Pointer to variable data

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
UpdateVariables (
  IN UINTN                       CnvVarSize,
  IN CHAR16                     *VariableName,
  IN EFI_GUID                   *VendorGuid,
  IN VOID                       *NewData
  )
{
  EDKII_VARIABLE_LOCK_PROTOCOL  *VariableLock;
  EFI_STATUS                     Status;
  UINTN                          VarSize;
  VOID                          *OldData;
  BOOLEAN                        NeedUpdate;

  OldData       = NULL;
  NeedUpdate    = FALSE;

  VarSize = CnvVarSize;
  OldData = AllocateZeroPool (VarSize);
  if (OldData == NULL) {
    ASSERT (OldData);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Get Variable to know whether variable is already created or not
  //
  Status = gRT->GetVariable (
                  VariableName,
                  VendorGuid,
                  NULL,
                  &VarSize,
                  OldData
                  );

  if (Status == EFI_NOT_FOUND) {
    Status = EFI_SUCCESS;
    NeedUpdate = TRUE;
  }

  //
  // Update the variable if the variable has not been created yet or has been changed.
  //
  if (!EFI_ERROR (Status)) {
    if (NeedUpdate == FALSE) {
      if (CompareMem (OldData, NewData, VarSize)) {
        if (VarSize == CnvVarSize) {
          NeedUpdate = TRUE;
        } else {
          FreePool(OldData);
          return EFI_INVALID_PARAMETER;
        }
      }
    }

    if (NeedUpdate) {
      Status = gRT->SetVariable (
                      VariableName,
                      VendorGuid,
                      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                      VarSize,
                      NewData
                      );
    }
  }

  if (EFI_ERROR (Status)) {
    FreePool(OldData);
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  //
  // Lock CNV variables
  //
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, VariableName, VendorGuid);
  }

  FreePool(OldData);
  ASSERT (!EFI_ERROR (Status));

  return Status;
}

/**
  Install SPLC for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallSplc (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_SPLC                 SplcVarWifi;
  EFI_STATUS                        Status;

  SplcVarWifi.Header.Revision  = UEFI_CNV_SPLC_REVISION;

  switch (CnvConfig->WifiDomainType1) {
    case WIFI_DOMAIN_VALUE:
      SplcVarWifi.DefaultPowerLimit   = CnvConfig->WifiPowerLimit1;
      SplcVarWifi.DefaultTimeWindow   = CnvConfig->WifiTimeWindow1;
      break;
    default:
      break;
  }

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_SPLC),
             UEFI_CNV_SPLC_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &SplcVarWifi
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  return Status;
}

/**
  Install WAND for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallWand (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_WAND                 WandVar;
  EFI_STATUS                        Status;

  WandVar.Header.Revision                 = UEFI_CNV_WAND_REVISION;
  WandVar.AntDiversity[0].TxRxDelay       = CnvConfig->TRxDelay0;
  WandVar.AntDiversity[0].TxRxCableLength = CnvConfig->TRxCableLength0;
  WandVar.AntDiversity[1].TxRxDelay       = CnvConfig->TRxDelay1;
  WandVar.AntDiversity[1].TxRxCableLength = CnvConfig->TRxCableLength1;

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_WAND),
             UEFI_CNV_WAND_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &WandVar
             );
  ASSERT (!EFI_ERROR (Status));

  return Status;
}

/**
  Install WRDD for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallWrdd (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_WRDD                 WrddVarWifi;
  EFI_STATUS                        Status;

  WrddVarWifi.Header.Revision  = UEFI_CNV_WRDD_REVISION;

  switch (CnvConfig->WrddDomainType1) {
    case WIFI_DOMAIN_VALUE:
      WrddVarWifi.RegulatoryDomain  = CnvConfig->WrddCountryIndentifier1;
      break;
    default:
      break;
  }

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_WRDD),
             UEFI_CNV_WRDD_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &WrddVarWifi
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  return Status;
}

/**
  Install WRDS for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallWrds (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_WRDS_WIFI_SAR        WrdsVarWifi;
  EFI_STATUS                        Status;

  WrdsVarWifi.Header.Revision                              = UEFI_CNV_WRDS_REVISION;
  WrdsVarWifi.Enable                                       = CnvConfig->WrdsWiFiSarEnable;
  WrdsVarWifi.SarValues.ChainATxPowerLimits.From2400       = CnvConfig->WrdsWiFiSarTxPowerSet1Limit1;
  WrdsVarWifi.SarValues.ChainATxPowerLimits.From5150To5350 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit2;
  WrdsVarWifi.SarValues.ChainATxPowerLimits.From5350To5470 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit3;
  WrdsVarWifi.SarValues.ChainATxPowerLimits.From5470To5725 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit4;
  WrdsVarWifi.SarValues.ChainATxPowerLimits.From5725To5950 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit5;
  WrdsVarWifi.SarValues.ChainBTxPowerLimits.From2400       = CnvConfig->WrdsWiFiSarTxPowerSet1Limit6;
  WrdsVarWifi.SarValues.ChainBTxPowerLimits.From5150To5350 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit7;
  WrdsVarWifi.SarValues.ChainBTxPowerLimits.From5350To5470 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit8;
  WrdsVarWifi.SarValues.ChainBTxPowerLimits.From5470To5725 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit9;
  WrdsVarWifi.SarValues.ChainBTxPowerLimits.From5725To5950 = CnvConfig->WrdsWiFiSarTxPowerSet1Limit10;

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_WRDS_WIFI_SAR),
             UEFI_CNV_WRDS_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &WrdsVarWifi
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  return Status;
}

/**
  Install BRDS for BT

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallBrds (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_BRDS                 BrdsVar;
  EFI_STATUS                        Status;

  BrdsVar.Header.Revision  = UEFI_CNV_BRDS_REVISION;
  BrdsVar.Enable           = CnvConfig->Enable;
  BrdsVar.BrModulation     = CnvConfig->BluetoothSarBr;
  BrdsVar.Edr2Modulation   = CnvConfig->BluetoothSarEdr2;
  BrdsVar.Edr3Modulation   = CnvConfig->BluetoothSarEdr3;
  BrdsVar.LeModulation     = CnvConfig->BluetoothSarLe;
  BrdsVar.Le2MhzModulation = CnvConfig->BluetoothSarLe2Mhz;
  BrdsVar.LeLrModulation   = CnvConfig->BluetoothSarLeLr;

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_BRDS),
             UEFI_CNV_BRDS_VAR_NAME,
             &gUefiIntelCnvBtVariablesGuid,
             (VOID *) &BrdsVar
             );
  ASSERT (!EFI_ERROR (Status));

  return Status;
}

/**
  Install EWRD for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallEwrd (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_EWRD                 EwrdVar;
  EFI_STATUS                        Status;

  EwrdVar.Header.Revision                                               = UEFI_CNV_EWRD_REVISION;
  EwrdVar.WifiDynamicSarEnable                                          = CnvConfig->EwrdWiFiDynamicSarEnable;
  EwrdVar.WifiDynamicSarRangeSets                                       = CnvConfig->EwrdWiFiDynamicSarRangeSets;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainATxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet2Limit1;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainATxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit2;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainATxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit3;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainATxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit4;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainATxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit5;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainBTxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet2Limit6;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainBTxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit7;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainBTxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit8;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainBTxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit9;
  EwrdVar.WifiDynamicSarValuesExt[0].ChainBTxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet2Limit10;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainATxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet3Limit1;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainATxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit2;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainATxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit3;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainATxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit4;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainATxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit5;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainBTxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet3Limit6;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainBTxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit7;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainBTxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit8;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainBTxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit9;
  EwrdVar.WifiDynamicSarValuesExt[1].ChainBTxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet3Limit10;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainATxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet4Limit1;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainATxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit2;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainATxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit3;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainATxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit4;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainATxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit5;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainBTxPowerLimits.From2400       = CnvConfig->EwrdWiFiSarTxPowerSet4Limit6;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainBTxPowerLimits.From5150To5350 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit7;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainBTxPowerLimits.From5350To5470 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit8;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainBTxPowerLimits.From5470To5725 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit9;
  EwrdVar.WifiDynamicSarValuesExt[2].ChainBTxPowerLimits.From5725To5950 = CnvConfig->EwrdWiFiSarTxPowerSet4Limit10;

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_EWRD),
             UEFI_CNV_EWRD_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &EwrdVar
             );
  ASSERT (!EFI_ERROR (Status));

  return Status;
}

/**
  Install WGDS for WiFi

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallWgds (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_WGDS                 WgdsVar;
  EFI_STATUS                        Status;

  WgdsVar.Header.Revision                                     = UEFI_CNV_WGDS_REVISION;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset2400Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax1;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset2400Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA1;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset2400Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB1;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset5200Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup1PowerMax2;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset5200Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainA2;
  WgdsVar.WifiSarPowerDelta[0].GeoSarOffset5200Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup1PowerChainB2;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset2400Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax1;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset2400Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA1;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset2400Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB1;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset5200Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup2PowerMax2;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset5200Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainA2;
  WgdsVar.WifiSarPowerDelta[1].GeoSarOffset5200Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup2PowerChainB2;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset2400Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax1;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset2400Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA1;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset2400Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB1;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset5200Mhz.MaxAllowed = CnvConfig->WgdsWiFiSarDeltaGroup3PowerMax2;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset5200Mhz.ChainA     = CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainA2;
  WgdsVar.WifiSarPowerDelta[2].GeoSarOffset5200Mhz.ChainB     = CnvConfig->WgdsWiFiSarDeltaGroup3PowerChainB2;

  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_WGDS),
             UEFI_CNV_WGDS_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &WgdsVar
             );
  ASSERT (!EFI_ERROR (Status));

  return Status;
}


/**
  Install SADS for WiFi, BT

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallSads (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_SADS                 SadsVar;
  EFI_STATUS                        Status;

  SadsVar.Header.Revision = UEFI_CNV_SADS_REVISION;
  SadsVar.AntDiversitySel = CnvConfig->AntennaDiversity;

  //
  // Update SADS for WiFi GUID
  //
  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_SADS),
             UEFI_CNV_SADS_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &SadsVar
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  //
  // Update SADS for BT GUID
  //
  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_SADS),
             UEFI_CNV_SADS_VAR_NAME,
             &gUefiIntelCnvBtVariablesGuid,
             (VOID *) &SadsVar
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  return Status;
}

/**
  Install GPC for WiFi, BT

  @param[in] CnvConfig       Pointer to Connectivity Conigurations

  @retval EFI_SUCCESS        The function completed successfully

**/
EFI_STATUS
InstallGpc (
  IN UEFI_CNV_CONFIG               *CnvConfig
  )
{
  UEFI_CNV_VAR_GPC                  GpcVar;
  EFI_STATUS                        Status;

  GpcVar.Header.Revision = UEFI_CNV_GPC_REVISION;

  //
  // End of TLV
  //
  GpcVar.Tlv[UEFI_CNV_GPC_TLV_MAX_WIFI_BT_CORE - 1].Type     = 0;
  GpcVar.Tlv[UEFI_CNV_GPC_TLV_MAX_WIFI_BT_CORE - 1].Length   = 0;
  GpcVar.Tlv[UEFI_CNV_GPC_TLV_MAX_WIFI_BT_CORE - 1].Value[0] = 0;

  //
  // Update GPC for WiFi GUID
  //
  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_GPC),
             UEFI_CNV_GPC_VAR_NAME,
             &gUefiIntelCnvWlanVariablesGuid,
             (VOID *) &GpcVar
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  //
  // Update GPC for BT GUID
  //
  Status = UpdateVariables (
             sizeof (UEFI_CNV_VAR_GPC),
             UEFI_CNV_GPC_VAR_NAME,
             &gUefiIntelCnvBtVariablesGuid,
             (VOID *) &GpcVar
             );
  if (EFI_ERROR (Status)) {
    ASSERT (!EFI_ERROR (Status));
    return Status;
  }

  return Status;
}

/**
  Entry point of the CNV UEFI Variables driver.

  @param[in] ImageHandle     Handle for this drivers loaded image protocol.
  @param[in] SystemTable     EFI system table.

  @retval EFI_SUCCESS        The driver installed without error.
  @retval EFI_ABORTED        The driver encountered an error and could not create/update
                             the CNV UEFI Variables completely.

**/
EFI_STATUS
EFIAPI
CnvUefiVariables (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE                    Handle;
  EFI_STATUS                    Status;
  UINTN                         VarDataSize;
  UEFI_CNV_CONFIG               CnvConfig;
  SETUP_DATA                    SystemConfiguration;


  DEBUG ((DEBUG_INFO, "CnvUefiVariables entry\n"));

  Handle = NULL;
  ZeroMem ((VOID *) &CnvConfig, sizeof (UEFI_CNV_CONFIG));
  ZeroMem ((VOID *) &SystemConfiguration, sizeof (SETUP_DATA));

  VarDataSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &SystemConfiguration
                  );
  if (!EFI_ERROR (Status)) {
    CnvConfigInit (&CnvConfig, &SystemConfiguration);
  } else {
    CnvConfigInit (&CnvConfig, NULL);
  }

  Status = InstallSplc (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallWand (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallWrdd (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallWrds (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallBrds (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallEwrd (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallWgds (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallSads (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = InstallGpc (&CnvConfig);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Install the CNV UEFI Variables Protocol on a new handle
  // to signify the CNV UEFI Variables are ready.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiCnvUefiVariablesProtocolGuid,
                  NULL,
                  NULL
                  );

Done:
  DEBUG ((DEBUG_ERROR, "CnvUefiVariables status: %r\n", Status));
  ASSERT (!EFI_ERROR (Status));

  return Status;
}
