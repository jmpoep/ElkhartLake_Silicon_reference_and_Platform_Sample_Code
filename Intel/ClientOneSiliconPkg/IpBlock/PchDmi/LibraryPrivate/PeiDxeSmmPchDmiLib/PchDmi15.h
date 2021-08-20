/** @file
  Internal header file for PCH DMI library for SIP15

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef __PCH_DMI_15_H__
#define __PCH_DMI_15_H__

#include <Library/PchDmiLib.h>
#include <Library/PeiPchDmiLib.h>

/**
  This function checks if DMI SIP15 Secured Register Lock (SRL) is set

  @retval SRL state
**/
BOOLEAN
IsPchDmi15Locked (
  VOID
  );

/**
  Set DMI thermal throttling to recommended configuration.
  It's intended only for DMI SIP15.
**/
VOID
PchDmi15SetRecommendedThermalThrottling (
  VOID
  );

/**
  Set DMI thermal throttling to custom configuration.
  This function will configure Thermal Sensor 0/1/2/3 TargetWidth and set
  DMI Thermal Sensor Autonomous Width Enable.
  It's intended only for DMI SIP15.

  @param[in] PchDmiThermalThrottling        DMI Thermal Throttling structure.
**/
VOID
PchDmi15SetCustomThermalThrottling (
  IN PCH_DMI_THERMAL_THROTTLING      PchDmiThermalThrottling
  );

/**
  Enable PCIe Relaxed Order for DMI SIP15
**/
VOID
PchDmi15EnablePcieRelaxedOrder (
  VOID
  );

/**
  This function will switch SAI value to be driven to IOSF Primary Fabric
  for cycles with Core BDF from HOSTIA_BOOT_SAI to HOSTIA_POSTBOOT_SAI.
  To be used when PCH is paired with CFL CPU.
**/
VOID
PchDmi15EnablePostBootSai (
  VOID
  );

/**
  This function will do necessary configuration after platform
  should have switched to POSTBOOT_SAI. It needs to be called even if
  POSTBOOT_SAI was not set.
**/
VOID
PchDmi15ConfigAfterPostBootSai (
  VOID
  );

/**
 Secure Register Lock data

 @param[out] SrlRegOffset        Register offset holding Secure Register Lock setting
 @param[out] SrlRegMask          Mask for Secure Register Lock setting
**/
VOID
PchDmi15SrlRegData (
  OUT UINT16  *SrlRegOffset,
  OUT UINT32  *SrlRegMask
  );

/**
  Get PCH DMI SIP15 Virtual Channel Control and Status registers

  @param[in]  Vc                   The virtual channel number for programing
  @param[out] PchDmiVcCtlAddress      DMI Virtual Channel Control register address
  @param[out] PchDmiVcStsAddress      DMI Virtual Channel Status register address
**/
VOID
PchDmi15VcRegs (
  IN   PCH_DMI_VC_TYPE  Vc,
  OUT  UINT16           *PchDmiVcCtlAddress,
  OUT  UINT16           *PchDmiVcStsAddress
  );

/**
  The function sets the Target Link Speed in PCH-H to GEN 3 in DMI SIP15.

  @param[in] TargetLinkSpeed        Target Link Speed
                                    2: GEN2
                                    3: GEN3
**/
VOID
PchDmi15SetTargetLinkSpeed (
  IN  UINT8                 TargetLinkSpeed
  );

#endif
