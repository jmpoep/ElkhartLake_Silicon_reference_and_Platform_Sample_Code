/** @file
  Provides platform policy services used during a capsule update.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <PiDxe.h>
#include <Library/CapsuleUpdatePolicyLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/EcMiscLib.h>
#include <SetupVariable.h>

/**
  Check platform AC status.

  @param[out]   IsAcPluggedIn          TRUE:  AC is plugged-in.
                                       FALSE: AC is not plugged-in
**/
VOID
EFIAPI
PlatformGetAcStatus (
  OUT BOOLEAN                *IsAcPluggedIn
  )
{
  UINT8                               ValTemp;
  EFI_STATUS                          Status;

  //
  // Read EC ACPI offset 0x03 [bit0] to determine if AC is present
  //
  ValTemp = 0x03;
  Status = ReadEcRam (&ValTemp);

  if (!EFI_ERROR (Status) && ((ValTemp & BIT0) == BIT0)) {
    DEBUG ((DEBUG_INFO, "PowerCheck: AC is plugged-in\n"));
    *IsAcPluggedIn = TRUE;
  } else {
    DEBUG ((DEBUG_INFO, "PowerCheck: AC is not plugged-in\n"));
    *IsAcPluggedIn = FALSE;
  }

  return;
}

/**
  Check platform battery status.

  @param[in]    RequiredCapacity       The required battery capacity.
  @param[out]   IsBatteryLow           TRUE:  Current battery capacity meets the criteria.
                                       FALSE: Current battery capacity is insufficient.
**/
VOID
EFIAPI
PlatformCheckBattery (
  IN  UINT8                  RequiredCapacity,
  OUT BOOLEAN                *IsBatteryLow
  )
{
  EFI_STATUS                           Status;
  UINT8                                BatStatus;
  BOOLEAN                              Bat1Present;
  BOOLEAN                              Bat2Present;
  UINT8                                Bat1Capacity;
  UINT8                                Bat2Capacity;

  DEBUG ((DEBUG_INFO, "PerformCheckBattery : RequiredCapacity is 0x%d\n", RequiredCapacity));

  Bat1Present  = FALSE;
  Bat2Present  = FALSE;
  Bat1Capacity = 0;
  Bat2Capacity = 0;

  //
  // Battery 1 present check and read remaining percent
  //
  BatStatus = EC_REAL_BAT1_STATUS;
  Status = ReadEcRam (&BatStatus);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Battery1 status is 0x%x\n", BatStatus));
    Bat1Present = (BatStatus & EC_REAL_BAT_PRESENT_MASK) ? TRUE : FALSE;
  }

  if (Bat1Present) {
    Bat1Capacity = EC_REAL_BAT1_REMAINING_PERCENT;
    Status = ReadEcRam (&Bat1Capacity);
    if (EFI_ERROR (Status)) {
      Bat1Capacity = 0;
    }
    DEBUG ((DEBUG_INFO, "Battery1 remaining precent is 0x%x\n", Bat1Capacity));
  }

  //
  // Battery 2 present check and read remaining percent
  //
  BatStatus = EC_REAL_BAT2_STATUS;
  Status = ReadEcRam (&BatStatus);
  if (!EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "Battery2 status is 0x%x\n", BatStatus));
    Bat2Present = (BatStatus & EC_REAL_BAT_PRESENT_MASK) ? TRUE : FALSE;
  }

  if (Bat2Present) {
    Bat2Capacity = EC_REAL_BAT2_REMAINING_PERCENT;
    Status = ReadEcRam (&Bat2Capacity);
    if (EFI_ERROR (Status)) {
      Bat2Capacity = 0;
    }
    DEBUG ((DEBUG_INFO, "Battery2 remaining precent is 0x%x\n", Bat2Capacity));
  }

  //
  // Batteries capacity check
  //
  if (Bat1Present && Bat2Present) {
    // Both batteries exist
    if ((Bat1Capacity < RequiredCapacity) && (Bat2Capacity < RequiredCapacity)) {
      *IsBatteryLow = TRUE;
    } else {
      *IsBatteryLow = FALSE;
    }
  } else if (Bat1Present) {
    // Battery 1 only
    *IsBatteryLow = (Bat1Capacity < RequiredCapacity) ? TRUE : FALSE;
  } else if (Bat2Present) {
    // Battery 2 only
    *IsBatteryLow = (Bat2Capacity < RequiredCapacity) ? TRUE : FALSE;
  } else {
    // No Battery
    *IsBatteryLow = TRUE;
  }

  return;
}

/**
  Determine if the system power state supports a capsule update.

  @param[out] Good  Returns TRUE if system power state supports a capsule
                    update.  Returns FALSE if system power state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System power state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemPower (
  OUT BOOLEAN  *Good
  )
{
  EFI_STATUS                             Status;
  SETUP_DATA                             SetupData;
  UINTN                                  VariableSize;
  BOOLEAN                                IsAcPluggedIn;
  BOOLEAN                                IsBatteryLow;

  *Good = TRUE;

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );

  if (!EFI_ERROR (Status)) {
   if (SetupData.SysFwUpdateSkipPowerCheck) {
     return EFI_SUCCESS;
   }
  }

  PlatformGetAcStatus (&IsAcPluggedIn);
  PlatformCheckBattery (FixedPcdGet8 (PcdLowBatteryCheck), &IsBatteryLow);

  DEBUG ((DEBUG_INFO, "IsAcPluggedIn = 0x%x\n", IsAcPluggedIn));
  DEBUG ((DEBUG_INFO, "IsBatteryLow  = 0x%x\n", IsBatteryLow));

  if ((!IsAcPluggedIn) && (IsBatteryLow)) {
    DEBUG ((DEBUG_ERROR, "Perform SysFwUpdate PowerCheck failure.\n"));
    *Good = FALSE;
  }

  return EFI_SUCCESS;
}

/**
  Determines if the system thermal state supports a capsule update.

  @param[out] Good  Returns TRUE if system thermal state supports a capsule
                    update.  Returns FALSE if system thermal state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System thermal state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemThermal (
  OUT BOOLEAN   *Good
  )
{
  *Good = TRUE;
  return EFI_SUCCESS;
}

/**
  Determines if the system environment state supports a capsule update.

  @param[out] Good  Returns TRUE if system environment state supports a capsule
                    update.  Returns FALSE if system environment state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System environment state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemEnvironment (
  OUT BOOLEAN   *Good
  )
{
  *Good = TRUE;
  return EFI_SUCCESS;
}

/**
  Determines if the Lowest Supported Version checks should be performed.  The
  expected result from this function is TRUE.  A platform can choose to return
  FALSE (e.g. during manufacturing or servicing) to allow a capsule update to a
  version below the current Lowest Supported Version.

  @retval TRUE   The lowest supported version check is required.
  @retval FALSE  Do not perform lowest support version check.

**/
BOOLEAN
EFIAPI
IsLowestSupportedVersionCheckRequired (
  VOID
  )
{
  return TRUE;
}

/**
  Determines if the FMP device should be locked when the event specified by
  PcdFmpDeviceLockEventGuid is signaled. The expected result from this function
  is TRUE so the FMP device is always locked.  A platform can choose to return
  FALSE (e.g. during manufacturing) to allow FMP devices to remain unlocked.

  @retval TRUE   The FMP device lock action is required at lock event guid.
  @retval FALSE  Do not perform FMP device lock at lock event guid.

**/
BOOLEAN
EFIAPI
IsLockFmpDeviceAtLockEventGuidRequired (
  VOID
  )
{
  return TRUE;
}
