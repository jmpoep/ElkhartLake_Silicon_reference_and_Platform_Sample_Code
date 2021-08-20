/** @file
  Simple Boot Flag.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/
#ifndef __SIMPLE_BOOT_FLAG_INTERNAL_H_
#define __SIMPLE_BOOT_FLAG_INTERNAL_H_

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Protocol/AcpiTable.h>
#include <Guid/GlobalVariable.h>
#include <SimpleBootFlag.h>
#include <IndustryStandard/Acpi.h>

//
// ACPI table information used to initialize tables.
//
#define EFI_ACPI_OEM_ID           "INTEL"
#define EFI_ACPI_OEM_TABLE_ID     0x2020204F4E414954  // "TIANO   "
#define EFI_ACPI_OEM_REVISION     0x00000002
#define EFI_ACPI_CREATOR_ID       0x5446534D          // TBD "MSFT"
#define EFI_ACPI_CREATOR_REVISION 0x01000013          // TBD

//
// Ensure proper structure formats
//
#pragma pack(1)
//
// Boot Table header definition.
//
typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER             Header;
  UINT8                                   CmosIndex;
  UINT8                                   Reserved[3];
} EFI_ACPI_BOOT_TABLE;
#pragma pack()

#endif
