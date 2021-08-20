/** @file
  Implementation of the command training algorithm.
  The algorithm finds the N mode for the current board and also the correct
  CLK CMD CTL pi setting.

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
#include "MrcCommandTraining.h"
#include "MrcDdrCommon.h"
#include "MrcCpgcApi.h"
#include "Cpgc20Patterns.h"
#include "Cpgc20TestCtl.h"
#include "MrcMaintenance.h"
#include "MrcCpgcOffsets.h"
#include "MrcLpddr4.h"
#include "MrcGears.h"
#include "MrcReadDqDqs.h"

/**
  This function performs early command training.
  Only needed for LPDDR4; DDR4 relies on 3N timing and initial CS/CLK PI settings/

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if it succeeded
**/
MrcStatus
MrcEarlyCommandTraining (
  IN MrcParameters *const MrcData
  )
{
  // Check if LPDDR4 memory is used
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4) {
    return EarlyCommandTrainingLpddr4 (MrcData);
  }

  return mrcSuccess;
}

/**
  Find a good starting point for DDR4 CTL/CMD/CLK, using a quick 2D search.
  Sweep CTL/CMD PI range and look for best CLK margin using linear CLK sweep at each point.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
CtlClockCentering (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcStatus           Status;
  UINT32              Left[MAX_CHANNEL];
  UINT32              Right[MAX_CHANNEL];
  UINT32              Width[MAX_CHANNEL];
  UINT32              MaxWidth[MAX_CHANNEL];
  UINT8               BestCtlPi[MAX_CHANNEL];
  UINT8               BestCtlPiLast[MAX_CHANNEL];
  UINT8               ChBitMask;
  UINT8               RankMask;
  UINT8               Channel;
  UINT8               ResultRank[MAX_CHANNEL];
  UINT8               Rank;
  UINT8               CtlPiCode;
  UINT8               CtlLow;
  UINT8               CtlHigh;
  UINT8               CtlStep;
  INT8                ClkLow;
  UINT8               ClkHigh;
  UINT8               ClkStep;
  BOOLEAN             SkipVref;
  BOOLEAN             SkipPrint;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ControllerOut  = &Outputs->Controller[0];
  Status         = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) Left, sizeof (Left), 0);
  MrcCall->MrcSetMem ((UINT8 *) Right, sizeof (Right), 0);
  MrcCall->MrcSetMem ((UINT8 *) Width, sizeof (Width), 0);
  MrcCall->MrcSetMem (BestCtlPi, sizeof (BestCtlPi), 0);
  MrcCall->MrcSetMem (BestCtlPiLast, sizeof (BestCtlPiLast), 0);
  MrcCall->MrcSetMem (ResultRank, sizeof (ResultRank), 0);
  ClkLow  = 0;
  ClkHigh = 127;
  CtlLow  = 32;   // [0..127] --> [32..96], keep 32 ticks on each side for later margining steps.
  CtlHigh = 96;
  CtlStep = 16;

  RankMask = Outputs->ValidRankMask;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((1 << Rank) & ControllerOut->Channel[Channel].ValidRankBitMask) {  // Pick one rank to get the results from
        ResultRank[Channel] = Rank;
        break;
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Clock Timing per rank\n\tChannel 0\t\t\tChannel 1\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CTL/CMD\tLeft\tRight\tWidth\t\tLeft\tRight\tWidth\n");

  // Setup CPGC Test to iteration through appropriate ranks during test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
  }

  SkipVref  = TRUE;
  SkipPrint = TRUE;
  MrcCall->MrcSetMem ((UINT8 *) MaxWidth, sizeof (MaxWidth), 0);

  for (CtlPiCode = CtlLow; CtlPiCode <= CtlHigh; CtlPiCode += CtlStep) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u", CtlPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChBitMask) {
        // Shift both CTL and CMD
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  RankMask, 0, CtlPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd,  RankMask, 0x1F, CtlPiCode, 1);  //0x1F = All 5 Cmd Groups
      }
    }

    ClkStep = 6;
    CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, SkipPrint, SkipVref);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        if (Channel == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
        }
        continue;
      }
      Rank = ResultRank[Channel];
      Left[Channel]  = Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] / 10;
      Right[Channel] = Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] / 10;
      Width[Channel] = Right[Channel] - Left[Channel];
      if (Width[Channel] > MaxWidth[Channel]) {
        MaxWidth[Channel] = Width[Channel];
        BestCtlPi[Channel] = BestCtlPiLast[Channel] = CtlPiCode;
      } else if (Width[Channel] == MaxWidth[Channel]) { // Track the last PI which still gives the max width
        BestCtlPiLast[Channel] = CtlPiCode;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%u\t%u\t%u\t", Left[Channel], Right[Channel], Width[Channel]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // for CtlPiCode

  // Apply the best CTL/CMD PI and re-center the CLK
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChBitMask) {
      CtlPiCode = (BestCtlPi[Channel] + BestCtlPiLast[Channel]) / 2;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: Best CTL/CMD PI is %u, CLK width = %u\n", Channel, CtlPiCode, MaxWidth[Channel]);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl,  RankMask, 0, CtlPiCode, 1);
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd,  RankMask, 0x1F, CtlPiCode, 1);  //0x1F = All 5 Cmd Groups
    }
  }
  SkipPrint = FALSE;
  ClkStep = 4;
  Status = CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, SkipPrint, SkipVref);

  return Status;
}

/**
  This function performs Late command training.
  Center CMD/CTL-CLK timing using complex patterns.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it's a success return mrcSuccess
**/
MrcStatus
MrcLateCommandTraining (
  MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcStatus           Status;
  MrcProfile          Profile;
  INT64               GetSetVal;
  UINT32              MinCode;
  UINT32              SubCh;
  UINT8               Loopcount;
  UINT8               Cmd2N;
  UINT8               Channel;
  UINT8               ChBitMask;
  UINT8               RankMask;
  UINT8               SubChMask;
  UINT8               Rank;
  UINT8               Ranks;
  UINT8               Byte;
  UINT8               CmdGroup;
  UINT8               CmdGroupMax;
  UINT8               CmdPiCode[MAX_CHANNEL];
  UINT8               CtlPiCode[MAX_CHANNEL];
  UINT8               MidPointCmd[MAX_COMMAND_GROUPS][MAX_CHANNEL];
  BOOLEAN             Lpddr4;
  BOOLEAN             Ddr4;
  BOOLEAN             ExitOnFailure;
  CH0_SC0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Profile       = Inputs->MemoryProfile;
  ExitOnFailure = (Inputs->ExitOnFailure == TRUE);
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];

  Lpddr4  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  CmdGroupMax = (Ddr4) ? MAX_COMMAND_GROUPS : MAX_COMMAND_GROUPS - 1;

  ChBitMask = Outputs->ValidChBitMask;
  RankMask  = Outputs->ValidRankMask;
  SubChMask = 0;

  Loopcount = 10;

  // Setup CPGC
  // LC = 10, SOE = 1 (NTHSOE), EnCADB = 1, EnCKE = 0
  SetupIOTestCADB (MrcData, ChBitMask, Loopcount, NTHSOE, 1, 0);

  // Program default rank mapping
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    ChannelOut  = &ControllerOut->Channel[Channel];
    SubChMask |=  ChannelOut->ValidSubChBitMask;
  }

  if (!Lpddr4) {
    Cmd2N = FALSE;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        Cmd2N = (ControllerOut->Channel[Channel].Timing[Profile].NMode == 2) ? TRUE : FALSE; // All channels have same NMode
        break;
      }
    }
    CmdPiCode[0] = CmdPiCode[1] = (Cmd2N == TRUE) ? 85 : 64;
    CtlPiCode[0] = CtlPiCode[1] = 64;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      " Cmd2N %d, CmdPiCode %d, ChBitMask = 0x%x\n",
      Cmd2N,
      CmdPiCode[0],
      ChBitMask
      );

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }

      ChannelOut = &ControllerOut->Channel[Channel];
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
      // Shift everything to the right.  To get DQ timing right, program Clk to 0
      ShiftPIforCmdTraining (
        MrcData,
        Channel,
        MrcIterationClock,
        ChannelOut->ValidRankBitMask,
        1,
        0 - (INT32) (IntCmdTiming->ClkPiCode[0]),
        1
        );
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, ChannelOut->ValidRankBitMask, 0x1F, CmdPiCode[Channel], 1);  //0x1F = All 5 Cmd Groups
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, ChannelOut->ValidRankBitMask, 0, CtlPiCode[Channel], 1);
    }
  }

  // Get the new midpoint for CMD
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
    for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
      MidPointCmd[CmdGroup][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
    }
  }

  if (Lpddr4) {
    // Center Command Timing
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** ECT results\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u: CA%c: Pi0Code: %d, Pi1Code: %d\n",
          Channel,
          'A',
          MidPointCmd[0][Channel],
          MidPointCmd[1][Channel]
          );
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CAA[Pi0] Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 0), MidPointCmd[0]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CAA[Pi1] Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 1), MidPointCmd[1]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** ECT results\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u: CA%c: Pi0Code: %d, Pi1Code: %d\n",
          Channel,
          'B',
          MidPointCmd[2][Channel],
          MidPointCmd[3][Channel]
          );
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CAB[Pi0] Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 2), MidPointCmd[2]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CAB[Pi1] Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 3), MidPointCmd[3]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Control Timing\n");

    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (!(SubChMask & (1 << SubCh))) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** ECT results SubChannel %d\n", SubCh);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          // Ctl Pi is shared across Rank 0 and Rank 1.  Use Rank 0 entry for now.
          // @todo: Determine what ECT is doing with the final answer and update appropriately.
          IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
          CtlPiCode[Channel] = IntCmdTiming->CtlPiCode[SubCh];
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%uSch%u: CTL: %u\n", Channel, SubCh, CtlPiCode[Channel]);
        }
      }

      // RankMask should be 0x1 or 0x3.  Cannot change per Channel or Sub Channel.
      // Group mask for Control is used to select which SubChannel to train.
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCentering CTL on Ranks 0x%x\n", RankMask);
      Status = CmdTimingCentering (MrcData, MrcIterationCtl, RankMask, 1 << SubCh, CtlPiCode);
      if ((Status != mrcSuccess) && (ExitOnFailure)) {
        return Status;
      }
    }
  } else { // not Lpddr4
    // Center CMD/CTL vs. CLK
    Status = CtlClockCentering (MrcData);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    // Get the new midpoint for CMD and CTL
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
      CtlPiCode[Channel] = IntCmdTiming->CtlPiCode[Channel];
      for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
        MidPointCmd[CmdGroup][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
      }
    }

    // Center Command Timing
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDA_Pi0Code Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 0), MidPointCmd[0]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDA_Pi1Code Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 1), MidPointCmd[1]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDB_Pi0Code Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 2), MidPointCmd[2]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDB_Pi1Code Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 3), MidPointCmd[3]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CKECMD_Pi2Code Timing\n");
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << 4), MidPointCmd[4]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    // Center Control Timing.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center Control Timing.");
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Ranks = (1 << Rank);
      Ranks = Ranks & RankMask;

      if (Ranks) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n Ranks 0x%x\n", Ranks);
        Status = CmdTimingCentering (MrcData, MrcIterationCtl, Ranks, 1, CtlPiCode);
        if ((Status != mrcSuccess) && (ExitOnFailure)) {
          return Status;
        }
      }
    }
  }

  // Normalize timing back to 0 to improve performance
  if (Ddr4) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Normalize timing back to 0\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];

      // Find the minimum PI Code across all relevant CMD and CTL fubs
      // CLK shift will also change RcvEn / TxDq / TxDqs, so check them as well.
      MinCode     = MRC_UINT32_MAX;
      for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
        MinCode = MIN (MinCode, IntCmdTiming->CmdPiCode[CmdGroup]);
      }

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          // Cke PI
          MinCode = MIN (MinCode, IntCmdTiming->CkePiCode[Rank]);
          // Ctl PI
          MinCode = MIN (MinCode, IntCmdTiming->CtlPiCode[Rank]);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
            MinCode = MIN (MinCode, (UINT32) GetSetVal);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
            MinCode = MIN (MinCode, (UINT32) GetSetVal);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
            MinCode = MIN (MinCode, (UINT32) GetSetVal);
          }
        }
      }

      if (MinCode >= 32) {
        MinCode = MIN (MinCode, MinCode - 32);  // Keep at least 32 PI ticks for margining.
      } else {
        MinCode = 0;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d: shifting all PI settings by Min PI Code = %d\n", Channel, MinCode);
      ShiftChannelTiming (MrcData, Channel, (-1) * MinCode);
    } // for Channel
  } // Ddr4

  // Disable CADB Deselects after Command Training
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);
  if (MrcData->Inputs.TrainingEnables2.DCC && Lpddr4) {
    MrcDccClkUpdate (MrcData);
  }
  // Finish Training with JEDEC Reset / Init
  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  Perform Command Voltage Centering.

  DDR4:   CmdV is per DIMM
  LPDDR4: CmdV is per rank (we keep same MR values for both subch)

  @param[in, out] MrcData         - Include all MRC global data.
  @param[in]      EarlyCentering  - Execute as early centering routine

  @retval MrcStatus -  if it succeeded returns mrcSuccess
**/
MrcStatus
CmdVoltageCentering (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              EarlyCentering
  )
{
  const MrcInput *Inputs;
  MrcDebug       *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput      *Outputs;
  MrcStatus      Status;
  UINT32         *Margin;
  UINT8          LoopCount;
  UINT8          Channel;
#ifdef MRC_DEBUG_PRINT
  UINT8          Dimm;
#endif
  UINT8          Rank;
  UINT8          FirstRank;
  UINT8          Byte;
  UINT8          RankMask;
  UINT32         Low[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32         High[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32         Height;
  UINT16         MinHeight;
  INT32          Center[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  BOOLEAN        Ddr4;
  CH0_SC0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Ddr4      = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  LoopCount = 10;
  Status    = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) Low, sizeof (Low), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) High, sizeof (High), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) Center, sizeof (Center), 0);
  MinHeight = MrcGetUpmPwrLimit (MrcData, WrV, UpmLimit) / 2;   // 1/2 WrV UPM Limit

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Cmd Vref Training with LC = %d\n", LoopCount);
  Status = DQTimeCentering1D (
            MrcData,
            Outputs->ValidChBitMask,
            CmdV,
            0,          // ResetPerBit
            LoopCount,
            MRC_PRINTS_ON,
            EarlyCentering
            );

  // Find low/high margins per DIMM / rank
  // Don't check for channel/rank/byte presense to save code size
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) == 0) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        Margin = &Outputs->MarginResult[LastCmdV][Rank][Channel][Byte][0];
        Low[Channel][Rank]  = MIN (Low[Channel][Rank],  Margin[0]);
        High[Channel][Rank] = MIN (High[Channel][Rank], Margin[1]);
        if (Ddr4) {
          if (Inputs->IclA0) {
            // ICL A0: CmdV is per channel, so get the worst case of all ranks into rank0
            Low[Channel][0]  = MIN (Low[Channel][0], Margin[0]);
            High[Channel][0] = MIN (High[Channel][0], Margin[1]);
          } else {
            // DDR4 CmdV is per DIMM, store per-DIMM margins in Rank0 and Rank2
            if ((Rank % 2) != 0) {  // Second rank of the DIMM
              FirstRank = Rank & 2; // 0 or 2
              Low[Channel][FirstRank]  = MIN (Low[Channel][FirstRank],  Margin[0]);
              High[Channel][FirstRank] = MIN (High[Channel][FirstRank], Margin[1]);
            }
          }
        } // Ddr4
      } // Byte
    } // Rank
  } // Channel

  // Calculate center value
  // Don't check for channel/rank presense to save code size
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Center[Channel][Rank] = ((INT32) (High[Channel][Rank] - Low[Channel][Rank])) / 20;
    }
  }

#ifdef MRC_DEBUG_PRINT
  // Print per-channel/DIMM/Rank results summary
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd Vref Summary:\n\tLow\tHigh\tHeight\tCenter\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (Ddr4 && ((Rank % 2) != 0)) {  // DDR4 is per DIMM, so skip odd ranks
        continue;
      }
      Dimm = Rank / 2;
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          Ddr4 ? "C%u DIMM%u: %u\t%u\t%u\t%d\n" : "C%u R%u:\t%u\t%u\t%u\t%d\n",
          Channel,
          Ddr4 ? Dimm : Rank,
          Low[Channel][Rank] / 10,
          High[Channel][Rank] / 10,
          (Low[Channel][Rank] + High[Channel][Rank]) / 10,
          Center[Channel][Rank]
          );
      }
    } // Rank
  } // for Channel
