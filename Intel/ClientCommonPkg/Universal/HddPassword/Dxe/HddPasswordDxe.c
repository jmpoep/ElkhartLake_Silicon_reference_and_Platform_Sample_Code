//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
HDD password driver which is used to support HDD security feature.

Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/


#include "HddPasswordDxe.h"

EFI_EVENT  mHddPasswordRegistration        = NULL;
EFI_GUID   mHddPasswordVendorGuid          = HDD_PASSWORD_CONFIG_GUID;
CHAR16     mHddPasswordVendorStorageName[] = L"HDD_PASSWORD_CONFIG";
LIST_ENTRY mHddPasswordConfigFormList;
UINT32     mNumberOfHddDevices = 0;

EFI_SMM_COMMUNICATION_PROTOCOL *mSmmCommunication = NULL;
EFI_EVENT                      mHddPasswordEvent;

HII_VENDOR_DEVICE_PATH  mHddPasswordHiiVendorDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    HDD_PASSWORD_CONFIG_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};


/**
  Get attached harddisk identify data through Ata Pass Thru Protocol.

  @param[in] AtaPassThru         The pointer to the ATA_PASS_THRU protocol.
  @param[in] Port                The port number of the ATA device to send the command.
  @param[in] PortMultiplierPort  The port multiplier port number of the ATA device to send the command.
                                 If there is no port multiplier, then specify 0.
  @param[in] IdentifyData        The buffer to store identify data.

  @retval EFI_SUCCESS            Successful to get identify data.
  @retval EFI_INVALID_PARAMETER  The parameter passed-in is invalid.
  @retval EFI_OUT_OF_RESOURCES   Not enough memory to get identify data.
  @retval EFI_DEVICE_ERROR       Can not get identify data.

**/
EFI_STATUS
GetHddDeviceIdentifyData (
  IN  EFI_ATA_PASS_THRU_PROTOCOL    *AtaPassThru,
  IN  UINT16                        Port,
  IN  UINT16                        PortMultiplierPort,
  IN  ATA_IDENTIFY_DATA             *IdentifyData
  )
{
  EFI_STATUS                        Status;
  EFI_ATA_COMMAND_BLOCK             Acb;
  EFI_ATA_STATUS_BLOCK              *Asb;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  Packet;

  if ((AtaPassThru == NULL) || (IdentifyData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // The 'Asb' field (a pointer to the EFI_ATA_STATUS_BLOCK structure) in
  // EFI_ATA_PASS_THRU_COMMAND_PACKET is required to be aligned specified by
  // the 'IoAlign' field in the EFI_ATA_PASS_THRU_MODE structure. Meanwhile,
  // the structure EFI_ATA_STATUS_BLOCK is composed of only UINT8 fields, so it
  // may not be aligned when allocated on stack for some compilers. Hence, we
  // use the API AllocateAlignedPages to ensure this structure is properly
  // aligned.
  //
  Asb = AllocateAlignedPages (
          EFI_SIZE_TO_PAGES (sizeof (EFI_ATA_STATUS_BLOCK)),
          AtaPassThru->Mode->IoAlign
          );
  if (Asb == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Prepare for ATA command block.
  //
  ZeroMem (&Acb, sizeof (Acb));
  ZeroMem (Asb, sizeof (EFI_ATA_STATUS_BLOCK));
  Acb.AtaCommand    = ATA_CMD_IDENTIFY_DRIVE;
  Acb.AtaDeviceHead = (UINT8) (BIT7 | BIT6 | BIT5 | (PortMultiplierPort == 0xFFFF ? 0 : (PortMultiplierPort << 4)));

  //
  // Prepare for ATA pass through packet.
  //
  ZeroMem (&Packet, sizeof (Packet));
  Packet.Protocol = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
  Packet.Length   = EFI_ATA_PASS_THRU_LENGTH_BYTES | EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT;
  Packet.Asb      = Asb;
  Packet.Acb      = &Acb;
  Packet.InDataBuffer     = IdentifyData;
  Packet.InTransferLength = sizeof (ATA_IDENTIFY_DATA);
  Packet.Timeout          = ATA_TIMEOUT;

  Status = AtaPassThru->PassThru (
                          AtaPassThru,
                          Port,
                          PortMultiplierPort,
                          &Packet,
                          NULL
                          );

  FreeAlignedPages (Asb, EFI_SIZE_TO_PAGES (sizeof (EFI_ATA_STATUS_BLOCK)));

  return Status;
}

/**
  Parse security status according to identify data.

  @param[in] IdentifyData        The buffer to store identify data.
  @param[in, out] IfrData        The port number of the ATA device to send the command.

  @retval EFI_SUCCESS            Successful to get harddisk model number.
  @retval EFI_INVALID_PARAMETER  The parameter passed-in is invalid.
  @retval EFI_DEVICE_ERROR       Can not get harddisk model number.

**/
EFI_STATUS
GetHddPasswordSecurityStatus (
  IN     ATA_IDENTIFY_DATA    *IdentifyData,
  IN OUT HDD_PASSWORD_CONFIG  *IfrData
  )
{
  IfrData->Supported = (IdentifyData->command_set_supported_82 & BIT1) ? 1 : 0;
  IfrData->Enabled   = (IdentifyData->security_status & BIT1) ? 1 : 0;
  IfrData->Locked    = (IdentifyData->security_status & BIT2) ? 1 : 0;
  IfrData->Frozen    = (IdentifyData->security_status & BIT3) ? 1 : 0;
  IfrData->UserPasswordStatus   = IfrData->Enabled;
  IfrData->MasterPasswordStatus = IfrData->Supported;

  return EFI_SUCCESS;
}

/**
  Get attached harddisk model number from identify data buffer.

  @param[in] IdentifyData    Pointer to identify data buffer.
  @param[in, out] String     The buffer to store harddisk model number.

**/
VOID
GetHddDeviceModelNumber (
  IN ATA_IDENTIFY_DATA             *IdentifyData,
  IN OUT CHAR16                    *String
  )
{
  UINTN             Index;

  //
  // Swap the byte order in the original module name.
  // From Ata spec, the maximum length is 40 bytes.
  //
  for (Index = 0; Index < 40; Index += 2) {
    String[Index]      = IdentifyData->ModelName[Index + 1];
    String[Index + 1]  = IdentifyData->ModelName[Index];
  }

  //
  // Chap it off after 11 characters
  //
  String[11] = L'\0';

  return ;
}

/**
  Get password input from the popup windows.

  @param[in]       HddString    On entry, point to UserName buffer lengh, in bytes.
                                On exit, point to input user name length, in bytes.
  @param[in, out]  Password     The buffer to hold the input user name.

  @retval EFI_ABORTED           It is given up by pressing 'ESC' key.
  @retval EFI_NOT_READY         Not a valid input at all.
  @retval EFI_SUCCESS           Get a user name successfully.

**/
EFI_STATUS
PopupHddPasswordInputWindows (
  IN     CHAR16      *HddString,
  IN OUT CHAR8       *Password
  )
{
  EFI_INPUT_KEY Key;
  UINTN         Length;
  CHAR16        String[8 + 64];
  CHAR16        Mask[32 + 1];
  CHAR16        Unicode[32 + 1];
  CHAR8         Ascii[32 + 1];

  ZeroMem (Unicode, sizeof (Unicode));
  ZeroMem (Ascii, sizeof (Ascii));
  ZeroMem (Mask, sizeof (Mask));
  ZeroMem (String, sizeof (String));
  UnicodeSPrint(String, 8 + 64, L"Unlock %s", HddString);

  Length = 0;
  while (TRUE) {
    Mask[Length] = L'_';
    CreatePopUp (
      EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE,
      &Key,
      String,
      L"---------------------",
      Mask,
      NULL
      );
    //
    // Check key.
    //
    if (Key.ScanCode == SCAN_NULL) {
      if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
        //
        // Add the null terminator.
        //
        Unicode[Length] = 0;
        Length++;
        break;
      } else if ((Key.UnicodeChar == CHAR_NULL) ||
                 (Key.UnicodeChar == CHAR_TAB) ||
                 (Key.UnicodeChar == CHAR_LINEFEED)
                 ) {
        continue;
      } else {
        if (Key.UnicodeChar == CHAR_BACKSPACE) {
          if (Length > 0) {
            Unicode[Length] = 0;
            Mask[Length] = 0;
            Length--;
          }
        } else {
          Unicode[Length] = Key.UnicodeChar;
          Mask[Length] = L'*';
          Length++;
          if (Length == 32) {
            //
            // Add the null terminator.
            //
            Unicode[Length] = 0;
            Mask[Length] = 0;
            break;
          }
        }
      }
    }

    if (Key.ScanCode == SCAN_ESC) {
      if (Length == 0) {
        return EFI_ABORTED;
      } else {
        return EFI_NOT_READY;
      }
    }
  }

  if (Length <= 1) {
    return EFI_NOT_READY;
  }

  UnicodeStrToAsciiStrS (Unicode, Ascii, sizeof (Ascii));
  CopyMem (Password, Ascii, 32);
  ZeroMem (Unicode, sizeof (Unicode));
  ZeroMem (Ascii, sizeof (Ascii));

  return EFI_SUCCESS;
}

/**
  Get hash data of hdd password from non-volatile variable region.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in, out] HashData        The hash data of hdd password of attached ATA device.
  @param[in, out] SaltData        The salt data of hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
HddPasswordGetPasswordHash (
  IN     UINTN                        Bus,
  IN     UINTN                        Device,
  IN     UINTN                        Function,
  IN     UINT16                       Port,
  IN     UINT16                       PortMultiplierPort,
  IN OUT CHAR8                        *HashData,
  IN OUT CHAR8                        *SaltData
  )
{
  EFI_STATUS             Status;
  VOID                   *List;
  UINTN                  ListSize;
  EFI_HDD_DEVICE_LIST    *DeviceNode;
  UINTN                  Index;

  List     = NULL;
  ListSize = 0;

  Status = gRT->GetVariable (
                  L"HddPassword",
                  &gEfiHddPasswordSecurityVariableGuid,
                  NULL,
                  &ListSize,
                  List
                  );

  if (Status == EFI_NOT_FOUND) {
    return Status;
  } else if (Status == EFI_BUFFER_TOO_SMALL) {
    //
    // Allocate the buffer to store hdd device list
    //
    List = AllocateZeroPool (ListSize);
    if (List == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = gRT->GetVariable (
                    L"HddPassword",
                    &gEfiHddPasswordSecurityVariableGuid,
                    NULL,
                    &ListSize,
                    List
                    );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      goto EXIT;
    }

    for (Index = 0; Index < ListSize / sizeof (EFI_HDD_DEVICE_LIST); Index += 1) {
      DeviceNode = (EFI_HDD_DEVICE_LIST *)((UINTN)List + Index * sizeof (EFI_HDD_DEVICE_LIST));

      if ((DeviceNode->Bus == Bus) &&
          (DeviceNode->Device == Device) &&
          (DeviceNode->Function == Function) &&
          (DeviceNode->Port == Port) &&
          (DeviceNode->PortMultiplierPort == PortMultiplierPort)) {
        CopyMem (HashData, DeviceNode->Password, sizeof (DeviceNode->Password));
        CopyMem (SaltData, DeviceNode->PasswordSalt, sizeof (DeviceNode->PasswordSalt));
        break;
      }
    }

    //
    // Device node is not found.
    //
    if (Index >= ListSize / sizeof (EFI_HDD_DEVICE_LIST)) {
      Status = EFI_NOT_FOUND;
      goto EXIT;
    }
  } else {
    ASSERT (FALSE);
    Status = EFI_INVALID_PARAMETER;
    goto EXIT;
  }

EXIT:
  if (List != NULL) {
    FreePool (List);
  }

  return Status;
}

/**
  Initialize the communicate buffer using DataSize and Function.

  @param[out]      DataPtr          Points to the data in the communicate buffer.
  @param[in]       DataSize         The data size to send to SMM.
  @param[in]       Function         The function number to initialize the communicate header.

  @retval EFI_INVALID_PARAMETER     The data size is too big.
  @retval EFI_SUCCESS               Find the specified variable.

**/
VOID*
InitCommunicateBuffer (
  OUT     VOID                              **DataPtr OPTIONAL,
  IN      UINTN                             DataSize,
  IN      UINTN                             Function
  )
{
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_COMMUNICATE_HEADER                    *SmmFunctionHeader;
  VOID                                      *Buffer;
  EDKII_PI_SMM_COMMUNICATION_REGION_TABLE   *SmmCommRegionTable;
  EFI_MEMORY_DESCRIPTOR                     *SmmCommMemRegion;
  UINTN                                     Index;
  UINTN                                     Size;
  EFI_STATUS                                Status;

  Buffer = NULL;
  Status = EfiGetSystemConfigurationTable (
             &gEdkiiPiSmmCommunicationRegionTableGuid,
             (VOID **) &SmmCommRegionTable
             );
  if (EFI_ERROR (Status)) {
    return NULL;
  }
  ASSERT (SmmCommRegionTable != NULL);
  SmmCommMemRegion = (EFI_MEMORY_DESCRIPTOR *) (SmmCommRegionTable + 1);
  Size = 0;
  for (Index = 0; Index < SmmCommRegionTable->NumberOfEntries; Index++) {
    if (SmmCommMemRegion->Type == EfiConventionalMemory) {
      Size = EFI_PAGES_TO_SIZE ((UINTN) SmmCommMemRegion->NumberOfPages);
      if (Size >= (DataSize + OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data) + OFFSET_OF (SMM_COMMUNICATE_HEADER, Data))) {
        break;
      }
    }
    SmmCommMemRegion = (EFI_MEMORY_DESCRIPTOR *) ((UINT8 *) SmmCommMemRegion + SmmCommRegionTable->DescriptorSize);
  }
  ASSERT (Index < SmmCommRegionTable->NumberOfEntries);

  Buffer = (VOID*)(UINTN)SmmCommMemRegion->PhysicalStart;
  ASSERT (Buffer != NULL);
  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) Buffer;
  CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gEfiHddPasswordNotifyProtocolGuid);
  SmmCommunicateHeader->MessageLength = DataSize + OFFSET_OF (SMM_COMMUNICATE_HEADER, Data);

  SmmFunctionHeader = (SMM_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data;
  ZeroMem (SmmFunctionHeader, DataSize + OFFSET_OF (SMM_COMMUNICATE_HEADER, Data));
  SmmFunctionHeader->Function = Function;
  if (DataPtr != NULL) {
    *DataPtr = SmmFunctionHeader->Data;
  }

  return Buffer;
}

