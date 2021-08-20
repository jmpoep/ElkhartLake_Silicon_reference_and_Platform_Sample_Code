/** @file

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

#include "IntelRaidBiosThunk.h"

//
// Global data declaration
//
//
// EFI Driver Binding Protocol Instance
// Driver version need be higher than AtaBus driver, in RAID mode,
// it need open AtaPassThru protocol by driver before AtaBus driver.
//
EFI_DRIVER_BINDING_PROTOCOL gIntelRaidBiosThunkDriverBinding = {
  IntelRaidBiosThunkDriverBindingSupported,
  IntelRaidBiosThunkDriverBindingStart,
  IntelRaidBiosThunkDriverBindingStop,
  0x11,
  NULL,
  NULL
};

//
// Semaphore to control access to global variables mActiveInstances and mBufferUnder1Mb
//
EFI_LOCK                    mGlobalDataLock = EFI_INITIALIZE_LOCK_VARIABLE(TPL_APPLICATION);

//
// Number of active instances of this protocol.  This is used to allocate/free
// the shared buffer.  You must acquire the semaphore to modify.
//
UINTN                       mActiveInstances = 0;

//
// Pointer to the beginning of the buffer used for real mode thunk
// You must acquire the semaphore to modify.
//
EFI_PHYSICAL_ADDRESS        mBufferUnder1Mb = 0;

//
// Address packet is a buffer under 1 MB for all version EDD calls
//
EDD_DEVICE_ADDRESS_PACKET   *mEddBufferUnder1Mb;

//
// This is a buffer for INT 13h func 48 information
//
BIOS_LEGACY_DRIVE           *mLegacyDriverUnder1Mb;

//
// Buffer of 0xFE00 bytes for EDD 1.1 transfer must be under 1 MB
//  0xFE00 bytes is the max transfer size supported.
//
VOID                        *mEdd11Buffer;

/**
  Driver entry point.

  @param  ImageHandle  Handle of driver image.
  @param  SystemTable  Pointer to system table.

  @retval EFI_SUCCESS  Entrypoint successfully executed.
  @retval Others       Fail to execute entrypoint.

**/
EFI_STATUS
EFIAPI
IntelRaidBiosThunkDriverEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;

  //
  // Install protocols
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gIntelRaidBiosThunkDriverBinding,
             ImageHandle,
             &gIntelRaidBiosThunkComponentName,
             &gIntelRaidBiosThunkComponentName2
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Install Legacy BIOS GUID to mark this driver as a BIOS Thunk Driver
  //
  return gBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiLegacyBiosGuid,
                NULL,
                NULL
                );
}

