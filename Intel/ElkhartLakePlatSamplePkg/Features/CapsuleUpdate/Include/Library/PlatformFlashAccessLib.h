/** @file
  Platform flash device access library.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#ifndef __PLATFORM_FLASH_ACCESS_LIB_H__
#define __PLATFORM_FLASH_ACCESS_LIB_H__

#include <Protocol/FirmwareManagement.h>
#include <Protocol/Spi.h>

/**
  Perform EC firmware update.

  @param[in] Offset                  Offset relative to EC region to be programmed.
  @param[in] EcBinPtr                Pointer to EC FW binary.
  @param[in] EcBinSize               Size of EC FW binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                EC FW is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateEcFirmware (
  IN UINT32                                         Offset,
  IN UINT8                                          *EcBinPtr,
  IN UINTN                                          EcBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

/**
  Perform ME firmware update.

  @param[in] MeBinPtr                Pointer to ME FW binary.
  @param[in] MeBinSize               Size of ME FW binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                ME FW is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateMeFirmware (
  IN UINT8                                          *MeBinPtr,
  IN UINTN                                          MeBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

/**
  Perform ISH PDT configuration update

  @param[in] PdtBinPtr               Pointer to PDT binary.
  @param[in] PdtBinSize              Size of PDT binary.
  @param[in] Progress                A function used report the progress of the
                                     firmware update.  This is an optional parameter
                                     that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.
  @param[in] EndPercentage           The end completion percentage value that may
                                     be used to report progress during the flash
                                     write operation.

  @retval EFI_SUCCESS                PDT is updated successfully.
  @retval Others                     The update operation fails.

**/
EFI_STATUS
UpdateIshPdt (
  IN UINT8                                          *PdtBinPtr,
  IN UINTN                                          PdtBinSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

/**
  Perform BIOS region update.

  This function is intended to support both non-BiosGuard and BiosGuard cases.
  When BiosGuard is supported and enabled on the platform, BiosGuardUpdate argument
  is supposed to be TRUE and BgupImage is the Bios Guard Update Package along with
  input BIOS data buffer.
  Considering BIOS region might be updated by stage, the input argument FlashAddress
  indicates the relative or absolute BIOS region address (depends on FlashAddressType)
  to be flashed.

  @param[in] FlashAddress      The offset relative to BIOS region to be accessed.
  @param[in] Buffer            The pointer to the data buffer.
  @param[in] Length            The length of data buffer in bytes.
  @param[in] BiosGuardUpdate   Indicates if this update should be performed by
                               BiosGuard service or not.
  @param[in] BgupImage         If BiosGuardUpdate is TRUE, the pointer to the
                               BGUP image corresponding to Buffer used in
                               BiosGuard Update.
  @param[in] BgupImageSize     The length of BgupImage in bytes.
  @param[in] Progress          A function used report the progress of the
                               firmware update.  This is an optional parameter
                               that may be NULL.
  @param[in] StartPercentage   The start completion percentage value that may
                               be used to report progress during the flash
                               write operation.
  @param[in] EndPercentage     The end completion percentage value that may
                               be used to report progress during the flash
                               write operation.

  @retval EFI_SUCCESS           The operation returns successfully.
  @retval EFI_WRITE_PROTECTED   The flash device is read only.
  @retval EFI_DEVICE_ERROR      The flash update fails.
  @retval EFI_UNSUPPORTED       The flash device access is unsupported.
  @retval EFI_INVALID_PARAMETER The input parameter is not valid.
  @retval Others                Flash update failure

**/
EFI_STATUS
EFIAPI
UpdateBiosFirmware (
  IN EFI_PHYSICAL_ADDRESS                           FlashAddress,
  IN VOID                                           *Buffer,
  IN UINTN                                          Length,
  IN BOOLEAN                                        BiosGuardUpdate,
  IN VOID                                           *BgupImage,
  IN UINTN                                          BgupImageSize,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

EFI_STATUS
EFIAPI
SpiFlashErase (
  IN FLASH_REGION_TYPE                              FlashRegionType,
  IN UINT32                                         FlashAddress,
  IN UINT32                                         Length,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

EFI_STATUS
EFIAPI
SpiFlashUpdate (
  IN FLASH_REGION_TYPE                              FlashRegionType,
  IN UINT32                                         FlashAddress,
  IN UINT8                                          *Buffer,
  IN UINT32                                         Length,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

/**
  Get BIOS region base and size on UFS flash.

  @param[out] BiosRegionOffset   The address of BIOS region in flash.
  @param[out] BiosRegionSize     The size of BIOS region in bytes.

  @retval EFI_SUCCESS            The operation returns successfully.
  @retval EFI_INVALID_PARAMETER  The input parameter is not valid.

**/
EFI_STATUS
EFIAPI
GetUfsBiosRegion (
  OUT UINT32 *BiosRegionOffset,
  OUT UINT32 *BiosRegionSize
  );

/**
  Update BPDT signature with given value.

  @param[in] BpdtNum                     BPDT table number (0 or 1).
  @param[in] BpdtSignature               Value to be updated.
                                           Green       0x000055AA    //Normal Boot
                                           Yellow      0x00AA55AA    //Recovery Boot
                                           Red         0xFFFFFFFF    //any other value, ie !(GREEN || YELLOW)

  @retval EFI_SUCCESS                    The BPDT signature is updated successfully.
  @retval Others                         The update operation fails.

**/
EFI_STATUS
EFIAPI
UpdateBpdtSignature (
  IN UINT8  BpdtNum,
  IN UINT32 BpdtSignature
  );

/**
  Reads BIOS image from flash and copies to an input Buffer.

  @param[in] Buffer                      Pointer to the buffer to which image is copied.

  @retval EFI_SUCCESS                    Successfully copied image to buffer.
  @retval EFI_INVALID_PARAMETER          The input buffer is invalid.
  @retval Others                         Failed to get BIOS region.

**/
EFI_STATUS
EFIAPI
GetUfsBiosImageFromFlash (
  IN UINT8           *Buffer
  );

/**
  Return UFS TopSwap region size from PCD
**/
UINT32
GetUfsTopSwapBlockSize (
  VOID
  );

/**
  Update TopSwap region with the current IBB block on flash.

  @param[in] Progress                    A function used report the progress of the
                                         firmware update.  This is an optional parameter
                                         that may be NULL.
  @param[in] StartPercentage             The start completion percentage value that may
                                         be used to report progress during the flash
                                         write operation.
  @param[in] EndPercentage               The end completion percentage value that may
                                         be used to report progress during the flash
                                         write operation.

  @retval EFI_SUCCESS                    The flash region is updated successfully.
  @retval Others                         The update operation fails.

**/
EFI_STATUS
EFIAPI
UpdateUfsTopSwapArea (
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );
#endif
