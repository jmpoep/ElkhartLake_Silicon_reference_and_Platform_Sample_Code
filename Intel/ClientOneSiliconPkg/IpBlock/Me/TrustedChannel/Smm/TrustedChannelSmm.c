/** @file
  Implementation file for HECI Trusted Channnel Services

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

@par Specification Reference

**/

#include "TrustedChannelSmm.h"
#include <Library/BaseLib.h>
#include <MeBiosPayloadData.h>
#include <MeBiosPayloadHob.h>
#include <TrustedChannel.h>
#include <Protocol/TrustedChannel.h>
#include <Protocol/ComputeHmacSha256.h>
#include <Register/HeciRegs.h>
#include <Library/PciSegmentLib.h>

STATIC UINT32  mSignMonotonicCount;
STATIC UINT32  mVerifyMonotonicCount;
STATIC UINT8   mHmacSha256Key[32] = {0};
COMPUTE_HMAC_SHA_256_PROTOCOL *mComputeHmacSha256Protocol;

HECI_TRUSTED_CHANNEL_PROTOCOL mHeciTrustedChannelProtocol = {
  HeciTrustedChannelDecrementMonotonicCount,
  HeciTrustedChannelIsTrustedChannelEnabled,
  HeciTrustedChannelUpdateTrustedHeader,
  HeciTrustedChannelVerifyTrustedHeader
};

/**
  Retrieves the Trusted Channel key from MBP.

  @param[out] TrustedChannelKey      A pointer to a data buffer to hold the trusted key.

  @return     EFI_SUCCESS            Retrieved the trusted channel key successfully.
  @retval     EFI_INVALID_PARAMETER  The TrustedChannelData pointer is NULL
  @retval     EFI_NOT_FOUND          The trusted channel key could not be found.
  @return     Others                 Failed to retrieve the trusted channel key.
**/
EFI_STATUS
EFIAPI
GetTrustedChannelKey (
  OUT TRUSTED_CHANNEL_DATA   *TrustedChannelData
  )
{
  UINTN                         MbpSensitiveDataHobInstances;
  ME_BIOS_PAYLOAD_SENSITIVE_HOB *MbpSensitiveDataHob;

  if (TrustedChannelData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the sensitive data MBP HOB
  //
  MbpSensitiveDataHob = GetFirstGuidHob (&gMeBiosPayloadSensitiveDataHobGuid);
  if (MbpSensitiveDataHob != NULL) {
    if (MbpSensitiveDataHob->MeBiosPayloadSensitive.TrustedChannel.Available) {
      CopyMem (
        (VOID *) TrustedChannelData,
        (VOID *) &(MbpSensitiveDataHob->MeBiosPayloadSensitive.TrustedChannel.Data),
        sizeof (TRUSTED_CHANNEL_DATA)
        );
    } else {
      DEBUG ((DEBUG_ERROR, "The trusted channel MBP item is not available.\n"));
      return EFI_NOT_FOUND;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "The trusted channel MBP item was not found.\n"));
    return EFI_NOT_FOUND;
  }

  MbpSensitiveDataHobInstances = 0;
  do {
    //
    // Clear the Trusted Channel MBP item from the HOB
    //
    ZeroMem (
      (VOID *) &(MbpSensitiveDataHob->MeBiosPayloadSensitive.TrustedChannel),
      sizeof (MBP_ME_NVM_SMM_TRUSTED_CHANNEL)
      );
    MbpSensitiveDataHob = GET_NEXT_HOB (MbpSensitiveDataHob);
    MbpSensitiveDataHob = GetNextGuidHob (&gMeBiosPayloadSensitiveDataHobGuid, MbpSensitiveDataHob);
    MbpSensitiveDataHobInstances++;
  } while (MbpSensitiveDataHob != NULL);
  ASSERT (MbpSensitiveDataHobInstances == 1);

  return EFI_SUCCESS;
}

