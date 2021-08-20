/** @file
  Install Pei phase ATA passthru PPI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

@par Specification
**/

#include "AtaPassThruPei.h"

//
// Template for PEI ATA Private Data.
//
PEI_ATA_PASS_THRU_INSTANCE gPeiAtaPassThruPrivateTemplate = {
  PEI_ATA_PASS_THRU_SIGNATURE,    // Signature
  {                               // AtaPassThruMode
    //
    // According to UEFI2.3 spec Section 12.10, Drivers for non-RAID ATA controllers should set
    // both EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL and EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL
    // bits.
    // Note that the driver doesn't support AtaPassThru non blocking I/O.
    //
    EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL | EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL,
    //
    // IoAlign
    //
    sizeof (UINTN)
  },
  {                               // PeiAtaPassThruPpi
    NULL,
    PeiAtaPassThruPassThru,
    PeiAtaPassThruGetNextPort,
    PeiAtaPassThruGetNextDevice
  },
  {                               // PeiAtaPassThruPpiList
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiAtaPassThruPpiGuid,
    NULL
  },
  EfiAtaUnknownMode,              // Work Mode
  {                               // AhciRegisters
    0
  },
  0,                              // MmioBase
  {                               // DeviceList
    NULL,
    NULL
  },
  0,                  // PreviousPort
  0                   // PreviousPortMultiplier
};

UINTN               mAhciBar = 0;

/**
  Sends an ATA command to an ATA device that is attached to the ATA controller. This function
  supports both blocking I/O and non-blocking I/O. The blocking I/O functionality is required,
  and the non-blocking I/O functionality is optional.

  @param[in]      Port               The port number of the ATA device to send the command.
  @param[in]      PortMultiplierPort The port multiplier port number of the ATA device to send the command.
                                     If there is no port multiplier, then specify 0xFFFF.
  @param[in, out] Packet             A pointer to the ATA command to send to the ATA device specified by Port
                                     and PortMultiplierPort.
  @param[in]      Instance           Pointer to the ATA_ATAPI_PASS_THRU_INSTANCE.

  @retval EFI_SUCCESS                The ATA command was sent by the host. For
                                     bi-directional commands, InTransferLength bytes
                                     were transferred from InDataBuffer. For
                                     write and bi-directional commands, OutTransferLength
                                     bytes were transferred by OutDataBuffer.
  @retval EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number
                                     of bytes that could be transferred is returned
                                     in InTransferLength. For write and bi-directional
                                     commands, OutTransferLength bytes were transferred
                                     by OutDataBuffer.
  @retval EFI_NOT_READY              The ATA command could not be sent because
                                     there are too many ATA commands already
                                     queued. The caller may retry again later.
  @retval EFI_DEVICE_ERROR           A device error occurred while attempting
                                     to send the ATA command.
  @retval EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents
                                     of Acb are invalid. The ATA command was
                                     not sent, so no additional status information
                                     is available.

**/
EFI_STATUS
EFIAPI
AtaPassThruPassThruExecute (
  IN     UINT16                           Port,
  IN     UINT16                           PortMultiplierPort,
  IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet,
  IN     PEI_ATA_PASS_THRU_INSTANCE       *Instance,
  IN     ATA_NONBLOCK_TASK                *Task OPTIONAL
  )
{
  EFI_ATA_PASS_THRU_CMD_PROTOCOL  Protocol;
  EFI_ATA_HC_WORK_MODE            Mode;
  EFI_STATUS                      Status;

  Protocol = Packet->Protocol;

  Mode = Instance->Mode;
  switch (Mode) {
    case EfiAtaAhciMode :
      if (PortMultiplierPort == 0xFFFF) {
        //
        // If there is no port multiplier, PortMultiplierPort will be 0xFFFF
        // according to UEFI spec. Here, we convert its value to 0 to follow
        // AHCI spec.
        //
        PortMultiplierPort = 0;
      }
      switch (Protocol) {
        case EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA:
          Status = AhciNonDataTransfer (
                     &Instance->AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplierPort,
                     NULL,
                     0,
                     Packet->Acb,
                     Packet->Asb,
                     Packet->Timeout,
                     Task
                     );
          break;
        case EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN:
          Status = AhciPioTransfer (
                     &Instance->AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplierPort,
                     NULL,
                     0,
                     TRUE,
                     Packet->Acb,
                     Packet->Asb,
                     Packet->InDataBuffer,
                     Packet->InTransferLength,
                     Packet->Timeout
                     );
          break;
        case EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT:
          Status = AhciPioTransfer (
                     &Instance->AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplierPort,
                     NULL,
                     0,
                     FALSE,
                     Packet->Acb,
                     Packet->Asb,
                     Packet->OutDataBuffer,
                     Packet->OutTransferLength,
                     Packet->Timeout
                     );
          break;
        case EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN:
          Status = AhciDmaTransfer (
                     Instance,
                     &Instance->AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplierPort,
                     NULL,
                     0,
                     TRUE,
                     Packet->Acb,
                     Packet->Asb,
                     Packet->InDataBuffer,
                     Packet->InTransferLength,
                     Packet->Timeout,
                     Task
                     );
          break;
        case EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT:
          Status = AhciDmaTransfer (
                     Instance,
                     &Instance->AhciRegisters,
                     (UINT8)Port,
                     (UINT8)PortMultiplierPort,
                     NULL,
                     0,
                     FALSE,
                     Packet->Acb,
                     Packet->Asb,
                     Packet->OutDataBuffer,
                     Packet->OutTransferLength,
                     Packet->Timeout,
                     Task
                     );
          break;
        default :
          return EFI_UNSUPPORTED;
      }
      break;

    default:
      Status = EFI_DEVICE_ERROR;
      break;
  }

  return Status;
}

