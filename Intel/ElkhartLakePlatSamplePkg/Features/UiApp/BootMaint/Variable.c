/** @file
  Variable operation that will be used by bootmaint

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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

#include "BootMaint.h"

/**
  Delete Boot Option that represent a Deleted state in BootOptionMenu.
  After deleting this boot option, call Var_ChangeBootOrder to
  make sure BootOrder is in valid state.

  @retval EFI_SUCCESS   If all boot load option EFI Variables corresponding to
                        BM_LOAD_CONTEXT marked for deletion is deleted.
  @retval EFI_NOT_FOUND If can not find the boot option want to be deleted.
  @return Others        If failed to update the "BootOrder" variable after deletion.

**/
EFI_STATUS
Var_DelBootOption (
  VOID
  )
{
  BM_MENU_ENTRY                 *NewMenuEntry;
  BM_LOAD_CONTEXT               *NewLoadContext;
  UINT16                        BootString[10];
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         Index2;

  Status  = EFI_SUCCESS;
  Index2  = 0;
  for (Index = 0; Index < BootOptionMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&BootOptionMenu, (Index - Index2));
    if (NULL == NewMenuEntry) {
      return EFI_NOT_FOUND;
    }

    NewLoadContext = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
    if (!NewLoadContext->Deleted) {
      continue;
    }

    UnicodeSPrint (
      BootString,
      sizeof (BootString),
      L"Boot%04X",
      NewMenuEntry->OptionNumber
      );

    EfiLibDeleteVariable (BootString, &gEfiGlobalVariableGuid);
    Index2++;
    //
    // If current Load Option is the same as BootNext,
    // must delete BootNext in order to make sure
    // there will be no panic on next boot
    //
    if (NewLoadContext->IsBootNext) {
      EfiLibDeleteVariable (L"BootNext", &gEfiGlobalVariableGuid);
    }

    RemoveEntryList (&NewMenuEntry->Link);
    BOpt_DestroyMenuEntry (NewMenuEntry);
    NewMenuEntry = NULL;
  }

  BootOptionMenu.MenuNumber -= Index2;

  Status = Var_ChangeBootOrder ();
  return Status;
}

/**
  After any operation on Boot####, there will be a discrepancy in BootOrder.
  Since some are missing but in BootOrder, while some are present but are
  not reflected by BootOrder. Then a function rebuild BootOrder from
  scratch by content from BootOptionMenu is needed.




  @retval  EFI_SUCCESS  The boot order is updated successfully.
  @return               EFI_STATUS other than EFI_SUCCESS if failed to
                        Set the "BootOrder" EFI Variable.

**/
EFI_STATUS
Var_ChangeBootOrder (
  VOID
  )
{
  EFI_STATUS                    Status;
  BM_MENU_ENTRY                 *NewMenuEntry;
  UINT16                        *BootOrderList;
  UINT16                        *BootOrderListPtr;
  UINTN                         BootOrderListSize;
  UINTN                         Index;
  UINTN                         Index2;
  EFI_BOOT_MANAGER_LOAD_OPTION  *BootOption;

  BootOrderList     = NULL;
  BootOrderListSize = 0;
  BootOption        = NULL;
  NewMenuEntry      = NULL;
  Status            = EFI_SUCCESS;

  //
  // First check whether BootOrder is present in current configuration
  //
  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrderList, &BootOrderListSize);

  //
  // If exists, delete it to hold new BootOrder
  //
  if (BootOrderList != NULL) {
    BootOption = EfiBootManagerGetLoadOptions (&BootOrderListSize, LoadOptionTypeBoot);
    EfiLibDeleteVariable (L"BootOrder", &gEfiGlobalVariableGuid);
    FreePool (BootOrderList);
    BootOrderList = NULL;
  }
  //
  // Maybe here should be some check method to ensure that
  // no new added boot options will be added
  // but the setup engine now will give only one callback
  // that is to say, user are granted only one chance to
  // decide whether the boot option will be added or not
  // there should be no indictor to show whether this
  // is a "new" boot option
  //
  if ((BootOrderListSize > 0) && (BootOption != NULL)) {
    BootOrderList = AllocateZeroPool (BootOrderListSize * sizeof (UINT16));
    ASSERT (BootOrderList != NULL);
    if (BootOrderList == NULL) {
      EfiBootManagerFreeLoadOptions (BootOption, BootOrderListSize);
      return EFI_OUT_OF_RESOURCES;
    }

    BootOrderListPtr = BootOrderList;

    //
    // Get all current used, hidden and inactive Boot#### from BootOptionMenu and BootOption.
    // OptionNumber in each BM_LOAD_OPTION is really its
    // #### value.
    //
    for (Index = 0; Index < BootOrderListSize; Index++) {
      if (((BootOption[Index].Attributes & LOAD_OPTION_HIDDEN) != 0) || ((BootOption[Index].Attributes & LOAD_OPTION_ACTIVE) == 0)) {
        *BootOrderList = (UINT16) BootOption[Index].OptionNumber;
      } else {
        //
        // If the option exists in both BootOption and BootOptionMenu, put it into BootOrderList.
        //
        for (Index2 = 0; Index2 < BootOptionMenu.MenuNumber; Index2++) {
          NewMenuEntry = BOpt_GetMenuEntry (&BootOptionMenu, Index2);
          if (NewMenuEntry->OptionNumber == BootOption[Index].OptionNumber) {
            *BootOrderList = (UINT16) NewMenuEntry->OptionNumber;
            break;
          }
        }
        if (NewMenuEntry != NULL) {
          if (*BootOrderList != (UINT16) NewMenuEntry->OptionNumber) {
            continue;
          }
        }
      }
      BootOrderList++;
    }

    BootOrderList = BootOrderListPtr;

    //
    // After building the BootOrderList, write it back
    //
    Status = gRT->SetVariable (
                    L"BootOrder",
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    BootOrderListSize * sizeof (UINT16),
                    BootOrderList
                    );
  }

  if (BootOption != NULL) {
    EfiBootManagerFreeLoadOptions (BootOption, BootOrderListSize);
  }
  return Status;
}

