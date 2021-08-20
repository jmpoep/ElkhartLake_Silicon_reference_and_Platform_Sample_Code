/** @file
  FmpDeviceLib instance to support BIOS update

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

#include <PiDxe.h>

#include <Library/FmpDeviceLib.h>

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/BiosIdLib.h>
#include <Library/PlatformFlashAccessLib.h>
#include <Library/BiosUpdateHelpersLib.h>
#include <Library/SeamlessRecoverySupportLib.h>
#include <Library/BootMediaLib.h>

/**
  Used to pass the FMP install function to this lib.  This allows the library to
  have control of the handle that the FMP instance is installed on.  This allows
  the library to use DriverBinding protocol model to locate its device(s) in the
  system.

  @param[in] Func  Function pointer to FMP install function.

  @retval EFI_SUCCESS       Library has saved function pointer and will call
                            function pointer on each DriverBinding Start.
  @retval EFI_UNSUPPORTED   Library doesn't use driver binding and only supports
                            a single instance.
  @retval other error       Error occurred.  Don't install FMP

**/
EFI_STATUS
EFIAPI
RegisterFmpInstaller (
  IN FMP_DEVICE_LIB_REGISTER_FMP_INSTALLER Func
  )
{
  //
  // This is a system firmware update that does not use Driver Binding Protocol
  //
  return EFI_UNSUPPORTED;
}


/**
  Returns the size, in bytes, of the firmware image currently stored in the
  firmware device.  This function is used to by the GetImage() and
  GetImageInfo() services of the Firmware Management Protocol.  If the image
  size can not be determined from the firmware device, then 0 must be returned.

  @param[out] Size  Pointer to the size, in bytes, of the firmware image
                    currently stored in the firmware device.

  @retval EFI_SUCCESS            The size of the firmware image currently
                                 stored in the firmware device was returned.
  @retval EFI_INVALID_PARAMETER  Size is NULL.
  @retval EFI_UNSUPPORTED        The firmware device does not support reporting
                                 the size of the currently stored firmware image.
  @retval EFI_DEVICE_ERROR       An error occured attempting to determine the
                                 size of the firmware image currently stored in
                                 in the firmware device.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetSize (
  IN UINTN  *Size
  )
{
  if (Size == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Size = FixedPcdGet32 (PcdBiosSize);
  return EFI_SUCCESS;
}

/**
  Used to return a library supplied guid that will be the ImageTypeId guid of
  the FMP descriptor.  This is optional but can be used if at runtime the guid
  needs to be determined.

  @param[out] Guid  Double Guid Ptr that will be updated to point to guid.
                    This should be from static memory and will not be freed.

  @return EFI_UNSUPPORTED  Library instance doesn't need dynamic guid.
  @return Error            Any error will cause the wrapper to use the GUID
                           defined by PCD.
  @return EFI_SUCCESS      Guid ptr should be updated to point to static memeory
                           which contains a valid guid.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetImageTypeIdGuidPtr (
  OUT EFI_GUID  **Guid
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Returns values used to fill in the AttributesSupported and AttributesSettings
  fields of the EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the
  GetImageInfo() service of the Firmware Management Protocol.  The following
  bit values from the Firmware Management Protocol may be combined:
    IMAGE_ATTRIBUTE_IMAGE_UPDATABLE
    IMAGE_ATTRIBUTE_RESET_REQUIRED
    IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED
    IMAGE_ATTRIBUTE_IN_USE
    IMAGE_ATTRIBUTE_UEFI_IMAGE

  @param[out] Supported  Attributes supported by this firmware device.
  @param[out] Setting    Attributes settings for this firmware device.

  @retval EFI_SUCCESS            The attributes supported by the firmware
                                 device were returned.
  @retval EFI_INVALID_PARAMETER  Supported is NULL.
  @retval EFI_INVALID_PARAMETER  Setting is NULL.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetAttributes (
  IN OUT UINT64  *Supported,
  IN OUT UINT64  *Setting
  )
{
  if (Supported == NULL || Setting == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Supported = (IMAGE_ATTRIBUTE_IMAGE_UPDATABLE         |
                IMAGE_ATTRIBUTE_RESET_REQUIRED          |
                IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED |
                IMAGE_ATTRIBUTE_IN_USE
                );
  *Setting   = (IMAGE_ATTRIBUTE_IMAGE_UPDATABLE         |
                IMAGE_ATTRIBUTE_RESET_REQUIRED          |
                IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED
                );

  if (PcdGet8 (PcdSystemFirmwareFmpSupportedMode) != 0) {
    //
    // Expose ESRT entry if not in Monolithic mode.
    //
    *Setting = *Setting | IMAGE_ATTRIBUTE_IN_USE;
  }

  return EFI_SUCCESS;
}

/**
  Gets the current Lowest Supported Version.

  This is a protection mechanism so that a previous version with known issue is
  not applied.  ONLY implement this if your running firmware has a method to
  return this at runtime.  If EFI_UNSUPPORTED is returned, then the Lowest
  Supported Version is stored in a UEFI Variable.

  @param[out] Version  On return this value represents the current Lowest
                       Supported Version (in same format as GetVersion).

  @retval EFI_SUCCESS       The Lowest Supported Version was correctly retrieved
  @retval EFI_UNSUPPORTED   Device firmware doesn't support reporting LSV
  @retval EFI_DEVICE_ERROR  Error occurred when trying to get the LSV
**/
EFI_STATUS
EFIAPI
FmpDeviceGetLowestSupportedVersion (
  IN OUT UINT32  *LowestSupportedVersion
  )
{
  //
  // Retrieve the lowest support version from a PCD
  // NOTE: This method of using a PCD can only be used for the system firmware
  //       FMP instance that is updated every time the system firmware is
  //       updated.  If system firmware updates support partial updates that
  //       would not include the system firmware FMP instance, then a PCD can
  //       not be used and the value must come from the currently running system
  //       firmware image.
  //
  *LowestSupportedVersion = PcdGet32 (PcdSystemFirmwareFmpLowestSupportedVersion);
  return EFI_SUCCESS;
}

