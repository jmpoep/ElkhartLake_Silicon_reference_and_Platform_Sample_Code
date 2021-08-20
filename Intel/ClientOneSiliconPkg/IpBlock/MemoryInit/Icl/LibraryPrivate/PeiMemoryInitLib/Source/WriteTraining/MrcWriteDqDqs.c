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
#include "MrcDdrCommon.h"
#include "MrcDdr4.h"
#include "MrcLpddr4.h"
#include "MrcMaintenance.h"
#include "MrcCpgcOffsets.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcGears.h"

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
  MrcOutput       *Outputs;
  MRC_MarginTypes MarginParam;
  MrcStatus       Status;
  UINT8           ResetPerbit;
  UINT8           LoopCount;

  Outputs = &MrcData->Outputs;
  ResetPerbit = 1;
  LoopCount   = 10;

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    MarginParam = WrTLp4;
  } else {
    MarginParam = WrT;
  }

  MrcRelaxReadToReadSameRank (MrcData, TRUE);

  Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, MarginParam, ResetPerbit, LoopCount, TRUE, FALSE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE);
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
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     LoopCount;

  Outputs = &MrcData->Outputs;

  LoopCount   = 10;

  MrcRelaxReadToReadSameRank (MrcData, TRUE);

  Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, LoopCount, TRUE, FALSE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE);

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
  INT64           GetSetVal;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  LoopCount = 15;
  EnRxDutyCycle = 0;

  if (!Inputs->WrTPbdDis) {
    EnPerBit    = 1;
    ResetPerBit = 1;
    En2D        = 0;

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
              Outputs->ValidChBitMask,
              WrT,
              EnPerBit,
              EnRxDutyCycle,
              ResetPerBit,
              LoopCount,
              En2D,
              MRC_PRINTS_ON
              );

    if (!Outputs->Gear2) {
      MrcPerBitDeskew (MrcData, Outputs->MarginResult, WrT);
    }
  }

  if (mrcSuccess == Status) {
    EnPerBit    = 0;
    ResetPerBit = 0;
    En2D        = 1;
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
              Outputs->ValidChBitMask,
              WrT,
              EnPerBit,
              EnRxDutyCycle,
              ResetPerBit,
              LoopCount,
              En2D,
              MRC_PRINTS_ON
              );
  }

  if (Inputs->DqBitDccRerunInWrTPbd && (Status == mrcSuccess) && Outputs->Gear2) {
    if (Inputs->IclA0) {
      GetSetVal = 0;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);
    }

    Status = MrcDccDqBitInitSweep (MrcData);

    if (Inputs->IclA0) {
      GetSetVal = 1;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);
      MrcResetSequence (MrcData);
    }
  }

  return Status;
}

const MarginCheckPoint MarginCheckL1Table[MAX_MARGIN_CHECK] = {
// Timing type, timing margin, Voltage type, Voltage margin
  { RdT,              10,            RdV,         24 },
  { WrT,              10,            WrV,         28 },
  { CmdT,             10,            CmdV,        17 }
};

/**
  Check Margin Limits by utilizing box test.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
 **/
