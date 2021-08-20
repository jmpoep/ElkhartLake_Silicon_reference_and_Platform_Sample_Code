/** @file
  This is the main PEIM file for TXT. It represents an abstract outline of the
  steps required during PEI for enabling TXT. Each individual step is further
  abstracted behind a function call interface. This is intended to minimize
  the need to modify this file when porting TXT to future platforms.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Uefi.h>

/**
  TXT init after memory PEI module

  @retval EFI_SUCCESS  - always return EFI_SUCCESS
**/
EFI_STATUS
TxtInit (
  VOID
  );

/**
  AliasCheck for MRC

  @retval EFI_SUCCESS  - always return EFI_SUCCESS
**/

EFI_STATUS
EFIAPI
AliasCheck (
  VOID
  );

/**
  This is ClearSecretsBit entry point for MRC call.
**/
EFI_STATUS
EFIAPI
ClearSecretsBit (
  VOID
  );

/**
  This is SetPowerDownRequest entry point for MRC call.
**/
EFI_STATUS
EFIAPI
SetPowerDownRequest (
  VOID
  );

/**
  Determines whether or not SECRETS.STS bit is set in E2STS status register
**/
BOOLEAN
IsTxtSecretsSet (
  VOID
  );

/**
 TXT init after memory PEI module

 @retval EFI_SUCCESS  - always return EFI_SUCCESS
**/
EFI_STATUS
TxtInit (
  VOID
  )
{
  return EFI_UNSUPPORTED;
}

/**
  AliasCheck for MRC
**/

EFI_STATUS
EFIAPI
AliasCheck (
  VOID
  )
{
  return EFI_SUCCESS;
}

/**
  This is ClearSecretsBit entry point for MRC call.
**/
EFI_STATUS
EFIAPI
ClearSecretsBit (
  VOID
  )
{
  return EFI_SUCCESS;
}


/**
  This is SetPowerDownRequest entry point for MRC call.
**/
EFI_STATUS
EFIAPI
SetPowerDownRequest (
  VOID
  )
{
  return EFI_SUCCESS;
}

/**
  Determines whether or not SECRETS.STS bit is set in E2STS status register
**/
BOOLEAN
IsTxtSecretsSet (
  VOID
  )
{
  return FALSE;
}

