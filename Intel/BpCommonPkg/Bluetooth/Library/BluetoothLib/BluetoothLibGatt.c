//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The help functions which is used to read and parse bluetooth attributes.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <Library/DebugLib.h>
#include <Library/BluetoothLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <IndustryStandard/BluetoothAtt.h>
#include <IndustryStandard/BluetoothAssignedNumbers.h>

/**
  Compares two Bluetooth UUID data.

  @param[in]  Uuid1  A pointer to the EFI_BLUETOOTH_UUID structure.
  @param[in]  Uuid2  A pointer to the EFI_BLUETOOTH_UUID structure.

  @retval  TRUE   Uuid1 and Uuid2 are identical.
  @retval  FALSE  Uuid1 and Uuid2 are not identical.

**/
STATIC
BOOLEAN
UuidCompareInternal(
  IN EFI_BLUETOOTH_UUID *Uuid1,
  IN EFI_BLUETOOTH_UUID *Uuid2
  )
{
  if (Uuid1->Length != Uuid2->Length)
    return FALSE;

  if ((Uuid1->Length == UUID_16BIT_TYPE_LEN) && (Uuid1->Data.Uuid16 == Uuid2->Data.Uuid16))
    return TRUE;

  if ((Uuid1->Length == UUID_32BIT_TYPE_LEN) && (Uuid1->Data.Uuid32 == Uuid2->Data.Uuid32))
    return TRUE;

  if ((Uuid1->Length == UUID_128BIT_TYPE_LEN) && (!CompareMem(Uuid1->Data.Uuid128, Uuid2->Data.Uuid128, UUID_128BIT_TYPE_LEN)))
    return TRUE;

  return FALSE;
}

/**
  Converts a given Bluetooth UUID to 128-bit UUID data.

  If the given UUID is a 128-bit Bluetooth UUID data, the origin UUID will be
  returned. Otherwise, the converted 128-bit UUID data will be returned.

  @param[in, out]  Uuid  On input, a pointer to the EFI_BLUETOOTH_UUID
                         structure that specifies the UUID to convert. On
                         output, the converted 128-bit UUID data.

**/
STATIC
VOID
UuidToUuid128Internal(
  IN OUT EFI_BLUETOOTH_UUID *Uuid
  )
{
  UINT8 BaseUuidArray[16];

  BaseUuidArray[0] = 0x00;
  BaseUuidArray[1] = 0x00;
  BaseUuidArray[2] = 0x00;
  BaseUuidArray[3] = 0x00;
  BaseUuidArray[4] = 0x00;
  BaseUuidArray[5] = 0x00;
  BaseUuidArray[6] = 0x10;
  BaseUuidArray[7] = 0x00;
  BaseUuidArray[8] = 0x80;
  BaseUuidArray[9] = 0x00;
  BaseUuidArray[10] = 0x00;
  BaseUuidArray[11] = 0x80;
  BaseUuidArray[12] = 0x5F;
  BaseUuidArray[13] = 0x9B;
  BaseUuidArray[14] = 0x34;
  BaseUuidArray[15] = 0xFB;

  if (Uuid->Length == UUID_128BIT_TYPE_LEN)
    return;

  if (Uuid->Length == UUID_16BIT_TYPE_LEN)
  {
    BaseUuidArray[2] = (UINT8)((Uuid->Data.Uuid16 & 0xFF00) >> 8);
    BaseUuidArray[3] = (UINT8)((Uuid->Data.Uuid16 & 0x00FF));
  }
  else if(Uuid->Length == UUID_32BIT_TYPE_LEN)
  {
    BaseUuidArray[0] = (UINT8)((Uuid->Data.Uuid32 & 0xFF000000) >> 24);
    BaseUuidArray[1] = (UINT8)((Uuid->Data.Uuid32 & 0x00FF0000) >> 16);
    BaseUuidArray[2] = (UINT8)((Uuid->Data.Uuid32 & 0x0000FF00) >> 8);
    BaseUuidArray[3] = (UINT8)(Uuid->Data.Uuid32 & 0x000000FF);
  }

  Uuid->Length = UUID_128BIT_TYPE_LEN;
  CopyMem(Uuid->Data.Uuid128, BaseUuidArray, UUID_128BIT_TYPE_LEN);
}

