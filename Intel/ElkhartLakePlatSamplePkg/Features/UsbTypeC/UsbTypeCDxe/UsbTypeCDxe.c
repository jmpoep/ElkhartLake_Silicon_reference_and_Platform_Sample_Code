/** @file
  Implements UsbTypeC Dxe driver and publish UsbTypeC Acpi table

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <UsbTypeCDxe.h>

#include <Protocol/AcpiTable.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/EcMiscLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/PcdLib.h>
#include <Protocol/PlatformNvsArea.h>


GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA_PROTOCOL    *PlatformNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA             *mPlatformNvsAreaPtr;

#define USBTYPEC_DATA_VAR         L"UsbTypeC"
EFI_GUID UsbTypeCVarGuid      =  { 0xfc876842, 0xd8f0, 0x4844, {0xae, 0x32, 0x1f, 0xf8, 0x43, 0x79, 0x7b, 0x17} };

/**
  Allocate MemoryType below 4G memory address.

  @param[in] Size           Size of memory to allocate.
  @param[in] Buffer         Allocated address for output.

  @retval EFI_SUCCESS       Memory successfully allocated.
  @retval Other             Other errors occur.
**/
static EFI_STATUS
AllocateMemoryBelow4G (
  IN   EFI_MEMORY_TYPE MemoryType,
  IN   UINTN           Size,
  OUT  VOID           **Buffer
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;

  Pages = EFI_SIZE_TO_PAGES (Size);
  Address = 0xffffffff;

  Status  = (gBS->AllocatePages) (
                   AllocateMaxAddress,
                   MemoryType,
                   Pages,
                   &Address
                   );

  *Buffer = (VOID *) (UINTN) Address;

  return Status;
};

static UINT16 GetUcsiRev(VOID)
{
  UINT8  Rev1;
  UINT8  Rev2;

  Rev1 = 0;
  Rev2 = 0;

  SendEcCommand (0xE1);
  ReceiveEcData (&Rev1);
  ReceiveEcData (&Rev2);
  return ((Rev1 << 8) + Rev2);
}

/**
  Initialize and publish UsbTypeC ACPI table.

  @retval   EFI_SUCCESS     The UsbTypeC ACPI table is published successfully.
  @retval   Others          The UsbTypeC ACPI table is not published.

**/
EFI_STATUS
PublishAcpiTable (
  VOID
  )
{
  EFI_STATUS                     Status;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTable;
  UINTN                          TableKey;
  EFI_ACPI_DESCRIPTION_HEADER    *Table;
  UINTN                          TableSize;

  Status = GetSectionFromFv (
             &gEfiCallerIdGuid,
             EFI_SECTION_RAW,
             0,
             (VOID **) &Table,
             &TableSize
             );
  ASSERT_EFI_ERROR (Status);

  ASSERT (Table->OemTableId == SIGNATURE_64 ('U', 's', 'b', 'C', 'T', 'a', 'b', 'l'));

  CopyMem (Table->OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (Table->OemId) );

  //
  // Publish UsbTypeC ACPI table
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  ASSERT_EFI_ERROR (Status);

  TableKey = 0;
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        Table,
                        TableSize,
                        &TableKey
                        );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
/**
  This function is the entry point for this DXE driver.
  It creates ACPI table and publishes it.

  @param[in] ImageHandle       Image handle of this driver.
  @param[in] SystemTable       Global system service table.

  @retval EFI_DEVICE_ERROR     Initialization fails
  @retval EFI_SUCCESS          Initialization completes successfully.

**/
EFI_STATUS
EFIAPI
UsbTypeCEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS         Status;
  USBTYPEC_OPM_BUF   *OpmBuffer;

  DEBUG ((DEBUG_INFO, "UsbTypeC entrypoint.\n"));

  Status = PublishAcpiTable ();
  ASSERT_EFI_ERROR (Status);

  if (!PcdGetBool (PcdUsbTypeCSupport)) {
    DEBUG ((DEBUG_WARN, "UsbTypeC currently only supported on ICL U, Y.\n"));
    return EFI_UNSUPPORTED;
  }

  Status = gBS->LocateProtocol (&gPlatformNvsAreaProtocolGuid, NULL, (VOID **) &PlatformNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mPlatformNvsAreaPtr = PlatformNvsAreaProtocol->Area;
  //
  // Allocate memory in ACPI NVS
  //
  Status = AllocateMemoryBelow4G (EfiACPIMemoryNVS, 0x1000, (VOID **) &OpmBuffer);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  SetMem (OpmBuffer, sizeof (USBTYPEC_OPM_BUF), 0x0);
  OpmBuffer->Version =  GetUcsiRev();

  mPlatformNvsAreaPtr->UsbTypeCOpBaseAddr = (UINT32) (UINTN) OpmBuffer;
  DEBUG ((DEBUG_INFO, "UsbTypeC EntryPoint: mPlatformNvsAreaPtr->UsbTypeCOpBaseAddr = 0x%X\n", mPlatformNvsAreaPtr->UsbTypeCOpBaseAddr));

  Status = gRT->SetVariable (
    USBTYPEC_DATA_VAR,
    &UsbTypeCVarGuid,
    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof (UINT32),
    &(mPlatformNvsAreaPtr->UsbTypeCOpBaseAddr)
  );

  // Total Type C ports supported
  mPlatformNvsAreaPtr->TotalTypeCPorts      = PcdGet8(PcdTypeCPortsSupported);
  // Port 1  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort1        = PcdGet8(PcdUsbTypeCPort1);
  mPlatformNvsAreaPtr->UsbTypeCPort1Pch     = PcdGet8(PcdUsbTypeCPort1Pch);
  mPlatformNvsAreaPtr->UsbCPort1Proterties  = PcdGet8(PcdUsbCPort1Properties);
  // Port 2  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort2        = PcdGet8(PcdUsbTypeCPort2);
  mPlatformNvsAreaPtr->UsbTypeCPort2Pch     = PcdGet8(PcdUsbTypeCPort2Pch);
  mPlatformNvsAreaPtr->UsbCPort2Proterties  = PcdGet8(PcdUsbCPort2Properties);
  // Port 3  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort3        = PcdGet8(PcdUsbTypeCPort3);
  mPlatformNvsAreaPtr->UsbTypeCPort3Pch     = PcdGet8(PcdUsbTypeCPort3Pch);
  mPlatformNvsAreaPtr->UsbCPort3Proterties  = PcdGet8(PcdUsbCPort3Properties);
  // Port 4  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort4        = PcdGet8(PcdUsbTypeCPort4);
  mPlatformNvsAreaPtr->UsbTypeCPort4Pch     = PcdGet8(PcdUsbTypeCPort4Pch);
  mPlatformNvsAreaPtr->UsbCPort4Proterties  = PcdGet8(PcdUsbCPort4Properties);
  // Port 5  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort5        = PcdGet8(PcdUsbTypeCPort5);
  mPlatformNvsAreaPtr->UsbTypeCPort5Pch     = PcdGet8(PcdUsbTypeCPort5Pch);
  mPlatformNvsAreaPtr->UsbCPort5Proterties  = PcdGet8(PcdUsbCPort5Properties);
  // Port 6  mapping and properties
  mPlatformNvsAreaPtr->UsbTypeCPort6        = PcdGet8(PcdUsbTypeCPort6);
  mPlatformNvsAreaPtr->UsbTypeCPort6Pch     = PcdGet8(PcdUsbTypeCPort6Pch);
  mPlatformNvsAreaPtr->UsbCPort6Proterties  = PcdGet8(PcdUsbCPort6Properties);

  return Status;
}
