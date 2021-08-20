/** @file
  Parse the INI configuration file and pass the information to the update driver
  so that the driver can perform update accordingly.

  Refer to BiosUpdateHelpersLib.h for more infomation about the structure of
  configuration file.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/BiosUpdateHelpersLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IniParsingLib.h>
#include <Library/PrintLib.h>

#define MAX_LINE_LENGTH           512

/**
  Parse Config data file to get the updated data array.

  @param[in]      DataBuffer      Config raw file buffer.
  @param[in]      BufferSize      Size of raw buffer.
  @param[in, out] ConfigHeader    Pointer to the config header.
  @param[in, out] UpdateArray     Pointer to the config of update data.

  @retval EFI_NOT_FOUND         No config data is found.
  @retval EFI_OUT_OF_RESOURCES  No enough memory is allocated.
  @retval EFI_SUCCESS           Parse the config file successfully.

**/
EFI_STATUS
ParseUpdateDataFile (
  IN      UINT8                         *DataBuffer,
  IN      UINTN                         BufferSize,
  IN OUT  CONFIG_HEADER                 *ConfigHeader,
  IN OUT  UPDATE_CONFIG_DATA            **UpdateArray
  )
{
  EFI_STATUS                            Status;
  CHAR8                                 *SectionName;
  CHAR8                                 Entry[MAX_LINE_LENGTH];
  UINTN                                 Num;
  UINT64                                Num64;
  UINTN                                 Index;
  EFI_GUID                              FileGuid;
  VOID                                  *Context;
  BOOLEAN                               SupportHelperImage;

  //
  // First process the data buffer and get all sections and entries
  //
  Context = OpenIniFile (DataBuffer, BufferSize);
  if (Context == NULL) {
    DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: Failed to open ini file"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Now get NumOfUpdate
  //
  Status = GetDecimalUintnFromDataFile (
             Context,
             "Head",
             "NumOfUpdate",
             &Num
             );
  if (EFI_ERROR (Status) || (Num == 0)) {
    DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: NumOfUpdate not found\n"));
    CloseIniFile (Context);
    return EFI_NOT_FOUND;
  }

  ConfigHeader->NumOfUpdates = Num;
  *UpdateArray = AllocateZeroPool ((sizeof (UPDATE_CONFIG_DATA) * Num));
  if (*UpdateArray == NULL) {
    CloseIniFile (Context);
    DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: Run out of memory resouce\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // FileGuid
  //
  Status = GetGuidFromDataFile (
             Context,
             "Head",
             "ImageFileGuid",
             &FileGuid
             );
  if (EFI_ERROR (Status)) {
    CloseIniFile (Context);
    DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: ImageFileGuid not found\n"));
    return EFI_NOT_FOUND;
  }

  CopyGuid (&ConfigHeader->FileGuid, &FileGuid);

  //
  // HelperFileGuid
  //
  SupportHelperImage = TRUE;
  Status = GetGuidFromDataFile (
             Context,
             "Head",
             "HelperFileGuid",
             &FileGuid
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "ParseUpdateDataFile: HelperFileGuid is not found\n"));
    SetMem (&FileGuid, sizeof (EFI_GUID), 0);
    SupportHelperImage = FALSE;
  }

  CopyGuid (&ConfigHeader->HelperFileGuid, &FileGuid);

  for (Index = 0 ; Index < ConfigHeader->NumOfUpdates ; Index++) {
    //
    // Get the section name of each update
    //
    AsciiStrCpyS (Entry, MAX_LINE_LENGTH, "Update");
    AsciiValueToStringS (Entry + AsciiStrLen(Entry), MAX_LINE_LENGTH - AsciiStrLen(Entry), 0, Index, 0);
    Status = GetStringFromDataFile (
               Context,
               "Head",
               Entry,
               &SectionName
               );
    if (EFI_ERROR (Status) || (SectionName == NULL)) {
      DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: [%d] %a not found\n", Index, Entry));
      CloseIniFile (Context);
      return EFI_NOT_FOUND;
    }

    //
    // The section name of this update has been found.
    // Now looks for all the config data of this update
    //
    (*UpdateArray)[Index].Index = Index;

    //
    // BaseAddress
    //
    Status = GetHexUint64FromDataFile (
               Context,
               SectionName,
               "BaseAddress",
               &Num64
               );
    if (EFI_ERROR (Status)) {
      CloseIniFile (Context);
      DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: [%d] BaseAddress not found\n", Index));
      return EFI_NOT_FOUND;
    }
    (*UpdateArray)[Index].BaseAddress = (EFI_PHYSICAL_ADDRESS) Num64;

    //
    // Length
    //
    Status = GetHexUintnFromDataFile (
               Context,
               SectionName,
               "Length",
               &Num
               );
    if (EFI_ERROR (Status)) {
      CloseIniFile (Context);
      DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: [%d] Length not found\n", Index));
      return EFI_NOT_FOUND;
    }
    (*UpdateArray)[Index].Length = (UINTN) Num;

    //
    // ImageOffset
    //
    Status = GetHexUintnFromDataFile (
               Context,
               SectionName,
               "ImageOffset",
               &Num
               );
    if (EFI_ERROR (Status)) {
      CloseIniFile (Context);
      DEBUG ((DEBUG_ERROR, "ParseUpdateDataFile: [%d] ImageOffset not found\n", Index));
      return EFI_NOT_FOUND;
    }
    (*UpdateArray)[Index].ImageOffset = (UINTN) Num;

    //
    // HelperImageOffset
    //
    Status = GetHexUintnFromDataFile (
               Context,
               SectionName,
               "HelperOffset",
               &Num
               );
    if (EFI_ERROR (Status) || !SupportHelperImage) {
      Num = 0;
    }

    (*UpdateArray)[Index].HelperImageOffset = (UINTN) Num;

    //
    // HelperImageLength
    //
    Status = GetHexUintnFromDataFile (
               Context,
               SectionName,
               "HelperLength",
               &Num
               );
    if (EFI_ERROR (Status) || !SupportHelperImage) {
      Num = 0;
    }

    (*UpdateArray)[Index].HelperImageLength = (UINTN) Num;

  }

  //
  // Now all configuration data got. Free those temporary buffers
  //
  CloseIniFile (Context);

  return EFI_SUCCESS;
}
