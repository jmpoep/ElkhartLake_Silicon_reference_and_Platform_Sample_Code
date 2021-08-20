/** @file
  Mmio device driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <IndustryStandard/Pci22.h>
#include <Protocol/DevicePath.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include <Library/SerialIoAccessLib.h>
#include <SetupVariable.h>
#include <Protocol/I2cEnumerate.h>
#include <Protocol/I2cBusConfigurationManagement.h>
#include <Protocol/PciIo.h>
#include <Protocol/I2cMaster.h>


#define I2C_SLAVE_ADDRESS_SENSOR_HUB_1             0x40
#define I2C_SLAVE_ADDRESS_SENSOR_HUB_2             0x41
#define I2C_SLAVE_ADDRESS_AUDIO_CODEC_1            0x1C   // Realtek ALC298

#define I2C_SLAVE_ADDRESS_ATMEL_3432_TOUCHPANEL    0x4C
#define I2C_SLAVE_ADDRESS_ATMEL_2952_TOUCHPANEL    0x4A
#define I2C_SLAVE_ADDRESS_ELAN_2097_TOUCHPANEL     0x10
#define I2C_SLAVE_ADDRESS_NTRIG_SAMSUNG_TOUCHPANEL 0x07
#define I2C_SLAVE_ADDRESS_NTRIG_SHARP_TOUCHPANEL   0x64
#define I2C_SLAVE_ADDRESS_EETI_TOUCHPANEL          0x2A

#define I2C_SLAVE_ADDRESS_TOUCH_PAD_1              0x20  // Touch pad.  Address is common for HSB/WSB, Synaptic
#define I2C_SLAVE_ADDRESS_SAR_1_WSB                0x48  // TI SAR device for WSB

#define I2C_PLATFORM_SIGNATURE          SIGNATURE_32 ('I', '2', 'C', 'M')
#define I2C_PLATFORM_CONTEXT_FROM_ENUMERATION_PROTOCOL(a) CR (a, I2C_PLATFORM_CONTEXT, Enumerate, I2C_PLATFORM_SIGNATURE)
#define I2C_PLATFORM_CONTEXT_FROM_BUS_CFG_PROTOCOL(a) CR (a, I2C_PLATFORM_CONTEXT, BusConfiguration, I2C_PLATFORM_SIGNATURE)

#define DIM(x) (sizeof (x) / sizeof (x[0]))

UINT32 mTouchPanelI2cAddress[] = {
  I2C_SLAVE_ADDRESS_ATMEL_3432_TOUCHPANEL
};

#define DEVICE_ID_TOUCHPANEL 1
#define TOUCHPANEL_HW_REVISION 1
#define BUS_CONFIG_0 0
#define I2C_PLATFORM_DRIVER_VERSION 0

EFI_GUID gTouchPanelDeviceGuid = { 0x1bf4b7ae, 0xc199, 0x4f10, { 0xa8, 0xc6, 0xd0, 0xc1, 0xd0, 0x10, 0x98, 0x06 } };

EFI_I2C_DEVICE mI2cDeviceList [ ] = {
  { &gTouchPanelDeviceGuid, DEVICE_ID_TOUCHPANEL, TOUCHPANEL_HW_REVISION, BUS_CONFIG_0, DIM ( mTouchPanelI2cAddress), &mTouchPanelI2cAddress[0] },
  { 0, 0, 0, 0, 0, 0 }, // End of I2c devices list.
};

typedef struct {
  UINTN                                         Signature;
  EFI_HANDLE                                    ControllerHandle;
  EFI_I2C_ENUMERATE_PROTOCOL                    Enumerate;
  EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL BusConfiguration;
  UINTN                                         I2cNumber;
} I2C_PLATFORM_CONTEXT;

typedef struct {
  ACPI_EXTENDED_HID_DEVICE_PATH   AcpiExtendedPath;
  CHAR8                           Strings[3];//this field's real size depends on length of HID, CID and UID strings
} ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STRINGS;

/**
  Retrieves I2c address of the touchpanel model selected in BIOS setup
**/
UINT16
GetTouchpanelI2cAddress (
  VOID
  )
{
  SETUP_DATA              SetupData;
  EFI_STATUS              Status;
  UINTN                   Size;

  Size = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (L"Setup", &gSetupVariableGuid, NULL, &Size, &SetupData);
  if (EFI_ERROR(Status)) {
    return 0xFFFF;
  }
  switch(SetupData.PchI2cTouchPanelType) {
    case 1: return I2C_SLAVE_ADDRESS_ATMEL_3432_TOUCHPANEL;
    case 2: return I2C_SLAVE_ADDRESS_ATMEL_2952_TOUCHPANEL;
    case 3: return I2C_SLAVE_ADDRESS_ELAN_2097_TOUCHPANEL;
    case 4: return I2C_SLAVE_ADDRESS_NTRIG_SAMSUNG_TOUCHPANEL;
    case 5: return I2C_SLAVE_ADDRESS_NTRIG_SHARP_TOUCHPANEL;
    case 6: return SetupData.PchI2cTouchPanelBusAddress;
    default: return 0xFFFF;
  }

}

