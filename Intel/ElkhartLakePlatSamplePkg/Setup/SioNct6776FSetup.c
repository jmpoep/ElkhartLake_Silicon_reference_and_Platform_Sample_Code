/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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
#include "SioNct6776FSetup.h"
#include <SetupPrivate.h>

///
/// Control values. Values smaller than 8 are pointers to VoltageFactor and
/// indicate that reading is a voltage. The final value is added to AddValue
/// From 8 through 16 it's the same, but indicates negative voltage that
/// should be subtracted from AddValue.
///
#define HWMON_UNSUPPORTED               0x80
#define HWMON_PECI_TEMP                 0x40
#define HWMON_TEMP                      0x20
#define HWMON_FAN                       0x10

///
/// NctHwmonStringCommon Control Values.
///
#define HWMON_COMMON_UNSUPPORTED        0x80
#define HWMON_COMMON_PLUS_VOLTAGE       0x40
#define HWMON_COMMON_NEG_VOLTAGE        0x41
#define HWMON_COMMON_TEMPERATURE        0x20
#define HWMON_COMMON_FAN_SPEED          0x10

  #define HWMON_INDEX_ADDRESS           HWMON_BASE_ADDRESS + 5
  #define HWMON_DATA_ADDRESS            HWMON_BASE_ADDRESS + 6


  #ifdef SIO_HWMON_CPU_PECI_TEMP
    #define HWMON_CPU_TEMP_CTRL         HWMON_PECI_TEMP
  #else // SIO_HWMON_CPU_PECI_TEMP
    #define HWMON_CPU_TEMP_CTRL         HWMON_TEMP
  #endif // SIO_HWMON_CPU_PECI_TEMP

  #ifdef SIO_HWMON_AUX_PECI_TEMP
    #define HWMON_AUX_TEMP_CTRL         HWMON_PECI_TEMP
  #else // SIO_HWMON_AUX_PECI_TEMP
    #define HWMON_AUX_TEMP_CTRL         HWMON_TEMP
  #endif // SIO_HWMON_AUX_PECI_TEMP

  #ifdef HWMON_NEGATIVE_CPU_VCORE
    #define HWMON_VCORE_CTRL            0x08
  #else // HWMON_NEGATIVE_CPU_VCORE
    #define HWMON_VCORE_CTRL            0x00
  #endif // HWMON_NEGATIVE_CPU_VCORE

  #ifdef HWMON_NEGATIVE_3VCC
    #define HWMON_3VCC_CTRL             0x09
  #else // HWMON_NEGATIVE_3VCC
    #define HWMON_3VCC_CTRL             0x01
  #endif // HWMON_NEGATIVE_3VCC

  #ifdef HWMON_NEGATIVE_AVCC
    #define HWMON_AVCC_CTRL             0x0a
  #else // HWMON_NEGATIVE_AVCC
    #define HWMON_AVCC_CTRL             0x02
  #endif // HWMON_NEGATIVE_AVCC

  #ifdef HWMON_NEGATIVE_VIN0
    #define HWMON_VIN0_CTRL             0x0b
  #else // HWMON_NEGATIVE_VIN0
    #define HWMON_VIN0_CTRL             0x03
  #endif // HWMON_NEGATIVE_VIN0

  #ifdef HWMON_NEGATIVE_VIN1
    #define HWMON_VIN1_CTRL             0x0c
  #else // HWMON_NEGATIVE_VIN1
    #define HWMON_VIN1_CTRL             0x04
  #endif // HWMON_NEGATIVE_VIN1

  #ifdef HWMON_NEGATIVE_VIN2
    #define HWMON_VIN2_CTRL             0x0d
  #else // HWMON_NEGATIVE_VIN2
    #define HWMON_VIN2_CTRL             0x05
  #endif // HWMON_NEGATIVE_VIN2

  #ifdef HWMON_NEGATIVE_VIN3
    #define HWMON_VIN3_CTRL             0x0e
  #else // HWMON_NEGATIVE_VIN3
    #define HWMON_VIN3_CTRL             0x06
  #endif // HWMON_NEGATIVE_VIN3

  #ifdef SIO_HWMON_MONITOR_SYS_FAN
    #define HWMON_SYS_FAN_CONTROL       HWMON_FAN
  #else // SIO_HWMON_MONITOR_SYS_FAN
    #define HWMON_SYS_FAN_CONTROL       HWMON_UNSUPPORTED
  #endif // SIO_HWMON_MONITOR_SYS_FAN

  #ifdef SIO_HWMON_MONITOR_CPU_FAN
    #define HWMON_CPU_FAN_CONTROL       HWMON_FAN
  #else // SIO_HWMON_MONITOR_CPU_FAN
    #define HWMON_CPU_FAN_CONTROL       HWMON_UNSUPPORTED
  #endif // SIO_HWMON_MONITOR_CPU_FAN

  #ifdef SIO_HWMON_MONITOR_AUX_FAN
    #define HWMON_AUX_FAN_CONTROL       HWMON_FAN
  #else // SIO_HWMON_MONITOR_AUX_FAN
    #define HWMON_AUX_FAN_CONTROL       HWMON_UNSUPPORTED
  #endif // SIO_HWMON_MONITOR_AUX_FAN

  #ifndef SIO_HWMON_MONITOR_OVT1
    #define HWMON_SYS_TEMP_CONTROL      HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR_OVT1
    #define HWMON_SYS_TEMP_CONTROL      HWMON_TEMP
  #endif // SIO_HWMON_MONITOR_OVT1

  #ifndef SIO_HWMON_MONITOR_OVT2
    #define HWMON_CPU_TEMP_CONTROL      HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR_OVT2
    #define HWMON_CPU_TEMP_CONTROL      HWMON_CPU_TEMP_CTRL
  #endif // SIO_HWMON_MONITOR_OVT2

  #ifndef SIO_HWMON_MONITOR_OVT3
    #define HWMON_AUX_TEMP_CONTROL      HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR_OVT3
    #define HWMON_AUX_TEMP_CONTROL      HWMON_AUX_TEMP_CTRL
  #endif // SIO_HWMON_MONITOR_OVT3

  #ifndef SIO_HWMON_MONITOR_CPU_VCORE
    #define HWMON_VCORE_CONTROL         HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__CPU_VCORE
    #define HWMON_VCORE_CONTROL         HWMON_VCORE_CTRL
  #endif // SIO_HWMON_MONITOR__CPU_VCORE

  #ifndef SIO_HWMON_MONITOR_3VCC
    #define HWMON_3VCC_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__3VCC
    #define HWMON_3VCC_CONTROL          HWMON_3VCC_CTRL
  #endif // SIO_HWMON_MONITOR__3VCC

  #ifndef SIO_HWMON_MONITOR_AVCC
    #define HWMON_AVCC_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__AVCC
    #define HWMON_AVCC_CONTROL          HWMON_AVCC_CTRL
  #endif // SIO_HWMON_MONITOR__AVCC

  #ifndef SIO_HWMON_MONITOR_VIN0
    #define HWMON_VIN0_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__VIN0
    #define HWMON_VIN0_CONTROL          HWMON_VIN0_CTRL
  #endif // SIO_HWMON_MONITOR__VIN0

  #ifndef SIO_HWMON_MONITOR_VIN1
    #define HWMON_VIN1_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__VIN1
    #define HWMON_VIN1_CONTROL          HWMON_VIN1_CTRL
  #endif // SIO_HWMON_MONITOR__VIN1

  #ifndef SIO_HWMON_MONITOR_VIN2
    #define HWMON_VIN2_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__VIN2
    #define HWMON_VIN2_CONTROL          HWMON_VIN2_CTRL
  #endif // SIO_HWMON_MONITOR__VIN2

  #ifndef SIO_HWMON_MONITOR_VIN3
    #define HWMON_VIN3_CONTROL          HWMON_UNSUPPORTED
  #else // SIO_HWMON_MONITOR__VIN3
    #define HWMON_VIN3_CONTROL          HWMON_VIN3_CTRL
  #endif // SIO_HWMON_MONITOR__VIN3

  typedef struct {
    UINT16  Key;
    UINT8   Control;
    UINT8   Bank;
    UINT8   Register;
    UINT8   AddValue;
  }NCT_SIO_HWMON_DATA;

