/** @file
  Provides Charging Applet Protocol definitions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#ifndef _CHARGING_APPLET_PROTOCOL_H_
#define _CHARGING_APPLET_PROTOCOL_H_

#define CHARGING_APPLET_PROTOCOL_GUID  \
  {0x810139A7, 0x133E, 0x44A1, 0xAC, 0x6F, 0xD2, 0x04, 0x62, 0x13, 0x9D, 0x90}

typedef struct _CHARGING_APPLET_PROTOCOL CHARGING_APPLET_PROTOCOL;

//
// Charger Type
//
typedef enum {
  SdpCharger,
  DcpCharger,
  CdpCharger,
  AcaCharger,
  AdapCharger,
  WirelessCharger,
  ChargerOther,
  ChargerUndefined
} CHARGER_TYPE;

//
// Current Charging State.
//
typedef enum {
  ChargeOn,
  ChargeFull,
  NoCharge
} CHARGE_STATE;

//
// Battery Information
//
typedef struct {
  UINT16  DesignCapacity;
} BATTERY_INFO;

typedef UINT8   BATTERY_CAPACITY;
typedef UINT16  BATTERY_VOLTAGE;

//
// Prototypes
//
typedef
EFI_STATUS
(EFIAPI *CHARGING_APPLET_GET_CHARGER_TYPE) (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT CHARGER_TYPE                 *ChargerType
  );

typedef
EFI_STATUS
(EFIAPI *CHARGING_APPLET_SET_CHARGE_RATE) (
  IN CHARGING_APPLET_PROTOCOL      *This,
  IN UINT32                        ChargeRate
  );

typedef
EFI_STATUS
(EFIAPI *CHARGING_APPLET_GET_CURRENT_CHARGE_STATE) (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT UINT32                       *CurrentCapacity,
  OUT CHARGE_STATE                 *CurrentState
  );

typedef
EFI_STATUS
(EFIAPI *CHARGING_APPLET_GET_BATTERY_INFO) (
  IN CHARGING_APPLET_PROTOCOL      *This,
  OUT BATTERY_INFO                 *BatteryInfo,
  OUT BOOLEAN                      *BatteryPresent,
  OUT BOOLEAN                      *BatteryValid,
  OUT BOOLEAN                      *CapacityReadable,    // based on FG.STATUS.POR
  OUT BATTERY_VOLTAGE              *BatteryVoltageLevel, // mVolts
  OUT BATTERY_CAPACITY             *BatteryCapacityLevel // Percentage
  );

typedef
EFI_STATUS
(EFIAPI *CHARGING_APPLET_PUT_PLATFORM_LOW_POWER_MODE) (
  IN CHARGING_APPLET_PROTOCOL      *This,
  IN BOOLEAN                       PowerSaveMode,
  IN BOOLEAN                       DisplayPMState
  );


//
//  struct CHARGING_APPLET_PROTOCOL
//
struct _CHARGING_APPLET_PROTOCOL {
  CHARGING_APPLET_GET_CHARGER_TYPE              GetChargerType;
  CHARGING_APPLET_SET_CHARGE_RATE               SetChargeRate;
  CHARGING_APPLET_GET_CURRENT_CHARGE_STATE      GetCurrentChargeState;
  CHARGING_APPLET_GET_BATTERY_INFO              GetBatteryInfo;
  CHARGING_APPLET_PUT_PLATFORM_LOW_POWER_MODE   PutPlatformToLowPowerMode;
  UINT16                                        MajorRevision;
  UINT16                                        MinorRevision;
};

extern EFI_GUID gChargingAppletProtocolGuid;

#endif
