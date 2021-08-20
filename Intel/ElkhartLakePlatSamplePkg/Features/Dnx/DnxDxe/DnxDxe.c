/** @file
Module Name:

  DnxDxe.c

Abstract:

  Dnx driver main function.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

@par Specification
**/

#include "DnxDxe.h"
#include <SetupVariable.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include <Library/DxeMeLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/DevicePathLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformMiscLib.h>
#include <Protocol/BlockIo.h>
/**
  Function to locate Ffu Applcation and launch it safely.

  @param[in] None
  @retval    None

**/
VOID
LaunchFfuApplication (
  VOID
)
{
  EFI_STATUS                        Status;
  UINT8                             *ImageBuffer;
  EFI_HANDLE                        ImageHandle;
  UINTN                             Index;
  UINTN                             FvHandleCount;
  EFI_HANDLE                        *FvHandleBuffer;
  UINTN                             Size;
  UINT32                            AuthenticationStatus;
  EFI_FIRMWARE_VOLUME2_PROTOCOL     *Fv;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH FfuNode;

  DEBUG ((DEBUG_INFO, "LaunchFfuApplication..\n"));
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &FvHandleCount,
                  &FvHandleBuffer
                  );

  if (EFI_ERROR (Status) || (FvHandleCount == 0)) {
    DEBUG ((DEBUG_INFO, "LocateHandleBuffer Status %r, Count %d..\n", Status, FvHandleCount));
    return;
  }
  for (Index = 0; Index < FvHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    FvHandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **)&Fv
                    );

    ImageBuffer  = NULL;
    Size    = 0;
    Status  = Fv->ReadSection (
                    Fv,
                    PcdGetPtr(PcdFfuLoaderFile),
                    EFI_SECTION_PE32,
                    0,
                    (VOID **) &ImageBuffer,
                    &Size,
                    &AuthenticationStatus
                    );
    if (EFI_ERROR(Status)) {
      //
      // Skip if no file in the FV
      //
      continue;
    }
    DEBUG ((DEBUG_INFO, "Image located..\n"));
    DevicePath = DevicePathFromHandle(FvHandleBuffer[Index]);
    //
    // Build device path
    //
    EfiInitializeFwVolDevicepathNode (&FfuNode, PcdGetPtr(PcdFfuLoaderFile));

    DevicePath = AppendDevicePathNode (DevicePath, (EFI_DEVICE_PATH_PROTOCOL *)&FfuNode);
    Status = gBS->LoadImage (
                    FALSE,
                    gImageHandle,
                    DevicePath,
                    ImageBuffer,
                    Size,
                    &ImageHandle
                    );
    if (!EFI_ERROR(Status)) {
      DEBUG ((DEBUG_INFO, "Load Image Successful..\n"));
      Status = gBS->StartImage (ImageHandle, NULL, NULL);
      DEBUG ((DEBUG_INFO, "Start Image Status %r..\n", Status));
    }
    if (EFI_ERROR(Status)) {
      gST->ConOut->ClearScreen (gST->ConOut);
      gST->ConOut->EnableCursor (gST->ConOut, TRUE);
      gST->ConOut->OutputString (gST->ConOut, L"Failed to Launch FFU Loader Application...");
    }
  }

}

/**
  Function to check for setup Option which will be set if Boot Loader is corrupted or not present

  @param[in] None
  @retval    Boolean TRUE if setup option is set

**/
BOOLEAN
CheckSetupOption (
  VOID
  )
{
  EFI_STATUS   Status;
  SETUP_DATA   SetupData;
  UINTN        DataSize;
  UINT32       Attributes;

  Attributes = 0;
  DataSize = sizeof (SETUP_DATA);

  DEBUG ((DEBUG_INFO, "Os Dnx Check Setup Option\n"));

  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &Attributes,
                  &DataSize,
                  &SetupData
                );

  if (!EFI_ERROR(Status)) {
    DEBUG ((DEBUG_INFO, "OsDnx Value: 0x%X\n", SetupData.OsDnx));
    if (SetupData.OsDnx == 1) {
      SetupData.OsDnx = 0;
      Status = gRT->SetVariable (
                     L"Setup",
                     &gSetupVariableGuid,
                     Attributes,
                     DataSize,
                     &SetupData
                   );
      ASSERT_EFI_ERROR (Status);
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Function to check for Cse Os Recovery

  @param[in] None
  @retval    Boolean TRUE if Cse Os Recovery is set

**/
BOOLEAN
CheckCseDnxOsRecovery (
  VOID
  )
{
  ME_BIOS_PAYLOAD_HOB     *MbpHob;

  MbpHob = NULL;
  DEBUG ((DEBUG_INFO, "CheckCseDnxOsRecovery\n"));
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if (MbpHob != NULL) {
    if (MbpHob->MeBiosPayload.IfwiDnxRequest.Available) {
      DEBUG ((DEBUG_INFO, "IFWI Dnx request Data is present\n"));
      if (((MbpHob->MeBiosPayload.IfwiDnxRequest.EnterRecovery & BIT0) == BIT0)) {
        DEBUG ((DEBUG_INFO, "IFWI Dnx requested for according to CSE\n"));
        HeciIafwDnxReqClear (0);
        DEBUG ((DEBUG_INFO, "Clearing CSE Dnx request\n"));
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
  Function to check for Bootloader corruption/not present

  @param[in] None
  @retval    Boolean TRUE if Bootloader is corrupted/not present

**/
BOOLEAN
CheckBootLoaderCorruption (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "CheckBootLoaderCorruption\n"));
  return (CheckSetupOption ());
}

/**
  Function to check for Volume up and down combinations

  @param[in] None
  @retval    Boolean TRUE if Volume buttons pressed

**/
BOOLEAN
CheckButtonCombination (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, " CheckButtonCombination\n"));
  return (GetVolumeUpButtonState () && GetVolumeDownButtonState ());
}

/**
  Function to check if Os Recovery Triggered

  @param[in] None
  @retval    Boolean TRUE if Os Recovery is triggered

**/
BOOLEAN
IsDnxModeTriggered (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, " IsDnxModeTriggered\n"));
  //
  // 1. Button combination(VolumeDown+VolumeUp)
  // 2. Bad OS boot loader and cable connection detected
  // 3. One shot device image request as indicated by the MBP Os Dnx bit
  //
  if ((CheckCseDnxOsRecovery ()) || (CheckBootLoaderCorruption ()) || (CheckButtonCombination ())) {
    return TRUE;
  }
  return FALSE;
}

