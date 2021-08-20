/** @file
  The third stage of the write training is determining the PI setting for
  each byte strobe to make sure that data is sent at the optimal location.
  In order to do that a pattern of alternating zeros and ones is written to
  a block of the memory, and then read out.  By identifying the location
  where it is farthest away from where errors are shown the DQS will be
  aligned to the center of the eye.

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
//
// Include files
//
#include "MrcWriteDqDqs.h"
#include "MrcMemoryApi.h"
#include "MrcDdr4.h"
#include "MrcLpddr4.h"
#include "MrcLpddr5.h"
#include "MrcLpddr5Registers.h"
#include "MrcCpgcOffsets.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcGears.h"
#include "MrcChipApi.h"

/**
  This function executes the write timing centering.
  Center Tx DQS-DQ using moderate pattern with 1D eye.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus   - If it succeeded, returns mrcSuccess
**/
MrcStatus
MrcWriteTimingCentering (
  IN     MrcParameters *const MrcData
  )
{
  MRC_MarginTypes MarginParam;
  MrcStatus       Status;
  INT64           RdRdsg;
  INT64           RdRddg;
  UINT8           ResetPerbit;
  UINT8           LoopCount;

  ResetPerbit = 0;
  LoopCount   = 10;

  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4) {
    MarginParam = WrTLp4;
  } else if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR5) {
    MarginParam = WrTLp5;
  } else {
    MarginParam = WrT;
  }

  MrcRelaxReadToReadSameRank (MrcData, TRUE, &RdRdsg, &RdRddg);

  Status = DQTimeCentering1D (MrcData, MarginParam, ResetPerbit, LoopCount, TRUE, FALSE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE, &RdRdsg, &RdRddg);

  return Status;
}

/**
  This function executes the write Voltage centering (DDR4 only).
  Center Tx DQ Vref using moderate pattern with 1D eye using PDA mode.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus   - If it succeeded, returns mrcSuccess
**/
MrcStatus
MrcWriteVoltageCentering (
  IN     MrcParameters *const MrcData
  )
{
  MrcStatus Status;
  UINT8     LoopCount;

  INT64     RdRdsg;
  INT64     RdRddg;

  LoopCount   = 10;

  MrcRelaxReadToReadSameRank (MrcData, TRUE, &RdRdsg, &RdRddg);

  Status = DQTimeCentering1D (MrcData, WrV, 0, LoopCount, TRUE, FALSE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE, &RdRdsg, &RdRddg);

  return Status;
}

/**
  this function executes the write timing centering in 2D.
    Final write timing centering using 2D algorithm and per bit optimization.

    @param[in] MrcData - Include all MRC global data.

    @retval MrcStatus -  If it succeeded, returns mrcSuccess

  **/
MrcStatus
MrcWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcStatus       Status;
  UINT8           EnPerBit;
  UINT8           EnRxDutyCycle;
  UINT8           ResetPerBit;
  UINT8           LoopCount;
  UINT8           En2D;
  //INT64           GetSetVal;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  Status = mrcSuccess;
  LoopCount = 15;
  EnRxDutyCycle = 0;

  if (!Inputs->WrTPbdDis) {
    EnPerBit = 1;
    ResetPerBit = 1;
    En2D = 0;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Calling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
      EnRxDutyCycle,
      EnPerBit,
      ResetPerBit,
      En2D
    );

    Status = DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      Outputs->McChBitMask,
      WrT,
      EnPerBit,
      EnRxDutyCycle,
      ResetPerBit,
      LoopCount,
      En2D
    );

    if (Inputs->DqBitDccRerunInWrTPbd && (Status == mrcSuccess) && Outputs->Gear2) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDQ BIT DCC Init Sweep being called within WrTPbd\n");
      //if ((Inputs->CpuModel == cmICL_ULX_ULT) && (Inputs->CpuStepping == csIclA0)) {
      //  GetSetVal = 0;
      //  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);
      //}

      //@todo Status = MrcDccDqBitInitSweep (MrcData);

      //if ((Inputs->CpuModel == cmICL_ULX_ULT) && (Inputs->CpuStepping == csIclA0)) {
      //  GetSetVal = 1;
      //  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);
      //  MrcResetSequence (MrcData);
      //}

      if (Status == mrcSuccess) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Repeat Calling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
          EnRxDutyCycle,
          EnPerBit,
          ResetPerBit,
          En2D
        );

        Status = DataTimeCentering2D (
          MrcData,
          Outputs->MarginResult,
          Outputs->McChBitMask,
          WrT,
          EnPerBit,
          EnRxDutyCycle,
          ResetPerBit,
          LoopCount,
          En2D
        );
      }
    }
    MrcPerBitDeskew (MrcData, Outputs->MarginResult, WrT);
  }

  if (mrcSuccess == Status) {
    EnPerBit = 0;
    ResetPerBit = 0;
    En2D = 1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nCalling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
      EnRxDutyCycle,
      EnPerBit,
      ResetPerBit,
      En2D
    );

    Status = DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      Outputs->McChBitMask,
      WrT,
      EnPerBit,
      EnRxDutyCycle,
      ResetPerBit,
      LoopCount,
      En2D
    );
  }

  return Status;
}