/**
  Send the data in communicate buffer to SMM.

  @param[in]   Buffer                 Points to the data in the communicate buffer.
  @param[in]   DataSize               This size of the function header and the data.

  @retval      EFI_SUCCESS            Success is returned from the functin in SMM.
  @retval      Others                 Failure is returned from the function in SMM.

**/
EFI_STATUS
SendCommunicateBuffer (
  IN      VOID                              *Buffer,
  IN      UINTN                             DataSize
  )
{
  EFI_STATUS                                Status;
  UINTN                                     CommSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_COMMUNICATE_HEADER                    *SmmFunctionHeader;
  EFI_SMM_COMMUNICATION_PROTOCOL            *SmmCommunication;

  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
  ASSERT_EFI_ERROR (Status);

  CommSize = DataSize + OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data) + OFFSET_OF (SMM_COMMUNICATE_HEADER, Data);

  Status = SmmCommunication->Communicate (SmmCommunication, Buffer, &CommSize);
  ASSERT_EFI_ERROR (Status);

  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) Buffer;
  SmmFunctionHeader    = (SMM_COMMUNICATE_HEADER *)SmmCommunicateHeader->Data;
  return  SmmFunctionHeader->ReturnStatus;
}

/**
  Unlock hdd password from SMM.
  This way is used to unlock HDD if it's locked again by 3rd option rom, such as legacy AHCI or RAID oprom.
  At this point, it would get password and unlock the device from SMM for security issue.

  @param[in] BusNum               The bus number of ATA controller.
  @param[in] DevNum               The device number of ATA controller.
  @param[in] FuncNum              The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in] Identifier           The identifier to set user or master password.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
HddPasswordUnlockHddPassword (
  IN  UINTN                           BusNum,
  IN  UINTN                           DevNum,
  IN  UINTN                           FuncNum,
  IN  UINT16                          Port,
  IN  UINT16                          PortMultiplierPort,
  IN  UINT16                          Identifier,
  IN  CHAR8                           *Password
  )
{
  EFI_STATUS                          Status;
  EFI_HDD_DEVICE_LIST                 *Parameter;
  VOID                                *Buffer;
  UINTN                               Length;

  Parameter = NULL;
  Buffer    = NULL;
  //
  // The data is comprised of two parts:
  // a) a EFI_HDD_DEVICE_LIST
  // b) a UINT16 data which is used to specify identifier.
  //
  Length = sizeof (EFI_HDD_DEVICE_LIST) + sizeof (Identifier);
  Buffer = InitCommunicateBuffer ((VOID**)&Parameter, Length, SMM_FUNCTION_UNLOCK_HDD_PASSWORD);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ASSERT (Parameter != NULL);
  Parameter->Bus      = (UINT32)BusNum;
  Parameter->Device   = (UINT32)DevNum;
  Parameter->Function = (UINT32)FuncNum;
  Parameter->Port     = Port;
  Parameter->PortMultiplierPort = PortMultiplierPort;
  if (Password != NULL) {
    CopyMem (Parameter->Password, Password, sizeof (Parameter->Password));
  }
  Identifier &= BIT0;
  CopyMem (Parameter + 1, &Identifier, sizeof (Identifier));

  Status = SendCommunicateBuffer (Buffer, Length);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

EXIT:
  ZeroMem (Parameter, Length);
  return Status;
}

/**
  Set hdd password from SMM.

  If the NewPassword is NULL and OldPassword is not NULL, it means executing
  SECURITY_DISABLE_PASSWORD command.
  If the OldPassword is NULL and NewPassword is not NULL, it means executing
  SECURITY_SET_PASSWORD command.

  @param[in] BusNum                    The bus number of ATA controller.
  @param[in] DevNum                    The device number of ATA controller.
  @param[in] FuncNum                   The function number of ATA controller.
  @param[in] Port                      The port number of attached ATA device.
  @param[in] PortMultiplierPort        The port number of port multiplier of attached ATA device.
  @param[in] Identifier                The identifier to set user or master password.
  @param[in] SecurityLevel             The security level to be set to device.
  @param[in] MasterPasswordIdentifier  The master password identifier to be set to device.
  @param[in] OldPassword               The old hdd password of attached ATA device.
  @param[in] NewPassword               The new hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
HddPasswordSetHddPassword (
  IN  UINTN                       BusNum,
  IN  UINTN                       DevNum,
  IN  UINTN                       FuncNum,
  IN  UINT16                      Port,
  IN  UINT16                      PortMultiplierPort,
  IN  UINT8                       Identifier,
  IN  UINT8                       SecurityLevel,
  IN  UINT16                      MasterPasswordIdentifier,
  IN  CHAR8                       *OldPassword,
  IN  CHAR8                       *NewPassword
  )
{
  EFI_STATUS                      Status;
  EFI_HDD_DEVICE_LIST             *Parameter;
  VOID                            *Buffer;
  UINTN                           Length;
  UINT32                          Data;
  Parameter = NULL;
  Buffer    = NULL;
  //
  // The data is comprised of the following parts:
  // a) a EFI_HDD_DEVICE_LIST
  // b) a UINT8 data which is used to specify identifier.
  // c) a UINT8 data which is used to specify security level.
  // d) a UINT16 data which is used to specify master passowrd identifier.
  // e) a 32bytes data which is used to specify old password.
  //
  Length = sizeof (EFI_HDD_DEVICE_LIST) + sizeof (Identifier) + sizeof (SecurityLevel) + sizeof (MasterPasswordIdentifier) + 32;
  Buffer = InitCommunicateBuffer ((VOID**)&Parameter, Length, SMM_FUNCTION_SET_HDD_PASSWORD);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ASSERT (Parameter != NULL);
  Parameter->Bus      = (UINT32)BusNum;
  Parameter->Device   = (UINT32)DevNum;
  Parameter->Function = (UINT32)FuncNum;
  Parameter->Port     = Port;
  Parameter->PortMultiplierPort = PortMultiplierPort;
  if (NewPassword != NULL) {
    CopyMem (Parameter->Password, NewPassword, sizeof (Parameter->Password));
  }
  Data = ((Identifier | (SecurityLevel << 8)) & (BIT0 | BIT8)) | (MasterPasswordIdentifier << 16);
  CopyMem (Parameter + 1, &Data, sizeof (UINT32));
  if (OldPassword != NULL) {
    CopyMem ((UINT32*)(Parameter + 1) + 1, OldPassword, 32);
  }
  Status = SendCommunicateBuffer (Buffer, Length);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

EXIT:
  ZeroMem (Parameter, Length);
  return Status;
}

/**
  Hash the data to get credential.

  @param[in]   Buffer         Points to the data buffer, 32 bytes
  @param[in]   SaltValue      Points to the salt buffer, 32 bytes
  @param[out]  Credential     Points to the hashed result

  @retval      TRUE           Hash the data successfully.
  @retval      FALSE          Failed to hash the data.

**/
BOOLEAN
GenerateCredential (
  IN      UINT8               *Buffer,
  IN      UINT8               *SaltValue,
     OUT  UINT8               *Credential
  )
{
  BOOLEAN                     Status;
  UINTN                       HashSize;
  VOID                        *Hash;
  VOID                        *HashData;

  Hash      = NULL;
  HashData  = NULL;
  Status    = FALSE;

  HashSize  = Sha256GetContextSize ();
  Hash      = AllocateZeroPool (HashSize);
  ASSERT (Hash != NULL);
  if (Hash == NULL) {
    goto Done;
  }

  Status = Sha256Init (Hash);
  if (!Status) {
    goto Done;
  }

  HashData = AllocateZeroPool (PASSWORD_SALT_SIZE + 32);
  ASSERT (HashData != NULL);
  if (HashData == NULL) {
    goto Done;
  }

  CopyMem (HashData, SaltValue, PASSWORD_SALT_SIZE);
  CopyMem ((CHAR8*)HashData + PASSWORD_SALT_SIZE, Buffer, 32);

  Status = Sha256Update (Hash, HashData, PASSWORD_SALT_SIZE + 32);
  if (!Status) {
    goto Done;
  }

  Status = Sha256Final (Hash, Credential);

Done:
  if (Hash != NULL) {
    FreePool (Hash);
  }
  if (HashData != NULL) {
    FreePool (HashData);
  }
  return Status;
}

