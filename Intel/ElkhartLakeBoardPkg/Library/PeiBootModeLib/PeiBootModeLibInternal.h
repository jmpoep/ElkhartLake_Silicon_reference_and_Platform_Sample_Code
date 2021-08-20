/** @file
Private header file for the Boot Mode Library.

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

#ifndef _BOOT_MODE_LIB_INTERNAL_H_
#define _BOOT_MODE_LIB_INTERNAL_H_

#define BOOT_SPECIAL_MASK                            0x80

/**
  Given the current boot mode, and a proposed new boot mode, determine
  which has priority. If the new boot mode has higher priority, then
  make it the current boot mode.

  @param[in][out] CurrentBootMode Pointer to current planned boot mode
  @param[in][out] NewBootMode     Proposed boot mode

  @retval         EFI_NOT_FOUND   If either boot mode is not recognized
  @retval         EFI_SUCCESS     If both boot mode values were
                                  recognized and were processed.
**/
EFI_STATUS
PrioritizeBootMode (
  IN OUT EFI_BOOT_MODE    *CurrentBootMode,
  IN EFI_BOOT_MODE        NewBootMode
  );

/**
  Check Fast Boot 30-second WDT (TCO Timer) timeout has occurred

  @retval  TRUE   Timeout has occurred
  @retval  FALSE  Timeout didnt occur
**/
BOOLEAN
IsTimeOutOccurred (
  VOID
  );

/**
  Check if the value is of ODD parity.

  @param[in]  Value  The 8 bits value

  @retval     TRUE   The value is of ODD parity
  @retval     FALSE  The value is not of ODD parity
**/
BOOLEAN
CheckOddParity (
  IN  UINT8 Value
  );

/**
  Update boot mode

  @param[in] BootMode             Current System BootMode.

  @retval EFI_SUCCESS             The boot mode was returned successfully.
**/

EFI_STATUS
EFIAPI
PreMemUpdateBootMode (
  IN OUT EFI_BOOT_MODE          *BootMode
  );

/**
  Check Boot Flag Status to determine if previous boot was successful

  @retval  TRUE   Previous Boot was success
  @retval  FALSE  Previous Boot wasn't success
**/
BOOLEAN
EFIAPI
IsPreviousBootSuccessful (
  VOID
  );

/**
  Query PCH to determine if Intrusion Detection set

  @retval  TRUE   No Change
  @retavl  FALSE  Change
**/

BOOLEAN
EFIAPI
IsBootWithNoChange (
  VOID
  );

/**
  Check if this system boot is due to 4sec power button override has occurred

  @retval  TRUE   Power Button Override occurred in last system boot
  @retval  FALSE  Power Button Override didnt occur
**/

BOOLEAN
EFIAPI
IsPowerButtonOverride (
  VOID
  );

/**
  Get simple boot flag

  @retval  LegacyValue
  @retval  EfiValue
**/

UINT8
EFIAPI
GetSimpleBootFlag (
  VOID
  );

/**
  Detect recovery mode

  @retval  EFI_SUCCESS       System in Recovery Mode
  @retval  EFI_UNSUPPORTED   System doesn't support Recovery Mode
  @retval  EFI_NOT_FOUND     System is not in Recovery Mode
**/
EFI_STATUS
IsRecoveryMode (
  VOID
  );

#endif
