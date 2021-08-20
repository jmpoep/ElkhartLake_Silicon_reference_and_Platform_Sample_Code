/** @file
 Entry point of VTIO DXE driver.

 This driver will install the VTIO ACPI table and invokes VtioMefunction.

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

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/MemoryAllocationLib.h>
#include <SetupVariable.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <VtioDxe.h>

extern EFI_BOOT_SERVICES         *gBS;
extern EFI_RUNTIME_SERVICES      *gRT;
extern EFI_HANDLE                gImageHandle;

EFI_ACPI_DESCRIPTION_HEADER mAcpiTemplate = {
  EFI_ACPI_5_0_VTIO_TABLE_SIGNATURE,
  0,//sizeof (EFI_VTIO_ACPI_TABLE) - will be updated dynamically
  EFI_VTIO_ACPI_TABLE_REVISION,
  //
  // Compiler initializes the remaining bytes to 0
  // These fields should be filled in in production
  //
  };

EFI_SECURE_CONTROLLER SecureController[NUMBER_OF_SECURE_CONTROLLERS-1] = {
  {
    //
    // Secure Controller 1 Struct - CIO2 controller
    //
    0x01,     // Type
    0x00,     // Flags
    sizeof (EFI_SECURE_CONTROLLER),  // Length - To be updated before publishing ACPI table
    0x0000,   // PCI Segment Number
    0x0000,   // Start Bus Number
    0x0010,   // PCI Path Offset
    0x0002,   // PCI Path Length
    0x0012,   // Capability Structure Offset
    sizeof (CAP_STRUCT),  // Capability Structure Length
    0x0314,   // PCI Path
    {0x0100,  // Capability Structure Version
    0x0000,   // Controller capability - TGL HW does not have support for BDF, MSI separation and HW crypto capability
    0xFF,     // Alternate Function Number
    0x00,     // Reserved
    0x0000,   // Reserved 1
    0x0002,   // Number of sensors
    0x0002,   // Sensor Entry Size
    //
    // CIO2 controller Sensor Info
    //
    {
      {0x0001},  // Sensor Info - User facing RGB Camera
      {0x0089},  // Sensor Info - User facing IR Camera
    }}
  },

  {
    //
    // Secure Controller 2 Struct - ISP controller
    //
    0x01,     // Type
    0x00,     // Flags
    sizeof (EFI_SECURE_CONTROLLER),  // Length - To be updated before publishing ACPI table
    0x0000,   // PCI Segment Number
    0x0000,   // Start Bus Number
    0x0010,   // PCI Path Offset
    0x0002,   // PCI Path Length
    0x0012,   // Capability Structure Offset
    sizeof (CAP_STRUCT),  // Capability Structure Length
    0x0005,   // PCI Path
    {0x0100,  // Capability Structure Version
    0x0000,   // Controller capability - TGL HW does not have support for BDF, MSI separation and HW crypto capability
    0xFF,     // Alternate Function Number
    0x00,     // Reserved
    0x0000,   // Reserved 1
    0x0002,   // Number of sensors
    0x0002,   // Sensor Entry Size
    //
    // ISP controller Sensor Info
    //
    {
      {0x0001},  // Sensor Info - User facing RGB Camera
      {0x0085},  // Sensor Info - User facing IR Camera
    }}
  },

  {
    //
    // Secure Controller 3 Struct - HECI controller
    //
    0x01,     // Type
    0x00,     // Flags
    sizeof (EFI_SECURE_CONTROLLER) - 4,  // Length - To be updated before publishing ACPI table
    0x0000,   // PCI Segment Number
    0x0000,   // Start Bus Number
    0x0010,   // PCI Path Offset
    0x0002,   // PCI Path Length
    0x0012,   // Capability Structure Offset
    sizeof (CAP_STRUCT) - 4,  // Capability Structure Length
    0x0016,   // PCI Path
    {0x0100,  // Capability Structure Version
    0x0000,   // Controller capability - TGL HW does not have support for BDF, MSI separation and HW crypto capability
    0xFF,     // Alternate Function Number
    0x00,     // Reserved
    0x0000,   // Reserved 1
    0x0000,   // Number of sensors
    0x0002,   // Sensor Entry Size
    //
    // HECI controller Sensor Info
    //
    {
      {0x0000},  // Dummy
      {0x0000},  // Dummy
    }}
  },

  {
    //
    // Secure Controller 4 Struct - SPI1 controller
    //
    0x01,     // Type
    0x00,     // Flags
    sizeof (EFI_SECURE_CONTROLLER) - 2,  // Length - To be updated before publishing ACPI table
    0x0000,   // PCI Segment Number
    0x0000,   // Start Bus Number
    0x0010,   // PCI Path Offset
    0x0002,   // PCI Path Length
    0x0012,   // Capability Structure Offset
    sizeof (CAP_STRUCT) - 2,  // Capability Structure Length
    0x021E,   // PCI Path
    {0x0100,  // Capability Structure Version
    0x0000,   // Controller capability - TGL HW does not have support for BDF, MSI separation and HW crypto capability
    0xFF,     // Alternate Function Number
    0x00,     // Reserved
    0x0000,   // Reserved 1
    0x0001,   // Number of sensors
    0x0002,   // Sensor Entry Size
    //
    // SPI1 controller Sensor Info
    //
    {
      {0x0001},  // Sensor
      {0x0000},  // Dummy
    }}
  },

  {
    //
    // Secure Controller 5 Struct - SPI2 controller
    //
    0x01,     // Type
    0x00,     // Flags
    sizeof (EFI_SECURE_CONTROLLER) - 2,  // Length - To be updated before publishing ACPI table
    0x0000,   // PCI Segment Number
    0x0000,   // Start Bus Number
    0x0010,   // PCI Path Offset
    0x0002,   // PCI Path Length
    0x0012,   // Capability Structure Offset
    sizeof (CAP_STRUCT) - 2,  // Capability Structure Length
    0x031E,   // PCI Path
    {0x0100,  // Capability Structure Version
    0x0000,   // Controller capability - TGL HW does not have support for BDF, MSI separation and HW crypto capability
    0xFF,     // Alternate Function Number
    0x00,     // Reserved
    0x0000,   // Reserved 1
    0x0001,   // Number of sensors
    0x0002,   // Sensor Entry Size
    //
    // SPI2 controller Sensor Info
    //
    {
      {0x0001},  // Sensor Info
      {0x0000},  // Dummy
    }}
  }
};

EFI_XHCI_SECURE_CONTROLLER XHCISecureController = {
  //
  // Secure Controller 6 Struct - XHCI controller
  //
  0x01,    // Type
  0x00,    // Flags
  0x007D,  // Length - This includes the length of Descriptor. To be updated before publishing ACPI table
  0x0000,  // PCI Segment Number
  0x0000,  // Start Bus Number
  0x0010,  // PCI Path Offset
  0x0002,  // PCI Path Length
  0x0012,  // Capability Structure Offset
  0x006B,  // Capability Structure Length. To be updated before publishing ACPI table
  0x0014,  // PCI Path
};

EFI_XHCI_VENDOR_DEVICE_DESC XHCIVendorDescriptor = {
  //
  // XHCI Vendor Device Descriptor Struct
  //
  0x80,    // Type
  0x000A,  // Length - To be updated before publishing ACPI table
  0x0000,  // Controller Capability
  0x40,    // Alternate function number
  0x0000,  // Reserved1
  0x0000,  // Reserved2
};

EFI_XHCI_SECURE_DEVICE_DESC RGBDescriptor = {
  //
  // XHCI Secure Device Descriptor Struct - RGB
  //
  0x00,     // Type
  0x0051,   // Length
  0x02,     // Revision
  0x00,     // Attributes
  0x00,     // Root port Number
  {0x0000,  // Vendor ID
  0x0000,   // Device ID
  0x0000,   // Revision
  0x00},    // Interface Number
  {0x0E,    // Class code
  0x01,     // Sub Class
  0x01,     // Protocol
  0x0034,   // ACPI Path string offset
  0x001D,   // ACPI Path string name
  {0x0,     // Firmware Hash [63:0]
  0x0,      // Firmware Hash [127:64]
  0x0,      // Firmware Hash [191:128]
  0x0},     // Firmware Hash [255:192]
  "\\_SB.PC00.XHCI.RHUB.HS00.CRGB"}  // ACPI Path name
};

EFI_XHCI_SECURE_DEVICE_DESC IRDescriptor = {
  //
  // XHCI Secure Device Descriptor Struct - IR
  //
  0x00,     // Type
  0x0050,   // Length
  0x02,     // Revision
  0x00,     // Attributes
  0x01,     // Root port Number
  {0x0000,  // Vendor ID
  0x0000,   // Device ID
  0x0000,   // Revision
  0x00},    // Interface Number
  {0x0E,    // Class code
  0x01,     // Sub Class
  0x01,     // Protocol
  0x0034,   // ACPI Path string offset
  0x001C,   // ACPI Path string name
  {0x0,     // Firmware Hash [63:0]
  0x0,      // Firmware Hash [127:64]
  0x0,      // Firmware Hash [191:128]
  0x0},     // Firmware Hash [255:192]
  "\\_SB.PC00.XHCI.RHUB.HS01.CIR"}   // ACPI Path name
};

EFI_SDEV_USB_DEVICE_STRUCT USBCameraRGB = {
  //
  // USB Device Struct for RGB Camera
  //
  0x00,    // Type
  0x00,    // Flags
  0x0029,  // Length - To be updated before publishing ACPI table
  0x000C,  // Device Identifier Offset
  0x001D,  // Device Identifier Length
  0x000C,  // Vendor Specific Information Offset
  0x0000,  // Vendor Specific Information Length
  "\\_SB.PC00.XHCI.RHUB.HS00.CRGB",  // Device Identifier
};

EFI_SDEV_USB_DEVICE_STRUCT USBCameraIR = {
  //
  // USB Device Struct for IR Camera
  //
  0x00,    // Type
  0x00,    // Flags
  0x0028,  // Length - To be updated before publishing ACPI table
  0x000C,  // Device Identifier Offset
  0x001C,  // Device Identifier Length
  0x000C,  // Vendor Specific Information Offset
  0x0000,  // Vendor Specific Information Length
  "\\_SB.PC00.XHCI.RHUB.HS01.CIR",  // Device Identifier
};

/**
  Update Secure Controller

  @param[in] SecureControllerIndex - Index of Secure Controller
  @param[in] NumberOfSensors       - Number of sensors for Secure Controller
  @param[in] Flags                 - Flags of Secure Controller
  @param[in] SensorEntry1          - Sensor information for first sensor
  @param[in] SensorEntry2          - Sensor information for second sensor
**/
VOID
UpdateSecureController (
  IN UINT16 SecureControllerIndex,
  IN UINT16 NumberOfSensors,
  IN UINT8  Flags,
  IN UINT16 SensorEntry1,
  IN UINT16 SensorEntry2
  )
{
  UINT16                         SensorEntryLengthUpdate;

  SensorEntryLengthUpdate      = 0;

  SecureController[SecureControllerIndex].CapabilityStruct.NumberofSensors = NumberOfSensors;
  SensorEntryLengthUpdate = (SecureController[SecureControllerIndex].CapabilityStruct.SensorEntrySize *
    (MAXIMUM_SENSOR_ENTRIES - SecureController[SecureControllerIndex].CapabilityStruct.NumberofSensors));
  SecureController[SecureControllerIndex].Length = sizeof (EFI_SECURE_CONTROLLER) - SensorEntryLengthUpdate;
  SecureController[SecureControllerIndex].CapabilityStructLength  = sizeof (CAP_STRUCT) - SensorEntryLengthUpdate;
  SecureController[SecureControllerIndex].Flags = Flags;
  SecureController[SecureControllerIndex].CapabilityStruct.SensorArray[0].SensorInfo = SensorEntry1;
  SecureController[SecureControllerIndex].CapabilityStruct.SensorArray[1].SensorInfo = SensorEntry2;

  DEBUG ((DEBUG_INFO, "Update Secure Controller %x\n", SecureControllerIndex));
  DEBUG ((DEBUG_INFO, "  Number of Sensors        = %x\n", SecureController[SecureControllerIndex].CapabilityStruct.NumberofSensors));
  DEBUG ((DEBUG_INFO, "  Flags                    = %x\n", SecureController[SecureControllerIndex].Flags));
  DEBUG ((DEBUG_INFO, "  Sensor Info              = %x, %x\n", SecureController[SecureControllerIndex].CapabilityStruct.SensorArray[0].SensorInfo,
                                                               SecureController[SecureControllerIndex].CapabilityStruct.SensorArray[1].SensorInfo));
  DEBUG ((DEBUG_INFO, "  Length                   = %x\n", SecureController[SecureControllerIndex].Length));
  DEBUG ((DEBUG_INFO, "  CapabilityStructLength   = %x\n", SecureController[SecureControllerIndex].CapabilityStructLength));

  return;
}

