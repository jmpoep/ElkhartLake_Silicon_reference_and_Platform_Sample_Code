/** @file
  Common driver entry point implementation.
  
 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#include <Library/I2cDriverLib.h>


/**
Common driver entry point

@param [in] ImageHandle       Handle for the image
@param [in] pSystemTable      Address of the system table.

@retval EFI_SUCCESS           Image successfully loaded.

**/
EFI_STATUS
EFIAPI
I2cDlEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE * pSystemTable
  )
{
  EFI_LOADED_IMAGE_PROTOCOL * pLoadedImage;
  EFI_STATUS Status;

  //
  //  Enable unload support
  //
  Status = gBS->HandleProtocol (
                  gImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID *)&pLoadedImage
                  );
  if (!EFI_ERROR (Status)) {
    pLoadedImage->Unload = mDriverLib.pfnUnload;

    //
    //  Add the driver to the list of drivers
    //
    Status = EfiLibInstallDriverBindingComponentName2 (
               ImageHandle,
               pSystemTable,
               mDriverLib.pDriverBindingProtocol,
               ImageHandle,
               mDriverLib.pComponentNameProtocol,
               mDriverLib.pComponentName2Protocol
               );
    if ( !EFI_ERROR ( Status )) {
      DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
                "Installed: gEfiDriverBindingProtocolGuid on   0x%016lx\r\n",
                (UINT64)((UINTN)ImageHandle )));
      if ( NULL != mDriverLib.pComponentNameProtocol ) {
        DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
                  "Installed: gEfiComponentNameProtocolGuid on   0x%016lx\r\n",
                  (UINT64)((UINTN)ImageHandle )));
      }
      if ( NULL != mDriverLib.pComponentName2Protocol ) {
        DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
                  "Installed: gEfiComponentName2ProtocolGuid on   0x%016lx\r\n",
                  (UINT64)((UINTN)ImageHandle )));
      }
    }
  }

  //
  //  Return the image loaded status
  //
  return Status;
}
