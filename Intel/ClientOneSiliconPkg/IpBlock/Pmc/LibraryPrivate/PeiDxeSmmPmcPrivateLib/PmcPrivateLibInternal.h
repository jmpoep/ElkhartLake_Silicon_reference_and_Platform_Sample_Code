/** @file
  Internal header file for PMC Private library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _PMC_PRIVATE_LIB_INTERNAL_H_
#define _PMC_PRIVATE_LIB_INTERNAL_H_

#include <PmConfig.h>

/**
  S0ix settings

  @param[in] PmConfig                     PmConfig
**/
VOID
PmcSlpS0Config (
  IN PCH_PM_CONFIG                        *PmConfig
  );

/**
  Check if MODPHY SUS PG is supported

  @retval  Status of MODPHY SUS PG support
**/
BOOLEAN
PmcIsModPhySusPgSupported (
  VOID
  );

/**
  This function is part of PMC init and configures which clock wake signals should
  set the SLOW_RING, SA, FAST_RING_CF and SLOW_RING_CF indication sent up to the CPU/PCH
**/
VOID
PmcInitClockWakeEnable (
  VOID
  );

/**
  Configures PM_SYNC state hysteresis according to IP recommendation
  for SoC.
**/
VOID
PmcConfigurePmSyncHysteresis (
  VOID
  );

/**
  This function configures PWRMBASE + 0x1E00 register
**/
VOID
PmcConfigureRegPwrm1E00 (
  VOID
  );

/**
  Configure CPPM Force Alignment Control
**/
VOID
PmcConfigureCppmForceAlignmentControl (
  VOID
  );

/**
  Configure Low Power Mode S0ix sub-state support

  @param[in] PmConfig                 PmConfig
**/
VOID
PmcConfigureLpmS0ixSupport (
  IN PCH_PM_CONFIG  *PmConfig
  );

/**
  Enable ModPHY SUS Power Gating
**/
VOID
EnableModPhySusWellPg (
  VOID
  );

/**
  Enable OS IDLE Mode
**/
VOID
PmcEnableOsIdleMode (
  VOID
  );

/**
  Check if OS IDLE Mode is supported by PCH

  @retval OS IDLE Mode support state
**/
BOOLEAN
PmcIsOsIdleModeSupported (
  VOID
  );

/**
  Lock OS IDLE Mode register
**/
VOID
PmcLockOsIdleMode (
  VOID
  );

/**
  This function configures PCH FIVR FET Ramp time config
**/
VOID
PmcFivrFetRampTimeConfig (
  VOID
  );

/**
  Restore Bus Master Enable (BME) bit in PMC device (clear the bit) after PCIe enumaration.

  Read from PMC Command register always returns 0 on I/O enable bit (bit 0).
  Use read/modify/write procedure to PMC Command register causes erasing I/O space enable bit that disables ACPI I/O space.
  PCIe enumerators can use such method and can override I/O enable bit.
  To prevent I/O space disabling by enumerators Bus Master Enable (BME) bit should be set.
  In this case enumerator skips the device during enumeration.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               Cannot access PMC device.
**/
EFI_STATUS
PmcEnableIOSpaceAndBusMaster (
  VOID
  );

/**
  Get the CPU IOVR ramp duration POR for the SoC

  @retval Ramp duration in the unit of 10us
**/
UINT8
PmcGetCpuIovrRampDuration (
  VOID
  );

/**
  Pmc miscellaneous configuration at end of PEI
**/
VOID
PmcMiscConfig (
  VOID
  );

#endif
