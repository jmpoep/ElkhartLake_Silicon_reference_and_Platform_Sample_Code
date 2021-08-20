/** @file

  Produce DiskInfo protocol for every attached RAID ATA HDD devices.

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

#include "IntelUefiRaidDiskInfo.h"

VOID
UninstallOrphanDiskInfoProtocol (
  VOID
  );

//
// Global data declaration
//
//
// EFI Driver Binding Protocol Instance
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL gIntelUefiRaidDiskInfoDriverBinding = {
  IntelUefiRaidDiskInfoDriverBindingSupported,
  IntelUefiRaidDiskInfoDriverBindingStart,
  IntelUefiRaidDiskInfoDriverBindingStop,
  0x01,
  NULL,
  NULL
};

//
// Template for SATA device path.
//
GLOBAL_REMOVE_IF_UNREFERENCED SATA_DEVICE_PATH    mSataDevicePathTemplate = {
  {
    MESSAGING_DEVICE_PATH,
    MSG_SATA_DP,
    {
      (UINT8) (sizeof (SATA_DEVICE_PATH)),
      (UINT8) ((sizeof (SATA_DEVICE_PATH)) >> 8)
    }
  },
  0,
  0,
  0
};

//
// Template for ATA Hdd Device.
//
GLOBAL_REMOVE_IF_UNREFERENCED ATA_DEVICE mAtaDeviceTemplate = {
  ATA_DEVICE_SIGNATURE,        // Signature
  {
    NULL,                      // Link
    NULL
  },
  NULL,                        // Handle
  {                            // DiskInfo
    EFI_DISK_INFO_RAID_INTERFACE_GUID,
    AtaDiskInfoInquiry,
    AtaDiskInfoIdentify,
    AtaDiskInfoSenseData,
    AtaDiskInfoWhichIde
  },
  NULL,                        // DevicePath
  0,                           // Port
  0,                           // PortMultiplierPort
  { 0, },                      // Packet
  {{ 0}, },                    // Acb
  NULL,                        // Asb
  NULL                         // IdentifyData
};


/**
  Wrapper for EFI_ATA_PASS_THRU_PROTOCOL.PassThru().

  This function wraps the PassThru() invocation for ATA pass through function
  for an ATA device. It assembles the ATA pass through command packet for ATA
  transaction.

  @param  AtaDevice         The ATA child device involved for the operation.

  @return The return status from EFI_ATA_PASS_THRU_PROTOCOL.PassThru().

**/
EFI_STATUS
AtaDevicePassThru (
  IN OUT ATA_DEVICE                       *AtaDevice,
  IN     EFI_ATA_PASS_THRU_PROTOCOL       *AtaPassThru
  )
{
  EFI_STATUS                              Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET        *Packet;

  //
  // Assemble packet
  //
  Packet = &AtaDevice->Packet;
  Packet->Asb = AtaDevice->Asb;
  Packet->Acb = &AtaDevice->Acb;
  Packet->Timeout = ATA_TIMEOUT;

  Status = AtaPassThru->PassThru (
                          AtaPassThru,
                          AtaDevice->Port,
                          AtaDevice->PortMultiplierPort,
                          Packet,
                          NULL
                          );
  //
  // Ensure ATA pass through caller and callee have the same
  // interpretation of ATA pass through protocol.
  //
  ASSERT (Status != EFI_INVALID_PARAMETER);
  ASSERT (Status != EFI_BAD_BUFFER_SIZE);

  return Status;
}


