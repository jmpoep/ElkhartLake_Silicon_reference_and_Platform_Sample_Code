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
#include "MrcMaintenance.h"

///
/// Local defines
///
#define RCV_EN_CENTER_LC (17)
#define RCVEN_FIFO_DELAY (4) // In DCLKS
// Guardband for tDQSCK_DRIFT
#define FIFO_GUARD_BAND  (5) // In DCLKS

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
const char gRcvEnSchCalcStr[] = "Sub-Channel Calculation";
const char gRcvEnRankCalcStr[] = "Rank Calculation";
const char gRcvEnByteProgStr[] = "Byte Programming";
#endif

VOID
PrintTotalDelay (
  IN  MrcParameters *const  MrcData,
  IN  INT32 RcvEnTotPiDly[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
#if 0
#if ((defined MRC_RCVEN_DEBUG) && (MRC_RCVEN_DEBUG == SUPPORT))
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT32 Channel;
  UINT32 Rank;
  UINT32 Byte;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Total Receive Enable Delay\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "C%u.R%u.B%u: %u\n", Channel, Rank, Byte, RcvEnTotPiDly[Channel][Rank][Byte]);
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
  MrcControllerOut      *ControllerOut;
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
  INT64                 RxFifoDelay;
  INT64                 RxFifoRdEnFlyby;
  INT64                 RxIoTclInit;
  INT64                 RxDataValidDclk;
  INT64                 Roundtrip;
  INT64                 CommonFlyby;
  INT64                 FifoDelta;
  INT64                 FlybyDelta;
  INT32                 InitialPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 IncPreAmble[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 RcvEnTotPiDly[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                 RcvEnSchMin[MAX_SUB_CHANNEL];
  INT32                 RcvEnSchMax[MAX_SUB_CHANNEL];
  INT32                 RcvEnSchRankMin[MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32                 RcvEnSchRankMax[MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL];
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
  INT32                 SchDelta;
  INT32                 HeadRoom;
  INT32                 RnkPiRsv;
  INT32                 SchDel;
  INT32                 SchDelayClk;
  INT32                 RnkDelta;
  INT32                 RnkStrbDel;
  INT32                 RnkDelClk;
  INT32                 SchRnkDelay;
  INT32                 RxFifoRdEnRankVal;
  INT32                 SubCh;
  UINT32                Tcl;
  UINT32                KnobIdx;
  UINT32                Offset;
  UINT32                Byte;
  UINT32                ByteStop;
  UINT32                Rank;
  UINT32                Gear2;
  UINT32                Data32;
  UINT16                ChResult[MAX_CHANNEL];
  UINT16                ChMask[MAX_CHANNEL];
  UINT16                SubChResults;
  UINT16                RxFifoRdEnRankDlyInPi;
  UINT8                 ByteStart;
  UINT8                 BytesPerSch;
  UINT8                 ByteEnd;
  UINT8                 NumSamples;
  UINT8                 Channel;
  UINT8                 RankMask;
  UINT8                 ChBitMask;
  UINT8                 ValidRankMask;  // RankBitMask for both channels
  UINT8                 Done;
  UINT8                 NumCL;
  UINT8                 SamplesAdd;
  UINT8                 NumKnobs;
  BOOLEAN               Pass;
  BOOLEAN               Lpddr4;
  BOOLEAN               Ddr4;
  MRC_BG_BANK_PAIR      BankMapping[MAX_CHANNEL][MAX_BANKS];
  DDR4_MODE_REGISTER_3_STRUCT Ddr4Mr3;
  DDR4_MODE_REGISTER_4_STRUCT Ddr4Mr4;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;
#ifdef MRC_DEBUG_PRINT
  INT32                 MinSchDelay[MAX_CHANNEL][MAX_SUB_CHANNEL];
#endif // MRC_DEBUG_PRINT

  Inputs                = &MrcData->Inputs;
  MrcCall               = Inputs->Call.Func;
  Outputs               = &MrcData->Outputs;
  Debug                 = &Outputs->Debug;
  DdrType               = Outputs->DdrType;
  ControllerOut         = &Outputs->Controller[0];
  ChBitMask             = Outputs->ValidChBitMask;
  ValidRankMask         = Outputs->ValidRankMask;
  Profile               = Inputs->MemoryProfile;
  Status                = mrcSuccess;
  Done                  = 0;
  GetSetEn              = 1;
  GetSetDis             = 0;
  Ddr4                  = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4                = (DdrType == MRC_DDR_TYPE_LPDDR4);
  PreamblePark          = (Lpddr4) ? 64 : 64; // In PI ticks.  @todo Shall we get back to 128 for LP4 ?
  PatternCtl.IncRate    = 4;
  PatternCtl.Start      = 0;
  PatternCtl.Stop       = 9;
  PatternCtl.DQPat      = BasicVA;
  PatternCtl.PatSource  = MrcPatSrcStatic;
  BytesPerSch           = Outputs->SdramCount / Outputs->SubChCount;
  KnobMoved             = GsmGtMax;
  Tcl = 0;
  Gear2 = Outputs->Gear2 ? 1 : 0;

  NumSamples = 6;
  RLStep0    = 8;
  FineStep   = 1;
  NumCL      = 8; // gives us about tCL*2 + flyby + NumCL*8 + 2(preamble) ~ 86QClk till last dqs (the init RTL should be big enough to overcome this delay !)
  SamplesAdd = MrcLog2 (NumCL) - 1;  // The log function return +1 so we subtract 1

  // Determine the limits of the used knobs.
  MrcGetSetLimits (MrcData, RxIoTclDelay, NULL, &GetSetVal, NULL);
  MrcGetSetLimits (MrcData, RxFlybyDelay, NULL, &GetSetVal, NULL);
  RxFlyByMaxLimit = (INT32) GetSetVal;
  MrcGetSetLimits (MrcData, RecEnDelay, NULL, &GetSetVal, NULL);
  RcvEnPiMaxLimit = (INT32) GetSetVal;

  RcvEnKnobPtr    = RcvEnCmplx;
  NumKnobs        = ARRAY_COUNT (RcvEnCmplx);
  RxFlybyDelPiVal = RRE_DCLK_PI_VAL;
  RxIoTclPiVal    = RRE_DCLK_PI_VAL;
  RxFifoRdEnRankDlyInPi = RRE_QCLK_PI_VAL * (1 + (UINT16) Gear2);  // RXDQFIFORDENCHACHBx.RxDqFifoRdEnRank0ChADel: G1 in UI, G2 in tCK

  // Setup ChMask based on SubChannel population
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    ChMask[Channel] = ChannelOut->ValidByteMask;
    if (MrcChannelExist (Outputs, Channel) && Ddr4) {
      // DDR4 uses different bank sequence to get back-to-back READs
      // Save Bank Mapping
      MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_GET);
      MrcGetSetBankSequence (MrcData, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
    }
  }

  CpgcAddress = Ddr4 ? &CPGCAddressDdr4 : &CPGCAddress;

  // CmdPat=PatRd, NumCL, LC, CpgcAddress, SOE=0, PatternCtl, EnCADB=0, EnCKE=0, SubSeqWait=128
  SetupIOTest (MrcData, ChBitMask, PatRd, NumCL, NumSamples + SamplesAdd, CpgcAddress, NSOE, &PatternCtl, 0, 0, 128);

  // Enable RLMode, force ODT and SAmp, set initial roundtrip values.
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,   WriteToCache, &GetSetEn);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn,  WriteToCache, &GetSetEn);
  MrcFlushRegisterCachedData (MrcData);

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,    WriteToCache, &GetSetEn);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocReadLevelMode, WriteToCache, &GetSetEn);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    ChannelOut  = &ControllerOut->Channel[Channel];

    // Get tCL.  Needed for FIFO timing.  Both channels have the same tCL.
    Tcl = ChannelOut->Timing[Profile].tCL;

    // Set initial RcvEn knobs.
    // Channel is programmed in the Rank loop since we need to reset it on each rank trained.
    GetSetVal = MRC_RX_FLYBY_INIT;
    MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, MAX_SUB_CHANNEL, MAX_RANK_IN_CHANNEL, RxFlybyDelay, WriteToCache | PrintValue, &GetSetVal);

    if (Gear2) {
      // Clear out RxDqFifoRdEnRank values - it might have bit [0] set from DdrioInit which runs at 1067/G1 on LP4
      Offset = OFFSET_CALC_CH (MCMISCS_RXDQFIFORDENCHACHB0_REG, MCMISCS_RXDQFIFORDENCHACHB1_REG, Channel);
      MrcWriteCR (MrcData, Offset, 0);
      InvalidateRegisterCache (MrcData, Offset);
    }
  } // for Channel
  if (Lpddr4) {
    // Set RxDqsAmpOffset to zero for better strobe capture
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsAmpOffset, WriteToCache, &GetSetDis);
  }
  MrcFlushRegisterCachedData (MrcData);

  RxIoTclInit = Tcl;  // @todo Might need to adjust post-si

  // We will add the trained RcvEn PI into this after the fine centering step.
  // @todo: A/B Step Flyby Unit
  MrcCall->MrcSetMemDword (
    (UINT32 *) RcvEnTotPiDly,
    sizeof (RcvEnTotPiDly) / sizeof (UINT32),
    (((UINT32) RxIoTclInit * RxIoTclPiVal) + (MRC_RX_FLYBY_INIT * RxFlybyDelPiVal))
    );
  PrintTotalDelay (MrcData, RcvEnTotPiDly);

  // Enable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = (1 << Rank);
    if ((RankMask & ValidRankMask) == 0) {
      // Skip if this rank is not present on any of the channels
      continue;
    }

    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteToCache, &GetSetVal);

    // Init Channel Delay Component
    MrcGetSetDdrIoGroupChSchRnk (MrcData, MAX_CHANNEL, MAX_SUB_CHANNEL, MRC_IGNORE_ARG, RxIoTclDelay, WriteToCache, &RxIoTclInit);
    MrcFlushRegisterCachedData (MrcData);

    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];

      if (Ddr4) {
        // Enable MPR mode - needed for DDR4 Read Preamble Training mode
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        Ddr4Mr3.Bits.MprOperation = 1;
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
        // Enable DDR4 Read Preamble Training mode
        Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
        Ddr4Mr4.Bits.ReadPreambleTrainingMode = 1;
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
        // Enable MPR mode in MC
        GetSetVal = 1;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteCached, &GetSetVal);
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
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteCached, &GetSetVal);
        } // Byte
      } // Channel
      // Run Test, Reset FIFOs will be done before running test
      RunIOTest (MrcData, ChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Channels/Bytes
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%s", (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, (UINT8) Byte);
          Pass = (MrcReadCR (MrcData, Offset) >= (UINT8) (MRC_BIT0 << (NumSamples - 1)));

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", Pass ? "1" : "0");
          if (RLDelay == RLStart) {
            if (Pass) {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = RLStart;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = RLStart;
            } else {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte]  = -RLStep0;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte]  = -RLStep0;
            }
          } else {
            if (Pass) {
              if (InitialPassingEnd[Channel][Byte] == (RLDelay - RLStep0)) {
                InitialPassingEnd[Channel][Byte] = RLDelay;
              }

              if (CurrentPassingEnd[Channel][Byte] == (RLDelay - RLStep0)) {
                CurrentPassingEnd[Channel][Byte] = RLDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = RLDelay;
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
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? " " : "  ");
      } // for Channel
    } // for RLDelay

    // Update RcvEn timing to be in the center of the high region.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\tLeft\tRight\tWidth\tCenter\n", Channel, Rank);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }
        Center  = (LargestPassingEnd[Channel][Byte] + LargestPassingStart[Channel][Byte]) / 2;
        Width   = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          " B%d:\t%d\t%d\t%d\t%d\n",
          Byte,
          LargestPassingStart[Channel][Byte],
          LargestPassingEnd[Channel][Byte],
          Width,
          Center
          );

        // Check if width is valid
        if ((Width < 8) || (Width > 96)) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "\n%s Width region (%d) outside expected limits [8..96] for Ch: %u Byte: %u\n",
            gErrString,
            Width,
            Channel,
            Byte
            );
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        GetSetVal = Center;
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteCached, &GetSetVal);

        // Add the trained RcvEn Pi to get current total delay.
        RcvEnTotPiDly[Channel][Rank][Byte] += Center;
      } // for Byte
    }
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // Step 2: Move Cycle delay from Strobe PI to Channel to give more headroom in the Strobe delay.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 2: Move cycle delay from Byte to Channel\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      MrcCall->MrcSetMemDword ((UINT32 *) RcvEnSchMin, MAX_SUB_CHANNEL, MRC_INT32_MAX);
      RcvEnChMin  = MRC_INT32_MAX;
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        ByteStart = ChannelOut->ByteStart[SubCh];
        ByteEnd   = ChannelOut->ByteEnd[SubCh];

        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
          RcvEnSchMin[SubCh] = MIN (RcvEnSchMin[SubCh], (INT32) GetSetVal);
        }
        // To prevent shifting too much into Channel
        RcvEnSchMin[SubCh] = MAX ((RcvEnSchMin[SubCh] - RxIoTclPiVal), 0);
        RcvEnChMin = MIN (RcvEnChMin, RcvEnSchMin[SubCh]);
      } // SubCh

      if (!Outputs->EnhancedChannelMode) {
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          RcvEnSchMin[SubCh] = RcvEnChMin;
        }
      }

      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        // Reserve 1 DCLK for Parking in the Preamble to avoid clamping.  Protect against INT underflow.
        RcvEnSchMin[SubCh] -= 128;
        RcvEnSchMin[SubCh]  = MAX (RcvEnSchMin[SubCh], 0);

        // Convert from Strobe PI's to SubCh cycle's
        SchDelayClk = RcvEnSchMin[SubCh] / RxIoTclPiVal;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.Sch%u\n", Channel, SubCh);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, " MinRcvEn = %u\n CycleOff = %u\n", RcvEnSchMin[SubCh], SchDelayClk);
        if (SchDelayClk > 0) {
          GetSetVal = SchDelayClk;
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MRC_IGNORE_ARG, RxIoTclDelay, WriteOffsetCached | PrintValue, &GetSetVal);

          GetSetVal = -SchDelayClk * RxIoTclPiVal;
          ByteStart = ChannelOut->ByteStart[SubCh];
          ByteEnd   = ChannelOut->ByteEnd[SubCh];
          for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached | PrintValue, &GetSetVal);
          } // Byte
        } // if (SchDelayClk > 0)
      } // SubCh
    } // Channel
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 3: Walk Backwards to find the preamble.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 3: Quarter Preamble - Walk Backwards (In PI ticks)\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t\t\t0\t\t\t1\nByte\t\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ?
      "0 1 2 3 4 5 6 7 8\t\t0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 \t\t0 1 2 3 4 5 6 7"
      );

