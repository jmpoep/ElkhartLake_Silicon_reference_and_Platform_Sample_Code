/** @file
  The write leveling flow is the first part of the write training.
  In this stage the memory controller needs to synchronize its DQS sending
  with the clock for each DRAM.  The DRAM can be put in a mode where for a
  write command it responds by sampling the clock using DQS and sending it
  back as the data.  The IO can receive this and tune the DQS alignment so
  it will appear in sync with the clock at the DRAM side.
  The following algorithm is used for the write leveling flow:

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
#include "MrcWriteLeveling.h"
#include "MrcCpgcApi.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcChipApi.h"
#include "MrcDdrIoOffsets.h" //@todo remove when setting Write Leveling mode is behind a Memory API

///
/// Local defines - used by this file only
///
// This defines the maximum ADD delay that can be programmed to the register. It may change in the future
#define MAX_ADD_DELAY       (7)
#define MAX_DEC_DELAY       (15)
#define MAX_ADD_RANK_DELAY  (7)
#define RTL_CONSTANT        (10)

// Separation required by hardware.
#define TX_FIFO_SEPARATION (-2)

// Dq/Dqs sweep range: LP4 need larger sweep due to tDQS2DQ variation of 200-800 ps.
// This is calucluated in the function.
#define DQ_SWEEP_START            (-15)
#define DQ_SWEEP_END              (15)
#define DQ_SWEEP_STEP             (5)
#define DQSDQ_SWEEP_STEP          (2)

/**
  This function executes the Jedec Write Leveling Cleanup.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeded, return mrcSuccess
**/
MrcStatus
WriteLevelingFlyBy (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MrcStatus           Status2;
  UINT64              ErrStatus;
  INT64               GetSetVal;
  INT64               GetSetVal1;
  //INT64               GetSetEn;
  INT64               FifoFlybyDelay;
  INT64               TxDqDqsDelayAdj;
  INT64               TxDqFifoWrEn;
  INT64               TxDqFifoRdEn;
  INT32               TxFifoSeparation;
  UINT32              tCWL;
  UINT32              WrLvlTotPiDly[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              WrLvlRankMin[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32              WrLvlRankMax[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32              WrLvlChMin[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              WrLvlChMax[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              Offset;
  UINT32              Tdqs2dqMinFs;
  UINT32              Tdqs2dqMaxFs;
  UINT32              Tdqs2dqCenterFs;
  UINT32              AddOneQclk[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32              MaxDec;
  UINT32              MaxAdd;
  INT32               WrLvlChMinReserved;
  INT32               DqSweepStart;
  INT32               DqSweepStop;
  INT32               DqOffset;
  INT32               WrLvlChCycle[MAX_CONTROLLER][MAX_CHANNEL];
  INT32               WrLvlRankCycle[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32               MaxChTxDqFifoRdEnDelay[MAX_CONTROLLER][MAX_CHANNEL];
  INT32               DeltaPi;
  INT32               CycleDelay[MAX_CONTROLLER][MAX_CHANNEL];
  INT32               GlobalByteOff;
  INT32               StartOffset;
  INT32               EndOffset;
  INT32               CurrentOffset;
  UINT16              BytePass[MAX_CONTROLLER][MAX_CHANNEL]; // Bit mask indicating which ch/byte has passed
  UINT16              SavedTxDqsVal[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM]; // Saved TxDqs value
  UINT16              ByteMask;
  UINT16              ValidByteMask;
  UINT16              Result;
  UINT16              SkipMe;
  UINT16              MaxCode;
  UINT16              MinCode;
  UINT16              TxDqValue;
  UINT16              TxDqsValue;
  UINT16              DqPiReserve;
  UINT16              TxDqMaxVal;
  //UINT16              NumIters; //Static Pattern # of Iterations per CL
  INT16               ByteDqOffsetPi[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8               Param;
  UINT8               Channel;
  UINT8               Controller;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               McChBitMask;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               ValidRankMask;
  UINT8               RankHalf;
  UINT8               RankMod2;
  UINT8               PiCycleDec;
  UINT8               PiCycleAdd;
  UINT8               LoopCount;
  UINT8               SdramCount;
  UINT8               MaxChannels;
  UINT8               IpChannel;
  INT8                DqSweepStep;
  BOOLEAN             Gear2;
  BOOLEAN             Done;
  BOOLEAN             Lpddr4;
  BOOLEAN             Lpddr;
  BOOLEAN             Saturated;
  MC0_CH0_CR_SC_WR_DELAY_STRUCT ScWrDelay;

  // Same pattern on all 64 DQ's
  // 4 different CL's:
  // 11111111 00000000 11110000 00001111
  //static UINT32 Pattern[8][2] = {
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF },
  //  { 0x0FF000FF, 0x0FF000FF }
  //};

#ifdef MRC_DEBUG_PRINT
  UINT8               BitGroupErr[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
#endif // MRC_DEBUG_PRINT

  Inputs = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;
  MaxChannels = Outputs->MaxChannels;
  Debug = &Outputs->Debug;
  Gear2 = Outputs->Gear2;
  Status = mrcSuccess;
  Done = TRUE;
  tCWL = 0;
  DqPiReserve = 128;
  //GetSetEn              = 1;
  SdramCount = Outputs->SdramCount;
  MrcCall->MrcSetMem ((UINT8 *) CycleDelay, sizeof (CycleDelay), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlRankMax, sizeof (WrLvlRankMax), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlRankMin, sizeof (WrLvlRankMin), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChMax, sizeof (WrLvlChMax), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChMin, sizeof (WrLvlChMin), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChCycle, sizeof (WrLvlChCycle), 0);
  MrcCall->MrcSetMem ((UINT8 *) ByteDqOffsetPi, sizeof (ByteDqOffsetPi), 0);
  MrcCall->MrcSetMem ((UINT8 *) AddOneQclk, sizeof (AddOneQclk), 0);

  MrcGetSetLimits (MrcData, TxDqDelay, NULL, &GetSetVal, NULL);
  TxDqMaxVal = (UINT16) GetSetVal;

  // 0.5UI for Gear 1, 1.5UI for Gear 2
  TxDqDqsDelayAdj = Gear2 ? 96 : 32;
  LoopCount = 1;
  //NumIters = 1;
  // Check memory used
  Lpddr4 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  McChBitMask = Outputs->McChBitMask;
  ValidRankMask = Outputs->ValidRankMask;
  ValidByteMask = (MRC_BIT0 << SdramCount) - 1; // 0x1FF or 0xFF

  TxFifoSeparation = TX_FIFO_SEPARATION;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      MaxChTxDqFifoRdEnDelay[Controller][Channel] = 0;
    }
  }
  //SetupIOTestStatic (MrcData, McChBitMask, LoopCount, NSOE, 0, 0, NumIters, Pattern);
  SetupIOTestBasicVA (MrcData, McChBitMask, LoopCount, NSOE, 0, 0, 8, PatWrRd, 0, 8);
  MaxAdd = MAX_ADD_DELAY * (Gear2 ? 2 : 1) + MAX_ADD_RANK_DELAY;
  MaxDec = 0;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      if (!IS_MC_SUB_CH (Lpddr, Channel)) {
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCWL, ReadFromCache | PrintValue, &GetSetVal);
        tCWL = (UINT32) GetSetVal;
        if (Lpddr4) {
          tCWL++;     // Due to tDQSS on LP4
        }
      }
      MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tCWL = %d, Separation = %d\n", tCWL, TxFifoSeparation);

      // Make sure TxDqFifoRdEnTcwlDelay won't become negative
      if (Gear2) {
        if (TxFifoSeparation < 0) {
          MaxDec = (tCWL - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2) + TxFifoSeparation + 1) / 2;
        } else {
          MaxDec = (tCWL - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2)) / 2;
        }
      } else {
        if (TxFifoSeparation < 0) {
          MaxDec = tCWL - 2 + TxFifoSeparation;
        } else {
          MaxDec = tCWL - 2;
        }
      }
      MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ensuring TxDqFifoRdEnTcwlDelay is not negative: MaxDec = %d \n", MaxDec);
      break;
    }
  } //Controller

  // Determine the Dq/Dqs sweep range during the cycle search.
  if (Lpddr4) {
    Param = WrTLp4;
    MrcGetTdqs2dq (MrcData, TRUE, &Tdqs2dqMinFs);
    MrcGetTdqs2dq (MrcData, FALSE, &Tdqs2dqMaxFs);
    Tdqs2dqMaxFs -= 200000;
    MrcGetTdqs2dqCenter (MrcData, &Tdqs2dqCenterFs);
    DqSweepStart = -1 * (MrcPicoSec2PiTick (MrcData,  Tdqs2dqCenterFs - Tdqs2dqMinFs));
    DqSweepStop = MrcPicoSec2PiTick (MrcData, Tdqs2dqMaxFs - Tdqs2dqCenterFs);
    DqSweepStep = DQSDQ_SWEEP_STEP;
  } else {
    Param = WrT;
    DqSweepStart  = DQ_SWEEP_START;
    DqSweepStop   = DQ_SWEEP_END;
    DqSweepStep   = DQ_SWEEP_STEP;
  }

  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Params : DqSweepStart: %d, DqSweepStop: %d, DQ_SWEEP_STEP: %d\n", DqSweepStart, DqSweepStop, DqSweepStep);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // Select Rank for REUT test
    McChBitMask   = 0;
    RankMask    = MRC_BIT0 << Rank;
    RankHalf    = Rank / 2;
    RankMod2    = Rank % 2;

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
        BytePass[Controller][Channel] = 0;
      }
    }
    // Skip if both channels empty
    if (!(RankMask & ValidRankMask)) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);
    // Sweep through the cycle offsets until we find a value that passes
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Sweep through the cycle offsets until we find a value that passes\n");
    // Find the minimum and maximum PI setting across Tx DQ/DQS on a given Rank, on all channels.
    // Determine how far we can use the PI value to shift the Cycle. Min value will use DQS,
    // Max value will use DQ (DQ is DQS + 32 (gear1) or DQS + 96 (gear2), and also plus tDQS2DQ for LP4).
    MaxCode = 0;
    MinCode = TxDqMaxVal;

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
          TxDqValue = (UINT16) GetSetVal;
          MaxCode = MAX (MaxCode, TxDqValue);

          MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
          TxDqsValue = (UINT16) GetSetVal;
          SavedTxDqsVal[Controller][Channel][Byte] = TxDqsValue;
          MinCode = MIN (MinCode, TxDqsValue);
        }
      }
    } //Controller
    PiCycleDec = (UINT8) (MinCode / 128);
    PiCycleAdd = (UINT8) ((TxDqMaxVal - MaxCode) / 128);

    if (Gear2) {
      PiCycleDec = 0;
      StartOffset = - 2 * MaxDec;
    } else {
      StartOffset = -PiCycleDec - MaxDec;  // We can go more negative offsets using PI settings
    }
    EndOffset   = MaxAdd + PiCycleAdd;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Params : MaxDec: %d, MaxAdd: %d, PiCycleDec: %d, PiCycleAdd: %d\n", MaxDec, MaxAdd, PiCycleDec, PiCycleAdd);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MinCode: %d, MaxCode: %d, Start: %d, End: %d\n", MinCode, MaxCode, StartOffset, EndOffset);
    if (RankMask & ValidRankMask) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel                 0                1\nDelay  DqOffset   Byte \t");
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE, (
        SdramCount == MAX_SDRAM_IN_DIMM
        ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
        );
    }

    for (CurrentOffset = StartOffset; CurrentOffset <= EndOffset; CurrentOffset++) {
      // Program new delay offsets to DQ/DQS timing:
      GlobalByteOff = 0;
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          GlobalByteOff = 0;
          if (Gear2) {
            AddOneQclk[Controller][Channel] = 1;
            if (CurrentOffset > (INT32) MaxAdd) {                 // Will use DQ/DQS PI to go right
              CycleDelay[Controller][Channel] = MAX_ADD_DELAY + MAX_ADD_RANK_DELAY;
              GlobalByteOff = 128 * (CurrentOffset - MaxAdd);
            } else if (CurrentOffset < -1 - 2 * (INT32) MaxDec) {     // Will use DQ/DQS PI to go left
              CycleDelay[Controller][Channel] = -1 * MaxDec;
              GlobalByteOff = 128 * (CurrentOffset + 2 * MaxDec);
            } else {
              if (CurrentOffset > 2 * MAX_ADD_DELAY) {            // Will use TxDqFifoRdEnFlybyDelay
                CycleDelay[Controller][Channel] = CurrentOffset - MAX_ADD_DELAY;
              } else {                                            // Will use Dec_tCWL / Add_tCWL
                AddOneQclk[Controller][Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;  // Add one QCLK in Gear2 every other cycle offset (when CurrentOffset is even)
                if (CurrentOffset > 0) {
                  CycleDelay[Controller][Channel] = (CurrentOffset + 1) / 2;
                } else {
                  CycleDelay[Controller][Channel] = CurrentOffset / 2;
                }
              }
            }
          } else {  // Gear1
            if (CurrentOffset > (INT32) MaxAdd) {
              CycleDelay[Controller][Channel] = MaxAdd;
              GlobalByteOff = 128 * (CurrentOffset - MaxAdd);
            } else if (CurrentOffset < -1 * (INT32) MaxDec) {
              CycleDelay[Controller][Channel] = -1 * MaxDec;
              GlobalByteOff = 128 * (CurrentOffset + MaxDec);
            } else {
              CycleDelay[Controller][Channel] = CurrentOffset;
            }
          }

          // Write Tx DQ/DQS Flyby delays
          // Note that we program these also in case GlobalByteOff is zero, because it might have been non-zero in the previous cycle.
          if (GlobalByteOff != 0) {
            MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nAdd GlobalByteOff = %d to TxDQS Flyby delay: Mc %d Ch %d \n", GlobalByteOff, Controller, Channel);
          }
          for (Byte = 0; Byte < SdramCount; Byte++) {
            if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
              GetSetVal = SavedTxDqsVal[Controller][Channel][Byte] + GlobalByteOff;
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
              GetSetVal += TxDqDqsDelayAdj;
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal);
            }
          }
          MrcFlushRegisterCachedData (MrcData);

          // Write SC_WR_DELAY
          FifoFlybyDelay = 0;
          ScWrDelay.Data = 0;
          if (CycleDelay[Controller][Channel] < 0) {
            ScWrDelay.Bits.Dec_tCWL = ABS (CycleDelay[Controller][Channel]);
            ScWrDelay.Bits.Add_tCWL = 0;
          } else {
            if (CycleDelay[Controller][Channel] > MAX_ADD_DELAY) {
              ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
              FifoFlybyDelay = CycleDelay[Controller][Channel] - MAX_ADD_DELAY;
            } else {
              ScWrDelay.Bits.Add_tCWL = CycleDelay[Controller][Channel];
            }
            ScWrDelay.Bits.Dec_tCWL = 0;
          }
          IpChannel = LP_IP_CH (Lpddr, Channel);
          Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WR_DELAY_REG, MC1_CH0_CR_SC_WR_DELAY_REG, Controller, MC0_CH1_CR_SC_WR_DELAY_REG, IpChannel);
          MrcWriteCR (MrcData, Offset, ScWrDelay.Data);  // @todo GetSet

          GetSetVal1 = 0;
          TxDqFifoWrEn = 0;
          TxDqFifoRdEn = 0;
          // @todo <CNL> check single sub-ch case
          MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, TxDqFifoRdEnFlybyDelay, WriteToCache, &FifoFlybyDelay);
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache, &GetSetVal1);

          if (Gear2) {
            TxDqFifoWrEn = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) + (2 * ScWrDelay.Bits.Add_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
          } else {
            TxDqFifoWrEn = tCWL - ScWrDelay.Bits.Dec_tCWL + ScWrDelay.Bits.Add_tCWL - 2; // TxDqFifoWrEnTcwlDelay(DClk)
          }
          TxDqFifoRdEn = TxDqFifoWrEn + TxFifoSeparation + AddOneQclk[Controller][Channel]; // TxDqFifoRdEnTcwlDelay(DCLK)

          if (TxDqFifoRdEn < 0) {
            TxDqFifoRdEn = 0;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s Not enough Tx FIFO separation! TxDqFifoWrEn: %d, TxFifoSeparation: %d\n", gErrString, (UINT32) TxDqFifoWrEn, TxFifoSeparation);
          }
          MrcGetSetMcCh (MrcData, Controller, Channel, TxDqFifoWrEnTcwlDelay, WriteToCache, &TxDqFifoWrEn);
          MrcGetSetMcCh (MrcData, Controller, Channel, TxDqFifoRdEnTcwlDelay, WriteToCache, &TxDqFifoRdEn);
          MrcFlushRegisterCachedData (MrcData);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nGlobalByteOff: %d, Dec: %d, Add: %d, 1Qclk: %d, WrEn: %d, RdEn: %d, flyby: %d\n",
            GlobalByteOff, ScWrDelay.Bits.Dec_tCWL, ScWrDelay.Bits.Add_tCWL, AddOneQclk[Controller][Channel], (UINT32) TxDqFifoWrEn, (UINT32) TxDqFifoRdEn, (UINT32) FifoFlybyDelay);
        } // for Channel
      } //Controller
      if (!Lpddr4) {
        // Reset FIFOs & Reset DRAM DLL. Wait 1uS for test to complete
        Status = IoReset (MrcData);
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          ControllerOut = &Outputs->Controller[Controller];
          for (Channel = 0; Channel < MaxChannels; Channel++) {
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              ChannelOut = &ControllerOut->Channel[Channel];
              Status = MrcWriteMRS (
                MrcData,
                Controller,
                Channel,
                RankMask,
                mrMR0,
                ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
              );
            }
          }
        }
        MrcWait (MrcData, (1 * MRC_TIMER_1US));
      }
      // Run Test sweeping DQ to DQS searching for a Pass.
      for (DqOffset = DqSweepStart; DqOffset <= DqSweepStop; DqOffset += DqSweepStep) {
        // Update Offset
        ChangeMargin (MrcData, Param, DqOffset, 0, 1, 0, 0, Rank, 0, 0, 0, 0);
        // Run Test
        // DQPat = BasicVA, DumArr, ClearErrors = 1, mode = 0
        RunIOTest (MrcData, McChBitMask, StaticPattern, 1, 0);
        // Update results for all ch/bytes
        Done = TRUE;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 3d\t% 3d\t       \t", CurrentOffset, DqOffset);
//        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CycleDelay: %3d, FifoRdEnFlyby: %d, FifoRdEn: %2d, FifoWrEn: %2d, Dec: %d, Add: %d, Add1Q: %d ",
//          CycleDelay[0], (UINT32) FifoFlybyDelay, (UINT32) TxDqFifoRdEn, (UINT32) TxDqFifoWrEn, ScWrDelay.Bits.Dec_tCWL, ScWrDelay.Bits.Add_tCWL, ScWrDelay.Bits.Add_1Qclk_delay);
        // Update results for all ch/bytes
#ifdef MRC_DEBUG_PRINT
        MrcCall->MrcSetMem((UINT8 *)BitGroupErr, sizeof (BitGroupErr), 0);
#endif // MRC_DEBUG_PRINT
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          ControllerOut = &Outputs->Controller[Controller];
          for (Channel = 0; Channel < MaxChannels; Channel++) {
            if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
              if (Channel == 0) {
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  (SdramCount == MAX_SDRAM_IN_DIMM) ? "                 " : "                "
                );
              }
              continue;
            }
            ChannelOut = &ControllerOut->Channel[Channel];
            ValidByteMask = ChannelOut->ValidByteMask;
            Result = 0;
            if (MrcChannelExist (MrcData, Controller, Channel)) {
              // Read out per byte error results and check for any byte error
              MrcGetMiscErrStatus (MrcData, Controller, Channel, ByteGroupErrStatus, &ErrStatus);
              Result = (UINT16) ErrStatus;
#ifdef MRC_DEBUG_PRINT
              MrcGetBitGroupErrStatus (MrcData, Controller, Channel, BitGroupErr[Controller][Channel]);
#endif // MRC_DEBUG_PRINT
            }
            SkipMe = (Result & ValidByteMask) | BytePass[Controller][Channel];

            for (Byte = 0; Byte < SdramCount; Byte++) {
              if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
                continue;
              }
              ByteMask = 1 << Byte;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Result & ValidByteMask) & ByteMask) ? "# " : ". ");
              // If this byte has failed or previously passed, nothing to do
              if (SkipMe & ByteMask) {
                continue;
              }
              // Pass case
              ByteDqOffsetPi[Controller][Channel][Rank][Byte] = (INT16) DqOffset;
              BytePass[Controller][Channel] |= ByteMask;
              // Adjust delay reference point to MAX_DEC_DELAY so they will be positive delays only
              if (Gear2) {
                WrLvlTotPiDly[Controller][Channel][Rank][Byte] = 128 * (CurrentOffset + 2 * MAX_DEC_DELAY + 1) + SavedTxDqsVal[Controller][Channel][Byte];
              } else {
                WrLvlTotPiDly[Controller][Channel][Rank][Byte] = 128 * (CurrentOffset + MAX_DEC_DELAY) + SavedTxDqsVal[Controller][Channel][Byte];
              }
              // Track max/min pi per ch and rank
              if (WrLvlChMax[Controller][Channel] < WrLvlTotPiDly[Controller][Channel][Rank][Byte]) {
                WrLvlChMax[Controller][Channel] = WrLvlTotPiDly[Controller][Channel][Rank][Byte];
              }
              if (WrLvlChMin[Controller][Channel] > WrLvlTotPiDly[Controller][Channel][Rank][Byte]) {
                WrLvlChMin[Controller][Channel] = WrLvlTotPiDly[Controller][Channel][Rank][Byte];
              }
              if (WrLvlRankMax[Controller][Channel][Rank] < WrLvlTotPiDly[Controller][Channel][Rank][Byte]) {
                WrLvlRankMax[Controller][Channel][Rank] = WrLvlTotPiDly[Controller][Channel][Rank][Byte];
              }
              if (WrLvlRankMin[Controller][Channel][Rank] > WrLvlTotPiDly[Controller][Channel][Rank][Byte]) {
                WrLvlRankMin[Controller][Channel][Rank] = WrLvlTotPiDly[Controller][Channel][Rank][Byte];
              }
              // MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrLvlTotPiDly[Channel=%d][Rank=%d][Byte=%d]=%d SavedTxDqsVal[Channel][Byte]=%d\n", Channel, Rank, Byte, WrLvlTotPiDly[Channel][Rank][Byte],SavedTxDqsVal[Channel][Byte]);
            } // for Byte
            // MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrLvlRankMin[Channel=%d][Rank=%d]=%d WrLvlChMin[Channel=%d]=%d\n", Channel, Rank, WrLvlRankMin[Channel][Rank], Channel, WrLvlChMin[Channel]);
            if (BytePass[Controller][Channel] != ValidByteMask) {
              Done = FALSE;
            }
          } // for Channel
        } // Controller
