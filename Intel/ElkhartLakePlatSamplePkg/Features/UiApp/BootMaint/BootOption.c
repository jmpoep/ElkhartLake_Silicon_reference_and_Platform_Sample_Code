/** @file
  Provide boot option support for Application "BootMaint"

  Include file system navigation, system handle selection

  Boot option manipulation

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
#include "BBSsupport.h"

///
/// Define the maximum characters that will be accepted.
///
#define MAX_CHAR            480

/**
  Create a menu entry by given menu type.

  @param MenuType        The Menu type to be created.

  @retval NULL           If failed to create the menu.
  @return the new menu entry.

**/
BM_MENU_ENTRY *
BOpt_CreateMenuEntry (
  UINTN           MenuType
  )
{
  BM_MENU_ENTRY *MenuEntry;
  UINTN         ContextSize;

  //
  // Get context size according to menu type
  //
  switch (MenuType) {
  case BM_LOAD_CONTEXT_SELECT:
    ContextSize = sizeof (BM_LOAD_CONTEXT);
    break;

  case BM_FILE_CONTEXT_SELECT:
    ContextSize = sizeof (BM_FILE_CONTEXT);
    break;

  case BM_CONSOLE_CONTEXT_SELECT:
    ContextSize = sizeof (BM_CONSOLE_CONTEXT);
    break;

  case BM_TERMINAL_CONTEXT_SELECT:
    ContextSize = sizeof (BM_TERMINAL_CONTEXT);
    break;

  case BM_HANDLE_CONTEXT_SELECT:
    ContextSize = sizeof (BM_HANDLE_CONTEXT);
    break;

  case BM_LEGACY_DEV_CONTEXT_SELECT:
    ContextSize = sizeof (BM_LEGACY_DEVICE_CONTEXT);
    break;

  default:
    ContextSize = 0;
    break;
  }

  if (ContextSize == 0) {
    return NULL;
  }

  //
  // Create new menu entry
  //
  MenuEntry = AllocateZeroPool (sizeof (BM_MENU_ENTRY));
  if (MenuEntry == NULL) {
    return NULL;
  }

  MenuEntry->VariableContext = AllocateZeroPool (ContextSize);
  if (MenuEntry->VariableContext == NULL) {
    FreePool (MenuEntry);
    return NULL;
  }

  MenuEntry->Signature        = BM_MENU_ENTRY_SIGNATURE;
  MenuEntry->ContextSelection = MenuType;
  return MenuEntry;
}

/**
  Free up all resource allocated for a BM_MENU_ENTRY.

  @param MenuEntry   A pointer to BM_MENU_ENTRY.

**/
VOID
BOpt_DestroyMenuEntry (
  BM_MENU_ENTRY         *MenuEntry
  )
{
  BM_LOAD_CONTEXT           *LoadContext;
  BM_FILE_CONTEXT           *FileContext;
  BM_CONSOLE_CONTEXT        *ConsoleContext;
  BM_TERMINAL_CONTEXT       *TerminalContext;
  BM_HANDLE_CONTEXT         *HandleContext;
  BM_LEGACY_DEVICE_CONTEXT  *LegacyDevContext;

  //
  //  Select by the type in Menu entry for current context type
  //
  switch (MenuEntry->ContextSelection) {
  case BM_LOAD_CONTEXT_SELECT:
    LoadContext = (BM_LOAD_CONTEXT *) MenuEntry->VariableContext;
    FreePool (LoadContext->FilePathList);
    FreePool (LoadContext->LoadOption);
    if (LoadContext->OptionalData != NULL) {
      FreePool (LoadContext->OptionalData);
    }
    FreePool (LoadContext);
    break;

  case BM_FILE_CONTEXT_SELECT:
    FileContext = (BM_FILE_CONTEXT *) MenuEntry->VariableContext;

    if (!FileContext->IsRoot) {
      FreePool (FileContext->DevicePath);
    } else {
      if (FileContext->FHandle != NULL) {
        FileContext->FHandle->Close (FileContext->FHandle);
      }
    }

    if (FileContext->FileName != NULL) {
      FreePool (FileContext->FileName);
    }
    if (FileContext->Info != NULL) {
      FreePool (FileContext->Info);
    }
    FreePool (FileContext);
    break;

  case BM_CONSOLE_CONTEXT_SELECT:
    ConsoleContext = (BM_CONSOLE_CONTEXT *) MenuEntry->VariableContext;
    FreePool (ConsoleContext->DevicePath);
    FreePool (ConsoleContext);
    break;

  case BM_TERMINAL_CONTEXT_SELECT:
    TerminalContext = (BM_TERMINAL_CONTEXT *) MenuEntry->VariableContext;
    FreePool (TerminalContext->DevicePath);
    FreePool (TerminalContext);
    break;

  case BM_HANDLE_CONTEXT_SELECT:
    HandleContext = (BM_HANDLE_CONTEXT *) MenuEntry->VariableContext;
    FreePool (HandleContext);
    break;

  case BM_LEGACY_DEV_CONTEXT_SELECT:
    LegacyDevContext = (BM_LEGACY_DEVICE_CONTEXT *) MenuEntry->VariableContext;
    FreePool (LegacyDevContext);

  default:
    break;
  }

  FreePool (MenuEntry->DisplayString);
  if (MenuEntry->HelpString != NULL) {
    FreePool (MenuEntry->HelpString);
  }

  FreePool (MenuEntry);
}

/**
  Get the Menu Entry from the list in Menu Entry List.

  If MenuNumber is great or equal to the number of Menu
  Entry in the list, then ASSERT.

  @param MenuOption      The Menu Entry List to read the menu entry.
  @param MenuNumber      The index of Menu Entry.

  @return The Menu Entry.

**/
BM_MENU_ENTRY *
BOpt_GetMenuEntry (
  BM_MENU_OPTION      *MenuOption,
  UINTN               MenuNumber
  )
{
  BM_MENU_ENTRY   *NewMenuEntry;
  UINTN           Index;
  LIST_ENTRY      *List;

  ASSERT (MenuNumber < MenuOption->MenuNumber);

  List = MenuOption->Head.ForwardLink;
  for (Index = 0; Index < MenuNumber; Index++) {
    List = List->ForwardLink;
  }

  NewMenuEntry = CR (List, BM_MENU_ENTRY, Link, BM_MENU_ENTRY_SIGNATURE);

  return NewMenuEntry;
}