/**
  Traverse the attached ATA devices list to find out the device to access.

  @param[in]  Instance            A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.
  @param[in]  Port                The port number of the ATA device to send the command.
  @param[in]  PortMultiplierPort  The port multiplier port number of the ATA device to send the command.
                                  If there is no port multiplier, then specify 0xFFFF.
  @param[in]  DeviceType          The device type of the ATA device.

  @retval     The pointer to the data structure of the device info to access.

**/
LIST_ENTRY *
EFIAPI
SearchDeviceInfoList (
  IN  PEI_ATA_PASS_THRU_INSTANCE     *Instance,
  IN  UINT16                         Port,
  IN  UINT16                         PortMultiplier,
  IN  EFI_ATA_DEVICE_TYPE            DeviceType
  )
{
  EFI_ATA_DEVICE_INFO  *DeviceInfo;
  LIST_ENTRY           *Node;

  Node = GetFirstNode (&Instance->DeviceList);
  while (!IsNull (&Instance->DeviceList, Node)) {
    DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

    //
    // For CD-ROM working in the AHCI mode, only 8 bits are used to record
    // the PortMultiplier information. If the CD-ROM is directly attached
    // on a SATA port, the PortMultiplier should be translated from 0xFF
    // to 0xFFFF according to the UEFI spec.
    //
    if ((Instance->Mode == EfiAtaAhciMode) &&
        (DeviceInfo->Type == EfiIdeCdrom) &&
        (PortMultiplier == 0xFF)) {
        PortMultiplier = 0xFFFF;
    }

    if ((DeviceInfo->Type == DeviceType) &&
        (Port == DeviceInfo->Port) &&
        (PortMultiplier == DeviceInfo->PortMultiplier)) {
      return Node;
    }

    Node = GetNextNode (&Instance->DeviceList, Node);
  }

  return NULL;
}

