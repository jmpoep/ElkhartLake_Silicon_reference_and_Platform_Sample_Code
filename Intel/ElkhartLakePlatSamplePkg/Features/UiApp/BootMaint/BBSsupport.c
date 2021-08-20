/** @file
  This function deal with the legacy boot option, it create, delete
  and manage the legacy boot option, all legacy boot option is getting from
  the legacy BBS table.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2016 Intel Corporation.

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

#include "BBSsupport.h"

/**
  Re-order the Boot Option according to the DevOrder.

  The routine re-orders the Boot Option in BootOption array according to
  the order specified by DevOrder.

  @param DevOrder           Pointer to buffer containing the BBS Index,
                            high 8-bit value 0xFF indicating a disabled boot option
  @param DevOrderCount      Count of the BBS Index
  @param EnBootOption       Callee allocated buffer containing the enabled Boot Option Numbers
  @param EnBootOptionCount  Count of the enabled Boot Option Numbers
  @param DisBootOption      Callee allocated buffer containing the disabled Boot Option Numbers
  @param DisBootOptionCount Count of the disabled Boot Option Numbers
**/
VOID
OrderLegacyBootOption4SameType (
  UINT16                   *DevOrder,
  UINTN                    DevOrderCount,
  UINT16                   **EnBootOption,
  UINTN                    *EnBootOptionCount,
  UINT16                   **DisBootOption,
  UINTN                    *DisBootOptionCount
  )
{
  EFI_STATUS               Status;
  UINT16                   *NewBootOption;
  UINT16                   *BootOrder;
  UINTN                    BootOrderSize;
  UINTN                    Index;
  UINTN                    StartPosition;

  EFI_BOOT_MANAGER_LOAD_OPTION    BootOption;

  CHAR16                   OptionName[sizeof ("Boot####")];
  UINT16                   *BbsIndexArray;
  UINT16                   *DeviceTypeArray;

  NewBootOption = NULL;
  BootOrder = NULL;
  BbsIndexArray = NULL;
  DeviceTypeArray = NULL;

  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &BootOrderSize);
  ASSERT (BootOrder != NULL);
  if (BootOrder == NULL) return;

  BbsIndexArray       = AllocatePool (BootOrderSize);
  if (BbsIndexArray == NULL) goto EXIT;

  DeviceTypeArray     = AllocatePool (BootOrderSize);
  if (DeviceTypeArray == NULL) goto EXIT;

  *EnBootOption       = AllocatePool (BootOrderSize);
  ASSERT (*EnBootOption != NULL);
  if (*EnBootOption == NULL) goto EXIT;

  *DisBootOption      = AllocatePool (BootOrderSize);
  ASSERT (*DisBootOption != NULL);
  if (*DisBootOption == NULL) goto EXIT;

  *DisBootOptionCount = 0;
  *EnBootOptionCount  = 0;
  Index               = 0;

  for (Index = 0; Index < BootOrderSize / sizeof (UINT16); Index++) {

    UnicodeSPrint (OptionName, sizeof (OptionName), L"Boot%04X", BootOrder[Index]);
    Status = EfiBootManagerVariableToLoadOption (OptionName, &BootOption);
    ASSERT_EFI_ERROR (Status);

    if ((DevicePathType (BootOption.FilePath) == BBS_DEVICE_PATH) &&
        (DevicePathSubType (BootOption.FilePath) == BBS_BBS_DP)) {
      //
      // Legacy Boot Option
      //
      ASSERT (BootOption.OptionalDataSize == sizeof (LEGACY_BOOT_OPTION_BBS_DATA));

      DeviceTypeArray[Index] = ((BBS_BBS_DEVICE_PATH *) BootOption.FilePath)->DeviceType;
      BbsIndexArray  [Index] = ((LEGACY_BOOT_OPTION_BBS_DATA *) BootOption.OptionalData)->BbsIndex;
    } else {
      DeviceTypeArray[Index] = BBS_TYPE_UNKNOWN;
      BbsIndexArray  [Index] = 0xFFFF;
    }
    EfiBootManagerFreeLoadOption (&BootOption);
  }

  //
  // Record the corresponding Boot Option Numbers according to the DevOrder
  // Record the EnBootOption and DisBootOption according to the DevOrder
  //
  StartPosition = BootOrderSize / sizeof (UINT16);
  NewBootOption = AllocatePool (DevOrderCount * sizeof (UINT16));
  if (NewBootOption == NULL) goto EXIT;

  while (DevOrderCount-- != 0) {
    for (Index = 0; Index < BootOrderSize / sizeof (UINT16); Index++) {
      if (BbsIndexArray[Index] == (DevOrder[DevOrderCount] & 0xFF)) {
        StartPosition = MIN (StartPosition, Index);
        NewBootOption[DevOrderCount] = BootOrder[Index];

        if ((DevOrder[DevOrderCount] & 0xFF00) == 0xFF00) {
          (*DisBootOption)[*DisBootOptionCount] = BootOrder[Index];
          (*DisBootOptionCount)++;
        } else {
          (*EnBootOption)[*EnBootOptionCount] = BootOrder[Index];
          (*EnBootOptionCount)++;
        }
        break;
      }
    }
  }

  //
  // Overwrite the old BootOption
  //
  CopyMem (&BootOrder[StartPosition], NewBootOption, (*DisBootOptionCount + *EnBootOptionCount) * sizeof (UINT16));
  Status = gRT->SetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  BootOrderSize,
                  BootOrder
                  );
  ASSERT_EFI_ERROR (Status);


