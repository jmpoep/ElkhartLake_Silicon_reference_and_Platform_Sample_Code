/** @file
  File explorer related functions.

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

#include "BootMaint.h"


#define INTERNAL_EDK_SHELL_NAME            L"Internal EDK Shell"
#define INTERNAL_UEFI_SHELL_NAME           L"Internal UEFI Shell 2.0"

#define IS_STRING_IDENTICAL(a, b)        (StrnCmp (a, b, StrLen (b)) == 0)

GLOBAL_REMOVE_IF_UNREFERENCED SHELL_ARRAY mShellArray[] = {
              {INTERNAL_EDK_SHELL_NAME,  PcdGetPtr (PcdShellFile)},
              {INTERNAL_UEFI_SHELL_NAME, &gUefiShellFileGuid},
            };

/**
  Get device path with Guid in a FV.

  @param FileGuid        File GUID value to be searched.
  @param DevicePath      The searched Device Path.

  @retval EFI_SUCCESS    The Device Path has been found successfully.

**/
EFI_STATUS
FindDevicePathByGuid (
  IN  EFI_GUID                     *FileGuid,
  OUT EFI_DEVICE_PATH_PROTOCOL     **DevicePath
  )
{
  EFI_STATUS                         Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL      *Fv;
  UINT32                             AuthenticationStatus;
  VOID                               *Buffer;
  UINTN                              Size;
  UINTN                              FvHandleCount;
  EFI_HANDLE                         *FvHandleBuffer;
  UINTN                              Index;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH  FileNode;

  Status = EFI_SUCCESS;

  EfiInitializeFwVolDevicepathNode (&FileNode, FileGuid);

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &FvHandleCount,
                  &FvHandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < FvHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    FvHandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &Fv
                    );
    ASSERT_EFI_ERROR (Status);

    Buffer = NULL;
    Size   = 0;
    Status = Fv->ReadSection (
                    Fv,
                    FileGuid,
                    EFI_SECTION_PE32,
                    0,
                    &Buffer,
                    &Size,
                    &AuthenticationStatus
                    );
    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  if (Index == FvHandleCount) {
    FreePool (FvHandleBuffer);
    return EFI_NOT_FOUND;
  }

  *DevicePath = AppendDevicePathNode (
                  DevicePathFromHandle (FvHandleBuffer[Index]),
                  (EFI_DEVICE_PATH_PROTOCOL *) &FileNode
                  );
  ASSERT (*DevicePath != NULL);

  if (FvHandleCount) {
    FreePool (FvHandleBuffer);
  }

  return Status;
}

