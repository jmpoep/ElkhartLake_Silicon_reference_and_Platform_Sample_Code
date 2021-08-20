/** @file
  This module contains functions to configure and use Memory Controller
  maintenance features.

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
#include "MrcTypes.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcMaintenance.h"
#include "MrcGeneral.h"
#include "MrcMcOffsets.h"


/**
  This function will disable the DQS Oscillator maintenance feature in the Memory Controller.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcDisableDqsOscillatorMc (
  IN  MrcParameters * const MrcData
  )
{
  UINT32  Controller;
  UINT32  Channel;
  UINT32  Offset;
  UINT32  IpChannel;
  BOOLEAN Lpddr;
  MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParams;

  Lpddr = MrcData->Outputs.Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                  MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG,
                  MC1_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG,
                  Controller,
                  MC0_CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG,
                  IpChannel
                  );
      Lp4DqsOsclParams.Data = MrcReadCR (MrcData, Offset);
      Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD          = 0;
      Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL         = 1;

      MrcWriteCR (MrcData, Offset, Lp4DqsOsclParams.Data);
    } // Channel
  } // Controller
}

/**
  This function executes the requested ZQ command.
  This function will wait the appropriate wait time as specified in the JEDEC spec.
  ZQ is sent to all populated controllers, channels, and ranks.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  ChBitMask - Bit mask of channels to run.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcSendZq (
  IN  MrcParameters *const  MrcData
  )
{
  MrcStatus   Status;
  UINT32      Offset;
  UINT32      Channel;
  UINT32      Controller;
  UINT32      IpChannel;
  BOOLEAN     Lpddr;
  MC0_CH0_CR_MRS_FSM_CONTROL_STRUCT FsmCtl;
  MC0_CH0_CR_MRS_FSM_CONTROL_STRUCT FsmCtlCurrentData[MAX_CHANNEL];

  Status = mrcSuccess;
  Lpddr = MrcData->Outputs.Lpddr;

  // Use MRS FSM to send ZQ commands on all populated channels / ranks.
  // DDR4:   FSM will issue ZQCL and wait tZQINIT
  // LPDDR4: FSM will issue MPC ZQCAL START and LATCH, and wait tZQCAL / tZQLAT
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
        // Save FSM CTRL
        IpChannel = LP_IP_CH (Lpddr, Channel);
        Offset = MrcGetMrsFsmCtlOffset (MrcData, Controller, IpChannel);
        FsmCtlCurrentData[Channel].Data = MrcReadCR64 (MrcData, Offset);

        FsmCtl.Data = 0;
        FsmCtl.Bits.do_ZQCL = 1;
        FsmCtl.Bits.reset_flow = 1;  // FSM should wait tZQINIT
        MrcWriteCR64 (MrcData, Offset, FsmCtl.Data);
      }
    } // Channel
  } // Controller

  // Will run on both channels in parallel
  Status = MrcProgramMrsFsm (MrcData);

  // Restore FSM CTRL
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
        IpChannel = LP_IP_CH (Lpddr, Channel);
        Offset = MrcGetMrsFsmCtlOffset (MrcData, Controller, IpChannel);
        MrcWriteCR64 (MrcData, Offset, FsmCtlCurrentData[Channel].Data);
      }
    }
  }

  return Status;
}

/**
  Issue ZQ calibration command on all populated controller, channels and ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData  - include all the MRC data
  @param[in] ZqType   - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcIssueZQ (
  IN  MrcParameters *const  MrcData,
  IN  MrcZqType             ZqType
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  MrcDebug  *Debug;
  char      *StrZqType;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (ZqType) {
  case MRC_ZQ_INIT:
    StrZqType = "INIT";
    break;

  case MRC_ZQ_LONG:
    StrZqType = "LONG";
    break;

  case MRC_ZQ_SHORT:
    StrZqType = "SHORT";
    break;

  case MRC_ZQ_RESET:
    StrZqType = "RESET";
    break;

  case MRC_ZQ_CAL:
    StrZqType = "CAL";
    break;

  default:
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Wrong ZQ type: %d\n", ZqType);
    return mrcWrongInputParameter;
  }

  if (!Outputs->JedecInitDone) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Issue ZQ %s on all channels / ranks\n", StrZqType);
  }

  // We only support MRC_ZQ_CAL for LPDDR4 and MRC_ZQ_LONG for DDR4
  Status = MrcSendZq (MrcData);

  return Status;
}

/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  Controller- Memory Controller Number within the processor (0-based).
  @param[in]  Channel   - Channel to send MRS command to.
  @param[in]  Rank      - Rank to send MRS command to.
  @param[in]  Address   - MRS command value.
  @param[in]  MR        - Which MR command to send.
  @param[in]  DeviceMask- Which set(s) of 8 DQs to set to low for PDA mode.

  @retval mrcSuccess    - PDA command was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcDdr4PdaCmd (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT16               Address,
  IN UINT8                MR,
  IN UINT16               DeviceMask
  )
{
  const MRC_FUNCTION                    *MrcCall;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  INT64                                 Ddr4OneDpc;
  UINT32                                Offset;
  UINT8                                 Data;
  UINT8                                 MrCmdAdd;
  BOOLEAN                               Busy;
  MC0_CH0_CR_DDR_MR_COMMAND_STRUCT      MrCommand;
  UINT64                                Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_COMMAND_REG, MC1_CH0_CR_DDR_MR_COMMAND_REG, Controller, MC0_CH1_CR_DDR_MR_COMMAND_REG, Channel);

  // Remap target rank if ddr4_1dpc is enabled on this channel
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccDdr4OneDpc, ReadNoCache, &Ddr4OneDpc);
  if (Ddr4OneDpc == 1) { // ddr4_1dpc enabled on DIMM0
    if (Rank == 1) {
      Rank = 3;
    }
  } else if (Ddr4OneDpc == 2) { // ddr4_1dpc enabled on DIMM1
    if (Rank == 2) {
      Rank = 0;
    }
  }

  //
  // Make sure MRH is not busy
  //
  do {
    MrCommand.Data = MrcReadCR (MrcData, Offset);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));
  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  Data = (Address & 0xFF);
  // MA13 is now in the Address field but this is unused in PDA.
  MrCmdAdd = ((UINT8) ((Address & 0x1F00) >> 5)) | (MR & 0x7);

  //
  // Send the PDA command
  //
  MrCommand.Data                 = 0;
  MrCommand.Bits.Data            = Data;
  MrCommand.Bits.Address         = MrCmdAdd;
  MrCommand.Bits.Rank            = Rank;
  MrCommand.Bits.Busy            = 1;
  MrCommand.Bits.DRAM_mask       = 0x1FF & (~DeviceMask); // 0 - for device enable
  MrCommand.Bits.Command         = 2; // Per DRAM addressability mode (PDA)
  MrCommand.Bits.Assume_idle     = 0;
  MrcWriteCR (MrcData, Offset, MrCommand.Data);

  //
  // Wait till MRH is done sending the command
  //
  Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, Offset);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  }

  return mrcSuccess;
}

VOID
MrcRankOccupancy (
  IN  MrcParameters * const MrcData
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  INT64         GetSetVal;
  UINT32        Controller;
  UINT32        Channel;
  UINT32        IpChannel;
  UINT8         RankMask;
  BOOLEAN       Lpddr;
  UINT32        Offset;
  MC0_CH0_CR_MC_INIT_STATE_STRUCT McInitState;

  Outputs = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
      // Set the Rank_occupancy to zero for ch1 due to  Outputs->MaxChannels is set to 1 for ddr4.
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MC_INIT_STATE_REG, MC1_CH0_CR_MC_INIT_STATE_REG, Controller, MC0_CH1_CR_MC_INIT_STATE_REG, 1);
      McInitState.Data = MrcReadCR (MrcData, Offset);
      McInitState.Bits.Rank_occupancy = 0;
      MrcWriteCR (MrcData, Offset, McInitState.Data);
    }

    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      RankMask   = ChannelOut->ValidRankBitMask;

      // Set the Rank_occupancy per channel.
      // For LPDDR technologies, the mapping is the following:
      //    Bit     Ch      Rank
      //    0   -   0         0
      //    1   -   0         1
      //    2   -   1         0
      //    3   -   1         1
      //    4   -   0         2
      //    5   -   0         3
      //    6   -   1         2
      //    7   -   1         3
      if (Lpddr) {
        if (((Channel % 2) == 0)) {
          GetSetVal = (RankMask & 0x3); // Bits 0/1
          GetSetVal |= (UINT64) ((RankMask & 0xC) << 2); // Bits 4/5
          // Only write the register on Channel 1/3 for LP.
          continue;
        } else {
          // Channel 1/3 rank pop start at bits 2
          GetSetVal |= (UINT64) ((RankMask & 0x3) << 2); // Bits 2/3
          GetSetVal |= (UINT64) ((RankMask & 0xC) << 4); // Bits 6/7
          //Set the channel to the previous channel as 1/3 do not have registers.
          IpChannel = Channel - 1;
        }
      } else {
        IpChannel = Channel;
        GetSetVal = ChannelOut->ValidRankBitMask;
      }
      MrcGetSetMcCh (MrcData, Controller, IpChannel, GsmMccRankOccupancy, WriteCached | PrintValue, &GetSetVal);
    } // Channel
  } // Controller
}

/**
  This function configures probeless config register.

  @param[in, out] MrcData - All the MRC global data.
**/
void
MrcProbelessConfig (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcDebug        *Debug;
  UINT32          Controller;
  UINT32          Channel;
  UINT32          IpChannel;
  UINT32          Offset;
  BOOLEAN         Lpddr;
  MC0_MCDECS_MISC_STRUCT              McdecsMisc;
  MC0_DDRPL_CFG_DTF_STRUCT            ProbelessCfg;
  MC0_CH0_CR_PL_AGENT_CFG_DTF_STRUCT  PlAgentCfg;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Lpddr   = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    if ((Inputs->UlxUlt) && (Inputs->CpuStepping == csTglA0)) {
      Offset = OFFSET_CALC_CH (MC0_MCDECS_MISC_REG, MC1_MCDECS_MISC_REG, Controller);
      McdecsMisc.Data = MrcReadCR (MrcData, Offset);
      McdecsMisc.Bits.Spare_RW |= MRC_BIT1;
      MrcWriteCR (MrcData, Offset, McdecsMisc.Data);
    }

    Offset = OFFSET_CALC_CH (MC0_DDRPL_CFG_DTF_REG, MC1_DDRPL_CFG_DTF_REG, Controller);
    ProbelessCfg.Data = MrcReadCR (MrcData, Offset);

    //If channel 0 is populated, program MCHTrace to 0. Else program to 1.
    //If DDR4 or LP memory subchannel 0 is populated for channel 0, program SCHTrace to 0.
    //Else if not DDR4 and subchannel 0 is not populated for channel 0, program SCHTrace to 1.
    Channel = (MrcChannelExist (MrcData, Controller, 0)) ? 0 : 1;
    ProbelessCfg.Bits.MCHTrace = Channel;
    ProbelessCfg.Bits.SCHTrace = Channel;

    //If ECC is enabled, set ECC_EN to 1.
    ProbelessCfg.Bits.ECC_EN = Outputs->EccSupport;

    //Set DDRPL_Activate based on setup option ProbelessTrace Enable or Disable. Default is Disabled.
    ProbelessCfg.Bits.DDRPL_Activate = Inputs->ProbelessTrace;

    if (Inputs->SafeMode) {
      ProbelessCfg.Bits.DDRPL_GLB_DRV_GATE_DIS = 1;
    }

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "MCHTrace = 0x%x\nSCHTrace = 0x%x\nECC_EN = 0x%x\nDDRPL_Activate = 0x%x\n",
      ProbelessCfg.Bits.MCHTrace,
      ProbelessCfg.Bits.SCHTrace,
      ProbelessCfg.Bits.ECC_EN,
      ProbelessCfg.Bits.DDRPL_Activate
      );
    MrcWriteCR (MrcData, Offset, ProbelessCfg.Data);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        IpChannel = LP_IP_CH (Lpddr, Channel);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_PL_AGENT_CFG_DTF_REG, MC1_CH0_CR_PL_AGENT_CFG_DTF_REG, Controller, MC0_CH1_CR_PL_AGENT_CFG_DTF_REG, IpChannel);
        PlAgentCfg.Data = MrcReadCR (MrcData, Offset);
        PlAgentCfg.Bits.data_trace_mode = 3;
        MrcWriteCR (MrcData, Offset, PlAgentCfg.Data);
      }
    } // Channel
  } // Controller
}

/**
  This function provides the initial configuration of the Memory Controller's
  maintenance services.  Some items are disabled during MRC training, and will need
  to be configured at the end of MRC.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcMaintenanceConfig (
  IN  MrcParameters * const MrcData
  )
{
  // Configure Rank Occupancy:
  MrcRankOccupancy (MrcData);
  // Disable Dqs Oscillator at the start of MRC.
  MrcDisableDqsOscillatorMc (MrcData);
  // Configure probeless.
  MrcProbelessConfig (MrcData);
}

