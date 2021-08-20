/** @file
  Library instance provide common functions that can be shared among different
  FmpDeviceLib instances especially for the instance which involves BIOS and/or
  multiple components update.

  The major functionalitise are:
  1. Extract files/compacted FvAdvanced from a given image
  2. Parse config ini file
  3. Perform BIOS update by config data with/without BiosGuard BGUP image

  Refer to BiosUpdateHelpersLib.h for more infomation about the image structure.

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
#include <Library/BiosUpdateHelpersLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/PlatformFlashAccessLib.h>
#include <Library/SeamlessRecoverySupportLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/BpdtLib.h>
#include <Library/BootMediaLib.h>

#include <Protocol/FirmwareVolumeBlock.h>
#include <Protocol/FirmwareVolume2.h>
#include <Register/PchRegsLpc.h>
#include <SetupVariable.h>

typedef struct {
  CHAR16                        *Name;
  EFI_GUID                      *Guid;
} USER_DATA_VARIABLE_ENTRY;

//
// Setup related variables that would be cleared after BIOS update if requested.
//
USER_DATA_VARIABLE_ENTRY mUserDataVariableList[] = {
  {L"Setup"               , &gSetupVariableGuid           },
  {L"MeInfoSetup"         , &gMeInfoSetupGuid             },
  {L"MeBiosExtensionSetup", &gEfiMeBiosExtensionSetupGuid },
  {L"TcgSetup"            , &gSetupVariableGuid           }
};

BOOLEAN                    mBiosGuardEnabled = FALSE;
SETUP_DATA                 mSetupData        = {0};

/**
  Check if a block of buffer is erased.

  @param[in] ErasePolarity  Erase polarity attribute of the firmware volume
  @param[in] InBuffer       The buffer to be checked
  @param[in] BufferSize     Size of the buffer in bytes

  @retval    TRUE           The block of buffer is erased
  @retval    FALSE          The block of buffer is not erased
**/
BOOLEAN
IsBufferErased (
  IN UINT8    ErasePolarity,
  IN VOID     *InBuffer,
  IN UINTN    BufferSize
  )
{
  UINTN   Count;
  UINT8   EraseByte;
  UINT8   *Buffer;

  if(ErasePolarity == 1) {
    EraseByte = 0xFF;
  } else {
    EraseByte = 0;
  }

  Buffer = InBuffer;
  for (Count = 0; Count < BufferSize; Count++) {
    if (Buffer[Count] != EraseByte) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Get FFS buffer pointer by FileName GUID and FileType.

  @param[in]   FdStart          The System Firmware FD image
  @param[in]   FdSize           The size of System Firmware FD image
  @param[in]   FileName         The FileName GUID of FFS to be found
  @param[in]   Type             The FileType of FFS to be found
  @param[out]  OutFfsBuffer     The FFS buffer found, including FFS_FILE_HEADER
  @param[out]  OutFfsBufferSize The size of FFS buffer found, including FFS_FILE_HEADER

  @retval TRUE  The FFS buffer is found.
  @retval FALSE The FFS buffer is not found.

**/
BOOLEAN
GetFfsByName (
  IN VOID                  *FdStart,
  IN UINTN                 FdSize,
  IN EFI_GUID              *FileName,
  IN EFI_FV_FILETYPE       Type,
  OUT VOID                 **OutFfsBuffer,
  OUT UINTN                *OutFfsBufferSize
  )
{
  UINTN                                     FvSize;
  EFI_FIRMWARE_VOLUME_HEADER                *FvHeader;
  EFI_FIRMWARE_VOLUME_EXT_HEADER            *FvExtHeader;
  EFI_FFS_FILE_HEADER                       *FfsHeader;
  UINT32                                    FfsSize;
  UINTN                                     TestLength;
  BOOLEAN                                   FvFound;

  DEBUG ((DEBUG_INFO, "GetFfsByName - FV: 0x%08x - 0x%08x\n", (UINTN)FdStart, (UINTN)FdSize));

  FvFound = FALSE;
  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FdStart;
  while ((UINTN)FvHeader < (UINTN)FdStart + FdSize - 1) {
    FvSize = (UINTN)FdStart + FdSize - (UINTN)FvHeader;

    if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
      FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)((UINTN)FvHeader + SIZE_4KB);
      continue;
    }
    DEBUG((DEBUG_INFO, "checking FV....0x%08x - 0x%x\n", FvHeader, FvHeader->FvLength));
    FvFound = TRUE;
    if (FvHeader->FvLength > FvSize) {
      DEBUG((DEBUG_INFO, "GetFfsByName - FvSize: 0x%08x, MaxSize - 0x%08x\n", (UINTN)FvHeader->FvLength, (UINTN)FvSize));
      return FALSE;
    }
    FvSize = (UINTN)FvHeader->FvLength;

    //
    // Find FFS
    //
    if (FvHeader->ExtHeaderOffset != 0) {
      FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8 *)FvHeader + FvHeader->ExtHeaderOffset);
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvExtHeader + FvExtHeader->ExtHeaderSize);
    } else {
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvHeader + FvHeader->HeaderLength);
    }
    FfsHeader = (EFI_FFS_FILE_HEADER *)((UINTN)FvHeader + ALIGN_VALUE((UINTN)FfsHeader - (UINTN)FvHeader, 8));

    while ((UINTN)FfsHeader < (UINTN)FvHeader + FvSize - 1) {
      DEBUG((DEBUG_INFO, "GetFfsByName - FFS: 0x%08x\n", FfsHeader));
      TestLength = (UINTN)((UINTN)FvHeader + FvSize - (UINTN)FfsHeader);
      if (TestLength > sizeof(EFI_FFS_FILE_HEADER)) {
        TestLength = sizeof(EFI_FFS_FILE_HEADER);
      }
      if (IsBufferErased (1, FfsHeader, TestLength)) {
        break;
      }

      if (IS_FFS_FILE2(FfsHeader)) {
        FfsSize = FFS_FILE2_SIZE (FfsHeader);
      } else {
        FfsSize = FFS_FILE_SIZE (FfsHeader);
      }

      if (CompareGuid (FileName, &FfsHeader->Name) &&
          ((Type == EFI_FV_FILETYPE_ALL) || (FfsHeader->Type == Type))) {
        //
        // Check section
        //
        *OutFfsBuffer = FfsHeader;
        *OutFfsBufferSize = FfsSize;
        return TRUE;
      } else {
        //
        // Any other type is not allowed
        //
        DEBUG((DEBUG_INFO, "GetFfsByName - other FFS type 0x%x, name %g\n", FfsHeader->Type, &FfsHeader->Name));
      }

      //
      // Next File
      //
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINTN)FfsHeader + ALIGN_VALUE(FfsSize, 8));
    }

    //
    // Next FV
    //
    FvHeader = (VOID *)(UINTN)((UINTN)FvHeader + FvHeader->FvLength);
    DEBUG((DEBUG_INFO, "Next FV....0x%08x - 0x%x\n", FvHeader, FvHeader->FvLength));
  }

  if (!FvFound) {
    DEBUG((DEBUG_ERROR, "GetFfsByName - NO FV Found\n"));
  }
  return FALSE;
}

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
  )
{
  BOOLEAN     Result;
  UINT32      FileHeaderSize;

  if ((FvImage == NULL) || (RawDataImage == NULL) || (RawDataImageSize == NULL)) {
    DEBUG ((DEBUG_ERROR, "ExtractImageByName: Invalid arguments\n"));
    ASSERT (FALSE);
    return FALSE;
  }

  *RawDataImage = NULL;
  *RawDataImageSize = 0;

  Result = GetFfsByName (FvImage, FvImageSize, FileName, EFI_FV_FILETYPE_RAW, RawDataImage, RawDataImageSize);
  if (!Result) {
    DEBUG ((DEBUG_INFO, "Extract image %g failed\n", FileName));
    return FALSE;
  }

  if (IS_FFS_FILE2 (*RawDataImage)) {
    FileHeaderSize = sizeof (EFI_FFS_FILE_HEADER2);
  } else {
    FileHeaderSize = sizeof (EFI_FFS_FILE_HEADER);
  }

  *RawDataImage = (UINT8 *)*RawDataImage + FileHeaderSize;
  *RawDataImageSize = *RawDataImageSize - FileHeaderSize;

  if (*((UINT32 *)(*RawDataImage)) == SYSTEM_FMP_DUMMY_FILE_SIGNATURE) {
    DEBUG ((DEBUG_INFO, "Dummy image (%g)\n", FileName));
    Result = FALSE;
    *RawDataImage = NULL;
    *RawDataImageSize = 0;
  }

  return Result;
}