#endif // MRC_DEBUG_PRINT

  // Apply the center value per channel / DIMM / Rank
  // Check height against UPM limits
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (Ddr4 && ((Rank % 2) != 0)) {  // DDR4 is per DIMM, so skip odd ranks
        continue;
      }
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        RankMask = 1 << Rank;
        ChangeMargin (MrcData, CmdV, Center[Channel][Rank], 0, 0, Channel, RankMask, 0, 0, 1, 0);
        Height = Low[Channel][Rank] + High[Channel][Rank];
        if (Height < MinHeight) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Height region (%d) less than expected value (%d)\n", gErrString, Height / 10, MinHeight / 10);
          if (Inputs->ExitOnFailure) {
//            return mrcMiscTrainingError;
          }
        }
      }
    } // Rank
  }
  MrcResetSequence (MrcData);

  // Update MrcData for future tests
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        Outputs->MarginResult[LastCmdV][Rank][Channel][0][0] = Low[Channel][Rank]  + Center[Channel][Rank];
        Outputs->MarginResult[LastCmdV][Rank][Channel][0][1] = High[Channel][Rank] - Center[Channel][Rank];
      }
    }
  }

  if (EarlyCentering) {
    // Re-center MPR at the final CmdV
    ReadMprTraining (MrcData, Outputs->ValidRankMask, 4, MRC_PRINTS_OFF); // HW-based, steps of 4
  }

  // Disable CADB Deselects
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  return Status;
}

/**
  Perform Early Command Voltage Centering.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeded returns mrcSuccess
**/
MrcStatus
MrcEarlyCmdVoltageCentering (
  IN OUT MrcParameters *const MrcData
  )
{
  return CmdVoltageCentering (MrcData, TRUE);
}

/**
  Perform Command Voltage Centering.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeded returns mrcSuccess
**/
MrcStatus
MrcCmdVoltageCentering (
  IN OUT MrcParameters *const MrcData
  )
{
  return CmdVoltageCentering (MrcData, FALSE);
}

/**
  Centers Command Timing around a MidPoint

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Iteration       - Determines which PI to shift
  @param[in] Ranks           - Valid Rank bit mask
  @param[in] GroupMask       - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in] MidPoint        - The MidPoint to center around (per channel)

  @retval Nothing
**/
MrcStatus
CmdTimingCentering (
  IN MrcParameters *const MrcData,
  IN UINT8                Iteration,
  IN UINT8                Ranks,
  IN UINT8                GroupMask,
  IN UINT8                MidPoint[MAX_CHANNEL]
  )
{
  const MrcInput     *Inputs;
  MrcDebug           *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput          *Outputs;
  MrcControllerOut   *ControllerOut;
  MrcStatus          Status;
  UINT8              Ledge[MAX_CHANNEL];
  UINT8              Redge[MAX_CHANNEL];
  UINT8              Mid[MAX_CHANNEL];
  UINT8              Low[MAX_CHANNEL];
  UINT8              High[MAX_CHANNEL];
  static const INT8  VrefOffsets[2] = {-8, 8};
  UINT8              Center;
  UINT8              ChBitMask;
  UINT8              RankMask;
  UINT8              Channel;
  UINT8              MinWidth = 18;
  UINT8              lWidth;
  BOOLEAN            SkipVref;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  ControllerOut  = &Outputs->Controller[0];
  Status         = mrcSuccess;
  MrcCall->MrcSetMem (Ledge, sizeof (Ledge), 0);
  MrcCall->MrcSetMem (Redge, sizeof (Redge), 0);

  // Binary search will use the full PI range of [0..127]
  MrcCall->MrcSetMem (Low, sizeof (Low), 0);
  MrcCall->MrcSetMem (High, sizeof (High), 127);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%u", Channel);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
#endif // MRC_DEBUG_PRINT

  // Setup CPGC Test to iteration through appropriate ranks during test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, Ranks, FALSE, 0);
    if (MidPoint != NULL) {
      Mid[Channel] = MidPoint[Channel];
    }
  }

  if (Iteration == MrcIterationClock) {
    // Use a linear search to center clock and Update Clock Delay/Host
    // Allow wrap around since this is clock
    // CmdLinearFindEdges also programs the new values
    SkipVref = FALSE;
    Status = CmdLinearFindEdges (MrcData, Iteration, ChBitMask, Ranks, GroupMask, Low[0], High[0], 6, 1, (INT8 *) VrefOffsets, FALSE, SkipVref);
  } else {
    CmdBinaryFindEdge (MrcData, Iteration, ChBitMask, Ranks, GroupMask, Low, Mid, 0, (INT8 *) VrefOffsets);
    Ledge[0] = Mid[0];
    Ledge[1] = Mid[1];  // CountUp is 0 so return High.
    if (MidPoint == NULL) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Midpoint[] is NULL and MrcIterationClock not selected!\n");
      return mrcWrongInputParameter;
    } else {
      Mid[0]   = MidPoint[0];
      Mid[1]   = MidPoint[1]; //Mid Modified by CmdBinaryFindEdge
    }
    CmdBinaryFindEdge (MrcData, Iteration, ChBitMask, Ranks, GroupMask, Mid, High, 1, (INT8 *) VrefOffsets);
    Redge[0] = Mid[0];
    Redge[1] = Mid[1];  // CountUp is 1 so return Low.
    // Update Variables:
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCH\tLeft\tRight\tWidth\tCenter");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        continue;
      }
      RankMask  = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
      lWidth    = Redge[Channel] - Ledge[Channel];

      if ((Redge[Channel] == 127) && (Ledge[Channel] == 0)) {
        // No errors found
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nNo Errors Found for C%u!\n", Channel);
        Center = MidPoint[Channel];
      } else {
        Center = (Ledge[Channel] + Redge[Channel] + 1) / 2;
        if (lWidth < MinWidth) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nEye < %u for C%u!\n", MinWidth, Channel);
          Status = mrcMiscTrainingError;
        }
      }

      ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, Center, 1);

      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\n %d\t%d\t%d\t%d\t%d",
        Channel,
        Ledge[Channel],
        Redge[Channel],
        lWidth,
        Center
        );
    } // for Channel
  }

  return Status;
}

#ifdef MRC_MINIBIOS_BUILD
/**
  Plot CmdT (linear CLK shift) vs CmdV, used for debug

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
CommandPlot2D (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput       *Inputs;
  MrcDebug             *Debug;
  const MRC_FUNCTION   *MrcCall;
  MrcOutput            *Outputs;
  MrcChannelOut        *ChannelOut;
  MrcControllerOut     *ControllerOut;
  MrcStatus            Status;
  BOOLEAN              Pass;
  UINT8                Channel;
  UINT8                ChannelMask;
  UINT8                RankMask;
  UINT8                Rank;
  INT16                LCTDelay;
  UINT8                LCTStep = 1;
  UINT8                ChError;
  INT8                 Vref;
  INT8                 VrefLow  = -63;
  INT8                 VrefHigh = 63;
  INT8                 VrefStep = 2;
  UINT8                CmdLoopCount;
  INT8                 Low = -64;
  UINT8                High = 64;
  UINT8                chBitMask;
  UINT8                chBitMaskToRun;
  UINT8                ChToPlot;
  UINT8                GroupMask;
  BOOLEAN              Ddr4;
  CH0_SC0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  GroupMask = 3;
  chBitMaskToRun = 0x3;
  CmdLoopCount = 17;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask  = 1 << Rank;
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }
    if (chBitMask == 0) { // Continue with next rank if this rank is not present on any channel
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %u\n", Rank);

    // Use CADB test for Cmd to match Late Command Training
    SetupIOTestCADB (MrcData, chBitMask, CmdLoopCount, NSOE, 1, 0);

    for (ChToPlot = 0; ChToPlot < MAX_CHANNEL; ChToPlot++) {
      if (((1 << ChToPlot) & chBitMask) == 0) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      ChannelMask = 1 << ChToPlot;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nChannel: %u\n", ChToPlot);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nVref");

      for (Vref = VrefHigh; Vref >= VrefLow; Vref -= VrefStep) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%d\t", Vref);

        for (LCTDelay = Low; LCTDelay <= High; LCTDelay += LCTStep) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if ((1 << Channel) & chBitMask) {
              ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, GroupMask, LCTDelay, 0);
            }
          }

          ChangeMargin (MrcData, CmdV, Vref, 0, 0, ChToPlot, ChannelOut->ValidRankBitMask, 0, 0, 0, 0);
          Status = MrcResetSequence (MrcData);  // Reset DDR
          ChError = RunIOTest (MrcData, chBitMaskToRun, Outputs->DQPat, 1, 0);

//          FailCount = 0;
//          for (Test = 1; Test <= 3; Test++) {
//            ChError = RunIOTest (MrcData, ChannelMask, Outputs->DQPat, 1, 0);
          Pass = ((ChError & ChannelMask) == 0);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? "." : "#");
//            if (!Pass) MRC_DEADLOOP();
//            FailCount = Pass ? FailCount : FailCount + 1;
//          }
//          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (FailCount == 0) ? "." : "%d", FailCount);
        } // for LCTDelay
      } // for Vref
    } // for ChToPlot

    // Restore centered value
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      ChangeMargin (MrcData, CmdV, 0, 0, 0, Channel, ChannelOut->ValidRankBitMask, 0, 0, 0, 0);
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, 3, 0, 0);
      }
    }
  } // for Rank
  // Disable CADB deselects
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  Status = MrcResetSequence (MrcData);
  return Status;
}

#endif // MRC_MINIBIOS_BUILD

/**
  Use a linear search to find the edges between Low and High
  if WrapAround = 0: Look for largest passing region between low and high
  if WrapAround = 1: Look for largest passing region, including wrapping from high to low

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      chBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in]      Low         - Low limit
  @param[in]      High        - High limit
  @param[in]      Step        - Step size
  @param[in]      WrapAllowed - Determines the search region
  @param[in]      VrefOffsets - Array of Vref offsets
  @param[in]      SkipPrint   - Switch to enable or disable debug printing
  @param[in]      SkipVref    - Skip changing CMD Vref offsets, only run test once at the current Vref.

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
MrcStatus
CmdLinearFindEdges (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                chBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN     INT8                 Low,
  IN     UINT8                High,
  IN     UINT8                Step,
  IN     UINT8                WrapAllowed,
  IN     INT8                 *VrefOffsets,
  IN     BOOLEAN              SkipPrint,
  IN     BOOLEAN              SkipVref
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcDebugMsgLevel   DebugLevel;
  INT32             *IPStart;
  INT32             *IPEnd;
  INT32             *CPStart;
  INT32             *CPEnd;
  INT32             *LPStart;
  INT32             *LPEnd;
  MrcStatus         Status;
  BOOLEAN           Pass;
  INT32             InitialPassingStart[MAX_CHANNEL];
  INT32             InitialPassingEnd[MAX_CHANNEL];
  INT32             CurrentPassingStart[MAX_CHANNEL];
  INT32             CurrentPassingEnd[MAX_CHANNEL];
  INT32             LargestPassingStart[MAX_CHANNEL];
  INT32             LargestPassingEnd[MAX_CHANNEL];
  INT32             lWidth;
  INT32             iWidth;
  INT32             cWidth;
  INT32             Center;
  INT16             LCTDelay;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             RankMask;
  UINT8             Rank;
  UINT8             LCTStep;
  UINT8             LastStep;
  UINT8             Vloop;
  UINT8             VoltageLoopCount;
  UINT8             ChError;
  INT8              Vref;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  lWidth        = 0;
  iWidth        = 0;
  cWidth        = 0;
  DebugLevel    = SkipPrint ? MSG_LEVEL_NEVER : MSG_LEVEL_NOTE;
  LCTStep       = Step;

  VoltageLoopCount  = 2;

  MRC_DEBUG_MSG (Debug, DebugLevel, "CLkDlay\t\t0 1");

  for (LCTDelay = Low; LCTDelay <= High; LCTDelay += LCTStep) {
    // Update Timing
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & chBitMask) {
        RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, LCTDelay, 0);
      }
    }

    // Reset DDR
    Status = MrcResetSequence (MrcData);

    // Run CPGC until both channels fail or we finish all Vref points
    if (SkipVref) {
      ChError = RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);
    } else {
      ChError = 0;
      for (Vloop = 0; Vloop < VoltageLoopCount; Vloop++) {
        Vref = VrefOffsets[Vloop];
        ChangeMargin (MrcData, CmdV, Vref, 0, 1, 0, 0, 0, 0, 0, 0);

        ChError |= RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);

        if (ChError == chBitMask) {
          break;
        }
      }
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n %d\t\t", LCTDelay);

    // Update Passing Variables
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask = MRC_BIT0 << Channel;
      if (!(ChannelMask & chBitMask)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, (Channel == 0) ? "  " : "");
        continue;
      }

      Pass = !(ChError & ChannelMask);

      MRC_DEBUG_MSG (Debug, DebugLevel, Pass ? ". " : "# ");

      IPStart = &InitialPassingStart[Channel];
      IPEnd   = &InitialPassingEnd[Channel];
      CPStart = &CurrentPassingStart[Channel];
      CPEnd   = &CurrentPassingEnd[Channel];
      LPStart = &LargestPassingStart[Channel];
      LPEnd   = &LargestPassingEnd[Channel];

      if (LCTDelay == (INT16) Low) {
        if (Pass) {
          *IPStart = *IPEnd = *CPStart = *CPEnd = *LPStart = *LPEnd = Low;
        } else {
          *IPStart = *IPEnd = *CPStart = *CPEnd = *LPStart = *LPEnd = Low - LCTStep;
        }
      } else {
        if (Pass) {
          // Update Initial variables
          if (*IPEnd == (LCTDelay - LCTStep)) {
            *IPEnd = LCTDelay; // In passing region
          }

          // Update Current variables
          if (*CPEnd == (LCTDelay - LCTStep)) {
            *CPEnd = LCTDelay; // In passing region
          } else {
            *CPStart = *CPEnd = LCTDelay;
          }

          // Special case for last step: Append Initial Passing Region
          // LCTDelay should be considered a continuous range that wraps around 0
          LastStep = High - LCTStep;
          if ((LCTDelay >= LastStep) && (*IPStart == Low) && WrapAllowed) {
            iWidth = *IPEnd -*IPStart;
            *CPEnd += (LCTStep + iWidth);
          }

          // Update Largest variables
          cWidth = *CPEnd - *CPStart;
          lWidth = *LPEnd - *LPStart;
          if (cWidth > lWidth) {
            *LPStart = *CPStart;
            *LPEnd   = *CPEnd;
          }
        }
      }
    } // for Channel
  } // for LCTDelay

  MRC_DEBUG_MSG (Debug, DebugLevel, "\nCH\tLeft\tRight\tWidth\tCenter\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MRC_BIT0 << Channel) & chBitMask) {
      LPStart = &LargestPassingStart[Channel];
      LPEnd   = &LargestPassingEnd[Channel];
      lWidth  = *LPEnd - *LPStart;
      Center = (*LPEnd + *LPStart) / 2;
      if ((lWidth < (3 * LCTStep)) || (lWidth >= (High - Low))) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\nERROR! Bad command eye width: %u\n", lWidth);
        if (lWidth == 0) {
          *LPStart = *LPEnd = 0;
        }
        if (Inputs->ExitOnFailure) {
          return mrcMiscTrainingError;
        }
      }
      RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
      if (!SkipPrint) {
        // Shift Timing
        ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, GroupMask, Center, 1);

        MRC_DEBUG_MSG (
          Debug,
          DebugLevel,
          " %d\t%d\t%d\t%d\t%d\n",
          Channel,
          *LPStart,
          *LPEnd,
          lWidth,
          Center
          );
      }

      // Determine in which rank to save the margins...
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & RankMask) {
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] = 10 * ABS (*LPStart);
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] = 10 * ABS (*LPEnd);
        }
      }
    }
  }

  // Clean Up
  if (!SkipVref) {
    ChangeMargin (MrcData, CmdV, 0, 1, 0, 0, 0, 0, 0, 0, 0);
  }

  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  Use a binary search to find the edge between Low and High
  High and Low track passing points
  if CountUp: Low is a passing point and need to count up to find a failing point
  if CountDn: High is a passing point and need to count dn to find a failing point

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in, out] Low         - Low limit
  @param[in, out] High        - High limit
  @param[in]      CountUp     - The direction to search
  @param[in]      VrefOffsets - Array of Vref offsets

  @retval Nothing
**/
void
CmdBinaryFindEdge (
  IN     MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN OUT UINT8                *Low,
  IN OUT UINT8                *High,
  IN     UINT8                CountUp,
  IN     INT8                 *VrefOffsets
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  UINT8             Target[MAX_CHANNEL];
  UINT8             Done;
  UINT8             ChError;
  INT8              Vref;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             RankMask;
  UINT8             Group;
  UINT8             Fail;
  UINT8             Vloop;
  UINT8             VoltageLoopCount;
  BOOLEAN           SkipWait;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Done          = 0;
  ChError       = 0;
  MrcCall->MrcSetMem (Target, sizeof (Target), 0);

  SkipWait          = FALSE;
  VoltageLoopCount  = 2;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Pi Delay\n");
  while (!Done) {
    // Update Timing
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChBitMask) {
        Target[Channel] = (High[Channel] + Low[Channel] + CountUp) / 2;    // CountUp gets rounding correct
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Channel == 1) && (ChBitMask > 1)) ? "/%d" : "%d", Target[Channel]);
        RankMask = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
        for (Group = 0; Group < MAX_COMMAND_GROUPS; Group++) {
          if ((1 << Group) & GroupMask) {
            ShiftPIforCmdTraining (MrcData, Channel, Iteration, RankMask, 1 << Group, Target[Channel], 0);
          }
        }
      }
    }

    // Run CPGC until both channels fail or we finish all Vref points
    ChError = 0;
    for (Vloop = 0; Vloop < VoltageLoopCount; Vloop++) {
      Vref = VrefOffsets[Vloop];
      ChangeMargin (MrcData, CmdV, Vref, 0, 1, 0, 0, 0, 0, 0, SkipWait);
      ChError |= RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);
      if (ChError == ChBitMask) {
        break;
      }
    }

    // Update High/Low
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask = 1 << Channel;
      if (ChannelMask & ChBitMask) {
        Fail = (ChError & ChannelMask);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Fail ? "\t#" : "\t.");

        // Skip if this channel is done
        if (High[Channel] > Low[Channel]) {
          if (CountUp) {
            if (Fail) {
              High[Channel] = Target[Channel] - 1;
            } else {
              Low[Channel] = Target[Channel];
            }
          } else {
            if (Fail) {
              Low[Channel] = Target[Channel] + 1;
            } else {
              High[Channel] = Target[Channel];
            }
          }
        }
      }
    }

    if ((ChError & ChBitMask) != 0) {
      // Perform JEDEC Reset/Init if at least one of the channels failed this PI iteration
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Failed, doing JEDEC Reset..\n");
      MrcResetSequence (MrcData);
    }

    // Update Done
    Done = 1;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChBitMask) {
        if (High[Channel] > Low[Channel]) {
          Done = 0;
        }
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  // Clean Up
  ChangeMargin (MrcData, CmdV, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  MrcResetSequence (MrcData);
  return;
}

/**
  Shift the CLK/CMD/CTL Timing by the given PI setting value
  CLK shift will also change RcvEn / TxDq / TxDqs.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Channel to shift
  @param[in] Offset     - Offset to shift by

  @retval Nothing
**/
void
ShiftChannelTiming (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN INT32                Offset
  )
{
  MrcDebug            *Debug;
  const MrcInput      *Inputs;
  const MrcChannelIn  *ChannelIn;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  INT32               NewCode;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               Group;
  BOOLEAN             Lpddr4;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelIn   = &Inputs->Controller[0].Channel[Channel];
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  IntOutputs  = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntCmdTiming = &IntOutputs->Controller[0].CmdTiming[Channel];
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d new values:\n", Channel);

  Lpddr4 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  // Shift the CLK/CTL Timing
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%sCTL\n", (Lpddr4) ? "" : "CLK\t");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " R%d", Rank);
      RankBit = 1 << Rank;
      NewCode = (INT32) (IntCmdTiming->ClkPiCode[Rank]) + Offset;
      if (!Lpddr4) {
        // CLK is per Rank in DDR4
        if (Inputs->Ddr4DdpSharedClock && (Rank == 1)) { // Clocks are shared, so only shift rank 0
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t--");
        } else {
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankBit, RankBit, Offset, 1);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", NewCode);
        }
      }

      if (!Lpddr4) {  // CTL is per subch in LPDDR4
        NewCode = (INT32) (IntCmdTiming->CtlPiCode[Rank]) + Offset;
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankBit, 0, NewCode, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d\n", NewCode);
      }
    }
  }

  // Shift the CMD Timing
  for (Group = 0; Group < MAX_COMMAND_GROUPS; Group++) {
    NewCode = (INT32) IntCmdTiming->CmdPiCode[Group] + Offset;
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, ChannelOut->ValidRankBitMask, (1 << Group), NewCode, 1);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " New CMD[%d] value = %d\n", Group, NewCode);
  }

  if (Lpddr4) { // CLK is per Group in LPDDR4
    for (Group = 0; Group < 2; Group++) {
      if (ChannelIn->DQByteMap[MrcIterationClock][Group] != 0) {
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, 0, 1 << Group, Offset, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " New CLK%d value = %d\n", Group, IntCmdTiming->ClkPiCode[Group]);
      }
    }
  }

  if (Lpddr4) {  // CTL is per subch in LPDDR4
    for (Group = 0; Group < 2; Group++) {
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, 1 << Group, Offset, 1);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " New CTL%d value = %d\n", Group, IntCmdTiming->CtlPiCode[Group]);
    }
  }
  return;
}

