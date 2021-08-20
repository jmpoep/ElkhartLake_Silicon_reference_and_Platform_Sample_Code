/** @file
  This file contains functions that initializes Dekel

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

#include <Library/PeiCpuPcieDekelInitLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <CpuSbInfo.h>
#include <Library/DebugLib.h>
#include <Library/PreSiliconEnvDetectLib.h>

/**
  Read DEKEL FW download status

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID

  @retval     BOOLEAN          Fw Download Completed TRUE or FALSE
**/

BOOLEAN
EFIAPI
DekelFwStatus (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
)
{
  ///
  ///
  if ((CpuRegbarRead32(CpuSbDevicePid, R_SA_DEKEL_FW_STATUS) & (UINT32)BIT15) != BIT15) {
    if (!IsSimicsEnvironment()) {
      switch (CpuSbDevicePid) {
        case CPU_SB_PID_DEKEL_IO4:
          DEBUG ((DEBUG_ERROR, "ERROR: DEKEL FW download failed for x4 controller (PEG 060) PHY !!!\n"));
          ASSERT(FALSE);
          break;
        case CPU_SB_PID_DEKEL_IO16:
          DEBUG ((DEBUG_ERROR, "ERROR: DEKEL FW download failed for x16 controller PHY !!!\n"));
          ASSERT(FALSE);
          break;
        default:
          DEBUG ((DEBUG_ERROR, "ERROR: DEKEL FW download failed!!!\n"));
          break;
      }
    }
    return FALSE;
  }
  return TRUE;
}

/**
  Initialize the Dekel in PEI

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
**/

VOID
EFIAPI
DekelInit (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
)
{
  UINT8     Index;
  UINT16    NumberOfLanes;

  NumberOfLanes = 0;

  if (CpuSbDevicePid == CPU_SB_PID_DEKEL_IO4) {
    NumberOfLanes = TIGERLAKE_CPU_PCIE_x4_MAX_LANES;
  } else if (CpuSbDevicePid == CPU_SB_PID_DEKEL_IO16) {
    NumberOfLanes = TIGERLAKE_CPU_PCIE_x16_MAX_LANES;
  }
  for(Index = 0; Index < NumberOfLanes; Index++) {
    //
    //  Program data lane
    //
    CpuRegbarOr16 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_DL_SUSWELL_PWRGATE_CNTRL_OFFSET, BIT2);
    CpuRegbarOr16 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_DL_SUSWELL_PWRGATE_CNTRL_OFFSET, BIT0);
    CpuRegbarAndThenOr32 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_NOMEMPTY_UNDFLW_THRESOLD_OFFSET, (UINT32)~(BIT20 | BIT19 | BIT18), 0);
    CpuRegbarOr32 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_REDO_RX_CALIB_EQ_TRAIN_OFFSET, BIT25);
    //
    // PCS glue registers
    //
    CpuRegbarAndThenOr32 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_PCS_PMD_RX_TMRS_OFFSET, (UINT32)~(BIT14 | BIT12), 0);
    //
    // PMD SUSWEL registers
    //
    CpuRegbarAndThenOr32 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_SQUELCH_CTRL_OFFSET, (UINT32)~(0xFFFF0000), 0);
    //
    // PMD ANA registers
    //
    CpuRegbarAndThenOr32 (CpuSbDevicePid, Index * LANE_MULTIPLIER + R_SA_DEKEL_PMD_LANE_ANA_CTRL_OFFSET,  (UINT32)~(BIT14 | BIT13 | BIT12 | BIT11), (BIT13 | BIT12 | BIT11));
  }
  //
  // Program Comon Lane with Data value
  //
  CpuRegbarOr32 (CpuSbDevicePid, R_SA_DEKEL_CMN_LANE_OFFSET, (BIT15 | BIT14 | BIT13 | BIT12));
}

/**
  Read DEKEL Firmware Version

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID

  @retval     UINT32         Dekel Firmware Version
**/

UINT32
EFIAPI
GetDekelFwVersion (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
)
{
  UINT32       DekelFwVersion;

  DekelFwVersion = CpuRegbarRead32(CpuSbDevicePid, R_SA_DEKEL_FW_VERSION_OFFSET);
  DEBUG ((DEBUG_INFO, "DekelFwVersion %x\n", DekelFwVersion));
  return DekelFwVersion;
}