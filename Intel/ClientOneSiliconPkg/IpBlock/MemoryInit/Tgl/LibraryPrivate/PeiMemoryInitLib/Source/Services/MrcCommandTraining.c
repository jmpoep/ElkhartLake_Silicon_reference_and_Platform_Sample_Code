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
#include "MrcCpgcApi.h"
#include "Cpgc20Patterns.h"
#include "Cpgc20TestCtl.h"
#include "MrcCpgcOffsets.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcLpddr5.h"
#include "MrcChipApi.h"
#include "MrcCommon.h"

#define CAPATTERNMASK (0xFF)
#define FEEDBACKMASKLP4 (0xFF)
#define FEEDBACKMASKLP5 (0x7F)
#define MAX_CBT_PHASES (2)

/**
  This function performs early command training.
  Center CTL-CLK timing to allow subsequent steps to work

  @param[in] MrcData - Include all MRC global data.
**/
MrcStatus
MrcEarlyCommandTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput        *Outputs;

  Outputs        = &MrcData->Outputs;

  // Check if LPDDR memory is used
  if (Outputs->Lpddr) {
    return EarlyCommandTrainingLpddr (MrcData);
  }
  return mrcSuccess;
}

/**
  Find a good starting point for DDR3/4 CTL/CMD/CLK, using a quick 2D search.
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
  INT64               Min;
  INT64               Max;
  UINT32              Left[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              Right[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              Width[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              MaxWidth[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16              BestCtlPi[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16              BestCtlPiLast[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              Controller;
  UINT32              Channel;
  UINT8               McChBitMask;
  UINT8               RankMask;
  UINT8               ResultRank[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8               Rank;
  UINT16              CtlPiCode;
  UINT16              CtlLow;
  UINT16              CtlHigh;
  UINT8               CtlStep;
  INT16               ClkLow;
  UINT16              ClkHigh;
  UINT8               ClkStep;
  UINT8               MaxChannels;
  BOOLEAN             SkipVref;
  BOOLEAN             SkipPrint;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  Status         = mrcSuccess;
  MaxChannels    = Outputs->MaxChannels;
  MrcCall->MrcSetMem ((UINT8 *) Left, sizeof (Left), 0);
  MrcCall->MrcSetMem ((UINT8 *) Right, sizeof (Right), 0);
  MrcCall->MrcSetMem ((UINT8 *) Width, sizeof (Width), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestCtlPi, sizeof (BestCtlPi), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestCtlPiLast, sizeof (BestCtlPiLast), 0);
  MrcCall->MrcSetMem ((UINT8 *) ResultRank, sizeof (ResultRank), 0);

  MrcGetSetLimits (MrcData, ClkGrpPi, &Min, &Max, NULL);
  ClkLow  = (UINT16) (Min + 64); // No need to sweep full Clk range
  ClkHigh = (UINT16) ClkLow + 128;
  ClkLow  = (UINT16) MAX (ClkLow, Min);
  ClkHigh = (UINT16) MIN (ClkHigh, Max);
  CtlLow  = (UINT16) (Min + 32);  // keep 32 ticks on each side for later margining steps.
  CtlHigh = (UINT16) (Max - 32);
  CtlStep = 16;

  RankMask = Outputs->ValidRankMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & ControllerOut->Channel[Channel].ValidRankBitMask) {  // Pick one rank to get the results from
          ResultRank[Controller][Channel] = Rank;
          break;
        }
      } // Rank
    } // Channel
  } // Controller

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Clock Timing per rank\n");
  // Setup CPGC Test to iteration through appropriate ranks during test
  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, (UINT8) Controller, (UINT8) Channel, RankMask, FALSE, 0);
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tMc%uCh%u\t\t", Controller, Channel);
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tLeft\tRight\tWidth", Controller, Channel);
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  SkipVref  = TRUE;
  SkipPrint = TRUE;
  MrcCall->MrcSetMem ((UINT8 *) MaxWidth, sizeof (MaxWidth), 0);

  for (CtlPiCode = CtlLow; CtlPiCode <= CtlHigh; CtlPiCode += CtlStep) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t", CtlPiCode);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          // Shift both CTL and CMD
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl,  RankMask, MRC_IGNORE_ARG_8, CtlPiCode, 1);
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd,  MRC_IGNORE_ARG_8, 0xF, CtlPiCode, 1);  //0xF = All 4 Cmd Groups
        }
      }
    }

    ClkStep = 6;
    CmdLinearFindEdges (MrcData, MrcIterationClock, McChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, SkipPrint, SkipVref);

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if ((MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) == 0) {
          if (Channel == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t");
          }
          continue;
        }
        Rank = ResultRank[Controller][Channel];
        Left[Controller][Channel]  = Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][0] / 10;
        Right[Controller][Channel] = Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][1] / 10;
        Width[Controller][Channel] = Right[Controller][Channel] - Left[Controller][Channel];
        if (Width[Controller][Channel] > MaxWidth[Controller][Channel]) {
          MaxWidth[Controller][Channel] = Width[Controller][Channel];
          BestCtlPi[Controller][Channel] = BestCtlPiLast[Controller][Channel] = CtlPiCode;
        } else if (Width[Controller][Channel] == MaxWidth[Controller][Channel]) { // Track the last PI which still gives the max width
          BestCtlPiLast[Controller][Channel] = CtlPiCode;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t%u\t%u\t", Left[Controller][Channel], Right[Controller][Channel], Width[Controller][Channel]);
      } // channel
    } // Controller
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // for CtlPiCode

  // Apply the best CTL/CMD PI and re-center the CLK
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
        CtlPiCode = (BestCtlPi[Controller][Channel] + BestCtlPiLast[Controller][Channel]) / 2;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u: Ch%u: Best CTL/CMD PI is %u, CLK width = %u\n",
                       Controller, Channel, CtlPiCode, MaxWidth[Controller][Channel]);
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, CtlPiCode, 1);
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CtlPiCode, 1);  //0xF = All 4 Cmd Groups
      }
    } // Channel
  } // Controller
  SkipPrint = FALSE;
  ClkStep = 4;
  Status = CmdLinearFindEdges (MrcData, MrcIterationClock, McChBitMask, RankMask, 3, ClkLow, ClkHigh, ClkStep, 1, (INT8 *) NULL, SkipPrint, SkipVref);

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
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcStatus           Status;
  MrcProfile          Profile;
  INT64               GetSetVal;
  UINT32              Controller;
  UINT32              Channel;
  UINT32              MinCode;
  UINT16              CmdPiCode[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16              CtlPiCode[MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL];
  UINT16              MidPointCmd[MAX_COMMAND_GROUPS][MAX_CONTROLLER][MAX_CHANNEL];
  UINT8               Byte;
  UINT8               Loopcount;
  UINT8               Cmd2N;
  UINT8               McChBitMask;
  UINT8               RankMask;
  UINT8               Rank;
  UINT8               Ranks;
  UINT8               CmdGroup;
  UINT8               CmdGroupMax;
  BOOLEAN             Lpddr;
  BOOLEAN             Ddr4;
  BOOLEAN             ExitOnFailure;
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Profile       = Inputs->MemoryProfile;
  ExitOnFailure = (Inputs->ExitOnFailure == TRUE);
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Lpddr         = Outputs->Lpddr;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  CmdGroupMax = (Ddr4) ? MAX_COMMAND_GROUPS : 1;

  RankMask  = Outputs->ValidRankMask;
  McChBitMask = 0;

  Loopcount = 10;

  if (Outputs->DdrType != MRC_DDR_TYPE_LPDDR5) {
    MrcBlockTrainResetToggle (MrcData, FALSE);
  }

  // Setup CPGC
  // LC = 10, SOE = 1 (NTHSOE), EnCADB = 1, EnCKE = 0
  SetupIOTestCADB (MrcData, Outputs->McChBitMask, Loopcount, NTHSOE, 1, 0);

  // Program default rank mapping
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, (UINT8)Controller, (UINT8)Channel, RankMask, FALSE, 0);
      }
    }
  } // Controller

  if (!Lpddr) {
    Cmd2N = FALSE;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++)  {
      // Set initial Pi Values
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];
        if (MrcChannelExist(MrcData, Controller, Channel)) {
          Cmd2N = (ChannelOut->Timing[Profile].NMode == 2) ? TRUE : FALSE;
          CmdPiCode[Controller][Channel] = (Cmd2N == TRUE) ? 149 : 128;
          // all ranks are initialized with the same value so use only Rank 0 here
          CtlPiCode[0][Controller][Channel] = 128;
          MRC_DEBUG_MSG(
             Debug,
             MSG_LEVEL_NOTE,
             "Mc%u, Ch%u, Cmd2N =%d, CmdPiCode = %d, McChBitMask = 0x%x\n",
             Controller,
             Channel,
             Cmd2N,
             CmdPiCode[Controller][Channel],
             McChBitMask
             );
          // Shift everything to the right.  To get DQ timing right, program Clk to 0
          ShiftPIforCmdTraining (
            MrcData,
            Controller,
            Channel,
            MrcIterationClock,
            ChannelOut->ValidRankBitMask,
            1,
            0 - (INT32) (IntCmdTiming->ClkPiCode[0]),
            1
            );
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CmdPiCode[Controller][Channel], 1);  //0xF = All 4 Cmd Groups
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, ChannelOut->ValidRankBitMask, MRC_IGNORE_ARG_8, CtlPiCode[0][Controller][Channel], 1);
        }
      }
    } // Controller
  } // if (!Lpddr)

  // Get the new midpoint for CMD
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    IntControllerOut = &IntOutputs->Controller[Controller];
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (MrcChannelExist(MrcData, Controller, Channel)) {
        IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
        for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
          MidPointCmd[CmdGroup][Controller][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Mc%u: C%u: CmdGroup%u Pi Code: %d\n",
            Controller,
            Channel,
            CmdGroup,
            MidPointCmd[CmdGroup][Controller][Channel]
            );
        }
      }
    } // Channel
  } // Controller

  if (Lpddr) {
    // Center Command Timing
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CMD Pi Timing\n");

    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, 1, MidPointCmd[0]);
    if ((Status != mrcSuccess) && (ExitOnFailure)) {
      return Status;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center Control Timing\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** ECT results \n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      IntControllerOut = &IntOutputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist(MrcData, Controller, Channel)) {
          IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if ((MRC_BIT0 << Rank) & RankMask) {
              CtlPiCode[Rank][Controller][Channel] = IntCmdTiming->CtlPiCode[Rank];
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ctl%uCh%uRank%u: CTL: %u\n", Controller, Channel, Rank, CtlPiCode[Rank][Controller][Channel]);
            }
          }
        }
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCentering CTL on Ranks 0x%x\n", RankMask);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Ranks = (MRC_BIT0 << Rank);
      Ranks = Ranks & RankMask;
      if (Ranks) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n Rank 0x%x\n", Rank);
        Status = CmdTimingCentering (MrcData, MrcIterationCtl, Ranks, MRC_IGNORE_ARG_8, CtlPiCode[Rank]);
        if ((Status != mrcSuccess) && (ExitOnFailure)) {
          return Status;
        }
      }
    } // Rank loop
  } else { // not Lpddr4
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Center CMD/CTL vs. CLK\n");
    // Center CMD/CTL vs. CLK
    Status = CtlClockCentering (MrcData);
    if ((Status != mrcSuccess) && ExitOnFailure) {
      return Status;
    }

    // Get the new midpoint for CMD and CTL
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      IntControllerOut = &IntOutputs->Controller[Controller];
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (MrcChannelExist(MrcData, Controller, Channel)) {
          IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if ((MRC_BIT0 << Rank) & RankMask) {
              CtlPiCode[Rank][Controller][Channel] = IntCmdTiming->CtlPiCode[Rank];
              MRC_DEBUG_MSG(
                   Debug,
                   MSG_LEVEL_NOTE,
                   "Mc%u, C%u, Rank%u, CtlPiCode : %d\n",
                   Controller,
                   Channel,
                   Rank,
                   CtlPiCode[Rank][Controller][Channel]
                   );
            }
          } // Rank
          for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
            MidPointCmd[CmdGroup][Controller][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
            MRC_DEBUG_MSG(
               Debug,
               MSG_LEVEL_NOTE,
               "Mc%u, C%u, CmdGroup%u, Pi Code: %d\n",
               Controller,
               Channel,
               CmdGroup,
               MidPointCmd[CmdGroup][Controller][Channel]
               );
          } // CmdGroup
        }
      }
    }

    // Center Command Timing
    for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center Cmd Group %u PI Timing\n", CmdGroup);
      Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << CmdGroup), MidPointCmd[CmdGroup]);
      if ((Status != mrcSuccess) && (ExitOnFailure)) {
        return Status;
      }
    }

    // Center Control Timing.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center Control Timing.");
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Ranks = (1 << Rank);
      Ranks = Ranks & RankMask;

      if (Ranks) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n Rank %d\n", Rank);
        Status = CmdTimingCentering (MrcData, MrcIterationCtl, Ranks, MRC_IGNORE_ARG_8, CtlPiCode[Rank]);
        if ((Status != mrcSuccess) && (ExitOnFailure)) {
          return Status;
        }
      }
    }
  } // else not Lpddr4

  // Normalize timing back to 0 to improve performance
  if (Ddr4) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n*** Normalize timing back to 0\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      IntControllerOut = &IntOutputs->Controller[Controller];
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
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
          if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
            // Cke PI
            MinCode = MIN (MinCode, IntCmdTiming->CkePiCode[Rank]);
            // Ctl PI
            MinCode = MIN (MinCode, IntCmdTiming->CtlPiCode[Rank]);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MrcGetSetStrobe(MrcData, Controller, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
              MinCode = MIN (MinCode, (UINT32) GetSetVal);
              MrcGetSetStrobe(MrcData, Controller, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
              MinCode = MIN (MinCode, (UINT32) GetSetVal);
              MrcGetSetStrobe(MrcData, Controller, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
              MinCode = MIN (MinCode, (UINT32) GetSetVal);
            }
          }
        }

        if (MinCode >= 32) {
          MinCode = MIN (MinCode, MinCode - 32);  // Keep at least 32 PI ticks for margining.
        } else {
          MinCode = 0;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d C%d: shifting all PI settings by Min PI Code = %d\n", Controller, Channel, MinCode);
        // Don't do final shifting as CLK cannnot be shifted in CTE
        ShiftChannelTiming (MrcData, Controller, Channel, (-1) * MinCode);
      } // for Channel
    } // for Controller
  } // Ddr4

  // Disable CADB Deselects after Command Training
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);


  // Finish Training with JEDEC Reset / Init
  Status = MrcResetSequence (MrcData);

  if (Outputs->DdrType != MRC_DDR_TYPE_LPDDR5) {
    MrcBlockTrainResetToggle (MrcData, TRUE);
  }

  return Status;
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
  const MrcInput *Inputs;
  MrcDebug       *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput      *Outputs;
  MrcChannelOut  *ChannelOut;
  MrcStatus      Status;
  UINT16         *Margin;
  UINT8          LoopCount;
  UINT8          Controller;
  UINT8          Channel;
  UINT8          Rank;
  UINT8          Byte;
  UINT8          RankMask;
  UINT8          MaxChannels;
  UINT16         Low[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16         High[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32         Height;
  UINT16         MinHeight;
  INT16          Center[MAX_CONTROLLER][MAX_CHANNEL];
  BOOLEAN        GetBerMargin;
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MaxChannels = Outputs->MaxChannels;
  LoopCount = 10;
  Status    = mrcSuccess;
  GetBerMargin  = FALSE;
  MrcCall->MrcSetMem ((UINT8 *) Low, sizeof (Low), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) High, sizeof (High), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) Center, sizeof (Center), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Cmd Vref Training with LC = %d\n", LoopCount);
  Status = DQTimeCentering1D (
            MrcData,
            CmdV,
            0,          // ResetPerBit
            LoopCount,
            TRUE,       // MsgPrint
            FALSE       // EarlyCentering
            );

  // Find center value and program it
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist(MrcData, Controller, Channel, Rank)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Margin = &Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][Byte][0];
            Low[Controller][Channel] = MIN(Low[Controller][Channel], Margin[0]);
            High[Controller][Channel] = MIN(High[Controller][Channel], Margin[1]);
            if (GetBerMargin) {
              break;  // GetBerMarginCh() stores results in rank 0 byte 0
            }
          } // for Byte
        } // MrcRankExist
        if (GetBerMargin) {
          break;  // GetBerMarginCh() stores results in rank 0 byte 0
        }
      } // for Rank
    } // Channel
  } // Controller


  // Print per-channel results summary
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd Vref Summary:\n\tLow\tHigh\tHeight\tCenter\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist(MrcData, Controller, Channel)) {
        MRC_DEBUG_MSG(
           Debug,
           MSG_LEVEL_NOTE,
           "Mc%u.C%u:\t%u\t%u\t%u\t%d\n",
           Controller,
           Channel,
           Low[Controller][Channel] / 10,
           High[Controller][Channel] / 10,
           (Low[Controller][Channel] + High[Controller][Channel]) / 10,
           ((INT32)(High[Controller][Channel] - Low[Controller][Channel])) / 20
           );
      } // MrcChannelExist
    } // for Channel
  } // Controller


  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist(MrcData, Controller, Channel)) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        RankMask = ChannelOut->ValidRankBitMask;
        Center[Controller][Channel] = (High[Controller][Channel] - Low[Controller][Channel]) / 2;
        ChangeMargin(MrcData, CmdV, Center[Controller][Channel] / 10, 0, 0, Controller, Channel, RankMask, 0, 0, 1, 0);
      }
    } // Channel
  } // Controller

  MrcResetSequence (MrcData);

  // Check UPM limits
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist(MrcData, Controller, Channel)) {
        // Get Min Height from 1/2 WrV UPM Limit.
        MinHeight = MrcGetUpmPwrLimit(MrcData, WrV, UpmLimit) / 2;   // 1/2 WrV UPM Limit
        Height = Low[Controller][Channel] + High[Controller][Channel];
        if (Height < MinHeight) {
          MRC_DEBUG_MSG(
             Debug,
             MSG_LEVEL_ERROR,
             "\nERROR! MC%u.Ch%u - Height region (%d) less than expected value (%d)\n",
             Controller,
             Channel,
             Height / 10,
             MinHeight / 10
             );
          if (Inputs->ExitOnFailure) {
            return mrcMiscTrainingError;
          }
        }
      } // MrcChannelExist
    } // for Channel
  } // Controller


  // Update MrcData for future tests
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;  // No such rank
        }
        Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][0] = Low[Controller][Channel] + Center[Controller][Channel];
        Outputs->MarginResult[LastCmdV][Rank][Controller][Channel][0][1] = High[Controller][Channel] - Center[Controller][Channel];
      } // Rank
    } // Channel
  } // Controller

  // Disable CADB Deselects
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  return Status;
}

/**
  Centers Command Timing around a MidPoint

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Iteration       - Determines which PI to shift
  @param[in] Ranks           - Valid Rank bit mask
  @param[in] GroupMask       - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
  @param[in] MidPoint        - The MidPoint to center around (per channel)

  @retval Nothing
**/
MrcStatus
CmdTimingCentering (
  IN MrcParameters *const MrcData,
  IN UINT8                Iteration,
  IN UINT8                Ranks,
  IN UINT8                GroupMask,
  IN UINT16               MidPoint[MAX_CONTROLLER][MAX_CHANNEL]
  )
{
  const MrcInput     *Inputs;
  MrcDebug           *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput          *Outputs;
  MrcStatus          Status;
  INT64              Min;
  INT64              Max;
  UINT16             Ledge[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16             Redge[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16             Mid[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16             Low[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16             High[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16             PiLow;
  UINT16             PiHigh;
  static const INT8  VrefOffsets[2] = {-8, 8};
  UINT16             Center;
  UINT8              McChBitMask;
  UINT8              RankMask;
  UINT8              Controller;
  UINT8              Channel;
  UINT8              MinWidth = 18;
  UINT16             lWidth;
  BOOLEAN            SkipVref;

  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  Status         = mrcSuccess;
  MrcCall->MrcSetMem ((UINT8 *) Ledge, sizeof (Ledge), 0);
  MrcCall->MrcSetMem ((UINT8 *) Redge, sizeof (Redge), 0);

  // get the sweep limits
  MrcGetSetLimits (MrcData, CmdGrpPi, &Min, &Max, NULL);
  PiLow     = (UINT16) Min;
  PiHigh    = (UINT16) Max;

#ifdef MRC_DEBUG_PRINT
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tMc%uCh%u",Controller, Channel);
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
#endif // MRC_DEBUG_PRINT

  if (NULL == MidPoint) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Midpoint[] parameter is NULL!\n");
    return mrcWrongInputParameter;
  }

  // Setup CPGC Test to iteration through appropriate ranks during test
  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (MrcChannelExist (MrcData, Controller, Channel)) {
          McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, Ranks, FALSE, 0);
          Mid[Controller][Channel] = MidPoint[Controller][Channel];
        }
      } // channel
    }
  } // Controller

  // Binary search will use the full PI range of [0..255(G1) or 511(G2)]
  MrcCall->MrcSetMemWord ((UINT16 *)Low, sizeof (Low) / sizeof (UINT16), PiLow);
  MrcCall->MrcSetMemWord ((UINT16 *)High, sizeof (High) / sizeof (UINT16), PiHigh);

  if (Iteration == MrcIterationClock) {
    // Use a linear search to center clock and Update Clock Delay/Host
    // Allow wrap around since this is clock
    // CmdLinearFindEdges also programs the new values
    SkipVref = FALSE;
    Status = CmdLinearFindEdges (MrcData, Iteration, McChBitMask, Ranks, GroupMask, (INT16) PiLow, (UINT16) PiHigh, 6, 1, (INT8 *) VrefOffsets, FALSE, SkipVref);
  } else {
    CmdBinaryFindEdge (MrcData, Iteration, McChBitMask, Ranks, GroupMask, Low, Mid, 0, (INT8 *) VrefOffsets);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
          Ledge[Controller][Channel] = Mid[Controller][Channel]; // CountUp is 0 so return High.
          Mid[Controller][Channel]   = MidPoint[Controller][Channel]; //Mid Modified by CmdBinaryFindEdge
        }
      }
    }
    CmdBinaryFindEdge (MrcData, Iteration, McChBitMask, Ranks, GroupMask, Mid, High, 1, (INT8 *) VrefOffsets);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
          Redge[Controller][Channel] = Mid[Controller][Channel];  // CountUp is 1 so return Low.
        }
      }
    } // Controller
    // Update Variables:
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMc\tCh\tLeft\tRight\tWidth\tCenter");

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if ((MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, Outputs->MaxChannels)) == 0) {
          continue;
        }
        RankMask  = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
        lWidth    = Redge[Controller][Channel] - Ledge[Controller][Channel];

        if ((Redge[Controller][Channel] == PiHigh) && (Ledge[Controller][Channel] == PiLow)) {
          // No errors found
          Center = MidPoint[Controller][Channel];
        } else {
          Center = (Ledge[Controller][Channel] + Redge[Controller][Channel] + 1) / 2;
          if (lWidth < MinWidth) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nEye < %u for Mc%u C%u!\n", MinWidth, Controller, Channel);
            Status = mrcMiscTrainingError;
          }
        }

        ShiftPIforCmdTraining (MrcData, Controller, Channel, Iteration, RankMask, GroupMask, Center, 1);

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\n %d\t%d\t%d\t%d\t%d\t%d\n",
          Controller,
          Channel,
          Ledge[Controller][Channel],
          Redge[Controller][Channel],
          lWidth,
          Center
          );
      } // for Channel
    } // for Controller
  }

  IoReset (MrcData);

  return Status;
}

