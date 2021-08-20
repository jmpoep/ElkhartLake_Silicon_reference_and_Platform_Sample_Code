/** @file
  Acpi Gnvs Init Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/PlatformNvsArea.h>
#include <Library/DxeAcpiGnvsInitLib.h>

/**
@brief
  Global NVS initialize.

  @param[in] PlatformNvsAreaPtr    - Pointer of global NVS area

  @retval EFI_SUCCESS              - Allocate Global NVS completed.
  @retval EFI_OUT_OF_RESOURCES     - Failed to allocate required page for PlatformNvsAreaProtocol.
**/
EFI_STATUS
EFIAPI
AcpiGnvsInit (
  IN OUT VOID               **PlatformNvsAreaPtr
  )
{
  UINTN                         Pages;
  EFI_PHYSICAL_ADDRESS          Address;
  EFI_STATUS                    Status;
  PLATFORM_NVS_AREA_PROTOCOL    *PlatformNvsAreaProtocol;

  Pages = EFI_SIZE_TO_PAGES (sizeof (PLATFORM_NVS_AREA));
  Address = 0xffffffff; // allocate address below 4G.

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiACPIMemoryNVS,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *PlatformNvsAreaPtr = (VOID *) (UINTN) Address;
  SetMem (*PlatformNvsAreaPtr, sizeof (PLATFORM_NVS_AREA), 0);

  //
  // PlatformNvsAreaProtocol default value init here...
  //
  PlatformNvsAreaProtocol = (PLATFORM_NVS_AREA_PROTOCOL *) &Address;

  //
  // Thermal trip points
  //
  PlatformNvsAreaProtocol->Area->Ac0TripPoint                = 71;
  PlatformNvsAreaProtocol->Area->Ac1TripPoint                = 55;
  PlatformNvsAreaProtocol->Area->Ac0FanSpeed                 = 100;
  PlatformNvsAreaProtocol->Area->Ac1FanSpeed                 = 75;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPoint     = 95;
  PlatformNvsAreaProtocol->Area->PassiveTc1Value             = 1;
  PlatformNvsAreaProtocol->Area->PassiveTc2Value             = 5;
  PlatformNvsAreaProtocol->Area->PassiveTspValue             = 10;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPoint    = 119;

  //
  // DPTF Devices and trip points
  //
  PlatformNvsAreaProtocol->Area->EnableDptf                   = 1;
  PlatformNvsAreaProtocol->Area->EnableSaDevice               = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSA     = 90;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSA    = 95;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSA   = 103;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSaS3 = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSA        = 98;
  PlatformNvsAreaProtocol->Area->PpccStepSize                 = 500;

  PlatformNvsAreaProtocol->Area->EnableChargerParticipant     = 1;

  PlatformNvsAreaProtocol->Area->Enable2DCameraParticipant    = 1;

  PlatformNvsAreaProtocol->Area->EnableBatteryParticipant    = 1;

  PlatformNvsAreaProtocol->Area->EnableSen1Participant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSen1   = 1;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSen1  = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen1 = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen1S3 = 1;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSen1      = 1;
  PlatformNvsAreaProtocol->Area->SensorSamplingPeriodSen1     = 0;

  PlatformNvsAreaProtocol->Area->EnableSen2Participant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSen2   = 1;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSen2  = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen2 = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen2S3 = 1;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSen2      = 1;
  PlatformNvsAreaProtocol->Area->SensorSamplingPeriodSen2     = 0;

  PlatformNvsAreaProtocol->Area->EnableSen3Participant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSen3   = 1;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSen3  = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen3 = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen3S3 = 1;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSen3      = 1;
  PlatformNvsAreaProtocol->Area->SensorSamplingPeriodSen3     = 0;

  PlatformNvsAreaProtocol->Area->EnableSen4Participant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSen4   = 1;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSen4  = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen4 = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen4S3 = 1;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSen4      = 1;
  PlatformNvsAreaProtocol->Area->SensorSamplingPeriodSen4     = 0;

  PlatformNvsAreaProtocol->Area->EnableSen5Participant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointSen5   = 1;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointSen5  = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen5 = 1;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointSen5S3 = 1;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointSen5      = 1;
  PlatformNvsAreaProtocol->Area->SensorSamplingPeriodSen5     = 0;

  PlatformNvsAreaProtocol->Area->EnablePowerParticipant       = 1;

  PlatformNvsAreaProtocol->Area->EnableVSPolicy               = 1;

  PlatformNvsAreaProtocol->Area->EnableVS1Participant          = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointVS1     = 80;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointVS1    = 55;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointVS1   = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointVS1        = 97;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointVS1S3 = 95;

  PlatformNvsAreaProtocol->Area->EnableVS2Participant          = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointVS2     = 80;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointVS2    = 55;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointVS2   = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointVS2        = 97;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointVS2S3 = 95;

  PlatformNvsAreaProtocol->Area->EnableStorageParticipantST1   = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointST1     = 63;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointST1    = 71;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointST1   = 103;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointS3ST1 = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointST1        = 95;
  PlatformNvsAreaProtocol->Area->EnableStorageParticipantST2   = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointST2     = 63;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointST2    = 71;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointST2   = 103;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointS3ST2 = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointST2        = 95;

  PlatformNvsAreaProtocol->Area->EnablePchFivrParticipant = 0;

  PlatformNvsAreaProtocol->Area->EnableWrlsParticipant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointWrls   = 63;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointWrls  = 71;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointWrls = 103;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointWrlsS3 = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointWrls      = 95;

  PlatformNvsAreaProtocol->Area->EnableWWANParticipant        = 1;
  PlatformNvsAreaProtocol->Area->ActiveThermalTripPointWWAN   = 63;
  PlatformNvsAreaProtocol->Area->PassiveThermalTripPointWWAN  = 71;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointWWAN = 103;
  PlatformNvsAreaProtocol->Area->CriticalThermalTripPointWwanS3 = 100;
  PlatformNvsAreaProtocol->Area->HotThermalTripPointWWAN      = 95;

  PlatformNvsAreaProtocol->Area->EnableDisplayParticipant     = 1;
  //
  // DPTF Policies
  //
  PlatformNvsAreaProtocol->Area->EnableActivePolicy           = 1;
  PlatformNvsAreaProtocol->Area->EnablePassivePolicy          = 2;
  PlatformNvsAreaProtocol->Area->EnableCriticalPolicy         = 1;
  PlatformNvsAreaProtocol->Area->TrtRevision                  = 1;
  PlatformNvsAreaProtocol->Area->EnableCtdpPolicy             = 1;
  PlatformNvsAreaProtocol->Area->EnablePowerBossPolicy        = 1;
  PlatformNvsAreaProtocol->Area->EnableRFIMPolicy             = 0;
  PlatformNvsAreaProtocol->Area->EnableAPPolicy               = 1;

  PlatformNvsAreaProtocol->Area->OemDesignVariable0           = 0;
  PlatformNvsAreaProtocol->Area->OemDesignVariable1           = 0;
  PlatformNvsAreaProtocol->Area->OemDesignVariable2           = 0;
  PlatformNvsAreaProtocol->Area->OemDesignVariable3           = 0;
  PlatformNvsAreaProtocol->Area->OemDesignVariable4           = 0;
  PlatformNvsAreaProtocol->Area->OemDesignVariable5           = 0;
  //
  // CLPO (Current Logical Processor Off lining Setting)
  //
  PlatformNvsAreaProtocol->Area->LPOEnable                    = 1;
  PlatformNvsAreaProtocol->Area->LPOStartPState               = 16;
  PlatformNvsAreaProtocol->Area->LPOStepSize                  = 1;
  PlatformNvsAreaProtocol->Area->LPOPowerControlSetting       = 1;
  PlatformNvsAreaProtocol->Area->LPOPerformanceControlSetting = 2;
  //
  // Wireless
  //
  PlatformNvsAreaProtocol->Area->PowerSharingManagerEnable    = 1;
  PlatformNvsAreaProtocol->Area->PsmSplcDomainType1           = 0x09;
  PlatformNvsAreaProtocol->Area->PsmSplcPowerLimit1           = 4000;
  PlatformNvsAreaProtocol->Area->PsmSplcTimeWindow1           = 30000;

  PlatformNvsAreaProtocol->Area->PsmDplcDomainType1           = 9;
  PlatformNvsAreaProtocol->Area->PsmDplcDomainPreference1     = 9;
  PlatformNvsAreaProtocol->Area->PsmDplcPowerLimitIndex1      = 0;
  PlatformNvsAreaProtocol->Area->PsmDplcDefaultPowerLimit1    = 1200;
  PlatformNvsAreaProtocol->Area->PsmDplcDefaultTimeWindow1    = 30000;
  PlatformNvsAreaProtocol->Area->PsmDplcMinimumPowerLimit1    = 1200;
  PlatformNvsAreaProtocol->Area->PsmDplcMaximumPowerLimit1    = 1200;
  PlatformNvsAreaProtocol->Area->PsmDplcMaximumTimeWindow1    = 1000;

  PlatformNvsAreaProtocol->Area->WifiEnable                   = 1;
  PlatformNvsAreaProtocol->Area->WifiDomainType1              = 0x7;
  PlatformNvsAreaProtocol->Area->WifiPowerLimit1              = 0xFFFF;
  PlatformNvsAreaProtocol->Area->WifiTimeWindow1              = 30000;
  PlatformNvsAreaProtocol->Area->TRxDelay0                    = 50;
  PlatformNvsAreaProtocol->Area->TRxCableLength0              = 50;
  PlatformNvsAreaProtocol->Area->TRxDelay1                    = 50;
  PlatformNvsAreaProtocol->Area->TRxCableLength1              = 50;
  PlatformNvsAreaProtocol->Area->WrddDomainType1              = 0x7;
  PlatformNvsAreaProtocol->Area->WrddCountryIndentifier1      = 0x4150; // "AP"
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarEnable            = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit1         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit2         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit3         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit4         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit5         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit6         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit7         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit8         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit9         = 0x0;
  PlatformNvsAreaProtocol->Area->WrdsWiFiSarTxPowerSet1Limit10        = 0x0;
  PlatformNvsAreaProtocol->Area->AntennaDiversity                     = 0x2;

  PlatformNvsAreaProtocol->Area->EwrdWiFiDynamicSarEnable             = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiDynamicSarRangeSets          = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit1         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit2         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit3         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit4         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit5         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit6         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit7         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit8         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit9         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet2Limit10        = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit1         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit2         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit3         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit4         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit5         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit6         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit7         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit8         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit9         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet3Limit10        = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit1         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit2         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit3         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit4         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit5         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit6         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit7         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit8         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit9         = 0x0;
  PlatformNvsAreaProtocol->Area->EwrdWiFiSarTxPowerSet4Limit10        = 0x0;
  PlatformNvsAreaProtocol->Area->WiFiDynamicSarAntennaACurrentSet = 0x0;
  PlatformNvsAreaProtocol->Area->WiFiDynamicSarAntennaBCurrentSet = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerMax1      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerChainA1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerChainB1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerMax2      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerChainA2   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup1PowerChainB2   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerMax1      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerChainA1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerChainB1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerMax2      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerChainA2   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup2PowerChainB2   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerMax1      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerChainA1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerChainB1   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerMax2      = 0xFF;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerChainA2   = 0x0;
  PlatformNvsAreaProtocol->Area->WgdsWiFiSarDeltaGroup3PowerChainB2   = 0x0;

  PlatformNvsAreaProtocol->Area->BluetoothSar                 = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarBr               = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarEdr2             = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarEdr3             = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarLe               = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarLe2Mhz           = 0x0;
  PlatformNvsAreaProtocol->Area->BluetoothSarLeLr             = 0x0;
  PlatformNvsAreaProtocol->Area->CoExistenceManager           = 0x0;
  //
  // Miscellaneous
  //
  PlatformNvsAreaProtocol->Area->ConfigTdpBios = 0;
  PlatformNvsAreaProtocol->Area->PL1LimitCS = 0;
  PlatformNvsAreaProtocol->Area->PL1LimitCSValue = 4500;
  return EFI_SUCCESS;
}

