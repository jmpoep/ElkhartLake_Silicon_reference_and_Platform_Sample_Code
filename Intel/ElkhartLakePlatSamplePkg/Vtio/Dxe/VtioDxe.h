/** @file
  VTIO DXE header file.

Copyright (c) 2017 - 2019, Intel Corporation. All rights reserved. <BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _VTIO_DXE_H_
#define _VTIO_DXE_H_

#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>

///
/// Secure Devices table for VTIO - Exposes the Secure controllers - XHCI and MIPI to OS via this table
///
#define EFI_ACPI_5_0_VTIO_TABLE_SIGNATURE  SIGNATURE_32('S', 'D', 'E', 'V')

#define EFI_VTIO_ACPI_TABLE_REVISION  1

#define NUMBER_OF_SECURE_CONTROLLERS  6
#define SECURE_CONTROLLER_INDEX_CIO2  0
#define SECURE_CONTROLLER_INDEX_ISP   1
#define SECURE_CONTROLLER_INDEX_HECI  2
#define SECURE_CONTROLLER_INDEX_SPI1  3
#define SECURE_CONTROLLER_INDEX_SPI2  4
#define SECURE_CONTROLLER_INDEX_HXCI  5

#define MAXIMUM_SENSOR_ENTRIES        2
#define MAXIMUM_XHCI_DEVICES          2
#define MAXIMUM_PATH_NAME_SIZE        49

#define EKpub_HANDLE 0x81010001

//
// Key value for HMAC-SHA-256 to generate E
//
GLOBAL_REMOVE_IF_UNREFERENCED CONST UINT8 mHmacSha256Key[8] = {
  0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

#pragma pack(push, 1)

typedef struct {
  UINT16  SensorInfo;
} SENSOR_INFO;

typedef struct {
  UINT16                 Version;
  UINT16                 ControllerCap;
  UINT8                  AFN; // Alternate Function Number
  UINT8                  Rsvd;
  UINT16                 Rsvd1;
  UINT16                 NumberofSensors;
  UINT16                 SensorEntrySize;
  SENSOR_INFO            SensorArray[2];
} CAP_STRUCT;

typedef struct {
  UINT8                  Type;
  UINT8                  Flags;
  UINT16                 Length;
  UINT16                 PciSegmentNumber;
  UINT16                 StartBusNumber;
  UINT16                 PciPathOffset;
  UINT16                 PciPathLength;
  UINT16                 CapabilityStructOffset; //Capability Structure Offset
  UINT16                 CapabilityStructLength; //Capability Structure Length
  UINT16                 PciPath;
  CAP_STRUCT             CapabilityStruct; // Capability Structure
} EFI_SECURE_CONTROLLER;

typedef struct {
  UINT16                VendorID;
  UINT16                DeviceID;
  UINT16                Revision;
  UINT8                 InterfaceNumber;
} USB_HID_STRUCT;

typedef struct {
  UINT8                Class;
  UINT8                SubClass;
  UINT8                Protocol;
  UINT16               AcpiPathStringOffset;
  UINT16               AcpiPathStringLength;
  UINT64               FirmwareHash[4];
  UINT8                AcpiPathName[MAXIMUM_PATH_NAME_SIZE];
} USB_CID_STRUCT;

typedef struct {
  UINT8                  Type;
  UINT16                 Length;
  UINT8                  Revision;
  UINT8                  Attributes;
  UINT8                  RootPortNumber;
  USB_HID_STRUCT         USBHidStruct;
  USB_CID_STRUCT         USBCidStruct;
} EFI_XHCI_SECURE_DEVICE_DESC;

typedef struct {
  UINT8                  Type;
  UINT16                 Length;
  UINT16                 ControllerCapability;
  UINT8                  AlternateFunctionNumber;
  UINT16                 Reserved1;
  UINT16                 Reserved2;
} EFI_XHCI_VENDOR_DEVICE_DESC;

typedef struct {
  UINT8                  Type;
  UINT8                  Flags;
  UINT16                 Length;
  UINT16                 DeviceIdentifierOffset;
  UINT16                 DeviceIdentifierLength;
  UINT16                 VendorSpecificInfoOffset;
  UINT16                 VendorSpecificInfoLength;
  UINT8                  AcpiPathName[MAXIMUM_PATH_NAME_SIZE];
} EFI_SDEV_USB_DEVICE_STRUCT;


typedef struct {
  UINT8                         Type;
  UINT8                         Flags;
  UINT16                        Length;
  UINT16                        PciSegmentNumber;
  UINT16                        StartBusNumber;
  UINT16                        PciPathOffset;
  UINT16                        PciPathLength;
  UINT16                        CapabilityStructOffset; //Capability Structure Offset
  UINT16                        CapabilityStructLength; //Capability Structure Length
  UINT16                        PciPath;
} EFI_XHCI_SECURE_CONTROLLER;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER         Header;
  EFI_SECURE_CONTROLLER               SecureController[NUMBER_OF_SECURE_CONTROLLERS];// Currently only 3 controllers are populated - modify this as when a new entry is made or existing enrty is deleted
} EFI_VTIO_ACPI_TABLE;

//
// NOTE NOTE : These declarations should be moved to BaseCryptLib.h after HMAC_SHA_256 is included in cryptopkg <<<
//

#pragma pack(pop)

/**
Main entry for this driver.
@retval EFI_SUCESS     This function always complete successfully.
**/
EFI_STATUS
EFIAPI
VtioRegisterEvents (
  VOID
  );

#endif