#ifdef MRC_DEBUG_PRINT
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannels; Channel++) {
            ErrStatus = 0;
            for (Byte = 0; Byte < SdramCount; Byte++) {
              ErrStatus |= MrcCall->MrcLeftShift64 (BitGroupErr[Controller][Channel][Byte], Byte * 8);
            }
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "0x%016llX ",
                ErrStatus
              );
            }
          }
        } //Controller
#endif  // MRC_DEBUG_PRINT
        // Jump out of the for DqOffset loop if everybody is passing
#ifdef MRC_DEBUG_PRINT
        if ((Done == TRUE) && (DqOffset >= DqSweepStop)) {
#else
        if (Done == TRUE) {
#endif // MRC_DEBUG_PRINT
          break;
        }
      } // for DqOffset

      // Jump out of the for offset loop if everybody is passing
      if (Done == TRUE) {
        break;
      }
    } // for offset
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
    // Walk through and find the correct value for each ch/byte
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        if (BytePass[Controller][Channel] != ChannelOut->ValidByteMask) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "Error! Write Leveling CleanUp - Couldn't find a passing value for all bytes on Channel %u Rank %u:\nBytes - ",
            Controller,
            Channel,
            Rank
          );
#ifdef MRC_DEBUG_PRINT
          for (Byte = 0; Byte < SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, ((BytePass[Controller][Channel] ^ ChannelOut->ValidByteMask) & (1 << Byte)) ? "%d " : "", Byte);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
