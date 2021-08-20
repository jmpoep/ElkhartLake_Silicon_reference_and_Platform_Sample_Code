/** @file
  The header file includes the definition of AMT_WRAPPER_PROTOCOL.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#ifndef _AMT_WRAPPER_PROTOCOL_H_
#define _AMT_WRAPPER_PROTOCOL_H_

#define AMT_WRAPPER_PROTOCOL_GUID \
  {0xd54f49f6, 0x0dd4, 0x4276, {0xb0, 0x9c, 0xdf, 0xe1, 0xfd, 0x80, 0x85, 0xf0}}

/**
  Get Serial Over Lan Device Path

  @param[in, out] DevicePath      Device Path of Serial Over Lan

  @retval True                    Index is supported.
  @retval False                   Index is not supported.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_GET) (
  IN OUT VOID  *DevicePath
);

/**
  Setting for AMT wrapper

  @param[in] Index                Setting index

  @retval True                    Required setting is supported.
  @retval False                   Required setting is not supported.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_SET) (
  IN UINTN     Index
);

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_ENABLE_KVM) (
  VOID
);

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_ENABLE_SOL) (
  VOID
);

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_ENABLE_STORAGE_REDIR) (
  VOID
);

/**
  Check if ASF boot options is present.

  @retval True                    ASF boot option is present.
  @retval False                   ASF boot option is not present
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_BOOT_OPTION_EXIST) (
  VOID
);

/**
  Process ASF boot options and if available, attempt the boot

  @retval EFI_SUCCESS    The command completed successfully
**/
typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_BDS_BOOT_VIA_ASF) (
  VOID
);

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_PAUSE_BOOT) (
  VOID
);

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_ENTER_SETUP) (
  VOID
);

/**
  This will return Console Lock Boot Option.
  True if the option is enabled.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_CONSOLE_LOCKED) (
  VOID
);

/**
  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
typedef
BOOLEAN
(EFIAPI *AMT_WRAPPER_ENABLE_SECURE_ERASE) (
  VOID
);

/**
  Get Next Setup Promt String.

  @param[out] String            Setup promt string.

  @retval EFI_SUCCESS           Get Setup Promt String successfully.
  @retval EFI_NOT_FOUND         Setup Promt String is not found.
**/
typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_GET_NEXT_SETUP_PROMPT) (
  OUT     CHAR16    **String
);

/**
  Determine if AMT hot key is pressed.

  @param[in] KeyData            Hot Key Data.

  @retval EFI_SUCCESS           AMT hot key is pressed.
  @retval EFI_NOT_FOUND         AMT hot key is not pressed.
**/
typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_DETERMINE_SETUP_HOTKEY) (
  IN  EFI_KEY_DATA              *KeyData
);

/**
  Get Supported Hot Keys.

  @param[out] KeyCnt            Supported Hot Key Count.
  @param[out] KeyData           Supported Hot Key Data.

  @retval EFI_SUCCESS           Get Supported Hot Keys Successfully.
  @retval EFI_NOT_FOUND         No Supported Hot Keys.
**/
typedef
EFI_STATUS
(EFIAPI *AMT_WRAPPER_GET_SUPPORTED_HOTKEYS) (
  OUT  UINTN             *KeyCnt,
  OUT  EFI_KEY_DATA      **KeyData
  );

///
/// This protocol abstracts interface for AMT functions.
///
typedef struct _AMT_WRAPPER_PROTOCOL {
  AMT_WRAPPER_GET                         Get;
  AMT_WRAPPER_SET                         Set;
  AMT_WRAPPER_BOOT_OPTION_EXIST           BootOptionExist;
  AMT_WRAPPER_ENABLE_STORAGE_REDIR        IsStorageRedirectionEnabled;
  AMT_WRAPPER_ENTER_SETUP                 IsEnterSetupEnabled;
  AMT_WRAPPER_PAUSE_BOOT                  IsPauseBootEnabled;
  AMT_WRAPPER_ENABLE_KVM                  IsKvmEnabled;
  AMT_WRAPPER_ENABLE_SECURE_ERASE         IsSecureEraseEnabled;
  AMT_WRAPPER_CONSOLE_LOCKED              IsConsoleLocked;
  AMT_WRAPPER_ENABLE_SOL                  IsSolEnabled;
  AMT_WRAPPER_BDS_BOOT_VIA_ASF            BdsBootViaAsf;
  AMT_WRAPPER_GET_NEXT_SETUP_PROMPT       GetNextSetupPrompt;
  AMT_WRAPPER_DETERMINE_SETUP_HOTKEY      DetermineSetupHotKey;
  AMT_WRAPPER_GET_SUPPORTED_HOTKEYS       GetSupportedHotkeys;
} AMT_WRAPPER_PROTOCOL;

#define SET_BIOS_WDT_START 1
#define SET_WDT_STOP       2
#define SET_OS_WDT_START   3

#endif
