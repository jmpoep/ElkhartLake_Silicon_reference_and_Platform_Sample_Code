#pragma optimize ("", off)
/** @file
  Implementation file for COMPUTE_HMAC_SHA_256 Protocol

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#include <Library/BaseCryptLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/ComputeHmacSha256.h>
#include "PlatformHmacShaSmm.h"

COMPUTE_HMAC_SHA_256_PROTOCOL mComputeHmacSha256Protocol = {
  ComputeHmacSha256Signature
};

/**
  Computes an HMAC SHA256 signature for a data message.

  @param[in]      HmacSha256Key   Pointer to the user-supplied key.
  @param[in]      KeySize         Key size in bytes.
  @param[in]      Data            The data buffer.
  @param[in]      DataSize        The size in bytes of data in the data buffer.
  @param[in, out] Signature       The HMAC SHA256 signature computed.

  @return     EFI_SUCCESS         The signature was computed successfully.
  @return     Others              Failed to compute the signature.
**/
EFI_STATUS
EFIAPI
ComputeHmacSha256Signature (
  IN CONST UINT8  *HmacSha256Key,
  IN       UINTN   KeySize,
  IN CONST VOID    *Data,
  IN       UINTN   DataSize,
  IN OUT   UINT8   *Signature
  )
{
  UINTN      ContextSize;
  VOID       *HmacContext;
  UINT8      Digest[64];
  BOOLEAN    Status;

  if (HmacSha256Key == NULL || Data == NULL || Signature == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // HMAC-SHA1 Digest Validation
  //
  ZeroMem (Digest, 64);

  ContextSize = HmacSha256GetContextSize ();
  HmacContext = AllocatePool (ContextSize);

  DEBUG ((EFI_D_INFO, "Compute HMAC Signature. DataSize = %x ContextSize = %x\n", DataSize, ContextSize));

  DEBUG ((EFI_D_INFO, "Init... "));

  Status  = HmacSha256Init (HmacContext, HmacSha256Key,KeySize);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "[Fail]"));
    return EFI_ABORTED;
  }

  DEBUG ((EFI_D_INFO, "Update...\n"));

  Status  = HmacSha256Update (HmacContext, Data, DataSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "[Fail]"));
    return EFI_ABORTED;
  }

  DEBUG ((EFI_D_INFO, "Finalize...\n"));

  Status  = HmacSha256Final (HmacContext, Digest);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "[Fail]"));
    return EFI_ABORTED;
  }

  CopyMem (Signature, Digest, SHA256_DIGEST_SIZE);
  FreePool (HmacContext);

  return EFI_SUCCESS;
}

/**
  Entry point of the SMM HMAC SHA driver

  @param[in]  ImageHandle    The firmware allocated handle for the EFI image.
  @param[in]  SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS    The entry point is executed successfully.
  @retval Others         An error occurred installing the COMPUTE_HMAC_SHA_256_PROTOCOL.
**/
EFI_STATUS
EFIAPI
InitializePlatformHmacShaSmm (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE             Handle;

  Handle = NULL;

  //
  // Install the Compute HMAC SHA256 Protocol
  //
  return gSmst->SmmInstallProtocolInterface (
                  &Handle,
                  &gComputeHmacSha256ProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mComputeHmacSha256Protocol
                  );
}