/**
  Extract compacted FvAdvanced image raw data within input image FdStart.

  @param[in]   FdStart      The input BIOS image.
  @param[in]   FdSize       The size of input image in bytes.
  @param[out]  FvAdvancedStart  The image pointer to FvAdvanced raw data.
  @param[out]  FvAdvancedSize   The size of FvAdvanced image.

  @retval TRUE  The image is extracted.
  @retval FALSE The image is not extracted.

**/
BOOLEAN
FindFvAdvancedInBiosImage (
  IN VOID                  *FdStart,
  IN UINTN                 FdSize,
  IN EFI_GUID              *FfsGuid,
  OUT VOID                 **FvAdvancedStart,
  OUT UINTN                *FvAdvancedSize
  )
{
  UINTN                                     FvSize;
  EFI_FIRMWARE_VOLUME_HEADER                *FvHeader;
  EFI_FIRMWARE_VOLUME_EXT_HEADER            *FvExtHeader;
  EFI_FFS_FILE_HEADER                       *FfsHeader;
  UINT32                                    FfsSize;
  UINTN                                     TestLength;
  BOOLEAN                                   FvFound;

  DEBUG ((DEBUG_INFO, "FindFvAdvancedInImage: 0x%08x - 0x%08x\n", (UINTN)FdStart, (UINTN)FdSize));

  FvFound = FALSE;
  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FdStart;
  while ((UINTN)FvHeader < (UINTN)FdStart + FdSize - 1) {
    FvSize = (UINTN)FdStart + FdSize - (UINTN)FvHeader;

    if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
      FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)((UINTN)FvHeader + SIZE_4KB);
      continue;
    }
    DEBUG ((DEBUG_INFO, "checking FV....0x%08x - 0x%x\n", FvHeader, FvHeader->FvLength));
    FvFound = TRUE;
    if (FvHeader->FvLength > FvSize) {
      DEBUG ((DEBUG_INFO, "FindFvAdvancedInImage - FvSize: 0x%08x, MaxSize - 0x%08x\n", (UINTN)FvHeader->FvLength, (UINTN)FvSize));
      return FALSE;
    }
    FvSize = (UINTN)FvHeader->FvLength;

    //
    // Find FFS
    //
    if (FvHeader->ExtHeaderOffset != 0) {
      FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8 *)FvHeader + FvHeader->ExtHeaderOffset);
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvExtHeader + FvExtHeader->ExtHeaderSize);
    } else {
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvHeader + FvHeader->HeaderLength);
    }
    FfsHeader = (EFI_FFS_FILE_HEADER *)((UINTN)FvHeader + ALIGN_VALUE ((UINTN)FfsHeader - (UINTN)FvHeader, 8));

    while ((UINTN)FfsHeader < (UINTN)FvHeader + FvSize - 1) {
      TestLength = (UINTN)((UINTN)FvHeader + FvSize - (UINTN)FfsHeader);
      if (TestLength > sizeof(EFI_FFS_FILE_HEADER)) {
        TestLength = sizeof(EFI_FFS_FILE_HEADER);
      }
      if (IsBufferErased (1, FfsHeader, TestLength)) {
        break;
      }

      if (IS_FFS_FILE2 (FfsHeader)) {
        FfsSize = FFS_FILE2_SIZE (FfsHeader);
      } else {
        FfsSize = FFS_FILE_SIZE (FfsHeader);
      }

      if (CompareGuid (FfsGuid, &FfsHeader->Name) && (FfsHeader->Type == EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE)) {
        //
        // Check section
        //
        *FvAdvancedStart = (VOID *) FvHeader;
        *FvAdvancedSize = FvSize;
        DEBUG ((DEBUG_INFO, "Found FV which has FvAdvancedCompactFile (%g)....exit\n", &FfsHeader->Name));
        return TRUE;
      }

      //
      // Next File
      //
      FfsHeader = (EFI_FFS_FILE_HEADER *)((UINTN)FfsHeader + ALIGN_VALUE (FfsSize, 8));
    }

    //
    // Next FV
    //
    FvHeader = (VOID *)(UINTN)((UINTN)FvHeader + FvHeader->FvLength);
  }

  if (!FvFound) {
    DEBUG ((DEBUG_ERROR, "GetFfsByName - NO FV Found\n"));
  }

  DEBUG ((DEBUG_ERROR, "GetFfsByName - NO FV Found\n"));
  return FALSE;
}

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
  )
{
  VOID        *BiosImage;
  UINTN       BiosImageSize;

  BiosImage     = NULL;
  BiosImageSize = 0;

  //
  // Find out BIOS image within Image first.
  //
  if (ExtractImageByName ((VOID *) Image, ImageSize, &gCapsuleBiosImageFileGuid, &BiosImage, &BiosImageSize)) {
    //
    // BIOS image is found. Further extract compact FvAdvanced in BIOS image.
    //
    return FindFvAdvancedInBiosImage (BiosImage, BiosImageSize, FfsGuid, FvAdvancedImage, FvAdvancedImageSize);
  }

  return FALSE;
}