#if 0
/**
  Plot CmdT (linear CLK shift) vs CmdV, used for debug of DDR3/4.

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
  UINT8                LCTStep = 3;
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
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  GroupMask = 3;
  chBitMaskToRun = 0x3;
  CmdLoopCount = 10;

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
    SetupIOTestCADB (MrcData, Outputs->McChBitMask, CmdLoopCount, NSOE, 1, 0);

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
              //@todo - 2MC
              ShiftPIforCmdTraining (MrcData, CONTROLLER_0, Channel, MrcIterationClock, RankMask, GroupMask, LCTDelay, 0);
            }
          }
          Status = MrcResetSequence (MrcData);  // Reset DDR
          ChangeMargin (MrcData, CmdV, Vref, 0, 0, /**Controller**/ 0, ChToPlot, ChannelOut->ValidRankBitMask, 0, 0, 0, 0);
          ChError = RunIOTest (MrcData, /**McBitMask**/ 1, chBitMaskToRun, Outputs->DQPat, 1, 0);

//          FailCount = 0;
//          for (Test = 1; Test <= 3; Test++) {
//            ChError = RunIOTest (MrcData, /**McBitMask**/ 1, ChannelMask, Outputs->DQPat, 1, 0);
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
      ChangeMargin (MrcData, CmdV, 0, 0, 0, /**Controller**/ 0, Channel, ChannelOut->ValidRankBitMask, 0, 0, 0, 0);
      if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
        //@todo - 2MC
        ShiftPIforCmdTraining (MrcData, CONTROLLER_0, Channel, MrcIterationClock, RankMask, 3, 0, 0);
      }
    }
  } // for Rank
  // Disable CADB deselects
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  Status = MrcResetSequence (MrcData);
  return Status;
}

#endif // if 0

/**
  Use a linear search to find the edges between Low and High
  if WrapAround = 0: Look for largest passing region between low and high
  if WrapAround = 1: Look for largest passing region, including wrapping from high to low

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      chBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
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
  IN     UINT8                McChBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN     INT16                Low,
  IN     UINT16               High,
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
  MrcDebugMsgLevel   DebugLevel;
  INT32             *IPStart;
  INT32             *IPEnd;
  INT32             *CPStart;
  INT32             *CPEnd;
  INT32             *LPStart;
  INT32             *LPEnd;
  MrcStatus         Status;
  BOOLEAN           Pass;
  BOOLEAN           ExitOnFailure;
  INT32             InitialPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             InitialPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             lWidth;
  INT32             iWidth;
  INT32             cWidth;
  INT32             Center;
  INT16             LCTDelay;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             CurMcChMask;
  UINT8             RankMask;
  UINT8             Rank;
  UINT16            LCTStep;
  UINT16            LastStep;
  UINT8             Vloop;
  UINT8             VoltageLoopCount;
  UINT8             McChError;
  INT8              Vref;
  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  lWidth        = 0;
  iWidth        = 0;
  cWidth        = 0;
  DebugLevel = SkipPrint ? MSG_LEVEL_NEVER : MSG_LEVEL_NOTE;
  ExitOnFailure = FALSE;

  LCTStep = Step;
  VoltageLoopCount  = 2;

  MRC_DEBUG_MSG (Debug, DebugLevel, "\nCLkDlay\t");

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "Mc%dCh%d\t", Controller, Channel);
      }
    } // channel
  } // Controller

  for (LCTDelay = Low; LCTDelay <= High; LCTDelay += LCTStep) {
    // Update Timing
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, Outputs->MaxChannels)) {
          RankMask = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
          ShiftPIforCmdTraining(MrcData, Controller, Channel, Iteration, RankMask, GroupMask, LCTDelay, 0);
        }
      } // channel
    } // Controller

    // Reset DDR
    Status = MrcResetSequence (MrcData);

    // Run CPGC until both channels fail or we finish all Vref points
    if (SkipVref) {
      McChError = RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);
    } else {
      McChError = 0;
      for (Vloop = 0; Vloop < VoltageLoopCount; Vloop++) {
        Vref = VrefOffsets[Vloop];
        ChangeMargin (MrcData, CmdV, Vref, 0, 1, 0, 0, 0, 0, 0, 0, 0);

        McChError |= RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);

        if (McChError == McChBitMask) {
          break;
        }
      } // Vloop
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n %d\t", LCTDelay);

    // Update Passing Variables
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++){
      if (MrcControllerExist (MrcData, Controller)) {
        for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
          CurMcChMask = (MRC_BIT0 << ((Controller * Outputs->MaxChannels) + Channel));
          if (!(CurMcChMask & McChBitMask)) {
            MRC_DEBUG_MSG (Debug, DebugLevel, (Channel == 0) ? "  " : "");
            continue;
          }

          Pass = !(McChError & CurMcChMask);

          MRC_DEBUG_MSG (Debug, DebugLevel, Pass ? "  .\t" : "  #\t");

          IPStart = &InitialPassingStart[Controller][Channel];
          IPEnd   = &InitialPassingEnd[Controller][Channel];
          CPStart = &CurrentPassingStart[Controller][Channel];
          CPEnd   = &CurrentPassingEnd[Controller][Channel];
          LPStart = &LargestPassingStart[Controller][Channel];
          LPEnd   = &LargestPassingEnd[Controller][Channel];

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
      }
    } // for Controller
  } // for LCTDelay

  MRC_DEBUG_MSG (Debug, DebugLevel, "\nMC\tCH\tLeft\tRight\tWidth\tCenter\n");

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if ((MRC_BIT0 << ((Controller * Outputs->MaxChannels) + Channel)) & McChBitMask) {
        LPStart = &LargestPassingStart[Controller][Channel];
        LPEnd   = &LargestPassingEnd[Controller][Channel];
        lWidth  = *LPEnd - *LPStart;
        Center = (*LPEnd + *LPStart) / 2;
        if ((lWidth < (3 * LCTStep)) || (lWidth >= (High - Low))) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "\nERROR! Bad command eye width: %u\n", lWidth);
          if (lWidth == 0) {
            *LPStart = *LPEnd = 0;
          }
          if (Inputs->ExitOnFailure) {
            ExitOnFailure = TRUE;
          }
        }
        RankMask = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
        if (!SkipPrint) {
          // Shift Timing
          ShiftPIforCmdTraining (MrcData, Controller, Channel, Iteration, RankMask, GroupMask, Center, 1);
          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            " %d\t%d\t%d\t%d\t%d\t%d\n",
            Controller,
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
            Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][0] = (UINT16) (10 * ABS (*LPStart));
            Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][1] = (UINT16) (10 * ABS (*LPEnd));
          }
        } // Rank loop
      }
    } // Channel loop
  } // Controller loop

  if (ExitOnFailure) {
    return mrcMiscTrainingError;
  }

  // Clean Up
  if (!SkipVref) {
    ChangeMargin (MrcData, CmdV, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
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
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR3
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
  IN     UINT8                McChBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN OUT UINT16               (*Low)[MAX_CHANNEL],
  IN OUT UINT16               (*High)[MAX_CHANNEL],
  IN     UINT8                CountUp,
  IN     INT8                 *VrefOffsets
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  UINT16            Target[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8             Done;
  UINT8             McChError;
  INT8              Vref;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             MaxChannels;
  UINT8             CurMcChMask;
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
  MaxChannels   = Outputs->MaxChannels;
  Done          = 0;
  McChError     = 0;
  MrcCall->MrcSetMem ((UINT8 *) Target, sizeof (Target), 0);

  SkipWait          = FALSE;
  VoltageLoopCount  = 2;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Pi Delay\n");
  while (!Done) {
    // Update Timing
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          Target[Controller][Channel] = (High[Controller][Channel] + Low[Controller][Channel] + CountUp) / 2;    // CountUp gets rounding correct
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", Target[Controller][Channel]);
          RankMask = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
          for (Group = 0; Group < MAX_COMMAND_GROUPS; Group++) {
            if ((1 << Group) & GroupMask) {
              ShiftPIforCmdTraining (MrcData, Controller, Channel, Iteration, RankMask, 1 << Group, Target[Controller][Channel], 0);
            }
          } // Group
        }
      } // Channel
    } // Controller

    IoReset (MrcData);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    // Run CPGC until both channels fail or we finish all Vref points
    McChError = 0;
    for (Vloop = 0; Vloop < VoltageLoopCount; Vloop++) {
      Vref = VrefOffsets[Vloop];
      ChangeMargin (MrcData, CmdV, Vref, 0, 1, 0, 0, 0, 0, 0, 0, SkipWait);
      McChError |= RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);
      if (McChError == McChBitMask) {
        break;
      }
    }

    // Update High/Low
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        CurMcChMask = (1 << ((Controller * MaxChannels) + Channel));
        if (CurMcChMask & McChBitMask) {
          Fail = (McChError & CurMcChMask);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, Fail ? "\t#" : "\t.");
          // Skip if this channel is done
          if (High[Controller][Channel] > Low[Controller][Channel]) {
            if (CountUp) {
              if (Fail) {
                High[Controller][Channel] = Target[Controller][Channel] - 1;
              } else {
                Low[Controller][Channel] = Target[Controller][Channel];
              }
            } else {
              if (Fail) {
                Low[Controller][Channel] = Target[Controller][Channel] + 1;
              } else {
                High[Controller][Channel] = Target[Controller][Channel];
              }
            }
          }
        }
      } // Channel
    } // Controller

    if ((McChError & McChBitMask) != 0) {
      // Perform JEDEC Reset/Init if at least one of the channels failed this PI iteration
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Failed, doing JEDEC Reset..\n");
      MrcResetSequence (MrcData);
    }

    // Update Done
    Done = 1;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          if (High[Controller][Channel] > Low[Controller][Channel]) {
            Done = 0;
          }
        }
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  // Clean Up
  ChangeMargin (MrcData, CmdV, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
  MrcResetSequence (MrcData);
  return;
}

/**
  Shift the CLK/CMD/CTL Timing by the given PI setting value
  CLK shift will also change RcvEn / TxDq / TxDqs.
  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to update.
  @param[in] Channel    - Channel to shift
  @param[in] Offset     - Offset to shift by

  @retval Nothing
**/
void
ShiftChannelTiming (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN INT32                Offset
  )
{
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  INT32               NewCode;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               Group;
  UINT8               MaxGroup;
  BOOLEAN             Ddr;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntCmdTiming  = &IntOutputs->Controller[Controller].CmdTiming[Channel];
  Ddr           = !MrcData->Outputs.Lpddr;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d Channel %d new values:\n", Controller, Channel);
  // Shift the CLK/CTL Timing
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tCTL\tCLK");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n R%d", Rank);
      RankBit = 1 << Rank;

      NewCode = (INT32) (IntCmdTiming->CtlPiCode[Rank]) + Offset;
      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankBit, MRC_IGNORE_ARG_8, NewCode, 1);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", NewCode);

      if ((Rank == 0) || (Ddr)) {
        // CLK is per Rank in DDR, and only 1 Clock per Channel in LPDDR
        NewCode = (INT32) (IntCmdTiming->ClkPiCode[Rank]) + Offset;
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationClock, RankBit, MRC_IGNORE_ARG_8, Offset, 1);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", NewCode);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }

  // Shift the CMD Timing
  MaxGroup = (Ddr) ? MAX_COMMAND_GROUPS : 1;
  for (Group = 0; Group < MaxGroup; Group++) {
    NewCode = (INT32) IntCmdTiming->CmdPiCode[Group] + Offset;
    ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, (1 << Group), NewCode, 1);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " New CMD[%d] value = %d\n", Group, NewCode);
  }

  return;
}

