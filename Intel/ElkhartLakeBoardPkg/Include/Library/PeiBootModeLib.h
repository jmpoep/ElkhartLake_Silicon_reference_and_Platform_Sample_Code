/** @file
Public header file for the Boot Mode Library.

@copyright
  Copyright (c) 2018 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by the
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is uniquely
  identified as "Intel Reference Module" and is licensed for Intel
  CPUs and chipsets under the terms of your license agreement with
  Intel or your vendor.This file may be modified by the user, subject
  to additional terms of the license agreement.

@par Specification
**/

#ifndef _BOOT_MODE_LIB_H_
#define _BOOT_MODE_LIB_H_

#include <Ppi/ReadOnlyVariable2.h>

/**
  Update boot mode if it is in capsule update boot mode.

  @retval EFI_SUCCESS             If we have a capsule available.
  @retval EFI_NOT_FOUND           No capsule detected.
**/
EFI_STATUS
EFIAPI
PreMemUpdateCapsuleBootMode (
  VOID
  );

/**
  Detect boot mode

  @retval EFI_BOOT_MODE
**/
EFI_BOOT_MODE
EFIAPI
DetectBootMode (
  VOID
  );

#endif