#endif
          if (Inputs->ExitOnFailure) {
            return mrcWriteLevelingError;
          }
        }
        if (!Lpddr4) {
          // Clean up after Test
          Status = MrcWriteMRS (
            MrcData,
            Controller,
            Channel,
            RankMask,
            mrMR0,
            ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
          );
          MrcWait (MrcData, (1 * MRC_TIMER_1US));
        }
      } // for Channel
    } //Controller
  } // for Rank

  // Calculate Cycle and PI Delay per channel and per rank
  //  1. Check if possible to reserve PI's if needed
  //  2. Program the global min cycle to each channel
  //  3. Program rank cycle delay
  //  4. Program byte PI delay + PI reserved as needed
  Saturated = FALSE;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Program per channel delay - Add/Dec
      WrLvlChMinReserved = MAX ((INT32) WrLvlChMin[Controller][Channel] - DqPiReserve, 0);

      ScWrDelay.Data = 0;
      if (Gear2) {
        AddOneQclk[Controller][Channel] = 1;
        WrLvlChCycle[Controller][Channel] = MIN (WrLvlChMinReserved / 128, (2 * MAX_ADD_DELAY + 2 * MAX_DEC_DELAY + 1));
        if (WrLvlChCycle[Controller][Channel] <= (2 * MAX_DEC_DELAY + 1)) {
          CurrentOffset = (2 * MAX_DEC_DELAY + 1) - WrLvlChCycle[Controller][Channel];
          AddOneQclk[Controller][Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;
          ScWrDelay.Bits.Dec_tCWL = CurrentOffset / 2;
          // Keeping ScWrDelay.Bits.Add_tCWL = 0;
        } else {
          // Keeping ScWrDelay.Bits.Dec_tCWL = 0;
          if (WrLvlChCycle[Controller][Channel] <= (2 * MAX_ADD_DELAY + 2 * MAX_DEC_DELAY + 1)) {
            CurrentOffset = WrLvlChCycle[Controller][Channel] - 2 * MAX_DEC_DELAY - 1;
            AddOneQclk[Controller][Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;
            ScWrDelay.Bits.Add_tCWL = (CurrentOffset + 1) / 2;
          } else {
            ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
          }
        }
      } else {
        AddOneQclk[Controller][Channel] = 0;
        WrLvlChCycle[Controller][Channel] = MIN (WrLvlChMinReserved / 128, (MAX_ADD_DELAY + MAX_DEC_DELAY));
        // Protect against underflow - i.e exceeding MaxDec
        WrLvlChCycle[Controller][Channel] = MAX (MAX_DEC_DELAY - (INT32) MaxDec, WrLvlChCycle[Controller][Channel]);
        if (WrLvlChCycle[Controller][Channel] <= MAX_DEC_DELAY) {
          ScWrDelay.Bits.Dec_tCWL = MAX_DEC_DELAY - WrLvlChCycle[Controller][Channel];
          // Keeping ScWrDelay.Bits.Add_tCWL = 0;
        } else {
          // Keeping ScWrDelay.Bits.Dec_tCWL = 0;
          if (WrLvlChCycle[Controller][Channel] <= (MAX_ADD_DELAY + MAX_DEC_DELAY)) {
            ScWrDelay.Bits.Add_tCWL = WrLvlChCycle[Controller][Channel] - MAX_DEC_DELAY;
          } else {
            ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
          }
        }
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WR_DELAY_REG, MC1_CH0_CR_SC_WR_DELAY_REG, Controller, MC0_CH1_CR_SC_WR_DELAY_REG, IpChannel);
      MrcWriteCR (MrcData, Offset, ScWrDelay.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d: Ch%d: Add_tCWL = %d Dec_tCWL = %d Add_1Qclk = %d\n", Controller, Channel, ScWrDelay.Bits.Add_tCWL, ScWrDelay.Bits.Dec_tCWL, AddOneQclk);
    } // for Channel
  } //Controller

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if (!(RankMask & ValidRankMask)) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        IpChannel = LP_IP_CH (Lpddr, Channel);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WR_DELAY_REG, MC1_CH0_CR_SC_WR_DELAY_REG, Controller, MC0_CH1_CR_SC_WR_DELAY_REG, IpChannel);
        ScWrDelay.Data = MrcReadCR (MrcData, Offset);
        DeltaPi = (WrLvlRankMin[Controller][Channel][Rank] - WrLvlChCycle[Controller][Channel] * 128);
        WrLvlRankCycle[Controller][Channel][Rank] = RANGE ((DeltaPi - DqPiReserve) / 128, 0, MAX_ADD_RANK_DELAY);
        FifoFlybyDelay = WrLvlRankCycle[Controller][Channel][Rank];
        //Grab the longest TxDqFifoRdEnDelay per ch across all ranks
        MaxChTxDqFifoRdEnDelay[Controller][Channel] = MAX (WrLvlRankCycle[Controller][Channel][Rank], MaxChTxDqFifoRdEnDelay[Controller][Channel]);
        GetSetVal1 = 0ULL;
        MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, TxDqFifoRdEnFlybyDelay, WriteToCache | PrintValue, &FifoFlybyDelay);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache | PrintValue, &GetSetVal1);

        if (Gear2) {
          TxDqFifoWrEn = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) + (2 * ScWrDelay.Bits.Add_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
        } else {
          TxDqFifoWrEn = tCWL - ScWrDelay.Bits.Dec_tCWL + ScWrDelay.Bits.Add_tCWL - 2; // TxDqFifoWrEnTcwlDelay(DClk)
        }
        TxDqFifoRdEn = TxDqFifoWrEn + TxFifoSeparation + AddOneQclk[Controller][Channel]; // TxDqFifoRdEnTcwlDelay(DCLK)
        if (TxDqFifoRdEn < 0) {
          TxDqFifoRdEn = 0;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s Not enough Tx FIFO separation! TxDqFifoWrEn: %d, TxFifoSeparation: %d\n", gErrString, (UINT32) TxDqFifoWrEn, TxFifoSeparation);
        }
        MrcGetSetChStrb (MrcData, Controller, Channel, 0, TxDqFifoWrEnTcwlDelay, WriteToCache | PrintValue, &TxDqFifoWrEn);
        MrcGetSetChStrb (MrcData, Controller, Channel, 0, TxDqFifoRdEnTcwlDelay, WriteToCache | PrintValue, &TxDqFifoRdEn);

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d.C%d.R%d:\tChCyc\tRankCyc\tDqsPi\tDqPi\n", Controller,Channel, Rank);
        // Program the final settings to the DQ bytes and update MrcData
        for (Byte = 0; Byte < SdramCount; Byte++) {
          GetSetVal = WrLvlTotPiDly[Controller][Channel][Rank][Byte] - WrLvlChCycle[Controller][Channel] * 128 - WrLvlRankCycle[Controller][Channel][Rank] * 128;
          Status = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal); // Write same value as DQS; DQ will be adjusted below.
          Status2 = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
          if ((Status == mrcParamSaturation) || (Status2 == mrcParamSaturation)) {
            Saturated = TRUE;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\t%d", Byte, WrLvlChCycle[Controller][Channel], WrLvlRankCycle[Controller][Channel][Rank], (UINT32) GetSetVal);
          if (Lpddr4) {
            ChangeMargin (MrcData, Param, ByteDqOffsetPi[Controller][Channel][Rank][Byte], 0, 0, Controller, Channel, Rank, Byte, 0, 1, 0);
          } else {
            GetSetVal = TxDqDqsDelayAdj;
            Status = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, WriteOffsetToCache, &GetSetVal);
            if (Status == mrcParamSaturation) {
              Saturated = TRUE;
            }
          }
