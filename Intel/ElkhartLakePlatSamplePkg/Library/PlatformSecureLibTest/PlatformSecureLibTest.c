//
// This file contains an 'Intel Peripheral Driver' and is
// licensed for Intel CPUs and chip sets under the terms of your
// license agreement with Intel or your vendor.  This file may
// be modified by the user, subject to additional terms of the
// license agreement
//
/** @file
  Provides a secure platform-specific method to clear PK(Platform Key).

  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/
#include <Library/PcdLib.h>

BOOLEAN    mSecurityPhysicalPresent;

/**
  Constructor function for Platform Security library.

  @param[in]  ImageHandle   The firmware allocated handle for the EFI image.
  @param[in]  SystemTable   A pointer to the EFI System Table.

  @retval  EFI_SUCCESS  When this function completed.

**/
EFI_STATUS
EFIAPI
PlatformSecureLibTestConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  mSecurityPhysicalPresent = PcdGetBool (PcdPhysicalPresent);

  mSecurityPhysicalPresent = TRUE;

  return EFI_SUCCESS;
}

/**

  This function provides a platform-specific method to detect whether the platform
  is operating by a physically present user.

  Programmatic changing of platform security policy (such as disable Secure Boot,
  or switch between Standard/Custom Secure Boot mode) MUST NOT be possible during
  Boot Services or after exiting EFI Boot Services. Only a physically present user
  is allowed to perform these operations.

  NOTE THAT: This function cannot depend on any EFI Variable Service since they are
  not available when this function is called in AuthenticateVariable driver.

  @retval  TRUE       The platform is operated by a physically present user.
  @retval  FALSE      The platform is NOT operated by a physically present user.

**/
BOOLEAN
EFIAPI
UserPhysicalPresent (
  VOID
  )
{
  //
  // Detect whether BIOS CFG Jumper is set in configuration mode.
  // Setting means platform is operated by a physical present user.
  //
  return mSecurityPhysicalPresent;
}
