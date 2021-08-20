/** @file
  MKHI Messages

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
#ifndef _MKHI_MSGS_H
#define _MKHI_MSGS_H

#pragma pack(1)

///
/// MKHI host message header. This header is part of HECI message sent from MEBx via
/// Host Configuration Interface (HCI). ME Configuration Manager or Power Configuration
/// Manager also include this header with appropriate fields set as part of the
/// response message to the HCI.
///
typedef union {
  UINT32  Data;
  struct {
    UINT32  GroupId    : 8;
    UINT32  Command    : 7;
    UINT32  IsResponse : 1;
    UINT32  Reserved   : 8;
    UINT32  Result     : 8;
  } Fields;
} MKHI_MESSAGE_HEADER;


///
/// Defines for GroupID
///
#define MKHI_CBM_GROUP_ID        0x00
#define MKHI_FWCAPS_GROUP_ID     0x03
#define MKHI_HMRFPO_GROUP_ID     0x05
#define MKHI_MCA_GROUP_ID        0x0A
#define MKHI_GEN_DNX_GROUP_ID    0x0D
#define MKHI_BUP_COMMON_GROUP_ID 0xF0
#define MKHI_GEN_GROUP_ID        0xFF

#define CSE_DNX_REQ_SET          0x01
#define IAFW_DNX_REQ_CLEAR       0x02

///
/// Defines for Command
///
///
/// Defines for CBM_GROUP Command
///
#define CBM_RESET_CMD                               0x0B
///
/// Defines for FWCAPS_GROUP Command
///
#define FWCAPS_GET_RULE_CMD                         0x02
#define FWCAPS_SET_RULE_CMD                         0x03
///
/// Defines for HMRFPO_GROUP Command
///
#define HMRFPO_ENABLE_CMD_ID                        0x01
#define HMRFPO_LOCK_CMD_ID                          0x02
#define HMRFPO_GET_STATUS_CMD_ID                    0x03
///
/// Defines for MCA_GROUP Command
///
#define MCA_COMMIT_FILES_CMD                        0x04
#define MCA_CORE_BIOS_DONE_CMD                      0x05
#define MCA_READ_FILE_EX_CMD                        0x0A
#define MCA_SET_FILE_EX_CMD                         0x0B
#define MCA_REQUEST_DEVICE_OWNERSHIP                0x0F
///
/// Defines for BUP_COMMON Command
///
#define BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2_CMD 0x1A
#define MCA_ARB_SVN_COMMIT_CMD                      0x1B
#define MCA_ARB_SVN_GET_INFO_CMD                    0x1C
///
/// Defines for GEN_GROUP Command
///
#define GEN_GET_MKHI_VERSION_CMD                    0x01
#define GEN_GET_FW_VERSION_CMD                      0x02
#define GEN_END_OF_POST_CMD                         0x0C
#define GEN_GET_ME_UNCFG_STATE_CMD                  0x0E
#define GEN_SET_ME_RESET_HALT_CMD                   0x10
#define GEN_FW_FEATURE_STATE_OVERRIDE_CMD           0x14
#define GEN_SET_FIPS_MODE_CMD                       0x20
#define GEN_GET_FIPS_MODE_CMD                       0x21
#define GEN_SET_MEASURED_BOOT_STATE_CMD             0x22
#define GEN_GET_MEASURED_BOOT_STATE_CMD             0x23

//
// Typedef for Result field of MHKI Header
//
typedef enum {
  MkhiStatusSuccess,
  MkhiStatusInvalidState,
  MkhiStatusMessageSkipped,
  MkhiStatusSizeError       = 0x5,
  MkhiStatusInvalidAccess   = 0x84,
  MkhiStatusInvalidParams   = 0x85,
  MkhiStatusNotReady        = 0x88,
  MkhiStatusNotSupported    = 0x89,
  MkhiStatusInvalidAddress  = 0x8C,
  MkhiStatusInvalidCommand  = 0x8D,
  MkhiStatusFailure         = 0x9E,
  MkhiStatusInvalidResource = 0xE4,
  MkhiStatusResourceInUse   = 0xE5,
  MkhiStatusNoResource      = 0xE6,
  MkhiStatusGeneralError    = 0xFF
} MKHI_RESULT;


//
// MKHI_FWCAPS_GROUP_ID Definitions
//

//
// Definitions for Firmware Capabilities Group Rule Id
//

#define FW_CAPS_RULE_ID                0x00
#define ME_PLATFORM_STATUS_RULE_ID     0x06
#define FW_UPDATE_RULE_ID              0x07
#define PLATFORM_TYPE_RULE_ID          0x1D
#define FW_FEATURE_STATE_RULE_ID       0x20
#define OEM_TAG_RULE_ID                0x2B
#define ACM_TPM_DATA_RULE_ID           0x2F
#define UNCONFIG_ON_RTC_CLEAR_RULE_ID  0x30
#define AMT_BIOS_SYNC_INFO_RULE_ID     0x30005

#define RULE_DATA_LENGTH               0x04

typedef union {
  UINT32  Data;
  struct {
    UINT32  RuleTypeId : 16;
    UINT32  FeatureId  : 8;
    UINT32  Reserved   : 8;
  } Fields;
} RULE_ID;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
} GET_RULE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
  UINT8               RuleDataLen;
  UINT32              RuleData;
} GET_RULE_ACK;

typedef union {
  GET_RULE            Request;
  GET_RULE_ACK        Response;
} GET_RULE_BUFFER;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
  UINT8               RuleDataLen;
  UINT32              RuleData;
} SET_RULE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              RuleId;
} SET_RULE_ACK;

typedef union {
  SET_RULE            Request;
  SET_RULE_ACK        Response;
} SET_RULE_BUFFER;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} REQUEST_OWNERSHIP;

typedef union {
  REQUEST_OWNERSHIP   Request;
  REQUEST_OWNERSHIP   Response;
} REQUEST_OWNERSHIP_BUFFER;

///
/// Get Firmware Capability
///

typedef union {
  UINT32  Data;
  struct {
    UINT32  FullMng         : 1;      ///< [0] Full manageability
    UINT32  StdMng          : 1;      ///< [1] Standard manageability
    UINT32  Amt             : 1;      ///< [2] Amt
    UINT32  Reserved        : 1;      ///< [3] Reserved
    UINT32  IntegratedTouch : 1;      ///< [4] Intel Integrated Touch
    UINT32  EyeRiver        : 1;      ///< [5] Eye River
    UINT32  IntelCLS        : 1;      ///< [6] IntelR Capability Licensing Service (CLS)
    UINT32  Reserved1       : 3;      ///< [9:7] Reserved
    UINT32  ISH             : 1;      ///< [10] IntelR Sensor Hub
    UINT32  Reserved2       : 1;      ///< [11] Reserved
    UINT32  PAVP            : 1;      ///< [12] Protected Audio Video Path (PAVP)
    UINT32  Reserved3       : 4;      ///< [16:13] Reserved
    UINT32  IPV6            : 1;      ///< [17] IPV6
    UINT32  KVM             : 1;      ///< [18] KVM Remote Control (KVM)
    UINT32  Reserved4       : 1;      ///< [19] Reserved
    UINT32  DAL             : 1;      ///< [20] Dynamic Application Loader (DAL)
    UINT32  TLS             : 1;      ///< [21] Cipher Transport Layer (TLS)
    UINT32  Reserved5       : 1;      ///< [22] Reserved
    UINT32  WLAN            : 1;      ///< [23] Wireless LAN (WLAN)
    UINT32  Reserved6       : 1;      ///< [24] Reserved
    UINT32  TrustedDevice   : 1;      ///< [25] Trusted Device
    UINT32  Reserved7       : 3;      ///< [28:26] Reserved
    UINT32  PTT             : 1;      ///< [29] Platform Trust Technology (PTT)
    UINT32  Reserved8       : 2;      ///< [31:30] Reserved
  } Fields;
} MEFWCAPS_SKU;

///
/// Get/Set Local FW Update
///
typedef enum {
  UpdateDisabled,
  UpdateEnabled
} LOCAL_FW_UPDATE;

///
/// Get Platform Type
///
typedef enum {
  NoBrand,
  IntelAmtBrand,
  IntelStandardManageabilityBrand,
  IntelReservedBrand1,
  IntelReservedBrand2,
  IntelReservedBrand3
} PLATFORM_BRAND;

typedef enum {
  IntelMeConsumerFw        = 3,
  IntelMeCorporateFw
} ME_IMAGE_TYPE;

typedef enum {
  RegularSku,
  SuperSku
} SKU_TYPE;

typedef enum {
  PlatformMobile          = 1,
  PlatformDesktop         = 2,
  PlatformServer          = 4,
  PlatformWorkstation     = 8
} PLATFORM_TARGET_USAGE_TYPE;

typedef union {
  UINT32  Data;
  struct {
    UINT32  PlatformTargetUsageType : 4;
    UINT32  Reserved                : 2;
    UINT32  SuperSku                : 1;
    UINT32  Reserved1               : 1;
    UINT32  IntelMeFwImageType      : 4;
    UINT32  PlatformBrand           : 4;
    UINT32  Reserved2               : 16;
  } Fields;
} PLATFORM_TYPE_RULE_DATA;

///
/// Set ME Disable
///

#define ME_DISABLE         0

///
/// Set ACM TPM
///

typedef union {
  UINT32 Data;
  struct {
    UINT32 Reserved      : 8;
    UINT32 TpmDeactivate : 1;
    UINT32 Reserved1     : 23;
  } Fields;
} TPM_STATE;

///
/// Unconfig On Rtc Clear Status
///
typedef enum {
  EnableState  = 0,  ///< [Unconfigure on RTC Clear] is enabled.
  DisableState = 1   ///< [Unconfigure on RTC Clear] is disabled.
} ME_UNCONFIG_ON_RTC_CLEAR_STATUS;

//
// MKHI_HMRFPO_GROUP_ID Definitions
//

///
/// HMRFPO ENABLE
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              Reserved[2];
} HMRFPO_ENABLE;

///
/// HMRFPO_ENABLE returned Status
///
#define HMRFPO_ENABLE_SUCCESS         0x00
#define HMRFPO_ENABLE_LOCKED          0x01
#define HMRFPO_NVAR_FAILURE           0x02
#define HMRFPO_ENABLE_UNKNOWN_FAILURE 0x05

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              Reserved[2];
  UINT8               Status;
  UINT8               Reserved1[3];
} HMRFPO_ENABLE_ACK;

typedef union {
  HMRFPO_ENABLE          Request;
  HMRFPO_ENABLE_ACK      Response;
} HMRFPO_ENABLE_BUFFER;

///
/// HMRFPO LOCK
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} HMRFPO_LOCK;

///
/// HMRFPO_LOCK_RESPONSE returned Status
///
#define HMRFPO_LOCK_SUCCESS 0x00
#define HMRFPO_LOCK_FAILURE 0x01

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              Reserved[4];
  UINT8               Status;
  UINT8               Reserved1[3];
} HMRFPO_LOCK_ACK;

typedef union {
  HMRFPO_LOCK          Request;
  HMRFPO_LOCK_ACK      Response;
} HMRFPO_LOCK_BUFFER;

///
/// HMRFPO GET STATUS
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} HMRFPO_GET_STATUS;

///
/// HMRFPO_GET_STATUS returned Status
///
#define HMRFPO_DISABLED         0x00
#define HMRFPO_LOCKED           0x01
#define HMRFPO_ENABLED          0x02

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT8               Status;
  UINT8               Reserved[3];
} HMRFPO_GET_STATUS_ACK;

typedef union {
  HMRFPO_GET_STATUS          Request;
  HMRFPO_GET_STATUS_ACK      Response;
} HMRFPO_GET_STATUS_BUFFER;

///
/// MKHI_MCA_GROUP_ID Definitions
///
#define MCA_DAM_FILE_SIZE                 1
#define MCA_MAX_FILE_SIZE                 4096

#define MCA_DAM_FILE_ID                   0x10050000

#define MCA_AMT_PROV_STATE_FILE_ID        0x0802
#define MCA_AMT_PROV_ADT_REC_FILE_ID      0x01A6
#define MCA_AMT_SEC_PKI_FILE_ID           0x01A0
#define MCA_AMT_BIOS_REDIR_FILE_ID        0x0803

///
/// Read File Ex
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              FileId;
  UINT32              Offset;
  UINT32              DataSize;
  UINT8               Flags;
} READ_FILE_EX;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              DataSize;
  UINT8               Data[];    ///< Data Buffer
} READ_FILE_EX_ACK;

typedef union {
  READ_FILE_EX        Request;
  READ_FILE_EX_ACK    Response;
} READ_FILE_EX_BUFFER;

///
/// Set File Ex
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              FileId;
  UINT32              Offset;
  UINT32              DataSize;
  UINT8               Flags;
  UINT8               Data[];     ///< Data Buffer
} SET_FILE_EX;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} SET_FILE_EX_ACK;

typedef union {
  SET_FILE_EX         Request;
  SET_FILE_EX_ACK        Response;
} SET_FILE_EX_BUFFER;

///
/// Commit Files
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} COMMIT_FILES;

///
/// Core Bios Done
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} CORE_BIOS_DONE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} CORE_BIOS_DONE_ACK;

///
/// HW Anti-Rollback (ARB) Security Version Number Commit
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              Reserved; ///< Reserved for future use, to allow specifying explicit usage to be committed.
} ARB_SVN_COMMIT;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} ARB_SVN_COMMIT_ACK;

typedef union {
  ARB_SVN_COMMIT       Request;
  ARB_SVN_COMMIT_ACK   Response;
} ARB_SVN_COMMIT_BUFFER;

///
/// HW Anti-Rollback (ARB) Security Version Number Get Info
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} ARB_SVN_GET_INFO;

typedef struct {
  UINT8           UsageId;              ///< Key usage number according to FAS manifest.
  /* Used in SPS to indicate partition.
     In client the SVN is same for all partitions
     0 - Boot partition 1 (RCV in SPS)
     1 - Boot partition 2 (OPR1 in SPS)
     2 - Boot partition 3 (OPR2 in SPS)
  */
  UINT8           BootPartitionId;
  UINT8           ExecutingSvn;         ///< The SVN value of the FW currently running.
  UINT8           MinAllowedSvn;        ///< The minimal SVN allowed on platform for given usage.
} ARB_SVN_INFO_ENTRY;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  UINT32              NumEntries;       ///< Number of ARB SVN Entry
  ARB_SVN_INFO_ENTRY  ArbSvnEntry [0];
} ARB_SVN_GET_INFO_ACK;