MrcStatus
MrcMarginLimitCheck (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  MrcStatus           Pass;
  INT64               GetSetDis;
  INT64               CmdTriStateSave[MAX_CHANNEL];
  UINT8               LoopCount;
  UINT8               RdRdTLoopCount;
  UINT8               Channel;
  UINT8               chBitMask;
  UINT8               Rank;
  UINT8               RankMask;
  UINT8               Param;
  UINT8               MarginLevel;
  UINT8               MarginLevelMask;
  UINT8               TimingSign;
  UINT8               VoltageSign;
  UINT8               SignalIdx;
  MarginCheckPoint    MarginCheckL2Table[MAX_MARGIN_CHECK];
  MarginCheckPoint    MarginPoint;
  MarginCheckPoint    MarginPointTemp;
  BOOLEAN             MarginCheckBoth;

  MarginCheckMode     MarginCheckResult;
  UINT8               FailResults[MAX_MARGIN_CHECK][MAX_RANK_IN_CHANNEL][MAX_EDGES][MAX_EDGES];

  #ifdef MRC_DEBUG_PRINT
  // Margin check strings are used for debug printing
  // Note: The order needs to same as MarginCheckMode Enum
  static const char *MarginCheckStr[] = {
    "Pass",
    "L1",
    "L2",
    "L1/L2"
  };
  #endif

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  GetSetDis  = 0;

  MrcCall->MrcSetMem ((UINT8 *) FailResults, sizeof (FailResults), 0);
  MrcCall->MrcSetMem ((UINT8 *) CmdTriStateSave, sizeof (CmdTriStateSave), 0);

  MarginCheckBoth = (Inputs->MarginLimitCheck == MARGIN_CHECK_BOTH);

  if (Inputs->BootMode == bmFast) {
    // Go to CPCG mode
    MrcSetNormalMode (MrcData, FALSE);
  }

    // Enable command tri state during Margin Check
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, ReadFromCache, &CmdTriStateSave[Channel]);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &GetSetDis);
    }
  }

  // Setup Loop Count
  LoopCount = (Inputs->RMTLoopCount != 0) ? Inputs->RMTLoopCount : 17;
  //For RdRdT, it has 2 TA tests. Cut the loop count in half like power training did.
  RdRdTLoopCount = LoopCount - 1;

  // Setup L2 table
  for(SignalIdx = 0; SignalIdx < MAX_MARGIN_CHECK; SignalIdx++) {
    MarginCheckL2Table[SignalIdx].TimingType = MarginCheckL1Table[SignalIdx].TimingType;
    MarginCheckL2Table[SignalIdx].TimingMargin = (INT8) ((MarginCheckL1Table[SignalIdx].TimingMargin * Inputs->MarginLimitL2)/100);
    MarginCheckL2Table[SignalIdx].VoltageType = MarginCheckL1Table[SignalIdx].VoltageType;
    MarginCheckL2Table[SignalIdx].VoltageMargin = (INT8) ((MarginCheckL1Table[SignalIdx].VoltageMargin * Inputs->MarginLimitL2)/100);
  }

  for(SignalIdx = 0; SignalIdx < MAX_MARGIN_CHECK; SignalIdx++) {
    Param = MarginCheckL1Table[SignalIdx].TimingType;

    // Note: The following statement depends on the order of MarginCheckL1Table.
    if (Param == RdT) {
      // Test Margin for RdT/RdV, WrT/WrV
      // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
      SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, RdRdTLoopCount, NSOE, 0, 0, 8);

      // For Write/Read timing margining, we want to run traffic with Rd->Rd turnaround times of 4 and 5.
      Outputs->DQPat = RdRdTA;
    } else if (Param == CmdT) {
      SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
    }

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      // Select rank for REUT test
      RankMask  = 1 << Rank;

      chBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      } // Channel

      // Continue with next rank if this rank is not present on any channel
      if (!(chBitMask)) {
        continue;
      }

      for (MarginLevel = MARGIN_CHECK_L2; MarginLevel > MARGIN_CHECK_DISABLE; MarginLevel--) {

        // check wether to run margin level
        MarginLevelMask = 1 << (MarginLevel-1);
        if ((MarginLevelMask & Inputs->MarginLimitCheck) == 0) {
          continue;
        }

        if (MarginLevel  == MARGIN_CHECK_L2) {
          MarginPointTemp = MarginCheckL2Table[SignalIdx];
        }
        else {
          MarginPointTemp = MarginCheckL1Table[SignalIdx];
        }

        MarginPoint = MarginPointTemp;
        MrcCall->MrcCopyMem ((UINT8 *) &MarginPoint, (UINT8 *) &MarginPointTemp, sizeof (MarginPoint));

        for (TimingSign = 0; TimingSign < 2; TimingSign++) {
          MarginPoint.TimingMargin =  MarginPointTemp.TimingMargin * ((TimingSign * 2) - 1);

          for(VoltageSign = 0; VoltageSign < 2; VoltageSign++) {

            // Skip testing point on L1 check if L2 check passed
            if ((MarginLevel  == MARGIN_CHECK_L1)
                   && (FailResults[SignalIdx][Rank][TimingSign][VoltageSign] != MARGIN_CHECK_L2 && MarginCheckBoth)) {
              continue;
            }

            MarginPoint.VoltageMargin =  MarginPointTemp.VoltageMargin * ((VoltageSign * 2) - 1);

            // test margin point
            if (Param == CmdT) {
              Pass = MrcCmdPointTest (MrcData, chBitMask, Outputs->ValidSubChMask, RankMask, &MarginPoint);
            } else {
              Pass = MrcDataPointTest (MrcData, chBitMask, RankMask, &MarginPoint);
            }

            if (Pass != mrcSuccess) {
              FailResults[SignalIdx][Rank][TimingSign][VoltageSign] = ((MarginLevel  == MARGIN_CHECK_L1) && MarginCheckBoth) ? MARGIN_CHECK_BOTH : MarginLevel;
            }
          } // VoltageSign
        } // TimingSign
      } // MarginLevel
    }  // Rank
  }  // Param

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Margin Check level\nParams: \tRdT/RdV\t\t\t\t WrT/WrV\t\t\t CmdT/CmdV\n"
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\t\t -T+V\t-T-V\t+T+V\t+T-V\t -T+V\t-T-V\t+T+V\t+T-V\t -T+V\t-T-V\t+T+V\t+T-V"
    );

  MarginCheckResult = 0;

  // Find the Worst level result
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {

    if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
      // Skip if this rank is not present on any of the channels
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nR%d\t\t", Rank);

    for (SignalIdx = 0; SignalIdx < MAX_MARGIN_CHECK; SignalIdx++) {

      for (TimingSign = 0; TimingSign < 2; TimingSign++) {
        for (VoltageSign = 0; VoltageSign < 2; VoltageSign++) {
          if(MarginCheckResult < FailResults[SignalIdx][Rank][TimingSign][VoltageSign]) {
            MarginCheckResult = FailResults[SignalIdx][Rank][TimingSign][VoltageSign];
          }
        } // VoltageSign
      }  // TimingSign
      MRC_DEBUG_MSG (Debug,
                     MSG_LEVEL_NOTE,
                     "%s\t%s\t%s\t%s\t",
                     MarginCheckStr[FailResults[SignalIdx][Rank][0][1]],
                     MarginCheckStr[FailResults[SignalIdx][Rank][0][0]],
                     MarginCheckStr[FailResults[SignalIdx][Rank][1][1]],
                     MarginCheckStr[FailResults[SignalIdx][Rank][1][0]]);
    }  // Param
  }  // Rank

  // Determine if a cold boot required
  Status = (MarginCheckResult == Inputs->MarginLimitCheck) ? mrcColdBootRequired : mrcSuccess;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nmargin check result:%s \n", MarginCheckStr[MarginCheckResult]);

  if (Status == mrcColdBootRequired) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Margin Check Failed - cold boot required\n");
  }

  // Restore command tri state setting
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateSave[Channel]);
    }
  }

  if (Inputs->BootMode == bmFast) {
    // Go to normal mode
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
  INT64               CmdTriStateSave[MAX_CHANNEL];
  UINT32              BERStats[4];
  UINT8               Rank;
  UINT8               Param;
  UINT8               RankMask;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               SubCh;
  UINT8               SubChMax;
  UINT8               byte;
  UINT8               ByteStart;
  UINT8               ByteEnd;
  UINT8               bit;
  UINT8               LcLoop;
  UINT8               BMap[MAX_SDRAM_IN_DIMM];
  UINT8               chBitMask;
  UINT8               MaxMargin;
#if DATA_EYE_MARGIN_SUPPORT
  INT8                MaxT;
#endif
  UINT8               LoopCount;

  INT8                VrefOffsets[2];
  BOOLEAN             Lpddr4;
  MrcIntCmdTimingOut  *IntCmdTiming;
  UINT32              Edge;
  UINT16              RmtMargins[MAX_RESULT_TYPE][MAX_CHANNEL][MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_EDGES];
  UINT8               RankMax;
  UINT8               CmdPiCodeIdx;
  BOOLEAN             SkipVref;
  BOOLEAN             SkipPrint;
  BOOLEAN             EnhancedChannelMode;
  MrcPower            PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  CH0_SC0_CR_CADB_CFG_STRUCT          CadbConfig;
  MrcIntControllerOut *IntControllerOut;
  MrcIntOutput        *IntOutputs;
  UINT32              GearDivider;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  IntOutputs = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) VrefOffsets, sizeof (VrefOffsets), 0);
  MrcCall->MrcSetMem ((UINT8 *) PwrChRank, sizeof (PwrChRank), 0);
  MrcCall->MrcSetMem ((UINT8 *) CmdTriStateSave, sizeof (CmdTriStateSave), 0);
  GetSetDis = 0;

  // Check memory used
  Lpddr4 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  EnhancedChannelMode = Outputs->EnhancedChannelMode;
  SubChMax = (EnhancedChannelMode) ? MAX_SUB_CHANNEL : 1;
  GearDivider = (Outputs->Gear2) ? 2 : 1;

  for (LcLoop = 0; LcLoop < (sizeof (BMap) / sizeof (BMap[0])); LcLoop++) {
    BMap[LcLoop] = LcLoop;
  }

  if (Inputs->BootMode == bmFast) {
    // Go to CPCG mode
    MrcSetNormalMode (MrcData, FALSE);
  }


