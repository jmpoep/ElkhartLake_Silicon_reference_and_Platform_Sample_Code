/** @file
  Header file for Software Guard Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#ifndef _SOFTWARE_GUARD_LIB_H_
#define _SOFTWARE_GUARD_LIB_H_

#include <Ppi/SiPolicy.h>

#define SINIT_SE_SVN_VALUE 0x2   ///< SINIT SVN for SGX

/**
  Check if SGX present.
  Presence of  feature is detectable by reading CPUID.(EAX=12,
  ECX=0):EAX[0].

  @retval TRUE  - SGX is present on the system
  @retval FALSE - SGX is not present on the system
**/
BOOLEAN
IsSgxPresent (
  VOID
  );


/**
  Return TRUE if SGX in feature control was set
  IA32_FEATURE_CONTROL MSR(3Ah) [18] == 1

  @retval TRUE if SGX in feature control was set.
  @retval FALSE if SGX in feature control was not set
**/
BOOLEAN
IsSgxFeatureCtrlSet (
  VOID
  );

/**
  Perform SGX Pre Patch Load initialization.

  @param[in] SiPreMemPolicyPpi  - SI PreMem Policy PPI
  @param[in] SiPolicyPpi        - SI Policy PPI
**/
VOID
SgxInitializationPrePatchLoad (
  IN SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi,
  IN SI_POLICY_PPI           *SiPolicyPpi
  );

/**
  Perform SGX initialization by logical processor.
**/
VOID
SgxInitializationByLogicalProcessorPrePatchLoad (
  VOID
  );

/**
  Perform SGX Post Patch Load initialization.
**/
VOID
SgxInitializationPostPatchLoad (
  VOID
  );
#endif
