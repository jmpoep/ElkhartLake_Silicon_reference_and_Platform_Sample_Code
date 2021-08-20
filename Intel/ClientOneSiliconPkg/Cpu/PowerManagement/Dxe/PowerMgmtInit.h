/** @file
  This header file contains processors power management definitions.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _POWER_MANAGEMENT_H_
#define _POWER_MANAGEMENT_H_

#include <Uefi.h>
#include <IndustryStandard/Acpi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/MpService.h>
#include <Protocol/FirmwareVolume2.h>
#include <CpuAccess.h>
#include <Protocol/CpuNvsArea.h>
#include <Library/CpuPlatformLib.h>
#include <PowerMgmtNvsStruct.h>
#include <Library/AslUpdateLib.h>
#include <Library/PciSegmentLib.h>
#include <CpuInitDataHob.h>
#include <Library/TimerLib.h>
#include <Library/CpuMailboxLib.h>

#define FADT_C3_LATENCY                 57
#define FADT_C3_LATENCY_DISABLED        1001

#define NATIVE_PSTATE_LATENCY           10
#define PSTATE_BM_LATENCY               10

#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(&(((TYPE *) 0)->Field)))

//
// Global variables
//
extern EFI_GUID gCpuAcpiTableStorageGuid;

extern CPU_NVS_AREA_PROTOCOL *gCpuNvsAreaProtocol; ///< CPU Nvs Protocol

//
// Globals to support updating ACPI Tables
//
extern EFI_ACPI_TABLE_PROTOCOL     *mAcpiTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpu0IstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mApIstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpu0CstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mApCstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpuSsdtTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpu0TstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mApTstTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mItbmTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mItbmSciTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpu0HwpTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mApHwpTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mHwpLvtTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mCpu0PsdTable;
extern EFI_ACPI_DESCRIPTION_HEADER *mApPsdTable;

extern CPU_INIT_DATA_HOB   *mCpuInitDataHob;
extern CPU_CONFIG_DATA     *mCpuConfigData;
///
/// ASL SSDT structure layout
///
#pragma pack(1)
typedef struct {
  UINT8  NameOp;          ///< First opcode is a NameOp.
  UINT32 NameString;      ///< 'TDSS'   ; Name of object.
  UINT8  PackageOp;       ///< db 12h   ; Sixth OpCode is PackageOp.
  UINT16 PackageLen;      ///< dw 0h    ; Seventh/Eighth OpCode is PackageLength.
  UINT8  PackageEntryNum; ///< db 0Ch   ; Ninth OpCode is number of package entries.
  UINT8  StringPrefix1;   ///< 0Dh
  UINT64 Cpu0IstStr;      ///< 00h
  UINT8  StringNull1;     ///< 00h
  UINT8  DwordPrefix1a;   ///< 0Ch
  UINT32 Cpu0IstAddr;     ///< 00h
  UINT8  DwordPrefix1b;   ///< 0Ch
  UINT32 Cpu0IstLen;      ///< 00h
  UINT8  StringPrefix2;   ///< 0Dh
  UINT64 Cpu1IstStr;      ///< 00h
  UINT8  StringNull2;     ///< 00h
  UINT8  DwordPrefix2a;   ///< 0Ch
  UINT32 ApIstAddr;       ///< 00h
  UINT8  DwordPrefix2b;   ///< 0Ch
  UINT32 ApIstLen;        ///< 00h
  UINT8  StringPrefix3;   ///< 0Dh
  UINT64 Cpu0CstStr;      ///< 00h
  UINT8  StringNull3;     ///< 00h
  UINT8  DwordPrefix3a;   ///< 0Ch
  UINT32 Cpu0CstAddr;     ///< 00h
  UINT8  DwordPrefix3b;   ///< 0Ch
  UINT32 Cpu0CstLen;      ///< 00h
  UINT8  StringPrefix4;   ///< 0Dh
  UINT64 ApCstStr;        ///< 00h
  UINT8  StringNull4;     ///< 00h
  UINT8  DwordPrefix4a;   ///< 0Ch
  UINT32 ApCstAddr;       ///< 00h
  UINT8  DwordPrefix4b;   ///< 0Ch
  UINT32 ApCstLen;        ///< 00h
  UINT8  StringPrefix5;   ///< 0Dh
  UINT64 Cpu0HwpStr;      ///< 00h
  UINT8  StringNull5;     ///< 00h
  UINT8  DwordPrefix5a;   ///< 0Ch
  UINT32 Cpu0HwpAddr;     ///< 00h
  UINT8  DwordPrefix5b;   ///< 0Ch
  UINT32 Cpu0HwpLen;      ///< 00h
  UINT8  StringPrefix6;   ///< 0Dh
  UINT64 ApHwpStr;        ///< 00h
  UINT8  StringNull6;     ///< 00h
  UINT8  DwordPrefix6a;   ///< 0Ch
  UINT32 ApHwpAddr;       ///< 00h
  UINT8  DwordPrefix6b;   ///< 0Ch
  UINT32 ApHwpLen;        ///< 00h
  UINT8  StringPrefix7;   ///< 0Dh
  UINT64 HwpLvtStr;       ///< 00h
  UINT8  StringNull7;     ///< 00h
  UINT8  DwordPrefix7a;   ///< 0Ch
  UINT32 HwpLvtAddr;      ///< 00h
  UINT8  DwordPrefix7b;   ///< 0Ch
  UINT32 HwpLvtLen;       ///< 00h
  UINT8  StringPrefix8;   ///< 0Dh
  UINT64 Cpu0PsdStr;      ///< 00h
  UINT8  StringNull8;     ///< 00h
  UINT8  DwordPrefix8a;   ///< 0Ch
  UINT32 Cpu0PsdAddr;     ///< 00h
  UINT8  DwordPrefix8b;   ///< 0Ch
  UINT32 Cpu0PsdLen;      ///< 00h
  UINT8  StringPrefix9;   ///< 0Dh
  UINT64 Cpu1PsdStr;      ///< 00h
  UINT8  StringNull9;     ///< 00h
  UINT8  DwordPrefix9a;   ///< 0Ch
  UINT32 ApPsdAddr;       ///< 00h
  UINT8  DwordPrefix9b;   ///< 0Ch
  UINT32 ApPsdLen;        ///< 00h
} SSDT_LAYOUT;
#pragma pack()

//
// FVID Table Information
// Default FVID table
// One header field plus states
//
extern UINT16     mNumberOfStates;
extern FVID_TABLE *mFvidPointer;

//
// Function prototypes
//

/**
  Configures the Interrupt Redirection Mode Selection for Logical Interrupts.
**/
VOID
InitPpmIrmConfiguration (
  VOID
  );