/**
  Create the firmware volumn as a boot option.

  @param  FileGuid          The pointer to the EFI_GUID.
  @param  Description       The description of the boot option.
  @param  BootOption        The pointer to the EFI_BOOT_MANAGER_LOAD_OPTION.
  @param  Attributes        The attributes of the boot option.
  @param  OptionalData      Optional data of the boot option.
  @param  OptionalDataSize  Size of the optional data of the boot option.

  @retval EFI_SUCCESS       The boot option has been created successfully.

**/
EFI_STATUS
CreateFvBootOption (
  IN EFI_GUID                     *FileGuid,
  IN CHAR16                       *Description,
  IN EFI_BOOT_MANAGER_LOAD_OPTION *BootOption,
  IN UINT32                       Attributes,
  IN UINT8                        *OptionalData,    OPTIONAL
  IN UINT32                       OptionalDataSize
  )
{
  EFI_STATUS                         Status;
  EFI_DEVICE_PATH_PROTOCOL           *DevicePath;

  DevicePath = NULL;

  if ((BootOption == NULL) || (FileGuid == NULL) || (Description == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = FindDevicePathByGuid (FileGuid, &DevicePath);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = EfiBootManagerInitializeLoadOption (
             BootOption,
             LoadOptionNumberUnassigned,
             LoadOptionTypeBoot,
             Attributes,
             Description,
             DevicePath,
             OptionalData,
             OptionalDataSize
             );
  FreePool (DevicePath);
  return Status;
}

/**
  Return the index of the load option in the load option array.

  The function consider two load options are equal when the
  OptionType, Attributes, Description, FilePath and OptionalData are equal.

  @param Key    Pointer to the load option to be found.
  @param Array  Pointer to the array of load options to be found.
  @param Count  Number of entries in the Array.

  @retval -1          Key wasn't found in the Array.
  @retval 0 ~ Count-1 The index of the Key in the Array.
**/
INTN
FindLoadOption (
  IN CONST EFI_BOOT_MANAGER_LOAD_OPTION *Key,
  IN CONST EFI_BOOT_MANAGER_LOAD_OPTION *Array,
  IN UINTN                              Count
  )
{
  UINTN                             Index;

  for (Index = 0; Index < Count; Index++) {
    if ((Key->OptionType == Array[Index].OptionType) &&
        (Key->Attributes == Array[Index].Attributes) &&
        (StrCmp (Key->Description, Array[Index].Description) == 0) &&
        (CompareMem (Key->FilePath, Array[Index].FilePath, GetDevicePathSize (Key->FilePath)) == 0) &&
        (Key->OptionalDataSize == Array[Index].OptionalDataSize) &&
        (CompareMem (Key->OptionalData, Array[Index].OptionalData, Key->OptionalDataSize) == 0)) {
      return (INTN) Index;
    }
  }

  return -1;
}

/**
  Register the boot option as a Global Variable of boot####.

  @param  FileGuid          The pointer to the EFI_GUID.
  @param  Description       The description of the boot option.
  @param  Position          The position of the boot option.
  @param  Attributes        The attributes of the boot option.
  @param  OptionalData      Optional data of the boot option.
  @param  OptionalDataSize  Size of the optional data of the boot option.

  @retval UINTN             The boot option number.

**/
UINTN
RegisterFvBootOption (
  IN EFI_GUID                         *FileGuid,
  IN CHAR16                           *Description,
  IN UINTN                            Position,
  IN UINT32                           Attributes,
  IN UINT8                            *OptionalData,    OPTIONAL
  IN UINT32                           OptionalDataSize
  )
{
  EFI_STATUS                       Status;
  UINTN                            OptionIndex;
  EFI_BOOT_MANAGER_LOAD_OPTION     NewOption;
  EFI_BOOT_MANAGER_LOAD_OPTION     *BootOptions;
  UINTN                            BootOptionCount;

  NewOption.OptionNumber = LoadOptionNumberUnassigned;
  Status = CreateFvBootOption (FileGuid, Description, &NewOption, Attributes, OptionalData, OptionalDataSize);
  if (!EFI_ERROR (Status)) {
    BootOptions = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);

    OptionIndex = FindLoadOption (&NewOption, BootOptions, BootOptionCount);

    if (OptionIndex == -1) {
      Status = EfiBootManagerAddLoadOptionVariable (&NewOption, Position);
      ASSERT_EFI_ERROR (Status);
    } else {
      NewOption.OptionNumber = BootOptions[OptionIndex].OptionNumber;
    }
    EfiBootManagerFreeLoadOption (&NewOption);
    EfiBootManagerFreeLoadOptions (BootOptions, BootOptionCount);
  }

  return NewOption.OptionNumber;
}

/**
  Display a checkbox for Shell boot option in File Explorer page.

  @param CallbackData    The BMM context data.

**/
VOID
DisplayShellOption (
  IN BMM_CALLBACK_DATA            *CallbackData
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  UINTN                       Index2;
  BM_MENU_ENTRY               *NewMenuEntry;
  BOOLEAN                     IsEdkShellExist;
  BOOLEAN                     IsUefiShellExist;
  EFI_STRING_ID               StrRef;
  EFI_STRING_ID               StrRefHelp;
  CHAR16                      String[100];
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;

  DevicePath       = NULL;
  NewMenuEntry     = NULL;
  IsEdkShellExist  = FALSE;
  IsUefiShellExist = FALSE;

  if (FileExplorerDisplayUnknown != CallbackData->FeDisplayContext) {
    return;
  }

  for (Index = 0; Index < BootOptionMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&BootOptionMenu, Index);

    if (IS_STRING_IDENTICAL(NewMenuEntry->DisplayString, INTERNAL_EDK_SHELL_NAME)) {
      IsEdkShellExist = TRUE;
    }
    if (IS_STRING_IDENTICAL(NewMenuEntry->DisplayString, INTERNAL_UEFI_SHELL_NAME)) {
      IsUefiShellExist = TRUE;
    }
  }

  for (Index2 = 0; Index2 < sizeof (mShellArray) / sizeof (mShellArray[0]); Index2++) {
    Status = FindDevicePathByGuid (mShellArray[Index2].ShellGuid, &DevicePath);
    if (!EFI_ERROR (Status)) {
      if ((!IsEdkShellExist  && (IS_STRING_IDENTICAL(mShellArray[Index2].ShellName, INTERNAL_EDK_SHELL_NAME))) ||
          (!IsUefiShellExist && (IS_STRING_IDENTICAL(mShellArray[Index2].ShellName, INTERNAL_UEFI_SHELL_NAME)))) {
        //
        // Create the string for CheckBox OpCode
        //
        UnicodeSPrint (String, sizeof (String), mShellArray[Index2].ShellName);
        StrRef = HiiSetString (CallbackData->FeHiiHandle, 0, String, NULL);

        UnicodeSPrint (String, sizeof (String), UiDevicePathToStr (DevicePath));
        StrRefHelp = HiiSetString (CallbackData->FeHiiHandle, 0, String, NULL);

        HiiCreateCheckBoxOpCode (
          mStartOpCodeHandle,
          (EFI_QUESTION_ID) (BOOT_OPTION_ADD_QUESTION_ID + Index2),
          VARSTORE_ID_BOOT_MAINT,
          (UINT16) (BOOT_OPTION_ADD_VAR_OFFSET + Index2),
          StrRef,
          StrRefHelp,
          0,
          0,
          NULL
          );
      }
    }
  }

  FreePool (DevicePath);
}

