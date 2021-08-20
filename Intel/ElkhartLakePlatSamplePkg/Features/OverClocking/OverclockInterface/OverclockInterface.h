/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

#ifndef __OverclockingInterface__H__
#define __OverclockingInterface__H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <Base.h>
#include <PiDxe.h>
#include <IndustryStandard/Acpi.h>
#include <Setup.h>
#include <PlatformBoardId.h>
#include <OemSetup.h>

#define STRING_TOKEN(t) t

#define OCASL_FFS_TABLE_STORAGE_GUID \
  { \
    0x22D85435, 0xF24A, 0x43DB, 0x7D, 0x04, 0x01, 0x56, 0x06, 0xDF, 0x21, 0xB1 \
  }

#define ASPT_SIG  0x54505341  // ASPT Signature
#define SPTT_SIG  0x54545053  // SPTT Signature
#define DDDT_SIG  0x44444424  // $DDD Signature
#define SMCD_SIG  0x44434D53  // SMCD Signature
#define SMVD_SIG  0x44564D53  // SMVD Signature
#define IOVX_SIG  0x58564F49  // IOVX Signature
#define LBC_SIG   0x43424C24  // $LBC Signature
#define LBS_SIG   0x53424C24  // $LBS Signature
#define HLBC_SIG  0x43424C48  // HLBC Signature

//
// ASPT table Macro definitions
//
#define ASPT_REVISION       7
#define OEM_ID_LENGTH       6
#define OEM_TABLE_ID_LENGTH 8
#define ASPT_CREATOR_REV    0x97
#define AMR_MEMREGION_COUNT 0

//
// SPTT table Macro definitions
//
#define SPTT_MAJORVER                       1
#define SPTT_MINORVER                       4

#define DEVICE_TYPE0                        0
#define DEVICE_TYPE1                        1
#define DEVICE_TYPE2                        2
#define DEVICE_TYPE4                        4
#define CONTROL_TYPE0                       0
#define CONTROL_TYPE1                       1
#define CONTROL_TYPE2                       2
#define IMPLEMENTATION_TYPE0                0
#define IMPLEMENTATION_TYPE1                1
#define IMPLEMENTATION_TYPE2                2
#define IMPLEMENTATION_TYPE3                3
#define IMPLEMENTATION_TYPE4                4
#define IMPLEMENTATION_TYPE5                5
#define IMPLEMENTATION_TYPE6                6
#define IMPLEMENTATION_TYPE7                7
#define IMPLEMENTATION_TYPE8                8
#define IMPLEMENTATION_TYPE9                9
#define IMPLEMENTATION_TYPE10               10
#define IMPLEMENTATION_TYPE11               11
#define IMPLEMENTATION_TYPE12               12
#define IMPLEMENTATION_TYPE13               13
#define IMPLEMENTATION_TYPE14               14
#define IMPLEMENTATION_TYPE15               15
#define IMPLEMENTATION_TYPE16               16
#define IMPLEMENTATION_TYPE17               17
#define IMPLEMENTATION_TYPE18               18
#define IMPLEMENTATION_TYPE19               19
#define IMPLEMENTATION_TYPE20               20
#define IMPLEMENTATION_TYPE21               21
#define IMPLEMENTATION_TYPE22               22
#define IMPLEMENTATION_TYPE23               23
#define IMPLEMENTATION_TYPE24               24
#define IMPLEMENTATION_TYPE25               25
#define IMPLEMENTATION_TYPE26               26
#define IMPLEMENTATION_TYPE27               27
#define IMPLEMENTATION_TYPE28               28
#define IMPLEMENTATION_TYPE29               29
#define IMPLEMENTATION_TYPE30               30
#define IMPLEMENTATION_TYPE31               31
#define IMPLEMENTATION_TYPE32               32
#define IMPLEMENTATION_TYPE33               33
#define IMPLEMENTATION_TYPE34               34
#define IMPLEMENTATION_TYPE35               35
#define IMPLEMENTATION_TYPE36               36
#define IMPLEMENTATION_TYPE39               39
#define IMPLEMENTATION_TYPE40               40
#define IMPLEMENTATION_TYPE41               41
#define IMPLEMENTATION_TYPE46               46
#define IMPLEMENTATION_TYPE47               47
#define IMPLEMENTATION_TYPE48               48
#define IMPLEMENTATION_TYPE49               49
#define IMPLEMENTATION_TYPE50               50
#define IMPLEMENTATION_TYPE57               57
#define IMPLEMENTATION_TYPE58               58
#define IMPLEMENTATION_TYPE59               59
#define IMPLEMENTATION_TYPE60               60
#define IMPLEMENTATION_TYPE61               61