/*
  Set bus configuration
  Since our platforms support only a single configuration per i2c bus,
  the only thing this function needs to do is to configure i2c master for correct bus speed
*/
EFI_STATUS
EFIAPI
SetConfiguration (
  IN CONST EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL *This,
  IN UINTN                                               I2cBusConfiguration,
  IN EFI_EVENT                                           Event      OPTIONAL,
  IN EFI_STATUS                                          *I2cStatus OPTIONAL
  )
{
  I2C_PLATFORM_CONTEXT     *Context;
  EFI_I2C_MASTER_PROTOCOL  *MasterProtocol;
  EFI_I2C_ENUMERATE_PROTOCOL *EnumerateProtocol;
  EFI_STATUS               Status;
  UINTN                    Frequency;

  Context = I2C_PLATFORM_CONTEXT_FROM_BUS_CFG_PROTOCOL (This);

  Status = gBS->OpenProtocol (
                  Context->ControllerHandle,
                  &gEfiI2cEnumerateProtocolGuid,
                  (VOID **) &EnumerateProtocol,
                  Context->ControllerHandle,
                  Context->ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG (( DEBUG_INFO, "SetConfiguration error @Enum, %r\n", Status ));
    return Status;
  }
  Status = EnumerateProtocol->GetBusFrequency(EnumerateProtocol, I2cBusConfiguration, &Frequency);
  gBS->CloseProtocol ( Context->ControllerHandle,
                       &gEfiI2cEnumerateProtocolGuid,
                       Context->ControllerHandle,
                       Context->ControllerHandle );

  Status = gBS->OpenProtocol (
                  Context->ControllerHandle,
                  &gEfiI2cMasterProtocolGuid,
                  (VOID **) &MasterProtocol,
                  Context->ControllerHandle,
                  Context->ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG (( DEBUG_INFO, "SetConfiguration error @Master, %r\n", Status ));
    return Status;
  }
  Status = MasterProtocol->SetBusFrequency(MasterProtocol, &Frequency);
  gBS->CloseProtocol ( Context->ControllerHandle,
                       &gEfiI2cMasterProtocolGuid,
                       Context->ControllerHandle,
                       Context->ControllerHandle );

  if (I2cStatus != NULL) {
    *I2cStatus = Status;
  };
  if (Event != NULL) {
    gBS->SignalEvent(Event);
  };
  return Status;
}

/**
  Get PCI Device ID from device pointed to by handle.
  If valid DeviceID can't be retrieved, 0xFFFF is returned

  @param[in] Handle   device handle

  retval     PCI Device ID
**/
UINT16
GetPciDevId (
  EFI_HANDLE Handle
  )
{
  EFI_STATUS          Status;
  EFI_PCI_IO_PROTOCOL *PciIo;
  UINT32 VenDevId;

  Status = gBS->OpenProtocol (
                  Handle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  Handle,
                  Handle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return 0xFFFF;
  }
  Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, 0, 1, &VenDevId);
  gBS->CloseProtocol ( Handle,
                       &gEfiPciIoProtocolGuid,
                       Handle,
                       Handle );
  if (EFI_ERROR(Status)) {
    return 0xFFFF;
  }
  return (VenDevId>>16);
}

/**
  Get Acpi HID from device pointed to by handle.
  If valid Acpi HID can't be retrieved, null string is returned

  @param[in] Handle   device handle

  retval     HID string
**/
CHAR8*
GetAcpiHID (
  EFI_HANDLE Handle
  )
{
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL *EndPath;

  DevicePath = DevicePathFromHandle ( Handle );
  if ( NULL == DevicePath ) {
    return "";
  }
  EndPath = DevicePath;
  while ( !IsDevicePathEnd ( EndPath )) {
    DevicePath = EndPath;
    EndPath = NextDevicePathNode ( EndPath );
  }
  if (DevicePath->Type==ACPI_DEVICE_PATH && DevicePath->SubType==ACPI_EXTENDED_DP) {
    return ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STRINGS*)DevicePath)->Strings;
  }
  return "";
}

/*
  GetBusFrequency
  For now, this function simply returns 100kHz because we only use one bus,
  single configuration, with a single device and it accepts just that speed
*/
EFI_STATUS
EFIAPI
GetBusFrequency (
  IN CONST EFI_I2C_ENUMERATE_PROTOCOL *This,
  IN UINTN                            I2cBusConfiguration,
  OUT UINTN                           *BusClockHertz
  )
{
  I2C_PLATFORM_CONTEXT *Context;
  SETUP_DATA              SetupData;
  EFI_STATUS              Status;
  UINTN                   Size;

  *BusClockHertz = 100*1000;

  Context = I2C_PLATFORM_CONTEXT_FROM_ENUMERATION_PROTOCOL(This);

  if (Context->I2cNumber == 1) {
    Size = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (L"Setup", &gSetupVariableGuid, NULL, &Size, &SetupData);
    if (EFI_ERROR(Status)) {
      return EFI_SUCCESS;
    }
    if (SetupData.PchI2cTouchPanelType == 6) {
      switch(SetupData.PchI2cTouchPanelSpeed) {
        case 0:
          *BusClockHertz = 100*1000;
          break;
        case 1:
          *BusClockHertz = 400*1000;
          break;
        case 2:
          *BusClockHertz = 1000*1000;
          break;
        default:;
      }
    }
  }
  return EFI_SUCCESS;
}

