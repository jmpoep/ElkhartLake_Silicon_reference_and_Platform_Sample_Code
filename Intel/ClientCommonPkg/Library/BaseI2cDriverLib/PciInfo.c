/** @file
  Read PCI device information
  
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
  Read PCI device information

  This routine fills in the ::DL_PCI_INFO structure with the data
  from configuration space.

  @param [in] Controller          Handle for the controller.
  @param [in] DriverBindingHandle Handle for binding protocols.
  @param [in] Attributes          Attributes for OpenProtocol
  @param [in] pPciInfo            Address of a ::DL_PCI_INFO structure.
  @param [out] ppPciIo            Optional address to receive the EFI_PCI_IO_PROTCOL,
                                  The caller must close the PCI I/O protocol if this
                                  address is not NULL.

  @retval EFI_SUCCESS   The structure was initialized.

**/
EFI_STATUS
DlPciInfo (
  IN EFI_HANDLE Controller,
  IN EFI_HANDLE DriverBindingHandle,
  IN UINT32 Attributes,
  IN DL_PCI_INFO * pPciInfo,
  OUT EFI_PCI_IO_PROTOCOL ** ppPciIo
  )
{
  EFI_PCI_IO_PROTOCOL * pPciIo;
  EFI_STATUS Status;

  //
  //  Determine if this is a PCI device.
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID**)&pPciIo,
                  DriverBindingHandle,
                  Controller,
                  Attributes );
  if ( !EFI_ERROR ( Status )) {
    //
    //  Read the vendor and device ID fields
    //
    Status = pPciIo->Pci.Read ( pPciIo,
                                EfiPciIoWidthUint32,
                                PCI_VENDOR_ID_OFFSET,
                                1,
                                (UINT32 *)&pPciInfo->VendorID );

    //
    //  Read the class code and revision fields
    //
    if ( !EFI_ERROR ( Status )) {
      Status = pPciIo->Pci.Read ( pPciIo,
                                  EfiPciIoWidthUint32,
                                  PCI_REVISION_ID_OFFSET,
                                  1,
                                  (UINT32 *)&pPciInfo->Revision );
    }

    //
    //  Done with the PCI I/O protocol
    //
    if ( NULL != ppPciIo ) {
      //
      //  Hand the protocol to the caller if requested
      //  The caller must release the protocol when done.
      //
      *ppPciIo = pPciIo;
    }
  }

  //
  //  Return the operation status
  //
  return Status;
}
