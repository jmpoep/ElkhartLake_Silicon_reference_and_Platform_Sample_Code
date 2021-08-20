/** @file
  Declaration of Intel Connectivity Variables Structures and guids for WLAN, BT and WIGIG.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  @par Specification Reference: 559910_Intel_Connectivity_Platforms_BIOS_Guidelines_Rev4_7_Internal.docx
**/

#ifndef __CNV_VARIABLES_H__
#define __CNV_VARIABLES_H__

//
// Statements that include other header files
//
#include <Base.h>
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

// This is a variable GUID where all Intel CNV regulatory, thermal, diversity and general definitions are stored for WLAN
#define UEFI_INTEL_CNV_WLAN_VARIABLES_GUID \
  { \
    0x92daaf2f, 0xc02b, 0x455b, { 0xb2, 0xec, 0xf5, 0xa3, 0x59, 0x4f, 0x4a, 0xea } \
  }

// This is a variable GUID where all Intel CNV regulatory, thermal, diversity and general definitions are stored for BT
#define UEFI_INTEL_CNV_BT_VARIABLES_GUID \
  { \
    0x42780dd5, 0x9a7d, 0x404c, { 0x80, 0xe4, 0x7f, 0x70, 0x94, 0x36, 0x03, 0x94 } \
  }

// This is a variable GUID where all Intel CNV regulatory, thermal, diversity and general definitions are stored for WIGIG
#define UEFI_INTEL_CNV_WIGIG_VARIABLES_GUID \
  { \
    0xc07a1f7c, 0xfa13, 0x4fcb, { 0x92, 0xca, 0x3b, 0x32, 0xbc, 0x09, 0x2e, 0x13 } \
  }

#pragma pack(push, 1)
//
// CNV Header Definition
//
typedef struct {
  UINT8  Revision;
} UEFI_CNV_VAR_HEADER;

//
// Definition for Static Power Limit Configuration (SPLC)
//
#define UEFI_CNV_SPLC_VAR_NAME   L"SPLC"
#define UEFI_CNV_SPLC_REVISION   0

typedef struct {
  UEFI_CNV_VAR_HEADER  Header;                // Revision
  UINT32               DefaultPowerLimit;     // mW
  UINT32               DefaultTimeWindow;     // ms
} UEFI_CNV_VAR_SPLC;

//
// Definition for Wireless Antenna Diversity (WAND)
//
#define UEFI_CNV_WAND_VAR_NAME              L"WAND"
#define UEFI_CNV_WAND_REVISION              0
#define UEFI_CNV_WIRELESS_ANTENNA_COUNT     2
#define UEFI_CNV_ANTENNA_A                  0
#define UEFI_CNV_ANTENNA_B                  1

typedef struct {
  UINT8  AntennaId;            // 0:Antenna A, 1:Antenna B
  UINT8  TxRxDelay;            // nSecDelay, possible values 1-100 in 0.1ns resolution (0.1 to 10ns).
  UINT8  TxRxCableLength;      // cm ; possible values 1-100cm in 1cm resolution.
} ANTENNA_DIVERSITY;

typedef struct {
  UEFI_CNV_VAR_HEADER  Header; // Revision
  ANTENNA_DIVERSITY    AntDiversity[UEFI_CNV_WIRELESS_ANTENNA_COUNT];
} UEFI_CNV_VAR_WAND;

//
// Definition for Wireless Regulatory Domain Description (WRDD)
//
#define UEFI_CNV_WRDD_VAR_NAME              L"WRDD"
#define UEFI_CNV_WRDD_REVISION              0

typedef struct {
  UEFI_CNV_VAR_HEADER  Header;             // Revision
  UINT16               RegulatoryDomain;   // Country identifier as defined in ISO/IEC 3166-1 Alpha 2 code
} UEFI_CNV_VAR_WRDD;

//
// Definition for Wireless Regulatory Domain SAR (WRDS SAR)
//
#define UEFI_CNV_WRDS_VAR_NAME               L"WRDS"
#define UEFI_CNV_WRDS_REVISION               0
#define UEFI_CNV_WRDS_WIGIG_RFE_CH_COUNT     4

//
// SAR Tx Power Limits
//
typedef struct {
  UINT8  From2400;        // WiFi SAR Tx Power Limit for 2400 MHz
  UINT8  From5150To5350;  // WiFi SAR Tx Power Limit for 5150-5350 MHz
  UINT8  From5350To5470;  // WiFi SAR Tx Power Limit for 5350-5470 MHz
  UINT8  From5470To5725;  // WiFi SAR Tx Power Limit for 5470-5725 MHz
  UINT8  From5725To5950;  // WiFi SAR Tx Power Limit for 5725-5950 MHz
} TX_POWER_LIMITS;

//
// Below structure to be used for WRDS - WIGIG RFE
//
typedef struct {
  UEFI_CNV_VAR_HEADER  Header;                                     // Revision
  UINT8                Enable;                                     // Define the mode of RFE control to be used. 0:Tx power shall be mandated by device OTP RFE Class; 1:Tx power shall be the minimum between BIOS RFE table and OTP RFE Class
  UINT8                Channel[UEFI_CNV_WRDS_WIGIG_RFE_CH_COUNT];  // RFE WiGig Channel 1 to 4
} UEFI_CNV_VAR_WRDS_WIGIG_RFE;

//
// Below structure to be used for WRDS - WIFI SAR
//
typedef struct {
  TX_POWER_LIMITS      ChainATxPowerLimits; // Chain Function A
  TX_POWER_LIMITS      ChainBTxPowerLimits; // Chain Function B
} SAR_VALUES;

