/** @file

    Source code file for the Report Firmware Volume (FV) library

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

#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/ReportFvLib.h>
#include <Guid/FirmwareFileSystem2.h>
#include <Ppi/FirmwareVolumeInfo.h>

VOID
ReportPreMemFv (
  VOID
  )
{
  if (!PcdGetBool(PcdFspWrapperBootMode)) {
    DEBUG ((DEBUG_INFO, "Install FlashFvFspM - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvFspMBase), PcdGet32 (PcdFlashFvFspMSize)));
    PeiServicesInstallFvInfo2Ppi (
      &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvFspMBase))->FileSystemGuid),
      (VOID *) (UINTN) PcdGet32 (PcdFlashFvFspMBase),
      PcdGet32 (PcdFlashFvFspMSize),
      NULL,
      NULL,
      0
      );
  }
  DEBUG ((DEBUG_INFO, "Install FlashFvSecurity - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvSecurityBase), PcdGet32 (PcdFlashFvSecuritySize)));
  PeiServicesInstallFvInfo2Ppi (
    &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvSecurityBase))->FileSystemGuid),
    (VOID *) (UINTN) PcdGet32 (PcdFlashFvSecurityBase),
    PcdGet32 (PcdFlashFvSecuritySize),
    NULL,
    NULL,
    0
    );

  DEBUG ((DEBUG_INFO, "Install FlashFvFirmwareBinaries - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvFirmwareBinariesBase), PcdGet32 (PcdFlashFvFirmwareBinariesSize)));
  PeiServicesInstallFvInfo2Ppi (
    &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvFirmwareBinariesBase))->FileSystemGuid),
    (VOID *) (UINTN) PcdGet32 (PcdFlashFvFirmwareBinariesBase),
    PcdGet32 (PcdFlashFvFirmwareBinariesSize),
    NULL,
    NULL,
    0
    );
}

VOID
ReportPostMemFv (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_BOOT_MODE                 BootMode;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Build HOB for DXE
  ///
  if (BootMode == BOOT_IN_RECOVERY_MODE) {
    ///
    /// Prepare the recovery service
    ///
  } else {
    DEBUG ((DEBUG_INFO, "Install FlashFvPostMemory - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvPostMemoryBase), PcdGet32 (PcdFlashFvPostMemorySize)));
    PeiServicesInstallFvInfo2Ppi (
      &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvPostMemoryBase))->FileSystemGuid),
      (VOID *) (UINTN) PcdGet32 (PcdFlashFvPostMemoryBase),
      PcdGet32 (PcdFlashFvPostMemorySize),
      NULL,
      NULL,
      0
      );
    if (!PcdGetBool(PcdFspWrapperBootMode)) {
      DEBUG ((DEBUG_INFO, "Install FlashFvFspS - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvFspSBase), PcdGet32 (PcdFlashFvFspSSize)));
      PeiServicesInstallFvInfo2Ppi (
        &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvFspSBase))->FileSystemGuid),
        (VOID *) (UINTN) PcdGet32 (PcdFlashFvFspSBase),
        PcdGet32 (PcdFlashFvFspSSize),
        NULL,
        NULL,
        0
        );
      DEBUG ((DEBUG_INFO, "Install FlashFvFspU - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvFspUBase), PcdGet32 (PcdFlashFvFspUSize)));
      PeiServicesInstallFvInfo2Ppi (
        &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvFspUBase))->FileSystemGuid),
        (VOID *) (UINTN) PcdGet32 (PcdFlashFvFspUBase),
        PcdGet32 (PcdFlashFvFspUSize),
        NULL,
        NULL,
        0
        );
    }

    if (GetFirstGuidHob (&gSysFwUpdateProgressGuid) == NULL) {
      DEBUG ((DEBUG_INFO, "Install FlashFvAdvanced - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvAdvancedBase), PcdGet32 (PcdFlashFvAdvancedSize)));
      PeiServicesInstallFvInfo2Ppi (
        &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvAdvancedBase))->FileSystemGuid),
        (VOID *) (UINTN) PcdGet32 (PcdFlashFvAdvancedBase),
        PcdGet32 (PcdFlashFvAdvancedSize),
        NULL,
        NULL,
        0
        );
      DEBUG ((DEBUG_INFO, "Install FlashFvUefiBoot - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvUefiBootBase), PcdGet32 (PcdFlashFvUefiBootSize)));
      PeiServicesInstallFvInfo2Ppi (
        &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvUefiBootBase))->FileSystemGuid),
        (VOID *) (UINTN) PcdGet32 (PcdFlashFvUefiBootBase),
        PcdGet32 (PcdFlashFvUefiBootSize),
        NULL,
        NULL,
        0
        );
      DEBUG ((DEBUG_INFO, "Install FlashFvOsBoot - 0x%x, 0x%x\n", PcdGet32 (PcdFlashFvOsBootBase), PcdGet32 (PcdFlashFvOsBootSize)));
      PeiServicesInstallFvInfo2Ppi (
        &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) PcdGet32 (PcdFlashFvOsBootBase))->FileSystemGuid),
        (VOID *) (UINTN) PcdGet32 (PcdFlashFvOsBootBase),
        PcdGet32 (PcdFlashFvOsBootSize),
        NULL,
        NULL,
        0
        );
    }

  }

  //
  // Report resource HOB for flash FV
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    (UINTN) PcdGet32 (PcdFlashAreaBaseAddress),
    (UINTN) PcdGet32 (PcdFlashAreaSize)
    );
  BuildMemoryAllocationHob (
    (UINTN) PcdGet32 (PcdFlashAreaBaseAddress),
    (UINTN) PcdGet32 (PcdFlashAreaSize),
    EfiMemoryMappedIO
    );
}
