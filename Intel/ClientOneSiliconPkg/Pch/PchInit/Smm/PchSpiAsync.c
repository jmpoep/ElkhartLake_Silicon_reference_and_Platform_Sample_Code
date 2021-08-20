/** @file
  PCH SPI Async SMI handler.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#include "PchInitSmm.h"

///
/// Global variables
///
GLOBAL_REMOVE_IF_UNREFERENCED PCH_SMI_DISPATCH_PROTOCOL     *mPchSmiDispatchProtocol;

/**
  This hardware SMI handler will be run every time the flash write/earse happens.

  @param[in] DispatchHandle       Not used

**/
VOID
EFIAPI
PchSpiAsyncCallback (
  IN  EFI_HANDLE                              DispatchHandle
  )
{
  //
  // Dummy SMI handler
  //
}

/**
  This fuction install SPI ASYNC SMI handler.

  @retval EFI_SUCCESS             Initialization complete.
**/
EFI_STATUS
EFIAPI
InstallPchSpiAsyncSmiHandler (
  VOID
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Handle;

  DEBUG ((DEBUG_INFO, "InstallPchSpiAsyncSmiHandler()\n"));

  ///
  /// Get the PCH SMM dispatch protocol
  ///
  mPchSmiDispatchProtocol = NULL;
  Status = gSmst->SmmLocateProtocol (&gPchSmiDispatchProtocolGuid, NULL, (VOID **) &mPchSmiDispatchProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Register an SpiAsync callback function
  ///
  Handle = NULL;
  Status = mPchSmiDispatchProtocol->SpiAsyncRegister (
                                      mPchSmiDispatchProtocol,
                                      PchSpiAsyncCallback,
                                      &Handle
                                      );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

