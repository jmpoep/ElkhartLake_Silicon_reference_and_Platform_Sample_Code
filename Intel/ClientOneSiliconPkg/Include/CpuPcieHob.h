/** @file
  The GUID definition for CpuPcieHob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SA_PEG_HOB_H_
#define _SA_PEG_HOB_H_

#include <Base.h>
#include <CpuPcieInfo.h>
#include <CpuPcieRpConfig.h>

extern EFI_GUID gSaPegHobGuid;
#pragma pack (push,1)
/**
  PEG data definition
  This structure can be saved in non-volatile memory to be re-used in the following boot.
  By this way reference code will not re-do PCIe Preset Search and save POST time
  SI_POLICY_PPI can be used to pass the pointer of pre-saved SA_PEG_DATA by platform code
**/
typedef struct {
  UINT32              EndPointVendorIdDeviceId[SA_PEG_MAX_FUN]; ///< Offset 0 - 11: VID/DID for each PEG controller
  UINT8               BestPreset[SA_PEG_MAX_LANE];              ///< Offset 12 - 27: Best preset value for each lane
  UINT8               PegGen3PresetSearch;                      ///< Offset 28: Preset search value
  UINT8               PegLinkFailMask;                          ///< Offset 29: Mask of PEG controllers to ignore
  UINT8               Rsvd0[2];                                 ///< Offset 30: Reserved for future use.
} SA_PEG_DATA;

/**
  The CPU_PCIERP_HOB block describes the expected configuration of the SA PCI Express controllers
**/
typedef struct {
  ///
  /// These members describe the configuration of each PCH PCIe root port.
  ///
  CPU_PCIE_ROOT_PORT_CONFIG   RootPort[CPU_PCIE_MAX_ROOT_PORTS];
  UINT8                       L1SubStates[CPU_PCIE_MAX_ROOT_PORTS];  ///< The L1 Substates configuration of the root port
} CPU_PCIERP_HOB;

///
/// System Agent PEG NVS Hob
///
typedef struct {
  EFI_HOB_GUID_TYPE        EfiHobGuidType;                           ///< Offset 0 - 23: GUID Hob type structure for gSaPegHobGuid
  SA_PEG_DATA              PegData;                                  ///< Offset 24 (Move to FSP NVS Hob) PEG data definition
  CPU_PCIERP_HOB           CpuPcieRp;                                ///< CPU PCIE root port HOB definition
  UINT32                   DekelFwVersion;                           ///< Dekel Firmware Version
  BOOLEAN                  PegPlatformResetRequired;                 ///< 1=platform code should generate a cold/power cycle reset after saving PEG config data into NVRAM
  BOOLEAN                  InitPcieAspmAfterOprom;                   ///< 1=initialize PCIe ASPM after Oprom; 0=before (This will be set basing on policy)
  UINT32                   RpEnabledMask;
  UINT32                   RpEnMaskFromDevEn;
  UINT8                    DisableClkReqMsg[CPU_PCIE_MAX_ROOT_PORTS];     ///< 1=ClkReqMsg disabled, 0=ClkReqMsg enabled
} SA_PEG_HOB;
#pragma pack (pop)
#endif
