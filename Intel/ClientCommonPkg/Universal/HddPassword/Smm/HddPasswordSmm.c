//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  HDD password smm driver which is used to support HDD security feature at s3 path.

  Caution: This file requires additional review when modified.
  This SMI handle will have external input HDD device information and password.
  This external input must be validated carefully to avoid security issue.
  Those SMI API is exposed even after even SmmReadyToLock, because they are need to
  be invoked after OROM dispatch or in setup page.

Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation
(if any) is furnished under a license and may only be used or
copied in accordance with the terms of the license.  Except as
permitted by such license, no part of this software or
documentation may be reproduced, stored in a retrieval system, or
transmitted in any form or by any means without the express written
consent of Intel Corporation.

**/

#include "HddPasswordSmm.h"

//
// To unlock the HDD password at S3 Resume, restored the following registers.
//
const HDD_HC_PCI_REGISTER_SAVE mHddHcRegisterSaveTemplate[] = {
  {0x4,  S3BootScriptWidthUint16},
  {0x9,  S3BootScriptWidthUint8},
  {0x10, S3BootScriptWidthUint32},
  {0x14, S3BootScriptWidthUint32},
  {0x18, S3BootScriptWidthUint32},
  {0x1C, S3BootScriptWidthUint32},
  {0x20, S3BootScriptWidthUint32},
  {0x24, S3BootScriptWidthUint32},
  {0x3c, S3BootScriptWidthUint8},
  {0x3d, S3BootScriptWidthUint8},
  {0x40, S3BootScriptWidthUint16},
  {0x42, S3BootScriptWidthUint16},
  {0x92, S3BootScriptWidthUint16},
  {0x94, S3BootScriptWidthUint32},
  {0x9C, S3BootScriptWidthUint32}
};

typedef struct _HDD_DEVICE_LIST {
  LIST_ENTRY          Link;
  EFI_HDD_DEVICE_LIST DeviceList;
} HDD_DEVICE_LIST;

UINT8                mSwSmiValue;
LIST_ENTRY           mDeviceList     = INITIALIZE_LIST_HEAD_VARIABLE (mDeviceList);
UINTN                mDeviceListSize = 0;
//
// DMA can not read/write data to smram, so we pre-allocates buffer from AcpiNVS.
//
VOID                 *mBuffer = NULL;
EFI_IDE_REGISTERS    mIdeRegisters[2];
UINT32               mAhciBar = 0;
EFI_AHCI_REGISTERS   mAhciRegisters;

