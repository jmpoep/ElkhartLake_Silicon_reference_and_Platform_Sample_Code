/** @file
  Implements CSE Variable Storage Services and installs
  an instance of the VariableStorage Runtime DXE protocol.

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

#include "CseVariableStorageInternal.h"
#include <CseVariableStorage.h>
#include <CseVariableStorageCommandQueue.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageInitLib.h>
#include <Library/CseVariableStorageIoLib.h>
#include <Library/CseVariableStorageLib.h>
#include <Library/CseVariableStorageSelectorLib.h>

CSE_VARIABLE_STORAGE_STORE  *mCseVariableStorageStores[CseVariableStorageTypeMax];

AUTHENTICATED_VARIABLE_NVM_HEADER               *mCurrentGetVariableHeader;
extern EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL  *mVariableStorageSupportProtocol;

EDKII_VARIABLE_STORAGE_PROTOCOL mCseVariableStorageProtocol = {
  CseVariableStorageGetId,
  CseVariableStorageGetVariable,
  CseVariableStorageGetAuthenticatedVariable,
  CseVariableStorageGetNextVariableName,
  CseVariableStorageGetStorageUsage,
  CseVariableStorageGetAuthenticatedSupport,
  CseVariableStorageSetVariable,
  CseVariableStorageWriteServiceIsReady,
  CseVariableStorageGarbageCollect,
  CseVariableStorageAsyncIoRequired
};
CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL mCseVarStorageSupportProtocol = {
  CseVariableStorageReadIoComplete,
  CseVariableStorageRuntimeInitialized
};

/**
  CSE Variable Storage Update Cache.

  @param[in]      None.

  @retval         EFI_SUCCESS               The update operation was successful.
  @retval         EFI_OUT_OF_RESOURCES      Unable to allocate required memory space.
  @retval         EFI_ABORTED               The Cse read operation could not be completed successfully.
  @retval         Others                    An error occurred updating the data.
**/
EFI_STATUS
EFIAPI
CseVariableStorageUpdateCache (
  VOID
)
{
  EFI_STATUS                         Status = EFI_SUCCESS;
  UINT8                              *SourceBuffer = NULL;
  UINT8                              *VariableSourceDataPtr = NULL;
  VARIABLE_NVM_HEADER                *NextVariable = NULL;
  VARIABLE_NVM_HEADER                *VariableSourcePtr = NULL;
  VARIABLE_NVM_STORE_INFO            SourceVariableStoreInfo;
  CSE_VARIABLE_STORAGE_TYPE          Type;
  UINTN                              DataSize;
  UINTN                              VariableStoreHeaderRegionSize;

  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    DEBUG ((DEBUG_INFO, "CseVariableStorageUpdateCache for Type %a Started \n",mCseVariableStorageStores[Type]->Info.Name));

    if ((mCseVariableStorageStores[Type]->Info.Header == NULL) || (mCseVariableStorageStores[Type]->Info.Data == NULL)) {
      DEBUG ((DEBUG_INFO, "Cse Variable  Info storage Header or Data area is NULL \n"));
      return EFI_ABORTED;
    }
    //
    // Allocate a source to hold the Cse Variable data
    //
    SourceBuffer = AllocateZeroPool (mCseVariableStorageStores[Type]->Info.MaximumSize);
    if (SourceBuffer == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      ASSERT_EFI_ERROR (Status);
    }

    if (SourceBuffer != NULL) {
      SourceVariableStoreInfo.VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) mCseVariableStorageStores[Type]->Info.Header;
      if ((GetVariableStoreStatus (SourceVariableStoreInfo.VariableStoreHeader) == EfiValid) && (SourceVariableStoreInfo.VariableStoreHeader->VariableHeaderTotalEntries != 0)) {
        //
        //  Variable Store Header and Index area will be already read during Variable store
        //  establish stage. Skip reading the same from cse and read only Variable Index data read
        //
        VariableStoreHeaderRegionSize = sizeof (VARIABLE_NVM_STORE_HEADER) + SourceVariableStoreInfo.VariableStoreHeader->VariableHeaderTotalLength +
          NVM_GET_PAD_SIZE (SourceVariableStoreInfo.VariableStoreHeader->VariableHeaderTotalLength);
        //
        // Copy Variable Store header and Variable Index header data
        //
        CopyMem(SourceBuffer, (UINT8 *)((UINTN) SourceVariableStoreInfo.VariableStoreHeader), VariableStoreHeaderRegionSize);
        //
        // Copy Variable Data Area
        //
        CopyMem( (UINT8 *) (SourceBuffer + VariableStoreHeaderRegionSize), (UINT8 *)((UINTN)(mCseVariableStorageStores[Type]->Info.Data)), (((UINTN) mCseVariableStorageStores[Type]->Info.MaximumSize) - VariableStoreHeaderRegionSize));

        //
        // Read Cse Variable store and update in the cache
        //
        SourceVariableStoreInfo.VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) SourceBuffer;
        IsAuthenticatedVariableStore (SourceVariableStoreInfo.VariableStoreHeader, &SourceVariableStoreInfo.AuthFlag);

        VariableSourcePtr = GetStartPointer (SourceVariableStoreInfo.VariableStoreHeader);

        while (IsValidVariableHeader (VariableSourcePtr, GetEndPointer (SourceVariableStoreInfo.VariableStoreHeader))) {
          NextVariable = GetNextVariablePtr (&SourceVariableStoreInfo, VariableSourcePtr);

          if (VariableSourcePtr->State == VAR_ADDED || VariableSourcePtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
            VariableSourceDataPtr = AllocateZeroPool (VariableSourcePtr->DataSize);
            CopyMem (
              VariableSourceDataPtr,
              (UINT8 *)((UINTN)SourceVariableStoreInfo.VariableStoreHeader + (UINTN)VariableSourcePtr->DataOffset),
              VariableSourcePtr->DataSize
              );
            DataSize = VariableSourcePtr->DataSize;
            mCurrentGetVariableHeader = (AUTHENTICATED_VARIABLE_NVM_HEADER *) VariableSourcePtr;
            DEBUG ((
              DEBUG_INFO,
              "Updating Variable : %s  \n",
              GetVariableNamePtr ((VARIABLE_NVM_HEADER *) mCurrentGetVariableHeader, SourceVariableStoreInfo.AuthFlag)
              ));

            Status = mVariableStorageSupportProtocol->UpdateNvCache (
                       GetVariableNamePtr(
                         (VARIABLE_NVM_HEADER *) mCurrentGetVariableHeader,
                         SourceVariableStoreInfo.AuthFlag
                         ),
                       &mCurrentGetVariableHeader->VendorGuid,
                       VariableSourceDataPtr,
                       DataSize,
                       mCurrentGetVariableHeader->Attributes,
                       mCurrentGetVariableHeader->PubKeyIndex,
                       mCurrentGetVariableHeader->MonotonicCount,
                       &mCurrentGetVariableHeader->TimeStamp
                       );

             mCurrentGetVariableHeader = NULL;
             FreePool (VariableSourceDataPtr);
          }
          VariableSourcePtr = NextVariable;
        }
      }
    }
  }

  if (SourceBuffer != NULL) {
    FreePool (SourceBuffer);
  }
  if (mCseVariableStorageStores[Type]->Info.Data != NULL) {
    FreePool (mCseVariableStorageStores[Type]->Info.Data);
    mCseVariableStorageStores[Type]->Info.Data = NULL;
  }
  return Status;
}

