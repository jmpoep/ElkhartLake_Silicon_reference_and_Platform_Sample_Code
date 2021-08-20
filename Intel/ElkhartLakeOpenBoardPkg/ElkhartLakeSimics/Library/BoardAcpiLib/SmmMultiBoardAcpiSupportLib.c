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
#include <Library/BoardAcpiEnableLib.h>
#include <Library/MultiBoardAcpiSupportLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#include <ElkhartLakeId.h>

EFI_STATUS
EFIAPI
ElkhartLakeSimicsBoardEnableAcpi (
  IN BOOLEAN  EnableSci
  );

EFI_STATUS
EFIAPI
ElkhartLakeSimicsBoardDisableAcpi (
  IN BOOLEAN  DisableSci
  );

EFI_STATUS
EFIAPI
SiliconEnableAcpi (
  IN BOOLEAN  EnableSci
  );

EFI_STATUS
EFIAPI
SiliconDisableAcpi (
  IN BOOLEAN  DisableSci
  );

EFI_STATUS
EFIAPI
ElkhartLakeSimicsMultiBoardEnableAcpi (
  IN BOOLEAN  EnableSci
  )
{
  SiliconEnableAcpi (EnableSci);
  return ElkhartLakeSimicsBoardEnableAcpi (EnableSci);
}

EFI_STATUS
EFIAPI
ElkhartLakeSimicsMultiBoardDisableAcpi (
  IN BOOLEAN  DisableSci
  )
{
  SiliconDisableAcpi (DisableSci);
  return ElkhartLakeSimicsBoardDisableAcpi (DisableSci);
}

BOARD_ACPI_ENABLE_FUNC  mElkhartLakeSimicsBoardAcpiEnableFunc = {
  ElkhartLakeSimicsMultiBoardEnableAcpi,
  ElkhartLakeSimicsMultiBoardDisableAcpi,
};

EFI_STATUS
EFIAPI
SmmElkhartLakeSimicsMultiBoardAcpiSupportLibConstructor (
  VOID
  )
{
  if (LibPcdGetSku () == BoardIdElkhartLakeSimics) {
    return RegisterBoardAcpiEnableFunc (&mElkhartLakeSimicsBoardAcpiEnableFunc);
  }
  return EFI_SUCCESS;
}

