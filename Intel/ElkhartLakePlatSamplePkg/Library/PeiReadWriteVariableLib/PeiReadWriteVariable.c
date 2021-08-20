/** @file
  Implement ReadWrite Variable Services required by PEIM and install
  PEI ReadWrite Varaiable PPI. These services operates the non volatile storage space.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#include "PeiReadWriteVariable.h"

///
/// Structure of PEI ReadWrite PPI.
///
PEI_READ_WRITE_VARIABLE_PPI mVariablePpi = {
  PeiGetVariable,
  PeiGetNextVariableName,
  PeiSetVariable
};

EFI_PEI_PPI_DESCRIPTOR     mPpiListVariable = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiReadWriteVariablePpiGuid,
  &mVariablePpi
};

PEI_VARIABLE_MODULE_GLOBAL  *mVariableModuleGlobal;

///
/// Define a memory cache that improves the search performance for a variable.
///
VARIABLE_STORE_HEADER  *mNvVariableCache      = NULL;

///
/// The memory entry used for variable statistics data.
///
VARIABLE_INFO_ENTRY    *gVariableInfo         = NULL;

typedef struct {
  CHAR16                                 *VariableName;
  EFI_GUID                               *VendorGuid;
} VARIABLE_TYPE;

/**
  This function will return if this variable is SecureBootPolicy Variable.

  @param[in]  VariableName      A Null-terminated string that is the name of the vendor's variable.
  @param[in]  VendorGuid        A unique identifier for the vendor.

  @retval TRUE  This is SecureBootPolicy Variable
  @retval FALSE This is not SecureBootPolicy Variable
**/
STATIC
BOOLEAN
IsSecureBootPolicyVariable (
  IN CHAR16                                 *VariableName,
  IN EFI_GUID                               *VendorGuid
  )
{
  UINTN                      Index;
  VARIABLE_TYPE              VariableType[] = {{EFI_SECURE_BOOT_MODE_NAME,    &gEfiGlobalVariableGuid},
                                               {EFI_PLATFORM_KEY_NAME,        &gEfiGlobalVariableGuid},
                                               {EFI_KEY_EXCHANGE_KEY_NAME,    &gEfiGlobalVariableGuid},
                                               {EFI_IMAGE_SECURITY_DATABASE,  &gEfiImageSecurityDatabaseGuid},
                                               {EFI_IMAGE_SECURITY_DATABASE1, &gEfiImageSecurityDatabaseGuid},
                                               };

  for (Index = 0; Index < sizeof (VariableType)/sizeof (VariableType[0]); Index++) {
    if ((StrCmp (VariableName, VariableType[Index].VariableName) == 0) &&
        (CompareGuid (VendorGuid, VariableType[Index].VendorGuid))) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Routine used to track statistical information about variable usage.
  The data is stored in the EFI system table so it can be accessed later.
  VariableInfo.efi can dump out the table. Only Boot Services variable
  accesses are tracked by this code. The PcdVariableCollectStatistics
  build flag controls if this feature is enabled.

  A read that hits in the cache will have Read and Cache true for
  the transaction. Data is allocated by this routine, but never
  freed.

  @param[in] VariableName   Name of the Variable to track.
  @param[in] VendorGuid     Guid of the Variable to track.
  @param[in] Volatile       TRUE if volatile FALSE if non-volatile.
  @param[in] Read           TRUE if GetVariable() was called.
  @param[in] Write          TRUE if SetVariable() was called.
  @param[in] Delete         TRUE if deleted via SetVariable().
  @param[in] Cache          TRUE for a cache hit.

**/
STATIC
VOID
UpdateVariableInfo (
  IN  CHAR16                  *VariableName,
  IN  EFI_GUID                *VendorGuid,
  IN  BOOLEAN                 Volatile,
  IN  BOOLEAN                 Read,
  IN  BOOLEAN                 Write,
  IN  BOOLEAN                 Delete,
  IN  BOOLEAN                 Cache
  )
{
  VARIABLE_INFO_ENTRY   *Entry;

  if (FeaturePcdGet (PcdVariableCollectStatistics)) {


    if (gVariableInfo == NULL) {
      //
      // On the first call allocate a entry and place a pointer to it in
      // the EFI System Table.
      //
      gVariableInfo = AllocateZeroPool (sizeof (VARIABLE_INFO_ENTRY));
      ASSERT (gVariableInfo != NULL);

      CopyGuid (&gVariableInfo->VendorGuid, VendorGuid);
      gVariableInfo->Name = AllocateZeroPool (StrSize (VariableName));
      ASSERT (gVariableInfo->Name != NULL);
      StrCpyS (gVariableInfo->Name, StrSize(VariableName)/sizeof(CHAR16), VariableName);
      gVariableInfo->Volatile = Volatile;
    }


    for (Entry = gVariableInfo; Entry != NULL; Entry = Entry->Next) {
      if (CompareGuid (VendorGuid, &Entry->VendorGuid)) {
        if (StrCmp (VariableName, Entry->Name) == 0) {
          if (Read) {
            Entry->ReadCount++;
          }
          if (Write) {
            Entry->WriteCount++;
          }
          if (Delete) {
            Entry->DeleteCount++;
          }
          if (Cache) {
            Entry->CacheCount++;
          }

          return;
        }
      }

      if (Entry->Next == NULL) {
        //
        // If the entry is not in the table add it.
        // Next iteration of the loop will fill in the data.
        //
        Entry->Next = AllocateZeroPool (sizeof (VARIABLE_INFO_ENTRY));
        ASSERT (Entry->Next != NULL);

        CopyGuid (&Entry->Next->VendorGuid, VendorGuid);
        Entry->Next->Name = AllocateZeroPool (StrSize (VariableName));
        ASSERT (Entry->Next->Name != NULL);
        StrCpyS (Entry->Next->Name, StrSize(VariableName)/sizeof(CHAR16), VariableName);
        Entry->Next->Volatile = Volatile;
      }

    }
  }
}

/**

  This function writes data to the FWH at the correct LBA even if the LBAs
  are fragmented.

  @param Global                  Pointer to VARAIBLE_GLOBAL structure.
  @param Volatile                Point out the Variable is Volatile or Non-Volatile.
  @param SetByIndex              TRUE if target pointer is given as index.
                                 FALSE if target pointer is absolute.
  @param Fvb                     Pointer to the writable FVB protocol.
  @param DataPtrIndex            Pointer to the Data from the end of VARIABLE_STORE_HEADER
                                 structure.
  @param DataSize                Size of data to be written.
  @param Buffer                  Pointer to the buffer from which data is written.

  @retval EFI_INVALID_PARAMETER  Parameters not valid.
  @retval EFI_SUCCESS            Variable store successfully updated.

**/
STATIC
EFI_STATUS
UpdateVariableStore (
  IN  PEI_VARIABLE_GLOBAL                 *Global,
  IN  BOOLEAN                             Volatile,
  IN  BOOLEAN                             SetByIndex,
  IN  PCH_SPI_PPI                         *SpiPpi,
  IN  UINTN                               DataPtrIndex,
  IN  UINT32                              DataSize,
  IN  UINT8                               *Buffer
  )
{
  UINTN                       LinearOffset;
  UINTN                       CurrWriteSize;
  UINTN                       CurrWritePtr;
  UINT8                       *CurrBuffer;
  VARIABLE_STORE_HEADER       *VolatileBase;
  EFI_PHYSICAL_ADDRESS        DataPtr;
  EFI_STATUS                  Status;

  DataPtr     = DataPtrIndex;

  //
  // Check if the Data is Volatile.
  //
  if (!Volatile) {
    if (SpiPpi == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    //
    // Data Pointer should point to the actual Address where data is to be
    // written.
    //
    if (SetByIndex) {
      DataPtr += mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase;
    }

  } else {
    //
    // Data Pointer should point to the actual Address where data is to be
    // written.
    //
    VolatileBase = (VARIABLE_STORE_HEADER *) ((UINTN) mVariableModuleGlobal->VariableGlobal.VolatileVariableBase);
    if (SetByIndex) {
      DataPtr += mVariableModuleGlobal->VariableGlobal.VolatileVariableBase;
    }

    if ((DataPtr + DataSize) >= ((UINTN) ((UINT8 *) VolatileBase + VolatileBase->Size))) {
      return EFI_INVALID_PARAMETER;
    }

    //
    // If Volatile Variable just do a simple mem copy.
    //
    CopyMem ((UINT8 *)(UINTN)DataPtr, Buffer, DataSize);
    return EFI_SUCCESS;
  }

  //
  // If we are here we are dealing with Non-Volatile Variables.
  //
  LinearOffset = (UINTN) PcdGet64 (PcdFlashNvStorageVariableBase64);
  if (LinearOffset == 0) {
    LinearOffset = (UINTN) PcdGet32 (PcdFlashNvStorageVariableBase);
  }
  CurrWritePtr  = (UINTN) DataPtr;
  CurrWriteSize = DataSize;
  CurrBuffer    = Buffer;

  if (CurrWritePtr < LinearOffset) {
    return EFI_INVALID_PARAMETER;
  }

  Status = SpiPpi->FlashWrite (
                     SpiPpi,
                     FlashRegionBios,
                     PcdGet32 (PcdFlashNvStorageVariableOffset) + (UINT32) (CurrWritePtr - LinearOffset),
                     CurrWriteSize,
                     CurrBuffer
                     );


  return Status;
}


/**

  This code gets the current status of Variable Store.

  @param VarStoreHeader  Pointer to the Variable Store Header.

  @retval EfiRaw         Variable store status is raw.
  @retval EfiValid       Variable store status is valid.
  @retval EfiInvalid     Variable store status is invalid.

**/
STATIC
VARIABLE_STORE_STATUS
GetVariableStoreStatus (
  IN VARIABLE_STORE_HEADER *VarStoreHeader
  )
{
  if ((CompareGuid (&VarStoreHeader->Signature, &gEfiAuthenticatedVariableGuid) ||
       CompareGuid (&VarStoreHeader->Signature, &gEfiVariableGuid)) &&
      VarStoreHeader->Format == VARIABLE_STORE_FORMATTED &&
      VarStoreHeader->State == VARIABLE_STORE_HEALTHY
      ) {

    return EfiValid;
  } else if (((UINT32 *)(&VarStoreHeader->Signature))[0] == 0xffffffff &&
             ((UINT32 *)(&VarStoreHeader->Signature))[1] == 0xffffffff &&
             ((UINT32 *)(&VarStoreHeader->Signature))[2] == 0xffffffff &&
             ((UINT32 *)(&VarStoreHeader->Signature))[3] == 0xffffffff &&
             VarStoreHeader->Size == 0xffffffff &&
             VarStoreHeader->Format == 0xff &&
             VarStoreHeader->State == 0xff
          ) {

    return EfiRaw;
  } else {
    return EfiInvalid;
  }
}

/**
  This code sets the size of name of variable.

  @param[in] Variable   Pointer to the Variable Header.
  @param[in] NameSize   Name size to set.

**/
STATIC
VOID
SetNameSizeOfVariable (
  IN VARIABLE_HEADER    *Variable,
  IN UINTN              NameSize
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (mVariableModuleGlobal->VariableGlobal.AuthFormat) {
    AuthVariable->NameSize = (UINT32) NameSize;
  } else {
    Variable->NameSize = (UINT32) NameSize;
  }
}

/**
  This code sets the size of variable data.

  @param[in] Variable   Pointer to the Variable Header.
  @param[in] DataSize   Data size to set.

**/
STATIC
VOID
SetDataSizeOfVariable (
  IN VARIABLE_HEADER    *Variable,
  IN UINTN              DataSize
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (mVariableModuleGlobal->VariableGlobal.AuthFormat) {
    AuthVariable->DataSize = (UINT32) DataSize;
  } else {
    Variable->DataSize = (UINT32) DataSize;
  }
}

/**
  Writes a buffer to variable storage space, in the working block.

  This function writes a buffer to variable storage space into a firmware
  volume block device. The destination is specified by parameter
  VariableBase.

  @param  VariableBase   Base address of variable to write
  @param  VariableBuffer Point to the variable data buffer.

  @retval EFI_SUCCESS    The function completed successfully.
  @retval EFI_NOT_FOUND  Fail to locate Fault Tolerant Write protocol.
  @retval EFI_ABORTED    The function could not complete successfully.

**/
STATIC
EFI_STATUS
ReflashNonVolatileStorage (
  IN EFI_PHYSICAL_ADDRESS   VariableBase,
  IN VARIABLE_STORE_HEADER  *VariableBuffer
  )
{
  EFI_STATUS            Status;
  PCH_SPI_PPI           *SpiPpi;
  UINTN                 LinearOffset;
  UINTN                 VariableStoreSize;
  UINT8                 *TempBuffer;

  DEBUG ((DEBUG_INFO, "ReflashNonVolatileStorage entry\n"));

  SpiPpi = mVariableModuleGlobal->PchSpiPpi;

  LinearOffset = (UINTN) PcdGet64 (PcdFlashNvStorageVariableBase64);
  if (LinearOffset == 0) {
    LinearOffset = (UINTN) PcdGet32 (PcdFlashNvStorageVariableBase);
  }
  VariableStoreSize = ((VARIABLE_STORE_HEADER *) ((UINTN) VariableBase))->Size;

  TempBuffer = AllocatePool ((UINTN) VariableBase - LinearOffset);
  ASSERT (TempBuffer != NULL);
  if (TempBuffer != NULL){
    CopyMem (TempBuffer, (UINT8 *) LinearOffset, (UINTN) (VariableBase - LinearOffset));

    //
    // Erase the whole NVStorage region
    //
    Status = SpiPpi->FlashErase (
                       SpiPpi,
                       FlashRegionBios,
                       PcdGet32 (PcdFlashNvStorageVariableOffset),
                       PcdGet32 (PcdFlashNvStorageVariableSize)
                       );

    //
    // Write FV header
    //
    Status = SpiPpi->FlashWrite (
                       SpiPpi,
                       FlashRegionBios,
                       PcdGet32 (PcdFlashNvStorageVariableOffset),
                       (UINT32) (VariableBase - LinearOffset),
                       TempBuffer
                       );

    //
    // Write variable store
    //
    Status = SpiPpi->FlashWrite (
                       SpiPpi,
                       FlashRegionBios,
                       PcdGet32 (PcdFlashNvStorageVariableOffset) + (UINT32) (VariableBase - LinearOffset),
                       (UINT32) VariableStoreSize,
                       (UINT8 *) VariableBuffer
                       );
  }
  return Status;
}

/**

  Variable store garbage collection and reclaim operation.

  @param[in]      VariableBase            Base address of variable store.
  @param[out]     LastVariableOffset      Offset of last variable.
  @param[in]      IsVolatile              The variable store is volatile or not;
                                          if it is non-volatile, need FTW.
  @param[in, out] UpdatingPtrTrack        Pointer to updating variable pointer track structure.
  @param[in]      NewVariable             Pointer to new variable.
  @param[in]      NewVariableSize         New variable size.

  @return EFI_SUCCESS                  Reclaim operation has finished successfully.
  @return EFI_OUT_OF_RESOURCES         No enough memory resources or variable space.
  @return Others                       Unexpect error happened during reclaim operation.

**/
STATIC
EFI_STATUS
Reclaim (
  IN     EFI_PHYSICAL_ADDRESS         VariableBase,
  OUT    UINTN                        *LastVariableOffset,
  IN     BOOLEAN                      IsVolatile,
  IN OUT VARIABLE_POINTER_TRACK       *UpdatingPtrTrack,
  IN     VARIABLE_HEADER              *NewVariable,
  IN     UINTN                        NewVariableSize
  )
{
  VARIABLE_HEADER       *Variable;
  VARIABLE_HEADER       *AddedVariable;
  VARIABLE_HEADER       *NextVariable;
  VARIABLE_HEADER       *NextAddedVariable;
  VARIABLE_STORE_HEADER *VariableStoreHeader;
  UINT8                 *ValidBuffer;
  UINTN                 MaximumBufferSize;
  UINTN                 VariableSize;
  UINTN                 NameSize;
  UINT8                 *CurrPtr;
  VOID                  *Point0;
  VOID                  *Point1;
  BOOLEAN               FoundAdded;
  EFI_STATUS            Status;
  UINTN                 CommonVariableTotalSize;
  UINTN                 HwErrVariableTotalSize;
  VARIABLE_HEADER       *UpdatingVariable;
  VARIABLE_HEADER       *UpdatingInDeletedTransition;

  UpdatingVariable = NULL;
  UpdatingInDeletedTransition = NULL;
  if (UpdatingPtrTrack != NULL) {
    UpdatingVariable = UpdatingPtrTrack->CurrPtr;
    UpdatingInDeletedTransition = UpdatingPtrTrack->InDeletedTransitionPtr;
  }

  VariableStoreHeader = (VARIABLE_STORE_HEADER *) ((UINTN) VariableBase);

  CommonVariableTotalSize = 0;
  HwErrVariableTotalSize  = 0;

  if (IsVolatile) {
    //
    // Start Pointers for the variable.
    //
    Variable          = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader);
    MaximumBufferSize = sizeof (VARIABLE_STORE_HEADER);

    while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)) {
      NextVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
      if ((Variable->State == VAR_ADDED || Variable->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) &&
          Variable != UpdatingVariable &&
          Variable != UpdatingInDeletedTransition
         ) {
        VariableSize = (UINTN) NextVariable - (UINTN) Variable;
        MaximumBufferSize += VariableSize;
      }

      Variable = NextVariable;
    }

    if (NewVariable != NULL) {
      //
      // Add the new variable size.
      //
      MaximumBufferSize += NewVariableSize;
    }

    //
    // Reserve the 1 Bytes with Oxff to identify the
    // end of the variable buffer.
    //
    MaximumBufferSize += 1;
    ValidBuffer = AllocatePool (MaximumBufferSize);
    if (ValidBuffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    //
    // For NV variable reclaim, don't allocate pool here and just use mNvVariableCache
    // as the buffer to reduce SMRAM consumption for SMM variable driver.
    //
    MaximumBufferSize = mNvVariableCache->Size;
    ValidBuffer = (UINT8 *) mNvVariableCache;
  }

  SetMem (ValidBuffer, MaximumBufferSize, 0xff);

  //
  // Copy variable store header.
  //
  CopyMem (ValidBuffer, VariableStoreHeader, sizeof (VARIABLE_STORE_HEADER));
  CurrPtr = (UINT8 *) GetStartPointer ((VARIABLE_STORE_HEADER *) ValidBuffer);

  //
  // Reinstall all ADDED variables as long as they are not identical to Updating Variable.
  //
  Variable = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader);
  while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)) {
    NextVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
    if (Variable != UpdatingVariable && Variable->State == VAR_ADDED) {
      VariableSize = (UINTN) NextVariable - (UINTN) Variable;
      CopyMem (CurrPtr, (UINT8 *) Variable, VariableSize);
      CurrPtr += VariableSize;
      if ((!IsVolatile) && ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD)) {
        HwErrVariableTotalSize += VariableSize;
      } else if ((!IsVolatile) && ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != EFI_VARIABLE_HARDWARE_ERROR_RECORD)) {
        CommonVariableTotalSize += VariableSize;
      }
    }
    Variable = NextVariable;
  }

  //
  // Reinstall all in delete transition variables.
  //
  Variable = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader);
  while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)) {
    NextVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
    if (Variable != UpdatingVariable && Variable != UpdatingInDeletedTransition && Variable->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {

      //
      // Buffer has cached all ADDED variable.
      // Per IN_DELETED variable, we have to guarantee that
      // no ADDED one in previous buffer.
      //

      FoundAdded = FALSE;
      AddedVariable = (VARIABLE_HEADER *)GetStartPointer ((VARIABLE_STORE_HEADER *) ValidBuffer);
      while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)AddedVariable)) {
        NextAddedVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)AddedVariable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
        NameSize = NameSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)AddedVariable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
        if (CompareGuid (GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)AddedVariable, mVariableModuleGlobal->VariableGlobal.AuthFormat), GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)) &&
            NameSize == NameSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)
           ) {
          Point0 = (VOID *) GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)AddedVariable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
          Point1 = (VOID *) GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
          if (CompareMem (Point0, Point1, NameSize) == 0) {
            FoundAdded = TRUE;
            break;
          }
        }
        AddedVariable = NextAddedVariable;
      }
      if (!FoundAdded) {
        //
        // Promote VAR_IN_DELETED_TRANSITION to VAR_ADDED.
        //
        VariableSize = (UINTN) NextVariable - (UINTN) Variable;
        CopyMem (CurrPtr, (UINT8 *) Variable, VariableSize);
        ((VARIABLE_HEADER *) CurrPtr)->State = VAR_ADDED;
        CurrPtr += VariableSize;
        if ((!IsVolatile) && ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD)) {
          HwErrVariableTotalSize += VariableSize;
        } else if ((!IsVolatile) && ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != EFI_VARIABLE_HARDWARE_ERROR_RECORD)) {
          CommonVariableTotalSize += VariableSize;
        }
      }
    }

    Variable = NextVariable;
  }

  //
  // Install the new variable if it is not NULL.
  //
  if (NewVariable != NULL) {
    if ((UINTN) (CurrPtr - ValidBuffer) + NewVariableSize > VariableStoreHeader->Size) {
      //
      // No enough space to store the new variable.
      //
      Status = EFI_OUT_OF_RESOURCES;
      goto Done;
    }
    if (!IsVolatile) {
      if ((NewVariable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
        HwErrVariableTotalSize += NewVariableSize;
      } else if ((NewVariable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
        CommonVariableTotalSize += NewVariableSize;
      }
      if ((HwErrVariableTotalSize > PcdGet32 (PcdHwErrStorageSize)) ||
          (CommonVariableTotalSize > VariableStoreHeader->Size - sizeof (VARIABLE_STORE_HEADER) - PcdGet32 (PcdHwErrStorageSize))) {
        //
        // No enough space to store the new variable by NV or NV+HR attribute.
        //
        Status = EFI_OUT_OF_RESOURCES;
        goto Done;
      }
    }

    CopyMem (CurrPtr, (UINT8 *) NewVariable, NewVariableSize);
    ((VARIABLE_HEADER *) CurrPtr)->State = VAR_ADDED;
    if (UpdatingVariable != NULL) {
      UpdatingPtrTrack->CurrPtr = (VARIABLE_HEADER *)((UINTN)UpdatingPtrTrack->StartPtr + ((UINTN)CurrPtr - (UINTN)GetStartPointer ((VARIABLE_STORE_HEADER *) ValidBuffer)));
      UpdatingPtrTrack->InDeletedTransitionPtr = NULL;
    }
    CurrPtr += NewVariableSize;
  }

  if (IsVolatile) {
    //
    // If volatile variable store, just copy valid buffer.
    //
    SetMem ((UINT8 *) (UINTN) VariableBase, VariableStoreHeader->Size, 0xff);
    CopyMem ((UINT8 *) (UINTN) VariableBase, ValidBuffer, (UINTN) (CurrPtr - ValidBuffer));
    *LastVariableOffset = (UINTN) (CurrPtr - ValidBuffer);
    Status  = EFI_SUCCESS;
  } else {
    //
    // If non-volatile variable store, use SPI PPI to perform reclaim.
    //
    Status = ReflashNonVolatileStorage (
              VariableBase,
              (VARIABLE_STORE_HEADER *) ValidBuffer
              );
    if (!EFI_ERROR (Status)) {
      *LastVariableOffset = (UINTN) (CurrPtr - ValidBuffer);
      mVariableModuleGlobal->HwErrVariableTotalSize = HwErrVariableTotalSize;
      mVariableModuleGlobal->CommonVariableTotalSize = CommonVariableTotalSize;
    } else {
      Variable = (VARIABLE_HEADER *)GetStartPointer ((VARIABLE_STORE_HEADER *)(UINTN)VariableBase);
      while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)) {
        NextVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
        VariableSize = (UINTN) NextVariable - (UINTN) Variable;
        if ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
          mVariableModuleGlobal->HwErrVariableTotalSize += VariableSize;
        } else if ((Variable->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
          mVariableModuleGlobal->CommonVariableTotalSize += VariableSize;
        }

        Variable = NextVariable;
      }
      *LastVariableOffset = (UINTN) Variable - (UINTN) VariableBase;
    }
  }

