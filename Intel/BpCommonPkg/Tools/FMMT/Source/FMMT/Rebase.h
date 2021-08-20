/** @file  Rebase.h

 Library to rebase PE image.

 Copyright (c) 2015 - 2017, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _FMMT_REBASE_H
#define _FMMT_REBASE_H

#include <Common/UefiBaseTypes.h>
#include <Common/PiFirmwareFile.h>

EFI_STATUS
RebaseFfs(
IN OUT  UINT64                 BaseAddress,
IN      CHAR8                 *FileName,
IN OUT  EFI_FFS_FILE_HEADER   *FfsFile,
IN      UINTN                 XipOffset
);

EFI_STATUS
GetChildFvFromFfs (
  IN      UINT64                 BaseAddress,
  IN      EFI_FFS_FILE_HEADER   *FfsFile,
  IN      UINTN                 XipOffset
);

EFI_STATUS
GetPe32Info (
  IN UINT8                  *Pe32,
  OUT UINT32                *EntryPoint,
  OUT UINT32                *BaseOfCode,
  OUT UINT16                *MachineType
);

#endif