/**
  Compares two Bluetooth UUID data.

  If the length of the two UUIDs is different, both UUIDs will be converted to
  128-bit Bluetooth UUID data before comparison.

  @param[in]  Uuid1  A pointer to the EFI_BLUETOOTH_UUID structure.
  @param[in]  Uuid2  A pointer to the EFI_BLUETOOTH_UUID structure.

  @retval  TRUE   Uuid1 and Uuid2 represent the same UUID.
  @retval  FALSE  Uuid1 and Uuid2 represent different UUIDs.

**/
BOOLEAN
EFIAPI
BluetoothUuidCompare (
  IN EFI_BLUETOOTH_UUID *Uuid1,
  IN EFI_BLUETOOTH_UUID *Uuid2
  )
{
  EFI_BLUETOOTH_UUID Uuid1Copy, Uuid2Copy;

  if (Uuid1->Length == Uuid2->Length)
    return UuidCompareInternal(Uuid1, Uuid2);

  CopyMem (&Uuid1Copy, Uuid1, sizeof (EFI_BLUETOOTH_UUID));
  CopyMem (&Uuid2Copy, Uuid2, sizeof (EFI_BLUETOOTH_UUID));
  UuidToUuid128Internal(&Uuid1Copy);
  UuidToUuid128Internal(&Uuid2Copy);
  return UuidCompareInternal((&Uuid1Copy), (&Uuid2Copy));
}