Done:
  if (!IsVolatile) {
    //
    // For NV variable reclaim, we use mNvVariableCache as the buffer, so copy the data back.
    //
    CopyMem (mNvVariableCache, (UINT8 *)(UINTN)VariableBase, VariableStoreHeader->Size);
  }

  return Status;
}

/**
  Find the variable in the specified variable store.

  @param[in]       VariableName        Name of the variable to be found
  @param[in]       VendorGuid          Vendor GUID to be found.
  @param[in]       IgnoreRtCheck       Ignore EFI_VARIABLE_RUNTIME_ACCESS attribute
                                       check at runtime when searching variable.
  @param[in, out]  PtrTrack            Variable Track Pointer structure that contains Variable Information.

  @retval          EFI_SUCCESS         Variable found successfully
  @retval          EFI_NOT_FOUND       Variable not found
**/
EFI_STATUS
FindVariableEx (
  IN     CHAR16                  *VariableName,
  IN     EFI_GUID                *VendorGuid,
  IN     BOOLEAN                 IgnoreRtCheck,
  IN OUT VARIABLE_POINTER_TRACK  *PtrTrack
  )
{
  VARIABLE_HEADER                *InDeletedVariable;
  VOID                           *Point;

  PtrTrack->InDeletedTransitionPtr = NULL;

  //
  // Find the variable by walk through HOB, volatile and non-volatile variable store.
  //
  InDeletedVariable  = NULL;

  for ( PtrTrack->CurrPtr = PtrTrack->StartPtr
      ; IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr) && PtrTrack->CurrPtr >= PtrTrack->EndPtr
      ; PtrTrack->CurrPtr = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat)
      ) {
    if (PtrTrack->CurrPtr->State == VAR_ADDED ||
        PtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)
       ) {
      if (VariableName[0] == 0) {
        if (PtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
          InDeletedVariable   = PtrTrack->CurrPtr;
        } else {
          PtrTrack->InDeletedTransitionPtr = InDeletedVariable;
          return EFI_SUCCESS;
        }
      } else {
        if (CompareGuid (VendorGuid, GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat))) {
          Point = (VOID *) GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);

          ASSERT (NameSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat) != 0);
          if (CompareMem (VariableName, Point, NameSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)PtrTrack->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat)) == 0) {
            if (PtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
              InDeletedVariable     = PtrTrack->CurrPtr;
            } else {
              PtrTrack->InDeletedTransitionPtr = InDeletedVariable;
              return EFI_SUCCESS;
            }
          }
        }
      }
    }
  }

  PtrTrack->CurrPtr = InDeletedVariable;
  return (PtrTrack->CurrPtr  == NULL) ? EFI_NOT_FOUND : EFI_SUCCESS;
}


