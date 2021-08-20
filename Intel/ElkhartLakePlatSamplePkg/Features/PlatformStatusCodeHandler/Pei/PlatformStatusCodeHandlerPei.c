//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Platform status code implementation.

Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>
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
  UINT8                       StatusCodeFlags;

  Status = PeiServicesLocatePpi (
             &gEfiPeiRscHandlerPpiGuid,
             0,
             NULL,
             (VOID **) &RscHandlerPpi
             );
  ASSERT_EFI_ERROR (Status);

  StatusCodeFlags = GetDebugInterface ();

  if (PcdGetBool (PcdStatusCodeUseRam)) {
    if (StatusCodeFlags & STATUS_CODE_USE_RAM) {
      RamDebugInitialize ();
    }
    Status = RscHandlerPpi->Register (RamStatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  if (PcdGetBool (PcdStatusCodeUseUsb3)) {
    if (StatusCodeFlags & STATUS_CODE_USE_USB3) {
      Status = Usb3DebugPortInitialize ();
    }
    ASSERT_EFI_ERROR (Status);
    Status = RscHandlerPpi->Register (Usb3StatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  if (PcdGetBool (PcdStatusCodeUseSerialIoUart)) {
    if (StatusCodeFlags & STATUS_CODE_USE_SERIALIO) {
      SerialIoUartDebugInit ();
    }
    Status = RscHandlerPpi->Register (SerialIoUartStatusCodeReportWorker);
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}