/**
  Validate the user's password.

  @param Private     This driver's private context data.
  @param StringId    The user's input.

  @retval EFI_SUCCESS   The user's input matches the password.
  @retval EFI_NOT_READY The user's input does not match the password.
**/
EFI_STATUS
ValidatePassword (
  IN HDD_PASSWORD_DXE_PRIVATE_DATA   *Private,
  IN EFI_STRING_ID                   StringId
  )
{
  EFI_STATUS                      Status;
  CHAR16                          *Password;
  EFI_ATA_PASS_THRU_PROTOCOL      *AtaPassThru;
  ATA_IDENTIFY_DATA               IdentifyData;
  HDD_PASSWORD_CONFIG             IfrData;
  CHAR8                           AsciiPassword[32 + 1];
  UINTN                           Bus;
  UINTN                           Device;
  UINTN                           Function;
  UINT16                          Port;
  UINT16                          PortMultiplierPort;
  BOOLEAN                         HashOk;
  UINT8                           HashData[SHA256_DIGEST_SIZE];
  UINT8                           SavedHashData[SHA256_DIGEST_SIZE];
  UINT8                           SavedSaltData[PASSWORD_SALT_SIZE];

  //
  // Check if the password exists first
  //
  Status = gBS->HandleProtocol (Private->Current->Controller, &gEfiAtaPassThruProtocolGuid, (VOID**)&AtaPassThru);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Bus                = Private->Current->Bus;
  Device             = Private->Current->Device;
  Function           = Private->Current->Function;
  Port               = Private->Current->Port;
  PortMultiplierPort = Private->Current->PortMultiplierPort;
  ZeroMem (Private->Current->IfrData.IdeUserPassword, sizeof (Private->Current->IfrData.IdeUserPassword));
  Password           = NULL;
  ZeroMem (&IfrData, sizeof (HDD_PASSWORD_CONFIG));
  Status = GetHddDeviceIdentifyData (AtaPassThru, Port, PortMultiplierPort, &IdentifyData);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  GetHddPasswordSecurityStatus (&IdentifyData, &IfrData);

  if ((IfrData.Supported) && (IfrData.Enabled == 0)) {
    //
    // Old password not exist, prompt for new password
    //
    Status = EFI_SUCCESS;
    goto EXIT;
  }

  //
  // Get user input password
  //
  Password = HiiGetString (Private->HiiHandle, StringId, NULL);
  if (Password == NULL) {
    Status = EFI_NOT_READY;
    goto EXIT;
  }

  if ((StrLen (Password) > 32) || (Password[0] == 0)) {
    Status = EFI_NOT_READY;
    goto EXIT;
  }

  //
  // Validate old password
  //
  ZeroMem (AsciiPassword, sizeof (AsciiPassword));
  UnicodeStrToAsciiStrS (Password, AsciiPassword, sizeof (AsciiPassword));

  if ((IfrData.Supported) && (IfrData.Enabled) && (IfrData.Locked) && (IfrData.Frozen == 0)) {
   Status = HddPasswordUnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, 0, AsciiPassword);
    if (!EFI_ERROR (Status)) {
      CopyMem (IfrData.IdeUserPassword, Password, sizeof (IfrData.IdeUserPassword));
      goto EXIT1;
    } else {
      Status = EFI_NOT_READY;
      goto EXIT;
    }
  }

  //
  // Get corresponding password from variable and compare if the hash value is same.
  //
  Status = HddPasswordGetPasswordHash (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
  if (EFI_ERROR(Status)) {
    Status = EFI_NOT_READY;
    goto EXIT;
  }

  ZeroMem (HashData, sizeof (HashData));
  HashOk = GenerateCredential ((UINT8 *)AsciiPassword, SavedSaltData, HashData);

  if (HashOk) {
    if (CompareMem (SavedHashData, HashData, SHA256_DIGEST_SIZE) != 0) {
      //
      // We treat the device as unlocked at this case.
      //
      Status = EFI_NOT_READY;
      goto EXIT;
    }
    CopyMem (IfrData.IdeUserPassword, Password, sizeof (IfrData.IdeUserPassword));
  } else {
    ASSERT (FALSE);
    Status = EFI_NOT_READY;
    goto EXIT;
  }

EXIT1:
  Status = GetHddDeviceIdentifyData (AtaPassThru, Private->Current->Port, Private->Current->PortMultiplierPort, &IdentifyData);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  GetHddPasswordSecurityStatus (&IdentifyData, &IfrData);

EXIT:
  CopyMem (&Private->Current->IfrData, &IfrData, sizeof (HDD_PASSWORD_CONFIG));

  if (Password != NULL) {
    FreePool (Password);
  }
  ZeroMem (AsciiPassword, sizeof (AsciiPassword));
  return Status;
}

