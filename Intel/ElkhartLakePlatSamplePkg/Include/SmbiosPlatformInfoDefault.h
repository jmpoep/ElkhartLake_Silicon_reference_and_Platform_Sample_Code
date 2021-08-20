/** @file
This file contains Default data for Platform SMBIOS tables. This file should not
be altered unless update in SMBIOS Specification.

@copyright
INTEL CONFIDENTIAL
Copyright 2017 - 2018 Intel Corporation.

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

This file contains 'Sample Driver' and is licensed as such under the terms
of your license agreement with Intel or your vendor. This file may not be
modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _SMBIOS_PLATFORM_INFO_DEFAULT_H_
#define _SMBIOS_PLATFORM_INFO_DEFAULT_H_

#include <SmbiosPlatformInfoDefinition.h>
#include <../Features/Smbios/SmbiosMiscDxe/SmbiosMiscStrings.h>
//
// String Macro Definitions for Default Data
//
#define TO_BE_FILLED                                0
#define DEFAULT_BIOSVENDOR_SEGMENT                  TO_BE_FILLED
#define DEFAULT_BIOSVENDOR_SIZE                     TO_BE_FILLED
/**
  MISC_BIOS_CHARACTERISTICS.BiosCharacteristics
  Bit0-1 Reserved1,
  Bit02 Unknown,
  Bit03 BiosCharacteristicsNotSupported,
  Bit04 IsaIsSupported,
  Bit05 McaIsSupported,
  Bit06 EisaIsSupported,
  Bit07 PciIsSupported,
  Bit08 PcmciaIsSupported,
  Bit09 PlugAndPlayIsSupported,
  Bit10 ApmIsSupported,
  Bit11 BiosIsUpgradable,
  Bit12 BiosShadowingAllowed,
  Bit13 VLVesaIsSupported,
  Bit14 EscdSupportIsAvailable,
  Bit15 BootFromCdIsSupported
  Bit16 SelectableBootIsSupported,
  Bit17 RomBiosIsSocketed,
  Bit18 BootFromPcmciaIsSupported,
  Bit19 EDDSpecificationIsSupported,
  Bit20 JapaneseNecFloppyIsSupported,
  Bit21 JapaneseToshibaFloppyIsSupported,
  Bit22 Floppy525_360IsSupported,
  Bit23 Floppy525_12IsSupported,
  Bit24 Floppy35_720IsSupported,
  Bit25 Floppy35_288IsSupported,
  Bit26 PrintScreenIsSupported,
  Bit27 Keyboard8042IsSupported,
  Bit28 SerialIsSupported,
  Bit29 PrinterIsSupported,
  Bit30 CgaMonoIsSupported,
  Bit31 NecPc98,
  Bit32-63 Reserved for BIOS/System Vendor
**/
#define DEFAULT_BIOSVENDOR_CHARS                    { 0,0,0,0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0 }
/**
  MISC_BIOS_CHARACTERISTICS_EXTENSION.BiosReserved
  Bit0 AcpiIsSupported,
  Bit1 UsbLegacyIsSupported,
  Bit2 AgpIsSupported,
  Bit3 I20BootIsSupported,
  Bit4 Ls120BootIsSupported,
  Bit5 AtapiZipDriveBootIsSupported,
  Bit6 Boot1394IsSupported,
  Bit7 SmartBatteryIsSupported
**/
#define DEFAULT_BIOSVENDOR_CHARS_EXT_BIOS           (UINT8)(BIT0 | BIT1 | BIT4 | BIT5)
/**
  MISC_BIOS_CHARACTERISTICS_EXTENSION.SystemReserved
  Bit0 BiosBootSpecIsSupported,
  Bit1 FunctionKeyNetworkBootIsSupported,
  Bit2 TargetContentDistributionEnabled,
  Bit3 UefiSpecificationSupported,
  Bit4 VirtualMachineSupported,
  Bit5-7 ExtensionByte2Reserved
**/
#define DEFAULT_BIOSVENDOR_CHARS_EXT_SYSTEM         (UINT8)(BIT0 | BIT1 | BIT2 | BIT3)
#define DEFAULT_BIOSVENDOR_EC_RELEASE               0xFF
#define DEFAULT_SYSINFO_PRODUCTNAME                 L"Client Platform"
#define DEFAULT_SYSINFO_VERSION                     L"0.1"
#define DEFAULT_SYSINFO_FAMILY                      L"Client System"
#define DEFAULT_BOARDINFO_PRODUCTNAME               L"RVP/SDS"
#define DEFAULT_BOARDINFO_MANUFACTURER              L"Intel Corporation"
#define DEFAULT_BOARDINFO_VERSION                   L"FAB"
#define DEFAULT_BOARDINFO_FLAGS                     { 1,0,0,0,0,0 }
#define DEFAULT_BOARDINFO_CHASSIS                   L"Part Component"
#define DEFAULT_CHASSISINFO_MANUFACTURER            L"Intel Corporation"
#define DEFAULT_CHASSISINFO_VERSION                 L"0.1"
#define DEFAULT_CHASSISINFO_OEM                     { 0,0,0,0 }
#define DEFAULT_CHASSISINFO_HEIGHT                  0
#define DEFAULT_CHASSISINFO_POWER_CORDS_NUM         1
#define DEFAULT_PORT_INFO_INT_EXT_DESIGNATOR        L"None"
/*      Default Port Info                           { IsPublishRequired, InternalDesignator,                   InternalConnectorType,  ExternalDesignator,                   InternalConnectorType, PortType     } */
#define DEFAULT_PORT_INFO                           { Required,          DEFAULT_PORT_INFO_INT_EXT_DESIGNATOR, PortConnectorTypeNone,  DEFAULT_PORT_INFO_INT_EXT_DESIGNATOR, PortConnectorTypeNone, PortTypeNone }
#define DEFAULT_ONBOARD_DEV_INFO_DESCRIPTION        L"To Be Filled by O.E.M."
#define DEFAULT_CONFIG_OPTIONS_STRING               L"JUMPER:OPTIONS; NA:NA"
#define DEFAULT_BIOS_LANG_INFO_LANGUAGES            { L"enUS" }
#define DEFAULT_BIOS_LANG_INFO_INSTALL_LANGUAGES    MAX_LANGUAGES
#define DEFAULT_PORTABLE_BATTERY_LOCATION           L"Battery Location"
#define DEFAULT_PORTABLE_BATTERY_MANUFACTURER       L"Battery Manufacturer"
#define DEFAULT_PORTABLE_BATTERY_MANUFACTURER_DATE  L"Battery Manufacture Date"
#define DEFAULT_PORTABLE_BATTERY_SERIAL_NUMBER      L"Battery Serial Number"
#define DEFAULT_PORTABLE_BATTERY_DEVICE_NAME        L"Battery"
/*      Default Portable Battery Info               { IsPublishRequired, BatteryType, Location,            Manufacturer,            ManufactureDate,             SerialNumber,             DevName,    DevChemistry,                          DevCapacity, Voltage, SbdsVersion,     MaxErrorInBatteryData, SbdsSerialNumber, SbdsManufactureDate, SbdsDeviceChemistry,      CapacityMultiplier, Oem }*/
#define DEFAULT_PORTABLE_BATTERY_INFO               { Required,          Unknown,     L"Battery Location", L"Battery Manufacturer", L"Battery Manufacture Date", L"Battery Serial Number", L"Battery", PortableBatteryDeviceChemistryUnknown, 0,            0,      L"SBDS Version", 0,                     0,                0,                   L"SBDS Device Chemistry", 1,                  0,  }
/*      Default Cooling Device Info                 { IsPublishRequired, Type,                     Status,                     Group,  Oem, Speed,  Description       } */
#define DEFAULT_COOLING_DEVICE_INFO                 { Required,          CoolingDeviceTypeUnknown, CoolingDeviceStatusUnknown, 0x01,   0x0, 0x8000, L"Cooling Device" }
#define DEFAULT_COOLING_DEVICE_DESC                 L"Cooling Device"
#define TO_BE_FILLED_BY_OEM_STR                     L"To Be Filled by O.E.M."
#define DEFAULT_POWER_SUPPLY_INPUT_VOLT_PROBE       0
#define DEFAULT_POWER_SUPPLY_COOLING_DEVICE         0x0A
#define DEFAULT_POWER_SUPPLY_INPUT_CURR_PROBE       0
#define DEFAULT_POWER_SUPPLY_INFO_GROUP             0x1
#define DEFAULT_POWER_SUPPLY_INFO_POWER_CAPACITY    0x8000
/* Default Power Supply Characteristics             { Bit0 HotReplaceable, Bit1 Present, Bit2 Unplugged, Bit3-6 InputVoltageRangeSwitch, Bit7-9 Status,            Bit10-13 Type,          Bit14-15 Reserved } */
#define DEFAULT_POWER_SUPPLY_INFO_CHARACTERISTICS   { FALSE,               TRUE,         FALSE,          InputVoltRangeSwitchUnknown,    PowerSupplyStatusUnknown, PowerSupplyTypeUnknown, 0x0               }
/*      Default OnBoard Device Extended Info        { IsPublishRequired, Designation,                           DeviceType,                       DeviceStatus, DeviceInstance, Segment, Bus,  DevFunc } */
#define DEFAULT_ONBOARD_DEV_EXT_INFO                { Required,          DEFAULT_ONBOARD_DEV_INFO_DESCRIPTION,  OnBoardDeviceExtendedTypeUnknown, Enabled,      0,              0xFF,    0xFF, 0xFF    }
#define DEFAULT_SLOT_DESIGN                         L"PCI-Express #"    // Slot Designation
#define DEFAULT_EXTENDED_BIOS_ROM_SIZE              0
#define DEFAULT_EXTENDED_BIOS_ROM_UNIT              0
//
// Default Bios Vendor Info for SMBIOS Type 0
//