/**
  Get the Menu Entry from the list in Menu Entry List.

  If MenuNumber is great or equal to the number of Menu
  Entry in the list, then ASSERT.

  @param MenuOption      The Menu Entry List to read the menu entry.
  @param DevicePath      The device path belong to the devcie we want got.

  @return The Menu Entry.

**/
BM_MENU_ENTRY *
BOpt_GetMenuEntryFromDevicePath (
  BM_MENU_OPTION            *MenuOption,
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  BM_MENU_ENTRY       *NewMenuEntry;
  BM_TERMINAL_CONTEXT *NewTerminalContext;
  UINTN           Index;
  LIST_ENTRY      *List;

  ASSERT (DevicePath != NULL);

  List = MenuOption->Head.ForwardLink;
  for (Index = 0; Index < MenuOption->MenuNumber; Index++) {
    NewMenuEntry = CR (List, BM_MENU_ENTRY, Link, BM_MENU_ENTRY_SIGNATURE);
    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;

    if (CompareMem (NewTerminalContext->DevicePath, DevicePath, GetDevicePathSize(DevicePath)) == 0) {
      return NewMenuEntry;
    }

    List = List->ForwardLink;
  }

  return NULL;
}

/**
  This function build the FsOptionMenu list which records all
  available file system in the system. They includes all instances
  of EFI_SIMPLE_FILE_SYSTEM_PROTOCOL, all instances of EFI_LOAD_FILE_SYSTEM
  and all type of legacy boot device.

  @param CallbackData    BMM context data

  @retval  EFI_SUCCESS             Success find the file system
  @retval  EFI_OUT_OF_RESOURCES    Can not create menu entry

**/
EFI_STATUS
BOpt_FindFileSystem (
  IN BMM_CALLBACK_DATA          *CallbackData
  )
{
  UINTN                     NoBlkIoHandles;
  UINTN                     NoSimpleFsHandles;
  UINTN                     NoLoadFileHandles;
  EFI_HANDLE                *BlkIoHandle;
  EFI_HANDLE                *SimpleFsHandle;
  EFI_HANDLE                *LoadFileHandle;
  UINT16                    *VolumeLabel;
  EFI_BLOCK_IO_PROTOCOL     *BlkIo;
  UINTN                     Index;
  EFI_STATUS                Status;
  BM_MENU_ENTRY             *MenuEntry;
  BM_FILE_CONTEXT           *FileContext;
  UINT16                    *TempStr;
  UINTN                     OptionNumber;
  VOID                      *Buffer;
  BOOLEAN                   RemovableMedia;


  NoSimpleFsHandles = 0;
  NoLoadFileHandles = 0;
  OptionNumber      = 0;
  InitializeListHead (&FsOptionMenu.Head);

  //
  // Locate Handles that support BlockIo protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiBlockIoProtocolGuid,
                  NULL,
                  &NoBlkIoHandles,
                  &BlkIoHandle
                  );
  if (!EFI_ERROR (Status)) {

    for (Index = 0; Index < NoBlkIoHandles; Index++) {
      Status = gBS->HandleProtocol (
                      BlkIoHandle[Index],
                      &gEfiBlockIoProtocolGuid,
                      (VOID **) &BlkIo
                      );

      if (EFI_ERROR (Status)) {
        continue;
      }

      //
      // Issue a dummy read to trigger reinstall of BlockIo protocol for removable media
      //
      if (BlkIo->Media->RemovableMedia) {
        Buffer = AllocateZeroPool (BlkIo->Media->BlockSize);
        if (NULL == Buffer) {
          FreePool (BlkIoHandle);
          return EFI_OUT_OF_RESOURCES;
        }

        BlkIo->ReadBlocks (
                BlkIo,
                BlkIo->Media->MediaId,
                0,
                BlkIo->Media->BlockSize,
                Buffer
                );
        FreePool (Buffer);
      }
    }
    FreePool (BlkIoHandle);
  }

  //
  // Locate Handles that support Simple File System protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleFileSystemProtocolGuid,
                  NULL,
                  &NoSimpleFsHandles,
                  &SimpleFsHandle
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Find all the instances of the File System prototocol
    //
    for (Index = 0; Index < NoSimpleFsHandles; Index++) {
      Status = gBS->HandleProtocol (
                      SimpleFsHandle[Index],
                      &gEfiBlockIoProtocolGuid,
                      (VOID **) &BlkIo
                      );
      if (EFI_ERROR (Status)) {
        //
        // If no block IO exists assume it's NOT a removable media
        //
        RemovableMedia = FALSE;
      } else {
        //
        // If block IO exists check to see if it's remobable media
        //
        RemovableMedia = BlkIo->Media->RemovableMedia;
      }

      //
      // Allocate pool for this load option
      //
      MenuEntry = BOpt_CreateMenuEntry (BM_FILE_CONTEXT_SELECT);
      if (NULL == MenuEntry) {
        FreePool (SimpleFsHandle);
        return EFI_OUT_OF_RESOURCES;
      }

      FileContext = (BM_FILE_CONTEXT *) MenuEntry->VariableContext;

      FileContext->Handle     = SimpleFsHandle[Index];
      MenuEntry->OptionNumber = Index;
      FileContext->FHandle    = EfiLibOpenRoot (FileContext->Handle);
      if (FileContext->FHandle == NULL) {
        BOpt_DestroyMenuEntry (MenuEntry);
        continue;
      }

      MenuEntry->HelpString = UiDevicePathToStr (DevicePathFromHandle (FileContext->Handle));
      FileContext->Info = EfiLibFileSystemVolumeLabelInfo (FileContext->FHandle);
      FileContext->FileName = EfiStrDuplicate (L"\\");
      if (FileContext->FileName == NULL) {
        FreePool (SimpleFsHandle);
        BOpt_DestroyMenuEntry (MenuEntry);
        return EFI_OUT_OF_RESOURCES;
      }
      FileContext->DevicePath = FileDevicePath (
                                  FileContext->Handle,
                                  FileContext->FileName
                                  );
      FileContext->IsDir            = TRUE;
      FileContext->IsRoot           = TRUE;
      FileContext->IsRemovableMedia = RemovableMedia;
      FileContext->IsLoadFile       = FALSE;

      //
      // Get current file system's Volume Label
      //
      if (FileContext->Info == NULL) {
        VolumeLabel = L"NO FILE SYSTEM INFO";
      } else {
        if (FileContext->Info->VolumeLabel == NULL) {
          VolumeLabel = L"NULL VOLUME LABEL";
        } else {
          VolumeLabel = FileContext->Info->VolumeLabel;
          if (*VolumeLabel == 0x0000) {
            VolumeLabel = L"NO VOLUME LABEL";
          }
        }
      }

      TempStr                   = MenuEntry->HelpString;
      MenuEntry->DisplayString  = AllocateZeroPool (MAX_CHAR);
      ASSERT (MenuEntry->DisplayString != NULL);
      if (MenuEntry->DisplayString == NULL) {
        FreePool (SimpleFsHandle);
        BOpt_DestroyMenuEntry (MenuEntry);
        return EFI_OUT_OF_RESOURCES;
      }

      UnicodeSPrint (
        MenuEntry->DisplayString,
        MAX_CHAR,
        L"%s, [%s]",
        VolumeLabel,
        TempStr
        );
      OptionNumber++;
      InsertTailList (&FsOptionMenu.Head, &MenuEntry->Link);
    }
  }

  if (NoSimpleFsHandles != 0) {
    FreePool (SimpleFsHandle);
  }
  //
  // Searching for handles that support Load File protocol
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiLoadFileProtocolGuid,
                  NULL,
                  &NoLoadFileHandles,
                  &LoadFileHandle
                  );

  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < NoLoadFileHandles; Index++) {
      MenuEntry = BOpt_CreateMenuEntry (BM_FILE_CONTEXT_SELECT);
      if (NULL == MenuEntry) {
        FreePool (LoadFileHandle);
        return EFI_OUT_OF_RESOURCES;
      }

      FileContext                   = (BM_FILE_CONTEXT *) MenuEntry->VariableContext;
      FileContext->IsRemovableMedia = FALSE;
      FileContext->IsLoadFile       = TRUE;
      FileContext->Handle           = LoadFileHandle[Index];
      FileContext->IsRoot           = TRUE;

      FileContext->DevicePath       = DevicePathFromHandle (FileContext->Handle);
      FileContext->FileName         = UiDevicePathToStr (FileContext->DevicePath);

      MenuEntry->HelpString     = UiDevicePathToStr (FileContext->DevicePath);

      TempStr                   = MenuEntry->HelpString;
      MenuEntry->DisplayString  = AllocateZeroPool (MAX_CHAR);
      ASSERT (MenuEntry->DisplayString != NULL);
      if (MenuEntry->DisplayString == NULL) {
        FreePool (LoadFileHandle);
        BOpt_DestroyMenuEntry (MenuEntry);
        return EFI_OUT_OF_RESOURCES;
      }

      UnicodeSPrint (
        MenuEntry->DisplayString,
        MAX_CHAR,
        L"Load File [%s]",
        TempStr
        );

      MenuEntry->OptionNumber = OptionNumber;
      OptionNumber++;
      InsertTailList (&FsOptionMenu.Head, &MenuEntry->Link);
    }
  }

  if (NoLoadFileHandles != 0) {
    FreePool (LoadFileHandle);
  }


  //
  // Remember how many file system options are here
  //
  FsOptionMenu.MenuNumber = OptionNumber;
  return EFI_SUCCESS;
}