/**
  Update xHCI Secure Controller

  @param[in] DeviceIndex           - Index of xHCI Secure Controller device
  @param[in] Flags                 - Flags of xHCI Secure Controller device
  @param[in] NumberOfDevices       - Number of xHCI Secure Controller devices
  @param[in] DeviceAttributes      - Attributes of xHCI Secure Controller device
  @param[in] RootPortNumber        - Root Port Number of xHCI Secure Controller device
  @param[in] VendorId              - Vendor ID of xHCI Secure Controller device
  @param[in] ProductId             - Product ID of xHCI Secure Controller device
  @param[in] Revision              - Revision of xHCI Secure Controller device
  @param[in] InterfaceNumber       - Interface Number of xHCI Secure Controller device
  @param[in] Class                 - Class of xHCI Secure Controller device
  @param[in] SubClass              - Subclass of xHCI Secure Controller device
  @param[in] Protocol              - Protocol of xHCI Secure Controller device
  @param[in] AcpiPathStringOffset  - ACPI Path String Offset of xHCI Secure Controller device
  @param[in] AcpiPathStringLength  - ACPI Path String Length of xHCI Secure Controller device
  @param[in] FirmwareHashDevice1   - Firmware Hash of xHCI Secure Controller device
  @param[in] FirmwareHashDevice2   - Firmware Hash of xHCI Secure Controller device
  @param[in] AcpiPathNameDevice1   - ACPI Path Name of xHCI Secure Controller device
  @param[in] AcpiPathNameDevice2   - ACPI Path Name of xHCI Secure Controller device
**/
VOID
UpdateXHCISecureController (
  IN UINT16  DeviceIndex,
  IN UINT8   NumberOfDevices,
  IN UINT8   Flags,
  IN UINT8   DeviceAttributes,
  IN UINT8   RootPortNumber,
  IN UINT16  VendorId,
  IN UINT16  ProductId,
  IN UINT16  Revision,
  IN UINT8   InterfaceNumber,
  IN UINT8   Class,
  IN UINT8   SubClass,
  IN UINT8   Protocol,
  IN UINT16  AcpiPathStringOffset,
  IN UINT16  AcpiPathStringLength,
  IN UINT64  FirmwareHashDevice1[],
  IN UINT64  FirmwareHashDevice2[],
  IN UINT16  AcpiPathNameDevice1[],
  IN UINT16  AcpiPathNameDevice2[]
  )
{
  UINT8                        Index;
  UINT8                        PathNameTemp[MAXIMUM_PATH_NAME_SIZE];
  UINT16                       DescriptorLengthTemp;
  EFI_XHCI_SECURE_DEVICE_DESC  *TempXhciDevice;
  EFI_SDEV_USB_DEVICE_STRUCT   *TempUsbDevice;

  Index                = 0;
  DescriptorLengthTemp = 0;
  ZeroMem (PathNameTemp, sizeof (PathNameTemp)/sizeof (UINT8));
  TempXhciDevice       = NULL;
  TempUsbDevice        = NULL;

  ///
  /// Select xHCI Secure Device
  ///
  if (DeviceIndex == 0) {
    TempXhciDevice = &RGBDescriptor;
    TempUsbDevice  = &USBCameraRGB;
  } else if (DeviceIndex == 1) {
    TempXhciDevice = &IRDescriptor;
    TempUsbDevice  = &USBCameraIR;
  } else {
    DEBUG ((DEBUG_ERROR, "Invalid xHCI Secure Device - %x\n", DeviceIndex));
    return;
  }

  ///
  /// Update Flag field for Secure Device Struture
  ///
  TempUsbDevice->Flags                  = Flags;

  DEBUG ((DEBUG_INFO, "Update xHCI Secure Controller %x\n", DeviceIndex));
  if (DeviceIndex < NumberOfDevices) {
    DescriptorLengthTemp                              = TempXhciDevice->Length;
    TempXhciDevice->Length                            = (TempXhciDevice->Length - TempXhciDevice->USBCidStruct.AcpiPathStringLength + AcpiPathStringLength);
    TempXhciDevice->Attributes                        = DeviceAttributes;
    TempXhciDevice->RootPortNumber                    = RootPortNumber;
    TempXhciDevice->USBHidStruct.VendorID             = VendorId;
    TempXhciDevice->USBHidStruct.DeviceID             = ProductId;
    TempXhciDevice->USBHidStruct.Revision             = Revision;
    TempXhciDevice->USBHidStruct.InterfaceNumber      = InterfaceNumber;
    TempXhciDevice->USBCidStruct.Class                = Class;
    TempXhciDevice->USBCidStruct.SubClass             = SubClass;
    TempXhciDevice->USBCidStruct.Protocol             = Protocol;
    TempXhciDevice->USBCidStruct.AcpiPathStringOffset = AcpiPathStringOffset;
    TempXhciDevice->USBCidStruct.AcpiPathStringLength = AcpiPathStringLength;
    if (DeviceIndex == 0) {
      TempXhciDevice->USBCidStruct.FirmwareHash[0]    = FirmwareHashDevice1[0];
      TempXhciDevice->USBCidStruct.FirmwareHash[1]    = FirmwareHashDevice1[1];
      TempXhciDevice->USBCidStruct.FirmwareHash[2]    = FirmwareHashDevice1[2];
      TempXhciDevice->USBCidStruct.FirmwareHash[3]    = FirmwareHashDevice1[3];
    } else if (DeviceIndex == 1) {
      TempXhciDevice->USBCidStruct.FirmwareHash[0]    = FirmwareHashDevice2[0];
      TempXhciDevice->USBCidStruct.FirmwareHash[1]    = FirmwareHashDevice2[1];
      TempXhciDevice->USBCidStruct.FirmwareHash[2]    = FirmwareHashDevice2[2];
      TempXhciDevice->USBCidStruct.FirmwareHash[3]    = FirmwareHashDevice2[3];
    }

    ///
    /// Update USB CID Structure if ACPI Path Name has been modified
    ///
    if ((DeviceIndex == 0 && AcpiPathNameDevice1[0] != 0x0) || (DeviceIndex == 1 && AcpiPathNameDevice2[0] != 0x0)) {
      DEBUG ((DEBUG_INFO, "Current AcpiPathName\n"));
      for (Index = 0; Index < MAXIMUM_PATH_NAME_SIZE; Index++) {
        DEBUG ((DEBUG_INFO, "0x%02x ", TempXhciDevice->USBCidStruct.AcpiPathName[Index]));
      }
      DEBUG ((DEBUG_INFO, "\n"));

      ///
      /// Zero out current ACPI Path Name
      ///
      ZeroMem (TempXhciDevice->USBCidStruct.AcpiPathName, sizeof (TempXhciDevice->USBCidStruct.AcpiPathName)/sizeof (UINT8));

      ///
      /// Copy new ACPI Path Name to a temporary variable
      ///
      for (Index = 0; Index < AcpiPathStringLength; Index++) {
        if (DeviceIndex == 0) {
          PathNameTemp[Index] = (UINT8) AcpiPathNameDevice1[Index];
        } else if (DeviceIndex == 1) {
          PathNameTemp[Index] = (UINT8) AcpiPathNameDevice2[Index];
        }
      }

      ///
      /// Verify ACPI Path Name Length is correct
      /// Length is determined by the index of the NULL terminator
      ///
      Index = 0;
      while (PathNameTemp[Index] != 0x0) {
        Index++;
      }

      ///
      /// Update Descriptor Length and AcpiPathStringLength if needed
      ///
      if (AcpiPathStringLength != (Index + 1)) {
        DEBUG ((DEBUG_INFO, "Index %x contains NULL terminator\n", Index));
        DEBUG ((DEBUG_WARN, "AcpiPathStringLength is incorrect. Should be set to : %x \n", Index + 1));
        AcpiPathStringLength = Index + 1;

        TempXhciDevice->Length = (DescriptorLengthTemp - TempXhciDevice->USBCidStruct.AcpiPathStringLength + AcpiPathStringLength);
        DEBUG ((DEBUG_INFO, "Descriptor Length Updated: %x\n", TempXhciDevice->Length));
        TempXhciDevice->USBCidStruct.AcpiPathStringLength = AcpiPathStringLength;
        DEBUG ((DEBUG_INFO, "AcpiPathStringLength Updated: %x\n", TempXhciDevice->USBCidStruct.AcpiPathStringLength));
      }

      ///
      /// Update ACPI Path Name with new value
      ///
      CopyMem (TempXhciDevice->USBCidStruct.AcpiPathName, PathNameTemp, sizeof (PathNameTemp)/sizeof (UINT8));
      DEBUG ((DEBUG_INFO, "Updated AcpiPathName\n"));
      for (Index = 0; Index < MAXIMUM_PATH_NAME_SIZE; Index++) {
        DEBUG ((DEBUG_INFO, "0x%02x ", TempXhciDevice->USBCidStruct.AcpiPathName[Index]));
      }
      DEBUG ((DEBUG_INFO, "\n"));

      ///
      /// Update the corresponding ACPI Controller Description
      ///
      TempUsbDevice->Length                 = TempUsbDevice->Length - TempUsbDevice->DeviceIdentifierLength + TempXhciDevice->USBCidStruct.AcpiPathStringLength;
      TempUsbDevice->DeviceIdentifierLength = TempXhciDevice->USBCidStruct.AcpiPathStringLength;
      ZeroMem (TempUsbDevice->AcpiPathName, sizeof (TempUsbDevice->AcpiPathName)/sizeof (UINT8));
      CopyMem (TempUsbDevice->AcpiPathName, TempXhciDevice->USBCidStruct.AcpiPathName, sizeof (TempXhciDevice->USBCidStruct.AcpiPathName)/sizeof (UINT8));
    }

    DEBUG ((DEBUG_INFO, "  Flags                                 = %x\n", TempUsbDevice->Flags));
    DEBUG ((DEBUG_INFO, "  Length                                = %x\n", TempXhciDevice->Length));
    DEBUG ((DEBUG_INFO, "  Attributes                            = %x\n", TempXhciDevice->Attributes));
    DEBUG ((DEBUG_INFO, "  RootPortNumber                        = %x\n", TempXhciDevice->RootPortNumber));
    DEBUG ((DEBUG_INFO, "  USB Hardware ID - VendorID            = %x\n", TempXhciDevice->USBHidStruct.VendorID));
    DEBUG ((DEBUG_INFO, "  USB Hardware ID - Device ID           = %x\n", TempXhciDevice->USBHidStruct.DeviceID));
    DEBUG ((DEBUG_INFO, "  USB Hardware ID - Revision            = %x\n", TempXhciDevice->USBHidStruct.Revision));
    DEBUG ((DEBUG_INFO, "  USB Hardware ID - InterfaceNumber     = %x\n", TempXhciDevice->USBHidStruct.InterfaceNumber));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - Class                 = %x\n", TempXhciDevice->USBCidStruct.Class));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - SubClass              = %x\n", TempXhciDevice->USBCidStruct.SubClass));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - Protocol              = %x\n", TempXhciDevice->USBCidStruct.Protocol));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - AcpiPathStringOffset  = %x\n", TempXhciDevice->USBCidStruct.AcpiPathStringOffset));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - FW Hash [255:192]     = %016llx\n", TempXhciDevice->USBCidStruct.FirmwareHash[3]));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - FW Hash [191:128]     = %016llx\n", TempXhciDevice->USBCidStruct.FirmwareHash[2]));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - FW Hash [127:64]      = %016llx\n", TempXhciDevice->USBCidStruct.FirmwareHash[1]));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - FW Hash [63:0]        = %016llx\n", TempXhciDevice->USBCidStruct.FirmwareHash[0]));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - AcpiPathStringLength  = %x\n", TempXhciDevice->USBCidStruct.AcpiPathStringLength));
    DEBUG ((DEBUG_INFO, "  USB Compat ID - AcpiPathName (Hex)    = "));

    for (Index = 0; Index < TempXhciDevice->USBCidStruct.AcpiPathStringLength; Index++) {
      DEBUG ((DEBUG_INFO, "0x%02x ", TempXhciDevice->USBCidStruct.AcpiPathName[Index]));
    }
    DEBUG ((DEBUG_INFO, "\n"));

    DEBUG ((DEBUG_INFO, "  USB Compat ID - AcpiPathName (String) = "));
    for (Index = 0; Index < TempXhciDevice->USBCidStruct.AcpiPathStringLength; Index++) {
      DEBUG ((DEBUG_INFO, "%c", TempXhciDevice->USBCidStruct.AcpiPathName[Index]));
    }
    DEBUG ((DEBUG_INFO, "\n"));
  } else {
    TempXhciDevice->Length = 0;
    DEBUG ((DEBUG_INFO, "  Length                               = %x\n", TempXhciDevice->Length));
    TempUsbDevice->Length = 0;
  }

  return;
}

