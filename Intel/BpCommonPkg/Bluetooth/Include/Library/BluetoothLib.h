//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The public header file of BluetoothLib.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __BLUETOOTH_LIB_H__
#define __BLUETOOTH_LIB_H__

#include <Uefi.h>
#include <Protocol/BluetoothAttribute.h>

typedef enum {
  EfiBluetoothAttributeWriteRequest = 0x1,
  EfiBluetoothAttributeWriteCommand,
  EfiBluetoothAttributeSignedWrite,
  EfiBluetoothAttributeReliableWrite,
} EFI_BLUETOOTH_ATTRIBUTE_WRITE_TYPE;

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
  );

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
  );

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
  );

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
  );

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
  );

/**
  Finds a specific type of Generic Access Profile data from the advertisement
  data.

  @param[in]      AdvertisementData         Advertisement Data Buffer.
  @param[in]      AdvertisementDataSize     Length of buffer provided.
  @param[in]      Type                      Type of data field that is needed.
  @param[out]     OutLen                    Length of valid data in the output.

  @retval         Other       Null in case it fails and pointer to location of data in case of success.
**/
UINT8*
EFIAPI
BluetoothFindTypeFromAdvData (
  IN UINT8                                 *AdvertisementData,
  IN UINTN                                 AdvertisementDataSize,
  IN UINT8                                 Type,
  OUT UINT8                                *OutLen
  );

#endif

