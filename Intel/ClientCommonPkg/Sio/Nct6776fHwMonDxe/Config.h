/** @file
  Hardware Monitor configuration file.
  This file should be the only file to be modified when porting this driver
  between platforms. It contains build options and configuration values. It
  is grouped in 2 sections, by order: hardware monitor build
  options with its configuration values and a "do not change"
  section where some of the build options are translated to
  configuration values.

@copyright
  Copyright (c) 2013-2015, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor. This file may be modified by the user, subject to
  the additional terms of the license agreement.
**/

/**
The settings for over temperature assumes OVT1 source same as the used for
fan control. For system it will always be SYSTIN, for CPU it can be CPUTIN
or PECI0, and the auxiliary temperature source can be AUXTIN or PECI1.
**/

#ifndef _NCT6776F_CONFIG_H_
#define _NCT6776F_CONFIG_H_

//////////////////////////////////////////////////////////////////////////////
// HWMON IO addresses must be programmed within the ISA bridge. There are 4 //
// possible registers within PCI device 1F function 0 (ISA bridge): 0x84,   //
// 0x88, 0x8c and 0x90. Set HWMON_LPC_REG to a register that is free in the //
// board the SIO NCT6776F is being used.                                    //
//////////////////////////////////////////////////////////////////////////////

#define HWMON_LPC_REG                   0x8c
#define HWMON_SMBUS_ADDRESS_REG_VAL     0x2d    // for address 0x5a.

///////////////////////////////////////////////////////////////////////////////
// Within HWMON, the supported fan control. For each particular fan, only one//
// method of control can be enabled. For SYSFAN only, there's an option for  //
// DC control, for all other fan it's always PWM control.                    //
///////////////////////////////////////////////////////////////////////////////

//#define SIO_HWMON_SYSFAN_DC_CONTROL
//#define SIO_HWMON_SYSFAN_THERMAL_CRUISE
#define SIO_HWMON_SYSFAN_SMART_FAN
//#define SIO_HWMON_CPUFAN_THERMAL_CRUISE
#define SIO_HWMON_CPUFAN_SMART_FAN
//#define SIO_HWMON_AUXFAN_THERMAL_CRUISE
//#define SIO_HWMON_AUXFAN_SMART_FAN

/////////////////////////////////////////////////////////////////////////////
// CPU temperature could be diode or PECI0, AUX temperature could be diode //
// or PECI1.                                                               //
/////////////////////////////////////////////////////////////////////////////

#define SIO_HWMON_CPU_PECI_TEMP // if defined CPU temperature source is PECI.
//#define SIO_HWMON_AUX_PECI_TEMP // if defined AUX temperature source is PECI.
#define SIO_PECI_ENABLE                 0x95
#define SIO_PECI_CRITICAL_TEMP          100
#define SIO_PECI_AGENT_CONFIG           0x10
#define SIO_PECI_TIMING_CONFIG          0x02

///////////////////////////////////////////////////////////////////////////////
// Within HWMON, the FAN pulse per revolution. 1 -> 1, 2 -> 2, 3 -> 3, 0 -> 4//
///////////////////////////////////////////////////////////////////////////////

#define SIO_HWMON_SYS_FAN_PULSE         0   // 4 pulses per revolution.
#define SIO_HWMON_CPU_FAN_PULSE         2   // 2 pulses per revolution.
#define SIO_HWMON_AUX_FAN_PULSE         0   // 4 pulses per revolution.

/////////////////////////////////////////////
// Within HWMON, the supported monitoring. //
/////////////////////////////////////////////

//#define SIO_HWMON_MONITOR_SYS_FAN
#define SIO_HWMON_MONITOR_CPU_FAN
//#define SIO_HWMON_MONITOR_AUX_FAN0
//#define SIO_HWMON_MONITOR_OVT1
#define SIO_HWMON_MONITOR_OVT2
//#define SIO_HWMON_MONITOR_OVT3
#define SIO_HWMON_MONITOR_3VCC
#define SIO_HWMON_MONITOR_AVCC
#define SIO_HWMON_MONITOR_CPU_VCORE
#define SIO_HWMON_MONITOR_VIN0
#define SIO_HWMON_MONITOR_VIN1
#define SIO_HWMON_MONITOR_VIN2
#define SIO_HWMON_MONITOR_VIN3
//#define SIO_HWMON_MONITOR_CASE_OPEN0
//#define SIO_HWMON_MONITOR_CASE_OPEN1