/**
  This function updates Command Mode register, tXP and Roundtrip latency.
  This should only be called for DDR3/4.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - Controller to update.
  @param[in]      Channel     - Channel to update.
  @param[in]      OldN        - Old N Mode value.
  @param[in]      NewN        - New N mode value.

  @retval Nothing
**/
void
UpdateCmdNTiming (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Controller,
  IN     UINT32               Channel,
  IN     UINT8                OldN,
  IN     UINT8                NewN
  )
{
  MrcOutput     *Outputs;
  MrcTiming     *Timing;
  MrcDdrType    DdrType;
  INT64         CmdStretch;
  INT64         tXP;
  INT64         Diff;
  BOOLEAN       Lpddr;

  Outputs = &MrcData->Outputs;
  Timing  = &Outputs->Controller[Controller].Channel[Channel].Timing[MrcData->Inputs.MemoryProfile];
  DdrType = Outputs->DdrType;
  Lpddr   = Outputs->Lpddr;

  // If LPDDR, only update MC parameters on Even Channels.
  if ((Lpddr && ((Channel % 2) == 0)) || !Lpddr) {
    // Update Cmd NMode, till now we ran DDR4 at 3N (Gear1) or 2N (Gear2)
    // Command stretch:
    //   00 - 1N
    //   01 - 2N
    //   10 - 3N
    //   11 - N:1
    if (Timing->NMode == 1) {
      CmdStretch = Outputs->Gear2 ? 0 : 3;  // Use N:1 Mode in Gear1 and 1N mode in Gear2
    } else {
      CmdStretch = Timing->NMode - 1;
    }
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdStretch,  WriteNoCache | PrintValue, &CmdStretch);

    // Adjust tXP value - it depends on NMode
    // No frequency switching in DDR4 so we use Outputs->Frequency always.
    tXP     = tXPValue (DdrType, Timing->tCK);
    tXP     = RANGE (tXP, tXP_MIN, tXP_MAX);
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctXP, WriteCached | GSM_PRINT_VAL, &tXP);
  }

  // Adjust Roundtrip Latency and RxFIFO - it depends on NMode
  Diff = (NewN - OldN);
  // Pass system level channel to this parameter as it is treated like DDRIO training parameter.
  MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, RoundTripDelay, WriteOffsetCached | PrintValue, &Diff);
}

/**
  Force CKE values per rank.

  @param[in] MrcData      - MRC global data.
  @param[in] McChBitMask  - Bitmask of Controllers and Channels to work on.
  @param[in] CkeValue     - Bitmask of CKE values per rank. Bit0 = CKE0, Bit1 = CKE1 etc.

**/
VOID
MrcForceCkeValue (
  IN MrcParameters *const MrcData,
  IN UINT32               McChBitMask,
  IN INT64                CkeValue
  )
{
  MrcOutput           *Outputs;
  INT64   ValidCkeMask;
  UINT32  Controller;
  UINT32  Channel;
  UINT8   MaxChannel;
  BOOLEAN Lpddr;

  Outputs = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) && !(IS_MC_SUB_CH (Lpddr, Channel))) {
        ValidCkeMask = MrcData->Outputs.Controller[Controller].Channel[Channel].ValidRankBitMask;
        ValidCkeMask |= (MrcData->Outputs.Controller[Controller].Channel[Channel+1].ValidRankBitMask) << 2;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCkeOverride, WriteNoCache, &ValidCkeMask);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCkeOn, WriteNoCache, &CkeValue);
      }
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

CADB_LINE CadbLinesLp4[] = {
  { 0x00, 0x00, 0 },
  { 0x3F, 0x3F, 0 },
  { 0x2A, 0x2A, 1 },
  { 0x15, 0x15, 1 }
};

// CADB Lines here corrospond to CADB_BUF e.g. Line0 is programmed in CADB_BUF0
CADB_LINE CadbLinesLp5[] = {
  { 0x00, 0x00, 0 },
  { 0x7F, 0x7F, 0 },
  { 0x2A, 0x2A, 1 },
  { 0x55, 0x55, 1 },
  { 0x7F, 0x7F, 1 },
  { 0x00, 0x00, 1 }
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

// This is order of pattern we expect to see. Each value is 1/2 tCK wide
// 0,0,0,0,2A,7F,7F,7F,7F,7F,0,0 - Pattern
// 0,0,0,0, 2, 4, 1, 1, 1, 1,0,0 - CadbLines/CADB_BUF
UINT32 CadbMuxLp5RisingPattern2[] = {
  0x000003C0,
  0x00000010,
  0x00000020
};

// 0,0,0,0,55,7F,7F,7F,7F,7F,0,0 - Pattern
// 0,0,0,0, 3, 4, 1, 1, 1, 1,0,0 - CadbLines/CADB_BUF
UINT32 CadbMuxLp5RisingPattern3[] = {
  0x000003D0,
  0x00000010,
  0x00000020
};

// This is the order of pattern we expect to see. Each value is 1/2 tCK wide
// 0,0,0,0,0,2A,7F,7F,7F,7F,7F,0,0 - Pattern
// 0,0,0,0,5, 2, 1, 1, 1, 1, 1,0,0 - CadbLines/CADB_BUF
UINT32 CadbMuxLp5FallingPattern2[] = {
  0x000007D0,
  0x00000020,
  0x00000010
};

// 0,0,0,0,0,55,7F,7F,7F,7F,7F,0,0 - Pattern
// 0,0,0,0,5, 3, 1, 1, 1, 1, 1,0,0 - CadbLines/CADB_BUF
UINT32 CadbMuxLp5FallingPattern3[] = {
  0x000007F0,
  0x00000020,
  0x00000010
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
  @param[in] Rank       - rank to work on
  @param[in] CadbLines  - CADB lines to program
  @param[in] CadbCount  - Number of CADB lines to program
  @param[in] PatBuf     - Pattern buffer array.
**/
void
SetupCaTrainingCadb (
  IN MrcParameters  *const  MrcData,
  IN UINT32         Rank,
  IN CADB_LINE      *CadbLines,
  IN UINT32         CadbCount,
  IN UINT32         PatBuf[MRC_NUM_MUX_SEEDS]
  )
{
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  const MRC_FUNCTION  *MrcCall;
  MrcDdrType          DdrType;
  UINT32              i;
  UINT8               Cke[2];
  UINT8               Cs[2];
  UINT8               Odt;
  MRC_CA_MAP_TYPE     LpddrCmdAddr;
  UINT64_STRUCT       LpddrCadbPatternChunks[CADB_20_MAX_CHUNKS];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  DdrType = Outputs->DdrType;

  Odt = 0;
  MrcCall->MrcSetMem ((UINT8 *) Cke, sizeof (Cke), 0);
  MrcCall->MrcSetMem ((UINT8 *) Cs, sizeof (Cs), 0);
  MrcCall->MrcSetMem ((UINT8 *) LpddrCadbPatternChunks, sizeof (LpddrCadbPatternChunks), 0);

  for (i = 0; i < CadbCount; i++) {
    LpddrCmdAddr.Data32 = 0;
    Cs[0] = Cs[1] = (CadbLines[i].ChipSelect << Rank);
    if (DdrType == MRC_DDR_TYPE_LPDDR4) {
      LpddrCmdAddr.Lpddr4.Ca1 = CadbLines[i].CaLow;   // Ch 0
      LpddrCmdAddr.Lpddr4.Ca2 = CadbLines[i].CaHigh;  // Ch 1
    } else {
      LpddrCmdAddr.Lpddr5.Ca1 = CadbLines[i].CaLow;   // Ch 0
      LpddrCmdAddr.Lpddr5.Ca2 = CadbLines[i].CaHigh;  // Ch 1
    }
    CpgcConvertDdrToCadb (MrcData, &LpddrCmdAddr, Cke, Cs, Odt, &LpddrCadbPatternChunks[i]);
  }
  // Program CADB Pattern Generator
  MrcSetCadbPgPattern (MrcData, Outputs->McChBitMask, LpddrCadbPatternChunks, CadbCount, 0);

  // Set Mux0/1/2 to Pattern Buffer mode (LFSR size is ignored)

  Cadb20UniseqCfg (MrcData, MrcPgMuxPatBuffer, MrcLfsr8);

  // Program Pattern Buffers for a specific progression over CADB,
  // according to the given Pattern Buffer values
  MrcInitCadbPgMux (MrcData, PatBuf, 0, MRC_NUM_MUX_SEEDS);
}

/**
  Program DESWIZZLE_HIGH/LOW registers for MR4 decoding on LP4/LP5
  Program WRRETRAINSWIZZLECONTROL registers for MR18/MR19 decoding on LP4/LP5

  @param[in] MrcData - The MRC global data.

**/
void
ProgramDeswizzleRegisters (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                        *Inputs;
  MrcDebug                                        *Debug;
  MrcOutput                                       *Outputs;
  MrcChannelIn                                    *ChannelIn;
  UINT8                                           Controller;
  UINT8                                           Channel;
  UINT8                                           BigChannel;
  UINT8                                           IpChannel;
  UINT32                                          Byte;
  UINT32                                          DqsMapDramByte0;
  UINT8                                           Bit;
  UINT32                                          Offset;
  BOOLEAN                                         Lpddr;
  MC0_CH0_CR_DESWIZZLE_LOW_STRUCT                 DeswizzleLow;
  MC0_CH0_CR_DESWIZZLE_HIGH_STRUCT                DeswizzleHigh;
  MC0_CH0_CR_DESWIZZLE_LOW_ERM_STRUCT             DeswizzleLowErm;
  MC0_CH0_CR_DESWIZZLE_HIGH_ERM_STRUCT            DeswizzleHighErm;
  DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT WrRetrainSwizzleControl;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Lpddr     = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!(MrcChannelExist (MrcData, Controller, Channel))) {
        continue;
      }
      BigChannel = ((Channel == 0) || (Channel == 2));
      IpChannel = LP_IP_CH (Lpddr, Channel);
      ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
      DeswizzleLow.Data = 0;
      DeswizzleLowErm.Data = 0;
      DeswizzleHigh.Data = 0;
      DeswizzleHighErm.Data = 0;

      // DqsMapCpu2Dram maps CPU bytes to DRAM, we need to find the reverse mapping here
      // Program deswizzle low and deswizzle low erm if channel 0 and 2; program deswizzle high and deswizzle high erm if channel 1 and 3
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        switch (ChannelIn->DqsMapCpu2Dram[Byte]) {
          case 0:
            if (BigChannel) {
              DeswizzleLow.Bits.Byte_0 = Byte;
              DeswizzleLowErm.Bits.Byte_0 = Byte;
            } else {
              DeswizzleHigh.Bits.Byte_0 = Byte + 4;
              DeswizzleHighErm.Bits.Byte_0 = Byte + 4;
            }
            break;
          case 1:
            if (BigChannel) {
              DeswizzleLow.Bits.Byte_1 = Byte;
              DeswizzleLowErm.Bits.Byte_1 = Byte;
            } else {
              DeswizzleHigh.Bits.Byte_1 = Byte + 4;
              DeswizzleHighErm.Bits.Byte_1 = Byte + 4;
            }
            break;
        }
      }

      for (Bit = 0; Bit < MAX_BITS; Bit++) {
        // DqMapCpu2Dram maps CPU DQ pins to DRAM, we need to find the reverse mapping here
        if (BigChannel) {
          Byte = DeswizzleLow.Bits.Byte_0;
        } else {
          Byte = DeswizzleHigh.Bits.Byte_0 - 4;
        }
        switch (ChannelIn->DqMapCpu2Dram[Byte][Bit] % 8) {
          case 0:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_0 = Bit;
              DeswizzleLowErm.Bits.Bit_0 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_16 = Bit;
              DeswizzleHighErm.Bits.Bit_16 = Bit;
            }
            break;
          case 1:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_1 = Bit;
              DeswizzleLowErm.Bits.Bit_1 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_17 = Bit;
              DeswizzleHighErm.Bits.Bit_17 = Bit;
            }
            break;
          case 2:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_2 = Bit;
              DeswizzleLowErm.Bits.Bit_2 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_18 = Bit;
              DeswizzleHighErm.Bits.Bit_18 = Bit;
            }
            break;
          case 3:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_3 = Bit;
              DeswizzleLowErm.Bits.Bit_3 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_19 = Bit;
              DeswizzleHighErm.Bits.Bit_19 = Bit;
            }
            break;
          case 4:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_4 = Bit;
              DeswizzleLowErm.Bits.Bit_4 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_20 = Bit;
              DeswizzleHighErm.Bits.Bit_20 = Bit;
            }
            break;
        }

        if (BigChannel) {
          Byte = DeswizzleLow.Bits.Byte_1;
        } else {
          Byte = DeswizzleHigh.Bits.Byte_1 - 4;
        }
        switch (ChannelIn->DqMapCpu2Dram[Byte][Bit] % 8) {
          case 0:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_8 = Bit;
              DeswizzleLowErm.Bits.Bit_8 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_24 = Bit;
              DeswizzleHighErm.Bits.Bit_24 = Bit;
            }
            break;
          case 1:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_9 = Bit;
              DeswizzleLowErm.Bits.Bit_9 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_25 = Bit;
              DeswizzleHighErm.Bits.Bit_25 = Bit;
            }
            break;
          case 2:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_10 = Bit;
              DeswizzleLowErm.Bits.Bit_10 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_26 = Bit;
              DeswizzleHighErm.Bits.Bit_26 = Bit;
            }
            break;
          case 3:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_11 = Bit;
              DeswizzleLowErm.Bits.Bit_11 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_27 = Bit;
              DeswizzleHighErm.Bits.Bit_27 = Bit;
            }
            break;
          case 4:
            if (BigChannel) {
              DeswizzleLow.Bits.Bit_12 = Bit;
              DeswizzleLowErm.Bits.Bit_12 = Bit;
            } else {
              DeswizzleHigh.Bits.Bit_28 = Bit;
              DeswizzleHighErm.Bits.Bit_28 = Bit;
            }
            break;
        }
      } // for Bit

      if (BigChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DESWIZZLE_LOW_REG, MC1_CH0_CR_DESWIZZLE_LOW_REG, Controller, MC0_CH1_CR_DESWIZZLE_LOW_REG, IpChannel);
        MrcWriteCR64 (MrcData, Offset, DeswizzleLow.Data);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG, MC1_CH0_CR_DESWIZZLE_LOW_ERM_REG, Controller, MC0_CH1_CR_DESWIZZLE_LOW_ERM_REG, IpChannel);
        MrcWriteCR64 (MrcData, Offset, DeswizzleLowErm.Data);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Mc%d.Ch%d DESWIZZLE_LOW=0x%llx, DESWIZZLE_LOW_ERM=0x%llx\n",
          Controller,
          Channel,
          DeswizzleLow.Data,
          DeswizzleLowErm.Data
        );
      } else {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DESWIZZLE_HIGH_REG, MC1_CH0_CR_DESWIZZLE_HIGH_REG, Controller, MC0_CH1_CR_DESWIZZLE_HIGH_REG, IpChannel);
        MrcWriteCR64 (MrcData, Offset, DeswizzleHigh.Data);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG, MC1_CH0_CR_DESWIZZLE_HIGH_ERM_REG, Controller, MC0_CH1_CR_DESWIZZLE_HIGH_ERM_REG, IpChannel);
        MrcWriteCR64 (MrcData, Offset, DeswizzleHighErm.Data);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Mc%d.Ch%d DESWIZZLE_HIGH=0x%llx, DESWIZZLE_HIGH_ERM=0x%llx\n",
          Controller,
          Channel,
          DeswizzleHigh.Data,
          DeswizzleHighErm.Data
        );
      }

      if (Lpddr) {
        // Map the CPU bytes to the DRAM devices by programming the byte/bit deswizzle information in the DDRIO
        Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, DATA0CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Controller, DATA2CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          WrRetrainSwizzleControl.Data = 0;
          // DqsMapCpu2Dram maps CPU bytes to DRAM, we need to find the reverse mapping here
          Offset += ((DATA1CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG - DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG) * Byte);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqsMapCpu2Dram[%d]: %d\n", Byte, ChannelIn->DqsMapCpu2Dram[Byte]);
          if (Inputs->LpDqsOscEn) {
            WrRetrainSwizzleControl.Bits.DataRetrainEn = 1;
          }
          // ByteSel should always point to DRAM Byte 0 for x16 DRAM devices
          /*
             DRAM Byte0 --- SOC Byte0
             DRAM Byte1 --- SOC Byte1
                              SOC Byte0        SOC Byte1
             ByteSel          0 (Local)        1 (Neighbor)
             Retrain_DQ       SOC Byte0        SOC Byte0

             DRAM Byte0 --- SOC Byte1
             DRAM Byte1 --- SOC Byte0
                              SOC Byte0        SOC Byte1
             ByteSel          1 (Neighbor)     0 (Local)
             Retrain_DQ       SOC Byte1        SOC Byte1
          */
          if (ChannelIn->DqsMapCpu2Dram[Byte] && !Outputs->LpByteMode) {
            WrRetrainSwizzleControl.Bits.DataRetrain_ByteSel = 1;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DataRetrain_ByteSel: %d\n", WrRetrainSwizzleControl.Bits.DataRetrain_ByteSel);
            if (Byte == 0) {
              DqsMapDramByte0 = 1;
            } else {
              DqsMapDramByte0 = 0;
            }
          } else {
            DqsMapDramByte0 = Byte;
          }
          for (Bit = 0; Bit < MAX_BITS; Bit++) {
            // DQ bit mapping should always be deswizzling DRAM Byte0 DQ bits for x16 DRAM devices
            // DqMapCpu2Dram maps CPU DQ pins to DRAM, we need to find the reverse mapping here
            switch (ChannelIn->DqMapCpu2Dram[DqsMapDramByte0][Bit] % 8) {
              case 0:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ0 = Bit;
                break;

              case 1:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ1 = Bit;
                break;

              case 2:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ2 = Bit;
                break;

              case 3:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ3 = Bit;
                break;

              case 4:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ4 = Bit;
                break;

              case 5:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ5 = Bit;
                break;

              case 6:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ6 = Bit;
                break;

              case 7:
                WrRetrainSwizzleControl.Bits.DataRetrain_DQ7 = Bit;
                break;
            } // switch
          } // for Bit
          MrcWriteCR (MrcData, Offset, WrRetrainSwizzleControl.Data);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Mc%d.Ch%d Byte%d WrRetrainSwizzleControl=0x%08X\n",
            Controller,
            Channel,
            Byte,
            WrRetrainSwizzleControl.Data
            );
        } // for Byte
      } // (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4)
    } // for Channel
  } // for Controller
}

