/** @file
  These functions implement the crosser training algorithm.

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
#include "MrcCrosser.h"
#include "MrcWriteDqDqs.h"
#include "MrcReadDqDqs.h"
#include "MrcCommon.h"
#include "MrcMcConfiguration.h"
#include "MrcCpgcApi.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcMemoryApi.h"
#include "MrcCpgcOffsets.h"
#include "Cpgc20TestCtl.h"

#if SUPPORT_SODIMM == SUPPORT
#include "MrcSpdProcessing.h"
#endif //SUPPORT_SODIMM == SUPPORT


/// Module Definitions
#define DIMM_ODT_DIMM_MASK_SHIFT  (4)

/// Power optimizations Global Parameters
#define OPT_PARAM_LOOP_COUNT (15)
#define OPT_PARAM_1D_LC      (15)

/// UPM/PWR increment value if margins are at or below the retrain limit.
#define MRC_UPM_PWR_INC_VAL (80)

/// Vref step size for the following: DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
#define MRC_COMP_VREF_STEP_SIZE   (192)

/// SenseAmplifier Wake-Up Time in pS
#define MRC_SENSE_AMP_WAKEUP_TIME (2000)

/// SOT Spacing Macro
///   GroupIdx | Spaces | Trained
///   ---------|--------|-------------
///      0     |   9    | 8 DQs, 1 DQS
///      1     |   8    | 8 DQs
///      2     |   1    | 1 DQS
#define MRC_SOT_BIT_SPACE(x) (((x) == 0) ? ("         ") : (((x) == 1) ? ("        ") : (" ")))

/// We need to make one of the bits in the combined Scomp value the PC bit value. It can be any bit as long as we always use the same one everywhere, and don't overwrite any bits used to store the SComp values.
/// The combined Scomp value is split back into individual PC and Scomp values before being written to registers using the get/set methods.
#define SCOMP_PC_STORAGE_BIT_OFFSET (4)

// Param step sizes
#define TCO_COMP_STEP (7)
#define CLK_TCO_COMP_STEP (2)
#define VDDQ_STEP (4)
#define WR_DS_STEP (4)
#define CCC_DS_STEP (2)
#define RX_BIAS_STEP (2)
#define RX_LOAD_STEP (2)

// Adjustments to line up 0 ticks with 0 volts
#define VDDQ_BASE_TICKS (0) // Supposedly zero, documentation does not say for certain.
#define RXVREF_BASE_TICKS (0) // Supposedly zero, documentation does not say for certain. 0-381. Step size is Vddxx/382
#define DDR4_CMDVREF_BASE_TICKS (0) // Supposedly zero, documentation does not say for certain. 0-381. Step size is Vddxx/382
#define DDR4_TXVREF_BASE_TICKS (69) // 45% at 0.65% per tick
#define LP4_CMDVREF_BASE_TICKS (25) // 15% at 0.6% per tick
#define LP4_TXVREF_BASE_TICKS (25) // 15% at 0.6% per tick
// TGL_POWER_TRAINING - Update for DDR5. Also check if DDR5 ODT types, value ranges, and RZQ value has changed at all.
//#define DDR5_CMDVREF_BASE_TICKS (?)
//#define DDR5_TXVREF_BASE_TICKS (?)
// TGL_POWER_TRAINING - Update for LPDDR5 depending on manufacturer spec
#define LP5_CMDVREF_BASE_TICKS (20) // Samsung has 15% at 0.5% per tick, JEDEC spec has 10%
#define LP5_TXVREF_BASE_TICKS (20) // Samsung has 15% at 0.5% per tick, JEDEC spec has 10%

// Number of read-write command margin failures.
#define NUM_RW_CMD_MARGIN_FAILURES (3)

// CCC margins are twice as large.
#define MAX_CCC_POSSIBLE_TIME (MAX_POSSIBLE_TIME * 2)

/// Module Globals
GLOBAL_REMOVE_IF_UNREFERENCED const MrcUpmPwrRetrainLimits  InitialLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS] = {
  //           UPM,     PWR      Retrain
  {RdT,       {240,     320,     90 }},
  {WrT,       {240,     320,     90 }},
  {RdV,       {400,     520,     160}},
  // For ULT DDR3L rcF the values are increased by 20 ticks, see MrcGetUpmPwrLimit()
  {WrV,       {400,     520,     160}},
  {RdFan2,    {240,     480,     0  }},
  {WrFan2,    {240,     480,     0  }},
  {RdFan3,    {(240*4)/5, (480*4)/5, 0}},
  {WrFan3,    {(240*4)/5, (480*4)/5, 0}},
  // {650ps,750ps} * 64 pi ticks * 2 (for width) = 134 PI Ticks ->  ~1.3nsec for UPM, 154 PI Ticks -> ~1.5nsec for PWR
  // Margin function works in steps of 4, so we divide the margin by 4.
  // Margin numbers are scaled by 10.
  {RcvEnaX,   {((134 * 10) / 4), ((154 * 10) / 4), 0}},
  {CmdT,       {240,     320,     180 }}, // CCC retrain limit is around twice what data is, as margins are +-64 instead of +-32 (Data is DDR, CLK is not)
  {CmdV,       {400,     520,     160}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const MrcOptParamsLimits  MrcOptParamLimit[MRC_NUMBER_OPT_PARAMS_TRAIN] = {
  //            Normal/SAGV(high), SAGV (low), DT/Halo (max perf.)
  // Use full range for now, optimize postsilicon
  {OptRdOdt,          {-15,  15}, {-15,  15}, {-5,   10}},
  {OptRdDqOdt,        {-15,  15}, {-15,  15}, {-5,   10}},
  {OptRdDqsOdt,       {-15,  15}, {-15,  15}, {-5,   10}},
  {OptRxBias,         {0,     7}, {0,     7}, {0,     7}}, // Max 15, setting to 14 max (step size 2) to ensure less than 256 combinations
  {OptRxLoad,         {-8,    7}, {-8,    7}, {-8,    7}},
  {OptRxCb,           {0,    15}, {0,    15}, {0,    15}},
  {OptRxEq,           {0,    15}, {0,    15}, {0,    15}},
  {OptTxEq,           {0,    10}, {0,    10}, {0,    10}},
  {OptWrDS,           {-15,  15}, {-11,   0}, {-9,   10}},
  {OptWrDSDnCoarse,   {-3,    1}, {-3,    1}, {-2,    2}}, // Max is 7, min is -8 (step size of 4)
  {OptWrDSUpCoarse,   {-3,    1}, {-3,    1}, {-2,    2}}, // Max is 7, min is -8 (step size of 4)
  {OptSComp,          {-15,   5}, {-15,   5}, {-15,  10}},
  {OptClkTco,         {0,    31}, {0,    31}, {0,    31}},
  {OptTxDqTco,        {0,     9}, {0,     9}, {0,     9}},
  {OptTxDqsTco,       {0,     9}, {0,     9}, {0,     9}},
  {OptTCompOff,       {-15,  15}, {-15,  15}, {-15,  15}},
  {OptVddq,           {0,    30}, {0,    20}, {0,    10}},
  {OptCmdTxEq,        {0,    14}, {0,    14}, {0,    14}}, // Max 15, setting to 14 for now to ensure less than 256 combinations
  {OptCmdDS,          {-8,    7}, {-8,    7}, {-8,    7}},
  {OptCmdDSDnCoarse,  {-4,    3}, {-4,    3}, {-4,    3}},
  {OptCmdDSUpCoarse,  {-4,    3}, {-4,    3}, {-4,    3}},
  {OptCCCSComp,       {-8,    7}, {-8,    7}, {-8,    7}},
  {OptVccDLLBypass,   {0,     1}, {0,     1}, {0,     1}},
  {OptRxVrefVttDecap, {0,     7}, {0,     7}, {0,     7}},
  {OptRxVrefVddqDecap,{0,     7}, {0,     7}, {0,     7}},
  {OptDFETap0,        {0,    15}, {0,    15}, {0,    15}},
  {OptDFETap1,        {0,    15}, {0,    15}, {0,    15}},
  {OptRxC,            {0,     3}, {0,     3}, {0,     3}},
  {OptRxR,            {0,     3}, {0,     3}, {0,     3}},
  {OptPanicVttDnLp,   {0,    15}, {0,    15}, {0,    15}}
};

// DDR Params encoding
#ifdef MRC_DEBUG_PRINT
GLOBAL_REMOVE_IF_UNREFERENCED const char  *TOptParamOffsetString[] = {
  "WrDS",
  "Vddq",
  "SComp",
  "TxDqTCoComp",
  "TxDqsTCoComp",
  "ClkTCoComp",
  "TxTCoCompoff",
  "TxEq",
  "RdOdt",
  "RdDqOdt",
  "RdDqsOdt",
  "RxEq",
  "RxBias",
  "RxLoad",
  "RxCb",
  "DimmOdt",
  "DimmOdtWr",
  "DimmOdtNom",
  "DimmOdtNomNT",
  "OptOdtPark",
  "OptOdtParkNT",
  "OptDimmOdtComb",
  "DimmOdtCa",
  "DimmRon",
  "WrDSUp",
  "WrDSDn",
  "WrDSUpCoarse",
  "WrDSDnCoarse",
  "RdOdtUp",
  "RdOdtDn",
  "CmdDS",
  "CmdDSUp",
  "CmdDSDn",
  "CtlDS",
  "ClkDS",
  "RxBiasCb",
  "TxEqWrDS",
  "DimmSocOdt",
  "CmdTxEq",
  "CmdDSDnCoarse",
  "CmdDSUpCoarse",
  "CmdTxEqCmdDS",
  "CCCSComp",
  "VccDLLBypass",
  "RxVrefVttDecap",
  "RxVrefVddqDecap",
  "DFETap0",
  "DFETap1",
  "RxC",
  "RxR",
  "PanicVttDnLp"
  "OptDefault",
  "Default"
};

/// These strings match the OptResultPerByteDbgStr enum for indexing
/// the switch PrintCalcResultTableCh and PrintODTResultTable.
const char *OptResultDbgStrings[] = {
  "Best",
  "GrdBnd",
  "OffSel",
  "Scale",
  "MaxPost",
  "MinPost"
};

// Strings for TGlobalCompOffset decoding
const char *GlobalCompOffsetStr[] = {
  "RdOdt",
  "WrDS",
  "WrDSCmd",
  "WrDSCtl",
  "WrDSClk"
};

// Strings for CompGlobalOffsetParam decoding
const char *CompGlobalOffsetParamStr[] = {
  "RdOdtUp",
  "RdOdtDn",
  "WrDSUp",
  "WrDSDn",
  "WrDSCmdUp",
  "WrDSCmdDn",
  "WrDSCtlUp",
  "WrDSCtlDn",
  "WrDSClkUp",
  "WrDSClkDn",
  "SCompDq",
  "SCompCmd",
  "SCompCtl",
  "SCompClk",
  "DisOdtStatic"
};

const char *OdtTypeString[] = {
  "RttWr",
  "RttNom",
  "RttPark",
  "RttMaxType"
};

const char  *CmdIterTypesString[] = {
  "MrcIterationClock",
  "MrcIterationCmd",
  "MrcIterationCtl"
};
#endif // MRC_DEBUG_PRINT

/**
  This function implements Sense Amp Offset training.
  The algorithm sweeps Per-Bit Vref Offset and parks the SenseAmpOffset
  at the "last 1" setting before transitions to 0.

  Algorithm will account for speckling, and consider the "last 1" after specling.

  @param[in,out] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeded return mrcSuccess
**/
MrcStatus
MrcSenseAmpOffsetTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MRC_RX_MODE_TYPE    RxModeSave;
  GSM_GT              DqSaGrp;
  GSM_GT              DqsSaGrp;
  INT64               GetSetVal;
  INT64               GetSetMax;
  INT64               GetSetMin;
  INT64               GetSetEn;
  INT64               GetSetDis;
  INT64               DataTrainFeedbackReg;
  UINT32              DataTrainFeedback;
  UINT32              SenseAmpTestDelay;
  UINT32              SdramCount;
  INT8                FirstZero[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];  // Additional bit for DQS per each byte
  INT8                LastOne[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];  // Additional bit for DQS per each byte
  INT8                SampOffset;
  INT8                Vref;
  INT8                MinValue;
  INT8                MaxValue;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               Bit;
  UINT8               GroupIdx;
  UINT8               MaxChannel;
  UINT8               MaxGrp;
  UINT8               MaxRank;
  UINT8               BitStart;
  UINT8               BitEnd;
  UINT8               BiasPMCtrl;
  UINT8               OrigRxTap0;
  UINT8               OrigRxTap1;
  UINT8               RankPresent[MAX_CONTROLLER][MAX_CHANNEL];
  BOOLEAN             Ddr4;
  BOOLEAN             Ddr5;
  BOOLEAN             Lpddr5;
  BOOLEAN             EnDqsN;
  BOOLEAN             CheckDqs;
  BOOLEAN             CheckDq;
  BOOLEAN             Unmatched;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  Status          = mrcSuccess;
  Ddr4            = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Ddr5            = (Outputs->DdrType == MRC_DDR_TYPE_DDR5);
  Lpddr5          = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);
  MaxRank         = MAX_RANK_IN_CHANNEL;
  MaxChannel      = Outputs->MaxChannels;
  SdramCount      = Outputs->SdramCount;
  RxModeSave      = Outputs->RxMode;
  GetSetEn        = 1;
  GetSetDis       = 0;
  BiasPMCtrl      = 0xFF;
  EnDqsN          = 0;
  OrigRxTap0      = 0;
  OrigRxTap1      = 0;
  SenseAmpTestDelay = MRC_TIMER_1US;
  MrcCall->MrcSetMem ((UINT8 *) RankPresent,  sizeof (RankPresent), 0xFF);


  for (Controller = 0; (Controller < MAX_CONTROLLER) && (BiasPMCtrl == 0xFF); Controller++) {
    for (Channel = 0; (Channel < MaxChannel) && (BiasPMCtrl == 0xFF); Channel++) {
      for (Byte = 0; Byte < SdramCount; Byte++) {
        if (MrcByteExist (MrcData, Controller, Channel, Byte)) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocBiasPMCtrl, ReadFromCache, &GetSetVal);
          BiasPMCtrl = (UINT8) GetSetVal;
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte , GsmIocEnDqsNRcvEn, ReadFromCache, &GetSetVal);
          EnDqsN = (GetSetVal == 1);
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxTap0, ReadFromCache, &GetSetVal);
              OrigRxTap0 = (UINT8) GetSetVal;
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxTap1, ReadFromCache, &GetSetVal);
              OrigRxTap1 = (UINT8) GetSetVal;
              break;
            }
          }
          break;
        }
      }
    }
  }

  Unmatched = (RxModeSave == MrcRxModeUnmatchedRxWRload) || (RxModeSave == MrcRxModeUnmatchedRxWPpath);
  if (Unmatched) {
    if (Lpddr5 && EnDqsN) {
      MaxGrp = 3;
    } else {
      MaxGrp = 2;
    }
  } else {
    MaxGrp = 1;
  }

  if (Unmatched) {
    //Disable DFE for SOT
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap0, WriteToCache, &GetSetDis);
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap1, WriteToCache, &GetSetDis);
  }

  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);
  GetSetVal = 1;
  // Need to ungate SOT
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  // Find first rank present.  Need to set Rank Mux to this rank for training.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          RankPresent[Controller][Channel] = Rank;
          break;
        }
      }
    }
  }

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteCached, &GetSetEn);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetEn);
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        GetSetVal = RankPresent[Controller][Channel];
        MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteNoCache, &GetSetVal);
      }
    }
  }

  for (GroupIdx = 0; GroupIdx < MaxGrp; GroupIdx++) {
    switch (GroupIdx) {
      case 0:
        // Matched or Unmatched.  Sweep DQ and DQS.
        CheckDqs = 1;
        CheckDq = 1;
        BitStart = 0;
        BitEnd = MAX_BITS_FOR_OFFSET_TRAINING;
        break;

      case 1:
        // Unmatched case.  Sweep only DQ.
        CheckDqs = 0;
        CheckDq = 1;
        BitStart = 0;
        BitEnd = MAX_BITS;
        break;

      case 2:
        // Unmatched with EnDqsN.  Sweep only DQS.
        // Must set RxMode to matched p to train.
        GetSetVal = MrcRxModeMatchedP;
        // This is needed because MrcGetSetLimits limits depend on if we are in matched or unmatched.
        Outputs->RxMode = MrcRxModeMatchedP;
        MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxVocMode,  WriteCached, &GetSetVal);
        CheckDqs = 1;
        CheckDq = 0;
        BitStart = MAX_BITS_FOR_OFFSET_TRAINING - 1;
        BitEnd = MAX_BITS_FOR_OFFSET_TRAINING;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid iteration index of SOT: %d\n", GroupIdx);
        return mrcFail;
    }

    // Only train the strobe SenseAmp Offset on the first pass.
    if (Ddr4 || Ddr5) {
      GetSetVal = 1;
      DqsSaGrp = RxDqsAmpOffset;
      DqSaGrp = RxVoc;
    } else if (!Unmatched) {
      GetSetVal = 0;
      DqsSaGrp = RxDqsAmpOffset;
      DqSaGrp = RxVoc;
    } else {
      // LPDDR Unmatched
      if (GroupIdx == 0) {
        DqsSaGrp = RxDqsUnmatchedAmpOffset;
        DqSaGrp = RxVoc;
        GetSetVal = 1;
      } else {
        DqsSaGrp = RxDqsAmpOffset;
        DqSaGrp = RxVocUnmatched;
        GetSetVal = 0;
      }
    }

    MrcGetSetLimits (MrcData, DqSaGrp, &GetSetMin, &GetSetMax, NULL);
    MinValue = (INT8) GetSetMin;
    MaxValue = (INT8) GetSetMax;

    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxAmpOffsetEn, WriteNoCache, &GetSetVal);

    // Init FirstZero and LastOne to 0
    MrcCall->MrcSetMem ((UINT8 *) FirstZero, sizeof (FirstZero), 0);
    MrcCall->MrcSetMem ((UINT8 *) LastOne, sizeof (LastOne), 0);

    // Print Controller header.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SampOffset Training:");
    if (CheckDq) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s,", GsmGtDebugStrings[DqSaGrp]);
    }
    if (CheckDqs) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", GsmGtDebugStrings[DqsSaGrp]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMC\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (!MrcControllerExist (MrcData, Controller)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", Controller);
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", MRC_SOT_BIT_SPACE (GroupIdx), ((Byte != (SdramCount -1) ? " " : "")));
        }
      }
    }
    // Print Channel Header.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nChannel\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", Channel);
        for (Byte = 0; Byte < SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s%s", MRC_SOT_BIT_SPACE (GroupIdx), ((Byte != (SdramCount -1) ? " " : "")));
        }
      }
    }
    // Print Byte Header
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d%s", Byte, MRC_SOT_BIT_SPACE (GroupIdx));
        }
      }
    }
    //Print Bit Header
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nBits\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          for (Bit = BitStart; Bit < BitEnd; Bit++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Bit == 8) ? "S" : "%d"), Bit);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
        }
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n SAmp");

    for (SampOffset = MinValue; SampOffset <= MaxValue; SampOffset++) {
      // Display per Byte Feedback from REUT Registers
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", SampOffset);
      // Clear out DataTrainFeedback field
      GetSetVal = 0;
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataTrainFeedback, WriteNoCache, &GetSetVal);

      // Program Offset
      GetSetVal = SampOffset;
      if (CheckDq) {
        MrcGetSetBit (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, DqSaGrp, WriteToCache, &GetSetVal);
      }
      if (CheckDqs) {
        MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, DqsSaGrp, WriteToCache, &GetSetVal);
      }
      MrcFlushRegisterCachedData (MrcData);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        if (!MrcControllerExist (MrcData, Controller)) {
          continue;
        }

        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MrcChannelExist (MrcData, Controller, Channel)) {
            continue;
          }

          MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteCached, &GetSetEn);
          MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteNoCache, &GetSetEn);
          MrcWait (MrcData, SenseAmpTestDelay);

          for (Byte = 0; Byte < SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocSenseAmpMode, WriteNoCache, &GetSetDis);
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackReg);
            DataTrainFeedback = (UINT32) DataTrainFeedbackReg;
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DataTrainFeedback.Bits.DataTrainFeedback = 0x%x, SampOffset = %d\n", DataTrainFeedback, SampOffset);

            for (Bit = BitStart; Bit < BitEnd; Bit++) {
              if (DataTrainFeedback & (MRC_BIT0 << Bit)) {
                LastOne[Controller][Channel][Byte][Bit] = SampOffset;
              } else {
                if (FirstZero[Controller][Channel][Byte][Bit] == 0) {
                  FirstZero[Controller][Channel][Byte][Bit] = SampOffset;
                }
              }
              // Display in bits
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                ((MRC_BIT0 << Bit) & DataTrainFeedback) ? "1" : "0"
              );
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
          } // for Byte
        } // for Channel
      } // for Controller
    } // for SampOffset
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nResults\n");

    // Calculate and Program Offsets and display per bit SenseAmp Offset
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (!MrcControllerExist (MrcData, Controller)) {
        continue;
      }
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        for (Byte = 0; Byte < SdramCount; Byte++) {
          for (Bit = BitStart; Bit < BitEnd; Bit++) {
            // Find Vref center, add 1 for Round Up
            Vref = (FirstZero[Controller][Channel][Byte][Bit] + LastOne[Controller][Channel][Byte][Bit]) / 2;

            // Check for saturation conditions
            // to make sure we are as close as possible to vih/2
            if (FirstZero[Controller][Channel][Byte][Bit] == 0) {
              Vref = MaxValue;
            }

            if (LastOne[Controller][Channel][Byte][Bit] == 0) {
              Vref = MinValue;
            }

            GetSetVal = Vref;
            if (Bit == 8) {
              MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, Byte, DqsSaGrp, WriteCached | PrintValue, &GetSetVal);
              break;
            }

            for (Rank = 0; Rank < MaxRank; Rank++) {
              if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
                continue;
              }
              ChannelOut->RxDqVrefPb[Rank][Byte][Bit].Center = Vref;
              MrcGetSetBit (MrcData, Controller, Channel, Rank, Byte, Bit, DqSaGrp, WriteCached | PrintValue, &GetSetVal);
            }
          } // for Bit
        } // for Byte
      } // for Channel
    } // for Controller
  } // SenseAmp Knob

  // Clean up after test.
  // Disable Senseamp Mode and ForceOdtOn mode.
  // Disable ForceOdtOn before ODT mode switch.
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteNoCache, &GetSetDis);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteCached, &GetSetDis);
  // Restore training mode if we were LP5 unmatched with EnDqsN set
  if (Unmatched && Lpddr5 && EnDqsN) {
    GetSetVal = RxModeSave;
    Outputs->RxMode = RxModeSave;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxVocMode,  WriteToCache, &GetSetVal);
  }

  if (Unmatched) {
    //Re-enable DFE after SOT
    GetSetVal = OrigRxTap0;
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap0, WriteToCache, &GetSetVal);
    GetSetVal = OrigRxTap1;
    MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap1, WriteToCache, &GetSetVal);
  }
  // Disable Rank Mux Override
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetDis);

  GetSetVal = BiasPMCtrl;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocBiasPMCtrl, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  Status = IoReset (MrcData);

  return Status;
}

/**
  This function looks at the margin values stored in the global data structure and checks
  WrT, WrV, RdT, and RdV to see if they are above the minimum margin required.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess - If margins are acceptable.
  @retval mrcRetrain - If margins are not acceptable.
**/
MrcStatus
MrcRetrainMarginCheck (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                *Debug;
  MrcOutput               *Outputs;
  MRC_FUNCTION            *MrcCall;
  MRC_MarginTypes         MarginParam;
  MrcMarginResult         LastResultParam;
  MrcStatus               Status;
  MRC_MARGIN_LIMIT_TYPE   MarginLimitType;
  UINT16                  (*LastMargins)[MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                  BERStats[4];
  UINT16                  MinEdgeMargin[MAX_EDGES];
  UINT16                  RetrainMarginLimit;
  UINT16                  CurrentMargin;
  UINT8                   Controller;
  UINT8                   Channel;
  UINT8                   McChMask;
  UINT8                   Rank;
  UINT8                   RankMask;
  UINT8                   Edge;
  UINT8                   Loopcount;
  UINT8                   MaxMargin;
  BOOLEAN                 RdWrCmdMarginFail[NUM_RW_CMD_MARGIN_FAILURES];

  MrcCall             = MrcData->Inputs.Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  LastMargins         = Outputs->MarginResult;
  Status              = mrcSuccess;
  Loopcount           = 17;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) RdWrCmdMarginFail, sizeof (RdWrCmdMarginFail), FALSE);
  MaxMargin         = 0;
  // Loop is dependent on the order of MRC_MarginTypes.  If this changes, please ensure functionality
  // stays the same.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Loopcount: %d\n", Loopcount);
  // @todo Update with McChBitMask
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, Loopcount, NSOE, 0, 0, 8, PatWrRd, 0, 0);
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      RankMask    = MRC_BIT0 << Rank;
      McChMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        McChMask |= SelectReutRanks (MrcData, Controller, Channel, RankMask, FALSE, 0);
      }

      if (McChMask == 0) {
        continue;
      }

      for (MarginParam = RdT; MarginParam <= CmdV; MarginParam++) {
        switch (MarginParam) {
          case CmdT:
          case RdT:
          case WrT:
            Outputs->DQPat = RdRdTA;
            MaxMargin = (CmdT == MarginParam) ? MAX_CCC_POSSIBLE_TIME : MAX_POSSIBLE_TIME;
            break;

          case CmdV:
          case RdV:
          case WrV:
            Outputs->DQPat = BasicVA;
            MaxMargin = GetVrefOffsetLimits (MrcData, MarginParam);
            break;

          default:
            // Skip margin parameter.
            continue;
        }

        Status = MrcGetBERMarginCh (
          MrcData,
          LastMargins,
          McChMask,
          RankMask,
          RankMask,
          MarginParam,
          0,
          1,
          MaxMargin,
          0,
          BERStats
          );
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Margins\nParams: RdT\tWrT\tRdV\tWrV\tCmdT\tCmdV\n\tLft Rgt Lft Rgt Low Hi  Low Hi  Lft Rgt Low Hi");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCo%uCh%uRa%u\t", Controller, Channel, Rank);
        for (MarginParam = RdT; MarginParam <= CmdV; MarginParam++) {
          if (MarginParam != RdT && MarginParam != RdV && MarginParam != WrT && MarginParam != WrV && MarginParam != CmdT && MarginParam != CmdV) {
            continue;
          }

          LastResultParam     = GetMarginResultType (MarginParam);
          RetrainMarginLimit  = MrcGetUpmPwrLimit (MrcData, MarginParam, RetrainLimit) / 10;
          MrcCall->MrcSetMemWord (MinEdgeMargin, MAX_EDGES, (UINT16) (~0));

          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            CurrentMargin       = LastMargins[LastResultParam][Rank][Controller][Channel][0][Edge] / 10;
            MinEdgeMargin[Edge] = MIN (MinEdgeMargin[Edge], CurrentMargin);
            if ((CurrentMargin <= RetrainMarginLimit)) {
              Status =  mrcRetrain;
              if ((MarginParam == RdT) || (MarginParam == RdV)) {
                RdWrCmdMarginFail[0] = TRUE;
              } else if ((MarginParam == WrT) || (MarginParam == WrV)) {
                RdWrCmdMarginFail[1] = TRUE;
              } else if ((MarginParam == CmdT) || (MarginParam == CmdV)) {
                RdWrCmdMarginFail[2] = TRUE;
              }
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2d  %2d\t", MinEdgeMargin[0], MinEdgeMargin[1]);
          if ((RdWrCmdMarginFail[0] == TRUE) && (RdWrCmdMarginFail[1] == TRUE) && (RdWrCmdMarginFail[2] == TRUE)) {
            Rank    = MAX_RANK_IN_CHANNEL;
            Channel = MAX_CHANNEL;
            break;
          }
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table

  if (Status == mrcRetrain) {
    // Loop is dependent on the order of MRC_MarginTypes.  If this changes, please ensure functionality
    // stays the same.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** Margin Limit Check Failed! ***\nNew Limits:\nParam\tUPM\tPWR");
    for (MarginParam = RdT; MarginParam <= CmdV; MarginParam++) {
      if (((RdWrCmdMarginFail[0] == FALSE) && ((MarginParam == RdT) || (MarginParam == RdV))) ||
          ((RdWrCmdMarginFail[1] == FALSE) && ((MarginParam == WrT) || (MarginParam == WrV))) ||
          ((RdWrCmdMarginFail[2] == FALSE) && ((MarginParam == CmdT) || (MarginParam == CmdV))) ||
          (MarginParam != RdT && MarginParam != RdV && MarginParam != WrT && MarginParam != WrV && MarginParam != CmdT && MarginParam != CmdV)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s", gMarginTypesStr[MarginParam]);
      for (MarginLimitType = UpmLimit; MarginLimitType < RetrainLimit; MarginLimitType++) {
        RetrainMarginLimit = MrcUpdateUpmPwrLimits (MrcData, MarginParam, MarginLimitType, MRC_UPM_PWR_INC_VAL);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", RetrainMarginLimit);
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table.
  }

  return Status;
}

/**
  Force OLTM (Open Loop Thermal Management) on Hynix DDR4 DRAMs before ww45'2015.
  Only applied for 2DPC.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcForceOltm (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcSpd            *SpdIn;
  MrcStatus         Status;
  UINT16            DateCode;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;
  BOOLEAN           UpdateNeeded;
  UINT32            Offset;
  SPD4_MANUFACTURING_DATA              *ManufactureData;
  MC0_CH0_CR_SCHED_SECOND_CBIT_STRUCT  SchedSecondCbit;
  MC0_CH0_CR_MCMNTS_SPARE_STRUCT       McmntsSpare;
  MC0_CH0_CR_DDR_MR_PARAMS_STRUCT      DdrMrParams;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  UpdateNeeded = FALSE;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & Outputs->ValidChBitMask) == 0) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      if (ChannelOut->DimmCount != 2) {
        continue;  // Not 2DPC
      }

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        SpdIn = &Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data;
        ManufactureData = &SpdIn->Ddr4.ManufactureInfo;
        if ((ManufactureData->DramIdCode.Data == 0xAD80) ||
            (ManufactureData->ModuleId.IdCode.Data == 0xAD80)) { // Hynix
          DateCode = (ManufactureData->ModuleId.Date.Year << 8) | ManufactureData->ModuleId.Date.Week;
          if (DateCode < 0x1545) {  // Before ww45'2015
            UpdateNeeded = TRUE;
            break;
          }
        }
      }
    } // for Channel
  } // for Controller

  if (UpdateNeeded) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Forcing 2x refresh...\n");
    SchedSecondCbit.Data = MrcReadCR (MrcData, MC0_CH0_CR_SCHED_SECOND_CBIT_REG);
    SchedSecondCbit.Bits.dis_srx_mr4 = 1;
    MrcWriteCrMulticast (MrcData, MC0_BC_CR_SCHED_SECOND_CBIT_REG, SchedSecondCbit.Data);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_PARAMS_REG, MC1_CH0_CR_DDR_MR_PARAMS_REG, Controller, MC0_CH1_CR_DDR_MR_PARAMS_REG, Channel);
        DdrMrParams.Data = MrcReadCR (MrcData, Offset);
        DdrMrParams.Bits.MR4_PERIOD         = 0;
        DdrMrParams.Bits.DDR4_TS_readout_en = 0;
        MrcWriteCR (MrcData, Offset, DdrMrParams.Data);

        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MCMNTS_SPARE_REG, MC1_CH0_CR_MCMNTS_SPARE_REG, Controller, MC0_CH1_CR_MCMNTS_SPARE_REG, Channel);
        McmntsSpare.Data = MrcReadCR (MrcData, Offset);
        McmntsSpare.Bits.ForceX2Ref = 1;  // force 2X refresh
        MrcWriteCR (MrcData, Offset, McmntsSpare.Data);
      }
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Force OLTM is not needed in the current DRAM configuration\n");
  }

  return Status;
}

/**
  Print DIMM ODT / Ron values per DIMM.
  Also print CPU ODT / Ron.

  @param[in] MrcData  - Include all MRC global data.

  @retval none
**/
extern
void
MrcPrintDimmOdtValues (
  IN MrcParameters *const MrcData
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcDebug      *Debug;
  UINT32        Controller;
  UINT8         Channel;
  UINT8         RankMask;
  UINT8         Rank;
  UINT8         Dimm;
  BOOLEAN       Ddr4;
  UINT16        OdtWrite;
  UINT16        OdtNom;
  UINT16        OdtPark;
  UINT16        OdtCA;
  UINT16        DimmRon;
  UINT16        CpuOdt[MAX_CHANNEL];
  //UINT16        CpuRon[MAX_CHANNEL];

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

//   DIMM ODT summary:
//
//              Ron     OdtWr   OdtNom  OdtPark (DDR4)
//              Ron     OdtDQ   OdtCA           (LPDDR4)
//   ---------------------------------------
//   Mc0C0D0:   48      Hi-Z    48      80
//   Mc0C0D1:   48      240     60      120
//   ---------------------------------------
//   Mc1C0D0:   48      48      34      34
//   Mc1C0D1:   48      48      34      34
//   ---------------------------------------
//
//   CPU Summary: Ron = 56, Read ODT = 109
//
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDIMM ODT summary:\n\tRon\t%s\n", Ddr4 ? "OdtWr\tOdtNom\tOdtPark" : "OdtDQ\tOdtCA");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "---------------------------------------\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      if (!ChannelOut->ValidRankBitMask) {
        continue;
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        RankMask = DIMM_TO_RANK_MASK (Dimm);
        Rank = Dimm * 2;
        if ((RankMask & ChannelOut->ValidRankBitMask) == 0) {
          continue;
        }
        OdtNom   = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtNom,  FALSE, 0, FALSE);
        OdtPark  = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtPark, FALSE, 0, FALSE);
        OdtCA    = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtCA, FALSE, 0, FALSE);
        OdtWrite = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtWr,   FALSE, 0, FALSE);
        DimmRon  = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmRon,     FALSE, 0, FALSE);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%dC%dD%d:\t%d\t", Controller, Channel, Dimm, DimmRon);
        if ((OdtWrite == 0xFFFF) || (OdtWrite == 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((OdtWrite == 0xFFFF) && Ddr4) ? "Hi-Z\t" : "Off\t");
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", OdtWrite);
        }
        if (Ddr4) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtNom == 0xFFFF) ? "Hi-Z\t" : "%d\t", OdtNom);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtPark == 0xFFFF) ? "Hi-Z\n" : "%d\n", OdtPark);
        } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OdtCA == 0xFFFF) ? "Off\t" : "%d\t", OdtCA);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }
      } // for Dimm
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "---------------------------------------\n");

    // Override digital offset to zero, after Comp Optimization the global value reflects the average across all bytes.
    //CpuRon[Channel] = CalcCpuImpedance (MrcData, Channel, 0, 0, OptWrDS, TRUE, 0, FALSE, 0, 0);
    CpuOdt[Channel] = CalcCpuImpedance (MrcData, Controller, Channel, 0, 0, OptRdOdt, TRUE, 0, FALSE, 0, 0);
    } // for Channel

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Summary: Channel = %d Read ODT = %d\n", Channel, CpuOdt[Channel]);
    }
  } // for Controller

#endif // MRC_DEBUG_PRINT
}

/**
  This function wrap DimmODTTraining routine.
  It will enable to control ch/ranks for this training and additional options.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcDimmODTTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcInput          *Inputs;
  MrcStatus         Status;
  MrcDdrType        DdrType;
  UINT8             Channel;
  UINT8             ChMask;
  UINT8             RankMask;
  UINT8             Dimm;
  BOOLEAN           DisSubOpt;
  BOOLEAN           Ddr4;
  BOOLEAN           any2DPC;
  UINT8             DimmParamList[4];
  UINT8             DimmParamSize;
  BOOLEAN           Ddr4UniqueCase;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  ControllerOut = &Outputs->Controller[0];

  ChMask    = Outputs->ValidChBitMask;
  DdrType   = Outputs->DdrType;
  Ddr4      = (DdrType == MRC_DDR_TYPE_DDR4);
  DisSubOpt = FALSE;
  Status    = mrcFail;
  any2DPC   = FALSE;
  Ddr4UniqueCase = FALSE;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChMask)) {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];

    if (ChannelOut->DimmCount == 2) {
      any2DPC = TRUE;
      // optional disable sub optimizations for low ROI and runtime
      // assuming we have already good enough setting
      DisSubOpt = TRUE;
      break;
    }
  }

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    DisSubOpt = TRUE;
  }

  // To optimize park we need to run per channel.
  if (Ddr4 && any2DPC && 0) { // disabled for now
    DimmParamList[0] = OptDimmOdtPark;
    DimmParamSize    = 1;
    RankMask         = MrcData->Outputs.ValidRankMask;
    Status = DimmODTTraining (MrcData, ChMask, RankMask, DisSubOpt, DimmParamList, DimmParamSize);
    if (Status != mrcSuccess) {
      return Status;
    }
  }
  if (Ddr4) {
    if (!any2DPC) {
      DimmParamList[0] = OptDimmOdtWr;
      DimmParamSize    = 1;
    } else {
      if (Inputs->PowerTrainingMode == MrcTmPower) {
        DimmParamList[0] = OptDimmOdtNomNT;
        DimmParamList[1] = OptDimmOdtWr;
        DimmParamSize    = 2;
      } else { // margin training
        DimmParamList[0] = OptDimmOdtComb;
        DimmParamList[1] = OptDimmOdtParkNT;
        DimmParamSize    = 2;
        Ddr4UniqueCase   = TRUE;
      }
    }
  } else { // LPDDR3, LPDDR4
    DimmParamList[0] = OptDimmOdtWr;
    DimmParamSize    = 1;
  }

  DimmParamSize = MIN (ARRAY_COUNT (DimmParamList), DimmParamSize);

  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm ++) {
    RankMask = DIMM_TO_RANK_MASK (Dimm);
    if ((RankMask & Outputs->ValidRankMask) == 0) {
      continue;
    }
    if (Ddr4UniqueCase && (Dimm == 1)) {
      // In Margin training, only run OdtComb / OdtParkNT optimization for the first DIMM.  The second DIMM should only run OdtComb
      DimmParamSize = 1;
    }
    Status = DimmODTTraining (MrcData, ChMask, RankMask, DisSubOpt, DimmParamList, DimmParamSize);
    if (Status != mrcSuccess) {
      return Status;
    }
  }

  // Print out the end results of the training step in Table Format
  MrcPrintDimmOdtValues (MrcData);

  return Status;
}

/**
  This function implements DIMM ODT training.
  Adjust DIMM RTT_NOM/RTT_WR value to maximize read/write voltage/timing

  RdOdtPriority Needs to be an input parameter
  option to prioritize the ReadODT setting and attempt to optimize that value first,
  reducing CPU TDP power (as opposed to system power for the DRAM).
  For this case, the base value for ReadODT is changed at the compensation block
  by looking at the following values:
     RdOdt Global: (50, 64, 84, 110)

  In the case of 2 dpc, the flow will first optimizing RttNom, while keeping RttWr fixed
  at 60 Ohms (60 Ohms usually gives the best results).  It will then try to reduce RttWr
  to 120 Ohms if possible.

  In the case of 1 dpc, only RttNom is used and only a single pass is required.
  However, it is important to note that the two channels are completely independent
  and can have different numbers of dimms populated.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] ChMask   - channels to optimize
  @param[in] RankMask - rank to optimize
  @param[in] skipSubOpt - skip sub optimization (Ron, Odt ect.)
  @param[in] *DimmParamList - list of dimm parameters to optimize
  @param[in] DimmParamSize - parametes list size
  @retval MrcStatus   - if it succeed return mrcSuccess
**/
MrcStatus
DimmODTTraining (
  IN MrcParameters *const MrcData,
  IN UINT8                ChMask,
  IN UINT8                RankMask,
  IN BOOLEAN              skipSubOpt,
  IN UINT8                *DimmParamList,
  IN UINT8                DimmParamSize
  )
{
  // @todo - in DDR 4 1DPC to make Rtt nom effect only on write the OdtMatrix reg should be program accordingly
  static const UINT16 OptDimmOdtCombNomVals[]  = { 80, 60, 48, 40, 34 };
  static const UINT16 OptDimmOdtCombWrVals[]   = { 0xFFFF, 240 };         // 0xFFFF - represents Hi-Z
  static const UINT16 OdtWrDDR4[]              = { 0xFFFF, 240, 120, 80}; // 0xFFFF - represents Hi-Z
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  MrcDdrType        DdrType;
  MrcDebugMsgLevel  LocalDebugLevel;
  MRC_MARGIN_LIMIT_TYPE LimitType;
  UINT8             Channel;
  UINT8             LocalRanks[MAX_CHANNEL];
  UINT8             IntRankMask;
  UINT8             DimmParam;
  UINT8             DimmIdx;
  UINT8             DimmOdtOff;
  UINT8             Test;
  UINT8             *TestList = NULL;
  UINT8             TestListSize = 0;
  BOOLEAN           any2DPC;
  BOOLEAN           any1DPC;
  BOOLEAN           Ddr4;
  UINT8             TestListWr[]  = {OptTxEqWrDS};//OptSComp
  UINT8             TestListRdWr[] = {OptRdOdt, OptTxEqWrDS};
  UINT8             Scale4Test[] = { 1, 1, 1, 1, 0 }; // must specify scale=0 to unpopulated slots !!
  UINT8             Scale2Test[] = { 1, 1, 0, 0, 0 }; // must specify scale=0 to unpopulated slots !!
  UINT8             *Scale = Scale2Test;
  UINT16            PwrLimits[MAX_TRADEOFF_TYPES];
  DimmOptPoint      DimmOptPoints[MAX_DIMM_OPT_OFF];
  UINT8             DimmOptPointIdx;
  UINT16            Points2calc[MAX_TRADEOFF_TYPES][MAX_DIMM_OPT_OFF];
  UINT8             ArrayLength;
  UINT8             DimmParamIdx;
  OptResultsPerByte BestOff;
  UINT16            Margin;
  UINT8             ChNotDoneMask;
  UINT8             ChBit;
  UINT16            *OdtWrPtr;
  UINT16            *OdtNomPtr;
  UINT16            *OdtParkPtr;
  UINT8             OdtWrSize;
  UINT8             OdtNomSize;
  UINT8             OdtParkSize;
  UINT8             OdtSetSize[RttMaxType];
  UINT16            *OdtSetPtr[RttMaxType];
  UINT8             RttTypeList[RttMaxType];
  UINT8             RttTypeSize;
  UINT8             RttLoop;
  UINT8             RttCnt;
  UINT8             RttSetSize;
  UINT8             DimmOptTestLength[MAX_CHANNEL];
  UINT8             UPMOptimize[MAX_TRADEOFF_TYPES];

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  Status              = mrcSuccess;
  LocalDebugLevel     = MSG_LEVEL_NEVER;
  ArrayLength         = (UINT8) (sizeof (Points2calc) / sizeof (Points2calc[0][0]) / MAX_TRADEOFF_TYPES);
  MrcCall             = Inputs->Call.Func;
  DdrType = Outputs->DdrType;
  Ddr4  = (DdrType == MRC_DDR_TYPE_DDR4);

  MrcCall->MrcSetMem ((UINT8 *) &BestOff, sizeof (BestOff), 0);
  MrcCall->MrcSetMem ((UINT8 *) Points2calc, sizeof (Points2calc), 0);
  MrcCall->MrcSetMem ((UINT8 *) LocalRanks, sizeof (LocalRanks), 0);
  MrcCall->MrcSetMem ((UINT8 *) UPMOptimize, sizeof (UPMOptimize), 0);
  MrcCall->MrcSetMemWord (PwrLimits, MAX_TRADEOFF_TYPES, 0);

  ChMask    &= Outputs->ValidChBitMask;
  RankMask  &= Outputs->ValidRankMask;

  any2DPC = FALSE;
  any1DPC = FALSE;

  OdtParkPtr = NULL;
  OdtParkSize = 0;
  OdtNomSize  = 0;

  // ODT matrix already init from McConfig for DDR4
  // Read flow:
  // Keep RttWr un-touched from McConfig, go by the OdtMatrix for Rtt nom/park from max power save to min
  // Write flow:
  // Keep RttNom/park un-touched, go by the OdtMatrix for Rtt Wr from max power save to min.
  // If 1DPC, we can have combos of wr/nom/park to get other Rtt values (wont effect read).
  // option 0: Keep RttWr the same for both DIMMs (ie: train per Ch for both RttWr & WrDrv) - SKL
  // option 1: Allow different RttWr for each DIMM and break WrDrv out of this optimization (ie: do it later).- HSW
  // For DDR4 per Dimm/Rank Optimization, we run this function with RankBitMask param
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChBit = 1 << Channel;
    if (!(ChBit & ChMask)) {
       continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    // Setup Dimm Masks for NormalizePowerToMargins so we don't access a Dimm that isn't present.
    if (ChannelOut->DimmCount == 2) {
      any2DPC |= 1;
    } else {
      any1DPC |= 1;
    }
     LocalRanks[Channel] = RankMask & ChannelOut->ValidRankBitMask;
     if (LocalRanks[Channel] == 0) {
       // Clear channel not populated with input ranks
       ChMask &= (~ChBit);
     }
  }

  // Initialize Odt pointers so no compile warnings
  OdtWrPtr = (UINT16 *) OdtWrDDR4;
  OdtNomPtr = (UINT16 *) OdtWrDDR4;
  // Update Odt Pointers to possible values
  if (Ddr4) {
    // For DDR4 we do not scearch full range (skip RttWr = 0)
    OdtWrPtr = (UINT16 *) OdtWrDDR4;
    OdtWrSize = ARRAY_COUNT (OdtWrDDR4);
    GetDimmOptParamValues (MrcData, OptDimmOdtNom, &OdtNomPtr, &OdtNomSize);
    GetDimmOptParamValues (MrcData, OptDimmOdtPark, &OdtParkPtr, &OdtParkSize);
  } else {
    GetDimmOptParamValues (MrcData, OptDimmOdtWr, &OdtWrPtr, &OdtWrSize);
  }


  for (DimmParamIdx = 0; DimmParamIdx < DimmParamSize; DimmParamIdx++) {
    // init the results struct
    MrcCall->MrcSetMem ((UINT8 *) DimmOptPoints, ARRAY_COUNT (DimmOptPoints), 0);
    DimmParam = DimmParamList[DimmParamIdx];

    switch (DimmParam) {
      case OptDimmOdtNom:
      case OptDimmOdtNomNT:
        // Assuming we run Nom sweep only when 2DPC
        OdtSetPtr[0]   = OdtNomPtr;
        OdtSetSize[0]  = RttSetSize = OdtNomSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListRdWr;
        TestListSize   = ARRAY_COUNT (TestListRdWr);
        Scale          = Scale4Test;
        break;

      case OptDimmOdtWr:
        OdtSetPtr[0]   = OdtWrPtr;
        OdtSetSize[0]  = RttSetSize = OdtWrSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListWr;
        TestListSize   = ARRAY_COUNT (TestListWr);
        Scale          = Scale2Test;
        break;

      case OptDimmOdtPark:
      case OptDimmOdtParkNT:
        OdtSetPtr[0]   = OdtParkPtr;
        OdtSetSize[0]  = RttSetSize = OdtParkSize;
        RttTypeList[0] = DimmParam;
        RttTypeSize    = 1;
        TestList       = TestListRdWr;
        TestListSize   = ARRAY_COUNT (TestListRdWr);
        Scale          = Scale4Test;
        break;

      case OptDimmOdtComb:
        // Set new limits for special cases
        if ((RankMask & Outputs->ValidChBitMask) && Ddr4) {
          // Slot 0 (we optimize also park assuming this is our w/c slot)
          // Wr : hi-z and 240
          RttTypeList[0]  = OptDimmOdtNomNT;
          OdtSetPtr[0]    = (UINT16 *) OptDimmOdtCombNomVals;          OdtSetSize[0]   = ARRAY_COUNT (OptDimmOdtCombNomVals);

          RttTypeList[1]  = OptDimmOdtWr;
          OdtSetPtr[1]    = (UINT16 *) OptDimmOdtCombWrVals;
          OdtSetSize[1]   = ARRAY_COUNT (OptDimmOdtCombWrVals);

          RttTypeList[2]  = OptDimmOdtPark;
          OdtSetPtr[2]    = (UINT16 *) OptDimmOdtCombNomVals;          OdtSetSize[2]   = ARRAY_COUNT (OptDimmOdtCombNomVals);
          RttTypeSize     = 3;
          if ((Inputs->PowerTrainingMode == MrcTmMargin) && Ddr4 && any2DPC) {
            UPMOptimize[LastRxT] = 1;
            UPMOptimize[LastTxT] = 1;
          }
        } else {
          // DDR4 slot 1
          RttTypeList[0]  = OptDimmOdtNomNT;
          OdtSetPtr[0]    = OdtNomPtr;
          OdtSetSize[0]   = OdtNomSize;

          RttTypeList[1]  = OptDimmOdtWr;
          OdtSetPtr[1]    = OdtWrPtr;
          OdtSetSize[1]   = OdtWrSize;
          RttTypeSize     = 2;
        }
        RttSetSize   = 1;
        for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
          RttSetSize *= OdtSetSize[RttLoop];
        }
        TestList      = TestListRdWr;
        TestListSize  = ARRAY_COUNT (TestListRdWr);
        Scale = Scale4Test;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DimmOdt : Unknown value for Optparam : %d DimmParamIdx : %d\n", DimmParam, DimmParamIdx);
        return mrcFail;
        break;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Training (ChannelMask = 0x%X, RankMask = 0x%X) SetSize =  %d\n", TOptParamOffsetString[DimmParam], ChMask, RankMask, RttSetSize);

    // The loop can be done per rank/dimm if needed using rank mask
    // In 1DPC we use same odt per "dimm"(==ch), assuming no much difference. (true for DDR4?)
    MrcCall->MrcSetMem (DimmOptTestLength, MAX_CHANNEL, 0);
    ChNotDoneMask   = ChMask;
    for (DimmOptPointIdx = 0; ((DimmOptPointIdx < RttSetSize) && (ChNotDoneMask != 0)); DimmOptPointIdx++) {
      // Propagate Odt changes per ch
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((1 << Channel) & ChNotDoneMask) {
          DimmOptTestLength[Channel] = DimmOptPointIdx + 1;
          // Copy the odt values to DimmOdtSet array for all
          for (DimmIdx = 0; DimmIdx < MAX_DIMMS_IN_CHANNEL; DimmIdx++) {
            if (DIMM_TO_RANK_MASK (DimmIdx) & LocalRanks[Channel]) {
              for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
                //DimmOptPointIdx is the index need to advance each RttType
                if (DimmParam == OptDimmOdtComb) {
                  if (RttLoop == 0) {
                    RttCnt = DimmOptPointIdx % OdtSetSize[RttLoop];
                  } else if (RttLoop == 1) {
                    RttCnt = (DimmOptPointIdx / OdtSetSize[0]) % OdtSetSize[RttLoop];
                  } else {
                    RttCnt = (DimmOptPointIdx / (OdtSetSize[0] * OdtSetSize[1])) % OdtSetSize[RttLoop];
                  }
                } else {
                  RttCnt = DimmOptPointIdx;
                }
                DimmOptPoints[DimmOptPointIdx].ODTSet.DimmOdt[Channel][DimmIdx].Rtt[RttLoop] = OdtSetPtr[RttLoop][RttCnt];
                DimmOptPoints[DimmOptPointIdx].ODTSet.DimmOdt[Channel][DimmIdx].RttType[RttLoop] = RttTypeList[RttLoop];
                MRC_DEBUG_MSG (
                  Debug,
                  LocalDebugLevel,
                  "-->Mc%d Ch%d Dimm%d set Odt %s to %d\n",
                  cCONTROLLER0, // @todo - 2xMC
                  Channel,
                  DimmIdx,
                  TOptParamOffsetString[RttTypeList[RttLoop]],
                  CalcDimmImpedance (MrcData, cCONTROLLER0, Channel, 2 * DimmIdx, RttTypeList[RttLoop], TRUE, OdtSetPtr[RttLoop][RttCnt], FALSE)
                  );
              }
              UpdateOptPointValues (MrcData, Channel, DIMM_TO_RANK_MASK (DimmIdx), &DimmOptPoints[DimmOptPointIdx], RttTypeSize, TRUE, FALSE, TRUE, TRUE);
            }
          }
        }
      } // ch loop
      if (Ddr4) {
        MrcSetDefaultRxVrefDdr4 (MrcData, FALSE, FALSE);
      }
      DQTimeCentering1D (MrcData, WrV, 0, 10, FALSE, FALSE);

      Status = TrainDimmOdtSetting (
        MrcData,
        &DimmOptPoints[DimmOptPointIdx],
        Outputs->ValidChBitMask,     // We still run both channel (if selected) although one can already have its ODT selected
        RankMask,
        TestList,
        TestListSize,
        Inputs->PowerTrainingMode,
        skipSubOpt,
        FALSE,
        0, // Center Reads Bool
        0  // Center Writes Bool
        );
      if (Status != mrcSuccess) {
        return Status;
      }

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((0x1 << Channel) & ChNotDoneMask)) {
          continue;
        }
        ChNotDoneMask &= ~(1 << Channel); // Mark Ch as Done
        for (Test = 0; Test < (DimmOptPoints[DimmOptPointIdx].NumTests); Test++) {
          Margin = DimmOptPoints[DimmOptPointIdx].Points2Trade[Test][Channel];
          MRC_DEBUG_MSG (Debug, LocalDebugLevel, "Dimm Odt point Result Summary - CH%d Test %s\t EH/EW %d\n",
            Channel, gMarginTypesStr[DimmOptPoints[DimmOptPointIdx].TestList[Test]], Margin);
          LimitType = (Inputs->PowerTrainingMode == MrcTmMargin) ? PowerLimit : UpmLimit;

          // This channel didn't reach the required margin limit for Margin or Power Training (on Any Test).
          if (Margin < MrcGetUpmPwrLimit (MrcData, DimmOptPoints[DimmOptPointIdx].TestList[Test], LimitType)) {
            MRC_DEBUG_MSG (Debug, LocalDebugLevel, "Channel: %d\tMargin Fail UPM: %d\n", Channel, Margin);
            ChNotDoneMask |= (1 << Channel);
            break;
          }
        }
      }
      MRC_DEBUG_MSG (Debug, LocalDebugLevel, "ChNotDoneMask: 0x%X\tDimmOptPointIdx: %u\n", ChNotDoneMask, DimmOptPointIdx);
#ifdef POWER_TRAINING_DEBUG
// @todo:      CalcSysPower (MrcData, DimmOptPoints[DimmOptPointIdx].PowerCalc);
#endif
    }  // for DimmOptPointIdx

    // Find the best point.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & ChMask)) {
        continue;
      }
      for (DimmOdtOff = 0; DimmOdtOff < DimmOptTestLength[Channel]; DimmOdtOff++) {
        // copy point for the FindOptTradeOff routing
        for (Test = 0; Test < (DimmOptPoints[DimmOdtOff].NumTests); Test++) {
          Points2calc[Test][DimmOdtOff] = DimmOptPoints[DimmOdtOff].Points2Trade[Test][Channel];
        }
      }
      // Get appropriate UPM Limits based on test Margin Type.  Reusing DimmOdtOff variable as index.
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpmLimits\n");
      for (DimmOdtOff = 0; DimmOdtOff < DimmOptPoints[0].NumTests; DimmOdtOff++) {
        PwrLimits[DimmOdtOff] = MrcGetUpmPwrLimit (MrcData, DimmOptPoints[0].TestList[DimmOdtOff], UpmLimit);
        MRC_DEBUG_MSG (
          Debug,
          LocalDebugLevel,
          "%s: %d\n",
          gMarginTypesStr[DimmOptPoints[0].TestList[DimmOdtOff]],
          PwrLimits[DimmOdtOff]
          );
      }
      FindOptimalTradeOff (
        MrcData,
        &BestOff,
        &Points2calc[0][0],
        ArrayLength,
        DimmOptTestLength[Channel], // number offset point to trade
        Scale,
        UPMOptimize,
        0, // EnSq
        1, // AvgN
        1, // IncEnds
        1, // ScaleM
        PwrLimits,
        (Inputs->PowerTrainingMode == MrcTmPower) ? 0 : 97, // Select first point above UPM or 100% of MaxR.  (Assumes ordered low -> high power)
        0  // GuardBand
        );

      for (DimmIdx = 0; DimmIdx < MAX_DIMMS_IN_CHANNEL; DimmIdx++) {
        IntRankMask = DIMM_TO_RANK_MASK (DimmIdx);
        if (IntRankMask & LocalRanks[Channel]) {
          UpdateOptPointValues (
            MrcData,
            Channel,
            IntRankMask,
            &DimmOptPoints[BestOff.Best],
            RttTypeSize,
            (DimmParam == RdOdt) ? FALSE : TRUE,
            FALSE,
            FALSE || skipSubOpt,
            TRUE
            );
        }
      }
#ifdef MRC_DEBUG_PRINT
      PrintODTResultTable (
        MrcData,
        &BestOff,
        DimmOptPoints,
        DimmOptTestLength[Channel],
        1, // include end points
        DimmParam,
        RttTypeSize,
        Channel,
        LocalRanks[Channel],
        1, // Tline
        !skipSubOpt,
        Scale,
        0, // per nibble
        1  // PerCh
        );
#endif // MRC_DEBUG_PRINT
    } // end of channel loop

    if (Ddr4) {
      // set vref accordingly to odt's
      MrcSetDefaultRxVrefDdr4 (MrcData, FALSE, FALSE);
    }
    DQTimeCentering1D (MrcData, WrV, 0, 10, FALSE, FALSE);
    DQTimeCentering1D (MrcData, RdV, 0, 10, FALSE, FALSE);
    if (Outputs->Lpddr) {
      DQTimeCentering1D (MrcData, WrTLp4, 0, 10, FALSE, FALSE);
    } else {
      DQTimeCentering1D (MrcData, WrT, 0, 10, FALSE, FALSE);
    }
    DQTimeCentering1D (MrcData, RdT, 0, 10, FALSE, FALSE);
  }
  return Status;
}

/**
  This function wrap DimmODTCATraining routine.
  This step is for LPDDR4 only.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus - if it succeed return mrcSuccess
**/
MrcStatus
MrcDimmOdtCaTraining (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { CmdV, CmdT };
  static const UINT8  Scale[] = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptDimmOdtCA };
  MrcOutput           *Outputs;
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Outputs = &MrcData->Outputs;

  if (!Outputs->Lpddr) {
    return mrcSuccess;
  }

  // Get searching limits
  //  0 - OFF
  //  1 - 240
  //  2 - 120
  //  3 - 80
  //  4 - 60
  //  5 - 48
  //  6 - 40

  Start = 1;  // 240  Ohm
  Stop = 6;   // 40   Ohm

  // Train CA ODT only
  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT(OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT(TestList),
    Scale,
    NULL,
    &Start,  // Start
    &Stop,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatternType
    );

  MrcCmdVoltageCentering (MrcData);
  MrcResetSequence(MrcData);

  // @todo Do we need to recenter CmdT/CmdV here ? Ask EV team

  return mrcSuccess;
}

/**
  This function implements Read Equalization training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcReadEQTraining (
  IN MrcParameters *const MrcData
  )
{
  UINT8               RankMask;
  static const UINT8  TestList[]  = { RdV, RdT };
  static const UINT8  Scale[]     = { 1, 2, 0, 0, 0 };
  static const UINT8  *OptParam1 = 0x0;
  static const UINT8  *OptParam2 = 0x0;
  static const UINT8  OptParamCTLE1[] = { OptRxC, OptRxR };
  static const UINT8  OptParamCTLE2[] = { OptRxEq }; // May set RxEq constant and sweep R/C 2D
  static const UINT8  OptParamDFE1[] = { OptDFETap0 };
  static const UINT8  OptParamDFE2[] = { OptDFETap1 };
  OptOffsetChByte     BestOff;
  UINT8               GridMode1;
  UINT8               GridMode2;
  UINT8               OptParamLength1;
  UINT8               OptParamLength2;
  INT8                StartCTLE1[2];
  INT8                StopCTLE1[2];
  INT8                StartCTLE2[1];
  INT8                StopCTLE2[1];
  INT8                StartDFE1[1];
  INT8                StopDFE1[1];
  INT8                StartDFE2[1];
  INT8                StopDFE2[1];
  INT8                *Start1;
  INT8                *Stop1;
  INT8                *Start2;
  INT8                *Stop2;
  MrcOutput           *Outputs;

  // TGL_POWER_TRAINING read DDRDATA_CR_DDRCrDataControl0_0_0_0_MCHBAR.RxMode
  // MrcGetSetDdrIoGroupChannelStrobe (MrcData, 0, 0, RxMode, ReadFromCache, &RxModeVal);
  Outputs = &MrcData->Outputs;
  if (Outputs->RxMode == MrcRxModeMatchedN || Outputs->RxMode == MrcRxModeMatchedP) {
      // CTLE
      OptParamLength1 = 2;
      OptParamLength2 = 1;
      GridMode1 = FullGrid;
      GridMode2 = FullGrid;
      OptParam1 = OptParamCTLE1;
      OptParam2 = OptParamCTLE2;

      StartCTLE1[0] = OptParamLimitValue (MrcData, OptParamCTLE1[0], 0);
      StopCTLE1[0] = OptParamLimitValue (MrcData, OptParamCTLE1[0], 1);
      StartCTLE1[1] = OptParamLimitValue (MrcData, OptParamCTLE1[1], 0);
      StopCTLE1[1] = OptParamLimitValue (MrcData, OptParamCTLE1[1], 1);
      StartCTLE2[0] = OptParamLimitValue (MrcData, OptParamCTLE2[0], 0);
      StopCTLE2[0] = OptParamLimitValue (MrcData, OptParamCTLE2[0], 1);
      Start1 = StartCTLE1;
      Stop1 = StopCTLE1;
      Start2 = StartCTLE2;
      Stop2 = StopCTLE2;
  } else {
      // DFE
      OptParamLength1 = 1;
      OptParamLength2 = 1;
      GridMode1 = FullGrid;
      GridMode2 = FullGrid;
      OptParam1 = OptParamDFE1;
      OptParam2 = OptParamDFE2;

      StartDFE1[0] = OptParamLimitValue (MrcData, OptParamDFE1[0], 0);
      StopDFE1[0] = OptParamLimitValue (MrcData, OptParamDFE1[0], 1);
      StartDFE2[0] = OptParamLimitValue (MrcData, OptParamDFE2[0], 0);
      StopDFE2[0] = OptParamLimitValue (MrcData, OptParamDFE2[0], 1);
      Start1 = StartDFE1;
      Stop1 = StopDFE1;
      Start2 = StartDFE2;
      Stop2 = StopDFE2;
  }

  // Function Call for RxEQ Training
  // TGL_POWER_TRAINING Can do per channel if all ranks turn out to be about the same (which they probably won't)
  for (RankMask = 1; RankMask < (0x1 << MAX_RANK_IN_CHANNEL); RankMask <<= 1) {
    if (RankMask & MrcData->Outputs.ValidRankMask) {
      TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        RankMask,
        OptParam1,
        OptParamLength1,
        GridMode1,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start1, // Start
        Stop1,  // Stop
        OPT_PARAM_1D_LC,
        1,      // Repeats
        0,      // NoPrint
        0,      // SkipOptUpdate
        0,      // RdRd2Test
        0,      // GuardBand
        BasicVA // PatType
        );
      TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        RankMask,
        OptParam2,
        OptParamLength2,
        GridMode2,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start2, // Start
        Stop2,  // Stop
        OPT_PARAM_1D_LC,
        1,      // Repeats
        0,      // NoPrint
        0,      // SkipOptUpdate
        0,      // RdRd2Test
        0,      // GuardBand
        BasicVA // PatType
        );
    }
  }

  return mrcSuccess;
}

/**
  Training the Cmd/CTL TxEq and Ron for best margins.
  Steps:
  1. Find the minimal Vref (Ron) for which Comp is not saturated (Start).
  2. Find the maximal Vref (Ron) for which Comp is not saturated (Stop).
  3. Train CCC Ron (Vref) & TxEq in the region [Start, Stop].
  4. Center Cmd Timing.
  5. Center Cmd Voltage.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcCmdEqDsTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  static const UINT8  TestList[] = { CmdV, CmdT };
  UINT8               Scale[] = { 1, 2, 0, 0, 0 }; // Must specify scale = 0 to unpopulate slots!!
  static const UINT8  OptParam[] = { OptCmdDS, OptCmdTxEq };
  //MrcOutput           *Outputs;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                Start[2];
  INT8                Stop[2];
  Inputs = &MrcData->Inputs;
  //Outputs = &MrcData->Outputs;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0] = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1] = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,
    Stop,
    OPT_PARAM_1D_LC - 3,  // Loopcount
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    BasicVA               // PatType
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center (may be required, but probably vref centering will be sufficient as timing widths are used in next steps).
  //Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  //if (Status != mrcSuccess) {
  //  return Status;
  //}
  Status = MrcCmdVoltageCentering (MrcData);
  return Status;
}

/**
  This function implements CMD/CTL Drive Strength Up/Dn 2D.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcCmdDsUpDnTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  static const UINT8  TestList[] = { CmdV, CmdT };
  UINT8               Scale[] = { 1, 1, 0, 0, 0 }; // Must specify scale = 0 to unpopulated slots!!
  static const UINT8  OptParam[] = { OptCmdDSUpCoarse, OptCmdDSDnCoarse };
  OptOffsetChByte     BestOff;
  UINT8               UPMOptimize[MAX_TRADEOFF_TYPES] = { 0, 1 };
  INT8                Start[2];
  INT8                Stop[2];
  MrcStatus           Status;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0] = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1] = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    UPMOptimize,
    Start,
    Stop,
    OPT_PARAM_1D_LC - 3,  // @todo adjust lc by rank population
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    BasicVA              // PatType
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
  Training the Cmd/CTL/CLK slew rate for best margins.
  Steps:
  1. Get Min/Max Stage Number from DDR Scomp config step (Start).
  2. Train CCC Slew rate stages in the region [Start, Stop].
  3. Re-center Cmd Timing.
  4. Re-center Cmd Voltage.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcCmdSlewRate (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { CmdV, CmdT };
  static const UINT8  Scale[] = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptCCCSComp };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  //MrcIntOutput        *IntOutputs;
  MrcStatus           Status;
  OptOffsetChByte     BestOff;
  INT8                MaxNumStages;
  INT8                MinNumStages;

  Outputs = &MrcData->Outputs;
  //IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Debug = &Outputs->Debug;

  // Can run this on LPDDR4 if need be, but probably we should skip it
  if (Outputs->Lpddr) {
    return mrcSuccess;
  }

  // TGL_POWER_TRAINING - Use these values if calculated in SComp init or elsewhere. Otherwise, use the values in the sweep range table.
  MinNumStages = OptParamLimitValue (MrcData, OptParam[0], 0); // IntOutputs->CmdSRData.MinChainLengthCmd;
  MaxNumStages = OptParamLimitValue (MrcData, OptParam[0], 1); // IntOutputs->CmdSRData.MaxChainLengthCmd;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCmd SComp Stages: Min %d, Max %d\n", MinNumStages, MaxNumStages);

  // Train Slew Rate for best margins
  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    CustomSR,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &MinNumStages,  // Start
    &MaxNumStages,  // Stop
    OPT_PARAM_1D_LC,
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatType
    );

  // Re-Center CMD Timing and voltage and update Host Struct with new center (may be required, but probably vref centering will be sufficient as timing widths are used in next steps).
  //Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
  //if (Status != mrcSuccess) {
  //  return Status;
  //}
  Status = MrcCmdVoltageCentering (MrcData);
  return Status;
}

/**
  This function implements VccDLL Bypass training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcVccDLLBypassTraining (
  IN MrcParameters *const MrcData
  )
{
    static const UINT8  TestList[] = { RdT, WrT, CmdT };
    static const UINT8  Scale[] = { 1, 1, 1, 0, 0 };
    static const UINT8  OptParam[] = { OptVccDLLBypass };
    OptOffsetChByte     BestOff;
    INT8                Start;
    INT8                Stop;
    MrcOutput           *Outputs;

    Outputs = &MrcData->Outputs;

    Start = OptParamLimitValue (MrcData, OptParam[0], 0);
    Stop = OptParamLimitValue (MrcData, OptParam[0], 1);

    TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        MrcData->Outputs.ValidRankMask,
        OptParam,
        ARRAY_COUNT (OptParam),
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        &Start,           // Start
        &Stop,            // Stop
        OPT_PARAM_1D_LC,
        1,                // Repeats
        0,                // NoPrint
        0,                // SkipOdtUpdate
        0,                // RdRd2Test
        0,                // GuardBand
        BasicVA           // PatType
        );

    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "Re-center Write Timing \n");
    if (Outputs->Lpddr) {
      DQTimeCentering1D (MrcData, WrTLp4, 0, 10, FALSE, FALSE);
    } else {
      DQTimeCentering1D (MrcData, WrT, 0, 10, FALSE, FALSE);
    }
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "Re-center Read Timing \n");
    DQTimeCentering1D (MrcData, RdT, 0, 10, FALSE, FALSE);
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "Re-centering Cmd/CTL Timing is done by LCT (next step) \n");

    return mrcSuccess;
}

/**
  This function implements Write (Transmitter) Equalization and Drive Strength training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteEqDsTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  static const UINT8  TestList[]  = { WrV, WrT };
  UINT8               Scale[]     = { 1, 2, 1, 0, 0 }; // Must specify scale = 0 to unpopulate slots!!
  static const UINT8  OptParam[]  = { OptTxEq, OptWrDS };
  OptOffsetChByte     BestOff;

  UINT8               RankMask;
  INT8                Start[2];
  INT8                Stop[2];

  Inputs  = &MrcData->Inputs;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);


  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  // TGL_POWER_TRAINING Can do per channel if all ranks turn out to be about the same
  for (RankMask = 1; RankMask < (0x1 << MAX_RANK_IN_CHANNEL); RankMask <<= 1) {
    if (RankMask & MrcData->Outputs.ValidRankMask) {
      TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        RankMask,
        OptParam,
        ARRAY_COUNT (OptParam),
        ChessOdd,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start,
        Stop,
        OPT_PARAM_1D_LC + 1,  // DS is more LC sensitive
        1,                    // Repeats
        0,                    // NoPrint
        0,                    // SkipOptUpdate
        0,                    // RdRd2Test
        0,                    // GuardBand
        BasicVA               // PatType
        );
    }
  }

  return mrcSuccess;
}

/**
  This function implements Write (Transmitter) Drive Strength Up / Down training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteDsUpDnTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  static const UINT8  TestList[]  = { WrV, WrT };
  UINT8               Scale[]     = { 1, 1, 0, 0, 0 }; // Must specify scale = 0 to unpopulated slots!!
  static const UINT8  OptParam[]  = { OptWrDSUpCoarse, OptWrDSDnCoarse };
  OptOffsetChByte     BestOff;
  UINT8               UPMOptimize[MAX_TRADEOFF_TYPES] = {0, 1};

  INT8                Start[2];
  INT8                Stop[2];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1]  = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    ChessOdd,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    UPMOptimize,
    Start,
    Stop,
    OPT_PARAM_1D_LC + 1,  // @todo adjust lc by rank population
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    BasicVA              // PatType
    );

  // Centering write
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Re-center Write Vref\n");
  MrcWriteVoltageCentering2D (MrcData);

  return mrcSuccess;
}

/**
  This function implements RxVref Decap training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcRxVrefDecapTraining (
  IN MrcParameters *const MrcData
  )
{
    MrcDebug            *Debug;
    MrcOutput           *Outputs;
    static const UINT8  TestList[] = { RdT, RdV };
    static const UINT8  Scale[] = { 2, 1, 0, 0, 0 }; // Must specify scale = 0 to unpopulated slots!!
    static const UINT8  *OptParam = 0x0;
    static const UINT8  OptParam1[] = { OptRxVrefVddqDecap };
    static const UINT8  OptParam2[] = { OptRxVrefVttDecap, OptRxVrefVddqDecap };
    OptOffsetChByte     BestOff;
    UINT8               RecenterLC;
    UINT8               OptParamLength;

    INT8                *Start;
    INT8                *Stop;
    INT8                Start1[1];
    INT8                Stop1[1];
    INT8                Start2[2];
    INT8                Stop2[2];

    RecenterLC = 15;
    Outputs = &MrcData->Outputs;
    Debug = &Outputs->Debug;

    switch (Outputs->OdtMode) {
        case MrcOdtModeVss:
        case MrcOdtModeVddq:
            Start1[0] = OptParamLimitValue (MrcData, OptParam1[0], 0);
            Stop1[0] = OptParamLimitValue (MrcData, OptParam1[0], 1);
            Start = Start1;
            Stop = Stop1;
            OptParam = OptParam1;
            OptParamLength = 1;

            break;
        case MrcOdtModeVtt:
            // Technically, you are supposed to sweep VrefVddqCapMFC < 8 - VrefVttCapMFC, but there's no way in the current algorithm to make one sweep range dependant
            // on the value being tested in another sweep range (and adding this would be a major re-work). So, we just have to sweep the full grid and try to optimize as best we can post-silicon.
            Start2[0] = OptParamLimitValue (MrcData, OptParam2[0], 0);
            Stop2[0] = OptParamLimitValue (MrcData, OptParam2[0], 1);
            Start2[1] = OptParamLimitValue (MrcData, OptParam2[1], 0);
            Stop2[1] = OptParamLimitValue (MrcData, OptParam2[1], 1);
            Start = Start2;
            Stop = Stop2;
            OptParam = OptParam2;
            OptParamLength = 2;

            break;
        case MrcOdtModeDefault:
        default:
            return mrcSuccess;
    }

    TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        MrcData->Outputs.ValidRankMask,
        OptParam,
        OptParamLength,
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start,
        Stop,
        OPT_PARAM_1D_LC,  // @todo adjust lc by rank population
        1,                    // Repeats
        0,                    // NoPrint
        0,                    // SkipOptUpdate
        0,                    // RdRd2Test
        0,                    // GuardBand
        BasicVA              // PatType
        );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center RxVref\n");
    DQTimeCentering1D (MrcData, RdV, 0, RecenterLC, FALSE, FALSE);

    return mrcSuccess;
}

/**
  This function implements PanicVttDnLp Training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcPanicVttDnLpTraining (
  IN MrcParameters *const MrcData
  )
{
    MrcDebug            *Debug;
    MrcOutput           *Outputs;
    static const UINT8  TestList[] = { RdV };
    static const UINT8  Scale[] = { 1, 0, 0, 0, 0 }; // Must specify scale = 0 to unpopulated slots!!
    static const UINT8  OptParam[] = { OptPanicVttDnLp };
    OptOffsetChByte     BestOff;
    UINT8               RecenterLC = 15;

    INT8                Start[2];
    INT8                Stop[2];

    Outputs = &MrcData->Outputs;
    Debug = &Outputs->Debug;

    // TGL_POWER_TRAINING Use uSD to measure Vtt voltage and adjust DDRCrVttGenControl.Target to match (probably in the PHY init?).

    if ((!Outputs->Lpddr) || (Outputs->OdtMode != MrcOdtModeVtt)) {
        return mrcSuccess;
    }

    Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
    Stop[0] = OptParamLimitValue (MrcData, OptParam[0], 1);

    TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        MrcData->Outputs.ValidRankMask,
        OptParam,
        ARRAY_COUNT (OptParam),
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start,
        Stop,
        OPT_PARAM_1D_LC,      // @todo adjust lc by rank population
        1,                    // Repeats
        0,                    // NoPrint
        0,                    // SkipOptUpdate
        0,                    // RdRd2Test
        0,                    // GuardBand
        BasicVA               // PatType
        );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center RxVref\n");
    DQTimeCentering1D (MrcData, RdV, 0, RecenterLC, FALSE, FALSE);

    return mrcSuccess;
}

/**
  This function implements Vddq power training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess
**/
MrcStatus
MrcVddqTraining (
  IN MrcParameters *const MrcData
  )
{
    MrcStatus           Status;
    MrcOutput           *Outputs;
    MrcDebug            *Debug;
    static const UINT8  TestList[] = { CmdV, CmdT, WrV, WrT };
    static const UINT8  Scale[] = { 1, 1, 1, 1 };
    static const UINT8  OptParam[] = { OptVddq };
    OptOffsetChByte     BestOff;
    UINT8               RecenterLC;
    INT8                Start[1];
    INT8                Stop[1];
    INT8                GuardBand;
    BOOLEAN             Lpddr;

    // TGL_POWER_TRAINING: This algorithm can potentially (but shouldn't under operational conditions) overflow vref values during VDDQ adjustments. Make sure postsilicon that the VDDQ sweep range doesn't cause Vref overflows.

    RecenterLC = 15;
    Status = mrcSuccess;
    Outputs = &MrcData->Outputs;
    Debug = &Outputs->Debug;
    Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) || (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);

    if (!Lpddr) {
        return mrcSuccess;
    }

    Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
    Stop[0] = OptParamLimitValue (MrcData, OptParam[0], 1);

    GuardBand = 0; // Margins increases are monotonic with param changes, so does not require a param gaurdband

    TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask,
        MrcData->Outputs.ValidRankMask,
        OptParam,
        ARRAY_COUNT (OptParam),
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        Start,            // Start
        Stop,             // Stop
        OPT_PARAM_1D_LC,
        1,                // Repeats
        0,                // NoPrint
        0,                // SkipOdtUpdate
        0,                // RdRd2Test
        GuardBand,
        BasicVA           // PatType
        );

    // JEDEC init in case the last Vddq setting messed up the DRAMs (only needed if running data margins blindly after command margins).
    // MrcResetSequence (MrcData);

    // May not be neccesary if we can adjust in the get/set Vddq method
    // Timings need not be re-centered since we are using widths for power training after this, we just need to make sure the Vrefs aren't really far off.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Cmd Vref\n");
    Status = MrcCmdVoltageCentering (MrcData);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Tx Vref\n");
    DQTimeCentering1D (MrcData, WrV, 0, RecenterLC, FALSE, FALSE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Rx Vref\n");
    DQTimeCentering1D (MrcData, RdV, 0, RecenterLC, FALSE, FALSE);
    // May need to re-center CMD/CTL-CLK if this disturbs the CMD/CTL to CLK alignment by more than a few ticks. DQTimeCentering1D does not currently support 'CmdT'.
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Cmd Timing\n");
    // Re-Center CMD Timing and voltage and update Host Struct with new center
    // Status = MrcCmdTimingCentering (MrcData, Outputs->ValidChBitMask, 10, TRUE, MRC_PRINTS_ON, 1);
    // May need to re-center Write Leveling if this disturbs the TxDqs to CLK alignment by more than a few ticks. DQTimeCentering1D does not currently support 'WrDqsT'.
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center TxDqs (Write Leveling Fine)\n");
    // DQTimeCentering1D (MrcData, MrcData->Outputs.ValidChBitMask, WrDqsT, 0, RecenterLC, FALSE, FALSE);
    return Status;
}

/**
  This function implements Read Amplifier Power training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess
**/
MrcStatus
MrcReadAmplifierPower (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus           Status;
  MrcOutput           *Outputs;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  static const UINT8  TestList[]  = { RdV, RdT, RcvEnaX };
  UINT8               Scale[]     = { 1, 2, 1, 1, 0 }; // Must specify scale = 0 to unpopulated slots!!
  UINT8               OptParam[]  = { OptRxLoad, OptRxCb };
  OptOffsetChByte     BestOff;
  UINT8               RecenterLC;
  INT8                Start[2];
  INT8                Stop[2];
  INT8                GuardBand;

  RecenterLC  = 15;
  Status      = mrcSuccess;
  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Debug       = &Outputs->Debug;

  // TGL_POWER_TRAINING read DDRDATA_CR_DDRCrDataControl0_0_0_0_MCHBAR.RxMode if we end up training OptRxBias in matched path mode.
  // MrcGetSetDdrIoGroupChannelStrobe (MrcData, 0, 0, RxMode, ReadFromCache, &RxModeVal);
  if ((Outputs->RxMode == MrcRxModeMatchedN) || (Outputs->RxMode == MrcRxModeMatchedP)) {
    OptParam[0] = OptRxBias;
  }

  Start[0] = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop[0]  = OptParamLimitValue (MrcData, OptParam[0], 1);
  Start[1] = OptParamLimitValue (MrcData, OptParam[1], 0);
  Stop[1] = OptParamLimitValue (MrcData, OptParam[1], 1);

  if (Inputs->PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  GuardBand = 0;

  // Function Call for RxBias
  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    Start,            // Start
    Stop,             // Stop
    OPT_PARAM_1D_LC,
    1,                // Repeats
    0,                // NoPrint
    0,                // SkipOdtUpdate
    0,                // RdRd2Test
    GuardBand,
    BasicVA           // PatType
    );

  // @todo : we might want to do here Sense amp training instead.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Timing\n");
  Status = DataTimeCentering2D (
            MrcData,
            Outputs->MarginResult, // prev. margin results
            Outputs->ValidChBitMask,
            RdT,
            0, // EnPerBit,
            0, // EnRxDutyCycle
            0, // ResetPerBit
            RecenterLC,
            0  // En2D
            );

  return Status;
}

/**
  This function implements Dimm Ron training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeds return mrcSuccess
**/
MrcStatus
MrcDimmRonTraining (
  IN MrcParameters *const MrcData
  )
{
  OptOffsetChByte     BestOff;
  MrcOutput           *Outputs;
  static const UINT8  TestList[]  = { RdV, RdT };
  UINT8               Scale[]     = { 1, 2, 1, 0, 0 }; // Must specify scale = 0 to unpopulate slots!!
  static const UINT8  OptParam[]  = { OptDimmRon };
  UINT16              *DimmRonVals;
  UINT8               RankMask;
  INT8                Start;
  INT8                Stop;
  INT8                Off;

  if (MrcData->Inputs.PowerTrainingMode == MrcTmMargin) {
    Scale[ARRAY_COUNT (TestList)] = 0;
  }

  Outputs = &MrcData->Outputs;
  Start = 0;
  GetDimmOptParamValues (MrcData, OptParam[0], &DimmRonVals, (UINT8 *) &Stop);
  Stop -= 1; // Stop = Size - 1

  MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "\nDIMM Ron Offset - Value mapping \nOffset\t Value\n");
  for (Off = Start; Off < Stop + 1; Off++) {
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "%d:\t %u \n", Off, DimmRonVals[(UINT8) Off]);
  }

  // TGL_POWER_TRAINING Can do per channel if all ranks turn out to be about the same
  for (RankMask = 1; RankMask < (0x1 << MAX_RANK_IN_CHANNEL); RankMask <<= 1) {
    if (RankMask & MrcData->Outputs.ValidRankMask) {
      TrainDDROptParam (
        MrcData,
        &BestOff,
        MrcData->Outputs.ValidChBitMask, // Channels
        RankMask,         // Ranks
        OptParam,
        ARRAY_COUNT (OptParam),
        FullGrid,
        TestList,
        ARRAY_COUNT (TestList),
        Scale,
        NULL,
        &Start,          // Start
        &Stop,           // Stop
        OPT_PARAM_1D_LC, // Loopcount
        1,               // Repeats
        0,               // NoPrint
        0,               // SkipOdtUpdate
        0,               // RdRd2Test
        0,               // GuardBand
        BasicVA          // PatType
        );
    }
  }

  DQTimeCentering1D (MrcData, RdV, 0, 10, FALSE, FALSE);
  DQTimeCentering1D (MrcData, RdT, 0, 10, FALSE, FALSE);

  return mrcSuccess;
}

/**
  This function implements the general training algorithm for DDR and IO parameters
  that impact margin and power.

  This function can train for power or for margin, and the function determines the mode as follows:
    PowerTraining: (NumTests <= MAX_TRADEOFF_TYPES) && (Scale[NumTests] != 0)
    else MarginTraining.

  The Parameters that are supported:
    [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 3: TxEq, 4: RxEq, 5: RxBias, 6: DimmOdt, 7: DimmOdtWr]

  @param[in,out] MrcData           - Include all MRC global data.
  @param[in,out] BestOff           - Structure containg the best offest and margins (values) for th Opt param.
  @param[in]     ChannelMask       - Channels to train
  @param[in]     RankMask          - Condenses down the results from multiple ranks
  @param[in]     OptParam          - Defines the OptParam Offsets (e.g. OptRdOdt, OptSComp..etc)
  @param[in]     OptParamLen       - Defines the size of OptParam[].
  @param[in]     GridMode          - Selects the way to sweep the params
  @param[in]     TestList          - List of margin params that will be tested (up to 4)
  @param[in]     NumTests          - The length of TestList[].
  @param[in]     Scale             - List of the relative importance between the 4 tests
  @param[in]     UPMOptimize       - Optimize in FindOptimalTradeOff only for UPM limit for selected params, so if they pass UPM they do not affect the score.
  @param[in]     Start             - Start point of sweeping the Comp values
  @param[in]     Stop              - Stop point of sweeping the Comp values
  @param[in]     LoopCount         - The number of loops to run in IO tests.
  @param[in]     Repeats           - Number of times to repeat the test to average out any noise
  @param[in]     NoPrint           - Switch to disable printing.
  @param[in]     SkipOptUpdate     - Switch to train but not update Opt settings.
  @param[in]     RdRd2Test         - Switch to run with different TA times: possible values are [0, RdRdTA, RdRdTA_All]
  @param[in]     GuardBand         - Signed offset to apply to the Opt param best value.
  @param[in]     PatType           - Type of pattern the will be applied for optimization, trying to keep MrcDqPat definitions. Allowed values: [BasicVA, StaticPattern (Simple Pattern)]

  @retval Nothing
**/
void
TrainDDROptParam (
  IN OUT MrcParameters *const MrcData,
  IN OUT OptOffsetChByte      *BestOff,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     const UINT8          OptParam[],
  IN     UINT8                OptParamLen,
  IN     UINT8                GridMode,
  IN     const UINT8          *TestList,
  IN     UINT8                NumTests,
  IN     const UINT8          *Scale,
  IN     UINT8                UPMOptimize[MAX_TRADEOFF_TYPES],
  IN     INT8                 Start[],
  IN     INT8                 Stop[],
  IN     UINT8                LoopCount,
  IN     UINT8                Repeats,
  IN     BOOLEAN              NoPrint,
  IN     BOOLEAN              SkipOptUpdate,
  IN     UINT8                RdRd2Test,
  IN     INT8                 GuardBand,
  IN     UINT8                PatType
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcControllerOut    *ControllerOut;
  UINT16              (*MarginByte)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32              BERStats[4];
  INT32               NewVddq;
  INT32               DefaultVddq;
  INT32               TxVrefBaseTicks;
  INT32               CmdVrefBaseTicks;
  INT32               DefaultCmdVref[MAX_CHANNEL];
  INT32               DefaultTxVref[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  INT32               DefaultRxVref[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16              SaveMargin[MAX_MARGINS_TRADEOFF][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16              PostMargin[MAX_MARGINS_TRADEOFF][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8               Test;
  UINT16              MinEye;
  UINT16              Margins[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS]; // TestParam X 24 Comp Points
  UINT16              UpmLimits[MAX_TRADEOFF_TYPES];
  UINT16              PwrLimits[MAX_TRADEOFF_TYPES];
  INT16               Best;
  INT64               GetSetValue;
  UINT8               OptimizationMode;
  UINT8               ResultType;
  UINT8               AveN;
  UINT8               Ave2DXDim;
  UINT8               Ave2DXLim;
  UINT8               MarginStart;
  INT8                RxEqMarginLength;
  UINT8               ChBitMask;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Rank;
  UINT8               Edge;
  UINT8               FirstRank;
  UINT8               NumBytes;
  UINT8               BMap[9]; // Need by GetBERMarginByte
  UINT8               Param;
  UINT8               MaxMargin;
  UINT8               localR[MAX_CHANNEL];
  UINT8               FirstRankPerCh[MAX_CHANNEL];
  UINT8               Rep;
  UINT8               CurrentComp;
  UINT8               StepSize = 1;
  UINT8               NumChannels = 0;
  INT8                ReservedComp;
  INT8                MaxComp;
  UINT16              OptPower[MAX_CHANNEL][MAX_OPT_POINTS];
  INT8                Delta;
  UINT8               Index;
  UINT8               OffLen[MAX_GRID_DIM];
  INT8                ParamOff[MAX_GRID_DIM];
  UINT8               LenMargin;
  UINT8               MaxOptPoints;
  BOOLEAN             IncEnds;
  BOOLEAN             IncEndsForPrint;
  BOOLEAN             CPUComp;
  BOOLEAN             NeedForceComp;
  BOOLEAN             printPerCh;
  BOOLEAN             BusFailure = 0;
  BOOLEAN             GlobalSetDone = 0;
  BOOLEAN             PowerMeasured = 0;
  UINT8               OptIdx;
  MrcPower            BytePower[MAX_OPT_POINTS];
  BOOLEAN             EnBer;
  UINT16              Margin;
  BOOLEAN             IgnoreUpmPwrLimit;
  UINT16              MinChByte;
  BOOLEAN             GlobalParam;
  BOOLEAN             AllGlobalParam;
  BOOLEAN             UpdateHost;
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;
#ifdef LB_STUB_FLAG
  UINT16                ParamVector[3];
  UINT16                SimMargin;
  MRC_POWER_SYS_CONFIG  SysConfig;
#endif
  OptResultsPerByte calcResultSummary; // Result print summary: 5 columns per byte
  static UINT32 Pattern[8][2] = {
    { 0xF0F0F0F0, 0xF0F0F0F0 },
    { 0xCCCCCCCC, 0xCCCCCCCC },
    { 0x0F0F0F0F, 0x0F0F0F0F },
    { 0x55555555, 0x55555555 },
    { 0xCCCCCCCC, 0xCCCCCCCC },
    { 0xF0F0F0F0, 0xF0F0F0F0 },
    { 0x55555555, 0x55555555 },
    { 0x0F0F0F0F, 0x0F0F0F0F }
  };

  static UINT32 Pattern2[8][2] = {
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 }
  };

  DefaultVddq         = 0;
  AllGlobalParam      = TRUE;
  GlobalParam         = FALSE;
  ResultType          = 0;
  CurrentComp         = 0;
  IncEnds             = 1;
  IncEndsForPrint     = 1;
  printPerCh          = 0;
  UpdateHost          = FALSE;
  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  ReservedComp        = 3; // Reserve 3 comp codes for adjustment range
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  MarginByte          = &Outputs->MarginResult;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  if (Outputs->Lpddr) {
    TxVrefBaseTicks  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? LP4_TXVREF_BASE_TICKS : LP5_TXVREF_BASE_TICKS;
    CmdVrefBaseTicks = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? LP4_CMDVREF_BASE_TICKS : LP5_CMDVREF_BASE_TICKS;
  } else {
    TxVrefBaseTicks  = DDR4_TXVREF_BASE_TICKS;
    CmdVrefBaseTicks = DDR4_CMDVREF_BASE_TICKS;
  }
  NeedForceComp = FALSE;
  IgnoreUpmPwrLimit = FALSE;
  MrcCall->MrcSetMem ((UINT8 *) &calcResultSummary, sizeof (calcResultSummary), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestOff, sizeof (OptOffsetChByte), 0xFF); // @todo: cleanup multiple clears.
  MrcCall->MrcSetMem ((UINT8 *) Margins, sizeof (Margins), 0);
  MrcCall->MrcSetMem ((UINT8 *) SaveMargin, sizeof (SaveMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) PostMargin, sizeof (PostMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) OptPower, sizeof (OptPower), 0);
  MrcCall->MrcSetMem ((UINT8 *) localR, sizeof (localR), 0);
  MrcCall->MrcSetMem ((UINT8 *) FirstRankPerCh, sizeof (FirstRankPerCh), 0);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (Index = 0; Index < MAX_OPT_POINTS; Index++) {
    MrcCall->MrcSetMem ((UINT8 *) &BytePower[Index], sizeof (BytePower[Index]), 0);
  }
  MrcCall->MrcSetMem ((UINT8 *) &OffLen, sizeof (OffLen), 0);
  MrcCall->MrcSetMemWord (UpmLimits, MAX_TRADEOFF_TYPES, 0);
  MrcCall->MrcSetMemWord (PwrLimits, MAX_TRADEOFF_TYPES, 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  if (RdRd2Test == RdRdTA) {
    LoopCount -= 1;  // 2 TA tests, so cut the loop count in half.
  } else if (RdRd2Test == RdRdTA_All) {
    LoopCount -= 3;  // 8 TA tests, so divide the loop count by 8.
  }

  if (PatType == StaticPattern) {
    // @todo Update with McChBitMask
    if (OptTxDqTco) {
      SetupIOTestStatic (MrcData, ChannelMask, LoopCount, NSOE, 0, 0, 1, Pattern2);
    } else {
      SetupIOTestStatic (MrcData, ChannelMask, LoopCount, NSOE, 0, 0, 4, Pattern);
    }
    IgnoreUpmPwrLimit = TRUE;
  } else if (PatType == BasicVA){
    // For all other training params use regular VA pattern
    // @todo Update with McChBitMask
    SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, NSOE, 0, 0, 8, PatWrRd, 0, 0); // Set test to all channels.
  } else {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Unknown pattern in TrainDDROptParam %u \n", PatType);
    return;
  }
  if (RdRd2Test != 0) {
    Outputs->DQPat = RdRd2Test;
  }

  // Select All Ranks for REUT test
  ChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & ChannelMask)) {
        continue;
      }

      ChannelOut      = &ControllerOut->Channel[Channel];
      localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;

      if (localR[Channel] != 0x0) {
        NumChannels++;
      }

      // Use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
      ChBitMask |= SelectReutRanks (MrcData, Controller, Channel, localR[Channel], FALSE, 0);
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "reut ranks ChBitMask %x Local ranks=%x\n", ChBitMask,localR[Channel]);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((0x1 << Rank) & localR[Channel]) {
          FirstRankPerCh[Channel] = Rank;
          break;
        }
      }
    }
  }

  if (ChBitMask == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TrainDDROptParam() ChBitMask == %d\n", ChBitMask);
    return;
  }

  // Find the first selected rank
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((0x1 << Rank) & RankMask ) {
      FirstRank = Rank; // could be in any channel
      break;
    }
  }

  // Store margin results (per byte or ch)
  NumBytes = 1;
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
    if ((OptParam[OptIdx] != OptDimmOdt) && (OptParam[OptIdx] != OptDimmOdtWr) && (OptParam[OptIdx] != OptDimmRon) && (OptParam[OptIdx] != OptDimmOdtCA) &&
      (OptParam[OptIdx] != OptClkTco) && (OptParam[OptIdx] != OptCmdDSDnCoarse) && (OptParam[OptIdx] != OptCmdDSUpCoarse) && (OptParam[OptIdx] != OptCmdDS) &&
      (OptParam[OptIdx] != OptCmdTxEq) && (OptParam[OptIdx] != OptCCCSComp) && (OptParam[OptIdx] != OptVccDLLBypass) && (OptParam[OptIdx] != OptPanicVttDnLp) &&
      (OptParam[OptIdx] != OptVddq) && (OptParam[OptIdx] != OptRxCb)) {
      NumBytes = (UINT8) Outputs->SdramCount; // if one of param is per byte store per byte
    }
    // TGL_POWER_TRAINING - We need to check this depending on the power measurement system. In the past, we had no model for the CCC bus, so we left all CCC power training
    //                      off UPM/power limit evals. If we have FIVR, we should be able to measure CCC power. Only the Panic VTT Dn optimization isn't directly related to any power value,
    //                      and is simply being minimized.
    if (OptParam[OptIdx] == OptPanicVttDnLp) {
      IgnoreUpmPwrLimit = TRUE;
    }

    // Calculate Start/Stop Point for Comp Optimization
    // For TcoComp avoid Reserved comps as it isn't really compensated
    CPUComp = ((OptParam[OptIdx] == OptWrDS) || (OptParam[OptIdx] == OptCmdDS) || (OptParam[OptIdx] == OptWrDSUpCoarse) || (OptParam[OptIdx] == OptWrDSDnCoarse) ||
               (OptParam[OptIdx] == OptCmdDSUpCoarse) || (OptParam[OptIdx] == OptCmdDSDnCoarse) || (OptParam[OptIdx] == OptRdDqOdt) || (OptParam[OptIdx] == OptRdDqsOdt) ||
               (OptParam[OptIdx] == OptRdOdt) || (OptParam[OptIdx] == OptSComp) || (OptParam[OptIdx] == OptCCCSComp) || (OptParam[OptIdx] == OptRxLoad));
    if (CPUComp) {
      if (OptParam[OptIdx] == OptSComp || OptParam[OptIdx] == OptRxLoad) {
        MaxComp = 31;
      } else {
        MaxComp = 63;
      }
      CurrentComp = GetCompCode (MrcData, OptParam[OptIdx], 2);
      if ((OptParam[OptIdx] == OptWrDSUpCoarse) || (OptParam[OptIdx] == OptWrDSDnCoarse)) {
        StepSize = WR_DS_STEP;
      } else if ((OptParam[OptIdx] == OptCmdDSUpCoarse) || (OptParam[OptIdx] == OptCmdDSDnCoarse)) {
        StepSize = CCC_DS_STEP;
      } else if ((OptParam[OptIdx] == OptRxLoad)) {
        StepSize = RX_LOAD_STEP;
      }
      Delta = CurrentComp - ReservedComp + Start[OptIdx] * StepSize;
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Start[OptIdx] -= Delta / StepSize; // Value delta, not total steps, so compute steps here
      }

      Delta = MaxComp - CurrentComp - ReservedComp - Stop[OptIdx] * StepSize;
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Stop[OptIdx] += Delta / StepSize; // Value delta, not total steps, so compute steps here
      }

      if (Stop[OptIdx] < Start[OptIdx]) {
        Stop[OptIdx] = Start[OptIdx];
      }
      if (!SkipOptUpdate) {
        // print is irrelevant in this case
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "CurrentComp = %d, Start = %d, Stop = %d\n",
          CurrentComp,
          Start[OptIdx],
          Stop[OptIdx]
        );
      }
    }
    if (CPUComp || OptParam[OptIdx] == OptVddq || OptParam[OptIdx] == OptVccDLLBypass || OptParam[OptIdx] == OptRxVrefVttDecap || OptParam[OptIdx] == OptRxVrefVddqDecap || OptParam[OptIdx] == OptCmdTxEq) { // Re-run comps after any comp or voltage change (Why is OptCmdTxEq here?)
      NeedForceComp = TRUE;
    }
  } // End OptIdx loop to store margin results

  // Determine where the power column is, or if we're training for best margin.
  OptimizationMode = ((NumTests <= MAX_TRADEOFF_TYPES) && (Scale[NumTests] != 0)) ?
                      NumTests : 100;

  // Loop through all test params and measure margin.
  // Calc total num of points for full grid.
  LenMargin = 1;
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
    OffLen[OptIdx] = (Stop[OptIdx] - Start[OptIdx] + 1);
    LenMargin *= OffLen[OptIdx];
    BestOff->GridDataSet.Start[OptIdx] = Start[OptIdx];
    BestOff->GridDataSet.OffLen[OptIdx] = OffLen[OptIdx];
  }
  if (SkipOptUpdate) {
    // Just run Margins test
    LenMargin = 1;
    GridMode = FullGrid;
  }
  if ((GuardBand !=0 ) && (OptParamLen == 2)) {
    // Make sure we apply the GB to the DS
    if (OptParam[1] == OptWrDS) {
      GuardBand *= OffLen[0];
    }
  }
  BestOff->GridDataSet.GridMode = GridMode;
  BestOff->GridDataSet.OptParamLen = OptParamLen;
  MaxOptPoints = MAX_OPT_POINTS;
  if (LenMargin > MaxOptPoints) {
    LenMargin = MaxOptPoints;
     MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning : LenMargin exceed max: %d length is clipped\n", MAX_OPT_POINTS);
  }
  if (!NoPrint) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LenMargin = %d, Test LoopCount = %d\n", LenMargin, LoopCount);
  }

  // Loop Through all Comp Codes
  for (Index = 0; Index < LenMargin; Index++) {
    if (OptParam[0] == OptVddq && BusFailure) { // If the CAC and/or data bus failed for a previous Vddq setting, don't run any more Vddq settings as they should all fail.
      continue;
    } else if (OptParam[0] == OptVddq && Index == 0) {
      // TGL_POWER_TRAINING Replace this when Vddq get/set is complete.
      DefaultVddq = 440 + VDDQ_BASE_TICKS; // MrcGetSetDdrIoGroupController0 (MrcData, Vddq, ReadFromCache, &DefaultVddq);
    }

    // Continue accordingly to GridMode
    if (GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen)) { // return ParamOff[param]
      continue;
    }
    for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
    // GlobalParam = Train all channels to the same result based on the worst case results across all channels
    GlobalParam = OptParam[OptIdx] == OptClkTco || OptParam[OptIdx] == OptVccDLLBypass || OptParam[OptIdx] == OptPanicVttDnLp || OptParam[OptIdx] == OptVddq || OptParam[OptIdx] == OptRxCb;
      AllGlobalParam &= GlobalParam;
      GlobalSetDone = 0;
      UpdateHost = ((Outputs->Lpddr) && ((OptParam[OptIdx] == OptRdOdt) || (OptParam[OptIdx] == OptRdDqOdt) || (OptParam[OptIdx] == OptRdDqsOdt) || (OptParam[OptIdx] == OptRdOdtUp) || (OptParam[OptIdx] == OptRdOdtDn)));
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((0x1 << Channel) & ChBitMask)) {
            continue;
          }

          ChannelOut = &ControllerOut->Channel[Channel];
          for (Byte = 0; Byte < NumBytes; Byte++) {
            if (!SkipOptUpdate) {
              // Change OpParam offset for all ch/byte/LocalR
              // Note: When using multi OptParams need to take care that one is not overwritten
              //       by the other in UpdateOptParamOffset routine (because UpdateHost=0).
              //       Changed function to always read CSRs to avoid this.
              // Note: Some are limited in range inside e.g: RdOdt +15:-16
              if (GlobalSetDone != 1) {
                UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], UpdateHost);
              }
              if (GlobalParam) {
                GlobalSetDone = 1;
              }
            }
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--Channel=%d, localR[Channel]=%x Byte=%d OffsetComp=%d Off=%d\n",Channel,localR[Channel],Byte,OffsetComp,Off);
          }
        }
      }
      GlobalSetDone = 0;

      // Re-center any margins required as a result of updating the optimization param
      if (OptParam[OptIdx] == OptVddq) {
        // Run a JEDEC init in case the last Vddq setting messed up the DRAMs (only needed if running data margins blindly after command margins).
        //MrcResetSequence (MrcData);

        // Let's just re-center the vrefs. The timings will be by width, and should be accurate if the Vrefs are good. This will save time and limit JEDEC inits.
        if (NoPrint) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Cmd Vref, Tx Vref, and Rx Vref\n");
        }

        NewVddq = DefaultVddq - VDDQ_STEP * ParamOff[OptIdx];

        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((0x1 << Channel) & ChBitMask)) {
              continue;
            }

            if (Index == 0) { // Cache
              MrcGetSetMcCh (MrcData, Controller, Channel, CmdVref, ReadFromCache, &GetSetValue);
              DefaultCmdVref[Channel] = (INT32) GetSetValue;
            }
            GetSetValue = (INT64) ((NewVddq * (DefaultCmdVref[Channel] + CmdVrefBaseTicks)) / DefaultVddq - CmdVrefBaseTicks);
            MrcGetSetMcCh (MrcData, Controller, Channel, CmdVref, WriteCached, &GetSetValue);

            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if ((0x1 << Rank) & RankMask) {
                continue;
              }

              if (Index == 0) { // Cache
                // TGL_POWER_TRAINING - Add TxVref to Get/Set
                // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MRC_IGNORE_ARG, TxVref, ReadFromCache, &DefaultTxVref[Channel][Rank]);
              }
              GetSetValue = (INT64) ((NewVddq * (DefaultTxVref[Channel][Rank] + TxVrefBaseTicks)) / DefaultVddq - TxVrefBaseTicks);
              // TGL_POWER_TRAINING - Add TxVref to Get/Set
              // MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MRC_IGNORE_ARG, TxVref, WriteCached, &GetSetValue);
            }

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
                continue;
              }

              if (Index == 0) { // Cache
                MrcGetSetChStrb (MrcData, Controller, Channel, Byte, RxVref, ReadFromCache, &GetSetValue);
                DefaultRxVref[Channel][Byte] = (INT32) GetSetValue;
              }
              GetSetValue = (INT64) ((DefaultVddq * (DefaultRxVref[Channel][Byte] + RXVREF_BASE_TICKS)) / NewVddq - RXVREF_BASE_TICKS);
              MrcGetSetChStrb (MrcData, Controller, Channel, Byte, RxVref, WriteCached, &GetSetValue);
            }
          }
        }
      }
    }
    if (NeedForceComp) {
      ForceRcomp (MrcData);
    }

    for (Test = 0; Test < NumTests; Test++) {
      if (OptParam[0] == OptVddq && BusFailure) { // If the CAC and/or data bus failed for this Vddq setting, don't run any more tests.
        continue;
      }

      Param = TestList[Test]; // tl[0]=4 tl[1]=1
      if ((Param == CmdT) || (Param == CmdV)) {
        // @todo Update with McChBitMask
        SetupIOTestCADB (MrcData, ChannelMask, LoopCount, NSOE, 1, 0);
        IncEnds = 1;
      }
      ResultType = GetMarginResultType (Param); // rxv=0 rxt=1
                                                // Assign to last pass margin results by reference
                                                // get lowest margin from all ch/rankS/byte save in FirstRank
      GetMarginByte (MrcData, Outputs->MarginResult, Param, FirstRank, RankMask);
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- FirstRank = %d ResultType=%d Param=%d ranks=0x%x\n", FirstRank,ResultType,Param,RankMask);
      // Calculate the MaxMargin for this test
      if ((Param == WrV) || (Param == WrFan3) || (Param == WrFan2) ||
        (Param == RdV) || (Param == RdFan3) || (Param == RdFan2) || (Param == CmdV)) {
        MaxMargin = GetVrefOffsetLimits (MrcData, Param);
      } else {
        MaxMargin = MAX_POSSIBLE_TIME;
      }
      if (Index == 0) {
        if (IgnoreUpmPwrLimit) {
          // Set Upm / Power limits to maximal search region
          UpmLimits[Test] = 20 * MaxMargin;
          PwrLimits[Test] = 20 * MaxMargin;
        }
        else {
          UpmLimits[Test] = MrcGetUpmPwrLimit (MrcData, Param, UpmLimit);
          PwrLimits[Test] = MrcGetUpmPwrLimit (MrcData, Param, PowerLimit);
        }
      }
      MaxMargin = MIN (MaxMargin, (UINT8)(PwrLimits[Test] / 20));

      for (Rep = 0; Rep < Repeats; Rep++) {
        // Run Margin Test - margin_1d with chosen param
        // run on all ranks but change param only for firstRank??
        EnBer = 1;

#ifndef LB_STUB_FLAG
        if (Param == CmdT) {
          if (Outputs->Lpddr) {
            if (OptParam[0] == OptVddq) {
              // TGL_POWER_TRAINING Margin CMD timings here with ECT patterns. If using LCT patterns, re-enable MrcResetSequence() call further down.
            } else {
              CmdLinearFindEdgesLpddr (MrcData, MrcIterationClock, ChBitMask, RankMask, 0x1F, MRC_PRINTS_OFF); // 1F means all CMD groups
            }
          } else {
            CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, -64, 64, 6, 1, (INT8 *)NULL, TRUE, TRUE);
          }
          // Restore centered value
          for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
                if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
                  ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationClock, 1 << Rank, MRC_IGNORE_ARG_8, 0, 0);
                }
              }
            }
          }
        } else if (Param == CmdV) {
          if (OptParam[0] == OptVddq) {
            // TGL_POWER_TRAINING Margin CMD voltage here with ECT patterns. If using LCT patterns, re-enable MrcResetSequence() call further down.
          } else {
            MrcGetBERMarginCh (
              MrcData,
              Outputs->MarginResult,
              ChBitMask,
              0xFF,
              RankMask,
              Param,
              0,  // Mode
              0,
              MaxMargin,
              0,
              BERStats
              );
          }
        } else {
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcGetBERMarginByte ChBitMask=%x FirstRank=%d Param=%d\n",ChBitMask, FirstRank, Param);
          MrcGetBERMarginByte (
            MrcData,
            Outputs->MarginResult,
            ChBitMask,
            RankMask,
            RankMask,
            Param,
            0,  // Mode
            BMap,
            EnBer,
            MaxMargin,
            0,
            BERStats
            );
        }


        if (((Param == CmdT) || (Param == CmdV)) && !(OptParam[0] == OptVddq)) { // Don't run for Vddq unless using LCT patterns
          MrcResetSequence (MrcData);
        }
#endif
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " finish MrcGetBERMarginByte \n");
        // Record Test Results
        MinChByte = MRC_UINT16_MAX;
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((0x1 << Channel) & ChBitMask)) {
              continue;
            }
            MinEye = 0xFFFF;
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              SaveMargin[Test][Index][Channel][Byte] = 0;
              if (Param != CmdT) {
                for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                  // CmdT margins are stored according to a slightly different convention - Save in first populated rank per channel
                  // All other margins are saved to first populated rank among all channels
                  Margin = (*MarginByte)[ResultType][FirstRank][Controller][Channel][Byte][Edge];
                  SaveMargin[Test][Index][Channel][Byte] += Margin;

                  if (OptParam[0] == OptVddq) {
                    if (Margin == 0) {
                      // If any command Vref margins are 0, then we don't have at least 1 tick of margin on both sides of the eye.
                      // This indicates a failure of the CAC bus, so set a flag that skips any further tests (and leaves all margins at 0).
                      // This will save time and cause the algorithm to decide this Vddq setting doesn't work (without triggering any JEDEC inits).
                      BusFailure = 1;
                    }
                  }
                }
              } else {
                // For the case of CmdT we had previously performed centering of CMD Timing. If the margin is not centered then we apply a penalty to avoid this selection.
                SaveMargin[Test][Index][Channel][Byte] = 2 * MIN ((*MarginByte)[ResultType][FirstRankPerCh[Channel]][Controller][Channel][Byte][0],
                                                                  (*MarginByte)[ResultType][FirstRankPerCh[Channel]][Controller][Channel][Byte][1]);
                if (OptParam[0] == OptVddq) {
                  if (SaveMargin[Test][Index][Channel][Byte] < 2) {
                    // If any command timing margins are less than 2, then we don't have at least 1 tick of margin on both sides of the eye.
                    // This indicates a failure of the CAC bus, so set a flag that skips any further tests (and leaves all margins at 0).
                    // This will save time and cause the algorithm to decide this Vddq setting doesn't work (without triggering any JEDEC inits).
                    BusFailure = 1;
                  }
                }
              }
              if (MinEye > SaveMargin[Test][Index][Channel][Byte]) {
                MinEye = SaveMargin[Test][Index][Channel][Byte];
              }
              if ((Param == CmdT) || (Param == CmdV)) {
                break;  // Exit per-byte loop
              }
            }
            if (NumBytes == 1) {
              SaveMargin[Test][Index][Channel][0] = MinEye;
            }
          }
        }
        if (AllGlobalParam) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
              for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
                if (!((0x1 << Channel) & ChBitMask)) {
                  continue;
                }
                if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
                  continue;
                }
                // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u Byte%u MinChByte = %u\n", Channel, Byte, MinChByte);
                MinChByte = MIN (MinChByte, SaveMargin[Test][Index][Channel][Byte]);
              }
            }
            if ((Param == CmdT) || (Param == CmdV)) {
              break;  // Exit per-byte loop
            }
          }
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MinChByte = %u\n", MinChByte);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
              for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
                if (!((0x1 << Channel) & ChBitMask)) {
                  continue;
                }
                if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
                  continue;
                }
                SaveMargin[Test][Index][Channel][Byte] = MinChByte;
              }
            }
            if ((Param == CmdT) || (Param == CmdV)) {
              break;
            }
          }
        }
      }

      if ((Param == CmdT) || (Param == CmdV)) {
        // Disable CADB Deselects
        CadbConfig.Data = 0;
        CadbConfig.Bits.CADB_MODE = 0;
        CadbConfig.Bits.CADB_TO_CPGC_BIND = 1;
        Cadb20ConfigRegWrite (MrcData, CadbConfig);
      }
    } // end of test list
  } // end of offset
  for (Test = 0; Test < NumTests; Test++) {
#ifdef MRC_DEBUG_PRINT
    PrintResultTableByte4by24 (
      MrcData,
      ChBitMask,
      SaveMargin,
      Test,
      LenMargin,
      0,
      OptParam[0],// @todo expand to more then 1
      TestList[Test],
      PwrLimits,
      NoPrint
      );
#endif // MRC_DEBUG_PRINT
  } // end of test list

  PowerMeasured = 0;

  // Calculate the best value for every byte
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & ChBitMask)) {
        continue;
      }
       ChannelOut = &ControllerOut->Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & localR[Channel])) {
        continue;
      }
      for (Byte = 0; Byte < NumBytes; Byte++) {
        // Populate Margins array and asymmetric penalty
        for (Test = 0; Test < NumTests; Test++) {
          for (Index = 0; Index < LenMargin; Index++) {
            Margins[Test][Index] = SaveMargin[Test][Index][Channel][Byte];
          }
        }

        // Special Cases for Running Average Filter
        if (OptParamLen == 1) { // 1D case
          if ((OptParam[0] == OptDimmOdt) || (OptParam[0] == OptDimmOdtWr) || (OptParam[0] == OptDimmRon) || (OptParam[0] == OptDimmOdtCA) ||
              (OptParam[0] == OptClkTco) || (OptParam[0] == OptTxDqTco) || (OptParam[0] == OptTxDqsTco) || (OptParam[0] == OptVccDLLBypass) ||
              (OptParam[0] == OptPanicVttDnLp) || (OptParam[0] == OptVddq) || (OptParam[0] == OptRxVrefVttDecap)|| (OptParam[0] == OptRxVrefVddqDecap) ||
              (OptParam[0] == OptCmdDS) || (OptParam[0] == OptCmdDSDnCoarse) || (OptParam[0] == OptCmdDSUpCoarse) || (OptParam[0] == OptCCCSComp) || (OptParam[0] == OptDFETap0) || (OptParam[0] == OptDFETap1)) {
            AveN = 1;
          } else if ((OptParam[0] == OptRxBias) || (OptParam[0] == OptTxDqsTco) || (OptParam[0] == OptRxLoad)) {
            AveN = 3;
          } else if (OptParam[0] == OptRxEq) {
            // Use special, 2D running average for RxEq
            Ave2DXDim         = 7;
            Ave2DXLim         = 0;
            MarginStart       = 1;  // Skipping the first setting since it is a bypass mode.
            RxEqMarginLength  = LenMargin - 1;
            AveN = 1;
            for (Test = 0; Test < NumTests; Test++) {
              RunningAverage2D (&Margins[Test][MarginStart], RxEqMarginLength, Ave2DXDim, Ave2DXLim, Test);
            }
          } else {
            AveN = 7;
            if (LenMargin < AveN) {
              AveN = LenMargin - 1;
            }
          }
        } else {
          // 2D case (for now) - Todo: should depend on GridMode.
          AveN = 1;
          for (Test = 0; Test < NumTests; Test++) {
            if (GridMode < FullGrid) {
              Fill2DAverage (MrcData, Margins, Test, LenMargin, OffLen[0], 0, 1);
              for (Index = 0; Index < LenMargin; Index++) { // refill the SaveMargin array after filling the gaps
                SaveMargin[Test][Index][Channel][Byte] = Margins[Test][Index];
              }
            }
            RunningAverage2D (&Margins[Test][0], LenMargin, OffLen[0], 0, 1);
          }
        }

        // Use one of the Margin Arrays for fine grain power tradeoffs. This is only used if Scale[NumTests] is not 0
        for (Index = 0; Index < LenMargin; Index++) {
          if (PowerMeasured == 0) {
            MrcCall->MrcSetMem ((UINT8 *)&BytePower[Index], sizeof (BytePower[Index]), 0);
            GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen);
            CalcOptPower (MrcData, &BytePower[Index], FirstRank, OptParam, ParamOff, OptParamLen, CurrentComp, 10);
          }
          if ((OptParam[0] == OptVccDLLBypass) || (OptParam[0] == OptVddq) || (OptParam[0] == OptClkTco) || (OptParam[0] == OptCmdTxEq) ||
              (OptParam[0] == OptCmdDS) || (OptParam[0] == OptCmdDSDnCoarse) || (OptParam[0] == OptCmdDSUpCoarse) || (OptParam[0] == OptCCCSComp) || (OptParam[0] == OptDimmOdtCA)) {
            Margins[NumTests][Index] = BytePower[Index].TotalPwr / (NumBytes * NumChannels);
          } else if ((OptParam[0] == OptRdDqOdt) || (OptParam[0] == OptRdDqsOdt) || (OptParam[0] == OptRdOdt) || (OptParam[0] == OptRxBias) || (OptParam[0] == OptRxLoad) || (OptParam[0] == OptRxC) || (OptParam[0] == OptRxR) ||
                     (OptParam[0] == OptPanicVttDnLp) || (OptParam[0] == OptRxVrefVttDecap) || (OptParam[0] == OptRxVrefVddqDecap) ||
                     (OptParam[0] == OptDFETap0) || (OptParam[0] == OptDFETap1) || (OptParam[0] == OptDimmRon) || (OptParam[0] == OptRxCb) || (OptParam[0] == OptRxEq)) {
            Margins[NumTests][Index] = BytePower[Index].RdPower / (NumBytes * NumChannels);
          } else {
            Margins[NumTests][Index] = BytePower[Index].WrPower / (NumBytes * NumChannels);
          }
          OptPower[Channel][Index] = Margins[NumTests][Index]; //+= BytePower.TotalPwr; // sum all bytes.  @todo check if OptPower[Index]can be remove (for print)
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OptPower[%d][%d]: %d Power->WrPower: %d\n", Channel, Index, OptPower[Channel][Index], BytePower.TotalPwr);
        }
        PowerMeasured = 1; // Don't measure the power except on one channel and byte, as we get the entire power value for all channels/bytes on a given rank

        // need to provide set of power numbers depending on the OffsetComp codes (per byte)for trend line.
        NormalizePowerToMargins (MrcData, Margins, MAX_OPT_POINTS, LenMargin, NumTests);

        // Use that value to create Margin Results based on power.
        // Creates a smooth, linear function that goes from MaxSum to N/(N-1)*MaxSum
        // RatioNum = FinePwrRatio[OptParam] * LenMargin; //e.g FinePwrRatio[RdOdt]=5
        // Find the Best Overall Setting
        // senSq=0,caleM=1,powerOpHigh=0
        FindOptimalTradeOff (
          MrcData,
          &calcResultSummary,
          &Margins[0][0],
          MAX_OPT_POINTS,
          LenMargin,
          Scale,
          UPMOptimize,
          0,
          AveN,
          IncEnds,
          1,
          UpmLimits,
          OptimizationMode,
          GuardBand
          );

        // Get the best index considering the GuardBand
        Best = calcResultSummary.Best + calcResultSummary.GuardBand;
        for (Test = 0; Test < NumTests; Test++) {
          // PostMargin will be reported back to DimmOdt
          // in old method you can get non coherency between result here and what reported out
          PostMargin[Test][Channel][Byte] = calcResultSummary.Margins[Test][Best].EW;
        }

        // Best is Index, need to convert to OptParam Offset (ParamOff)
        //Best -= Shift  // update take offset look like bug

        GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, (UINT8) Best, Start, OffLen);
        if (!SkipOptUpdate) {
          if (GlobalSetDone != 1) {
            for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++) {
              UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], 1);
            }
          }
          if (AllGlobalParam) {
            GlobalSetDone = 1;
          }
        }

        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " localR[Channel]=%x Best =%d ch=%d byte=%d \n",localR[Channel],(UINT8) Best,Channel,Byte);
        BestOff->Offset[Channel][Byte] = Best;
#ifdef MRC_DEBUG_PRINT
        for (Test = 0; Test < NumTests; Test++) {
          Print2DResultTableChByte (
            MrcData,
            Channel,
            Byte,
            &calcResultSummary,
            BestOff,
            TestList[Test],
            LenMargin,
            Start,
            Stop,
            OptParam,
            OffLen,
            PwrLimits,
            OptParamLen,
            Test,
            NumTests,
            NoPrint
            );
        }
#endif // MRC_DEBUG_PRINT
      } // end byte
      // Print After Calc (Stack Size Reduction)
      // Printing the results
#ifdef MRC_DEBUG_PRINT


      if (0) {
        // printing the results
        // @todo: make some loop here
        IncEndsForPrint =
          (
          OptParam[0] == OptDimmOdt ||
          OptParam[0] == OptDimmOdtWr ||
          OptParam[0] == OptDimmRon ||
          OptParam[0] == OptRxEq ||
          IncEnds
          );
        printPerCh = (OptParam[0] == OptDimmOdt || OptParam[0] == OptDimmOdtWr || OptParam[0] == OptDimmRon);

        // lower bytes
        PrintCalcResultTableCh (
          MrcData,
          &calcResultSummary,
          TestList,
          NumTests,
          LenMargin,
          0,
          IncEndsForPrint,
          OptParam[0],
          OptPower[Channel],
          Channel,
          localR[Channel],
          Scale[NumTests],
          0,
          printPerCh,
          NoPrint
          );

        // higher bytes
        if (!printPerCh) {
          PrintCalcResultTableCh (
            MrcData,
            &calcResultSummary,
            TestList,
            NumTests,
            LenMargin,
            0,
            IncEndsForPrint,
            OptParam[0],
            OptPower[Channel],
            Channel,
            localR[Channel],
            Scale[NumTests],
            1,
            printPerCh,
            NoPrint
            );
          }
        } // if (0)
#endif // MRC_DEBUG_PRINT
    } // End of Calculating best value (ch)
  }

  // Update the LastPass points in host
  for (Test = 0; Test < NumTests; Test++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }

      ResultType = GetMarginResultType (TestList[Test]);
      for (Byte = 0; Byte < NumBytes; Byte++) {
        // save the margins in best offset point for each byte/ch in  rank 0/1
         Best = (UINT8) (BestOff->Offset[Channel][Byte]);

         (*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][0] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
         (*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][1] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "best offset= %d ;byte=%d ;(*MarginByte)[ResultType][0][Controller][Channel][Byte][0] -%d (*MarginByte)[ResultType][0][Controller][Channel][Byte][1] -%d add=%d\n",(UINT8) (BestOff->Offset[Channel][Byte] - Start),Byte,(UINT16) (*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][0] , (*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][1],((UINT16) (*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][0] + (UINT16)(*MarginByte)[ResultType][0][/**Controller**/ CONTROLLER_0][Channel][Byte][1]));
      }
    }

    ScaleMarginByte (MrcData, Outputs->MarginResult, TestList[Test], 0);
  }

  // Save the BestOff Values
  BestOff->NumTests = NumTests;
  for (Test = 0; Test < NumTests; Test++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }
      // Track minimum eye width per ch
      for (Byte = 0; Byte < NumBytes; Byte++) {
        if (Byte == 0) {
          BestOff->Margins[Test][Channel] = PostMargin[Test][Channel][0];
        } else if (BestOff->Margins[Test][Channel] > PostMargin[Test][Channel][Byte]) {
          BestOff->Margins[Test][Channel] = PostMargin[Test][Channel][Byte];
        }
      }
      BestOff->TestList[Test][Channel] = TestList[Test];
      // @todo : add OptParam list
    }
  }
  // Clean up
  if (NeedForceComp) {
    ForceRcomp (MrcData);
  }

  return;
}

/**
  This function calculates the average Rx ODT impedance for the given channel/subchannel.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index to legacy channel (x64 bit)
  @param[in]  SubCh   - 0-based index to enhanced channel (x32 bit).

  @retval - UINT16: Impedance in Ohms.
**/
UINT16
CalcAverageByteImpedance (
  IN MrcParameters *const MrcData,
  IN UINT8                Controller,
  IN UINT8                Channel
  )
{
  MrcOutput      *Outputs;
  UINT8           Byte;
  UINT8           Bytes;
  UINT8           Rank;
  UINT16          ByteImpedance;
  MrcDebug       *Debug;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  ByteImpedance = 0;
  Bytes = 0;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
      continue;
    }

    for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
      if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
        continue;
      }

      ByteImpedance += CalcCpuImpedance (MrcData, Controller, Channel, Rank, Byte, OptRdOdt, FALSE, FALSE, FALSE, FALSE, 0);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ctrl%u.Ch%u.B%u - ByteImpedance %u\n", Controller, Channel, Byte, ByteImpedance);
      Bytes++;
    }
  }

  ByteImpedance /= Bytes;

  return ByteImpedance ;
}

/**
  This function is responsible for updating the SOC ODT value in LPDDR4 memory based on the CPU ODT settings.
  This reads the CPU ODT using the current comp settings, find the closest SOC ODT settings and programs it to the corresponding MR.
  Note - calculating CPU impedance assumes the cached value holds the current settings.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval -Nothing.
**/
void
Lpddr4UpdateSocOdt (
  IN MrcParameters *const MrcData
  )
{
  // MrcDebug        *Debug;
  // MrcOutput       *Outputs;
  UINT8           Channel;
  UINT8           Controller;
  UINT16          CpuImpedance;
  UINT16          SocOdt;

  // Outputs = &MrcData->Outputs;
  // Debug   = &Outputs->Debug;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (MrcData, Controller, Channel))) {
        continue;
      }

      CpuImpedance = CalcAverageByteImpedance (MrcData, Controller, Channel);
      SocOdt = MrcCheckForSocOdtEnc (MrcData, CpuImpedance);
      SetDimmParamValue (MrcData, Controller, Channel, 0xF, OptDimmSocOdt, SocOdt, TRUE);
    }
  }
}


/**
  This function implements Read ODT training.
  Optimize Read ODT strength for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeded return mrcSuccess
**/
MrcStatus
MrcReadODTTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus       Status;
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  UINT8           *TestList;
  UINT8           TestListNonLp[]  = { RdV, RdT };
  UINT8           TestListSize;
  UINT8           ScaleNonLp[]     = { 1, 2, 1, 0, 0 };
  UINT8           *Scale;
  INT8            StartDqs;
  INT8            StopDqs;
  INT8            StartDq;
  INT8            StopDq;
  UINT8           OdtCodeMin;
  UINT8           OdtCodeMax;
  INT8            Delta;
  UINT16          Rleg;
  INT8            StatLegs;
  UINT8           OdtLegsDis;
  INT8            CurrentVrefUp;
  UINT8           CurrentCompDn;
  UINT8           CurrentCompUp;
  OptOffsetChByte BestOff;
  UINT8           RdTATestType;
  UINT8           OptParamDqs[] = { OptRdDqsOdt };
  UINT8           OptParamDq[] = { OptRdDqOdt };
  UINT8           TestListLpddr[] = { RdV, RdT, RcvEnaX };
  UINT8           ScaleLpddr[]    = { 1, 2, 2, 1, 0 };
  BOOLEAN         Lpddr;
  BOOLEAN         ODTSingleSegEn;
  INT64           GetSetVal;
  //MrcChannelOut                 *ChannelOut;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;

  Lpddr = Outputs->Lpddr;
  StartDqs = OptParamLimitValue (MrcData, OptParamDqs[0], 0);
  StopDqs  = OptParamLimitValue (MrcData, OptParamDqs[0], 1);
  StartDq  = OptParamLimitValue (MrcData, OptParamDq[0], 0);
  StopDq   = OptParamLimitValue (MrcData, OptParamDq[0], 1);
  // Find a start offset where we below 180ohm to protect against OS/US
  MrcGetSetNoScope (MrcData, CompRcompOdtUp, ReadUncached, &GetSetVal);
  CurrentCompUp       = (INT8) GetSetVal;
  MrcGetSetNoScope (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
  CurrentCompDn       = (INT8) GetSetVal;
  OdtCodeMin          = MIN(CurrentCompUp, CurrentCompDn); //ohm
  OdtCodeMax          = MAX(CurrentCompUp, CurrentCompDn); //ohm
  RdTATestType        = RdRdTA;

  if (Lpddr) {
    RdTATestType = RdRdTA_All;
    TestList     = TestListLpddr;
    Scale        = ScaleLpddr;
    TestListSize = ARRAY_COUNT (TestListLpddr);
  } else {
    TestList            = TestListNonLp;
    TestListSize        = ARRAY_COUNT (TestListNonLp);
    Scale               = ScaleNonLp;
  }

  if ((Outputs->OdtMode == MrcOdtModeVtt) || (Inputs->PowerTrainingMode == MrcTmMargin)) {
    Scale[TestListSize] = 0; // no power considuration in Vtt
  }

  // TGL_POWER_TRAINING The get/set method for GsmIocCompOdtStaticDis needs to set 3 registers/fields. Any one can be read, as they should all be the same.
  //    DDRDATA_CR_DDRCrDataControl.DisableOdtStatic
  //    DDRCOMP_CR_DDRCRCOMPCTL1_0_0_0_MCHBAR.disableodtstatic
  //    DDRDATA_CR_DDRCrDataControl2.DisableDqsOdtStatic
  MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, ReadFromCache, &GetSetVal);
  OdtLegsDis = (UINT8) GetSetVal;
  // TGL_POWER_TRAINING In the get/set method for DqOdtVref, DqOdtVrefUp, and DqOdtVrefDn, we need to check for
  // DDRDATA_CR_DDRCrDataControl5_0_0_0_MCHBAR.ODTSingleSegEn == 0. If this is true, then set DqOdtVref to 2 * GetSetVal, and if read, return (register value / 2).
  MrcGetSetNoScope (MrcData, DqOdtVrefUp, ReadFromCache, &GetSetVal);
  CurrentVrefUp = (INT8) GetSetVal;
  ODTSingleSegEn = 0; // TGL_POWER_TRAINING ChannelOut->DdrCrDataControl5[0].ODTSingleSegEn == 1;
  StatLegs            = 5 * (2 - ODTSingleSegEn);
  if (CurrentVrefUp & 0x10) {
    CurrentVrefUp -= 0x20; // 2's complement
  }

  Rleg  = CalcCpuImpedance (MrcData, 0, 0, 0, 0, OptRdDqOdt, TRUE, 0, TRUE, CurrentVrefUp, CurrentCompUp) * (StatLegs * (!OdtLegsDis) + CurrentCompUp);

  // Check Comp code limit on start and stop
  Delta = OdtCodeMin + StartDqs;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> Warning: %s range %s is clipped by %d\n", "Dqs", "start", Delta);
    StartDqs -= Delta;
  }

  Delta = 63 - OdtCodeMax - StopDqs;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> Warning: %s range %s is clipped by %d\n", "Dqs", "stop", Delta);
    StopDqs += Delta;
  }

  // Check Comp code limit on start and stop
  Delta = OdtCodeMin + StartDq;
  if (Delta < 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> Warning: %s range %s is clipped by %d\n", "Dq", "start", Delta);
      StartDq -= Delta;
  }

  Delta = 63 - OdtCodeMax - StopDq;
  if (Delta < 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> Warning: %s range %s is clipped by %d\n", "Dq", "stop", Delta);
      StopDq += Delta;
  }

  if (StopDqs > (MAX_OPT_POINTS + StartDqs)) {
    StopDqs = (INT8) (MAX_OPT_POINTS + StartDqs); // MAX_OPT_POINTS offsets in the margin array.
  }

  if (StopDq > (MAX_OPT_POINTS + StartDq)) {
      StopDq = (INT8)(MAX_OPT_POINTS + StartDq); // MAX_OPT_POINTS offsets in the margin array.
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    " current code = %d OdtLegsDis = %d Rleg = %d CurrentVref = %d  StartDqs = %d StopDqs = %d StartDq = %d StopDq = %d\n",
    CurrentCompUp,
    OdtLegsDis,
    Rleg,
    CurrentVrefUp,
    StartDqs,
    StopDqs,
    StartDq,
    StopDq
    );

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParamDqs,
    ARRAY_COUNT (OptParamDqs),
    FullGrid,
    TestList,
    TestListSize,
    Scale,
    NULL,
    &StartDqs,
    &StopDqs,           // Stop
    OPT_PARAM_LOOP_COUNT + 2, // Loopcount increased from 15 to better match RMT margins
    1,              // Repeats
    0,              // NoPrint
    0,              // SkipOptUpdate
    RdTATestType,   // RdRd2Test
    0,              // GuardBand
    BasicVA         // PatType
    );

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParamDq,
    ARRAY_COUNT (OptParamDq),
    FullGrid,
    TestList,
    TestListSize,
    Scale,
    NULL,
    &StartDq,
    &StopDq,        // Stop
    OPT_PARAM_LOOP_COUNT + 2, // Loopcount increased from 15 to better match RMT margins
    1,              // Repeats
    0,              // NoPrint
    0,              // SkipOptUpdate
    RdTATestType,   // RdRd2Test
    0,              // GuardBand
    BasicVA         // PatType
    );

  DQTimeCentering1D (MrcData, RdV, 0, OPT_PARAM_LOOP_COUNT, FALSE, FALSE);
  DQTimeCentering1D (MrcData, RdT, 0, OPT_PARAM_LOOP_COUNT, FALSE, FALSE);

  return Status;
}

/**
  This function implements Write Slew Rate training.
  Optimize Write Slew Rate for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcWriteSlewRate (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { WrV, WrT };
  static const UINT8  Scale[]    = { 1, 2, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptSComp };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;
  MrcOutput          *Outputs;

  Outputs = &MrcData->Outputs;

  if (Outputs->Lpddr) {
      return mrcSuccess;
  }

  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    CustomSR,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,            // Start
    &Stop,             // Stop
    OPT_PARAM_1D_LC,
    1,                // Repeats
    0,                // NoPrint
    0,                // SkipOdtUpdate
    0,                // RdRd2Test
    0,                // GuardBand
    BasicVA           // PatType
    );

  return mrcSuccess;
}

/**
  Updates a given ch/Rank/byte combination with a new value for OptParam
  OptParam can be: WrDS, RdOdt, TComp, SComp, RxEq, TxEq, RxBias or DimmOdt
  OptParam == OptDefault restore values from Host except Dimms Odt's
  @param[in,out] MrcData         - Include all MRC global data.
  @param[in]     Channel         - Channel index to work on.
  @param[in]     Ranks           - Condenses down the results from multiple ranks
  @param[in]     Byte            - Byte index to work on.
  @param[in]     OptParam        - Defines the OptParam Offsets.
                                   Supported OptParam = [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 4: TxEq,
                                                         5: RxEq, 6: RxBias, 7: DimmOdt, 8: DimmOdtWr]
  @param[in]     Off             - Offset
  @param[in]     UpdateHost      - Desides if MrcData has to be updated

  @retval Nothing
**/
void
UpdateOptParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN           UINT8          Ranks,
  IN     const UINT8          Byte,
  IN           UINT8          OptParam,
  IN     INT16                Off,
  IN     const UINT8          UpdateHost
  )
{

  UINT16         *DimmOptParamVals;
  UINT8           NumDimmOptParamVals;

  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  INT64           GetSetVal;
  UINT8           GsmMode;
  BOOLEAN         Type;
  BOOLEAN         OptDimmParam;
  BOOLEAN         Lpddr;
  UINT8           RankMask;
  UINT8           Rank;
  UINT8           Index;
  INT16           TempOff;
  UINT32          Offset;
  INT16           OffCode;
  INT16           OffMin;
  INT16           OffMax;
  MrcStatus       Status;
  DATA_CR_DDRCRDATACONTROL5_STRUCT DdrCrDataControl5;
  DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  CH0CCC_CR_DDRCRCTLCACOMPOFFSET_STRUCT DdrCrCmdOffsetComp;
  CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_STRUCT DdrCrClkOffsetComp;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Lpddr         = Outputs->Lpddr;
  ChannelOut    = &Outputs->Controller[0].Channel[Channel];
  if (OptParam == OptVddq) {
    GsmMode = (UpdateHost) ? ForceWriteOffsetCached : ForceWriteOffsetUncached;
  } else {
    GsmMode = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;
  }
  GsmMode |= GSM_READ_CSR; // We are updating multiple params in the same register without updating the cache, so we are forced to read the CSRs now.
  GsmMode |= (OptParam == OptDefault) ? ForceWriteOffsetUncached : 0;
  if (OptParam == OptTxDqTco || OptParam == OptTxDqsTco) {
    // Sweep TCO comp using step size of 8
    GetSetVal = TCO_COMP_STEP * Off;
  } else if (OptParam == OptClkTco) {
    // Sweep TCO comp using step size of 2
    GetSetVal = CLK_TCO_COMP_STEP * Off;
  } else if (OptParam == OptVddq) {
    // Sweep Vddq with a step size of -4 for now (sweep from high to low unlike all other params)
    GetSetVal = -VDDQ_STEP * Off;
  } else {
    GetSetVal = Off;
  }

  // Update OptParamOffset is not currently used for setting ODT parameter; code is kept for possible future usage.
  // DIMM ODT setting is performed using UpdateOptPointValues
  OptDimmParam = ((OptParam == OptDimmRon) ||
    (OptParam == OptDimmOdtWr) ||
    (OptParam == OptDimmOdtNom) ||
    (OptParam == OptDimmOdtPark) ||
    (OptParam == OptDimmOdtParkNT) ||
    (OptParam == OptDimmOdtNomNT) ||
    (OptParam == OptDimmOdtCA)
    );

  // Compensation Offsets
  Type =
    (
      // Dq Comp Offsets
      (OptParam == OptWrDS) ||
      (OptParam == OptCmdDS) ||
      (OptParam == OptCmdDSUp) ||
      (OptParam == OptCmdDSDn) ||
      (OptParam == OptWrDSUp) ||
      (OptParam == OptWrDSDn) ||
      (OptParam == OptWrDSUpCoarse) ||
      (OptParam == OptWrDSDnCoarse) ||
      (OptParam == OptCmdDSUpCoarse) ||
      (OptParam == OptCmdDSDnCoarse) ||
      (OptParam == OptRdOdt) ||
      (OptParam == OptRdDqOdt) ||
      (OptParam == OptRdDqsOdt) ||
      (OptParam == OptRdOdtUp) ||
      (OptParam == OptRdOdtDn) ||
      (OptParam == OptRxLoad) ||
      (OptParam == OptSComp) ||
      (OptParam == OptCCCSComp) ||
      // TCO Comp overrides
      (OptParam == OptTxDqTco) ||
      (OptParam == OptTxDqsTco) ||
      (OptParam == OptClkTco) ||
      (OptParam == OptTCompOff) ||
      (OptParam == OptDefault)
    );
  if (Type) {
    if (OptParam == OptClkTco) {
      // Clk TCO Comp override
      MrcGetSetNoScope (MrcData, TcoCompCodeClk, GsmMode, &GetSetVal);
      MrcGetSetNoScope (MrcData, TcoCompCodeCmd, GsmMode, &GetSetVal);
      MrcGetSetNoScope (MrcData, TcoCompCodeCtl, GsmMode, &GetSetVal);
    } else if (OptParam == OptTxDqTco) {
      MrcGetSetChStrb (MrcData, CONTROLLER_0, Channel, Byte, TxTco, GsmMode, &GetSetVal);
    } else if (OptParam == OptTxDqsTco) {
      // TGL_POWER_TRAINING create case in the get/set interface for DDRDATA_CR_DDRCRDataTcoControl1_0_0_0_MCHBAR.DQSTcocomp
      //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, TxDqsTco, GsmMode, &GetSetVal);
    } else {
      // Dq/CCC Comp offset
      if ((OptParam == OptWrDS) ||
        (OptParam == OptWrDSUp) ||
        (OptParam == OptWrDSDn)) {
        OffMin = -32;
        OffMax = 31;
      } if ((OptParam == OptCmdDS) ||
           (OptParam == OptCmdDSUp) ||
           (OptParam == OptCmdDSDn)) {
        OffMin = -8;
        OffMax = 7;
      } else if ((OptParam == OptWrDSUpCoarse) ||
                 (OptParam == OptWrDSDnCoarse)) {
        OffMin = -32 / WR_DS_STEP;
        OffMax = 31 / WR_DS_STEP;
      } else if ((OptParam == OptCmdDSUpCoarse) ||
                 (OptParam == OptCmdDSDnCoarse)) {
        OffMin = -8 / CCC_DS_STEP;
        OffMax = 7 / CCC_DS_STEP;
      } else if (OptParam == OptSComp) {
        OffMin = -17; // -17 for SR dis.
        OffMax = 15;
      } else if (OptParam == OptCCCSComp) {
          OffMin = -17; // -17 for SR dis, min is actually -8.
          OffMax = 7;
      } else {
        OffMin = -16;
        OffMax = 15;
      }

      if (Off > OffMax) {
        Off = OffMax;
      } else if (Off < OffMin) {
        Off = OffMin;
      }

      DdrCrDataControl5.Data = 0; // TGL_POWER_TRAINING Add a per-byte channel cache variable for this
      DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
      DdrCrCmdOffsetComp.Data = ChannelOut->CmdCompOffset;
      DdrCrClkOffsetComp.Data = ChannelOut->ClkCompOffset;

      if (OptParam == OptWrDS) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
      } else if (OptParam == OptRdOdt || OptParam == OptRdDqsOdt) {
        DdrCrDataControl5.Bits.DqsOdtCompOffset = Off;
      } else if (OptParam == OptRdOdt || OptParam == OptRdDqOdt) {
        DdrCrDataOffsetComp.Bits.DqOdtCompOffset = Off;
      } else if (OptParam == OptSComp) {
        if (Off == -17) {
          // Just picked value outside SR range.
          GetSetVal = 1;
        } else {
          DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset = Off;
          GetSetVal = 0;
        }
        MrcGetSetChStrb (MrcData, CONTROLLER_0, Channel, Byte, GsmIocDqSlewDlyByPass, GsmMode, &GetSetVal);
      } else if (OptParam == OptCCCSComp) {
          if (Off == -17) {
              // Just picked value outside SR range.
              GetSetVal = 1;
          } else {
              DdrCrCmdOffsetComp.Bits.CaScompOffset = Off;
              DdrCrCmdOffsetComp.Bits.CtlScompOffset = Off;
              DdrCrClkOffsetComp.Bits.ClkScompOffset = Off;
              GetSetVal = 0;
          }
          // TGL_POWER_TRAINING Get/Set needs to support setting DDRCRPINSUSED.DdrClkSlwDlyBypass/DdrCaSlwDlyBypass/DdrCtlSlwDlyBypass
          //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocCmdSlewDlyByPass, GsmMode, &GetSetVal);
          //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocCtlSlewDlyByPass, GsmMode, &GetSetVal);
          //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocClkSlewDlyByPass, GsmMode, &GetSetVal);
      } else if (OptParam == OptWrDSDn) {
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
      } else if (OptParam == OptWrDSUp) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
      } else if (OptParam == OptWrDSDnCoarse) {
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = WR_DS_STEP * Off;
      } else if (OptParam == OptWrDSUpCoarse) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = WR_DS_STEP * Off;
      } else if (OptParam == OptCmdDS) {
        DdrCrCmdOffsetComp.Bits.CaRcompDrvDownOffset = Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvDownOffset = Off;
        DdrCrCmdOffsetComp.Bits.CaRcompDrvUpOffset = Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvUpOffset = Off;
      } else if (OptParam == OptCmdDSUp) {
        DdrCrCmdOffsetComp.Bits.CaRcompDrvUpOffset = Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvUpOffset = Off;
      } else if (OptParam == OptCmdDSUpCoarse) {
        DdrCrCmdOffsetComp.Bits.CaRcompDrvUpOffset = CCC_DS_STEP * Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvUpOffset = CCC_DS_STEP * Off;
      } else if (OptParam == OptCmdDSDn) {
        DdrCrCmdOffsetComp.Bits.CaRcompDrvDownOffset = Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvDownOffset = Off;
      } else if (OptParam == OptCmdDSDnCoarse) {
        DdrCrCmdOffsetComp.Bits.CaRcompDrvDownOffset = CCC_DS_STEP * Off;
        DdrCrCmdOffsetComp.Bits.CtlRcompDrvDownOffset = CCC_DS_STEP * Off;
      } else if (OptParam == OptRxLoad) {
        DdrCrDataOffsetComp.Bits.RloadOffset = RX_LOAD_STEP * Off;
      } else if (OptParam == OptRdOdtUp) {
        //DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset    = Off;
      } else if (OptParam == OptRdOdtDn) {
        //DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset  = Off;
      }
      if (OptParam == OptCmdDSDnCoarse || OptParam == OptCmdDSUpCoarse || OptParam == OptCmdDS || OptParam == OptCmdDSUp || OptParam == OptCmdDSDn || OptParam == OptCCCSComp) {
          // TGL_POWER_TRAINING Need to add the method MrcGetOffsetCmdOffsetComp() to get the offset of DDRCCC_CR_DDRCRCTLCACOMPOFFSET_0_0_0_MCHBAR
          Offset = 0; //MrcGetOffsetCmdOffsetComp (MrcData, Channel);
          MrcWriteCR (MrcData, Offset, DdrCrCmdOffsetComp.Data);
          if (UpdateHost) {
              ChannelOut->CmdCompOffset = DdrCrCmdOffsetComp.Data;
          }
          if (OptParam == OptCCCSComp) {
                // TGL_POWER_TRAINING Need to add the method MrcGetOffsetClkOffsetComp() to get the offset of DDRCCC_CR_DDRCRVSSHICLKCOMPOFFSET_0_0_0_MCHBAR
                Offset = 0; //MrcGetOffsetCmdOffsetComp (MrcData, Channel);
                MrcWriteCR (MrcData, Offset, DdrCrClkOffsetComp.Data);
                if (UpdateHost) {
                    ChannelOut->ClkCompOffset = DdrCrClkOffsetComp.Data;
                }
          }
      } else if (OptParam == OptRdOdt || OptParam == OptRdDqsOdt) {
          Offset = 0; // TGL_POWER_TRAINING  MrcGetOffsetDdrCrDataControl5 (MrcData, Channel, Byte);
          MrcWriteCR (MrcData, Offset, DdrCrDataControl5.Data);
          if (UpdateHost) {
              ; // TGL_POWER_TRAINING Add cache: ChannelOut->DdrCrDataControl5[Byte] = DdrCrDataControl5.Data;
          }
      } else {
          Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
          MrcWriteCR (MrcData, Offset, DdrCrDataOffsetComp.Data);
          if (UpdateHost) {
              ChannelOut->DataCompOffset[Byte] = DdrCrDataOffsetComp.Data;
          }
      }
    }

    GetSetVal = 1;
    MrcGetSetChStrb (MrcData, CONTROLLER_0, Channel, Byte, GsmIocInternalClocksOn, ForceWriteCached, &GetSetVal);
    // Propagate new value and force comp update
    MrcGetSetNoScope (MrcData, GsmIocForceCmpUpdt, ForceWriteUncached, &GetSetVal);

    GetSetVal = 0;
    MrcGetSetChStrb (MrcData, CONTROLLER_0, Channel, Byte, GsmIocInternalClocksOn, ForceWriteCached, &GetSetVal);
    ForceRcomp(MrcData);
  }

  if ((Lpddr) && ((OptParam == OptRdOdt) || (OptParam == OptRdDqOdt) || (OptParam == OptRdDqsOdt) || (OptParam == OptRdOdtUp) || (OptParam == OptRdOdtDn))) {
    // Readjust SOC ODT for each change in RdOdt
    Lpddr4UpdateSocOdt (MrcData);
  }
  // Equalization Settings
  Type = ((OptParam == OptTxEq) || (OptParam == OptRxEq) || (OptParam == OptRxC) || (OptParam == OptRxR) || (OptParam == OptDFETap0) || (OptParam == OptDFETap1) || (OptParam == OptDefault));
  if (Type) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) && ((Ranks & (MRC_BIT0 << Rank)))) {
        if (OptParam == OptTxEq) {
          if (Inputs->UlxUlt) {
            // Update setting for 2 segments (ULX/ULT), range up to 10 legs vs. 3 segments (DT/Halo), range up to 15 legs
            // Map setting [0..10] to [0..15] range while skipping settings that are not used
            TempOff = Off + (Off - 1) / 2;
          } else {
            TempOff = Off;
          }
          if (TempOff > 15) {
            TempOff = 15;
          }

          if (TempOff < 0) {
            TempOff = 0;
          }
          OffCode = TempOff;
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel=%d,Rank= %d update to %x \n",Channel,Rank,OffCode);
          GetSetVal = OffCode;
          // TGL_POWER_TRAINING make sure that this get/set disables TxEq for the given byte if it's set to 0 across all ranks on the given channel (via DDRDATA_CR_DDRCrDataControl2_0_0_0_MCHBAR.TxEqDis) to save power (and make sure TxEq is enabled if set to a non-zero value)
          MrcGetSetStrobe (MrcData, CONTROLLER_0, Channel, Rank, Byte, TxEq, WriteCached, &GetSetVal);
        }
        if (OptParam == OptRxEq) {
          if (Off <= 0) {
            Off = 0;
          } else {
            if (Off > 15) {
              Off = 15;
            }
          }
          GetSetVal = Off;
          // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl4_0_0_0_MCHBAR.RxEqRank0/1/2/3 bits 4:7
          MrcGetSetStrobe (MrcData, CONTROLLER_0, Channel, Rank, Byte, RxEq, GsmMode, &GetSetVal);
        }
        if (OptParam == OptRxC) {
            if (Off <= 0) {
                Off = 0;
            } else {
                if (Off > 3) {
                    Off = 3;
                }
            }
            GetSetVal = Off;
            // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl4_0_0_0_MCHBAR.RxEqRank0/1/2/3 bits 0:1
            //MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxC, GsmMode, &GetSetVal);
        }
        if (OptParam == OptRxR) {
            if (Off <= 0) {
                Off = 0;
            } else {
                if (Off > 3) {
                    Off = 3;
                }
            }
            GetSetVal = Off;
            // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl4_0_0_0_MCHBAR.RxEqRank0/1/2/3 bits 2:3
            //MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxR, GsmMode, &GetSetVal);
        }
        if (OptParam == OptDFETap0) {
            if (Off <= 0) {
                Off = 0;
            } else {
                if (Off > 7) {
                    Off = 7;
                }
            }
            GetSetVal = Off;
            // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl4_0_0_0_MCHBAR.RxEqRank0/1/2/3 bits 0:3
            //MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxTap0, GsmMode, &GetSetVal);
        }
        if (OptParam == OptDFETap1) {
            if (Off <= 0) {
                Off = 0;
            } else {
                if (Off > 7) {
                    Off = 7;
                }
            }
            GetSetVal = Off;
            // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl4_0_0_0_MCHBAR.RxEqRank0/1/2/3 bits 4:7
            //MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxTap1, GsmMode, &GetSetVal);
        }

        if (OptParam == OptDefault) {
          GetSetVal = 0;
          MrcGetSetStrobe (MrcData, CONTROLLER_0, Channel, Rank, Byte, RecEnDelay, GsmMode, &GetSetVal);
        }
      }
    }
  }

  // Equalization Settings
  Type = (OptParam == OptCmdTxEq);
  if (Type) {
    if (OptParam == OptCmdTxEq) {
       TempOff = Off;
       if (TempOff > 15) {
         TempOff = 15;
       }
       if (TempOff < 0) {
         TempOff = 0;
       }
       OffCode = TempOff;

       // For CCC, the 5th bit TxEq[4] = !(DDR4). If DDR4, set to 0, else 1. High equalizations save power for DDR4 but cost power for other modes.
       if (Lpddr) {
         OffCode |= 0x16;
       } else {
         OffCode &= 0<<4;
       }

       //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel=%d,Rank= %d update to %x \n",Channel,Rank,OffCode);
       GetSetVal = OffCode;
       // TGL_POWER_TRAINING make sure that this get/set supports DDRCCC_CR_DDRCRCCCCLKCONTROLS_0_0_0_MCHBAR.CtlTxEq/CaTxEq. If either is set to 0, disable that particular TxEq (if registers exist to do this).
       //MrcGetSetDdrIoGroupChannel (MrcData, Channel, CmdTxEq, WriteCached, &GetSetVal);
       //MrcGetSetDdrIoGroupChannel (MrcData, Channel, CtlTxEq, WriteCached, &GetSetVal);
    }
  }

  // RxCb Amplifier BIAS
  if ((OptParam == OptRxCb) || (OptParam == OptDefault)) {
    if (Off > 0xF) {
      Off = 0xF;
    }

    if (Off < 0) {
      Off = 0;
    }

    if (OptParam == OptRxCb) {
      GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    // TGL_POWER_TRAINING ddrdll_cr_pitune_0_0_0_mchbar.PiCbEn
    //    When this register is set, the following registers need the 4-bit value copied over to them as side effects in the Get/Set function:
    //    DRDATA_CR_DDRCrDataControl6_0_0_0_MCHBAR.RxD0PICB - Rx D0 PI
    //    DRDATA_CR_DDRCrDataControl6_0_0_0_MCHBAR.SDLL_PICB - SDLL PI
    //    DDRComp_CR_DdrCrVccDLLReplicaCtrl2.RxD0PICB - RX D0 PI in the VccDLL replica
    //    DDRComp_CR_DdrCrVccDLLReplicaCtrl2.SDLLPICB - SDLL in the VccDLL replica
    // MrcGetSetDdrIoGroupController0 (MrcData, RxCben, GsmMode, &GetSetVal);
  }

  // RX Amplifier BIAS IRef
  if ((OptParam == OptRxBias) || (OptParam == OptDefault)) {
    if (OptParam == OptRxBias) {
      GetSetVal = Off * RX_BIAS_STEP;
    } else {
      GetSetVal = 0;
    }

    // TGL_POWER_TRAINING - DDRDATA_CR_DDRCrDataControl5_0_0_0_MCHBAR.BiasIrefAdj
    //                      DDRCCC_CR_DDRCRBSCANDATA_0_0_0_MCHBAR.BiasIrefAdj needs value copied over to it.
    // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasCtl, GsmMode, &GetSetVal);
  }

  // RxVref Vtt/Vddq Decap
  if ((OptParam == OptRxVrefVttDecap) || (OptParam == OptRxVrefVddqDecap) || (OptParam == OptDefault)) {
    if (OptParam == OptRxVrefVttDecap || OptParam == OptRxVrefVddqDecap) {
      GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    if (OptParam == OptRxVrefVttDecap || OptParam == OptDefault) {
      // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl2_0_0_0_MCHBAR.RxVrefVttProgMFC
      //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVrefVttDecap, GsmMode, &GetSetVal);
    }
    if (OptParam == OptRxVrefVddqDecap || OptParam == OptDefault) {
      // TGL_POWER_TRAINING DDRDATA_CR_DDRCrDataControl2_0_0_0_MCHBAR.RxVrefVddqProgMFC
      //MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVrefVddqDecap, GsmMode, &GetSetVal);
    }
  }

  // VccDLL Bypass
  if ((OptParam == OptVccDLLBypass) || (OptParam == OptDefault)) {
    if (OptParam == OptVccDLLBypass) {
          GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    // TGL_POWER_TRAINING DDRDLL_CR_DdrCrVccDLLFFControl.Bypass & DDRVccDLLReg_CR_DdrCrVccDLLControl.Bypass
    // MrcGetSetDdrIoGroupController0 (MrcData, VccDLLByPass, GsmMode, &GetSetVal);
  }
  // PanicVttDnLp
  if ((OptParam == OptPanicVttDnLp) || (OptParam == OptDefault)) {
    if (OptParam == OptPanicVttDnLp) {
      GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    // TGL_POWER_TRAINING DDRComp_CR_DdrCrCompVttPanic2.VttPanicCompDnLPMult
    // MrcGetSetDdrIoGroupController0 (MrcData, PanicVttDnLp, GsmMode, &GetSetVal);
  }

  // Vddq
  if ((OptParam == OptVddq) || (OptParam == OptDefault)) {
    if (OptParam == OptVddq) {
       GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    // TGL_POWER_TRAINING Need to set Vddq via FIVR register:
    // MC_BIOS_REQ_PCU.REQ_VOLTAGE_DATA -> Set by MRC, read by Pcode (11 bits, 2.5 mV per tick)
    // MC_BIOS_DATA.VDDQ_TX_VOLTAGE -> Set by Pcode to what was actually requested from FIVR (may not be the same as what MRC requested)(11 bits, 2.5 mV per tick)
    // MAILBOX_BIOS_CMD_READ_BIOS_MC_REQ_ERROR -> Set by Pcode, read by MRC to see if there are any error codes indicating problems during setting Vddq. BIOS should retry or throw an error if this occurs.
    // Details for how to set Vddq in BIOS are here: https://sharepoint.amr.ith.intel.com/sites/tgldoc/tglhas/Shared%20Documents/Power%20Management%20and%20Delivery/Features/Vddq_tx%20FIVR/Vddq_tx%20FIVR.html#active-power-management
    // TGL_POWER_TRAINING There are some PHY init settings that depend on the Vddq setting, and those need to be copied from the PHY init and added to a function that is called as a side effects of the Vddq get/set.
    // MrcGetSetDdrIoGroupController0 (MrcData, Vddq, GsmMode, &GetSetVal);
  }

  if (OptDimmParam) {
    // Get corresponding Ranks for Non-Target DIMMs for OptDimmOdtParkNT and OptDimmOdtNomNT
    if ((OptParam == OptDimmOdtParkNT) || (OptParam == OptDimmOdtNomNT)) {
      Ranks = DIMM_TO_RANK_MASK(MrcGetOtherDimm (MrcData, Channel, Ranks));
      if (OptParam == OptDimmOdtNomNT) {
        OptParam = OptDimmOdtNom;
      } else {
        OptParam = OptDimmOdtPark;
      }
    }
    RankMask = MrcData->Outputs.ValidRankMask;
    Status = GetDimmOptParamValues (MrcData, OptParam, &DimmOptParamVals, &NumDimmOptParamVals);
    if (Status == mrcSuccess) {
      Index = (UINT8) Off;
      if (OptParam == OptDimmOdtCA) {
        SetDimmParamValue (MrcData, CONTROLLER_0, Channel, Ranks & RankMask, OptParam, DimmOptParamVals[Index], 1);
      } else if (DimmOptParamVals != NULL){
        SetDimmParamValue (MrcData, CONTROLLER_0, Channel, Ranks & RankMask, OptParam, DimmOptParamVals[Index], UpdateHost);
      }
    }
  }

  return;
}

/**
  Slightly penalize any Asymmetry in margin

  @param[in] NegEdge - Negative edge of the margin
  @param[in] PosEdge - Positive edge of the margin

  @retval p2p - Width/Height reduced by the asymmetric difference in margin.
**/
UINT16
EffectiveMargin (
  IN const UINT16 NegEdge,
  IN const UINT16 PosEdge
  )
{
  INT16 p2p;
  UINT16 p2pDiff;

  p2p     = 2 * (PosEdge + NegEdge);
  p2pDiff = PosEdge - NegEdge;

  if (PosEdge > NegEdge) {
    p2p -= p2pDiff;
  } else {
    p2p += p2pDiff;
  }

  return p2p / 2;
}

/**
  This function does a running average on Margins in two dimentional fashion.

  @param[in,out] Margins - Margins to average in a 1D array.
  @param[in]     MLen    - Determines the Y-Dimension lengths
  @param[in]     XDim    - Determines the X-Dimension lengths
  @param[in]     XMin    - Used to skip the first elements in the Margin when averaging.
  @param[in]     CScale  - Used to place more weight on the center point.

  @retval Nothing
**/
void
RunningAverage2D (
  IN OUT UINT16       Margins[MAX_OPT_POINTS],
  IN     const UINT8  MLen,
  IN     const UINT8  XDim,
  IN     const UINT8  XMin,
  IN     const UINT8  CScale
)

{
  UINT8  XMax;
  UINT8  YMax;
  UINT16 TMargins[MAX_OPT_POINTS];
  UINT8  i;
  UINT8  x;
  UINT8  y;
  UINT8  xo;
  UINT8  yo;
  UINT8  XOff;
  INT8   YOff;

  if (MLen == 1) {
    return;
  }
  XMax  = XDim - 1;
  YMax  = ((MLen + XDim - 1) / XDim) - 1; // Ceiling to int in case the matrix is not fully populated

  for (i = 0; i < MLen; i++) {
    x = (i % XDim);
    y = (i / XDim);

    // Center Point
    TMargins[i] = Margins[i] * (CScale - 1); // Also add margin at the centerpoint below
    // Sum up surrounding results
    for (xo = 0; xo < 3; xo++) {
      XOff = x + xo - 1;
      // Avoid negative numbers on XOff
      if ((x == 0) && (xo == 0)) {
        XOff = 0;
      }
      // (x < XMin) allows averaging across points (1;0) and (2;0)
      if ((XOff < XMin) && (x < XMin)) {
        XOff = x; // RxEq special case.  Skip averaging on Col0/Col1
      }

      if (XOff > XMax) {
        XOff = XMax;
      }

      for (yo = 0; yo < 3; yo++) {
        YOff = y + yo - 1;
        if (YOff < 0) {
          YOff = 0;
        }

        if (YOff > YMax) {
          YOff = YMax;
        }
        // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
        if ((XDim * YOff + XOff) > (MLen - 1)) {
          YOff = YOff - 1;
        }

        TMargins[i] += Margins[XDim * YOff + XOff];
      }
    }
  }
  // Copy TempMargins back over to real margins
  for (i = 0; i < MLen; i++) {
    Margins[i] = TMargins[i] / (8 + CScale); // Added div to maintain margin scaling
  }

  return;
}

/**
  This function does a running average on Margins in two dimentional fashion.

  @param[in,out] Margins - Margins to average
  @param[in]     Test    - Selects the Margins to average
  @param[in]     MLen    - Determines the Y-Dimension lengths
  @param[in]     XDim    - Determines the X-Dimension lengths
  @param[in]     XMin    - Used to skip the first elements in the Margin when averaging.
  @param[in]     CScale  - Used to place more weight on the center point.

  @retval Nothing
**/
void
Fill2DAverage (
  IN     MrcParameters *const MrcData,
  IN OUT UINT16               Margins[2][MAX_OPT_POINTS],
  IN     const UINT8          Test,
  IN     const UINT8          MLen,
  IN     const UINT8          XDim,
  IN     const UINT8          XMin,
  IN     const UINT8          CScale
)
{
  UINT8  XMax;
  UINT8  YMax;
  UINT16 TMargins[MAX_OPT_POINTS];
  UINT8  i;
  UINT8  x;
  UINT8  y;
  UINT8  xo;
  UINT8  yo;
  UINT8  XOff;
  INT8   YOff;
  UINT8  Edge;
  INT16  Gradient;
  INT16  MaxGradient;

  XMax  = XDim - 1;
  YMax  = ((MLen + XDim - 1) / XDim) - 1; // Ceiling to int in case the matrix is not fully populated

  for (i = 0; i < MLen; i++) {
    if (Margins[Test][i]) { // skip already populated entries
    continue;
    }

    x = (i % XDim);
    y = (i / XDim);
    Edge = 0;

//     if (i == 14)
//       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Margins[%d][%d]=%d\n", x, y, Test, i, Margins[Test][i]);

    // Center Point
    TMargins[i] = Margins[Test][i] * (CScale - 1); // Also add margin at the centerpoint below
    // Sum up surrounding results
    for (xo = 0; xo < 3; xo += 2) {
      XOff = x + xo - 1;
      // Avoid negative numbers on XOff
      if (((INT8) XOff) < 0) {
        //XOff = 0;
        Edge++;
        continue;
      }
      // (x < XMin) allows averaging across points (1;0) and (2;0)
      if ((XOff < XMin) && (x < XMin)) {
        XOff = x; // RxEq special case.  Skip averaging on Col0/Col1
      }

      if (XOff > XMax) {
        //XOff = XMax;
        Edge++;
        continue;
      }
      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      if ((XDim * y + XOff) > (MLen - 1)) {
        Edge++;
        continue;
      }
      TMargins[i] += Margins[Test][XDim * y + XOff];
//       if (i == 14)
//         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    for (yo = 0; yo < 3; yo += 2) {
      YOff = y + yo - 1;
      if (YOff < 0) {
        // YOff = 0;
        Edge++;
        continue;
      }

      if (YOff > YMax) {
        // YOff = YMax;
        Edge++;
        continue;
      }

      TMargins[i] += Margins[Test][XDim * YOff + x];
//       if (i == 14)
//         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    // Copy TempMargins back over to real margins
//     if (Edge > 0) {
//       Margins[Test][i] = Margins[Test][i] * 8 / 10; // Penalize the edges by decreaseing margin by 20%
//     }
    Margins[Test][i] = TMargins[i] / (4 - Edge + CScale - 1); // Added div to maintain margin scaling
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Margins[%d][i]=%d Edge=%d\n", x, y, i, TMargins[i], Test, Margins[Test][i], Edge);
  }

  // penalize for high margin gradient
  for (i = 0; i < MLen; i++) {
    x = (i % XDim);
    y = (i / XDim);
    MaxGradient = 0;
    // Sum up surrounding results
    for (xo = 0; xo < 3; xo += 2) {
      XOff = x + xo - 1;
      // Avoid negative numbers on XOff
      if ((x == 0) && (xo == 0)) {
        XOff = 0;
      }
      if (XOff > XMax) {
        XOff = XMax;
      }
      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      if ((XDim * y + XOff) > (MLen - 1)) {
        XOff = XOff - 1;
      }
      Gradient = Margins[Test][XDim * y + x] - Margins[Test][XDim * y + XOff];
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Gradient=%d Margins[Test][XDim * y + x] = %d Margins[Test][XDim * y + XOff] = %d XOff = %d\n",x, y, Gradient, Margins[Test][XDim * y + x], Margins[Test][XDim * y + XOff], XOff);
      if (Gradient > MaxGradient) {
        // if we loose margin update MaxGradient
        MaxGradient = Gradient;
      }
    }
    for (yo = 0; yo < 3; yo += 2) {
      YOff = y + yo - 1;
      if (YOff < 0) {
        YOff = 0;
      }

      if (YOff > YMax) {
        YOff = YMax;
      }

      // Avoid averaging with unpopulated matrix elements when dealing with partially populated matrices
      if ((XDim * YOff + x) > (MLen - 1)) {
        YOff = YOff - 1;
      }

      Gradient = (Margins[Test][XDim * y + x] - Margins[Test][XDim * YOff + x]);
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d Gradient=%d Margins[Test][XDim * y + x] = %d Margins[Test][XDim * y + XOff] = %d YOff = %d\n",x, y, Gradient, Margins[Test][XDim * y + x], Margins[Test][XDim * y + YOff], YOff);
      if (Gradient > MaxGradient) {
        MaxGradient = Gradient;
      }
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d TMargins[%d]=%d Edge=%d\n", x, y, i, TMargins[i],Edge);
    }
    // save MaxGradient in Temp array and clip for max margin.
    if (MaxGradient > Margins[Test][i]) {
      MaxGradient = Margins[Test][i];
    }
    TMargins[i] = MaxGradient;
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "x=%d y=%d  Margins[%d][%d]=%d MaxGradient=%d \n", x, y, i, Test, Margins[Test][i], TMargins[i]);
  }
  // apply the MaxGradient to Original array
  for (i = 0; i < MLen; i++) {
    Margins[Test][i] -= TMargins[i];
  }
  return;
}

/**
  This function takes in 2D array of Margins: MarginType / Parameter Index.
  This index to the array represents some arbitrary parameter value that we are optimizing.
  The function will look for up to MAX_TRADEOFF_TYPES entries to optimize on.
  OptResultByte will store the results of the optimization, and various other data.

  In addition to optimizing for margin, this function can also optimize for power.
  GoodPowerLimit is an array that sets level where power is more important than margin.
    i.e. Any points where ((Margin[0]>GoodPowerLimit[0]) & (Margin[1]>GoodPowerLimit[1]) & ... )
  To avoid overflow, this function will automatic scale margins to fit in UINT64

  @param[in]     MrcData          - The global MRC data structure.
  @param[in,out] OptResultByte    - Structure containing the optimized results.
  @param[in]     InputMargins     - Margins we are optimizing
  @param[in]     MarginsLength    - The length of InputMargins
  @param[in]     LenMargin        - The length of InputMargins we are optimizing (0 - LenMargin -1).
  @param[in]     Scale            - Controls the relative importance on Margins[0] vs. [1] ...
                                      ex: To make Margins[0] twice as important, set Scale = [1, 2, 2, 2, 2].
                                      Since the search optimizes the lowest margin, increasing [1:4] makes 0 more important.
                                      This function can be used to optimize only Margin[0] by setting Scale = [1, 0, 0, 0, 0].
  @param[in]     UPMOptimize      - Optimize only for UPM limit for selected params, so if they pass UPM they do not affect the score.
  @param[in]     EnSq             - Enables the square root term in the optimization functions to make the tradeoff steeper.
  @param[in]     AveN             - The number of points used for the averaging filter.
  @param[in]     IncEnds          - Controls if the endpoints are to be included.
  @param[in]     ScaleM           - Controls the scaling of the middle point in 1-D average filter.
  @param[in]     GoodPowerLimit   - The power limit above which we only trade-off for power and not margin.
  @param[in]     OptimizationMode - 0:    Returns first good margin limit point.
                                    1-4:  Return the first index that meets GoodPowerLimit and lowest power.
                                            OptimizationMode is power column index.
                                    5-99: Return the index that meets GoodPowerLimit and >= % of the Max Optimization result.
                                    >100: Returns the highest Optimization Result.
  @param[in]     GuardBand        - Signed offest to check if margin drop is acceptable.  Save good guardband
                                    in OptResultByte.

  @retval Nothing.
**/
void
FindOptimalTradeOff (
  IN     MrcParameters      *const  MrcData,
  IN OUT OptResultsPerByte          *OptResultByte,
  IN     UINT16                     *InputMargins,
  IN     UINT8                      MarginsLength,
  IN     UINT8                      LenMargin,
  IN     const UINT8                Scale[MAX_TRADEOFF_TYPES],
  IN     const UINT8                UPMOptimize[MAX_TRADEOFF_TYPES],
  IN     UINT8                      EnSq,
  IN     UINT8                      AveN,
  IN     UINT8                      IncEnds,
  IN     UINT8                      ScaleM,
  IN     UINT16                     GoodPowerLimit[],
  IN     UINT8                      OptimizationMode,
  IN     INT8                       GuardBand
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  UINT32               PostMar[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS];
  UINT32               SMaxPost[MAX_TRADEOFF_TYPES];
  UINT32               MaxPost[MAX_TRADEOFF_TYPES];
  UINT32               MinPost[MAX_TRADEOFF_TYPES];
  UINT16               GoodPwrLimitPost[MAX_TRADEOFF_TYPES];
  UINT32               ScaleMin;
  UINT8                Nby2;
  UINT8                EqOrder;
  UINT8                MarginArray;
  UINT8                yArr;
  UINT8                x;
  UINT8                i;
  UINT8                Off;
  INT16                xEff;
  UINT8                NumBits;
  UINT32               localY;
  UINT8                Shift;
  UINT8                Adder;
  UINT8                Start;
  UINT8                Stop;
  UINT64               Result;
  UINT64               LocalResult;
  UINT64               MaxR;
  UINT64               MarginLimit;
  UINT8                BestX;
  UINT8                PowerX;
  UINT8                FoundPwrOpt;
  UINT8                NumCalcArr;
  INT8                 StepSize;
  UINT8                MarginDropPercent;
  UINT32               MinPost1;
  BOOLEAN              GoodPower;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Debug             = &MrcData->Outputs.Debug;
  MarginDropPercent = 10;  // 10% loss of margin is a bad guardband offset.
  EqOrder           = 0; // Is the optimization equation: X^1, X^2, X^5
  Result            = 0;
  MaxR              = 0;
  BestX             = 0;
  PowerX            = 0;
  FoundPwrOpt       = 0;
  MrcCall->MrcSetMemDword (MaxPost, sizeof (MaxPost) / sizeof (UINT32), 1);
  MrcCall->MrcSetMemDword (SMaxPost, sizeof (SMaxPost) / sizeof (UINT32), 1);
  MrcCall->MrcSetMemDword (MinPost, sizeof (MinPost) / sizeof (UINT32), 0xFFFFFFFF);
  MrcCall->MrcSetMemWord (GoodPwrLimitPost, sizeof (GoodPwrLimitPost) / sizeof (UINT16), 0);
  MrcCall->MrcSetMem ((UINT8 *) PostMar, sizeof (PostMar), 0);
  MrcCall->MrcSetMem ((UINT8 *) OptResultByte, sizeof (OptResultsPerByte), 0);

  if (AveN <= 0) {
    AveN = 1;
  }
  Nby2    = (AveN >> 1);

  // Process Raw Margins Results with a running average filter of AveN
  for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
    // Scale GoodPowerLimit to match PostMar results
    GoodPwrLimitPost[MarginArray] = GoodPowerLimit[MarginArray] * (AveN + ScaleM - 1) * Scale[MarginArray];

    for (x = 0; x < LenMargin; x++) {
      if (Scale[MarginArray] == 0) {
        // Not in the game
        MinPost[MarginArray] = PostMar[MarginArray][x] = 1;
      } else {
        if (x == 0) {
          // Update EqOrder once for each MarginArray value with a non-zero scale factor.
          //   e.g.:so for {RdT,RdV,0,0} it will be = 2
          EqOrder += 1;
        }

        for (Off = 0; Off < AveN; Off++) {
          xEff = x + Off - Nby2;
          if (xEff < 0) {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + 0);  // InputMargins[MarginArray][0];
          } else if (xEff >= LenMargin) {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + LenMargin - 1);
          } else if (x == xEff) {
            PostMar[MarginArray][x] += ScaleM * *(InputMargins + MarginArray * MarginsLength + xEff);
          } else {
            PostMar[MarginArray][x] += *(InputMargins + MarginArray * MarginsLength + xEff);
          }
        }
        // save none scaled margins after avg filtering
        OptResultByte->Margins[MarginArray][x].EW = (UINT16) PostMar[MarginArray][x] / (AveN + ScaleM - 1);
        PostMar[MarginArray][x] *= Scale[MarginArray];
        if (MaxPost[MarginArray] < PostMar[MarginArray][x]) {
          MaxPost[MarginArray] = PostMar[MarginArray][x];
        }

        if (MinPost[MarginArray] > PostMar[MarginArray][x]) {
          MinPost[MarginArray] = PostMar[MarginArray][x];
        }
      }
    }

    if (Scale[MarginArray] == 0) {
      continue;
    }

    SMaxPost[MarginArray]               = MaxPost[MarginArray];
    OptResultByte->Scale[MarginArray]   = Scale[MarginArray];
    OptResultByte->MaxPost[MarginArray] = MaxPost[MarginArray] / (AveN + ScaleM - 1);
    OptResultByte->MinPost[MarginArray] = MinPost[MarginArray] / (AveN + ScaleM - 1);
  }
  // Sort Array
  MrcBsort (SMaxPost, MAX_TRADEOFF_TYPES);
  // Calculate Number of Bits Required to represent this number. Make sure to handle care of EnSq
  NumBits = 0;

  for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
    if (MarginArray < (MAX_TRADEOFF_TYPES - 1)) {
      // if EnSq we do Max^2 so the num get twice the bits...
      localY = SMaxPost[MarginArray];
      if (EnSq) {
        localY = (localY * localY);
      }

      NumBits += MrcLog2 (localY);
    } else {
      NumBits += MrcLog2 (SMaxPost[MarginArray]);
    }
  }

  NumBits += 11; // reserved another 10 bits for division in order to format for printing ; 3 for adding - up to 8
  // EqOrder for square terms
  if (EnSq) {
    EqOrder = (EqOrder + (EqOrder - 1));
  }
  // Handle Potential Saturation
  if (NumBits > 64) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Warning number of bits exceeds 64 bit : %d \n", NumBits);
    // Shift all numbers to reduce final result to be less than 32 bits.  Round Up
    Shift = (NumBits - 64 + EqOrder - 1) / EqOrder;
    // RoundUp Adder
    Adder = (1 << (Shift - 1));
    // Divide by (1<<Shift) and Round Up
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      MaxPost[MarginArray]       = (MaxPost[MarginArray] + Adder) >> Shift;
      GoodPwrLimitPost[MarginArray]  = (GoodPwrLimitPost[MarginArray] + Adder) >> Shift;
      for (x = 0; x < LenMargin; x++) {
        PostMar[MarginArray][x] = (PostMar[MarginArray][x] + Adder) >> Shift;
      }
    }
  }
  // Calculate Square terms:
  if (EnSq) {
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      MaxPost[MarginArray] = MaxPost[MarginArray] * MaxPost[MarginArray];
    }
  }
  // Set Limits for Search
  Start = 0;
  Stop  = LenMargin;
  if ((IncEnds == 0) && (LenMargin > AveN)) {
    if (Nby2 > 0) {
      Start++;
      Stop--;
    }
  }
  if (UPMOptimize != NULL) {
    for (x = Start; x < Stop; x++) {
      for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
        if (UPMOptimize[MarginArray] == 0) {
          continue; // not need to calculate those
        }
        if (PostMar[MarginArray][x] > GoodPwrLimitPost[MarginArray]) {
          PostMar[MarginArray][x] = GoodPwrLimitPost[MarginArray];
          OptResultByte->Margins[MarginArray][x].EW = (UINT16) PostMar[MarginArray][x] / (AveN + ScaleM - 1) / Scale[MarginArray];
        }
      }
    }
  }
  // Find Optimal Point from Margin Point of View
  // Combine the points using the formula:
  //   Max0*Max1*Max2*Post3 + Max1*Max2*Max3*Post0 + Max2*Max3*Max0*Post1 +
  //   Max3*Max0*Max1*Post2 + Scale*min(Post0,Post1,Post2,Post3)^EqOrder
  //   Scale = 1 + (10*(SMaxPost[0]-SMaxPost[1]))/SMaxPost[MAX_TRADEOFF_TYPES-1]
  for (x = Start; x < Stop; x++) {
    Result      = 0;
    MinPost1    = 0xFFFFFFFF;
    GoodPower   = TRUE;
    NumCalcArr  = 0;
    for (MarginArray = 0; MarginArray < MAX_TRADEOFF_TYPES; MarginArray++) {
      if (Scale[MarginArray] == 0) {
        continue; // not need to calculate those
      }
      NumCalcArr++; // Count the number of MarginTypes in the optimization function.
      // Find Min of all PostMar at offset x
      // Does this point meet the min power Margin requirements?
      if (Scale[MarginArray] > 0) {
        if (MinPost1 > PostMar[MarginArray][x]) {
          MinPost1 = PostMar[MarginArray][x];
        }

        if (PostMar[MarginArray][x] < GoodPwrLimitPost[MarginArray]) {
          GoodPower = FALSE;
        }
      }
      // Calculate this portion of result
      LocalResult = 1;
      for (yArr = 0; yArr < MAX_TRADEOFF_TYPES; yArr++) {
        if (Scale[yArr] == 0) {
          continue; // not need to calculate those
        }

        if (MarginArray == yArr) {
          continue;
        } else {
          LocalResult = MrcCall->MrcMultU64x32 (LocalResult, MaxPost[yArr]);
        }
      }

      Result += MrcCall->MrcMultU64x32 (LocalResult, PostMar[MarginArray][x]);
    }
    // Add in (MinPost ^ EqOrder)
    // If NumCalcArr is 0, set it to 1 so that it still in the range of array size.
    //  This will cause PowerCalcIndex to underflow.  Set to 1 in this case.
    if (NumCalcArr == 0) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Error: wrong input parameter caused NumCalcArr = 0 when calling FindOptimalTradeOff()\n"
        );
      NumCalcArr = 1;
    }

    ScaleMin = 1 + (10 * (SMaxPost[0] - SMaxPost[1])) / SMaxPost[NumCalcArr - 1];
    if (ScaleMin > 5) {
      ScaleMin = 5;
    }

    ScaleMin  = 1;
    LocalResult    = ScaleMin;
    for (i = 0; i < EqOrder; i++) {
      LocalResult = MrcCall->MrcMultU64x32 (LocalResult, MinPost1);
    }

    Result += LocalResult;

    if (Result > MaxR) {
      MaxR  = Result;
      BestX = x; // save first highest function result offset
    }

    OptResultByte->Result[x] = Result;
    // Find Optimal Point from Power Point of View.
    // All the margin types must be >= GoodPowerLimit
    if (GoodPower) {
      if (FoundPwrOpt == 0) {
        FoundPwrOpt = 1;
        PowerX      = x;
      } else {
        // Find the first lowest power point.
        // PostMar[Power] is inverted: higher number is lower power.
        if ((OptimizationMode > 0) && (OptimizationMode < MAX_TRADEOFF_TYPES)) {
          if (PostMar[OptimizationMode][x] > PostMar[OptimizationMode][PowerX]) {
            PowerX = x;
          }
        }
      }
    }
  } // end shmoo offsets
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (MaxR == 0) ? "Warning : MaxR is Zero !!!\n" : "");
  // At this point, BestX will have the highest Margin Result index.  PowerX will have
  // the highest or lowest index that is marked good based on MarginLimits.
  if (FoundPwrOpt) {
    if (OptimizationMode < MAX_TRADEOFF_TYPES) {
      BestX = PowerX;
    } else if (OptimizationMode < 100) {
      for (x = PowerX; x < Stop; x++) {
        Result = (UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (OptResultByte->Result[x], 100), MaxR, NULL));
        if (Result >= OptimizationMode) {
          BestX = x;
          break;
        }
      }
    }
  }

  OptResultByte->Best     = BestX;
  OptResultByte->MaxR     = MaxR;
  // Apply a guard band to the best setting, clamped at edges of the search.
  if (GuardBand != 0) {
    // Determine step direction and limit to the search edge.
    if (GuardBand < 0) {
      StepSize = 1;
      Off = ((BestX + GuardBand) < Start) ? Start : (BestX + GuardBand);
    } else {
      StepSize = -1;
      Off = ((BestX + GuardBand) >= Stop) ? (Stop - 1) : (BestX + GuardBand);
    }
    // Check each test for margin drop of MarginDropPercent.
    // If any test fails, we step towards the original selection.
    MarginLimit = MrcCall->MrcMultU64x32 (OptResultByte->Result[BestX], (100 - MarginDropPercent));
    MarginLimit = MrcCall->MrcDivU64x64 (MarginLimit, 100, NULL);
    for(; (Off != BestX); Off += StepSize) {
      if (OptResultByte->Result[Off] > MarginLimit) {
        break;
      }
    }

    OptResultByte->GuardBand = Off - (INT8) BestX;
  }

  return;
}

/**
  This function implements Turn Around Timing training.
  Optimize TA ODT Delay and Duration

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess.
**/
MrcStatus
MrcTurnAroundTiming (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  INT64               GetSetVal;
  INT64               MaxVal;
  UINT32              Controller;
  UINT32              Channel;
  UINT32              IpChannel;
  UINT32              ChannelIncrement;
  UINT8               MaxChannel;
  UINT8               RankMaskCh;
  UINT8               RankMask;
  BOOLEAN             RunDD;
  BOOLEAN             RunDR;
  BOOLEAN             Lpddr;
  static const UINT8  ParamListX[6]  = {RdV, RdT, WrV, WrT, RcvEnaX, WrLevel};
  static const UINT8  TestListRdX[3] = {RdV, RdT, RcvEnaX};
  static const UINT8  TestListWr[2]  = {WrV, WrT};
  static const INT8   ClkShifts[2]   = {-7, 7};
  INT8                Range;
  UINT8               GuardBand;
  UINT8               Update;
  UINT8               LoopCount;
  UINT32              RelaxBy;
  UINT32              MinNomWR2WR_dr;
  UINT32              NomWR2RD_dr;
  UINT32              NomWR2RD_dd;
  UINT32              NomRD2WR_dd;
  UINT32              NomRD2WR_dr;
  UINT32              NomRD2RD_dr;
  UINT32              NomRD2RD_dd;
  UINT32              NomWR2WR_dr;
  UINT32              NomWR2WR_dd;
  UINT32              Offset;
  MC0_CH0_CR_SC_PCIT_STRUCT  ScPcit;
  MC0_CH0_CR_SC_PCIT_STRUCT  ScPcitSave[MAX_CONTROLLER][MAX_CHANNEL];

#ifdef MRC_DEBUG_PRINT
  UINT8 GroupIdx;
  UINT8 TaTypeIdx;
  static const GSM_GT PrintGroups [4][2] = {{GsmMctRDRDdr, GsmMctRDRDdd},
                                            {GsmMctRDWRdr, GsmMctRDWRdd},
                                            {GsmMctWRRDdr, GsmMctWRRDdd},
                                            {GsmMctWRWRdr, GsmMctWRWRdd}};
  static const char *TaString[] = {"RdRd", "RdWr", "WrRd", "WrWr"};
  static const char *TypeStr[] = {"Dr", "Dd"};
#endif

  Status        = mrcSuccess;
  RankMaskCh    = 0;
  Update        = 1;
  LoopCount     = 10;  //1024 per Rank
  RelaxBy       = 4;
  RunDD         = FALSE;
  RunDR         = FALSE;
  NomWR2RD_dr   = 0;
  NomWR2RD_dd   = 0;
  NomRD2WR_dd   = 0;
  NomRD2WR_dr   = 0;
  NomRD2RD_dr   = 0;
  NomRD2RD_dd   = 0;
  NomWR2WR_dr   = 0;
  NomWR2WR_dd   = 0;
  MaxVal        = 0;
  RankMask      = MrcData->Outputs.ValidRankMask;
  Range         = 1;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MaxChannel    = Outputs->MaxChannels;
  Lpddr         = Outputs->Lpddr;

  ChannelIncrement = Lpddr ? 2 : 1;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel += ChannelIncrement) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

      RankMaskCh  = ChannelOut->ValidRankBitMask;
      RunDD       = RunDD || (ChannelOut->DimmCount == 2);
      RunDR       = RunDR || ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);
      RunDD       = 0;
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Mc %d, Channel %d: RunDR = 0x%x, RunDD = 0x%x, RankMaskCh = 0x%x\n",
        Controller,
        Channel,
        RunDR,
        RunDD,
        RankMaskCh
      );

      // Use nominal values (previously programmed) +1 and -1 to test for Gear1.  Gear2 will need to do +2 and -2 with steps of 2.
      // Taking worst case of both channels.
      // Ideally the Cliff routine should support offset per channel or better make the param a real offset (not the abs value)
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, ReadFromCache, &GetSetVal);
      NomWR2RD_dr = MAX (NomWR2RD_dr, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, ReadFromCache, &GetSetVal);
      NomWR2RD_dd = MAX (NomWR2RD_dd, (UINT8) GetSetVal);

      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, ReadFromCache, &GetSetVal);
      NomRD2WR_dr = MAX (NomRD2WR_dr, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, ReadFromCache, &GetSetVal);
      NomRD2WR_dd = MAX (NomRD2WR_dd, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, ReadFromCache, &GetSetVal);
      NomRD2RD_dr = MAX (NomRD2RD_dr, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, ReadFromCache, &GetSetVal);
      NomRD2RD_dd = MAX (NomRD2RD_dd, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, ReadFromCache, &GetSetVal);
      NomWR2WR_dr = MAX (NomWR2WR_dr, (UINT8) GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, ReadFromCache, &GetSetVal);
      NomWR2WR_dd = MAX (NomWR2WR_dd, (UINT8) GetSetVal);

    // Change PCIT to 0xFF
    // This allows proper tRDWR_dg stress without extra PRE/ACT cycles.
      IpChannel   = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PCIT_REG, MC1_CH0_CR_SC_PCIT_REG, Controller, MC0_CH1_CR_SC_PCIT_REG, IpChannel);
      ScPcit.Data = MrcReadCR (MrcData, Offset);
      ScPcitSave[Controller][IpChannel] = ScPcit;
      ScPcit.Bits.PCIT = 0xFF;
      MrcWriteCR (MrcData, Offset, ScPcit.Data);
    } // for Channel
  } // for Controller

  if (Outputs->Gear2) {
    Range = 2;
    MinNomWR2WR_dr = MAX (NomWR2WR_dr - Range, 7); // 7 QClks
    MinNomWR2WR_dr = 2 * (DIVIDECEIL (MinNomWR2WR_dr, 2));
  } else {
    MinNomWR2WR_dr = MAX (NomWR2WR_dr - Range, DIVIDECEIL (7, 2)); // 7 QClks in DClks
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel += ChannelIncrement) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Adjust initial values to be more relaxed so any detected failures are due to the parameter being tested.
      if (RunDR) {
        // Different Rank, Same DIMM
        MrcGetSetLimits (MrcData, GsmMctRDRDdr, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomRD2RD_dr + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, WriteToCache, &GetSetVal);
        MrcGetSetLimits (MrcData, GsmMctWRWRdr, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomWR2WR_dr + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, WriteToCache, &GetSetVal);

        MrcGetSetLimits (MrcData, GsmMctWRRDdr, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomWR2RD_dr + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, WriteToCache, &GetSetVal);
        MrcGetSetLimits (MrcData, GsmMctRDWRdr, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomRD2WR_dr + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, WriteToCache, &GetSetVal);
      }
      if (RunDD) {
        // Different DIMMs
        MrcGetSetLimits (MrcData, GsmMctWRRDdd, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomWR2RD_dd + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, WriteToCache, &GetSetVal);
        MrcGetSetLimits (MrcData, GsmMctRDWRdd, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomRD2WR_dd + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, WriteToCache, &GetSetVal);
        MrcGetSetLimits (MrcData, GsmMctRDRDdd, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomRD2RD_dd + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, WriteToCache, &GetSetVal);
        MrcGetSetLimits (MrcData, GsmMctWRWRdd, NULL, &MaxVal, NULL);
        GetSetVal = MIN ((UINT32) MaxVal, NomWR2WR_dd + RelaxBy);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, WriteToCache, &GetSetVal);
      }
      MrcFlushRegisterCachedData (MrcData);
      // Must update the XARB bubble injector when TAT values change
      SetTcBubbleInjector (MrcData, Controller, Channel);
    } // for Channel
  } // for Controller

  // Different DIMM turnarounds
  if (RunDD) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDRD2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              ddrd2rd,
              TestListRdX,
              ARRAY_COUNT (TestListRdX),
              (INT8) NomRD2RD_dd,
              (INT8) NomRD2RD_dd + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDWR2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              ddwr2wr,
              TestListWr,
              ARRAY_COUNT (TestListWr),
              (INT8) NomWR2WR_dd - Range,
              (INT8) NomWR2WR_dd + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDWR2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              ddwr2rd,
              ParamListX,
              ARRAY_COUNT (ParamListX),
              MAX ((INT8) NomWR2RD_dd - Range, 4),
              (INT8) NomWR2RD_dd + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DDRD2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              ddrd2wr,
              ParamListX,
              ARRAY_COUNT (ParamListX),
              (INT8) NomRD2WR_dd - Range,
              (INT8) NomRD2WR_dd + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
  }
  // Different Rank turnarounds
  if (RunDR) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRRD2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              drrd2rd,
              TestListRdX,
              ARRAY_COUNT (TestListRdX),
              (INT8) NomRD2RD_dr,
              (INT8) NomRD2RD_dr + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRWR2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              drwr2wr,
              TestListWr,
              ARRAY_COUNT (TestListWr),
              (INT8) MinNomWR2WR_dr,
              (INT8) NomWR2WR_dr + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRWR2RD\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              drwr2rd,
              ParamListX,
              ARRAY_COUNT (ParamListX),
              MAX ((INT8) NomWR2RD_dr - Range, 4),
              (INT8) NomWR2RD_dr + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s DRRD2WR\n", "\n ##### Running");
    Status = TrainDDROptParamCliff (
              MrcData,
              drrd2wr,
              ParamListX,
              ARRAY_COUNT (ParamListX),
              (INT8) NomRD2WR_dr - Range,
              (INT8) NomRD2WR_dr + Range,
              LoopCount,
              Update,
              Outputs->MarginResult,
              ClkShifts,
              ARRAY_COUNT (ClkShifts),
              0,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcFail;
    }
  }

  // Program SAFE values for ODT and SAmp
  GuardBand = 1;
  if (Outputs->Gear2) {
    GuardBand *= 2;
  }
  UpdateSampOdtTiming (MrcData, GuardBand);
  // ODT Delay (start) / Duration
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s mcodts\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
            MrcData,
            mcodts,
            TestListRdX,          // Including RcvEnaX to the test list
            ARRAY_COUNT (TestListRdX),
            0,
            2 + GuardBand,
            LoopCount,
            Update,
            Outputs->MarginResult,
            ClkShifts,
            ARRAY_COUNT (ClkShifts),
            0,
            RankMask,
            GuardBand
            );
  if (Status != mrcSuccess) {
    return mrcFail;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s mcodtd\n", "\n ##### Running");
  Status = TrainDDROptParamCliff (
            MrcData,
            mcodtd,
            TestListRdX,
            ARRAY_COUNT (TestListRdX),
            (-1 - GuardBand),
            0,
            LoopCount,
            Update,
            Outputs->MarginResult,
            ClkShifts,
            ARRAY_COUNT (ClkShifts),
            0,
            RankMask,
            GuardBand
            );
  if (Status != mrcSuccess) {
    return mrcFail;
  }

  // Restore PCIT value
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel += ChannelIncrement) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PCIT_REG, MC1_CH0_CR_SC_PCIT_REG, Controller, MC0_CH1_CR_SC_PCIT_REG, IpChannel);
      MrcWriteCR (MrcData, Offset, ScPcitSave[Controller][IpChannel].Data);
    }
  }

  // Print out the end results of the training step in Table Format
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- Final TA values ---\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel += ChannelIncrement) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tMc%d.C%d", Controller, Channel);
    }
  }
  for (TaTypeIdx = 0; TaTypeIdx < (sizeof (PrintGroups) / (sizeof (PrintGroups[0]))); TaTypeIdx++) {
    for (GroupIdx = 0; GroupIdx < (sizeof (PrintGroups[0]) / (sizeof (PrintGroups[0][0]))); GroupIdx++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s%s", TaString[TaTypeIdx], TypeStr[GroupIdx]);
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel += ChannelIncrement) {
          if (!MrcChannelExist (MrcData, Controller, Channel)) {
            continue;
          }
          MrcGetSetMcCh (MrcData, Controller, Channel, PrintGroups[TaTypeIdx][GroupIdx], ReadFromCache, &GetSetVal);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", (UINT8) GetSetVal);
        }
      }
    } // GroupIdx
  } // TaTypeIdx
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
#endif
  return Status;
}

/**
  General purpose function to optimize an arbitrary value, OptParam (see list above)
    OptParam is generally some timing number that impacts performance or power
    Expects that as OptParam gets smaller*, margins are flat until we hit a cliff
    This procedure defines a cliff as a reduction of 4 ticks in eye height/width
    * In the case of mcodts, higher values are actually worst
    To stress out the timing, xxDDR_CLK is shifted by +/- 15 PI ticks

  @param[in] MrcData         - Include all MRC global data.
  @param[in] OptParam        - Supports Turnaround Timings and ODT Start / Duration
  @param[in] TestList        - List of margin param to check to make sure timing are okay.
  @param[in] NumTests        - The size of TestList
  @param[in] Start           - Start point for this turn around time setting.
  @param[in] Stop            - Stop point for this turnaround time setting.
                                 Note that the Start/Stop values are the real values, not the encoded value
  @param[in] LoopCount       - Length of a given test (per rank)
  @param[in] Update          - Update the CRs and host structure with ideal values
  @param[in] MarginByte      - Byte level margins
  @param[in] ClkShifts       - Array of PI clocks to be shifted
  @param[in] NumR2RPhases    - Number of PI clock phases
  @param[in] rank            - rank to work on
  @param[in] RankMask        - RankMask to be optimized
  @param[in] GuardBand       - GuardBand to be added to last pass value (to be a bit conservative).

  @retval MrcStatus      - If it succeeds return mrcSuccess
**/
MrcStatus
TrainDDROptParamCliff (
  IN MrcParameters *const MrcData,
  IN UINT8                OptParam,
  IN const UINT8          TestList[],
  IN UINT8                NumTests,
  IN INT8                 Start,
  IN INT8                 Stop,
  IN UINT8                LoopCount,
  IN UINT8                Update,
  IN UINT16               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const INT8           *ClkShifts,
  IN UINT8                NumR2RPhases,
  IN UINT8                rank,
  IN UINT8                RankMask,
  IN UINT8                GuardBand
  )
{
  static const UINT8 OptParamDDType[] = { // Does this test run dr, dd or both
  //drrd2rd ddrd2rd drwr2wr ddwr2wr drrd2wr ddrd2wr drwr2rd ddwr2rd rdodtd wrodtd mcodts mcodtd rtl
    1,      2,      1,      2,      1,      2,      1,      2,      3,     3,     3,     3,     0};
  static const UINT8 RankMapping[16] = {15, 15, 15, 4, 15, 3, 15, 1, 15, 15, 15, 15, 5, 2, 15, 0};
    // Order of rank turnarounds for dr & dd.
  static const UINT32  RankOrder[2][6] = {
    { 0x32320101, 0x10101010, 0x32323232, 0x20, 0x10, 0x23 }, // RankOrder[0]: drsd - same DIMM
    { 0x21303120, 0x00002120, 0x00003020, 0x20, 0x00, 0x00 }  // RankOrder[1]: drdd - diff DIMM
  };
  static const Cpgc20Address CPGCAddressConst = {
    CPGC20_RANK_2_ROW_COL_2_BANK,
    CPGC20_FAST_Y,
    0,
    0,
    0,
    0,
    8,
    8
  };
  Cpgc20Address     CpgcAddress;
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  MRC_PATTERN_CTL   PatternCtl; // For 8 bit VA, this walks through each WDB pointer ~ 2X
  INT64             WrRdSg[MAX_CONTROLLER][MAX_CHANNEL];
  INT64             RdWrSg[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32            BERStats[4];  // Track BER results
  UINT32            RankList;
  UINT32            Offset;
  UINT32            Controller;
  UINT32            Channel;
  UINT32            IpChannel;
  UINT16            Margins[MAX_TESTS_OPT_PARAM_CLIFF][2][2][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];  // Tests X DR/DD x ClkPhases x Ch X Byte
  UINT16            NumCL;  // Number of cachelines per SubSeq
  UINT16            m;
  UINT16            ByteMask;
  UINT16            ByteFailMask[MAX_CONTROLLER][MAX_CHANNEL];  // Per ch mask indicating which bytes have failed
  UINT16            ByteDone;
  INT8              Inc;
  INT8              Off;
  INT8              Index;
  INT8              LastPass[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];     // Lass Pass Value for off
  INT8              Begin;
  INT8              End;
  INT8              ChLastPass;
  INT8              ActualGuardBand;
  UINT8             MaxChannel;
  UINT8             McChannelMask;
  UINT8             Byte;
  UINT8             Rank;
  UINT8             McChBitMask;
  UINT8             RankCount;
  UINT8             OrigRankCount;
  UINT8             McChBitMaskdd;
  UINT8             RankMaskCh;
  UINT8             GlobalRankMask;
  UINT8             drddPresent[2]; // [0]: ChBitMask for dr, [1]: ChBitMask for dd
  UINT8             CmdPat;
  UINT8             BMap[9];  // Needed for GetBERMarginByte function
  UINT8             MarginLimit;  // Need to change it to 20%of eye heigth
  UINT8             ResetDDR;
  UINT8             SelfRefresh;
  UINT8             offs[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8             Param;
  UINT8             iparam;
  UINT8             dd;
  UINT8             test0;
  UINT8             v0;
  UINT8             RankOrderIndex;
  UINT8             UpdateHostMargin;
  UINT8             Done;
  UINT8             MaxMargin;
  UINT8             ResultType;
  UINT8             WDBIncRate; // Number of cachelines between incrementing WDB.
  UINT8             LoopEnd;
  UINT8             ResultRank;
  UINT8             ShiftValue;
  BOOLEAN           WriteVrefParam;
  BOOLEAN           DramVref;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr;
  BOOLEAN           IsDual;
  BOOLEAN           ODT;
  BOOLEAN           PerByte;
  BOOLEAN           NotRankTraining;
  BOOLEAN           FindFirstPass;
#ifdef MRC_DEBUG_PRINT
  INT64             GetSetVal;
  INT8              ChLastPass1[MAX_CONTROLLER][MAX_CHANNEL];
#endif // MRC_DEBUG_PRINT
  UINT8             RepeatInitialTest;
  MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT  CpgcChSeqRankL2PMapping;
  MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_STRUCT           Cpgc2AddrSize;
//  REUT_CH_SEQ_CFG_0_STRUCT                         ReutChSeqCfg; // @todo <ICL> Update with CPGC 2.0 implementation
//  REUT_CH_SEQ_BASE_ADDR_WRAP_0_STRUCT ReutChSeqBaseAddrWrap;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  Status          = mrcSuccess;
  Ddr4            = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr           = Outputs->Lpddr;
  Done            = 0;
  drddPresent[0]  = 0;
  drddPresent[1]  = 0;
  MarginLimit     = 10;  // Drop of X% in margin means failure
  ResetDDR        = 1;
  SelfRefresh     = 0;
  WDBIncRate      = 13;
  NumCL           = (Lpddr) ? 64 : 128;
  MaxChannel      = Outputs->MaxChannels;
  RepeatInitialTest = 4;  // Run initial RTL point 5 times

  MRC_DEBUG_ASSERT (NumTests <= MAX_TESTS_OPT_PARAM_CLIFF, Debug, "ERROR: too many tests passed into TrainDDROptParamCliff()\n");

  PatternCtl.IncRate  = 0;
  PatternCtl.DQPat    = 0;
  PatternCtl.EnableXor = FALSE;
  PatternCtl.PatSource = MrcPatSrcDynamic;
  MrcCall->MrcSetMem ((UINT8 *) ByteFailMask, sizeof (ByteFailMask), 0);
  MrcCall->MrcSetMem ((UINT8 *) offs, sizeof (offs), 0);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcCopyMem ((UINT8 *) &CpgcAddress, (UINT8 *) &CPGCAddressConst, sizeof (CpgcAddress));
  switch (OptParam) {
  case mcodts:
  case mcodtd:
    CpgcAddress.AddrIncOrder = CPGC20_BANK_2_ROW_COL_2_RANK;
    CpgcAddress.ColSizeBits = 3;
    NumCL           = 32;
    break;

  case rtl:
    CpgcAddress.BankSize = 1;
    break;

  default:
  case drwr2rd:
  case drwr2wr:
  case drrd2rd:
  case drrd2wr:
    //Use currently defined CpgcAddress
    break;
  }
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  GlobalRankMask = Outputs->ValidRankMask & RankMask;

  NotRankTraining = (OptParam == rtl);
  FindFirstPass   = (OptParam == rtl);  // FindFirstPass logic only works for RTL!
  ODT             = (OptParam == rdodtd) || (OptParam == wrodtd) || (OptParam == mcodtd) || (OptParam == mcodts);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nNotRankTraining = %u, ODT = %d\n", NotRankTraining, ODT);

  // Decide which channels need to be run and program NumCachelines and LC
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      if (ChannelOut->ValidRankBitMask) {
        McChannelMask = 1 << ((Controller * MaxChannel) + Channel);
        RankMaskCh  = ChannelOut->ValidRankBitMask;
        IsDual      = ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);

        // Continue if no ranks in this channel
        if ((RankMaskCh & RankMask) == 0) {
          continue;
        }

        if ((OptParamDDType[OptParam] & 0x2) && (ChannelOut->DimmCount == 2)) {
          drddPresent[1] |= McChannelMask; // dd parameter and channel has 2 DIMMs
        }

        if (((OptParamDDType[OptParam] & 0x1) && IsDual) || NotRankTraining) {
          drddPresent[0] |= McChannelMask; // dr parameter and channel has a dual rank
        }

        if (ODT && ((drddPresent[0] & McChannelMask) == 0)) {
          // ODT matters when Single rank
          // dr parameter and channel has a dual rank
          drddPresent[0] |= McChannelMask;
        }
      }
    }
  }

  McChBitMask = drddPresent[1] | drddPresent[0]; // Channel is present if it has either a dr or dd
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "drddPresent[0] = 0x%x, drddPresent[1] = 0x%x, McChBitMask = 0x%x\n",
    drddPresent[0],
    drddPresent[1],
    McChBitMask
    );

  // There is nothing to optimize for this parameter
  if ((McChBitMask == 0) || (Stop <= Start)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "McChBitMask = %d, Start = 0x%x, Stop = 0x%x\n", McChBitMask, Start, Stop);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "No need to optimize TA, OptParam = %d\n", OptParam);
    return (Inputs->ExitOnFailure) ? mrcFail : mrcSuccess;
  }
  // Setup the REUT Test
  if ((OptParam == ddwr2rd) || (OptParam == drwr2rd)) {
    CmdPat = PatWrRdTA;
    Outputs->DQPat  = TurnAroundWR;
    // WrRdSg is a long delay.  Extend RdWrSg to cover the remaining WrRdSg delay so we get WrRdDr properly.
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
            continue;
        }
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDsg, ReadFromCache, &WrRdSg[Controller][Channel]);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, ReadFromCache, &RdWrSg[Controller][Channel]);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, WriteCached, &WrRdSg[Controller][Channel]);
        // Must update the XARB bubble injector when TAT values change
        SetTcBubbleInjector (MrcData, Controller, Channel);
      }
    }
  } else if ((OptParam == ddrd2wr) || (OptParam == drrd2wr)) {
    CmdPat          = PatRdWrTA;
    Outputs->DQPat  = TurnAroundRW;
//    RankInc         = 1;
  } else if (ODT) {
    CmdPat          = PatODTTA;
    Outputs->DQPat  = TurnAroundODT;
//    RankInc         = 1;
  } else if (OptParam == rtl) {
    CmdPat = PatWrRd;
    Outputs->DQPat  = RdRdTA;
    // Less optimistic values since we are updating values and RMT fails
    WDBIncRate  = 16;
    NumCL       = 4;
  } else {
    CmdPat = PatWrRd;
    Outputs->DQPat  = TurnAround;
  }

  PatternCtl.DQPat        = Outputs->DQPat;
  PatternCtl.IncRate      = WDBIncRate;
//  REUTAddress.IncRate[0]  = RankInc; // Rank
//  REUTAddress.IncRate[3]  = RankInc; // Col

  // SOE=0, EnCADB=0, EnCKE=0, SubSeqWait=0
  // @todo Update with McChBitMask
  SetupIOTest (MrcData, McChBitMask, CmdPat, NumCL, LoopCount, &CpgcAddress, NSOE, &PatternCtl, 0, 0, 0);

  Outputs->DQPatLC = MRC_BIT0 << (LoopCount - MrcLog2 ((UINT32) (NumCL - 1)));
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }
  // Optimize parameter per byte.  Everything else is per channel
  PerByte = (OptParam == mcodts) || (OptParam == mcodtd);

  // Keep track of which bytes have failed and are we done yet
  ByteDone = (1 << Outputs->SdramCount) - 1;

  // ###########################################################
  // ####  Loop through OptParam X DD X ClkPhases X Params and measure margin #####
  // ###########################################################
  if (OptParam == mcodts) {
    // In the case of mcodts, higher values are actually worst.
    Begin = Start;
    End   = Stop;
    Inc   = 1;
  } else {
    Begin = Stop;
    End   = Start;
    Inc   = -1;
  }

  if ((Outputs->Gear2) && (OptParam != mcodts) && (OptParam != mcodtd)) {
    Inc *= 2;
  }

  ActualGuardBand = (Inc * GuardBand);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Start = %d, Stop = %d, Begin = %d, End = %d, Inc = %d\n",
    Start,
    Stop,
    Begin,
    End,
    Inc
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (OptParam == rtl) ? "Rank = %d\n" : "", rank);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel 0\t\t\t\t\t\t\t\t1\nByte\t");
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE, (
    Outputs->SdramCount == MAX_SDRAM_IN_DIMM
    ) ? "0\t1\t2\t3\t4\t5\t6\t7\t8\t0\t1\t2\t3\t4\t5\t6\t7\t8\n" :
    "0\t1\t2\t3\t4\t5\t6\t7\t0\t1\t2\t3\t4\t5\t6\t7\n"
    );

  // Init Variables
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        MrcCall->MrcSetMem ((UINT8 *) &LastPass[Controller][Channel][0], Outputs->SdramCount, (UINT8) (Begin - ActualGuardBand));
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (iparam = 0; iparam < NumTests; iparam++) {
            for (dd = 0; dd < 2; dd++) {
              for (test0 = 0; test0 < NumR2RPhases; test0++) {
                Margins[iparam][dd][test0][Channel][Byte] = 1280;
              }
            }
          }
        }
      }
    }
  }
  // Walk through different OptParam values
  for (Off = (INT8) Begin; Off != (INT8) (End + Inc); Off += Inc) {
    if (Done) {
      break;
    }
    Index = (Off - Begin) * Inc; // Index = 0, 1, 2..
    if (Index == 1) {
      if ((RepeatInitialTest != 0) && FindFirstPass) {  // Repeat initial measurement of RTL to filter out repetition noise
        Off -= Inc;
        Index = 0;
        RepeatInitialTest--;
      }
    }
    // Inc can only take a value of +/- 1.
    if ((Index == 1) && FindFirstPass) {
      Inc  *= -1;
      Off   = End;
      End   = Begin - Inc;  // One Inc less since we have already done Index 0.
      Begin = Off - Inc;    // One Inc less to get us starting at Index 1
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Find First Pass - Walking backwards.\n Off = %d, Begin = %d, End = %d, Inc = %d\n",
        Off,
        Begin,
        End,
        Inc
        );
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Param^ Offset-> %d\n   Actl\t", Off);

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        RankMaskCh = ChannelOut->ValidRankBitMask & RankMask;
        if (IS_MC_SUB_CH (Lpddr, Channel)) {
          //Dont print
          continue;
        }
        // if nothing for this channel OR No Ranks in this channel
        if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) || (RankMaskCh == 0)) {
#ifdef MRC_DEBUG_PRINT
          if (Channel == 0) { //@todo need to adjust for MaxChannel printing
            if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
            }
          }
#endif // MRC_DEBUG_PRINT
          continue;
        }

        if (FindFirstPass && (Index == 0)) {
          // We use the current RTL value for the initial test
#ifdef MRC_DEBUG_PRINT
          MrcGetSetMcChRnk (MrcData, Controller, Channel, rank, RxFlybyDelay, ReadFromCache, &GetSetVal);
#endif
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Mc%u Ch%u initial RTL: %u", Controller, Channel, (UINT32) GetSetVal);
        } else {
          // No need to update MrcData host during this step even if not collecting data
          LoopEnd = (UINT8) ((PerByte) ? Outputs->SdramCount : 1);
          for (Byte = 0; Byte < LoopEnd; Byte++) {
            UpdateTAParamOffset (MrcData, Controller, Channel, Byte, OptParam, Off, 0, 0, RankMaskCh);
          }
          if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
            // Set UpdateHost to TRUE because TA values share the same register
            MrcTatStretch (MrcData, Controller, Channel, OptParam, Off - Start, TRUE);
          }
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    // Test both: different dr and dd as required
    for (dd = 0; dd < 2; dd++) {
      if (Done) {
        break;
      }
      // Check if this test type should be run
      McChBitMaskdd = drddPresent[dd];
      if (McChBitMaskdd == 0) {
        continue;
      }

      if (OptParam != rtl) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (dd == 0) ? "Dual Rank\n" : "Dual Dimm\n");
      }
      // Select Ranks in the correct order based on the test type
      // Need to re-order the ranks based on the value of ddw2r
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          RankMaskCh = ChannelOut->ValidRankBitMask & RankMask;
          if ((RankMaskCh == 0) || IS_MC_SUB_CH (Lpddr, Channel)) {
            // No Ranks in this channel
            // For LPDDR4/5, only program register on even channels.
            continue;
          }
          // Initialize variables and read out ordered rank list
          CpgcChSeqRankL2PMapping.Data = 0;
          RankCount = 0;
          IpChannel = LP_IP_CH (Lpddr, Channel);
          if (NotRankTraining) {
            RankList = 0x00003210;
          } else {
            RankOrderIndex = RankMapping[RankMaskCh];
            if (RankOrderIndex == 15) {
              RankList = 0x00003210;
            } else {
              RankList = RankOrder[dd][RankOrderIndex];
            }
          }

          while (RankList > 0) {
            if ((RankCount % 6 == 0) && (RankCount)) {
              // Program the RankMapping register if we exceed 6 ranks that fits within the register width

              Offset = OFFSET_CALC_MC_CH (MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, MC1_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, Controller, MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, IpChannel);
              Offset += (RankCount / 6) * (MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG - MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG);
              MrcWriteCR (MrcData, Offset, CpgcChSeqRankL2PMapping.Data);

              // Reset RankMapping register
              CpgcChSeqRankL2PMapping.Data = 0;
            }
            Rank = (RankList & 0xF); // Nibble by Nibble
            RankList = (RankList >> 4);
            if (!(RankMaskCh & (1 << Rank))) {
              continue;
            }

            ShiftValue = (RankCount % 6) * MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_WID;
            CpgcChSeqRankL2PMapping.Data |= (Rank << ShiftValue);
            RankCount++;
          }

          if (CpgcChSeqRankL2PMapping.Data != 0) {
            // Program the RankMapping register that did not get programmed in the while loop

            Offset = OFFSET_CALC_MC_CH (MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, MC1_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, Controller, MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, IpChannel);
            Offset += (RankCount / 6) * (MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG - MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG);
            MrcWriteCR (MrcData, Offset, CpgcChSeqRankL2PMapping.Data);
          }

          Offset = OFFSET_CALC_MC_CH (MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REG, MC1_REQ0_CR_CPGC2_ADDRESS_SIZE_REG, Controller, MC0_REQ1_CR_CPGC2_ADDRESS_SIZE_REG, IpChannel);
          Cpgc2AddrSize.Data = MrcReadCR64 (MrcData, Offset);
          OrigRankCount = (UINT8) (Cpgc2AddrSize.Bits.Block_Size_Max_Rank + 1);
          if (OrigRankCount != RankCount) {
            Cpgc2AddrSize.Bits.Block_Size_Max_Rank = RankCount - 1;
            Cpgc2AddrSize.Bits.Region_Size_Max_Rank = RankCount - 1;
            MrcWriteCR64 (MrcData, Offset, Cpgc2AddrSize.Data);
            Cpgc20AdjustNumOfRanks (MrcData, Controller, IpChannel, OrigRankCount, RankCount);
          }
        } // for Channel
      } // for Controller
      // ###################################################
      // ### Walk through different sets of rank2rank timings  ###
      // ###################################################
      for (test0 = 0; test0 < NumR2RPhases; test0++) {
        if (Done) {
          break;
        }

        v0 = ClkShifts[test0];

        // Program rank offsets differently for dd vs. dr
        if (NotRankTraining) {
          for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
            for (Channel = 0; Channel < MaxChannel; Channel++) {
              if (!(McChBitMaskdd & (1 << ((Controller * MaxChannel) + Channel)))) {
                offs[Controller][Channel] = 0;
              } else {
                // Shift all signals in the channel(Clk/Ctl/Cmd/Dq) by v0
                offs[Controller][Channel] = v0;
              }
            }
          }
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 0);
          }
        } else if (dd == 1) {
          // For DD
          // Shift Clk/DQ on one DIMM by v0 and Clk/DQ on other DIMM by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          SetCmdMargin (MrcData, McChBitMaskdd, 0x3, WrT, v0, 0, ResetDDR, SelfRefresh);
          SetCmdMargin (MrcData, McChBitMaskdd, 0xC, WrT, -v0, 0, ResetDDR, SelfRefresh);
        } else {
          // For DR
          // Shift Clk/DQ on front side by v0 and Clk/DQ on backside by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          SetCmdMargin (MrcData, McChBitMaskdd, 0x5, WrT, v0, 0, ResetDDR, SelfRefresh);
          SetCmdMargin (MrcData, McChBitMaskdd, 0xA, WrT, -v0, 0, ResetDDR, SelfRefresh);
        }
        // Test different margin param
        for (iparam = 0; iparam < NumTests; iparam++) {
          Param = TestList[iparam];
          WriteVrefParam = ((Param == WrV) || (Param == WrFan2) || (Param == WrFan3));
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s ", gMarginTypesStr[Param]);

          ResultType = GetMarginResultType (Param);

          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", MinMarginLimit);
          // Calculate MaxMargin and Starting Point for margin search
          ResultRank = rank;
          if ((Param == WrV) || (Param == WrFan3) || (Param == WrFan2) ||
              (Param == RdV) || (Param == RdFan3) || (Param == RdFan2) || (Param == CmdV)) {
            MaxMargin = GetVrefOffsetLimits (MrcData, Param);
          } else {
            MaxMargin = MAX_POSSIBLE_TIME;
          }
          DramVref = (Ddr4 || Lpddr) && WriteVrefParam;
          // Are we done yet or should we keep testing?
          Done = 1;
          for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
            for (Channel = 0; Channel < MaxChannel; Channel++) {
              if (!(McChBitMaskdd & (1 << ((Controller * MaxChannel) + Channel)))) {
                continue;
              }

              ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
              RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
              if (RankMaskCh == 0) {
                continue; // No Ranks in this channel
              }

              // When FindFirstPass is used, all Bytes have to have passed before we stop.
              // We uses ByteFailMask[] to track the passing bytes in this case.
              if (PerByte || FindFirstPass) {
                if (ByteFailMask[Controller][Channel] != ByteDone) {
                  Done = 0;
                }
              } else {
                if (ByteFailMask[Controller][Channel] == 0) {
                  Done = 0;
                }
              }
            }
          }

          if (Done) {
            break;
          }

          Status = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, 0xF);
          if (Status != mrcSuccess) {
            return Status;
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 3d\t", (INT8) v0);
          Status = MrcGetBERMarginByte (
                    MrcData,
                    Outputs->MarginResult,
                    McChBitMaskdd,
                    GlobalRankMask,
                    GlobalRankMask,
                    Param,
                    0,  // Mode
                    BMap,
                    1,
                    MaxMargin,
                    0,
                    BERStats
                    );
          if (Status != mrcSuccess) {
            return Status;
          }

          if (DramVref) {
            // We return results on first available rank.
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if ((1 << Rank) & GlobalRankMask) {
                ResultRank = Rank;
                break;
              }
            }
          }
          // Record Results
          UpdateHostMargin = 1;

          for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
            for (Channel = 0; Channel < MaxChannel; Channel++) {
              ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
              RankMaskCh = ChannelOut->ValidRankBitMask & RankMask;
              // if nothing for this channel OR No Ranks in this channel
              if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMaskdd) || (RankMaskCh == 0)) {
#ifdef MRC_DEBUG_PRINT
                if (Channel == 0) {
                  if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
                  } else {
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
                  }
                }
#endif // MRC_DEBUG_PRINT
                continue;
              }

              for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
                // For this optimization, it makes more sense to look at the full sum
                ByteMask = 1 << Byte;
                m = EffectiveMargin (
                    MarginByte[ResultType][ResultRank][/**Controller**/ CONTROLLER_0][Channel][Byte][0],
                    MarginByte[ResultType][ResultRank][/**Controller**/ CONTROLLER_0][Channel][Byte][1]
                      );

                if (m < 20) {
                  m = 20;
                }
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", m);

                // If previously failed, this is also a failure unless we are looking for
                // the first passing offset.
                if ((ByteFailMask[Controller][Channel] & ByteMask) && !FindFirstPass) {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                  continue;
                }

                // Check if the first RoundTripLatency test is failing with zero margin.
                // Stop the test in this case - initial point should be passing.
                if (FindFirstPass && (Index == 0)) {
                  if (m == 20) {
                    ByteFailMask[Controller][Channel] = ByteDone;
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                    continue;
                  }
                }

                /* @todo: disable this as it make the results very conservative
                // Byte fails if margin is below MinMarginLimit at any time
                if (m < MinMarginLimit) {
                  // If we are looking for pass, continue and do not update LastPass
                  if (TRUE == FindFirstPass) {
                    if (Index == 0) {
                      // When training from the most aggressive setting to the conservative setting,
                      // if we fail the first setting we stop.
                      ByteFailMask[Controller][Channel] = ByteDone;
                    }
                    UpdateHostMargin = 0;
                  } else {
                    ByteFailMask[Controller][Channel] |= ByteMask;
                    LastPass[Controller][Channel][Byte] = Off - Inc - ActualGuardBand;
                  }
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                  continue;
                }
                */
                if (Index == 0) {
                  // Get the smallest marging at Index 0
                  if (Margins[iparam][dd][test0][Channel][Byte] > m) {
                    Margins[iparam][dd][test0][Channel][Byte] = m;
                  }
                } else {
                  // Check if we dropped more than the percent allowed
                  if (m < ((Margins[iparam][dd][test0][Channel][Byte] * (100 - MarginLimit)) / 100)) {
                    if (!FindFirstPass) {
                      ByteFailMask[Controller][Channel] |= ByteMask;
                      LastPass[Controller][Channel][Byte] = Off - Inc - ActualGuardBand;
                    }
                    UpdateHostMargin = 0;
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_NOTE,
                      "#-%d\t",
                      (ABS (m - Margins[iparam][dd][test0][Channel][Byte]) * 100) / Margins[iparam][dd][test0][Channel][Byte]
                      );
                    continue;
                  } else {
                    if (FindFirstPass) {
                      if ((ByteFailMask[Controller][Channel] & ByteMask) != ByteMask) {
                        LastPass[Controller][Channel][Byte] = Off - ActualGuardBand;
                        ByteFailMask[Controller][Channel] |= ByteMask;
                      }
                    } else {
                      LastPass[Controller][Channel][Byte] = Off - ActualGuardBand;
                    }
                  }
                }

                MRC_DEBUG_MSG (
                  Debug,
                  MSG_LEVEL_NOTE,
                  ".%c%d\t",
                  (m > Margins[iparam][dd][test0][Channel][Byte]) ? '+' : '-',
                  (ABS(m - Margins[iparam][dd][test0][Channel][Byte]) * 100) / Margins[iparam][dd][test0][Channel][Byte]
                  );
              } // for Byte
            } // for Channel
          } // for Controller
          // Stop the test if we fail on the initial RTL setting

          if (FindFirstPass && (Index == 0)) {
            for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
              for (Channel = 0; Channel < MaxChannel; Channel++) {
                ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
                RankMaskCh = ChannelOut->ValidRankBitMask & RankMask;
                // if nothing for this channel OR No Ranks in this channel
                if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMaskdd) || (RankMaskCh == 0)) {
                  continue;
                }
                if (ByteFailMask[Controller][Channel] != 0) {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nMc%u.Ch%u failed initial roundtrip latency value!\n", Controller, Channel);
                  return mrcFail;
                }
              }
            }
          }

          if (UpdateHostMargin) {
            Status = ScaleMarginByte (MrcData, Outputs->MarginResult, Param, ResultRank);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        } // for iparam

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

        // Clean up
        if (NotRankTraining) {
          MrcCall->MrcSetMem ((UINT8 *) offs, sizeof (offs), 0);
          // UpdateHost=0, SkipTx=0
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 0);
          }
        } else {
          SetCmdMargin (MrcData, McChBitMaskdd, RankMask, WrT, 0, 0, ResetDDR, SelfRefresh);
        }
      } // for test0 in ClkShifts[]

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    } // for dd
    if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
          RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
          // If nothing for this channel OR No Ranks in this channel
          if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) || (RankMaskCh == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
            continue;
          }
          // MrcTatStretch was called with UpdateHost so need to clean back to original values
          MrcTatStretch (MrcData, Controller, Channel, OptParam, - (Off - Start), TRUE);
        }
      }
    }
  } // for Off

  // If we are sweeping aggressive settings to conservative settings, we
  // need to restore original Inc, Begin, and End values to select the
  // proper offset if bytes have varying offsets values for a parameter
  // that is NOT specified per Byte.
  if (FindFirstPass) {
    Off   = End;         // Temp storage for swap
    End   = Begin + Inc;
    Begin = Off + Inc;
    Inc  *= -1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Find First Pass - Reverting Inc, Begin, and End\n Begin = %d, End = %d, Inc = %d,\n",
      Begin,
      End,
      Inc
      );
  }

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimal offset per Byte\n\t");
  // Print optimal value
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      ChannelOut            = &Outputs->Controller[Controller].Channel[Channel];
      RankMaskCh            = ChannelOut->ValidRankBitMask & RankMask;
      ChLastPass1[Controller][Channel]  = End;
      // if nothing for this channel OR No Ranks in this channel
      if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) || (RankMaskCh == 0)) {
        if (Channel == 0) {
          if (Outputs->SdramCount == (MAX_SDRAM_IN_DIMM - 1)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t");
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t");
          }
        }
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", LastPass[Controller][Channel][Byte]);
        if ((Inc == 1) && (ChLastPass1[Controller][Channel] > LastPass[Controller][Channel][Byte])) {
          ChLastPass1[Controller][Channel] = LastPass[Controller][Channel][Byte];
        }

        if ((Inc == -1) && (ChLastPass1[Controller][Channel] < LastPass[Controller][Channel][Byte])) {
          ChLastPass1[Controller][Channel] = LastPass[Controller][Channel][Byte];
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
      RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
      // if nothing for this channel OR No Ranks in this channel
      if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) || (RankMaskCh == 0)) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimal offset Mc %d Channel %d = %d\n", Controller, Channel, ChLastPass1[Controller][Channel]);
    }
  }
#endif // MRC_DEBUG_PRINT
  // Program new value
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
      RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
      // if nothing for this channel OR No Ranks in this channel
      if (!((1 << ((Controller * MaxChannel) + Channel)) & McChBitMask) || (RankMaskCh == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }

      // Start with the most aggressive setting
      ChLastPass = End;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (Update == 0) {
          LastPass[Controller][Channel][Byte] = Begin;
        }

        if ((Inc == 1) && (ChLastPass > LastPass[Controller][Channel][Byte])) {
          ChLastPass = LastPass[Controller][Channel][Byte];
        }

        if ((Inc == -1) && (ChLastPass < LastPass[Controller][Channel][Byte])) {
          ChLastPass = LastPass[Controller][Channel][Byte];
        }

        if (PerByte) {
          UpdateTAParamOffset (MrcData, Controller, Channel, Byte, OptParam, LastPass[Controller][Channel][Byte], Update, 1, RankMaskCh);
        }
      }

      if (PerByte == FALSE) {
        UpdateTAParamOffset (MrcData, Controller, Channel, 0, OptParam, ChLastPass, Update, 1, RankMaskCh);
        if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
          MrcTatStretch (MrcData, Controller, Channel, OptParam, ChLastPass - Start, TRUE);
        }
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected Offset for Mc %d Channel %d is = %d\n", Controller, Channel, ChLastPass);
    }

    if ((OptParam == ddwr2rd) || (OptParam == drwr2rd)) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
          continue;
        }
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, WriteCached,   &RdWrSg[Controller][Channel]);
      }
    }
  }
  return Status;
}

/**
  Sets command margins when moving WrT, WrTBox, or WrV
  NOTE: ONLY one, ResetDDR or SelfRefresh can be set inside this function

  @param[in] MrcData         - Include all MRC global data.
  @param[in] McChBitMask     - Bit mask of populated controllers/channels
  @param[in] Ranks           - Bit Mask of populated ranks
  @param[in] Param           - Input parameter to update
  @param[in] Value0          - value to be added
  @param[in] Value1          - value to be added
  @param[in] ResetDDR        - Do we reset DDR?
  @param[in] SelfRefresh     - Do we perform Self refresh?

  @retval MrcStatus      - If it succeeds return mrcSuccess
**/
void
SetCmdMargin (
  IN MrcParameters *const MrcData,
  IN const UINT8          McChBitMask,
  IN const UINT8          Ranks,
  IN const UINT8          Param,
  IN const UINT8          Value0,
  IN const UINT8          Value1,
  IN UINT8                ResetDDR,
  IN const UINT8          SelfRefresh
  )
{
  MrcOutput         *Outputs;
  INT64             GetSetVal;
  UINT32            Controller;
  UINT32            Channel;
  UINT8             MaxChannel;
  UINT8             RankMaskCh;
  UINT8             Offset;

  Outputs       = &MrcData->Outputs;
  MaxChannel    = Outputs->MaxChannels;
  Offset        = 0;

  if (SelfRefresh && ResetDDR) {
    MRC_DEBUG_MSG (
      &Outputs->Debug,
      MSG_LEVEL_ERROR,
      "WARNING SelfRefresh OR ResetDDR can be set at once...performing SelfRefresh\n"
      );
    ResetDDR = 0;
  }

  if (SelfRefresh) {
    GetSetVal = 1;
    MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);
  }

  // Walk though all mcs, chs and ranks
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (McChBitMask & (1 << ((Controller * MaxChannel) + Channel))) {
        // determine which ranks from parameter "Ranks" exist in this channel
        RankMaskCh = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
        if (RankMaskCh == 0) {
          continue; // No Ranks in this channel
        }
        switch (Param) {
          case WrTBox:
          case WrT:
            ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationClock, RankMaskCh, MRC_IGNORE_ARG_8, Value0, 0);
            if (Param != WrTBox) {
              break;
            }
            /*FALLTHROUGH*/
          // Fall through to WrV if Param is WrTBox.
          case WrV:
            Offset = (Param == WrTBox) ? ((2 * Value1) - 1) * 8 : Value0;
            ChangeMargin (MrcData, WrV, Offset, 0, 0, (UINT8) Controller, (UINT8) Channel, RankMaskCh, 0, 0, 0, 0);
            break;

          default:
            return;
        }
      }
    }
  }

  if (ResetDDR) {
    MrcResetSequence (MrcData);
  } else if (SelfRefresh) {
    MrcSelfRefreshState (MrcData, MRC_SR_EXIT);
  }

  return;
}

/**
  Updates the value for following OptParamCliff variables:
  drrd2rd=0, ddrd2rd=1, drwr2wr=2, ddwr2wr=3, drrd2wr=4, ddrd2wr=5, drwr2rd=6, ddwr2rd=7,
  rdodtd=8, wrodtd=9, mcodts=10, mcodtd=11, rtl=12}

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Controller - Controller to update the specified parameter.
  @param[in]     Channel    - Channel to update the specified parameter.
  @param[in]     Byte       - Byte to update the specified parameter.
  @param[in]     OptParam   - Parameter to update.
  @param[in]     Off        - Value to offset the current setting.
  @param[in]     UpdateHost - Switch to update the host structure with the new value.
  @param[in]     SkipPrint  - Switch to skip debug prints.
  @param[in]     RankMask   - Bit mask of Ranks to update.

  @retval Nothing
**/
void
UpdateTAParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
  IN     const UINT32         Channel,
  IN     const UINT8          Byte,
  IN     const UINT8          OptParam,
  IN     const INT8           Off,
  IN     const UINT8          UpdateHost,
  IN     const UINT8          SkipPrint,
  IN     const UINT8          RankMask
  )
{
  MrcDebug  *Debug;
  MrcOutput *Outputs;
  INT64     GetSetVal;
  INT64     GetSetValSaved1[MAX_RANK_IN_CHANNEL];
  INT64     GetSetValSaved2[MAX_RANK_IN_CHANNEL];
  UINT8     Rank;
  INT8      New;
  UINT8     GsmModeSingle;  //For parameters that only updates one setting
  UINT8     GsmModeMulti;   //For parameters that updates more than one setting
  BOOLEAN   TatUpdate;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  GsmModeMulti  = ForceWriteCached;
  GsmModeSingle = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;
  GetSetVal     = Off;
  TatUpdate     = FALSE;
  if (SkipPrint) {
    GsmModeSingle |= GSM_PRINT_VAL;
    GsmModeMulti  |= GSM_PRINT_VAL;
  }

  //@todo: Update
  switch (OptParam) {
    case drrd2rd:
      // Different Rank RD 2 RD Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddrd2rd:
      // Different DIMM RD 2 RD Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drwr2wr:
      // Different Rank WR 2 WR Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddwr2wr:
      // Different DIMM WR 2 WR Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drrd2wr:
      // Different Rank RD 2 WR Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddrd2wr:
      // Different DIMM RD 2 WR Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drwr2rd:
      // Different Rank WR 2 RD Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddwr2rd:
      // Different DIMM WR 2 RD Turn Around offsets
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case rdodtd:
      // Convert into Register values. 2'b00 = BL/2 + 2 (For Enhanced Channels 10 DCLKs, otherwise 6 DCLKs)
      // @todo: <CNL> Enhance Channel switch.
      GetSetVal  = Off - 6;
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOdtRdDuration, GsmModeSingle, &GetSetVal);
      break;

/* // Do not seem like this is being used
    case wrodtd:
      // Convert into Register values. 2'b00 = BL/2 + 2 (For Enhanced Channels 10 DCLKs, otherwise 6 DCLKs)
      // @todo: <CNL> Enhance Channel switch.
      GetSetVal  = Off - 6;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtWrDuration, GsmModeSingle, &GetSetVal);
      break;
*/
    case mcodts:
      // MC ODT delay
      if (!UpdateHost) {
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDelay, ReadFromCache, &GetSetValSaved2[0]);
      }
      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDelay, ReadFromCache, &GetSetValSaved1[0]);
      New                   = (INT8) GetSetValSaved1[0] + Off;
      if (New < -4) {
        New = -4; // RcvEnPi[8:6] - 5 qclk Min
      } else if (New > 6) {
        New = 6; // RcvEnPi[8:6] + 5 qclk Max
      }

      GetSetVal             = New;
      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDelay, GsmModeMulti, &GetSetVal);
      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDelay, GsmModeMulti, &GetSetVal);
      if (!UpdateHost) {
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDelay, WriteToCache, &GetSetValSaved1[0]);
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDelay, WriteToCache, &GetSetValSaved2[0]);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (SkipPrint) ? "" : "%d\t", New);
      break;

    case mcodtd:
      // Duration
      if (!UpdateHost) {
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDuration, ReadFromCache, &GetSetValSaved2[0]);
      }
      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDuration, ReadFromCache, &GetSetValSaved1[0]);
      GetSetVal = GetSetValSaved1[0] + Off;

      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDuration, GsmModeMulti, &GetSetVal);
      MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDuration, GsmModeMulti, &GetSetVal);
      if (!UpdateHost) {
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDuration, WriteToCache, &GetSetValSaved1[0]);
        MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDuration, WriteToCache, &GetSetValSaved2[0]);
      }
      break;

    case rtl:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (RankMask & (1 << Rank)) {
          if (!UpdateHost) {
            MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFlybyDelay, ReadFromCache, &GetSetValSaved2[Rank]);
          }
          // Keep RecvEn in place - adjust IoLatency by RTL delta
          MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RoundTripDelay, ReadFromCache, &GetSetValSaved1[Rank]);
          GetSetVal = 0 - (GetSetValSaved1[Rank] - Off);
          MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFlybyDelay, ForceWriteOffsetCached, &GetSetVal);

          GetSetVal = Off;
          MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RoundTripDelay, ForceWriteCached, &GetSetVal);
        }
      }
      if (!UpdateHost) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (RankMask & (1 << Rank)) {
            MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RoundTripDelay, WriteToCache, &GetSetValSaved1[Rank]);
            MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFlybyDelay, WriteToCache, &GetSetValSaved2[Rank]);
          }
        }
      }
      break;

    default:
      break;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    ((OptParam != mcodtd) && (OptParam != mcodts) && (!SkipPrint)) ? "%d\t" : "",
    Off
    );

  if (TatUpdate) {
    // Must update the XARB bubble injector when TAT values change
    SetTcBubbleInjector (MrcData, Controller, Channel);
  }
  return;
}

/**
  This function applies the new DRAM ODT settings
  Walks through various optimizations to get the best result with new ODT values
  This includes WrDS, RdODT, Eq, etc.
  Updates Best* variables if this point if better than the prior points
  chDone is both an input and output.  Reports which channels have a good enough value
  if SkipRd is high, it will skip the read related functions (RdODT, RdEq, RdTiming)

  @param[in]     MrcData              - Include all MRC global data.
  @param[in,out] DimmOptPoints        - Structure of all the DIMM ODT optimal settings.
  @param[in]     ChMask               - Channel to work on.
  @param[in]     RankMask             - Rank to work on.
  @param[in]     OptParamTestList     - List of Opt test(Drive Strength, RxBias, TxEq, RxEq) to run.
  @param[in]     OptParamTestListSize - Size of OptParamTestList.
  @param[in]     SubOptMode           - Training for power or for margin for suboptimizations.
  @param[in]     skipOptTests         - Skips the suboptimization.
  @param[in]     skipOptPrint         - Skip printing of the suboptimization steps.
  @param[in]     RdCenter             - Switch to recenter read.
  @param[in]     WrCenter             - Switch to recenter write.

  @retval mrcSuccess or mrcWrongInputParameter.
**/
MrcStatus
TrainDimmOdtSetting (
  IN     MrcParameters *const MrcData,
  IN OUT DimmOptPoint         *DimmOptPoints,
  IN     UINT8                ChMask,
  IN     UINT8                RankMask,
  IN     UINT8                *OptParamTestList,
  IN     UINT8                OptParamTestListSize,
  IN     TrainingModeType     SubOptMode,
  IN     BOOLEAN              skipOptTests,
  IN     BOOLEAN              skipOptPrint,
  IN     BOOLEAN              RdCenter,
  IN     BOOLEAN              WrCenter
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  DimmOptPoint      *PointResults;
  OptOffsetChByte   BestOffArr[MAX_RANK_IN_CHANNEL];
  UINT8             UPMOptimize[MAX_TRADEOFF_TYPES];
  UINT8             rank;
  UINT8             GlobalRankMask;
  UINT8             LocalRanks[MAX_CHANNEL];
  UINT8             ChBitMask;
  UINT8             Channel;
//  UINT8             TestListFull[] = { RdV, RdT, WrV, WrT }; // List of parameters to margin
  UINT8             TestListRd[]  = { RdV, RdT };
  UINT8             TestListWr[]  = { WrV, WrT };
  UINT8             *TestList;
  UINT8             TestListSize;
  UINT8             Scale3Test[]      = { 1, 2, 1, 0, 0 };
  UINT8             TestListRdLpddr[] = { RdV, RdT, RcvEnaX };
  UINT8             ScaleRdLpddr[]    = { 1, 2, 2, 1, 0 };
  UINT8             *Scale;
  UINT8             i;
  UINT8             t;
  UINT8             ResultType;
  UINT8             RecenterLC;
  UINT8             OptParamLC;
  UINT8             TestResultType[5];
  UINT8             OptParam[2];
  INT8              LStart[2];
  INT8              LStop[2];
  BOOLEAN           Lpddr;
  INT8              GB;

  TestList      = TestListRd;
  TestListSize  = 0;
  RecenterLC    = 15;
  OptParamLC    = OPT_PARAM_LOOP_COUNT + 1;
  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Lpddr         = Outputs->Lpddr;
  PointResults  = DimmOptPoints;
  MrcCall->MrcSetMem ((UINT8 *) BestOffArr, sizeof (BestOffArr), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) UPMOptimize, sizeof (UPMOptimize), 0);
  MrcCall->MrcSetMem ((UINT8 *) TestResultType, sizeof (TestResultType), 0);

  // TrainDDROptParam already check the valid against host chRankBit mask
  // Walk through channels, check if this point is redundant, set RttNom
  ChMask &= Outputs->ValidChBitMask;
  GlobalRankMask = 0;
  ChBitMask     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    LocalRanks[Channel] = 0;
    if ((MRC_BIT0 << Channel) & ChMask) {
      LocalRanks[Channel] = RankMask & ControllerOut->Channel[Channel].ValidRankBitMask;
      if (LocalRanks[Channel]) {
        ChBitMask |= MRC_BIT0 << Channel; // remove ch with no "active" ranks
        GlobalRankMask |= LocalRanks[Channel];
      }
    }
  }

  if (RdCenter) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Vref\n");
    ReadVoltageCentering2D (
      MrcData,
      Outputs->MarginResult,
      ChBitMask,
      RdV,
      0,
      0,
      RecenterLC,
      0
      );
    // @todo: We can add if status fail go to next point.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Read Timing ChBitMask=%x\n", ChBitMask);
    DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      ChBitMask,
      RdT,
      0, // EnPerBit,
      0, // EnRxDutyCycle
      0, // ResetPerBit
      RecenterLC,
      0  // En2D
      );
  }

  if (WrCenter) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Vref\n");
    MrcWriteVoltageCentering2D (MrcData);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Re-center Write Timing ChBitMask=%x\n", ChBitMask);
    DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult, // prev. margin results
      ChBitMask,
      WrT,
      0, // EnPerBit,
      0, // EnRxDutyCycle
      0, // ResetPerBit
      RecenterLC,
      0  // En2D
      );
  }
  // @todo: we could check here if we have some reasonable amount of margin to play with

  // Check if we need to ignore the power column
  if (SubOptMode == MrcTmMargin) {
    ScaleRdLpddr[3] = 0;
    Scale3Test[2]   = 0;
  }

  PointResults->OptParamTestListSize = OptParamTestListSize;
  for (t = 0; t < OptParamTestListSize; t++) {
    Scale = Scale3Test; // Assume base scale.  Update for LPDDR during OptRdOdt
    PointResults->OptParamTestList[t] = OptParamTestList[t];
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParamTestList[%d]=%d , %s\n",t,OptParamTestList[t],TOptParamOffsetString[OptParamTestList[t]]);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParamTestList[%d]=%d OptParamTestListSize=%d\n",t,OptParamTestList[t],OptParamTestListSize);
    OptParam[0] = OptParamTestList[t];
    switch (OptParamTestList[t]) {
      case (OptWrDS):
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          1,
          FullGrid,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,  // Repeats
          skipOptPrint,
          skipOptTests,
          0,          // RdRd2Test
          1,          // GuardBand
          BasicVA     // PatType
          );
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[WrDSOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptRdOdt):
        if (Lpddr) {
          TestList     = TestListRdLpddr;
          TestListSize = ARRAY_COUNT (TestListRdLpddr);
          Scale        = ScaleRdLpddr; // does also RcvEnX
        } else {
          TestList     = TestListRd;
          TestListSize = ARRAY_COUNT (TestListRd);
        }
        if (Outputs->OdtMode == MrcOdtModeVtt) {
          Scale[3] = 0;  //in Vtt mode Odt dont effect power go for best margins
        }
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          1,
          FullGrid,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,                            // Repeats
          skipOptPrint,
          skipOptTests,
          Lpddr ? RdRdTA_All : RdRdTA,  // RdRd2Test
          0,                            // GuardBand
          BasicVA                       // PatType
          );
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RdOdtOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptSComp):
      case (OptCCCSComp):
      case (OptTxDqTco):
      case (OptTxDqsTco):
        break;

      case (OptTxEq):
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (!((MRC_BIT0 << rank) & GlobalRankMask)) {
            continue; // check if rank at least on one channel
          }

          TrainDDROptParam (
            MrcData,
            &BestOffArr[rank],
            ChBitMask,
            (MRC_BIT0 << rank),
            OptParam,
            1,
            FullGrid,
            TestList,
            TestListSize,
            Scale,
            UPMOptimize,
            LStart,
            LStop,
            OptParamLC,
            1,            // Repeats
            skipOptPrint,
            skipOptTests,
            0,            // RdRd2Test
            1,            // GuardBand
            BasicVA       // PatType
            );
          //MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[TxEqOfft][rank], (UINT8 *) &BestOffArr[rank], sizeof (BestOffArr[rank]));
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((MRC_BIT0 << rank) & LocalRanks[Channel])) {
              continue;
              // check if the rank exist in this ch
            }
            for (i = 0; i < TestListSize; i++) {
              // track min margin per ch
              if (BestOffArr[rank].Margins[i][Channel] < BestOffArr[0].Margins[i][Channel]) {
                BestOffArr[0].Margins[i][Channel] = BestOffArr[rank].Margins[i][Channel];
              }
            }
          }
        }
        // copy min result for rank 0
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[TxEqOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0]));
        break;

      case (OptTxEqWrDS):
        OptParam[0] = OptTxEq;
        OptParam[1] = OptWrDS;
        TestList = TestListWr;
        TestListSize = ARRAY_COUNT (TestListWr);
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        LStart[1] = OptParamLimitValue(MrcData, OptParam[1], 0);
        LStop[1]  = OptParamLimitValue(MrcData, OptParam[1], 1);
        GB = 0;
        if (Inputs->PowerTrainingMode == MrcTmPower) {
          if ((Inputs->VccIomV > 900) && (Outputs->Frequency > f1600)) {
            GB = 3 ;
          } else {
            GB = 1;
          }
        }

        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          ARRAY_COUNT (OptParam),
          ChessEven,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC + 1, // @todo adjust lc by rank population
          1,            // Repeats
          skipOptPrint,
          skipOptTests,
          0,            // RdRd2Test
          GB,           // GuardBand
          BasicVA       // PatType
          );

        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[WrDSOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      case (OptRxEq):
        TestList = TestListRd;
        TestListSize = ARRAY_COUNT (TestListRd);
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (!((MRC_BIT0 << rank) & GlobalRankMask)) {
            continue; // check if rank at least on one channel
          }

          TrainDDROptParam (
            MrcData,
            &BestOffArr[rank],
            ChBitMask,
            (MRC_BIT0 << rank),
            OptParam,
            1,
            FullGrid,
            TestList,
            TestListSize,
            Scale,
            UPMOptimize,
            LStart,
            LStop,
            OptParamLC,
            1,            // Repeats
            skipOptPrint,
            skipOptTests,
            RdRdTA,       // RdRd2Test
            0,            // GuardBand
            BasicVA       // PatType
            );
          //MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RxEqOfft][rank], (UINT8 *) &BestOffArr[rank], sizeof (BestOffArr[rank]));
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((1 << rank) & LocalRanks[Channel])) {
              continue; // check if the rank exist in this ch
            }

            for (i = 0; i < ARRAY_COUNT (TestListRd); i++) {
              // track min margin per ch and asign to rank0
              if (BestOffArr[rank].Margins[i][Channel] < BestOffArr[0].Margins[i][Channel]) {
                BestOffArr[0].Margins[i][Channel] = BestOffArr[rank].Margins[i][Channel];
              }
            }
          }
        }
        // copy min result for rank 0
        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RxEqOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0]));
        break;

      case (OptRxBiasCb):
        TestList = TestListRd;
        TestListSize = ARRAY_COUNT (TestListRd);
        OptParam[0] = OptRxBias;
        OptParam[1] = OptRxCb;
        LStart[0] = OptParamLimitValue(MrcData, OptParam[0], 0);
        LStop[0]  = OptParamLimitValue(MrcData, OptParam[0], 1);
        LStart[1] = OptParamLimitValue(MrcData, OptParam[1], 0);
        LStop[1]  = OptParamLimitValue(MrcData, OptParam[1], 1);

        TrainDDROptParam (
          MrcData,
          &BestOffArr[0],
          ChBitMask,
          GlobalRankMask,
          OptParam,
          ARRAY_COUNT (OptParam),
          ChessEven,
          TestList,
          TestListSize,
          Scale,
          UPMOptimize,
          LStart,
          LStop,
          OptParamLC,
          1,            // Repeats
          skipOptPrint,
          skipOptTests,
          RdRdTA,       // RdRd2Test
          0,            // GuardBand
          BasicVA       // PatType
          );

        MrcCall->MrcCopyMem ((UINT8 *) &PointResults->BestOptOff[RdSAmpOfft][0], (UINT8 *) &BestOffArr[0], sizeof (BestOffArr[0])); // Result in Rank 0
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptParam Test not valid\n");
        return mrcWrongInputParameter;
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(LocalRanks[Channel])) {
        continue; // check if the active rank run this ch
      }
      // run through all BestOff[optParam][0] and track min[RdV,RdT,WrV,WrT]
      for (i = 0; i < TestListSize; i++) {
        ResultType = GetMarginResultType (TestList[i]);
        if ((ResultType >= ARRAY_COUNT (TestResultType)) || (ResultType >= MAX_TRADEOFF_TYPES)) {
          return mrcFail;
        }
        TestResultType[ResultType] = TestList[i]; // indicate which test we run and create the reverse dic
        //we need to update only last results
        PointResults->Test[ResultType][Channel] = BestOffArr[0].Margins[i][Channel];
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BestOffArr[0].Margins[test index i=%d][%d] =%d\n", i, Channel, BestOffArr[0].Margins[i][Channel]);
      }
    }
  } // end for OptParamTest
  // assign the point for passing to the FindOptimalTradeOff function
  i                       = 0;
  PointResults->NumTests  = 0;
  for (t = 0; t < 4; t++) {
    if (TestResultType[t] == 0) {
      continue; // can only be 1,2,4,5 (WrV,RdV ..)
    } else {
      PointResults->TestList[i] = TestResultType[t];
      PointResults->NumTests++;
      // sorting test for TradeOff
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(LocalRanks[Channel])) {
          continue; // check if the active rank run this ch
        }
        PointResults->Points2Trade[i][Channel] = PointResults->Test[t][Channel];
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PointResults->TestList[%d]=%d PointResults->Test[test index=%d][channel=%d] =%d\n",i,PointResults->TestList[i],t,Channel,PointResults->Test[t][Channel]);
      }
      i++;
    }
  }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PointResults->NumTests =%d\n",PointResults->NumTests);
  return mrcSuccess;
}

/**
  This function applies an offset to the global compensation logic.
  Reruns Compensation and returns the new comp value

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in]     param           - Parameter defining the desired global compensation logic
  @param[in]     offset          - Value to apply
  @param[in]     AjustOdtStatic  - Decides if Static ODT will be adjusted for ReadODT param
  @param[in]     UpdateHost      - Decides if MrcData has to be updated

  @retval Returns the new comp value.
**/
UINT32
UpdateCompGlobalOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          offset,
  IN     const BOOLEAN        AjustOdtStatic,
  IN     const BOOLEAN        UpdateHost
  )
{
  INT64     RcompOdt;
  INT64     GetSetVal;
  UINT32    GsModeFlags;
  GSM_GT    GetSetWrite[MaxCompGlobalOffsetParam] = {DqOdtVrefUp, DqOdtVrefDn, DqDrvVrefUp, DqDrvVrefDn, CmdDrvVrefUp, CmdDrvVrefDn, CtlDrvVrefUp, CtlDrvVrefDn, ClkDrvVrefUp, ClkDrvVrefDn, GsmGtDelim, GsmGtDelim, GsmGtDelim, GsmGtDelim, GsmGtDelim, GsmGtDelim};
  GSM_GT    GetSetRead[MaxCompGlobalOffsetParam] = {CompRcompOdtUp, CompRcompOdtDn, TxRonUp, TxRonDn, WrDSCodeUpCmd, WrDSCodeDnCmd, WrDSCodeUpCtl, WrDSCodeDnCtl, WrDSCodeUpClk, WrDSCodeDnClk, SCompCodeDq, SCompCodeCmd, SCompCodeCtl, SCompCodeClk, GsmGtDelim, CompRcompOdtUp};

  GsModeFlags = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;

  // For CCC params, we assume CMD/CTL/CLK comps are set to the same value since they are trained together
  // Update offset in local CR variable
  if (GetSetWrite[param] != GsmGtDelim) {
    GetSetVal = offset;
    MrcGetSetNoScope (MrcData, GetSetWrite[param], GsModeFlags, &GetSetVal);
  }
  switch (param) {
    case SCompDq:
      // Apply Comp Offset to Scomp-DQ
      GetSetVal = offset & 0xF;
      MrcGetSetNoScope (MrcData, TxSlewRate, GsModeFlags, &GetSetVal);
      GetSetVal = (offset >> SCOMP_PC_STORAGE_BIT_OFFSET) & 0x1; // The value is stored in bit 4 of the value passed in, because bits 0-3 are now used to store the Scomp value
      MrcGetSetNoScope (MrcData, DqScompPC, GsModeFlags, &GetSetVal);
      break;

    case SCompCmd:
      // Apply Comp Offset to Scomp-CMD/CTL/CLK
      GetSetVal = offset & 0xF;
      MrcGetSetNoScope (MrcData, CmdSlewRate, GsModeFlags, &GetSetVal);
      MrcGetSetNoScope (MrcData, CtlSlewRate, GsModeFlags, &GetSetVal);
      MrcGetSetNoScope (MrcData, ClkSlewRate, GsModeFlags, &GetSetVal);

      GetSetVal = (offset >> SCOMP_PC_STORAGE_BIT_OFFSET) & 0x1; // The value is stored in bit 4 of the value passed in, because bits 0-3 are now used to store the Scomp value
      MrcGetSetNoScope (MrcData, CmdScompPC, GsModeFlags, &GetSetVal);
      MrcGetSetNoScope (MrcData, CtlScompPC, GsModeFlags, &GetSetVal);
      MrcGetSetNoScope (MrcData, ClkScompPC, GsModeFlags, &GetSetVal);
      break;

    case RxLoad:
      // Apply Comp Offset to RxLoad
      GetSetVal = offset;
      // TGL_POWER_TRAINING - Add this:
      //   MrcGetSetNoScope (MrcData, RxLoadCompVref, GsModeFlags, &GetSetVal);
      break;

    case DisOdtStatic:
      // Enable/Disable static read Odt legs for both Dq and Dqs
      GetSetVal = offset;
      MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, GsModeFlags, &GetSetVal);
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataOdtStaticDis, GsModeFlags, &GetSetVal);
      break;

    default:
      break;
  }

  // Run Compensation
  // Start Comp Engine
  ForceRcomp (MrcData);
  if ((param == RdOdtUp) && (AjustOdtStatic)) {
    // we check if we close to saturation and try dis/en the static legs
    MrcGetSetNoScope (MrcData, CompRcompOdtUp, ReadUncached, &RcompOdt);
    if (RcompOdt > 48) { // First, try changing static ODT legs. If that isn't enough, then also change ODTSingleSegEn
      // Change static read Odt legs
      GetSetVal = 0;
      MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, WriteCached, &GetSetVal);
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataOdtStaticDis, WriteCached, &GetSetVal); // Update the Comp Offsets and Host Structure

      ForceRcomp (MrcData); // Re-run compensation
      MrcGetSetNoScope (MrcData, CompRcompOdtUp, ReadUncached, &RcompOdt);

      if (RcompOdt > 48) {
        // Change ODTSingleSegEn
        GetSetVal = 0;
        // TGL_POWER_TRAINING Add GsmIocDataODTSingleSegEn get/set method and make it write to DDRDATA_CR_DDRCrDataControl5_0_0_0_MCHBAR.ODTSingleSegEn
        // MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataODTSingleSegEn, WriteCached, &GetSetVal);

        // Re-run compensation
        ForceRcomp (MrcData);
      }
    } else if (RcompOdt < 16) { // First, try changing ODTSingleSegEn. If that isn't enough, then also change static ODT legs.
      // Change ODTSingleSegEn
      GetSetVal = 1;
      // TGL_POWER_TRAINING Add GsmIocDataODTSingleSegEn get/set method and make it write to DDRDATA_CR_DDRCrDataControl5_0_0_0_MCHBAR.ODTSingleSegEn
      // MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataODTSingleSegEn, WriteCached, &GetSetVal);

      ForceRcomp (MrcData);
      MrcGetSetNoScope (MrcData, CompRcompOdtUp, ReadUncached, &RcompOdt);

      if (RcompOdt < 16) {
          // Change static read Odt legs
          GetSetVal = 1;
          MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, WriteCached, &GetSetVal);
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataOdtStaticDis, WriteCached, &GetSetVal); // Update the Comp Offsets and Host Structure

          ForceRcomp (MrcData); // Re-run compensation
      }
    }
  }

  // Return the new comp code (hardware output)
  if (GetSetRead[param] != GsmGtDelim) {
    MrcGetSetNoScope (MrcData, GetSetRead[param], ReadUncached, &GetSetVal);
  } else {
    // TGL_POWER_TRAINING - Add this:
    GetSetVal = 0; // MrcGetSetNoScope (MrcData, RloadDqsDn, ReadUncached, &GetSetVal);
  }

  return (UINT32) GetSetVal;
}

/**
  Programs Delay/Duration for the SenseAmp and MCODT based on RcvEn timing
  Provide GuardBand > 0 if needed to be more conservative in timing
  Main goal is to optimize power

  @param[in,out] MrcData   - Include all MRC global data.
  @param[in]     GuardBand - QCLK guardband on Duration.

  @retval Nothing
**/
void
UpdateSampOdtTiming (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          GuardBand
  )
{
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  MrcDdrType  DdrType;
  INT64       Min;
  INT64       Max;
  INT64       GetSetOn;   // SenseAmp / ODT delay
  INT64       GetSetOff;  // SenseAmp / ODT duration
  INT64       DqsOff;
  INT64       GetSetVal;
  INT32       On;         // SenseAmp / ODT delay
  INT32       Off;        // SenseAmp / ODT duration
  UINT32      Channel;
  UINT32      Controller;
  UINT32      Byte;
  UINT32      Rank;
  UINT32      Strobe2ClkDriftPs;
  UINT32      Strobe2ClkDriftQclk;
  UINT32      WakeUpQclk;
  UINT32      QclkPs;
  INT16       MaxRcvEn;
  INT16       MinRcvEn;
  INT16       CurRcvEn;
  INT16       QclkPi;
  BOOLEAN     Gear2;
  BOOLEAN     Lpddr5;

  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  DdrType   = Outputs->DdrType;
  Gear2     = Outputs->Gear2;
  Lpddr5    = (DdrType == MRC_DDR_TYPE_LPDDR5);
  if (Lpddr5) {
    // tWCK2DQO is drift of DRAM read data to our WCK.
    Strobe2ClkDriftPs = 1600; //ps
    QclkPs = Outputs->Wckps / ((Gear2) ? 1 : 2);
  } else {
    QclkPs = Outputs->Qclkps;
    if (DdrType == MRC_DDR_TYPE_LPDDR4) {
      Strobe2ClkDriftPs = 1200; //ps
    } else {
      Strobe2ClkDriftPs = 0;
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpdateSampOdtTiming: GuardBand = %d\n", GuardBand);
  MrcGetSetLimits (MrcData, RecEnDelay, &Min, &Max, NULL);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MaxRcvEn  = 0;
          MinRcvEn  = (UINT16) Max;

          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
              CurRcvEn = (INT16) GetSetVal;
              if (MaxRcvEn < CurRcvEn) {
                MaxRcvEn = CurRcvEn;
              }

              if (MinRcvEn > CurRcvEn) {
                MinRcvEn = CurRcvEn;
              }
            }
          }
          // Round Max to nearest cycle
          QclkPi = (Gear2) ? 128 : 64;
          MaxRcvEn = DIVIDECEIL (MaxRcvEn, QclkPi);
          MinRcvEn = MinRcvEn >> (6 + ((Gear2) ? 1 : 0));
          Strobe2ClkDriftQclk = DIVIDECEIL (Strobe2ClkDriftPs, QclkPs);

          // SENSE AMP CAN ONLY BE ON WHEN ODT IS ON FOR EOS REASONS.
          // Ideal: On = 4 - MAX (WakeUpNs, 2Qclk) - TdqsckQclk + MinRcvEnQclk
          //WakeUpQclk = (((QclkPi * MRC_SENSE_AMP_WAKEUP_TIME) + TdqsckPs) / Outputs->Qclkps); // Convert to PI codes
          WakeUpQclk = MRC_SENSE_AMP_WAKEUP_TIME + Strobe2ClkDriftPs;
          WakeUpQclk = DIVIDECEIL (WakeUpQclk, QclkPs); // Convert to PI codes
          WakeUpQclk = MAX (WakeUpQclk, 2);
          On = 4 - WakeUpQclk + MinRcvEn;
          if (MrcData->Inputs.SafeMode) {
            On = 0;
          }

          // Turn Off Samp/ODT 1 qclk after postamble
          Off = (MaxRcvEn - MinRcvEn) + Strobe2ClkDriftQclk + 1 + GuardBand + ((Gear2) ? 2 : 5);

          GetSetOn = On;
          GetSetOff = Off;
          DqsOff = Off * 2;
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDelay,       WriteToCache | PrintValue, &GetSetOn);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, McOdtDuration,    WriteToCache | PrintValue, &GetSetOff);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, DqsOdtDelay,      WriteToCache | PrintValue, &GetSetOn);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, DqsOdtDuration,   WriteToCache | PrintValue, &DqsOff);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDelay,    WriteToCache | PrintValue, &GetSetOn);
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, SenseAmpDuration, WriteToCache | PrintValue, &GetSetOff);
        }
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  return;
}

/**
  Turns off unused portions of the slave DLL to save power

  @param[in,out] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
UpdateSlaveDLLLength (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput           *Outputs;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             MaxChannel;
  UINT8             byte;
  UINT8             rank;
  UINT8             MaxPi;
  INT64             GetSetVal;
  UINT32            Ratio;
  UINT32            TempVar1;
  UINT32            AvgSdllSegmentDisable;
  UINT32            SdllSegDisable;
  UINT32            Average;
  UINT32            Count;
  UINT32            Offset;
  UINT32            VccDllBlock;
  BOOLEAN           BreakOut;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_STRUCT         VccDllFFControl;

  Outputs  = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  Ratio    = 0;
  Average  = 0;
  Count    = 0;
  SdllSegDisable = 0;
  BreakOut = FALSE;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          MaxPi = 0;
          for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
            if (MrcRankExist (MrcData, Controller, Channel, rank)) {
              MrcGetSetStrobe (MrcData, Controller, Channel, rank, byte, RxDqsPDelay, ReadFromCache, &GetSetVal);
              if (MaxPi < GetSetVal) {
                MaxPi = (UINT8) GetSetVal;
              }

              MrcGetSetStrobe (MrcData, Controller, Channel, rank, byte, RxDqsNDelay, ReadFromCache, &GetSetVal);
              if (MaxPi < GetSetVal) {
                MaxPi = (UINT8) GetSetVal;
              }
            }
          }
          // Update SlaveDLL Length for power Savings
          // Calculate which segments to turn off:
          // NEW (OFF: 0, PI<48: 0x2, PI<32: 0x4, PI<16: 0x6)
          // results are:   0, 2 , 4 or 6
          GetSetVal = ((7 - (MaxPi >> 3)) & ~MRC_BIT0);
          MrcGetSetChStrb (MrcData, Controller, Channel, byte, GsmIocSdllSegmentDisable, WriteCached, &GetSetVal);
          SdllSegDisable = (UINT32) GetSetVal;
          Average = Average + (RANGE (SdllSegDisable, 0, 10));
          Count++;
        }
      }
    }
  }//controller

  // Read the first populated VccDllFFControl register
  // @todo : Review this for DDR4 2DPC and DDR5
  for (Controller = 0; (Controller < MAX_CONTROLLER) && (BreakOut == FALSE); Controller++) {
    for (Channel = 0; (Channel < MaxChannel) && (BreakOut == FALSE); Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        VccDllBlock = ((MAX_CCC_PER_CHANNEL * Controller) + Channel);
        Offset = OFFSET_CALC_CH (DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG, DLLDDRDATA1_CR_DDRCRVCCDLLFFCONTROL_REG, VccDllBlock) ;
        VccDllFFControl.Data = MrcReadCR (MrcData, Offset);
        BreakOut = TRUE;
      }
    }
  } //controller
  if (Count == 0) {
    Count = 1;
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_WARNING, "SdllSegDisable for each byte is 0 and is forced to be 1 to avoid divide by zero error. Possibly unpopulated channel\n", Count);
  }
  AvgSdllSegmentDisable = Average / Count;

  TempVar1 = 183 / 8;
  Ratio = (((10 - AvgSdllSegmentDisable) * 170) +  TempVar1* 12) + 670;
  //Ratio = DIVIDEROUND (TempVar2, 1000); // Dont divide, instead multiply the RHS by 1000
  TempVar1 = ((Ratio > 900) && (Ratio <= 1000)) ? 0 : ((Ratio > 800) && (Ratio <= 900)) ? 1 : ((Ratio > 700) && (Ratio <= 800)) ? 2 : 3;
  VccDllFFControl.Bits.VccdllReadPwrSave = (4 * (!(Outputs->Gear2))) + TempVar1;
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLFFCONTROL_REG, VccDllFFControl.Data);
  return;
}

/**
  This function Shifts the CMD timing.
  NOTE: ONLY one, ResetDDR or SelfRefresh can be set inside this function

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in]     Ranks       - Parameter defining the desired global compensation logic
  @param[in]     offset      - per channel Value to shift picode for
  @param[in]     ResetDDR    - Do we reset DDR?
  @param[in]     SelfRefresh - Do we perform Self refresh?
  @param[in]     UpdateHost  - Determines if MrcData has to be updated

  @retval MrcStatus       - If it succeeds return mrcSuccess
**/
MrcStatus
ShiftCh2Ch (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Ranks,
  IN     UINT8                offset[MAX_CONTROLLER][MAX_CHANNEL],
  IN     UINT8                ResetDDR,
  IN     const UINT8          SelfRefresh,
  IN     const UINT8          UpdateHost
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcIntOutput      *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcStatus         Status;
  INT64             GetSetVal;
  UINT32            Controller;
  UINT32            Channel;
  UINT8             Rank;
  UINT8             RankMaskCh;
  UINT8             CmdGroup;
  INT32             NewValue;
  INT32             Offset;

  Status        = mrcSuccess;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);

  if (SelfRefresh && ResetDDR) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "WARNING SelfRefresh OR ResetDDR can be set at once...performing SelfRefresh\n"
      );
    ResetDDR = 0;
  }

  if (SelfRefresh) {
    GetSetVal = 1;
    MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }

      IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];
      RankMaskCh = Ranks & Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;

      if (RankMaskCh == 0) {
        continue;
      }

      Offset = offset[Controller][Channel];

      // Shift CLK (this will shift DQ PIs as well)
      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationClock, RankMaskCh, MRC_IGNORE_ARG_8, Offset, UpdateHost);

      // Shift CTL
      NewValue = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (RankMaskCh & (1 << Rank)) {
          NewValue = (INT32) (IntCmdTiming->CtlPiCode[Rank]) + Offset;
          break;
        }
      }

      ShiftPIforCmdTraining (MrcData, Controller, Channel, MrcIterationCtl, RankMaskCh, MRC_IGNORE_ARG_8, NewValue, UpdateHost);

      // Shift Cmd
      for (CmdGroup = 0; CmdGroup < MAX_COMMAND_GROUPS; CmdGroup++) {
        ShiftPIforCmdTraining (
          MrcData,
          Controller,
          Channel,
          MrcIterationCmd,
          MRC_IGNORE_ARG_8,
          1 << CmdGroup,
          (INT32) IntCmdTiming->CmdPiCode[CmdGroup] + Offset,
          UpdateHost
        );
      }
    } // for Channel
  } // for Controller

  // Reset DDR is required
  if (ResetDDR) {
    Status = MrcResetSequence (MrcData);
  } else if (SelfRefresh) {
    Status = MrcSelfRefreshState (MrcData, MRC_SR_EXIT);
  }

  return Status;
}

/**
  Returns the index into the array OptResult in the MrcOutput structure.

  @param[in] OptParam - Margin parameter

  @retval One of the following values: RdSAmpOfft(0), WrDSOfft (1), RxEqOfft(2), TxEqOfft (3), RdOdtOfft(4)
**/
UINT8
GetOptResultType (
  IN UINT8 OptParam
  )
{
  switch (OptParam) {
  case OptRxBias:
  case OptRxBiasCb:
    return RdSAmpOfft;

  case OptWrDS:
  case OptTxEqWrDS:
    return WrDSOfft;

  case OptRxEq:
    return RxEqOfft;

  case OptTxEq:
    return TxEqOfft;

  case OptRdOdt:
    return RdOdtOfft;

  default:
    return 0; // Return RdSAmpOfft to point to the beginning of the array
  }
}

/**
  Program DimmOptPoint values on CPU and DIMM sides, such as DIMM ODT, CPU ODT, Ron, Slew Rate, Equalization.

  @param[in, out] MrcData          - Include all MRC global data.
  @param[in]      Channel          - Channel to work on.
  @param[in]      RankMask         - Ranks to update Opt Settings.
  @param[in, out] BestDimmOptPoint - Best DIMM Opt settings used to update hardware
  @param[in, out] RttTypeSize      - Which termination to set.
  @param[in]      SkipGRdOdt       - Switch to skip updating CPU ODT
  @param[in]      SkipDimmOdts     - Switch to skip updating DIMM ODT
  @param[in]      SkipBestOffsets  - Switch to skip updating Opt settings
  @param[in]      UpdateHost       - Switch to skip updating MRC host structure

  @retval Nothing
**/
void
UpdateOptPointValues (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN OUT DimmOptPoint         *BestDimmOptPoint,
  IN     UINT8                RttTypeSize,
  IN     BOOLEAN              SkipGRdOdt,
  IN     BOOLEAN              SkipDimmOdts,
  IN     BOOLEAN              SkipBestOffsets,
  IN     BOOLEAN              UpdateHost
  )
{
  MrcOutput       *Outputs;
  UINT8           byte;
  UINT8           rank;
  //UINT8           offset;
  //UINT8           Dimm;
  UINT8           RttLoop;
  UINT8           test;
  UINT8           TestArray[SizeOfTCompOffset];
  UINT16          RcompTargetArray[MAX_RCOMP_TARGETS];
  BOOLEAN         DebugPrint;
  BOOLEAN         PerRank;
  UINT8           Ranks;
  UINT8           OptParam[MAX_GRID_DIM];
  //UINT8           OptParamTest;
  UINT8           OptIdx;
  INT8            ParamOff[MAX_GRID_DIM];
  OptOffsetChByte *PBestOff;
  UINT8           NumTests;
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Debug       = &Outputs->Debug;
  NumTests    = BestDimmOptPoint->OptParamTestListSize;
  DebugPrint  = 0;

  MrcCall->MrcSetMem (TestArray, sizeof (TestArray), 0);
  if (SkipBestOffsets) {
    NumTests = 0;
  }
  // build tests array to update RdSAmpOfft(0), WrDSOfft (1), RxEqOfft(2), TxEqOfft (3), RdOdtOfft(4)
  for (test = 0; test < NumTests; test++) {
    OptParam[0]  = BestDimmOptPoint->OptParamTestList[test];
    TestArray[GetOptResultType (OptParam[0])] = 1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Test - %s : %d ,UpdateHost: %d\n",
      TOptParamOffsetString[OptParam[0]],
      test,
      UpdateHost
      );
  }

  if (!SkipGRdOdt) {
    MrcCall->MrcCopyMem ((UINT8 *) RcompTargetArray, (UINT8 *) Inputs->RcompTarget, sizeof (RcompTargetArray));
    RcompTargetArray[RdOdt] = BestDimmOptPoint->ODTSet.GRdOdt;
    // update GRdOdt
    UpdateCompTargetValue (MrcData, RdOdt, RcompTargetArray, UpdateHost);
    BestDimmOptPoint->ODTSet.GRdOdtCode = GetCompCode ( MrcData, RdOdt, 2);

    if (DebugPrint) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "GRdODT aplly is : %d \n",
        CalcCpuImpedance (MrcData, 0, 0, 0, 0, OptRdOdt, FALSE, 0, FALSE, 0, 0)
        );
    }
  }

  // On ULT (1DPC) DIMM ODT is connected to Vdd, so RttNom must be disabled
  // Apply Best RTT Points
  if (!SkipDimmOdts) {
    for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank += 2) {
      if (!MrcRankExist (MrcData, CONTROLLER_0, Channel, rank)) {
        continue;
      }
      Ranks = (0x3 << rank) & RankMask;
      if (Ranks == 0) {
        continue;
      }
      for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
        SetDimmParamValue (
           MrcData,
          CONTROLLER_0,
           Channel,
           Ranks,
           BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank / 2].RttType[RttLoop],
           BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank / 2].Rtt[RttLoop],
           UpdateHost
          );
        if (DebugPrint) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%s Mc %d Channel %d Ranks  0x%X apply is : %d\t\n",
            TOptParamOffsetString[BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop]],
            cCONTROLLER0, // @todo - 2xMC
            Channel,
            Ranks,
            CalcDimmImpedance (MrcData, cCONTROLLER0, Channel, rank, BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop], FALSE,
            BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].Rtt[RttLoop], FALSE)
            );
        }
      }
    }
  }

  if (NumTests) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      // Apply Best RdOdt and WrDS
      // OdtOff = Off[RdOdtOfft][0][Channel][byte] + RdOdtChOffset[Channel];
      for (test = 0; test < NumTests; test++) {
        OptParam[0]  = BestDimmOptPoint->OptParamTestList[test];
        PBestOff = &BestDimmOptPoint->BestOptOff[GetOptResultType (OptParam[0])][0];
        if ((OptParam[0] == OptRxEq) || (OptParam[0] == OptTxEq)) {
          PerRank = TRUE;
        } else {
          PerRank = FALSE;
        }
        if (OptParam[0] == OptTxEqWrDS) {
          OptParam[0] = OptTxEq;
          OptParam[1] = OptWrDS;
        } else if (OptParam[0] == OptRxBiasCb) {
          OptParam[0] = OptRxBias;
          OptParam[1] = OptRxCb;
        }
        GetParamsXYZ(MrcData, ParamOff, PBestOff->GridDataSet.OptParamLen, PBestOff->GridDataSet.GridMode,
          (UINT8) PBestOff->Offset[Channel][byte], PBestOff->GridDataSet.Start, PBestOff->GridDataSet.OffLen);
        for (OptIdx = 0; OptIdx < PBestOff->GridDataSet.OptParamLen; OptIdx++ ) { // @todo: error checking, exceeding loop
          for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
            if (PerRank) {
              Ranks = 1 << rank;
              if (!(MrcRankExist (MrcData, CONTROLLER_0, Channel, rank) && (Ranks & RankMask))) {
                continue;
              }
            } else {
              Ranks = RankMask;
            }
            UpdateOptParamOffset (
              MrcData,
              Channel,
              Ranks,
              byte,
              OptParam[OptIdx],
              ParamOff[OptIdx],
              UpdateHost
              );
            if (DebugPrint) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "param[%d]=%s best Offset for byte %d RankMask = %x is : %d\t\n",
                OptIdx,
                TOptParamOffsetString[OptParam[OptIdx]],
                byte,
                Ranks,
                ParamOff[OptIdx]
              );
            }
            if (!PerRank) {
              break;
            }
          }
        }
      }
    }
  }
}

/**
  Normalizes the Power values to the Margins passed in Points2Calc.
  Assumes that power numbers are represented as lowest number is the lowest power,
  and inverts the scale such that highest number is the lowest power.  This is done
  before normalizing to margins.

  @param[in]     MrcData       - Include all MRC global data.
  @param[in]     Points2calc   - Data normalize power.
  @param[in]     ArrayLength   - Array length of Points2calc.
  @param[in]     LenMargin     - The length of inputMargins we are optimizing (0 - LenMargin -1).
  @param[in]     TestListSize  - Size of TestList/Scale

  @retval Nothing
**/
void
NormalizePowerToMargins (
  IN     MrcParameters   *MrcData,
  IN     void            *Points2calc,
  IN     UINT8           ArrayLength,
  IN     UINT8           LenMargin,
  IN     UINT8           TestListSize
  )
{
#if (defined (MRC_POWER_TRAINING_DEBUG) && (MRC_POWER_TRAINING_DEBUG == SUPPORT))
  MrcDebug          *Debug;
#endif
  const MRC_FUNCTION *MrcCall;
  UINT16          MaxPoints[MAX_MARGINS_TRADEOFF];
  UINT16          MinPoints[MAX_MARGINS_TRADEOFF];
  UINT16          MaxPwr;
  UINT16          MinPwr;
  UINT8           off;
  UINT8           test;
  UINT16          AveOfMax;
  UINT16          X;
  UINT16          *Points;
  UINT16          *PointsElement;

  MrcCall     = MrcData->Inputs.Call.Func;
#if (defined (MRC_POWER_TRAINING_DEBUG) && (MRC_POWER_TRAINING_DEBUG == SUPPORT))
  Debug       = &MrcData->Outputs.Debug;
#endif
  Points      = (UINT16 *) Points2calc;
  MaxPwr      = 0;
  MinPwr      = 0xffff;

  MrcCall->MrcSetMemWord (MaxPoints, sizeof (MaxPoints) / sizeof (UINT16), 0);
  MrcCall->MrcSetMemWord (MinPoints, sizeof (MinPoints) / sizeof (UINT16), 0xFFFF);

  // Sorting the min max margin points for each test
  for (off = 0; off < LenMargin; off++) {
    for (test = 0; test < TestListSize; test++) {
      PointsElement = (Points + ArrayLength * test + off);
      if (MaxPoints[test] < *PointsElement) {
        MaxPoints[test] = *PointsElement;
      }

      if (MinPoints[test] > *PointsElement) {
        MinPoints[test] = *PointsElement;
      }
    }
    PointsElement = (Points + ArrayLength * TestListSize + off);

    if (MaxPwr < *PointsElement) {
      MaxPwr = *PointsElement;
    }

    if (MinPwr > *PointsElement) {
      MinPwr = *PointsElement;
    }

    if (LenMargin == 1) {
      MaxPwr  = *PointsElement;
      MinPwr  = *PointsElement;
    }
  }

  MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "MaxPwr=%d MinPwr=%d\n",MaxPwr,MinPwr);
  AveOfMax  = 0;
  TestListSize = MIN (TestListSize, ARRAY_COUNT (MaxPoints));
  for (test = 0; test < TestListSize; test++) {
    AveOfMax += MaxPoints[test];
  }
  AveOfMax = AveOfMax / TestListSize;

  MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "Power Values\nBefore\tAfter\n");
  for (off = 0; off < LenMargin; off++) {
    PointsElement = (Points + ArrayLength * TestListSize + off);
    MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "%d\t", *PointsElement);
    if (MaxPwr == MinPwr) {
      X = 0;
    } else {
      X = 100 - 100 * (*PointsElement - MinPwr) / (MaxPwr);
    }
    *PointsElement = AveOfMax * X / 100;
    MRC_POWER_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "%d\n", *PointsElement);
  }
}

#ifdef MRC_DEBUG_PRINT

#if 0 // This function is not used right now
/**
  Prints OptParam values from CRs and Host structure for all ch/Rank/byte as well as
  the Best optimization value (if requested)
  OptWrDS = 0
  OptRdOd = 1
  OptSCom = 2
  OptTCompOff = 3
  OptTxEq = 4
  OptRxEq = 5
  OptRxBias = 6
  OptDimmOdt = 7
  OptDimmOdtWr = 8
  OptDimmRon = 9
  OptDefault = 10

  @param[in] MrcData   - Include all MRC global data.
  @param[in] ChMask    - Channel Mask to print the summary for
  @param[in] RankMask  - Rank Mask to print the summary for (in case Rank is not applicable set RankMask = 0xF)
  @param[in] OptParam  - Defines the OptParam Offsets. OptDefault reports all parameters
  @param[in] OptOff    - Structure containg the best offest and margins for the OptParam.
                         If OptOffsetChByte is not available, NullPtr needs to be passed (void  *NullPtr)
  @param[in] OptResult - True/False: Whether to print the Best optimization value

  @retval Nothing
**/
void
ReadOptParamOffsetSum (
  IN MrcParameters *const MrcData,
  IN UINT8                ChMask,
  IN UINT8                RankMask,
  IN const UINT8          OptParam,
  IN OptOffsetChByte      *OptOff,
  IN BOOLEAN              OptResult
  )
{
  const MrcInput     *Inputs;
  MrcDebug           *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput          *Outputs;
  UINT8              Channel;
  UINT8              Rank;
  UINT8              Byte;
  UINT8              Param;
  UINT8              NumBytes;
  UINT8              ChannelMask;
  INT16              OffArr[2];
  INT16              Best;
  BOOLEAN            PerRank;
  BOOLEAN            SkipByte;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Debug       = &Outputs->Debug;
  ChannelMask = Outputs->ValidChBitMask & ChMask;
  NumBytes    = (UINT8) Outputs->SdramCount;
  MrcCall->MrcSetMemWord ((UINT16 *) OffArr, ARRAY_COUNT (OffArr), 0);

  for (Param = OptWrDS; Param < OptDefault; Param++) {
    if (OptParam == Param || OptParam == OptDefault) {

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nOffsets for Optimization Parameter %s\n", TOptParamOffsetString[Param]);
      PerRank =
        (
          Param == OptTxEq ||
          Param == OptRxEq ||
          Param == OptDimmOdt ||
          Param == OptDimmOdtWr ||
          Param == OptDimmRon
        );
      SkipByte = (Param == OptDimmRon || Param == OptDimmOdt || Param == OptDimmOdtWr);

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((MRC_BIT0 << Channel) & ChannelMask)) {
          continue;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if ((MRC_BIT0 << Rank) & RankMask) {
            if (!(MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank))) {
              continue;
            }

            if (PerRank) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank %d\n", Rank);
            } else if (Rank > 0) {
              continue;
            }

            if (!SkipByte) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Byte\t");
              for (Byte = 0; Byte < NumBytes; Byte++) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Byte);
              }

              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
            }

            if (OptResult) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Opt/CR/Host\t");
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CR/Host\t");
            }

            if (!SkipByte) {
              for (Byte = 0; Byte < NumBytes; Byte++) {
                ReadOptParamOffset (MrcData, &OffArr[0], Channel, Rank, Byte, Param);

                if (OptResult) {
                  Best = OptOff->Offset[Channel][Byte];
                  if (Best != OffArr[0] || Best != OffArr[1]) {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_NOTE,
                      "\nError: Mismatch in Param %s in Channel %d Rank %d Byte %d is found: Best=%d CR=%d Host=%d\n",
                      TOptParamOffsetString[Param],
                      Channel,
                      Rank,
                      Byte,
                      Best,
                      OffArr[0],
                      OffArr[1]
                      );
                  }

                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d/%d/%d\t", Best, OffArr[0], OffArr[1]);
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d/%d\t", OffArr[0], OffArr[1]);
                }
              }
            } else {
              ReadOptParamOffset (MrcData, &OffArr[0], Channel, Rank, 0, Param);

              if (Param == OptDimmRon || Param == OptDimmOdtWr) {
                if (OptResult) {
                  Best = OptOff->Offset[Channel][0];
                  if (Best != OffArr[1]) {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_NOTE,
                      "\nError: Mismatch in Param %s in Channel %d Rank %d is found: Best=%d Host=%d\n",
                      TOptParamOffsetString[Param],
                      Channel,
                      Rank,
                      Best,
                      OffArr[1]
                      );
                  }

                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d/NA/%d", Best, OffArr[1]);
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "NA/%d", OffArr[1]);
                }
              } else if (Param == OptDimmOdt) {
                if (OptResult) {
                  Best = OptOff->Offset[Channel][0];
                  if (Best != OffArr[0]) {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_NOTE,
                      "\nError: Mismatch in Param %s in Channel %d Rank %d is found: Best=%d Host=%d\n",
                      TOptParamOffsetString[Param],
                      Channel,
                      Rank,
                      Best,
                      OffArr[0]
                      );
                  }

                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d/NA/%d", Best, OffArr[0]);
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "NA/%d", OffArr[0]);
                }
              }
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }
        }
      }
    }
  }
}

/**
  Reads OptParam value from CRs and Host structure for a given ch/Rank/byte combination
  OptParam can be: WrDS, RdOdt, TComp, SComp, RxEq, TxEq, RxBias, DIMM Ron, DIMM RttNom or DIMM RttWr

  @param[in]  MrcData  - Include all MRC global data.
  @param[out] FinalVal - Pointer to the array consisting of CR value and Host value for a particular
                         OptParam and given ch/Rank/byte combination.
  @param[in]  Channel  - Channel index to work on.
  @param[in]  Rank     - Rank index to work on (valid only for TxEq and RxEq, for others is ignored)
  @param[in]  Byte     - Byte index to work on.
  @param[in]  OptParam - Defines the OptParam Offsets. Supported OptParam =
                         [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 3: TxEq,
                          4: RxEq, 5: RxBias, 6: DimmOdt, 7: DimmOdtWr]

  @retval Nothing
**/
void
ReadOptParamOffset (
  IN  MrcParameters *const MrcData,
  OUT INT16                *FinalVal,
  IN  const UINT8          Channel,
  IN  const UINT8          Rank,
  IN  const UINT8          Byte,
  IN  const UINT8          OptParam
  )
{
  const MRC_FUNCTION *MrcCall;
  static const UINT16 RttNomMRSEncodingConst[] = {0x00, 0x10, 0x01, 0x11, 0x81, 0x80}; // RttNom Off,120,60,40,30,20 Ohms
  static const UINT16 RttWrMRSEncodingConst[]  = {0x00, 0x02, 0x01};                // RttWr  RttNom,120,60 Ohms
  MrcDebug         *Debug;
  static const UINT8 LpddrRonEnc[] = {0x1, 0x2, 0x3}; //{34,40,48};
  static const UINT8 LpddrOdtEnc[] = {0x0, 0x2, 0x3}; //{0,120,240};
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  UINT16          *MrReg;
  BOOLEAN         Type;
  UINT8           Index;
  UINT16          MRValue;
  UINT16          RttNomMRSEncoding[ARRAY_COUNT (RttNomMRSEncodingConst)];
  UINT16          RttWrMRSEncoding[ARRAY_COUNT (RttWrMRSEncodingConst)];
  UINT16          RttWr;
  UINT16          RttNom;
  UINT16          RttNomMask;
  UINT16          RttWrMask;
  UINT32          Offset;
  INT16           UpOff;
  INT16           DnOff;
  INT64           GetSetVal;
  DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetCompCr;
  DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetCompHost;
  DDRDATA0CH0_CR_TXTRAINRANK0_STRUCT        CrTxTrainRank;
  DDRDATA0CH0_CR_RXTRAINRANK0_STRUCT        CrRxTrainRank;
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT   DdrCrDataControl1Cr;
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT   DdrCrDataControl1Host;

  MrcCall     = MrcData->Inputs.Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  MrcCall->MrcCopyMem ((UINT8 *) RttNomMRSEncoding, (UINT8 *) RttNomMRSEncodingConst, sizeof (RttNomMRSEncoding));
  MrcCall->MrcCopyMem ((UINT8 *) RttWrMRSEncoding, (UINT8 *) RttWrMRSEncodingConst, sizeof (RttWrMRSEncoding));

  // Compensation Offsets
  Type = ((OptParam == OptWrDS) || (OptParam == OptRdOdt) || (OptParam == OptTCompOff) || (OptParam == OptSComp));
  if (Type) {

    Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
    DdrCrDataOffsetCompCr.Data   = MrcReadCR (MrcData, Offset);
    DdrCrDataOffsetCompHost.Data = ChannelOut->DataCompOffset[Byte];

    if (OptParam == OptWrDS) {
      UpOff = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqDrvUpCompOffset;
      DnOff = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqDrvDownCompOffset;
      if (UpOff != DnOff) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "DqDrvUpCompOffset %d is not equal to DqDrvDownCompOffset for Channel=%d, Byte=%d\n",
          UpOff,
          DnOff,
          Channel,
          Byte
          );
      }

      FinalVal[0] = UpOff;
      UpOff = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqDrvUpCompOffset;
      DnOff = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqDrvDownCompOffset;
      if (UpOff != DnOff) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "DqDrvUpCompOffset %d is not equal to DqDrvDownCompOffset for Channel=%d, Byte=%d in Host Structure\n",
          UpOff,
          DnOff,
          Channel,
          Byte
          );
      }

      FinalVal[1] = UpOff;

      if (FinalVal[0] & 0x20) {     // 6-bit 2's complement
        FinalVal[0] -= 0x40;
      }
      if (FinalVal[1] & 0x20) {     // 6-bit 2's complement
        FinalVal[1] -= 0x40;
      }
    } else if (OptParam == OptRdOdt) {
      UpOff = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqOdtUpCompOffset;
      DnOff = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqOdtDownCompOffset;
      if (UpOff != DnOff) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "DqOdtUpCompOffset %d is not equal to DqOdtDownCompOffset for Channel=%d, Byte=%d\n",
          UpOff,
          DnOff,
          Channel,
          Byte
          );
      }

      FinalVal[0] = UpOff;
      UpOff = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqOdtUpCompOffset;
      DnOff = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqOdtDownCompOffset;
      if (UpOff != DnOff) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "DqOdtUpCompOffset %d is not equal to DqOdtDownCompOffset for Channel=%d, Byte=%d in Host Structure\n",
          UpOff,
          DnOff,
          Channel,
          Byte
          );
      }

      FinalVal[1] = UpOff;

      if (FinalVal[0] & 0x10) {     // 5-bit 2's complement
        FinalVal[0] -= 0x20;
      }
      if (FinalVal[1] & 0x10) {     // 5-bit 2's complement
        FinalVal[1] -= 0x20;
      }
    } else if (OptParam == OptTCompOff) {
      FinalVal[0] = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqTcoCompOffset;
      FinalVal[1] = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqTcoCompOffset;

      if (FinalVal[0] & 0x10) {     // 5-bit 2's complement
        FinalVal[0] -= 0x20;
      }
      if (FinalVal[1] & 0x10) {     // 5-bit 2's complement
        FinalVal[1] -= 0x20;
      }
    } else if (OptParam == OptSComp) {
      FinalVal[0] = (INT16) (INT32) DdrCrDataOffsetCompCr.Bits.DqSlewRateCompOffset;
      FinalVal[1] = (INT16) (INT32) DdrCrDataOffsetCompHost.Bits.DqSlewRateCompOffset;

      if (FinalVal[0] & 0x10) {     // 5-bit 2's complement
        FinalVal[0] -= 0x20;
      }
      if (FinalVal[1] & 0x10) {     // 5-bit 2's complement
        FinalVal[1] -= 0x20;
      }
    }

    if (FinalVal[0] != FinalVal[1]) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Error: Param %s: CR value %d doesn't match Host value %d for Channel=%d, Byte=%d\n",
        TOptParamOffsetString[OptParam],
        FinalVal[0],
        FinalVal[1],
        Channel,
        Byte
        );
    }
  }
  // Equalization Settings
  Type = ((OptParam == OptTxEq) || (OptParam == OptRxEq));
  if (Type) {
    // TxEq[5:4] = Emphasize   = [3, 6, 9, 12] legs
    // TxEq[3:0] = Deemphasize = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 4*Rsvd] legs
    if (OptParam == OptTxEq) {

     Offset = DDRDATA0CH0_CR_TXTRAINRANK0_REG +
      ((DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel) +
      ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
      ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte);

      CrTxTrainRank.Data  = MrcReadCR (MrcData, Offset);
      // @todo: <CNL> Fix this is broken
      FinalVal[0]         = (INT16) (INT32) CrTxTrainRank.Bits.TxEqualization;
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxEq, ReadFromCache, &GetSetVal);
      FinalVal[1]         = (INT16) GetSetVal;
      FinalVal[0]        &= 0xF;  // Read Deemphasize portion only
      FinalVal[1]        &= 0xF;  // Read Deemphasize portion only
    }
    // RxEQ[4:0] CR Decoding (pF/kOhm)
    //            [2:0]
    //  [4:3]     0        1        2        3        4        5-7
    //     0      0.5/.02  0.5/1.0  0.5/.50  0.5/.25  0.5/.12  rsvd
    //     1      1.0/.02  1.0/1.0  1.0/.50  1.0/.25  1.0/.12  rsvd
    //     2      1.5/.02  1.5/1.0  1.5/.50  1.5/.25  1.5/.12  rsvd
    //     3      2.0/.02  2.0/1.0  2.0/.50  2.0/.25  2.0/.12  rsvd
    // Sweep = 0-19        [4:3] = (Sweep/5)  [2:0] = (Sweep%5)
    if (OptParam == OptRxEq) {
      Offset = DDRDATA0CH0_CR_RXCONTROL1RANK0_REG +
        ((DDRDATA0CH1_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Channel) +
        ((DDRDATA0CH0_CR_RXCONTROL1RANK1_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Rank) +
        ((DDRDATA1CH0_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Byte);

      CrRxTrainRank.Data = MrcReadCR (MrcData, Offset);
      FinalVal[0] = (INT16) (INT32) CrRxTrainRank.Bits.RxEq;
      FinalVal[1] = (INT16) (INT32) ChannelOut->RxEq[Rank][Byte];
      FinalVal[0] = ((FinalVal[0] >> 3) * 5) + (FinalVal[0] & 0x7);  // Multiply Cap portion by 5 and add Res portion
      FinalVal[1] = ((FinalVal[1] >> 3) * 5) + (FinalVal[1] & 0x7);  // Multiply Cap portion by 5 and add Res portion
    }

    if (FinalVal[0] != FinalVal[1]) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Error: Param %s: CR value %d doesn't match Host value %d for Channel=%d, Rank=%d, Byte=%d\n",
        TOptParamOffsetString[OptParam],
        FinalVal[0],
        FinalVal[1],
        Channel,
        Rank,
        Byte
        );
    }
  }
  // RX Amplifier BIAS
  if ((OptParam == OptRxBias)) {
    // Mapping: [0: 0.44, 1: 0.66, 2: 0.88, 3: 1.00, 4: 1.33, 5: 1.66, 6: 2.00, 7: 2.33]
    Offset = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);

    DdrCrDataControl1Cr.Data    = MrcReadCR (MrcData, Offset);
    MrcGetSetChStrb (MrcData, CONTROLLER_0, Channel, Byte, RxBiasIComp, ReadFromCache, &GetSetVal);
    FinalVal[0]                 = (INT16) (INT32) DdrCrDataControl1Cr.Bits.RxBiasCtl;
    FinalVal[1]                 = (INT16) (INT32) GetSetVal;

    if (FinalVal[0] != FinalVal[1]) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Error: Param %s: CR value %d doesn't match Host value %d for Channel=%d, Byte=%d\n",
        TOptParamOffsetString[OptParam],
        FinalVal[0],
        FinalVal[1],
        Channel,
        Byte
        );
    }
  }
  // Dimm Ron value
  if ((OptParam == OptDimmRon)) {
    // DIMM Ron Encoding   DriverImpCtrl[A5,A1]
    if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
      MrReg = &ChannelOut->Dimm[Rank / 2].Rank[(Rank % 2)].MR[mrMR0];
      MRValue     = MrReg[mrMR1];
      FinalVal[1] = (INT16) ((MRValue >> 1) & 0x1);
    }
  }
  // DIMM ODT Values
  if ((OptParam == OptDimmOdt) || (OptParam == OptDimmOdtWr)) {
    // DIMM ODT Encoding   RttNom[A9,A6,A2]   RttWr[A10, A9] LPDDR - No RttNom
    if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
        MrReg       = &ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR0];
        RttNomMask  = (MRC_BIT9 + MRC_BIT6 + MRC_BIT2);
        RttWrMask   = (MRC_BIT10 + MRC_BIT9);
        RttWr       = (MrReg[mrMR2] & RttWrMask) >> 9;
        RttNom      = (MrReg[mrMR1] & RttNomMask) >> 2;

        for (Index = 0; Index < ARRAY_COUNT (RttNomMRSEncodingConst); Index++) {
          if (RttNom == RttNomMRSEncoding[Index]) {
            FinalVal[0] = (INT16) (INT8) Index;
          }
        }

        for (Index = 0; Index < ARRAY_COUNT (RttWrMRSEncodingConst); Index++) {
          if (RttWr == RttWrMRSEncoding[Index]) {
            FinalVal[1] = (INT16) (INT8) Index;
          }
        }
    }
  }
}

/**
  This function will print out the last margin data collected of the Param passed in.
  It will print both edges of all the requested bytes, Ranks and Channels.
  NOTE: The function will not check to see if the Rank/Channel exists.  It will print out the
  values stored in the margin array regardless of population status.

  @param[in]  MrcData     - Global MRC data.
  @param[in]  Param       - Parameter of MRC_MarginTypes of which to print the margin.
  @param[in]  ChannelMask - Bit mask of channels to print.
  @param[in]  RankMask    - Bit mask of ranks to print.
  @param[in]  ByteMask    - Bit mask of bytes to print.

  @retval Nothing.
**/
void
MrcPrintLastMargins (
  IN MrcParameters *const MrcData,
  IN const UINT8          Param,
  IN const UINT8          ChannelMask,
  IN const UINT8          RankMask,
  IN const UINT16         ByteMask
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  char            *EdgeString;
  MrcMarginResult LastResultParam;
  UINT32          (*LastMargins)[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT8           Channel;
  UINT8           Rank;
  UINT8           Byte;
  UINT8           Edge;

  LastResultParam = GetMarginResultType (Param);
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  LastMargins     = Outputs->MarginResult;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%s Last Margins:\n",
    gMarginTypesStr[Param]
    );

  EdgeString = ((Param == RdV) || (Param == WrV)) ? "H" : "R";

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Byte\t");
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if ((1 << Byte) & ByteMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 10d", Byte);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nEdge\t");
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if ((1 << Byte) & ByteMask) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    L    %s", EdgeString);
    }
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & RankMask) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((1 << Channel) & ChannelMask) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nR%d.C%d\t", Rank, Channel);
          for(Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if ((1 << Byte) & ByteMask) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 5d", LastMargins[LastResultParam][Rank][Channel][Byte][Edge]);
              }
            }
          }
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table
}
#endif // #if 0

/**
  This function implements switch to print the correct format and data for the
  OptResultsPerByte struct members.

  @param[in] Debug     - Debug pointer for printing.
  @param[in] Data      - Pointer to OptResultsPerByte struct.
  @param[in] TypeIndex - Member of OptResultsPerByte to print.
  @param[in] TestIndex - Some parameters store multiple test results to be printed.
  @param[in] MidPoint  - Used to convert from zero-based indexing to the selected value

  @retval Nothing.
**/
void
MrcOptResultsPerBytePrint (
  IN MrcDebug *const    Debug,
  IN OptResultsPerByte  *Data,
  IN UINT8              TypeIndex,
  IN UINT8              TestIndex,
  IN INT8               MidPoint
  )
{
  switch (TypeIndex) {
    case (MrcOptResultBest):
      (TestIndex == 0) ? MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "=== %d ===", Data->Best - MidPoint) :
                         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
      break;

    case (MrcOptResultGrdBnd):
      (TestIndex == 0) ? MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** %d ***", Data->GuardBand) :
                         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
      break;

    case(MrcOptResultOffSel):
      (TestIndex == 0) ? MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> %d <--", Data->Best - MidPoint + Data->GuardBand) :
                         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
      break;

    case (MrcOptResultScale):
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Data->Scale[TestIndex]);
      break;

    case (MrcOptResultMaxPost):
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Data->MaxPost[TestIndex]);
      break;

    case (MrcOptResultMinPost):
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Data->MinPost[TestIndex]);
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "OptResultPerByteDbgStr Switch exceeded number of cases defined\n");
  }
}


/**
  This function prints the Optimize margin result table
  e.g: calcResultSummary[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]

  @param[in] MrcData           - MRC data structure
  @param[in] calcResultSummary - The data array [MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  @param[in] TestList          - Test list
  @param[in] NumTest           - Number of test
  @param[in] NumOffsets        - Number of offsets
  @param[in] MidPoint          - Middle point
  @param[in] IncEnds           - Print ends points
  @param[in] OptParam          - Used to convert to the Opt param string for printing
  @param[in] OptPower          - Opt Power values to be printed
  @param[in] Channel           - Channel to print
  @param[in] Ranks             - Ranks to print
  @param[in] TrendLine         - Switch to print the trend line
  @param[in] Nibble            - take low/high bytes
  @param[in] perCh             - Switch to only print 1 Byte of data
  @param[in] noPrint           - Boolean used to disable printing of results

  @retval Nothing
**/
void
PrintCalcResultTableCh (
  IN MrcParameters *const MrcData,
  IN OptResultsPerByte    calcResultSummary[MAX_SDRAM_IN_DIMM],
  IN const UINT8          *TestList,
  IN UINT8                NumTest,
  IN UINT8                NumOffsets,
  IN INT8                 MidPoint,
  IN BOOLEAN              IncEnds,
  IN UINT8                OptParam,
  IN UINT16               *OptPower,
  IN UINT8                Channel,
  IN UINT8                Ranks,
  IN BOOLEAN              TrendLine,
  IN UINT8                Nibble,
  IN BOOLEAN              perCh,
  IN BOOLEAN              noPrint
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  OptResultsPerByte *data;
  UINT8             Off; // @todo: change for the new alg.
  UINT8             Start;
  UINT8             Stop;
  UINT8             i;
  UINT8             j;
  UINT8             b;
  UINT8             FirstByte;
  UINT8             NumBytes;
  UINT8             NumTestPlus;
  UINT32            Result;
  BOOLEAN           Format64Results;
  UINT8             Param;

  MrcCall         = MrcData->Inputs.Call.Func;
  Format64Results = 1;
  // Display result in %/Delta , 0-displat raw 64bit result in HEX
  Debug = &MrcData->Outputs.Debug;
  Start = (!IncEnds);
  Stop  = NumOffsets - (!IncEnds);
  if (noPrint) {
    return ;

  }

  FirstByte = (Nibble) ? 4 : 0;
  NumBytes  = FirstByte + 4 + Nibble * MrcData->Outputs.SdramCount % 8;
  if (perCh) {
    NumBytes = 1;
  }

  NumTestPlus = (TrendLine) ? NumTest + 1 : NumTest;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\n<======== optimize %s ========>Plot results ",
    TOptParamOffsetString[OptParam]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "<Channel=%d><rank/s=0x%x><Nibble=%s> across settings :(Start=%d,Stop=%d)\n",
    Channel,
    Ranks,
    (Nibble) ? "High" : "Low",
    Start - MidPoint,
    Stop - MidPoint - 1
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Bytes\t");
  for (b = FirstByte; b < NumBytes; b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", b);
    for (i = 0; i < NumTestPlus + 1; i++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t"); // tab insertion
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset\t"); // row starts here !
  if (OptPower[Stop - 1] != 0) {//WA: need to add param to enable this print
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t","TotPwr");
  }

  for (b = FirstByte; b < NumBytes; b++) {
    for (i = 0; i < NumTest; i++) {
      // Test types header
      Param = TestList[i];
      if (Param > CmdV) {
        Param = (Param % 16) + 4;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", gMarginTypesStr[Param]);
    }

    if (TrendLine) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", "PwrVal");
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Opt.func\t"); // more header..
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n"); // row end here !
  for (Off = Start; Off < Stop; Off++) {
    // row starts here !
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off - MidPoint);
    if (OptPower[Stop - 1] != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d.%d\t", OptPower[Off]/10, OptPower[Off]%10);
    }

    for (b = FirstByte; b < NumBytes; b++) {
      if (b < MAX_SDRAM_IN_DIMM) {
        data = &calcResultSummary[b];
      } else {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Error: calcResultSummary array out of bounds! %d > %d \n",
          b,
          MAX_SDRAM_IN_DIMM - 1
          );
        return;
      }

      for (i = 0; i < NumTestPlus; i++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", data->Margins[i][Off].EW);
      }

      if (Format64Results) {
        Result = (UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (data->Result[Off], 200), data->MaxR, NULL));
        Result /= 2;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t", Result);
      }

      if (!Format64Results) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%08x-%08x\t\t",
          (UINT32) MrcCall->MrcRightShift64 (data->Result[Off],
                32),
          (UINT32) (data->Result[Off])
          );
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
  }

  for (i = 0; i < ARRAY_COUNT (OptResultDbgStrings); i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OptResultDbgStrings[i]);
    for (b = FirstByte; b < NumBytes; b++) {
      if (b < MAX_SDRAM_IN_DIMM) {
        data = &calcResultSummary[b];
      } else {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Error: calcResultSummary array out of bounds! %d > %d \n",
          b,
          MAX_SDRAM_IN_DIMM - 1
          );
        return;
      }

      for (j = 0; j < NumTestPlus; j++) {
        MrcOptResultsPerBytePrint (Debug, data, i, j, MidPoint);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t"); // tab insertion
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // row end here !
  return;
}

/**
  This function prints the Optimize margin result table: calcResultSummary.

  @param[in] MrcData           - MRC data structure
  @param[in] calcResultSummary - The data array [MAX_STROBES]
  @param[in] DimmOptPoints     - Pointer to the structure holding the test data
  @param[in] NumOffsets        - Number of offsets
  @param[in] MidPoint          - Middle point
  @param[in] IncEnds           - Print ends points
  @param[in] OptParam          - Used to convert to the Opt param string for printing
  @param[in] RttTypeSize       - Rtt values that are being trained
  @param[in] Channel           - Channel to print
  @param[in] Ranks             - Ranks to print
  @param[in] TrendLine         - Switch to print the trend line
  @param[in] printOptSetting   - print sub optimization prints (TxEq/DS etc.) per byte (for power optimization)
  @param[in] Scale             - print the scale (weight) we applied for each test (WrV, WrT, RdV, RdT) for optimization
  @param[in] Nibble            - take low/high bytes
  @param[in] perCh             - Switch to only print 1 Byte of data

  @retval Nothing
**/
void
PrintODTResultTable (
  IN MrcParameters *const MrcData,
  IN OptResultsPerByte    *calcResultSummary,
  IN DimmOptPoint         *DimmOptPoints,
  IN UINT8                NumOffsets,
  IN BOOLEAN              IncEnds,
  IN UINT8                OptParam,
  IN UINT8                RttTypeSize,
  IN UINT8                Channel,
  IN UINT8                Ranks,
  IN BOOLEAN              TrendLine,
  IN BOOLEAN              printOptSetting,
  IN UINT8                *Scale,
  IN UINT8                Nibble,
  IN BOOLEAN              perCh
  )
{
  static const char *Strings[] = {
    //"GRdOdt",
    "Pwr[mW]",
    "Pwr Rd",
    "Pwr Wr"
  };
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  OptResultsPerByte *data;
  UINT8             Off;
  UINT8             Start;
  UINT8             Stop;
  UINT8             i;
//  UINT8             j;
  UINT8             b;
  UINT8             r;
  UINT8             Rank;
  UINT8             NumTestPlus;
  UINT8             *TestList;
  UINT8             Param;
  UINT8             TestSize;
  UINT32            Result;
  UINT8             OptParamType;
  UINT8             OptResultType;
  BOOLEAN           Format64Results; // Display result in %/MaxR , 0-display raw 64bit result in HEX
  INT8              Opt0;
  INT8              Opt1;
  GridData         *GridDataSet;
  INT8             ParamOff[MAX_GRID_DIM];
  UINT8            FirstRank;
  UINT8            Idx;

  MrcCall         = MrcData->Inputs.Call.Func;
  Format64Results = 1;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  Start           = (!IncEnds);
  Stop            = NumOffsets - (!IncEnds);
  TestList        = DimmOptPoints[0].TestList;

  // Find the first selected rank
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((1 << Rank) & Ranks) {
      FirstRank = Rank;  // could be in any channel
      break;
    }
  }

  NumTestPlus = (TrendLine) ? DimmOptPoints[0].NumTests + 1 : DimmOptPoints[0].NumTests;
  // RttNomOffset = (MrcData->Outputs.Channel[Channel].DimmCount == 1) ? 0 : RttOffset; // if 2DPC - RttNom 40,30,20 Ohms
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\n<======== optimize %s ========>Plot results ",
    TOptParamOffsetString[OptParam]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "<Channel=%d><rank/s=0x%x> across settings :(Start=%d,Stop=%d)\n",
    Channel,
    Ranks,
    Start,
    Stop - 1
    );
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ODT\t");
  // for (b = 0; b < ARRAY_COUNT (OdtStrings); b++) {
  //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t",OdtStrings[b] );
  //  for (i = 0; i < NumTestPlus+1; i++) MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");//tab insertion
  // }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");//row end here!
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset\t"); // row starts here!
  for (b = 0; b < RttTypeSize; b++) {
    Idx = MIN ((UINT8) GetRttType(DimmOptPoints[0].ODTSet.DimmOdt[Channel][FirstRank/2].RttType[b]), ARRAY_COUNT (OdtTypeString) - 1);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OdtTypeString[Idx]);
  }
  for (b = 0; b < ARRAY_COUNT (Strings); b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", Strings[b]);
  }

  for (i = 0; i < DimmOptPoints[0].NumTests; i++) {
    // Test types header
    Param = TestList[i];
    if (Param > CmdV) {
      Param = (Param % 16) + 4;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", gMarginTypesStr[Param]);
  }

  if (TrendLine) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", "T.line");
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Opt.func\nScale\t"); // Row starts here
  for (b = 0; b < RttTypeSize; b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }
  for (b = 0; b < ARRAY_COUNT (Strings); b++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }

  TestSize = DimmOptPoints[0].NumTests;
  if (TrendLine) {
    TestSize++;
  }
  for (i = 0; i < TestSize; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Scale[i]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n");

  for (Off = Start; Off < Stop; Off++) {
    // row starts here !
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off);
    for (b = 0; b < RttTypeSize; b++) {
      // @todo - 2xMC
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", CalcDimmImpedance (MrcData, cCONTROLLER0, Channel, FirstRank,
        DimmOptPoints[Off].ODTSet.DimmOdt[Channel][FirstRank/2].RttType[b], TRUE, DimmOptPoints[Off].ODTSet.DimmOdt[Channel][FirstRank/2].Rtt[b], FALSE));
    }
    for (b = 0; b < ARRAY_COUNT (Strings); b++) {
//       if (b == 0) {
//         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t",
//           DimmOptPoints[Off].ODTSet.GRdOdt
//           );
//       }
      if (b == 0) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.TotalPwr / 10,
          DimmOptPoints[Off].PowerCalc.TotalPwr % 10
          );
      }
      if (b == 1) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.RdPower / 10,
          DimmOptPoints[Off].PowerCalc.RdPower % 10
          );
      }
      if (b == 2) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d.%d\t",
          DimmOptPoints[Off].PowerCalc.WrPower / 10,
          DimmOptPoints[Off].PowerCalc.WrPower % 10
          );
      }
    }

    data = calcResultSummary;
    for (i = 0; i < NumTestPlus; i++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t",DimmOptPoints[Off].Points2Trade[i][Channel]);
    }

    if (data->MaxR == 0) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "MaxR - Div by Zero error"
        );
      data->MaxR++;
    }
    if (Format64Results) {
      Result = (UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (data->Result[Off], 200), data->MaxR, NULL));
      Result /= 2;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t", Result);
    } else {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "%08x-%08x\t\t",
        (UINT32) MrcCall->MrcRightShift64 (data->Result[Off],
              32),
        (UINT32) (data->Result[Off])
        );
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
    if (printOptSetting) {
      for (i = 0; i < DimmOptPoints[0].OptParamTestListSize; i++) {
        OptParamType = DimmOptPoints[0].OptParamTestList[i];
        OptResultType = GetOptResultType (OptParamType);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s  \t", TOptParamOffsetString[OptParamType]);
        if ((OptParamType == OptRxEq) || (OptParamType == OptTxEq)) {
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          for (r = 0; r < MAX_RANK_IN_CHANNEL; r++) {
            if (!(Ranks & (0x1 << r))) {
              continue;
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<Rank %d>|", r);
            for (b = 0; b < Outputs->SdramCount; b++) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%02d|",
                DimmOptPoints[Off].BestOptOff[OptResultType][r].Offset[Channel][b]
                );
            }

            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
          }
        } else {
          GridDataSet = &DimmOptPoints[Off].BestOptOff[OptResultType][0].GridDataSet;
          for (b = 0; b < Outputs->SdramCount; b++) {
            if (GridDataSet->OptParamLen > 1) {
              GetParamsXYZ (MrcData, ParamOff, GridDataSet->OptParamLen, GridDataSet->GridMode, (UINT8) DimmOptPoints[Off].BestOptOff[OptResultType][0].Offset[Channel][b], GridDataSet->Start, GridDataSet->OffLen);
              Opt0 = ParamOff[0];
              Opt1 = ParamOff[1];
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%d:%d|",
                Opt0,
                Opt1
                );
            } else {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "%d|",
                DimmOptPoints[Off].BestOptOff[OptResultType][0].Offset[Channel][b]
              );
            }
          }
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n"); // row end here !
      }
    }

  }

//   for (i = 0; i < ARRAY_COUNT (OptResultDbgStrings); i++) {
//     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", OptResultDbgStrings[i]);
//     for (b = FirstByte; b < NumBytes; b++) {
//       data = calcResultSummary;
//       for (j = 0; j < NumTestPlus; j++) {
//         MrcOptResultsPerBytePrint (Debug, data, i, j, MidPoint);
//       }
//       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t");  // tab insertion
//     }
//     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
//   } // row end here !
}

/**
  This function prints the Optimize margin result table
  e.g: MarginResult[Test][Offset][Channel][Byte][sign]

  @param[in] MrcData     - MRC data structure
  @param[in] ChMask      - Channels to print
  @param[in] ResultArray - Array with saved margin results
  @param[in] TestNum     - Test index
  @param[in] OffsetsNum  - number of offsets
  @param[in] MidPoint    - Zero point
  @param[in] OptParam    - Used to convert to the Opt param string for printing
  @param[in] Param       - Margin type to be printed.
  @param[in] PowerLimits - Power limits to print.
  @param[in] noPrint     - Used to skip printing.

  @retval Nothing
**/
void
PrintResultTableByte4by24 (
  IN MrcParameters   *MrcData,
  IN UINT8           ChMask,
  IN UINT16          ResultArray[4][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT16          TestNum,
  IN UINT8           OffsetsNum,
  IN UINT8           MidPoint,
  IN UINT8           OptParam,
  IN UINT8           Param,
  IN UINT16          *PowerLimits,
  IN BOOLEAN         noPrint
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  UINT8           Channel;
  UINT8           Byte;
  UINT8           Off;
  UINT8           Start;
  UINT8           Stop;

  // @todo new alg. change pass start stop...
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Start   = -MidPoint;
  Stop    = OffsetsNum - MidPoint - 1;
  if (Param > CmdV) {
    Param = (Param % 16) + 4;
  }

  if (noPrint) {
    return;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\nTest number: %d - %s, Plot results across OptParam=%s (Start=%d,Stop=%d)",
    TestNum,
    gMarginTypesStr[Param],
    TOptParamOffsetString[OptParam],
    Start,
    Stop
    );

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "w/power limits(width): %d\nChannel\t0\t\t\t\t\t\t\t\t1\nByte\t",
    PowerLimits[TestNum]
    );

  for (Channel = 0; Channel < 2; Channel ++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t", Byte);
    }
  }
  // Sweep through OpParam settings
  for (Off = Start; Off < Stop + 1; Off++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  %d:\t", Off);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      // spaces for non populated channel
      if (!((1 << Channel) & ChMask)) {
        if (Channel == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Outputs->SdramCount == 8) ? "\t\t\t\t\t\t\t\t" : "\t\t\t\t\t\t\t\t\t");
        }
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (Byte < MAX_SDRAM_IN_DIMM) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%d\t",
            ResultArray[TestNum][Off - Start][Channel][Byte]
            );
          }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // New line after the end of the table

  return;
}

/**
  This function prints the Optimize margin result table
  e.g: MarginResult[Test][Offset][Channel][Byte][sign]

  @param[in] MrcData            - MRC data structure
  @param[in] Channel            - Channel to print
  @param[in] Byte               - Byte to print
  @param[in] calcResultSummary  - Array with saved margin results
  @param[in] BestOff            - Pointer to the selected offsets
  @param[in] Param              - Margin type to print.
  @param[in] OffsetsNum         - number of offsets
  @param[in] Start              - Start offsets
  @param[in] Stop               - End offsets
  @param[in] OptParam           - List of optimization parameters
  @param[in] OptParamLen        - Number of optimization parameters
  @param[in] PowerLimits        - Power limits to print.
  @param[in] Dim                - Dimension
  @param[in] TestNum            - Test index
  @param[in] NumTests           - Number of tests
  @param[in] noPrint            - Used to skip printing.

  @retval Nothing
**/
void
Print2DResultTableChByte (
  IN MrcParameters      *MrcData,
  IN UINT8              Channel,
  IN UINT8              Byte,
  IN OptResultsPerByte  *calcResultSummary,
  IN OptOffsetChByte    *BestOff,
  IN UINT8              Param,
  IN UINT8              OffsetsNum,
  IN INT8               *Start,
  IN INT8               *Stop,
  IN const UINT8        *OptParam,
  IN UINT8              *OptParamLen,
  IN UINT16             *PowerLimits,
  IN UINT8              Dim,
  IN UINT16             TestNum,
  IN UINT8              NumTests,
  IN BOOLEAN            noPrint
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT8             Off;
  UINT8             XOff;
  UINT8             YOff;
  OptResultsPerByte *data;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  if (Param > CmdV) {
    Param = (Param % 16) + 4;
  }

  if (noPrint) {
    return;
  }

  if ((Byte == 0) && ((Dim > 1) || (TestNum == 0))) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nPlot Margin %s results across OptParam=%s Start=%d Stop=%d ",
      (Dim > 1)? gMarginTypesStr[Param] : "",
      TOptParamOffsetString[OptParam[0]],
      Start[0],
      Stop[0]
    );

    if (Dim > 1) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "& OptParam=%s Start=%d Stop=%d, power limits=%d\n",
        TOptParamOffsetString[OptParam[1]],
        Start[1],
        Stop[1],
        PowerLimits[TestNum]
      );
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }
  // Sweep through OpParam settings
  data = calcResultSummary;
  // print param0 header and offsets
  if ((Dim > 1) || ((TestNum == 0) && (Byte == 0))) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\n\t", TOptParamOffsetString[OptParam[0]]);
  //     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dB%d\t", Channel, Byte);
    for (Off = 0; Off < OptParamLen[0]; Off++) {// print param0 offsets
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Off + Start[0]);
    }
  }
  // print param1 header
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s\t", (Dim > 1) ? TOptParamOffsetString[OptParam[1]] : "");

  if ((Dim > 1 ) || (TestNum == 0)) {
  // print Ch Byte and separators, the -1 is result of the 2 tab width of below line
    for (Off = 0; Off < (OptParamLen[0] - 1); Off++) {
      if (Off == (OptParamLen[0] / 2 - 1)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dB%d %s", Channel, Byte, (Dim > 1)? gMarginTypesStr[Param] : "---");
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--------");
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "----");
  }

  for (Off = 0; Off <  OffsetsNum; Off++) {
    XOff = Off % OptParamLen[0];
    YOff = Off / OptParamLen[0];
    if (XOff == 0) {
      if (Dim > 1) { // print param1 offset
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%d\t", YOff + Start[1]);
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s\t", gMarginTypesStr[Param]);
      }
    }
    //(UINT32) (MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (data->Result[Off], 200), data->MaxR, NULL)/2)
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", data->Margins[TestNum][Off].EW);
    if (BestOff->Offset[Channel][Byte] == Off) { // mark the chosen one
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "**");
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
  }

  if ((Dim > 1) || (TestNum == (NumTests - 1))) {
    // print separators between ch or at last test in list
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t");
    for (Off = 0; Off < (OptParamLen[0] - 1); Off++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--------");
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "----\n");
  }

  return;
}
#endif // MRC_DEBUG_PRINT

/**
  This function returns the UPM or PWR limit value for the specified parameter

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Margin type
  @param[in] LimitType - Type of limit: UpmLimit or PowerLimit

  @retval Returns the UPM or PWR limit
**/
UINT16
MrcGetUpmPwrLimit (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                LimitType
  )
{
  MrcIntOutput           *IntOutputs;
  MrcOutput              *Outputs;
  const MrcInput         *Inputs;
  MrcDdrType             DdrType;
  MrcUpmPwrRetrainLimits *MrcLimits;
  UINT32                 Index;
  UINT16                 Limit;

  Limit      = 0;
  Outputs    = &MrcData->Outputs;
  Inputs     = &MrcData->Inputs;
  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MrcLimits  = IntOutputs->UpmPwrRetrainLimits.Pointer;
  DdrType    = Outputs->DdrType;

  for (Index = 0; Index < MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS; Index++) {
    if (Param == MrcLimits[Index].Param) {
      Limit = MrcLimits[Index].ParamLimit[LimitType];
      break;
    }
  }

  if (LimitType != RetrainLimit) {
    if ((Param == WrV) && (Outputs->Frequency > f1867)) { // TGL_POWER_TRAINING May need to change this speed or eliminate this case (or add others)
      Limit += 160;
    }

    if ((Inputs->PowerTrainingMode == MrcTmMargin) && (LimitType == PowerLimit)) {
      Limit += 120;
    }
  }

  // TGL_POWER_TRAINING - Need to look into how this limit changes with DDR5.
  if (Param == WrV || Param == CmdVref) {
    // Divide by (<memory> vref step size / LP4 vref step size * 10)
    if (DdrType == MRC_DDR_TYPE_DDR4) {
      if (Param == WrV) {
        Limit = ((Limit * 10) / 16); // DDR4 TxVref 0.65% step size
      } else {
        Limit = ((Limit * 10) / 7); // DDR4 CmdVref 0.26% step size
      }
    } else if (DdrType == MRC_DDR_TYPE_LPDDR4 && Outputs->Lp4x) {
      Limit = ((Limit * 10) / 15); // LP4x 0.6% step size
    } else if (DdrType == MRC_DDR_TYPE_LPDDR5) {
      Limit = ((Limit * 10) / 8); // LP5 0.5% step size
    }
  }

  if ((Inputs->PowerTrainingMode == MrcTmPower) && (DdrType == MRC_DDR_TYPE_LPDDR4) && (LimitType == UpmLimit)) {
    if (Param == RdV) {
      Limit += 120;
    } else if (Param == RdT) {
      Limit += 80;
    }
  }

  return Limit;
}


/**
  This function returns the Start/Stop limits value for the specified parameter

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Opt Param type
  @param[in] LimitType - Type of limit: 0 - Start 1 - Stop

  @retval Returns the Start or Stop limit
**/
INT8
OptParamLimitValue (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                LimitType
  )
{
  MrcDebug                 *Debug;
  MrcOutput                *Outputs;
  const MrcInput           *Inputs;
  const MrcOptParamsLimits *MrcLimits;
  UINT32                   Index;
  INT8                     Limit;
  BOOLEAN                  NotFound;

  Limit      = 0;
  NotFound   = TRUE;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  Inputs     = &MrcData->Inputs;
  MrcLimits  = MrcOptParamLimit;

  for (Index = 0; Index < MRC_NUMBER_OPT_PARAMS_TRAIN; Index++) {
    if (Param == MrcLimits[Index].Param) {
      if (Outputs->Frequency < f1600) { // TGL_POWER_TRAINING May need to change this speed
        Limit = MrcLimits[Index].SaGvLimits[LimitType];
      } else if (Inputs->PowerTrainingMode == MrcTmMargin || Inputs->DtHalo) {
        Limit = MrcLimits[Index].MaxPerfLimits[LimitType];
      } else {
        Limit = MrcLimits[Index].Limits[LimitType];
      }
      NotFound =FALSE;
      break;
    }
  }

  if (NotFound) {
    MRC_DEBUG_ASSERT (
      FALSE,
      Debug,
      "Can't find OptParamLimit for param %s",
      TOptParamOffsetString[Param]
      );
  }
  return Limit;
}

/**
  This function will adjust the requested Limit Type of the margin parameter by the signed offset passed in.

  @param[in]  MrcData   - MRC global data.
  @param[in]  Param     - Margin parameter type to adjust.
  @param[in]  LimitType - MRC_MARGIN_LIMIT_TYPE to adjust.
  @param[in]  Offset    - The adjustment value.

  @retval UINT16 - The new value of Param[MRC_MARGIN_LIMIT_TYPE]
**/
UINT16
MrcUpdateUpmPwrLimits (
  IN OUT MrcParameters * const  MrcData,
  IN UINT8                      Param,
  IN UINT8                      LimitType,
  IN INT8                       Offset
  )
{
  MrcIntOutput            *IntOutputs;
  MrcUpmPwrRetrainLimits  *MrcLimits;
  UINT32                  Index;
  INT32                   UpdatedValue;

  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  MrcLimits     = IntOutputs->UpmPwrRetrainLimits.Pointer;
  UpdatedValue  = 0;

  for (Index = 0; Index < MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS; Index++) {
    if (Param == MrcLimits[Index].Param) {
      UpdatedValue = MrcLimits[Index].ParamLimit[LimitType];
      break;
    }
  }

  UpdatedValue += Offset;
  UpdatedValue = MAX (UpdatedValue, 0);
  UpdatedValue = MIN (UpdatedValue, 0xFFFF);

  MrcLimits[Index].ParamLimit[LimitType] = (UINT16) UpdatedValue;

  return (UINT16) UpdatedValue;
}

/**
  Returns the Actual DIMM Driver/Odt Impedance in Ohms.
  Note: host structure calculation based.

  @param[in] MrcData       - Pointer to MRC global data.
  @param[in] Controller    - Zero based controller number.
  @param[in] Channel       - Zero based channel number.
  @param[in] Rank          - Zero based rank number.
  @param[in] OptParam      - Param to read.
  @param[in] Override      - Override host read value.
  @param[in] OverrideValue - Value to override.
  @param[in] GetFromTable  - Get the Values from Odt tables

  @retval Returns the DIMM driver impedance value in Ohms
**/
UINT16
CalcDimmImpedance (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT8                OptParam,
  IN BOOLEAN              Override,
  IN UINT16               OverrideValue,
  IN BOOLEAN              GetFromTable
  )
{
  MrcOutput                   *Outputs;
  MrcChannelOut               *ChannelOut;
  MrcDebug                    *Debug;
  MrcDdrType                  DdrType;
  // DDR4 Parameters
  static const UINT16         Ddr4RttNomDic[8] = { 0xFFFF, 60, 120, 40, 240, 48, 80, 34 }; // Same for Rtt_Park
  static const UINT16         Ddr4RttWrDic[5]  = { 0, 120, 240, 0xFFFF, 80 };              // in DDR4 we dont assert odt to target so 0 = off also
  static const UINT16         Ddr4RonDic[2]    = { 34, 48};
  // LPDDR4/LPDDR5 Parameters
  static const UINT16         Lpddr4OdtDic[7]  = { 0xFFFF, 240, 120, 80, 60, 48, 40 };
  static const UINT16         Lpddr4RonDic[6]  = { 240, 120, 80, 60, 48, 40 };             // MR3 PD-DS ; Note: Index starts from 1 (0 field values is RFU)
  DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister1;
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister2;
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister5;
  UINT8                       MaxLpddrIndex;
  UINT32                      Dimm;
  BOOLEAN                     Ddr4;
  BOOLEAN                     Lpddr;
  UINT16                      LpddrMr;
  UINT16                      *MR;
  TOdtValueDdr4               *Ddr4OdtTableIndex;
  TOdtValueLpddr              *Lpddr4OdtTableIndex;
  UINT16                      Impedance = 0xFFFF; // Odt off
  UINT8                       MrIndex;
  UINT8                       MrNum;
  UINT16                      MrValue;

  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  Debug       = &Outputs->Debug;
  DdrType     = Outputs->DdrType;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr       = Outputs->Lpddr;
  Dimm        = RANK_TO_DIMM_NUMBER (Rank);

  if (GetFromTable) {
    if (Ddr4) {
      Ddr4OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Controller, Channel, Dimm);
      if (Ddr4OdtTableIndex == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s: OdtTableIndex is NULL!\n", gErrString);
        return 0;
      }
      if (OptParam == OptDimmOdtWr) {
        Impedance = Ddr4OdtTableIndex->RttWr;
      } else if (OptParam == OptDimmOdtPark) {
        Impedance = (Ddr4OdtTableIndex->RttPark == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttPark;
      } else if (OptParam == OptDimmOdtNom) {
        // Our convention is that ODT Write/Park is symmetric, ODT Nom is not (e.g 1R-2R vs. 2R-1R)
        Impedance = (Ddr4OdtTableIndex->RttNom == 0) ? 0xFFFF : Ddr4OdtTableIndex->RttNom;
      }
    } else if (Lpddr) {
      Lpddr4OdtTableIndex = (TOdtValueLpddr *) GetOdtTableIndex (MrcData, Controller, Channel, Dimm);
      if (Lpddr4OdtTableIndex == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s: OdtTableIndex is NULL!\n", gErrString);
        return 0;
      }
      if (OptParam == OptDimmOdtCA) {
        Impedance = Lpddr4OdtTableIndex->RttCa;
      } else if (OptParam == OptDimmOdtWr) {
        Impedance = Lpddr4OdtTableIndex->RttWr;
      }
    }
  } else { // else GetFromTable == FALSE
    MR = ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR;

    if (OptParam == OptDimmOdtWr) {
      GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
      MrValue = ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR[MrIndex];
      if (Ddr4) {
        Ddr4ModeRegister2.Data = MrValue;
        Impedance = Override ? OverrideValue : Ddr4RttWrDic[Ddr4ModeRegister2.Bits.DynamicOdt];
      } else if (Lpddr) {
        LpddrMr = MrValue & 0x7;
        MaxLpddrIndex = ARRAY_COUNT (Lpddr4OdtDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4OdtDic[RANGE (LpddrMr, 0, MaxLpddrIndex)];
      }
    }
    if (OptParam == OptDimmOdtNom) {
      if (Ddr4) {
        GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
        Ddr4ModeRegister1.Data = MR[MrIndex];
        Impedance = Override ? OverrideValue : Ddr4RttNomDic[Ddr4ModeRegister1.Bits.OdtRttValue];
      }
    }

    if (OptParam == OptDimmOdtPark) {
      if (Ddr4) {
        GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
        Ddr4ModeRegister5.Data = MR[MrIndex];
        Impedance = Override ? OverrideValue : Ddr4RttNomDic[Ddr4ModeRegister5.Bits.RttPark];
      }
    }

    if (OptParam == OptDimmRon) {
      GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
      MrValue = ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR[MrIndex];
      if (Ddr4) {
        Ddr4ModeRegister1.Data = MrValue;
        Impedance = Override ? OverrideValue : Ddr4RonDic[Ddr4ModeRegister1.Bits.ODImpedance];
      } else if (Lpddr) {
        LpddrMr = (MrValue >> 3) & 0x7;
        MaxLpddrIndex = ARRAY_COUNT(Lpddr4RonDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4RonDic[RANGE(LpddrMr - 1, 0, MaxLpddrIndex)];
      }
    }

    if (OptParam == OptDimmOdtCA) {
      if (Lpddr) {
        GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
        LpddrMr = (MR[MrIndex] >> 4) & 0x7;
        MaxLpddrIndex = ARRAY_COUNT (Lpddr4OdtDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4OdtDic[RANGE(LpddrMr, 0, MaxLpddrIndex)];
      }
    }
  } //end else GetFromTable

  if ((OptParam == OptDimmOdtCA) && Lpddr) {
    Impedance /= 2;
  }

  return Impedance;
}

/**
  This function returns the Actual Cpu Impedance in Ohms for given OptParam.
  The values will be taken from the host structure, unless override is used.

  @param[in] MrcData        - Pointer to MRC global data.
  @param[in] Controller     - Controller to work on.
  @param[in] Channel        - channel to work on.
  @param[in] Rank           - rank to work on.
  @param[in] Byte           - byte to work on.
  @param[in] OptParam       - param to read
  @param[in] Override       - override enable to verf and offset
  @param[in] OffsetOverride - to override host read value
  @param[in] CompOverride   - override enable
  @param[in] VrefOverride   - value to override
  @param[in] CompCode       - value to override

  @retval Returns the DIMM driver impedance value in Ohms
**/
UINT16
CalcCpuImpedance (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT8                Channel,
  IN UINT8                Rank,
  IN UINT8                Byte,
  IN UINT8                OptParam,
  IN BOOLEAN              Override,
  IN INT8                 OffsetOverride,
  IN BOOLEAN              CompOverride,
  IN INT8                 VrefOverride,
  IN UINT8                CompCode
  )
{
  const MrcInput *Inputs;
  MrcOutput      *Outputs;
  MrcChannelOut  *ChannelOut;
  UINT32         Result;
  UINT16         Rext;
  UINT8          StepSize;
  UINT8          LegsPerSeg;
  UINT8          ODTSingleSegEn;
  UINT32         Rleg;
  UINT8          Segments;
  UINT8          TermFactor;
  UINT16         Divider;
  UINT8          OdtLegsOn;
  UINT8          CurrentComp;
  INT8           VrefOffset;
  INT16          DigiOffset;
  INT64          GetSetVal;
  //UINT8          UnsignedData8;
  UINT32         Numerator;
  UINT32         Denomenator;
  UINT16         VddVoltage;
  DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  VddVoltage  = Outputs->VddVoltage[Inputs->MemoryProfile];
  Numerator   = 0;
  Denomenator = 0;
  DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
  ODTSingleSegEn = 1; // TGL_POWER_TRAINING Add once DDRDATA_CR_DDRCrDataControl5_0_0_0_MCHBAR.ODTSingleSegEn is added to the BIOS cache: (Outputs->ODTSingleSegEn == 1);

  if (CompOverride) {
    VrefOffset = VrefOverride;
    CurrentComp = CompCode;
  } else {
    CurrentComp = GetCompCode (MrcData, OptParam, FALSE); // Get comp code up
    if (OptParam == OptRdOdt || OptParam == OptRdDqOdt) {
      MrcGetSetNoScope (MrcData, DqOdtVrefUp, ReadFromCache, &GetSetVal);
      VrefOffset = (INT8) GetSetVal;
    } /*else if (OptParam == OptWrDS || OptParam == OptTxEq) {
      MrcGetSetNoScope (MrcData, DqDrvVrefUp, ReadFromCache, &GetSetVal);
      VrefOffset = (INT8) GetSetVal;
    }*/ else {
      VrefOffset = 0;
    }
  }

  OdtLegsOn = 1;
  StepSize = MRC_COMP_VREF_STEP_SIZE;

  if (OptParam == OptRdOdt || OptParam == OptRdDqOdt) {
    LegsPerSeg = 8;   // Number of Static legs per segment TGL_POWER_TRAINING - Might change for TGL
    if (Outputs->OdtMode == MrcOdtModeVtt) {
      Segments    = ODTSingleSegEn + 1; // in Vtt mode the segment(s) are compensated to the actual ext. resistor
      TermFactor  = 2; // Terminated to VDD/2
    } else {
      Segments    = 2 * (ODTSingleSegEn + 1); // in Odt mode we have up to 2 segments but we treat up & dn as 2 seperate segments
      TermFactor  = 1; // Terminated to VDD
    }
    MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, ReadFromCache, &GetSetVal);
    OdtLegsOn = GetSetVal ? 0 : 1;
    if (Override) {
      DigiOffset = OffsetOverride;
    } else {
      DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqOdtCompOffset, DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_WID, 8);
    }
  }/* else if ((OptParam == OptWrDS) || (OptParam == OptTxEq)) {
    Segments = 2;
    TermFactor = 1; // @todo: LowSupplyEn calculation factor
    // TxEq full drive bits [4:5]
    // A0: ULX - 3, 6, 8, 10  DT - 4, 8, 12, 15
    // B0: ULX - 4, 6, 8, 10  DT - 6, 9, 12, 15
    MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, TxEq, ReadFromCache, &GetSetVal);
    UnsignedData8 = (UINT8) GetSetVal;
    LegsPerSeg = ((0x3 & (UnsignedData8 >> 4)) + 2 ) * Segments;
    if (Override) {
      DigiOffset = OffsetOverride;
    } else { // from host
      if (OptParam == OptWrDS) {
        DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset, DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID, 8);
      } else { // OptTxEq
        DigiOffset =  (Inputs->UlxUlt) ? (((0xF & (UnsignedData8)) * 2 + 2) / 3) : (0xF & (UnsignedData8));// in ulx num legs 0-10
      }
    }
  }*/ else {
    return 0;
  }

  // TermFactor is always non-zero.  VrefOffset can be zero.
  // Protect by divide by zero here.
  if (VrefOffset == 0) {
    return 0;
  } else {
    Rext = Inputs->RcompResistor;
    // Calc global (Comp) value - Normalize according to LowSupEn
    if (((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) || (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5)) && (Inputs->LowSupplyEnData)) {
      Numerator = Rext * (StepSize * Inputs->VccIomV - VddVoltage * VrefOffset * TermFactor);
      Denomenator = (VddVoltage * VrefOffset * TermFactor);
    } else  {
      Numerator = Rext * (StepSize - (VrefOffset * TermFactor));
      Denomenator = (VrefOffset * TermFactor);
    }
    Denomenator = MAX (Denomenator, 1);
    Result = (UINT16) (Numerator / Denomenator);
    Rleg = Result * (OdtLegsOn * (LegsPerSeg * 10) + CurrentComp * 10);
  }

  /*if (OptParam == OptTxEq) { // we calc here the tx relative to global drv value
    DigiOffset = RatioR2r * DigiOffset; // total number of static legs
    if (DigiOffset == 0) {
      Result = 0xFFFF; // Infinite resistance
    } else {
      Result = DIVIDEROUND (Rleg, DigiOffset); // result is for entire buffer
    }
  } else {*/
    Divider = OdtLegsOn * (LegsPerSeg * 10)  + 10 * (CurrentComp + DigiOffset);
    Divider = MAX (Divider, 1);
    Segments = MAX (Segments, 1);
    Result = Rleg / (Divider * Segments);
  //}
  return (UINT16) Result;
}

/**
  Calculate Power for the selected Opt param based on

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Power       - @todo
  @param[in] Rank        - Rank to work on
  @param[in] OptParam    - Array of parameters to work on.
  @param[in] Offset      - Array of Offsets to work on.
  @param[in] OptParamLen - Length of OptParam[] and Offset[].
  @param[in] CurrentComp - The current Comp code for OptParam
  @param[in] ReadHost    - Switch to read current offset and CompCode from Host structure.
  @param[in] Scale       - @todo

  @retval Calc power in mW
**/
MrcStatus
CalcOptPower (
  IN MrcParameters   *MrcData,
  IN MrcPower        *Power,
  IN UINT8           Rank,
  IN const UINT8     *OptParam,
  IN INT8            *Offset,
  IN UINT8           OptParamLen,
  IN INT8            CurrentComp,
  IN UINT8           Scale
  )
{
  //const MrcInput        *Inputs;
  MrcOutput             *Outputs;
  //MrcIntOutput          *IntOutputs;
  MrcChannelOut         *ChannelOut;
  //static const UINT16   RxPowerConstuW[][2] = {{1288,900}, {1525, 1105}, {1800, 1180}}; // [Vddq current/Vccio Current][ULX/ULT/ULT(DDR3)]  - 100x [mA]  Per Byte
  //static const UINT16   RxPowerScaleSKL[] = {125, 250, 375, 500, 625, 750, 875, 1000, 1125, 1250, 1375, 1500, 1625, 1750, 1875, 2000};
  //UINT8                 RxDefault;
  //UINT32                CPURXPower;
  //UINT16                TxParamVector[MaxTxPowerParam];
  //UINT16                RxParamVector[MaxRxPowerParam];
  BOOLEAN               Override;
  UINT8                 Idx;
  UINT8                 Channel;
  UINT8                 Byte;
  UINT8                 ChBitMask = 0;
  UINT8                 Iterator;
  //MRC_POWER_SYS_CONFIG  SysConfig;
  //DimmRttWr             DimmWrOdt;
  INT8                  LocalOffset;
  //UINT16                BufferStageDelayPS;
  UINT8                 ScaleRdPwr;
  UINT8                 ScaleWrPwr;
  UINT32                FivrPInValueStart;
  UINT32                FivrPInCountStart;
  UINT32                FivrPInValueEnd;
  UINT32                FivrPInCountEnd;
  UINT32                MaxPOutValue;
  UINT32                MaxPOutUnits;
  //UINT16                DimmRon;
  //BOOLEAN               Ddr4;
  //UINT32                VccIO;
  //UINT32                Vdd;
  //UINT8                 BiasConfig;
  INT64                 GetSetVal = 0x0;
  //UINT8                 NumStages;
  //UINT8                 SlewRateCompCells;
  //DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;

  //Inputs                   = &MrcData->Inputs;
  Outputs                  = &MrcData->Outputs;
  //IntOutputs               = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  //ChannelOut               = &Outputs->Controller[0].Channel[Channel];
  //Ddr4                     = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  //VccIO                    = Inputs->VccIomV;
  //Vdd                      = Outputs->VddVoltage[Inputs->MemoryProfile];

  Power->RdPower = 0;
  Power->WrPower = 0;
  Power->TotalPwr = 0;

  // For PanicVttDnLp, don't calculate power; instead, find the number of [panic high + (panic high - panic lo)] panic events that occur (and minimize it while making sure [panic high - panic lo > 0])
  Idx = MrcSearchList (OptPanicVttDnLp, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  if (Idx != 0) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
        continue;
      }
      ChBitMask |= 0x1 << Channel;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }

        GetSetVal = 0;
        // TGL_POWER_TRAINING DDRVtt_CR_DDRCrVttGenStatus.SelCount
        // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, VttGenStatusSelCount, WriteCached, &GetSetVal);
      }
    }

    // Run CPGC
    RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
        continue;
      }
      ChBitMask |= 0x1 << Channel;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }

        // TGL_POWER_TRAINING DDRVtt_CR_DDRCrVttGenStatus.Count
        // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, VttGenStatusCount, ReadUncached, &GetSetVal);
        Power->RdPower += (UINT16)(GetSetVal & 0x7FFF); // Use the absolute value of the 16 bit signed error count, so cut off the MSB sign bit

        GetSetVal = 5;
        // TGL_POWER_TRAINING DDRVtt_CR_DDRCrVttGenStatus.SelCount
        // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, VttGenStatusSelCount, WriteCached, &GetSetVal);
      }
    }

    // Run CPGC
    RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
        continue;
      }
      ChBitMask |= 0x1 << Channel;
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
          continue;
        }

        // TGL_POWER_TRAINING DDRVtt_CR_DDRCrVttGenStatus.Count
        // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, VttGenStatusCount, ReadUncached, &GetSetVal);
        if (GetSetVal < 0) {
          GetSetVal = 0x7FFF; // Set panic count to maximum if SelCount=5 gives a negative result, so that this PanicVttDnLp value is not chosen.
        }
        Power->RdPower += (UINT16)GetSetVal;
      }
    }

    Power->WrPower = 0;
    Power->TotalPwr = 0;
    return mrcSuccess;
  }

  //DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
  ScaleRdPwr = 60;
  ScaleWrPwr = 40;

  /*
  // Tx
  TxParamVector[MbLengthTx] = 1000; // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[MbLengthTx] = RANGE (TxParamVector[MbLengthTx], 800, 2800);

  TxParamVector[SoDimmLenTx] = 200;  // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[SoDimmLenTx] = RANGE (TxParamVector[SoDimmLenTx], 50, 900);

  Idx = MrcSearchList (OptWrDS, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVrefUp, ReadFromCache, &GetSetVal);
  TxParamVector[CpuRon]  = CalcCpuImpedance (
                          MrcData,
                          cCONTROLLER0, // @todo - 2xMC
                          Channel,
                          Rank,
                          Byte,
                          OptWrDS,
                          Override,
                          LocalOffset,
                          Override,
                          (UINT8) GetSetVal,
                          CurrentComp
                          );
  // keep within the simulation range
  TxParamVector[CpuRon] = RANGE (TxParamVector[CpuRon], 35, 65);

  Idx = MrcSearchList (OptSComp, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  if (Override) {
    LocalOffset = Offset[Idx - 1];
  } else {
    LocalOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset, DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID, 8);
  }

  // read global cell delay for Tx
  MrcGetSetDdrIoGroupController0 (MrcData, TxSlewRate, ReadFromCache, &GetSetVal);
  SlewRateCompCells = (UINT8) GetSetVal;
  MrcGetSetDdrIoGroupController0 (MrcData, DqScompPC, ReadFromCache, &GetSetVal);
  NumStages = (GetSetVal == ScompTypePhase) ? 2 * (SlewRateCompCells + 1) : (SlewRateCompCells + 1);

  BufferStageDelayPS = DIVIDEROUND (Outputs->Qclkps, NumStages);
  TxParamVector[CpuCellDelay] = BufferStageDelayPS * ((UINT16) MrcPercentPower ((LocalOffset < 0) ? 95 : 105, ABS (LocalOffset))) / 100; // simple linear T-line
  // keep within the simulation range
  TxParamVector[CpuCellDelay] = RANGE (TxParamVector[CpuCellDelay], 10, 100);

  Idx = MrcSearchList (OptTxEq, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVrefUp, ReadFromCache, &GetSetVal);
  TxParamVector[CpuTxEq]  = CalcCpuImpedance (
                            MrcData,
                            cCONTROLLER0, // @todo - 2xMC
                            Channel,
                            Rank,
                            Byte,
                            OptTxEq,
                            Override,
                            LocalOffset,
                            Override,
                            (UINT8) GetSetVal,
                            CurrentComp
                            );
  // x2 to match simulation input for the RSM calc. and clip to range [100 - 700]
  TxParamVector[CpuTxEq] *= 2;
  TxParamVector[CpuTxEq] = RANGE (TxParamVector[CpuTxEq], 100, 700);

  if (Ddr4) {
    Idx = MrcSearchList (DimmWrOdtNT, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
    // @todo - 2xMC
    TxParamVector[DimmWrOdtNT]  = MrcGetEffDimmWriteOdt (MrcData, cCONTROLLER0, Channel, Rank, 1, FALSE);
    // keep within the simulation range
    TxParamVector[DimmWrOdtNT] = RANGE (TxParamVector[DimmWrOdtNT], 100, 500);
  } else {
    // in LPDDR4 we use entry [3] for Mb_len
    TxParamVector[DimmWrOdtNT] = TxParamVector[MbLengthTx];
  }

  Idx = MrcSearchList (OptDimmOdtWr, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  // @todo - 2xMC
  DimmWrOdt = CalcDimmImpedance (MrcData, cCONTROLLER0, Channel, Rank, OptDimmOdtWr, Override, LocalOffset, FALSE);
  if (DimmWrOdt == 0xFFFF) {// DDR4 HiZ
    DimmWrOdt = 0;
  } else if (DimmWrOdt == 0) {// when dynamic odt off the nom is picked
    // @todo - 2xMC
    DimmWrOdt = CalcDimmImpedance (MrcData, cCONTROLLER0,  Channel, Rank, OptDimmOdtNom, Override, LocalOffset, FALSE);
  }


  // Rx
  RxParamVector[MbLengthRx]   = 1000; //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[MbLengthRx]   = RANGE (RxParamVector[MbLengthRx], 800, 2800);
  RxParamVector[SoDimmLenRx]  = 200;  //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[SoDimmLenRx]  = RANGE (RxParamVector[SoDimmLenRx], 50, 900);

  Idx = MrcSearchList (OptRdOdt, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVrefUp, ReadFromCache, &GetSetVal);
  RxParamVector[CpuOdt]  = CalcCpuImpedance (
                            MrcData,
                            cCONTROLLER0, // @todo - 2xMC
                            Channel,
                            Rank,
                            Byte,
                            OptRdOdt,
                            Override,
                            LocalOffset,
                            Override,
                            (UINT8) GetSetVal,
                            CurrentComp
                            );
  // keep within the simulation range
  RxParamVector[CpuOdt] = RANGE (RxParamVector[CpuOdt], 60, 500);

  Idx = MrcSearchList (DimmRdOdtNT, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  // @todo - 2xMC
  RxParamVector[DimmRdOdtNT]  = MrcGetEffDimmWriteOdt (MrcData, cCONTROLLER0, Channel, Rank, 1, FALSE);
  // keep within the simulation range
  RxParamVector[DimmRdOdtNT] = RANGE (RxParamVector[DimmRdOdtNT], 60, 500);

  Idx = MrcSearchList (OptDimmRon, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  // @todo - 2xMC
  DimmRon = CalcDimmImpedance (MrcData, cCONTROLLER0, Channel, Rank, OptDimmRon, Override, LocalOffset, FALSE);


  Idx = MrcSearchList (OptRxBias, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  // RX BIAS calculations
  if (VccIO < 900) {
    // LPDDR3 UlX - 0.85v
    BiasConfig = 0;
    RxDefault  = 8;
  } else {
    // LPDDR3 Ult - 0.95v
    BiasConfig = 1;
    RxDefault  = 8;
  }

  CPURXPower = Vdd * RxPowerConstuW[BiasConfig][0] / 100 + VccIO * RxPowerConstuW[BiasConfig][1] / 100;

  if (Override) {
    LocalOffset = (UINT8) Offset[Idx - 1];
    LocalOffset = RANGE (LocalOffset, 0, 15);
  } else {
    // TGL_POWER_TRAINING - This register no longer seems to exist in TGL. When we redo power measurement, may need to look at this.
    // MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasCtl, ReadFromCache, &GetSetVal);
    LocalOffset = (UINT8) GetSetVal;
  }

  CPURXPower  = (RxPowerScaleSKL[(UINT8) LocalOffset] * CPURXPower) / RxPowerScaleSKL[RxDefault];
  CPURXPower /= 1000; // div by 1000 to get mW (result is per byte)
  Power->RdPower += (UINT16) CPURXPower * Scale;

  // Set the RSM configuration for Tx
  SysConfig.Data = 0;
  SysConfig.Bits.DdrType = Outputs->DdrType;
  SysConfig.Bits.Frequency = Outputs->Frequency;
  SysConfig.Bits.RttWr = DimmWrOdt;
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DimmWrOdt: %d ch %d  rank %d\n", DimmWrOdt, Channel, Rank);
  GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysTxPowerFormula),  RSMPowerCalcTableTx, sizeof (RSMPowerCalcTableTx) / sizeof (MRC_RSM_POWER_FORMULA));
  // calc Tx Power
  Power->WrPower += (UINT16) CalcPowerRSM (
                            MrcData,
                            IntOutputs->SysTxPowerFormula,
                            TxParamVector,
                            Ddr4 ? 6 : 4,
                            Scale
                            );

  // Set the RSM configuration for Rx
  SysConfig.Data = 0;
  SysConfig.Bits.DdrType = MRC_DDR_TYPE_DDR4; // we currently have only DDR4 equ. Outputs->DdrType;
  SysConfig.Bits.Frequency = f1333; // we currently have only 1333 equ. Outputs->Frequency;
  SysConfig.Bits.RttWr = DimmRon; //  we currently have only 34 and 48 values
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DimmWrOdt: %d ch %d  rank %d\n", DimmWrOdt, Channel, Rank);
  GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysRxPowerFormula),  RSMPowerCalcTableRx, sizeof (RSMPowerCalcTableRx) / sizeof (MRC_RSM_POWER_FORMULA));

  // calc Rx Power
  Power->RdPower += (UINT16) CalcPowerRSM (
                            MrcData,
                            IntOutputs->SysRxPowerFormula,
                            RxParamVector,
                            4,
                            Scale
                            );
  */

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    // no need to run on channel with no selected ranks
    if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
      continue;
    }
    ChBitMask |= 0x1 << Channel;
  }

  if (ChBitMask == 0x0) {
    return mrcSuccess; // Nothing to do here
  }

  do {
    // TGL_POWER_TRAINING - Read initial FIVR input power accumulator from P_IN_ACCUMULATOR and sample count from P_IN_NUM_SAMPLES_SNAPSHOT
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInValue, ReadUncached, &GetSetVal);
    FivrPInValueStart = (UINT16)GetSetVal;
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInCount, ReadUncached, &GetSetVal);
    FivrPInCountStart = (UINT16)GetSetVal;

    SetupIOTestBasicVA (MrcData, ChBitMask, OPT_PARAM_1D_LC, NSOE, 0x4, 0, 8, PatWrRd, 0, 0); // Read-only test all channels. TGL_POWER_TRAINING - LC may need to be optimized
    RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0); // This is a standard point test

    // TGL_POWER_TRAINING - Read final FIVR input power accumulator from P_IN_ACCUMULATOR and sample count from P_IN_NUM_SAMPLES_SNAPSHOT
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInValue, ReadUncached, &GetSetVal);
    FivrPInValueEnd = (UINT16)GetSetVal;
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInCount, ReadUncached, &GetSetVal);
    FivrPInCountEnd = (UINT16)GetSetVal;
  } while (FivrPInCountEnd < FivrPInCountStart); // If this is not true, then we overflowed

  FivrPInValueEnd = FivrPInValueEnd - FivrPInValueStart;
  FivrPInCountEnd = FivrPInCountEnd - FivrPInCountStart;
  // TGL_POWER_TRAINING - Result must be in mW, so we have to adjust for this by finding out what the units are in FIVR. Units are (VR_MAX.MAX_P_OUT * 2^VR_MAX.P_OUT_EXP / 255) mW
  // MrcGetSetDdrIoGroupController0 (MrcData, MaxPOutValue, ReadUncached, &GetSetVal);
  MaxPOutValue = (UINT32)GetSetVal;
  // MrcGetSetDdrIoGroupController0 (MrcData, MaxPOutExp, ReadUncached, &GetSetVal);
  MaxPOutUnits = 1;
  for (Iterator = 0; Iterator < GetSetVal; Iterator++) {
    MaxPOutUnits *= 2;
  }
  MaxPOutValue *= MaxPOutUnits;
//#ifdef LOCAL_STUB_FLAG
  FivrPInValueEnd = 12750;
  MaxPOutValue = 1000;
  FivrPInCountEnd = 100;
//#endif
  Power->RdPower = (UINT16)((FivrPInValueEnd * MaxPOutValue) / (FivrPInCountEnd * 255));

  do {
    // TGL_POWER_TRAINING - Read initial FIVR input power accumulator from P_IN_ACCUMULATOR and sample count from P_IN_NUM_SAMPLES_SNAPSHOT
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInValue, ReadUncached, &GetSetVal);
    FivrPInValueStart = (UINT16)GetSetVal;
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInCount, ReadUncached, &GetSetVal);
    FivrPInCountStart = (UINT16)GetSetVal;

    SetupIOTestBasicVA (MrcData, ChBitMask, OPT_PARAM_1D_LC, NSOE, 0x2, 0, 8, PatWrRd, 0, 0); // Write-only test all channels. TGL_POWER_TRAINING - LC may need to be optimized
    RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0); // This is a standard point test

    // TGL_POWER_TRAINING - Read final FIVR input power accumulator from P_IN_ACCUMULATOR and sample count from P_IN_NUM_SAMPLES_SNAPSHOT
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInValue, ReadUncached, &GetSetVal);
    FivrPInValueEnd = (UINT16)GetSetVal;
    // MrcGetSetDdrIoGroupController0 (MrcData, FivrPInCount, ReadUncached, &GetSetVal);
    FivrPInCountEnd = (UINT16)GetSetVal;
  } while (FivrPInCountEnd < FivrPInCountStart); // If this is not true, then we overflowed

  FivrPInValueEnd = FivrPInValueEnd - FivrPInValueStart;
  FivrPInCountEnd = FivrPInCountEnd - FivrPInCountStart;
//#ifdef LOCAL_STUB_FLAG
  FivrPInValueEnd = 12750;
  MaxPOutValue = 1000;
  FivrPInCountEnd = 100;
//#endif
  Power->WrPower = (UINT16)((FivrPInValueEnd * MaxPOutValue) / (FivrPInCountEnd * 255));

  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power->RdPower : %d Power->WrPower: %d ParamVector: %d ParamVector: %d ParamVector: %d ParamVector: %d \n", Power->RdPower, Power->WrPower, ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3]);
  Power->TotalPwr = ((Power->RdPower * ScaleRdPwr ) + (Power->WrPower * ScaleWrPwr )) / 100; // [mW] when Scale=1
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power->TotalPwr %d\n", Power->TotalPwr);
  return mrcSuccess;
}

#if EYE_MARGIN_SUPPORT
/**
  This function prints out the Margin eye diagram for ParamT/ParamV.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Channel to margin.
  @param[in] Ranks   - Bit mask of Ranks to margin.
  @param[in] ParamT  - Time parameter to margin.
  @param[in] ParamV  - Voltage parameter to margin.
  @param[in] CmdIteration - Whether doing CLK/CMD/CTL (only used with ParamT == CmdT and ParamV == CmdV)
  @param[in] CmdGroup     - Determines which CmdGrp to use (0 through 4, only used with CmdIteration == MrcIterationCmd)
  @param[in] Start   - Starting point for margining.
  @param[in] Stop    - Stopping point for margining.
  @param[in] Repeats - Number of times to repeat the test to average out any noise.
  @param[in] NoPrint - Switch to skip printing.

  @retval Nothing
**/
#define MRC_EM_MAX_H  (192)
#define MRC_EM_MAX_W  (128)
void
EyeMargin (
  IN MrcParameters *const MrcData,
  IN UINT8                Ranks,
  IN UINT8                ParamT,
  IN UINT8                ParamV,
  IN UINT8                CmdIteration,
  IN UINT8                CmdGroup,
  IN INT8                 Start,
  IN INT8                 Stop,
  IN UINT16               SearchLimits,
  IN UINT8                LoopCount,
  IN UINT8                Repeats
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcIntOutput      *IntOutputs;
  MrcIntCmdTimingOut *IntCmdTiming;
  MrcStatus         Status;
  UINT32            (*MarginByte)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32            BERStats[4];
  UINT16            SaveMargin[MRC_EM_MAX_W][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  BOOLEAN           Eye[MAX_CHANNEL][MRC_EM_MAX_W][MRC_EM_MAX_H];
  BOOLEAN           Lines[MAX_CHANNEL][MRC_EM_MAX_H];
  UINT32            Channel;
  UINT8             i,j;
  UINT16            MinEdge;
  UINT8             ResultTypeV = 0;
  UINT8             ChBitMask;
  UINT8             Byte;
  UINT8             Rank;
  UINT8             Edge;
  UINT8             FirstRank;
  UINT8             NumBytes;
  UINT8             BMap[9];  // Need by GetBERMarginByte
  UINT8             MaxMarginV;
  UINT8             localR[MAX_CHANNEL];
  UINT8             Rep;
  INT8              Index;
  UINT8             IndexOff;
  INT8              Off;
  UINT8             OffStep;
  UINT8             byteMax[MAX_CHANNEL];
  UINT8             sign;
  UINT8             SafeOff[MAX_CHANNEL]={0,0};
  UINT8             CurrValue;
  INT64             GetSetVal;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           IsMrVref;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MarginByte    = &Outputs->MarginResult;
  ControllerOut = &Outputs->Controller[0];
  IndexOff      = 0;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);

  MrcCall->MrcSetMem ((UINT8 *) localR, sizeof (localR), 0);
  MrcCall->MrcSetMem ((UINT8 *) Eye, sizeof (Eye), 0);
  MrcCall->MrcSetMem ((UINT8 *) Lines, sizeof (Lines), 0);
  MrcCall->MrcSetMem ((UINT8 *) SaveMargin, sizeof (SaveMargin), 0);
  MrcCall->MrcSetMemDword (BERStats, sizeof (BERStats) / sizeof (UINT32), 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }
  ResultTypeV = GetMarginResultType (ParamV);
  IsMrVref = (ParamV == WrV) || (Lpddr4 && (ParamV == CmdV));

  if ((ParamT == CmdT) | (ParamT == CmdV)) {
    // @todo Update with McChBitMask
    SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
  } else {
    // @todo Update with McChBitMask
    SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, LoopCount, 0, 0, 0, 8, PatWrRd, 0, 0);  //set test to all channels
  }

  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (MrcData, 0, Channel)) {
      ChannelOut      = &ControllerOut->Channel[Channel];
      localR[Channel] = ChannelOut->ValidRankBitMask & Ranks;
      ChBitMask |= SelectReutRanks (MrcData, (UINT8) Channel, localR[Channel], FALSE, 0);
    } // Channel Exists
  } // Channel
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EM: ChBitMask 0x%X, Ranks 0x%X, LocalR[C0] 0x%X, LocalR[C1] 0x%X\n", ChBitMask, Ranks, localR[0], localR[1]);
  if (ChBitMask == 0) {
    return;
  }

  // Find the first selected rank
  FirstRank = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((1 << Rank) & localR[Channel]) {
        FirstRank = Rank;  // could be in any channel
        break;
      }
    } // Rank
  } // Channel
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EM: FirstRank 0x%X\n", FirstRank);

  // Store margin results for
  NumBytes = (UINT8) Outputs->SdramCount;
  //if (ParamV == CmdV) {
  //  NumBytes = 1;
  //}

  // Ensure all bit are checking for errors.
  MrcSetDataAndEccErrMsk (MrcData, 0xFFFFFFFFFFFFFFFFULL, 0xFF);

  // Find MaxMargin for this channel
  MaxMarginV = GetVrefOffsetLimits (MrcData, ParamV);

  //if (MAX_POSSIBLE_TIME < Stop) {
  //  Stop = MAX_POSSIBLE_TIME;
  //}
  //if (-MAX_POSSIBLE_TIME > Start) {
  //  Start = -MAX_POSSIBLE_TIME;
  //}

  if (ParamT == RdT) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, 0, Channel)) {
        continue;
      }
      for (sign = 0; sign < 2; sign++) {
        byteMax[Channel] = (sign) ? ABS(Stop) : ABS(Start);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          byteMax[Channel] = MrcCalcMaxRxMargin (MrcData, ParamT, /**Controller**/ CONTROLLER_0, (UINT8) Channel, FirstRank, Byte, 0, byteMax[Channel]);
        }
      }
    }
    Start = - byteMax[0];
    Stop  = byteMax[1];
  }

  IndexOff = MRC_EM_MAX_W / 2 + Start;
  // No need to search too far
  if (MaxMarginV > SearchLimits) {
    MaxMarginV = (UINT8) (SearchLimits);
  }

  OffStep = 1;

  // Loop through all Test Params and Measure Margin
  for (Off = Start; Off < Stop + 1; Off += OffStep) {
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Timing: %d\n", Off);
    Index = Off - Start;

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, 0, Channel)) {
        continue;
      }
      if (ParamT == CmdT) {
        IntCmdTiming  = &IntOutputs->Controller[0].CmdTiming[Channel];
        if (CmdIteration == MrcIterationClock) {
          // the 3 is to select two SubChannels
          //@todo - 2MC
          ShiftPIforCmdTraining (MrcData, CONTROLLER_0, (UINT8) Channel, CmdIteration, localR[Channel], 3, Off, 0);
        }
        if (CmdIteration == MrcIterationCmd) {
          if (CmdGroup >= MAX_COMMAND_GROUPS) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: CmdGroup out of bounds! %d", CmdGroup);
            return;
          }
          //@todo - 2MC
          ShiftPIforCmdTraining (MrcData, CONTROLLER_0, (UINT8) Channel, CmdIteration, localR[Channel], 1 << CmdGroup, (INT32) IntCmdTiming->CmdPiCode[CmdGroup] + Off, 0);
        }
        if (CmdIteration == MrcIterationCtl) {
          CurrValue = 0;
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (localR[Channel] & (1 << Rank)) {
              MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Rank, CtlGrpPi, ReadFromCache, &GetSetVal);
              CurrValue = (UINT8) IntCmdTiming->CtlPiCode[Rank];
              break;
            }
          }
          //@todo - 2MC
          ShiftPIforCmdTraining (MrcData, CONTROLLER_0, (UINT8) Channel, CmdIteration, localR[Channel], localR[Channel], CurrValue + Off, 0);
        }
        MrcResetSequence (MrcData);
      } else {
        for (Byte = 0; Byte < NumBytes; Byte++) {
          Status = ChangeMargin (MrcData, ParamT, Off, 0, 0, /**Controller**/ 0, (UINT8) Channel, FirstRank, Byte, 0, 1, 0);
        }
      }
      // Assign to last pass margin results by reference
      // get lowest margin from all ch/rankS/byte save in FirstRank
      //if (ParamT != CmdT) {
      //  Status = GetMarginByte (
      //            MrcData,
      //            Outputs->MarginResult,
      //            ParamV,
      //            FirstRank,
      //            localR[Channel]
      //            );
      //}
    } // Channel

    for (Rep = 0; Rep < Repeats; Rep++) {
      // Run Margin Test - margin_1d with chosen param
      Status = MrcGetBERMarginByte (
        MrcData,
        Outputs->MarginResult,
        ChBitMask,
        (IsMrVref) ? Ranks : FirstRank,
        (IsMrVref) ? Ranks : FirstRank,
        ParamV,
        0, // Mode
        BMap,
        0,
        MaxMarginV,
        0,
        BERStats
        );
      //MrcDisplayMarginResultArray (MrcData, ResultTypeV);
      // Record Results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (MrcData, 0, Channel)) {
          continue;
        }
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          for (Byte = 0; Byte < NumBytes; Byte++) {
            if ((Index > MRC_EM_MAX_W) || (Index < 0)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: SaveMargin array out of bounds! %d", Index);
              return;
            }

            if (Rep == 0) {
              SaveMargin[Index][Channel][Byte][Edge] = 0;
            }
            SaveMargin[Index][Channel][Byte][Edge] += (UINT16) (*MarginByte)[ResultTypeV][FirstRank][Channel][Byte][Edge];
          } // Byte
        } // Edge
      } // Channel
    } // Repeats

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, 0, Channel)) {
        continue;
      }
      for (Edge = 0; Edge < MAX_EDGES; Edge++) {
        MinEdge = 0xFFFF;
        for (Byte = 0; Byte < NumBytes; Byte++) {
          if ((Index > (MRC_EM_MAX_W - 1)) || (Index < 0)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: SaveMargin array out of bounds! %d", Index);
            return;
          }

          SaveMargin[Index][Channel][Byte][Edge] /= Repeats;
          if (MinEdge > SaveMargin[Index][Channel][Byte][Edge]) {
            MinEdge = SaveMargin[Index][Channel][Byte][Edge];
          }
        } // Byte

        if ((Index > (MRC_EM_MAX_W - 1)) ||
            (Index < 0) ||
            ((MRC_EM_MAX_H / 2 - (MinEdge - 1) / 10) > (MRC_EM_MAX_H - 1)) ||
            ((MRC_EM_MAX_H / 2 - (MinEdge - 1) / 10) < 0) ||
            ((MRC_EM_MAX_H / 2 + (MinEdge - 1) / 10) > (MRC_EM_MAX_H - 1)) ||
            ((MRC_EM_MAX_H / 2 + (MinEdge - 1) / 10) < 0)
            ) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: Eye or Lines array out of bounds!\n");
          return;
        }

        if (Edge) {
          Eye[Channel][Index + IndexOff][MRC_EM_MAX_H / 2 - (MinEdge) / 10]  = 1;
          Lines[Channel][MRC_EM_MAX_H / 2 - (MinEdge) / 10] = 1;
        } else {
          Eye[Channel][Index + IndexOff][MRC_EM_MAX_H / 2 + (MinEdge) / 10]  = 1;
          Lines[Channel][MRC_EM_MAX_H / 2 + (MinEdge) / 10] = 1;
        }
      } // Edge
    } // Channel
  } // Offset

  // Print the box
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (MrcData, 0, Channel)) {
      continue;
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Plot Eye across ParamT = %s ParamV = %s CmdIter = %s CmdGrp = 0x%x settings:(Start=%d,Stop=%d) LC = %d  Channel = %d Ranks = 0x%x\n",
      gMarginTypesStr[ParamT],
      gMarginTypesStr[ParamV],
      CmdIterTypesString[CmdIteration],
      CmdGroup,
      Start,
      Stop,
      LoopCount,
      Channel,
      localR[Channel]
      );
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t---------------------------------------------------------- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t66666555555555544444444443333333333222222222211111111110000000000000000000111111111122222222223333333333444444444455555555556666\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Vref\t43210987654321098765432109876543210987654321098765432109876543210123456789012345678901234567890123456789012345678901234567890123\n");
    for (i = 0; i < MRC_EM_MAX_H; i++) {
      if (Lines[Channel][i]) {
        // print only fail lines
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%3d:\t", MRC_EM_MAX_H / 2 - i); // per ch
        for (j = 0; j < MRC_EM_MAX_W; j++) {
          if (Eye[Channel][j][i]) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", "#"); // per ch
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", ((j == (MRC_EM_MAX_W) / 2) || (i == (MRC_EM_MAX_H) / 2)) ? "+" : " "); // per ch
          }
        } // j
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");//per ch
      }
    } // i
  } // Channel
  if (ParamT != CmdT) {
    Status = ChangeMargin (MrcData, ParamT, 0, 0, 1, /**Controller**/ 0, 0, 0, 0, 0, 1, 0);
  } else {
    //restore settings
    ShiftCh2Ch (MrcData, 0xff, SafeOff, 1, 0, 0, 0);
  }
  Status = MrcResetSequence (MrcData);
}
#endif // EYE_MARGIN_SUPPORT

/**
  This function fill the input array (e.g array[ch][rank]) with the power calculation
  per rank/ch for current sys. setting.

  @param[in]     MrcData   - MRC data struct;
  @param[in,out] PwrChRank - Array to fill;

  @retval Nothing
**/
void
CalcSysPower (
  IN     MrcParameters *const MrcData,
  IN OUT MrcPower             PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL]
  )
{
  MrcOutput                   *Outputs;
  MrcChannelOut               *ChannelOut;
  MrcOdtPowerSaving           *OdtPowerSaving;
  MrcPower                    PwrRank[MAX_RANK_IN_CHANNEL];
  UINT8                       Rank;
  //UINT8                       Byte;
  UINT8                       Channel;
  UINT8                       TotalRankCount;
  UINT8                       TotalChannelCount = 0;
  UINT32                      PwrAvgRd;
  UINT32                      PwrAvgWr;
  UINT32                      PwrAvgTotal;

  Outputs         = &MrcData->Outputs;
  OdtPowerSaving  = &Outputs->OdtPowerSavingData;
  TotalRankCount  = 0;
  PwrAvgRd        = 0;
  PwrAvgWr        = 0;
  PwrAvgTotal     = 0;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    // CalcOptPower will sum the channels and bytes to get overall power, and return 0 if no valid ranks are present matching the rank given
    CalcOptPower (MrcData, &PwrRank[Rank], Rank, NULL, NULL, 0, 0, 10);

    PwrAvgRd += (PwrRank[Rank].RdPower);
    PwrAvgWr += (PwrRank[Rank].WrPower);
    PwrAvgTotal += (PwrRank[Rank].TotalPwr);

    TotalChannelCount = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
        continue;
      }

      TotalChannelCount++;

      if (ChannelOut->ValidRankBitMask & (0x1 << Rank)) {
        TotalRankCount++;
      }
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & MrcData->Outputs.ValidChBitMask)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      // no need to run on channel with no selected ranks
      if (!(ChannelOut->ValidRankBitMask & (0x1 << Rank))) {
        continue;
      }
      PwrChRank[Channel][Rank].RdPower = PwrRank[Rank].RdPower / TotalChannelCount;
      PwrChRank[Channel][Rank].WrPower = PwrRank[Rank].WrPower / TotalChannelCount;
      PwrChRank[Channel][Rank].TotalPwr = PwrRank[Rank].TotalPwr / TotalChannelCount;
    }
  }

  if (TotalRankCount == 0) {
    TotalRankCount = 1;  // Prevent divide by 0
  }

  // Per rank in the system (per rank per channel, since we divide by total ranks in the system)
  PwrAvgRd    /= (TotalRankCount);
  PwrAvgWr    /= (TotalRankCount);
  PwrAvgTotal /= (TotalRankCount);
  // update Mrc struct with Base line numbers
  if (OdtPowerSaving->BaseFlag == FALSE) {
    OdtPowerSaving->BaseSavingRd  = (UINT16) PwrAvgRd;
    OdtPowerSaving->BaseSavingWr  = (UINT16) PwrAvgWr;
    OdtPowerSaving->BaseSavingCmd = 0; // currently no power train for CMD
  } else {
    OdtPowerSaving->MrcSavingRd  = (UINT16) PwrAvgRd;
    OdtPowerSaving->MrcSavingWr  = (UINT16) PwrAvgWr;
    OdtPowerSaving->MrcSavingCmd = 0; // currently no power train for CMD
  }

  return;
}

/**
  This function optimize the digital offsets by reducing the digital
  offset and apply the difference to the global one.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Param      - Parameter defining the desired digital compensation offset.
  @param[in] UpdateHost - Decides if MrcData is to be updated.

  @retval The new comp value.
**/
UINT32
OptimizeCompOffset (
  IN MrcParameters *const MrcData,
  IN const UINT8          Param,
  IN const UINT8          UpdateHost
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  UINT8             CurrCompVref;
  UINT8             NewCompVref;
  UINT8             CurrentComp;
  UINT8             CurrentCompDn;
  UINT8             NewComp;
  UINT8             NewCompDn;
  INT8              Sign;
  UINT8             Done;
  INT16             AvgOffset;
  UINT8             Offset;
  UINT8             OffsetDn;
  UINT8             StartDelta;
  UINT8             CurrDelta;
  UINT8             MinDelta;
  UINT8             Off;
  UINT8             DRAMs;
  UINT8             BestVrefOff;
  UINT8             MaxCompOffsetBits;
  UINT8             Byte;
  UINT8             Channel;
  UINT8             NumCh;
  UINT8             ReservedCodes;
  UINT8             MaxComp;
  UINT8             MaxCompVref;
  UINT8             MinCompVref;
  UINT8             SCompPC;
  UINT8             CurrSCompPC;
  INT8              CompCodes[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8              CompCodesDn[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8             RcompUp;
  UINT8             RcompDn;
  UINT8             SlewRateComp;
  UINT8             GlobalParam;
  INT64             GetSetVal;
  // INT16             Width;
  GSM_GT            Group1;
  GSM_GT            Group2;
  DATA_CR_DDRCRDATACONTROL5_STRUCT DdrCrDataControl5;
  DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;
  CH0CCC_CR_DDRCRCTLCACOMPOFFSET_STRUCT DdrCrCmdOffsetComp;

  Outputs                   = &MrcData->Outputs;
  Debug                     = &Outputs->Debug;

  DdrCrDataControl5.Data    = 0;
  DdrCrDataOffsetComp.Data  = 0;
  DdrCrCmdOffsetComp.Data   = 0;
  ReservedCodes             = 3;
  NewComp                   = 0;
  Offset                    = 0;
  MaxCompOffsetBits         = 0;
  MaxComp                   = 0;
  SCompPC                   = 0;
  CurrSCompPC               = 0;
  CurrentCompDn             = 0;
  NewCompDn                 = 0;
  OffsetDn                  = 0;
  RcompUp = RcompDn = SlewRateComp = 0;

  if (Param == OptWrDS) {
    Group1 = TxRonUp;
    Group2 = TxRonDn;
  } else if (Param == OptCmdDS) { // When training CCC DS, we assume CMD/CTL/CLK all have the same DS value (since they are trained together)
    Group1 = WrDSCodeUpCmd;
    Group2 = WrDSCodeDnCmd;
  } else if (Param == OptSComp) {
    Group1 = SCompCodeDq;
    Group2 = SCompCodeDq;
  } else if (Param == OptCCCSComp) { // When training CCC SComp, we assume CMD/CTL/CLK all have the same offset value (since they are trained together)
    Group1 = SCompCodeCmd;
    Group2 = SCompCodeCmd;
  } else if (Param == OptRxLoad) {
    // TGL_POWER_TRAINING - Add these variables
    Group1 = 0; // RloadDqsDn;
    Group2 = 0; // RloadDqsDn;
  }
  else {
    Group1 = CompRcompOdtUp;
    Group2 = CompRcompOdtDn;
  }

  MrcGetSetNoScope (MrcData, Group1, ReadUncached, &GetSetVal);
  if (Param != OptSComp && Param != OptCCCSComp && Param != OptRxLoad) {
    RcompUp   = (UINT8) GetSetVal;
    MrcGetSetNoScope (MrcData, Group2, ReadUncached, &GetSetVal);
    RcompDn   = (UINT8) GetSetVal;
  } else {
    SlewRateComp = (UINT8) GetSetVal;
  }

  switch (Param) {
    case OptWrDS:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      MrcGetSetNoScope (MrcData, DqDrvVrefUp, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      MaxCompVref         = 191;
      MinCompVref         = 0;
      GlobalParam         = WrDSUp;
      MaxCompOffsetBits   = 6; // Comp offset
      MaxComp             = 63; // Comp
      break;

    case OptCmdDS:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      MrcGetSetNoScope (MrcData, CmdDrvVrefUp, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8)GetSetVal;
      MaxCompVref         = 191;
      MinCompVref         = 0;
      GlobalParam         = WrDSCmdUp;
      MaxCompOffsetBits   = 4; // Comp offset
      MaxComp             = 63; // Comp
      break;

    case OptRdOdt:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      MrcGetSetNoScope (MrcData, DqOdtVrefUp, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      MaxCompVref         = 191;
      MinCompVref         = 0;
      GlobalParam         = RdOdtUp;
      MaxCompOffsetBits   = 5; // Comp offset
      MaxComp             = 63; // Comp
      break;

    case OptSComp:
      CurrentComp         = SlewRateComp;
      MrcGetSetNoScope (MrcData, DqScompPC, ReadFromCache, &GetSetVal);
      CurrSCompPC         = (UINT8) GetSetVal;
      MrcGetSetNoScope (MrcData, TxSlewRate, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      MaxCompVref         = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX;
      MinCompVref         = 4;
      GlobalParam         = SCompDq;
      MaxCompOffsetBits   = 5; // Comp offset
      MaxComp             = 31; // Comp
      break;

    case OptCCCSComp:
      CurrentComp       = SlewRateComp;
      MrcGetSetNoScope (MrcData, CmdScompPC, ReadFromCache, &GetSetVal);
      CurrSCompPC       = (UINT8)GetSetVal;
      MrcGetSetNoScope (MrcData, CmdSlewRate, ReadFromCache, &GetSetVal);
      CurrCompVref      = (UINT8)GetSetVal;
      MaxCompVref       = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CmdScompCells_MAX;
      MinCompVref       = 4;
      GlobalParam       = SCompCmd;
      MaxCompOffsetBits = 4; // Comp offset
      MaxComp           = 63; // Comp
      break;

    case OptRxLoad:
      CurrentComp = SlewRateComp;
      // TGL_Power_Training - DDRComp_CR_DdrCrVccDLLReplicaCtrl1.RloadVref
      //   MrcGetSetDdrIoGroupController0 (MrcData, RxLoadCompVref, ReadFromCache, &GetSetVal);
      CurrCompVref = (UINT8)GetSetVal;
      MaxCompVref = 191;
      MinCompVref = 0;
      GlobalParam = RxLoad;
      MaxCompOffsetBits = 5; // Comp offset
      MaxComp = 63; // Comp
      break;

    default:
      CurrentComp   = 0;
      CurrCompVref  = 0;
      MaxCompVref   = 0;
      MinCompVref   = 0;
      GlobalParam   = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid Param : %d", Param);
      break;
  }

  AvgOffset = 0;
  NumCh     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (MrcData, 0, Channel))) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DdrCrDataControl5.Data = 0; // TGL_POWER_TRAINING: Add ChannelOut->DdrCrDataControl5[Byte];
        DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
        DdrCrCmdOffsetComp.Data = ChannelOut->CmdCompOffset;
        if (Param == OptWrDS) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset;
        }

        if (OptCmdDS) {
            Offset = (UINT8) DdrCrCmdOffsetComp.Bits.CaRcompDrvUpOffset;
            OffsetDn = (UINT8) DdrCrCmdOffsetComp.Bits.CaRcompDrvDownOffset;
            break; // Only run for 1 byte
        }

        if (Param == OptRdOdt) {
          Offset  = (UINT8) DdrCrDataControl5.Bits.DqsOdtCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqOdtCompOffset;
        }

        if (Param == OptSComp) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset;
          OffsetDn = 0;
        }

        if (OptCCCSComp) {
          Offset = (UINT8) DdrCrCmdOffsetComp.Bits.CaScompOffset; // Technically OffsetDn, but if you have only one you can set it to the offset instead.
          OffsetDn = 0;
          break; // Only run for 1 byte
        }

        if (OptRxLoad) {
          Offset = (UINT8) DdrCrDataOffsetComp.Bits.RloadOffset; // Technically OffsetDn, but if you have only one you can set it to the offset instead.
          OffsetDn = 0;
        }

        AvgOffset += (INT8) MrcSE (Offset, MaxCompOffsetBits, 8);
        CompCodes[Channel][Byte] = CurrentComp + MrcSE (Offset, MaxCompOffsetBits, 8);
        CompCodesDn[Channel][Byte] = CurrentCompDn + MrcSE (OffsetDn, MaxCompOffsetBits, 8);
      }
    }
    NumCh++;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s CompUp:%d CompDn:%d CompVref:%d", TOptParamOffsetString[Param], CurrentComp, CurrentCompDn, (INT8) CurrCompVref);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (MrcData, 0, Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%dByte  ",Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d:% 3d/",Byte, (INT8) (CompCodes[Channel][Byte] - CurrentComp));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "% 3d\t", (INT8) (CompCodesDn[Channel][Byte] - CurrentCompDn));
      }
    }
  }
  Sign = (AvgOffset < 0) ? -1 : 1;
  // Calculate the average offset and round to the nearest integer.
  if (Param == OptCCCSComp || Param == OptCmdDS) { // Run once per channel
      DRAMs = 1;
  } else {
      DRAMs = (UINT8)Outputs->SdramCount;
  }
  AvgOffset = (AvgOffset + Sign * NumCh * DRAMs / 2) / (NumCh * DRAMs);

  if (AvgOffset == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
    return CurrentComp;
  }
  // Find the CompVref minimum of the delta between (CurrentComp + AvgOffset) to NewComp.
  // Take care of keeping 3 code reserved.
  // Exit if no vref range left.
  Done        = 0;
  Off         = 1;
  BestVrefOff = CurrCompVref;
  NewComp     = CurrentComp;
  SCompPC     = CurrSCompPC;
  StartDelta  = ABS ((INT8) AvgOffset);
  MinDelta    = StartDelta;
  if (Param == OptSComp || Param == OptCCCSComp || Param == OptRxLoad) { // If we decrease the offset value for these, it decreases the comp vref as they are only pulldown comps.
    Sign *= -1;
  }

  while (!Done) {
    NewCompVref = CurrCompVref + (Sign * Off);
    if ((MinCompVref > NewCompVref) || (NewCompVref > MaxCompVref)) {
      Done = 1;
    }
    if (Param == OptSComp || Param == OptCCCSComp) {
      if (NewCompVref > MaxCompVref) {
        SCompPC = 0;
      }
      NewCompVref = (SCompPC << SCOMP_PC_STORAGE_BIT_OFFSET) + NewCompVref;
    }
    NewComp   = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, NewCompVref, FALSE, 0);
    NewCompDn = GetCompCode(MrcData, Param, 1); // take care of up/dn
    // Reserve 3 comp codes
    if ((ReservedCodes > NewComp) || (NewComp > (MaxComp - ReservedCodes))) {
      Done = 1;
    }
    if ((ReservedCodes > NewCompDn) || (NewCompDn > (MaxComp - ReservedCodes))) {
      Done = 1;
    }

    if (!Done) {
      CurrDelta = ABS (CurrentComp + (INT8) AvgOffset - NewComp);
      if (CurrDelta <= StartDelta) {
        if (CurrDelta < MinDelta) {
          MinDelta    = CurrDelta;
          BestVrefOff = NewCompVref;
          if (MinDelta == 0) {
            Done = 1;
          }
        }
      } else {
        Done = 1;
      }
    }

    Off++;
  }
  // update new compVref setting
  if (BestVrefOff != CurrCompVref) {
    NewComp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, (INT8) BestVrefOff, FALSE, UpdateHost);
  } else {
    // Restore CompVref
    if (Param == OptSComp || Param == OptCCCSComp) {
      NewCompVref = (CurrSCompPC << SCOMP_PC_STORAGE_BIT_OFFSET) + CurrCompVref;
    }
    NewComp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, (INT8) CurrCompVref, FALSE, UpdateHost);
  }

  if (Param == OptWrDS || Param == OptCmdDS) {
    MrcGetSetDdrIoGroupController0 (MrcData, Group2, ReadUncached, &GetSetVal);
    NewCompDn = (UINT8) GetSetVal;
  } else if (Param == OptRdOdt) {
    MrcGetSetNoScope (MrcData, Group2, ReadUncached, &GetSetVal);
    NewCompDn  = (UINT8) GetSetVal;
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
    if ((MrcChannelExist (MrcData, 0, Channel))) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (Param == OptRdOdt) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdDqsOdt, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdDqOdt, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
        } else {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, Param, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          if (Param == OptWrDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          } else if (Param == OptCmdDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptCmdDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
            break;
          }
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s NewCompUp:%d NewCompDn:%d NewCompVref:%d", TOptParamOffsetString[Param], NewComp, NewCompDn, (INT8) BestVrefOff);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (MrcData, 0, Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%dByte  ",Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d:% 3d/", Byte, (INT8) (CompCodes[Channel][Byte] - NewComp));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "% 3d\t", (INT8) (CompCodesDn[Channel][Byte] - NewCompDn));
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
  return NewComp;
}

/**
  This step performs Comp Offset optimization on the param list defined in this function.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess
**/
MrcStatus
MrcOptimizeComp (
  IN MrcParameters *const MrcData
  )
{
  // TGL_POWER_TRAINING - Both OptCmdDS and OptRxLoad use comp vref registers that need to be the same level to minimize linearity error.
  //                      This is because RxLoad uses the CMD comp vref. This is a problem, because optimizing them both will set them to seperate comp vrefs,
  //                      which may cause a lot of linearity error with the RxLoad comp. As such, it's possible we shouldn't optimize either if the RxLoad comp offset is being trained.
  static UINT8 ParamList1[] = {OptWrDS, OptRdOdt, OptSComp, OptCCCSComp, OptCmdDS};
  static UINT8 ParamList2[] = {OptWrDS, OptRdOdt, OptSComp, OptCCCSComp, OptCmdDS, OptRxLoad };
  // static UINT8 ParamList3[] = {OptWrDS, OptRdOdt, OptSComp, OptCCCSComp};
  UINT8              Param;
  INT64              RxModeVal = 0;

  // TGL_POWER_TRAINING read DDRDATA_CR_DDRCrDataControl0_0_0_0_MCHBAR.RxMode if we end up training OptRxBias in matched path mode.
  // MrcGetSetDdrIoGroupChannelStrobe (MrcData, 0, 0, RxMode, ReadFromCache, &RxModeVal);
  if (RxModeVal != MrcRxModeMatchedN && RxModeVal != MrcRxModeMatchedP) {
    // TGL_POWER_TRAINING - Set to ParamList2 if you don't think the RxLoad comp linearity error will be a problem, else set to ParamList3
    for (Param = 0; Param < ARRAY_COUNT (ParamList2); Param++) {
      OptimizeCompOffset (MrcData, ParamList2[Param], 1);
    }
  } else {
    for (Param = 0; Param < ARRAY_COUNT (ParamList1); Param++) {
      OptimizeCompOffset (MrcData, ParamList1[Param], 1);
    }
  }
#ifdef LB_STUB_FLAG
  return mrcFail;
#endif

  return mrcSuccess;
}

/**
  This function calculates the percent of power saving from the power optimization steps and
  updates the proper registers in the PCU.  To get the correct base line for this calculation,
  this routing needs to run first time early in the training in order to update the MrcStruct
  with the base line.  After the power training steps, it will run again to get the actual
  percent of power saving.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess

**/
MrcStatus
MrcPowerSavingMeter (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  const MrcInput                          *Inputs;
  MrcOutput                               *Outputs;
  MrcPower                                PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  MrcOdtPowerSaving                       *OdtPowerSaving;
  UINT8                                   PercentRd = 0;
  UINT8                                   PercentWr = 0;
  UINT8                                   PercentCmd = 0;
  MRC_ODT_POWER_SAVING_PCU_STRUCT         CrMrcOdtPowerSavingPcu;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  OdtPowerSaving  = &Outputs->OdtPowerSavingData;
  MrcCall->MrcSetMem ((UINT8 *) PwrChRank, sizeof (PwrChRank), 0);

  CalcSysPower (MrcData, PwrChRank);

  if (OdtPowerSaving->BaseFlag) {
    // Calculate power saving and update PCU regs
    if (OdtPowerSaving->BaseSavingRd > OdtPowerSaving->MrcSavingRd) {
      PercentRd = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingRd - OdtPowerSaving->MrcSavingRd) * 256) / OdtPowerSaving->BaseSavingRd);
    } else {
      PercentRd = 0;
    }

    if (OdtPowerSaving->BaseSavingWr > OdtPowerSaving->MrcSavingWr) {
      PercentWr = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingWr - OdtPowerSaving->MrcSavingWr) * 256) / OdtPowerSaving->BaseSavingWr);
    } else {
      PercentWr = 0;
    }

    if (OdtPowerSaving->BaseSavingCmd > OdtPowerSaving->MrcSavingCmd) {
      PercentCmd = (UINT8) (((UINT32) (OdtPowerSaving->BaseSavingCmd - OdtPowerSaving->MrcSavingCmd) * 256) / OdtPowerSaving->BaseSavingCmd);
    } else {
      PercentCmd = 0;
    }

    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Rd   = PercentRd;
    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Wt   = PercentWr;
    CrMrcOdtPowerSavingPcu.Bits.MRC_Saving_Cmd  = PercentCmd;

    MrcWriteCR (MrcData, MRC_ODT_POWER_SAVING_PCU_REG, CrMrcOdtPowerSavingPcu.Data);
  } else {
    OdtPowerSaving->BaseFlag = TRUE;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "\tBaseLine\tMrcSaving\tSaving\nAvgRd\t%d\t\t%d\t\t%d%%\nAvgWr\t%d\t\t%d\t\t%d%%\n",
    OdtPowerSaving->BaseSavingRd/10,
    OdtPowerSaving->MrcSavingRd/10,
    ((UINT16) PercentRd) * 100 / 256,
    OdtPowerSaving->BaseSavingWr/10,
    OdtPowerSaving->MrcSavingWr/10,
    ((UINT16) PercentWr) * 100 / 256
    );

  MrcPrintDimmOdtValues (MrcData);  // Print DIMM ODT table

  return mrcSuccess;
}



/**
  This function assign the pointer to the relevant power Coefficient table to the MRC structure
  offset and apply the difference to the global one.

  @param[in] MrcData        - Include all MRC global data.
  @param[in] Formula        -
  @param[in] ParamVector[MaxTxPowerParam] - Parameter vector of Rx/TxPowerOptParam enum holding the actual value in ohms
  @param[in] VectoreSize    - This vector hold the input params to the RSM equations, it should match the equations order
  @param[in] Scale          - optional Scale to get more precision in integer math

  @retval Result in 10x [mW]
**/
INT32
CalcPowerRSM (
  IN MrcParameters *const       MrcData,
  const MRC_RSM_POWER_FORMULA   *Formula,
  UINT16                        ParamVector[],
  UINT8                         VectoreSize,
  UINT8                         Scale
  )
{
  INT32                           Result;
  const MRC_RSM_POWER_FORMULA     *RSMCoeff;
  const MRC_POWER_COEFF           *iCoeff;
  UINT8                           i;
  UINT8                           j;

  // b0+sum(BiXi)+sum(BiiXi^2)+sum(sum(BijXiXj)) ; i!=j
  RSMCoeff = Formula;
  Result = RSMCoeff->Intercept0;
  for (i=0; i < VectoreSize; i++) {
    iCoeff = &RSMCoeff->Coeff[i];
    Result += (ParamVector[i]) * iCoeff->FirstOrder;
    Result += (ParamVector[i] - iCoeff->Intercept) * (ParamVector[i] - iCoeff->Intercept) * iCoeff->SecondOrder;
    for (j = 0; (j < i);  j++) {
      Result += (ParamVector[i] - iCoeff->Intercept) * (ParamVector[j] - RSMCoeff->Coeff[j].Intercept) * iCoeff->Interactions[j];
    }
  }

  // coeff are mult by 1e6
  Result /= (1000000 / Scale);
  return Result;
}

#if 0
/**
  This function been use in stub MRC mode to export in CSV format the power calculation for validation purpuse
  offset and apply the difference to the global one.

  @param[in] MrcData        - Include all MRC global data.

  @retval None
**/
MrcStatus
PowerCalcverification (
  MrcParameters *MrcData
  )
{
  MrcDebug     *Debug;
  UINT16       ParamVector[6];
  //UINT16 ParamStart[] = {59, 35, 50, 100, 500, 200};
  //UINT16 ParamStop[] = {80, 56, 150, 500, 2500, 800};
  //UINT16 ParamStep[] = {10, 5, 10, 100, 200, 200};

  UINT16 ParamStart[] = {50,  30,  800,   100};
  UINT16 ParamStop[] =  {200, 1000, 1000, 200};
  UINT16 ParamStep[] =  {10,  100,  100,  20};

  MRC_POWER_SYS_CONFIG SysConfig;
  MrcIntOutput         *IntOutputs;

  IntOutputs  = (MrcIntOutput *) MrcData->IntOutputs.Internal;
  Debug       = &MrcData->Outputs.Debug;

  if(0) {
    SysConfig.Data = 0;
    SysConfig.Bits.DdrType = MRC_DDR_TYPE_DDR4; //Outputs->DdrType;
    SysConfig.Bits.Frequency = 1333; //Outputs->Frequency;
    SysConfig.Bits.RttWr = RttWr120;
    GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysTxPowerFormula), RSMPowerCalcTableTx, sizeof (RSMPowerCalcTableTx) / sizeof (MRC_RSM_POWER_FORMULA));

    // calc Tx Power
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "cpu_cell_delay, cpu_ron, cpu_txle, DimmOdtNom, mb_main_len, SoDimmLen, Power %d  %d \n", SysConfig.Bits.RttWr, SysConfig.Bits.Frequency);
    for (ParamVector[0] = ParamStart[0]; ParamVector[0] < ParamStop[0]; ParamVector[0]+=ParamStep[0]) {
      for (ParamVector[1] = ParamStart[1]; ParamVector[1] < ParamStop[1]; ParamVector[1]+=ParamStep[1]) {
        for (ParamVector[2] = ParamStart[2]; ParamVector[2] < ParamStop[2]; ParamVector[2]+=ParamStep[2]) {
          for (ParamVector[3] = ParamStart[3]; ParamVector[3] < ParamStop[3]; ParamVector[3]+=ParamStep[3]) {
            for (ParamVector[4] = ParamStart[4]; ParamVector[4] < ParamStop[4]; ParamVector[4]+=ParamStep[4]) {
              for (ParamVector[5] = ParamStart[5]; ParamVector[5] < ParamStop[5]; ParamVector[5]+=ParamStep[5]) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "%d, %d, %d, %d, %d, %d, %d\n", ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3], ParamVector[4], ParamVector[5], CalcPowerRSM (MrcData, IntOutputs->SysTxPowerFormula, ParamVector, 6, 1));
                //MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "%d, %d, %d, %d, %d\n", ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3], CalcPowerRSM (MrcData, &SysConfig, RsmMarginCalcTableTx, sizeof (RsmMarginCalcTableTx) / sizeof (MRC_RSM_POWER_FORMULA), ParamVector, 3, 1));
              }
            }
          }
        }
      }
    }
  }

  SysConfig.Data = 0;
  SysConfig.Bits.DdrType = MRC_DDR_TYPE_DDR4;//MrcIntputData->DdrType;
  SysConfig.Bits.Frequency = 1867;//MrcIntputData->Frequency;
  SysConfig.Bits.RttWr = 48;
  GetPowerTable (MrcData, &SysConfig, &(IntOutputs->SysRxPowerFormula), RSMPowerCalcTableRx, sizeof (RSMPowerCalcTableRx) / sizeof (MRC_RSM_POWER_FORMULA));

  // calc Rx Power
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "CpuOdt, Dram_Odt, Mb_mail_len, Sodimm_len, DimmRon %d  freq %d \n", SysConfig.Bits.RttWr, SysConfig.Bits.Frequency);
  for (ParamVector[0] = ParamStart[0]; ParamVector[0] < ParamStop[0]; ParamVector[0]+=ParamStep[0]) {
    for (ParamVector[1] = ParamStart[1]; ParamVector[1] < ParamStop[1]; ParamVector[1]+=ParamStep[1]) {
      for (ParamVector[2] = ParamStart[2]; ParamVector[2] < ParamStop[2]; ParamVector[2]+=ParamStep[2]) {
        for (ParamVector[3] = ParamStart[3]; ParamVector[3] < ParamStop[3]; ParamVector[3]+=ParamStep[3]) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "%d, %d, %d, %d, %d\n", ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3], CalcPowerRSM (MrcData, IntOutputs->SysRxPowerFormula, ParamVector, 4, 1));
              //MRC_DEBUG_MSG (Debug, MSG_LEVEL_CSV, "%d, %d, %d, %d, %d\n", ParamVector[0], ParamVector[1], ParamVector[2], ParamVector[3], CalcPowerRSM (MrcData, &SysConfig, RsmMarginCalcTableTx, sizeof (RsmMarginCalcTableTx) / sizeof (MRC_RSM_POWER_FORMULA), ParamVector, 3, 1));
        }
      }
    }
  }
  return mrcFail;
  //return mrcSuccess;
}

#endif


/**
  This function assign the pointer to the relevant power Coefficient table to the MRC structure
  offset and apply the difference to the global one.
  The search algorithm:
    - We match the DIMM technology,
    - Power.Frequency <= Config.Frequency,
    - Power.RttWr <= Config.RttWr.
    - This is assuming that we pre-arrange (low to high) the table to match this algorithm.

  This function implements the following config search algorithm:
    We match the DIMM technology
    Power.Frequency <= Config.Frequency
    Power.RttWr <= Config.RttWr
  This is assuming that we pre-arrange (low to high) the table to match this algo.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] SysPwrConfig     - Parameter defining the desired system configuration (frequency, ddr type, dimm termination).
  @param[in] SysPowerFormula  -
  @param[in] Table            - Pointer to the relevant power equations table
  @param[in] TableSize        -

  @retval None
**/
void
GetPowerTable (
  IN MrcParameters *const      MrcData,
  MRC_POWER_SYS_CONFIG         *SysPwrConfig,
  const MRC_RSM_POWER_FORMULA  **SysPowerFormula,
  const MRC_RSM_POWER_FORMULA  *Table,
  UINT32                       TableSize
  )
{
  UINT32          Index;

  const MRC_RSM_POWER_FORMULA *ClosestConfig;

  // init Mrc struct if not populated yet
  if ((*SysPowerFormula) == NULL) {
    (*SysPowerFormula) = Table;
  }

  ClosestConfig = &Table[0];
  if ((*SysPowerFormula)->Config.Data != SysPwrConfig->Data) {
    for (Index = 0; Index < TableSize; Index++) {
      if (SysPwrConfig->Data == Table[Index].Config.Data) {
        (*SysPowerFormula) = &Table[Index];
        return;
      } else {
        if (Table[Index].Config.Bits.DdrType <= SysPwrConfig->Bits.DdrType) {
          if (Table[Index].Config.Bits.Frequency <= SysPwrConfig->Bits.Frequency) {
            if (Table[Index].Config.Bits.RttWr <= SysPwrConfig->Bits.RttWr) {
              ClosestConfig = &Table[Index];
            }
          }
        }
      }
    }
    (*SysPowerFormula) = ClosestConfig;
  }
}

/**
  This function reads the selected comp code.
  In case of comp up/dn we select the value that is closer to saturation (0 or 63).
  Safe assumption is that up/dn codes don't differ by too much.
  So if one of the codes is in the upper range (more than 32), we select MAX of both, otherwise we select MIN of both.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] OptParam - Parameter to read the relevant comp code.
  @param[in] UpDown   - 0 : up only. 1 : down only. 2 : use min/max of both Up and Down codes.

  @retval The selected Comp code
**/
UINT8
GetCompCode (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                OptParam,
  IN     UINT8                UpDown
  )
{
  MrcDebug                            *Debug;
  UINT32                              CurrentComp;
  UINT32                              UpCode;
  UINT32                              DownCode;
  INT64                               GetSetVal;
  GSM_GT                              GroupUp;
  GSM_GT                              GroupDn;
  BOOLEAN                             ReadReg;
  BOOLEAN                             Read2Regs;

  Debug  = &MrcData->Outputs.Debug;

  CurrentComp = 0;
  UpCode = DownCode = 0;

  if ((OptParam == OptRdOdt || OptParam == OptRdDqOdt || OptParam == OptRdDqsOdt) && (MrcData->Outputs.OdtMode == MrcOdtModeVtt)) {
    // in Vtt mode only odt up is valid
    UpDown = 0;
  }

  ReadReg   = TRUE;
  Read2Regs = TRUE;
  switch (OptParam) {
    case OptCmdDSUpCoarse:
      Read2Regs = FALSE;
      GroupUp = WrDSCodeUpCmd;
      GroupDn = WrDSCodeUpCmd;
      break;

    case OptCmdDSDnCoarse:
      Read2Regs = FALSE;
      GroupUp = WrDSCodeDnCmd;
      GroupDn = WrDSCodeDnCmd;
      break;

    case OptWrDSUpCoarse:
      Read2Regs = FALSE;
      GroupUp = TxRonUp;
      GroupDn = TxRonUp;
      break;

    case OptWrDSDnCoarse:
      Read2Regs = FALSE;
      GroupUp = TxRonDn;
      GroupDn = TxRonDn;
      break;

    case OptWrDS:
    case OptTxEq:
      GroupUp = TxRonUp;
      GroupDn = TxRonDn;
      break;

    case OptCmdTxEq:
    case OptCmdDS:
      GroupUp = WrDSCodeUpCmd;
      GroupDn = WrDSCodeDnCmd;
      break;

    case OptCtlDS:
      GroupUp = WrDSCodeUpCtl;
      GroupDn = WrDSCodeDnCtl;
      break;

    case OptClkDS:
      GroupUp = WrDSCodeUpClk;
      GroupDn = WrDSCodeDnClk;
      break;

    case OptRdDqsOdt:
    case OptRdDqOdt:
    case OptRdOdt:
      GroupUp = CompRcompOdtUp;
      GroupDn = CompRcompOdtDn;
      break;

    case OptRxLoad:
      // TGL_POWER_TRAINING Add this
      Read2Regs = FALSE;
      GroupUp = 0;// GroupUp = RloadDqsDn;
      GroupDn = 0;// GroupDn = RloadDqsDn;
      break;

    case OptSComp:
      Read2Regs = FALSE;
      GroupUp = SCompCodeDq;
      GroupDn = SCompCodeDq;
      break;

    case OptCCCSComp:
        Read2Regs = FALSE;
        GroupUp = SCompCodeCmd;
        GroupDn = SCompCodeCmd;
        break;

    case OptTxDqTco:
      Read2Regs = FALSE;
      GroupUp = TxTco;
      GroupDn = TxTco;
      break;

    case OptTxDqsTco:
        Read2Regs = FALSE;
        GroupUp = TxDqsTco;
        GroupDn = TxDqsTco;
        break;

    default:
      ReadReg = FALSE;
      GroupUp = 0;
      GroupDn = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetCompCode(): Invalid OptParam %d\n", OptParam);
      break;
  }

  if (ReadReg) {
    // TGL_POWER_TRAINING - Need to support reading from TxDqsTco, WrDSCodeUpCmd/WrDSCodeDnCmd, WrDSCodeUpCtl/WrDSCodeDnCtl, WrDSCodeUpClk/WrDSCodeDnClk, SCompCodeCmd, RloadDqsDn
    // TxDqsTco:
    //     DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1.DQSTcocomp
    // WrDSCodeUpCmd/WrDSCodeDnCmd:
    //     DDRCCC_CR_DDRCRCMDCOMP.RcompDrvUp/Down
    // WrDSCodeUpCtl/WrDSCodeDnCtl:
    //     DDRCCC_CR_DDRCRCTLCOMP.RcompDrvUp/Down
    // WrDSCodeUpClk/WrDSCodeDnClk:
    //     DDRCCC_CR_DDRCRCLKCOMP.RcompDrvUp/Down
    // SCompCodeCmd:
    //     DDRCCC_CR_DDRCRCTLCOMP.Scomp
    //     DDRCCC_CR_DDRCRCLKCOMP.Scomp
    //     DDRCCC_CR_DDRCRCMDCOMP.Scomp
    // RloadDqsDn:
    //     DDRDLL_CR_DdrCrVccDllCompDll.RloadDqs
    MrcGetSetNoScope (MrcData, GroupUp, ReadUncached, &GetSetVal);
    UpCode   = (UINT32) GetSetVal;
    if (Read2Regs) {
      MrcGetSetNoScope (MrcData, GroupDn, ReadUncached, &GetSetVal);
      DownCode = (UINT32) GetSetVal;
    } else {
      DownCode = UpCode;
    }
  } else {
    UpCode = 0;
  }

  if (UpDown == 2) {
    CurrentComp = (UpCode > 32) ?  MAX (UpCode, DownCode) : MIN (UpCode, DownCode);
  } else if (UpDown == 1) {
    CurrentComp = DownCode;
  } else {
    CurrentComp = UpCode;
  }

  return (UINT8) CurrentComp;
}

/**
  Program COMP Vref offset according to the passed parameter and target values.
  DqOdt segments:
   Based on setting of GsmIocDataODTSingleSegEn enumration, 1 segment if enum is set otherwise 2.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Param        - COMP Vref parameter (see TGlobalCompOffset).
  @param[in] RcompTarget  - Array of the Rcomp Targets COMP for { DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv }
  @param[in] UpdateHost   - Update host struct with the new value or not.

  @retval mrcSuccess  - if Param is a valid COMP Vref parameter
**/
MrcStatus
UpdateCompTargetValue (
  MrcParameters *const MrcData,
  UINT8                Param,
  UINT16               RcompTarget[MAX_RCOMP_TARGETS],
  BOOLEAN              UpdateHost
  )
{
  MrcDebug  *Debug;
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  INT64     GetSetVal;
  UINT32    Numerator;
  UINT32    Denominator;
  UINT32    FirstController;
  UINT32    FirstChannel;
  INT16     CompVrefUp;
  INT16     CompVrefDn;
  UINT16    ReferenceRUp;
  UINT16    ReferenceRDn;
  UINT16    TargetUpValue;
  UINT16    TargetDnValue;
  UINT8     NumOfSegments;
  UINT8     CompCodeUp;
  UINT8     CompCodeDn;
  BOOLEAN   VttOdt;
  CompGlobalOffsetParam GlobalCompUp;
  CompGlobalOffsetParam GlobalCompDn;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  VttOdt  = (Outputs->OdtMode == MrcOdtModeVtt);
  if (Param >= MAX_RCOMP_TARGETS) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Bad Param : %d\n", Param);
    return mrcFail;
  }
  TargetDnValue = TargetUpValue = RcompTarget[Param];
  ReferenceRDn = RcompTarget[Param];

  // The number of segments for CmdDrv, CtlDrv, and ClkDrv is 3
  // DqDrv is 2 segments
  // DqOdt is based on ODT mode: 1 for VTT and 2 for the rest.
  // RCOMP0: DQ ODT (read)
  // RCOMP1: DQ  / CLK Ron (drive strength)
  // RCOMP2: CMD / CTL Ron (drive strength)
  NumOfSegments = 3;
  switch (Param) {
    case RdOdt:
      FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
      FirstChannel = MrcData->Outputs.Controller[FirstController].FirstPopCh;
      MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocDataODTSingleSegEn, ReadFromCache, &GetSetVal);
      NumOfSegments = (GetSetVal) ? 1 : 2;
      GlobalCompUp = RdOdtUp;
      GlobalCompDn = RdOdtDn;
      TargetDnValue = RcompTarget[WrDS]; //Override the default
      break;

    case WrDS:
      NumOfSegments = 2;
      GlobalCompUp = WrDSUp;
      GlobalCompDn = WrDSDn;
      break;

    case WrDSClk:
      GlobalCompUp = WrDSClkUp;
      GlobalCompDn = WrDSClkDn;
      break;

    case WrDSCmd:
      GlobalCompUp = WrDSCmdUp;
      GlobalCompDn = WrDSCmdDn;
      break;

    case WrDSCtl:
      GlobalCompUp = WrDSCtlUp;
      GlobalCompDn = WrDSCtlDn;
      break;

    default:
      GlobalCompUp = 0;
      GlobalCompDn = 0;
      break;
  }

  ReferenceRUp = DIVIDEROUND (Inputs->RcompResistor, NumOfSegments);
  Numerator    = MRC_COMP_VREF_STEP_SIZE * ReferenceRUp;
  Denominator  = TargetUpValue + ReferenceRUp;
  if (VttOdt && (Param == RdOdt)) {
    // Do multiply by 2 here to optimize to 1 divide which handles rounding.
    Denominator *= 2;
  }
  Denominator = MAX (Denominator, 1);
  // Used UINT32 to prevent overflow of multiply with large UINT16 numbers.
  // Result should be less than UINT8 Max as register field is smaller than UINT8.
  CompVrefUp = (UINT16) DIVIDEROUND (Numerator, Denominator);
  Numerator    = MRC_COMP_VREF_STEP_SIZE * ReferenceRDn;
  Denominator  = TargetDnValue + ReferenceRDn;
  if (VttOdt && (Param == RdOdt)) {
    // Do multiply by 2 here to optimize to 1 divide which handles rounding.
    Denominator *= 2;
  }
  Denominator = MAX (Denominator, 1);
  // Used UINT32 to prevent overflow of multiply with large UINT16 numbers.
  // Result should be less than UINT8 Max as register field is smaller than UINT8.
  CompVrefDn = (UINT16) DIVIDEROUND (Numerator, Denominator);

  // Callee handles saturation at Min/Max values.
  CompCodeUp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalCompUp, CompVrefUp, TRUE, UpdateHost);
  CompCodeDn = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalCompDn, CompVrefDn, TRUE, UpdateHost);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%8s: Target (Up/Down) value: %3d/%3d ReferenceR (Up/Down): %3d/%3d VrefOffset (Up/Down): %3d/%3d Current Comp code (Up/Down): %3d/%3d\n",
    GlobalCompOffsetStr[Param],
    TargetUpValue,
    TargetDnValue,
    ReferenceRUp,
    ReferenceRDn,
    CompVrefUp,
    CompVrefDn,
    CompCodeUp,
    CompCodeDn
    );

  if ((CompCodeUp == 0) || (CompCodeUp == 63) || (CompCodeDn == 0) || (CompCodeDn == 63)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING: COMP code is saturated !\n");
  }

  return mrcSuccess;
}
/**
  This function returns the params setting accordingly to input.

  @param[in out] ParamOff- Parameters result Offsets
  @param[in]     GridMode- Selects the way we sweep the params
  @param[in]     Index   - Linear Index for all params
  @param[in]     YLen    - Determines the Y-Dimension lengths
  @param[in]     XLen    - Determines the X-Dimension lengths


  @retval if point is valid (tested)
**/
BOOLEAN
GetParamsXYZ (
  IN     MrcParameters      *const MrcData,
  IN OUT INT8              *ParamOff,
  IN     const UINT8        OptParamLen,
  IN     const UINT8        GridMode,
  IN     const UINT8        Index,
  IN     const INT8         *Start,
  IN     const UINT8        *ParamOffLen
)

{
  MrcDebug          *Debug;
  UINT8             XOff;
  INT8              YOff;
  BOOLEAN           SkipPoint = FALSE;

  Debug  = &MrcData->Outputs.Debug;

  if (OptParamLen == 1) {
    switch (GridMode) {
    case FullGrid:
      break;
    case HalfGrid:
      if (Index % 2) {
        SkipPoint = TRUE;
      }
      break;
    }
    ParamOff[0] =  Index + Start[0];

  } else if (OptParamLen == 2) {
    XOff =  Index % ParamOffLen[0];
    YOff =  Index / ParamOffLen[0];
    switch (GridMode) {
    case FullGrid:
      break;
    case ChessOdd:
      if (XOff % 2) {
        if (YOff % 2) {
          SkipPoint = TRUE;
        }
      } else {
        if (YOff % 2 == 0) {
          SkipPoint = TRUE;
        }
      }
      break;
    case ChessEven:
      if (XOff % 2) {
        if (YOff % 2 == 0) {
          SkipPoint = TRUE;
        }
      } else {
        if (YOff % 2) {
          SkipPoint = TRUE;
        }
      }
      break;
    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "unknow GridMode %d\t", GridMode);
    }

    ParamOff[0] = XOff + Start[0];
    ParamOff[1] = YOff + Start[1];
  }

  if (GridMode == CustomSR) {
    if (Index == 0) {
      ParamOff[0] =  -17; // disable SR for fastest SR
    }
  }

  if (GridMode == Reversed1D) {
    ParamOff[0] =  Start[0] + ParamOffLen[0] - 1 - Index; // reversed ordering for param
  }

    return SkipPoint;
}

/**
  Returns the index into RttType array

  @param[in] OptDimmOdt - DimmOdt type

  @retval One of the following values: RttWr RttNom RttPark

**/
DimmOdtType
GetRttType (
  IN const UINT8 OptDimmOdt
  )
{
  switch (OptDimmOdt) {
    case OptDimmOdtWr:
      return RttWr;

    case OptDimmOdtNom:
    case OptDimmOdtNomNT:
      return RttNom;

    case OptDimmOdtPark:
    case OptDimmOdtParkNT:
      return RttPark;

    default:
      break;
  }

  return RttMaxType;
}

/**
This function is used to train the Tx TCO Comp offset for Dq.
TCO Comp performs training using fixed pattern, in order to avoid optimization of TCO Comp based on ISI / Crosstalk
In order to leverage for very high margins resulting of fixed pattern, we ignore the power / UPM limits.

@param[in] MrcData - Pointer to global MRC data.

@retval - mrcSuccess
**/
MrcStatus
MrcTxDqTcoCompTraining (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { WrT };
  static const UINT8  Scale[] = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptTxDqTco };

  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  // Coarse search for Global comp
  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,
    &Stop,
    OPT_PARAM_1D_LC - 5,
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    StaticPattern         // PatType
    );

  return mrcSuccess;
}

/**
  This function is used to train the Tx TCO Comp offset for Dqs.
  TcoDqs trained per byte.

  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcTxDqsTcoCompTraining (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { WrT };
  static const UINT8  Scale[] = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptTxDqsTco };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  // Coarse search for Global comp
  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop = OptParamLimitValue (MrcData, OptParam[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,
    &Stop,
    OPT_PARAM_1D_LC - 2,
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    BasicVA               // PatType
    );

  return mrcSuccess;
}

/**
  This function is used to train the Clk TCO Comp code.

  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcClkTcoCompTraining (
  IN MrcParameters *const MrcData
)
{
  static const UINT8  TestList[] = { CmdT };
  static const UINT8  Scale[]    = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptClkTco };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    MrcData->Outputs.ValidChBitMask,
    MrcData->Outputs.ValidRankMask,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,
    &Stop,
    OPT_PARAM_1D_LC - 2,
    1,                    // Repeats
    0,                    // NoPrint
    0,                    // SkipOptUpdate
    0,                    // RdRd2Test
    0,                    // GuardBand
    StaticPattern         // PatType
    );

  return mrcSuccess;
}

// This is for debug
#if 0
void
GetMarginsByte4Debug (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT8                Param,
  IN     UINT16               PwrLimit,
  IN     UINT8                LoopCount,
  IN     UINT8                Repeats,
  IN     BOOLEAN              NoPrint
  )

{
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcStatus         Status;
  UINT32            (*MarginByte)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32            BERStats[4];
  UINT16            SaveMargin[MAX_MARGINS_TRADEOFF][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT16            MinEdge;
  UINT8             ChBitMask;
  UINT8             Channel;
  UINT8             localR[MAX_CHANNEL];
  UINT8             Byte;
  UINT8             Rank;
  UINT8             Edge;
  UINT8             NumBytes;
  UINT8             BMap[9]; // Need by GetBERMarginByte
  UINT8             MaxMargin;
  UINT8             Rep;
  UINT8             FirstRank;
  UINT8             ResultType;
  BOOLEAN           WriteVrefParam;

  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  MarginByte          = &Outputs->MarginResult;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  ControllerOut       = &Outputs->Controller[0];
  MrcCall             = MrcData->Inputs.Call.Func;
  WriteVrefParam      = ((Param == WrV) || (Param == WrFan2) || (Param == WrFan3));

  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  // @todo Update with McChBitMask
  SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, 0, 0, 0, 8, PatWrRd, 0, 0); // set test to all channels

  // Select All Ranks for REUT test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChannelMask)) {
      continue;
    }


    ChannelOut      = &ControllerOut->Channel[Channel];
    localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;

    // use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    ChBitMask |= SelectReutRanks (MrcData, Channel, localR[Channel], FALSE, 0);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "reut ranks ChBitMask %x Local ranks=%x\n", ChBitMask,localR[Channel]);
  }

  if (ChBitMask == 0) {
    return ;
  }

  // Find the first selected rank
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((MRC_BIT0 << Rank) & RankMask) {
      FirstRank = Rank; // could be in any channel
      break;
    }
  }

  ResultType = GetMarginResultType (Param);

  MaxMargin = MAX_POSSIBLE_TIME;
  if ((Param == RdV) ||
      (Param == RdFan2) ||
      (Param == RdFan3) ||
       WriteVrefParam
     ) {
   MaxMargin = GetVrefOffsetLimits (MrcData, Param);
  }

  // No need to search too far
  if (MaxMargin > (PwrLimit / 20)) {
    MaxMargin = (UINT8) (PwrLimit / 20);
  }
  NumBytes = (UINT8) Outputs->SdramCount;
  for (Rep = 0; Rep < Repeats; Rep++) {
    // Run Margin Test - margin_1d with chosen param
    // run on all ranks but change param only for firstRank??
    Outputs->Ddr4PdaEnable = TRUE;
    Status = MrcGetBERMarginByte (
      MrcData,
      Outputs->MarginResult,
      ChBitMask,
      RankMask,
      RankMask,
      Param,
      0,  // Mode
      BMap,
      1,
      MaxMargin,
      0,
      BERStats
      );

    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " finish MrcGetBERMarginByte \n");
    // Record Results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }

      for (Edge = 0; Edge < MAX_EDGES; Edge++) {
        MinEdge = 0xFFFF;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (Rep == 0) {
            SaveMargin[0][0][Channel][Byte][Edge] = 0;
          }

          SaveMargin[0][0][Channel][Byte][Edge] +=
            (UINT16) (*MarginByte)[ResultType][FirstRank][Channel][Byte][Edge];
          if (MinEdge > SaveMargin[0][0][Channel][Byte][Edge]) {
            MinEdge = SaveMargin[0][0][Channel][Byte][Edge];
          }
        }
        if (NumBytes == 1) {
          SaveMargin[0][0][Channel][0][Edge] = MinEdge; // Todo:change Byte->0
        }
      }
    }
  }
#ifdef MRC_DEBUG_PRINT
  PrintResultTableByte4by24 (
    MrcData,
    ChBitMask,
    SaveMargin,
    0,
    1,
    0,
    2,
    Param,
    Param,
    &PwrLimit,
    NoPrint //NoPrint
    );
#endif
}

#endif // #if 0

// This is for debug
#if 0
void
PointTest (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT8                LoopCount,
  IN     UINT8                NumCL,
  IN     BOOLEAN              NoPrint
  )

{
  const MRC_FUNCTION *MrcCall;
  MrcDebug           *Debug;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  UINT32            BERStats[4];
  UINT32            Offset;
  UINT8             ChBitMask;
  UINT8             Channel;
  UINT8             SubCh;
  UINT8             localR[MAX_CHANNEL];
  UINT8             Byte;
  UINT8             Rank;
  UINT8             BMap[9]; // Need by GetBERMarginByte
  UINT16            Results;
  UINT64            ErrStatus;
  UINT32            ErrCount;
  BOOLEAN           Overflow;
  UINT8             FirstRank;
  MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT                         ReutGlobalCtl;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  ControllerOut       = &Outputs->Controller[0];
  MrcCall             = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }
  // @todo Update with McChBitMask
  SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, 0, 0, 0, 8, PatWrRd, 0, 0); // set test to all channels
  // Select All Ranks for REUT test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut      = &ControllerOut->Channel[Channel];
    localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;
    // use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    ChBitMask |= SelectReutRanks (MrcData, Channel, localR[Channel], FALSE, 0);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "reut ranks ChBitMask %x Local ranks=%x\n", ChBitMask,localR[Channel]);
  }
  if (ChBitMask == 0) {
    return;
  }
  // Find the first selected rank
  FirstRank = 0;
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((MRC_BIT0 << Rank) & RankMask) {
      FirstRank = Rank; // could be in any channel
      break;
    }
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++)  {
      // Setup REUT Error Counters to count errors per Byte Group, 1 count per UI with an error across all lanes in the Byte Group, all UI
      MrcSetupErrCounterCtl (MrcData, BMap[Byte], ErrCounterCtlPerByte, 0);
    }
  }
  ReutGlobalCtl.Data = 0;
  ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data); // Clear errors
  // Run Test
  RunIOTest (MrcData, /**McBitMask**/ 1, ChBitMask, Outputs->DQPat, 0, 0);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }
    Results = 0;
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      // Read out per byte error results
      MrcGetMiscErrStatus (MrcData,  /**Controller**/ 0, Channel, ByteGroupErrStatus, &ErrStatus);
      Results |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
    }
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      // Read Error Count
      MrcGetErrCounterStatus (MrcData, /*Controller*/ CONTROLLER_0, Channel, Byte, ErrCounterCtlPerByte, &ErrCount, &Overflow);
      if (!NoPrint) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d Byte=%d Error Counter:%d\n", Channel, Byte, ErrCount);
      }
    }
  }
}
#endif // #if 0

