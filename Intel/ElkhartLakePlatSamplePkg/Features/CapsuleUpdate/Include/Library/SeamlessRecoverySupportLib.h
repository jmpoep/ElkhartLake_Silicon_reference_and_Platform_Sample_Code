/** @file
  Support Seamless Recovery based system firmware update.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#ifndef __SEAMLESS_RECOVERY_SUPPORT_LIB_H__
#define __SEAMLESS_RECOVERY_SUPPORT_LIB_H__

#include <Guid/SysFwUpdateProgress.h>

/**
  Delete all backup files from the external storage plus the associated NV variable.

**/
VOID
DeleteBackupFiles (
  VOID
  );

/**
  Save compact FvAdvanced image from both current/new BIOS to external storages.

  @param[in] FvAdvancedImage       Pointers to the compact FvAdvanced in new BIOS to be written to flash.
  @param[in] FvAdvancedImageSize   The size of FvAdvancedImage.
  @param[in] FvUefiBootImage       Pointers to the compact FvUefiBootImage in new BIOS to be written to flash.
  @param[in] FvUefiBootImageSize   The size of FvUefiBootImage.
  @param[in] FvOsBootImage         Pointers to the compact FvOsBootImage in new BIOS to be written to flash.
  @param[in] FvOsBootImageSize     The size of FvOsBootImage.

  @retval  EFI_SUCCESS         Successfully backed up necessary files on external storage.
  @retval  Others              Failed to back up necessary files.

**/
EFI_STATUS
SaveBackupBiosToFlash (
  VOID
  );

/**
  Save compact FvAdvanced image from both current/new BIOS to external storages.

  @param[in] FvAdvancedImage       Pointers to the compact FvAdvanced in new BIOS to be written to flash.
  @param[in] FvAdvancedImageSize   The size of FvAdvancedImage.
  @param[in] FvUefiBootImage       Pointers to the compact FvUefiBootImage in new BIOS to be written to flash.
  @param[in] FvUefiBootImageSize   The size of FvUefiBootImage.
  @param[in] FvOsBootImage         Pointers to the compact FvOsBootImage in new BIOS to be written to flash.
  @param[in] FvOsBootImageSize     The size of FvOsBootImage.

  @retval  EFI_SUCCESS         Successfully backed up necessary files on external storage.
  @retval  Others              Failed to back up necessary files.

**/
EFI_STATUS
SaveFvAdvancedToStorage (
  IN VOID                         *FvAdvancedImage,
  IN UINTN                        FvAdvancedImageSize,
  IN VOID                         *FvUefiBootImage,
  IN UINTN                        FvUefiBootImageSize,
  IN VOID                         *FvOsBootImage,
  IN UINTN                        FvOsBootImageSize
  );

/**
  Save current FMP Capsule and UX Capsule to external storages.

  @param[in] PayloadImage       Pointer to FMP payload image (FMP image header is stripped off).
  @param[in] PayloadImageSize   The size of PayloadImage.

  @retval  EFI_SUCCESS    Successfully backed up necessary files on external storage.
  @retval  Others         Failed to back up necessary files.

**/
EFI_STATUS
SaveCurrentCapsuleToStorage (
  IN VOID                         *PayloadImage,
  IN UINTN                        PayloadImageSize
  );

/**
  Check platform capability to support Fault tolerance based system firmware update.

  @retval TRUE  Current platform is capable of supporting Fault tolerance based system firmware update.
  @retval FALSE Current platform is incapable of supporting Fault tolerance based system firmware update.

**/
BOOLEAN
IsBiosFaultTolerantUpdateSupported (
  VOID
  );

/**
  Check if system firmware update got interrupted last time.

  @param[in,out] PreviousUpdateProgress      Pointers to the progress where updating process got
                                             interrupted last time.

  @retval TRUE   Previous update process got interrupted.
  @retval FALSE  There is no indication that update was in progress.

**/
BOOLEAN
IsPreviousUpdateUnfinished (
  IN OUT SYSTEM_FIRMWARE_UPDATE_PROGRESS       *PreviousUpdateProgress
  );

/**
  Record the current update progress

  @param[in] UpdatingComponent      The FW component being updated now.
  @param[in] UpdatingProgress       The updating stage associated to UpdatingComponent

  @retval EFI_SUCCESS   Update progress is recorded to NV storage successfully.
  @retval Others        Update progress is not recorded.

**/
EFI_STATUS
SetUpdateProgress (
  IN SYSTEM_FIRMWARE_COMPONENT  UpdatingComponent,
  IN UINT32                     UpdatingProgress
  );

/**
  Clear update progress in NV storage. This indicates that no FW update process is happening.

**/
VOID
ClearUpdateProgress (
  VOID
  );

/**
  Save both current and new BIOS images to external storage.

  @param[in] BiosImage         Pointer to the new BIOS image to be written to flash.
  @param[in] BiosImageSize     The size of new BIOS image.

  @retval  EFI_SUCCESS         Successfully backed up necessary files on external storage.
  @retval  Others              Failed to back up necessary files.

**/
EFI_STATUS
SaveBiosImageToStorage (
  IN      VOID                          *BiosImage,
  IN      UINTN                         BiosImageSize
  );
#endif
