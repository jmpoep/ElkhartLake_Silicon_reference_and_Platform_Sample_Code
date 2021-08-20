/** @file
  CSE Variable Storage Index Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <CseVariableStorage.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageIndexLib.h>

/**
  Determines if a given index context element meets the given criteria.

  @param[in]    IndexContext                A pointer to the index context structure that should be evaluated.
  @param[in]    RequireValidVariableStore   If TRUE, the entry must point to a valid variable store.
  @param[in]    RequireValidVariableHeader  If TRUE, the entry must point to a valid variable header.
  @param[in]    RequireValidVariableName    If TRUE, the entry must point to a valid variable name.

  @retval       BOOLEAN                     TRUE if the index context meets the given criteria, otherwise FALSE.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsIndexContextValid (
  IN  CONST CSE_VARIABLE_STORAGE_INDEX_CONTEXT  *IndexContext,
  IN        BOOLEAN                             RequireValidVariableStore,
  IN        BOOLEAN                             RequireValidVariableHeader,
  IN        BOOLEAN                             RequireValidVariableName
  )
{
  if (IndexContext == NULL || !IndexContext->Valid) {
    return FALSE;
  }

  if (
    RequireValidVariableStore &&
    (
      IndexContext->VariableStoreIndexPtr == NULL ||
      GetVariableStoreStatus (&(IndexContext->VariableStoreHeader)) != EfiValid
      )
    ) {
    return FALSE;
  }
  if (
    RequireValidVariableHeader &&
    (
      IndexContext->VariableHeaderIndexPtr == NULL ||
      IndexContext->VariableHeader.StartId != VARIABLE_DATA
      )
    ) {
    return FALSE;
  }
  if (RequireValidVariableName && IndexContext->VariableNamePtr == NULL) {
    return FALSE;
  }

  return TRUE;
}

/**
  Updates the index area based on the current variable context.

  @param[in]  IndexContext            A pointer to an index context structure that should be written to the index area.

  @retval     EFI_SUCCESS             The context information was successfully written to the index area.
  @retval     EFI_INVALID_PARAMETER   An error occurred writing the context to the index area.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoUpdateIndexArea (
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT    *IndexContext
  )
{
  if (IndexContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (IndexContext->Valid) {
    if (IndexContext->VariableStoreIndexPtr != NULL) {
      DEBUG ((DEBUG_INFO, "Updated variable store header in the index.\n"));
      CopyMem (
        (VOID *) IndexContext->VariableStoreIndexPtr,
        (VOID *) &(IndexContext->VariableStoreHeader),
        sizeof (VARIABLE_NVM_STORE_HEADER)
        );
    }

    if (IndexContext->VariableHeaderIndexPtr != NULL) {
      DEBUG ((DEBUG_INFO, "Updated variable header in the index.\n"));
      CopyMem (
        (VOID *) IndexContext->VariableHeaderIndexPtr,
        (VOID *) &(IndexContext->VariableHeader),
        GetVariableHeaderSize (IndexContext->AuthFlag)
        );
    }

    if (IndexContext->VariableHeaderIndexPtr != NULL && IndexContext->VariableNamePtr != NULL) {
      DEBUG ((DEBUG_INFO, "Updated variable name in the index.\n"));
      StrCpyS (
        GetVariableNamePtr ((VARIABLE_NVM_HEADER *) IndexContext->VariableHeaderIndexPtr, IndexContext->AuthFlag),
        IndexContext->VariableHeader.NameSize,
        IndexContext->VariableNamePtr
        );
    }
  } else {
    DEBUG ((DEBUG_INFO, "Skipped updating invalid index context structure.\n"));
  }

  return EFI_SUCCESS;
}

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
  )
{
  EFI_STATUS Status;
  UINT32     Index;
  UINT32     VariableHeaderWriteOffset;

  VariableHeaderWriteOffset = 0;

  if (CseVariableStorageStore == NULL || CseVariableIndexQueueWriteBuffer == NULL || Data == NULL || IndexContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Update the variable store in the data
  //
  if (IndexContext->VariableStoreIndexPtr != NULL) {
    if (DataSize < sizeof (VARIABLE_NVM_STORE_HEADER)) {
      ASSERT (DataSize >= sizeof (VARIABLE_NVM_STORE_HEADER));
      return EFI_BUFFER_TOO_SMALL;
    }
    DEBUG ((DEBUG_INFO, "Updating the variable store header in the index data.\n"));
    CopyMem (
      Data,
      (VOID *) &(IndexContext->VariableStoreHeader),
      sizeof (VARIABLE_NVM_STORE_HEADER)
      );

    //
    // Replay any queued index variable entries on the store
    //
    if (CseVariableIndexQueueEntries > 0) {
      for (Index = 0; Index < CseVariableIndexQueueEntries; Index++) {
        if (
          CseVariableStorageIsIndexContextValid (CseVariableIndexQueueWriteBuffer[Index], FALSE, TRUE, FALSE) &&
          CseVariableIndexQueueWriteBuffer[Index]->CseVariableStore->Info.Type == CseVariableStorageStore->Info.Type
          ) {
          VariableHeaderWriteOffset = NVM_HEADER_ALIGN (
                                        (UINT32) (
                                          (UINTN) CseVariableIndexQueueWriteBuffer[Index]->VariableHeaderIndexPtr -
                                          (UINTN) CseVariableIndexQueueWriteBuffer[Index]->CseVariableStore->Info.Header
                                          )
                                        );
          if (DataSize < (VariableHeaderWriteOffset + GetVariableHeaderSize (IndexContext->AuthFlag))) {
            continue;
          }

          DEBUG ((DEBUG_INFO, "Updating the variable store with a queued index variable header.\n"));
          CopyMem (
            (VOID *) ((UINT8 *) Data + VariableHeaderWriteOffset),
            (VOID *) &(CseVariableIndexQueueWriteBuffer[Index]->VariableHeader),
            GetVariableHeaderSize (IndexContext->AuthFlag)
            );
        }

        if (
          CseVariableIndexQueueWriteBuffer[Index]->VariableNamePtr != NULL &&
          CseVariableIndexQueueWriteBuffer[Index]->CseVariableStore->Info.Type == CseVariableStorageStore->Info.Type
          ) {
          ASSERT (
            CseVariableIndexQueueWriteBuffer[Index]->VariableHeader.NameSize ==
            StrSize (CseVariableIndexQueueWriteBuffer[Index]->VariableNamePtr)
            );
          VariableHeaderWriteOffset = NVM_HEADER_ALIGN (
                                        (UINT32) (
                                          (UINTN) CseVariableIndexQueueWriteBuffer[Index]->VariableHeaderIndexPtr -
                                          (UINTN) CseVariableIndexQueueWriteBuffer[Index]->CseVariableStore->Info.Header
                                          )
                                        );
          if (
            DataSize >=
            (
              VariableHeaderWriteOffset +
              (
                GetVariableHeaderSize (CseVariableIndexQueueWriteBuffer[Index]->AuthFlag) +
                CseVariableIndexQueueWriteBuffer[Index]->VariableHeader.NameSize
                )
              )
            ) {
            Status =  StrCpyS (
                        (VOID *) GetVariableNamePtr (
                          (VARIABLE_NVM_HEADER *) (
                            (UINT8 *) Data + VariableHeaderWriteOffset
                            ),
                          CseVariableIndexQueueWriteBuffer[Index]->AuthFlag
                          ),
                        (UINTN) CseVariableIndexQueueWriteBuffer[Index]->VariableHeader.NameSize,
                        CseVariableIndexQueueWriteBuffer[Index]->VariableNamePtr
                        );
            ASSERT_EFI_ERROR (Status);
          }
        }
      }
    }
  }

  //
  // Update the current variable header in the index data
  //
  if (IndexContext->VariableHeaderIndexPtr != NULL) {
    VariableHeaderWriteOffset = 0;
    if (IndexContext->VariableStoreIndexPtr != NULL) {
      VariableHeaderWriteOffset = NVM_HEADER_ALIGN (
                                    (UINT32) (
                                      (UINTN) IndexContext->VariableHeaderIndexPtr -
                                      (UINTN) CseVariableStorageStore->Info.Header
                                      )
                                    );
    }
    if (DataSize < (VariableHeaderWriteOffset + sizeof (VARIABLE_NVM_HEADER))) {
      ASSERT (DataSize >= (VariableHeaderWriteOffset + sizeof (VARIABLE_NVM_HEADER)));
      return EFI_BUFFER_TOO_SMALL;
    }
    DEBUG ((DEBUG_INFO, "Updating the variable header in the index data.\n"));
    CopyMem (
      (VOID *) ((UINT8 *) Data + VariableHeaderWriteOffset),
      (VOID *) &(IndexContext->VariableHeader),
      GetVariableHeaderSize (IndexContext->AuthFlag)
      );

    if (IndexContext->VariableNamePtr != NULL) {
      DEBUG ((DEBUG_INFO, "Updating the variable name in the index data.\n"));

      Status =  StrCpyS (
                  GetVariableNamePtr (
                    (VARIABLE_NVM_HEADER *) ((UINT8 *) Data + VariableHeaderWriteOffset),
                    IndexContext->AuthFlag
                    ),
                  IndexContext->VariableHeader.NameSize,
                  IndexContext->VariableNamePtr
                  );
      ASSERT_EFI_ERROR (Status);
    }
  }

  return EFI_SUCCESS;
}

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
  )
{
  UINTN Index;

  if (CseVariableIndexQueueEntries == 0 || CseVariableIndexQueueWriteBuffer == NULL) {
    return NULL;
  }

  for (Index = CseVariableIndexQueueEntries - 1; Index > 0; Index--) {
    if (
      CseVariableStorageIsIndexContextValid (
        CseVariableIndexQueueWriteBuffer[Index],
        RequireValidVariableStore,
        RequireValidVariableHeader,
        RequireValidVariableName
        ) &&
      CseVariableIndexQueueWriteBuffer[Index]->CseVariableStore->Info.Type == CseVariableStorageType
      )
    {
      return CseVariableIndexQueueWriteBuffer[Index];
    }
  }

  return NULL;
}