/**
  This function updates Command Mode register, tXP and Roundtrip latency.
  This should only be called for DDR4.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to perform update to
  @param[in]      OldN        - Old N Mode value
  @param[in]      NewN        - New N mode value

  @retval Nothing
**/
void
UpdateCmdNTiming (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                OldN,
  IN     UINT8                NewN
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcTiming     *Timing;
  MrcDdrType    DdrType;
  INT64         GetSetVal;
  INT64         CmdStretch;
  INT64         tXP;
  INT64         Diff;
  UINT32        MinVal;
  UINT32        MaxVal;
  UINT8         Rank;
  INT64         EnCmdRate;

  Outputs    = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  Timing     = &ChannelOut->Timing[MrcData->Inputs.MemoryProfile];
  DdrType    = Outputs->DdrType;

  // Update Cmd NMode, till now we ran DDR4 at 3N (Gear1) or 2N (Gear2)
  // Command stretch:
  //   00 - 1N
  //   01 - 2N
  //   10 - 3N
  //   11 - N:1
  if (Timing->NMode == 1) {
    CmdStretch = Outputs->Gear2 ? 0 : 3;  // Use N:1 Mode in Gear1 and 1N mode in Gear2
    EnCmdRate = MrcData->Inputs.EnCmdRate;
    if ((CmdStretch == 3) && (EnCmdRate != 0)) {  // Command rate limit is only valid in N:1 mode
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdGapRatio, WriteCached | GSM_PRINT_VAL, &EnCmdRate);  // This was called Command Rate Limit before
    }
  } else {
    CmdStretch = Timing->NMode - 1;
  }
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdStretch,  WriteCached | PrintValue, &CmdStretch);
  if (CmdStretch == 3) {
    // Set bus_retain_on_n_to_1_bubble when N:1 is used.
    GetSetVal = 1;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccBusRetainOnBubble, WriteNoCache | PrintValue, &GetSetVal);
  }

  // Adjust tXP value - it depends on NMode
  // No frequency switching in DDR4 so we use Outputs->Frequency always.
  tXP     = tXPValue (DdrType, Outputs->Frequency, Timing->tCK, (UINT8) Timing->NMode);
  MinVal  = tXP_MIN;
  MaxVal  = tXP_MAX;
  tXP     = RANGE (tXP, MinVal, MaxVal);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctXP, WriteCached | GSM_PRINT_VAL, &tXP);

  // Adjust Roundtrip Latency and RxFIFO - it depends on NMode
  Diff = (NewN - OldN);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, Rank, RoundTripDelay, WriteOffsetCached | PrintValue, &Diff);
    }
  }
}

/**
  Force CKE values per rank.

  @param[in] MrcData      - MRC global data.
  @param[in] ChannelMask  - Bitmask of channels to work on.
  @param[in] CkeValue     - Bitmask of CKE values per rank. Bit0 = CKE0, Bit1 = CKE1 etc.

**/
VOID
MrcForceCkeValue (
  IN MrcParameters *const MrcData,
  IN UINT32               ChannelMask,
  IN INT64                CkeValue
  )
{
  INT64   ValidCkeMask;
  UINT32  Channel;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChannelMask) {
      ValidCkeMask = MrcData->Outputs.Controller[0].Channel[Channel].ValidCkeBitMask;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOverride,  WriteNoCache, &ValidCkeMask);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn,        WriteNoCache, &CkeValue);
    }
  }
}

//
//  Sets up 4 CADB lines that will be used to send out a CS / CA pattern for LPDDR4.
//
//  -----------------------
//  CADB  Phase  Phase  CS
//  Line  High   Low
//        (Sch1) (Sch0)
//  -----------------------
//   0    0x00   0x00  Off
//   1    0x3F   0x3F  Off
//   2    0x2A   0x2A  On
//   3    0x15   0x15  On
//
//  The CS pattern uses Pattern Buffer and has 32 lines on ICL (CADB 2.1), with CS active for one line only.
//  This will send a command every 32 DCLKs.
//
//  Pattern Buffer details:
//  The line order is:    0, 0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//  or different command: 0, 0, 0, 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//
//  000
//  000
//  000
//  000
//
//  010 or 011
//  001
//  001
//  001

//  001
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000
//
//  000
//  000
//  000
//  000

//  ----
//  000        --> PB[0] = 0x000001E0 or 0x000001F0
//  01E or 01F     PB[1] = 0x00000010
//  001            PB[2] = 0x00000000
//  000
//  000
//  000
//  000
//  000
//

CADB_LINE CadbLinesCsLp4[] = {
  { 0x00, 0x00, 0 },
  { 0x3F, 0x3F, 0 },
  { 0x2A, 0x2A, 1 },
  { 0x15, 0x15, 1 }
};

UINT32 CadbMuxLp4Pattern2[] = {
  0x000001E0,
  0x00000010,
  0x00000000
};

UINT32 CadbMuxLp4Pattern3[] = {
  0x000001F0,
  0x00000010,
  0x00000000
};

//
//  Sets up 8 CADB lines that will be used to send out a CS / CA pattern.
//
//  -----------------------
//  CADB  Phase  Phase  CS
//  Line  High   Low
//  -----------------------
//   0    0x111  0x111  Off
//   1    0x222  0x222  On
//   2    0x333  0x333  Off
//   3    0x444  0x444  Off
//   4    0x555  0x555  Off
//   5    0x666  0x666  Off
//   6    0x777  0x777  Off
//   7    0x888  0x888  Off
//
//
//  The CS pattern uses Pattern Buffer and hence has 24 lines, with CS active for one line only.
//  This will send a command every 24 DCLKs.
//
//  Pattern Buffer details:
//  The line order is:    0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7
//  or different command: 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0
//
//  000
//  001
//  010
//  011
//
//  100
//  101
//  110
//  111
//
//  000
//  001
//  010
//  011
//
//  100
//  101
//  110
//  111
//
//  000
//  001
//  010
//  011
//
//  100
//  101
//  110
//  111
//
//  000
//  001
//  010
//  011
//
//  100
//  101
//  110
//  111
//  ----
//  0CA  --> PB[0] = 0xAAAAAAAA
//  FCA      PB[1] = 0xCCCCCCCC
//  0CA      PB[2] = 0xF0F0F0F0
//  FCA
//  0CA
//  FCA
//  0CA
//  FCA
//----------------------------------------------
//
//  111
//  110
//  101
//  100
//
//  011
//  010
//  001
//  000
//
//  111
//  110
//  101
//  100
//
//  011
//  010
//  001
//  000
//
//  111
//  110
//  101
//  100
//
//  011
//  010
//  001
//  000
//-----
//  F35  --> PB[0] = 0x555555
//  035      PB[1] = 0x333333
//  F35      PB[2] = 0x0F0F0F
//  035
//  F35
//  035
/*
CADB_LINE CadbLinesTest[] = {
  { 0x11, 0x11, 0 },
  { 0x22, 0x22, 1 },
  { 0x33, 0x33, 0 },
  { 0x44, 0x44, 0 },
  { 0x55, 0x55, 0 },
  { 0x66, 0x66, 0 },
  { 0x77, 0x77, 0 },
  { 0x88, 0x88, 0 }
};

UINT32 CadbMuxPattern2Test[] = {
  0xAAAAAAAA,
  0xCCCCCCCC,
  0xF0F0F0F0
};

UINT32 CadbMuxPattern3Test[] = {
  0x555555,
  0x333333,
  0x0F0F0F
};
*/

/**
  Setup the CADB for CS or CA training.

  @param[in] MrcData    - The MRC global data.
  @param[in] Channel    - channel to work on
  @param[in] Rank       - rank to work on
  @param[in] CadbLines  - CADB lines to program
  @param[in] CadbCount  - Number of CADB lines to program
  @param[in] PatBuf     - Pattern buffer array.
**/
void
SetupCaTrainingCadb (
  IN MrcParameters  *const  MrcData,
  IN UINT8          Channel,
  IN UINT8          Rank,
  IN CADB_LINE      *CadbLines,
  IN UINT32         CadbCount,
  IN UINT32         PatBuf[MRC_NUM_MUX_SEEDS]
  )
{
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  const MRC_FUNCTION  *MrcCall;
  UINT32              i;
  UINT8               Cke[2];
  UINT8               Cs[2];
  UINT8               Odt;
  MRC_CA_MAP_TYPE     LpddrCmdAddr;
  UINT64_STRUCT       LpddrCadbPatternChunks[CADB_20_MAX_CHUNKS];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  MrcCall = Inputs->Call.Func;

  Odt = 0;
  MrcCall->MrcSetMem ((UINT8 *) Cke, sizeof (Cke), 0);
  MrcCall->MrcSetMem ((UINT8 *) Cs, sizeof (Cs), 0);
  MrcCall->MrcSetMem ((UINT8 *) LpddrCadbPatternChunks, sizeof (LpddrCadbPatternChunks), 0);

  MrcSelectEngines (MrcData, 0, 1 << Channel, ChannelOut->ValidSubChBitMask);

  for (i = 0; i < CadbCount; i++) {
    LpddrCmdAddr.Data32 = 0;
    Cs[0] = Cs[1] = (CadbLines[i].ChipSelect << Rank);
    LpddrCmdAddr.Lpddr4.Ca1 = CadbLines[i].CaLow;   // SubCh 0
    LpddrCmdAddr.Lpddr4.Ca2 = CadbLines[i].CaHigh;  // SubCh 1
    CpgcConvertDdrToCadb (MrcData, &LpddrCmdAddr, Cke, Cs, Odt, &LpddrCadbPatternChunks[i]);
  }

  // Program CADB Pattern Generator
  MrcSetCadbPgPattern (MrcData, LpddrCadbPatternChunks, CadbCount, 0);

  // Set Mux0/1/2 to Pattern Buffer mode (LFSR size is ignored)
  Cadb20UniseqCfg (MrcData, MrcPgMuxPatBuffer, MrcLfsr8);

  // Program Pattern Buffers for a specific progression over CADB,
  // according to the given Pattern Buffer values
  MrcInitCadbPgMux (MrcData, PatBuf, 0, MRC_NUM_MUX_SEEDS);
}

