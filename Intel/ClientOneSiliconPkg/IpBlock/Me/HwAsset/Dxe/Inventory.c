/** @file
  Performs PCI and Media device inventory.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PchInfoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/IdeControllerInit.h>
#include <Protocol/DiskInfo.h>
#include <IndustryStandard/Nvme.h>
#include <Protocol/NvmExpressPassthru.h>
#include <Protocol/AtaPassThru.h>
#include <Protocol/BlockIo.h>
#include <IndustryStandard/AlertStandardFormatTable.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/SmBios.h>
#include "Inventory.h"

/**
  Create the FRU table to send to AMT FW

  @param[in] AssetTableData  Buffer of all Asset tables to send to FW
  @param[in] TableOffset     Offset to the beginning of HWA PCI Fru Table

  @return    Size            Size of the HWA PCI Fru Table
**/
UINT16
BuildHwaPciFruTable (
  IN HWA_TABLE                    *AssetTableData,
  IN UINT16                       TableOffset
  )
{
  HWA_FRU_TABLE                   *PciFruTable;
  HWA_PCI_FRU_DATA                *PciFru;
  EFI_STATUS                      Status;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *IoDev;
  UINT16                          MaxBus;
  UINT16                          Bus;
  UINT16                          Device;
  UINT16                          Func;
  UINT64                          Address;
  PCI_DEVICE_INDEPENDENT_REGION   PciHeader;
  UINT8                           SecondaryBus;
  UINT16                          Length;

  PciFruTable = (HWA_FRU_TABLE*)&AssetTableData->TableData[TableOffset];
  PciFru = &PciFruTable->Data[0];

  //
  // Locate the PCI IO protocol
  //
  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  (VOID **) &IoDev
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Go through devices on bus 0, if PCI bridge found - increase maximum bus number.
  // Break the function loop if the device is not a multi - function device.
  // Do not send PCH devices (bus 0) to AMT.
  //
  MaxBus = 0;
  for (Bus = 0; Bus <= MaxBus; Bus++) {
    for (Device = 0; Device <= PCI_MAX_DEVICE; Device++) {
      for (Func = 0; Func <= PCI_MAX_FUNC; Func++) {
        Address = EFI_PCI_ADDRESS (Bus, Device, Func, 0);
        IoDev->Pci.Read (IoDev, EfiPciWidthUint16, Address, 1, &PciHeader.VendorId);
        if (PciHeader.VendorId != 0xFFFF) {
          IoDev->Pci.Read (IoDev, EfiPciWidthUint32, Address, sizeof (PciHeader) / sizeof (UINT32), &PciHeader);
          if (PciHeader.ClassCode[2] == PCI_CLASS_BRIDGE) {
            IoDev->Pci.Read (IoDev, EfiPciWidthUint8, Address + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, 1, &SecondaryBus);
            MaxBus = MAX (MaxBus, SecondaryBus);
          }
          if (Bus != 0) {
            PciFru->SmbiosType   = 0;
            PciFru->Length       = sizeof (HWA_PCI_FRU_DATA);
            PciFru->SmbiosHandle = 0;
            PciFru->FruType      = HWA_FRU_TYPE_PCI;
            PciFru->VendorId     = PciHeader.VendorId;
            PciFru->DeviceId     = PciHeader.DeviceId;
            PciFru->RevisionId   = PciHeader.RevisionID;
            PciFru->ClassCode    = ((UINT32) PciHeader.ClassCode[0]) | ((UINT32) PciHeader.ClassCode[1] << 0x8) | ((UINT32) PciHeader.ClassCode[2] << 0x10);
            //
            // Read SVID and SID
            //
            IoDev->Pci.Read (IoDev, EfiPciWidthUint16, Address + PCI_SVID_OFFSET, 2, &PciFru->SubsystemVendorId);
            PciFru->BusDevFunc  = (UINT16) (Bus << 0x08 | Device << 0x03 | Func);
            PciFruTable->StructureCount++;
            PciFru++;
          }
          if (Func == 0 && ((PciHeader.HeaderType & HEADER_TYPE_MULTI_FUNCTION) == 0x00)) {
            break;
          }
        }
      }
    }
  }

  PciFruTable->TableByteCount = PciFruTable->StructureCount * sizeof (HWA_PCI_FRU_DATA);

  Length = PciFruTable->TableByteCount + sizeof (PciFruTable->StructureCount)
           + sizeof (PciFruTable->TableByteCount);

  return Length;
}

/**
  Transfer each other while being front and back.

  @param[in] Data                 The address of data
  @param[in] Size                 Size of data

**/
VOID
SwapEntries (
  IN CHAR8                        *Data,
  IN UINT8                        Size
  )
{
  UINT16                          Index;
  CHAR8                           Temp8;

  Index = 0;
  while (Data[Index] != 0 && Data[Index + 1] != 0) {
    Temp8           = Data[Index];
    Data[Index]     = Data[Index + 1];
    Data[Index + 1] = Temp8;
    Index += 2;
    if (Index >= Size) {
      break;
    }
  }

  return;
}