///////////////////////////////////////////////////////////////////////////////
// The next monitoring capabilities are incompatible with AMT, as the status //
// register is in bank 4.                                                    //
///////////////////////////////////////////////////////////////////////////////

//#define SIO_HWMON_MONITOR_AUX_FAN1
//#define SIO_HWMON_MONITOR_AUX_FAN2
//#define SIO_HWMON_MONITOR_VBAT
//#define SIO_HWMON_MONITOR_3VSB

//////////////////////////////////////////////////////////////////////////////
// Within monitoring, some input options can be defined. Bellow, grouped by //
// sensor type, are input configuration options.                            //
//////////////////////////////////////////////////////////////////////////////

// Temperature sensors (both for OVT and for FAN control).
#define SIO_HWMON_SYSTIN_THERMISTOR     // if undefined then current mode.
#define SIO_HWMON_CPUTIN_THERMISTOR     // if undefined then current mode.
#define SIO_HWMON_AUXTIN_THERMISTOR     // if undefined then current mode.

#define SIO_HWMON_CURRENT_SENSOR_TEMP   0x00 // bank 0 register 0x5e.
#define SIO_HWMON_PECI_ENABLE           0x01 // bank 0 register 0xae.

#define SIO_HWMON_TEMP_SEL_SYSTIN       0x01
#define SIO_HWMON_TEMP_SEL_CPUTIN       0x02
#define SIO_HWMON_TEMP_SEL_AUXTIN       0x03
#define SIO_HWMON_TEMP_SEL_PECI0        0x0c
#define SIO_HWMON_TEMP_SEL_PECI1        0x0d
#define SIO_HWMON_TEMP_SEL_PCH_CHIP     0x0f
#define SIO_HWMON_TEMP_SEL_PCH_CPU      0x10
#define SIO_HWMON_TEMP_SEL_PCH_MCH      0x11

// Fan sensors.
#define HWMON_SYS_FAN_STYLE             0x00  // 0 -> 4 wire; 1 -> 3 wire.
#define HWMON_CPU_FAN_STYLE             0x00  // 0 -> 4 wire; 1 -> 3 wire.
#define HWMON_AUX_FAN_STYLE             0x00  // 0 -> 4 wire; 1 -> 3 wire.

// Voltage sensors.
#define SIO_HWMON_EN_VBAT_MNT           // controls bank 0, reg 0x5d, bit 0.

///////////////////////////////////////////////////////////////////////////////
// Programming values that are board specific. This values can be edited to  //
// match a particular platform. If needed, new definitions can also be added //
// here.                                                                     //
///////////////////////////////////////////////////////////////////////////////

#define SIO_HWMON_SYS_FAN_PWM_FREQ      0x04  // 18.78 KHz.
#define SIO_HWMON_CPU_FAN_PWM_FREQ      0x04  // 18.78 KHz.
#define SIO_HWMON_AUX_FAN_PWM_FREQ      0x04  // 18.78 KHz.
#define SIO_HWMON_CONFIGURATION_START   0x00  // disable SMI and stop monitoring.
#define SIO_HWMON_CONFIGURATION_END     0x03  // enable SMI and start monitoring.
#define SIO_HWMON_OVT_CONTROL           0x18  // OVT polarity active low.

