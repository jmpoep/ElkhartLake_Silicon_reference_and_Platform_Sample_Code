/** @file
  Intel Trusted Device Setup Implementation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.
**/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Include/TrustedDeviceSetup.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/DevicePath.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <SetupVariable.h>
#include <Library/PciSegmentLib.h>
#include <TrustedDeviceSetupExtensionProtocol.h>
#include <Library/DxeServicesTableLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED TRUSTED_DEVICE_SETUP_PROTOCOL mTrustedDeviceSetupProtocol = {
  TRUSTED_DEVICE_SETUP_PROTOCOL_REVISION,
  TrustedDeviceSetupMain,
  UpdateSmbiosTrustedDeviceSetupCapabilities
};

GLOBAL_REMOVE_IF_UNREFERENCED TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL mTrustedDeviceSetupExtensionProtocol = {
  TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL_REVISION,
  TrustedDeviceSetupChassisIntrusionEnabled,
  TrustedDeviceSetupChassisIntrusionDetected,
  TrustedDeviceSetupAddKeyboard,
  TrustedDeviceSetupRemoveKeyboard
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mTrustedDeviceSetupParameter = 0;

/**
  Checks CSME for Intel Trusted Device Setup Enable/Disable and BootLock Enable/Disable
  Also checks Setup Variable used for Trusted Device Setup testing; when set, mimic
  both TrustedDeviceSetupEnable and BootLock Enable

  @param[in] Param                    BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval BIT0                        1 - TrustedDeviceSetupBoot is Enabled; 0 - TrustedDeviceSetupBoot is Disabled
          BIT1                        1 - BootLock is Enabled; 0 - BootLock is Disabled
**/
UINT8
GetTrustedDeviceSetupStatusHelper (
  IN UINT16  Param
  )
{

  UINT16                  SpecialCommandParam;
  UINT8                   TrustedDeviceSetupStatus;
  BOOLEAN                 TrustedDeviceSetupSetupVar;

  TrustedDeviceSetupStatus = 0;
  TrustedDeviceSetupSetupVar = FALSE;


  SpecialCommandParam = Param;
  //
  // Set BIT0 for Trusted Device Setup boot mode if the CSME Boot Option has TrustedDeviceSetupBootEnabled or the setup option is set
  //
  if ((TRUSTED_DEVICE_SETUP_BOOT_ENABLE & SpecialCommandParam) != 0 || TrustedDeviceSetupSetupVar) {
    TrustedDeviceSetupStatus |= BIT0;
  }
  //
  // Set BIT1 for BootLock if the CSME Boot Option has BootLockEnabled or the setup option is set
  //
  if ((TRUSTED_DEVICE_SETUP_BOOT_LOCK & SpecialCommandParam) != 0 || TrustedDeviceSetupSetupVar) {
    TrustedDeviceSetupStatus |= BIT1;
  }
  return TrustedDeviceSetupStatus;
}

/**
  Function to check whether or not this is a Intel Trusted Device Setup boot

  @param[in] Param                    BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval TRUE                        This is a Trusted Device Setup Boot
  @retval FALSE                       This is NOT a Trusted Device Setup Boot
**/
BOOLEAN
IsTrustedDeviceSetupBoot (
  IN UINT16  Param
  )
{
  if (GetTrustedDeviceSetupStatusHelper (Param) & BIT0) {
    DEBUG ((DEBUG_INFO, "IsTrustedDeviceSetupBoot True\n"));
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Function to check if Intel Trusted Device Setup BootLock enabled

  @param[in] Param                    BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval TRUE                        This is a Trusted Device Setup Boot
  @retval FALSE                       This is NOT a Trusted Device Setup Boot
**/
BOOLEAN
IsTrustedDeviceSetupBootLock (
  IN UINT16  Param
  )
{
  if (GetTrustedDeviceSetupStatusHelper (Param) & BIT1) {
    DEBUG((DEBUG_INFO, "IsTrustedDeviceSetupBootLock True\n"));
    return TRUE;
  } else {
    return FALSE;
  }
}
/**
  Get device path with Guid in a FV.

  @param[in] FileGuid        File GUID value to be searched.
  @param[in] FvBase          Starting Address of the Firmware Volume accommodate the Extension.
  @param[in] FvSize          Size of the Firmware Volume
  @param[out] DevicePath     The searched Device Path.

  @retval EFI_SUCCESS        The Device Path has been found successfully.
  @retval EFI_NOT_FOUND      The requested file was not found in the firmware volume.
  @retval Other              Error finding the Device Path.

**/
EFI_STATUS
FindDevicePathByGuid (
  IN  EFI_GUID                     *FileGuid,
  IN  UINT32                       FvBase,
  IN  UINT32                       FvSize,
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
  EFI_HANDLE                         FwVolHandle;

  Status = EFI_SUCCESS;

  if ((VOID *) (UINTN) FvBase == NULL) {
    return EFI_NOT_FOUND;
  }

  DEBUG((DEBUG_INFO, "[FVTDS] Trusted Device Setup is enabled, decompressing FVTDS.\n"));
  gDS->ProcessFirmwareVolume (
         (VOID *) (UINTN) FvBase,
         FvSize,
         &FwVolHandle
         );

  gDS->Dispatch ();

  EfiInitializeFwVolDevicepathNode (&FileNode, FileGuid);

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &FvHandleCount,
                  &FvHandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < FvHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    FvHandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **)&Fv
                    );
    if (EFI_ERROR (Status)) {
      break;
    }

    Buffer = NULL;
    Size = 0;
    Status = Fv->ReadSection (
                   Fv,
                   FileGuid,
                   EFI_SECTION_PE32,
                   0,
                   &Buffer,
                   &Size,
                   &AuthenticationStatus
                   );
    if (!EFI_ERROR(Status)) {
      break;
    }
  }

  if (Index == FvHandleCount) {
    FreePool (FvHandleBuffer);
    return EFI_NOT_FOUND;
  }

  *DevicePath = AppendDevicePathNode (
                  DevicePathFromHandle (FvHandleBuffer[Index]),
                  (EFI_DEVICE_PATH_PROTOCOL *)&FileNode
                  );
  ASSERT (*DevicePath != NULL);

  if (FvHandleCount != 0) {
    FreePool (FvHandleBuffer);
  }

  return Status;
}