/**
  Main entry for this driver.

  @param ImageHandle     Image handle this driver.
  @param SystemTable     Pointer to SystemTable.

  @retval EFI_SUCESS     This function always complete successfully.
**/
EFI_STATUS
EFIAPI
VtioDxeEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                     Status;
  SETUP_DATA                     SetupData;
  SA_SETUP                       SaSetup;
  UINTN                          VariableSize;
  BOOLEAN                        EnableControllerEntry[NUMBER_OF_SECURE_CONTROLLERS];
  UINT16                         ControllerNumber;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTable;
  UINTN                          TableKey;
  UINT8                          *VtioTable, *TempVtioTable;
  UINT32                         Length;
  UINT16                         XhciDeviceNumber;

  Status                       = EFI_SUCCESS;
  VariableSize                 = sizeof (SA_SETUP);
  Length                       = 0;

  DEBUG ((DEBUG_INFO, "VtioDxeEntryPoint\n"));

  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  if (SaSetup.EnableVtd == 0) { // Publish SDEV table only if VT-d is enabled in BIOS setup
    DEBUG ((DEBUG_ERROR, "VT-d is disabled in BIOS setup - just return\n"));
    return EFI_SUCCESS;
  }

  VariableSize = sizeof (SETUP_DATA);

  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );

  DEBUG ((DEBUG_INFO, "VTIO GetVariable Status = %r\n", Status));

  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  if (!SetupData.VtioSupport) {
    DEBUG ((DEBUG_ERROR, "VTIO is disabled in BIOS setup - just return\n"));
    return EFI_SUCCESS;
  }

  EnableControllerEntry[SECURE_CONTROLLER_INDEX_CIO2] = (BOOLEAN) SetupData.SdevCio2Entry;
  EnableControllerEntry[SECURE_CONTROLLER_INDEX_ISP]  = (BOOLEAN) SetupData.SdevIspEntry;
  EnableControllerEntry[SECURE_CONTROLLER_INDEX_HECI] = (BOOLEAN) SetupData.SdevHeciEntry;
  EnableControllerEntry[SECURE_CONTROLLER_INDEX_SPI1] = (BOOLEAN) SetupData.SdevSpi1Entry;
  EnableControllerEntry[SECURE_CONTROLLER_INDEX_SPI2] = (BOOLEAN) SetupData.SdevSpi2Entry;
  EnableControllerEntry[SECURE_CONTROLLER_INDEX_HXCI] = (BOOLEAN) SetupData.SdevXhciEntry;

  DEBUG ((DEBUG_INFO, "SetupData.VtioSupport   = %x\n", SetupData.VtioSupport));
  DEBUG ((DEBUG_INFO, "SetupData.SdevCio2Entry = %x\n", SetupData.SdevCio2Entry));
  DEBUG ((DEBUG_INFO, "SetupData.SdevIspEntry  = %x\n", SetupData.SdevIspEntry));
  DEBUG ((DEBUG_INFO, "SetupData.SdevHeciEntry = %x\n", SetupData.SdevHeciEntry));
  DEBUG ((DEBUG_INFO, "SetupData.SdevSpi1Entry = %x\n", SetupData.SdevSpi1Entry));
  DEBUG ((DEBUG_INFO, "SetupData.SdevSpi2Entry = %x\n", SetupData.SdevSpi2Entry));
  DEBUG ((DEBUG_INFO, "SetupData.SdevXhciEntry = %x\n", SetupData.SdevXhciEntry));

  Length = sizeof (EFI_ACPI_DESCRIPTION_HEADER);
  //
  // Exclude XHCI controller since it has a different structure
  //
  for (ControllerNumber = 0; ControllerNumber < NUMBER_OF_SECURE_CONTROLLERS-1; ControllerNumber++) {
    if (EnableControllerEntry[ControllerNumber]) {
      UpdateSecureController (ControllerNumber,
                                SetupData.SdevNumberOfSensors[ControllerNumber],
                                SetupData.SdevFlags[ControllerNumber],
                                SetupData.SdevSensorEntry1[ControllerNumber],
                                SetupData.SdevSensorEntry2[ControllerNumber]
                              );
      Length += SecureController[ControllerNumber].Length;
    }
  }

  //
  // Update xHCI Secure Controllers if enabled in BIOS setup
  //
  if (EnableControllerEntry[(SECURE_CONTROLLER_INDEX_HXCI)]) {
    for (XhciDeviceNumber = 0; XhciDeviceNumber < MAXIMUM_XHCI_DEVICES; XhciDeviceNumber++) {
      UpdateXHCISecureController (
        XhciDeviceNumber,
        SetupData.SdevXhciNumberOfDevices,
        SetupData.SdevXhciFlags,
        SetupData.SdevXhciDeviceAttributes[XhciDeviceNumber],
        SetupData.SdevXhciRootPortNumber[XhciDeviceNumber],
        SetupData.SdevXhciVendorId[XhciDeviceNumber],
        SetupData.SdevXhciProductId[XhciDeviceNumber],
        SetupData.SdevXhciRevision[XhciDeviceNumber],
        SetupData.SdevXhciInterfaceNumber[XhciDeviceNumber],
        SetupData.SdevXhciClass[XhciDeviceNumber],
        SetupData.SdevXhciSubClass[XhciDeviceNumber],
        SetupData.SdevXhciProtocol[XhciDeviceNumber],
        SetupData.SdevXhciAcpiPathStringOffset[XhciDeviceNumber],
        SetupData.SdevXhciAcpiPathStringLength[XhciDeviceNumber],
        SetupData.SdevXhciFirmwareHashDevice1,
        SetupData.SdevXhciFirmwareHashDevice2,
        SetupData.SdevXhciAcpiPathNameDevice1,
        SetupData.SdevXhciAcpiPathNameDevice2
        );

      XHCISecureController.Flags = SetupData.SdevXhciFlags;

      XHCISecureController.Length = (sizeof (XHCISecureController) +
                                      XHCIVendorDescriptor.Length +
                                      RGBDescriptor.Length +
                                      IRDescriptor.Length
                                    );

      XHCISecureController.CapabilityStructLength = (XHCIVendorDescriptor.Length +
                                                      RGBDescriptor.Length +
                                                      IRDescriptor.Length
                                                    );
    }

    //
    // Add the length of all XHCI structures
    //
    Length += (sizeof (EFI_XHCI_SECURE_CONTROLLER) +
                XHCIVendorDescriptor.Length +
                RGBDescriptor.Length +
                IRDescriptor.Length +
                USBCameraRGB.Length +
                USBCameraIR.Length
              );
  }

  VtioTable = AllocatePool (Length);

  if (VtioTable == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  TempVtioTable = VtioTable;

  CopyMem (TempVtioTable, &mAcpiTemplate, sizeof (EFI_ACPI_DESCRIPTION_HEADER));
  TempVtioTable = TempVtioTable + sizeof (EFI_ACPI_DESCRIPTION_HEADER);
  for (ControllerNumber = 0; ControllerNumber < NUMBER_OF_SECURE_CONTROLLERS-1; ControllerNumber++) {
    if (EnableControllerEntry[ControllerNumber]){
      CopyMem (TempVtioTable, &SecureController[ControllerNumber], SecureController[ControllerNumber].Length);
      TempVtioTable = TempVtioTable + SecureController[ControllerNumber].Length;
    }
  }

  //
  // Copy all XHCI structures if it is enabled in BIOS setup
  //
  if (EnableControllerEntry[(SECURE_CONTROLLER_INDEX_HXCI)]) {
    CopyMem (TempVtioTable, &XHCISecureController, sizeof (EFI_XHCI_SECURE_CONTROLLER));
    TempVtioTable = TempVtioTable + sizeof (EFI_XHCI_SECURE_CONTROLLER);

    CopyMem (TempVtioTable, &XHCIVendorDescriptor, XHCIVendorDescriptor.Length);
    TempVtioTable = TempVtioTable + XHCIVendorDescriptor.Length;

    CopyMem (TempVtioTable, &RGBDescriptor, RGBDescriptor.Length);
    TempVtioTable = TempVtioTable + RGBDescriptor.Length;

    CopyMem (TempVtioTable, &IRDescriptor, IRDescriptor.Length);
    TempVtioTable = TempVtioTable + IRDescriptor.Length;

    CopyMem (TempVtioTable, &USBCameraRGB, USBCameraRGB.Length);
    TempVtioTable = TempVtioTable + USBCameraRGB.Length;

    CopyMem (TempVtioTable, &USBCameraIR, USBCameraIR.Length);
    TempVtioTable = TempVtioTable + USBCameraIR.Length;
  }

  ///
  /// Construct ACPI table
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTable);
  ASSERT_EFI_ERROR (Status);

  ((EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(VtioTable))->Length = Length;

  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        VtioTable,
                        ((EFI_ACPI_DESCRIPTION_HEADER *)VtioTable)->Length,
                        &TableKey
                        );
  ASSERT_EFI_ERROR (Status);
  if (VtioTable != NULL) {
    gBS->FreePool (VtioTable);
  }

  return Status;
}

