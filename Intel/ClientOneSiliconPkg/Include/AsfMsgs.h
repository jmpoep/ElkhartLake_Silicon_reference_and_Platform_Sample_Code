/** @file
  AMT/ASF Messages

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#ifndef _ASF_MSGS_H_
#define _ASF_MSGS_H_

#include <Pi/PiStatusCode.h>
#include <IndustryStandardAsf.h>
#include <IntelAsfExtensions.h>

#pragma pack(1)


//
// Always define the whole ASF message structure so you can use the macro for ByteCount calculation
//
#define ASF_MESSAGE_BYTE_COUNT_MAP(a) (sizeof(a)-2)

///
/// Abstract ASF message header. This header is part of HECI message sent from BIOS to AMT/ASF ME Client
///
typedef union {
  UINT32  Data;
  struct {
    UINT32  Command       : 8;          ///< ASF Message Command.
    UINT32  ByteCount     : 8;          ///< ASF Message Bytes Count Beyond This Byte.
    UINT32  SubCommand    : 8;          ///< ASF Message Sub-command.
    UINT32  VersionNumber : 8;          ///< ASF Specification Version.
  } Fields;
} ASF_MESSAGE_HEADER;

//
// Management Control Command Definitions
//

///
/// Start Watchdog Timer Type
///
#define ASF_START_BIOS_WDT  0
#define ASF_START_OS_WDT    1

///
/// Start Watchdog Timer Message Structure.
/// This structure is only used for Starting Watchdog Timer Message.
/// Elements' description is based on Start Watchdog Timer.
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
  UINT8                TimeoutLow;      ///< Low byte of watchdog timeout value in seconds.
  UINT8                TimeoutHigh;     ///< High byte of watchdog timeout value in seconds.
  UINT8                EventSensorType; ///< Default value is 0x23 to indicate it is for Watchdog 2.
  UINT8                EventType;       ///< Default value is 0x6F to indicate it is Sensor specific.
  UINT8                EventOffset;     ///< Default value is 0x00 to indicate it is for Timer expired.
  /**
    Class of device or type of software that originated the event.
      0x00: Platform firmware
      0x48: OS vendor
  **/
  UINT8                EventSourceType;
  UINT8                EventSeverity;   ///< Default value is 0x10 to indicate it is Critical.
  UINT8                SensorDevice;    ///< Default value is 0xFF to indicate it is Unspecified.
  UINT8                SensorNumber;    ///< Default value is 0xFF to indicate it is Unspecified.
  UINT8                Entity;          ///< Default value is 0x00 to indicate it is Unspecified.
  UINT8                EntityInstance;  ///< Default value is 0x00 to indicate it is Unspecified.
  /**
    Additional parametric data byte.
      BYTE 0: 0x40
      BYTE 1: 0x02, BIOS POST WDT Timeout
              0x04, OS WDT Timeout
      BYTE 2-4: Not defined.
  **/
  UINT8                EventData[5];
} ASF_START_WDT;

///
/// Stop Watchdog Timer Message Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
} ASF_STOP_WDT;


//
// ASF Configuration Command Definitions
//

///
/// Clear Boot Options Message Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
} CLEAR_BOOT_OPTIONS;

///
/// Return Boot Options
/// Elements' description is based on Get Boot Options and No Boot Options Message.
///
typedef struct {
  /**
    ASF Message Sub-command.
      0x16: Return boot option
      0x17: No boot option
  **/
  UINT8   SubCommand;
  UINT8   Version;                      ///< Default value is 0x10 to indicate ASF Specification Version.
  /**
    IANA-assigned Enterprise Number.
      0x000011BE: IANA Enterprise Number for ASF
      0x00000157: IANA Enterprise Number for Intel
  **/
  UINT32  IanaId;
  /**
    Defines commands to be processed by the managed client on the boot initiated by the ASF-RMCP message.
      0x00: NOP
      0x01: Force PXE Boot
      0x02: Force Hard-drive Boot
      0x03: Force Hard-drive Safe Mode Boot
      0x04: Force Diagnostic Boot
      0x05: Force CD/DVD Boot
      0x06-0xBF: Reserved
      0xC0-0xFF: OEM special commands
      0xC1: Intel special command
  **/
  UINT8   SpecialCommand;
  UINT8   SpecialCommandParamHighByte;  ///< Defines a command parameter to augment the Special Command High Byte.
  UINT8   SpecialCommandParamLowByte;   ///< Defines a command parameter to augment the Special Command Low Byte.
  UINT8   BootOptionsMaskByte1;         ///< Defines a standard set of firmware operations.
  UINT8   BootOptionsMaskByte2;         ///< Defines a standard set of firmware operations.
  UINT8   OemParameterByte1;            ///< Defines parameters that further augment the Special Command definition.
  UINT8   OemParameterByte2;            ///< Defines parameters that further augment the Special Command definition.
} ASF_BOOT_OPTIONS;

