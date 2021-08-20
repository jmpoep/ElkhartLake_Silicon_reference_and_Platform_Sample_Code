/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#include <PiPei.h>
#include <BiosInfo.h>
#include <Guid/FirmwareContentsSigned.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#define GET_OCCUPIED_SIZE(ActualSize, Alignment) \
  ((ActualSize) + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1)))
#define FIT_TABLE_TYPE_BIOS_MODULE    7

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
  Return if this FFS has single signed section.

  @param[in] FileBuffer
  @param[in] FileBufferSize

  @retval    TRUE            Single signed section found.
  @retval    FALSE           Duplicate or unsigned section found
**/
BOOLEAN
HasSingleSignedSection (
  IN VOID                  *FileBuffer,
  IN UINT32                FileBufferSize
  )
{
  EFI_COMMON_SECTION_HEADER             *SectionHeader;
  UINTN                                 SectionSize;
  BOOLEAN                               FindSignSection;

  DEBUG ((DEBUG_INFO, "HasSingleSignedSection - FFS: 0x%08x - 0x%08x\n", FileBuffer, FileBufferSize));

  //
  // Find Section
  //
  if (IS_FFS_FILE2(FileBuffer)) {
    SectionHeader = (EFI_COMMON_SECTION_HEADER *)((UINTN)FileBuffer + sizeof(EFI_FFS_FILE_HEADER2));
    DEBUG ((DEBUG_INFO, " Guid      = 0x%g\n", &((EFI_GUID_DEFINED_SECTION2 *)SectionHeader)->SectionDefinitionGuid));
    DEBUG ((DEBUG_INFO, " DataOfset = 0x%X\n", ((EFI_GUID_DEFINED_SECTION2 *)SectionHeader)->DataOffset));
  } else {
    SectionHeader = (EFI_COMMON_SECTION_HEADER *)((UINTN)FileBuffer + sizeof(EFI_FFS_FILE_HEADER));
    DEBUG ((DEBUG_INFO, " Guid      = 0x%g\n", &((EFI_GUID_DEFINED_SECTION *)SectionHeader)->SectionDefinitionGuid));
    DEBUG ((DEBUG_INFO, " DataOfset = 0x%X\n", ((EFI_GUID_DEFINED_SECTION *)SectionHeader)->DataOffset));
  }
  SectionHeader = (EFI_COMMON_SECTION_HEADER *)ALIGN_POINTER(SectionHeader, 4);

  FindSignSection = FALSE;
  while ((UINTN)SectionHeader < (UINTN)FileBuffer + FileBufferSize) {
    DEBUG ((DEBUG_INFO, "HasSingleSignedSection - Section: 0x%08x\n", SectionHeader));
    if (IS_SECTION2(SectionHeader)) {
      SectionSize = SECTION2_SIZE(SectionHeader);
    } else {
      SectionSize = SECTION_SIZE(SectionHeader);
    }
    SectionSize = GET_OCCUPIED_SIZE (SectionSize, 4);
    DEBUG ((DEBUG_INFO, " Size      = 0x%X\n", SectionSize));
    DEBUG ((DEBUG_INFO, " Type      = 0x%X\n", SectionHeader->Type));

    //
    // Do not allow duplicated Section
    //
    if (FindSignSection) {
      DEBUG ((DEBUG_ERROR, "HasSingleSignedSection - duplicated Section\n"));
      return FALSE;
    }

    if ((SectionHeader->Type == EFI_SECTION_GUID_DEFINED) &&
        ((((EFI_GUID_DEFINED_SECTION *)SectionHeader)->Attributes & (EFI_GUIDED_SECTION_AUTH_STATUS_VALID | EFI_GUIDED_SECTION_PROCESSING_REQUIRED)) != 0) &&
        (CompareGuid (&((EFI_GUID_DEFINED_SECTION *)SectionHeader)->SectionDefinitionGuid, &gEfiCertTypeRsa2048Sha256Guid))) {
      //
      // record it
      //
      FindSignSection = TRUE;
    } else {
      //
      // Any unsigned section is not allowed
      //
      if (SectionHeader->Type != EFI_SECTION_GUID_DEFINED) {
        DEBUG ((DEBUG_ERROR, "HasSingleSignedSection - invalid section type %x\n", SectionHeader->Type));
      } else {
        DEBUG ((DEBUG_ERROR, "HasSingleSignedSection - invalid section GUID %g\n", &((EFI_GUID_DEFINED_SECTION *)SectionHeader)->SectionDefinitionGuid));
      }
      return FALSE;
    }

    //
    // Next Section
    //
    SectionHeader = (EFI_COMMON_SECTION_HEADER *)((UINTN)SectionHeader + SectionSize);
  }

  return FindSignSection;
}