/**
  Update the File Explore page.

  @param CallbackData    The BMM context data.
  @param MenuOption      Pointer to menu options to display.

**/
VOID
UpdateFileExplorePage (
  IN BMM_CALLBACK_DATA            *CallbackData,
  BM_MENU_OPTION                  *MenuOption
  )
{
  UINTN                       Index;
  BM_MENU_ENTRY               *NewMenuEntry;
  BM_FILE_CONTEXT             *NewFileContext;
  EFI_FORM_ID                 FormId;

  FormId           = 0;
  NewMenuEntry     = NULL;
  NewFileContext   = NULL;

  RefreshUpdateData ();
  mStartLabel->Number = FORM_FILE_EXPLORER_ID;

  DisplayShellOption (CallbackData);

  for (Index = 0; Index < MenuOption->MenuNumber; Index++) {
    NewMenuEntry    = BOpt_GetMenuEntry (MenuOption, Index);
    NewFileContext  = (BM_FILE_CONTEXT *) NewMenuEntry->VariableContext;

    if (NewFileContext->IsBootLegacy) {
      continue;
    }

    if ((NewFileContext->IsDir) || (FileExplorerStateBootFromFile == CallbackData->FeCurrentState)) {
      //
      // Create Text opcode for directory, also create Text opcode for file in FileExplorerStateBootFromFile.
      //
      HiiCreateActionOpCode (
        mStartOpCodeHandle,
        (UINT16) (FILE_OPTION_OFFSET + Index),
        NewMenuEntry->DisplayStringToken,
        STRING_TOKEN (STR_NULL_STRING),
        EFI_IFR_FLAG_CALLBACK,
        0
        );
    } else {
      //
      // Create Goto opcode for file in FileExplorerStateAddBootOption or FileExplorerStateAddDriverOptionState.
      //
      if (FileExplorerStateAddBootOption == CallbackData->FeCurrentState) {
        FormId = FORM_BOOT_ADD_DESCRIPTION_ID;
      } else if (FileExplorerStateAddDriverOptionState == CallbackData->FeCurrentState) {
        FormId = FORM_DRIVER_ADD_FILE_DESCRIPTION_ID;
      }

      HiiCreateGotoOpCode (
        mStartOpCodeHandle,
        FormId,
        NewMenuEntry->DisplayStringToken,
        STRING_TOKEN (STR_NULL_STRING),
        EFI_IFR_FLAG_CALLBACK,
        (UINT16) (FILE_OPTION_OFFSET + Index)
        );
    }
  }

  HiiUpdateForm (
    CallbackData->FeHiiHandle,
    &mFileExplorerGuid,
    FORM_FILE_EXPLORER_ID,
    mStartOpCodeHandle, // Label FORM_FILE_EXPLORER_ID
    mEndOpCodeHandle    // LABEL_END
    );
}

