/** @file
  Header file for HECI Trusted Channnel Services

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

#ifndef _TRUSTED_CHANNEL_SMM_H_
#define _TRUSTED_CHANNEL_SMM_H_

#include <TrustedChannel.h>
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

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
  );

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
  );

/**
  Updates the Trusted Channel header for a new Trusted Channel message.

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
  );

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
  );

#endif