SMBIOS_TABLE_TYPE0  mDefaultBiosVendorInfo = {
  {                                         // Hdr
    SMBIOS_TYPE_BIOS_INFORMATION,           /// Hdr.Type
    sizeof (SMBIOS_TABLE_TYPE0),            /// Hdr.Length
    0                                       /// Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                     // Vendor
  SMBIOS_MISC_STRING_2,                     // BiosVersion
  DEFAULT_BIOSVENDOR_SEGMENT,               // BiosSegment
  SMBIOS_MISC_STRING_3,                     // BiosReleaseDate
  DEFAULT_BIOSVENDOR_SEGMENT,               // BiosSize = 64K *(n+1) where n=20 for 2MB
  DEFAULT_BIOSVENDOR_CHARS,                 // BiosCharacteristics
  {                                         // BiosCharacteristicsExtensionBytes
   DEFAULT_BIOSVENDOR_CHARS_EXT_BIOS,
   DEFAULT_BIOSVENDOR_CHARS_EXT_SYSTEM
  },
  0x0,                                      // System BIOS Major Release
  0x1,                                      // System BIOS Minor Release
  DEFAULT_BIOSVENDOR_EC_RELEASE,            // Embedded controller firmware major Release
  DEFAULT_BIOSVENDOR_EC_RELEASE,            // Embedded controller firmware minor Release
  {                                         // Extended BIOS Rom Size
   DEFAULT_EXTENDED_BIOS_ROM_SIZE,
   DEFAULT_EXTENDED_BIOS_ROM_UNIT
  }
};

SMBIOS_TABLE_TYPE00_STRINGS  mDefaultBiosVendorStrings = {
  SMBIOS_MISC_TYPE00_VENDOR,
  SMBIOS_MISC_TYPE00_BIOS_VERSION,
  SMBIOS_MISC_TYPE00_BIOS_RELEASE_DATE
};

//
// Default System Info for SMBIOS Type 1
//

SMBIOS_TABLE_TYPE1 mDefaultSysInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_SYSTEM_INFORMATION,             /// Hdr.Type
    sizeof (SMBIOS_TABLE_TYPE1),                /// Hdr.Size
    0                                           /// Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                         // SystemManufactrurer
  SMBIOS_MISC_STRING_2,                         // SystemProductName
  SMBIOS_MISC_STRING_3,                         // SystemVersion
  SMBIOS_MISC_STRING_4,                         // SystemSerialNumber
  {                                             // SystemUuid
    0x5e24fe9c, 0xc8d0, 0x45bd, { 0xa7, 0x9f, 0x54, 0xea, 0x5f, 0xbd, 0x3d, 0x97 }
  },
  SystemWakeupTypeOther,                        // SystemWakeupType
  SMBIOS_MISC_STRING_5,                         // SystemSKUNumber
  SMBIOS_MISC_STRING_6                          // SystemFamily
};

