/** @file
  This file contains the crypto code for Seed Protocol DXE driver.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification

**/

#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/RngLib.h>
#include <Library/DebugLib.h>
#include "SeedProtocolCrypto.h"
#include "PersistentStorage.h"

/**
  Generate random seed salt.
  The salt must be a multiple of 64 bits (8 bytes).

  @param[out]       SeedSalt          Buffer to receive seed salt.
  @param[in]        SeedSaltSize      Size of buffer receiving seed salt.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
EFI_STATUS
GenerateSeedSalt (
  OUT UINT8       *SeedSalt,
  IN CONST UINTN  SeedSaltSize
)
{
  UINT64 *RandomPtr = (UINT64*)SeedSalt;
  EFI_STATUS Status = EFI_SUCCESS;
  BOOLEAN Result    = TRUE;
  UINT32 Index      = 0;

  ASSERT (SeedSalt != NULL);
  ASSERT ((SeedSaltSize % 8) == 0);

  while ((Index < SeedSaltSize/sizeof(UINT64)) && Result) {
    Result = GetRandomNumber64 (RandomPtr);
    RandomPtr++;
    Index++;
  }

  if (!Result) {
    ZeroMem (SeedSalt, SeedSaltSize);
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Get seed salt (from persiatant storage or generate random value).

  @param[in]        SaltName          Name of salt to load.
  @param[out]       SeedSalt          Buffer to receive seed salt.
  @param[in, out]   SeedSaltSize      Size of buffer receiving seed salt.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
EFI_STATUS
GetSeedSalt (
  CONST IN UINT16* SaltName,
  OUT UINT8       *SeedSalt,
  IN UINTN        *SeedSaltSize
)
{
  EFI_STATUS Status;

  /* Validate input parameters. */
  if ((SeedSalt == NULL) || (*SeedSaltSize != SEED_SALT_SIZE)) {
    return EFI_INVALID_PARAMETER;
  }

  /* Load salt if previously generated. */
  Status = LoadPersistentData (SaltName, SeedSalt, SeedSaltSize);
  if (Status == EFI_NOT_FOUND) {
    /* Generate new random salt. */
    Status = GenerateSeedSalt (SeedSalt, *SeedSaltSize);
    if (Status == EFI_SUCCESS) {
      /* Save generated value. */
      Status = SavePersistentData (SaltName, SeedSalt, *SeedSaltSize);
    }
  }

  return Status;
}

/**
  Compute keyed hash of data.

  @param[in]       Key        Hash key.
  @param[in]       KeySize    Hash key size.
  @param[in]       Data       Hash key.
  @param[in]       DataSize   Hash key size.
  @param[out]      Hash       Result hash

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
HmacSha256 (
  IN CONST UINT8  *Key,
  IN CONST UINTN  KeySize,
  IN CONST UINT8  *Data,
  IN CONST UINTN  DataSize,
  OUT UINT8      *Hash
)
{
  EFI_STATUS Status = EFI_DEVICE_ERROR;
  VOID *HmacCtx = NULL;

  HmacCtx = HmacSha256New ();
  if (HmacCtx) {

    do {
      BOOLEAN Result;

      Result = HmacSha256Init (
            HmacCtx,
            Key,
            KeySize
      );
      if (Result == FALSE) {
        break;
      }

      Result = HmacSha256Update (
            HmacCtx,
            Data,
            DataSize
      );
      if (Result == FALSE) {
        break;
      }

      Result = HmacSha256Final (
            HmacCtx,
            Hash
      );
      if (Result == FALSE) {
        break;
      }

      Status = EFI_SUCCESS;

    } while (0);

    HmacSha256Free (HmacCtx);
  }

  return Status;
}

/**
  Set buffer to debug seed (fixed value).

  @param[out]      Key        Pointer to receive key.
  @param[in]       KeySize    Key size.

**/
VOID
SetDebugSeed (
  OUT VOID        *Key,
  IN CONST UINTN  KeySize
)
{
  SetMem (Key, KeySize, 0xA5);
}

/**
  Check buffer for debug seed (fixed value).

  @param[in]       Key        Pointer to receive key.
  @param[in]       KeySize    Key size.

  @retval TRUE                Seed is debug seed.
  @retval FALSE               Seed is not debug seed.

**/
BOOLEAN
IsDebugSeed (
  IN CONST VOID   *Key,
  IN CONST UINTN  KeySize
)
{
  BOOLEAN ReturnCode = TRUE;
  CONST UINT8 *KeyPtr = (UINT8*)Key;
  UINTN KeyIndex;
  for (KeyIndex = 0; KeyIndex < KeySize; KeyIndex++) {
    if (KeyPtr[KeyIndex] != 0xA5) {
      ReturnCode = FALSE;
      break;
    }
  }
  return ReturnCode;
}