/**
  Add and Set Intel Trusted Device Setup Boot SysPrep option

  @param[in]  FvBase                Starting Address of the Firmware Volume accommodate the Extension.
  @param[in]  FvSize                Size of the Firmware Volume

  @retval EFI_SUCCESS               TDS Extension has been added as a SysPrep option
  @retval EFI_INVALID_PARAMETER     Option, Description or FilePath to initialize load option is NULL.
  @retval EFI_NOT_FOUND             The TDS Extension could not be found.
  @retval Other                     Error creating SysPrep option

**/
EFI_STATUS
CreateTrustedDeviceSetupLoadOption (
  IN UINT32 FvBase,
  IN UINT32 FvSize
  )
{
  EFI_STATUS                   Status;
  EFI_BOOT_MANAGER_LOAD_OPTION TrustedDeviceSetupOption;
  EFI_DEVICE_PATH_PROTOCOL     *DevicePath;

  //
  // Specific boot for Trusted Device Setup feature
  //

  Status = FindDevicePathByGuid (&gTdsExtensionGuid, FvBase, FvSize, &DevicePath);
  DEBUG((DEBUG_INFO, "TrustedDeviceSetup Find TDS Extension Status: %r\n", Status));
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = EfiBootManagerInitializeLoadOption (
             &TrustedDeviceSetupOption,
             LoadOptionNumberUnassigned,
             LoadOptionTypeSysPrep,
             EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION | LOAD_OPTION_ACTIVE,
             L"TrustedDeviceSetupBoot",
             DevicePath,
             NULL,
             0
             );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    Status = EfiBootManagerAddLoadOptionVariable (&TrustedDeviceSetupOption, 0);
  }
  return Status;
}

/**
  Function removes Intel Trusted Device Setup SysPrep option from load options on Ready To Boot event

  @param[in] Event      Event whose notification function is being invoked.
  @param[in] Context    Pointer to the notification function's context.
**/
VOID
EFIAPI
TrustedDeviceSetupReadyToBoot (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions;
  UINTN                        BootOptionCount;
  UINTN                        Index;

  BootOptions = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeSysPrep);
  for (Index = 0; Index < BootOptionCount; Index++) {
    if ((StrnCmp(BootOptions[Index].Description, L"TrustedDeviceSetupBoot", StrLen(L"TrustedDeviceSetupBoot"))) == 0) {
      EfiBootManagerDeleteLoadOptionVariable (BootOptions[Index].OptionNumber, LoadOptionTypeSysPrep);
      break;
    }
  }
  EfiBootManagerFreeLoadOptions (BootOptions, BootOptionCount);
  gBS->CloseEvent (Event);
}

/**
  Registers a callback on Ready to Boot event that will remove the sysprep option

  @retval EFI_SUCCESS    Callback has been successfully registered
  @retval Others         Callback was not registered
**/
EFI_STATUS
EFIAPI
RegisterTrustedDeviceSetupCallback (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   ReadyToBootEvent;

  //
  // Register Ready to Boot Event for Intel Trusted Device Setup boot
  //
  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             TrustedDeviceSetupReadyToBoot,
             NULL,
             &ReadyToBootEvent
             );
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  Installs the protocol provided for the TDS Extension to determine chassis intrusion capability and status

  @retval EFI_SUCCESS  The protocol has been successfully installed
  @retval Others       An error has occurred and the protocol was not published
**/
EFI_STATUS
EFIAPI
InstallTrustedDeviceSetupExtensionProtocol (
  VOID
  )
{
  EFI_HANDLE            Handle;
  EFI_STATUS            Status;

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gTrustedDeviceSetupExtensionProtocolGuid,
                  &mTrustedDeviceSetupExtensionProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR(Status);
  DEBUG((DEBUG_INFO, "TDS Extension Protocol Installed Status: %r\n", Status));

  return Status;
}