SMBIOS_TABLE_TYPE01_STRINGS  mDefaultSysStrings = {
  SMBIOS_MISC_TYPE01_MANUFACTURER,
  DEFAULT_SYSINFO_PRODUCTNAME,
  DEFAULT_SYSINFO_VERSION,
  SMBIOS_MISC_TYPE01_SERIAL_NUMBER,
  SMBIOS_MISC_TYPE01_SKU_NUMBER,
  DEFAULT_SYSINFO_FAMILY
};


//
// Default Base Board info for RVP Board data
//
#define DEFAULT_BASE_BOARD_INFO  { DEFAULT_BOARDINFO_PRODUCTNAME, DEFAULT_BOARDINFO_MANUFACTURER, DEFAULT_BOARDINFO_VERSION, 0x1, BaseBoardTypeMotherBoard, DEFAULT_BOARDINFO_CHASSIS }
BASE_BOARD_INFO mDefaultBaseBoardInfo[] = {
  DEFAULT_BASE_BOARD_INFO
};
//
// Default BaseBoard Info for SMBIOS Type 2
//
SMBIOS_TABLE_TYPE2 mDefaultBaseBoardsInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_BASEBOARD_INFORMATION,          ///< Hdr.Type
    sizeof (SMBIOS_TABLE_TYPE2),                ///< Hdr.Length
    0                                           ///< Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                         ///< Manufacturer
  SMBIOS_MISC_STRING_2,                         ///< ProductName
  SMBIOS_MISC_STRING_3,                         ///< Version
  SMBIOS_MISC_STRING_4,                         ///< SerialNumber
  SMBIOS_MISC_STRING_5,                         ///< AssetTag
  {                                             // FeatureFlags
    1,                                          ///< Bit0 Motherboard
    0,                                          ///< Bit1 RequiresDaughterCard
    0,                                          ///< Bit2 Removable
    1,                                          ///< Bit3 Replaceable,
    0,                                          ///< Bit4 HotSwappable
    0,                                          ///< Bit5-7 Reserved
  },
  SMBIOS_MISC_STRING_6,                         // LocationInChassis
  0,                                            // ChassisHandle
  BaseBoardTypeMotherBoard,                     // BoardType
  0,                                            // NumberOfContainedObjectHandles
  { 0 }                                         // ContainedObjectHandles
};