UINT16  VoltageMultiplier[] = {
  HWMON_MULT_VCORE,
  HWMON_MULT_3VCC,
  HWMON_MULT_AVCC,
  HWMON_MULT_VIN0,
  HWMON_MULT_VIN1,
  HWMON_MULT_VIN2,
  HWMON_MULT_VIN3
};

NCT_SIO_HWMON_DATA HwmonMonitorData[] = {
  {NCT_HWMON_SYS_TEMP_KEY,  HWMON_SYS_TEMP_CONTROL, 0, 0x27, HWMON_SYS_TEMP_ADD},
  {NCT_HWMON_SYS_FAN_KEY,   HWMON_SYS_FAN_CONTROL,  6, 0x56, 0},

#ifdef SIO_HWMON_CPU_PECI_TEMP
  {NCT_HWMON_CPU_TEMP_KEY,  HWMON_CPU_TEMP_CONTROL, 7, 0x20, 1},
#else // SIO_HWMON_CPU_PECI_TEMP
  {NCT_HWMON_CPU_TEMP_KEY,  HWMON_CPU_TEMP_CONTROL, 1, 0x50, HWMON_CPU_TEMP_ADD},
#endif // SIO_HWMON_CPU_PECI_TEMP
  {NCT_HWMON_CPU_FAN_KEY,   HWMON_CPU_FAN_CONTROL,  6, 0x58, 0},

#ifdef SIO_HWMON_AUX_PECI_TEMP
  {NCT_HWMON_AUX_TEMP_KEY,  HWMON_AUX_TEMP_CONTROL, 7, 0x20, 2},
#else // SIO_HWMON_AUX_PECI_TEMP
  {NCT_HWMON_AUX_TEMP_KEY,  HWMON_AUX_TEMP_CONTROL, 2, 0x50, HWMON_AUX_TEMP_ADD},
#endif // SIO_HWMON_AUX_PECI_TEMP
  {NCT_HWMON_AUX_FAN_KEY,   HWMON_AUX_FAN_CONTROL,  6, 0x5a, 0},

  {NCT_HWMON_CPU_VCORE_KEY, HWMON_VCORE_CONTROL,    0, 0x20, HWMON_ADD_VCORE},
  {NCT_HWMON_3VCC_KEY,      HWMON_3VCC_CONTROL,     0, 0x23, HWMON_ADD_3VCC},
  {NCT_HWMON_AVCC_KEY,      HWMON_AVCC_CONTROL,     0, 0x22, HWMON_ADD_AVCC},
  {NCT_HWMON_VIN0_KEY,      HWMON_VIN0_CONTROL,     0, 0x21, HWMON_ADD_VIN0},
  {NCT_HWMON_VIN1_KEY,      HWMON_VIN1_CONTROL,     0, 0x24, HWMON_ADD_VIN1},
  {NCT_HWMON_VIN2_KEY,      HWMON_VIN2_CONTROL,     0, 0x25, HWMON_ADD_VIN2},
  {NCT_HWMON_VIN3_KEY,      HWMON_VIN3_CONTROL,     0, 0x26, HWMON_ADD_VIN3}
};

