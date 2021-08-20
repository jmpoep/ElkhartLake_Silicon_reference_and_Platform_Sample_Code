/** @file
  Update SMBIOS Platform Information according to platform. This file also allow
  to customize the code according to the platform.

  @par Revision Reference:
  SMBIOS Specification version 3.0.0 from DMTF: http://www.dmtf.org/standards/smbios

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
#include <SmbiosPlatformInfo.h>
#include <SmbiosPlatformInfoDefault.h>
#include <Register/PchRegs.h>

CHAR16         BoardVersionString[SMBIOS_STRING_MAX_LENGTH];
CHAR16         BiosReleaseDate[SMBIOS_STRING_MAX_LENGTH];
CHAR16         BiosVersion[SMBIOS_STRING_MAX_LENGTH];
//
// Below Port Connector Info Table can be customized accordingly to platform.
//
PORT_INFO_TYPE8 PortInfoTable[] = {
  PORT_INFO_KEYBOARD,
  PORT_INFO_MOUSE,
  PORT_INFO_COM1,
  PORT_INFO_VIDEO,
  PORT_INFO_HDMI,
  PORT_INFO_USB1,
  PORT_INFO_USB2,
  PORT_INFO_USB3,
  PORT_INFO_USB4,
  PORT_INFO_USB5,
  PORT_INFO_USB201,
  PORT_INFO_USB202,
  PORT_INFO_NETWORK,
  PORT_INFO_SATA0,
  PORT_INFO_ESATA4,
  PORT_INFO_ESATA3,
  PORT_INFO_SATA2,
  PORT_INFO_SATA1,
  PORT_INFO_ACIN,
  PORT_INFO_PCHJTAG,
  PORT_INFO_PORT80,
  PORT_INFO_2X8HEADER,
  PORT_INFO_8PINHEADER,
  PORT_INFO_HDAHDMI,
  PORT_INFO_MKEYBOARD,
  PORT_INFO_SPI,
  PORT_INFO_LPCDOCKING,
  PORT_INFO_SIDEBAND,
  PORT_INFO_LPCSLOT,
  PORT_INFO_PCHXDP,
  PORT_INFO_SATAPOWER,
  PORT_INFO_FPHEADER,
  PORT_INFO_ATXPOWER,
  PORT_INFO_AVMC,
  PORT_INFO_BATTB,
  PORT_INFO_BATTA,
  PORT_INFO_CPUFAN,
  PORT_INFO_XDP,
  PORT_INFO_MEMORY1,
  PORT_INFO_MEMORY2,
  PORT_INFO_FANPWR
};

//
// Below Portable Battery Info Table can be customized accordingly to platform.
//
PORTABLE_BATTERY_INFO_TYPE22 PortableBatteryInfoTable[] = {
  PORTABLE_BATTERY_INFO_REAL1,
  PORTABLE_BATTERY_INFO_REAL2,
  PORTABLE_BATTERY_INFO_VIRTUAL
};

//
// Below Cooling Device Info Table can be customized accordingly to platform.
//
COOLING_DEVICE_INFO_TYPE27 CoolingDevInfoTable[] = {
  COOLING_DEVICE_INFO1,
  COOLING_DEVICE_INFO2
};

//
// Below OnBoard Device Extended Info Table can be customized accordingly to platform.
//
ONBOARD_DEV_EXT_INFO_TYPE41 OnboardExtInfoTable[] = {
  ONBOARD_EXT_INFO_VIDEO,
  ONBOARD_EXT_INFO_ETHERNET,
  ONBOARD_EXT_INFO_SOUND,
  ONBOARD_EXT_INFO_SATA
};

//
// Global pointer variable which holds the address the Platform Info Table
//
SMBIOS_PLATFORM_INFO  *mSmbiosPlatformInfo=NULL;
//
// Global pointer variable which holds the address the Board Info from RVP
//
SMBIOS_PLATFORM_BOARD_INFO  *mSmbiosBoardInfo=NULL;
UINT8                       IsSmbiosBoardInfoEnabled = 0;

//
// Platform Info for SMBIOS Type 12
//
SYSTEM_CONFIG_TYPE12  SysConfig12 = {
  SYSTEM_OPTION_TYPE12_STRING //ConfigOptions
};

//
// Platform Info for SMBIOS Type 13
//
CHAR16   *LanguagesLong[]      = BIOS_LANG_INFO_LANGUAGES_LONG;
CHAR16   *LanguagesAbbr[]      = BIOS_LANG_INFO_LANGUAGES_ABBR;

//
// Default System Slot Table
//
SYSTEM_SLOT_ENTRY gDefaultSlotEntryTable =
{
  0x07, // Number of Entries
  {
    // Slot Desig       SlotType               BusWidth             CurrentUsage        SlotLength      SlotID   Char1                       Char 2          SegGrpnu Bus                         Device      Fun         Isvalid
    { L"PCI-Express 0", SlotTypePciExpressX16, SlotDataBusWidth16X, SlotUsageAvailable, SlotLengthLong, 0,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_1, TRUE },
    { L"PCI-Express 1", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 1,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_2, TRUE },
    { L"PCI-Express 2", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 2,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_3, TRUE },
    { L"PCI-Express 3", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 3,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_4, TRUE },
    { L"PCI-Express 4", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 4,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_5, TRUE },
    { L"PCI-Express 5", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 5,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_6, TRUE },
    { L"PCI-Express 6", SlotTypePciExpress,    SlotDataBusWidth1X,  SlotUsageAvailable, SlotLengthLong, 6,       { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 1, 1, 0 }, 0,       DEFAULT_PCI_BUS_NUMBER_PCH, PCIE_DEV_1, PCIE_FUN_7, TRUE },
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

/**
  Get the enabling/disabling setting through PciBridgeIo and return that.

  @param[in]    OnBoardDeviceType
  @param[out]   DeviceStatus

**/
VOID
GetOnBoardDeviceType (
  MISC_ONBOARD_DEVICE_TYPE         OnBoardDeviceType,
  DEVICE_STATUS                    *DeviceStatus
  )
{
  EFI_STATUS    Status;
  UINT8         Value8;
  UINT32        Value32;
  UINT64        PciAddress;

  Value8        = 0;
  Value32       = 0;
  PciAddress    = 0;
  *DeviceStatus = Disabled;

  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  (VOID**) &gPciRootBridgeIo
                  );
  if (EFI_ERROR(Status)) {
    //
    // Can't access PciRootBridgeIoProtocol, don't change the default setting.
    //
    DEBUG ((DEBUG_INFO, "(GetOnBoardDeviceType) Don't change the default setting for the OnBoardDeviceType.\n"));
    return;
  }

  //
  // Read PCI registers to set enabling/disabling onboard device
  //
  switch (OnBoardDeviceType) {
    case OnBoardDeviceTypeVideo:
      //
      // Read command reg of IGD to check whether onboard device is enabled
      //
      PciAddress = EFI_PCI_ADDRESS(
                     SA_IGD_BUS,
                     SA_IGD_DEV,
                     SA_IGD_FUN_0,
                     PCI_COMMAND_OFFSET
                     );
      gPciRootBridgeIo->Pci.Read (
                          gPciRootBridgeIo,
                          EfiPciWidthUint8,
                          PciAddress,
                          1,
                          &Value8
                          );
      if (Value8 != 0xff) {
        if ((Value8 & 0x02) || (Value8 & 0x01)) {
          *DeviceStatus = Enabled;
          DEBUG((DEBUG_INFO, "(GetOnBoardDeviceType) OnBoardDevice Video is enabled.\n"));
        } else {
          *DeviceStatus = Disabled;
        }
      }
      break;
    case OnBoardDeviceTypeEthernet:
      //
      // Read command reg of LAN to check whether onboard device is enabled
      //
      PciAddress = EFI_PCI_ADDRESS (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     GbeDevNumber (),
                     GbeFuncNumber (),
                     PCI_COMMAND_OFFSET
                     );
      gPciRootBridgeIo->Pci.Read (
                          gPciRootBridgeIo,
                          EfiPciWidthUint8,
                          PciAddress,
                          1,
                          &Value8
                          );
      if (Value8 != 0xff) {
        if ((Value8 & 0x02) || (Value8 & 0x01)) {
          *DeviceStatus = Enabled;
          DEBUG ((DEBUG_INFO, "(GetOnBoardDeviceType) OnBoardDevice Ethernet is enabled.\n"));
        } else {
          *DeviceStatus = Disabled;
        }
      }
      break;
    case OnBoardDeviceTypeSound:
      //
      // Read command reg of HDA (device 31, function 3) to check whether onboard device is enabled
      //
      PciAddress = EFI_PCI_ADDRESS (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     HdaDevNumber (),
                     HdaFuncNumber (),
                     PCI_COMMAND_OFFSET
                     );
      gPciRootBridgeIo->Pci.Read (
                          gPciRootBridgeIo,
                          EfiPciWidthUint32,
                          PciAddress,
                          1,
                          &Value32
                          );
      if (Value32 != 0xffffffff) {
        if ((Value32 & 0x02) || (Value32 & 0x01)) {
          *DeviceStatus = Enabled;
          DEBUG ((DEBUG_INFO, "(GetOnBoardDeviceType) OnBoardDevice Sound is enabled.\n"));
        } else {
          *DeviceStatus = Disabled;
        }
      }
      break;
    case OnBoardDeviceTypeSATAController:
      //
      // Read command reg of SATA (device 23, function 0) to check whether onboard device is enabled
      //
      PciAddress = EFI_PCI_ADDRESS (
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     SataDevNumber (SATA_1_CONTROLLER_INDEX),
                     SataFuncNumber (SATA_1_CONTROLLER_INDEX),
                     PCI_COMMAND_OFFSET
                     );
      gPciRootBridgeIo->Pci.Read (
                          gPciRootBridgeIo,
                          EfiPciWidthUint8,
                          PciAddress,
                          1,
                          &Value8
                          );
      if (Value8 != 0xff) {
        if ((Value8 & 0x02) || (Value8 & 0x01)) {
          *DeviceStatus = Enabled;
          DEBUG ((DEBUG_INFO, "(GetOnBoardDeviceType) OnBoardDevice SATA Controller is enabled.\n"));
        } else {
          *DeviceStatus = Disabled;
        }
      }
      break;
    case OnBoardDeviceTypeOther:
    case OnBoardDeviceTypeUnknown:
    case OnBoardDeviceTypeScsiController:
    case OnBoardDeviceTypeTokenRing:
    case OnBoardDeviceTypePATAController:
    case OnBoardDeviceTypeSASController:
    default:
      break;
  }
}

