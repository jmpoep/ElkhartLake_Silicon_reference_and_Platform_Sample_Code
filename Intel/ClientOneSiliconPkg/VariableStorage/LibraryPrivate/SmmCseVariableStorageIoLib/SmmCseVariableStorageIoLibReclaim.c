/** @file
  SMM CSE Variable Storage General Data Reclaim Implementation

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

#include "CseVariableStorageIoSmm.h"
#include <Library/VariableNvmStorageLib.h>

extern CSE_VARIABLE_STORAGE_INDEX_CONTEXT   *mCseIndexQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern UINTN                                mCseCommandQueueWriteRequestProducerIndex;

/**
  Reclaims a CSE Variable Storage General Data store.

  @param[in]      CseVariableStorageStore   A pointer to a structure CSE Variable Storage Store structure.

  @retval         EFI_SUCCESS               The reclaim operation was successful.
  @retval         EFI_UNSUPPORTED           A reclaim operation is not available for this CSE storage store.
  @retval         EFI_INVALID_PARAMETER     A pointer given to the function is NULL.
  @retval         EFI_NOT_READY             The CSE variable store used for the reclaim operation is not available.
  @retval         EFI_OUT_OF_RESOURCES      The memory resources available are insufficient for the reclaim operation.
  @retval         EFI_LOAD_ERROR            An error occurred loading data via CSE from non-volatile memory.
  @retval         Others                    The pre-memory file reclaim operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReclaim (
  IN CONST CSE_VARIABLE_STORAGE_STORE       *CseVariableStorageStore
  )
{
  EFI_STATUS                         Status;
  UINTN                              DataSize                    = 0;
  UINTN                              TotalBufferSize             = 0;
  UINTN                              TotalDataProcessed          = 0;
  UINTN                              VariableHeaderTotalSize     = 0;
  BOOLEAN                            ReadCommandQueueEnabled     = FALSE;

  CHAR16                             *VariableName               = NULL;
  UINT8                              *ReclaimBuffer              = NULL;
  UINT8                              *SourceBuffer               = NULL;
  UINT8                              *VariableDestPtr            = NULL;
  UINT8                              *VariableDestDataPtr        = NULL;
  UINT8                              *VariableSourceDataPtr      = NULL;
  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *LastQueuedIndexContext     = NULL;
  VARIABLE_NVM_HEADER                *NextVariable               = NULL;
  VARIABLE_NVM_HEADER                *VariableSourcePtr          = NULL;
  VARIABLE_NVM_STORE_HEADER          *ReclaimBufferStoreHeader   = NULL;

  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  IndexContext;
  VARIABLE_NVM_STORE_INFO             SourceVariableStoreInfo;

  DEBUG ((
    DEBUG_WARN,
    "Variable reclaim operation invoked on the %a CSE variable store...\n",
    CseVariableStorageStore->Info.Name
    ));

  if (
    (CseVariableStorageStore == NULL) ||
    (
      CseVariableStorageStore->Info.Type != CseVariableStorageTypeSecurePreMemoryArea &&
      CseVariableStorageStore->Info.Type != CseVariableStorageTypeGeneralDataArea
      )
    ) {
    return EFI_INVALID_PARAMETER;
  } else if (!CseVariableStorageStore->Info.Enabled || !CseVariableStorageStore->Info.Established) {
    return EFI_NOT_READY;
  }

  TotalBufferSize = (UINTN) CseVariableStorageStore->Info.MaximumSize;
  ASSERT (TotalBufferSize > 0);

  //
  // Allocate a source and reclaim buffer as the working reclaim area
  //
  SourceBuffer = AllocateZeroPool (TotalBufferSize);
  if (SourceBuffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  ReclaimBuffer = AllocateZeroPool (TotalBufferSize);
  if (ReclaimBuffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  DEBUG ((DEBUG_INFO, "TotalBufferSize:  0x%x.\n", TotalBufferSize));
  DEBUG ((DEBUG_INFO, "SourceBuffer at:  0x%x.\n", (UINTN) SourceBuffer));
  DEBUG ((DEBUG_INFO, "ReclaimBuffer at: 0x%x.\n", (UINTN) ReclaimBuffer));

  //
  // Populate the source buffer with the pre-memory file contents
  //

  //
  // Disable the command queue to improve read performance and immediately return data.
  // If CSE cannot service reads without proxy support this cannot be done.
  //
  ReadCommandQueueEnabled = CseVariableStorageIsReadCommandQueueEnabled ();
  CseVariableStorageDisableReadCommandQueue ();
  while (TotalDataProcessed < TotalBufferSize) {
    if ((TotalBufferSize - TotalDataProcessed) > CSE_VARIABLE_MAX_DMA_SIZE) {
      DataSize = CSE_VARIABLE_MAX_DMA_SIZE;
    } else {
      DataSize = TotalBufferSize - TotalDataProcessed;
    }

    Status = CseVariableStorageStore->Read (
                                        CseVariableStorageStore,
                                        (VOID *) (SourceBuffer + TotalDataProcessed),
                                        &DataSize,
                                        (UINT32) TotalDataProcessed,
                                        NULL
                                        );
    if (EFI_ERROR (Status)) {
      DEBUG ((
        DEBUG_ERROR,
        "Error occurred reading from the %a CSE variable store. Reclaim operation aborted. Status = %r.\n",
        CseVariableStorageStore->Info.Name,
        Status
        ));
      ASSERT_EFI_ERROR (Status);
      goto Done;
    }

    TotalDataProcessed += DataSize;
  }
  if (ReadCommandQueueEnabled) {
    CseVariableStorageEnableReadCommandQueue ();
  }

  ZeroMem (&IndexContext, sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT));
  IndexContext.CseVariableStore       = CseVariableStorageStore;
  IndexContext.VariableHeaderIndexPtr = NULL;
  IndexContext.VariableNamePtr        = NULL;
  IndexContext.VariableStoreIndexPtr  = (VARIABLE_NVM_STORE_HEADER *) CseVariableStorageStore->Info.Header;
  ASSERT (GetVariableStoreStatus (IndexContext.VariableStoreIndexPtr) == EfiValid);

  LastQueuedIndexContext =  CseVariableStorageGetLastIndexQueueEntry (
                              CseVariableStorageStore->Info.Type,
                              mCseIndexQueueWriteBuffer,
                              mCseCommandQueueWriteRequestProducerIndex,
                              TRUE,
                              FALSE,
                              FALSE
                              );
  if (LastQueuedIndexContext != NULL) {
    DEBUG ((DEBUG_INFO, "Last queued index entry found.\n"));
    CopyMem (
      (VOID *) &(IndexContext.VariableStoreHeader),
      (VOID *) &(LastQueuedIndexContext->VariableStoreHeader),
      sizeof (VARIABLE_NVM_STORE_HEADER)
      );
  } else {
    DEBUG ((DEBUG_INFO, "Last queued index entry not found.\n"));
    CopyMem (
      (VOID *) &(IndexContext.VariableStoreHeader),
      (VOID *) SourceBuffer,
      sizeof (VARIABLE_NVM_STORE_HEADER)
      );
  }
  ASSERT (GetVariableStoreStatus (&(IndexContext.VariableStoreHeader)) == EfiValid);

  Status =  IsAuthenticatedVariableStore (
              (CONST VARIABLE_NVM_STORE_HEADER *) CseVariableStorageStore->Info.Header,
              &IndexContext.AuthFlag
              );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    goto Done;
  }

  //
  // Replay any queued index updates onto SourceBuffer
  //
  Status =  CseVariableStorageIoUpdateDataWithContext (
              CseVariableStorageStore,
              mCseIndexQueueWriteBuffer,
              mCseCommandQueueWriteRequestProducerIndex,
              (VOID *) SourceBuffer,
              TotalDataProcessed,
              &IndexContext
              );

  SourceVariableStoreInfo.VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) SourceBuffer;
  SourceVariableStoreInfo.AuthFlag = IndexContext.AuthFlag;

  //
  // Copy the variable store header
  //
  CopyMem ((VOID *) ReclaimBuffer, (VOID *) SourceVariableStoreInfo.VariableStoreHeader, sizeof (VARIABLE_NVM_STORE_HEADER));

  ReclaimBufferStoreHeader = (VARIABLE_NVM_STORE_HEADER *) ReclaimBuffer;
  VariableDestPtr = (UINT8 *) GetStartPointer (ReclaimBufferStoreHeader);

  //
  // Initialize new variable store properties subject to change
  //
  ReclaimBufferStoreHeader->VariableDataTotalLength    = 0;
  ReclaimBufferStoreHeader->VariableHeaderTotalEntries = 0;
  ReclaimBufferStoreHeader->VariableHeaderTotalLength  = 0;

  //
  // Reinstall all valid (active) variables
  //
  VariableSourcePtr = GetStartPointer (SourceVariableStoreInfo.VariableStoreHeader);
  VariableDestDataPtr = (UINT8 *) (
                          (UINTN) ReclaimBuffer +
                          (UINTN) CseVariableStorageStore->Info.MaximumSize -
                          1
                          );

  while (IsValidVariableHeader (VariableSourcePtr, GetEndPointer (SourceVariableStoreInfo.VariableStoreHeader))) {
    NextVariable = GetNextVariablePtr (&SourceVariableStoreInfo, VariableSourcePtr);

    if (VariableSourcePtr->State == VAR_ADDED || VariableSourcePtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
      VariableHeaderTotalSize = (UINTN) NextVariable - (UINTN) VariableSourcePtr;

      VariableSourceDataPtr = (UINT8 *) ((UINTN) SourceVariableStoreInfo.VariableStoreHeader + (UINTN) VariableSourcePtr->DataOffset);
      VariableDestDataPtr -= VariableSourcePtr->DataSize;
      VariableDestDataPtr -= NVM_GET_PAD_SIZE_N ((UINTN) VariableDestDataPtr);

      // Copy variable header
      CopyMem (VariableDestPtr, VariableSourcePtr, VariableHeaderTotalSize);
      ((VARIABLE_NVM_HEADER *) VariableDestPtr)->DataOffset = (UINT32) (
                                                                (UINTN) VariableDestDataPtr -
                                                                (UINTN) ReclaimBufferStoreHeader
                                                                );

      VariableDestPtr += VariableHeaderTotalSize;

      // Copy variable data
      CopyMem (VariableDestDataPtr, VariableSourceDataPtr, VariableSourcePtr->DataSize);

      // Update variable store properties
      VariableName = GetVariableNamePtr (VariableSourcePtr, SourceVariableStoreInfo.AuthFlag);

      ReclaimBufferStoreHeader->VariableHeaderTotalEntries++;
      ReclaimBufferStoreHeader->VariableDataTotalLength += (UINT32) (
                                                             VariableSourcePtr->DataSize +
                                                             NVM_GET_PAD_SIZE_N (VariableSourcePtr->DataSize)
                                                             );
      ReclaimBufferStoreHeader->VariableHeaderTotalLength += (UINT32) (
                                                               GetVariableHeaderSize (SourceVariableStoreInfo.AuthFlag) +
                                                               StrSize (VariableName) +
                                                               NVM_GET_PAD_SIZE (StrSize (VariableName))
                                                               );
    }
    VariableSourcePtr = NextVariable;
  }

  TotalDataProcessed = 0;
  while (TotalDataProcessed < TotalBufferSize) {
    if ((TotalBufferSize - TotalDataProcessed) > CSE_VARIABLE_MAX_DMA_SIZE) {
      DataSize = CSE_VARIABLE_MAX_DMA_SIZE;
    } else {
      DataSize = TotalBufferSize - TotalDataProcessed;
    }

    Status = CseVariableStorageStore->Write (
                                        CseVariableStorageStore,
                                        (VOID *) (ReclaimBuffer + TotalDataProcessed),
                                        DataSize,
                                        (UINT32) TotalDataProcessed,
                                        TRUE,
                                        NULL,
                                        NULL
                                        );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Error occurred updating the %a CSE variable store after reclaim. Status = %r.\n", Status));
      ASSERT_EFI_ERROR (Status);
      goto Done;
    }

    CopyMem (
      (VOID *) ((UINT8 *) CseVariableStorageStore->Info.Header + TotalDataProcessed),
      (VOID *) (ReclaimBuffer + TotalDataProcessed),
      DataSize
      );

    TotalDataProcessed += DataSize;
  }

Done:
  if (ReclaimBuffer != NULL) {
    FreePool (ReclaimBuffer);
  }
  if (SourceBuffer != NULL) {
    FreePool (SourceBuffer);
  }

  return Status;
}
