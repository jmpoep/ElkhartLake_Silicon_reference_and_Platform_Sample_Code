/** @file
  Driver for Platform Boot Options support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

#include "BdsPlatform.h"
#include "AmtSupport.h"
#include "FastBootSupport.h"
#include "String.h"

#include "PlatformBoardId.h"
#include <Library/GpioLib.h>
#include <Library/PcdLib.h>
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Guid/SysFwUpdateProgress.h>
#include <Library/HobLib.h>
#endif
#include <Library/BootMediaLib.h>

BOOLEAN    mContinueBoot  = FALSE;
BOOLEAN    mBootMenuBoot  = FALSE;
BOOLEAN    mPxeBoot       = FALSE;
BOOLEAN    mAnyKeypressed = FALSE;
BOOLEAN    mHotKeypressed = FALSE;
EFI_EVENT  HotKeyEvent    = NULL;
UINTN      mBootMenuOptionNumber;
BOOLEAN    mDecompressFvUefiBoot = FALSE;


EFI_DEVICE_PATH_PROTOCOL *
BdsCreateShellDevicePath (
  VOID
  )
/*++

Routine Description:

  This function will create a SHELL BootOption to boot.

Arguments:

  None.

Returns:

  Shell Device path for booting.

--*/
{
  UINTN                             FvHandleCount;
  EFI_HANDLE                        *FvHandleBuffer;
  UINTN                             Index;
  EFI_STATUS                        Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL     *Fv;
  UINTN                             Size;
  UINT32                            AuthenticationStatus;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  VOID                              *Buffer;

  DevicePath  = NULL;
  Status      = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "BdsCreateShellDevicePath\n"));
  gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiFirmwareVolume2ProtocolGuid,
        NULL,
        &FvHandleCount,
        &FvHandleBuffer
        );

  for (Index = 0; Index < FvHandleCount; Index++) {
    gBS->HandleProtocol (
          FvHandleBuffer[Index],
          &gEfiFirmwareVolume2ProtocolGuid,
          (VOID **) &Fv
          );

    Buffer  = NULL;
    Size    = 0;
    Status  = Fv->ReadSection (
                    Fv,
                    PcdGetPtr(PcdShellFile),
                    EFI_SECTION_PE32,
                    0,
                    &Buffer,
                    &Size,
                    &AuthenticationStatus
                    );
    if (EFI_ERROR (Status)) {
      //
      // Skip if no shell file in the FV
      //
      continue;
    } else {
      //
      // Found the shell
      //
      break;
    }
  }

  if (EFI_ERROR (Status)) {
    //
    // No shell present
    //
    if (FvHandleCount) {
      FreePool (FvHandleBuffer);
    }
    return NULL;
  }
  //
  // Build the shell boot option
  //
  DevicePath = DevicePathFromHandle (FvHandleBuffer[Index]);

  if (FvHandleCount) {
    FreePool (FvHandleBuffer);
  }

  return DevicePath;
}

VOID
ChangeFirstBootDeviceToShell (
  VOID
  );

