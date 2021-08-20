/** @file
  Library instance provide common functions that can be shared among different
  FmpDeviceLib instances especially for the instance which involves BIOS and/or
  multiple components update.

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

#ifndef __BIOS_UPDATE_HELPERS_LIB_H__
#define __BIOS_UPDATE_HELPERS_LIB_H__

#include <Protocol/FirmwareManagement.h>

/**
  1. BIOS FMP Payload (FV.CapsulePayloadBios) is constructed as below:
  +------------------------------------------+
  |            EFI_FIRMWARE_VOLUME           |
  |  +------------------------------------+  |
  |  |       FFS (Configure File)         |  | <== gCapsuleBiosConfigFileGuid
  |  +------------------------------------+  |
  |  |         FFS (BIOS Image)           |  | <== gCapsuleBiosImageFileGuid
  |  |  +------------------------------+  |  |
  |  |  |       Compacted FV Advanced  |  |  | <== gFvAdvancedCompactFileGuid
  |  |  +------------------------------+  |  |
  |  +------------------------------------+  |
  +------------------------------------------+

  2. Monolithic FMP Payload (FV.CapsulePayloadMonolithic) is constructed as below:
  +------------------------------------------+
  |            EFI_FIRMWARE_VOLUME           |
  |  +------------------------------------+  |
  |  |       FFS (Configure File)         |  | <== gCapsuleBiosConfigFileGuid
  |  +------------------------------------+  |
  |  |         FFS (BIOS Image)           |  | <== gCapsuleBiosImageFileGuid
  |  |  +------------------------------+  |  |
  |  |  |       Compacted FV Advanced  |  |  | <== gFvAdvancedCompactFileGuid
  |  |  +------------------------------+  |  |
  |  +------------------------------------+  |
  |  |       FFS (Other components)       |  | <== gCapsuleMeImageFileGuid
  |  +------------------------------------+  |
  |  |       etc.                         |  |
  |  +------------------------------------+  |
  +------------------------------------------+

  NOTE:
  1. There might be multiple FFS (System Firmware Image) exist in the Monolithic/BIOS FMP Capsule.
  2. Above digram shows the input image of FmpDeviceSetImage()/FmpDeviceCheckImage() APIs where the
     FMP image header EFI_FIRMWARE_IMAGE_AUTHENTICATION and FMP_PAYLOAD_HEADER are stripped off.
  3. The format of the BIOS update configuration is below:

  [Head]
  NumOfUpdate    = <Num>     # Decimal
  ImageFileGuid  = XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX  # gCapsuleBiosImageFileGuid
  HelperFileGuid = XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX  # gCapsuleBiosBgupFileGuid (Optional)

  Update0        = <Name1>   # String
  Update1        = <Name2>   # String
  Update<Num-1>  = <NameX>   # String

  [Name?]
  BaseAddress    = <BaseAddress>    # Relative address to BIOS region on flash (HEX)
  Length         = <Length>         # Image Length (HEX)
  ImageOffset    = <ImageOffset>    # Image offset within file of ImageFileGuid (HEX)
  HelperOffset   = <ImageOffset>    # Image offset within file of HelperFileGuid (HEX) (Optional)
  HelperLength   = <HelperLength>   # Helper image Length (HEX) (Optional)

**/

//
// Use to indicate a dummy file
//
#define SYSTEM_FMP_DUMMY_FILE_SIGNATURE  SIGNATURE_32('$', 'D', 'U', 'M')

//
// Update data in config ini file
//
typedef struct {
  UINTN                           NumOfUpdates;
  EFI_GUID                        FileGuid;
  EFI_GUID                        HelperFileGuid;
} CONFIG_HEADER;

typedef struct {
  UINTN                           Index;
  EFI_PHYSICAL_ADDRESS            BaseAddress;
  UINTN                           Length;
  UINTN                           ImageOffset;
  UINTN                           HelperImageOffset;
  UINTN                           HelperImageLength;
} UPDATE_CONFIG_DATA;