SMBIOS_TABLE_TYPE02_STRINGS  mDefaultBaseBoardsStrings = {
  DEFAULT_BOARDINFO_MANUFACTURER,              //Manufacturer
  DEFAULT_BOARDINFO_PRODUCTNAME,               //ProductName
  DEFAULT_BOARDINFO_VERSION,                   //Version
  SMBIOS_MISC_TYPE02_BOARD_SERIAL_NUMBER,      //SerialNumber
  SMBIOS_MISC_TYPE02_BOARD_ASSET_TAG,          //AssetTag
  DEFAULT_BOARDINFO_CHASSIS                    //LocationInChassis
};


//
// Default Chassis info for RVP Board data
//
#define DEFAULT_CHASSIS_INFO { DEFAULT_CHASSISINFO_MANUFACTURER, MiscChassisTypeOther, DEFAULT_CHASSISINFO_VERSION, ChassisStateSafe, ChassisStateSafe, ChassisStateOther, ChassisSecurityStatusOther, DEFAULT_CHASSISINFO_HEIGHT, DEFAULT_CHASSISINFO_POWER_CORDS_NUM }
CHASSIS_INFO mDefaultChssisInfo [] = {
  DEFAULT_CHASSIS_INFO
};
//
// Default Chassis Info for SMBIOS Type 3
//
SMBIOS_TABLE_TYPE3 mDefaultChssisInfoInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_SYSTEM_ENCLOSURE,               ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE3),                 ///< Hdr.Length
    0                                           ///< Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                         ///< Manufactrurer
  0,                                            ///< Type
  SMBIOS_MISC_STRING_2,                         ///< Version
  SMBIOS_MISC_STRING_3,                         ///< SerialNumber
  SMBIOS_MISC_STRING_4,                         ///< AssetTag
  ChassisStateSafe,                             ///< BootupState
  ChassisStateSafe,                             ///< PowerSupplyState
  ChassisStateOther,                            ///< ThermalState
  ChassisSecurityStatusOther,                   ///< SecurityStatus
  {                                             // OemDefined[4]
    0,
    0,
    0,
    0
  },
  0,                                            ///< Height
  1,                                            ///< NumberofPowerCords
  0,                                            ///< ContainedElementCount
  0,                                            ///< ContainedElementRecordLength
  {                                             // ContainedElements
    {
      0,                                          ///< ContainedElementType
      0,                                          ///< ContainedElementMinimum
      0                                           ///< ContainedElementMaximum
    }
  }
};

