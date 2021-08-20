/** @file
  Header file for Reference code Firmware Version Info Init Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _SI_FVI_H_
#define _SI_FVI_H_

///
/// Non-static SMBIOS table data to be filled later with a dynamically generated value
///
#define TO_BE_FILLED  0
#define TO_BE_FILLED_STRING  " "        ///< Initial value should not be NULL

///
/// String references in SMBIOS tables. This eliminates the need for pointers.
/// See the DMTF SMBIOS Specification v2.7.1, section 6.1.3.
///
#define NO_STRING_AVAILABLE  0
#define STRING_1  1
#define STRING_2  2
#define STRING_3  3
#define STRING_4  4
#define STRING_5  5
#define STRING_6  6
#define STRING_7  7

#define FVI_NUMBER_OF_STRINGS  2

#pragma pack(1)

///
/// The string number for ComponentName and VersionString is always calculated dynamically.
/// The initial value is ignored and should always be TO_BE_FILLED.
///
#define DEFAULT_FVI_DATA() \
{ \
  TO_BE_FILLED, \
  TO_BE_FILLED, \
  { \
    TO_BE_FILLED, \
    TO_BE_FILLED, \
    TO_BE_FILLED, \
    TO_BE_FILLED, \
  } \
}

#define FVI_VERSION(Version) \
{ \
  TO_BE_FILLED, \
  TO_BE_FILLED, \
  Version \
}

#define DEFAULT_FVI_STRINGS(Name) \
{ \
  Name ## _FVI_STRING, \
  NULL \
}

#define DEFAULT_FVI_VERSION \
{ \
  0xFF, 0xFF, 0xFF, 0xFFFF \
}

#pragma pack()

///
/// CPU Data definitions
///
#define CPU_FVI_STRING              "Reference Code - CPU"
#define UCODE_FVI_STRING            "uCode Version"
#define TXT_FVI_STRING              "TXT ACM version"

typedef enum {
  CPU_RC_VER= 0,
  UCODE_VER,
  TXT_VER
} CPU_FVI_INDEX;

///
/// ME Data definitions
///
#define ME_FVI_STRING               "Reference Code - ME 11.0"
#define MEBX_FVI_STRING             "MEBx version"
#define ME_FW_FVI_STRING            "ME Firmware Version"
#define ME_FW_CONSUMER_SKU_STRING   "Consumer SKU"
#define ME_FW_CORPORATE_SKU_STRING  "Corporate SKU"

typedef enum {
  EnumMeRc = 0, ///< ME Reference Code Version
  EnumMebx,     ///< MEBx Version
  EnumMeFw      ///< ME FW Version
} ME_FVI_INDEX;

///
/// PCH Data definitions
///
#define PCH_FVI_STRING              "Reference Code - EHL PCH"
#define PCH_CRID_STATUS_STRING      "PCH-CRID Status"
#define PCH_CRID_ORIGINAL_VALUE     "PCH-CRID Original Value"
#define PCH_CRID_NEW_VALUE          "PCH-CRID New Value"
#define PCH_CRID_ENABLED            "Enabled "
#define PCH_CRID_DISABLED           "Disabled"
#define ICL_PCH_LP_AX_HSIO_STRING   "EHL PCH LP Ax Hsio Version"
#define RAID_FVI_STRING             "OPROM - RST - RAID"
#define RST_DRIVER_NAME1            L"Intel RST"
#define RST_DRIVER_NAME2            L"Intel(R) RST"

#define FVI_PCH_ICL_LP_AX_HSIO_VERSION \
  { \
    ICL_PCH_LP_HSIO_VER_AX, 0, 0, 0 \
  }

typedef enum {
  RC_VER        = 0,
  PCH_CRID_STATUS,
  PCH_CRID_ORIGINAL,
  PCH_CRID_NEW,
  RAID_VER,
  HSIO_CNLPCHHAX_VER,
  HSIO_CNLPCHLPAX_VER
} PCH_FVI_INDEX;

///
/// SA Data definitions
///
#define SA_FVI_STRING               "Reference Code - SA - System Agent"
#define MEM_FVI_STRING              "Reference Code - MRC"
#define PCIE_FVI_STRING             "SA - PCIe Version"
#define SA_CRID_STATUS              "SA-CRID Status"
#define SA_CRID_ORIGINAL_VALUE      "SA-CRID Original Value"
#define SA_CRID_NEW_VALUE           "SA-CRID New Value"
#define SA_CRID_ENABLED             "Enabled "
#define SA_CRID_DISABLED            "Disabled"
#define VBIOS_FVI_STRING            "OPROM - VBIOS"

#define CRID_DATA                   0x69
#define CRID_LOCK                   0x17

typedef enum {
  SA_RC_VER = 0,
  MEM_RC_VER,
  PCIE_VER,
  CRID_STATUS,
  CRID_ORIGINAL,
  CRID_NEW,
  VBIOS_VER
} SA_FVI_INDEX;

///
/// Function definitions
///
/**
  Initialize all Smbios FVI OEM Type Data Hob
**/
VOID
EFIAPI
BuildFviInfoHob (
  VOID
  );

/**
  Update All Smbios FVI OEM Type Data

  @param  SmbiosOemType        - SMBIOS OEM Type

  @retval EFI_UNSUPPORTED      - Could not locate SMBIOS protocol
  @retval EFI_SUCCESS          - Successfully update FVI data
**/
EFI_STATUS
EFIAPI
UpdateFviInfo (
  IN UINT8           SmbiosOemType
  );

#endif