/**
  Update the file explower page with the refershed file system.


  @param CallbackData    BMM context data
  @param KeyValue        Key value to identify the type of data to expect.

  @retval  TRUE           Inform the caller to create a callback packet to exit file explorer.
  @retval  FALSE          Indicate that there is no need to exit file explorer.

**/
BOOLEAN
UpdateFileExplorer (
  IN BMM_CALLBACK_DATA            *CallbackData,
  IN UINT16                       KeyValue
  )
{
  UINT16          FileOptionMask;
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_FILE_CONTEXT *NewFileContext;
  EFI_FORM_ID     FormId;
  BOOLEAN         ExitFileExplorer;
  EFI_STATUS      Status;

  NewMenuEntry      = NULL;
  NewFileContext    = NULL;
  ExitFileExplorer  = FALSE;

  FileOptionMask    = (UINT16) (FILE_OPTION_MASK & KeyValue);

  if (FileExplorerDisplayUnknown == CallbackData->FeDisplayContext) {
    //
    // First in, display file system.
    //
    BOpt_FreeMenu (&FsOptionMenu);
    BOpt_FindFileSystem (CallbackData);
    CreateMenuStringToken (CallbackData, CallbackData->FeHiiHandle, &FsOptionMenu);

    UpdateFileExplorePage (CallbackData, &FsOptionMenu);

    CallbackData->FeDisplayContext = FileExplorerDisplayFileSystem;
  } else {
    if (FileExplorerDisplayFileSystem == CallbackData->FeDisplayContext) {
      NewMenuEntry = BOpt_GetMenuEntry (&FsOptionMenu, FileOptionMask);
    } else if (FileExplorerDisplayDirectory == CallbackData->FeDisplayContext) {
      NewMenuEntry = BOpt_GetMenuEntry (&DirectoryMenu, FileOptionMask);
    }

    NewFileContext = (BM_FILE_CONTEXT *) NewMenuEntry->VariableContext;

    if (NewFileContext->IsDir ) {
      CallbackData->FeDisplayContext = FileExplorerDisplayDirectory;

      RemoveEntryList (&NewMenuEntry->Link);
      BOpt_FreeMenu (&DirectoryMenu);
      Status = BOpt_FindFiles (CallbackData, NewMenuEntry);
       if (EFI_ERROR (Status)) {
         ExitFileExplorer = TRUE;
         goto exit;
       }
      CreateMenuStringToken (CallbackData, CallbackData->FeHiiHandle, &DirectoryMenu);
      BOpt_DestroyMenuEntry (NewMenuEntry);

      UpdateFileExplorePage (CallbackData, &DirectoryMenu);

    } else {
      switch (CallbackData->FeCurrentState) {
      case FileExplorerStateBootFromFile:
        //
        // Here boot from file
        //
        BootThisFile (NewFileContext);
        ExitFileExplorer = TRUE;
        break;

      case FileExplorerStateAddBootOption:
      case FileExplorerStateAddDriverOptionState:
        if (FileExplorerStateAddBootOption == CallbackData->FeCurrentState) {
          FormId = FORM_BOOT_ADD_DESCRIPTION_ID;
        } else {
          FormId = FORM_DRIVER_ADD_FILE_DESCRIPTION_ID;
        }

        CallbackData->MenuEntry = NewMenuEntry;
        CallbackData->LoadContext->FilePathList = ((BM_FILE_CONTEXT *) (CallbackData->MenuEntry->VariableContext))->DevicePath;

        //
        // Create Subtitle op-code for the display string of the option.
        //
        RefreshUpdateData ();
        mStartLabel->Number = FormId;

        HiiCreateSubTitleOpCode (
          mStartOpCodeHandle,
          NewMenuEntry->DisplayStringToken,
          0,
          0,
          0
          );

        HiiUpdateForm (
          CallbackData->FeHiiHandle,
          &mFileExplorerGuid,
          FormId,
          mStartOpCodeHandle, // Label FormId
          mEndOpCodeHandle    // LABEL_END
          );
        break;

      default:
        break;
      }
    }
  }
  exit:
  return ExitFileExplorer;
}

