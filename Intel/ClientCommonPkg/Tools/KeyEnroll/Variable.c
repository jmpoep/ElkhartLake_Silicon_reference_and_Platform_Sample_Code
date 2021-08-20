//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Read and edit the EFI variable.

Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "KeyEnroll.h"
#include "VariableCommon.h"
#include "Variable.h"
#include <time.h>

EFI_GUID  gEfiVariableGuid     = EFI_VARIABLE_GUID;
EFI_GUID  gEfiAuthenticatedVariableGuid     = EFI_AUTHENTICATED_VARIABLE_GUID;
EFI_GUID  gEfiAuthenticatedVariableBasedTimeGuid     = EFI_AUTHENTICATED_VARIABLE_BASED_TIME_GUID;
/**

  Gets the pointer to the first variable header in given variable store area.

  @param VarStoreHeader  Pointer to the Variable Store Header.

  @return Pointer to the first variable header.

**/
VARIABLE_HEADER *
GetStartPointer (
  IN VARIABLE_STORE_HEADER       *VarStoreHeader
  )
{
  //
  // The end of variable store.
  //
  return (VARIABLE_HEADER *) HEADER_ALIGN (VarStoreHeader + 1);
}

/**

  Gets the pointer to the end of the variable storage area.

  This function gets pointer to the end of the variable storage
  area, according to the input variable store header.

  @param VarStoreHeader  Pointer to the Variable Store Header.

  @return Pointer to the end of the variable storage area.

**/
VARIABLE_HEADER *
GetEndPointer (
  IN VARIABLE_STORE_HEADER       *VarStoreHeader
  )
{
  //
  // The end of variable store
  //
  return (VARIABLE_HEADER *) HEADER_ALIGN ((UINTN) VarStoreHeader + VarStoreHeader->Size);
}


/**

  This code checks if variable header is valid or not.

  @param Variable        Pointer to the Variable Header.

  @retval TRUE           Variable header is valid.
  @retval FALSE          Variable header is not valid.

**/
BOOLEAN
IsValidVariableHeader (
  IN  VARIABLE_HEADER   *Variable
  )
{
  if ((Variable == NULL) || (Variable->Common.StartId != VARIABLE_DATA)) {
    return FALSE;
  }

  return TRUE;
}

