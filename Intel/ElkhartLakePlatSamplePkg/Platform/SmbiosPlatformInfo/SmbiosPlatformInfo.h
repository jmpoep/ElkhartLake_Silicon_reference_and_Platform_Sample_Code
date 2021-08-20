/** @file
  This file will containing the Header file and Platform Info String definintions.

  @par Revision Reference:
  SMBIOS Specification from DMTF: http://www.dmtf.org/standards/smbios
  Intel Framework Specifications, all available at: http://www.intel.com/technology/framework/spec.htm
  Unified Extensible Firmware Interface (UEFI) Specifications: http://www.uefi.org/specs/

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#ifndef _SMBIOS_PLATFORM_INFO_H_
#define _SMBIOS_PLATFORM_INFO_H_

#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/PciRootBridgeIo.h>
#include <PlatformBoardId.h>
#include <IndustryStandard/Pci30.h>
#include <SaRegs.h>
#include <Library/EcMiscLib.h>
#include <Library/EcLiteMiscLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/PciSegmentLib.h>
#include <Library/HobLib.h>
#include <Protocol/Spi.h>
#include <Library/GbeLib.h>
#include <Library/IoLib.h>
#include <Library/BiosIdLib.h>
#include <Library/HdaLib.h>
#include <PchPcieRpInfo.h>
#include <Register/SataRegs.h>
#include <Library/SataLib.h>
#include <Register/IgdRegs.h>


//
// BCD to Decimal Conversion
//
#define BCD_TO_DECIMAL(A)                      (((((A) >> 4) & 0xF) * 10) + ((A) & 0xF))

//
// Default Strings required for System Info - TYPE 1
//
#define SYSINFO_TYPE01_PRODUCT_NAME             L"Elkhart Lake Embedded Platform"
#define SYSINFO_TYPE01_VERSION                  L"0.1"
#define SYSINFO_TYPE01_FAMILY                   L"Elkhart Lake Embedded System"


//
// TYPE1 related defines and below is sync with WIST ASL method
//
#define SUPPORTED_INTEL_WLAN_DEVICES {\
  0x095A, 0x095B, 0x3165, 0x3166,\
  0x08B0, 0x08B1, 0x08B2, 0x08B3, 0x08B4, 0x08B5, 0x08B6,\
  0x24F3, 0x24F4, 0x24F5, 0x24F6, 0x24FB, 0x24FD\
  }

#define SMBIOS_TYPE1_SYSTEM_UUID_VARIABLE       (L"SmbiosType1SystemUuid")

//
// Default Strings required for System Info - TYPE 12
//
#define SYSTEM_OPTION_TYPE12_STRING             L"J6H1:1-X Boot with Default; J8H1:1-X BIOS RECOVERY"

//
// Default Strings required for Port Info - TYPE 8
//
/* Port Connector Info               { IsPublishRequired, InternalDesignator,             InternalConnectorType,         ExternalDesignator,            InternalConnectorType,       PortType } */
#define PORT_INFO_KEYBOARD           { NotRequired,       L"None",                        PortConnectorTypeNone,         L"Keyboard",                   PortConnectorTypePS2,        PortTypeKeyboard }
#define PORT_INFO_MOUSE              { NotRequired,       L"None",                        PortConnectorTypeNone,         L"Mouse",                      PortConnectorTypePS2,        PortTypeMouse    }
#define PORT_INFO_COM1               { NotRequired,       L"None",                        PortConnectorTypeOther,        L"COM 1",                      PortConnectorTypeNone,       PortTypeSerial16550ACompatible }
#define PORT_INFO_VIDEO              { Required,          L"J1A2B",                       PortConnectorTypeOther,        L"Video",                      PortConnectorTypeDB15Female, PortTypeVideoPort }
#define PORT_INFO_HDMI               { Required,          L"J3A2",                        PortConnectorTypeOther,        L"HDMI",                       PortConnectorTypeNone,       PortTypeVideoPort }
#define PORT_INFO_USB1               { Required,          L"None",                        PortConnectorTypeNone,         L"USB1.1 - 1#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB2               { Required,          L"None",                        PortConnectorTypeNone,         L"USB1.1 - 2#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB3               { Required,          L"None",                        PortConnectorTypeNone,         L"USB1.1 - 3#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB4               { Required,          L"None",                        PortConnectorTypeNone,         L"USB1.1 - 4#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB5               { Required,          L"None",                        PortConnectorTypeNone,         L"USB1.1 - 5#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB201             { Required,          L"None",                        PortConnectorTypeNone,         L"USB2.0 - 1#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_USB202             { Required,          L"None",                        PortConnectorTypeNone,         L"USB2.0 - 2#",                PortConnectorTypeUsb,        PortTypeUsb }
#define PORT_INFO_NETWORK            { Required,          L"None",                        PortConnectorTypeNone,         L"Ethernet",                   PortConnectorTypeRJ45,       PortTypeNetworkPort }
#define PORT_INFO_SATA0              { Required,          L"J8J1",                        PortConnectorTypeNone,         L"SATA Port 0 Direct Connect", PortConnectorTypeSasSata,    PortTypeSata }
#define PORT_INFO_ESATA4             { Required,          L"J7J1",                        PortConnectorTypeNone,         L"eSATA Port 4",               PortConnectorTypeSasSata,    PortTypeSata }
#define PORT_INFO_ESATA3             { Required,          L"J6J1",                        PortConnectorTypeNone,         L"eSATA Port 3",               PortConnectorTypeSasSata,    PortTypeSata }
#define PORT_INFO_SATA2              { Required,          L"J7G1 - SATA Port 2",          PortConnectorTypeSasSata,      L"None",                       PortConnectorTypeNone,       PortTypeSata }
#define PORT_INFO_SATA1              { Required,          L"J7G2 - SATA Port 1",          PortConnectorTypeSasSata,      L"None",                       PortConnectorTypeNone,       PortTypeSata }
#define PORT_INFO_ACIN               { Required,          L"J1F2",                        PortConnectorTypeNone,         L"AC IN",                      PortConnectorTypeOther,      PortTypeOther }
#define PORT_INFO_PCHJTAG            { Required,          L"J5B1 - PCH JTAG",             PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_PORT80             { Required,          L"J9A1 - TPM/PORT 80",          PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_2X8HEADER          { Required,          L"J9E4 - HDA 2X8 Header",       PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_8PINHEADER         { Required,          L"J9E7 - HDA 8Pin Header",      PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_HDAHDMI            { Required,          L"J8F1 - HDA HDMI",             PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_MKEYBOARD          { Required,          L"J9E3 - Scan Matrix Keyboard", PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_SPI                { Required,          L"J8E1 - SPI Program",          PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_LPCDOCKING         { Required,          L"J9E5 - LPC Hot Docking",      PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_SIDEBAND           { Required,          L"J9G2 - LPC SIDE BAND",        PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_LPCSLOT            { Required,          L"J8F2 - LPC Slot",             PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_PCHXDP             { Required,          L"J8H3 - PCH XDP",              PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_SATAPOWER          { Required,          L"J6H1 - SATA Power",           PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_FPHEADER           { Required,          L"J5J1 - FP Header",            PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_ATXPOWER           { Required,          L"J4H1 - ATX Power",            PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_AVMC               { Required,          L"J1J3 - AVMC",                 PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_BATTB              { Required,          L"J1H1 - BATT B",               PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_BATTA              { Required,          L"J1H2 - BATT A",               PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_CPUFAN             { Required,          L"J2G1 - CPU Fan",              PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_XDP                { Required,          L"J1D3 - XDP",                  PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_MEMORY1            { Required,          L"J4V1 - Memory Slot 1",        PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_MEMORY2            { Required,          L"J4V2 - Memory Slot 2",        PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
#define PORT_INFO_FANPWR             { Required,          L"J4C1 - FAN PWR",              PortConnectorTypeOther,        L"None",                       PortConnectorTypeNone,       PortTypeOther }
//
// Below Port Info can be added if it is really Required
//
//#define PORT_INFO_IDE1               { Required,          L"None",                        PortConnectorTypeOnboardIde,   L"PATA",                         PortConnectorTypeNone,       PortTypeOther }
//#define PORT_INFO_INFRARED           { Required,          L"None",                        PortConnectorTypeOther,        L"Infrared",                     PortConnectorTypeNone,       PortTypeOther }
//#define PORT_INFO_SDVO               { Required,          L"None",                        PortConnectorTypeOther,        L"Serial-Digital-Video-Out",     PortConnectorTypeNone,       PortTypeOther }
//#define PORT_INFO_LINEIN             { Required,          L"None",                        PortConnectorTypeOther,        L"Audio Line In",                PortConnectorTypeNone,       PortTypeOther }
//#define PORT_INFO_LINEOUT            { Required,          L"None",                        PortConnectorTypeOther,        L"Audio Line Out",               PortConnectorTypeNone,       PortTypeOther }