/**
  Finds variable in storage blocks of volatile and non-volatile storage areas.

  This code finds variable in storage blocks of volatile and non-volatile storage areas.
  If VariableName is an empty string, then we just return the first
  qualified variable without comparing VariableName and VendorGuid.
  If IgnoreRtCheck is TRUE, then we ignore the EFI_VARIABLE_RUNTIME_ACCESS attribute check
  at runtime when searching existing variable, only VariableName and VendorGuid are compared.
  Otherwise, variables without EFI_VARIABLE_RUNTIME_ACCESS are not visible at runtime.

  @param[in]   VariableName           Name of the variable to be found.
  @param[in]   VendorGuid             Vendor GUID to be found.
  @param[out]  PtrTrack               VARIABLE_POINTER_TRACK structure for output,
                                      including the range searched and the target position.
  @param[in]   Global                 Pointer to VARIABLE_GLOBAL structure, including
                                      base of volatile variable storage area, base of
                                      NV variable storage area, and a lock.
  @param[in]   IgnoreRtCheck          Ignore EFI_VARIABLE_RUNTIME_ACCESS attribute
                                      check at runtime when searching variable.

  @retval EFI_INVALID_PARAMETER       If VariableName is not an empty string, while
                                      VendorGuid is NULL.
  @retval EFI_SUCCESS                 Variable successfully found.
  @retval EFI_NOT_FOUND               Variable not found

**/
EFI_STATUS
FindVariable (
  IN  CHAR16                  *VariableName,
  IN  EFI_GUID                *VendorGuid,
  OUT VARIABLE_POINTER_TRACK  *PtrTrack,
  IN  PEI_VARIABLE_GLOBAL     *Global,
  IN  BOOLEAN                 IgnoreRtCheck
  )
{
  EFI_STATUS              Status;
  VARIABLE_STORE_HEADER   *VariableStoreHeader[VariableStoreTypeMax];
  VARIABLE_STORE_TYPE     Type;

  if (VariableName[0] != 0 && VendorGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // 0: Volatile, 1: HOB, 2: Non-Volatile.
  // The index and attributes mapping must be kept in this order as RuntimeServiceGetNextVariableName
  // make use of this mapping to implement search algorithm.
  //
  VariableStoreHeader[VariableStoreTypeVolatile] = (VARIABLE_STORE_HEADER *) (UINTN) Global->VolatileVariableBase;
  VariableStoreHeader[VariableStoreTypeHob]      = (VARIABLE_STORE_HEADER *) (UINTN) Global->HobVariableBase;
  VariableStoreHeader[VariableStoreTypeNv]       = mNvVariableCache;

  //
  // Find the variable by walk through HOB, volatile and non-volatile variable store.
  //
  for (Type = (VARIABLE_STORE_TYPE) 0; Type < VariableStoreTypeMax; Type++) {
    if (VariableStoreHeader[Type] == NULL) {
      continue;
    }

    PtrTrack->StartPtr = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader[Type]);
    PtrTrack->EndPtr   = (VARIABLE_HEADER *)GetEndPointer   (VariableStoreHeader[Type]);
    PtrTrack->Volatile = (BOOLEAN) (Type == VariableStoreTypeVolatile);

    Status = FindVariableEx (VariableName, VendorGuid, IgnoreRtCheck, PtrTrack);
    if (!EFI_ERROR (Status)) {
      return Status;
    }
  }
  return EFI_NOT_FOUND;
}

