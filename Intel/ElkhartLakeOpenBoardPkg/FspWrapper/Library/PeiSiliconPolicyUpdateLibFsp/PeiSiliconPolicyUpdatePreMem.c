/** @file
  This file is SampleCode for Intel PEI Platform Policy initialization in pre-memory.

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
#include <Library/DebugLib.h>

EFI_STATUS
EFIAPI
PeiFspCpuPolicyUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  );

EFI_STATUS
EFIAPI
PeiFspSaPolicyUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  );

EFI_STATUS
EFIAPI
PeiFspMiscUpdUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  );

VOID
InternalPrintVariableData (
  IN UINT8   *Data8,
  IN UINTN   DataSize
  )
{
  UINTN      Index;

  for (Index = 0; Index < DataSize; Index++) {
    if (Index % 0x10 == 0) {
      DEBUG ((DEBUG_INFO, "\n%08X:", Index));
    }
    DEBUG ((DEBUG_INFO, " %02X", *Data8++));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID *
EFIAPI
SiliconPolicyUpdatePreMem (
  IN OUT VOID *Policy
  )
{
  FSPM_UPD              *FspmUpdDataPtr;

  FspmUpdDataPtr = Policy;
  PeiFspCpuPolicyUpdatePreMem (FspmUpdDataPtr);
  PeiFspSaPolicyUpdatePreMem (FspmUpdDataPtr);
  PeiFspMiscUpdUpdatePreMem (FspmUpdDataPtr);

  InternalPrintVariableData ((VOID *)FspmUpdDataPtr, sizeof (FSPM_UPD));

  return Policy;
}