//
// Below Device Info can be added if it is really required
//
//#define ONBOARD_INFO_SATA_CONTROLLER           { REQUIRED,          L"To Be Filled by O.E.M.",  OnBoardDeviceTypeSATAController,    ENABLED      }

//
// Default Strings required for Language Info - TYPE 13
//
#define BIOS_LANG_INFO_LANGUAGES_LONG     { L"en|US|iso8859-1" }
#define BIOS_LANG_INFO_LANGUAGES_ABBR     { L"enUS" }
//
// Default Strings required for Portable Battery Info - TYPE 22
//
/*      Portable Battery Info             { IsPublishRequired, BatteryType, Location,   Manufacturer,           ManufactureDate, SerialNumber, DevName,          DevChemistry,                        DevCapacity, Voltage, SbdsVersion,    MaxErrorInBatteryData, SbdsSerialNumber, SbdsManufactureDate, SbdsDeviceChemistry,    CapacityMultiplier, Oem }*/
#define PORTABLE_BATTERY_INFO_REAL1       { NotRequired,       Real1,       L"Real 1",  L"E-One Moli Energy",   L"01/01/2017",   L"FSPK50074", L"MOLICEL",       PortableBatteryDeviceChemistryOther, 0,           0,       L"SBDSVersion", 0xff,                  0,                0,                   L"SBDSDeviceChemistry", 1,                  0   }
#define PORTABLE_BATTERY_INFO_REAL2       { NotRequired,       Real2,       L"Real 2",  L"E-One Moli Energy",   L"01/01/2017",   L"FSPK50074", L"MOLICEL",       PortableBatteryDeviceChemistryOther, 0,           0,       L"SBDSVersion", 0xff,                  0,                0,                   L"SBDSDeviceChemistry", 1,                  0   }
#define PORTABLE_BATTERY_INFO_VIRTUAL     { NotRequired,       Virtual,     L"Virtual", L"-Virtual Battery 0-", L"01/01/2017",   L"Battery 0", L"CRB Battery 0", PortableBatteryDeviceChemistryOther, 0xffff,      0x2710,  L"SBDSVersion", 0xff,                  0,                0,                   L"SBDSDeviceChemistry", 1,                  0   }
//
// Default Strings required for Cooling Device Info - TYPE 27
//
/*      Cooling Device Info               { IsPublishRequired, Type,                            Status,                Group,  Oem, Speed,  Description         } */
#define COOLING_DEVICE_INFO1              { Required,          CoolingDeviceTypeChipFan,        CoolingDeviceStatusOk, 0x01,   0x0, 0x8000, L"Cooling Device 1" }
#define COOLING_DEVICE_INFO2              { Required,          CoolingDeviceTypePassiveCooling, CoolingDeviceStatusOk, 0x01,   0x0, 0x8000, L"Cooling Device 2" }
//
// Default Strings required for OnBoard Device Extended Info - TYPE 41
//
#define ONBOARD_DEV_INFO_DESIGNATION      L"To Be Filled by O.E.M."
/*      OnBoard Device Extended Info      { IsPublishRequired, Designation,                   DeviceType,                               DeviceStatus, DeviceInstance, Segment, Bus,                        DevFunc                           } */
#define ONBOARD_EXT_INFO_VIDEO            { Required,          ONBOARD_DEV_INFO_DESIGNATION,  OnBoardDeviceExtendedTypeVideo,           Enabled,      0x0,            0x0,     SA_IGD_BUS,                 (SA_IGD_DEV << 3) | (SA_IGD_FUN_0) }
#define ONBOARD_EXT_INFO_ETHERNET         { Required,          ONBOARD_DEV_INFO_DESIGNATION,  OnBoardDeviceExtendedTypeEthernet,        Enabled,      0x0,            0x0,     DEFAULT_PCI_BUS_NUMBER_PCH, 0x0 }
#define ONBOARD_EXT_INFO_SOUND            { Required,          ONBOARD_DEV_INFO_DESIGNATION,  OnBoardDeviceExtendedTypeSound,           Enabled,      0x0,            0x0,     DEFAULT_PCI_BUS_NUMBER_PCH, 0x0 }
#define ONBOARD_EXT_INFO_SATA             { Required,          ONBOARD_DEV_INFO_DESIGNATION,  OnBoardDeviceExtendedTypeSATAController,  Enabled,      0x0,            0x0,     DEFAULT_PCI_BUS_NUMBER_PCH, 0x0 }

#define PCIE_DEV_1 PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1
#define PCIE_DEV_2 PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2
#define PCIE_DEV_3 PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3

#define PCIE_FUN_1 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1
#define PCIE_FUN_2 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_2
#define PCIE_FUN_3 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_3
#define PCIE_FUN_4 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_4
#define PCIE_FUN_5 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_5
#define PCIE_FUN_6 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_6
#define PCIE_FUN_7 PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_7

#endif // _SMBIOS_PLATFORM_INFO_H_
