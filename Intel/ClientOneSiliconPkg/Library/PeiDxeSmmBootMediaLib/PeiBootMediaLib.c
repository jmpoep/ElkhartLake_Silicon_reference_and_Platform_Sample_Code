/** @file
  PEI Boot Media Library.

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

/**
  This function retrieves the NEM map layout structure on a block media boot and produces
  a boot media HOB that will be used for the remainder of the boot.

  @retval     EFI_NOT_FOUND   The boot device indicator could not be found.
  @retval     EFI_SUCCESS     The boot device indicator was found successfully.
**/
EFI_STATUS
EFIAPI
ProduceBootMediaHob (
  VOID
  )
{
  BOOT_MEDIA_HOB_DATA BootMediaHobData;

  BootMediaHobData.BootMedia = ReadBootMediaTypeFromHardware ();
  if (BootMediaHobData.BootMedia == BootMediaMax) {
    return EFI_NOT_FOUND;
  }

  //
  // Build the BootMediaHob for consumption in BootMediaLib
  //
  BuildGuidDataHob (
    &gBootMediaHobGuid,
    &BootMediaHobData,
    sizeof (BOOT_MEDIA_HOB_DATA)
    );

  return EFI_SUCCESS;
}

/**
  Determines the current platform boot media device.

  @param[out] BootMedia       The current platform Boot Media type.

  @retval     EFI_SUCCESS     The operation completed successfully.
  @retval     EFI_NOT_FOUND   The boot media type could not be found.
**/
EFI_STATUS
EFIAPI
GetBootMediaType (
  OUT BOOT_MEDIA_TYPE   *BootMediaType
  )
{
  EFI_STATUS                Status;
  BOOT_MEDIA_HOB_DATA       *BootMediaHobData;
  EFI_HOB_GUID_TYPE         *GuidHobPtr;

  GuidHobPtr  = GetFirstGuidHob (&gBootMediaHobGuid);
  if (GuidHobPtr == NULL) {
    Status = ProduceBootMediaHob ();
    GuidHobPtr = GetFirstGuidHob (&gBootMediaHobGuid);
    if (EFI_ERROR (Status) || (GuidHobPtr == NULL)) {
      DEBUG ((DEBUG_ERROR, "BootMediaLib Error: Boot Media HOB does not exist!\n"));
      ASSERT (!EFI_ERROR (Status) && GuidHobPtr != NULL);
      //
      // The boot cannot continue if the boot device is unknown
      //
      CpuDeadLoop ();
    }
  }

  BootMediaHobData = (BOOT_MEDIA_HOB_DATA *) GET_GUID_HOB_DATA (GuidHobPtr);

  if (BootMediaHobData == NULL) {
    return EFI_NOT_FOUND;
  }

  if (BootMediaHobData->BootMedia != BootMediaSpi && BootMediaHobData->BootMedia != BootMediaUfs) {
    return EFI_NOT_FOUND;
  }
  *BootMediaType = BootMediaHobData->BootMedia;

  return EFI_SUCCESS;
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
  EFI_HOB_GUID_TYPE         *GuidHobPtr;

  GuidHobPtr  = GetFirstGuidHob (&gBootMediaHobGuid);
  return GuidHobPtr != NULL;
}