/**
  Identifies ATA device via the Identify data.

  This function identifies the ATA device and initializes the Media information in
  Block IO protocol interface.

  @param  AtaDevice         The ATA child device involved for the operation.

  @retval EFI_UNSUPPORTED   The device is not a valid ATA device (hard disk).
  @retval EFI_SUCCESS       The device is successfully identified and Media information
                            is correctly initialized.

**/
EFI_STATUS
IdentifyAtaDevice (
  IN OUT ATA_DEVICE                 *AtaDevice
  )
{
  ATA_IDENTIFY_DATA                 *IdentifyData;

  IdentifyData = AtaDevice->IdentifyData;

  if ((IdentifyData->config & BIT15) != 0) {
    //
    // This is not an hard disk
    //
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


/**
  Discovers whether it is a valid ATA device.

  This function issues ATA_CMD_IDENTIFY_DRIVE command to the ATA device to identify it.
  If the command is executed successfully, it then identifies it and initializes
  the Media information in Block IO protocol interface.

  @param  AtaDevice         The ATA child device involved for the operation.

  @retval EFI_SUCCESS       The device is successfully identified and Media information
                            is correctly initialized.
  @return others            Some error occurs when discovering the ATA device.

**/
EFI_STATUS
DiscoverAtaDevice (
  IN OUT ATA_DEVICE                 *AtaDevice,
  IN     EFI_ATA_PASS_THRU_PROTOCOL *AtaPassThru
  )
{
  EFI_STATUS                        Status;
  EFI_ATA_COMMAND_BLOCK             *Acb;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  *Packet;
  UINTN                             Retry;

  //
  // Prepare for ATA command block.
  //
  Acb = ZeroMem (&AtaDevice->Acb, sizeof (*Acb));
  Acb->AtaCommand = ATA_CMD_IDENTIFY_DRIVE;
  Acb->AtaDeviceHead = (UINT8) (BIT7 | BIT6 | BIT5 | (AtaDevice->PortMultiplierPort << 4));

  //
  // Prepare for ATA pass through packet.
  //
  Packet = ZeroMem (&AtaDevice->Packet, sizeof (EFI_ATA_PASS_THRU_COMMAND_PACKET));
  Packet->InDataBuffer = AtaDevice->IdentifyData;
  Packet->InTransferLength = sizeof (ATA_IDENTIFY_DATA);
  Packet->Protocol = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet->Length = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;

  Retry = 3;
  do {
    Status = AtaDevicePassThru (AtaDevice, AtaPassThru);
    if (!EFI_ERROR (Status)) {
      //
      // The command is issued successfully
      //
      Status = IdentifyAtaDevice (AtaDevice);
      if (!EFI_ERROR (Status)) {
        return Status;
      }
    }
  } while (Retry-- > 0);

  return Status;
}


/**
  Provides inquiry information for the controller type.

  This function is used by the IDE bus driver to get inquiry data.  Data format
  of Identify data is defined by the Interface GUID.

  @param[in]      This             Pointer to the EFI_DISK_INFO_PROTOCOL instance.
  @param[in, out] InquiryData      Pointer to a buffer for the inquiry data.
  @param[in, out] InquiryDataSize  Pointer to the value for the inquiry data size.

  @retval EFI_SUCCESS            The command was accepted without any errors.
  @retval EFI_NOT_FOUND          Device does not support this data class
  @retval EFI_DEVICE_ERROR       Error reading InquiryData from device
  @retval EFI_BUFFER_TOO_SMALL   InquiryDataSize not big enough

**/
EFI_STATUS
EFIAPI
AtaDiskInfoInquiry (
  IN     EFI_DISK_INFO_PROTOCOL   *This,
  IN OUT VOID                     *InquiryData,
  IN OUT UINT32                   *InquiryDataSize
  )
{
  return EFI_NOT_FOUND;
}


/**
  Provides identify information for the controller type.

  This function is used by the IDE bus driver to get identify data.  Data format
  of Identify data is defined by the Interface GUID.

  @param[in]      This              Pointer to the EFI_DISK_INFO_PROTOCOL
                                    instance.
  @param[in, out] IdentifyData      Pointer to a buffer for the identify data.
  @param[in, out] IdentifyDataSize  Pointer to the value for the identify data
                                    size.

  @retval EFI_SUCCESS            The command was accepted without any errors.
  @retval EFI_NOT_FOUND          Device does not support this data class
  @retval EFI_DEVICE_ERROR       Error reading IdentifyData from device
  @retval EFI_BUFFER_TOO_SMALL   IdentifyDataSize not big enough

**/
EFI_STATUS
EFIAPI
AtaDiskInfoIdentify (
  IN     EFI_DISK_INFO_PROTOCOL   *This,
  IN OUT VOID                     *IdentifyData,
  IN OUT UINT32                   *IdentifyDataSize
  )
{
  EFI_STATUS                      Status;
  ATA_DEVICE                      *AtaDevice;

  AtaDevice = ATA_DEVICE_FROM_DISK_INFO (This);

  Status = EFI_BUFFER_TOO_SMALL;
  if (*IdentifyDataSize >= sizeof (*AtaDevice->IdentifyData)) {
    Status = EFI_SUCCESS;
    CopyMem (IdentifyData, AtaDevice->IdentifyData, sizeof (*AtaDevice->IdentifyData));
  }
  *IdentifyDataSize = sizeof (*AtaDevice->IdentifyData);

  return Status;
}


/**
  Provides sense data information for the controller type.

  This function is used by the IDE bus driver to get sense data.
  Data format of Sense data is defined by the Interface GUID.

  @param[in]      This             Pointer to the EFI_DISK_INFO_PROTOCOL instance.
  @param[in, out] SenseData        Pointer to the SenseData.
  @param[in, out] SenseDataSize    Size of SenseData in bytes.
  @param[out]     SenseDataNumber  Pointer to the value for the sense data size.

  @retval EFI_SUCCESS            The command was accepted without any errors.
  @retval EFI_NOT_FOUND          Device does not support this data class.
  @retval EFI_DEVICE_ERROR       Error reading SenseData from device.
  @retval EFI_BUFFER_TOO_SMALL   SenseDataSize not big enough.

**/
EFI_STATUS
EFIAPI
AtaDiskInfoSenseData (
  IN     EFI_DISK_INFO_PROTOCOL   *This,
  IN OUT VOID                     *SenseData,
  IN OUT UINT32                   *SenseDataSize,
  OUT    UINT8                    *SenseDataNumber
  )
{
  return EFI_NOT_FOUND;
}


/**
  This function is used by the IDE bus driver to get controller information.

  @param[in]  This         Pointer to the EFI_DISK_INFO_PROTOCOL instance.
  @param[out] IdeChannel   Pointer to the Ide Channel number.  Primary or secondary.
  @param[out] IdeDevice    Pointer to the Ide Device number.  Master or slave.

  @retval EFI_SUCCESS       IdeChannel and IdeDevice are valid.
  @retval EFI_UNSUPPORTED   This is not an IDE device.

**/
EFI_STATUS
EFIAPI
AtaDiskInfoWhichIde (
  IN  EFI_DISK_INFO_PROTOCOL   *This,
  OUT UINT32                   *IdeChannel,
  OUT UINT32                   *IdeDevice
  )
{
  ATA_DEVICE                   *AtaDevice;

  AtaDevice       = ATA_DEVICE_FROM_DISK_INFO (This);
  *IdeChannel     = AtaDevice->Port;
  *IdeDevice      = AtaDevice->PortMultiplierPort;

  return EFI_SUCCESS;
}

/**
  Get the remaining devicepath if two devicepaths have the same prefix devicepath.

  @param[in]      ParentDevicePath      Pointer to parent devicepath.
  @param[in]      DevicePath            Pointer to object devicepath.
  @param[in, out] RemainingDevicePath   Pointer to return the remaining devicepath.

  @retval EFI_SUCCESS                   The same prefix devicepath, and return valid remaining devicepath.
  @retval EFI_UNSUPPORTED               Prefix devicepath is not the same, and doesn't .

**/
EFI_STATUS
GetRemainingDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL           *ParentDevicePath,
  IN EFI_DEVICE_PATH_PROTOCOL           *DevicePath,
  IN EFI_DEVICE_PATH_PROTOCOL           **RemainingDevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL              *ParentDevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePathNode;
  UINTN                                 NodeLength;

  ParentDevicePathNode = ParentDevicePath;
  DevicePathNode       = DevicePath;

  while (!IsDevicePathEndType (ParentDevicePathNode)) {
    if (IsDevicePathEndType (DevicePathNode)) {
      return EFI_UNSUPPORTED;
    }

    NodeLength = DevicePathNodeLength (ParentDevicePathNode);
    if (CompareMem (ParentDevicePathNode, DevicePathNode, NodeLength)) {
      return EFI_UNSUPPORTED;
    }

    ParentDevicePathNode = NextDevicePathNode (ParentDevicePathNode);
    DevicePathNode       = NextDevicePathNode (DevicePathNode);
  }

  if (IsDevicePathEndType (DevicePathNode)) {
    return EFI_UNSUPPORTED;
  }

  *RemainingDevicePath = DevicePathNode;

  return EFI_SUCCESS;
}


/**
  Registers an ATA HDD device.

  There are three cases to install the DiskInfo protocol.
  1. For Raid disks, DiskInfo driver will new the individual device path for each disk and
      install the DiskInfo protocol on the handle.
  2. For non-Raid disks, DiskInfo driver will install the DiskInfo protocol on the corresponding
      device path handle.
  3. For the disk that is hidden by RAID driver, DiskInfo driver will new a device path for it,
      and install DiskInfo protocol on the handle. (In the edge case that the RST cache disk.)

  @param  AtaBusDriverData      The parent ATA bus driver data structure.
  @param  Port                  The port number of the ATA device.
  @param  PortMultiplierPort    The port multiplier port number of the ATA device.

  @retval EFI_SUCCESS           The ATA device is successfully registered.
  @retval EFI_OUT_OF_RESOURCES  There is not enough memory to allocate the ATA device
                                and related data structures.
  @return Others                Some error occurs when registering the ATA device.
**/
EFI_STATUS
RegisterAtaHddDevice (
  IN EFI_HANDLE                     Controller,
  IN EFI_HANDLE                     DriverBinding,
  IN EFI_ATA_PASS_THRU_PROTOCOL     *AtaPassThru,
  IN EFI_DEVICE_PATH_PROTOCOL       *ParentDevicePath,
  IN UINT16                         Port,
  IN UINT16                         PortMultiplierPort
  )
{
  EFI_STATUS                        Status;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *NewDevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePathNode;
  SATA_DEVICE_PATH                  *SataDevicePathNode;
  EFI_HANDLE                        DeviceHandle;
  ATA_DEVICE                        *AtaDevice;
  EFI_DISK_INFO_PROTOCOL            *DiskInfo;
  UINTN                             HandleCount;
  EFI_HANDLE                        *HandleBuffer;
  UINTN                             Index;

  AtaDevice           = NULL;
  DiskInfo            = NULL;
  DevicePath          = NULL;
  RemainingDevicePath = NULL;
  NewDevicePathNode   = NULL;

  HandleCount         = 0;
  HandleBuffer        = NULL;
  DeviceHandle        = NULL;

  //
  // The UEFI RAID driver produces only one Sata device path for the Raid Disks,
  // which the HBAPortNumber is the bitmap for the sata ports.
  // For example, if there are three disks on port0,1,4 with RAID 5, then Raid driver
  // creates DP with HBAPortNumber as 0x13 (bit0, bit1, bit4) and the PortMultiplierPortNumber
  // as 0x8000 (bit15). (In this case, more than one bits are set in HBAPortNumber.)
  // On the other hand, the UEFI RAID driver also produces the Sata device path
  // for each non-Raid disk, and set the HBAPortNumber as bitmap for the port.
  // For example, if there are two non-Raid disks on port0 and port1, then Raid driver
  // creates the HBAPortNumber as 0x01 (bit0) for port0, and HBAPortNumber as 0x02 (bit1)
  // for port1. Also set the PortMultiplierPortNumber as 0x8000 (bit15).
  // (In this case, only one bit is set in HBAPortNumber.)
  //
  // There are three cases to install the DiskInfo protocol.
  // 1. For Raid disks, DiskInfo driver will new the individual device path for each disk and
  // install the DiskInfo protocol on the handle.
  // 2. For non-Raid disks, DiskInfo driver will install the DiskInfo protocol on the corresponding
  // device path handle.
  // 3. For the disk that is hidden by RAID driver, DiskInfo driver will new a device path for it,
  // and install DiskInfo protocol on the handle. (In the edge case that the RST cache disk.)
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiDevicePathProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR(Status);

  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < HandleCount; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiDevicePathProtocolGuid,
                      (VOID *) &DevicePath
                      );
      ASSERT_EFI_ERROR(Status);

      //
      // Check that parent devicepath is identical.
      //
      Status = GetRemainingDevicePath (ParentDevicePath, DevicePath, &RemainingDevicePath);
      if (EFI_ERROR (Status)) {
        continue;
      }

      //
      // Check the sata devicepath port number
      //
      DevicePathNode = RemainingDevicePath;
      while (!IsDevicePathEndType (DevicePathNode)) {
        if ((DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
            (DevicePathNode->SubType == MSG_SATA_DP)) {
          SataDevicePathNode = (SATA_DEVICE_PATH *) DevicePathNode;
          //
          // The RAID driver overloads the Sata port number information.
          // Since customers require a mechanism to communicate which physical devices are represented
          // with each Logical Disk (3 physical disks may be exposed as a RAID5 logical disk).
          // It uses the port number of the SATA DEVICE PATH as a bitmap of the ports.
          //
          if (SataDevicePathNode->HBAPortNumber == (1 << Port)) {
            //
            // Only one bit is set, then this is a non-Raid Disk device path.
            // It's case 2.
            //
            DeviceHandle = HandleBuffer[Index];
            break;
          }
        }
        DevicePathNode = NextDevicePathNode (DevicePathNode);
      }

      if (DeviceHandle != NULL) {
        break;
      }
    }
  }

  if (HandleBuffer != NULL) {
    FreePool (HandleBuffer);
  }

  if (DeviceHandle != NULL) {
    //
    // If DeviceHandle is available, it's case 2 or the device path is generated earlier.
    // If the DiskInfo protocol is existed, it's already started.
    //
    Status = gBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiDiskInfoProtocolGuid,
                    (VOID **) &DiskInfo
                    );
    if (!EFI_ERROR (Status)) {
      Status = EFI_ALREADY_STARTED;
      goto Done;
    }
  } else {
    //
    // If no DeviceHandle is available, it's case 1 or case 3.
    // will generate new device path for this sata port.
    //
    NewDevicePathNode = AllocateCopyPool (sizeof (SATA_DEVICE_PATH), &mSataDevicePathTemplate);
    if (NewDevicePathNode == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto Done;
    }

    //
    // The HBAPortNumbe is bitmap for the port.
    // Set bit 15 of PortMultiplierPortNumber to indicate direct connect.
    //
    ((EFI_DEV_PATH *)NewDevicePathNode)->Sata.HBAPortNumber            = (1 << Port);
    ((EFI_DEV_PATH *)NewDevicePathNode)->Sata.PortMultiplierPortNumber = (0x8000 | PortMultiplierPort);
    ((EFI_DEV_PATH *)NewDevicePathNode)->Sata.Lun                      = 0;

    DevicePath = AppendDevicePathNode (ParentDevicePath, NewDevicePathNode);
    if (DevicePath == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto Done;
    }

    //
    // Relese the resouce
    //
    if (NewDevicePathNode != NULL) {
      FreePool (NewDevicePathNode);
    }
    //
    // Keep the resouce and need to be released later if error.
    //
    NewDevicePathNode = DevicePath;
  }

  //
  // Allocate ATA device from the template.
  //
  AtaDevice = AllocateCopyPool (sizeof (mAtaDeviceTemplate), &mAtaDeviceTemplate);
  if (AtaDevice == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  //
  // Initializes ATA device structures and allocates the required buffer.
  //
  AtaDevice->Handle             = DeviceHandle;
  AtaDevice->DevicePath         = DevicePath;
  AtaDevice->Port               = Port;
  AtaDevice->PortMultiplierPort = PortMultiplierPort;
  AtaDevice->Asb                = AllocateAlignedPages (EFI_SIZE_TO_PAGES (sizeof(EFI_ATA_STATUS_BLOCK)), AtaPassThru->Mode->IoAlign);
  if (AtaDevice->Asb == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }
  AtaDevice->IdentifyData       = AllocateAlignedPages (EFI_SIZE_TO_PAGES (sizeof(ATA_IDENTIFY_DATA)), AtaPassThru->Mode->IoAlign);
  if (AtaDevice->IdentifyData == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  //
  // Try to identify the ATA device via the ATA pass through command.
  //
  Status = DiscoverAtaDevice (AtaDevice, AtaPassThru);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  if (DeviceHandle != NULL) {
    //
    // For case 2, install the DiskInfo protocol on existed device path handle.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &AtaDevice->Handle,
                    &gEfiDiskInfoProtocolGuid,
                    &AtaDevice->DiskInfo,
                    NULL
                    );
  } else {
    //
    // For case 1 and case 3, new a handle and install the device path nad DiskInfo protocols.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &AtaDevice->Handle,
                    &gEfiDevicePathProtocolGuid,
                    AtaDevice->DevicePath,
                    &gEfiDiskInfoProtocolGuid,
                    &AtaDevice->DiskInfo,
                    NULL
                    );
  }