#if DATA_EYE_MARGIN_SUPPORT
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    MaxMargin = GetMaxPossibleVrefOffset (MrcData, WrV);
    MaxT      = GetMaxPossibleTimingOffset (MrcData, WrT);
    EyeMargin (MrcData, 1 << Rank, WrT, WrV, 0, 0, -MaxT, MaxT, MaxMargin, 15, 1);

    MaxMargin = GetMaxPossibleVrefOffset (MrcData, RdV);
    MaxT      = GetMaxPossibleTimingOffset (MrcData, RdT);
    EyeMargin (MrcData, 1 << Rank, RdT, RdV, 0, 0, -MaxT, MaxT, MaxMargin, 15, 1);
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
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, ReadFromCache, &CmdTriStateSave[Channel]);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &GetSetDis);
    }
  }

  LoopCount = (Inputs->RMTLoopCount != 0) ? Inputs->RMTLoopCount : 17;


  // Calculate all the Ranks/Channel power.
  CalcSysPower(MrcData, PwrChRank);

  // Data Margins
  // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 0, 0, 8);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select rank for REUT test
    RankMask  = 1 << Rank;
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }
    // Continue with next rank if this rank is not present on any channel
    if (!(chBitMask)) {
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
        MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
      } else {
        MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
      }
      Status = MrcGetBERMarginByte (
              MrcData,
              Outputs->MarginResult,
              chBitMask,
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
      GetMarginCh (MrcData, Outputs->MarginResult, Param, RankMask, Rank, EnhancedChannelMode);
    }
  } // Rank

  // Command Margins
  SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
  if (EnhancedChannelMode) {
    RankMax = 2;
  } else {
    RankMax = 4;
  }
  for (SubCh = 0; SubCh < SubChMax; SubCh++) {
    if ((Outputs->ValidSubChMask & (1 << SubCh)) == 0) {
      continue;
    }
    for (Rank = 0; Rank < RankMax; Rank++) {
      // Select rank for REUT test
      RankMask  = 1 << Rank;
      chBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      }
      // Continue with next rank if this rank is not present on any channel
      if (!(chBitMask)) {
        continue;
      }

      // Run test for Cmd Timing
      SkipVref  = TRUE;
      SkipPrint = TRUE;
      if (Lpddr4) {
        CmdLinearFindEdgesLpddr (MrcData, MrcIterationCmd, chBitMask, RankMask, 0x1F, !SkipPrint); // Shift all CMD/CTL fubs in LP4, instead of CLK
      } else {
        CmdLinearFindEdges (MrcData, MrcIterationClock, chBitMask, RankMask, 3, -64, 64, 6, 1, VrefOffsets, SkipPrint, SkipVref);
      }

      // Restore centered value
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Lpddr4) {
            IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
            ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 0), IntCmdTiming->CtlPiCode[0], 0);
            ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 1), IntCmdTiming->CtlPiCode[1], 0);
            for (CmdPiCodeIdx = 0; CmdPiCodeIdx < (MAX_COMMAND_GROUPS - 1); CmdPiCodeIdx++) {
              ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, (1 << CmdPiCodeIdx), IntCmdTiming->CmdPiCode[CmdPiCodeIdx], 0);
            }
          } else {
            ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, 0x3, 0, 1);
          }
        }
      }
      Status = MrcResetSequence (MrcData);

      // Run test for Cmd Voltage
      // For LPDDR4 MrcGetBERMarginCh() runs on both subch
      if (SubCh == 0) {
        MaxMargin = GetMaxPossibleVrefOffset (MrcData, CmdV);
        Status = MrcGetBERMarginCh (
                  MrcData,
                  Outputs->MarginResult,
                  chBitMask,
                  (Lpddr4) ? RankMask : 0xFF,
                  RankMask,
                  CmdV,
                  mode,
                  0,
                  MaxMargin,
                  0,
                  BERStats
                  );
        Status = MrcResetSequence (MrcData);
      }
      if (EnhancedChannelMode) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            RmtMargins[LastCmdT][Channel][SubCh][Rank][Edge] = (UINT16) Outputs->MarginResult[LastCmdT][Rank][Channel][0][Edge];
            RmtMargins[LastCmdV][Channel][SubCh][Rank][Edge] = (UINT16) Outputs->MarginResult[LastCmdV][Rank][Channel][0][Edge];
          } // Edge
        } // Channel
      } // if (EnhancedChannelMode)
    } // Rank
  } // SubCh

  // Place CMD margins in expected spots
  if (EnhancedChannelMode) {
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
            if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
              continue;
            }
            ByteStart = ChannelOut->ByteStart[SubCh];
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              Outputs->MarginResult[LastCmdT][Rank][Channel][ByteStart][Edge] = RmtMargins[LastCmdT][Channel][SubCh][Rank][Edge];
              Outputs->MarginResult[LastCmdV][Rank][Channel][ByteStart][Edge] = RmtMargins[LastCmdV][Channel][SubCh][Rank][Edge];
            }
          }
        }
      }
    }
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
              continue;
            }
            ByteStart = EnhancedChannelMode ? ChannelOut->ByteStart[SubCh] : 0;
            ByteEnd = EnhancedChannelMode ? ChannelOut->ByteEnd[SubCh] : Outputs->SdramCount - 1;
            CommandOut        = &ChannelOut->Command[Rank][SubCh];
            CommandOut->Left  = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Channel][ByteStart][0] / 10);
            CommandOut->Right = (UINT8) (Outputs->MarginResult[LastCmdT][Rank][Channel][ByteStart][1] / 10);
            CommandOut->Low   = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Channel][ByteStart][0] / 10);
            CommandOut->High  = (UINT8) (Outputs->MarginResult[LastCmdV][Rank][Channel][ByteStart][1] / 10);
            RecvEnOut         = &ChannelOut->ReceiveEnable[Rank][SubCh];
            RecvEnOut->Left   = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Channel][ByteStart][0] / 10);
            RecvEnOut->Right  = (UINT8) (Outputs->MarginResult[LastRcvEna][Rank][Channel][ByteStart][1] / 10);
            WrLevelOut        = &ChannelOut->WriteLevel[Rank][SubCh];
            WrLevelOut->Left  = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Channel][ByteStart][0] / 10);
            WrLevelOut->Right = (UINT8) (Outputs->MarginResult[LastWrLevel][Rank][Channel][ByteStart][1] / 10);
            for (byte = ByteStart; byte <= ByteEnd; byte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                ChannelOut->RxDqPb[Rank][byte][bit].Left      = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Channel][ByteStart][0] / (10 * GearDivider));
                ChannelOut->RxDqPb[Rank][byte][bit].Right     = (UINT8) (Outputs->MarginResult[LastRxT][Rank][Channel][ByteStart][1] / (10 * GearDivider));
                ChannelOut->TxDqPb[Rank][byte][bit].Left      = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Channel][ByteStart][0] / 10);
                ChannelOut->TxDqPb[Rank][byte][bit].Right     = (UINT8) (Outputs->MarginResult[LastTxT][Rank][Channel][ByteStart][1] / 10);
                ChannelOut->RxDqVrefPb[Rank][byte][bit].Low   = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Channel][ByteStart][0] / 10);
                ChannelOut->RxDqVrefPb[Rank][byte][bit].High  = (UINT8) (Outputs->MarginResult[LastRxV][Rank][Channel][ByteStart][1] / 10);
                ChannelOut->TxDqVrefPb[Rank][byte][bit].Low   = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Channel][ByteStart][0] / 10);
                ChannelOut->TxDqVrefPb[Rank][byte][bit].High  = (UINT8) (Outputs->MarginResult[LastTxV][Rank][Channel][ByteStart][1] / 10);
              } // Bit
            } // Byte
          }
        } // MrcRankInChannelExist
      } // Channel
    } // Controller
  } // for Rank

  // Disable CADB Deselects after RMT
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  // Restore command tri state setting
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateSave[Channel]);
    }
  }