/**
  Get Nvme device identify data.

  @param[in]   NvmeDevice        The pointer to the NVME_PASS_THRU_DEVICE data structure.
  @param[in]   NamespaceId       NamespaceId for an NVM Express namespace present on the NVM Express controller
  @param[in]   IdentifyStructure Specifies the information to be returned to host.
  @param[out]  Buffer            The buffer used to store the identify controller data.

  @return EFI_SUCCESS            Successfully get the identify controller data.
  @return EFI_DEVICE_ERROR       Fail to get the identify controller data.
**/
EFI_STATUS
NvmeIdentifyCommand (
  IN  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NvmeDevice,
  IN  UINT32                                NamespaceId,
  IN  UINT32                                IdentifyStructure,
  OUT VOID                                  *Buffer
  )
{
  EFI_STATUS                                Status;
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET  CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                   Command;
  EFI_NVM_EXPRESS_COMPLETION                Completion;

  ZeroMem (&CommandPacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof(EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof(EFI_NVM_EXPRESS_COMPLETION));

  DEBUG ((DEBUG_INFO, "Sending Identify Command with Cns = %d\n", IdentifyStructure));

  Command.Cdw0.Opcode          = NVME_ADMIN_IDENTIFY_CMD;

  Command.Nsid                 = NamespaceId;

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;
  CommandPacket.TransferBuffer = Buffer;
  CommandPacket.TransferLength = sizeof (NVME_ADMIN_CONTROLLER_DATA);
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;
  //
  // Set bit 0 (Cns bit) to 0 to identify a namespace / 1 to identify a controller
  //
  Command.Cdw10                = IdentifyStructure;
  Command.Flags                = CDW10_VALID;

  Status = NvmeDevice->PassThru (NvmeDevice, NamespaceId, &CommandPacket, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "Identify Command Status=%r\n", Status));
  }

  return Status;
}

/**
  Checks if the given device is a USBr device.

  @param[in]   DevicePath         A pointer to a device path data structure.

  @retval      True               Current device is a USBr device.
  @return      False              Current device is not a USBr device.
**/
BOOLEAN
IsUsbrDevice(
  IN  EFI_DEVICE_PATH_PROTOCOL          *DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL             *DevicePathNode;

  DevicePathNode  = DevicePath;

  while (!IsDevicePathEnd (DevicePathNode)) {
    if ((DevicePathType (DevicePathNode) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (DevicePathNode) == MSG_USB_DP)) {
      if (((IsPchH ()) && (((USB_DEVICE_PATH *)DevicePathNode)->ParentPortNumber == V_ME_PCH_H_USBR2_PORT_NUMBER)) ||
          ((IsPchLp ()) && (((USB_DEVICE_PATH *)DevicePathNode)->ParentPortNumber == V_ME_PCH_LP_USBR2_PORT_NUMBER))) {
        return TRUE;
      }
    }
    DevicePathNode = NextDevicePathNode (DevicePathNode);
  }
  return FALSE;
}


/**
  Searches the device path for the handle that has a pass thru protocol installed.

  @param[in]   DevicePath         A pointer to a device path data structure.
  @param[in]   ProtocolGuid       Guid of a protocol that is being searched.

  @retval      True               Pass Thru Protocol was located.
  @return      False              Failed to locate Pass Thru Protocol.
**/
BOOLEAN
IsPassThruProtocolAvailable (
  IN  EFI_DEVICE_PATH_PROTOCOL          *DevicePath,
  IN  EFI_GUID                          ProtocolGuid
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            Handle;

  Status = gBS->LocateDevicePath (
                  &ProtocolGuid,
                  &DevicePath,
                  &Handle
                  );
  if (EFI_ERROR (Status)) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Get Sata HDD identify data.

  @param[in]          AtaDevice           The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]          Port                Port number on the ATA controller
  @param[in]          PortMultiplierPort  Port multiplier port number on the ATA controller
  @param[out]         ControllerData      The buffer used to store the identify controller data.

  @return             EFI_SUCCESS         Successfully get the identify controller data.
  @return             EFI_DEVICE_ERROR    Fail to get the identify controller data.
**/
EFI_STATUS
GetHddIdentifyData (
  IN EFI_ATA_PASS_THRU_PROTOCOL             *AtaDevice,
  IN UINT16                                 Port,
  IN UINT16                                 PortMultiplierPort,
  OUT ATA_IDENTIFY_DATA                     *ControllerData
  )
{
  EFI_STATUS                               Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET         Packet;
  EFI_ATA_COMMAND_BLOCK                    Acb;
  EFI_ATA_STATUS_BLOCK                     Asb;

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));

  Acb.AtaCommand             = ATA_CMD_IDENTIFY_DRIVE;

  Packet.Protocol            = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Acb                 = &Acb;
  Packet.Asb                 = &Asb;
  Packet.InDataBuffer        = ControllerData;
  Packet.InTransferLength    = sizeof (ATA_IDENTIFY_DATA);
  Packet.Length              = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Timeout             = EFI_TIMER_PERIOD_SECONDS (3);

  Status = AtaDevice->PassThru (AtaDevice, Port, PortMultiplierPort, &Packet, NULL);

  return Status;

}