#ifdef MRC_DEBUG_PRINT
    MrcCall->MrcSetMemDword ((UINT32 *) MinSchDelay, MAX_CHANNEL * MAX_SUB_CHANNEL, 0);
#endif // MRC_DEBUG_PRINT
    do {
      // Run Test
      RunIOTest (MrcData, ChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Channel/Bytes
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChResult[Channel] = 0;

        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          if (Channel == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t");
          }
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];

#ifdef MRC_DEBUG_PRINT
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            if (SubCh != 0) {
              // Print the "/" between each number printed.
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "/");
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 4d", MinSchDelay[Channel][SubCh]);
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
#endif // MRC_DEBUG_PRINT

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
            // We leave this Byte in the ChResult mask marked as 0 (In the preamble) to ensure we exit the loop.
            // ChResult[x] is set to 0 at the beginning of the channel loop.
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, (UINT8) Byte);
          DataTrainFeedback.Data  = MrcReadCR (MrcData, Offset);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2u,", DataTrainFeedback.Bits.DataTrainFeedback);
          Pass                    = (DataTrainFeedback.Bits.DataTrainFeedback >= (UINT16) (1 << (NumSamples - 1)));
          if (Pass) {
            ChResult[Channel] |= (1 << Byte);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? "H " : "L ");
        }
        // Adjust Timing
        // If one byte is not at the Preamble yet, we're walking back 1 DCLK
        // The fall through to handle RcvEn correction for bytes in the preamble.
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          // Search in the appropriate Byte Range for x64 or x32 channels.
          ByteStart = ChannelOut->ByteStart[SubCh];
          ByteEnd   = ChannelOut->ByteEnd[SubCh];

          // Check if we have found all the preambles in the channel depending
          // on the channel mode.
          if (Outputs->EnhancedChannelMode) {
            SubChResults = ((1 << BytesPerSch) - 1);
            SubChResults = SubChResults << ByteStart;
            SubChResults &= ChResult[Channel];
            if (SubChResults == 0) {
              continue;
            }
          } else {
            // x64 mode
            if (ChResult[Channel] == 0) {
              continue;
            }
          }
