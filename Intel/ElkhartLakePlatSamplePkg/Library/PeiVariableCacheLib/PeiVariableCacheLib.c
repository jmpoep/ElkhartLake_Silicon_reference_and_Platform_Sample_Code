/** @file
  Variable Cache Library implementation file.

  This library builds a variable cache HOB consumed by the variable driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

#include <PiPei.h>
#include <VariableNvmStorageFormat.h>

#include <Guid/PeiVariableCacheHobGuid.h>
#include <Guid/VariableFormat.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/VariableCacheLib.h>

/**
  Gets the variable header size.

  @param[in]   IsAuthenticated Indicates if the variable is an authenticated variable.

  @retval      Size of variable header in bytes in type UINTN.

**/
UINTN
GetVariableHeaderSizeHob (
  IN BOOLEAN  IsAuthenticated
  )
{
  UINTN Value;

  if (IsAuthenticated) {
    Value = sizeof (AUTHENTICATED_VARIABLE_HEADER);
  } else {
    Value = sizeof (VARIABLE_HEADER);
  }

  return Value;
}

/**

  Gets the variable name size.

  @param[in]   Variable        Pointer to the Variable Header.
  @param[in]   IsAuthenticated Indicates if the variable is an authenticated variable.

  @retval      Size of the variable name in bytes.

**/
UINTN
NameSizeOfVariableHob (
  IN  VARIABLE_HEADER   *Variable,
  IN  BOOLEAN           IsAuthenticated
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (IsAuthenticated) {
    if (AuthVariable->State == (UINT8) (-1) ||
       AuthVariable->DataSize == (UINT32) (-1) ||
       AuthVariable->NameSize == (UINT32) (-1) ||
       AuthVariable->Attributes == (UINT32) (-1)) {
      return 0;
    }
    return (UINTN) AuthVariable->NameSize;
  } else {
    if (Variable->State == (UINT8) (-1) ||
        Variable->DataSize == (UINT32) (-1) ||
        Variable->NameSize == (UINT32) (-1) ||
        Variable->Attributes == (UINT32) (-1)) {
      return 0;
    }
    return (UINTN) Variable->NameSize;
  }
}

/**
  Sets the name size of a variable.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] NameSize         Name size to set.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

**/
VOID
SetNameSizeOfVariableHob (
  IN VARIABLE_HEADER    *Variable,
  IN UINTN              NameSize,
  IN BOOLEAN            IsAuthenticated
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (IsAuthenticated) {
    AuthVariable->NameSize = (UINT32) NameSize;
  } else {
    Variable->NameSize = (UINT32) NameSize;
  }
}

/**

  This code gets the size of variable data.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

  @retval    Size of variable in bytes.

**/
UINTN
DataSizeOfVariableHob (
  IN  VARIABLE_HEADER   *Variable,
  IN  BOOLEAN           IsAuthenticated
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (IsAuthenticated) {
    if (AuthVariable->State == (UINT8) (-1) ||
       AuthVariable->DataSize == (UINT32) (-1) ||
       AuthVariable->NameSize == (UINT32) (-1) ||
       AuthVariable->Attributes == (UINT32) (-1)) {
      return 0;
    }
    return (UINTN) AuthVariable->DataSize;
  } else {
    if (Variable->State == (UINT8) (-1) ||
        Variable->DataSize == (UINT32) (-1) ||
        Variable->NameSize == (UINT32) (-1) ||
        Variable->Attributes == (UINT32) (-1)) {
      return 0;
    }
    return (UINTN) Variable->DataSize;
  }
}

/**
  This code sets the size of variable data.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] DataSize         Data size to set.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

**/
VOID
SetDataSizeOfVariableHob (
  IN VARIABLE_HEADER    *Variable,
  IN UINTN              DataSize,
  IN BOOLEAN            IsAuthenticated
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (IsAuthenticated) {
    AuthVariable->DataSize = (UINT32) DataSize;
  } else {
    Variable->DataSize = (UINT32) DataSize;
  }
}

