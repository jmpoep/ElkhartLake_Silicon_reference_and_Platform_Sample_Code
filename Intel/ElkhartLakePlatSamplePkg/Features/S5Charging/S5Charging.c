/** @file
  Source code file for the S5 Charging DXE module

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

#include "S5Charging.h"

extern APPLET_STATE              mChargingState;
extern CHARGING_APPLET_PROTOCOL  mChargingAppletProtocol;

BATT_CONF                        DynBatConfig;
BATT_CONF_HR                     DynBatConfigHr;
UINT8                            mLpmFeature;
Reset_Shutdown                   ResetVariable;
UINT8                            CriticalBatteryLimit;


EFI_STATUS
EFIAPI
GetResetTypeVarible (
  UINTN    VariableType
  )
{
  EFI_STATUS  Status;
  UINTN       VarSize;

  Status = EFI_SUCCESS;

  if (VariableType == NVRAM_DYNAMIC_BAT_PARAM) {
    VarSize = sizeof (DynBatConfig);

    Status = gRT->GetVariable (
                    REG_PARM,
                    &gSfiveChargingGuid,
                    NULL,
                    &VarSize,
                    &DynBatConfig
                    );

    DEBUG ((EFI_D_INFO, "NVRAM-DYN_BAT_CONF %x\t %x\t %x\t %x\t %x\t\n %x\t %x\t %x\t %x\t \n",
           DynBatConfig.signature,
           DynBatConfig.fcc,
           DynBatConfig.learned_cycle,
           DynBatConfig.cycle_count,
           DynBatConfig.cycle_q,
           DynBatConfig.c_min_rate,
           DynBatConfig.rmc,
           DynBatConfig.nac,
           DynBatConfig.overcharge_q));
  } else if (VariableType == NVRAM_RESET_VARIABLE_PARAM) {
    VarSize = sizeof (ResetVariable);
    Status = gRT->GetVariable (
                    REG_PARM,
                    &gResetTypeGuid,
                    NULL,
                    &VarSize,
                    &ResetVariable
                    );

    DEBUG ((EFI_D_INFO, "NVRAM-RESET %x\t %x\t %x\t %x\t %X\t \n",
            ResetVariable.Sign,
            ResetVariable.Reset_Type,
            ResetVariable.OS_Reset,
            ResetVariable.OS_Shutdown,
            ResetVariable.ChargingEnable
            ));
  } else if (VariableType == NVRAM_DYNAMIC_BAT_PARAM_HR) {
    VarSize = sizeof (DynBatConfigHr);

    Status = gRT->GetVariable (
                    REG_PARM,
                    &gSfiveChargingGuid,
                    NULL,
                    &VarSize,
                    &DynBatConfigHr
                    );

    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Rcomp0 = %x \n", DynBatConfigHr.Rcomp0));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Tempco = %x \n", DynBatConfigHr.Tempco));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Iavg_empty = %x \n", DynBatConfigHr.Iavg_empty));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.FullCapNom = %x \n", DynBatConfigHr.FullCapNom));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Qrtable_00 = %x \n", DynBatConfigHr.Qrtable_00));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Qrtable_10 = %x \n", DynBatConfigHr.Qrtable_10));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Qrtable_20 = %x \n", DynBatConfigHr.Qrtable_20));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Qrtable_30 = %x \n", DynBatConfigHr.Qrtable_30));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.FullCap = %x \n", DynBatConfigHr.FullCap));
    DEBUG ((EFI_D_INFO, " DynBatConfigHr.Cycles = %x \n", DynBatConfigHr.Cycles));

  }

  return Status;
}


EFI_STATUS
EFIAPI
SetResetTypeVarible (
  UINTN    VariableType
  )
{
  EFI_STATUS  Status;
  UINTN       VarSize;

  Status = EFI_SUCCESS;

  if (VariableType == NVRAM_DYNAMIC_BAT_PARAM ) {
    VarSize = sizeof (DynBatConfig);

    Status = gRT->SetVariable (
                    REG_PARM,
                    &gSfiveChargingGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    VarSize,
                    &DynBatConfig
                    );
    DEBUG ((EFI_D_INFO, "NVRAM DynBatConfig Parameter Update Periodically\n"));
  } else if (VariableType == NVRAM_RESET_VARIABLE_PARAM) {
    VarSize = sizeof (ResetVariable);
    Status = gRT->SetVariable (
                    REG_PARM,
                    &gResetTypeGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS |  EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    VarSize,
                    &ResetVariable
                    );
    DEBUG ((EFI_D_INFO, "NVRAM ResetVariable Parameter Update\n"));
  } else if (VariableType == NVRAM_DYNAMIC_BAT_PARAM_HR ) {

    VarSize = sizeof (DynBatConfigHr);

    Status = gRT->SetVariable (
                    REG_PARM,
                    &gSfiveChargingGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    VarSize,
                    &DynBatConfigHr
                    );
    DEBUG ((EFI_D_INFO, "NVRAM DynBatConfigHr Parameter Update Periodically\n"));
  }

  return Status;
}


VOID
EFIAPI
DummyHandler (
  EFI_EVENT           Event,
  VOID                *Context
  )
{
  return;
}


EFI_STATUS
EFIAPI
InitializeS5Charging (
  VOID
  )
/*++

Routine Description:

  Initialize the timers, etc.

Arguments:
   None
Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.

--*/
{
  EFI_STATUS      Status;
  UINTN           Index;
  CHARGER_TYPE    Type;
  EFI_EVENT       WaitList[2];

  Status = EFI_SUCCESS;
  Index  = 0;

  DEBUG ((EFI_D_INFO, "[InitializeS5Charging] Start\n"));
  if (CheckForChargerPresence (&Type) == FALSE) {
    //
    // There is no charger, so exit
    //
    DEBUG ((EFI_D_INFO, "[InitializeS5Charging] NO CHARGER, End\n"));
    return EFI_DEVICE_ERROR;
  }

  if (mLpmFeature != 0x0) {
    DEBUG ((EFI_D_INFO, "LPM Start\n"));
    PutPchIpInD3 ();
    SetCpuInLfm ();
    DEBUG ((EFI_D_INFO, "LPM End\n"));
  }

  //
  // Initialize the timer.
  //
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_WAIT,
                  TPL_CALLBACK,
                  ChargingTimerHandler,
                  &mChargingState,
                  &mChargingState.TimerEvent
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "[InitializeS5Charging] CreateEvent Failed\n"));
    return Status;
  }

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_CALLBACK,
                  DummyHandler,
                  NULL,
                  &mChargingState.ExitTimerEvent
                  );

  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_INFO, "[InitializeS5Charging] Create ExitTimerEvent Failed\n"));
    return Status;
  }

  //
  // Check for 100ms Timer Interval.
  //
  Status = gBS->SetTimer (
                  mChargingState.TimerEvent,
                  TimerPeriodic,
                  CHARGING_TIMER_INTERVAL
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_INFO, "[InitializeS5Charging] SetTimer Failed\n"));
    return Status;
  }

  //
  // This will keep waiting until power button pressed or charging done.
  //
  WaitList[0] = mChargingState.TimerEvent;
  WaitList[1] = mChargingState.ExitTimerEvent;
  do {
    Status = gBS->WaitForEvent (2, WaitList, &Index);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO, "gBS->WaitForEvent Failed - Status: %r\n", Status));
    }
    DEBUG ((EFI_D_INFO, "gBS->WaitForEvent Left - Status: %r Index: %x\n", Status, Index));
  } while (Index < 1);

  gBS->SetTimer (
         mChargingState.TimerEvent,
         TimerCancel,
         0
         );
  DEBUG ((EFI_D_INFO, "[InitializeS5Charging] Cancelling the timer = %r\n", Status));

  if (EFI_ERROR(Status)) {
    DEBUG ((EFI_D_INFO, "[InitializeS5Charging] SetTimer Failed\n"));
    return Status;
  }
  gBS->CloseEvent (mChargingState.TimerEvent);
  gBS->CloseEvent (mChargingState.ExitTimerEvent);

  DEBUG ((EFI_D_INFO, "[InitializeS5Charging] End\n"));
  return Status;
}