/**
  Free resources allocated in Allocate Rountine.

  @param FreeMenu        Menu to be freed
**/
VOID
BOpt_FreeMenu (
  BM_MENU_OPTION        *FreeMenu
  )
{
  BM_MENU_ENTRY *MenuEntry;
  while (!IsListEmpty (&FreeMenu->Head)) {
    MenuEntry = CR (
                  FreeMenu->Head.ForwardLink,
                  BM_MENU_ENTRY,
                  Link,
                  BM_MENU_ENTRY_SIGNATURE
                  );
    RemoveEntryList (&MenuEntry->Link);
    BOpt_DestroyMenuEntry (MenuEntry);
  }
  FreeMenu->MenuNumber = 0;
}

/**
  Find files under current directory
  All files and sub-directories in current directory
  will be stored in DirectoryMenu for future use.

  @param CallbackData  The BMM context data.
  @param MenuEntry     The Menu Entry.

  @retval EFI_SUCCESS         Get files from current dir successfully.
  @return Other value if can't get files from current dir.

**/
EFI_STATUS
BOpt_FindFiles (
  IN BMM_CALLBACK_DATA          *CallbackData,
  IN BM_MENU_ENTRY              *MenuEntry
  )
{
  EFI_FILE_HANDLE NewDir;
  EFI_FILE_HANDLE Dir;
  EFI_FILE_INFO   *DirInfo;
  UINTN           BufferSize;
  UINTN           DirBufferSize;
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_FILE_CONTEXT *FileContext;
  BM_FILE_CONTEXT *NewFileContext;
  UINTN           Pass;
  EFI_STATUS      Status;
  UINTN           OptionNumber;

  FileContext   = (BM_FILE_CONTEXT *) MenuEntry->VariableContext;
  Dir           = FileContext->FHandle;
  OptionNumber  = 0;
  //
  // Open current directory to get files from it
  //
  Status = Dir->Open (
                  Dir,
                  &NewDir,
                  FileContext->FileName,
                  EFI_FILE_READ_ONLY,
                  0
                  );
  if (!FileContext->IsRoot) {
    Dir->Close (Dir);
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DirInfo = EfiLibFileInfo (NewDir);
  if (DirInfo == NULL) {
    return EFI_NOT_FOUND;
  }

  if ((DirInfo->Attribute & EFI_FILE_DIRECTORY) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  FileContext->DevicePath = FileDevicePath (
                              FileContext->Handle,
                              FileContext->FileName
                              );

  DirBufferSize = sizeof (EFI_FILE_INFO) + 1024;
  DirInfo       = AllocateZeroPool (DirBufferSize);
  if (DirInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Get all files in current directory
  // Pass 1 to get Directories
  // Pass 2 to get files that are EFI images
  //
  for (Pass = 1; Pass <= 2; Pass++) {
    NewDir->SetPosition (NewDir, 0);
    for (;;) {
      BufferSize  = DirBufferSize;
      Status      = NewDir->Read (NewDir, &BufferSize, DirInfo);
      if (EFI_ERROR (Status) || BufferSize == 0) {
        break;
      }

      if (((DirInfo->Attribute & EFI_FILE_DIRECTORY) != 0 && Pass == 2) ||
          ((DirInfo->Attribute & EFI_FILE_DIRECTORY) == 0 && Pass == 1)
          ) {
        //
        // Pass 1 is for Directories
        // Pass 2 is for file names
        //
        continue;
      }

      if (!(BOpt_IsEfiImageName (DirInfo->FileName) || (DirInfo->Attribute & EFI_FILE_DIRECTORY) != 0)) {
        //
        // Slip file unless it is a directory entry or a .EFI file
        //
        continue;
      }

      NewMenuEntry = BOpt_CreateMenuEntry (BM_FILE_CONTEXT_SELECT);
      if (NULL == NewMenuEntry) {
        return EFI_OUT_OF_RESOURCES;
      }

      NewFileContext          = (BM_FILE_CONTEXT *) NewMenuEntry->VariableContext;
      NewFileContext->Handle  = FileContext->Handle;
      NewFileContext->FileName = BOpt_AppendFileName (
                                  FileContext->FileName,
                                  DirInfo->FileName
                                  );
      if (NewFileContext->FileName == NULL) {
        return EFI_UNSUPPORTED;
      }

      NewFileContext->FHandle = NewDir;
      NewFileContext->DevicePath = FileDevicePath (
                                    NewFileContext->Handle,
                                    NewFileContext->FileName
                                    );
      NewMenuEntry->HelpString = NULL;

      MenuEntry->DisplayStringToken = GetStringTokenFromDepository (
                                        CallbackData,
                                        FileOptionStrDepository
                                        );

      NewFileContext->IsDir = (BOOLEAN) ((DirInfo->Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY);

      if (NewFileContext->IsDir) {
        BufferSize                  = StrLen (DirInfo->FileName) * 2 + 6;
        NewMenuEntry->DisplayString = AllocateZeroPool (BufferSize);

        UnicodeSPrint (
          NewMenuEntry->DisplayString,
          BufferSize,
          L"<%s>",
          DirInfo->FileName
          );

      } else {
        NewMenuEntry->DisplayString = EfiStrDuplicate (DirInfo->FileName);
      }

      NewFileContext->IsRoot            = FALSE;
      NewFileContext->IsLoadFile        = FALSE;
      NewFileContext->IsRemovableMedia  = FALSE;

      NewMenuEntry->OptionNumber        = OptionNumber;
      OptionNumber++;
      InsertTailList (&DirectoryMenu.Head, &NewMenuEntry->Link);
    }
  }

  DirectoryMenu.MenuNumber = OptionNumber;
  FreePool (DirInfo);
  return EFI_SUCCESS;
}

/**
  Build the LegacyFDMenu LegacyHDMenu LegacyCDMenu according to LegacyBios.GetBbsInfo().

  @retval EFI_SUCCESS The function complete successfully.
  @retval EFI_OUT_OF_RESOURCES No enough memory to complete this function.

**/
EFI_STATUS
BOpt_GetLegacyOptions (
  VOID
  )
{
  BM_MENU_ENTRY                 *NewMenuEntry;
  BM_LEGACY_DEVICE_CONTEXT      *NewLegacyDevContext;
  EFI_BOOT_MANAGER_LOAD_OPTION  *BootOption;
  UINTN                         BootOptionCount;
  UINT16                        Index;
  UINTN                         FDNum;
  UINTN                         HDNum;
  UINTN                         CDNum;
  UINTN                         NETNum;
  UINTN                         BEVNum;
  //
  // Initialize Bbs Table Context from BBS info data
  //
  InitializeListHead (&LegacyFDMenu.Head);
  InitializeListHead (&LegacyHDMenu.Head);
  InitializeListHead (&LegacyCDMenu.Head);
  InitializeListHead (&LegacyNETMenu.Head);
  InitializeListHead (&LegacyBEVMenu.Head);

  FDNum   = 0;
  HDNum   = 0;
  CDNum   = 0;
  NETNum  = 0;
  BEVNum  = 0;

  BootOption = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);
  for (Index = 0; Index < BootOptionCount; Index++) {
    if ((DevicePathType (BootOption[Index].FilePath) != BBS_DEVICE_PATH) ||
        (DevicePathSubType (BootOption[Index].FilePath) != BBS_BBS_DP)
       ) {
      continue;
    }
    ASSERT (BootOption[Index].OptionalDataSize == sizeof (LEGACY_BOOT_OPTION_BBS_DATA));
    NewMenuEntry = BOpt_CreateMenuEntry (BM_LEGACY_DEV_CONTEXT_SELECT);
    ASSERT (NewMenuEntry != NULL);
    if (NewMenuEntry == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    NewLegacyDevContext              = (BM_LEGACY_DEVICE_CONTEXT *) NewMenuEntry->VariableContext;
    NewLegacyDevContext->BbsIndex    = ((LEGACY_BOOT_OPTION_BBS_DATA *) BootOption[Index].OptionalData)->BbsIndex;
    NewLegacyDevContext->Description = AllocateCopyPool (StrSize (BootOption[Index].Description), BootOption[Index].Description);
    ASSERT (NewLegacyDevContext->Description != NULL);

    NewMenuEntry->DisplayString = NewLegacyDevContext->Description;
    NewMenuEntry->HelpString    = NULL;

    switch (((BBS_BBS_DEVICE_PATH *) BootOption[Index].FilePath)->DeviceType) {
    case BBS_TYPE_FLOPPY:
      InsertTailList (&LegacyFDMenu.Head, &NewMenuEntry->Link);
      FDNum++;
      break;

    case BBS_TYPE_HARDDRIVE:
      InsertTailList (&LegacyHDMenu.Head, &NewMenuEntry->Link);
      HDNum++;
      break;

    case BBS_TYPE_CDROM:
      InsertTailList (&LegacyCDMenu.Head, &NewMenuEntry->Link);
      CDNum++;
      break;

    case BBS_TYPE_EMBEDDED_NETWORK:
      InsertTailList (&LegacyNETMenu.Head, &NewMenuEntry->Link);
      NETNum++;
      break;

    case BBS_TYPE_BEV:
      InsertTailList (&LegacyBEVMenu.Head, &NewMenuEntry->Link);
      BEVNum++;
      break;
    }
  }

  EfiBootManagerFreeLoadOptions (BootOption, BootOptionCount);

  LegacyFDMenu.MenuNumber   = FDNum;
  LegacyHDMenu.MenuNumber   = HDNum;
  LegacyCDMenu.MenuNumber   = CDNum;
  LegacyNETMenu.MenuNumber  = NETNum;
  LegacyBEVMenu.MenuNumber  = BEVNum;
  return EFI_SUCCESS;
}

/**
  Free out resouce allocated from Legacy Boot Options.

**/
VOID
BOpt_FreeLegacyOptions (
  VOID
  )
{
  BOpt_FreeMenu (&LegacyFDMenu);
  BOpt_FreeMenu (&LegacyHDMenu);
  BOpt_FreeMenu (&LegacyCDMenu);
  BOpt_FreeMenu (&LegacyNETMenu);
  BOpt_FreeMenu (&LegacyBEVMenu);
}

/**

  Build the BootOptionMenu according to BootOrder Variable.
  This Routine will access the Boot#### to get EFI_LOAD_OPTION.

  @param CallbackData The BMM context data.

  @return EFI_NOT_FOUND Fail to find "BootOrder" variable.
  @return EFI_SUCESS    Success build boot option menu.

**/
EFI_STATUS
BOpt_GetBootOptions (
  IN  BMM_CALLBACK_DATA         *CallbackData
  )
{
  UINTN                         Index;
  UINT16                        BootString[10];
  UINT8                         *LoadOptionFromVar;
  UINT8                         *LoadOption;
  UINTN                         BootOptionSize;
  BOOLEAN                       BootNextFlag;
  UINT16                        *BootOrderList;
  UINTN                         BootOrderListSize;
  UINT16                        *BootNext;
  UINTN                         BootNextSize;
  BM_MENU_ENTRY                 *NewMenuEntry;
  BM_LOAD_CONTEXT               *NewLoadContext;
  UINT8                         *LoadOptionPtr;
  UINTN                         StringSize;
  UINTN                         OptionalDataSize;
  UINT8                         *LoadOptionEnd;
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;
  UINTN                         MenuCount;
  UINT8                         *Ptr;
  EFI_BOOT_MANAGER_LOAD_OPTION  *BootOption;
  UINTN                         BootOptionCount;
  UINTN                         OptionIndex;
  UINTN                         DescriptionLen;

  MenuCount         = 0;
  BootOrderListSize = 0;
  BootNextSize      = 0;
  BootOrderList     = NULL;
  BootNext          = NULL;
  LoadOptionFromVar = NULL;
  DescriptionLen    = 0;
  BOpt_FreeMenu (&BootOptionMenu);
  InitializeListHead (&BootOptionMenu.Head);

  //
  // Get the BootOrder from the Var
  //
  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrderList, &BootOrderListSize);
  if (BootOrderList == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Get the BootNext from the Var
  //
  GetEfiGlobalVariable2 (L"BootNext", (VOID **) &BootNext, &BootNextSize);
  if (BootNext != NULL) {
    if (BootNextSize != sizeof (UINT16)) {
      FreePool (BootNext);
      BootNext = NULL;
    }
  }
  BootOption = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);
  for (Index = 0; Index < BootOrderListSize / sizeof (UINT16); Index++) {
    OptionIndex = (BootNext == NULL) ? Index : Index + 1;
    //
    // Don't display the hidden/inactive boot option
    //
    if (((BootOption[OptionIndex].Attributes & LOAD_OPTION_HIDDEN) != 0) || ((BootOption[OptionIndex].Attributes & LOAD_OPTION_ACTIVE) == 0)) {
      continue;
    }

    UnicodeSPrint (BootString, sizeof (BootString), L"Boot%04X", BootOrderList[Index]);
    //
    //  Get all loadoptions from the VAR
    //
    GetEfiGlobalVariable2 (BootString, (VOID **) &LoadOptionFromVar, &BootOptionSize);
    if (LoadOptionFromVar == NULL) {
      continue;
    }

    LoadOption = AllocateZeroPool (BootOptionSize);
    if (LoadOption == NULL) {
      continue;
    }

    CopyMem (LoadOption, LoadOptionFromVar, BootOptionSize);
    FreePool (LoadOptionFromVar);

    if (BootNext != NULL) {
      BootNextFlag = (BOOLEAN) (*BootNext == BootOrderList[Index]);
    } else {
      BootNextFlag = FALSE;
    }

    NewMenuEntry = BOpt_CreateMenuEntry (BM_LOAD_CONTEXT_SELECT);
    ASSERT (NULL != NewMenuEntry);
    if (NewMenuEntry == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    NewLoadContext                      = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;

    LoadOptionPtr                       = LoadOption;
    LoadOptionEnd                       = LoadOption + BootOptionSize;

    NewMenuEntry->OptionNumber          = BootOrderList[Index];
    NewLoadContext->LoadOptionModified  = FALSE;
    NewLoadContext->Deleted             = FALSE;
    NewLoadContext->IsBootNext          = BootNextFlag;

    //
    // Is a Legacy Device?
    //
    Ptr = (UINT8 *) LoadOption;

    //
    // Attribute = *(UINT32 *)Ptr;
    //
    Ptr += sizeof (UINT32);

    //
    // FilePathSize = *(UINT16 *)Ptr;
    //
    Ptr += sizeof (UINT16);

    //
    // Description = (CHAR16 *)Ptr;
    //
    Ptr += StrSize ((CHAR16 *) Ptr);

    //
    // Now Ptr point to Device Path
    //
    DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) Ptr;
    if ((BBS_DEVICE_PATH == DevicePath->Type) && (BBS_BBS_DP == DevicePath->SubType)) {
      NewLoadContext->IsLegacy = TRUE;
    } else {
      NewLoadContext->IsLegacy = FALSE;
    }
    //
    // LoadOption is a pointer type of UINT8
    // for easy use with following LOAD_OPTION
    // embedded in this struct
    //
    NewLoadContext->LoadOption      = LoadOption;
    NewLoadContext->LoadOptionSize  = BootOptionSize;

    NewLoadContext->Attributes      = *(UINT32 *) LoadOptionPtr;
    NewLoadContext->IsActive        = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_ACTIVE);

    NewLoadContext->ForceReconnect  = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_FORCE_RECONNECT);

    LoadOptionPtr += sizeof (UINT32);

    NewLoadContext->FilePathListLength = *(UINT16 *) LoadOptionPtr;
    LoadOptionPtr += sizeof (UINT16);

    StringSize = StrSize((UINT16*)LoadOptionPtr);

    NewLoadContext->Description = AllocateZeroPool (StrSize((UINT16*)LoadOptionPtr) + 2);
    DescriptionLen = (StrSize((UINT16*)LoadOptionPtr) + 2) / sizeof (CHAR16);
    ASSERT (NewLoadContext->Description != NULL);
    if (NewLoadContext->Description == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    StrCpyS (NewLoadContext->Description, DescriptionLen, (UINT16*) LoadOptionPtr);

    ASSERT (NewLoadContext->Description != NULL);
    NewMenuEntry->DisplayString = NewLoadContext->Description;

    LoadOptionPtr += StringSize;

    NewLoadContext->FilePathList = AllocateZeroPool (NewLoadContext->FilePathListLength);
    ASSERT (NewLoadContext->FilePathList != NULL);
    CopyMem (
      NewLoadContext->FilePathList,
      (EFI_DEVICE_PATH_PROTOCOL *) LoadOptionPtr,
      NewLoadContext->FilePathListLength
      );

    NewMenuEntry->HelpString = UiDevicePathToStr (NewLoadContext->FilePathList);
    NewMenuEntry->DisplayStringToken = GetStringTokenFromDepository (
                                        CallbackData,
                                        BootOptionStrDepository
                                        );
    NewMenuEntry->HelpStringToken = GetStringTokenFromDepository (
                                      CallbackData,
                                      BootOptionHelpStrDepository
                                      );
    LoadOptionPtr += NewLoadContext->FilePathListLength;

    if (LoadOptionPtr < LoadOptionEnd) {
      OptionalDataSize = BootOptionSize -
        sizeof (UINT32) -
        sizeof (UINT16) -
        StringSize -
        NewLoadContext->FilePathListLength;

      NewLoadContext->OptionalData = AllocateZeroPool (OptionalDataSize);
      ASSERT (NewLoadContext->OptionalData != NULL);
      CopyMem (
        NewLoadContext->OptionalData,
        LoadOptionPtr,
        OptionalDataSize
        );

      NewLoadContext->OptionalDataSize = OptionalDataSize;
    }

    InsertTailList (&BootOptionMenu.Head, &NewMenuEntry->Link);
    MenuCount++;
  }
  EfiBootManagerFreeLoadOptions (BootOption, BootOptionCount);

  if (BootNext != NULL) {
    FreePool (BootNext);
  }
  if (BootOrderList != NULL) {
    FreePool (BootOrderList);
  }
  BootOptionMenu.MenuNumber = MenuCount;
  return EFI_SUCCESS;
}

/**

  Append file name to existing file name.

  @param Str1  The existing file name
  @param Str2  The file name to be appended

  @return Allocate a new string to hold the appended result.
          Caller is responsible to free the returned string.

**/
CHAR16 *
BOpt_AppendFileName (
  IN  CHAR16  *Str1,
  IN  CHAR16  *Str2
  )
{
  UINTN   Size1;
  UINTN   Size2;
  CHAR16  *Str;
  CHAR16  *TmpStr;
  CHAR16  *Ptr;
  CHAR16  *LastSlash;

  Size1 = StrSize (Str1);
  Size2 = StrSize (Str2);
  Str   = AllocateZeroPool (Size1 + Size2 + sizeof (CHAR16));
  ASSERT (Str != NULL);
  if (Str == NULL) {
    return NULL;
  }

  TmpStr = AllocateZeroPool (Size1 + Size2 + sizeof (CHAR16));
  ASSERT (TmpStr != NULL);
  if (TmpStr == NULL) {
    FreePool(Str);
    return NULL;
  }

  StrCatS (Str, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), Str1);
  if (!((*Str == '\\') && (*(Str + 1) == 0))) {
    StrCatS (Str, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), L"\\");
  }

  StrCatS (Str, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), Str2);

  Ptr       = Str;
  LastSlash = Str;
  while (*Ptr != 0) {
    if (*Ptr == '\\' && *(Ptr + 1) == '.' && *(Ptr + 2) == '.' && *(Ptr + 3) == L'\\') {
      //
      // Convert "\Name\..\" to "\"
      // DO NOT convert the .. if it is at the end of the string. This will
      // break the .. behavior in changing directories.
      //

      //
      // Use TmpStr as a backup, as StrCpyS in BaseLib does not handle copy of two strings
      // that overlap.
      //
      StrCpyS (TmpStr, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), Ptr + 3);
      StrCpyS (LastSlash, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), TmpStr);
      Ptr = LastSlash;
    } else if (*Ptr == '\\' && *(Ptr + 1) == '.' && *(Ptr + 2) == '\\') {
      //
      // Convert a "\.\" to a "\"
      //

      //
      // Use TmpStr as a backup, as StrCpyS in BaseLib does not handle copy of two strings
      // that overlap.
      //
      StrCpyS (TmpStr, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), Ptr + 2);
      StrCpyS (Ptr, (Size1 + Size2 + sizeof (CHAR16)) / sizeof (CHAR16), TmpStr);
      Ptr = LastSlash;
    } else if (*Ptr == '\\') {
      LastSlash = Ptr;
    }

    Ptr++;
  }

  FreePool (TmpStr);

  return Str;
}

