/** @file
  Support routines for ASF boot options in the BDS

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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

#include <Library/UefiBootManagerLib.h>
#include "AmtWrapperDxe.h"
#include "AsfSupport.h"
#include <Library/DebugLib.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID                        gAsfRestoreBootSettingsGuid = RESTORE_SECURE_BOOT_GUID;

GLOBAL_REMOVE_IF_UNREFERENCED STORAGE_REDIRECTION_DEVICE_PATH mUsbrDevicePath = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8)(sizeof(PCI_DEVICE_PATH)),
        (UINT8)((sizeof(PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_XHCI,
    PCI_DEVICE_NUMBER_PCH_XHCI
  },
  {
    {
      MESSAGING_DEVICE_PATH,
      MSG_USB_DP,
      {
        (UINT8)(sizeof(USB_DEVICE_PATH)),
        (UINT8)((sizeof(USB_DEVICE_PATH)) >> 8)
      }
    },
    V_ME_PCH_LP_USBR2_PORT_NUMBER,
    0x0
  },
  gEndEntire
};

/**
  This routine makes necessary Secure Boot & CSM state changes for Storage Redirection boot

  @retval EFI_SUCCESS      Changes applied succesfully
**/
EFI_STATUS
ManageSecureBootState (
  VOID
  )
{
  EFI_STATUS Status;
  BOOLEAN    EnforceSecureBoot;
  UINT8      SecureBootState;
  UINT8      UsbrBoot;
  UINTN      VarSize;
  UINT32     VarAttributes;
  UINT8      RestoreBootSettings;

  VarSize = sizeof (UINT8);

  //
  // Get boot parameters (Storage Redirection boot?, EnforceSecureBoot flag set?, secure boot enabled?)
  //
  EnforceSecureBoot = AsfIsEnforceSecureBootEnabled ();
  UsbrBoot          = AsfIsStorageRedirectionEnabled ();

  Status = gRT->GetVariable (
                  L"SecureBootEnable",
                  &gEfiSecureBootEnableDisableGuid,
                  &VarAttributes,
                  &VarSize,
                  &SecureBootState
                  );
  if (EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

  //
  // Check whether we need to restore SecureBootEnable value changed in previous Storage Redirection boot
  //
  Status = gRT->GetVariable(
                  L"RestoreBootSettings",
                  &gAsfRestoreBootSettingsGuid,
                  NULL,
                  &VarSize,
                  &RestoreBootSettings
                  );

  if (Status == EFI_SUCCESS && RestoreBootSettings != RESTORE_SECURE_BOOT_NONE) {
    if (RestoreBootSettings == RESTORE_SECURE_BOOT_ENABLED && SecureBootState == SECURE_BOOT_DISABLED &&
      !(UsbrBoot && !EnforceSecureBoot)) {

      SecureBootState = SECURE_BOOT_ENABLED;
      Status = gRT->SetVariable (
                      L"SecureBootEnable",
                      &gEfiSecureBootEnableDisableGuid,
                      VarAttributes,
                      VarSize,
                      &SecureBootState
                      );
      ASSERT_EFI_ERROR (Status);

      //
      // Delete RestoreBootSettings variable
      //
      Status = gRT->SetVariable (
                      L"RestoreBootSettings",
                      &gAsfRestoreBootSettingsGuid,
                      0,
                      0,
                      NULL
                      );
      ASSERT_EFI_ERROR (Status);

      DEBUG ((DEBUG_INFO, "Secure Boot settings restored after Storage Redirection boot - Cold Reset!\n"));
      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  Status = EFI_SUCCESS;

  if (UsbrBoot) {
    if (SecureBootState == SECURE_BOOT_ENABLED && !EnforceSecureBoot) {
      //
      // Secure boot needs to be disabled if we're doing Storage Redirection and EnforceSecureBoot not set
      //
      SecureBootState     = SECURE_BOOT_DISABLED;
      RestoreBootSettings = RESTORE_SECURE_BOOT_ENABLED;

      Status = gRT->SetVariable (
                      L"SecureBootEnable",
                      &gEfiSecureBootEnableDisableGuid,
                      VarAttributes,
                      sizeof (UINT8),
                      &SecureBootState
                      );
      ASSERT_EFI_ERROR (Status);

      //
      // Set variable to restore previous secure boot state
      //
      Status = gRT->SetVariable (
                      L"RestoreBootSettings",
                      &gAsfRestoreBootSettingsGuid,
                      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                      sizeof (UINT8),
                      &RestoreBootSettings
                      );
      ASSERT_EFI_ERROR (Status);

      DEBUG ((DEBUG_INFO, "Secure Boot disabled for USBr boot - Cold Reset!\n"));
      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  return Status;
}

/**
  Compare two device paths up to a size of Boot Opion's Device Path

  @param[in] BootOptionDp     Device path acquired from BootXXXX EFI variable
  @param[in] FileSysDp        Device path acquired through EFI_SIMPLE_FILE_SYSTEM_PROTOCOL Handles buffer

  @retval TRUE                Both device paths point to the same device
  @retval FALSE               Device paths point to different devices
**/
BOOLEAN
CompareDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL *BootOptionDp,
  IN  EFI_DEVICE_PATH_PROTOCOL *FileSysDp
  )
{
  UINTN BootOptionDpSize;
  UINTN FileSysDpSize;

  if (BootOptionDp == NULL || FileSysDp == NULL) {
    return FALSE;
  }

  BootOptionDpSize = GetDevicePathSize (BootOptionDp) - END_DEVICE_PATH_LENGTH;
  FileSysDpSize    = GetDevicePathSize (FileSysDp) - END_DEVICE_PATH_LENGTH;

  if ((BootOptionDpSize <= FileSysDpSize) && (CompareMem (FileSysDp, BootOptionDp, BootOptionDpSize) == 0)) {
    return TRUE;
  }

  return FALSE;
}

/**
  Get EFI device path through EFI_SIMPLE_FILE_SYSTEM_PROTOCOL Handles buffer. Acquired path must
  point to the same device as argument DevicePath passed to the function.

  @param[in] DevicePath              Device path acquired from BootXXXX EFI variable

  @retval EFI_DEVICE_PATH_PROTOCOL   Device path for booting
**/
EFI_DEVICE_PATH_PROTOCOL *
GetFullBootDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL *DevicePath
  )
{
  EFI_STATUS               Status;
  EFI_DEVICE_PATH_PROTOCOL *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL *ReturnDevicePath;
  UINTN                    HandleNum;
  EFI_HANDLE               *HandleBuf;
  UINTN                    Index;

  ReturnDevicePath = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleFileSystemProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuf
                  );
  if ((EFI_ERROR (Status)) || (HandleBuf == NULL)) {
    return NULL;
  }

  for (Index = 0; Index < HandleNum; Index++) {
    TempDevicePath     = DevicePathFromHandle (HandleBuf[Index]);

    if (CompareDevicePaths (DevicePath, TempDevicePath)) {
      ReturnDevicePath = DuplicateDevicePath(TempDevicePath);
      break;
    }
  }

  return ReturnDevicePath;
}

/**
  Translate ASF request type to BBS or EFI device path type

  @param[in] DeviceType     ASF request type
  @param[in] Efi            TRUE if DeviceType is to be translated to EFI device path type
                            FALSE if BBS type
  @retval UINTN             Translated device type
**/
UINTN
GetBootDeviceType (
  IN UINTN    DeviceType,
  IN BOOLEAN  Efi
  )
{
  UINTN Type = 0;

  switch (DeviceType) {
    case FORCE_PXE:
      if (Efi) {
        Type = MSG_MAC_ADDR_DP;
      } else {
        Type = BBS_EMBED_NETWORK;
      }
      break;
    case FORCE_HARDDRIVE:
    case FORCE_SAFEMODE:
      if (Efi) {
        Type = MEDIA_HARDDRIVE_DP;
      } else {
        Type = BBS_TYPE_HARDDRIVE;
      }
      break;
    case FORCE_DIAGNOSTICS:
      if (Efi) {
        Type = MEDIA_PIWG_FW_FILE_DP;
      }
      break;
    case FORCE_CDDVD:
      if (Efi) {
        Type = MEDIA_CDROM_DP;
      } else {
        Type = BBS_TYPE_CDROM;
      }
      break;
    default:
      break;
  }

  return Type;
}

/**
  Update the BBS table with our required boot device

  @param[in]  BbsIndex    Index of BBS_TABLE structures
  @param[out] IsUsbr      Set to TRUE if this is USBR device path

  @retval EFI_SUCCESS     BBS table successfully updated
**/
EFI_STATUS
ProcessBbsTable (
  IN UINT16     BbsIndex,
  OUT BOOLEAN   *IsUsbr
  )
{
  return EFI_NOT_FOUND;
}

/**
  Build the Device Path for this boot selection

  @param[in] BootOptions   Boot Option data pointer
  @param[in] OptionCount   Boot Option count
  @param[in] DeviceType    Boot device whose device type
  @param[in] DeviceIndex   Boot device whose device index
  @param[in] UsbrBoot      If UsbrBoot is TRUE then check USBr device
  @param[in] EfiBoot       Set to TRUE if this is EFI boot

  @retval BootDeviceIndex  Index of Boot Device
**/
UINTN
GetBootOptionIndex (
  IN EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions,
  IN UINTN                        OptionCount,
  IN UINT16                       DeviceType,
  IN UINT16                       DeviceIndex,
  IN BOOLEAN                      UsbrBoot,
  IN BOOLEAN                      EfiBoot
  )
{
  EFI_DEVICE_PATH_PROTOCOL     *FullDevicePath;
  UINTN                        Index;
  UINTN                        TempIndex;
  EFI_DEVICE_PATH_PROTOCOL     *DevPathNode;
  UINTN                        EfiDeviceType;
  UINTN                        LegacyDeviceType;
  BOOLEAN                      TypeMatched;
  INTN                         BootDeviceIndex;
  UINTN                        EfiNodeType;

  FullDevicePath   = NULL;
  TempIndex        = 1;
  EfiDeviceType    = GetBootDeviceType (DeviceType, TRUE);
  LegacyDeviceType = GetBootDeviceType (DeviceType, FALSE);
  TypeMatched      = FALSE;
  BootDeviceIndex  = -1;
  EfiNodeType      = (EfiDeviceType == MSG_MAC_ADDR_DP) ? MESSAGING_DEVICE_PATH : MEDIA_DEVICE_PATH;

  mUsbrDevicePath.Usbr.InterfaceNumber = AsfGetStorageRedirectionBootDevice ();
  if (IsPchH ()) {
    mUsbrDevicePath.Usbr.ParentPortNumber = V_ME_PCH_H_USBR2_PORT_NUMBER;
  }

  for (Index = 0; Index < OptionCount; Index++) {
    if (DevicePathType (BootOptions[Index].FilePath) == BBS_DEVICE_PATH && DevicePathSubType (BootOptions[Index].FilePath) == BBS_BBS_DP) {
      FullDevicePath = DuplicateDevicePath (BootOptions[Index].FilePath);
    } else {
      //
      // If this is EFI boot option, we need to get full device path from EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
      // to determine type of device
      //
      FullDevicePath = GetFullBootDevicePath (BootOptions[Index].FilePath);
      if (FullDevicePath == NULL) {
        continue;
      }
    }

    DevPathNode = FullDevicePath;
    if (DevPathNode == NULL) {
      continue;
    }

    //
    // Check if this is our requested boot device
    //
    while (!IsDevicePathEnd (DevPathNode)) {
      if (UsbrBoot) {
        if (EfiBoot) {
          if (CompareDevicePaths((EFI_DEVICE_PATH_PROTOCOL*)&mUsbrDevicePath, FullDevicePath)) {
            TypeMatched = TRUE;
          }
        } else {
          //
          // USBR legacy boot, lookup BBS table to check if this is Storage Redirection boot option
          //
          ProcessBbsTable ((UINT16)*BootOptions[Index].OptionalData, &TypeMatched);
        }
      } else {
        if (DevicePathType (DevPathNode) == BBS_DEVICE_PATH && DevicePathSubType (DevPathNode) == BBS_BBS_DP) {
          //
          // Legacy boot option
          //
          if (((BBS_BBS_DEVICE_PATH *)DevPathNode)->DeviceType == LegacyDeviceType) {
            TypeMatched = TRUE;
          }
        } else {
          //
          // EFI boot option
          //
          if (DevicePathType (DevPathNode) == EfiNodeType && DevicePathSubType (DevPathNode) == EfiDeviceType) {
            if (DeviceType == FORCE_DIAGNOSTICS) {
              //
              // If boot to EFI shell, find shell file by GUID
              //
              if (CompareMem (&((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)DevPathNode)->FvFileName, PcdGetPtr (PcdShellFile), sizeof(EFI_GUID))) {
                TypeMatched = TRUE;
              }
            } else {
              TypeMatched = TRUE;
            }
          }
        }
      }

      if (TypeMatched) {
        //
        // Type matched, check for device index
        //
        if (!UsbrBoot && TempIndex < DeviceIndex) {
          TempIndex++;
          TypeMatched = FALSE;
          break;
        }

        BootDeviceIndex = Index;
        //
        // Refresh BBS table if legacy option
        //
        if (DevicePathType (FullDevicePath) == BBS_DEVICE_PATH && DevicePathSubType(FullDevicePath) == BBS_BBS_DP) {
          ProcessBbsTable ((UINT16)*BootOptions[Index].OptionalData, NULL);
        }
        break;
      }

      DevPathNode = NextDevicePathNode (DevPathNode);
    }

    if (FullDevicePath != NULL) {
      FreePool (FullDevicePath);
      FullDevicePath = NULL;
    }

    if (BootDeviceIndex != -1) {
      break;
    }
  }

  return BootDeviceIndex;
}

/**
  Found out ASF boot options.

  @param[in] BootOptions               Boot Option data pointer
  @param[in] DeviceType                Boot device whose device type
  @param[in] OptionCount               Boot Option count
  @param[in] EfiBoot                   Set to TRUE if this is EFI boot

  @retval INTN                         Boot Option Index.
**/
INTN
GetAsfBootOptionIndex (
  IN EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions,
  IN UINT8                        DeviceType,
  IN UINTN                        OptionCount,
  IN BOOLEAN                      EfiBoot
  )
{
  INTN                BootOptionIndex = -1;
  UINT8               SpecialCmdParamHigh;
  UINT8               SpecialCmdParamLow;

  SpecialCmdParamHigh = AsfGetSpecialCmdParamHighByte ();
  SpecialCmdParamLow  = AsfGetSpecialCmdParamLowByte ();

  //
  // First we check ASF boot options Special Command
  //
  switch (DeviceType) {
  //
  // The Special Command Parameter can be used to specify a PXE
  // parameter. When the parameter value is 0, the system default PXE device is booted. All
  // other values for the PXE parameter are reserved for future definition by this specification.
  //
  case FORCE_PXE:
  case FORCE_DIAGNOSTICS:
    if ((SpecialCmdParamHigh != 0) || (SpecialCmdParamLow != 0)) {
      //
      // ASF spec says 0 currently is the only option
      //
      break;
    }

    //
    // We want everything connected up for PXE or EFI shell
    //
    EfiBootManagerConnectAll ();
    BootOptionIndex = GetBootOptionIndex (BootOptions, OptionCount, DeviceType, SpecialCmdParamHigh, FALSE, EfiBoot);
    break;

  //
  // The Special Command Parameter identifies the boot-media index for
  // the managed client. When the parameter value is 0, the default hard-drive/optical drive is booted, when the
  // parameter value is 1, the primary hard-drive/optical drive is booted; when the value is 2, the secondary
  // hard-drive/optical drive is booted and so on.
  //
  case FORCE_HARDDRIVE:
  case FORCE_SAFEMODE:
  case FORCE_CDDVD:
    BootOptionIndex = GetBootOptionIndex (BootOptions, OptionCount, DeviceType, SpecialCmdParamHigh, FALSE, EfiBoot);
    break;

  //
  // No additional special command is included; the Special Command Parameter has no
  // meaning.
  //
  case NOP:
  default:
    break;
  }

  return BootOptionIndex;
}

/**
  Check Storage Redirection boot device and Asf boot device

  @param[in] BootOptions   Boot Option data pointer
  @param[in] OptionCount   Boot Option count
  @param[in] EfiBoot       Set to TRUE if this is EFI boot

  @retval INTN             Boot Option Index.
**/
INTN
GetForcedBootOptionIndex (
  IN EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions,
  IN UINTN                        OptionCount,
  IN BOOLEAN                      EfiBoot
  )
{
  INTN                BootOptionIndex = -1;
  UINT8               SpecialCommand;

  SpecialCommand = AsfGetSpecialCommand ();

  //
  // OEM command values; the interpretation of the Special Command and associated Special
  // Command Parameters is defined by the entity associated with the Enterprise ID.
  //
  if (AsfIsStorageRedirectionEnabled ()) {
    BootOptionIndex = GetBootOptionIndex (
                        BootOptions,
                        OptionCount,
                        FORCE_CDDVD,
                        0,
                        TRUE,
                        EfiBoot
                        );
  } else if (!AsfIsIndustryIanaId ()) {
    BootOptionIndex = GetAsfBootOptionIndex (
                        BootOptions,
                        SpecialCommand,
                        OptionCount,
                        EfiBoot
                        );
  }

  return BootOptionIndex;
}

/**
  Process ASF boot options and if available, attempt the boot

  @retval EFI_SUCCESS    The command completed successfully
**/
EFI_STATUS
BdsBootViaAsf (
  VOID
  )
{
  EFI_STATUS                   Status;
  EFI_BOOT_MANAGER_LOAD_OPTION *BootOptions;
  UINTN                        OptionCount;
  INTN                         BootOptionIndex;
  BOOLEAN                      EfiBoot;
  EFI_INPUT_KEY                Key = {0};
  UINTN                        EventIndex;
  EFI_TPL                      OldTpl;

  Status          = EFI_SUCCESS;
  BootOptions     = NULL;
  EfiBoot         = TRUE;

  //
  // Check if ASF Boot Options is present.
  //
  if (!AsfIsBootOptionsPresent ()) {
    return EFI_NOT_FOUND;
  }

  BootOptions = EfiBootManagerGetLoadOptions (&OptionCount, LoadOptionTypeBoot);
  if (BootOptions == NULL) {
    return EFI_UNSUPPORTED;
  }

  BootOptionIndex = GetForcedBootOptionIndex (BootOptions, OptionCount, EfiBoot);
  //
  // If device path was set, the we have a boot option to use
  //
  if (BootOptionIndex == -1) {
    return EFI_UNSUPPORTED;
  }

  //
  // If this is RCO/Storage Redirection EFI Boot, keep trying unless user cancels
  //
  while (!(Key.ScanCode == SCAN_ESC && Key.UnicodeChar == 0)) {
    EfiBootManagerBoot (&BootOptions[BootOptionIndex]);
    //
    // Returning from EfiBootManagerBoot means the boot failed
    // Display message to user before attempting another RCO/Storage Redirection boot
    //
    gST->ConOut->ClearScreen (gST->ConOut);
    gST->ConOut->OutputString (
                  gST->ConOut,
                  L"RCO/USBR boot failed. Press ENTER to try again or ESC to return to regular boot\r\n"
                  );
    Key.ScanCode    = 0;
    Key.UnicodeChar = 0;
    OldTpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);
    gBS->RestoreTPL (TPL_APPLICATION);
    while (!(Key.ScanCode == 0 && Key.UnicodeChar == L'\r')) {
      gBS->WaitForEvent (1, &(gST->ConIn->WaitForKey), &EventIndex);
      gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);

      if (Key.ScanCode == SCAN_ESC && Key.UnicodeChar == 0) {
        break;
      }
    }

    if (OldTpl > TPL_APPLICATION) {
      gBS->RaiseTPL (OldTpl);
    }
  }

  EfiBootManagerFreeLoadOptions (BootOptions, OptionCount);

  return Status;
}