/**
  Program DESWIZZLE_HIGH/LOW registers for MR4 decoding on LP3/LP4
  Program DESWIZZLE_RANKPAIR registers for MR18/MR19 decoding on LP4

  @param[in] MrcData - The MRC global data.

**/
void
ProgramDeswizzleRegisters (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                      *Inputs;
  MrcDebug                                      *Debug;
  MrcOutput                                     *Outputs;
  MrcChannelIn                                  *ChannelIn;
  MrcChannelOut                                 *ChannelOut;
  MrcControllerOut                              *ControllerOut;
  UINT8                                         Channel;
  UINT8                                         SubCh;
  UINT8                                         Rank;
  UINT8                                         MaxDevice;
  UINT8                                         Device;
  UINT32                                        DeviceVal;
  UINT8                                         DevWidth;
  UINT32                                        Byte;
  UINT8                                         Bit;
  UINT32                                        Offset;
  UINT32                                        Offset1;
  UINT32                                        DevPosition;
  CH0_CR_DESWIZZLE_LOW_STRUCT                   DeswizzleLow;
  CH0_CR_DESWIZZLE_HIGH_STRUCT                  DeswizzleHigh;
  MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_STRUCT     Deswizzle;
  MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_STRUCT      DqsDevUseMap;
  MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_STRUCT_A0   DqsDevUseMapA0;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  MaxDevice = (Outputs->Lp4x8 ? 4 : 2);
  DevWidth  = (4 / MaxDevice);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &Inputs->Controller[0].Channel[Channel];
    ChannelOut = &ControllerOut->Channel[Channel];

    DeswizzleLow.Data   = 0;
    DeswizzleHigh.Data  = 0;

    for (Byte = 0; Byte <= 7; Byte++) {
      // DqsMapCpu2Dram maps CPU bytes to DRAM, we need to find the reverse mapping here
      switch (ChannelIn->DqsMapCpu2Dram[Byte]) {
        case 0:
          DeswizzleLow.Bits.Byte_0  = Byte;
          break;
        case 2:
          DeswizzleLow.Bits.Byte_2  = Byte;
          break;
        case 4:
          DeswizzleHigh.Bits.Byte_4 = Byte;
          break;
        case 6:
          DeswizzleHigh.Bits.Byte_6 = Byte;
          break;
      }
    }

    for (Bit = 0; Bit <= 7; Bit++) {
      // DqMapCpu2Dram maps CPU DQ pins to DRAM, we need to find the reverse mapping here
      Byte = DeswizzleLow.Bits.Byte_0;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 0:
          DeswizzleLow.Bits.Bit_0 = Bit;
          break;
        case 1:
          DeswizzleLow.Bits.Bit_1 = Bit;
          break;
        case 2:
          DeswizzleLow.Bits.Bit_2 = Bit;
          break;
      }

      Byte = DeswizzleLow.Bits.Byte_2;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 16:
          DeswizzleLow.Bits.Bit_16 = Bit;
          break;
        case 17:
          DeswizzleLow.Bits.Bit_17 = Bit;
          break;
        case 18:
          DeswizzleLow.Bits.Bit_18 = Bit;
          break;
      }

      Byte = DeswizzleHigh.Bits.Byte_4;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 32:
          DeswizzleHigh.Bits.Bit_32 = Bit;
          break;
        case 33:
          DeswizzleHigh.Bits.Bit_33 = Bit;
          break;
        case 34:
          DeswizzleHigh.Bits.Bit_34 = Bit;
          break;
      }

      Byte = DeswizzleHigh.Bits.Byte_6;
      switch (ChannelIn->DqMapCpu2Dram[Byte][Bit]) {
        case 48:
          DeswizzleHigh.Bits.Bit_48 = Bit;
          break;
        case 49:
          DeswizzleHigh.Bits.Bit_49 = Bit;
          break;
        case 50:
          DeswizzleHigh.Bits.Bit_50 = Bit;
          break;
      }
    } // for Bit

    Offset = CH0_CR_DESWIZZLE_LOW_REG +
      (CH1_CR_DESWIZZLE_LOW_REG - CH0_CR_DESWIZZLE_LOW_REG) * Channel;
    MrcWriteCR (MrcData, Offset, DeswizzleLow.Data);

    Offset = CH0_CR_DESWIZZLE_HIGH_REG +
      (CH1_CR_DESWIZZLE_HIGH_REG - CH0_CR_DESWIZZLE_HIGH_REG) * Channel;
    MrcWriteCR (MrcData, Offset, DeswizzleHigh.Data);

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Ch%d DESWIZZLE_HIGH=0x%08X, DESWIZZLE_LOW=0x%08X\n",
      Channel,
      DeswizzleHigh.Data,
      DeswizzleLow.Data
      );

    Offset = CH0_CR_DESWIZZLE_LOW_ERM_REG + (CH1_CR_DESWIZZLE_LOW_ERM_REG - CH0_CR_DESWIZZLE_LOW_ERM_REG) * Channel;
    MrcWriteCR(MrcData, Offset, DeswizzleLow.Data);
    Offset = CH0_CR_DESWIZZLE_HIGH_ERM_REG + (CH1_CR_DESWIZZLE_HIGH_ERM_REG - CH0_CR_DESWIZZLE_HIGH_ERM_REG) * Channel;
    MrcWriteCR(MrcData, Offset, DeswizzleHigh.Data);

    if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        // Map the CPU bytes to the DRAM devices for Delta DQS
        Offset = MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_REG +
                  ((MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_REG - MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_REG) * SubCh) +
                  ((MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_REG - MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_REG) * Channel);
        DqsDevUseMap.Data   = 0;
        DqsDevUseMapA0.Data = 0;
        DevPosition         = 0;
        for (Byte = ChannelOut->ByteStart[SubCh]; Byte <= ChannelOut->ByteEnd[SubCh]; Byte++) {
          // Dram device pointed from cpu byte
          Device = ((ChannelIn->DqsMapCpu2Dram[Byte] / DevWidth) & (MaxDevice - 1));
          // Bit position of the device for each sub channel byte
          DevPosition = (Byte % 4);
          //Devuse register has 2 bits per Byte since ICL B, instead of 1
          if (!Inputs->IclA0) {
            DevPosition *= 2;
          }
          DeviceVal = Device << DevPosition;
          // Same value for all ranks in the Sub Channel
          if (!Inputs->IclA0) {
            DqsDevUseMap.Bits.DevUseMapRank0 |= DeviceVal;
            DqsDevUseMap.Bits.DevUseMapRank1 |= DeviceVal;
            DqsDevUseMap.Bits.DevUseMapRank2 |= DeviceVal;
            DqsDevUseMap.Bits.DevUseMapRank3 |= DeviceVal;
          }else{
            DqsDevUseMapA0.Bits.DevUseMapRank0 |= DeviceVal;
            DqsDevUseMapA0.Bits.DevUseMapRank1 |= DeviceVal;
            DqsDevUseMapA0.Bits.DevUseMapRank2 |= DeviceVal;
            DqsDevUseMapA0.Bits.DevUseMapRank3 |= DeviceVal;
          }
        }
        MrcWriteCR (MrcData, Offset, (Inputs->IclA0 ? DqsDevUseMapA0.Data : DqsDevUseMap.Data));
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Ch%d SubCh%d Offset=0x%04X DQSDEVUSEMAP=0x%08X\n",
          Channel,
          SubCh,
          Offset,
          DqsDevUseMap.Data
        );

        // Program the Byte/Bit deswizzle information in the DDRIO
        Offset = MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_REG +
                 ((MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_REG - MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_REG) * (SubCh + (Channel * 2)));
        for (Device = 0; Device < MaxDevice; Device++) {
          if (Device == 2) {
            Offset += (MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_REG - MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_REG);
          }
          Offset += ((MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_REG - MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_REG) * (Device & 1));
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
            if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
              continue;
            }
            Offset1 = (Rank == 0) ? Offset : (Offset + (MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_REG - MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_REG));
            Deswizzle.Data = 0;
            for (Byte = ChannelOut->ByteStart[SubCh]; Byte <= ChannelOut->ByteEnd[SubCh]; Byte++) {
              // DqsMapCpu2Dram maps CPU bytes to DRAM, we need to find the reverse mapping here
              if ((ChannelIn->DqsMapCpu2Dram[Byte] % 4) == (Device * DevWidth)) {
                Deswizzle.Bits.DeSwizzleByte = (Byte % 4);
                break;
              }
            }
            for (Bit = 0; Bit <= 7; Bit++) {
              // DqMapCpu2Dram maps CPU DQ pins to DRAM, we need to find the reverse mapping here
              switch (ChannelIn->DqMapCpu2Dram[Byte][Bit] % 8) {
                case 0:
                  Deswizzle.Bits.DeSwizzleLane0 = Bit;
                  break;

                case 1:
                  Deswizzle.Bits.DeSwizzleLane1 = Bit;
                  break;

                case 2:
                  Deswizzle.Bits.DeSwizzleLane2 = Bit;
                  break;

                case 3:
                  Deswizzle.Bits.DeSwizzleLane3 = Bit;
                  break;

                case 4:
                  Deswizzle.Bits.DeSwizzleLane4 = Bit;
                  break;

                case 5:
                  Deswizzle.Bits.DeSwizzleLane5 = Bit;
                  break;

                case 6:
                  Deswizzle.Bits.DeSwizzleLane6 = Bit;
                  break;

                case 7:
                  Deswizzle.Bits.DeSwizzleLane7 = Bit;
                  break;
              } // switch
            } // for Bit
            MrcWriteCR (MrcData, Offset1, Deswizzle.Data);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "Ch%d SubCh%d Dev%d RankPair%d%d DESWIZZLE=0x%08X\n",
              Channel,
              SubCh,
              Device,
              Rank,
              Rank + 1,
              Deswizzle.Data
              );
          } // for Rank
        } // for Device
      } // for SubCh
    } // (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4)
  } // for Channel
}

/**
  This routine is used throughout LPDDR ECT code to initialize DDR IO for CA training.
  Enable the following bits because we will use DATATRAINFEEDBACK to read back CA values on DQ pins:
    DataControl0.SenseampTrainingMode and ForceOdtOn
    DataControl2.ForceRxOn and ForceBiasOn

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingInitIo (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput           *Outputs;
  INT64               GetSetVal;
  UINT8               Channel;

  Outputs           = &MrcData->Outputs;
  GetSetVal         = 1;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,  WriteToCache, &GetSetVal);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,   WriteToCache, &GetSetVal);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
  }
}

/**
  This routine is used throughout LPDDR ECT code to restore DDR IO from CA training.
  The order of HW writes is opposite from LpddrCaTrainingInitIo.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingRestoreIo (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput           *Outputs;
  INT64               GetSetVal;
  UINT8               Channel;

  Outputs           = &MrcData->Outputs;
  GetSetVal         = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,   WriteToCache, &GetSetVal);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,  WriteToCache, &GetSetVal);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
  }
}

/**
  Run the CADB test on all channels / ranks at the current CS/CMD PIs.

  @param[in] MrcData - The MRC global data.

  @retval Bitmask of passing ranks
**/
UINT8
RunEarlyCsCmdTestLpddr (
  IN MrcParameters * const  MrcData
  )
{
  MRC_FUNCTION        *MrcCall;
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcControllerIn     *ControllerIn;
  MrcControllerOut    *ControllerOut;
  MrcChannelIn        *ChannelIn;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MrcStatus           CurStatus;
  BOOLEAN             IgnoreByte;
  CADB_LINE           *CadbLines;
  UINT32              CadbCount;
  UINT32              *PatBuf;
  const UINT32        *Seeds;
  UINT8               Channel;
  UINT8               ChannelMask;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               TermRankMask;
  UINT8               Byte;
  UINT8               ByteMask;
  UINT8               DramByte;
  UINT8               NumOfOnes;
  UINT8               RankPassMask;
  UINT32              ChannelPassMask;
  UINT8               BytePassMask[MAX_CHANNEL];
  UINT32              Feedback[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              DelayCadb;
  UINT32              Offset;
  UINT32              Pattern;
  CHAR8               PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT   DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];
  TermRankMask  = Inputs->CmdRanksTerminated;

  DelayCadb = 1 * MRC_TIMER_1US;

  RankPassMask = 0; // Bitmask of passed ranks
  MrcCall->MrcSetMem ((UINT8 *) BytePassMask, sizeof (BytePassMask), 0);

  CadbLines = CadbLinesCsLp4;
  CadbCount = ARRAY_COUNT (CadbLinesCsLp4);
  PatBuf    = CadbMuxLp4Pattern2;
  NumOfOnes = MrcCountBitsEqOne (CadbLines[2].CaHigh & 0xFF);  // Take the low 8 bits of the pattern

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & Outputs->ValidRankMask) == 0) {
      continue;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      Status = MrcLpddr4SetCbtCaOdtEn (MrcData, TRUE);
      if (Status != mrcSuccess) {
        return Status;
      }
    }


    ChannelPassMask = 0; // Bitmask of passed channels on the current rank
    ChannelMask = 0;     // Bitmask of channels that have current rank populated
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelMask |= (1 << Channel);
      SetupCaTrainingCadb (MrcData, Channel, Rank, CadbLines, CadbCount, PatBuf);
    }  // for Channel

    // Enter CBT Mode for this Rank.
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 1);
    if (Status != mrcSuccess) {
      return Status;
    }

    // Send VrefCA on DQ[6:0]
    MrcSendCaVrefOnDq (MrcData, Rank);

    // Try two different patterns (0x2AA or 0x155), to see if the command is still decoded correctly
    for (Pattern = 0; Pattern <= 1; Pattern++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        MrcSelectEngines (MrcData, 0, 1 << Channel, ChannelOut->ValidSubChBitMask);
        Seeds = (Pattern == 0) ? CadbMuxLp4Pattern2 : CadbMuxLp4Pattern3;
        MrcInitCadbPgMux (MrcData, Seeds, 0, MRC_NUM_MUX_SEEDS);
      }
      // Run CADB pattern on selected channels at the same time
      ShortRunCADB (MrcData, ChannelMask);
      MrcWait (MrcData, DelayCadb);

      // Read and process the results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Pattern == 1) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
          }
          continue;
        }
        ChannelIn  = &ControllerIn->Channel[Channel];
        ChannelOut = &ControllerOut->Channel[Channel];
        BytePassMask[Channel] = 0;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          IgnoreByte = FALSE;
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            IgnoreByte = TRUE;
          }
          if ((DramByte & 1) == 0) { // Ignore DRAM bytes 0, 2, 4 and 6 - they don't provide feedback
            IgnoreByte = TRUE;
          }
          if (IgnoreByte) {
            BytePassMask[Channel] |= ByteMask;
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data = MrcReadCR (MrcData, Offset) & 0xFF;  // Get only DQ bits, not DQS
          if (Pattern == 0) {
            Feedback[Channel][Byte] = DataTrainFeedback.Data; // Save the first pattern
          } else {
            // Second Pattern
            // If still read the same data, then DRAM was not able to decode the new command
            if ((Feedback[Channel][Byte] != DataTrainFeedback.Data) &&
                (MrcCountBitsEqOne (DataTrainFeedback.Data) == NumOfOnes)) {
              BytePassMask[Channel] |= ByteMask;
            }
          }
        }  // for Byte
        if (Pattern == 1) {
          if (BytePassMask[Channel] == 0xFF) { // If all bytes on a channel passed, mark this channel as passed.
            ChannelPassMask |= (1 << Channel);
            PassFail = '.';
          } else {
            PassFail = '#';
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%02X", PassFail, BytePassMask[Channel]);
        }
      }  // for Channel
    } // for Pattern
    if (ChannelPassMask == ChannelMask) {
      RankPassMask |= RankBit; // If all channels passed, mark this rank as passed
    }

    // Exit CA training mode on the current rank
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 0);
    if ((RankBit & TermRankMask) == 0) {
      // Disable Termination on the terminated rank via FSP-High
      CurStatus = MrcLpddr4SetCbtCaOdtEn (MrcData, FALSE);
      if (Status == mrcSuccess) {
        Status = CurStatus;
      }
    }
    if (Status != mrcSuccess) {
      return Status;
    }
  } // for Rank

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  return RankPassMask;
}