/**
  Update the variable region with Variable information. These are the same
  arguments as the EFI Variable services.

  @param[in] VariableName       Name of variable.
  @param[in] VendorGuid         Guid of variable.
  @param[in] Data               Variable data.
  @param[in] DataSize           Size of data. 0 means delete.
  @param[in] Attributes         Attributes of the variable.
  @param[in, out] CacheVariable The variable information which is used to keep track of variable usage.

  @retval EFI_SUCCESS           The update operation is success.
  @retval EFI_OUT_OF_RESOURCES  Variable region is full, can not write other data into this region.

**/
STATIC
EFI_STATUS
UpdateVariable (
  IN      CHAR16                      *VariableName,
  IN      EFI_GUID                    *VendorGuid,
  IN      VOID                        *Data,
  IN      UINTN                       DataSize,
  IN      UINT32                      Attributes      OPTIONAL,
  IN OUT  VARIABLE_POINTER_TRACK      *CacheVariable
  )
{
  EFI_STATUS                          Status;
  VARIABLE_HEADER                     *NextVariable;
  UINTN                               ScratchSize;
  UINTN                               NonVolatileVarableStoreSize;
  UINTN                               VarNameOffset;
  UINTN                               VarDataOffset;
  UINTN                               VarNameSize;
  UINTN                               VarSize;
  BOOLEAN                             Volatile;
  PCH_SPI_PPI                         *SpiPpi;
  UINT8                               State;
  VARIABLE_POINTER_TRACK              *Variable;
  VARIABLE_POINTER_TRACK              NvVariable;
  VARIABLE_STORE_HEADER               *VariableStoreHeader;
  UINTN                               CacheOffset;
  AUTHENTICATED_VARIABLE_HEADER       *AuthVariable;


  if ((CacheVariable->CurrPtr == NULL) || CacheVariable->Volatile) {
    Variable = CacheVariable;
  } else {
    //
    // Update/Delete existing NV variable.
    // CacheVariable points to the variable in the memory copy of Flash area
    // Now let Variable points to the same variable in Flash area.
    //
    VariableStoreHeader  = (VARIABLE_STORE_HEADER *) ((UINTN) mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase);
    Variable = &NvVariable;
    Variable->StartPtr = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader);
    Variable->EndPtr   = (VARIABLE_HEADER *)GetEndPointer (VariableStoreHeader);
    Variable->CurrPtr  = (VARIABLE_HEADER *)((UINTN)Variable->StartPtr + ((UINTN)CacheVariable->CurrPtr - (UINTN)CacheVariable->StartPtr));
    if (CacheVariable->InDeletedTransitionPtr != NULL) {
      Variable->InDeletedTransitionPtr = (VARIABLE_HEADER *)((UINTN)Variable->StartPtr + ((UINTN)CacheVariable->InDeletedTransitionPtr - (UINTN)CacheVariable->StartPtr));
    } else {
      Variable->InDeletedTransitionPtr = NULL;
    }
    Variable->Volatile = FALSE;
  }

  SpiPpi = mVariableModuleGlobal->PchSpiPpi;

  //
  // Tricky part: Use scratch data area at the end of volatile variable store
  // as a temporary storage.
  //
  NextVariable = (VARIABLE_HEADER *)GetEndPointer ((VARIABLE_STORE_HEADER *) ((UINTN) mVariableModuleGlobal->VariableGlobal.VolatileVariableBase));
  ScratchSize = MAX (PcdGet32 (PcdMaxVariableSize), PcdGet32 (PcdMaxHardwareErrorVariableSize));
  SetMem (NextVariable, ScratchSize, 0xff);


  if (Variable->CurrPtr != NULL) {
    //
    // Update/Delete existing variable.
    //

    //
    // Setting a data variable with no access, or zero DataSize attributes
    // causes it to be deleted.
    //
    if (DataSize == 0 || (Attributes & (EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS)) == 0) {
      if (Variable->InDeletedTransitionPtr != NULL) {
        //
        // Both ADDED and IN_DELETED_TRANSITION variable are present,
        // set IN_DELETED_TRANSITION one to DELETED state first.
        //
        State = Variable->InDeletedTransitionPtr->State;
        State &= VAR_DELETED;
        Status = UpdateVariableStore (
                   &mVariableModuleGlobal->VariableGlobal,
                   Variable->Volatile,
                   FALSE,
                   SpiPpi,
                   (UINTN) &Variable->InDeletedTransitionPtr->State,
                   sizeof (UINT8),
                   &State
                   );
        if (!EFI_ERROR (Status)) {
          if (!Variable->Volatile) {
            ASSERT (CacheVariable->InDeletedTransitionPtr != NULL);
            CacheVariable->InDeletedTransitionPtr->State = State;
          }
        } else {
          goto Done;
        }
      }

      State = Variable->CurrPtr->State;
      State &= VAR_DELETED;

      Status = UpdateVariableStore (
                 &mVariableModuleGlobal->VariableGlobal,
                 Variable->Volatile,
                 FALSE,
                 SpiPpi,
                 (UINTN) &Variable->CurrPtr->State,
                 sizeof (UINT8),
                 &State
                 );
      if (!EFI_ERROR (Status)) {
        UpdateVariableInfo (VariableName, VendorGuid, Variable->Volatile, FALSE, FALSE, TRUE, FALSE);
        if (!Variable->Volatile) {
          CacheVariable->CurrPtr->State = State;
          FlushHobVariableToFlash (VariableName, VendorGuid);
        }
      }
      goto Done;
    }
    //
    // If the variable is marked valid, and the same data has been passed in,
    // then return to the caller immediately.
    //
    if (DataSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)Variable->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat) == DataSize &&
        (CompareMem (Data, GetVariableDataPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable->CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat), DataSize) == 0)) {

      UpdateVariableInfo (VariableName, VendorGuid, Variable->Volatile, FALSE, TRUE, FALSE, FALSE);
      Status = EFI_SUCCESS;
      goto Done;
    } else if ((Variable->CurrPtr->State == VAR_ADDED) ||
               (Variable->CurrPtr->State == (VAR_ADDED & VAR_IN_DELETED_TRANSITION))) {

      //
      // Mark the old variable as in delete transition.
      //
      State = Variable->CurrPtr->State;
      State &= VAR_IN_DELETED_TRANSITION;

      Status = UpdateVariableStore (
                 &mVariableModuleGlobal->VariableGlobal,
                 Variable->Volatile,
                 FALSE,
                 SpiPpi,
                 (UINTN) &Variable->CurrPtr->State,
                 sizeof (UINT8),
                 &State
                 );
      if (EFI_ERROR (Status)) {
        goto Done;
      }
      if (!Variable->Volatile) {
        CacheVariable->CurrPtr->State = State;
      }
    }
  } else {
    //
    // Not found existing variable. Create a new variable.
    //

    //
    // Make sure we are trying to create a new variable.
    // Setting a data variable with zero DataSize or no access attributes means to delete it.
    //
    if (DataSize == 0 || (Attributes & (EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS)) == 0) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }

  }

  //
  // Function part - create a new variable and copy the data.
  // Both update a variable and create a variable will come here.
  //
  NextVariable->StartId     = VARIABLE_DATA;
  //
  // NextVariable->State = VAR_ADDED;
  //
  NextVariable->Reserved        = 0;
  if (mVariableModuleGlobal->VariableGlobal.AuthFormat) {
    AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) NextVariable;
    AuthVariable->PubKeyIndex    = 0;
    AuthVariable->MonotonicCount = 0;
    ZeroMem (&AuthVariable->TimeStamp, sizeof (EFI_TIME));
  }

  NextVariable->Attributes  = Attributes;

  VarNameOffset                 = GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat);
  VarNameSize                   = StrSize (VariableName);
  CopyMem (
    (UINT8 *) ((UINTN) NextVariable + VarNameOffset),
    VariableName,
    VarNameSize
    );
  VarDataOffset = VarNameOffset + VarNameSize + GET_PAD_SIZE (VarNameSize);
  CopyMem (
    (UINT8 *) ((UINTN) NextVariable + VarDataOffset),
    Data,
    DataSize
    );
  CopyMem (GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)NextVariable, mVariableModuleGlobal->VariableGlobal.AuthFormat), VendorGuid, sizeof (EFI_GUID));
  //
  // There will be pad bytes after Data, the NextVariable->NameSize and
  // NextVariable->DataSize should not include pad size so that variable
  // service can get actual size in GetVariable.
  //
  SetNameSizeOfVariable (NextVariable, VarNameSize);
  SetDataSizeOfVariable (NextVariable, DataSize);

  //
  // The actual size of the variable that stores in storage should
  // include pad size.
  //
  VarSize = VarDataOffset + DataSize + GET_PAD_SIZE (DataSize);
  if ((Attributes & EFI_VARIABLE_NON_VOLATILE) != 0) {
    //
    // Create a nonvolatile variable.
    //
    Volatile = FALSE;
    NonVolatileVarableStoreSize = ((VARIABLE_STORE_HEADER *)(UINTN)(mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase))->Size;
    if ((((Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != 0)
      && ((VarSize + mVariableModuleGlobal->HwErrVariableTotalSize) > PcdGet32 (PcdHwErrStorageSize)))
      || (((Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == 0)
      && ((VarSize + mVariableModuleGlobal->CommonVariableTotalSize) > NonVolatileVarableStoreSize - sizeof (VARIABLE_STORE_HEADER) - PcdGet32 (PcdHwErrStorageSize)))) {
      //
      // Perform garbage collection & reclaim operation, and integrate the new variable at the same time.
      //
      Status = Reclaim (
                 mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase,
                 &mVariableModuleGlobal->NonVolatileLastVariableOffset,
                 FALSE,
                 Variable,
                 NextVariable,
                 HEADER_ALIGN (VarSize)
                 );
      if (!EFI_ERROR (Status)) {
        //
        // The new variable has been integrated successfully during reclaiming.
        //
        if (Variable->CurrPtr != NULL) {
          CacheVariable->CurrPtr = (VARIABLE_HEADER *)((UINTN) CacheVariable->StartPtr + ((UINTN) Variable->CurrPtr - (UINTN) Variable->StartPtr));
          CacheVariable->InDeletedTransitionPtr = NULL;
        }
        UpdateVariableInfo (VariableName, VendorGuid, FALSE, FALSE, TRUE, FALSE, FALSE);
        FlushHobVariableToFlash (VariableName, VendorGuid);
      }
      goto Done;
    }
    //
    // Four steps
    // 1. Write variable header
    // 2. Set variable state to header valid
    // 3. Write variable data
    // 4. Set variable state to valid
    //
    //
    // Step 1:
    //
    CacheOffset = mVariableModuleGlobal->NonVolatileLastVariableOffset;
    Status = UpdateVariableStore (
               &mVariableModuleGlobal->VariableGlobal,
               FALSE,
               TRUE,
               SpiPpi,
               mVariableModuleGlobal->NonVolatileLastVariableOffset,
               (UINT32) GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat),
               (UINT8 *) NextVariable
               );

    if (EFI_ERROR (Status)) {
      goto Done;
    }

    //
    // Step 2:
    //
    NextVariable->State = VAR_HEADER_VALID_ONLY;
    Status = UpdateVariableStore (
               &mVariableModuleGlobal->VariableGlobal,
               FALSE,
               TRUE,
               SpiPpi,
               mVariableModuleGlobal->NonVolatileLastVariableOffset + OFFSET_OF (VARIABLE_HEADER, State),
               sizeof (UINT8),
               &NextVariable->State
               );

    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // Step 3:
    //
    Status = UpdateVariableStore (
               &mVariableModuleGlobal->VariableGlobal,
               FALSE,
               TRUE,
               SpiPpi,
               mVariableModuleGlobal->NonVolatileLastVariableOffset + GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat),
               (UINT32) (VarSize - GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat)),
               (UINT8 *) NextVariable + GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat)
               );

    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // Step 4:
    //
    NextVariable->State = VAR_ADDED;
    Status = UpdateVariableStore (
               &mVariableModuleGlobal->VariableGlobal,
               FALSE,
               TRUE,
               SpiPpi,
               mVariableModuleGlobal->NonVolatileLastVariableOffset + OFFSET_OF (VARIABLE_HEADER, State),
               sizeof (UINT8),
               &NextVariable->State
               );

    if (EFI_ERROR (Status)) {
      goto Done;
    }

    mVariableModuleGlobal->NonVolatileLastVariableOffset += HEADER_ALIGN (VarSize);

    if ((Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != 0) {
      mVariableModuleGlobal->HwErrVariableTotalSize += HEADER_ALIGN (VarSize);
    } else {
      mVariableModuleGlobal->CommonVariableTotalSize += HEADER_ALIGN (VarSize);
    }
    //
    // update the memory copy of Flash region.
    //
    CopyMem ((UINT8 *)mNvVariableCache + CacheOffset, (UINT8 *)NextVariable, VarSize);
  } else {
    //
    // Create a volatile variable.
    //
    Volatile = TRUE;

    if ((UINT32) (VarSize + mVariableModuleGlobal->VolatileLastVariableOffset) >
        ((VARIABLE_STORE_HEADER *) ((UINTN) (mVariableModuleGlobal->VariableGlobal.VolatileVariableBase)))->Size) {
      //
      // Perform garbage collection & reclaim operation, and integrate the new variable at the same time.
      //
      Status = Reclaim (
                 mVariableModuleGlobal->VariableGlobal.VolatileVariableBase,
                 &mVariableModuleGlobal->VolatileLastVariableOffset,
                 TRUE,
                 Variable,
                 NextVariable,
                 HEADER_ALIGN (VarSize)
                 );
      if (!EFI_ERROR (Status)) {
        //
        // The new variable has been integrated successfully during reclaiming.
        //
        if (Variable->CurrPtr != NULL) {
          CacheVariable->CurrPtr = (VARIABLE_HEADER *)((UINTN) CacheVariable->StartPtr + ((UINTN) Variable->CurrPtr - (UINTN) Variable->StartPtr));
          CacheVariable->InDeletedTransitionPtr = NULL;
        }
        UpdateVariableInfo (VariableName, VendorGuid, TRUE, FALSE, TRUE, FALSE, FALSE);
      }
      goto Done;
    }

    NextVariable->State = VAR_ADDED;
    Status = UpdateVariableStore (
               &mVariableModuleGlobal->VariableGlobal,
               TRUE,
               TRUE,
               SpiPpi,
               mVariableModuleGlobal->VolatileLastVariableOffset,
               (UINT32) VarSize,
               (UINT8 *) NextVariable
               );

    if (EFI_ERROR (Status)) {
      goto Done;
    }

    mVariableModuleGlobal->VolatileLastVariableOffset += HEADER_ALIGN (VarSize);
  }

  //
  // Mark the old variable as deleted.
  //
  if (!EFI_ERROR (Status) && Variable->CurrPtr != NULL) {
    if (Variable->InDeletedTransitionPtr != NULL) {
      //
      // Both ADDED and IN_DELETED_TRANSITION old variable are present,
      // set IN_DELETED_TRANSITION one to DELETED state first.
      //
      State = Variable->InDeletedTransitionPtr->State;
      State &= VAR_DELETED;
      Status = UpdateVariableStore (
                 &mVariableModuleGlobal->VariableGlobal,
                 Variable->Volatile,
                 FALSE,
                 SpiPpi,
                 (UINTN) &Variable->InDeletedTransitionPtr->State,
                 sizeof (UINT8),
                 &State
                 );
      if (!EFI_ERROR (Status)) {
        if (!Variable->Volatile) {
          ASSERT (CacheVariable->InDeletedTransitionPtr != NULL);
          CacheVariable->InDeletedTransitionPtr->State = State;
        }
      } else {
        goto Done;
      }
    }

    State = Variable->CurrPtr->State;
    State &= VAR_DELETED;

    Status = UpdateVariableStore (
             &mVariableModuleGlobal->VariableGlobal,
             Variable->Volatile,
             FALSE,
             SpiPpi,
             (UINTN) &Variable->CurrPtr->State,
             sizeof (UINT8),
             &State
             );
    if (!EFI_ERROR (Status) && !Variable->Volatile) {
      CacheVariable->CurrPtr->State = State;
    }
  }

  if (!EFI_ERROR (Status)) {
    UpdateVariableInfo (VariableName, VendorGuid, Volatile, FALSE, TRUE, FALSE, FALSE);
    if (!Volatile) {
      FlushHobVariableToFlash (VariableName, VendorGuid);
    }
  }