#ifdef MRC_DEBUG_PRINT
          MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
#endif // MRC_DEBUG_PRINT
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d\n", (UINT32) GetSetVal);
        } // Byte
      } // for Channel
    } // Controller
  } // for Rank
  MrcFlushRegisterCachedData (MrcData);

  if (Saturated) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s, Parameter saturation!\n", gErrString);
    return mrcParamSaturation;
  }

  if (!Lpddr4) {
    // Clean up after Test
    ChangeMargin (MrcData, Param, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);  // Clean TxDq offset
  }
  Status = IoReset (MrcData);
  return Status;
}

/**
  this function execute the Jedec write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succedes return mrcSuccess
**/
MrcStatus
MrcJedecWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcDdrType        DdrType;
  MrcStatus         Status;
  INT64             GetSetVal;
  INT64             WriteLevelDis;
  INT64             WriteLevelEn;
  INT64             WlLongDelay;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             TxDqDqsDelayAdj;
  INT64             DataTrainFeedbackField;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankHalf;
  UINT8             RankMod2;
  UINT8             Byte;
  UINT8             refbyte;
  UINT8             RankMask;  // RankBitMask for both channels
  UINT8             ValidRankMask;
  UINT8             BiasPMCtrl;
  UINT8             EnDqsOdtParkMode;
  UINT16            *MrReg;
  UINT16            WLStart;
  UINT16            WLStop;
  UINT16            WLDelay;
  UINT8             WLStep;
  UINT32            WaitTime;
  UINT32            CRValue;
  UINT32            DqsToggleTime;
  UINT32            DataTrainFeedback;
  INT32             InitialPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             InitialPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            FinalDqs[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             iWidth;
  INT32             cWidth;
  INT32             lWidth;
  INT32             ByteWidth;
  BOOLEAN           Pass;
  BOOLEAN           RankIsx16;
  BOOLEAN           SavedRestoreMRS;
  BOOLEAN           Lpddr4;
  BOOLEAN           Ddr4;
  BOOLEAN           Ddr5;
  BOOLEAN           Gear2;
  UINT16            RttParkSetVal;
  TOdtValueDdr4     *Ddr4OdtTableIndex;
  DDR4_MODE_REGISTER_1_STRUCT             Ddr4ModeRegister1;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  CRValue       = 0;
  ValidRankMask = Outputs->ValidRankMask;
  GetSetEn      = 1;
  GetSetDis     = 0;
  WlLongDelay   = 1;
  BiasPMCtrl    = 0xFF;
  EnDqsOdtParkMode = 0xFF;
  Gear2 = Outputs->Gear2;

  DdrType = Outputs->DdrType;
  Lpddr4 = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Ddr5  = (Outputs->DdrType == MRC_DDR_TYPE_DDR5);

  // Save the flag and force MRS recalculation
  SavedRestoreMRS = Outputs->RestoreMRs;
  Outputs->RestoreMRs = FALSE;

  WriteLevelEn  = Ddr5 ? MrcWriteLevelDdr5 : MrcWriteLevelDdr4Lpddr4;
  WriteLevelDis = MrcWriteLevelOff;

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWlLongDelEn, WriteToCache, &WlLongDelay);
  MrcGetSetNoScope (MrcData, GsmIocDisDataIdlClkGate, WriteToCache, &GetSetEn);

  for (Controller = 0; (Controller < MAX_CONTROLLER) && (BiasPMCtrl == 0xFF) && (EnDqsOdtParkMode == 0xFF); Controller++) {
    for (Channel = 0; (Channel < Outputs->MaxChannels) && (BiasPMCtrl == 0xFF) && (EnDqsOdtParkMode == 0xFF); Channel++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocBiasPMCtrl, ReadFromCache, &GetSetVal);
          BiasPMCtrl = (UINT8) GetSetVal;
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataDqsOdtParkMode, ReadFromCache, &GetSetVal);
          EnDqsOdtParkMode  =  (UINT8) GetSetVal;
          break;
        }
      }
    }
  }
  DqsToggleTime = (WlLongDelay || Gear2) ? 4096 : 2048;

  // 0.5UI for Gear 1, 1.5UI for Gear 2
  TxDqDqsDelayAdj = Gear2 ? 96 : 32;

  WaitTime = Outputs->UIps * DqsToggleTime;


  // DDR4: Set Qoff bit in MR1 on all ranks
  if (Ddr4) {
    MrcSetMR1_DDR4 (MrcData, 1, INIT_DIMM_RON_34, 0, 0, 1);
  }

  // Enable Rank Mux Override
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if (!(RankMask & ValidRankMask)) {
      // Skip if all channels empty
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);
    RankHalf = Rank / MAX_RANK_IN_DIMM;
    RankMod2 = Rank % MAX_RANK_IN_DIMM;
    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteNoCache, &GetSetVal);

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          // Enable WL mode in MR2[7]
          if (Lpddr4) {
            CRValue = (ChannelOut->Dimm[dDIMM0].Rank[RankMod2].MR[mrMR2]);
            MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR2, (CRValue | MRC_BIT7), TRUE);
          } else {
            // Ddr4
            Ddr4OdtTableIndex = GetOdtTableIndex (MrcData, Controller, Channel, RankHalf);
            if (Ddr4OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
              return mrcFail;
            }
            RttParkSetVal = (Ddr4OdtTableIndex->RttWr == 0xFFFF) ? 0 : Ddr4OdtTableIndex->RttWr; // To get High-Z we must disable Rtt Park (0)
            SetDimmParamValue (MrcData, Controller, Channel, RankMask, OptDimmOdtPark, RttParkSetVal, FALSE);
            // RttWr must be disabled in Write Leveling mode
            SetDimmParamValue (MrcData, Controller, Channel, RankMask, OptDimmOdtWr, 0, FALSE);
            Ddr4ModeRegister1.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR1];
            Ddr4ModeRegister1.Bits.WriteLeveling = 1;
            Ddr4ModeRegister1.Bits.Qoff = 0;
            Status = MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR1, (UINT16) Ddr4ModeRegister1.Data);
          }
        }
      }  // for Channel
    } // Controller
    MrcFlushRegisterCachedData (MrcData);
    if (!Ddr5) {
      GetSetVal = 1;
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataDqsOdtParkMode, WriteToCache, &GetSetVal);
    }
    GetSetVal = 0;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    // ******************************************
    // STEP 1 and 2: Find middle of high region
    // ******************************************
    // We will add 64 ticks at the end, so shift the range left by 64.
    //  WLStart = 192 - 64;
    //  WLStop  = 192 - 64 + 128;
    WLStart = 192;
    WLStop = 192 + 128;
    WLStep = 2;

    MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\n\tCh0\t\t\t\t\t\t\t\t%sCh1\n",
        (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
    );
    // @todo adjust this to print out 2MC
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "WLDelay%s%s",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t0\t1\t2\t3\t4\t5\t6\t7\t8" : "\t0\t1\t2\t3\t4\t5\t6\t7",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t0\t1\t2\t3\t4\t5\t6\t7\t8" : "\t0\t1\t2\t3\t4\t5\t6\t7"
    );

    for (WLDelay = WLStart; WLDelay < WLStop; WLDelay += WLStep) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n %d:", WLDelay);

      GetSetVal = WLDelay;
      MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxDqsDelay, WriteToCache, &GetSetVal);

      // Set TxPiOn and WLMode
      MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache, &GetSetEn);
      MrcFlushRegisterCachedData (MrcData); // This needs to be here because WLmode is writenocache so it will set the WLmode before TxDqsDelay and clockPwrdn are disabled.

      MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode, WriteNoCache, &WriteLevelEn);
      if (WlLongDelay || Gear2) {
        MrcWait (MrcData, (WaitTime * MRC_TIMER_1NS) / 1000);
      }
      Status = IoReset (MrcData);
      MrcWait (MrcData, (WaitTime * MRC_TIMER_1NS) / 1000);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        // Update results for all Channels/Bytes
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "\t\t\t\t\t\t\t\t%s",
              (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
            );
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
              continue;
            }

            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            DataTrainFeedback = (UINT32) DataTrainFeedbackField;
            Pass = (DataTrainFeedback >= 16);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%d", Pass ? '.' : '#', DataTrainFeedback);
            if (WLDelay == WLStart) {
              if (Pass) {
                InitialPassingStart[Controller][Channel][Byte] = InitialPassingEnd[Controller][Channel][Byte] = WLStart;
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = WLStart;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = WLStart;
              } else {
                InitialPassingStart[Controller][Channel][Byte] = InitialPassingEnd[Controller][Channel][Byte] = -WLStep;
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = -WLStep;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = -WLStep;
              }
            } else {
              if (Pass) {
                if (InitialPassingEnd[Controller][Channel][Byte] == (WLDelay - WLStep)) {
                  InitialPassingEnd[Controller][Channel][Byte] = WLDelay;
                }

                if (CurrentPassingEnd[Controller][Channel][Byte] == (WLDelay - WLStep)) {
                  CurrentPassingEnd[Controller][Channel][Byte] = WLDelay;
                } else {
                  CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = WLDelay;
                }
                // Special case for last step: Append Initial Passing Region
                // WLDelay should be considered a continuous range that wraps around 0
                if ((WLDelay >= (WLStop - WLStep)) && (InitialPassingStart[Controller][Channel][Byte] == WLStart)) {
                  iWidth = (InitialPassingEnd[Controller][Channel][Byte] - InitialPassingStart[Controller][Channel][Byte]);
                  CurrentPassingEnd[Controller][Channel][Byte] += (WLStep + iWidth);
                }
                // Update Largest variables
                cWidth = CurrentPassingEnd[Controller][Channel][Byte] - CurrentPassingStart[Controller][Channel][Byte];
                lWidth = LargestPassingEnd[Controller][Channel][Byte] - LargestPassingStart[Controller][Channel][Byte];
                if (cWidth > lWidth) {
                  LargestPassingStart[Controller][Channel][Byte] = CurrentPassingStart[Controller][Channel][Byte];
                  LargestPassingEnd[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte];
                }
              }
            }
          } // for Byte
        } // for Channel
      } // Controller
    } // for WLDelay

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tInitPassSt\tInitPassEn\tCurrPassSt\tCurrPassEn\tLargPassSt\tLargPassEn\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d\n", Controller);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d\n", Channel);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "   B%d:\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                Byte,
                InitialPassingStart[Controller][Channel][Byte],
                InitialPassingEnd[Controller][Channel][Byte],
                CurrentPassingStart[Controller][Channel][Byte],
                CurrentPassingEnd[Controller][Channel][Byte],
                LargestPassingStart[Controller][Channel][Byte],
                LargestPassingEnd[Controller][Channel][Byte]
              );
            }
          }
        }
      } // Channel
    } //Controller
