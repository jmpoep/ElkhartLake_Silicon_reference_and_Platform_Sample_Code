/** @file
  Trusted Channel Message Definitions.

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

@par Specification
**/

#ifndef _TRUSTED_CHANNEL_H_
#define _TRUSTED_CHANNEL_H_

#include "DataServicesMsg.h"
#include <Base.h>
#include <Uefi.h>

#define TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE  32

#pragma pack(push, 1)

typedef struct _TRUSTED_CHANNEL_BIOS_HEADER {
  UINT8                Signature[TRUSTED_CHANNEL_HMAC_SHA256_SIGNATURE_SIZE];  ///< HMAC-SHA2 of the message
                                                                               ///< Note: This signature is not part of the hash
  UINT32               MonotonicCounter;                                       ///< Counter value of the request
                                                                               ///< This counter is incremented for each request
  BIOS_STORAGE_COMMAND Command;                                                ///< The command and response fields
} TRUSTED_CHANNEL_BIOS_HEADER;

typedef struct _TRUSTED_CHANNEL_BIOS_REQUEST_HEADER {
  TRUSTED_CHANNEL_BIOS_HEADER  TrustedHeader;
  UINT8                        Reserved1;
  UINT16                       Reserved2;
} TRUSTED_CHANNEL_BIOS_REQUEST_HEADER;

typedef struct _TRUSTED_CHANNEL_BIOS_RESPONSE_HEADER {
  TRUSTED_CHANNEL_BIOS_HEADER  TrustedHeader;
  UINT8                        Status;                                         ///< Command status
  UINT16                       Reserved2;
} TRUSTED_CHANNEL_BIOS_RESPONSE_HEADER;

///
/// Trusted Channel BIOS Storage Message
///
typedef struct {
  TRUSTED_CHANNEL_BIOS_REQUEST_HEADER  Header;
  BIOS_STORAGE_REQUEST_BODY            Body;
} BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST;

typedef struct {
  TRUSTED_CHANNEL_BIOS_RESPONSE_HEADER Header;
  BIOS_STORAGE_RESPONSE_BODY           Body;
} BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE;

typedef union {
  BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST     Request;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE    Response;
} BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER;

#pragma pack(pop)

#endif
