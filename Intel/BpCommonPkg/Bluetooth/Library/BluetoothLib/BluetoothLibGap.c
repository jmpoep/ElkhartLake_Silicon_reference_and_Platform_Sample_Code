//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The helper functions are used Generic Attributes Profile.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <Library/BluetoothLib.h>

#pragma pack(1)
typedef struct {
  UINT8 Length;
  UINT8 Type;
} BLUETOOTH_ADVERTISING_DATA_HEAD;
#pragma pack()
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
  )
{
  BLUETOOTH_ADVERTISING_DATA_HEAD          *Head;
  UINTN                                    Offset;

  if (AdvertisementDataSize < sizeof (BLUETOOTH_ADVERTISING_DATA_HEAD)) {
    return NULL;
  }

  Offset = 0;
  Head   = (BLUETOOTH_ADVERTISING_DATA_HEAD *)AdvertisementData;
  while (Offset <= AdvertisementDataSize - sizeof (BLUETOOTH_ADVERTISING_DATA_HEAD)) {
    Head   = (BLUETOOTH_ADVERTISING_DATA_HEAD *)&AdvertisementData[Offset];
    if (Head->Length == 0) {
      *OutLen = 0;
      return NULL;
    }

    if ((UINTN)Head->Length + 1 > MAX_UINTN - Offset) {
      *OutLen = 0;
      return NULL;
    }
    Offset += Head->Length + 1;
    if (Head->Type == Type) {
      break;
    }
  }

  if ((Offset > AdvertisementDataSize) || (Head->Type != Type)) {
    *OutLen = 0;
    return NULL;
  }

  *OutLen = Head->Length - 1;
  return (UINT8 *)(Head + 1);
}
