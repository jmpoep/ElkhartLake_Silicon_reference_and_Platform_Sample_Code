/** @file
  Prototype of Intel Processor Trace memory allocation library.

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

#ifndef  _PROCESSOR_TRACE_MEMORY_ALLOCATION_LIB_H_
#define  _PROCESSOR_TRACE_MEMORY_ALLOCATION_LIB_H_

#include <PiPei.h>

///
/// Processor trace buffer size selection.
///
typedef enum {
  Enum4K    = 0,
  Enum8K,
  Enum16K,
  Enum32K,
  Enum64K,
  Enum128K,
  Enum256K,
  Enum512K,
  Enum1M,
  Enum2M,
  Enum4M,
  Enum8M,
  Enum16M,
  Enum32M,
  Enum64M,
  Enum128M,
  EnumProcessorTraceMemDisable
} PROCESSOR_TRACE_MEM_SIZE;

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
  );

#endif

