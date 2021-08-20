/** @file
  SIO chip specific implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

LOCAL_IO_WRITE8    mIoWrite8         = IoWrite8;
//
// COM 1 UART Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mCom1Resources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x3f8,
    8
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT4    // IRQ4
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// LPT 1 Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mLpt1Resources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x378,
    8
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT7
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// PS/2 Keyboard Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mKeyboardResources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x60,
    5
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT1
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// PS/2 Mouse Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mMouseResources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x60,
    5
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT12
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// Table of SIO Controllers
//
DEVICE_INFO    mDeviceInfo[] = {
  {
    {
      EISA_PNP_ID(0x501),
      0
    },
    SIO_COM1,
    RESOURCE_IO | RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources }
  },  // COM 1 UART Controller
  {
    {
      EISA_PNP_ID(0x401),
      0
    },
    SIO_PARA,
    RESOURCE_IO | RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mLpt1Resources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mLpt1Resources }
  },  // LPT 1 Controller
  {
    {
      EISA_PNP_ID(0x303),
      0
    },
    SIO_KYBD,
    RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources }
  },  // PS/2 Keyboard Controller
  {
    {
      EISA_PNP_ID(0xF03),
      0
    },
    SIO_MOUSE,
    RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources }
  }   // PS/2 Mouse Controller
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
  mIoWrite8 (SIO_CONFIG_PORT, 0x55);
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
  WriteRegister (R_SIO_LOGICAL_DEVICE, DeviceInfo->DeviceId);
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

      break;
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
  LocalDevices = AllocatePool (sizeof (EFI_SIO_ACPI_DEVICE_ID) * 4);
  ASSERT (LocalDevices != NULL);
  if (LocalDevices == NULL) {
    return;
  }
  LocalCount   = 0;

  CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[0].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
  LocalCount ++;

  CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[1].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
  LocalCount ++;

  CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[2].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
  LocalCount ++;

  CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[3].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
  LocalCount ++;

  *Devices = LocalDevices;
  *Count   = LocalCount;
}


/**
  Initialize the SIO chip for S3.
**/
VOID
SioInitForS3 (
  VOID
  )
{
  UINTN                   Index;
  EFI_SIO_ACPI_DEVICE_ID  *Devices;
  UINTN                   Count;

  //
  // LPC device is connected to ICH LPC interface on the 
  // platform. Most ICH initialization work is done in Platform Code
  // such as Platform PEIM and Platform DXE driver. 
  // Please make sure the initialization works are ready

  // For example, the initialization works include:
  // 1) Enable serial IRQ, and set mode to continous, 4 clocks (DxePlatformDriverEntry)
  // 2) LPC I/F enable (PeiIchPostMemInit)
  // 3) Enable ptp bridge offset 04 for floppy working properly (PeiIchPostMemInit:Enable Bus Master on HubLink #1 to PCI Bridge)
  // 4) ICH DMA I/O register initialization 
 

  // This driver (SmscLpc47m17xDxe) assumes
  // that all ICH initialization has been done before this driver is
  // started to manage the device. 

  //
  // Use S3BootScriptSaveIoWrite8(...) function
  //  the following actions only apply to the boot script instead of real IO operation
  //
  DeviceGetList (&Devices, &Count);
  mIoWrite8        = S3BootScriptSaveIoWrite8;

  for (Index = 0; Index < Count; Index++) {
    DeviceEnable (&Devices[Index]);
  }

  mIoWrite8        = IoWrite8;

  FreePool (Devices);
  //
  // Save Init 8042 Keyboard Controll to Script Table for S3.
  //
  // Actually, this code was added for 815 platform S3 support.
  //  At that time, I remember if we remove the Keyboard intialization, 
  //  then we may have problem to get back into OS. I don't know why OS seems to need it.
  //  Some legacy BIOSes also have the KBC initialization?code on S3 resume. 
  //  It can be considered as part of the S3 boot path to provide a better pre-OS environment.
  // 
  S3BootScriptSaveIoWrite8 (0x64, 0xaa);
}

/**
  Super I/O controller initialization.

  @retval     EFI_SUCCESS       The super I/O controller is found and initialized.
  @retval     EFI_UNSUPPORTED   The super I/O controller is not found.
**/
EFI_STATUS
SioInit (
  VOID
  )
{
  EFI_SIO_ACPI_DEVICE_ID Keyboard;
  EFI_SIO_ACPI_DEVICE_ID Mouse;

  //
  // Read SIO Device ID
  // If Data is 0xFF, which means Device ID is invalid.
  // Return EFI_DEVICE_ERROR to indicate no SIO device is found or device error.
  //
  IoWrite8 (SIO_INDEX_PORT, REG_DEVICE_ID);
  if (IoRead8 (SIO_DATA_PORT) == 0xFF) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Record the SIO chip initialization to boot script
  //
  SioInitForS3 ();

  //
  // Initialize Keyboard for legacy USB
  //
  Keyboard.HID = EISA_PNP_ID(0x303);
  Keyboard.UID = 0;
  DeviceEnable (&Keyboard);
  Mouse.HID = EISA_PNP_ID(0xF03);
  Mouse.UID = 0;
  DeviceEnable (&Mouse);

  return EFI_SUCCESS;
}
