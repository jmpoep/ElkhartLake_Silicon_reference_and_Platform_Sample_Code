/** @file
  FSP Wrapper Extract Guided Section Peim Implementation

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#include <Uefi.h>
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcdLib.h>
#include <Ppi/GuidedSectionExtraction.h>
#include <Library/HobLib.h>


/**
  Verify the Guided Section GUID by checking if there is the Guided Section GUID HOB recorded the GUID itself.

  @param GuidedSectionGuid          The Guided Section GUID.
  @param GuidedSectionExtraction    A pointer to the pointer to the supported Guided Section Extraction Ppi
                                    for the Guided Section.

  @return TRUE      The GuidedSectionGuid could be identified, and the pointer to
                    the Guided Section Extraction Ppi will be returned to *GuidedSectionExtraction.
  @return FALSE     The GuidedSectionGuid could not be identified, or
                    the Guided Section Extraction Ppi has not been installed yet.

**/
BOOLEAN
VerifyGuidedSectionGuid (
  IN  EFI_GUID                                  *GuidedSectionGuid,
  OUT EFI_PEI_GUIDED_SECTION_EXTRACTION_PPI     **GuidedSectionExtraction
  )
{
  EFI_PEI_HOB_POINTERS  Hob;
  EFI_GUID              *GuidRecorded;
  VOID                  *Interface;
  EFI_STATUS            Status;

  //
  // Check if there is the Guided Section GUID HOB recorded the GUID itself.
  //
  Hob.Raw = GetFirstGuidHob (GuidedSectionGuid);
  if (Hob.Raw != NULL) {
    GuidRecorded = (EFI_GUID *) GET_GUID_HOB_DATA (Hob);
    if (CompareGuid (GuidRecorded, GuidedSectionGuid)) {
      //
      // Found the recorded GuidedSectionGuid.
      //
      Status = PeiServicesLocatePpi (GuidedSectionGuid, 0, NULL, (VOID **) &Interface);
      if (!EFI_ERROR (Status) && Interface != NULL) {
        //
        // Found the supported Guided Section Extraction Ppi for the Guided Section.
        //
        *GuidedSectionExtraction = (EFI_PEI_GUIDED_SECTION_EXTRACTION_PPI *) Interface;
        return TRUE;
      }
      return FALSE;
    }
  }

  return FALSE;
}


/**
  The Entry point of the FSP Wrapper Extract Guided Section

  @param[in]  FileHandle   Pointer to image file handle
  @param[in]  PeiServices  Pointer to PEI Services Table

  @return     EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
FspWrapperExtractGuidedSectionEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_COMMON_SECTION_HEADER               *Section = NULL;
  EFI_PEI_GUIDED_SECTION_EXTRACTION_PPI   *GuidSectionPpi;
  EFI_STATUS                              Status;
  VOID                                    *OutputBuffer = NULL;
  UINT32                                  OutputBufferSize;
  UINT32                                  AuthenticationStatus;
  EFI_GUID                                *SectionDefinitionGuid;
  UINT16                                  SectionAttribute;
  UINT32                                  BaseAddress;

  DEBUG ((DEBUG_INFO, "Entered FspExtractGuidedSectionEntry\n"));

  // Add FV_HEADER Length + FFS_HEADER_LENGTH along with the FV FSP Base address to determine section start
  Section = (EFI_COMMON_SECTION_HEADER *) (PcdGet32 (PcdFlashFvFspSBase) + 0x60);

  if (Section->Type != EFI_SECTION_GUID_DEFINED) {
    DEBUG ((DEBUG_INFO, "Exit FspExtractGuidedSectionEntry - Not Guided Section 0x%x\n", Section->Type));
    return EFI_INVALID_PARAMETER;
  }
  if (IS_SECTION2 (Section)) {
    SectionDefinitionGuid   = &((EFI_GUID_DEFINED_SECTION2 *)Section)->SectionDefinitionGuid;
    SectionAttribute        = ((EFI_GUID_DEFINED_SECTION2 *) Section)->Attributes;
  } else {
    SectionDefinitionGuid   = &((EFI_GUID_DEFINED_SECTION *)Section)->SectionDefinitionGuid;
    SectionAttribute        = ((EFI_GUID_DEFINED_SECTION *) Section)->Attributes;
  }
  if (!VerifyGuidedSectionGuid (SectionDefinitionGuid, &GuidSectionPpi)) {
    DEBUG ((DEBUG_INFO, "Exit FspExtractGuidedSectionEntry - Unable to get the Extraction Ppi for SectionGuid %g\n", SectionDefinitionGuid));
    return EFI_SECURITY_VIOLATION;
  }

  Status = GuidSectionPpi->ExtractSection (
                               GuidSectionPpi,
                               Section,
                               &OutputBuffer,
                               &OutputBufferSize,
                               &AuthenticationStatus
                               );

  if ((Status == EFI_SUCCESS) && (AuthenticationStatus == EFI_AUTH_STATUS_IMAGE_SIGNED)) {
    BaseAddress = ((((UINT32) OutputBuffer) + 0x10)& ~0xF);
    PcdSetEx32S (&gIntelFsp2WrapperTokenSpaceGuid, PcdFspsBaseAddress, BaseAddress);
    if (SectionAttribute & EFI_GUIDED_SECTION_PROCESSING_REQUIRED) {
      *(UINT32 *) (BaseAddress + 0xB0) = BaseAddress;    // Set  FSP-S Image Base Address (Offset 0xB0 calculated as FD/FV/FSP Header->ImageBase)
    }
    DEBUG ((DEBUG_INFO, "Signed Verification of FSP-S FV Passed and FSP-S Base Address set to 0x%x\n", BaseAddress));
  } else {
    ///
    /// Set PcdFspsBaseAddress to 0, if verification failed, so that FspsWrapperPeim won't be able to make FSP Silicon Init API Call.
    ///
    PcdSetEx32S (&gIntelFsp2WrapperTokenSpaceGuid, PcdFspsBaseAddress, 0);
    DEBUG ((DEBUG_ERROR, "Signed Verification of FSP-S FV Failed Status:0x%x, AuthenticationStatus:0x%x\n", Status, AuthenticationStatus));
  }
  DEBUG ((DEBUG_INFO, "Exit FspExtractGuidedSectionEntry - SectionGuid - %g, SectionAttribute - 0x%x\n", SectionDefinitionGuid, SectionAttribute));

  return EFI_SUCCESS;
}