/**
  Check if the password is full zero.

  @param[in]   Password       Points to the data buffer

  @retval      TRUE           This password string is full zero.
  @retval      FALSE          This password string is not full zero.

**/
BOOLEAN
PasswordIsFullZero (
  IN UINT8                    *Password
  )
{
  UINTN                       Index;

  for (Index = 0; Index < HDD_PASSWORD_MAX_LENGTH; Index++) {
    if (Password[Index] != 0) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Generate Salt value.

  @param[in, out]   SaltValue           Points to the salt buffer, 32 bytes

**/
VOID
GenSalt (
  IN OUT UINT8  *SaltValue
  )
{
  RandomSeed (NULL, 0);
  RandomBytes (SaltValue, PASSWORD_SALT_SIZE);
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

  HashSize = Sha256GetContextSize ();
  Hash     = AllocateZeroPool (HashSize);
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
  Calculate hdd password hash data and save it to non-volatile variable region.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
SavePasswordToVariable (
  IN  UINTN                         Bus,
  IN  UINTN                         Device,
  IN  UINTN                         Function,
  IN  UINT16                        Port,
  IN  UINT16                        PortMultiplierPort,
  IN  CHAR8                         *Password
  )
{
  EFI_STATUS                        Status;
  VOID                              *List;
  UINTN                             ListSize;
  EFI_HDD_DEVICE_LIST               *DeviceNode;
  EFI_HDD_DEVICE_LIST               *DeviceList;
  UINTN                             Index;
  EFI_SMM_VARIABLE_PROTOCOL         *SmmVariable;
  BOOLEAN                           HashOk;
  UINT8                             HashData[SHA256_DIGEST_SIZE];
  UINT8                             SaltData[PASSWORD_SALT_SIZE];

  List       = NULL;
  ListSize   = 0;
  DeviceList = NULL;
  DeviceNode = NULL;

  ZeroMem (HashData, sizeof (HashData));
  ZeroMem (SaltData, sizeof (SaltData));
  //
  // If password is NULL, it means we want to clean password field saved in variable region.
  //
  if (Password != NULL) {
    GenSalt (SaltData);
    HashOk = GenerateCredential ((UINT8 *)Password, SaltData, HashData);
    if (!HashOk) {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = gSmst->SmmLocateProtocol (&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&SmmVariable);
  ASSERT_EFI_ERROR (Status);

  Status = SmmVariable->SmmGetVariable (
                  L"HddPassword",
                  &gEfiHddPasswordSecurityVariableGuid,
                  NULL,
                  &ListSize,
                  List
                  );

  if (Status == EFI_NOT_FOUND) {
    DEBUG ((EFI_D_ERROR, "HddPasswordSmm: now adding a new device node[%d][%d]\n", Port, PortMultiplierPort));
    DeviceNode = AllocateZeroPool (sizeof (EFI_HDD_DEVICE_LIST));
    ASSERT (DeviceNode != NULL);

    DeviceNode->Bus      = (UINT32)Bus;
    DeviceNode->Device   = (UINT32)Device;
    DeviceNode->Function = (UINT32)Function;
    DeviceNode->Port     = Port;
    DeviceNode->PortMultiplierPort = PortMultiplierPort;
    if (Password != NULL) {
      CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
      CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);
    } else {
      ZeroMem (DeviceNode->Password, SHA256_DIGEST_SIZE);
      ZeroMem (DeviceNode->PasswordSalt, PASSWORD_SALT_SIZE);
    }
    DeviceList = DeviceNode;
    ListSize   = sizeof (EFI_HDD_DEVICE_LIST);
  } else if (Status == EFI_BUFFER_TOO_SMALL) {

    //
    // Allocate the buffer to return
    //
    List = AllocateZeroPool (ListSize);
    if (List == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmmVariable->SmmGetVariable (
                    L"HddPassword",
                    &gEfiHddPasswordSecurityVariableGuid,
                    NULL,
                    &ListSize,
                    List
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "SavePasswordToVariable fails with %r\n", Status));
      FreePool (List);
      goto EXIT;
    }

    for (Index = 0; Index < ListSize / sizeof (EFI_HDD_DEVICE_LIST); Index += 1) {
      DeviceNode = (EFI_HDD_DEVICE_LIST *)((UINTN)List + Index * sizeof (EFI_HDD_DEVICE_LIST));

      if ((DeviceNode->Bus == Bus) &&
          (DeviceNode->Device == Device) &&
          (DeviceNode->Function == Function) &&
          (DeviceNode->Port == Port) &&
          (DeviceNode->PortMultiplierPort == PortMultiplierPort)) {
        //
        // if the device node has existed, then only update the password.
        //
        DEBUG ((EFI_D_ERROR, "HddPasswordSmm: now update existed device node[%d][%d]\n", Port, PortMultiplierPort));
        if (Password != NULL) {
          CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
          CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);
        } else {
          ZeroMem (DeviceNode->Password, SHA256_DIGEST_SIZE);
          ZeroMem (DeviceNode->PasswordSalt, PASSWORD_SALT_SIZE);
        }
        DeviceList = List;
        break;
      }
    }

    //
    // Device node is not found, so add the new device node into device list variable.
    //
    if (Index >= ListSize / sizeof (EFI_HDD_DEVICE_LIST)) {
      DeviceList = AllocateZeroPool (sizeof (EFI_HDD_DEVICE_LIST) + ListSize);

      if (DeviceList == NULL) {
        FreePool (List);
        Status = EFI_OUT_OF_RESOURCES;
        goto EXIT;
      }

      CopyMem (DeviceList, List, ListSize);
      FreePool (List);

      DeviceNode = (EFI_HDD_DEVICE_LIST *)((UINTN)DeviceList + ListSize);
      DeviceNode->Bus      = (UINT32) Bus;
      DeviceNode->Device   = (UINT32) Device;
      DeviceNode->Function = (UINT32) Function;
      DeviceNode->Port     = Port;
      DeviceNode->PortMultiplierPort = PortMultiplierPort;
      if (Password != NULL) {
        CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
        CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);
      } else {
        ZeroMem (DeviceNode->Password, SHA256_DIGEST_SIZE);
        ZeroMem (DeviceNode->PasswordSalt, PASSWORD_SALT_SIZE);
      }

      ListSize = sizeof (EFI_HDD_DEVICE_LIST) + ListSize;
      DEBUG ((EFI_D_ERROR, "HddPassSmm: now adding a new device node[%d][%d]\n", Port, PortMultiplierPort));
    }
  } else {
    ASSERT (FALSE);
    Status = EFI_INVALID_PARAMETER;
    goto EXIT;
  }

  Status = SmmVariable->SmmSetVariable (
                  L"HddPassword",
                  &gEfiHddPasswordSecurityVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                  ListSize,
                  DeviceList
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SavePasswordToVariable fails with %r\n", Status));
    goto EXIT;
  }

EXIT:
  if (DeviceList != NULL) {
    FreePool (DeviceList);
  }

  return Status;
}

/**
  Save hdd password hash data to non-volatile variable region.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in] HashData             The hash data of hdd password of attached ATA device.
  @param[in] SaltData             The salt data of hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
SavePasswordHashToVariable (
  IN  UINTN                         Bus,
  IN  UINTN                         Device,
  IN  UINTN                         Function,
  IN  UINT16                        Port,
  IN  UINT16                        PortMultiplierPort,
  IN  CHAR8                         *HashData,
  IN  CHAR8                         *SaltData
  )
{
  EFI_STATUS                        Status;
  VOID                              *List;
  UINTN                             ListSize;
  EFI_HDD_DEVICE_LIST               *DeviceNode;
  EFI_HDD_DEVICE_LIST               *DeviceList;
  UINTN                             Index;
  EFI_SMM_VARIABLE_PROTOCOL         *SmmVariable;

  List       = NULL;
  ListSize   = 0;
  DeviceList = NULL;
  DeviceNode = NULL;

  Status = gSmst->SmmLocateProtocol (&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&SmmVariable);
  ASSERT_EFI_ERROR (Status);

  Status = SmmVariable->SmmGetVariable (
                  L"HddPassword",
                  &gEfiHddPasswordSecurityVariableGuid,
                  NULL,
                  &ListSize,
                  List
                  );

  if (Status == EFI_NOT_FOUND) {
    DEBUG ((EFI_D_ERROR, "HddPasswordSmm: now adding a new device node[%d][%d]\n", Port, PortMultiplierPort));
    DeviceNode = AllocateZeroPool (sizeof (EFI_HDD_DEVICE_LIST));
    ASSERT (DeviceNode != NULL);

    DeviceNode->Bus      = (UINT32)Bus;
    DeviceNode->Device   = (UINT32)Device;
    DeviceNode->Function = (UINT32)Function;
    DeviceNode->Port     = Port;
    DeviceNode->PortMultiplierPort = PortMultiplierPort;
    CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
    CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);
    DeviceList = DeviceNode;
    ListSize   = sizeof (EFI_HDD_DEVICE_LIST);
  } else if (Status == EFI_BUFFER_TOO_SMALL) {
    //
    // Allocate the buffer to return
    //
    List = AllocateZeroPool (ListSize);
    if (List == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmmVariable->SmmGetVariable (
                    L"HddPassword",
                    &gEfiHddPasswordSecurityVariableGuid,
                    NULL,
                    &ListSize,
                    List
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "SavePasswordHashToVariable fails with %r\n", Status));
      FreePool (List);
      goto EXIT;
    }

    for (Index = 0; Index < ListSize / sizeof (EFI_HDD_DEVICE_LIST); Index += 1) {
      DeviceNode = (EFI_HDD_DEVICE_LIST *)((UINTN)List + Index * sizeof (EFI_HDD_DEVICE_LIST));

      if ((DeviceNode->Bus == Bus) &&
          (DeviceNode->Device == Device) &&
          (DeviceNode->Function == Function) &&
          (DeviceNode->Port == Port) &&
          (DeviceNode->PortMultiplierPort == PortMultiplierPort)) {
        //
        // if the device node has existed, then only update the password.
        //
        DEBUG ((EFI_D_ERROR, "HddPasswordSmm: now update existed device node[%d][%d]\n", Port, PortMultiplierPort));
        CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
        CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);
        DeviceList = List;
        break;
      }
    }

    //
    // Device node is not found, so add the new device node into device list variable.
    //
    if (Index >= ListSize / sizeof (EFI_HDD_DEVICE_LIST)) {
      DeviceList = AllocateZeroPool (sizeof (EFI_HDD_DEVICE_LIST) + ListSize);

      if (DeviceList == NULL) {
        FreePool (List);
        Status = EFI_OUT_OF_RESOURCES;
        goto EXIT;
      }

      CopyMem (DeviceList, List, ListSize);
      FreePool (List);

      DeviceNode = (EFI_HDD_DEVICE_LIST *)((UINTN)DeviceList + ListSize);
      DeviceNode->Bus      = (UINT32) Bus;
      DeviceNode->Device   = (UINT32) Device;
      DeviceNode->Function = (UINT32) Function;
      DeviceNode->Port     = Port;
      DeviceNode->PortMultiplierPort = PortMultiplierPort;
      CopyMem (DeviceNode->Password, HashData, SHA256_DIGEST_SIZE);
      CopyMem (DeviceNode->PasswordSalt, SaltData, PASSWORD_SALT_SIZE);

      ListSize = sizeof (EFI_HDD_DEVICE_LIST) + ListSize;
      DEBUG ((EFI_D_ERROR, "HddPassSmm: now adding a new device node[%d][%d]\n", Port, PortMultiplierPort));
    }
  } else {
    ASSERT (FALSE);
    Status = EFI_INVALID_PARAMETER;
    goto EXIT;
  }

  Status = SmmVariable->SmmSetVariable (
                  L"HddPassword",
                  &gEfiHddPasswordSecurityVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                  ListSize,
                  DeviceList
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SavePasswordHashToVariable fails with %r\n", Status));
    goto EXIT;
  }

EXIT:
  if (DeviceList != NULL) {
    FreePool (DeviceList);
  }

  return Status;
}

/**
  Save hdd password to SMM.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database record
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
SavePasswordToSmm (
  IN  UINTN                         Bus,
  IN  UINTN                         Device,
  IN  UINTN                         Function,
  IN  UINT16                        Port,
  IN  UINT16                        PortMultiplierPort,
  IN  CHAR8                         *Password
  )
{
  HDD_DEVICE_LIST                   *List;
  LIST_ENTRY                        *Entry;

  EFI_LIST_FOR_EACH (Entry, &mDeviceList) {
    List = BASE_CR (Entry, HDD_DEVICE_LIST, Link);
    if ((List->DeviceList.Bus == Bus) &&
        (List->DeviceList.Device == Device) &&
        (List->DeviceList.Function == Function) &&
        (List->DeviceList.Port == Port) &&
        (List->DeviceList.PortMultiplierPort == PortMultiplierPort)) {
      CopyMem (List->DeviceList.Password, Password, HDD_PASSWORD_MAX_LENGTH);
      return EFI_SUCCESS;
    }
  }

  List = AllocatePool (sizeof (HDD_DEVICE_LIST));
  if (List == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  List->DeviceList.Bus      = (UINT32)Bus;
  List->DeviceList.Device   = (UINT32)Device;
  List->DeviceList.Function = (UINT32)Function;
  List->DeviceList.Port     = Port;
  List->DeviceList.PortMultiplierPort = PortMultiplierPort;

  CopyMem (&(List->DeviceList.Password), Password, HDD_PASSWORD_MAX_LENGTH);
  InsertHeadList (&mDeviceList, &List->Link);
  return EFI_SUCCESS;
}

/**
  Get hdd password from SMM.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplierPort   The port number of port multiplier of attached ATA device.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_NOT_FOUND           Doesn't find out the HDD info from list.
  @retval EFI_SUCCESS             The function has been successfully executed.

**/
EFI_STATUS
GetPasswordFromSmm (
  IN  UINTN                         Bus,
  IN  UINTN                         Device,
  IN  UINTN                         Function,
  IN  UINT16                        Port,
  IN  UINT16                        PortMultiplierPort,
  IN  CHAR8                         *Password
  )
{
  HDD_DEVICE_LIST                   *List;
  LIST_ENTRY                        *Entry;

  EFI_LIST_FOR_EACH (Entry, &mDeviceList) {
    List = BASE_CR (Entry, HDD_DEVICE_LIST, Link);
    if ((List->DeviceList.Bus == Bus) &&
        (List->DeviceList.Device == Device) &&
        (List->DeviceList.Function == Function) &&
        (List->DeviceList.Port == Port) &&
        (List->DeviceList.PortMultiplierPort == PortMultiplierPort)) {
      CopyMem (Password, List->DeviceList.Password, HDD_PASSWORD_MAX_LENGTH);
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
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
GetPasswordHashFromVariable (
  IN     UINTN                        Bus,
  IN     UINTN                        Device,
  IN     UINTN                        Function,
  IN     UINT16                       Port,
  IN     UINT16                       PortMultiplierPort,
  IN OUT CHAR8                        *HashData,
  IN OUT CHAR8                        *SaltData
  )
{
  EFI_STATUS                         Status;
  VOID                               *List;
  UINTN                              ListSize;
  EFI_HDD_DEVICE_LIST                *DeviceNode;
  UINTN                              Index;
  EFI_SMM_VARIABLE_PROTOCOL          *SmmVariable;

  List     = NULL;
  ListSize = 0;

  Status = gSmst->SmmLocateProtocol (&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&SmmVariable);
  ASSERT_EFI_ERROR (Status);

  Status = SmmVariable->SmmGetVariable (
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

    Status = SmmVariable->SmmGetVariable (
                    L"HddPassword",
                    &gEfiHddPasswordSecurityVariableGuid,
                    NULL,
                    &ListSize,
                    List
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "GetPasswordHashFromVariable fails with %r\n", Status));
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
  Get attached harddisk identify data.

  @param[in] Bus                 The bus number of ATA controller.
  @param[in] Device              The device number of ATA controller.
  @param[in] Function            The function number of ATA controller.
  @param[in] Port                The port number of attached ATA device.
  @param[in] PortMultiplier      The port number of port multiplier of attached ATA device.
  @param[in] AtaCmd              The ATA cmd to be executed.
  @param[in] Buffer              The data buffer to be read or write.

  @retval EFI_SUCCESS            Successful to execute the ATA cmd.
  @retval EFI_INVALID_PARAMETER  The parameter passed-in is invalid.
  @retval EFI_DEVICE_ERROR       Can not execute the ATA cmd.

**/
EFI_STATUS
AtaCmdDispatcher (
  IN  UINTN                       Bus,
  IN  UINTN                       Device,
  IN  UINTN                       Function,
  IN  UINT16                      Port,
  IN  UINT16                      PortMultiplier,
  IN  UINT8                       AtaCmd,
  IN  VOID                        *Buffer
  )
{
  UINT8                           SubClassCode;
  UINT8                           BaseClassCode;
  EFI_STATUS                      Status;
  EFI_ATA_COMMAND_BLOCK           AtaCommandBlock;
  BOOLEAN                         Read;

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  SubClassCode  = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0A));
  BaseClassCode = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0B));
  if (BaseClassCode != 0x01) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_DEVICE_ERROR;
  if (AtaCmd == ATA_CMD_IDENTIFY_DRIVE) {
    Read = TRUE;
  } else {
    Read = FALSE;
  }

  if (SubClassCode == 0x01) {
    ASSERT (Port < EfiIdeMaxChannel);
    ASSERT (PortMultiplier < EfiIdeMaxDevice);
    Status = GetIdeRegisterIoAddr (Bus, Device, Function, mIdeRegisters);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    AtaCommandBlock.AtaCommand    = AtaCmd;
    AtaCommandBlock.AtaDeviceHead = (UINT8)(PortMultiplier == 0xFFFF ? 0 : (PortMultiplier << 0x4));

    Status = AtaPioDataInOut (
               &mIdeRegisters[Port],
               Buffer,
               HDD_PAYLOAD,
               Read,
               &AtaCommandBlock,
               NULL,
               ATA_TIMEOUT
               );

  } else if ((SubClassCode == 0x06) || (SubClassCode == 0x04)) {
    Status = GetAhciBaseAddress (Bus, Device, Function);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    AtaCommandBlock.AtaCommand     = AtaCmd;

    Status = AhciPioTransfer (
               &mAhciRegisters,
               (UINT8)Port,
               (UINT8)PortMultiplier,
               NULL,
               0,
               Read,
               &AtaCommandBlock,
               NULL,
               Buffer,
               HDD_PAYLOAD,
               ATA_TIMEOUT
               );
  } else {
    ASSERT (FALSE);
  }
  return Status;
}

/**
  Unlock hdd if it's locked.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplier       The port number of port multiplier of attached ATA device.
  @param[in] Identifier           The identifier to set user or master password.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_SUCCESS            The interrupt was handled and quiesced. No other handlers
                                 should still be called.
  @retval Others                 Other execution results.
**/
EFI_STATUS
EFIAPI
UnlockHddPassword (
  IN  UINTN                      Bus,
  IN  UINTN                      Device,
  IN  UINTN                      Function,
  IN  UINT16                     Port,
  IN  UINT16                     PortMultiplier,
  IN  UINT16                     Identifier,
  IN  CHAR8                      *Password
  )
{
  EFI_STATUS                     Status;

  ZeroMem (mBuffer, HDD_PAYLOAD);
  ((CHAR16 *)mBuffer)[0] = Identifier & BIT0;
  CopyMem (&((CHAR16 *)mBuffer)[1], Password, HDD_PASSWORD_MAX_LENGTH);

  Status = AtaCmdDispatcher (Bus, Device, Function, Port, PortMultiplier, ATA_SECURITY_UNLOCK_CMD, mBuffer);
  return Status;
}

/**
  Disable hdd if it's enabled.

  @param[in] Bus                  The bus number of ATA controller.
  @param[in] Device               The device number of ATA controller.
  @param[in] Function             The function number of ATA controller.
  @param[in] Port                 The port number of attached ATA device.
  @param[in] PortMultiplier       The port number of port multiplier of attached ATA device.
  @param[in] Identifier           The identifier to set user or master password.
  @param[in] Password             The hdd password of attached ATA device.

  @retval EFI_SUCCESS            The interrupt was handled and quiesced. No other handlers
                                 should still be called.
  @retval Others                 Other execution results.
**/
EFI_STATUS
EFIAPI
DisableHddPassword (
  IN  UINTN                      Bus,
  IN  UINTN                      Device,
  IN  UINTN                      Function,
  IN  UINT16                     Port,
  IN  UINT16                     PortMultiplier,
  IN  UINT16                     Identifier,
  IN  CHAR8                      *Password
  )
{
  EFI_STATUS                     Status;

  ZeroMem (mBuffer, HDD_PAYLOAD);
  ((CHAR16 *)mBuffer)[0] = Identifier & BIT0;
  CopyMem (&((CHAR16 *)mBuffer)[1], Password, HDD_PASSWORD_MAX_LENGTH);

  Status = AtaCmdDispatcher (Bus, Device, Function, Port, PortMultiplier, ATA_SECURITY_DIS_PASSWORD_CMD, mBuffer);
  return Status;
}

/**
  Set hdd password if it's enabled.

  @param[in] Bus                       The bus number of ATA controller.
  @param[in] Device                    The device number of ATA controller.
  @param[in] Function                  The function number of ATA controller.
  @param[in] Port                      The port number of attached ATA device.
  @param[in] PortMultiplier            The port number of port multiplier of attached ATA device.
  @param[in] Identifier                The identifier to set user or master password.
  @param[in] SecurityLevel             The security level to be set to device.
  @param[in] MasterPasswordIdentifier  The master password identifier to be set to device.
  @param[in] Password                  The hdd password of attached ATA device.

  @retval EFI_SUCCESS            The interrupt was handled and quiesced. No other handlers
                                 should still be called.
  @retval Others                 Other execution results.
**/
EFI_STATUS
EFIAPI
SetHddPassword (
  IN  UINTN                      Bus,
  IN  UINTN                      Device,
  IN  UINTN                      Function,
  IN  UINT16                     Port,
  IN  UINT16                     PortMultiplier,
  IN  UINT8                      Identifier,
  IN  UINT8                      SecurityLevel,
  IN  UINT16                     MasterPasswordIdentifier,
  IN  CHAR8                      *Password
  )
{
  EFI_STATUS                     Status;

  ZeroMem (mBuffer, HDD_PAYLOAD);
  ((CHAR16 *)mBuffer)[0] = (Identifier | (UINT16)(SecurityLevel << 8)) & (BIT0 | BIT8);
  CopyMem (&((CHAR16 *)mBuffer)[1], Password, HDD_PASSWORD_MAX_LENGTH);
  if ((Identifier & BIT0) != 0) {
    ((CHAR16 *)mBuffer)[17] = MasterPasswordIdentifier;
  }

  Status = AtaCmdDispatcher (Bus, Device, Function, Port, PortMultiplier, ATA_SECURITY_SET_PASSWORD_CMD, mBuffer);
  return Status;
}


/**
  Dispatch function for a Software SMI handler.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     RegisterContext Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in, out] CommBuffer     A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize The size of the CommBuffer.

  @retval EFI_SUCCESS            The interrupt was handled and quiesced. No other handlers
                                 should still be called.
  @retval Others                 Other execution results.
**/
EFI_STATUS
EFIAPI
SmmUnlockHddPassword (
  IN     EFI_HANDLE              DispatchHandle,
  IN     CONST VOID              *RegisterContext,
  IN OUT VOID                    *CommBuffer,
  IN OUT UINTN                   *CommBufferSize
  )
{
  EFI_HDD_DEVICE_LIST            *DeviceNode;
  UINTN                          Bus;
  UINTN                          Device;
  UINTN                          Function;
  UINT16                         Port;
  UINT16                         PortMultiplierPort;
  EFI_STATUS                     Status;
  HDD_DEVICE_LIST                *List;
  LIST_ENTRY                     *Entry;
  UINT8                          SubClassCode;
  UINT8                          BaseClassCode;

  //
  // try to unlock all locked hdd disks.
  //
  EFI_LIST_FOR_EACH (Entry, &mDeviceList) {
    List       = BASE_CR (Entry, HDD_DEVICE_LIST, Link);
    DeviceNode = &List->DeviceList;
    Bus        = DeviceNode->Bus;
    Device     = DeviceNode->Device;
    Function   = DeviceNode->Function;
    Port       = DeviceNode->Port;
    PortMultiplierPort = DeviceNode->PortMultiplierPort;

    ASSERT (mBuffer != NULL);
    if (mBuffer == NULL) {
      return EFI_DEVICE_ERROR;
    }
    ZeroMem (mBuffer, 512);

    SubClassCode  = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0A));
    BaseClassCode = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0B));
    if (BaseClassCode != 0x01) {
      return EFI_INVALID_PARAMETER;
    }

    if ((SubClassCode == 0x06) || (SubClassCode == 0x04)) {
      PciWrite16 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x04), 0x7);
      Status = AhciModeInitialize ((UINT8)Port);
      ASSERT_EFI_ERROR (Status);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    } else if (SubClassCode == 0x01) {
      PciWrite16 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x04), 0x5);
    } else {
      ASSERT (FALSE);
    }

    Status = AtaCmdDispatcher (Bus, Device, Function, Port, PortMultiplierPort, ATA_CMD_IDENTIFY_DRIVE, mBuffer);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = UnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, 0, (CHAR8 *)DeviceNode->Password);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
  Communication service SMI Handler entry.

  This SMI handler provides services for saving HDD password and saving S3 boot script when ready to boot.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     RegisterContext Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in, out] CommBuffer     A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize The size of the CommBuffer.

  @retval EFI_SUCCESS                         The interrupt was handled and quiesced. No other handlers
                                              should still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_QUIESCED  The interrupt has been quiesced but other handlers should
                                              still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_PENDING   The interrupt is still pending and other handlers should still
                                              be called.
  @retval EFI_INTERRUPT_PENDING               The interrupt could not be quiesced.