/**
  Get device identify data using Disk Info Protocol.

  @param[in]   Handle             Handle to the device.
  @param[out]  IdentifyDriveInfo  The buffer used to store the device identify data.

  @return EFI_SUCCESS             Successfully got the device identify data.
  @return Other                   Failed to get the identify controller data.
**/
EFI_STATUS
GetIdentifyDataFromDiskInfo (
  IN  EFI_HANDLE                        Handle,
  OUT EFI_IDENTIFY_DATA                 *IdentifyDriveInfo
  )
{
  EFI_STATUS                           Status;
  EFI_DISK_INFO_PROTOCOL               *DiskInfo;
  UINT32                               BufferSize;

  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiDiskInfoProtocolGuid,
                  (VOID **) &DiskInfo
                  );

  if (EFI_ERROR (Status)) {
   return Status;
  }

  BufferSize = sizeof (EFI_IDENTIFY_DATA);
  ZeroMem (IdentifyDriveInfo, sizeof (EFI_IDENTIFY_DATA));

  Status = DiskInfo->Identify (
                       DiskInfo,
                       IdentifyDriveInfo,
                       &BufferSize
                       );
  ASSERT_EFI_ERROR (Status);

  return Status;
}


/**
  Detects all Ata Devices with Ata Pass Thru Protocol installed and adds them to
  media table.

  @param[in] MediaEntryPtr     A pointer to current Media Table tail.

  @return DeviceCount          Number of detected ATA Devices.
**/
UINT16
DetectAtaDevices (
  IN HWA_MEDIA_ENTRY         *MediaEntryPtr
  )
{
  EFI_STATUS                 Status;
  UINTN                      HandleNum;
  EFI_HANDLE                 *AtaPassThruHandles;
  UINTN                      Index;
  UINTN                      WordOffset;
  EFI_ATA_PASS_THRU_PROTOCOL *AtaDevice;
  EFI_ATA_IDENTIFY_DATA      AtaIdentifyData;
  UINT16                     Port;
  UINT16                     PortMultiplierPort;
  UINT64                     DriveSize;
  UINT16                     DeviceCount;

  DeviceCount = 0;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiAtaPassThruProtocolGuid,
                  NULL,
                  &HandleNum,
                  &AtaPassThruHandles
                  );

  if (EFI_ERROR (Status)) {
    return DeviceCount;
  }

  DEBUG ((DEBUG_INFO, "Number of detected ATA Handles: %d\n", HandleNum));

  for (Index = 0; Index < HandleNum; Index++) {

    Status = gBS->HandleProtocol (
                    AtaPassThruHandles[Index],
                    &gEfiAtaPassThruProtocolGuid,
                    (VOID **) &AtaDevice
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "gBS->Handle Protocol : Status = %r\n", Status));
      return DeviceCount;
    }

    //
    // Go through all of the ports and portmultiplierports and get identify data
    //
    Port = 0xFFFF;

    while (TRUE) {

      Status = AtaDevice->GetNextPort (AtaDevice, &Port);
      if (EFI_ERROR (Status)) {
        if (Status == EFI_NOT_FOUND) {
          break;
        } else {
          return DeviceCount;
        }
      }

      PortMultiplierPort = 0xFFFF;

      while (TRUE) {
        Status = AtaDevice->GetNextDevice (AtaDevice, Port, &PortMultiplierPort);
        if (EFI_ERROR (Status)) {
          if (Status == EFI_NOT_FOUND) {
            break;
          } else {
            return DeviceCount;
          }
        }

        ZeroMem (&AtaIdentifyData, sizeof(ATA_IDENTIFY_DATA));
        Status = GetHddIdentifyData (AtaDevice, Port, PortMultiplierPort, &AtaIdentifyData);
        if (EFI_ERROR (Status)) {
          continue;
        }

        DriveSize = AtaIdentifyData.maximum_lba_for_48bit_addressing[0];
        ///
        /// Lower byte goes first: word[100] is the lowest word, word[103] is highest
        ///
        for (WordOffset = 1; WordOffset < 4; WordOffset++) {
          DriveSize |= LShiftU64 (AtaIdentifyData.maximum_lba_for_48bit_addressing[WordOffset], 16 * WordOffset);
        }
        DriveSize = MultU64x32 (DriveSize, 512);

        MediaEntryPtr->SmbiosType                    = 0;
        MediaEntryPtr->Length                        = sizeof (HWA_MEDIA_ENTRY);
        MediaEntryPtr->SmbiosHandle                  = 0;
        MediaEntryPtr->MediaData.StructSize          = sizeof (HWA_FRU_MEDIA_DEVICES);
        MediaEntryPtr->MediaData.Interface           = HWA_MEDIA_IN_SATA;
        MediaEntryPtr->MediaData.DevType             = HWA_MEDIA_DT_HDD;
        SwapEntries ((CHAR8 *) AtaIdentifyData.ModelName, (UINT8)MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
        SwapEntries ((CHAR8 *) AtaIdentifyData.SerialNo, (UINT8)MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
        CopyMem (&MediaEntryPtr->MediaData.SerialNo, AtaIdentifyData.SerialNo, MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
        CopyMem (&MediaEntryPtr->MediaData.VersionNo, AtaIdentifyData.FirmwareVer, MEDIA_DEVICE_VERSION_NO_MAX_LENGTH);
        CopyMem (&MediaEntryPtr->MediaData.ModelNo, AtaIdentifyData.ModelName, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
        CopyMem (&MediaEntryPtr->MediaData.SupportedCmdSets, &AtaIdentifyData.command_set_supported_82, sizeof (MediaEntryPtr->MediaData.SupportedCmdSets));
        MediaEntryPtr->MediaData.MaxMediaSize = DriveSize;
        DeviceCount++;
        MediaEntryPtr++;
      }
    }
  }
  return DeviceCount;
}


/**
  Detects all Nvm Express Devices with Nvm Express Pass Thru Protocol installed and adds them to
  media table.

  @param[in] MediaEntryPtr     A pointer to current Media Table tail.

  @return DeviceCount          Number of detected NVMe Devices.
**/
UINT16
DetectNvmeDevices (
  IN OUT HWA_MEDIA_ENTRY             *MediaEntryPtr
  )
{
  EFI_STATUS                         Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *NvmeDevice;
  NVME_ADMIN_CONTROLLER_DATA         ControllerData;
  NVME_ADMIN_NAMESPACE_DATA          NamespaceData;
  UINT32                             NamespaceId;
  UINTN                              HandleNum;
  EFI_HANDLE                         *NvmePassThruHandles;
  UINTN                              Index;
  UINT16                             DeviceCount;

  DeviceCount = 0;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiNvmExpressPassThruProtocolGuid,
                  NULL,
                  &HandleNum,
                  &NvmePassThruHandles
                  );

  if (EFI_ERROR (Status)) {
    return DeviceCount;
  }

  DEBUG ((DEBUG_INFO, "Number of detected NVMe Handles: %d\n", HandleNum));

  for (Index = 0; Index < HandleNum; Index++) {
    Status = gBS->HandleProtocol (
                    NvmePassThruHandles[Index],
                    &gEfiNvmExpressPassThruProtocolGuid,
                    (VOID **) &NvmeDevice
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "gBS->Handle Protocol : Status=%r\n", Status));
      return DeviceCount;
    }

    NamespaceId = NVME_ALL_NAMESPACES;

    while (TRUE) {
      Status = NvmeDevice->GetNextNamespace (NvmeDevice, &NamespaceId);
      if (EFI_ERROR (Status)) {
        if (Status == EFI_NOT_FOUND) {
          Status = EFI_SUCCESS;
          break;
        } else {
          return DeviceCount;
        }
      }
      ZeroMem (&ControllerData, sizeof(NVME_ADMIN_CONTROLLER_DATA));
      ZeroMem (&NamespaceData, sizeof(NVME_ADMIN_NAMESPACE_DATA));
      Status = NvmeIdentifyCommand (NvmeDevice, NamespaceId, NVME_IDENTIFY_NAMESPACE_STRUCT, (VOID *) &NamespaceData);
      if (EFI_ERROR (Status)) {
        continue;
      }
      //
      // Due to the fact that RAID Driver expects other value of NamespaceId parameter than AHCI driver,
      // need to send the Identify Controller command twice - once with the NamespaceId retrieved
      // using GetNextNamespace. If it fails we need to set NamespaceId = 0.
      //
      Status = NvmeIdentifyCommand (NvmeDevice, NamespaceId, NVME_IDENTIFY_CONTROLLER_STRUCT, (VOID *) &ControllerData);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_WARN, "NvmeIdentifyCommand Error. Sending Identify Command once again\n"));
        Status = NvmeIdentifyCommand (NvmeDevice, NVME_CONTROLLER_ID, NVME_IDENTIFY_CONTROLLER_STRUCT, (VOID *) &ControllerData);
        if (EFI_ERROR (Status)) {
          continue;
        }
      }
      MediaEntryPtr->SmbiosType                    = 0;
      MediaEntryPtr->Length                        = sizeof (HWA_MEDIA_ENTRY);
      MediaEntryPtr->SmbiosHandle                  = 0;
      MediaEntryPtr->MediaData.StructSize          = sizeof (HWA_FRU_MEDIA_DEVICES);
      MediaEntryPtr->MediaData.Interface           = HWA_MEDIA_IN_PCIE;
      MediaEntryPtr->MediaData.DevType             = HWA_MEDIA_DT_HDD;
      CopyMem (&MediaEntryPtr->MediaData.ModelNo,   ControllerData.Mn, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
      CopyMem (&MediaEntryPtr->MediaData.SerialNo,  ControllerData.Sn, MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
      CopyMem (&MediaEntryPtr->MediaData.VersionNo, ControllerData.Fr, MEDIA_DEVICE_VERSION_NO_MAX_LENGTH);
      MediaEntryPtr->MediaData.SupportedCmdSets[0] = ControllerData.Oacs;
      MediaEntryPtr->MediaData.SupportedCmdSets[1] = ControllerData.Oncs;
      MediaEntryPtr->MediaData.MaxMediaSize        = MultU64x32 (NamespaceData.Ncap, 512);
      DeviceCount++;
      MediaEntryPtr++;
    }
  }
  return DeviceCount;
}