/**
  Check whether the driver supports this device.

  @param  This                   The Udriver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
IntelRaidBiosThunkDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS                  Status;
  EFI_LEGACY_BIOS_PROTOCOL    *LegacyBios;
  EFI_PCI_IO_PROTOCOL         *PciIo;
  EFI_ATA_PASS_THRU_PROTOCOL  *AtaPassThru;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  PCI_TYPE00                  Pci;

  //
  // See if the Legacy BIOS Protocol is available
  //
  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiAtaPassThruProtocolGuid,
                  (VOID **) &AtaPassThru,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    goto Done;
  }  
  
  //
  // Open the IO Abstraction(s) needed to perform the supported test
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // See if this is a PCI VGA Controller by looking at the Command register and
  // Class Code Register
  //
  Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint32, 0, sizeof (Pci) / sizeof (UINT32), &Pci);
  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
    goto Done;
  }

  Status = EFI_UNSUPPORTED;
  if ((Pci.Hdr.ClassCode[2] == PCI_CLASS_MASS_STORAGE) && 
      (Pci.Hdr.ClassCode[1] == PCI_CLASS_MASS_STORAGE_RAID)) {
    Status = EFI_SUCCESS;
  }

Done:
  gBS->CloseProtocol (
        Controller,
        &gEfiAtaPassThruProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  return Status;
}

/**
  Starts the device with this driver.

  @param  This                   The driver binding instance.
  @param  Controller             Handle of device to bind driver to.
  @param  RemainingDevicePath    Optional parameter use to pick a specific child
                                 device to start.

  @retval EFI_SUCCESS            The controller is controlled by the driver.
  @retval Other                  This controller cannot be started.

**/
EFI_STATUS
EFIAPI
IntelRaidBiosThunkDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  UINT8                     DiskStart;
  UINT8                     DiskEnd;
  BIOS_BLOCK_IO_DEV         *BiosBlockIoPrivate;
  EFI_DEVICE_PATH_PROTOCOL  *PciDevPath;
  UINTN                     Index;
  UINTN                     Flags;
  UINTN                     TmpAddress;
  EFI_ATA_PASS_THRU_PROTOCOL *AtaPassThru;
  EFI_ATA_PASS_THRU_PROTOCOL *ChildAtaPassThru;
  EFI_HANDLE                 Handle;

  //
  // Initialize variables
  //
  AtaPassThru = NULL;
  PciDevPath  = NULL;
  
  //
  // See if the Legacy BIOS Protocol is available
  //
  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiAtaPassThruProtocolGuid,
                  (VOID **) &AtaPassThru,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open the IO Abstraction(s) needed
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &PciDevPath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    goto Error;
  }

  //
  // Produce DiskInfo for every physical ATA HDD devices
  //
  DiskInfoForPhyDev (Controller, This->DriverBindingHandle, AtaPassThru, PciDevPath);
  
  //
  // Check to see if there is a legacy option ROM image associated with this PCI device
  //
  Status = LegacyBios->CheckPciRom (
                        LegacyBios,
                        Controller,
                        NULL,
                        NULL,
                        &Flags
                        );
  if (EFI_ERROR (Status)) {
    goto Error;
  }
  //
  // Post the legacy option ROM if it is available.
  //
  Status = LegacyBios->InstallPciRom (
                        LegacyBios,
                        Controller,
                        NULL,
                        &Flags,
                        &DiskStart,
                        &DiskEnd,
                        NULL,
                        NULL
                        );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Handle = 0;
  gBS->InstallProtocolInterface (
               &Handle,
               &gEfiHddPasswordNotifyProtocolGuid,
               EFI_NATIVE_INTERFACE,
               NULL
               );
  
  //
  // All instances share a buffer under 1MB to put real mode thunk code in
  // If it has not been allocated, then we allocate it.
  //
  if (mBufferUnder1Mb == 0) {
    //
    // Should only be here if there are no active instances
    //
    ASSERT (mActiveInstances == 0);

    //
    // Acquire the lock
    //
    EfiAcquireLock (&mGlobalDataLock);

    //
    // Allocate below 1MB
    //
    mBufferUnder1Mb = 0x00000000000FFFFF;
    Status          = gBS->AllocatePages (AllocateMaxAddress, EfiBootServicesData, BLOCK_IO_BUFFER_PAGE_SIZE, &mBufferUnder1Mb);

    //
    // Release the lock
    //
    EfiReleaseLock (&mGlobalDataLock);

    //
    // Check memory allocation success
    //
    if (EFI_ERROR (Status)) {
      //
      // In checked builds we want to assert if the allocate failed.
      //
      ASSERT_EFI_ERROR (Status);
      Status          = EFI_OUT_OF_RESOURCES;
      mBufferUnder1Mb = 0;
      goto Error;
    }

    TmpAddress = (UINTN) mBufferUnder1Mb;
    //
    // Adjusting the value to be on proper boundary
    //
    mEdd11Buffer = (VOID *) ALIGN_VARIABLE (TmpAddress);

    TmpAddress   = (UINTN) mEdd11Buffer + MAX_EDD11_XFER;
    //
    // Adjusting the value to be on proper boundary
    //
    mLegacyDriverUnder1Mb = (BIOS_LEGACY_DRIVE *) ALIGN_VARIABLE (TmpAddress);

    TmpAddress = (UINTN) mLegacyDriverUnder1Mb + sizeof (BIOS_LEGACY_DRIVE);
    //
    // Adjusting the value to be on proper boundary
    //
    mEddBufferUnder1Mb = (EDD_DEVICE_ADDRESS_PACKET *) ALIGN_VARIABLE (TmpAddress);
  }
  //
  // Allocate the private device structure for each disk
  //
  for (Index = DiskStart; Index < DiskEnd; Index++) {

    Status = gBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (BIOS_BLOCK_IO_DEV),
                    (VOID **) &BiosBlockIoPrivate
                    );
    if (EFI_ERROR (Status)) {
      goto Error;
    }
    //
    // Zero the private device structure
    //
    ZeroMem (BiosBlockIoPrivate, sizeof (BIOS_BLOCK_IO_DEV));

    //
    // Initialize the private device structure
    //
    BiosBlockIoPrivate->Signature                 = BIOS_CONSOLE_BLOCK_IO_DEV_SIGNATURE;
    BiosBlockIoPrivate->ControllerHandle          = Controller;
    BiosBlockIoPrivate->LegacyBios                = LegacyBios;
    BiosBlockIoPrivate->PciIo                     = PciIo;

    BiosBlockIoPrivate->Bios.Floppy               = FALSE;
    BiosBlockIoPrivate->Bios.Number               = (UINT8) Index;
    BiosBlockIoPrivate->Bios.Letter               = (UINT8) (Index - 0x80 + 'C');
    BiosBlockIoPrivate->BlockMedia.RemovableMedia = FALSE;

    if (BiosInitBlockIo (BiosBlockIoPrivate)) {
      SetBiosInitBlockIoDevicePath (PciDevPath, &BiosBlockIoPrivate->Bios, &BiosBlockIoPrivate->DevicePath);

      //
      // Install the Block Io Protocol onto a new child handle. It's only for logical device.
      //
      Status = gBS->InstallMultipleProtocolInterfaces (
                      &BiosBlockIoPrivate->Handle,
                      &gEfiBlockIoProtocolGuid,
                      &BiosBlockIoPrivate->BlockIo,
                      &gEfiDevicePathProtocolGuid,
                      BiosBlockIoPrivate->DevicePath,
                      NULL
                      );
      if (EFI_ERROR (Status)) {
        gBS->FreePool (BiosBlockIoPrivate);
      }
      //
      // Open For Child Device
      //
      Status = gBS->OpenProtocol (
                      Controller,
                      &gEfiAtaPassThruProtocolGuid,
                      (VOID **) &ChildAtaPassThru,
                      This->DriverBindingHandle,
                      BiosBlockIoPrivate->Handle,
                      EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                      );

    } else {
      gBS->FreePool (BiosBlockIoPrivate);
    }
  }

