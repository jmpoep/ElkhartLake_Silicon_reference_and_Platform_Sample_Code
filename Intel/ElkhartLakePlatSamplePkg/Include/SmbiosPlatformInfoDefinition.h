/** @file
This file contains definition for Platform SMBIOS Info.

@par Revision Reference:
SMBIOS Specification version 3.0.0 from DMTF: http://www.dmtf.org/standards/smbios

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

This file contains 'Framework Code' and is licensed as such under the terms
of your license agreement with Intel or your vendor. This file may not be
modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _SMBIOS_PLATFORM_INFO_DEFINITION_H_
#define _SMBIOS_PLATFORM_INFO_DEFINITION_H_

#include <IndustryStandard/SmBios.h>
//
// The below enumeration describes the order in which SMBIOS tables are published by SmbiosMiscDxe driver.
//
typedef enum{
  BiosVendor = 0,
  SystemManufacturer,
  BaseBoardManufacturer,
  ChassisManufacturer,
  BootInfoStatus,
  BiosLanguagesInfo,
  SystemOptionString,
  PortConnectors,
  OemType136,
  PortableBattery,
  CoolingDevice,
  SystemPowerSupply,
  OnBoardDeviceExtended,
  SystemSlot
}PLATFORM_SMBIOS_DATA_ORDER;

#define SIZEOF_SMBIOS_STRINGS(Type)   (sizeof(SMBIOS_TABLE_TYPE ## Type ## _STRINGS) / sizeof (CHAR16*))

//
// Platform Info for Type 0 - BIOS Vendor
//
typedef struct {
  UINT16                                   Segment;
  UINT32                                   Size;
  MISC_BIOS_CHARACTERISTICS                Characteristics;
  MISC_BIOS_CHARACTERISTICS_EXTENSION      CharacteristicsExt;
  UINT8                                    EcFwMajorRelease;
  UINT8                                    EcFwMinorRelease;
}BIOS_VENDOR_INFO_TYPE0;

//
// Platform Info for Type 1 - System Info
//
typedef struct {
  CHAR16         *ProductName;
  CHAR16         *Version;
  CHAR16         *Family;
  UINT8          WakeUpType;
}SYSTEM_INFO_TYPE1;

//
// Platform Info For Type 2 - Base Board Info
//
typedef struct {
  CHAR16                        *ProductName;
  CHAR16                        *Manufacturer;
  CHAR16                        *Version;
  BASE_BOARD_FEATURE_FLAGS      FeatureFlags;
  UINT8                         BoardType;
  CHAR16                        *LocationInChassis;
}BASEBOARD_INFO_TYPE2;

//
// Platform Info For Type 3 - Chassis Info
//
typedef struct {
  CHAR16                        *Manufacturer;
  MISC_CHASSIS_TYPE             Type;
  CHAR16                        *Version;
  MISC_CHASSIS_STATE            Bootup;
  MISC_CHASSIS_STATE            PowerSupply;
  MISC_CHASSIS_STATE            Thermal;
  MISC_CHASSIS_SECURITY_STATE   Security;
  UINT8                         Oem[4];
  UINT8                         Height;
  UINT8                         NumberofPowerCords;
}CHASSIS_INFO_TYPE3;

//
// Platform Info For Type 8 - Port Connector Information
//
#define NUM_DEFINED_PORT_TYPES    41

typedef enum {
  NotRequired = 0,
  Required
}PUBLISH_REQ;

typedef struct {
  PUBLISH_REQ                IsPublishRequired;
  CHAR16                     *InternalDesignator;
  MISC_PORT_CONNECTOR_TYPE   InternalConnectorType;
  CHAR16                     *ExternalDesignator;
  MISC_PORT_CONNECTOR_TYPE   ExternalConnectorType;
  MISC_PORT_TYPE             PortType;
} PORT_INFO_TYPE8;

//
// Platform Info For Type 12 - System Config Options
//
typedef struct {
  CHAR16                        *ConfigOptions;
}SYSTEM_CONFIG_TYPE12;

//
// Platform Info For Type 13 - BIOS Language Information
//

typedef enum{
  Long = 0,
  Abbreviated
}LANGUAGES_FORMAT;

#define MAX_LANGUAGES              1 // TODO: it requires some investigation to update properly

typedef enum{
  English = 1,
  French,
  Japanese
}CURRENT_LANGUAGES;

typedef struct {
  CHAR16                 *Language[MAX_LANGUAGES];
  UINT8                  InstallableLanguages;
  LANGUAGES_FORMAT       Flags;
  CURRENT_LANGUAGES      CurrentLanguage;
}BIOS_LANGUAGE_INFO_TYPE13;

//
// Platform Info For Type 22 - Portable Battery Info
//
#define NUM_PORTABLE_BATTERIES    3

typedef enum{
  Unknown = 0,
  Real1,
  Real2,
  Virtual
}BATTERY_TYPE;

typedef struct {
  PUBLISH_REQ                           IsPublishRequired;
  BATTERY_TYPE                          BatteryType;
  CHAR16                                *Location;
  CHAR16                                *Manufacturer;
  CHAR16                                *ManufactureDate;
  CHAR16                                *SerialNumber;
  CHAR16                                *DevName;
  PORTABLE_BATTERY_DEVICE_CHEMISTRY     DevChemistry;
  UINT16                                DevCapacity;
  UINT16                                Voltage;
  CHAR16                                *SbdsVersion;
  UINT8                                 MaxErrorInBatteryData;
  UINT16                                SbdsSerialNumber;
  UINT16                                SbdsManufactureDate;
  CHAR16                                *SbdsDeviceChemistry;
  UINT8                                 CapacityMultiplier;
  UINT32                                Oem;
} PORTABLE_BATTERY_INFO_TYPE22;

//
// Platform Info For Type 27 - Cooling Device Info
//

typedef enum{
  CoolingDeviceTypeOther = 0x1,
  CoolingDeviceTypeUnknown,
  CoolingDeviceTypeFan,
  CoolingDeviceTypeCentrifugalBlower,
  CoolingDeviceTypeChipFan,
  CoolingDeviceTypeCabinetFan,
  CoolingDeviceTypePowerSupplyFan,
  CoolingDeviceTypeHeatPipe,
  CoolingDeviceTypeIntegratedRefrigeration,
  CoolingDeviceTypeActiveCooling = 0x10,
  CoolingDeviceTypePassiveCooling
}COOLING_DEVICE_TYPE;

typedef enum{
  CoolingDeviceStatusOther = 1,
  CoolingDeviceStatusUnknown,
  CoolingDeviceStatusOk,
  CoolingDeviceStatusNonCritical,
  CoolingDeviceStatusCritical,
  CoolingDeviceStatusNonRecoverable
}COOLING_DEVICE_STATUS;

typedef struct {
  PUBLISH_REQ                  IsPublishRequired;
  COOLING_DEVICE_TYPE          Type;
  COOLING_DEVICE_STATUS        Status;
  UINT8                        Group;
  UINT32                       Oem;
  UINT16                       Speed;
  CHAR16                       *Description;
} COOLING_DEVICE_INFO_TYPE27;

//
// Platform Info For Type 32 - Boot Info Status
//
typedef struct {
  MISC_BOOT_INFORMATION_STATUS_DATA_TYPE BootStatus;
}BOOT_INFO_TYPE32;

//
// Platform Info For Type 39 - System Power Supply
//
typedef enum{
  InputVoltRangeSwitchOther = 1,
  InputVoltRangeSwitchUnknown,
  InputVoltRangeSwitchManual,
  InputVoltRangeSwitchAutoSwitch,
  InputVoltRangeSwitchWideRange,
  InputVoltRangeSwitchNotApplicable,
  InputVoltRangeSwitchNotReserved
}INPUT_VOLT_RANGE_SWITCH;

typedef enum{
  PowerSupplyStatusOther = 1,
  PowerSupplyStatusUnknown,
  PowerSupplyStatusOk,
  PowerSupplyStatusNonCritical,
  PowerSupplyStatusCritical
}POWER_SUPPLY_STATUS;

typedef enum{
  PowerSupplyTypeOther = 1,
  PowerSupplyTypeUnknown,
  PowerSupplyTypeLinear,
  PowerSupplyTypeSwitching,
  PowerSupplyTypeBattery,
  PowerSupplyTypeUps,
  PowerSupplyTypeConverter,
  PowerSupplyTypeRegulator,
  PowerSupplyTypeReserved
}POWER_SUPPLY_TYPE;

typedef struct {
  UINT8                             PowerUnitGroup;
  CHAR16                            *Location;
  CHAR16                            *DeviceName;
  CHAR16                            *Manufacturer;
  CHAR16                            *SerialNumber;
  CHAR16                            *AssetTagNumber;
  CHAR16                            *ModelPartNumber;
  CHAR16                            *RevisionLevel;
  UINT16                            MaxPowerCapacity;
  SYS_POWER_SUPPLY_CHARACTERISTICS  Characteristics;
}SYS_POWER_SUPPLY_INFO_TYPE39;

//
// Platform Info For Type 41 - OnBoard Device Extended Information
//

typedef enum {
  Disabled = 0,
  Enabled
} DEVICE_STATUS;

typedef struct {
  PUBLISH_REQ                         IsPublishRequired;
  CHAR16                              *Designation;
  ONBOARD_DEVICE_EXTENDED_INFO_TYPE   DeviceType;
  DEVICE_STATUS                       DeviceStatus;
  UINT8                               DeviceInstance;
  UINT16                              Segment;
  UINT8                               Bus;
  UINT8                               DevFunc;
} ONBOARD_DEV_EXT_INFO_TYPE41;

//
// OEM Type 136
//
#define NUM_OEM_TYPE_136       1
#define SMBIOS_TYPE_OEM_136    0x88

typedef struct {
  SMBIOS_STRUCTURE              Hdr;
  UINT16                        RawData;
  UINT16                        Zero;       //terminator
} SMBIOS_TABLE_TYPE136;

//
// Smbios Platform Info table
//
typedef struct {
  VOID        *Info;
  VOID        *Strings;
  UINTN       StringCount;
  BOOLEAN     IsPoolAllocated;
  UINTN       NoOfInstances;
}SMBIOS_PLATFORM_INFO;


//
// Base Board info for RVP Board data
//
#define NUM_BASE_BOARDS          0x1
typedef struct{
  CHAR16                   *ProductName;
  CHAR16                   *Manufacturer;
  CHAR16                   *Version;
  UINT8                    FeatureFlags;
  UINT8                    BoardType;
  CHAR16                   *LocationInChassis;
} BASE_BOARD_INFO;
//
// Chassis info for RVP Board data
//
#define NUM_CHASSIS_INFO         0x1
typedef struct{
  CHAR16              *Manufacturer;
  UINT8               Type;
  CHAR16              *Version;
  UINT8               Bootup;
  UINT8               PowerSupply;
  UINT8               Thermal;
  UINT8               Security;
  UINT8               Height;
  UINT8               NumberofPowerCords;
} CHASSIS_INFO;

/*
The SupportedPortConnectors is represented as below.

BIT0    Keyboard,
BIT1    Mouse,
BIT2    Com1,
BIT3    Video,
BIT4    Hdmi,
BIT5    Usb1,
BIT6    Usb2,
BIT7    Usb3,
BIT8    Usb4,
BIT9    Usb5,
BIT10   Usb201,
BIT11   Usb202,
BIT12   Network,
BIT13   Sata0,
BIT14   eSata4,
BIT15   eSata3,
BIT16   Sata2,
BIT17   Sata1,
BIT18   Acin,
BIT19   PchJtag,
BIT20   Port80,
BIT21   2X8Header,
BIT22   8PinHeader,
BIT23   HdaHdmi,
BIT24   Mkeyboard,
BIT25   Spi,
BIT26   LpcDocking,
BIT27   Sideband,
BIT28   LpcSlot,
BIT29   PchXdp,
BIT30   SataPower,
BIT31   FpHeader,
BIT32   AtxPower,
BIT33   Avmc,
BIT34   Battb,
BIT35   Batta,
BIT36   CpuFan,
BIT37   Xdp,
BIT38   Memory1,
BIT39   Memory2,
BIT40   FanPwr,
BIT41-63 Reserved
*/

