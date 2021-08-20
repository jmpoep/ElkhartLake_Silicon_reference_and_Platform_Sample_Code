/** @file
  Initializes Serial IO Controllers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include <Ppi/SiPolicy.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchPcrLib.h>
#include <Library/SiScheduleResetLib.h>
#include <Library/PchInfoLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Register/PchPcrRegs.h>
#include <PchResetPlatformSpecific.h>
#include "PeiSerialIoInitPrivateLib.h"

/**
  Configures Serial IO Controllers

  @param[in] SiPolicy

**/
VOID
SerialIoInit (
  IN SI_POLICY_PPI           *SiPolicy
  )
{
  UINT8                       Index;
  EFI_STATUS                  Status;
  SERIAL_IO_CONFIG            *SerialIoConfig;
  PCH_RESET_DATA              ResetData;
  BOOLEAN                     IsSerialIoDisabled;
  BOOLEAN                     DisableSerialIo;

  DEBUG ((DEBUG_INFO, "SerialIoInit() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);

  IsSerialIoDisabled = PmcIsSerialIoStaticallyDisabled ();

  if (!IsSerialIoDisabled) {
    //
    // enable clock gating and power gating
    //
    PchPcrAndThenOr32 (PID_SERIALIO, R_SERIAL_IO_PCR_GPPRVRW2, 0xFFFFFFFF, V_SERIAL_IO_PCR_GPPRVRW2_CLK_GATING);
    PchPcrAndThenOr32 (PID_SERIALIO, R_SERIAL_IO_PCR_PMCTL   , 0xFFFFFFFF, V_SERIAL_IO_PCR_PMCTL_PWR_GATING);

    SerialIoSpiInit  (SiPolicy, SerialIoConfig);
    SerialIoI2cInit  (SiPolicy, SerialIoConfig);
    SerialIoUartInit (SiPolicy, SerialIoConfig);
  }

  //
  // Check if all SerialIo controllers should be disabled in PMC
  //
  DisableSerialIo = TRUE;

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    if (SerialIoConfig->SpiDeviceConfig[Index].Mode != SerialIoSpiDisabled) {
      DisableSerialIo = FALSE;
    }
  }

  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    if (SerialIoConfig->I2cDeviceConfig[Index].Mode != SerialIoI2cDisabled) {
      DisableSerialIo = FALSE;
    }
  }

  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    if (SerialIoConfig->UartDeviceConfig[Index].Mode != SerialIoUartDisabled) {
      DisableSerialIo = FALSE;
    }
  }

  if (DisableSerialIo && !IsSerialIoDisabled) {
    //
    // If all SertialIo controllers are disabled do static power gating in PMC
    //
    PmcStaticDisableSerialIo ();
  } else if (!DisableSerialIo && IsSerialIoDisabled) {
    //
    // If at least one SertialIo controller is to be used remove static power gating in PMC
    //
    PmcEnableSerialIo ();
  }

  //
  // Trigger reset if SerialIo static power gating state has to be changed
  //
  if (IsSerialIoDisabled != DisableSerialIo) {
    DEBUG ((DEBUG_INFO, "Reset due to changes in SerialIo FunctionDisable\n"));
    CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
    SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
  }

  DEBUG ((DEBUG_INFO, "SerialIoInit() End\n"));
}

/**
  Configures Serial IO Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy

**/
VOID
SerialIoFunction0Disable (
  IN SI_POLICY_PPI           *SiPolicy
  )
{
  SERIAL_IO_CONFIG            *SerialIoConfig;
  EFI_STATUS                  Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);

  SerialIoSpiFunction0Disable  (SiPolicy, SerialIoConfig);
  SerialIoI2cFunction0Disable  (SiPolicy, SerialIoConfig);
  SerialIoUartFunction0Disable (SiPolicy, SerialIoConfig);
}

