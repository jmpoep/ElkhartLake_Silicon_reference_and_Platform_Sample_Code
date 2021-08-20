/** @file
  This is an implementation of the Advanced ACPI driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#ifndef _ACPI_PLATFORM_H_
#define _ACPI_PLATFORM_H_

//
// Statements that include other header files
//

#include <IndustryStandard/Acpi.h>
#include <Guid/EventGroup.h>
#include <Guid/GlobalVariable.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Protocol/CpuIo2.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/MpService.h>
#include <Register/Cpuid.h>
#include <CpuAccess.h>
#include <Protocol/PciIo.h>
#include <Library/PchCycleDecodingLib.h>

#include <IndustryStandard/HighPrecisionEventTimerTable.h>
#include <Library/DxeAcpiGnvsInitLib.h>

#include <Register/PchRegs.h>
#include <SaCommonDefinitions.h>

//
// Produced protocols
//
#include <Protocol/PlatformNvsArea.h>

#include <Platform.h>
#include <Library/AslUpdateLib.h>
#include <SetupVariable.h>
#include <Library/EcMiscLib.h>

#include <Acpi/AcpiTables/Fadt/Fadt6.1.h>

//
// ACPI table information used to initialize tables.
//

#define NAT_CONFIG_INDEX          0x2E
#define NAT_CONFIG_DATA           0x2F
#define WPCN381U_CONFIG_INDEX     0x2E
#define WPCN381U_CONFIG_DATA      0x2F
#define WPCN381U_CHIP_ID          0xF4
#define WDCP376_CHIP_ID           0xF1
#define Smsc1007_CONFIG_INDEX     0x164E
#define SMSC1000_CONFIG_INDEX     0x4E

#define MAX_CPU_NUM               16

#define KBC_DATA_PORT             0x60
#define KBC_CMD_STS_PORT          0x64

#define ENABLE_CMD                0xf4
#define WRITE_AUX_DEV             0xd4

#define PS2_ACK                   0xfa
#define PS2_RESEND                0xfe

#define KBC_INPB                  0x02
#define KBC_OUTB                  0x01
#define KBC_AUXB                  0x20

#define TIMEOUT                   50000
#define BAT_TIMEOUT               5000

#define IO_EXPANDER_DISABLED      0xFF

typedef struct {
  UINT8   ApicId;
  UINT32  Flags;
  UINT8   Package;
  UINT8   Die;
  UINT8   Core;
  UINT8   Thread;
} EFI_CPU_ID_ORDER_MAP;

typedef struct {
  UINT8   Package;
  UINT8   ApicId;
  UINT32  Flags;
} EFI_CPU_APIC_ID_REORDER_MAP;

typedef struct {
  UINT8   BspApicId;
  UINT8   TotalThreads;
  UINT8   PackageNo;
  UINT8   CoreNo;
  UINT8   LogicalThreadNo;
} EFI_CPU_PACKAGE_INFO;

//
// Function definitions
//
EFI_STATUS
LocateSupportProtocol (
  IN     EFI_GUID                      *Protocol,
  IN     EFI_GUID                      gEfiAcpiMultiTableStorageGuid,
  OUT    VOID                          **Instance,
  IN     BOOLEAN                       Type
  );

/**
  Entry point of the ACPI platform driver.

  @param[in] ImageHandle  A handle for the image that is initializing this driver
  @param[in] SystemTable  A pointer to the EFI system table

  @retval    EFI_SUCCESS  The driver installed without error.
  @retval    EFI_ABORTED  The driver encountered an error and could not complete
                          installation of the ACPI tables.
**/
EFI_STATUS
EFIAPI
InstallAcpiPlatform (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
SortCpuLocalApicInTable (
  IN  EFI_MP_SERVICES_PROTOCOL                   *MpService,
  IN  UINTN                                      NumberOfCPUs,
  IN  UINTN                                      NumberOfEnabledCPUs
  );

EFI_STATUS
AppendCpuMapTableEntry (
  IN  EFI_ACPI_1_0_PROCESSOR_LOCAL_APIC_STRUCTURE   *AcpiLocalApic,
  IN  UINTN                                      NumberOfCPUs,
  IN  UINTN                                      NumberOfEnabledCPUs,
  IN  UINT8                                      LocalApicCounter
  );

BOOLEAN
IsPs2MouseConnected (
  VOID
  );

#endif
