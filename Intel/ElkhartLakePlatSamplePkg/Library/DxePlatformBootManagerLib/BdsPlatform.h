/** @file
  Header file for BDS Platform specific code

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

#ifndef _BDS_PLATFORM_H
#define _BDS_PLATFORM_H

#include <PiDxe.h>
#include <Protocol/DevicePath.h>
#include <Protocol/SimpleNetwork.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/LoadFile.h>
#include <Protocol/PciIo.h>
#include <Protocol/CpuIo2.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/GenericMemoryTest.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/EsrtManagement.h>

#include <Guid/MemoryTypeInformation.h>
#include <Guid/GlobalVariable.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Guid/FileInfo.h>
#include <BootState.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformBootManagerLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/HiiLib.h>
#include <Library/LogoLib.h>
#include <Library/CapsuleLib.h>
#include <Library/PerformanceLib.h>
#include <Library/EcMiscLib.h>

#include <Register/PchRegsLpc.h>
#include <Register/PchPcieRpRegs.h>
#include <Register/UsbRegs.h>
#include <Register/ScsVer3Regs.h>

#include <IndustryStandard/Pci30.h>
#include <IndustryStandard/PciCodeId.h>

#include <SetupVariable.h>
#include <IccSetupData.h>
#include <PlatformBoardType.h>

///
/// ConnectType
///
#define CONSOLE_OUT 0x00000001
#define STD_ERROR   0x00000002
#define CONSOLE_IN  0x00000004
#define CONSOLE_ALL (CONSOLE_OUT | CONSOLE_IN | STD_ERROR)

extern EFI_GUID                  gUefiShellFileGuid;
extern EFI_GUID                  gSetupEnterGuid;
extern EFI_BOOT_MODE             gBootMode;
extern SA_SETUP                  mSaSetup;
extern SETUP_DATA                mSystemConfiguration;
extern BOOLEAN                   mDecompressFvUefiBoot;
extern EFI_DEVICE_PATH_PROTOCOL  *gPlatformConnectSequence[];

#define gPciRootBridge \
  { \
    { \
      ACPI_DEVICE_PATH, \
      ACPI_DP, \
      { \
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), \
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8) \
      }, \
    }, \
    EISA_PNP_ID (0x0A03), \
    0 \
  }

#define gEndEntire \
  { \
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { END_DEVICE_PATH_LENGTH, 0 } \
  }

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     ConnectType;
} BDS_CONSOLE_CONNECT_ENTRY;

//
// Platform Root Bridge
//
typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_ROOT_BRIDGE_DEVICE_PATH;

//
// Below is the platform console device path
//
typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           IsaBridge;
  ACPI_HID_DEVICE_PATH      Keyboard;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_KEYBOARD_DEVICE_PATH;

typedef struct {
  ACPI_EXTENDED_HID_DEVICE_PATH      I2cController;
  UINT8                              HidStr[8];
  UINT8                              UidStr[1];
  UINT8                              CidStr[8];
} PLATFORM_VIRTUAL_KEYBOARD_I2C_CONTROLLER_DEVICE_PATH;

typedef struct {
  ACPI_EXTENDED_HID_DEVICE_PATH      I2cDevice;
  UINT8                              HidStr[13];
  UINT8                              UidStr[1];
  UINT8                              CidStr[13];
} PLATFORM_VIRTUAL_KEYBOARD_I2C_DEVICE_DEVICE_PATH;

typedef struct {
  PLATFORM_VIRTUAL_KEYBOARD_I2C_CONTROLLER_DEVICE_PATH      I2cController;
  PLATFORM_VIRTUAL_KEYBOARD_I2C_DEVICE_DEVICE_PATH          I2cDevice;
  EFI_DEVICE_PATH_PROTOCOL                                  End;
} PLATFORM_VIRTUAL_KEYBOARD_I2C_DEVICE_PATH;

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           IsaBridge;
  ACPI_HID_DEVICE_PATH      IsaSerial;
  UART_DEVICE_PATH          Uart;
  VENDOR_DEVICE_PATH        TerminalType;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_ISA_SERIAL_DEVICE_PATH;

typedef struct {
  VENDOR_DEVICE_PATH        Guid;
  UART_DEVICE_PATH          Uart;
  VENDOR_DEVICE_PATH        TerminalType;
  EFI_DEVICE_PATH_PROTOCOL  End;
} SERIAL_DEVICE_PATH;

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           PciDevice;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH;

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           PciDevice;
  USB_DEVICE_PATH           UsbDevice;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_ONBOARD_USB_DEVICE_PATH;

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           Pci0Device;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_PEG_ROOT_CONTROLLER_DEVICE_PATH;

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           PciBridge;
  PCI_DEVICE_PATH           PciDevice;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_PCI_CONTROLLER_DEVICE_PATH;

//
// Below is the boot option device path
//
typedef struct {
  BBS_BBS_DEVICE_PATH       LegacyHD;
  EFI_DEVICE_PATH_PROTOCOL  End;
} LEGACY_HD_DEVICE_PATH;

#define CLASS_HID           3
#define SUBCLASS_BOOT       1
#define PROTOCOL_KEYBOARD   1

typedef struct {
  USB_CLASS_DEVICE_PATH           UsbClass;
  EFI_DEVICE_PATH_PROTOCOL        End;
} USB_CLASS_FORMAT_DEVICE_PATH;

extern BDS_CONSOLE_CONNECT_ENTRY                 gPlatformConsole[];
extern PLATFORM_ISA_SERIAL_DEVICE_PATH           gSerialDevicePath;
extern SERIAL_DEVICE_PATH                        gPchSerialDevicePath;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformIGDDevice;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformOnboardXhciDevice;
extern PLATFORM_ONBOARD_USB_DEVICE_PATH          gUsbBluetoothHostController;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformPchPcieRootController;
extern PLATFORM_PEG_ROOT_CONTROLLER_DEVICE_PATH  gPlatformPegRootController;
extern PLATFORM_KEYBOARD_DEVICE_PATH             gKeyboardDevicePath;
extern USB_CLASS_FORMAT_DEVICE_PATH              gUsbClassKeyboardDevicePath;
extern USB_CLASS_FORMAT_DEVICE_PATH              gUsbClassMassStorageDevice;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformOnboardVmdDevice;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformOnboardUfs0Device;
extern PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH   gPlatformOnboardUfs1Device;

//
// Platform BDS Functions
//
typedef
VOID
(*PROCESS_VARIABLE) (
  VOID  **Variable,
  UINTN *VariableSize
  );

/**
  Generic function to update the console variable.
  Please refer to FastBootSupport.c for how to use it.

  @param VariableName    - The name of the variable to be updated
  @param AgentGuid       - The Agent GUID
  @param ProcessVariable - The function pointer to update the variable
                           NULL means to restore to the original value
**/
VOID
UpdateEfiGlobalVariable (
  CHAR16           *VariableName,
  EFI_GUID         *AgentGuid,
  PROCESS_VARIABLE ProcessVariable
  );

/**
  Perform the memory test base on the memory test intensive level,
  and update the memory resource.

  @param  Level         The memory test intensive level.

  @retval EFI_STATUS    Success test all the system memory and update
                        the memory resource

**/
EFI_STATUS
MemoryTest (
  IN EXTENDMEM_COVERAGE_LEVEL Level
  );

VOID
ConnectSequence (
  IN EFI_BOOT_MODE                      BootMode
  );

/**
  This function locks platform flash that is not allowed to be updated during normal boot path.
  The flash layout is platform specific.

**/
VOID
LockNonUpdatableFlash (
  VOID
  );

INTN
EFIAPI
CompareBootOption (
  CONST VOID  *Left,
  CONST VOID  *Right
  );

/**
  Print the boot prompt.
**/
VOID
PrintBootPrompt (
  VOID
  );

VOID
RegisterStaticHotkey (
  VOID
  );

VOID
RegisterDynamicHotkey (
  VOID
  );

VOID
RegisterDefaultBootOption (
  VOID
  );

VOID
BootUi (
  VOID
  );

VOID
PlatformBootManagerAttemptUsbBoot (
  VOID
  );

BOOLEAN
IsShellInBootList (
  VOID
  );
#endif
