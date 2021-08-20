/** @file
  BHP package format definition
   * Ins is short for install
   * Sig is short for signature
   * AC is short for Admin Command
   * TA is short for Trusted Application
   * NTA is for nativeTA and JTA is for JavaTA
   * SD is short for Security Domain
   * Check CSE Beihai HLD for more details of the keyword
   *
   * Each section has to be aligned on 4 bytes
   * Changes applied on them should be consitent with
   * package_generator(BPKT) and package_parser(admin_pack lib)
   * ACPackage
   *   |--ACPackHeader--|--ACInsCond--|--data--|--ACSignature--|
   *   Use idx_XXX to reference condition/data
   * The package that ACPackage.data contains:
   *   AC Install SD Package structure:
   *     |--ACInsSDHeader--|--ACInsGroups--|--ACName--|
   *   AC Uninstall SD
   *     |--BH_SDID--|
   *   AC Install JTA Package structure:
   *     |--ACInsJTAHeader--|--ACInsHash--|--ACInsGroups--|
   *     |--ACInsReasons(post)--|--ACInsReasons(reg)--|--ACName--|
   *   AC Intall Native TA Package structure:
   *     |--ACInsNTAHeader--|--ACInsHash--|--ACInsGroups--|
   *     |--ACInsMetadata--|--ACName--|
   *   AC UninstallTA
   *     |--BH_TAID, ACInsCond--|

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

#ifndef BH_ACP_FORMAT_H
#define BH_ACP_FORMAT_H

#include "bh_shared_types.h"

#ifdef _MSC_VER
#pragma warning (disable:4200)
#endif

//make sure those limitation values are adjusted to real world
#define BH_MAX_ACP_INS_REASONS_LENGTH 1024
#define BH_MAX_ACP_USED_SERVICES 20
#define BH_MAX_ACP_SVL_RECORDS 40
#define BH_MAX_ACP_PORPS_LENGTH 2048
#define BH_MAX_ACP_SIG_EXT_LENGTH 544
#define BH_MAX_ACP_NTA_METADATA_LENGTH 5120

typedef char* TEMP_SIG_KEY;
typedef BH_U32 TEMP_SIG_SIG;
typedef char* TEMP_COND;
typedef BH_U32 TEMP_HASH;

enum AC_CMD_ID {
    AC_CMD_INVALID,
    AC_INSTALL_SD,
    AC_UNINSTALL_SD,
    AC_INSTALL_JTA,
    AC_UNINSTALL_JTA,
    AC_INSTALL_NTA,
    AC_UNINSTALL_NTA,
    AC_UPDATE_SVL,
    AC_INSTALL_JTA_PROP,
    AC_CMD_NUM
};

enum AC_TA_TYPE {
    AC_TA_TYPE_BOTH,
    AC_TA_TYPE_JAVA,
    AC_TA_TYPE_NATIVE,
};

/*TBD:
typedef struct {
    BH_U32 enc_alg;
    BH_U32 len;
    char data[0];
} ACEncryption;
*/

#pragma pack(1)

typedef struct {
    /*ACP Header*/
    BH_U8 magic[4];
    BH_U8 version;
    BH_U8 little_endian;
    BH_U16 reserved;
    BH_U32 size;/*total package size in byte except signature*/
    BH_U32 cmd_id;
    BH_U32 svn;

    /*Section Index*/
    BH_U32 idx_num;
    BH_U32 idx_condition;
    /*TBD: BH_U32 idx_encrypt;*/
    BH_U32 idx_data;
} ACPackHeader;


typedef struct {
    BH_U8 len;/*the size of data in byte*/
    BH_I8 data[0];
} ACName;

typedef struct {
    BH_TAID ta_id;
    BH_U32 ta_svn;
} ACSV;

struct BH_SV_LIST{
    BH_U32 num; //number of sv items
    ACSV data[0];
};

struct BH_TAID_LIST {
    BH_U32 num;
    BH_TAID list[0];
};

/*
Firmware properties are formatted as "type\0key\0value\0"
Example: "string\0name\0Tom\0int\0Age\013\0"
*/
struct BH_PROP_LIST {
    BH_U32 num; //number of properties
    BH_U32 len; //the size of data in byte
    BH_I8 data[0];
};