/**
  Encode the password using a simple algorithm.

  @param Private     This driver's private context data.
  @param StringId    The password from User.

  @retval  EFI_SUCESS The operation is successful.
  @return  Other value if gRT->SetVariable () fails.

**/
EFI_STATUS
SetPassword (
  IN HDD_PASSWORD_DXE_PRIVATE_DATA   *Private,
  IN EFI_STRING_ID                   StringId
  )
{
  EFI_STATUS                         Status;
  CHAR16                             *TempPassword;
  EFI_ATA_PASS_THRU_PROTOCOL         *AtaPassThru;
  CHAR8                              AsciiPassword[32 + 1];
  CHAR8                              AsciiOldPassword[32 + 1];
  CHAR16                             OldPassword[32 + 1];
  ATA_IDENTIFY_DATA                  IdentifyData;
  HDD_PASSWORD_CONFIG                IfrData;

  //
  // Get user input password
  //
  TempPassword = HiiGetString (Private->HiiHandle, StringId, NULL);
  if (TempPassword == NULL) {
    return EFI_NOT_READY;
  }

  if (StrLen (TempPassword) > 32) {
    Status = EFI_NOT_READY;
    goto EXIT;
  }

  //
  // Check if the password exists first
  //
  Status = gBS->HandleProtocol (Private->Current->Controller, &gEfiAtaPassThruProtocolGuid, (VOID**)&AtaPassThru);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  //
  // Set password
  //
  ZeroMem (AsciiPassword, sizeof (AsciiPassword));
  ZeroMem (AsciiOldPassword, sizeof (AsciiOldPassword));
  ZeroMem (OldPassword, sizeof (OldPassword));
  UnicodeStrToAsciiStrS (TempPassword, AsciiPassword, sizeof (AsciiPassword));
  CopyMem (OldPassword, Private->Current->IfrData.IdeUserPassword, sizeof (Private->Current->IfrData.IdeUserPassword));
  UnicodeStrToAsciiStrS (OldPassword, AsciiOldPassword, sizeof (AsciiOldPassword));
  Status = HddPasswordSetHddPassword (
             Private->Current->Bus,
             Private->Current->Device,
             Private->Current->Function,
             Private->Current->Port,
             Private->Current->PortMultiplierPort,
             0,
             1,
             0,
             AsciiOldPassword,
             AsciiPassword
             );
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  Status = GetHddDeviceIdentifyData (AtaPassThru, Private->Current->Port, Private->Current->PortMultiplierPort, &IdentifyData);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  GetHddPasswordSecurityStatus (&IdentifyData, &IfrData);
  CopyMem (&Private->Current->IfrData, &IfrData, sizeof (HDD_PASSWORD_CONFIG));

EXIT:
  ZeroMem (Private->Current->IfrData.IdeUserPassword, sizeof (Private->Current->IfrData.IdeUserPassword));
  ZeroMem (TempPassword, StrLen (TempPassword));
  FreePool (TempPassword);
  ZeroMem (AsciiPassword, sizeof (AsciiPassword));

  return Status;
}


/**
  Get the HDD Password configuration form entry by the index of the goto opcode actived.

  @param[in]  Index The 0-based index of the goto opcode actived.

  @return The HDD Password configuration form entry found.
**/
HDD_PASSWORD_CONFIG_FORM_ENTRY *
HddPasswordGetConfigFormEntryByIndex (
  IN UINT32 Index
  )
{
  LIST_ENTRY                     *Entry;
  UINT32                         CurrentIndex;
  HDD_PASSWORD_CONFIG_FORM_ENTRY *ConfigFormEntry;

  CurrentIndex    = 0;
  ConfigFormEntry = NULL;

  EFI_LIST_FOR_EACH (Entry, &mHddPasswordConfigFormList) {
    if (CurrentIndex == Index) {
      ConfigFormEntry = BASE_CR (Entry, HDD_PASSWORD_CONFIG_FORM_ENTRY, Link);
      break;
    }

    CurrentIndex++;
  }

  return ConfigFormEntry;
}