VOID
EFIAPI
ChargingTimerHandler (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
/*++

Routine Description:

  Initialize the timers, etc.

Arguments:
   None
Returns:

--*/
{
  APPLET_STATE  *State = (APPLET_STATE *)Context;

  DEBUG ((EFI_D_INFO, "[ChargingTimerHandler] Entered, State->CurrentState is %d\n", State->CurrentState));

  switch (State->CurrentState) {
  case Initial:
    ExecInitialStateActions ();
    break;
  case Charging:
    ExecChargingStateActions ();
    break;
  case Charged:
    ExecChargedStateActions ();
    break;
  case PowerUp:
    ExecPowerUpStateActions ();
    break;
  default:
    DEBUG ((EFI_D_INFO, "[ChargingTimerHandler] Default\n"));
    break;
  }

  DEBUG ((EFI_D_INFO, "[ChargingTimerHandler] Exit\n"));
  return;
}


EFI_STATUS
EFIAPI
DiscoverHardwareCombination (
  UINT16       BoardId
  )
/*++

Routine Description:

  Prior to initialization, discover the hardware combination.

Arguments:
   BoardId

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_DEVICE_ERROR        Cannot startup the driver.

--*/
{
  DEBUG ((EFI_D_INFO, "[DiscoverHardwareCombination] Start\n"));
  DEBUG ((EFI_D_INFO, "[DiscoverHardwareCombination] BoardId = 0x%X\n", BoardId));

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
      InitializeHardwareInterfaces (ECLITE);
      break;
    default:
      break;
  }
  DEBUG ((EFI_D_INFO, "[DiscoverHardwareCombination] End\n"));
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
S5ChargingEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
/*++

Routine Description:

  Driver Entry point.

Arguments:

  ImageHandle             Image handle of the loaded driver
  SystemTable             Pointer to the System Table

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_OUT_OF_RESOURCES    Cannot allocate protocol data structure
  EFI_DEVICE_ERROR        Cannot startup the driver.

--*/
{
  EFI_STATUS             Status;
  UINTN                  VarDataSize;
  SETUP_DATA             SetupData;
  EFI_HANDLE             Handle;
  CHARGER_TYPE           Type;
  UINT8                  WakeSource;
  UINT32                 CurrentCapacity;
  CHARGE_STATE           CurrentState;
  UINT8                  CriticalBatteryLimitFeature;
  UINT16                 OS_Shutdown;
#if (defined X64_EFICHARGING_ENABLE) && (X64_EFICHARGING_ENABLE == 1)
  UINT16                 OS_Restart = 0;
#endif
  UINT16                 BoardId;

  DEBUG ((EFI_D_INFO, "[S5ChargingEntry] Start\n"));

  Status                      = EFI_SUCCESS;
  WakeSource                  = 0;
  CriticalBatteryLimitFeature = 0;
  OS_Shutdown                 = 0x0;
  BoardId                     = BoardIdUnknown1;

  //
  // Get Board ID
  //
  BoardId = PcdGet16 (PcdBoardId);
  if (!((BoardId == BoardIdEhlLp4xType4Erb)  ||
       (BoardId == BoardIdEhlLp4xType4Rvp1)  ||
       (BoardId == BoardIdEhlDdr4Type3Rvp2)  ||
       (BoardId == BoardIdEhlLp4xType3Crb))) {
    DEBUG ((EFI_D_INFO, "[S5ChargingEntry] Skip S5Charging. BoardId = %d \n", BoardId));
    return EFI_UNSUPPORTED;
  }

  //
  // First discover the hardware board combination
  //
  Status = DiscoverHardwareCombination (BoardId);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  //
  // Install Charging Applet Protocol
  //
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gChargingAppletProtocolGuid,
                  &mChargingAppletProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get platform setting from setup variable
  //
  VarDataSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mLpmFeature = SetupData.ChargingLpmEnable;
  CriticalBatteryLimitFeature = SetupData.CriticalBatteryLimitFeature;
  CriticalBatteryLimit = SetupData.CriticalBatteryLimit;

  //
  // Check for power button press in the case of power button override shutdown
  //
  Status = CheckWakeSource (&WakeSource);
  if (EFI_ERROR (Status)) {
    WakeSource = 0;
  }
  DEBUG ((EFI_D_INFO, "[S5ChargingEntry] WakeSource is 0x%x\n", WakeSource));
  DEBUG ((EFI_D_INFO, "[S5ChargingEntry] S5Charging Configuration: %d \n", SetupData.ChargingEnable));

  if (SetupData.ChargingEnable == 0) {
    //
    // Handles critical battery level when charging is off
    //
    if (CriticalBatteryLimitFeature == 0x1) {
      DEBUG ((EFI_D_INFO, "CriticalBatteryLimitFeature Enabled \n"));
      Status = GetStateOfCharge (&CurrentCapacity, &CurrentState);
      if (CurrentCapacity <= CriticalBatteryLimit) {
        Print (L"Critical Battery. Booting Halted.\n");
        DEBUG ((EFI_D_INFO, "Critical Battery. Booting Halted.\n"));
        gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
        CpuDeadLoop (); // should never go here...
      }
    }
  } else {
    //
    // ChargingEnable = 1
    //
  }

  GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
  if (ResetVariable.Sign != RESET_SIGN) {
    //
    // Signature NOT valid, clear variable
    //
    ResetVariable.Sign = RESET_SIGN;
    ResetVariable.Reset_Type = 0x0;
    ResetVariable.OS_Reset = 0x0;
    ResetVariable.OS_Shutdown = 0x0;
    ResetVariable.ChargingEnable = 0x0;
    DEBUG ((EFI_D_INFO, "[ResetVariable.ChargingEnable = %d\n", ResetVariable.ChargingEnable));
    SetResetTypeVarible(NVRAM_RESET_VARIABLE_PARAM);
  }

  if (SetupData.ChargingEnable == 0) {
    DEBUG ((EFI_D_INFO, "S5 charging not enabled in setup\r\n"));
    GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    if (ResetVariable.OS_Shutdown != OS_SHUTDOWN) {
      return EFI_SUCCESS; // return immediately if disabled
    }
  } else {
    GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    ResetVariable.Sign = RESET_SIGN;
    ResetVariable.ChargingEnable = SetupData.ChargingEnable;
    SetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    DEBUG ((EFI_D_INFO, "ChargingEnable =  %x \t LPM = %x \t \n", SetupData.ChargingEnable, mLpmFeature));
  }

  if (ResetVariable.Reset_Type == RESET_TYPE) {
    GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    DEBUG ((EFI_D_INFO, "RESET_SIGN %x\n", ResetVariable.Sign));
    DEBUG ((EFI_D_INFO, "RESET_Reset_type %x\n", ResetVariable.Reset_Type));
    ResetVariable.Reset_Type  = 0x0;
    ResetVariable.OS_Shutdown = 0x0;
    ResetVariable.OS_Reset= 0x0;
    SetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    return Status;
  }

  if (ResetVariable.OS_Shutdown == OS_SHUTDOWN) {
    GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    DEBUG ((EFI_D_INFO, "RESET_OS_Shutdown %x\n", ResetVariable.OS_Shutdown));
    ResetVariable.OS_Shutdown = 0x0;
    ResetVariable.OS_Reset= 0x0;
    SetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
    OS_Shutdown = OS_SHUTDOWN;
  } else {
    if (ResetVariable.OS_Reset== OS_RESET) {
      GetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
      DEBUG ((EFI_D_INFO, "RESET_OS_reset %x\n",ResetVariable.OS_Reset));
      ResetVariable.OS_Reset = 0x0;
      SetResetTypeVarible (NVRAM_RESET_VARIABLE_PARAM);
      return Status;
    } else {
#if (defined X64_EFICHARGING_ENABLE) && (X64_EFICHARGING_ENABLE == 1)
      OS_Restart = OS_X64_RESTART;
#endif
    }
  }

  if (OS_Shutdown == OS_SHUTDOWN) {
    if (!CheckForChargerPresence (&Type) || !SetupData.ChargingEnable) {
      // Shutdown immediately.
      Status = EFI_SUCCESS;
      DEBUG ((EFI_D_INFO, "Shutdown system\n"));
      gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
    }
  }

#if (defined X64_EFICHARGING_ENABLE) && (X64_EFICHARGING_ENABLE == 1)
  if ((OS_Restart == OS_X64_RESTART) && ((WakeSource & PMIC_MASK_WAKEUSB) != PMIC_MASK_WAKEUSB)) {
    DEBUG ((EFI_D_INFO, "64-Bit  OS Restart\n"));
    Status = EFI_SUCCESS;
    return Status;
  }
#endif

  //
  // Set the initial state.
  //
  SetActiveState (Initial);

  //
  // Initialize the driver
  //
  Status = InitializeS5Charging ();
  if (Status != EFI_SUCCESS ) {
    return Status;
  }
  DEBUG ((EFI_D_INFO, "[S5ChargingEntry] End\n"));
  return Status;
}
