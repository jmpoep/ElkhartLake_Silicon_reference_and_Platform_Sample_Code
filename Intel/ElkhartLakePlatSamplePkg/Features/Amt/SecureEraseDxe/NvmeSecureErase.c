/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "NvmeSecureErase.h"
#include "Ui.h"

/**
  Function checks which Secure Erase operations should be conducted.

  @retval          NoEraseMode         Secure Erase should not be conducted at all.
  @retval          UserDataEraseMode   Only User Data Erase should be conducted.
  @retval          FullEraseMode       Both User Data Erase and Cryptographic Erase
                                       should be conducted.
**/
SECURE_ERASE_MODE
GetSecureEraseMode (
  IN  EFI_HANDLE                        Handle,
  IN  NVME_ADMIN_CONTROLLER_DATA        *ControllerData
  )
{
  EFI_STATUS                           Status;
  EFI_PCI_IO_PROTOCOL                  *PciIo;
  UINT16                               DeviceId;
  UINT16                               VendorId;
  UINT16                               SubsystemId;
  UINT16                               SubsystemVendorId;

  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo
                  );
  if (!EFI_ERROR (Status)) {

    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_VENDOR_ID_OFFSET, 1, &VendorId);
    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_DEVICE_ID_OFFSET, 1, &DeviceId);

    DEBUG ((DEBUG_INFO, "VendorID: 0x%04X DeviceId: 0x%04X\n",VendorId, DeviceId));
    DEBUG ((DEBUG_INFO, "ControllerData.Oacs = 0x%04X\n",ControllerData->Oacs));
    DEBUG ((DEBUG_INFO, "ControllerData.Fna = 0x%02X\n",ControllerData->Fna));

    if (!(ControllerData->Oacs & FORMAT_NVM_SUPPORTED)) {
      DEBUG ((DEBUG_INFO, "NvmeSecureErase: Format NVM Command not supported\n"));
      return NoEraseMode;
    } else {
      // Cryptographic Erase may only be skipped for Stony Beach v1. For other drives,
      // which does not support Cryptographic Erase, Secure Erase should fail.
      if (VendorId == INTEL_VENDOR_ID && DeviceId == STONY_BEACH_V1_DEVICE_ID) {
        PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_SUBSYSTEM_VENDOR_ID_OFFSET, 1, &SubsystemVendorId);
        PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_SUBSYSTEM_ID_OFFSET, 1, &SubsystemId);
        DEBUG ((DEBUG_INFO, "SubsystemVendorId: 0x%04X SubsystemId: 0x%04X\n",SubsystemVendorId, SubsystemId));
        if (SubsystemVendorId == INTEL_VENDOR_ID &&
           (SubsystemId == STONY_BEACH_V1_MIN_SSID || SubsystemId == STONY_BEACH_V1_MAX_SSID)) {
          DEBUG ((DEBUG_INFO, "NvmeSecureErase: User Data Erase Mode\n"));
          return UserDataEraseMode;
        }
      }
      if (!(ControllerData->Fna & CRYPTOGRAPHIC_ERASE_SUPPORTED)) {
        DEBUG ((DEBUG_INFO, "NvmeSecureErase: Cryptographic Erase not supported\n"));
        return NoEraseMode;
      }
    }
    DEBUG ((DEBUG_INFO, "NvmeSecureErase: Full Erase Mode\n"));
    return FullEraseMode;
    }
  return NoEraseMode;
}