/**
  Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcRankMarginTool (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT16 mode = 0;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcCommandMargin    *CommandOut;
  MrcRecvEnMargin     *RecvEnOut;
  MrcWrLevelMargin    *WrLevelOut;
  MrcStatus           Status;
  INT64               GetSetDis;
  INT64               GetSetEn;
  UINT32              BERStats[4];
  UINT8               Rank;
  UINT8               Param;
  UINT8               RankMask;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Bit;
  UINT8               LcLoop;
  UINT8               BMap[MAX_SDRAM_IN_DIMM];
  UINT8               McChBitMask;
  UINT8               MaxMargin;
  UINT8               DqLoopCount;
  UINT8               CmdLoopCount;
  UINT8               MaxChannels;
  INT8                VrefOffsets[2];
  BOOLEAN             Lpddr;
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;
  BOOLEAN SkipVref;
  BOOLEAN SkipPrint;

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;
  Lpddr       = Outputs->Lpddr;
  MaxChannels = Outputs->MaxChannels;
  GetSetDis   = 0;
  GetSetEn    = 1;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) VrefOffsets, sizeof (VrefOffsets), 0);

  for (LcLoop = 0; LcLoop < (sizeof (BMap) / sizeof (BMap[0])); LcLoop++) {
    BMap[LcLoop] = LcLoop;
  }

  if (Inputs->BootMode == bmFast) {
    // Go to CPCG mode
    MrcSetNormalMode (MrcData, FALSE);
  }


#if DATA_EYE_MARGIN_SUPPORT
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    MaxMargin = GetVrefOffsetLimits (MrcData, WrV);
    EyeMargin (MrcData, 1 << Rank, WrT, WrV, 0, 0, -MAX_POSSIBLE_TIME, MAX_POSSIBLE_TIME, MaxMargin, 15, 1);
    MaxMargin = GetVrefOffsetLimits (MrcData, RdV);
    EyeMargin (MrcData, 1 << Rank, RdT, RdV, 0, 0, -MAX_POSSIBLE_TIME, MAX_POSSIBLE_TIME, MaxMargin, 15, 1);
  }
#endif

#if CMD_EYE_MARGIN_SUPPORT
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Param = 0; Param < MrcIterationCmd; Param++) {
      EyeMargin (MrcData, 1 << Rank, CmdT, CmdV, Param, 0x1F, -63, 63, 64, 10, 1);
    } // Param
  } // Rank
#endif

  // Enable command tri state during RMT training.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteNoCache, &GetSetDis);
      }
    }
  }

  DqLoopCount = 17;
  CmdLoopCount = (Lpddr) ? 10 : 17;


  // Data Margins
  // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
  // @todo Update with McChBitMask
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, DqLoopCount, NSOE, 0, 0, 8, PatWrRd, 0, 0);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select rank for REUT test
    RankMask  = 1 << Rank;
    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
      }
    }
    // Continue with next rank if this rank is not present on any channel
    if (!(McChBitMask)) {
      continue;
    }

    for (Param = RcvEna; Param <= WrLevel; Param++) {
      if (Param == WrDqsT) {
        continue;
      }
      // For Write/Read timing margining, we want to run traffic with Rd->Rd turnaround times of 4 and 5.
      // This statement depends on the order of MRC_MarginTypes.  If this enum's order changes, this
      // statement must change.
      if (Param == RdT) {
        Outputs->DQPat = RdRdTA;
      } else if (Param == RdV) {
        Outputs->DQPat = BasicVA;
      }
      if ((Param == RdV) || (Param == WrV)) {
        MaxMargin = GetVrefOffsetLimits (MrcData, Param);
      } else {
        MaxMargin = MAX_POSSIBLE_TIME;
      }
      Status = MrcGetBERMarginByte (
              MrcData,
              Outputs->MarginResult,
              McChBitMask,
              RankMask,
              RankMask,
              Param,
              mode,
              BMap,
              0,
              MaxMargin,
              0,
              BERStats
              );
      // Put worst case margin into the given Rank
      GetMarginCh (MrcData, Outputs->MarginResult, Param, RankMask, Rank);
    }
  } // Rank

  // Command Margins
  SetupIOTestCADB (MrcData, Outputs->McChBitMask, CmdLoopCount, NSOE, 1, 0);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select rank for REUT test
    RankMask  = 1 << Rank;
    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
      }
    }
    // Continue with next rank if this rank is not present on any channel
    if (!(McChBitMask)) {
      continue;
    }
    // Run test for Command Timing
    SkipVref  = TRUE;
    SkipPrint = TRUE;
    MrcBlockTrainResetToggle (MrcData, FALSE);
    if (Lpddr) {
      CmdLinearFindEdgesLpddr (MrcData, MrcIterationClock, McChBitMask, RankMask, 0x1F, !SkipPrint); // 1F means all CMD groups
    } else {
      CmdLinearFindEdges (MrcData, MrcIterationClock, McChBitMask, RankMask, 3, -64, 64, 6, 1, VrefOffsets, SkipPrint, SkipVref);
    }
    // Restore centered value
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationClock, RankMask, MRC_IGNORE_ARG_8, 0, 0);
        }
      }
    }
    Status = MrcResetSequence (MrcData);
    MrcBlockTrainResetToggle (MrcData, TRUE);

    // Run test for Cmd Voltage
    MaxMargin = GetVrefOffsetLimits (MrcData, CmdV);
    Status = MrcGetBERMarginCh (
              MrcData,
              Outputs->MarginResult,
              McChBitMask,
              (Lpddr) ? RankMask : 0xFF,
              RankMask,
              CmdV,
              mode,
              0,
              MaxMargin,
              0,
              BERStats
              );
    Status = MrcResetSequence (MrcData);
  } // Rank

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut        = &ControllerOut->Channel[Channel];
          CommandOut        = &ChannelOut->Command[Rank];
          CommandOut->Left  = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][0] / 10);
          CommandOut->Right = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][1] / 10);
          CommandOut->Low   = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][0] / 10);
          CommandOut->High  = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][1] / 10);
          RecvEnOut         = &ChannelOut->ReceiveEnable[Rank];
          RecvEnOut->Left   = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Controller][Channel][0][0] / 10);
          RecvEnOut->Right  = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Controller][Channel][0][1] / 10);
          WrLevelOut        = &ChannelOut->WriteLevel[Rank];
          WrLevelOut->Left  = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Controller][Channel][0][0] / 10);
          WrLevelOut->Right = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Controller][Channel][0][1] / 10);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              ChannelOut->RxDqPb[Rank][Byte][Bit].Left      = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Controller][Channel][0][0] / 10);
              ChannelOut->RxDqPb[Rank][Byte][Bit].Right     = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Controller][Channel][0][1] / 10);
              ChannelOut->TxDqPb[Rank][Byte][Bit].Left      = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Controller][Channel][0][0] / 10);
              ChannelOut->TxDqPb[Rank][Byte][Bit].Right     = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Controller][Channel][0][1] / 10);
              ChannelOut->RxDqVrefPb[Rank][Byte][Bit].Low   = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Controller][Channel][0][0] / 10);
              ChannelOut->RxDqVrefPb[Rank][Byte][Bit].High  = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Controller][Channel][0][1] / 10);
              ChannelOut->TxDqVrefPb[Rank][Byte][Bit].Low   = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Controller][Channel][0][0] / 10);
              ChannelOut->TxDqVrefPb[Rank][Byte][Bit].High  = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Controller][Channel][0][1] / 10);
            } // Bit
          } // Byte
        } // MrcRankExist
      } // Channel
    } // Controller
  } // for Rank

  // Disable CADB Deselects after RMT
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  // Disable command tristate back
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteNoCache, &GetSetEn);
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  // Print test results
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Testing: DQ LC = %d, Cmd LC = %d\n\n", DqLoopCount, CmdLoopCount);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%sRMT\nParams:\t\t%s\t%s\t%s\t%s\t  %s\t  %s\t %s\t %s\n",
    gStartTagStr, GsmGtDebugStrings[RecEnDelay], GsmGtDebugStrings[TxDqsDelay], "RxDqsDelay",
    GsmGtDebugStrings[TxDqDelay], GsmGtDebugStrings[RxVref], GsmGtDebugStrings[TxVref],
    GsmGtDebugStrings[ClkGrpPi], GsmGtDebugStrings[CmdVref]
    );
  for (Controller = 0;  Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u.R%u:\t", Controller, Channel, Rank);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\n",
            ((INT16) Outputs->MarginResult[LastRcvEna][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastRcvEna][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastWrLevel][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastWrLevel][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastRxT][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastRxT][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastTxT][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastTxT][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastRxV][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastRxV][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastTxV][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastTxV][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][1] / 10,
            ((INT16) Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][0]) / -10,
            Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][1] / 10
            );
        }
      } // Rank
    } // Ch
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sRMT\n", gStopTagStr);
#endif

  if (Inputs->BootMode == bmFast) {
    // Go to Normal mode
    MrcSetNormalMode (MrcData, TRUE);
  }

  return Status;
}

/**
  Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcRankMarginToolBit (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  INT64               GetSetDis;
  INT64               CmdTriStateSave[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8               PerBitMarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT16              MarginBit[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT16              MarginByte[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8               Rank;
  UINT8               RankMask;
  UINT8               Param;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Bit;
  UINT16              *BitResult;
  UINT8               Edge;
  UINT8               McChBitMask;
  UINT8               LoopCount;
  UINT8               ResultType;
  UINT8               MaxMargin;
  UINT8               MaxChannels;
#ifdef MRC_DEBUG_PRINT
  UINT8               BitIndex;
#endif

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MaxChannels = Outputs->MaxChannels;
  Status      = mrcSuccess;
  GetSetDis   = 0;
  MrcCall->MrcSetMem ((UINT8 *) CmdTriStateSave, sizeof (CmdTriStateSave), 0);

  if (Inputs->BootMode == bmFast) {
    // Set CPGC mode
    MrcSetNormalMode (MrcData, FALSE);
  }

  // Enable command tri state during RMT training.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!IS_MC_SUB_CH (Outputs->Lpddr, Channel))) {
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, ReadFromCache, &CmdTriStateSave[Controller][Channel]);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteCached, &GetSetDis);
      }
    }
  }

  if (Inputs->RMTLoopCount != 0) {
    LoopCount  = Inputs->RMTLoopCount;
  } else {
    LoopCount  = 17;
  }

  // Data Margins
  // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
  SetupIOTestBasicVA (MrcData, Outputs->McChBitMask, LoopCount, NSOE, 0, 0, 8, PatWrRd, 0, 0);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select rank for REUT test
    RankMask  = 1 << Rank;
    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
      }
    }
    // Continue with next rank if this rank is not present on any channel
    if (!(McChBitMask)) {
      continue;
    }

    for (Param = RdT; Param < WrLevel; Param++) {
      if (Param == WrDqsT) {
        continue;
      }

      ResultType = GetMarginResultType (Param);
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              MarginByte[Controller][Channel][Byte][Edge] = Outputs->MarginResult[ResultType][Rank][Controller][Channel][Byte][Edge];
            }
          }
        }
      }
      // For Write/Read timing margining, we want to run traffic with Rd->Rd turnaround times of 4 and 5.
      // This statement depends on the order of MRC_MarginTypes.  If this enum's order changes, this
      // statement must change.
      if (Param == RdT) {
        Outputs->DQPat = RdRdTA;
      } else if (Param == RdV) {
        Outputs->DQPat = BasicVA;
      }
      if ((Param == RdV) || (Param == WrV)) {
        MaxMargin = GetVrefOffsetLimits (MrcData, Param);
      } else {
        MaxMargin = MAX_POSSIBLE_TIME;
      }

      MrcGetMarginBit (MrcData, McChBitMask, Rank, MarginBit, MarginByte, Param, 0, MaxMargin, MRC_PRINTS_OFF);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }
          ChannelOut = &ControllerOut->Channel[Channel];
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                PerBitMarginResult[ResultType][Rank][Controller][Channel][Byte][Bit][Edge] = (UINT8) MarginBit[Controller][Channel][Byte][Bit][Edge];
              }
              BitResult = &MarginBit[Controller][Channel][Byte][Bit][0];
              switch (Param) {
                case WrV:
                  ChannelOut->TxDqVrefPb[Rank][Byte][Bit].High = (UINT8) BitResult[1];
                  ChannelOut->TxDqVrefPb[Rank][Byte][Bit].Low  = (UINT8) BitResult[0];
                  break;

                case WrT:
                  ChannelOut->TxDqPb[Rank][Byte][Bit].Right = (UINT8) BitResult[1];
                  ChannelOut->TxDqPb[Rank][Byte][Bit].Left  = (UINT8) BitResult[0];
                  break;

                case RdV:
                  ChannelOut->RxDqVrefPb[Rank][Byte][Bit].High = (UINT8) BitResult[1];
                  ChannelOut->RxDqVrefPb[Rank][Byte][Bit].Low  = (UINT8) BitResult[0];
                  break;

                case RdT:
                  ChannelOut->RxDqPb[Rank][Byte][Bit].Right = (UINT8) BitResult[1];
                  ChannelOut->RxDqPb[Rank][Byte][Bit].Left  = (UINT8) BitResult[0];
                  break;

                default:
                  break;
              } // switch (Param)
            } // for Bit
          } // for Byte
        } // for Channel
      } // for Controller
    } // for Param
  } // Rank

  // Restore command tri state setting
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!IS_MC_SUB_CH (Outputs->Lpddr, Channel))) {
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateSave[Controller][Channel]);
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  // Print test results
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Testing Per-Bit: DQ LC = %u\n\n", LoopCount);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%sRMTBIT\nParams:\t\t\t%s\t%s\t%s\t\t%s\n",
    gStartTagStr, "RxDqsDelay", GsmGtDebugStrings[TxDqDelay], GsmGtDebugStrings[RxVref], GsmGtDebugStrings[TxVref]
  );
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              BitIndex = (MAX_BITS * Byte) + Bit;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u.R%u.B%s%u:\t\t", Controller, Channel, Rank, (((BitIndex / 10) > 0) ? "" : "0"), BitIndex);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%4d %4d\t%4d %4d\t%4d %4d\t%4d %4d\n",
                -((INT16) PerBitMarginResult[LastRxT][Rank][Controller][Channel][Byte][Bit][0]),
                PerBitMarginResult[LastRxT][Rank][Controller][Channel][Byte][Bit][1],
                -((INT16) PerBitMarginResult[LastTxT][Rank][Controller][Channel][Byte][Bit][0]),
                PerBitMarginResult[LastTxT][Rank][Controller][Channel][Byte][Bit][1],
                -((INT16) PerBitMarginResult[LastRxV][Rank][Controller][Channel][Byte][Bit][0]),
                PerBitMarginResult[LastRxV][Rank][Controller][Channel][Byte][Bit][1],
                -((INT16) PerBitMarginResult[LastTxV][Rank][Controller][Channel][Byte][Bit][0]),
                PerBitMarginResult[LastTxV][Rank][Controller][Channel][Byte][Bit][1]
              );
            } // Bit
          } // Byte
        }
      } // Rank
    } // Ch
  } // Controller
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%sRMTBIT\n", gStopTagStr);
#endif

  if (Inputs->BootMode == bmFast) {
    // Set Normal Operation Mode
    MrcSetNormalMode (MrcData, TRUE);
  }

  return Status;
}

/**
  Perform Write Voltage Centering in 2D.
  Note: This function currently only supports param = WrV

  @param[in, out] MrcData       - Include all MRC global data.

  @retval MrcStatus -  if it succeded returns mrcSuccess
  @todo - Need option for loopcount
**/
MrcStatus
MrcWriteVoltageCentering2D (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput     *Inputs;
  MrcDebug           *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput          *Outputs;
  MrcChannelOut      *ChannelOut;
  MrcStatus          Status;
  UINT16             (*marginch)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8  ResultType;
  UINT8  ResultTypeT;
  UINT8  loopcount;
  UINT8  param;
  UINT8  paramT;
  UINT8  Controller;
  UINT8  Channel;
  UINT8  byte;
  UINT8  tim;
  UINT8  McChBitMask;
  UINT8  MaxChannels;
  UINT8  MaxTscale;
  INT8   SumEH;
  INT8   SumEHSign;
  INT8   TimePoints[3];
  UINT8  EHWeights[sizeof (TimePoints)];
  UINT16 mode;
  INT32  center;
  INT32  height;
  UINT32 value0[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32 BERStats[4];
  UINT32 TimScale[MAX_CONTROLLER][MAX_CHANNEL];
  INT32  centersum[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32 MinHalfMargin[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8  MaxMargin;

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  marginch    = &Outputs->MarginResult;
  MaxChannels = Outputs->MaxChannels;
  Status     = mrcSuccess;
  MaxTscale  = 12;
  SumEH      = 0;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) EHWeights, sizeof (EHWeights), 1);
  MrcCall->MrcSetMem ((UINT8 *) centersum, sizeof (centersum), 0);
  MrcCall->MrcSetMem ((UINT8 *) value0, sizeof (value0), 0);
  MrcCall->MrcSetMem ((UINT8 *) MinHalfMargin, sizeof (MinHalfMargin), 0xFF);
  loopcount = 17;
  TimePoints[0] = -4;
  TimePoints[1] = 4;
  TimePoints[2] = 0;

  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4)  {
    return MrcWriteVoltageCentering2D_DDR4 (MrcData);
  }
  // No input for param so set it to WrV
  param = WrV;
  MaxMargin = GetVrefOffsetLimits (MrcData, param);

  // Assume rank0 is always popuplated
  if (param == WrV) {
    paramT = WrT;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcFail;
    return Status;
  }

  ResultType  = GetMarginResultType (param);
  ResultTypeT = GetMarginResultType (paramT);

  SetupIOTestBasicVA (MrcData, Outputs->McChBitMask, loopcount, NSOE, 0, 0, 8, PatWrRd, 0, 0);

  // Calculate SumEH for use in weighting equations
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];
  }

  // Select rank for REUT test
  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist(MrcData, Controller, Channel)) {
        continue;
      }

      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      McChBitMask |= SelectReutRanks(MrcData, Controller, Channel, ChannelOut->ValidRankBitMask, FALSE, 0);
    }
  } // Controller


  // ####################################################
  // #############  Initialize EW/EH variables   ########
  // ####################################################
  Status = GetMarginCh (MrcData, Outputs->MarginResult, paramT, 0xF, 0);

  //
  // Update TimScale with results
  //

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      TimScale[Controller][Channel] = 0;
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }

      TimScale[Controller][Channel] = ((*marginch)[ResultTypeT][0][Controller][Channel][0][0] + (*marginch)[ResultTypeT][0][Controller][Channel][0][1]) / 20;
      //
      // It is possible TimScale[Controller][Channel] is 0.
      //
      if (!TimScale[Controller][Channel] || (TimScale[Controller][Channel] > MaxTscale)) {
        TimScale[Controller][Channel] = MaxTscale;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u TimScale is %d\n", Controller, Channel, TimScale[Controller][Channel]);
    } // Channel
  } // Controller


  Status = GetMarginCh (MrcData, Outputs->MarginResult, param, 0xF, 0);

  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u:\t\t\t\t\t", Controller, Channel);
    }
  }

  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "WrTime\tLow\tHigh\tHeight\tCenter\t\t");
    }
  } // Controller


  // Loop through all the Time Points to Test
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    // Setup Timing Offset for this point
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
          continue;
        }
        value0[Controller][Channel] = (INT32)(TimePoints[tim] * TimScale[Controller][Channel]) / MaxTscale;
        // There is no multicast per channel...
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          Status = ChangeMargin(MrcData, paramT, value0[Controller][Channel], 0, 0, Controller, Channel, 0, byte, 0, 1, 0);
        }
      } // Channel
    } // Controller

    // Run Margin Test
    mode = 0;
    Status = MrcGetBERMarginCh (
              MrcData,
              Outputs->MarginResult,
              McChBitMask,
              0xFF,
              0xFF,
              param,
              mode,
              1,
              MaxMargin,
              0,
              BERStats
              );

    // Store Results
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, Outputs->MaxChannels))) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
          continue;
        }

        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", value0[Controller][Channel]);

        height  = ((*marginch)[ResultType][0][Controller][Channel][0][1] + (*marginch)[ResultType][0][Controller][Channel][0][0]) / 10;
        center  = (INT32)((*marginch)[ResultType][0][Controller][Channel][0][1] - (*marginch)[ResultType][0][Controller][Channel][0][0]);
        MRC_DEBUG_MSG(
           Debug,
           MSG_LEVEL_NOTE,
           "%d\t%d\t%d\t%d\t",
           (*marginch)[ResultType][0][Controller][Channel][0][0] / 10,
           (*marginch)[ResultType][0][Controller][Channel][0][1] / 10,
           height,
           center / 20
           );

        // Calculate weight for this point
        centersum[Controller][Channel] += EHWeights[tim] * center;
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->centersum[%d][%d] = %d, \n", Controller, Channel, centersum[Controller][Channel]);

        // Determine the smallest half margin
        MinHalfMargin[Controller][Channel] = MIN(MinHalfMargin[Controller][Channel], (*marginch)[ResultType][0][Controller][Channel][0][0]);
        MinHalfMargin[Controller][Channel] = MIN(MinHalfMargin[Controller][Channel], (*marginch)[ResultType][0][Controller][Channel][0][1]);
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
      } // Channel
    } // Controller
  } // time points loop

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWtdCntr ");
  // ####################################################
  // ###########   Center Results per Mc/Ch    #############
  // ####################################################
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
        continue;
      }

      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

      // Calculate CenterPoint.  Round to Nearest Int
      SumEHSign           = (centersum[Controller][Channel] < 0) ? (-1) : 1;

      centersum[Controller][Channel] = (centersum[Controller][Channel] + 10 * SumEH * SumEHSign) / (20 * SumEH);

      // Apply new centerpoint
      // Only Byte 0 on Channel 0 is needed to update DIMM Vref
      Status = ChangeMargin(MrcData, param, centersum[Controller][Channel], 0, 0, Controller, Channel, 0xFF, 0, 0, 1, TRUE);

      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t%d\t\t\t\t\t", centersum[Controller][Channel]);

      // Update MrcData for future tests
      (*marginch)[ResultType][0][Controller][Channel][0][0] = ((*marginch)[ResultType][0][Controller][Channel][0][0]) + (UINT16)(10 * (centersum[Controller][Channel]));
      (*marginch)[ResultType][0][Controller][Channel][0][1] = ((*marginch)[ResultType][0][Controller][Channel][0][1]) - (UINT16)(10 * (centersum[Controller][Channel]));
    } // Channel
  } // Controller


  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  // Clean up
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);

  return Status;
}