/**
  Returns the Null-terminated Unicode string that is used to fill in the
  VersionName field of the EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is
  returned by the GetImageInfo() service of the Firmware Management Protocol.
  The returned string must be allocated using EFI_BOOT_SERVICES.AllocatePool().

  @note It is recommended that all firmware devices support a method to report
        the VersionName string from the currently stored firmware image.

  @param[out] VersionString  The version string retrieved from the currently
                             stored firmware image.

  @retval EFI_SUCCESS            The version string of currently stored
                                 firmware image was returned in Version.
  @retval EFI_INVALID_PARAMETER  VersionString is NULL.
  @retval EFI_UNSUPPORTED        The firmware device does not support a method
                                 to report the version string of the currently
                                 stored firmware image.
  @retval EFI_DEVICE_ERROR       An error occurred attempting to retrieve the
                                 version string of the currently stored
                                 firmware image.
  @retval EFI_OUT_OF_RESOURCES   There are not enough resources to allocate the
                                 buffer for the version string of the currently
                                 stored firmware image.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetVersionString (
  OUT CHAR16  **VersionString
  )
{
  CHAR16                            Version[100];

  if (VersionString == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (Version, sizeof (CHAR16) * 100);
  GetBiosVersionDateTime (Version, NULL, NULL);
  *VersionString = (CHAR16 *)AllocateCopyPool (
                               sizeof (CHAR16) * 100,
                               Version
                               );

  if (*VersionString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  return EFI_SUCCESS;
}

/**
  Gets the current running version.

  ONLY implement this if your running firmware has a method to return this at
  runtime.

  @param[out] Version  On return this value represents the current running
                       version.

  @retval EFI_SUCCESS       The version was correctly retrieved.
  @retval EFI_UNSUPPORTED   Device firmware doesn't support reporting current
                            version.
  @retval EFI_DEVICE_ERROR  Error occurred when trying to get the version.
**/
EFI_STATUS
EFIAPI
FmpDeviceGetVersion (
  IN OUT UINT32  *Version
  )
{
  EFI_STATUS                        Status;
  BIOS_ID_IMAGE                     BiosIdImage;
  CHAR16                            MajorVersion[10];
  CHAR16                            MinorVersion[10];

  ZeroMem (&BiosIdImage, sizeof (BIOS_ID_IMAGE));
  ZeroMem (MajorVersion, sizeof (CHAR16) * 10);
  ZeroMem (MinorVersion, sizeof (CHAR16) * 10);

  Status = GetBiosId (&BiosIdImage);
  if (Status == EFI_SUCCESS) {
    StrnCpyS (MajorVersion, 5, BiosIdImage.BiosIdString.VersionMajor, 4);
    StrnCpyS (MinorVersion, 5, BiosIdImage.BiosIdString.VersionMinor, 4);
    *Version = (UINT32) ((StrDecimalToUintn (MajorVersion) * 100) + StrDecimalToUintn (MinorVersion));
  }

  return Status;
}


