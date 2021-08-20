/** @file
  The functions in this file implement the DDR3 reset sequence.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
// Include files

#include "MrcReset.h"
#include "MrcMcConfiguration.h"
#include "MrcMaintenance.h"
#include "MrcGears.h"
#include "MrcChipApi.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"

/**
  Perform full JEDEC reset and init sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcResetSequence (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus     Status;
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  UINT32        Controller;
  UINT32        Offset;
  BOOLEAN       Lpddr;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Lpddr   = Outputs->Lpddr;

  // Start with an IO reset
  Status = IoReset (MrcData);

  if (mrcSuccess == Status) {
    // Perform jedec reset.
    // If RTT_NOM is to be enabled in MR1, the ODT input signal must be statically held LOW
    // in our system RTT_NOM is always enable.
    // Force ODT low
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_BC_CR_REUT_CH_MISC_ODT_CTRL_REG, MC1_BC_CR_REUT_CH_MISC_ODT_CTRL_REG, Controller);
        MrcWriteCR (MrcData, Offset, MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX);
      }
    }

    if (Lpddr) {
      // Set Low frequency (1067), unless we're already there
      if ((Outputs->Frequency != f1067) && (Inputs->LpFreqSwitch == TRUE)) {
        Status = MrcFrequencySwitch (MrcData, f1067, !Outputs->RestoreMRs);
        if (Status != mrcSuccess) {
          return Status;
        }
      }
    }

    Status = MrcJedecReset (MrcData);
    if (Status == mrcSuccess) {
      Status = MrcJedecInit (MrcData);
    }

    if (Lpddr) {
      if (Outputs->LpddrEctDone && (Status == mrcSuccess)) {
        // Set FSP-OP = 1, set High frequency
        Status = MrcLpddrSwitchToHigh (MrcData, !Outputs->RestoreMRs);
      }
    }

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_BC_CR_REUT_CH_MISC_ODT_CTRL_REG, MC1_BC_CR_REUT_CH_MISC_ODT_CTRL_REG, Controller);
        MrcWriteCR (MrcData, Offset, 0);
      }
    }
  }

  // Set flag to restore from host structure instead from look-up table
  Outputs->RestoreMRs = TRUE;
  Outputs->JedecInitDone = TRUE;

  return Status;
}

/**
  Perform the required steps to exit self refresh in S3/Warm reset:
   1. Set MC_INIT_STATE_G.pure_srx to 1.
   2. Set MCHBAR_CHx_CR_MC_INIT_STATE.SRX_reset to 1.
    - MRC does not need to pull DIMMs out of self-refresh by
      asserting CKE high, and issue ZQ Long.
    - MC will do these steps automatically when MRC will switch
      it to Normal mode.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSelfRefreshExit (
  IN MrcParameters *const MrcData
  )
{
  const MrcOutput *Outputs;
  MrcDdrType      DdrType;
  INT64           GetSetVal;
  UINT32          Offset;
  UINT32          IpChannel;
  UINT32          Channel;
  UINT32          Controller;
  UINT32          Data32;
  BOOLEAN         Lpddr;
  MC0_CH0_CR_MC_INIT_STATE_STRUCT McInitState;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Lpddr   = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }

      IpChannel = LP_IP_CH (Lpddr, Channel);
      // Indicate to MC that we are going to exit Self Refresh when we go to Normal Mode
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MC_INIT_STATE_REG, MC1_CH0_CR_MC_INIT_STATE_REG, Controller, MC0_CH1_CR_MC_INIT_STATE_REG, IpChannel);
      McInitState.Data = MrcReadCR (MrcData, Offset);
      McInitState.Bits.SRX_reset = 1;
      MrcWriteCR (MrcData, Offset, McInitState.Data);

      // Initialize MC to "hot" temperature until the first temperature read occurs.
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        Data32 = RANK_TEMPERATURE_HOT_DDR4;
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, MC1_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, Controller, MC0_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG, IpChannel);
      } else {
        Data32 = (DdrType == MRC_DDR_TYPE_LPDDR4) ? RANK_TEMPERATURE_HOT_LPDDR4 : RANK_TEMPERATURE_HOT_LPDDR5;
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, MC1_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, Controller, MC0_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, IpChannel);
      }
      MrcWriteCR (MrcData, Offset, Data32);
    } // for Channel
  } // for Controller

  GetSetVal = 1;
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccPureSrx, WriteNoCache, &GetSetVal);

  return mrcSuccess;
}
