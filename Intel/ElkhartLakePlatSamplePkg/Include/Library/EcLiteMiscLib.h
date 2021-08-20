/** @file
  EcLite miscellaneous library functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017- 2019 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef _BASE_ECLITE_MISC_LIB_H_
#define _BASE_ECLITE_MISC_LIB_H_

//
// Include files
//
#include <Base.h>
#include <Uefi.h>
#include <Library/EcLiteLib.h>

/**
  Set Rate of charge for Charger Fuel Gauge 1

  @param[in]  DataBuffer          Rate of charge
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
SetCharger1ChargeRate (
  IN  OUT UINT16   *DataBuffer
);

/**
  Set Rate of charge for Charger Fuel Gauge 2

  @param[in]  DataBuffer          Rate of charge
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
SetCharger2ChargeRate (
  IN  UINT16   *DataBuffer
);

/**
  Get Battery 1 Current State
  Bit values
    Bit [0] - 1 indicates the battery is discharging.
    Bit [1] - 1 indicates the battery is charging.
    Bit [2] - 1 indicates the battery is in the critical energy state.

  Notice that the Charging bit and the Discharging bit are mutually exclusive and must not both be set at the same time. Even in critical state,
  hardware should report the corresponding charging/discharging state.

  @param[in]  DataBuffer          Current State
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery1CurrentState (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 2 Current State
  Bit values
    Bit [0] - 1 indicates the battery is discharging.
    Bit [1] - 1 indicates the battery is charging.
    Bit [2] - 1 indicates the battery is in the critical energy state.

  Notice that the Charging bit and the Discharging bit are mutually exclusive and must not both be set at the same time. Even in critical state,
  hardware should report the corresponding charging/discharging state.

  @param[in]  DataBuffer          Current State
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery2CurrentState (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 1 Design Capacity

  @param[in]  DataBuffer          Design Capacity
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery1DesignCapacity (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 2 Design Capacity

  @param[in]  DataBuffer          Design Capacity
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery2DesignCapacity (
  IN  OUT UINT16   *DataBuffer
);
/**
  Get Battery 1 Voltage Level

  @param[in]  DataBuffer          Voltage Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery1VoltageLevel (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 2 Voltage Level

  @param[in]  DataBuffer          Voltage Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery2VoltageLevel (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 1 Remaining Capacity Level

  @param[in]  DataBuffer          Capacity Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery1RemainingCapacityLevel (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 2 Remaining Capacity Level

  @param[in]  DataBuffer          Capacity Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery2RemainingCapacityLevel (
 IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 1 Full Charge Capacity Level

  @param[in]  DataBuffer          Capacity Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery1FullChargeCapacityLevel (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get Battery 2 Full Charge Capacity Level

  @param[in]  DataBuffer          Capacity Level
  @retval     EFI_SUCCESS         Command success
  @retval     EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
GetBattery2Percentage (
  IN  OUT UINT16   *DataBuffer
);

/**
  Get power state from EcLite Firmware. If power state cannot be determined, battery powered is assumed.

  @param  TRUE         AC powered
  @param  FALSE        Battery powered
**/
BOOLEAN
PowerStateIsAc_EcLite (
  VOID
);

/**
  Get Ucsi Revision.

  @retval  Data        Version number
**/
UINT16
GetUcsiRevision (
  VOID
);
#endif