#ifdef MRC_DEBUG_PRINT
          MinSchDelay[Channel][SubCh] -= RRE_DCLK_PI_VAL;
#endif // MRC_DEBUG_PRINT
          for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
            RcvEnTotPiDly[Channel][Rank][Byte] -= RRE_DCLK_PI_VAL;
          }
          for (KnobIdx = 0; KnobIdx < NumKnobs; KnobIdx++) {
            Status = mrcSuccess;
            GetSetVal = -RcvEnKnobPtr[KnobIdx].NumToEqualDclk;
            if (RcvEnKnobPtr[KnobIdx].Knob == RecEnDelay) {
              Byte = ByteStart;
              ByteStop = ByteEnd;
            } else {
              // Run the per-byte loop only once.
              Byte = MRC_IGNORE_ARG;
              ByteStop = Byte + 1;
            }
            for (; Byte < ByteStop; Byte++) {
              CurStatus = MrcGetSetDdrIoGroupSocket0Sch (
                            MrcData,
                            Channel,
                            SubCh,
                            Rank,
                            Byte,
                            MRC_IGNORE_ARG,
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
            // we break out of the knob loop to go to the next SubChannel.
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
            for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
              if ((ChResult[Channel] & (1 << Byte)) == 0) { // if byte is low
                GetSetVal = RRE_DCLK_PI_VAL;
                RcvEnTotPiDly[Channel][Rank][Byte] += RRE_DCLK_PI_VAL;
              Status = MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);

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
        } // SubCh
      } // for Channel
    } while ((ChResult[0] != 0) || (ChResult[1] != 0)); // while preamble not found on all bytes yet
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