/**
  This function allows the caller to request the current
  configuration for one or more named elements. The resulting
  string is in <ConfigAltResp> format. Any and all alternative
  configuration strings shall also be appended to the end of the
  current configuration string. If they are, they must appear
  after the current configuration. They must contain the same
  routing (GUID, NAME, PATH) as the current configuration string.
  They must have an additional description indicating the type of
  alternative configuration the string represents,
  "ALTCFG=<StringToken>". That <StringToken> (when
  converted from Hex UNICODE to binary) is a reference to a
  string in the associated string pack.

  @param[in] This       Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in] Request    A null-terminated Unicode string in
                        <ConfigRequest> format. Note that this
                        includes the routing information as well as
                        the configurable name / value pairs. It is
                        invalid for this string to be in
                        <MultiConfigRequest> format.
  @param[out] Progress  On return, points to a character in the
                        Request string. Points to the string's null
                        terminator if request was successful. Points
                        to the most recent "&" before the first
                        failing name / value pair (or the beginning
                        of the string if the failure is in the first
                        name / value pair) if the request was not
                        successful.
  @param[out] Results   A null-terminated Unicode string in
                        <ConfigAltResp> format which has all values
                        filled in for the names in the Request string.
                        String to be allocated by the called function.

  @retval EFI_SUCCESS             The Results string is filled with the
                                  values corresponding to all requested
                                  names.
  @retval EFI_OUT_OF_RESOURCES    Not enough memory to store the
                                  parts of the results that must be
                                  stored awaiting possible future
                                  protocols.
  @retval EFI_INVALID_PARAMETER   For example, passing in a NULL
                                  for the Request parameter
                                  would result in this type of
                                  error. In this case, the
                                  Progress parameter would be
                                  set to NULL.
  @retval EFI_NOT_FOUND           Routing data doesn't match any
                                  known driver. Progress set to the
                                  first character in the routing header.
                                  Note: There is no requirement that the
                                  driver validate the routing data. It
                                  must skip the <ConfigHdr> in order to
                                  process the names.
  @retval EFI_INVALID_PARAMETER   Illegal syntax. Progress set
                                  to most recent & before the
                                  error or the beginning of the
                                  string.
  @retval EFI_INVALID_PARAMETER   Unknown name. Progress points
                                  to the & before the name in
                                  question.Currently not implemented.
**/
EFI_STATUS
EFIAPI
HddPasswordFormExtractConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Request,
  OUT EFI_STRING                             *Progress,
  OUT EFI_STRING                             *Results
  )
{
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  HDD_PASSWORD_CONFIG              *IfrData;
  HDD_PASSWORD_DXE_PRIVATE_DATA    *Private;
  EFI_STRING                       ConfigRequestHdr;
  EFI_STRING                       ConfigRequest;
  BOOLEAN                          AllocatedRequest;
  UINTN                            Size;

  if (Progress == NULL || Results == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Progress = Request;
  if ((Request != NULL) && !HiiIsConfigHdrMatch (Request, &mHddPasswordVendorGuid, mHddPasswordVendorStorageName)) {
    return EFI_NOT_FOUND;
  }

  ConfigRequestHdr = NULL;
  ConfigRequest    = NULL;
  AllocatedRequest = FALSE;
  Size             = 0;

  Private = HDD_PASSWORD_DXE_PRIVATE_FROM_THIS (This);
  IfrData = AllocateZeroPool (sizeof (HDD_PASSWORD_CONFIG));
  ASSERT (IfrData != NULL);
  if (Private->Current != NULL) {
    CopyMem (IfrData, &Private->Current->IfrData, sizeof (HDD_PASSWORD_CONFIG));
  }

  //
  // Convert buffer data to <ConfigResp> by helper function BlockToConfig()
  //
  BufferSize = sizeof (HDD_PASSWORD_CONFIG);
  ConfigRequest = Request;
  if ((Request == NULL) || (StrStr (Request, L"OFFSET") == NULL)) {
    //
    // Request has no request element, construct full request string.
    // Allocate and fill a buffer large enough to hold the <ConfigHdr> template
    // followed by "&OFFSET=0&WIDTH=WWWWWWWWWWWWWWWW" followed by a Null-terminator
    //
    ConfigRequestHdr = HiiConstructConfigHdr (&mHddPasswordVendorGuid, mHddPasswordVendorStorageName, Private->DriverHandle);
    Size = (StrLen (ConfigRequestHdr) + 32 + 1) * sizeof (CHAR16);
    ConfigRequest = AllocateZeroPool (Size);
    ASSERT (ConfigRequest != NULL);
    AllocatedRequest = TRUE;
    UnicodeSPrint (ConfigRequest, Size, L"%s&OFFSET=0&WIDTH=%016LX", ConfigRequestHdr, (UINT64)BufferSize);
    FreePool (ConfigRequestHdr);
  }
  Status = gHiiConfigRouting->BlockToConfig (
                                gHiiConfigRouting,
                                ConfigRequest,
                                (UINT8 *) IfrData,
                                BufferSize,
                                Results,
                                Progress
                                );
  FreePool (IfrData);
  //
  // Free the allocated config request string.
  //
  if (AllocatedRequest) {
    FreePool (ConfigRequest);
    ConfigRequest = NULL;
  }

  //
  // Set Progress string to the original request string.
  //
  if (Request == NULL) {
    *Progress = NULL;
  } else if (StrStr (Request, L"OFFSET") == NULL) {
    *Progress = Request + StrLen (Request);
  }

  return Status;
}

/**
  This function applies changes in a driver's configuration.
  Input is a Configuration, which has the routing data for this
  driver followed by name / value configuration pairs. The driver
  must apply those pairs to its configurable storage. If the
  driver's configuration is stored in a linear block of data
  and the driver's name / value pairs are in <BlockConfig>
  format, it may use the ConfigToBlock helper function (above) to
  simplify the job. Currently not implemented.

  @param[in]  This           Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in]  Configuration  A null-terminated Unicode string in
                             <ConfigString> format.
  @param[out] Progress       A pointer to a string filled in with the
                             offset of the most recent '&' before the
                             first failing name / value pair (or the
                             beginn ing of the string if the failure
                             is in the first name / value pair) or
                             the terminating NULL if all was
                             successful.

  @retval EFI_SUCCESS             The results have been distributed or are
                                  awaiting distribution.
  @retval EFI_OUT_OF_RESOURCES    Not enough memory to store the
                                  parts of the results that must be
                                  stored awaiting possible future
                                  protocols.
  @retval EFI_INVALID_PARAMETERS  Passing in a NULL for the
                                  Results parameter would result
                                  in this type of error.
  @retval EFI_NOT_FOUND           Target for the specified routing data
                                  was not found.
**/
EFI_STATUS
EFIAPI
HddPasswordFormRouteConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Configuration,
  OUT EFI_STRING                             *Progress
  )
{
  if (Configuration == NULL || Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check routing data in <ConfigHdr>.
  // Note: if only one Storage is used, then this checking could be skipped.
  //
  if (!HiiIsConfigHdrMatch (Configuration, &mHddPasswordVendorGuid, mHddPasswordVendorStorageName)) {
    *Progress = Configuration;
    return EFI_NOT_FOUND;
  }

  *Progress = Configuration + StrLen (Configuration);
  return EFI_SUCCESS;
}

/**
  This function is called to provide results data to the driver.
  This data consists of a unique key that is used to identify
  which data is either being passed back or being asked for.

  @param[in]  This               Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in]  Action             Specifies the type of action taken by the browser.
  @param[in]  QuestionId         A unique value which is sent to the original
                                 exporting driver so that it can identify the type
                                 of data to expect. The format of the data tends to
                                 vary based on the opcode that enerated the callback.
  @param[in]  Type               The type of value for the question.
  @param[in]  Value              A pointer to the data being sent to the original
                                 exporting driver.
  @param[out]  ActionRequest     On return, points to the action requested by the
                                 callback function.

  @retval EFI_SUCCESS            The callback successfully handled the action.
  @retval EFI_OUT_OF_RESOURCES   Not enough storage is available to hold the
                                 variable and its data.
  @retval EFI_DEVICE_ERROR       The variable could not be saved.
  @retval EFI_UNSUPPORTED        The specified Action is not supported by the
                                 callback.Currently not implemented.
  @retval EFI_INVALID_PARAMETERS Passing in wrong parameter.
  @retval Others                 Other errors as indicated.
**/
EFI_STATUS
EFIAPI
HddPasswordFormCallback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  EFI_BROWSER_ACTION                     Action,
  IN  EFI_QUESTION_ID                        QuestionId,
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest
  )
{
  HDD_PASSWORD_DXE_PRIVATE_DATA   *Private;
  EFI_STRING_ID                    DeviceFormTitleToken;
  HDD_PASSWORD_CONFIG              *IfrData;
  HDD_PASSWORD_CONFIG_FORM_ENTRY   *ConfigFormEntry;
  EFI_STATUS                       Status;
  EFI_ATA_PASS_THRU_PROTOCOL       *AtaPassThru;
  CHAR16                           *Password;
  CHAR8                            AsciiPassword[32 + 1];
  ATA_IDENTIFY_DATA                IdentifyData;
  EFI_INPUT_KEY                    Key;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    //
    // Do nothing for other UEFI Action. Only do call back when data is changed.
    //
    return EFI_UNSUPPORTED;
  }

  Private  = HDD_PASSWORD_DXE_PRIVATE_FROM_THIS (This);
  Password = NULL;
  ZeroMem (AsciiPassword, sizeof (AsciiPassword));

  //
  // Retrive data from Browser
  //
  IfrData = AllocateZeroPool (sizeof (HDD_PASSWORD_CONFIG));
  ASSERT (IfrData != NULL);
  if (!HiiGetBrowserData (&mHddPasswordVendorGuid, mHddPasswordVendorStorageName, sizeof (HDD_PASSWORD_CONFIG), (UINT8 *) IfrData)) {
    FreePool (IfrData);
    return EFI_NOT_FOUND;
  }

  Status = EFI_SUCCESS;

  switch (QuestionId) {
  case KEY_HDD_USER_PASSWORD:
    //
    // Only used to update the state.
    //
    if ((Type == EFI_IFR_TYPE_STRING) && (Value->string == 0) && (Private->Current->PasswordState == BROWSER_STATE_SET_PASSWORD)) {
      Private->Current->PasswordState = BROWSER_STATE_VALIDATE_PASSWORD;
      return EFI_INVALID_PARAMETER;
    }

    //
    // When try to set a new password, user will be chanlleged with old password.
    // The Callback is responsible for validating old password input by user,
    // If Callback return EFI_SUCCESS, it indicates validation pass.
    //
    switch (Private->Current->PasswordState) {
      case BROWSER_STATE_VALIDATE_PASSWORD:
        Status = ValidatePassword (Private, Value->string);
        if (Status == EFI_SUCCESS) {
          Private->Current->PasswordState = BROWSER_STATE_SET_PASSWORD;
        }
        break;

      case BROWSER_STATE_SET_PASSWORD:
        Status = SetPassword (Private, Value->string);
        Private->Current->PasswordState = BROWSER_STATE_VALIDATE_PASSWORD;
        break;

      default:
        break;
    }

    CopyMem (IfrData, &Private->Current->IfrData, sizeof (HDD_PASSWORD_CONFIG));
    break;
  case KEY_HDD_MASTER_PASSWORD:
    if ((Type == EFI_IFR_TYPE_STRING) && (Value->string == 0)) {
      return EFI_INVALID_PARAMETER;
    }
    Password = HiiGetString (Private->HiiHandle, Value->string, NULL);
    if ((Password != NULL) && (Password[0] != 0)) {
      Status = gBS->HandleProtocol (Private->Current->Controller, &gEfiAtaPassThruProtocolGuid, (VOID**)&AtaPassThru);
      ASSERT_EFI_ERROR (Status);
      ASSERT (StrLen (Password) <= 32);
      UnicodeStrToAsciiStrS (Password, AsciiPassword, sizeof (AsciiPassword));
      Status = HddPasswordSetHddPassword (
                 Private->Current->Bus,
                 Private->Current->Device,
                 Private->Current->Function,
                 Private->Current->Port,
                 Private->Current->PortMultiplierPort,
                 1,
                 1,
                 1,
                 NULL,
                 AsciiPassword
                 );

      if (EFI_ERROR (Status)) {
        do {
          CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Setting master password fails, Please check your password.", L"Press ENTER to continue", NULL);
        } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);
        goto EXIT;
      }

      Status = GetHddDeviceIdentifyData (AtaPassThru, Private->Current->Port, Private->Current->PortMultiplierPort, &IdentifyData);
      if (EFI_ERROR (Status)) {
        goto EXIT;
      }

      //
      // update the device security status.
      //
      GetHddPasswordSecurityStatus (&IdentifyData, IfrData);
      CopyMem (&Private->Current->IfrData, IfrData, sizeof (HDD_PASSWORD_CONFIG));
    }

    break;

  default:
    if ((QuestionId >= KEY_HDD_DEVICE_ENTRY_BASE) && (QuestionId < (mNumberOfHddDevices + KEY_HDD_DEVICE_ENTRY_BASE))) {
      //
      // In case goto the device configuration form, update the device form title.
      //
      ConfigFormEntry = HddPasswordGetConfigFormEntryByIndex ((UINT32) (QuestionId - KEY_HDD_DEVICE_ENTRY_BASE));
      ASSERT (ConfigFormEntry != NULL);

      DeviceFormTitleToken = (EFI_STRING_ID) STR_IDE_SECURITY_HD;
      HiiSetString (Private->HiiHandle, DeviceFormTitleToken, ConfigFormEntry->HddString, NULL);

      Private->Current = ConfigFormEntry;
      CopyMem (IfrData, &ConfigFormEntry->IfrData, sizeof (HDD_PASSWORD_CONFIG));

    }

    break;
  }

  if (!EFI_ERROR (Status)) {
    //
    // Pass changed uncommitted data back to Form Browser
    //
    HiiSetBrowserData (&mHddPasswordVendorGuid, mHddPasswordVendorStorageName, sizeof (HDD_PASSWORD_CONFIG), (UINT8 *) IfrData, NULL);
  }