/**

  Check whether current FileName point to a valid
  Efi Image File.

  @param FileName  File need to be checked.

  @retval TRUE  Is Efi Image
  @retval FALSE Not a valid Efi Image

**/
BOOLEAN
BOpt_IsEfiImageName (
  IN UINT16  *FileName
  )
{
  //
  // Search for ".efi" extension
  //
  while (*FileName != L'\0') {
    if (FileName[0] == '.') {
      if (FileName[1] == 'e' || FileName[1] == 'E') {
        if (FileName[2] == 'f' || FileName[2] == 'F') {
          if (FileName[3] == 'i' || FileName[3] == 'I') {
            return TRUE;
          } else if (FileName[3] == 0x0000) {
            return FALSE;
          }
        } else if (FileName[2] == 0x0000) {
          return FALSE;
        }
      } else if (FileName[1] == 0x0000) {
        return FALSE;
      }
    }

    FileName += 1;
  }

  return FALSE;
}

/**

  Check whether current FileName point to a valid Efi Application

  @param Dir       Pointer to current Directory
  @param FileName  Pointer to current File name.

  @retval TRUE      Is a valid Efi Application
  @retval FALSE     not a valid Efi Application

**/
BOOLEAN
BOpt_IsEfiApp (
  IN EFI_FILE_HANDLE Dir,
  IN UINT16          *FileName
  )
{
  UINTN                       BufferSize;
  EFI_IMAGE_DOS_HEADER        DosHdr;
  UINT16                      Subsystem;
  EFI_FILE_HANDLE             File;
  EFI_STATUS                  Status;
  EFI_IMAGE_OPTIONAL_HEADER_UNION PeHdr;

  Status = Dir->Open (Dir, &File, FileName, EFI_FILE_MODE_READ, 0);

  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  BufferSize = sizeof (EFI_IMAGE_DOS_HEADER);
  File->Read (File, &BufferSize, &DosHdr);
  if (DosHdr.e_magic != EFI_IMAGE_DOS_SIGNATURE) {
    File->Close (File);
    return FALSE;
  }

  File->SetPosition (File, DosHdr.e_lfanew);
  BufferSize = sizeof (EFI_IMAGE_OPTIONAL_HEADER_UNION);
  File->Read (File, &BufferSize, &PeHdr);
  if (PeHdr.Pe32.Signature != EFI_IMAGE_NT_SIGNATURE) {
    File->Close (File);
    return FALSE;
  }
  //
  // Determine PE type and read subsytem
  //
  if (PeHdr.Pe32.OptionalHeader.Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    Subsystem = PeHdr.Pe32.OptionalHeader.Subsystem;
  } else if (PeHdr.Pe32.OptionalHeader.Magic == EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
    Subsystem = PeHdr.Pe32Plus.OptionalHeader.Subsystem;
  } else {
    return FALSE;
  }

  if (Subsystem == EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION) {
    File->Close (File);
    return TRUE;
  } else {
    File->Close (File);
    return FALSE;
  }
}