#ifdef MRC_DEBUG_PRINT
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
    } // Channel
#endif // MRC_DEBUG_PRINT
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 4: Add 1 qclk to move closer to the first burst.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 4: Add 1qclk.\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }

      GetSetVal = RRE_QCLK_PI_VAL;
      // Update RcvEnDelay tracking.
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
          RcvEnTotPiDly[Channel][Rank][Byte] += RRE_QCLK_PI_VAL;
          Status = MrcGetSetDdrIoGroupStrobe (
            MrcData,
            Channel,
            Rank,
            Byte,
            RecEnDelay,
            WriteOffsetCached | PrintValue,
            &GetSetVal
            );
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
    PrintTotalDelay (MrcData, RcvEnTotPiDly);
    // STEP 5: Walk forward to find the first transaction edge.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Step 5: Walk forward to find rising edge\n");
    // Find Rising Edge
    ChResult[0] = 0;
    ChResult[1] = 0;

    for (Inc = 0; Inc < RRE_QCLK_PI_VAL; Inc += FineStep) {
      // Run Test
      RunIOTest (MrcData, ChBitMask, BasicVA, 1, OemReceiveEnable);

      // Update results for all Channel/bytes
      Done = 1;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Skip Bytes that are already done or Skip Bytes that don't exist.
          if ((ChResult[Channel] & (1 << Byte)) || (!MrcByteInChannelExist (MrcData, Channel, Byte))) {
            continue;
          }
          // Check if Byte is done defined by finding the high region of the first strobe.
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, (UINT8) Byte);
          Pass = (MrcReadCR (MrcData, Offset) >= (UINT8) (1 << (NumSamples - 1)));
          if (Pass) {
            ChResult[Channel] |= (1 << Byte);
            RcvEnTotPiDly[Channel][Rank][Byte] += Inc;
          } else {
            GetSetVal = FineStep;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);
            IncPreAmble[Channel][Byte] = Inc;
          }
        } // for Byte

        if (ChResult[Channel] != ChMask[Channel]) {
          Done = 0;
        }
      } // for Channel
      // Skip additional testing if all Channel/bytes done
      if (Done) {
        break;
      }
    }  // Inc
    MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChResult[0]: 0x%x\t[1]: 0x%x\n", ChResult[0], ChResult[1]);
    // Check if Edge was found for all Bytes in the channels
    if (!Done) {
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%s Pre-amble edge not found for all Bytes with following final RcvEn results\n",
        gErrString
        );

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %u Rank %u:  Preamble\n", Channel, Rank);
        MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // ChMask is 0 for bytes that don't exist, and ChResult is 0 by default.
          // Bytes that don't exist will never be set in ChResult.
          // Thus small code savings skipping ByteExists here.
          if (((ChResult[Channel] ^ ChMask[Channel]) & (1 << Byte)) != 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Check byte %u\n", gErrString, Byte);
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
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u:  Preamble Increment\n", Channel);

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
          // Place RecvEn in the middle of preamble - subtract 1 QCLK from the first strobe.
          GetSetVal = -PreamblePark;
          RcvEnTotPiDly[Channel][Rank][Byte] -= PreamblePark;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "B%u, IncPreAmble %d\n",
            Byte,
            IncPreAmble[Channel][Byte]
            );
        }
      }
      MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
    }

    // Clean up DDR4 read preamble mode and MPR mode
    //@todo: <CNL> Move behind MemoryApi.
    if (Ddr4) {
      MrcWait (MrcData, 150 * MRC_TIMER_1NS);  // Allow MC to close open pages using PRE
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        // Clear MPR mode in MC before sending MRS commands
        GetSetVal = 0;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteCached, &GetSetVal);
        // Disable DDR4 Read Preamble Training mode
        Ddr4Mr4.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR4];
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR4, Ddr4Mr4.Data);
        // Disable MPR mode
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        MrcWriteMRS (MrcData, Channel, RankMask, mrMR3, Ddr4Mr3.Data);
      }
    } // if DDR4
  } // END OF RANK LOOP

  // Clean up after Test
  if (Ddr4) {
    // Restore the bank mapping
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_SET);
    } // for Channel
  }

  GetSetVal = 0; // Disable Read Leveling Mode
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocReadLevelMode,  WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,    WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn,   WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,     WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);
  PrintTotalDelay (MrcData, RcvEnTotPiDly);

  // Step 7: Program RcvEn delays and Rx FIFO Timing.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nStep 7: Program RcvEn Delays and Rx FIFO Timing\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnSchRankMin, MAX_RANK_IN_CHANNEL * MAX_SUB_CHANNEL, MRC_INT32_MAX);
    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnSchRankMax, MAX_RANK_IN_CHANNEL * MAX_SUB_CHANNEL, 0);
    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnChRankMin, MAX_RANK_IN_CHANNEL, MRC_INT32_MAX);
    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnChRankMax, MAX_RANK_IN_CHANNEL, 0);
    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnSchMin, MAX_SUB_CHANNEL, MRC_INT32_MAX);
    MrcCall->MrcSetMemDword ((UINT32 *) RcvEnSchMax, MAX_SUB_CHANNEL, 0);
    RcvEnChMin  = MRC_INT32_MAX;
    RcvEnChMax  = 0;
    MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnMinMaxStr, gRcvEnBannerStr);
    ChannelOut = &ControllerOut->Channel[Channel];
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      // Find the min/max delay in two different scopes: SubChannel; SubChannel/Rank
      ByteStart = ChannelOut->ByteStart[SubCh];
      ByteEnd   = ChannelOut->ByteEnd[SubCh];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }

        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Ch%u.Sch%u.Rank%u\nTotalPiDelay:\n", Channel, SubCh, Rank);
        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          CurRcvEnTotPiDly  = RcvEnTotPiDly[Channel][Rank][Byte];
          MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, " B%u: %u\n", Byte, CurRcvEnTotPiDly);
          RcvEnChMin  = MIN (RcvEnChMin, CurRcvEnTotPiDly);
          RcvEnChMax  = MAX (RcvEnChMax, CurRcvEnTotPiDly);
          RcvEnChRankMin[Rank]  = MIN (RcvEnChRankMin[Rank], CurRcvEnTotPiDly);
          RcvEnChRankMax[Rank]  = MAX (RcvEnChRankMax[Rank], CurRcvEnTotPiDly);
          RcvEnSchMin[SubCh]    = MIN (RcvEnSchMin[SubCh], CurRcvEnTotPiDly);
          RcvEnSchMax[SubCh]    = MAX (RcvEnSchMax[SubCh], CurRcvEnTotPiDly);
          RcvEnSchRankMin[SubCh][Rank] = MIN (RcvEnSchRankMin[SubCh][Rank], CurRcvEnTotPiDly);
          RcvEnSchRankMax[SubCh][Rank] = MAX (RcvEnSchRankMax[SubCh][Rank], CurRcvEnTotPiDly);
        } // Byte
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Sch Rank Min: %d Max: %d\n", RcvEnSchRankMin[SubCh][Rank], RcvEnSchRankMax[SubCh][Rank]);
      } // Rank
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO,   "Sch      Min: %d Max: %d\n", RcvEnSchMin[SubCh], RcvEnSchMax[SubCh]);
    } // SubCh
    MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO,     "Ch       Min: %d Max: %d\n", RcvEnChMin, RcvEnChMax);

    // If we're x64 mode, set SubCh[Rank]X Min/Max to be the Min/Max across both SubCh
    if (!Outputs->EnhancedChannelMode) {
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Overriding Sch Min/Max to Ch Min/Max for x64 mode\n");
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        RcvEnSchMin[SubCh]  = RcvEnChMin; //Align SchDelta calculation between SubChannels.
        RcvEnSchMax[SubCh]  = RcvEnChMax; //Align SchDelta calculation between SubChannels.
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          RcvEnSchRankMin[SubCh][Rank] = RcvEnChRankMin[Rank];
          RcvEnSchRankMax[SubCh][Rank] = RcvEnChRankMax[Rank];
        }
      }
    }

    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      ByteStart = ChannelOut->ByteStart[SubCh];
      ByteEnd   = ChannelOut->ByteEnd[SubCh];
      // Get RxDqDataValidDclk Delay for RoundTrip and RdDataValid alignment
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxDqDataValidDclkDelay, ReadFromCache, &RxDataValidDclk);

      // Check to see if there is enough delay in the lower scope knobs to satisfy this delay.
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnSchCalcStr, gRcvEnBannerStr);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "SubChannel %d\n", SubCh);
      SchDelta  = RcvEnSchMax[SubCh] - RcvEnSchMin[SubCh];
      HeadRoom  = RcvEnPiMaxLimit + (RxFlyByMaxLimit * RxFlybyDelPiVal);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  SchDelta: %d\n  HeadRoom: %d\n", SchDelta, HeadRoom);
      HeadRoom -= SchDelta;
      if (HeadRoom < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Not enough headroom to handle the delta. HeadRoom = %d\n", gErrString, HeadRoom);
        if (Inputs->ExitOnFailure) {
          return mrcReadLevelingError;
        }
        HeadRoom = 0;
      }
      // Reserve Rank and Strobe delay.
      RnkPiRsv  = MIN (HeadRoom, RRE_PI_IDEAL);
      MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  HeadRoom after Delta: %d\n  Pi Reserved: %d\n", HeadRoom, RnkPiRsv);

      // Determine the Channel/SubChannel RcvEn DCLK Delay from the smallest RcvEn.
      // Program Rx FIFO Ready to match.
      SchDel      = RcvEnSchMin[SubCh] - RnkPiRsv;
      SchDelayClk = SchDel / RxIoTclPiVal;
      GetSetVal   = SchDelayClk;
      Status      = MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxIoTclDelay, WriteCached | PrintValue, &GetSetVal);
      GetSetVal   = GetSetVal + (RCVEN_FIFO_DELAY + FIFO_GUARD_BAND);
      RxFifoDelay = GetSetVal;
      CurStatus   = MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, WriteCached | PrintValue, &GetSetVal);
      if (Inputs->ExitOnFailure && ((Status != mrcSuccess) || (CurStatus != mrcSuccess))) {
        return mrcReadLevelingError;
      }

      // Calculate the delay consumed in the Sch scope.
      SchDel  = SchDelayClk * RxIoTclPiVal;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnRankCalcStr, gRcvEnBannerStr);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Rank %d\n", Rank);

        // Check to see if there is enough delay in the lower scope knobs to satisfy this delay.
        RnkStrbDel  = RcvEnSchRankMin[SubCh][Rank] - SchDel;
        RnkDelta    = RcvEnSchRankMax[SubCh][Rank] - RcvEnSchRankMin[SubCh][Rank];
        // We reduce the headroom by the remainder that cannot be programmed into the Rank Delay, and the PI to reserve for other training
        HeadRoom    = RcvEnPiMaxLimit - (RnkStrbDel % RxFlybyDelPiVal);// - RRE_PI_TO_RESERVE;
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "  Rank Delta: %d\n  HeadRoom: %d\n", RnkDelta, HeadRoom);
        HeadRoom   -= RnkDelta;
        if (HeadRoom < 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Not enough headroom to handle the delta. HeadRoom = %d\n", gErrString, HeadRoom);
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        // Determine the Rank RcvEn DCLK Delay from the smallest RcvEn Rank/Byte delay.
        RnkDelClk   = RcvEnSchRankMax[SubCh][Rank] + RcvEnSchRankMin[SubCh][Rank] - (SchDel * 2);
        RnkDelClk   = UDIVIDEROUND (RnkDelClk, 2);
        RnkDelClk  -= RRE_PI_IDEAL;
        RnkDelClk   = RnkDelClk / RxFlybyDelPiVal;
        GetSetVal   = RnkDelClk;
        Status = MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFlybyDelay, WriteCached | PrintValue, &GetSetVal);
        // FIFO delay needs to account for the longest RcvEn Delay in this SubCh/Rank (x32) or Ch/Rank (x64)
        RxFifoRdEnRankVal = RcvEnSchRankMax[SubCh][Rank] - SchDel;
        RxFifoRdEnFlyby = DIVIDECEIL(RxFifoRdEnRankVal, RxFifoRdEnRankDlyInPi); // FifoRdEn needs to be at the latest Byte in the rank.
        CurStatus = MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, WriteCached | PrintValue, &RxFifoRdEnFlyby);
        if ((Status != mrcSuccess) || (CurStatus != mrcSuccess)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Parameter saturation: RxFlybyDelay=%s\tRxFifoRdEnFlybyDelay=%s\n", gMrcStatusStr[Status], gMrcStatusStr[CurStatus]);
          if (Inputs->ExitOnFailure) {
            return mrcReadLevelingError;
          }
        }

        // Calculate Roundtrip Latency
        // RoundTrip = RxFifoDelay [QCLK] + RxDataValidDclk + CmdToRxFifoRdEnConst + (Lpddr4 ? 6 : 0) + (Ddr4 ? 4 : 0)
        Data32 = (UINT32) RxFifoDelay * 2;  // Convert to QCLK
        Data32 += (((UINT32) RxFifoRdEnFlyby) * (Gear2 + 1));
        Data32 += ((UINT32) RxDataValidDclk * 2); // Convert to QCLK
        if (Lpddr4) {
          Data32 += 8;
          Data32 = DIVIDECEIL (Data32, Gear2 + 1);
          Data32 += (Gear2 ? 3 : 5);
        } else { // DDR4
          if (!Gear2) {
            Data32 += 7;
          }
          Data32 += 2 * (2 - Gear2);                // Gear1: 3N mode (add 2 DCLKs), Gear2: 2N mode (add 1 DCLK)
          Data32 = DIVIDECEIL (Data32, Gear2 + 1);
          Data32 += (Gear2 ? 6 : 0);
        }
        Roundtrip = Data32;

        if (Outputs->EnhancedChannelMode) {
          // For each SubCh, we need to set RoundTrip when Enhanced Channel Mode.
          CurStatus = MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay, WriteCached | PrintValue, &Roundtrip);
        } else if (SubCh == 1) {
          // If we're not Enhanced Channel Mode, we only need to write Sub Channel 0.
          // We will go through both Sub Channels to get the maximum Receive Enable delay across all bytes within the rank.
          CurStatus = MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, Rank, RoundTripDelay, WriteCached | PrintValue, &Roundtrip);
        }

        // Determine the delay programmed in the Sch/Rank knobs above and then program the rest in the Strobe.
        SchRnkDelay = SchDel + (RnkDelClk * RxFlybyDelPiVal);
        MRC_RCVEN_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "\n%s\n%s\n%s\n", gRcvEnBannerStr, gRcvEnByteProgStr, gRcvEnBannerStr);
        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          GetSetVal = RcvEnTotPiDly[Channel][Rank][Byte] - SchRnkDelay;
          Status = MrcGetSetDdrIoGroupSocket0Sch (MrcData, Channel, SubCh, Rank, Byte, 0, RecEnDelay, WriteCached | PrintValue, &GetSetVal);
          if (Status != mrcSuccess) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Parameter saturation: RecEnDelay=%s\n", gMrcStatusStr[Status]);
            if (Inputs->ExitOnFailure) {
              return mrcReadLevelingError;
            }
          }
        } // Byte
      } // Rank
    } // SubCh
  } // Channel
  MrcFlushRegisterCachedData (MrcData);

  // Make sure we turn on/off the Odt/Samp at the correct time, based on RX flyby
  UpdateSampOdtTiming (MrcData, 1);

  // Print IO Latency/RcvEn
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusted Receive Enable Settings.\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d.R%d:\n", Channel, Rank);
          MRC_PRINT_DDR_IO_GROUP (MrcData, SOCKET_0, Channel, Rank, MAX_SDRAM_IN_DIMM, MRC_IGNORE_ARG, MRC_IGNORE_ARG, RecEnDelay);
        }
      }
    }
  }
