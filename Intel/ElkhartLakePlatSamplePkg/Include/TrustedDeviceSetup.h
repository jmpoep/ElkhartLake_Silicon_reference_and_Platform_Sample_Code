/** @file
  Intel Trusted Device Setup library services.

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

@par Specification Reference:
**/

#ifndef _TRUSTED_DEVICE_SETUP_H_
#define _TRUSTED_DEVICE_SETUP_H_

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Protocol/TrustedDeviceSetupMainProtocol.h>

//
// These define the BIOS Intel Trusted Device Setup Capabilities for SMBIOS table 131
//
#define TRUSTED_DEVICE_SETUP_MEASURED_BOOT_CAPABLE     1
#define TRUSTED_DEVICE_SETUP_BOOT_SETUP_LOCK_CAPABLE   1
#define TRUSTED_DEVICE_SETUP_CHASSIS_INTRUSION_CAPABLE 1

#define TRUSTED_DEVICE_SETUP_BOOT_ENABLE   BIT14 ///< 0100 0000 0000 0000 - bit 14
#define TRUSTED_DEVICE_SETUP_BOOT_LOCK     BIT15 ///< 1000 0000 0000 0000 - bit 15

typedef struct {
  UINT32  Presvered1          : 6;    ///< [5:0]  Preserved, do not modify
  UINT32  TdsMeasuredBoot     : 1;    ///< [6]    BIOS supports Intel Trusted Device Setup Measured Boot
  UINT32  TdsBiosLock         : 1;    ///< [7]    BIOS supports Intel Trusted Device Setup Boot and Setup Lock
  UINT32  TdsChassisIntrusion : 1;    ///< [8]    BIOS supports Intel Trusted Device Setup Chassis Intrusion
  UINT32  Reserved4           : 23;   ///< [31:9] Reserved, must be set to 0
} TDS_BIOS_CAP;

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
  );

/**
  Function to check whether or not this is a Intel Trusted Device Setup boot

  @param[in] Param                    BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval TRUE                        This is a Trusted Device Setup Boot
  @retval FALSE                       This is NOT a Trusted Device Setup Boot
**/
BOOLEAN
IsTrustedDeviceSetupBoot (
  IN UINT16  Param
  );

/**
  Function to check if Intel Trusted Device Setup BootLock enabled

  @param[in] Param                    BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.

  @retval TRUE                        This is a Trusted Device Setup Boot
  @retval FALSE                       This is NOT a Trusted Device Setup Boot
**/
BOOLEAN
IsTrustedDeviceSetupBootLock (
  IN UINT16  Param
  );

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
  );

/**
  This function determines if chassis intrusion detection is enabled

  @retval TRUE      Chassis intrusion detection is enabled
  @retval FALSE     Chassis intrusion detection is not enabled
**/
BOOLEAN
EFIAPI
TrustedDeviceSetupChassisIntrusionEnabled (
  VOID
  );

/**
  This function checks the status of the chassis intrusion detection pin

  @retval TRUE      Chassis intrusion has been detected
  @retval FALSE     Chassis intrusion has not been detected
**/
BOOLEAN
EFIAPI
TrustedDeviceSetupChassisIntrusionDetected (
  VOID
  );

/**
  Installs the protocol provided for the PBA to determine chassis intrusion capability and status

  @retval EFI_SUCCESS  The protocol has been successfully installed
  @retval Others       An error has occurred and the protocol was not published
**/
EFI_STATUS
EFIAPI
InstallTrustedDeviceSetupExtensionProtocol (
  VOID
  );

/**
  Suppress user input by removing ConIn
  In order for this ConIn removal to correctly remove input, no ConIn variable shall be added after this function runs.

  @retval EFI_SUCCESS    ConIn has been set to NULL
  @retval Other          Error setting ConIn to NULL
**/
EFI_STATUS
EFIAPI
SuppressUserInput (
  VOID
  );

/**
  Add Keyboard Function

  @retval EFI_SUCCESS Keyboard functionality has successfully been added.
  @retval EFI_UNSUPPORTED Keyboard functionality addition is not supported
  @retval Others Adding keyboard functionality has failed
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupAddKeyboard (
  VOID
  );

/**
  Remove Keyboard Function

  @retval EFI_SUCCESS Keyboard functionality has successfully been removed.
  @retval EFI_UNSUPPORTED Keyboard functionality removal is not supported
  @retval Others Removing keyboard functionality has failed
**/
EFI_STATUS
EFIAPI
TrustedDeviceSetupRemoveKeyboard (
  VOID
  );
#endif