Done:
  return Status;
}

/**
  Check if a Unicode character is a hexadecimal character.

  This function checks if a Unicode character is a
  hexadecimal character.  The valid hexadecimal character is
  L'0' to L'9', L'a' to L'f', or L'A' to L'F'.


  @param Char           The character to check against.

  @retval TRUE          If the Char is a hexadecmial character.
  @retval FALSE         If the Char is not a hexadecmial character.

**/
STATIC
BOOLEAN
EFIAPI
IsHexaDecimalDigitCharacter (
  IN CHAR16             Char
  )
{
  return (BOOLEAN) ((Char >= L'0' && Char <= L'9') || (Char >= L'A' && Char <= L'F') || (Char >= L'a' && Char <= L'f'));
}

/**

  This code checks if variable is hardware error record variable or not.

  According to UEFI spec, hardware error record variable should use the EFI_HARDWARE_ERROR_VARIABLE VendorGuid
  and have the L"HwErrRec####" name convention, #### is a printed hex value and no 0x or h is included in the hex value.

  @param VariableName   Pointer to variable name.
  @param VendorGuid     Variable Vendor Guid.

  @retval TRUE          Variable is hardware error record variable.
  @retval FALSE         Variable is not hardware error record variable.

**/
STATIC
BOOLEAN
EFIAPI
IsHwErrRecVariable (
  IN CHAR16             *VariableName,
  IN EFI_GUID           *VendorGuid
  )
{
  if (!CompareGuid (VendorGuid, &gEfiHardwareErrorVariableGuid) ||
      (StrLen (VariableName) != StrLen (L"HwErrRec####")) ||
      (StrnCmp(VariableName, L"HwErrRec", StrLen (L"HwErrRec")) != 0) ||
      !IsHexaDecimalDigitCharacter (VariableName[0x8]) ||
      !IsHexaDecimalDigitCharacter (VariableName[0x9]) ||
      !IsHexaDecimalDigitCharacter (VariableName[0xA]) ||
      !IsHexaDecimalDigitCharacter (VariableName[0xB])) {
    return FALSE;
  }

  return TRUE;
}