Error:
  if (EFI_ERROR (Status)) {
    if (AtaPassThru != NULL) {
      gBS->CloseProtocol (
            Controller,
            &gEfiAtaPassThruProtocolGuid,
            This->DriverBindingHandle,
            Controller
            );

      if (mBufferUnder1Mb != 0 && mActiveInstances == 0) {
        gBS->FreePages (mBufferUnder1Mb, BLOCK_IO_BUFFER_PAGE_SIZE);

        //
        // Clear the buffer back to 0
        //
        EfiAcquireLock (&mGlobalDataLock);
        mBufferUnder1Mb = 0;
        EfiReleaseLock (&mGlobalDataLock);
      }
    }
  } else {
    //
    // Successfully installed, so increment the number of active instances
    //
    EfiAcquireLock (&mGlobalDataLock);
    mActiveInstances++;
    EfiReleaseLock (&mGlobalDataLock);
  }

  return Status;
}

/**
  Stop the device handled by this driver.

  @param  This                   The driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_DEVICE_ERROR       The device could not be stopped due to a device error.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
IntelRaidBiosThunkDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer
  )
{
  EFI_STATUS             Status;
  BOOLEAN                AllChildrenStopped;
  EFI_BLOCK_IO_PROTOCOL  *BlockIo;
  EFI_DISK_INFO_PROTOCOL *DiskInfo;
  BIOS_BLOCK_IO_DEV      *BiosBlockIoPrivate;
  UINTN                  Index;
  ATA_DEVICE             *AtaDevice;

  //
  // Decrement the number of active instances
  //
  if (mActiveInstances != 0) {
    //
    // Add a check since the stop function will be called 2 times for each handle
    //
    EfiAcquireLock (&mGlobalDataLock);
    mActiveInstances--;
    EfiReleaseLock (&mGlobalDataLock);
  }

  if ((mActiveInstances == 0) && (mBufferUnder1Mb != 0)) {
    //
    // Free our global buffer
    //
    Status = gBS->FreePages (mBufferUnder1Mb, BLOCK_IO_BUFFER_PAGE_SIZE);
    ASSERT_EFI_ERROR (Status);

    EfiAcquireLock (&mGlobalDataLock);
    mBufferUnder1Mb = 0;
    EfiReleaseLock (&mGlobalDataLock);
  }

  AllChildrenStopped = TRUE;

  for (Index = 0; Index < NumberOfChildren; Index++) {
    Status = gBS->OpenProtocol (
                    ChildHandleBuffer[Index],
                    &gEfiDiskInfoProtocolGuid,
                    (VOID **) &DiskInfo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (!EFI_ERROR (Status)) {
      //
      // The child handle is only for physical device. Release Device Path and Disk Info protocols on the child handle.
      //
      AtaDevice = ATA_DEVICE_FROM_DISK_INFO (DiskInfo);
      
      gBS->CloseProtocol (
            Controller,
            &gEfiAtaPassThruProtocolGuid,
            This->DriverBindingHandle,
            ChildHandleBuffer[Index]
            );

      Status = gBS->UninstallMultipleProtocolInterfaces (
                      ChildHandleBuffer[Index],
                      &gEfiDiskInfoProtocolGuid,
                      &AtaDevice->DiskInfo,
                      &gEfiDevicePathProtocolGuid,
                      AtaDevice->DevicePath,
                      NULL
                      );
      ASSERT_EFI_ERROR (Status);
      if (EFI_ERROR (Status)) {
        AllChildrenStopped = FALSE;
      }
      
      if (AtaDevice->Asb != NULL) {
        FreePages (AtaDevice->Asb, EFI_SIZE_TO_PAGES (sizeof (EFI_ATA_STATUS_BLOCK)));
      }
      
      if (AtaDevice->IdentifyData != NULL) {
        FreePages (AtaDevice->IdentifyData, EFI_SIZE_TO_PAGES (sizeof (ATA_IDENTIFY_DATA)));
      }
      
      if (AtaDevice->DevicePath != NULL) {
        FreePool (AtaDevice->DevicePath);
      }
      
      FreePool (AtaDevice);
    } else {
      Status = gBS->OpenProtocol (
                      ChildHandleBuffer[Index],
                      &gEfiBlockIoProtocolGuid,
                      (VOID **) &BlockIo,
                      This->DriverBindingHandle,
                      Controller,
                      EFI_OPEN_PROTOCOL_GET_PROTOCOL
                      );
      if (!EFI_ERROR (Status)) {
        //
        // The child handle is only for logical device.
        // 
        BiosBlockIoPrivate = BIOS_BLOCK_IO_FROM_THIS (BlockIo);
        gBS->CloseProtocol (
              Controller,
              &gEfiAtaPassThruProtocolGuid,
              This->DriverBindingHandle,
              ChildHandleBuffer[Index]
              );

        //
        // Release Device Path and Block IO Protocols on the child handle.
        //
        Status = gBS->UninstallMultipleProtocolInterfaces (
                        ChildHandleBuffer[Index],
                        &gEfiBlockIoProtocolGuid,
                        &BiosBlockIoPrivate->BlockIo,
                        &gEfiDevicePathProtocolGuid,
                        BiosBlockIoPrivate->DevicePath,
                        NULL
                        );
        if (EFI_ERROR (Status)) {
          AllChildrenStopped = FALSE;
        }

        gBS->FreePool (BiosBlockIoPrivate);
      }
    }
  }

  if (!AllChildrenStopped) {
    return EFI_DEVICE_ERROR;
  }

  Status = gBS->CloseProtocol (
                  Controller,
                  &gEfiAtaPassThruProtocolGuid,
                  This->DriverBindingHandle,
                  Controller
                  );

  return EFI_SUCCESS;
}

/**
  Build device path for device.

  @param  BaseDevicePath         Base device path.
  @param  Drive                  Legacy drive.
  @param  DevicePath             Device path for output.

**/
VOID
SetBiosInitBlockIoDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL  *BaseDevicePath,
  IN  BIOS_LEGACY_DRIVE         *Drive,
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath
  )
{
  EFI_STATUS                        Status;
  UNKNOWN_DEVICE_VENDOR_DEVICE_PATH VendorNode;
  
  Status = EFI_UNSUPPORTED;
  
  //
  // BugBug: Check for memory leaks!
  //
  if (Drive->EddVersion == EDD_VERSION_30) {
    //
    // EDD 3.0 case.
    //
    Status = BuildEdd30DevicePath (BaseDevicePath, Drive, DevicePath);
  }
  
  if (EFI_ERROR (Status)) {
    //
    // EDD 1.1 device case or it is unrecognized EDD 3.0 device
    //
    ZeroMem (&VendorNode, sizeof (VendorNode));
    VendorNode.DevicePath.Header.Type     = HARDWARE_DEVICE_PATH;
    VendorNode.DevicePath.Header.SubType  = HW_VENDOR_DP;
    SetDevicePathNodeLength (&VendorNode.DevicePath.Header, sizeof (VendorNode));
    CopyMem (&VendorNode.DevicePath.Guid, &gBlockIoVendorGuid, sizeof (EFI_GUID));
    VendorNode.LegacyDriveLetter  = Drive->Number;
    *DevicePath                   = AppendDevicePathNode (BaseDevicePath, &VendorNode.DevicePath.Header);
  }
}

