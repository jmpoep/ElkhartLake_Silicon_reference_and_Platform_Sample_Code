/** @file
  Firmware Version Info Interface Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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
#include "SiFviLib.h"

/**
  Create the Reference code version info as per Firmware Version Info (FVI) Interface Spec v0.8
  and add the SMBIOS table using the SMBIOS protocol

  Invoke this routine to add the table entry when all the Fvi data is finalized.

  - @pre
    - EFI_SMBIOS_PROTOCOL in Native mode

  @param[in] Header    The expanded header includes the standard SMBIOS table header, plus the Count
                       of the number of elements in the Data and Strings arrays.
  @param[in] *Data     Pointer to an array of Data blocks.
  @param[in] *Strings  Pointer to an array of Strings. There are FVI_NUMBER_OF_STRINGS * Count strings total.

  @retval EFI_SUCCESS          - if the data is successfully reported.
  @retval EFI_OUT_OF_RESOURCES - if not able to get resources.
  @retval EFI_UNSUPPORTED      - if required DataHub or SMBIOS protocol is not available.
**/
EFI_STATUS
AddFviEntry (
  IN FVI_HEADER  Header,
  IN FVI_DATA    *Data,
  IN FVI_STRINGS *Strings
  )
{
  EFI_STATUS                Status;
  UINTN                     Size;
  CHAR8                     **StringArray;
  UINT8                     StringCount;
  UINT8                     StringNumber;
  UINT8                     *DataPtr;
  UINT8                     *Record;
  UINT8                     i;
  CHAR8                     *StringPtr;
  EFI_SMBIOS_HANDLE         SmbiosHandle;
  EFI_SMBIOS_PROTOCOL       *Smbios;

  Status = EFI_SUCCESS;

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&Smbios);
  if (Smbios == NULL) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Create full SMBIOS record
  /// Adjust size to include variable length strings,
  /// and set string numbers to point to the correct string.
  ///
  Size = Header.SmbiosHeader.Length;
  StringArray = (CHAR8 **) Strings;
  StringCount = 0;                   ///< Number of non-null strings total.
  StringNumber = 0;                  ///< String number of the current string.
  DataPtr = (UINT8 *) Data;          ///< Points to the fixed data location for the current string.

  for (i = 0; (i < (Header.Count * FVI_NUMBER_OF_STRINGS)); i++) {
    if (StringArray[i] != NULL) {
      Size += AsciiStrSize (StringArray[i]);
      StringCount++;
      StringNumber = StringCount;
    } else {
      StringNumber = NO_STRING_AVAILABLE;
    }
    *DataPtr = StringNumber;
    DataPtr++;
    ///
    /// If this was the last string of this data block, adjust the DataPtr
    /// to the start of the string section of the next data block.
    ///
    if (((i+1) % FVI_NUMBER_OF_STRINGS) == 0) {
      DataPtr += (sizeof (FVI_DATA) - FVI_NUMBER_OF_STRINGS);
    }
  }

  ///
  /// Add the size of the terminating double null
  /// If there were any strings added, just add the second null
  ///
  if (Size == Header.SmbiosHeader.Length) {
    Size += 2;
  } else {
    Size += 1;
  }

  ///
  /// Initialize the full record
  ///
  Record = (UINT8 *) AllocateZeroPool (Size);
  if (Record == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (Record, &Header, sizeof (FVI_HEADER));
  CopyMem ((Record + sizeof (FVI_HEADER)), Data, (sizeof (FVI_DATA) * Header.Count));

  ///
  /// Copy the strings to the end of the record
  ///
  StringPtr = ((CHAR8 *) Record) + Header.SmbiosHeader.Length;
  for (i = 0; (i < (Header.Count * FVI_NUMBER_OF_STRINGS)); i++) {
    if (StringArray[i] != NULL) {
      AsciiStrCpyS (StringPtr, Size - Header.SmbiosHeader.Length, StringArray[i]);
      StringPtr += AsciiStrSize (StringArray[i]);
      Size -= AsciiStrSize (StringArray[i]);
    }
  }

  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  Status = Smbios->Add (Smbios, NULL, &SmbiosHandle, (EFI_SMBIOS_TABLE_HEADER *) Record);

  FreePool (Record);
  return Status;
}