/**
  This function does the actual string formating.

  @param[in]  HiiHandle       HII interface handle.
  @param[in]  StrRef          Pointer to Setup token
  @param[in]  Value           Value to be formated into StrRef
  @param[in]  Control         indicative of desired formating
**/
VOID
NctHwmonStringCommon (
  EFI_HII_HANDLE  HiiHandle,
  EFI_STRING_ID   StrRef,
  UINT16          Value,
  UINT8           Control
  )
{
  UINT16  ValueIntg = 0;
  UINT16  ValueFrac = 0;

  if ((Control == HWMON_COMMON_PLUS_VOLTAGE) ||
      (Control == HWMON_COMMON_NEG_VOLTAGE)  ) {
        ValueIntg  = (UINT16) (Value / 1000);
        ValueFrac  = (UINT16) (Value % 1000);
  }

  switch (Control) {
    case HWMON_COMMON_UNSUPPORTED:
      InitString (HiiHandle, StrRef, L"N/A        ");
      break;

    case HWMON_COMMON_PLUS_VOLTAGE:
      if (ValueFrac < 10) {
        InitString (HiiHandle, StrRef, L"+ %d.00%d V", ValueIntg, ValueFrac);
      } else if (ValueFrac < 100) {
        InitString (HiiHandle, StrRef, L"+ %d.0%d V", ValueIntg, ValueFrac);
      } else {
        InitString (HiiHandle, StrRef, L"+ %d.%d V", ValueIntg, ValueFrac);
      }
      break;

    case HWMON_COMMON_NEG_VOLTAGE:
      if (ValueFrac < 10) {
        InitString (HiiHandle, StrRef, L"- %d.00%d V", ValueIntg, ValueFrac);
      } else if (ValueFrac < 100) {
        InitString (HiiHandle, StrRef, L"- %d.0%d V", ValueIntg, ValueFrac);
      } else {
        InitString (HiiHandle, StrRef, L"- %d.%d V", ValueIntg, ValueFrac);
      }
      break;

    case HWMON_COMMON_TEMPERATURE:
      ValueIntg  = (UINT16) (Value / 2);
      ValueFrac  = (UINT16) (Value % 2);
      if (ValueFrac != 0) ValueFrac = 5;
      InitString (HiiHandle, StrRef, L"%d.%d C", ValueIntg, ValueFrac);
      break;

    case HWMON_COMMON_FAN_SPEED:
      InitString (HiiHandle, StrRef, L"%d RPM", Value);
      break;

    default:
      break;
  }
}