#define VERSION_0                           0
#define VERSION_1                           1
#define ENABLE_DISABLE_SETTING_ENTRY_COUNT  2
#define STEP_SIZE_1                         1

#define END_OF_DEVICE_COUNT                 1
#define DDDT_COUNT                          (END_OF_DEVICE_COUNT + 21)
#define DSD_DISCRETE_LBS_COUNT              3
#define DSD_CONTINUOUS_LBS_COUNT            15
#define DSD_HP_LBS_COUNT                    3
//
// DDR + EIST
//
#define LBS_SETTINGS_ENTRY_COUNT      (DDR_MODE_SETTING_ENTRY_COUNT + ENABLE_DISABLE_SETTING_ENTRY_COUNT)

#define PRECISION_NONE                0
#define PRECISION_ONE                 1
#define PRECISION_TWO                 2
#define PRECISION_THREE               3
#define PRECISION_FOUR                4
#define PRECISION_FIVE                5
#define PRECISION_EIGHT               8
#define DATA_TYPE_NONE                0
#define DATA_TYPE_MHZ                 1
#define DATA_TYPE_GHZ                 2
#define DATA_TYPE_VOLTS               3
#define DATA_TYPE_CLOCKS              4
#define DATA_TYPE_ENABLE              5
#define DATA_TYPE_DISABLE             6
#define DATA_TYPE_AMPS                7
#define DATA_TYPE_WATTS               8

#define NOT_SUPPORTED                 0
#define SUPPORTED                     1

#define MIN_SETTING_LOW_PERFORMANCE   0
#define MIN_SETTING_HIGH_PERFORMANCE  1

#define AUTOMATIC_MODE                0xFFFFFFFE
#define ZERO                          0
#define WATT_TO_MILLIWATT             1000

//
// Clock device (SMBUS based) Macro definitions
//
#define SMBUS_CLOCK_PROGRAMMING_BYTE_COUNT          18
#define SMBUS_CLOCK_BYTE_COUNT_REGISTER             12
#define SMBUS_CLOCK_BYTE_COUNT_ANDMASK              0
#define SMBUS_CLOCK_BYTE_COUNT_ORMASK               SMBUS_CLOCK_PROGRAMMING_BYTE_COUNT
#define SMBUS_CLOCK_AUTO_MODE_ENTRIES               1
#define SMBUS_CLOCK_SETTING_ENTRY_COUNT             50
#define SMBUS_CLOCK_VALUE_ENTRY_COUNT               3
#define R_SMBUS_CLOCK_CONTROLREG_15                 15
#define R_SMBUS_CLOCK_CONTROLREG_16                 16
#define R_SMBUS_CLOCK_CONTROLREG_17                 17
#define B_SMBBUS_CLOCK_CONTROLREG_17_CPUPLL_CONTROL 0x80

//
// Processor Multiplier Macro definitions
//
#define FLEX_RATIO_MINIMUM    6
#define FLEX_RATIO_MAXIMUM    31
#define FLEX_RATIO_STEP_SIZE  1
#define MAX_OVERCLOCKING_BINS 0x7

//
// CPU Voltage Macro definitions
//
#define SMBUS_VID_DEVICE_SETTING_ENTRY_COUNT  41
#define SMBUS_VID_VALUE_ENTRY_COUNT           4

#define R_SMBUS_CPU_VID_CONTROLREG_2          2     // Bus-hold / pull-up / pull-down Control Reg
#define R_SMBUS_CPU_VID_CONTROLREG_4          4     // Direction of I/O Pins
#define R_SMBUS_CPU_VID_CONTROLREG_5          5     // Output Port Register
#define CPU_VOLTAGE_MINIMUM_VALUE             9000  // The value is with precision 4. Actual base is 0.9000 Volts
#define CPU_VOLTAGE_MAXIMUM_VALUE             14000
#define CPU_VOLTAGE_MINIMUM_DATA              48
#define CPU_VOLTAGE_MAXIMUM_DATA              8
#define CPU_VOLTAGE_VALUE_STEP_SIZE           125
#define CPU_VOLTAGE_DATA_STEP_SIZE            1