/**
  Extract config file from input Image and parse the config file.

  @param[in]   Image             The input image.
  @param[in]   ImageSize         The size of input image in bytes.
  @param[in]   ConfigFileGuid    The filename of Config file within Image.
  @param[out]  ConfigHeader      Pointer to parsed Config header.
  @param[out]  ConfigDataArray   Pointer to parsed Config data.

  @retval EFI_SUCCESS      The config file is successfully extracted and parsed.
  @retval EFI_NOT_FOUND    The compacted FvAdvanced is not extracted.

**/
EFI_STATUS
ExtractAndParseConfigImage (
  IN      VOID                          *Image,
  IN      UINTN                         ImageSize,
  IN      EFI_GUID                      *ConfigFileGuid,
  IN OUT  CONFIG_HEADER                 *ConfigHeader,
  IN OUT  UPDATE_CONFIG_DATA            **ConfigDataArray
  )
{
  EFI_STATUS                    Status;
  VOID                          *ConfigImage;
  UINTN                         ConfigImageSize;

  DEBUG ((DEBUG_INFO, "ExtractAndParseConfigImage: entry\n"));

  Status          = EFI_NOT_FOUND;
  ConfigImage     = NULL;
  ConfigImageSize = 0;

  ZeroMem (ConfigHeader, sizeof (CONFIG_HEADER));
  *ConfigDataArray = NULL;

  if (ExtractImageByName (Image, ImageSize, ConfigFileGuid, &ConfigImage, &ConfigImageSize)) {
    Status = ParseUpdateDataFile (
               ConfigImage,
               ConfigImageSize,
               ConfigHeader,
               ConfigDataArray
               );
  } else {
    DEBUG ((DEBUG_ERROR, "Config image file is not found"));
  }

  if (EFI_ERROR (Status) && (*ConfigDataArray != NULL)) {
    FreePool (*ConfigDataArray);
    *ConfigDataArray = NULL;
  }

  DEBUG ((DEBUG_INFO, "ExtractAndParseConfigImage: exit (%r)\n", Status));

  return Status;
}

