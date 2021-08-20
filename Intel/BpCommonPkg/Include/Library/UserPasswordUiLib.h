//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Provides services to do password authentication.

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __USER_PASSWORD_UI_LIB_H__
#define __USER_PASSWORD_UI_LIB_H__

/**
  Do password authentication.

  @retval EFI_SUCCESS               Password authentication pass.
**/
EFI_STATUS
EFIAPI
UiDoPasswordAuthentication (
  VOID
  );

/**
  Set password verification policy.

  @param[in] NeedReVerify           Need re-verify or not.

  @retval EFI_SUCCESS               Set verification policy successfully.
  @retval EFI_OUT_OF_RESOURCES      Insufficient resources to set verification policy.
**/
EFI_STATUS
EFIAPI
UiSetPasswordVerificationPolicy (
  IN BOOLEAN    NeedReVerify
  );

#endif
