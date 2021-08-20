/** @file
  CSE Variable Storage General Data Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <CseVariableStorageGeneralDataArea.h>
#include <CseVariableStorageSecurePreMemoryData.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SecurePreMemoryDataInitLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageIoLib.h>
#include <Library/CseVariableStorageLib.h>
#include <Guid/VariableFormat.h>

/**
  Writes a new variable in CSE variable storage.

  @param[in]  This                             Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableInformationTrack         Pointer to a structure that maintains common variable information.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[in]  AuthenticatedVariableFieldTrack  Pointer to a structure which maintains authenticated field values.
  @param[out] CommandInProgress                TRUE if the command requires asynchronous I/O and has not completed yet.
                                               If this command is TRUE, then the Data and DataSize are not updated and do
                                               not contain valid data.

  @retval     EFI_SUCCESS                      The variable write operation was successful.
  @retval     Others                           The variable write operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteNewVariable (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE              *This,
  IN  CONST  CSE_VARIABLE_INFORMATION_TRACK          *VariableInformationTrack,
  IN         VARIABLE_NVM_STORE_INFO                 *VariableStoreInfo,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  *VariableAuthenticatedFieldTrack OPTIONAL,
  OUT        BOOLEAN                                 *CommandInProgress OPTIONAL
  )
{
  EFI_STATUS Status;
  UINTN      NewVariableTotalSize     = 0; ///< The total variable size (header + data)
  UINT32     VariableDataWriteOffset  = 0; ///< The offset from the beginning of the data file to the data
  UINT32     VariablePaddingSize      = 0; ///< Size in bytes of padding to align data to a dword boundary
  UINTN      VariableDataTotalSize    = 0; ///< The total variable data size including alignment padding if applicable
  UINTN      VariableHeaderTotalSize  = 0; ///< The total variable header size including the variable name
  UINTN      VariableIndexWriteOffset = 0; ///< The offset from the beginning of the index file to the variable header

  AUTHENTICATED_VARIABLE_NVM_HEADER   *AuthenticatedVariableHeader     = NULL;
  VARIABLE_NVM_STORE_HEADER           *IndexVariableStoreHeader        = NULL;

  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  IndexContext;
  INT32                               TotalVariableStoreRemainingSize  = 0;

  if (This == NULL || VariableInformationTrack  == NULL || VariableStoreInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = CseVariableStorageInitializeNewVariableContext (This, VariableStoreInfo, &IndexContext, &IndexVariableStoreHeader);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  //
  // Make sure a new variable does not contain invalid attributes
  //
  if (VariableInformationTrack->DataSize == 0 ||
    (VariableInformationTrack->Attributes & (EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS)) == 0
    ) {
    DEBUG ((DEBUG_ERROR, "Invalid attributes specified for a new variable.\n"));
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "A new CSE %a variable is being written.\n", This->Info.Name));

  VariableHeaderTotalSize = GetVariableHeaderSize (IndexContext.AuthFlag) +
                              StrSize (VariableInformationTrack->VariableName) +
                              NVM_GET_PAD_SIZE (StrSize (VariableInformationTrack->VariableName));
  VariableDataTotalSize = VariableInformationTrack->DataSize;
  NewVariableTotalSize = VariableHeaderTotalSize + VariableDataTotalSize;

  //
  // Calculate the space remaining in the variable header region
  //
  TotalVariableStoreRemainingSize = This->Info.MaximumSize -
                                      sizeof (VARIABLE_NVM_STORE_HEADER) -
                                      IndexVariableStoreHeader->VariableHeaderTotalLength -
                                      IndexVariableStoreHeader->VariableDataTotalLength;

  //
  // Check for reclaim conditions
  //
  if (TotalVariableStoreRemainingSize < NewVariableTotalSize) {
    DEBUG ((DEBUG_WARN, "Variable data exceeds available capacity. Attempting to recover space...\n"));

    DEBUG ((DEBUG_INFO, "Variable Store Info Before Reclaim:\n"));
    DEBUG ((DEBUG_INFO, "  Total Header Entries: %d\n", IndexVariableStoreHeader->VariableHeaderTotalEntries));
    DEBUG ((DEBUG_INFO, "  Total Header Length: %d\n",  IndexVariableStoreHeader->VariableHeaderTotalLength));
    DEBUG ((DEBUG_INFO, "  Total Data Length: %d\n",    IndexVariableStoreHeader->VariableDataTotalLength));

    // Perform a reclaim operation to attempt to recover space
    Status = This->Reclaim (This);
    if (Status == EFI_UNSUPPORTED) {
      DEBUG ((DEBUG_WARN, "The reclaim operation cannot occur in this boot phase.\n"));
      return EFI_UNSUPPORTED;
    } else if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "An error occurred in reclaim. The variable could not be updated. Status = %r.\n", Status));
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    DEBUG ((DEBUG_INFO, "Variable Store Info After Reclaim:\n"));
    DEBUG ((DEBUG_INFO, "  Total Header Entries: %d\n", IndexVariableStoreHeader->VariableHeaderTotalEntries));
    DEBUG ((DEBUG_INFO, "  Total Header Length: %d\n",  IndexVariableStoreHeader->VariableHeaderTotalLength));
    DEBUG ((DEBUG_INFO, "  Total Data Length: %d\n",    IndexVariableStoreHeader->VariableDataTotalLength));

    Status = CseVariableStorageInitializeNewVariableContext (This, VariableStoreInfo, &IndexContext, &IndexVariableStoreHeader);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    // Check if enough space is available after the reclaim
    TotalVariableStoreRemainingSize = This->Info.MaximumSize -
                                        sizeof (VARIABLE_NVM_STORE_HEADER) -
                                        IndexVariableStoreHeader->VariableHeaderTotalLength -
                                        IndexVariableStoreHeader->VariableDataTotalLength;

    if (TotalVariableStoreRemainingSize < NewVariableTotalSize) {
        DEBUG ((DEBUG_ERROR, "Cannot save the variable. The CSE variable storage area is at maximum capacity.\n"));
        return EFI_OUT_OF_RESOURCES;
    } else {
      DEBUG ((DEBUG_INFO, "Sufficient capacity exists for the new variable after reclaim.\n"));
    }
  }

  VariableIndexWriteOffset =  NVM_HEADER_ALIGN (
                                (UINTN) IndexContext.VariableHeaderIndexPtr -
                                (UINTN) IndexContext.VariableStoreIndexPtr
                                );

  VariableDataWriteOffset = This->Info.MaximumSize -
                              IndexVariableStoreHeader->VariableDataTotalLength -
                              (UINT32) VariableInformationTrack->DataSize;
  if (IndexVariableStoreHeader->VariableDataTotalLength == 0) {
    VariableDataWriteOffset--;
  }
  VariablePaddingSize = NVM_GET_PAD_SIZE_N (VariableDataWriteOffset);
  VariableDataWriteOffset -= VariablePaddingSize;
  VariableDataTotalSize += VariablePaddingSize;

  DEBUG ((DEBUG_INFO, "New variable total size (header + data + padding): %d bytes.\n", NewVariableTotalSize));
  DEBUG ((DEBUG_INFO, "Size available BEFORE adding the variable:\n"));
  DEBUG ((
    DEBUG_INFO,
    "  Total available in store: %d bytes of maximum %d bytes.\n",
    TotalVariableStoreRemainingSize,
    This->Info.MaximumSize
    ));

  DEBUG ((DEBUG_INFO, "New variable header at memory address 0x%x\n", (UINTN) &IndexContext));

  IndexContext.VariableHeader.StartId    = VARIABLE_DATA;
  IndexContext.VariableHeader.State      = VAR_ADDED;
  IndexContext.VariableHeader.Attributes = VariableInformationTrack->Attributes;
  IndexContext.VariableHeader.DataSize   = (UINT32) VariableInformationTrack->DataSize;
  IndexContext.VariableHeader.NameSize   = (UINT32) StrSize (VariableInformationTrack->VariableName);
  IndexContext.VariableHeader.DataOffset = VariableDataWriteOffset;
  IndexContext.VariableNamePtr           = VariableInformationTrack->VariableName;
  CopyMem (&(IndexContext.VariableHeader.VendorGuid), VariableInformationTrack->VendorGuid, sizeof (EFI_GUID));

  if (IndexContext.AuthFlag) {
    AuthenticatedVariableHeader = &(IndexContext.VariableHeader);

    if (VariableAuthenticatedFieldTrack == NULL) {
      ASSERT (VariableAuthenticatedFieldTrack != NULL);
      return EFI_INVALID_PARAMETER;
    }

    SetAuthenticatedVariableFields (AuthenticatedVariableHeader, VariableAuthenticatedFieldTrack);
  }

  //
  // The EFI_VARIABLE_APPEND_WRITE attribute will never be set in the returned Attributes bitmask.
  //
  IndexContext.VariableHeader.Attributes = IndexContext.VariableHeader.Attributes & (~EFI_VARIABLE_APPEND_WRITE);

  //
  // Update the variable store properties in the variable store header
  //
  CopyMem (
    (VOID *) &(IndexContext.VariableStoreHeader),
    (VOID *) IndexVariableStoreHeader,
    sizeof (VARIABLE_NVM_STORE_HEADER)
    );

  IndexContext.VariableStoreHeader.VariableHeaderTotalEntries++;
  IndexContext.VariableStoreHeader.VariableHeaderTotalLength += (UINT32) VariableHeaderTotalSize;
  IndexContext.VariableStoreHeader.VariableDataTotalLength   += (UINT32) VariableDataTotalSize;
  IndexContext.VariableStoreHeader.Size = sizeof (VARIABLE_NVM_STORE_HEADER) +
                                                   IndexContext.VariableStoreHeader.VariableDataTotalLength +
                                                   IndexContext.VariableStoreHeader.VariableHeaderTotalLength;

  DEBUG ((DEBUG_INFO, "Updated the volatile variable store for the new variable. Current data:\n"));

  DEBUG ((
    DEBUG_INFO,
    "  Total number of variable entries: %d\n",
    IndexContext.VariableStoreHeader.VariableHeaderTotalEntries
    ));
  DEBUG ((
    DEBUG_INFO,
    "  Total size of all variable headers: %d bytes\n",
    IndexContext.VariableStoreHeader.VariableHeaderTotalLength
    ));
  DEBUG ((
    DEBUG_INFO,
    "  Total size of variable data: %d bytes\n",
    IndexContext.VariableStoreHeader.VariableDataTotalLength
  ));

  DEBUG ((DEBUG_INFO, "Writing the data area...\n"));
  Status =  This->Write (
                    This,
                    VariableInformationTrack->Data,
                    VariableInformationTrack->DataSize,
                    (UINTN) VariableDataWriteOffset,
                    FALSE,
                    NULL,
                    CommandInProgress
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Error occurred writing the variable data. Variable not written.\n"));
    return Status;
  }

  DEBUG ((
    DEBUG_INFO,
    "Writing the new variable header to offset 0x%x in the NVM index area.\n",
    VariableIndexWriteOffset
    ));

  DEBUG ((DEBUG_INFO, "Updating the index area...\n"));
  return  CseVariableStorageUpdateIndexArea (
            This,
            &IndexContext,
            (UINT32) VariableIndexWriteOffset,
            (UINT32) VariableHeaderTotalSize,
            CommandInProgress
            );
}

/**
  Updates a variable in CSE variable storage.

  @param[in]  This                             Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableInformationTrack         Pointer to a structure that maintains common variable information.
  @param[in]  VariablePtrTrack                 Pointer to a structure that maintains variable header pointers.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[in]  VariableAuthenticatedFieldTrack  Pointer to a structure which maintains authenticated field values.
  @param[out] CommandInProgress                TRUE if the command requires asynchronous I/O and has not completed yet.
                                               If this command is TRUE, then the Data and DataSize are not updated and do
                                               not contain valid data.

  @retval     EFI_SUCCESS                      The variable update operation was successful.
  @retval     EFI_INVALID_PARAMETER            A pointer given was NULL or pointed to invalid data.
  @retval     EFI_UNSUPPORTED                  The update operation is not valid at this time.
  @retval     Others                           The variable update operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataUpdateVariable (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE              *This,
  IN  CONST  CSE_VARIABLE_INFORMATION_TRACK          *VariableInformationTrack,
  IN  CONST  VARIABLE_NVM_POINTER_TRACK              *VariablePtrTrack,
  IN         VARIABLE_NVM_STORE_INFO                 *VariableStoreInfo,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  *VariableAuthenticatedFieldTrack OPTIONAL,
  OUT        BOOLEAN                                 *CommandInProgress OPTIONAL
  )
{
  EFI_STATUS  Status;
  UINT32      VariableDataWriteOffset  = 0; ///< The offset from the beginning of the data file to the data
  UINTN       VariableHeaderTotalSize  = 0; ///< The total variable header size including the variable name
  UINTN       VariableIndexWriteOffset = 0; ///< The offset from the beginning of the index file to the variable header

  AUTHENTICATED_VARIABLE_NVM_HEADER *AuthenticatedVariableHeader = NULL;

  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  IndexContext;

  if (
    This                        == NULL ||
    VariableInformationTrack    == NULL ||
    VariablePtrTrack            == NULL ||
    VariablePtrTrack->CurrPtr   == NULL ||
    VariablePtrTrack->EndPtr    == NULL ||
    VariableStoreInfo           == NULL
    ) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "A CSE %a variable is being updated.\n", This->Info.Name));

  // Note: Do not check if data already exists on NVM to prevent re-write as HECI I/O is the bottleneck.

  if (!IsValidVariableHeader (VariablePtrTrack->CurrPtr, VariablePtrTrack->EndPtr)) {
    DEBUG ((DEBUG_ERROR, "The existing variable header is not valid.\n"));
    return EFI_INVALID_PARAMETER;
  }
  ASSERT ((UINTN) VariablePtrTrack->CurrPtr > (UINTN) VariableStoreInfo->VariableStoreHeader);

  if (VariablePtrTrack->CurrPtr->DataSize != VariableInformationTrack->DataSize) {
    // Note: Pre-memory file updates with size changes should be handled prior to
    //       this function in the flow: variable delete, reclaim, and new variable addition.
    ASSERT (VariablePtrTrack->CurrPtr->DataSize == VariableInformationTrack->DataSize);
    return EFI_UNSUPPORTED;
  }

  ZeroMem ((VOID *) &IndexContext, sizeof (IndexContext));
  CopyMem (
    (VOID *) &(IndexContext.VariableHeader),
    (VOID *) VariablePtrTrack->CurrPtr,
    GetVariableHeaderSize (VariableStoreInfo->AuthFlag)
    );
  IndexContext.VariableHeaderIndexPtr = (AUTHENTICATED_VARIABLE_NVM_HEADER *) VariablePtrTrack->CurrPtr;
  IndexContext.AuthFlag = VariableStoreInfo->AuthFlag;
  IndexContext.CseVariableStore = This;

  //
  // The EFI_VARIABLE_APPEND_WRITE attribute will never be set in the returned Attributes bitmask.
  //
  IndexContext.VariableHeader.Attributes = VariableInformationTrack->Attributes & (~EFI_VARIABLE_APPEND_WRITE);

  VariableDataWriteOffset = IndexContext.VariableHeader.DataOffset;
  VariableIndexWriteOffset  = NVM_HEADER_ALIGN (
                                ((UINTN) (VariablePtrTrack->CurrPtr) - (UINTN) VariableStoreInfo->VariableStoreHeader)
                                );
  VariableHeaderTotalSize = GetVariableHeaderSize (IndexContext.AuthFlag) +
                              StrSize (VariableInformationTrack->VariableName) +
                              NVM_GET_PAD_SIZE (StrSize (VariableInformationTrack->VariableName));
  if (IndexContext.AuthFlag) {
    AuthenticatedVariableHeader = &(IndexContext.VariableHeader);

    if (VariableAuthenticatedFieldTrack == NULL) {
      return EFI_INVALID_PARAMETER;
    }

    SetAuthenticatedVariableFields (AuthenticatedVariableHeader, VariableAuthenticatedFieldTrack);
  }

  DEBUG ((DEBUG_INFO, "Writing the data area...\n"));
  Status =  This->Write (
                    This,
                    VariableInformationTrack->Data,
                    VariableInformationTrack->DataSize,
                    VariableDataWriteOffset,
                    FALSE,
                    NULL,
                    CommandInProgress
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Error occurred writing the variable data. Variable not updated.\n"));
    return Status;
  }

  DEBUG ((DEBUG_INFO, "Updating the index area...\n"));
  Status =  This->Write (
                    This,
                    (VOID *) VariablePtrTrack->CurrPtr,
                    (UINT32) VariableHeaderTotalSize,
                    (UINT32) VariableIndexWriteOffset,
                    FALSE,
                    &IndexContext,
                    CommandInProgress
                    );
  DEBUG ((DEBUG_INFO, "Variable update is complete. Status = %r.\n", Status));

  return Status;
}

/**
  Deletes a variable in CSE variable storage.

  @param[in]  This                     A pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableStoreInfo        Pointer to a structure that maintains variable store information.
  @param[in]  VariableHeader           Pointer to the variable header that should be deleted.
  @param[out] CommandInProgress        TRUE if the command requires asynchronous I/O and has not completed yet.
                                       If this command is TRUE, then the Data and DataSize are not updated and do
                                       not contain valid data.

  @retval     EFI_SUCCESS              The variable was deleted successfully.
  @retval     EFI_INVALID_PARAMETER    The pointers given to the function are NULL or invalid.
  @retval     Others                   The variable deletion operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataDeleteVariable (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE *This,
  IN  CONST  VARIABLE_NVM_STORE_INFO    *VariableStoreInfo,
  IN         VARIABLE_NVM_HEADER        *VariableHeader,
  OUT        BOOLEAN                    *CommandInProgress OPTIONAL
  )
{
  UINT32                              VariableIndexWriteOffset  = 0;
  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  IndexContext;

  if (This == NULL || VariableStoreInfo == NULL || VariableHeader == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  VariableIndexWriteOffset =  NVM_HEADER_ALIGN (
                                (UINT32) (
                                  (UINTN) (VariableHeader) -
                                  (UINTN) VariableStoreInfo->VariableStoreHeader)
                                  );

  DEBUG ((DEBUG_INFO, "Deleting a variable in the %a CSE storage store.\n", This->Info.Name));
  DEBUG ((
    DEBUG_INFO,
    "  Total data length before delete = %d bytes. Data size of deleted variable = %d bytes.\n",
    VariableStoreInfo->VariableStoreHeader->VariableDataTotalLength,
    VariableHeader->DataSize
    ));

  // Note: Variable store data size properties are not updated until the reclaim operation.
  // Note: VariableHeaderTotalEntries is not readjusted until the reclaim operation as the variable headers are still
  //       present in the variable store after deletion.

  ZeroMem ((VOID *) &IndexContext, sizeof (IndexContext));
  IndexContext.AuthFlag = VariableStoreInfo->AuthFlag;
  IndexContext.CseVariableStore = This;
  IndexContext.VariableHeaderIndexPtr = (AUTHENTICATED_VARIABLE_NVM_HEADER *) VariableHeader;
  CopyMem (
    (VOID *) &(IndexContext.VariableHeader),
    (VOID *) VariableHeader,
    GetVariableHeaderSize (IndexContext.AuthFlag)
    );
  IndexContext.VariableHeader.State &= VAR_DELETED;

  return  This->Write (
                  This,
                  VariableHeader,
                  GetVariableHeaderSize (IndexContext.AuthFlag),
                  VariableIndexWriteOffset,
                  FALSE,
                  &IndexContext,
                  CommandInProgress
                  );
}

/**
  Creates an empty UEFI variable store in the CSE Variable Storage area.

  @param[in,out]  This                        A pointer to a structure that contains CSE variable storage store info.
  @param[out]     VariableStore               A pointer to the caller allocated buffer for the variable store.
  @param[in,out]  VariableStoreBufferLength   The size in bytes of the buffer available on input.
                                              The size in bytes of the variable store created on output.

  @retval         EFI_SUCCESS                 The variable store was created successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        VariableStoreBufferLength is too small to hold a variable store.
  @retval         Others                      A different error occurred attempting to create the variable store.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataAreaCreateVariableStore (
  IN OUT  CSE_VARIABLE_STORAGE_STORE *This,
  OUT     VOID                       *VariableStore,
  IN OUT  UINTN                      *VariableStoreBufferLength
  )
{
  EFI_STATUS  Status;
  VARIABLE_NVM_STORE_HEADER   *VariableStoreHeader;

  if (This == NULL || VariableStore == NULL || VariableStoreBufferLength == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (*VariableStoreBufferLength < sizeof (VARIABLE_NVM_STORE_HEADER)) {
    return EFI_BUFFER_TOO_SMALL;
  }

  VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) VariableStore;
  Status = GetEmptyVariableStore (VariableStoreHeader);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *VariableStoreBufferLength = (UINTN) VariableStoreHeader->Size;
  return  This->Write (
                  This,
                  VariableStore,
                  *VariableStoreBufferLength,
                  0,
                  TRUE,
                  NULL,
                  NULL
                  );
}

/**
  Creates an empty UEFI variable store in the CSE Variable Storage area.

  SPMD has special conditions to also set up the SPMD table when the store is initialized:
  - VariableStore should point to the beginning of a buffer which will contain the variable store (excluding SPMD header).
  - The CSE_VARIABLE_STORAGE_STORE offset should be set to the variable store offset taking the SPMD header into account.
  - The VariableStoreBufferLength return value will not include the SPMD table header size.

  @param[in]      This                        A pointer to a structure that contains CSE variable storage store info.
  @param[out]     VariableStore               A pointer to the caller allocated buffer for the variable store.
  @param[in,out]  VariableStoreBufferLength   The size in bytes of the buffer available on input.
                                              The size in bytes of the variable store created on output.

  @retval         EFI_SUCCESS                 The variable store was created successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        VariableStoreBufferLength is too small to hold a variable store.
  @retval         Others                      A different error occurred attempting to create the variable store.
**/
EFI_STATUS
EFIAPI
CseVariableStorageSpmdAreaCreateVariableStore (
  IN OUT  CSE_VARIABLE_STORAGE_STORE  *This,
  OUT     VOID                        *VariableStore,
  IN OUT  UINTN                       *VariableStoreBufferLength
  )
{
  EFI_STATUS                        Status;
  SECURE_PRE_MEMORY_DATA_TABLE      SpmdTable;
  VARIABLE_NVM_STORE_HEADER         *VariableStoreHeader;
  UINT32                            BackupOffset;

  if (This == NULL || VariableStore == NULL || VariableStoreBufferLength == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (This->Info.Offset < sizeof (SECURE_PRE_MEMORY_DATA_TABLE)) {
    DEBUG ((DEBUG_ERROR, "The variable store must proceed the SPMD header. The offset is not large enough.\n"));
    return EFI_BUFFER_TOO_SMALL;
  } else if (*VariableStoreBufferLength < (sizeof (VARIABLE_NVM_STORE_HEADER) + sizeof (SECURE_PRE_MEMORY_DATA_TABLE))) {
    DEBUG ((DEBUG_ERROR, "The buffer is not large enough to accommodate the SPMD header and a variable store.\n"));
    return EFI_BUFFER_TOO_SMALL;
  }

  Status = GetNewSecurePreMemoryDataTable (&SpmdTable);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred creating the SPMD table.\n"));
    return Status;
  }
  VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) VariableStore;

  Status = GetEmptyVariableStore (VariableStoreHeader);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred getting an empty variable store.\n"));
    return Status;
  }

  BackupOffset = This->Info.Offset;
  This->Info.Offset -= sizeof (SECURE_PRE_MEMORY_DATA_TABLE);
  Status =  This->Write (
                    This,
                    (VOID *) &SpmdTable,
                    sizeof (SECURE_PRE_MEMORY_DATA_TABLE),
                    0,
                    TRUE,
                    NULL,
                    NULL
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  This->Info.Offset = BackupOffset;

  *VariableStoreBufferLength = (UINTN) VariableStoreHeader->Size;
  Status =  This->Write (
                    This,
                    VariableStore,
                    *VariableStoreBufferLength,
                    0,
                    TRUE,
                    NULL,
                    NULL
                    );


  return Status;
}

