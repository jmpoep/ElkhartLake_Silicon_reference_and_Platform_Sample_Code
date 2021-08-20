/** @file
  Intel Trusted Device Setup OEM Implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 -2019 Intel Corporation.

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
#include <Library/PciSegmentLib.h>
#include <TrustedDeviceSetupExtensionProtocol.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiBootManagerLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_DEVICE_PATH_PROTOCOL  *ConInDevPath = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                     ConInSize = 0;

#define TDS_BOOT_OPTION_SUPPORT_KEY_MASK 0xFFFFFFFE

extern UINT16 mTrustedDeviceSetupParameter;

/**
Removes the ability to boot a Boot#### option from its associated Key#### option by setting
EFI_BOOT_OPTION_SUPPORT_KEY of BootOptionSupport global variable to 0.

NOTE: Implementation assumes that boot manager reinitializes/sets BootOptionSupport variable
every boot. If it does not, this function will permanently disable booting from Key####

@retval EFI_SUCCESS           Set BIT0 of EFI_BOOT_OPTION_SUPPORT to 0
@retval EFI_NOT_FOUND         Could not locate the BootOptionSupport Variable
@retval Others                Failed to set BIT0 of EFI_BOOT_OPTION_SUPPORT to 0
**/
EFI_STATUS
EFIAPI
RemoveBootFromKeyOption (
  VOID
)
{
  EFI_STATUS  Status;
  UINT32      *BootOptionSupport;
  UINT32      NewBootOptionSupport;



  NewBootOptionSupport = 0;

  Status = GetEfiGlobalVariable2 (EFI_BOOT_OPTION_SUPPORT_VARIABLE_NAME, (VOID **) &BootOptionSupport, NULL);
  if (BootOptionSupport == NULL)
  {
    DEBUG ((DEBUG_ERROR, "EFI_BOOT_OPTION_SUPPORT_VARIABLE_NAME NOT FOUND\n"));
    ASSERT (BootOptionSupport != NULL);
    return EFI_NOT_FOUND;
  }

  //
  // Set EFI_BOOT_OPTION_SUPPORT_KEY (BIT0 of BootOptionSupport) to O
  //
  NewBootOptionSupport = *BootOptionSupport & TDS_BOOT_OPTION_SUPPORT_KEY_MASK;

  Status = gRT->SetVariable (
                  EFI_BOOT_OPTION_SUPPORT_VARIABLE_NAME,
                  &gEfiGlobalVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof (NewBootOptionSupport),
                  &NewBootOptionSupport
                  );

  FreePool (BootOptionSupport);

  return Status;
}

/**
Suppress user input by removing ConIn and disabling boot by Key####
In order for this ConIn removal to correctly remove input, no ConIn variable shall be added after this function runs.

@retval EFI_SUCCESS    ConIn has been set to NULL and EFI_BOOT_OPTION_SUPPORT_KEY has been set to 0
@retval EFI_ABORTED    Error setting ConIn to NULL and/or EFI_BOOT_OPTION_SUPPORT_KEY to 0
**/
EFI_STATUS
EFIAPI
SuppressUserInput (
  VOID
  )
{
  EFI_STATUS  ConInStatus;
  EFI_STATUS  BootKeyStatus;

  //
  // Save ConIn so it can be restored during AddKeyboard ()
  // Remove all device path from ConIn by setting ConIn to NULL.
  // BIOS should not enumerate any input devices when Windows Console behavior is used
  //
  GetEfiGlobalVariable2 (L"ConIn", (VOID **) &ConInDevPath, &ConInSize);
  ConInStatus = gRT->SetVariable (
                       L"ConIn",
                       &gEfiGlobalVariableGuid,
                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                       0,
                       NULL
                       );

  PcdSetBoolS (PcdConInConnectOnDemand, TRUE); // Do not display pop up screen for hotkeys
  BootKeyStatus = RemoveBootFromKeyOption ();  // Disable EFI_BOOT_OPTION_SUPPORT_KEY

  //
  // Return EFI_SUCCESS if all subfunctions executed properly.
  // Return EFI_ABORTED for any error detected.
  //
  if (!EFI_ERROR (ConInStatus) && !EFI_ERROR (BootKeyStatus)) {
    return EFI_SUCCESS;
  } else {
    return EFI_ABORTED;
  }
}

/**
  Update SMBIOS table 131 with Intel Trusted Device Setup BIOS capabilities

  Function sets whether BIOS supports the enhanced measured boot feature,
  the Trusted Device Setup boot and setup lock feature, and chassis intrusion detection.

  @param[in, out] RecordData               Structure of SMBIOS record to be updated wtih Trusted Device Setup capabilities.
**/
VOID
EFIAPI
UpdateSmbiosTrustedDeviceSetupCapabilities (
  IN OUT VOID           *RecordData
  )
{
  ((TDS_BIOS_CAP*)RecordData)->TdsMeasuredBoot     = TRUSTED_DEVICE_SETUP_MEASURED_BOOT_CAPABLE;
  ((TDS_BIOS_CAP*)RecordData)->TdsBiosLock         = TRUSTED_DEVICE_SETUP_BOOT_SETUP_LOCK_CAPABLE;
  ((TDS_BIOS_CAP*)RecordData)->TdsChassisIntrusion = TRUSTED_DEVICE_SETUP_CHASSIS_INTRUSION_CAPABLE;
  DEBUG((DEBUG_INFO, "UpdateSmbiosTrustedDeviceSetupCapabilities\n"));
}

/**
  This function determines if chassis intrusion detection is enabled

  @retval TRUE      Chassis intrusion detection is enabled
  @retval FALSE     Chassis intrusion detection is not enabled
**/
BOOLEAN
EFIAPI
TrustedDeviceSetupChassisIntrusionEnabled (
  VOID
  )
{
  return TRUSTED_DEVICE_SETUP_CHASSIS_INTRUSION_CAPABLE;
}

/**
  This function checks the status of the chassis intrusion detection pin

  @retval TRUE      Chassis intrusion has been detected
  @retval FALSE     Chassis intrusion has not been detected
**/
BOOLEAN
EFIAPI
TrustedDeviceSetupChassisIntrusionDetected (
  VOID
  )
{
  return ((mTrustedDeviceSetupParameter & BIT0) == BIT0);
}

/**
  Add Keyboard Function

  @retval EFI_SUCCESS     Keyboard functionality has successfully been added.
  @retval EFI_UNSUPPORTED Keyboard functionality addition is not supported
  @retval EFI_NOT_FOUND   ConIn did not exist so it cannot be added
  @retval Others          Adding keyboard functionality has failed
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupAddKeyboard (
  VOID
  )
{
  if (ConInSize == 0 || ConInDevPath == NULL) {
    return EFI_NOT_FOUND;
  }

  EFI_STATUS Status;
  Status = gRT->SetVariable (
                  L"ConIn",
                  &gPlatformGlobalVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                  ConInSize,
                  ConInDevPath
                  );

  return Status;
}

/**
  Remove Keyboard Function

  @retval EFI_SUCCESS     Keyboard functionality has successfully been removed.
  @retval EFI_UNSUPPORTED Keyboard functionality removal is not supported
  @retval Others          Removing keyboard functionality has failed
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupRemoveKeyboard (
  VOID
  )
{
  EFI_STATUS Status;
  Status = SuppressUserInput();
  return Status;
}

