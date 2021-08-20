//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  PKCS7 related operations used in KeyEnroll tool.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "Pkcs7Verify.h"

UINT8 mOidValue[9] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x02 };

BOOLEAN
WrapPkcs7Data (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  OUT BOOLEAN      *WrapFlag,
  OUT UINT8        **WrapData,
  OUT UINTN        *WrapDataSize
  )
{
  BOOLEAN          Wrapped;
  UINT8            *SignedData;

  //
  // Check whether input P7Data is a wrapped ContentInfo structure or not.
  //
  Wrapped = FALSE;
  if ((P7Data[4] == 0x06) && (P7Data[5] == 0x09)) {
    if (CompareMem (P7Data + 6, mOidValue, sizeof (mOidValue)) == 0) {
      if ((P7Data[15] == 0xA0) && (P7Data[16] == 0x82)) {
        Wrapped = TRUE;
      }
    }
  }

  if (Wrapped) {
    *WrapData     = (UINT8 *) P7Data;
    *WrapDataSize = P7Length;
  } else {
    //
    // Wrap PKCS#7 signeddata to a ContentInfo structure - add a header in 19 bytes.
    //
    *WrapDataSize = P7Length + 19;
    *WrapData     = malloc (*WrapDataSize);
    if (*WrapData == NULL) {
      *WrapFlag = Wrapped;
      return FALSE;
    }

    SignedData = *WrapData;

    //
    // Part1: 0x30, 0x82.
    //
    SignedData[0] = 0x30;
    SignedData[1] = 0x82;

    //
    // Part2: Length1 = P7Length + 19 - 4, in big endian.
    //
    SignedData[2] = (UINT8) (((UINT16) (*WrapDataSize - 4)) >> 8);
    SignedData[3] = (UINT8) (((UINT16) (*WrapDataSize - 4)) & 0xff);

    //
    // Part3: 0x06, 0x09.
    //
    SignedData[4] = 0x06;
    SignedData[5] = 0x09;

    //
    // Part4: OID value -- 0x2A 0x86 0x48 0x86 0xF7 0x0D 0x01 0x07 0x02.
    //
    CopyMem (SignedData + 6, mOidValue, sizeof (mOidValue));

    //
    // Part5: 0xA0, 0x82.
    //
    SignedData[15] = 0xA0;
    SignedData[16] = 0x82;

    //
    // Part6: Length2 = P7Length, in big endian.
    //
    SignedData[17] = (UINT8) (((UINT16) P7Length) >> 8);
    SignedData[18] = (UINT8) (((UINT16) P7Length) & 0xff);

    //
    // Part7: P7Data.
    //
    CopyMem (SignedData + 19, (VOID *)P7Data, P7Length);
  }

  *WrapFlag = Wrapped;
  return TRUE;
}


BOOLEAN
X509PopCertificate (
  IN  VOID  *X509Stack,
  OUT UINT8 **Cert,
  OUT UINTN *CertSize
  )
{
  BIO             *CertBio;
  X509            *X509Cert;
  STACK_OF(X509)  *CertStack;
  BOOLEAN         Status;
  INT32           Result;
  BUF_MEM         *Ptr;
  INT32           Length;
  VOID            *Buffer;

  Status = FALSE;

  if ((X509Stack == NULL) || (Cert == NULL) || (CertSize == NULL)) {
    return Status;
  }

  CertStack = (STACK_OF(X509) *) X509Stack;

  X509Cert = sk_X509_pop (CertStack);

  if (X509Cert == NULL) {
    return Status;
  }

  Buffer = NULL;

  CertBio = BIO_new (BIO_s_mem ());
  if (CertBio == NULL) {
    return Status;
  }

  Result = i2d_X509_bio (CertBio, X509Cert);
  if (Result == 0) {
    goto _Exit;
  }

  BIO_get_mem_ptr (CertBio, &Ptr);
  Length = (INT32)(Ptr->length);
  if (Length <= 0) {
    goto _Exit;
  }

  Buffer = malloc (Length);
  if (Buffer == NULL) {
    goto _Exit;
  }

  Result = BIO_read (CertBio, Buffer, Length);
  if (Result != Length) {
    goto _Exit;
  }

  *Cert     = Buffer;
  *CertSize = Length;

  Status = TRUE;

_Exit:

  BIO_free (CertBio);

  if (!Status && (Buffer != NULL)) {
    free (Buffer);
  }

  return Status;
}

