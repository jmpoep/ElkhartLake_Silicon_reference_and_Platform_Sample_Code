/** @file
  RST Policy Lib

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <RstConfig.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiRstPolicyLib.h>
/**
  Check if RST PCIe Storage Remapping is enabled based on RST config from SATA config

  @param[in] RstPcieStorageRemap    The PCH PCIe Storage remapping

  @retval TRUE                      RST PCIe Storage Remapping is enabled
  @retval FALSE                     RST PCIe Storage Remapping is disabled
**/
STATIC
BOOLEAN
RstIsPcieStorageRemapEnabledByConfig (
  IN  CONST RST_HARDWARE_REMAPPED_STORAGE_CONFIG   *RstPcieStorageRemap
  )
{
  UINT32  Index;

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    if (RstPcieStorageRemap[Index].Enable == 1) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Check if RST PCIe Storage Remapping is enabled based on policy

  @param[in]  SiPolicy              The Silicon Policy PPI instance

  @retval TRUE                      RST PCIe Storage Remapping is enabled
  @retval FALSE                     RST PCIe Storage Remapping is disabled
**/
BOOLEAN
RstIsPcieStorageRemapEnabled (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  RST_CONFIG         *RstConfig;

  RstConfig = GetRstConfig (SiPolicy);
  return RstIsPcieStorageRemapEnabledByConfig (RstConfig->HardwareRemappedStorageConfig);
}