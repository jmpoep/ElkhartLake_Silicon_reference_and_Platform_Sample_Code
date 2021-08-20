/** @file
  This file is SampleCode for Intel PEI System Agent Policy initialization.

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
  Performs FSP SA PEI Policy initialization in pre-memory.

  @param[in][out]  FspmUpd             Pointer to FSP UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
  @retval          EFI_NOT_FOUND       Fail to locate required PPI.
  @retval          Other               FSP UPD Data update process fail.
**/
EFI_STATUS
EFIAPI
PeiFspSaPolicyUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  )
{
  FspmUpd->FspmConfig.SpdAddressTable[0] = PcdGet8 (PcdMrcSpdAddressTable0);
  FspmUpd->FspmConfig.SpdAddressTable[1] = PcdGet8 (PcdMrcSpdAddressTable1);
  FspmUpd->FspmConfig.SpdAddressTable[2] = PcdGet8 (PcdMrcSpdAddressTable2);
  FspmUpd->FspmConfig.SpdAddressTable[3] = PcdGet8 (PcdMrcSpdAddressTable3);

  FspmUpd->FspmConfig.MemorySpdDataLen = PcdGet16 (PcdMrcSpdDataSize);
  FspmUpd->FspmConfig.MemorySpdPtr00 = PcdGet32 (PcdMrcSpdData00);
  FspmUpd->FspmConfig.MemorySpdPtr01 = PcdGet32 (PcdMrcSpdData01);
  FspmUpd->FspmConfig.MemorySpdPtr10 = PcdGet32 (PcdMrcSpdData10);
  FspmUpd->FspmConfig.MemorySpdPtr11 = PcdGet32 (PcdMrcSpdData11);

  //
  // Todo: Need to figure out why TsegSize required for debug mode is bigger then External build Bios.
  //
  FspmUpd->FspmConfig.TsegSize = PcdGet32 (PcdTsegSize);

  return EFI_SUCCESS;
}

