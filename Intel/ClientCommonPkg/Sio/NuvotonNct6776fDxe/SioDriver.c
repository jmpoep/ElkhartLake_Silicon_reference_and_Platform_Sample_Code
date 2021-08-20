/** @file
  EFI Driver following Driver Binding Protocol for Nuvoton Nct6776f device.

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


//
// This driver is for ACPI(PNP0A03,0)/PCI(0x1f,0)
//
//
//  Sio Driver Global Variables
//
EFI_DRIVER_BINDING_PROTOCOL mSioDriver = {
  SioDriverSupported,
  SioDriverStart,
  SioDriverStop,
  1,
  NULL,
  NULL
};

NCT6776F_HWMON_PROTOCOL mNct6776fHwMon = {
  Nct6776fHwMonStart,
  Nct6776fHwMonSetBankValues,
  Nct6776fHwMonReadRegister
};

EFI_HANDLE HwMonHandle = NULL;

//
// The list of the created SIO_DEV
//
LIST_ENTRY                  mSioDevPool = INITIALIZE_LIST_HEAD_VARIABLE (mSioDevPool);

//
// Template structure to create SIO_DEV
//
SIO_DEV                     mSioDevTemplate = {
  SIO_DEV_SIGNATURE,        // Signature
  NULL,                     // PciHandle
  {
    0x00000000,             // HID
    0x00000000              // UID
  },
  NULL,                     // Handle
  {                         // Sio Instance
    SioRegisterAccess,
    SioGetResources,
    SioSetResources,
    SioPossibleResources,
    SioModify
  },
  NULL,                     // DevicePath
  {
    NULL,                   // ForwardLink
    NULL,                   // BackLink
  }
};

//
// Template ACPI_HID_DEVICE_PATH structure to create device path
//
ACPI_HID_DEVICE_PATH        mAcpiNodeTemplate = {
  {
    ACPI_DEVICE_PATH,       // Type
    ACPI_DP,                // SubType
    {
      sizeof (ACPI_HID_DEVICE_PATH),  // Length[0]
      0                               // Length[1]
    }
  },
  0x00000000,               // HID
  0x00000000                // UID
};


/**
  The user Entry Point for module NuvotonNct6776F. The user code starts with this function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval    EFI_SUCCESS    The entry point is executed successfully.
  @retval    other          Some error occurs when executing this entry point.
**/
EFI_STATUS
EFIAPI
SioDriverEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "SioDriverEntryPoint - Start\n"));
  //
  // Assume it is NTC6776F and try to open configuration space (by writing
  // 0x87 twice to the index port) and read the device ID. If it's not the
  // correct device ID, try to close the configuration space by writing 0xaa
  // to the index port (several SIO use the same sequence to open and close
  // configuration space, but some older SIO have the configuration space
  // always open) and return EFI_DEVICE_ERROR.
  //
  IoWrite8 (SIO_CONFIG_PORT, 0x87);
  IoWrite8 (SIO_CONFIG_PORT, 0x87);
  IoWrite8 (SIO_INDEX_PORT, REG_DEVICE_ID);

  if (IoRead8 (SIO_DATA_PORT) == 0xC3) {
    IoWrite8 (SIO_INDEX_PORT, REG_DEVICE_REV);
    if ((IoRead8 (SIO_DATA_PORT) & 0xF0) != 0x30) {
      IoWrite8 (SIO_CONFIG_PORT, 0xaa);
      return EFI_UNSUPPORTED;
    }
  } else {
    IoWrite8 (SIO_CONFIG_PORT, 0xaa);
    return EFI_UNSUPPORTED;
  }

  //
  // NCT6776F detected, install the hardware monitor protocol which will be
  // used to initialize and program the hardware monitor within the SIO.
  //
  Status = gBS->InstallProtocolInterface (
                  &HwMonHandle,
                  &gNct6776fHwMonProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mNct6776fHwMon
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Record the SIO chip initialization to boot script
  //
  SioInitAndSaveS3 ();

  DEBUG ((DEBUG_INFO, "SioDriverEntryPoint - End\n"));

  return EfiLibInstallDriverBindingComponentName2 (
           ImageHandle,
           SystemTable,
           &mSioDriver,
           ImageHandle,
           &mSioComponentName,
           &mSioComponentName2
           );
}