/**

  Find drivers that will be added as Driver#### variables from handles
  in current system environment
  All valid handles in the system except those consume SimpleFs, LoadFile
  are stored in DriverMenu for future use.

  @retval EFI_SUCCESS The function complets successfully.
  @return Other value if failed to build the DriverMenu.

**/
EFI_STATUS
BOpt_FindDrivers (
  VOID
  )
{
  UINTN                           NoDevicePathHandles;
  EFI_HANDLE                      *DevicePathHandle;
  UINTN                           Index;
  EFI_STATUS                      Status;
  BM_MENU_ENTRY                   *NewMenuEntry;
  BM_HANDLE_CONTEXT               *NewHandleContext;
  EFI_HANDLE                      CurHandle;
  UINTN                           OptionNumber;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFs;
  EFI_LOAD_FILE_PROTOCOL          *LoadFile;

  SimpleFs  = NULL;
  LoadFile  = NULL;

  InitializeListHead (&DriverMenu.Head);

  //
  // At first, get all handles that support Device Path
  // protocol which is the basic requirement for
  // Driver####
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiDevicePathProtocolGuid,
                  NULL,
                  &NoDevicePathHandles,
                  &DevicePathHandle
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  OptionNumber = 0;
  for (Index = 0; Index < NoDevicePathHandles; Index++) {
    CurHandle = DevicePathHandle[Index];

    Status = gBS->HandleProtocol (
                    CurHandle,
                    &gEfiSimpleFileSystemProtocolGuid,
                    (VOID **) &SimpleFs
                    );
    if (Status == EFI_SUCCESS) {
      continue;
    }

    Status = gBS->HandleProtocol (
                    CurHandle,
                    &gEfiLoadFileProtocolGuid,
                    (VOID **) &LoadFile
                    );
    if (Status == EFI_SUCCESS) {
      continue;
    }

    NewMenuEntry = BOpt_CreateMenuEntry (BM_HANDLE_CONTEXT_SELECT);
    if (NULL == NewMenuEntry) {
      FreePool (DevicePathHandle);
      return EFI_OUT_OF_RESOURCES;
    }

    NewHandleContext              = (BM_HANDLE_CONTEXT *) NewMenuEntry->VariableContext;
    NewHandleContext->Handle      = CurHandle;
    NewHandleContext->DevicePath  = DevicePathFromHandle (CurHandle);
    NewMenuEntry->DisplayString = UiDevicePathToStr (NewHandleContext->DevicePath);
    NewMenuEntry->HelpString    = NULL;
    NewMenuEntry->OptionNumber  = OptionNumber;
    OptionNumber++;
    InsertTailList (&DriverMenu.Head, &NewMenuEntry->Link);

  }

  if (DevicePathHandle != NULL) {
    FreePool (DevicePathHandle);
  }

  DriverMenu.MenuNumber = OptionNumber;
  return EFI_SUCCESS;
}