#define HWMON_SYS_FAN_TARGET_TEMP       0x32  // 50 C.
#define HWMON_SYS_FAN_TEMP_TOLERANCE_L  0x05  // from 45 C to 55 C.
#define HWMON_SYS_FAN_TEMP_TOLERANCE_H  0x00
#define HWMON_SYS_START_FAN_SPEED       0x1e  // start at 30% max speed.
#define HWMON_SYS_STOP_FAN_SPEED        0x14  // stop at 20% max speed.
#define HWMON_SYS_FAN_STEP_UP_TIME      0x0a  // 1 second.
#define HWMON_SYS_FAN_STEP_DOWN_TIME    0x0a  // 1 second.
#define HWMON_SYS_STOP_FAN_TIME         0x32  // fully stop after 5 seconds.
#define HWMON_SYS_FAN_STEP_SIZE         0x05  // 5% increase/decrease.
#define HWMON_SYS_FAN_SF4_T1            0x2d  // 45 C.
#define HWMON_SYS_FAN_SF4_T2            0x30  // 48 C.
#define HWMON_SYS_FAN_SF4_T3            0x33  // 51 C.
#define HWMON_SYS_FAN_SF4_T4            0x37  // 55 C.
#define HWMON_SYS_FAN_SF4_PWM1          0x1e  // start at 30%.
#define HWMON_SYS_FAN_SF4_PWM2          0x2e  // increase slowly to 46% (+16%).
#define HWMON_SYS_FAN_SF4_PWM3          0x46  // faster to 70%. (+24%).
#define HWMON_SYS_FAN_SF4_PWM4          0x64  // even faster to 100%. (+30%).
#define HWMON_SYS_FAN_CRITICAL_TEMP     0x48  // 72 C.
#define HWMON_SYS_FAN_CRITICAL_TOLER    0x02  // +/-2 C.
#define HWMON_SYS_OVT_TEMPERATURE       0x4c  // 76 C.

#define HWMON_CPU_FAN_TARGET_DIODE_TEMP 0x50  // 80 C.
#define HWMON_CPU_FAN_TARGET_PECI_TEMP  0x5a  // 90 C.
#define HWMON_CPU_FAN_TEMP_TOLERANCE_L  0x05  // 75 C to 85 C.
#define HWMON_CPU_FAN_PECI_TOLERANCE_L  0x02  // +/- 2 counts.
#define HWMON_CPU_FAN_TEMP_TOLERANCE_H  0x00
#define HWMON_CPU_START_FAN_SPEED       0x28  // start at 40% max speed.
#define HWMON_CPU_STOP_FAN_SPEED        0x14  // stop at 20% max speed.
#define HWMON_CPU_FAN_STEP_UP_TIME      0x0a  // 1 second.
#define HWMON_CPU_FAN_STEP_DOWN_TIME    0x0a  // 1 second.
#define HWMON_CPU_STOP_FAN_TIME         0x32  // fully stop after 5 seconds.
#define HWMON_CPU_FAN_STEP_SIZE         0x05  // 5% increase/decrease.
#define HWMON_CPU_FAN_SF4_DIODE_T1      0x19  // 25 C.
#define HWMON_CPU_FAN_SF4_DIODE_T2      0x28  // 40 C.
#define HWMON_CPU_FAN_SF4_DIODE_T3      0x37  // 55 C.
#define HWMON_CPU_FAN_SF4_DIODE_T4      0x46  // 70 C.
#define HWMON_CPU_FAN_SF4_PECI_T1       0x19  // 25 C.
#define HWMON_CPU_FAN_SF4_PECI_T2       0x28  // 40 C.
#define HWMON_CPU_FAN_SF4_PECI_T3       0x37  // 55 C.
#define HWMON_CPU_FAN_SF4_PECI_T4       0x46  // 70 C.
#define HWMON_CPU_FAN_SF4_PWM1          0x40  // 25%
#define HWMON_CPU_FAN_SF4_PWM2          0x80  // 50%
#define HWMON_CPU_FAN_SF4_PWM3          0xc0  // 75%
#define HWMON_CPU_FAN_SF4_PWM4          0xfe  // 99%.
#define HWMON_CPU_FAN_CRITICAL_DIODE_T  0x5a  // 90 C.
#define HWMON_CPU_FAN_CRITICAL_PECI_T   0x5a  // 90 C.
#define HWMON_CPU_FAN_CRITICAL_TOLER    0x02  // +/-2 C.
#define HWMON_CPU_FAN_OVT_DIODE_TEMP    0x64  // 100 C.
#define HWMON_CPU_FAN_OVT_PECI_TEMP     0x64  // 100 C.
#define HWMON_CPU_OVT_CONTROL           0x12  // 2 faults, interrupt mode.

