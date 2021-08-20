/** @file
  This file is SampleCode for Intel PEI CPU Policy initialization.

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
#include <Library/PcdLib.h>

/**
  Performs FSP CPU PEI Policy initialization in pre-memory.

  @param[in][out]  FspmUpd             Pointer to FSP UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
  @retval          EFI_NOT_FOUND       Fail to locate required PPI.
  @retval          Other               FSP UPD Data update process fail.
**/
EFI_STATUS
EFIAPI
PeiFspCpuPolicyUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  )
{
  FspmUpd->FspmConfig.CpuRatio = PcdGet8 (PcdCpuRatio);
  FspmUpd->FspmConfig.BiosGuard = PcdGet8 (PcdBiosGuard);

  return EFI_SUCCESS;
}

