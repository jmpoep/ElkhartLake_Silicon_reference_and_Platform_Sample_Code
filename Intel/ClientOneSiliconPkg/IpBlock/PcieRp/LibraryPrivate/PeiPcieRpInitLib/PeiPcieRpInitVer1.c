/** @file
  This file contains functions needed for PCIe root port initialization
  specific to ICL project.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include "PcieRpInitInternal.h"

/**
  Get project specific PTM configuration.

  @param[in]  ControllerIndex  Index of the PCIe controller
  @param[out] PciePtmConfig    Pointer to caller allocated PTM configuration
**/
VOID
PcieGetProjectPtmConfiguration (
  IN UINT32                   ControllerIndex,
  OUT PCIE_PTM_CONFIGURATION  *PciePtmConfig
  )
{
  //
  // First controller's lanes are using the non-ML phy
  // so recommendation for non ML phy is used.
  //
  if (ControllerIndex == 0) {
    PciePtmConfig->PtmPipeStageDelay[0] = 0x240B2B07;
    PciePtmConfig->PtmPipeStageDelay[1] = 0x1B09200C;
    PciePtmConfig->PtmPipeStageDelay[2] = 0x170B180B;
    PciePtmConfig->PtmPipeStageDelay[3] = 0x190B1C09;
    PciePtmConfig->PtmPipeStageDelay[4] = 0x190B;
  //
  // Second controller's lanes are using a mix of non-ML
  // and ML phy. We use the lower value from both non-ML
  // and ML recommendation.
  //
  } else if (ControllerIndex == 1) {
    PciePtmConfig->PtmPipeStageDelay[0] = 0x240B2B07;
    PciePtmConfig->PtmPipeStageDelay[1] = 0x1B08200C;
    PciePtmConfig->PtmPipeStageDelay[2] = 0x160B180B;
    PciePtmConfig->PtmPipeStageDelay[3] = 0x180A1B08;
    PciePtmConfig->PtmPipeStageDelay[4] = 0x180C;
  //
  // Other PCIe controllers use ML phy. ML recommendation
  // is used.
  //
  } else {
    PciePtmConfig->PtmPipeStageDelay[0] = 0x250C2C08;
    PciePtmConfig->PtmPipeStageDelay[1] = 0x1C08210C;
    PciePtmConfig->PtmPipeStageDelay[2] = 0x160C180B;
    PciePtmConfig->PtmPipeStageDelay[3] = 0x180A1B08;
    PciePtmConfig->PtmPipeStageDelay[4] = 0x180C;
  }

  PciePtmConfig->PtmConfig = 0x40052;
}

/**
  Get the project recommended equalization settings

  @param[in] RpIndex                    Index of the PCI root port
  @param[in] PcieLinkEqSettings         Pointer to the equalization config
**/
VOID
PcieGetProjectDefaultEqConfiguration (
  IN  UINT32                 RpIndex,
  OUT PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  CONST PCIE_LINK_EQ_COEFFICIENTS  PcieCoeffList[] = {
    {6, 8},
    {6, 12},
    {8, 8}
  };

  PcieLinkEqSettings->PlatformSettings.PcieLinkEqMethod = PcieLinkHardwareEq;
  PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode = PcieLinkEqCoefficientMode;
  if (ARRAY_SIZE (PcieCoeffList) <= ARRAY_SIZE (PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList)) {
    PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients = ARRAY_SIZE (PcieCoeffList);
    CopyMem (PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList, PcieCoeffList, sizeof (PcieCoeffList));
  }
  PcieLinkEqSettings->PlatformSettings.Ph1DownstreamPortTransmitterPreset = 7;
  PcieLinkEqSettings->PlatformSettings.Ph1UpstreamPortTransmitterPreset = 5;

  PcieLinkEqSettings->ProjectSettings.PipePresetToCoefficientQuerySupported = TRUE;
}