/**

  This code gets the pointer to the variable name.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

  @retval    Pointer to Variable Name which is Unicode encoding.

**/
CHAR16 *
GetVariableNamePtrHob (
  IN  VARIABLE_HEADER   *Variable,
  IN  BOOLEAN            IsAuthenticated
  )
{
  return (CHAR16 *) ((UINTN) Variable + GetVariableHeaderSizeHob (IsAuthenticated));
}

/**

  This code gets the pointer to the variable data.

  @param[in]  Variable        Pointer to the Variable Header.
  @param[in]  IsAuthenticated  Indicates if the variable is an authenticated variable.

  @retval     Pointer to Variable Data.

**/
UINT8 *
GetVariableDataPtrHob (
  IN  VARIABLE_HEADER   *Variable,
  IN  BOOLEAN           IsAuthenticated
  )
{
  UINTN Value;

  //
  // Be careful about pad size for alignment.
  //
  Value =  (UINTN) GetVariableNamePtrHob (Variable, IsAuthenticated);
  DEBUG ((DEBUG_INFO, "  Value(1) = 0x%x\n", Value));
  Value += NameSizeOfVariableHob (Variable, IsAuthenticated);
  DEBUG ((DEBUG_INFO, "  Value(2) = 0x%x\n", Value));
  Value += GET_PAD_SIZE (NameSizeOfVariableHob (Variable, IsAuthenticated));
  DEBUG ((DEBUG_INFO, "  Value(3) = 0x%x\n", Value));

  return (UINT8 *) Value;
}

/**

  This code gets the pointer to the next variable header.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

  @retval    Pointer to next variable header.

**/
VARIABLE_HEADER *
GetNextVariablePtrHob (
  IN  VARIABLE_HEADER   *Variable,
  IN  BOOLEAN           IsAuthenticated
  )
{
  UINTN Value;

  Value =  (UINTN) GetVariableDataPtrHob (Variable, IsAuthenticated);
  Value += DataSizeOfVariableHob (Variable, IsAuthenticated);
  Value += GET_PAD_SIZE (DataSizeOfVariableHob (Variable, IsAuthenticated));

  //
  // Be careful about pad size for alignment.
  //
  return (VARIABLE_HEADER *) HEADER_ALIGN (Value);
}

/**
  This code gets the pointer to the variable guid.

  @param[in] Variable         Pointer to the Variable Header.
  @param[in] IsAuthenticated  Indicates if the variable is an authenticated variable.

  @retval    A EFI_GUID* pointer to Vendor Guid.

**/
EFI_GUID *
GetVendorGuidPtrHob (
  IN VARIABLE_HEADER    *Variable,
  IN BOOLEAN            IsAuthenticated
  )
{
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;

  AuthVariable = (AUTHENTICATED_VARIABLE_HEADER *) Variable;
  if (IsAuthenticated) {
    return &AuthVariable->VendorGuid;
  } else {
    return &Variable->VendorGuid;
  }
}

