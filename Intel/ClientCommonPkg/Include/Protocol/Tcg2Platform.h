/** @file
 Ihis protocol is defined to abstract TPM2 platform behavior.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef __Tcg2_PLATFORM_H__
#define __Tcg2_PLATFORM_H__

#include <IndustryStandard/Tpm20.h>
#include <Protocol/Tcg2Protocol.h>

typedef struct _EFI_Tcg2_PLATFORM_PROTOCOL EFI_Tcg2_PLATFORM_PROTOCOL;

/**
  This service returns the platform auth value.

  @param[in]  This                     Indicates the calling context
  @param[out] AuthSize                 Tpm2 Auth size

  @retval EFI_SUCCESS            Auth size returned.
  @retval EFI_SECURITY_VIOLATION Can not return platform auth due to security reason.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_Tcg2_PLATFORM_GET_AUTH_SIZE) (
IN EFI_Tcg2_PLATFORM_PROTOCOL *This,
  OUT UINT16                    *AuthSize
  );

/**
  This service returns the Tpm2 auth value.

  Platform need figour out a way to decide if it is proper to publish Tpm2 auth value.

  @param[in]  This                     Indicates the calling context
  @param[in]  AuthHandle               TPM_RH_LOCKOUT, TPM_RH_ENDORSEMENT, TPM_RH_OWNER or TPM_RH_PLATFORM+{PP}
  @param[out] AuthValue                Tpm2 Auth value

  @retval EFI_SUCCESS            Tpm2 auth value returned.
  @retval EFI_SECURITY_VIOLATION Can not return Tpm2 auth value due to security reason.
  @retval EFI_UNSUPPORTED        Unsupported AuthHandle.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_Tcg2_PLATFORM_GET_AUTH_VALUE) (
IN EFI_Tcg2_PLATFORM_PROTOCOL *This,
  IN TPMI_RH_HIERARCHY_AUTH     AuthHandle,
  OUT TPM2B_AUTH                *AuthValue
  );

/**
  This service sets the Tpm2 auth value.

  Platform need figour out a way to decide if it is proper to set Tpm2 auth value.

  @param[in]  This                     Indicates the calling context
  @param[in]  AuthHandle               TPM_RH_LOCKOUT, TPM_RH_ENDORSEMENT, TPM_RH_OWNER or TPM_RH_PLATFORM+{PP}
  @param[in]  AuthValue                Tpm2 Auth value

  @retval EFI_SUCCESS            Tpm2 auth value set.
  @retval EFI_SECURITY_VIOLATION Can not set Tpm2 auth value due to security reason.
  @retval EFI_UNSUPPORTED        Unsupported AuthHandle.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_Tcg2_PLATFORM_SET_AUTH_VALUE) (
IN EFI_Tcg2_PLATFORM_PROTOCOL *This,
  IN TPMI_RH_HIERARCHY_AUTH     AuthHandle,
  IN TPM2B_AUTH                 *AuthValue
  );

struct _EFI_Tcg2_PLATFORM_PROTOCOL {
	EFI_Tcg2_PLATFORM_GET_AUTH_SIZE         GetAuthSize;
	EFI_Tcg2_PLATFORM_GET_AUTH_VALUE        GetAuthValue;
	EFI_Tcg2_PLATFORM_SET_AUTH_VALUE        SetAuthValue;
};

#endif // __Tcg2_PLATFORM_H__