/**
  Delete Load Option that represent a Deleted state in BootOptionMenu.
  After deleting this Driver option, call Var_ChangeDriverOrder to
  make sure DriverOrder is in valid state.

  @retval EFI_SUCCESS       Load Option is successfully updated.
  @retval EFI_NOT_FOUND     Fail to find the driver option want to be deleted.
  @return Other value than EFI_SUCCESS if failed to update "Driver Order" EFI
          Variable.

**/
EFI_STATUS
Var_DelDriverOption (
  VOID
  )
{
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_LOAD_CONTEXT *NewLoadContext;
  UINT16          DriverString[12];
  EFI_STATUS      Status;
  UINTN           Index;
  UINTN           Index2;

  Status  = EFI_SUCCESS;
  Index2  = 0;
  for (Index = 0; Index < DriverOptionMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&DriverOptionMenu, (Index - Index2));
    if (NULL == NewMenuEntry) {
      return EFI_NOT_FOUND;
    }

    NewLoadContext = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
    if (!NewLoadContext->Deleted) {
      continue;
    }

    UnicodeSPrint (
      DriverString,
      sizeof (DriverString),
      L"Driver%04X",
      NewMenuEntry->OptionNumber
      );

    EfiLibDeleteVariable (DriverString, &gEfiGlobalVariableGuid);
    Index2++;

    RemoveEntryList (&NewMenuEntry->Link);
    BOpt_DestroyMenuEntry (NewMenuEntry);
    NewMenuEntry = NULL;
  }

  DriverOptionMenu.MenuNumber -= Index2;

  Status = Var_ChangeDriverOrder ();
  return Status;
}