/**
  Test to see if this driver supports Controller Handle.

  @param[in]  This                Protocol instance pointer.
  @param[in]  Controller          Handle of device to test
  @param[in]  RemainingDevicePath Optional parameter use to pick a specific child
                                  device to start.

  @retval     EFI_SUCCESS         This driver supports this device
  @retval     EFI_ALREADY_STARTED This driver is already running on this device
  @retval     other               This driver does not support this device
**/
EFI_STATUS
EFIAPI
SioDriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  EFI_DEVICE_PATH_PROTOCOL  *ParentDevicePath;
  ACPI_HID_DEVICE_PATH      *AcpiNode;
  PCI_TYPE00                Pci;
  UINTN                     Index;
  EFI_SIO_ACPI_DEVICE_ID    *Devices;
  UINTN                     Count;
  UINTN                     SegmentNumber;
  UINTN                     BusNumber;
  UINTN                     DeviceNumber;
  UINTN                     FunctionNumber;

  //
  // If RemainingDevicePath is not NULL, it should verify that the first device
  // path node in RemainingDevicePath is an ACPI Device path node which is a 
  // legal Device Path Node for this bus driver's children.
  //
  if (RemainingDevicePath != NULL) {
    if (!IsDevicePathEnd (RemainingDevicePath)) {
      if ((RemainingDevicePath->Type != ACPI_DEVICE_PATH) ||
          ((RemainingDevicePath->SubType != ACPI_DP) || (DevicePathNodeLength (RemainingDevicePath) != sizeof (ACPI_HID_DEVICE_PATH))) &&
          ((RemainingDevicePath->SubType != ACPI_EXTENDED_DP) || (DevicePathNodeLength (RemainingDevicePath) != sizeof (ACPI_EXTENDED_HID_DEVICE_PATH)))
          ) {
        return EFI_UNSUPPORTED;
      }

      DeviceGetList (&Devices, &Count);
      if (Devices == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }
      AcpiNode = (ACPI_HID_DEVICE_PATH *) RemainingDevicePath;
      for (Index = 0; Index < Count; Index++) {
        if ((AcpiNode->HID == Devices[Index].HID) &&
            (AcpiNode->UID == Devices[Index].UID)) {
          break;
        }
      }
      FreePool (Devices);
      if (Index == Count) {
        return EFI_UNSUPPORTED;
      }
    }
  }

  //
  // See if the parent device path can be opened BY_DRIVER
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &ParentDevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  gBS->CloseProtocol (
         Controller,
         &gEfiDevicePathProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  //
  // Get PciIo protocol instance
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (!EFI_ERROR (Status)) {
    Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint32,
                          0,
                          sizeof (Pci) / sizeof (UINT32),
                          &Pci
                          );
    ASSERT_EFI_ERROR (Status);

    Status = EFI_UNSUPPORTED;
    if ((Pci.Hdr.Command & (EFI_PCI_COMMAND_IO_SPACE | EFI_PCI_COMMAND_MEMORY_SPACE))
                        == (EFI_PCI_COMMAND_IO_SPACE | EFI_PCI_COMMAND_MEMORY_SPACE)
       ) {
      if (Pci.Hdr.ClassCode[2] == PCI_CLASS_BRIDGE) {
        //
        // See if this is a standard PCI to ISA Bridge from the Base Code and Class Code
        //
        if (Pci.Hdr.ClassCode[1] == PCI_CLASS_BRIDGE_ISA) {
          Status = EFI_SUCCESS;
        }

        //
        // See if this is an Intel PCI to ISA Bridge in Positive Decode Mode
        //
        if ((Pci.Hdr.ClassCode[1] == PCI_CLASS_BRIDGE_ISA_PDECODE) &&
            (Pci.Hdr.VendorId == INTEL_VENDOR_ID)) {
          //
          // See if this is on Function #0 to avoid false positive on
          // PCI_CLASS_BRIDGE_OTHER that has the same value as
          // PCI_CLASS_BRIDGE_ISA_PDECODE
          //
          Status = PciIo->GetLocation (
                            PciIo,
                            &SegmentNumber,
                            &BusNumber,
                            &DeviceNumber,
                            &FunctionNumber
                            );
          if (!EFI_ERROR (Status) && (FunctionNumber == 0)) {
            Status = EFI_SUCCESS;
          } else {
            Status = EFI_UNSUPPORTED;
          }
        }
      }
    }

    gBS->CloseProtocol (
           Controller,
           &gEfiPciIoProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
  }
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  return EFI_SUCCESS;
}