//
// Memory Voltage Macro definitions
//
#define MEMORY_VOLTAGE_BASE               150
#define MEMORY_VOLTAGE_VALUE_COUNT        1
#define MEMORY_VOLTAGE_VALUE_COUNT_EL_FAB2 2
#define SIOGPIO_MEMORY_VOLTAGE_IO_OFFSET  0x0E
#define SIOGPIO_MEMORY_VOLTAGE_ANDMASK    0xF3
#define PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_DESKTOP  ~((1 << 28) | (1 << 14) | (1 << 13))
#define PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_1_EL_FAB2  ~(1 << 8)
#define PCH_GPIO_MEMORY_VOLTAGE_AND_MASK_2_EL_FAB2  ~(1 << 14)
#define LEGACY_IO_TYPE                    2
#define DONT_CARE_TYPE                    0xFFFFFFFF
#define MEMORY_VOLTAGE_OVERRIDE_INFO      0
#define MEMORY_VOLTAGE_DATA_SIZE_SIO_GPIO 8
#define MEMORY_VOLTAGE_DATA_SIZE_GPIO     32
#define MEMORY_VOLTAGE_MINIMUM_VALUE      150
#define MEMORY_VOLTAGE_MAXIMUM_VALUE      165
#define MEMORY_VOLTAGE_MINIMUM_DATA       0
#define MEMORY_VOLTAGE_MAXIMUM_DATA       3
#define MEMORY_VOLTAGE_VALUE_STEP_SIZE    5
#define MEMORY_VOLTAGE_DATA_STEP_SIZE     1

//
// Memory Frequency Macro definitions
//
#define MEMORY_FREQ_AUTO_VALUE  0
#define MEMORY_FREQ_1067_VALUE  1
#define MEMORY_FREQ_1333_VALUE  2
#define MEMORY_FREQ_1600_VALUE  3
#define MEMORY_FREQ_1867_VALUE  4
#define MEMORY_FREQ_2133_VALUE  5

#define MEMORY_FREQ_1067        1067
#define MEMORY_FREQ_1333        1333
#define MEMORY_FREQ_1600        1600
#define MEMORY_FREQ_1867        1867
#define MEMORY_FREQ_2133        2133

//
// All the minimum and maximum values are specified in DCLK units
//

//
// tCL Macro definitions
//
#define tCL_MINIMUM   0
#define tCL_MAXIMUM   31
#define tCL_STEP_SIZE 1

//
// tRCDtRP Macro definitions
//
#define tRCD_tRP_MINIMUM    0
#define tRCD_tRP_MAXIMUM    63
#define tRCD_tRP_STEP_SIZE  1

//
// tRAS Macro definitions
//
#define tRAS_MINIMUM    0
#define tRAS_MAXIMUM    64
#define tRAS_STEP_SIZE  1

//
// tWR Macro definitions
//
#define tWR_MINIMUM   5
#define tWR_MAXIMUM   24
#define tWR_STEP_SIZE 1

//
// tRFC Macro definitions
//
#define tRFC_MINIMUM    0
#define tRFC_MAXIMUM    1023
#define tRFC_STEP_SIZE  1

//
// tRRD Macro definitions
//
#define tRRD_MINIMUM    0
#define tRRD_MAXIMUM    15
#define tRRD_STEP_SIZE  1

//
// tWTR Macro definitions
//
#define tWTR_MINIMUM    0
#define tWTR_MAXIMUM    28
#define tWTR_STEP_SIZE  1

//
// tRTP Macro definitions
//
#define tRTP_MINIMUM    0
#define tRTP_MAXIMUM    15
#define tRTP_STEP_SIZE  1

//
// tFAW Macro definitions
//
#define tFAW_MINIMUM    0
#define tFAW_MAXIMUM    63
#define tFAW_STEP_SIZE  1

//
// CMD Rate Macro definitions
//
#define SYSTEM_CMD_RATE_MINIMUM   0
#define SYSTEM_CMD_RATE_MAXIMUM   2
#define SYSTEM_CMD_RATE_STEP_SIZE 1

//
// DDR Multiplier Macro definitions
//
#define DDR_MODE_SETTING_ENTRY_COUNT    5
#define DDR_MULTIPLIER_MINIMUM_VALUE    6
#define DDR_MULTIPLIER_MAXIMUM_VALUE    12
#define DDR_MULTIPLIER_VALUE_STEP_SIZE  2
#define DDR_MULTIPLIER_MINIMUM_DATA     1
#define DDR_MULTIPLIER_MAXIMUM_DATA     4
#define DDR_MULTIPLIER_DATA_STEP_SIZE   1

