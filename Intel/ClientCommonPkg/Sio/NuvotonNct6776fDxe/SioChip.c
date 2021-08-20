/** @file
  SIO chip specific implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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


#include "SioDriver.h"
#include <Library/S3IoLib.h>
#include <Library/DebugLib.h>

LOCAL_IO_WRITE8    mIoWrite8         = IoWrite8;
//
// COM 1 UART Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mCom1Resources = {
  {
    ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR,
    COM1_ADDRESS,
    8
  },
  {
    ACPI_IRQ_NOFLAG_DESCRIPTOR,
    COM1_IRQ_BIT
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

ACPI_SIO_RESOURCES_IO            mHwMonResources = {
  {
    ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR,
    HWMON_BASE_ADDRESS,
    8
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// Table of SIO Controllers. This table assumes COM1 (UART_A) will always
// be enabled. Compile error will happen if SIO_SUPPORT_UART_A is undefined.
//
DEVICE_INFO    mDeviceInfo[] = {
  {
    {
      EISA_PNP_ID(0x501),
      0
    },
    SIO_COM1,
    RESOURCE_IO | RESOURCE_IRQ,
    (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources,
    (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources
  },  // COM 1 UART Controller
  {
    {
      EISA_PNP_ID(0xc08),
      0
    },
    SIO_HWMON,
    RESOURCE_IO,
    (ACPI_SMALL_RESOURCE_HEADER *) &mHwMonResources,
    (ACPI_SMALL_RESOURCE_HEADER *) &mHwMonResources,
  }   // PS/2 Mouse Controller
};

//
// Using HWMON_REGISTER_PAIR for convinience, as it's already defined as
// a register/value pair. Just defining some register/value pairs that need
// to be programmed.
// This table accomplishes the following tasks: Programing multipurpose pins
// mostly to GPIO, except for those required by UART A; disabling all GPIO,
// floppy controller, LPT, and UART B to reduce power consumption; enabling
// PS2 controller. Though the PS2 controller is not physically connected, it
// is needed for legacy USB keyboard (DOS and when installing WINXP).
// Because there is no register 0xaa (0xaa is used to exit SIO configuration
// space), register 0xaa is used as a marker for end of table.
//
HWMON_REGISTER_PAIR     mGenericRegisters[] = {
  {0x1a, 0x80},
  {0x1b, 0x58},
  {0x22, 0xd6},
  {0x25, 0x0b},
  {0x2c, 0x80},
  {0x07, 0x00},
  {0x30, 0x00},
  {0x07, 0x01},
  {0x30, 0x00},
  {0x07, 0x02},
  {0xf0, 0x20},
  {0x07, 0x03},
  {0x30, 0x00},
  {0x07, 0x05},
  {0x61, 0x60},
  {0x63, 0x64},
  {0x70, 0x01},
  {0x72, 0x0c},
  {0x30, 0x01},
  {0x07, 0x07},
  {0x30, 0x00},
  {0x07, 0x08},
  {0x30, 0x00},
  {0x07, 0x09},
  {0x30, 0x00},
  {0xaa, 0xff}  // end of table.
};


/**
  Record the 8-bit I/O port writing to boot script.

  @param[in]  Port     The I/O port to write.
  @param[in]  Value    The value to write to the I/O port.

  @retval     Value    The value written the I/O port.
**/
UINT8
EFIAPI
S3BootScriptSaveIoWrite8 (
  IN      UINTN                     Port,
  IN      UINT8                     Value
  )
{
  S3BootScriptSaveIoWrite (
    S3BootScriptWidthUint8,
    Port,
    1,
    &Value
    );
  return Value;
}


/**
  Find the DEVICE_INFO for specified Device.

  @param[in]  Device        Pointer to the EFI_SIO_ACPI_DEVICE_ID.

  @retval     DEVICE_INFO*  Pointer to the DEVICE_INFO.
**/
DEVICE_INFO *
DeviceSearch (
  IN EFI_SIO_ACPI_DEVICE_ID *Device
  )
{
  UINTN       Index;

  for (Index = 0; Index < sizeof (mDeviceInfo) / sizeof (mDeviceInfo[0]); Index++) {
    if (CompareMem (Device, &mDeviceInfo[Index].Device, sizeof (*Device)) == 0) {
      return &mDeviceInfo[Index];
    }
  }

  ASSERT (FALSE);
  return NULL;
}