/**
  Returns whether trusted channel is enabled.

  @param[in]  None.

  @retval     TRUE if trusted channel is enabled.
              FALSE if trusted channel is disabled.
**/
BOOLEAN
EFIAPI
HeciTrustedChannelIsTrustedChannelEnabled (
  VOID
  )
{
  return ((mSignMonotonicCount != 0) && (mVerifyMonotonicCount != 0));
}

/**
  Decrements the monotonic count.

  This function should only be called if an error occurred that prevented the monotonic count
  from being updated in the other agent.

  @param[in]        Count            The decrement count

  @retval           EFI_SUCCESSS     The monotonic count was updated successfully
  @retval           Others           The monotonic count could not be updated
**/
EFI_STATUS
EFIAPI
HeciTrustedChannelDecrementMonotonicCount (
  IN      UINT32    Count
  )
{
  if (Count > mSignMonotonicCount) {
    return EFI_INVALID_PARAMETER;
  }
  mSignMonotonicCount -= Count;

  return EFI_SUCCESS;
}

/**
  Updates the SHA256 signature and monotonic counter fields of a HECI message header.

  @param[in,out]  MessageHeader   A pointer to the message header
  @param[in]      TotalHeaderSize The total header size
  @param[in]      TotalDataSize   The total data size

  @retval         EFI_SUCCESSS    The header was updated successfully
  @retval         Others          The header could not be updated
**/
EFI_STATUS
EFIAPI
HeciTrustedChannelUpdateTrustedHeader (
  IN OUT  VOID        *MessageHeader,
  IN      UINT32      TotalHeaderSize,
  IN      UINT32      TotalDataSize
  )
{
  EFI_STATUS                   Status;
  TRUSTED_CHANNEL_BIOS_HEADER  *TrustedChannelHeader = NULL;
  UINT8                        Digest[64];

  if ((MessageHeader == NULL) || (TotalHeaderSize < sizeof (TRUSTED_CHANNEL_BIOS_HEADER))) {
    return EFI_INVALID_PARAMETER;
  }

  TrustedChannelHeader = (TRUSTED_CHANNEL_BIOS_HEADER  *) MessageHeader;
  TrustedChannelHeader->MonotonicCounter = mSignMonotonicCount;

  DEBUG ((EFI_D_INFO, "Current HMAC monotonic count = %d.\n", TrustedChannelHeader->MonotonicCounter));

  //
  // Compute the HMAC SHA-256 digest
  //
  // Includes all fields except the signature field
  //
  Status = mComputeHmacSha256Protocol->ComputeHmacSha256Signature (
                                         mHmacSha256Key,
                                         sizeof (mHmacSha256Key),
                                         (VOID *) ((UINT8 *) MessageHeader + TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE),
                                         (TotalHeaderSize + TotalDataSize) - TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE,
                                         Digest
                                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  CopyMem (&TrustedChannelHeader->Signature, Digest, TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE);
  mSignMonotonicCount++;

  DEBUG ((EFI_D_INFO, "Trusted channel signature computed = 0x%x\n", Digest));

  return EFI_SUCCESS;
}

/**
  Verifies the SHA 256 HMAC signature of a HECI message.

  @param[in]        MessageHeader             A pointer to the message header
  @param[in]        TotalDataSize             The total data size
  @param[out]       IsVerificationSuccessful  Set to TRUE if the signature in the given message is valid

  @retval           EFI_SUCCESSS     The verification was successful
  @retval           Others           An error occurred during verification
**/
EFI_STATUS
EFIAPI
HeciTrustedChannelVerifyTrustedHeader (
  IN CONST VOID      *MessageHeader,
  IN       UINT32    TotalDataSize,
  OUT      BOOLEAN   *IsVerificationSuccessful
  )
{
  EFI_STATUS                         Status;
  CONST TRUSTED_CHANNEL_BIOS_HEADER  *TrustedChannelHeader = NULL;
  UINT8                              Digest[64];

  *IsVerificationSuccessful = FALSE;
  ZeroMem (Digest, sizeof (Digest));

  if ((mSignMonotonicCount == 0) || (mVerifyMonotonicCount == 0) || (CompareMem (mHmacSha256Key, Digest, sizeof (mHmacSha256Key)) == 0)) {
    // Verification should always occur after the monotonic counter and key have been initialized
    ASSERT (FALSE);
    return EFI_NOT_READY;
  }

  TrustedChannelHeader = (CONST TRUSTED_CHANNEL_BIOS_HEADER  *) MessageHeader;
  DEBUG ((EFI_D_INFO, "HMAC monotonic count in verification = %d.\n", TrustedChannelHeader->MonotonicCounter));

  if ((mVerifyMonotonicCount + 1) != TrustedChannelHeader->MonotonicCounter) {
    DEBUG ((EFI_D_WARN, "Monotonic counter value is invalid!\n"));
    return EFI_SECURITY_VIOLATION;
  }

  //
  // Compute the HMAC SHA-256 digest
  //
  // Includes all fields except the signature field
  //
  Status = mComputeHmacSha256Protocol->ComputeHmacSha256Signature (
                                         mHmacSha256Key,
                                         sizeof (mHmacSha256Key),
                                         (UINT8 *) MessageHeader + TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE,
                                         TotalDataSize - TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE,
                                         Digest
                                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CompareMem (Digest, TrustedChannelHeader->Signature, TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE) == 0) {
    DEBUG ((EFI_D_INFO, "Trusted channel signature is valid.\n"));
    *IsVerificationSuccessful = TRUE;
    mVerifyMonotonicCount++;
  } else {
    DEBUG ((EFI_D_WARN, "Trusted channel signature is invalid!\n"));
  }

  return EFI_SUCCESS;
}

/**
  Entry point of the SMM Trusted Channel Driver.

  @param[in]  ImageHandle    The firmware allocated handle for the EFI image.
  @param[in]  SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS    The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
TrustedChannelSmmEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE             Handle;
  EFI_STATUS             Status;
  TRUSTED_CHANNEL_DATA   TrustedChannelData;
  HECI_FWS_REGISTER      MeFirmwareStatus;

  MeFirmwareStatus.ul = PciSegmentRead32 (
                          PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS)
                          );
  if (BootMediaIsSpi () || PcdGetBool (PcdNvVariableEmulationMode)) {
    return EFI_SUCCESS;
  }



  Handle = NULL;

  if ((mSignMonotonicCount == 0 || mVerifyMonotonicCount == 0) && (!PcdGetBool (PcdEnableVariableConfigInCseRecoveryMode))) {
    //
    // Initialize the Trusted Channel data for this boot
    //
    Status = GetTrustedChannelKey (&TrustedChannelData);
    if (!EFI_ERROR (Status)) {
      CopyMem ((VOID *) mHmacSha256Key, (VOID *) TrustedChannelData.TrustedKey, sizeof (mHmacSha256Key));
      mSignMonotonicCount = TrustedChannelData.MonotonicCounter;
      mVerifyMonotonicCount = TrustedChannelData.MonotonicCounter;

      DEBUG ((EFI_D_INFO, "HMAC Monotonic Count = %d\n", mSignMonotonicCount));
    } else {
      DEBUG ((EFI_D_ERROR, "Unable to get the SMM trusted key. Cannot send HECI2 transactions.\n"));
      ASSERT_EFI_ERROR (Status);
      return Status;
    }
  }

  Status = gSmst->SmmLocateProtocol (
                    &gComputeHmacSha256ProtocolGuid,
                    NULL,
                    (VOID **) &mComputeHmacSha256Protocol
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "The ComputeHmacSha256Protocol is not found. Trusted channel is unavailable!\n"));
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  //
  // Install the Trusted Channel SMM Protocol
  //
  return gSmst->SmmInstallProtocolInterface (
                  &Handle,
                  &gHeciTrustedChannelProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mHeciTrustedChannelProtocol
                  );
}