/**
  Performs basic initialization of an EDKII variable store header.

  @param[in]  VariableCacheStore        A pointer to a variable store header.

  @retval EFI_SUCCESS                   The store header was initialized successfully.
  @retval EFI_INVALID_PARAMETER         The VariableCacheStore parameter is invalid.

**/
EFI_STATUS
EFIAPI
InitializeVariableCacheStore (
  IN VARIABLE_STORE_HEADER  *VariableCacheStore
)
{
  if (VariableCacheStore == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the variable store
  //
  CopyMem (&VariableCacheStore->Signature, &gEfiAuthenticatedVariableGuid, sizeof (EFI_GUID));

  VariableCacheStore->Format = VARIABLE_STORE_FORMATTED;
  VariableCacheStore->State  = VARIABLE_STORE_HEALTHY;
  VariableCacheStore->Size   = 0;

  return EFI_SUCCESS;
}

/**
  Copies variables from a custom UEFI variable store format to the format expected by the EDKII
  variable driver.

  @param[in]  VariableStoreHeader       A pointer to the buffer for the EDKII style store (the destination)
  @param[in]  VariableNvmStoreInfo      A pointer to a structure that describes the custom formatted store (the source)

  @retval EFI_SUCCESS                   The data was successfully copied.
  @retval Others                        An error occurred copying the variable data.

**/
EFI_STATUS
EFIAPI
CopyNvmVariablesToCacheStore (
  IN  VARIABLE_STORE_HEADER    *VariableStoreHeader,
  IN  VARIABLE_NVM_STORE_INFO  *VariableNvmStoreInfo
)
{
  VARIABLE_HEADER      *VariableHeader    = NULL;
  VARIABLE_NVM_HEADER  *VariableNvmHeader = NULL;

  CHAR16               *VariableNamePtr   = NULL;
  UINT8                *VariableDataPtr   = NULL;
  EFI_GUID             *VendorGuidPtr     = NULL;

  VariableHeader    = (VARIABLE_HEADER *) HEADER_ALIGN (VariableStoreHeader + 1);
  VariableNvmHeader = GetStartPointer (VariableNvmStoreInfo->VariableStoreHeader);

  DEBUG ((DEBUG_INFO, "Copying variables from the pre-memory location to the cache HOB...\n"));
  DEBUG ((
    DEBUG_INFO,
    " Starting pointers: EDKII variable header at %p. Pre-memory variable header at %p.\n",
    VariableHeader,
    VariableNvmHeader
    ));

  while (IsValidVariableHeader (VariableNvmHeader, GetEndPointer (VariableNvmStoreInfo->VariableStoreHeader))) {
    VariableHeader->StartId    = VARIABLE_DATA;
    VariableHeader->State      = VariableNvmHeader->State;
    VariableHeader->Attributes = VariableNvmHeader->Attributes;

    SetNameSizeOfVariableHob (VariableHeader, VariableNvmHeader->NameSize, VariableNvmStoreInfo->AuthFlag);
    SetDataSizeOfVariableHob (VariableHeader, VariableNvmHeader->DataSize, VariableNvmStoreInfo->AuthFlag);

    VariableNamePtr = GetVariableNamePtrHob (VariableHeader, VariableNvmStoreInfo->AuthFlag);
    VariableDataPtr = GetVariableDataPtrHob (VariableHeader, VariableNvmStoreInfo->AuthFlag);

    DEBUG ((DEBUG_INFO, "  EDKII store variable: NamePtr = %p. DataPtr = %p.\n", VariableNamePtr, VariableDataPtr));

    DEBUG ((
      DEBUG_INFO,
      "  NVM store variable: DataPtr = 0x%08x.\n",
      ((UINTN) VariableNvmStoreInfo->VariableStoreHeader + GetVariableDataPtr (VariableNvmHeader, VariableNvmStoreInfo))
      ));
    CopyMem (
      VariableDataPtr,
      (UINT8 *) ((UINTN) VariableNvmStoreInfo->VariableStoreHeader + GetVariableDataPtr (VariableNvmHeader, VariableNvmStoreInfo)),
      VariableNvmHeader->DataSize
      );

    //
    // Copy the variable GUID and name
    //
    VendorGuidPtr = GetVendorGuidPtrHob (VariableHeader, VariableNvmStoreInfo->AuthFlag);

    CopyMem (VendorGuidPtr, &VariableNvmHeader->VendorGuid, sizeof (EFI_GUID));
    CopyMem (VariableNamePtr, GetVariableNamePtr (VariableNvmHeader, VariableNvmStoreInfo->AuthFlag), VariableNvmHeader->NameSize);

    DEBUG ((DEBUG_INFO, "  Variable name = %s and variable GUID = %g.\n", VariableNamePtr, VendorGuidPtr));

    //
    // Output debug data for the variable just copied
    //
    DEBUG ((
      DEBUG_INFO,
      "  Variable name size = %d bytes.\n",
      NameSizeOfVariableHob (VariableHeader, VariableNvmStoreInfo->AuthFlag)
      ));
    DEBUG ((
      DEBUG_INFO,
      "  Variable data size = %d bytes.\n",
      DataSizeOfVariableHob (VariableHeader, VariableNvmStoreInfo->AuthFlag)
      ));

    VariableHeader    = GetNextVariablePtrHob (VariableHeader, VariableNvmStoreInfo->AuthFlag);
    VariableNvmHeader = GetNextVariablePtr (VariableNvmStoreInfo, VariableNvmHeader);
  }

  ASSERT ((UINTN) VariableHeader > (UINTN) VariableStoreHeader);
  VariableStoreHeader->Size = (UINT32) ((UINTN) VariableHeader - (UINTN) VariableStoreHeader);

  DEBUG ((DEBUG_INFO, " Final EDKII cache HOB variable store size created = %d bytes.\n", VariableStoreHeader->Size));
  return EFI_SUCCESS;
}

/**
  Creates the PEI variable cache HOB.

  @param[in]  VariableNvmStore          A pointer to a UEFI variable store.

  @retval EFI_SUCCESS                   The variable cache HOB was successfully produced.
  @retval Others                        An error occurred creating the variable cache HOB.

**/
EFI_STATUS
EFIAPI
CreateVariableCacheHob (
  IN    VARIABLE_NVM_STORE_HEADER  *VariableNvmStore
  )
{
  EFI_STATUS                       Status;

  VARIABLE_STORE_HEADER            *VariableStoreHeader;
  VARIABLE_NVM_STORE_INFO          VariableNvmStoreInfo;
  UINT32                           VariableStoreSize;

  if (GetFirstGuidHob (&gPeiVariableCacheHobGuid) != NULL) {
    // Variable cache HOB already created
    return EFI_SUCCESS;
  }

  //
  // Assume that the data (not the structure) is at the pointer
  //
  // Note: In the future the full structure will be passed and BIOS will parse the structure to find the UEFI
  //       variable data.
  //
  VariableNvmStoreInfo.VariableStoreHeader = VariableNvmStore;
  Status = IsAuthenticatedVariableStore (VariableNvmStoreInfo.VariableStoreHeader, &VariableNvmStoreInfo.AuthFlag);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  VariableStoreSize = VariableNvmStoreInfo.VariableStoreHeader->Size;

  DEBUG ((
    DEBUG_INFO,
    "The secure pre-memory data UEFI variable store %a authenticated.\n",
    (VariableNvmStoreInfo.AuthFlag) ? "is" : "is not"
    ));
  DEBUG ((
    DEBUG_INFO,
    "The secure pre-memory data UEFI variable store size = %d bytes.\n",
    VariableStoreSize
    ));

  if (SECURE_PRE_MEMORY_DATA_MAX_TOTAL_LENGTH < VariableStoreSize) {
    DEBUG ((
      DEBUG_ERROR,
      "The SPMD UEFI variable store size exceeds the maximum size allowed. Maximum = 0x%x.\n",
      SECURE_PRE_MEMORY_DATA_MAX_TOTAL_LENGTH
      ));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the variable cache HOB
  //
  VariableStoreHeader = BuildGuidHob (&gPeiVariableCacheHobGuid, VariableStoreSize);
  if (VariableStoreHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ZeroMem (VariableStoreHeader, VariableStoreSize);

  DEBUG ((DEBUG_INFO, "Variable cache HOB allocated at 0x%08x.\n", VariableStoreHeader));

  InitializeVariableCacheStore (VariableStoreHeader);
  Status = CopyNvmVariablesToCacheStore (VariableStoreHeader, &VariableNvmStoreInfo);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "Variable cache created successfully\n"));

  return EFI_SUCCESS;
}