SMBIOS_TABLE_TYPE02_STRINGS  mDefaultChssisInfoStrings = {
  DEFAULT_CHASSISINFO_MANUFACTURER,      //Manufacturer
  DEFAULT_CHASSISINFO_VERSION,           //Version
  SMBIOS_MISC_CHASSIS_SERIAL_NUMBER,     //SerialNumber
  SMBIOS_MISC_CHASSIS_ASSET_TAG          //AssetTag
};

//
// Default Port Info for SMBIOS Type 8
//

SMBIOS_TABLE_TYPE8 mDefaultPortConnectorsInfo = {
  {                                               // Hdr
    SMBIOS_TYPE_PORT_CONNECTOR_INFORMATION,       ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE8),                   ///< Hdr.Length
    0                                             ///< Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                           ///< InternalConnectorDesignator
  PortConnectorTypeNone,                          ///< InternalConnectorType
  SMBIOS_MISC_STRING_2,                           ///< ExternalConnectorDesignator
  PortConnectorTypeNone,                          ///< ExternalConnectorType
  PortTypeNone                                    ///< PortType
};

SMBIOS_TABLE_TYPE8_STRINGS mDefaultPortConnectorsStrings = {
  DEFAULT_PORT_INFO_INT_EXT_DESIGNATOR,
  DEFAULT_PORT_INFO_INT_EXT_DESIGNATOR
};

//
// Default Supported Port Connectors for RVP Board data
//
#define DEFAULT_PORT_CONNECTORS_SUPPORT    0x1FFFFFFFFFF // Set from Bit0 to Bit 40 in order to enable all port connectors by default.

//
// Default System Config for SMBIOS Type 12
//

SMBIOS_TABLE_TYPE12 mDefaultSysConfigInfo = {
  {
    SMBIOS_TYPE_SYSTEM_CONFIGURATION_OPTIONS,
    sizeof(SMBIOS_TABLE_TYPE12),
    0
  },
  SMBIOS_MISC_STRING_1
};

SMBIOS_TABLE_TYPE12_STRINGS mDefaultSysConfigStrings = {
  DEFAULT_CONFIG_OPTIONS_STRING //StringCount
};
//
// Default Language Info for SMBIOS Type 13
//

SMBIOS_TABLE_TYPE13 mDefaultBiosLangInfo = {
  {                                                     // Hdr
    SMBIOS_TYPE_BIOS_LANGUAGE_INFORMATION,              ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE13),                        ///< Hdr.Length
    0                                                   ///< Hdr.Handle
  },
  DEFAULT_BIOS_LANG_INFO_INSTALL_LANGUAGES,             // NumberOfInstallableLanguages
  Abbreviated,                                          // LanguageFlags
  {                                                     // Reserve[15]
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  },
  SMBIOS_MISC_STRING_1,                                 // CurrentLanguage
};
SMBIOS_TABLE_TYPE13_STRINGS mDefaultBiosLangStrings[] = {DEFAULT_BIOS_LANG_INFO_LANGUAGES}; //CurrentLanguages
//
// Default Portable Battery Info for SMBIOS Type 22
//

SMBIOS_TABLE_TYPE22 mDefaultPortableBatteryInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_PORTABLE_BATTERY,               ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE22),                ///< Hdr.Length
    0                                           ///< Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                         ///< Location
  SMBIOS_MISC_STRING_2,                         ///< Manufacturer
  SMBIOS_MISC_STRING_3,                         ///< ManufacturerDate
  SMBIOS_MISC_STRING_4,                         ///< SerialNumber
  SMBIOS_MISC_STRING_5,                         ///< DeviceName
  PortableBatteryDeviceChemistryUnknown,        ///< DeviceChemistry
  0,                                            ///< DeviceCapacity
  0,                                            ///< DeviceVoltage
  SMBIOS_MISC_STRING_NULL,                      ///< SBDSVersionNumber
  0xff,                                         ///< MaximumErrorInBatteryData
  0,                                            ///< SBDSSerialNumber
  0,                                            ///< SBDSManufactureDate
  SMBIOS_MISC_STRING_NULL,                      ///< SBDSDeviceChemistry
  1,                                            ///< DesignCapacityMultiplier
  0                                             ///< OEMSpecific
};
SMBIOS_TABLE_TYPE22_STRINGS  mDefaultPortableBatteryStrings = {
  DEFAULT_PORTABLE_BATTERY_LOCATION,             //Location;
  DEFAULT_PORTABLE_BATTERY_MANUFACTURER,         //Manufacturer;
  DEFAULT_PORTABLE_BATTERY_MANUFACTURER_DATE,    //ManufacturerDate;
  DEFAULT_PORTABLE_BATTERY_SERIAL_NUMBER,        //SerialNumber;
  DEFAULT_PORTABLE_BATTERY_DEVICE_NAME           //DeviceName;
};


