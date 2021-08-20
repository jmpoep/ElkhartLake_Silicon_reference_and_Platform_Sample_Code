/** @file
  EFI Charging Applet Protocol hardware interface header

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _HARDWARE_INTERFACE_H_
#define _HARDWARE_INTERFACE_H_

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Protocol/ChargingAppletProtocol.h>
#include <Protocol/MpService.h>
#include "DisplayIcon.h"
#include "DummyCharger.h"
#include "EcLiteCharger.h"

#define MAX_CHARGE_CAP            100

//
// Can be added if there are more chargers needed to be implemented.
//
typedef enum {
  ECLITE     = 0,
} CHARGER_ID;

//
// Power button, wake etc. related methods
//
typedef BOOLEAN    (EFIAPI *CHECK_PWRBTN_STATUS)(VOID);
typedef BOOLEAN    (EFIAPI *CHECK_ALTBTN_STATUS)(VOID);
typedef EFI_STATUS (EFIAPI *CHECK_WAKESRC)(UINT8  *WakeCause);

//
// Charging related methods
//
typedef BOOLEAN    (EFIAPI *CHECK_BATTERY_PRESENCE)(VOID);
typedef BOOLEAN    (EFIAPI *CHECK_CHRG_PRESENCE)(CHARGER_TYPE  *Type);
typedef EFI_STATUS (EFIAPI *START_CHARGING)(VOID);
typedef EFI_STATUS (EFIAPI *GET_STATE_OF_CHARGE)(UINT32  *CurrentCapacity, CHARGE_STATE *CurrentState);
typedef EFI_STATUS (EFIAPI *SET_CHARGE_RATE)(UINT32 ChargeRate);
typedef EFI_STATUS (EFIAPI *GET_BATTERY_INFO)(BATTERY_INFO  *BatteryInfo, BOOLEAN  *CapacityReadable, BATTERY_VOLTAGE  *BatteryVoltageLevel,  BATTERY_CAPACITY *BatteryCapacityLevel);

//
// Display Interface methods
//
typedef EFI_STATUS (EFIAPI *DISPLAY_CHARGING_INDICATION)(UINT32 SOC);

typedef struct {
  UINTN                         ClockTicks;
  DISPLAY_CHARGING_INDICATION   DisplayChargingIndication;
} DisplayInterface;

//
// Abstract Charger interface.
// Use "InitializeHardwareInterfaces" function to create a proper charger object.
//
typedef struct {
  CHECK_BATTERY_PRESENCE        CheckForBatteryPresence;
  CHECK_CHRG_PRESENCE           CheckForChargerPresence;
  START_CHARGING                StartCharging;
  GET_STATE_OF_CHARGE           GetStateOfCharge;
  SET_CHARGE_RATE               SetChargeRate;
  GET_BATTERY_INFO              GetBatteryInfo;
} ChargerInterface;


//
// Alternate hardware connected buttons interface.
// To consider the possibility of buttons apart connected to hardware
// for power button press.
//
typedef struct {
  CHECK_PWRBTN_STATUS  CheckPowerButtonStatus;
  CHECK_ALTBTN_STATUS  CheckInputButtonStatus; // alternate input button
} InputButtonInterface;

//
// global objects required for charging.
//
ChargerInterface           mChargerInterface;
InputButtonInterface       mInputButtonInterface;
DisplayInterface           mDisplayInterface;
UINTN                      mMaxDisplayClockTicks;


//
// Function Declarations
//
EFI_STATUS
EFIAPI
SetCpuVid (
  IN VOID        *Buffer
  );

EFI_STATUS
EFIAPI
SetCpuInLfm (
  VOID
  );

VOID
EFIAPI
SetFuncDisable (
  VOID
  );

VOID
EFIAPI
PutPchIpInD3 (
  VOID
  );

//
// Initialize the input button interface.
//
EFI_STATUS
InitializeInputButtonInterface (
  VOID
  );

//
// CheckPowerButtonStatus: Abstraction for getting the status of the location-dependent
// power button.
//
BOOLEAN
CheckPowerButtonStatus (
  VOID
  );

//
// CheckWakeSource: Abstraction for getting the wake source.
//
EFI_STATUS
CheckWakeSource (
  UINT8    *Source
  );

//
// CheckForBatteryPresence: Abstraction for detecting the presence of the battery.
//
BOOLEAN
EFIAPI
CheckForBatteryPresence (
  VOID
  );

//
// CheckForChargerPresence: Abstraction for detecting the presence of the charger.
//
BOOLEAN
EFIAPI
CheckForChargerPresence (
  CHARGER_TYPE    *Type
  );

//
// StartCharging: Abstraction for starting the charging process.
//
EFI_STATUS
EFIAPI
StartCharging (
  VOID
  );

//
// SetChargeRate: Abstraction for setting the Charge current.
//
EFI_STATUS
EFIAPI
SetRateOfCharge (
  IN UINT32  ChargeRate
  );

//
// GetStateOfCharge: Abstraction for getting the State of Charge
//
EFI_STATUS
EFIAPI
GetStateOfCharge (
  OUT UINT32          *CurrentCapacity,
  OUT CHARGE_STATE    *CurrentState
);


//
// allocation functions per hardware
//
VOID
InitializeHardwareInterfaces (
  CHARGER_ID        Id
  );

#endif
