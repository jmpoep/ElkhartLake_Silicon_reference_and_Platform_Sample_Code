/** @file

  This library registers CRC32 guided section handler 
  to parse CRC32 encapsulation section and extract raw data.
  It uses UEFI boot service CalculateCrc32 to authenticate 32 bit CRC value.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2016 Intel Corporation.

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
#include <Ppi/ReadOnlyVariable2.h>
#include <Guid/FirmwareContentsSigned.h>
#include <Library/ExtractGuidedSectionLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/MemoryAllocationLib.h>

VOID
DumpHex (
  IN UINT8 *Buffer,
  IN UINTN BufferSize
  )
{
  UINTN  Index;
  UINTN  IndexJ;
#define COL_SIZE  16

  for (Index = 0; Index < BufferSize/COL_SIZE; Index++) {
    DEBUG ((DEBUG_ERROR, "      %04x: ", Index * COL_SIZE));
    for (IndexJ = 0; IndexJ < COL_SIZE; IndexJ++) {
      DEBUG ((DEBUG_ERROR, "%02x ", *(Buffer + Index * COL_SIZE + IndexJ)));
    }
    DEBUG ((DEBUG_ERROR, "\n"));
  }
  if ((BufferSize % COL_SIZE) != 0) {
    DEBUG ((DEBUG_ERROR, "      %04x: ", Index * COL_SIZE));
    for (IndexJ = 0; IndexJ < (BufferSize % COL_SIZE); IndexJ++) {
      DEBUG ((DEBUG_ERROR, "%02x ", *(Buffer + Index * COL_SIZE + IndexJ)));
    }
    DEBUG ((DEBUG_ERROR, "\n"));
  }
}

VOID
CreateHash (
  IN  UINT8     *Data,
  OUT UINT8     *Hash,
  IN  UINTN     Size
  )
{
  UINTN                           CtxSize;
  VOID                            *HashCtx;

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);
  Sha256Init (HashCtx);
  Sha256Update (HashCtx, Data, Size);
  Sha256Final (HashCtx, Hash);
}

UINTN
GetSectionSize (
  IN  EFI_SECTION_TYPE              SectionType,
  IN  VOID                          *Data
  )
{
  UINT32                     SectionSize;
  UINTN                      SectionHeaderSize;
  EFI_COMMON_SECTION_HEADER  *SectionData;

  SectionHeaderSize = sizeof (EFI_COMMON_SECTION_HEADER);
  SectionData = (EFI_COMMON_SECTION_HEADER *)((UINT8 *)Data - SectionHeaderSize);
  if (SectionData->Type != SectionType) {
    SectionHeaderSize = sizeof (EFI_COMMON_SECTION_HEADER2);
    SectionData = (EFI_COMMON_SECTION_HEADER *)((UINT8 *)Data - SectionHeaderSize);
  }
  ASSERT (SectionData->Type == SectionType);
  if (IS_SECTION2(SectionData)) {
    SectionSize = SECTION2_SIZE(SectionData);
  } else {
    SectionSize = SECTION_SIZE(SectionData);
  }
  return SectionSize - SectionHeaderSize;
}

/**
  Searches all the available firmware volumes and returns the first matching FFS section. 

  This function searches all the firmware volumes for FFS files with an FFS filename specified by NameGuid.  
  The order in which the firmware volumes are searched is not deterministic. For each FFS file found, a search 
  is made for FFS sections of type SectionType. If the FFS file contains at least SectionInstance instances 
  of the FFS section specified by SectionType, then the SectionInstance instance is returned in Buffer. 
  Buffer is allocated using AllocatePool(), and the size of the allocated buffer is returned in Size. 

  If SectionType is EFI_SECTION_TE, and the search with an FFS file fails, 
  the search will be retried with a section type of EFI_SECTION_PE32.

  If NameGuid is NULL, then ASSERT().
  If Buffer is NULL, then ASSERT().
  If Size is NULL, then ASSERT().


  @param  NameGuid             A pointer to to the FFS filename GUID to search for  
                               within any of the firmware volumes in the platform. 
  @param  SectionType          Indicates the FFS section type to search for within 
                               the FFS file specified by NameGuid.
  @param  SectionInstance      Indicates which section instance within the FFS file 
                               specified by NameGuid to retrieve.
  @param  Buffer               On output, a pointer to a buffer 
                               containing the FFS file section that was found.  
  @param  Size                 On output, a pointer to the size, in bytes, of Buffer.

  @retval  EFI_SUCCESS          The specified FFS section was returned.
  @retval  EFI_NOT_FOUND        The specified FFS section could not be found.
  @retval  EFI_OUT_OF_RESOURCES There are not enough resources available to retrieve 
                                the matching FFS section.
  @retval  EFI_DEVICE_ERROR     The FFS section could not be retrieves due to a 
                                device error.
  @retval  EFI_ACCESS_DENIED    The FFS section could not be retrieves because the 
                                firmware volume that contains the matching FFS 
                                section does not allow reads.
**/
EFI_STATUS
EFIAPI
GetSectionFromAnyFv  (
  IN  CONST EFI_GUID                *NameGuid,
  IN  EFI_SECTION_TYPE              SectionType,
  IN  UINTN                         SectionInstance,
  OUT VOID                          **Buffer,
  OUT UINTN                         *Size
  )
{
  EFI_STATUS                 Status;
  UINTN                      FvIndex;
  EFI_PEI_FV_HANDLE          VolumeHandle;
  EFI_PEI_FILE_HANDLE        FileHandle;
  EFI_COMMON_SECTION_HEADER  *SectionData;

  //
  // Search all FV
  //
  VolumeHandle = NULL;
  for (FvIndex = 0; ; FvIndex++) {
    Status = PeiServicesFfsFindNextVolume (FvIndex, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      break;
    }
    //
    // Search PEIM FFS
    //
    FileHandle = NULL;
    Status = PeiServicesFfsFindFileByName (NameGuid, VolumeHandle, &FileHandle);
    if (EFI_ERROR (Status)) {
      continue;
    }
    //
    // Search Section
    //
    SectionData = NULL;
    Status = PeiServicesFfsFindSectionData (SectionType, FileHandle, Buffer);
    if (EFI_ERROR (Status)) {
      continue;
    }
    //
    // Great!
    //
    *Size = GetSectionSize (SectionType, *Buffer);
    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

EFI_STATUS
GetFfsFromAnyFv (
  IN  CONST EFI_GUID                *NameGuid,
  OUT VOID                          **Buffer,
  OUT UINTN                         *Size
  )
{
  EFI_STATUS                 Status;
  UINTN                      FvIndex;
  EFI_PEI_FV_HANDLE          VolumeHandle;
  EFI_PEI_FILE_HANDLE        FileHandle;
  EFI_FV_FILE_INFO           FileInfo;

  //
  // Search all FV
  //
  VolumeHandle = NULL;
  for (FvIndex = 0; ; FvIndex++) {
    Status = PeiServicesFfsFindNextVolume (FvIndex, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      break;
    }
    //
    // Search PEIM FFS
    //
    FileHandle = NULL;
    Status = PeiServicesFfsFindFileByName (NameGuid, VolumeHandle, &FileHandle);
    if (EFI_ERROR (Status)) {
      continue;
    }
    Status = PeiServicesFfsGetFileInfo (FileHandle, &FileInfo);
    if (EFI_ERROR (Status)) {
      continue;
    }
    //
    // Great!
    //
    *Buffer = FileInfo.Buffer;
    *Size = (UINTN)FileInfo.BufferSize;
    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

EFI_STATUS
GetPubKeyHash (
  OUT UINT8      **PubKeyHash,
  OUT UINTN      *PubKeyHashLength
  )
{
  EFI_STATUS  Status;

  //
  // Step 1: Check standalone FFS
  //
  Status = GetFfsFromAnyFv (
             &gPubkeyFfsGuid,
             (VOID **) PubKeyHash,
             PubKeyHashLength
             );
  if (!EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }
  //
  // Step 2: Check RAW section in this FFS
  //
  Status = GetSectionFromAnyFv (
             &gEfiCallerIdGuid,
             EFI_SECTION_RAW,
             0,
             (VOID **) PubKeyHash,
             PubKeyHashLength
             );
  if (!EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

VOID
BuildPubKeyHashHob (
  IN UINT8      *PubKeyHash,
  IN UINTN      PubKeyHashLength
  )
{
  VOID                   *HobData;
  EFI_HOB_GUID_TYPE      *GuidHob;

  GuidHob = GetFirstGuidHob (&gPubkeyFfsGuid);
  if (GuidHob != NULL) {
    //
    // Already Done
    //
    return ;
  }

  //
  // Build hob, so that DXE module can also get the data.
  //
  HobData = BuildGuidHob (&gPubkeyFfsGuid, PubKeyHashLength);
  ASSERT (HobData != NULL);
  if (HobData == NULL) {
    return ;
  }
  CopyMem (HobData, PubKeyHash, PubKeyHashLength);
}

/**

  GetInfo gets raw data size and attribute of the input guided section.
  It first checks whether the input guid section is supported. 
  If not, EFI_INVALID_PARAMETER will return.

  @param InputSection       Buffer containing the input GUIDed section to be processed.
  @param OutputBufferSize   The size of OutputBuffer.
  @param ScratchBufferSize  The size of ScratchBuffer.
  @param SectionAttribute   The attribute of the input guided section.

  @retval EFI_SUCCESS            The size of destination buffer, the size of scratch buffer and 
                                 the attribute of the input section are successull retrieved.
  @retval EFI_INVALID_PARAMETER  The GUID in InputSection does not match this instance guid.

**/
EFI_STATUS
EFIAPI
SignedSectionGetInfo (
  IN  CONST VOID  *InputSection,
  OUT UINT32      *OutputBufferSize,
  OUT UINT32      *ScratchBufferSize,
  OUT UINT16      *SectionAttribute
  )
{
  WIN_CERTIFICATE_UEFI_GUID *WinCert;

  if (IS_SECTION2 (InputSection)) {
    //
    // Check whether the input guid section is recognized.
    //
    if (!CompareGuid (
        &gEfiFirmwareContentsSignedGuid,
        &(((EFI_GUID_DEFINED_SECTION2 *) InputSection)->SectionDefinitionGuid))) {
      return EFI_INVALID_PARAMETER;
    }

    WinCert = (WIN_CERTIFICATE_UEFI_GUID *)((UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION2));
    //
    // Retrieve the size and attribute of the input section data.
    //
    *SectionAttribute  = ((EFI_GUID_DEFINED_SECTION2 *) InputSection)->Attributes;
    *ScratchBufferSize = 0;
    *OutputBufferSize  = SECTION2_SIZE (InputSection) - sizeof(EFI_GUID_DEFINED_SECTION2) - WinCert->Hdr.dwLength;
  } else {
    //
    // Check whether the input guid section is recognized.
    //
    if (!CompareGuid (
        &gEfiFirmwareContentsSignedGuid,
        &(((EFI_GUID_DEFINED_SECTION *) InputSection)->SectionDefinitionGuid))) {
      return EFI_INVALID_PARAMETER;
    }

    WinCert = (WIN_CERTIFICATE_UEFI_GUID *)((UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION));
    //
    // Retrieve the size and attribute of the input section data.
    //
    *SectionAttribute  = ((EFI_GUID_DEFINED_SECTION *) InputSection)->Attributes;
    *ScratchBufferSize = 0;
    *OutputBufferSize  = SECTION_SIZE (InputSection) - sizeof(EFI_GUID_DEFINED_SECTION) - WinCert->Hdr.dwLength;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
VerifyRsa2048Sha256Signature (
  IN  EFI_CERT_BLOCK_RSA_2048_SHA256   *Rsa2048Sha256,
  IN  UINT8                            *DataBuffer,
  IN  UINTN                            DataBufferSize,
  OUT UINT32                           *AuthenticationStatus
  )
{
  VOID                            *RsaContext;
  UINT8                           Exponent[] = {0x1, 0x0, 0x1};
  UINT8                           MessageHash[SHA256_DIGEST_SIZE];
  UINT8                           Signature[256];
  UINT8                           *PubKeyHash;
  UINTN                           PubKeyHashLength;
  EFI_STATUS                      Status;
  BOOLEAN                         BStatus;

  //
  // Step 0: Validate PublicKey
  //
  CreateHash (Rsa2048Sha256->PublicKey, MessageHash, sizeof(Rsa2048Sha256->PublicKey));

  Status = GetPubKeyHash (&PubKeyHash, &PubKeyHashLength);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - GetPubKeyHash - %r\n", Status));
    *AuthenticationStatus |= EFI_AUTH_STATUS_NOT_TESTED;
     return EFI_SECURITY_VIOLATION;
  } else {
    DEBUG_CODE (
      DEBUG ((DEBUG_ERROR, "PubKeyHash:\n"));
      DumpHex (PubKeyHash, PubKeyHashLength);
      DEBUG ((DEBUG_ERROR, "MessageHash:\n"));
      DumpHex (MessageHash, sizeof(MessageHash));
    );
    if ((PubKeyHashLength != sizeof(MessageHash)) || (CompareMem (PubKeyHash, MessageHash, sizeof(MessageHash)) != 0)) {
      DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - PubKey Validation FAIL\n"));
      *AuthenticationStatus |= EFI_AUTH_STATUS_NOT_TESTED;
      return EFI_SECURITY_VIOLATION;
    }
  }
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - PubKey Validation PASS\n"));

  //
  // Step 1.1: Create Hash for Section data
  //
  CreateHash (DataBuffer, MessageHash, DataBufferSize);

  //
  // Step 1.2: Do PKCS1 verification
  //
  RsaContext = RsaNew ();
  RsaSetKey (RsaContext, RsaKeyN, Rsa2048Sha256->PublicKey, sizeof(Rsa2048Sha256->PublicKey));
  RsaSetKey (RsaContext, RsaKeyE, Exponent, sizeof(Exponent));

  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - RsaPkcs1Verify ... \n"));
  //
  // BUGBUG: Use local variable, because RsaPkcs1Verify will reuse the signature buffer to hold data.
  //
  CopyMem (Signature, Rsa2048Sha256->Signature, sizeof(Rsa2048Sha256->Signature));
  BStatus = RsaPkcs1Verify (
              RsaContext,
              MessageHash,
              SHA256_DIGEST_SIZE,
              Signature,
              sizeof(Signature)
              );

  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - RsaPkcs1Verify - %x\n", BStatus));
  RsaFree (RsaContext);
  if (!BStatus) {
    //
    // Signature invalid.
    //
    *AuthenticationStatus |= EFI_AUTH_STATUS_TEST_FAILED;
    return EFI_SECURITY_VIOLATION;
  } else {
    BuildPubKeyHashHob (PubKeyHash, PubKeyHashLength);
    return EFI_SUCCESS;
  }
}

/**

  Extraction handler tries to extract raw data from the input guided section.
  It also does authentication check for 32bit CRC value in the input guided section.
  It first checks whether the input guid section is supported. 
  If not, EFI_INVALID_PARAMETER will return.

  @param InputSection    Buffer containing the input GUIDed section to be processed.
  @param OutputBuffer    Buffer to contain the output raw data allocated by the caller.
  @param ScratchBuffer   A pointer to a caller-allocated buffer for function internal use.
  @param AuthenticationStatus A pointer to a caller-allocated UINT32 that indicates the
                              authentication status of the output buffer.

  @retval EFI_SUCCESS            Section Data and Auth Status is extracted successfully.
  @retval EFI_INVALID_PARAMETER  The GUID in InputSection does not match this instance guid.

**/
EFI_STATUS
EFIAPI
SignedSectionHandler (
  IN CONST  VOID    *InputSection,
  OUT       VOID    **OutputBuffer,
  IN        VOID    *ScratchBuffer,        OPTIONAL
  OUT       UINT32  *AuthenticationStatus
  )
{
  UINT32                    OutputBufferSize;
  UINT8                     *SignedData;
  UINT32                    SignedDataSize;
  WIN_CERTIFICATE_UEFI_GUID *WinCert;
  EFI_STATUS                Status;

  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - Enter\n"));
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - InputSection - %x\n", InputSection));

  if (IS_SECTION2 (InputSection)) {
    //
    // Check whether the input guid section is recognized.
    //
    if (!CompareGuid (
        &gEfiFirmwareContentsSignedGuid,
        &(((EFI_GUID_DEFINED_SECTION2 *) InputSection)->SectionDefinitionGuid))) {
      return EFI_INVALID_PARAMETER;
    }

    WinCert = (WIN_CERTIFICATE_UEFI_GUID *)((UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION2));
  
    *OutputBuffer      = (UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION2) + WinCert->Hdr.dwLength;
    OutputBufferSize   = SECTION2_SIZE (InputSection) - sizeof(EFI_GUID_DEFINED_SECTION2) - WinCert->Hdr.dwLength;
    SignedData         = (UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION2) + sizeof(WinCert->Hdr) +  sizeof(WinCert->CertType);
    SignedDataSize     = WinCert->Hdr.dwLength - (sizeof(WinCert->Hdr) +  sizeof(WinCert->CertType));

    //ASSERT (((EFI_GUID_DEFINED_SECTION2 *) InputSection)->Attributes & EFI_GUIDED_SECTION_AUTH_STATUS_VALID);
    *AuthenticationStatus = EFI_AUTH_STATUS_IMAGE_SIGNED;
  } else {
    //
    // Check whether the input guid section is recognized.
    //
    if (!CompareGuid (
        &gEfiFirmwareContentsSignedGuid,
        &(((EFI_GUID_DEFINED_SECTION *) InputSection)->SectionDefinitionGuid))) {

      DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - Guid Mismatch\n"));
      return EFI_INVALID_PARAMETER;
    }

    WinCert = (WIN_CERTIFICATE_UEFI_GUID *)((UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION));
  
    *OutputBuffer      = (UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION) + WinCert->Hdr.dwLength;
    OutputBufferSize   = SECTION_SIZE (InputSection) - sizeof(EFI_GUID_DEFINED_SECTION) - WinCert->Hdr.dwLength;
    SignedData         = (UINT8 *) InputSection + sizeof(EFI_GUID_DEFINED_SECTION) + sizeof(WinCert->Hdr) +  sizeof(WinCert->CertType);
    SignedDataSize     = WinCert->Hdr.dwLength - (sizeof(WinCert->Hdr) +  sizeof(WinCert->CertType));

    //ASSERT (((EFI_GUID_DEFINED_SECTION *) InputSection)->Attributes & EFI_GUIDED_SECTION_AUTH_STATUS_VALID);
    *AuthenticationStatus = EFI_AUTH_STATUS_IMAGE_SIGNED;
  }
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - OutputBuffer - %x\n", *OutputBuffer));
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - OutputBufferSize - %x\n", OutputBufferSize));
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - SignedData - %x\n", SignedData));
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - SignedDataSize - %x\n", SignedDataSize));

  if (PcdGetBool (PcdPostIbbVerificationEnable)) {
  //
  // Validate SignedSection
  //
  Status = VerifyRsa2048Sha256Signature ((EFI_CERT_BLOCK_RSA_2048_SHA256 *)SignedData, *OutputBuffer, OutputBufferSize, AuthenticationStatus);

  DEBUG ((DEBUG_ERROR, "AuthenticationStatus - 0x%08x\n", *AuthenticationStatus));
  DEBUG ((DEBUG_ERROR, "PeiSignedSectionHandler - Exit\n"));

  //
  // BUGBUG: PeiCore does not handle AuthenticationStatus now, so use return status to indicate error.
  //
  return Status;
  } else {
    return EFI_SUCCESS;
  }
}

/**
  Register the handler to extract CRC32 guided section.

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
PeiSignedSectionVerificationLibConstructor (
  IN EFI_PEI_FILE_HANDLE     FileHandle,
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  return ExtractGuidedSectionRegisterHandlers (
           &gEfiFirmwareContentsSignedGuid,
           SignedSectionGetInfo,
           SignedSectionHandler
           );
}

