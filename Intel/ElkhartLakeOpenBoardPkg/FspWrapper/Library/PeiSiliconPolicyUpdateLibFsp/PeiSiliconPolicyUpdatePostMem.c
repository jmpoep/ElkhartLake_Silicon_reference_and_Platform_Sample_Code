/** @file
  This file is SampleCode for Intel PEI Platform Policy initialization in post-memory.

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
#include <FspsUpd.h>

EFI_STATUS
EFIAPI
PeiFspPchPolicyUpdatePostMem (
  IN OUT FSPS_UPD    *FspsUpd
  );

VOID
InternalPrintVariableData (
  IN UINT8   *Data8,
  IN UINTN   DataSize
  );

VOID *
EFIAPI
SiliconPolicyUpdatePostMem (
  IN OUT VOID *Policy
  )
{
  FSPS_UPD              *FspsUpdDataPtr;

  FspsUpdDataPtr = Policy;
  PeiFspPchPolicyUpdatePostMem (FspsUpdDataPtr);

  InternalPrintVariableData ((VOID *)FspsUpdDataPtr, sizeof (FSPS_UPD));

  return Policy;
}