/**
  Reads Hardware Monitor register.

  @param[in]  Reg             register to be read.

  @retval     UINT8           register value.
**/
UINT8
NctReadHwMonReg (
  UINT8 Reg
  )
{
  IoWrite8 (HWMON_INDEX_ADDRESS, Reg);
  return IoRead8 (HWMON_DATA_ADDRESS);
}

/**
  Reads a monitored value indicated by received setup token key.

  @param[in]  Key             Key of Setup token.
  @param[out] Value           current value, valid only if Supported = TRUE
                                  Units = milivolts / (1/2 C) / RPM.
  @param[out] Sign            0 if positive, 0xFF if negativ

  @retval     Boolean         TRUE if reading supported, FALSE if not supported.
**/
BOOLEAN
NctReadValue (
  UINT16         Key,
  UINT16         *Value,
  UINT8          *Sign
  )
{
  UINT32  VoltTemp = 0;
  UINT32  Multiplier = 1000;
  UINT16  Size, i;
  UINT16  Temp = 0;
  UINT16  AddValue = 0;
  UINT8   RegL = 0;
  UINT8   RegH = 0;
  UINT8   Bank = 0;
  UINT8   Register = 0;
  UINT8   Control = HWMON_UNSUPPORTED;

  ///
  /// By default sign is positive. Only voltages can be negative.
  ///
  *Sign = 0;
  Size = sizeof (HwmonMonitorData) / sizeof (HwmonMonitorData[0]);
  for (i=0; i<Size; i++) {
    if (Key == HwmonMonitorData[i].Key) {
      Bank = HwmonMonitorData[i].Bank;
      Register = HwmonMonitorData[i].Register;
      AddValue = (UINT16) HwmonMonitorData[i].AddValue;
      Control = HwmonMonitorData[i].Control;
      break;
    }
  }
  if (Control == HWMON_UNSUPPORTED) return FALSE;

  ///
  /// Set the desired bank and read 1 or 2 consecutive registers. If voltage
  /// read only 1 register and compute final volt value else read 2 registers.
  ///
  RegL = NctReadHwMonReg (0x4e);
  if ((RegL & 0x07) != Bank) {
    ///
    /// If desired bank != current bank, clear bank bits and set new bank
    /// value. Then write it back, index already set by the read operation.
    ///
    RegL &= 0xF8;
    RegL |= Bank;
    IoWrite8 (HWMON_DATA_ADDRESS, RegL);
  }

  ///
  /// Read the designated register and check the Control to decide what to do
  /// next. If Control is larger than 0x0f then we are not reading a voltage,
  /// and the next register needs to be read; else it is voltage and Control
  /// indicates both an index to a voltage multiplier (bits 2-0) and a
  /// definition if it is a negative voltage (bit 3).
  ///
  RegL = NctReadHwMonReg (Register);
  if (Control > 0x0f) {
    RegH = NctReadHwMonReg (Register+1);
  } else {
    i = (UINT16) (Control & 0x07);
    if (i == 7) {
      return FALSE; // Not supported in VoltageMultiplier
    }

    ///
    /// It's voltage, convert AddValue to milivolts.
    ///
    AddValue *= 100;

    ///
    /// Do multiplications followed by division by 1000 as UINT32 for precision.
    /// Readings are in 8 milivolts units.
    ///
    Multiplier = (UINT32) VoltageMultiplier[i];
    VoltTemp = (UINT32) RegL * 8;
    VoltTemp *= Multiplier;
    VoltTemp /= 1000;

    ///
    /// Convert back to UINT16 to obtain the value that will be added to or
    /// subtracted from the base voltage.
    ///
    i = (UINT16) (0x0000ffff & VoltTemp);
    if (Control < 8) {
      ///
      /// Positive value, add it to AddValue.
      ///
      Temp = AddValue + i;            // positive value.
    } else {
      ///
      /// Negative value, subtract it from AddValue to obtain module of
      /// negative value. Then indicate it's a negative value.
      ///
      Temp = AddValue - i;
      *Sign = 0xff;
    }
  }

  ///
  /// Final computations if not voltage.
  ///
  if (Control == HWMON_FAN) {
    if (NctReadHwMonReg (Register - 0x26) == 0xff) {
      ///
      /// With fan count at maximum, RPM is 0 (avoid false value when fan is
      /// stoped).
      ///
      Temp = 0;
    } else {
      Temp = (UINT16) ((RegL << 8) + RegH);
    }
  }

  if ((Control == HWMON_TEMP) || (Control == HWMON_PECI_TEMP)) {
    ///
    /// Setup uses 0.5 C resolution. RegL has the temperature in C, multiply
    /// by to to match setup resolution, and add 0.5 C bit from RegH. Notice
    /// that different bits represent 0.5 C depending if it's thermal diode
    /// input or PECI input. Also, if PECI the code needs to verify if the
    /// PECI agent is alive.
    ///
    Temp = (UINT16) RegL * 2;
    if (Control == HWMON_TEMP) {
      if ((RegH & 0x80) == 0x80) Temp++;
    } else {
      ///
      /// Check if agent is alive, return FALSE if not.
      ///
      Control = NctReadHwMonReg (0x1f);
      if (((UINT8) (AddValue & 3) & Control) == 0) {
        return FALSE;
      }
      if ((RegH & 0x02) == 0x02) {
        Temp++;
      }
    }
  }
  *Value = Temp;
  return TRUE;
}