//
// Cooling info for RVP Board data
//
#define NUM_COOLING_DEVICES      2
typedef struct{
  UINT8          Type;
  CHAR16         *Description;
} COOLING_DEV;

/*
The SupportedOnboardDev is represented  as below.

BIT0    Video,
BIT1    Ethernet,
BIT2    Sound,
BIT3    SataController,
BIT4    ScsiController,
BIT5    TokenRing,
BIT6    PataController,
BIT7    SasController

*/
//
// OnBoard Device info for RVP Board data
//
#define NUM_ONBOARD_DEVICES_EXT  4
typedef struct{
  UINT8         Seg;
  UINT8         Bus;
  UINT8         Dev;
  UINT8         Func;
} ONBOARD_DEV_ADDR;

//
// Smbios Board info for RVP Board data
//
typedef struct {
  /*System Info Type 1*/
  CHAR16                           *SystemProductName;
  CHAR16                           *SystemVersion;
  CHAR16                           *SystemFamily;
  UINT8                            SystemWakeUpType;
  /*Base Board Info Type 2*/
  BASE_BOARD_INFO                  *BaseBoard;
  /*Chassis Info Type 3*/
  CHASSIS_INFO                     *ChassisInfo;
  /* Port Connector Info type 8 */
  UINTN                            SupportedPortConnectors;
  /*System Config Options Type 12*/
  CHAR16                           *SystemConfigOptions;
  /*Cooling device Type 27*/
  COOLING_DEV                      *CoolingDev;
  /* Onboard Device Ext Type 41*/
  UINT8                            SupportedOnboardDev;
  ONBOARD_DEV_ADDR                 *OnBoardDevAddr;
} SMBIOS_PLATFORM_BOARD_INFO;