typedef struct {
  UEFI_CNV_VAR_HEADER  Header;              // Revision
  UINT8                Enable;              // Configures the source location of the WiFi SAR table to be used; 0:Device ignores BIOS configuration; 1:Device uses BIOS configuration
  SAR_VALUES           SarValues;           // SAR Values for Chain Function A and B
} UEFI_CNV_VAR_WRDS_WIFI_SAR;

//
// Definition for Bluetooth wireless Regulatory Domain SAR (BRDS)
//
#define UEFI_CNV_BRDS_VAR_NAME        L"BRDS"
#define UEFI_CNV_BRDS_REVISION        0
typedef struct {
  UEFI_CNV_VAR_HEADER  Header;              // Revision
  UINT8                Enable;              // Define the mode of SAR control to be used.0: Tx power shall be mandated by device NVM; 1: Tx power shall be the minimum between BIOS SAR table and BT Device NVM (either Module or Platform)
  UINT8                BrModulation;        // Bluetooth SAR BR Modulation
  UINT8                Edr2Modulation;      // Bluetooth SAR EDR2 Modulation
  UINT8                Edr3Modulation;      // Bluetooth SAR EDR3 Modulation
  UINT8                LeModulation;        // Bluetooth SAR LE Modulation
  UINT8                Le2MhzModulation;    // Bluetooth SAR LE 2Mhz Modulation
  UINT8                LeLrModulation;      // Bluetooth SAR LE LR Modulation
} UEFI_CNV_VAR_BRDS;

//
// Definition for Extended Wireless Regulatory Domain SAR (EWRD)
//
#define UEFI_CNV_EWRD_VAR_NAME                          L"EWRD"
#define UEFI_CNV_EWRD_REVISION                          0
#define UEFI_CNV_EWRD_WIFI_SAR_VALUES_EXT    3
typedef struct {
  UEFI_CNV_VAR_HEADER  Header;                                                      // Revision
  UINT8                WifiDynamicSarEnable;                                        // WiFi Dynamic SAR Enable/Disable
  UINT8                WifiDynamicSarRangeSets;                                     // WiFi SAR Number of Optional added SAR table sets to be used: 0 - Default OTP Table, 1 - Value as mandated in WRDS object, 2-4 - Extended values as mandated in this table
  SAR_VALUES           WifiDynamicSarValuesExt[UEFI_CNV_EWRD_WIFI_SAR_VALUES_EXT];  // Extended SAR Values
} UEFI_CNV_VAR_EWRD;

//
// Definition for Wireless Geo Delta Settings (WGDS)
//
#define UEFI_CNV_WGDS_VAR_NAME               L"WGDS"
#define UEFI_CNV_WGDS_REVISION               0
#define UEFI_CNV_WGDS_SAR_DELTA_GROUP        3 // 1 - FCC , 2 - EC Japan, 3 - ROW, 4-8 - Reserved
#define UEFI_CNV_WGDS_GROUP_1_FCC            0
#define UEFI_CNV_WGDS_GROUP_2_EC             1
#define UEFI_CNV_WGDS_GROUP_3_ROW            2

typedef struct {
  UINT8  MaxAllowed;  // 2400 and 5200 MHZ Max Allowed
  UINT8  ChainA;      // Chain A Offset
  UINT8  ChainB;      // Chain B Offset
} GEO_SAR_OFFSET;

typedef struct {
  GEO_SAR_OFFSET       GeoSarOffset2400Mhz;
  GEO_SAR_OFFSET       GeoSarOffset5200Mhz;
} GEO_SAR_DELTA;

typedef struct {
  UEFI_CNV_VAR_HEADER  Header;                                              // Revision
  GEO_SAR_DELTA        WifiSarPowerDelta[UEFI_CNV_WGDS_SAR_DELTA_GROUP];    // WiFi SAR Output Power Delta
} UEFI_CNV_VAR_WGDS;

//
// Definition for Antenna Weight Vectors Class Index (AWVC)
//
#define UEFI_CNV_AWVC_VAR_NAME               L"AWVC"
typedef struct {
  UINT32               ClassIndex;       // Platform Characteristics Reference ID
} UEFI_CNV_VAR_AWVC;

//
// Definition for Switched Antenna Diversity Selection (SADS)
//
#define UEFI_CNV_SADS_VAR_NAME               L"SADS"
#define UEFI_CNV_SADS_REVISION               0
typedef struct {
  UEFI_CNV_VAR_HEADER  Header;           // Revision
  UINT8                AntDiversitySel;  // 0:Antenna1, 1:Antenna2, 2:Diversity, 3:Diversity Antenna1, 4:Diversity Antenna2
} UEFI_CNV_VAR_SADS;

//
// Definition for General Purpose Configuration (GPC)
//
#define UEFI_CNV_GPC_VAR_NAME                 L"GPC"
#define UEFI_CNV_GPC_REVISION                 0
#define UEFI_CNV_GPC_TLV_MAX_DWORD_VALUES     1
#define UEFI_CNV_GPC_TLV_MAX_WIFI_BT_CORE     1

typedef struct {
  UINT32  Type;                                        // The type of configuration which is defined in the structure
  UINT32  Length;                                      // The length of the value
  UINT32  Value[UEFI_CNV_GPC_TLV_MAX_DWORD_VALUES];    // The value/data of the type
} TLV;

typedef struct {
  UEFI_CNV_VAR_HEADER  Header;                                  // Revision
  TLV                  Tlv[UEFI_CNV_GPC_TLV_MAX_WIFI_BT_CORE];  // GPC TLV for WiFi / BT Core
} UEFI_CNV_VAR_GPC;
#pragma pack(pop)

#endif