/**
  Reads a Hwmon value and updates the related string.

  @param[in]  HiiHandle       HII interface handle.
  @param[in]  Key             Key of Setup token
**/
VOID
NctUpdateHwmonString (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Key
  )
/*++
Routine Description:

Arguments:
  HiiHandle - Handle to HII database


Returns:
  none.
--*/
{
  EFI_STRING_ID  StrRef = 0;    // initialize variables, avoid build warning.
  UINT16         Value = 0;
  UINT8          Sign = 0;
  UINT8          Control = HWMON_COMMON_UNSUPPORTED;
  BOOLEAN        Status;

  ///
  /// Read current monitored value, and if voltage set appropriate Sign.
  ///
  Status = NctReadValue (Key, &Value, &Sign);

  ///
  /// Set the correct StrRef and Control.
  ///
  switch (Key) {
    case NCT_HWMON_SYS_TEMP_KEY:
      if (Status) {
        Control = HWMON_COMMON_TEMPERATURE;
      }
      StrRef  = STRING_TOKEN (STR_SYS_TEMP_VALUE);
      break;

    case NCT_HWMON_SYS_FAN_KEY:
      if (Status) {
        Control = HWMON_COMMON_FAN_SPEED;
      }
      StrRef  = STRING_TOKEN (STR_SYS_FAN_VALUE);
      break;

    case NCT_HWMON_CPU_TEMP_KEY:
      if (Status) {
        Control = HWMON_COMMON_TEMPERATURE;
      }
      StrRef  = STRING_TOKEN (STR_CPU_TEMP_VALUE);
      break;

    case NCT_HWMON_CPU_FAN_KEY:
      if (Status) {
        Control = HWMON_COMMON_FAN_SPEED;
      }
      StrRef  = STRING_TOKEN (STR_CPU_FAN_VALUE);
      break;

    case NCT_HWMON_AUX_TEMP_KEY:
      if (Status) {
        Control = HWMON_COMMON_TEMPERATURE;
      }
      StrRef  = STRING_TOKEN (STR_AUX_TEMP_VALUE);
      break;

    case NCT_HWMON_AUX_FAN_KEY:
      if (Status) {
        Control = HWMON_COMMON_FAN_SPEED;
      }
      StrRef  = STRING_TOKEN (STR_AUX_FAN_VALUE);
      break;

    case NCT_HWMON_CPU_VCORE_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_VCORE_VALUE);
      break;

    case NCT_HWMON_3VCC_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_3VCC_VALUE);
      break;

    case NCT_HWMON_AVCC_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_AVCC_VALUE);
      break;

    case NCT_HWMON_VIN0_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_VIN0_VALUE);
      break;

    case NCT_HWMON_VIN1_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_VIN1_VALUE);
      break;

    case NCT_HWMON_VIN2_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_VIN2_VALUE);
      break;

    case NCT_HWMON_VIN3_KEY:
      if (Status) {
        if (Sign == 0) {
          Control = HWMON_COMMON_PLUS_VOLTAGE;
        } else {
          Control = HWMON_COMMON_NEG_VOLTAGE;
        }
      }
      StrRef  = STRING_TOKEN (STR_VIN3_VALUE);
      break;

    default:
      break;
  }

  ///
  /// Change the string pointed by StrRef to the new Value, format defined
  /// by Control.
  ///
  NctHwmonStringCommon (HiiHandle, StrRef, Value, Control);
}

