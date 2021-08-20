/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#include "AtaSecureErase.h"
#include "Ui.h"

CHAR8                                  mDefaultPassStr[] = "AIMIEJEGOCZTERDZIESCICZTERY";

/**
  Sends an ATA command packet using a given ata pass thru device

  @param[in]       AtaDevice                  The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Packet                     Ata packet to be send
  @param[in]       Port                       Port number on the ATA controller
  @param[in]       PortMultiplierPort         Port multiplier port number on the ATA controller
  @param[in]       Event                      Efi event to be used when non blocking I/O is supported

  @retval          EFI_SUCCESS
  @retval          EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                              is returned in InTransferLength. For write and bi-directional commands,
                                              OutTransferLength bytes were transferred by OutDataBuffer.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.

**/
EFI_STATUS
SendAtaCommand (
  IN EFI_ATA_PASS_THRU_PROTOCOL       *AtaDevice,
  IN EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet,
  IN UINT16                            Port,
  IN UINT16                            PortMultiplierPort,
  IN OUT EFI_EVENT                     Event OPTIONAL
  )
{
  EFI_STATUS                           Status;

  Status = AtaDevice->PassThru (
                        AtaDevice,
                        Port,
                        PortMultiplierPort,
                        Packet,
                        NULL
                        );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "\tError! Port=0x%04X, multiplier=0x%04X .Status=%r\n", Port, PortMultiplierPort, Status));
    DEBUG ((DEBUG_ERROR, "AtaStatus = %02X\n", Packet->Asb->AtaStatus));
    DEBUG ((DEBUG_ERROR, "AtaError = %02X\n", Packet->Asb->AtaError));
  }
  return Status;
}

/**
  Get HDD identify data.

  @param[in]          AtaDevice           The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]          Port                Port number on the ATA controller
  @param[in]          PortMultiplierPort  Port multiplier port number on the ATA controller
  @param[out]         ControllerData      The buffer used to store the identify controller data.

  @return             EFI_SUCCESS         Successfully get the identify controller data.
  @return             EFI_DEVICE_ERROR    Fail to get the identify controller data.

**/
EFI_STATUS
GetHddIdentifyData (
  IN EFI_ATA_PASS_THRU_PROTOCOL            *AtaDevice,
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

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  return Status;
}


/**
  Attempt to unlock the ATA device using supplied password

  @param[in]       Device              Device to unlock
  @param[in]       Password            32 character wide CHAR16 array containing the password

  @retval          EFI_SUCCESS                The device is unlocked
  @retval          EFI_DEVICE_ERROR           Either the device rejected the password or there was some other hardware problem
  @retval          EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                              is returned in InTransferLength. For write and bi-directional commands,
                                              OutTransferLength bytes were transferred by OutDataBuffer.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.
**/
EFI_STATUS
SendHddUnlockCommand (
  IN EFI_ATA_PASS_THRU_PROTOCOL            *AtaDevice,
  IN UINT16                                 Port,
  IN UINT16                                 PortMultiplierPort,
  IN CHAR8                                  Password[ATA_PASSWORD_MAX_LENGTH + 1]
  )
{
  EFI_STATUS                           Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET     Packet;
  EFI_ATA_COMMAND_BLOCK                Acb;
  EFI_ATA_STATUS_BLOCK                 Asb;
  ATA_UNLOCK_COMMAND_BLOCK             SecurityUnlock;

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));
  ZeroMem (&SecurityUnlock, sizeof(ATA_UNLOCK_COMMAND_BLOCK));

  SecurityUnlock.ControlData = ATA_SECURITY_ERASE_UNIT_COMPARE_ADMIN_PASSWORD;
  CopyMem (SecurityUnlock.Password, Password, ATA_PASSWORD_MAX_LENGTH);
  Acb.AtaCommand           = ATA_SECURITY_UNLOCK_CMD;

  Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT;
  Packet.Acb               = &Acb;
  Packet.Asb               = &Asb;
  Packet.OutDataBuffer     = &SecurityUnlock;
  Packet.OutTransferLength = sizeof (ATA_UNLOCK_COMMAND_BLOCK);
  Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Timeout           = EFI_TIMER_PERIOD_SECONDS (3);

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  ZeroMem (&SecurityUnlock, sizeof(ATA_UNLOCK_COMMAND_BLOCK));

  DEBUG ((DEBUG_INFO, "SendHddUnlockCommand :: Status %r \n", Status));

  return Status;

}

