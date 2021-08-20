/** @file
  Variable NVM Storage Helper library

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

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/VariableNvmStorageLib.h>

/**
  Returns a pointer of type VARIABLE_NVM_STORE_HEADER to a buffer containing
  the header of an empty variable store.

  @param[out] VarStoreHeader  Pointer to the Variable Store Header.

  @retval     EFI_SUCCESS     The variable store was created successfully.
  @retval     Others          An error occurred creating the variable store.

**/
EFI_STATUS
EFIAPI
GetEmptyVariableStore (
  OUT VARIABLE_NVM_STORE_HEADER  *VarStoreHeader
  )
{
  if (VarStoreHeader == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem (&VarStoreHeader->Signature, &gEfiAuthenticatedVariableGuid, sizeof (EFI_GUID));

  VarStoreHeader->Size     = sizeof (VARIABLE_NVM_STORE_HEADER);
  VarStoreHeader->Revision = VARIABLE_NVM_STORE_REVISION_1_0;
  VarStoreHeader->Format   = VARIABLE_STORE_FORMATTED;
  VarStoreHeader->State    = VARIABLE_STORE_HEALTHY;

  VarStoreHeader->VariableHeaderTotalEntries = 0;
  VarStoreHeader->VariableHeaderTotalLength  = 0;
  VarStoreHeader->VariableDataTotalLength    = 0;
  VarStoreHeader->VariableHeaderOffset       = VarStoreHeader->Size + 1;

  VarStoreHeader->VariableHeaderOffset += NVM_GET_PAD_SIZE (VarStoreHeader->VariableHeaderOffset);

  return EFI_SUCCESS;
}

/**
  Gets the pointer to the first variable header in the given variable header region.

  @param[in] VarStoreHeader  Pointer to the Variable Store Header.

  @retval    Pointer to the first variable header

**/
VARIABLE_NVM_HEADER *
EFIAPI
GetStartPointer (
  IN  CONST VARIABLE_NVM_STORE_HEADER  *VarStoreHeader
  )
{
  //
  // The end of the variable store header is the first variable header
  //
  return (VARIABLE_NVM_HEADER *) NVM_HEADER_ALIGN (VarStoreHeader + 1);
}

/**
  This code gets the pointer to the last variable header in the variable header region.

  @param[in]  VarStoreHeader  Pointer to the Variable Store Header.

  @retval     VARIABLE_NVM_HEADER* pointer to last unavailable Variable Header.

**/
VARIABLE_NVM_HEADER *
EFIAPI
GetEndPointer (
  IN  CONST VARIABLE_NVM_STORE_HEADER  *VarStoreHeader
  )
{
  //
  // The end of variable store
  //
  return (VARIABLE_NVM_HEADER *)
    NVM_HEADER_ALIGN (
      (UINTN) VarStoreHeader +
      sizeof (VARIABLE_NVM_STORE_HEADER) +
      VarStoreHeader->VariableHeaderTotalLength
      );
}

/**
  This code checks if the variable header is valid or not.

  @param[in]  Variable          Pointer to the Variable Header.
  @param[in]  VariableStoreEnd  Pointer to the end of the Variable Store

  @retval     TRUE              Variable header is valid.
  @retval     FALSE             Variable header is not valid.

**/
BOOLEAN
EFIAPI
IsValidVariableHeader (
  IN  CONST VARIABLE_NVM_HEADER  *Variable,
  IN  CONST VARIABLE_NVM_HEADER  *VariableStoreEnd
  )
{
  if ((Variable == NULL) || (Variable >= VariableStoreEnd) || (Variable->StartId != VARIABLE_DATA)) {
    return FALSE;
  }

  return TRUE;
}

/**
  Returns whether the variable store contains authenticated variables.

  @param[in]  VarStoreHeader        Pointer to the Variable Store Header.
  @param[out] IsAuthenticatedStore  Indicates whether this store is authenticated.

  @retval     EFI_SUCCESS           The authenticated status of the store was successfully determined.
  @retval     EFI_INVALID_PARAMETER An invalid parameter was passed to the function.

**/
EFI_STATUS
EFIAPI
IsAuthenticatedVariableStore (
  IN  CONST VARIABLE_NVM_STORE_HEADER  *VarStoreHeader,
  OUT       BOOLEAN                    *IsAuthenticatedStore
  )
{
  if (VarStoreHeader == NULL || IsAuthenticatedStore == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *IsAuthenticatedStore = (BOOLEAN)(CompareGuid (&VarStoreHeader->Signature, &gEfiAuthenticatedVariableGuid));

  return EFI_SUCCESS;
}

/**
  This code gets the size of the variable header.

  @param[in] AuthFlag   Authenticated variable flag.

  @retval    Size of variable header in bytes in type UINTN.

**/
UINTN
EFIAPI
GetVariableHeaderSize (
  IN  BOOLEAN       AuthFlag
  )
{
  UINTN Value;

  if (AuthFlag) {
    Value = sizeof (AUTHENTICATED_VARIABLE_NVM_HEADER);
  } else {
    Value = sizeof (VARIABLE_NVM_HEADER);
  }

  return Value;
}

/**
  This code gets the size of the name of the variable.

  @param[in]  Variable  Pointer to the Variable Header.
  @param[in]  AuthFlag  Authenticated variable flag.

  @retval     Size of variable in bytes in type UINTN.

**/
UINTN
EFIAPI
NameSizeOfVariable (
  IN  CONST VARIABLE_NVM_HEADER  *Variable,
  IN        BOOLEAN              AuthFlag
  )
{
  AUTHENTICATED_VARIABLE_NVM_HEADER *AuthVariable;

  if (AuthFlag) {
    AuthVariable = (AUTHENTICATED_VARIABLE_NVM_HEADER *) Variable;

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
  This code gets the size of the variable data.

  @param[in]  Variable  Pointer to the Variable Header.
  @param[in]  AuthFlag  Authenticated variable flag.

  @retval     Size of variable in bytes in type UINTN.

**/
UINTN
EFIAPI
DataSizeOfVariable (
  IN  CONST VARIABLE_NVM_HEADER  *Variable,
  IN        BOOLEAN              AuthFlag
  )
{
  AUTHENTICATED_VARIABLE_NVM_HEADER *AuthVariable;

  if (AuthFlag) {
    AuthVariable = (AUTHENTICATED_VARIABLE_NVM_HEADER *) Variable;

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
  This code gets the pointer to the variable name.

  @param[in]   Variable  Pointer to the Variable Header.
  @param[in]   AuthFlag  Authenticated variable flag.

  @retval      A CHAR16* pointer to Variable Name.

**/
CHAR16 *
EFIAPI
GetVariableNamePtr (
  IN  CONST VARIABLE_NVM_HEADER  *Variable,
  IN        BOOLEAN              AuthFlag
  )
{
  return (CHAR16 *) ((UINTN) Variable + GetVariableHeaderSize (AuthFlag));
}

/**
  This code gets the pointer to the variable GUID.

  @param[in] Variable   Pointer to the Variable Header.
  @param[in] AuthFlag   Authenticated variable flag.

  @retval    A EFI_GUID* pointer to Vendor Guid.

**/
CONST EFI_GUID *
EFIAPI
GetVendorGuidPtr (
  IN  CONST VARIABLE_NVM_HEADER  *Variable,
  IN        BOOLEAN              AuthFlag
  )
{
  AUTHENTICATED_VARIABLE_NVM_HEADER *AuthVariable;

  if (AuthFlag) {
    AuthVariable = (AUTHENTICATED_VARIABLE_NVM_HEADER *) Variable;

    return &AuthVariable->VendorGuid;
  } else {
    return &Variable->VendorGuid;
  }
}

/**
  This code gets the pointer to the variable data.

  This is an "offset" that is interpreted as needed based on the caller's requirements.

  @param[in]   Variable         Pointer to the Variable Header.
  @param[in]   StoreInfo        Pointer to a Variable Store Info structure for this variable.

  @retval       A UINT32 value representing the offset to the variable data.

**/
UINT32
EFIAPI
GetVariableDataPtr (
  IN  CONST VARIABLE_NVM_HEADER     *Variable,
  IN        VARIABLE_NVM_STORE_INFO *StoreInfo
  )
{
  if (StoreInfo->AuthFlag) {
    return ((AUTHENTICATED_VARIABLE_NVM_HEADER *) Variable)->DataOffset;
  } else {
    return Variable->DataOffset;
  }
}

/**
  This code gets the pointer to the next variable header.

  @param[in]  StoreInfo         Pointer to variable store info structure.
  @param[in]  VariableHeader    Pointer to the Variable Header.

  @return     A VARIABLE_NVM_HEADER* pointer to next variable header.

**/
VARIABLE_NVM_HEADER *
EFIAPI
GetNextVariablePtr (
  IN  CONST VARIABLE_NVM_STORE_INFO  *StoreInfo,
  IN  CONST VARIABLE_NVM_HEADER      *VariableHeader
  )
{
  UINTN Value;

  if (!IsValidVariableHeader (VariableHeader, GetEndPointer(StoreInfo->VariableStoreHeader))) {
    DEBUG ((
      EFI_D_ERROR,
      "Invalid header hit in GetNextVariablePtr() header address = 0x%x, store end = 0x%x\n",
      VariableHeader,
      GetEndPointer(StoreInfo->VariableStoreHeader)
      ));
    return NULL;
  }

  Value =  (UINTN) GetVariableNamePtr (VariableHeader, StoreInfo->AuthFlag);
  Value += NameSizeOfVariable (VariableHeader, StoreInfo->AuthFlag);
  Value += NVM_GET_PAD_SIZE (NameSizeOfVariable (VariableHeader, StoreInfo->AuthFlag));

  return (VARIABLE_NVM_HEADER *) NVM_HEADER_ALIGN (Value);
}

/**
  Get variable store status.

  @param[in]  VarStoreHeader  Pointer to the Variable Store Header.

  @retval     EfiRaw          Variable store is raw
  @retval     EfiValid        Variable store is valid
  @retval     EfiInvalid      Variable store is invalid

**/
VARIABLE_STORE_STATUS
EFIAPI
GetVariableStoreStatus (
  IN  CONST VARIABLE_NVM_STORE_HEADER  *VarStoreHeader
  )
{
  if (
    (CompareGuid (&VarStoreHeader->Signature, &gEfiAuthenticatedVariableGuid) ||
    CompareGuid (&VarStoreHeader->Signature, &gEfiVariableGuid)) &&
    VarStoreHeader->Format == VARIABLE_STORE_FORMATTED &&
    VarStoreHeader->State  == VARIABLE_STORE_HEALTHY
    ) {
    return EfiValid;
  }

  if (((UINT32 *)(&VarStoreHeader->Signature))[0] == 0 &&
      ((UINT32 *)(&VarStoreHeader->Signature))[1] == 0 &&
      ((UINT32 *)(&VarStoreHeader->Signature))[2] == 0 &&
      ((UINT32 *)(&VarStoreHeader->Signature))[3] == 0 &&
      VarStoreHeader->Size   == 0 &&
      VarStoreHeader->Format == 0 &&
      VarStoreHeader->State  == 0
      ) {
    return EfiRaw;
  } else {
    return EfiInvalid;
  }
}

/**
  Compare two variable names.

  @param[in] StoreInfo      Pointer to variable store info structure.
  @param[in] Name1          Pointer to one variable name.
  @param[in] Name2          Pointer to another variable name.
  @param[in] NameSize       Variable name size.

  @retval    TRUE           Name1 and Name2 are identical.
  @retval    FALSE          Name1 and Name2 are not identical.

**/
BOOLEAN
EFIAPI
CompareVariableName (
  IN  CONST VARIABLE_NVM_STORE_INFO  *StoreInfo,
  IN  CONST CHAR16                   *Name1,
  IN  CONST CHAR16                   *Name2,
  IN        UINTN                    NameSize
  )
{

  //
  // Both Name1 and Name2 are consecutive.
  //
  if (CompareMem ((UINT8 *) Name1, (UINT8 *) Name2, NameSize) == 0) {
    return TRUE;
  }
  return FALSE;
}

/**
  This function compares a variable with the variable entry in the database.

  @param[in]  StoreInfo      Pointer to variable store info structure.
  @param[in]  Variable       Pointer to the variable in our database
  @param[in]  VariableHeader Pointer to the Variable Header that has consecutive content.
  @param[in]  VariableName   Name of the variable to compare to 'Variable'
  @param[in]  VendorGuid     GUID of the variable to compare to 'Variable'
  @param[out] PtrTrack       Variable Track Pointer structure that contains Variable Information.

  @retval     EFI_SUCCESS    Found match variable
  @retval     EFI_NOT_FOUND  Variable not found

**/
EFI_STATUS
EFIAPI
CompareWithValidVariable (
  IN  CONST VARIABLE_NVM_STORE_INFO     *StoreInfo,
  IN        VARIABLE_NVM_HEADER         *Variable,
  IN  CONST VARIABLE_NVM_HEADER         *VariableHeader,
  IN  CONST CHAR16                      *VariableName,
  IN  CONST EFI_GUID                    *VendorGuid,
  OUT       VARIABLE_NVM_POINTER_TRACK  *PtrTrack
  )
{
  VOID            *Point;
  CONST EFI_GUID  *TempVendorGuid;

  TempVendorGuid = GetVendorGuidPtr (VariableHeader, StoreInfo->AuthFlag);

  if (VariableName[0] == 0) {
    PtrTrack->CurrPtr = Variable;
    return EFI_SUCCESS;
  } else {
    //
    // Don't use CompareGuid function here for performance reasons.
    // Instead we compare the GUID a UINT32 at a time and branch
    // on the first failed comparison.
    //
    if ((((INT32 *) VendorGuid)[0] == ((INT32 *) TempVendorGuid)[0]) &&
        (((INT32 *) VendorGuid)[1] == ((INT32 *) TempVendorGuid)[1]) &&
        (((INT32 *) VendorGuid)[2] == ((INT32 *) TempVendorGuid)[2]) &&
        (((INT32 *) VendorGuid)[3] == ((INT32 *) TempVendorGuid)[3])
        ) {
      ASSERT (NameSizeOfVariable (VariableHeader, StoreInfo->AuthFlag) != 0);
      Point = (VOID *) GetVariableNamePtr (Variable, StoreInfo->AuthFlag);
      if (CompareVariableName (StoreInfo, VariableName, Point, NameSizeOfVariable (VariableHeader, StoreInfo->AuthFlag))) {
        PtrTrack->CurrPtr = Variable;
        return EFI_SUCCESS;
      }
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Validate the provided variable header.

  @param[in]  StoreInfo      Pointer to variable store info structure.
  @param[in]  Variable       Pointer to the Variable Header.
  @param[out] VariableHeader Pointer to Pointer to the Variable Header that has consecutive content.

  @retval     TRUE           Variable header is valid.
  @retval     FALSE          Variable header is not valid.

**/
BOOLEAN
EFIAPI
GetVariableHeader (
  IN  CONST VARIABLE_NVM_STORE_INFO   *StoreInfo,
  IN        VARIABLE_NVM_HEADER       *Variable,
  OUT       VARIABLE_NVM_HEADER       **VariableHeader
  )
{
  VARIABLE_NVM_HEADER   *EndVariablePtr;

  if (Variable == NULL) {
    return FALSE;
  }

  *VariableHeader = Variable;
  EndVariablePtr = GetEndPointer (StoreInfo->VariableStoreHeader);

  if (Variable >= EndVariablePtr) {
    //
    // Reached the end of the variable store.
    //
    return FALSE;
  }

  return IsValidVariableHeader (*VariableHeader, EndVariablePtr);
}

/**
  Compares two EFI_TIME data structures.

  @param[in]   FirstTime   A pointer to the first EFI_TIME data.
  @param[in]   SecondTime  A pointer to the second EFI_TIME data.

  @retval      TRUE        The FirstTime is not later than the SecondTime.
  @retval      FALSE       The FirstTime is later than the SecondTime.

**/
BOOLEAN
EFIAPI
VariableNvmCompareTimeStamp (
  IN  CONST EFI_TIME  *FirstTime,
  IN  CONST EFI_TIME  *SecondTime
  )
{
  if (FirstTime->Year != SecondTime->Year) {
    return (BOOLEAN) (FirstTime->Year < SecondTime->Year);
  } else if (FirstTime->Month != SecondTime->Month) {
    return (BOOLEAN) (FirstTime->Month < SecondTime->Month);
  } else if (FirstTime->Day != SecondTime->Day) {
    return (BOOLEAN) (FirstTime->Day < SecondTime->Day);
  } else if (FirstTime->Hour != SecondTime->Hour) {
    return (BOOLEAN) (FirstTime->Hour < SecondTime->Hour);
  } else if (FirstTime->Minute != SecondTime->Minute) {
    return (BOOLEAN) (FirstTime->Minute < SecondTime->Minute);
  }

  return (BOOLEAN) (FirstTime->Second <= SecondTime->Second);
}