/**
  Call Back function for NCT6776F HWMON Setup key change

  @param[in]  HiiHandle       HII interface handle.
  @param[in]  Class           Indicates the setup class
  @param[in]  SubClass        Indicates setup Subclass
  @param[in]  Key             Key of Setup token
**/
VOID
NctHwmonCallBack (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class,
  UINT16         SubClass,
  UINT16         Key
  )
{
  if(Class == ADVANCED_FORM_SET_CLASS){
    DEBUG ((EFI_D_INFO, "<NctHwmonCallBack>"));
    NctUpdateHwmonString (HiiHandle, Key);
  }
}

/**
  Initializes all Hardware Monitor strings with the actual value read from
  the Hardware Monitor registers.

  @param[in]  HiiHandle       HII interface handle.
  @param[in]  Class           Setup class, must be ADVANCED_FORM_SET_CLASS.
**/
VOID NctInitSioStrings(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
  if(Class == ADVANCED_FORM_SET_CLASS){

    ///
    /// Intialize current settings setup strings.
    ///

    NctUpdateHwmonString (HiiHandle, NCT_HWMON_SYS_TEMP_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_SYS_FAN_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_CPU_TEMP_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_CPU_FAN_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_AUX_TEMP_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_AUX_FAN_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_CPU_VCORE_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_3VCC_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_AVCC_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_VIN0_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_VIN1_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_VIN2_KEY);
    NctUpdateHwmonString (HiiHandle, NCT_HWMON_VIN3_KEY);

  }
}
