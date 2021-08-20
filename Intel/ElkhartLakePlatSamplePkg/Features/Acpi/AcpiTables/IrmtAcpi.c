/** @file
  These routines get called during ACPI Platform Init to install the ACPI table for
  AOAA (Always on, always available) aka IRMT (Intel Ready Mode Technology).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>
#include <IndustryStandard/Acpi.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/IgdOpRegion.h>


/**
  Routine to search the FV for compiled IRMT SSDT AML binary and install it.

  @retval EFI_SUCCESS    IRMT ACPI tables are initialized successfully
  @retval EFI_NOT_FOUND  IRMT ACPI tables not found
**/
STATIC
EFI_STATUS
InitializeIrmtAcpiTables (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;

  FwVol         = NULL;

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  DEBUG((DEBUG_INFO, "IRMT :gBS->LocateProtocol->AcpiTable Status = %r \n", Status));
  ASSERT_EFI_ERROR (Status);

  //
  // Locate FV Protocol. There is little chance we can't find an FV protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  DEBUG((DEBUG_INFO, "IRMT :gBS->LocateHandleBuffer Status = %r\n", Status));
  ASSERT_EFI_ERROR (Status);
  //
  // Looking for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &FwVol
                    );
    DEBUG((DEBUG_INFO, "IRMT :gBS->HandleProtocol Status = %r\n", Status));
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &gIrmtAcpiTableStorageGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );
    DEBUG((DEBUG_INFO, "IRMT :FwVol->ReadFile Status = %r\n", Status));
    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Free any allocated buffers
  //
  FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol != NULL);
  if (FwVol == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  // Read tables from the storage file.
  //
  Instance      = 0;
  CurrentTable  = NULL;
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &gIrmtAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &CurrentTable,
                      &Size,
                      &FvStatus
                      );
    DEBUG((DEBUG_INFO, "IRMT :FwVol->ReadSection Status = %r\n", Status));

    if (!EFI_ERROR (Status)) {
      //
      // Look for IRMT table.
      //
      if (((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable)->OemTableId == SIGNATURE_64 ('I', 'r', 'm', 't', 'T', 'a', 'b', 'l')) {
        DEBUG((DEBUG_INFO, "IRMT: Publishing IrmtTabl\n"));

        //
        // Install the table
        //
        TableHandle = 0;
        Status = AcpiTable->InstallAcpiTable (
                            AcpiTable,
                            CurrentTable,
                            CurrentTable->Length,
                            &TableHandle
                            );

        gBS->FreePool (CurrentTable);
        CurrentTable = NULL;
        return EFI_SUCCESS;
      }
      //
      // Increment the instance
      //
      Instance++;
      gBS->FreePool (CurrentTable);
      CurrentTable = NULL;
    }
  }
  return Status;
}


/**
  Callback to install IRMT ACPI table at ready to boot.

  @param[in] Event    The event that triggered this notification function
  @param[in] Context  Pointer to the notification functions context
**/
VOID
EFIAPI
IrmtOnReadyToBoot (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "IrmtOnReadyToBoot()\n"));

  Status = InitializeIrmtAcpiTables ();
  DEBUG((DEBUG_INFO, "Initializes IRMT SSDT tables Status = %r \n", Status));

  gBS->CloseEvent (Event);

}


/**
  Intel Ready Mode Technology DXE driver entry point function

  @param[in] ImageHandle Image handle for this driver image
  @param[in] SystemTable Pointer to the EFI System Table

  @retval EFI_OUT_OF_RESOURCES - no enough memory resource when installing reference code information protocol
  @retval EFI_SUCCESS          - function completed successfully
**/
EFI_STATUS
IrmtDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_EVENT                     Event;

  DEBUG ((DEBUG_INFO, "IrmtDxe: Entry Point...\n"));

  //
  // Register ready to boot event for installing IRMT and updating IGD op-region
  //
  Status = EfiCreateEventReadyToBootEx (
            TPL_NOTIFY,
            IrmtOnReadyToBoot,
            NULL,
            &Event
            );
  DEBUG((DEBUG_INFO, "Create ReadyToBoot event for IRMT Status = %r\n", Status));

  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }
  DEBUG ((DEBUG_INFO, "(IrmtDxe) entry End...\n"));

  return EFI_SUCCESS;
}