/**
  Parse Config data file to get the updated data array.

  @param[in]      DataBuffer      Config raw file buffer.
  @param[in]      BufferSize      Size of raw buffer.
  @param[in, out] ConfigHeader    Pointer to the config header.
  @param[in, out] UpdateArray     Pointer to the config of update data.

  @retval EFI_NOT_FOUND         No config data is found.
  @retval EFI_OUT_OF_RESOURCES  No enough memory is allocated.
  @retval EFI_SUCCESS           Parse the config file successfully.

**/
EFI_STATUS
ParseUpdateDataFile (
  IN      UINT8                         *DataBuffer,
  IN      UINTN                         BufferSize,
  IN OUT  CONFIG_HEADER                 *ConfigHeader,
  IN OUT  UPDATE_CONFIG_DATA            **UpdateArray
  );

/**
  Extract the image raw data within input FvImage by FileName GUID.

  @param[in]   FvImage                 Pointer to a buffer containing FVs
  @param[in]   FvImageSize             The size of FvImage buffer in bytes.
  @param[in]   FileName                The FileName GUID of FFS to be found
  @param[out]  RawDataImage            The image pointer to requested raw data.
  @param[out]  RawDataImageSize        The size of RawDataImage.

  @retval TRUE  The image is extracted.
  @retval FALSE The image is not extracted.
**/
BOOLEAN
ExtractImageByName (
  IN VOID                  *FvImage,
  IN UINTN                 FvImageSize,
  IN EFI_GUID              *FileName,
  OUT VOID                 **RawDataImage,
  OUT UINTN                *RawDataImageSize
  );

/**
  Extract compact FvAdvanced image raw data from FMP payload image.

  The input image contains multiple FFS files. This function
  extract BIOS image first and then find out the compact FvAdvanced
  image within BIOS image.

  @param[in]   Image             Pointer to FMP payload image (FMP image header is stripped off)
  @param[in]   ImageSize         The size of input image in bytes.
  @param[out]  FvAdvancedImage       The image pointer to compacted FvAdvanced raw data.
  @param[out]  FvAdvancedImageSize   The size of compacted FvAdvanced image.

  @retval TRUE  The compacted FvAdvanced is extracted.
  @retval FALSE The compacted FvAdvanced is not extracted.

**/
BOOLEAN
ExtractFvAdvancedFromImage (
  IN      VOID                          *Image,
  IN      UINTN                         ImageSize,
  IN      EFI_GUID                      *FfsGuid,
  IN      VOID                          **FvAdvancedImage,
  IN      UINTN                         *FvAdvancedImageSize
  );

/**
  Check if the input Image contains expected files used for BIOS update.

  @param[in]   Image               Pointer to FMP payload image (FMP image header is stripped off)
  @param[in]   ImageSize           The size of Image in bytes

  @retval TRUE  The image contains expected files used for BIOS update.
  @retval FALSE The image does not contain expected files used for BIOS update.

**/
BOOLEAN
IsImageForBiosUpdate (
  IN      VOID                          *Image,
  IN      UINTN                         ImageSize
  );

/**
  Perform BIOS update in stages

  The input Image contains multiple FFS files including config data file
  and BIOS image file. This function extracts and parse config file first,
  then extracts BIOS and BGUP images described in config header.
  Finally update BIOS region by stage according to the address described in
  config data.
  This function povides the capability to support fault tolerant BIOS update
  by recording update progress and switching BootBlock region accordingly between
  update stages.

  @param[in] Image                   Pointer to FMP payload image (FMP image header is stripped off)
  @param[in] ImageSize               The size of Image in bytes
  @param[in] LastUpdatingProgress    Indicates the update progress if BIOS update got interrupted last time.
  @param[in] DisplayProgress         A function used to display the progress of the firmware update.
                                     This is an optional parameter that may be NULL.
  @param[in] StartPercentage         The start completion percentage value that may be used to report
                                     progress during the flash write operation.
  @param[in] EndPercentage           The end completion percentage value that may be used to report
                                     progress during the flash write operation.

  @retval EFI_SUCCESS                BIOS update is successfully performed.
  @retval Other                      BIOS update fails.

**/
EFI_STATUS
PerformBiosUpdateByConfigData (
  IN VOID                                           *Image,
  IN UINTN                                          ImageSize,
  IN UINT32                                         LastUpdatingProgress,
  IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  DisplayProgress,        OPTIONAL
  IN UINTN                                          StartPercentage,
  IN UINTN                                          EndPercentage
  );

#endif