/**

  Get the Option Number that has not been allocated for use.

  @param Type  The type of Option.

  @return The available Option Number.

**/
UINT16
BOpt_GetOptionNumber (
  CHAR16        *Type
  )
{
  UINT16        *OrderList;
  UINTN         OrderListSize;
  UINTN         Index;
  CHAR16        StrTemp[20];
  UINT16        *OptionBuffer;
  UINT16        OptionNumber;
  UINTN         OptionSize;

  OrderListSize = 0;
  OrderList     = NULL;
  OptionBuffer  = NULL;
  OptionNumber  = 0;
  Index         = 0;

  UnicodeSPrint (StrTemp, sizeof (StrTemp), L"%sOrder", Type);

  GetEfiGlobalVariable2 (StrTemp, (VOID **) &OrderList, &OrderListSize);
  do {
    if (OrderList != NULL) {
      for (Index = 0; Index < OrderListSize / sizeof (UINT16); Index++) {
        if (OptionNumber == OrderList[Index]) {
          break;
        }
      }
    }

    if (Index < OrderListSize / sizeof (UINT16)) {
      //
      // The OptionNumber occurs in the OrderList, continue to use next one
      //
      continue;
    }
    UnicodeSPrint (StrTemp, sizeof (StrTemp), L"%s%04X", Type, (UINTN) OptionNumber);
    DEBUG((DEBUG_INFO,"Option = %s\n", StrTemp));
    GetEfiGlobalVariable2 (StrTemp, (VOID **) &OptionBuffer, &OptionSize);
    if (NULL == OptionBuffer) {
      //
      // The Boot[OptionNumber] / Driver[OptionNumber] NOT occurs, we found it
      //
      break;
    }
    OptionNumber++;
  } while (OptionBuffer != NULL);

  return OptionNumber;
}

