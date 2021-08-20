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
#include "MrcDdrCommon.h"
#include "MrcCpgcApi.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcMaintenance.h"

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
  MrcIntOutput        *MrcIntData;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MrcStatus           Status2;
  UINT64              ErrStatus;
  INT64               GetSetVal;
  INT64               GetSetVal1;
  INT64               GetSetEn;
  INT64               FifoFlybyDelay;
  INT64               TxDqDqsDelayAdj;
  INT64               TxDqFifoWrEn;
  INT64               TxDqFifoRdEn;
  INT32               TxFifoSeparation;
  UINT32              tCWL;
  UINT32              WrLvlTotPiDly[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              WrLvlRankMin[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32              WrLvlRankMax[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  UINT32              WrLvlChMin[MAX_CHANNEL];
  UINT32              WrLvlChMax[MAX_CHANNEL];
  UINT32              Offset;
  UINT32              Tdqs2dqMinFs;
  UINT32              Tdqs2dqMaxFs;
  UINT32              Tdqs2dqCenterFs;
  UINT32              AddOneQclk[MAX_CHANNEL];
  UINT32              MaxDec;
  UINT32              MaxAdd;
  UINT32              UiLoop;
  INT32               WrLvlChMinReserved;
  INT32               DqSweepStart;
  INT32               DqSweepStop;
  INT32               DqOffset;
  INT32               WrLvlChCycle[MAX_CHANNEL];
  INT32               WrLvlRankCycle[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32               MaxChTxDqFifoRdEnDelay[MAX_CHANNEL];
  INT32               DeltaPi;
  INT32               CycleDelay[MAX_CHANNEL];
  INT32               GlobalByteOff;
  INT32               StartOffset;
  INT32               EndOffset;
  INT32               CurrentOffset;
  UINT16              BytePass[MAX_CHANNEL]; // Bit mask indicating which ch/byte has passed
  UINT16              SavedTxDqsVal[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]; // Saved TxDqs value
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
  UINT16              NumIters; //Static Pattern # of Iterations per CL
  INT16               ByteDqOffsetStart[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               ByteDqOffsetEnd[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               ByteDqOffset;
  UINT8               Param;
  UINT8               Channel;
  UINT8               SubCh;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               ChBitMask;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               ValidRankMask;
  UINT8               RankHalf;
  UINT8               RankMod2;
  UINT8               PiCycleDec;
  UINT8               PiCycleAdd;
  UINT8               LoopCount;
  UINT8               SdramCount;
  INT8                DqSweepStep;
  BOOLEAN             Gear2;
  BOOLEAN             Done;
  BOOLEAN             Lpddr4;
  BOOLEAN             Saturated;
  CH0_CR_SC_WR_DELAY_STRUCT ScWrDelay;

  // Same pattern on all 64 DQ's
  // 4 different CL's:
  // 11111111 00000000 11110000 00001111
  UINT32        (*DataPattern)[2];
  static UINT32 Pattern[8][2] = {
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF },
    { 0x0FF000FF, 0x0FF000FF }
  };

  static UINT32 PatternLp4[8][2] = {
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 },
    { 0xA55A5AA5, 0xA55A5AA5 }
  };

#ifdef MRC_DEBUG_PRINT
  UINT8               BitGroupErr[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
#endif // MRC_DEBUG_PRINT

  Inputs                = &MrcData->Inputs;
  MrcCall               = Inputs->Call.Func;
  Outputs               = &MrcData->Outputs;
  MrcIntData            = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug                 = &Outputs->Debug;
  ControllerOut         = &Outputs->Controller[0];
  Lpddr4                = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Gear2                 = Outputs->Gear2;
  Status                = mrcSuccess;
  Done                  = TRUE;
  tCWL                  = 0;
  DqPiReserve           = 128;
  GetSetEn              = 1;
  SdramCount            = Outputs->SdramCount;
  MrcCall->MrcSetMem ((UINT8 *) CycleDelay, sizeof (CycleDelay), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlRankMax, sizeof (WrLvlRankMax), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlRankMin, sizeof (WrLvlRankMin), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChMax, sizeof (WrLvlChMax), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChMin, sizeof (WrLvlChMin), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) WrLvlChCycle, sizeof (WrLvlChCycle), 0);
  MrcCall->MrcSetMem ((UINT8 *) ByteDqOffsetStart, sizeof (ByteDqOffsetStart), 0);
  MrcCall->MrcSetMem ((UINT8 *) ByteDqOffsetEnd, sizeof (ByteDqOffsetEnd), 0);

  MrcGetSetLimits (MrcData, TxDqDelay, NULL, &GetSetVal, NULL);
  TxDqMaxVal  = (UINT16) GetSetVal;

  // 0.5UI for Gear 1, 1.5UI for Gear 2
  TxDqDqsDelayAdj = Gear2 ? 96 : 32;
  LoopCount = 10;
  NumIters  = 1;

  if (Inputs->LoopBackTest) {
    // Enable DCLK in case JEDEC Reset is skipped
    MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache, &GetSetEn);

    // Disable CKE - DRAM enters power down
    GetSetVal = 0;
    MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmIocCkeOn, WriteNoCache, &GetSetVal);

    // Set SC_GS_CFG_TRAINING.ignore_cke to send CPGC commands even if CKE is LOW.
    MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccIgnoreCke, WriteNoCache, &GetSetEn);

    MrcIntData->SkipZq = TRUE;  // We don't need ZQ in SetupIOTest()
  }

  ChBitMask     = Outputs->ValidChBitMask;
  ValidRankMask = Outputs->ValidRankMask;
  ValidByteMask = (MRC_BIT0 << SdramCount) - 1; // 0x1FF or 0xFF

  TxFifoSeparation = TX_FIFO_SEPARATION;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MaxChTxDqFifoRdEnDelay[Channel] = 0;
  }
  DataPattern = Pattern;
  if (Inputs->LoopBackTest && Lpddr4) {
    DataPattern = PatternLp4;            // Use stronger pattern for LP4 loopback test
  }
  SetupIOTestStatic (MrcData, ChBitMask, LoopCount, NSOE, 0, 0, NumIters, DataPattern);

  MaxAdd = MAX_ADD_DELAY * (Gear2 ? 2 : 1) + MAX_ADD_RANK_DELAY;
  MaxDec = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCWL, ReadFromCache | PrintValue, &GetSetVal);
    tCWL = (UINT32) GetSetVal;
    if (Lpddr4) {
      tCWL++;     // Due to tDQSS on LP3/4
    }
    MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tCWL = %d, Separation = %d\n", tCWL, TxFifoSeparation);

    // Calculate max range for Dec delay (Add is 0 in this case)
    // Make sure TxDqFifoRdEnTcwlDelayand and TxDqFifoWrEnTcwlDelay won't become negative
    if (Gear2) {
      // TxDqFifoWrEn = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
      // TxDqFifoRdEn = TxDqFifoWrEn + TxFifoSeparation + AddOneQclk
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
    if (Inputs->LoopBackTest) {
      MaxDec = Gear2 ? 4 : 6;   // We use big tCWL, so no reason to start sweep too early
    }
    MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ensuring TxFifo pointers are not negative: MaxDec = %d \n", MaxDec);

    // If DDR4 and we go to 1N in LCT so need to reduce Dec by 1
//    if (!Lpddr && (ControllerOut->Channel[Channel].Timing[Inputs->MemoryProfile].NMode == 1)) {
//      MaxDec -= (Gear2 ? 2 : 1); // @todo <ICL> Do we need this ?
//      MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MaxDec Decrement = %d \n", MaxDec);
//    }
    // tCWL and NMode is the same across channels
    break;
  }

  if (!Lpddr4) {
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn, WriteToCache, &GetSetEn);
  }

  // Determine the Dq/Dqs sweep range during the cycle search.
  if (Lpddr4) {
    Param = WrTLp4;
    MrcGetTdqs2dq (MrcData, TRUE, &Tdqs2dqMinFs);
    MrcGetTdqs2dq (MrcData, FALSE, &Tdqs2dqMaxFs);
    // @todo Check with DE - limit the tDQS2DQ range from the right for now to avoid FlyBy pass on the adjacent cycle at high speeds
    Tdqs2dqMaxFs -= 200000;
    if (Inputs->LoopBackTest && Gear2) {
      Tdqs2dqMinFs -= 100000;
    }
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
    ChBitMask   = 0;
    RankMask    = MRC_BIT0 << Rank;
    RankHalf    = Rank / 2;
    RankMod2    = Rank % 2;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      BytePass[Channel] = 0;
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
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      for (Byte = 0; Byte < SdramCount; Byte++) {
        if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
          TxDqValue = (UINT16) GetSetVal;
          MaxCode = MAX (MaxCode, TxDqValue);

          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
          TxDqsValue = (UINT16) GetSetVal;
          SavedTxDqsVal[Channel][Byte] = TxDqsValue;
          MinCode = MIN (MinCode, TxDqsValue);
        }
      }
    }
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

    MrcCall->MrcSetMem ((UINT8 *) AddOneQclk, sizeof (AddOneQclk), 0);

    for (CurrentOffset = StartOffset; CurrentOffset <= EndOffset; CurrentOffset++) {

      for (UiLoop = 0; UiLoop < 4; UiLoop++) {
        if (Inputs->LoopBackTest) {
          MrcCall->MrcSetMem ((UINT8 *) ByteDqOffsetStart, sizeof (ByteDqOffsetStart), 0);  // In loopback mode all bytes should pass on the same cycle, so ignore previous passes
          MrcCall->MrcSetMem ((UINT8 *) ByteDqOffsetEnd, sizeof (ByteDqOffsetEnd), 0);
          MrcCall->MrcSetMem ((UINT8 *) BytePass, sizeof (BytePass), 0);
        }

        // Program new delay offsets to DQ/DQS timing:
        GlobalByteOff = 0;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            continue;
          }
          GlobalByteOff = 0;
          if (Gear2) {
            AddOneQclk[Channel] = 1;
            if (CurrentOffset > (INT32) MaxAdd) {                 // Will use DQ/DQS PI to go right
              CycleDelay[Channel] = MAX_ADD_DELAY + MAX_ADD_RANK_DELAY;
              GlobalByteOff       = 128 * (CurrentOffset - MaxAdd);
            } else if (CurrentOffset < -1 - 2 * (INT32) MaxDec) {     // Will use DQ/DQS PI to go left
              CycleDelay[Channel] = -1 * MaxDec;
              GlobalByteOff       = 128 * (CurrentOffset + 2 * MaxDec);
            } else {
              if (CurrentOffset > 2 * MAX_ADD_DELAY) {            // Will use TxDqFifoRdEnFlybyDelay
                CycleDelay[Channel] = CurrentOffset - MAX_ADD_DELAY;
              } else {                                            // Will use Dec_tCWL / Add_tCWL
                AddOneQclk[Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;  // Add one QCLK in Gear2 every other cycle offset (when CurrentOffset is even)
                if (CurrentOffset > 0) {
                  CycleDelay[Channel] = (CurrentOffset + 1) / 2;
                } else {
                  CycleDelay[Channel] = CurrentOffset / 2;
                }
              }
            }
          } else {  // Gear1
            if (CurrentOffset > (INT32) MaxAdd) {
              CycleDelay[Channel] = MaxAdd;
              GlobalByteOff       = 128 * (CurrentOffset - MaxAdd);
            } else if (CurrentOffset < -1 * (INT32) MaxDec) {
              CycleDelay[Channel] = -1 * MaxDec;
              GlobalByteOff       = 128 * (CurrentOffset + MaxDec);
            } else {
              CycleDelay[Channel] = CurrentOffset;
            }
          }

          if (Inputs->LoopBackTest) {
            GlobalByteOff += (32 * UiLoop);
          }

          // Write Tx DQ/DQS Flyby delays
          // Note that we program these also in case GlobalByteOff is zero, because it might have been non-zero in the previous cycle.
          if (GlobalByteOff != 0) {
            MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nAdd GlobalByteOff = %d to TxDQS Flyby delay: Ch %d \n", GlobalByteOff, Channel);
          }
          for (Byte = 0; Byte < SdramCount; Byte++) {
            if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
              GetSetVal = SavedTxDqsVal[Channel][Byte] + GlobalByteOff;
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
              GetSetVal += TxDqDqsDelayAdj;
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal);
            }
          }
          MrcFlushRegisterCachedData (MrcData);

          // Write SC_WR_DELAY
          FifoFlybyDelay = 0;
          ScWrDelay.Data = 0;
          if (CycleDelay[Channel] < 0) {
            ScWrDelay.Bits.Dec_tCWL = ABS (CycleDelay[Channel]);
            ScWrDelay.Bits.Add_tCWL = 0;
          } else {
            if (CycleDelay[Channel] > MAX_ADD_DELAY) {
              ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
              FifoFlybyDelay = CycleDelay[Channel] - MAX_ADD_DELAY;
            } else {
              ScWrDelay.Bits.Add_tCWL = CycleDelay[Channel];
            }
            ScWrDelay.Bits.Dec_tCWL = 0;
          }
          Offset = OFFSET_CALC_CH (CH0_CR_SC_WR_DELAY_REG, CH1_CR_SC_WR_DELAY_REG, Channel);
          MrcWriteCR (MrcData, Offset, ScWrDelay.Data);  // @todo <CNL> GetSet

          GetSetVal1 = 0;
          TxDqFifoWrEn = 0;
          TxDqFifoRdEn = 0;
          for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
            // @todo <CNL> check single sub-ch case
            MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, TxDqFifoRdEnFlybyDelay,    WriteToCache, &FifoFlybyDelay);
            MrcGetSetDdrIoGroupChSch    (MrcData, Channel, SubCh, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache, &GetSetVal1);

            if (Gear2) {
              TxDqFifoWrEn  = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) + (2 * ScWrDelay.Bits.Add_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
            } else {
              TxDqFifoWrEn  = tCWL - ScWrDelay.Bits.Dec_tCWL + ScWrDelay.Bits.Add_tCWL - 2; // TxDqFifoWrEnTcwlDelay(DClk)
            }
            TxDqFifoRdEn = TxDqFifoWrEn + TxFifoSeparation + AddOneQclk[Channel]; // TxDqFifoRdEnTcwlDelay(DCLK)
            if (TxDqFifoRdEn < 0) {
              TxDqFifoRdEn = 0;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s Not enough Tx FIFO separation! TxDqFifoWrEn: %d, TxFifoSeparation: %d\n", gErrString, (UINT32) TxDqFifoWrEn, TxFifoSeparation);
            }

            MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoWrEnTcwlDelay, WriteToCache, &TxDqFifoWrEn);
            MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoRdEnTcwlDelay, WriteToCache, &TxDqFifoRdEn);
          }
          MrcFlushRegisterCachedData (MrcData);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nGlobalByteOff: %d, Dec: %d, Add: %d, 1Qclk: %d, WrEn: %d, RdEn: %d, flyby: %d\n",
            GlobalByteOff, ScWrDelay.Bits.Dec_tCWL, ScWrDelay.Bits.Add_tCWL, AddOneQclk[Channel], (UINT32) TxDqFifoWrEn, (UINT32) TxDqFifoRdEn, (UINT32) FifoFlybyDelay);
        } // for Channel
        if (!Lpddr4) {
          // Reset FIFOs & Reset DRAM DLL. Wait 1uS for test to complete
          Status = IoReset (MrcData);
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              ChannelOut = &ControllerOut->Channel[Channel];
              Status = MrcWriteMRS (
                        MrcData,
                        Channel,
                        RankMask,
                        mrMR0,
                        ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
                        );
            }
          }
          MrcWait (MrcData, 1 * MRC_TIMER_1US);
        }
        // Run Test sweeping DQ to DQS searching for a Pass.
        for (DqOffset = DqSweepStart; DqOffset <= DqSweepStop; DqOffset += DqSweepStep) {
          // Update Offset
          ChangeMargin (MrcData, Param, DqOffset, 0, 1, 0, Rank, 0, 0, 0, 0);
          // Run Test
          // DQPat = BasicVA, DumArr, ClearErrors = 1, mode = 0
          RunIOTest (MrcData, ChBitMask, StaticPattern, 1, 0);
          // Update results for all ch/bytes
          Done = TRUE;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 3d\t% 3d\t       \t", CurrentOffset, DqOffset);
//        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CycleDelay: %3d, FifoRdEnFlyby: %d, FifoRdEn: %2d, FifoWrEn: %2d, Dec: %d, Add: %d, Add1Q: %d ",
//          CycleDelay[0], (UINT32) FifoFlybyDelay, (UINT32) TxDqFifoRdEn, (UINT32) TxDqFifoWrEn, ScWrDelay.Bits.Dec_tCWL, ScWrDelay.Bits.Add_tCWL, AddOneQclk[0]);
          // Update results for all ch/bytes
#ifdef MRC_DEBUG_PRINT
          MrcCall->MrcSetMem((UINT8 *)BitGroupErr, sizeof (BitGroupErr), 0);
#endif // MRC_DEBUG_PRINT
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
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
            for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
              if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
                // Read out per byte error results and check for any byte error
                MrcGetMiscErrStatus (MrcData, Channel, SubCh, ByteGroupErrStatus, &ErrStatus);
                Result |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
#ifdef MRC_DEBUG_PRINT
                MrcGetBitGroupErrStatus (MrcData, Channel, SubCh, BitGroupErr[Channel]);
#endif // MRC_DEBUG_PRINT
              }
            } // for SubCh
            SkipMe = (Result & ValidByteMask) | BytePass[Channel];

            for (Byte = 0; Byte < SdramCount; Byte++) {
              if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
                continue;
              }
              ByteMask = 1 << Byte;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Result & ValidByteMask) & ByteMask) ? "# " : ". ");
              // If this byte has failed or previously passed, nothing to do
              if (SkipMe & ByteMask) {
                if ((Result & ByteMask) == 0) {  // Byte passed, record the current end of the passing region
                  ByteDqOffsetEnd[Channel][Rank][Byte] = (INT16) DqOffset;
                }
                continue;
              }
              // Pass case
              if ((BytePass[Channel] & ByteMask) == 0) {  // This is the first pass for this byte, record the start of the passing region
                ByteDqOffsetStart[Channel][Rank][Byte] = (INT16) DqOffset;
              }
              BytePass[Channel] |= ByteMask;
              // Adjust delay reference point to MAX_DEC_DELAY so they will be positive delays only
              if (Gear2) {
                WrLvlTotPiDly[Channel][Rank][Byte] = 128 * (CurrentOffset + 2 * MAX_DEC_DELAY + 1) + SavedTxDqsVal[Channel][Byte];
              } else {
                WrLvlTotPiDly[Channel][Rank][Byte] = 128 * (CurrentOffset + MAX_DEC_DELAY) + SavedTxDqsVal[Channel][Byte];
              }
              if (Inputs->LoopBackTest) {
                WrLvlTotPiDly[Channel][Rank][Byte] += (32 * UiLoop);
              }
              // Track max/min pi per ch and rank
              if (WrLvlChMax[Channel] < WrLvlTotPiDly[Channel][Rank][Byte]) {
                WrLvlChMax[Channel] = WrLvlTotPiDly[Channel][Rank][Byte];
              }
              if (WrLvlChMin[Channel] > WrLvlTotPiDly[Channel][Rank][Byte]) {
                WrLvlChMin[Channel] = WrLvlTotPiDly[Channel][Rank][Byte];
              }
              if (WrLvlRankMax[Channel][Rank] < WrLvlTotPiDly[Channel][Rank][Byte]) {
                WrLvlRankMax[Channel][Rank] = WrLvlTotPiDly[Channel][Rank][Byte];
              }
              if (WrLvlRankMin[Channel][Rank] > WrLvlTotPiDly[Channel][Rank][Byte]) {
                WrLvlRankMin[Channel][Rank] = WrLvlTotPiDly[Channel][Rank][Byte];
              }
              // MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrLvlTotPiDly[Channel=%d][Rank=%d][Byte=%d]=%d SavedTxDqsVal[Channel][Byte]=%d\n", Channel, Rank, Byte, WrLvlTotPiDly[Channel][Rank][Byte],SavedTxDqsVal[Channel][Byte]);
            } // for Byte
            // MRC_WRLVL_FLYBY_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WrLvlRankMin[Channel=%d][Rank=%d]=%d WrLvlChMin[Channel=%d]=%d\n", Channel, Rank, WrLvlRankMin[Channel][Rank], Channel, WrLvlChMin[Channel]);
            if (BytePass[Channel] != ValidByteMask) {
              Done = FALSE;
            }
          } // for Channel
