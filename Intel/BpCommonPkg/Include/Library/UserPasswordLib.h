//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Provides services to set/verify password and return if the password is set.

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __USER_PASSWORD_LIB_H__
#define __USER_PASSWORD_LIB_H__

/**
  Validate if the password is correct.

  @param[in] Password               The user input password.
  @param[in] PasswordSize           The size of Password in byte.

  @retval EFI_SUCCESS               The password is correct.
  @retval EFI_SECURITY_VIOLATION    The password is incorrect.
  @retval EFI_INVALID_PARAMETER     The password or size is invalid.
  @retval EFI_OUT_OF_RESOURCES      Insufficient resources to verify the password.
  @retval EFI_ACCESS_DENIED         Password retry count reach.
**/
EFI_STATUS
EFIAPI
VerifyPassword (
  IN CHAR16         *Password,
  IN UINTN          PasswordSize
  );

/**
  Set a new password.

  @param[in] NewPassword            The user input new password.
                                    NULL means clear password.
  @param[in] NewPasswordSize        The size of NewPassword in byte.
  @param[in] OldPassword            The user input old password.
                                    NULL means no old password.
  @param[in] OldPasswordSize        The size of OldPassword in byte.

  @retval EFI_SUCCESS               The NewPassword is set successfully.
  @retval EFI_SECURITY_VIOLATION    The OldPassword is incorrect.
  @retval EFI_INVALID_PARAMETER     The password or size is invalid.
  @retval EFI_OUT_OF_RESOURCES      Insufficient resources to set the password.
  @retval EFI_ACCESS_DENIED         Password retry count reach.
  @retval EFI_UNSUPPORTED           NewPassword is not strong enough.
  @retval EFI_ALREADY_STARTED       NewPassword is in history.
**/
EFI_STATUS
EFIAPI
SetPassword (
  IN CHAR16         *NewPassword,     OPTIONAL
  IN UINTN          NewPasswordSize,
  IN CHAR16         *OldPassword,     OPTIONAL
  IN UINTN          OldPasswordSize
  );

/**
  Return if the password is set.

  @retval TRUE      The password is set.
  @retval FALSE     The password is not set.
**/
BOOLEAN
EFIAPI
IsPasswordInstalled (
  VOID
  );

#endif