/**

  This code finds variable in storage blocks (Volatile or Non-Volatile).

  @param VariableName               Name of Variable to be found.
  @param VendorGuid                 Variable vendor GUID.
  @param Attributes                 Attribute value of the variable found.
  @param DataSize                   Size of Data found. If size is less than the
                                    data, this value contains the required size.
  @param Data                       Data pointer.

  @return EFI_INVALID_PARAMETER     Invalid parameter.
  @return EFI_SUCCESS               Find the specified variable.
  @return EFI_NOT_FOUND             Not found.
  @return EFI_BUFFER_TO_SMALL       DataSize is too small for the result.

**/
EFI_STATUS
EFIAPI
PeiGetVariable (
  IN      CHAR16            *VariableName,
  IN      EFI_GUID          *VendorGuid,
  OUT     UINT32            *Attributes OPTIONAL,
  IN OUT  UINTN             *DataSize,
  OUT     VOID              *Data
  )
{
  EFI_STATUS              Status;
  VARIABLE_POINTER_TRACK  Variable;
  UINTN                   VarDataSize;

  if (VariableName == NULL || VendorGuid == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = FindVariable (VariableName, VendorGuid, &Variable, &mVariableModuleGlobal->VariableGlobal, FALSE);
  if (Variable.CurrPtr == NULL || EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Get data size
  //
  VarDataSize = DataSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
  ASSERT (VarDataSize != 0);

  if (*DataSize >= VarDataSize) {
    if (Data == NULL) {
      Status = EFI_INVALID_PARAMETER;
      goto Done;
    }

    CopyMem (Data, GetVariableDataPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat), VarDataSize);
    if (Attributes != NULL) {
      *Attributes = Variable.CurrPtr->Attributes;
    }

    *DataSize = VarDataSize;
    UpdateVariableInfo (VariableName, VendorGuid, Variable.Volatile, TRUE, FALSE, FALSE, FALSE);

    Status = EFI_SUCCESS;
    goto Done;
  } else {
    *DataSize = VarDataSize;
    Status = EFI_BUFFER_TOO_SMALL;
    goto Done;
  }

Done:
  return Status;
}

/**
  This code Finds the Next available variable.

  @param[in]  VariableName  Pointer to variable name.
  @param[in]  VendorGuid    Variable Vendor Guid.
  @param[out] VariablePtr   Pointer to variable header address.

  @return EFI_SUCCESS       Find the specified variable.
  @return EFI_NOT_FOUND     Not found.

**/
EFI_STATUS
EFIAPI
PeiGetNextVariableInternal (
  IN  CHAR16                *VariableName,
  IN  EFI_GUID              *VendorGuid,
  OUT VARIABLE_HEADER       **VariablePtr
  )
{
  VARIABLE_STORE_TYPE     Type;
  VARIABLE_POINTER_TRACK  Variable;
  VARIABLE_POINTER_TRACK  VariableInHob;
  VARIABLE_POINTER_TRACK  VariablePtrTrack;
  EFI_STATUS              Status;
  VARIABLE_STORE_HEADER   *VariableStoreHeader[VariableStoreTypeMax];

  Status = FindVariable (VariableName, VendorGuid, &Variable, &mVariableModuleGlobal->VariableGlobal, FALSE);
  if (Variable.CurrPtr == NULL || EFI_ERROR (Status)) {
    goto Done;
  }

  if (VariableName[0] != 0) {
    //
    // If variable name is not NULL, get next variable.
    //
    Variable.CurrPtr = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
  }

  //
  // 0: Volatile, 1: HOB, 2: Non-Volatile.
  // The index and attributes mapping must be kept in this order as FindVariable
  // makes use of this mapping to implement search algorithm.
  //
  VariableStoreHeader[VariableStoreTypeVolatile] = (VARIABLE_STORE_HEADER *) (UINTN) mVariableModuleGlobal->VariableGlobal.VolatileVariableBase;
  VariableStoreHeader[VariableStoreTypeHob]      = (VARIABLE_STORE_HEADER *) (UINTN) mVariableModuleGlobal->VariableGlobal.HobVariableBase;
  VariableStoreHeader[VariableStoreTypeNv]       = mNvVariableCache;

  while (TRUE) {
    //
    // Switch from Volatile to HOB, to Non-Volatile.
    //
    while (!IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr) && Variable.CurrPtr >= Variable.EndPtr) {
      //
      // Find current storage index
      //
      for (Type = (VARIABLE_STORE_TYPE) 0; Type < VariableStoreTypeMax; Type++) {
        if ((VariableStoreHeader[Type] != NULL) && (Variable.StartPtr == (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader[Type]))) {
          break;
        }
      }
      ASSERT (Type < VariableStoreTypeMax);
      //
      // Switch to next storage
      //
      for (Type++; Type < VariableStoreTypeMax; Type++) {
        if (VariableStoreHeader[Type] != NULL) {
          break;
        }
      }
      //
      // Capture the case that
      // 1. current storage is the last one, or
      // 2. no further storage
      //
      if (Type == VariableStoreTypeMax) {
        Status = EFI_NOT_FOUND;
        goto Done;
      }
      Variable.StartPtr = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader[Type]);
      Variable.EndPtr   = (VARIABLE_HEADER *)GetEndPointer   (VariableStoreHeader[Type]);
      Variable.CurrPtr  = Variable.StartPtr;
    }

    //
    // Variable is found
    //
    if (Variable.CurrPtr->State == VAR_ADDED || Variable.CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
      if (Variable.CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
        //
        // If it is a IN_DELETED_TRANSITION variable,
        // and there is also a same ADDED one at the same time,
        // don't return it.
        //
        VariablePtrTrack.StartPtr = Variable.StartPtr;
        VariablePtrTrack.EndPtr = Variable.EndPtr;
        Status = FindVariableEx (
                   GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   FALSE,
                   &VariablePtrTrack
                   );
        if (!EFI_ERROR (Status) && VariablePtrTrack.CurrPtr->State == VAR_ADDED) {
          Variable.CurrPtr = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
          continue;
        }
      }

      //
      // Don't return NV variable when HOB overrides it
      //
      if ((VariableStoreHeader[VariableStoreTypeHob] != NULL) && (VariableStoreHeader[VariableStoreTypeNv] != NULL) &&
          (Variable.StartPtr == (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader[VariableStoreTypeNv]))
         ) {
        VariableInHob.StartPtr = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader[VariableStoreTypeHob]);
        VariableInHob.EndPtr   = (VARIABLE_HEADER *)GetEndPointer   (VariableStoreHeader[VariableStoreTypeHob]);
        Status = FindVariableEx (
                   GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   FALSE,
                   &VariableInHob
                   );
        if (!EFI_ERROR (Status)) {
          Variable.CurrPtr = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
          continue;
        }
      }

      *VariablePtr = Variable.CurrPtr;
      Status = EFI_SUCCESS;
      goto Done;
    }

    Variable.CurrPtr = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable.CurrPtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
  }

Done:
  return Status;
}

/**

  This code Finds the Next available variable.

  @param VariableNameSize           Size of the variable name.
  @param VariableName               Pointer to variable name.
  @param VendorGuid                 Variable Vendor Guid.

  @return EFI_INVALID_PARAMETER     Invalid parameter.
  @return EFI_SUCCESS               Find the specified variable.
  @return EFI_NOT_FOUND             Not found.
  @return EFI_BUFFER_TO_SMALL       DataSize is too small for the result.

**/
EFI_STATUS
EFIAPI
PeiGetNextVariableName (
  IN OUT  UINTN             *VariableNameSize,
  IN OUT  CHAR16            *VariableName,
  IN OUT  EFI_GUID          *VendorGuid
  )
{
  EFI_STATUS              Status;
  UINTN                   VarNameSize;
  VARIABLE_HEADER         *VariablePtr;

  if (VariableNameSize == NULL || VariableName == NULL || VendorGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = PeiGetNextVariableInternal (VariableName, VendorGuid, &VariablePtr);
  if (!EFI_ERROR (Status)) {
    VarNameSize = NameSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)VariablePtr, mVariableModuleGlobal->VariableGlobal.AuthFormat);
    ASSERT (VarNameSize != 0);
    if (VarNameSize <= *VariableNameSize) {
      CopyMem (VariableName, GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)VariablePtr, mVariableModuleGlobal->VariableGlobal.AuthFormat), VarNameSize);
      CopyMem (VendorGuid, GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)VariablePtr, mVariableModuleGlobal->VariableGlobal.AuthFormat), sizeof (EFI_GUID));
      Status = EFI_SUCCESS;
    } else {
      Status = EFI_BUFFER_TOO_SMALL;
    }

    *VariableNameSize = VarNameSize;
  }

  return Status;
}

/**

  This code sets variable in storage blocks (Volatile or Non-Volatile).

  @param VariableName                     Name of Variable to be found.
  @param VendorGuid                       Variable vendor GUID.
  @param Attributes                       Attribute value of the variable found
  @param DataSize                         Size of Data found. If size is less than the
                                          data, this value contains the required size.
  @param Data                             Data pointer.

  @return EFI_INVALID_PARAMETER           Invalid parameter.
  @return EFI_SUCCESS                     Set successfully.
  @return EFI_OUT_OF_RESOURCES            Resource not enough to set variable.
  @return EFI_NOT_FOUND                   Not found.
  @return EFI_WRITE_PROTECTED             Variable is read-only.

**/
EFI_STATUS
EFIAPI
PeiSetVariable (
  IN CHAR16                  *VariableName,
  IN EFI_GUID                *VendorGuid,
  IN UINT32                  Attributes,
  IN UINTN                   DataSize,
  IN VOID                    *Data
  )
{
  VARIABLE_POINTER_TRACK              Variable;
  EFI_STATUS                          Status;

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
  // Prohibit to set SecureBootPolicyVariable.
  //
  if (IsSecureBootPolicyVariable (VariableName, VendorGuid)) {
    return EFI_SECURITY_VIOLATION;
  }

  //
  // Not support authenticated or append variable write yet.
  //
  if ((Attributes & (EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_APPEND_WRITE)) != 0) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //  Make sure if runtime bit is set, boot service bit is set also.
  //
  if ((Attributes & (EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS)) == EFI_VARIABLE_RUNTIME_ACCESS) {
    return EFI_INVALID_PARAMETER;
  } else if ((Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) != 0) {
    if (PcdGet32 (PcdHwErrStorageSize) == 0) {
      //
      // Not support harware error record variable variable.
      //
      return EFI_INVALID_PARAMETER;
    }
  }

  if ((UINTN)(~0) - DataSize < StrSize(VariableName)){
    //
    // Prevent whole variable size overflow
    //
    return EFI_INVALID_PARAMETER;
  }

  //
  //  The size of the VariableName, including the Unicode Null in bytes plus
  //  the DataSize is limited to maximum size of PcdGet32 (PcdMaxHardwareErrorVariableSize)
  //  bytes for HwErrRec, and PcdGet32 (PcdMaxVariableSize) bytes for the others.
  //
  if ((Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD) == EFI_VARIABLE_HARDWARE_ERROR_RECORD) {
    if (StrSize (VariableName) + DataSize > PcdGet32 (PcdMaxHardwareErrorVariableSize) - GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat)) {
      return EFI_INVALID_PARAMETER;
    }
    if (!IsHwErrRecVariable(VariableName, VendorGuid)) {
      return EFI_INVALID_PARAMETER;
    }
  } else {
    //
    //  The size of the VariableName, including the Unicode Null in bytes plus
    //  the DataSize is limited to maximum size of PcdGet32 (PcdMaxVariableSize) bytes.
    //
    if (StrSize (VariableName) + DataSize > PcdGet32 (PcdMaxVariableSize) - GetVariableHeaderSize (mVariableModuleGlobal->VariableGlobal.AuthFormat)) {
      return EFI_INVALID_PARAMETER;
    }
  }


  //
  // Check whether the input variable is already existed.
  //
  Status = FindVariable (VariableName, VendorGuid, &Variable, &mVariableModuleGlobal->VariableGlobal, TRUE);
  if (!EFI_ERROR (Status)) {
    if (Attributes != 0 && Attributes != Variable.CurrPtr->Attributes) {
      //
      // If a preexisting variable is rewritten with different attributes, SetVariable() shall not
      // modify the variable and shall return EFI_INVALID_PARAMETER. Two exceptions to this rule:
      // 1. No access attributes specified
      // 2. The only attribute differing is EFI_VARIABLE_APPEND_WRITE
      //
      Status = EFI_INVALID_PARAMETER;
      goto Done;
    }
  }


  Status = UpdateVariable (VariableName, VendorGuid, Data, DataSize, Attributes, &Variable);