#endif

  // Move the common part of RxFifoFlyby (Subch/Rank) into RxFifo (Subch)
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nOptimize RxFifoFlyby into RxFifo\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      CommonFlyby = MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MAX;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "[C%d Sch%d]\n", Channel, SubCh);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel) != 0) {
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, ReadFromCache | PrintValue, &RxFifoRdEnFlyby);
          CommonFlyby = MIN (CommonFlyby, RxFifoRdEnFlyby);
        }
      } // for Rank

      if (CommonFlyby > 1) {
        FifoDelta = (INT32) CommonFlyby / (2 - (INT32) Gear2);
        FlybyDelta = -((INT32) FifoDelta * (2 - (INT32) Gear2));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CommonFlyby: %lld, FifoDelta: %lld, FlyByDelta: %lld\n", CommonFlyby, FifoDelta, FlybyDelta);
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MAX_RANK_IN_CHANNEL, RxFifoRdEnFlybyDelay, WriteOffsetCached | PrintValue, &FlybyDelta);
        MrcGetSetDdrIoGroupChSch    (MrcData, Channel, SubCh,                      RxFifoRdEnTclDelay,   WriteOffsetCached | PrintValue, &FifoDelta);
      }
    } // for SubCh
  } // for Channel

  // Disable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteCached, &GetSetDis);

  Status = IoReset (MrcData);

  return Status;
}

