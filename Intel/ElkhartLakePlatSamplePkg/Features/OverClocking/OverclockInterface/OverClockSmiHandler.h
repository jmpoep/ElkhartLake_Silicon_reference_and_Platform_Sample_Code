/** @file
  Header for OverclockSmiHandler Module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

#ifndef __OverclockSmiHandler__H__
#define __OverclockSmiHandler__H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "Setup.h"
#include "OverclockInterface.h"

//
// Number of entries in the SMI BIOS table which do not have
// conditional logic associated with adding to the table.
//
#define NO_OF_BIOS_SETTING_STATIC_ENTRIES 40

typedef struct _BIOS_SETTING_ENTRY {
  UINT32  BiosImplementationType;
  UINT32  SettingValue;
} BIOS_SETTING_ENTRY;

typedef struct _BIOS_SETTINGS_DATA_HEADER {
  UINT32  Signature;
  UINT32  Length;
  UINT16  MajorRev;
  UINT16  MinorRev;
  UINT32  Count;
} BIOS_SETTINGS_DATA_HEADER;

#define BIOSSETTINGS_SIG_REV3                     0x24444224  // $BD$ Signature
#define BIOSSETTINGS_SIG_REV4                     0x32444224  // $BD2 Signature
#define ENABLE_SUPPRORT                           1
#define DISABLE_SUPPRORT                          0
#define AUTO                                      0

#define OVERCLOCK_SMI_READ_COMMAND                0
#define OVERCLOCK_SMI_WRITE_COMMAND               1
#define OVERCLOCK_SMI_WDT_CONFIRM_REQUEST_COMMAND 2

#define SUCCESSFUL_BOOT                           0
#define MAX_TIME_OUT                              0xFFFFFFFF

#define SPD_PROFILE_CUSTOM                        1

#define VOLTAGE_MODE_ADAPTIVE                     0
#define VOLTAGE_MODE_OVERRIDE                     1

//
// BIOS Setting Device Data defines
//
#define BIOS_DEVICE_FLEX_RATIO                     0
#define BIOS_DEVICE_HOST_CLK_FREQ                  0x1
#define BIOS_DEVICE_CPU_VOLTAGE                    0x2
#define BIOS_DEVICE_MEMORY_VOLTAGE                 0x5
#define BIOS_DEVICE_tCL                            0x7
#define BIOS_DEVICE_tRCD_tRP                       0x8
#define BIOS_DEVICE_tRAS                           0xA
#define BIOS_DEVICE_tWR                            0xB
#define BIOS_DEVICE_DDR_MULTIPLIER                 0x13
#define BIOS_DEVICE_tRFC                           0x15
#define BIOS_DEVICE_tRRD                           0x16
#define BIOS_DEVICE_tWTR                           0x17
#define BIOS_DEVICE_SYSTEM_CMD_RATE                0x18
#define BIOS_DEVICE_tRTP                           0x19
#define BIOS_DEVICE_TURBO_MODE                     0x1A
#define BIOS_DEVICE_1_CORE_RATIO_LIMIT             0x1D
#define BIOS_DEVICE_2_CORE_RATIO_LIMIT             0x1E
#define BIOS_DEVICE_3_CORE_RATIO_LIMIT             0x1F
#define BIOS_DEVICE_4_CORE_RATIO_LIMIT             0x20
#define BIOS_DEVICE_5_CORE_RATIO_LIMIT             0x2A
#define BIOS_DEVICE_6_CORE_RATIO_LIMIT             0x2B
#define BIOS_DEVICE_7_CORE_RATIO_LIMIT             0x60
#define BIOS_DEVICE_8_CORE_RATIO_LIMIT             0x61
#define BIOS_DEVICE_IA_CORE_VOLTAGE_OFFSET         0x22
#define BIOS_DEVICE_tFAW                           0x28
#define BIOS_DEVICE_EIST                           0x29
#define BIOS_DEVICE_MAX_TURBO_MODE_CPU_VOLTAGE     0x2E
#define BIOS_DEVICE_SHORT_WINDOW_TDP_LIMIT         0x2F
#define BIOS_DEVICE_EXTENDED_TDP_LIMIT             0x30
#define BIOS_DEVICE_SHORT_WINDOW_POWER_ENABLE      0x31
#define BIOS_DEVICE_TURBO_POWER_LIMIT_LOCK         0x32
#define BIOS_DEVICE_PRIMARY_PLANE_CURRENT_LIMIT    0x39
#define BIOS_DEVICE_SECONDARY_PLANE_CURRENT_LIMIT  0x3A
#define BIOS_DEVICE_IGFX_FREQUENCY                 0x3B
#define BIOS_DEVICE_IGFX_VOLTAGE                   0x3C
#define BIOS_DEVICE_XMP_PROFILE                    0x40
#define BIOS_DEVICE_TURBO_BOOST_POWER_TIME_WINDOWS 0x42
#define BIOS_DEVICE_MEMORY_CLOCK_FREQUENCY         0x49
#define BIOS_DEVICE_FILTER_PLL                     0x4A
#define BIOS_DEVICE_RING_RATIO                     0x4C
#define BIOS_DEVICE_OC_ENABLE                      0x50
#define BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE          0x51
#define BIOS_DEVICE_IGFX_VOLTAGE_MODE              0x52
#define BIOS_DEVICE_IGFX_VOLTAGE_OFFSET            0x53
#define BIOS_DEVICE_SA_VOLTAGE_OFFSET              0x55
#define BIOS_DEVICE_IA_CORE_VOLTAGE_MODE           0x58
// IGFX UNSLICE
#define BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_MODE      0x62
#define BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE  0x63
#define BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OFFSET    0x64
#define BIOS_DEVICE_IGFX_UNSLICE_FREQUENCY         0x65
// ICC MAX
#define BIOS_DEVICE_IA_CURRENT_LIMIT_MAX           0x66
#define BIOS_DEVICE_SA_CURRENT_LIMIT_MAX           0x67
#define BIOS_DEVICE_GTS_CURRENT_LIMIT_MAX          0x68
#define BIOS_DEVICE_GTUS_CURRENT_LIMIT_MAX         0x69
#define BIOS_DEVICE_RING_CURRENT_LIMIT_MAX         0x6A
// Core AVX Ratio
#define BIOS_DEVICE_IA_AVX2_CORE_RATIO_OFFSET      0x72
#define BIOS_DEVICE_IA_AVX3_CORE_RATIO_OFFSET      0x73

#define ADD_ENTRY_TO_BIOS_SETTING_TABLE(BiosSettingEntriesArray, Index, SetupValue, ImplementationType) \
  BiosSettingEntriesArray[Index].BiosImplementationType = ImplementationType; \
  BiosSettingEntriesArray[Index].SettingValue = SetupValue; \
  Index++

#define ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC(BiosSettingEntriesArray, Index, SetupValue, ImplementationType, DefaultValue) \
  BiosSettingEntriesArray[Index].BiosImplementationType = ImplementationType; \
  if (SetupValue == DefaultValue) { \
    BiosSettingEntriesArray[Index].SettingValue = AUTOMATIC_MODE; \
  } else { \
    BiosSettingEntriesArray[Index].SettingValue = SetupValue; \
  } \
  Index++

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // OverclockSmiHandler
