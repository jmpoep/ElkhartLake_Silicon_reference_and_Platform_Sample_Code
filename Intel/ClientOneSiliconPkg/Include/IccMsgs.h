/** @file
  ICC Messages

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#ifndef _ICC_MSGS_H
#define _ICC_MSGS_H

#pragma pack(1)

//
// macro for determining length of ICC message buffer
//
#define ICC_MESSAGE_BUFFER_LENGTH(a) (a-sizeof(ICC_HEADER))

//
// definitions for ICC MEI Messages
//
#define ICC_API_VERSION    0x00050000

typedef enum {
  ICC_STATUS_SUCCESS                              = 0x0,
  ICC_STATUS_FAILURE                              = 0x1,
  ICC_STATUS_INCORRECT_API_VERSION                = 0x2,
  ICC_STATUS_INVALID_FUNCTION                     = 0x3,
  ICC_STATUS_INVALID_BUFFER_LENGTH                = 0x4,
  ICC_STATUS_INVALID_PARAMS                       = 0x5,
  ICC_STATUS_FLASH_WEAR_OUT_VIOLATION             = 0x6,
  ICC_STATUS_FLASH_CORRUPTION                     = 0x7,
  ICC_STATUS_PROFILE_NOT_SELECTABLE_BY_BIOS       = 0x8,
  ICC_STATUS_TOO_LARGE_PROFILE_INDEX              = 0x9,
  ICC_STATUS_NO_SUCH_PROFILE_IN_FLASH             = 0xA,
  ICC_STATUS_CMD_NOT_SUPPORTED_AFTER_END_OF_POST  = 0xB,
  ICC_STATUS_NO_SUCH_RECORD                       = 0xC,
  ICC_STATUS_FILE_NOT_FOUND                       = 0xD,
  ICC_STATUS_INVALID_RECORD_FORMAT                = 0xE,
  ICC_STATUS_TOO_LARGE_UOB_RECORD                 = 0xF,
  ICC_STATUS_CLOCK_NOT_CONFIGURABLE               = 0x10,
  ICC_STATUS_REGISTER_IS_LOCKED                   = 0x11,
  ICC_STATUS_NO_VALID_PRE_UOB                     = 0x12,
  ICC_STATUS_NO_VALID_PERM_UOB                    = 0x13,
  ICC_STATUS_NO_DATA_FOR_THIS_CLOCK               = 0x14,
  ICC_STATUS_PROFILE_INDEX_IS_CURRENT             = 0x15,
  ICC_STATUS_NO_BCLK_ADJUSTMENT_FOUND             = 0x16,
  ICC_STATUS_WARM_RESET_RAMP_NOT_SUPPORTED        = 0x17,
  ICC_STATUS_UOB_RECORD_IS_ALREADY_INVALID        = 0x18,
  ICC_STATUS_NO_PROFILES_EXIST                    = 0x19,
  ICC_STATUS_AUTH_FAILURE                         = 0x1A,
  ICC_STATUS_ERROR_READING_FILE                   = 0x1B,
  ICC_STATUS_RANGE_VIOLATION_FREQ_TOO_HIGH        = 0x1C,
  ICC_STATUS_HW_VIOLATION_FREQ_TOO_HIGH           = 0x1D,
  ICC_STATUS_PENDING_REVERT_TO_DEFAULT            = 0x1E,
  ICC_STATUS_PENDING_SET_PROFILE                  = 0x1F,
  ICC_STATUS_UNVALID_PROFILE                      = 0x20,
  ICC_STATUS_UNVALID_OEM_DATA                     = 0x21,
  ICC_STATUS_ERROR_READING_DYNAMIC_RECORD         = 0x22,
  ICC_STATUS_RESERVED35                           = 0x23,
  ICC_STATUS_RANGE_VIOLATION_FREQ_TOO_LOW         = 0x24,
  ICC_STATUS_HW_VIOLATION_FREQ_TOO_LOW            = 0x25,
  ICC_STATUS_GET_REGISTER_NO_SUCH_REG             = 0x26,
  ICC_STATUS_RESERVED39                           = 0x27,
  ICC_STATUS_RESERVED40                           = 0x28,
  ICC_STATUS_RESERVED41                           = 0x29,
  ICC_STATUS_RESERVED42                           = 0x2A,
  ICC_STATUS_RESERVED43                           = 0x2B,
  ICC_STATUS_SSC_MODE_CHANGE_NOT_SUPPORTED        = 0x2C,
  ICC_STATUS_RANGE_VIOLATION_SSC_TOO_HIGH         = 0x2D,
  ICC_STATUS_RESERVED46                           = 0x2E,
  ICC_STATUS_RESERVED47                           = 0x2F,
  ICC_STATUS_RESERVED48                           = 0x30,
  ICC_STATUS_RESERVED49                           = 0x31,
  ICC_STATUS_SURVIVABILITY_SYNC_DISABLED          = 0x32,
  ICC_STATUS_WARM_RESET_FREQ_TOO_LOW              = 0x33,
  ICC_STATUS_NO_SUCH_TARGET_ID                    = 0x34,
  ICC_STATUS_NO_SUCH_REGISTER                     = 0x35,
  ICC_STATUS_INVALIDATE_SUCCESSFUL                = 0x36,
  ICC_STATUS_BUFFER_TOO_SMALL                     = 0x37,
  ICC_STATUS_VALID_UOB_ALREADY_PRESENT            = 0x38,
  ICC_STATUS_WAITING_FOR_POWER_CYCLE              = 0x39,
  ICC_STATUS_SURVIVABILITY_TABLE_ACCESS_VIOLATION = 0x3A,
  ICC_STATUS_SURVIVABILITY_TABLE_TOO_LARGE        = 0x3B,
  ICC_STATUS_NO_SUCH_EID                          = 0x3C,
  ICC_STATUS_SUCCESS_TRANSLATE_ONLY               = 0x3D,
  ICC_STATUS_CMD_NOT_SUPPORTED_BEFORE_DID         = 0x40,
  ICC_STATUS_FIA_MUX_CONFIG_SKU_MISMATCH          = 0x41,
  ICC_STATUS_FIA_MUX_NO_CONFIG_FOUND              = 0x42,
  ICC_STATUS_MAX_BUNDLES_PER_RECORD_REACHED       = 0x500,
  ICC_STATUS_PLL_UNSUPPORTED                      = 0x501,
  ICC_STATUS_DATA_ITEM_UNSUPPORTED                = 0x502,
  ICC_STATUS_OEM_PROFILE_CRDR_VIOLATION           = 0x503,
  ICC_STATUS_UNSPECIFIED_ERROR                    = 0xFFFF
} ICC_CMD_STATUS;

typedef enum {
  ///
  /// Commands 0-15 except 10 not used.
  ///
  ICC_READ_FROM_MPHY_CMD                    = 0xA,
  ICC_GET_PROFILE_CMD                       = 0x10,
  ICC_SET_PROFILE_CMD                       = 0x11,
  ICC_GET_REGISTERS_LOCK_CMD                = 0x12,
  ICC_SET_REGISTERS_LOCK_CMD                = 0x13,
  ICC_GET_CLOCK_CAPABILITIES_CMD            = 0x14,
  ICC_GET_CLOCK_RANGE_DEF_REC_CMD           = 0x15,
  ICC_GET_RECORD_CMD                        = 0x16,
  ICC_SET_RECORD_CMD                        = 0x17,
  ICC_GET_MPHY_SETTINGS_CMD                 = 0x18,
  ICC_SET_MPHY_SETTINGS_CMD                 = 0x19,
  ICC_GET_CLOCK_SETTINGS_CMD                = 0x1A,
  ICC_SET_CLOCK_SETTINGS_CMD                = 0x1B,
} ICC_COMMAND_ID;

typedef struct {
  UINT32              ApiVersion;
  ICC_COMMAND_ID      IccCommand;
  ICC_CMD_STATUS      IccResponse;
  UINT32              BufferLength;
  UINT32              Reserved;
} ICC_HEADER;

//
// Defines the HECI request buffer format for the ICC_READ_FROM_MPHY_CMD.
//
typedef struct {
  ICC_HEADER  Header;         ///< Standard ICC HECI Header
  UINT32      Reserved1;      ///< Reserved for future use
  UINT32      Offset;         ///< Offset in the mPhy file to start reading from
  UINT32      Reserved2;      ///< Reserved for future use
  UINT32      NumOfBytes;     ///< How many bytes to read. For the entire file specifiy the mPhy max size
} ICC_READ_FROM_MPHY_REQ;

//
// Defines the HECI request buffer format for reponse to ICC_READ_FROM_MPHY_CMD.
//
typedef struct {
  ICC_HEADER  Header;               ///< Standard ICC HECI Header
  UINT32      Reserved1;            ///< Reserved for future use
  UINT32      FileSize;             ///< mPhy file size. This will be filled regardless of how many bytes the user asked to read (e.g. zero)
  UINT32      Reserved2;            ///< Reserved for future use
  UINT32      ReadSize;             ///< How many bytes were actually read, having less than requested is NOT an error
  UINT32      Reserved3;            ///< Reserved for future use
  UINT8       Payload[];            ///< The binary content requested (or at least as many bytes as we could read)
} ICC_READ_FROM_MPHY_ACK;

typedef union {
  ICC_READ_FROM_MPHY_REQ Request;
  ICC_READ_FROM_MPHY_ACK Response;
} ICC_READ_FROM_MPHY_BUFFER;

///
/// Get/Set ICC Profile
///
#define MAX_NUM_ICC_PROFILES  16

typedef struct {
  ICC_HEADER  Header;
} ICC_GET_PROFILE_MESSAGE;

typedef struct {
  UINT8       IccProfileName[24];
  UINT8       IccProfileBase[24];
} ICC_PROFILE_DESC;

typedef struct {
  ICC_HEADER    Header;
  UINT8         IccNumOfProfiles;
  union {
    UINT8 Data;
    struct {
      UINT8     IccFailsafeProfile  : 4;
      UINT8     Reserved            : 3;
      UINT8     IccRuntimeSelect    : 1;
    } Fields;
  } OemParams;
  UINT8             IccProfileIndex;
  UINT8             Reserved;
  ICC_PROFILE_DESC  IccProfileDesc[MAX_NUM_ICC_PROFILES];
} ICC_GET_PROFILE_RESPONSE;

typedef union {
  ICC_GET_PROFILE_MESSAGE   Message;
  ICC_GET_PROFILE_RESPONSE  Response;
} ICC_GET_PROFILE_BUFFER;

typedef struct {
  ICC_HEADER  Header;
  UINT8       BiosIccProfile;
  UINT8       PaddingA;
  UINT16      PaddingB;
} ICC_SET_PROFILE_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
} ICC_SET_PROFILE_RESPONSE;

typedef union {
  ICC_SET_PROFILE_MESSAGE   Message;
  ICC_SET_PROFILE_RESPONSE  Response;
} ICC_SET_PROFILE_BUFFER;

///
/// Get/Set ICC Clock Capabilities
///
typedef struct {
  ICC_HEADER  Header;
} ICC_GET_CLK_CAPABILITIES_MESSAGE;

typedef struct {
  ICC_HEADER  Header;
  UINT32      VersionNumber;
  UINT8       IccHwSku;
  UINT8       Reserved;
  UINT16      MaxSusramRecordSize;
  UINT64      IccSkuEnforcementTable;
  UINT32      IccBootStatusReport;
} ICC_GET_CLK_CAPABILITIES_RESPONSE;

typedef union {
  ICC_GET_CLK_CAPABILITIES_MESSAGE  Message;
  ICC_GET_CLK_CAPABILITIES_RESPONSE Response;
} ICC_GET_CLK_CAPABILITIES_BUFFER;

//
// Defines the HECI request buffer format for the ICC_HSIO_WRITE_SETTINGS_CMD.
//
typedef struct {
   ICC_HEADER  Header;      ///< Standard ICC HECI Header
   UINT32      Reserved;    ///< Reserved for future use
} HSIO_WRITE_SETTINGS_REQ;

///
/// Get/Set Clock Settings
///

///
/// Used for the FLAGS parameter of Get/Set Clock Settings
///
typedef union {
  UINT8 u;
  struct {
    UINT8 RoundDown   : 1;
    UINT8 Reserved    : 7;
  } Flags;
} ICC_CLOCK_SETTINGS_FLAGS;

///
/// Used for the CURRENT FLAGS parameter of Get/Set Clock Settings
///
typedef union {
  UINT16 u;
  struct {
    UINT16 Reserved           : 3;  ///< Reserved.
    UINT16 ForcePowerFlow     : 1;  ///< This indicates that the clock settings will include a power flow, depending on the specific platform.
    /**
      Specifies how the settings with associated clock were applied.
      0 - Persistent
      1 - Dynamic , indicating a run time ad-hoc change (ramp)
      2 - Reserved
      3 - Reserved
    **/
    UINT16 Type               : 2;
    UINT16 SetToDefault       : 1;  ///< Revert this clock to nominal.
    UINT16 Reserved1          : 3;  ///< Reserved.
    /**
      New Boot settings applied and power cycle reset pending.
      Flag cleared once boot settings are consumed.
      Reserved in Set Clock Settings.
    **/
    UINT16 PwrCyclePending    : 1;
    UINT16 Reserved2          : 5;
  } Flags;
} ICC_CLOCK_SETTINGS_CURRENT_FLAGS;