//
// Smbios System Slot Board Info
//
#define MAX_SLOT_ENTRIES 20

typedef struct {
  CHAR16                      *SlotDesignation;
  UINT8                       SlotType;                 ///< The enumeration value from MISC_SLOT_TYPE.
  UINT8                       SlotDataBusWidth;         ///< The enumeration value from MISC_SLOT_DATA_BUS_WIDTH.
  UINT8                       CurrentUsage;             ///< The enumeration value from MISC_SLOT_USAGE.
  UINT8                       SlotLength;               ///< The enumeration value from MISC_SLOT_LENGTH.
  UINT16                      SlotID;
  MISC_SLOT_CHARACTERISTICS1  SlotCharacteristics1;
  MISC_SLOT_CHARACTERISTICS2  SlotCharacteristics2;
  UINT16                      SegmentGroupNum;          // Valid Only for PCIe Root Ports, Others 0xFF is expected
  UINT8                       BusNum;
  UINT8                       DevNum;
  UINT8                       FuncNum;
  BOOLEAN                     Isvalid;
} SYSTEM_SLOT_INFO;

typedef struct {
  UINT8            Numberofentries;
  SYSTEM_SLOT_INFO Slotinfo[MAX_SLOT_ENTRIES];
}SYSTEM_SLOT_ENTRY;

#endif // _SMBIOS_PLATFORM_INFO_DEFINITION_H_
