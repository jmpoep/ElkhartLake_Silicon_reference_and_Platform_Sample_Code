//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Header file for UserAuthentication formset.

  Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _USER_AUTHENTICATION_DXE_FORMSET_H_
#define _USER_AUTHENTICATION_DXE_FORMSET_H_

//
// Vendor GUID of the formset
//
#define USER_AUTHENTICATION_FORMSET_GUID \
  { 0x760e3022, 0xf149, 0x4560, {0x9c, 0x6f, 0x33, 0xaa, 0x7d, 0x48, 0x75, 0xfa} }

#define ADMIN_PASSWORD_KEY_ID       0x2001

#define MAX_PASSWORD_LEN  32
#define MIN_PASSWORD_LEN  0

#endif