/**
  Perform a 8-bit I/O write to SIO register.

  @param[in]  Index  The register index.
  @param[in]  Data   The value to write to register.
**/
VOID
WriteRegister (
  IN  UINT8            Index,
  IN  UINT8            Data
  )
{
  mIoWrite8 (SIO_INDEX_PORT, Index);
  mIoWrite8 (SIO_DATA_PORT, Data);
}


/**
  Perform a 8-bit I/O read from SIO register.

  @param[in]  Index  The register index.

  @retval     Value  The value written to the register.
**/
UINT8
ReadRegister (
  IN  UINT8            Index
  )
{
  IoWrite8 (SIO_INDEX_PORT, Index);
  return IoRead8 (SIO_DATA_PORT);
}


/**
  Program the SIO chip to enter the configure mode.
**/
VOID
EnterConfigMode (
  VOID
  )
{
  mIoWrite8 (SIO_CONFIG_PORT, 0x87);
  mIoWrite8 (SIO_CONFIG_PORT, 0x87);
}


/**
  Program the SIO chip to exit the configure mode.
**/
VOID
ExitConfigMode (
  VOID
  )
{
  mIoWrite8 (SIO_CONFIG_PORT, 0xAA);
}


/**
  Program the SIO chip to select the specified device.

  @param[in]  Device       Pointer to EFI_SIO_ACPI_DEVICE_ID.

  @retval     DEVICE_INFO  Pointer to DEVICE_INFO.
**/
DEVICE_INFO *
DeviceSelect (
  IN EFI_SIO_ACPI_DEVICE_ID *Device
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);
  WriteRegister (REG_SIO_LOGICAL_DEVICE, DeviceInfo->DeviceId);
  return DeviceInfo;
}


/**
  Program the SIO chip to set the IO base address of the specified device.

  @param[in]  Device       Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in]  BaseAddress  The base address to set.
**/
VOID
DeviceSetIo (
  IN EFI_SIO_ACPI_DEVICE_ID *Device,
  IN UINT16                 BaseAddress
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  if ((DeviceInfo->ResourceMask & RESOURCE_IO) == RESOURCE_IO) {
    WriteRegister (R_SIO_BASE_ADDRESS_HIGH, (UINT8) (BaseAddress >> 8));
    WriteRegister (R_SIO_BASE_ADDRESS_LOW,  (UINT8) BaseAddress);
  }
}


/**
  Program the SIO chip to set the IRQ of the specified device.

  @param[in]  Device      Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in]  Irq         The IRQ to set.
**/
VOID
DeviceSetIrq (
  IN EFI_SIO_ACPI_DEVICE_ID *Device,
  IN UINT8                  Irq
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  if ((DeviceInfo->ResourceMask & RESOURCE_IRQ) == RESOURCE_IRQ) {
    WriteRegister (R_SIO_PRIMARY_INTERRUPT_SELECT, Irq);
  }
}


/**
  Program the SIO chip to set the DMA of the specified device.

  @param[in]  Device      Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in]  Dma         The DMA to set.
**/
VOID
DeviceSetDma (
  IN EFI_SIO_ACPI_DEVICE_ID *Device,
  IN UINT8                  Dma
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  if ((DeviceInfo->ResourceMask & RESOURCE_DMA) == RESOURCE_DMA) {
    WriteRegister (R_SIO_DMA_CHANNEL_SELECT, Dma);
  }
}