/**
  Get last device before end of device path node.

  @param[in]   DevicePath         A pointer to a device path data structure.
  @param[out]  Type               The Type field of the device path node specified by Node.
  @param[out]  SubType            The SubType field of the device path node specified by Node.
**/
VOID
GetLastDeviceFromDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL         *DevicePath,
  OUT UINT8                            *Type,
  OUT UINT8                            *Subtype
  )
{
  EFI_DEVICE_PATH_PROTOCOL             *DevicePathNode;

  DevicePathNode  = DevicePath;

  while (!IsDevicePathEnd (DevicePathNode)) {
    *Type = DevicePathType (DevicePathNode);
    *Subtype = DevicePathSubType (DevicePathNode);
    DevicePathNode = NextDevicePathNode (DevicePathNode);
  }
}

/**
  Detects Block I/O devices without ATA and NVMe PassThru Protocol installed and adds them to
  media table.

  @param[in] MediaEntryPtr     A pointer to current Media Table tail.

  @return DeviceCount          Number of detected Block I/O Devices.
**/
UINT16
DetectBlockIoDevices (
  IN HWA_MEDIA_ENTRY       *MediaEntryPtr
  )
{
  EFI_STATUS               Status;
  UINT16                   Index;
  UINTN                    HandleCount;
  EFI_HANDLE               *HandleBuffer;
  EFI_BLOCK_IO_PROTOCOL    *BlkIo;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  EFI_IDENTIFY_DATA        IdentifyDriveInfo;
  UINT8                    Type;
  UINT8                    Subtype;
  UINT16                   DeviceCount;

  DeviceCount = 0;

  ///
  /// Locate all media devices connected.
  /// We look for the Block I/O protocol to be attached to the device.
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiBlockIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || HandleCount == 0) {
    return DeviceCount;
  }
  DEBUG ((DEBUG_INFO, "HandleCount = 0x%x\n", HandleCount));
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiBlockIoProtocolGuid,
                    (VOID **) &BlkIo
                    );
    ASSERT_EFI_ERROR (Status);

    ///
    /// We want to remove any Block I/O instances that refer to Logical partitions.
    /// A Block I/O instance is added to the raw device and any partition discovered on
    /// the media. This prevents duplications in our table.
    ///
    if (BlkIo->Media->LogicalPartition) {
      continue;
    }

    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiDevicePathProtocolGuid,
                    (VOID *) &DevicePath
                    );
    ASSERT_EFI_ERROR (Status);

    GetLastDeviceFromDevicePath (DevicePath, &Type, &Subtype);

    if (Type == MESSAGING_DEVICE_PATH) {
      switch (Subtype) {
        case MSG_ATAPI_DP:
          MediaEntryPtr->MediaData.MaxMediaSize = MultU64x32 (BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
          MediaEntryPtr->MediaData.Interface = HWA_MEDIA_IN_ATAPI;
          if (BlkIo->Media->RemovableMedia) {
            MediaEntryPtr->MediaData.DevType = HWA_MEDIA_DT_DVD;
          } else {
            MediaEntryPtr->MediaData.DevType = HWA_MEDIA_DT_HDD;
          }

          Status = GetIdentifyDataFromDiskInfo (HandleBuffer[Index], &IdentifyDriveInfo);
          if (!EFI_ERROR (Status)) {
            SwapEntries ((CHAR8 *) &IdentifyDriveInfo.AtapiData.ModelName, (UINT8)MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
            SwapEntries ((CHAR8 *) &IdentifyDriveInfo.AtapiData.SerialNo, (UINT8)MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
            CopyMem (&MediaEntryPtr->MediaData.SerialNo, IdentifyDriveInfo.AtapiData.SerialNo, MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
            CopyMem (&MediaEntryPtr->MediaData.VersionNo, IdentifyDriveInfo.AtapiData.FirmwareVer, MEDIA_DEVICE_VERSION_NO_MAX_LENGTH);
            CopyMem (&MediaEntryPtr->MediaData.ModelNo, IdentifyDriveInfo.AtapiData.ModelName, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
            CopyMem (&MediaEntryPtr->MediaData.SupportedCmdSets, &IdentifyDriveInfo.AtapiData.cmd_set_support_82, sizeof (MediaEntryPtr->MediaData.SupportedCmdSets));
          } else {
            AsciiStrCpyS ((CHAR8*)&MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "ATAPI");
          }
          break;

        case MSG_USB_DP:
          if (IsUsbrDevice (DevicePath) == TRUE) {
            continue;
          }
          MediaEntryPtr->MediaData.MaxMediaSize = MultU64x32 (BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
          MediaEntryPtr->MediaData.Interface = HWA_MEDIA_IN_ATA;
          MediaEntryPtr->MediaData.DevType   = HWA_MEDIA_DT_HDD;
          AsciiStrCpyS ((CHAR8*)&MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "USB");
          break;

        case MSG_SATA_DP:
          //
          // If this is a Removable Media it means the device is a ODD
          //
          if (BlkIo->Media->RemovableMedia) {
            MediaEntryPtr->MediaData.MaxMediaSize = MultU64x32 (BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
            MediaEntryPtr->MediaData.Interface    = HWA_MEDIA_IN_SATA;
            MediaEntryPtr->MediaData.DevType      = HWA_MEDIA_DT_DVD;

            Status = GetIdentifyDataFromDiskInfo (HandleBuffer[Index], &IdentifyDriveInfo);
            if (!EFI_ERROR (Status)) {
              SwapEntries ((CHAR8*)&IdentifyDriveInfo.AtaData.ModelName, (UINT8)MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
              SwapEntries ((CHAR8*)&IdentifyDriveInfo.AtaData.SerialNo, (UINT8)MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
              CopyMem (&MediaEntryPtr->MediaData.SerialNo, IdentifyDriveInfo.AtaData.SerialNo, MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH);
              CopyMem (&MediaEntryPtr->MediaData.VersionNo, IdentifyDriveInfo.AtaData.FirmwareVer, MEDIA_DEVICE_VERSION_NO_MAX_LENGTH);
              CopyMem (&MediaEntryPtr->MediaData.ModelNo, IdentifyDriveInfo.AtaData.ModelName, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH);
              CopyMem (&MediaEntryPtr->MediaData.SupportedCmdSets, &IdentifyDriveInfo.AtaData.command_set_supported_82, sizeof (MediaEntryPtr->MediaData.SupportedCmdSets));
            } else {
              AsciiStrCpyS ((CHAR8*)&MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "DVD Disk");
            }
            break;
          }
          //
          // If Protocol is available it means that the device was already identified and we should not increase
          // media device count.
          //
          if (IsPassThruProtocolAvailable (DevicePath, gEfiAtaPassThruProtocolGuid)) {
            continue;
          }
          MediaEntryPtr->MediaData.MaxMediaSize = MultU64x32 (BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
          MediaEntryPtr->MediaData.Interface = HWA_MEDIA_IN_SATA;
          if (BlkIo->Media->RemovableMedia) {
            MediaEntryPtr->MediaData.DevType = HWA_MEDIA_DT_DVD;
          } else {
            MediaEntryPtr->MediaData.DevType = HWA_MEDIA_DT_HDD;
          }
          AsciiStrCpyS ((CHAR8*)&MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "Unknown SATA Disk");
          break;

        case MSG_NVME_NAMESPACE_DP:
          if (IsPassThruProtocolAvailable (DevicePath, gEfiNvmExpressPassThruProtocolGuid)) {
            continue;
          }
          MediaEntryPtr->MediaData.MaxMediaSize = MultU64x32 (BlkIo->Media->LastBlock + 1, BlkIo->Media->BlockSize);
          MediaEntryPtr->MediaData.Interface    = HWA_MEDIA_IN_PCIE;
          MediaEntryPtr->MediaData.DevType      = HWA_MEDIA_DT_HDD;
          AsciiStrCpyS ((CHAR8*)MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "Unknown NVMe Disk");
          break;

        default:
          MediaEntryPtr->MediaData.Interface = HWA_MEDIA_IN_ATA;
          MediaEntryPtr->MediaData.DevType   = HWA_MEDIA_DT_MO;
          AsciiStrCpyS ((CHAR8*)&MediaEntryPtr->MediaData.ModelNo, MEDIA_DEVICE_MODEL_NO_MAX_LENGTH, "Unknown");
          break;
      }

      //
      // Add a common preface for each entry, increase number of entries
      // and forward the entry pointer
      //
      MediaEntryPtr->SmbiosType           = 0;
      MediaEntryPtr->Length               = sizeof (HWA_MEDIA_ENTRY);
      MediaEntryPtr->SmbiosHandle         = 0;
      MediaEntryPtr->MediaData.StructSize = sizeof (HWA_FRU_MEDIA_DEVICES);
      DeviceCount++;
      MediaEntryPtr++;
    }
  }

  FreePool (HandleBuffer);

  return DeviceCount;
}


/**
  Create the Media table to send to AMT FW

  @param[in] AssetTableData            Buffer of all Asset tables to send to FW
  @param[in] TableOffset               Offset to the beginning of Media Table

  @return    Size                      Size of the HWA Media Table
*/
UINT16
BuildHwaMediaTable (
  IN HWA_TABLE             *AssetTableData,
  IN UINT16                TableOffset
  )
{
  HWA_MEDIA_TABLE          *MediaHeaderPtr;
  HWA_MEDIA_ENTRY          *MediaEntryPtr;
  UINT16                   Length;
  UINT16                   DeviceCount;

  MediaHeaderPtr = (HWA_MEDIA_TABLE *) &AssetTableData->TableData[TableOffset];
  MediaEntryPtr = &MediaHeaderPtr->Data[0];

  ///
  /// 1. Detect connected ATA and NVMe devices using latest corresponding protocols.
  ///    The purpose is to detect devices in RAID configuration, which cannot be detected
  ///    using Block I/O.
  ///    Add ATA and NVMe devices using previous versions of protocols will be detected later on.
  /// 2. For other media devices use Block I/O to find them
  ///
  DeviceCount = DetectAtaDevices (MediaEntryPtr);
  MediaEntryPtr += DeviceCount;
  MediaHeaderPtr->StructureCount += DeviceCount;

  DeviceCount = DetectNvmeDevices (MediaEntryPtr);
  MediaEntryPtr += DeviceCount;
  MediaHeaderPtr->StructureCount += DeviceCount;

  DeviceCount = DetectBlockIoDevices (MediaEntryPtr);
  MediaEntryPtr += DeviceCount;
  MediaHeaderPtr->StructureCount += DeviceCount;

  MediaHeaderPtr->TableByteCount = MediaHeaderPtr->StructureCount * sizeof (HWA_MEDIA_ENTRY);
  Length = sizeof (MediaHeaderPtr->TableByteCount) + sizeof (MediaHeaderPtr->StructureCount) + MediaHeaderPtr->TableByteCount;
  return Length;
}

/**
  Get the full size of SMBIOS structure including optional strings that follow the formatted structure.

  @param[in] Head               Pointer to the beginning of SMBIOS structure.

  @return Size                  The returned size.
**/
UINTN
GetSmbiosStructureSize (
  IN   SMBIOS_STRUCTURE *Head
  )
{
  UINTN  Size;
  UINTN  StrLen;
  CHAR8  *CharInStr;

  CharInStr = (CHAR8*)Head + Head->Length;
  Size = Head->Length;
  StrLen = 0;
  //
  // look for the two consecutive zeros, check the string limit by the way.
  //
  while (*CharInStr != 0 || *(CharInStr+1) != 0) {
    if (*CharInStr == 0) {
      Size += 1;
      CharInStr++;
    }

    for (StrLen = 0 ; StrLen < SMBIOS_3_0_TABLE_MAX_LENGTH; StrLen++) {
      if (*(CharInStr+StrLen) == 0) {
        break;
      }
    }

    if (StrLen == SMBIOS_3_0_TABLE_MAX_LENGTH) {
      return 0;
    }

    //
    // forward the pointer
    //
    CharInStr += StrLen;
    Size += StrLen;
  }

  //
  // count ending two zeros.
  //
  Size += 2;

  return Size;
}

/**
  Create the SMBIOS table to send to AMT FW

  @param[in] AssetTableData   Buffer of all Asset tables to send to FW
  @param[in] TableOffset      Offset to the beginning of HWA SMBIOS Table

  @return    Size             Size of the HWA Asf Table
**/
UINT16
BuildHwaSmbiosTable (
  IN HWA_TABLE             *AssetTableData,
  IN UINT16                TableOffset
  )
{
  EFI_STATUS               Status;
  VOID                     *SmbiosTablePointer;
  SMBIOS_TABLE_ENTRY_POINT SmbiosEntryPointTable;
  SMBIOS_STRUCTURE         *SmbiosHeaderPtr;
  UINTN                    StructureLength;
  BOOLEAN                  IsEndOfTable;
  UINT16                   Length;

  IsEndOfTable = FALSE;

  ///
  /// 1. Locate SMBIOS table entry point structure and verify the anchor string ('_SM_')
  /// 2. Go through all SMBIOS tables and copy the required ones into Asset Table
  ///
  Status = EfiGetSystemConfigurationTable (&gEfiSmbiosTableGuid, (VOID **) &SmbiosTablePointer);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "Error getting SMBIOS Table GUID %g -> %r\n", gEfiSmbiosTableGuid, Status));
    return 0;
  }
  CopyMem (&SmbiosEntryPointTable, SmbiosTablePointer, sizeof (SMBIOS_TABLE_ENTRY_POINT));

  if (CompareMem (&SmbiosEntryPointTable.AnchorString, "_SM_", 4) == 1) {
    DEBUG ((DEBUG_WARN, "CalulateSmbiosTable Error:  Not SMBIOS Signature\n"));
    return 0;
  }

  if (SmbiosEntryPointTable.TableLength == 0) {
    DEBUG ((DEBUG_WARN, "CalulateSmbiosTable Error: SMBIOS Table Size == 0\n"));
    return 0;
  } else if (SmbiosEntryPointTable.TableLength > (MAX_ASSET_TABLE_ALLOCATED_SIZE - TableOffset)) {
    DEBUG ((DEBUG_WARN, "SMBIOS Tables Are Larger Than 0x%x\n", (MAX_ASSET_TABLE_ALLOCATED_SIZE - TableOffset)));
    return 0;
  }

  SmbiosHeaderPtr = (SMBIOS_STRUCTURE*)(UINTN)(SmbiosEntryPointTable.TableAddress);

  while (!IsEndOfTable) {
    StructureLength = GetSmbiosStructureSize (SmbiosHeaderPtr);
    switch (SmbiosHeaderPtr->Type) {
      case 13:
      case 15:
      case 25:
      case 32:
        ///
        /// Not needed by AMT - forward the SMBIOS table pointer but don't copy the data
        ///
        SmbiosHeaderPtr = (SMBIOS_STRUCTURE*)((UINT8*)SmbiosHeaderPtr + StructureLength);
        continue;
        break;

      case 127:
        IsEndOfTable = TRUE;
        break;
      default:
        break;
    }
    //
    // Copy the data and forward the pointers
    //
    CopyMem (&AssetTableData->TableData[TableOffset], (VOID *)(UINTN)SmbiosHeaderPtr, StructureLength);
    TableOffset += (UINT16)StructureLength;
    SmbiosHeaderPtr = (SMBIOS_STRUCTURE*)((UINT8*)SmbiosHeaderPtr + StructureLength);
  }

  Length = TableOffset - AssetTableData->Table[HWA_TABLE_TYPE_INDEX_SMBIOS].Offset;
  return Length;
}

/**
  Create the ASF table to send to AMT FW

  @param[in] AssetTableData   Buffer of all Asset tables to send to FW
  @param[in] TableOffset      Offset to the beginning of HWA ASF Table

  @return    Size             Size of the HWA Asf Table
**/
UINT16
BuildHwaAsfTable (
  IN HWA_TABLE                                 *AssetTableData,
  IN UINT16                                    TableOffset
  )
{
  EFI_STATUS                                   Status;
  EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                  *Rsdt;
  EFI_ACPI_DESCRIPTION_HEADER                  *TempAcpiTable;
  UINT32                                       Index;
  UINT32                                       Address;


  ///
  /// 1. Locate RSDP and RSDT.
  /// 2. Locate ASF! Table and copy it into Asset Table
  ///
  /// ACPI 2.0 or newer tables use gEfiAcpiTableGuid.
  ///
  Status = EfiGetSystemConfigurationTable (&gEfiAcpiTableGuid, (VOID *) &Rsdp);
  if (EFI_ERROR (Status) || (Rsdp == NULL)) {
    DEBUG ((DEBUG_WARN, "Error getting ACPI Table -> %r\n", Status));
    return 0;
  }

  Rsdt = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Rsdp->RsdtAddress;

  if (Rsdt->Signature != EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
    DEBUG ((DEBUG_WARN, "ACPI RSDT Signature Does Not Match\n"));
    return 0;
  }

  for (Index = sizeof (EFI_ACPI_DESCRIPTION_HEADER); Index < Rsdt->Length; Index = Index + sizeof (UINT32)) {
    Address       = *(UINT32*)((UINT8*) Rsdt + Index);
    TempAcpiTable = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Address;
    if (TempAcpiTable->Signature == EFI_ACPI_ASF_DESCRIPTION_TABLE_SIGNATURE) {
      CopyMem (&AssetTableData->TableData[TableOffset], (VOID *) (UINTN) TempAcpiTable, TempAcpiTable->Length);
      return (UINT16)TempAcpiTable->Length;
    }
  }

  return 0;

}

/**
  Constructs each of the lower level asset tables

  @param[in]  AssetTablesData           Buffer of all Asset tables to send to FW
  @param[in]  IsMediaTablePushRequested Determines if CSME has requested Media Table in this boot

  @return     TableSize                 Total Size of the HWA Table
**/
UINT16
BuildHwaTable (
  IN  HWA_TABLE           *AssetTableData,
  IN  BOOLEAN             IsMediaTablePushRequested
  )
{
  UINT16 TableSize;

  TableSize = 0;

  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_FRU_DEVICE].Offset = 0;
  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_FRU_DEVICE].Length = BuildHwaPciFruTable (AssetTableData, TableSize);
  TableSize += AssetTableData->Table[HWA_TABLE_TYPE_INDEX_FRU_DEVICE].Length;
  DEBUG ((DEBUG_INFO, "HWA Table offset after PCI FRU: %d,\n", TableSize));

  ///
  /// Build Media List if Firmware requests it or full BIOS boot path:
  /// If there are no media devices in the system - HWA Media table size is 4 bytes
  ///
  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_MEDIA_DEVICE].Offset = TableSize;
  if (GetBootModeHob () != BOOT_WITH_MINIMAL_CONFIGURATION || IsMediaTablePushRequested) {
    AssetTableData->Table[HWA_TABLE_TYPE_INDEX_MEDIA_DEVICE].Length = BuildHwaMediaTable (AssetTableData, TableSize);
  } else {
    AssetTableData->Table[HWA_TABLE_TYPE_INDEX_MEDIA_DEVICE].Length = sizeof (HWA_MEDIA_TABLE);
  }
  TableSize += AssetTableData->Table[HWA_TABLE_TYPE_INDEX_MEDIA_DEVICE].Length;
  DEBUG ((DEBUG_INFO, "HWA Table offset after Media Table: %d,\n", TableSize));

  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_SMBIOS].Offset = TableSize;
  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_SMBIOS].Length = BuildHwaSmbiosTable (AssetTableData, TableSize);
  TableSize += AssetTableData->Table[HWA_TABLE_TYPE_INDEX_SMBIOS].Length;
  DEBUG ((DEBUG_INFO, "HWA Table offset after SMBIOS Table: %d,\n", TableSize));

  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_ASF].Offset = TableSize;
  AssetTableData->Table[HWA_TABLE_TYPE_INDEX_ASF].Length = BuildHwaAsfTable (AssetTableData, TableSize);
  TableSize += AssetTableData->Table[HWA_TABLE_TYPE_INDEX_ASF].Length;
  DEBUG ((DEBUG_INFO, "Complete HWA Table Size: %d,\n", TableSize));

  return TableSize;
}

