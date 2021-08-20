/** @file
  Implementation of helper functions for interacting with UEFI variables.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _UEFI_VARIABLE_HELPER_LIB_H_
#define _UEFI_VARIABLE_HELPER_LIB_H_

#include <Uefi.h>
#include <Guid/VariableFormat.h>

/**
  Gets the pointer to the first variable header in given variable store area.

  @param VarStoreHeader  Pointer to the Variable Store Header.

  @return Pointer to the first variable header

**/
AUTHENTICATED_VARIABLE_HEADER *
GetStartPointer (
  IN VARIABLE_STORE_HEADER       *VarStoreHeader
  );

/**
  This code gets the pointer to the last variable memory pointer byte.

  @param  VarStoreHeader  Pointer to the Variable Store Header.

  @return AUTHENTICATED_VARIABLE_HEADER* pointer to last unavailable Variable Header.

**/
AUTHENTICATED_VARIABLE_HEADER *
GetEndPointer (
  IN VARIABLE_STORE_HEADER       *VarStoreHeader
  );

/**
  This code checks if variable header is valid or not.

  @param  Variable  Pointer to the Variable Header.

  @retval TRUE      Variable header is valid.
  @retval FALSE     Variable header is not valid.

**/
BOOLEAN
IsValidVariableHeader (
  IN  AUTHENTICATED_VARIABLE_HEADER   *Variable
  );

/**
  This code gets the size of name of variable.

  @param  Variable  Pointer to the Variable Header.
  @param  AuthFlag  Authenticated variable flag.

  @return Size of variable in bytes in type UINTN.

**/
UINTN
NameSizeOfVariable (
  IN  AUTHENTICATED_VARIABLE_HEADER     *AuthVariable,
  IN  BOOLEAN                           AuthFlag
  );

/**
  This code gets the size of data of variable.

  @param  Variable  Pointer to the Variable Header.
  @param  AuthFlag  Authenticated variable flag.

  @return Size of variable in bytes in type UINTN.

**/
UINTN
DataSizeOfVariable (
  IN  AUTHENTICATED_VARIABLE_HEADER     *AuthVariable,
  IN  BOOLEAN                           AuthFlag
  );

/**
  This code gets the size of variable header.

  @param AuthFlag   Authenticated variable flag.

  @return Size of variable header in bytes in type UINTN.

**/
UINTN
GetVariableHeaderSize (
  IN  BOOLEAN       AuthFlag
  );

/**
  This code gets the pointer to the variable name.

  @param   Variable  Pointer to the Variable Header.
  @param   AuthFlag  Authenticated variable flag.

  @return  A CHAR16* pointer to Variable Name.

**/
CHAR16 *
GetVariableNamePtr (
  IN  AUTHENTICATED_VARIABLE_HEADER     *Variable,
  IN BOOLEAN                            AuthFlag
  );

/**
  This code gets the pointer to the variable guid.

  @param Variable   Pointer to the Variable Header.
  @param AuthFlag   Authenticated variable flag.

  @return A EFI_GUID* pointer to Vendor Guid.

**/
EFI_GUID *
GetVendorGuidPtr (
  IN  AUTHENTICATED_VARIABLE_HEADER     *AuthVariable,
  IN  BOOLEAN                           AuthFlag
  );

/**
  This code gets the pointer to the variable data.

  @param   Variable  Pointer to the Variable Header.
  @param   AuthFlag  Authenticated variable flag.

  @return  A UINT8* pointer to Variable Data.

**/
UINT8 *
GetVariableDataPtr (
  IN  AUTHENTICATED_VARIABLE_HEADER     *Variable,
  IN  BOOLEAN                           AuthFlag
  );

/**
  This code gets the pointer to the next variable header.

  @param  Variable  Pointer to the Variable Header.
  @param  AuthFlag  Authenticated variable flag.

  @return  A AUTHENTICATED_VARIABLE_HEADER* pointer to next variable header.

**/
AUTHENTICATED_VARIABLE_HEADER *
GetNextVariablePtr (
  IN  AUTHENTICATED_VARIABLE_HEADER     *Variable,
  IN  BOOLEAN                           AuthFlag
  );

/**
  Prints UEFI variable data.

  @param  Data8     A pointer to a buffer of UEFI variable data.
  @param  DataSize  The size of UEFI variable data in the buffer.

**/
VOID
PrintVariableData (
  IN UINT8   *Data8,
  IN UINTN   DataSize
  );

#endif