#ifdef MRC_DEBUG_PRINT
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            ErrStatus = 0;
            for (Byte = 0; Byte < (MAX_SDRAM_IN_DIMM - 1); Byte++) {
              ErrStatus |= MrcCall->MrcLeftShift64 (BitGroupErr[Channel][Byte], Byte * 8);
            }
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              if (Outputs->EccSupport) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "0x%02X", BitGroupErr[Channel][8]);
              }
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%016llX ", Outputs->EccSupport ? "" : "0x", ErrStatus);
            }
          }
#endif  // MRC_DEBUG_PRINT
        } // for DqOffset

        // Jump out of the UI loop if everybody is passing or if it's not a loopback test
        if ((Done == TRUE) || !Inputs->LoopBackTest) {
          break;
        }
      } // for UiLoop

      // Jump out of the for offset loop if everybody is passing
      if (Done == TRUE) {
        break;
      }
    } // for offset
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
    // Walk through and find the correct value for each ch/byte
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      if (BytePass[Channel] != ChannelOut->ValidByteMask) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_ERROR,
          "Error! Write Leveling CleanUp - Couldn't find a passing value for all bytes on Channel %u Rank %u:\nBytes - ",
          Channel,
          Rank
          );
#ifdef MRC_DEBUG_PRINT
        for (Byte = 0; Byte < SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, ((BytePass[Channel] ^ ChannelOut->ValidByteMask) & (1 << Byte)) ? "%d " : "", Byte);
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
                Channel,
                RankMask,
                mrMR0,
                ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0] | (MRC_BIT0 << 8)
                );
      MrcWait (MrcData, 1 * MRC_TIMER_1US);
    }
    } // for Channel
  } // for Rank

  // Calculate Cycle and PI Delay per channel and per rank
  //  1. Program the global min cycle to each channel
  //  2. Program rank cycle delay
  //  3. Program byte PI delay + PI reserved as needed
  Saturated = FALSE;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    // Program per channel delay - Add/Dec
    WrLvlChMinReserved = MAX ((INT32) WrLvlChMin[Channel] - DqPiReserve, 0);
    ScWrDelay.Data = 0;
    if (Gear2) {
      AddOneQclk[Channel] = 1;
      WrLvlChCycle[Channel] = MIN (WrLvlChMinReserved / 128, (2 * MAX_ADD_DELAY + 2 * MAX_DEC_DELAY + 1)) ;
      if (WrLvlChCycle[Channel] <= (2 * MAX_DEC_DELAY + 1)) {
        CurrentOffset = (2 * MAX_DEC_DELAY + 1) - WrLvlChCycle[Channel];
        AddOneQclk[Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;
        ScWrDelay.Bits.Dec_tCWL = CurrentOffset / 2;
        // Keeping ScWrDelay.Bits.Add_tCWL = 0;
      } else {
        // Keeping ScWrDelay.Bits.Dec_tCWL = 0;
        if (WrLvlChCycle[Channel] <= (2 * MAX_ADD_DELAY + 2 * MAX_DEC_DELAY + 1)) {
          CurrentOffset = WrLvlChCycle[Channel] - 2 * MAX_DEC_DELAY - 1;
          AddOneQclk[Channel] = ((CurrentOffset % 2) == 0) ? 1 : 0;
          ScWrDelay.Bits.Add_tCWL = (CurrentOffset + 1) / 2;
        } else {
          ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
        }
      }
    } else {
      AddOneQclk[Channel] = 0;
      WrLvlChCycle[Channel] = MIN (WrLvlChMinReserved / 128, (MAX_ADD_DELAY + MAX_DEC_DELAY)) ;
      // Protect against underflow - i.e exceeding MaxDec
      WrLvlChCycle[Channel] = MAX (MAX_DEC_DELAY - (INT32) MaxDec, WrLvlChCycle[Channel]);
      if (WrLvlChCycle[Channel] <= MAX_DEC_DELAY) {
        ScWrDelay.Bits.Dec_tCWL = MAX_DEC_DELAY - WrLvlChCycle[Channel];
        // Keeping ScWrDelay.Bits.Add_tCWL = 0;
      } else {
        // Keeping ScWrDelay.Bits.Dec_tCWL = 0;
        if (WrLvlChCycle[Channel] <= (MAX_ADD_DELAY + MAX_DEC_DELAY)) {
          ScWrDelay.Bits.Add_tCWL = WrLvlChCycle[Channel] - MAX_DEC_DELAY;
        } else {
          ScWrDelay.Bits.Add_tCWL = MAX_ADD_DELAY;
        }
      }
    }
    Offset = OFFSET_CALC_CH (CH0_CR_SC_WR_DELAY_REG, CH1_CR_SC_WR_DELAY_REG, Channel);
    MrcWriteCR (MrcData, Offset, ScWrDelay.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d: Add_tCWL = %d Dec_tCWL = %d Add_1Qclk = %d\n", Channel, ScWrDelay.Bits.Add_tCWL, ScWrDelay.Bits.Dec_tCWL, AddOneQclk[Channel]);
  } // for Channel

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if (!(RankMask & ValidRankMask)) {
      continue;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      Offset = OFFSET_CALC_CH (CH0_CR_SC_WR_DELAY_REG, CH1_CR_SC_WR_DELAY_REG, Channel);
      ScWrDelay.Data = MrcReadCR (MrcData, Offset);
      DeltaPi = (WrLvlRankMin[Channel][Rank] -  WrLvlChCycle[Channel] * 128);
      WrLvlRankCycle[Channel][Rank] = RANGE ((DeltaPi - DqPiReserve) / 128, 0, MAX_ADD_RANK_DELAY);
      FifoFlybyDelay = WrLvlRankCycle[Channel][Rank];
      //Grab the longest TxDqFifoRdEnDelay per ch across all ranks
      MaxChTxDqFifoRdEnDelay[Channel] = MAX (WrLvlRankCycle[Channel][Rank], MaxChTxDqFifoRdEnDelay[Channel]);
      GetSetVal1 = 0ULL;
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, TxDqFifoRdEnFlybyDelay,    WriteToCache | PrintValue, &FifoFlybyDelay);
        MrcGetSetDdrIoGroupChSch    (MrcData, Channel, SubCh, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache | PrintValue, &GetSetVal1);

        if (Gear2) {
          TxDqFifoWrEn = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) + (2 * ScWrDelay.Bits.Add_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
        } else {
          TxDqFifoWrEn = tCWL - ScWrDelay.Bits.Dec_tCWL + ScWrDelay.Bits.Add_tCWL - 2; // TxDqFifoWrEnTcwlDelay(DClk)
        }
        TxDqFifoRdEn = TxDqFifoWrEn + TxFifoSeparation + AddOneQclk[Channel]; // TxDqFifoRdEnTcwlDelay(DCLK)
        if (TxDqFifoRdEn < 0) {
          TxDqFifoRdEn = 0;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s Not enough Tx FIFO separation! TxDqFifoWrEn: %d, TxFifoSeparation: %d\n", gErrString, (UINT32) TxDqFifoWrEn, TxFifoSeparation);
        }

        MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoWrEnTcwlDelay, WriteToCache | PrintValue, &TxDqFifoWrEn);
        MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoRdEnTcwlDelay, WriteToCache | PrintValue, &TxDqFifoRdEn);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tChCyc\tRankCyc\tDqsPi\tDqPi\n", Channel, Rank);
      // Program the final settings to the DQ bytes and update MrcData
      for (Byte = 0; Byte < SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        GetSetVal = WrLvlTotPiDly[Channel][Rank][Byte] - WrLvlChCycle[Channel] * 128 - WrLvlRankCycle[Channel][Rank] * 128;
        Status  = MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,  WriteToCache, &GetSetVal); // Write same value as DQS; DQ will be adjusted below.
        Status2 = MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
        if ((Status == mrcParamSaturation) || (Status2 == mrcParamSaturation)) {
          Saturated = TRUE;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  B%d:\t%d\t%d\t%d", Byte, WrLvlChCycle[Channel], WrLvlRankCycle[Channel][Rank], (UINT32) GetSetVal);
        if (Lpddr4) {
          // Set DQ to the middle of the passing region
          ByteDqOffset = (ByteDqOffsetEnd[Channel][Rank][Byte] + ByteDqOffsetStart[Channel][Rank][Byte]) / 2;
          ChangeMargin (MrcData, Param, ByteDqOffset, 0, 0, Channel, Rank, Byte, 0, 1, 0);
        } else {
          GetSetVal = TxDqDqsDelayAdj;
          Status = MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteOffsetToCache, &GetSetVal);
          if (Status == mrcParamSaturation) {
            Saturated = TRUE;
          }
        }
