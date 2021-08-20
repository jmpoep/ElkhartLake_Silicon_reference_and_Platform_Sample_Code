/** @file
  Header file for Cpu Init Lib Pei Phase

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

@par Specification
**/
#ifndef _CPU_INIT_LIB_H_
#define _CPU_INIT_LIB_H_

#include <PiPei.h>
#include <Ppi/SiPolicy.h>

/**
  Check some CPU policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] SiPreMemPolicy    The Silicon PreMem Policy protocol instance

**/
VOID
CpuValidatePolicy (
  IN  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy
  );

/**
  Get CPU Debug Interface and update.

  @retval VOID - No value to return
**/
VOID
LockEnableDisableCpuDebug (
  VOID
  );

/**
  This function performs basic initialization for CPU in PEI phase after Policy produced.

  @param[in] SiPreMemPolicyPpi The Si PreMem Policy PPI instance
**/
EFI_STATUS
CpuOnPolicyInstalled (
  IN  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  );

/**
  Initialize processor features, performance and power management features, BIOS GUARD, and Overclocking etc features before RESET_CPL at post-memory phase.

  @param[in] PeiServices    Pointer to PEI Services Table
  @param[in] SiPolicyPpi    The SI Policy PPI instance

  @retval EFI_SUCCESS     The driver installed/initialized correctly.
**/
EFI_STATUS
CpuInit (
  IN  CONST EFI_PEI_SERVICES  **PeiServices,
  IN  SI_POLICY_PPI           *SiPolicyPpi
  );

/**
  Initialize power management after RESET_CPL at post-memory phase.

  @param[in] PeiServices    Pointer to PEI Services Table

  @retval EFI_SUCCESS     The driver installed/initialized correctly.
  @retval Driver will ASSERT in debug builds on error.  PPM functionality is considered critical for mobile systems.
**/
EFI_STATUS
CpuPowerMgmtInit (
  IN  CONST EFI_PEI_SERVICES  **PeiServices
  );

/**
  Get TCC cross throttling temperature.
  Set Thermal trip point temperature indicated by MSR 1A2h
  If (RATL mode), T0L = MSR 1A2h[23:16]
  Else          , T0L = MSR 1A2h[23:16] - MSR 1A2h[29:24]

  @retval  Value of the activation temperature
**/
UINT32
CpuGetCrossThrottlingTripPoint (
  VOID
  );

/**
  Cpu End of PEI callback function. This is the last change before entering DXE and OS when S3 resume.
**/
VOID
CpuOnEndOfPei (
  VOID
  );

/**
  This function handles Cpu Initialization routine at the end of PEI

  @param[in] PeiServices   - Pointer to PEI Services Table.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
CpuInitAtEndOfPei (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  );

/**
  Set the BIOS DONE MSR for all Enabled Cores

  @param[in] PeiServices   - Pointer to PEI Services Table.
**/
VOID
SetBiosDone (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  );

/**
  Perform Total Memory Encryption initialization.

  @param[in] TmeEnable      - TME policy enable
  @param[in] TmeExcludeBase - Base physical address to be excluded for TME encryption
  @param[in] TmeExcludeSize - Size of range to be excluded from TME encryption

  @retval VOID - No value to return
**/
VOID
TmeInit (
    IN UINT32 TmeEnable,
    IN UINT64 TmeExcludeBase,
    IN UINT64 TmeExcludeSize
  );
#endif
