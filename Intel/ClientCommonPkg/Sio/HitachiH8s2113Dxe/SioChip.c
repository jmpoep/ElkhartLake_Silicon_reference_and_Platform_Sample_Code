/** @file
  Hitachi H8S/2113 Super I/O specific implementation.

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
// System configuration (setup) information
//
// SYSTEM_CONFIGURATION                mSystemConfiguration;

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
    0,
    RESOURCE_IO | RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources }
  },  // COM 1 UART Controller
  {
    {
      EISA_PNP_ID(0x303),
      0
    },
    0,
    0,  // Cannot change resource
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources }
  },  // PS/2 Keyboard Controller
  {
    {
      EISA_PNP_ID(0xF03),
      0
    },
    0,
    0,  // Cannot change resource
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources }
  }  // PS/2 Mouse Controller
};


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
  EFI_SIO_ACPI_DEVICE_ID   *LocalDevices;
  UINTN                    LocalCount;
  UINTN                    DeviceCount;
  UINTN                    Index;

  //
  // Allocate enough memory for simplicity
  //
  DeviceCount =  sizeof (mDeviceInfo) / sizeof (mDeviceInfo[0]);
  LocalDevices = AllocatePool (sizeof (EFI_SIO_ACPI_DEVICE_ID) * DeviceCount);
  ASSERT (LocalDevices != NULL);
  if (LocalDevices == NULL) {
    return;
  }
  LocalCount = 0;

  for (Index = 0; Index < DeviceCount; Index++) {
    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[Index].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount++;
  }

  *Devices = LocalDevices;
  *Count   = LocalCount;
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

  if ((IoRead8(EC_COMMAND_PORT) == 0xFF) && (IoRead8 (EC_DATA_PORT) == 0xFF)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
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
  Program the SIO chip to enable the specified device using the default resource.

  @param[in] Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
**/
VOID
DeviceEnable (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device
  )
{
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

  @retval    EFI_UNSUPPORTED
**/
EFI_STATUS
DeviceSetResources (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device,
  IN ACPI_RESOURCE_HEADER_PTR Resources
  )
{
  return EFI_UNSUPPORTED;
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
