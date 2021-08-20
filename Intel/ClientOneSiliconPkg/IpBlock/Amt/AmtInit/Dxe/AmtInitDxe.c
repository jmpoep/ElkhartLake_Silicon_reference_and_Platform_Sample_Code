/** @file
  Amt Initialization Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include "AmtInitDxe.h"

/**
  Invoke a notification event to update ASF Table RMCP part

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context.

**/
VOID
EFIAPI
AsfTableRmcpOnReadyToBoot (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                          Status;
  EFI_ACPI_DESCRIPTION_HEADER         *AcpiAsfTable;
  UINTN                               Handle;
  EFI_ACPI_TABLE_PROTOCOL             *AcpiTable;
  EFI_ACPI_ASF_RECORD_HEADER          *AsfRecord;
  EFI_ACPI_ASF_RMCP                   *AsfRmcp;
  ALERT_STANDARD_FORMAT_PROTOCOL      *Asf;

  ///
  /// Locate ACPI Table Protocol
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);

  ///
  /// Initialize ASL manipulation library
  ///
  InitializeAslUpdateLib ();

  ///
  /// Locate the ASF Table
  ///
  AcpiAsfTable = NULL;
  Status = LocateAcpiTableBySignature (
             EFI_ACPI_ASF_DESCRIPTION_TABLE_SIGNATURE,
             &AcpiAsfTable,
             &Handle
             );
  if (EFI_ERROR (Status) || (AcpiAsfTable == NULL)) {
    return;
  }

  ///
  /// Locate the RMCP Table
  ///
  AsfRecord = (EFI_ACPI_ASF_RECORD_HEADER *)((UINT8 *)AcpiAsfTable + sizeof (EFI_ACPI_DESCRIPTION_HEADER));
  do {
    if ((AsfRecord->Type & ASF_RMCP_TYPE) == ASF_RMCP_TYPE) {
      break;
    }
    AsfRecord = (EFI_ACPI_ASF_RECORD_HEADER *)((UINT8 *)AsfRecord + AsfRecord->RecordLength);
  } while ((AsfRecord->Type & ASF_LAST_RECORD_TYPE) != ASF_LAST_RECORD_TYPE);

  if ((AsfRecord->Type & ASF_RMCP_TYPE) != ASF_RMCP_TYPE) {
    DEBUG ((DEBUG_INFO, "ASF_RMCP table NOT found\n"));
    return;
  }

  //
  // Get Protocol for ASF
  //
  Status = gBS->LocateProtocol (
                  &gAlertStandardFormatProtocolGuid,
                  NULL,
                  (VOID **) &Asf
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Info : Error gettings ASF protocol -> %r\n", Status));
    return;
  }

  AsfRmcp = (EFI_ACPI_ASF_RMCP *) AsfRecord;
  if (!EFI_ERROR (Status) && (Asf->AsfBootOptions.SpecialCommand != NOP)) {
    AsfRmcp->RMCPCompletionCode = ASF_RMCP_BOOT_OPTION_SUCCESS;
    CopyMem (
      &AsfRmcp->RMCPIANA,
      &Asf->AsfBootOptions.IanaId,
      sizeof (Asf->AsfBootOptions) -
      sizeof (Asf->AsfBootOptions.SubCommand) -
      sizeof (Asf->AsfBootOptions.Version));
  }

  if (Handle != 0) {
    Status = AcpiTable->UninstallAcpiTable (AcpiTable, Handle);
  }

  ///
  /// Update the Acpi Asf table
  ///
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiAsfTable,
                        AcpiAsfTable->Length,
                        &Handle
                        );
  FreePool (AcpiAsfTable);
}

/**
  The driver entry point - initialize PET alert, progress message and KVM query functions.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             The driver installed without error.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
EFIAPI
AmtInitDxeEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS           Status;
  EFI_EVENT            ReadyToBoot;

  DEBUG ((DEBUG_INFO, "AmtInitDxeEntryPoint start\n"));

  ///
  /// KVM function initialization
  ///
  if (AsfIsKvmEnabled ()) {
    Status = KvmInit ();
    ASSERT_EFI_ERROR (Status);
  }

  ///
  /// PET message and progress code initialization
  ///
  Status = PetMessageInit ();
  ASSERT_EFI_ERROR (Status);

  //
  // Register a Ready to boot event to config PCIE power management setting after OPROM executed
  //
  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             AsfTableRmcpOnReadyToBoot,
             NULL,
             &ReadyToBoot
             );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