BOOLEAN
EFIAPI
Pkcs7GetSigners (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  OUT UINT8        **CertStack,
  OUT UINTN        *StackLength,
  OUT UINT8        **TrustedCert,
  OUT UINTN        *CertLength
  )
{
  PKCS7            *Pkcs7;
  BOOLEAN          Status;
  UINT8            *SignedData;
  CONST UINT8      *Temp;
  UINTN            SignedDataSize;
  BOOLEAN          Wrapped;
  STACK_OF(X509)   *Stack;
  UINT8            Index;
  UINT8            *CertBuf;
  UINT8            *OldBuf;
  UINTN            BufferSize;
  UINTN            OldSize;
  UINT8            *SingleCert;
  UINTN            SingleCertSize;

  if ( (P7Data == NULL) || (CertStack == NULL) || (StackLength == NULL) ||
       (TrustedCert == NULL) || (CertLength == NULL) || (P7Length > INT_MAX)
     ) {
    return FALSE;
  }

  Status = WrapPkcs7Data (P7Data, P7Length, &Wrapped, &SignedData, &SignedDataSize);
  if (!Status) {
    return Status;
  }

  Status     = FALSE;
  Pkcs7      = NULL;
  Stack      = NULL;
  CertBuf    = NULL;
  OldBuf     = NULL;
  SingleCert = NULL;

  //
  // Retrieve PKCS#7 Data (DER encoding)
  //
  if (SignedDataSize > INT_MAX) {
    goto _Exit;
  }

  Temp = SignedData;
  Pkcs7 = d2i_PKCS7 (NULL, (const unsigned char **) &Temp, (int) SignedDataSize);
  if (Pkcs7 == NULL) {
    goto _Exit;
  }

  //
  // Check if it's PKCS#7 Signed Data (for Authenticode Scenario)
  //
  if (!PKCS7_type_is_signed (Pkcs7)) {
    goto _Exit;
  }

  Stack = PKCS7_get0_signers(Pkcs7, NULL, PKCS7_BINARY);
  if (Stack == NULL) {
    goto _Exit;
  }

  //
  // Convert CertStack to buffer in following format:
  // UINT8  CertNumber;
  // UINT32 Cert1Length;
  // UINT8  Cert1[];
  // UINT32 Cert2Length;
  // UINT8  Cert2[];
  // ...
  // UINT32 CertnLength;
  // UINT8  Certn[];
  //
  BufferSize = sizeof (UINT8);
  OldSize    = BufferSize;

  for (Index = 0; ; Index++) {
    Status = X509PopCertificate (Stack, &SingleCert, &SingleCertSize);
    if (!Status) {
      break;
    }

    OldSize    = BufferSize;
    OldBuf     = CertBuf;
    BufferSize = OldSize + SingleCertSize + sizeof (UINT32);
    CertBuf    = malloc (BufferSize);

    if (CertBuf == NULL) {
      goto _Exit;
    }

    if (OldBuf != NULL) {
      CopyMem (CertBuf, OldBuf, OldSize);
      free (OldBuf);
      OldBuf = NULL;
    }

    KeyEnrollWriteUnaligned32 ((UINT32 *) (CertBuf + OldSize), (UINT32) SingleCertSize);
    CopyMem (CertBuf + OldSize + sizeof (UINT32), SingleCert, SingleCertSize);

    free (SingleCert);
    SingleCert = NULL;
  }

  if (CertBuf != NULL) {
    //
    // Update CertNumber.
    //
    CertBuf[0] = Index;

    *CertLength = BufferSize - OldSize - sizeof (UINT32);
    *TrustedCert = malloc (*CertLength);
    if (*TrustedCert == NULL) {
      goto _Exit;
    }

    CopyMem (*TrustedCert, CertBuf + OldSize + sizeof (UINT32), *CertLength);
    *CertStack   = CertBuf;
    *StackLength = BufferSize;
    Status = TRUE;
  }

_Exit:
  //
  // Release Resources
  //
  if (!Wrapped) {
    free (SignedData);
  }

  if (Pkcs7 != NULL) {
    PKCS7_free (Pkcs7);
  }

  if (Stack != NULL) {
    sk_X509_pop_free(Stack, X509_free);
  }

  if (SingleCert !=  NULL) {
    free (SingleCert);
  }

  if (!Status && (CertBuf != NULL)) {
    free (CertBuf);
    *CertStack = NULL;
  }

  if (OldBuf != NULL) {
    free (OldBuf);
  }

  return Status;
}

