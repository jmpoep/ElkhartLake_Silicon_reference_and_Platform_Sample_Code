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

#ifndef Nct6776F_SETUP_H_
#define Nct6776F_SETUP_H_
#ifdef __cplusplus
extern "C" {
#endif

///
/// Set the NCT6776F index and data register addresses.
///
#define NctIndex        0x2e
#define NctData         0x2f

///
/// These defines are copied from BroadwellPlatPkg\Platform\Nct6776HwMon\Config.h
/// and commented lines must match. Notice that not all definitions are copied, but
/// those that are must match commented/uncommented from the Config.h file.
///

#define SIO_HWMON_CPU_PECI_TEMP // if defined CPU temperature source is PECI.
//#define SIO_HWMON_AUX_PECI_TEMP // if defined AUX temperature source is PECI.

#define HWMON_BASE_ADDRESS              0x0290  // HWMON uses +5 and +6.

#define SIO_HWMON_MONITOR_SYS_FAN
#define SIO_HWMON_MONITOR_CPU_FAN
//#define SIO_HWMON_MONITOR_AUX_FAN0
#define SIO_HWMON_MONITOR_OVT1          // SYS_TEMP
#define SIO_HWMON_MONITOR_OVT2          // CPU_TEMP
//#define SIO_HWMON_MONITOR_OVT3          // AUX_TEMP
#define SIO_HWMON_MONITOR_3VCC
#define SIO_HWMON_MONITOR_AVCC
#define SIO_HWMON_MONITOR_CPU_VCORE
#define SIO_HWMON_MONITOR_VIN0
#define SIO_HWMON_MONITOR_VIN1
#define SIO_HWMON_MONITOR_VIN2
#define SIO_HWMON_MONITOR_VIN3

// End of definitions copied from Config.h

// Negative voltage indicator. Comment those that are positive voltages.
//#define HWMON_NEGATIVE_CPU_VCORE
//#define HWMON_NEGATIVE_3VCC
//#define HWMON_NEGATIVE_AVCC
//#define HWMON_NEGATIVE_VIN0
//#define HWMON_NEGATIVE_VIN1
//#define HWMON_NEGATIVE_VIN2
//#define HWMON_NEGATIVE_VIN3

/// Board specific voltage add and multiplier values. AddValue is UINT8 and
/// MultiplierValue is UINT16. MultiplierValue assumes 3 decimal digits.
/// AddValue is in tens of volts.
/// ((MultiplierValue * reading) / 1000) + (AddValue * 100) = final milivolts.
#define HWMON_ADD_VCORE            0    // for CPU_VCORE entry.
#define HWMON_ADD_3VCC             0
#define HWMON_ADD_AVCC             0
#define HWMON_ADD_VIN0             0
#define HWMON_ADD_VIN1             0
#define HWMON_ADD_VIN2             0
#define HWMON_ADD_VIN3             0
#define HWMON_MULT_VCORE        1000    // for CPU_VCORE entry.
#define HWMON_MULT_3VCC         2000    // internal divider by 2.
#define HWMON_MULT_AVCC         2000    // internal divider by 2.
#define HWMON_MULT_VIN0        12002    // 54.9K + 4.99K.   12V
#define HWMON_MULT_VIN1         4920    // 39.2K + 10K.     5V
#define HWMON_MULT_VIN2         1000    //                  1.05V
#define HWMON_MULT_VIN3         1000    //                  VDD.

// Temperature add values if not PECI temperature.
#define HWMON_SYS_TEMP_ADD         0
#define HWMON_CPU_TEMP_ADD         0
#define HWMON_AUX_TEMP_ADD         0

  #pragma pack(1)


  #pragma pack()


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif  // Nct6776F_SETUP_H_