/**
  Program the common FifoRdEn per Subch, across all ranks.
  Compensate using FifoRdEnFlyby per rank.

  @param[in] MrcData          - all the global data
  @param[in] FifoRdEnMin      - Array of minimum FifoRdEn values across all ranks, per ch/subch
  @param[in] FifoRdEnTrained  - Array of trained FifoRdEn values per rank/ch/subch

  @retval mrcSuccess - if GetSet operations succeeded
**/
MrcStatus
MrcSetCommonFifoRdEn (
  IN  MrcParameters *const MrcData,
  IN  INT64     FifoRdEnMin[MAX_CHANNEL][MAX_SUB_CHANNEL],
  IN  INT64     FifoRdEnTrained[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SUB_CHANNEL]
  )
{
  MrcStatus Status;
  MrcOutput *Outputs;
  UINT8     Channel;
  UINT32    SubCh;
  INT32     Gear2;
  UINT8     Rank;
  INT64     FifoDelta;
  INT64     FlybyDelta;

  Outputs = &MrcData->Outputs;
  Status  = mrcSuccess;
  Gear2   = Outputs->Gear2 ? 1 : 0;

  MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "\nProgram FifoRdEn per Subch\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          // Program the minimal FifoRdEn value across all ranks, and adjust FlyBy per rank if needed
          Status = MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, WriteCached | PrintValue, &FifoRdEnMin[Channel][SubCh]);
          if (Status != mrcSuccess) {
            return Status;
          }
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              FifoDelta = FifoRdEnTrained[Rank][Channel][SubCh] - FifoRdEnMin[Channel][SubCh];
              if (FifoDelta != 0) {
                FlybyDelta = (2 - Gear2) * (INT32) FifoDelta;
                Status = MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, WriteOffsetCached | PrintValue, &FlybyDelta);
                if (Status != mrcSuccess) {
                  return Status;
                }
              }
            }
          } // for Rank
        }
      } // for SubCh
    }
  } // for Channel
  return Status;
}