//
// Turbo Mode Macro definitions
//
#define TURBO_MODE_SETTING_ENTRY_COUNT  2
#define TURBO_MODE_DISABLE              0
#define TURBO_MODE_ENABLE               1
#define TURBO_MODE_STEP_SIZE            1

//
// TDP LIMIT Macro definitions
//
#define TDP_MINIMUM   0
#define TDP_MAXIMUM   4095
#define TDP_STEP_SIZE 1

//
#define POWER_LIMIT1_TIME_MINIMUM   0
#define POWER_LIMIT1_TIME_MAXIMUM   128
#define POWER_LIMIT1_TIME_STEP_SIZE 1
//
// CORE1 RATIO LIMIT Macro definitions
//
#define CORE1_RATIO_MINIMUM   0
#define CORE1_RATIO_MAXIMUM   80
#define CORE1_RATIO_STEP_SIZE 1

//
// CORE2 RATIO LIMIT Macro definitions
//
#define CORE2_RATIO_MINIMUM   0
#define CORE2_RATIO_MAXIMUM   80
#define CORE2_RATIO_STEP_SIZE 1

//
// CORE3 RATIO LIMIT Macro definitions
//
#define CORE3_RATIO_MINIMUM   0
#define CORE3_RATIO_MAXIMUM   80
#define CORE3_RATIO_STEP_SIZE 1

//
// CORE4 RATIO LIMIT Macro definitions
//
#define CORE4_RATIO_MINIMUM   0
#define CORE4_RATIO_MAXIMUM   80
#define CORE4_RATIO_STEP_SIZE 1

//
// CORE5 RATIO LIMIT Macro definitions
//
#define CORE5_RATIO_MINIMUM   0
#define CORE5_RATIO_MAXIMUM   80
#define CORE5_RATIO_STEP_SIZE 1

//
// CORE6 RATIO LIMIT Macro definitions
//
#define CORE6_RATIO_MINIMUM   0
#define CORE6_RATIO_MAXIMUM   80
#define CORE6_RATIO_STEP_SIZE 1

//
// CORE7 RATIO LIMIT Macro definitions
//
#define CORE7_RATIO_MINIMUM   0
#define CORE7_RATIO_MAXIMUM   80
#define CORE7_RATIO_STEP_SIZE 1

//
// CORE8 RATIO LIMIT Macro definitions
//
#define CORE8_RATIO_MINIMUM   0
#define CORE8_RATIO_MAXIMUM   80
#define CORE8_RATIO_STEP_SIZE 1

//
// XE
//
#define XE_EXTRA_VOLTAGE_MINIMUM      0
#define XE_EXTRA_VOLTAGE_MAXIMUM      99609375  // Voltage is reported in 8 decimal place precision. Max voltage is 0.996 Volt
#define XE_EXTRA_VOLTAGE_MINIMUM_DATA 0
#define XE_EXTRA_VOLTAGE_MAXIMUM_DATA 255
#define XE_EXTRA_VOLTAGE_STEP_SIZE    390625    // 1/256 * 10^8 = 390625
#define XE_EXTRA_VOLTAGE_PRECISION    8
//
// Primary Plane Current Limit
//
#define PRIMARY_PLANE_CURRENT_LIMIT_MINIMUM       0
#define PRIMARY_PLANE_CURRENT_LIMIT_MAXIMUM       1023875 // Current limit is in 3 deminal place precision (1023.875 A)
#define PRIMARY_PLANE_CURRENT_LIMIT_MINIMUM_DATA  0
#define PRIMARY_PLANE_CURRENT_LIMIT_MAXIMUM_DATA  0x1FFF  // Current limit is in 3 deminal place precision (1023.875 A)
#define PRIMARY_PLANE_CURRENT_LIMIT_STEP_SIZE     125     // 1/8 A = 0.125 A
//
// Secondary Plane Current Limit
//
#define SECONDARY_PLANE_CURRENT_LIMIT_MINIMUM       0
#define SECONDARY_PLANE_CURRENT_LIMIT_MAXIMUM       1023875 // Current limit is in 3 deminal place precision (1023.875 A)
#define SECONDARY_PLANE_CURRENT_LIMIT_MINIMUM_DATA  0
#define SECONDARY_PLANE_CURRENT_LIMIT_MAXIMUM_DATA  0x1FFF  // Current limit is in 3 deminal place precision (1023.875 A)
#define SECONDARY_PLANE_CURRENT_LIMIT_STEP_SIZE     125     // 1/8 A = 0.125 A
//
// Internal Graphics Frequency Ratio
//
#define IGD_FREQ_RATIO_LIMIT_MINIMUM        0
#define IGD_FREQ_RATIO_LIMIT_MAXIMUM        60
#define IGD_FREQ_RATIO_DISPLAY_MAX          300
#define IGD_FREQ_RATIO_LIMIT_STEP_SIZE      1

