/** @file
  This file describes the contents of the Reset Shutdown Communication Interface Table (RSCI).

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _RSCI_H
#define _RSCI_H

//
// Statements that include other files
//
#include <IndustryStandard/Acpi62.h>


//
// Definitions
//
#define EFI_ACPI_OEM_RSCI_REVISION                      0x00000002
#define EFI_ACPI_RSCI_REVISION                          1
#define EFI_ACPI_RESET_SHUTDOWN_COMMUNICATION_INTERFACE_SIGNATURE  SIGNATURE_32('R', 'S', 'C', 'I')
#ifndef EFI_ACPI_OEM_ID
#define EFI_ACPI_OEM_ID                                 'I','N','T','E','L',' '    // 6 Bytes long
#endif
#define EFI_ACPI_RSCI_OEM_TABLE_ID                      SIGNATURE_64 ('B','O','O','T','S','R','C',' ') // OEM table id 8 bytes long
//
// RSCI structure
//
//
// Ensure proper structure formats
//

#pragma pack(1)

typedef enum {
 FBR_NONE = 0,
 FBR_WATCHDOG_COUNTER_EXCEEDED,
 FBR_NO_MATCHING_OS,
 FBR_INVALID_OSNIB_CHECKSUM,
} FALL_BACK_POLICY_REASON;

typedef struct {
  UINT8                       FallbackPolicyReason;
  UINT8                       FastbootCombo;
  UINT8                       Reserved[2];
} EFI_ACPI_RSCI_INDICATORS;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER Header;
  UINT8                       WakeSrc;
  UINT8                       Resets;
  UINT8                       ResetType;
  UINT8                       ShuntdownSrc;
  EFI_ACPI_RSCI_INDICATORS    Indicators;
  UINT32                      ResetExtraInfo;
} EFI_ACPI_RESET_SHUTDOWN_COMMUNICATION_INTERFACE;



#pragma pack()

//
// Android Wake Sources for S4/S5
//
typedef enum {
 WAKE_NOT_APPLICABLE = 0,
 WAKE_BATTERY_INSERTED, // Not supported in EHL
 WAKE_USB_CHARGER_INSERTED, // Not supported in EHL
 WAKE_ACDC_CHARGER_INSERTED, // Not supported in EHL
 WAKE_POWER_BUTTON_PRESSED,
 WAKE_RTC_TIMER,
 WAKE_BATTERY_REACHED_IA_THRESHOLD // Not supported in EHL
} ANDROID_WAKE_SOURCE;

//
// Android Reset Sources
//
typedef enum {
  RESET_NOT_APPLICABLE = 0,
  RESET_OS_INITIATED,
  RESET_FORCED,
  RESET_FW_UPDATE,
  RESET_KERNEL_WATCHDOG,
  RESET_SECURITY_WATCHDOG, // Not supported in EHL
  RESET_SECURITY_INITIATED, // Not supported in EHL
  RESET_PMC_WATCHDOG, // Not supported in EHL
  RESET_EC_WATCHDOG, // Not supported in EHL
  RESET_PLATFORM_WATCHDOG,
  RESET_SHORT_POWER_LOSS = 11 // Not supported in EHL
} ANDROID_RESET_SOURCE;

typedef enum {
  NOT_APPLICABLE_RESET = 0,
  WARM_RESET = 1,
  COLD_RESET = 2,
  GLOBAL_RESET = 7,
} ANDROID_RESET_TYPE;

//
// Android Shutdown sources
//
typedef enum {
  SHTDWN_NOT_APPLICABLE = 0,
  SHTDWN_POWER_BUTTON_OVERRIDE,
  SHTDWN_BATTERY_REMOVAL,
  SHTDWN_VCRIT,
  SHTDWN_THERMTRIP,
  SHTDWN_PMICTEMP,
  SHTDWN_SYSTEMP,
  SHTDWN_BATTEMP,
  SHTDWN_SYSUVP,
  SHTDWN_SYSOVP,
  SHTDWN_SECURITY_WATCHDOG,
  SHTDWN_SECURITY_INITIATED,
  SHTDWN_PMC_WATCHDOG,
  SHTDWN_EC_WATCHDOG,
  SHTDWN_PLATFORM_WATCHDOG,
  SHTDWN_KERNEL_WATCHDOG
} ANDROID_SHUTDOWN_SOURCE;

#define EFI_OS_INDICATIONS_OS_INITIATED_RESET 0x00000040
#endif
