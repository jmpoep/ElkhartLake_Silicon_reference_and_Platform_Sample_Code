/** @file
  Source code file for the Dummy Charger

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

#include "DummyCharger.h"

EFI_STATUS
EFIAPI
Dummy_StartCharging (
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
  DEBUG((EFI_D_INFO, "[Dummy_StartCharging] Start\n"));
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
Dummy_GetStateOfCharge (
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
  DEBUG((EFI_D_INFO, "[Dummy_GetStateOfCharge] Start\n"));
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
Dummy_SetChargeCurrent (
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
  DEBUG((EFI_D_INFO, "[Dummy_SetChargeCurrent] Start\n"));
  return EFI_UNSUPPORTED;
}


BOOLEAN
EFIAPI
Dummy_CheckForChargerPresence (
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
  DEBUG((EFI_D_INFO, "[Dummy_CheckForChargerPresence] Start\n"));
  return FALSE;
}


EFI_STATUS
EFIAPI
Dummy_GetBatteryInfo (
  BATTERY_INFO                 *BatteryInfo,
  BOOLEAN                      *CapacityReadable,
  BATTERY_VOLTAGE              *BatteryVoltageLevel,
  BATTERY_CAPACITY             *BatteryCapacityLevel
  )
{
  DEBUG((EFI_D_INFO, "[Dummy_GetBatteryInfo] Start\n"));
  return EFI_UNSUPPORTED;
}
