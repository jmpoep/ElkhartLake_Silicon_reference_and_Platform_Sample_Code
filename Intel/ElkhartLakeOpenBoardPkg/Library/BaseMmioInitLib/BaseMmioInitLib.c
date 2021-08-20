/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Pi/PiMultiPhase.h>
#include <Library/HobLib.h>
#include <Library/MmioInitLib.h>

typedef struct {
  EFI_PHYSICAL_ADDRESS    BaseAddress;
  UINT64                  Length;
} MEMORY_MAP;

GLOBAL_REMOVE_IF_UNREFERENCED MEMORY_MAP MmioMap [] = {
  {FixedPcdGet64 (PcdLocalApicAddress), FixedPcdGet32 (PcdLocalApicMmioSize)},
  {FixedPcdGet64 (PcdMchBaseAddress), FixedPcdGet32 (PcdMchMmioSize)},
  {FixedPcdGet64 (PcdDmiBaseAddress), FixedPcdGet32 (PcdDmiMmioSize)},
  {FixedPcdGet64 (PcdEpBaseAddress), FixedPcdGet32 (PcdEpMmioSize)}
};

/**
  Initialize MMIO ranges

  @retval EFI_SUCCESS    The function completed successfully
**/
EFI_STATUS
MmioInit (
  VOID
  )
{
  UINTN                         Index;
  MEMORY_MAP                    PcieMmioMap;

  ///
  /// Build Memory Mapped IO Resource which is used to build E820 Table in LegacyBios.
  ///
  PcieMmioMap.BaseAddress = FixedPcdGet64 (PcdPciExpressBaseAddress);
  PcieMmioMap.Length = PcdGet32 (PcdPciExpressRegionLength);

  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    PcieMmioMap.BaseAddress,
    PcieMmioMap.Length
    );
  BuildMemoryAllocationHob (
    PcieMmioMap.BaseAddress,
    PcieMmioMap.Length,
    EfiMemoryMappedIO
    );
  for (Index = 0; Index < sizeof (MmioMap) / (sizeof (MEMORY_MAP)); Index++) {
    BuildResourceDescriptorHob (
      EFI_RESOURCE_MEMORY_MAPPED_IO,
      (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
      EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
      EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
      MmioMap[Index].BaseAddress,
      MmioMap[Index].Length
      );
    BuildMemoryAllocationHob (
      MmioMap[Index].BaseAddress,
      MmioMap[Index].Length,
      EfiMemoryMappedIO
      );
  }

  return EFI_SUCCESS;
}
