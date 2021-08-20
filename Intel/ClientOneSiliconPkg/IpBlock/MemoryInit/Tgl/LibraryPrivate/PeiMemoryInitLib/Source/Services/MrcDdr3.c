/** @file
  This file includes all the DDR3 specific characteristic functions.

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
#include "MrcDdr3.h"
#include "MrcDdrCommon.h"
#include "MrcRefreshConfiguration.h"
#include "MrcPowerModes.h"
#include "MrcMemoryScrub.h"
#include "MrcMcOffsets.h"
#include "MrcCpgcApi.h"
#include "MrcMemoryApi.h"

// Module external functions
/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData    - include all the MRC data
  @param[in] Controller - Controller to send MRS.
  @param[in] Channel    - Channel to send command to
  @param[in] RankMask   - Rank mask for which command will be sent to
  @param[in] MR         - MRS command to be sent
  @param[in] DimmValue  - Dimm Values to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRSAll (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel,
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

  ChannelOut  = &MrcData->Outputs.Controller[Controller].Channel[Channel];
  RankMask    &= ChannelOut->ValidRankBitMask;
  Status      = mrcSuccess;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & RankMask) == 0) {
      continue;
    }
    MrhAddr.Ddr3Ddr4Mrs.MrNum   = MR;
    MrhAddr.Ddr3Ddr4Mrs.MA12To8 = (DimmValue[Rank / 2] >> 8) & 0x1F;
    MrhData = DimmValue[Rank / 2] & 0xFF;
    // MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "MrcWriteMRSAll: Mc %d, Ch %d, Rank %d, MR%d = 0x%04X\n", Controller, Channel, Rank, MR, MrhData);
    Status = MrcRunMrh (MrcData, Controller, Channel, Rank, MrhAddr.Data8, MrhData, MRC_MRH_CMD_MRS, FALSE);
    if (Status != mrcSuccess) {
      break;
    }
  }

  return Status;
}

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData    - Include all the MRC data
  @param[in] Controller - Controller to send MRS.
  @param[in] Channel    - Channel to send MRS.
  @param[in] RankMask   - Rank mask for which command will be sent to
  @param[in] MR         - MRS command to be sent
  @param[in] Value      - Value to be sent

  @retval MrcStatus
**/
MrcStatus
MrcWriteMRS (
  IN MrcParameters  *const MrcData,
  IN       UINT32          Controller,
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

  ChannelOut  = &MrcData->Outputs.Controller[Controller].Channel[Channel];
  RankMask    &= ChannelOut->ValidRankBitMask;
  Status      = mrcSuccess;

  MrhAddr.Ddr3Ddr4Mrs.MrNum   = MR;
  MrhAddr.Ddr3Ddr4Mrs.MA12To8 = (Value >> 8) & 0x1F;
  MrhData = Value & 0xFF;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & RankMask) == 0) {
      continue;
    }
    // MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "MrcWriteMRS: Mc %d, Ch %d,Rank %d, MR%d = 0x%04X\n", Controller, Channel, Rank, MR, Value);
    Status = MrcRunMrh (MrcData, Controller, Channel, Rank, MrhAddr.Data8, MrhData, MRC_MRH_CMD_MRS, FALSE);
    if (Status != mrcSuccess) {
      break;
    }
  }

  return Status;
}