/**
This function configures the terminating ranks to FSP-OP 1 to enable their CA ODT
termination for the non-terminating ranks if enabled.  Otherwise, they are set
to FSP-OP 0, which is the reset default configuration (off).
This is done across all LPDDR4 and LPDDR5 channels.

@param[in]  MrcData - Pointer to the MRC global data.
@param[in]  Enable  - Boolean parameter to enable(TRUE) or disable(FALSE) CA termination.

@retval MrcStatus - mrcSuccess, otherwise an error status.
**/
MrcStatus
MrcLpddrSetCbtCaOdtEn (
  IN  MrcParameters *const  MrcData,
  IN  BOOLEAN               Enable
)
{
  MrcStatus           Status;
  MrcStatus           CurStatus;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcDdrType          DdrType;
  MrcOutput           *Outputs;
  INT32               CtlPi;
  INT32               CmdPi;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               MaxChannel;
  UINT8               Rank;
  UINT8               RankMask;
  UINT8               CmdRanksTermMask;
  BOOLEAN             Lpddr4;
  LPDDR4_FSP_OP_TYPE  FspOpPoint;

  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Status  = mrcSuccess;

  CmdRanksTermMask = MrcData->Inputs.CmdRanksTerminated;
  MaxChannel = Outputs->MaxChannels;

  FspOpPoint = (Enable) ? LpFspOpPoint1 : LpFspOpPoint0;

  CtlPi = (Lpddr4) ? MRC_SAFE_LP4_CTL_PI : MRC_SAFE_LP5_CTL_PI;
  CmdPi = (Lpddr4) ? MRC_SAFE_LP4_CMD_PI : MRC_SAFE_LP5_CMD_PI;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if ((RankMask & Outputs->ValidRankMask) == 0) {
      continue;
    }

    if ((CmdRanksTermMask & RankMask) != 0) {
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          // Use safe CS/CA PI settings, otherwise this MRW may get sampled as invalid command (or SRE etc.)
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, CtlPi, 0);
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CmdPi, 0);
        }
      }
      IoReset (MrcData);

      CurStatus = MrcSetFspVrcg (MrcData, RankMask, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, FspOpPoint);
      if (Status == mrcSuccess) {
        Status = CurStatus;
      }
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          // Restore CS/CA PI settings from the host struct
          IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];
          // CS is per subch
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, IntCmdTiming->CtlPiCode[Rank], 0);
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, IntCmdTiming->CmdPiCode[0], 0);
        }
      }
      IoReset (MrcData);
    }
  } // Rank

  return Status;
}