/**
  Perform Write Voltage Centering in 2D For DDR4 PDA mode.
  Note: This function currently only supports param = WrV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     McChBitMask - Channel bit mask.
  @param[in]     Rank        - The particular rank being centered
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
WriteVoltageCentering2D_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                McChBitMask,
  IN     UINT8                Rank,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D
  )
{
  static const INT8                       TimePoints[] = { 0, -8, 8 };
  static const UINT8                      EHWeights[sizeof (TimePoints)] = { 1, 1, 1 };
  static const UINT8                      paramT = WrT;
  static const UINT8                      paramV = WrV;
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcOutput                               *Outputs;
  MrcChannelOut                           *ChannelOut;
#ifdef MRC_DEBUG_PRINT
  MrcRankOut                              *RankOut;
#endif
  MrcStatus                               Status;
  UINT8                                   ResultType;
  UINT8                                   Controller;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   RankMask;
  UINT8                                   lcloop;
  UINT8                                   tim;
#ifdef MRC_DEBUG_PRINT
  UINT8                                   Edge;
#endif
  UINT8                                   BMap[MAX_SDRAM_IN_DIMM];
  INT8                                    SumEH;
  INT8                                    SumEHSign;
  UINT8                                   MaxTscale;
  UINT16                                  mode;
  INT16                                   center[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   value0[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  BERStats[4];
  UINT16                                  TimScale[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16                                   CenterSumByte[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16                                   CenterRank;
  UINT16                                  EyeShape[sizeof(TimePoints)][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8                                   MaxVrefOffset;
  UINT8                                   MaxChannels;

  MaxVrefOffset = GetVrefOffsetLimits (MrcData, paramV);
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MaxChannels = Outputs->MaxChannels;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  CenterRank = 0;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (lcloop = 0; lcloop < (sizeof (BMap) / sizeof (BMap[0])); lcloop++) {
    BMap[lcloop] = lcloop;
  }
  if (Outputs->Ddr4PdaEnable == FALSE) {
      Outputs->Ddr4PdaEnable = TRUE;
  }

  RankMask = (1 << Rank) & (Outputs->ValidRankMask);
  if (!RankMask) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "WriteVoltageCentering2D Called with no valid Ranks\n");
    return mrcWriteVoltage2DError;
  }

  SetupIOTestBasicVA (MrcData, McChBitMask, LoopCount, ABGSOE, 0, 0, 8, PatWrRd, 0, 0);

  // Calculate SumEH for use in weighting equations
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];

    // Loop once at nominal Vref point
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }

  // SumEH is used as divisor, make sure is never 0
  if (SumEH == 0) {
    SumEH = 1;
  }

  // Select rank for REUT test
  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      McChBitMask |= SelectReutRanks(MrcData, Controller, Channel, ChannelOut->ValidRankBitMask & RankMask, FALSE, 0);
    }
  } // Controller


  // ####################################################
  // ################  Initialize EW/EH variables  ######
  // ####################################################
  Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramT, Rank, RankMask);
  ResultType  = GetMarginResultType (paramT);

#ifdef MRC_DEBUG_PRINT
  if (En2D) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at ALL (2D) Timing Points - RankBitMask = 0x%X\n", RankMask);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at NOMINAL Timing - RankBitMask = 0x%X\n", RankMask);
  }


  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }

      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "MC%u.Ch%u", Controller, Channel);
      if (Channel == 0) {
        for (Byte = 0; Byte < Outputs->SdramCount - 1; Byte++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "        ");
        }
      }
    }
  } // Controller

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte    ");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d       ", Byte);
      }
    }
  } // Controller

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nTScale\t");
#endif // MRC_DEBUG_PRINT

  // Update TimScale to have the appropriate eye width (read from last saved parameters)
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }

      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (En2D > 0) {
          TimScale[Controller][Channel][Byte] =
             (
              MarginByte[ResultType][0][Controller][Channel][Byte][0] +
              MarginByte[ResultType][0][Controller][Channel][Byte][1]
              ) /
             20;
        } else {
          TimScale[Controller][Channel][Byte] = 1;
        }

        // It is possible sumT is 0.
        if (!(TimScale[Controller][Channel][Byte]) || (TimScale[Controller][Channel][Byte] > MaxTscale)) {
          TimScale[Controller][Channel][Byte] = MaxTscale;
        }

        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", TimScale[Controller][Channel][Byte]);
      }
    } // Channel
  } // Controller

  Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramV, 0, RankMask);
  ResultType  = GetMarginResultType (paramV);

  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################

  // Loop through all the Time Points to Test
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWrTime\t");

    // Setup Timing Offset for this point
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          value0[Controller][Channel][Byte] = (INT32)(TimePoints[tim] * TimScale[Controller][Channel][Byte]) / MaxTscale;
          Status = ChangeMargin(MrcData, paramT, value0[Controller][Channel][Byte], 0, 0, Controller, Channel, 0, Byte, 0, 1, 0);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", value0[Controller][Channel][Byte]);
        }
      } // Channel
    } // Controller

    // Run Margin Test
    mode = 0;
    Status = MrcGetBERMarginByte (
              MrcData,
              Outputs->MarginResult,
              McChBitMask,
              RankMask,
              RankMask,
              paramV,
              mode,
              BMap,
              1,
              MaxVrefOffset,
              0,
              BERStats
              );

    // condense the results to FirstRank
    GetMarginByte (MrcData, Outputs->MarginResult, paramV, Rank, RankMask);

#ifdef MRC_DEBUG_PRINT
    for (Edge = 0; Edge < MAX_EDGES; Edge++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Edge == 0) ? "\nLo\t" : "\nHi\t");
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
            continue;
          }

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG(
               Debug,
               MSG_LEVEL_NOTE,
               "%d\t",
               MarginByte[ResultType][Rank][Controller][Channel][Byte][Edge]
               );
          }
        } // Channel
      } // Controller
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCenter\t");
#endif // MRC_DEBUG_PRINT

    // Store Results
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels)) {

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            center[Controller][Channel][Rank][Byte] = (MarginByte[ResultType][Rank][Controller][Channel][Byte][1] -
                                           MarginByte[ResultType][Rank][Controller][Channel][Byte][0]);
            if (tim == 0) {
              CenterSumByte[Controller][Channel][Byte] = 0;
            }

            // Calculate weight for this point
            CenterSumByte[Controller][Channel][Byte] += EHWeights[tim] * center[Controller][Channel][Rank][Byte];

            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", center[Controller][Channel][Rank][Byte] / 20);

            // Record edges for use in per bit margining
            EyeShape[tim][Controller][Channel][Byte][0] = MarginByte[ResultType][Rank][Controller][Channel][Byte][0];
            EyeShape[tim][Controller][Channel][Byte][1] = MarginByte[ResultType][Rank][Controller][Channel][Byte][1];
          } // Byte
        } // MC_CH_MASK_CHECK
      } // Channel
    } // Controller


    // Loop once at nominal Vref point
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWtdCntr\t");
  // ####################################################
  // ###########   Center Results per Byte   ############
  // ####################################################
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }

      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

      // Calculate CenterPoint.  Round to Nearest Int
      // @todo: might need to ajust because now step is 7.8mV
      CenterRank = 0;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        SumEHSign = (CenterSumByte[Controller][Channel][Byte] < 0) ? (-1) : 1;

        CenterSumByte[Controller][Channel][Byte] = (CenterSumByte[Controller][Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
        CenterRank += CenterSumByte[Controller][Channel][Byte];
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", CenterSumByte[Controller][Channel][Byte]);
        // Update the Eye Edges
        for (tim = 0; tim < sizeof(TimePoints); tim++) {
          EyeShape[tim][Controller][Channel][Byte][0] = EyeShape[tim][Controller][Channel][Byte][0] + (10 * CenterSumByte[Controller][Channel][Byte]);
          EyeShape[tim][Controller][Channel][Byte][1] = EyeShape[tim][Controller][Channel][Byte][1] - (10 * CenterSumByte[Controller][Channel][Byte]);

          // Loop once at nominal Vref point
          if (En2D == 0) {
            tim = sizeof(TimePoints);
          }
        }

        // Update MrcData for future tests (MarginResult points back to MrcData)
        // EyeShape for Vref 0 is assumed to have the best shape for future tests.
        MarginByte[ResultType][Rank][Controller][Channel][Byte][0] = EyeShape[0][Controller][Channel][Byte][0];
        MarginByte[ResultType][Rank][Controller][Channel][Byte][1] = EyeShape[0][Controller][Channel][Byte][1];
      } // For Byte
      CenterRank /= Outputs->SdramCount;
      // Set WrV Offset average across Byte (Non-PDA). Do not update cache
      ChangeMargin(MrcData, WrV, CenterRank, 0, 0,  Controller, Channel, RankMask, 0, 0, 0, 1);
      // Set WrV Offset per byte using PDA. Update cache
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        ChangeMargin(MrcData, WrV, CenterSumByte[Controller][Channel][Byte], 0, 0, Controller, Channel, RankMask, 1 << Byte, 0, 1, 1);
      }
      // Update WrV Non-PDA cached value
      UpdatePdaCenter(MrcData, Controller, Channel, RankMask);
    } // Channel
  } // Controller


#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWrVref\t");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!(MC_CH_MASK_CHECK(McChBitMask, Controller, Channel, MaxChannels))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER(Rank)].Rank[Rank % 2];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", MrcVrefDqToOffsetDdr4(RankOut->Ddr4PdaMr6[Byte] & 0x7F));
      }
    } // Channel
  } // Controller

  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nPerByte Margins after per BYTE Centering\nLo-Hi   ");
  //
#endif // MRC_DEBUG_PRINT

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  //
  // Clean up after test
  //
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);
  return Status;
}

/**
  Perform Write Voltage Centering in 2D.
  Note: This function currently only supports param = WrV

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it succeded return mrcSuccess
**/
MrcStatus
MrcWriteVoltageCentering2D_DDR4 (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     LoopCount;
  UINT8     En2D;
  UINT8     RankMask;
  UINT8     Rank;

  Outputs   = &MrcData->Outputs;
  Status    = mrcSuccess;

    LoopCount   = 15;
    En2D        = 1;

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      RankMask = (0x1 << Rank) & Outputs->ValidRankMask;
      if (RankMask) {
        Status = WriteVoltageCentering2D_DDR4 (
          MrcData,
          Outputs->MarginResult,
          Outputs->ValidChBitMask,
          Rank,
          LoopCount,
          En2D
          );
      }
    }
  return Status;
}