#ifdef MRC_DEBUG_PRINT
  // Print test results
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Testing: DQ LC = %d, Cmd LC = %d\n\n", LoopCount, LoopCount);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Margin\nParams: RcvEna\tWrLevel\tRdT\tWrT\tRdV\tWrV\tCmdT\tCmdV\tRdPower\tWrPower\tTotPwr\n"
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\tLft Rgt Lft Rgt Lft Rgt Lft Rgt Low Hi  Low Hi  Lft Rgt Low Hi\t[mW]\t[mW]\t[mW]\n"
    );
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (SubCh = 0; SubCh < SubChMax; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        ByteStart = ChannelOut->ByteStart[SubCh];
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dR%d:\t", (EnhancedChannelMode) ? ((Channel * 2) + SubCh) : Channel, Rank);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d.%d\t%2d.%d\t%2d.%d\n",
              Outputs->MarginResult[LastRcvEna][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastRcvEna][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastWrLevel][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastWrLevel][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastRxT][Rank][Channel][ByteStart][0] / (10 * GearDivider),
              Outputs->MarginResult[LastRxT][Rank][Channel][ByteStart][1] / (10 * GearDivider),
              Outputs->MarginResult[LastTxT][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastTxT][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastRxV][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastRxV][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastTxV][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastTxV][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastCmdT][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastCmdT][Rank][Channel][ByteStart][1] / 10,
              Outputs->MarginResult[LastCmdV][Rank][Channel][ByteStart][0] / 10,
              Outputs->MarginResult[LastCmdV][Rank][Channel][ByteStart][1] / 10,
              PwrChRank[Channel][Rank].RdPower / 10,
              PwrChRank[Channel][Rank].RdPower % 10,
              PwrChRank[Channel][Rank].WrPower / 10,
              PwrChRank[Channel][Rank].WrPower % 10,
              PwrChRank[Channel][Rank].TotalPwr / 10,
              PwrChRank[Channel][Rank].TotalPwr % 10
              );
          }
        } // Rank
      } // SubCh
    } // Ch
  } // Controller
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
  INT64               CmdTriStateSave[MAX_CHANNEL];
  UINT8               PerBitMarginResult[4][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32              MarginBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32              MarginByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8               Rank;
  UINT8               RankMask;
  UINT8               Param;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               SubCh;
  UINT8               SubChMax;
  UINT8               Byte;
  UINT8               ByteStart;
  UINT8               ByteEnd;
  UINT8               Bit;
  UINT32              *BitResult;
  UINT8               Edge;
  UINT8               chBitMask;
  UINT8               LoopCount;
  UINT8               ResultType;
  UINT8               MaxMargin;
  BOOLEAN             EnhancedChannelMode;
  UINT32              GearDivider;
#ifdef MRC_DEBUG_PRINT
  UINT8               BitIndex;
#endif

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Status    = mrcSuccess;
  GetSetDis = 0;
  MrcCall->MrcSetMem ((UINT8 *) CmdTriStateSave, sizeof (CmdTriStateSave), 0);
  GearDivider = (Outputs->Gear2) ? 2 : 1;

  // Check memory used
  EnhancedChannelMode = Outputs->EnhancedChannelMode;
  SubChMax = (EnhancedChannelMode) ? MAX_SUB_CHANNEL : 1;

  if (Inputs->BootMode == bmFast) {
    // Set CPGC mode
    MrcSetNormalMode (MrcData, FALSE);
  }

  // Enable command tri state during RMT training.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, ReadFromCache, &CmdTriStateSave[Channel]);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &GetSetDis);
    }
  }

  if (Inputs->RMTLoopCount != 0) {
    LoopCount  = Inputs->RMTLoopCount;
  } else {
    LoopCount  = 17;
  }

  // Data Margins
  // SOE=1, EnCADB=0, EnCKE=0 SOE=1 sets bit12 of REUT_CH_ERR_CTL
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 0, 0, 8);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select rank for REUT test
    RankMask  = 1 << Rank;
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }
    // Continue with next rank if this rank is not present on any channel
    if (!(chBitMask)) {
      continue;
    }

    for (Param = RdT; Param < WrLevel; Param++) {
      if (Param == WrDqsT) {
        continue;
      }

      ResultType = GetMarginResultType (Param);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            MarginByte[Channel][Byte][Edge] = Outputs->MarginResult[ResultType][Rank][Channel][Byte][Edge];
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
        MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
      } else {
        MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
      }

      MrcGetMarginBit (MrcData, chBitMask, Rank, MarginBit, MarginByte, Param, 0, MaxMargin, FALSE);

      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          ChannelOut        = &ControllerOut->Channel[Channel];
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
              continue;
            }
            ByteStart = EnhancedChannelMode ? ChannelOut->ByteStart[SubCh] : 0;
            ByteEnd = EnhancedChannelMode ? ChannelOut->ByteEnd[SubCh] : Outputs->SdramCount - 1;
            for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
              for (Bit = 0; Bit < MAX_BITS; Bit++) {
                for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                  PerBitMarginResult[ResultType][Rank][Channel][Byte][Bit][Edge] = (UINT8) MarginBit[Channel][Byte][Bit][Edge];
                }
                BitResult = &MarginBit[Channel][Byte][Bit][0];
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
                  ChannelOut->RxDqPb[Rank][Byte][Bit].Right = (UINT8)(BitResult[1] / GearDivider);
                  ChannelOut->RxDqPb[Rank][Byte][Bit].Left  = (UINT8)(BitResult[0] / GearDivider);
                    break;

                  default:
                    break;
                } // switch (Param)
              } // for Bit
            } // for Byte
          } // for SubCh
        } // for Channel
      } // for Controller
    } // for Param
  } // Rank

  // Restore command tri state setting
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateSave[Channel]);
    }
  }