/**
  Run the CADB test on all channels / ranks at the current CS/CMD PIs.
  For LP5 ECT training, JEDEC allows Commands to be sampled at rising edge of CK and falling edge of CK. MR16.CbtPhase = 0 is for the former.
  This function runs the ShortCADB test twice, collects results and changes the MR16.CbtPhase for that channel.
  In the end all channels have to pass both CBT Phases for the 2D sweep of CS,CMD w.r.t CK training to pass.

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
  MrcChannelIn        *ChannelIn;
  MrcStatus           Status;
  MrcStatus           CurStatus;
  BOOLEAN             IgnoreByte;
  CADB_LINE           *CadbLines;
  UINT32              CadbCount;
  UINT32              *PatBuf;
  const UINT32        *Seeds;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               MaxChannel;
  UINT8               McChannelMask;
  UINT16              PhaseMask;
  UINT16              PhasePassMask;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               TermRankMask;
  UINT8               Byte;
  UINT8               ByteMask;
  UINT8               DramByte;
  UINT8               NumOfOnes;
  UINT8               RankPassMask;
  UINT8               FeedbackMask;
  UINT8               CbtPhase;
  UINT32              CaPattern;
  UINT32              McChannelPassMask;
  UINT32              WckControlSave;
  UINT32              MiscControl7Save;
  UINT32              DataRcompDataSave[MAX_CONTROLLER][MAX_SDRAM_IN_DIMM];
  UINT8               BytePassMaskCheck;
  UINT8               BytePassMask[MAX_CHANNEL];
  UINT32              Feedback[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              DelayCadb;
  UINT32              Pattern;
  CHAR8               PassFail;
  INT64               DataTrainFeedbackField;
  UINT32              DataTrainFeedback;
  MrcDdrType          DdrType;
  BOOLEAN             Lpddr4;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  TermRankMask  = Inputs->CmdRanksTerminated;
  MaxChannel    = Outputs->MaxChannels;
  DdrType       = Outputs->DdrType;
  Lpddr4        = (DdrType == MRC_DDR_TYPE_LPDDR4);
  FeedbackMask = Lpddr4 ? FEEDBACKMASKLP4 : FEEDBACKMASKLP5;

  DelayCadb = (Lpddr4) ? (1 * MRC_TIMER_1US) : (MRC_LP5_tADR_PS / 1000);

  RankPassMask = 0; // Bitmask of passed ranks
  BytePassMaskCheck = (1 << Outputs->SdramCount) - 1;
  MrcCall->MrcSetMem ((UINT8 *) BytePassMask, sizeof (BytePassMask), 0);

  CadbLines = Lpddr4 ? CadbLinesLp4 : CadbLinesLp5;
  CadbCount = Lpddr4 ? ARRAY_COUNT (CadbLinesLp4) : ARRAY_COUNT (CadbLinesLp5);

  PatBuf    = Lpddr4 ? CadbMuxLp4Pattern2 : CadbMuxLp5RisingPattern2;
  // LP5 patterns with CS are 0x2a and 0x55. 0x2a has 3 ones but 0x55 has 4 ones. LP4 patterns has 3 ones for both.
  CaPattern = Lpddr4 ? (CadbLines[2].CaHigh & CAPATTERNMASK) : (CadbLines[3].CaHigh & CAPATTERNMASK);
  NumOfOnes = MrcCountBitsEqOne (CaPattern);
  Status = mrcSuccess; // Initialize Status otherwise MiniBios fails

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & Outputs->ValidRankMask) == 0) {
      continue;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      Status = MrcLpddrSetCbtCaOdtEn (MrcData, TRUE);
      if (Status != mrcSuccess) {
        return Status;
      }
    }


    // PhaseMask will be packed as below
    // Each Channel has 2 consecutive bits for PassFail results
    // Channel 0 through 7 for both MCs will occupy all even positions for CbtPhase0
    // Bit 15  14  13  12  11  10  9  8  7  6  5  4  3  2  1  0
    // Ph0      1       1       1     1     1     1     1     1
    // Ph1  1       1       1      1     1     1     1     1
    PhasePassMask = 0;
    PhaseMask = 0;
    McChannelPassMask = 0; // Bitmask of passed channels on the current rank
    McChannelMask = 0;     // Bitmask of channels that have current rank populated
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        McChannelMask |= (1 << ((Controller * MaxChannel) + Channel));
        for (CbtPhase = 0; CbtPhase < MAX_CBT_PHASES; CbtPhase++) {
          PhaseMask |= (MRC_BIT0 << ((((Controller * MaxChannel) + (Channel)) * MAX_CBT_PHASES) + CbtPhase));
        }
      }  // for Channel
    } // for Controller

    for (CbtPhase = 0; CbtPhase < MAX_CBT_PHASES; CbtPhase++) {
      if (Lpddr4 && (CbtPhase > 0)) { // Run this loop only once for Lp4
        continue;
      }
      // Setup and Enter CBT Mode for this Rank.
      SetupCaTrainingCadb (MrcData, Rank, CadbLines, CadbCount, PatBuf);
      Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 1, CbtPhase, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
      if (Status != mrcSuccess) {
        return Status;
      }

      if (Lpddr4) {
        // Send VrefCA on DQ[6:0]
        MrcSendCaVrefOnDq (MrcData, Rank);
      }

      // Try two different patterns (0x2AA or 0x55), to see if the command is still decoded correctly
      for (Pattern = 0; Pattern <= 1; Pattern++) {
        if (Lpddr4) {
          Seeds = (Pattern == 0) ? CadbMuxLp4Pattern2 : CadbMuxLp4Pattern3;
        } else {
          if (CbtPhase == 0) {
            Seeds = (Pattern == 0) ? CadbMuxLp5RisingPattern2 : CadbMuxLp5RisingPattern3;
          } else {
            Seeds = (Pattern == 0) ? CadbMuxLp5FallingPattern2 : CadbMuxLp5FallingPattern3;
          }
        }
        MrcInitCadbPgMux (MrcData, Seeds, 0, MRC_NUM_MUX_SEEDS);

        // Run CADB pattern on selected channels at the same time
        ShortRunCADB (MrcData, McChannelMask);
        MrcWait (MrcData, DelayCadb);

        // Read and process the results
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
              if (Pattern == 1) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
              }
              continue;
            }
            ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
            BytePassMask[Channel] = 0;
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              ByteMask = (1 << Byte);
              DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
              IgnoreByte = FALSE;
              if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
                IgnoreByte = TRUE;
              }
              if (Lpddr4) {
                if ((DramByte & 1) == 0) { // Ignore DRAM bytes 0, 2, 4 and 6 - they don't provide feedback
                  IgnoreByte = TRUE;
                }
              } else {
                if ((DramByte & 1) == 1) { // Ignore DRAM bytes 1, 3, 5 and 7 - they don't provide feedback
                  IgnoreByte = TRUE;
                }
              }
              if (IgnoreByte) {
                BytePassMask[Channel] |= ByteMask;
                continue;
              }
              MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
              DataTrainFeedback = (UINT32) DataTrainFeedbackField & FeedbackMask;  // Get only DQ bits, not DQS
              if (Pattern == 0) {
                Feedback[Channel][Byte] = DataTrainFeedback; // Save the first pattern
              } else {
                // Second Pattern
                // If still read the same data, then DRAM was not able to decode the new command
                if ((Feedback[Channel][Byte] != DataTrainFeedback) &&
                  (MrcCountBitsEqOne (DataTrainFeedback) == NumOfOnes)) {
                  BytePassMask[Channel] |= ByteMask;
                }
              }
            }  // for Byte
            if (Pattern == 1) {
              if (BytePassMask[Channel] == BytePassMaskCheck) { // If all bytes on a channel passed, mark this channel as passed.
                McChannelPassMask |= (MRC_BIT0 << ((Controller * MaxChannel) + Channel));
                PhasePassMask |= (MRC_BIT0 << ((((Controller * MaxChannel) + (Channel)) * 2) + CbtPhase));
                PassFail = '.';
              } else {
                PassFail = '#';
              }
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%02X PhasePassMask = 0x%x CbtPhase = %d \n", PassFail, BytePassMask[Channel], PhasePassMask, CbtPhase);
            }
          }  // for Channel
        } // for Controller
      } // for Pattern

      if (Lpddr4) {
        if (McChannelPassMask == McChannelMask) {
          RankPassMask |= RankBit; // If all channels passed, mark this rank as passed
        }
      } else {
        if (PhasePassMask == PhaseMask) { // If both CbtPhases pass
          RankPassMask |= RankBit; // If all channels passed, mark this rank as passed
        }
      }

      // Exit CA training mode on the current rank
      Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 0, CbtPhase, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
      if ((RankBit & TermRankMask) == 0) {
        // Disable Termination on the terminated rank via FSP-High
        CurStatus = MrcLpddrSetCbtCaOdtEn (MrcData, FALSE);
        if (Status == mrcSuccess) {
          Status = CurStatus;
        }
      }
    } // CbtPhase
    if (Status != mrcSuccess) {
      return Status;
    }
  } // for Rank

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  return RankPassMask;
}

/**
  Find a good starting point for LPDDR3/LPDDR4 CMD/CS, using a quick 2D search.
  CLK is being kept at default (64).
  Start from ideal theoretical point: CS=64, CMD=96 (LPDDR3) / CMD=64 (LPDDR4).
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
  UINT32              Controller;
  UINT32              Channel;
  UINT8               MaxChannel;
  UINT8               RankMask;
  UINT8               RankPassMask;
  UINT32              CaPiCode;
  UINT32              CsPiCode;
  UINT32              CaPiCodePass[3];
  UINT32              CsPiCodePass[3];
  UINT8               CaPassIndex;
  UINT8               CsPassIndex;
  UINT8               IndexMax;
  UINT32              CsPiIndex;
  UINT32              CaPiIndex;
  const UINT16        *CsPiTable;
  const UINT16        *CaPiTable;

  static const UINT16 CsPiTableG1[]    = { 144, 128, 112, 96, 80, 64, 48, 32, 16, 0, 240, 224, 208, 192, 176, 160  };
  //static const UINT16 CsPiTableG2[]    = { 144, 128, 112, 96, 80, 64, 48, 32, 16, 0, 496, 480, 464, 448, 432, 416, 400, 384, 368, 352, 336, 320, 304, 288, 272, 256, 240, 224, 208, 192, 176, 160  };
  static const UINT16 CsPiTableLP5G2[] = { 16, 0, 496, 480, 464, 448, 432, 416, 400, 384, 368, 352, 336, 320, 304, 288, 272, 256, 240, 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48, 32  };

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  RankMask = Outputs->ValidRankMask;
  MaxChannel = Outputs->MaxChannels;
  CsPiCode = 0;
  CaPiCode = 0;
  CaPassIndex = 0;
  CsPassIndex = 0;
  RankPassMask = 0; // Bitmask of passed ranks
  MrcCall->MrcSetMem ((UINT8 *) CaPiCodePass, sizeof (CaPiCodePass), 0);
  MrcCall->MrcSetMem ((UINT8 *) CsPiCodePass, sizeof (CsPiCodePass), 0);

  // Init DDR IO for CA training
  if ((Outputs->Gear2) && (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5)) {
    CsPiTable = CsPiTableLP5G2;
    CaPiTable = CsPiTableLP5G2;
    IndexMax = ARRAY_COUNT (CsPiTableLP5G2);
  } else {
    CsPiTable = CsPiTableG1;
    CaPiTable = CsPiTableG1;
    IndexMax = ARRAY_COUNT (CsPiTableG1);
  }

  LpddrCaTrainingInitIo (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tM0C0R0\tM0C0R1\tM0C0R2\tM0C0R3\tM0C1R0\tM0C1R1\tM0C1R2\tM0C1R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM0C2R0\tM0C2R1\tM0C2R2\tM0C2R3\tM0C3R0\tM0C3R1\tM0C3R2\tM0C3R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM1C0R0\tM1C0R1\tM1C0R2\tM1C0R3\tM1C1R0\tM1C1R1\tM1C1R2\tM1C1R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM1C2R0\tM1C2R1\tM1C2R2\tM1C2R3\tM1C3R0\tM1C3R1\tM1C3R2\tM1C3R3\n");
  for (CsPiIndex = 0; CsPiIndex < IndexMax; CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\n", CsPiCode);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        // Shift the CS PI on all ranks, keep the value in the host struct.
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, CsPiCode, 1);
      }
    }

    CaPassIndex = 0;            // Restart search for 3 passing CMD points
    for (CaPiIndex = 0; CaPiIndex < IndexMax; CaPiIndex++) {
      CaPiCode = CaPiTable[CaPiIndex];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD:%d\t", CaPiCode);
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcChannelExist (MrcData, Controller, Channel)) {
            continue;
          }
          // Shift the Command PI on both CAA and CAB groups; RankMask is not relevant for CMD/CKE.
          // Keep the value in the host struct.
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CaPiCode, 1);
        }
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
  CaPiCode = CaPiCodePass[1];                   // Select the middle code out of three.

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Shift the Command PI and keep the value in the host struct.
      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CaPiCode, 1);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tM0C0R0\tM0C0R1\tM0C0R2\tM0C0R3\tM0C1R0\tM0C1R1\tM0C1R2\tM0C1R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM0C2R0\tM0C2R1\tM0C2R2\tM0C2R3\tM0C3R0\tM0C3R1\tM0C3R2\tM0C3R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM1C0R0\tM1C0R1\tM1C0R2\tM1C0R3\tM1C1R0\tM1C1R1\tM1C1R2\tM1C1R3");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tM1C2R0\tM1C2R1\tM1C2R2\tM1C2R3\tM1C3R0\tM1C3R1\tM1C3R2\tM1C3R3\n");
  // Now let's find 3 passing CS points at this CMD point
  for (CsPiIndex = 0; CsPiIndex < IndexMax; CsPiIndex++) {
    CsPiCode = CsPiTable[CsPiIndex];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS: %d\t", CsPiCode);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        // Shift the CS PI on all ranks, keep the value in the host struct.
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, CsPiCode, 1);
      }
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
  CsPiCode = CsPiCodePass[1];                   // Select the middle code out of three.

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Shift the CS PI on all ranks, keep the value in the host struct.
      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, CsPiCode, 1);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Final selected values: CS = %d, CMD = %d\n\n", CsPiCode, CaPiCode);

  // Restore DDR IO values that were used for CA training
  LpddrCaTrainingRestoreIo (MrcData);

  return Status;
}

/**
  Sweep CMD PI up or down and find edges for all bytes.
  Main flow:
  1.
  2.
  3.
  For LP5 ECT training, JEDEC allows Commands to be sampled at rising edge of CK and falling edge of CK. MR16.CbtPhase = 0 is for the former.
  This function runs the ShortCADB test twice, collects results and changes the MR16.CbtPhase for that channel.
  In the end all channels have to pass both CBT Phases for the CA sweep w.r.t CK to pass.

  @param[in] MrcData - The MRC global data.

**/
void
EarlyCaFindEdge (
  IN MrcParameters *const   MrcData,
  UINT32                    Rank,
  UINT16                    Start,
  UINT16                    Stop,
  INT16                     Step,
  UINT8                     CbtPhase,
  UINT16                    Limit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_CBT_PHASES]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelIn      *ChannelIn;
  CADB_LINE         *CadbLines;
  UINT32            Controller;
  UINT32            Channel;
  UINT32            Byte;
  UINT32            CaPattern;
  UINT8             MaxChannel;
  UINT8             McChannelMask;
  UINT8             ByteMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8             ByteDoneMaskCheck;
  UINT8             FeedbackMask;
  UINT16            PiCode;
  UINT8             NumOfOnes;
  UINT32            DelayCadb;
  UINT32            DataTrainFeedback;
  INT64             DataTrainFeedbackField;
  BOOLEAN           Done;
  BOOLEAN           IgnoreByte;
  BOOLEAN           BreakOut;
  BOOLEAN           Lpddr4;
  char              *BytesHeader;
  char              PassFail;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MaxChannel    = Outputs->MaxChannels;
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 1 : 0;
  FeedbackMask  = Lpddr4 ? FEEDBACKMASKLP4 : FEEDBACKMASKLP5;

  DelayCadb = (Lpddr4) ? (1 * MRC_TIMER_1US) : (MRC_LP5_tADR_PS / 1000);

  MrcCall->MrcSetMem ((UINT8 *) ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode  = Start;
  Done    = FALSE;
  ByteDoneMaskCheck = 0;
  CadbLines = (Lpddr4) ? CadbLinesLp4 : CadbLinesLp5;
  CaPattern = CadbLines[2].CaHigh & CAPATTERNMASK;
  NumOfOnes = MrcCountBitsEqOne (CaPattern);

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    ByteDoneMaskCheck |= (1 << Byte);
  }

  McChannelMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
        McChannelMask |= (1 << ((Controller * MaxChannel) + Channel));
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Mc0Ch0    Mc0Ch1    Mc0Ch2    Mc0Ch3    Mc1Ch0    Mc1Ch1    Mc1Ch2    Mc1Ch3\n");
  BytesHeader = "0   1     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD PI\t %s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d: \t", PiCode);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        // Shift the Command PI
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, PiCode, 0);
      }
    }

    // Run CADB pattern on selected controller/channels at the same time
    ShortRunCADB (MrcData, McChannelMask);
    MrcWait (MrcData, DelayCadb);

    // Read and process the results
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ByteDoneMask[Controller][Channel] = ByteDoneMaskCheck;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
          continue;
        }
        if (ByteDoneMask[Controller][Channel] == ByteDoneMaskCheck) { // All bytes failed on this channel, no need to sweep anymore
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
          continue;
        }
        ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteMask = (1 << Byte);
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          IgnoreByte = FALSE;
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            IgnoreByte = TRUE;
          }
          if (Lpddr4) {
            if ((DramByte & 1) == 0) { // Ignore DRAM bytes 0, 2, 4 and 6 - they don't provide feedback
              IgnoreByte = TRUE;
            }
          } else {
            if ((DramByte & 1) == 1) { // Ignore DRAM bytes 1, 3, 5 and 7 - they don't provide feedback
              IgnoreByte = TRUE;
            }
          }
          if (IgnoreByte) {
            ByteDoneMask[Controller][Channel] |= ByteMask;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
            continue;
          }
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
          DataTrainFeedback = (UINT32) DataTrainFeedbackField & FeedbackMask;  // Get only DQ bits, not DQS
          PassFail = '#';
          if ((ByteDoneMask[Controller][Channel] & ByteMask) == 0) {
            // If we don't see 4 ones in the byte, then the command was not aligned properly
            if (MrcCountBitsEqOne (DataTrainFeedback) != NumOfOnes) {
              Limit[Controller][Channel][Rank][Byte][CbtPhase] = PiCode;
              ByteDoneMask[Controller][Channel] |= ByteMask;
            } else {
              PassFail = '.';
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c%02X ", PassFail, DataTrainFeedback);
        }  // for Byte
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
      }  // for Channel
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
    }  // for Controller
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    BreakOut = TRUE;
    for (Controller = 0; Controller < MAX_CONTROLLER && BreakOut; Controller++) {
      for (Channel = 0; Channel < MaxChannel && BreakOut; Channel++) {
        if (ByteDoneMask[Controller][Channel] != ByteDoneMaskCheck) {
          BreakOut = FALSE;
        }
      }
    }
    if (BreakOut) {
      // Found the limit on all bytes on all channels on all mc - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT16) PiCode) < Stop);
    }
  }  // while not done
}

/**
  Process the results of the early LPDDR3/LPDDR4 CMD training and find the best PI settings for CAA/CAB.
  Flow:
   1. Find the worst case Right and Left limits for each channel
   2. Find the Center for each channel

  @param[in]  MrcData     - The MRC global data.
  @param[in]  MaxValue    - Value to start RightLimit array at
  @param[in]  LeftLimit   - array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - array of best CMD PI settings, per channel

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCmdPi (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                MaxValue,
  IN  UINT16                LeftLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_CBT_PHASES],
  IN  UINT16                RightLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_CBT_PHASES],
  OUT UINT16                BestCmd[MAX_CONTROLLER][MAX_CHANNEL]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            Controller;
  UINT32            Channel;
  UINT32            Rank;
  UINT8             MaxChannel;
  UINT8             Byte;
  UINT16            CmdLeftLimit[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16            CmdRightLimit[MAX_CONTROLLER][MAX_CHANNEL];

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MaxChannel    = Outputs->MaxChannels;

  Status = mrcSuccess;

  MrcCall->MrcSetMemWord ((UINT16 *) CmdRightLimit, sizeof (CmdRightLimit) / sizeof (UINT16), MaxValue);
  MrcCall->MrcSetMemWord ((UINT16 *) CmdLeftLimit, sizeof (CmdLeftLimit) / sizeof (UINT16), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CMD PIs:\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc: %d, Channel: %d\tLeft\tRight\tCenter\n", Controller, Channel);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        // Find the worst case Right and Left limits for all ranks, for bytes from the particular CA group
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          CmdRightLimit[Controller][Channel] = MIN (CmdRightLimit[Controller][Channel], RightLimit[Controller][Channel][Rank][Byte][0]);
          CmdLeftLimit[Controller][Channel]  = MAX (CmdLeftLimit[Controller][Channel], LeftLimit[Controller][Channel][Rank][Byte][0]);
        }
      } // for Rank
      // Find the Center for each group, worst case of all ranks
      BestCmd[Controller][Channel] = (CmdRightLimit[Controller][Channel] + CmdLeftLimit[Controller][Channel]) / 2;

      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "CAA\t\t\t%d\t%d\t%d\n",
        CmdLeftLimit[Controller][Channel],
        CmdRightLimit[Controller][Channel],
        BestCmd[Controller][Channel]
      );
    } // for Channel
  } // for Controller

  return Status;
}

/**
  Update DqMapCpu2Dram array

  @param[in] MrcData     - The MRC global data.
  @param[in] Controller  - the controller to work on
  @param[in] Channel     - the channel to work on
  @param[in] Feedback    - array of DATATRAINFEEDBACK values for all 8 bytes
  @param[in] Bit         - The DQ bit that should be set in each DRAM byte

  @retval mrcSuccess if succeeded
**/
MrcStatus
FillCA2DQMapResult (
  IN OUT MrcParameters *const   MrcData,
  IN const UINT32               Controller,
  IN const UINT32               Channel,
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
  ControllerIn  = &Inputs->Controller[Controller];

  ChannelIn  = &ControllerIn->Channel[Channel];

  BitNumber = -1;

  // Loop on CPU bytes
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
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
  UINT32    Controller;
  UINT32    Channel;
  UINT8     Byte;
  UINT8     Bit;
  UINT8     DramBit;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;


  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcRankExist (MrcData, Controller, Channel, 0)) {
        continue;
      }
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\nMapCA2DQPins Results for Mc%d.Ch%d (\"-1\" for skipped Bytes, DRAM DQ pins offsets):\n",
        Controller,
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
          DramBit = MrcData->Inputs.Controller[Controller].Channel[Channel].DqMapCpu2Dram[Byte][Bit];
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", (DramBit == 255) ? -1 : DramBit);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      }
    }
  }