/**
  Dnx ready to Boot Function

  @param[in] Event
  @param[in] Context

  @retval EFI_SUCCESS   if driver support is initialized without any issue.

**/
VOID
EFIAPI
DnxReadyToBootFunction (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  UINTN                     NoBlkIoHandles;
  EFI_HANDLE                *BlkIoHandle;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     Index;
  EFI_STATUS                Status;
  BOOLEAN                   UfsDeviceFound;

  UfsDeviceFound = FALSE;

  DEBUG ((DEBUG_INFO, "Dnx Entry\n"));

  if (IsDnxModeTriggered () == TRUE) {
    DEBUG ((DEBUG_INFO, "OS Dnx is Triggerred\n"));

    //
    // Locate Handles that support BlockIo protocol
    //
    Status = gBS->LocateHandleBuffer(
                    ByProtocol,
                    &gEfiBlockIoProtocolGuid,
                    NULL,
                    &NoBlkIoHandles,
                    &BlkIoHandle
                    );

    if (!EFI_ERROR (Status)) {
      for (Index = 0; Index < NoBlkIoHandles; Index++) {
        Status = gBS->HandleProtocol(
                        BlkIoHandle[Index],
                        &gEfiDevicePathProtocolGuid,
                        (VOID **) &DevicePath
                        );
        if (!EFI_ERROR (Status)) {
          while (!IsDevicePathEndType (NextDevicePathNode(DevicePath))) {
            DevicePath = NextDevicePathNode (DevicePath);
            if ((DevicePath->Type == MESSAGING_DEVICE_PATH) && (DevicePath->SubType == MSG_UFS_DP)) {
              UfsDeviceFound = TRUE;
              break;
            }
          }
        }
      }
    }
    if (UfsDeviceFound != TRUE) {
      DEBUG ((DEBUG_INFO, "FFU tool supports only UFS Flash and there is no UFS device detected in this boot\n"));
      gST->ConOut->ClearScreen (gST->ConOut);
      gST->ConOut->EnableCursor (gST->ConOut, TRUE);
      gST->ConOut->OutputString (gST->ConOut, L"FFU tool supports only UFS Flash and there is no UFS device detected in this boot\n");
      return;
    }
    gST->ConOut->ClearScreen (gST->ConOut);
    gST->ConOut->EnableCursor (gST->ConOut, TRUE);
    gST->ConOut->OutputString (gST->ConOut, L"OS Recovery Triggered...");
    LaunchFfuApplication ();
  }
  return;
}

/**
  Initializes the Dnx driver

  @param[in] ImageHandle  A copy of the ImageHandle.
  @param[in] SystemTable  A pointer to the SystemTable for the application.

  @retval EFI_SUCCESS   if driver support is initilized without any issue.

**/
EFI_STATUS
EFIAPI
DnxDxeEntry (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   Event;
  EFI_EVENT   DnxEvent;

  DEBUG ((DEBUG_INFO, "Entry DnxDxe driver\n"));

  Status = EFI_SUCCESS;

  Status = EfiCreateEventReadyToBootEx (
            TPL_CALLBACK,
            DnxReadyToBootFunction,
            NULL,
            &Event
            );

  //
  // Register the event handling function to return to Dnx when bootloader failed.
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  DnxReadyToBootFunction,
                  NULL,
                  &gPlatformOsDnxEventGuid,
                  &DnxEvent
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Exit DnxDxe driver %r\n", Status));

  return Status;
}
