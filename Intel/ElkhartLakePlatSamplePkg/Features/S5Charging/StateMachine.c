/** @file
  This file is for S5 charging flow control.

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
#include "StateMachine.h"
#include "HardwareInterface.h"
#include "S5Charging.h"

extern APPLET_STATE       mChargingState;
extern Reset_Shutdown     ResetVariable;
extern BATT_CONF          Dyn_bat_conf;
extern BATT_CONF_HR       Dyn_bat_conf_hr;
extern UINT8              CriticalBatteryLimit;


VOID
SetActiveState (
  STATE_TYPE    State
  )
/*++

Routine Description:

  Set the current active state. Can be one of the states in the enum STATE_TYPE.

Arguments:

  State             State to which applet must transition

Returns:
  None
--*/
{
  // For each state, set the global state
  DEBUG ((EFI_D_INFO, "[SetActiveState] Start\n"));

  switch(State) {
  case Initial:
    mChargingState.CurrentState = Initial;
    DEBUG ((EFI_D_INFO, "[SetActiveState] Current State Initial\n"));
    break;

  case Charging:
    mChargingState.CurrentState = Charging;
    DEBUG ((EFI_D_INFO, "[SetActiveState] Current State Charging\n"));
    break;

  case Charged:
    mChargingState.CurrentState = Charged;
    DEBUG ((EFI_D_INFO, "[SetActiveState] Current State Charged\n"));
    break;

  case PowerUp:
    mChargingState.CurrentState = PowerUp;
    DEBUG ((EFI_D_INFO, "[SetActiveState] Current State PowerUp\n"));
    break;

  default:
    DEBUG ((EFI_D_INFO, "[SetActiveState] Current State: Unknown\n"));
    break;

  }
  DEBUG ((EFI_D_INFO, "[SetActiveState] End\n"));
  return;
}

EFI_STATUS
ExecInitialStateActions (
  VOID
  )
/*++

Routine Description:

  Execute the actions relevant to Initial State.

Arguments:

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.
--*/
{
  EFI_STATUS      Status;
  UINT32          CurrentCapacity;
  CHARGE_STATE    CurrentState;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[ExecInitialStateActions] Start\n"));

  // start charging activity
  StartCharging ();

  DEBUG ((EFI_D_INFO, "[ExecInitialStateActions] Before CheckWakeSource\n"));

  // Get the State of Charge.
  Status = GetStateOfCharge (&CurrentCapacity, &CurrentState);

  mDisplayInterface.ClockTicks = 0;
  DisplayIcon (CurrentCapacity);

  DEBUG ((EFI_D_INFO, "[ExecInitialStateActions] After CheckWakeSource\n"));

  SetActiveState (Charging);

  DEBUG ((EFI_D_INFO, "[ExecInitialStateActions] End\n"));

  return Status;
}


EFI_STATUS
ExecChargedStateActions (
  VOID
  )
/*++

Routine Description:

  Execute the actions relevant to Charged State.

Arguments:

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.
--*/
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[ExecChargedStateActions] Start\n"));
  Print (L"[ExecChargedStateActions] Start\n");
  DisplayIcon (MAX_STATE_OF_CHARGE);

  Print (L"Fully Charged. Shutting down system from S5 Charging\n");

  // Do a Shutdown.
  gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);

  DEBUG ((EFI_D_INFO, "[ExecChargedStateActions] End\n"));

  return Status;
}


EFI_STATUS
ExecChargingStateActions (
  VOID
  )
/*++

Routine Description:

  Execute the actions relevant to Charging State.

Arguments:

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.
--*/
{
  EFI_STATUS      Status;
  UINT8           Duration;
  UINT32          CurrentCapacity;
  CHARGE_STATE    CurrentState;
  BOOLEAN         Level;
  CHARGER_TYPE    Type;
  EFI_TPL         CurrentTpl;

  Status   = EFI_SUCCESS;
  Duration = 0;
  Level    = TRUE;

  DEBUG ((EFI_D_INFO, "[ExecChargingStateActions] Start\n"));

  if (!CheckForChargerPresence (&Type)) {
    //
    // Shutdown immediately. There is no charger connected possibly.
    //
    Status = EFI_SUCCESS;
    gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
  }

  ClearDisplay ();

  Level = CheckPowerButtonStatus ();

  Status = GetStateOfCharge (&CurrentCapacity, &CurrentState);

  if (Level) {
    //
    // Get CurrentCapacity if CurrentCapacity > crtical
    //
    DEBUG ((EFI_D_INFO, "[ExecChargingStateActions] Power Button pressed for %x Level = %x\n", Duration, Level));

    if (CurrentCapacity > CriticalBatteryLimit) {
      CurrentTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
      GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
      ResetVariable.Reset_Type = RESET_TYPE;
      SetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
      gBS->RestoreTPL (CurrentTpl);
      SetActiveState (PowerUp);
    } else {
      ClearDisplay ();
      Print (L"Battery Charge Level = %d%%. Below critical Level(%d%%). Cannot Power Up.\nLeave charger connected.\n", CurrentCapacity, CriticalBatteryLimit);
    }
  }

  // alternate button
  if (mInputButtonInterface.CheckInputButtonStatus != NULL) {
    DEBUG ((EFI_D_INFO, "[ExecChargingStateActions] CheckInputbuttonStatus != NULL\n"));
    if (!mInputButtonInterface.CheckInputButtonStatus()) {
      DisplayIcon (CurrentCapacity);
    }
  }

  if (CurrentCapacity == MAX_STATE_OF_CHARGE) {
    Print (L"reached MAX_STATE_OF_CHARGE\n");
    SetActiveState (Charged);
  }
  return Status;
}

EFI_STATUS
ExecPowerUpStateActions (
  VOID
  )
/*++

Routine Description:

  Execute the actions relevant to PowerUp State.

Arguments:

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.
--*/
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[ExecPowerUpStateActions] Start\n"));

  // Clear the screen.
  gST->ConOut->ClearScreen (gST->ConOut);

  // Allow the device to boot up normally.
  // This will signal the WaitForEvent in InitializeEFICharging to exit
  // and allow normal boot.
  gBS->SetTimer (mChargingState.TimerEvent, TimerCancel, 0);

  gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
  DEBUG ((EFI_D_INFO, "[ExecPowerUpStateActions] End\n"));
  return Status;
}