typedef union {
  ARB_SVN_GET_INFO       Request;
  ARB_SVN_GET_INFO_ACK   Response;
} ARB_SVN_GET_INFO_BUFFER;

//
// MKHI_GEN_GROUP_ID Definitions
//

///
/// MKHI_BUP_COMMON_GROUP_ID Definitions
///
#define CSE_MAX_FIXED_IV_SIZE  16
#define CSE_SEED_LEN           64
#define CSE_SEED_MAX_ENTRIES    4

/// 
/// BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2
///

typedef struct BootloaderFixedSeedIv
{
  UINT8 FixedSeedIvSize;
  UINT8 FixedSeedIv[CSE_MAX_FIXED_IV_SIZE];
} BOOTLOADER_FIXED_SEED_IV;

typedef struct BootloaderSeedInfoEx
{
  UINT8 CseSvn;        // Always 0 for fixed seed.
  UINT8 BiosSvn;       // Always 0 for fixed seed.
                       // For SVN bound seed, populated only in ICL and above.
  UINT8 Reserved[2];
  UINT8 Seed[CSE_SEED_LEN];
} BOOTLOADER_SEED_INFO_EX;

typedef struct BootloaderSeedInfoExList
{
  BOOTLOADER_SEED_INFO_EX FixedSeed;
  UINT8                   NumOfSvnSeeds;
  BOOTLOADER_SEED_INFO_EX SVNSeedList[CSE_SEED_MAX_ENTRIES];
} BOOTLOADER_SEED_INFO_EX_LIST;