/**
  Sends prepare secure erase ATA command

  @param[in]       AtaDevice                  The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Port                       Port number on the ATA controller
  @param[in]       PortMultiplierPort         Port multiplier port number on the ATA controller

  @retval          EFI_SUCCESS
  @retval          EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                              is returned in InTransferLength. For write and bi-directional commands,
                                              OutTransferLength bytes were transferred by OutDataBuffer.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.

**/
EFI_STATUS
PrepareSecureErase (
  IN EFI_ATA_PASS_THRU_PROTOCOL            *AtaDevice,
  IN UINT16                                 Port,
  IN UINT16                                 PortMultiplierPort
  )
{
  EFI_STATUS                                Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET          Packet;
  EFI_ATA_COMMAND_BLOCK                     Acb;
  EFI_ATA_STATUS_BLOCK                      Asb;

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));

  DEBUG ((DEBUG_INFO, "AtaSecureErase :: PrepareSecureErase\n"));

  Acb.AtaCommand         = ATA_SECURITY_ERASE_PREPARE_CMD;
  Packet.Acb             = &Acb;
  Packet.Asb             = &Asb;
  Packet.Protocol        = EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA;
  Packet.Length          = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Timeout         = EFI_TIMER_PERIOD_SECONDS (3);

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  DEBUG ((DEBUG_INFO, "PrepareSecureErase :: Status = %r \n", Status));

  return Status;
}

/**
  Send ATA secure erase command and wait for completion for a specified timeout
  @param[in]       AtaDevice             The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Port                  Port number on the ATA controller
  @param[in]       PortMultiplierPort    Port multiplier port number on the ATA controller
  @param[in]       Password              Disk password
  @param[in]       Timeout               Time to wait in 100ns units

  @retval          EFI_SUCCESS
  @retval          EFI_TIMEOUT           Secure erase command takes longer to complete
                                         then the specified timeout
  @retval          EFI_DEVICE_ERROR      The device has failed to complete the command
  @retval          EFI_OUT_OF_RESOURCES  There was not enough resources to complete
                                         the call
**/
EFI_STATUS
SendEraseCommand (
  IN EFI_ATA_PASS_THRU_PROTOCOL        *AtaDevice,
  IN UINT16                            Port,
  IN UINT16                            PortMultiplierPort,
  IN CHAR8                             Password[ATA_PASSWORD_MAX_LENGTH + 1],
  IN UINT64                            Timeout
  )
{
  EFI_STATUS                           Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET     Packet;
  EFI_ATA_COMMAND_BLOCK                Acb;
  EFI_ATA_STATUS_BLOCK                 Asb;
  ATA_SECURE_ERASE_DATA_BLOCK          SecurityEraseUnit;

  DEBUG ((DEBUG_INFO, "SecureErase/AtaSecureErase :: SendEraseCommand\n"));

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));
  ZeroMem (&SecurityEraseUnit, sizeof(ATA_SECURE_ERASE_DATA_BLOCK));

  SecurityEraseUnit.EraseControldata = ATA_SECURITY_ERASE_UNIT_ENHANCED_MODE | ATA_SECURITY_ERASE_UNIT_COMPARE_ADMIN_PASSWORD;
  CopyMem (SecurityEraseUnit.Password, Password, ATA_PASSWORD_MAX_LENGTH);
  Acb.AtaCommand                   = ATA_SECURITY_ERASE_UNIT_CMD;

  Packet.Protocol                  = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT;
  Packet.Acb                       = &Acb;
  Packet.Asb                       = &Asb;
  Packet.OutDataBuffer             = &SecurityEraseUnit;
  Packet.OutTransferLength         = sizeof (ATA_SECURE_ERASE_DATA_BLOCK);
  Packet.Length                    = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Timeout                   = Timeout;

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  ZeroMem (&SecurityEraseUnit, sizeof(ATA_SECURE_ERASE_DATA_BLOCK));

  DEBUG ((DEBUG_INFO, "SendEraseCommand :: Status %r \n", Status));

  return Status;
}