EXIT:

  //
  // clear input password for security
  //
  if (Password != NULL) {
    ZeroMem (Password, StrSize (Password));
    ZeroMem (AsciiPassword, AsciiStrSize (AsciiPassword));
    FreePool (Password);
  }

  FreePool (IfrData);
  return Status;
}

/**
  Updates the HDD Password configuration form to add an entry for the attached
  ata harddisk device specified by the Controller.

  @param[in] HiiHandle            The HII Handle associated with the registered package list.
  @param[in] AtaPassThru          Pointer to ATA_PASSTHRU instance.
  @param[in] Controller           The controller handle of the attached ata controller.
  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.

  @retval EFI_SUCCESS             The Hdd Password configuration form is updated.
  @retval EFI_OUT_OF_RESOURCES    Failed to allocate memory.
  @retval Others                  Other errors as indicated.

**/
EFI_STATUS
HddPasswordConfigUpdateForm (
  IN EFI_HII_HANDLE              HiiHandle,
  IN EFI_ATA_PASS_THRU_PROTOCOL  *AtaPassThru,
  IN EFI_HANDLE                  Controller,
  IN UINTN                       Bus,
  IN UINTN                       Device,
  IN UINTN                       Function,
  IN UINT16                      Port,
  IN UINT16                      PortMultiplierPort
  )
{
  LIST_ENTRY                       *Entry;
  HDD_PASSWORD_CONFIG_FORM_ENTRY   *ConfigFormEntry;
  BOOLEAN                          EntryExisted;
  BOOLEAN                          Locked;
  EFI_STATUS                       Status;
  VOID                             *StartOpCodeHandle;
  VOID                             *EndOpCodeHandle;
  EFI_IFR_GUID_LABEL               *StartLabel;
  EFI_IFR_GUID_LABEL               *EndLabel;
  CHAR16                           HddString[40];
  ATA_IDENTIFY_DATA                IdentifyData;
  CHAR8                            Password[32];
  EFI_INPUT_KEY                    Key;
  UINT16                           RetryCount;
  BOOLEAN                          HashOk;
  UINT8                            HashData[SHA256_DIGEST_SIZE];
  UINT8                            SavedHashData[SHA256_DIGEST_SIZE];
  UINT8                            SavedSaltData[PASSWORD_SALT_SIZE];

  ConfigFormEntry = NULL;
  EntryExisted    = FALSE;
  Locked          = TRUE;
  RetryCount      = 0;

  EFI_LIST_FOR_EACH (Entry, &mHddPasswordConfigFormList) {
    ConfigFormEntry = BASE_CR (Entry, HDD_PASSWORD_CONFIG_FORM_ENTRY, Link);

    if ((ConfigFormEntry->Bus == Bus) &&
        (ConfigFormEntry->Device == Device) &&
        (ConfigFormEntry->Function == Function) &&
        (ConfigFormEntry->Port == Port) &&
        (ConfigFormEntry->PortMultiplierPort == PortMultiplierPort)) {
      EntryExisted = TRUE;
      break;
    }
  }

  if (!EntryExisted) {
    //
    // Add a new form.
    //
    ConfigFormEntry = AllocateZeroPool (sizeof (HDD_PASSWORD_CONFIG_FORM_ENTRY));
    if (ConfigFormEntry == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    InitializeListHead (&ConfigFormEntry->Link);
    ConfigFormEntry->Controller = Controller;
    ConfigFormEntry->Bus        = Bus;
    ConfigFormEntry->Device     = Device;
    ConfigFormEntry->Function   = Function;
    ConfigFormEntry->Port       = Port;
    ConfigFormEntry->PortMultiplierPort = PortMultiplierPort;
    ConfigFormEntry->PasswordState = BROWSER_STATE_VALIDATE_PASSWORD;

    DEBUG ((DEBUG_INFO, "HddPasswordDxe: Create new form for device[%d][%d] at Bus 0x%x Dev 0x%x Func 0x%x\n", Port, PortMultiplierPort, Bus, Device, Function));
    //
    // Get attached harddisk model number
    //
    Status = GetHddDeviceIdentifyData (AtaPassThru, Port, PortMultiplierPort, &IdentifyData);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    GetHddDeviceModelNumber (&IdentifyData, HddString);
    //
    // Compose the HDD title string and help string of this port and create a new EFI_STRING_ID.
    //
    UnicodeSPrint (ConfigFormEntry->HddString, 64, L"HDD %d:%s", mNumberOfHddDevices, HddString);
    ConfigFormEntry->TitleToken     = HiiSetString (HiiHandle, 0, ConfigFormEntry->HddString, NULL);
    ConfigFormEntry->TitleHelpToken = HiiSetString (HiiHandle, 0, L"Set HDD Password", NULL);

    GetHddPasswordSecurityStatus (&IdentifyData, &ConfigFormEntry->IfrData);

    InsertTailList (&mHddPasswordConfigFormList, &ConfigFormEntry->Link);

    //
    // Init OpCode Handle
    //
    StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    ASSERT (StartOpCodeHandle != NULL);

    EndOpCodeHandle = HiiAllocateOpCodeHandle ();
    ASSERT (EndOpCodeHandle != NULL);

    //
    // Create Hii Extend Label OpCode as the start opcode
    //
    StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
    StartLabel->Number       = HDD_DEVICE_ENTRY_LABEL;

    //
    // Create Hii Extend Label OpCode as the end opcode
    //
    EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
    EndLabel->Number       = HDD_DEVICE_LABEL_END;

    mNumberOfHddDevices = 0;
    EFI_LIST_FOR_EACH (Entry, &mHddPasswordConfigFormList) {
      ConfigFormEntry = BASE_CR (Entry, HDD_PASSWORD_CONFIG_FORM_ENTRY, Link);

      HiiCreateGotoOpCode (
        StartOpCodeHandle,                                // Container for dynamic created opcodes
        FORMID_HDD_DEVICE_FORM,                           // Target Form ID
        ConfigFormEntry->TitleToken,                      // Prompt text
        ConfigFormEntry->TitleHelpToken,                  // Help text
        EFI_IFR_FLAG_CALLBACK,                            // Question flag
        (UINT16)(KEY_HDD_DEVICE_ENTRY_BASE + mNumberOfHddDevices)   // Question ID
        );

      mNumberOfHddDevices++;
    }

    HiiUpdateForm (
      HiiHandle,
      &mHddPasswordVendorGuid,
      FORMID_HDD_MAIN_FORM,
      StartOpCodeHandle,
      EndOpCodeHandle
      );

    HiiFreeOpCodeHandle (StartOpCodeHandle);
    HiiFreeOpCodeHandle (EndOpCodeHandle);

    //
    // Check the device security status.
    // If it's locked and not frozen, popup a window to wait user input.
    // If it's unlocked and frozen, popup a window to wait user input.
    // The former is used to really unlock the HDD, the latter is used to
    // simulate a unlock operation to the HDD to meet security requirement.
    //
    if ((ConfigFormEntry->IfrData.Supported) &&
        (ConfigFormEntry->IfrData.Enabled)) {
      //
      // As soon as the HDD password is in enable state, we pop up a window to unlock hdd
      // no matter it's really in locked or frozen state.
      // This way force user to enter password every time to provide best safety.
      //
      gST->ConOut->ClearScreen (gST->ConOut);
      while (Locked) {
        Status = PopupHddPasswordInputWindows (ConfigFormEntry->HddString, Password);
        gST->ConOut->ClearScreen (gST->ConOut);

        if (!EFI_ERROR (Status)) {
          if ((ConfigFormEntry->IfrData.Locked) &&
              (ConfigFormEntry->IfrData.Frozen == 0)) {
            //
            // The HDD is in locked state, unlock it by user input.
            //
            Status = HddPasswordUnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, 0, Password);
            if (!EFI_ERROR (Status)) {
              Status = GetHddDeviceIdentifyData (AtaPassThru, Port, PortMultiplierPort, &IdentifyData);
              ASSERT_EFI_ERROR (Status);
              if (EFI_ERROR (Status)) {
                return Status;
              }

              //
              // Check the device security status again.
              //
              GetHddPasswordSecurityStatus (&IdentifyData, &ConfigFormEntry->IfrData);
              Locked = FALSE;
            }
          } else {
            //
            // Get corresponding password from variable and compare if the hash value is same.
            //
            Status = HddPasswordGetPasswordHash (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
            if (EFI_ERROR(Status)) {
              return Status;
            }

            //
            // The device is in unlock or freeze state. In this case, we still ask for user input.
            // we would compare it with password hash data saved in variable region.
            //
            ZeroMem (HashData, sizeof (HashData));
            HashOk = GenerateCredential ((UINT8 *)Password, SavedSaltData, HashData);

            if (HashOk) {
              //
              // We treat the device as unlocked at this case.
              //
              if (CompareMem (SavedHashData, HashData, SHA256_DIGEST_SIZE) == 0) {
                //
                // Force to sync Hddpassword data structure in variable and SMM.
                //
                Status = HddPasswordUnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, 0, Password);
                if (!EFI_ERROR (Status)) {
                  Locked = FALSE;
                }
              } else {
                Status = EFI_SECURITY_VIOLATION;
              }
            } else {
              ASSERT (FALSE);
              return EFI_SECURITY_VIOLATION;
            }
          }
          //
          // clear the temporary password buffer for security.
          //
          ZeroMem (Password, sizeof (Password));
          ZeroMem (HashData, sizeof (HashData));
          ZeroMem (SavedHashData, sizeof (SavedHashData));
          ZeroMem (SavedSaltData, sizeof (SavedSaltData));

          if (EFI_ERROR (Status)) {
            RetryCount ++;
            if (RetryCount < MAX_HDD_PASSWORD_RETRY_COUNT) {
              do {
                CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Invalid password.", L"Press ENTER to retry", NULL);
              } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);
              continue;
            } else {
              do {
                CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Hdd password retry count is expired. Please shutdown the machine.", L"Press ENTER to shutdown", NULL);
              } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);
              gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
              break;
            }
          }
        } else if (Status == EFI_ABORTED) {
          break;
        }
      }
    }
  }

  return EFI_SUCCESS;
}

