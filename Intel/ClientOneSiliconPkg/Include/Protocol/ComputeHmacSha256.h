/** @file
  This file declares the Compute HMAC SHA256 Protocol

  This protocol allows the users to compute a HMAC SHA256 for a given message.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _COMPUTE_HMAC_SHA_256_PROTOCOL_H_
#define _COMPUTE_HMAC_SHA_256_PROTOCOL_H_

extern EFI_GUID gComputeHmacSha256ProtocolGuid;

///
/// Revision
///
#define COMPUTE_HMAC_SHA_256_PROTOCOL_REVISION  1

typedef struct _COMPUTE_HMAC_SHA_256_PROTOCOL  COMPUTE_HMAC_SHA_256_PROTOCOL;
/**
  Computes an HMAC SHA256 signature for a data message.

  @param[in]  HmacSha256Key   Pointer to the user-supplied key.
  @param[in]  KeySize         Key size in bytes.
  @param[in]  Data            The data buffer.
  @param[in]  DataSize        The size in bytes of data in the data buffer.
  @param[in, out] Signature   The HMAC SHA256 signature computed.

  @return     EFI_SUCCESS   The signature was computed successfully.
  @return     Others        Failed to compute the signature.
**/
typedef
EFI_STATUS
(EFIAPI *COMPUTE_HMAC_SHA_256)(
  IN CONST UINT8   *HmacSha256Key,
  IN       UINTN   KeySize,
  IN CONST VOID    *Data,
  IN       UINTN   DataSize,
  IN OUT   UINT8   *Signature
  );

///
/// Compute HMAC256 Protocol.
///
struct _COMPUTE_HMAC_SHA_256_PROTOCOL {
  COMPUTE_HMAC_SHA_256  ComputeHmacSha256Signature;
};

#endif
