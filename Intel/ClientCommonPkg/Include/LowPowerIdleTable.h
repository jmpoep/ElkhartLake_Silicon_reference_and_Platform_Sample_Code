/** @file

This file defines the Low Power Idle Table definition, defined by
Intel IA-PC LPIT (Low Power Idle Table) Specification draft.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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

#ifndef _LOW_POWER_IDLE_TABLE_H_
#define _LOW_POWER_IDLE_TABLE_H_

//
// LPIT Definitions
//

#define EFI_ACPI_LOW_POWER_IDLE_TABLE_REVISION 0x1

//
// Ensure proper structure formats
//
#pragma pack(1)

typedef union _EFI_ACPI_LPI_STATE_FLAGS {
  struct {
    UINT32 Disabled           :1;
    UINT32 CounterUnavailable :1;
    UINT32 Reserved           :30;
  } Bits;
  UINT32 AsUlong;
} EFI_ACPI_LPI_STATE_FLAGS, *PEFI_ACPI_LPI_STATE_FLAGS;

// Only Mwait LPI here:

typedef struct _EFI_ACPI_MWAIT_LPI_STATE_DESCRIPTOR {
  UINT32 Type;        // offset: 0
  UINT32 Length;      // offset: 4
  UINT16 UniqueId;    // offset: 8
  UINT8 Reserved[2]; // offset: 10
  EFI_ACPI_LPI_STATE_FLAGS Flags; // offset: 12
  EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE EntryTrigger; // offset: 16
  UINT32 Residency;  // offset: 28
  UINT32 Latency; // offset: 32
  EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE ResidencyCounter; // offset: 36
  UINT64 ResidencyCounterFrequency; //offset: 48
} EFI_ACPI_MWAIT_LPI_STATE_DESCRIPTOR;

#pragma pack()

#endif //_LOW_POWER_IDLE_TABLE_H_
