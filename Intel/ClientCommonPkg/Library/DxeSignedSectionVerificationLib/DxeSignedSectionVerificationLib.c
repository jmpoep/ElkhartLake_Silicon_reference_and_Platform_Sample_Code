/** @file

  This library registers signed guided section handler 
  to verify the signed section and extract raw data.

 Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiDxe.h>
#include <Library/ExtractGuidedSectionLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/FirmwareVolume2.h>

#define EFI_FIRMWARE_CONTENTS_SIGNED_GUID \
  { 0xf9d89e8, 0x9259, 0x4f76, { 0xa5, 0xaf, 0xc, 0x89, 0xe3, 0x40, 0x23, 0xdf } }
EFI_GUID mSignFvGuid = EFI_FIRMWARE_CONTENTS_SIGNED_GUID;

#define EFI_PUBKEY_FFS_GUID \
  { 0x31c17abe, 0x6071, 0x435e, { 0xba, 0xa4, 0xb, 0x8a, 0x8c, 0x36, 0x49, 0xf3 } }
EFI_GUID mPubkeyFfsGuid = EFI_PUBKEY_FFS_GUID;

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
  FreePool (HashCtx);
}

EFI_STATUS
GetPubKeyHash (
  OUT UINT8      **PubKeyHash,
  OUT UINTN      *PubKeyHashLength
  )
{
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         NumberOfHandles;
  EFI_HANDLE                    *HandleBuffer;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  UINT8                         *FileBuffer;
  UINTN                         FileSize;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < NumberOfHandles; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &FwVol
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    FileBuffer = NULL;
    FileSize = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &mPubkeyFfsGuid,
                      (VOID **) &FileBuffer,
                      &FileSize,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );
    if (Status == EFI_SUCCESS) {
      *PubKeyHash = FileBuffer;
      *PubKeyHashLength = FileSize;
      break;
    }
  }

  return Status;
}

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
    DEBUG ((EFI_D_ERROR, "      %04x: ", Index * COL_SIZE));
    for (IndexJ = 0; IndexJ < COL_SIZE; IndexJ++) {
      DEBUG ((EFI_D_ERROR, "%02x ", *(Buffer + Index * COL_SIZE + IndexJ)));
    }
    DEBUG ((EFI_D_ERROR, "\n"));
  }
  if ((BufferSize % COL_SIZE) != 0) {
    DEBUG ((EFI_D_ERROR, "      %04x: ", Index * COL_SIZE));
    for (IndexJ = 0; IndexJ < (BufferSize % COL_SIZE); IndexJ++) {
      DEBUG ((EFI_D_ERROR, "%02x ", *(Buffer + Index * COL_SIZE + IndexJ)));
    }
    DEBUG ((EFI_D_ERROR, "\n"));
  }
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
    DEBUG ((EFI_D_ERROR, "SignedSectionHandler - GetPubKeyHash - %r\n", Status));
    *AuthenticationStatus |= EFI_AUTH_STATUS_NOT_TESTED;
     return EFI_SECURITY_VIOLATION;
  } else {
    DEBUG_CODE (
      DEBUG ((EFI_D_ERROR, "PubKeyHash:\n"));
      DumpHex (PubKeyHash, PubKeyHashLength);
      DEBUG ((EFI_D_ERROR, "MessageHash:\n"));
      DumpHex (MessageHash, sizeof(MessageHash));
    );
    if ((PubKeyHashLength != sizeof(MessageHash)) || (CompareMem (PubKeyHash, MessageHash, sizeof(MessageHash)) != 0)) {
      DEBUG ((EFI_D_ERROR, "SignedSectionHandler - PubKey Validation FAIL\n"));
      *AuthenticationStatus |= EFI_AUTH_STATUS_NOT_TESTED;
      return EFI_SECURITY_VIOLATION;
    }
  }
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - PubKey Validation PASS\n"));

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

  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - RsaPkcs1Verify ... \n"));
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

  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - RsaPkcs1Verify - %x\n", BStatus));
  RsaFree (RsaContext);
  if (!BStatus) {
    //
    // Signature invalid.
    //
    *AuthenticationStatus |= EFI_AUTH_STATUS_TEST_FAILED;
    return EFI_SECURITY_VIOLATION;
  } else {
    return EFI_SUCCESS;
  }
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
        &mSignFvGuid,
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
        &mSignFvGuid,
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

  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - Enter\n"));
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - InputSection - %x\n", InputSection));

  if (IS_SECTION2 (InputSection)) {
    //
    // Check whether the input guid section is recognized.
    //
    if (!CompareGuid (
        &mSignFvGuid,
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
        &mSignFvGuid,
        &(((EFI_GUID_DEFINED_SECTION *) InputSection)->SectionDefinitionGuid))) {

      DEBUG ((EFI_D_ERROR, "SignedSectionHandler - Guid Mismatch\n"));
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
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - OutputBuffer - %x\n", *OutputBuffer));
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - OutputBufferSize - %x\n", OutputBufferSize));
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - SignedData - %x\n", SignedData));
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - SignedDataSize - %x\n", SignedDataSize));

  //
  // Validate SignedSection
  //
  Status = VerifyRsa2048Sha256Signature ((EFI_CERT_BLOCK_RSA_2048_SHA256 *)SignedData, *OutputBuffer, OutputBufferSize, AuthenticationStatus);

  DEBUG ((EFI_D_ERROR, "AuthenticationStatus - 0x%08x\n", *AuthenticationStatus));
  DEBUG ((EFI_D_ERROR, "SignedSectionHandler - Exit\n"));

  return Status;
}

/**
  Register the handler to extract CRC32 guided section.

  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
DxeSignedSectionVerificationLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return ExtractGuidedSectionRegisterHandlers (
           &mSignFvGuid,
           SignedSectionGetInfo,
           SignedSectionHandler
           );
}