/**
  Get the On-board Device Status(enable/disable) through PciBridgeIo and return that.

  @param[in]    BusNum
  @param[in]    DevNum
  @param[in]    FuncNum
  @param[out]   DeviceStatus

**/
VOID
GetOnBoardDeviceStatus (
  UINT8        BusNum,
  UINT8        DevNum,
  UINT8        FuncNum,
  UINT8        *DevStatus
  )
{
  EFI_STATUS    Status;
  UINT8         Value8;
  UINT64        PciAddress;

  Value8        = 0;
  PciAddress    = 0;
  *DevStatus = Disabled;

  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  (VOID**) &gPciRootBridgeIo
                  );
  if (EFI_ERROR(Status)) {
    //
    // Can't access PciRootBridgeIoProtocol, don't change the default setting.
    //
    DEBUG ((DEBUG_INFO, "(GetOnBoardDeviceStatus) Don't change the default setting for the GetOnBoardDeviceStatus.\n"));
    return;
  }
  //
  // Read PCI command register of IGD to check whether on-board device is enabled or not.
  //
  PciAddress = EFI_PCI_ADDRESS(
                BusNum,
                DevNum,
                FuncNum,
                PCI_COMMAND_OFFSET
                );
  gPciRootBridgeIo->Pci.Read (
                      gPciRootBridgeIo,
                      EfiPciWidthUint8,
                      PciAddress,
                      1,
                      &Value8
                      );
  if (Value8 != 0xff) {
    if ((Value8 & 0x02) || (Value8 & 0x01)) {
      *DevStatus = 1;
      DEBUG((DEBUG_INFO, "(GetOnBoardDeviceStatus) OnBoardDevice Device(Bus : %X, Dev : %X, Func : %X) is enabled.\n",BusNum,DevNum,FuncNum));
    } else {
      *DevStatus = 0;
      DEBUG((DEBUG_INFO, "(GetOnBoardDeviceStatus) OnBoardDevice Device(Bus : %X, Dev : %X, Func : %X) is disabled.\n",BusNum,DevNum,FuncNum));
    }
  }
}

/**
Get the chassis type by PCD

@retval UINT8                The chassis type.

**/
UINT8
GetChassisType(
  VOID
  )
{
  if (PcdGet8(PcdPlatformFlavor) == FlavorMobile) {
    return MiscChassisTypeLapTop;
  } else if (PcdGet8(PcdPlatformFlavor) == FlavorDesktop || (PcdGet8(PcdPlatformFlavor) == FlavorWorkstation)) {
    return MiscChassisTypeDeskTop;
  } else if (PcdGet8(PcdPlatformFlavor) == FlavorEmbedded) {
    return MiscChassisTypeLapTop;
  } else {
    return MiscChassisTypeMainServerChassis;
  }
}

#ifdef EC_SUPPORT
/**
  Return the desired value from ACPI memory space. Assumes the EC has ACPI memory space read
  enabled.

  @param[in]    Register      Register to read from
  @param[out]   RetValue      Return value from EC

  @retval       EFI_SUCCESS   successful
  @retval       Other Vals    something wrong

**/
static EFI_STATUS
GetBatteryValue (
  IN  UINT8    Register,
  OUT UINT8   *RetValue
  )
{
  EFI_STATUS    Status;
  UINT8         DataBuffer[1];

  DataBuffer[0] = Register;
  Status = ReadEcRam (DataBuffer);
  if (Status == EFI_SUCCESS) {
    *RetValue = DataBuffer[0];
  }

  return Status;
}
#endif