/**
  After any operation on Driver####, there will be a discrepancy in
  DriverOrder. Since some are missing but in DriverOrder, while some
  are present but are not reflected by DriverOrder. Then a function
  rebuild DriverOrder from scratch by content from DriverOptionMenu is
  needed.

  @retval  EFI_SUCCESS  The driver order is updated successfully.
  @return  Other status than EFI_SUCCESS if failed to set the "DriverOrder" EFI Variable.

**/
EFI_STATUS
Var_ChangeDriverOrder (
  VOID
  )
{
  EFI_STATUS    Status;
  BM_MENU_ENTRY *NewMenuEntry;
  UINT16        *DriverOrderList;
  UINT16        *DriverOrderListPtr;
  UINTN         DriverOrderListSize;
  UINTN         Index;

  DriverOrderList     = NULL;
  DriverOrderListSize = 0;

  //
  // First check whether DriverOrder is present in current configuration
  //
  GetEfiGlobalVariable2 (L"DriverOrder", (VOID **) &DriverOrderList, &DriverOrderListSize);
  //
  // If exists, delete it to hold new DriverOrder
  //
  if (DriverOrderList != NULL) {
    EfiLibDeleteVariable (L"DriverOrder", &gEfiGlobalVariableGuid);
    FreePool (DriverOrderList);
    DriverOrderList = NULL;
  }

  DriverOrderListSize = DriverOptionMenu.MenuNumber;

  if (DriverOrderListSize > 0) {
    DriverOrderList = AllocateZeroPool (DriverOrderListSize * sizeof (UINT16));
    ASSERT (DriverOrderList != NULL);
    if (DriverOrderList == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    DriverOrderListPtr = DriverOrderList;

    //
    // Get all current used Driver#### from DriverOptionMenu.
    // OptionNumber in each BM_LOAD_OPTION is really its
    // #### value.
    //
    for (Index = 0; Index < DriverOrderListSize; Index++) {
      NewMenuEntry      = BOpt_GetMenuEntry (&DriverOptionMenu, Index);
      *DriverOrderList  = (UINT16) NewMenuEntry->OptionNumber;
      DriverOrderList++;
    }

    DriverOrderList = DriverOrderListPtr;

    //
    // After building the DriverOrderList, write it back
    //
    Status = gRT->SetVariable (
                    L"DriverOrder",
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    DriverOrderListSize * sizeof (UINT16),
                    DriverOrderList
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }
  return EFI_SUCCESS;
}

/**
  Update the device path of "ConOut", "ConIn" and "ErrOut"
  based on the new BaudRate, Data Bits, parity and Stop Bits
  set.

**/
VOID
Var_UpdateAllConsoleOption (
  VOID
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *OutDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *InpDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *ErrDevicePath;
  EFI_STATUS                Status;

  GetEfiGlobalVariable2 (L"ConOut", (VOID **) &OutDevicePath, NULL);
  GetEfiGlobalVariable2 (L"ConIn", (VOID **) &InpDevicePath, NULL);
  GetEfiGlobalVariable2 (L"ErrOut", (VOID **) &ErrDevicePath, NULL);
  if (OutDevicePath != NULL) {
    ChangeVariableDevicePath (OutDevicePath);
    Status = gRT->SetVariable (
                    L"ConOut",
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    GetDevicePathSize (OutDevicePath),
                    OutDevicePath
                    );
    ASSERT (!EFI_ERROR (Status));
  }

  if (InpDevicePath != NULL) {
    ChangeVariableDevicePath (InpDevicePath);
    Status = gRT->SetVariable (
                    L"ConIn",
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    GetDevicePathSize (InpDevicePath),
                    InpDevicePath
                    );
    ASSERT (!EFI_ERROR (Status));
  }

  if (ErrDevicePath != NULL) {
    ChangeVariableDevicePath (ErrDevicePath);
    Status = gRT->SetVariable (
                    L"ErrOut",
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    GetDevicePathSize (ErrDevicePath),
                    ErrDevicePath
                    );
    ASSERT (!EFI_ERROR (Status));
  }
}

/**
  This function delete and build multi-instance device path for
  specified type of console device.

  This function clear the EFI variable defined by ConsoleName and
  gEfiGlobalVariableGuid. It then build the multi-instance device
  path by appending the device path of the Console (In/Out/Err) instance
  in ConsoleMenu. Then it scan all corresponding console device by
  scanning Terminal (built from device supporting Serial I/O instances)
  devices in TerminalMenu. At last, it save a EFI variable specifed
  by ConsoleName and gEfiGlobalVariableGuid.

  @param ConsoleName     The name for the console device type. They are
                         usually "ConIn", "ConOut" and "ErrOut".
  @param ConsoleMenu     The console memu which is a list of console devices.
  @param UpdatePageId    The flag specifying which type of console device
                         to be processed.

  @retval EFI_SUCCESS    The function complete successfully.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.

**/
EFI_STATUS
Var_UpdateConsoleOption (
  IN UINT16                     *ConsoleName,
  IN BM_MENU_OPTION             *ConsoleMenu,
  IN UINT16                     UpdatePageId
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *ConDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *ConActDevPath;
  BM_MENU_ENTRY             *NewMenuEntry;
  BM_CONSOLE_CONTEXT        *NewConsoleContext;
  BM_TERMINAL_CONTEXT       *NewTerminalContext;
  EFI_STATUS                Status;
  VENDOR_DEVICE_PATH        Vendor;
  EFI_DEVICE_PATH_PROTOCOL  *TerminalDevicePath;
  UINTN                     Index;
  CHAR16                    ActConsoleName[20];

  GetEfiGlobalVariable2 (ConsoleName, (VOID **) &ConDevicePath, NULL);
  if (ConDevicePath != NULL) {
    EfiLibDeleteVariable (ConsoleName, &gEfiGlobalVariableGuid);
    FreePool (ConDevicePath);
    ConDevicePath = NULL;
  };
  UnicodeSPrint (ActConsoleName, sizeof (ActConsoleName), L"%sAct", ConsoleName);
  GetEfiGlobalVariable2 (ActConsoleName, (VOID **) &ConActDevPath, NULL);
  if (ConActDevPath != NULL) {
    EfiLibDeleteVariable (
      ActConsoleName,
      &gPlatformGlobalVariableGuid
      );
    FreePool (ConActDevPath);
    ConActDevPath = NULL;
  }

  //
  // First add all console input device from console input menu
  //
  for (Index = 0; Index < ConsoleMenu->MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (ConsoleMenu, Index);

    NewConsoleContext = (BM_CONSOLE_CONTEXT *) NewMenuEntry->VariableContext;
    if (NewConsoleContext->IsActive) {
      ConDevicePath = AppendDevicePathInstance (
                        ConDevicePath,
                        NewConsoleContext->DevicePath
                        );
    }
  }

  for (Index = 0; Index < TerminalMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, Index);

    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    if (NewTerminalContext->IsEnabled == 0x01) {
      Vendor.Header.Type    = MESSAGING_DEVICE_PATH;
      Vendor.Header.SubType = MSG_VENDOR_DP;

      ASSERT (NewTerminalContext->TerminalType < (sizeof (TerminalTypeGuid) / sizeof (TerminalTypeGuid[0])));
      CopyMem (
        &Vendor.Guid,
        &TerminalTypeGuid[NewTerminalContext->TerminalType],
        sizeof (EFI_GUID)
        );
      SetDevicePathNodeLength (&Vendor.Header, sizeof (VENDOR_DEVICE_PATH));
      TerminalDevicePath = AppendDevicePathNode (
                            NewTerminalContext->DevicePath,
                            (EFI_DEVICE_PATH_PROTOCOL *) &Vendor
                            );
      ASSERT (TerminalDevicePath != NULL);
      ChangeTerminalDevicePath (&TerminalDevicePath, TRUE);
      ConDevicePath = AppendDevicePathInstance (
                        ConDevicePath,
                        TerminalDevicePath
                        );
    }
  }

  if (ConDevicePath != NULL) {
    Status = gRT->SetVariable (
                    ConsoleName,
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    GetDevicePathSize (ConDevicePath),
                    ConDevicePath
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    ConActDevPath = DuplicateDevicePath (ConDevicePath);
    Status = gRT->SetVariable (
                    ActConsoleName,
                    &gEfiGlobalVariableGuid,
                    VAR_ATTR_NV_BS_RT,
                    GetDevicePathSize (ConActDevPath),
                    ConActDevPath
                    );
    if (EFI_ERROR (Status)) {
      FreePool (ConActDevPath);
      return Status;
    }
  }
  if (ConActDevPath != NULL) {
    FreePool (ConActDevPath);
  }

  return EFI_SUCCESS;

}

/**
  This function delete and build multi-instance device path ConIn
  console device.

  @retval EFI_SUCCESS    The function complete successfully.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.
**/
EFI_STATUS
Var_UpdateConsoleInpOption (
  VOID
  )
{
  return Var_UpdateConsoleOption (L"ConIn", &ConsoleInpMenu, FORM_CON_IN_ID);
}

/**
  This function delete and build multi-instance device path ConOut
  console device.

  @retval EFI_SUCCESS    The function complete successfully.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.
**/
EFI_STATUS
Var_UpdateConsoleOutOption (
  VOID
  )
{
  return Var_UpdateConsoleOption (L"ConOut", &ConsoleOutMenu, FORM_CON_OUT_ID);
}

/**
  This function delete and build multi-instance device path ErrOut
  console device.

  @retval EFI_SUCCESS    The function complete successfully.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.
**/
EFI_STATUS
Var_UpdateErrorOutOption (
  VOID
  )
{
  return Var_UpdateConsoleOption (L"ErrOut", &ConsoleErrMenu, FORM_CON_ERR_ID);
}

/**
  This function delete and build Out of Band console device.

  @param   MenuIndex   Menu index which user select in the terminal menu list.

  @retval EFI_SUCCESS    The function complete successfully.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.
**/
EFI_STATUS
Var_UpdateOutOfBandOption (
  IN  UINT16                  MenuIndex
  )
{
  EFI_STATUS               Status;
  BM_MENU_ENTRY            *NewMenuEntry;
  BM_TERMINAL_CONTEXT      *NewTerminalContext;
  EFI_DEVICE_PATH_PROTOCOL *SavedDevicePath;
  VENDOR_DEVICE_PATH       Vendor;
  UINTN                    DevicePathLen;

  Status = EFI_SUCCESS;
  NewTerminalContext = NULL;
  GetVariable2 (L"OutOfBand", &gOutOfBandGuid, (VOID **) &SavedDevicePath, NULL);

  if (MenuIndex < TerminalMenu.MenuNumber) {
    NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, MenuIndex);
    if (NULL == NewMenuEntry) {
      return EFI_NOT_FOUND;
    }

    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    ASSERT (NewTerminalContext != NULL);
    if (NewTerminalContext == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    DevicePathLen = GetDevicePathSize (NewTerminalContext->DevicePath) - sizeof (EFI_DEVICE_PATH_PROTOCOL);
    if ((SavedDevicePath == NULL) ||
      (CompareMem (SavedDevicePath, NewTerminalContext->DevicePath, DevicePathLen) != 0)) {
      EfiLibDeleteVariable (L"OutOfBand", &gOutOfBandGuid);
      //
      // Append the terminal type device path node, used for ACPI table get info about terminal type.
      //
      ASSERT (NewTerminalContext->TerminalType < (sizeof (TerminalTypeGuid) / sizeof (TerminalTypeGuid[0])));
      CopyMem (
        &Vendor.Guid,
        &TerminalTypeGuid[NewTerminalContext->TerminalType],
        sizeof (EFI_GUID)
        );
      SetDevicePathNodeLength (&Vendor.Header, sizeof (VENDOR_DEVICE_PATH));
      SavedDevicePath = AppendDevicePathNode (
                            NewTerminalContext->DevicePath,
                            (EFI_DEVICE_PATH_PROTOCOL *) &Vendor
                            );

      Status = gRT->SetVariable (
                      L"OutOfBand",
                      &gOutOfBandGuid,
                      VAR_ATTR_NV_BS,
                      GetDevicePathSize (SavedDevicePath),
                      SavedDevicePath
                      );
    }
  } else {
    if (SavedDevicePath != NULL) {
      EfiLibDeleteVariable (L"OutOfBand", &gOutOfBandGuid);
    }
  }

  return Status;
}

/**
  This function create a currently loaded Drive Option from
  the BMM. It then appends this Driver Option to the end of
  the "DriverOrder" list. It append this Driver Opotion to the end
  of DriverOptionMenu.

  @param CallbackData    The BMM context data.
  @param HiiHandle       The HII handle associated with the BMM formset.
  @param DescriptionData The description of this driver option.
  @param OptionalData    The optional load option.
  @param ForceReconnect  If to force reconnect.
  @param DescriptionSize Size of DescriptionData.

  @retval EFI_OUT_OF_RESOURCES If not enought memory to complete the operation.
  @retval EFI_SUCCESS          If function completes successfully.
  @retval EFI_BUFFER_TOO_SMALL DescriptionSize is zero.

**/
EFI_STATUS
Var_UpdateDriverOption (
  IN  BMM_CALLBACK_DATA         *CallbackData,
  IN  EFI_HII_HANDLE            HiiHandle,
  IN  UINT16                    *DescriptionData,
  IN  UINT16                    *OptionalData,
  IN  UINT8                     ForceReconnect,
  IN  UINTN                     DescriptionSize
  )
{
  UINT16          Index;
  UINT16          *DriverOrderList;
  UINT16          *NewDriverOrderList;
  UINT16          DriverString[12];
  UINTN           DriverOrderListSize;
  VOID            *Buffer;
  UINTN           BufferSize;
  UINT8           *Ptr;
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_LOAD_CONTEXT *NewLoadContext;
  BOOLEAN         OptionalDataExist;
  EFI_STATUS      Status;

  if (DescriptionSize == 0) {
    return EFI_BUFFER_TOO_SMALL;
  }
  OptionalDataExist = FALSE;

  Index             = BOpt_GetDriverOptionNumber ();
  UnicodeSPrint (
    DriverString,
    sizeof (DriverString),
    L"Driver%04X",
    Index
    );

  if (*DescriptionData == 0x0000) {
    StrCpyS (DescriptionData, DescriptionSize, DriverString);
  }

  BufferSize = sizeof (UINT32) + sizeof (UINT16) + StrSize (DescriptionData);
  BufferSize += GetDevicePathSize (CallbackData->LoadContext->FilePathList);

  if (*OptionalData != 0x0000) {
    OptionalDataExist = TRUE;
    BufferSize += StrSize (OptionalData);
  }

  Buffer = AllocateZeroPool (BufferSize);
  if (NULL == Buffer) {
    return EFI_OUT_OF_RESOURCES;
  }

  NewMenuEntry = BOpt_CreateMenuEntry (BM_LOAD_CONTEXT_SELECT);
  if (NULL == NewMenuEntry) {
    FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  NewLoadContext                  = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
  NewLoadContext->Deleted         = FALSE;
  NewLoadContext->LoadOptionSize  = BufferSize;
  Ptr = (UINT8 *) Buffer;
  NewLoadContext->LoadOption = Ptr;
  *((UINT32 *) Ptr) = LOAD_OPTION_ACTIVE | (ForceReconnect << 1);
  NewLoadContext->Attributes = *((UINT32 *) Ptr);
  NewLoadContext->IsActive = TRUE;
  NewLoadContext->ForceReconnect = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_FORCE_RECONNECT);

  Ptr += sizeof (UINT32);
  *((UINT16 *) Ptr) = (UINT16) GetDevicePathSize (CallbackData->LoadContext->FilePathList);
  NewLoadContext->FilePathListLength = *((UINT16 *) Ptr);

  Ptr += sizeof (UINT16);
  CopyMem (
    Ptr,
    DescriptionData,
    StrSize (DescriptionData)
    );

  NewLoadContext->Description = AllocateZeroPool (StrSize (DescriptionData));
  ASSERT (NewLoadContext->Description != NULL);
  NewMenuEntry->DisplayString = NewLoadContext->Description;
  CopyMem (
    NewLoadContext->Description,
    (VOID *) Ptr,
    StrSize (DescriptionData)
    );

  Ptr += StrSize (DescriptionData);
  CopyMem (
    Ptr,
    CallbackData->LoadContext->FilePathList,
    GetDevicePathSize (CallbackData->LoadContext->FilePathList)
    );

  NewLoadContext->FilePathList = AllocateZeroPool (GetDevicePathSize (CallbackData->LoadContext->FilePathList));
  ASSERT (NewLoadContext->FilePathList != NULL);

  CopyMem (
    NewLoadContext->FilePathList,
    (VOID *) Ptr,
    GetDevicePathSize (CallbackData->LoadContext->FilePathList)
    );

  NewMenuEntry->HelpString    = UiDevicePathToStr (NewLoadContext->FilePathList);
  NewMenuEntry->OptionNumber  = Index;
  NewMenuEntry->DisplayStringToken = GetStringTokenFromDepository (
                                      CallbackData,
                                      DriverOptionStrDepository
                                      );
  NewMenuEntry->DisplayStringToken = HiiSetString (HiiHandle, 0, NewMenuEntry->DisplayString, NULL);

  NewMenuEntry->HelpStringToken = GetStringTokenFromDepository (
                                    CallbackData,
                                    DriverOptionHelpStrDepository
                                    );
  NewMenuEntry->HelpStringToken = HiiSetString (HiiHandle, 0, NewMenuEntry->HelpString, NULL);

  if (OptionalDataExist) {
    Ptr += (UINT8) GetDevicePathSize (CallbackData->LoadContext->FilePathList);

    CopyMem (
      Ptr,
      OptionalData,
      StrSize (OptionalData)
      );
  }

  Status = gRT->SetVariable (
                  DriverString,
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  BufferSize,
                  Buffer
                  );
  ASSERT_EFI_ERROR (Status);
  GetEfiGlobalVariable2 (L"DriverOrder", (VOID **) &DriverOrderList, &DriverOrderListSize);
  NewDriverOrderList = AllocateZeroPool (DriverOrderListSize + sizeof (UINT16));
  ASSERT (NewDriverOrderList != NULL);
  if (NewDriverOrderList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (NewDriverOrderList, DriverOrderList, DriverOrderListSize);
  NewDriverOrderList[DriverOrderListSize / sizeof (UINT16)] = Index;
  if (DriverOrderList != NULL) {
    EfiLibDeleteVariable (L"DriverOrder", &gEfiGlobalVariableGuid);
  }

  Status = gRT->SetVariable (
                  L"DriverOrder",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  DriverOrderListSize + sizeof (UINT16),
                  NewDriverOrderList
                  );
  ASSERT_EFI_ERROR (Status);
  if (DriverOrderList != NULL) {
    FreePool (DriverOrderList);
  }
  DriverOrderList = NULL;
  FreePool (NewDriverOrderList);
  InsertTailList (&DriverOptionMenu.Head, &NewMenuEntry->Link);
  DriverOptionMenu.MenuNumber++;

  *DescriptionData  = 0x0000;
  *OptionalData     = 0x0000;
  return EFI_SUCCESS;
}

/**
  This function create a currently loaded Boot Option from
  the BMM. It then appends this Boot Option to the end of
  the "BootOrder" list. It also append this Boot Opotion to the end
  of BootOptionMenu.

  @param CallbackData    The BMM context data.
  @param NvRamMap        The file explorer formset internal state.
  @param BootDescriptionSize    Size of NvRamMap->BootOptionalData.

  @retval EFI_OUT_OF_RESOURCES If not enought memory to complete the operation.
  @retval EFI_SUCCESS          If function completes successfully.
  @retval EFI_BUFFER_TOO_SMALL BootDescriptionSize is zero.

**/
EFI_STATUS
Var_UpdateBootOption (
  IN  BMM_CALLBACK_DATA                   *CallbackData,
  IN  FILE_EXPLORER_NV_DATA               *NvRamMap,
  IN  UINTN                               BootDescriptionSize
  )
{
  UINT16          *BootOrderList;
  UINT16          *NewBootOrderList;
  UINTN           BootOrderListSize;
  UINT16          BootString[10];
  VOID            *Buffer;
  UINTN           BufferSize;
  UINT8           *Ptr;
  UINT16          Index;
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_LOAD_CONTEXT *NewLoadContext;
  BOOLEAN         OptionalDataExist;
  EFI_STATUS      Status;

  if (BootDescriptionSize == 0) {
    return EFI_BUFFER_TOO_SMALL;
  }
  OptionalDataExist = FALSE;

  Index = BOpt_GetBootOptionNumber () ;
  UnicodeSPrint (BootString, sizeof (BootString), L"Boot%04X", Index);

  if (NvRamMap->BootDescriptionData[0] == 0x0000) {
    StrCpyS (NvRamMap->BootDescriptionData, BootDescriptionSize, BootString);
  }

  BufferSize = sizeof (UINT32) + sizeof (UINT16) + StrSize (NvRamMap->BootDescriptionData);
  BufferSize += GetDevicePathSize (CallbackData->LoadContext->FilePathList);

  if (NvRamMap->BootOptionalData[0] != 0x0000) {
    OptionalDataExist = TRUE;
    BufferSize += StrSize (NvRamMap->BootOptionalData);
  }

  Buffer = AllocateZeroPool (BufferSize);
  if (NULL == Buffer) {
    return EFI_OUT_OF_RESOURCES;
  }

  NewMenuEntry = BOpt_CreateMenuEntry (BM_LOAD_CONTEXT_SELECT);
  if (NULL == NewMenuEntry) {
    return EFI_OUT_OF_RESOURCES;
  }

  NewLoadContext                  = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
  NewLoadContext->Deleted         = FALSE;
  NewLoadContext->LoadOptionSize  = BufferSize;
  Ptr = (UINT8 *) Buffer;
  NewLoadContext->LoadOption = Ptr;
  *((UINT32 *) Ptr) = LOAD_OPTION_ACTIVE;
  NewLoadContext->Attributes = *((UINT32 *) Ptr);
  NewLoadContext->IsActive = TRUE;
  NewLoadContext->ForceReconnect = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_FORCE_RECONNECT);

  Ptr += sizeof (UINT32);
  *((UINT16 *) Ptr) = (UINT16) GetDevicePathSize (CallbackData->LoadContext->FilePathList);
  NewLoadContext->FilePathListLength = *((UINT16 *) Ptr);
  Ptr += sizeof (UINT16);

  CopyMem (
    Ptr,
    NvRamMap->BootDescriptionData,
    StrSize (NvRamMap->BootDescriptionData)
    );

  NewLoadContext->Description = AllocateZeroPool (StrSize (NvRamMap->BootDescriptionData));
  ASSERT (NewLoadContext->Description != NULL);

  NewMenuEntry->DisplayString = NewLoadContext->Description;
  CopyMem (
    NewLoadContext->Description,
    (VOID *) Ptr,
    StrSize (NvRamMap->BootDescriptionData)
    );

  Ptr += StrSize (NvRamMap->BootDescriptionData);
  CopyMem (
    Ptr,
    CallbackData->LoadContext->FilePathList,
    GetDevicePathSize (CallbackData->LoadContext->FilePathList)
    );

  NewLoadContext->FilePathList = AllocateZeroPool (GetDevicePathSize (CallbackData->LoadContext->FilePathList));
  ASSERT (NewLoadContext->FilePathList != NULL);

  CopyMem (
    NewLoadContext->FilePathList,
    (VOID *) Ptr,
    GetDevicePathSize (CallbackData->LoadContext->FilePathList)
    );

  NewMenuEntry->HelpString    = UiDevicePathToStr (NewLoadContext->FilePathList);
  NewMenuEntry->OptionNumber  = Index;
  NewMenuEntry->DisplayStringToken = GetStringTokenFromDepository (
                                      CallbackData,
                                      BootOptionStrDepository
                                      );
  NewMenuEntry->DisplayStringToken = HiiSetString (CallbackData->FeHiiHandle, 0, NewMenuEntry->DisplayString, NULL);

  NewMenuEntry->HelpStringToken = GetStringTokenFromDepository (
                                    CallbackData,
                                    BootOptionHelpStrDepository
                                    );
  NewMenuEntry->HelpStringToken = HiiSetString (CallbackData->FeHiiHandle, 0, NewMenuEntry->HelpString, NULL);

  if (OptionalDataExist) {
    Ptr += (UINT8) GetDevicePathSize (CallbackData->LoadContext->FilePathList);

    CopyMem (Ptr, NvRamMap->BootOptionalData, StrSize (NvRamMap->BootOptionalData));
  }

  Status = gRT->SetVariable (
                  BootString,
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  BufferSize,
                  Buffer
                  );
  ASSERT_EFI_ERROR (Status);

  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrderList, &BootOrderListSize);
  NewBootOrderList = AllocateZeroPool (BootOrderListSize + sizeof (UINT16));
  ASSERT (NewBootOrderList != NULL);
  if (NewBootOrderList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (NewBootOrderList, BootOrderList, BootOrderListSize);
  NewBootOrderList[BootOrderListSize / sizeof (UINT16)] = Index;

  if (BootOrderList != NULL) {
    FreePool (BootOrderList);
  }

  Status = gRT->SetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  BootOrderListSize + sizeof (UINT16),
                  NewBootOrderList
                  );
  ASSERT_EFI_ERROR (Status);

  FreePool (NewBootOrderList);
  NewBootOrderList = NULL;
  InsertTailList (&BootOptionMenu.Head, &NewMenuEntry->Link);
  BootOptionMenu.MenuNumber++;

  NvRamMap->BootDescriptionData[0]  = 0x0000;
  NvRamMap->BootOptionalData[0]     = 0x0000;
  return EFI_SUCCESS;
}

/**
  This function update the "BootNext" EFI Variable. If there is
  no "BootNext" specified in BMM, this EFI Variable is deleted.
  It also update the BMM context data specified the "BootNext"
  vaule.

  @param CallbackData    The BMM context data.

  @retval EFI_SUCCESS    The function complete successfully.
  @return                The EFI variable can be saved. See gRT->SetVariable
                         for detail return information.

**/
EFI_STATUS
Var_UpdateBootNext (
  IN BMM_CALLBACK_DATA            *CallbackData
  )
{
  BM_MENU_ENTRY     *NewMenuEntry;
  BM_LOAD_CONTEXT   *NewLoadContext;
  BMM_FAKE_NV_DATA  *CurrentFakeNVMap;
  UINT16            Index;
  EFI_STATUS        Status;

  Status            = EFI_SUCCESS;
  CurrentFakeNVMap  = &CallbackData->BmmFakeNvData;
  for (Index = 0; Index < BootOptionMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&BootOptionMenu, Index);
    ASSERT (NULL != NewMenuEntry);
    if (NewMenuEntry == NULL) {
      return EFI_NOT_FOUND;
    }

    NewLoadContext              = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
    NewLoadContext->IsBootNext  = FALSE;
  }

  if (CurrentFakeNVMap->BootNext == BootOptionMenu.MenuNumber) {
    EfiLibDeleteVariable (L"BootNext", &gEfiGlobalVariableGuid);
    return EFI_SUCCESS;
  }

  NewMenuEntry = BOpt_GetMenuEntry (
                  &BootOptionMenu,
                  CurrentFakeNVMap->BootNext
                  );
  ASSERT (NewMenuEntry != NULL);
  if (NewMenuEntry == NULL) {
    return EFI_NOT_FOUND;
  }

  NewLoadContext = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
  Status = gRT->SetVariable (
                  L"BootNext",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  sizeof (UINT16),
                  &NewMenuEntry->OptionNumber
                  );
  NewLoadContext->IsBootNext              = TRUE;
  CallbackData->BmmOldFakeNVData.BootNext = CurrentFakeNVMap->BootNext;
  return Status;
}