#endif // MRC_DEBUG_PRINT

    // Clean up after step
    // Program values for TxDQS
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

          // Check if rank is a x16.  Don't apply to LPDDR parts.
          RankIsx16 = (((ChannelOut->Dimm[RankHalf].SdramWidth == 16) && Ddr4) ? TRUE : FALSE);

          // Clear ODT before MRS (JEDEC Spec)
          GetSetVal = 0;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccOdtOverride, WriteToCache | PrintValue, &GetSetVal);
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccOdtOn, WriteToCache | PrintValue, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);

          // Restore MR2 values
          if (Lpddr4) {
            CRValue = (ChannelOut->Dimm[dDIMM0].Rank[RankMod2].MR[mrMR2]);
            MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR2, CRValue, TRUE);
            //@todo - LP Channels
            //if (Outputs->EnhancedChannelMode && (ChannelOut->ValidSubChBitMask == 3)) { // Second subch is populated
            //  MrcIssueMrw (MrcData, Controller, Channel, Rank + 2, mrMR2, CRValue, FALSE, TRUE);
            //}
          }
          if (Ddr4) {
            MrReg = &ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0];
            // Restore Write Leveling mode and Rtt_Nom for this rank, set Qoff.
            Ddr4ModeRegister1.Data = MrReg[mrMR1];
            Ddr4ModeRegister1.Bits.Qoff = 1;
            MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR1, Ddr4ModeRegister1.Data);

            // Restore RttWr and RttPark for this rank
            MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR2, MrReg[mrMR2]);
            MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR5, MrReg[mrMR5]);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d.C%d.R%d:\tLftEdge Width\n", Controller, Channel, Rank);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            ByteWidth = LargestPassingEnd[Controller][Channel][Byte] - LargestPassingStart[Controller][Channel][Byte];
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  B%d:\t%d\t%d\n",
              Byte,
              LargestPassingStart[Controller][Channel][Byte],
              ByteWidth
            );

              // Check if width is valid
              if ((ByteWidth <= 32) || (ByteWidth >= 96)) {
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_ERROR,
                  "\nERROR! Width region outside expected limits for Mc: %u Channel: %u Rank %u Byte: %u\n",
                  Controller,
                  Channel,
                  Rank,
                  Byte
                );
                if (Inputs->ExitOnFailure) {
                  return mrcWriteLevelingError;
                }
              }
            // Align byte pairs if DIMM is x16
            if (Ddr4 && (RankIsx16 && (Byte & MRC_BIT0))) {
              // If odd byte number (1, 3, 5 or 7)
              refbyte = Byte - 1;
              if (LargestPassingStart[Controller][Channel][Byte] > (LargestPassingStart[Controller][Channel][refbyte] + 64)) {
                LargestPassingStart[Controller][Channel][Byte] -= 128;
              }
              if (LargestPassingStart[Controller][Channel][Byte] < (LargestPassingStart[Controller][Channel][refbyte] - 64)) {
                LargestPassingStart[Controller][Channel][Byte] += 128;
              }
            }

            // Add 1 QCLK to DqsPi
            // if (!Gear2) {
            //   LargestPassingStart[Channel][Byte] += 64;
            // }


            // GetSetVal = LargestPassingStart[Channel][Byte];
            // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
            // GetSetVal += 32;
            // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal);
            // Save the results from the current rank into a global array
                FinalDqs[Controller][Channel][Rank][Byte] = (UINT32) LargestPassingStart[Controller][Channel][Byte];
          } // for Byte
          MrcFlushRegisterCachedData (MrcData);