///
/// Used for the SUPPORTED FLAGS parameter of Get/Set Clock Settings
///
typedef union {
  UINT16 u;
  struct {
    UINT16 Reserved           : 1;  ///< Reserved.
    UINT16 DownSpread         : 1;  ///< Down spread SSC supported.
    UINT16 UpSpread           : 1;  ///< Up spread SSC supported.
    UINT16 CenterSpread       : 1;  ///< Center spread SSC supported.
    UINT16 ChangeAllowed      : 1;  ///< Frequency & Spread changes allowed.
    UINT16 HaltAllowed        : 1;  ///< Spread can be enabled or disabled.
    UINT16 PCIe               : 1;  ///< Clock uses the PCIe clock source
    UINT16 Bclk               : 1;  ///< Clock uses the BCLK clock source
    UINT16 Reserved1          : 8;  ///< Reserved.
  } Flags;
} ICC_CLOCK_SETTINGS_SUPPORTED_FLAGS;

///
/// Structure for Clock Settings
///
typedef struct {
  UINT8                              ReqClock;
  UINT8                              SettingType;
  ICC_CLOCK_SETTINGS_FLAGS           Flags;
  UINT8                              Reserved;
  UINT32                             Freq;
  UINT32                             UserFreq;
  UINT32                             MaxFreq;
  UINT32                             MinFreq;
  UINT8                              SscMode;
  UINT8                              SscPercent;
  UINT8                              MaxSscPercent;
  UINT8                              Reserved1;
  ICC_CLOCK_SETTINGS_CURRENT_FLAGS   CurrentFlags;
  ICC_CLOCK_SETTINGS_SUPPORTED_FLAGS SupportFlags;
} ICC_CLOCK_SETTINGS;


