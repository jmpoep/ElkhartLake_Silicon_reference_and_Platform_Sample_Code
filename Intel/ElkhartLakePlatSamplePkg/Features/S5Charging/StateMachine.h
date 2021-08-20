/** @file
  This file is for S5 charging flow control.

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
#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

//
// State Of Charge related defines
//
#define MAX_STATE_OF_CHARGE             100
#define CRITICAL_STATE_OF_CHARGE          4


#define RCOMP_0                         0x38
#define TEMPCO                         0x39
#define IAVG_EMPTY                     0x36
#define FULLCAPNOM                     0x23
#define QRTABLE_00                     0x12
#define QRTABLE_10                     0x22
#define QRTABLE_20                     0x32
#define QRTABLE_30                     0x42
#define FULLCAP                        0x10
#define CYCLES                         0x17

//
// Enumeration of the states of the S5Charging State Machine.
//
typedef enum {
  Initial = 0,
  Charging,
  Charged,
  PowerUp
} STATE_TYPE;

//
// Applet State.
// This struct has been created so that the state and any future state-related
// items can be aggregated in the same data struct.
//
typedef struct {
  STATE_TYPE    CurrentState;
  EFI_EVENT     TimerEvent;
  EFI_EVENT     ExitTimerEvent;
} APPLET_STATE;

APPLET_STATE  mChargingState;


///
/// Set the state
///
VOID
SetActiveState (
  STATE_TYPE    State
  );

///
/// Execute the actions for state "Initial"
///
EFI_STATUS
ExecInitialStateActions (
  VOID
  );

///
/// Execute the actions for state "Charging"
///
EFI_STATUS
ExecChargingStateActions (
  VOID
  );

///
/// Execute the actions for state "Charged"
///
EFI_STATUS
ExecChargedStateActions (
  VOID
  );

///
/// Execute the actions for state "PowerUp"
///
EFI_STATUS
ExecPowerUpStateActions (
  VOID
  );

#endif