/**
  Checks whether an attribute can be found on a Bluetooth device. The attribute
  is specified by the service type and service UUID.

  @param[in]   This        A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                           instance.
  @param[in]   Type        Type of the Bluetooth service.
  @param[in]   Uuid        The Bluetooth Service Discovery UUID.
  @param[in]   StartHandle The starting identifier for a range of attributes to obtain.
  @param[out]  Attribute   A pointer to the attribute data if the specified
                           attribute is found on the Bluetooth device.

  @retval  EFI_SUCCESS    The specified attribute is found on the Bluetooth
                          device.
  @retval  EFI_NOT_FOUND  The specified attribute is not found on the Bluetooth
                          device.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeSearch (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL            *This,
  IN UINT16                                      Type,
  IN EFI_BLUETOOTH_UUID                          *Uuid,
  IN UINT16                                      StartHandle,
  OUT EFI_BLUETOOTH_ATTRIBUTE_HEADER             *Attribute
  )
{
  EFI_STATUS                                        Status;
  UINT8                                             *ServiceInfo;
  VOID                                              *ServiceInfoCopy;
  UINTN                                             ServiceInfoSize;
  UINT8                                             AttrSize;
  EFI_BLUETOOTH_ATTRIBUTE_HEADER                    *Attr;
  EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO           *ServiceVal;
  EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO           *IncludeVal;
  EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO            *CharVal;
  EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO *DescVal;

  Status = This->GetServiceInfo(This, &ServiceInfoSize, (VOID**) &ServiceInfo);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  ServiceInfoCopy = ServiceInfo;

  while (ServiceInfoSize > 0) {
    Attr = (EFI_BLUETOOTH_ATTRIBUTE_HEADER*) ServiceInfo;
    if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(Attr, BluetoothGattTypePrimaryService)) {
      AttrSize = sizeof(EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO);
      if (Type == BluetoothGattTypePrimaryService) {
        ServiceVal = (EFI_BLUETOOTH_GATT_PRIMARY_SERVICE_INFO *) Attr;
        if ((BluetoothUuidCompare(&ServiceVal->ServiceUuid, Uuid)) && (ServiceVal->Header.AttributeHandle >= StartHandle)) {
          if (Attribute != NULL) {
            CopyMem(Attribute, Attr, AttrSize);
          }
          break;
        }
      }

      ServiceInfo += AttrSize;
      ServiceInfoSize -= AttrSize;
    }
    else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(Attr, BluetoothGattTypeInclude)) {
      AttrSize = sizeof(EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO);
      if (Type == BluetoothGattTypeInclude) {
        IncludeVal = (EFI_BLUETOOTH_GATT_INCLUDE_SERVICE_INFO*) Attr;
        if ((BluetoothUuidCompare(&IncludeVal->ServiceUuid, Uuid)) && (IncludeVal->Header.AttributeHandle >= StartHandle)) {
          if (Attribute != NULL) {
            CopyMem(Attribute, Attr, AttrSize);
          }
          break;
        }
      }
      ServiceInfo += AttrSize;
      ServiceInfoSize -= AttrSize;
    }
    else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(Attr, BluetoothGattTypeCharacteristic)) {
      AttrSize = sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
      if (Type == BluetoothGattTypeCharacteristic) {
        CharVal = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO*) Attr;
        if ((BluetoothUuidCompare(&CharVal->CharacteristicUuid, Uuid)) && (CharVal->Header.AttributeHandle >= StartHandle)) {
          if (Attribute != NULL) {
            CopyMem(Attribute, Attr, AttrSize);
          }
          break;
        }
      }
      ServiceInfo += AttrSize;
      ServiceInfoSize -= AttrSize;
    }
    else if (BLUETOOTH_IS_ATTRIBUTE_OF_TYPE(Attr, BluetoothGattTypeCharacteristicExtendedProperties)) {
      AttrSize = sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO);
      if (Type == BluetoothGattTypeCharacteristicExtendedProperties) {
        DescVal = (EFI_BLUETOOTH_GATT_CHARACTERISTIC_DESCRIPTOR_INFO*) Attr;
        if ((BluetoothUuidCompare(&DescVal->CharacteristicDescriptorUuid, Uuid)) && (DescVal->Header.AttributeHandle >= StartHandle)) {
          if (Attribute != NULL) {
            CopyMem(Attribute, Attr, AttrSize);
          }
          break;
        }
      }
      ServiceInfo += AttrSize;
      ServiceInfoSize -= AttrSize;
    } else {
      /* Characteristic Value */
      AttrSize = sizeof(EFI_BLUETOOTH_GATT_CHARACTERISTIC_INFO);
      ServiceInfo += AttrSize;
      ServiceInfoSize -= AttrSize;
    }
  }

  FreePool(ServiceInfoCopy);

  if (ServiceInfoSize != 0) {
    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

/**
  Submits a request to obtain the value of attributes from a remote server.

  @param[in]  This       A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                         interface.
  @param[in]  Handle     If Uuid is NULL, a 16-bit identifier for the attribute
                         to obtain. Otherwise, the starting identifier for a
                         range of attributes to obtain.
  @param[in]  EndHandle  The 16-bit ending identifier for a range of attributes
                         to obtain.
  @param[in]  Uuid       A UUID to specify the type of the attribute to obtain.
  @param[in]  Callback   The callback function when a response is received from
                         the remote server.
  @param[in]  Context    Data passed into Callback function.

  @retval  EFI_SUCCESS  The request is sent successfully.
  @retval  Other        A error from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeRead (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL            *This,
  IN UINT16                                      Handle,
  IN UINT16                                      EndHandle,
  IN EFI_BLUETOOTH_UUID                          *Uuid,
  IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION   Callback,
  IN VOID                                        *Context
  )
{
  EFI_STATUS  Status;
  UINT16      Length;
  UINT8       *Buffer;

  Length = 0;
  Buffer = NULL;
  Buffer = AllocateZeroPool (sizeof (UINT8) + 2 * sizeof (UINT16) + UUID_128BIT_TYPE_LEN);
  ASSERT (Buffer != NULL);
  if (Uuid != NULL) {
    *(Buffer+Length) = BluetoothAttOpReadByTypeRequest;
    Length++;
    *((UINT16*)(Buffer+Length)) = Handle;
    Length += 2;
    *((UINT16*)(Buffer+Length)) = EndHandle;
    Length += 2;
    if (Uuid->Length == UUID_16BIT_TYPE_LEN) {
      CopyMem ((Buffer + Length), &Uuid->Data.Uuid16, UUID_16BIT_TYPE_LEN);
    }
    if (Uuid->Length == UUID_32BIT_TYPE_LEN) {
      CopyMem ((Buffer + Length), &Uuid->Data.Uuid32, UUID_32BIT_TYPE_LEN);
    }
    if (Uuid->Length == UUID_128BIT_TYPE_LEN) {
      CopyMem ((Buffer + Length), &Uuid->Data.Uuid128, UUID_128BIT_TYPE_LEN);
    }
    Length += Uuid->Length;
  } else {
    *(Buffer+Length) = BluetoothAttOpReadRequest;
    Length++;
    *((UINT16*)(Buffer+Length)) = Handle;
    Length += 2;
  }

  Status = This->SendRequest (This, Buffer, Length, Callback, Context);
  FreePool (Buffer);
  return Status;
}

/**
  Submits a request to obtain the value of attributes using multiple handles.

  @param[in]  This        A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                          instance.
  @param[in]  Handles     A list of 16-bit identifiers for the attributes to
                          obtain.
  @param[in]  NumHandles  The number of handles in the list.
  @param[in]  Callback    The callback function when a response is received
                          from the remote server.
  @param[in]  Context     Data passed into Callback function.

  @retval  EFI_SUCCESS  The request is sent successfully.
  @retval  Other        A error from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeMultiRead (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL            *This,
  IN UINT16                                      *Handles,
  IN UINT8                                       NumHandles,
  IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION   Callback,
  IN VOID                                        *Context
  )
{
  EFI_STATUS  Status;
  UINT16      Length;
  UINT8       *Buffer;

  Length = 0;
  Buffer = NULL;
  Buffer = AllocateZeroPool (sizeof (UINT8) + 10 * sizeof (UINT16));
  ASSERT (Buffer != NULL);

  *(Buffer+Length) = BluetoothAttOpReadMultipleRequest;
  Length++;
  CopyMem ((Buffer+Length), Handles, NumHandles * sizeof (UINT16));
  Length += (NumHandles * sizeof (UINT16));

  Status = This->SendRequest (This, Buffer, Length, Callback, Context);
  FreePool(Buffer);
  return Status;
}

/**
  Submits a request to write the value of an attribute to a remote server.

  @param[in]  This       A pointer to the EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL
                         instance.
  @param[in]  Handle     A 16-bit identifier for the attribute to write.
  @param[in]  WriteType  The type of write operation that will be sent to the
                         server.
  @param[in]  DataSize   The size of Data in bytes, of the data buffer
                         specified by Data.
  @param[in]  Data       A pointer to the buffer of data that will be sent.
  @param[in]  Callback   The callback function when a response is received from
                         the remote server.
  @param[in]  Context    Data passed into Callback function.

  @retval  EFI_SUCCESS  The request is sent successfully.
  @retval  Other        A error from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothAttributeWrite (
  IN EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL                   *This,
  IN UINT16                                             Handle,
  IN EFI_BLUETOOTH_ATTRIBUTE_WRITE_TYPE                 WriteType,
  IN UINT16                                             DataSize,
  IN VOID                                               *Data,
  IN EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION          Callback,
  IN VOID                                               *Context
  )
{
  EFI_STATUS  Status;
  UINT16      Length;
  UINT8       *Buffer;

  Length = 0;
  Buffer = NULL;
  Buffer = AllocateZeroPool (sizeof (UINT8) + sizeof (UINT16) + DataSize);
  ASSERT (Buffer != NULL);

  switch (WriteType) {
    case EfiBluetoothAttributeWriteRequest:
      *(Buffer+Length) = BluetoothAttOpWriteRequest;
      break;
    case EfiBluetoothAttributeWriteCommand:
      *(Buffer+Length) = BluetoothAttOpWriteCommand;
      break;
    case EfiBluetoothAttributeSignedWrite:
      *(Buffer+Length) = BluetoothAttOpSignedWriteCommand;
      break;
    case EfiBluetoothAttributeReliableWrite:
      *(Buffer+Length) = BluetoothAttOpPrepareWriteRequest;
      break;
  }
  Length++;

  *((UINT16*)(Buffer+Length)) = Handle;
  Length += 2;

  CopyMem ((Buffer+Length), Data, DataSize);
  Length += DataSize;

  Status = This->SendRequest (This, Buffer, Length, Callback, Context);
  FreePool (Buffer);
  return Status;
}