/**
  Find a good starting point for LPDDR4 CMD/CS, using a quick 2D search.
  CLK is being kept at default (64).
  Start from ideal theoretical point: CS=64, CMD=64 (LPDDR4).
  Sweep CS with a step of 16 PI ticks.
  Sweep CMD with a step of 16 PI ticks, and look for 3 consecutive passing points.
  The CMD eye in ECT stress is about 60 ticks, so we can always find such 3 points.
  Run CS training CADB pattern to robustly catch CS/CMD errors.
  Stop when a PASS found on all channels/ranks.
  Select the middle of the three CMD passing points.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCsCmdLpddr (
  IN MrcParameters *const MrcData
  )
{
  MRC_FUNCTION        *MrcCall;
  MrcInput            *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               RankMask;
  UINT8               RankPassMask;
  UINT8               GroupMask;
  UINT8               CaPiCode;
  UINT8               CsPiCode;
  UINT32              CaPiCodePass[3];
  UINT32              CsPiCodePass[3];
  UINT8               CaPassIndex;
  UINT8               CsPassIndex;
  UINT32              CsPiIndex;
  UINT32              CaPiIndex;
  const UINT8         *CaPiTable;
  static const UINT8  CsPiTable[]    = { 64, 48, 32, 16, 0, 112, 96, 80 };

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  RankMask = Outputs->ValidRankMask;
  CsPiCode = 0;
  CaPiCode = 0;
  CaPassIndex = 0;
  CsPassIndex = 0;
  RankPassMask = 0; // Bitmask of passed ranks
  MrcCall->MrcSetMem ((UINT8 *) CaPiCodePass, sizeof (CaPiCodePass), 0);
  MrcCall->MrcSetMem ((UINT8 *) CsPiCodePass, sizeof (CsPiCodePass), 0);

  // Init DDR IO for CA training
  CaPiTable = CsPiTable;
  GroupMask = 3;  // CTL PI is per subch

  Lpddr4CaTrainingInitIo (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Early CS/CMD 2D search\n\t\tR0C0\tR0C1\tR1C0\tR1C1\n");

  for (CsPiIndex = 0; CsPiIndex < ARRAY_COUNT (CsPiTable); CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\n", CsPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      // Shift the CS PI on all ranks, keep the value in the host struct.
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, GroupMask, CsPiCode, 1);
    }

    CaPassIndex = 0;            // Restart search for 3 passing CMD points
    for (CaPiIndex = 0; CaPiIndex < ARRAY_COUNT (CsPiTable); CaPiIndex++) {
      CaPiCode = CaPiTable[CaPiIndex];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD:%d\t", CaPiCode);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        // Shift the Command PI on both CAA and CAB groups; RankMask is not relevant for CMD/CKE.
        // Keep the value in the host struct.
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, 0x1F, CaPiCode, 1);
      }

      RankPassMask = RunEarlyCsCmdTestLpddr (MrcData); // Run the test on all channels / ranks at the current CS/CMD PIs

      if (RankPassMask == RankMask) {           // If all ranks passed, we are done for this PI
        CaPiCodePass[CaPassIndex] = CaPiCode;   // Store passing CMD PI code
        CaPassIndex++;
        if (CaPassIndex > 2) {                  // Do we have 3 passing CA points ?
          break;
        }
      }
    } // for CMD PI
    if (RankPassMask == RankMask) { // If all ranks passed, we are done
      if (CaPassIndex > 2) {        // Do we have 3 passing CA points ?
        break;
      }
    }
  }  // for CS PI

  if (RankPassMask != RankMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: cannot find a working starting point for CS/CMD for all channels/ranks\n");
    return mrcFail;
  }

  MrcBsort (CaPiCodePass, ARRAY_COUNT (CaPiCodePass));  // Sort the array, because the passing range might wrap around
  CaPiCode = (UINT8) CaPiCodePass[1];                   // Select the middle code out of three.

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    // Shift the Command PI on both CAA and CAB groups, keep the value in the host struct.
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, 0x1F, CaPiCode, 1);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  // Now let's find 3 passing CS points at this CMD point
  for (CsPiIndex = 0; CsPiIndex < ARRAY_COUNT (CsPiTable); CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\t", CsPiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      // Shift the CS PI on all ranks, keep the value in the host struct.
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, GroupMask, CsPiCode, 1);
    }

    RankPassMask = RunEarlyCsCmdTestLpddr (MrcData); // Run the test on all channels / ranks at the current CS/CMD PIs

    if (RankPassMask == RankMask) {           // If all ranks passed, we are done for this PI
      CsPiCodePass[CsPassIndex] = CsPiCode;   // Store passing CS PI code
      CsPassIndex++;
      if (CsPassIndex > 2) {                  // Do we have 3 passing CS points ?
        break;
      }
    }
  } // for CS PI

  if (RankPassMask != RankMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: cannot find a working starting point for CS/CMD for all channels/ranks\n");
    return mrcFail;
  }

  MrcBsort (CsPiCodePass, ARRAY_COUNT (CsPiCodePass));  // Sort the array, because the passing range might wrap around
  CsPiCode = (UINT8) CsPiCodePass[1];                   // Select the middle code out of three.

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Shift the CS PI on all ranks, keep the value in the host struct.
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, GroupMask, CsPiCode, 1);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Final selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  // Restore DDR IO values that were used for CA training
  Lpddr4CaTrainingRestoreIo (MrcData);

  return Status;
}

/**
  Sweep CMD PI up or down and find edges for all bytes.
  Main flow:
  1.
  2.
  3.

  @param[in] MrcData - The MRC global data.

**/
void
EarlyCaFindEdge (
  IN MrcParameters *const   MrcData,
  UINT8                     Rank,
  UINT8                     Start,
  UINT8                     Stop,
  INT8                      Step,
  UINT8                     Limit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerIn   *ControllerIn;
  MrcChannelIn      *ChannelIn;
  CADB_LINE         *CadbLines;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             Byte;
  UINT8             ByteMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CHANNEL];
  UINT8             PiCode;
  UINT8             NumOfOnes;
  UINT32            DelayCadb;
  UINT32            Offset;
  UINT32            Repeat;
  UINT32            Loopcount;
  BOOLEAN           Done;
  BOOLEAN           Lpddr4;
  BOOLEAN           IgnoreByte;
  char              *BytesHeader;
  char              PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  DelayCadb = 1 * MRC_TIMER_1US;
  Loopcount = 10;

  MrcCall->MrcSetMem (ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode  = Start;
  Done    = FALSE;
  CadbLines = CadbLinesCsLp4;
  NumOfOnes = MrcCountBitsEqOne (CadbLines[2].CaHigh & 0xFF);  // Take the low 8 bits of the pattern

  ChannelMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      ChannelMask |= (1 << Channel);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Ch0\t\t\t\t   Ch1\n");
  BytesHeader = "0   1   2   3   4   5   6   7     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD PI\t%s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d: \t", PiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      // Shift the Command PI on both CAA and CAB groups
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 1 << Rank, 0x1F, PiCode, 0);
    }

    for (Repeat = 0; Repeat < Loopcount; Repeat++) {
      // Run CADB pattern on selected channels at the same time
      ShortRunCADB (MrcData, ChannelMask);
      MrcWait (MrcData, DelayCadb);

      // Read and process the results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          ByteDoneMask[Channel] = 0xFF;
          continue;
        }
        if (ByteDoneMask[Channel] == 0xFF) { // All bytes failed on this channel, no need to sweep anymore
          continue;
        }
        ChannelIn = &ControllerIn->Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          IgnoreByte = FALSE;
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            IgnoreByte = TRUE;
          }
          if (Lpddr4) {
            if (((DramByte & 1) == 0) && !Outputs->Lp4x8) {
              // Ignore DRAM bytes 0, 2, 4 and 6 on x16 devices - they don't provide feedback
              // Byte mode parts provide feedback on all bytes
              IgnoreByte = TRUE;
            }
          }
          if (IgnoreByte) {
            ByteDoneMask[Channel] |= ByteMask;
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data = (MrcReadCR (MrcData, Offset) & 0xFF);  // Get only DQ bits, not DQS

          if ((ByteDoneMask[Channel] & ByteMask) == 0) {
            // If we don't see 4 ones in the byte, then the command was not aligned properly
            if (MrcCountBitsEqOne (DataTrainFeedback.Data) != NumOfOnes) {
              Limit[Channel][Rank][Byte] = PiCode;
              ByteDoneMask[Channel] |= ByteMask;
            }
          }
        }  // for Byte
      }  // for Channel
      if ((ByteDoneMask[0] == 0xFF) && (ByteDoneMask[1] == 0xFF)) {
        // Found the limit on all bytes on both channels - no need to repeat the stress any longer
        break;
      }
    } // Repeat
    // Print the accumulated results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
        continue;
      }
      ChannelIn = &ControllerIn->Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        ByteMask = (1 << Byte);
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        IgnoreByte = FALSE;
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          IgnoreByte = TRUE;
        }
        if (Lpddr4) {
          if (((DramByte & 1) == 0) && !Outputs->Lp4x8) {
            // Ignore DRAM bytes 0, 2, 4 and 6 on x16 devices - they don't provide feedback
            // Byte mode parts provide feedback on all bytes
            IgnoreByte = TRUE;
          }
        }
        if (IgnoreByte) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
          continue;
        }
        PassFail = '.';
        if ((ByteDoneMask[Channel] & ByteMask) != 0) {
          // Check if this byte failed on this PiCode (or before)
          if (((Step > 0 ) && (Limit[Channel][Rank][Byte] <= PiCode)) ||
              ((Step < 0 ) && (Limit[Channel][Rank][Byte] >= PiCode))) {
            PassFail = '#';
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c   ", PassFail);
      }  // for Byte
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
    } // Channel

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    if ((ByteDoneMask[0] == 0xFF) && (ByteDoneMask[1] == 0xFF)) {
      // Found the limit on all bytes on both channels - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT8) PiCode) < Stop);
    }
  }  // while not done
}

/**
  Process the results of the early LPDDR4 CMD training and find the best PI settings for CAA/CAB.
  Flow:
   1. Find the worst case Right and Left limits for each channel
   2. Find the Center for each channel

  @param[in]  MrcData     - The MRC global data.
  @param[in]  LeftLimit   - array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - array of best CMD PI settings, per channel

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCmdPi (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  OUT UINT8                 BestCmd[MAX_CHANNEL][2]    // per Channel and per group (CAA and CAB)
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  MrcChannelIn      *ChannelIn;
  MrcControllerIn   *ControllerIn;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             CaGroup;
  UINT8             CmdLeftLimit[MAX_CHANNEL][2];  // Per ch and group
  UINT8             CmdRightLimit[MAX_CHANNEL][2]; // Per ch and group

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];

  Status = mrcSuccess;

  MrcCall->MrcSetMem ((UINT8 *) CmdRightLimit, sizeof (CmdRightLimit), 127);
  MrcCall->MrcSetMem ((UINT8 *) CmdLeftLimit, sizeof (CmdLeftLimit), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CMD PIs:\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &ControllerIn->Channel[Channel];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel: %d\t\tLeft\tRight\tCenter\n", Channel);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      // Find the worst case Right and Left limits for all ranks, for bytes from the particular CA group
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if ((1 << Byte) & ChannelIn->DQByteMap[MrcIterationCmd][0]) {
          CaGroup = 0;
        } else {
          CaGroup = 1;
        }
        CmdRightLimit[Channel][CaGroup] = MIN (CmdRightLimit[Channel][CaGroup], RightLimit[Channel][Rank][Byte]);
        CmdLeftLimit[Channel][CaGroup]  = MAX (CmdLeftLimit[Channel][CaGroup], LeftLimit[Channel][Rank][Byte]);
      }
    } // for Rank

    // Find the Center for each group, worst case of all ranks
    BestCmd[Channel][0] = (CmdRightLimit[Channel][0] + CmdLeftLimit[Channel][0]) / 2;
    BestCmd[Channel][1] = (CmdRightLimit[Channel][1] + CmdLeftLimit[Channel][1]) / 2;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CA%c\t\t\t%d\t%d\t%d\n",
      'A',
      CmdLeftLimit[Channel][0],
      CmdRightLimit[Channel][0],
      BestCmd[Channel][0]
      );

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CA%c\t\t\t%d\t%d\t%d\n",
      'B',
      CmdLeftLimit[Channel][1],
      CmdRightLimit[Channel][1],
      BestCmd[Channel][1]
      );
  } // for Channel

  return Status;
}

/**
  Update DqMapCpu2Dram array

  @param[in] MrcData  - The MRC global data.
  @param[in] Channel  - the channel to work on
  @param[in] Feedback - array of DATATRAINFEEDBACK values for all 8 bytes
  @param[in] Bit      - The DQ bit that should be set in each DRAM byte

  @retval mrcSuccess if succeeded
**/
MrcStatus
FillCA2DQMapResult (
  IN OUT MrcParameters *const   MrcData,
  IN const UINT8                Channel,
  IN const UINT8                Feedback[8],
  IN const UINT8                Bit
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerIn   *ControllerIn;
  MrcChannelIn      *ChannelIn;
  MrcStatus         Status;
  UINT8             Byte;
  UINT8             Temp;
  UINT8             CpuBit;
  INT8              BitNumber;
  BOOLEAN           BitFound;

  Status        = mrcSuccess;
  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  ChannelIn     = &ControllerIn->Channel[Channel];
  BitNumber     = -1;

  // Loop on CPU bytes
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
      continue;
    }
    Temp = Feedback[Byte];
    BitNumber = 0;
    CpuBit    = 0;
    BitFound  = FALSE;
    while (Temp > 0) {
      if (Temp & 1) {
        if (!BitFound) {
          CpuBit = BitNumber;
          BitFound = TRUE;
        } else {
          Status = mrcFail;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Ch%d: ERROR: More than one DQ pin toggled while looking for DQ%d in Byte%d, Feedback=0x%X\n",
            Channel,
            Bit,
            Byte,
            Feedback[Byte]
            );
          break;
        }
      }
      Temp >>= 1;
      BitNumber++;
    }
    if (!BitFound) {
      Status = mrcFail;
    }
    ChannelIn->DqMapCpu2Dram[Byte][CpuBit] = ChannelIn->DqsMapCpu2Dram[Byte] * 8 + Bit;
  } // for Byte

  return Status;
}

/**
  Rotate a given number left by a specified number of bits.

  @param[in] Value      - The input value
  @param[in] BitLength  - How many bits to rotate in the input value. Should be >1 and <32, tested for 16
  @param[in] RotateBy   - Number of bits to rotate by.

  @retval The rotated number
**/
UINT32
RotateLeft (
  IN const UINT32 Value,
  IN const UINT8 BitLength,
  IN const UINT8 RotateBy
  )
{
  UINT32 Mask;
  UINT32 Lsb;
  UINT32 Result;
  UINT8 i;

  Result = Value;
  Mask = (1 << BitLength) - 1;

  for (i = 0; i < RotateBy; i++) {
    Lsb = 1 & (((Result) & (1 << (BitLength - 1))) >> (BitLength-1)); // The MSB value needs to move to LSB
    Result = (Mask & (Result << 1)) | Lsb;                            // Shift Left once and add the new LSB
  }

  return Result;
}

/**
  Calculate 3 Pattern Buffers values for the given CADB sequence.

  @param[in] MrcData             - The MRC global data.
  @param[in] CadbSequence        - CADB line numbers in the order of transmission.
                                   Example: 0,1,0,0,...0 for DQ mapping, 0,0,2,1,1,0,0,...0 for CS training
  @param[out] CadbPatternBuffers - Array of 3 Pattern Buffer values

**/
void
CalculateCadbPB (
  IN MrcParameters *const   MrcData,
  IN const UINT8            CadbSequence[MRC_MUX_PB_LENGTH],
  OUT UINT32                CadbPatternBuffers[3]
  )
{
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  UINT8        i;
  UINT8        j;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  MrcCall->MrcSetMem ((UINT8 *) CadbPatternBuffers, 3 * sizeof (CadbPatternBuffers[0]), 0);

  for (i = 0; i < MRC_MUX_PB_LENGTH; i++) {
    for (j = 0; j < 3; j++) {
      CadbPatternBuffers[j] = RotateLeft (CadbPatternBuffers[j], MRC_MUX_PB_LENGTH, 1) |
                                ((CadbSequence[i] & (1 << j)) >> j);
    }
  }

  for (j = 0; j < 3; j++) {
    CadbPatternBuffers[j] = RotateLeft (CadbPatternBuffers[j], MRC_MUX_PB_LENGTH, 1);
  }
}

/**
  Print final results of CPU-to-DRAM DQ mapping.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
VOID
MrcPrintDqMapResults (
  IN MrcParameters *const MrcData
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT32    Channel;
  UINT8     Byte;
  UINT8     Bit;
  UINT8     DramBit;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcRankInChannelExist (MrcData, 0, Channel)) {
      continue;
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nMapCA2DQPins Results for Ch%d (\"-1\" for skipped Bytes, DRAM DQ pins offsets):\n",
      Channel
      );
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CPU Bit: \t[0]\t[1]\t[2]\t[3]\t[4]\t[5]\t[6]\t[7]\n"
      );
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Byte%d:", Byte);
      for (Bit = 0; Bit <  MAX_BITS; Bit++) {
        DramBit = MrcData->Inputs.Controller[0].Channel[Channel].DqMapCpu2Dram[Byte][Bit];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", (DramBit == 255) ? -1 : DramBit);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }
#endif //MRC_DEBUG_PRINT
}

/**
  Sweep the given PI up or down and find the edge.

  @param[in]  MrcData     - The MRC global data.
  @param[in]  Iteration   - Determines which PI to shift
  @param[in]  ChannelMask - Valid Channel bit mask
  @param[in]  RankMask    - Valid Rank bit mask
  @param[in]  GroupMask   - Valid Group bit mask
  @param[in]  Stop        - End of the PI range
  @param[in]  Step        - PI step for the sweep
  @param[out] Limit       - array of edge values (per channel), filled by this function
  @param[in]  DebugPrint  - Print debug messages or not

**/
void
CaFindEdge (
  IN  MrcParameters *const   MrcData,
  IN  UINT8                  Iteration,
  IN  UINT8                  ChannelMask,
  IN  UINT8                  RankMask,
  IN  UINT8                  GroupMask,
  IN  INT16                  Stop,
  IN  INT16                  Step,
  OUT UINT8                  Limit[MAX_CHANNEL],
  IN  BOOLEAN                DebugPrint
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             ChannelBit;
  UINT8             ChError;
  UINT8             CmdGroup;
  INT16             PiOffset;
  BOOLEAN           Pass;
  BOOLEAN           Done;
  BOOLEAN           ChannelDone[MAX_CHANNEL];
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntOutput          *IntOutputs;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  IntOutputs = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];

  PiOffset = 0;
  Done = FALSE;
  ChannelDone[0] = ChannelDone[1] = FALSE;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "\t0 1\n" : "");

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "%d:\t" : "", PiOffset);
    // Update Timing
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((1 << Channel) & ChannelMask) {
        if (!ChannelDone[Channel]) {
          if (MrcIterationClock == Iteration) {
            ShiftPIforCmdTraining(MrcData, Channel, Iteration, RankMask, GroupMask, PiOffset, 0);
          } else if (MrcIterationCmd == Iteration) {
            IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
            for (CmdGroup = 0; CmdGroup < MAX_COMMAND_GROUPS; CmdGroup++) {
              if (GroupMask & (1 << CmdGroup)) {
                ShiftPIforCmdTraining(MrcData, Channel, Iteration, RankMask, (1 << CmdGroup), (INT32) IntCmdTiming->CmdPiCode[CmdGroup] + PiOffset, 0);
              }
            }
            ShiftPIforCmdTraining(MrcData, Channel, MrcIterationCtl, RankMask, (1 << 0), (INT32) IntCmdTiming->CtlPiCode[0] + PiOffset, 0);
            ShiftPIforCmdTraining(MrcData, Channel, MrcIterationCtl, RankMask, (1 << 1), (INT32) IntCmdTiming->CtlPiCode[1] + PiOffset, 0);
          } // If CmdIteration
        } // if ChannelDone
      }
    } // For channel
    // Reset DDR after changing the CLK PI
    MrcResetSequence (MrcData);

    // Run CPGC test on both channels
    ChError = RunIOTest (MrcData, ChannelMask, Outputs->DQPat, 1, 0);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelBit = (1 << Channel);
      if (((ChannelBit & ChannelMask) == 0) || (ChannelDone[Channel])) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint && (Channel == 0)) ? "  " : "");
        continue;
      }

      Pass = !(ChError & ChannelBit);

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? (Pass ? ". " : "# ") : "");

      if (Pass) {
        Limit[Channel] = (UINT8) (ABS (PiOffset));
      } else {
        ChannelDone[Channel] = TRUE;
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "\n" : "");

    PiOffset += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiOffset > Stop);
    } else {
      // Sweep down
      Done = (PiOffset < Stop);
    }

    if (ChannelDone[0] && ChannelDone[1]) {
      // Found the limit on both channels - no need to sweep PI any longer
      Done = TRUE;
    }
  }  // while not done
}

