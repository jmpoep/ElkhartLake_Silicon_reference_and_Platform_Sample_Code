/** @file
  DXE SMM Boot Media Library.

@copyright
  @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>

BOOLEAN         mFoundBootDevice  = FALSE;
BOOT_MEDIA_TYPE mBootMedia        = BootMediaMax;

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
  )
{
  if (!mFoundBootDevice) {
    return EFI_NOT_FOUND;
  } else {
    if (mBootMedia == BootMediaMax) {
      return EFI_NOT_FOUND;
    }
    *BootMedia = mBootMedia;
    return EFI_SUCCESS;
  }
}

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
  )
{
  return mFoundBootDevice;
}

/**
  The DxeSmmBootMediaLib library constructor.

  This constructor depends upon gBootMediaHobGuid. It should be produced by the platform in the HOB producer phase.

  @param[in]  ImageHandle           The firmware allocated handle for the UEFI image.
  @param[in]  SystemTable           A pointer to the EFI system table.

  @retval     EFI_SUCCESS           The constructor executed successfully.
  @retval     EFI_NOT_FOUND         The gBootMediaHobGuid HOB could not be located or the boot media type is invalid.
**/
EFI_STATUS
EFIAPI
DxeSmmBootMediaLibInit (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  BOOT_MEDIA_HOB_DATA       *BootMediaHobData;
  BOOT_MEDIA_TYPE           BootMediaType;
  EFI_HOB_GUID_TYPE         *GuidHobPtr;

  GuidHobPtr  = GetFirstGuidHob (&gBootMediaHobGuid);
  if (GuidHobPtr == NULL) {
    BootMediaType = ReadBootMediaTypeFromHardware ();
  } else {
    BootMediaHobData = (BOOT_MEDIA_HOB_DATA *) GET_GUID_HOB_DATA (GuidHobPtr);
    BootMediaType = BootMediaHobData->BootMedia;
  }

  switch (BootMediaType) {
    case BootMediaSpi:
      mBootMedia        = BootMediaSpi;
      mFoundBootDevice  = TRUE;
      break;
    case BootMediaUfs:
      mBootMedia        = BootMediaUfs;
      mFoundBootDevice  = TRUE;
      break;
    case BootMediaMax:
    default:
      DEBUG ((DEBUG_ERROR, "BootMediaLib Error: Invalid Boot Media\n"));
      return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}