/**
  Installs user password on a ATA device.

  @param[in]       AtaDevice                  The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Port                       Port number on the ATA controller
  @param[in]       PortMultiplierPort         Port multiplier port number on the ATA controller
  @param[in]       Password                   Devices master password

  @retval          EFI_SUCCESS
  @retval          EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                              is returned in InTransferLength. For write and bi-directional commands,
                                              OutTransferLength bytes were transferred by OutDataBuffer.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.
**/
EFI_STATUS
SetDefaultPassword (
  IN EFI_ATA_PASS_THRU_PROTOCOL        *AtaDevice,
  IN UINT16                            Port,
  IN UINT16                            PortMultiplierPort
  )
{
  EFI_STATUS                           Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET     Packet;
  EFI_ATA_COMMAND_BLOCK                Acb;
  EFI_ATA_STATUS_BLOCK                 Asb;
  ATA_SET_PASSWORD_COMMAND_BLOCK       SecuritySetPassword;

  DEBUG ((DEBUG_INFO, "AtaSecureErase :: PrepareSecureErase\n"));
  DEBUG ((DEBUG_INFO, "SetDefaultPassword ::"));

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));
  ZeroMem (&SecuritySetPassword, sizeof(ATA_SET_PASSWORD_COMMAND_BLOCK));

  CopyMem (&SecuritySetPassword.Password, mDefaultPassStr, sizeof (mDefaultPassStr) - 1);
  SecuritySetPassword.ControlData = ATA_SECURITY_SET_MASTER_PASSWORD | ATA_SECURITY_SET_MAXIMUM_SECURITY;
  SecuritySetPassword.MasterPasswordRevisionCode = 0x0;
  Acb.AtaCommand             = ATA_SECURITY_SET_PASSWORD_CMD;

  Packet.Protocol            = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT;
  Packet.Acb                 = &Acb;
  Packet.Asb                 = &Asb;
  Packet.OutDataBuffer       = &SecuritySetPassword;
  Packet.OutTransferLength   = sizeof (ATA_SET_PASSWORD_COMMAND_BLOCK);
  Packet.Length              = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Timeout             = EFI_TIMER_PERIOD_SECONDS (5);

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  ZeroMem (&SecuritySetPassword, sizeof(ATA_SET_PASSWORD_COMMAND_BLOCK));

  DEBUG ((DEBUG_INFO, "SetDefaultPassword , master pwd : %r\n", Status));
  return Status;
}

/**
  Removes password and disables security features set on the device

  @param[in]       AtaDevice                  The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Port                       Port number on the ATA controller
  @param[in]       PortMultiplierPort         Port multiplier port number on the ATA controller
  @param[in]       Password                   Devices master password

  @retval          EFI_SUCCESS
  @retval          EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                              is returned in InTransferLength. For write and bi-directional commands,
                                              OutTransferLength bytes were transferred by OutDataBuffer.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.

**/
EFI_STATUS
RemovePassword (
  IN EFI_ATA_PASS_THRU_PROTOCOL        *AtaDevice,
  IN UINT16                            Port,
  IN UINT16                            PortMultiplierPort,
  IN CHAR8                             *Password
  )
{
  EFI_STATUS                           Status;
  EFI_ATA_PASS_THRU_COMMAND_PACKET     Packet;
  EFI_ATA_COMMAND_BLOCK                Acb;
  EFI_ATA_STATUS_BLOCK                 Asb;
  ATA_DISABLE_PASSWORD_COMMAND_BLOCK   SecurityDisablePassword;

  DEBUG ((DEBUG_INFO, "RemoveMasterPassword ::\n"));

  ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&Asb, sizeof(EFI_ATA_STATUS_BLOCK));
  ZeroMem (&SecurityDisablePassword, sizeof (ATA_DISABLE_PASSWORD_COMMAND_BLOCK));

  CopyMem (&SecurityDisablePassword.Password, Password, AsciiStrLen(Password));
  SecurityDisablePassword.ControlData = ATA_SECURITY_DISABLE_PASSWORD_COMPARE_ADMIN_PASSWORD;
  Acb.AtaCommand             = ATA_SECURITY_DIS_PASSWORD_CMD;

  Packet.Protocol            = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT;
  Packet.Length              = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Acb                 = &Acb;
  Packet.Asb                 = &Asb;
  Packet.OutDataBuffer       = &SecurityDisablePassword;
  Packet.OutTransferLength   = sizeof (ATA_DISABLE_PASSWORD_COMMAND_BLOCK);
  Packet.Timeout             = EFI_TIMER_PERIOD_SECONDS (5);

  Status = SendAtaCommand (AtaDevice, &Packet, Port, PortMultiplierPort, NULL);

  ZeroMem (&SecurityDisablePassword, sizeof (ATA_DISABLE_PASSWORD_COMMAND_BLOCK));

  DEBUG ((DEBUG_INFO, "RemoveMasterPassword , master pwd : %r\n", Status));
  return Status;
}