#define HWMON_AUX_FAN_TARGET_DIODE_TEMP 0x50  // 80 C.
#define HWMON_AUX_FAN_TARGET_PECI_TEMP  0x14  // critical - 20C
#define HWMON_AUX_FAN_TEMP_TOLERANCE_L  0x05  // 75 C to 85 C.
#define HWMON_AUX_FAN_PECI_TOLERANCE_L  0x02  // +/- 2 counts.
#define HWMON_AUX_FAN_TEMP_TOLERANCE_H  0x00
#define HWMON_AUX_START_FAN_SPEED       0x28  // start at 40% max speed.
#define HWMON_AUX_STOP_FAN_SPEED        0x14  // stop at 20% max speed.
#define HWMON_AUX_FAN_STEP_UP_TIME      0x0a  // 1 second.
#define HWMON_AUX_FAN_STEP_DOWN_TIME    0x0a  // 1 second.
#define HWMON_AUX_STOP_FAN_TIME         0x32  // fully stop after 5 seconds.
#define HWMON_AUX_FAN_STEP_SIZE         0x05  // 5% increase/decrease.
#define HWMON_AUX_FAN_SF4_DIODE_T1      0x4b  // 75 C.
#define HWMON_AUX_FAN_SF4_DIODE_T2      0x4e  // 78 C.
#define HWMON_AUX_FAN_SF4_DIODE_T3      0x51  // 81 C.
#define HWMON_AUX_FAN_SF4_DIODE_T4      0x55  // 85 C.
#define HWMON_AUX_FAN_SF4_PECI_T1       0x4b  // 75 C.
#define HWMON_AUX_FAN_SF4_PECI_T2       0x4e  // 78 C.
#define HWMON_AUX_FAN_SF4_PECI_T3       0x51  // 81 C.
#define HWMON_AUX_FAN_SF4_PECI_T4       0x55  // 85 C.
#define HWMON_AUX_FAN_SF4_PWM1          0x18  // start at 24%.
#define HWMON_AUX_FAN_SF4_PWM2          0x28  // slowly to 40%. (+16%).
#define HWMON_AUX_FAN_SF4_PWM3          0x41  // faster to 65%. (+25%).
#define HWMON_AUX_FAN_SF4_PWM4          0x64  // even faster to 100%. (+ 35%).
#define HWMON_AUX_FAN_CRITICAL_DIODE_T  0x60  // 96 C.
#define HWMON_AUX_FAN_CRITICAL_PECI_T   0x06  // PECI count of 6.
#define HWMON_AUX_FAN_CRITICAL_TOLER    0x02  // +/-2 C.
#define HWMON_AUX_FAN_OVT_DIODE_TEMP    0x64  // 100 C.
#define HWMON_AUX_FAN_OVT_PECI_TEMP     0x02  // PECI count of 2.
#define HWMON_AUX_OVT_CONTROL           0x12  // 2 faults, interrupt mode.

// Voltage low and high limits.
#define HWMON_MONITOR_3VCC_LOW          0xc3  // 3.120 V.
#define HWMON_MONITOR_3VCC_HIGH         0xd8  // 3.456 V.
#define HWMON_MONITOR_AVCC_LOW          0xc3  // 3.120 V.
#define HWMON_MONITOR_AVCC_HIGH         0xd8  // 3.456 V.
#define HWMON_MONITOR_CPU_VCORE_LOW     0x5d  // 0.744 V.
#define HWMON_MONITOR_CPU_VCORE_HIGH    0x9c  // 1.248 V.
#define HWMON_MONITOR_VIN0_LOW          0x76  // 11.329 V.
#define HWMON_MONITOR_VIN0_HIGH         0x89  // 12.578 V.
#define HWMON_MONITOR_VIN1_LOW          0x78  // 4.723 V.
#define HWMON_MONITOR_VIN1_HIGH         0x89  // 5.234 V.
#define HWMON_MONITOR_VIN2_LOW          0x7c  // 0.992 V.
#define HWMON_MONITOR_VIN2_HIGH         0x89  // 1.096 V.
#define HWMON_MONITOR_VIN3_LOW          0xa0  // 1.280 V.
#define HWMON_MONITOR_VIN3_HIGH         0xb1  // 1.416 V.

