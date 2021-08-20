//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  GUID is for UserAuthentication SMM communication.

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __USER_AUTHENTICATION_GUID_H__
#define __USER_AUTHENTICATION_GUID_H__

#define PASSWORD_MIN_SIZE    9  // MIN number of chars of password, including NULL.
#define PASSWORD_MAX_SIZE    33 // MAX number of chars of password, including NULL.

#define USER_AUTHENTICATION_GUID \
  { 0xf06e3ea7, 0x611c, 0x4b6b, { 0xb4, 0x10, 0xc2, 0xbf, 0x94, 0x3f, 0x38, 0xf2 } }

extern EFI_GUID gUserAuthenticationGuid;

typedef struct {
  UINTN       Function;
  EFI_STATUS  ReturnStatus;
} SMM_PASSWORD_COMMUNICATE_HEADER;

#define SMM_PASSWORD_FUNCTION_IS_PASSWORD_SET       1
#define SMM_PASSWORD_FUNCTION_SET_PASSWORD          2
#define SMM_PASSWORD_FUNCTION_VERIFY_PASSWORD       3
#define SMM_PASSWORD_FUNCTION_SET_VERIFY_POLICY     4
#define SMM_PASSWORD_FUNCTION_GET_VERIFY_POLICY     5
#define SMM_PASSWORD_FUNCTION_WAS_PASSWORD_VERIFIED 6

typedef struct {
  CHAR8                                 NewPassword[PASSWORD_MAX_SIZE];
  CHAR8                                 OldPassword[PASSWORD_MAX_SIZE];
} SMM_PASSWORD_COMMUNICATE_SET_PASSWORD;

typedef struct {
  CHAR8                                 Password[PASSWORD_MAX_SIZE];
} SMM_PASSWORD_COMMUNICATE_VERIFY_PASSWORD;

typedef struct {
  BOOLEAN                               NeedReVerify;
} SMM_PASSWORD_COMMUNICATE_VERIFY_POLICY;

#endif