/**
  Get the specific battery information through EC part.

  @param[out]   PortableBatteryRecord   Return the battery information for the
                                        Platform Portable Battery Info Table.

  @retval       EFI_SUCCESS             All parameters are valid.
  @retval       EFI_INVALID_PARAMETER   Invalid parameter is found.
  @retval       EFI_OUT_OF_RESOURCES    Locate PlatformInfo failed.
  @retval       EFI_OUT_OF_RESOURCES    The platform is not needed to install
                                        the battery information.
  @retval       EFI_OUT_OF_RESOURCES    Initialize EC library failed.

**/
EFI_STATUS
UpdateBatteryInfo (
  OUT PORTABLE_BATTERY_INFO_TYPE22    *PortableBatteryRecord
)
{
  static BOOLEAN            NeedVirtualBattery = TRUE;
  EFI_STATUS                Status;
  UINT8                     RegData;
  UINT16                    Value;

  RegData = 0;
  Value   = 0;
  Status  = EFI_NOT_FOUND;

  if (PortableBatteryRecord == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if ((PcdGet8 (PcdPlatformFlavor) != FlavorMobile) &&
      (PcdGet8 (PcdPlatformFlavor) != FlavorEmbedded)) {
    PortableBatteryRecord->IsPublishRequired = NotRequired;
    DEBUG ((DEBUG_INFO, "Battery is not supported in this platform \n"));
    return EFI_SUCCESS;
  }

#ifdef EC_SUPPORT
  if (!PcdGetBool (PcdEcPresent)) {
    PortableBatteryRecord->IsPublishRequired = NotRequired;
    return EFI_NOT_FOUND;
  }
#endif

  switch (PortableBatteryRecord->BatteryType) {
    case Real1:
#ifdef EC_SUPPORT
      Status = GetBatteryValue (EC_REAL_BAT1_STATUS, &RegData);
      DEBUG ((DEBUG_INFO, "Battery 1 Status = %x\n", RegData));
#endif
#ifdef ECLITE_PSE_SUPPORT
      Status = GetBattery1CurrentState (&Value);
      DEBUG ((DEBUG_INFO, "Battery 1 Status = %x\n", Value));
#endif
      if (Status == EFI_SUCCESS) {
#ifdef EC_SUPPORT
        if (RegData & EC_REAL_BAT_PRESENT_MASK) {
          DEBUG ((DEBUG_INFO, "Adding Battery 1\n"));
          NeedVirtualBattery = FALSE;
          Status = GetBatteryValue (EC_REAL_BAT1_REMAINING_CAPACITY + 1, &RegData); // Get uppder Byte
          Value = 0;
          Value |= (UINT16)RegData;
          Value = Value << 8;
          Status = GetBatteryValue (EC_REAL_BAT1_REMAINING_CAPACITY, &RegData); // Get lower Byte
          Value |= (UINT16)RegData;
          PortableBatteryRecord->DevCapacity = Value;
          Status = GetBatteryValue (EC_REAL_BAT1_RESOLUTION_VOLTAGE + 1, &RegData); // Get uppder Byte
          Value = 0;
          Value |= (UINT16)RegData;
          Value = Value << 8;
          Status = GetBatteryValue (EC_REAL_BAT1_RESOLUTION_VOLTAGE, &RegData); // Get lower Byte
          Value |= (UINT16)RegData;
          PortableBatteryRecord->Voltage = Value;
          PortableBatteryRecord->DevChemistry = PortableBatteryDeviceChemistryLithiumIon;
          PortableBatteryRecord->IsPublishRequired = Required;
        }
#endif
#ifdef ECLITE_PSE_SUPPORT
        if ((Value & 0x7) != 0) {
          DEBUG ((DEBUG_INFO, "Adding Battery 1\n"));
          NeedVirtualBattery = FALSE;
          //
          // Obtain Battery 1 Current Capacity
          //
          Value = 0;
          Status = GetBattery1RemainingCapacityLevel (&Value);
          if (Status == EFI_SUCCESS) {
            PortableBatteryRecord->DevCapacity = Value;
          }
          //
          // Obtain Battery 1 Current Voltage
          //
          Value = 0;
          Status = GetBattery1VoltageLevel (&Value);
          if (Status == EFI_SUCCESS) {
            PortableBatteryRecord->DevCapacity = Value;
          }
          PortableBatteryRecord->Voltage = Value;
          PortableBatteryRecord->DevChemistry = PortableBatteryDeviceChemistryLithiumIon;
          PortableBatteryRecord->IsPublishRequired = Required;
        } else {
          PortableBatteryRecord->IsPublishRequired = NotRequired;
        }
#endif
      } else {
        PortableBatteryRecord->IsPublishRequired = NotRequired;
      }
      break;
    case Real2:
#ifdef EC_SUPPORT
      Status = GetBatteryValue (EC_REAL_BAT2_STATUS, &RegData);
      DEBUG ((DEBUG_INFO, "Battery 2 Status = %x\n", RegData));
#endif
#ifdef ECLITE_PSE_SUPPORT
      Status = GetBattery2CurrentState (&Value);
      DEBUG ((DEBUG_INFO, "Battery 2 Status = %x\n", Value));
#endif
      if (Status == EFI_SUCCESS) {
#ifdef EC_SUPPORT
        if (RegData & EC_REAL_BAT_PRESENT_MASK) {
          DEBUG ((DEBUG_INFO, "Adding Battery 2\n"));
          NeedVirtualBattery = FALSE;
          Status = GetBatteryValue(EC_REAL_BAT2_REMAINING_CAPACITY + 1, &RegData); // Get uppder Byte
          Value = 0;
          Value |= (UINT16)RegData;
          Value = Value << 8;
          Status = GetBatteryValue(EC_REAL_BAT2_REMAINING_CAPACITY, &RegData); // Get lower Byte
          Value |= (UINT16)RegData;
          PortableBatteryRecord->DevCapacity = Value;
          Status = GetBatteryValue(EC_REAL_BAT2_RESOLUTION_VOLTAGE + 1, &RegData); // Get uppder Byte
          Value = 0;
          Value |= (UINT16)RegData;
          Value = Value << 8;
          Status = GetBatteryValue(EC_REAL_BAT2_RESOLUTION_VOLTAGE, &RegData); // Get lower Byte
          Value |= (UINT16)RegData;
          PortableBatteryRecord->Voltage = Value;
          PortableBatteryRecord->DevChemistry = PortableBatteryDeviceChemistryLithiumIon;
          PortableBatteryRecord->IsPublishRequired = Required;
        }
#endif
#ifdef ECLITE_PSE_SUPPORT
        if ((Value & 0x7) != 0) {
          DEBUG ((DEBUG_INFO, "Adding Battery 1\n"));
          NeedVirtualBattery = FALSE;
          //
          // Obtain Battery 2 Current Capacity
          //
          Value = 0;
          Status = GetBattery2RemainingCapacityLevel (&Value);
          if (Status == EFI_SUCCESS) {
            PortableBatteryRecord->DevCapacity = Value;
          }
          //
          // Obtain Battery 2 Current Voltage
          //
          Value = 0;
          Status = GetBattery2VoltageLevel (&Value);
          if (Status == EFI_SUCCESS) {
            PortableBatteryRecord->DevCapacity = Value;
          }
          PortableBatteryRecord->Voltage = Value;
          PortableBatteryRecord->DevChemistry = PortableBatteryDeviceChemistryLithiumIon;
          PortableBatteryRecord->IsPublishRequired = Required;
        } else {
          PortableBatteryRecord->IsPublishRequired = NotRequired;
        }
#endif
      } else {
        PortableBatteryRecord->IsPublishRequired = NotRequired;
      }
      break;
    case Virtual:
      PortableBatteryRecord->IsPublishRequired = NotRequired;
#ifdef EC_SUPPORT
      if (NeedVirtualBattery) {
        Status = GetBatteryValue (EC_VIRTUAL_BAT_STATUS, &RegData);
        DEBUG ((DEBUG_INFO, "Virtual Battery Status = %x\n", RegData));
        if (Status == EFI_SUCCESS) {
          if (RegData & EC_REAL_BAT_PRESENT_MASK) {
            PortableBatteryRecord->IsPublishRequired = Required;
          }
        }
      } else {
        PortableBatteryRecord->IsPublishRequired = NotRequired;
      }
#endif
      break;
    case Unknown:
    default:
      break;
  }

  return EFI_SUCCESS;
}

/**
Get Smbios Platform Info Table. This function will update the
Global Smbios Platform Info Table pointer variable using PCD
PcdSmbiosPlatformInfo which holds address of default Smbios Platform
Info Table address.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
GetSmbiosPlatformInfoTable(
  VOID
  )
{
  //
  // Update the Global Smbios Platform Info Table pointer variable with PcdSmbiosPlatformInfo.
  //
  mSmbiosPlatformInfo = (SMBIOS_PLATFORM_INFO*)(UINTN)PcdGet64(PcdSmbiosPlatformInfo);

  return EFI_SUCCESS;
}

/**
Get Smbios Board Info PCDS. This function will update the
Global Smbios Board Info pointer and enable switch variables using PCD
PcdSmbiosBoardInfo and PcdSmbiosBoardInfoEnable

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
GetSmbiosBoardInfoPCDs(
  VOID
  )
{
  //
  // Update the Global Smbios Board Info Enable Switch.
  //
  IsSmbiosBoardInfoEnabled = (UINT8)PcdGetBool(PcdSmbiosBoardInfoEnable);

  if (IsSmbiosBoardInfoEnabled) {
    //
    // Update the Global Smbios Board Info pointer variable with PcdSmbiosBoardInfo.
    //
    mSmbiosBoardInfo = (SMBIOS_PLATFORM_BOARD_INFO*)(UINTN)PcdGet64(PcdSmbiosBoardInfo);
  }

  return EFI_SUCCESS;
}

/**
  Field Filling Function. Transform an UINTN to a byte, with '64k' as the unit.

  @param[in]  Value                   The value based on UINTN.

  @retval     Value                   The value which is transformed by '64k'.

**/
UINTN
GetValueBy64KUnit(
  IN UINTN          Value
  )
{
  UINTN         Uint64K;

  Uint64K       = 0x10000;

  return Value/Uint64K;
}

/**
  This function returns the BiosMajorVersion and BiosMinorVersion by getting and converting
  BIOS ID.

  @param[in]  BiosVersionString     The Bios Version string for the conversion.
  @param[out] MajorVersion          The Bios Major Version out of the conversion
  @param[out] MinorVersion          The Bios Minor Version out of the conversion

  @retval     EFI_SUCCESS           BIOS Version & Release Date and Time have been got successfully.
  @retval     EFI_INVALID_PARAMETER Either one of the parameters is NULL.

**/
EFI_STATUS
GetSystemBiosVersion (
  IN  CHAR16      *BiosVersionString,
  OUT UINT8       *MajorVersion,
  OUT UINT8       *MinorVersion
  )
{
  CHAR8           *Buffer;
  UINTN           BufferSize;
  BIOS_ID_STRING  BiosIdString;

  if ((BiosVersionString == NULL) || (MajorVersion == NULL) || (MinorVersion == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Buffer = NULL;

  CopyMem (&BiosIdString, BiosVersionString, sizeof (BIOS_ID_STRING));

  if (StrLen (BiosIdString.VersionMajor) > StrLen (BiosIdString.VersionMinor)) {
    BufferSize = (StrLen (BiosIdString.VersionMajor) + 1) * sizeof (CHAR8);
  } else {
    BufferSize = (StrLen (BiosIdString.VersionMinor) + 1) * sizeof (CHAR8);
  }
  Buffer = AllocateZeroPool (BufferSize);
  if (Buffer != NULL) {

    if (BiosIdString.VersionMajor[0] < (CHAR16)'0' || \
        BiosIdString.VersionMajor[0] > (CHAR16)'9') {
      // The left most character of the MAJOR VERSION field within the BIOS ID string {Offset 0} specifies
      // the color of the bar at the top of the screen.
      // Make it to zero for the computation of System BIOS Major Release
      // Otherwise keep it without modification.
      BiosIdString.VersionMajor[0] = (CHAR16)'0';
    }

    UnicodeStrToAsciiStrS (BiosIdString.VersionMajor, Buffer, BufferSize);
    *MajorVersion = (UINT8) AsciiStrDecimalToUintn(Buffer);

    // SMBIOS type 0 offset 0x14(Major Release)/0x15(Minor Release) is BYTE field and mark it as 0xFF if over 255.
    if (AsciiStrDecimalToUintn(Buffer) >= 255) {
      *MajorVersion = 0xFF;
      *MinorVersion = 0xFF;
      FreePool (Buffer);
      return EFI_SUCCESS;
    }

    UnicodeStrToAsciiStrS (BiosIdString.VersionMinor, Buffer, BufferSize);
    *MinorVersion = (UINT8) AsciiStrDecimalToUintn (Buffer);

    FreePool (Buffer);
  }

  return EFI_SUCCESS;
}

/**
Update Bios Vendor Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateBiosVendorInfo (
  VOID
  )
{
  EFI_STATUS                     Status;
  SMBIOS_TABLE_TYPE0             *UpdBiosVendorInfo;
  SMBIOS_TABLE_TYPE00_STRINGS    *UpdBiosVendorStrings;
  UINT8                          SystemBiosMajorVersion;
  UINT8                          SystemBiosMinorVersion;
  //
  // Get Default Bios Vendor Info and Strings
  //
  UpdBiosVendorInfo                                           = mDefaultSmbiosPlatformInfo[BiosVendor].Info;
  UpdBiosVendorStrings                                        = mDefaultSmbiosPlatformInfo[BiosVendor].Strings;

  if(UpdBiosVendorInfo == NULL || UpdBiosVendorStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateBiosVendorInfo: Default Bios Vendor Info Type 0 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Update the Bios Vendor data
  //
  Status = GetBiosVersionDateTime (
             BiosVersion,
             BiosReleaseDate,
             NULL
             );
  UpdBiosVendorStrings->BiosReleaseDate                       = BiosReleaseDate;
  UpdBiosVendorStrings->BiosVersion                           = BiosVersion;
  UpdBiosVendorInfo->BiosSize = (UINT8)(GetValueBy64KUnit((UINTN)PcdGet32(PcdBiosSize)) - 1); // Update BIOS Size
  //
  // Update Extended BIOS & System Characteristic as below
  //
  UpdBiosVendorInfo->BIOSCharacteristicsExtensionBytes[0]     = (UINT8)(BIT0 | BIT1 | BIT4 | BIT5);
  UpdBiosVendorInfo->BIOSCharacteristicsExtensionBytes[1]     = (UINT8)(BIT0 | BIT1 | BIT2 | BIT3);
  //
  // Update the System BIOS version
  //
  Status = GetSystemBiosVersion (
             BiosVersion,
             &SystemBiosMajorVersion,
             &SystemBiosMinorVersion
             );
  if (Status == EFI_SUCCESS) {
    UpdBiosVendorInfo->SystemBiosMajorRelease = SystemBiosMajorVersion;
    UpdBiosVendorInfo->SystemBiosMinorRelease = SystemBiosMinorVersion;
    UpdBiosVendorInfo->ExtendedBiosSize.Size  = 32;
    UpdBiosVendorInfo->ExtendedBiosSize.Unit  = 0;
  }
#ifdef EC_SUPPORT
  //
  // Update EC Firmware Revision
  //
  if (PcdGetBool (PcdEcPresent)) {
    UpdBiosVendorInfo->EmbeddedControllerFirmwareMajorRelease = PcdGet8(PcdEcMajorRevision);
    UpdBiosVendorInfo->EmbeddedControllerFirmwareMinorRelease = PcdGet8(PcdEcMinorRevision);
  }
#endif
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[BiosVendor].Info                 = UpdBiosVendorInfo;
  mDefaultSmbiosPlatformInfo[BiosVendor].Strings              = UpdBiosVendorStrings;
  mDefaultSmbiosPlatformInfo[BiosVendor].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[BiosVendor].IsPoolAllocated      = FALSE;
  DEBUG((DEBUG_INFO, "UpdateBiosVendorInfo: Bios Vendor Info Type 0 is updated\n"));

  return EFI_SUCCESS;
}

/**
  Get UUID from Gbe region MAC

  @param[out]   UuidBuffer    Buffer for the MAC

  @retval       EFI_SUCCESS   successful
  @retval       Other Vals    something wrong

**/
EFI_STATUS
GetGbeUuid (
  UINT8 *UuidBuffer
  )
{
  EFI_STATUS        Status;
  PCH_SPI_PROTOCOL  *SpiProtocol;

  if (UuidBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Locate the SPI protocol.
  //
  Status = gBS->LocateProtocol (
                  &gPchSpiProtocolGuid,
                  NULL,
                  (VOID **) &SpiProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Read MAC address from GbE region
  //
  Status = SpiProtocol->FlashRead (
                          SpiProtocol,
                          FlashRegionGbE,
                          (UINT32)0,
                          (UINT32)6,
                          UuidBuffer
                          );
  return Status;
}

/**
  This function get the next bus range of given address space descriptors.
  It also moves the pointer backward a node, to get prepared to be called
  again.

  @param[in] Descriptors          points to current position of a serial of address space
                                  descriptors
  @param[in] MinBus               The lower range of bus number
  @param[in] MaxBus               The upper range of bus number
  @param[in] IsEnd                Meet end of the serial of descriptors

  @retval EFI_SUCCESS             The command completed successfully

**/
EFI_STATUS
PciGetNextBusRange (
  IN OUT EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR  **Descriptors,
  OUT    UINT16                             *MinBus,
  OUT    UINT16                             *MaxBus,
  OUT    BOOLEAN                            *IsEnd
  )
{
  *IsEnd = FALSE;

  //
  // When *Descriptors is NULL, Configuration() is not implemented, so assume
  // range is 0~PCI_MAX_BUS
  //
  if ((*Descriptors) == NULL) {
    *MinBus = 0;
    *MaxBus = PCI_MAX_BUS;
    return EFI_SUCCESS;
  }
  //
  // *Descriptors points to one or more address space descriptors, which
  // ends with a end tagged descriptor. Examine each of the descriptors,
  // if a bus typed one is found and its bus range covers bus, this handle
  // is the handle we are looking for.
  //
  if ((*Descriptors)->Desc == ACPI_END_TAG_DESCRIPTOR) {
    *IsEnd = TRUE;
  }

  while ((*Descriptors)->Desc != ACPI_END_TAG_DESCRIPTOR) {
    if ((*Descriptors)->ResType == ACPI_ADDRESS_SPACE_TYPE_BUS) {
      *MinBus = (UINT16) (*Descriptors)->AddrRangeMin;
      *MaxBus = (UINT16) (*Descriptors)->AddrRangeMax;
    }

    (*Descriptors)++;
  }

  return EFI_SUCCESS;
}

/**
  This function gets the protocol interface from the given handle, and
  obtains its address space descriptors.

  @param[in]  Handle              The PCI_ROOT_BRIDIGE_IO_PROTOCOL handle
  @param[in]  IoDev               Handle used to access configuration space of PCI device
  @param[in]  Descriptors         Points to the address space descriptors

  @retval     EFI_SUCCESS         The command completed successfully
**/
EFI_STATUS
PciGetProtocolAndResource (
  IN  EFI_HANDLE                            Handle,
  OUT EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       **IoDev,
  OUT EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR     **Descriptors
  )
{
  EFI_STATUS  Status;

  //
  // Get inferface from protocol
  //
  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiPciRootBridgeIoProtocolGuid,
                  (VOID **) IoDev
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Call Configuration() to get address space descriptors
  //
  Status = (*IoDev)->Configuration (*IoDev, (VOID **) Descriptors);
  if (Status == EFI_UNSUPPORTED) {
    *Descriptors = NULL;
    return EFI_SUCCESS;

  } else {
    return Status;
  }
}

/**
  Check if WLAN with given device Id is on the list of supported adapters

  @param[in]    DeviceId    PCI Device ID to be checked

  @retval       TRUE        device supported
  @retval       FALSE       not supported

**/
BOOLEAN
IsSupportedIntelWlanDevice (
  IN  UINT16     DeviceId
  )
{
  UINT16 SupportedIntelWlanDevices[] = SUPPORTED_INTEL_WLAN_DEVICES;
  UINTN  Index;

  for (Index = 0; Index < sizeof(SupportedIntelWlanDevices)/sizeof(UINT16); Index++) {
    if (DeviceId == SupportedIntelWlanDevices[Index]) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Find WLAN device on PCI

  @param[out]     Bus           Updated with PCI bus number of discovered WLAN device
  @param[out]     Device        Updated with PCI device number of discovered WLAN device

  @retval         EFI_SUCCESS   successful
  @retval         Other Vals    something wrong

**/
EFI_STATUS
FindCompatibleWlanDevice (
  OUT UINT16     *Bus,
  OUT UINT16     *Device
  )
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        *HandleBuffer;
  UINTN                             NumberOfHandles;
  UINTN                             Index;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *IoDev;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *Descriptors;
  UINT16                            MinBus;
  UINT16                            MaxBus;
  BOOLEAN                           IsEnd;
  UINT16                            TempBus;
  UINT16                            TempDev;
  PCI_DEVICE_INDEPENDENT_REGION     PciHeader;

  //
  // Get all instances of PciRootBridgeIo
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // For each handle, which decides a segment and a bus number range,
  // enumerate all devices on it.
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    Status = PciGetProtocolAndResource (
              HandleBuffer[Index],
              &IoDev,
              &Descriptors
              );
    if (EFI_ERROR (Status)) {
      FreePool (HandleBuffer);
      return Status;
    }

    //
    // No document say it's impossible for a RootBridgeIo protocol handle
    // to have more than one address space descriptors, so find out every
    // bus range and for each of them do device enumeration.
    //
    while (TRUE) {
      Status = PciGetNextBusRange (&Descriptors, &MinBus, &MaxBus, &IsEnd);

      if (EFI_ERROR (Status)) {
        FreePool (HandleBuffer);
        return Status;
      }
      //
      // Wifi device will not be on Bus 0.
      //
      if (MinBus == 0 && MaxBus == 0) {
        DEBUG((DEBUG_INFO, "SMBIOS type 1: Find Wifi- PCIe MaxBus is 0, no wifi device exists on Bus 0, no wifi device found\n"));
        return EFI_NOT_FOUND;
      }
      if (IsEnd) {
        break;
      }
      //
      // Wifi device will not be on Bus 0. Increase MinBus to Bus 1 to optimize search.
      //
      if (MinBus == 0) {
        MinBus = 1;
      }
      for (TempBus = MinBus; TempBus <= MaxBus; TempBus++) {
        //
        // Enumerate all devices on a bus
        //
        for (TempDev = 0; TempDev <= PCI_MAX_DEVICE; TempDev++) {
          SetMem (&PciHeader, sizeof(PCI_DEVICE_INDEPENDENT_REGION), 0);

          //
          // Read vendor and device id
          //
          IoDev->Pci.Read (
                      IoDev,
                      EfiPciWidthUint32,
                      EFI_PCI_ADDRESS (TempBus, TempDev, 0, PCI_VENDOR_ID_OFFSET),
                      3,
                      &PciHeader.VendorId
                      );

          //
          // Find a supported device on a hard-coded list
          // Or, since this is our internal implementation, check PCI class ID only to allow using more devices for validation purposes
          //
          if (PciHeader.VendorId == V_PCH_INTEL_VENDOR_ID &&
             (IsSupportedIntelWlanDevice(PciHeader.DeviceId) ||
              (PciHeader.ClassCode[2] == PCI_CLASS_NETWORK && PciHeader.ClassCode[1] == PCI_CLASS_NETWORK_OTHER))) {
            *Bus = TempBus;
            *Device = TempDev;
            return EFI_SUCCESS;
          }
        }
      }
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Get UUID from WLAN MAC.

  @param[in]  UuidBuffer    Buffer for the MAC

  @retval     EFI_SUCCESS   successful
  @retval     Other Vals    something wrong

**/
EFI_STATUS
GetWlanUuid (
  UINT8 *UuidBuffer,
  UINT16 Bus,
  UINT16 Dev
  )
{
  UINT32  Data32;
  UINT64  WlanBaseAddress;

  if (UuidBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Read MAC from WLAN pci config space offset 0x144 and 0x148
  //
  WlanBaseAddress = PCI_SEGMENT_LIB_ADDRESS (0, Bus, Dev, 0, 0);
  Data32 = PciSegmentRead32 (WlanBaseAddress + 0x148);
  *UuidBuffer = (UINT8)(Data32 >> 24);
  *(UuidBuffer+1) = (UINT8)(Data32 >> 16);
  *(UuidBuffer+2) = (UINT8)(Data32 >> 8);

  Data32 = PciSegmentRead32 (WlanBaseAddress + 0x144);
  *(UuidBuffer+3) = (UINT8)(Data32 >> 16);
  *(UuidBuffer+4) = (UINT8)(Data32 >> 8);
  *(UuidBuffer+5) = (UINT8)Data32;

  return EFI_SUCCESS;
}
/**
Update System Manufacturer Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateSystemManufacturerInfo(
  VOID
  )
{
  EFI_STATUS                     Status;
  CHAR16                         UuidVarName[sizeof(SMBIOS_TYPE1_SYSTEM_UUID_VARIABLE)+1];
  UINTN                          UuidVarSize;
  UINT8                          UuidBuffer[6];
  UINT8                          *UuidPtr;
  UINT8                          *UuidPtrTemp;
  UINT8                          i;
  UINT16                         Bus;
  UINT16                         Dev;
  UINT8                          UuidRetry;
  SMBIOS_TABLE_TYPE1             *UpdSysInfo;
  SMBIOS_TABLE_TYPE01_STRINGS    *UpdSysStrings;
  //
  // Get Default System Manufacturer Info and Strings
  //
  UpdSysInfo                            = mDefaultSmbiosPlatformInfo[SystemManufacturer].Info;
  UpdSysStrings                         = mDefaultSmbiosPlatformInfo[SystemManufacturer].Strings;

  if(UpdSysInfo == NULL || UpdSysStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateSysInfo: Default System Manufacturer Info Type 1 is not available!!\n"));
    return EFI_SUCCESS;
  }

  UpdSysStrings->ProductName   = SYSINFO_TYPE01_PRODUCT_NAME;
  UpdSysStrings->Version       = SYSINFO_TYPE01_VERSION;
  UpdSysStrings->Family        = SYSINFO_TYPE01_FAMILY;
  UpdSysInfo->WakeUpType       = PcdGet8(PcdWakeupType);
  //
  // Update the RVP board info here.
  //
  if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
    if(mSmbiosBoardInfo){
      UpdSysStrings->ProductName   = mSmbiosBoardInfo->SystemProductName;
      UpdSysStrings->Version       = mSmbiosBoardInfo->SystemVersion;
      UpdSysStrings->Family        = mSmbiosBoardInfo->SystemFamily;
      UpdSysInfo->WakeUpType       = mSmbiosBoardInfo->SystemWakeUpType;
    }
  }

  //
  // Fill in UUID by first copying default GUID.  Then update last six bytes
  // with MAC address to make it unique.
  //
  StrCpyS (UuidVarName, sizeof (UuidVarName) / sizeof (CHAR16), SMBIOS_TYPE1_SYSTEM_UUID_VARIABLE);
  UuidPtr     = (UINT8 *) &UpdSysInfo->Uuid;
  UuidPtrTemp = UuidPtr;
  UuidRetry   = 0;
  UuidVarSize = sizeof(EFI_GUID);
  Status = gRT->GetVariable (
                  UuidVarName,
                  &gEfiSmbiosVariableGuid,
                  NULL,
                  &UuidVarSize,
                  UuidPtr
                  );
  //
  // If variable is not present or we are booting with defaults, re-create the UUID.
  // Use the following methods in order of priority to create the UUID:
  // 1) UUID based on WLAN MAC Address
  // 2) UUID based on LAN MAC Address
  // 3) Default UUID
  //

  //
  // If the current UUID Matches the default UUID, then re-evaluate to find WLAN MAC
  //
  if (!EFI_ERROR(Status) && (UuidPtrTemp != NULL)) {
    if (CompareMem(UuidPtr,UuidPtrTemp,sizeof (EFI_GUID)) == 0x0) {
      DEBUG ((DEBUG_INFO, "Default UUID detected. Re-search for WLAN or LAN to generate UUID\n"));
      UuidRetry = 0x1;
    }
  }

  if (EFI_ERROR(Status) || (GetBootModeHob() == BOOT_WITH_DEFAULT_SETTINGS) || (UuidRetry == 0x1)) {
    //
    // Set system GUID. If there is no MAC address, use default UUID set when structure was defined
    //
    Status = FindCompatibleWlanDevice(&Bus, &Dev);
    if (Status == EFI_SUCCESS) { // Check for Wifi device
      Status = GetWlanUuid(UuidBuffer, Bus, Dev);
      DEBUG ((DEBUG_INFO, "SMBIOS type 1: UUID will be derived from WLAN MAC\n"));
    } else if (IsGbeRegionValid () && (PcdGetBool(PcdBfxEnable) == FALSE)) { // Check for LAN device
      Status = GetGbeUuid (UuidBuffer);
      DEBUG ((DEBUG_INFO, "SMBIOS type 1: UUID will be derived from GbE MAC\n"));
    } else { //No device with MAC found- use default UUID
      Status = EFI_NOT_FOUND;
      DEBUG ((DEBUG_INFO, "SMBIOS type 1: No WLAN or LAN detected. UUID set as default.\n"));
    }

    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UUID = "));
      for (i = 0; i < sizeof (EFI_GUID); i++) {
        UuidPtr[i] = UuidBuffer[i % 6];
        DEBUG ((DEBUG_INFO, "%02x ", UuidPtr[i]));
      }
      DEBUG ((DEBUG_INFO, "\n"));
    }
    //
    // Store UUID in NVRAM
    //
    Status = gRT->SetVariable (
                    UuidVarName,
                    &gEfiSmbiosVariableGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    UuidVarSize,
                    UuidPtr
                    );
    DEBUG ((DEBUG_INFO, "UuidVarName : %X  "));
    ASSERT_EFI_ERROR(Status);
  }


  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[SystemManufacturer].Info                 = UpdSysInfo;
  mDefaultSmbiosPlatformInfo[SystemManufacturer].Strings              = UpdSysStrings;
  mDefaultSmbiosPlatformInfo[SystemManufacturer].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[SystemManufacturer].IsPoolAllocated      = FALSE;
  DEBUG((DEBUG_INFO, "UpdateSysInfo: System Manufacturer Info Type 1 is updated\n"));

  return EFI_SUCCESS;
}

/**
Update Base Board Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateBaseBoardManufacturerInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          MaxInstances;
  BASE_BOARD_INFO                *BaseBoardInfo;
  SMBIOS_TABLE_TYPE2             *DefBaseBoardInfo;
  SMBIOS_TABLE_TYPE2             *UpdBaseBoardInfo;
  SMBIOS_TABLE_TYPE02_STRINGS    *DefBaseBoardStrings;
  SMBIOS_TABLE_TYPE02_STRINGS    *UpdBaseBoardStrings;
  //
  // Get Default Base Board Info and Strings
  //
  DefBaseBoardInfo        = mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].Info;
  DefBaseBoardStrings     = mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].Strings;
  MaxInstances            = NUM_BASE_BOARDS;

  if(DefBaseBoardInfo == NULL || DefBaseBoardStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateBaseBoardManufacturerInfo: Default Base Board Info Type 2 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdBaseBoardInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE2) * MaxInstances);
    if (UpdBaseBoardInfo == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateBaseBoardManufacturerInfo: Can't allocate enough resource for UpdBaseBoardInfo variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
    UpdBaseBoardStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE02_STRINGS) * MaxInstances);
    if (UpdBaseBoardStrings == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateBaseBoardManufacturerInfo: Can't allocate enough resource for UpdBaseBoardStrings variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdBaseBoardInfo        = DefBaseBoardInfo;
    UpdBaseBoardStrings     = DefBaseBoardStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  for (Instance = 0; Instance < MaxInstances; Instance++){
    if(MaxInstances > 1){
      CopyMem((UpdBaseBoardInfo+Instance), DefBaseBoardInfo, sizeof(SMBIOS_TABLE_TYPE2));
      CopyMem((UpdBaseBoardStrings+Instance), DefBaseBoardStrings, sizeof(SMBIOS_TABLE_TYPE02_STRINGS));
    }
    //
    // Get FAB Board Name from PCD and udpate it in Board Info
    //
    (UpdBaseBoardStrings + Instance)->ProductName = (CHAR16 *)(UINTN)PcdGet64(PcdSmbiosFabBoardName);

    //
    // Get Board Revision from PCD and udpate it in Board Info
    //
    UnicodeValueToStringS (BoardVersionString, sizeof (BoardVersionString), 0, (INT64)PcdGet16 (PcdBoardRev) + 1, 0);
    (UpdBaseBoardStrings + Instance)->Version      = BoardVersionString;
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo){
        BaseBoardInfo = (BASE_BOARD_INFO*)mSmbiosBoardInfo->BaseBoard;
      }
      if(mSmbiosBoardInfo && (BaseBoardInfo + Instance)){
        (UpdBaseBoardStrings + Instance)->ProductName        = (BaseBoardInfo + Instance)->ProductName;
        (UpdBaseBoardStrings + Instance)->Manufacturer       = (BaseBoardInfo + Instance)->Manufacturer;
        (UpdBaseBoardStrings + Instance)->Version            = (BaseBoardInfo + Instance)->Version;
        (UpdBaseBoardInfo + Instance)->FeatureFlag           = *((BASE_BOARD_FEATURE_FLAGS*)&(BaseBoardInfo + Instance)->FeatureFlags);
        (UpdBaseBoardInfo + Instance)->BoardType             = (BaseBoardInfo + Instance)->BoardType;
        (UpdBaseBoardStrings + Instance)->LocationInChassis  = (BaseBoardInfo + Instance)->LocationInChassis;
      } else { // otherwise update the default SMBIOS Board Info
        (UpdBaseBoardStrings + Instance)->ProductName        = mDefaultSmbiosBoardInfo.BaseBoard->ProductName;
        (UpdBaseBoardStrings + Instance)->Manufacturer       = mDefaultSmbiosBoardInfo.BaseBoard->Manufacturer;
        (UpdBaseBoardStrings + Instance)->Version            = mDefaultSmbiosBoardInfo.BaseBoard->Version;
        (UpdBaseBoardInfo + Instance)->FeatureFlag           = *((BASE_BOARD_FEATURE_FLAGS*)&mDefaultSmbiosBoardInfo.BaseBoard->FeatureFlags);
        (UpdBaseBoardInfo + Instance)->BoardType             = mDefaultSmbiosBoardInfo.BaseBoard->BoardType;
        (UpdBaseBoardStrings + Instance)->LocationInChassis  = mDefaultSmbiosBoardInfo.BaseBoard->LocationInChassis;
      }
    }
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].Info               = UpdBaseBoardInfo;
  mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].Strings            = UpdBaseBoardStrings;
  mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].NoOfInstances      = MaxInstances;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[BaseBoardManufacturer].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateBaseBoardManufacturerInfo: Base Board Info Type 2 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Chassis Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateChassisManufacturerInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          MaxInstances;
  CHASSIS_INFO                   *ChassisInfo=NULL;
  SMBIOS_TABLE_TYPE3             *DefChassisInfoInfo;
  SMBIOS_TABLE_TYPE3             *UpdChassisInfoInfo;
  SMBIOS_TABLE_TYPE03_STRINGS    *DefChassisInfoStrings;
  SMBIOS_TABLE_TYPE03_STRINGS    *UpdChassisInfoStrings;
  //
  // Get Chassis Info and Strings
  //
  DefChassisInfoInfo        = mDefaultSmbiosPlatformInfo[ChassisManufacturer].Info;
  DefChassisInfoStrings     = mDefaultSmbiosPlatformInfo[ChassisManufacturer].Strings;
  MaxInstances              = NUM_CHASSIS_INFO;

  if(DefChassisInfoInfo == NULL || DefChassisInfoStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateChassisManufacturerInfo: Default Chassis Info Type 3 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdChassisInfoInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE3) * MaxInstances);
    if (UpdChassisInfoInfo == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateChassisManufacturerInfo: Can't allocate enough resource for UpdChassisInfoInfo variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
    UpdChassisInfoStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE03_STRINGS) * MaxInstances);
    if (UpdChassisInfoStrings == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateChassisManufacturerInfo: Can't allocate enough resource for UpdChassisInfoStrings variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdChassisInfoInfo        = DefChassisInfoInfo;
    UpdChassisInfoStrings     = DefChassisInfoStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  for (Instance = 0; Instance < MaxInstances; Instance++){
    if(MaxInstances > 1){
      CopyMem((UpdChassisInfoInfo+Instance), DefChassisInfoInfo, sizeof(SMBIOS_TABLE_TYPE3));
      CopyMem((UpdChassisInfoStrings+Instance), DefChassisInfoStrings, sizeof(SMBIOS_TABLE_TYPE03_STRINGS));
    }
    (UpdChassisInfoInfo+Instance)->Type = GetChassisType(); // Get Chassis Type from PCD and update it in Chassis Info
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo){
        ChassisInfo = (CHASSIS_INFO*)mSmbiosBoardInfo->ChassisInfo;
      }
      if(mSmbiosBoardInfo && (ChassisInfo + Instance)){
        (UpdChassisInfoStrings+Instance)->Manufacturer          = (ChassisInfo + Instance)->Manufacturer;
        (UpdChassisInfoInfo+Instance)->Type                     = (ChassisInfo + Instance)->Type;
        (UpdChassisInfoInfo+Instance)->BootupState              = (ChassisInfo + Instance)->Bootup;
        (UpdChassisInfoInfo+Instance)->PowerSupplyState         = (ChassisInfo + Instance)->PowerSupply;
        (UpdChassisInfoInfo+Instance)->ThermalState             = (ChassisInfo + Instance)->Thermal;
        (UpdChassisInfoInfo+Instance)->SecurityStatus           = (ChassisInfo + Instance)->Security;
        (UpdChassisInfoInfo+Instance)->Height                   = (ChassisInfo + Instance)->Height;
        (UpdChassisInfoInfo+Instance)->NumberofPowerCords       = (ChassisInfo + Instance)->NumberofPowerCords;
       } else { // otherwise update the default SMBIOS Board Info
        (UpdChassisInfoStrings+Instance)->Manufacturer          = mDefaultSmbiosBoardInfo.ChassisInfo->Manufacturer;
        (UpdChassisInfoInfo+Instance)->Type                     = mDefaultSmbiosBoardInfo.ChassisInfo->Type;
        (UpdChassisInfoInfo+Instance)->BootupState              = mDefaultSmbiosBoardInfo.ChassisInfo->Bootup;
        (UpdChassisInfoInfo+Instance)->PowerSupplyState         = mDefaultSmbiosBoardInfo.ChassisInfo->PowerSupply;
        (UpdChassisInfoInfo+Instance)->ThermalState             = mDefaultSmbiosBoardInfo.ChassisInfo->Thermal;
        (UpdChassisInfoInfo+Instance)->SecurityStatus           = mDefaultSmbiosBoardInfo.ChassisInfo->Security;
        (UpdChassisInfoInfo+Instance)->Height                   = mDefaultSmbiosBoardInfo.ChassisInfo->Height;
        (UpdChassisInfoInfo+Instance)->NumberofPowerCords       = mDefaultSmbiosBoardInfo.ChassisInfo->NumberofPowerCords;
       }
    }
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[ChassisManufacturer].Info                = UpdChassisInfoInfo;
  mDefaultSmbiosPlatformInfo[ChassisManufacturer].Strings             = UpdChassisInfoStrings;
  mDefaultSmbiosPlatformInfo[ChassisManufacturer].NoOfInstances       = MaxInstances;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[ChassisManufacturer].IsPoolAllocated   = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[ChassisManufacturer].IsPoolAllocated   = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateChassisManufacturerInfo: Chassis Info Type 3 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Port Connector Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdatePortConnectorInfo (
  VOID
  )
{
  UINT8                         Instance;
  UINT8                         Index;
  UINT8                         MaxInstances;
  UINT8                         TableInstances;
  SMBIOS_TABLE_TYPE8            *DefPortConnInfo;
  SMBIOS_TABLE_TYPE8            *UpdPortConnInfo;
  SMBIOS_TABLE_TYPE8_STRINGS    *DefPortConnStrings;
  SMBIOS_TABLE_TYPE8_STRINGS    *UpdPortConnStrings;
  //
  // Get Default Port Connectors Info and Strings
  //
  DefPortConnInfo        = mDefaultSmbiosPlatformInfo[PortConnectors].Info;
  DefPortConnStrings     = mDefaultSmbiosPlatformInfo[PortConnectors].Strings;
  TableInstances         = NUM_DEFINED_PORT_TYPES;
  MaxInstances           = NUM_DEFINED_PORT_TYPES;


  if (DefPortConnInfo == NULL || DefPortConnStrings == NULL) {
    DEBUG ((DEBUG_INFO, "UpdatePortConnectorInfo: Default Port Info Type 8 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Deduct the entries that are not required to publish
  //
  for (Index = 0; Index < TableInstances; Index++) {
    if (PortInfoTable[Index].IsPublishRequired == NotRequired) {
      MaxInstances--;
    }
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if (MaxInstances > 1) { // Allocate Memory in case of multiple instances
    UpdPortConnInfo        = AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE8) * MaxInstances);
    UpdPortConnStrings     = AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE8_STRINGS) * MaxInstances);
    if (!UpdPortConnStrings || !UpdPortConnInfo) {
      DEBUG ((DEBUG_ERROR, "Can't allocate enough resource for UpdPortConn variables!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else {  // otherwise just default pointer
    UpdPortConnInfo        = DefPortConnInfo;
    UpdPortConnStrings     = DefPortConnStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  Instance = 0;
  for (Index = 0; Index < MaxInstances; Index++) {
    //
    // Update the RVP board info here.
    //
    if (IsSmbiosBoardInfoEnabled) { // Check whether SMBIOS Board Info code is enabled by RVP.
      if (mSmbiosBoardInfo) {
        if ((mSmbiosBoardInfo->SupportedPortConnectors >> Index) & BIT0) {
        } else {
          continue;
        }
      } else { // otherwise update the default SMBIOS Board Info
        if (!((mDefaultSmbiosBoardInfo.SupportedPortConnectors >> Index) & BIT0)) {
          continue;
        }
      }
    }
    //
    // Skip instance that is not required to be published
    //
    if (PortInfoTable[Index].IsPublishRequired == NotRequired) {
      continue;
    }
    if (MaxInstances > 1) {
      CopyMem ((UpdPortConnInfo+Instance), DefPortConnInfo, sizeof (SMBIOS_TABLE_TYPE8));
      CopyMem ((UpdPortConnStrings+Instance), DefPortConnStrings, sizeof (SMBIOS_TABLE_TYPE8_STRINGS));
    }
    (UpdPortConnInfo + Instance)->InternalConnectorType             = PortInfoTable[Index].InternalConnectorType;
    (UpdPortConnInfo + Instance)->ExternalConnectorType             = PortInfoTable[Index].ExternalConnectorType;
    (UpdPortConnInfo + Instance)->PortType                          = PortInfoTable[Index].PortType;
    (UpdPortConnStrings+Instance)->InternalReferenceDesignator      = PortInfoTable[Index].InternalDesignator;
    (UpdPortConnStrings+Instance)->ExternalReferenceDesignator      = PortInfoTable[Index].ExternalDesignator;
    Instance++;
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[PortConnectors].Info               = UpdPortConnInfo;
  mDefaultSmbiosPlatformInfo[PortConnectors].Strings            = UpdPortConnStrings;
  mDefaultSmbiosPlatformInfo[PortConnectors].NoOfInstances      = Instance;

  if (MaxInstances > 1) {
    mDefaultSmbiosPlatformInfo[PortConnectors].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[PortConnectors].IsPoolAllocated  = FALSE;
  }
  DEBUG ((DEBUG_INFO, "UpdatePortConnectorInfo: Port Info Type 8 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update System Config Options in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateSystemOptionString(
  VOID
  )
{
  SMBIOS_TABLE_TYPE12             *UpdSysConfigInfo;
  SMBIOS_TABLE_TYPE12_STRINGS     *UpdSysConfigStrings;
  //
  // Get Default Bios Vendor Info and Strings
  //
  UpdSysConfigInfo                     = mDefaultSmbiosPlatformInfo[SystemOptionString].Info;
  UpdSysConfigStrings                  = mDefaultSmbiosPlatformInfo[SystemOptionString].Strings;

  if(UpdSysConfigInfo == NULL || UpdSysConfigStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateSystemOptionString: Default System Config Option Info Type 12 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Update the Platform Configuration Options
  //
  UpdSysConfigStrings->StringCount       = SysConfig12.ConfigOptions;
  //
  // Update the RVP board info here.
  //
  if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
    if(mSmbiosBoardInfo){
      UpdSysConfigStrings->StringCount   = mSmbiosBoardInfo->SystemConfigOptions;
    } else { // otherwise update the default SMBIOS Board Info
      UpdSysConfigStrings->StringCount   = mDefaultSmbiosBoardInfo.SystemConfigOptions;
    }
  }

  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[SystemOptionString].Info                 = UpdSysConfigInfo;
  mDefaultSmbiosPlatformInfo[SystemOptionString].Strings              = UpdSysConfigStrings;
  mDefaultSmbiosPlatformInfo[SystemOptionString].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[SystemOptionString].IsPoolAllocated      = FALSE;
  DEBUG((DEBUG_INFO, "UpdateSystemOptionString: System Config Option Info Type 12 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Portable Battery Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdatePortableBatteryInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          Index;
  UINT8                          MaxInstances;
  SMBIOS_TABLE_TYPE22            *DefPortableBatteryInfo;
  SMBIOS_TABLE_TYPE22            *UpdPortableBatteryInfo;
  SMBIOS_TABLE_TYPE22_STRINGS    *DefPortableBatteryStrings;
  SMBIOS_TABLE_TYPE22_STRINGS    *UpdPortableBatteryStrings;
  //
  // Get Default Cooling Device Info and Strings
  //
  DefPortableBatteryInfo        = mDefaultSmbiosPlatformInfo[PortableBattery].Info;
  DefPortableBatteryStrings     = mDefaultSmbiosPlatformInfo[PortableBattery].Strings;
  MaxInstances                  = NUM_PORTABLE_BATTERIES;

  if(DefPortableBatteryInfo == NULL || DefPortableBatteryStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdatePortableBatteryInfo: Default Portable Battery Info Type 22 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdPortableBatteryInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE22) * MaxInstances);
    UpdPortableBatteryStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE22_STRINGS) * MaxInstances);
    if (! UpdPortableBatteryInfo || ! UpdPortableBatteryStrings) {
      DEBUG((DEBUG_ERROR, "Can't allocate enough resource for UpdPortableBattery variables!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdPortableBatteryInfo        = DefPortableBatteryInfo;
    UpdPortableBatteryStrings     = DefPortableBatteryStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  Instance = 0;
  for (Index = 0; Index < MaxInstances; Index++){
    if(MaxInstances > 1){
      CopyMem((UpdPortableBatteryInfo+Instance), DefPortableBatteryInfo, sizeof(SMBIOS_TABLE_TYPE22));
      CopyMem((UpdPortableBatteryStrings+Instance), DefPortableBatteryStrings, sizeof(SMBIOS_TABLE_TYPE22_STRINGS));
    }
    UpdateBatteryInfo(&PortableBatteryInfoTable[Index]); // Update Battery Info with EC data
    if (PortableBatteryInfoTable[Index].IsPublishRequired == Required){
      (UpdPortableBatteryStrings+Instance)->Location                =  PortableBatteryInfoTable[Index].Location;
      (UpdPortableBatteryStrings+Instance)->Manufacturer            =  PortableBatteryInfoTable[Index].Manufacturer;
      (UpdPortableBatteryStrings+Instance)->ManufacturerDate        =  PortableBatteryInfoTable[Index].ManufactureDate;
      (UpdPortableBatteryStrings+Instance)->SerialNumber            =  PortableBatteryInfoTable[Index].SerialNumber;
      (UpdPortableBatteryStrings+Instance)->DeviceName              =  PortableBatteryInfoTable[Index].DevName;
      (UpdPortableBatteryInfo+Instance)->DeviceChemistry            =  PortableBatteryInfoTable[Index].DevChemistry;
      (UpdPortableBatteryInfo+Instance)->DeviceCapacity             =  PortableBatteryInfoTable[Index].DevCapacity;
      (UpdPortableBatteryInfo+Instance)->DesignVoltage              =  PortableBatteryInfoTable[Index].Voltage;
      (UpdPortableBatteryInfo+Instance)->MaximumErrorInBatteryData  =  PortableBatteryInfoTable[Index].MaxErrorInBatteryData;
      (UpdPortableBatteryInfo+Instance)->DesignCapacityMultiplier   =  PortableBatteryInfoTable[Index].CapacityMultiplier;
      (UpdPortableBatteryInfo+Instance)->OEMSpecific                =  PortableBatteryInfoTable[Index].Oem;
      Instance++;
    }
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[PortableBattery].Info             = UpdPortableBatteryInfo;
  mDefaultSmbiosPlatformInfo[PortableBattery].Strings          = UpdPortableBatteryStrings;
  mDefaultSmbiosPlatformInfo[PortableBattery].NoOfInstances    = Instance;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[PortableBattery].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[PortableBattery].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdatePortableBatteryInfo: Portable Battery Info Type 22 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Cooling Device Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateCoolingDeviceInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          Index;
  UINT8                          MaxInstances;
  COOLING_DEV                    *CoolingDev;
  SMBIOS_TABLE_TYPE27            *DefCoolingDevInfo;
  SMBIOS_TABLE_TYPE27            *UpdCoolingDevInfo;
  SMBIOS_TABLE_TYPE27_STRINGS    *DefCoolingDevStrings;
  SMBIOS_TABLE_TYPE27_STRINGS    *UpdCoolingDevStrings;
  //
  // Get Default Cooling Device Info and Strings
  //
  DefCoolingDevInfo        = mDefaultSmbiosPlatformInfo[CoolingDevice].Info;
  DefCoolingDevStrings     = mDefaultSmbiosPlatformInfo[CoolingDevice].Strings;
  MaxInstances             = NUM_COOLING_DEVICES;

  if(DefCoolingDevInfo == NULL || DefCoolingDevStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateCoolingDeviceInfo: Default Cooling Device Info Type 27 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdCoolingDevInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE27) * MaxInstances);
    UpdCoolingDevStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE27_STRINGS) * MaxInstances);
    if (! UpdCoolingDevStrings || ! UpdCoolingDevInfo) {
      DEBUG((DEBUG_ERROR, "Can't allocate enough resource for UpdCoolingDev variables!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdCoolingDevInfo        = DefCoolingDevInfo;
    UpdCoolingDevStrings     = DefCoolingDevStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  Instance = 0;
  for (Index = 0; Index < MaxInstances; Index++){
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo){
        CoolingDev = (COOLING_DEV*)mSmbiosBoardInfo->CoolingDev;
      }
    }
    if(MaxInstances > 1){
      CopyMem((UpdCoolingDevInfo+Instance), DefCoolingDevInfo, sizeof(SMBIOS_TABLE_TYPE27));
      CopyMem((UpdCoolingDevStrings+Instance), DefCoolingDevStrings, sizeof(SMBIOS_TABLE_TYPE27_STRINGS));
    }
    //
    // Set the PWM to run at 100 % (0x64) and read the Nominal Speed from EC
    //
    GetFanSpeed(0x64,&CoolingDevInfoTable[Index].Speed);
    (UpdCoolingDevInfo+Instance)->DeviceTypeAndStatus.CoolingDevice          = CoolingDevInfoTable[Index].Type;
    (UpdCoolingDevInfo+Instance)->DeviceTypeAndStatus.CoolingDeviceStatus    = CoolingDevInfoTable[Index].Status;
    (UpdCoolingDevInfo+Instance)->CoolingUnitGroup                           = CoolingDevInfoTable[Index].Group;
    (UpdCoolingDevInfo+Instance)->OEMDefined                                 = CoolingDevInfoTable[Index].Oem;
    (UpdCoolingDevInfo+Instance)->NominalSpeed                               = CoolingDevInfoTable[Index].Speed;
    (UpdCoolingDevStrings+Instance)->Description                             = CoolingDevInfoTable[Index].Description;
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo && (CoolingDev + Instance)){
        (UpdCoolingDevInfo+Instance)->DeviceTypeAndStatus.CoolingDevice       = (CoolingDev + Index)->Type;
        (UpdCoolingDevStrings+Instance)->Description                          = (CoolingDev + Index)->Description;
      } else { // otherwise update the default SMBIOS Board Info
        (UpdCoolingDevInfo+Instance)->DeviceTypeAndStatus.CoolingDevice       = mDefaultSmbiosBoardInfo.CoolingDev->Type;
        (UpdCoolingDevStrings+Instance)->Description                          = mDefaultSmbiosBoardInfo.CoolingDev->Description;
      }
    }
    Instance++;
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[CoolingDevice].Info               = UpdCoolingDevInfo;
  mDefaultSmbiosPlatformInfo[CoolingDevice].Strings            = UpdCoolingDevStrings;
  mDefaultSmbiosPlatformInfo[CoolingDevice].NoOfInstances      = Instance;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[CoolingDevice].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[CoolingDevice].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateCoolingDeviceInfo: Cooling Device Info Type 27 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update BIOS Language Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateBiosLanguageInfo(
  VOID
  )
{
  SMBIOS_TABLE_TYPE13             *UpdLangInfoInfo;
  SMBIOS_TABLE_TYPE13_STRINGS     *UpdLangInfoStrings;
  UINT8                           Index;
  //
  // Get Default Bios Langauge Info and Strings
  //
  UpdLangInfoInfo                                 = mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].Info;
  UpdLangInfoStrings                              = mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].Strings;

  if(UpdLangInfoInfo == NULL || UpdLangInfoStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateBiosLanguageInfo: Default Bios Language Info Type 13 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Update the Language String Format and Current Language as Abbreviated and English
  //
  UpdLangInfoInfo->Flags            = Abbreviated;
  UpdLangInfoInfo->CurrentLanguages = English;
  //
  // Update the language strings in either Abbreviated or Long format.
  //
  if(UpdLangInfoInfo->Flags == Abbreviated){
    for(Index = 0; Index < MAX_LANGUAGES; Index++)
      (UpdLangInfoStrings+Index)->CurrentLanguages = LanguagesAbbr[Index];
  } else {
    for(Index = 0; Index < MAX_LANGUAGES; Index++)
      (UpdLangInfoStrings+Index)->CurrentLanguages = LanguagesLong[Index];
  }

  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].Info                 = UpdLangInfoInfo;
  mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].Strings              = UpdLangInfoStrings;
  mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].IsPoolAllocated      = FALSE;
  mDefaultSmbiosPlatformInfo[BiosLanguagesInfo].StringCount          = MAX_LANGUAGES;
  DEBUG((DEBUG_INFO, "UpdateBiosLanguageInfo: Bios Language Info Type 13 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Power Supply Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdatePowerSupplyInfo(
  VOID
  )
{
  SMBIOS_TABLE_TYPE39             *UpdPowerSupplyInfo;
  SMBIOS_TABLE_TYPE39_STRINGS     *UpdPowerSupplyStrings;
  //
  // Get Default Power Supply Info and Strings
  //
  UpdPowerSupplyInfo                           = mDefaultSmbiosPlatformInfo[SystemPowerSupply].Info;
  UpdPowerSupplyStrings                        = mDefaultSmbiosPlatformInfo[SystemPowerSupply].Strings;

  if(UpdPowerSupplyInfo == NULL || UpdPowerSupplyStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdatePowerSupplyInfo: Default Power Supply Info Type 39 is not available!!\n"));
    return EFI_SUCCESS;
  }

  //
  // TODO: Power Supply Info can be updated according to platform here.
  //

  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[SystemPowerSupply].Info                 = UpdPowerSupplyInfo;
  mDefaultSmbiosPlatformInfo[SystemPowerSupply].Strings              = UpdPowerSupplyStrings;
  mDefaultSmbiosPlatformInfo[SystemPowerSupply].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[SystemPowerSupply].IsPoolAllocated      = FALSE;
  DEBUG((DEBUG_INFO, "UpdatePowerSupplyInfo: Power Supply Info Type 39 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Boot Info Status in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateBootInfoStatus(
  VOID
  )
{
  SMBIOS_TABLE_TYPE32             *UpdBootInfoInfo;
  //
  // Get Default Boot Info
  //
  UpdBootInfoInfo                        = mDefaultSmbiosPlatformInfo[BootInfoStatus].Info;

  if(UpdBootInfoInfo == NULL){
    DEBUG((DEBUG_INFO, "UpdateBiosLanguageInfo: Default Boot Status Info Type 32 is not available!!\n"));
    return EFI_SUCCESS;
  }
  UpdBootInfoInfo->BootStatus            = BootInformationStatusNoError;  // Update Boot Status as No Error;

  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[BootInfoStatus].Info                 = UpdBootInfoInfo;
  mDefaultSmbiosPlatformInfo[BootInfoStatus].NoOfInstances        = 1;
  mDefaultSmbiosPlatformInfo[BootInfoStatus].IsPoolAllocated      = FALSE;
  DEBUG((DEBUG_INFO, "UpdateBiosLanguageInfo: Boot Status Info Type 32 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update OnBoard Device Extended Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateOnboardDeviceExtInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          Index;
  UINT8                          MaxInstances;
  UINT8                          DeviceStatus;
  ONBOARD_DEV_ADDR               *DevAddr;
  SMBIOS_TABLE_TYPE41            *DefOnboardDevExtInfo;
  SMBIOS_TABLE_TYPE41            *UpdOnboardDevExtInfo;
  SMBIOS_TABLE_TYPE41_STRINGS    *DefOnboardDevExtStrings;
  SMBIOS_TABLE_TYPE41_STRINGS    *UpdOnboardDevExtStrings;
  //
  // Get Default OnBoard Device Extended Record and Strings
  //
  DefOnboardDevExtInfo        = mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].Info;
  DefOnboardDevExtStrings     = mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].Strings;
  MaxInstances                = NUM_ONBOARD_DEVICES_EXT;

  if(DefOnboardDevExtInfo == NULL || DefOnboardDevExtStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateOnboardDeviceExtInfo: Default OnBoard Device Extended Info Type 41 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdOnboardDevExtInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE41) * MaxInstances);
    UpdOnboardDevExtStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE41_STRINGS) * MaxInstances);
    if (! UpdOnboardDevExtInfo || ! UpdOnboardDevExtStrings) {
      DEBUG((DEBUG_ERROR, "Can't allocate enough resource for UpdOnboardDevExt variables!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdOnboardDevExtInfo        = DefOnboardDevExtInfo;
    UpdOnboardDevExtStrings     = DefOnboardDevExtStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  Instance = 0;
  for (Index = 0; Index < MaxInstances; Index++){
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo){
        if((mSmbiosBoardInfo->SupportedOnboardDev >> Index) & BIT0){
          DevAddr = (ONBOARD_DEV_ADDR*)mSmbiosBoardInfo->OnBoardDevAddr;
        } else {
          continue;
        }
      } else { // otherwise update the default SMBIOS Board Info
        if(!((mDefaultSmbiosBoardInfo.SupportedOnboardDev >> Index) & BIT0))
          continue;
      }
    }
    if(MaxInstances > 1){
      CopyMem((UpdOnboardDevExtInfo+Instance), DefOnboardDevExtInfo, sizeof(SMBIOS_TABLE_TYPE41));
      CopyMem((UpdOnboardDevExtStrings+Instance), DefOnboardDevExtStrings, sizeof(SMBIOS_TABLE_TYPE41_STRINGS));
    }
    //
    // Get device status
    //
    GetOnBoardDeviceType(
      (MISC_ONBOARD_DEVICE_TYPE) OnboardExtInfoTable[Instance].DeviceType,
      &OnboardExtInfoTable[Instance].DeviceStatus
      );
    (UpdOnboardDevExtInfo + Instance)->DeviceType                = (UINT8)(OnboardExtInfoTable[Index].DeviceType & 0x7F) | (UINT8)(OnboardExtInfoTable[Index].DeviceStatus << 7);
    (UpdOnboardDevExtInfo + Instance)->DeviceTypeInstance        = 0;
    (UpdOnboardDevExtInfo + Instance)->SegmentGroupNum           = OnboardExtInfoTable[Index].Segment;
    (UpdOnboardDevExtInfo + Instance)->BusNum                    = OnboardExtInfoTable[Index].Bus;

    switch (OnboardExtInfoTable[Index].DeviceType) {
      case OnBoardDeviceExtendedTypeSound:
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum            = (HdaDevNumber () << 3) | HdaFuncNumber ();
        break;
      case OnBoardDeviceExtendedTypeSATAController:
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum            = (SataDevNumber (SATA_1_CONTROLLER_INDEX) << 3) | SataFuncNumber (SATA_1_CONTROLLER_INDEX);
        break;
      case OnBoardDeviceExtendedTypeEthernet:
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum            = (GbeDevNumber () << 3) | GbeFuncNumber ();
        break;
      case OnBoardDeviceExtendedTypeVideo:
      default:
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum            = OnboardExtInfoTable[Index].DevFunc;
    }
    //
    // Update the RVP board info here.
    //
    if(IsSmbiosBoardInfoEnabled){ // Check whether SMBIOS Board Info code is enabled by RVP.
      if(mSmbiosBoardInfo && (DevAddr + Instance)){
        (UpdOnboardDevExtInfo + Instance)->SegmentGroupNum    = (DevAddr + Index)->Seg;
        (UpdOnboardDevExtInfo + Instance)->BusNum             = (DevAddr + Index)->Bus;
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum         = ((DevAddr + Index)->Dev << 3) |(DevAddr + Index)->Func;
      } else { // otherwise update the default SMBIOS Board Info
       (UpdOnboardDevExtInfo + Instance)->SegmentGroupNum     = mDefaultSmbiosBoardInfo.OnBoardDevAddr->Seg;
       (UpdOnboardDevExtInfo + Instance)->BusNum            = mDefaultSmbiosBoardInfo.OnBoardDevAddr->Bus;
       (UpdOnboardDevExtInfo + Instance)->DevFuncNum        = (mDefaultSmbiosBoardInfo.OnBoardDevAddr->Dev << 3) | mDefaultSmbiosBoardInfo.OnBoardDevAddr->Func;
      }
      GetOnBoardDeviceStatus(
        (UpdOnboardDevExtInfo + Instance)->BusNum,
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum >> 3,
        (UpdOnboardDevExtInfo + Instance)->DevFuncNum & 7,
        &DeviceStatus
        );
      (UpdOnboardDevExtInfo + Instance)->DeviceType           = (UINT8)((UpdOnboardDevExtInfo + Instance)->DeviceType & 0x7F) | (UINT8) (DeviceStatus << 7);
    }

    (UpdOnboardDevExtStrings+Instance)->DescriptionString      = OnboardExtInfoTable[Index].Designation;
    Instance++;
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].Info             = UpdOnboardDevExtInfo;
  mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].Strings          = UpdOnboardDevExtStrings;
  mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].NoOfInstances    = Instance;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[OnBoardDeviceExtended].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateOnboardDeviceExtInfo: OnBoard Device Extended Info Type 41 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Oem type 136 Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateOemType136(
  VOID
  )
{
  UINT8                 Instance;
  UINT8                 MaxInstances;
  SMBIOS_TABLE_TYPE136  *DefOemType136;
  SMBIOS_TABLE_TYPE136  *UpdOemType136;

  //
  // Get Default Oem Type 136 data
  //
  DefOemType136 = mDefaultSmbiosPlatformInfo[OemType136].Info;
  MaxInstances  = NUM_OEM_TYPE_136;
  if(DefOemType136 == NULL){
    DEBUG((DEBUG_INFO, "UpdateOemType136: Default Oem Type 136 Info is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Allocates the memory for Maximum Instance required
  //
  if (MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdOemType136 = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE136) * MaxInstances);
    if (UpdOemType136 == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateOemType136: Can't allocate enough resource for UpdOemType136 variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use default to update
    UpdOemType136 = DefOemType136;
  }
  //
  // Copy the default data with instance to be updated
  //
  for (Instance = 0; Instance < MaxInstances; Instance++){
    CopyMem((UpdOemType136+Instance), DefOemType136, sizeof(SMBIOS_TABLE_TYPE136));
    //
    // TODO: Update the Platform Info here.
    //
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[OemType136].Info               = UpdOemType136;
  mDefaultSmbiosPlatformInfo[OemType136].NoOfInstances      = MaxInstances;

  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[OemType136].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[OemType136].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateOemType136: Oem Type 136 Info is updated\n"));
  return EFI_SUCCESS;
}

/**
Update System Slot Info in Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateSystemSlotInfo(
  VOID
  )
{
  UINT8                          Instance;
  UINT8                          Index;
  UINT8                          MaxInstances;
  SYSTEM_SLOT_ENTRY              *mSlotEntries;
  SMBIOS_TABLE_TYPE9             *DefSystemSlotInfo;
  SMBIOS_TABLE_TYPE9             *UpdSystemSlotInfo;
  SMBIOS_TABLE_TYPE9_STRINGS     *DefSystemSlotStrings;
  SMBIOS_TABLE_TYPE9_STRINGS     *UpdSystemSlotStrings;
  SYSTEM_SLOT_INFO               *SlotEntry;
  UINT64                         PcieRpBaseAddr;

  PcieRpBaseAddr = 0;

  //
  // Get Default OnBoard Device Extended Record and Strings
  //
  DefSystemSlotInfo           = mDefaultSmbiosPlatformInfo[SystemSlot].Info;
  DefSystemSlotStrings        = mDefaultSmbiosPlatformInfo[SystemSlot].Strings;

  if(DefSystemSlotInfo == NULL || DefSystemSlotStrings == NULL){
    DEBUG((DEBUG_INFO, "UpdateSystemSlotInfo: Default System Slot Info Type 9 is not available!!\n"));
    return EFI_SUCCESS;
  }
  //
  // Get Slot entries Specific to the Board
  //
  mSlotEntries = (SYSTEM_SLOT_ENTRY *) (UINTN) PcdGet64 (PcdSmbiosMainSlotEntry);
  if (mSlotEntries == NULL) {
    mSlotEntries = &gDefaultSlotEntryTable;
  }
  MaxInstances = mSlotEntries->Numberofentries;
  //
  // Allocates the memory for Maximum Instance required
  //
  if(MaxInstances > 1){ // allocate memory in case of multiple instances
    UpdSystemSlotInfo        = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE9) * MaxInstances);
    if (UpdSystemSlotInfo == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateSystemSlotInfo: Can't allocate enough resource for UpdSystemSlotInfo variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
    UpdSystemSlotStrings     = AllocateZeroPool(sizeof (SMBIOS_TABLE_TYPE9_STRINGS) * MaxInstances);
    if (UpdSystemSlotStrings == NULL) {
      DEBUG((DEBUG_ERROR, "UpdateSystemSlotInfo: Can't allocate enough resource for UpdSystemSlotStrings variable!!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else { // otherwise use the default to update
    UpdSystemSlotInfo        = DefSystemSlotInfo;
    UpdSystemSlotStrings     = DefSystemSlotStrings;
  }
  //
  // Copy the default data and update the data for each instances
  //
  Instance = 0;
  for (Index = 0; Index < MaxInstances; Index++){
    if(MaxInstances > 1){
      CopyMem((UpdSystemSlotInfo+Instance), DefSystemSlotInfo, sizeof(SMBIOS_TABLE_TYPE9));
      CopyMem((UpdSystemSlotStrings+Instance), DefSystemSlotInfo, sizeof(SMBIOS_TABLE_TYPE9_STRINGS));
    }
    SlotEntry = &mSlotEntries->Slotinfo[Index];
    if (SlotEntry->Isvalid){
      (UpdSystemSlotInfo + Instance)->SlotType                = SlotEntry->SlotType;
      (UpdSystemSlotInfo + Instance)->SlotDataBusWidth        = SlotEntry->SlotDataBusWidth;
      //
      // Check the Root Port is used by Plug-in card or enabled for hot plug
      //
      PcieRpBaseAddr = PCI_SEGMENT_LIB_ADDRESS (0, SlotEntry->BusNum, (UINT32)SlotEntry->DevNum, (UINT32)SlotEntry->FuncNum, 0);
      if ((PciSegmentRead16 (PcieRpBaseAddr) != 0xFFFF)) {
        SlotEntry->CurrentUsage = SlotUsageInUse;
      }
      (UpdSystemSlotInfo + Instance)->CurrentUsage            = SlotEntry->CurrentUsage;
      (UpdSystemSlotInfo + Instance)->SlotLength              = SlotEntry->SlotLength;
      (UpdSystemSlotInfo + Instance)->SlotID                  = SlotEntry->SlotID;
      (UpdSystemSlotInfo + Instance)->SlotCharacteristics1    = SlotEntry->SlotCharacteristics1;
      (UpdSystemSlotInfo + Instance)->SlotCharacteristics2    = SlotEntry->SlotCharacteristics2;
      (UpdSystemSlotInfo + Instance)->SegmentGroupNum         = SlotEntry->SegmentGroupNum;
      (UpdSystemSlotInfo + Instance)->BusNum                  = SlotEntry->BusNum;
      (UpdSystemSlotInfo + Instance)->DevFuncNum              = ((SlotEntry->DevNum << 3) | SlotEntry->FuncNum);

      (UpdSystemSlotStrings+Instance)->SlotDesignation        = SlotEntry->SlotDesignation;
      Instance++;
    }
  }
  //
  // Update the Updated Platform info into Smbios Platform Table
  //
  mDefaultSmbiosPlatformInfo[SystemSlot].Info             = UpdSystemSlotInfo;
  mDefaultSmbiosPlatformInfo[SystemSlot].Strings          = UpdSystemSlotStrings;
  mDefaultSmbiosPlatformInfo[SystemSlot].NoOfInstances    = Instance;
  if(MaxInstances > 1){
    mDefaultSmbiosPlatformInfo[SystemSlot].IsPoolAllocated  = TRUE;
  } else {
    mDefaultSmbiosPlatformInfo[SystemSlot].IsPoolAllocated  = FALSE;
  }
  DEBUG((DEBUG_INFO, "UpdateSystemSlotInfo: System Slot Info Type 9 is updated\n"));
  return EFI_SUCCESS;
}

/**
Update Smbios Platform Info Table.
This function provides Sample code to update Smbios Platform Info.
Platform Owner can customize it according to the Platform.

@retval     EFI_SUCCESS   successful

**/
EFI_STATUS
UpdateSmbiosPlatformInfo(
  VOID
  )
{
  GetSmbiosPlatformInfoTable();              // First Get the Smbios Platform Information table

  if (mSmbiosPlatformInfo){

    GetSmbiosBoardInfoPCDs();                // Get values of Smbios Board Information PCDs

    UpdateSystemManufacturerInfo();          // Update System Manufacturer Info

    UpdateBaseBoardManufacturerInfo();       // Update Base Board Info

    UpdateChassisManufacturerInfo();         // Update Chassis Info

    UpdatePortConnectorInfo();               // Update Port Info

    UpdateSystemOptionString();              // Update System Config Options

    UpdatePortableBatteryInfo();             // Update Portable Battery Info

    UpdateCoolingDeviceInfo ();              // Update Cooling Device Info

    UpdateBiosLanguageInfo();                // Update BIOS Languages Info

    UpdateBiosVendorInfo();                  // Update Bios Vendor Info

    UpdateBootInfoStatus();                  // Update Boot Info Status

    UpdatePowerSupplyInfo();                 // Update Power Supply Info

    UpdateOnboardDeviceExtInfo();            // Update OnBoard Extended Info

    UpdateOemType136();                      // OEM Type 136

    UpdateSystemSlotInfo();                  // System Slot Info
  } else {
    DEBUG((DEBUG_INFO, "UpdateSmbiosPlatformInfo: Smbios Platform Information Table is not available\n!!"));
  }

  return EFI_SUCCESS;
}

/**
Standard EFI driver point. This driver updates the Platform
Info required for all SMBIOS Platform Tables.

@param[in] ImageHandle     Handle for the image of this driver
@param[in] SystemTable     Pointer to the EFI System Table

@retval EFI_SUCCESS        The data was successfully updated.

**/
EFI_STATUS
EFIAPI
SmbiosPlatformInfoEntryPoint(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  //
  // Set default Smbios Platform Info into PCD which can be consumed in SmbiosMiscDxe driver
  // in order to add Smbios Platform records.
  //
  PcdSet64S(PcdSmbiosPlatformInfo, (UINTN) &mDefaultSmbiosPlatformInfo);

  //
  // Update Smbios Platform Info specific to platform
  //
  UpdateSmbiosPlatformInfo();

  return EFI_SUCCESS;
}