/**

  Get the Option Number for Boot#### that does not used.

  @return The available Option Number.

**/
UINT16
BOpt_GetBootOptionNumber (
  VOID
  )
{
  return BOpt_GetOptionNumber (L"Boot");
}

/**

  Get the Option Number for Driver#### that does not used.

  @return The unused Option Number.

**/
UINT16
BOpt_GetDriverOptionNumber (
  VOID
  )
{
  return BOpt_GetOptionNumber (L"Driver");
}

/**

  Build up all DriverOptionMenu

  @param CallbackData The BMM context data.

  @retval EFI_SUCESS           The functin completes successfully.
  @retval EFI_OUT_OF_RESOURCES Not enough memory to compete the operation.
  @retval EFI_NOT_FOUND        Fail to get "DriverOrder" variable.

**/
EFI_STATUS
BOpt_GetDriverOptions (
  IN  BMM_CALLBACK_DATA         *CallbackData
  )
{
  UINTN           Index;
  UINT16          DriverString[12];
  UINT8           *LoadOptionFromVar;
  UINT8           *LoadOption;
  UINTN           DriverOptionSize;

  UINT16          *DriverOrderList;
  UINTN           DriverOrderListSize;
  BM_MENU_ENTRY   *NewMenuEntry;
  BM_LOAD_CONTEXT *NewLoadContext;
  UINT8           *LoadOptionPtr;
  UINTN           StringSize;
  UINTN           OptionalDataSize;
  UINT8           *LoadOptionEnd;

  DriverOrderListSize = 0;
  DriverOrderList     = NULL;
  DriverOptionSize    = 0;
  LoadOptionFromVar   = NULL;
  BOpt_FreeMenu (&DriverOptionMenu);
  InitializeListHead (&DriverOptionMenu.Head);
  //
  // Get the DriverOrder from the Var
  //
  GetEfiGlobalVariable2 (L"DriverOrder", (VOID **) &DriverOrderList, &DriverOrderListSize);
  if (DriverOrderList == NULL) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < DriverOrderListSize / sizeof (UINT16); Index++) {
    UnicodeSPrint (
      DriverString,
      sizeof (DriverString),
      L"Driver%04X",
      DriverOrderList[Index]
      );
    //
    //  Get all loadoptions from the VAR
    //
    GetEfiGlobalVariable2 (DriverString, (VOID **) &LoadOptionFromVar, &DriverOptionSize);
    if (LoadOptionFromVar == NULL) {
      continue;
    }

    LoadOption = AllocateZeroPool (DriverOptionSize);
    if (LoadOption == NULL) {
      continue;
    }

    CopyMem (LoadOption, LoadOptionFromVar, DriverOptionSize);
    FreePool (LoadOptionFromVar);

    NewMenuEntry = BOpt_CreateMenuEntry (BM_LOAD_CONTEXT_SELECT);
    if (NULL == NewMenuEntry) {
      return EFI_OUT_OF_RESOURCES;
    }

    NewLoadContext                      = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;
    LoadOptionPtr                       = LoadOption;
    LoadOptionEnd                       = LoadOption + DriverOptionSize;
    NewMenuEntry->OptionNumber          = DriverOrderList[Index];
    NewLoadContext->LoadOptionModified  = FALSE;
    NewLoadContext->Deleted             = FALSE;
    NewLoadContext->IsLegacy            = FALSE;

    //
    // LoadOption is a pointer type of UINT8
    // for easy use with following LOAD_OPTION
    // embedded in this struct
    //
    NewLoadContext->LoadOption      = LoadOption;
    NewLoadContext->LoadOptionSize  = DriverOptionSize;

    NewLoadContext->Attributes      = *(UINT32 *) LoadOptionPtr;
    NewLoadContext->IsActive        = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_ACTIVE);

    NewLoadContext->ForceReconnect  = (BOOLEAN) (NewLoadContext->Attributes & LOAD_OPTION_FORCE_RECONNECT);

    LoadOptionPtr += sizeof (UINT32);

    NewLoadContext->FilePathListLength = *(UINT16 *) LoadOptionPtr;
    LoadOptionPtr += sizeof (UINT16);

    StringSize                  = StrSize ((UINT16 *) LoadOptionPtr);
    NewLoadContext->Description = AllocateZeroPool (StringSize);
    ASSERT (NewLoadContext->Description != NULL);
    CopyMem (
      NewLoadContext->Description,
      (UINT16 *) LoadOptionPtr,
      StringSize
      );
    NewMenuEntry->DisplayString = NewLoadContext->Description;

    LoadOptionPtr += StringSize;

    NewLoadContext->FilePathList = AllocateZeroPool (NewLoadContext->FilePathListLength);
    ASSERT (NewLoadContext->FilePathList != NULL);
    CopyMem (
      NewLoadContext->FilePathList,
      (EFI_DEVICE_PATH_PROTOCOL *) LoadOptionPtr,
      NewLoadContext->FilePathListLength
      );

    NewMenuEntry->HelpString = UiDevicePathToStr (NewLoadContext->FilePathList);
    NewMenuEntry->DisplayStringToken = GetStringTokenFromDepository (
                                        CallbackData,
                                        DriverOptionStrDepository
                                        );
    NewMenuEntry->HelpStringToken = GetStringTokenFromDepository (
                                      CallbackData,
                                      DriverOptionHelpStrDepository
                                      );
    LoadOptionPtr += NewLoadContext->FilePathListLength;

    if (LoadOptionPtr < LoadOptionEnd) {
      OptionalDataSize = DriverOptionSize -
        sizeof (UINT32) -
        sizeof (UINT16) -
        StringSize -
        NewLoadContext->FilePathListLength;

      NewLoadContext->OptionalData = AllocateZeroPool (OptionalDataSize);
      ASSERT (NewLoadContext->OptionalData != NULL);
      CopyMem (
        NewLoadContext->OptionalData,
        LoadOptionPtr,
        OptionalDataSize
        );

      NewLoadContext->OptionalDataSize = OptionalDataSize;
    }

    InsertTailList (&DriverOptionMenu.Head, &NewMenuEntry->Link);

  }

  if (DriverOrderList != NULL) {
    FreePool (DriverOrderList);
  }
  DriverOptionMenu.MenuNumber = Index;
  return EFI_SUCCESS;

}

