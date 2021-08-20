/** @file
  Locate an ACPI device path node at the end of a device path

  Various drivers and applications use this API to locate the
  device that they are interested in manipulating.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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

#include <Library/I2cDriverLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>



/**
  Converts integer representation of a EisaID to string.
  Output string will be null-terminated and no longer than 8 bytes

  @param [in] EisaId                    Converts integer representation of a EisaID
                                        value in the ACPI_HID_DEVICE_PATH
                                        node.  This value is ignored when
                                        IdString is neither NULL nor zero-length
  @param [in] Text                      String representation of EisaID, null-terminated,
                                        not longer than 8 bytes

**/
VOID
TextFromEisaId (
  IN UINT32 EisaId,
  OUT CHAR8 *Text
  )
{
  CONST CHAR8 Hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

  Text[0] = 'A' - 1 + ((EisaId >> 10) & 0x1f);
  Text[1] = 'A' - 1 + ((EisaId >> 5) & 0x1f);
  Text[2] = 'A' - 1 + ((EisaId >> 0) & 0x1f);
  Text[3] = Hex[(EisaId >> 28) & 0xF];
  Text[4] = Hex[(EisaId >> 24) & 0xF];
  Text[5] = Hex[(EisaId >> 20) & 0xF];
  Text[6] = Hex[(EisaId >> 16) & 0xF];
  Text[7] = 0;
}

/**
  Locate a matching ACPI device path node

  This routine walks the device path attached to the ControllerHandle
  and determines if the last (non-end) device path node matches the ID
  passed to this function.
  Function will run comparison with both HID and CID. Single match is enough
  to report success.
  String IDs will be used instead of integer representation. If string 
  is invalid (null pointer, 0-length or not provided in device path), integer
  representation will be unpacked to string.

  @param [in] Id                        The value to match against the CID/HID
                                        value in the ACPI_HID_DEVICE_PATH
                                        node.  This value is ignored when
                                        IdString is neither NULL nor zero-length
  @param [in] IdString                  The value to match against the CID/HID
                                        value in the ACPI_HID_DEVICE_PATH
                                        node.

  @return                               TRUE when either HID or CID matches, else FALSE

**/

BOOLEAN
EFIAPI
DlIsMatchingHidCid (
  EFI_HANDLE ControllerHandle,
  UINT32 Id,
  CONST CHAR8 * IdString OPTIONAL
  )
{
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL *EndPath;
  CHAR8 DeviceHidString [9];
  CHAR8 DeviceCidString [9];
  CHAR8 InputIdString [9];
  CHAR8 *String;
  UINTN Length;

  ZeroMem(DeviceHidString, sizeof(DeviceHidString));
  ZeroMem(DeviceCidString, sizeof(DeviceCidString));
  ZeroMem(InputIdString, sizeof(InputIdString));
  //
  //  Locate the last node in the device path
  //
  EndPath = NULL;
  DevicePath = DevicePathFromHandle ( ControllerHandle );
  if ( NULL == DevicePath ) {
    DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - No device path for this controller!\r\n" ));
    return FALSE;
  }

  EndPath = DevicePath;
  while ( !IsDevicePathEnd ( EndPath )) {
    //
    //  Skip this portion of the device path
    //
    DevicePath = EndPath;
    if ( sizeof ( *DevicePath ) > DevicePathNodeLength ( EndPath )) {
      //
      //  Invalid device path node
      //
      DEBUG (( DEBUG_ERROR,
                "DlIsMatchingHidCid - Invalid device path found at 0x%016Lx\r\n",
                (UINT64)(UINTN) EndPath ));
      return FALSE;
    }
    EndPath = NextDevicePathNode ( EndPath );
  }

  //
  // Prepare String representation of input ID
  //
  if (IdString != NULL) {
    CopyMem(InputIdString, IdString, 8);
    InputIdString[8] = 0;
  }
  if (AsciiStrLen(InputIdString) == 0) {
    TextFromEisaId(Id, InputIdString);
  }

  //
  //  Prepare String representation of devicepath's HID and CID
  //
  if ( ACPI_DEVICE_PATH != DevicePathType ( DevicePath )) {
      DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - Not an ACPI device path node!\r\n" ));
      return FALSE;
  }

  if (DevicePathSubType ( DevicePath ) == ACPI_DP) {
    TextFromEisaId(((ACPI_HID_DEVICE_PATH*)DevicePath)->HID , DeviceHidString);
  } else if (DevicePathSubType ( DevicePath ) == ACPI_EXTENDED_DP) {
    String = (CHAR8*)( (ACPI_EXTENDED_HID_DEVICE_PATH*)DevicePath + 1 ); //String now points to HidString
    Length = AsciiStrLen(String);
    if (Length > 8) {
      return FALSE;
    }
    if (Length != 0) {
      CopyMem(DeviceHidString, String, Length+1);
    } else {
      TextFromEisaId(((ACPI_EXTENDED_HID_DEVICE_PATH*)DevicePath)->HID , DeviceHidString);
    }
    String = String + Length + 1; //String now points to UidString
    Length = AsciiStrLen(String);
    if (Length > 8) {
      return FALSE;
    }
    String = String + Length + 1; //String now points to CidString
    Length = AsciiStrLen(String);
    if (Length > 8) {
      return FALSE;
    }
    if (Length != 0) {
      CopyMem(DeviceCidString, String, Length+1);
    } else {
      TextFromEisaId(((ACPI_EXTENDED_HID_DEVICE_PATH*)DevicePath)->CID , DeviceCidString);
    }
  } else {
    DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - wrong ACPI device path subtype!\n" ));
    return FALSE;
  }
  
  DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid %a : %a %a\n",InputIdString, DeviceHidString, DeviceCidString ));

  if (!AsciiStrCmp ( InputIdString, DeviceHidString)) {
    DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - yes, HID\n" ));
    return TRUE;
  } else if (!AsciiStrCmp ( InputIdString, DeviceCidString) ) {
    DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - yes, CID\n" ));
    return TRUE;
  } else {
    DEBUG (( DEBUG_INFO, "DlIsMatchingHidCid - No\n" ));
    return FALSE;
  }
}