/**
  This will perform Miscellaneous Power Management related programming.
**/
VOID
InitMiscFeatures (
  VOID
  );

/**
  Configures PowerLimits and Config TDP values
**/
VOID
CtdpS3Save (
  VOID
  );

/**
  Patch the native _PSS package with the EIST values
  Uses ratio/VID values from the FVID table to fix up the control values in the _PSS.

  (1) Find _PSS package:
    (1.1) Find the _PR_CPU0 scope.
    (1.2) Save a pointer to the package length.
    (1.3) Find the _PSS AML name object.
  (2) Resize the _PSS package.
  (3) Fix up the _PSS package entries
    (3.1) Check Turbo mode support.
    (3.2) Check Dynamic FSB support.
  (4) Fix up the Processor block and \_PR_CPU0 Scope length.
  (5) Update SSDT Header with new length.

  @retval EFI_SUCCESS
  @retval EFI_NOT_FOUND - If _PR_.CPU0 scope is not foud in the ACPI tables
**/
EFI_STATUS
AcpiPatchPss (
  VOID
  );

/**
  Locate the CPU ACPI tables data file and read ACPI SSDT tables.
  Publish the appropriate SSDT based on current configuration and capabilities.

  @param[in] This                Pointer to the protocol instance

  @retval EFI_SUCCESS - on success
  @retval Appropiate failure code on error
**/
EFI_STATUS
InitCpuAcpiTable (
  VOID
  );

/**
  Initialize the power management support.
  This function will do boot time configuration:
    Install into SMRAM/SMM
    Detect HW capabilities and SW configuration
    Initialize HW and software state (primarily MSR and ACPI tables)
    Install SMI handlers for runtime interfacess

  @param[in] ImageHandle  Pointer to the loaded image protocol for this driver
  @param[in] SystemTable  Pointer to the EFI System Table

  @retval EFI_SUCCESS   The driver installed/initialized correctly.
  @retval Driver will ASSERT in debug builds on error. PPM functionality is considered critical for mobile systems.
**/
EFI_STATUS
EFIAPI
InitPowerManagement (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  );

/**
  Initializes the CPU power management global variable.
  This must be called prior to any of the functions being used.
**/
VOID
InitPowerManagementGlobalVariables (
  VOID
  );

/**
  Initialize the platform power management based on hardware capabilities
  and user configuration settings.

  This includes creating FVID table, updating ACPI tables,
  and updating processor and chipset hardware configuration.

  This should be called prior to any Px, Cx, Tx activity.

  @retval EFI_SUCCESS - on success
  @retval Appropiate failure code on error
**/
EFI_STATUS
InitPpmDxe (
  VOID
  );
#endif