Done:
  if (EFI_ERROR (Status) && (NewDevicePathNode != NULL)) {
    FreePool (NewDevicePathNode);
  }
  if (EFI_ERROR (Status) && (AtaDevice != NULL)) {
    if (AtaDevice->Asb != NULL) {
      FreePages (AtaDevice->Asb, EFI_SIZE_TO_PAGES (sizeof (EFI_ATA_STATUS_BLOCK)));
    }

    if (AtaDevice->IdentifyData != NULL) {
      FreePages (AtaDevice->IdentifyData, EFI_SIZE_TO_PAGES (sizeof (ATA_IDENTIFY_DATA)));
    }
    FreePool (AtaDevice);
  }
  return Status;
}


/**
  Produce DiskInfo protocol interface for every attached ATA HDD physical device.

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  RemainingDevicePath  A pointer to the remaining portion of a device path.  This
                                   parameter is ignored by device drivers, and is optional for bus
                                   drivers. For a bus driver, if this parameter is NULL, then handles
                                   for all the children of Controller are created by this driver.
                                   If this parameter is not NULL and the first Device Path Node is
                                   not the End of Device Path Node, then only the handle for the
                                   child device specified by the first Device Path Node of
                                   RemainingDevicePath is created by this driver.
                                   If the first Device Path Node of RemainingDevicePath is
                                   the End of Device Path Node, no child handle is created by this
                                   driver.

  @retval EFI_SUCCESS              The device was started.
  @retval EFI_DEVICE_ERROR         The device could not be started due to a device error.Currently not implemented.
  @retval EFI_OUT_OF_RESOURCES     The request could not be completed due to a lack of resources.
  @retval Others                   The driver failded to start the device.

**/
VOID
DiskInfoForPhyDev (
  IN EFI_HANDLE                   Controller,
  IN EFI_HANDLE                   DriverBinding,
  IN EFI_ATA_PASS_THRU_PROTOCOL   *AtaPassThru,
  IN EFI_DEVICE_PATH_PROTOCOL     *ParentDevicePath
  )
{
  EFI_STATUS                        Status;
  UINT16                            Port;
  UINT16                            PortMultiplierPort;

  Port = 0xFFFF;
  while (TRUE) {
    Status = AtaPassThru->GetNextPort (AtaPassThru, &Port);
    if (EFI_ERROR (Status)) {
      //
      // We cannot find more legal port then we are done.
      //
      break;
    }

    PortMultiplierPort = 0xFFFF;
    while (TRUE) {
      Status = AtaPassThru->GetNextDevice (AtaPassThru, Port, &PortMultiplierPort);
      if (EFI_ERROR (Status)) {
        //
        // We cannot find more legal port multiplier port number for ATA device
        // on the port, then we are done.
        //
        break;
      }
      RegisterAtaHddDevice (Controller, DriverBinding, AtaPassThru, ParentDevicePath, Port, PortMultiplierPort);
    }
  }

  //
  // Uninstall Orphan DiskInfo protocols.
  // In cases where HDD locked password is not entered (Esc key pressed), RST driver re-enumerates the HDDs.
  // RST driver uninstalls the BlockIo and DevicePath protocol for existing handles but does not uninstall the DiskInfo
  // protocol handles. The UefiRaidDiskInfo driver needs to uninstall the same to handle Orphan DiskInfo handles which
  // wont have a corresponding DevicePath installed.
  //
  UninstallOrphanDiskInfoProtocol ();
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
IntelUefiRaidDiskInfoDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS                      Status;
  EFI_PCI_IO_PROTOCOL             *PciIo;
  EFI_ATA_PASS_THRU_PROTOCOL      *AtaPassThru;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  PCI_TYPE00                      PciData;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiAtaPassThruProtocolGuid,
                  (VOID **) &AtaPassThru,
                  This->DriverBindingHandle,
                  Controller,
//todo                   EFI_OPEN_PROTOCOL_BY_DRIVER
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
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
  // Now further check the PCI header: Base class (offset 0x0B) and
  // Sub Class (offset 0x0A). This controller should be an ATA controller
  //
  Status = PciIo->Pci.Read (
                        PciIo,
                        EfiPciIoWidthUint8,
                        PCI_CLASSCODE_OFFSET,
                        sizeof (PciData.Hdr.ClassCode),
                        PciData.Hdr.ClassCode
                        );
  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
    goto Done;
  }

  Status = EFI_UNSUPPORTED;
  if (IS_PCI_RAID (&PciData)) {
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
IntelUefiRaidDiskInfoDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS                      Status;
  EFI_DEVICE_PATH_PROTOCOL        *PciDevPath;
  EFI_ATA_PASS_THRU_PROTOCOL      *AtaPassThru;

  //
  // Initialize variables
  //
  AtaPassThru = NULL;
  PciDevPath  = NULL;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiAtaPassThruProtocolGuid,
                  (VOID **) &AtaPassThru,
                  This->DriverBindingHandle,
                  Controller,
//todo                   EFI_OPEN_PROTOCOL_BY_DRIVER
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
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

Error:
  if (EFI_ERROR (Status)) {
    if (AtaPassThru != NULL) {
      gBS->CloseProtocol (
            Controller,
            &gEfiAtaPassThruProtocolGuid,
            This->DriverBindingHandle,
            Controller
            );
    }
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
IntelUefiRaidDiskInfoDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer
  )
{
  EFI_STATUS             Status;
  BOOLEAN                AllChildrenStopped;
  EFI_DISK_INFO_PROTOCOL *DiskInfo;
  UINTN                  Index;
  ATA_DEVICE             *AtaDevice;

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
  Driver entry point.

  @param  ImageHandle  Handle of driver image.
  @param  SystemTable  Pointer to system table.

  @retval EFI_SUCCESS  Entrypoint successfully executed.
  @retval Others       Fail to execute entrypoint.

**/
EFI_STATUS
EFIAPI
IntelUefiRaidDiskInfoEntryPoint (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable
  )
{
  PCH_SETUP                             PchSetup;
  UINTN                                 VarSize;
  EFI_STATUS                            Status;

  DEBUG ((DEBUG_INFO, "IntelUefiRaidDiskInfoEntryPoint efi driver\n"));

  VarSize = sizeof (PCH_SETUP);
  Status  = gRT->GetVariable (
                   L"PchSetup",
                   &gPchSetupVariableGuid,
                   NULL,
                   &VarSize,
                   &PchSetup
                   );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "SataInterfaceMode:%x \n", PchSetup.SataInterfaceMode));
    if (PchSetup.SataInterfaceMode == SATA_MODE_RAID) {
      //
      // Install protocols
      //
      Status = EfiLibInstallDriverBindingComponentName2 (
                 ImageHandle,
                 SystemTable,
                 &gIntelUefiRaidDiskInfoDriverBinding,
                 ImageHandle,
                 &gIntelUefiRaidDiskInfoComponentName,
                 &gIntelUefiRaidDiskInfoComponentName2
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  return EFI_SUCCESS;
}

/**
  Uninstalls all Orphan DiskInfo protocols whenever there is a re-enumeration of drives by RST driver (ATA_IDENTIFY)

  @param  VOID                   No Input parameter

  @retval VOID                   No Return Value

**/
VOID
UninstallOrphanDiskInfoProtocol (
  VOID
  )
{
  EFI_STATUS                        Status;
  UINTN                             HandleCount;
  EFI_HANDLE                        *HandleBuffer;
  EFI_DISK_INFO_PROTOCOL            *pDiskInfo;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  UINT8                             i;

  HandleCount  = 0;
  HandleBuffer = NULL;
  pDiskInfo    = NULL;
  DevicePath   = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiDiskInfoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );

  if (EFI_ERROR (Status)) {
    return;
  }

  for (i = 0; i < HandleCount; i++) {
    //
    // Check for Orphan DiskInfo protocols (i.e. any handle without DevicePath). If any found, uninstall the same.
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[i],
                    &gEfiDevicePathProtocolGuid,
                    (VOID *) &DevicePath
                    );

    if (Status == EFI_SUCCESS) {
      //
      // Not an orphan. Skip it.
      //
      continue;
    }

    Status = gBS->HandleProtocol (
                    HandleBuffer[i],
                    &gEfiDiskInfoProtocolGuid,
                    (VOID *) &pDiskInfo
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // Uninstall Orphan DiskInfo protocol
    //
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    HandleBuffer[i],
                    &gEfiDiskInfoProtocolGuid,
                    pDiskInfo,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }

  if (HandleBuffer != NULL) {
    FreePool (HandleBuffer);
  }

  return;
}