Done:

  return Status;
}

/**
  Init non-volatile variable store.

  @param[out] NvFvHeader        Output pointer to non-volatile FV header address.

  @retval EFI_SUCCESS           Function successfully executed.
  @retval EFI_OUT_OF_RESOURCES  Fail to allocate enough memory resource.
  @retval EFI_VOLUME_CORRUPTED  Variable Store or Firmware Volume for Variable Store is corrupted.

**/
EFI_STATUS
InitNonVolatileVariableStore (
  OUT EFI_FIRMWARE_VOLUME_HEADER    **NvFvHeader
  )
{
  EFI_FIRMWARE_VOLUME_HEADER            *FvHeader;
  VARIABLE_HEADER                       *Variable;
  VARIABLE_HEADER                       *NextVariable;
  EFI_PHYSICAL_ADDRESS                  VariableStoreBase;
  UINT64                                VariableStoreLength;
  UINTN                                 VariableSize;
  EFI_HOB_GUID_TYPE                     *GuidHob;
  EFI_PHYSICAL_ADDRESS                  NvStorageBase;
  UINT8                                 *NvStorageData;
  UINT32                                NvStorageSize;
  FAULT_TOLERANT_WRITE_LAST_WRITE_DATA  *FtwLastWriteData;
  UINT32                                BackUpOffset;
  UINT32                                BackUpSize;
  UINT32                                HwErrStorageSize;


  //
  // Allocate runtime memory used for a memory copy of the FLASH region.
  // Keep the memory and the FLASH in sync as updates occur.
  //
  NvStorageSize = PcdGet32 (PcdFlashNvStorageVariableSize);
  NvStorageData = AllocatePages (EFI_SIZE_TO_PAGES (NvStorageSize));
  if (NvStorageData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else {
    NvStorageData = ZeroMem (NvStorageData, NvStorageSize);
  }

  NvStorageBase = (EFI_PHYSICAL_ADDRESS) PcdGet64 (PcdFlashNvStorageVariableBase64);
  if (NvStorageBase == 0) {
    NvStorageBase = (EFI_PHYSICAL_ADDRESS) PcdGet32 (PcdFlashNvStorageVariableBase);
  }
  //
  // Copy NV storage data to the memory buffer.
  //
  CopyMem (NvStorageData, (UINT8 *) (UINTN) NvStorageBase, NvStorageSize);

  //
  // Check the FTW last write data hob.
  //
  GuidHob = GetFirstGuidHob (&gEdkiiFaultTolerantWriteGuid);
  if (GuidHob != NULL) {
    FtwLastWriteData = (FAULT_TOLERANT_WRITE_LAST_WRITE_DATA *) GET_GUID_HOB_DATA (GuidHob);
    if (FtwLastWriteData->TargetAddress == NvStorageBase) {
      DEBUG ((DEBUG_INFO, "Variable: NV storage is backed up in spare block: 0x%x\n", (UINTN) FtwLastWriteData->SpareAddress));
      //
      // Copy the backed up NV storage data to the memory buffer from spare block.
      //
      CopyMem (NvStorageData, (UINT8 *) (UINTN) (FtwLastWriteData->SpareAddress), NvStorageSize);
    } else if ((FtwLastWriteData->TargetAddress > NvStorageBase) &&
               (FtwLastWriteData->TargetAddress < (NvStorageBase + NvStorageSize))) {
      //
      // Flash NV storage from the Offset is backed up in spare block.
      //
      BackUpOffset = (UINT32) (FtwLastWriteData->TargetAddress - NvStorageBase);
      BackUpSize = NvStorageSize - BackUpOffset;
      DEBUG ((DEBUG_INFO, "Variable: High partial NV storage from offset: %x is backed up in spare block: 0x%x\n", BackUpOffset, (UINTN) FtwLastWriteData->SpareAddress));
      //
      // Copy the partial backed up NV storage data to the memory buffer from spare block.
      //
      CopyMem (NvStorageData + BackUpOffset, (UINT8 *) (UINTN) FtwLastWriteData->SpareAddress, BackUpSize);
    }
  }

  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) NvStorageData;

  //
  // Check if the Firmware Volume is not corrupted
  //
  if ((FvHeader->Signature != EFI_FVH_SIGNATURE) || (!CompareGuid (&gEfiSystemNvDataFvGuid, &FvHeader->FileSystemGuid))) {
    DEBUG ((DEBUG_ERROR, "Firmware Volume for Variable Store is corrupted\n"));
    return EFI_VOLUME_CORRUPTED;
  }

  VariableStoreBase = (EFI_PHYSICAL_ADDRESS) ((UINTN) FvHeader + FvHeader->HeaderLength);
  VariableStoreLength = (UINT64) (NvStorageSize - FvHeader->HeaderLength);

  mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase = VariableStoreBase;
  mNvVariableCache = (VARIABLE_STORE_HEADER *) (UINTN) VariableStoreBase;
  if (GetVariableStoreStatus (mNvVariableCache) != EfiValid) {
    DEBUG((DEBUG_ERROR, "Variable Store header is corrupted\n"));
    return EFI_VOLUME_CORRUPTED;
  }
  ASSERT(mNvVariableCache->Size == VariableStoreLength);

  ASSERT (sizeof (VARIABLE_STORE_HEADER) <= VariableStoreLength);

  mVariableModuleGlobal->VariableGlobal.AuthFormat = (BOOLEAN)(CompareGuid (&mNvVariableCache->Signature, &gEfiAuthenticatedVariableGuid));

  HwErrStorageSize = PcdGet32 (PcdHwErrStorageSize);

  //
  // Note that in EdkII variable driver implementation, Hardware Error Record type variable
  // is stored with common variable in the same NV region. So the platform integrator should
  // ensure that the value of PcdHwErrStorageSize is less than the value of
  // (VariableStoreLength - sizeof (VARIABLE_STORE_HEADER)).
  //
  ASSERT (HwErrStorageSize < (VariableStoreLength - sizeof (VARIABLE_STORE_HEADER)));
  //
  // The max variable or hardware error variable size should be < variable store size.
  //
  ASSERT(MAX (PcdGet32 (PcdMaxVariableSize), PcdGet32 (PcdMaxHardwareErrorVariableSize)) < VariableStoreLength);

  //
  // Parse non-volatile variable data and get last variable offset.
  //
  Variable  = (VARIABLE_HEADER *)GetStartPointer ((VARIABLE_STORE_HEADER *)(UINTN)VariableStoreBase);
  while (IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)) {
    NextVariable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
    VariableSize = (UINTN) NextVariable - (UINTN) Variable;
    if ((Variable->Attributes & (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_HARDWARE_ERROR_RECORD)) == (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_HARDWARE_ERROR_RECORD)) {
      mVariableModuleGlobal->HwErrVariableTotalSize += VariableSize;
    } else {
      mVariableModuleGlobal->CommonVariableTotalSize += VariableSize;
    }

    Variable = NextVariable;
  }
  mVariableModuleGlobal->NonVolatileLastVariableOffset = (UINTN) Variable - (UINTN) VariableStoreBase;

  *NvFvHeader = FvHeader;
  return EFI_SUCCESS;
}

