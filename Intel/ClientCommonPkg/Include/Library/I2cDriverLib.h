/** @file
  Definitions for the Driver Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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

#ifndef _I2C_DRIVER_LIB_H
#define _I2C_DRIVER_LIB_H

//------------------------------------------------------------------------------
//  Specify the header files
//------------------------------------------------------------------------------

#include <Uefi.h>

#include <IndustryStandard/Pci.h>

#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>

#include <Protocol/DevicePath.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/PciIo.h>

//------------------------------------------------------------------------------
// Data Types
//------------------------------------------------------------------------------

/**
  PCI device information
**/
#pragma pack(1)
typedef struct
{
  UINT16 VendorID;        ///<  PCI-SIG <a href="http://www.pcisig.com/membership/vid_search/">vendor identification</a>
  UINT16 DeviceID;        ///<  Vendor specific device identification
  UINT8 Revision;         ///<  Hardware revision
  UINT8 ProgIf;           ///<  Programming interface
  UINT8 SubClass;         ///<  Device subclass
  UINT8 Class;            ///<  Class of device defined by <a href="http://www.pcisig.com/specifications/conventional/conventional_pci">PCI 2.2 Specification</a>
} DL_PCI_INFO;
#pragma pack()

/**
  Driver library control structure definition
**/
typedef struct
{
  //
  //  Component Name(2) Protocol support
  //
  CONST EFI_COMPONENT_NAME_PROTOCOL * pComponentNameProtocol;   ///<  Address of component name protocol
  CONST EFI_COMPONENT_NAME2_PROTOCOL * pComponentName2Protocol; ///<  Address of component name 2 protocol
  CONST EFI_UNICODE_STRING_TABLE * pControllerNameStringTable;  ///<  String table for ::DlGetControllerName
  CONST EFI_UNICODE_STRING_TABLE * pDriverNameStringTable;      ///<  String table for ::DlGetDriverName

  //
  //  Driver Binding Protocol support
  //
  EFI_DRIVER_BINDING_PROTOCOL * pDriverBindingProtocol;   ///<  Address of driver binding protocol

  //
  //  Loaded Image Protocol support
  //
  EFI_IMAGE_UNLOAD pfnUnload;               ///<  Driver unload routine
} DL_DRIVER_LIB;

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

extern CONST DL_DRIVER_LIB mDriverLib;  ///<  Driver library control structure

//------------------------------------------------------------------------------
// Component Name(2) Protocol API
//------------------------------------------------------------------------------

/**
  Locate a matching ACPI device path node

  This routine walks the device path attached to the ControllerHandle
  and determines if the last (non-end) device path node matches the ID
  passed to this function.
  Function will run comparison with both HID and CID. Single match is enough
  to report success.
  String IDs will be used instead of integer representation. If string 
  is invalid (null pointer, 0-length or not provided in device path), integer
  representation will be unpacked to string.

  @param [in] ControllerHandle          Controller Handle
  @param [in] Id                        The value to match against the CID/HID
                                        value in the ACPI_HID_DEVICE_PATH
                                        node.  This value is ignored when
                                        IdString is neither NULL nor zero-length
  @param [in] *IdString                 The value to match against the CID/HID
                                        value in the ACPI_HID_DEVICE_PATH
                                        node.

  @retval                               TRUE when either HID or CID matches, else FALSE

**/

BOOLEAN
EFIAPI
DlIsMatchingHidCid (
  EFI_HANDLE ControllerHandle,
  UINT32 Id,
  CONST CHAR8 * IdString OPTIONAL
  );

