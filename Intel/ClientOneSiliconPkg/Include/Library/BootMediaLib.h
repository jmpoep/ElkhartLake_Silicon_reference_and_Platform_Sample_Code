/** @file
  Header file for the Boot Media Library.

@copyright
 Copyright (c) 2017 - 2019 Intel Corporation. All rights reserved
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
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification
**/

#ifndef _BOOT_MEDIA_LIB_H_
#define _BOOT_MEDIA_LIB_H_

#include <Uefi.h>

typedef enum {
  BootMediaSpi,
  BootMediaUfs,
  BootMediaMax
} BOOT_MEDIA_TYPE;

typedef struct {
  BOOT_MEDIA_TYPE BootMedia;
} BOOT_MEDIA_HOB_DATA;

/**
  Determines the current platform boot media device.

  @param[out] BootMedia       The current platform Boot Media type.

  @retval     EFI_SUCCESS     The operation completed successfully.
  @retval     EFI_NOT_FOUND   The boot media type could not be found.
**/
EFI_STATUS
EFIAPI
GetBootMediaType (
  OUT BOOT_MEDIA_TYPE   *BootMedia
  );

/**
  Determines if the boot media is presently known.

  Note: Very early in boot this data may not be available.

  @retval TRUE        Boot media is known
  @retval FALSE       Boot media is not known
**/
BOOLEAN
EFIAPI
BootMediaIsKnown (
  VOID
  );

/**
  Determines if the platform firmware is booting from SPI or not.

  @retval TRUE        Platform firmware is booting from SPI
  @retval FALSE       Platform firmware is booting from a non-SPI device (eMMC, UFS, etc.)
**/
BOOLEAN
EFIAPI
BootMediaIsSpi (
  VOID
  );

/**
  Determines if the platform firmware is booting from UFS or not.

  @retval TRUE        Platform firmware is booting from UFS
  @retval FALSE       Platform firmware is booting from a non-UFS device (eMMC, SPI, etc.)
**/
BOOLEAN
EFIAPI
BootMediaIsUfs (
  VOID
  );

/**
  Reads the boot media type from hardware.

  By definition, this function is hardware-specific and implementation may vary to accommodate the method
  use to read the boot device in hardware.

  @retval BOOT_MEDIA_TYPE   The boot media type.
**/
BOOT_MEDIA_TYPE
EFIAPI
ReadBootMediaTypeFromHardware (
  VOID
  );

#endif