/**
  Destroy the SIO controller handle.

  @param[in]  ChildHandle     The SIO controller handle.

  @retval     EFI_SUCCESS     The SIO controller handle is destroyed successfully.
**/
EFI_STATUS
SioDestroyDevice (
  IN EFI_HANDLE                ChildHandle
  )
{
  EFI_STATUS                Status;
  SIO_DEV                   *SioDev;
  EFI_SIO_PROTOCOL          *Sio;
  EFI_PCI_IO_PROTOCOL       *PciIo;

  Status = gBS->HandleProtocol (
                  ChildHandle,
                  &gEfiSioProtocolGuid,
                  (VOID **) &Sio
                  );
  ASSERT_EFI_ERROR (Status);

  SioDev = SIO_DEV_FROM_THIS (Sio);

  Status = gBS->CloseProtocol (
                  SioDev->PciHandle,
                  &gEfiPciIoProtocolGuid,
                  mSioDriver.DriverBindingHandle,
                  ChildHandle
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ChildHandle,
                  &gEfiDevicePathProtocolGuid,
                  SioDev->DevicePath,
                  &gEfiSioProtocolGuid,
                  &SioDev->Sio,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    gBS->OpenProtocol (
           SioDev->PciHandle,
           &gEfiPciIoProtocolGuid,
           (VOID **) &PciIo,
           mSioDriver.DriverBindingHandle,
           ChildHandle,
           EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
           );
    return Status;
  }

  RemoveEntryList (&SioDev->Link);
  FreePool (SioDev->DevicePath);
  FreePool (SioDev);
  return EFI_SUCCESS;
}


/**
  Create the SIO controller handle.

  @param[in]  Controller       The parent PCI controller handle.
  @param[in]  Device           Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in]  ParentDevicePath The device path of the parent controller.
  @param[out] PciIo            The PciIo instance of the parent controller.
**/
VOID
SioCreateDevice (
  IN  EFI_HANDLE                Controller,
  IN  EFI_SIO_ACPI_DEVICE_ID    *Device,
  IN  EFI_DEVICE_PATH_PROTOCOL  *ParentDevicePath,
  OUT EFI_PCI_IO_PROTOCOL       *PciIo
  )
{
  EFI_STATUS                Status;
  SIO_DEV                   *SioDev;

  DeviceEnable (Device);
  SioDev = AllocateCopyPool (sizeof (SIO_DEV), &mSioDevTemplate);
  ASSERT (SioDev != NULL);
  if (SioDev == NULL) {
    return;
  }
  InsertHeadList (&mSioDevPool, &SioDev->Link);

  SioDev->PciHandle       = Controller;

  CopyMem (&SioDev->Device, Device, sizeof (*Device));

  mAcpiNodeTemplate.HID = Device->HID;
  mAcpiNodeTemplate.UID = Device->UID;
  SioDev->DevicePath = AppendDevicePathNode (ParentDevicePath, (EFI_DEVICE_PATH_PROTOCOL *) &mAcpiNodeTemplate);
  ASSERT (SioDev->DevicePath != NULL);

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &SioDev->Handle,
                  &gEfiSioProtocolGuid,        &SioDev->Sio,
                  &gEfiDevicePathProtocolGuid, SioDev->DevicePath,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  mSioDriver.DriverBindingHandle,
                  SioDev->Handle,
                  EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                  );
  ASSERT_EFI_ERROR (Status);
}