/**
  Optimize the Roundtrip Latency in MC.

  @param[in] MrcData - all the global data

  @retval mrcSuccess - if the training step succeeded
**/
MrcStatus
MrcRoundTripLatency (
  IN     MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcStatus Status;
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  MrcDebug  *Debug;
  INT64     tRDRDdr;
  INT64     tRDRDdd;
  INT64     GetSetVal;
  INT64     FifoRdEnOrig[MAX_CHANNEL][MAX_SUB_CHANNEL];
  INT64     FifoRdEnTrained[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SUB_CHANNEL];
  INT64     FifoRdEnMin[MAX_CHANNEL][MAX_SUB_CHANNEL];
  INT8      ClkShifts[1];
  INT8      DeltaLimitRtl;
  INT8      Start;
  INT8      Stop;
  UINT8     Channel;
  UINT32    SubCh;
  UINT8     Rank;
  UINT8     OptParam;
  UINT8     RankMask;
  UINT8     TestList[1];
  UINT8     RtLatency[MAX_RANK_IN_CHANNEL];
  UINT8     LoopCount;
  UINT8     Update;
  UINT8     MaxRankRtl;
  UINT8     DeltaRtl;
  UINT8     FifoRecovery;
  UINT8     Guardband;
  UINT32    PrintMode;
  BOOLEAN   Ddr4;
  TrainingModeType  TrainingModeBackup;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  Status        = mrcSuccess;
  TestList[0]   = RdT;        // Test based on read eye width
  ClkShifts[0]  = MRC_RTL_CLK_SHIFT;  // Delay by 25 PI ticks to guardband for delay drift/jitter
  LoopCount     = 10;
  Update        = 1;          // Apply the optimal settings
  OptParam      = rtl;        // Which parameter to optimize for
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  FifoRecovery  = RCVEN_FIFO_DELAY + FIFO_GUARD_BAND + (Outputs->Gear2 ? 0 : 5);
  PrintMode     = 0;          // Set to PrintValue for debug

  // LPDDR4 should have a guardband for tDQSCK drift
  Guardband = Ddr4 ? 0 : 1;

  MrcCall->MrcSetMem ((UINT8 *) FifoRdEnMin, sizeof (FifoRdEnMin), 0);

  // Disable margin training mode to keep the correct UPM limits for this routine
  TrainingModeBackup = Inputs->PowerTrainingMode;
  Inputs->PowerTrainingMode = MrcTmPower;

  // Capture the original FifoRdEn per Subch
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, ReadFromCache | PrintMode, &FifoRdEnOrig[Channel][SubCh]);
          FifoRdEnMin[Channel][SubCh] = MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MAX;
        }
      } // for SubCh
    }
  } // for Channel

  // Train timing separately for each rank
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RtLatency[Rank] = 0;
    RankMask = 1 << Rank;
    if ((RankMask & Outputs->ValidRankMask) == 0) {
      continue;
    }
    // Pick starting and stopping points
    Stop  = 0;
    Start = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) != 0) {
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay, ReadFromCache | PrintMode, &GetSetVal);
            if (Stop < (UINT8) GetSetVal) {
              Stop = (UINT8) GetSetVal;
            }
          }
        } // for SubCh
      }
    } // for Channel

    Start = Stop - FifoRecovery;
    Start = MAX (0, Start);
    // Find optimal Roundtrip Latency for this rank
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
              Guardband
              );
    if (Status != mrcSuccess) {
      return mrcRoundTripLatencyError;
    }
    // Capture the trained FifoRdEn for this rank and restore original FifoRdEn to train the next rank
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, ReadFromCache | PrintMode, &FifoRdEnTrained[Rank][Channel][SubCh]);
            MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, WriteCached   | PrintMode, &FifoRdEnOrig[Channel][SubCh]);
            // Find the minimal FifoRdEn for this ch/subch, across all ranks
            FifoRdEnMin[Channel][SubCh] = MIN (FifoRdEnMin[Channel][SubCh], FifoRdEnTrained[Rank][Channel][SubCh]);
          }
        } // for SubCh
      }
    } // for Channel
  } // for Rank

  // Program the common FifoRdEn per Subch, across all ranks
  Status = MrcSetCommonFifoRdEn (MrcData, FifoRdEnMin, FifoRdEnTrained);
  if (Status != mrcSuccess) {
    return mrcRoundTripLatencyError;
  }

  // Limit the RTL delta across the ranks, taking Read turnaround into account, per channel
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nLimit the delta between Rank's RTL value\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MaxRankRtl = 0;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache, &tRDRDdr);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, ReadFromCache, &tRDRDdd);
    DeltaLimitRtl = MIN ((INT8) tRDRDdr, (INT8) tRDRDdd);
    // Turnaround times are in tCK. Roundtrip is in QCLK (both Gear1 and Gear2).
    // Must convert to QCLK and subtract the burst length (Outputs->BurstLength is in tCK)
    // Ensure we do not underflow the variable.
    DeltaLimitRtl = DeltaLimitRtl - Outputs->BurstLength;
    if (!Outputs->Gear2) {
      // G1: tCK = 2 * QCLK
      // G2: tCK = QCLK
      DeltaLimitRtl = 2 * DeltaLimitRtl;
    }
    DeltaLimitRtl = MAX (DeltaLimitRtl, 0);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RTL Delta Limit: %d\n", DeltaLimitRtl);

    // Get the current Roundtrip values per rank and find the MAX value for this channel
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        FifoRdEnMin[Channel][SubCh] = MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MAX;  // Reset the MIN value
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay, ReadFromCache, &GetSetVal);
            RtLatency[Rank] = (UINT8) GetSetVal;
            MaxRankRtl = MAX (MaxRankRtl, RtLatency[Rank]);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " SubCh%d R%d RTL: %d\n", SubCh, Rank, RtLatency[Rank]);
          }
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MaxRankRtl: %u\n", MaxRankRtl);

    // Decrease the roundtrip difference between the ranks if it exceeds DeltaLimitRtl
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
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
              if (!Ddr4 || (SubCh == 0)) {  // Use only Subch0 for DDR4
                UpdateTAParamOffset (MrcData, Channel, (1 << SubCh), 0, OptParam, (INT8) MaxRankRtl - DeltaLimitRtl, 1, MRC_PRINTS_ON, 1 << Rank);
              }
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
            // Capture the trained FifoRdEn for this rank
            MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, RxFifoRdEnTclDelay, ReadFromCache | PrintMode, &FifoRdEnTrained[Rank][Channel][SubCh]);
            // Find the minimal FifoRdEn for this ch/subch, across all ranks
            FifoRdEnMin[Channel][SubCh] = MIN (FifoRdEnMin[Channel][SubCh], FifoRdEnTrained[Rank][Channel][SubCh]);
          }
        } // for Rank
      }
    } // for SubCh
  } // for Channel

  // Program the common FifoRdEn per Subch, across all ranks
  Status = MrcSetCommonFifoRdEn (MrcData, FifoRdEnMin, FifoRdEnTrained);

  // Clean up
  Inputs->PowerTrainingMode = TrainingModeBackup;

  return Status;
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

  return DQTimeCentering1D (MrcData, MrcData->Outputs.ValidChBitMask, RcvEnaX, 0, LoopCount, TRUE, FALSE);
}