typedef struct BH_PROP_LIST ACProp;
typedef struct BH_TAID_LIST ACTAIDList;
typedef struct BH_SV_LIST ACSVList;
typedef struct {
    BH_U32 len; /*the amount of items in data*/
    BH_U8 data[0];
} ACInsHash;

typedef struct {
    /*NOTE: len means the amount of items in data,
    when counting total bytes, you need to multiply it with sizeof(data[0]) */
    BH_U32 len;
    BH_U32 data[0];
} ACInsReasons;

typedef struct {
    BH_U32 len; /*the amount of items in data*/
    BH_U8 data[0];
} ACInsMetadata;

typedef struct {
    BH_SDID sd_id;
    BH_U32 sd_svn;
    BH_U16 ssd_num;
    BH_U8 ta_type;
    BH_U8 reserved;
    BH_U16 max_ta_can_install;
    BH_U16 max_ta_can_run;
    BH_U32 flash_quota;
    BH_U64 ac_groups;
    BH_I8 sd_name[32];
} ACInsSDHeader;

#pragma pack()

//it should match the key type with BeihaiHAL.h
enum SIG_KEY_TYPE {UNKNOWN = 0, INTEL_PLATFORM_KEY, DAL_KEY_1, INTEL_KEY_Manifest_V1, AC_SIG_KEY_OTHER};

#define AC_SIG_KEY_LEN 260

#pragma pack(1)

typedef struct {
    BH_U16 sig_alg;
    BH_U16 sig_key_type;
    /*sig_data covers sig_key and sig_manifest,
      parser of signature should be reponsible to extract them
      according to sig_alg and sig_key_type*/
    BH_I8 sig_key[AC_SIG_KEY_LEN];
} ACInsSDSigKey;

#define AC_MAX_SIGNATURE_LEN 256
typedef struct {
    BH_U8 sig_magic[4];
    BH_I8 sig_version;
    BH_U8 reserved;
    BH_U16 sig_len;
    BH_SDID sig_sd;
    BH_U16 sig_alg;
    BH_U16 sig_key_type;
    BH_I8 sig_key_manifest[AC_SIG_KEY_LEN];
    /*sig_data covers signing result
      signature verification API should be reponsible to extract them
      according to sig_alg and sig_key_type.
      Its max length is AC_MAX_SIGNATURE_LEN*/
    BH_I8 sig_data[0];
} ACSig;

/*
below structures are the parsing result that application layer should use
they are in-memory representation of admin packages
*/
typedef struct {
    ACPackHeader *head;
    /*the type of data depends on head->cmd_id*/
    char data[0];
    /*--ACSignature is appendeded after command package*/
} ACPack;

typedef struct {
    ACProp* ins_cond;
    ACInsSDHeader* head;
    ACInsSDSigKey* sig_key;
} ACInsSDPack;

typedef struct {
    BH_SDID* p_sdid;
} ACUnsSDPack;

typedef struct {
    BH_TAID ta_id;
    BH_U32 ta_svn;
    BH_U8 hash_alg_type;
    BH_U8 ta_reserved[3];
    BH_PACK_HASH hash;
} ACInsTAHeader; /*header struct shared between JTA and NTA*/

typedef ACInsTAHeader ACInsNTAHeader;
typedef ACInsTAHeader ACInsJTAHeader;

typedef struct {
    ACProp* ins_cond;
    ACInsJTAHeader* head;
} ACInsJTAPack;

typedef struct {
    BH_U32 mem_quota;
    BH_U8 ta_encrypted;
    BH_U8 padding;
    BH_U16 allowed_inter_session_num;
    BH_U64 ac_groups;
    BH_U32 timeout;
} ACInsJTAPropHeader;

typedef struct {
    ACInsJTAPropHeader* head;
    ACInsReasons *post_reasons;
    ACInsReasons *reg_reasons;
    ACProp *prop;
    ACTAIDList *used_service_list;
} ACInsJTAProp;


typedef struct {
    ACProp* ins_cond;
    ACInsNTAHeader* head;
    ACInsMetadata* mdata;
} ACInsNTAPack;

typedef struct {
    BH_TAID* p_taid;
} ACUnsTAPack;

typedef struct {
    ACProp* ins_cond;
    ACSVList* sv_list;
} ACUpdateSVLPack;

#pragma pack()

#endif