#ifdef MRC_DEBUG_PRINT
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
#endif // MRC_DEBUG_PRINT
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d\n", (UINT32) GetSetVal);
      }
    } // for Channel
  } // for Rank
  MrcFlushRegisterCachedData (MrcData);

  if (Saturated) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s, Parameter saturation!\n", gErrString);
    return mrcParamSaturation;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoRdEnTcwlDelay,  ReadFromCache, &TxDqFifoRdEn);
        GetSetVal = (UINT16) (MaxChTxDqFifoRdEnDelay[Channel] + TxDqFifoRdEn + RTL_CONSTANT);
        //@todo <ICL> Temp: Setting TxAnlgEnGraceCnt less than MAX causing some issues in CNL.
        //MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, GsmIocTxAnlgEnGraceCnt, WriteToCache | PrintValue, &GetSetVal);
      }
    }
  }

  if (!Lpddr4)  {
    // Clean up after Test
    ChangeMargin (MrcData, Param, 0, 0, 1, 0, 0, 0, 0, 0, 0);  // Clean TxDq offset
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
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDdrType        DdrType;
  MrcStatus         Status;
  INT64             GetSetVal;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             TxDqDqsDelayAdj;
  UINT8             Channel;
  UINT8             SubCh;
  UINT8             Rank;
  UINT8             RankHalf;
  UINT8             RankMod2;
  UINT8             Byte;
  UINT8             refbyte;
  UINT8             RankMask;  // RankBitMask for both channels
  UINT8             ValidRankMask;
  UINT16            *MrReg;
  UINT16            WLStart;
  UINT16            WLStop;
  UINT16            WLDelay;
  UINT8             WLStep;
  UINT32            WaitTime;
  UINT32            CRValue;
  UINT32            Offset;
  UINT32            DqsToggleTime;
  INT32             InitialPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             InitialPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            FinalDqs[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             iWidth;
  INT32             cWidth;
  INT32             lWidth;
  INT32             ByteWidth;
  BOOLEAN           Pass;
  BOOLEAN           RankIsx16;
  BOOLEAN           SavedRestoreMRS;
  BOOLEAN           Lpddr4;
  BOOLEAN           Ddr4;
  BOOLEAN           DtHalo;
  UINT16            RttParkSetVal;
  TOdtValueDdr4     *Ddr4OdtTableIndex;
  DDR4_MODE_REGISTER_1_STRUCT             Ddr4ModeRegister1;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;

  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  ControllerOut    = &Outputs->Controller[0];
  Debug            = &Outputs->Debug;
  Status           = mrcSuccess;
  CRValue          = 0;
  ValidRankMask    = Outputs->ValidRankMask;
  GetSetEn         = 1;
  GetSetDis        = 0;
  DtHalo           = (Inputs->CpuModel == cmICL_DT_HALO_R);

  // Save the flag and force MRS recalculation
  SavedRestoreMRS = Outputs->RestoreMRs;
  Outputs->RestoreMRs = FALSE;

  DdrType = Outputs->DdrType;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4    = (DdrType == MRC_DDR_TYPE_DDR4);

  // 0.5UI for Gear 1, 1.5UI for Gear 2
  TxDqDqsDelayAdj = Outputs->Gear2 ? 96 : 32;

  // A0:
  //       | WlLongDelEn = 0                        |  WlLongDelEn = 1
  //---------------------------------------------------------------------------------------------
  // Gear1 | 32 bursts * 32  = 1024 UIs (Not used)  |  32 bursts * 64  = 2048 UIs
  // Gear2 | 32 bursts * 64  = 2048 UIs (Not used)  |  32 bursts * 128 = 4096 UIs

  //
  // B0:
  //       | WlLongDelEn = 0                        |  WlLongDelEn = 1
  //-----------------------------------------------------------------------------
  // Gear1 | 32 bursts * 64  = 2048 UIs (DDR4)      |  32 bursts * 128 = 4096 UIs (LP4)
  // Gear2 | 64 bursts * 128 = 8192 UIs             |  64 bursts * 256 = 16384 UIs (Not useed)
  //
  if (Inputs->IclA0) {
    DqsToggleTime = Outputs->Gear2 ? 4096 : 2048;
  } else {
    DqsToggleTime = Outputs->Gear2 ? 8192 : 2048;
  }

  // Set ForceBiasOn and make sure ForceRxAmpOn is cleared
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,  WriteToCache, &GetSetEn);

  if (!DtHalo) {
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetDis);
  }
  if (Inputs->IclA0) {
    GetSetVal = 1;
  } else {
    if (!Outputs->Gear2 && Lpddr4) {
      // LP4 Gear1: use WlLongDelEn to accomodate tWLO
      GetSetVal = 1;
      DqsToggleTime = 4096;
    } else {
      GetSetVal = 0;
    }
  }
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWlLongDelEn,  WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDisDataIdlClkGate, WriteToCache, &GetSetEn);
  MrcFlushRegisterCachedData (MrcData);

  // Enabling WLmode causes DQS to toggle for a certain number of UIs (see table above). Wait for this to stop.
  WaitTime = Outputs->UIps * DqsToggleTime;

  // DDR4: Set Qoff bit in MR1 on all ranks
  if (Ddr4) {
    MrcSetMR1_DDR4 (MrcData, 1, INIT_DIMM_RON_34, 0, 0, 1);
  }

  // Enable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if (!(RankMask & ValidRankMask)) {
      // Skip if all channels empty
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\n", Rank);

    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteToCache, &GetSetVal);

    RankHalf    = Rank / 2;
    RankMod2    = Rank % 2;
    // Program MR1: Set A7 to enter Write Leveling mode, and clear A12 (Qoff).
    // Write MaskRasWe to prevent scheduler from issuing non-Read commands
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {

        ChannelOut = &ControllerOut->Channel[Channel];

        // Enable WL mode in MR2[7]
        if (Lpddr4) {
          CRValue = (ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR2]);
          for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, mrMR2, (CRValue | MRC_BIT7), FALSE, FALSE, TRUE);
            }
          }
        } else {
          // Ddr4
          Ddr4OdtTableIndex = GetOdtTableIndex (MrcData, Channel, RankHalf);
          if (Ddr4OdtTableIndex == NULL) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: OdtTableIndex is NULL!\n");
            return mrcFail;
          }
          RttParkSetVal = (Ddr4OdtTableIndex->RttWr == 0xFFFF) ? 0 : Ddr4OdtTableIndex->RttWr; // To get High-Z we must disable Rtt Park (0)
          SetDimmParamValue (MrcData, Channel, RankMask, 0, OptDimmOdtPark, RttParkSetVal, FALSE);
          // RttWr must be disabled in Write Leveling mode
          SetDimmParamValue (MrcData, Channel, RankMask, 0, OptDimmOdtWr, 0, FALSE);
          Ddr4ModeRegister1.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR1];
          Ddr4ModeRegister1.Bits.WriteLeveling = 1;
          Ddr4ModeRegister1.Bits.Qoff          = 0;
          Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, (UINT16) Ddr4ModeRegister1.Data);
        }
      }
    }  // for Channel

    // Set TxPiOn and WLMode
    // The first burst comes out as we enable WL mode, need to ignore it
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,   WriteToCache, &GetSetEn);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode, WriteToCache, &GetSetEn);
    MrcFlushRegisterCachedData (MrcData);

    // Wait for the first burst to finish
    MrcWait (MrcData, (WaitTime * MRC_TIMER_1NS) / 1000);  // WaitTime is in [ps]

    // ******************************************
    // STEP 1 and 2: Find middle of high region
    // ******************************************
    // We will add 64 ticks at the end, so shift the range left by 64.
    WLStart = 192 - 64;
    WLStop  = 192 - 64 + 128;
    WLStep  = 2;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\n\tCh0\t\t\t\t\t\t\t\t%sCh1\n",
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
      );

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
      MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxDqsDelay, WriteCached, &GetSetVal);

      Status = IoReset (MrcData);
      MrcWait (MrcData, (WaitTime * MRC_TIMER_1NS) / 1000);  // WaitTime is in [ps]

      // Update results for all Channels/Bytes
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "\t\t\t\t\t\t\t\t%s",
            (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "\t" : ""
            );
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
            continue;
          }

          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          DataTrainFeedback.Data  = MrcReadCR (MrcData, Offset);
          Pass                    = (DataTrainFeedback.Bits.DataTrainFeedback >= 16);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%c%d", Pass ? '.' : '#', DataTrainFeedback.Data);
          if (WLDelay == WLStart) {
            if (Pass) {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = WLStart;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = WLStart;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = WLStart;
            } else {
              InitialPassingStart[Channel][Byte] = InitialPassingEnd[Channel][Byte]  = -WLStep;
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = -WLStep;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = -WLStep;
            }
          } else {
            if (Pass) {
              if (InitialPassingEnd[Channel][Byte] == (WLDelay - WLStep)) {
                InitialPassingEnd[Channel][Byte] = WLDelay;
              }

              if (CurrentPassingEnd[Channel][Byte] == (WLDelay - WLStep)) {
                CurrentPassingEnd[Channel][Byte] = WLDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = WLDelay;
              }
              // Special case for last step: Append Initial Passing Region
              // WLDelay should be considered a continuous range that wraps around 0
              if ((WLDelay >= (WLStop - WLStep)) && (InitialPassingStart[Channel][Byte] == WLStart)) {
                iWidth = (InitialPassingEnd[Channel][Byte] - InitialPassingStart[Channel][Byte]);
                CurrentPassingEnd[Channel][Byte] += (WLStep + iWidth);
              }
              // Update Largest variables
              cWidth  = CurrentPassingEnd[Channel][Byte] - CurrentPassingStart[Channel][Byte];
              lWidth  = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
              if (cWidth > lWidth) {
                LargestPassingStart[Channel][Byte]  = CurrentPassingStart[Channel][Byte];
                LargestPassingEnd[Channel][Byte]    = CurrentPassingEnd[Channel][Byte];
              }
            }
          }
        } // for Byte
      } // for Channel
    } // for WLDelay

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tInitPassSt\tInitPassEn\tCurrPassSt\tCurrPassEn\tLargPassSt\tLargPassEn\n");

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d\n", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "   B%d:\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
              Byte,
              InitialPassingStart[Channel][Byte],
              InitialPassingEnd[Channel][Byte],
              CurrentPassingStart[Channel][Byte],
              CurrentPassingEnd[Channel][Byte],
              LargestPassingStart[Channel][Byte],
              LargestPassingEnd[Channel][Byte]
              );
          }
        }
      }
    }
