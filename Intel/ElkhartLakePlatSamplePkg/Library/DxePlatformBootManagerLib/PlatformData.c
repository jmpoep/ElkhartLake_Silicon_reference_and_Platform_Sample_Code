/** @file
  Defined the platform specific device path which will be used by
  platform Bbd to perform the platform policy connect.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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

#include "BdsPlatform.h"
#include <Register/VmdRegs.h>
#include <PchPcieRpInfo.h>

//
// Predefined platform root bridge
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ROOT_BRIDGE_DEVICE_PATH  gPlatformRootBridge0 = {
  gPciRootBridge,
  gEndEntire
};


//
// Platform specific keyboard device path
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_KEYBOARD_DEVICE_PATH     gKeyboardDevicePath = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_LPC,
    PCI_DEVICE_NUMBER_PCH_LPC
  },
  {
    {
      ACPI_DEVICE_PATH,
      ACPI_DP,
      {
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8)
      }
    },
    EISA_PNP_ID(0x0303),
    0
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_VIRTUAL_KEYBOARD_I2C_DEVICE_PATH gVirtualKeyboardDevicePath = {
  {
    {
      {
        ACPI_DEVICE_PATH,
        ACPI_EXTENDED_DP,
        { 33, 0 }
      },
      0,  // HID
      2,  // UID
      0   // CID
    },
    {'I', 'N', 'T', '3', '3', 'C', '3', 0},
    {0},
    {'I', 'N', 'T', '3', '3', 'C', '3', 0}
  },
  {
    {
      {
        ACPI_DEVICE_PATH,
        ACPI_EXTENDED_DP,
        { 43, 0 }
      },
      0,  // HID
      1,  // UID
      0   // CID
    },
    {'I', '2', 'C', '0', '1',  '\\', 'T', 'P', 'A', 'N', 'E', 'L', 0},
    {0},
    {'I', '2', 'C', '0', '1',  '\\', 'T', 'P', 'A', 'N', 'E', 'L', 0}
  },
  gEndEntire
};

//
// Platform specific serial device path
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ISA_SERIAL_DEVICE_PATH   gSerialDevicePath = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_LPC,
    PCI_DEVICE_NUMBER_PCH_LPC
  },
  {
    {
      ACPI_DEVICE_PATH,
      ACPI_DP,
      {
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)),
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8)
      }
    },
    EISA_PNP_ID(0x0501),
    0
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_UART_DP,
      {
        (UINT8) (sizeof (UART_DEVICE_PATH)),
        (UINT8) ((sizeof (UART_DEVICE_PATH)) >> 8)
      }
    },
    0,
    FixedPcdGet32 (PcdSerialBaudRate),
    8,
    1,
    1
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    DEVICE_PATH_MESSAGING_PC_ANSI
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED USB_CLASS_FORMAT_DEVICE_PATH gUsbClassBtKeyboardDevicePath = {
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_USB_CLASS_DP,
      {
        (UINT8) (sizeof (USB_CLASS_DEVICE_PATH)),
        (UINT8) ((sizeof (USB_CLASS_DEVICE_PATH)) >> 8)
      }
    },
    0xffff,  // VendorId
    0xffff,  // ProductId
    0xE0,    // DeviceClass    - Wireless Controller Class
    0x1,     // DeviceSubClass - RF Controller
    0x1      // DeviceProtocol - Bluetooth Primary Controller
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_DEVICE_PATH gPchSerialDevicePath = {
  {
    { HARDWARE_DEVICE_PATH, HW_VENDOR_DP, { sizeof (VENDOR_DEVICE_PATH), 0} },
	{0xF9CD1703, 0x8108, 0x45CD, {0x93, 0x84, 0x5B, 0x24, 0x7B, 0x8C, 0xAF, 0xF5}}  // Use the driver's GUID
  },
  {
    { MESSAGING_DEVICE_PATH, MSG_UART_DP, { sizeof (UART_DEVICE_PATH), 0} },
    0,                                                  // Reserved
    FixedPcdGet32 (PcdSerialBaudRate),                  // BaudRate
    8,                                                  // DataBits
    1,                                                  // Parity
    1                                                   // StopBits
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    DEVICE_PATH_MESSAGING_PC_ANSI
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { sizeof (EFI_DEVICE_PATH_PROTOCOL), 0 } }
};

GLOBAL_REMOVE_IF_UNREFERENCED USB_CLASS_FORMAT_DEVICE_PATH gUsbClassKeyboardDevicePath = {
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_USB_CLASS_DP,
      {
        (UINT8) (sizeof (USB_CLASS_DEVICE_PATH)),
        (UINT8) ((sizeof (USB_CLASS_DEVICE_PATH)) >> 8)
      }
    },
    0xffff,           // VendorId
    0xffff,           // ProductId
    CLASS_HID,        // DeviceClass
    SUBCLASS_BOOT,    // DeviceSubClass
    PROTOCOL_KEYBOARD // DeviceProtocol
  },
  gEndEntire
};

//
// Onboard VGA controller device path
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH         gPlatformIGDDevice = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    0x0,
    0x2
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_PEG_ROOT_CONTROLLER_DEVICE_PATH        gPlatformPegRootController = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    0x0,
    0x1
  },
  gEndEntire
};

//
// Template, the dev/func would updated runtime.
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH         gPlatformPchPcieRootController = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    0x0,
    PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS
  },
  gEndEntire
};

//
// Predefined platform default console device path
//
GLOBAL_REMOVE_IF_UNREFERENCED BDS_CONSOLE_CONNECT_ENTRY         gPlatformConsole[] = {
  //
  // Match PCCG current bios, remove console from ConIn&ConOut
  //
  // {
  //   (EFI_DEVICE_PATH_PROTOCOL *) &gSerialDevicePath,
  //   (CONSOLE_OUT | CONSOLE_IN)
  // },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &gKeyboardDevicePath,
    CONSOLE_IN
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &gUsbClassKeyboardDevicePath,
    CONSOLE_IN
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &gUsbClassBtKeyboardDevicePath,
    CONSOLE_IN
  },
  {
    NULL,
    0
  }
};

//
// XHCI Controller Device Path (0x14, 0x00)
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH  gPlatformOnboardXhciDevice = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_XHCI,
    PCI_DEVICE_NUMBER_PCH_XHCI
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_USB_DEVICE_PATH gUsbBluetoothHostController = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_XHCI,
    PCI_DEVICE_NUMBER_PCH_XHCI
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_USB_DP,
      {
        (UINT8) (sizeof (USB_DEVICE_PATH)),
        (UINT8) ((sizeof (USB_DEVICE_PATH)) >> 8)
      }
    },
    0,
    0
  },
  gEndEntire
};

//
// UFS0 Controller Device Path
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH  gPlatformOnboardUfs0Device = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS0,
    PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS0
  },
  gEndEntire
};

//
// UFS1 Controller Device Path
//
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH  gPlatformOnboardUfs1Device = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS1,
    PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS1
  },
  gEndEntire
};

GLOBAL_REMOVE_IF_UNREFERENCED USB_CLASS_FORMAT_DEVICE_PATH gUsbClassMassStorageDevice = {
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_USB_CLASS_DP,
      {
        (UINT8) (sizeof (USB_CLASS_DEVICE_PATH)),
        (UINT8) ((sizeof (USB_CLASS_DEVICE_PATH)) >> 8)
      }
    },
    0xffff,  // VendorId
    0xffff,  // ProductId
    0x08,    // DeviceClass    - USB Mass Storage Class
    0x06,    // DeviceSubClass - SCSI Transparent Command Set
    0xff     // DeviceProtocol - Match any Device Protocol
  },
  gEndEntire
};
//
// Predefined platform connect sequence
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DEVICE_PATH_PROTOCOL          *gPlatformConnectSequence[] = {
  //
  // Add USB BT host controller so that BT devices can work
  //
  (EFI_DEVICE_PATH_PROTOCOL *) &gUsbBluetoothHostController,
  //
  // Add USB so that USB devices can work
  //
  (EFI_DEVICE_PATH_PROTOCOL *) &gPlatformOnboardXhciDevice,

  NULL
};