#endif //MRC_DEBUG_PRINT
}

/**
  Sweep the given PI up or down and find the edge.

  @param[in]  MrcData     - The MRC global data.
  @param[in]  Iteration   - Determines which PI to shift
  @param[in]  McChBitMask - Valid Channel bit mask flat across all controllers.
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
  IN  UINT8                  McChBitMask,
  IN  UINT8                  RankMask,
  IN  UINT8                  GroupMask,
  IN  INT16                  Stop,
  IN  INT16                  Step,
  OUT UINT8                  Limit[MAX_CONTROLLER][MAX_CHANNEL],
  IN  BOOLEAN                DebugPrint
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  UINT32              Controller;
  UINT32              Channel;
  INT16               PiOffset;
  UINT8               McChBit;
  UINT8               McChError;
  UINT8               MaxChannels;
  BOOLEAN             Pass;
  BOOLEAN             Done;
  BOOLEAN             LimitDone;
  BOOLEAN             ChannelDone[MAX_CONTROLLER][MAX_CHANNEL];
#ifdef MRC_DEBUG_PRINT
  MrcDebugMsgLevel    DbgLvl;

  DbgLvl = (DebugPrint) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
#endif

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MaxChannels = Outputs->MaxChannels;
  MrcCall     = MrcData->Inputs.Call.Func;
  PiOffset    = 0;
  Done        = FALSE;
  MrcCall->MrcSetMem ((UINT8 *) ChannelDone, ARRAY_COUNT2D (ChannelDone), FALSE);

  MRC_DEBUG_MSG (Debug, DbgLvl, "\t0 1\n");
  while (!Done) {
    MRC_DEBUG_MSG (Debug, DbgLvl, "%d:\t", PiOffset);
    // Update Timing
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          if (!ChannelDone[Controller][Channel]) {
            ShiftPIforCmdTraining (MrcData, Controller, Channel, Iteration, RankMask, GroupMask, PiOffset, 0);
          }
        }
      }
    }
    // Reset DDR after changing the CLK PI
    MrcResetSequence (MrcData);

    // Run CPGC test on both channels
    McChError = RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBit = MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels);
        if (((McChBit) == 0) || (ChannelDone[Controller][Channel])) {
          MRC_DEBUG_MSG (Debug, DbgLvl, (Channel == 0) ? "  " : "");
          continue;
        }

        Pass = !(McChError & McChBit);

        MRC_DEBUG_MSG (Debug, DbgLvl, (Pass ? ". " : "# "));

        if (Pass) {
          Limit[Controller][Channel] = (UINT8) (ABS (PiOffset));
        } else {
          ChannelDone[Controller][Channel] = TRUE;
        }
      } // Channel
    } // Controller
    MRC_DEBUG_MSG (Debug, DbgLvl, "\n");

    PiOffset += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiOffset > Stop);
    } else {
      // Sweep down
      Done = (PiOffset < Stop);
    }

    // Check if we have finished all channels
    LimitDone = TRUE;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
          if (ChannelDone[Controller][Channel] == FALSE) {
            LimitDone = FALSE;
          }
        }
      }
    }
    // If we found all the edges, break out of the while loop
    if (LimitDone) {
      Done = TRUE;
    }
  }  // while not done
}

/**
  Sweep right and left from the current point to find the margins.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      McChBitMask - Valid Channel bit mask flat across all controllers.
  @param[in]      RankMask    - Valid Rank bit mask
  @param[in]      GroupMask   - Valid Group bit mask
  @param[in]      DebugPrint  - Print debug messages or not

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
void
CmdLinearFindEdgesLpddr (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                McChBitMask,
  IN     UINT8                RankMask,
  IN     UINT8                GroupMask,
  IN     BOOLEAN              DebugPrint
  )
{
  const MrcInput    *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  UINT32            Controller;
  UINT32            Channel;
  UINT32            Rank;
  INT16             PiLow;
  INT16             PiHigh;
  INT16             PiStep;
  UINT8             MaxChannels;
  UINT8             RightLimit[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8             LeftLimit[MAX_CONTROLLER][MAX_CHANNEL];
  BOOLEAN           ClockIteration;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  MaxChannels = Outputs->MaxChannels;
  ClockIteration = (Iteration == MrcIterationClock);

  // We are going to sweep clock 64 PI ticks to the left and to the right
  //@todo adjustment needed for extra sweep range of TGL and Gear2
  PiLow   = -64;
  PiHigh  = 64;

  PiStep = 1;


  // Initialize to zero margin
  MrcCall->MrcSetMem ((UINT8 *) RightLimit, sizeof (RightLimit), 0);
  MrcCall->MrcSetMem ((UINT8 *) LeftLimit, sizeof (LeftLimit), 0);

  // Find right and left margins
  CaFindEdge (MrcData, Iteration, McChBitMask, RankMask, GroupMask, PiHigh, PiStep, ClockIteration ? RightLimit : LeftLimit, DebugPrint);
  CaFindEdge (MrcData, Iteration, McChBitMask, RankMask, GroupMask, PiLow, -PiStep, ClockIteration ? LeftLimit : RightLimit, DebugPrint);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannels)) {
        // Save margins for RMT
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if ((1 << Rank) & RankMask) {
            Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][0] = 10 * LeftLimit[Controller][Channel];
            Outputs->MarginResult[LastCmdT][Rank][Controller][Channel][0][1] = 10 * RightLimit[Controller][Channel];
          }
        }
      }
    }
  }
}

/**
  Early CMD / CLK training for LPDDR3 / LPDDR4.
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

  Lp5 Flow :
    Same as above except
    3) Drive DQ7 high to switch to FSP high. LpddrCommandTrainingMode () takes care of it.
    5) Run training on all channels in parallel per CbtPhase and average the PiLimit from both the phases.
    8) Drive DQ7 low


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
  MrcIntOutput          *IntOutputs;
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcStatus             Status;
  CADB_LINE             *CadbLines;
  MrcDdrType            DdrType;
  INT64                 Min;
  INT64                 Max;
  UINT32                CadbCount;
  UINT32                *PatBuf;
  UINT32                Controller;
  UINT32                Channel;
  UINT32                Rank;
  UINT32                WckControlSave;
  UINT32                MiscControl7Save;
  UINT32                DataRcompDataSave[MAX_CONTROLLER][MAX_SDRAM_IN_DIMM];
  UINT8                 MaxChannel;
  UINT8                 CbtPhase;
  UINT8                 McChannelMask;
  UINT8                 RankBit;
  UINT8                 RankMask;
  UINT8                 TermRankMask;
  UINT16                PiLow;
  UINT16                PiHigh;
  UINT16                PiMiddle;
  UINT16                PiStep;
  UINT16                RightLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_CBT_PHASES];
  UINT16                LeftLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_CBT_PHASES];
  UINT16                BestCmd[MAX_CONTROLLER][MAX_CHANNEL]; // per Channel and per group (CAA and CAB)
  BOOLEAN               Lpddr4;
  MrcChannelIn          *ChannelIn;
  UINT16                LeftPhase0;
  UINT16                LeftPhase1;
  UINT16                RightPhase0;
  UINT16                RightPhase1;
  UINT16                Left;
  UINT16                Right;
  UINT8                 Byte;
  UINT8                 DramByte;

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  TermRankMask     = Inputs->CmdRanksTerminated;
  MaxChannel       = Outputs->MaxChannels;
  DdrType          = Outputs->DdrType;
  Lpddr4           = (DdrType == MRC_DDR_TYPE_LPDDR4);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyCaTraining started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  MrcGetSetLimits (MrcData, CmdGrpPi, &Min, &Max, NULL);
  PiLow     = (UINT16) Min;
  PiHigh    = (UINT16) Max;
  PiMiddle  = (PiHigh - PiLow + 1) / 2; // Will be updated below from the host struct
  PiStep = (PiHigh + 1) / 64;



  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PiLow = %d, PiHigh = %d, PiStep = %d\n", PiLow, PiHigh, PiStep);
  MrcCall->MrcSetMemWord ((UINT16 *) RightLimit, sizeof (RightLimit) / sizeof (UINT16), PiHigh);
  MrcCall->MrcSetMemWord ((UINT16 *) LeftLimit, sizeof (LeftLimit) / sizeof (UINT16), PiLow);

  // Init DDR IO for CA training
  CadbLines = Lpddr4 ? CadbLinesLp4 : CadbLinesLp5;
  CadbCount = Lpddr4 ? ARRAY_COUNT (CadbLinesLp4) : ARRAY_COUNT (CadbLinesLp5);
  PatBuf    = Lpddr4 ? CadbMuxLp4Pattern2 : CadbMuxLp5RisingPattern2;
  LpddrCaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }
    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      Status = MrcLpddrSetCbtCaOdtEn (MrcData, TRUE);
      if (Status != mrcSuccess) {
        return Status;
      }
    }


    McChannelMask = 0;     // Bitmask of Controller channels that have current rank populated
    for (CbtPhase = 0; CbtPhase < MAX_CBT_PHASES; CbtPhase++) {
      if (Lpddr4 && (CbtPhase > 0)) { // Run this loop only once for Lp4
        continue;
      }
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }
          McChannelMask |= (1 << ((Controller * MaxChannel) + Channel));
          IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];
          PiMiddle = IntCmdTiming->CmdPiCode[0]; // Found in EarlyCsCmdLpddr()
        }  // for Channel
      }
      // Setup and Enter CBT Mode for this Rank.
      if (!Lpddr4) {
        PatBuf = (CbtPhase == 0) ? CadbMuxLp5RisingPattern2 : CadbMuxLp5FallingPattern2;
      }
      SetupCaTrainingCadb (MrcData, Rank, CadbLines, CadbCount, PatBuf);
      Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 1, CbtPhase, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
      if (Status != mrcSuccess) {
        return Status;
      }

      if (Lpddr4) {
        // Send VrefCA on DQ[6:0]
        MrcSendCaVrefOnDq (MrcData, Rank);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "R%d: MrcSendCaVrefOnDq done\n", Rank);

      }

      // Sweep CMD PI up and down from the middle, on both channels at the same time
      EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, CbtPhase, RightLimit);
      EarlyCaFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, CbtPhase, LeftLimit);
    } // CbtPhase

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CA training data Mc%d Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\tCbtPhase\n", Controller, Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            continue;
          }

          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          if (Lpddr4) {
            if ((DramByte & 1) == 0) {  // Ignore DRAM even bytes.
              continue;
            }
          } else {
            if ((DramByte & 1) == 1) {  // Ignore DRAM odd bytes.
              continue;
            }
          }
          LeftPhase0 = LeftLimit[Controller][Channel][Rank][Byte][0];
          RightPhase0 = RightLimit[Controller][Channel][Rank][Byte][0];
          LeftPhase1 = LeftLimit[Controller][Channel][Rank][Byte][1];
          RightPhase1 = RightLimit[Controller][Channel][Rank][Byte][1];
          if (Lpddr4) {
            Left  = LeftPhase0;
            Right = RightPhase0;
          } else {
            // Larger Pi value for Left and smaller Pi value for the right
            Left = MAX (LeftPhase0, LeftPhase1);
            Right = MIN (RightPhase0, RightPhase1);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left, CbtPhase);
          // average of PiLimits for both phases are stored in [CbtPhase] = 0
          LeftLimit[Controller][Channel][Rank][Byte][0] = Left;
          RightLimit[Controller][Channel][Rank][Byte][0] = Right;
        } // for Byte
      } // for Channel
    } // for Controller

    // Exit CA training mode on the current rank
    // For exit we dont care about CbtPhase input parameter therefore passing 0
    Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 0, 0, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
    if (Status != mrcSuccess) {
      return Status;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Disable Termination on the terminated rank via FSP-High
      Status = MrcLpddrSetCbtCaOdtEn (MrcData, FALSE);
    }

  }  // for Rank
  // Restore DDR IO values that were used for CA training
  LpddrCaTrainingRestoreIo (MrcData);
  // Select optimal CMD timings for both channels
  FindBestCmdPi (MrcData, PiHigh, LeftLimit, RightLimit, BestCmd);

  // Apply the new CMD PI settings
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
        continue;
      }
      // CAA is controlled by CmdGrp0 & CmdGrp1
      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, (1 << 0), BestCmd[Controller][Channel], 1);
    } // for Channel
  } // for Controller

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
  UINT16                    Start,
  UINT16                    Stop,
  INT16                     Step,
  OUT UINT16                Limit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelIn      *ChannelIn;
  CADB_LINE         *CadbLines;
  MrcDdrType        DdrType;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             McChannelMask;
  UINT8             RankMask;
  UINT8             Byte;
  UINT8             ByteMask;
  UINT8             DramByte;
  UINT8             ByteDoneMask[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8             ByteDoneMaskCheck;
  UINT16            PiCode;
  UINT8             NumOfOnes;
  UINT8             Feedback[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8             MaxChannel;
  UINT8             FeedbackMask;
  UINT32            DataTrainFeedback;
  UINT32            CaPattern;
  UINT32            Pattern;
  UINT32            DelayChipSelectCadb;
  const UINT32      *Seeds;
  INT64             DataTrainFeedbackField;
  BOOLEAN           Done;
  BOOLEAN           Failed;
  BOOLEAN           IgnoreByte;
  BOOLEAN           BreakOut;
  BOOLEAN           Lpddr4;
  char              *BytesHeader;
  char              PassFail;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  McChannelMask = 0;
  MaxChannel    = Outputs->MaxChannels;
  DdrType       = Outputs->DdrType;
  Lpddr4        = (DdrType == MRC_DDR_TYPE_LPDDR4);
  FeedbackMask  = Lpddr4 ? FEEDBACKMASKLP4 : FEEDBACKMASKLP5;

  DelayChipSelectCadb = 1 * MRC_TIMER_1US;

  MrcCall->MrcSetMem ((UINT8 *) ByteDoneMask, sizeof (ByteDoneMask), 0);

  PiCode = Start;
  Done = FALSE;
  ByteDoneMaskCheck = 0;

  RankMask  = 1 << Rank;
  CadbLines = Lpddr4 ? CadbLinesLp4 : CadbLinesLp5;
  // LP5 patterns with CS are 0x2a and 0x55. 0x2a has 3 ones but 0x55 has 4 ones. LP4 patterns has 3 ones for both.
  CaPattern = Lpddr4 ? (CadbLines[2].CaHigh & CAPATTERNMASK) : (CadbLines[3].CaHigh & CAPATTERNMASK);
  NumOfOnes = MrcCountBitsEqOne (CaPattern);

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    ByteDoneMaskCheck |= (1 << Byte);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t Mc0Ch0 p1 Mc0Ch1 p1 Mc0Ch2 p1 Mc0Ch3 p1 Mc1Ch0 p1 Mc1Ch1 p1 Mc1Ch2 p1 Mc1Ch3 p1 ");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc0Ch0 p2 Mc0Ch1 p2 Mc0Ch2 p2 Mc0Ch3 p2 Mc1Ch0 p2 Mc1Ch1 p2 Mc1Ch2 p2 Mc1Ch3 p2\n");
  BytesHeader = "0   1     ";
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CTL PI\t %s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s\n", BytesHeader, BytesHeader);

  while (!Done) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d:\t", PiCode);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMask, MRC_IGNORE_ARG_8, PiCode, 0);
        }
      }
    }

    // Try two different paterns (0x2AA or 0x155), to see if the command is still decoded correctly
    for (Pattern = 0; Pattern <= 1; Pattern++) {
      if (Lpddr4) {
        Seeds = (Pattern == 0) ? CadbMuxLp4Pattern2 : CadbMuxLp4Pattern3;
      } else {
        Seeds = (Pattern == 0) ? CadbMuxLp5RisingPattern2 : CadbMuxLp5RisingPattern3;
      }
      MrcInitCadbPgMux (MrcData, Seeds, 0, MRC_NUM_MUX_SEEDS);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }
          McChannelMask |= (1 << ((Controller * MaxChannel) + Channel));
        }
      }

      // Run CADB pattern on selected channels at the same time
      ShortRunCADB (MrcData, McChannelMask);
      MrcWait (MrcData, DelayChipSelectCadb);

      // Read and process the results
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            ByteDoneMask[Controller][Channel] = ByteDoneMaskCheck;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
            continue;
          }
          if (ByteDoneMask[Controller][Channel] == ByteDoneMaskCheck) { // All bytes failed on this channel, no need to sweep anymore
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
            continue;
          }
          ChannelIn  = &Inputs->Controller[Controller].Channel[Channel];
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ByteMask = (1 << Byte);
            DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
            IgnoreByte = FALSE;
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              IgnoreByte = TRUE;
            }
            if ((DramByte & 1) == 0) { // Ignore DRAM byte 0.
              IgnoreByte = TRUE;
            }
            if (IgnoreByte) {
              ByteDoneMask[Controller][Channel] |= ByteMask;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    ");
              continue;
            }
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            DataTrainFeedback = (UINT32) DataTrainFeedbackField & FeedbackMask;  // Get only DQ bits, not DQS
            PassFail = '#';
            if ((ByteDoneMask[Controller][Channel] & ByteMask) == 0) {
              if (Pattern == 0) {
                // First pattern
                Feedback[Controller][Channel][Byte] = (UINT8) DataTrainFeedback;
                PassFail = ' ';
              } else {
                // Second Pattern
                // If still read the same data, then DRAM was not able to decode the new command
                Failed = FALSE;
                if (Feedback[Controller][Channel][Byte] == (UINT8) DataTrainFeedback) {
                  Failed = TRUE;
                }
                if (MrcCountBitsEqOne (DataTrainFeedback) != NumOfOnes) {
                  Failed = TRUE;
                }
                if (Failed) {
                  Limit[Controller][Channel][Rank][Byte] = PiCode;
                  ByteDoneMask[Controller][Channel] |= ByteMask;
                } else {
                  PassFail = '.';
                }
              }
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c%02X ", PassFail, DataTrainFeedback);
          }  // for Byte
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
        }  // for Channel
      }  // for Controller
    } // for Pattern
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    BreakOut = TRUE;
    for (Controller = 0; Controller < MAX_CONTROLLER && BreakOut; Controller++) {
      for (Channel = 0; Channel < MaxChannel && BreakOut; Channel++) {
        if (ByteDoneMask[Controller][Channel] != ByteDoneMaskCheck) {
          BreakOut = FALSE;
        }
      }
    }
    if (BreakOut) {
      // Found the limit on all bytes on all channels on all mc - no need to sweep Pi any longer
      break;
    }

    PiCode += Step;
    if (Step > 0) {
      // Sweep up
      Done = (PiCode > Stop);
    } else {
      // Sweep down
      Done = (((INT16) PiCode) < Stop);
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
  return mrcSuccess;
}

/**
  This routine is used throughout LPDDR4  and LP5 ECT code to initialize DDR IO for CA training.
  For LP4 we do the following
  On "Odd" DRAM bytes: enable the following bits because we will use DATATRAINFEEDBACK to read back CA values on DQ[13:8] pins:
    DataControl2.ForceRxOn and ForceBiasOn (must be set first)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes we will send VrefCA values on DQ[6:0] pins:
    DataControl5.DdrCRMaskCntPulseNumStart[16:13] = 6 (number of masked DQS pulses)
    DataControl5.DdrCRNumOfPulses[12:11] = 2 (number of DQS pulses sent)
    DataControl5.Ddrcrdqsmaskcnten[10] = 1 (enables the special CBT VrefCA programming mode)
    DataControl0.TxOn (must be after DataControl5)

  Since we use CBT1 for LP5 , we do not send CAVref on DQ and hence we do not need to Mask Dqs Pulses.
  CA feedback is always recieved on CA [6:0]

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingInitIo (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput                   *Outputs;
  MrcChannelIn                *ChannelIn;
  MrcDdrType                  DdrType;
  INT64                       GetSetVal;
  INT64                       NumMaskedPulses;
  INT64                       NumOfPulses;
  UINT32                      Controller;
  UINT32                      Channel;
  UINT8                       Byte;

  Outputs         = &MrcData->Outputs;
  DdrType         = Outputs->DdrType;
  GetSetVal       = 1;
  NumMaskedPulses = 6;
  NumOfPulses     = 2;

  IoReset (MrcData); // To avoid ODT segment shift while in ForceOdtOn mode

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        ChannelIn = &MrcData->Inputs.Controller[Controller].Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (ChannelIn->DqsMapCpu2Dram[Byte]) {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
          }
        }
        MrcFlushRegisterCachedData (MrcData);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (ChannelIn->DqsMapCpu2Dram[Byte]) {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceOdtOn, WriteToCache, &GetSetVal);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxDisable, WriteToCache, &GetSetVal);
            MrcFlushRegisterCachedData (MrcData);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocCaTrainingMode, WriteNoCache, &GetSetVal);
          } else {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDqsMaskPulseCnt, WriteToCache, &NumMaskedPulses);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDqsPulseCnt, WriteToCache, &NumOfPulses);
            // @todo - Configure strobe toggle to get pattern.
            MrcFlushRegisterCachedData (MrcData);  // Must enable Pulse config before turning on Tx.
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxPiPwrDnDis, WriteCached, &GetSetVal);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxOn, WriteCached, &GetSetVal);
          }
        }
      }
    } //Controller
  } else {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceOdtOn, WriteToCache, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocCaTrainingMode, WriteNoCache, &GetSetVal);
        } //Byte
      } //Channel
    } //Controller
    CadbStartDelay (MrcData, 4);
  } //Lp5
}

/**
  This routine is used throughout LPDDR4 and LPDDR5 ECT code to restore DDR IO from CA training.
  For LP4 we do the following :
  On "Odd" DRAM bytes: disable the following bits:
    DataControl2.ForceRxOn and ForceBiasOn (must be cleared last)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes: disable the following bits:
    DataControl0.TxOn (must be cleared first)

  Since we use CBT1 for LP5 , we do not send CAVref on DQ and hence we do not need to Mask Dqs Pulses.
  CA feedback is always recieved on CA [6:0]

  The order of HW writes is opposite from LpddrCaTrainingInitIo.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
LpddrCaTrainingRestoreIo (
  IN MrcParameters *const  MrcData
  )
{
  MrcOutput                   *Outputs;
  MrcChannelIn                *ChannelIn;
  MrcDdrType                  DdrType;
  INT64                       GetSetVal;
  UINT32                      Controller;
  UINT32                      Channel;
  UINT8                       Byte;

  Outputs   = &MrcData->Outputs;
  DdrType   = Outputs->DdrType;
  GetSetVal = 0;

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        ChannelIn = &MrcData->Inputs.Controller[Controller].Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (ChannelIn->DqsMapCpu2Dram[Byte]) {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocCaTrainingMode, WriteNoCache, &GetSetVal);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceOdtOn, WriteToCache, &GetSetVal);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxDisable, WriteToCache, &GetSetVal);
          } else {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxOn, WriteToCache, &GetSetVal);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocTxPiPwrDnDis, WriteToCache, &GetSetVal);
          }
        }
        MrcFlushRegisterCachedData (MrcData);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (ChannelIn->DqsMapCpu2Dram[Byte]) {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
          }
        }
        MrcFlushRegisterCachedData (MrcData);
      }
    } //Controller
  } else {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocCaTrainingMode, WriteNoCache, &GetSetVal);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceOdtOn, WriteToCache, &GetSetVal);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
        }
        MrcFlushRegisterCachedData (MrcData);
      } //Channel
    } //Controller
    CadbStartDelay (MrcData, 0);
  } //Lp5
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

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDqsMaskPulseCnt, WriteToCache, &NumMaskedPulses);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDqsPulseCnt,     WriteToCache, &NumOfPulses);
  // @todo - Configure strobe toggle to get pattern.
  MrcFlushRegisterCachedData (MrcData);  // Must enable Pulse config before turning on Tx.

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,       WriteCached, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxOn,               WriteCached, &GetSetVal);
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
  INT64 GetSetVal;

  GetSetVal = 0;

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxOn,        WriteToCache, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,       WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  Enter / exit LPDDR4 and LPDDR5 CA training mode:
  If ENABLE:
    - Send MRW to MR13 OP[0] = 1, Wait tMRD
    - Force CKE low
    - Switch PLL to High frequency
  Else // DISABLE
    - Switch PLL to Low frequency
    - Force CKE high, Wait tFC
    - Send MRW to MR13 OP[0] = 0.

  NOTE: this has to be called at once on all participating channels using ChBitMask argument, because we switch to high frequency when enabling CBT.

  @param[in] MrcData                 - The MRC global data.
  @param[in] McChBitMask             - McChannels to work on.
  @param[in] RankBitMask             - Ranks to work on.
  @param[in] Enable                  - Enable or disable CBT.
  @param[in] CbtPhase                - CbtPhase in MR13 LP5
  @param[in,out] WckControlSave      - Save WckControl register.
  @param[in,out] MiscControl7Save    - Save MiscControl7 register.
  @param[in,out] DataRcompDataSave   - Save RcompData register.
  @retval mrcSuccess if succeeded
**/
MrcStatus
LpddrCommandTrainingMode (
  IN MrcParameters *const  MrcData,
  IN UINT8                 McChBitMask,
  IN UINT8                 RankBitMask,
  IN UINT8                 Enable,
  IN UINT8                 CbtPhase,
  IN OUT UINT32    *const  WckControlSave,
  IN OUT UINT32    *const  MiscControl7Save,
  IN OUT UINT32            DataRcompDataSave[MAX_CONTROLLER][MAX_SDRAM_IN_DIMM]
  )
{
  MrcStatus           Status;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  INT32               CtlPi;
  INT32               CmdPi;
  UINT16              Data;
  UINT8               MaxChannel;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               RankBit;
  UINT8               CbtModeForFsp;
  BOOLEAN             Lpddr4;
  UINT8               CbtMode;
  BOOLEAN             Set;

  Outputs       = &MrcData->Outputs;
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MaxChannel    = Outputs->MaxChannels;
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Status        = mrcSuccess;
  CbtMode       = Lpddr4 ? Enable : 0; //LP5 MR13 OP[6] = 0 - CBT1 mode, thats the default

  CtlPi = (Lpddr4) ? MRC_SAFE_LP4_CTL_PI : MRC_SAFE_LP5_CTL_PI;
  CmdPi = (Lpddr4) ? MRC_SAFE_LP4_CMD_PI : MRC_SAFE_LP5_CMD_PI;

  Set = Enable ? 1 : 0;

  if (!Enable) { // Exit CBT mode
    // Set Low frequency (1067), unless we're already there
    if ((Outputs->Frequency != f1067) && (MrcData->Inputs.LpFreqSwitch == TRUE)) {
      Status = MrcFrequencySwitch (MrcData, f1067, MRC_PRINTS_OFF);
      if (Status != mrcSuccess) {
        return Status;
      }
    }
    // Force CKE high, Wait tFC_Long = 250ns
    if (Lpddr4) {
      MrcForceCkeValue (MrcData, McChBitMask, 0xF);
    } else {
      // Set TxOn and change Tx termination i.e RcompDrvDn to look like Rx termination
      MrcSetRcompData (MrcData, Set, DataRcompDataSave);
      // Drive DQ7 low
      MrcDriveDq7 (MrcData, Set, WckControlSave, MiscControl7Save);
    }
    // lp5 this needs to be tCAENT = MRC_LP4_tFC_LONG_NS = 250ns
    MrcWait (MrcData, MRC_LP4_tFC_LONG_NS * MRC_TIMER_1NS);
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      IntCmdTiming  = &IntOutputs->Controller[Controller].CmdTiming[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        RankBit = (1 << Rank);
        if ((RankBit & RankBitMask) != 0) {
          // Use safe CS/CA PI settings, otherwise this MRW may get sampled as invalid command (or SRE etc.)
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankBit, MRC_IGNORE_ARG_8, CtlPi, 0);
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, CmdPi, 0);
          IoReset (MrcData);
          Data = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR[mrIndexMR13];
          if (Lpddr4) {
            MrcLpddr4SetMr13 (MrcData, CbtMode, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, &Data);
            Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR13, Data, FALSE);
          } else {
            MrcLpddr5SetMr13 (MrcData, CbtMode, &Data); //Set OP[6] = 0 - CBT1 mode
            Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR13, Data, FALSE);
            Data = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR[mrIndexMR16];
            CbtModeForFsp = Enable ? 2 : 0;
            //MrcLpddr5Mr16 - Set OP[3:2] - FSP-OP[1] , OP[5:4]  - CBT for FSP, OP[7] - CBT-Phase before starting patterns on CA bus
            MrcLpddr5SetMr16 (MrcData, MRC_IGNORE_ARG_8, Enable, CbtModeForFsp, MRC_IGNORE_ARG_8, CbtPhase, &Data);
            Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR16, Data, FALSE);
          }
          // Restore CS/CA PI settings from the host struct, CS is per SubCh
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankBit, MRC_IGNORE_ARG_8, IntCmdTiming->CtlPiCode[Rank], 0); //@todo RankMask needed
          ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCmd, MRC_IGNORE_ARG_8, 0xF, IntCmdTiming->CmdPiCode[0], 0);
          IoReset (MrcData);

          if (Status != mrcSuccess) {
            return Status;
          }
        } // if
      } // Rank
    } // Channel
  } // Controller

  if (Enable) {
    // Wait tMRD - guaranteed by MRH
    if (Lpddr4) {
      // Force CKE low
      MrcForceCkeValue (MrcData, McChBitMask, 0);
    } else {
      MrcSetRcompData (MrcData, Set, DataRcompDataSave);
      // Drive DQ7 high
      MrcDriveDq7 (MrcData, Set, WckControlSave, MiscControl7Save); // This will switch FSP_OP[0] to FSP_OP[1]
    }

    // Wait tCAENT = 250ns
    MrcWait (MrcData, MRC_LP_tCAENT_NS * MRC_TIMER_1NS);

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
  @param[in]  MaxValue    - Value to start RightLimit array at
  @param[in]  LeftLimit   - Array of left edge values per channel, rank and CPU byte
  @param[in]  RightLimit  - Array of right edge values per channel, rank and CPU byte
  @param[out] BestCs      - Array of best CS PI settings, per channel and group

  @retval mrcSuccess if succeeded
**/
MrcStatus
FindBestCsPi (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                MaxValue,
  IN  UINT16                LeftLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN  UINT16                RightLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM],
  OUT UINT16                BestCs[MAX_CONTROLLER][MAX_CHANNEL]
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            Controller;
  UINT32            Channel;
  UINT8             Rank;
  UINT8             Byte;
  UINT16            CsLeftLimit[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16            CsRightLimit[MAX_CONTROLLER][MAX_CHANNEL];

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  MrcCall->MrcSetMemWord ((UINT16 *) CsRightLimit, sizeof (CsRightLimit) / sizeof (UINT16), MaxValue);
  MrcCall->MrcSetMemWord ((UINT16 *) CsLeftLimit, sizeof (CsLeftLimit) / sizeof (UINT16), 0);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Finding best CS PIs:\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d Ch%d\t\tLeft\tRight\tCenter\n", Controller, Channel);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Find the worst case Right and Left limits across ranks
          CsRightLimit[Controller][Channel] = MIN (CsRightLimit[Controller][Channel], RightLimit[Controller][Channel][Rank][Byte]);
          CsLeftLimit[Controller][Channel]  = MAX (CsLeftLimit[Controller][Channel], LeftLimit[Controller][Channel][Rank][Byte]);
        } // for Byte
      } // for Rank

      // Find the Center for each Channel
      BestCs[Controller][Channel] = (CsRightLimit[Controller][Channel] + CsLeftLimit[Controller][Channel]) / 2;

      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\t\t%d\t%d\t%d\n",
        CsLeftLimit[Controller][Channel],
        CsRightLimit[Controller][Channel],
        BestCs[Controller][Channel]
        );
    } // for Channel
  } // for Controller

  return Status;
}