EFI_STATUS
CreateFvBootOption (
  EFI_GUID                     *FileGuid,
  CHAR16                       *Description,
  EFI_BOOT_MANAGER_LOAD_OPTION *BootOption,
  UINT32                       Attributes,
  UINT8                        *OptionalData,    OPTIONAL
  UINT32                       OptionalDataSize
  )
{
  EFI_STATUS                         Status;
  EFI_DEVICE_PATH_PROTOCOL           *DevicePath;
  EFI_LOADED_IMAGE_PROTOCOL          *LoadedImage;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH  FileNode;
  EFI_FIRMWARE_VOLUME2_PROTOCOL      *Fv;
  UINT32                             AuthenticationStatus;
  VOID                               *Buffer;
  UINTN                              Size;

  if ((BootOption == NULL) || (FileGuid == NULL) || (Description == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  EfiInitializeFwVolDevicepathNode (&FileNode, FileGuid);

  if (!CompareGuid (PcdGetPtr (PcdShellFile), FileGuid)) {
    Status = gBS->HandleProtocol (
                    gImageHandle,
                    &gEfiLoadedImageProtocolGuid,
                    (VOID **) &LoadedImage
                    );
    if (!EFI_ERROR (Status)) {
      Status = gBS->HandleProtocol (
                      LoadedImage->DeviceHandle,
                      &gEfiFirmwareVolume2ProtocolGuid,
                      (VOID **) &Fv
                      );
      if (!EFI_ERROR (Status)) {
        Buffer  = NULL;
        Size    = 0;
        Status  = Fv->ReadSection (
                        Fv,
                        FileGuid,
                        EFI_SECTION_PE32,
                        0,
                        &Buffer,
                        &Size,
                        &AuthenticationStatus
                        );
        if (Buffer != NULL) {
          FreePool (Buffer);
        }
      }
    }
    if (EFI_ERROR (Status)) {
      return EFI_NOT_FOUND;
    }

    DevicePath = AppendDevicePathNode (
                   DevicePathFromHandle (LoadedImage->DeviceHandle),
                   (EFI_DEVICE_PATH_PROTOCOL *) &FileNode
                   );
  } else {
    DevicePath = AppendDevicePathNode (
                   BdsCreateShellDevicePath (),
                   (EFI_DEVICE_PATH_PROTOCOL *) &FileNode
                   );
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
PlatformFindLoadOption (
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

UINTN
RegisterFvBootOption (
  EFI_GUID                         *FileGuid,
  CHAR16                           *Description,
  UINTN                            Position,
  UINT32                           Attributes,
  UINT8                            *OptionalData,    OPTIONAL
  UINT32                           OptionalDataSize
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

    OptionIndex = PlatformFindLoadOption (&NewOption, BootOptions, BootOptionCount);

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

VOID
BootUi (
  VOID
  )
{
  EFI_STATUS                   Status;
  EFI_BOOT_MANAGER_LOAD_OPTION BootOption;

  Status = EfiBootManagerGetBootManagerMenu (&BootOption);
  if (!EFI_ERROR (Status)) {
    EfiBootManagerBoot (&BootOption);
    EfiBootManagerFreeLoadOption (&BootOption);
  }
}

VOID
EFIAPI
PlatformBootManagerWaitCallback (
  UINT16          TimeoutRemain
  )
{
  CHAR16                        *TmpStr;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Foreground;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Background;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
  UINT16                        Timeout;
  EFI_STATUS                    Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *TxtInEx;
  EFI_KEY_DATA                  KeyData;
  BOOLEAN                       PausePressed;

  Timeout = PcdGet16 (PcdPlatformBootTimeOut);
  if (GetDisplayBootMode () == NORMAL_BOOT) {
    //
    // Show progress
    //
    SetMem (&Foreground, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0xff);
    SetMem (&Background, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0x0);
    SetMem (&Color,      sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0xff);

    TmpStr = GetStringById (STRING_TOKEN (STR_START_BOOT_OPTION));
    if (TmpStr != NULL) {
      ShowProgress (
        Foreground,
        Background,
        TmpStr,
        Color,
        (Timeout - TimeoutRemain) * 100 / Timeout,
        0
        );
      FreePool (TmpStr);
    }
  }

  //
  // Pause on PAUSE key
  //
  Status = gBS->HandleProtocol (gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid, (VOID **) &TxtInEx);
  ASSERT_EFI_ERROR (Status);

  PausePressed = FALSE;

  while (TRUE) {
    Status = TxtInEx->ReadKeyStrokeEx (TxtInEx, &KeyData);
    if (EFI_ERROR (Status)) {
      break;
    }

    if (KeyData.Key.ScanCode == SCAN_PAUSE) {
      PausePressed = TRUE;
      break;
    }
  }

  //
  // Loop until non-PAUSE key pressed
  //
  while (PausePressed) {
    Status = TxtInEx->ReadKeyStrokeEx (TxtInEx, &KeyData);
    if (!EFI_ERROR (Status)) {
      DEBUG ((
        DEBUG_INFO, "[PauseCallback] %x/%x %x/%x\n",
        KeyData.Key.ScanCode, KeyData.Key.UnicodeChar,
        KeyData.KeyState.KeyShiftState, KeyData.KeyState.KeyToggleState
        ));
      PausePressed = (BOOLEAN) (KeyData.Key.ScanCode == SCAN_PAUSE);
    }
  }
}

/**
  Check if the boot option is a legacy PXE boot option.

  @param  Option         The boot option need to be processed.

  @retval TRUE           It is a legacy PXE boot option.
  @retval FALSE          It is not a legacy PXE boot option.

**/
BOOLEAN
IsLegacyPxeBootOption (
  IN  EFI_BOOT_MANAGER_LOAD_OPTION     *Option
  )
{
  if (DevicePathType (Option->FilePath) == BBS_DEVICE_PATH &&
      DevicePathSubType (Option->FilePath) == BBS_BBS_DP) {
    if (((BBS_BBS_DEVICE_PATH *) Option->FilePath)->DeviceType == BBS_TYPE_EMBEDDED_NETWORK) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Check if the boot option is a EFI network boot option.

  @param  Option         The boot option need to be processed.

  @retval TRUE           It is a EFI network boot option.
  @retval FALSE          It is not a EFI network boot option.

**/
BOOLEAN
IsEfiNetWorkBootOption (
  IN  EFI_BOOT_MANAGER_LOAD_OPTION     *Option
  )
{
  EFI_DEVICE_PATH_PROTOCOL   *Node;

  for (Node = Option->FilePath; !IsDevicePathEndType (Node); Node = NextDevicePathNode (Node)) {
    if (DevicePathType (Node) == MESSAGING_DEVICE_PATH) {
      switch (DevicePathSubType (Node)) {
      case MSG_MAC_ADDR_DP:
      case MSG_VLAN_DP:
      case MSG_IPv4_DP:
      case MSG_IPv6_DP:
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
  This funciton uses to get first PXE boot option from boot option list.
  The caller is responsible for free the data in the found option.
**/
EFI_STATUS
GetPxeOption (
  UINT16                           *OptionNumber
  )
{
  UINTN                            Index;
  UINTN                            BootOptionCount;
  EFI_BOOT_MANAGER_LOAD_OPTION     *BootOption;

  ASSERT (OptionNumber != NULL);
  if (OptionNumber == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Search PXE device
  //
  BootOption = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);
  for (Index = 0; Index < BootOptionCount; Index++) {
    if (IsLegacyPxeBootOption (&BootOption[Index]) || IsEfiNetWorkBootOption (&BootOption[Index])) {
      *OptionNumber = (UINT16) BootOption[Index].OptionNumber;
      break;
    }
  }
  EfiBootManagerFreeLoadOptions (BootOption, BootOptionCount);

  return (Index == BootOptionCount) ? EFI_NOT_FOUND : EFI_SUCCESS;
}

#define INTERNAL_EDK_SHELL_NAME       L"Internal EDK Shell"
#define INTERNAL_UEFI_SHELL_NAME      L"Internal UEFI Shell 2.0"
#define UEFI_HARD_DRIVE_NAME          L"UEFI Hard Drive"
#define FFU_LOADER_NAME               L"FFU Loader"
#define EMMC_HARD_DRIVE_NAME          L"UEFI eMMC Device"
#define EMMC_HARD_DRIVE_NAME2         L"UEFI eMMC Device 2"
#define EMMC_HARD_DRIVE_NAME3         L"UEFI eMMC Device 3"

VOID
RegisterDefaultBootOption (
  VOID
  )
{
  EFI_LOADED_IMAGE_PROTOCOL          *LoadedImage;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH  FileNode;
  VOID                               *BootState;
  UINT16                             *ShellData;
  UINT32                             ShellDataSize;

  //
  // Check BootState variable, NULL means it's the first boot after reflashing
  //
  GetVariable2 (L"BootState", &gBootStateGuid, &BootState, NULL);

  //
  // Shell
  //
  if (BootState == NULL) {
    ShellData = NULL;
    ShellDataSize = 0;
    RegisterFvBootOption (&gUefiShellFileGuid,      INTERNAL_UEFI_SHELL_NAME, (UINTN) -1, LOAD_OPTION_ACTIVE, (UINT8 *)ShellData, ShellDataSize);
    if (PcdGetBool(PcdUefiShellEnable)) {
      RegisterFvBootOption (PcdGetPtr (PcdShellFile), INTERNAL_EDK_SHELL_NAME,  (UINTN) -1, LOAD_OPTION_ACTIVE, (UINT8 *)ShellData, ShellDataSize);
    }
    //
    // FV UefiBoot has been decompessed by Dxe driver.
    //
     mDecompressFvUefiBoot = TRUE;
  }
  //
  // FFU Loader boot option
  //
  if (mSystemConfiguration.UsbFnEnable && BootMediaIsUfs ()) {
    RegisterFvBootOption (PcdGetPtr(PcdFfuLoaderFile), FFU_LOADER_NAME, (UINTN)-1, LOAD_OPTION_ACTIVE, NULL, 0);
  }
  //
  // Boot Menu
  //
  mBootMenuOptionNumber = RegisterFvBootOption (&gBootMenuFileGuid, L"Boot Device List",   (UINTN) -1, LOAD_OPTION_CATEGORY_APP | LOAD_OPTION_ACTIVE | LOAD_OPTION_HIDDEN, NULL, 0);

  if (mBootMenuOptionNumber == LoadOptionNumberUnassigned) {
    DEBUG ((DEBUG_INFO, "BootMenuOptionNumber (%d) should not be same to LoadOptionNumberUnassigned(%d).\n", mBootMenuOptionNumber, LoadOptionNumberUnassigned));
  }

  //
  // Boot Manager Menu
  //
  EfiInitializeFwVolDevicepathNode (&FileNode, &gUiFileGuid);

  gBS->HandleProtocol (
         gImageHandle,
         &gEfiLoadedImageProtocolGuid,
         (VOID **) &LoadedImage
         );
  AppendDevicePathNode (DevicePathFromHandle (LoadedImage->DeviceHandle), (EFI_DEVICE_PATH_PROTOCOL *) &FileNode);

  if (BootState != NULL) {
    FreePool (BootState);
  }
}

VOID
RegisterBootOptionHotkey (
  UINT16                       OptionNumber,
  EFI_INPUT_KEY                *Key,
  BOOLEAN                      Add
  )
{
  EFI_STATUS                   Status;

  if (!Add) {
    //
    // No enter hotkey when force to setup or there is no boot option
    //
    Status = EfiBootManagerDeleteKeyOptionVariable (NULL, 0, Key, NULL);
    ASSERT (Status == EFI_SUCCESS || Status == EFI_NOT_FOUND);
  } else {
    //
    // Register enter hotkey for the first boot option
    //
    Status = EfiBootManagerAddKeyOptionVariable (NULL, OptionNumber, 0, Key,NULL);
   if (BootMediaIsSpi ()) {
     // BFX boot: Need to debug this assert being hit in UEFI variable emulation mode.
      ASSERT (Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED);
    }
  }
}

EFI_STATUS
EFIAPI
DetectKeypressCallback (
  IN EFI_KEY_DATA     *KeyData
)
{
  mHotKeypressed = TRUE;

  if (HotKeyEvent != NULL) {
    gBS->SignalEvent(HotKeyEvent);
  }

  return EFI_SUCCESS;
}

VOID
EFIAPI
ProcessFirmwareVolumeCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
)
{
//  EFI_HANDLE                    FwVolHandle;  @todo Align PlatformBootOption (DxePlatformBootManagerLib) with the Minimum Platform FV map
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  EFI_HOB_GUID_TYPE        *GuidHob;

  GuidHob = NULL;
#endif
  DEBUG ((DEBUG_INFO, "Callback invoke, mDecompressFvUefiBoot %d\n", mDecompressFvUefiBoot));
  if (mDecompressFvUefiBoot) {
    return;
  }

  if (!mHotKeypressed) {
    return;
  }
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  GuidHob = GetFirstGuidHob (&gSysFwUpdateProgressGuid);
  if ((GuidHob != NULL) && \
      (((SYSTEM_FIRMWARE_UPDATE_PROGRESS *) GET_GUID_HOB_DATA (GuidHob))->Component == UpdatingBios)) {
    return;
  }
#endif
// @todo Align PlatformBootOption (DxePlatformBootManagerLib) with the Minimum Platform FV map
//  gDS->ProcessFirmwareVolume (
//          (VOID *) (UINTN)PcdGet32(PcdFlashFvUefiBootBase),
//          PcdGet32(PcdFlashFvUefiBootSize),
//          &FwVolHandle
//          );
//  gDS->Dispatch ();
  DEBUG ((DEBUG_INFO, "ProcessFirmwareVolumeCallback, Decompress FvUefiBoot before entering into setup menu\n"));
  mDecompressFvUefiBoot = TRUE;
  mHotKeypressed = FALSE;

  return;
}

VOID
EFIAPI
StopProcessFirmwareVolume (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                            Status;
  UINTN                                 Index;
  EFI_HANDLE                            *Handles;
  UINTN                                 HandleCount;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *TxtInEx;
  VOID                                  *NotifyHandle;
  VOID                                  *NotifyHandle2;
  EFI_KEY_DATA                  F2;
  EFI_KEY_DATA                  F7;
  F2.Key.ScanCode    = SCAN_F2;
  F2.Key.UnicodeChar = CHAR_NULL;
  F2.KeyState.KeyShiftState = EFI_SHIFT_STATE_VALID;
  F2.KeyState.KeyToggleState = 0;

  F7.Key.ScanCode    = SCAN_F7;
  F7.Key.UnicodeChar = CHAR_NULL;
  F7.KeyState.KeyShiftState = EFI_SHIFT_STATE_VALID;
  F7.KeyState.KeyToggleState = 0;
  gBS->CloseEvent (Event);

  gBS->LocateHandleBuffer (
          ByProtocol,
          &gEfiSimpleTextInputExProtocolGuid,
          NULL,
          &HandleCount,
          &Handles
          );

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (Handles[Index], &gEfiSimpleTextInputExProtocolGuid, (VOID **) &TxtInEx);
    ASSERT_EFI_ERROR (Status);

    Status = TxtInEx->RegisterKeyNotify (
                        TxtInEx,
                        &F2,
                        DetectKeypressCallback,
                        &NotifyHandle
                        );
    if (!EFI_ERROR (Status)) {
      Status = TxtInEx->UnregisterKeyNotify (TxtInEx, NotifyHandle);
      DEBUG ((DEBUG_INFO, "UnregisterKeyNotify: %04x/%04x %r\n", F2.Key.ScanCode, F2.Key.UnicodeChar, Status));
    }

    Status = TxtInEx->RegisterKeyNotify (
                        TxtInEx,
                        &F7,
                        DetectKeypressCallback,
                        &NotifyHandle2
                        );
    if (!EFI_ERROR (Status)) {
      Status = TxtInEx->UnregisterKeyNotify (TxtInEx, NotifyHandle2);
      DEBUG ((DEBUG_INFO, "UnregisterKeyNotify: %04x/%04x %r\n", F7.Key.ScanCode, F7.Key.UnicodeChar, Status));
    }
  }
}

/**
  This function is called after all the boot options are enumerated and ordered properly.
**/
VOID
RegisterStaticHotkey (
  VOID
  )
{

  EFI_INPUT_KEY                 Enter;
  EFI_KEY_DATA                  F2;
  EFI_KEY_DATA                  F7;
  BOOLEAN                       EnterSetup;
  EFI_STATUS                    Status;
  EFI_BOOT_MANAGER_LOAD_OPTION  BootOption;
  VOID                          *NotifyHandle;
  VOID                          *NotifyHandle2;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *TxtInEx;
  EFI_HANDLE                    *Handles;
  UINTN                         HandleCount;
  UINTN                         HandleIndex;
  EFI_EVENT                     Event;

  EnterSetup = AmtEnterSetup ();

  //
  // [Enter]
  //
  mContinueBoot = !EnterSetup;
  if (mContinueBoot) {
    Enter.ScanCode    = SCAN_NULL;
    Enter.UnicodeChar = CHAR_CARRIAGE_RETURN;
    EfiBootManagerRegisterContinueKeyOption (0, &Enter, NULL);
  }

  //
  // [F2]/[F7]
  //
  F2.Key.ScanCode    = SCAN_F2;
  F2.Key.UnicodeChar = CHAR_NULL;
  F2.KeyState.KeyShiftState = EFI_SHIFT_STATE_VALID;
  F2.KeyState.KeyToggleState = 0;
  Status = EfiBootManagerGetBootManagerMenu (&BootOption);
  ASSERT_EFI_ERROR (Status);
  RegisterBootOptionHotkey ((UINT16) BootOption.OptionNumber, &F2.Key, TRUE);
  EfiBootManagerFreeLoadOption (&BootOption);

  F7.Key.ScanCode    = SCAN_F7;
  F7.Key.UnicodeChar = CHAR_NULL;
  F7.KeyState.KeyShiftState = EFI_SHIFT_STATE_VALID;
  F7.KeyState.KeyToggleState = 0;
  mBootMenuBoot  = !EnterSetup;
  RegisterBootOptionHotkey ((UINT16) mBootMenuOptionNumber, &F7.Key, mBootMenuBoot);

  //
  // Register ProcessFirmwareVolumeCallback function of F2 & F7
  //
  //
    if (!mDecompressFvUefiBoot) {
      DEBUG ((DEBUG_INFO, "Register F2 and F7\n"));
      gBS->LocateHandleBuffer (
                ByProtocol,
                &gEfiSimpleTextInputExProtocolGuid,
                NULL,
                &HandleCount,
                &Handles
                );

      for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        Status = gBS->HandleProtocol (Handles[HandleIndex], &gEfiSimpleTextInputExProtocolGuid, (VOID **) &TxtInEx);
        ASSERT_EFI_ERROR (Status);
        Status = TxtInEx->RegisterKeyNotify (
                      TxtInEx,
                      &F2,
                      DetectKeypressCallback,
                      &NotifyHandle
                      );

        Status = TxtInEx->RegisterKeyNotify (
                      TxtInEx,
                      &F7,
                      DetectKeypressCallback,
                      &NotifyHandle2
                      );
      }

      Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  ProcessFirmwareVolumeCallback,
                  NULL,
                  &HotKeyEvent
                  );

      Status = EfiCreateEventReadyToBootEx (
                  TPL_CALLBACK,
                  StopProcessFirmwareVolume,
                  NULL,
                  &Event
                  );
    }
}

/**
  Convert KeyShiftState in EFI_KEY_DATA structure to EFI boot manager modifier.

  @param  Keydata        Pointer to EFI_KEY_DATA structure.

  @retval UINT32         EFI boot manager modifier.

**/
UINT32
GetEfiBootManagerModifier (
  EFI_KEY_DATA         *Keydata
  )
{
  UINT32        Modifier;

  ASSERT (Keydata != NULL);
  if (Keydata == NULL) {
    return 0;
  }

  Modifier = 0;

  if ((Keydata->KeyState.KeyShiftState & EFI_SHIFT_STATE_VALID) == 0) {
    return Modifier;
  }

  if ((Keydata->KeyState.KeyShiftState & (EFI_RIGHT_SHIFT_PRESSED | EFI_LEFT_SHIFT_PRESSED)) != 0) {
    Modifier |= EFI_BOOT_MANAGER_SHIFT_PRESSED;
  }
  if ((Keydata->KeyState.KeyShiftState & (EFI_RIGHT_CONTROL_PRESSED | EFI_LEFT_CONTROL_PRESSED)) != 0) {
    Modifier |= EFI_BOOT_MANAGER_CONTROL_PRESSED;
  }
  if ((Keydata->KeyState.KeyShiftState & (EFI_RIGHT_ALT_PRESSED | EFI_LEFT_ALT_PRESSED)) != 0) {
    Modifier |= EFI_BOOT_MANAGER_ALT_PRESSED;
  }
  if ((Keydata->KeyState.KeyShiftState & (EFI_RIGHT_LOGO_PRESSED | EFI_LEFT_LOGO_PRESSED)) != 0) {
    Modifier |= EFI_BOOT_MANAGER_LOGO_PRESSED;
  }
  if ((Keydata->KeyState.KeyShiftState & EFI_MENU_KEY_PRESSED) != 0) {
    Modifier |= EFI_BOOT_MANAGER_MENU_KEY_PRESSED;
  }
  if ((Keydata->KeyState.KeyShiftState & EFI_SYS_REQ_PRESSED) != 0) {
    Modifier |= EFI_BOOT_MANAGER_SYS_REQ_PRESSED;
  }

  return Modifier;
}

VOID
RegisterDynamicHotkey (
  VOID
  )
{
  EFI_INPUT_KEY                 F12;
  EFI_STATUS                    Status;
  UINT16                        PxeOptionNumber;
  //
  // [F12]
  //
  F12.ScanCode    = SCAN_F12;
  F12.UnicodeChar = CHAR_NULL;

  Status = GetPxeOption (&PxeOptionNumber);
  if (!EFI_ERROR (Status)) {
    mPxeBoot = TRUE;
  }

  if (AmtEnterSetup ()) {
    mPxeBoot = FALSE;
  }

  RegisterBootOptionHotkey (PxeOptionNumber, &F12, mPxeBoot);
}

/**
  Print the boot prompt.
**/
VOID
PrintBootPrompt (
  VOID
  )
{
  EFI_STRING      String;
  EFI_STATUS      Status;
  EFI_INPUT_KEY   Key;

  if ((BOOLEAN) (mSystemConfiguration.BootFirstToShell)) {
    //
    // Modify the boot order and move the Shell to the first in the boot option list
    //
    ChangeFirstBootDeviceToShell();
    Print (L"\nBoot First To Shell enabled...\n");
  }

  if (FastBootEnabled () && !mAnyKeypressed) {
    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    if (!EFI_ERROR (Status)) {
      mAnyKeypressed = TRUE;
    }
  }
  if (GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"\n\n");
  }

  if (mContinueBoot && GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"     Press [Enter]  to directly boot.\n");
  }

  if (GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"     Press [F2]     to enter setup and select boot options.\n");
  }
  if (mBootMenuBoot && GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"     Press [F7]     to show boot menu options.\n");
  }
  if (mPxeBoot && GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"     Press [F12]    to PXE boot.\n");
  }

  if (GetDisplayBootMode () == NORMAL_BOOT) {
    do {
      Status = AmtGetSetupPrompt (&String);
      if (!EFI_ERROR (Status) && (String != NULL)) {
        Print (L"     %s\n", String);
      }
    } while (!EFI_ERROR (Status));
  }

  if (GetDisplayBootMode () == NORMAL_BOOT) {
    Print (L"     Press [Pause]  to pause and <any key> to continue booting.\n");
  }

}

UINT8
BootOptionType (
  IN EFI_DEVICE_PATH_PROTOCOL   *DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL      *Node;
  EFI_DEVICE_PATH_PROTOCOL      *NextNode;

  for (Node = DevicePath; !IsDevicePathEndType (Node); Node = NextDevicePathNode (Node)) {
    if (DevicePathType (Node) == MESSAGING_DEVICE_PATH) {
      //
      // Make sure the device path points to the driver device.
      //
      NextNode = NextDevicePathNode (Node);
      if (DevicePathSubType(NextNode) == MSG_DEVICE_LOGICAL_UNIT_DP) {
        //
        // if the next node type is Device Logical Unit, which specify the Logical Unit Number (LUN),
        // skip it
        //
        NextNode = NextDevicePathNode (NextNode);
      }
      if (IsDevicePathEndType (NextNode)) {
        if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH)) {
          return DevicePathSubType (Node);
        } else {
          return MSG_SATA_DP;
        }
      }
    }
  }

  return (UINT8) -1;
}

/**
  Returns the priority number.
  OptionType      Legacy           EFI
  ------------------------------------
  PXE               1              2
  DVD               3              4
  USB               5              6
  HDD               7              8
  EFI Shell                        9
  Others            98             99

  @param BootOption
**/
UINTN
BootOptionPriority (
  CONST EFI_BOOT_MANAGER_LOAD_OPTION *BootOption
  )
{

  if (DevicePathType (BootOption->FilePath) == BBS_DEVICE_PATH) {
    switch (((BBS_BBS_DEVICE_PATH *) BootOption->FilePath)->DeviceType) {
    case BBS_TYPE_EMBEDDED_NETWORK:
      return 1;
    case BBS_TYPE_CDROM:
      return 3;
    case BBS_TYPE_USB:
      return 5;
    case BBS_TYPE_HARDDRIVE:
      return 7;
    default:
      return 98; // put in the end but before UEFI other boot options
    }
  } else {
    //
    // EFI boot options
    //
    switch (BootOptionType (BootOption->FilePath)) {
    case MSG_MAC_ADDR_DP:
    case MSG_VLAN_DP:
    case MSG_IPv4_DP:
    case MSG_IPv6_DP:
      return 2;

    case MSG_SATA_DP:
    case MSG_ATAPI_DP:
    case MSG_UFS_DP:
    case MSG_NVME_NAMESPACE_DP:
      return 4;

    case MSG_USB_DP:
      return 6;

    }
    if ((StrCmp (BootOption->Description, INTERNAL_EDK_SHELL_NAME) == 0) ||
        (StrCmp (BootOption->Description, INTERNAL_UEFI_SHELL_NAME) == 0)
       ) {
      return 9;
    }
    if (StrCmp (BootOption->Description, UEFI_HARD_DRIVE_NAME) == 0) {
      return 8;
    }

    if ((StrCmp (BootOption->Description, EMMC_HARD_DRIVE_NAME) == 0) ||
        (StrCmp (BootOption->Description, EMMC_HARD_DRIVE_NAME2) == 0) ||
        (StrCmp (BootOption->Description, EMMC_HARD_DRIVE_NAME3) == 0)
       ) {
      return 8;
    }
    return 99;
  }
}

INTN
EFIAPI
CompareBootOption (
  CONST VOID  *Left,
  CONST VOID  *Right
  )
{
  return BootOptionPriority ((EFI_BOOT_MANAGER_LOAD_OPTION *) Left) -
         BootOptionPriority ((EFI_BOOT_MANAGER_LOAD_OPTION *) Right);
}

/**
  This function is called each when Manufacturing mode is enabled.

  If first bootdevice is Shell, No changes will be done.
  If first bootdevice is not shell,then shell is moved to first in boot
  list and first device to shell's previous position in the boot list.

**/
VOID
ChangeFirstBootDeviceToShell (
  VOID
  )
{
  EFI_BOOT_MANAGER_LOAD_OPTION    *BootOption;
  EFI_BOOT_MANAGER_LOAD_OPTION    TempOption;
  UINTN                           BootOptionCount;
  UINT8                           FirstBootdevice;
  UINT8                           IndexI,IndexJ;
  UINT16                          *OptionOrder;

  BootOption = NULL;
  FirstBootdevice = 0;
  //
  // Get the Boot options
  //
  BootOption = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);
  //
  // If first boot device is already shell, Dont need to change the bootlist
  //
  if( (StrCmp(BootOption[FirstBootdevice].Description, INTERNAL_EDK_SHELL_NAME)==0) ||
      (StrCmp(BootOption[FirstBootdevice].Description, INTERNAL_UEFI_SHELL_NAME)==0)) {
    return ;
  }
  //
  // Find the UEFI shell in the boot list
  //
  for(IndexI=1;IndexI<BootOptionCount;IndexI++) {
    //
    // If find the shell, change the boot order
    //
    if( (StrCmp(BootOption[IndexI].Description, INTERNAL_EDK_SHELL_NAME)==0) ||
        (StrCmp(BootOption[IndexI].Description, INTERNAL_UEFI_SHELL_NAME)==0)) {
      //
      // Swap the Boot Order
      //
      CopyMem (&TempOption, &BootOption[IndexI], sizeof (EFI_BOOT_MANAGER_LOAD_OPTION));
      CopyMem (&BootOption[IndexI], &BootOption[FirstBootdevice], sizeof (EFI_BOOT_MANAGER_LOAD_OPTION));
      CopyMem (&BootOption[FirstBootdevice], &TempOption, sizeof (EFI_BOOT_MANAGER_LOAD_OPTION));
      //
      // Update the new BootOrder
      //
      OptionOrder = AllocatePool ((BootOptionCount ) * sizeof (UINT16));
      ASSERT (OptionOrder != NULL);
      if (OptionOrder == NULL) return;
      for (IndexJ = 0; IndexJ < BootOptionCount; IndexJ++) {
        OptionOrder[IndexJ ] = (UINT16) BootOption[IndexJ].OptionNumber;
      }

      gRT->SetVariable (
             L"BootOrder",
             &gEfiGlobalVariableGuid,
             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
             (BootOptionCount)* sizeof (UINT16),
             OptionOrder
             );
      break;
    }
  }
}

/**
  Return if Shell is in Boot List.

  @retval TRUE  Shell is in Boot List.
  @retval FALSE Shell is in NOT Boot List.
**/
BOOLEAN
IsShellInBootList (
  VOID
  )
{
  EFI_BOOT_MANAGER_LOAD_OPTION    *BootOption;
  UINTN                           BootOptionCount;
  UINT8                           IndexI;

  BootOption = NULL;

  //
  // Get the Boot options
  //
  BootOption = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeBoot);
  //
  // Find the UEFI shell in the boot list
  //
  for(IndexI=0;IndexI<BootOptionCount;IndexI++) {
    if( (StrCmp(BootOption[IndexI].Description, INTERNAL_EDK_SHELL_NAME)==0) ||
        (StrCmp(BootOption[IndexI].Description, INTERNAL_UEFI_SHELL_NAME)==0)) {
      return TRUE;
    }
  }
  return FALSE;
}