//
// Default Cooling device info for RVP Board data
//
#define DEFAULT_COOLING_DEV_SUPPORT  (BIT0 | BIT1)
#define DEFAULT_COOLING_DEV          { CoolingDeviceTypeUnknown, L"Cooling Device" }

COOLING_DEV mDefaultCoolingDev [] = {
  DEFAULT_COOLING_DEV
};
//
// Default Cooling Device Info for SMBIOS Type 27
//
SMBIOS_TABLE_TYPE27 mDefaultCoolingDeviceInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_COOLING_DEVICE,                 ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE27),                ///< Hdr.Length
    0                                           ///< Hdr.Handle
  },
  SMBIOS_MISC_TEMP_PROBE_HANDLE,                ///< TempratureProbeHandle
  {                                             // DeviceTypeAndStatus
    CoolingDeviceTypeUnknown,                   ///< DeviceTypeAndStatus.CoolingDevice
    CoolingDeviceStatusUnknown                  ///< DeviceTypeAndStatus.CoolingDeviceStatus
  },
  0x01,                                         ///< CoolingUnitGroup
  0,                                            ///< OEMDefined
  0x8000,                                       ///< NominalSpeed
  SMBIOS_MISC_STRING_1                          ///< Description
};

SMBIOS_TABLE_TYPE27_STRINGS  mDefaultCoolingDeviceStrings = {
  DEFAULT_COOLING_DEVICE_DESC     //Description
};

//
// Default Boot Info for SMBIOS Type 32
//

SMBIOS_TABLE_TYPE32 mDefaultBootInfo = {
  {                                           // Hdr
    SMBIOS_TYPE_SYSTEM_BOOT_INFORMATION,      ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE32),              ///< Hdr.Length
    0                                         ///< Hdr.Handle
  },
  {                                           // Reserved[6]
    0,
    0,
    0,
    0,
    0,
    0
  },
  BootInformationStatusNoError                ///< BootStatus
};
//
// Default System Power Supply Info for SMBIOS Type 39
//

SMBIOS_TABLE_TYPE39 mDefaultPowerSupplyInfo = {
  {                                             // Hdr
    SMBIOS_TYPE_SYSTEM_POWER_SUPPLY,            ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE39),                ///< Hdr.Length
    0                                           ///< Hdr.Handle
  },
  DEFAULT_POWER_SUPPLY_INFO_GROUP,              ///< PowerUnitGroup
  SMBIOS_MISC_STRING_1,                         ///< Location
  SMBIOS_MISC_STRING_2,                         ///< DeviceName
  SMBIOS_MISC_STRING_3,                         ///< Manufacturer
  SMBIOS_MISC_STRING_4,                         ///< SerialNumber
  SMBIOS_MISC_STRING_5,                         ///< AssertTagNumber
  SMBIOS_MISC_STRING_6,                         ///< ModelPartNumber
  SMBIOS_MISC_STRING_7,                         ///< RevisionLevel
  DEFAULT_POWER_SUPPLY_INFO_POWER_CAPACITY,     ///< MaxPowerCapacity
  DEFAULT_POWER_SUPPLY_INFO_CHARACTERISTICS,    // PowerSupplyCharacteristics
  DEFAULT_POWER_SUPPLY_INPUT_VOLT_PROBE,        ///< InputVoltageProbeHandle
  DEFAULT_POWER_SUPPLY_COOLING_DEVICE,          ///< CoolingDeviceHandle
  DEFAULT_POWER_SUPPLY_INPUT_CURR_PROBE         ///< InputCurrentProbeHandle
};

SMBIOS_TABLE_TYPE39_STRINGS mDefaultPowerSupplyStrings = {
  TO_BE_FILLED_BY_OEM_STR,   //Location
  TO_BE_FILLED_BY_OEM_STR,   //DeviceName
  TO_BE_FILLED_BY_OEM_STR,   //Manufacturer
  TO_BE_FILLED_BY_OEM_STR,   //SerialNumber
  TO_BE_FILLED_BY_OEM_STR,   //AssetTagNumber
  TO_BE_FILLED_BY_OEM_STR,   //ModelPartNumber
  TO_BE_FILLED_BY_OEM_STR    //RevisionLevel
};



