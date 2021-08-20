/** @file
  CSE Variable Storage Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageLib.h>

/**
  Updates the variable header in the index area.

  @param[in]  CseVariableStorageStore        A pointer to a structure that contains CSE variable storage store info.
  @param[in]  IndexContext                   Pointer to an index context structure for the variable being updated.
  @param[in]  IndexAreaWriteOffset           The offset in bytes in the index file of the variable header.
  @param[in]  VariableHeaderUpdateSize       Total size in bytes that should be updated.
  @param[out] CommandInProgress              TRUE if the command requires asynchronous I/O and has not completed yet.
                                             If this command is TRUE, then the Data and DataSize are not updated and do
                                             not contain valid data.

  @retval     EFI_SUCCESS                    The CSE NVM index area was updated successfully.
  @retval     Others                         The CSE NVM index area update operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageUpdateIndexArea (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE         *CseVariableStorageStore,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext,
  IN         UINT32                             IndexAreaWriteOffset,
  IN         UINT32                             VariableHeaderUpdateSize,
  OUT        BOOLEAN                            *CommandInProgress OPTIONAL
  )
{
  UINT32     TotalUpdateSize      = 0;
  VOID       *VariableStoreHeader = NULL;

  if (CseVariableStorageStore == NULL || IndexContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  VariableStoreHeader = CseVariableStorageStore->Info.Header;
  TotalUpdateSize = IndexAreaWriteOffset + VariableHeaderUpdateSize;

  //
  // Update both the variable store header and the variable header in one write transaction (monolithic update)
  //
  // The IndexAreaWriteOffset parameter could be used for two smaller updates to the variable store header and
  // variable header but that is not used in the present design.
  //
  return CseVariableStorageStore->Write (
                                    CseVariableStorageStore,
                                    VariableStoreHeader,
                                    TotalUpdateSize,
                                    0,
                                    FALSE,
                                    IndexContext,
                                    CommandInProgress
                                    );
}

/**
  Returns the maximum index region size for a variable store.

  This is determined by the theoretical maximum number of variables that could reside in the store.

  @param[in]  TotalVariableStoreSize  The total size in bytes of the variable store.
  @param[in]  VariableStoreHeaderSize The total size in bytes of the variable store header.
  @param[in]  VariableHeaderSize      The total size in bytes of the variable header.

  @retval     UINTN                   The maximum size in bytes needed for index region for the variable store.
**/
UINTN
EFIAPI
CalculateMaximumIndexRegionSize (
  IN UINTN  TotalVariableStoreSize,
  IN UINTN  VariableStoreHeaderSize,
  IN UINTN  VariableHeaderSize
  )
{
  UINTN MaximumNumberOfVariables;

  MaximumNumberOfVariables =  (TotalVariableStoreSize - VariableStoreHeaderSize) / \
                                (NVM_GET_PAD_SIZE (VariableHeaderSize) + NVM_GET_PAD_SIZE (1));

  return  (UINTN) TotalVariableStoreSize - \
                    (VariableStoreHeaderSize + (NVM_GET_PAD_SIZE (VariableHeaderSize) * MaximumNumberOfVariables));
}