/**

  This code gets the size of name of variable.

  @param Variable        Pointer to the Variable Header.

  @return UINTN          Size of variable in bytes.

**/
UINTN
NameSizeOfVariable (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    if ((Variable->Normal.State    == (UINT8) (-1))  ||
        (Variable->Normal.DataSize == (UINT32) (-1)) ||
        (Variable->Normal.NameSize == (UINT32) (-1)) ||
        (Variable->Normal.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->Normal.NameSize;
  case VariableTypeCountBasedAuth:
    if ((Variable->CountBasedAuth.State    == (UINT8) (-1))  ||
        (Variable->CountBasedAuth.DataSize == (UINT32) (-1)) ||
        (Variable->CountBasedAuth.NameSize == (UINT32) (-1)) ||
        (Variable->CountBasedAuth.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->CountBasedAuth.NameSize;
  case VariableTypeTimeBasedAuth:
    if ((Variable->TimeBasedAuth.State    == (UINT8) (-1))  ||
        (Variable->TimeBasedAuth.DataSize == (UINT32) (-1)) ||
        (Variable->TimeBasedAuth.NameSize == (UINT32) (-1)) ||
        (Variable->TimeBasedAuth.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->TimeBasedAuth.NameSize;
  default:
    return 0;
  }
}

/**

  This code gets the size of variable data.

  @param Variable        Pointer to the Variable Header.

  @return Size of variable in bytes.

**/
UINTN
DataSizeOfVariable (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    if ((Variable->Normal.State    == (UINT8)  (-1)) ||
        (Variable->Normal.DataSize == (UINT32) (-1)) ||
        (Variable->Normal.NameSize == (UINT32) (-1)) ||
        (Variable->Normal.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->Normal.DataSize;
  case VariableTypeCountBasedAuth:
    if ((Variable->CountBasedAuth.State    == (UINT8)  (-1)) ||
        (Variable->CountBasedAuth.DataSize == (UINT32) (-1)) ||
        (Variable->CountBasedAuth.NameSize == (UINT32) (-1)) ||
        (Variable->CountBasedAuth.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->CountBasedAuth.DataSize;
  case VariableTypeTimeBasedAuth:
    if ((Variable->TimeBasedAuth.State    == (UINT8)  (-1)) ||
        (Variable->TimeBasedAuth.DataSize == (UINT32) (-1)) ||
        (Variable->TimeBasedAuth.NameSize == (UINT32) (-1)) ||
        (Variable->TimeBasedAuth.Attributes == (UINT32) (-1))
        ) {
      return 0;
    }
    return (UINTN) Variable->TimeBasedAuth.DataSize;
  default:
    return 0;
  }
}

/**

  This code gets the pointer to the variable name.

  @param Variable        Pointer to the Variable Header.

  @return Pointer to Variable Name which is Unicode encoding.

**/
CHAR16 *
GetVariableNamePtr (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    return (CHAR16 *) ((UINTN)Variable + sizeof(VARIABLE_HEADER_NORMAL));
  case VariableTypeCountBasedAuth:
    return (CHAR16 *) ((UINTN)Variable + sizeof(VARIABLE_HEADER_COUNT_BASED_AUTH));
  case VariableTypeTimeBasedAuth:
    return (CHAR16 *) ((UINTN)Variable + sizeof(VARIABLE_HEADER_TIME_BASED_AUTH));
  default:
    return NULL;
  }
}

/**

  This code gets the pointer to the variable data.

  @param Variable        Pointer to the Variable Header.

  @return Pointer to Variable Data.

**/
UINT8 *
GetVariableDataPtr (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  UINTN Value;

  //
  // Be careful about pad size for alignment.
  //
  Value =  (UINTN) GetVariableNamePtr (Variable, VariableType);
  Value += NameSizeOfVariable (Variable, VariableType);
  Value += GET_PAD_SIZE (NameSizeOfVariable (Variable, VariableType));

  return (UINT8 *) Value;
}

/**

  This code gets the pointer to the next variable header.

  @param Variable        Pointer to the Variable Header.

  @return Pointer to next variable header.

**/
VARIABLE_HEADER *
GetNextVariablePtr (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  UINTN Value;

  if (!IsValidVariableHeader (Variable)) {
    return NULL;
  }

  Value =  (UINTN) GetVariableDataPtr (Variable, VariableType);
  Value += DataSizeOfVariable (Variable, VariableType);
  Value += GET_PAD_SIZE (DataSizeOfVariable (Variable, VariableType));

  //
  // Be careful about pad size for alignment.
  //
  return (VARIABLE_HEADER *) HEADER_ALIGN (Value);
}

/**

  This code gets the pointer to the variable GUID.

  @param Variable        Pointer to the Variable Header.

  @return Pointer to variable GUID.

**/
EFI_GUID *
GetVariableGuidPtr (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    return &Variable->Normal.VendorGuid;
  case VariableTypeCountBasedAuth:
    return &Variable->CountBasedAuth.VendorGuid;
  case VariableTypeTimeBasedAuth:
    return &Variable->TimeBasedAuth.VendorGuid;
  default:
    return NULL;
  }
}

/**

  This code gets the Attributes of variable data.

  @param Variable        Pointer to the Variable Header.

  @return Attributes of variable.

**/
UINT32
AttributesOfVariable (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType
  )
{
  return Variable->Normal.Attributes;
}

VOID
SetVariableAttributes (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  UINT32            Attributes
  )
{
  Variable->Normal.Attributes = Attributes;
}

VOID
SetVariableNameSize (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  UINT32            NameSize
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    Variable->Normal.NameSize = NameSize;
    break;
  case VariableTypeCountBasedAuth:
    Variable->CountBasedAuth.NameSize = NameSize;
    break;
  case VariableTypeTimeBasedAuth:
    Variable->TimeBasedAuth.NameSize = NameSize;
    break;
  default:
    break;
  }
}

VOID
SetVariableDataSize (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  UINT32            DataSize
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    Variable->Normal.DataSize = DataSize;
    break;
  case VariableTypeCountBasedAuth:
    Variable->CountBasedAuth.DataSize = DataSize;
    break;
  case VariableTypeTimeBasedAuth:
    Variable->TimeBasedAuth.DataSize = DataSize;
    break;
  default:
    break;
  }
}

VOID
SetVariableGuid (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  EFI_GUID          *Guid
  )
{
  EFI_GUID         *VendorGuid;

  VendorGuid = GetVariableGuidPtr (Variable, VariableType);
  if (VendorGuid != NULL) {
    memcpy (VendorGuid, Guid, sizeof (EFI_GUID));
  }
}

VOID
SetVariableName (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  CHAR16            *Name,
  IN  UINTN             NameSize
  )
{
  CHAR16           *VariableName;

  VariableName = GetVariableNamePtr (Variable, VariableType);
  if (VariableName != NULL) {
    memcpy (VariableName, Name, NameSize);
  }
}

VOID
SetVariableData (
  IN  VARIABLE_HEADER   *Variable,
  IN  VARIABLE_TYPE     VariableType,
  IN  VOID              *Buffer,
  IN  UINTN             BuffferSize
  )
{
  memcpy (GetVariableDataPtr (Variable, VariableType), Buffer, BuffferSize);
}

UINTN
SizeOfVariableHeader (
  IN  VARIABLE_TYPE     VariableType
  )
{
  switch (VariableType) {
  case VariableTypeNormal:
    return sizeof(VARIABLE_HEADER_NORMAL);
  case VariableTypeCountBasedAuth:
    return sizeof(VARIABLE_HEADER_COUNT_BASED_AUTH);
  case VariableTypeTimeBasedAuth:
    return sizeof(VARIABLE_HEADER_TIME_BASED_AUTH);
  default:
    return 0;
  }
}

/**
  Search and get a free space in the EFI variable zone

  @param VariableStoreHeader       The start of a EFI variable zone.
  @param VarListSize               The size of a variables needs to be allocated.
  @param FreeBeginVar              The dual pointer to the free NV space.

  @retval EFI_SUCCESS              Return the beginning of a free variable space.
  @retval RETURN_BUFFER_TOO_SMALL  Failed.
**/
EFI_STATUS
GetVariableVar (
  IN      VARIABLE_STORE_HEADER  *VariableStoreHeader,
  IN      VARIABLE_TYPE          VariableType,
  IN      UINT32                 VarListSize,
  IN OUT  CHAR8                  **FreeBeginVar
)
{
  BOOLEAN          Flag;
  VARIABLE_HEADER  *Variable;
  VARIABLE_HEADER  *EndOfVariable;
  CHAR8            *BeginVar;

  BeginVar      = NULL;
  Flag          = FALSE;
  Variable      = NULL;
  EndOfVariable = NULL;
  *FreeBeginVar = NULL;

  if (VariableStoreHeader == NULL) {
    *FreeBeginVar = NULL;
    return RETURN_INVALID_PARAMETER;
  }
  Variable      = GetStartPointer (VariableStoreHeader);
  EndOfVariable = GetEndPointer(VariableStoreHeader);
  //
  //Search the beginning of free NV
  //
  while (Variable != EndOfVariable) {
    BeginVar = (CHAR8 *)Variable;
    Variable = GetNextVariablePtr (Variable, VariableType);
    if (Variable == NULL) {
      Flag = TRUE;
      break;
    }
  }
  //
  // Check whether the free space is more than what we want
  //
  if ((CHAR8 *)BeginVar + VarListSize > (CHAR8 *)EndOfVariable) {
    return RETURN_BUFFER_TOO_SMALL;
  }
  //
  // If not find the available space, return NULL
  //
  if (!Flag) {
    return RETURN_BUFFER_TOO_SMALL;
  }
  *FreeBeginVar = BeginVar;

  return EFI_SUCCESS;
}

/**
  Search whether the variable in VarList has existed in current NV.

  Parse the FFS or Fd image, and find the valid variable pointer.

  @param VariableStoreHeader    The start of a EFI variable zone.
  @param VarList                The pointer to the VarList

  @retval address               If the variable existed in current NV, return address
  @return NULL                  Otherwise, return NULL
**/
VARIABLE_HEADER  *
FindVariableInNv (
  IN     VARIABLE_STORE_HEADER  *VariableStoreHeader,
  IN     VARIABLE_TYPE          VariableType,
  IN     VARIABLE_INFO_PRIVATE  *Storage
  )
{
  BOOLEAN          Flag;
  VARIABLE_HEADER  *Variable;
  VARIABLE_HEADER  *EndOfVariable;
  CHAR16           *VariableName;
  EFI_GUID         *VendorGuid;

  Flag            = FALSE;
  Variable        = NULL;
  EndOfVariable   = NULL;
  VariableName    = NULL;
  VendorGuid      = NULL;

  if ((VariableStoreHeader == NULL) || (Storage == NULL) || (Storage->Name == NULL)) {
    return NULL;
  }
  Variable      = GetStartPointer (VariableStoreHeader);
  EndOfVariable = GetEndPointer(VariableStoreHeader);
  //
  // Parse and compare the variable in the NV space one by one
  //
  while ((Variable != EndOfVariable) && (Variable != NULL)) {
    VariableName = (CHAR16 *)GetVariableNamePtr (Variable, VariableType);
    if (NULL == VariableName) {
      return NULL;
    }
    VendorGuid = GetVariableGuidPtr (Variable, VariableType);
    if (NULL == VendorGuid) {
      return NULL;
    }
    if ((CompareGuid (VendorGuid, &Storage->Guid) == 0) &&
        (KeyEnrollStrCmp (Storage->Name, VariableName) == 0) &&
        (Variable->Common.State == VAR_ADDED)) {
      Flag = TRUE;
      break;
    }
    Variable = GetNextVariablePtr (Variable, VariableType);
  }
  if (!Flag) {
    return NULL;
  }
  return Variable;
}

/**
  Exchange the data between Efi variable and the data of VarList when the
  variable use the authenticated variable header

  If VarToList is TRUE, copy the efi variable data to the VarList; Otherwise,
  update the data from varlist to efi variable.

  @param VarToList         The flag to control the direction of exchange.
  @param StorageListHead   Decide which variale list be updated

  @retval EFI_SUCCESS           Get the address successfully.
  @retval EFI_OUT_OF_RESOURCES  No available in the EFI variable zone.
**/
EFI_STATUS
SynEfiVariable (
  IN  BOOLEAN       VarToList,
  IN  VARIABLE_TYPE VariableType,
  IN  LIST_ENTRY    *StorageListHead
  )
{
  EFI_FIRMWARE_VOLUME_HEADER    *VarAddr;
  LIST_ENTRY                    *StorageLink;
  VARIABLE_INFO_PRIVATE         *Storage;
  EFI_STATUS                    Status;
  CHAR8                         *NewAvailableAddr;
  VARIABLE_HEADER               *VariableHeader;
  VARIABLE_HEADER               *EndOfVariable;
  VARIABLE_STORE_HEADER         *VariableStoreHeader;
  UINTN                         VarNameSize;
  CHAR16                        *VariableName;
  EFI_GUID                      *VendorGuid;
  UINT32                        Attributes;
  EFI_TIME                      *TimeStamp;

  VarAddr             = (EFI_FIRMWARE_VOLUME_HEADER   *) gEfiFdInfo.EfiVariableAddr;
  VariableStoreHeader = (VARIABLE_STORE_HEADER *)((CHAR8 *)VarAddr + VarAddr->HeaderLength);
  VariableHeader = GetStartPointer (VariableStoreHeader);
  EndOfVariable = GetEndPointer(VariableStoreHeader);

  if (VarToList) {
    //
    // Copy the data from NV to the VarList.
    //
    while ((UINTN)VariableHeader < (UINTN)EndOfVariable) {
      if (!IsValidVariableHeader (VariableHeader)) {
        break;
      }
      if (VariableHeader->Common.State != VAR_ADDED) {
        VariableHeader = GetNextVariablePtr (VariableHeader, VariableType);
        continue;
      }
      VariableName = GetVariableNamePtr (VariableHeader, VariableType);
      VendorGuid   = GetVariableGuidPtr (VariableHeader, VariableType);
      if (NULL == VariableName || NULL == VendorGuid) {
        return EFI_INVALID_PARAMETER;
      }
      Attributes = AttributesOfVariable (VariableHeader, VariableType);
      TimeStamp = NULL;
      if ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) {
        TimeStamp = &VariableHeader->TimeBasedAuth.TimeStamp;
      }
      Status = CreateVariableList (
                 StorageListHead,
                 VariableName,
                 VendorGuid,
                 Attributes,
                 TimeStamp,
                 DataSizeOfVariable (VariableHeader, VariableType),
                 GetVariableDataPtr (VariableHeader, VariableType),
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        printf ("Error. CreateVariableList fail.\n");
        return EFI_OUT_OF_RESOURCES;
      }
      VariableHeader = GetNextVariablePtr (VariableHeader, VariableType);
    }
    return EFI_SUCCESS;
  } else {
    //
    // Clear Variable region, then copy the List data to the variable in NV directly.
    //
    memset (VariableHeader, 0xFF, (UINTN)EndOfVariable - (UINTN)VariableHeader);
    NewAvailableAddr = NULL;
    StorageLink = GetFirstNode (StorageListHead);
    while (!IsNull (StorageListHead, StorageLink)) {
      Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (StorageLink);
      //
      // Report error, if the variable name is invalid.
      //
      if ((Storage->Name == NULL) || (KeyEnrollStrLen(Storage->Name) == 0)) {
        printf ("Error. One variable name is NULL. Its GUID is: ");
        PrintGuid(&(Storage->Guid));
        return EFI_INVALID_PARAMETER;
      }

      //
      // If existed, copy the List data to the variable in NV directly. If not found, create a new one.
      //
      VarNameSize = KeyEnrollStrSize (Storage->Name);

      Status = GetVariableVar (
                 VariableStoreHeader,
                 VariableType,
                 GET_PAD_SIZE (KeyEnrollStrSize (Storage->Name)) + GET_PAD_SIZE (Storage->Size) + SizeOfVariableHeader (VariableType),
                 &NewAvailableAddr
                 );
      if (EFI_ERROR (Status)) {
        printf ("Error. No available space in NV ram.\n");
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Create the authenticated variable header
      //
      VariableHeader                  = (VARIABLE_HEADER *) NewAvailableAddr;
      VariableHeader->Common.StartId         = VARIABLE_DATA;
      VariableHeader->Common.State           = VAR_ADDED;
      VariableHeader->Common.Reserved        = 0x0;
      switch (VariableType) {
      case VariableTypeCountBasedAuth:
        VariableHeader->CountBasedAuth.MonotonicCount  = 0x0;
        VariableHeader->CountBasedAuth.PubKeyIndex     = 0x0;
        break;
      case VariableTypeTimeBasedAuth:
        VariableHeader->TimeBasedAuth.MonotonicCount  = 0x0;
        VariableHeader->TimeBasedAuth.PubKeyIndex     = 0x0;
        memset (&(VariableHeader->TimeBasedAuth.TimeStamp), 0, sizeof (EFI_TIME));
        if ((Storage->Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) {
          CopyMem (&(VariableHeader->TimeBasedAuth.TimeStamp), &Storage->TimeStamp, sizeof (Storage->TimeStamp));
        }
        break;
      default:
        break;
     }
      SetVariableAttributes (VariableHeader, VariableType, Storage->Attributes);
      SetVariableNameSize (VariableHeader, VariableType, VarNameSize);
      SetVariableDataSize (VariableHeader, VariableType, Storage->Size);
      //
      //Copy the Guid, variable name, and data in sequence.
      //
      SetVariableGuid (VariableHeader, VariableType, &(Storage->Guid));
      SetVariableName (VariableHeader, VariableType, Storage->Name, VarNameSize);
      SetVariableData  (VariableHeader, VariableType, Storage->Buffer, Storage->Size);

      StorageLink = GetNextNode (StorageListHead, StorageLink);
    }
    return EFI_SUCCESS;
  }
}

/**
  Check the store variable type

  @param VariableStoreHeader    The pointer to the header of Variable Store.

  @return VariableType VariableType
**/

UINT32
CheckVarStore (
  IN VOID  *VariableStoreHeader
  )
{
  if (CompareGuid (
         &gEfiVariableGuid,
         &((VARIABLE_STORE_HEADER *)VariableStoreHeader)->Signature) == 0) {
    return VariableTypeNormal;
  } else if (CompareGuid (
                &gEfiAuthenticatedVariableGuid,
                &((VARIABLE_STORE_HEADER *)VariableStoreHeader)->Signature) == 0) {
    return VariableTypeCountBasedAuth;
  } else if (CompareGuid (
                &gEfiAuthenticatedVariableBasedTimeGuid,
                &((VARIABLE_STORE_HEADER *)VariableStoreHeader)->Signature) == 0) {
    return VariableTypeTimeBasedAuth;
  } else {
    return VariableTypeUnknown;
  }
}