/**
  Retrieves a Unicode string that is the user readable name of the controller
  that is being managed by a driver.

  This function retrieves the user readable name of the controller specified by
  ControllerHandle and ChildHandle in the form of a Unicode string. If the
  driver specified by This has a user readable name in the language specified by
  Language, then a pointer to the controller name is returned in ControllerName,
  and EFI_SUCCESS is returned.  If the driver specified by This is not currently
  managing the controller specified by ControllerHandle and ChildHandle,
  then EFI_UNSUPPORTED is returned.  If the driver specified by This does not
  support the language specified by Language, then EFI_UNSUPPORTED is returned.

  @param [in] pThis             A pointer to the EFI_COMPONENT_NAME2_PROTOCOL or
                                EFI_COMPONENT_NAME_PROTOCOL instance.
  @param [in] ControllerHandle  The handle of a controller that the driver
                                specified by This is managing.  This handle
                                specifies the controller whose name is to be
                                returned.
  @param [in] ChildHandle       The handle of the child controller to retrieve
                                the name of.  This is an optional parameter that
                                may be NULL.  It will be NULL for device
                                drivers.  It will also be NULL for a bus drivers
                                that wish to retrieve the name of the bus
                                controller.  It will not be NULL for a bus
                                driver that wishes to retrieve the name of a
                                child controller.
  @param [in] pLanguage         A pointer to a Null-terminated ASCII string
                                array indicating the language.  This is the
                                language of the driver name that the caller is
                                requesting, and it must match one of the
                                languages specified in SupportedLanguages. The
                                number of languages supported by a driver is up
                                to the driver writer. Language is specified in
                                RFC 3066 or ISO 639-2 language code format.
  @param [out] ppControllerName A pointer to the Unicode string to return.
                                This Unicode string is the name of the
                                controller specified by ControllerHandle and
                                ChildHandle in the language specified by
                                Language from the point of view of the driver
                                specified by This.

  @retval EFI_SUCCESS           The Unicode string for the user readable name in
                                the language specified by Language for the
                                driver specified by This was returned in
                                DriverName.
  @retval EFI_INVALID_PARAMETER ControllerHandle is not a valid EFI_HANDLE.
  @retval EFI_INVALID_PARAMETER ChildHandle is not NULL and it is not a valid
                                EFI_HANDLE.
  @retval EFI_INVALID_PARAMETER Language is NULL.
  @retval EFI_INVALID_PARAMETER ControllerName is NULL.
  @retval EFI_UNSUPPORTED       The driver specified by This is not currently
                                managing the controller specified by
                                ControllerHandle and ChildHandle.
  @retval EFI_UNSUPPORTED       The driver specified by This does not support
                                the language specified by Language.

**/
EFI_STATUS
EFIAPI
DlGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL * pThis,
  IN  EFI_HANDLE ControllerHandle,
  IN OPTIONAL EFI_HANDLE ChildHandle,
  IN  CHAR8 * pLanguage,
  OUT CHAR16 ** ppControllerName
  );

/**
  Retrieves a Unicode string that is the user readable name of the driver.

  This function retrieves the user readable name of a driver in the form of a
  Unicode string. If the driver specified by This has a user readable name in
  the language specified by Language, then a pointer to the driver name is
  returned in DriverName, and EFI_SUCCESS is returned. If the driver specified
  by This does not support the language specified by Language,
  then EFI_UNSUPPORTED is returned.

  @param [in] pThis             A pointer to the EFI_COMPONENT_NAME2_PROTOCOL or
                                EFI_COMPONENT_NAME_PROTOCOL instance.
  @param [in] pLanguage         A pointer to a Null-terminated ASCII string
                                array indicating the language. This is the
                                language of the driver name that the caller is
                                requesting, and it must match one of the
                                languages specified in SupportedLanguages. The
                                number of languages supported by a driver is up
                                to the driver writer. Language is specified
                                in RFC 3066 or ISO 639-2 language code format.
  @param [out] ppDriverName     A pointer to the Unicode string to return.
                                This Unicode string is the name of the
                                driver specified by This in the language
                                specified by Language.

  @retval EFI_SUCCESS           The Unicode string for the Driver specified by
                                This and the language specified by Language was
                                returned in DriverName.
  @retval EFI_INVALID_PARAMETER Language is NULL.
  @retval EFI_INVALID_PARAMETER DriverName is NULL.
  @retval EFI_UNSUPPORTED       The driver specified by This does not support
                                the language specified by Language.

**/
EFI_STATUS
EFIAPI
DlGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL * pThis,
  IN  CHAR8 * pLanguage,
  OUT CHAR16 ** ppDriverName
  );

//------------------------------------------------------------------------------
// Loaded Image Protocol Support
//------------------------------------------------------------------------------

/**
Common driver entry point

@param [in] ImageHandle       Handle for the image
@param [in] pSystemTable      Address of the system table.

@retval EFI_SUCCESS           Image successfully loaded.

**/
EFI_STATUS
EFIAPI
DlEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE * pSystemTable
  );

/**
  Driver unload routine

  @param [in] ImageHandle       Handle for the image.

  @retval EFI_SUCCESS           Image may be unloaded

**/
EFI_STATUS
EFIAPI
DlDriverUnload (
  IN EFI_HANDLE ImageHandle
  );

//------------------------------------------------------------------------------
// PCI Support
//------------------------------------------------------------------------------

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
  );

//------------------------------------------------------------------------------

#endif  //  _I2C_DRIVER_LIB_H
