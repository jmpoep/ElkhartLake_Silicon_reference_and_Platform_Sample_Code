/** @file
  AMT Wrapper include file

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

#ifndef _AMT_WRAPPER_DXE_H_
#define _AMT_WRAPPER_DXE_H_

#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/AmtWrapperProtocol.h>
#include <Protocol/AsfProtocol.h>
#include <Protocol/LegacyBios.h>
#include <Library/DxeAmtHeciLib.h>
#include <Library/DxeAsfLib.h>
#include <Register/MeRegs.h>
#include <Protocol/AmtPolicy.h>
#include <Protocol/HeciProtocol.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include <MebxDataHob.h>
#include <AmtConfig.h>

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           SerialOverLAN;
  UART_DEVICE_PATH          Uart;
  VENDOR_DEVICE_PATH        TerminalType;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH;

#define gPciRootBridge \
  { \
    { \
      ACPI_DEVICE_PATH, \
      ACPI_DP, \
      { \
        (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), \
        (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8) \
      } \
    }, \
    EISA_PNP_ID (0x0A03), 0 \
  }

#define gEndEntire \
  { \
    END_DEVICE_PATH_TYPE,\
    END_ENTIRE_DEVICE_PATH_SUBTYPE,\
    { \
      END_DEVICE_PATH_LENGTH,\
      0 \
    } \
  }

/**
  Get Serial Over Lan Device Path

  @param[in, out] DevicePath      Device Path of Serial Over Lan

  @retval True                    Get SOL Device Path Successful.
**/
BOOLEAN
EFIAPI
AmtWrapperGetSolDevicePath (
  IN OUT VOID  *DevicePath
  );

/**
  Setting for AMT wrapper

  @param[in] Index                Setting index

  @retval True                    Required setting is supported.
  @retval False                   Required setting is not supported.
**/
BOOLEAN
EFIAPI
AmtWrapperSet (
  IN UINTN     Index
  );

/**
  Check if ASF boot options is present.

  @retval True                    ASF boot option is present.
  @retval False                   ASF boot option is not present
**/
BOOLEAN
EFIAPI
AmtWrapperBootOptionExist (
  VOID
  );

/**
  This will return Storage Redirection Boot Option.
  True if the option is enabled.

  @retval True                    Storage Redirection boot option is enabled.
  @retval False                   Storage Redirection boot option is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableStorageRedir (
  VOID
  );

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnterSetup (
  VOID
  );

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperPauseBoot (
  VOID
  );

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableKvm (
  VOID
  );

/**
  This will return Secure Erase Boot Option.
  True if the option is enabled.

  @retval True                    Secure Erase is enabled.
  @retval False                   Secure Erase is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableSecureErase (
  VOID
  );

/**
  This will return Console Lock Boot Option.
  True if the option is enabled.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperConsoleLocked (
  VOID
  );

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
EFIAPI
AmtWrapperEnableSol (
  VOID
  );

/**
  Process ASF boot options and if available, attempt the boot

  @retval EFI_SUCCESS    The command completed successfully
**/
EFI_STATUS
EFIAPI
AmtWrapperBdsBootViaAsf (
  VOID
  );

/**
  Process ASF boot options and if available, attempt the boot

  @retval EFI_SUCCESS    The command completed successfully
**/
EFI_STATUS
BdsBootViaAsf (
  VOID
  );

/**
  Get AMT Setup Promt String.

  @param[out] String            Setup promt string.

  @retval EFI_SUCCESS           Get Setup Promt String successfully.
  @retval EFI_NOT_FOUND         Setup Promt String is not found.
  @retval EFI_UNSUPPORTED       Get Setup Promt String is not supported.
  @retval EFI_INVALID_PARAMETER One of parameters is NULL.
**/
EFI_STATUS
EFIAPI
AmtWrapperGetNextAmtSetupPrompt (
  OUT     CHAR16    **String
  );


/**
  Determine if AMT hot key is pressed.
  Ctrl+ALT+F1  : Scan    = 0x0B, Shift = 0x3C
  Ctrl+P       : Unicode = 0x10/L'p', Shift = 0x0C

  @param[in] KeyData            Hot Key Data.

  @retval EFI_SUCCESS           AMT hot key is pressed.
  @retval EFI_NOT_FOUND         AMT hot key is not pressed.
**/
EFI_STATUS
EFIAPI
AmtWrapperDetermineSetupHotKey (
  IN EFI_KEY_DATA       *KeyData
  );

/**
  Get Supported Hot Keys.

  @param[out] KeyCnt            Supported Hot Key Count.
  @param[out] KeyData           Supported Hot Key Data.

  @retval EFI_SUCCESS           Get Supported Hot Keys Successfully.
  @retval EFI_OUT_OF_RESOURCES  Out of memory.
  @retval EFI_NOT_FOUND         No Supported Hot Keys.
**/
EFI_STATUS
EFIAPI
AmtWrapperGetSupportedHotkeys (
  OUT  UINTN             *KeyCnt,
  OUT  EFI_KEY_DATA      **KeyData
  );

/**
  This routine makes necessary Secure Boot & CSM state changes for Storage Redirection boot

  @retval EFI_SUCCESS      Changes applied succesfully
**/
EFI_STATUS
ManageSecureBootState (
  VOID
  );

#endif