/**
  Initializes the Secure Pre-Memory Data area storage store.

  @param[out]     This              A pointer to a CSE variable storage store.

  @retval         EFI_SUCCESS       The CSE variable storage store was initialized successfully.
  @retval         Others            An error occurred initializing the CSE variable storage store structure.

**/
EFI_STATUS
EFIAPI
InitializeCseVariableStorageSecurePreMemoryDataArea (
  OUT CSE_VARIABLE_STORAGE_STORE   *This
  )
{
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem (
    (VOID *) &(This->Info.Guid),
    &gCseVariableStorageSecurePreMemoryDataGuid,
    sizeof (EFI_GUID)
    );

  This->Info.Type                 = CseVariableStorageTypeSecurePreMemoryArea;
  This->Info.Enabled              = CSE_VARIABLE_STORAGE_SECURE_PRE_MEMORY_DATA_ENABLED;
  This->Info.Established          = FALSE;
  This->Info.DataExpansionAllowed = FALSE;
  This->Info.MaximumSize          = SECURE_PRE_MEMORY_DATA_MAX_DATA_LENGTH;
  This->Info.Offset               = CSE_VARIABLE_STORAGE_SECURE_PRE_MEMORY_DATA_STORE_OFFSET;
  This->Info.Header               = NULL;
  This->Info.Data                 = NULL;
  This->Info.Name                 = "Secure Pre-Memory Data";
  This->Info.OtherInfo            = NULL;

  This->Read             = CseVariableStorageGeneralDataRead;
  This->Write            = CseVariableStorageGeneralDataWrite;
  This->CreateNewStore   = CseVariableStorageSpmdAreaCreateVariableStore;
  This->Reclaim          = CseVariableStorageGeneralDataReclaim;
  This->WriteNewVariable = CseVariableStorageGeneralDataWriteNewVariable;
  This->UpdateVariable   = CseVariableStorageGeneralDataUpdateVariable;
  This->DeleteVariable   = CseVariableStorageGeneralDataDeleteVariable;

  return EFI_SUCCESS;
}