#endif // MRC_DEBUG_PRINT

    // Clean up after step
    // Program values for TxDQS
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ChannelOut = &ControllerOut->Channel[Channel];

        // Check if rank is a x16.  Don't apply to LPDDR parts.
        RankIsx16 = (((ChannelOut->Dimm[RankHalf].SdramWidth == 16) && Ddr4) ? TRUE : FALSE);

        // Clear ODT before MRS (JEDEC Spec)
        GetSetVal = 0;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocOdtOverride,    WriteToCache, &GetSetVal);
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocOdtOn,          WriteToCache, &GetSetVal);
        MrcFlushRegisterCachedData (MrcData);

        // Restore MR2 values
        if (Lpddr4) {
          CRValue = (ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR2]);
          for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, mrMR2, CRValue, FALSE, FALSE, TRUE);
            }
          }
        }
        if (Ddr4) {
          MrReg = &ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR0];
          // Restore Write Leveling mode and Rtt_Nom for this rank, set Qoff.
          Ddr4ModeRegister1.Data = MrReg[mrMR1];
          Ddr4ModeRegister1.Bits.Qoff = 1;
          MrcWriteMRS (MrcData, Channel, RankMask, mrMR1, Ddr4ModeRegister1.Data);

          // Restore RttWr and RttPark for this rank
          MrcWriteMRS (MrcData, Channel, RankMask, mrMR2, MrReg[mrMR2]);
          MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, MrReg[mrMR5]);
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tLftEdge Width\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          ByteWidth = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%d:\t%d\t%d\n",
            Byte,
            LargestPassingStart[Channel][Byte],
            ByteWidth
            );

          // Check if width is valid
          if ((ByteWidth <= 32) || (ByteWidth >= 96)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "\nERROR! Width region outside expected limits for Channel: %u Rank %u Byte: %u\n",
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
            if (LargestPassingStart[Channel][Byte] > (LargestPassingStart[Channel][refbyte] + 64)) {
              LargestPassingStart[Channel][Byte] -= 128;
            }

            if (LargestPassingStart[Channel][Byte] < (LargestPassingStart[Channel][refbyte] - 64)) {
              LargestPassingStart[Channel][Byte] += 128;
            }
          }

          // Add 1 QCLK to DqsPi
          if (!Outputs->Gear2) {
            LargestPassingStart[Channel][Byte] += 64;
          }

          // GetSetVal = LargestPassingStart[Channel][Byte];
          // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
          // GetSetVal += 32;
          // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteToCache, &GetSetVal);
          // Save the results from the current rank into a global array
          FinalDqs[Channel][Rank][Byte] = (UINT32) LargestPassingStart[Channel][Byte];
        } // for Byte
        MrcFlushRegisterCachedData (MrcData);
