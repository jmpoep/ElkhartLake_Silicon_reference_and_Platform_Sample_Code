/** @file
  This file header contains the crypto interface for Seed Protocol DXE driver.

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

@par Specification Reference:
**/
#ifndef _SEED_PROTOCOL_CRYPTO_H_
#define _SEED_PROTOCOL_CRYPTO_H_

#include <Uefi/UefiBaseType.h>

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
);

/**
  Get seed salt (from persiatant storage or generate random value).

  @param[out]       SeedSalt          Buffer to receive seed salt.
  @param[in]        SeedSaltSize      Size of buffer receiving seed salt.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
EFI_STATUS
GetSeedSalt (
  CONST IN UINT16    *SaltName,
  OUT UINT8          *SeedSalt,
  IN UINTN           *SeedSaltSize
);

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
  OUT UINT8       *Hash
);

/**
  Set buffer to debug seed (fixed value).

  @param[out]      Key        Pointer to receive key.
  @param[in]       KeySize    Key size.

**/
VOID
SetDebugSeed (
  OUT VOID        *Key,
  IN CONST UINTN  KeySize
);

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
);

#endif