/**
  Sweep right and left from the current point to find the margins.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChannelMask - Valid Channel bit mask
  @param[in]      RankMask    - Valid Rank bit mask
  @param[in]      GroupMask   - Valid Group bit mask
  @param[in]      DebugPrint  - Print debug messages or not

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
void
CmdLinearFindEdgesLpddr (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT8                GroupMask,
  IN     BOOLEAN              DebugPrint
  )
{
  const MrcInput    *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             Rank;
  INT16             PiLow;
  INT16             PiHigh;
  INT16             PiStep;
  UINT8             RightLimit[MAX_CHANNEL];
  UINT8             LeftLimit[MAX_CHANNEL];
  BOOLEAN           ClockIteration;


  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  ClockIteration = (Iteration == MrcIterationClock);
  // We are going to sweep clock 64 PI ticks to the left and to the right
  PiLow   = -64;
  PiHigh  = 64;
  if (!ClockIteration) {
    PiLow  = -DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
    PiHigh =  DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
  }
  PiStep = 1;


  // Initialize to zero margin
  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), 0);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), 0);

  // Find right and left margins
  CaFindEdge (MrcData, Iteration, ChannelMask, RankMask, GroupMask, PiHigh, PiStep, ClockIteration ? LeftLimit : RightLimit, DebugPrint);
  CaFindEdge (MrcData, Iteration, ChannelMask, RankMask, GroupMask, PiLow, -PiStep, ClockIteration ? RightLimit : LeftLimit, DebugPrint);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & ChannelMask) {
      // Save margins for RMT
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & RankMask) {
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][0] = 10 * LeftLimit[Channel];
          Outputs->MarginResult[LastCmdT][Rank][Channel][0][1] = 10 * RightLimit[Channel];
        }
      }
    }
  }
}

/**
  Early CMD / CLK training for LPDDR4.
  Main LPDDR4 flow:
  For Rank:
    1) IF Rank != Terminating:
      a) Enable Termination on the terminated rank via FSP-High
    2) Enter CBT Mode for this Rank.
    3) Drive Rank CKE Low: DIMM switches to FSP-High (1), wait tCKELCK
    4) PLL Frequency switch from low to High
    5) Run Training on all channels / subch in parallel, find passing CA region per ch/subch.
    6) IF Rank != Terminating:
      a) Disable Termination on the terminated rank via FSP-Low
    7) PLL Frequency Switch from High to Low
    8) Drive CKE High: DIMM switches to FSP Low (0)
    9) Exit CBT Mode (In Low Frequency)
    10) Set Vref MR to FSP-High.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCaTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcInput              *Inputs;
  MrcDebug              *Debug;
  MRC_FUNCTION          *MrcCall;
  MrcOutput             *Outputs;
  MrcControllerIn       *ControllerIn;
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcStatus             Status;
  BOOLEAN               Lpddr4;
  CADB_LINE             *CadbLines;
  UINT32                CadbCount;
  UINT32                *PatBuf;
  UINT8                 Channel;
  UINT8                 ChannelMask;
  UINT8                 Rank;
  UINT8                 RankBit;
  UINT8                 RankMask;
  UINT8                 TermRankMask;
  UINT8                 PiLow;
  UINT8                 PiHigh;
  UINT8                 PiMiddle;
  UINT8                 PiStep;
  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                 BestCmd[MAX_CHANNEL][2]; // per Channel and per group (CAA and CAB)
#ifdef MRC_DEBUG_PRINT
  MrcChannelIn          *ChannelIn;
  UINT8                 Left;
  UINT8                 Right;
  UINT8                 Byte;
  UINT8                 DramByte;
#endif

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerIn     = &Inputs->Controller[0];
  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  Lpddr4           = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  TermRankMask     = Inputs->CmdRanksTerminated;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyCaTraining started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  PiLow     = DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN;
  PiHigh    = DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
  PiMiddle  = (DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN + DDRCMDCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX + 1) / 2; // // Will be updated below from the host struct
  PiStep = 2;


  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), PiHigh);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), PiLow);

  // Init DDR IO for CA training
  CadbLines = CadbLinesCsLp4;
  CadbCount = ARRAY_COUNT (CadbLinesCsLp4);
  PatBuf    = CadbMuxLp4Pattern2;
  Lpddr4CaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }
    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      Status = MrcLpddr4SetCbtCaOdtEn (MrcData, TRUE);
      if (Status != mrcSuccess) {
        return Status;
      }
    }


    ChannelMask = 0;     // Bitmask of channels that have current rank populated
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelMask |= (1 << Channel);
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
      PiMiddle = IntCmdTiming->CmdPiCode[0]; // Found in EarlyCsCmdLpddr()

      SetupCaTrainingCadb (MrcData, Channel, Rank, CadbLines, CadbCount, PatBuf);
    }  // for Channel

    // Enter CBT Mode for this Rank.
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 1);
    if (Status != mrcSuccess) {
      return Status;
    }

    // Send VrefCA on DQ[6:0]
    MrcSendCaVrefOnDq (MrcData, Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "R%d: MrcSendCaVrefOnDq done\n", Rank);

    // Sweep CMD PI up and down from the middle, on both channels at the same time
    EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, RightLimit);
    EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, LeftLimit);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
#ifdef MRC_DEBUG_PRINT
      ChannelIn  = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CA training data Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (Lpddr4) {
          if (((DramByte & 1) == 0) && !Outputs->Lp4x8) {
            // Ignore DRAM bytes 0, 2, 4 and 6 on x16 devices - they don't provide feedback
            // Byte mode parts provide feedback on all bytes
            continue;
          }
        }
        Left  = LeftLimit[Channel][Rank][Byte];
        Right = RightLimit[Channel][Rank][Byte];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left);
      }
#endif // MRC_DEBUG_PRINT
    } // for Channel

    // Exit CA training mode on the current rank
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 0);
    if (Status != mrcSuccess) {
      return Status;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Disable Termination on the terminated rank via FSP-High
      Status = MrcLpddr4SetCbtCaOdtEn (MrcData, FALSE);
    }
  }  // for Rank
  // Restore DDR IO values that were used for CA training
  Lpddr4CaTrainingRestoreIo (MrcData);
  // Select optimal CMD timings for both channels
  FindBestCmdPi (MrcData, LeftLimit, RightLimit, BestCmd);

  // Apply the new CMD PI settings
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    // CAA is controlled by CmdGrp0 & CmdGrp1
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, RankMask, (3 << 0), BestCmd[Channel][0], 1);

    // CAB is controlled by CmdGrp2 & CmdGrp3
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, RankMask, (3 << 2), BestCmd[Channel][1], 1);
  } // for Channel

  return Status;
}

/**
  Sweep CS Pi up or down and find edges for all bytes.
  Main flow:
  1.
  2.
  3.

  @param[in]  MrcData - The MRC global data.
  @param[out] Limit   - array of edge PI values per channel, rank and CPU byte

**/
void
ChipSelectFindEdge (
  IN MrcParameters *const   MrcData,
  UINT8                     Rank,
  UINT8                     Start,
  UINT8                     Stop,
  INT8                      Step,
  OUT UINT8                 Limit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerIn   *ControllerIn;
  MrcControllerOut  *ControllerOut;
  MrcChannelIn      *ChannelIn;
  MrcChannelOut     *ChannelOut;
  CADB_LINE         *CadbLines;
  UINT8             Channel;
  UINT8             ChannelMask;
  UINT8             RankMask;
  UINT8             Byte;
  UINT8             ByteMask;
  UINT8             GroupMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CHANNEL];
  UINT8             PiCode;
  UINT8             NumOfOnes;
  UINT8             Feedback[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            Pattern;
  UINT32            DelayChipSelectCadb;
  UINT32            Offset;
  const UINT32      *Seeds;
  BOOLEAN           Done;
  BOOLEAN           Failed;
  BOOLEAN           Lpddr4;
  BOOLEAN           IgnoreByte;
  char              *BytesHeader;
  char              PassFail;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  ControllerOut = &Outputs->Controller[0];
  ChannelMask   = 0;
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  DelayChipSelectCadb = 1 * MRC_TIMER_1US;

  MrcCall->MrcSetMem (ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode = Start;
  Done = FALSE;
  RankMask  = 0;
  GroupMask = 3;
  CadbLines = CadbLinesCsLp4;
  NumOfOnes = MrcCountBitsEqOne (CadbLines[2].CaHigh & 0xFF);  // Take the low 8 bits of the pattern

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Ch0 pattern 1\t\t\t   Ch1 pattern 1\t\t     Ch 0 pattern 2\t\t       Ch 1 pattern 2\n");
  BytesHeader = "0   1   2   3   4   5   6   7     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CTL PI\t %s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d:\t", PiCode);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMask, GroupMask, PiCode, 0);
      }
    }

    // Try two different paterns (0x2AA or 0x155), to see if the command is still decoded correctly
    for (Pattern = 0; Pattern <= 1; Pattern++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        ChannelMask |= (1 << Channel);
        MrcSelectEngines (MrcData, 0, 1 << Channel, ChannelOut->ValidSubChBitMask);
        Seeds = (Pattern == 0) ? CadbMuxLp4Pattern2 : CadbMuxLp4Pattern3;
        MrcInitCadbPgMux (MrcData, Seeds, 0, MRC_NUM_MUX_SEEDS);
      }

      // Run CADB pattern on selected channels at the same time
      ShortRunCADB (MrcData, ChannelMask);
      MrcWait (MrcData, DelayChipSelectCadb);

      // Read and process the results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          ByteDoneMask[Channel] = 0xFF;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
          continue;
        }
        if (ByteDoneMask[Channel] == 0xFF) { // All bytes failed on this channel, no need to sweep anymore
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "                                  ");
          continue;
        }
        ChannelIn  = &ControllerIn->Channel[Channel];
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          IgnoreByte = FALSE;
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            IgnoreByte = TRUE;
          }
          if (Lpddr4) {
            if (((DramByte & 1) == 0) && !Outputs->Lp4x8) { // Ignore DRAM bytes 0, 2, 4 and 6 - they don't provide feedback  (for non x8 dram device)
              IgnoreByte = TRUE;
            }
          }
          if (IgnoreByte) {
            ByteDoneMask[Channel] |= ByteMask;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data = (MrcReadCR (MrcData, Offset) & 0xFF);  // Get only DQ bits, not DQS
          PassFail = '#';
          if ((ByteDoneMask[Channel] & ByteMask) == 0) {
            if (Pattern == 0) {
              // First pattern
              Feedback[Channel][Byte] = (UINT8) DataTrainFeedback.Data;
              PassFail = ' ';
            } else {
              // Second Pattern
              // If still read the same data, then DRAM was not able to decode the new command
              Failed = FALSE;
              if (Feedback[Channel][Byte] == (UINT8) DataTrainFeedback.Data) {
                Failed = TRUE;
              }
              if (MrcCountBitsEqOne (DataTrainFeedback.Data) != NumOfOnes) {
                Failed = TRUE;
              }
              if (Failed) {
                Limit[Channel][Rank][Byte] = PiCode;
                ByteDoneMask[Channel] |= ByteMask;
              } else {
                PassFail = '.';
              }
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c%02X ", PassFail, DataTrainFeedback.Data);
        }  // for Byte
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
      }  // for Channel
    } // for Pattern
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    if ((ByteDoneMask[0] == 0xFF) && (ByteDoneMask[1] == 0xFF)) {
      // Found the limit on all bytes on both channels - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT8) PiCode) < Stop);
    }
  }  // while not done
}


