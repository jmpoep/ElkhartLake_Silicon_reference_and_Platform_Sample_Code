//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Header file for UserAuthenticationSmm.

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __USER_AUTHENTICATION_SMM_H__
#define __USER_AUTHENTICATION_SMM_H__

#include <PiSmm.h>

#include <Protocol/SmmVariable.h>
#include <Protocol/VariableLock.h>

#include <Guid/UserAuthentication.h>

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/PlatformPasswordLib.h>

#include "KeyService.h"

#define PASSWORD_SALT_SIZE   32
#define PASSWORD_HASH_SIZE   32 // SHA256_DIGEST_SIZE

#define PASSWORD_MAX_TRY_COUNT  3
#define PASSWORD_HISTORY_CHECK_COUNT  5

//
// Name of the variable
//
#define USER_AUTHENTICATION_VAR_NAME L"Password"
#define USER_AUTHENTICATION_HISTORY_LAST_VAR_NAME L"PasswordLast"

//
// Variable storage
//
typedef struct {
  UINT8        PasswordHash[PASSWORD_HASH_SIZE];
  UINT8        PasswordSalt[PASSWORD_SALT_SIZE];
} USER_PASSWORD_VAR_STRUCT;

#endif
