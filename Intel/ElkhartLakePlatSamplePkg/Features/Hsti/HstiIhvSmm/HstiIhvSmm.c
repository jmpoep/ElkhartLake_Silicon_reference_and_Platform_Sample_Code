/** @file
  This file contains SMM driver for testing HSTI

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

#include "HstiIhvSmm.h"

EFI_SMM_VARIABLE_PROTOCOL *mSmmVariable;

/**
  Read HSTI Smm data from cached results
**/
VOID
ReadData (
  VOID
  )
{
  EFI_STATUS  Status;
  UINT32      StatusResult;

  StatusResult =  CheckSecurePchSmmConfiguration ();
  //
  // Save Results to be processed by SecurePchConfiguration (HSTI DXE Driver)
  //
  Status = mSmmVariable->SmmSetVariable (
                           L"SecurePchSmmVariableName",
                           &gHstiSmmVariableGuid,
                           EFI_VARIABLE_BOOTSERVICE_ACCESS,
                           sizeof (StatusResult),
                           &StatusResult
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SecurePchSmmVariable: Not Set\n"));
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  The HSTI HVI SMM driver's entry point.

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval other           Some error occurs when executing this entry point.
**/
EFI_STATUS
EFIAPI
HstiIhvSmmEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmVariableProtocolGuid,
                    NULL,
                    (VOID **) &mSmmVariable
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Unable to Locate EfiSmmVariableProtocolGuid Protocol\n"));
    ASSERT_EFI_ERROR (Status);
    return (Status);
  }

  DEBUG ((DEBUG_INFO, "HSTI SMM Driver Checkpoint Tests\n"));
  DEBUG ((DEBUG_INFO, "  Secure PCH SMM P2SB Configuration\n"));

  ReadData ();

  return EFI_SUCCESS;
}
