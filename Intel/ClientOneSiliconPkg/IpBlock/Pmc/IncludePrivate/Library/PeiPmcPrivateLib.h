/** @file
  Header file for private PEI PMC Lib.

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
#ifndef _PEI_PMC_PRIVATE_LIB_H_
#define _PEI_PMC_PRIVATE_LIB_H_

/**
  Check if PCH PM Timer enabled based on platform policy

  @retval TRUE       PCH PM Timer is enabled.
  @retval FALSE      PCH PM Timer is disabled.
**/
BOOLEAN
PmcIsPchPmTimerEnabled (
  VOID
  );

/**
  Configure PM Timer.
  Once PM Timer is disabled, TCO timer stops counting.
  This must be executed after uCode PM timer emulation.

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
PmcConfigurePmTimer (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  Lock down PMC settings

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
PmcLockSettings (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  Perform PCH PMC initialization

  @param[in] SiPolicy           The SI Policy PPI instance
**/
VOID
PmcInit (
  IN  SI_POLICY_PPI           *SiPolicy
  );

/**
  Perform FIVR initialization
  This function does configuration for below settings:
   - external V1p05 and Vnn rails
   - characteristics of VCCIN_AUX voltage rail
   - CPPM interaction with FIVR
  Many of those settings reside in RTC power well.

  @param[in] SiPolicy                  The SI Policy PPI instance
**/
VOID
PmcPchFivrInit (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  This function locks FIVR Configuration
**/
VOID
PmcLockFivrConfig (
  VOID
  );

/**
  This function configures PCH FIVR RFI Control4 setting

  @param[in] RfiControl4  FIVR RFI Control4 setting value
**/
VOID
PmcConfigureFivrRfiControl4 (
  IN UINT32  RfiControl4
  );

/**
  This function configures PCH FIVR EMI Control0 setting

  @param[in] EmiControl0  FIVR EMI Control0 setting value
**/
VOID
PmcConfigureFivrEmiControl0 (
  IN UINT32  EmiControl0
  );

/**
  Configure the Time Sync Gpio
**/
VOID
TimeSyncInit (
  IN  SI_POLICY_PPI                    *SiPolicy
  );

/**
  Checks if the Intel Touch Host Controller is Enabled

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval TRUE                    THC_DIS strap is 0
  @retval FALSE                   THC_DIS strap is 1
**/
BOOLEAN
PmcIsThcEnabled (
  IN UINT8  ThcNumber
  );

#endif // _PEI_PMC_PRIVATE_LIB_H_