//
// Internal Graphics Voltage
//
#define IGD_VOLTAGE_LIMIT_MINIMUM       0
#define IGD_VOLTAGE_LIMIT_MAXIMUM       99609375  // Max IGfx voltage = 0.996 V (8 decimal place precision)
#define IGD_VOLTAGE_LIMIT_MINIMUM_DATA  0
#define IGD_VOLTAGE_LIMIT_MAXIMUM_DATA  255
#define IGD_VOLTAGE_LIMIT_STEP_SIZE     390625

//
// Ring Ratio
//
#define RING_RATIO_MINIMUM              0
#define RING_RATIO_MAXIMUM              80

//
// iVR Voltage Override range
//
#define IVR_VOLTAGE_MINIMUM             0
#define IVR_VOLTAGE_MAXIMUM             2000

//
// iVR Offset ranges
//

// XTU Spec supports negative display values, but not data values. The offset range is -1000 to 1000.
// BIOS will represent the data value as 0 to 2000 and interpret 0 to 1000 as -1000 to 0, and 1001 to 2000
// as 1 to 1000. This is done int he Overclock SMI handler code.
#define IVR_VOLTAGE_OFFSET_DEFAULT_VAL  1000        // 1000 maps to 0 for XTU display
#define IVR_VOLTAGE_OFFSET_MIN_DATA_VAL 0
#define IVR_VOLTAGE_OFFSET_MAX_DATA_VAL 2000
#define IVR_VOLTAGE_OFFSET_MIN_DISP_VAL 0xFFFFFC18  // -1000 in 2's complement representation
#define IVR_VOLTAGE_OFFSET_MAX_DISP_VAL 1000

//
// SVID Voltage Override range
//
#define SVID_VOLTAGE_MINIMUM             0
#define SVID_VOLTAGE_MAXIMUM             2500

#define INIT_DDDT(DddtP, Sign, DType, CType, IType, Revision) { \
    (DddtP)->Signature                  = (Sign); \
    (DddtP)->DevType                    = (DType); \
    (DddtP)->ControlType                = (CType); \
    (DddtP)->ImpType                    = (IType); \
    (DddtP)->DeviceSpecificDataRevision = (Revision); \
  }

#define MEMORY_CLOCK_FREQ_MINIMUM          100
#define MEMORY_CLOCK_FREQ_MAXIMUM          133

#define R_SA_MC_CAPID0_A_OFFSET            0xE4
#define PCIE_RATIO_DIS_MASK              0x00040000
#define PCIE_RATIO_DIS_OFFSET            18
#pragma pack(1)
//
// Overclocking Interface structure definitions
//
//
// ACPI System Performance Tuning Table(ASPT)
//
typedef struct _ASPT_20 {
  EFI_ACPI_DESCRIPTION_HEADER Header;
  UINT64      SpttAdd;
  UINT64      Reserved;
} ASPT_20;

//
// System Performance Tuning Table(SPTT)
//
typedef struct _SPTT {
  UINT32  Signature;
  UINT32  Length;
  UINT16  MajorVer;
  UINT16  MinorVer;
  UINT32  Reserved1;
  UINT32  Reserved2;
  UINT32  Reserved3;
  UINT16  SmiPort;
  UINT8   SmiCmdValue;
  UINT8   Checksum;
  UINT32  FeatureFlags;
} SPTT;

//
// Device Description Data Table(DDDT) structure
//
typedef struct _DDDT {
  UINT32  Signature;
  UINT8   DevType;
  UINT8   ControlType;
  UINT8   ImpType;
  UINT8   DeviceSpecificDataRevision;
} DDDT;

