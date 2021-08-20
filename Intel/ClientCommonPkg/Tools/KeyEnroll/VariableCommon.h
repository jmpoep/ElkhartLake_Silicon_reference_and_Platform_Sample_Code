//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The header of common Variable.c

Copyright (c) 2014 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation
(if any) is furnished under a license and may only be used or
copied in accordance with the terms of the license.  Except as
permitted by such license, no part of this software or
documentation may be reproduced, stored in a retrieval system, or
transmitted in any form or by any means without the express written
consent of Intel Corporation.

**/

#ifndef __VARIABLE_COMMON_H__
#define __VARIABLE_COMMON_H__

typedef enum {
  VariableTypeNormal,
  VariableTypeCountBasedAuth,
  VariableTypeTimeBasedAuth,
  VariableTypeUnknown,
} VARIABLE_TYPE;

/**
  Check the store variable type

  @param VariableStoreHeader    The pointer to the header of Variable Store.

  @return VariableType VariableType
**/

VARIABLE_TYPE
CheckVarStore (
  IN VOID  *VariableStoreHeader
  );

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
  );


EFI_STATUS
CreateVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid,
  IN  UINT32         Attributes,
  IN  EFI_TIME       *TimeStamp,
  IN  UINTN          Size,
  IN  UINT8          *Buffer,
  IN  BOOLEAN        Append
  );

EFI_STATUS
DeleteVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid
  );

LIST_ENTRY *
FindVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid
  );

VARIABLE_INFO_PRIVATE*
FindVariableInfoPtr(
  IN    CHAR16        *VariableName,
  IN    EFI_GUID      *VendorGuid
  );

#endif // _EFI_VARIABLE_COMMON_H_