/**
  This function update the "BootOrder" EFI Variable based on
  BMM Formset's NV map. It then refresh BootOptionMenu
  with the new "BootOrder" list.

  @param CallbackData    The BMM context data.

  @retval EFI_SUCCESS             The function complete successfully.
  @retval EFI_OUT_OF_RESOURCES    Not enough memory to complete the function.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.

**/
EFI_STATUS
Var_UpdateBootOrder (
  IN BMM_CALLBACK_DATA            *CallbackData
  )
{
  EFI_STATUS  Status;
  UINT16      Index;
  UINT16      OrderIndex;
  UINT16      *BootOrder;
  UINTN       BootOrderSize;
  UINT16      OptionNumber;

  //
  // First check whether BootOrder is present in current configuration
  //
  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &BootOrderSize);
  if (BootOrder == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ASSERT (BootOptionMenu.MenuNumber <= (sizeof (CallbackData->BmmFakeNvData.BootOptionOrder) / sizeof (CallbackData->BmmFakeNvData.BootOptionOrder[0])));

  //
  // OptionOrder is subset of BootOrder
  //
  for (OrderIndex = 0; (OrderIndex < BootOptionMenu.MenuNumber) && (CallbackData->BmmFakeNvData.BootOptionOrder[OrderIndex] != 0); OrderIndex++) {
    for (Index = OrderIndex; Index < BootOrderSize / sizeof (UINT16); Index++) {
      if ((BootOrder[Index] == (UINT16) (CallbackData->BmmFakeNvData.BootOptionOrder[OrderIndex] - 1)) && (OrderIndex != Index)) {
        OptionNumber = BootOrder[Index];
        CopyMem (&BootOrder[OrderIndex + 1], &BootOrder[OrderIndex], (Index - OrderIndex) * sizeof (UINT16));
        BootOrder[OrderIndex] = OptionNumber;
      }
    }
  }

  Status = gRT->SetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  BootOrderSize,
                  BootOrder
                  );
  FreePool (BootOrder);

  GroupMultipleLegacyBootOption4SameType ();

  BOpt_FreeMenu (&BootOptionMenu);
  BOpt_GetBootOptions (CallbackData);

  return Status;

}

