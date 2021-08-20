/** @file
  CSE Variable Storage Index Library Header File

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_INDEX_LIB_H_
#define _CSE_VARIABLE_STORAGE_INDEX_LIB_H_

#include <CseVariableStorage.h>

/**
  Updates the index area based on the current variable context

  @param[in]  IndexContext            A pointer to an index context structure that should be written to the index area.

  @retval     EFI_SUCCESS             The context information was successfully written to the index area.
  @retval     EFI_INVALID_PARAMETER   An error occurred writing the context to the index area.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoUpdateIndexArea (
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT    *IndexContext
  );

/**
  Updates the data buffer provided based on the variable context.

  @param[in]      CseVariableStorageStore           A pointer to a structure CSE Variable Storage Store structure.
  @param[in]      CseVariableIndexQueueWriteBuffer  A pointer to an array of index context pointers.
  @param[in]      CseVariableIndexQueueWriteEntries The number of queued index contexts.
  @param[in,out]  Data                              A pointer to a buffer of data to write.
  @param[in]      DataSize                          The length in bytes of data to write.
  @param[in]      IndexContext                      A structure with the index context for the variable being written.

  @retval         EFI_SUCCESS                       The data buffer was updated successfully.
  @retval         EFI_INVALID_PARAMETER             A parameter to the function was invalid such as a NULL pointer.
  @retval         EFI_BUFFER_TOO_SMALL              A buffer provided to the function was too small to perform the update.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoUpdateDataWithContext (
  IN      CONST CSE_VARIABLE_STORAGE_STORE         *CseVariableStorageStore,
  IN      CONST CSE_VARIABLE_STORAGE_INDEX_CONTEXT **CseVariableIndexQueueWriteBuffer,
  IN            UINTN                              CseVariableIndexQueueEntries,
  IN OUT        VOID                               *Data,
  IN            UINTN                              DataSize,
  IN      CONST CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext
  );

/**
  Returns a pointer to the last index context entry in the queue or NULL if no entries are present.

  @param[in]    CseVariableStorageType            The type of CSE variable store the variable is stored in.
  @param[in]    CseVariableIndexQueueWriteBuffer  A pointer to an array of index context pointers.
  @param[in]    CseVariableIndexQueueWriteEntries The number of queued index contexts.
  @param[in]    RequireValidVariableStore         If TRUE, the entry must point to a valid variable store.
  @param[in]    RequireValidVariableHeader        If TRUE, the entry must point to a valid variable header.
  @param[in]    RequireValidVariableName          If TRUE, the entry must point to a valid variable name.

  @retval       IndexContext                      A pointer to the last index context structure entry in the queue or
                                                  NULL if the index context queue is empty.

**/
CSE_VARIABLE_STORAGE_INDEX_CONTEXT *
EFIAPI
CseVariableStorageGetLastIndexQueueEntry (
  IN  CSE_VARIABLE_STORAGE_TYPE           CseVariableStorageType,
  IN  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  **CseVariableIndexQueueWriteBuffer,
  IN  UINTN                               CseVariableIndexQueueEntries,
  IN  BOOLEAN                             RequireValidVariableStore,
  IN  BOOLEAN                             RequireValidVariableHeader,
  IN  BOOLEAN                             RequireValidVariableName
  );

#endif
