/** @file
  This file is SampleCode for miscellaneous Intel FSP UPD initialization.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <FspEas.h>
#include <FspmUpd.h>
#include <Library/PeiServicesLib.h>
#include <Library/PreSiliconEnvDetectLib.h>

/**
  Performs FSP Misc UPD initialization.

  @param[in][out]  FspmUpd             Pointer to FSPM_UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
**/
EFI_STATUS
EFIAPI
PeiFspMiscUpdUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  )
{
  EFI_BOOT_MODE      BootMode;
  EFI_STATUS         Status;

  FspmUpd->FspmArchUpd.StackBase = (VOID *)(UINTN)PcdGet32 (PcdStackBase);
  FspmUpd->FspmArchUpd.StackSize = PcdGet32 (PcdStackSize);
  FspmUpd->FspmArchUpd.NvsBufferPtr = (VOID *)(UINTN)PcdGet32 (PcdNvsBufferPtr);
  FspmUpd->FspmConfig.CleanMemory = PcdGet8 (PcdCleanMemory);

  Status = PeiServicesGetBootMode (&BootMode);
  FspmUpd->FspmArchUpd.BootMode = BootMode;

  //
  // Work around for Simics testing
  //
  if (IsSimicsEnvironment ()) {
    FspmUpd->FspmConfig.PlatformDebugConsent = 0;
  }

  return EFI_SUCCESS;
}