/**
  Allocate device info data structure to contain device info.
  And insert the data structure to the tail of device list for tracing.

  @param[in]  Instance            A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.
  @param[in]  Port                The port number of the ATA device to send the command.
  @param[in]  PortMultiplierPort  The port multiplier port number of the ATA device to send the command.
                                  If there is no port multiplier, then specify 0xFFFF.
  @param[in]  DeviceType          The device type of the ATA device.
  @param[in]  IdentifyData        The data buffer to store the output of the IDENTIFY cmd.

  @retval EFI_SUCCESS             Successfully insert the ata device to the tail of device list.
  @retval EFI_OUT_OF_RESOURCES    Can not allocate enough resource for use.

**/
EFI_STATUS
EFIAPI
CreateNewDeviceInfo (
  IN  PEI_ATA_PASS_THRU_INSTANCE     *Instance,
  IN  UINT16                         Port,
  IN  UINT16                         PortMultiplier,
  IN  EFI_ATA_DEVICE_TYPE            DeviceType,
  IN  EFI_IDENTIFY_DATA              *IdentifyData
  )
{
  EFI_ATA_DEVICE_INFO  *DeviceInfo;

  DeviceInfo = AllocateZeroPool (sizeof (EFI_ATA_DEVICE_INFO));

  if (DeviceInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  DeviceInfo->Signature      = PEI_ATA_DEVICE_SIGNATURE;
  DeviceInfo->Port           = Port;
  DeviceInfo->PortMultiplier = PortMultiplier;
  DeviceInfo->Type           = DeviceType;

  if (IdentifyData != NULL) {
    DeviceInfo->IdentifyData = AllocateCopyPool (sizeof (EFI_IDENTIFY_DATA), IdentifyData);
    if (DeviceInfo->IdentifyData == NULL) {
      FreePool (DeviceInfo);
      return EFI_OUT_OF_RESOURCES;
    }
  }

  InsertTailList (&Instance->DeviceList, &DeviceInfo->Link);
  DEBUG ((DEBUG_INFO, "CreateNewDeviceInfo: port [%d] port mulitplier [%d] has a [%a]\n", Port, 0, DeviceType == EfiIdeCdrom ? "cdrom" : "harddisk"));

  return EFI_SUCCESS;
}

/**
  Destroy all attached ATA devices info.

  @param[in]  Instance          A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.

**/
VOID
EFIAPI
DestroyDeviceInfoList (
  IN  PEI_ATA_PASS_THRU_INSTANCE  *Instance
  )
{
  EFI_ATA_DEVICE_INFO  *DeviceInfo;
  LIST_ENTRY           *Node;

  Node = GetFirstNode (&Instance->DeviceList);
  while (!IsNull (&Instance->DeviceList, Node)) {
    DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

    Node = GetNextNode (&Instance->DeviceList, Node);

    RemoveEntryList (&DeviceInfo->Link);
    if (DeviceInfo->IdentifyData != NULL) {
      FreePool (DeviceInfo->IdentifyData);
    }
    FreePool (DeviceInfo);
  }
}


/**
  Sends an ATA command to an ATA device that is attached to the ATA controller. This function
  supports both blocking I/O and non-blocking I/O. The blocking I/O functionality is required,
  and the non-blocking I/O functionality is optional.

  @param[in]      This               A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in]      Port               The port number of the ATA device to send the command.
  @param[in]      PortMultiplierPort The port multiplier port number of the ATA device to send the command.
                                     If there is no port multiplier, then specify 0xFFFF.
  @param[in, out] Packet             A pointer to the ATA command to send to the ATA device specified by Port
                                     and PortMultiplierPort.

  @retval EFI_SUCCESS                The ATA command was sent by the host. For bi-directional commands,
                                     InTransferLength bytes were transferred from InDataBuffer. For write and
                                     bi-directional commands, OutTransferLength bytes were transferred by OutDataBuffer.
  @retval EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                     is returned in InTransferLength. For write and bi-directional commands,
                                     OutTransferLength bytes were transferred by OutDataBuffer.
  @retval EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                     already queued. The caller may retry again later.
  @retval EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                     command was not sent, so no additional status information is available.

**/
EFI_STATUS
EFIAPI
PeiAtaPassThruPassThru (
  IN     PEI_ATA_PASS_THRU_PPI            *This,
  IN     UINT16                           Port,
  IN     UINT16                           PortMultiplierPort,
  IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet
  )
{
  PEI_ATA_PASS_THRU_INSTANCE      *Instance;
  LIST_ENTRY                      *Node;
  EFI_ATA_DEVICE_INFO             *DeviceInfo;
  EFI_IDENTIFY_DATA               *IdentifyData;
  UINT64                          Capacity;
  UINT32                          MaxSectorCount;
  UINT32                          BlockSize;

  Instance = PEI_ATA_PASS_THRU_PRIVATE_DATA_FROM_THIS (This);

  if ((This->Mode->IoAlign > 1) && !IS_ALIGNED(Packet->InDataBuffer, This->Mode->IoAlign)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((This->Mode->IoAlign > 1) && !IS_ALIGNED(Packet->OutDataBuffer, This->Mode->IoAlign)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((This->Mode->IoAlign > 1) && !IS_ALIGNED(Packet->Asb, This->Mode->IoAlign)) {
    return EFI_INVALID_PARAMETER;
  }

  Node = SearchDeviceInfoList (Instance, Port, PortMultiplierPort, EfiIdeHarddisk);
  if (Node == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //if (Node == NULL) {
  //  Node = SearchDeviceInfoList(Instance, Port, PortMultiplierPort, EfiIdeCdrom);
  //  if (Node == NULL) {
  //    return EFI_INVALID_PARAMETER;
  //  }
  //}

  //
  // Check whether this device needs 48-bit addressing (ATAPI-6 ata device).
  // Per ATA-6 spec, word83: bit15 is zero and bit14 is one.
  // If bit10 is one, it means the ata device support 48-bit addressing.
  //
  DeviceInfo     = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);
  IdentifyData   = DeviceInfo->IdentifyData;
  MaxSectorCount = 0x100;
  if ((IdentifyData->AtaData.command_set_supported_83 & (BIT10 | BIT15 | BIT14)) == 0x4400) {
    Capacity = *((UINT64 *)IdentifyData->AtaData.maximum_lba_for_48bit_addressing);
    if (Capacity > 0xFFFFFFF) {
      //
      // Capacity exceeds 120GB. 48-bit addressing is really needed
      // In this case, the max sector count is 0x10000
      //
      MaxSectorCount = 0x10000;
    }
  }

  BlockSize = 0x200;
  if ((IdentifyData->AtaData.phy_logic_sector_support & (BIT14 | BIT15)) == BIT14) {
    //
    // Check logical block size
    //
    if ((IdentifyData->AtaData.phy_logic_sector_support & BIT12) != 0) {
      BlockSize = (UINT32) (((IdentifyData->AtaData.logic_sector_size_hi << 16) | IdentifyData->AtaData.logic_sector_size_lo) * sizeof (UINT16));
    }
  }

  //
  // convert the transfer length from sector count to byte.
  //
  if (((Packet->Length & EFI_ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
       (Packet->InTransferLength != 0)) {
    Packet->InTransferLength = Packet->InTransferLength * BlockSize;
  }

  //
  // convert the transfer length from sector count to byte.
  //
  if (((Packet->Length & EFI_ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
       (Packet->OutTransferLength != 0)) {
    Packet->OutTransferLength = Packet->OutTransferLength * BlockSize;
  }

  //
  // If the data buffer described by InDataBuffer/OutDataBuffer and InTransferLength/OutTransferLength
  // is too big to be transferred in a single command, then no data is transferred and EFI_BAD_BUFFER_SIZE
  // is returned.
  //
  if (((Packet->InTransferLength != 0) && (Packet->InTransferLength > MaxSectorCount * BlockSize)) ||
      ((Packet->OutTransferLength != 0) && (Packet->OutTransferLength > MaxSectorCount * BlockSize))) {
    return EFI_BAD_BUFFER_SIZE;
  }

  return AtaPassThruPassThruExecute (
           Port,
           PortMultiplierPort,
           Packet,
           Instance,
           NULL
           );

}

/**
  Used to retrieve the list of legal port numbers for ATA devices on an ATA controller.
  These can either be the list of ports where ATA devices are actually present or the
  list of legal port numbers for the ATA controller. Regardless, the caller of this
  function must probe the port number returned to see if an ATA device is actually
  present at that location on the ATA controller.

  The GetNextPort() function retrieves the port number on an ATA controller. If on input
  Port is 0xFFFF, then the port number of the first port on the ATA controller is returned
  in Port and EFI_SUCCESS is returned.

  If Port is a port number that was returned on a previous call to GetNextPort(), then the
  port number of the next port on the ATA controller is returned in Port, and EFI_SUCCESS
  is returned. If Port is not 0xFFFF and Port was not returned on a previous call to
  GetNextPort(), then EFI_INVALID_PARAMETER is returned.

  If Port is the port number of the last port on the ATA controller, then EFI_NOT_FOUND is
  returned.

  @param[in]     This           A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in,out] Port           On input, a pointer to the port number on the ATA controller.
                                On output, a pointer to the next port number on the ATA
                                controller. An input value of 0xFFFF retrieves the first port
                                number on the ATA controller.

  @retval EFI_SUCCESS           The next port number on the ATA controller was returned in Port.
  @retval EFI_NOT_FOUND         There are no more ports on this ATA controller.
  @retval EFI_INVALID_PARAMETER Port is not 0xFFFF and Port was not returned on a previous call
                                to GetNextPort().

**/
EFI_STATUS
EFIAPI
PeiAtaPassThruGetNextPort (
  IN PEI_ATA_PASS_THRU_PPI      *This,
  IN OUT UINT16                 *Port
  )
{
  PEI_ATA_PASS_THRU_INSTANCE      *Instance;
  LIST_ENTRY                      *Node;
  EFI_ATA_DEVICE_INFO             *DeviceInfo;

  Instance = PEI_ATA_PASS_THRU_PRIVATE_DATA_FROM_THIS (This);

  if (Port == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (*Port == 0xFFFF) {
    //
    // If the Port is all 0xFF's, start to traverse the device list from the beginning
    //
    Node = GetFirstNode (&Instance->DeviceList);

    while (!IsNull (&Instance->DeviceList, Node)) {
      DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

      if (DeviceInfo->Type == EfiIdeHarddisk) {
        *Port = DeviceInfo->Port;
        goto Exit;
      }

      Node = GetNextNode (&Instance->DeviceList, Node);
    }

    return EFI_NOT_FOUND;
  } else if (*Port == Instance->PreviousPort) {
    Node = GetFirstNode (&Instance->DeviceList);

    while (!IsNull (&Instance->DeviceList, Node)) {
      DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

      if ((DeviceInfo->Type == EfiIdeHarddisk) &&
           (DeviceInfo->Port > *Port)){
        *Port = DeviceInfo->Port;
        goto Exit;
      }

      Node = GetNextNode (&Instance->DeviceList, Node);
    }

    return EFI_NOT_FOUND;
  } else {
    //
    // Port is not equal to 0xFFFF and also not equal to previous return value
    //
    return EFI_INVALID_PARAMETER;
  }

Exit:
  //
  // Update the PreviousPort and PreviousPortMultiplier.
  //
  Instance->PreviousPort = *Port;

  return EFI_SUCCESS;
}

/**
  Used to retrieve the list of legal port multiplier port numbers for ATA devices on a port of an ATA
  controller. These can either be the list of port multiplier ports where ATA devices are actually
  present on port or the list of legal port multiplier ports on that port. Regardless, the caller of this
  function must probe the port number and port multiplier port number returned to see if an ATA
  device is actually present.

  The GetNextDevice() function retrieves the port multiplier port number of an ATA device
  present on a port of an ATA controller.

  If PortMultiplierPort points to a port multiplier port number value that was returned on a
  previous call to GetNextDevice(), then the port multiplier port number of the next ATA device
  on the port of the ATA controller is returned in PortMultiplierPort, and EFI_SUCCESS is
  returned.

  If PortMultiplierPort points to 0xFFFF, then the port multiplier port number of the first
  ATA device on port of the ATA controller is returned in PortMultiplierPort and
  EFI_SUCCESS is returned.

  If PortMultiplierPort is not 0xFFFF and the value pointed to by PortMultiplierPort
  was not returned on a previous call to GetNextDevice(), then EFI_INVALID_PARAMETER
  is returned.

  If PortMultiplierPort is the port multiplier port number of the last ATA device on the port of
  the ATA controller, then EFI_NOT_FOUND is returned.

  @param[in]      This               A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in]      Port               The port number present on the ATA controller.
  @param[in, out] PortMultiplierPort On input, a pointer to the port multiplier port number of an
                                     ATA device present on the ATA controller.
                                     If on input a PortMultiplierPort of 0xFFFF is specified,
                                     then the port multiplier port number of the first ATA device
                                     is returned. On output, a pointer to the port multiplier port
                                     number of the next ATA device present on an ATA controller.

  @retval EFI_SUCCESS                The port multiplier port number of the next ATA device on the port
                                     of the ATA controller was returned in PortMultiplierPort.
  @retval EFI_NOT_FOUND              There are no more ATA devices on this port of the ATA controller.
  @retval EFI_INVALID_PARAMETER      PortMultiplierPort is not 0xFFFF, and PortMultiplierPort was not
                                     returned on a previous call to GetNextDevice().

**/
EFI_STATUS
EFIAPI
PeiAtaPassThruGetNextDevice (
  IN PEI_ATA_PASS_THRU_PPI      *This,
  IN UINT16                     Port,
  IN OUT UINT16                 *PortMultiplierPort
  )
{
  PEI_ATA_PASS_THRU_INSTANCE      *Instance;
  LIST_ENTRY                      *Node;
  EFI_ATA_DEVICE_INFO             *DeviceInfo;

  Instance = PEI_ATA_PASS_THRU_PRIVATE_DATA_FROM_THIS (This);

  if (PortMultiplierPort == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Instance->PreviousPortMultiplier == 0xFFFF) {
    //
    // If a device is directly attached on a port, previous call to this
    // function will return the value 0xFFFF for PortMultiplierPort. In
    // this case, there should be no more device on the port multiplier.
    //
    Instance->PreviousPortMultiplier = 0;
    return EFI_NOT_FOUND;
  }

  if (*PortMultiplierPort == Instance->PreviousPortMultiplier) {
    Node = GetFirstNode (&Instance->DeviceList);

    while (!IsNull (&Instance->DeviceList, Node)) {
      DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

      if ((DeviceInfo->Type == EfiIdeHarddisk) &&
           (DeviceInfo->Port == Port) &&
           (DeviceInfo->PortMultiplier > *PortMultiplierPort)){
        *PortMultiplierPort = DeviceInfo->PortMultiplier;
        goto Exit;
      }

      Node = GetNextNode (&Instance->DeviceList, Node);
    }

    return EFI_NOT_FOUND;
  } else if (*PortMultiplierPort == 0xFFFF) {
    //
    // If the PortMultiplierPort is all 0xFF's, start to traverse the device list from the beginning
    //
    Node = GetFirstNode (&Instance->DeviceList);

    while (!IsNull (&Instance->DeviceList, Node)) {
      DeviceInfo = PEI_ATA_DEVICE_INFO_FROM_THIS (Node);

      if ((DeviceInfo->Type == EfiIdeHarddisk) &&
           (DeviceInfo->Port == Port)){
        *PortMultiplierPort = DeviceInfo->PortMultiplier;
        goto Exit;
      }

      Node = GetNextNode (&Instance->DeviceList, Node);
    }

    return EFI_NOT_FOUND;
  } else {
    //
    // PortMultiplierPort is not equal to 0xFFFF and also not equal to previous return value
    //
    return EFI_INVALID_PARAMETER;
  }

Exit:
  //
  // Update the PreviousPort and PreviousPortMultiplier.
  //
  Instance->PreviousPortMultiplier = *PortMultiplierPort;

  return EFI_SUCCESS;
}

/**
  Initializes the ATA passthru PPI.

  @param[in]  FileHandle           Handle of the file being invoked.
  @param[in]  PeiServices          Describes the list of possible PEI Services.

  @retval     EFI_SUCCESS          Operation performed successfully.
  @retval     EFI_OUT_OF_RESOURCES Not enough memory to allocate.
  @retval     Others               Failed to initialize AtaPassThru PPI

**/
EFI_STATUS
EFIAPI
InitializeAtaPassThru (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  PEI_ATA_HOST_CONTROLLER_PPI       *AtaHcPpi;
  EFI_STATUS                        Status;
  PEI_ATA_PASS_THRU_INSTANCE        *Instance;

  //Status = PeiServicesRegisterForShadow (FileHandle);
  //if (!EFI_ERROR (Status)) {
  //  return Status;
  //}

  Status = PeiServicesLocatePpi (
             &gPeiAtaHostControllerPpiGuid,
             0,
             NULL,
             (VOID **) &AtaHcPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  Status = AtaHcPpi->GetAtaControllerInfo (
                       (EFI_PEI_SERVICES **) PeiServices,
                       AtaHcPpi,
                       0,
                       &mAhciBar
                       );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "InitializeAtaPassThru: Ata host MMIO address.= 0x%x\n", mAhciBar));

  Instance = AllocateCopyPool (sizeof (PEI_ATA_PASS_THRU_INSTANCE), &gPeiAtaPassThruPrivateTemplate);
  if (Instance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Instance->PeiAtaPassThruPpi.Mode    = &Instance->AtaPassThruMode;
  Instance->PeiAtaPassThruPpiList.Ppi = (VOID*)&Instance->PeiAtaPassThruPpi;
  Instance->MmioBase                  = mAhciBar;
  Instance->Mode                      = EfiAtaAhciMode;

  //
  // Initial device List
  //
  InitializeListHead (&Instance->DeviceList);

  Status = AhciModeInitialization (Instance);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  Status = PeiServicesInstallPpi (&Instance->PeiAtaPassThruPpiList);

  return Status;
}