//
// Voltage Value Entry (GPIO based)
//
typedef struct _VOLTAGE_VALUE_ENTRY {
  UINT32  Offset;
  UINT32  AndMask;
  UINT32  OrMask;
} VOLTAGE_VALUE_ENTRY;

//
// Voltage device Setting Entry (GPIO based)
//
typedef struct _VOLTAGE_DEVICE_SETTING_ENTRY {
  UINT32              SettingValue;
  UINT8               SettingPrecision;
  UINT8               SettingFlags;
  UINT16              VoltageValueEntryCount;
  VOLTAGE_VALUE_ENTRY VoltageValueEntry[1];
} VOLTAGE_DEVICE_SETTING_ENTRY;

//
// Voltage device Setting Entry (GPIO based) with 2 Voltage Value Entries
//
typedef struct _VOLTAGE_DEVICE_SETTING_ENTRY_2 {
  UINT32              SettingValue;
  UINT8               SettingPrecision;
  UINT8               SettingFlags;
  UINT16              VoltageValueEntryCount;
  VOLTAGE_VALUE_ENTRY VoltageValueEntry[2];
} VOLTAGE_DEVICE_SETTING_ENTRY_2;
//
// Device Specific data for Voltage device (GPIO based)
//
typedef struct _DSD_GPIO_VOLTAGE_DEVICE {
  UINT32  Signature;
  UINT16  VoltageSettingCount;
  UINT8   IoType;
  UINT8   UseIndexPort;
  UINT32  IndexPort;
  UINT32  BaseAddress;
  UINT8   DataSize;
  UINT8   Reserved[3];
  UINT32  HardwareControlledModeSettingValue;
  UINT8   HardwareControlledModeSettingPrecision;
  UINT8   HardwareControllerModeSupportFlags;
  UINT16  NumOfVoltageControllerHwControlledModeEntries;
  //
  // VOLTAGE_DEVICE_SETTING_ENTRY VoltageDevEntry[MEMORY_VOLTAGE_DEVICE_SETTING_COUNT];
  //
} DSD_GPIO_VOLTAGE_DEVICE;

//
// Clock value entry for Clock device - SmBus based
//
typedef struct _CLOCK_VALUE_ENTRY {
  UINT8 ByteIndex;
  UINT8 AND_Mask;
  UINT8 OR_Mask;
  UINT8 Reserved;
} CLOCK_VALUE_ENTRY;

//
// Device setting entry for Clock device - SmBus based
//
typedef struct _CLOCKDEVICE_SETTING_ENTRY {
  UINT16            SettingValue;
  UINT8             SettingPrecision;
  UINT8             Reserved;
  CLOCK_VALUE_ENTRY ClockValueEntry[SMBUS_CLOCK_VALUE_ENTRY_COUNT];
} CLOCKDEVICE_SETTING_ENTRY;

//
// Automatic mode entry for Clock device - SmBus based
//
typedef struct _AUTOMATIC_MODE_ENTRY {
  UINT8 AutoModeByteIndex;
  UINT8 AutoModeAndMask;
  UINT8 AutoModeOrMask;
  UINT8 Reserved;
} AUTOMATIC_MODE_ENTRY;

//
// Device Specific data for Clock device - SmBus based
//
typedef struct _DSD_SMBUS_CLOCK_DEVICE {
  UINT32                    Signature;
  UINT8                     SmBusAddress;
  UINT8                     Reserved1;
  UINT16                    AutoModeSettingValue;
  UINT8                     AutoModeSettingPrecision;
  UINT8                     Reserved2;
  UINT16                    AutoModeEntries;
  UINT8                     ByteCount;
  UINT8                     ByteCountLocation;
  UINT8                     ByteCountANDMask;
  UINT8                     ByteCountORMask;
  UINT8                     PCIDerivedClock;
  UINT8                     PCIRatioMultiplier;
  UINT8                     PCIRatioDivider;
  UINT8                     Reserved3;
  UINT16                    ClockValueEntryCount;
  UINT16                    SettingsEntryCount;
  AUTOMATIC_MODE_ENTRY      AutoModeEntry[SMBUS_CLOCK_AUTO_MODE_ENTRIES];
  CLOCKDEVICE_SETTING_ENTRY ClockSettingEnty[SMBUS_CLOCK_SETTING_ENTRY_COUNT];
} DSD_SMBUS_CLOCK_DEVICE;

