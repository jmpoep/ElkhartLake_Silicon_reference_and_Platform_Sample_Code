/** @file
  Hardware Monitor entry point.

@copyright
  Copyright (c) 2013-2015, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor. This file may be modified by the user, subject to
  the additional terms of the license agreement.
**/

#include "Config.h"
#include "HwMonInit.h"

/**
  The user Entry Point for module Nct6776fHwMon. The user code starts
  with this function.

  @param[in]  ImageHandle    The firmware allocated handle for the EFI image.
  @param[in]  SystemTable    A pointer to the EFI System Table.

  @retval     EFI_SUCCESS    The entry point is executed successfully.
  @retval     other          Some error occurs when executing this entry point.
**/
EFI_STATUS
EFIAPI
NctHwMonEntryPoint (
  IN  EFI_HANDLE           ImageHandle,
  IN  EFI_SYSTEM_TABLE     *SystemTable
  )
{

  EFI_BOOT_SERVICES      *gBS;
  NCT6776F_HWMON_PROTOCOL *HwMonProtocol;
  EFI_STATUS              Status;

  //
  // Locate the protocol published by the Nct6776f SIO module.
  //

  gBS = SystemTable->BootServices;
  Status = gBS->LocateProtocol(&gNct6776fHwMonProtocolGuid, NULL, &HwMonProtocol);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Ask the Nct6776f SIO module to enable the hardware monitor within
  // the SIO.
  //
  Status = HwMonProtocol->StartMonitor();
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Do the actual programming of the hardware monitor.
  //

  HwMonInit(HwMonProtocol);             // initialize the HwMon.

  return EFI_SUCCESS;
}
