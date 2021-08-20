/** @file
  This file contains functions for PCH DMI SIP15

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchDmiLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchDmi15Regs.h>
#include <Register/PchPcrRegs.h>

/**
  This function checks if DMI SIP15 Secured Register Lock (SRL) is set

  @retval SRL state
**/
BOOLEAN
IsPchDmi15Locked (
  VOID
  )
{
  return ((PchPcrRead32 (PID_DMI, R_PCH_DMI15_PCR_MPC) & B_PCH_DMI15_PCR_MPC_SRL) != 0);
}

/**
  Set DMI thermal throttling to recommended configuration.
  It's intended only for PCH-H DMI SIP15.
**/
VOID
PchDmi15SetRecommendedThermalThrottling (
  VOID
  )
{
  UINT32  Data32And;
  UINT32  Data32Or;
  ///
  /// DMI recommended Thermal Sensor Target Width
  /// is the HW default configuration:
  ///  - Thermal Sensor 3 Target Width: 0 (x1)
  ///  - Thermal Sensor 2 Target Width: 1 (x2)
  ///  - Thermal Sensor 1 Target Width: 2 (x4)
  ///  - Thermal Sensor 0 Target Width: 3 (x8)
  /// Enable Thermal Sensor Autonomous Width
  ///
  Data32And = (UINT32)~(B_PCH_DMI15_PCR_UPHWAWC_TS3TW | B_PCH_DMI15_PCR_UPHWAWC_TS2TW |
                        B_PCH_DMI15_PCR_UPHWAWC_TS1TW | B_PCH_DMI15_PCR_UPHWAWC_TS0TW);
  Data32Or  = (0 << N_PCH_DMI15_PCR_UPHWAWC_TS3TW) |
              (1 << N_PCH_DMI15_PCR_UPHWAWC_TS2TW) |
              (2 << N_PCH_DMI15_PCR_UPHWAWC_TS1TW) |
              (3 << N_PCH_DMI15_PCR_UPHWAWC_TS0TW) |
              B_PCH_DMI15_PCR_UPHWAWC_TSAWEN;

  PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI15_PCR_UPHWAWC, Data32And, Data32Or);
}

/**
  Set DMI thermal throttling to custom configuration.
  This function will configure Thermal Sensor 0/1/2/3 TargetWidth and set
  DMI Thermal Sensor Autonomous Width Enable.
  It's intended only for PCH-H DMI SIP15.

  @param[in] PchDmiThermalThrottling        DMI Thermal Throttling structure.
**/
VOID
PchDmi15SetCustomThermalThrottling (
  IN PCH_DMI_THERMAL_THROTTLING      PchDmiThermalThrottling
  )
{
  UINT32  Data32And;
  UINT32  Data32Or;

  ///
  /// DMI Throttling action
  ///
  Data32And = (UINT32)~(B_PCH_DMI15_PCR_UPHWAWC_TS3TW | B_PCH_DMI15_PCR_UPHWAWC_TS2TW |
                        B_PCH_DMI15_PCR_UPHWAWC_TS1TW | B_PCH_DMI15_PCR_UPHWAWC_TS0TW);
  Data32Or  = (PchDmiThermalThrottling.ThermalSensor3TargetWidth << N_PCH_DMI15_PCR_UPHWAWC_TS3TW) |
              (PchDmiThermalThrottling.ThermalSensor2TargetWidth << N_PCH_DMI15_PCR_UPHWAWC_TS2TW) |
              (PchDmiThermalThrottling.ThermalSensor1TargetWidth << N_PCH_DMI15_PCR_UPHWAWC_TS1TW) |
              (PchDmiThermalThrottling.ThermalSensor0TargetWidth << N_PCH_DMI15_PCR_UPHWAWC_TS0TW) |
              B_PCH_DMI15_PCR_UPHWAWC_TSAWEN;

  PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI15_PCR_UPHWAWC, Data32And, Data32Or);
}

/**
  Enable PCIe Relaxed Order for DMI SIP15
**/
VOID
PchDmi15EnablePcieRelaxedOrder (
  VOID
  )
{
  //
  // Enable Forced Relaxed Ordering to always allow downstream completions to pass posted writes.
  // Set Completion Relaxed Ordering Attribute Override Value
  // and Completion Relaxed Ordering Attribute Override Enable
  //
  PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI15_PCR_PCIECFG2, ~0u, (B_PCH_DMI15_PCR_PCIECFG2_CROAOV | B_PCH_DMI15_PCR_PCIECFG2_CROAOE));
}

/**
  This function will switch SAI value to be driven to IOSF Primary Fabric
  for cycles with Core BDF from HOSTIA_BOOT_SAI to HOSTIA_POSTBOOT_SAI.
  To be used when PCH is paired with CFL CPU.
**/
VOID
PchDmi15EnablePostBootSai (
  VOID
  )
{
  PchPcrAndThenOr32 (
    PID_DMI,
    R_PCH_DMI15_PCR_CTRL1,
    ~0u,
    B_PCH_DMI15_PCR_CTRL1_PSS
    );
  //
  // Read back to ensure that the programming through sideband completes
  // before any new transaction is generated by subsequent code.
  // Ordering between primary and sideband is not guaranteed and
  // primary transaction triggered afterwards may be completed
  // before IPCS_PSS programming is finished.
  //
  PchPcrRead32 (PID_DMI, R_PCH_DMI15_PCR_CTRL1);
}

/**
  This function will do necessary configuration after platform
  should have switched to POSTBOOT_SAI. It needs to be called even if
  POSTBOOT_SAI was not set.
**/
VOID
PchDmi15ConfigAfterPostBootSai (
  VOID
  )
{
  //
  // Set Unsupported Transaction Policy Bit
  // Enable Transaction Credit Update Arbitration Performance Fix
  PchPcrAndThenOr32 (
  PID_DMI, R_PCH_DMI15_PCR_CTRL1,
  ~0u,
  B_PCH_DMI15_PCR_CTRL1_UTPB | B_PCH_DMI15_PCR_CTRL1_TCUAPF
  );
}

/**
 Secure Register Lock data

 @param[out] SrlRegOffset        Register offset holding Secure Register Lock setting
 @param[out] SrlRegMask          Mask for Secure Register Lock setting
**/
VOID
PchDmi15SrlRegData (
  OUT UINT16  *SrlRegOffset,
  OUT UINT32  *SrlRegMask
  )
{
  *SrlRegMask = B_PCH_DMI15_PCR_MPC_SRL;
  *SrlRegOffset = R_PCH_DMI15_PCR_MPC;
}
