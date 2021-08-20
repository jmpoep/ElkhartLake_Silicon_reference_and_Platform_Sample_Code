/** @file
  Source code file for the EC Lite Charger

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include "EcLiteCharger.h"

EFI_STATUS
EFIAPI
EcLite_StartCharging (
  VOID
  )
/*++

Routine Description:
   Start Charging by setting appropriate registers.

Arguments:


Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.
--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  DEBUG ((EFI_D_INFO, "[EcLite_StartCharging] Start\n"));

  DEBUG ((EFI_D_INFO, "Not implemented - TODO\n"));

  DEBUG ((EFI_D_INFO, "[EcLite_StartCharging] End\n"));
  return Status;
}


EFI_STATUS
EFIAPI
EcLite_GetStateOfCharge (
  OUT UINT32          *CurrentCapacity,
  OUT CHARGE_STATE    *CurrentState
  )
/*++

Routine Description:

  Gets the State of Charge.

Arguments:

Returns:
   SOC   State of Charge in percentage
--*/
{
  EFI_STATUS  Status;
  UINT16      DataBuffer;
  UINT16      DataBuffer1;

  Status      = EFI_SUCCESS;
  DataBuffer  = 0;
  DataBuffer1 = 0xFFFF;

  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] Start\n"));

  GetBattery1CurrentState (&DataBuffer);
  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] GetBattery1CurrentState %d\n", DataBuffer));

  if ((DataBuffer & BIT0) == BIT0) {
    *CurrentState = NoCharge;// Discharging
  }
  if ((DataBuffer & BIT1) == BIT1) {
    *CurrentState = ChargeOn;
  }
  if ((DataBuffer & BIT2) == BIT2) {
    *CurrentState = ChargeOn;// Critical
  }

  GetBattery1RemainingCapacityLevel (&DataBuffer);
  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] Remaining Capacity %d\n", DataBuffer));

  GetBattery1FullChargeCapacityLevel (&DataBuffer1);
  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] Full charge Capacity %d\n", DataBuffer1));

  if (DataBuffer1 == 0) {
    *CurrentCapacity = 0;
  } else {
    *CurrentCapacity = (DataBuffer * 100 / DataBuffer1);
  }
  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] CurrentCapacity %d CurrentState %d\n", *CurrentCapacity, *CurrentState));
  DEBUG ((EFI_D_INFO, "[EcLite_GetStateOfCharge] End\n"));

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EcLite_SetChargeCurrent (
  UINT32  ChargeRate
  )
/*++

Routine Description:

  Sets the charge rate.

Arguments:
   ChargeRate: The rate at which we want it to charge.
Returns:
   EFI_SUCCESS            Set rate successfully
   EFI_INVALID_PARAMETER  Rate value is invalid
   EFI_DEVICE_ERROR       Unable to write the value to device.
--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  DEBUG ((EFI_D_INFO, "[EcLite_SetChargeCurrent] Start\n"));

  DEBUG ((EFI_D_INFO, "Not implemented - TODO\n"));

  DEBUG ((EFI_D_INFO, "[EcLite_SetChargeCurrent] End\n"));
  return Status;
}


BOOLEAN
EFIAPI
EcLite_CheckForChargerPresence (
  CHARGER_TYPE  *Type
  )
/*++

Routine Description:

  Checks for the presence of the charger

Arguments:
   Type: [OUT] Charger Type
Returns:
   TRUE      charger present
   FALSE     charger absent
--*/
{
  EFI_STATUS  Status;
  BOOLEAN     ChargerPresent;

  Status         = EFI_SUCCESS;
  ChargerPresent = PowerStateIsAc_EcLite();

  DEBUG ((EFI_D_INFO, "[EcLite_CheckForChargerPresence] Start\n"));

  *Type = SdpCharger;
  DEBUG ((EFI_D_INFO, "[CheckForChargerType] SdpCharger. This is hardcoded - TODO\n"));

  DEBUG ((EFI_D_INFO, "[CheckForChargerPresence] Status %x\n", ChargerPresent));

  DEBUG ((EFI_D_INFO, "[EcLite_CheckForChargerPresence] End\n"));

  return ChargerPresent;
}


EFI_STATUS
EFIAPI
EcLite_GetBatteryInfo (
  BATTERY_INFO                 *BatteryInfo,
  BOOLEAN                      *CapacityReadable,
  BATTERY_VOLTAGE              *BatteryVoltageLevel,
  BATTERY_CAPACITY             *BatteryCapacityLevel
  )
{
  EFI_STATUS  Status;
  UINT16      DataBuffer;

  Status     = EFI_SUCCESS;
  DataBuffer = 0;

  DEBUG ((EFI_D_INFO, "[EcLite_GetBatteryInfo] Start\n"));

  //Battery design capacity to be filled in BatteryInfo
  GetBattery1DesignCapacity (&DataBuffer);
  BatteryInfo->DesignCapacity = DataBuffer;
  DEBUG ((EFI_D_INFO, "[BatteryGetBatteryInfo] Design capacity is %x\n", BatteryInfo->DesignCapacity));

  //Capacity readable
  GetBattery2DesignCapacity (&DataBuffer);
  *CapacityReadable = (BOOLEAN) DataBuffer;
  DEBUG ((EFI_D_INFO, "[CapacityReadable] Capacity readable is %x\n", *CapacityReadable));

  DataBuffer = 0;
  GetBattery1VoltageLevel (&DataBuffer);
  *BatteryVoltageLevel = DataBuffer;
  DEBUG ((EFI_D_INFO, "[BatteryGetBatteryInfo] BatteryVoltageLevel is %x\n", *BatteryVoltageLevel));

  DataBuffer = 0;
  GetBattery1RemainingCapacityLevel (&DataBuffer);
  *BatteryCapacityLevel = (BATTERY_CAPACITY) DataBuffer;
  DEBUG ((EFI_D_INFO, "[BatteryGetBatteryInfo] BatteryCapacityLevel is %x\n",*BatteryCapacityLevel));

  DEBUG ((EFI_D_INFO, "[EcLite_GetBatteryInfo] End\n"));

  return Status;
}