///
/// Combined Request and Response structure for Get/Set Clock Settings
///
typedef struct {
  ICC_HEADER                         Header;
  ICC_CLOCK_SETTINGS                 ClockSettings;
} ICC_GETSET_CLOCK_SETTINGS_REQRSP;

typedef union {
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  Message;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  Response;
} ICC_GET_CLOCK_SETTINGS_BUFFER;

typedef union {
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  Message;
  ICC_GETSET_CLOCK_SETTINGS_REQRSP  Response;
} ICC_SET_CLOCK_SETTINGS_BUFFER;

//
// Defines the HECI request buffer format for the ICC_HSIO_WRITE_SETTINGS_CMD.
//
typedef struct {
  ICC_HEADER  Header;      ///< Standard ICC HECI Header
  UINT32      Reserved;    ///< Reserved for future use
  UINT8       MphyData[];  ///< Payload
} ICC_SET_MPHY_SETTINGS_REQ;

//
// Defines the HECI request buffer format for the ICC_HSIO_READ_MPHY_CMD.
//
typedef struct {
  ICC_HEADER  Header;         ///< Standard ICC HECI Header
  UINT32      Reserved;       ///< Reserved for future use
  UINT32      Offset;         ///< Offset in the mPhy file to start reading from
  UINT32      Reserved2;      ///< Reserved for future use
  UINT32      NumBytesToRead; ///< How many bytes to read. For the entire file specifiy the mPhy max size
} HSIO_READ_MPHY_REQ;

//
// Defines the HECI request buffer format for reponse to ICC_HSIO_READ_MPHY_CMD.
//
typedef struct {
  ICC_HEADER  Header;               ///< Standard ICC HECI Header
  UINT32      Reserved;             ///< Reserved for future use
  UINT32      MphyFileSize;         ///< mPhy file size. This will be filled regardless of how many bytes the user asked to read (e.g. zero)
  UINT32      Reserved2;            ///< Reserved for future use
  UINT32      NumBytesActuallyRead; ///< How many bytes were actually read, having less than requested is NOT an error
  UINT32      Reserved3;            ///< Reserved for future use
  UINT8       Payload[];            ///< The binary content requested (or at least as many bytes as we could read)
} HSIO_READ_MPHY_ACK;

typedef union {
  HSIO_READ_MPHY_REQ Request;
  HSIO_READ_MPHY_ACK Response;
} HSIO_READ_MPHY_BUFFER;

#pragma pack()

#endif // _ICC_MSGS_H