#ifdef MRC_DEBUG_PRINT
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u.R%u:\tDqsPi\tDqPi\n",Controller, Channel, Rank);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
                // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
                // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal2);
                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  "  B%d:\t%u\t%u\n",
                  Byte,
                  (UINT32) FinalDqs[Controller][Channel][Rank][Byte],     // GetSetVal,
                  (UINT32) FinalDqs[Controller][Channel][Rank][Byte] + (UINT32) TxDqDqsDelayAdj // GetSetVal2
                );
              }
            }
#endif
        } // rank exist
      } // for Channel
    } //Controller

    if (Gear2) {
      MrcWait (MrcData, (WaitTime * MRC_TIMER_1NS) / 1000);
    }

    // Restore EnDQSOdtParkMode
    GetSetVal = EnDqsOdtParkMode;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataDqsOdtParkMode, WriteToCache, &GetSetVal);

    // Exit Write Leveling Mode and Re-enable TxPi Power Down.
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache, &GetSetDis);
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode, WriteNoCache, &WriteLevelDis);
    MrcFlushRegisterCachedData (MrcData);

    Status = IoReset (MrcData);
  } // for Rank

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if (!(RankMask & ValidRankMask)) {
      continue;
    }
    for (Controller = 0 ; Controller < MAX_CONTROLLER ; Controller++) {
      if (!MrcControllerExist (MrcData, Controller)) {
         continue;
      }
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
            GetSetVal = (INT64) FinalDqs[Controller][Channel][Rank][Byte];
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
            GetSetVal += TxDqDqsDelayAdj;
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal);
          }
        }
      } // Channel
    } // Controller
  } // for Rank
  MrcFlushRegisterCachedData (MrcData);

  // Clean up after Test
  // Restore DqControl2 values.
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWlLongDelEn, WriteToCache, &GetSetDis);

  // Restore BiasPMCtrl
  GetSetVal = BiasPMCtrl;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);

  // Restore EnDQSOdtParkMode
  GetSetVal = EnDqsOdtParkMode;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataDqsOdtParkMode, WriteToCache, &GetSetVal);

  // Restore cached value
  MrcGetSetNoScope (MrcData, GsmIocDisDataIdlClkGate, WriteToCache, &GetSetDis);
  MrcFlushRegisterCachedData (MrcData);

  if (Ddr4) {
    // Disable Qoff on all ranks
    // DLLEnable=1, Dic=0, Al=0, Level=0, Tdqs=0, Qoff=0
    MrcSetMR1_DDR4 (MrcData, 1, INIT_DIMM_RON_34, 0, 0, 0);
  }

  // Disable Rank Mux Override
  MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetDis);

  // Restore flag
  Outputs->RestoreMRs = SavedRestoreMRS;

  return Status;
}