/**
  Flush the HOB variable to flash.

  @param[in] VariableName       Name of variable has been updated or deleted.
  @param[in] VendorGuid         Guid of variable has been updated or deleted.

**/
VOID
FlushHobVariableToFlash (
  IN CHAR16                     *VariableName,
  IN EFI_GUID                   *VendorGuid
  )
{
  EFI_STATUS                    Status;
  VARIABLE_STORE_HEADER         *VariableStoreHeader;
  VARIABLE_HEADER               *Variable;
  VOID                          *VariableData;
  BOOLEAN                       ErrorFlag;

  ErrorFlag = FALSE;

  //
  // Flush the HOB variable to flash.
  //
  if (mVariableModuleGlobal->VariableGlobal.HobVariableBase != 0) {
    VariableStoreHeader = (VARIABLE_STORE_HEADER *) (UINTN) mVariableModuleGlobal->VariableGlobal.HobVariableBase;
    //
    // Set HobVariableBase to 0, it can avoid SetVariable to call back.
    //
    mVariableModuleGlobal->VariableGlobal.HobVariableBase = 0;
    for ( Variable = (VARIABLE_HEADER *)GetStartPointer (VariableStoreHeader)
        ; IsValidVariableHeader ((AUTHENTICATED_VARIABLE_HEADER *)Variable)
        ; Variable = (VARIABLE_HEADER *)GetNextVariablePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)
        ) {
      if (Variable->State != VAR_ADDED) {
        //
        // The HOB variable has been set to DELETED state in local.
        //
        continue;
      }
      ASSERT ((Variable->Attributes & EFI_VARIABLE_NON_VOLATILE) != 0);
      if (VendorGuid == NULL || VariableName == NULL ||
          !CompareGuid (VendorGuid, GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)) ||
          StrCmp (VariableName, GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)) != 0) {
        VariableData = GetVariableDataPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat);
        Status = PeiSetVariable (
                   GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   Variable->Attributes,
                   DataSizeOfVariable ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat),
                   VariableData
                   );
        DEBUG ((DEBUG_INFO, "Variable driver flush the HOB variable to flash: %g %s %r\n", GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat), GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat), Status));
      } else {
        //
        // The updated or deleted variable is matched with this HOB variable.
        // Don't break here because we will try to set other HOB variables
        // since this variable could be set successfully.
        //
        Status = EFI_SUCCESS;
      }
      if (!EFI_ERROR (Status)) {
        //
        // If set variable successful, or the updated or deleted variable is matched with the HOB variable,
        // set the HOB variable to DELETED state in local.
        //
        DEBUG ((DEBUG_INFO, "Variable driver set the HOB variable to DELETED state in local: %g %s\n", GetVendorGuidPtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat), GetVariableNamePtr ((AUTHENTICATED_VARIABLE_HEADER *)Variable, mVariableModuleGlobal->VariableGlobal.AuthFormat)));
        Variable->State &= VAR_DELETED;
      } else {
        ErrorFlag = TRUE;
      }
    }
    if (ErrorFlag) {
      //
      // We still have HOB variable(s) not flushed in flash.
      //
      mVariableModuleGlobal->VariableGlobal.HobVariableBase = (EFI_PHYSICAL_ADDRESS) (UINTN) VariableStoreHeader;
    } else {
      //
      // All HOB variables have been flushed in flash.
      //
      DEBUG ((DEBUG_INFO, "Variable driver: all HOB variables have been flushed in flash.\n"));
    }
  }

}

/**
  Initializes variable write service after FTW was ready.

  @retval EFI_SUCCESS          Function successfully executed.
  @retval Others               Fail to initialize the variable service.

**/
EFI_STATUS
VariableWriteServiceInitialize (
  VOID
  )
{
  EFI_STATUS                      Status;
  VARIABLE_STORE_HEADER           *VariableStoreHeader;
  UINTN                           Index;
  UINT8                           Data;
  EFI_PHYSICAL_ADDRESS            VariableStoreBase;
  EFI_PHYSICAL_ADDRESS            NvStorageBase;

  NvStorageBase = (EFI_PHYSICAL_ADDRESS) PcdGet64 (PcdFlashNvStorageVariableBase64);
  if (NvStorageBase == 0) {
    NvStorageBase = (EFI_PHYSICAL_ADDRESS) PcdGet32 (PcdFlashNvStorageVariableBase);
  }
  VariableStoreBase = NvStorageBase + (((EFI_FIRMWARE_VOLUME_HEADER *)(UINTN)(NvStorageBase))->HeaderLength);

  //
  // Let NonVolatileVariableBase point to flash variable store base directly after FTW ready.
  //
  mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase = VariableStoreBase;
  VariableStoreHeader = (VARIABLE_STORE_HEADER *)(UINTN)VariableStoreBase;

  //
  // Check if the free area is really free.
  //
  for (Index = mVariableModuleGlobal->NonVolatileLastVariableOffset; Index < VariableStoreHeader->Size; Index++) {
    Data = ((UINT8 *) mNvVariableCache)[Index];
    if (Data != 0xff) {
      //
      // There must be something wrong in variable store, do reclaim operation.
      //
      Status = Reclaim (
                 mVariableModuleGlobal->VariableGlobal.NonVolatileVariableBase,
                 &mVariableModuleGlobal->NonVolatileLastVariableOffset,
                 FALSE,
                 NULL,
                 NULL,
                 0
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }
      break;
    }
  }

  FlushHobVariableToFlash (NULL, NULL);

  return EFI_SUCCESS;
}


/**
  Initializes variable store area for non-volatile and volatile variable.

  @retval EFI_SUCCESS           Function successfully executed.
  @retval EFI_OUT_OF_RESOURCES  Fail to allocate enough memory resource.

**/
EFI_STATUS
VariableCommonInitialize (
  VOID
  )
{
  EFI_STATUS                      Status;
  VARIABLE_STORE_HEADER           *VolatileVariableStore;
  VARIABLE_STORE_HEADER           *VariableStoreHeader;
  UINT64                          VariableStoreLength;
  UINTN                           ScratchSize;
  EFI_HOB_GUID_TYPE               *GuidHob;
  EFI_GUID                        *VariableGuid;
  EFI_FIRMWARE_VOLUME_HEADER      *NvFvHeader;

  //
  // Allocate runtime memory for variable driver global structure.
  //
  mVariableModuleGlobal = AllocateZeroPool (sizeof (PEI_VARIABLE_MODULE_GLOBAL));
  if (mVariableModuleGlobal == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = PeiServicesLocatePpi (
              &gPchSpiPpiGuid,
              0,
              NULL,
              (VOID **)&mVariableModuleGlobal->PchSpiPpi
              );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Init non-volatile variable store.
  //
  NvFvHeader = NULL;
  Status = InitNonVolatileVariableStore (&NvFvHeader);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // mVariableModuleGlobal->VariableGlobal.AuthFormat
  // has been initialized in InitNonVolatileVariableStore().
  // Pei Variable library does not support AuthVariable write
  if (mVariableModuleGlobal->VariableGlobal.AuthFormat) {
    DEBUG ((DEBUG_INFO, "Pei Variable library will work with auth variable format!\n"));
    VariableGuid = &gEfiAuthenticatedVariableGuid;
  } else {
    DEBUG ((DEBUG_INFO, "Pei Variable library will work without auth variable support!\n"));
    VariableGuid = &gEfiVariableGuid;
  }

  //
  // Get HOB variable store.
  //
  GuidHob = GetFirstGuidHob (VariableGuid);
  if (GuidHob != NULL) {
    VariableStoreHeader = GET_GUID_HOB_DATA (GuidHob);
    VariableStoreLength = (UINT64) (GuidHob->Header.HobLength - sizeof (EFI_HOB_GUID_TYPE));
    if (GetVariableStoreStatus (VariableStoreHeader) == EfiValid) {
      mVariableModuleGlobal->VariableGlobal.HobVariableBase = (EFI_PHYSICAL_ADDRESS) (UINTN) AllocateRuntimeCopyPool ((UINTN) VariableStoreLength, (VOID *) VariableStoreHeader);
      if (mVariableModuleGlobal->VariableGlobal.HobVariableBase == 0) {
        return EFI_OUT_OF_RESOURCES;
      }
      //
      // Make the Variable HOB invalid here so that it won't be processed by DXE Variable driver again
      // Mark it as "unhealthy"
      //
      VariableStoreHeader->State = VARIABLE_STORE_HEALTHY - 1;
    } else {
      DEBUG ((DEBUG_ERROR, "HOB Variable Store header is corrupted!\n"));
    }
  }

  //
  // Allocate memory for volatile variable store, note that there is a scratch space to store scratch data.
  //
  ScratchSize = MAX (PcdGet32 (PcdMaxVariableSize), PcdGet32 (PcdMaxHardwareErrorVariableSize));
  VolatileVariableStore = AllocateRuntimePool (PcdGet32 (PcdVariableStoreSize) + ScratchSize);
  if (VolatileVariableStore == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SetMem (VolatileVariableStore, PcdGet32 (PcdVariableStoreSize) + ScratchSize, 0xff);

  //
  // Initialize Variable Specific Data.
  //
  mVariableModuleGlobal->VariableGlobal.VolatileVariableBase = (EFI_PHYSICAL_ADDRESS) (UINTN) VolatileVariableStore;
  mVariableModuleGlobal->VolatileLastVariableOffset = (UINTN) GetStartPointer (VolatileVariableStore) - (UINTN) VolatileVariableStore;

  CopyGuid (&VolatileVariableStore->Signature, VariableGuid);
  VolatileVariableStore->Size        = PcdGet32 (PcdVariableStoreSize);
  VolatileVariableStore->Format      = VARIABLE_STORE_FORMATTED;
  VolatileVariableStore->State       = VARIABLE_STORE_HEALTHY;
  VolatileVariableStore->Reserved    = 0;
  VolatileVariableStore->Reserved1   = 0;

  Status = VariableWriteServiceInitialize ();
  return Status;
}

/**
  Provide the functionality of the variable services.

  @param  VOID

  @retval EFI_SUCCESS  If the interface could be successfully installed
  @retval Others       Returned from PeiServicesInstallPpi()
**/
EFI_STATUS
EFIAPI
PeiReadWriteVariableInit (
  VOID
  )
{
  EFI_STATUS                       Status;
  PEI_READ_WRITE_VARIABLE_PPI      *ReadWriteVariable;

  if (GetBootModeHob () == BOOT_IN_RECOVERY_MODE) {
    //
    // Avoid accessing NV storage in recover mode
    //
    return EFI_UNSUPPORTED;
  }

  Status = PeiServicesLocatePpi (
             &gPeiReadWriteVariablePpiGuid,
             0,
             NULL,
             (VOID** ) &ReadWriteVariable
             );
  if (Status == EFI_SUCCESS) {
    //
    // Avoid initializing variable service more than once.
    //
    return EFI_ALREADY_STARTED;
  }

  Status = VariableCommonInitialize ();
  if (Status == EFI_SUCCESS) {
    Status = PeiServicesInstallPpi (&mPpiListVariable);
  }

  return Status;
}

