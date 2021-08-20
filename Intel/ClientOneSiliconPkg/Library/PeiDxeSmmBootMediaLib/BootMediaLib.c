/** @file
  Boot Media Library.

@copyright
  @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <CpuRegs.h>
#include <Library/BaseLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>

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
  )
{
  UINT32 AcmStatusPolicyData;

  //
  // Read the boot device from the upper DWORD of the 64-bit Boot Status register
  //
  AcmStatusPolicyData = MmioRead32 (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_BOOTSTATUS + 0x4);

  if ((AcmStatusPolicyData & B_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) == V_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) {
    return BootMediaUfs;
  }

  return BootMediaSpi;
}

/**
  Determines if the platform firmware is booting from UFS or not.

  @retval TRUE        Platform firmware is booting from UFS
  @retval FALSE       Platform firmware is booting from a non-UFS device (eMMC, SPI, etc.)
**/
BOOLEAN
EFIAPI
BootMediaIsUfs (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOT_MEDIA_TYPE BootMedia;

  Status = GetBootMediaType (&BootMedia);
  if (EFI_ERROR (Status) || BootMedia != BootMediaUfs) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Determines if the platform firmware is booting from SPI or not.

  @retval TRUE        Platform firmware is booting from SPI
  @retval FALSE       Platform firmware is booting from a non-SPI device (eMMC, UFS, etc.)
**/
BOOLEAN
EFIAPI
BootMediaIsSpi (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOT_MEDIA_TYPE BootMedia;

  Status = GetBootMediaType (&BootMedia);
  if (EFI_ERROR (Status) || BootMedia != BootMediaSpi) {
    return FALSE;
  } else {
    return TRUE;
  }
}
