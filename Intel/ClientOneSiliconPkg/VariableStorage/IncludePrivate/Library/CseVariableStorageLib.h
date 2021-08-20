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

#ifndef _CSE_VARIABLE_STORAGE_LIB_H_
#define _CSE_VARIABLE_STORAGE_LIB_H_

#include <CseVariableStorage.h>
#include <SecurePreMemoryData.h>
#include <VariableNvmStorageFormat.h>
#include <Library/CircularBufferLib.h>
#include <Protocol/HeciProtocol.h>

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
  );

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
  );

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
  );

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
  IN  CONST  CHAR16                       *VariableName,
  IN  CONST  EFI_GUID                     *VendorGuid,
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   **CseVariableStorageInfo,
  OUT        VARIABLE_NVM_POINTER_TRACK   *VariablePtrTrack
  );

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
  );

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
  );

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
  );

#endif
