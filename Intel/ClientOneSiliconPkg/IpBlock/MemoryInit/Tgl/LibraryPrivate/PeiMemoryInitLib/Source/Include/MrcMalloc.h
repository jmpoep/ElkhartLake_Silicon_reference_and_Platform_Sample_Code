/** @file
  Memory controller buffer allocation routines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _MrcMalloc_h_
#define _MrcMalloc_h_

#include "MrcInterface.h"
#include "MrcDebugPrint.h"

/**
  Function used to initialize the MRC memory used for heap.

  @param[in, out] MrcData  - The MRC global data area.
  @param[in]      HeapBase - The base address of the heap.
  @param[in]      HeapSize - Amount of memory in bytes to allocate.

  @retval Returns a pointer to an allocated memory block on success or NULL on failure.
**/
extern
MrcStatus
MrcHeapInitialize (
  MrcParameters *const MrcData,
  void          *HeapBase,
  UINT32        HeapSize
  );

/**
  Function used to dynamically allocate memory.

  @param[in, out] MrcData - The MRC global data area.
  @param[in]         Size - Amount of memory in bytes to allocate.

  @retval Returns a pointer to an allocated memory block on success or NULL on failure.
**/
extern
void *
MrcHeapMalloc (
  MrcParameters *const MrcData,
  UINT32               Size
  );

/**
  Function used to release memory allocated using MrcMalloc.

  @param[in, out] MrcData - The MRC global data area.
  @param[in]      Buffer  - The buffer to return to the free pool.

  @retval Nothing.
**/
extern
void
MrcHeapFree (
  MrcParameters *const MrcData,
  void                 *Buffer
  );

#endif // _MrcMalloc_h_