//
// Default OnBoard Device info for RVP Board data
//
#define DEFAULT_ONBOARD_DEV_SUPPORT           (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7) // Enable all bits to support all On-board devices
#define DEFAULT_ONBOARD_DEV_ADDR              { 0, 0xFF, 0xFF, 0xFF }

ONBOARD_DEV_ADDR mDefaultOnboardDevAddr [] =  {
  DEFAULT_ONBOARD_DEV_ADDR
};
//
// Default OnBoard Device Extended Info for SMBIOS Type 41
//
SMBIOS_TABLE_TYPE41 mDefaultOnBoardDeviceExtendedRecord = {
  {                                                                         // Hdr
    SMBIOS_TYPE_ONBOARD_DEVICES_EXTENDED_INFORMATION,                       ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE41),                                            ///< Hdr.Length
    0                                                                       ///< Hdr.Handle
  },
                                                                            // Device
  SMBIOS_MISC_STRING_1,                                                     ///< ReferenceDesignation
  OnBoardDeviceExtendedTypeUnknown,                                         ///< DeviceType
  0,                                                                        ///< DeviceTypeInstance
  0,                                                                        ///< SegmentGroupNum
  0xFF,                                                                     ///< BusNum
  0xFF                                                                      ///< DevFuncNum
};

SMBIOS_TABLE_TYPE41_STRINGS   mDefaultOnBoardDeviceExtendedStrings = {
  DEFAULT_ONBOARD_DEV_INFO_DESCRIPTION   //Description String
};

//
// Default OEM Type 136
//
SMBIOS_TABLE_TYPE136 mDefaultOemType136 = {
  {                                     // Hdr
    SMBIOS_TYPE_OEM_136,                ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE136),       ///< Hdr.Length
    0                                   ///< Hdr.Handle
  },
  0,                                    ///< RawData
  0                                     ///< Zero
};

//
// Default System Slot Info for SMBIOS Type 9
//
SMBIOS_TABLE_TYPE9 mDefaultSystemSlotRecord = {
  {                                                 // Hdr
    SMBIOS_TYPE_SYSTEM_SLOTS,                       ///< Hdr.Type
    sizeof(SMBIOS_TABLE_TYPE9),                     ///< Hdr.Length
    0                                               ///< Hdr.Handle
  },
  SMBIOS_MISC_STRING_1,                             ///< SlotDesignation;
  SlotTypePciExpress,                               ///< SlotType
  SlotDataBusWidth1X,                               ///< SlotDataBusWidth;
  SlotUsageAvailable,                               ///< CurrentUsage;
  SlotLengthLong,                                   ///< SlotLength;
  0,                                                ///< SlotID;
  {                                                 ///< SlotCharacteristics1;
    0,                                              // Bit0 - CharacteristicsUnknown
    0,                                              // Bit1 - Provides 5.0 Volts
    1,                                              // Bit2 - Provides 3.3 Volts
    0,                                              // Bit3 - SharedSlot
    0,                                              // Bit4 - PcCard16Supported
    0,                                              // Bit5 - CardBusSupported
    0,                                              // Bit6 - ZoomVideoSupported
    0                                               // Bit7 - ModemRingResumeSupported
  },
  {                                                 ///< SlotCharacteristics2;
    1,                                              // Bit0   - PmeSignalSupported
    1,                                              // Bit1   - HotPlugDevicesSupported
    1,                                              // Bit2   - SmbusSignalSupported
    0                                               // Bit3-7 - Reserved
  },
  0x00,                                             ///< SegmentGroupNum;
  0xFF,                                             ///< BusNum;
  0xFF                                              ///< DevFuncNum;
};

SMBIOS_TABLE_TYPE9_STRINGS   mDefaultSystemSlotStrings = {
  DEFAULT_SLOT_DESIGN   //SlotDesignation
};