/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Controller   - Controller to send MRW.
  @param[in] Channel      - the channel to work on
  @param[in] Rank         - the rank to work on
  @param[in] Address      - MRW address
  @param[in] Data         - MRW Data
  @param[in] DebugPrint   - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              DebugPrint
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MrcOutput *Outputs;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  // Send the MRW
  Status = MrcRunMrh (
            MrcData,
            Controller,
            Channel,
            Rank,
            Address,
            Data,
            MRC_MRH_CMD_MRW,
            DebugPrint
            );

  if (DebugPrint && !Outputs->JedecInitDone) {
    MRC_DEBUG_MSG (
      Debug, MSG_LEVEL_NOTE,
      "MrcIssueMrw on mc %d ch %d rank %d: MR%d, Opcode=0x%02X\n",
      Controller, Channel, Rank, Address, Data
      );
  }

  return Status;
}

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData    - Include all MRC global data.
  @param[in]  Controller - the controller to issue MRR.
  @param[in]  Channel    - the channel to work on
  @param[in]  Rank       - the rank to work on
  @param[in]  Address    - MRR address
  @param[out] Data       - MRR Data array per SDRAM device

  @retval mrcSuccess     - MRR was executed successfully
  @retval mrcDeviceBusy  - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrr (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
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
  MrcOutput             *Outputs;
  UINT32                OffsetMrrResult;
  UINT32                CurrCpuBit;
  UINT32                CurrCpuByte;
  UINT32                CpuByteCnt;
  UINT32                DeviceCnt;
  UINT32                DeviceMax;
  UINT32                CurrDramBit;
  UINT32                DramByte;
  UINT32                BitVal;
  UINT32                IpChannel;
  BOOLEAN               Lpddr;
  MC0_CH0_CR_DDR_MR_RESULT_0_STRUCT  MrResult;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[Controller];
  ChannelIn     = &ControllerIn->Channel[Channel];
  CurrCpuByte   = 0;
  Lpddr         = Outputs->Lpddr;
  IpChannel     = LP_IP_CH (Lpddr, Channel);
  MrcCall->MrcSetMem (Data, 4 * sizeof (Data[0]), 0);

  if (Lpddr) {
    DeviceMax = (Outputs->LpByteMode) ? 2 : 1;
  } else {
    DeviceMax = 4;
  }

  // Send the MRR
  MrcRunMrh (MrcData, Controller, Channel, Rank, Address, 1, MRC_MRH_CMD_MRR, FALSE);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcIssueMrr on mc %u ch %u rank %u: MR%d\n", Controller, Channel, Rank, Address);

  OffsetMrrResult = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_RESULT_0_REG, MC1_CH0_CR_DDR_MR_RESULT_0_REG, Controller, MC0_CH1_CR_DDR_MR_RESULT_0_REG, IpChannel);
  MrResult.Data = MrcReadCR (MrcData, OffsetMrrResult);

  // Device now maps per byte with LPDDR.
  for (DeviceCnt = 0; DeviceCnt < DeviceMax; DeviceCnt++) {
    DramByte = DeviceCnt;
    // Find which CPU byte is mapped to the relevant DRAM byte
    for (CpuByteCnt = 0; CpuByteCnt < Outputs->SdramCount; CpuByteCnt++) {
      if (DramByte == ChannelIn->DqsMapCpu2Dram[CpuByteCnt]) {
        CurrCpuByte = CpuByteCnt;
        break;
      }
    }

    for (CurrCpuBit = 0; CurrCpuBit < MAX_BITS; CurrCpuBit++) {
      // The actual DRAM bit that is connected to the current CPU DQ pin
      CurrDramBit = ChannelIn->DqMapCpu2Dram[CurrCpuByte][CurrCpuBit] - 8 * DramByte; // Subtract 8xDramByte
      BitVal = (MrResult.Data8[DeviceCnt] >> CurrCpuBit) & 1; // The 0/1 value that came from the DRAM bit
      Data[DeviceCnt] |= (BitVal << CurrDramBit);             // Putting the value in the correct place
    }
  }  // for DeviceCnt

  return mrcSuccess;
}

/**
  Use MRS Burst FSM to program all relevant MR registers in one quick operation.
  Can only be used on ULT/ULX (up to 2 ranks, no ECC).
  Runs on all populated controllers, channels, and ranks.

  @param[in]  MrcData - Include all MRC global data.

  @retval mrcSuccess    - MRS FSM was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  INT64               GetSetVal;
  UINT64              Timeout;
  UINT32              OffsetMrCommand;
  UINT32              OffsetMrsFsm;
  UINT32              Channel;
  UINT32              Controller;
  UINT32              IpChannel;
  BOOLEAN             Busy;
  BOOLEAN             Lpddr;
  MC0_CH0_CR_DDR_MR_COMMAND_STRUCT  MrCommand;
  MC0_CH0_CR_MRS_FSM_RUN_STRUCT     MrsFsm;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  Lpddr   = Outputs->Lpddr;

  // Disable Self Refresh when using MRS FSM.
  // Function will wait for MC to exit self refresh.
  Status = MrcSelfRefreshState (MrcData, MRC_SR_EXIT);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Make sure both MRH and MRS FSM are not busy
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      OffsetMrCommand = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_COMMAND_REG, MC1_CH0_CR_DDR_MR_COMMAND_REG, Controller, MC0_CH1_CR_DDR_MR_COMMAND_REG, IpChannel);
      OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Controller, IpChannel);

      Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout
      do {
        MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
        MrsFsm.Data    = MrcReadCR (MrcData, OffsetMrsFsm);
        Busy = (MrCommand.Bits.Busy == 1) || (MrsFsm.Bits.Run == 1);
      } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));
      if (Busy) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
        return mrcDeviceBusy;
      }
    } // Channel
  } // Controller

  // Start MRS FSM on both channels in parallel
  MrsFsm.Data = 0;
  MrsFsm.Bits.Run = 1;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
        IpChannel = LP_IP_CH (Lpddr, Channel);
        OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Controller, IpChannel);
        MrcWriteCR (MrcData, OffsetMrsFsm, MrsFsm.Data);
      }
    } // Channel
  } // Controller

  // Poll for completion
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      OffsetMrsFsm = MrcGetMrsRunFsmOffset (MrcData, Controller, IpChannel);

      Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout
      do {
        MrsFsm.Data = MrcReadCR (MrcData, OffsetMrsFsm);
        Busy = (MrsFsm.Bits.Run == 1);
      } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));
      if (Busy) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for MRS FSM finish!\n");
        return mrcDeviceBusy;
      }
    } // Channel
  } // Controller

  // Re-enable Self Refresh when done using MRS FSM
  GetSetVal = 1;
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableSr, WriteNoCache, &GetSetVal);

  return Status;
}