/*
  Enumerate
  Every time it's called, it returns next i2c device connected to this bus
*/
EFI_STATUS
EFIAPI
Enumerate (
  IN CONST EFI_I2C_ENUMERATE_PROTOCOL *This,
  IN OUT CONST EFI_I2C_DEVICE         **Device
  )
{
  I2C_PLATFORM_CONTEXT *Context;
  UINTN                Index;
  UINTN                Size;
  EFI_STATUS           Status;
  SETUP_DATA           SetupData;

  if (Device == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Size = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (L"Setup", &gSetupVariableGuid, NULL, &Size, &SetupData);
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Context = I2C_PLATFORM_CONTEXT_FROM_ENUMERATION_PROTOCOL (This);

  //TODO: add device list for other I2c controllers. Right now we only enumerate touchpanels on i2c1
  if (Context->I2cNumber != 1) {
    *Device = NULL;
    return EFI_NOT_FOUND;
  }

  if ((SetupData.PchI2cTouchPanelType != 0) &&
    (SetupData.PchI2cSensorDevicePort[Context->I2cNumber] & SERIAL_IO_I2C_TOUCHPANEL)) {
    if (*Device == NULL) {
      *Device = &mI2cDeviceList[0];
      return EFI_SUCCESS;
    }
    for (Index = 0; Index < DIM(mI2cDeviceList) - 1; Index++) {
      if (*Device == &mI2cDeviceList[Index]) {
        if (mI2cDeviceList[Index+1].DeviceGuid != 0) {
          *Device = &mI2cDeviceList[Index+1];
        }else {
          *Device = NULL;
          return EFI_NOT_FOUND;
        }
        return EFI_SUCCESS;
      }
    }
    *Device = NULL;
  }
  return EFI_NOT_FOUND;
}

/*
  I2cPlatformDriverBindingSupported
  Checks if this driver can install on device pointed to by Handle
  It will only install on I2c controllers
*/
EFI_STATUS
EFIAPI
I2cPlatformDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL *I2cBusConfigurationManagement;
  EFI_STATUS Status;
  UINT8 Number;

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiI2cBusConfigurationManagementProtocolGuid,
                  (VOID **)&I2cBusConfigurationManagement,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (Status == EFI_SUCCESS) {
    return EFI_ALREADY_STARTED;
  }

  if(!IsSerialIoI2cDeviceId (GetPciDevId(ControllerHandle),&Number)) {
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

/*
  I2cPlatformDriverBindingStart
  Starts this driver on I2c controller device pointed to by Handle
*/
EFI_STATUS
EFIAPI
I2cPlatformDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  UINT8 I2cNumber;
  I2C_PLATFORM_CONTEXT *Context;
  EFI_STATUS Status;

  mTouchPanelI2cAddress[0] = GetTouchpanelI2cAddress();

  if(!IsSerialIoI2cDeviceId (GetPciDevId(ControllerHandle),&I2cNumber)) {
    return EFI_UNSUPPORTED;
  }

  Context = AllocateZeroPool (sizeof(I2C_PLATFORM_CONTEXT));

  if (Context == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Context->Signature = I2C_PLATFORM_SIGNATURE;
  Context->ControllerHandle = ControllerHandle;
  Context->I2cNumber = I2cNumber;
  Context->Enumerate.Enumerate = Enumerate;
  Context->Enumerate.GetBusFrequency = GetBusFrequency;
  Context->BusConfiguration.EnableI2cBusConfiguration = SetConfiguration;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ControllerHandle,
                  &gEfiI2cEnumerateProtocolGuid,
                  &Context->Enumerate,
                  &gEfiI2cBusConfigurationManagementProtocolGuid,
                  &Context->BusConfiguration,
                  NULL
                  );

  return Status;
}


/*
  I2cPlatformDriverBindingStart
  Stops this driver on device pointed to by Handle
*/
EFI_STATUS
EFIAPI
I2cPlatformDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
  return EFI_SUCCESS;
}

GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL gI2cPlatformDriverBinding = {
  I2cPlatformDriverBindingSupported,
  I2cPlatformDriverBindingStart,
  I2cPlatformDriverBindingStop,
  I2C_PLATFORM_DRIVER_VERSION,
  NULL,
  NULL
};

EFI_STATUS
EFIAPI
I2cPlatformEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gI2cPlatformDriverBinding,
             ImageHandle,
             NULL,
             NULL
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
