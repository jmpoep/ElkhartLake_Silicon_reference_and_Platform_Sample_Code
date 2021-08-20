/** @file
  Include file for Industry Standard ASF definition

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _INDUSTRY_STANDARD_ASF_H_
#define _INDUSTRY_STANDARD_ASF_H_

#pragma pack (1)

#define ASF_VERSION 0x10

///
/// ASF Messages Command
///
#define ASF_MESSAGE_COMMAND_SENSOR_DEVICE_SYSTEM_STATE 0x01
#define ASF_MESSAGE_COMMAND_MANAGEMENT_CONTROL         0x02
#define ASF_MESSAGE_COMMAND_ASF_CONFIGURATION          0x03
#define ASF_MESSAGE_COMMAND_MESSAGE                    0x04

///
/// ASF Messages Sub-Command for Command SENSOR_DEVICE_SYSTEM_STATE (0x01)
///
#define ASF_MESSAGE_SUBCOMMAND_GET_EVENT_DATA         0x11
#define ASF_MESSAGE_SUBCOMMAND_GET_EVENT_STATUS       0x12
#define ASF_MESSAGE_SUBCOMMAND_DEVICE_TYPE_POLL       0x13
#define ASF_MESSAGE_SUBCOMMAND_SET_SYSTEM_STATE       0x18

///
/// ASF Messages Sub-Command for Command MANAGEMENT_CONTROL (0x02)
///
#define ASF_MESSAGE_SUBCOMMAND_START_WATCH_DOG_TIMER  0x13
#define ASF_MESSAGE_SUBCOMMAND_STOP_WATCH_DOG_TIMER   0x14

///
/// ASF Messages Sub-Command for Command ASF_CONFIGURATION (0x03)
///
#define ASF_MESSAGE_SUBCOMMAND_CLEAR_BOOT_OPT         0x15
#define ASF_MESSAGE_SUBCOMMAND_RETURN_BOOT_OPT        0x16
#define ASF_MESSAGE_SUBCOMMAND_NO_BOOT_OPT            0x17

///
/// ASF Messages Sub-Command for Command MESSAGE (0x04)
///
#define ASF_MESSAGE_SUBCOMMAND_SET_ALERT_CONFIG       0x11
#define ASF_MESSAGE_SUBCOMMAND_GET_ALERT_CONFIG       0x12
#define ASF_MESSAGE_SUBCOMMAND_RETRANSMIT             0x15
#define ASF_MESSAGE_SUBCOMMAND_NORETRANSMIT           0x16

///
/// ASF Event Sensor Type Codes
///
#define ASF_EVENT_SENSOR_TYPE_TEMPERATURE             0x01
#define ASF_EVENT_SENSOR_TYPE_VOLTAGE                 0x02
#define ASF_EVENT_SENSOR_TYPE_FAN                     0x04
#define ASF_EVENT_SENSOR_TYPE_CHASSIS_INTRUSION       0x05
#define ASF_EVENT_SENSOR_TYPE_SECURITY_VIOLATION      0x06
#define ASF_EVENT_SENSOR_TYPE_PROCESSOR               0x07
#define ASF_EVENT_SENSOR_TYPE_POWER_SUPPLY            0x08
#define ASF_EVENT_SENSOR_TYPE_POWER_UNIT              0x09
#define ASF_EVENT_SENSOR_TYPE_SYS_FW_ERR_PROG         0x0F
#define ASF_EVENT_SENSOR_TYPE_CHIPSET                 0x19
#define ASF_EVENT_SENSOR_TYPE_BOOT_ERROR              0x1E
#define ASF_EVENT_SENSOR_TYPE_OS_BOOT                 0x1F
#define ASF_EVENT_SENSOR_TYPE_WATCHDOG2               0x23
#define ASF_EVENT_SENSOR_TYPE_ENTITY_PRESENCE         0x25
#define ASF_EVENT_SENSOR_TYPE_BATTERY                 0x29

///
/// ASF Event Type Codes
/// IPMI/PET related definition
///
#define ASF_EVENT_TYPE_THRESHOLD_BASED                0x01
#define ASF_EVENT_TYPE_USAGE_STATE                    0x02
#define ASF_EVENT_TYPE_DISCRETE_EVENT_STATE           0x03
#define ASF_EVENT_TYPE_DISCRETE_EVENT_PREDICTIVE_FAIL 0x04
#define ASF_EVENT_TYPE_DISCRETE_EVENT_LIMIT           0x05
#define ASF_EVENT_TYPE_DISCRETE_EVENT_PERFORMANCE     0x06
#define ASF_EVENT_TYPE_SEVERITY_STATE                 0x07
#define ASF_EVENT_TYPE_AVAILABILITY_STATUS_PRESENT    0x08
#define ASF_EVENT_TYPE_AVAILABILITY_STATUS_ENABLE     0x09
#define ASF_EVENT_TYPE_AVAILABILITY_STATUS_RUNNING    0x0A
#define ASF_EVENT_TYPE_AVAILABILITY_STATUS_OTHER      0x0B
#define ASF_EVENT_TYPE_DEVICE_POWER_STATES            0x0C
#define ASF_EVENT_TYPE_SENSOR_SPECIFIC                0x6F

///
/// ASF Event Offset Codes
/// IPMI/PET related definition
///
#define ASF_EVENT_OFFSET_ENTITY_PRESENT                           0x00
#define ASF_EVENT_OFFSET_TIMER_EXPIRED                            0x00

#define ASF_EVENT_OFFSET_SYS_FW_ERROR                             0x00
#define ASF_EVENT_OFFSET_SYS_FW_HANG                              0x01
#define ASF_EVENT_OFFSET_SYS_FW_PROGRESS                          0x02

#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_NONCRITICAL              0x00
#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_NONCRITICAL_GO_HIGH      0x01
#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_CRITICAL                 0x02
#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_CRITICAL_GO_HIGH         0x03
#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_NONRECOVERABLE           0x04
#define ASF_EVENT_OFFSET_THRESHOLD_LOWER_NONRECOVERABLE_GO_HIGH   0x05
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_NONCRITICAL_GO_LOW       0x06
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_NONCRITICAL              0x07
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_CRITICAL_GO_LOW          0x08
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_CRITICAL                 0x09
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_NONRECOVERABLE_GO_LOW    0x0A
#define ASF_EVENT_OFFSET_THRESHOLD_UPPER_NONRECOVERABLE           0x0B

#define ASF_EVENT_OFFSET_DISCRETE_EVENT_PREDICTIVE_FAIL_DEASSERT  0x00
#define ASF_EVENT_OFFSET_DISCRETE_EVENT_PREDICTIVE_FAIL_ASSERT    0x01

#define ASF_EVENT_OFFSET_SEVERITY_TO_OK                           0x00
#define ASF_EVENT_OFFSET_SEVERITY_MORE_NONCRITICAL                0x01
#define ASF_EVENT_OFFSET_SEVERITY_MORE_CRITICAL                   0x02
#define ASF_EVENT_OFFSET_SEVERITY_MORE_NONRECOVERABLE             0x03
#define ASF_EVENT_OFFSET_SEVERITY_LESS_NONCRITICAL                0x04
#define ASF_EVENT_OFFSET_SEVERITY_LESS_CRITICAL                   0x05
#define ASF_EVENT_OFFSET_SEVERITY_TO_NONRECOVERABLE               0x06
#define ASF_EVENT_OFFSET_SEVERITY_MONITOR                         0x07
#define ASF_EVENT_OFFSET_SEVERITY_INFORMATIONAL                   0x08

#define ASF_EVENT_OFFSET_CHASSIS_INTRUSION_GENERIC                0x00

#define ASF_EVENT_OFFSET_PROCESSOR_IERR                           0x00

#define ASF_EVENT_OFFSET_SECURITY_VIOLATION_USER_PASSWORD         0x01
#define ASF_EVENT_OFFSET_SECURITY_VIOLATION_SUPERVISOR_PASSWORD   0x02
#define ASF_EVENT_OFFSET_SECURITY_VIOLATION_NETWORK_PASSWORD      0x03
#define ASF_EVENT_OFFSET_SECURITY_VIOLATION_OTHER_PASSWORD        0x04
#define ASF_EVENT_OFFSET_SECURITY_VIOLATION_OUTOFBAND_PASSWORD    0x05

#define ASF_EVENT_OFFSET_BATTERY_LOW_WARNING                      0x00
#define ASF_EVENT_OFFSET_BATTERY_LOW_CRITICAL                     0x01
#define ASF_EVENT_OFFSET_BATTERY_PRESENCE_DETECTED                0x02

#define ASF_EVENT_OFFSET_POWER_SUPPLY_PRESENCE                    0x00
#define ASF_EVENT_OFFSET_POWER_SUPPLY_FAILURE                     0x01
#define ASF_EVENT_OFFSET_POWER_SUPPLY_PREDICTIVE_FAILURE          0x02

#define ASF_EVENT_OFFSET_POWER_UNIT_DOWN                          0x00
#define ASF_EVENT_OFFSET_POWER_UNIT_CYCLE                         0x01
#define ASF_EVENT_OFFSET_POWER_UNIT_240VA_DOWN                    0x02
#define ASF_EVENT_OFFSET_POWER_UNIT_INTERLOCK_DOWN                0x03
#define ASF_EVENT_OFFSET_POWER_UNIT_AC_LOST                       0x04
#define ASF_EVENT_OFFSET_POWER_UNIT_SOFT_CONTROL_FAILURE          0x05
#define ASF_EVENT_OFFSET_POWER_UNIT_FAILURE                       0x06

#define ASF_EVENT_OFFSET_REMOTE_SECURE_ERASE_FW_ERROR             0x03
#define ASF_EVENT_OFFSET_REMOTE_SECURE_ERASE_FW_PROGRESS          0x05


///
/// ASF Event Source Type Code
/// IPMI/PET related definition
///
#define ASF_EVENT_SOURCE_TYPE_PLATFORM_FIRMWARE 0x00
#define ASF_EVENT_SOURCE_TYPE_OS                0x48
#define ASF_EVENT_SOURCE_TYPE_ASF10             0x68

///
/// ASF Event Severity Codes
/// IPMI/PET related definition
///
#define ASF_EVENT_SEVERITY_CODE_MONITOR         0x01
#define ASF_EVENT_SEVERITY_CODE_INFORMATION     0x02
#define ASF_EVENT_SEVERITY_CODE_OK              0x04
#define ASF_EVENT_SEVERITY_CODE_NONCRITICAL     0x08
#define ASF_EVENT_SEVERITY_CODE_CRITICAL        0x10
#define ASF_EVENT_SEVERITY_CODE_NONRECOVERABLE  0x20

///
/// ASF Sensor Device Codes
/// IPMI/PET related definition
///
#define ASF_SENSOR_DEVICE 0xFF

///
/// ASF Sensor Number Codes
/// IPMI/PET related definition
///
#define ASF_SENSOR_NUMBER 0xFF

///
/// ASF Entity Codes (IPMI Table 43 - Entity ID Codes)
/// IPMI/PET related definition
///
#define ASF_ENTITY_UNSPECIFIED              0x00
#define ASF_ENTITY_OTHER                    0x01
#define ASF_ENTITY_UNKNOWN                  0x02
#define ASF_ENTITY_PROCESSOR                0x03
#define ASF_ENTITY_DISK                     0x04
#define ASF_ENTITY_PERIPHERAL               0x05
#define ASF_ENTITY_SYSTEM_MGMT_MOD          0x06
#define ASF_ENTITY_SYSTEM_BOARD             0x07
#define ASF_ENTITY_POWER_SUPPLY             0x0A
#define ASF_ENTITY_ADDIN_CARD               0x0B
#define ASF_ENTITY_CHASIS_BACK_PANEL_BOARD  0x16
#define ASF_ENTITY_MEMORY                   0x20
#define ASF_ENTITY_SYSTEM_MGMT_SW           0x21
#define ASF_ENTITY_BIOS                     0x22
#define ASF_ENTITY_OS                       0x23
#define ASF_ENTITY_REMOTE_OOB_MGMT          0x26

///
/// ASF Entity Instance Codes
/// IPMI/PET related definition
///
#define ASF_ENTITY_INSTANCE_UNSPECIFIED     0x00

///
/// ASF Event Data Codes for System Firmware Progress Events
/// IPMI/PET related definition
///
#define ASF_FP_EVENT_DATA1          0x40

#define ASF_FP_UNSPECIFIED          0x00
#define ASF_FP_MEMORY_INIT          0x01
#define ASF_FP_HDD_INIT             0x02
#define ASF_FP_AP_INIT              0x03
#define ASF_FP_USER_AUTHENTICATION  0x04
#define ASF_FP_USER_SETUP           0x05
#define ASF_FP_USB_RESOURCE_CONFIG  0x06
#define ASF_FP_PCI_RESOURCE_CONFIG  0x07
#define ASF_FP_OPTION_ROM_INIT      0x08
#define ASF_FP_VIDEO_INIT           0x09
#define ASF_FP_CACHE_INIT           0x0A
#define ASF_FP_SMBUS_INIT           0x0B
#define ASF_FP_KBC_INIT             0x0C
#define ASF_FP_EC_INIT              0x0D
#define ASF_FP_ATTACH_DOCK          0x0E
#define ASF_FP_ENABLE_DOCK          0x0F
#define ASF_FP_EJECT_DOCK           0x10
#define ASF_FP_DISABLE_DOCK         0x11
#define ASF_FP_WAKE_OS              0x12
#define ASF_FP_BOOT_OS              0x13
#define ASF_FP_BOARD_INIT           0x14
#define ASF_FP_RESERVED             0x15
#define ASF_FP_FDC_INIT             0x16
#define ASF_FP_KBD_TEST             0x17
#define ASF_FP_MOUSE_TEST           0x18
#define ASF_FP_BSP_INIT             0x19

///
/// ASF Event Data Codes for System Firmware Error Events
/// IPMI/PET related definition
///
#define ASF_FE_EVENT_DATA1                    0x40

#define ASF_FE_UNSPECIFIED                    0x00
#define ASF_FE_AMTBX_FAILURE                  0x00
#define ASF_FE_NO_MEMORY                      0x01
#define ASF_FE_MEMORY_FAILURE                 0x02
#define ASF_FE_HDD_FAILURE                    0x03
#define ASF_FE_BOARD_FAILURE                  0x04
#define ASF_FE_FDC_FAILURE                    0x05
#define ASF_FE_HDC_FAILURE                    0x06
#define ASF_FE_KBD_FAILURE                    0x07
#define ASF_FE_REMOVABLE_BOOT_MEDIA_NOT_FOUND 0x08
#define ASF_FE_VIDEO_CONTROLLER_FAILURE       0x09
#define ASF_FE_VIDEO_DEVICE_NOT_FOUND         0x0A
#define ASF_FE_ROM_CORRUPTED                  0x0B
#define ASF_FE_CPU_VOLTAGE_FAILURE            0x0C
#define ASF_FE_CPU_MISMATCH_FAILURE           0x0D

///
/// ASF Event Data Codes for Watchdog2 Events
/// IPMI/PET related definition
///
#define ASF_WD_EVENT_DATA1                    0x40

#define ASF_WD_EVENT_DATA2_BIOS_TIMEOUT       0x02
#define ASF_WD_EVENT_DATA2_OS_TIMEOUT         0x04

///
/// ACPI ASF! Definition
///

///
/// This field identifies the type of data present in the record's Variable
/// Data field, as well as an indication as to whether this is the last
/// record in the table:
/// Bit(s) Description
/// 7   Last Record. If this bit is set to 1b, then the record is the
///     last one present in the ASF! table.
/// 6:0 Record Type. Identifies the format of the record's Variable
///     Data field, one of:
///     00h ASF_INFO
///     01h ASF_ALRT
///     02h ASF_RCTL
///     03h ASF_RMCP
///     04h ASF_ADDR
///     05h-7Fh Reserved for future definition by this specification
///
#define ASF_INFO_TYPE                       0x00
#define ASF_ALRT_TYPE                       0x01
#define ASF_RCTL_TYPE                       0x02
#define ASF_RMCP_TYPE                       0x03
#define ASF_ADDR_TYPE                       0x04
#define ASF_LAST_RECORD_TYPE                0x80

///
/// ACPI ASF_RMCP
///
#define ASF_RMCP_BOOT_OPTION_SUCCESS        0x00
#define ASF_RMCP_NO_BOOT_OPTION             0x01
#define ASF_RMCP_BOOT_OPTION_MISMATCH       0x80

///
/// This structure contains ASF! RMCP Remote Control Capabilities
///

///
/// Boot Options Bit Mask Byte1 values
///
#define LOCK_POWER_BUTTON             BIT1
#define LOCK_RESET_BUTTON             BIT2
#define LOCK_KEYBOARD                 BIT5
#define LOCK_SLEEP_BUTTON             BIT6

///
/// Boot Options Bit Mask Byte2 values
///
#define USER_PASSWORD_BYPASS          BIT3
#define FORCE_PROGRESS_EVENTS         BIT4
#define FIRMWARE_VERBOSITY_MASK       (BIT6 | BIT5)
#define FIRMWARE_VERBOSITY_QUIET      BIT5
#define FIRMWARE_VERBOSITY_VERBOSE    BIT6
#define FIRMWARE_VERBOSITY_BLANK      (BIT6 | BIT5)
#define CONFIG_DATA_RESET             BIT7

///
/// Boot Options/System Firmware Capabilities Bit Mask
///
/// Byte1:
///         7: Reserved for future definition by this specification
///         6: Supports Sleep Button Lock
///         5: Supports Lock Keyboard
///       4:3: Reserved for future definition by this specification
///         2: Supports Reset Button Lock
///         1: Supports Power Button Lock
///         0: Supports Firmware Verbosity/Screen Blank
/// Byte2:
///         7: Supports Configuration Data Reset
///         6: Supports Firmware Verbosity/Quiet
///         5: Supports Firmware Verbosity/Verbose
///         4: Supports Forced Progress Events
///         3: Supports User Password Bypass
///       2:0: Reserved for future definition by this specification
/// Byte3:
///       7:0: Reserved for future definition by this specification
/// Byte4:
///       7:0: Reserved for future definition by this specification
typedef struct {
  UINT8   BootOptionByte1;
  UINT8   BootOptionByte2;
  UINT8   BootOptionByte3;
  UINT8   BootOptionByte4;
} BOOT_OPTION_CAPS_STRUC;

///
/// Special Command Definitions
///
#define NOP               0x00
#define FORCE_PXE         0x01
#define FORCE_HARDDRIVE   0x02
#define FORCE_SAFEMODE    0x03
#define FORCE_DIAGNOSTICS 0x04
#define FORCE_CDDVD       0x05

///
/// Special Command Bit Mask Byte2 values
///
#define SUPPORT_FORCE_PXE             BIT0
#define SUPPORT_FORCE_HARDDRIVE       BIT1
#define SUPPORT_FORCE_SAFEMODE        BIT2
#define SUPPORT_FORCE_DIAGNOSTICS     BIT3
#define SUPPORT_FORCE_CDDVD           BIT4

///
/// Special Commands Bit Mask
///
/// Byte1:
///       7:0: Reserved to identify support for ASF-RMCP Special Commands defined by a future version of this specification
/// Byte2:
///       7:5: Reserved to identify support for ASF-RMCP Special Commands defined by a future version of this specification
///         4: Supports Force CD/DVD Boot command
///         3: Supports Force Diagnostic Boot command
///         2: Supports Force Hard-drive Safe-mode Boot command
///         1: Supports Force Hard-drive Boot command
///         0: Supports Force PXE Boot command
typedef struct {
  UINT8   SpecialCmdByte1;
  UINT8   SpecialCmdByte2;
} SPECIAL_COMMAND_CAPS_STRUC;

///
/// System Capabilities Bit Mask values
///
#define SUPPORT_POWER_CYCLE_RESET        BIT0 ///< Supports Power Cycle Reset only on the secure port
#define SUPPORT_POWER_DOWN               BIT1 ///< Supports Power-Down only on the secure port
#define SUPPORT_POWER_UP                 BIT2 ///< Supports Power-Up only on the secure port
#define SUPPORT_RESET                    BIT3 ///< Supports Reset only on the secure port
#define SUPPORT_POWER_CYCLE_RESET_COMBO  BIT4 ///< Supports Power Cycle Reset on either the compatibility or secure port
#define SUPPORT_POWER_DOWN_COMBO         BIT5 ///< Supports Power-Down on either the compatibility or secure port
#define SUPPORT_POWER_UP_COMBO           BIT6 ///< Supports Power-Up on either the compatibility or secure port
#define SUPPORT_RESET_COMBO              BIT7 ///< Supports Reset on either the compatibility or secure port

///
/// System Capabilities Bit Mask
///
/// Byte1:
///         7: Supports Reset on either the compatibility or secure port
///         6: Supports Power-Up on either the compatibility or secure port
///         5: Supports Power-Down on either the compatibility or secure port
///         4: Supports Power Cycle Reset on either the compatibility or secure port
///         3: Supports Reset only on the secure port
///         2: Supports Power-Up only on the secure port
///         1: Supports Power-Down only on the secure port
///         0: Supports Power Cycle Reset only on the secure port
typedef struct {
  UINT8   SystemByte1;
} SYSTEM_CAPS_STRUC;

typedef struct {
  BOOT_OPTION_CAPS_STRUC        BootOptionCaps;
  SPECIAL_COMMAND_CAPS_STRUC    SpecialCmdCaps;
  SYSTEM_CAPS_STRUC             SystemCaps;
} ASF_RMCP_REMOTE_CTRL_CAPS;

#pragma pack ()

#endif