/**
  Get identify controller data.

  @param[in]   NvmeDevice       The pointer to the NVME_PASS_THRU_DEVICE data structure.
  @param[in]   NamespaceId      NamespaceId for an NVM Express namespace present on the NVM Express controller
  @param[out]  Buffer           The buffer used to store the identify controller data.

  @return EFI_SUCCESS           Successfully get the identify controller data.
  @return EFI_DEVICE_ERROR      Fail to get the identify controller data.

**/
EFI_STATUS
NvmeIdentifyController (
  IN  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NvmeDevice,
  IN  UINT32                                NamespaceId,
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

  DEBUG ((DEBUG_INFO, "NvmeSecureErase: Sending Identify Command\n"));

  Command.Cdw0.Opcode          = NVME_ADMIN_IDENTIFY_CMD;

  Command.Nsid                 = NamespaceId;

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;
  CommandPacket.TransferBuffer = Buffer;
  CommandPacket.TransferLength = sizeof (NVME_ADMIN_CONTROLLER_DATA);
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;
  //
  // Set bit 0 (Cns bit) to 1 to identify a controller
  //
  Command.Cdw10                = 1;
  Command.Flags                = CDW10_VALID;

  Status = NvmeDevice->PassThru (NvmeDevice, NamespaceId, &CommandPacket, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeSecureErase: Identify Command Status=%r\n", Status));
  }

  return Status;
}


/**
  Perform Nvme User Data Erase.

  @param[in]  NvmeDevice             The pointer to the NVME_PASS_THRU_DEVICE data structure.
  @param[in]  NamespaceId            NamespaceId for an NVM Express namespace present on the NVM Express controller
  @param[in]  SecureEraseSettings    Type of the Secure Erase operation

  @retval     EFI_SUCCESS            Successfully performed secure erase operation.
  @retval     EFI_NOT_READY          The NVM Express Command Packet could not be sent because the controller is not ready.
  @retval     EFI_DEVICE_ERROR       A device error occurred while attempting to send the NVM Express Command Packet.
  @retval     EFI_INVALID_PARAMETER  NamespaceId or the contents of EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET are invalid.
  @retval     EFI_UNSUPPORTED        The command described by the NVM Express Command Packet is not supported by the NVM Express
  @retval     EFI_TIMEOUT            A timeout occurred while waiting for the NVM Express Command Packet to execute.
**/
EFI_STATUS
NvmeFormatNvmCommand (
  IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *NvmeDevice,
  IN UINT32                                NamespaceId,
  IN UINT32                                SecureEraseSettings
  )
{
  EFI_STATUS                               Status;
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  NVME_ADMIN_FORMAT_NVM                    FormatNvm;

  ZeroMem (&CommandPacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof(EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof(EFI_NVM_EXPRESS_COMPLETION));
  ZeroMem (&FormatNvm, sizeof(NVME_ADMIN_FORMAT_NVM));

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;

  Command.Nsid                 = NamespaceId;
  Command.Cdw0.Opcode          = NVME_ADMIN_FORMAT_NVM_CMD;
  CommandPacket.CommandTimeout = NVME_FORMAT_NVM_CMD_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;
  FormatNvm.Ses                = SecureEraseSettings;
  CopyMem (&CommandPacket.NvmeCmd->Cdw10, &FormatNvm, sizeof (NVME_ADMIN_FORMAT_NVM));
  CommandPacket.NvmeCmd->Flags = CDW10_VALID;

  Status = NvmeDevice->PassThru (NvmeDevice, Command.Nsid, &CommandPacket, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeSecureErase: FormatNvmCommand Status=%r\n", Status));
  }

  return Status;
}

/**
  Attempts to erase a device specified by a given device path protocol

  @param[in]       NvmeDevice             The pointer to the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL.
  @param[in]       NamespaceId            NamespaceId for an NVM Express namespace present on the NVM Express controller
  @param[in]       SecureEraseMode        Secure Erase Mode defining Secure Erase Operations to be conducted

  @retval          EFI_SUCCESS            Secure Erase Commands were processed successfully.
  @retval          EFI_NOT_READY          The NVM Express Command Packet could not be sent because the controller is not ready.
  @retval          EFI_DEVICE_ERROR       A device error occurred while attempting to send the NVM Express Command Packet.
  @retval          EFI_INVALID_PARAMETER  NamespaceId or the contents of EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET are invalid.
  @retval          EFI_UNSUPPORTED        The command described by the NVM Express Command Packet is not supported by the NVM Express
  @retval          EFI_TIMEOUT            A timeout occurred while waiting for the NVM Express Command Packet to execute.

  @retval          Others                 Secure Erase has failed
**/
EFI_STATUS
SendNvmeSecureEraseCommands (
  IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   *NvmeDevice,
  IN UINT32                               NamespaceId,
  IN SECURE_ERASE_MODE                    SecureEraseMode
  )
{
  EFI_STATUS                          Status;

  if (SecureEraseMode == NoEraseMode) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "NvmeSecureErase: Performing Secure Erase operations on NamespaceId = 0x%08X\n", NamespaceId));

  DEBUG ((DEBUG_INFO, "NvmeSecureErase: Performing User Data Erase\n"));
  ProgressBarDialog (L"Nvme Secure Erase in progress...");
  Status = NvmeFormatNvmCommand (NvmeDevice, NamespaceId, FORMAT_NVM_USER_DATA_ERASE);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (SecureEraseMode != UserDataEraseMode) {
    DEBUG ((DEBUG_INFO, "NvmeSecureErase: Performing Cryptographic Erase\n"));
    Status = NvmeFormatNvmCommand (NvmeDevice, NamespaceId, FORMAT_NVM_CRYPTOGRAPHIC_ERASE);
  }

  return Status ;
}

