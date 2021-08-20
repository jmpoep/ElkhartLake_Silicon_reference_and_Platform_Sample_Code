/** @file
  Instance of Intel Processor Trace memory allocation library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ProcessorTraceMemoryAllocationLib.h>
#include <Library/CpuPlatformLib.h>

/**
  Allocate memory region for Processor Trace, based on requested size per thread.

  @param[in]  RequestedMemSize          Requested size per thread, specified using PROCESSOR_TRACE_MEM_SIZE encoding
  @param[out] *BaseAddress              Outputs a pointer to the base address of the allocated memory region. Base address is NULL on a failure
  @param[out] *LengthInBytes            Outputs a pointer to the size of the allocated memory region, in bytes

  @retval EFI_SUCCESS                   Successfully allocated the memory region
  @retval EFI_INVALID_PARAMETER         Invalid value for RequestedMemSize
  @retval EFI_OUT_OF_RESOURCES          AllocatePages failed to allocate the memory region
**/
EFI_STATUS
EFIAPI
ProcessorTraceAllocateMemory (
  IN  PROCESSOR_TRACE_MEM_SIZE RequestedMemSize,
  OUT EFI_PHYSICAL_ADDRESS     *BaseAddress,
  OUT UINT32                   *LengthInBytes
  )
{
  UINT32                       MemRegionSize;
  UINTN                        Pages;
  UINT16                       NumThreads;

  *BaseAddress = (EFI_PHYSICAL_ADDRESS) (UINTN) NULL;
  *LengthInBytes = 0;

  if (RequestedMemSize >= EnumProcessorTraceMemDisable) {
    DEBUG ((DEBUG_INFO, "ProcessorTraceAllocateMemory: No memory requested.\n", RequestedMemSize));
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Get the total number of enabled processor threads.
  ///
  NumThreads = GetEnabledThreadCount ();

  ///
  /// Refer to PROCESSOR_TRACE_MEM_SIZE Table for Size Encoding
  ///
  MemRegionSize = (UINT32) (1 << (RequestedMemSize + 12));
  DEBUG ((DEBUG_INFO, "ProcessorTraceAllocateMemory: MemSize requested per thread: 0x%X \n", MemRegionSize));

  ///
  /// Allocate enough pages for all threads.
  /// All Processor Trace regions must be aligned based on their size.
  ///
  Pages = EFI_SIZE_TO_PAGES (MemRegionSize) * NumThreads;
  *BaseAddress = (EFI_PHYSICAL_ADDRESS) (UINTN) AllocateAlignedReservedPages (Pages, MemRegionSize);
  if (*BaseAddress == 0) {
    DEBUG ((DEBUG_ERROR, "ProcessorTraceAllocateMemory: Out of memory, allocate pages failed\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  *LengthInBytes = EFI_PAGES_TO_SIZE (Pages);

  DEBUG ((DEBUG_INFO, "ProcessorTraceAllocateMemory: MemBase: 0x%X \n", *BaseAddress));
  DEBUG ((DEBUG_INFO, "ProcessorTraceAllocateMemory: MemLength: 0x%X \n", *LengthInBytes));
  return EFI_SUCCESS;
}
