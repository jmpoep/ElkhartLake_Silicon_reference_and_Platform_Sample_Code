/** @file
  Implementation of the receive enable algorithm.
  Receive enable training is made out of two stages, the first is finding the
  DQS rising edge for each DRAM device, and the second is determining the
  roundtrip latency by locating the preamble cycle.

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
#include "MrcReadReceiveEnable.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcCommon.h"
#include "MrcDdrIoApi.h"
#include "MrcDdrIoApiInt.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"

///
/// Local defines
///
#define MRC_RX_FLYBY_INIT     (3)
#define RRE_DCLK_PI_VAL       (128)
#define RRE_QCLK_PI_VAL       (64)
#define MRC_DQSCK_TEMP_GB     (90)
#define MRC_DQSCK_MILIVOLT_GB (45)

#define RCVEN_FIFO_DELAY (3) // In DCLKS
#define FIFO_GUARD_BAND  (3) // In DCLKS

///
/// Local Structs
///
typedef struct {
  GSM_GT Knob;
  INT32 ValInPi;
  INT32 NumToEqualDclk;
} RCV_EN_CMPLX_TYPE;

///
/// Globals
///
const RCV_EN_CMPLX_TYPE RcvEnCmplx[] = {
  { RxIoTclDelay, 128,   1 },  // Channel
  { RxFlybyDelay, 128,   1 },  // Rank
  { RecEnDelay,     1, 128 }   // Strobe
};

///
/// Common Strings
///
#ifdef MRC_RCVEN_DEBUG_MSG
const char gRcvEnBannerStr[] = "*************************";
const char gRcvEnMinMaxStr[] = "Min/Max Search";
const char gRcvEnChCalcStr[] = "Channel Calculation";
const char gRcvEnRankCalcStr[] = "Rank Calculation";
const char gRcvEnByteProgStr[] = "Byte Programming";
#endif

VOID
PrintTotalDelay (
  IN  MrcParameters *const  MrcData,
  IN  INT32 RcvEnTotPiDly[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
#if 1
#if ((defined MRC_RCVEN_DEBUG) && (MRC_RCVEN_DEBUG == SUPPORT))
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT32 Controller;
  UINT32 Channel;
  UINT32 Rank;
  UINT32 Byte;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Total Receive Enable Delay\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            continue;
          }
          MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Mc%u.C%u.R%u.B%u: %u\n", Controller, Channel, Rank, Byte, RcvEnTotPiDly[Controller][Channel][Rank][Byte]);
        }
      }
    }
  }
#endif // ((defined MRC_RCVEN_DEBUG) && (MRC_RCVEN_DEBUG == SUPPORT))
#endif // if 0
}

/**
  Perform receive enable training.
  Optimize RcvEn timing with MPR pattern

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
MrcStatus
MrcReadLevelingTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  static const Cpgc20Address CPGCAddress = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0,
    0,
    0,
    0,
    5,
    1 // Banks
  };
  static const Cpgc20Address CPGCAddressDdr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0,
    0,
    0,
    0,
    4,
    2 // Banks
  };
  const Cpgc20Address      *CpgcAddress;
  const RCV_EN_CMPLX_TYPE  *RcvEnKnobPtr;
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcOutput             *Outputs;
  MrcChannelOut         *ChannelOut;
  MrcStatus             CurStatus;
  MrcStatus             Status;
  MrcProfile            Profile;
  MrcDdrType            DdrType;
  MRC_PATTERN_CTL       PatternCtl;
  GSM_GT                KnobMoved;
  INT64                 GetSetVal;
  INT64                 GetSetEn;
  INT64                 GetSetDis;
  INT64                 RxFifoRdEnFlyby;
  INT64                 RxIoTclInit;
  INT64                 RxDataValidDclk;
  INT64                 Roundtrip;
  INT64                 DataTrainFeedbackField;
  INT32                 InitialPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 IncPreAmble[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 RcvEnTotPiDly[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 RcvEnChRankMin[MAX_RANK_IN_CHANNEL];
  INT32                 RcvEnChRankMax[MAX_RANK_IN_CHANNEL];
  INT32                 Inc;
  INT32                 RLStart;
  INT32                 RLStop;
  INT32                 RLStep0;
  INT32                 RLDelay;
  INT32                 FineStep;
  INT32                 RcvEnChMin;
  INT32                 RcvEnChMax;
  INT32                 CurRcvEnTotPiDly;
  INT32                 cWidth;
  INT32                 lWidth;
  INT32                 Center;
  INT32                 Width;
  INT32                 PreamblePark;
  INT32                 RxFlybyDelPiVal;
  INT32                 RxIoTclPiVal;
  INT32                 RxFlyByMaxLimit;
  INT32                 RcvEnPiMaxLimit;
  INT32                 ChDelta;
  INT32                 HeadRoom;
  INT32                 RnkPiRsv;
  INT32                 ChDel;
  INT32                 ChDelayClk;
  INT32                 RnkDelta;
  INT32                 RnkStrbDel;
  INT32                 RnkDelClk;
  INT32                 ChRnkDelay;
  INT32                 RxFifoRdEnRankVal;
  INT32                 RcvEnPiRsvd;
  UINT32                RxFifoDelay;
  UINT32                TdqsCkDriftPs;
  UINT32                RxFifoTclClkPs;
  UINT32                Tcl;
  UINT32                KnobIdx;
  UINT32                Byte;
  UINT32                ByteStop;
  UINT32                Rank;
  UINT32                Gear2;
  UINT32                Data32;
  UINT16                RoundTripVals[MAX_SUB_CHANNEL][MAX_RANK_IN_DIMM];
  UINT16                RxFifoRdEnRank[MAX_SUB_CHANNEL][MAX_RANK_IN_DIMM];
  UINT16                ChResult[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16                ChMask[MAX_CONTROLLER][MAX_CHANNEL];
  UINT16                RxFifoRdEnRankDlyInPi;
  INT8                  UnmatchedPreambleToggles;
  UINT8                 NumSamples;
  UINT8                 Controller;
  UINT8                 MaxChannels;
  UINT8                 Channel;
  UINT8                 RankMask;
  UINT8                 McChBitMask;
  UINT8                 ValidRankMask;  // RankBitMask for both channels
  UINT8                 Done;
  UINT8                 NumCL;
  UINT8                 SamplesAdd;
  UINT8                 NumKnobs;
  UINT8                 EnDqsNRcvEnSave;
  BOOLEAN               UnMatched;
  BOOLEAN               BlockSdlWithRcvEnSet;
  BOOLEAN               Pass;
  BOOLEAN               Lpddr;
  BOOLEAN               Lpddr5;
  BOOLEAN               Ddr4;
  BOOLEAN               NotDone;
  MRC_BG_BANK_PAIR      BankMapping[MAX_CONTROLLER][MAX_CHANNEL][MAX_BANKS];
  DDR4_MODE_REGISTER_3_STRUCT Ddr4Mr3;
  DDR4_MODE_REGISTER_4_STRUCT Ddr4Mr4;
#ifdef MRC_DEBUG_PRINT
  INT32                 MinChDelay[MAX_CONTROLLER][MAX_CHANNEL];
#endif // MRC_DEBUG_PRINT

  Inputs                = &MrcData->Inputs;
  MrcCall               = Inputs->Call.Func;
  Outputs               = &MrcData->Outputs;
  Debug                 = &Outputs->Debug;
  DdrType               = Outputs->DdrType;
  ValidRankMask         = Outputs->ValidRankMask;
  Profile               = Inputs->MemoryProfile;
  Status                = mrcSuccess;
  Done                  = 0;
  GetSetEn              = 1;
  GetSetDis             = 0;
  Ddr4                  = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr5                = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Lpddr                 = Outputs->Lpddr;
  PatternCtl.IncRate    = 32;
  PatternCtl.Start      = 0;
  PatternCtl.Stop       = 9;
  PatternCtl.DQPat      = BasicVA;
  PatternCtl.PatSource  = MrcPatSrcStatic;
  KnobMoved             = GsmGtMax;
  Tcl                   = 0;
  Gear2                 = Outputs->Gear2 ? 1 : 0;
  MaxChannels           = Outputs->MaxChannels;
  EnDqsNRcvEnSave       = 0xFF;
  RxFifoTclClkPs        = (Gear2) ? Outputs->Qclkps : Outputs->Dclkps;
  RcvEnPiRsvd           = 320; // PI ticks.
  UnMatched             = ((Outputs->RxMode == MrcRxModeUnmatchedRxWPpath) || (Outputs->RxMode == MrcRxModeUnmatchedRxWRload));
  BlockSdlWithRcvEnSet  = 0;
  //@todo - Hook to DRAM MR
  UnmatchedPreambleToggles = (Lpddr5 && UnMatched) ? 1 : 0;
  if (Ddr4) {
    TdqsCkDriftPs = 0;
  } else {
    TdqsCkDriftPs = MRC_DQSCK_PS_PER_DEGREE_LP4 * MRC_DQSCK_TEMP_GB + MRC_DQSCK_PS_PER_MV_LP4 * MRC_DQSCK_MILIVOLT_GB;
  }

  NumSamples = 6;
  RLStep0    = 8;
  FineStep   = 1;
  NumCL      = 8; // gives us about tCL*2 + flyby + NumCL*8 + 2(preamble) ~ 86QClk till last dqs (the init RTL should be big enough to overcome this delay !)
  SamplesAdd = MrcLog2 (NumCL) - 1;  // The log function return +1 so we subtract 1

  // Determine the limits of the used knobs.
  MrcGetSetLimits (MrcData, RxFlybyDelay, NULL, &GetSetVal, NULL);
  RxFlyByMaxLimit = (INT32) GetSetVal;
  MrcGetSetLimits (MrcData, RecEnDelay, NULL, &GetSetVal, NULL);
  RcvEnPiMaxLimit = (INT32) GetSetVal;

  RcvEnKnobPtr          = RcvEnCmplx;
  NumKnobs              = ARRAY_COUNT (RcvEnCmplx);
  RxFlybyDelPiVal       = RRE_DCLK_PI_VAL;
  RxIoTclPiVal          = RRE_DCLK_PI_VAL;
  RxFifoRdEnRankDlyInPi = Gear2 ? RRE_DCLK_PI_VAL : RRE_QCLK_PI_VAL;
  CpgcAddress           = Ddr4 ? &CPGCAddressDdr4 : &CPGCAddress;

  // CmdPat=PatRd, NumCL, LC, CpgcAddress, SOE=0, PatternCtl, EnCADB=0, EnCKE=0, SubSeqWait=128
  SetupIOTest (MrcData, Outputs->McChBitMask, PatRd, NumCL, NumSamples + SamplesAdd, CpgcAddress, NSOE, &PatternCtl, 0, 0, 128);

  // Setup ChMask based on SubChannel population
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      ChMask[Controller][Channel] = ChannelOut->ValidByteMask;

      // Enable ReadLeveling Mode, Force On ODT and SenseAmp
      // Force on SenseAmp
      MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetEn);
      MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteToCache, &GetSetEn);

      // Get tCL.  Needed for FIFO timing.  Both channels have the same tCL.
      Tcl = ChannelOut->Timing[Profile].tCL;

      if (Lpddr5) {
        Tcl *= 4;  //DCLK to WCK
      }
      // Set initial RcvEn knobs.
      // Channel is programmed in the Rank loop since we need to reset it on each rank trained.
      GetSetVal = MRC_RX_FLYBY_INIT;
      MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, RxFlybyDelay, WriteToCache | PrintValue, &GetSetVal);
      if (Lpddr && (EnDqsNRcvEnSave == 0xFF)) {
        //Read from Byte 0 as it will always exist on Existing Channel
        MrcGetSetChStrb (MrcData, Controller, Channel, 0, GsmIocEnDqsNRcvEn, ReadFromCache | PrintValue, &GetSetVal);
        EnDqsNRcvEnSave = (UINT8) GetSetVal;
      }
      //if (UnMatched) {
      //  MrcGetSetChStrb (MrcData, Controller, Channel, 0, GsmIocEnDqsNRcvEn, ReadFromCache | PrintValue, &GetSetVal);
      //}
      if (Ddr4) {
        // DDR4 uses different bank sequence to get back-to-back READs
        // Save Bank Mapping
        MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_GET);
        MrcGetSetBankSequence (MrcData, Controller, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
      }
    }
  }
  if (Lpddr) {
    // Must Disable before enabling Read Leveling Mode
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocEnDqsNRcvEn, WriteToCache | PrintValue, &GetSetDis);
  }
  MrcFlushRegisterCachedData (MrcData);

  // Determine where to park the preamble at the end of training
  // For LP4/LP5, training will walk back until it finds first low
  // which will be after preamble toggles.
  // Assumption here is that we guarantee at least 2UI of ODT turn-on before RcvEn.
  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      if (UnMatched) {
        PreamblePark = (EnDqsNRcvEnSave) ? 128 : 64;
      } else {
        PreamblePark = 128;
      }
      break;

    case MRC_DDR_TYPE_LPDDR5:
      if (UnMatched) {
        PreamblePark = (EnDqsNRcvEnSave) ? 256 : 128;
      } else {
        PreamblePark = 128;
      }
      break;

    case MRC_DDR_TYPE_DDR5:
    case MRC_DDR_TYPE_DDR4:
    default:
      PreamblePark = 64;
      break;
  }
  if (Lpddr && !BlockSdlWithRcvEnSet) {
    PreamblePark -= 32;
  }

  RxIoTclInit = Tcl + MrcFemtoTimeToTCK (MrcData, 3500000 / (Gear2 + 1));  // @todo Might need to adjust post-si

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocReadLevelMode, WriteNoCache, &GetSetEn);

  // We will add the trained RcvEn PI into this after the fine centering step.
  MrcCall->MrcSetMemDword (
    (UINT32 *) RcvEnTotPiDly,
    sizeof (RcvEnTotPiDly) / sizeof (UINT32),
    (((UINT32) RxIoTclInit * RxIoTclPiVal) + (MRC_RX_FLYBY_INIT * RxFlybyDelPiVal))
    );
  PrintTotalDelay (MrcData, RcvEnTotPiDly);

  // Enable Rank Mux Override
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if ((RankMask & ValidRankMask) == 0) {
      // Skip if this rank is not present on any of the channels
      continue;
    }

    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteNoCache, &GetSetVal);

    // Init Channel Delay Component
    MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, RxIoTclDelay, WriteToCache, &RxIoTclInit);
    MrcFlushRegisterCachedData (MrcData);

    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

        if (Ddr4) {
          // Enable MPR mode - needed for DDR4 Read Preamble Training mode
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Ddr4Mr3.Bits.MprOperation = 1;
          MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
          // Enable DDR4 Read Preamble Training mode
          Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
          Ddr4Mr4.Bits.ReadPreambleTrainingMode = 1;
          MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
          // Enable MPR mode in MC
          GetSetVal = 1;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccMprTrainDdrOn, WriteCached, &GetSetVal);
        }
      }
    }

    // STEP 1: Find middle of high region
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRank %d\nStep 1 Find Middle of high region\nCh/Byte\t0\t  1\nRcvEnPi\t", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %s", "012345678", "012345678");

    RLStart = 256;
    RLStop  = RLStart + 192;
    for (RLDelay = RLStart; RLDelay < RLStop; RLDelay += RLStep0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%d:\t", RLDelay);
      // Program RL Delays:
      GetSetVal = RLDelay;
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        if (!(MrcControllerExist (MrcData, Controller))) {
          continue;
        }
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteCached, &GetSetVal);
          } // Byte
        } // Channel
      } // Controller
      // Run Test, Reset FIFOs will be done before running test
      RunIOTest (MrcData, McChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Controllers/Channels/Bytes
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%s", (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
            continue;
          }

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
              continue;
            }
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            Pass = (DataTrainFeedbackField >= (UINT8) (MRC_BIT0 << (NumSamples - 1)));
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", Pass ? "1" : "0");
            if (RLDelay == RLStart) {
              if (Pass) {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = RLStart;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = RLStart;
              } else {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = -RLStep0;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = -RLStep0;
              }
            } else {
              if (Pass) {
                if (InitialPassingEnd[Controller][Channel][Byte] == (RLDelay - RLStep0)) {
                  InitialPassingEnd[Controller][Channel][Byte] = RLDelay;
                }

                if (CurrentPassingEnd[Controller][Channel][Byte] == (RLDelay - RLStep0)) {
                  CurrentPassingEnd[Controller][Channel][Byte] = RLDelay;
                } else {
                  CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = RLDelay;
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
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
        } // for Channel
      } // for Controller
    } // for RLDelay

    // Update RcvEn timing to be in the center of the high region.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%dC%d.R%d:\tLeft\tRight\tWidth\tCenter\n", Controller, Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            continue;
          }
          Center = (LargestPassingEnd[Controller][Channel][Byte] + LargestPassingStart[Controller][Channel][Byte]) / 2;
          Width = LargestPassingEnd[Controller][Channel][Byte] - LargestPassingStart[Controller][Channel][Byte];

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            " B%d:\t%d\t%d\t%d\t%d\n",
            Byte,
            LargestPassingStart[Controller][Channel][Byte],
            LargestPassingEnd[Controller][Channel][Byte],
            Width,
            Center
          );

          // Check if width is valid
          if ((Width < 32) || (Width > 96)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "\n%s Width region (%d) outside expected limits [32..96] for Mc: %u Ch: %u Byte: %u\n",
              gErrString,
              Width,
              Controller,
              Channel,
              Byte
            );
            if (Inputs->ExitOnFailure) {
              return mrcReadLevelingError;
            }
          }

          GetSetVal = Center;
          MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteCached, &GetSetVal);

          // Add the trained RcvEn Pi to get current total delay.
          RcvEnTotPiDly[Controller][Channel][Rank][Byte] += Center;
        } // for Byte
      } // for Channel
    } // for Controller

    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // Step 2: Move Cycle delay from Strobe PI to Channel to give more headroom in the Strobe delay.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 2: Move cycle delay from Byte to Channel\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        RcvEnChMin  = MRC_INT32_MAX;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
            continue;
          }
          MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
          RcvEnChMin = MIN (RcvEnChMin, (INT32) GetSetVal);
        }
        // To prevent shifting too much into Channel
        RcvEnChMin = MAX ((RcvEnChMin - RxIoTclPiVal), 0);

        // Reserve 1 DCLK for Parking in the Preamble to avoid clamping.  Protect against INT underflow.
        RcvEnChMin -= 128;
        RcvEnChMin  = MAX (RcvEnChMin, 0);

        // Convert from Strobe PI's to Channel cycle's
        ChDelayClk = RcvEnChMin / RxIoTclPiVal;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u\n", Controller, Channel);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, " MinRcvEn = %u\n CycleOff = %u\n", RcvEnChMin, ChDelayClk);
        if (ChDelayClk > 0) {
          GetSetVal = ChDelayClk;
          MrcGetSetMcCh (MrcData, Controller, Channel, RxIoTclDelay, WriteOffsetCached | PrintValue, &GetSetVal);

          GetSetVal = -ChDelayClk * RxIoTclPiVal;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached | PrintValue, &GetSetVal);
          } // Byte
        } // if (ChDelayClk > 0)
      } // Channel
    } // Controller

    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 3: Walk Backwards to find the preamble.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 3: Quarter Preamble - Walk Backwards (In PI ticks)\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t\t\t0\t\t\t1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ?
      "0 1 2 3 4 5 6 7 8\t\t0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 \t\t0 1 2 3 4 5 6 7"
      );

#ifdef MRC_DEBUG_PRINT
    MrcCall->MrcSetMemDword ((UINT32 *) MinChDelay, MAX_CONTROLLER * MAX_CHANNEL, 0);
#endif // MRC_DEBUG_PRINT
    do {
      // Run Test
      RunIOTest (MrcData, McChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Controller/Channel/Bytes
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        MrcCall->MrcSetMemWord ((UINT16 *) ChResult[Controller], MAX_CHANNEL, 0);
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            if (Channel == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t"); //@todo revisit this tabbing across memory techs
            }
            continue;
          }
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

#ifdef MRC_DEBUG_PRINT
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 4d\t", MinChDelay[Controller][Channel]);
#endif // MRC_DEBUG_PRINT

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  "); //@todo revisit this spacing across memory techs
              continue;
            }
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            Pass = (DataTrainFeedbackField >= (UINT16) (1 << (NumSamples - 1)));
            if (Pass) {
              ChResult[Controller][Channel] |= (1 << Byte);
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? "H " : "L ");
          }

          // Adjust Timing
          // If one byte is not at the Preamble yet, we're walking back 1 DCLK
          // The fall through to handle RcvEn correction for bytes in the preamble.
          if (ChResult[Controller][Channel] == 0) {
            continue;
          }
#ifdef MRC_DEBUG_PRINT
          MinChDelay[Controller][Channel] -= RRE_DCLK_PI_VAL;
#endif // MRC_DEBUG_PRINT
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            RcvEnTotPiDly[Controller][Channel][Rank][Byte] -= RRE_DCLK_PI_VAL;
          }
          for (KnobIdx = 0; KnobIdx < NumKnobs; KnobIdx++) {
            Status = mrcSuccess;
            GetSetVal = -RcvEnKnobPtr[KnobIdx].NumToEqualDclk;
            if (RcvEnKnobPtr[KnobIdx].Knob == RecEnDelay) {
              Byte = 0;
              ByteStop = Outputs->SdramCount;
            } else {
              // Run the per-byte loop only once.
              Byte = MRC_IGNORE_ARG;
              ByteStop = Byte + 1;
            }
            for (; Byte < ByteStop; Byte++) {
              CurStatus = MrcGetSetStrobe (
                MrcData,
                Controller,
                Channel,
                Rank,
                Byte,
                RcvEnKnobPtr[KnobIdx].Knob,
                WriteOffsetCached,
                &GetSetVal
              );
              if (Status == mrcSuccess) {
                Status = CurStatus;
              }
            }
            // If the knob is saturated walking backwards, continue to the
            // next knob until we run out of knobs or are successful.  Otherwise
            // we break out of the knob loop.
            if (Status == mrcSuccess) {
              KnobMoved = RcvEnKnobPtr[KnobIdx].Knob;
              KnobIdx = NumKnobs;
            }
          } // for KnobIdx
          if (Status != mrcSuccess) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s  Cannot go backwards anymore\n", gErrString);
            return mrcReadLevelingError;
          }

          // For bytes that were already at the preamable, Add 1 DCLK (128 PI)
          // to their byte delay to keep them in the same spot if we moved a
          // knob that adjust groups of bytes.
          if (KnobMoved != RecEnDelay) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if ((ChResult[Controller][Channel] & (1 << Byte)) == 0) { // if byte is low
                GetSetVal = RRE_DCLK_PI_VAL;
                RcvEnTotPiDly[Controller][Channel][Rank][Byte] += RRE_DCLK_PI_VAL;
                Status = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);

                if (Status != mrcSuccess) {
                  // Error Handler
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s RcvEn Saturated while walking backwards: %u\n", gErrString);
                  if (Inputs->ExitOnFailure) {
                    return mrcReadLevelingError;
                  }
                }
              } // (((ChResult[Channel] & (1 << Byte)) == 0)
            } // for Byte
          } // if (KnobMoved != RecEnDelay)
        } // for Channel
      } // for Controller
      NotDone = FALSE;
      for (Controller = 0; (Controller < MAX_CONTROLLER) && (NotDone == FALSE); Controller++) {
        for (Channel = 0; (Channel < MaxChannels) && (NotDone == FALSE); Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          NotDone = ChResult[Controller][Channel] ? TRUE : FALSE;
        }
      }
    } while (NotDone); // while preamble not found on all bytes yet
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

#ifdef MRC_DEBUG_PRINT
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Controller, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
      } // Channel
    } // Controller
#endif // MRC_DEBUG_PRINT
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 4: Add 1 qclk to move closer to the first burst.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 4: Add 1qclk.\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }

        GetSetVal = RRE_QCLK_PI_VAL;
        //GetSetVal = UnMatched ? RRE_QCLK_PI_VAL  * 2 : RRE_QCLK_PI_VAL
        // Update RcvEnDelay tracking.
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
            RcvEnTotPiDly[Controller][Channel][Rank][Byte] += RRE_QCLK_PI_VAL;
            Status = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached | PrintValue, &GetSetVal);
          }
        }
        if (Status != mrcSuccess) {
          // Since we moved as much of the Byte Delay as we could into Channel, we fail if we saturate here.
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s Saturated RcvEn while looking for the Preamble Edge\n", gErrString);
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }
      } // Channel
    } // Controller
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 5: Walk forward to find the first transaction edge.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 5: Walk forward to find rising edge\n");
    // Find Rising Edge
    MrcCall->MrcSetMemWord ((UINT16 *) ChResult, MAX_CONTROLLER * MAX_CHANNEL, 0);

    for (Inc = 0; Inc < RRE_QCLK_PI_VAL; Inc += FineStep) {
      // Run Test
      RunIOTest (MrcData, McChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Channel/bytes
      Done = 1;
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            // Skip Bytes that are already done.
            if (ChResult[Controller][Channel] & (1 << Byte)) {
              continue;
            }
            // Check if Byte is done defined by finding the high region of the first strobe.
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            Pass = (DataTrainFeedbackField >= (UINT8) (1 << (NumSamples - 1)));
            if (Pass) {
              ChResult[Controller][Channel] |= (1 << Byte);
              RcvEnTotPiDly[Controller][Channel][Rank][Byte] += Inc;
            } else {
              GetSetVal = FineStep;
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);
              IncPreAmble[Controller][Channel][Byte] = Inc;
            }
          } // for Byte
          if (ChResult[Controller][Channel] != ChMask[Controller][Channel]) {
            Done = 0;
          }
        } // for Channel
      } // Controller
      // Skip additional testing if all Channel/bytes done
      if (Done) {
        break;
      }
    }  // Inc
#ifdef MRC_RCVEN_DEBUG_MSG
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChResult[Mc%d][Ch%d]: 0x%x\n", Controller, Channel, ChResult[Controller][Channel]);
      }
    }
#endif
    // Check if Edge was found for all Bytes in the channels
    if (!Done) {
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%s Pre-amble edge not found for all Bytes with following final RcvEn results\n",
        gErrString
        );

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Controller %u Channel %u Rank %u:  Preamble\n", Controller, Channel, Rank);
          MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Controller, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            // ChMask is 0 for bytes that don't exist, and ChResult is 0 by default.
            // Bytes that don't exist will never be set in ChResult.
            // Thus small code savings skipping ByteExists here.
            if (((ChResult[Controller][Channel] ^ ChMask[Controller][Channel]) & (1 << Byte)) != 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Check byte %u\n", gErrString, Byte);
            }
          }
        }
      }
#endif
      if (Inputs->ExitOnFailure) {
        return mrcReadLevelingError;
      }
    }
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 6: Sub 1 qclk to center in the middle of the preamble and Clean Up Rank.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 6: Mid Preamble\n");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u:  Preamble Increment\n", Controller, Channel);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
            // Place RecvEn in the middle of preamble - subtract 1 QCLK from the first strobe.
            GetSetVal = -PreamblePark;
            RcvEnTotPiDly[Controller][Channel][Rank][Byte] -= PreamblePark;
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "B%u, IncPreAmble %d\n",
              Byte,
              IncPreAmble[Controller][Channel][Byte]
            );
          }
        }
        MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Controller, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
      }
    }

    // Clean up DDR4 read preamble mode and MPR mode
    //@todo: <CNL> Move behind MemoryApi.
    if (Ddr4) {
      MrcWait (MrcData, 150 * MRC_TIMER_1NS);  // Allow MC to close open pages using PRE
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannels; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          // Clear MPR mode in MC before sending MRS commands
          GetSetVal = 0;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccMprTrainDdrOn, WriteCached, &GetSetVal);
          // Disable DDR4 Read Preamble Training mode
          Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
          MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
          // Disable MPR mode
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          MrcWriteMRS (MrcData, Controller, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
        }
      }
    } // if DDR4
  } // END OF RANK LOOP

  // Clean up after Test
  if (Ddr4) {
    // Restore the bank mapping
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_SET);
      } // for Channel
    } // Controller
  }
  if (Lpddr) {
    GetSetVal = EnDqsNRcvEnSave;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocEnDqsNRcvEn, WriteToCache | PrintValue, &GetSetVal);
  }

  GetSetVal = 0; // Disable Read Leveling Mode
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocReadLevelMode, WriteNoCache, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
  PrintTotalDelay (MrcData, RcvEnTotPiDly);

  // Step 7: Program RcvEn delays and Rx FIFO Timing.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 7: Program RcvEn Delays and Rx FIFO Timing\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }

      MrcCall->MrcSetMem ((UINT8 *) RoundTripVals, sizeof (RoundTripVals), 0);
      MrcCall->MrcSetMem ((UINT8 *) RxFifoRdEnRank, sizeof (RxFifoRdEnRank), 0);
      MrcCall->MrcSetMemDword ((UINT32 *) RcvEnChRankMin, MAX_RANK_IN_CHANNEL, MRC_INT32_MAX);
      MrcCall->MrcSetMemDword ((UINT32 *) RcvEnChRankMax, MAX_RANK_IN_CHANNEL, 0);
      RcvEnChMin = MRC_INT32_MAX;
      RcvEnChMax = 0;
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnMinMaxStr, gRcvEnBannerStr);
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }

        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Mc%u.Ch%u.Rank%u\nTotalPiDelay:\n", Controller, Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          CurRcvEnTotPiDly  = RcvEnTotPiDly[Controller][Channel][Rank][Byte];
          MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, " B%u: %u\n", Byte, CurRcvEnTotPiDly);
          RcvEnChMin  = MIN (RcvEnChMin, CurRcvEnTotPiDly);
          RcvEnChMax  = MAX (RcvEnChMax, CurRcvEnTotPiDly);
          RcvEnChRankMin[Rank]  = MIN (RcvEnChRankMin[Rank], CurRcvEnTotPiDly);
          RcvEnChRankMax[Rank]  = MAX (RcvEnChRankMax[Rank], CurRcvEnTotPiDly);
        } // Byte
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO,   "Rank     Min: %d Max: %d\n", RcvEnChRankMin[Rank], RcvEnChRankMax[Rank]);
      } // Rank
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO,     "Ch       Min: %d Max: %d\n", RcvEnChMin, RcvEnChMax);

      // Get RxDqDataValidDclk Delay for RoundTrip and RdDataValid alignment
      MrcGetSetMcCh (MrcData, Controller, Channel, RxDqDataValidDclkDelay, ReadFromCache, &RxDataValidDclk);

      // Check to see if there is enough delay in the lower scope knobs to satisfy this delay.
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnChCalcStr, gRcvEnBannerStr);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Channel %d\n", Channel);
      ChDelta  = RcvEnChMax - RcvEnChMin;
      HeadRoom  = RcvEnPiMaxLimit + (RxFlyByMaxLimit * RxFlybyDelPiVal);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  ChDelta: %d\n  HeadRoom: %d\n", ChDelta, HeadRoom);
      HeadRoom -= ChDelta;
      if (HeadRoom < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Not enough headroom to handle the delta. HeadRoom = %d\n", gErrString, HeadRoom);
        if (Inputs->ExitOnFailure) {
          return mrcReadLevelingError;
        }
        HeadRoom = 0;
      }
      // Reserve Rank and Strobe delay.
      RnkPiRsv  = MIN (HeadRoom, RcvEnPiRsvd);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  HeadRoom after Delta: %d\n  Pi Reserved: %d\n", HeadRoom, RnkPiRsv);

      // Determine the Channel RcvEn DCLK Delay from the smallest RcvEn.
      // Program Rx FIFO Ready to match.
      ChDel      = RcvEnChMin - RnkPiRsv;
      ChDelayClk = ChDel / RxIoTclPiVal;
      GetSetVal  = ChDelayClk;
      Status = MrcGetSetMcCh (MrcData, Controller, Channel, RxIoTclDelay, WriteCached | PrintValue, &GetSetVal);
      GetSetVal  = GetSetVal + RxFifoChDelay[DdrType][Gear2][(Controller * MaxChannels) + Channel];
        // Account for tDQSCK_DRIFT and receiver delay here.
      GetSetVal  += DIVIDECEIL (TdqsCkDriftPs, RxFifoTclClkPs) + DIVIDECEIL (MRC_DDRIO_RX_TO_FIFO_GB_PS, RxFifoTclClkPs) + UnmatchedPreambleToggles;
      RxFifoDelay = (UINT32) GetSetVal;
      CurStatus   = MrcGetSetMcCh (MrcData, Controller, Channel, RxFifoRdEnTclDelay, WriteCached | PrintValue, &GetSetVal);
      if (Inputs->ExitOnFailure && ((Status != mrcSuccess) || (CurStatus != mrcSuccess))) {
        return mrcReadLevelingError;
      }

      ChDel  = ChDelayClk * RxIoTclPiVal;
      // Calculate the delay consumed in the Ch scope.
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnRankCalcStr, gRcvEnBannerStr);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Rank %d\n", Rank);

        // Check to see if there is enough delay in the lower scope knobs to satisfy this delay.
        RnkStrbDel  = RcvEnChRankMin[Rank] - ChDel;
        RnkDelta    = RcvEnChRankMax[Rank] - RcvEnChRankMin[Rank];
        // We reduce the headroom by the remainder that cannot be programmed into the Rank Delay, and the PI to reserve for other training
        HeadRoom    = RcvEnPiMaxLimit - (RnkStrbDel % RxFlybyDelPiVal);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  Rank Delta: %d\n  HeadRoom: %d\n", RnkDelta, HeadRoom);
        HeadRoom   -= RnkDelta;
        if (HeadRoom < 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Not enough headroom to handle the delta. HeadRoom = %d\n", gErrString, HeadRoom);
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        // Determine the Rank RcvEn DCLK Delay from the smallest RcvEn Rank/Byte delay.
        RnkDelClk   = RcvEnChRankMax[Rank] + RcvEnChRankMin[Rank] - (ChDel * 2);
        RnkDelClk   = UDIVIDEROUND (RnkDelClk, 2);
        RnkDelClk  -= RcvEnPiRsvd;
        RnkDelClk   = RnkDelClk / RxFlybyDelPiVal;
        GetSetVal   = RnkDelClk;
        Status = MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFlybyDelay, WriteCached | PrintValue, &GetSetVal);
        // FIFO delay needs to account for the longest RcvEn Delay in this SubCh/Rank (x32) or Ch/Rank (x64)
        RxFifoRdEnRankVal = RcvEnChRankMax[Rank] - ChDel;
        RxFifoRdEnFlyby = DIVIDECEIL (RxFifoRdEnRankVal, RxFifoRdEnRankDlyInPi); // FifoRdEn needs to be at the latest Byte in the rank.
        CurStatus = MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFifoRdEnFlybyDelay, WriteCached | PrintValue, &RxFifoRdEnFlyby);

        if ((Status != mrcSuccess) || (CurStatus != mrcSuccess)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Parameter saturation: RxFlybyDelay=%s\tRxFifoRdEnFlybyDelay=%s\n", gMrcStatusStr[Status], gMrcStatusStr[CurStatus]);
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        // Calculate Roundtrip Latency
        Data32 = (RxFifoDelay * (2 - Gear2)) + (UINT32) (RxFifoRdEnFlyby);
        Data32 += 10 + 2;
        // Modify the RoundTrip formula to account for the preamble toggles in unmatched path
        Data32 -= UnmatchedPreambleToggles;
        if (Gear2) {
          // DDR4 or LP4 or LP5
          Data32 += (Lpddr5) ? 17 : 12;
        } else {
          // DDR4 or LP4/5
          Data32 += (Ddr4) ? 16 : 18;
        }
        Roundtrip = Data32;

        CurStatus = MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RoundTripDelay, WriteCached | PrintValue, &Roundtrip);

        // Determine the delay programmed in the Sch/Rank knobs above and then program the rest in the Strobe.
        ChRnkDelay = ChDel + (RnkDelClk * RxFlybyDelPiVal);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnByteProgStr, gRcvEnBannerStr);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          GetSetVal = (INT64) (RcvEnTotPiDly[Controller][Channel][Rank][Byte] - ChRnkDelay);
          Status = MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, WriteCached | PrintValue, &GetSetVal);
          if (Status != mrcSuccess) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Parameter saturation: RecEnDelay=%s\n", gMrcStatusStr[Status]);
            if (Inputs->ExitOnFailure) {
              return mrcReadLevelingError;
            }
          }
        } // Byte
      } // Rank
    } // Channel
  } // Channel
  MrcFlushRegisterCachedData (MrcData);

  // Print IO Latency/RcvEn
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusted Receive Enable Settings.\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d.Ch%d.R%d:\n", Controller, Channel, Rank);
        MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Controller, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
      }
    }
  }
#endif
  // Disable Rank Mux Override
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetDis);

  Status = IoReset (MrcData);

  return Status;
}

/**
  Once the DQS high phase has been found (for each DRAM) the next stage is to find out the round trip latency,
  by locating the preamble cycle. This is achieved by trying smaller and smaller roundtrip
  values until the strobe sampling is done on the preamble cycle.
  The following algorithm is used to find the preamble cycle:

  @param[in] MrcData         - all the global data

  @retval Nothing.
**/
MrcStatus
MrcRoundTripLatency (
  IN     MrcParameters *const MrcData
  )
{
/*  MrcStatus Status;
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  MrcDebug  *Debug;
  INT64     tRDRDdr;
  INT64     tRDRDdd;
  INT64     GetSetVal;
  INT8      ClkShifts[1];
  INT8      DeltaLimitRtl;
  INT8      Start;
  INT8      Stop;
  UINT8     Channel;
  UINT8     Rank;
  UINT8     OptParam;
  UINT8     RankMask;
  UINT8     TestList[1];
  UINT8     RtLatency[MAX_RANK_IN_CHANNEL];
  UINT8     LoopCount;
  UINT8     Update;
  UINT8     MaxRankRtl;
  UINT8     DeltaRtl;
  UINT8     PowerTrainingMode;
  UINT8     FifoRecovery;

  Status        = mrcSuccess;
  TestList[0]   = RdT;        // Test based on read eye width
  ClkShifts[0]  = 25;         // Delay by 25 pi ticks to guardband for delay drift/jitter
  LoopCount     = 10;
  Update        = 1;          // Apply the optimal settings
  MaxRankRtl    = 0;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Inputs        = &MrcData->Inputs;
  OptParam      = rtl;        // Which parameter to optimize for
  FifoRecovery  = RCVEN_FIFO_DELAY + FIFO_GUARD_BAND;

  PowerTrainingMode = 0;
  if (Inputs->PowerTrainingMode == 1) {
    // disable margin training mode to keep the correct UPM limits for this routine
    Inputs->PowerTrainingMode = 0;
    PowerTrainingMode = 1; // save/restore
  }
  // Train timing separately for each rank
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (MRC_BIT0 << Rank);
    if (!(RankMask & Outputs->ValidRankMask)) {
      continue;
    }
    // Pick starting and stopping points
    Stop      = 0;
    Start     = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank))) {
        continue;
      }
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MRC_IGNORE_ARG, RoundTripDelay, ReadFromCache | PrintValue, &GetSetVal);

      if (Stop < (UINT8) GetSetVal) {
        Stop = (UINT8) GetSetVal;
      }
    }

    Start = Stop - FifoRecovery;
    Start = MIN (0, Start);
    // Find optimal answer
    Status = TrainDDROptParamCliff (
              MrcData,
              OptParam,
              TestList,
              sizeof (TestList),
              Start,
              Stop,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              sizeof (ClkShifts),
              Rank,
              RankMask,
              0
              );
    if (Status == mrcFail) {
      return mrcRoundTripLatencyError;
    }
  }

  // Limit the RTL delta across the ranks present.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nLimit the delta between Rank's RTL value.\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (MrcData, 0, Channel)) {
      MaxRankRtl = 0;

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache, &tRDRDdr);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, ReadFromCache, &tRDRDdd);
      DeltaLimitRtl = MAX ((INT8) tRDRDdr, (INT8) tRDRDdd);
      // TA Times are in dclks.  Must convert to qclks and subtract the burst length.
      // Ensure we do not underflow the variable.
      DeltaLimitRtl = ((2 * DeltaLimitRtl) - 2 * Outputs->BurstLength);
      DeltaLimitRtl = MAX (DeltaLimitRtl, 0);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RTL Delta Limit: %d\n", DeltaLimitRtl);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MRC_IGNORE_ARG, RoundTripDelay, ReadFromCache, &GetSetVal);
          RtLatency[Rank] = (UINT8) GetSetVal;
          MaxRankRtl = MAX (MaxRankRtl, RtLatency[Rank]);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Rank %u RTL: %u\n", Rank, RtLatency[Rank]);
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MaxRankRtl: %u\n", MaxRankRtl);

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
          DeltaRtl = MaxRankRtl - RtLatency[Rank];
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Rank %d: DeltaRtl: %u\tDeltaLimitRtl: %u%s",
            Rank,
            DeltaRtl,
            DeltaLimitRtl,
            (DeltaRtl > DeltaLimitRtl) ? "\tNew RTL: " : ""
            );
          if (DeltaRtl > DeltaLimitRtl) {
            UpdateTAParamOffset (MrcData, 0, Channel, 0, OptParam, (INT8) MaxRankRtl - DeltaLimitRtl, 1, 0, 1 << Rank);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }
      }
    }
  }
  // clean up
  Inputs->PowerTrainingMode = PowerTrainingMode;

  return Status;*/
  return mrcSuccess;
}

/**
  Perform Receive Enable Timing Centering.
  Center Receive Enable using moderate pattern with 1D eye.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If successful, returns mrcSuccess.
**/
MrcStatus
MrcReceiveEnTimingCentering (
  IN MrcParameters *const MrcData
  )
{
  UINT8     LoopCount;

  LoopCount = 17;

  return DQTimeCentering1D (MrcData, RcvEnaX, 0, LoopCount, TRUE, FALSE);
}