/**
  Send VrefCA on DQ[6:0] during LPDDR4 CBT.

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
  INT64                         GetSetVal;
  UINT32                        Controller;
  UINT32                        Channel;
  UINT32                        DramByte;
  UINT32                        DramBit;
  UINT32                        CpuByte;
  UINT32                        CpuBit;
  UINT32                        BitValue;
  UINT8                         MaxChannel;
  UINT8                         McChBitMask;
  UINT8                         DramValue;
  UINT8                         CpuValue;
  BOOLEAN                       Lpddr;
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

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MaxChannel = Outputs->MaxChannels;
  Lpddr      = Outputs->Lpddr;

  WDBPattern.IncRate    = 0;
  WDBPattern.Start      = 0;
  WDBPattern.Stop       = 1;
  WDBPattern.DQPat      = StaticPattern;
  WDBPattern.PatSource  = MrcPatSrcDynamic; // Don't use WDB
  WDBPattern.EnableXor  = FALSE;

  // Default VrefCA is 27.2% of VDD = 0.3v
  // Encoding: Range 1, 001101 --> 0x4D
  DramValue = 0x4D;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelIn  = &Inputs->Controller[Controller].Channel[Channel];
      MrcCall->MrcSetMem ((UINT8 *) VrefPattern, sizeof (VrefPattern), 0);
      for (CpuByte = 0; CpuByte < Outputs->SdramCount; CpuByte++) {
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
        MrcGetSetChStrb (MrcData, Controller, Channel, CpuByte, GsmIocDqOverrideData, WriteToCache, &GetSetVal);
        GetSetVal = 0xFF;   // Send all the bits
        MrcGetSetChStrb (MrcData, Controller, Channel, CpuByte, GsmIocDqOverrideEn,   WriteToCache, &GetSetVal);
        VrefPattern[0].Data |= MrcCall->MrcLeftShift64 (CpuValue, CpuByte * 8);
      }
    } // for Channel
  } // for Controller
  MrcFlushRegisterCachedData (MrcData);

  // Setup IO test: CmdPat=PatWr, NumCL=2, LC=1, NSOE, EnCADB=0, EnCKE=0, SubSeqWait=0
  IntOutputs->SkipZq = TRUE;
  SetupIOTest (MrcData, Outputs->McChBitMask, PatWr, 2, 1, &CPGCAddress, NSOE, &WDBPattern, 0, 0, 0);
  IntOutputs->SkipZq = FALSE;


  GetSetVal = 1;
  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      McChBitMask |= SelectReutRanks (MrcData, (UINT8) Controller, (UINT8) Channel, 1 << Rank, FALSE, 0);
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        continue;
      }

      // Set SC_GS_CFG_TRAINING.mask_cs to mask CS while sending CPGC commands.
      // Set SC_GS_CFG_TRAINING.ignore_cke to send CPGC commands even if CKE is LOW.
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccMaskCs,    WriteNoCache, &GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccIgnoreCke, WriteNoCache, &GetSetVal);
    }
  }
  MrcSetLoopcount (MrcData, 0); // Set BLOCK_REPEATS = 0 --> 1 iteration
  Cpgc20BaseRepeats (MrcData, 8, 1); // Set BASE_REPEATS to 7 (8 iterations)

  // Run Test: DQPat = StaticPattern, ClearErrors = 0, ResetMode = 0
  RunIOTest (MrcData, McChBitMask, WDBPattern.DQPat, 0, 0);

  // Wait tVrefCA_Long = 250ns
  MrcWait (MrcData, MRC_LP4_tVREFCA_LONG_NS * MRC_TIMER_1NS);

  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDqOverrideEn, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  // Restore MC registers
  GetSetVal = 0;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMaskCs,    WriteNoCache, &GetSetVal);
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccIgnoreCke, WriteNoCache, &GetSetVal);
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
  MrcIntOutput          *IntOutputs;
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcDdrType            DdrType;
  MrcStatus             Status;
  CADB_LINE             *CadbLines;
  UINT32                CadbCount;
  INT64                 Min;
  INT64                 Max;
  UINT32                *CadbMuxPattern;
  UINT32                Controller;
  UINT32                Channel;
  UINT32                WckControlSave;
  UINT32                MiscControl7Save;
  UINT32                DataRcompDataSave[MAX_CONTROLLER][MAX_SDRAM_IN_DIMM];
  UINT8                 MaxChannel;
  UINT8                 McChannelMask;
  UINT8                 Rank;
  UINT8                 RankBit;
  UINT8                 RankMask;
  UINT8                 TermRankMask;
  UINT16                PiLow;
  UINT16                PiHigh;
  UINT16                PiMiddle;
  UINT16                PiStep;
  UINT16                RightLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16                LeftLimit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16                BestCs[MAX_CONTROLLER][MAX_CHANNEL];
  BOOLEAN               Lpddr4;
#ifdef MRC_DEBUG_PRINT
  MrcChannelIn          *ChannelIn;
  UINT16                Left;
  UINT16                Right;
  UINT8                 Byte;
  UINT8                 DramByte;
#endif // MRC_DEBUG_PRINT

  Inputs           = &MrcData->Inputs;
  MrcCall          = Inputs->Call.Func;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  IntOutputs       = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  TermRankMask     = Inputs->CmdRanksTerminated;
  MaxChannel       = Outputs->MaxChannels;
  DdrType          = Outputs->DdrType;
  Lpddr4           = (DdrType == MRC_DDR_TYPE_LPDDR4);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EarlyChipSelectTrainingLp4 started\n");

  Status = mrcSuccess;
  RankMask  = Outputs->ValidRankMask;

  MrcGetSetLimits (MrcData, CtlGrpPi, &Min, &Max, NULL);
  PiLow     = (UINT16) Min;
  PiHigh    = (UINT16) Max;
  PiMiddle  = (PiHigh - PiLow + 1) / 2; // // Will be updated below from the host struct
  PiStep = (PiHigh + 1) / 64;
  CadbLines = Lpddr4 ? CadbLinesLp4 : CadbLinesLp5;
  CadbCount = Lpddr4 ? ARRAY_COUNT (CadbLinesLp4) : ARRAY_COUNT (CadbLinesLp5);
  CadbMuxPattern = Lpddr4 ? CadbMuxLp4Pattern2 : CadbMuxLp5RisingPattern2;



  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PiLow = %d, PiHigh = %d PiStep = %d\n", PiLow, PiHigh, PiStep);
  MrcCall->MrcSetMemWord ((UINT16 *) RightLimit, sizeof (RightLimit) / sizeof (UINT16), PiHigh);
  MrcCall->MrcSetMemWord ((UINT16 *) LeftLimit, sizeof (LeftLimit) / sizeof (UINT16), PiLow);

  // Init DDR IO for CA training
  LpddrCaTrainingInitIo (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankBit = 1 << Rank;
    if ((RankBit & RankMask) == 0) {
      continue;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Enable Termination on the terminated rank via FSP-High
      MrcLpddrSetCbtCaOdtEn (MrcData, TRUE);
    }


    McChannelMask = 0;     // Bitmask of channels that have current rank populated
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        McChannelMask |= (1 << ((Controller * MaxChannel) + Channel));
        IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];
        PiMiddle = IntCmdTiming->CtlPiCode[Rank];  // Found in EarlyCsCmdLpddr()
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IntCmdTiming->CtlPiCode[%d] = %d\n", Rank, PiMiddle);
      }  // for Channel
    } // for Controller

    // Setup and Enter CBT Mode for this Rank.
    SetupCaTrainingCadb (MrcData, Rank, CadbLines, CadbCount, CadbMuxPattern);
    Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 1, 0, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
    if (Status != mrcSuccess) {
      return Status;
    }

    if (Lpddr4) {
      // Send VrefCA on DQ[6:0]
      MrcSendCaVrefOnDq (MrcData, Rank);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "R%d: MrcSendCaVrefOnDq done\n", Rank);
    }

    // Sweep CS Pi up and down from the middle, on both channels at the same time
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiHigh, PiStep, RightLimit);
    ChipSelectFindEdge (MrcData, Rank, PiMiddle, PiLow, -PiStep, LeftLimit);

#ifdef MRC_DEBUG_PRINT
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        ChannelIn  = &Inputs->Controller[Controller].Channel[Channel];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CS training data Mc%d Ch%d Rank%d\nCPU Byte\tLeft\tRight\tWidth\n", Controller, Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            continue;
          }
          DramByte = ChannelIn->DqsMapCpu2Dram[Byte];
          if ((DramByte & 1) == 0) {
            // Ignore DRAM bytes 0, 2, 4 and 6 - they don't provide feedback
            continue;
          }
          Left  = LeftLimit[Controller][Channel][Rank][Byte];
          Right = RightLimit[Controller][Channel][Rank][Byte];
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t%d\t%d\t%d\n", Byte, Left, Right, Right - Left);
        }
      }
    } // for Controller
#endif // MRC_DEBUG_PRINT

    // Exit CA training mode on the current rank
    Status = LpddrCommandTrainingMode (MrcData, McChannelMask, RankBit, 0, 0, &WckControlSave, &MiscControl7Save, DataRcompDataSave);
    if (Status != mrcSuccess) {
      return Status;
    }

    if ((RankBit & TermRankMask) == 0) {
      // Disable Termination on the terminated rank via FSP-High
      Status = MrcLpddrSetCbtCaOdtEn (MrcData, FALSE);
    }
  }  // for Rank
  // Restore DDR IO values that were used for CMD training
  LpddrCaTrainingRestoreIo (MrcData);
  // Select optimal CS timings for all populated controllers/channels
  FindBestCsPi (MrcData, PiHigh, LeftLimit, RightLimit, BestCs);

  // Apply the new CS settings
  // Note that both ranks share the same PI setting
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        // Shift CS per subch
        ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask,
          MRC_IGNORE_ARG_8, BestCs[Controller][Channel], 1);
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
EarlyCommandTrainingLpddr (
  IN MrcParameters *const MrcData
)
{
  MrcOutput       *Outputs;
  MrcInput        *Inputs;
  MrcStatus       Status;
  MrcDdrType      DdrType;
  UINT8           BiasPMCtrl;
  UINT32          Controller;
  UINT32          Channel;
  UINT32          Byte;
  INT64           GetSetVal;
  BOOLEAN         Lpddr4;

  Outputs = &MrcData->Outputs;
  Inputs = &MrcData->Inputs;
  Status  = mrcSuccess;
  BiasPMCtrl = 0xFF;
  DdrType    = Outputs->DdrType;
  Lpddr4     = (DdrType == MRC_DDR_TYPE_LPDDR4);

  // Run CPU-to-DRAM DQ Mapping
  if ((Inputs->CpuModel == cmTGL_ULX_ULT) && (Inputs->CpuStepping > csTglA0)) {
    Status = MapCA2DQPinsLp4 (MrcData);
  }
  if (Status != mrcSuccess) {
    return Status;
  }

  MrcBlockTrainResetToggle (MrcData, FALSE);

  for (Controller = 0; (Controller < MAX_CONTROLLER) && (BiasPMCtrl == 0xFF); Controller++) {
    for (Channel = 0; (Channel < Outputs->MaxChannels) && (BiasPMCtrl == 0xFF); Channel++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocBiasPMCtrl, ReadFromCache, &GetSetVal);
          BiasPMCtrl = (UINT8) GetSetVal;
          break;
        }
      }
    }
  }

  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  // Early 2D CS/CMD training - find the good starting point for the rest of the ECT steps.
  Status = EarlyCsCmdLpddr (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }
  //No IoReset due to CBT entry on next training

  // CS is single pumped in LP5 and 4 times slower than WCK so we dont need to train it.
  // Run CS vs. CLK training
  if (Lpddr4) {
    Status = EarlyChipSelectTrainingLp4 (MrcData);
    if (Status != mrcSuccess) {
      return Status;
    }
  }
  //No IoReset due to CBT entry on next training

  // Run CA vs. CLK training
  Status = EarlyCaTraining (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }
  IoReset (MrcData);

  GetSetVal = BiasPMCtrl;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
  MrcSetWritePreamble (MrcData);

  // Program DESWIZZLE_HIGH/LOW registers
  ProgramDeswizzleRegisters (MrcData);

  // Set FSP-OP = 1, set High frequency
  Status = MrcLpddrSwitchToHigh (MrcData, MRC_PRINTS_ON);

  MrcBlockTrainResetToggle (MrcData, TRUE);

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
  UINT8               Controller;
  UINT8               ChBitMask;
  UINT8               RankMask;
  UINT16              MidPointCmd[MAX_COMMAND_GROUPS][MAX_CONTROLLER][MAX_CHANNEL];
  UINT8               CmdGroup;
  UINT8               CmdGroupMax;
  BOOLEAN             ExitOnFailure;
  BOOLEAN             Ddr4;
  MC0_CH0_CR_CADB_CFG_STRUCT          CadbConfig;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  IntOutputs        = (MrcIntOutput *) (MrcData->IntOutputs.Internal);

  ExitOnFailure = (BOOLEAN) Inputs->ExitOnFailure;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  ChBitMask     = Outputs->ValidChBitMask & ChannelMask;
  RankMask      = Outputs->ValidRankMask;

  CmdGroupMax = (Ddr4) ? MAX_COMMAND_GROUPS : 1;

  // Program default rank mapping
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
    }
  }

  if (SetupCadb) {
    // SetupIOTest is already called in TrainDDROptParms and LCT.
    SetupIOTestCADB (MrcData, ChBitMask, LoopCount, NTHSOE, 1, 0);
  }

  // Get the midpoint for CMD and CTL
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    IntControllerOut = &IntOutputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
      for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
        MidPointCmd[CmdGroup][Controller][Channel] = IntCmdTiming->CmdPiCode[CmdGroup];
      }
    }
  }

  // Center Command Timing
  for (CmdGroup = 0; CmdGroup < CmdGroupMax; CmdGroup++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n*** Center CMD_Pi%u Code Timing\n", CmdGroup);
    Status = CmdTimingCentering (MrcData, MrcIterationCmd, RankMask, (1 << CmdGroup), MidPointCmd[CmdGroup]);
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