/**
  Hdd Password Notify Protocol notification event handler.

  This protocol will be installed by platform after ahci oprom and raid oprom loaded.
  This event handler will try to unlock device again if it found the device ever got
  unlocked but now become locked. This case is mainly caused by legacy oprom which
  may reset port and device and cause security lock state machine change to locked state
  again.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.

**/
VOID
EFIAPI
HddPasswordRetryUnlockEvent (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS                        Status;
  LIST_ENTRY                        *Entry;
  HDD_PASSWORD_CONFIG_FORM_ENTRY    *ConfigFormEntry;
  ATA_IDENTIFY_DATA                 IdentifyData;
  EFI_ATA_PASS_THRU_PROTOCOL        *AtaPassThru;
  HDD_PASSWORD_CONFIG               IfrData;
  UINTN                             Bus;
  UINTN                             Device;
  UINTN                             Function;
  UINT16                            Port;
  UINT16                            PortMultiplierPort;

  //
  // ROYAL_PARK_OVERRIDE: RoyalParkOverrideBegin - RPCO-0104
  //
  if (PcdGetBool (PcdSkipHddPasswordPrompt)) {
    DEBUG ((DEBUG_INFO, "Skip Hdd Password Prompt\n"));
    return;
  }
  //
  // ROYAL_PARK_OVERRIDE: RoyalParkOverrideEnd - RPCO-0104
  //

  EFI_LIST_FOR_EACH (Entry, &mHddPasswordConfigFormList) {
    ConfigFormEntry = BASE_CR (Entry, HDD_PASSWORD_CONFIG_FORM_ENTRY, Link);
    Status = gBS->HandleProtocol (
                    ConfigFormEntry->Controller,
                    &gEfiAtaPassThruProtocolGuid,
                    (VOID **) &AtaPassThru
                    );
    if (EFI_ERROR (Status)) {
      break;
    }

    Bus                = ConfigFormEntry->Bus;
    Device             = ConfigFormEntry->Device;
    Function           = ConfigFormEntry->Function;
    Port               = ConfigFormEntry->Port;
    PortMultiplierPort = ConfigFormEntry->PortMultiplierPort;
    Status = GetHddDeviceIdentifyData (AtaPassThru, Port, PortMultiplierPort, &IdentifyData);
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Check the device security status.
    //
    GetHddPasswordSecurityStatus (&IdentifyData, &IfrData);

    //
    // if the device ever got unlocked and now is locked state, then unlock it again.
    //
    if ((IfrData.Frozen == 0) && (IfrData.Locked == 1) && (ConfigFormEntry->IfrData.Locked == 0)) {
      Status = HddPasswordUnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, 0, NULL);
      DEBUG ((EFI_D_ERROR, "HddPasswordDxe: Retry unlock device[%d][%d] at Bus 0x%x Dev 0x%x Func 0x%x with %r\n", ConfigFormEntry->Port, ConfigFormEntry->PortMultiplierPort, ConfigFormEntry->Bus, ConfigFormEntry->Device, ConfigFormEntry->Function, Status));
      if (EFI_ERROR (Status)) {
        break;
      }
    }
  }

  return ;
}