/**
  Checks if password attempts counter has been exceeded

  @param[in]       ControllerData      The buffer used to store the identify controller data.

  @retval          TRUE
  @retval          FALSE
**/
BOOLEAN
IsPasswordAttemptsCounterExceeded (
  IN ATA_IDENTIFY_DATA           *ControllerData
  )
{
  return IS_FLAG_SET(ControllerData->security_status, ATA_DATA_SECURITY_COUNT_EXPIRED_BIT);
}

/**
  Checks if device is password protected by checking if 1st bit of 128th word of
  ATA IDENTIFY DEVICE packet is set.

  @param[in]       ControllerData      The buffer used to store the identify controller data.


  @retval          TRUE                The device is password protected
  @retval          FALSE               The device is NOT password protected
**/
BOOLEAN
IsPasswordProtected (
  IN ATA_IDENTIFY_DATA           *ControllerData
  )
{
  DEBUG ((DEBUG_INFO, "SecureErase/AtaSecureErase :: IsPasswordProtected\n"));
  return IS_FLAG_SET(ControllerData->security_status, ATA_DATA_SECURITY_ENABLED_BIT);
}

/**
  Check if the device has been properly erased

  @param[in]       ControllerData      The buffer used to store the identify controller data.

  @retval          TRUE
  @retval          FALSE
**/
BOOLEAN
VerifySecureErase (
  IN ATA_IDENTIFY_DATA           *ControllerData
  )
{
  return !IsPasswordProtected (ControllerData);
}

/**
  Returns estimated secure erase time

  @param[in]       ControllerData      The buffer used to store the identify controller data.

  @retval          Secure erase time in 100 ns units
**/
UINT64
GetEraseTimeout (
  IN ATA_IDENTIFY_DATA                 *ControllerData
  )
{
  UINT64                               Time;

  DEBUG ((DEBUG_INFO, "AtaSecureErase :: GetEraseTimeout\n"));
  Time = EFI_TIMER_PERIOD_SECONDS (ControllerData->time_for_enhanced_security_erase_unit*2*60);

  DEBUG ((DEBUG_INFO, "\tIdentifyData.time_for_enhanced_security_erase_unit : %04X\n", ControllerData->time_for_enhanced_security_erase_unit));

  return Time;
}

/**
  Performs every action required to securely erase a given device

  @param[in]       AtaDevice                  The pointer to the EFI_ATA_PASS_THRU_PROTOCOL.
  @param[in]       Port                       Port number on the ATA controller
  @param[in]       PortMultiplierPort         Port multiplier port number on the ATA controller
  @param[in]       ControllerData             The buffer used to store the identify controller data.
  @param[in]       Password                   Drive password

  @retval          EFI_SUCCESS
  @retval          EFI_DEVICE_ERROR           The command has failed
  @retval          EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                              command was not sent, so no additional status information is available.
  @retval          EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                              already queued. The caller may retry again later.
  @retval          EFI_TIMEOUT                Secure erase command takes longer to complete
                                              then the specified timeout
**/
EFI_STATUS
SendSecureEraseCommands (
  IN EFI_ATA_PASS_THRU_PROTOCOL        *AtaDevice,
  IN UINT16                            Port,
  IN UINT16                            PortMultiplierPort,
  IN ATA_IDENTIFY_DATA                 *ControllerData,
  IN CHAR8                             Password[ATA_PASSWORD_MAX_LENGTH + 1]
  )
{
  EFI_STATUS                           Status;
  UINT64                               Timeout;

  Timeout = GetEraseTimeout (ControllerData);
  Status = PrepareSecureErase (AtaDevice, Port, PortMultiplierPort);
  if (EFI_ERROR (Status)){
    goto Exit;
  }

  Status = SendEraseCommand (AtaDevice, Port, PortMultiplierPort, Password, Timeout);
  if (EFI_ERROR (Status)){
    goto Exit;
  }

  GetHddIdentifyData (AtaDevice, Port, PortMultiplierPort, ControllerData);

  if (!VerifySecureErase (ControllerData)){
    Status = EFI_DEVICE_ERROR;
  }

Exit:

  DEBUG ((DEBUG_INFO, "SendSecureEraseCommands :: end. Status=%r\n", Status));
  return Status;
}