///
/// Get Boot Options Response Structure
///
typedef struct {
  UINT8                 Command;        ///< ASF Message Command.
  UINT8                 ByteCount;      ///< ASF Message Bytes Count Beyond This Byte.
  ASF_BOOT_OPTIONS      AsfBootOptions; ///< ASF Return Boot Options.
} GET_BOOT_OPTIONS_RESPONSE;

///
/// Get Boot Options Request Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
} GET_BOOT_OPTIONS;

///
/// Get Boot Options Union Buffer
///
typedef union {
  GET_BOOT_OPTIONS          Request;
  GET_BOOT_OPTIONS_RESPONSE Response;
} GET_BOOT_OPTIONS_BUFFER;

//
// Get Remote Secure Erase Password
//

#define RSE_PASSWORD_MAX_LENGTH 32

///
/// Get RSE Password Response Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;                          ///< ASF Message Header.
  UINT16               PasswordLength;                     ///< Password length in bytes.
  CHAR8                Password[RSE_PASSWORD_MAX_LENGTH];  ///< RSE Password.
} GET_RSE_PASSWORD_RESPONSE;

///
/// Get RSE Password Request Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
} GET_RSE_PASSWORD;

///
/// Report BIOS Status
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;       ///< ASF Message Header.
  /**
    Current BIOS Status.
      0: Success
      0xFFFF: Failed
  **/
  UINT16               BiosStatus;
  /**
    The Reason Causes Current BIOS Status.
      0: BiosStatus is Success/InProgress
      1: General Drive Failure
      2: Drive Password/Authentication Failure
      3: Feature is not supported
  **/
  UINT16               StatusCause;
} REPORT_BIOS_STATUS;


//
// Messaging Command Definitions
//

///
/// ASF Message
///
typedef struct {
  UINT8 SubCommand;                     ///< ASF Message Sub-command.
  UINT8 Version;                        ///< ASF Specification Version.
  UINT8 EventSensorType;                ///< The Event Sensor Type field indicates what types of events the sensor is monitoring.
  UINT8 EventType;                      ///< Code indicating what type of transition/state change triggered the trap.
  UINT8 EventOffset;                    ///< Indicates which particular event occurred for a given Event Type.
  UINT8 EventSourceType;                ///< Class of device or type of software that originated the event.
  UINT8 EventSeverity;                  ///< Severity of the event.
  UINT8 SensorDevice;                   ///< Identifies the instance of the device that holds the sensor that generated the event.
  UINT8 SensorNumber;                   ///< Identify a given instance of a sensor relative to the Sensor Device.
  UINT8 Entity;                         ///< Indicates the platform entity the event is associated with.
  UINT8 EntityInstance;                 ///< Indicates which instance of the Entity the event is for.
  UINT8 EventData1;                     ///< Additional parametric data 1.
  UINT8 EventData2;                     ///< Additional parametric data 2.
} ASF_MESSAGE;

///
/// ASF Push Progress Code
///
typedef struct {
  UINT8           Command;              ///< ASF Message Command.
  UINT8           ByteCount;            ///< ASF Message Bytes Count Beyond This Byte.
  ASF_MESSAGE     AsfMessage;           ///< ASF Message Instance.
  UINT8           EventData[3];         ///< Additional parametric data.
} HECI_ASF_PUSH_PROGRESS_CODE;

///
/// ASF Framework Message
///
typedef struct {
  ASF_FRAMEWORK_MESSAGE_TYPE      MessageType;      ///< ASF Message Type.
  ASF_MESSAGE                     Message;          ///< ASF Message Instance.
} ASF_FRAMEWORK_MESSAGE;

///
/// Data Hub of ASF Progress Status
///
typedef struct {
  ASF_FRAMEWORK_MESSAGE_TYPE      MessageType;      ///< ASF Message Type.
  EFI_STATUS_CODE_VALUE           StatusCodeValue;  ///< Platform Progress Status Code.
} ASF_DATA_HUB_MAP;