/**
  Retrieves a copy of the current firmware image of the device.

  This function allows a copy of the current firmware image to be created and
  saved.  The saved copy could later been used, for example, in firmware image
  recovery or rollback.

  @param[out] Image      Points to the buffer where the current image is copied
                         to.
  @param[out] ImageSize  On entry, points to the size of the buffer pointed to
                         by Image, in bytes.  On return, points to the length of
                         the image, in bytes.

  @retval EFI_SUCCESS            The image was successfully read from the device.
  @retval EFI_BUFFER_TOO_SMALL   The buffer specified by ImageSize is too small
                                 to hold the image. The current buffer size
                                 needed to hold the image is returned in
                                 ImageSize.
  @retval EFI_INVALID_PARAMETER  The Image was NULL.
  @retval EFI_NOT_FOUND          The current image is not copied to the buffer.
  @retval EFI_UNSUPPORTED        The operation is not supported.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetImage (
  IN OUT VOID   *Image,
  IN OUT UINTN  *ImageSize
  )
{
  //
  // Check for invalid parameters
  //
  if (Image == NULL || ImageSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Make sure the buffer is big enough to hold the device image
  //
  if (*ImageSize < PcdGet32 (PcdBiosSize)) {
    *ImageSize = PcdGet32 (PcdBiosSize);
    return EFI_BUFFER_TOO_SMALL;
  }

  //
  // Copy the device image to the buffer
  //
  *ImageSize = PcdGet32 (PcdBiosSize);
  CopyMem (
    Image,
    (VOID *)(UINTN)PcdGet32 (PcdBiosAreaBaseAddress),
    *ImageSize
    );

  return EFI_SUCCESS;
}

/**
  Updates the firmware image of the device.

  This function updates the hardware with the new firmware image.  This function
  returns EFI_UNSUPPORTED if the firmware image is not updatable.  If the
  firmware image is updatable, the function should perform the following minimal
  validations before proceeding to do the firmware image update.
    - Validate the image is a supported image for this device.  The function
      returns EFI_ABORTED if the image is unsupported.  The function can
      optionally provide more detailed information on why the image is not a
      supported image.
    - Validate the data from VendorCode if not null.  Image validation must be
      performed before VendorCode data validation.  VendorCode data is ignored
      or considered invalid if image validation failed.  The function returns
      EFI_ABORTED if the data is invalid.

  VendorCode enables vendor to implement vendor-specific firmware image update
  policy.  Null if the caller did not specify the policy or use the default
  policy.  As an example, vendor can implement a policy to allow an option to
  force a firmware image update when the abort reason is due to the new firmware
  image version is older than the current firmware image version or bad image
  checksum.  Sensitive operations such as those wiping the entire firmware image
  and render the device to be non-functional should be encoded in the image
  itself rather than passed with the VendorCode.  AbortReason enables vendor to
  have the option to provide a more detailed description of the abort reason to
  the caller.

  @param[in]  Image             Points to the new image.
  @param[in]  ImageSize         Size of the new image in bytes.
  @param[in]  VendorCode        This enables vendor to implement vendor-specific
                                firmware image update policy. Null indicates the
                                caller did not specify the policy or use the
                                default policy.
  @param[in]  Progress          A function used by the driver to report the
                                progress of the firmware update.
  @param[in]  CapsuleFwVersion  FMP Payload Header version of the image.
  @param[out] AbortReason       A pointer to a pointer to a null-terminated
                                string providing more details for the aborted
                                operation. The buffer is allocated by this
                                function with AllocatePool(), and it is the
                                caller's responsibility to free it with a call
                                to FreePool().

  @retval EFI_SUCCESS            The device was successfully updated with the
                                 new image.
  @retval EFI_ABORTED            The operation is aborted.
  @retval EFI_INVALID_PARAMETER  The Image was NULL.
  @retval EFI_UNSUPPORTED        The operation is not supported.

**/
EFI_STATUS
EFIAPI
FmpDeviceSetImage (
  IN  CONST VOID                                     *Image,
  IN  UINTN                                          ImageSize,
  IN  CONST VOID                                     *VendorCode,
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,
  IN  UINT32                                         CapsuleFwVersion,
  OUT CHAR16                                         **AbortReason
  )
{
  EFI_STATUS                          Status;
  UINT32                              Updateable;
  SYSTEM_FIRMWARE_UPDATE_PROGRESS     PreviousProgress;
  VOID                                *FvAdvancedImage;
  UINTN                               FvAdvancedImageSize;
  VOID                                *FvUefiBootImage;
  UINTN                               FvUefiBootImageSize;
  VOID                                *FvOsBootImage;
  UINTN                               FvOsBootImageSize;
  VOID                                *BiosImage;
  UINTN                               BiosImageSize;

  DEBUG ((DEBUG_INFO, "FmpDeviceSetImage (BIOS) - Start\n"));

  FvAdvancedImage     = NULL;
  FvAdvancedImageSize = 0;

  Updateable = 0;
  Status = FmpDeviceCheckImage (Image, ImageSize, &Updateable);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "FmpDeviceSetImage - Check Image failed with %r.\n", Status));
    return Status;
  }

  if (Updateable != IMAGE_UPDATABLE_VALID) {
    DEBUG((DEBUG_ERROR, "FmpDeviceSetImage - Check Image returned that the Image was not valid for update.  Updatable value = 0x%X.\n", Updateable));
    return EFI_ABORTED;
  }

  if (Progress == NULL) {
    DEBUG((DEBUG_ERROR, "FmpDeviceSetImage - Invalid progress callback\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Test Progress Callback function
  //
  Status = Progress (5);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "FmpDeviceSetImage - Progress Callback failed with Status %r.\n", Status));
  }

  //
  // Check if system is continuing from an interrupted update.
  // If not, save current Capsule image to storage for support seamless recovery
  // Otherwise, no need to backup files again.
  //
  if (!IsPreviousUpdateUnfinished (&PreviousProgress)) {
    if (BootMediaIsUfs ()) {
      if (ExtractImageByName ((VOID *) Image, ImageSize, &gCapsuleBiosImageFileGuid, &BiosImage, &BiosImageSize)) {
        Status = SaveBiosImageToStorage((VOID *) BiosImage, BiosImageSize);
        DEBUG ((DEBUG_INFO, "SaveBiosImageToStorage - Status: %r\n", Status));
      } else {
        DEBUG ((DEBUG_ERROR, "Fail to find BIOS image in Capsule file\n"));
        ASSERT (FALSE);
      }
    } else {
      if (!ExtractFvAdvancedFromImage ((VOID *) Image,
                        ImageSize,
                        &gFvAdvancedFileGuid,
                        &FvAdvancedImage,
                        &FvAdvancedImageSize)) {
        DEBUG ((DEBUG_ERROR, "Fail to find FvAdvanced in new BIOS image\n"));
        ASSERT (FALSE);
      }
      if (!ExtractFvAdvancedFromImage ((VOID *) Image,
                        ImageSize,
                        &gFvUefiBootFileGuid,
                        &FvUefiBootImage,
                        &FvUefiBootImageSize)) {
        DEBUG ((DEBUG_ERROR, "Fail to find FvUefiBoot in new BIOS image\n"));
        ASSERT (FALSE);
      }
      if (!ExtractFvAdvancedFromImage ((VOID *) Image,
                        ImageSize,
                        &gFvOsBootFileGuid,
                        &FvOsBootImage,
                        &FvOsBootImageSize)) {
        DEBUG ((DEBUG_ERROR, "Fail to find FvOsBoot in new BIOS image\n"));
        ASSERT (FALSE);
      }

      SaveFvAdvancedToStorage (FvAdvancedImage,
                              FvAdvancedImageSize,
                              FvUefiBootImage,
                              FvUefiBootImageSize,
                              FvOsBootImage,
                              FvOsBootImageSize);
    }

    SaveCurrentCapsuleToStorage ((VOID *) Image, ImageSize);
  } else {
    ASSERT (PreviousProgress.Component == UpdatingBios);
  }

  DEBUG ((DEBUG_INFO, "UpdateBios - Start\n"));
  Status = PerformBiosUpdateByConfigData (
             (VOID *) Image,
             ImageSize,
             PreviousProgress.Progress,
             Progress,
             5,
             99
             );

  DEBUG ((DEBUG_INFO, "UpdateBios - End (%r)\n", Status));

  ClearUpdateProgress ();
  DeleteBackupFiles ();
  Progress (100);

  DEBUG ((DEBUG_INFO, "FmpDeviceSetImage (BIOS) - %r\n", Status));

  return Status;
}