/**
  Ata Pass Thru Protocol notification event handler.

  Check attached harddisk status to see if it's locked. If yes, then pop up a password windows to require user input.
  It also registers a form for user configuration on Hdd password configuration.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.

**/
VOID
EFIAPI
HddPasswordNotificationEvent (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS                        Status;
  HDD_PASSWORD_DXE_PRIVATE_DATA     *Private;
  EFI_ATA_PASS_THRU_PROTOCOL        *AtaPassThru;
  UINT16                            Port;
  UINT16                            PortMultiplierPort;
  EFI_HANDLE                        Controller;
  EFI_HANDLE                        *HandleBuffer;
  UINTN                             HandleCount;
  UINTN                             Index;
  EFI_PCI_IO_PROTOCOL               *PciIo;
  UINTN                             SegNum;
  UINTN                             BusNum;
  UINTN                             DevNum;
  UINTN                             FuncNum;

  Private = (HDD_PASSWORD_DXE_PRIVATE_DATA *)Context;

  //
  // ROYAL_PARK_OVERRIDE: RoyalParkOverrideBegin - RPCO-0104
  //
  if (PcdGetBool (PcdSkipHddPasswordPrompt)) {
    DEBUG ((DEBUG_INFO, "Skip Hdd Password Prompt\n"));
    return;
  }
  //
  // ROYAL_PARK_OVERRIDE: RoyalParkOverrideEnd - RPCO-0104
  //

  //
  // Locate all handles of AtaPassThru protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiAtaPassThruProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //
  // Check attached hard disk status to see if it's locked
  //
  for (Index = 0; Index < HandleCount; Index += 1) {
    Controller = HandleBuffer[Index];
    Status = gBS->HandleProtocol (
                    Controller,
                    &gEfiAtaPassThruProtocolGuid,
                    (VOID **) &AtaPassThru
                    );
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Ignore those logical ATA_PASS_THRU instance.
    //
    if ((AtaPassThru->Mode->Attributes & EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL) == 0) {
      continue;
    }

    Status = gBS->HandleProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo
                    );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      break;
    }

    Status = PciIo->GetLocation (
                      PciIo,
                      &SegNum,
                      &BusNum,
                      &DevNum,
                      &FuncNum
                      );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // traverse all attached harddisk devices to update form and unlock it
    //
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
        //
        // Find out the attached harddisk devices.
        // Try to add a HDD Password configuration page for the attached devices.
        //
        gBS->RestoreTPL (TPL_APPLICATION);
        Status = HddPasswordConfigUpdateForm (Private->HiiHandle, AtaPassThru, Controller, BusNum, DevNum, FuncNum, Port, PortMultiplierPort);
        gBS->RaiseTPL (TPL_CALLBACK);
        if (EFI_ERROR (Status)) {
          break;
        }
      }
    }
  }

  FreePool (HandleBuffer);
  return ;
}

/**
  Initialize the HDD Password configuration form.

  @param[out] Instance             Pointer to private instance.

  @retval EFI_SUCCESS              The HDD Password configuration form is initialized.
  @retval EFI_OUT_OF_RESOURCES     Failed to allocate memory.
  @retval Others                   Other errors as indicated.
**/
EFI_STATUS
HddPasswordConfigFormInit (
  OUT HDD_PASSWORD_DXE_PRIVATE_DATA    **Instance
  )
{
  EFI_STATUS                       Status;
  HDD_PASSWORD_DXE_PRIVATE_DATA    *Private;

  InitializeListHead (&mHddPasswordConfigFormList);

  Private = AllocateZeroPool (sizeof (HDD_PASSWORD_DXE_PRIVATE_DATA));
  if (Private == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Private->Signature   = HDD_PASSWORD_DXE_PRIVATE_SIGNATURE;

  Private->ConfigAccess.ExtractConfig = HddPasswordFormExtractConfig;
  Private->ConfigAccess.RouteConfig   = HddPasswordFormRouteConfig;
  Private->ConfigAccess.Callback      = HddPasswordFormCallback;

  //
  // Install Device Path Protocol and Config Access protocol to driver handle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Private->DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mHddPasswordHiiVendorDevicePath,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &Private->ConfigAccess,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    FreePool(Private);
    return Status;
  }

  //
  // Publish our HII data
  //
  Private->HiiHandle = HiiAddPackages (
                         &mHddPasswordVendorGuid,
                         Private->DriverHandle,
                         HddPasswordDxeStrings,
                         HddPasswordBin,
                         NULL
                         );
  if (Private->HiiHandle == NULL) {
    FreePool(Private);
    return EFI_OUT_OF_RESOURCES;
  }

  *Instance = Private;
  return Status;
}

/**
  Main entry for this driver.

  @param ImageHandle     Image handle this driver.
  @param SystemTable     Pointer to SystemTable.

  @retval EFI_SUCESS     This function always complete successfully.

**/
EFI_STATUS
EFIAPI
HddPasswordDxeInit (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                     Status;
  HDD_PASSWORD_DXE_PRIVATE_DATA  *Private;

  Private = NULL;

  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &mSmmCommunication);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Initialize the configuration form of HDD Password.
  //
  Status = HddPasswordConfigFormInit (&Private);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Register HddPasswordNotificationEvent() notify function.
  //
  EfiCreateProtocolNotifyEvent (
    &gEfiAtaPassThruProtocolGuid,
    TPL_CALLBACK,
    HddPasswordNotificationEvent,
    (VOID *)Private,
    &mHddPasswordRegistration
    );

  //
  // Register HddPasswordRetryUnlockEvent () notify function to unlock device again.
  // It's because legacy ahci oprom or raid oprom may reset device and cause those
  // unlocked devices lock again.
  //
  EfiCreateProtocolNotifyEvent (
    &gEfiHddPasswordNotifyProtocolGuid,
    TPL_CALLBACK,
    HddPasswordRetryUnlockEvent,
    NULL,
    &mHddPasswordRegistration
    );

  return Status;
}
