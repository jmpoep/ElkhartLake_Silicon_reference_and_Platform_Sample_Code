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

#include "PlatformStatusCodeHandlerPei.h"

/**
  Entry point of Status Code PEIM.

  This function is the entry point of this Status Code PEIM.
  It initializes supported status code devices and installs PostCode and Beep Status Code PPI.

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCESS  The entry point of DXE IPL PEIM executes successfully.

**/
EFI_STATUS
EFIAPI
StatusCodeHandlerPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                  Status;
  EFI_PEI_RSC_HANDLER_PPI     *RscHandlerPpi;

  Status = PeiServicesLocatePpi (
             &gEfiPeiRscHandlerPpiGuid,
             0,
             NULL,
             (VOID **) &RscHandlerPpi
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Dispatch initialization request to sub-statuscode-devices.
  //
  if (PcdGetBool (PcdStatusCodeUsePostCode)) {
    Status = RscHandlerPpi->Register (PostCodeStatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  if (PcdGetBool (PcdStatusCodeUseBeep)) {
      Status = RscHandlerPpi->Register (BeepStatusCodeReportWorker);
      ASSERT_EFI_ERROR (Status);
  }

  if (PcdGetBool (PcdStatusCodeUseSerialPortPlatform)) {
    //
    // Call Serial Port Lib API to initialize serial port.
    //
    Status = SerialPortInitialize ();
    ASSERT_EFI_ERROR (Status);
    Status = RscHandlerPpi->Register (SerialStatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  if (PcdGetBool (PcdStatusCodeUseTraceHub)) {
    Status = RscHandlerPpi->Register (TraceHubStatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}