/**
  Wrap function to use free() to free allocated memory for certificates.

  @param[in]  Certs        Pointer to the certificates to be freed.

**/
VOID
Pkcs7FreeSigners (
  IN  UINT8        *Certs
  )
{
  if (Certs == NULL) {
    return;
  }

  free (Certs);
}

BOOLEAN
EFIAPI
Pkcs7Verify(
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  IN  CONST UINT8  *TrustedCert,
  IN  UINTN        CertLength,
  IN  CONST UINT8  *InData,
  IN  UINTN        DataLength
  )
{
  PKCS7       *Pkcs7;
  BIO         *DataBio;
  BOOLEAN     Status;
  X509        *Cert;
  X509_STORE  *CertStore;
  UINT8       *SignedData;
  CONST UINT8 *Temp;
  UINTN       SignedDataSize;
  BOOLEAN     Wrapped;

  //
  // Check input parameters.
  //
  if (P7Data == NULL || TrustedCert == NULL || InData == NULL ||
    P7Length > INT_MAX || CertLength > INT_MAX || DataLength > INT_MAX) {
    return FALSE;
  }

  Pkcs7 = NULL;
  DataBio = NULL;
  Cert = NULL;
  CertStore = NULL;

  //
  // Register & Initialize necessary digest algorithms for PKCS#7 Handling
  //
  if (EVP_add_digest(EVP_md5()) == 0) {
    return FALSE;
  }
  if (EVP_add_digest(EVP_sha1()) == 0) {
    return FALSE;
  }
  if (EVP_add_digest(EVP_sha256()) == 0) {
    return FALSE;
  }
  if (EVP_add_digest(EVP_sha384()) == 0) {
    return FALSE;
  }
  if (EVP_add_digest(EVP_sha512()) == 0) {
    return FALSE;
  }
  if (EVP_add_digest_alias(SN_sha1WithRSAEncryption, SN_sha1WithRSA) == 0) {
    return FALSE;
  }

  Status = WrapPkcs7Data(P7Data, P7Length, &Wrapped, &SignedData, &SignedDataSize);
  if (!Status) {
    return Status;
  }

  Status = FALSE;

  //
  // Retrieve PKCS#7 Data (DER encoding)
  //
  if (SignedDataSize > INT_MAX) {
    goto _Exit;
  }

  Temp = SignedData;
  Pkcs7 = d2i_PKCS7(NULL, (const unsigned char **)&Temp, (int)SignedDataSize);
  if (Pkcs7 == NULL) {
    goto _Exit;
  }

  //
  // Check if it's PKCS#7 Signed Data (for Authenticode Scenario)
  //
  if (!PKCS7_type_is_signed(Pkcs7)) {
    goto _Exit;
  }

  //
  // Read DER-encoded root certificate and Construct X509 Certificate
  //
  Temp = TrustedCert;
  Cert = d2i_X509(NULL, &Temp, (long)CertLength);
  if (Cert == NULL) {
    goto _Exit;
  }

  //
  // Setup X509 Store for trusted certificate
  //
  CertStore = X509_STORE_new();
  if (CertStore == NULL) {
    goto _Exit;
  }
  if (!(X509_STORE_add_cert(CertStore, Cert))) {
    goto _Exit;
  }

  //
  // For generic PKCS#7 handling, InData may be NULL if the content is present
  // in PKCS#7 structure. So ignore NULL checking here.
  //
  DataBio = BIO_new(BIO_s_mem());
  if (DataBio == NULL) {
    goto _Exit;
  }

  if (BIO_write(DataBio, InData, (int)DataLength) <= 0) {
    goto _Exit;
  }

  //
  // Allow partial certificate chains, terminated by a non-self-signed but
  // still trusted intermediate certificate. Also disable time checks.
  //
  X509_STORE_set_flags(CertStore,
    X509_V_FLAG_PARTIAL_CHAIN | X509_V_FLAG_NO_CHECK_TIME);

  //
  // OpenSSL PKCS7 Verification by default checks for SMIME (email signing) and
  // doesn't support the extended key usage for Authenticode Code Signing.
  // Bypass the certificate purpose checking by enabling any purposes setting.
  //
  X509_STORE_set_purpose(CertStore, X509_PURPOSE_ANY);

  //
  // Verifies the PKCS#7 signedData structure
  //
  Status = (BOOLEAN)PKCS7_verify(Pkcs7, NULL, CertStore, DataBio, NULL, PKCS7_BINARY);

_Exit:
  //
  // Release Resources
  //
  BIO_free(DataBio);
  X509_free(Cert);
  X509_STORE_free(CertStore);
  PKCS7_free(Pkcs7);

  if (!Wrapped) {
    OPENSSL_free(SignedData);
  }

  return Status;
}

