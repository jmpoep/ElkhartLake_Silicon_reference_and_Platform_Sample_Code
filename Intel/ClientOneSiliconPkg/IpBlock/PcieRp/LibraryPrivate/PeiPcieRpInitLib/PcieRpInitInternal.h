/** @file
  Common header for PcieRpInitLib

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

#ifndef _PEI_PCIE_RP_INIT_INTERNAL_H_
#define _PEI_PCIE_RP_INIT_INTERNAL_H_

#include <PchPcieRpConfig.h>

#define PTM_DELAY_REGISTERS_NUM 5

typedef struct {
  UINT32  PtmPipeStageDelay[PTM_DELAY_REGISTERS_NUM];
  UINT32  PtmConfig;
} PCIE_PTM_CONFIGURATION;

/**
  Get project specific PTM configuration.

  @param[in]  ControllerIndex  Index of the PCIe controller
  @param[out] PciePtmConfig    Pointer to caller allocated PTM configuration
**/
VOID
PcieGetProjectPtmConfiguration (
  IN UINT32                   ControllerIndex,
  OUT PCIE_PTM_CONFIGURATION  *PciePtmConfig
  );

typedef struct {
  UINT32  PostCursorCoefficient;
  UINT32  CursorCoefficient;
  UINT32  PreCursorCoefficient;
} PCIE_PRESET_TO_COEFFICIENT_MAPPING;

typedef struct {
  //
  // This flag indicates if project's PCIe PIPE implementation supports
  // get preset to coefficient mapping query in the phy. If this query is supported project
  // doesn't have to specify preset to coefficient mapping in the BIOS as root port
  // can get it from phy.
  //
  BOOLEAN                             PipePresetToCoefficientQuerySupported;
  UINT32                              LowFrequencyValue; // Only valid if query to PIPE is unsupported
  UINT32                              FullSwingValue; // Only valid if query to PIPE is unsupported
  PCIE_PRESET_TO_COEFFICIENT_MAPPING  PresetToCoefficient[PCIE_LINK_EQ_PRESETS_MAX]; // Only valid if query to PIPE is unsupported
} PCIE_LINK_EQ_PROJECT_SETTINGS;

typedef struct {
  PCIE_LINK_EQ_PLATFORM_SETTINGS  PlatformSettings;
  PCIE_LINK_EQ_PROJECT_SETTINGS   ProjectSettings;
} PCIE_LINK_EQ_SETTINGS;

/**
  Get the project recommended equalization settings

  @param[in] RpIndex                    Index of the PCI root port
  @param[in] PcieLinkEqSettings         Pointer to the equalization config
**/
VOID
PcieGetProjectDefaultEqConfiguration (
  IN  UINT32                         RpIndex,
  OUT PCIE_LINK_EQ_SETTINGS          *PcieLinkEqSettings
  );

/**
  Get max link width.

  @param[in] RpBase    Root Port base address

  @retval Max link width
**/
UINT8
GetMaxLinkWidth (
  UINT64  RpBase
  );

/**
  Performs PCIe link equalization according to platform settings.
  Please make sure that link is in gen1 or gen2 before calling this
  procedure.

  @param[in] RpBase              PCI base of the RP
  @param[in] Gen3DeviceAttached  Gen3 capable device is attached to the root port
  @param[in] PcieLinkEqSettings  PCIe link equalization settings to be used during EQ
**/
VOID
PcieLinkEqualize (
  IN UINT64                 RpBase,
  IN BOOLEAN                Gen3DeviceAttached,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  );

#endif

