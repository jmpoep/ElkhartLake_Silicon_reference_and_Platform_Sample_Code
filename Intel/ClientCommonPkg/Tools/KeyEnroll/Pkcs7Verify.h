//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Header file for PKCS7 related operations used in KeyEnroll tool.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _PKCS_VERIFY_H
#define _PKCS_VERIFY_H

#include "KeyEnroll.h"
#include "Unaligned.h"

#define X509_V_FLAG_PARTIAL_CHAIN               0x80000
#define X509_V_FLAG_NO_CHECK_TIME               0x200000
#define X509_PURPOSE_ANY                        7

BOOLEAN
WrapPkcs7Data (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  OUT BOOLEAN      *WrapFlag,
  OUT UINT8        **WrapData,
  OUT UINTN        *WrapDataSize
  );

BOOLEAN
X509PopCertificate (
  IN  VOID  *X509Stack,
  OUT UINT8 **Cert,
  OUT UINTN *CertSize
  );

BOOLEAN
EFIAPI
Pkcs7GetSigners (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  OUT UINT8        **CertStack,
  OUT UINTN        *StackLength,
  OUT UINT8        **TrustedCert,
  OUT UINTN        *CertLength
  );

VOID
Pkcs7FreeSigners (
  IN  UINT8        *Certs
  );

BOOLEAN
EFIAPI
Pkcs7Verify(
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  IN  CONST UINT8  *TrustedCert,
  IN  UINTN        CertLength,
  IN  CONST UINT8  *InData,
  IN  UINTN        DataLength
  );

RETURN_STATUS
EFIAPI
X509GetCommonName (
  IN      CONST UINT8  *Cert,
  IN      UINTN        CertSize,
  OUT     CHAR8        *CommonName,  OPTIONAL
  IN OUT  UINTN        *CommonNameSize
  );

BOOLEAN
EFIAPI
X509ConstructCertificate (
  IN   CONST UINT8  *Cert,
  IN   UINTN        CertSize,
  OUT  UINT8        **SingleX509Cert
  );

BOOLEAN
Sha256Init (
  OUT  VOID  *Sha256Context
  );

BOOLEAN
Sha256Update (
  IN OUT  VOID        *Sha256Context,
  IN      CONST VOID  *Data,
  IN      UINTN       DataSize
  );

BOOLEAN
EFIAPI
Sha256Final (
  IN OUT  VOID   *Sha256Context,
  OUT     UINT8  *HashValue
  );

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
  );

#endif