/**
  Performs common initialization needed for this module.

  @param  None

  @retval EFI_SUCCESS  The module was initialized successfully.
  @retval Others       The module could not be initialized.
**/
EFI_STATUS
EFIAPI
CseVariableStorageCommonInitialize (
  VOID
  )
{
  EFI_STATUS                 Status;
  CSE_VARIABLE_STORAGE_TYPE  Type;

  //
  // Allocate and initialize CSE variable store data structures
  //
  Status = InitializeCseVariableStorage (mCseVariableStorageStores);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Error returned from InitializeCseVariableStorage() - %r.\n", Status));
    return Status;
  }

  //
  // Establish (load index into memory and write new store if necessary) the CSE variable stores
  //
  Status = EstablishAndLoadCseVariableStores (mCseVariableStorageStores);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Error returned from EstablishAndLoadCseVariableStores() - %r.\n", Status));
    return Status;
  }

  DEBUG_CODE_BEGIN ();
  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    DEBUG ((
      EFI_D_INFO,
      "CSE %a Variable Store:\n  Enabled: %c\n  Established: %c\n  Maximum Size: 0x%x\n  Header: 0x%x\n",
      mCseVariableStorageStores[Type]->Info.Name,
      (mCseVariableStorageStores[Type]->Info.Enabled ? 'T' : 'F'),
      (mCseVariableStorageStores[Type]->Info.Established ? 'T' : 'F'),
      mCseVariableStorageStores[Type]->Info.MaximumSize,
      (UINTN) mCseVariableStorageStores[Type]->Info.Header
      ));
  }
  DEBUG_CODE_END ();

  return EFI_SUCCESS;
}

/**
  Notifies the CSE variable driver that the previously requested asynchronous Read I/O operation is complete.

  @param[in]  Status  The result of the variable I/O operation. Possible values are:
                        EFI_SUCCESS             The variable I/O completed successfully.
                        EFI_NOT_FOUND           The variable was not found.
                        EFI_DEVICE_ERROR        The variable I/O could not complete due to a hardware error.
                        EFI_SECURITY_VIOLATION  The variable I/O could not complete due to an authentication failure.
  @param[in]  Data                              A pointer to the data buffer with data from the read operation.
  @param[in]  DataSize                          The total size of variable data in bytes.

**/
VOID
EFIAPI
CseVariableStorageReadIoComplete (
  IN      EFI_STATUS        Status,
  IN      VOID              *Data,
  IN      UINTN             VariableSize
  )
{
  if (mCurrentGetVariableHeader == NULL) {
    return;
  } else if (Data == NULL || VariableSize == 0) {
    mCurrentGetVariableHeader = NULL;
    return;
  }

  if (!EFI_ERROR (Status)) {
    Status = mVariableStorageSupportProtocol->UpdateNvCache (
                                                GetVariableNamePtr (
                                                  (VARIABLE_NVM_HEADER *) mCurrentGetVariableHeader,
                                                  TRUE
                                                  ),
                                                &mCurrentGetVariableHeader->VendorGuid,
                                                Data,
                                                VariableSize,
                                                mCurrentGetVariableHeader->Attributes,
                                                mCurrentGetVariableHeader->PubKeyIndex,
                                                mCurrentGetVariableHeader->MonotonicCount,
                                                &mCurrentGetVariableHeader->TimeStamp
                                                );
  }
  mCurrentGetVariableHeader = NULL;
}