/**
  This function processes the results of changes in configuration.
  When user select a interactive opcode, this callback will be triggered.
  Based on the Question(QuestionId) that triggers the callback, the corresponding
  actions is performed. It handles:

  1) the addition of boot option.
  2) the addition of driver option.
  3) exit from file browser
  4) update of file content if a dir is selected.
  5) boot the file if a file is selected in "boot from file"


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval  EFI_SUCCESS           The callback successfully handled the action.
  @retval  EFI_OUT_OF_RESOURCES  Not enough storage is available to hold the variable and its data.
  @retval  EFI_DEVICE_ERROR      The variable could not be saved.
  @retval  EFI_UNSUPPORTED       The specified Action is not supported by the callback.
  @retval  EFI_INVALID_PARAMETER If paramter Value or ActionRequest is NULL.
**/
EFI_STATUS
EFIAPI
FileExplorerCallback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  EFI_BROWSER_ACTION                     Action,
  IN  EFI_QUESTION_ID                        QuestionId,
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest
  )
{
  BMM_CALLBACK_DATA     *Private;

  Private = FE_CALLBACK_DATA_FROM_THIS (This);
  if (Action == EFI_BROWSER_ACTION_FORM_OPEN && QuestionId == KEY_VALUE_INIT_FORM) {
    UpdateFileExplorer (Private, 0);
    return EFI_SUCCESS;
  }

  if (Action != EFI_BROWSER_ACTION_CHANGING) {
    //
    // Do nothing for other UEFI Action. Only do call back when data is changed.
    //
    return EFI_UNSUPPORTED;
  }

  if (Value == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (QuestionId >= FILE_OPTION_OFFSET) {
    UpdateFileExplorer (Private, QuestionId);
  }

  return EFI_SUCCESS;
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

  @param[in]  This                Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in]  Configuration       A null-terminated Unicode string in
                                  <ConfigString> format.
  @param[out] Progress            A pointer to a string filled in with the
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
FileExplorerRouteConfig (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN CONST EFI_STRING                     Configuration,
  OUT EFI_STRING                          *Progress
  )
{
  EFI_STATUS                      Status;
  UINTN                           Index;
  UINTN                           BufferSize;
  EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting;
  FILE_EXPLORER_NV_DATA           *FeData;
  BMM_CALLBACK_DATA               *Private;

  if (Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Progress = Configuration;

  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check routing data in <ConfigHdr>.
  // Note: there is no name for Name/Value storage, only GUID will be checked
  //
  if (!HiiIsConfigHdrMatch (Configuration, &mFileExplorerGuid, mFileExplorerStorageName)) {
    return EFI_NOT_FOUND;
  }

  Status = gBS->LocateProtocol (
                  &gEfiHiiConfigRoutingProtocolGuid,
                  NULL,
                  (VOID **) &ConfigRouting
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Private = FE_CALLBACK_DATA_FROM_THIS (This);
  //
  // Get Buffer Storage data from EFI variable
  //
  BufferSize = sizeof (FILE_EXPLORER_NV_DATA );
  FeData = &Private->FeFakeNvData;

  //
  // Convert <ConfigResp> to buffer data by helper function ConfigToBlock()
  //
  Status = ConfigRouting->ConfigToBlock (
                            ConfigRouting,
                            Configuration,
                            (UINT8 *) FeData,
                            &BufferSize,
                            Progress
                            );
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < sizeof (mShellArray) / sizeof (mShellArray[0]); Index++) {
    if (FeData->BootOptionAdd[Index]) {
      RegisterFvBootOption (mShellArray[Index].ShellGuid, mShellArray[Index].ShellName, (UINTN) -1, LOAD_OPTION_ACTIVE, NULL, 0);
      BOpt_GetBootOptions (Private);
      CreateMenuStringToken (Private, Private->FeHiiHandle, &BootOptionMenu);
    }

    //
    // Clear up BootOptionAdd variables
    //
    FeData->BootOptionAdd[Index] = FALSE;
  }

  if (FeData->BootDescriptionData[0] != 0x00 || FeData->BootOptionalData[0] != 0x00) {
    Status = Var_UpdateBootOption (Private, FeData, sizeof (FeData->BootDescriptionData) / sizeof (CHAR16));
    DEBUG ((DEBUG_INFO, "[GINO] FeData->BootDescriptionData size = %d\n", sizeof (FeData->BootDescriptionData) / sizeof (CHAR16)));
    if (EFI_ERROR (Status)) {
      return Status;
    }

    BOpt_GetBootOptions (Private);
    CreateMenuStringToken (Private, Private->FeHiiHandle, &BootOptionMenu);
  }

  if (FeData->DriverDescriptionData[0] != 0x00 || FeData->DriverOptionalData[0] != 0x00) {
    Status = Var_UpdateDriverOption (
              Private,
              Private->FeHiiHandle,
              FeData->DriverDescriptionData,
              FeData->DriverOptionalData,
              FeData->ForceReconnect,
              sizeof (FeData->DriverDescriptionData) / sizeof (CHAR16)
              );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    BOpt_GetDriverOptions (Private);
    CreateMenuStringToken (Private, Private->FeHiiHandle, &DriverOptionMenu);
  }

  //
  // Pass changed uncommitted data back to Form Browser
  //
  HiiSetBrowserData (&mFileExplorerGuid, mFileExplorerStorageName, sizeof (FILE_EXPLORER_NV_DATA), (UINT8 *) FeData, NULL);

  return EFI_SUCCESS;
}
