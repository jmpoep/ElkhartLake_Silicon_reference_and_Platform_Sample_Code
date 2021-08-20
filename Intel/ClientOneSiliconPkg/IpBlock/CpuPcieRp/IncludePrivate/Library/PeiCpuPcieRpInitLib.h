/** @file
  Header file for private PeiPcieRpInitLib.

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
#ifndef _PEI_PCIE_RP_INIT_LIB_H_
#define _PEI_PCIE_RP_INIT_LIB_H_

/**
  Configure root port function number mapping

**/
VOID
CpuPcieRpConfigureRpfnMapping (
  IN CPU_PCIE_CONFIG           *CpuPcieRpConfig
  );

/**
  Lock SRL bits after function remapping - lock it for all root ports

**/
VOID
CpuPcieRpSetSecuredRegisterLock (
  VOID
  );

/**
  Perform Initialization of the Downstream Root Ports.

  @param[in] SiPolicy             The SI Policy PPI

**/
VOID
CpuPcieRpInit (
  IN CONST SI_POLICY_PPI     *SiPolicy
  );

/**
  This is the function to do IOSF Port Configuration and Grant Count Programming.

  @param[in] RPBase               Root Port Base Address
  @param[in] SiPolicy             SI Policy PPI

**/
VOID
CpuPcieRpSetIosfPortAndGrantCount (
  IN UINTN             RPBase,
  IN SI_POLICY_PPI*    SiPolicy
  );
#endif
