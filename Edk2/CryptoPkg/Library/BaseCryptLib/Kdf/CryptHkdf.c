/** @file
  HMAC-SHA256 KDF Wrapper Implementation over OpenSSL.

Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/BaseCryptLib.h>
#include <openssl/evp.h>
#include <openssl/kdf.h>

/**
  Derive HMAC-based Extract-and-Expand Key Derivation Function (HKDF).

  @param[in]   Key              Pointer to the user-supplied key.
  @param[in]   KeySize          Key size in bytes.
  @param[in]   Salt             Pointer to the salt(non-secret) value.
  @param[in]   SaltSize         Salt size in bytes.
  @param[in]   Info             Pointer to the application specific info.
  @param[in]   InfoSize         Info size in bytes.
  @param[Out]  Out              Pointer to buffer to receive hkdf value.
  @param[in]   OutSize          Size of hkdf bytes to generate.

  @retval TRUE   Hkdf generated successfully.
  @retval FALSE  Hkdf generation failed.

**/
BOOLEAN
EFIAPI
HkdfSha256ExtractAndExpand (
  IN   CONST UINT8  *Key,
  IN   UINTN        KeySize,
  IN   CONST UINT8  *Salt,
  IN   UINTN        SaltSize,
  IN   CONST UINT8  *Info,
  IN   UINTN        InfoSize,
  OUT  UINT8        *Out,
  IN   UINTN        OutSize
  )
{
  EVP_PKEY_CTX *pHkdfCtx;

  if (Key == NULL || Salt == NULL || Info == NULL || Out == NULL ||
    KeySize > INT_MAX || SaltSize > INT_MAX || InfoSize > INT_MAX || OutSize > INT_MAX ) {
    return FALSE;
  }

  pHkdfCtx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, NULL);
  if (pHkdfCtx == NULL) {
    goto _Error;
  }

  if (EVP_PKEY_derive_init(pHkdfCtx) <= 0) {
    goto _Error;
  }
  if (EVP_PKEY_CTX_set_hkdf_md(pHkdfCtx, EVP_sha256()) <= 0) {
    goto _Error;
  }
  if (EVP_PKEY_CTX_set1_hkdf_salt(pHkdfCtx, Salt, (UINT32)SaltSize) <= 0) {
    goto _Error;
  }
  if (EVP_PKEY_CTX_set1_hkdf_key(pHkdfCtx, Key, (UINT32)KeySize) <= 0) {
    goto _Error;
  }
  if (EVP_PKEY_CTX_add1_hkdf_info(pHkdfCtx, Info, (UINT32)InfoSize) <= 0) {
    goto _Error;
  }
  if (EVP_PKEY_derive(pHkdfCtx, Out, &OutSize) <= 0) {
    goto _Error;
  }

  EVP_PKEY_CTX_free(pHkdfCtx);
  pHkdfCtx = NULL;
  return TRUE;

_Error:
  EVP_PKEY_CTX_free(pHkdfCtx);
  return FALSE;
}