#ifdef MRC_DEBUG_PRINT
  // Print test results
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank Margin Testing Per-Bit: DQ LC = %d\n\n", LoopCount);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Margin\nParams: \tRdT\tWrT\tRdV\tWrV\n"
  );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\t\tLft Rgt Lft Rgt Lft Rgt Lft Rgt\n"
  );
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
              continue;
            }
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              BitIndex = (8 * Byte) + Bit;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dR%dB%s%d:\t", Channel, Rank, ((BitIndex / 10) > 0)? "" : "0", BitIndex);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%2d  %2d\t%2d  %2d\t%2d  %2d\t%2d  %2d\n",
                PerBitMarginResult[LastRxT][Rank][Channel][Byte][Bit][0] / GearDivider,
                PerBitMarginResult[LastRxT][Rank][Channel][Byte][Bit][1] / GearDivider,
                PerBitMarginResult[LastTxT][Rank][Channel][Byte][Bit][0],
                PerBitMarginResult[LastTxT][Rank][Channel][Byte][Bit][1],
                PerBitMarginResult[LastRxV][Rank][Channel][Byte][Bit][0],
                PerBitMarginResult[LastRxV][Rank][Channel][Byte][Bit][1],
                PerBitMarginResult[LastTxV][Rank][Channel][Byte][Bit][0],
                PerBitMarginResult[LastTxV][Rank][Channel][Byte][Bit][1]
              );
            } // Bit
          } // Byte
        }
      } // Rank
    } // Ch
  } // Controller
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
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcStatus       Status;
  UINT32 (*marginch)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];

  UINT8 ResultType;
  UINT8 ResultTypeT;
  UINT8 loopcount;
  UINT8 param;
  UINT8 paramT;
  UINT8 Channel;
  UINT8 byte;
  UINT8 tim;
  UINT8 chBitMask;
  UINT8 MaxTscale;
  UINT8 SkipWait;
  INT8  SumEH;
  INT8  SumEHSign;
  INT8  TimePoints[3];
  UINT8 EHWeights[sizeof (TimePoints)];
  UINT16 mode;
  INT32 center;
  INT32 height;
  UINT32 value0[MAX_CHANNEL];
  UINT32 BERStats[4];
  UINT32 TimScale[MAX_CHANNEL];
  INT32 centersum[MAX_CHANNEL];
  UINT32 MinHalfMargin[MAX_CHANNEL];
  UINT8 MaxMargin;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  marginch  = &Outputs->MarginResult;
  Status    = mrcSuccess;
  MaxTscale = 12;
  SumEH     = 0;
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
  MaxMargin = GetMaxPossibleVrefOffset (MrcData, param);

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

  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, loopcount, NSOE, 0, 0, 8);

  // Calculate SumEH for use in weighting equations
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];
  }

  // Select rank for REUT test
  chBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    chBitMask |= SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask, FALSE, 0);
  }

  // ####################################################
  // #############  Initialize EW/EH variables   ########
  // ####################################################
  Status = GetMarginCh (MrcData, Outputs->MarginResult, paramT, 0xF, 0, FALSE);

  //
  // Update TimScale with results
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    TimScale[Channel] = 0;
    if (!(chBitMask & (1 << Channel))) {
      continue;
    }

    TimScale[Channel] = ((*marginch)[ResultTypeT][0][Channel][0][0] + (*marginch)[ResultTypeT][0][Channel][0][1]) / 20;
    //
    // It is possible TimScale[Channel] is 0.
    //
    if (!TimScale[Channel] || (TimScale[Channel] > MaxTscale)) {
      TimScale[Channel] = MaxTscale;
    }
  }

  Status = GetMarginCh (MrcData, Outputs->MarginResult, param, 0xF, 0, FALSE);

  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TimScale[0] is %d, TimScale[1] is %d\n", TimScale[0], TimScale[1]);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0\t\t\t\t1\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrTime\tLow\tHigh\tHeight\tCenter\t");
  }

  // Loop through all the Time Points to Test
  for (tim = 0; tim < sizeof (TimePoints); tim++) {

    // Setup Timing Offset for this point
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (1 << Channel))) {
        continue;
      }

      value0[Channel] = (INT32) (TimePoints[tim] * TimScale[Channel]) / MaxTscale;

      // There is no multicast per channel...
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        Status = ChangeMargin (MrcData, paramT, value0[Channel], 0, 0, Channel, 0, byte, 0, 1, 0);
      }
    }
    // Run Margin Test
    mode = 0;
    Status = MrcGetBERMarginCh (
              MrcData,
              Outputs->MarginResult,
              chBitMask,
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
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (1 << Channel))) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", value0[Channel]);

      height  = ((*marginch)[ResultType][0][Channel][0][1] + (*marginch)[ResultType][0][Channel][0][0]) / 10;
      center  = (INT32) ((*marginch)[ResultType][0][Channel][0][1] - (*marginch)[ResultType][0][Channel][0][0]);
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "%d\t%d\t%d\t%d\t",
        (*marginch)[ResultType][0][Channel][0][0] / 10,
        (*marginch)[ResultType][0][Channel][0][1] / 10,
        height,
        center / 20
        );

      // Calculate weight for this point
      centersum[Channel] += EHWeights[tim] * center;
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->centersum[%d] = %d, \n", Channel, centersum[Channel]);

      // Determine the smallest half margin
      MinHalfMargin[Channel] = MIN (MinHalfMargin[Channel], (*marginch)[ResultType][0][Channel][0][0]);
      MinHalfMargin[Channel] = MIN (MinHalfMargin[Channel], (*marginch)[ResultType][0][Channel][0][1]);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWtdCntr\t");
  // ####################################################
  // ###########   Center Results per Ch    #############
  // ####################################################
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(chBitMask & (1 << Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    // Calculate CenterPoint.  Round to Nearest Int
    SumEHSign           = (centersum[Channel] < 0) ? (-1) : 1;

    centersum[Channel]  = (centersum[Channel] + 10 * SumEH * SumEHSign) / (20 * SumEH);

    // Apply new centerpoint
    // Only Byte 0 on Channel 0 is needed to update DIMM Vref
    // Skip if there are more channels
    SkipWait = (chBitMask >> (Channel + 1));
    Status = ChangeMargin (MrcData, param, centersum[Channel], 0, 0, Channel, 0xFF, 0, 0, 1, SkipWait);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t\t\t", centersum[Channel]);

    // Update MrcData for future tests
    (*marginch)[ResultType][0][Channel][0][0] = (INT32) ((*marginch)[ResultType][0][Channel][0][0]) + (10 * (centersum[Channel]));
    (*marginch)[ResultType][0][Channel][0][1] = (INT32) ((*marginch)[ResultType][0][Channel][0][1]) - (10 * (centersum[Channel]));
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  // Clean up
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0);

  return Status;
}

