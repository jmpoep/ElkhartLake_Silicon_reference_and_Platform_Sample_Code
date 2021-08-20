/** @file
  Install NHLT Table Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/AcpiTable.h>
#include <Pi/PiFirmwareFile.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include "DxeCreateNhltTableLib.h"
#include <Library/DxeServicesLib.h>
#include <Library/DxeInstallNhltTableLib.h>

/**
  Initialize and publish NHLT (Non-HDA Link Table), update NVS variables.

  @param[in]                *HdAudioDxeNhltConfig
  @param[in]                Pointer to NHLT table

  @retval EFI_SUCCESS            The function completed successfully
  @retval EFI_BAD_BUFFER_SIZE    Not enough resources to allocate NHLT
**/
EFI_STATUS
NhltCreateTableFromScratch (
  IN HDA_NHLT_CONFIG                        *NhltConfig
  )
{
  EFI_ACPI_DESCRIPTION_HEADER               *NhltTable;
  UINTN                                     AcpiTableKey;
  EFI_ACPI_TABLE_PROTOCOL                   *AcpiTableProtocol;
  UINT32                                    TableSize;
  EFI_STATUS                                Status;

  AcpiTableProtocol = NULL;
  NhltTable = NULL;
  AcpiTableKey = 0;

  DEBUG ((DEBUG_INFO, "NhltCreateTableFromScratch () - Start\n"));

  Status = NhltConstructor (NhltConfig, &NhltTable, &TableSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Nhlt not created correctly - Status = %r\n", Status));
    return Status;
  }

  // Header
  NhltTable->Signature = NHLT_ACPI_TABLE_SIGNATURE;
  NhltTable->Length = TableSize;
  NhltTable->Revision = 0x0;
  NhltTable->Checksum = 0x0;

  CopyMem (NhltTable->OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (NhltTable->OemId));
  NhltTable->OemTableId      = PcdGet64 (PcdAcpiDefaultOemTableId);
  NhltTable->OemRevision     = PcdGet32 (PcdAcpiDefaultOemRevision);
  NhltTable->CreatorId       = PcdGet32 (PcdAcpiDefaultCreatorId);
  NhltTable->CreatorRevision = PcdGet32 (PcdAcpiDefaultCreatorRevision);
  DEBUG ((DEBUG_INFO, "NhltAcpiHeaderConstructor(), NhltAcpiTable->Header.Length = %d B\n", NhltTable->Length));

  //
  // Locate ACPI support protocol
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTableProtocol);
  if ( EFI_ERROR (Status) || AcpiTableProtocol == NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // Publish NHLT ACPI table
  //
  Status = AcpiTableProtocol->InstallAcpiTable (
                                AcpiTableProtocol,
                                NhltTable,
                                NhltTable->Length,
                                &AcpiTableKey
                                );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "NhltCreateTableFromScratch () - End\n"));
  return EFI_SUCCESS;
}

/**
  Initialize and publish NHLT ACPI table.

  @retval   EFI_SUCCESS     The NHLT ACPI table is published successfully.
  @retval   EFI_NOT_FOUND   The NHLT ACPI table does not exist.
  @retval   EFI_LOAD_ERROR  The NHLT ACPI table has bad signature.
**/
EFI_STATUS
NhltLoadExternalTable (
  VOID
  )
{
  EFI_ACPI_DESCRIPTION_HEADER    *NhltTable;
  EFI_STATUS                     Status;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTableProtocol;
  UINTN                          TableKey;
  UINTN                          TableSize;

  NhltTable = NULL;
  TableSize = 0;

  DEBUG ((DEBUG_INFO, "NhltLoadExternalTable - Start()\n"));

  Status = GetSectionFromFv (
             &gHdaExternalNhltTableGuid,
             EFI_SECTION_RAW,
             0,
             (VOID **) &NhltTable,
             &TableSize
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "External NHLT table does not exist.\n"));
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO, "External NHLT table exist. Size = %d\n", TableSize));

  ///
  /// Check NHLT signature, would be 'N, 'H, 'L, 'T
  ///
  if (NhltTable->Signature != NHLT_ACPI_TABLE_SIGNATURE) {
    DEBUG ((DEBUG_ERROR, "External NHLT has bad signature.\n"));
    return EFI_LOAD_ERROR;
  }

  ///
  /// Set default ACPI Oem data
  ///
  CopyMem (NhltTable->OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (NhltTable->OemId));
  NhltTable->OemTableId      = PcdGet64 (PcdAcpiDefaultOemTableId);
  NhltTable->OemRevision     = PcdGet32 (PcdAcpiDefaultOemRevision);
  NhltTable->CreatorId       = PcdGet32 (PcdAcpiDefaultCreatorId);
  NhltTable->CreatorRevision = PcdGet32 (PcdAcpiDefaultCreatorRevision);

  //
  // Publish NHLT ACPI table
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTableProtocol);
  ASSERT_EFI_ERROR (Status);

  TableKey = 0;
  Status = AcpiTableProtocol->InstallAcpiTable (
                                AcpiTableProtocol,
                                NhltTable,
                                TableSize,
                                &TableKey
                                );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "NhltLoadExternalTable - End()\n"));
  return EFI_SUCCESS;
}

VOID
NhltPrintConfig (
  HDA_NHLT_CONFIG *NhltConfig
  )
{
  DEBUG ((DEBUG_INFO, " DSP Endpoint: DMIC  : %d\n", NhltConfig->DspEndpointDmic));
  DEBUG ((DEBUG_INFO, " DSP Endpoint: I2S   : %d\n", NhltConfig->DspEndpointI2s));
  DEBUG ((DEBUG_INFO, " DSP Endpoint: BT    : %d\n", NhltConfig->DspEndpointBluetooth));
  DEBUG ((DEBUG_INFO, " DSP External Table  : %d\n", NhltConfig->DspExternalTable));
}

/**
  Initialize and publish NHLT ACPI table.

  @retval   EFI_SUCCESS     The NHLT ACPI table is published successfully.
  @retval   EFI_NOT_FOUND   The NHLT ACPI table does not exist.
  @retval   EFI_LOAD_ERROR  The NHLT ACPI table has bad signature.
**/
EFI_STATUS
NhltPublishAcpiTable (
  HDA_NHLT_CONFIG *NhltConfig
  )
{
  EFI_STATUS                     Status;

  DEBUG ((DEBUG_INFO, "NhltPublishAcpiTable () - Start\n"));
  NhltPrintConfig (NhltConfig);

  if (NhltConfig->DspExternalTable) {
    Status = NhltLoadExternalTable ();
  } else {
    Status = NhltCreateTableFromScratch (NhltConfig);
  }

  DEBUG ((DEBUG_INFO, "NhltPublishAcpiTable () - End Status = %r\n", Status));
  return Status;
}