/**
  This function is a wrapper for WriteLevelingFlyBy executed from the CallTable.
  This allows us to apply workarounds and multi-D implementations of WriteLevelingFlyby.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteLevelingFlyByTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcStatus Status;
  INT64     RdRdsg;
  INT64     RdRddg;

  MrcRelaxReadToReadSameRank (MrcData, TRUE, &RdRdsg, &RdRddg);
  Status = WriteLevelingFlyBy (MrcData);
  MrcRelaxReadToReadSameRank (MrcData, FALSE, &RdRdsg, &RdRddg);

  return Status;
}

/**
  this function execute the Jedec WCK training.
  Center WCK2CK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succedes return mrcSuccess
**/
MrcStatus
MrcJedecWCKTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  const MRC_FUNCTION  *MrcCall;
  MrcStatus         Status;
  INT64             GetSetVal;
  INT64             WriteLevelEn;
  INT64             WriteLevelDis;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             DataTrainFeedbackField;
//  UINT64            Timeout;
  UINT32            Controller;
  UINT32            Channel;
  UINT32            Rank;
  UINT32            OrigWckControl;
  UINT32            OrigCccPiDivider;
  UINT32            OrigMiscControl7;
  UINT32            WckPulseWait;
  UINT16            Qclkps;
  UINT8             MaxChannel;
  UINT8             Byte;
  UINT8             RankMask;  // RankBitMask for all controllers/channels
  UINT8             ValidRankMask;
  UINT16            WckStart;
  UINT16            WckStop;
  UINT16            WckPi;
  UINT16            MaxWckValue;
  UINT8             WckStep;
  UINT8             Mr18ArrayIndex;
  UINT32            WckTemp32;
  UINT32            CRValue;
  UINT32            DataTrainFeedback;
  UINT8             WckStatus[MAX_CONTROLLER][MAX_CHANNEL][CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_MAX]; //BitMask of passing Bit0 - Rank0/Byte0, Bit1 - Rank0/Byte1, Bit2 - Rank1/Byte0...
  UINT8             WckStatusPassMask[MAX_CONTROLLER][MAX_CHANNEL]; //BitMask = Bit0 - Rank0/Byte0, Bit1 - Rank0/Byte1, Bit2 - Rank1/Byte0...
  UINT8             PassMask;
  INT32             InitialPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             InitialPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             *InitialPassingStartPtr;
  INT32             *InitialPassingEndPtr;
  INT32             *CurrentPassingStartPtr;
  INT32             *CurrentPassingEndPtr;
  INT32             *LargestPassingStartPtr;
  INT32             *LargestPassingEndPtr;
  UINT32            FinalWckPi[MAX_CONTROLLER][MAX_CHANNEL];
  INT32             iWidth;
  INT32             cWidth;
  INT32             lWidth;
  INT32             ChannelWidth;
  BOOLEAN           Pass;
  BOOLEAN           SavedRestoreMRS;
  char              *BytesHeader;
  MCMISCS_DDRWCKCONTROL_STRUCT  WckControl;
  MCMISCS_DDRWCKCONTROL_STRUCT  WckControlPreIoReset;
  CH0CCC_CR_DDRCRCCCPIDIVIDER_STRUCT  CccPiDivider;
  DDRSCRAM_CR_DDRMISCCONTROL7_STRUCT  MiscControl7;

  Outputs       = &MrcData->Outputs;
  if (Outputs->DdrType != MRC_DDR_TYPE_LPDDR5) {
    return mrcSuccess;
  }

  Inputs        = &MrcData->Inputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  Status        = mrcSuccess;
  CRValue       = 0;
  ValidRankMask = Outputs->ValidRankMask;
  GetSetEn      = 1;
  GetSetDis     = 0;
  WriteLevelEn  = MrcWriteLevelLpddr5;
  WriteLevelDis = MrcWriteLevelOff;
  MaxChannel    = Outputs->MaxChannels;
  Qclkps        = Outputs->Qclkps;
  WckTemp32     = 0;
  WckStart      = 0;

  SavedRestoreMRS = Outputs->RestoreMRs;
  Outputs->RestoreMRs = FALSE;
  MrcCall->MrcSetMem ((UINT8 *) WckStatus, sizeof (WckStatus), 0);
  MrcCall->MrcSetMem ((UINT8 *) WckStatusPassMask, sizeof (WckStatusPassMask), 0);

  MrcGetSetLimits (MrcData, WckGrpPi, NULL, &GetSetVal, NULL);
  MaxWckValue = (UINT16) GetSetVal + 1;

  Mr18ArrayIndex = mrMR18;
  Mr18ArrayIndex = MrcMrAddrToIndex (MrcData, &Mr18ArrayIndex);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Disable WCK Termination to all detected Ranks\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          CRValue = (ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[Mr18ArrayIndex]);
          if ((CRValue & 0x7) != 0) {
            //Disable WCK Termination for all detected Ranks
            MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR18, (CRValue & ~0x7), TRUE);
          }
          // Setup PassMask for later comparison
          WckStatusPassMask[Controller][Channel] |= (0x3 << (Rank * 2));//Tie 2 to MaxByteInLpChannel?
        }
      }
    }  // for Channel
  } // Controller
  MrcBlockTrainResetToggle (MrcData, FALSE);

  //Sweep +/-0.25 CK

  WckStart = 0;

  WckStop  = MaxWckValue;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WCK Start = 0x%x, WCK Stop = 0x%x\n", WckStart, WckStop);

  MrcGetSetNoScope (MrcData, GsmIocLp5Wck2CkRatio, ReadFromCache | PrintValue, &GetSetVal);
  WckTemp32 = (GetSetVal == 0) ? 1 : 2;

  MiscControl7.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG);
  OrigMiscControl7 = MiscControl7.Data;
  MiscControl7.Bits.TrainWCkEn = 1;
  MiscControl7.Bits.TrainWCkSyncRatio = WckTemp32;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, MiscControl7.Data);

  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableDclk, WriteNoCache, &GetSetDis);
  MrcWait (MrcData, 27 * MRC_TIMER_1NS);
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableDclk, WriteNoCache, &GetSetEn);

  WckControl.Data = MrcReadCR (MrcData, MCMISCS_DDRWCKCONTROL_REG);
  OrigWckControl = WckControl.Data;
  WckControl.Bits.TrainWCkBL = 12;
  WckControl.Bits.TrainWCkMask = 4;
  WckControlPreIoReset.Data = WckControl.Data;
  WckControl.Bits.WCkDiffLowInIdle = 1;

  CccPiDivider.Data = MrcReadCR (MrcData, CH0CCC_CR_DDRCRCCCPIDIVIDER_REG);
  OrigCccPiDivider = CccPiDivider.Data;
  WckTemp32 = CccPiDivider.Bits.Pi4Inc;
  WckTemp32 = WckTemp32 ? WckTemp32 - 1 : 0;
  CccPiDivider.Bits.Pi4DivEn  = 1;
  CccPiDivider.Bits.Pi4Inc    = WckTemp32;

  WckStep = 2;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if (!(RankMask & ValidRankMask)) {
      // Skip if all channels empty
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);

    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode, WriteNoCache, &WriteLevelEn);

    MrcWriteCR (MrcData, CCC_CR_DDRCRCCCPIDIVIDER_REG, CccPiDivider.Data);

    WckPulseWait = (Qclkps * (1 << WckControl.Bits.TrainWCkBL)) + (5 * Qclkps);
    WckPulseWait = DIVIDECEIL (WckPulseWait, 1000);
    // ******************************************
    // Find the rising edge of the high phase.
    // ******************************************
    MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "\n\tMc0Ch0\t\tMc0Ch1\t\tMc0Ch2\t\tMc0Ch3\t\tMc1Ch0\t\tMc1Ch1\t\tMc1Ch2\t\tMc1Ch3\n"
        );
    BytesHeader = "\t0\t1";
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WckPi%s%s", BytesHeader, BytesHeader);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", BytesHeader, BytesHeader);

    for (WckPi = WckStart; WckPi < WckStop; WckPi += WckStep) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n %d:", WckPi);

      GetSetVal = WckPi;
      MrcGetSetCcc (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MRC_IGNORE_ARG, 0, WckGrpPi, WriteCached, &GetSetVal);

      Status = IoReset (MrcData);

      MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
            ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
            // Enable WL mode in MR18[6] and set CKR (WCK to CK freq ratio) to 2:1 MR18[7], MR18[5] needs to match MR18[7]
            CRValue = (ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[Mr18ArrayIndex]);
            MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR18, (CRValue | 0xE0), TRUE); //@todo make this an memory api usage
          }
        }  // for Channel
      } // Controller

      // Probably do not need to specifically wait tWLMRD which is MAX (14ns, 5tCK)
      MrcWait (MrcData, 27 * MRC_TIMER_1NS);
      WckControl.Bits.TrainWCkPulse = 1;
      MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);

