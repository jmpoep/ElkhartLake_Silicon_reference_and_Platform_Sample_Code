/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#define EFI_DISK_INFO_RAID_INTERFACE_GUID \
  { \
    0x5f9d4e5e, 0x9d11, 0x40fe, { 0x9d, 0x33, 0x6b, 0x33, 0xbf, 0xf4, 0x54, 0xfb} \
  }

//
// Template for ATA Hdd Device.
//
ATA_DEVICE mAtaDeviceTemplate = {
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

LIST_ENTRY                  mDeviceList;

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
  Gets ATA device Capacity according to ATA 6.

  This function returns the capacity of the ATA device if it follows
  ATA 6 to support 48 bit addressing.

  @param  AtaDevice         The ATA child device involved for the operation.

  @return The capacity of the ATA device or 0 if the device does not support
          48-bit addressing defined in ATA 6.

**/
EFI_LBA
GetAtapi6Capacity (
  IN ATA_DEVICE                 *AtaDevice
  )
{
  EFI_LBA                       Capacity;
  EFI_LBA                       TmpLba;
  UINTN                         Index;
  ATA_IDENTIFY_DATA             *IdentifyData;

  IdentifyData = AtaDevice->IdentifyData;
  if ((IdentifyData->command_set_supported_83 & BIT10) == 0) {
    //
    // The device doesn't support 48 bit addressing
    //
    return 0;
  }

  //
  // 48 bit address feature set is supported, get maximum capacity
  //
  Capacity = 0;
  for (Index = 0; Index < 4; Index++) {
    //
    // Lower byte goes first: word[100] is the lowest word, word[103] is highest
    //
    TmpLba = IdentifyData->maximum_lba_for_48bit_addressing[Index];
    Capacity |= LShiftU64 (TmpLba, 16 * Index);
  }

  return Capacity;
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
  Registers an ATA HDD device.

  This function allocates an ATA device structure for the ATA device specified by
  Port and PortMultiplierPort if the ATA device is identified as a valid one. 
  Then it will create child handle and install Block IO and Disk Info protocol on
  it.

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
  EFI_DEVICE_PATH_PROTOCOL          *NewDevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;
  EFI_HANDLE                        DeviceHandle;
  ATA_DEVICE                        *AtaDevice;
  EFI_ATA_PASS_THRU_PROTOCOL        *ChildAtaPassThru;

  AtaDevice           = NULL;
  NewDevicePathNode   = NULL;
  DevicePath          = NULL;
  RemainingDevicePath = NULL;

  Status = AtaPassThru->BuildDevicePath (AtaPassThru, Port, PortMultiplierPort, &NewDevicePathNode);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  DevicePath = AppendDevicePathNode (ParentDevicePath, NewDevicePathNode);
  if (DevicePath == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  DeviceHandle = NULL;
  RemainingDevicePath = DevicePath;
  Status = gBS->LocateDevicePath (&gEfiDevicePathProtocolGuid, &RemainingDevicePath, &DeviceHandle);
  if (!EFI_ERROR (Status) && (DeviceHandle != NULL) && IsDevicePathEnd(RemainingDevicePath)) {
    Status = EFI_ALREADY_STARTED;
    FreePool (DevicePath);
    goto Done;
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
  //AtaDevice->BlockIo.Media = &AtaDevice->BlockMedia;
  AtaDevice->DevicePath = DevicePath;
  AtaDevice->Port = Port;
  AtaDevice->PortMultiplierPort = PortMultiplierPort;
  AtaDevice->Asb = AllocateAlignedPages (EFI_SIZE_TO_PAGES (sizeof(EFI_ATA_STATUS_BLOCK)), AtaPassThru->Mode->IoAlign);
  if (AtaDevice->Asb == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }
  AtaDevice->IdentifyData = AllocateAlignedPages (EFI_SIZE_TO_PAGES (sizeof(ATA_IDENTIFY_DATA)), AtaPassThru->Mode->IoAlign);
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

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &AtaDevice->Handle,
                  &gEfiDevicePathProtocolGuid,
                  AtaDevice->DevicePath,
                  &gEfiDiskInfoProtocolGuid,
                  &AtaDevice->DiskInfo,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  gBS->OpenProtocol (
         Controller,
         &gEfiAtaPassThruProtocolGuid,
         (VOID **) &ChildAtaPassThru,
         DriverBinding,
         AtaDevice->Handle,
         EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
         );

  //
  // Insert device info into global variable.
  //
  InsertTailList(&mDeviceList, &AtaDevice->Link);

Done:
  if (NewDevicePathNode != NULL) {
    FreePool (NewDevicePathNode);
  }

  if (EFI_ERROR (Status) && (AtaDevice != NULL)) {
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

  InitializeListHead(&mDeviceList);

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
  
}