/**
  Get the ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DeviceGetResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  *Resources = DeviceInfo->Resources;

  return EFI_SUCCESS;
}


/**
  Set the ACPI resources for specified device.

  The SIO chip is programmed to use the new resources and the
  resources setting are saved. The function assumes the resources
  are valid.

  @param[in] Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in] Resources       ACPI_RESOURCE_HEADER_PTR.

  @retval    EFI_SUCCESS     The resources are set successfully.
**/
EFI_STATUS
DeviceSetResources (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device,
  IN ACPI_RESOURCE_HEADER_PTR Resources
  )
{
  DEVICE_INFO                                 *DeviceInfo;
  ACPI_RESOURCE_HEADER_PTR                    ResourcePtr;
  ACPI_RESOURCE_HEADER_PTR                    ResourcePtr2;
  EFI_ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR  *FixedIo;
  EFI_ACPI_IRQ_DESCRIPTOR                     *Irq;
  EFI_ACPI_DMA_DESCRIPTOR                     *Dma;

  ResourcePtr = Resources;
  DeviceInfo  = DeviceSearch (Device);

  EnterConfigMode ();
  DeviceSelect (Device);
  while (ResourcePtr.SmallHeader->Byte != ACPI_END_TAG_DESCRIPTOR) {

    switch (ResourcePtr.SmallHeader->Byte) {
      case ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR:
        FixedIo = (EFI_ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR *) ResourcePtr.SmallHeader;
        DeviceSetIo (Device, FixedIo->BaseAddress);
        break;

      case ACPI_IRQ_NOFLAG_DESCRIPTOR:
      case ACPI_IRQ_DESCRIPTOR:
        Irq = (EFI_ACPI_IRQ_DESCRIPTOR *) ResourcePtr.SmallHeader;
        DeviceSetIrq (Device, (UINT8) LowBitSet32 ((UINT32) Irq->Mask));
        break;

      case ACPI_DMA_DESCRIPTOR:
        Dma = (EFI_ACPI_DMA_DESCRIPTOR *) ResourcePtr.SmallHeader;
        DeviceSetDma (Device, (UINT8) LowBitSet32 ((UINT32) Dma->ChannelMask));
        break;
    }

    //
    // Update the current resource
    //
    ResourcePtr2 = DeviceInfo->Resources;
    while (ResourcePtr2.SmallHeader->Byte != ACPI_END_TAG_DESCRIPTOR) {
      if (ResourcePtr2.SmallHeader->Byte == ResourcePtr.SmallHeader->Byte) {
        if (ResourcePtr2.SmallHeader->Bits.Type == 0) {
          CopyMem (
            ResourcePtr2.SmallHeader,
            ResourcePtr.SmallHeader,
            ResourcePtr.SmallHeader->Bits.Length + sizeof (*ResourcePtr.SmallHeader)
            );
        } else {
          CopyMem (
            ResourcePtr2.LargeHeader,
            ResourcePtr.LargeHeader,
            ResourcePtr.LargeHeader->Length + sizeof (*ResourcePtr.LargeHeader)
            );
        }
		break;
      }

      if (ResourcePtr2.SmallHeader->Bits.Type == 0) {
        ResourcePtr2.SmallHeader = (ACPI_SMALL_RESOURCE_HEADER *) ((UINT8 *) ResourcePtr2.SmallHeader
                                + ResourcePtr2.SmallHeader->Bits.Length
                                + sizeof (*ResourcePtr2.SmallHeader));
      } else {
        ResourcePtr2.LargeHeader = (ACPI_LARGE_RESOURCE_HEADER *) ((UINT8 *) ResourcePtr2.LargeHeader
                                + ResourcePtr2.LargeHeader->Length
                                + sizeof (*ResourcePtr2.LargeHeader));
      }

    }
    //
    // Should find a match
    //
    ASSERT (ResourcePtr2.SmallHeader->Byte != ACPI_END_TAG_DESCRIPTOR);


    if (ResourcePtr.SmallHeader->Bits.Type == 0) {
      ResourcePtr.SmallHeader = (ACPI_SMALL_RESOURCE_HEADER *) ((UINT8 *) ResourcePtr.SmallHeader
                              + ResourcePtr.SmallHeader->Bits.Length
                              + sizeof (*ResourcePtr.SmallHeader));
    } else {
      ResourcePtr.LargeHeader = (ACPI_LARGE_RESOURCE_HEADER *) ((UINT8 *) ResourcePtr.LargeHeader
                              + ResourcePtr.LargeHeader->Length
                              + sizeof (*ResourcePtr.LargeHeader));
    }
  }

  ExitConfigMode ();

  return EFI_SUCCESS;
}


/**
  Get the possible ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DevicePossibleResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  *Resources = DeviceInfo->PossibleResources;

  return EFI_SUCCESS;
}


/**
  Program the SIO chip to enable the specified device using the default resource.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
**/
VOID
DeviceEnable (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device
  )
{
  
  ACPI_RESOURCE_HEADER_PTR    Resources;

  DeviceGetResources (Device, &Resources);
  DeviceSetResources (Device, Resources);

  EnterConfigMode ();
  DeviceSelect (Device);
  WriteRegister (R_SIO_ACTIVATE, 1);
  ExitConfigMode ();
}


/**
  Return the supported devices.

  @param[out] Devices         Pointer to pointer of EFI_SIO_ACPI_DEVICE_ID.
                              Caller is responsible to free the buffer.
  @param[out] Count           Pointer to UINTN holding the device count.
**/
VOID
DeviceGetList (
  OUT EFI_SIO_ACPI_DEVICE_ID **Devices,
  OUT UINTN                  *Count
  )
{
  EFI_SIO_ACPI_DEVICE_ID     *LocalDevices;
  UINTN                      LocalCount;

  //
  // Allocate enough memory for simplicity
  //
  LocalDevices = AllocatePool (sizeof (EFI_SIO_ACPI_DEVICE_ID) * 5);
  ASSERT (LocalDevices != NULL);
  if (LocalDevices != NULL){
    LocalCount   = 0;

    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[0].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount ++;

    *Devices = LocalDevices;
    *Count   = LocalCount;
  }
}