/**
  This function update the "DriverOrder" EFI Variable based on
  BMM Formset's NV map. It then refresh DriverOptionMenu
  with the new "DriverOrder" list.

  @param CallbackData    The BMM context data.

  @retval EFI_SUCCESS           The function complete successfully.
  @retval EFI_OUT_OF_RESOURCES  Not enough memory to complete the function.
  @return The EFI variable can not be saved. See gRT->SetVariable for detail return information.

**/
EFI_STATUS
Var_UpdateDriverOrder (
  IN BMM_CALLBACK_DATA            *CallbackData
  )
{
  EFI_STATUS  Status;
  UINT16      Index;
  UINT16      *DriverOrderList;
  UINT16      *NewDriverOrderList;
  UINTN       DriverOrderListSize;

  DriverOrderList     = NULL;
  DriverOrderListSize = 0;

  //
  // First check whether DriverOrder is present in current configuration
  //
  GetEfiGlobalVariable2 (L"DriverOrder", (VOID **) &DriverOrderList, &DriverOrderListSize);
  NewDriverOrderList = AllocateZeroPool (DriverOrderListSize);

  if (NewDriverOrderList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // If exists, delete it to hold new DriverOrder
  //
  if (DriverOrderList != NULL) {
    EfiLibDeleteVariable (L"DriverOrder", &gEfiGlobalVariableGuid);
    FreePool (DriverOrderList);
  }

  ASSERT (DriverOptionMenu.MenuNumber <= (sizeof (CallbackData->BmmFakeNvData.DriverOptionOrder) / sizeof (CallbackData->BmmFakeNvData.DriverOptionOrder[0])));
  for (Index = 0; Index < DriverOptionMenu.MenuNumber; Index++) {
    NewDriverOrderList[Index] = (UINT16) (CallbackData->BmmFakeNvData.DriverOptionOrder[Index] - 1);
  }

  Status = gRT->SetVariable (
                  L"DriverOrder",
                  &gEfiGlobalVariableGuid,
                  VAR_ATTR_NV_BS_RT,
                  DriverOrderListSize,
                  NewDriverOrderList
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BOpt_FreeMenu (&DriverOptionMenu);
  BOpt_GetDriverOptions (CallbackData);
  return EFI_SUCCESS;
}


/**
  Update the Text Mode of Console.

  @param CallbackData  The context data for BMM.

  @retval EFI_SUCCSS If the Text Mode of Console is updated.
  @return Other value if the Text Mode of Console is not updated.

**/
EFI_STATUS
Var_UpdateConMode (
  IN BMM_CALLBACK_DATA            *CallbackData
  )
{
  EFI_STATUS        Status;
  UINTN             Mode;
  CONSOLE_OUT_MODE  ModeInfo;

  Mode = CallbackData->BmmFakeNvData.ConsoleOutMode;

  Status = gST->ConOut->QueryMode (gST->ConOut, Mode, &(ModeInfo.Column), &(ModeInfo.Row));
  if (!EFI_ERROR(Status)) {
    PcdSet32S (PcdConOutColumn, (UINT32) ModeInfo.Column);
    PcdSet32S (PcdConOutRow, (UINT32) ModeInfo.Row);
  }

  return EFI_SUCCESS;
}