/**
  Start this driver on ControllerHandle.

  @param[in]  This                 Protocol instance pointer.
  @param[in]  Controller           Handle of device to bind driver to
  @param[in]  RemainingDevicePath  Optional parameter use to pick a specific child
                                   device to start.

  @retval     EFI_SUCCESS          This driver is added to ControllerHandle
  @retval     EFI_ALREADY_STARTED  This driver is already running on ControllerHandle
  @retval     other                This driver does not support this device
**/
EFI_STATUS
EFIAPI
SioDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                          Status;
  EFI_PCI_IO_PROTOCOL                 *PciIo;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *ParentDevicePath;
  EFI_SIO_ACPI_DEVICE_ID              *Devices;
  SIO_DEV                             *SioDev;
  UINTN                               Count;
  UINTN                               Index;
  ACPI_HID_DEVICE_PATH                *AcpiNode;
  BOOLEAN                             *HasCreated;
  BOOLEAN                             *RequestCreate;
  LIST_ENTRY                          *Node;

  HasCreated    = NULL;
  RequestCreate = NULL;
  //
  // Get the ISA bridge's Device Path
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &ParentDevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status) && Status != EFI_ALREADY_STARTED) {
    return Status;
  }

  //
  // Get Pci IO
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (EFI_ERROR (Status) && Status != EFI_ALREADY_STARTED) {
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    return Status;
  }

  if ((RemainingDevicePath != NULL) && IsDevicePathEnd (RemainingDevicePath)) {
    return EFI_SUCCESS;
  }

  DeviceGetList (&Devices, &Count);
  if (Devices == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit_Start;
  }
  HasCreated    = AllocatePool (sizeof (BOOLEAN) * Count);
  ASSERT (HasCreated != NULL);
  if (HasCreated == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit_Start;
  }
  RequestCreate = AllocatePool (sizeof (BOOLEAN) * Count);
  ASSERT (RequestCreate != NULL);
  if (RequestCreate == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit_Start;
  }

  //
  // Assume no children has been created.
  // Assume the SIO interface hasn't been initialized.
  //
  ZeroMem (HasCreated, sizeof (BOOLEAN) * Count);

  if (Status == EFI_ALREADY_STARTED) {
    for (Node = GetFirstNode (&mSioDevPool);
         !IsNull (&mSioDevPool, Node); 
         Node = GetNextNode (&mSioDevPool, Node)
        ) {
      SioDev = CR (Node, SIO_DEV, Link, SIO_DEV_SIGNATURE);
      Status = gBS->HandleProtocol (
                      SioDev->PciHandle,
                      &gEfiDevicePathProtocolGuid,
                      (VOID **) &DevicePath
                      );
      ASSERT_EFI_ERROR (Status);

      //
      // See if they are under the same PCI to ISA Bridge
      //
      if (CompareMem (DevicePath, ParentDevicePath, GetDevicePathSize (DevicePath)) == 0) {
        for (Index = 0; Index < Count; Index++) {
          if (CompareMem (&SioDev->Device, &Devices[Index], sizeof (EFI_SIO_ACPI_DEVICE_ID)) == 0) {
            HasCreated[Index] = TRUE;
            break;
          }
        }
      }
    }
  }

  AcpiNode = (ACPI_HID_DEVICE_PATH *) RemainingDevicePath;
  for (Index = 0; Index < Count; Index++) {
    if ((AcpiNode == NULL) ||
        ((AcpiNode->HID == Devices[Index].HID) && (AcpiNode->UID == Devices[Index].UID))
       ) {
      RequestCreate[Index] = TRUE;
    } else {
      RequestCreate[Index] = FALSE;
    }
  }

  for (Index = 0; Index < Count; Index++) {
    if (RequestCreate[Index] && !HasCreated[Index]) {
      SioCreateDevice (Controller, &Devices[Index], ParentDevicePath, PciIo);
    }
  }
Exit_Start:
  if (Devices != NULL) {
    FreePool (Devices);
  }
  if (HasCreated != NULL) {
    FreePool (HasCreated);
  }
  if (RequestCreate != NULL) {
    FreePool (RequestCreate);
  }

  return Status;
}


/**
  Stop this driver on ControllerHandle.

  @param[in]  This              Protocol instance pointer.
  @param[in]  Controller        Handle of device to stop driver on
  @param[in]  NumberOfChildren  Number of Handles in ChildHandleBuffer. If number of
                                children is zero stop the entire bus driver.
  @param[in]  ChildHandleBuffer List of Child Handles to Stop.

  @retval     EFI_SUCCESS       This driver is removed ControllerHandle
  @retval     other             This driver was not removed from this device
**/
EFI_STATUS
EFIAPI
SioDriverStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  BOOLEAN     AllChildrenStopped;

  if (NumberOfChildren == 0) {
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    gBS->CloseProtocol (
           Controller,
           &gEfiPciIoProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    return EFI_SUCCESS;
  }

  AllChildrenStopped = TRUE;
  for (Index = 0; Index < NumberOfChildren; Index++) {
    Status = SioDestroyDevice (ChildHandleBuffer[Index]);
    if (EFI_ERROR (Status)) {
      AllChildrenStopped = FALSE;
    }
  }

  if (AllChildrenStopped) {
    return EFI_SUCCESS;
  } else {
    return EFI_DEVICE_ERROR;
  }
}