RETURN_STATUS
EFIAPI
X509GetCommonName (
  IN      CONST UINT8  *Cert,
  IN      UINTN        CertSize,
  OUT     CHAR8        *CommonName,  OPTIONAL
  IN OUT  UINTN        *CommonNameSize
  )
{
  RETURN_STATUS  ReturnStatus;
  BOOLEAN        Status;
  X509           *X509Cert;
  X509_NAME      *X509Name;
  INTN           Length;

  ReturnStatus = RETURN_INVALID_PARAMETER;

  //
  // Check input parameters.
  //
  if ((Cert == NULL) || (CertSize > INT_MAX) || (CommonNameSize == NULL)) {
    return ReturnStatus;
  }
  if ((CommonName != NULL) && (*CommonNameSize == 0)) {
    return ReturnStatus;
  }

  X509Cert = NULL;
  //
  // Read DER-encoded X509 Certificate and Construct X509 object.
  //
  Status = X509ConstructCertificate (Cert, CertSize, (UINT8 **) &X509Cert);
  if ((X509Cert == NULL) || (!Status)) {
    //
    // Invalid X.509 Certificate
    //
    goto _Exit;
  }

  Status = FALSE;

  //
  // Retrieve subject name from certificate object.
  //
  X509Name = X509_get_subject_name (X509Cert);
  if (X509Name == NULL) {
    //
    // Fail to retrieve subject name content
    //
    goto _Exit;
  }

  //
  // Retrieve the CommonName information from X.509 Subject
  //
  Length = (INTN) X509_NAME_get_text_by_NID (X509Name, NID_commonName, CommonName, (int)(*CommonNameSize));
  if (Length < 0) {
    //
    // No CommonName entry exists in X509_NAME object
    //
    *CommonNameSize = 0;
    ReturnStatus    = RETURN_NOT_FOUND;
    goto _Exit;
  }

  *CommonNameSize = (UINTN)(Length + 1);
  if (CommonName == NULL) {
    ReturnStatus = RETURN_BUFFER_TOO_SMALL;
  } else {
    ReturnStatus = RETURN_SUCCESS;
  }

_Exit:
  //
  // Release Resources.
  //
  if (X509Cert != NULL) {
    X509_free (X509Cert);
  }

  return ReturnStatus;
}

BOOLEAN
EFIAPI
X509ConstructCertificate (
  IN   CONST UINT8  *Cert,
  IN   UINTN        CertSize,
  OUT  UINT8        **SingleX509Cert
  )
{
  X509         *X509Cert;
  CONST UINT8  *Temp;

  //
  // Check input parameters.
  //
  if (Cert == NULL || SingleX509Cert == NULL || CertSize > INT_MAX) {
    return FALSE;
  }

  //
  // Read DER-encoded X509 Certificate and Construct X509 object.
  //
  Temp     = Cert;
  X509Cert = d2i_X509 (NULL, &Temp, (long) CertSize);
  if (X509Cert == NULL) {
    return FALSE;
  }

  *SingleX509Cert = (UINT8 *) X509Cert;

  return TRUE;
}

BOOLEAN
Sha256Init (
  OUT  VOID  *Sha256Context
  )
{
  //
  // Check input parameters.
  //
  if (Sha256Context == NULL) {
    return FALSE;
  }

  //
  // OpenSSL SHA-256 Context Initialization
  //
  return (BOOLEAN) (SHA256_Init ((SHA256_CTX *) Sha256Context));
}