/**
  Checks if the firmware image is valid for the device.

  This function allows firmware update application to validate the firmware image without
  invoking the SetImage() first.

  @param[in]  Image              Points to the new image.
  @param[in]  ImageSize          Size of the new image in bytes.
  @param[out] ImageUpdatable     Indicates if the new image is valid for update. It also provides,
                                 if available, additional information if the image is invalid.

  @retval EFI_SUCCESS            The image was successfully checked.
  @retval EFI_INVALID_PARAMETER  The Image was NULL.

**/
EFI_STATUS
EFIAPI
FmpDeviceCheckImage (
  IN  CONST VOID  *Image,
  IN  UINTN       ImageSize,
  OUT UINT32      *ImageUpdateable
  )
{
  if (ImageUpdateable == NULL) {
    DEBUG((DEBUG_ERROR, "CheckImage - ImageUpdateable Pointer Parameter is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  //Set to valid and then if any tests fail it will update this flag.
  //
  *ImageUpdateable = IMAGE_UPDATABLE_VALID;

  if (Image == NULL) {
    DEBUG((DEBUG_ERROR, "CheckImage - Image Pointer Parameter is NULL.\n"));
    //
    // Not sure if this is needed
    //
    *ImageUpdateable = IMAGE_UPDATABLE_INVALID;
    return EFI_INVALID_PARAMETER;
  }

  //
  // Make sure the image has the inforamtion needed for updating BIOS
  //
  if (!IsImageForBiosUpdate ((VOID *) Image, ImageSize)) {
    *ImageUpdateable = IMAGE_UPDATABLE_INVALID;
  }

  return EFI_SUCCESS;
}

/**
  Device frimware should trigger lock mechanism so that device fw can not be
  updated or tampered with. This lock mechanism is generally only cleared by a
  full system reset (not just sleep state/low power mode)

  @retval EFI_SUCCESS           The device was successfully locked.
  @retval EFI_UNSUPPORTED       The hardware device/firmware doesn't support locking

**/
EFI_STATUS
EFIAPI
FmpDeviceLock (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "FmpDeviceLib(Bios): FmpDeviceLock() for system FLASH\n"));
  // FLASH security is relied on gSkipBiosLockForSysFwUpdateGuid.
  return EFI_UNSUPPORTED;
}

/**
  The constructor function.

  @param[in]  ImageHandle   The firmware allocated handle for the EFI image.
  @param[in]  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor successfully .
**/
EFI_STATUS
EFIAPI
FmpDeviceLibBiosConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;

  //
  // Determine supported mode if PCD has not been initialized.
  //
  if (PcdGet8 (PcdSystemFirmwareFmpSupportedMode) == 0xFF) {
    VariableSize = 0;
    Status = gRT->GetVariable (
                    L"LastAttemptStatus",
                    &gEfiCallerIdGuid,
                    NULL,
                    &VariableSize,
                    NULL
                    );
    if (Status == EFI_BUFFER_TOO_SMALL) {
      //
      // Last attemp status exists. Switch to standalone mode.
      //
      PcdSet8S (PcdSystemFirmwareFmpSupportedMode, 1);
    }
  }

  return EFI_SUCCESS;
}
