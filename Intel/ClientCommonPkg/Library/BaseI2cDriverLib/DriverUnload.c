/** @file
  Common driver unload implementation.
  
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
  Driver unload routine

  @param [in] ImageHandle       Handle for the image.

  @retval EFI_SUCCESS           Image may be unloaded

**/
EFI_STATUS
EFIAPI
DlDriverUnload (
  IN EFI_HANDLE ImageHandle
  )
{
  UINTN Index;
  UINTN LengthInBytes;
  UINTN Max;
  EFI_HANDLE * pController;
  EFI_STATUS Status;

  //
  //  Assume success
  //
  Status = EFI_SUCCESS;

  //
  //  Use break instead of goto
  //
  pController = NULL;
  for ( ; ; ) {
    //
    //  Determine the buffer size
    //
    LengthInBytes = 0;
    Status = gBS->LocateHandle ( ByProtocol,
                                 mpDriverProtocol,
                                 NULL,
                                 &LengthInBytes,
                                 NULL );
    if ( EFI_BUFFER_TOO_SMALL != Status ) {
      DEBUG (( DEBUG_INIT | DEBUG_INFO,
                "No controllers found, Status: %r\r\n",
                Status ));
      Status = EFI_SUCCESS;
      break;
    }

    //
    //  One or more devices are present
    //
    pController = AllocateZeroPool ( LengthInBytes );
    if ( NULL == pController ) {
      Status = EFI_OUT_OF_RESOURCES;
      DEBUG (( DEBUG_ERROR | DEBUG_INIT | DEBUG_INFO,
                "Insufficient memory, failed handle buffer allocation\r\n" ));
      break;
    }

    //
    //  Get the lists of controllers
    //
    Status = gBS->LocateHandle ( ByProtocol,
                                 mpDriverProtocol,
                                 NULL,
                                 &LengthInBytes,
                                 pController );
    if ( EFI_ERROR ( Status )) {
      //
      //  Error getting handles
      //
      DEBUG (( DEBUG_ERROR | DEBUG_INIT | DEBUG_INFO,
              "Failure getting controller handles, Status: %r\r\n",
              Status ));
      break;
    }
      
    //
    //  Remove each of the driver instances
    //
    Max = LengthInBytes / sizeof ( pController[ 0 ]);
    for ( Index = 0; Max > Index; Index++ ) {
      Status = mDriverLib.pDriverBindingProtocol->Stop ( mDriverLib.pDriverBindingProtocol,
                                                         pController[ Index ],
                                                         0,
                                                         NULL );
      if ( EFI_ERROR ( Status )) {
        DEBUG (( DEBUG_ERROR | DEBUG_INIT | DEBUG_INFO,
                  "ERROR - Failed to stop the driver on handle %08x\r\n",
                  pController[ Index ]));
        break;
      }
    }
    break;
  }

  //
  // Free the handle array
  //
  if ( NULL != pController ) {
    FreePool ( pController );
  }

  //
  //  Remove the protocols installed by the EntryPoint routine.
  //
  if ( NULL != mDriverLib.pComponentName2Protocol ) {
    Status = gBS->UninstallMultipleProtocolInterfaces (
                ImageHandle,
                &gEfiComponentName2ProtocolGuid,
                mDriverLib.pComponentName2Protocol,
                NULL
                );
    if ( !EFI_ERROR ( Status )) {
      DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
              "Removed:   gEfiComponentName2ProtocolGuid from 0x%016lx\r\n",
              (UINT64)((UINTN)ImageHandle )));
    }
    else {
      DEBUG (( DEBUG_ERROR | DEBUG_POOL | DEBUG_INIT,
                  "ERROR - Failed to remove gEfiComponentName2ProtocolGuid from 0x%016lx, Status: %r\r\n",
                  (UINT64)((UINTN)ImageHandle ),
                  Status ));
    }
  }

  if (( !EFI_ERROR ( Status ))
    && ( NULL != mDriverLib.pComponentNameProtocol )) {
    Status = gBS->UninstallMultipleProtocolInterfaces (
                ImageHandle,
                &gEfiComponentNameProtocolGuid,
                mDriverLib.pComponentNameProtocol,
                NULL
                );
    if ( !EFI_ERROR ( Status )) {
      DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
                "Removed:   gEfiComponentNameProtocolGuid from 0x%016lx\r\n",
                (UINT64)((UINTN)ImageHandle )));
    }
    else {
      DEBUG (( DEBUG_ERROR | DEBUG_POOL | DEBUG_INIT,
                  "ERROR - Failed to remove gEfiComponentNameProtocolGuid from 0x%016lx, Status: %r\r\n",
                  (UINT64)((UINTN)ImageHandle ),
                  Status ));
    }
  }

  if ( !EFI_ERROR ( Status )) {
    Status = gBS->UninstallMultipleProtocolInterfaces (
                ImageHandle,
                &gEfiDriverBindingProtocolGuid,
                mDriverLib.pDriverBindingProtocol,
                NULL
                );
    if ( !EFI_ERROR ( Status )) {
      DEBUG (( DEBUG_POOL | DEBUG_INIT | DEBUG_INFO,
                "Removed:   gEfiDriverBindingProtocolGuid from 0x%016lx\r\n",
                (UINT64)((UINTN)ImageHandle )));
    }
    else {
      DEBUG (( DEBUG_ERROR | DEBUG_POOL | DEBUG_INIT,
                  "ERROR - Failed to remove gEfiDriverBindingProtocolGuid from 0x%016lx, Status: %r\r\n",
                  (UINT64)((UINTN)ImageHandle ),
                  Status ));
    }
  }

  //
  //  Return the unload status
  //
  return Status;
}