/**
  Return if this FV has single signed FFS.

  @param[in] FvStart
  @param[in] FvSize

  @retval    TRUE    Single signed section found.
  @retval    FALSE   Duplicate or no signed section found.
**/
BOOLEAN
HasSingleSignedFile (
  IN VOID                  *FvStart,
  IN UINT64                FvSize
  )
{
  EFI_FIRMWARE_VOLUME_HEADER                *FvHeader;
  EFI_FIRMWARE_VOLUME_EXT_HEADER            *FvExtHeader;
  EFI_FFS_FILE_HEADER                       *FfsHeader;
  UINTN                                     FfsSize;
  BOOLEAN                                   FindSignFile;
  UINTN                                     TestLength;

  DEBUG ((DEBUG_INFO, "HasSingleSignedFile - FV: 0x%08x - 0x%08x\n", (UINTN)FvStart, (UINTN)FvSize));

  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FvStart;
  //
  // FvHeader
  //
  DEBUG ((DEBUG_INFO, " FileSystemGuid = 0x%g\n", &FvHeader->FileSystemGuid));
  DEBUG ((DEBUG_INFO, " FvLength       = 0x%X\n", FvHeader->FvLength));
  DEBUG ((DEBUG_INFO, " FvHeader Size  = 0x%X\n", FvHeader->HeaderLength));

  if (FvHeader->FvLength != FvSize) {
    DEBUG ((DEBUG_ERROR, "HasSingleSignedFile - FvSize: 0x%08x, expect - 0x%08x\n", (UINTN)FvHeader->FvLength, (UINTN)FvSize));
    return FALSE;
  }

  //
  // Find FFS
  //
  if (FvHeader->ExtHeaderOffset != 0) {
    FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8 *)FvHeader + FvHeader->ExtHeaderOffset);
    FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvExtHeader + FvExtHeader->ExtHeaderSize);
  } else {
    FfsHeader = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvHeader + FvHeader->HeaderLength);
  }
  FfsHeader = (EFI_FFS_FILE_HEADER *)ALIGN_POINTER(FfsHeader, 8);

  FindSignFile = FALSE;
  while ((UINTN)FfsHeader < (UINTN)FvStart + FvSize) {
    DEBUG ((DEBUG_INFO, "HasSingleSignedFile - FFS: 0x%08x\n", FfsHeader));
    DEBUG ((DEBUG_INFO, " Name = 0x%g\n", &FfsHeader->Name));
    DEBUG ((DEBUG_INFO, " Type = 0x%X\n", FfsHeader->Type));

    TestLength = (UINTN)((UINTN)FvStart + FvSize - (UINTN)FfsHeader);
    if (TestLength > sizeof (EFI_FFS_FILE_HEADER)) {
      TestLength = sizeof (EFI_FFS_FILE_HEADER);
    }
    if (IsBufferErased (1, FfsHeader, TestLength)) {
      break;
    }

    //
    // Do not allow duplicated FFS
    //
    if (FindSignFile) {
      DEBUG ((DEBUG_ERROR, "HasSingleSignedFile - duplicated FFS\n"));
      return FALSE;
    }

    if (IS_FFS_FILE2 (FfsHeader)) {
      FfsSize = FFS_FILE2_SIZE(FfsHeader);
    } else {
      FfsSize = FFS_FILE_SIZE(FfsHeader);
    }

    if (FfsHeader->Type == EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE) {
      //
      // Check section
      //
      FindSignFile = HasSingleSignedSection (FfsHeader, FfsSize);
      if (FindSignFile == FALSE) {
        DEBUG ((DEBUG_ERROR, "HasSingleSignedFile - HasSingleSignedSection Failed\n"));
        return FALSE;
      }
    } else {
      //
      // Any other type is not allowed
      //
      DEBUG ((DEBUG_ERROR, "HasSingleSignedFile - invalid FFS type %x\n", FfsHeader->Type));
      return FALSE;
    }

    //
    // Next File
    //
    FfsHeader = (EFI_FFS_FILE_HEADER *) ALIGN_POINTER ((UINTN)FfsHeader + FfsSize, 8);
  }

  return FindSignFile;
}