/**
  Searches device handles for EfiAtaPassThru protocol. If the protocol is found the function
  will cycle through all of the valid Ports and Port Multiplier Ports and erase the devices.

  @retval          EFI_SUCCESS         Nvme Device was erased successfully
  @retval          EFI_NOT_FOUND       No NvmExpressPassThru protocol found
  @retval          Others              An error occurred during Secure Erase operation
**/
EFI_STATUS
EraseAtaDevice (
  VOID
  )
{
  EFI_STATUS                           Status;
  EFI_STATUS                           AtaStatus;
  EFI_ATA_PASS_THRU_PROTOCOL           *AtaDevice;
  ATA_IDENTIFY_DATA                    IdentifyData;
  UINTN                                HandleNum;
  EFI_HANDLE                           *AtaPassThruHandles;
  UINTN                                Index;
  UINT16                               Port;
  UINT16                               PortMultiplierPort;
  CHAR8                                Password[ATA_PASSWORD_MAX_LENGTH + 1];
  BOOLEAN                              AmtPasswordAvailable;
  CHAR16                               AmtPassword[ATA_PASSWORD_MAX_LENGTH + 1];
  EFI_INPUT_KEY                        Key;

  DEBUG ((DEBUG_INFO, "AtaSecureErase:: EraseAtaDevice start\n"));

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiAtaPassThruProtocolGuid,
                  NULL,
                  &HandleNum,
                  &AtaPassThruHandles
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "gBS->LocateHandleBuffer : Status=%r\n", Status));
    if (Status == EFI_NOT_FOUND) {
      return EFI_SUCCESS;
    } else {
      return Status;
    }
  }

  DEBUG ((DEBUG_INFO, "Number of detected ATA Handles : %d\n", HandleNum));

  Status = GetRsePassword (AmtPassword);

  if (!EFI_ERROR (Status)) {
    AmtPasswordAvailable = TRUE;
  } else {
    AmtPasswordAvailable = FALSE;
  }

  AtaStatus = EFI_SUCCESS;

  for (Index = 0; Index < HandleNum; Index++) {
    Status = gBS->HandleProtocol (
                    AtaPassThruHandles[Index],
                    &gEfiAtaPassThruProtocolGuid,
                    (VOID **) &AtaDevice
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "gBS->HandleProtocol : Status=%r\n", Status));
      continue;
    }

    //
    //Go through all of the ports and portmultiplierports and try SE if a device is present
    //
    Port = 0xFFFF;
    while (TRUE) {
      Status = AtaDevice->GetNextPort (AtaDevice, &Port);
      if (EFI_ERROR (Status)) {
        if (Status == EFI_NOT_FOUND) {
          break;
        } else {
          return Status;
        }
      }

      PortMultiplierPort = 0xFFFF;
      while (TRUE) {
        Status = AtaDevice->GetNextDevice (AtaDevice, Port, &PortMultiplierPort);
        if (EFI_ERROR (Status)) {
          if (Status == EFI_NOT_FOUND) {
            break;
          } else {
            return Status;
          }
        }

        ZeroMem (&IdentifyData, sizeof(ATA_IDENTIFY_DATA));
        AtaStatus = GetHddIdentifyData (AtaDevice, Port, PortMultiplierPort, &IdentifyData);
        if (EFI_ERROR (AtaStatus)){
          return AtaStatus;
        }

        DEBUG ((DEBUG_INFO, "AtaSecureErase: Conducting Secure Erase on device on port = 0x%04X multiplier = 0x%04X\n", Port, PortMultiplierPort));
        DEBUG ((DEBUG_INFO, "IdentifyData.command_set_supported_82 0x%04X\n", IdentifyData.command_set_supported_82));
        DEBUG ((DEBUG_INFO, "IdentifyData.command_set_feature_enb_85 0x%04X\n",  IdentifyData.command_set_feature_enb_85));
        DEBUG ((DEBUG_INFO, "IdentifyData.security_status 0x%04X\n", IdentifyData.security_status));

        ZeroMem (Password, sizeof (CHAR8)*(ATA_PASSWORD_MAX_LENGTH + 1));
        //
        // Get the password for performing SE:
        // 1. If device is protected with user password and no master password was received from AMT
        //    ask user to input password manually.
        // 2. If device is protected with user password and master password was received from AMT
        //    use password from AMT.
        // 3. If device is not protected with user password use the default hardcoded password for SE.
        //    Remove master password afterwards.
        //
        if (IsPasswordProtected (&IdentifyData)){
          if (AmtPasswordAvailable == FALSE) {
            while (IsPasswordAttemptsCounterExceeded (&IdentifyData) == FALSE) {
              Status = PopupHddPasswordInputWindows (Password);
              if (EFI_ERROR (Status)){
                DEBUG ((DEBUG_ERROR, "\tConIn not ready\n"));
                return Status;
              }
              ClearScreen ();
              ProgressBarDialog (L"Ata Secure Erase in progress...");
              DEBUG ((DEBUG_INFO, "AtaSecureErase using password supplied by the user\n"));
              //
              // The HDD Unlock Command might be failing here because of the security settings.
              // It doesn't matter as its sole purpose is to decrement the password attempts counter.
              //
              SendHddUnlockCommand (AtaDevice, Port, PortMultiplierPort, Password);
              AtaStatus = SendSecureEraseCommands (AtaDevice, Port, PortMultiplierPort, &IdentifyData, Password);
              ZeroMem (Password, sizeof (CHAR8)*(ATA_PASSWORD_MAX_LENGTH + 1));

              if (AtaStatus == EFI_SUCCESS){
                break;
              } else {
                CreatePopUp (
                  EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE,
                  &Key,
                  L"Failed to erase the HDD, please try again.",
                  L"Press [Enter] to continue",
                  NULL
                  );
              }

              DEBUG ((DEBUG_INFO, "IdentifyData.security_status : %04X\n", IdentifyData.security_status));

              GetHddIdentifyData (AtaDevice, Port, PortMultiplierPort, &IdentifyData);
              ClearScreen ();
            }
            if (EFI_ERROR (AtaStatus)){
              AtaStatus = EFI_ACCESS_DENIED;
              goto Exit;
            } else {
              continue;
            }
          } else {
            UnicodeStrToAsciiStrS (AmtPassword, Password, ATA_PASSWORD_MAX_LENGTH);
            ZeroMem (AmtPassword, sizeof (CHAR16)*(ATA_PASSWORD_MAX_LENGTH + 1));
            while (IsPasswordAttemptsCounterExceeded (&IdentifyData) == FALSE) {
              DEBUG ((DEBUG_INFO, "AtaSecureErase using stored password\n"));
              SendHddUnlockCommand (AtaDevice, Port, PortMultiplierPort, Password);
              AtaStatus = SendSecureEraseCommands (AtaDevice, Port, PortMultiplierPort, &IdentifyData, Password);
              if (AtaStatus == EFI_SUCCESS){
                break;
              } else {
                GetHddIdentifyData (AtaDevice, Port, PortMultiplierPort, &IdentifyData);
                DEBUG ((DEBUG_INFO, "IdentifyData.security_status : %04X\n", IdentifyData.security_status));
              }
            }
            if (EFI_ERROR (AtaStatus)) {
              AtaStatus = EFI_ACCESS_DENIED;
            }
          }
        } else {
          AtaStatus = SetDefaultPassword (AtaDevice, Port, PortMultiplierPort);
          if (EFI_ERROR (AtaStatus)){
            goto Exit;
          }
          CopyMem (Password, mDefaultPassStr, sizeof (mDefaultPassStr) - 1);
          DEBUG ((DEBUG_INFO, "AtaSecureErase using default password\n"));
          ProgressBarDialog (L"Ata Secure Erase in progress...");
          AtaStatus = SendSecureEraseCommands (AtaDevice, Port, PortMultiplierPort, &IdentifyData, Password);
          AtaStatus = RemovePassword (AtaDevice, Port, PortMultiplierPort, Password);
        }

        if (EFI_ERROR (AtaStatus)) {
          goto Exit;
        }
      }
    }
  }

Exit:
  ZeroMem (Password, sizeof (CHAR8)*(ATA_PASSWORD_MAX_LENGTH + 1));
  FreePool (AtaPassThruHandles);

  return AtaStatus;
}
