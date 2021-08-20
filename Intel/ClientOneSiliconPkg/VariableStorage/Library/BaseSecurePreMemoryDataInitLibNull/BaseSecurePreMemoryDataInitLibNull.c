/** @file
  Base Secure Pre-Memory Data Initialize Null Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017-2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/SecurePreMemoryDataInitLib.h>

/**
  The Secure Pre-Memory Data (SPMD) table resides at the beginning of the BIOS data partition. BIOS maintains the
  table and CSE uses the table to manage pre-memory data structures exchanged between BIOS and CSE.

  This function populates a user passed buffer with the SPMD structure to be returned to the caller.

  @param[out]      SECURE_PRE_MEMORY_DATA_TABLE  A pointer to a SPMD table structure.

  @retval          EFI_SUCCESS                   The table was created successfully.
  @retval          EFI_INVALID_PARAMETER         The pointer to the SPMD table is invalid.
  @retval          Others                        An error occurred returning the table.
**/
EFI_STATUS
EFIAPI
GetNewSecurePreMemoryDataTable (
  OUT SECURE_PRE_MEMORY_DATA_TABLE               *SecurePreMemoryDataTable
  )
{
  return EFI_SUCCESS;
}