/**
  Get option number according to Boot#### and BootOrder variable.
  The value is saved as #### + 1.

  @param CallbackData    The BMM context data.
**/
VOID
GetBootOrder (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  BMM_FAKE_NV_DATA          *BmmConfig;
  UINT16                    Index;
  UINT16                    OptionOrderIndex;
  BM_MENU_ENTRY             *NewMenuEntry;

  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) {
    return;
  }

  BmmConfig  = &CallbackData->BmmFakeNvData;
  ZeroMem (BmmConfig->BootOptionOrder, sizeof (BmmConfig->BootOptionOrder));

  for (Index = 0, OptionOrderIndex = 0; ((Index < BootOptionMenu.MenuNumber) &&
       (OptionOrderIndex < (sizeof (BmmConfig->BootOptionOrder) / sizeof (BmmConfig->BootOptionOrder[0]))));
       Index++) {
    NewMenuEntry   = BOpt_GetMenuEntry (&BootOptionMenu, Index);

    BmmConfig->BootOptionOrder[OptionOrderIndex++] = (UINT32) (NewMenuEntry->OptionNumber + 1);
  }
}


/**
  Get driver option order from globalc DriverOptionMenu.

  @param CallbackData    The BMM context data.

**/
VOID
GetDriverOrder (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  BMM_FAKE_NV_DATA          *BmmConfig;
  UINT16                    Index;
  UINT16                    OptionOrderIndex;
  UINTN                     DeviceType;
  BM_MENU_ENTRY             *NewMenuEntry;
  BM_LOAD_CONTEXT           *NewLoadContext;


  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) return;

  DeviceType = (UINTN) -1;
  BmmConfig  = &CallbackData->BmmFakeNvData;
  if (BmmConfig == NULL) return;

  ZeroMem (BmmConfig->DriverOptionOrder, sizeof (BmmConfig->DriverOptionOrder));

  for (Index = 0, OptionOrderIndex = 0; ((Index < DriverOptionMenu.MenuNumber) &&
       (OptionOrderIndex < (sizeof (BmmConfig->DriverOptionOrder) / sizeof (BmmConfig->DriverOptionOrder[0]))));
       Index++) {
    NewMenuEntry   = BOpt_GetMenuEntry (&DriverOptionMenu, Index);
    NewLoadContext = (BM_LOAD_CONTEXT *) NewMenuEntry->VariableContext;

    if (NewLoadContext->IsLegacy) {
      if (((BBS_BBS_DEVICE_PATH *) NewLoadContext->FilePathList)->DeviceType != DeviceType) {
        DeviceType = ((BBS_BBS_DEVICE_PATH *) NewLoadContext->FilePathList)->DeviceType;
      } else {
        //
        // Only show one legacy boot option for the same device type
        // assuming the boot options are grouped by the device type
        //
        continue;
      }
    }

    BmmConfig->DriverOptionOrder[OptionOrderIndex++] = (UINT32) (NewMenuEntry->OptionNumber + 1);
  }
}