// Request
typedef struct {
  MKHI_MESSAGE_HEADER      MkhiHeader;
  BOOTLOADER_FIXED_SEED_IV FixedSeedIv;
} BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2;

// Response
typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
  BOOTLOADER_SEED_INFO_EX_LIST CseSeedList;
} BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2_ACK;

typedef union {
  BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2     Request;
  BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2_ACK Response;
} BUP_COMMON_BOOTLOADER_GET_SEED_LIST_EX2_BUFFER;

///
/// Get MKHI Version
///
#define MKHI_MSG_VERSION_MAJOR 0x1
#define MKHI_MSG_VERSION_MINOR 0x1

typedef union {
  UINT32 Data;
  struct {
    UINT32 Minor : 16;
    UINT32 Major : 16;
  } Fields;
} MKHI_VERSION;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} GET_MKHI_VERSION;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  MKHI_VERSION        MkhiVersion;
} GET_MKHI_VERSION_ACK;

typedef union {
  GET_MKHI_VERSION     Request;
  GET_MKHI_VERSION_ACK Response;
} GET_MKHI_VERSION_BUFFER;

///
/// Get FW Version
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} GET_FW_VER;

typedef struct {
  UINT32  CodeMinor   : 16;
  UINT32  CodeMajor   : 16;
  UINT32  CodeBuildNo : 16;
  UINT32  CodeHotFix  : 16;
  UINT32  RcvyMinor   : 16;
  UINT32  RcvyMajor   : 16;
  UINT32  RcvyBuildNo : 16;
  UINT32  RcvyHotFix  : 16;
  UINT32  FitcMinor   : 16;
  UINT32  FitcMajor   : 16;
  UINT32  FitcBuildNo : 16;
  UINT32  FitcHotFix  : 16;
} GET_FW_VER_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_FW_VER_ACK_DATA Data;
} GET_FW_VER_ACK;

