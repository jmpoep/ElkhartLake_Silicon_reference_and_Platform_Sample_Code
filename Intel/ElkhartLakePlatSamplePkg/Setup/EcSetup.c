/** @file
  Extracts system info from EC, for Mobile systems.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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


#include <SetupPrivate.h>
#include <Library/EcMiscLib.h>

/**

  @param[in]  Reg
  @param[out] RetValue

  @retval    EFI_STATUS
**/
EFI_STATUS
ReadEcRegister(
    IN  UINT8  Reg,
    OUT UINT8  *RetValue
)
{
  EFI_STATUS Status;
  UINT8      DataBuffer[1];

  DataBuffer[0] = Reg;
  Status = ReadEcRam (DataBuffer);
  if (Status == EFI_SUCCESS) {
    *RetValue = DataBuffer[0];
  }
  return Status;
}

/**

@param[in]  RegLsb   LSB Register value.
@param[out] RetValue Temperature in 10ths of degree Celsius.

@retval     EFI_STATUS
**/

EFI_STATUS
GetSensorTemperatures(
    IN UINT8 RegLsb,
    OUT UINT16 *RetValue
)
{
  EFI_STATUS Status;
  UINT8      DataBuffer[2];
  DataBuffer[0] = RegLsb; // Read LSB
  Status = ReadEcRam(&DataBuffer[0]);

  DataBuffer[1] = RegLsb +1; // Read MSB
  Status = ReadEcRam(&DataBuffer[1]);

  *RetValue = (DataBuffer[0] | (DataBuffer[1] << 8));
   return Status;
}

/**
  Returns system monitor values from the EC.

  @param[in]  KeyValue
  @param[out] MonitorValues  Pointer to a structure to return the monitor values in.

  @retval     EFI_INVALID_PARAMETER
  @retval     EFI_SUCCESS
**/
EFI_STATUS
GetSystemMonitorValues (
    IN  UINT16                             KeyValue,
    OUT MOBILE_SYSTEM_MONITOR_INFO*        MonitorValues
  )
{
  UINT16                    Data16;
  UINT8                     Data;
  UINT8                     Register;

  // Check input parameters
  if (MonitorValues == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (!PcdGetBool (PcdEcPresent)) {
    return EFI_SUCCESS;
  }

  switch(KeyValue)
  {
    case THERMAL_SENSOR_1_KEY:
    {
      //
      // Read Thermal Sensor from EC
      //
      Register = EC_REG_TSR1_LSB;
      Data = 0;
      GetSensorTemperatures(Register, &Data16);
      MonitorValues->EC_TSR1 = Data16;
      break;
    }
    case THERMAL_SENSOR_2_KEY:
    {
      //
      // Read Thermal Sensor from EC
      //
      Register = EC_REG_TSR2_LSB;
      Data = 0;
      GetSensorTemperatures (Register, &Data16);
      MonitorValues->EC_TSR2 = Data16;
      break;
    }
    case THERMAL_SENSOR_3_KEY:
    {
      //
      // Read Thermal Sensor from EC
      //
      Register = EC_REG_TSR3_LSB;
      Data = 0;
      GetSensorTemperatures (Register, &Data16);
      MonitorValues->EC_TSR3 = Data16;
      break;
    }
    case THERMAL_SENSOR_4_KEY:
    {
      //
      // Read Thermal Sensor from EC
      //
      Register = EC_REG_TSR4_LSB;
      Data = 0;
      GetSensorTemperatures (Register, &Data16);
      MonitorValues->EC_TSR4 = Data16;
      break;
    }
    case THERMAL_SENSOR_5_KEY:
    {
      //
      // Read Thermal Sensor from EC
      //
      Register = EC_REG_TSR5_LSB;
      Data = 0;
      GetSensorTemperatures (Register, &Data16);
      MonitorValues->EC_TSR5 = Data16;
      break;
    }
    case CPU_FAN_KEY :
    {
      //
      // Read CPU Fan Speed from EC
      //
      Register = EC_REG_CPU_FAN_SPEED + 1;
      ReadEcRegister (Register, &Data);
      MonitorValues->CPUFanSpeed = Data;
      Register = EC_REG_CPU_FAN_SPEED;
      ReadEcRegister (Register, &Data);
      MonitorValues->CPUFanSpeed = (MonitorValues->CPUFanSpeed << 8) + Data;
      break;
     }
    case PCH_DTS_TEMP_KEY :
    {
      //
      // Read PCH DTS Temp from EC
      //
      Register = EC_REG_PCH_DTS_TEMP;
      ReadEcRegister (Register, &Data);
      MonitorValues->PCHDTSTemp = Data;
          break;
        }
    case TS_ON_DIMM0_TEMP_KEY :
    {
      //
      // Read TS-on-DIMM0 Temp from EC
      //
      Register = EC_REG_TS_ON_DIMM0_TEMP;
      ReadEcRegister (Register, &Data);
      MonitorValues->TSonDimm0Temp = Data;
          break;
        }
    case TS_ON_DIMM1_TEMP_KEY :
    {
      //
      // Read TS-on-DIMM1 Temp from EC
      //
      Register = EC_REG_TS_ON_DIMM1_TEMP;
      ReadEcRegister (Register, &Data);
      MonitorValues->TSonDimm1Temp = Data;
      break;
    }
    default:
    break;
  }

  return EFI_SUCCESS;
}


/**

  @param[in] HiiHandle
  @param[in] Class
**/
VOID
InitHhmMobileStrings (
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class
  )
{
  UINT16                        Value1;
  UINT16                        Value2;
  MOBILE_SYSTEM_MONITOR_INFO    MonitorValues;

  if (Class != ADVANCED_FORM_SET_CLASS) {
    return ;
  }

  GetSystemMonitorValues (THERMAL_SENSOR_1_KEY, &MonitorValues);
  GetSystemMonitorValues (THERMAL_SENSOR_2_KEY, &MonitorValues);
  GetSystemMonitorValues (THERMAL_SENSOR_3_KEY, &MonitorValues);
  GetSystemMonitorValues (THERMAL_SENSOR_4_KEY, &MonitorValues);
  GetSystemMonitorValues (THERMAL_SENSOR_5_KEY, &MonitorValues);

  GetSystemMonitorValues (CPU_FAN_KEY, &MonitorValues);
  GetSystemMonitorValues (PCH_DTS_TEMP_KEY, &MonitorValues);
  GetSystemMonitorValues (TS_ON_DIMM0_TEMP_KEY, &MonitorValues);
  GetSystemMonitorValues (TS_ON_DIMM1_TEMP_KEY, &MonitorValues);

  Value1 = (UINT16)(MonitorValues.EC_TSR1 / 10);
  Value2 = (UINT16)(MonitorValues.EC_TSR1 % 10);
  InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_1_VALUE), L"%d.%01d C", Value1, Value2);

  Value1 = (UINT16)(MonitorValues.EC_TSR2 / 10);
  Value2 = (UINT16)(MonitorValues.EC_TSR2 % 10);
  InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_2_VALUE), L"%d.%01d C", Value1, Value2);

  Value1 = (UINT16)(MonitorValues.EC_TSR3 / 10);
  Value2 = (UINT16)(MonitorValues.EC_TSR3 % 10);
  InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_3_VALUE), L"%d.%01d C", Value1, Value2);

  Value1 = (UINT16)(MonitorValues.EC_TSR4 / 10);
  Value2 = (UINT16)(MonitorValues.EC_TSR4 % 10);
  InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_4_VALUE), L"%d.%01d C", Value1, Value2);

  Value1 = (UINT16)(MonitorValues.EC_TSR5 / 10);
  Value2 = (UINT16)(MonitorValues.EC_TSR5 % 10);
  InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_5_VALUE), L"%d.%01d C", Value1, Value2);

  InitString(HiiHandle, STRING_TOKEN(STR_CPU_FAN_VALUE), L"%d rpm", MonitorValues.CPUFanSpeed);
  InitString(HiiHandle, STRING_TOKEN(STR_PCH_DTS_TEMP_VALUE), L"%d C", MonitorValues.PCHDTSTemp);

}


