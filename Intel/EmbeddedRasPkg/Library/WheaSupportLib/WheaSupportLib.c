/** @file
  Implementation of whea support library on top of whea support protocol.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/RasGlobalDataLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/WheaSupportLib.h>
#include <Protocol/AcpiTable.h>


#define EFI_ACPI_CREATOR_ID                 0x4C544E49  // "INTL"
#define EFI_ACPI_CREATOR_REVISION           0x00000001
#define EFI_WHEA_OEM_REVISION               0x0001;

//
// Maximum buffer size for WHEA ACPI tables
//
#define MAX_EINJ_SIZE               0x2000
BOOLEAN  EINJTableInstalled = FALSE;
// Global variable to cache pointer to SMM Whea support protocol.
//
EFI_ACPI_TABLE_PROTOCOL         *mAcpiTbl = NULL;

VOID
EFIAPI
UpdateAcpiTableIds (
  EFI_ACPI_DESCRIPTION_HEADER *TableHeader
  )
{
  UINT64  TempOemTableId;

  //
  // Update the OEMID, Creator ID, and Creator revision.
  //
  *(UINT32 *) (TableHeader->OemId) = 'I' + ('N' << 8) + ('T' << 16) + ('E' << 24);
  *(UINT16 *) (TableHeader->OemId + 4) = 'L' + (' ' << 8);

  //
  // Update the OEMID and OEM Table ID.
  //
  TempOemTableId = PcdGet64 (PcdAcpiDefaultOemTableId);

  CopyMem (TableHeader->OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (TableHeader->OemId));
  CopyMem (&TableHeader->OemTableId, &TempOemTableId, sizeof (TableHeader->OemTableId));

  TableHeader->CreatorId = EFI_ACPI_CREATOR_ID;
  TableHeader->CreatorRevision = EFI_ACPI_CREATOR_REVISION;

  //
  // Update OEM revision and OEM TABLE ID based on the platform/SKU
  //
  TableHeader->OemRevision = EFI_WHEA_OEM_REVISION;
}


VOID
EFIAPI
InstallAcpiWheaTables (
  IN EFI_ACPI_DESCRIPTION_HEADER  *ACPITableHeader
  )
{
  EFI_STATUS                      Status;
  UINTN                           TableKey;

  DEBUG((DEBUG_INFO, "[WHEAINIT] start to install WHEA ACPI tables \n"));

  TableKey = 0;
  Status = mAcpiTbl->InstallAcpiTable (mAcpiTbl, ACPITableHeader, ACPITableHeader->Length, &TableKey);

  DEBUG((DEBUG_INFO, "[WHEAINIT] install WHEA ACPI tables status:%r \n", Status));
}


/**
  The constructor function caches the pointer to WHEA support protocol.

  The constructor function locates SMM WEHA support  protocol from protocol database.
  It will ASSERT() if that operation fails and it will always return EFI_SUCCESS.

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
InitializeWheaSupportLib (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
{
  EFI_STATUS                      Status;
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, &mAcpiTbl);

  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "[WHEAINIT] Fail to locate gEfiAcpiTableProtocolGuid: %r \n", Status));
  }

  return EFI_SUCCESS;
}
/**
  This routine add EINJ error injection instruction entry. And it can install EINJ table.
  EINJ table only can install once.


  @param [in]  InjectionEntry    - pointer to EINJ error injection entry.
  @param [in]  InstallTableFlag  - TRUE --> Install EINJ table; FALSE --> don't install.

  @retval  VOID
**/
VOID
EFIAPI
AddEinjActionItem (
  IN   EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY       *InjectionEntry,
  IN   BOOLEAN                                             InstallTableFlag
  )
{
  EFI_ACPI_6_0_ERROR_INJECTION_TABLE_HEADER             *EINJHeader;
  BOOLEAN                                               NewAllocation;

  EINJHeader = GetRasGlobalData (L"WHEAEinjData", MAX_EINJ_SIZE, &NewAllocation);

  if (EINJHeader == NULL) {
    DEBUG ((DEBUG_INFO, "[WHEAEINJ]ERROR: GetRasGlobalData returned NULL pointer\n"));
    ASSERT (FALSE);
    return;
  }

  if (NewAllocation) {
    EINJHeader->Header.Signature = EFI_ACPI_6_0_ERROR_INJECTION_TABLE_SIGNATURE;
    EINJHeader->Header.Length = sizeof (EFI_ACPI_6_0_ERROR_INJECTION_TABLE_HEADER);
    EINJHeader->Header.Revision = EFI_ACPI_6_0_ERROR_INJECTION_TABLE_REVISION;
    UpdateAcpiTableIds (&EINJHeader->Header);

    EINJHeader->InjectionHeaderSize = sizeof (EFI_ACPI_6_0_ERROR_INJECTION_TABLE_HEADER);
    EINJHeader->InjectionFlags = 0;
    EINJHeader->InjectionEntryCount = 0;
  }

  if (EINJTableInstalled) {
    return;
  }

  CopyMem ((VOID *) (UINTN) ((UINT8 *) EINJHeader + EINJHeader->Header.Length), (VOID *) InjectionEntry, sizeof (EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY));
  EINJHeader->Header.Length += sizeof (EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY);
  EINJHeader->InjectionEntryCount ++;
  DEBUG((DEBUG_INFO, "[WHEAEINJ] table length:%x  entry count:%d \n", EINJHeader->Header.Length, EINJHeader->InjectionEntryCount));

  if (InstallTableFlag) {
    EINJTableInstalled = TRUE;
    InstallAcpiWheaTables (&EINJHeader->Header);
  }

}
