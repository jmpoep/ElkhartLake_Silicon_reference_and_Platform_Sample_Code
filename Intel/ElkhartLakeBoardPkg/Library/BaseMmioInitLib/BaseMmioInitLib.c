/** @file

    Source code file for the Base MMIO Init library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
