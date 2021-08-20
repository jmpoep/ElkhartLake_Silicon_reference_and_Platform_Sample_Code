/** @file
  Platform Hook Library instances

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Uefi.h>
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/BoardAcpiTableLib.h>
#include <Library/MultiBoardAcpiSupportLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#include <ElkhartLakeId.h>

EFI_STATUS
EFIAPI
ElkhartLakeSimicsBoardUpdateAcpiTable (
  IN OUT EFI_ACPI_COMMON_HEADER       *Table,
  IN OUT EFI_ACPI_TABLE_VERSION       *Version
  );

BOARD_ACPI_TABLE_FUNC  mElkhartLakeSimicsBoardAcpiTableFunc = {
  ElkhartLakeSimicsBoardUpdateAcpiTable
};

EFI_STATUS
EFIAPI
DxeElkhartLakeSimicsMultiBoardAcpiSupportLibConstructor (
  VOID
  )
{
  if (LibPcdGetSku () == BoardIdElkhartLakeSimics) {
    return RegisterBoardAcpiTableFunc (&mElkhartLakeSimicsBoardAcpiTableFunc);
  }
  return EFI_SUCCESS;
}

