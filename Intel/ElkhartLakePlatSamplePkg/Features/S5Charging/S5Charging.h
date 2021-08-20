/**@file
  This file is for S5 charging

@copyright
 Copyright (c) 1999 - 2015 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.
 This file contains an 'Intel Peripheral Driver' and is uniquely
 identified as "Intel Reference Module" and is licensed for Intel
 CPUs and chipsets under the terms of your license agreement with
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification
**/

#ifndef _S5CHARGING_DXE_H_
#define _S5CHARGING_DXE_H_

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <CpuRegs.h>
#include "StateMachine.h"
#include "HardwareInterface.h"
#include <PlatformBoardId.h>
#include <SetupVariable.h>

#define RESET_TYPE                              0xAA
#define OS_RESET                                0xAA
#define OS_SHUTDOWN                             0xBB

#define RESET_SIGN                              0x11223344
#define OS_X64_RESTART                          0xAA

#define COLD_OFF_POWER_BUTTON                   0x11
#define POWER_BUTTON_WAKE                       0x1

#define POWER_BUTTON_ON_STATUS                  0xAA
#define PBOFF_PBBTN                             0x81
#define COLDOFF_PBBTN                           0x41
#define FORCED_POWER_BUTTON_OFF                 0x80
#define FORCED_POWER_BUTTON_STATUS              0xAB

#define POWER_BUTTON_ON_STATUS                  0xAA
#define OS_SHUTDOWN_STATUS                      0xBB
#define USB_WAKE_STATUS                         0x02

#define NVRAM_DYNAMIC_BAT_PARAM_HR              2
#define NVRAM_DYNAMIC_BAT_PARAM                 1
#define NVRAM_RESET_VARIABLE_PARAM              0

#define REG_PARM                                L"Regparm"

extern EFI_GUID  gSfiveChargingGuid;
extern EFI_GUID  gResetTypeGuid;

typedef struct {
  UINT32 signature;
  UINT32 fcc;               //Full charge capacity
  UINT16 cycle_count;       //Number cycle the battery fully charged
  UINT32 cycle_q;
  UINT16 learned_cycle;     //NUmbe of cycle used by the Software fuel gauge algorithm
  UINT16 c_min_rate;        //Charge minimum rate
  UINT32 rmc;               //Remaining capacity
  UINT32 nac;               //Net available capacity
  UINT32 overcharge_q;
} BATT_CONF;


typedef struct {
  UINT16 Rcomp0;         // used for battery characterization
  UINT16 Tempco;         // used for battery characterization
  UINT16 Iavg_empty;     // used for battery characterization
  UINT16 FullCapNom;     // This register holds the calculated full capacity of the cell,not including temperature and charger tolerance.
  UINT16 Qrtable_00;     // used for battery characterization
  UINT16 Qrtable_10;     // used for battery characterization
  UINT16 Qrtable_20;     // used for battery characterization
  UINT16 Qrtable_30;     // used for battery characterization
  UINT16 FullCap;        //Full charge capacity
  UINT16 Cycles;         //Number cycle the battery fully charged
} BATT_CONF_HR;


typedef struct {
  UINT32  Sign;
  UINT16  Reset_Type;
  UINT16  OS_Reset;
  UINT16  OS_Shutdown;
  UINT16  ChargingEnable;
} Reset_Shutdown;

//
// Initialize the state machine.
//
EFI_STATUS
EFIAPI
InitS5ChargingStateMachine (
  VOID
  );

//
// Callback for handling the timer event.
//
VOID
EFIAPI
ChargingTimerHandler (
  IN EFI_EVENT    Event,
  IN VOID         *Context
);

EFI_STATUS
EFIAPI
GetResetTypeVarible (
  UINTN    VariableType
  );

EFI_STATUS
EFIAPI
SetResetTypeVarible (
  UINTN    VariableType
  );

#endif