//
// Logical BIOS Settings Device Specific Data
//
typedef struct _DSD_LBS {
  UINT32  Signature;
  UINT8   AutoModeSupport;
  UINT8   Reserved1;
  UINT16  DefaultSetting;
  UINT16  LBSEntryCount;
  UINT16  Reserved2;
} DSD_LBS;

//
// Logical BIOS Device Setting Entry
//
typedef struct _LBS_SETTINGS_ENTRY {
  UINT16  SettingValue;
  UINT8   SettingPrecision;
  UINT8   DataTypeEnumeration;
  UINT16  BiosSettingsValue;
  UINT8   SettingFlag;
  UINT16  Reserved;
  UINT8   Reserved1;
} LBS_SETTINGS_ENTRY;

//
// Logical BIOS Settings Device Specific Data - Continuous
//
typedef struct _DSD_CONTINUOUS_LBS {
  UINT32  Signature;
  UINT16  MinimumSettingValue;
  UINT16  MaximumSettingValue;
  UINT8   StepSize;
  UINT8   DataTypeEnumeration;
  UINT8   AutoModeSupport;
  UINT8   PerformanceFlag;
  UINT16  DefaultSetting;
  UINT8   SettingPrecision;
  UINT8   Reserved;
} DSD_CONTINUOUS_LBS;

//
// Logical BIOS Settings Device Specific Data - High Precision
//
typedef struct _DSD_HP_LBS {
  UINT32  Signature;
  UINT32  MinimumSettingValue;
  UINT32  MaximumSettingValue;
  UINT32  ValueStepSize;
  UINT8   SettingPrecision;
  UINT8   Reserved1;
  UINT16  MinimumSettingData;
  UINT16  MaximumSettingData;
  UINT16  DataStepSize;
  UINT8   DataTypeEnumeration;
  UINT8   AutoModeSupport;
  UINT8   PerformanceFlag;
  UINT8   Reserved2;
  UINT16  DefaultSettingData;
  UINT16  Reserved3;
} DSD_HP_LBS;

#pragma pack()

//
// Define function prototypes
//
/**
  OverClocking Interface callback gets executed on ReadyToBoot Event

  @param[in] Event              Pointer to the event that triggered this Callback Function
  @param[in] Context            VOID Pointer required for Callback function

  @retval EFI_OUT_OF_RESOURCES  The function fails due to Out of Resources.
  @retval EFI_SUCCESS           The function completed successfully.
**/
VOID
EFIAPI
RegisterProtocolOverClockingInterface (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
;

/**
  Create control ids table in ACPI NVS memory.

**/
EFI_STATUS
CreateControlIDs (
  VOID
  )
;

/**
  Calculates checksum for table.

  @param[in] TblStart        Start Address of the Table
  @param[in] BytesCount      Number of Bytes Count

  @retval Checksum           Return to the Checksum value of the table
**/
UINT8
ChecksumTable (
  IN  UINT8     *TblStart,
  IN  UINT32    BytesCount
  )
;

/**
  This function will start the Watchdog Timer.

  @param[in] TimeoutValue     Time out value in seconds

  @retval EFI_SUCCESS         Start the Watchdog Timer successfully

  Appropiate failure code on error.

**/
EFI_STATUS
StartTimer (
  IN  UINT32  TimeoutValue
  )
;

typedef struct ControlIdData  {
   UINT32 ControlId;
   UINT16 NumberOfValues;
   UINT8 Precision;
   UINT8 Flags;
   UINT32 DefaultDataValue;
   UINT32 MinDataValue;
   UINT32 MaxDataValue;
   UINT32 MinDisplayValue;
   UINT32 MaxDisplayValue;
}CONTROLID_DATA;

#define SUPPORTED_CONTROL_ID_COUNT 49
typedef struct ControlBuffer  {
   CONTROLID_DATA ControlIDData[SUPPORTED_CONTROL_ID_COUNT];
}CONTROLID_BUFF;

typedef struct XmpTimingControl  {
   UINT16 ControlID;
   UINT8  Reserved;
   UINT8  Precision;
   UINT32 DisplayValue;
}XMP_TIMING_CONTROL;

typedef struct XMPProfile  {
   XMP_TIMING_CONTROL Control[9];
}XMP_PROFILE;

typedef struct XMPBuffer  {
   XMP_PROFILE XmpProfile[2];
}XMP_BUFF;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
