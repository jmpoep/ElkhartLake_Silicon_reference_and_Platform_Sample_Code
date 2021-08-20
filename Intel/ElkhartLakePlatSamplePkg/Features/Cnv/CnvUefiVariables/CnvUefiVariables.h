/** @file
  Header file to define internal macro, structures for CNV variable implementation

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

**/

#ifndef __CNV_UEFI_VARIABLES_H__
#define __CNV_UEFI_VARIABLES_H__

//
// Statements that include other header files
//
#include <Protocol/VariableLock.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <CnvVariables.h>
#include <SetupVariable.h>

#define WIFI_DOMAIN_VALUE    0x07
#define WIGIG_DOMAIN_VALUE   0x10

#pragma pack(push, 1)
//
// CNV Configuration
//
typedef struct {
  UINT8   WifiDomainType1;
  UINT16  WifiPowerLimit1;
  UINT32  WifiTimeWindow1;

  UINT8   TRxDelay0;
  UINT8   TRxCableLength0;
  UINT8   TRxDelay1;
  UINT8   TRxCableLength1;

  UINT8   WrddDomainType1;
  UINT16  WrddCountryIndentifier1;

  UINT8   WrdsWiFiSarEnable;
  UINT8   WrdsWiFiSarTxPowerSet1Limit1;
  UINT8   WrdsWiFiSarTxPowerSet1Limit2;
  UINT8   WrdsWiFiSarTxPowerSet1Limit3;
  UINT8   WrdsWiFiSarTxPowerSet1Limit4;
  UINT8   WrdsWiFiSarTxPowerSet1Limit5;
  UINT8   WrdsWiFiSarTxPowerSet1Limit6;
  UINT8   WrdsWiFiSarTxPowerSet1Limit7;
  UINT8   WrdsWiFiSarTxPowerSet1Limit8;
  UINT8   WrdsWiFiSarTxPowerSet1Limit9;
  UINT8   WrdsWiFiSarTxPowerSet1Limit10;

  UINT8   EwrdWiFiDynamicSarEnable;
  UINT8   EwrdWiFiDynamicSarRangeSets;
  UINT8   EwrdWiFiSarTxPowerSet2Limit1;
  UINT8   EwrdWiFiSarTxPowerSet2Limit2;
  UINT8   EwrdWiFiSarTxPowerSet2Limit3;
  UINT8   EwrdWiFiSarTxPowerSet2Limit4;
  UINT8   EwrdWiFiSarTxPowerSet2Limit5;
  UINT8   EwrdWiFiSarTxPowerSet2Limit6;
  UINT8   EwrdWiFiSarTxPowerSet2Limit7;
  UINT8   EwrdWiFiSarTxPowerSet2Limit8;
  UINT8   EwrdWiFiSarTxPowerSet2Limit9;
  UINT8   EwrdWiFiSarTxPowerSet2Limit10;
  UINT8   EwrdWiFiSarTxPowerSet3Limit1;
  UINT8   EwrdWiFiSarTxPowerSet3Limit2;
  UINT8   EwrdWiFiSarTxPowerSet3Limit3;
  UINT8   EwrdWiFiSarTxPowerSet3Limit4;
  UINT8   EwrdWiFiSarTxPowerSet3Limit5;
  UINT8   EwrdWiFiSarTxPowerSet3Limit6;
  UINT8   EwrdWiFiSarTxPowerSet3Limit7;
  UINT8   EwrdWiFiSarTxPowerSet3Limit8;
  UINT8   EwrdWiFiSarTxPowerSet3Limit9;
  UINT8   EwrdWiFiSarTxPowerSet3Limit10;
  UINT8   EwrdWiFiSarTxPowerSet4Limit1;
  UINT8   EwrdWiFiSarTxPowerSet4Limit2;
  UINT8   EwrdWiFiSarTxPowerSet4Limit3;
  UINT8   EwrdWiFiSarTxPowerSet4Limit4;
  UINT8   EwrdWiFiSarTxPowerSet4Limit5;
  UINT8   EwrdWiFiSarTxPowerSet4Limit6;
  UINT8   EwrdWiFiSarTxPowerSet4Limit7;
  UINT8   EwrdWiFiSarTxPowerSet4Limit8;
  UINT8   EwrdWiFiSarTxPowerSet4Limit9;
  UINT8   EwrdWiFiSarTxPowerSet4Limit10;

  UINT8   WgdsWiFiSarDeltaGroup1PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainB2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainB2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainB2;

  UINT8   AntennaDiversity;

  UINT8   Enable;
  UINT8   BluetoothSarBr;
  UINT8   BluetoothSarEdr2;
  UINT8   BluetoothSarEdr3;
  UINT8   BluetoothSarLe;
  UINT8   BluetoothSarLe2Mhz;
  UINT8   BluetoothSarLeLr;
} UEFI_CNV_CONFIG;
#pragma pack(pop)

extern EFI_GUID gUefiIntelCnvWlanVariablesGuid;
extern EFI_GUID gUefiIntelCnvBtVariablesGuid;
extern EFI_GUID gUefiIntelCnvWigigVariablesGuid;

#endif
