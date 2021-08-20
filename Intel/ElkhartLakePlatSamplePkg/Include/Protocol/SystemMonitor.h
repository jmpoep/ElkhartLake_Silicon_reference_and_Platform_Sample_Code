/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef _SYSTEM_MONITOR_H_
#define _SYSTEM_MONITOR_H_


// Device Types
#define HECETA6x    0x01

// Company IDs
#define NATIONAL    0x01
#define SMSC        0x5C
#define ADI         0x41

//Number of Monitor Device Supported
#define MAX_MONITOR_DEVICE 0x03

#define EC_REG_TSR1_LSB                  145
#define EC_REG_TSR2_LSB                  147
#define EC_REG_TSR3_LSB                  149
#define EC_REG_TSR4_LSB                  151
#define EC_REG_TSR5_LSB                  153

#define EC_REG_CPU_FAN_SPEED             115
#define EC_REG_PCH_DTS_TEMP              129
#define EC_REG_TS_ON_DIMM0_TEMP          133
#define EC_REG_TS_ON_DIMM1_TEMP          134

// Structure used to return system status
// NOTE:
//   All voltages have been multiplied by 1000 so that integer data
//   types can be used.  To find the actual voltage divide the voltage
//   data member by 1000.
typedef struct {
  UINTN   V1_5;
  UINTN   Vccp;
  UINTN   V3_3;
  UINTN   V5;
  UINTN   V12;
  INT8    ProcessorTemp;
  INT8    InternalTemp;
  INT8    RemoteTemp;
  UINT16  Tach1;
  UINT16  Tach2;
  UINT16  Tach3;
  UINT16  Tach4;
  UINT8   CurrentPwm1;
  UINT8   CurrentPwm2;
  UINT8   CurrentPwm3;
} EFI_SYSTEM_MONITOR_INFO;

typedef struct {
  INT16     EC_TSR1;
  INT16     EC_TSR2;
  INT16     EC_TSR3;
  INT16     EC_TSR4;
  INT16     EC_TSR5;
  INT16     EC_TSR6;
  INT16     EC_TSR7;
  INT16     EC_TSR8;

  INT16    CPUFanSpeed;
  INT8     PCHDTSTemp;
  INT8     TSonDimm0Temp;
  INT8     TSonDimm1Temp;
} MOBILE_SYSTEM_MONITOR_INFO;

typedef struct {
  UINT8   MonitorDeviceType;
  UINT8   CompanyId;
  UINT8   DeviceVersion;
  UINT8   DeviceRevision;
  UINT8   DeviceSmbusAddress;
} EFI_MONITOR_DEVICE_INFO;

// Protocol function prototypes
typedef
EFI_STATUS
(EFIAPI *EFI_GET_SYSTEM_MONITOR_VALUES) (
    IN  UINT8                       DeviceSmbusAddress,
    IN  UINT16                      KeyValue,
    OUT EFI_SYSTEM_MONITOR_INFO*    MonitorValues
  );

typedef
EFI_STATUS
(EFIAPI *EFI_ACCURATE_TACH_SETTINGS) (
  IN UINT8    DeviceSmbusAddress,
  IN BOOLEAN  EnablePws
  );

// Protocol Definition
typedef struct {
  UINT8                         DeviceCount;
  EFI_MONITOR_DEVICE_INFO       DeviceInfoList[MAX_MONITOR_DEVICE];
  EFI_GET_SYSTEM_MONITOR_VALUES GetMonitorValues;
  EFI_ACCURATE_TACH_SETTINGS    AccurateTachSettings;
} EFI_SYSTEM_MONITOR_PROTOCOL;

#endif