/**

  @param[in] HiiHandle
  @param[in] Class
  @param[in] SubClass
  @param[in] Key
**/
VOID HhmMobileCallBack(
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16 Class,
  IN UINT16 SubClass,
  IN UINT16 Key
  )
{
    MOBILE_SYSTEM_MONITOR_INFO       MonitorValues;
    UINT16                        Value1;
    UINT16                        Value2;

    GetSystemMonitorValues (Key, &MonitorValues);

    switch(Key)
    {
        case THERMAL_SENSOR_1_KEY:
        {
            Value1 = (UINT16)(MonitorValues.EC_TSR1 / 10);
            Value2 = (UINT16)(MonitorValues.EC_TSR1 % 10);
            InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_1_VALUE), L"%d.%01d C", Value1, Value2);
            break;
        }
        case THERMAL_SENSOR_2_KEY:
        {
            Value1 = (UINT16)(MonitorValues.EC_TSR2 / 10);
            Value2 = (UINT16)(MonitorValues.EC_TSR2 % 10);
            InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_2_VALUE), L"%d.%01d C", Value1, Value2);
            break;
        }
        case THERMAL_SENSOR_3_KEY:
        {
            Value1 = (UINT16)(MonitorValues.EC_TSR3 / 10);
            Value2 = (UINT16)(MonitorValues.EC_TSR3 % 10);
            InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_3_VALUE), L"%d.%01d C", Value1, Value2);
            break;
        }
        case THERMAL_SENSOR_4_KEY:
        {
            Value1 = (UINT16)(MonitorValues.EC_TSR4 / 10);
            Value2 = (UINT16)(MonitorValues.EC_TSR4 % 10);
            InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_4_VALUE), L"%d.%01d C", Value1, Value2);
            break;
        }
        case THERMAL_SENSOR_5_KEY:
        {
            Value1 = (UINT16)(MonitorValues.EC_TSR5 / 10);
            Value2 = (UINT16)(MonitorValues.EC_TSR5 % 10);
            InitString(HiiHandle, STRING_TOKEN(STR_THERMAL_SENSOR_5_VALUE), L"%d.%01d C", Value1, Value2);
            break;
        }
        case CPU_FAN_KEY :
        {
            InitString(HiiHandle, STRING_TOKEN(STR_CPU_FAN_VALUE), L"%d rpm", MonitorValues.CPUFanSpeed);
            break;
        }
        case PCH_DTS_TEMP_KEY :
        {
            InitString(HiiHandle, STRING_TOKEN(STR_PCH_DTS_TEMP_VALUE), L"%d C", MonitorValues.PCHDTSTemp);
            break;
        }
        case TS_ON_DIMM0_TEMP_KEY :
        {
            InitString(HiiHandle, STRING_TOKEN(STR_TS_ON_DIMM0_TEMP_VALUE), L"%d C", MonitorValues.TSonDimm0Temp);
            break;
        }
        case TS_ON_DIMM1_TEMP_KEY :
        {
            InitString(HiiHandle, STRING_TOKEN(STR_TS_ON_DIMM1_TEMP_VALUE), L"%d C", MonitorValues.TSonDimm1Temp);
            break;
        }
  }
}