#ifdef MRC_DEBUG_PRINT
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.R%u:\tDqsPi\tDqPi\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
            // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
            // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal2);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  B%d:\t%u\t%u\n",
              Byte,
              (UINT32) FinalDqs[Channel][Rank][Byte],     // GetSetVal,
              (UINT32) FinalDqs[Channel][Rank][Byte] + (UINT32) TxDqDqsDelayAdj // GetSetVal2
              );
          }
        }
#endif
      }
    } // for Channel

    // Exit Write Leveling Mode and Re-enable TxPi Power Down.
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocWriteLevelMode,   WriteToCache, &GetSetDis);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis,     WriteToCache, &GetSetDis);
    // Set InternalClocksOn to avoid clock gating when we issue IoReset
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache, &GetSetEn);
    MrcFlushRegisterCachedData (MrcData);

    Status = IoReset (MrcData);

    // Clear InternalClocksOn
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache, &GetSetDis);
    MrcFlushRegisterCachedData (MrcData);
  } // for Rank

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if (!(RankMask & ValidRankMask)) {
      continue;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
          GetSetVal = (INT64) FinalDqs[Channel][Rank][Byte];
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, WriteToCache, &GetSetVal);
          GetSetVal += TxDqDqsDelayAdj;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,  WriteToCache, &GetSetVal);
        }
      }
    }
  } // for Rank
  MrcFlushRegisterCachedData (MrcData);

  // Clean up after Test
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // Restore DqControl2 values.
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceBiasOn, WriteToCache, &GetSetDis);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, (DtHalo) ? &GetSetEn : &GetSetDis);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocWlLongDelEn, WriteToCache, &GetSetDis);
      }
    }
  }
  // Restore cached value
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDisDataIdlClkGate, WriteToCache, &GetSetDis);
  MrcFlushRegisterCachedData (MrcData);

  if (Ddr4) {
    // Disable Qoff on all ranks
    // DLLEnable=1, Dic=0, Al=0, Level=0, Tdqs=0, Qoff=0
    MrcSetMR1_DDR4 (MrcData, 1, INIT_DIMM_RON_34, 0, 0, 0);
  }

  // Disable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteCached, &GetSetDis);

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
  MrcStatus     Status;
  MrcOutput     *Outputs;
  BOOLEAN       Lpddr4;
  INT64         GetSetVal;
  Outputs = &MrcData->Outputs;
  Lpddr4  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  MrcRelaxReadToReadSameRank (MrcData, TRUE);

  Status = WriteLevelingFlyBy (MrcData);

  MrcRelaxReadToReadSameRank (MrcData, FALSE);

  // Program final ForceBiasOn value; it was enabled/disabled in many basic training steps up to this point.
  // Subsequent training steps are not touching this bit.
  // Keep ForceBiasOn enabled on DDR4
  GetSetVal = (!Lpddr4) ? 1 : 0;
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn, WriteCached, &GetSetVal);

  return Status;
}