typedef struct {
  UINT16              Major;
  UINT16              Minor;
  UINT16              Hotfix;
  UINT16              Build;
} FIPS_VERSION;

typedef struct {
  UINT32              FipsMode;
  FIPS_VERSION        CryptoVersion;
  UINT8               Reserved[8];
} GET_FIPS_MODE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} GET_FIPS_MODE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  GET_FIPS_MODE_DATA  Data;
} GET_FIPS_MODE_ACK;

typedef union {
  GET_FIPS_MODE       Request;
  GET_FIPS_MODE_ACK   Response;
} GET_FIPS_MODE_BUFFER;

#define FIPS_MODE_DISABLED 0
#define FIPS_MODE_ENABLED  1

typedef struct {
  UINT32              FipsMode;
} SET_FIPS_MODE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  SET_FIPS_MODE_DATA  Data;
} SET_FIPS_MODE;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} SET_FIPS_MODE_ACK;

typedef union {
  SET_FIPS_MODE       Request;
  SET_FIPS_MODE_ACK   Response;
} SET_FIPS_MODE_BUFFER;

///
/// CSME Measured Boot
///
typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
} GET_MEASURED_BOOT;

typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
  UINT8                   Data;
} GET_MEASURED_BOOT_ACK;

typedef union {
  GET_MEASURED_BOOT       Request;
  GET_MEASURED_BOOT_ACK   Response;
} GET_MEASURED_BOOT_BUFFER;

