/** @file
Header file for the CrashLog Support.

@copyright
INTEL CONFIDENTIAL
Copyright 2016 - 2019 Intel Corporation.

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

#ifndef _CRASH_LOG_DXE_H_
#define _CRASH_LOG_DXE_H_

//
// Statements that include other header files
//
#include <Uefi.h>
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuMailboxLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>
#include <SetupVariable.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PmcLib.h>
#include <Register/PmcRegs.h>
#include <CpuRegs.h>
#include <Library/HobLib.h>
#include <Guid/Cper.h>
#include <Library/TelemetryLib.h>
#include <Guid/CrashLog.h>

//
// Data definitions & structures
//
#define EFI_ACPI_CREATOR_ID                           SIGNATURE_32 ('I', 'N', 'T', 'L')
#define EFI_ACPI_CREATOR_REVISION                     0x00000001
#define EFI_ACPI_OEM_TABLE_ID                         SIGNATURE_64 ('E', 'D', 'K', '2', ' ', ' ', ' ', ' ') // OEM table id 8 bytes long
#define EFI_WHEA_OEM_REVISION                         0x0001;

#define CRASHLOG_SIZE_DEBUG_PURPOSE                   0x030  // It will help to verify the extracted binary from BERT by matching the binary content

#define EFI_2_7_FIRMWARE_ERROR_RECORD_REVISION        2  // Header Revision. Will be removed when Cper.h has defined it.

#pragma pack(1)

typedef struct {
  EFI_ACPI_6_1_GENERIC_ERROR_DATA_ENTRY_STRUCTURE   GenericErrorDataEntry;
  EFI_FIRMWARE_ERROR_DATA                           EfiFirmwareErrorData;
} FIRMWARE_GENERIC_ERROR;

//
// CRASHLOG_REASON
//
typedef union {
  struct {
    UINT32  CWReset    : 1;  // Cold/Warm reset
    UINT32  GReset     : 1;  // Global reset
    UINT32  Error      : 1;  // Error
    UINT32  MInit      : 1;  // Manually Initiated
    UINT32  Reserved   : 28;
  } Bits;
  UINT32  Uint32;
} CRASHLOG_REASON;

//
// CRASHLOG FIELD
//
typedef struct {
  UINT32            CrashLogVersion;
  CRASHLOG_REASON   CrashLogReason;
} CRASHLOG_FIELD;

#pragma pack()

/**
  Entry point of the CrashLog support driver.

  @param[in]  ImageHandle   EFI_HANDLE: A handle for the image that is initializing this driver
  @param[in]  SystemTable   EFI_SYSTEM_TABLE: A pointer to the EFI system table

  @retval  EFI_SUCCESS:              Driver initialized successfully
           EFI_LOAD_ERROR:           Failed to Initialize or has been loaded
           EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
EFIAPI
InstallCrashLogSupport (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

/**

  Update Platform & OEM ID's in Whea ACPI tables.

  @param[in]  TableHeader  BERT Table Header Pointer

**/
VOID
UpdateAcpiTableIds (
  EFI_ACPI_DESCRIPTION_HEADER     *TableHeader
  );

extern  EFI_GUID         gEfiFirmwareErrorSectionGuid;

#endif
