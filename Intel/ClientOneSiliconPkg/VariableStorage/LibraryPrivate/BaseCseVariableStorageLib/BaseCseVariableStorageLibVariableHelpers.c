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
#include <Library/DebugLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageLib.h>
#include <Library/CseVariableStorageSelectorLib.h>

/**
  Sets authenticated fields in a CSE NVM variable header.

  @param[in]  AuthenticatedVariableHeader      Pointer to an authenticated CSE NVM variable header.
  @param[in]  AuthenticatedVariableFieldTrack  Pointer to a structure which maintains authenticated field values.

  @retval     EFI_SUCCESS                      The authenticated fields in the variable header were set successfully.
  @retval     EFI_INVALID_PARAMETER            A required pointer is invalid.

**/
EFI_STATUS
EFIAPI
SetAuthenticatedVariableFields (
  IN         AUTHENTICATED_VARIABLE_NVM_HEADER      *AuthenticatedVariableHeader,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK *AuthenticatedVariableFieldTrack
  )
{
  if (AuthenticatedVariableHeader   == NULL ||
    AuthenticatedVariableFieldTrack == NULL ||
    AuthenticatedVariableFieldTrack->TimeStamp == NULL
    )  {
    return EFI_INVALID_PARAMETER;
  }

  AuthenticatedVariableHeader->MonotonicCount = AuthenticatedVariableFieldTrack->MonotonicCount;
  AuthenticatedVariableHeader->PubKeyIndex    = AuthenticatedVariableFieldTrack->PubKeyIndex;

  ZeroMem (&AuthenticatedVariableHeader->TimeStamp, sizeof (EFI_TIME));
  CopyMem (&AuthenticatedVariableHeader->TimeStamp, AuthenticatedVariableFieldTrack->TimeStamp, sizeof (EFI_TIME));

  return EFI_SUCCESS;
}

/**
  Finds deleted variables in the specified CSE NVM variable store.

  If VariableName is an empty string, then we just return the first
  qualified variable without comparing VariableName and VendorGuid.

  @param[in]      VariableName            Name of the variable to be found.
  @param[in]      VendorGuid              Vendor GUID to be found.
  @param[in]      VariableStore           Pointer to a VARIABLE_NVM_STORE_HEADER structure which
                                          is the variable store to search.
  @param[in,out]  VariableTrack Ptr       Pointer to a variable NVM tracking structure which points
                                          current pointer to the variable if found.

  @retval         EFI_INVALID_PARAMETER   If VariableName is not an empty string, while
                                          VendorGuid is NULL.
  @retval         EFI_SUCCESS             Variable successfully found.
  @retval         EFI_NOT_FOUND           Variable not found

**/
EFI_STATUS
EFIAPI
FindDeletedVariable (
  IN  CONST  CHAR16                     *VariableName,
  IN  CONST  EFI_GUID                   *VendorGuid,
  IN         VARIABLE_NVM_STORE_HEADER  *VariableStorePtr,
  IN OUT     VARIABLE_NVM_POINTER_TRACK *VariablePtrTrack
  )
{
  EFI_STATUS               Status;
  VARIABLE_NVM_STORE_INFO  VariableNvmStoreInfo;
  VOID                     *VariableCandidateName;

  VariablePtrTrack->InDeletedTransitionPtr = NULL;

  Status = IsAuthenticatedVariableStore (VariableStorePtr, &VariableNvmStoreInfo.AuthFlag);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  VariableNvmStoreInfo.VariableStoreHeader = VariableStorePtr;

  //
  // Find the variable by walking through the specified variable store
  //
  for (VariablePtrTrack->CurrPtr = VariablePtrTrack->StartPtr;
       IsValidVariableHeader (VariablePtrTrack->CurrPtr, VariablePtrTrack->EndPtr);
       VariablePtrTrack->CurrPtr = GetNextVariablePtr (&VariableNvmStoreInfo, VariablePtrTrack->CurrPtr)
       ) {
    if (
      VariablePtrTrack->CurrPtr->State != VAR_ADDED &&
      VariablePtrTrack->CurrPtr->State != (VAR_IN_DELETED_TRANSITION & VAR_ADDED)
      ) {

      //
      // A variable name was given to find
      //
      if (CompareGuid (VendorGuid, &VariablePtrTrack->CurrPtr->VendorGuid)) {
        VariableCandidateName = (VOID *) GetVariableNamePtr (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag);

        ASSERT (NameSizeOfVariable (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag) != 0);
        if (CompareMem (
              VariableName,
              VariableCandidateName,
              NameSizeOfVariable (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag)
              ) == 0) {
          DEBUG ((DEBUG_INFO, "Previously deleted variable found at header address 0x%x\n", VariablePtrTrack->CurrPtr));
          return EFI_SUCCESS;
        }
      }
    }
  }
  VariablePtrTrack->CurrPtr = NULL;

  return EFI_NOT_FOUND;
}