/**
  Extract update image by config file.

  The input FvImage contains multiple FFS files including config data file
  and update image file. This function extracts and parse config file first,
  then extracts images of FileGuid and HelperFileGuid described in config header.

  @param[in]   FvImage           The input firmware volume image consisted of multiple FFSs.
  @param[in]   FvImageSize       The size of FvImage in bytes.
  @param[in]   ConfigFileGuid    The filename of Config file within FvImage.
  @param[out]  ConfigHeader      Pointer to parsed Config header.
  @param[out]  ConfigDataArray   Pointer to parsed Config data.
  @param[out]  UpdateImage       Pointer to image described by ConfigHeader->FileGuid.
  @param[out]  UpdateImageSize   The size of UpdateImage in bytes.
  @param[out]  HelperImage       Pointer to image described by ConfigHeader->HelperFileGuid. May be NULL.
  @param[out]  HelperImageSize   The size of HelperImage in bytes. May be NULL.

  @retval EFI_SUCCESS      UpdateImage is successfully extracted.
  @retval EFI_NOT_FOUND    UpdateImage is not extracted.

**/
EFI_STATUS
ExtractUpdateImageByConfigFile (
  IN      VOID                          *FvImage,
  IN      UINTN                         FvImageSize,
  IN      EFI_GUID                      *ConfigFileGuid,
  IN OUT  CONFIG_HEADER                 *ConfigHeader,
  IN OUT  UPDATE_CONFIG_DATA            **ConfigDataArray,
  IN OUT  VOID                          **UpdateImage,
  IN OUT  UINTN                         *UpdateImageSize,
  IN OUT  VOID                          **HelperImage,   OPTIONAL
  IN OUT  UINTN                         *HelperImageSize OPTIONAL
  )
{
  EFI_STATUS              Status;
  UINTN                   Index;
  UINTN                   ExpecteSize;

  DEBUG ((DEBUG_INFO, "ExtractUpdateImageByConfigFile: entry\n"));

  if ((ConfigHeader == NULL) || (ConfigDataArray == NULL) || (UpdateImage == NULL) || (UpdateImageSize == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Extract and parse config file
  //
  Status = ExtractAndParseConfigImage (
             FvImage,
             FvImageSize,
             ConfigFileGuid,
             ConfigHeader,
             ConfigDataArray
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to parse config image"));
    return Status;
  }

  //
  // Extract Update image
  //
  if (!ExtractImageByName (FvImage, FvImageSize, &ConfigHeader->FileGuid, UpdateImage, UpdateImageSize)) {
    DEBUG ((DEBUG_ERROR, "Failed to find Update image (%g)", &ConfigHeader->FileGuid));
    Status = EFI_NOT_FOUND;
    goto cleanup;
  }

  //
  // Bundary check
  //
  ExpecteSize = 0;
  for (Index = 0; Index < ConfigHeader->NumOfUpdates; Index++) {
    ExpecteSize = MAX (
                    (*ConfigDataArray)[Index].ImageOffset + (*ConfigDataArray)[Index].Length,
                    ExpecteSize
                    );
  }

  if (*UpdateImageSize < ExpecteSize) {
    //
    // ImageOffset described in Config data exceeds Update image length
    //
    DEBUG ((DEBUG_ERROR, "Update image is smaller than expected"));
    Status = EFI_UNSUPPORTED;
    goto cleanup;
  }

  //
  // Extract Helper image
  //
  if ((HelperImage != NULL) && (HelperImageSize != NULL)) {
    if (ExtractImageByName (FvImage, FvImageSize, &ConfigHeader->HelperFileGuid, HelperImage, HelperImageSize)) {
      //
      // Bundary check
      //
      ExpecteSize = 0;
      for (Index = 0; Index < ConfigHeader->NumOfUpdates; Index++) {
        ExpecteSize = MAX (
                        (*ConfigDataArray)[Index].HelperImageOffset + (*ConfigDataArray)[Index].HelperImageLength,
                        ExpecteSize
                        );
      }
      if (*HelperImageSize < ExpecteSize) {
        //
        // HelperImageOffset described in Config data exceeds Helper image length
        //
        DEBUG ((DEBUG_ERROR, "Helper image is smaller than expected"));
        Status = EFI_UNSUPPORTED;
        goto cleanup;
      }
    } else {
      //
      // Expect a Helper image but fail to extract
      //
      DEBUG ((DEBUG_ERROR, "Helper image is expected but fail to extract"));
      Status = EFI_NOT_FOUND;
      goto cleanup;
    }
  }

cleanup:
  if (EFI_ERROR (Status)) {
    FreePool (*ConfigDataArray);
    *ConfigDataArray = NULL;
    ZeroMem (ConfigHeader, sizeof (CONFIG_HEADER));
  }

  DEBUG ((DEBUG_INFO, "ExtractUpdateImageByConfigFile: exit (%r)\n", Status));
  return Status;
}

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
  )
{
  EFI_STATUS                  Status;
  CONFIG_HEADER               ConfigHeader;
  UPDATE_CONFIG_DATA          *ConfigData;
  VOID                        *BiosImage;
  UINTN                       BiosImageSize;
  VOID                        *BgupImage;
  UINTN                       BgupImageSize;

  ConfigData = NULL;

  //
  // Check if all needed binaries for BIOS update can be extracted from Image
  //
  Status = ExtractUpdateImageByConfigFile (
             Image,
             ImageSize,
             &gCapsuleBiosConfigFileGuid,
             &ConfigHeader,
             &ConfigData,
             &BiosImage,
             &BiosImageSize,
             mBiosGuardEnabled ? &BgupImage : NULL,
             mBiosGuardEnabled ? &BgupImageSize : NULL
             );

  if (ConfigData != NULL) {
    //
    // No need to use ConfigData in this function anymore.
    //
    FreePool (ConfigData);
  }

  if (Status == EFI_SUCCESS) {
    if (CompareGuid (&(ConfigHeader.FileGuid), &gCapsuleBiosImageFileGuid)) {
      DEBUG ((DEBUG_INFO, "IsImageForBiosUpdate: TRUE\n"));
      return TRUE;
    } else {
      DEBUG ((DEBUG_ERROR, "The file indicated in Congfig data is not for BIOS update\n"));
    }
  }

  DEBUG ((DEBUG_ERROR, "IsImageForBiosUpdate: FALSE\n"));
  return FALSE;
}

/**
  Set/Clear TopSwap bit by request. This is used in Non-BiosGuard BIOS update scenerio.

  @param[in]      Enable        TRUE: Set TopSwap bit; FALSE: Clear TopSwap bit.

  @retval EFI_UNSUPPORTED       Current platform does not support the SwSmi functions to access TopSwap bit.
  @retval EFI_SUCCESS           Triggered TopSwap enable/disable SMI by request.

**/
EFI_STATUS
TopSwapControl (
  IN BOOLEAN           Enable
  )
{
  if (mBiosGuardEnabled) {
    //
    // TopSwap will be manipulated in BGUP script
    //
    return EFI_SUCCESS;
  }

  ASSERT (PcdGet8 (PcdTopSwapEnableSwSmi) != 0xFF);
  ASSERT (PcdGet8 (PcdTopSwapDisableSwSmi) != 0xFF);

  if (Enable) {
    DEBUG ((DEBUG_INFO, "Enable TopSwap via SwSmi (0x%x)\n", PcdGet8 (PcdTopSwapEnableSwSmi)));
    IoWrite8 (R_PCH_IO_APM_CNT, PcdGet8 (PcdTopSwapEnableSwSmi));
  } else {
    DEBUG ((DEBUG_INFO, "Disable TopSwap via SwSmi (0x%x)\n", PcdGet8 (PcdTopSwapDisableSwSmi)));
    IoWrite8 (R_PCH_IO_APM_CNT, PcdGet8 (PcdTopSwapDisableSwSmi));
  }

  return EFI_SUCCESS;
}

/**
  Delete SETUP related Variables

  @retval     EFI_SUCCESS.             Operation is successful.

**/
EFI_STATUS
DeleteSetupVariables (
  VOID
  )
{
  EFI_STATUS        Status;
  UINTN             Index;

  DEBUG ((DEBUG_INFO, "Delete Setup User Data\n"));

  for (Index = 0; Index < sizeof (mUserDataVariableList) / sizeof (mUserDataVariableList[0]); Index++) {
     Status = gRT->SetVariable (
                     mUserDataVariableList[Index].Name,
                     mUserDataVariableList[Index].Guid,
                     0,
                     0,
                     NULL
                     );
     if (EFI_ERROR (Status)) {
       DEBUG ((DEBUG_INFO, "Failed to delete variable %s (%r)\n", mUserDataVariableList[Index].Name, mUserDataVariableList[Index].Guid));
     }
  }

  return EFI_SUCCESS;
}

/**
  Clear assigned non-volatile variables after BIOS update.

**/
VOID
ClearBiosNvData (
  VOID
  )
{
  if (mSetupData.SysFwUpdateLoadDefault) {
    DeleteSetupVariables ();
  }

  //
  // Enforce booting with full configuration after flash
  //
  gRT->SetVariable (
         L"BootState",
         &gBootStateGuid,
         0,
         0,
         NULL
         );

  return;
}

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
  )
{
  EFI_STATUS                            Status;
  CONFIG_HEADER                         ConfigHeader;
  UPDATE_CONFIG_DATA                    *ConfigData;
  VOID                                  *BiosImage;
  UINTN                                 BiosImageSize;
  VOID                                  *BgupImage;
  UINTN                                 BgupImageSize;
  UINTN                                 DisplayLength;
  UINTN                                 Index;
  UINTN                                 TotalUpdateSize;
  UINTN                                 BytesWritten;
  EFI_PHYSICAL_ADDRESS                  FlashAddress;
  VOID                                  *UpdateBuffer;
  UINTN                                 UpdateLength;
  VOID                                  *BgupBuffer;
  UINTN                                 BgupBufferLength;

  DEBUG ((DEBUG_INFO, "PerformBiosUpdateByConfigData: entry\n"));

  ConfigData      = NULL;
  BiosImage       = NULL;
  BiosImageSize   = 0;
  BgupImage       = NULL;
  BgupImageSize   = 0;
  BytesWritten    = 0;
  DisplayLength   = EndPercentage - StartPercentage;

  //
  // Extract BIOS image and BGUP image (if BiosGuard is enabled) by parsing Config file.
  //
  Status = ExtractUpdateImageByConfigFile (
             Image,
             ImageSize,
             &gCapsuleBiosConfigFileGuid,
             &ConfigHeader,
             &ConfigData,
             &BiosImage,
             &BiosImageSize,
             mBiosGuardEnabled ? &BgupImage : NULL,
             mBiosGuardEnabled ? &BgupImageSize : NULL
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PerformBiosUpdateByConfigData: Failed to ExtractUpdateImageByConfigFile (%r)\n", Status));
    return Status;
  }

  //
  // Calculate the toltal size to be written
  //
  TotalUpdateSize = 0;
  for (Index = LastUpdatingProgress; Index < ConfigHeader.NumOfUpdates; Index++) {
    TotalUpdateSize += ConfigData[Index].Length;
  }

  for (Index = LastUpdatingProgress; Index < ConfigHeader.NumOfUpdates; Index++) {

    if (BootMediaIsUfs () && (Index == BiosIbbR)) {
      DEBUG ((DEBUG_INFO, "PerformBiosUpdateByConfigData (stage %d): Updating UFS TopSwap Area\n", Index));
      SetUpdateProgress (UpdatingBios, (UINT32) Index);
      UpdateLength = GetUfsTopSwapBlockSize ();
      Status = UpdateUfsTopSwapArea (
                 DisplayProgress,
                 StartPercentage + ((BytesWritten * DisplayLength) / TotalUpdateSize),                           // StartPercentage
                 StartPercentage + (((BytesWritten + UpdateLength) * DisplayLength) / TotalUpdateSize)           // EndPercentage
                 );
    } else {
      DEBUG ((DEBUG_INFO,
        "PerformBiosUpdateByConfigData (stage %d): BaseAddress - 0x%lx ImageOffset - 0x%x Length - 0x%x\n",
        Index,
        ConfigData[Index].BaseAddress,
        ConfigData[Index].ImageOffset,
        ConfigData[Index].Length
        ));

      FlashAddress     = ConfigData[Index].BaseAddress;
      UpdateBuffer     = (VOID *)((UINTN) BiosImage + ConfigData[Index].ImageOffset);
      UpdateLength     = ConfigData[Index].Length;
      BgupBuffer       = (VOID *)((UINTN) BgupImage + ConfigData[Index].HelperImageOffset);
      BgupBufferLength = ConfigData[Index].HelperImageLength;

      if (BootMediaIsUfs ()) {
        if (Index == BiosUfsIbb) {
          TopSwapControl (TRUE);
          UpdateBpdtSignature(Bpdt1, BPDT_SIGN_RED);
        }
      } else {
        if (Index == BiosIbb) {
          TopSwapControl (TRUE);
        }
      }

      SetUpdateProgress (UpdatingBios, (UINT32) Index);
      Status = UpdateBiosFirmware (
                FlashAddress,
                UpdateBuffer,
                UpdateLength,
                mBiosGuardEnabled,
                BgupBuffer,
                BgupBufferLength,
                DisplayProgress,
                StartPercentage + ((BytesWritten * DisplayLength) / TotalUpdateSize),                  // StartPercentage
                StartPercentage + (((BytesWritten + UpdateLength) * DisplayLength) / TotalUpdateSize)  // EndPercentage
                );

      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "UpdateBiosFirmware failed in stage %d (%r)\n", Index, Status));
        break;
      }

      if (BootMediaIsUfs ()) {
        if (Index == BiosUfsBpdt1) {
          TopSwapControl (FALSE);
          UpdateBpdtSignature(Bpdt2, BPDT_SIGN_RED);
        }
      } else {
        if (Index == BiosIbb) {
          TopSwapControl (FALSE);
        }
      }

      BytesWritten += UpdateLength;
    }
  }

  if (Status == EFI_SUCCESS) {
    ClearBiosNvData ();
  }

  if (ConfigData != NULL) {
    FreePool (ConfigData);
  }

  DEBUG ((DEBUG_INFO, "PerformBiosUpdateByConfigData: exit (%r)\n", Status));
  return Status;
}

/**
  The constructor function of BiosUpdateHelperLib.

  @param[in]  ImageHandle   The firmware allocated handle for the EFI image.
  @param[in]  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor successfully .

**/
EFI_STATUS
EFIAPI
BiosUpdateHelpersLibConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINTN              VariableSize;

  mBiosGuardEnabled = IsBiosGuardEnabled ();

  VariableSize = sizeof (SETUP_DATA);
  gRT->GetVariable (
         L"Setup",
         &gSetupVariableGuid,
         NULL,
         &VariableSize,
         &mSetupData
         );

  return EFI_SUCCESS;
}