///////////////////////////////////////////////////////////////////////////////
// Fan Count Limit High bytes. The count is 13-bit wide, and the lower 5 bits//
// will always be left at 0 (to reduce the number of IO). When a fan slows,  //
// its count increases. These count values indicate that the fan is too slow.//
///////////////////////////////////////////////////////////////////////////////

#define HWMON_SYSFAN_COUNT_LIMIT        0xc0
#define HWMON_CPUFAN_COUNT_LIMIT        0xc0
#define HWMON_AUXFAN_COUNT_LIMIT        0xc0

//////////////////////////////////////////////////////////////////////////
// HwMon configuration values that are based on definitions above being //
// commented out or enabled. DO NOT CHANGE THIS VALUES HERE!            //
//////////////////////////////////////////////////////////////////////////

#ifdef SIO_SUPPORT_SMI_ALERTS
#define SIO_SMI_ALERT_MASK1             0x00
#define SIO_SMI_ALERT_MASK2             0x00
#define SIO_SMI_ALERT_MASK3             0x00
#define SIO_SMI_ALERT_MASK4             0x00
#else  // SIO_SUPPORT_SMI_ALERTS
#define SIO_SMI_ALERT_MASK1             0xff
#define SIO_SMI_ALERT_MASK2             0xff
#define SIO_SMI_ALERT_MASK3             0x3f
#define SIO_SMI_ALERT_MASK4             0x13
#endif // SIO_SUPPORT_SMI_ALERTS

#ifdef SIO_HWMON_CPU_PECI_TEMP
#define HWMON_CPU_FAN_TARGET_TEMP       HWMON_CPU_FAN_TARGET_PECI_TEMP
#define HWMON_CPU_FAN_SF4_T1            HWMON_CPU_FAN_SF4_PECI_T1
#define HWMON_CPU_FAN_SF4_T2            HWMON_CPU_FAN_SF4_PECI_T2
#define HWMON_CPU_FAN_SF4_T3            HWMON_CPU_FAN_SF4_PECI_T3
#define HWMON_CPU_FAN_SF4_T4            HWMON_CPU_FAN_SF4_PECI_T4
#define HWMON_CPU_FAN_CRITICAL_TEMP     HWMON_CPU_FAN_CRITICAL_PECI_T
#define SIO_HWMON_TEMP_SEL_CPU_TIN      SIO_HWMON_TEMP_SEL_PECI0
#define HWMON_CPU_OVT_TEMPERATURE       HWMON_CPU_FAN_OVT_PECI_TEMP
#else // SIO_HWMON_CPU_PECI_TEMP
#define HWMON_CPU_FAN_TARGET_TEMP       HWMON_CPU_FAN_TARGET_DIODE_TEMP
#define HWMON_CPU_FAN_SF4_T1            HWMON_CPU_FAN_SF4_DIODE_T1
#define HWMON_CPU_FAN_SF4_T2            HWMON_CPU_FAN_SF4_DIODE_T2
#define HWMON_CPU_FAN_SF4_T3            HWMON_CPU_FAN_SF4_DIODE_T3
#define HWMON_CPU_FAN_SF4_T4            HWMON_CPU_FAN_SF4_DIODE_T4
#define HWMON_CPU_FAN_CRITICAL_TEMP     HWMON_CPU_FAN_CRITICAL_DIODE_T
#define SIO_HWMON_TEMP_SEL_CPU_TIN      SIO_HWMON_TEMP_SEL_CPUTIN
#define HWMON_CPU_OVT_TEMPERATURE       HWMON_CPU_FAN_OVT_DIODE_TEMP
#endif // SIO_HWMON_CPU_PECI_TEMP