/**
  Initialize the SIO chip for S3.
**/
VOID
SioInitAndSaveS3 (
  VOID
  )
{
  EFI_SIO_ACPI_DEVICE_ID  *Devices;
  HWMON_REGISTER_PAIR     *RegisterPtr;
  UINTN                   Index;
  UINTN                   Count;
  //
  // LPC device is connected to PCH LPC interface on the
  // platform. Most PCH initialization work is done in Platform Code
  // such as Platform PEIM and Platform DXE driver.
  // Please make sure the initialization works are ready
  // This driver (NuvotonNct6776F) assumes that all PCH initialization has
  // been done before this driver is started to manage the device.
  //

  //
  // Use S3BootScriptSaveIoWrite8(...) function. This will simply add the
  // required IO to the S3 table.
  //

  mIoWrite8        = S3BootScriptSaveIoWrite8;

  //
  // The procedure DeviceGetList has ben modified to only return the UART A.
  // However, UART A is actually initialized at PEI, so here UART A is only
  // saved to the SIO table, no actual IO is required.
  //
  DeviceGetList (&Devices, &Count);

  for (Index = 0; Index < Count; Index++) {
    DeviceEnable (&Devices[Index]);
  }

  FreePool (Devices);
  //
  // Generic programming: SIO global registers, disable unused devices, force
  // all unused possible GPIO pins to input GPIO. This will both access the
  // IO and save it to the S3 table. This initialization was not done at PEI.
  //

  RegisterPtr = mGenericRegisters;
  //
  // Use S3IoWrite8(...) function. This will both access the IO and save it
  // to the S3 table.
  //
  mIoWrite8 = S3IoWrite8;
  EnterConfigMode();
  while (RegisterPtr->Register != 0xaa) {
    WriteRegister (RegisterPtr->Register, RegisterPtr->Value);
    RegisterPtr++;
  }
  ExitConfigMode();
  //
  // Return to simple IO access.
  //
  mIoWrite8        = IoWrite8;
}

/* Here starts Hardware Monitor Specific Code */

VOID
SetHwMonRegister (
  IN  UINT8 Register,
  IN  UINT8 Value
  )
{
  S3IoWrite8 (HWMON_INDEX_ADDRESS, Register);
  S3IoWrite8 (HWMON_DATA_ADDRESS, Value);
}

EFI_STATUS
EFIAPI
Nct6776fHwMonStart(
  VOID
  )
{
  EFI_STATUS              Status = 0;
  EFI_SIO_ACPI_DEVICE_ID  HwMonDevice;

  DEBUG ((DEBUG_INFO, "SIO Nct6776fHwMonStart\n"));

  //Move Lpc decode programing to Platform code.
  //S3IoWrite32 (0xcf8, LpcControlRegister);
  //S3IoWrite32 (0xcfc, (UINT32) (0x001C0001 | HWMON_BASE_ADDRESS));
  
  mIoWrite8 = S3IoWrite8;
  HwMonDevice.HID = EISA_PNP_ID(0xc08);
  HwMonDevice.UID = 0;
  DeviceEnable(&HwMonDevice);
  mIoWrite8 = IoWrite8;
  return Status;
}

EFI_STATUS
EFIAPI
Nct6776fHwMonSetBankValues (
  IN  HWMON_REGISTER_PAIR  *RegisterPair,
  IN  UINT8                 Bank,
  IN  UINT8                 RegisterCount
  )
{
  EFI_STATUS            Status    = 0;
  HWMON_REGISTER_PAIR  *BankValuesPtr;
  UINT8                 BankValue = 0x80;
  UINT8                 i;

  BankValue |= Bank;
  BankValuesPtr = RegisterPair;
  SetHwMonRegister (0x4e, BankValue);
  for (i=0; i<RegisterCount; i++) {
    SetHwMonRegister (
      BankValuesPtr->Register,
      BankValuesPtr->Value
      );
    BankValuesPtr++;
  }
  return Status;
}

EFI_STATUS
EFIAPI
Nct6776fHwMonReadRegister (
  IN  UINT8     Register,
  OUT UINT8    *Value
  )
{
  EFI_STATUS            Status    = 0;


 

  IoWrite8 (HWMON_INDEX_ADDRESS, Register);
  *Value = IoRead8 (HWMON_DATA_ADDRESS);
  return Status;
}