BOOLEAN
Sha256Update (
  IN OUT  VOID        *Sha256Context,
  IN      CONST VOID  *Data,
  IN      UINTN       DataSize
  )
{
  //
  // Check input parameters.
  //
  if (Sha256Context == NULL) {
    return FALSE;
  }

  //
  // Check invalid parameters, in case that only DataLength was checked in OpenSSL
  //
  if (Data == NULL && DataSize != 0) {
    return FALSE;
  }

  //
  // OpenSSL SHA-256 Hash Update
  //
  return (BOOLEAN) (SHA256_Update ((SHA256_CTX *) Sha256Context, Data, DataSize));
}

BOOLEAN
EFIAPI
Sha256Final (
  IN OUT  VOID   *Sha256Context,
  OUT     UINT8  *HashValue
  )
{
  //
  // Check input parameters.
  //
  if (Sha256Context == NULL || HashValue == NULL) {
    return FALSE;
  }

  //
  // OpenSSL SHA-256 Hash Finalization
  //
  return (BOOLEAN) (SHA256_Final (HashValue, (SHA256_CTX *) Sha256Context));
}


/**
  Calculate SHA256 digest of SignerCert CommonName + ToplevelCert tbsCertificate
  SignerCert and ToplevelCert are inside the signer certificate chain.

  @param[in]  SignerCert          A pointer to SignerCert data.
  @param[in]  SignerCertSize      Length of SignerCert data.
  @param[in]  TopLevelCert        A pointer to TopLevelCert data.
  @param[in]  TopLevelCertSize    Length of TopLevelCert data.
  @param[out] Sha256Digest        Sha256 digest calculated.

  @return EFI_ABORTED             Digest process failed.
  @return EFI_SUCCESS             SHA256 Digest is succesfully calculated.

**/
EFI_STATUS
CalculatePrivAuthVarSignChainSHA256Digest (
  IN    UINT8               *SignerCert,
  IN    UINTN               SignerCertSize,
  IN    UINT8               *TopLevelCert,
  IN    UINTN               TopLevelCertSize,
  OUT   UINT8               *Sha256Digest
  )
{
  EFI_STATUS                Status;
  UINT8                     *TbsCert;
  UINTN                     TbsCertSize;
  CHAR8                     CertCommonName[128];
  UINTN                     CertCommonNameSize;
  VOID                      *mHashCtx;
  BOOLEAN                   CryptoStatus;

  Status                    = EFI_SUCCESS;
  mHashCtx                  = NULL;

  CertCommonNameSize = sizeof (CertCommonName);

  //
  // Get SignerCert CommonName
  //
  Status = X509GetCommonName (SignerCert, SignerCertSize, CertCommonName, &CertCommonNameSize);
  if (EFI_ERROR(Status)) {
    return EFI_ABORTED;
  }

  //
  // Get TopLevelCert tbsCertificate
  //
  if (!X509GetTBSCert (TopLevelCert, TopLevelCertSize, &TbsCert, &TbsCertSize)) {
    return EFI_ABORTED;
  }

  //
  // Digest SignerCert CN + TopLevelCert tbsCertificate
  //
  ZeroMem (Sha256Digest, SHA256_DIGEST_SIZE);

  mHashCtx = malloc((UINTN)(sizeof(SHA256_CTX)));
  if (mHashCtx == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CryptoStatus = Sha256Init (mHashCtx);
  if (!CryptoStatus) {
    Status = EFI_ABORTED;
    goto ON_EXIT;
  }

  //
  // '\0' is forced in CertCommonName. No overflow issue
  //
  CryptoStatus = Sha256Update (
                   mHashCtx,
                   CertCommonName,
                   strlen (CertCommonName)
                   );
  if (!CryptoStatus) {
    Status = EFI_ABORTED;
    goto ON_EXIT;
  }

  CryptoStatus = Sha256Update (mHashCtx, TbsCert, TbsCertSize);
  if (!CryptoStatus) {
    Status = EFI_ABORTED;
    goto ON_EXIT;
  }

  CryptoStatus  = Sha256Final (mHashCtx, Sha256Digest);
  if (!CryptoStatus) {
    Status = EFI_ABORTED;
    goto ON_EXIT;
  }

ON_EXIT:
  FREE_NON_NULL_PTR (mHashCtx);

  return Status;
}
