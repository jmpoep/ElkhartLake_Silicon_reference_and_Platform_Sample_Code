/** @file
  This driver will determine the default string setting for SMBIOS tables.

  @par Revision Reference:
  SMBIOS Specification from DMTF: http://www.dmtf.org/standards/smbios
  Intel Framework Specifications, all available at: http://www.intel.com/technology/framework/spec.htm
  Unified Extensible Firmware Interface (UEFI) Specifications: http://www.uefi.org/specs/

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _SMBIOS_MISC_STRINGS_H_
#define _SMBIOS_MISC_STRINGS_H_
///
/// String references in SMBIOS tables. This eliminates the need for pointers.
/// See "Text strings" related information in the DMTF SMBIOS Specification
///
#define SMBIOS_MISC_STRING_NULL                     0
#define SMBIOS_MISC_STRING_1                        1
#define SMBIOS_MISC_STRING_2                        2
#define SMBIOS_MISC_STRING_3                        3
#define SMBIOS_MISC_STRING_4                        4
#define SMBIOS_MISC_STRING_5                        5
#define SMBIOS_MISC_STRING_6                        6
#define SMBIOS_MISC_STRING_7                        7
#define SMBIOS_MISC_STRING_8                        8
#define SMBIOS_MISC_STRING_9                        9

///
/// Non-static SMBIOS table data to be filled later with a dynamically generated value
///
#define TO_BE_FILLED                                0
#define TO_BE_FILLED_STRING                         " "        ///< Initial value should not be NULL
#define TO_BE_FILLED_BY_OEM_STR                     L"To Be Filled by O.E.M."

///
/// SMBIOS_TABLE_TYPE00 Default Strings
///
///
#define SMBIOS_MISC_TYPE00_VENDOR                   L"Intel Corporation"
#define SMBIOS_MISC_TYPE00_BIOS_VERSION             L"ElkhartLake Client Platform BIOS"
#define SMBIOS_MISC_TYPE00_BIOS_RELEASE_DATE        L"01/01/2014"

typedef struct {
  CHAR16 *Vendor;
  CHAR16 *BiosVersion;
  CHAR16 *BiosReleaseDate;
} SMBIOS_TABLE_TYPE00_STRINGS;

///
/// SMBIOS_TABLE_TYPE01 Default Strings
///
#define SMBIOS_MISC_TYPE01_MANUFACTURER             L"Intel Corporation"
#define SMBIOS_MISC_TYPE01_SERIAL_NUMBER            L"System Serial Number"
#define SMBIOS_MISC_TYPE01_SKU_NUMBER               L"System SKU Number"

typedef struct {
  CHAR16 *Manufacturer;
  CHAR16 *ProductName;
  CHAR16 *Version;
  CHAR16 *SerialNumber;
  CHAR16 *SkuNumber;
  CHAR16 *Family;
} SMBIOS_TABLE_TYPE01_STRINGS;

///
/// SMBIOS_TABLE_TYPE02 Default Strings
///
#define SMBIOS_MISC_TYPE02_BOARD_SERIAL_NUMBER      L"Base Board Serial Number"
#define SMBIOS_MISC_TYPE02_BOARD_ASSET_TAG          L"Base Board Asset Tag"

typedef struct {
  CHAR16 *Manufacturer;
  CHAR16 *ProductName;
  CHAR16 *Version;
  CHAR16 *SerialNumber;
  CHAR16 *AssetTag;
  CHAR16 *LocationInChassis;
} SMBIOS_TABLE_TYPE02_STRINGS;

///
/// SMBIOS_TABLE_TYPE03 Default Strings
///
#define SMBIOS_MISC_CHASSIS_SERIAL_NUMBER           L"Chassis Serial Number"
#define SMBIOS_MISC_CHASSIS_ASSET_TAG               L"Chassis Asset Tag"

typedef struct {
  CHAR16 *Manufacturer;
  CHAR16 *Version;
  CHAR16 *SerialNumber;
  CHAR16 *AssetTag;
} SMBIOS_TABLE_TYPE03_STRINGS;

///
/// SMBIOS_TABLE_TYPE08 Default Strings
///
#define SMBIOS_MISC_PORT_TOKEN_KEYBOARD             0x01
#define SMBIOS_MISC_PORT_TOKEN_MOUSE                0x02
#define SMBIOS_MISC_PORT_TOKEN_COM1                 0x03
#define SMBIOS_MISC_PORT_TOKEN_VIDEO                0x04
#define SMBIOS_MISC_PORT_TOKEN_HDMI                 0x05
#define SMBIOS_MISC_PORT_TOKEN_USB1                 0x06
#define SMBIOS_MISC_PORT_TOKEN_USB2                 0x07
#define SMBIOS_MISC_PORT_TOKEN_USB3                 0x08
#define SMBIOS_MISC_PORT_TOKEN_USB4                 0x09
#define SMBIOS_MISC_PORT_TOKEN_USB5                 0x0A
#define SMBIOS_MISC_PORT_TOKEN_USB201               0x0B
#define SMBIOS_MISC_PORT_TOKEN_USB202               0x0C
#define SMBIOS_MISC_PORT_TOKEN_NETWORK              0x0D
#define SMBIOS_MISC_PORT_TOKEN_IDE1                 0x0E
#define SMBIOS_MISC_PORT_TOKEN_SATA0                0x0F
#define SMBIOS_MISC_PORT_TOKEN_ESATA4               0x10
#define SMBIOS_MISC_PORT_TOKEN_ESATA3               0x11
#define SMBIOS_MISC_PORT_TOKEN_ACIN                 0x12
#define SMBIOS_MISC_PORT_TOKEN_PCHJTAG              0x13
#define SMBIOS_MISC_PORT_TOKEN_PORT80               0x14
#define SMBIOS_MISC_PORT_TOKEN_2X8HEADER            0x15
#define SMBIOS_MISC_PORT_TOKEN_8PINHEADER           0x16
#define SMBIOS_MISC_PORT_TOKEN_HDAHDMI              0x17
#define SMBIOS_MISC_PORT_TOKEN_MKEYBOARD            0x18
#define SMBIOS_MISC_PORT_TOKEN_SPI                  0x19
#define SMBIOS_MISC_PORT_TOKEN_LPCDOCKING           0x1A
#define SMBIOS_MISC_PORT_TOKEN_SIDEBAND             0x1B
#define SMBIOS_MISC_PORT_TOKEN_LPCSLOT              0x1C
#define SMBIOS_MISC_PORT_TOKEN_PCHXDP               0x1D
#define SMBIOS_MISC_PORT_TOKEN_INFRARED             0x1E
#define SMBIOS_MISC_PORT_TOKEN_SDVO                 0x1F
#define SMBIOS_MISC_PORT_TOKEN_LINEIN               0x20
#define SMBIOS_MISC_PORT_TOKEN_LINEOUT              0x21
#define SMBIOS_MISC_PORT_TOKEN_SATA2                0x22
#define SMBIOS_MISC_PORT_TOKEN_SATA1                0x23
#define SMBIOS_MISC_PORT_TOKEN_SATAPOWER            0x24
#define SMBIOS_MISC_PORT_TOKEN_FPHEADER             0x25
#define SMBIOS_MISC_PORT_TOKEN_ATXPOWER             0x26
#define SMBIOS_MISC_PORT_TOKEN_AVMC                 0x27
#define SMBIOS_MISC_PORT_TOKEN_BATTB                0x28
#define SMBIOS_MISC_PORT_TOKEN_BATTA                0x29
#define SMBIOS_MISC_PORT_TOKEN_CPUFAN               0x2A
#define SMBIOS_MISC_PORT_TOKEN_XDP                  0x2B
#define SMBIOS_MISC_PORT_TOKEN_MEMORY1              0x2C
#define SMBIOS_MISC_PORT_TOKEN_MEMORY2              0x2D
#define SMBIOS_MISC_PORT_TOKEN_FANPWR               0x2E
typedef struct {
  CHAR16 *InternalReferenceDesignator;
  CHAR16 *ExternalReferenceDesignator;
} SMBIOS_TABLE_TYPE8_STRINGS;

///
/// SMBIOS_TABLE_TYPE9 Default Strings
///
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE0         0x43
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE0               L"PCI-Express 0"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE1         0x44
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE1               L"PCI-Express 1"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE2         0x45
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE2               L"PCI-Express 2"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE3         0x46
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE3               L"PCI-Express 3"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE4         0x47
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE4               L"PCI-Express 4"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE5         0x48
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE5               L"PCI-Express 5"
#define SMBIOS_MISC_SYSTEM_SLOT_TOKEN_PCIE6         0x49
#define SMBIOS_MISC_SYSTEM_SLOT_PCIE6               L"PCI-Express 6"

typedef struct {
  CHAR16 *SlotDesignation;
} SMBIOS_TABLE_TYPE9_STRINGS;

///
/// SMBIOS_TABLE_TYPE12 Default Strings
///
typedef struct {
  CHAR16 *StringCount;
} SMBIOS_TABLE_TYPE12_STRINGS;

///
/// SMBIOS_TABLE_TYPE13 Default Strings
///
typedef struct {
  CHAR16 *CurrentLanguages;
} SMBIOS_TABLE_TYPE13_STRINGS;

///
/// SMBIOS_TABLE_TYPE22 Default Strings
///
#define SMBIOS_MISC_PROTABLE_BATTERY_TOKEN_VIRTUAL                    0x60
#define SMBIOS_MISC_PROTABLE_BATTERY_TOKEN_REAL1                      0x61
#define SMBIOS_MISC_PROTABLE_BATTERY_TOKEN_REAL2                      0x62

typedef struct {
  CHAR16 *Location;
  CHAR16 *Manufacturer;
  CHAR16 *ManufacturerDate;
  CHAR16 *SerialNumber;
  CHAR16 *DeviceName;
} SMBIOS_TABLE_TYPE22_STRINGS;

///
/// SMBIOS_TABLE_TYPE27 Default Strings
///
#define SMBIOS_MISC_COOLING_DEVICE_DESCRIPTION                        L" "
#define SMBIOS_MISC_TEMP_PROBE_HANDLE                                 0x0B

typedef struct {
  CHAR16 *Description;
} SMBIOS_TABLE_TYPE27_STRINGS;

///
/// SMBIOS_TABLE_TYPE39 Default Strings
///
typedef struct {
  CHAR16 *Location;
  CHAR16 *DeviceName;
  CHAR16 *Manufacturer;
  CHAR16 *SerialNumber;
  CHAR16 *AssetTagNumber;
  CHAR16 *ModelPartNumber;
  CHAR16 *RevisionLevel;
} SMBIOS_TABLE_TYPE39_STRINGS;

///
/// SMBIOS_TABLE_TYPE41 Default Strings
///
typedef struct {
  CHAR16 *DescriptionString;
} SMBIOS_TABLE_TYPE41_STRINGS;

#endif