/**

  @param[in] BiosInfoHeader

  @retval    TRUE            POST Ibb is signed
  @retval    FALSE           POST Ibb is not signed
**/
BOOLEAN
IsPostIbbSigned (
  IN BIOS_INFO_HEADER       *BiosInfoHeader
  )
{
  BOOLEAN                FinalResult;
  BOOLEAN                Result;
  BIOS_INFO_STRUCT       *BiosInfoStruct;
  UINTN                  Index;

  DEBUG ((DEBUG_INFO, "IsPostIbbSigned Entry\n"));

  FinalResult = TRUE;
  BiosInfoStruct = (BIOS_INFO_STRUCT *)(BiosInfoHeader + 1);
  for (Index = 0; Index < BiosInfoHeader->EntryCount; Index++) {
    if (BiosInfoStruct[Index].Type != FIT_TABLE_TYPE_BIOS_MODULE) {
      continue;
    }
    if ((BiosInfoStruct[Index].Attributes & BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB) != 0) {
      Result = HasSingleSignedFile ((VOID *)(UINTN)BiosInfoStruct[Index].Address, BiosInfoStruct[Index].Size);
      if (!Result) {
        FinalResult = FALSE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "IsPostIbbSigned Exit\n"));
  return FinalResult;
}

/**
  Checks BiosInfo Ppi.

  @param[in] FileHandle  Handle of the file being invoked.
  @param[in] PeiServices Describes the list of possible PEI Services.

  @retval    EFI_SUCCESS Boot mode is S3, Recovery or Post Ibb is verified signed
  @retval    FALSE       Failed to locate gBiosInfoGuid Ppi
  @retval    None        May enter CpuDeadLoop() if Post Ibb is not signed
**/
EFI_STATUS
EFIAPI
BiosInfoCheckerEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS             Status;
  BIOS_INFO_HEADER       *BiosInfoHeader;
  BOOLEAN                Result;
  EFI_BOOT_MODE          BootMode;

  DEBUG ((DEBUG_INFO, "BiosInfoCheckerEntryPoint Entry\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode == BOOT_ON_S3_RESUME) {
    // Do not check S3, because we do not run DxeFv.
    DEBUG ((DEBUG_INFO, "BiosInfoChecker skipped in S3 resume boot path\n"));
    return EFI_SUCCESS;
  }
  if (BootMode == BOOT_IN_RECOVERY_MODE) {
    // Do not check RECOVERY, because we do not trust flash region.
    DEBUG ((DEBUG_INFO, "BiosInfoChecker skipped in Recovery boot path\n"));
    return EFI_SUCCESS;
  }
  Status = PeiServicesLocatePpi (
             &gBiosInfoGuid,
             0,
             NULL,
             (VOID **)&BiosInfoHeader
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "BiosInfoChecker skipped due to BioInfo PPI not found\n"));
    return EFI_NOT_FOUND;
  }

  //
  // EnforcePolicy
  //
  if (PcdGetBool (PcdPostIbbVerificationEnable)) {
    Result = IsPostIbbSigned (BiosInfoHeader);
    if (!Result) {
      //
      // TBD: Need set recovery mode? or just reset system?
      // Or check VerifiedBoot/MeasuredBoot policy?
      //
      ASSERT (FALSE);
      CpuDeadLoop ();
    }
  } else {
    DEBUG ((DEBUG_INFO, "Warning: BiosInfoChecker skipped.\n"));
  }

  DEBUG ((DEBUG_INFO, "BiosInfoCheckerEntryPoint Exit\n"));
  return EFI_SUCCESS;
}
