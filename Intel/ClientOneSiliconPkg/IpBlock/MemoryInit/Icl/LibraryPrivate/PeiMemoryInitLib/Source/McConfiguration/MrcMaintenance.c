/** @file
  This module contains functions to configure and use Memory Controller
  maintenance features.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
  MrcOutput *Outputs;
  UINT32    Channel;
  UINT32    Offset;
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParams;

  Outputs = &MrcData->Outputs;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = OFFSET_CALC_CH (
                  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG,
                  CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG,
                  Channel
                  );
      Lp4DqsOsclParams.Data = MrcReadCR (MrcData, Offset);
      Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD          = 0;
      Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL         = 1;

      MrcWriteCR (MrcData, Offset, Lp4DqsOsclParams.Data);
    } // MrcChannelExists
  } // For Channel
}

/**
  This function executes the requested ZQ command for DDR4 / LPDDR4 DRAMS.
  This function will wait the appropriate wait time as specified in the JEDEC spec.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  ChBitMask - Bit mask of channels to run.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcSendZq (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                ChBitMask
  )
{
  MrcStatus   Status;
  UINT32      Offset;
  UINT32      Channel;

  CH0_CR_MRS_FSM_CONTROL_STRUCT   FsmCtl;
  CH0_CR_MRS_FSM_CONTROL_STRUCT   FsmCtlCurrentData[MAX_CHANNEL];

  Status = mrcSuccess;

  // Use MRS FSM to send ZQ commands on all populated channels / ranks.
  // DDR4:   FSM will issue ZQCL and wait tZQINIT
  // LPDDR4: FSM will issue MPC ZQCAL START and LATCH, and wait tZQCAL / tZQLAT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) != 0) {
      // Save FSM CTRL
      Offset = MrcGetMrsFsmCtlOffset (MrcData, Channel);
      FsmCtlCurrentData[Channel].Data = MrcReadCR64 (MrcData, Offset);

      FsmCtl.Data = 0;
      FsmCtl.Bits.do_ZQCL = 1;
      FsmCtl.Bits.reset_flow = 1;  // FSM should wait tZQINIT
      MrcWriteCR64 (MrcData, Offset, FsmCtl.Data);
    }
  }

  // Will run on both channels in parallel
  Status = MrcProgramMrsFsm (MrcData, ChBitMask);

  // Restore FSM CTRL
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) != 0) {
      Offset = MrcGetMrsFsmCtlOffset(MrcData, Channel);
      MrcWriteCR64 (MrcData, Offset, FsmCtlCurrentData[Channel].Data);
    }
  }

  return Status;
}

/**
  Issue ZQ calibration command on all ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData    - include all the MRC data
  @param[in] chBitMask  - Channel bit mask to be sent to.
  @param[in] ZqType     - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcIssueZQ (
  IN  MrcParameters *const  MrcData,
  IN  const UINT8           chBitMask,
  IN  MrcZqType             ZqType
  )
{
  MrcOutput     *Outputs;
  MrcStatus     Status;
  MrcDebug      *Debug;
  char          *StrZqType;

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
  Status = MrcSendZq (MrcData, chBitMask);

  return Status;
}

/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in]  MrcData   - Include all MRC global data.
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
  CH0_CR_DDR_MR_COMMAND_STRUCT          MrCommand;
  UINT64                                Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout

  Offset = CH0_CR_DDR_MR_COMMAND_REG +
    ((CH1_CR_DDR_MR_COMMAND_REG - CH0_CR_DDR_MR_COMMAND_REG) * Channel);

  // Remap target rank if ddr4_1dpc is enabled on this channel
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, ReadNoCache, &Ddr4OneDpc);
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
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));
  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  Data = (Address & 0xFF);
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
  MrCommand.Bits.DDR4_MA13       = 0;
  MrcWriteCR (MrcData, Offset, MrCommand.Data);

  //
  // Wait till MRH is done sending the command
  //
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, Offset);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  }

  return mrcSuccess;
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
  // Disable Dqs Oscillator at the start of MRC.
  MrcDisableDqsOscillatorMc (MrcData);
}

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Channel     - the channel to work on
  @param[in]  SubChannel  - the sub-channel to work on
  @param[in]  Rank        - the rank to work on
  @param[in]  Address     - MRR address
  @param[out] Data        - MRR Data array per SDRAM device

  @retval mrcSuccess    - MRR was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrr (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  OUT UINT8               Data[4]
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcChannelOut   *ChannelOut;
  MrcOutput             *Outputs;
  UINT32                OffsetMrrResult;
  UINT32                CurrCpuBit;
  UINT32                CurrCpuByte;
  UINT32                CpuByteCnt;
  UINT32                DeviceCnt;
  UINT32                CurrDramBit;
  UINT32                DramByte;
  UINT32                BitVal;
  UINT32                ByteStart;
  UINT32                MaxDevice;
  CH0_CR_DDR_MR_RESULT_0_STRUCT  MrResult;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ControllerIn   = &Inputs->Controller[0];
  ChannelIn      = &ControllerIn->Channel[Channel];
  ChannelOut     = &Outputs->Controller[0].Channel[Channel];
  CurrCpuByte    = 0;
  MaxDevice      = 2;
  ByteStart      = (ChannelOut->ByteStart[SubChannel]);
  MrcCall->MrcSetMem(Data, 4 * sizeof(Data[0]), 0);

  OffsetMrrResult = OFFSET_CALC_CH (CH0_CR_DDR_MR_RESULT_0_REG, CH1_CR_DDR_MR_RESULT_0_REG, Channel);

  // Send the MRR
  MrcRunMrh(MrcData, Channel, SubChannel, Rank, Address, 1, MRC_MRH_CMD_MRR);
  MrResult.Data = MrcReadCR (MrcData, OffsetMrrResult);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcIssueMrr on ch %d subch %d rank %d: MR%d --> 0x%08X\n", Channel, SubChannel, Rank, Address, MrResult.Data);

  for (DeviceCnt = 0; DeviceCnt < MaxDevice; DeviceCnt++) {
    DramByte = (2 * DeviceCnt) + ByteStart; // LPDDR4 only provides feedback from Bytes 0 and 2 within the SubChannel.
    // Find which CPU byte is mapped to the relevant DRAM byte
    for (CpuByteCnt = 0; CpuByteCnt < Outputs->SdramCount; CpuByteCnt++) {
      if (DramByte == ChannelIn->DqsMapCpu2Dram[CpuByteCnt]) {
        CurrCpuByte = CpuByteCnt;
        break;
      }
    }
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Dev %d, DRAM byte: %d -> CPU byte: %d\n", DeviceCnt, DramByte, CurrCpuByte);
    for (CurrCpuBit = 0; CurrCpuBit < MAX_BITS; CurrCpuBit++) {
      //
      // The actual DRAM bit that is connected to the current CPU DQ pin
      //
      CurrDramBit = ChannelIn->DqMapCpu2Dram[CurrCpuByte][CurrCpuBit] - (8 * DramByte); // Subtract 8xDramByte
      BitVal = (MrResult.Data8[DeviceCnt] >> CurrCpuBit) & 1; // The 0/1 value that came from the DRAM bit
      Data[DeviceCnt] |= (BitVal << CurrDramBit);             // Putting the value in the correct place
    }
  }  // for DeviceCnt

  return mrcSuccess;
}

/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - the channel to work on
  @param[in] SubChannel   - the sub-channel to work on
  @param[in] Rank         - the rank to work on
  @param[in] Address      - MRW address
  @param[in] Data         - MRW Data
  @param[in] InitMrw      - when TRUE, command is stretched (used before CA training is done)
  @param[in] ChipSelect2N - when TRUE, use 2N stretch mode for CS (used before CA training is done)
  @param[in] DebugPrint   - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              InitMrw,
  IN BOOLEAN              ChipSelect2N,
  IN BOOLEAN              DebugPrint
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MrcOutput *Outputs;
  INT64     GetSetVal;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  if (ChipSelect2N) {
    //
    // Enable 2N stretch mode for CS
    //
    GetSetVal = 1;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLpddr2nCsMrw, WriteNoCache, &GetSetVal);
  }

  //
  // Send the MRW
  //
  Status = MrcRunMrh (MrcData, Channel, SubChannel, Rank, Address, Data, (InitMrw) ? MRC_MRH_CMD_LP3_INIT_MRW : MRC_MRH_CMD_MRW);

  if (DebugPrint && !Outputs->JedecInitDone) {
    MRC_DEBUG_MSG(
      Debug, MSG_LEVEL_NOTE,
      "MrcIssueMrw on ch %d subch %d rank %d: MR%d, Opcode=0x%02X, InitMrw=%d, 2N_CS=%d\n",
      Channel, SubChannel, Rank, Address, Data, InitMrw, ChipSelect2N
    );
  }

  if (ChipSelect2N) {
    //
    // Disable 2N stretch mode for CS
    //
    GetSetVal = 0;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLpddr2nCsMrw, WriteNoCache, &GetSetVal);
  }

  return Status;
}

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] DimmValue       - Dimm Values to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRSAll (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN       UINT8          RankMask,
  IN const UINT8          MR,
  IN const UINT16 *const  DimmValue
  )
{
  MrcStatus             Status;
  MrcChannelOut         *ChannelOut;
  UINT32                Rank;
  UINT16                MrhData;
  MRC_MRH_ADDRESS_TYPE  MrhAddr;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  RankMask &= ChannelOut->ValidRankBitMask;
  Status = mrcSuccess;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & RankMask) == 0) {
      continue;
    }
    MrhAddr.Ddr3Ddr4Mrs.MrNum = MR;
    MrhAddr.Ddr3Ddr4Mrs.MA12To8 = (DimmValue[Rank / 2] >> 8) & 0x1F;
    MrhData = DimmValue[Rank / 2] & 0xFF;
    Status = MrcRunMrh (
              MrcData,
              Channel,
              0, // Subchannel
              Rank,
              MrhAddr.Data8,
              MrhData,
              MRC_MRH_CMD_MRS
              );
    if (Status != mrcSuccess) {
      break;
    }
  }

  return Status;
}

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - Include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] Value           - Value to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRS (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN UINT8                 RankMask,
  IN const UINT8           MR,
  IN const UINT16          Value
  )
{
  MrcChannelOut *ChannelOut;
  MrcStatus     Status;
  UINT32        Rank;
  UINT16        MrhData;
  MRC_MRH_ADDRESS_TYPE  MrhAddr;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
  RankMask &= ChannelOut->ValidRankBitMask;
  Status = mrcSuccess;

  MrhAddr.Ddr3Ddr4Mrs.MrNum = MR;
  MrhAddr.Ddr3Ddr4Mrs.MA12To8 = (Value >> 8) & 0x1F;
  MrhData = Value & 0xFF;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & RankMask) == 0) {
      continue;
    }
    Status = MrcRunMrh (
              MrcData,
              Channel,
              0, // Subchannel
              Rank,
              MrhAddr.Data8,
              MrhData,
              MRC_MRH_CMD_MRS
              );
    if (Status != mrcSuccess) {
      break;
    }
  }

  return Status;
}

/**
  Use MRS Burst FSM to program all relevant MR registers in one quick operation.
  Can only be used on ULT/ULX (up to 2 ranks, no ECC).

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  ChannelMask - bit mask of channels to run.

  @retval mrcSuccess    - MRS FSM was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm (
  IN MrcParameters *const MrcData,
  IN UINT32               ChannelMask
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcOutput             *Outputs;
  MrcStatus             Status;
  INT64                 GetSetVal;
  UINT32                Timeout;
  UINT32                OffsetMrCommand;
  UINT32                OffsetMrsFsm;
  UINT8                 Channel;
  BOOLEAN               Busy;
  CH0_CR_DDR_MR_COMMAND_STRUCT  MrCommand;
  CH0_CR_MRS_FSM_RUN_STRUCT     MrsFsm;


  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug = &Outputs->Debug;
  Status = mrcSuccess;

  // Disable Self Refresh when using MRS FSM.
  // Function will wait for MC to exit self refresh.
  Status = MrcSelfRefreshState (MrcData, MRC_SR_EXIT);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // Make sure both MRH and MRS FSM are not busy
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    if (((1 << Channel) & ChannelMask) == 0) {
      continue;
    }
    OffsetMrCommand = CH0_CR_DDR_MR_COMMAND_REG +
      (CH1_CR_DDR_MR_COMMAND_REG - CH0_CR_DDR_MR_COMMAND_REG) * Channel;

    OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Channel);

    Timeout = (UINT32)MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
    do {
      MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
      MrsFsm.Data = MrcReadCR (MrcData, OffsetMrsFsm);
      Busy = (MrCommand.Bits.Busy == 1) || (MrsFsm.Bits.Run == 1);
    } while (Busy && ((UINT32)MrcCall->MrcGetCpuTime (MrcData) < Timeout));
    if (Busy) {
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
      return mrcDeviceBusy;
    }
  }

  //
  // Start MRS FSM on both channels in parallel
  //
  MrsFsm.Data = 0;
  MrsFsm.Bits.Run = 1;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (((1 << Channel) & ChannelMask) != 0) {
        OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Channel);
        MrcWriteCR (MrcData, OffsetMrsFsm, MrsFsm.Data);
      }
    }
  }
  //
  // Poll for completion
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    if (((1 << Channel) & ChannelMask) == 0) {
      continue;
    }

    OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Channel);

    Timeout = (UINT32)MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
    do {
      MrsFsm.Data = MrcReadCR (MrcData, OffsetMrsFsm);
      Busy = (MrsFsm.Bits.Run == 1);
    } while (Busy && ((UINT32)MrcCall->MrcGetCpuTime (MrcData) < Timeout));
    if (Busy) {
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Timed out waiting for MRS FSM finish!\n");
      return mrcDeviceBusy;
    }
  }

  // Re-enable Self Refresh when done using MRS FSM
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableSr, WriteNoCache, &GetSetVal);

  return Status;
}