/**
  Searches device handles for NvmExpressPassThru protocol and erases devices
  which have this protocol installed.

  @retval          EFI_SUCCESS         Nvme Device was erased successfully or there were no devices to erase.
  @retval          EFI_NOT_FOUND       No NvmExpressPassThru protocol found
  @retval          Others              An error occurred during Secure Erase operation
**/
EFI_STATUS
EraseNvmeDevice (
  VOID
  )
{
  EFI_STATUS                           Status;
  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   *NvmeDevice;
  NVME_ADMIN_CONTROLLER_DATA           ControllerData;
  UINTN                                HandleNum;
  EFI_HANDLE                           *NvmePassThruHandles;
  UINTN                                Index;
  UINT32                               NamespaceId;
  SECURE_ERASE_MODE                    SecureEraseMode;

  DEBUG ((DEBUG_INFO, "NvmeSecureErase:: EraseNvmeDevice start\n"));

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiNvmExpressPassThruProtocolGuid,
                  NULL,
                  &HandleNum,
                  &NvmePassThruHandles
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "gBS->LocateHandleBuffer: Status=%r\n", Status));
    if (Status == EFI_NOT_FOUND) {
      return EFI_SUCCESS;
    } else {
      return Status;
    }
  }
  DEBUG ((DEBUG_INFO, "Number of detected NVMe Handles: %d\n", HandleNum));

  for (Index = 0; Index < HandleNum; Index++) {

    Status = gBS->HandleProtocol (
                    NvmePassThruHandles[Index],
                    &gEfiNvmExpressPassThruProtocolGuid,
                    (VOID **) &NvmeDevice
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "gBS->HandleProtocol: Status=%r\n", Status));
      continue;
    }

    NamespaceId = NVME_ALL_NAMESPACES;

    while (TRUE) {
      Status = NvmeDevice->GetNextNamespace (NvmeDevice, &NamespaceId);
      if (EFI_ERROR (Status)) {
        if (Status == EFI_NOT_FOUND) {
          Status = EFI_SUCCESS;
          break;
        } else {
          return Status;
        }
      }

      //
      // Due to the fact that RAID Driver expects other value of NamespaceId parameter than AHCI driver,
      // need to send the Identify Controller command twice - once with the NamespaceId retrieved
      // using GetNextNamespace. If it fails we need to set NamespaceId = 0.
      //
      ZeroMem (&ControllerData, sizeof(NVME_ADMIN_CONTROLLER_DATA));
      Status = NvmeIdentifyController (NvmeDevice, NamespaceId, (VOID *) &ControllerData);
      if (EFI_ERROR (Status)) {
        Status = NvmeIdentifyController (NvmeDevice, NVME_CONTROLLER_ID, (VOID *) &ControllerData);
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }

      SecureEraseMode = GetSecureEraseMode (NvmePassThruHandles[Index], &ControllerData);

      Status = SendNvmeSecureEraseCommands (NvmeDevice, NamespaceId, SecureEraseMode);
      if (EFI_ERROR (Status)) {
        return Status;
      }

    }

  }

  FreePool (NvmePassThruHandles);

  return Status;
}