/**
  Perform Write Voltage Centering in 2D For DDR4 PDA mode.
  Note: This function currently only supports param = WrV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     Rank        - The particular rank being centered
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
WriteVoltageCentering2D_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
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
  MrcRankOut                              *RankOut;
  MrcStatus                               Status;
  UINT8                                   ResultType;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   RankMask;
  UINT8                                   lcloop;
  UINT8                                   tim;
  UINT8                                   BMap[MAX_SDRAM_IN_DIMM];
  INT8                                    SumEH;
  INT8                                    SumEHSign;
  UINT8                                   MaxTscale;
  UINT16                                  mode;
  INT32                                   center[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   value0[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  BERStats[4];
  UINT32                                  TimScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterRank;
  UINT32                                  EyeShape[sizeof(TimePoints)][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8                                   MaxVrefOffset;
  UINT32                                  Low;
  UINT32                                  High;
  UINT32                                  MinWidth;
  BOOLEAN                                 EyeTooSmall[MAX_CHANNEL];

  MaxVrefOffset = GetMaxPossibleVrefOffset (MrcData, paramV);
  MinWidth      = GetMinRequiredEyeWidth (MrcData, FALSE);
  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  CenterRank = 0;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) EyeTooSmall, sizeof (EyeTooSmall), FALSE);
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

  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, ABGSOE, 0, 0, 8);

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
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    ChBitMask |= SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask & RankMask, FALSE, 0);
  }

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

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d", Channel);
    if (Channel == 0) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "        ");
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d       ", Byte);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nTScale\t");
#endif // MRC_DEBUG_PRINT

  // Update TimScale to have the appropriate eye width (read from last saved parameters)
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }

    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (En2D > 0) {
        TimScale[Channel][Byte] =
          (
            MarginByte[ResultType][0][Channel][Byte][0] +
            MarginByte[ResultType][0][Channel][Byte][1]
          ) /
          20;
      } else {
        TimScale[Channel][Byte] = 1;
      }

      // It is possible sumT is 0.
      if (!(TimScale[Channel][Byte]) || (TimScale[Channel][Byte] > MaxTscale)) {
        TimScale[Channel][Byte] = MaxTscale;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", TimScale[Channel][Byte]);
    }
  }

  Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramV, 0, RankMask);
  ResultType  = GetMarginResultType (paramV);

  // ####################################################
  // ######   Measure Eye Height at all Timing Points  #####
  // ####################################################

  // Loop through all the Time Points to Test
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWrTime\t");

    // Setup Timing Offset for this point
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
        Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, 0, Byte, 0, 1, 0);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", value0[Channel][Byte]);
      }
    }

    // Run Margin Test
    mode = 0;
    Status = MrcGetBERMarginByte (
              MrcData,
              Outputs->MarginResult,
              ChBitMask,
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
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nLo-Hi\t");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d %d\t",
          MarginByte[ResultType][Rank][Channel][Byte][0],
          MarginByte[ResultType][Rank][Channel][Byte][1]
          );
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCenter\t");
#endif // MRC_DEBUG_PRINT

    // Store Results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ChBitMask & (MRC_BIT0 << Channel)) {

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Low  = MarginByte[ResultType][Rank][Channel][Byte][0];
          High = MarginByte[ResultType][Rank][Channel][Byte][1];

          // See if any byte has eye height below minimum on this channel
          if ((Low + High) < (MinWidth * 10)) {
            EyeTooSmall[Channel] = TRUE;
          }

          center[Channel][Rank][Byte] = (INT32) (High - Low);
          if (tim == 0) {
            CenterSumByte[Channel][Byte] = 0;
          }

          // Calculate weight for this point
          CenterSumByte[Channel][Byte] += EHWeights[tim] * center[Channel][Rank][Byte];

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", center[Channel][Rank][Byte] / 20);

          // Record edges for use in per bit margining
          EyeShape[tim][Channel][Byte][0] = Low;
          EyeShape[tim][Channel][Byte][1] = High;
        }
      }
    }

    // Loop once at nominal Vref point
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWtdCntr\t");
  // ####################################################
  // ###########   Center Results per Byte   ############
  // ####################################################
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      if ((1 << Rank) & RankMask) {
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER(Rank)].Rank[Rank % 2];
        // Calculate CenterPoint.  Round to Nearest Int
        // @todo: might need to ajust because now step is 7.8mV
        CenterRank = 0;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          SumEHSign = (CenterSumByte[Channel][Byte] < 0) ? (-1) : 1;

          CenterSumByte[Channel][Byte] = (CenterSumByte[Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", CenterSumByte[Channel][Byte]);
          CenterRank += CenterSumByte[Channel][Byte];

          // Update the Eye Edges
          for (tim = 0; tim < sizeof (TimePoints); tim++) {
            EyeShape[tim][Channel][Byte][0] = (INT32)EyeShape[tim][Channel][Byte][0] + (10 * CenterSumByte[Channel][Byte]);
            EyeShape[tim][Channel][Byte][1] = (INT32)EyeShape[tim][Channel][Byte][1] - (10 * CenterSumByte[Channel][Byte]);

            // Loop once at nominal Vref point
            if (En2D == 0) {
              tim = sizeof (TimePoints);
            }
          }
          // Update MrcData for future tests (MarginResult points back to MrcData)
          // EyeShape for Vref 0 is assumed to have the best shape for future tests.
          MarginByte[ResultType][Rank][Channel][Byte][0] = EyeShape[0][Channel][Byte][0];
          MarginByte[ResultType][Rank][Channel][Byte][1] = EyeShape[0][Channel][Byte][1];
        } // for Byte
        CenterRank /= Outputs->SdramCount;
        // Program common center in Non PDA fashion in order to make sure the PDA is successful
        UpdatePdaCenter (MrcData, Channel, 1 << Rank);
        // Set WrV Offset average across Byte (Non-PDA). Do not update cache
        ChangeMargin (MrcData, WrV, CenterRank, 0, 0, Channel, RankMask, 0, 0, 0, 1);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Write using PDA only when we have a passing window
          if (!EyeTooSmall[Channel]) {
            // Set WrV Offset per byte using PDA. Update cache
            ChangeMargin (MrcData, WrV, CenterSumByte[Channel][Byte], 0, 0, Channel, 1 << Rank, 1 << Byte, 0, 1, 1);
          } else {
            Outputs->Ddr4PdaEnable = FALSE;
          }
        }
      }
    } // for Rank
  } // for Channel

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWrVref");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nC%dR%d\t", Channel, Rank);
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[Rank % 2];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcVrefDqToOffsetDdr4 (RankOut->Ddr4PdaMr6[Byte] & 0x7F));
      }
    }
  }
  //
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nPerByte Margins after per BYTE Centering\nLo-Hi   ");
  //
#endif // MRC_DEBUG_PRINT

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  //
  // Clean up after test
  //
  Status  = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0);
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

  Points2DMax = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 32 : 12;
  Points2DMin = -Points2DMax;

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

  MrcRelaxReadToReadSameRank (MrcData, TRUE);

  Status = EarlyWriteTimingCentering2D (MrcData, TRUE);

  MrcRelaxReadToReadSameRank (MrcData, FALSE);

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
  MrcStatus                                   Status;
  MrcOutput                                   *Outputs;
  MrcInput                                    *Inputs;
  MrcControllerOut                            *ControllerOut;
  MrcChannelOut                               *ChannelOut;
  MrcDebug                                    *Debug;
  UINT16                                      *MrPtr;
  const MRC_FUNCTION                          *MrcCall;
  UINT32                                      Offset;
  UINT8                                       Channel;
  UINT8                                       SubCh;
  UINT8                                       Rank;
  UINT8                                       MaxDevice;
  UINT8                                       Device;
  UINT16                                      ROCount;
  UINT32                                      ROPITicks;
  UINT8                                       Mrr18Result[4];
  UINT8                                       Mrr19Result[4];
  UINT32                                      MrAddr;
  UINT32                                      Lp4ReTrainDuration;
  UINT8                                       DqioDuration;
  UINT8                                       SubChannelOffset;
  UINT16                                      RORunTime;
  BOOLEAN                                     Lp4ReTrainingStatus;
  BOOLEAN                                     IclBPI;
  MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_STRUCT   RODev0123Ch0123Rank012;
  UINT32                                      RODevXCh012Rank3[4];
  MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_STRUCT    RODev01Ch3Rank3;
  MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_STRUCT    RODev23Ch3Rank3;
  MCMISCS_DELTADQSCOMMON0_STRUCT              DeltaDqsCommon0;
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT     Lp4DqsOsclParams;
  static const UINT32 RODevXCh012Rank3Address[4] = { MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_REG, MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_REG, MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_REG, MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_REG };

  Outputs             = &MrcData->Outputs;
  Inputs              = &MrcData->Inputs;
  ControllerOut       = &Outputs->Controller[CONTROLLER_0];
  Debug               = &Outputs->Debug;
  Status              = mrcSuccess;
  MrcCall             = Inputs->Call.Func;

  IclBPI = ((Inputs->CpuModel == cmICL_ULX_ULT && (Inputs->CpuStepping == csIclB0 || Inputs->CpuStepping == csIclB4)) || (Inputs->CpuModel == cmICL_DT_HALO_R && Inputs->CpuStepping == csIclP0));

  RODev01Ch3Rank3.Data = RODev23Ch3Rank3.Data = 0;
  MrcCall->MrcSetMem ((UINT8 *)RODevXCh012Rank3, sizeof(RODevXCh012Rank3), 0);

  DqioDuration = 0;
  ROPITicks = 0;
  MaxDevice = (((Outputs->Lp4x8) && (!Inputs->IclA0)) ? 4 : 2);
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
    Lp4ReTrainDuration = RORunTime*64;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqioDuration = %d\nRORunTime = %d\nLp4ReTrainDuration = %d\n", DqioDuration, RORunTime, Lp4ReTrainDuration);
    for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; (Rank < MAX_RANK_IN_CHANNEL) && (Status == mrcSuccess); Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        MrPtr = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR;
        Status = MrcLpddr4SetMr23 (
                     MrcData,
                     DqioDuration,
                     &MrPtr[mrIndexMR23]
                     );
        for (SubCh = 0; (SubCh < MAX_SUB_CHANNEL) && (Status == mrcSuccess); SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          Status = MrcIssueMrw (
                       MrcData,
                       Channel,
                       SubCh,
                       Rank,
                       mrMR23,
                       (UINT8) MrPtr[mrIndexMR23],
                       FALSE,  // InitMrw
                       FALSE,  // ChipSelect2N
                       TRUE    // DebugPrint
                       );
        } // for SubCh
      } // for Rank
    } // for Channel

    for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; (Rank < MAX_RANK_IN_CHANNEL) && (Status == mrcSuccess); Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel) == 0) {
          continue;
        }
        for (SubCh = 0; (SubCh < MAX_SUB_CHANNEL) && (Status == mrcSuccess); SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          Status = MrcIssueMpc (
                       MrcData,
                       Channel,
                       SubCh,
                       Rank,
                       MRC_LP4_MPC_START_DQS_OSC,
                       0,
                       TRUE
                       );
          MrcWait (MrcData, 1 * MRC_TIMER_1US);
        } // for SubCh
      } // for Rank
    } // for Channel

    if (Status == mrcSuccess) {
      Lp4ReTrainingStatus = TRUE;
      for (Channel = 0; (Channel < MAX_CHANNEL) && (Lp4ReTrainingStatus == TRUE); Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          SubChannelOffset = SubCh + (Channel * MAX_CHANNEL);
          Offset = MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_REG +
                 ((MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_REG - MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_REG) * SubChannelOffset);
          for (Device = 0; Device < MaxDevice; Device++) {
            if (Device == 2) {
              Offset += (MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_REG - MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_REG);
            }
            Offset += ((MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_REG - MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_REG) * (Device & 1));
            RODev0123Ch0123Rank012.Data = 0;
            for (Rank = 0; Rank < (MAX_RANK_IN_CHANNEL); Rank++) {
              if (!MrcRankInChannelExist (MrcData, (UINT8) Rank, (UINT8) Channel)) {
                continue;
              }

              // MR18
              MrAddr = 18;
              MrcIssueMrr (MrcData, Channel, SubCh, Rank, MrAddr, Mrr18Result);
              // MR19
              MrAddr = 19;
              MrcIssueMrr (MrcData, Channel, SubCh, Rank, MrAddr, Mrr19Result);
              ROCount = Mrr19Result[Device / 2] << 8 | Mrr18Result[Device / 2];
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Dev%d MR18 = 0x%02X  MR19 = 0x%02X  ROCount = %d\n",
                Device,
                Mrr18Result[Device / 2],
                Mrr19Result[Device / 2],
                ROCount
                );
              // Max value for ROCount is 4095
              if (ROCount <= 4095) {
                ROPITicks = 0;
                if (ROCount > 0) {
                  ROPITicks = (UINT32) ((64 * RORunTime) / ROCount);
                }

                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ROPITicks = %d\n", ROPITicks);
                if (ROPITicks <= MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_MAX) {
                  // for Rank3, we used a seperate local variable for each R0 register and write it after the loops
                  if (Rank == 3) {
                    if (SubChannelOffset == 3) {
                      // Set the corresponding ROCount Ch3/R3 bit field here, indexed by Device
                      if (Device < 2) {
                        RODev01Ch3Rank3.Data |= ROPITicks << (MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_WID * Device);
                      }else{
                        RODev23Ch3Rank3.Data |= ROPITicks << (MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_WID * (Device & 1));
                      }
                    } else {  // SubChannelOffset != 3)
                      RODevXCh012Rank3[Device] |= ROPITicks << (MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_WID * SubChannelOffset);
                    } // Channel != 3
                  } else { // Rank != 3
                    // Set the corresponding ROCount bit field here, indexed by Rank
                    RODev0123Ch0123Rank012.Data |= ROPITicks << (MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_WID * Rank);
                  }
                } else {
                  MRC_DEBUG_MSG (
                    Debug,
                    MSG_LEVEL_ERROR,
                    "ROPITicks %d is greater than %d\n",
                    ROPITicks,
                    MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_MAX
                    );
                  Lp4ReTrainingStatus = FALSE;
                  break;
                } // (ROPITicks <= MCMISCS_ROCOUNTTRAINCH0DEV0_ROCountTrainRank1Dev0_MAX)
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
            } // for Rank
            if (Lp4ReTrainingStatus == TRUE) {
              // Write the new non-Rank3 RO values back to their corresponding offsets.
              MrcWriteCR(MrcData, Offset, RODev0123Ch0123Rank012.Data);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Ch%d SubCh%d Dev%d RoCountTrain=%08X\n",
                Channel,
                SubCh,
                Device,
                RODev0123Ch0123Rank012.Data
                );

            } else {
              Status = mrcFail;
              break;
            } // (Lp4ReTrainingStatus == TRUE)
          } // for Device
        } // for SubCh
      } // for Channel

      if (Lp4ReTrainingStatus == TRUE) {
        // Write the remaining Rank3 Registers
        for (Device = 0; Device < MaxDevice; Device++) {
          MrcWriteCR (MrcData, RODevXCh012Rank3Address[Device], RODevXCh012Rank3[Device]);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RODev%dCh012Rank3 = %08X\n", Device, RODevXCh012Rank3[Device]);
        }
        MrcWriteCR (MrcData, MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_REG, RODev01Ch3Rank3.Data);
        if (MaxDevice == 4) {
          MrcWriteCR (MrcData, MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_REG, RODev23Ch3Rank3.Data);
        }

        MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  "RODev01Ch3Rank3 = %08X\nRODev23Ch3Rank3 = %08X\n",
                  RODev01Ch3Rank3.Data,
                  RODev23Ch3Rank3.Data
                  );
      } else {
        Status = mrcFail;
      } // (Lp4ReTrainingStatus == TRUE)           );

      // After all RO values are written, set up the OSC Params per channel
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        if (Lp4ReTrainingStatus == TRUE) {
          Offset = CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG +
                 ((CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG - CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG) * Channel);
          Lp4DqsOsclParams.Data = MrcReadCR (MrcData, Offset);
          Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD          = ZQCS_PERIOD_LPDDR * 128;
          Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL         = 0;
          //Lp4DqsOsclParams.Bits.serialize_ERM_zqcs      = ;
          Lp4DqsOsclParams.Bits.disable_wr_on_pkgc_exit = 1;
          Lp4DqsOsclParams.Bits.disable_wr_on_SR_exit   = 1;
          MrcWriteCR (MrcData, Offset, Lp4DqsOsclParams.Data);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Ch%d Lp4DqsOsclParams=%08X\n",
            Channel,
            Lp4DqsOsclParams.Data
            );
        } else {
          Status = mrcFail;
          break;
        } // (Lp4ReTrainingStatus == TRUE)
      } // for Channel

      if (Lp4ReTrainingStatus == TRUE) {
        Offset = MCMISCS_DELTADQSCOMMON0_REG;
        DeltaDqsCommon0.Data = MrcReadCR (MrcData, Offset);
        DeltaDqsCommon0.Bits.Lp4ReTrainDuration   = Lp4ReTrainDuration;
        DeltaDqsCommon0.Bits.Lp4DeltaDQSTrainMode = 1;
        DeltaDqsCommon0.Bits.clock_on_with_rxanalogen = IclBPI;
        MrcWriteCR (MrcData, Offset, DeltaDqsCommon0.Data);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "DeltaDqsCommon0=%08X\n",
          DeltaDqsCommon0.Data
          );
      } else {
        Status = mrcFail;
      } // (Lp4ReTrainingStatus == TRUE)
    } // (Status == mrcSuccess)
  } // (Status == mrcSuccess)
  return Status;
}