**/
EFI_STATUS
EFIAPI
SmmHddPasswordHandler (
  IN     EFI_HANDLE                 DispatchHandle,
  IN     CONST VOID                 *RegisterContext,
  IN OUT VOID                       *CommBuffer,
  IN OUT UINTN                      *CommBufferSize
  )
{
  EFI_STATUS                        Status;
  SMM_COMMUNICATE_HEADER            *SmmFunctionHeader;
  UINTN                             CommBufferPayloadSize;
  UINTN                             TempCommBufferSize;
  UINTN                             Bus;
  UINTN                             Device;
  UINTN                             Function;
  UINT16                            Port;
  UINT16                            PortMultiplierPort;
  UINT8                             NewPassword[HDD_PASSWORD_MAX_LENGTH];
  UINT8                             OldPassword[HDD_PASSWORD_MAX_LENGTH];
  UINT16                            Identifier;
  UINT16                            MasterPasswordIdentifier;
  UINT32                            *Other;
  UINT8                             HashData[SHA256_DIGEST_SIZE];
  UINT8                             SavedHashData[SHA256_DIGEST_SIZE];
  UINT8                             SavedSaltData[PASSWORD_SALT_SIZE];
  BOOLEAN                           HashOk;
  BOOLEAN                           OldPwdExist;

  //
  // If input is invalid, stop processing this SMI
  //
  if (CommBuffer == NULL || CommBufferSize == NULL) {
    return EFI_SUCCESS;
  }

  TempCommBufferSize = *CommBufferSize;

  if (TempCommBufferSize < OFFSET_OF (SMM_COMMUNICATE_HEADER, Data)) {
    DEBUG ((EFI_D_ERROR, "SmmVariableHandler: SMM communication buffer size invalid!\n"));
    return EFI_SUCCESS;
  }

  CommBufferPayloadSize = TempCommBufferSize - OFFSET_OF (SMM_COMMUNICATE_HEADER, Data);

  if (CommBufferPayloadSize < sizeof (EFI_HDD_DEVICE_LIST)) {
    DEBUG ((EFI_D_ERROR, "SmmVariableHandler: SMM communication buffer payload size invalid!\n"));
    return EFI_SUCCESS;
  }
  //
  // The implementation of function InternalAsmLfence() is the same with BaseLib
  // API AsmLfence() on the Edk2 master branch. Here, this internal implementation
  // is introduced to keep the compatibility with Edk2 UDK branches.
  //
  // The InternalAsmLfence() call here is to ensure the above range checks for
  // the CommBuffer have been completed before calling into functions like
  // SetHddPassword().
  //
  InternalAsmLfence ();

  Status   = EFI_SUCCESS;
  SmmFunctionHeader = (SMM_COMMUNICATE_HEADER *)CommBuffer;

  Bus      = ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->Bus;
  Device   = ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->Device;
  Function = ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->Function;
  Port     = ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->Port;
  PortMultiplierPort = ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->PortMultiplierPort;
  CopyMem (NewPassword, ((EFI_HDD_DEVICE_LIST*)(SmmFunctionHeader->Data))->Password, sizeof (NewPassword));
  switch (SmmFunctionHeader->Function) {
    case SMM_FUNCTION_SET_HDD_PASSWORD:
      if (CommBufferPayloadSize != (sizeof (EFI_HDD_DEVICE_LIST) + sizeof (UINT32) + HDD_PASSWORD_MAX_LENGTH)) {
        Status = EFI_INVALID_PARAMETER;
        goto EXIT;
      }
      Other      = (UINT32 *)((EFI_HDD_DEVICE_LIST *)(SmmFunctionHeader->Data) + 1);
      Identifier = *((UINT16 *)Other);
      CopyMem (OldPassword, (Other + 1), sizeof (OldPassword));
      MasterPasswordIdentifier = *((UINT16 *)Other + 1);
      if (PasswordIsFullZero (NewPassword) && PasswordIsFullZero (OldPassword)) {
        Status = EFI_INVALID_PARAMETER;
        goto EXIT;
      }

      //
      // OldPassword is full zero and identifier show usr is requesting to set master password.
      //
      if (PasswordIsFullZero (OldPassword) && ((Identifier & BIT0) == BIT0)) {
        Status = SetHddPassword (Bus, Device, Function, Port, PortMultiplierPort, (UINT8)Identifier, (UINT8)(Identifier >> 8), MasterPasswordIdentifier, (CHAR8 *)NewPassword);
        goto EXIT;
      }

      //
      // OldPassword is not full zero, it means executing SECURITY_DISABLE_PASSWORD command.
      //
      if (!PasswordIsFullZero (OldPassword)) {
        Status = DisableHddPassword (Bus, Device, Function, Port, PortMultiplierPort, Identifier, (CHAR8 *)OldPassword);
        if (EFI_ERROR (Status)) {
          goto EXIT;
        }
      }

      //
      // NewPassword is not full zero, it means executing SECURITY_SET_PASSWORD command.
      //
      if (!PasswordIsFullZero (NewPassword)) {
        //
        // Get old password hash data first to prepare restore it if SECURITY_SET_PASSWORD fails due to hostile attack.
        //
        Status = GetPasswordHashFromVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
        if (!EFI_ERROR (Status)) {
          OldPwdExist = TRUE;
        } else {
          OldPwdExist = FALSE;
        }
        Status = SavePasswordToVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
        if (!EFI_ERROR (Status)) {
          Status = SetHddPassword (Bus, Device, Function, Port, PortMultiplierPort, (UINT8)Identifier, (UINT8)(Identifier >> 8), MasterPasswordIdentifier, (CHAR8 *)NewPassword);
          if (!EFI_ERROR (Status)) {
            Status = SavePasswordToSmm (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
            if (EFI_ERROR (Status)) {
              goto EXIT;
            }
          } else {
            //
            // Restore to old password hash data. If old password hash data doesn't exist, clean it to all zero.
            //
            if (OldPwdExist) {
              SavePasswordHashToVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
            } else {
              SavePasswordToVariable (Bus, Device, Function, Port, PortMultiplierPort, NULL);
            }
          }
        }
      }
      break;

    case SMM_FUNCTION_UNLOCK_HDD_PASSWORD:
      //
      // The common buffer is comprised of two parts:
      // a) a EFI_HDD_DEVICE_LIST
      // b) a UINT16 data which is used to specify identifier.
      //
      if (CommBufferPayloadSize != (sizeof (EFI_HDD_DEVICE_LIST) + sizeof (UINT16))) {
        Status = EFI_INVALID_PARAMETER;
        goto EXIT;
      }

      Identifier = *(UINT16 *)((EFI_HDD_DEVICE_LIST *)(SmmFunctionHeader->Data) + 1);

      //
      // If the password payload is full zero, it means retry unlocking specified HDD.
      // This case is usually seen after loading 3rd oprom which may lock unlocked HDD again.
      //
      if (PasswordIsFullZero (NewPassword)) {
        Status = GetPasswordFromSmm (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
        if (!EFI_ERROR (Status)) {
          Status = UnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, Identifier, (CHAR8 *)NewPassword);
        }
        goto EXIT;
      }
      //
      // Get old password hash data first to prepare restore it if SECURITY_SET_PASSWORD fails due to hostile attack.
      //
      Status = GetPasswordHashFromVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
      if (!EFI_ERROR (Status)) {
        OldPwdExist = TRUE;
      } else {
        OldPwdExist = FALSE;
      }
      //
      // Save new password to flash at first then try to unlock the HDD.
      // It's used to avoid flash variable region out-of-resource attack.
      //
      Status = SavePasswordToVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
      if (!EFI_ERROR (Status)) {
        Status = UnlockHddPassword (Bus, Device, Function, Port, PortMultiplierPort, Identifier, (CHAR8 *)NewPassword);
        if (!EFI_ERROR (Status)) {
          Status = SavePasswordToSmm (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
          if (EFI_ERROR (Status)) {
            goto EXIT;
          }
        } else {
          //
          // Unlock operation fails. For such case we would restore the old password hash data at first.
          //
          if (OldPwdExist) {
            Status = SavePasswordHashToVariable (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)SavedHashData, (CHAR8 *)SavedSaltData);
            if (EFI_ERROR (Status)) {
              goto EXIT;
            }
          } else {
            SavePasswordToVariable (Bus, Device, Function, Port, PortMultiplierPort, NULL);
            goto EXIT;
          }
          //
          // Continue to compare with old password hash data to see if it's matched.
          // It's specific for frozen case. In this case, unlock cmd would fail. we would construct a soft verification process
          // by this.
          //
          HashOk = GenerateCredential ((UINT8 *)NewPassword, SavedSaltData, HashData);
          if (!HashOk) {
            Status = EFI_DEVICE_ERROR;
            goto EXIT;
          }
          if (CompareMem (SavedHashData, HashData, SHA256_DIGEST_SIZE) == 0) {
            //
            // If comes here, it means the HDD is in frozen state.
            // For such case, we have to compare input password with the one in flash.
            //
            Status = GetPasswordFromSmm (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
            if (Status == EFI_NOT_FOUND) {
              Status = SavePasswordToSmm (Bus, Device, Function, Port, PortMultiplierPort, (CHAR8 *)NewPassword);
              if (EFI_ERROR (Status)) {
                goto EXIT;
              }
            }
          } else {
            Status = EFI_DEVICE_ERROR;
            goto EXIT;
          }
        }
      }
      break;

    default:
      Status = EFI_UNSUPPORTED;
      break;
  }

EXIT:
  SmmFunctionHeader->ReturnStatus = Status;

  return EFI_SUCCESS;
}

/**
  Main entry point for an SMM handler dispatch or communicate-based callback.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     Context         Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in,out] CommBuffer      A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in,out] CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS                         The interrupt was handled and quiesced. No other handlers
                                              should still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_QUIESCED  The interrupt has been quiesced but other handlers should
                                              still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_PENDING   The interrupt is still pending and other handlers should still
                                              be called.
  @retval EFI_INTERRUPT_PENDING               The interrupt could not be quiesced.
**/
EFI_STATUS
EFIAPI
S3SleepEntryCallBack (
  IN           EFI_HANDLE           DispatchHandle,
  IN     CONST VOID                 *Context         OPTIONAL,
  IN OUT       VOID                 *CommBuffer      OPTIONAL,
  IN OUT       UINTN                *CommBufferSize  OPTIONAL
  )
{
  UINTN                             Bus;
  UINTN                             Device;
  UINTN                             Function;
  UINTN                             Index;
  EFI_STATUS                        Status;
  LIST_ENTRY                        *Entry;
  UINTN                             Offset;
  UINT64                            Address;
  S3_BOOT_SCRIPT_LIB_WIDTH          Width;
  UINT32                            Data;
  HDD_DEVICE_LIST                   *List;
  EFI_HDD_DEVICE_LIST               *DeviceNode;

  Data     = 0;
  Status   = EFI_SUCCESS;

  EFI_LIST_FOR_EACH (Entry, &mDeviceList) {
    List       = BASE_CR (Entry, HDD_DEVICE_LIST, Link);
    DeviceNode = &List->DeviceList;
    Bus        = DeviceNode->Bus;
    Device     = DeviceNode->Device;
    Function   = DeviceNode->Function;

    //
    // Save register data for SataController Pci Configuration Registers.
    //
    for (Index = 0; Index < (sizeof (mHddHcRegisterSaveTemplate) / sizeof (HDD_HC_PCI_REGISTER_SAVE)); Index += 1) {
      Offset  = mHddHcRegisterSaveTemplate[Index].Address;
      Width   = mHddHcRegisterSaveTemplate[Index].Width;
      switch (Width) {
        case S3BootScriptWidthUint8:
          Data = (UINT32)PciRead8 (PCI_LIB_ADDRESS(Bus,Device,Function,Offset));
          break;
        case S3BootScriptWidthUint16:
          Data = (UINT32)PciRead16 (PCI_LIB_ADDRESS(Bus,Device,Function,Offset));
          break;
        case S3BootScriptWidthUint32:
          Data = PciRead32 (PCI_LIB_ADDRESS(Bus,Device,Function,Offset));
          break;
        default:
          ASSERT (FALSE);
          break;
      }
      Address = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS (Bus, Device, Function, Offset);
      Status  = S3BootScriptSavePciCfgWrite (Width, Address, 1, &Data);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  if (!IsListEmpty (&mDeviceList)) {
    Status = S3BootScriptSaveIoWrite (S3BootScriptWidthUint8, 0xB2, 1, &mSwSmiValue);
    ASSERT_EFI_ERROR (Status);
  }

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
HddPasswordSmmInit (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL         *SwDispatch;
  EFI_SMM_SX_DISPATCH2_PROTOCOL         *SxDispatch;
  EFI_HANDLE                            SwHandle;
  EFI_SMM_SW_REGISTER_CONTEXT           Context;
  EFI_HANDLE                            SmmHandle;
  EFI_HANDLE                            S3SleepEntryHandle;
  EFI_SMM_SX_REGISTER_CONTEXT           EntryRegisterContext;
  EDKII_VARIABLE_LOCK_PROTOCOL          *VariableLock;
  EFI_PHYSICAL_ADDRESS                  Address;

  mBuffer            = NULL;
  SwHandle           = NULL;
  SmmHandle          = NULL;
  S3SleepEntryHandle = NULL;

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSwDispatch2ProtocolGuid,
                    NULL,
                    (VOID **)&SwDispatch
                    );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSxDispatch2ProtocolGuid,
                    NULL,
                    (VOID **)&SxDispatch
                    );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Preallocate a 512 bytes buffer to store Identify/Unlock cmd payload.
  // It's because DMA can not access smmram stack at the cmd execution.
  //
  Address = 0xFFFFFFFF;
  Status = gBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiACPIMemoryNVS,
                  EFI_SIZE_TO_PAGES(HDD_PAYLOAD),
                  &Address
                  );
  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  mBuffer = (VOID *)(UINTN) Address;
  ZeroMem ((VOID *)(UINTN)mBuffer, HDD_PAYLOAD);
  ZeroMem (mIdeRegisters, sizeof (mIdeRegisters));

  //
  // Preallocate resource for AHCI transfer descriptor.
  //
  Status = AhciAllocateResource ();
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto EXIT;
  }

  //
  // Make "HddPassword" varible read-only for DXE driver for security concern.
  //
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, L"HddPassword", &gEfiHddPasswordSecurityVariableGuid);
    DEBUG ((EFI_D_INFO, "HddPasswordSmm: Lock HddPassword variable for security concern\n"));
    ASSERT_EFI_ERROR (Status);
  }

  //
  // Register a S3 entry callback function to store ATA host controller context to boot script.
  // These boot scripts would be invoked at S3 path to recovery ATA host controller h/w context
  // for executing HDD unlock cmd.
  //
  EntryRegisterContext.Type  = SxS3;
  EntryRegisterContext.Phase = SxEntry;
  Status = SxDispatch->Register (
                         SxDispatch,
                         S3SleepEntryCallBack,
                         &EntryRegisterContext,
                         &S3SleepEntryHandle
                         );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  SmmHandle = NULL;
  Status    = gSmst->SmiHandlerRegister (SmmHddPasswordHandler, &gEfiHddPasswordNotifyProtocolGuid, &SmmHandle);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto EXIT;
  }

  //
  // Register Hdd password smm unlock handler
  //
  Context.SwSmiInputValue = (UINTN) -1;
  Status = SwDispatch->Register (
               SwDispatch,
               SmmUnlockHddPassword,
               &Context,
               &SwHandle
               );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    goto EXIT;
  }

  //
  // trigger smi to unlock hdd if it's locked.
  //
  mSwSmiValue = (UINT8) Context.SwSmiInputValue;

  return EFI_SUCCESS;

EXIT:
  if (SmmHandle != NULL) {
    gSmst->SmiHandlerUnRegister (SmmHandle);
  }

  if (S3SleepEntryHandle != NULL) {
    SxDispatch->UnRegister (SxDispatch, S3SleepEntryHandle);
  }

  AhciFreeResource ();

  if (mBuffer != NULL) {
    gBS->FreePages ((EFI_PHYSICAL_ADDRESS)(UINTN)mBuffer, EFI_SIZE_TO_PAGES(HDD_PAYLOAD));
  }

  return Status;
}