typedef struct {
  MKHI_MESSAGE_HEADER     MkhiHeader;
  UINT8                   Data;
} SET_MEASURED_BOOT;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} SET_MEASURED_BOOT_ACK;

typedef union {
  SET_MEASURED_BOOT       Request;
  SET_MEASURED_BOOT_ACK   Response;
} SET_MEASURED_BOOT_BUFFER;

///
/// End of Post
///
#define EOP_DISABLED    0
#define EOP_SEND_IN_PEI 1
#define EOP_SEND_IN_DXE 2

#define MAX_EOP_SEND_RETRIES 3

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} END_OF_POST;

typedef enum {
  HeciEopStatusSuccess,
  HeciEopPerformGlobalReset
} EOP_REQUESTED_ACTIONS;

typedef struct {
  UINT32  RequestedActions;
} EOP_ACK_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  EOP_ACK_DATA        Data;
} END_OF_POST_ACK;

typedef union {
 END_OF_POST     Request;
 END_OF_POST_ACK Response;
} END_OF_POST_BUFFER;

///
/// Get ME Unconfiguration State
///
#define ME_UNCONFIG_IN_PROGRESS     0x01 ///< Unconfig without password is in progress
#define ME_UNCONFIG_NOT_IN_PROGRESS 0x02 ///< Normal case, there is no unconfigure w/o password to be processed
#define ME_UNCONFIG_FINISHED        0x03 ///< CSME finished processing unconfigure w/o password. Bios will perform a global reset
#define ME_UNCONFIG_ERROR           0x80 ///< CSME encountered error while processing revert back to default. Specific error status defined starting at 0x81

typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} GEN_GET_ME_UNCFG_STATE;

///
/// FW Feature Shipment Time State Override
///
typedef struct {
  UINT32  EnableFeature;
  UINT32  DisableFeature;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER                          MkhiHeader;
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_DATA FeatureState;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE;

///
/// FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE returned Status
///
typedef enum {
  SetFeatureStateAccepted,
  SetFeatureStateRejected
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_RESPONSE;

typedef struct {
  MKHI_MESSAGE_HEADER   MkhiHeader;
  UINT32                Status;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_ACK;

typedef union {
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE      Request;
  FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_ACK  Response;
} FW_FEATURE_SHIPMENT_TIME_STATE_OVERRIDE_BUFFER;

///
/// Set Manufacturing ME Reset and Halt messages
///
typedef struct {
  MKHI_MESSAGE_HEADER   MkhiHeader;
} SET_ME_RESET_HALT;

typedef struct {
  MKHI_MESSAGE_HEADER   MkhiHeader;
} SET_ME_RESET_HALT_ACK;

typedef struct {
  MKHI_MESSAGE_HEADER  MkhiHeader;
  UINT32               Flag;
} IAFW_DNX_REQ_CLEAR_REQ_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER  MkhiHeader;
} IAFW_DNX_REQ_CLEAR_RESP_DATA;

typedef union {
  IAFW_DNX_REQ_CLEAR_REQ_DATA  *Request;
  IAFW_DNX_REQ_CLEAR_RESP_DATA *Response;
} IAFW_DNX_REQ_CLEAR_BUFFER;

typedef struct {
  MKHI_MESSAGE_HEADER  MKHIHeader;
} IAFW_DNX_REQ_SET_REQ_DATA;

typedef struct {
  MKHI_MESSAGE_HEADER  MKHIHeader;
  UINT32               ReqBiosAction;
} IAFW_DNX_REQ_SET_RESP_DATA;

#pragma pack()

#endif // _MKHI_MSGS_H
