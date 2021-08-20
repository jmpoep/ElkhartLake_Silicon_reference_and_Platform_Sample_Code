/** @file
  EFI Charging Applet Protocol function

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
#include "HardwareInterface.h"

#define CHARGING_MAJOR_REVISION  0x01
#define CHARGING_MINOR_REVISION  0x01

EFI_STATUS
EFIAPI
AppletGetChargerType (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT CHARGER_TYPE                 *ChargerType
  )
/*++

Routine Description:
   Retrieves the type of battery charger plugged in to the system.
Arguments:
   [OUT] ChargerType : the type of the charger

Returns:
   EFI_SUCCESS       : Successfully retrieved the Charger Type.
   EFI_UNSUPPORTED   : Charger is not connected
--*/
{
  EFI_STATUS  Status;
  BOOLEAN     ChargerPresent;

  Status         = EFI_SUCCESS;
  ChargerPresent = FALSE;

  DEBUG ((EFI_D_INFO, "[GetChargerType] Start\n"));

  if (mChargerInterface.CheckForChargerPresence != NULL) {
    ChargerPresent = mChargerInterface.CheckForChargerPresence (ChargerType);
  } else {
    DEBUG ((EFI_D_INFO, "[GetChargerType] Charger functions not implemented\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  DEBUG ((EFI_D_INFO, "[GetChargerType] ChargerType is 0x%x\n", *ChargerType));

Exit:
  if (ChargerPresent == FALSE) {
    *ChargerType = ChargerUndefined;
  }
  DEBUG ((EFI_D_INFO, "[GetChargerType] End\n"));
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
AppletSetChargeRate (
  IN CHARGING_APPLET_PROTOCOL      *This,
  IN UINT32                        ChargeRate
  )
/*++

Routine Description:
   Set the charge rate on the battery charging hardware
Arguments:
   [IN] ChargerRate : the rate of charging desired.

Returns:
   EFI_SUCCESS       : Successfully retrieved the Charger Type.
   EFI_DEVICE_ERROR  : Unable to set the required rate.
--*/
{
  EFI_STATUS         Status;
  CHARGER_TYPE       ChargerType;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[SetChargeRate] Start\n"));

  Status = AppletGetChargerType (This, &ChargerType);

  if (EFI_ERROR (Status))
    goto Exit;

  if (mChargerInterface.SetChargeRate != NULL) {
    mChargerInterface.SetChargeRate (ChargeRate);
  } else {
    DEBUG ((EFI_D_INFO, "[SetChargeRate] charger functions not implemented\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  DEBUG ((EFI_D_INFO, "[SetChargeRate] End\n"));

Exit:
  return Status;

}

EFI_STATUS
EFIAPI
AppletGetCurrentChargeState (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT UINT32                       *CurrentCapacity,
  OUT CHARGE_STATE                 *CurrentState
  )
/*++

Routine Description:
   Get the current charge state on the battery charging hardware
Arguments:
   [OUT] CurrentCapacity :
   [OUT] CurrentState    : State of charging

Returns:
   EFI_SUCCESS       : Successfully retrieved the data.
   EFI_DEVICE_ERROR  : Unable to retrieve the data.
--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[GetCurrentChargeState] Start\n"));
  if (mChargerInterface.GetStateOfCharge != NULL) {
    Status = mChargerInterface.GetStateOfCharge (CurrentCapacity, CurrentState);
  } else {
    DEBUG ((EFI_D_INFO, "[GetCurrentChargeState] charger functions not implemented\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  DEBUG ((EFI_D_INFO, "[GetCurrentChargeState] End\n"));

Exit:
  return Status;
}

EFI_STATUS
EFIAPI
AppletGetBatteryInfo (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT BATTERY_INFO                 *BatteryInfo,
  OUT BOOLEAN                      *BatteryPresent,
  OUT BOOLEAN                      *BatteryValid,
  OUT BOOLEAN                      *CapacityReadable,
  OUT BATTERY_VOLTAGE              *BatteryVoltageLevel,
  OUT BATTERY_CAPACITY             *BatteryCapacityLevel
  )
/*++

Routine Description:
   Returns the battery static info needed for the charging applet.

Arguments:
   [OUT] BatteryInfo : Battery Information retrieved.

Returns:
   EFI_SUCCESS       : Successfully retrieved the data.
   EFI_DEVICE_ERROR  : Unable to retrieve the data.
--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  if ((BatteryInfo == NULL)         ||
      (BatteryPresent == NULL)      ||
      (BatteryValid == NULL)        ||
      (CapacityReadable == NULL)    ||
      (BatteryVoltageLevel == NULL) ||
      (BatteryCapacityLevel == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Set initial value
  //
  *BatteryPresent         = FALSE;
  *CapacityReadable       = FALSE;
  *BatteryValid           = FALSE;
  *BatteryVoltageLevel    = 0;
  *BatteryCapacityLevel   = 0;

  DEBUG ((EFI_D_INFO, "[GetBatteryInfo] Start\n"));

  //
  // TODO: Get *BatteryPresent and *BatteryValid status from hardware
  //
  *BatteryPresent         = TRUE;
  *BatteryValid           = TRUE;

  if (mChargerInterface.GetBatteryInfo != NULL) {
    Status = mChargerInterface.GetBatteryInfo (BatteryInfo, CapacityReadable, BatteryVoltageLevel, BatteryCapacityLevel);
  } else {
    DEBUG ((EFI_D_INFO, "[GetBatteryInfo] GetBatteryInfo functions not implemented\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  DEBUG ((EFI_D_INFO, "[GetBatteryInfo] End\n"));

Exit:
  return Status;
}


EFI_STATUS
EFIAPI
AppletPutPlatformToLowPower (
  IN CHARGING_APPLET_PROTOCOL      *This,
  IN BOOLEAN                       PowerSaveMode,
  IN BOOLEAN                       DisplayPMState
  )
{
  EFI_STATUS      Status;
  UINT32          CurrentCapacity;
  CHARGE_STATE    CurrentState;

  Status = EFI_SUCCESS;
  //
  // To indicate if Platform to be kept power saver mode or not
  //
  if (PowerSaveMode) {
    PutPchIpInD3 ();
    SetFuncDisable ();
    SetCpuInLfm ();
  }

  //
  // Display Panel electronics/controller should be in off state or they should in on state to enable the display
  //
  if (DisplayPMState) {
    Status = GetStateOfCharge (&CurrentCapacity, &CurrentState);
    mDisplayInterface.ClockTicks = 0;
    DisplayIcon (CurrentCapacity);
  }
  return EFI_SUCCESS;
}


CHARGING_APPLET_PROTOCOL mChargingAppletProtocol = {
  AppletGetChargerType,
  AppletSetChargeRate,
  AppletGetCurrentChargeState,
  AppletGetBatteryInfo,
  AppletPutPlatformToLowPower,
  CHARGING_MAJOR_REVISION,
  CHARGING_MINOR_REVISION
};