/**
  Perform Write Timing Linear Centering in different Write Vref points.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Prints        - Debug prints enable/disable

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
EarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData,
  IN     BOOLEAN              Prints
  )
{
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT8             LoopCount;
  UINT8             Dimm;
  UINT8             RankMask;
  INT8              Points2DMin;
  INT8              Points2DMax;
  UINT8             StepSize;

  Outputs   = &MrcData->Outputs;
  Status    =  mrcSuccess;

  Points2DMin     = -12;
  Points2DMax     = 12;
  StepSize = (MrcData->Inputs.MemoryProfile != STD_PROFILE) ? 1 : 3;

    LoopCount   = 10;

  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    RankMask = DIMM_TO_RANK_MASK (Dimm) & Outputs->ValidRankMask;
    if (RankMask) {
      Status = EarlyLinearCentering2D (
                MrcData,
                Outputs->ValidChBitMask,
                RankMask,
                WrT,
                WrV,
                Points2DMin,
                Points2DMax,
                StepSize,
                LoopCount,
                0, // test type - normal reads
                Prints
                );
    }
  }
  return Status;
}

/**
  Perform Write Timing Linear Centering in different Write Vref points.

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
MrcEarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  MrcStatus Status;
  INT64     RdRdsg;
  INT64     RdRddg;

  MrcRelaxReadToReadSameRank (MrcData, TRUE, &RdRdsg, &RdRddg);

  Status = EarlyWriteTimingCentering2D (MrcData, TRUE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE, &RdRdsg, &RdRddg);

  return Status;
}

/**
  Perform LP4 Re-Training.

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus        - if it success return mrcSuccess
**/
MrcStatus
MrcWriteDqDqsReTraining (
  IN     MrcParameters *const MrcData
  )
{
  MrcStatus                                       Status;
  MrcOutput                                       *Outputs;
  MrcDebug                                        *Debug;
  UINT16                                          *MrPtr;
  UINT32                                          Offset;
  UINT32                                          Controller;
  UINT8                                           Channel;
  UINT8                                           IpChannel;
  UINT8                                           Rank;
  UINT8                                           MaxDevice;
  UINT8                                           Device;
  UINT16                                          ROCount;
  UINT16                                          ROPITicks;
  UINT8                                           MrrOscLsbResult[4];
  UINT8                                           MrrOscMsbResult[4];
  UINT32                                          MrAddr;
  UINT32                                          Lp4ReTrainDuration;
  UINT8                                           DqioDuration;
  UINT16                                          RORunTime;
  BOOLEAN                                         Lp4ReTrainingStatus;
  BOOLEAN                                         Lpddr;
  BOOLEAN                                         Lpddr4;
  DATA0CH0_CR_DDRCRWRRETRAINRANK0_STRUCT          WrRetrain;
  DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT  WrRetrainStatus;
  MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT     Lp4DqsOsclParams;
  DDRSCRAM_CR_DDRMISCCONTROL2_STRUCT              MiscControl2;
  UINT8                                           mrIndex;


  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  Status              = mrcSuccess;
  Lpddr               = Outputs->Lpddr;
  Lpddr4              = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  DqioDuration = 0;
  ROPITicks = 0;
  WrRetrain.Data = 0;
  Offset = 0;
  MaxDevice = (Outputs->LpByteMode) ? 2 : 1;

  if (Outputs->Frequency >= f5333) {
    DqioDuration = 64;
  } else if (Outputs->Frequency >= f3467) {
    DqioDuration = 63;
  } else if (Outputs->Frequency >= f3200) {
    DqioDuration = 60;
  } else if (Outputs->Frequency >= f2933) {
    DqioDuration = 55;
  } else if (Outputs->Frequency >= f2667) {
    DqioDuration = 50;
  } else if (Outputs->Frequency >= f2400) {
    DqioDuration = 45;
  } else if (Outputs->Frequency >= f2133) {
    DqioDuration = 40;
  } else if (Outputs->Frequency >= f1867) {
    DqioDuration = 35;
  } else if (Outputs->Frequency >= f1600) {
    DqioDuration = 30;
  } else if (Outputs->Frequency >= f1333) {
    DqioDuration = 25;
  } else if (Outputs->Frequency >= f1067) {
    DqioDuration = 20;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Frequency unsupported\n", gErrString);
    Status = mrcUnsupportedTechnology;
  }

  if (Status == mrcSuccess) {
    if (DqioDuration == 64) {
      RORunTime = 2048;
    } else {
      RORunTime = DqioDuration*16;
    }
    // TGL is in steps of UI/128
    Lp4ReTrainDuration = RORunTime*128;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqioDuration = %d\nRORunTime = %d\nLp4ReTrainDuration = %d\n", DqioDuration, RORunTime, Lp4ReTrainDuration);
    for (Controller = 0; (Controller < MAX_CONTROLLER) && (Status == mrcSuccess); Controller++) {
      for (Channel = 0; (Channel < Outputs->MaxChannels) && (Status == mrcSuccess); Channel++) {
        if (!(MrcChannelExist (MrcData, Controller, Channel))) {
          continue;
        }
        for (Rank = 0; (Rank < MAX_RANK_IN_CHANNEL) && (Status == mrcSuccess); Rank++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          MrPtr = Outputs->Controller[Controller].Channel[Channel].Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR;
          if (Lpddr4) {
            mrIndex = mrIndexMR23;
            MrAddr = 23;
          } else { // Lpddr5
            mrIndex = mrIndexMR37;
            MrAddr = 37;
          }
          Status = MrcLpddr4SetMr23 (
                       MrcData,
                       DqioDuration,
                       &MrPtr[mrIndex]
                       );
          // Set Interval timer run time setting
          Status = MrcIssueMrw (
                      MrcData,
                      Controller,
                      Channel,
                      Rank,
                      MrAddr,
                      (UINT8) MrPtr[mrIndex],
                      TRUE    // DebugPrint
                      );
        } // for Rank
      } // for Channel
    } // for Controller
    for (Controller = 0; (Controller < MAX_CONTROLLER) && (Status == mrcSuccess); Controller++) {
      for (Channel = 0; (Channel < Outputs->MaxChannels) && (Status == mrcSuccess); Channel++) {
        if (!(MrcChannelExist (MrcData, Controller, Channel))) {
          continue;
        }
        for (Rank = 0; (Rank < MAX_RANK_IN_CHANNEL) && (Status == mrcSuccess); Rank++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          // Issue MPC MRC_LP4_MPC_START_DQS_OSC/MRC_LP5_MPC_START_WCK2DQI_OSC
          Status = MrcIssueMpc (
                      MrcData,
                      Controller,
                      Channel,
                      Rank,
                      (Lpddr4 ? MRC_LP4_MPC_START_DQS_OSC : MRC_LP5_MPC_START_WCK2DQI_OSC),
                      0,
                      TRUE
                      );

          MrcWait (MrcData, MRC_TIMER_1US);
        } // for Rank
        for (Device = 0; Device < MaxDevice; Device++) {
          Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, DATA0CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, Controller, DATA2CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, Channel);
          Offset += ((DATA1CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG - DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG) * Device);
          WrRetrainStatus.Data = MrcReadCR (MrcData, Offset);
          WrRetrainStatus.Bits.Duration = DqioDuration;
          MrcWriteCR (MrcData, Offset, WrRetrainStatus.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrRetrainControl.Data: 0x%x\n", WrRetrainStatus.Data);
        } // for Device
      } // for Channel
    } // for Controller
    MrcWait (MrcData, (250 * MRC_TIMER_1NS));
    if (Status == mrcSuccess) {
      Lp4ReTrainingStatus = TRUE;
      for (Controller = 0; (Controller < MAX_CONTROLLER) && (Lp4ReTrainingStatus == TRUE); Controller++) {
        for (Channel = 0; (Channel < Outputs->MaxChannels) && (Lp4ReTrainingStatus == TRUE); Channel++) {
          if (!(MrcChannelExist (MrcData, Controller, Channel))) {
            continue;
          }
          for (Device = 0; Device < MaxDevice; Device++) {
            for (Rank = 0; Rank < (MAX_RANK_IN_CHANNEL); Rank++) {
              if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
                continue;
              }
              Offset = DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG +
                     ((DATA0CH1_CR_DDRCRWRRETRAINRANK3_REG - DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG) * Controller) +
                     ((DATA2CH0_CR_DDRCRWRRETRAINRANK3_REG - DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG) * Channel) +
                     ((DATA0CH0_CR_DDRCRWRRETRAINRANK0_REG - DATA0CH0_CR_DDRCRWRRETRAINRANK1_REG) * (3 - Rank));
              Offset += ((DATA1CH0_CR_DDRCRWRRETRAINRANK0_REG - DATA0CH0_CR_DDRCRWRRETRAINRANK0_REG) * Device);
              WrRetrain.Data = 0;
              // LPDDR4:MR18 LPDDR5:MR35
              MrAddr = (Lpddr4) ? 18 : 35;
              MrcIssueMrr (MrcData, Controller, Channel, Rank, MrAddr, MrrOscLsbResult);
              // LPDDR4:MR19 LPDDR5:MR36
              MrAddr = (Lpddr4) ? 19 : 36;
              MrcIssueMrr (MrcData, Controller, Channel, Rank, MrAddr, MrrOscMsbResult);
              ROCount = (MrrOscMsbResult[Device] << 8) | MrrOscLsbResult[Device];
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Mc%d Ch%d R%d: MR%d Device%d= 0x%02X\nMR%d Device%d = 0x%02X\nROCount = %d\n",
                Controller,
                Channel,
                Rank,
                (Lpddr4) ? 18 : 35,
                Device,
                MrrOscLsbResult[Device],
                (Lpddr4) ? 19 : 36,
                Device,
                MrrOscMsbResult[Device],
                ROCount
                );
              // Max value for ROCount is 4095
              if (ROCount <= 4095) {
                ROPITicks = 0;
                if (ROCount > 0) {
                  ROPITicks = (UINT16) (Lp4ReTrainDuration / ROCount);
                }

                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ROPITicks = %d\n", ROPITicks);
                if (ROPITicks <= DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MAX) {
                    // Set the corresponding ROCount bit field
                  WrRetrain.Bits.InitPiCode = ROPITicks;
                } else {
                  MRC_DEBUG_MSG (
                    Debug,
                    MSG_LEVEL_ERROR,
                    "ROPITicks %d is greater than %d\n",
                    ROPITicks,
                    DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MAX
                    );
                  Lp4ReTrainingStatus = FALSE;
                  break;
                } // (ROPITicks <= DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MAX)
              } else {
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_ERROR,
                  "ROCount %d is greater than %d\n",
                  ROCount,
                  4095
                  );
                Lp4ReTrainingStatus = FALSE;
                break;
              } // (ROCount > 4095)

              if (Lp4ReTrainingStatus == TRUE) {
                // Write the new RO values back to their corresponding offsets.
                MrcWriteCR (MrcData, Offset, WrRetrain.Data);
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  "Mc%d Ch%d R%d Dev%d: RoCountTrain=%08X\n",
                  Controller,
                  Channel,
                  Rank,
                  Device,
                  ROPITicks
                  );
              } else {
                Status = mrcFail;
                break;
              } // (Lp4ReTrainingStatus == TRUE)
            } // for Rank
          } // for Device
        } // for Channel
      } // for Controller

      // After all RO values are written, set up the OSC Params per channel
      if (Lp4ReTrainingStatus == TRUE) {
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
            if (!(MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
              continue;
            }
            IpChannel = LP_IP_CH (Lpddr, Channel);
            Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, MC1_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, Controller, MC0_CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, IpChannel);
            Lp4DqsOsclParams.Data = MrcReadCR (MrcData, Offset);
            Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD          = ZQCS_PERIOD_LPDDR * 128;
            Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL         = 0;
            Lp4DqsOsclParams.Bits.disable_wr_on_pkgc_exit = 1;
            Lp4DqsOsclParams.Bits.disable_wr_on_SR_exit   = 1;
            MrcWriteCR (MrcData, Offset, Lp4DqsOsclParams.Data);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "Mc%d Ch%d Lp4DqsOsclParams=%08X\n",
              Controller,
              IpChannel,
              Lp4DqsOsclParams.Data
              );
          } // for Channel
          // Write every Byte in the phy to reset its Status.
          for (Device = 0; Device < MAX_SDRAM_IN_DIMM - 1; Device++) {
            Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, DATA0CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, Controller, DATA1CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, Device);
            WrRetrainStatus.Data = MrcReadCR (MrcData, Offset);
            WrRetrainStatus.Bits.ResetStatus = 1;
            MrcWriteCR (MrcData, Offset, WrRetrainStatus.Data);
          }
        } // for Controller
        Offset = DDRSCRAM_CR_DDRMISCCONTROL2_REG;
        MiscControl2.Data = MrcReadCR (MrcData, Offset);
        MiscControl2.Bits.lpdeltadqstrainmode = 1;
        MrcWriteCR (MrcData, Offset, MiscControl2.Data);
      } else {
        Status = mrcFail;
      } // (Lp4ReTrainingStatus == TRUE)
    } // (Status == mrcSuccess)
  } // (Status == mrcSuccess)
  return Status;
}
