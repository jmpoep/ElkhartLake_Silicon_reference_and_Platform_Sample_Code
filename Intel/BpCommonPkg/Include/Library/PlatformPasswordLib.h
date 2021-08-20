//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Provides a platform-specific method to return password policy.

  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __PLATFORM_PASSWORD_LIB_H__
#define __PLATFORM_PASSWORD_LIB_H__

/**
  This function is called at password driver entrypoint.
  This function should be called only once, to clear the password.

  This function provides a way to reset the password, just in case
  the platform owner forgets the password.
  The platform should provide a secure way to make sure
  only the platform owner is allowed to clear password.

  Once the password is cleared, the platform should provide a way
  to set a new password.

  @retval TRUE  There is a platform request to clear the password.
  @retval FALSE There is no platform request to clear the password.
**/
BOOLEAN
EFIAPI
IsPasswordCleared (
  VOID
  );

/**
  This function is called if the password driver finds that the password is not enrolled,
  when the password is required to input.

  This function should return the action according to platform policy.

  @retval TRUE  The caller should force the user to enroll the password.
  @retval FALSE The caller may skip the password enroll.
**/
BOOLEAN
EFIAPI
NeedEnrollPassword (
  VOID
  );

#endif