#ifdef SIO_HWMON_AUX_PECI_TEMP
#define HWMON_AUX_FAN_TARGET_TEMP       HWMON_AUX_FAN_TARGET_PECI_TEMP
#define HWMON_AUX_FAN_SF4_T1            HWMON_AUX_FAN_SF4_PECI_T1
#define HWMON_AUX_FAN_SF4_T2            HWMON_AUX_FAN_SF4_PECI_T2
#define HWMON_AUX_FAN_SF4_T3            HWMON_AUX_FAN_SF4_PECI_T3
#define HWMON_AUX_FAN_SF4_T4            HWMON_AUX_FAN_SF4_PECI_T4
#define HWMON_AUX_FAN_CRITICAL_TEMP     HWMON_AUX_FAN_CRITICAL_PECI_T
#define SIO_HWMON_TEMP_SEL_AUX_TIN      SIO_HWMON_TEMP_SEL_PECI1
#define HWMON_AUX_OVT_TEMPERATURE       HWMON_AUX_FAN_OVT_PECI_TEMP
#else // SIO_HWMON_AUX_PECI_TEMP
#define HWMON_AUX_FAN_TARGET_TEMP       HWMON_AUX_FAN_TARGET_DIODE_TEMP
#define HWMON_AUX_FAN_SF4_T1            HWMON_AUX_FAN_SF4_DIODE_T1
#define HWMON_AUX_FAN_SF4_T2            HWMON_AUX_FAN_SF4_DIODE_T2
#define HWMON_AUX_FAN_SF4_T3            HWMON_AUX_FAN_SF4_DIODE_T3
#define HWMON_AUX_FAN_SF4_T4            HWMON_AUX_FAN_SF4_DIODE_T4
#define HWMON_AUX_FAN_CRITICAL_TEMP     HWMON_AUX_FAN_CRITICAL_DIODE_T
#define SIO_HWMON_TEMP_SEL_AUX_TIN      SIO_HWMON_TEMP_SEL_AUXTIN
#define HWMON_AUX_OVT_TEMPERATURE       HWMON_AUX_FAN_OVT_DIODE_TEMP
#endif // SIO_HWMON_AUX_PECI_TEMP

#ifdef SIO_HWMON_SYSFAN_DC_CONTROL
#define SIO_HWMON_SYSFAN_METHOD         0x01
#else // SIO_HWMON_SYSFAN_DC_CONTROL
#define SIO_HWMON_SYSFAN_METHOD         0x00
#endif // SIO_HWMON_SYSFAN_DC_CONTROL

#ifdef SIO_HWMON_SYSTIN_THERMISTOR
#define SIO_HWMON_SYSTIN_MODE           0x00
#else // SIO_HWMON_SYSTIN_THERMISTOR
#define SIO_HWMON_SYSTIN_MODE           0x02
#endif // SIO_HWMON_SYSTIN_THERMISTOR

#ifdef SIO_HWMON_CPUTIN_THERMISTOR
#define SIO_HWMON_CPUTIN_MODE           0x00
#else // SIO_HWMON_CPUTIN_THERMISTOR
#define SIO_HWMON_CPUTIN_MODE           0x04
#endif // SIO_HWMON_CPUTIN_THERMISTOR

#ifdef SIO_HWMON_AUXTIN_THERMISTOR
#define SIO_HWMON_AUXTIN_MODE           0x00
#else // SIO_HWMON_AUXTIN_THERMISTOR
#define SIO_HWMON_AUXTIN_MODE           0x08
#endif // SIO_HWMON_AUXTIN_THERMISTOR

#ifdef SIO_HWMON_EN_VBAT_MNT
#define HWMON_B0_R5D                    (0x01 | SIO_HWMON_SYSTIN_MODE | SIO_HWMON_CPUTIN_MODE | SIO_HWMON_AUXTIN_MODE)
#else // SIO_HWMON_EN_VBAT_MNT
#define HWMON_B0_R5D                    (SIO_HWMON_SYSTIN_MODE | SIO_HWMON_CPUTIN_MODE | SIO_HWMON_AUXTIN_MODE)
#endif // SIO_HWMON_EN_VBAT_MNT

/////////////////////////////////////////
// END OF "DO NOT CHANGE VALUES" AREA! //
/////////////////////////////////////////

#endif  // _NCT6776F_CONFIG_H_
