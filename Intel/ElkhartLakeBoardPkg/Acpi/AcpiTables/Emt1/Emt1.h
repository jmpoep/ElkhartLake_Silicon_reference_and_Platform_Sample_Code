/** @file
  This file describes the contents of the Energy Management Table (EMT).

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
#ifndef _EMT1_H_
#define _EMT1_H_

//
// Statements that include other files
//
#include <IndustryStandard/Acpi62.h>

#define EFI_ACPI_EMT1_REVISION     0x00000000
#define EFI_ACPI_OEM1_REVISION     0x00000001
#define EFI_ACPI_OEM_REVISION      0x00000005
#define EFI_ACPI_EMT1_SIGNATURE    SIGNATURE_32('E', 'M', '_', '1')
#define EFI_ACPI_OEM1_SIGNATURE    SIGNATURE_32('O', 'E', 'M', '1')

#define EFI_ACPI_EMT1_TABLE_ID     SIGNATURE_64('O','E','M','1',' ',' ',' ',' ') // OEM table id 8 bytes long
#define EFI_ACPI_OEM1_TABLE_ID     SIGNATURE_64('E','N','R','G','Y','M','G','T') // OEM table id 8 bytes long

#pragma pack(1)

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER Header;
  UINT8                       FixedOption0; /* Fixed Platform Options 0 */
  UINT8                       FixedOption1; /* Fixed Platform Options 1*/
  UINT8                       DBIInGpioNumber; /* DBIIN GPIO number */
  UINT8                       DBIOutGpioNumber; /* DBIOUT GPIO number */
  UINT8                       BatChpType; /* Identification or Authentication chip inside the battery */
  UINT16                      IaAppsRun; /* Minimum battery voltage required to boot the platform if FG has been reset */
  UINT8                       BatIdDBIBase; /* Resistance in KOhms for BSI used to indicate a digital battery */
  UINT8                       BatIdAnlgBase; /* Resistance in KOhms for BSI beyond which the battery is an analog battery */
  UINT8                       IaAppsCap; /* Minimum capacity at which to boot to Main OS */
  UINT16                      VBattFreqLmt; /* Battery Voltage up to which the CPU frequency should be limited */
  UINT8                       CapFreqIdx; /* Index into the Frequency table at which the CPU Frequency should be capped. */
  UINT8                       Rsvd1; /* Reserved */
  UINT8                       BatIdx; /* Battery Index: Charging profile to use in case of fixed battery */
  UINT8                       IaAppsToUse; /* Whether to use the IA_APPS_RUN (value = 1) or IA_APPS_CAP (value = 0) to while booting */
  UINT8                       TurboChrg; /* Maximum Turbo charge supported (in multiples of 100mA). Zero means no Turbo charge */
  UINT8                       Rsvd2[11]; /* Reserved */
} EFI_ACPI_EM_OEM_1_TABLE;

#pragma pack()


#endif
