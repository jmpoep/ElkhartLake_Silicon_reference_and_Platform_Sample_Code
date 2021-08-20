/** @file  VariableCommon.h

 The header of common Variable.c TimeBasedVariable.c and MonotonicBasedVariable.c.

 Copyright (c) 2011 - 2014, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __VARIABLE_COMMON_H__
#define __VARIABLE_COMMON_H__

/**
  Check the store variable is no-authenticated or not

  @param VarToList     The pointer to the header of Variable Store.

  @retval TRUE         If no-authenticated, return TRUE.
  @retval FALSE        Otherwise, return FALSE.
**/

BOOLEAN
CheckNormalVarStoreOrNot (
  IN VOID  *VariableStoreHeader
  );
/**
  Check the store variable is Monotonic based authenticated or not

  @param VarToList     The pointer to the header of Variable Store.

  @retval TRUE         If authenticated, return TRUE.
  @retval FALSE        Otherwise, return FALSE.
**/

BOOLEAN
CheckMonotonicBasedVarStore (
  IN VOID  *VariableStoreHeader
  );

/**
  Check the store variable is Time stamp authenticated or not

  @param VarToList     The pointer to the header of Variable Store.

  @retval TRUE         If authenticated, return TRUE.
  @retval FALSE        Otherwise, return FALSE.
**/
BOOLEAN
CheckTimeBasedVarStoreOrNot (
  IN VOID  *VariableStoreHeader
  );



#endif // _EFI_VARIABLE_COMMON_H_