/**
  Finds the variable in the specified CSE NVM variable store.

  If VariableName is an empty string, then we just return the first
  qualified variable without comparing VariableName and VendorGuid.

  @param[in]      VariableName            Name of the variable to be found.
  @param[in]      VendorGuid              Vendor GUID to be found.
  @param[in]      VariableStore           Pointer to a VARIABLE_NVM_STORE_HEADER structure which
                                          is the variable store to search.
  @param[in,out]  VariableTrack Ptr       Pointer to a variable NVM tracking structure which points
                                          current pointer to the variable if found.

  @retval         EFI_INVALID_PARAMETER   If VariableName is not an empty string, while
                                          VendorGuid is NULL.
  @retval         EFI_SUCCESS             Variable successfully found.
  @retval         EFI_NOT_FOUND           Variable not found

**/
EFI_STATUS
EFIAPI
FindVariableEx (
  IN  CONST  CHAR16                     *VariableName,
  IN  CONST  EFI_GUID                   *VendorGuid,
  IN         VARIABLE_NVM_STORE_HEADER  *VariableStorePtr,
  IN OUT     VARIABLE_NVM_POINTER_TRACK *VariablePtrTrack
  )
{
  EFI_STATUS               Status;
  VARIABLE_NVM_HEADER      *InDeletedTransitionVariable;
  VARIABLE_NVM_STORE_INFO  VariableNvmStoreInfo;
  VOID                     *VariableCandidateName;

  InDeletedTransitionVariable              = NULL;
  VariablePtrTrack->InDeletedTransitionPtr = NULL;

  Status = IsAuthenticatedVariableStore (VariableStorePtr, &VariableNvmStoreInfo.AuthFlag);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  VariableNvmStoreInfo.VariableStoreHeader = VariableStorePtr;

  //
  // Find the variable by walking through the specified variable store
  //
  for (VariablePtrTrack->CurrPtr = VariablePtrTrack->StartPtr;
       IsValidVariableHeader (VariablePtrTrack->CurrPtr, VariablePtrTrack->EndPtr);
       VariablePtrTrack->CurrPtr = GetNextVariablePtr (&VariableNvmStoreInfo, VariablePtrTrack->CurrPtr)
       ) {
    if (VariablePtrTrack->CurrPtr->State == VAR_ADDED ||
        VariablePtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)
        ) {

      if (VariableName[0] == 0) {
        DEBUG ((DEBUG_INFO, "The variable has been requested to be deleted.\n"));
        //
        // The variable has been requested to be deleted
        //
        if (VariablePtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
          InDeletedTransitionVariable = VariablePtrTrack->CurrPtr;
        } else {
          VariablePtrTrack->InDeletedTransitionPtr = InDeletedTransitionVariable;
          return EFI_SUCCESS;
        }
      } else {
        //
        // A variable name was given to find
        //
        if (CompareGuid (VendorGuid, &VariablePtrTrack->CurrPtr->VendorGuid)) {
          VariableCandidateName = (VOID *) GetVariableNamePtr (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag);

          ASSERT (NameSizeOfVariable (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag) != 0);
          if (CompareMem (VariableName, VariableCandidateName,
                          NameSizeOfVariable (VariablePtrTrack->CurrPtr, VariableNvmStoreInfo.AuthFlag)) == 0) {
            if (VariablePtrTrack->CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
              InDeletedTransitionVariable = VariablePtrTrack->CurrPtr;
            } else {
              VariablePtrTrack->InDeletedTransitionPtr = InDeletedTransitionVariable;
              DEBUG ((DEBUG_INFO, "Returning with variable found at header address 0x%x\n", VariablePtrTrack->CurrPtr));
              return EFI_SUCCESS;
            }
          }
        }
      }
    }
  }

  VariablePtrTrack->CurrPtr = InDeletedTransitionVariable;

  return (VariablePtrTrack->CurrPtr == NULL) ? EFI_NOT_FOUND : EFI_SUCCESS;
}

