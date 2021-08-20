/** @file
  Include file for Intel Extended ASF definition

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _INTEL_EXTENDED_ASF_H_
#define _INTEL_EXTENDED_ASF_H_

///
/// Intel extended ASF Messages Command
///
#define ASF_MESSAGE_COMMAND_KVM                       0x08

///
/// Intel extended ASF Messages Sub-Command for Command ASF_CONFIGURATION (0x03)
///
#define ASF_MESSAGE_SUBCOMMAND_GET_RSE_PASSWORD       0x18
#define ASF_MESSAGE_SUBCOMMAND_REPORT_BIOS_STATUS     0x19

///
/// Intel extended ASF Messages Sub-Command for Command KVM (0x08)
///
#define ASF_MESSAGE_SUBCOMMAND_KVM_QUERY              0x01

///
/// Intel extended ASF Entity Codes
///
#define ASF_ENTITY_INTEL_AMT                          0x26

///
/// Intel extended ASF Event Data Codes for System Firmware Progress Events
///
#define ASF_FP_AMTBX_INIT                             0x0D

///
/// Intel extended ASF Event Data Codes for System Firmware Error Events
///
#define ASF_FE_AMTBX_FAILURE                          0x00

///
/// Intel extended ASF Event Data Codes for RSE Fw Progress/Error Events
///
#define ASF_RSE_EVENT_DATA0_EVENT_DATA_SET_BY_OEM     0xAA

#define ASF_RSE_EVENT_DATA1_REMOTE_SECURE_ERASE       0x20

#define ASF_RSE_EVENT_DATA2_SECURE_ERASE_SUCCESS      0x00
#define ASF_RSE_EVENT_DATA2_GENERAL_FAILURE           0x01
#define ASF_RSE_EVENT_DATA2_DRIVE_AUTH_FAILURE        0x02
#define ASF_RSE_EVENT_DATA2_UNSUPPORTED               0x03

///
/// Intel extended ASF Report BIOS Status Additional Data
///
#define ASF_RBS_BIOS_STATUS_SUCCESS                  0x0000
#define ASF_RBS_BIOS_STATUS_IN_PROGRESS              0x0001
#define ASF_RBS_BIOS_STATUS_FAILED                   0xFFFF
#define ASF_RBS_STATUS_CAUSE_SUCCESS_INPROGRESS      0x0000
#define ASF_RBS_STATUS_CAUSE_GENERAL_FAILURE         0x0001
#define ASF_RBS_STATUS_CAUSE_AUTHENTICATION_FAILURE  0x0002
#define ASF_RBS_STATUS_CAUSE_UNSUPPORTED             0x0003

//
// AMT BX Software Class DXE Subclass Progress Code definitions.
//
#define SW_DXE_AMTBX_OPROM_DONE               (EFI_OEM_SPECIFIC | 0x00000000)
#define SW_DXE_AMTBX_OPROM_NOT_STARTED        (EFI_OEM_SPECIFIC | 0x00000001)
#define SW_DXE_AMTBX_SLEEP_S4_NOT_TAKEN       (EFI_OEM_SPECIFIC | 0x00000002)
#define SW_DXE_AMTBX_SLEEP_S5_NOT_TAKEN       (EFI_OEM_SPECIFIC | 0x00000003)
#define SW_DXE_AMTBX_SLEEP_UNSPECD_NOT_TAKEN  (EFI_OEM_SPECIFIC | 0x00000004)
#define SW_DXE_AMTBX_ERROR_ACTION_INTF        (EFI_OEM_SPECIFIC | 0x00000005)
#define SW_DXE_AMTBX_ERROR_ACTION_INV         (EFI_OEM_SPECIFIC | 0x00000006)
#define SW_DXE_AMTBX_ERROR_ACTION_SETUP       (EFI_OEM_SPECIFIC | 0x00000007)
#define SW_DXE_AMTBX_ERROR_ACTION_FAIL        (EFI_OEM_SPECIFIC | 0x00000008)
#define SW_DXE_AMTBX_ERROR_ACTION_UNSPECD     (EFI_OEM_SPECIFIC | 0x00000009)
#define SW_DXE_AMTBX_OTHER_UNSPECD            (EFI_OEM_SPECIFIC | 0x00000009)

typedef enum {
  AsfMessageBiosPresent,
  AsfMessageMemInit,
  AsfMessageMemInitDone,
  AsfMessageHddInit,
  AsfMessageApInit,
  AsfMessageUserAuthentication,
  AsfMessageUserInitSetup,
  AsfMessageUsbResourceConfig,
  AsfMessagePciResourceConfig,
  AsfMessageOptionRomInit,
  AsfMessageVideoInit,
  AsfMessageCacheInit,
  AsfMessageSmbusInit,
  AsfMessageKbcInit,
  AsfMessageEmControllerInit,
  AsfMessageDockAttached,
  AsfMessageEnableDock,
  AsfMessageDockEject,
  AsfMessageDisableDock,
  AsfMessageOSWakeVector,
  AsfMessageMotherBoardInit,
  AsfMessageFdcInit,
  AsfMessageKeyboardTest,
  AsfMessageMouseTest,
  AsfMessageBspInit,
  AsfMessageAmtBxDone,
  AsfMessageAmtBxNotStarted,
  AsfMessageAmtBxSleepS4ReportedNotTaken,
  AsfMessageAmtBxSleepS5ReportedNotTaken,
  AsfMessageAmtBxSleepUnspecifiedReportedNotTaken,
  AsfMessageAmtBxErrActionIntF,
  AsfMessageAmtBxErrActionInv,
  AsfMessageAmtBxErrActionSetup,
  AsfMessageAmtBxErrActionFailure,
  AsfMessageAmtBxErrActionUnspecified,
  AsfMessageAmtBxOtherUnspecified,
  AsfMessageNoMemory,
  AsfMessageMemoryFailure,
  AsfMessageHddFailure,
  AsfMessageBoardFailure,
  AsfMessageFdcFailure,
  AsfMessageHdcFailure,
  AsfMessageKbdFailure,
  AsfMessageNoFdd,
  AsfMessageVideoControllerFailure,
  AsfMessageNoVideo,
  AsfMessageFirmwareCorruption,
  AsfMessageCpuVidMismatch,
  AsfMessageCpuSpeedMatchingFailure,
  AsfMessageUserAuthenticationInvalid,
  AsfMessageHddAuthenticationInvalid,
  AsfMessageNoBootMedia,
  AsfMessageTemperatureGenericCritical,
  AsfMessageTemperatureGenericWarning,
  AsfMessageTemperatureOverCritical,
  AsfMessageTemperatureOverWarning,
  AsfMessageTemperatureUnderCritical,
  AsfMessageTemperatureUnderWarning,
  AsfMessageVoltageGenericCritical,
  AsfMessageVoltageOverCritical,
  AsfMessageVoltageUnderCritical,
  AsfMessageFanGenericCritical,
  AsfMessageFanPredictiveFailure,
  AsfMessageFanLowSpeedCritical,
  AsfMessageFanLowSpeedWarning,
  AsfMessageBatteryLowWarning,
  AsfMessageBatteryLowCritical,
  AsfMessageBatteryPresenceDetected,
  AsfMessagePowerFailure,
  AsfMessageChassisIntrusion,
  AsfMessageTermination = 0xFFFF
} ASF_FRAMEWORK_MESSAGE_TYPE;

///
/// Intel extended StatusCode extension for ASF
///


///
/// Intel extended Computing Unit Host Processor Subclass Error Code definitions.
///
#define CU_HP_EC_VID_MISMATCH                   (EFI_SUBCLASS_SPECIFIC | 0x0000000E)
#define CU_HP_EC_SPEED_MATCHING_FAILURE         (EFI_SUBCLASS_SPECIFIC | 0x0000000F)

///
/// Intel extended Peripheral Subclass definitions.
///
#define PERIPHERAL_EMBEDDED_CONTROLLER          (EFI_PERIPHERAL | 0x000D0000)
#define PERIPHERAL_DOCK                         (EFI_PERIPHERAL | 0x000E0000)

#define PERIPHERAL_BATTERY                      (EFI_PERIPHERAL | 0x000F0000)
#define P_BATTERY_PC_LOW_WARNING                (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_BATTERY_EC_LOW_CRITICAL               (EFI_SUBCLASS_SPECIFIC | 0x00000000)

#define PERIPHERAL_FAN                          (EFI_PERIPHERAL | 0x00100000)
#define P_FAN_EC_GENERIC_CRITICAL               (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_FAN_EC_PREDICTIVE_FAILURE             (EFI_SUBCLASS_SPECIFIC | 0x00000001)
#define P_FAN_EC_LOW_SPEED_CRITICAL             (EFI_SUBCLASS_SPECIFIC | 0x00000002)
#define P_FAN_PC_LOW_SPEED_WARNING              (EFI_SUBCLASS_SPECIFIC | 0x00000002)

#define PERIPHERAL_TEMPERATURE                  (EFI_PERIPHERAL | 0x00110000)
#define P_TEMERATURE_EC_GENERIC_CRITICAL        (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_TEMERATURE_PC_GENERIC_WARNING         (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_TEMERATURE_EC_OVER_CRITICAL           (EFI_SUBCLASS_SPECIFIC | 0x00000001)
#define P_TEMERATURE_PC_OVER_WARNING            (EFI_SUBCLASS_SPECIFIC | 0x00000001)
#define P_TEMERATURE_EC_UNDER_CRITICAL          (EFI_SUBCLASS_SPECIFIC | 0x00000002)
#define P_TEMERATURE_PC_UNDER_WARNING           (EFI_SUBCLASS_SPECIFIC | 0x00000002)

#define PERIPHERAL_VOLTAGE                      (EFI_PERIPHERAL | 0x00120000)
#define P_VOLTAGE_EC_GENERIC_CRITICAL           (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_VOLTAGE_EC_OVER_CRITICAL              (EFI_SUBCLASS_SPECIFIC | 0x00000001)
#define P_VOLTAGE_EC_UNDER_CRITICAL             (EFI_SUBCLASS_SPECIFIC | 0x00000002)

#define PERIPHERAL_POWER_SUPPLY                 (EFI_PERIPHERAL | 0x00130000)
#define P_POWER_SUPPLY_EC_FAILURE               (EFI_SUBCLASS_SPECIFIC | 0x00000000)
#define P_POWER_SUPPLY_EC_PREDICTIVE_FAILURE    (EFI_SUBCLASS_SPECIFIC | 0x00000001)

///
/// Intel extended Computing Unit Chipset Subclass Progress Code definitions.
///
#define CU_CHIPSET_PC_INTRUDER_DETECT           (EFI_SUBCLASS_SPECIFIC | 0x00000000)

///
/// Intel extended Software Class DXE Boot Service Driver Subclass Error Code definitions.
///
#define SW_DXE_BS_EC_NO_BOOT_MEDIA              (EFI_SUBCLASS_SPECIFIC | 0x00000001)
#define SW_DXE_BS_EC_AUTHENTICATE_USER_INVALID  (EFI_SUBCLASS_SPECIFIC | 0x00000002)
#define SW_DXE_BS_EC_AUTHENTICATE_HDD_INVALID   (EFI_SUBCLASS_SPECIFIC | 0x00000003)

#endif