/**
  Map CA to DQ Pins for CBT training and MR4 bit swizzling settings for LPDDR4.
  Main flow:
  Repeat for each of the 8 bits per DQ byte (total 8 iterations for both channels, for rank0 only):
    - Put DRAM into MPC RD DQ Calibration mode.
    - Set both MR32 and MR40 to 0, and set the current DQ bit in both MR15 and MR20.
      This will result in a pattern of 0's on all but one bits per byte.
    - Issue a sequence of READ commands.
    - Locate the single DQ in each byte in DataTrainFeedback (using SenseAmp Mode).
    - Report error if more than one DQ pin toggles.
    - Report error if no active DQ pin found.
  Update the DQ mapping data structure.

  Assumption: runs on stable and correct CLK, CS and CA PI settings, and CA Vref.
  This should be guaranteed at 1067 MT/s.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
MapCA2DQPinsLp4 (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                    *Inputs;
  MRC_FUNCTION                                *MrcCall;
  MrcDebug                                    *Debug;
  MrcOutput                                   *Outputs;
  MrcControllerIn                             *ControllerIn;
  MrcChannelIn                                *ChannelIn;
  MrcStatus                                   Status;
  MrcStatus                                   StatusLocal;
  INT64                                       GetSetEn;
  INT64                                       GetSetDis;
  INT64                                       LeakerCompSave[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                      Offset;
  UINT32                                      InvertData;
  UINT8                                       Channel;
  UINT8                                       SubCh;
  UINT8                                       ChBitMask;
  UINT8                                       Rank;
  UINT8                                       Byte;
  UINT8                                       DramByte;
  UINT8                                       Bit;
  UINT8                                       LoopCount;
  UINT8                                       TestDoneStatus;
  UINT8                                       Feedback[8];
  CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT              CpgcSeqCtl;
  CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT           CpgcSeqStatus;

  Status        = mrcSuccess;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerIn  = &Inputs->Controller[0];
  Rank          = 0;
  ChBitMask     = 0;
  GetSetEn      = 1;
  GetSetDis     = 0;
  LoopCount     = 10;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MapCA2DQPinsLp4 started\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, 0);
    if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
      continue;
    }
    MrcCall->MrcSetMem (
      (UINT8 *) (ControllerIn->Channel[Channel].DqMapCpu2Dram),
      sizeof (ControllerIn->Channel[0].DqMapCpu2Dram),
      0xFF
      );

    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        MrcIssueMrw (MrcData, Channel, SubCh, Rank, 32, 0x00, FALSE, FALSE, FALSE); // DQ Calibration Pattern "A"
        MrcIssueMrw (MrcData, Channel, SubCh, Rank, 40, 0x00, FALSE, FALSE, FALSE); // DQ Calibration Pattern "B"
      }
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp, ReadFromCache, &LeakerCompSave[Channel][Byte]);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp, WriteToCache, &GetSetDis);
    }
    MrcFlushRegisterCachedData (MrcData);
  } // for Channel

  // Init DDR IO for static feedback on DQ
  LpddrCaTrainingInitIo (MrcData);

  // Setup CPGC Engine
  SetupIOTestMPR (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 0, 0);

  // Set BLOCK_REPEATS to a big number to get B2B traffic
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MrcSetLoopcount (MrcData, Channel, 0x80000000);
  }

  for (Bit = 0; Bit < MAX_BITS; Bit++) {
    InvertData = 1 << Bit;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRunning Bit %d\n", Bit);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          MrcIssueMrw (MrcData, Channel, SubCh, Rank, 15, InvertData, FALSE, FALSE, FALSE); // Lower Byte Invert for DQ Calibration
          MrcIssueMrw (MrcData, Channel, SubCh, Rank, 20, InvertData, FALSE, FALSE, FALSE); // Upper Byte Invert for DQ Calibration
        }
      }
      // Configure MC to issue MPC[Read DQ Calibration] instead of reads
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteCached, &GetSetEn);
    }

    // Start CPGC and run for 1uS
    CpgcSeqCtl.Data            = 0;
    CpgcSeqCtl.Bits.START_TEST = 1;
    Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);

    // Wait to obtain results in DataTrainFeedback
    MrcWait (MrcData, 200 * MRC_TIMER_1NS);

    // Get Results for all ch/bytes
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelIn  = &ControllerIn->Channel[Channel];

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
        Feedback[Byte] = (UINT8) (MrcReadCR (MrcData, Offset) & 0xFF); // Strip out DQS bit
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\t   Channel %d CPU Byte %d DRAM Byte %d => Feedback = %02X - %s feedback\n",
          Channel,
          Byte,
          DramByte,
          Feedback[Byte],
          (MrcCountBitsEqOne (Feedback[Byte]) == 1) ? "Good" : "Bad"
          );
      } // for Byte

      // Store results in ChannelIn->DqMapCpu2Dram
      StatusLocal = FillCA2DQMapResult (MrcData, Channel, Feedback, Bit);
      if (StatusLocal != mrcSuccess) {
        Status = StatusLocal;  // This will signal ECT failure
      }
    } // for Channel

    // Stop CPGC
    CpgcSeqCtl.Data            = 0;
    CpgcSeqCtl.Bits.STOP_TEST  = 1;
    Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);

    // Wait till CPGC test is done on all participating channels
    do {
      TestDoneStatus = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          Offset = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_SEQ_STATUS_REG, CH1_SC0_CR_CPGC_SEQ_STATUS_REG, Channel);
          CpgcSeqStatus.Data = MrcReadCR (MrcData, Offset);
          TestDoneStatus |= (CpgcSeqStatus.Bits.TEST_DONE) << Channel;
        }
      }
    } while ((TestDoneStatus & ChBitMask) != ChBitMask);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        // Disable MPR mode on MC
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteCached, &GetSetDis);
      }
    } // for Channel
  }  // for Bit

  // Restore DDR IO values that were used for static feedback on DQ
  LpddrCaTrainingRestoreIo (MrcData);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
      continue;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp,   WriteToCache, &LeakerCompSave[Channel][Byte]);
    }
    MrcFlushRegisterCachedData (MrcData);
  } // for Channel
  IoReset (MrcData);

#ifdef MRC_DEBUG_PRINT
  MrcPrintDqMapResults (MrcData);
#endif //MRC_DEBUG_PRINT

  return Status;
}

/**
  This routine is used throughout LPDDR4 ECT code to initialize DDR IO for CA training.
  On "Odd" DRAM bytes: enable the following bits because we will use DATATRAINFEEDBACK to read back CA values on DQ[13:8] pins:
    DataControl2.ForceRxOn and ForceBiasOn (must be set first)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes we will send VrefCA values on DQ[6:0] pins:
    DataControl5.DdrCRMaskCntPulseNumStart[16:13] = 6 (number of masked DQS pulses)
    DataControl5.DdrCRNumOfPulses[12:11] = 2 (number of DQS pulses sent)
    DataControl5.Ddrcrdqsmaskcnten[10] = 1 (enables the special CBT VrefCA programming mode)
    DataControl0.TxOn (must be after DataControl5)
  Note: For x8 devices all bytes will return feedback. Don't send VrefCA on DQ pins.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingInitIo (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput           *Outputs;
  MrcChannelIn        *ChannelIn;
  INT64               GetSetVal;
  INT64               NumMaskedPulses;
  INT64               NumOfPulses;
  UINT8               Channel;
  UINT8               Byte;

  Outputs         = &MrcData->Outputs;
  GetSetVal       = 1;
  NumMaskedPulses = 6;
  NumOfPulses     = 2;

  IoReset (MrcData); // To avoid ODT segment shift while in ForceOdtOn mode

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &MrcData->Inputs.Controller[0].Channel[Channel];
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
        if ((ChannelIn->DqsMapCpu2Dram[Byte] % 2) || Outputs->Lp4x8) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceBiasOn,  WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
        }
      }
    }
    MrcFlushRegisterCachedData (MrcData);

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
        // For x8 devices enable the following bits on both even and odd bytes.
        if ((ChannelIn->DqsMapCpu2Dram[Byte] % 2) || Outputs->Lp4x8) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceOdtOn,   WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocSenseAmpMode, WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxDisable,    WriteToCache, &GetSetVal);
        } else {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxPiPwrDnDis,       WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4DqsMaskPulseCnt, WriteToCache, &NumMaskedPulses);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4DqsPulseCnt,     WriteToCache, &NumOfPulses);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4DqsPulseEn,      WriteToCache, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);  // Must enable Pulse config before turning on Tx.
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxOn,               WriteToCache, &GetSetVal);
        }
      }
    }
    MrcFlushRegisterCachedData (MrcData);
  }
}

/**
  This routine is used throughout LPDDR4 ECT code to restore DDR IO from CA training.
  On "Odd" DRAM bytes: disable the following bits:
    DataControl2.ForceRxOn and ForceBiasOn (must be cleared last)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes: disable the following bits:
    DataControl0.TxOn (must be cleared first)
    DataControl5.Ddrcrdqsmaskcnten[10] = 0 (disable the special CBT VrefCA programming mode)

  The order of HW writes is opposite from Lpddr4CaTrainingInitIo.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingRestoreIo (
  IN MrcParameters *const  MrcData
  )
{
  MrcOutput           *Outputs;
  MrcChannelIn        *ChannelIn;
  INT64               GetSetVal;
  UINT8               Channel;
  UINT8               Byte;

  Outputs   = &MrcData->Outputs;
  GetSetVal = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &MrcData->Inputs.Controller[0].Channel[Channel];
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
        if ((ChannelIn->DqsMapCpu2Dram[Byte] % 2) || Outputs->Lp4x8) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceOdtOn,   WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocSenseAmpMode, WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxDisable,    WriteToCache, &GetSetVal);
        } else {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxOn,         WriteToCache, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);   // DdrCRDqsMaskCntEn must be written after TxOn
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4DqsPulseEn,      WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxPiPwrDnDis,       WriteToCache, &GetSetVal);
        }
      }
    }
    MrcFlushRegisterCachedData (MrcData);

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
        if ((ChannelIn->DqsMapCpu2Dram[Byte] % 2) || Outputs->Lp4x8) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceBiasOn,  WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
        }
      }
    }
    MrcFlushRegisterCachedData (MrcData);
  }
}

/**
  This routine is used throughout LPDDR4 ECT code to initialize DDR IO for CA training.
  On all DRAM bytes we will send VrefCA values on DQ[6:0] pins:
    DataControl5.DdrCRMaskCntPulseNumStart[16:13] = 6 (number of masked DQS pulses)
    DataControl5.DdrCRNumOfPulses[12:11] = 2 (number of DQS pulses sent)
    DataControl5.Ddrcrdqsmaskcnten[10] = 1 (enables the special CBT VrefCA programming mode)
    DataControl0.TxOn (must be after DataControl5)

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingInitIoTx (
  IN MrcParameters *const MrcData
  )
{
  INT64               GetSetVal;
  INT64               NumMaskedPulses;
  INT64               NumOfPulses;

  GetSetVal       = 1;
  NumMaskedPulses = 6;
  NumOfPulses     = 2;

  // Set DataControl0.TxPiOn before TxOn
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,       WriteToCache, &GetSetVal);

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4DqsMaskPulseCnt, WriteToCache, &NumMaskedPulses);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4DqsPulseCnt,     WriteToCache, &NumOfPulses);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4DqsPulseEn,      WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);  // Must enable Pulse config before turning on Tx.

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxOn,               WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This routine is used throughout LPDDR4 ECT code to restore DDR IO from CA training.
  On all DRAM bytes: disable the following bits:
    DataControl0.TxOn (must be cleared first)
    DataControl5.Ddrcrdqsmaskcnten[10] = 0 (disable the special CBT VrefCA programming mode)

  The order of HW writes is opposite from Lpddr4CaTrainingInitIoTx.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingRestoreIoTx (
  IN MrcParameters *const MrcData
  )
{
  INT64               GetSetVal;

  GetSetVal       = 0;

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxOn,               WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4DqsPulseEn,      WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,       WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  Enter / exit LPDDR4 CA training mode:
  If ENABLE:
    - Send MRW to MR13 OP[0] = 1, Wait tMRD
    - Force CKE low
    - Switch PLL to High frequency
  Else // DISABLE
    - Switch PLL to Low frequency
    - Force CKE high, Wait tFC
    - Send MRW to MR13 OP[0] = 0.

  NOTE: this has to be called at once on all participating channels using ChBitMask argument, because we switch to high frequency when enabling CBT.

  @param[in] MrcData      - The MRC global data.
  @param[in] ChBitMask    - Channels to work on.
  @param[in] RankBitMask  - Ranks to work on.
  @param[in] Enable       - Enable or disable CBT.

  @retval mrcSuccess if succeeded
**/
MrcStatus
Lpddr4CommandTrainingMode (
  IN MrcParameters *const  MrcData,
  IN UINT8                 ChBitMask,
  IN UINT8                 RankBitMask,
  IN BOOLEAN               Enable
  )
{
  MrcStatus           Status;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  UINT8               Channel;
  UINT8               SubCh;
  UINT8               Rank;
  UINT16              Data;
  UINT32              Address;

  Outputs       = &MrcData->Outputs;
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  ControllerOut = &Outputs->Controller[0];

  Address = 13;
  Status  = mrcSuccess;

  if (!Enable) { // Exit CBT mode
    // Set Low frequency (1067), unless we're already there
    if ((Outputs->Frequency != f1067) && (MrcData->Inputs.LpFreqSwitch == TRUE)) {
      Status = MrcFrequencySwitch (MrcData, f1067, MRC_PRINTS_OFF);
      if (Status != mrcSuccess) {
        return Status;
      }
    }
    // Force CKE high, Wait tFC_Long = 250ns
    MrcForceCkeValue (MrcData, ChBitMask, 0xF);
    MrcWait (MrcData, MRC_LP4_tFC_LONG_NS * MRC_TIMER_1NS);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) == 0) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    IntCmdTiming  = &IntOutputs->Controller[0].CmdTiming[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      if (((1 << Rank) & RankBitMask) != 0) {
        // Use safe CS/CA PI settings, otherwise this MRW may get sampled as invalid command (or SRE etc.)
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, 0x03, MRC_INITIAL_CTL_PI, 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, 0x1F, MRC_INITIAL_CMD_PI, 0);

        Data = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR[mrIndexMR13];
        MrcLpddr4SetMr13 (MrcData, (UINT8) Enable, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, &Data);
        for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            Status = MrcIssueMrw (MrcData, Channel, SubCh, Rank, Address, Data, FALSE, FALSE, FALSE);
          }
        }
        // Restore CS/CA PI settings from the host struct, CS is per SubCh
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 0), IntCmdTiming->CtlPiCode[0], 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 1), IntCmdTiming->CtlPiCode[1], 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0,     0x1F, IntCmdTiming->CmdPiCode[0], 0);

        if (Status != mrcSuccess) {
          return Status;
        }
      }
    }
  }

  if (Enable) {
    // Wait tMRD - guaranteed by MRH
    // Force CKE low
    MrcForceCkeValue (MrcData, ChBitMask, 0);

    // Wait tCAENT = 250ns
    MrcWait (MrcData, MRC_LP4_tCAENT_NS * MRC_TIMER_1NS);

    // Set High frequency, unless we're already there
    if ((Outputs->Frequency != Outputs->HighFrequency)  && (MrcData->Inputs.LpFreqSwitch == TRUE)) {
      Status = MrcFrequencySwitch (MrcData, Outputs->HighFrequency, MRC_PRINTS_OFF);
    }
  }

  return Status;
}

/**
  Process the results of the early LPDDR4 CS training and find the best PI settings for CS per sub-channel.
  Flow:
   1. Find the worst case Right and Left limits for each group
   2. Find the Center for each group

  @param[in]  MrcData     - The MRC global data.
  @param[in]  LeftLimit   - Array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - Array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - Array of best CS PI settings, per channel and group

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCsPi (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  OUT UINT8                 BestCs[MAX_CHANNEL][MAX_SUB_CHANNEL]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  UINT32            SubCh;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             CsLeftLimit[MAX_CHANNEL][MAX_SUB_CHANNEL];
  UINT8             CsRightLimit[MAX_CHANNEL][MAX_SUB_CHANNEL];

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  MrcCall->MrcSetMem ((UINT8 *) CsRightLimit, sizeof (CsRightLimit), 127);
  MrcCall->MrcSetMem ((UINT8 *) CsLeftLimit, sizeof (CsLeftLimit), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CS PIs:\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel: %d\tLeft\tRight\tCenter\n", Channel);
    ChannelOut = &Outputs->Controller[0].Channel[Channel];

    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        for (Byte = ChannelOut->ByteStart[SubCh]; Byte <= ChannelOut->ByteEnd[SubCh]; Byte++) {
          // Find the worst case Right and Left limits across both ranks
          if (CsRightLimit[Channel][SubCh] > RightLimit[Channel][Rank][Byte]) {
            CsRightLimit[Channel][SubCh] = RightLimit[Channel][Rank][Byte];
          }
          if (CsLeftLimit[Channel][SubCh] < LeftLimit[Channel][Rank][Byte]) {
            CsLeftLimit[Channel][SubCh] = LeftLimit[Channel][Rank][Byte];
          }
        } // for Byte
      } // for Rank

      // Find the Center for each subch
      BestCs[Channel][SubCh] = (CsRightLimit[Channel][SubCh] + CsLeftLimit[Channel][SubCh]) / 2;

      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "SubCh %d:\t%d\t%d\t%d\n",
        SubCh,
        CsLeftLimit[Channel][SubCh],
        CsRightLimit[Channel][SubCh],
        BestCs[Channel][SubCh]
        );
    } // for SubCh
  } // for Channel

  return Status;
}

/**
  Send VrefCA on DQ[6:0] during LPDDR4 CBT for non x8 dram devices.

  @param[in] MrcData  - The MRC global data.
  @param[in] Rank     - The rank to work on.

  @retval none
**/
VOID
MrcSendCaVrefOnDq (
  IN MrcParameters *const   MrcData,
  IN UINT32                 Rank
  )
{
  MrcInput                      *Inputs;
  MRC_FUNCTION                  *MrcCall;
  MrcOutput                     *Outputs;
  MrcIntOutput                  *IntOutputs;
  MrcChannelIn                  *ChannelIn;
  MrcChannelOut                 *ChannelOut;
  INT64                         GetSetVal;
  UINT8                         Channel;
  UINT8                         SubCh;
  UINT8                         ChBitMask;
  UINT32                        DramByte;
  UINT32                        DramBit;
  UINT32                        CpuByte;
  UINT32                        CpuBit;
  UINT32                        BitValue;
  UINT8                         DramValue;
  UINT8                         CpuValue;
  MRC_PATTERN_CTL               WDBPattern;
  UINT64_STRUCT                 VrefPattern[CADB_20_MAX_CHUNKS];

  static const Cpgc20Address  CPGCAddress = {
    CPGC20_ROW_COL_2_BANK_2_RANK,
    0,
    0,
    0,
    0,
    0,
    3,
    1
  };

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);

  WDBPattern.IncRate    = 0;
  WDBPattern.Start      = 0;
  WDBPattern.Stop       = 1;
  WDBPattern.DQPat      = StaticPattern;
  WDBPattern.PatSource  = MrcPatSrcDynamic; // Don't use WDB
  WDBPattern.EnableXor  = FALSE;

  // Default VrefCA is 27.2% of VDD = 0.3v
  // Encoding: Range 1, 001101 --> 0x4D
  DramValue = 0x4D;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn  = &Inputs->Controller[0].Channel[Channel];
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    if (Outputs->Lp4x8) {
      // skip for x8 devices
      return;
    }
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      MrcCall->MrcSetMem ((UINT8 *) VrefPattern, sizeof (VrefPattern), 0);
      for (CpuByte = ChannelOut->ByteStart[SubCh]; CpuByte <= ChannelOut->ByteEnd[SubCh]; CpuByte++) {
        // Find which DRAM byte is mapped to this CPU byte
        DramByte = ChannelIn->DqsMapCpu2Dram[CpuByte];
        // CTE has x8 connection, so need to send VREF on all bytes
        if ((DramByte & 1) == 1) {
          continue; // VrefCA should be sent on even bytes only - DQ[6:0]
        }
        CpuValue = 0;
        for (CpuBit = 0; CpuBit < MAX_BITS; CpuBit++) {
          // Find DRAM DQ pin that is connected to the current CPU DQ pin
          DramBit = ChannelIn->DqMapCpu2Dram[CpuByte][CpuBit] - 8 * DramByte; // Subtract 8xDramByte
          BitValue = (DramValue >> DramBit) & 1;    // DRAM DQ value
          CpuValue |= (BitValue << CpuBit);         // Should go on this CPU DQ pin
        }
        GetSetVal = CpuValue;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, CpuByte, GsmIocLp4DqOverrideData, WriteToCache, &GetSetVal);
        GetSetVal = 0xFF;   // Send all the bits
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, CpuByte, GsmIocLp4DqOverrideEn,   WriteToCache, &GetSetVal);
        VrefPattern[0].Data |= MrcCall->MrcLeftShift64 (CpuValue, (CpuByte - ChannelOut->ByteStart[SubCh]) * 8);
      }  // for Device
    } // for Subch
  } // for Channel
  MrcFlushRegisterCachedData (MrcData);

  // Setup IO test: CmdPat=PatWr, NumCL=2, LC=1, NSOE, EnCADB=0, EnCKE=0, SubSeqWait=0
  IntOutputs->SkipZq = TRUE;
  SetupIOTest (MrcData, Outputs->ValidChBitMask, PatWr, 2, 1, &CPGCAddress, NSOE, &WDBPattern, 0, 0, 0);
  IntOutputs->SkipZq = FALSE;


  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBitMask |= SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, 0);

    // Set SC_GS_CFG_TRAINING.mask_cs to mask CS while sending CPGC commands.
    // Set SC_GS_CFG_TRAINING.ignore_cke to send CPGC commands even if CKE is LOW.
    GetSetVal = 1;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccMaskCs,    WriteNoCache, &GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccIgnoreCke, WriteNoCache, &GetSetVal);

    MrcSetLoopcount (MrcData, Channel, 0); // Set BLOCK_REPEATS = 0 --> 1 iteration
  }
  MrcSelectEngines (MrcData, 0, ChBitMask, Outputs->ValidSubChMask);
  Cpgc20BaseRepeats (MrcData, 8, 1); // Set BASE_REPEATS to 7 (8 iterations)

  // Run Test: DQPat = StaticPattern, ClearErrors = 0, ResetMode = 0
  RunIOTest (MrcData, ChBitMask, WDBPattern.DQPat, 0, 0);

  // Wait tVrefCA_Long = 250ns
  MrcWait (MrcData, MRC_LP4_tVREFCA_LONG_NS * MRC_TIMER_1NS);

  GetSetVal = 0;
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4DqOverrideEn, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  // Restore MC registers
  GetSetVal = 0;
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccMaskCs,    WriteNoCache, &GetSetVal);
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccIgnoreCke, WriteNoCache, &GetSetVal);
}

