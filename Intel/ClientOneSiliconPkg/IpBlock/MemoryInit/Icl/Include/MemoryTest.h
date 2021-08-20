/** @file
  This header file provides memory test function.

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

#ifndef _Memory_TEST_H_
#define _Memory_TEST_H_

#include <Base.h>
#include <MrcGlobal.h>
#include <MrcDebugPrint.h>
#include <Library/DebugLib.h>

///
/// Used in memory test routines
///
#define  MEMORY_TEST_COVER_SPAN         0x40000
#define  MEMORY_TEST_PATTERN            0x5A5A5A5A

typedef enum {
  Ignore,
  Quick,
  Sparse,
  Extensive,
  MemTestMax
} MEMORY_TEST_LEVEL;

/**
  This function checks the memory range.

  @param[in]  MrcData           Pointer to the MRC global data structure
  @param[in]  BeginAddress      Beginning of the memory address to be checked.
  @param[in]  MemoryLength      Bytes of memory range to be checked.
  @param[in]  MemoryTestLevel   Type of memory check level to be performed.
  @param[out] ErrorAddress      Return the address of the error memory address.

  @retval     EFI_SUCCESS       The operation completed successfully.
  @retval     EFI_DEVICE_ERROR  Memory test failed. It's not reliable to use this range of memory.
**/
EFI_STATUS
EFIAPI
BaseMemoryTest (
  IN CONST MrcParameters         * CONST MrcData,
  IN       EFI_PHYSICAL_ADDRESS  BeginAddress,
  IN       UINT64                MemoryLength,
  IN       MEMORY_TEST_LEVEL     MemoryTestLevel,
  OUT      EFI_PHYSICAL_ADDRESS  *ErrorAddress
  );

/**
  A small memory test to quickly point out severe memory issues.

  @param[in]  MrcData Pointer to the MRC global data structure

  @retval mrcFail on failure, otherwise mrcSuccess.
**/
MrcStatus
BasicMemoryTest (
  IN CONST MrcParameters * CONST MrcData
  );

/**
  A small memory test to quickly point out severe memory issues.
  This test restores each modified memory location,
  so we can run it on S3 resume as well.

  @param[in] MrcData - Pointer to the MRC global data structure

  @retval mrcFail on failure, otherwise mrcSuccess.
**/
MrcStatus
BasicMemoryTestS3 (
  IN CONST MrcParameters * CONST MrcData
  );

#endif