/**
  Build device path for EDD 3.0.

  @param  BaseDevicePath         Base device path.
  @param  Drive                  Legacy drive.
  @param  DevicePath             Device path for output.

  @retval EFI_SUCCESS            The device path is built successfully.
  @retval EFI_UNSUPPORTED        It is failed to built device path.

**/
EFI_STATUS
BuildEdd30DevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL  *BaseDevicePath,
  IN  BIOS_LEGACY_DRIVE         *Drive,
  IN  EFI_DEVICE_PATH_PROTOCOL  **DevicePath
  )
{
  //
  // AVL    UINT64                  Address;
  // AVL    EFI_HANDLE              Handle;
  //
  EFI_DEV_PATH  Node;
  UINT32        Controller;

  Controller = (UINT32) Drive->Parameters.InterfacePath.Pci.Controller;

  ZeroMem (&Node, sizeof (Node));
  if ((AsciiStrnCmp ("ATAPI", Drive->Parameters.InterfaceType, 5) == 0) ||
      (AsciiStrnCmp ("ATA", Drive->Parameters.InterfaceType, 3) == 0)
      ) {
    //
    // ATA or ATAPI drive found
    //
    Node.Atapi.Header.Type    = MESSAGING_DEVICE_PATH;
    Node.Atapi.Header.SubType = MSG_ATAPI_DP;
    SetDevicePathNodeLength (&Node.Atapi.Header, sizeof (ATAPI_DEVICE_PATH));
    Node.Atapi.SlaveMaster      = Drive->Parameters.DevicePath.Atapi.Master;
    Node.Atapi.Lun              = Drive->Parameters.DevicePath.Atapi.Lun;
    Node.Atapi.PrimarySecondary = (UINT8) Controller;
  } else {
    //
    // Not an ATA/ATAPI drive
    //
    if (Controller != 0) {
      ZeroMem (&Node, sizeof (Node));
      Node.Controller.Header.Type      = HARDWARE_DEVICE_PATH;
      Node.Controller.Header.SubType   = HW_CONTROLLER_DP;
      SetDevicePathNodeLength (&Node.Controller.Header, sizeof (CONTROLLER_DEVICE_PATH));
      Node.Controller.ControllerNumber = Controller;
      *DevicePath                      = AppendDevicePathNode (*DevicePath, &Node.DevPath);
    }

    ZeroMem (&Node, sizeof (Node));

    if (AsciiStrnCmp ("SCSI", Drive->Parameters.InterfaceType, 4) == 0) {
      //
      // SCSI drive
      //
      Node.Scsi.Header.Type     = MESSAGING_DEVICE_PATH;
      Node.Scsi.Header.SubType  = MSG_SCSI_DP;
      SetDevicePathNodeLength (&Node.Scsi.Header, sizeof (SCSI_DEVICE_PATH));

      //
      // Lun is miss aligned in both EDD and Device Path data structures.
      //  thus we do a byte copy, to prevent alignment traps on IA-64.
      //
      CopyMem (&Node.Scsi.Lun, &Drive->Parameters.DevicePath.Scsi.Lun, sizeof (UINT16));
      Node.Scsi.Pun = Drive->Parameters.DevicePath.Scsi.Pun;

    } else if (AsciiStrnCmp ("USB", Drive->Parameters.InterfaceType, 3) == 0) {
      //
      // USB drive
      //
      Node.Usb.Header.Type    = MESSAGING_DEVICE_PATH;
      Node.Usb.Header.SubType = MSG_USB_DP;
      SetDevicePathNodeLength (&Node.Usb.Header, sizeof (USB_DEVICE_PATH));
      Node.Usb.ParentPortNumber = (UINT8) Drive->Parameters.DevicePath.Usb.Reserved;

    } else if (AsciiStrnCmp ("1394", Drive->Parameters.InterfaceType, 4) == 0) {
      //
      // 1394 drive
      //
      Node.F1394.Header.Type    = MESSAGING_DEVICE_PATH;
      Node.F1394.Header.SubType = MSG_1394_DP;
      SetDevicePathNodeLength (&Node.F1394.Header, sizeof (F1394_DEVICE_PATH));
      Node.F1394.Guid = Drive->Parameters.DevicePath.FireWire.Guid;

    } else if (AsciiStrnCmp ("FIBRE", Drive->Parameters.InterfaceType, 5) == 0) {
      //
      // Fibre drive
      //
      Node.FibreChannel.Header.Type     = MESSAGING_DEVICE_PATH;
      Node.FibreChannel.Header.SubType  = MSG_FIBRECHANNEL_DP;
      SetDevicePathNodeLength (&Node.FibreChannel.Header, sizeof (FIBRECHANNEL_DEVICE_PATH));
      Node.FibreChannel.WWN = Drive->Parameters.DevicePath.FibreChannel.Wwn;
      Node.FibreChannel.Lun = Drive->Parameters.DevicePath.FibreChannel.Lun;

    } else {
      DEBUG (
        (
        DEBUG_BLKIO, "It is unrecognized EDD 3.0 device, Drive Number = %x, InterfaceType = %s\n",
        Drive->Number,
        Drive->Parameters.InterfaceType
        )
        );      
    }
  }

  if (Node.DevPath.Type == 0) {
    return EFI_UNSUPPORTED;
  }
  
  *DevicePath = AppendDevicePathNode (BaseDevicePath, &Node.DevPath);
  return EFI_SUCCESS;
}
