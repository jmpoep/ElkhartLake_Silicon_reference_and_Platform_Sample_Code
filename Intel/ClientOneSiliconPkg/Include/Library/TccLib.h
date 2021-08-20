/** @file
  Header file for TCC Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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
#ifndef _TCC_LIB_H_
#define _TCC_LIB_H_

#include <TccConfigSubRegion.h>

#define EFI_ACPI_PTCT_SIGNATURE           SIGNATURE_32('P', 'T', 'C', 'T')  // 'PTCT'
#define EFI_ACPI_PTCT_TABLE_REVISION      0x1
#define EFI_ACPI_OEM_ID                   "INTEL "  // OEMID 6 bytes long
#define EFI_ACPI_OEM_TABLE_ID             SIGNATURE_64('E','D','K','2',' ',' ',' ',' ') // OEM table id 8 bytes long
#define EFI_ACPI_OEM_REVISION             0x00000005
#define EFI_ACPI_CREATOR_ID               SIGNATURE_32('I','N','T','L')
#define EFI_ACPI_CREATOR_REVISION         0x0100000D
#define EFI_ACPI_PTCT_FW_VENDOR_SIZE      16
#define EFI_ACPI_PTCT_FW_VENDOR           "INTEL           "   // 16 bytes long
#define MAX_NUM_LLC_QOS_RECORDS           5

//
// PTCT Structure
//

#pragma pack(1)

typedef struct {
  UINT8                             Type;
  UINT8                             Length;
  UINT8                             Flags;
  UINT8                             Reserved;
  UINT32                            ApicId;
  UINT64                            RegionBase;
  UINT64                            RegionSize;
} LLC_QOS_RECORD;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER       Header;
  LLC_QOS_RECORD                    RecordStructures[MAX_NUM_LLC_QOS_RECORDS];
} EFI_ACPI_PTCT_TABLE;

#pragma pack()

/**
  Check whether SKU supports Real-Time features

  @retval TRUE                    Real-Time SKU
  @retval FALSE                   Non-Real-Time SKU
**/
BOOLEAN
IsRtSku (
  VOID
  );

/**
  Get the Base Address of Psuedo-Lockable region for LLC QoS.

  @param[in]   Index          The index of the region
**/
UINTN
GetLlcQosRegionAddress (
  UINT8 Index
  );

/**
  Get the Size of Psuedo-Lockable region for LLC QoS.

  @param[in]   Index          The index of the region
**/
UINTN
GetLlcQosRegionSize (
  UINT8 Index
  );

/**
  Get the optimal region for psuedo-locking LLC to improve QoS.
  Base address and size identified by modeling data of each platform.
  More than one region may be psuedo-lockable.

  @param[in]   Index          The index of the psuedo-lockable region
  @param[out]  LlcQosAddress  Base address of locking region
  @param[out]  LlcQosSize     Size of locking region
**/
VOID
GetLlcQosRegion (
  IN  UINT8 Index,
  OUT UINTN *LlcQosAddress,
  OUT UINTN *LlcQosSize
  );

/**
  The number of LLC QoS records to be installed.

  @return The number of LLC QoS records to be installed.
**/
UINT8
GetNumLlcQosRecords (
  VOID
  );

EFI_STATUS
TccTuning (
  UINT8   Phase,
  VOID   *RtFileBuffer,
  UINTN   FileSize
  );

VOID
TuneMmio32Register (
  TCC_REGISTER* RtData
  );

VOID
TuneMmio64Register (
  TCC_REGISTER* RtData
  );

VOID
TuneMsrRegister (
  TCC_REGISTER* RtData
  );

VOID
TuneIosfSbRegister (
  TCC_REGISTER* RtData
  );

VOID
TuneMailboxRegister (
  TCC_REGISTER* RtData
  );

#endif // _TCC_LIB_H_
