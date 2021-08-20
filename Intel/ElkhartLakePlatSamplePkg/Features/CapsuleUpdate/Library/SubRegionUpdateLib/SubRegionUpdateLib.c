/** @file
  Sub Region Update Library. Writes to Sub Region in Flash.

  Caution: This module requires additional review when modified.
  This module will have external input - capsule image.
  This external input must be validated carefully to avoid security issue like
  buffer overflow, integer overflow.

  SubRegionWrite() and VerifySubRegion() will receive untrusted input and do basic validation.

  Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/SubRegionUpdateLib.h>

/**
  Write SubRegion.

  Caution: This function may receive untrusted input.

  @param[in]   Image               The SubRegion image buffer.
  @param[in]   ImageSize           The size of SubRegion image buffer in bytes.
  @param[in]   SubRegionSignature  The Sub Region FV Signature.
  @param[in]   FlashSubRegionInfo  The info for the sub region being updated.
  @param[out]  AbortReason         A pointer to a pointer to a null-terminated string providing more
                                   details for the aborted operation. The buffer is allocated by this function
                                   with AllocatePool(), and it is the caller's responsibility to free it with a
                                   call to FreePool().

  @retval EFI_SUCCESS               The SubRegion image is written.
  @retval EFI_VOLUME_CORRUPTED      The SubRegion image is corrupt.
  @retval EFI_INCOMPATIBLE_VERSION  The SubRegion image version is incorrect.
  @retval EFI_SECURITY_VIOLATION    The SubRegion image fails to load.
  @retval EFI_WRITE_PROTECTED       The flash device is read only.
**/
EFI_STATUS
SubRegionWrite (
  IN  VOID                              *Image,
  IN  UINTN                             ImageSize,
  IN  UINT32                            SubRegionSignature,
  IN  FLASH_SUB_REGION_INFO             *FlashSubRegionInfo,
  OUT CHAR16                            **AbortReason
  )
{
  EFI_STATUS                                     Status = EFI_SUCCESS;
  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress = NULL;


  *AbortReason    = NULL;

  if (ImageSize > FlashSubRegionInfo->FvSize) {
    DEBUG ((DEBUG_INFO, "Image is too large for Sub Region.\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = SpiFlashErase (
               FlashRegionBios,
               (UINT32) FlashSubRegionInfo->Offset,
               (UINT32) FlashSubRegionInfo->FvSize,
               Progress,
               0,
               30
               );

  Status = SpiFlashUpdate (
               FlashRegionBios,
               (UINT32) FlashSubRegionInfo->Offset,
               (UINT8 *) Image,
               (UINT32) ImageSize,
               Progress,
               30,
               100
               );


  return Status;
}

// Add back when sub-region sanity check is ready
/*
BOOLEAN
IsImageForSubRegion (
  IN VOID*  Image,
  IN UINT64 ImageSize,
  IN UINT8  RegionType
  )
{
  return TRUE;
}
*/