//      Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
//      do {
//        WckControl.Data = MrcReadCR (MrcData, MCMISCS_DDRWCKCONTROL_REG);
//      } while (WckControl.Bits.TrainWCkPulse && (MrcCall->MrcGetCpuTime () < Timeout));
//      MrcWait (MrcData, 27 * MRC_TIMER_1NS);
      MrcWait (MrcData, WckPulseWait * MRC_TIMER_1NS);

      WckControl.Bits.TrainWCkPulse = 0;
      MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);

      // Update results for all Controllers/Channels/Bytes
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t");
            continue;
          }
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            DataTrainFeedback = (UINT32) DataTrainFeedbackField;
            Pass = (DataTrainFeedback >= 16);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%d", Pass ? '.' : '#', DataTrainFeedback);
            WckStatus[Controller][Channel][WckPi] |= Pass ? (1 << ((Rank * 2) + Byte)) : 0;
          }
          // Disable WL mode in MR18[6]
          CRValue = (ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[Mr18ArrayIndex]);
          MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR18, CRValue, TRUE);
        } // for Channel
      } // Controller
      MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControlPreIoReset.Data);
    } // for WckPi

    // Clean up after step
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

          // Restore MR18 values
          CRValue = (ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[Mr18ArrayIndex]);
          //Disable WCK Termination for current rank to allow subsequent rank
          MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR18, (CRValue & ~0x7), TRUE);
        } // rank exist
      } // for Channel
    } //Controller

    // Exit Write Leveling Mode and Re-enable TxPi Power Down.
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache, &GetSetDis);
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode, WriteNoCache, &WriteLevelDis);
    MrcFlushRegisterCachedData (MrcData);

    Status = IoReset (MrcData);
  } // for Rank

  //Aggregate the results within each Channel (Specific to TGL design)
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      PassMask = WckStatusPassMask[Controller][Channel];
      InitialPassingStartPtr = &InitialPassingStart[Controller][Channel];
      InitialPassingEndPtr = &InitialPassingEnd[Controller][Channel];
      CurrentPassingStartPtr = &CurrentPassingStart[Controller][Channel];
      CurrentPassingEndPtr = &CurrentPassingEnd[Controller][Channel];
      LargestPassingStartPtr = &LargestPassingStart[Controller][Channel];
      LargestPassingEndPtr = &LargestPassingEnd[Controller][Channel];

      for (WckPi = WckStart; WckPi < WckStop; WckPi += WckStep) {
        Pass = ((WckStatus[Controller][Channel][WckPi] & PassMask) == PassMask);
        if (WckPi == WckStart) {
          if (Pass) {
            *InitialPassingStartPtr = *InitialPassingEndPtr = WckStart;
            *CurrentPassingStartPtr = *CurrentPassingEndPtr = WckStart;
            *LargestPassingStartPtr = *LargestPassingEndPtr = WckStart;
          } else {
            *InitialPassingStartPtr = *InitialPassingEndPtr = -WckStep;
            *CurrentPassingStartPtr = *CurrentPassingEndPtr = -WckStep;
            *LargestPassingStartPtr = *LargestPassingEndPtr = -WckStep;
          }
        } else {
          if (Pass) {
            if (*InitialPassingEndPtr == (WckPi - WckStep)) {
              *InitialPassingEndPtr = WckPi;
            }

            if (*CurrentPassingEndPtr == (WckPi - WckStep)) {
              *CurrentPassingEndPtr = WckPi;
            } else {
              *CurrentPassingStartPtr = *CurrentPassingEndPtr = WckPi;
            }
            // Special case for last step: Append Initial Passing Region
            // WckPi should be considered a continuous range that wraps around 0
            if ((WckPi >= (WckStop - WckStep)) && (*InitialPassingStartPtr == WckStart) && (WckStart == 0) && (WckStop == MaxWckValue)) {
              iWidth = (*InitialPassingEndPtr - *InitialPassingStartPtr);
              *CurrentPassingEndPtr += (WckStep + iWidth);
            }
            // Update Largest variables
            cWidth = *CurrentPassingEndPtr - *CurrentPassingStartPtr;
            lWidth = *LargestPassingEndPtr - *LargestPassingStartPtr;
            if (cWidth > lWidth) {
              *LargestPassingStartPtr = *CurrentPassingStartPtr;
              *LargestPassingEndPtr = *CurrentPassingEndPtr;
            }
          }
        }
      } // for WckPi
    } // for Channel
  } // for Controller

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t\tInitPassSt\tInitPassEn\tCurrPassSt\tCurrPassEn\tLargPassSt\tLargPassEn\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          " Mc%d.C%d:\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
          Controller,
          Channel,
          InitialPassingStart[Controller][Channel],
          InitialPassingEnd[Controller][Channel],
          CurrentPassingStart[Controller][Channel],
          CurrentPassingEnd[Controller][Channel],
          LargestPassingStart[Controller][Channel],
          LargestPassingEnd[Controller][Channel]
        );
      }
    } // Channel
  } //Controller
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tLftEdge Width\n");
#endif // MRC_DEBUG_PRINT

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelWidth = LargestPassingEnd[Controller][Channel] - LargestPassingStart[Controller][Channel];
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        " Mc%d.C%d:\t%d\t%d\n",
        Controller,
        Channel,
        LargestPassingStart[Controller][Channel],
        ChannelWidth
        );
      FinalWckPi[Controller][Channel] = (UINT32) (LargestPassingStart[Controller][Channel]) % MaxWckValue;
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tWckPi\n");
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        " Mc%u.C%u:\t%u\n",
        Controller,
        Channel,
        (UINT32) FinalWckPi[Controller][Channel]
        );
#endif
    } // for Channel
  } //Controller

  for (Controller = 0 ; Controller < MAX_CONTROLLER ; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      GetSetVal = (INT64) FinalWckPi[Controller][Channel];
      MrcGetSetCcc (MrcData, Controller, Channel, MRC_IGNORE_ARG, 0, WckGrpPi, WriteToCache | PrintValue, &GetSetVal);
    } // Channel
  } // Controller
  MrcFlushRegisterCachedData (MrcData);
  Status = IoReset (MrcData);

  MrcBlockTrainResetToggle (MrcData, TRUE);

  // Clean up after Test
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          // Restore MR18
          CRValue = (ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[Mr18ArrayIndex]);
          MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR18, CRValue, TRUE);
        }
      }
    }  // for Channel
  } // Controller

  // Restore cached value
  MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, OrigWckControl);
  MrcWriteCR (MrcData, CCC_CR_DDRCRCCCPIDIVIDER_REG, OrigCccPiDivider);
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, OrigMiscControl7);

  // Restore flag
  Outputs->RestoreMRs = SavedRestoreMRS;

  return Status;
}
