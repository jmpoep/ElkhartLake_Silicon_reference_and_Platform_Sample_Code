/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _PEI_SA_POLICY_UPDATE_H_
#define _PEI_SA_POLICY_UPDATE_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#include <SetupVariable.h>
#include <SaPolicyCommon.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Setup/SaSetup.h>
#include <Ppi/Wdt.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include "PeiPchPolicyUpdate.h"
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <CpuAccess.h>
#include <Library/SiPolicyLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#endif

///
/// DIMM SMBus addresses for Haddock Creek
///
#define DIMM_SMB_SPD_P0C0D0_HC 0xA2
#define DIMM_SMB_SPD_P0C0D1_HC 0xA0
#define DIMM_SMB_SPD_P0C1D0_HC 0xA6
#define DIMM_SMB_SPD_P0C1D1_HC 0xA4
#define DIMM_SMB_SPD_P0C0D2_HC 0xAA
#define DIMM_SMB_SPD_P0C1D2_HC 0xA8

//
// Sawtooth Peak
// Single SPD EEPROM at 0xA2 serves both C0D0 and C1D0 (LPDDR is 1DPC only)
//
#define DIMM_SMB_SPD_P0C0D0_STP 0xA2
#define DIMM_SMB_SPD_P0C0D1_STP 0xA0
#define DIMM_SMB_SPD_P0C1D0_STP 0xA2
#define DIMM_SMB_SPD_P0C1D1_STP 0xA0


#define WDT_TIMEOUT 60

// BClk Frequency Limitations (in Hz)
#define BCLK_MAX                600000000
#define BCLK_100                100000000
#define BCLK_GRANULARITY        1000000
#define MAX_BCLK_RFI_POINTS     4
#define MAX_IBECC_REGIONS       8  ///< Maximum number of protection regions handled by IBECC

/**
  PeiGetSectionFromFv finds the file in FV and gets file Address and Size

  @param[in] NameGuid              - File GUID
  @param[out] Address              - Pointer to the File Address
  @param[out] Size                 - Pointer to File Size

  @retval EFI_SUCCESS                Successfull in reading the section from FV
**/
EFI_STATUS
EFIAPI
PeiGetSectionFromFv (
  IN CONST  EFI_GUID        NameGuid,
  OUT VOID                  **Address,
  OUT UINT32               *Size
  );

#endif