///
/// Platform Event Trap (PET) Alert To Indicate Which Event Causes The Alert.
/// This structure is used for sending Remote Secure Erase / Boot Audit Entry PET Message.
/// Elements' description is based on Remote Secure Erase / Boot Audit Entry.
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;         ///< ASF Message Header.
  UINT8                EventSensorType;   ///< Default value is 0x0F to indicate it is Firmware progress/error type.
  UINT8                EventType;         ///< Default value is 0x6F to indicate it is Sensor specific.
  /**
    Indicates which particular event occurred for a given Event Type.
    For Remote Secure Erase:
      0x03: OEM specific firmware error
      0x05: OEM specific firmware progress
    For Boot Audit Entry:
      0x00: System Firmware Error
      0x01: System Firmware Hang
      0x02: System Firmware In Progress
  **/
  UINT8                EventOffset;
  UINT8                EventSourceType;   ///< Default value is 0x68 to indicate it is ASF 1.0.
  /**
    Severity of the event.
      0x01: Monitor
      0x02: Information
      0x04: Ok
      0x08: Non-critical
      0x10: Critical
      0x20: Non-Recoverable
  **/
  UINT8                EventSeverity;
  UINT8                SensorDevice;      ///< Default value is 0xFF to indicate it is Unspecified.
  UINT8                Sensornumber;      ///< Default value is 0xFF to indicate it is Unspecified.
  /**
    Indicates the platform device or subsystem associated with the event.
      0x00: Unspecified
      0x01: Other
      0x02: Unknown
      0x03: Processor
      0x04: Disk
      0x05: Peripheral
      0x07: System Board
      0x0A: Power Supply
      0x0B: Add-in Card
      0x20: Memory
      0x22: BIOS
      0x23: OS
  **/
  UINT8                Entity;
  /**
    Identifies which unique device is associated with the event when a system includes multiple device instances.
    For Remote Secure Erase:
        0xFF: Unspecified
    For Boot Audit Entry:
        0x00: Unspecified
  **/
  UINT8                EntityInstance;
  /**
    The Event Type determines the Event Data.
    For Remote Secure Erase:
        0xAA: Indicate EventData 2-5 set by OEM specification.
    For Boot Audit Entry:
        0x40: EventData 2 conforms ASF spec.
        0xAA: Indicate EventData 2-5 set by OEM specification.
  **/
  UINT8                EventData1;
  /**
    Additional Event Data 2.
    For Remote Secure Erase:
        0x20: Indicate it is for Remote Secure Erase.
    For Boot Audit Entry:
        0x13: Performing system boot.
  **/
  UINT8                EventData2;
  /**
    Additional Event Data 3.
    For Remote Secure Erase:
      Success Case: 0x00 - Secure erase success
      Failure Case: 0x01 - General failure
                    0x02 - Drive authentication failure
                    0x03 - Feature is not supported
                    0x04 - 0XFF - Reserved
    For Boot Audit Entry (Boot Device Not Changed):
      00: Not used.
    For Boot Audit Entry (Boot Device Changed):
      N/A: Most recent BAE queue entry.
  **/
  UINT8                EventData3;
  /**
    Additional Event Data 4.
    For Remote Secure Erase:
      N/A: Not used.
    For Boot Audit Entry (Boot Device Not Changed):
      N/A: Not used.
    For Boot Audit Entry (Boot Device Changed):
      N/A: Next most recent BAE queue entry.
  **/
  UINT8                EventData4;
  /**
    Additional Event Data 5.
    For Remote Secure Erase:
      N/A: Not used.
    For Boot Audit Entry (Boot Device Not Changed):
      N/A: Not used.
    For Boot Audit Entry (Boot Device Changed):
      N/A: Oldest BAE queue entry.
  **/
  UINT8                EventData5;
} PET_ALERT;


//
// KVM Command Definitions
//

///
/// AMT Query KVM timer related definition
///
#define KVM_STALL_1_SECOND  1000000   ///< Stall 1 second
#define KVM_MAX_WAIT_TIME   (60 * 8)  ///< 8 Mins

///
/// Query KVM Response Type
///
typedef enum {
  KvmSessionEstablished  = 1,
  KvmSessionCancelled
} RESPONSE_CODE;

///
/// Query KVM Response Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;         ///< ASF Message Header.
  /**
    Response Code of KVM Session Status.
      0x01: the KVM session established
      0x02: the KVM session cancelled
  **/
  UINT32               ResponseCode;
} AMT_QUERY_KVM_RESPONSE;

///
/// Query KVM Type
///
typedef enum {
  QueryRequest            = 0,
  CancelRequest
} QUERY_TYPE;

///
/// Query KVM Request Structure
///
typedef struct {
  ASF_MESSAGE_HEADER   AsfHeader;         ///< ASF Message Header.
  /**
    KVM Session Query Type.
      0x00: Query the KVM session request
      0x01: Cancel the KVM session request
  **/
  UINT32               QueryType;
} AMT_QUERY_KVM;

///
/// Query KVM Union Buffer
///
typedef union {
  AMT_QUERY_KVM          Request;
  AMT_QUERY_KVM_RESPONSE Response;
} AMT_QUERY_KVM_BUFFER;

#pragma pack()

#endif // _ASF_MSGS_H