/**
  Initializes the General Data area storage store.

  @param[out]     This          A pointer to a CSE variable storage store.

  @retval         EFI_SUCCESS   The CSE variable storage store was initialized successfully.
  @retval         Others        An error occurred initializing the CSE variable storage store structure.

**/
EFI_STATUS
EFIAPI
InitializeCseVariableStorageGeneralDataArea (
  OUT CSE_VARIABLE_STORAGE_STORE   *This
  )
{
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem ((VOID *) &(This->Info.Guid), &gCseVariableStorageGeneralDataAreaGuid, sizeof (EFI_GUID));

  This->Info.Type                 = CseVariableStorageTypeGeneralDataArea;
  This->Info.Enabled              = CSE_VARIABLE_STORAGE_GENERAL_DATA_ENABLED;
  This->Info.Established          = FALSE;
  This->Info.DataExpansionAllowed = FALSE;
  This->Info.MaximumSize          = CSE_VARIABLE_STORAGE_GENERAL_DATA_MAXIMUM_SIZE;
  This->Info.Offset               = CSE_VARIABLE_STORAGE_GENERAL_DATA_AREA_STORE_OFFSET;
  This->Info.Header               = NULL;
  This->Info.Data                 = NULL;
  This->Info.Name                 = "General Data";
  This->Info.OtherInfo            = NULL;

  This->Read             = CseVariableStorageGeneralDataRead;
  This->Write            = CseVariableStorageGeneralDataWrite;
  This->CreateNewStore   = CseVariableStorageGeneralDataAreaCreateVariableStore;
  This->Reclaim          = CseVariableStorageGeneralDataReclaim;
  This->WriteNewVariable = CseVariableStorageGeneralDataWriteNewVariable;
  This->UpdateVariable   = CseVariableStorageGeneralDataUpdateVariable;
  This->DeleteVariable   = CseVariableStorageGeneralDataDeleteVariable;

  return EFI_SUCCESS;
}