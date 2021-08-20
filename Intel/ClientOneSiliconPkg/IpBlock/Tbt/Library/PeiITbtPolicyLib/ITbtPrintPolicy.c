/** @file
  This file provides service for PEI phase policy printing

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
#include <PeiITbtPolicyLibrary.h>

/**
  This function prints the PEI phase PreMem policy.

  @param[in] SiPolicyPpi                Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
ITbtPrintPolicy (
  IN  SI_POLICY_PPI                     *SiPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  UINT8                                 Index;
  PEI_ITBT_CONFIG                       *PeiITbtConfig;

  PeiITbtConfig = NULL;
  Status = EFI_NOT_FOUND;
  DEBUG ((DEBUG_INFO, "[TBT] TbtPrintPolicyConfig Start\n"));

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPeiITbtConfigGuid, (VOID *) &PeiITbtConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "\n------------------------ ITBT Policy (PEI) Print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : 0x%x\n", SiPolicyPpi->TableHeader.Header.Revision));
  ASSERT (SiPolicyPpi->TableHeader.Header.Revision == SI_POLICY_REVISION);

  DEBUG ((DEBUG_INFO, " Revision : %d\n", PeiITbtConfig->Header.Revision));
  ASSERT (PeiITbtConfig->Header.Revision == PEI_ITBT_CONFIG_REVISION);
  //
  // Print ITBT Common Policy
  //
  DEBUG ((DEBUG_INFO, "PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs = %x\n", PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs));
  DEBUG ((DEBUG_INFO, "PeiITbtConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs = %x\n", PeiITbtConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs));

  //
  // Print ITBT Policy
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    DEBUG ((DEBUG_INFO, "PeiITbtConfig->ITbtRootPortConfig[%x].ITbtPcieRootPortEn = %x\n", Index, PeiITbtConfig->ITbtRootPortConfig[Index].ITbtPcieRootPortEn));
  }

  DEBUG ((DEBUG_INFO, "\n------------------------ ITBT Policy (PEI) Print END -----------------\n"));
  DEBUG_CODE_END ();

  return;
}