EXIT:

  if (NewBootOption != NULL) {
    FreePool (NewBootOption);
  }

  if (DeviceTypeArray != NULL) {
    FreePool (DeviceTypeArray);
  }

  if (BbsIndexArray != NULL) {
    FreePool (BbsIndexArray);
  }

}

/**
  Group the legacy boot options in the BootOption.

  The routine assumes the boot options in the beginning that covers all the device
  types are ordered properly and re-position the following boot options just after
  the corresponding boot options with the same device type.
  For example:
  1. Input  = [Harddisk1 CdRom2 Efi1 Harddisk0 CdRom0 CdRom1 Harddisk2 Efi0]
     Assuming [Harddisk1 CdRom2 Efi1] is ordered properly
     Output = [Harddisk1 Harddisk0 Harddisk2 CdRom2 CdRom0 CdRom1 Efi1 Efi0]

  2. Input  = [Efi1 Efi0 CdRom1 Harddisk0 Harddisk1 Harddisk2 CdRom0 CdRom2]
     Assuming [Efi1 Efi0 CdRom1 Harddisk0] is ordered properly
     Output = [Efi1 Efi0 CdRom1 CdRom0 CdRom2 Harddisk0 Harddisk1 Harddisk2]

**/
VOID
GroupMultipleLegacyBootOption4SameType (
  VOID
  )
{
  EFI_STATUS                   Status;
  UINTN                        Index;
  UINTN                        DeviceIndex;
  UINTN                        DeviceTypeIndex[7];
  UINTN                        *NextIndex;
  UINT16                       OptionNumber;
  UINT16                       *BootOrder;
  UINTN                        BootOrderSize;
  CHAR16                       OptionName[sizeof ("Boot####")];
  EFI_BOOT_MANAGER_LOAD_OPTION BootOption;

  SetMem (DeviceTypeIndex, sizeof (DeviceTypeIndex), 0xff);

  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &BootOrderSize);
  if (BootOrder == NULL) return;

  for (Index = 0; Index < BootOrderSize / sizeof (UINT16); Index++) {
    UnicodeSPrint (OptionName, sizeof (OptionName), L"Boot%04X", BootOrder[Index]);
    Status = EfiBootManagerVariableToLoadOption (OptionName, &BootOption);
    ASSERT_EFI_ERROR (Status);

    if ((DevicePathType (BootOption.FilePath) == BBS_DEVICE_PATH) &&
        (DevicePathSubType (BootOption.FilePath) == BBS_BBS_DP)) {
      //
      // Legacy Boot Option
      //
      ASSERT ((((BBS_BBS_DEVICE_PATH *) BootOption.FilePath)->DeviceType & 0xF) < sizeof (DeviceTypeIndex) / sizeof (DeviceTypeIndex[0]));
      NextIndex = &DeviceTypeIndex[((BBS_BBS_DEVICE_PATH *) BootOption.FilePath)->DeviceType & 0xF];

      if (*NextIndex == (UINTN) -1) {
        //
        // *NextIndex is the Index in BootOrder to put the next Option Number for the same type
        //
        *NextIndex = Index + 1;
      } else {
        //
        // insert the current boot option before *NextIndex, causing [*Next .. Index] shift right one position
        //
        OptionNumber = BootOrder[Index];
        CopyMem (&BootOrder[*NextIndex + 1], &BootOrder[*NextIndex], (Index - *NextIndex) * sizeof (UINT16));
        BootOrder[*NextIndex] = OptionNumber;

        //
        // Update the DeviceTypeIndex array to reflect the right shift operation
        //
        for (DeviceIndex = 0; DeviceIndex < sizeof (DeviceTypeIndex) / sizeof (DeviceTypeIndex[0]); DeviceIndex++) {
          if (DeviceTypeIndex[DeviceIndex] != (UINTN) -1 && DeviceTypeIndex[DeviceIndex] >= *NextIndex) {
            DeviceTypeIndex[DeviceIndex]++;
          }
        }
      }
    }
    EfiBootManagerFreeLoadOption (&BootOption);
  }

  gRT->SetVariable (
         L"BootOrder",
         &gEfiGlobalVariableGuid,
         VAR_ATTR_NV_BS_RT,
         BootOrderSize,
         BootOrder
         );

  FreePool (BootOrder);
}