/**
  Finds the variable in CSE NVM.
  This code finds the variable in the CSE NVM variable stores enabled.

  If VariableName is an empty string, then we just return the first
  qualified variable without comparing VariableName and VendorGuid.

  @param[in]  VariableName            Name of the variable to be found.
  @param[in]  VendorGuid              Vendor GUID to be found.
  @param[in]  CseVariableStorageInfo  A pointer to a structure that contains CSE variable storage info.
  @param[out] VariablePtrTrack        VARIABLE_NVM POINTER_TRACK structure for output,
                                      including the range searched and the target position.

  @retval     EFI_INVALID_PARAMETER   If VariableName is not an empty string, while
                                      VendorGuid is NULL.
  @retval     EFI_SUCCESS             Variable successfully found.
  @retval     EFI_NOT_FOUND           Variable not found

**/
EFI_STATUS
EFIAPI
FindVariable (
  IN  CONST  CHAR16                      *VariableName,
  IN  CONST  EFI_GUID                    *VendorGuid,
  IN  CONST  CSE_VARIABLE_STORAGE_STORE  **CseVariableStorageInfo,
  OUT        VARIABLE_NVM_POINTER_TRACK  *VariablePtrTrack
  )
{
  EFI_STATUS                  Status;
  CSE_VARIABLE_STORAGE_TYPE   Type;
  VARIABLE_NVM_STORE_HEADER   *VariableStoreHeader;

  if (VariableName[0] != 0 && VendorGuid == NULL) {
    DEBUG ((DEBUG_ERROR, "VariableName and VendorGuid passed to FindVariable() are invalid.\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Determine the CSE storage area type for this variable
  //
  Type = GetCseVariableStoreStorageType (VariableName, VendorGuid, CseVariableStorageInfo);

  if (CseVariableStorageInfo[Type] == NULL || !CseVariableStorageInfo[Type]->Info.Established) {
    DEBUG ((
      DEBUG_ERROR,
      "The %a CSE variable store needed is not available for this variable.\n",
      CseVariableStorageInfo[Type]->Info.Name
      ));
    return EFI_NOT_FOUND;
  }

  VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) CseVariableStorageInfo[Type]->Info.Header;

  DEBUG ((DEBUG_INFO, "VariableStoreHeader Region Base in FindVariable() = 0x%x\n", VariableStoreHeader));

  VariablePtrTrack->CurrPtr  = NULL;
  VariablePtrTrack->StartPtr = GetStartPointer (VariableStoreHeader);
  VariablePtrTrack->EndPtr   = GetEndPointer (VariableStoreHeader);

  //
  // Do not search in this variable store if it is empty
  //
  if (
    VariableStoreHeader->VariableHeaderTotalEntries == 0 ||
    !IsValidVariableHeader (VariablePtrTrack->StartPtr, VariablePtrTrack->EndPtr)
    ) {
    DEBUG ((
      DEBUG_INFO,
      "The variable store in the %a CSE store is empty, not searching.\n",
      CseVariableStorageInfo[Type]->Info.Name
      ));
    return EFI_NOT_FOUND;
  }

  //
  // Find the variable by searching in the variable header region of the store
  //
  Status = FindVariableEx (VariableName, VendorGuid, VariableStoreHeader, VariablePtrTrack);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Found the variable in the %a CSE variable store.\n", CseVariableStorageInfo[Type]->Info.Name));
    return Status;
  }

  return EFI_NOT_FOUND;
}

/**
  Returns the next available variable in the given CSE variable stores.

  @param[in]  VariableName            Pointer to variable name.
  @param[in]  VendorGuid              Variable Vendor Guid.
  @param[in]  CseVariableStorageInfo  A pointer to a structure that contains CSE variable storage info.
  @param[out] VariablePtr             Pointer to variable header address.
  @param[out] IsAuthVariable          Indicates if the variable returned is an authenticated variable.

  @retval     EFI_SUCCESS             Found the specified variable.
  @retval     EFI_NOT_FOUND           Not found.
**/
EFI_STATUS
EFIAPI
GetNextCseVariableName (
  IN   CHAR16                     *VariableName,
  IN   EFI_GUID                   *VariableGuid,
  IN   CSE_VARIABLE_STORAGE_STORE **CseVariableStorageInfo,
  OUT  VARIABLE_NVM_HEADER        **VariablePtr,
  OUT  BOOLEAN                    *IsAuthVariable
  )
{
  CSE_VARIABLE_STORAGE_TYPE    Type;
  EFI_STATUS                   Status;
  VARIABLE_NVM_POINTER_TRACK   Variable;
  VARIABLE_NVM_POINTER_TRACK   VariablePtrTrack;
  VARIABLE_NVM_STORE_INFO      StoreInfo[CseVariableStorageTypeMax];

  //
  // In the case of a NULL variable name, FindVariable will return the first
  // variable in the appropriate CSE file store. It is recommended to make
  // a special case for the name NULL that returns the first CSE variable file
  // store type (currently implemented in CseVariableStorageSelectorLib).
  //
  Status = FindVariable (VariableName, VariableGuid, CseVariableStorageInfo, &Variable);
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (Variable.CurrPtr == NULL) {
    return EFI_NOT_FOUND;
  }

  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    if (CseVariableStorageInfo[Type] == NULL || !CseVariableStorageInfo[Type]->Info.Established) {
      StoreInfo[Type].AuthFlag = FALSE;
      StoreInfo[Type].VariableStoreHeader = NULL;
    } else {
      StoreInfo[Type].VariableStoreHeader = (VARIABLE_NVM_STORE_HEADER *) CseVariableStorageInfo[Type]->Info.Header;

      Status = IsAuthenticatedVariableStore (StoreInfo[Type].VariableStoreHeader, &StoreInfo[Type].AuthFlag);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return Status;
      }
    }
  }
  DEBUG ((DEBUG_INFO, "Beginning search algorithm in CSE variable storage GetNextVariableName().\n"));

  //
  // Find which CSE store the current variable is in, and get the next variable if the variable given was valid.
  //
  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    if (
      (StoreInfo[Type].VariableStoreHeader != NULL) &&
      (Variable.StartPtr == GetStartPointer (StoreInfo[Type].VariableStoreHeader))
      ) {
      DEBUG ((DEBUG_INFO, "Found current variable in the %a CSE store.\n", CseVariableStorageInfo[Type]->Info.Name));
      if (VariableName[0] != 0) {
        Variable.CurrPtr = GetNextVariablePtr (&StoreInfo[Type], Variable.CurrPtr);
      }
      break;
    }
  }

  while (TRUE) {
    while (!IsValidVariableHeader (Variable.CurrPtr, Variable.EndPtr)) {
      //
      // Find a new valid CSE variable file store
      //
      for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
        if (
          (StoreInfo[Type].VariableStoreHeader != NULL) &&
          (Variable.StartPtr == GetStartPointer (StoreInfo[Type].VariableStoreHeader))
          ) {
          DEBUG ((DEBUG_INFO, "Switched to the %a CSE store.\n", CseVariableStorageInfo[Type]->Info.Name));
          break;
        }
      }

      ASSERT (Type < CseVariableStorageTypeMax);

      //
      // Switch to the next CSE variable file store
      //
      for (Type++; Type < CseVariableStorageTypeMax; Type++) {
        if (StoreInfo[Type].VariableStoreHeader != NULL) {
          DEBUG ((
            DEBUG_INFO,
            "Next store type in search is %a. Header at 0x%x\n",
            CseVariableStorageInfo[Type]->Info.Name,
            StoreInfo[Type].VariableStoreHeader
            ));
          break;
        }
      }

      //
      // Check if the CSE variable file stores available have
      // been exhausted and return not found if so.
      //
      if (Type == CseVariableStorageTypeMax) {
        return EFI_NOT_FOUND;
      }

      Variable.StartPtr = GetStartPointer (StoreInfo[Type].VariableStoreHeader);
      Variable.EndPtr   = GetEndPointer   (StoreInfo[Type].VariableStoreHeader);
      Variable.CurrPtr  = Variable.StartPtr;
    }

    if (Type == CseVariableStorageTypeMax) {
      return EFI_NOT_FOUND;
    }

    //
    // A valid variable was found
    //
    if (Variable.CurrPtr->State == VAR_ADDED || Variable.CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
      if (Variable.CurrPtr->State == (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) {
        //
        // If the variable is IN_DELETED_TRANSITION and there is
        // also the same variable with the ADDED attribute, don't
        // return it.
        //
        VariablePtrTrack.StartPtr = Variable.StartPtr;
        VariablePtrTrack.EndPtr   = Variable.EndPtr;

        Status = FindVariableEx (
                   GetVariableNamePtr (Variable.CurrPtr, StoreInfo[Type].AuthFlag),
                   GetVendorGuidPtr (Variable.CurrPtr, StoreInfo[Type].AuthFlag),
                   StoreInfo[Type].VariableStoreHeader,
                   &VariablePtrTrack
                   );
        if (!EFI_ERROR (Status) && VariablePtrTrack.CurrPtr->State == VAR_ADDED) {
          Variable.CurrPtr = GetNextVariablePtr (&StoreInfo[Type], Variable.CurrPtr);
          continue;
        }
      }

      DEBUG ((
        DEBUG_INFO,
        "Found next variable. Variable header at 0x%x in the %a CSE store. StoreInfo structure at 0x%x\n",
        Variable.CurrPtr, CseVariableStorageInfo[Type]->Info.Name, &StoreInfo[Type]
        ));

      *VariablePtr = Variable.CurrPtr;
      *IsAuthVariable = StoreInfo[Type].AuthFlag;

      return EFI_SUCCESS;
    }

    Variable.CurrPtr = GetNextVariablePtr (&StoreInfo[Type], Variable.CurrPtr);
  }

  return EFI_SUCCESS;
}