/**
  Early CS / CLK training for LPDDR4.
  Main flow:
  For Rank:
    1) IF Rank != Terminating:
      a) Enable Termination on the terminated rank via FSP-High
    2) Enter CBT Mode for this Rank.
    3) Drive Rank CKE Low: DIMM switches to FSP-High (1), wait tCKELCK
    4) PLL Frequency switch from low to High
    5) Run Training on all channels / subch in parallel, find passing CS region per ch/subch.
    6) IF Rank != Terminating:
      a) Disable Termination on the terminated rank via FSP-Low
    7) PLL Frequency Switch from High to Low
    8) Drive CKE High: DIMM switches to FSP Low (0)
    9) Exit CBT Mode (In Low Frequency)
    10) Set Vref MR to FSP-High.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyChipSelectTrainingLp4 (
  IN MrcParameters *const MrcData
  )
{
  MrcInput              *Inputs;
  MRC_FUNCTION          *MrcCall;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerIn       *ControllerIn;
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcStatus             Status;
  UINT32                SubCh;
  UINT8                 Channel;
  UINT8                 ChannelMask;
  UINT8                 Rank;
  UINT8                 RankBit;
  UINT8                 RankMask;
  UINT8                 TermRankMask;
  UINT8                 PiLow;
  UINT8                 PiHigh;
  UINT8                 PiMiddle;
  UINT8                 PiStep;
  UINT8                 RightLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                 LeftLimit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8                 BestCs[MAX_CHANNEL][MAX_SUB_CHANNEL];
#ifdef MRC_DEBUG_PRINT
  MrcChannelIn          *ChannelIn;
  UINT8                 Left;
  UINT8                 Right;
  UINT8                 Byte;
  UINT8                 DramByte;
#endif // MRC_DEBUG_PRINT

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerIn     = &Inputs->Controller[0];
  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  TermRankMask     = Inputs->CmdRanksTerminated;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyChipSelectTrainingLp4 started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  PiLow    = DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN;
  PiHigh   = DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX;
  PiMiddle = (DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN + DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX + 1) / 2; // Will be updated below from the host struct
  PiStep = 2;


  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), PiHigh);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), PiLow);

  // Init DDR IO for CA training
  Lpddr4CaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      MrcLpddr4SetCbtCaOdtEn (MrcData, TRUE);
    }


    ChannelMask = 0;     // Bitmask of channels that have current rank populated
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      ChannelMask |= (1 << Channel);
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
      PiMiddle = IntCmdTiming->CtlPiCode[Rank];  // Found in EarlyCsCmdLpddr()
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IntCmdTiming->CtlPiCode[%d] = %d\n", Rank, PiMiddle);

      SetupCaTrainingCadb (
        MrcData,
        Channel,
        Rank,
        CadbLinesCsLp4,
        sizeof (CadbLinesCsLp4) / sizeof (CadbLinesCsLp4[0]),
        CadbMuxLp4Pattern2
        );
    }  // for Channel

    // Enter CBT Mode for this Rank.
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 1);
    if (Status != mrcSuccess) {
      return Status;
    }

    // Send VrefCA on DQ[6:0]
    MrcSendCaVrefOnDq (MrcData, Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "R%d: MrcSendCaVrefOnDq done\n", Rank);

    // Sweep CS Pi up and down from the middle, on both channels at the same time
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, RightLimit);
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, LeftLimit);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
#ifdef MRC_DEBUG_PRINT
      ChannelIn  = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS training data Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
        if (((DramByte & 1) == 0) && !Outputs->Lp4x8) {
          // Ignore DRAM bytes 0, 2, 4 and 6 on x16 devices - they don't provide feedback
          // Byte mode parts provide feedback on all bytes
          continue;
        }
        Left  = LeftLimit[Channel][Rank][Byte];
        Right = RightLimit[Channel][Rank][Byte];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left);
      }
#endif // MRC_DEBUG_PRINT
    } // for Channel

      // Exit CA training mode on the current rank
    Status = Lpddr4CommandTrainingMode (MrcData, ChannelMask, RankBit, 0);
    if (Status != mrcSuccess) {
      return Status;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Disable Termination on the terminated rank via FSP-High
      Status = MrcLpddr4SetCbtCaOdtEn (MrcData, FALSE);
    }
  }  // for Rank
  // Restore DDR IO values that were used for CMD training
  Lpddr4CaTrainingRestoreIo (MrcData);
  // Select optimal CS timings for both channels
  FindBestCsPi (MrcData, LeftLimit, RightLimit, BestCs);

  // Apply the new CS settings
  // Note that both ranks share the same PI setting
  // CS PI is separate per sub-channel
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        // Shift CS per subch
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, 1 << SubCh, BestCs[Channel][SubCh], 1);
      }
    }
  }

  return Status;
}

/**
  Early CA / CS training for LPDDR4.
  Main flow:
  1. Run CPU-to-DRAM DQ Mapping (map DQ pins according to the board swizzling).
  2. Run Early 2D CS/CMD training
  3. Run CS vs. CLK training.
  4. Run CA vs. CLK training.
  5. Program DESWIZZLE_HIGH/LOW registers.
  6. Set DRAM to FSP-High for all Ranks; lock PLL to High Frequency.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyCommandTrainingLpddr4 (
  IN MrcParameters *const MrcData
)
{
  MrcOutput       *Outputs;
  MrcStatus       Status;

  Outputs = &MrcData->Outputs;
  Status  = mrcSuccess;

  // Run CPU-to-DRAM DQ Mapping
  Status = MapCA2DQPinsLp4 (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Early 2D CS/CMD training - find the good starting point for the rest of the ECT steps.
  Status = EarlyCsCmdLpddr (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Run CS vs. CLK training
  Status = EarlyChipSelectTrainingLp4 (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Run CA vs. CLK training
  Status = EarlyCaTraining (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Program DESWIZZLE_HIGH/LOW registers
  ProgramDeswizzleRegisters (MrcData);

  // Set FSP-OP = 1, set High frequency
  Status = MrcLpddr4SwitchToHigh (MrcData, MRC_PRINTS_ON);

  Outputs->LpddrEctDone = TRUE;

  return Status;
}

/**
  Center CMD with respect to CLK & CTL.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChannelMask    - Channels to train
  @param[in]     LoopCount      - Loop count for CMD stress.
  @param[in]     SetupCadb      - Indicates if SetupCadb should be called and disabled at the end.
  @param[in]     DebugPrint     - Enable / disable debug printing
  @param[in]     UpdateHost     - Determines if MrcData structure is updated

  @retval MrcStatus
**/
MrcStatus
MrcCmdTimingCentering (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                ChannelMask,
  IN UINT8                LoopCount,
  IN BOOLEAN              SetupCadb,
  IN BOOLEAN              DebugPrint,
  IN const UINT8          UpdateHost
)
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               ChBitMask;
  UINT8               RankMask;
  UINT8               MidPointCmd[MAX_COMMAND_GROUPS][MAX_CHANNEL];
  UINT8               CmdGroup;
  UINT8               CmdGroupMax;
  BOOLEAN             ExitOnFailure;
  BOOLEAN             Ddr4;
  CH0_SC0_CR_CADB_CFG_STRUCT          CadbConfig;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  IntOutputs        = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut  = &IntOutputs->Controller[0];

  ExitOnFailure = (BOOLEAN) Inputs->ExitOnFailure;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  ChBitMask     = Outputs->ValidChBitMask & ChannelMask;
  RankMask      = Outputs->ValidRankMask;

  CmdGroupMax = (Ddr4) ? MAX_COMMAND_GROUPS : MAX_COMMAND_GROUPS - 1;


  // Program default rank mapping
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    SelectReutRanks(MrcData, Channel, RankMask, FALSE, 0);
  }

  if (SetupCadb) {
    // SetupIOTest is already called in TrainDDROptParms and LCT.
    SetupIOTestCADB(MrcData, ChBitMask, LoopCount, NTHSOE, 1, 0);
  }

  // Get the midpoint for CMD and CTL
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
    for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
      MidPointCmd[CmdGroup][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
    }
  }

  // Center Command Timing
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDA_Pi0Code Timing\n");
  Status = CmdTimingCentering(MrcData, MrcIterationCmd, RankMask, (1 << 0), MidPointCmd[0]);
  if ((Status != mrcSuccess) && (ExitOnFailure)) {
    return Status;
  }
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDA_Pi1Code Timing\n");
  Status = CmdTimingCentering(MrcData, MrcIterationCmd, RankMask, (1 << 1), MidPointCmd[1]);
  if ((Status != mrcSuccess) && (ExitOnFailure)) {
    return Status;
  }
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDB_Pi0Code Timing\n");
  Status = CmdTimingCentering(MrcData, MrcIterationCmd, RankMask, (1 << 2), MidPointCmd[2]);
  if ((Status != mrcSuccess) && (ExitOnFailure)) {
    return Status;
  }
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMDB_Pi1Code Timing\n");
  Status = CmdTimingCentering(MrcData, MrcIterationCmd, RankMask, (1 << 3), MidPointCmd[3]);
  if ((Status != mrcSuccess) && (ExitOnFailure)) {
    return Status;
  }
  if (Ddr4) { // CKECMD FUB only for DDR4
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\n*** Center CKECMD_Pi2Code Timing\n");
    Status = CmdTimingCentering(MrcData, MrcIterationCmd, RankMask, (1 << 4), MidPointCmd[4]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }
  }

  // Disable CADB Deselects after Command Training
  if (SetupCadb) {
    CadbConfig.Data = 0;
    Cadb20ConfigRegWrite (MrcData, CadbConfig);
  }

  // Finish Training with JEDEC Reset / Init
  Status = MrcResetSequence (MrcData);
  return Status;
}

/**
  Training the Cmd slew rate for best margins.
  Steps:
  1. Get Min/Max Stage Number from DDR Scomp config step (Start).
  2. Train Cmd Slew rate stages in the region [Start, Stop].
  3. Re-center Cmd Timing.
  4. Re-center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdSlewRate (
  IN MrcParameters *const MrcData
)
{
  static const UINT8  TestList[] = { CmdV, CmdT };
  static const UINT8  Scale[] = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptCmdSComp };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8        MaxNumStages;
  INT8        MinNumStages;

  Outputs = &MrcData->Outputs;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Debug = &Outputs->Debug;

  MinNumStages = IntOutputs->CmdSRData.MinChainLengthCmd;
  MaxNumStages = IntOutputs->CmdSRData.MaxChainLengthCmd;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd SComp Stages: Min %d, Max %d\n", MinNumStages, MaxNumStages);

  // Train Slew Rate for best margins
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &MinNumStages,  // Start
    &MaxNumStages,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatternType
    );

  // Trainning CMD SR by Offset
  Status = MrcCmdSlewRateOffset (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  return Status;
}

/**
  Training the Cmd slew rate offset for best margins.
  Steps:
  1. Find the minimal number of stages for which Comp is not saturated (Start).
  2. Find the maximal number of stages for which Comp is not saturated (Stop).
  3. Train Cmd Slew rate stages in the region [Start, Stop].
  4. Re-center Cmd Timing.
  5. Re-center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdSlewRateOffset (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { CmdV, CmdT };
  static const UINT8  Scale[] = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptCmdSCompOffset };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                Start=-16;
  INT8                Stop=15;
  INT64               GetSetVal;
  DDRPHY_COMP_CR_DDRCRCOMPCTL1_STRUCT      DdrCrCompCtl1;


  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  DdrCrCompCtl1.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG); // Save COMP values
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd SCompPC : %s\tCmdScompCells : %u \n", ((DdrCrCompCtl1.Bits.CmdScompPC == 1) ? "Cycle" : "Phase"), DdrCrCompCtl1.Bits.CmdScompCells);

  MrcGetSetDdrIoCmdGroup (MrcData, 0, 0, CmdSCompOffset, ReadUncached | PrintValue, &GetSetVal);
  MrcGetSetDdrIoCmdGroup (MrcData, 1, 0, CmdSCompOffset, ReadUncached | PrintValue, &GetSetVal);

  // Train Slew Rate for best margins
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    CustomSR,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start, // Start
    &Stop,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatternType
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center
  Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  if (Status != mrcSuccess) {
    return Status;
  }

  Status = MrcCmdVoltageCentering (MrcData);

  return Status;
}

/**
  Training the Command TxEq and Ron for best margins.
  Steps:
  1. Find the minimal Vref (Ron) for which Comp is no saturated (Start).
  2. Find the maximal Vref (Ron) for which Comp is no saturated (Stop).
  3. Train Cmd Ron (Vref) & TxEq in the region [Start, Stop].
  4. Center Cmd Timing.
  5. Center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcCmdDsTxEq (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { CmdV, CmdT };
  static const UINT8  Scale[] = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptCmdDS, OptCmdTxEq };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                Start[2];
  INT8                Stop[2];
  UINT32              CompCode;
  UINT32              CompCodeGb;
  UINT32              CmddrvVrefConst;
  INT64               GetSetVal;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  MrcGetSetDdrIoGroupController0 (MrcData, WrDSCodeUpCmd, ReadUncached, &GetSetVal); // Read Cmd DS Comp Code Value

  CmddrvVrefConst = 48;
  CompCodeGb = 3;
  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0] = OptParamLimitValue (MrcData, OptParam[0], 1);
  // Find the minimal and maximal CMD Ron Vref that does not overflow the Comp Code.
  // Search is performed by initializing the read Comp code to a saturated value
  // in order to ensure entry to while loop.
  CompCode = 0; // Set CompCode to a saturated value

  // 1. Find the minimal Drive Strength that doesn't overflow the Comp Code
  while ((CompCode > 63 - CompCodeGb) || (CompCode < CompCodeGb)) { // While comp is saturated
    Start[0]++; // Start from 1/4 Vdd (48)
    CompCode = UpdateCompGlobalOffset (MrcData, WrDSCmd, (UINT32)(CmddrvVrefConst + 4 * Start[0]), FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD Ron Vref: %d, CompCode: %d\n", CmddrvVrefConst + 4 * Start[0], CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Start Search region for Cmd WrDs Code: %d, CompCode: %d\n", Start[0], CompCode);

  // 2. Find the maximal Drive Strength that doesn't overflow the Comp Code
  CompCode = 64; // Set CompCode to a saturated value
  while ((CompCode > 63 - CompCodeGb) || (CompCode < CompCodeGb)) { // While comp is saturated
    Stop[0]--; // Start from 3/4 Vdd (134)
    CompCode = UpdateCompGlobalOffset (MrcData, WrDSCmd, (UINT32)(CmddrvVrefConst + 4 * Stop[0]), FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD Ron Vref: %d, CompCode: %d\n", CmddrvVrefConst + 4 * Stop[0], CompCode);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Stop Search region for Cmd WrDs Code: %d, CompCode: %d\n", Stop[0], CompCode);
  // 3. Restore Cmd DS Comp value
  MrcGetSetDdrIoGroupController0 (MrcData, WrDSCodeUpCmd, WriteUncached, &GetSetVal);

  // For TxEq simply using the Codes defined in OptParamLimitValue
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1] = OptParamLimitValue (MrcData, OptParam[1], 1);

  TrainDDROptParam(
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,  // Start
    Stop,   // Stop
    12,     // Loopcount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // Pattern
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center
  Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  if (Status != mrcSuccess) {
    return Status;
  }
  Status = MrcCmdVoltageCentering (MrcData);
  return Status;
}
