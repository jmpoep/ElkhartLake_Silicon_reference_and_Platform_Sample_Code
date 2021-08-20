/** @file
  Extracts Voltage info from EC.

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
#include <Library/EcLib.h>
//
// Voltage define
//
#define  Voltage5VH          0xC9
#define  Voltage5VL          0xCA
#define  Voltage12VH         0xCB
#define  Voltage12VL         0xCC
#define  Voltage3_3VH        0xCD
#define  Voltage3_3VL        0xCE
#define  Voltage1_05VH       0xCF
#define  Voltage1_05VL       0xD0
//
//  formula Parameter define
//
#define  Vef                 3222   // 3.3/1024(Vref/1024) = 0.003222
#define  Scaling_Factor_12V  401    // 12V HW Scaling Factor
#define  Scaling_Factor_5V   200    // 5V HW Scaling Factor

EFI_STATUS
ReadEcRegister(
  IN  UINT8  Reg,
  OUT UINT8  *RetValue
);


/**
  Returns Voltage values from the EC.

  @param[in]  KeyValue
  @param[out] EfiMonitorValues      Pointer to a structure to return the monitor values in.

  @retval     EFI_INVALID_PARAMETER
  @retval     EFI_SUCCESS
**/
EFI_STATUS
GetEfiSystemMonitorValues (
  IN  UINT16                             KeyValue,
  OUT EFI_SYSTEM_MONITOR_INFO*           EfiMonitorValues
  )
{
  UINT8                     Data;
  UINT16                    Buffer;
  //
  // Check input parameters
  //
  if (EfiMonitorValues == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (!PcdGetBool (PcdEcPresent)) {
    return EFI_SUCCESS;
  }

  switch(KeyValue) {
  case VOLT_5V_KEY :
    {
      //
      // get 5V High Byte
      //
      ReadEcRegister (Voltage5VH, &Data);
      Buffer = Data * 0x100;
      //
      // get 5V low Byte
      //
      ReadEcRegister (Voltage5VL, &Data);
      //
      // Raw value = High Byte + Low Byte
      //
      Buffer = Buffer + Data;
      //
      // 5V : 3.3/1024(Vref/1024) * 2(5V HW Scaling Factor)* Raw value
      //
      EfiMonitorValues->V5 = ((Vef * Scaling_Factor_5V * Buffer) / 100000);
      break;
    }
  case VOLT_12V_KEY :
    {
      //
      // get 12V High Byte
      //
      ReadEcRegister (Voltage12VH, &Data);
      Buffer = Data * 0x100;
      //
      // get 12V low Byte
      //
      ReadEcRegister (Voltage12VL, &Data);
      //
      // Raw value = High Byte + Low Byte
      //
      Buffer = Buffer + Data;
      //
      // 12V : 3.3/1024(Vref/1024) * 401(12V HW Scaling Factor)* Raw value
      //
      EfiMonitorValues->V12 = ((Vef * Scaling_Factor_12V * Buffer) / 100000);
      break;
    }
  case VOLT_3_3V_KEY :
      {
      //
      // get 3.3V High Byte
      //
      ReadEcRegister (Voltage3_3VH, &Data);
      Buffer = Data * 0x100;
      //
      // get 3.3V low Byte
      //
      ReadEcRegister (Voltage3_3VL, &Data);
      //
      // Raw value = High Byte + Low Byte
      //
      Buffer = Buffer + Data;
      //
      // 3.3V : 3.3/1024(Vref/1024) * 2(HW scaling factor)* Raw value
      //
      EfiMonitorValues->V3_3 = ((Vef * Scaling_Factor_5V * Buffer) / 100000);
      break;
    }
  case VOLT_1_5V_KEY :
    {
      //
      // get 1.5V High Byte
      //
      ReadEcRegister (Voltage1_05VH, &Data);
      Buffer = Data * 0x100;
      //
      // get 3.3V low Byte
      //
      ReadEcRegister (Voltage1_05VL, &Data);
      //
      // Raw value = High Byte + Low Byte
      //
      Buffer = Buffer + Data;
      //
      // 1.5V : 3.3/1024(Vref/1024) * 2(HW scaling factor)* Raw value
      //
      EfiMonitorValues->V1_5 = ((Vef * Scaling_Factor_5V * Buffer) / 100000);
      break;
    }
  }
  return EFI_SUCCESS;
}


/**
  Function to Initialise Setup strings related to EC

  @param[in] HiiHandle  Handle to HII database
  @param[in] Class      Indicates the setup class
**/
VOID
InitHhmStrings (
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class
  )
{
  EFI_SYSTEM_MONITOR_INFO        EfiMonitorValues;
  UINT16                         value1;
  UINT16                         value2;

  if (Class != ADVANCED_FORM_SET_CLASS) {
    return ;
  }

  GetEfiSystemMonitorValues (VOLT_1_5V_KEY, &EfiMonitorValues);
  GetEfiSystemMonitorValues (VOLT_3_3V_KEY, &EfiMonitorValues);
  GetEfiSystemMonitorValues (VOLT_5V_KEY, &EfiMonitorValues);
  GetEfiSystemMonitorValues (VOLT_12V_KEY, &EfiMonitorValues);
  //
  // 5 Volt
  //
  value1  = (UINT16) (EfiMonitorValues.V5 / 1000);
  value2  = (UINT16) (EfiMonitorValues.V5 % 1000);
  InitString (HiiHandle,STRING_TOKEN (STR_V5P_VALUE), L"%d.%03d V", value1, value2);
  //
  // 3.3 Volt
  //
  value1  = (UINT16) (EfiMonitorValues.V3_3 / 1000);
  value2  = (UINT16) (EfiMonitorValues.V3_3 % 1000);
  InitString (HiiHandle,STRING_TOKEN (STR_V3_3P_VALUE), L"%d.%03d V", value1, value2);
  //
  // 1.5 Volt
  //
  value1  = (UINT16) (EfiMonitorValues.V1_5 / 1000);
  value2  = (UINT16) (EfiMonitorValues.V1_5 % 1000);
  InitString (HiiHandle,STRING_TOKEN (STR_V1_5P_VALUE), L"%d.%03d V", value1, value2);
  //
  // 12 Volt
  //
  value1  = (UINT16) (EfiMonitorValues.V12 / 1000);
  value2  = (UINT16) (EfiMonitorValues.V12 % 1000);
  InitString (HiiHandle,STRING_TOKEN (STR_V12P_VALUE), L"%d.%03d V", value1, value2);
}


/**
  Call Back function for Setup key change

  @param[in] HiiHandle  Handle to HII database
  @param[in] Class      Indicates the setup class
  @param[in] SubClass   Indicates setup Subclass
  @param[in] Key        Key of Setup token
**/
VOID
HhmCallBack(
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16 Class,
  IN UINT16 SubClass,
  IN UINT16 Key
  )
{
  EFI_SYSTEM_MONITOR_INFO        EfiMonitorValues;
  UINT16                         value1;
  UINT16                         value2;

  GetEfiSystemMonitorValues (Key, &EfiMonitorValues);

  switch(Key) {
  case VOLT_5V_KEY :
    {
      value1 = (UINT16) (EfiMonitorValues.V5 / 1000);
      value2 = (UINT16) (EfiMonitorValues.V5 % 1000);
      InitString (HiiHandle,STRING_TOKEN (STR_V5P_VALUE), L"%d.%03d V", value1, value2);
      break;
    }
  case VOLT_12V_KEY :
    {
      value1 = (UINT16) (EfiMonitorValues.V12 / 1000);
      value2 = (UINT16) (EfiMonitorValues.V12 % 1000);
      InitString (HiiHandle,STRING_TOKEN (STR_V12P_VALUE), L"%d.%03d V", value1, value2);
      break;
    }
  case VOLT_3_3V_KEY :
    {
      value1 = (UINT16) (EfiMonitorValues.V3_3 / 1000);
      value2 = (UINT16) (EfiMonitorValues.V3_3 % 1000);
      InitString (HiiHandle,STRING_TOKEN (STR_V3_3P_VALUE), L"%d.%03d V", value1, value2);
      break;
    }
  case VOLT_1_5V_KEY :
    {
      value1 = (UINT16) (EfiMonitorValues.V1_5 / 1000);
      value2 = (UINT16) (EfiMonitorValues.V1_5 % 1000);
      InitString (HiiHandle,STRING_TOKEN (STR_V1_5P_VALUE), L"%d.%03d V", value1, value2);
      break;
    }
  }
}