/**
  Retrieves a variable's value using its name and GUID.

  Read the specified variable from the CSE NVM variable store. If the Data
  buffer is too small to hold the contents of the variable,
  the error EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the
  required buffer size to obtain the data.

  Note: It is the caller's responsibility to extensively validate the input parameters.

  @param[in]       CseVariableStorageInfo A pointer to an array of structures with CSE variable storage information.
  @param[in]       VariableName           A pointer to a null-terminated string that is the variable's name.
  @param[in]       VariableGuid           A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                          VariableGuid and VariableName must be unique.
  @param[out]      CommandInProgress      Determines whether asynchronous I/O should be used or the variable should
                                          immediately be written.
  @param[out]      Attributes             If non-NULL, on return, points to the variable's attributes.
  @param[in,out]   DataSize               On entry, points to the size in bytes of the Data buffer.
                                          On return, points to the size of the data returned in Data.
  @param[out]      Data                   Points to the buffer which will hold the returned variable value.
  @param[out]      VariableHeader         A pointer to the variable header.

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
CseVariableStorageGetVariableInternal (
  IN CONST  CSE_VARIABLE_STORAGE_STORE  **CseVariableStorageInfo,
  IN CONST  CHAR16                      *VariableName,
  IN CONST  EFI_GUID                    *VariableGuid,
  OUT       BOOLEAN                     *CommandInProgress,
  OUT       UINT32                      *Attributes,         OPTIONAL
  IN OUT    UINTN                       *DataSize,
  OUT       VOID                        *Data,
  OUT       VARIABLE_NVM_HEADER         **VariableHeader     OPTIONAL
  )
{
  CSE_VARIABLE_STORAGE_TYPE    CseVariableStorageType;

  UINTN                        VariableDataSize;
  VARIABLE_NVM_STORE_INFO      VariableNvmStoreInfo;
  VARIABLE_NVM_POINTER_TRACK   VariablePtrTrack;

  EFI_STATUS                   Status;

  if (VariableName == NULL || VariableGuid == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CseVariableStorageType = GetCseVariableStoreStorageType (VariableName, VariableGuid, CseVariableStorageInfo);

  if (
    CseVariableStorageInfo[CseVariableStorageType] == NULL ||
    !CseVariableStorageInfo[CseVariableStorageType]->Info.Established
    ) {
    DEBUG ((
      DEBUG_ERROR,
      "The %a CSE variable store is not available for this get variable request.\n",
      CseVariableStorageInfo[CseVariableStorageType]->Info.Name
      ));
    return EFI_NOT_FOUND;
  }

  VariableNvmStoreInfo.VariableStoreHeader = \
    (VARIABLE_NVM_STORE_HEADER *) CseVariableStorageInfo[CseVariableStorageType]->Info.Header;

  Status = IsAuthenticatedVariableStore (VariableNvmStoreInfo.VariableStoreHeader, &VariableNvmStoreInfo.AuthFlag);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = FindVariable (VariableName, VariableGuid, CseVariableStorageInfo, &VariablePtrTrack);
  if (VariablePtrTrack.CurrPtr == NULL) {
    DEBUG ((DEBUG_INFO, "Could not find variable \"%s\".\n", VariableName));
    return EFI_NOT_FOUND;
  } else if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred finding variable \"%s\". Status = %r\n", VariableName, Status));
    return Status;
  }

  VariableDataSize = DataSizeOfVariable (VariablePtrTrack.CurrPtr, VariableNvmStoreInfo.AuthFlag);
  ASSERT (VariableDataSize != 0);

  if (*DataSize < VariableDataSize) {
    DEBUG ((DEBUG_ERROR, "Buffer size to CseVariableStorageGetVariableInternal() is too small.\n"));

    *DataSize = VariableDataSize;
    return EFI_BUFFER_TOO_SMALL;
  } else if (Data == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *DataSize = VariableDataSize;

  if (Attributes != NULL) {
    *Attributes = VariablePtrTrack.CurrPtr->Attributes;
  }

  if (VariableHeader != NULL) {
    *VariableHeader = VariablePtrTrack.CurrPtr;
  }

  Status = CseVariableStorageInfo[CseVariableStorageType]->Read (
                                                             CseVariableStorageInfo[CseVariableStorageType],
                                                             Data,
                                                             DataSize,
                                                             VariablePtrTrack.CurrPtr->DataOffset,
                                                             CommandInProgress
                                                             );
  // The data size from non-volatile memory and the variable header should match unless a corruption
  // or synchronization issue occurred.
  ASSERT (*DataSize == DataSizeOfVariable (VariablePtrTrack.CurrPtr, VariableNvmStoreInfo.AuthFlag));

  return Status;
}