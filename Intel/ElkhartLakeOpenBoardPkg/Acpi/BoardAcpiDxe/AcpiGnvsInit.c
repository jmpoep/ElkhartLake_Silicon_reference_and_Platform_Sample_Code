/** @file
  Acpi Gnvs Init Library.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/PlatformNvsArea.h>
#include <Protocol/MpService.h>

/**
@brief
  Global NVS initialize.

  @param[in] PlatformNvsAreaPtr    - Pointer of global NVS area

  @retval EFI_SUCCESS              - Allocate Global NVS completed.
  @retval EFI_OUT_OF_RESOURCES     - Failed to allocate required page for GNVS.
**/
EFI_STATUS
EFIAPI
AcpiGnvsInit (
  IN OUT VOID                   **PlatformNvsAreaPtr
  )
{
  UINTN                         Pages;
  EFI_PHYSICAL_ADDRESS          Address;
  EFI_STATUS                    Status;
  PLATFORM_NVS_AREA_PROTOCOL    *GNVS;
  EFI_MP_SERVICES_PROTOCOL      *MpService;
  UINTN                         NumberOfCPUs;
  UINTN                         NumberOfEnabledCPUs;

  Pages = EFI_SIZE_TO_PAGES (sizeof (PLATFORM_NVS_AREA));
  Address = 0xffffffff; // allocate address below 4G.

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiACPIMemoryNVS,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Locate the MP services protocol
  // Find the MP Protocol. This is an MP platform, so MP protocol must be there.
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &MpService
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Determine the number of processors
  //
  MpService->GetNumberOfProcessors (
              MpService,
              &NumberOfCPUs,
              &NumberOfEnabledCPUs
              );

  *PlatformNvsAreaPtr = (VOID *) (UINTN) Address;
  SetMem (*PlatformNvsAreaPtr, sizeof (PLATFORM_NVS_AREA), 0);

  //
  // GNVS default value init here...
  //
  GNVS = (PLATFORM_NVS_AREA_PROTOCOL *) &Address;

  GNVS->Area->ThreadCount = (UINT8)NumberOfEnabledCPUs;

  //
  // Miscellaneous
  //
  GNVS->Area->PL1LimitCS = 0;
  GNVS->Area->PL1LimitCSValue = 4500;

  return EFI_SUCCESS;
}

