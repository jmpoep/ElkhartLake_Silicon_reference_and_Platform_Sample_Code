//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Platform status code implementation.

Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "PlatformStatusCodeHandlerSmm.h"

EFI_SMM_RSC_HANDLER_PROTOCOL  *mRscHandlerProtocol       = NULL;

/**
  Entry point of SMM Status Code Driver.

  This function is the entry point of SMM Status Code Driver.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
StatusCodeHandlerSmmEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmRscHandlerProtocolGuid,
                    NULL,
                    (VOID **) &mRscHandlerProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  if (PcdGetBool (PcdStatusCodeUsePostCode)) {
    mRscHandlerProtocol->Register (PostCodeStatusCodeReportWorker);
  }

  if (PcdGetBool (PcdStatusCodeUseBeep)) {
    mRscHandlerProtocol->Register (BeepStatusCodeReportWorker);
  }

  if (PcdGetBool (PcdStatusCodeUseSerialPortPlatform)) {
    //
    // Call Serial Port Lib API to initialize serial port.
    //
    Status = SerialPortInitialize ();
    ASSERT_EFI_ERROR (Status);
    mRscHandlerProtocol->Register (SerialStatusCodeReportWorker);
  }

  if (PcdGetBool (PcdStatusCodeUseTraceHub)) {
    mRscHandlerProtocol->Register (TraceHubStatusCodeReportWorker);
  }

  return EFI_SUCCESS;
}