/**
  Deletes a variable and performs a reclaim operation.

  This is often needed when a variable is updated with a new size due to the packing format of the variable data.

  @param[in]  CseVariableStorageStore  Pointer to the CSE variable storage info structure.
  @param[in]  VariableStoreInfo        Pointer to a structure that maintains variable store information.
  @param[in]  VariableHeader           Pointer to the variable header to be deleted and reclaimed.

  @retval     EFI_SUCCESS              The delete and reclaim operation was successful.
  @retval     EFI_INVALID_PARAMETER    A pointer given to the function is NULL or invalid.
  @retval     Others                   The delete and reclaim operation failed.
**/
EFI_STATUS
EFIAPI
DeleteAndReclaimVariable (
  IN CONST    CSE_VARIABLE_STORAGE_STORE        *CseVariableStorageStore,
  IN CONST    VARIABLE_NVM_STORE_INFO           *VariableStoreInfo,
  IN          VARIABLE_NVM_HEADER               *VariableHeader
  )
{
  EFI_STATUS  Status;

  if (CseVariableStorageStore == NULL || VariableStoreInfo == NULL || VariableHeader == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = CseVariableStorageStore->DeleteVariable (CseVariableStorageStore, VariableStoreInfo, VariableHeader, NULL);
  if (!EFI_ERROR (Status)) {
    Status = CseVariableStorageStore->Reclaim (CseVariableStorageStore);
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((
      DEBUG_ERROR,
      "An error occurred during the %a CSE variable storage delete and reclaim operation.\n",
      CseVariableStorageStore->Info.Name
      ));
  }

  return Status;
}

/**
  Recycles a variable.

  A variable is recycled when it is added while in the deleted state. The goal is to minimize the need for reclaim
  operations when possible.

  @param[in]  CseVariableStorageStore          Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableInformationTrack         Pointer to a structure that maintains common variable information.
  @param[in]  RecycledVariablePtrTrack         Pointer to a structure that maintains variable header pointers.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[in]  VariableAuthenticatedFieldTrack  Pointer to a structure which maintains authenticated field values.
  @param[out] CommandInProgress                TRUE if the command requires asynchronous I/O and has not completed yet.
                                               If this command is TRUE, then the Data and DataSize are not updated and do
                                               not contain valid data.

  @retval     EFI_SUCCESS                      The recycle operation was successful.
  @retval     Others                           The recycle operation failed.
**/
EFI_STATUS
EFIAPI
RecycleVariable (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE              *CseVariableStorageStore,
  IN  CONST  CSE_VARIABLE_INFORMATION_TRACK          *VariableInformationTrack,
  IN  CONST  VARIABLE_NVM_POINTER_TRACK              *RecycledVariablePtrTrack,
  IN         VARIABLE_NVM_STORE_INFO                 *VariableStoreInfo,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  *VariableAuthenticatedFieldTrack OPTIONAL,
  OUT        BOOLEAN                                 *CommandInProgress OPTIONAL
  )
{
  EFI_STATUS  Status;
  UINTN       VariableHeaderTotalSize    = 0;
  UINTN       VariableDataTotalSize      = 0;
  UINTN       VariableStoreRemainingSize = 0;

  if (
    CseVariableStorageStore           == NULL ||
    VariableInformationTrack          == NULL ||
    RecycledVariablePtrTrack          == NULL ||
    RecycledVariablePtrTrack->CurrPtr == NULL ||
    RecycledVariablePtrTrack->EndPtr  == NULL ||
    VariableStoreInfo                 == NULL
    ) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((EFI_D_INFO, "A variable in %a CSE storage is being recycled.\n", CseVariableStorageStore->Info.Name));
  if (
    !CseVariableStorageStore->Info.DataExpansionAllowed &&
    (VariableInformationTrack->DataSize != RecycledVariablePtrTrack->CurrPtr->DataSize)
    ) {
    // Check if there is sufficient space to add the new variable (old copy is already marked deleted)
    VariableHeaderTotalSize = GetVariableHeaderSize (VariableStoreInfo->AuthFlag) +
                                StrSize (VariableInformationTrack->VariableName);
    VariableHeaderTotalSize += NVM_GET_PAD_SIZE (VariableHeaderTotalSize);
    VariableDataTotalSize = VariableInformationTrack->DataSize +
                              NVM_GET_PAD_SIZE_N (VariableInformationTrack->DataSize);
    VariableStoreRemainingSize = CseVariableStorageStore->Info.MaximumSize -
                                   sizeof (VARIABLE_NVM_STORE_HEADER) -
                                   VariableStoreInfo->VariableStoreHeader->VariableHeaderTotalLength -
                                   VariableStoreInfo->VariableStoreHeader->VariableDataTotalLength;

    if (VariableStoreRemainingSize < (VariableHeaderTotalSize + VariableDataTotalSize)) {
      if (CseVariableStorageIsAsyncIoRequired ()) {
        // Reclaim should not be attempted when asynchronous I/O is active
        DEBUG ((DEBUG_WARN, "The variable storage space is exhausted and reclaim is not possible after POST.\n"));
        return EFI_OUT_OF_RESOURCES;
      }
      // There is not sufficient space so attempt reclaim and then add the new variable
      Status = CseVariableStorageStore->Reclaim (CseVariableStorageStore);
      if (!EFI_ERROR (Status)) {
        VariableStoreRemainingSize = CseVariableStorageStore->Info.MaximumSize -
                                       sizeof (VARIABLE_NVM_STORE_HEADER) -
                                       VariableStoreInfo->VariableStoreHeader->VariableHeaderTotalLength -
                                       VariableStoreInfo->VariableStoreHeader->VariableDataTotalLength;
        if (VariableStoreRemainingSize < (VariableHeaderTotalSize + VariableDataTotalSize)) {
          // Still not enough space after reclaim, exit with error
          return EFI_OUT_OF_RESOURCES;
        } else {
          Status = CseVariableStorageStore->WriteNewVariable (
                                              CseVariableStorageStore,
                                              VariableInformationTrack,
                                              VariableStoreInfo,
                                              VariableAuthenticatedFieldTrack,
                                              CommandInProgress
                                              );
        }
      } else {
        // Reclaim failed and not enough space, return with error
        ASSERT_EFI_ERROR (Status);
        return Status;
      }
    } else {
      // There is sufficient space so write the new variable
      Status = CseVariableStorageStore->WriteNewVariable (
                                          CseVariableStorageStore,
                                          VariableInformationTrack,
                                          VariableStoreInfo,
                                          VariableAuthenticatedFieldTrack,
                                          CommandInProgress
                                          );
    }
  } else {
    // The CSE storage store allows updates that expand data size so update the variable
    RecycledVariablePtrTrack->CurrPtr->State = VAR_ADDED;

    Status = CseVariableStorageStore->UpdateVariable (
                                        CseVariableStorageStore,
                                        VariableInformationTrack,
                                        RecycledVariablePtrTrack,
                                        VariableStoreInfo,
                                        VariableAuthenticatedFieldTrack,
                                        CommandInProgress
                                        );
  }

  return Status;
}

/**
  Sets the CSE NVM variable with the supplied data. These arguments are similar to those in the EFI Variable services.

  @param[in]      VariableName         Name of variable.
  @param[in]      VendorGuid           Guid of variable.
  @param[in]      Data                 Variable data.
  @param[in]      DataSize             Size of data. 0 means delete.
  @param[in]      Attributes           Attributes of the variable. No runtime or bootservice attribute set means delete.
  @param[out]     CommandInProgress    Determines whether asynchronous I/O should be used or the variable should
                                       immediately be written.
  @param[in,out]  IndexVariable        The variable found in the header region corresponding to this variable.
  @param[in]      FromSmm              Indicates the variable caller invoked variable services from SMM.
  @param[in]      KeyIndex             Index of associated public key in database
  @param[in]      MonotonicCount       Associated monotonic count value to protect against replay attack
  @param[in]      TimeStamp            Associated TimeStamp value to protect against replay attack

  @retval         EFI_SUCCESS          The set operation was successful.
  @retval         Others               The set operation failed.
**/
EFI_STATUS
EFIAPI
SetVariable (
  IN       CHAR16                      *VariableName,
  IN       EFI_GUID                    *VendorGuid,
  IN       VOID                        *Data,
  IN       UINTN                       DataSize,
  IN       UINT32                      Attributes,
  OUT      BOOLEAN                     *CommandInProgress,
  IN OUT   VARIABLE_NVM_POINTER_TRACK  *IndexVariable,
  IN       BOOLEAN                     FromSmm,
  IN       UINT32                      KeyIndex        OPTIONAL,
  IN       UINT64                      MonotonicCount  OPTIONAL,
  IN       EFI_TIME                    *TimeStamp      OPTIONAL
  )
{
  BOOLEAN                                 UpdatingExistingVariable;
  CSE_VARIABLE_STORAGE_STORE              *CseVariableStorageStore;
  CSE_VARIABLE_STORAGE_TYPE               VariableCseFileType;
  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  VariableAuthenticatedFieldTrack;
  CSE_VARIABLE_INFORMATION_TRACK          VariableInformationTrack;
  EFI_STATUS                              Status;
  UINTN                                   VariableHeaderTotalSize;
  UINTN                                   VariableDataTotalSize;
  UINTN                                   VariableStoreRemainingSize;
  VARIABLE_NVM_STORE_INFO                 VariableStoreInfo;
  VARIABLE_NVM_POINTER_TRACK              VariableNvmDeletedVariablePtrTrack;

  VariableNvmDeletedVariablePtrTrack.StartPtr               = NULL;
  VariableNvmDeletedVariablePtrTrack.EndPtr                 = NULL;
  VariableNvmDeletedVariablePtrTrack.CurrPtr                = NULL;
  VariableNvmDeletedVariablePtrTrack.InDeletedTransitionPtr = NULL;

  UpdatingExistingVariable = (BOOLEAN) (
                               IndexVariable->CurrPtr != NULL
                               && IsValidVariableHeader (IndexVariable->CurrPtr, IndexVariable->EndPtr)
                               );
  VariableCseFileType = GetCseVariableStoreStorageType (VariableName, VendorGuid, mCseVariableStorageStores);

  if (VariableCseFileType >= CseVariableStorageTypeMax) {
    return EFI_UNSUPPORTED;
  }

  if (mCseVariableStorageStores[VariableCseFileType] == NULL) {
    DEBUG ((EFI_D_ERROR, "The CSE variable storage store for this variable was not initialized.\n"));
    return EFI_NOT_FOUND;
  }
  CseVariableStorageStore = mCseVariableStorageStores[VariableCseFileType];

  VariableStoreInfo.VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) CseVariableStorageStore->Info.Header;
  if (VariableStoreInfo.VariableStoreHeader == NULL) {
    DEBUG ((EFI_D_ERROR, "The variable store could not be found for this variable.\n"));
    return EFI_NOT_FOUND;
  }

  Status = IsAuthenticatedVariableStore (VariableStoreInfo.VariableStoreHeader, &VariableStoreInfo.AuthFlag);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  if (!CseVariableStorageStore->Info.Enabled || !CseVariableStorageStore->Info.Established) {
    DEBUG ((EFI_D_ERROR, "Error: Attempted to set a variable with a CSE storage type not enabled.\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Populate structures consumed by helper functions
  //
  if (VariableStoreInfo.AuthFlag) {
    VariableAuthenticatedFieldTrack.MonotonicCount = MonotonicCount;
    VariableAuthenticatedFieldTrack.PubKeyIndex    = KeyIndex;
    VariableAuthenticatedFieldTrack.TimeStamp      = TimeStamp;
  }

  VariableInformationTrack.VariableName = VariableName;
  VariableInformationTrack.VendorGuid   = VendorGuid;
  VariableInformationTrack.Data         = Data;
  VariableInformationTrack.DataSize     = DataSize;
  VariableInformationTrack.Attributes   = Attributes;

  if (UpdatingExistingVariable) {
    //
    // Existing Variable
    //
    if (DataSize == 0 || (Attributes & (EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS)) == 0) {
      // Note: Setting a variable with no access or zero DataSize attributes causes it to be deleted.
      DEBUG ((EFI_D_INFO, "Variable has been requested for delete.\n"));

      Status =  CseVariableStorageStore->DeleteVariable (
                                           CseVariableStorageStore,
                                           &VariableStoreInfo,
                                           IndexVariable->CurrPtr,
                                           CommandInProgress
                                           );
    } else {
      // An existing variable is being updated
      if (!CseVariableStorageStore->Info.DataExpansionAllowed && (IndexVariable->CurrPtr->DataSize != DataSize)) {
        // The data cannot be expanded in place and varies from the previous size
        // Check if there is sufficient space to add the new variable
        VariableHeaderTotalSize = GetVariableHeaderSize (VariableStoreInfo.AuthFlag) +
                                    StrSize (VariableInformationTrack.VariableName);
        VariableHeaderTotalSize += NVM_GET_PAD_SIZE (VariableHeaderTotalSize);
        VariableDataTotalSize = VariableInformationTrack.DataSize +
                                  (UINTN) NVM_GET_PAD_SIZE_N (VariableInformationTrack.DataSize);
        VariableStoreRemainingSize = CseVariableStorageStore->Info.MaximumSize -
                                       sizeof (VARIABLE_NVM_STORE_HEADER) -
                                       VariableStoreInfo.VariableStoreHeader->VariableHeaderTotalLength -
                                       VariableStoreInfo.VariableStoreHeader->VariableDataTotalLength;

        if (VariableStoreRemainingSize < (VariableHeaderTotalSize + VariableDataTotalSize)) {
          if (CseVariableStorageIsAsyncIoRequired ()) {
            // Reclaim should not be attempted when asynchronous I/O is active
            DEBUG ((DEBUG_WARN, "The variable storage space is exhausted and reclaim is not possible after POST.\n"));
            return EFI_OUT_OF_RESOURCES;
          }
          // There is not sufficient space so attempt reclaim and then add the new variable
          Status = CseVariableStorageStore->Reclaim (CseVariableStorageStore);
          if (!EFI_ERROR (Status)) {
            VariableStoreRemainingSize = CseVariableStorageStore->Info.MaximumSize -
                                           sizeof (VARIABLE_NVM_STORE_HEADER) -
                                           VariableStoreInfo.VariableStoreHeader->VariableHeaderTotalLength -
                                           VariableStoreInfo.VariableStoreHeader->VariableDataTotalLength;
            if (VariableStoreRemainingSize < (VariableHeaderTotalSize + VariableDataTotalSize)) {
              // Still not enough space after reclaim, exit with error
              DEBUG ((DEBUG_ERROR, "Insufficient storage space after reclaim for the new variable.\n"));
              return EFI_OUT_OF_RESOURCES;
            }
          } else {
            return Status;
          }
        }

        // There is enough space, mark the old variable deleted and add the new variable
        Status = CseVariableStorageStore->DeleteVariable (
                                            CseVariableStorageStore,
                                            &VariableStoreInfo,
                                            IndexVariable->CurrPtr,
                                            CommandInProgress
                                            );
        if (!EFI_ERROR (Status)) {
          Status = CseVariableStorageStore->WriteNewVariable (
                                              CseVariableStorageStore,
                                              &VariableInformationTrack,
                                              &VariableStoreInfo,
                                              (VariableStoreInfo.AuthFlag) ? &VariableAuthenticatedFieldTrack : NULL,
                                              CommandInProgress
                                              );
        }
      } else {
        // The data can be expanded in place or does not vary from the previous size
        Status = CseVariableStorageStore->UpdateVariable (
                                            CseVariableStorageStore,
                                            &VariableInformationTrack,
                                            IndexVariable,
                                            &VariableStoreInfo,
                                            (VariableStoreInfo.AuthFlag) ? &VariableAuthenticatedFieldTrack : NULL,
                                            CommandInProgress
                                            );
      }
    }
  } else {
    //
    // Non-Existing Variable
    //
    VariableNvmDeletedVariablePtrTrack.StartPtr = GetStartPointer (VariableStoreInfo.VariableStoreHeader);
    VariableNvmDeletedVariablePtrTrack.EndPtr   = GetEndPointer (VariableStoreInfo.VariableStoreHeader);

    //
    // Check if variable is recycled (added back after deletion)
    //
    Status = FindDeletedVariable (
               VariableName,
               VendorGuid,
               VariableStoreInfo.VariableStoreHeader,
               &VariableNvmDeletedVariablePtrTrack
               );
    if (EFI_ERROR (Status)) {
      VariableNvmDeletedVariablePtrTrack.CurrPtr = NULL;
    }

    if (VariableNvmDeletedVariablePtrTrack.CurrPtr != NULL) {
      // Recycle the existing deleted variable entry
      Status = RecycleVariable (
                 CseVariableStorageStore,
                 &VariableInformationTrack,
                 &VariableNvmDeletedVariablePtrTrack,
                 &VariableStoreInfo,
                 (VariableStoreInfo.AuthFlag) ? &VariableAuthenticatedFieldTrack : NULL,
                 CommandInProgress
                 );
    } else {
      // Add a new variable entry
      Status = CseVariableStorageStore->WriteNewVariable (
                                          CseVariableStorageStore,
                                          &VariableInformationTrack,
                                          &VariableStoreInfo,
                                          (VariableStoreInfo.AuthFlag) ? &VariableAuthenticatedFieldTrack : NULL,
                                          CommandInProgress
                                          );
    }
  }

  if (!EFI_ERROR (Status) && FromSmm) {
    // If no messages are queued, the command queue is not active and this function should
    // immediately return success.
    Status = CseVariableStorageStartSmmCommandQueue ();
  }

  return Status;
}

/**
  Retrieves a protocol instance-specific GUID.

  Returns a unique GUID per EDKII_VARIABLE_STORAGE_PROTOCOL instance.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[out]      VariableGuid           A pointer to an EFI_GUID that is this protocol instance's GUID.

  @retval          EFI_SUCCESS            The data was returned successfully.
  @retval          EFI_INVALID_PARAMETER  A required parameter is NULL.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetId (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  OUT       EFI_GUID                          *InstanceGuid
  )
{
  if (InstanceGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem (InstanceGuid, &gCseVariableStorageProtocolInstanceGuid, sizeof (EFI_GUID));

  return EFI_SUCCESS;
}

/**
  This service retrieves a variable's value using its name and GUID.

  Read the specified variable from the CSE NVM variable store. If the Data
  buffer is too small to hold the contents of the variable,
  the error EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the
  required buffer size to obtain the data.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]       AtRuntime              TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]       FromSmm                TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]       VariableName           A pointer to a null-terminated string that is the variable's name.
  @param[in]       VariableGuid           A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                          VariableGuid and VariableName must be unique.
  @param[out]      Attributes             If non-NULL, on return, points to the variable's attributes.
  @param[in, out]  DataSize               On entry, points to the size in bytes of the Data buffer.
                                          On return, points to the size of the data returned in Data.
  @param[out]      Data                   Points to the buffer which will hold the returned variable value.
  @param[out]      CommandInProgress      TRUE if the command requires asyncronous I/O and has not completed yet
                                          If this parameter is TRUE, then Attributes, DataSize, and Data will not
                                          be updated by this driver and do not contain valid data.  Asyncronous I/O
                                          should only be required during OS runtime phase, this return value must be
                                          FALSE if the AtRuntime parameter is FALSE.  This parameter should only be
                                          used by SMM Variable Storage implementations.  Runtime DXE implementations
                                          must always return FALSE.  If CommandInProgress is returned TRUE, then the
                                          function must return EFI_SUCCESS

  @retval          EFI_SUCCESS            The variable was read successfully.
  @retval          EFI_NOT_FOUND          The variable could not be found.
  @retval          EFI_BUFFER_TOO_SMALL   The DataSize is too small for the resulting data.
                                          DataSize is updated with the size required for
                                          the specified variable.
  @retval          EFI_INVALID_PARAMETER  VariableName, VariableGuid, DataSize or Data is NULL.
  @retval          EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetVariable (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN        BOOLEAN                           AtRuntime,
  IN        BOOLEAN                           FromSmm,
  IN CONST  CHAR16                            *VariableName,
  IN CONST  EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *Attributes OPTIONAL,
  IN OUT    UINTN                             *DataSize,
  OUT       VOID                              *Data,
  OUT       BOOLEAN                           *CommandInProgress
  )
{
  EFI_STATUS          Status;
  BOOLEAN             IsCommandInProgressLocal;
  VARIABLE_NVM_HEADER *VariableHeader = NULL;

  //
  // Check input parameters
  //
  if (VariableName == NULL || VariableGuid == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *CommandInProgress = FALSE;

  DEBUG ((
    EFI_D_INFO,
    "Attempting to read CSE NVM variable.\n  Name=\'%ls\'\n  GUID=%g\n\n",
    VariableName,
    VariableGuid
    ));

  Status = CseVariableStorageGetVariableInternal (
             mCseVariableStorageStores,
             VariableName,
             VariableGuid,
             &IsCommandInProgressLocal,
             Attributes,
             DataSize,
             Data,
             &VariableHeader
             );
  if (!EFI_ERROR (Status)) {
    mCurrentGetVariableHeader = (AUTHENTICATED_VARIABLE_NVM_HEADER *) VariableHeader;
    *CommandInProgress = IsCommandInProgressLocal;

    DEBUG ((EFI_D_INFO, "The variable was %a successfully.\n", ((IsCommandInProgressLocal) ? "queued" : "read")));
  }

  return Status;
}

/**
  This service retrieves an authenticated variable's value using its name and GUID.

  Read the specified authenticated variable from the UEFI variable store. If the Data
  buffer is too small to hold the contents of the variable,
  the error EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the
  required buffer size to obtain the data.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]       AtRuntime              TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]       FromSmm                TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]       VariableName           A pointer to a null-terminated string that is the variable's name.
  @param[in]       VariableGuid           A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                          VariableGuid and VariableName must be unique.
  @param[out]      Attributes             If non-NULL, on return, points to the variable's attributes.
  @param[in, out]  DataSize               On entry, points to the size in bytes of the Data buffer.
                                          On return, points to the size of the data returned in Data.
  @param[out]      Data                   Points to the buffer which will hold the returned variable value.
  @param[out]      KeyIndex               Index of associated public key in database
  @param[out]      MonotonicCount         Associated monotonic count value to protect against replay attack
  @param[out]      TimeStamp              Associated TimeStamp value to protect against replay attack
  @param[out]      CommandInProgress      TRUE if the command requires asyncronous I/O and has not completed yet
                                          If this parameter is TRUE, then Attributes, DataSize, Data, KeyIndex,
                                          MonotonicCount, and TimeStamp will not be updated by this driver
                                          and do not contain valid data.  Asyncronous I/O should only be required
                                          during OS runtime phase, this return value must be FALSE if the AtRuntime
                                          parameter is FALSE.  This parameter should only be used by SMM Variable
                                          Storage implementations.  Runtime DXE implementations must always return
                                          FALSE.  If CommandInProgress is returned TRUE, then the function must return
                                          EFI_SUCCESS.

  @retval          EFI_SUCCESS            The variable was read successfully.
  @retval          EFI_NOT_FOUND          The variable could not be found.
  @retval          EFI_BUFFER_TOO_SMALL   The DataSize is too small for the resulting data.
                                          DataSize is updated with the size required for
                                          the specified variable.
  @retval          EFI_INVALID_PARAMETER  VariableName, VariableGuid, DataSize or Data is NULL.
  @retval          EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetAuthenticatedVariable (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN        BOOLEAN                           AtRuntime,
  IN        BOOLEAN                           FromSmm,
  IN CONST  CHAR16                            *VariableName,
  IN CONST  EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *Attributes,
  IN OUT    UINTN                             *DataSize,
  OUT       VOID                              *Data,
  OUT       UINT32                            *KeyIndex,
  OUT       UINT64                            *MonotonicCount,
  OUT       EFI_TIME                          *TimeStamp,
  OUT       BOOLEAN                           *CommandInProgress
  )
{
  EFI_STATUS                        Status;
  BOOLEAN                           IsCommandInProgressLocal;
  AUTHENTICATED_VARIABLE_NVM_HEADER *AuthenticatedVariableHeader = NULL;

  //
  // Check input parameters
  //
  if (VariableName == NULL || VariableGuid == NULL || DataSize == NULL ||
      KeyIndex == NULL || MonotonicCount == NULL || TimeStamp == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *CommandInProgress = FALSE;

  DEBUG ((
    EFI_D_INFO,
    "Attempting to read CSE NVM authenticated variable.\n  Name=\'%ls\'\n  GUID=%g\n\n",
    VariableName,
    VariableGuid
    ));

  Status = CseVariableStorageGetVariableInternal (
             mCseVariableStorageStores,
             VariableName,
             VariableGuid,
             &IsCommandInProgressLocal,
             Attributes,
             DataSize,
             Data,
             (VARIABLE_NVM_HEADER **) &AuthenticatedVariableHeader
             );
  if (!EFI_ERROR (Status)) {
    mCurrentGetVariableHeader = AuthenticatedVariableHeader;
    *CommandInProgress = IsCommandInProgressLocal;
    DEBUG ((EFI_D_INFO, "The variable was %a successfully.\n", ((IsCommandInProgressLocal) ? "queued" : "read")));

    if (AuthenticatedVariableHeader != NULL) {
      *KeyIndex       = AuthenticatedVariableHeader->PubKeyIndex;
      *MonotonicCount = AuthenticatedVariableHeader->MonotonicCount;

      CopyMem (TimeStamp, &AuthenticatedVariableHeader->TimeStamp, sizeof (EFI_TIME));
    }
  }

  return Status;
}

/**
  Return the next variable name and GUID.

  This function is called multiple times to retrieve the VariableName
  and VariableGuid of all variables currently available in the system.
  On each call, the previous results are passed into the interface,
  and, on return, the interface returns the data for the next
  interface. When the entire variable list has been returned,
  EFI_NOT_FOUND is returned.

  @param[in]      This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.

  @param[in, out] VariableNameSize       On entry, points to the size of the buffer pointed to by
                                         VariableName. On return, the size of the variable name buffer.
  @param[in, out] VariableName           On entry, a pointer to a null-terminated string that is the
                                         variable's name. On return, points to the next variable's
                                         null-terminated name string.
  @param[in, out] VariableGuid           On entry, a pointer to an EFI_GUID that is the variable's GUID.
                                         On return, a pointer to the next variable's GUID.
  @param[out]     VariableAttributes     A pointer to the variable attributes.

  @retval         EFI_SUCCESS            The variable was read successfully.
  @retval         EFI_NOT_FOUND          The variable could not be found.
  @retval         EFI_BUFFER_TOO_SMALL   The VariableNameSize is too small for the resulting
                                         data. VariableNameSize is updated with the size
                                         required for the specified variable.
  @retval         EFI_INVALID_PARAMETER  VariableName, VariableGuid or
                                         VariableNameSize is NULL.
  @retval         EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetNextVariableName (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN OUT    UINTN                             *VariableNameSize,
  IN OUT    CHAR16                            *VariableName,
  IN OUT    EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *VariableAttributes
  )
{
  EFI_STATUS           Status;
  BOOLEAN              IsAuthVariable;
  UINTN                VarNameSize;
  VARIABLE_NVM_HEADER  *VariablePtr;

  if (VariableNameSize == NULL || VariableName == NULL || VariableGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = GetNextCseVariableName (VariableName, VariableGuid, mCseVariableStorageStores, &VariablePtr, &IsAuthVariable);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VarNameSize = NameSizeOfVariable (VariablePtr, IsAuthVariable);
  ASSERT (VarNameSize != 0);

  if (VarNameSize <= *VariableNameSize) {
    CopyMem (VariableName, GetVariableNamePtr (VariablePtr, IsAuthVariable), VarNameSize);
    CopyMem (VariableGuid, GetVendorGuidPtr (VariablePtr, IsAuthVariable), sizeof (EFI_GUID));
    Status = EFI_SUCCESS;
  } else {
    Status = EFI_BUFFER_TOO_SMALL;
  }
  *VariableNameSize = VarNameSize;
  *VariableAttributes = VariablePtr->Attributes;

  return Status;
}

/**
  Returns information on the amount of space available in the variable store. If the amount of data that can be written
  depends on if the platform is in Pre-OS stage or OS stage, the AtRuntime parameter should be used to compute usage.

  @param[in]  This                        A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  AtRuntime                   TRUE is the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[out] VariableStoreSize           The total size of the NV storage. Indicates the maximum amount
                                          of data that can be stored in this NV storage area.
  @param[out] CommonVariablesTotalSize    The total combined size of all the common UEFI variables that are
                                          stored in this NV storage area. Excludes variables with the
                                          EFI_VARIABLE_HARDWARE_ERROR_RECORD attribute set.
  @param[out] HwErrVariablesTotalSize     The total combined size of all the UEFI variables that have the
                                          EFI_VARIABLE_HARDWARE_ERROR_RECORD attribute set and which are
                                          stored in this NV storage area. Excludes all other variables.

  @retval     EFI_INVALID_PARAMETER       Any of the given parameters are NULL
  @retval     EFI_SUCCESS                 Space information returned successfully.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetStorageUsage (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           AtRuntime,
  OUT         UINT32                            *VariableStoreSize,
  OUT         UINT32                            *CommonVariablesTotalSize,
  OUT         UINT32                            *HwErrVariablesTotalSize
  )
{
  BOOLEAN                    IsAuthVariable;
  CSE_VARIABLE_STORAGE_TYPE  Type;
  EFI_GUID                   Guid;
  EFI_STATUS                 Status;
  UINT32                     Attributes;
  VARIABLE_NVM_POINTER_TRACK VariablePtrTrack;

  CHAR16  *VariableName         = NULL;

  UINTN   VariableNameSize      = 0;
  UINTN   NewVariableNameSize   = 0;

  UINTN  CseVariableTotalStoreSizeInternal   = 0;
  UINTN  CseCommonVariablesTotalSizeInternal = 0;
  UINTN  CseHwErrVariablesTotalSizeInternal  = 0;

  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    if (mCseVariableStorageStores[Type] != NULL && mCseVariableStorageStores[Type]->Info.Established) {
      CseVariableTotalStoreSizeInternal += (mCseVariableStorageStores[Type]->Info.MaximumSize - sizeof (VARIABLE_NVM_STORE_HEADER));
      DEBUG ((EFI_D_INFO, "Current store maximum size = %d bytes.\n", mCseVariableStorageStores[Type]->Info.MaximumSize));
    }

  }
  ASSERT (CseVariableTotalStoreSizeInternal > 0);

  VariableNameSize = sizeof (CHAR16);
  VariableName     = AllocateZeroPool (VariableNameSize);
  if (VariableName == NULL) {
    ASSERT (VariableName != NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  while (TRUE) {
    NewVariableNameSize = VariableNameSize;
    Status = CseVariableStorageGetNextVariableName (This, &NewVariableNameSize, VariableName, &Guid, &Attributes);

    if (Status == EFI_BUFFER_TOO_SMALL) {
      VariableName = ReallocatePool (VariableNameSize, NewVariableNameSize, VariableName);
      if (VariableName == NULL) {
        ASSERT (VariableName != NULL);
        return EFI_OUT_OF_RESOURCES;
      }
      Status = CseVariableStorageGetNextVariableName (This, &NewVariableNameSize, VariableName, &Guid, &Attributes);
      VariableNameSize = NewVariableNameSize;
    }

    if (Status == EFI_NOT_FOUND) {
      break;
    }
    ASSERT_EFI_ERROR (Status);

    //
    // Get the variable header for this variable
    //
    Status = FindVariable (VariableName, &Guid, mCseVariableStorageStores, &VariablePtrTrack);

    if (EFI_ERROR (Status) || VariablePtrTrack.CurrPtr == NULL) {
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    Type = GetCseVariableStoreStorageType (VariableName, &Guid, mCseVariableStorageStores);

    Status = IsAuthenticatedVariableStore (
               (VARIABLE_NVM_STORE_HEADER *)  mCseVariableStorageStores[Type]->Info.Header,
               &IsAuthVariable
               );

    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    //
    // When the reclaim operation is implemented, need to do a runtime check.
    // At runtime, don't worry about the variable state. At boot time, the
    // state needs to be taken into account because the variables can be reclaimed.
    //
    if ((VariablePtrTrack.CurrPtr->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
      CseHwErrVariablesTotalSizeInternal += GetVariableHeaderSize (IsAuthVariable);
      CseHwErrVariablesTotalSizeInternal += VariablePtrTrack.CurrPtr->NameSize;
      CseHwErrVariablesTotalSizeInternal += VariablePtrTrack.CurrPtr->DataSize;
    } else {
      CseCommonVariablesTotalSizeInternal += GetVariableHeaderSize (IsAuthVariable);
      CseCommonVariablesTotalSizeInternal += VariablePtrTrack.CurrPtr->NameSize;
      CseCommonVariablesTotalSizeInternal += VariablePtrTrack.CurrPtr->DataSize;
    }
  }

  FreePool (VariableName);

  *VariableStoreSize        = (UINT32) CseVariableTotalStoreSizeInternal;
  *CommonVariablesTotalSize = (UINT32) CseCommonVariablesTotalSizeInternal;
  *HwErrVariablesTotalSize  = (UINT32) CseHwErrVariablesTotalSizeInternal;

  return EFI_SUCCESS;
}

/**
  Returns whether this NV storage area supports storing authenticated variables or not

  @param[in]  This             A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[out] AuthSupported    TRUE if this NV storage area can store authenticated variables,
                               FALSE otherwise

  @retval     EFI_SUCCESS      AuthSupported was returned successfully.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetAuthenticatedSupport (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  OUT         BOOLEAN                           *AuthSupported
  )
{
  *AuthSupported = TRUE;

  return EFI_SUCCESS;
}

/**
  This code sets a variable's value using its name and GUID.

  Caution: This function may receive untrusted input.
  This function may be invoked in SMM mode, and datasize and data are external input.
  This function will do basic validation, before parsing the data.
  This function will parse the authentication carefully to avoid security issues, like
  buffer overflow, integer overflow.
  This function will check attribute carefully to avoid authentication bypass.

  @param[in]  This                     A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  AtRuntime                TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]  FromSmm                  TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]  VariableName             Name of Variable to be found.
  @param[in]  VendorGuid               Variable vendor GUID.
  @param[in]  Attributes               Attribute value of the variable found
  @param[in]  DataSize                 Size of Data found. If size is less than the
                                       data, this value contains the required size.
  @param[in]  Data                     Data pointer.
  @param[in]  KeyIndex                 If writing an authenticated variable, the public key index
  @param[in]  MonotonicCount           If writing a monotonic counter authenticated variable, the counter value
  @param[in]  TimeStamp                If writing a timestamp authenticated variable, the timestamp value
  @param[out] CommandInProgress        TRUE if the command requires asyncronous I/O and has not completed yet.
                                       Asyncronous I/O should only be required during OS runtime phase, this
                                       return value must be FALSE if the AtRuntime parameter is FALSE.  This
                                       parameter should only be used by SMM Variable Storage implementations.
                                       Runtime DXE implementations must always return FALSE.  If
                                       CommandInProgress is returned TRUE, then the function must return
                                       EFI_SUCCESS.

  @retval     EFI_INVALID_PARAMETER    Invalid parameter.
  @retval     EFI_SUCCESS              Set successfully.
  @retval     EFI_OUT_OF_RESOURCES     Resource not enough to set variable.
  @retval     EFI_NOT_FOUND            Not found.
  @retval     EFI_WRITE_PROTECTED      Variable is read-only.
**/
EFI_STATUS
EFIAPI
CseVariableStorageSetVariable (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           AtRuntime,
  IN          BOOLEAN                           FromSmm,
  IN          CHAR16                            *VariableName,
  IN          EFI_GUID                          *VendorGuid,
  IN          UINT32                            Attributes,
  IN          UINTN                             DataSize,
  IN          VOID                              *Data,
  IN          UINT32                            KeyIndex       OPTIONAL,
  IN          UINT64                            MonotonicCount OPTIONAL,
  IN          EFI_TIME                          *TimeStamp     OPTIONAL,
  OUT         BOOLEAN                           *CommandInProgress
  )
{
  EFI_STATUS                  Status;
  BOOLEAN                     IsCommandInProgressLocal;
  VARIABLE_NVM_POINTER_TRACK  VariablePtrTrack;

  //
  // Check input parameters.
  //
  if (VariableName == NULL || VariableName[0] == 0 || VendorGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DataSize != 0 && Data == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // The proxy OS driver is unavailable during crash dump
  //
  if (CompareGuid (VendorGuid, &gBugCheckVariableGuid) && CseVariableStorageIsAsyncIoRequired ()) {
    return EFI_SUCCESS;
  }

  if (((Attributes & EFI_VARIABLE_NON_VOLATILE) != EFI_VARIABLE_NON_VOLATILE) && (DataSize != 0)) {
    DEBUG ((EFI_D_ERROR, "A volatile variable was passed to the CSE variable storage protocol.\n"));
    return EFI_INVALID_PARAMETER;
  }
  *CommandInProgress       = FALSE;

  DEBUG ((
    EFI_D_INFO,
    "Attempting to set a CSE storage variable.\n  Name=\'%ls\'\n  GUID=%g\n  Attributes=0x%x\n\n",
    VariableName,
    *VendorGuid,
    Attributes
    ));

  if ((PcdGet32 (PcdMaxVariableSize) - sizeof (VARIABLE_NVM_HEADER)) <= (StrSize (VariableName) + DataSize)) {
    DEBUG ((EFI_D_ERROR, "The variable being written is larger than the maximum specified variable size.\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check if the variable already exists
  //
  Status = FindVariable (VariableName, VendorGuid, mCseVariableStorageStores, &VariablePtrTrack);
  if (!EFI_ERROR (Status)) {
    if (Attributes != 0 && (Attributes & (~EFI_VARIABLE_APPEND_WRITE)) != VariablePtrTrack.CurrPtr->Attributes) {
      DEBUG ((EFI_D_ERROR, "Error: Attributes given do not match the existing variable.\n"));
      DEBUG ((
        EFI_D_ERROR,
        "       Attributes given = 0x%x. Existing attributes = 0x%x.\n",
        Attributes,
        VariablePtrTrack.CurrPtr->Attributes
        ));
      return EFI_INVALID_PARAMETER;
    }
  } else if (Status != EFI_NOT_FOUND) {
    DEBUG ((EFI_D_ERROR, "Error occurred finding the variable.\n"));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "VariablePtrTrack->CurrPtr is null = %c\n", (VariablePtrTrack.CurrPtr == NULL ? 'T' : 'F')));

  Status = SetVariable (
             VariableName,
             VendorGuid,
             Data,
             DataSize,
             Attributes,
             &IsCommandInProgressLocal,
             &VariablePtrTrack,
             FromSmm,
             KeyIndex,
             MonotonicCount,
             TimeStamp
             );
  if (!EFI_ERROR (Status)) {
    *CommandInProgress = IsCommandInProgressLocal;
    DEBUG ((EFI_D_INFO, "The variable was %a successfully.\n", ((IsCommandInProgressLocal) ? "queued" : "written")));
  }

  return Status;
}

/**
  Returns whether this NV storage area is ready to accept calls to SetVariable() or not

  @param[in]  This     A pointer to this instance of the VARIABLE_STORAGE_PROTOCOL.

  @retval     TRUE     The NV storage area is ready to accept calls to SetVariable()
  @retval     FALSE    The NV storage area is not ready to accept calls to SetVariable()
**/
BOOLEAN
EFIAPI
CseVariableStorageWriteServiceIsReady (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This
  )
{
  //
  // CSE should be ready to service write commands when this driver is loaded
  //
  return TRUE;
}

/**
  Performs variable store garbage collection/reclaim operation.

  @param[in]  This                             A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.

  @retval     EFI_INVALID_PARAMETER            Invalid parameter.
  @retval     EFI_SUCCESS                      Garbage Collection Successful.
  @retval     EFI_OUT_OF_RESOURCES             Insufficient resource to complete garbage collection.
  @retval     EFI_WRITE_PROTECTED              Write services are not yet ready.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGarbageCollect (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This
  )
{
  //
  // @todo: Need to Implement
  //
  return EFI_SUCCESS;
}

/**
  Queries the variable store to determine if asyncronous I/O is required during OS runtime to get/set variables.
  Different return values may be supplied depending on whether the origin of the call is SMM or not.

  @param[in]  This                           A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  FromSmm                        TRUE if Get/SetVariable() is being called by SMM code, FALSE if called by DXE code

  @retval     TRUE                           Asyncronous I/O is required during OS runtime to call to Get/SetVariable()
  @retval     FALSE                          Asyncronous I/O is not required during OS runtime to call to Get/SetVariable()

**/
BOOLEAN
EFIAPI
CseVariableStorageAsyncIoRequired (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           FromSmm
  )
{
  //
  // Note: The generic FromSmm parameter is not needed in this protocol's logic
  //
  return CseVariableStorageIsAsyncIoRequired ();
}