/**
Checks to see if there is already a TrustedDeviceSetup SysPrep Option

@retval TRUE     TrustedDeviceSetup SysPrep Option needs to be added
@retval FALSE    TrustedDeviceSetup SysPrep Option already exists
**/
BOOLEAN
NeedTrustedDeviceSetupSysPrepOption (
  VOID
)
{
  EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions;
  UINTN                        BootOptionCount;
  UINTN                        Index;

  BootOptionCount = 0;

  BootOptions = EfiBootManagerGetLoadOptions (&BootOptionCount, LoadOptionTypeSysPrep);
  for (Index = 0; Index < BootOptionCount; Index++) {
    if ((StrnCmp(BootOptions[Index].Description, L"TrustedDeviceSetupBoot", StrLen(L"TrustedDeviceSetupBoot"))) == 0) {
      DEBUG ((DEBUG_INFO, "TrustedDeviceSetupBoot already exists!\n"));
      return FALSE;
    }
  }
  return TRUE;
}

/**
  The Intel Trusted Device Setup main function.

  The function does the necessary work for the Trusted Device Setup feature.
  This function shall be called from the right before ExitPmAuth () to ensure no ConIn variables
  are set after this runs.

  @param[in] ExtensionFvBase              Starting Address of the Firmware Volume accommodate the Extension.
  @param[in] ExtensionFvSize              Size of the Firmware Volume
  @param[in] TrustedDeviceSetupParam      BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval EFI_SUCCESS                     It is a Trusted Device Setup boot and all tasks have been successfully completed.
  @retval EFI_UNSUPPORTED                 It is not a Trusted Device Setup boot
  @retval EFI_ABORTED                     Trusted Device Setup failed
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupMain (
  IN UINT32 ExtensionFvBase,
  IN UINT32 ExtensionFvSize,
  IN UINT16 TrustedDeviceSetupParam
  )
{
  EFI_STATUS  ModeStatus;
  EFI_STATUS  LockStatus;
  EFI_STATUS  ProtocolStatus;

  ModeStatus     = EFI_SUCCESS;
  LockStatus     = EFI_SUCCESS;
  ProtocolStatus = EFI_SUCCESS;

  mTrustedDeviceSetupParameter = TrustedDeviceSetupParam;
  //
  // Check if Trusted Device Setup is enabled, and if so, add TDS Extension to SysPrep#### and create
  // callback on ReadyToBoot to remove TDS Extension from SysPrep#### entries.
  //
  if (IsTrustedDeviceSetupBoot (mTrustedDeviceSetupParameter)) {
    ModeStatus = RegisterTrustedDeviceSetupCallback (); // Add the callback to remove the option
    DEBUG((DEBUG_INFO, "TrustedDeviceSetup Register Callback with Status: %r\n", ModeStatus));
    if (!EFI_ERROR (ModeStatus)) {
      if (NeedTrustedDeviceSetupSysPrepOption()) {
        ModeStatus = CreateTrustedDeviceSetupLoadOption (ExtensionFvBase, ExtensionFvSize); // Only add the SysPrep Option if it can be removed at end of running
      }
      ProtocolStatus = InstallTrustedDeviceSetupExtensionProtocol (); // Publish the chassis intrusion detection protocol for TDS Extension
    }

    //
    // Check if CSME requests user to be locked out of any BIOS menu. And if so, lock out the user.
    //
    if (IsTrustedDeviceSetupBootLock (mTrustedDeviceSetupParameter)) {
      LockStatus = SuppressUserInput ();
      DEBUG((DEBUG_INFO, "TrustedDeviceSetup Suppress User Input with Status: %r\n", LockStatus));
    }
  } else {

    //
    // Return EFI_UNSUPPORTED to indicate that it is not a Trusted Device Setup boot and Trusted Device Setup will not be supported
    //
    return EFI_UNSUPPORTED;
  }

  //
  // Return EFI_SUCCESS if all subfunctions executed properly.
  // Return EFI_ABORTED for any error detected.
  //
  if (!EFI_ERROR (LockStatus) && !EFI_ERROR (ModeStatus) && !EFI_ERROR (ProtocolStatus)) {
    return EFI_SUCCESS;
  } else {
    return EFI_ABORTED;
  }
}

/**
  Entry point of the Intel Trusted Device Setup DXE Driver

  Installs the Trusted Device Setup Protocol for other functions to locate and use

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval     EFI_SUCCESS         The protocol has installed successfully
  @retval     Others              The protocol did not install successfully
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gTrustedDeviceSetupMainProtocolGuid,
                  &mTrustedDeviceSetupProtocol,
                  NULL
                  );

  ASSERT_EFI_ERROR(Status);
  DEBUG ((DEBUG_INFO, "TrustedDeviceSetup Protocol Install Status: %r\n", Status));

  return Status;
}