//
// Default Smbios Platform Info table
//
SMBIOS_PLATFORM_INFO mDefaultSmbiosPlatformInfo[] = {

  { (VOID*)(&mDefaultBiosVendorInfo),              (VOID*)(&mDefaultBiosVendorStrings),            SIZEOF_SMBIOS_STRINGS(00), FALSE, 1 }, // SMBIOS Type 0  - BiosVendor

  { (VOID*)(&mDefaultSysInfo),                     (VOID*)(&mDefaultSysStrings),                   SIZEOF_SMBIOS_STRINGS(01), FALSE, 1 }, // SMBIOS Type 1  - SystemManufacturer

  { (VOID*)(&mDefaultBaseBoardsInfo),              (VOID*)(&mDefaultBaseBoardsStrings),            SIZEOF_SMBIOS_STRINGS(02), FALSE, 1 }, // SMBIOS Type 2  - BaseBoardManufacturer

  { (VOID*)(&mDefaultChssisInfoInfo),              (VOID*)(&mDefaultChssisInfoStrings),            SIZEOF_SMBIOS_STRINGS(03), FALSE, 1 }, // SMBIOS Type 3  - ChassisManufacturer

  { (VOID*)(&mDefaultBootInfo),                    NULL,                                           0,                         FALSE, 1 }, // SMBIOS Type 32 - BootInfoStatus

  { (VOID*)(&mDefaultBiosLangInfo),                (VOID*)(&mDefaultBiosLangStrings[0]),           SIZEOF_SMBIOS_STRINGS(13), FALSE, 1 }, // SMBIOS Type 13 - BiosLanguagesInfo

  { (VOID*)(&mDefaultSysConfigInfo),               (VOID*)(&mDefaultSysConfigStrings),             SIZEOF_SMBIOS_STRINGS(12), FALSE, 1 }, // SMBIOS Type 12 - SystemOptionString

  { (VOID*)(&mDefaultPortConnectorsInfo),          (VOID*)(&mDefaultPortConnectorsStrings),        SIZEOF_SMBIOS_STRINGS(8),  FALSE, 1 }, // SMBIOS Type 8  - PortConnectors

  { (VOID*)(&mDefaultOemType136),                  NULL,                                           0,                         FALSE, 1 }, // SMBIOS Type 136 - OemType136

  { (VOID*)(&mDefaultPortableBatteryInfo),         (VOID*)(&mDefaultPortableBatteryStrings),       SIZEOF_SMBIOS_STRINGS(22), FALSE, 1 }, // SMBIOS Type 22 - PortableBattery

  { (VOID*)(&mDefaultCoolingDeviceInfo),           (VOID*)(&mDefaultCoolingDeviceStrings),         SIZEOF_SMBIOS_STRINGS(27), FALSE, 1 }, // SMBIOS Type 27 - CoolingDevice

  { (VOID*)(&mDefaultPowerSupplyInfo),             (VOID*)(&mDefaultPowerSupplyStrings),           SIZEOF_SMBIOS_STRINGS(39), FALSE, 1 }, // SMBIOS Type 39 - SystemPowerSupply

  { (VOID*)(&mDefaultOnBoardDeviceExtendedRecord), (VOID*)(&mDefaultOnBoardDeviceExtendedStrings), SIZEOF_SMBIOS_STRINGS(41), FALSE, 1 }, // SMBIOS Type 41 - OnBoardDeviceExtended

  { (VOID*)(&mDefaultSystemSlotRecord),            (VOID*)(&mDefaultSystemSlotStrings),            SIZEOF_SMBIOS_STRINGS(9),  FALSE, 1 }  // SMBIOS Type 9  - SystemSlot

};
//
// Default Smbios Board info for RVP Board data
//
SMBIOS_PLATFORM_BOARD_INFO mDefaultSmbiosBoardInfo = {
  DEFAULT_SYSINFO_PRODUCTNAME,       //SystemProductName
  DEFAULT_SYSINFO_VERSION,           //SystemVersion
  DEFAULT_SYSINFO_FAMILY,            //SystemFamily
  SystemWakeupTypeOther,             //SystemWakeUpType
  &mDefaultBaseBoardInfo[0],         //BaseBoard
  &mDefaultChssisInfo[0],            //ChassisInfo
  DEFAULT_PORT_CONNECTORS_SUPPORT,   //SupportedPortConnectors
  DEFAULT_CONFIG_OPTIONS_STRING,     //SystemConfigOptions
  &mDefaultCoolingDev[0],            //CoolingDevCoolingDev
  DEFAULT_ONBOARD_DEV_SUPPORT,       //SupportedOnboardDev
  &mDefaultOnboardDevAddr[0]         //OnBoardDevAddr
};

#endif //_SMBIOS_PLATFORM_INFO_DEFAULT_H_
