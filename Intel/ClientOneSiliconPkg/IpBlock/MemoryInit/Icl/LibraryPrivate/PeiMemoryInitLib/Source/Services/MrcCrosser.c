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
#include "MrcDdrCommon.h"
#include "MrcMcConfiguration.h"
#include "MrcCpgcApi.h"
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

/// ICOMP/RCOMP MAX values
#define MRC_ICOMP_NUM         (4)
#define MRC_RCOMP_NUM         (4)

// POWER MACRO for Calculate a power score based on max power.
#define POWSCORE(max_pow, max , curr,per) ((max_pow) * (((max)-(curr))*100 / max) * (per) / 10000)
#define POWSCORE_IRCOMP(icomp,rcomp,mul,div) ((16*(icomp) + 34*(rcomp))*(mul)/(div))

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
  {RdFan3,    {240*4/5, 480*4/5, 0  }},
  {WrFan3,    {240*4/5, 480*4/5, 0  }},
  // {650ps,750ps} * 64 pi ticks * 2 (for width) = 134 PI Ticks ->  ~1.3nsec for UPM, 154 PI Ticks -> ~1.5nsec for PWR
  // Margin function works in steps of 4, so we divide the margin by 4.
  // Margin numbers are scaled by 10.
  {RcvEnaX,  {(134 / 4 * 10), (154 / 4 * 10), 0}}
};

GLOBAL_REMOVE_IF_UNREFERENCED const MrcOptParamsLimits  MrcOptParamLimit[MRC_NUMBER_OPT_PARAMS_TRAIN] = {
  //                Normal/SAGV(high), SAGV (low), DT/Halo (max perf.)
  {OptRdOdt,          {-15,      15}, {-15,      15}, {-15,      15}},
  {OptRxBias,         {0,         7}, {0,         7}, {0,         7}},  // 0-7 is not a real range but when the sweep will be by step of 2 for 0-15 range
  {OptRxRComp,        {0,         7}, {0,         7}, {0,         7}},  // 0-7 is not a real range but when the sweep will be by step of 2 for 0-15 range
  {OptRxCb,           {0,         3}, {0,         3}, {0,         3}},
  {OptRxEq,           {0, MAX_RX_EQ}, {0, MAX_RX_EQ}, {0, MAX_RX_EQ}},
  {OptTxEq,           {3,        10}, {4,         8}, {6,        15}},
  {OptWrDS,           {-15,      15}, {-11,       0}, {-9,       10}},
  {OptWrDSDnCoarse,   {-13,       2}, {-11,       0}, {-7,        7}},
  {OptWrDSUpCoarse,   {-13,       2}, {-11,       0}, {-7,        7}},
  {OptSComp,          {-15,       5}, {-15,       5}, {-15,      10}},
  {OptCmdSCompOffset, {-16,      15}, {-16,      15}, {-16,      15}},
  {OptCmdDS,          {0,        21}, {0,        21}, {0,        21}},
  {OptCmdTxEq,        {0,         3}, {0,         3}, {0,         3}},
  {OptClkTco,         {0,        31}, {0,        31}, {0,        31}},
  {OptTxTco,          {0,        63}, {0,        63}, {0,        63}},
  {OptTxTcoDqsP,      {0,        31}, {0,        31}, {0,        31}},
  {OptTxTcoDqsN,      {0,        31}, {0,        31}, {0,        31}}, // -1 - is a bypass value
  {OptDqDfeMode,      {0,        22}, {0,        22}, {0,        22}},
  {OptDqDfeDly,       {0,        63}, {0,        63}, {0,        63}},
  {OptDqDfeCoeff,     {0,         3}, {0,         3}, {0,         3}}
};

const MRC_RSM_POWER_FORMULA RSMPowerCalcTableRx[] = {
  // CpuOdt, Dram_Odt, Mb_mail_len, Sodimm_len
  // table structure (from Struct def):
  //  {SysConfig}, Intercept0,
  //  {Intercept, FirstOrder, SecondOrder, {Interactions[MaxTxPowerParam]}
  // DDR4 Rx - will plan to use it for all Ddr tech - should be close enough

  {{{f1333, MRC_DDR_TYPE_DDR4, 34, 0}},     105395535,
   {{300,   -5847,       12,    {0,     18,    1,    4}},
    {300,   -69132,     232,    {18,     0,    0,    3}},
    {1800,  925,         -2,    {1,      0,    0,   -4}},
    {500,   5016,        -1,    {4,      3,   -4,    0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, 48, 0}},     92397977,
   {{300,   -7601,       18,    {0,     26,    0,    3}},
    {300,   -63125,     204,    {26,     0,    0,    2}},
    {1800,     330,      -1,    {0,      0,    0,   -2}},
    {500,     2957,       0,    {3,      2,   -2,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, 34, 0}},     115767593,
   {{300,   -6506,       15,    {0,     15,   -3,    0}},
    {300,   -69132,      231,   {15,     0,    0,    3}},
    {1800,   -3171,       0,    {-3,     0,    0,   -2}},
    {500,      744,      -2,    {0,      3,   -2,    0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, 48, 0}},     98453822,
   {{300,   -8211,       20,    {0,     23,    -2,   0}},
    {300,   -62632,     204,    {23,     0,    0,    2}},
    {1800,   -2023,       0,    {-2,     0,    0,   -1}},
    {500,      491,       0,    {0,      2,   -1,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, 34, 0}},     109653751,
   {{300,   -6728,       17,    {0,     17,    0,    1}},
    {300,   -67527,     225,    {17,     0,    1,    0}},
    {1800,  -91,          3,    {0,      1,    0,    7}},
    {500,   1973,         0,    {1,      0,    7,    0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, 48, 0}},     94425599,
   {{300,   -8145,       21,    {0,     25,    0,    2}},
    {300,   -62024,     200,    {25,     0,    1,    0}},
    {1800,  63,           2,    {0,      1,    0,    4}},
    {500,   1332,         0,    {2,      0,    4,    0}}}}
 };

const MRC_RSM_POWER_FORMULA RSMPowerCalcTableTx[] = {
  // SR, Ron, TxEq, Mb_len
  // table structure (from Struct def):
  //  {SysConfig}, Intercept0,
  //  {Intercept, FirstOrder, SecondOrder, {Interactions[MaxTxPowerParam]}
  // Table is arranged from low to high (DdrType(enu), Freq, Odt)
  // DDR4 (6 params - SR, Ron, TxEq, Dimm Passive Odt, MBlength, SodimmLen)
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},  115462438,
  {{55,   26245,    205,    {0,    -1308,        3,      -18,       -2,        1}},
  {50,    -755958,  6427,   {-1308,    0,     -349,      305,      -59,      -24}},
  {409,   -13432,   27,     {3,     -349,        0,        7,        0,        0}},
  {300,   -32419,   90,     {-18,    305,        7,        0,        0,        0}},
  {1800,    1339,   -1,     {-2,     -59,        0,        0,        0,       -3}},
  {500,   104,      -1,     {1,      -24,        0,        0,       -3,        0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},  133044732,
  {{55,   26537,    198,    {0,    -1279,        5,       -4,       -1,        1}},
  {50,    -928307,  7413,   {-1279,    0,        -465,       287,      -40,    3}},
  {409,   -17043,   36,     {5,     -465,        0,        6,        0,        0}},
  {300,   -14221,   46,     {-4,     287,        6,        0,        0,        0}},
  {1800,  1030,     0,      {-1,     -40,        0,        0,        0,       -2}},
  {500,   -114,     -1,     {1,        3,        0,        0,       -2,        0}}}},
  {{{f1333, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},  125126929,
  {{55,     26515,    211,  {0,     -1265,         3,      -15,       -2,        0}},
  {50,    -843921,  6705,   {-1265,     0,      -418,      325,      -48,      -12}},
  {409,   -15312,   30,     {3,      -418,         0,        6,        0,        0}},
  {300,   -20526,   61,     {-15,     325,         6,        0,        0,        0}},
  {1800,  1180,     -1,     {-2,      -48,         0,        0,        0,       -2}},
  {500,   -6,       -1,     {0,       -12,         0,        0,       -2,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},    125976146,
  {{55,   31187,    262,    {0,      -1473,       -8,        0,       -1,        3}},
  {50,    -793451,  7071,   {-1473,      0,     -388,      299,       23,       29}},
  {409,   -13601,   29,     {-8,      -388,        0,       10,        0,        0}},
  {300,   -32894,   90,     {0,         299,      10,        0,       -1,        0}},
  {1800,  -1699,    -1,     {-1,        23,        0,       -1,        0,        0}},
  {500,   -1855,     0,     {3,         29,        0,        0,        0,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},    141684820,
  {{55,   31563,    237,    {0,     -1481,        -1,       0,         0,        4}},
  {50,    -966674,  8023,   {-1481,     0,      -502,      284,        8,       34}},
  {409,   -17306,   38,     {-1,     -502,         0,       10,        0,        0}},
  {300,   -14414,   46,     {0,       284,        10,        0,        0,        0}},
  {500,   -994,     0,      {0,        8,          0,        0,        0,        0}},
  {500,   -1357,    0,      {4,        34,         0,        0,        0,        0}}}},
  {{{f1600, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},    134734817,
  {{55,   31272,    262,    {0,     -1448,        -5,        0,       -1,        2}},
  {50,    -882744,  7319,   {-1448,     0,       -456,     321,        15,      29}},
  {409,   -15555,   33,     {-5,     -456,         0,       10,        0,        0}},
  {300,   -20861,   61,     {0,       321,        10,        0,        0,        0}},
  {1800,  -1321,   -1,      {-1,       15,         0,        0,        0,        0}},
  {500,   -1611,    0,      {2,        29,         0,        0,        0,        0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWrOff , 0}},    123734556,
  {{55,   34896,    283,    {0,     -1621,        -4,      -10,       -2,        4}},
  {50,    -797003,  7976,   {-1621,      0,     -380,      368,       21,       -7}},
  {409,   -14209,   29,     {-4,      -380,        0,        8,        0,       -2}},
  {300,   -33617,   92,     {-10,      368,        8,        0,        0,        0}},
  {1800,  -451,     2,      {-2,        21,        0,        0,        0,        6}},
  {500,   514,      1,      {4,         -7,        -2,       0,        6,        0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWr120 , 0}},    143297952,
  {{55,   35400,    315,    {0,    -1546,       -3,      -20,       -1,          2}},
  {50,    -984620,  8717,   {-1546,        0,     -519,      341,       13,     -9}},
  {409,   -18248,   36,     {-3,      -519,        0,        5,        0,        0}},
  {300,   -15136,   45,     {-20,      341,        5,        0,        0,        0}},
  {1800,  -454,     0,      {-1,        13,        0,        0,        0,        4}},
  {500,   566,      0,      {2,       -9,        0,        0,        4,          0}}}},
  {{{f1867, MRC_DDR_TYPE_DDR4, RttWr240 , 0}},    134001833,
  {{55,   35128,    293,    {0,      -1599,       -3,      -11,       -1,         4}},
  {50,    -892813,  8145,   {-1599,      0,     -458,      380,       17,        -6}},
  {409,   -16209,   33,     {-3,      -458,        0,        8,        0,        -1}},
  {300,   -21631,   64,     {-11,      380,        8,        0,        0,         0}},
  {1800,  -452,     1,      {-1,        17,        0,        0,        0,         5}},
  {500,   549,      1,      {4,          -6,      -1,        0,        5,         0}}}},
  // LPDDR3
  {{{f1067, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 106603589,
   {{80,   19833,    0,     {0,     -739,   0,    0}},
    {50,   -856523,  9074,  {-739,  0,      -273, 0}},
    {409,  -6926,    15,    {0,     -273,   0,    0}},
    {1099, 950,      -9,    {0,     0,      0,    0}}}},
  {{{f1333, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 115178290,
   {{80,   24153,     0,    {0,      -1180,  0,    0}},
    {50,   -865982,   9677, {-1180, 0,      -327,  0}},
    {409,   -10515,   23,   {0,      -327,    0,    0}},
    {1099, -6601,     -3,   {0,      0,      0,    0}}}},
  {{{f1600, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 114565521,
   {{80,   34158,    0,     {0,      -1467,  0,    0}},
    {50,   -846187,  10144, {-1467,  0,      -335,  0}},
    {409,   -13245,  29,    {0,      -335,    0,    0}},
    {1099, -9283,    1,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWrOff, 0}}, 107490163,
   {{80,   44175,    0,     {0,      -1861,  0,    0}},
    {50,   -825584,  10364, {-1861,  0,      -332,  0}},
    {409,   -14545,  33,    {0,      -332,    0,    0}},
    {1099, -5825,    9,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWr120, 0}}, 126800419,
   {{79,   45367,    0,     {0,      -1464,  0,    0}},
    {50,   -847125,  7984,  {-1464,  0,      -397,  0}},
    {409,   -14781,  32,    {0,      -397,    0,    0}},
    {1099, -5169,    8,     {0,      0,      0,    0}}}},
  {{{f1867, MRC_DDR_TYPE_LPDDR3, RttWr240, 0}}, 122800419,
   {{79,   45367,    0,     {0,      -1464,  0,    0}},
    {50,   -847125,  7984,  {-1464,  0,      -397,  0}},
    {409,   -14781,  32,    {0,      -397,    0,    0}},
    {1099, -5169,    8,     {0,      0,      0,    0}}}},
 };

// DDR Params encoding
#ifdef MRC_DEBUG_PRINT
GLOBAL_REMOVE_IF_UNREFERENCED const char  *TOptParamOffsetString[] = {
  "WrDS",
  "SComp",
  "TxTCoComp",
  "ClkTCoComp",
  "TxTCoCompoff",
  "TxEq",
  "RdOdt",
  "RxEq",
  "RxBias",
  "RxRComp",
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
  "WrDSUpX",
  "WrDSDnX",
  "OptRdOdtUp",
  "OptRdOdtDn",
  "CmdDS",
  "CtlDS",
  "ClkDS",
  "RxBiasCb",
  "TxEqWrDS",
  "CmdTxEq",
  "CmdSR",
  "CmdSROffset",
  "OptTxTcoDqsP",
  "OptTxTcoDqsN",
  "OptDimmSocOdt",
  "OptDqDfeMode",
  "OptDqDfeDly",
  "OptDqDfeCoeff",
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
  "WrDSClk",
  "SCompDq",
  "SCompCmd",
  "SCompCmdOffset",
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

UINT8 LPFARR33[3][3] = {
  { 1, 2, 1 },
  { 2, 4, 2 },
  { 1, 2, 1 }
};

UINT8 LPFARR55[5][5] = {
  { 1, 1, 1, 1, 1 },
  { 1, 3, 3, 3, 1 },
  { 1, 3, 7, 3, 1 },
  { 1, 3, 3, 3, 1 },
  { 1, 1, 1, 1, 1 }
};

/**
This function made for Matrix Convolution, Get an Matrix,
perform Convolution using Convolution matrix and updatre result matrix

@param[in]  arr         - Input array
@param[out] newarr      - Output array
@param[in]  row         - Number of rows in input/output arrays
@param[in]  col         - Number of columns in input/output arrays
@param[in]  ColForSeek  - Number of columns that are actually used
@retval None

**/
void
MrcConvolution2D(
  UINT32    *arr,
  UINT32    *newarr,
  UINT16    row,
  UINT16    col,
  UINT16    ColForSeek,
  UINT8     *lpfarr,
  UINT8     size)
{
  INT16   i, j, ii, jj, xi, xj;
  INT16   center;
  UINT32  weight;

  center = (size - 1) >> 1;
  for (i = 0; i < row; i++) {
    for (j = 0; j < ColForSeek; j++) {
      weight = 0;
      newarr[j + i*col] = 0;
      for (ii = 0; ii < size; ii++) {
        for (jj = 0; jj < size; jj++) {
          xi = i - center + ii;
          xj = j - center + jj;
          if ((xi < 0) || (xi >= row) || (xj < 0) || (xj >= ColForSeek))
          {
            continue;
          }
          weight += lpfarr[jj + ii*size];
          newarr[j + i*col] += (arr[xj + xi*col] * lpfarr[jj + ii*size]);
        }
      }
      newarr[j + i*col] = newarr[j + i*col] / weight;
    }
  }
}

/**
  This function implements Sense Amp Offset training.
  SenseAmp/ODT offset cancellation
  Find the best "average" point for Vref Control
  Test Vref point with SampOffset=-7 and Test Vref Point with SampOffset=+7
  Find Vref on per ch/byte basis where -7 samples all 1 and +7 samples all 0

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
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MRC_ODT_MODE_TYPE   OdtModeSave;
  INT64               GetSetVal;
  INT64               GetSetEn;
  INT64               GetSetDis;
  INT64               ForceBiasOnSaved;
  INT64               ForceRxOnSaved;
  INT64               StrongWkLeakerSave;
  INT64               StrongWkLeakerMsbSave;
  INT64               LeakerComp;
  INT64               RxVocMax;
  UINT32              Offset;
  UINT32              SenseAmpTestDelay;
  INT8                sumBits[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                FirstBestPoint[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                LastBestPoint[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                firstZero[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];  // Additional bit for DQS per each byte
  INT8                lastOne[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS_FOR_OFFSET_TRAINING];  // Additional bit for DQS per each byte
  INT8                sampOffset;
  UINT8               HighMask[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8               LowMask[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                VrefCenter[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                VrefSaved[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                vref;
  INT8                VrefWidth;
  INT8                LowVrefTested;
  INT8                HighVrefTested;
  INT8                VrefStep;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               byte;
  UINT8               bit;
  UINT8               MaxRank;
  UINT8               RankHalf;
  UINT8               RankMod2;
  UINT8               RankMask;
  BOOLEAN             IclB;
  BOOLEAN             Ddr4;
  BOOLEAN             Lpddr4;
  BOOLEAN             VrefStageFailed;
  BOOLEAN             FirstRankFound;
  DDRDATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DataTrainFeedback;
  DDR4_MODE_REGISTER_5_STRUCT             Ddr4ModeRegister5;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  ControllerOut   = &Outputs->Controller[0];
  Status          = mrcSuccess;
  Ddr4            = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4          = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  MaxRank         = MAX_RANK_IN_CHANNEL;
  GetSetEn        = 1;
  GetSetDis       = 0;
  OdtModeSave     = Outputs->OdtMode;
  VrefStageFailed = FALSE;
  LowVrefTested   = -60;
  HighVrefTested  = 60;
  VrefStep        = 1;
  SenseAmpTestDelay = MRC_TIMER_1US;
  IclB            = (Inputs->CpuModel == cmICL_ULX_ULT) && ((Inputs->CpuStepping == csIclB0) || (Inputs->CpuStepping == csIclB4));


  // Init LastBestPoint to 0, FirstBestPoint to 0, LowMask to 0xff and HighMask to 0
  MrcCall->MrcSetMem ((UINT8 *) LastBestPoint,  sizeof (LastBestPoint), 0);
  MrcCall->MrcSetMem ((UINT8 *) FirstBestPoint, sizeof (FirstBestPoint), 0);
  MrcCall->MrcSetMem ((UINT8 *) LowMask,  sizeof (LowMask), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) HighMask, sizeof (HighMask), 0);

  // DDR4 uses N-path, so the range is [0..15]
  // LP4 (P-Path) range is [0..31]
  MrcGetSetLimits (MrcData, RxVoc, NULL, &RxVocMax, NULL);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    FirstRankFound = FALSE;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      if (!FirstRankFound) {
        // Find first rank present in each channel.  Need to set Rank Mux to this rank for training.
        GetSetVal = Rank;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteToCache, &GetSetVal);
        FirstRankFound = TRUE;
      }
      if (Ddr4) {
        // Disable RttPark on DDR4
        RankMask = 1 << Rank;
        SetDimmParamValue (MrcData, Channel, RankMask, 0, OptDimmOdtPark, 0, FALSE);
      }
    } // for Rank
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
        continue;
      }
      if (Outputs->SenseAmpRetrain) {
        // Save RxVref point
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, RxVref, ReadUncached | GSM_PRINT_VAL, &GetSetVal);
        VrefSaved[Channel][byte] = (INT8) GetSetVal;
      }
      // Save current ForceBiasOn / ForceRxOn values; they should have same values on all bytes
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocForceBiasOn,  ReadFromCache, &ForceBiasOnSaved);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocForceRxAmpOn, ReadFromCache, &ForceRxOnSaved);
    } // for byte
  } // for Channel

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,    WriteToCache, &GetSetEn);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn,   WriteToCache, &GetSetEn);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetEn);

  // Switch to CTT before continuing training.  No impact if we are already CTT Mode.
  MrcSetIoOdtMode (MrcData, MrcOdtModeCtt);
  // Force ODT on for the duration of the training
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteToCache, &GetSetEn);
  MrcFlushRegisterCachedData (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Stage 1: Vref Offset Training\nPlot Of SumOfBits across Vref settings\nChannel\t0\t\t1\nByte\t");
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    (Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8\n" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7\n"
    );

  // Sweep through vref settings and find point SampOffset of MIN/MAX passes
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "1/2 Vref");
  for (vref = LowVrefTested; vref <= HighVrefTested; vref += VrefStep) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", vref);

    // Program settings for Vref and SampOffset = MAX
    Status = ChangeMargin (MrcData, RdV, vref, 0, 1, 0, 0, 0, 0, 0, 0);

    GetSetVal = RxVocMax;
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVoc, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    // To run test, enable Offset Cancel mode and Enable ODT
    // Check Results and Update variables.  Ideal result is all 0
    // Clear Offset Cancel mode at end test to enable writing RX_OffsetV
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        // Propagate delay values
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetEn);
        MrcFlushRegisterCachedData (MrcData);
        MrcWait (MrcData, SenseAmpTestDelay);

        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          if (MrcByteInChannelExist (MrcData, Channel, byte)) {
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocSenseAmpMode, WriteToCache, &GetSetDis);
            Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
            DataTrainFeedback.Data  = (UINT8) MrcReadCR (MrcData, Offset);
            sumBits[Channel][byte]  = -(MrcCountBitsEqOne (DataTrainFeedback.Bits.DataTrainFeedback));
            LowMask[Channel][byte] &= (UINT8) DataTrainFeedback.Bits.DataTrainFeedback;
          }
        }
        MrcFlushRegisterCachedData (MrcData);
      }
    }
    // Program settings for SampOffset = MIN
    GetSetVal = 0;
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVoc, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
          );
      } else {
        ChannelOut = &ControllerOut->Channel[Channel];

        // Propagate delay values
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetEn);
        MrcFlushRegisterCachedData (MrcData);
        MrcWait (MrcData, SenseAmpTestDelay);

        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
            continue;
          }
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocSenseAmpMode, WriteCached, &GetSetDis);
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
          DataTrainFeedback.Data = (UINT8) MrcReadCR (MrcData, Offset);
          sumBits[Channel][byte] += MrcCountBitsEqOne (DataTrainFeedback.Bits.DataTrainFeedback);
          HighMask[Channel][byte] |= DataTrainFeedback.Bits.DataTrainFeedback;

          // Check if this point is better
          if (sumBits[Channel][byte] > FirstBestPoint[Channel][byte]) {
            FirstBestPoint[Channel][byte] = sumBits[Channel][byte];
            LastBestPoint[Channel][byte]  = vref;
            VrefCenter[Channel][byte]     = vref;
          } else if (sumBits[Channel][byte] == FirstBestPoint[Channel][byte]) {
            LastBestPoint[Channel][byte] = vref;
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", sumBits[Channel][byte]);
        }
      }
    }
  } // for vref

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nHi-Lo\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "         ");
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "0x%02x 0x%02x ", HighMask[Channel][byte], LowMask[Channel][byte]);
        // Exit with error if any bit did not change
        if (((HighMask[Channel][byte] ^ LowMask[Channel][byte]) != 0xFF) || (FirstBestPoint[Channel][byte] < 8)) {
          VrefStageFailed = TRUE;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "\nERROR! At least one bit with unexpected results for Channel %u Byte %u\n",
            Channel,
            byte
            );
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "A '0' in the following BitMask value represents the failing Bit(s) 0x%x\n",
            (HighMask[Channel][byte] ^ LowMask[Channel][byte])
            );
        }
      }
    }
  }

  if (VrefStageFailed && Inputs->ExitOnFailure) {
    return mrcSenseAmpErr;
  }

  // Display the selected Read Vref per byte
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdVref\t");
#endif // MRC_DEBUG_PRINT
  // Clear RdV offset
  Status = ChangeMargin (MrcData, RdV, 0, 0, 1, 0, 0, 0, 0, 0, 0);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      // Upate RxVref center
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
          continue;
        }
        VrefWidth = (LastBestPoint[Channel][byte] - VrefCenter[Channel][byte]);
        vref      = (VrefCenter[Channel][byte] + (VrefWidth / 2));

        // Add 1 to Round Up and find the center
        if (vref < 0) {
          vref--;
        } else {
          vref++;
        }
        // step size for RxVref is VDD/192 AND for RxVrefOffset is VDD/384
        GetSetVal = vref / 2;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2d ", (INT8) GetSetVal);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, RxVref, WriteOffsetCached | GSM_PRINT_VAL, &GetSetVal);
      }
      if (Lpddr4) {
        // Leaker settings are the same for all Data Bytes.  So we only save one value to restore.
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, 0, GsmIocStrongWeakLeaker,    ReadFromCache, &StrongWkLeakerSave);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, 0, GsmIocStrongWeakLeakerMsb, ReadFromCache, &StrongWkLeakerMsbSave);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, 0, GsmIocLeakerComp,          ReadFromCache, &LeakerComp);
      }
    }
  }
  // init firstZero and lastOne to 0
  MrcCall->MrcSetMem ((UINT8 *) firstZero, sizeof (firstZero), 0);
  MrcCall->MrcSetMem ((UINT8 *) lastOne, sizeof (lastOne), 0);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nStage 2: SampOffset Training\nChannel 0\t\t\t\t\t\t\t\t\t \t1\nByte    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d         ", byte);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nBits    ");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "01234567S ");
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n SAmp");
#endif // MRC_DEBUG_PRINT

  // Disable Leaker / Park mode so that we can train DQS properly
  if (Lpddr4) {
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocStrongWeakLeaker, WriteToCache, &GetSetDis);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLeakerComp,       WriteToCache, &GetSetDis);
    if (!Inputs->IclA0 && !IclB) { // C0+
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocStrongWeakLeakerMsb,       WriteToCache, &GetSetDis);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsNOnWithLeaker,  WriteToCache, &GetSetDis);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsPOnWithLeaker,  WriteToCache, &GetSetDis);
    }
    if (Inputs->IclA0 || IclB) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsNOn,  WriteToCache, &GetSetDis);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsPOn,  WriteToCache, &GetSetDis);
    }
  }

  for (sampOffset = 0; sampOffset <= (INT8) RxVocMax; sampOffset++) {
    // Display per Byte Feedback from REUT Registers
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", sampOffset);

    // Program Offset
    GetSetVal = sampOffset;
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVoc, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t\t");
        continue;
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsAmpOffset, WriteToCache, &GetSetVal);
      MrcFlushRegisterCachedData (MrcData);
      // Propagate delay values
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetEn);
      MrcFlushRegisterCachedData (MrcData);
      MrcWait (MrcData, SenseAmpTestDelay);

      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "         ");
          continue;
        }
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocSenseAmpMode, WriteCached, &GetSetDis);
        Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, byte);
        DataTrainFeedback.Data = MrcReadCR (MrcData, Offset);
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DataTrainFeedback = 0x%x, sampOffset = %d\n", DataTrainFeedback.Data, sampOffset);

        for (bit = 0; bit < MAX_BITS_FOR_OFFSET_TRAINING; bit++) {
          if (DataTrainFeedback.Bits.DataTrainFeedback & (MRC_BIT0 << bit)) {
            lastOne[Channel][byte][bit] = sampOffset;
          } else {
            if (firstZero[Channel][byte][bit] == 0) {
              firstZero[Channel][byte][bit] = sampOffset;
            }
          }
          // Display in bits
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            ((MRC_BIT0 << bit) & DataTrainFeedback.Bits.DataTrainFeedback) ? "1" : "0"
            );
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
      }
    } // for Channel
  } // for sampOffset

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nBitSAmp ");

  // Calculate and Program Offsets and display per bit SenseAmp Offset
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t\t\t\t"); // Line up Channel 1
      continue;
    }
    ChannelOut    = &ControllerOut->Channel[Channel];
    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "         ");
        continue;
      }
      for (bit = 0; bit < MAX_BITS_FOR_OFFSET_TRAINING; bit++) {
        // Find vref center, add 1 for Round Up
        vref = (firstZero[Channel][byte][bit] + lastOne[Channel][byte][bit]) / 2;

        // Check for saturation conditions
        // to make sure we are as close as possible to vdd/2 (750mv)
        if (firstZero[Channel][byte][bit] == 0) {
          vref = (INT8) RxVocMax;
        }

        if (lastOne[Channel][byte][bit] == 0) {
          vref = 0;
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%X", vref);
        if (bit == 8) {
          GetSetVal = vref;
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, RxDqsAmpOffset, WriteCached, &GetSetVal);
          break;
        }

        GetSetVal = vref;
        for (Rank = 0; Rank < MaxRank; Rank++) {
          ChannelOut->RxDqVrefPb[Rank][byte][bit].Center = vref;
          MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, byte, bit, RxVoc, WriteCached, &GetSetVal);
        }
      } // for Bit
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " ");
    } // for Byte
  } // for Channel
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  // Clean up after test.
  // Disable Senseamp Mode and ForceOdtOn mode.
  // Disable ForceOdtOn before ODT mode switch.
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocSenseAmpMode, WriteToCache, &GetSetDis);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,   WriteToCache, &GetSetDis);

  // Restore Leaker / Park settings
  if (Lpddr4) {
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocStrongWeakLeaker, WriteToCache, &StrongWkLeakerSave);
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLeakerComp,       WriteToCache, &LeakerComp);
    if (!Inputs->IclA0 && !IclB) { // C0+
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocStrongWeakLeakerMsb,       WriteToCache, &StrongWkLeakerMsbSave);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsNOnWithLeaker,  WriteToCache, &GetSetEn);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsPOnWithLeaker,  WriteToCache, &GetSetEn);
    }
    if (Inputs->IclA0 || IclB) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsNOn,  WriteToCache, &GetSetEn);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocLp4ForceDqsPOn,  WriteToCache, &GetSetEn);
    }
  }

  MrcFlushRegisterCachedData (MrcData);
  MrcSetIoOdtMode (MrcData, OdtModeSave);  // Restore ODT mode

  if (Ddr4) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        RankMask = 1 << Rank;
        RankHalf = Rank / 2;
        RankMod2 = Rank % 2;
        // Restore RTT_PARK for this rank
        Ddr4ModeRegister5.Data = ChannelOut->Dimm[RankHalf].Rank[RankMod2].MR[mrMR5];
        Status = MrcWriteMRS (MrcData, Channel, RankMask, mrMR5, (UINT16) Ddr4ModeRegister5.Data);
      } // for Rank
    } // for Channel
  }

  // Disable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetDis);

  // Restore ForceBiasOn / ForceRxOn
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceBiasOn,  WriteToCache, &ForceBiasOnSaved);
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &ForceRxOnSaved);
  MrcFlushRegisterCachedData (MrcData);

  Status = IoReset (MrcData);
  if (Outputs->SenseAmpRetrain) {
    // restore RxVref point
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        // Upate RxVref center
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, byte)) {
            continue;
          }
          GetSetVal = VrefSaved[Channel][byte];
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, RxVref, ForceWriteCached | GSM_PRINT_VAL, &GetSetVal);
        }
      }
    } // channel
    // Re-Centering
    DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, 0, 10, MRC_PRINTS_OFF, FALSE);
    DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, 0, 10, MRC_PRINTS_OFF, FALSE);
    DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV,  0, 10, MRC_PRINTS_OFF, FALSE);
  }

  Outputs->SenseAmpRetrain = FALSE;
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
  UINT32                  (*LastMargins)[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                  BERStats[4];
  UINT16                  MinEdgeMargin[MAX_EDGES];
  UINT16                  RetrainMarginLimit;
  UINT16                  CurrentMargin;
  UINT8                   Channel;
  UINT8                   ChannelMask;
  UINT8                   Rank;
  UINT8                   RankMask;
  UINT8                   Edge;
  UINT8                   Loopcount;
  UINT8                   MaxMargin;
  BOOLEAN                 RdWrMarginFail[2];

  MrcCall             = MrcData->Inputs.Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  LastMargins         = Outputs->MarginResult;
  Status              = mrcSuccess;
  Loopcount           = 17;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  RdWrMarginFail[0] = FALSE;
  RdWrMarginFail[1] = FALSE;
  MaxMargin         = 0;
  // Loop is dependent on the order of MRC_MarginTypes.  If this changes, pleas ensure functionality
  // stays the same.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Loopcount: %d\n", Loopcount);
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, Loopcount, NSOE, 0, 0, 8);
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask    = 1 << Rank;
    ChannelMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }

    if (ChannelMask == 0) {
      continue;
    }

    for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
      if (MarginParam == WrDqsT) {
        continue;
      }

      if (MarginParam == RdT) {
        Outputs->DQPat = RdRdTA;
      } else if (MarginParam == RdV) {
        Outputs->DQPat = BasicVA;
      }
      if ((MarginParam == RdV) || (MarginParam == WrV)) {
        MaxMargin = GetMaxPossibleVrefOffset (MrcData, MarginParam);
      } else if ((MarginParam == RdT) || (MarginParam == WrT)) {
        MaxMargin = GetMaxPossibleTimingOffset (MrcData, MarginParam);
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Unexpected paramter %u in MrcRetrainMarginCheck\n", MaxMargin);
      }
      Status = MrcGetBERMarginCh (
        MrcData,
        LastMargins,
        ChannelMask,
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

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Margins\nParams: RdT\tWrT\tRdV\tWrV\n\tLft Rgt Lft Rgt Low Hi  Low Hi");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nC%dR%d\t", Channel, Rank);
      for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
        if (MarginParam == WrDqsT) {
          continue;
        }

        LastResultParam     = GetMarginResultType (MarginParam);
        RetrainMarginLimit  = MrcGetUpmPwrLimit (MrcData, MarginParam, RetrainLimit) / 10;
        MrcCall->MrcSetMemWord (MinEdgeMargin, MAX_EDGES, (UINT16) (~0));

        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          CurrentMargin       = (UINT16) LastMargins[LastResultParam][Rank][Channel][0][Edge] / 10;
          MinEdgeMargin[Edge] = MIN (MinEdgeMargin[Edge], CurrentMargin);
          if ((CurrentMargin <= RetrainMarginLimit)) {
            Status =  mrcRetrain;
            if ((MarginParam == RdT) || (MarginParam == RdV)) {
              RdWrMarginFail[0] = TRUE;
            } else if ((MarginParam == WrT) || (MarginParam == WrV)) {
              RdWrMarginFail[1] = TRUE;
            }
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2d  %2d\t", MinEdgeMargin[0], MinEdgeMargin[1]);
        if ((RdWrMarginFail[0] == TRUE) && (RdWrMarginFail[1] == TRUE)) {
          Rank    = MAX_RANK_IN_CHANNEL;
          Channel = MAX_CHANNEL;
          break;
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");  // End of table

  if (Status == mrcRetrain) {
    // Loop is dependent on the order of MRC_MarginTypes.  If this changes, please ensure functionality
    // stays the same.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** Margin Limit Check Failed! ***\nNew Limits:\nParam\tUPM\tPWR");
    for (MarginParam = RdT; MarginParam <= WrV; MarginParam++) {
      if (((RdWrMarginFail[0] == FALSE) && ((MarginParam == RdT) || (MarginParam == RdV))) ||
          ((RdWrMarginFail[1] == FALSE) && ((MarginParam == WrT) || (MarginParam == WrV))) ||
          (MarginParam == WrDqsT)) {
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
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDebug          *Debug;
  UINT8             Channel;
  UINT8             RankMask;
  UINT8             Rank;
  UINT8             Dimm;
  BOOLEAN           Ddr4;
  UINT16            OdtWrite;
  UINT16            OdtNom;
  UINT16            OdtPark;
  UINT16            OdtCA;
  UINT16            DimmRon;
  UINT16            CpuOdt[MAX_CHANNEL];
  UINT16            CpuRon[MAX_CHANNEL];

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  //   DIMM ODT summary:
  //
  //           Ron     OdtWr   OdtNom  OdtPark (DDR4)
  //           Ron     OdtDQ   OdtCA           (LPDDR4)
  //   ---------------------------------------
  //   C0D0:   48      Hi-Z    48      80
  //   C0D1:   48      240     60      120
  //   ---------------------------------------
  //   C1D0:   48      48      34      34
  //   C1D1:   48      48      34      34
  //   ---------------------------------------
  //
  //   CPU Summary: Ron = 56, Read ODT = 109
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDIMM ODT summary:\n\tRon\t%s\n", Ddr4 ? "OdtWr\tOdtNom\tOdtPark" : "OdtDQ\tOdtCA");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "---------------------------------------\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (!ChannelOut->ValidRankBitMask) {
      continue;
    }
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      RankMask = DIMM_TO_RANK_MASK (Dimm);
      Rank = Dimm * 2;
      if ((RankMask & ChannelOut->ValidRankBitMask) == 0) {
        continue;
      }
      OdtNom   = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom,  FALSE, 0, FALSE);
      OdtPark  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtPark, FALSE, 0, FALSE);
      OdtCA    = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtCA, FALSE, 0, FALSE);
      OdtWrite = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr,   FALSE, 0, FALSE);
      DimmRon  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmRon,     FALSE, 0, FALSE);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\t%d\t", Channel, Dimm, DimmRon);
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
    CpuRon[Channel] = CalcCpuImpedance(MrcData, Channel, 0, 0, OptWrDS, TRUE, 0, FALSE, 0, 0);
    CpuOdt[Channel] = CalcCpuImpedance(MrcData, Channel, 0, 0, OptRdOdt, TRUE, 0, FALSE, 0, 0);
  } // for Channel

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "CPU Summary: Channel = %d Ron = %d, Read ODT = %d\n", Channel, CpuRon[Channel], CpuOdt[Channel]);
  }

#endif
}

/**
  This function approximates a non linear heaviside function using 5 linear curves.
  The curves are defined by 3 parameters:
    a - The curve's slope
    b - Intercept with y axis.
    x_max - The maximal x value to which curve parameters apply. i.e., for x < x1 a = a1, b = b1.
  It should select a balanced wr/rd operating point with respect to UPM

  @param[in]  MrcCall - MRC_FUNCTION pointer
  @param[in]  PostMar - Margin after training
  @param[in]  GoodPwrLimitPost - UPM limits for margins

  @retval  linear approximation function output
**/
UINT64
LinearApproximationTradeOff (
  IN MrcParameters *const MrcData,
  IN UINT32   PostMar,
  IN UINT16   GoodPwrLimitPost
)
{
  const  MRC_FUNCTION *MrcCall;
  static const UINT32  a[]      = { 10,    50,   200,   50,    10,          1 };
  static const INT32   b[]      = { 0,   -100, -1225,  650,  1450,       1810 };
  static const UINT32  x_max[]  = { 250,  750,  1250, 2000,  4000, 0xFFFFFFFF };

  UINT64    LocalResult;
  MrcInput  *Inputs;
  UINT32    a_LocalResult;
  INT32     b_LocalResult;
  UINT32    i;
  UINT64    Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Value   = PostMar;
  // Five Linear approximation optimization function value, y1=a1x+b1, 1000*y1=1000*a1*(LocalResult/UPM)+1000*b1, 1000*y1 = a1*((LocalResults*1000)/UPM)+1000*b1
  // UPM normalized with three digits after zero
  LocalResult   = MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (Value, 1000), GoodPwrLimitPost, NULL);
  b_LocalResult = 0;
  a_LocalResult = 0;
  for (i = 0; i < ARRAY_COUNT (x_max); i++) {
    if (LocalResult <= x_max[i]) {
      a_LocalResult = a[i];
      b_LocalResult = b[i];
      break;
    }
  }
  LocalResult = MrcCall->MrcDivU64x64(MrcCall->MrcMultU64x32(LocalResult, a_LocalResult), 100, NULL) + b_LocalResult;
  // MRC_DEBUG_MSG(&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "LinearApproximationTradeOff return value=%d \n", LocalResult);

  return (LocalResult);
}

#define DIMM_ODT_TEST_NUM         (2)
#define DIMM_ODT_RTT_WR_VALS_NUM  (5)
#define DIMM_ODT_MAX_VAL          (240)
#define DIMM_ODT_MAX_LINEAR_VAL   (1850)

/**
  This function implements DIMM ODT training based on LinearApproximationTradeOff function.
  Only RttWr is supported (1DPC).
  For DDR4 2DPC need to add RttNom / RttPark support.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
extern
MrcStatus
MrcDimmODTTraining (
  IN MrcParameters *const MrcData
)
{
  static const UINT16 DimmOdtRttWrValues[DIMM_ODT_RTT_WR_VALS_NUM] = { 120, 80, 60, 48, 40 };
  static const UINT8  TestList[DIMM_ODT_TEST_NUM] = { WrT, WrV };
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               OdtIndex;
  UINT8               MaxOdtIndex;
  UINT8               TestIndex;
  UINT8               Param;
  UINT8               BMap[9];
  BOOLEAN             Ddr4;
  UINT32              UpperLimit[DIMM_ODT_TEST_NUM];
  UINT32              LowerLimit[DIMM_ODT_TEST_NUM];
  UINT32              WidthX[MAX_CHANNEL][DIMM_ODT_TEST_NUM][DIMM_ODT_RTT_WR_VALS_NUM];
  UINT64              ScoreX[MAX_CHANNEL][DIMM_ODT_TEST_NUM][DIMM_ODT_RTT_WR_VALS_NUM];
  UINT64              TScoreX[MAX_CHANNEL][DIMM_ODT_RTT_WR_VALS_NUM];
  UINT64              MaxScoreX[MAX_CHANNEL];
  UINT32              BERStats[4];
  UINT32              LimitSum;
  UINT8               MaxMargin;
  UINT8               SubChMask;
  UINT8               RankMask;
  UINT8               ValidChBitMask;
  UINT8               ChMask;
  UINT8               LoopCount;
  UINT8               ResultType;
  BOOLEAN             DimmOdtProgrammed;
  INT16               PowerScore;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  ValidChBitMask = Outputs->ValidChBitMask;
  SubChMask = 3;
  LoopCount = 17;

  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) WidthX, sizeof (WidthX), 0);
  MrcCall->MrcSetMem ((UINT8 *) TScoreX, sizeof (TScoreX), 0);
  MrcCall->MrcSetMem ((UINT8 *) MaxScoreX, sizeof (MaxScoreX), 0);

  MaxOdtIndex = (Ddr4) ? (DIMM_ODT_RTT_WR_VALS_NUM - 3) : DIMM_ODT_RTT_WR_VALS_NUM;

  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  // Sweep ODT values, run tests and collect margins
  for (OdtIndex = 0; OdtIndex < MaxOdtIndex; OdtIndex++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      // Set the ODT value
      SetDimmParamValue (MrcData, Channel, Outputs->ValidRankMask, SubChMask, OptDimmOdtWr, DimmOdtRttWrValues[OdtIndex], TRUE);
    }
    // Recenter with the new ODT value
    DQTimeCentering1D (MrcData, ValidChBitMask, WrT, 0, 10, MRC_PRINTS_OFF, FALSE);
    DQTimeCentering1D (MrcData, ValidChBitMask, WrV, 0, 10, MRC_PRINTS_OFF, FALSE);

    SetupIOTestBasicVA (MrcData, ValidChBitMask, LoopCount, NSOE, 0, 0, 8);
    RankMask = 0xFF;  // Run stress on all ranks
    ChMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }

    for (TestIndex = 0; TestIndex < DIMM_ODT_TEST_NUM; TestIndex++) {
      Param = TestList[TestIndex];
      // get max for running margin func
      if ((Param == WrV) || (Param == RdV)) {
        MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
      } else {
        MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
      }
      MrcGetBERMarginByte (MrcData, Outputs->MarginResult, ChMask, RankMask, RankMask, Param, 0, BMap, 1, MaxMargin, 0, BERStats);
    }
    // Analyze result, keep track of overall best score
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      for (TestIndex = 0; TestIndex < DIMM_ODT_TEST_NUM; TestIndex++) {
        ResultType = GetMarginResultType (TestList[TestIndex]);
        UpperLimit[TestIndex] = 999; // set to really big number
        LowerLimit[TestIndex] = 999; // set to really big number
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Results from all ranks are stored in Rank0
          UpperLimit[TestIndex] = MIN (UpperLimit[TestIndex], Outputs->MarginResult[ResultType][0][Channel][Byte][0]);
          LowerLimit[TestIndex] = MIN (LowerLimit[TestIndex], Outputs->MarginResult[ResultType][0][Channel][Byte][1]);
        }
        LimitSum = (UpperLimit[TestIndex] + LowerLimit[TestIndex]);
        WidthX[Channel][TestIndex][OdtIndex] = UDIVIDEROUND (LimitSum, 10); // minimum cross byte
        ScoreX[Channel][TestIndex][OdtIndex] = LinearApproximationTradeOff (MrcData, LimitSum, MrcGetUpmPwrLimit (MrcData, TestList[TestIndex], UpmLimit));
        if (Inputs->PowerTrainingMode == MrcTmPower) {
          PowerScore = POWSCORE(DIMM_ODT_MAX_LINEAR_VAL, DIMM_ODT_MAX_VAL, DimmOdtRttWrValues[OdtIndex], 15);
          // MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Score=%lu\n", ScoreX[Channel][TestIndex][OdtIndex]);
          ScoreX[Channel][TestIndex][OdtIndex] -= PowerScore;
          // MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Score=%lu\n", ScoreX[Channel][TestIndex][OdtIndex]);
        }
        TScoreX[Channel][OdtIndex] = TScoreX[Channel][OdtIndex] + ScoreX[Channel][TestIndex][OdtIndex];
        MaxScoreX[Channel] = MAX (MaxScoreX[Channel], TScoreX[Channel][OdtIndex]);
      }
    } // Channel
  } // Dimm Odt


  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    // Print summary data
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nChannel %d\n  ODT\tWrT\tScore\tWrV\tScore\tTScore\n", Channel);
    DimmOdtProgrammed = FALSE;
    // Set the value only once and to lowest value in case several config give the same score
    for (OdtIndex = MaxOdtIndex - 1; OdtIndex != 0xFF; OdtIndex--) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %d\t", DimmOdtRttWrValues[OdtIndex]);
      for (TestIndex = 0; TestIndex < DIMM_ODT_TEST_NUM; TestIndex++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t%d\t", WidthX[Channel][TestIndex][OdtIndex], ScoreX[Channel][TestIndex][OdtIndex]);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", TScoreX[Channel][OdtIndex]);

      if ((TScoreX[Channel][OdtIndex] == MaxScoreX[Channel]) && !DimmOdtProgrammed) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " <-\n");
        // Set the Best value
        SetDimmParamValue (MrcData, Channel, Outputs->ValidRankMask, SubChMask, OptDimmOdtWr, DimmOdtRttWrValues[OdtIndex], TRUE);
        DimmOdtProgrammed = TRUE;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      }
    } // ODT
  } // Channel

  // Recenter with final ODT value
  DQTimeCentering1D (MrcData, ValidChBitMask, WrT, 0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, ValidChBitMask, WrV, 0, 10, MRC_PRINTS_OFF, FALSE);

  return mrcSuccess;
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

  if (Outputs->DdrType != MRC_DDR_TYPE_LPDDR4) {
    return mrcUnsupportedTechnology;
  }

  // Get searching limits
  //  OFF - out of range
  //  240 - out of range
  //  0 - 120
  //  1 - 80
  //  2 - 60
  //  3 - 48
  //  4 - 40

  Start = 0;  // 120  Ohm
  Stop = 4;   // 40   Ohm

  // Train CA ODT only
  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
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

  MrcCmdVoltageCentering(MrcData);
  MrcResetSequence(MrcData);

  return mrcSuccess;
}

/**
  This function implements Read Equalization (CTLE) training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcReadEQTraining (
  IN MrcParameters *const MrcData
  )
{
  static const UINT8  OptParams[] = { RdV, RdT };
  static const UINT8  TrainParam[] = { OptRxEq };
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Ridx;
  UINT8               Cidx;
  UINT8               LoopCount;
  UINT8               RankMask;
  UINT8               chBitMask;
  UINT8               ParamsPointer;
  UINT8               BMap[MAX_SDRAM_IN_DIMM];
  UINT32              BERStats[4];
  UINT8               MaxMargin;
  UINT32              Width[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][2][MAX_RX_EQ + 1][MAX_RX_EQ + 1];
  UINT32              Score[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][2][MAX_RX_EQ + 1][MAX_RX_EQ + 1];
  UINT32              TScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_RX_EQ + 1][MAX_RX_EQ + 1];
  UINT32              TScoreNew[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_RX_EQ + 1][MAX_RX_EQ + 1];

  UINT32              MaxScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8                Start;
  INT8                Stop;
  INT64               GetSetVal;
  BOOLEAN             ReCenterDone;
  BOOLEAN             ParamValueSet;
  BOOLEAN             Ddr4;
  UINT8               ResultType;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) Width, sizeof (Width) / sizeof (UINT32), 0);

  MrcCall->MrcSetMemDword ((UINT32 *) TScore, sizeof (TScore) / sizeof (UINT32), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) TScoreNew, sizeof(TScoreNew) / sizeof(UINT32), 0);

  MrcCall->MrcSetMemDword ((UINT32 *) Score, sizeof (Score) / sizeof (UINT32), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) MaxScore, sizeof (MaxScore) / sizeof (UINT32), 0);
  Status = mrcSuccess;

  if (Ddr4) {
    LoopCount = 17;
  } else {
    LoopCount = 16;
  }

  Start = OptParamLimitValue (MrcData, TrainParam[0], 0); // Start for R,C
  Stop  = OptParamLimitValue (MrcData, TrainParam[0], 1);
  MRC_DEBUG_ASSERT (Stop <= MAX_RX_EQ, Debug, "%s RxEq out of range\n", gErrString);

  // Search R, C and collect the margin data
  for (Ridx = Start, ReCenterDone = FALSE; Ridx <= Stop; Ridx++, ReCenterDone = FALSE) {
    for (Cidx = Start; Cidx <= Stop; Cidx++) {
      // Set R,C
      // Calculate right RxEq value
      if (Ridx == 0) {
        GetSetVal = 0;  // CTLE disabled
      } else {
        GetSetVal = 1 + Ridx * 2 + Cidx * 16;  // CTLE enable
      }
      MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxEq, WriteToCache, &GetSetVal);
      MrcFlushRegisterCachedData (MrcData);

      // Centering Rx eye, only for R values
      if (!ReCenterDone) {
        EarlyReadTimingCentering2D (MrcData, ERTC2D_NORMAL, FALSE);
        ReCenterDone = TRUE; // Recenter once per R value
      }
      // Data Margins
      SetupIOTestBasicVA(MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 0, 0, 8);

      // Collect margin data
      RankMask  = 0xFF;  // Run stress on all ranks
      chBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      }

      for (ParamsPointer = 0; ParamsPointer < ARRAY_COUNT (OptParams); ParamsPointer++) {
        // get max for running margin func
        if (OptParams[ParamsPointer] == RdV) {
          MaxMargin = GetMaxPossibleVrefOffset (MrcData, OptParams[ParamsPointer]);
        } else {
          MaxMargin = GetMaxPossibleTimingOffset (MrcData, OptParams[ParamsPointer]);
        }
        ResultType = GetMarginResultType (OptParams[ParamsPointer]);
        //MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Collect Margin per Byte  \n");
        // Run stress on all ranks, report results on rank0
        MrcGetBERMarginByte (MrcData, Outputs->MarginResult, chBitMask, RankMask, RankMask, OptParams[ParamsPointer], 0, BMap, 1, MaxMargin, 0, BERStats);
        // Calculate Score
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcChannelExist (Outputs, Channel))) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Width[Channel][Byte][ParamsPointer][Ridx][Cidx] = (Outputs->MarginResult[ResultType][0][Channel][Byte][0] + Outputs->MarginResult[ResultType][0][Channel][Byte][1]) / 10; // minimum cross byte
            if (Ridx == 0) {
              Width[Channel][Byte][ParamsPointer][Ridx][Cidx] = (Width[Channel][Byte][ParamsPointer][Ridx][Cidx] * 105) / 100; // Add 5% to default - CTLE disable
            }
            Score[Channel][Byte][ParamsPointer][Ridx][Cidx] = (UINT32) LinearApproximationTradeOff (MrcData, Width[Channel][Byte][ParamsPointer][Ridx][Cidx] * 10, MrcGetUpmPwrLimit (MrcData, OptParams[ParamsPointer], UpmLimit));
            TScore[Channel][Byte][Ridx][Cidx] += Score[Channel][Byte][ParamsPointer][Ridx][Cidx];
          } // Byte
        } // Channel
      } // Loop on Margin Params
      if (Ridx == 0) { // CTLE disabled
        break;
      }
    } // C loop
  } // R loop

  // Convolution 2D
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist(Outputs, Channel))) {
      continue;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MrcConvolution2D( &TScore[Channel][Byte][1][0],
                        &TScoreNew[Channel][Byte][1][0],
                        (INT16)Stop,
                        (INT16)Stop + 1,
                        (INT16)Stop + 1,
                        &LPFARR33[0][0],
                        3);
      TScoreNew[Channel][Byte][0][0] = TScore[Channel][Byte][0][0];
    }
  }

  // Print results
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist(Outputs, Channel))) {
      continue;
    }
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n\nSummary for Ch%d RdV/RdT/TotalScore (Convolution)\n", Channel);
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Byte \t\t");
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, " %d\t\t\t", Byte);
    }
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n R\tC\n");

    for (Ridx = Start; Ridx <= Stop; Ridx++) {
      for (Cidx = Start; Cidx <= Stop; Cidx++) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, " %d\t%d\t", Ridx, Cidx);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d/%d/%d \t", Width[Channel][Byte][0][Ridx][Cidx], Width[Channel][Byte][1][Ridx][Cidx], TScoreNew[Channel][Byte][Ridx][Cidx]);
          MaxScore[Channel][Byte] = MAX(MaxScore[Channel][Byte], TScoreNew[Channel][Byte][Ridx][Cidx]);
        }
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");
        if (Ridx == 0) {
          break;
        }
      }
    }
  }

  // Choose and set optimal CTLE value ( R and C )
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
        continue;
      }
      // Go over results and print the final table. If we reached max score set the value
      ParamValueSet = FALSE; // Set the value only once and to highest value in case several config give the same score
      for (Ridx = Start; Ridx <= Stop; Ridx++) {
        for (Cidx = Start; Cidx <= Stop; Cidx++) {
          if ((TScoreNew[Channel][Byte][Ridx][Cidx] == MaxScore[Channel][Byte]) && !ParamValueSet) {
            // Update CTLE value
            if (Ridx == 0) {
              GetSetVal = 0;  // CTLE disabled
            } else {
              GetSetVal = 1 + Ridx * 2 + Cidx * 16;  // CTLE enable
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u B%u R=%u C=%u\n", Channel, Byte, Ridx, Cidx);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, RxEq, WriteToCache, &GetSetVal);
            ParamValueSet = TRUE;
          }
          if (Ridx == 0) {
            break; // C = 0, CTLE disabled
          }
        } // C
      } // R
    } // Byte
  } // Channel

  MrcFlushRegisterCachedData (MrcData);

  // Recenter RdT / RdV
  ReadVoltageCentering2D (
    MrcData,
    Outputs->MarginResult,
    Outputs->ValidChBitMask,
    RdV,
    0,
    0,
    LoopCount - 2,
    0,
    MRC_PRINTS_OFF
  );

  DataTimeCentering2D (
    MrcData,
    Outputs->MarginResult,
    Outputs->ValidChBitMask,
    RdT,
    0, // EnPerBit,
    0, // EnRxDutyCycle
    0, // ResetPerBit
    LoopCount - 2,
    0,  // En2D
    MRC_PRINTS_OFF
  );
  Outputs->SenseAmpRetrain = TRUE;
  return Status;
}


/**
  This function Sets and Prints Write EqDs Best results that are calculated in WriteEqDs training.

  @param[in] MrcData - Include all MRC global data.
  @param[in] BestScore - Array of BestScore results per channel/byte.
  @param[in] BestWrDs - Array of BestWrDs results per channel/byte.
  @param[in] BestTxEq - Array of BestTxEq results per channel/byte.
  @retval None
**/
void
SetAndPrintWriteEqDsBestResults (
  IN    MrcParameters *const MrcData,
  IN    UINT64    BestScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN    INT16     BestWrDs[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN    INT32     BestTxEq[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  UINT8               Channel;
  UINT8               Byte;
  INT64               GetSetVal;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\tByte\tBestScore\tBestTxEq\tBestWrDs\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t%d\t%ld\t\t0x%02X\t\t%d\n", Channel, Byte, BestScore[Channel][Byte], BestTxEq[Channel][Byte], BestWrDs[Channel][Byte]);
      UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSUpCoarse, BestWrDs[Channel][Byte], TRUE);
      UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDnCoarse, BestWrDs[Channel][Byte], TRUE);
      GetSetVal = (INT64) BestTxEq[Channel][Byte];
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, TxEq, WriteCached, &GetSetVal);
    }
  }
  // Re-center with final results
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrT, 0, 10, MRC_PRINTS_OFF, FALSE);
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
#define WrDsNum   (8)
#define TxEqNum   (5)

  const MrcInput      *Inputs;
  static const UINT8  OptParams[] = { WrV,WrT };
  const MRC_FUNCTION  *MrcCall;
  static const INT32  TxEqVal[TxEqNum] = { 0x3F, 0x3C, 0x3A, 0x37, 0x35 };
  static const INT16  WrDsVal[WrDsNum] = { -4, -3, -2, -1, 0, 1, 2, 3 };
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               ChMask;
  UINT8               RankMask;
  UINT8               ParamsPointer;
  UINT8               MaxMargin;
  UINT32              CurrentMargin;
  UINT32              BERStats[4];
  UINT8               BMap[MAX_SDRAM_IN_DIMM];
  UINT64              Score;
  UINT64              BestScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               BestWrDs[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               BestTxEq[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16              TotalScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][WrDsNum][TxEqNum];
  UINT32              ArrayCalc[WrDsNum][TxEqNum];
  UINT32              NewArrayCalc[WrDsNum][TxEqNum];
  UINT8               TxEqValind;
  UINT8               WrDsValind;
  UINT8               LoopCount;
  BOOLEAN             Optimize;
  UINT8               ResultType;
  INT64               GetSetVal;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  ChMask  = Outputs->ValidChBitMask;
  RankMask = Outputs->ValidRankMask;

  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestScore, sizeof (BestScore), 0);
  Optimize = TRUE;
  LoopCount = 17;

  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxEq\tWrDs");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tCh%dB%d\t", Channel, Byte);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
       MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tWrV\tWrT ");
    }
  }

  for (WrDsValind = 0; WrDsValind < WrDsNum; WrDsValind++) {
    for (TxEqValind = 0; TxEqValind < TxEqNum; TxEqValind++) {
      GetSetVal = (INT64) TxEqVal[TxEqValind];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDnCoarse, WrDsVal[WrDsValind], TRUE);
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSUpCoarse, WrDsVal[WrDsValind], TRUE);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, TxEq, WriteCached, &GetSetVal);
        }
      } // Channel

      // Perform centering
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrV, 0, 10, MRC_PRINTS_OFF, FALSE);
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, WrT, 0, 10, MRC_PRINTS_OFF, FALSE);

      SetupIOTestBasicVA (MrcData, ChMask, LoopCount, NSOE, 0, 0, 8);

      RankMask = 0xff; // stress all ranks
      ChMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      }

      for (ParamsPointer = 0; ParamsPointer < ARRAY_COUNT (OptParams); ParamsPointer++) {
        // get max for running margin func
        if (OptParams[ParamsPointer] == WrV) {
          MaxMargin = GetMaxPossibleVrefOffset (MrcData, OptParams[ParamsPointer]);
        } else {
          MaxMargin = GetMaxPossibleTimingOffset (MrcData, OptParams[ParamsPointer]);
        }
        MrcGetBERMarginByte (MrcData, Outputs->MarginResult, ChMask, RankMask, RankMask, OptParams[ParamsPointer], 0, BMap, 1, MaxMargin, 0, BERStats);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n0x%02X\t%3d", TxEqVal[TxEqValind], WrDsVal[WrDsValind]);

      // Analyses
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcChannelExist (Outputs, Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Score = 0;
          for (ParamsPointer = 0; ParamsPointer < ARRAY_COUNT (OptParams); ParamsPointer++) {
            ResultType = GetMarginResultType(OptParams[ParamsPointer]);
            CurrentMargin = Outputs->MarginResult[ResultType][0][Channel][Byte][0] + Outputs->MarginResult[ResultType][0][Channel][Byte][1];
            Score += LinearApproximationTradeOff (MrcData, CurrentMargin, MrcGetUpmPwrLimit (MrcData, OptParams[ParamsPointer], UpmLimit));
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", CurrentMargin);
          }
          TotalScore[Channel][Byte][WrDsValind][TxEqValind] = (UINT16)Score;
          if (BestScore[Channel][Byte] < Score) {
            BestScore[Channel][Byte] = Score;
            BestTxEq[Channel][Byte] = TxEqVal[TxEqValind];
            BestWrDs[Channel][Byte] = WrDsVal[WrDsValind];
          }
        }
      }
    } // TxEqValind
  } // WrDsValind

  if (!Optimize) {
    //Set results
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\n");
    SetAndPrintWriteEqDsBestResults (MrcData, BestScore, BestWrDs, BestTxEq);
  } else {
    MrcCall->MrcSetMem ((UINT8 *) BestScore, sizeof (BestScore), 0);
    MrcCall->MrcSetMem ((UINT8 *) BestTxEq, sizeof (BestTxEq), 0);
    MrcCall->MrcSetMem ((UINT8 *) BestWrDs, sizeof (BestWrDs), 0);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nC%d B%d \n", Channel,  Byte);
        for (WrDsValind = 0; WrDsValind < WrDsNum; WrDsValind++) {
          for (TxEqValind = 0; TxEqValind < TxEqNum; TxEqValind++) {
            ArrayCalc[WrDsValind][TxEqValind] = TotalScore[Channel][Byte][WrDsValind][TxEqValind];
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%5d ", ArrayCalc[WrDsValind][TxEqValind]);
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }

        MrcCall->MrcSetMem ((UINT8 *) NewArrayCalc, sizeof (NewArrayCalc), 0);
        MrcConvolution2D( &ArrayCalc[0][0],
                          &NewArrayCalc[0][0],
                          WrDsNum,
                          TxEqNum,
                          TxEqNum,
                          &LPFARR33[0][0],
                          3);

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nNew Matrix C%d B%d \n", Channel,  Byte);
        for (WrDsValind = 0; WrDsValind < WrDsNum; WrDsValind++) {
          for (TxEqValind = 0; TxEqValind < TxEqNum; TxEqValind++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%5d ", NewArrayCalc[WrDsValind][TxEqValind]);
            if (BestScore[Channel][Byte] < NewArrayCalc[WrDsValind][TxEqValind]) {
              BestScore[Channel][Byte] = NewArrayCalc[WrDsValind][TxEqValind];
              BestTxEq[Channel][Byte] = TxEqVal[TxEqValind];
              BestWrDs[Channel][Byte] = WrDsVal[WrDsValind];
            }
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        }
      }
    }

    // Set new  results
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nOptimized Results\n");
    SetAndPrintWriteEqDsBestResults (MrcData, BestScore, BestWrDs, BestTxEq);
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
    0x3,
    0xF,
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

typedef struct
{
  UINT16  OptLastParams[2];
  UINT64  Score;
} ReadAmpData;

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
  static const UINT8  OptParams[] = { RdV, RdT };
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  const MrcInput      *Inputs;
  static const UINT8  IcompVal[MRC_ICOMP_NUM] = { 8,9,11,14 };
  static const UINT8  RcompVal[MRC_RCOMP_NUM] = { 8,10,12,14 };
  UINT8               IcompValind;
  UINT8               RcompValind;
  UINT8               MaxRcompValind;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               ChMask;
  UINT8               RankMask;
  UINT8               ParamsPointer;
  BOOLEAN             Lpddr4;
  UINT8               MaxMargin;
  UINT32              BERStats[4];
  UINT8               BMap[9];
  UINT32              ScoreRdV, ScoreRdT;
  UINT64              BestScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT64               BestIcomp[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT64               BestRcomp[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  ReadAmpData         TotalScore[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MRC_ICOMP_NUM][MRC_RCOMP_NUM];
  INT64               DefaultValRcomp[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT64               DefaultValIcomp[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              ArrayCalc[MRC_ICOMP_NUM][MRC_RCOMP_NUM];
  UINT32              NewArrayCalc[MRC_ICOMP_NUM][MRC_RCOMP_NUM];
  UINT8               LoopCount;
  MrcDdrType          DdrType;
  INT64               SelectedIcompVal;
  INT64               SelectedRcompVal;
  UINT8               ResultType;
  INT16               PowerScore;
  INT16               AdditionalMargin;

  LoopCount   = 15;
  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MrcCall     = Inputs->Call.Func;
  ChMask      = Outputs->ValidChBitMask;
  RankMask    = Outputs->ValidRankMask;
  DdrType     = Outputs->DdrType;
  IcompValind = 0;
  IcompValind = 0;

  Lpddr4 = (DdrType == MRC_DDR_TYPE_LPDDR4);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) DefaultValIcomp, sizeof(DefaultValIcomp), 0);
  MrcCall->MrcSetMem ((UINT8 *) DefaultValRcomp, sizeof(DefaultValRcomp), 0);

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    BMap[Byte] = Byte;
  }

  // In DDR4 we run only on Icomp but we use the same structures both for Lp and DDR4
  MaxRcompValind = (Lpddr4) ? MRC_RCOMP_NUM : 1;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (Lpddr4) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasRComp, ReadCached, &DefaultValRcomp[Channel][Byte]);
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasIComp, ReadCached, &DefaultValIcomp[Channel][Byte]);
    } // Byte
  } // Channel

  for (IcompValind = 0; IcompValind < MRC_ICOMP_NUM; IcompValind++) {
    SelectedIcompVal = IcompVal[IcompValind];
    for (RcompValind = 0; RcompValind < MaxRcompValind; RcompValind++) {
      SelectedRcompVal = RcompVal[RcompValind];

      if (Lpddr4) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxBiasRComp, WriteToCache, &SelectedRcompVal);
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxBiasIComp, WriteToCache, &SelectedIcompVal);
      MrcFlushRegisterCachedData (MrcData);

      // Perform centering
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, 0, 10, MRC_PRINTS_OFF, FALSE);
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, 0, 10, MRC_PRINTS_OFF, FALSE);
      DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV,  0, 10, MRC_PRINTS_OFF, FALSE);
      SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 0, 0, 8);

      RankMask = 0xFF;  // Run stress on all ranks
      ChMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
      }

      for (ParamsPointer = 0; ParamsPointer < ARRAY_COUNT (OptParams); ParamsPointer++) {
        if (OptParams[ParamsPointer] == RdV) {
          MaxMargin = GetMaxPossibleVrefOffset (MrcData, OptParams[ParamsPointer]);
        } else {
          MaxMargin = GetMaxPossibleTimingOffset (MrcData, OptParams[ParamsPointer]);
        }
        MrcGetBERMarginByte (MrcData, Outputs->MarginResult, ChMask, RankMask, RankMask, OptParams[ParamsPointer], 0, BMap, 1, MaxMargin, 0, BERStats);
      } //ParamsPointer

      // Analyses
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcChannelExist (Outputs, Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Calcultae Margin/Score Per Channel Per Byte
          ResultType        = GetMarginResultType(OptParams[0]);
          AdditionalMargin  = 0;

          // check if need to add +40 for margin in case of default and NO POWER score.
          if (Inputs->PowerTrainingMode == MrcTmMargin)
          {
            // DDR4
            DefaultValRcomp[Channel][Byte] = (Lpddr4) ? DefaultValRcomp[Channel][Byte] : RcompVal[RcompValind];
            if ((IcompVal[IcompValind] == DefaultValIcomp[Channel][Byte]) && (RcompVal[RcompValind] == DefaultValRcomp[Channel][Byte]))
            {
              AdditionalMargin = 40;
            }
          }

          TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[0] = (UINT16)( Outputs->MarginResult[ResultType][0][Channel][Byte][0]  +
                                                                                           Outputs->MarginResult[ResultType][0][Channel][Byte][1]) + AdditionalMargin;
          ResultType = GetMarginResultType(OptParams[1]);
          TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[1] = (UINT16)( Outputs->MarginResult[ResultType][0][Channel][Byte][0]  +
                                                                                           Outputs->MarginResult[ResultType][0][Channel][Byte][1]) + AdditionalMargin;
          ScoreRdV = (UINT32)LinearApproximationTradeOff(MrcData,
                                                         (UINT32)TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[0],
                                                         MrcGetUpmPwrLimit(MrcData, OptParams[0], UpmLimit));
          ScoreRdT = (UINT32)LinearApproximationTradeOff(MrcData,
                                                         (UINT32)TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[1],
                                                         MrcGetUpmPwrLimit(MrcData, OptParams[1], UpmLimit));
          TotalScore[Channel][Byte][IcompValind][RcompValind].Score = (ScoreRdV * ScoreRdT) >> 10;

          // check if need power scale - (Total score / 2.5)
          if (Inputs->PowerTrainingMode == MrcTmPower) {
            PowerScore = POWSCORE_IRCOMP(IcompVal[IcompValind], RcompVal[RcompValind], 2, 5);
            TotalScore[Channel][Byte][IcompValind][RcompValind].Score -= PowerScore;
          }
        } // Byte
      } // Channel
    } //RcompValidInd
  } //IcompValidInd

  MrcCall->MrcSetMem ((UINT8 *) BestScore, sizeof (BestScore), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestIcomp, sizeof (BestIcomp), 0);
  MrcCall->MrcSetMem ((UINT8 *) BestRcomp, sizeof (BestRcomp), 0);

  // Convolution & Best Score
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist(Outputs, Channel))) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      for (IcompValind = 0; IcompValind < MRC_ICOMP_NUM; IcompValind++) {
        for (RcompValind = 0; RcompValind < MaxRcompValind; RcompValind++) {
          // copy data
          ArrayCalc[IcompValind][RcompValind]     = (UINT32)TotalScore[Channel][Byte][IcompValind][RcompValind].Score;
          NewArrayCalc[IcompValind][RcompValind]  = 0;
        } // RcompValind
      } // IcompValind

      MrcConvolution2D (&ArrayCalc[0][0],
                        &NewArrayCalc[0][0],
                        MRC_ICOMP_NUM,
                        MRC_RCOMP_NUM,
                        (UINT16) MaxRcompValind,
                        &LPFARR55[0][0],
                        5);

      for (IcompValind = 0; IcompValind < MRC_ICOMP_NUM; IcompValind++) {
        for (RcompValind = 0; RcompValind < MaxRcompValind; RcompValind++) {
          TotalScore[Channel][Byte][IcompValind][RcompValind].Score = (UINT32)NewArrayCalc[IcompValind][RcompValind];
          if (BestScore[Channel][Byte] < NewArrayCalc[IcompValind][RcompValind]) {
            BestScore[Channel][Byte] = NewArrayCalc[IcompValind][RcompValind];
            BestIcomp[Channel][Byte] = IcompVal[IcompValind];
            BestRcomp[Channel][Byte] = RcompVal[RcompValind];
          } // BestScore
        }
      }
    } // Byte
  } // channel

#ifdef MRC_DEBUG_PRINT
     // Print results
   for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
     if (!(MrcChannelExist(Outputs, Channel))) {
       continue;
     }
     MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\nSummary for Ch%d RdV/RdT/TotalScore (Convolution)\n", Channel);
     MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, Lpddr4 ? "Icomp \tRcomp \t" : "Icomp \t");
     for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
       MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Byte%d\t\t", Byte);
     }
     MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");
     for (IcompValind = 0; IcompValind < MRC_ICOMP_NUM; IcompValind++) {
       for (RcompValind = 0; RcompValind < MaxRcompValind; RcompValind++) {
         if (Lpddr4) {
           MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%3d \t%3d \t", (INT16)IcompVal[IcompValind], (INT16)RcompVal[RcompValind]);
         } else {
           MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%3d \t", (INT16)IcompVal[IcompValind]);
         }
         for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
           MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d/",  TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[0]);
           MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d/",  TotalScore[Channel][Byte][IcompValind][RcompValind].OptLastParams[1]);
           MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", TotalScore[Channel][Byte][IcompValind][RcompValind].Score);
         }
         MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");
       }
     }
   }
#endif // MRC_DEBUG_PRINT

    //Print Set new  results
#ifdef MRC_DEBUG_PRINT
   MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nNew Results\n");
   if (Lpddr4) {
     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\tByte\tBestScore\tBestIcomp\tBestRcomp\tDefaultIcomp\tDefaultRcomp\n");
   } else {
     MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\tByte\tBestScore\tBestIcomp\tDefaultIcomp\n");
   }
#endif //MRC_DEBUG_PRINT
   for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
     if (!(MrcChannelExist (Outputs, Channel))) {
       continue;
     }
     for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
       MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasIComp, WriteToCache, &BestIcomp[Channel][Byte]);
       if (Lpddr4) {
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t%d\t%ld\t\t%u\t\t%u\t\t%u\t\t%u\n", Channel, Byte, BestScore[Channel][Byte], (UINT8)BestIcomp[Channel][Byte], (UINT8)BestRcomp[Channel][Byte], (UINT8)DefaultValIcomp[Channel][Byte], (UINT16)DefaultValRcomp[Channel][Byte]);
         MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasRComp, WriteToCache, &BestRcomp[Channel][Byte]);
       } else {
         MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t%d\t%ld\t\t%ld\t\t%ld\n", Channel, Byte, BestScore[Channel][Byte], BestIcomp[Channel][Byte], DefaultValIcomp[Channel][Byte]);
       }
     }//Byte
   }//Channel

  MrcFlushRegisterCachedData (MrcData);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, 0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, 0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV,  0, 10, MRC_PRINTS_OFF, FALSE);

  Outputs->SenseAmpRetrain = TRUE;

  return mrcSuccess;
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

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,         // Channels
    0xF,         // Ranks
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

  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV,  0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, 0, 10, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, 0, 10, MRC_PRINTS_OFF, FALSE);
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
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut  *IntCmdTiming;
  UINT32              (*MarginByte)[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32              BERStats[4];
  UINT32              CmdPiCodeIdx;
  UINT16              SaveMargin[MAX_MARGINS_TRADEOFF][MAX_OPT_POINTS][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16              PostMargin[MAX_MARGINS_TRADEOFF][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8               Test;
  UINT16              MinEye;
  UINT16              Margins[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS]; // TestParam X 24 Comp Points
  UINT16              UpmLimits[MAX_TRADEOFF_TYPES];
  UINT16              PwrLimits[MAX_TRADEOFF_TYPES];
  INT16               Best;
  UINT8               OptimizationMode;
  UINT8               ResultType;
  UINT8               AveN;
  UINT8               Ave2DXDim;
  UINT8               Ave2DXLim;
  UINT8               MarginStart;
  INT8                RxEqMarginLength;
  UINT8               ChBitMask;
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
  BOOLEAN             Lpddr;
  UINT8               OptIdx;
  MrcPower            BytePower;
  BOOLEAN             EnBer;
  UINT16              Margin;
  BOOLEAN             IgnoreUpmPwrLimit;
  MrcDdrType          DdrType;
  UINT16              MinChByte;
  BOOLEAN             GlobalParam;
  BOOLEAN             UpdateHost;
  CH0_SC0_CR_CADB_CFG_STRUCT  CadbConfig;
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
  ControllerOut       = &Outputs->Controller[0];
  IntOutputs          = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut    = &IntOutputs->Controller[0];
  MarginByte          = &Outputs->MarginResult;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  DdrType             = Outputs->DdrType;
  Lpddr               = (DdrType == MRC_DDR_TYPE_LPDDR4);
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
  MrcCall->MrcSetMem ((UINT8 *) &BytePower, sizeof (BytePower), 0);
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
    SetupIOTestStatic (MrcData, ChannelMask, LoopCount, NSOE, 0, 0, 4, Pattern);
    IgnoreUpmPwrLimit = TRUE;
  } else if (PatType == BasicVA){
    // For all other training params use regular VA pattern
    SetupIOTestBasicVA(MrcData, ChannelMask, LoopCount, NSOE, 0, 0, 8); // Set test to all channels.
  } else {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Unknown pattern in TrainDDROptParam %u \n", PatType);
    return;
  }
  if (RdRd2Test != 0) {
    Outputs->DQPat = RdRd2Test;
  }

  // Select All Ranks for REUT test
  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((0x1 << Channel) & ChannelMask)) {
      continue;
    }

    ChannelOut      = &ControllerOut->Channel[Channel];
    localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;

    // Use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    ChBitMask |= SelectReutRanks (MrcData, Channel, localR[Channel], FALSE, 0);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "reut ranks ChBitMask %x Local ranks=%x\n", ChBitMask,localR[Channel]);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((0x1 << Rank) & localR[Channel]) {
        FirstRankPerCh[Channel] = Rank;
        break;
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
  for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
    if ((OptParam[OptIdx] != OptDimmOdt) && (OptParam[OptIdx] != OptDimmOdtWr) && (OptParam[OptIdx] != OptDimmRon) && (OptParam[OptIdx] != OptDimmOdtCA) &&
      (OptParam[OptIdx] != OptClkTco) && (OptParam[OptIdx] != OptCmdSComp) && (OptParam[OptIdx] != OptCmdSCompOffset) &&
      (OptParam[OptIdx] != OptCmdDS) && (OptParam[OptIdx] != OptCmdTxEq)) {
      NumBytes = (UINT8) Outputs->SdramCount; // if one of param is per byte store per byte
    }
    if ((OptParam[OptIdx] == OptCmdSComp) || (OptParam[OptIdx] == OptCmdSCompOffset) || (OptParam[OptIdx] == OptCmdDS) || (OptParam[OptIdx] == OptCmdTxEq) ||
      (OptParam[OptIdx] == OptDimmOdtCA)) {
      IgnoreUpmPwrLimit = TRUE;
    }

    // Calculate Start/Stop Point for Comp Optimization
    // For TcoComp avoid Reserved comps as it isn't really compensated
    CPUComp = ((OptParam[OptIdx] == OptWrDS) || (OptParam[OptIdx] == OptWrDSUpCoarse)|| (OptParam[OptIdx] == OptWrDSDnCoarse)|| (OptParam[OptIdx] == OptRdOdt) ||
               (OptParam[OptIdx] == OptSComp));
    if (CPUComp) {
      if (OptParam[OptIdx] == OptSComp) {
        MaxComp = 31;
      } else {
        MaxComp = 63;
      }
      CurrentComp = GetCompCode (MrcData, OptParam[OptIdx], 2);
      if ((OptParam[OptIdx] == OptWrDSUpCoarse) || (OptParam[OptIdx] == OptWrDSDnCoarse)) {
        MaxComp /= 4;
        ReservedComp = DIVIDEROUND (ReservedComp, 4);
      }
      Delta = CurrentComp - ReservedComp + Start[OptIdx];
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Start[OptIdx] -= Delta;
      }

      Delta = MaxComp - CurrentComp - ReservedComp - Stop[OptIdx];
      if (Delta < 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "------------> warning offset range is clipped by %d\n", Delta);
        Stop[OptIdx] += Delta;
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
       NeedForceComp = TRUE;
    } else if ((OptParam[OptIdx] == OptCmdSComp) || (OptParam[OptIdx] == OptCmdTxEq) || (OptParam[OptIdx] == OptCmdDS) || (OptParam[OptIdx] == OptCmdSCompOffset)) {
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
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LenMargin = %d, Test LoopCount = %d\n",LenMargin, LoopCount);
  }
  //Setup the Execute Margin Test
  for (Test = 0; Test < NumTests; Test++) {
    Param = TestList[Test]; // tl[0]=4 tl[1]=1
    if ((Param == CmdT) || (Param == CmdV)) {
      SetupIOTestCADB (MrcData, ChannelMask, LoopCount, NSOE, 1, 0);
      IncEnds = 1;
    }
    ResultType      = GetMarginResultType (Param); // rxv=0 rxt=1
    // Assign to last pass margin results by reference
    // get lowest margin from all ch/rankS/byte save in FirstRank
    GetMarginByte (MrcData, Outputs->MarginResult, Param, FirstRank, RankMask);
    // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- FirstRank = %d ResultType=%d Param=%d ranks=0x%x\n", FirstRank,ResultType,Param,RankMask);
    // Calculate the MaxMargin for this test
    if ((Param == WrV) || (Param == WrFan3) || (Param == WrFan2) ||
        (Param == RdV) || (Param == RdFan3) || (Param == RdFan2) || (Param == CmdV)) {
      MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
    } else {
      MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
    }
    if (IgnoreUpmPwrLimit) {
      // Set Upm / Power limits to maximal search region
      UpmLimits[Test] = 20 * MaxMargin;
      PwrLimits[Test] = 20 * MaxMargin;
    } else {
      UpmLimits[Test] = MrcGetUpmPwrLimit(MrcData, Param, UpmLimit);
      PwrLimits[Test] = MrcGetUpmPwrLimit(MrcData, Param, PowerLimit);
    }
    MaxMargin = MIN(MaxMargin, (UINT8)(PwrLimits[Test] / 20));

    // Start Execute Margin Test, Loop Through all Comp Codes
    for (Index = 0; Index < LenMargin; Index ++) {
      // Continue accordingly to GridMode
      if (GetParamsXYZ (MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen)) { // return ParamOff[param]
        continue;
      }
      for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
        GlobalParam = (OptParam[OptIdx] == OptTxTco) || (OptParam[OptIdx] == OptClkTco) || (OptParam[OptIdx] == OptCmdSComp) || (OptParam[OptIdx] == OptCmdDS);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((0x1 << Channel) & ChBitMask)) {
            continue;
          }
          UpdateHost = ((Lpddr) && ((OptParam[OptIdx] == OptRdOdt) || (OptParam[OptIdx] == OptRdOdtUp) || (OptParam[OptIdx] == OptRdOdtDn)));
          ChannelOut = &ControllerOut->Channel[Channel];
          for (Byte = 0; Byte < NumBytes; Byte++) {
            if (!SkipOptUpdate) {
              // Change OpParam offset for all ch/byte/LocalR
              // Note: When using multi OptParams need to take care that one is not overwritten
              //       by the other in UpdateOptParamOffset routine (because UpdateHost=0).
              // Note: Some are limited in range inside e.g: RdOdt +15:-16
              UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], UpdateHost);
            }
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--Channel=%d, localR[Channel]=%x Byte=%d OffsetComp=%d Off=%d\n",Channel,localR[Channel],Byte,OffsetComp,Off);
          }
        }
      }
      if (NeedForceComp) {
        ForceRcomp(MrcData);
      }

      for (Rep = 0; Rep < Repeats; Rep++) {
        // Run Margin Test - margin_1d with chosen param
        // run on all ranks but change param only for firstRank??
        EnBer = 1;

#ifndef LB_STUB_FLAG
        if (Param == CmdT) {
          if (Lpddr) {
            CmdLinearFindEdgesLpddr (MrcData, MrcIterationCmd, ChBitMask, RankMask, 0x1F, MRC_PRINTS_OFF); // Shift all CMD/CTL fubs in LP4, instead of CLK
          } else {
            CmdLinearFindEdges (MrcData, MrcIterationClock, ChBitMask, RankMask, 3, -64, 64, 6, 1, (INT8 *)NULL, TRUE, TRUE);
          }
          // Restore centered value
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if (MrcRankInChannelExist(MrcData, Rank, Channel)) {
                if (Lpddr) {
                  IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
                  ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 0), IntCmdTiming->CtlPiCode[0], 0);
                  ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 1), IntCmdTiming->CtlPiCode[1], 0);
                  for (CmdPiCodeIdx = 0; CmdPiCodeIdx < (MAX_COMMAND_GROUPS - 1); CmdPiCodeIdx++) {
                    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, (1 << CmdPiCodeIdx), IntCmdTiming->CmdPiCode[CmdPiCodeIdx], 0);
                  }
                } else {
                  ShiftPIforCmdTraining(MrcData, Channel, MrcIterationClock, 1 << Rank, 3, 0, 0);
                }
              }
            }
          }
        } else if (Param == CmdV) {
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
        } else {
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcGetBERMarginByte ChBitMask=%x FirstRank=%d Param=%d\n",ChBitMask, FirstRank, Param);
          MrcGetBERMarginByte(
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
        if ((Param == CmdT) || (Param == CmdV)) {
          MrcResetSequence(MrcData);
        }
#endif
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " finish MrcGetBERMarginByte \n");
        // Record Test Results
        MinChByte = MRC_UINT16_MAX;
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
                Margin = (UINT16) (*MarginByte)[ResultType][FirstRank][Channel][Byte][Edge];
                SaveMargin[Test][Index][Channel][Byte] += Margin;
              }
            } else if (Param == CmdT) {
              // For the case of CmdT we had previously performed centering of CMD Timing. If the margin is not centered then we apply a penalty to avoid this selection.
              SaveMargin[Test][Index][Channel][Byte] = 2 * MIN ((UINT16) (*MarginByte)[ResultType][FirstRankPerCh[Channel]][Channel][Byte][0],
                                                                (UINT16) (*MarginByte)[ResultType][FirstRankPerCh[Channel]][Channel][Byte][1]);
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
        if (GlobalParam) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              if (!((0x1 << Channel) & ChBitMask)) {
                continue;
              }
              if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
                continue;
              }
              // MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Ch%u Byte%u MinChByte = %u\n", Channel, Byte, MinChByte);
              MinChByte = MIN (MinChByte, SaveMargin[Test][Index][Channel][Byte]);
            }
            if ((Param == CmdT) || (Param == CmdV)) {
              break;  // Exit per-byte loop
            }
          }
          // MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "MinChByte = %u\n", MinChByte);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              if (!((0x1 << Channel) & ChBitMask)) {
                continue;
              }
              if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
                continue;
              }
              SaveMargin[Test][Index][Channel][Byte] = MinChByte;
            }
            if ((Param == CmdT) || (Param == CmdV)) {
              break;
            }
          }
        }
      }
    } // end of offset

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
      if ((Param == CmdT) || (Param == CmdV)) {
        // Disable CADB Deselects
        MrcSelectEngines (MrcData, 0, ChannelMask, Outputs->ValidSubChMask);
        CadbConfig.Data = 0;
        CadbConfig.Bits.CADB_MODE = 0;
        CadbConfig.Bits.CADB_TO_CPGC_BIND = 1;
        Cadb20ConfigRegWrite (MrcData, CadbConfig);
      }
  } // end of test list

  // Calculate the best value for every byte
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
      (OptParam[0] == OptClkTco) || (OptParam[0] == OptTxTco) || (OptParam[0] == OptCmdSComp) || (OptParam[0] == OptCmdSCompOffset) || (OptParam[0] == OptCmdDS)) {
          AveN = 1;
        } else if ((OptParam[0] == OptRxBias) || (OptParam[0] == OptTxTcoDqsP) || (OptParam[0] == OptTxTcoDqsN)) {
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
        MrcCall->MrcSetMem ((UINT8 *) &BytePower, sizeof (BytePower), 0);
        GetParamsXYZ(MrcData, ParamOff, OptParamLen, GridMode, Index, Start, OffLen);
        CalcOptPowerByte (MrcData, &BytePower, Channel, FirstRank, Byte, OptParam, ParamOff, OptParamLen, CurrentComp, 10);
        if (((OptParam[0] >= OptRdOdt) && (OptParam[0] <= OptRxCb)) || (OptParam[0] == OptDimmRon)) {
          Margins[NumTests][Index] = BytePower.RdPower;
        } else {
          Margins[NumTests][Index] = BytePower.WrPower;
        }
        OptPower[Channel][Index] = Margins[NumTests][Index]; //+= BytePower.TotalPwr; // sum all bytes.  @todo check if OptPower[Index]can be remove (for print)
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OptPower[%d][%d]: %d Power->WrPower: %d\n", Channel, Index, OptPower[Channel][Index], BytePower.TotalPwr);
      }

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

      GetParamsXYZ(MrcData, ParamOff, OptParamLen, GridMode, (UINT8) Best, Start, OffLen);
      if (!SkipOptUpdate) {
        for (OptIdx = 0; OptIdx < OptParamLen; OptIdx++ ) {
          UpdateOptParamOffset (MrcData, Channel, localR[Channel], Byte, OptParam[OptIdx], ParamOff[OptIdx], 1);
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

         (*MarginByte)[ResultType][0][Channel][Byte][0] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
         (*MarginByte)[ResultType][0][Channel][Byte][1] =
          SaveMargin[Test][Best][Channel][Byte] / 2;
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "best offset= %d ;byte=%d ;(*MarginByte)[ResultType][0][Channel][Byte][0] -%d (*MarginByte)[ResultType][0][Channel][Byte][1] -%d add=%d\n",(UINT8) (BestOff->Offset[Channel][Byte] - Start),Byte,(UINT16) (*MarginByte)[ResultType][0][Channel][Byte][0] , (*MarginByte)[ResultType][0][Channel][Byte][1],((UINT16) (*MarginByte)[ResultType][0][Channel][Byte][0] + (UINT16)(*MarginByte)[ResultType][0][Channel][Byte][1]));
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
    ForceRcomp(MrcData);
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
CalcSubChImpedance (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                SubCh
  )
{
  MrcOutput      *Outputs;
  MrcChannelOut  *ChannelOut;
  UINT8           ByteStart;
  UINT8           ByteEnd;
  UINT8           Byte;
  UINT16          SubChImpedance;
  UINT16          ByteImpedance;

  Outputs = &MrcData->Outputs;

  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  SubChImpedance = 0;
  ByteImpedance = 0;

  if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
    ByteStart = ChannelOut->ByteStart[SubCh];
    ByteEnd = ChannelOut->ByteEnd[SubCh];
    for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
      ByteImpedance = CalcCpuImpedance (MrcData, Channel, 0, Byte, OptRdOdt, FALSE, FALSE, FALSE, FALSE, 0);
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u.Sch%u.B%u - ByteImpedance %u\n", Channel, SubCh, Byte, ByteImpedance);
      SubChImpedance += ByteImpedance;
    }
    SubChImpedance /= (ByteEnd - ByteStart + 1);
  }

  return SubChImpedance;
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
  MrcOutput       *Outputs;
  UINT8           Channel;
  UINT8           SubCh;
  UINT8           NumSubChannels;
  UINT16          CpuImpedance;
  UINT16          SocOdt;

  Outputs = &MrcData->Outputs;
  // Debug   = &Outputs->Debug;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    CpuImpedance = 0;
    NumSubChannels = 0;
    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      NumSubChannels += 1;
      CpuImpedance += CalcSubChImpedance (MrcData, Channel, SubCh);
    }
    CpuImpedance /= NumSubChannels;
    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      SocOdt = MrcCheckSocOdtLpddr4 (MrcData, CpuImpedance);
      SetDimmParamValue (MrcData, Channel, 0xF, 1 << SubCh, OptDimmSocOdt, SocOdt, TRUE);
      // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u SubChannel %u CpuImpedance %u SocOdt %u\n", Channel, SubCh, CpuImpedance, SocOdt);

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
  MrcStatus                     Status;
  const MrcInput                *Inputs;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  UINT8                         *TestList;
  UINT8                         TestListNonLp[]  = { RdV, RdT };
  UINT8                         TestListSize;
  UINT8                         ScaleNonLp[]     = { 1, 2, 1, 0, 0 };
  UINT8                         *Scale;
  INT8                          Start;
  INT8                          Stop;
  UINT8                         OdtCodeMin;
  UINT8                         OdtCodeMax;
  INT8                          Delta;
  UINT16                        Rleg;
  INT8                          StatLegs;
  UINT8                         OdtLegsDis;
  INT8                          CurrentVref;
  UINT8                         CurrentCompDn;
  UINT8                         CurrentCompUp;
  OptOffsetChByte               BestOff;
  UINT8                         RdTATestType;
  UINT8                         OptParam[] = {OptRdOdt};
  UINT8                         TestListLpddr[] = { RdV, RdT, RcvEnaX };
  UINT8                         ScaleLpddr[]    = { 1, 2, 2, 1, 0 };
  BOOLEAN                       Lpddr;
  INT64                         GetSetVal;
#ifdef MRC_DEBUG_PRINT
  MrcChannelOut                 *ChannelOut;
  LPDDR4_MODE_REGISTER_22_TYPE  *Mr22Ptr;
  UINT16                        *MrPtr;
  UINT8                         Channel;
  UINT8                         Rank;
#endif

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;

  Lpddr = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Start = OptParamLimitValue(MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue(MrcData, OptParam[0], 1);
  // Find a start offset where we below 180ohm to protect against OS/US
  MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtUp, ReadUncached, &GetSetVal);
  CurrentCompUp       = (INT8) GetSetVal;
  MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
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

  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, ReadFromCache, &GetSetVal);
  OdtLegsDis          = (UINT8) GetSetVal;
  MrcGetSetDdrIoGroupController0 (MrcData, DqOdtVref, ReadFromCache, &GetSetVal);
  CurrentVref         = (INT8) GetSetVal;
  StatLegs            = 4 * 4; // we enable only 1/3 segment for odt @todo vtt/DT  change
  if (CurrentVref & 0x10) {
    CurrentVref -= 0x20; // 2's complement
  }

  Rleg  = CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, TRUE, 0, TRUE, CurrentVref, CurrentCompUp) * (StatLegs * (!OdtLegsDis) + CurrentCompUp);

  // Check Comp code limit on start and stop
  Delta = OdtCodeMin + Start;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> warning offset range is clipped by %d\n", Delta);
    Start -= Delta;
  }

  Delta = 63 - OdtCodeMax - Stop;
  if (Delta < 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------> warning offset range is clipped by %d\n", Delta);
    Stop += Delta;
  }

  if (Stop > (MAX_OPT_POINTS + Start)) {
    Stop = (INT8) (MAX_OPT_POINTS + Start); // MAX_OPT_POINTS offsets in the margin array.
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    " current code = %d OdtLegsDis = %d Rleg = %d CurrentVref = %d  Start = %d Stop = %d\n",
    CurrentCompUp,
    OdtLegsDis,
    Rleg,
    CurrentVref,
    Start,
    Stop
    );

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    TestListSize,
    Scale,
    NULL,
    &Start,
    &Stop,           // Stop
    OPT_PARAM_LOOP_COUNT + 2, // Loopcount increased from 15 to better match RMT margins
    1,              // Repeats
    0,              // NoPrint
    0,              // SkipOptUpdate
    RdTATestType,   // RdRd2Test
    0,              // GuardBand
    BasicVA         // PatType
    );

#ifdef MRC_DEBUG_PRINT
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        MrPtr = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR;
        Mr22Ptr = (LPDDR4_MODE_REGISTER_22_TYPE *)&MrPtr[mrIndexMR22];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u Rank%u Setting SocOdt %u\n", Channel, Rank, Lp4RzqValues[Mr22Ptr->Bits.SocOdt]);
      }
    }
  }
#endif // MRC_DEBUG_PRINT

  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV,  0, OPT_PARAM_LOOP_COUNT, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, 0, OPT_PARAM_LOOP_COUNT, MRC_PRINTS_OFF, FALSE);
  DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, 0, OPT_PARAM_LOOP_COUNT, MRC_PRINTS_OFF, FALSE);
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

  Start = OptParamLimitValue (MrcData, OptParam[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParam[0], 1);

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
  BOOLEAN         Lpddr4;
  UINT8           RankMask;
  UINT8           Rank;
  UINT8           Value;
  UINT8           Index;
  INT16           TempOff;
  UINT32          Offset;
  INT16           OffCode;
  INT16           OffMin;
  INT16           OffMax;
  MrcStatus       Status;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;


  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  ChannelOut    = &Outputs->Controller[0].Channel[Channel];
  GsmMode       = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;
  GsmMode      |= (OptParam == OptDefault) ? ForceWriteOffsetUncached : 0;


  if (OptParam == OptTxTco) {
    // Sweep TCO comp using step size of 2
    GetSetVal = 8 * Off;
  } else if (OptParam == OptClkTco) {
    // Sweep TCO comp using step size of 2
    GetSetVal = 2 * Off;
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
      (OptParam == OptWrDSUp) ||
      (OptParam == OptWrDSDn) ||
      (OptParam == OptWrDSUpCoarse) ||
      (OptParam == OptWrDSDnCoarse) ||
      (OptParam == OptRdOdt) ||
      (OptParam == OptRdOdtUp) ||
      (OptParam == OptRdOdtDn) ||
      (OptParam == OptSComp) ||
      // TCO Comp overrides
      (OptParam == OptClkTco) ||
      (OptParam == OptTxTcoDqsP) ||
      (OptParam == OptTxTcoDqsN) ||
      (OptParam == OptDefault)
    );
  if (Type) {
    if (OptParam == OptClkTco) {
      // Clk TCO Comp override
      MrcGetSetDdrIoGroupController0 (MrcData, TcoCompCodeClk, GsmMode, &GetSetVal);
      MrcGetSetDdrIoGroupController0 (MrcData, TcoCompCodeCmd, GsmMode, &GetSetVal);
      MrcGetSetDdrIoGroupController0 (MrcData, TcoCompCodeCtl, GsmMode, &GetSetVal);
    } else if (OptParam == OptTxTcoDqsP) {
      GetSetVal = (Off * 2);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, TxTcoDqsP, GsmMode, &GetSetVal);
    } else if (OptParam == OptTxTcoDqsN) {
      OffMin = -1;
      GetSetVal = (Off * 2);
      if (GetSetVal < OffMin) {  // bypass
        GetSetVal = 1;
        MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, TxTcoByPass, GsmMode, &GetSetVal);
      } else {
        MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, TxTcoDqsN, GsmMode, &GetSetVal);

        GetSetVal = 0;  // disable ByPass mode in case it enabled
        MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, TxTcoByPass, GsmMode, &GetSetVal);
      }

    } else {
      // Dq Comp offset
      if (OptParam == OptWrDS ||
        (OptParam == OptWrDSUp) ||
        (OptParam == OptWrDSDn)) {
        OffMin = -32;
        OffMax = 31;
      } else if ((OptParam == OptWrDSUpCoarse) ||
                 (OptParam == OptWrDSDnCoarse)) {
        OffMin = -8;
        OffMax = 7;
      } else if (OptParam == OptSComp) {
        OffMin = -17; // -17 for SR dis.
        OffMax = 15;
      } else {
        OffMin = -16;
        OffMax = 15;
      }

      if (Off > OffMax) {
        Off = OffMax;
      } else if (Off < OffMin) {
        Off = OffMin;
      }

      DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];

      if (OptParam == OptWrDS) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
      } else if (OptParam == OptRdOdt) {
        DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset    = Off;
        DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset  = Off;
      } else if (OptParam == OptSComp) {
        if (Off == -17) {
          // Just picked value outside SR range.
          GetSetVal = 1;
        } else {
          DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset = Off;
          GetSetVal = 0;
        }
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDqSlewDlyByPass, GsmMode, &GetSetVal);
      } else if (OptParam == OptWrDSDn) {
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = Off;
      } else if (OptParam == OptWrDSUp) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = Off;
      } else if (OptParam == OptWrDSDnCoarse) {
        DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset  = 4 * Off;
      } else if (OptParam == OptWrDSUpCoarse) {
        DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset    = 4 * Off;
      } else if (OptParam == OptRdOdtUp) {
        DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset    = Off;
      } else if (OptParam == OptRdOdtDn) {
        DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset  = Off;
      }
      Offset = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
      MrcWriteCR (MrcData, Offset, DdrCrDataOffsetComp.Data);
      if (UpdateHost) {
        ChannelOut->DataCompOffset[Byte] = DdrCrDataOffsetComp.Data;
      }
    }

    GetSetVal = 1;
    MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, GsmIocInternalClocksOn, ForceWriteCached, &GetSetVal);
    // Propagate new value and force comp update
    MrcGetSetDdrIoGroupController0(MrcData, GsmIocForceCmpUpdt, ForceWriteUncached, &GetSetVal);

    GetSetVal = 0;
    MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, GsmIocInternalClocksOn, ForceWriteCached, &GetSetVal);
    ForceRcomp(MrcData);
  }

  if ((Lpddr4) && ((OptParam == OptRdOdt) || (OptParam == OptRdOdtUp) || (OptParam == OptRdOdtDn))) {
    // Readjust SOC ODT for each change in RdOdt
    Lpddr4UpdateSocOdt (MrcData);
  }
  // Equalization Settings
  Type = ((OptParam == OptTxEq) || (OptParam == OptRxEq) || (OptParam == OptDefault));
  if (Type) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && ((Ranks & (MRC_BIT0 << Rank)))) {
        // TxEq[5:4] = Emphasize   = [4, 8, 12, 15] legs 3/2 seg? SKL : TODO
        // TxEq[3:0] = Deemphasize = [0:15] legs
        //(TxEq[3:0]%3 == 0) : off+
        if (OptParam == OptTxEq) {
          if (Inputs->CpuModel == cmICL_ULX_ULT) {
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
          // 15 Emphasize legs (not trained)
          OffCode = TempOff | TXEQFULLDRV;
          //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel=%d,Rank= %d update to %x \n",Channel,Rank,OffCode);
          GetSetVal = OffCode;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxEq, WriteCached, &GetSetVal);
        }
        // RxEQ[4:1] CR Decoding (pF/kOhm) SKL
        //            [2:1]
        //  [4:3]     0        1        2        3
        //     0      0.5/.15  0.5/0.25  0.5/0.5  0.5/1.0
        //     1      1.0/.15  1.0/0.25  1.0/0.5  1.0/1.0
        //     2      1.5/.15  1.5/0.25  1.5/0.5  1.5/1.0
        //     3      2.0/.15  2.0/0.25  2.0/0.5  2.0/1.0
        // [0] = CTLE Enabled with 20 Ohm bypass resistor.
        // Sweep = 0-16        if Sweep == 0, all bits [4:0] are 0
        //         all other Sweep values  [4:3] = ((Sweep-1)/4)  [2:0] = ((Sweep-1)%4)
        if (OptParam == OptRxEq) {
          Value = 0;
          if (Off <= 0) {
            Value = 0;
          } else {
            if (Off > 49) {
              Off = 49;
            }
            Value = (UINT8) ((((Off - 1) % 7 + 1) << 4) + ((((Off - 1) / 7) + 1) << 1) + 1);
          }
          GetSetVal = Value;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxEq, GsmMode, &GetSetVal);
        }

        if (OptParam == OptDefault) {
          GetSetVal = 0;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, GsmMode, &GetSetVal);
        }
      }
    }
  }
  // RxCb Amplifier BIAS
  if ((OptParam == OptRxCb) || (OptParam == OptDefault)) {
    if (Off > 7) {
      Off = 7;
    }

    if (Off < 0) {
      Off = 0;
    }

    if (OptParam == OptRxCb) {
      GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }

    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxCben, GsmMode, &GetSetVal);
  }
  // CMD Comp Settings
  if (OptParam == OptCmdSComp) {
    // For Cmd Slew Rate the Off is assumed to be the number of stages desired
    GetSetVal = Off;
    MrcGetSetDdrIoGroupController0 (MrcData, CmdSlewRate, GsmMode, &GetSetVal);
  } else if (OptParam == OptCmdSCompOffset) {
    OffMin = -16; // -17 for SR dis.
    OffMax = 15;
    if (Off > OffMax) {
      Off = OffMax;
    } else if (Off < OffMin) {
      Off = OffMin;
    }

    GetSetVal = Off;

    MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, CmdSCompOffset, GsmMode, &GetSetVal); // for DDR4

  } else if (OptParam == OptCmdDS) {
    GetSetVal = 48 + 4 * Off; // The search range of CmdDrvVref from 1/4 Vdd to 3/4 Vdd (48 : 134)
    MrcGetSetDdrIoGroupController0 (MrcData, CmdDrvVref, GsmMode, &GetSetVal);

  } else if (OptParam == OptCmdTxEq) {
    GetSetVal = Off;
    for (Index =0; Index< MRC_CMDTXEQ_GRP_MAX; Index ++){
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Index, CmdTxEq, GsmMode, &GetSetVal);   //program CMDA, CMB, CKE DDRCMDACH0_CR_DDRCRCMDCONTROLS_REG
    }
  }

  if (OptParam == OptDqDfeMode) {
    // DFE Mode
    if (Off < 20) {
      GetSetVal = Off / 5;
    } else {
      GetSetVal = 3;
    }
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, DqDfeDelayMode, GsmMode, &GetSetVal);

    // DqDfeDelay Coarse MSB 5:3
    if (Off < 20) {
      GetSetVal = (Off % 5) << 3;
    } else {
      GetSetVal = (Off - 15) << 3;
    }
    MrcGetSetDdrIoGroupSocket0  (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, MAX_BITS, DqDfeDelay, GsmMode, &GetSetVal);
  } else if (OptParam == OptDqDfeDly) {
    GetSetVal = Off;
    MrcGetSetDdrIoGroupSocket0  (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, MAX_BITS, DqDfeDelay, GsmMode, &GetSetVal);
  } else if (OptParam == OptDqDfeCoeff) {
    GetSetVal = Off;
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, DqDfeCoeff, GsmMode, &GetSetVal);
  }

  // RX Amplifier BIAS
  if ((OptParam == OptRxBias) || (OptParam == OptDefault)) {
    if (OptParam == OptRxBias) {
      GetSetVal = Off;
    } else {
      GetSetVal = 0;
    }
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmComplexRxBias, GsmMode, &GetSetVal);
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
    RankMask = 0xF;
    Status = GetDimmOptParamValues (MrcData, OptParam, &DimmOptParamVals, &NumDimmOptParamVals);
    if (Status == mrcSuccess) {
      Index = (UINT8) Off;
      if (OptParam == OptDimmOdtCA) {
        SetDimmParamValue (MrcData, Channel, Ranks & RankMask, ChannelOut->ValidSubChBitMask, OptParam, DimmOptParamVals[Index], 1);
      } else if (DimmOptParamVals != NULL){
        SetDimmParamValue (MrcData, Channel, Ranks & RankMask, ChannelOut->ValidSubChBitMask, OptParam, DimmOptParamVals[Index], UpdateHost);
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
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  INT64               GetSetVal;
  INT64               MaxVal;
  UINT8               Channel;
  UINT8               RankMaskCh;
  UINT8               RankMask;
  UINT8               ResultRank;
  BOOLEAN             RunDD;
  BOOLEAN             RunDR;
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
  CH0_CR_SC_PCIT_STRUCT  ScPcit;
  CH0_CR_SC_PCIT_STRUCT  ScPcitSave[MAX_CHANNEL];

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
  RankMask      = 0xF;
  ResultRank    = GetRankToStoreResults (MrcData, RankMask);
  Range         = 1;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (!ChannelOut->ValidRankBitMask) {
      continue;
    }

    RankMaskCh  = ChannelOut->ValidRankBitMask;
    RunDD       = RunDD || (ChannelOut->DimmCount == 2);
    RunDR       = RunDR || ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);
    RunDD       = 0;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Channel %d: RunDR = 0x%x, RunDD = 0x%x, RankMaskCh = 0x%x\n",
      Channel,
      RunDR,
      RunDD,
      RankMaskCh
      );

    // Use nominal values (previously programmed) +1 and -1 to test for Gear1.  Gear2 will need to do +2 and -2 with steps of 2.
    // Taking worst case of both channels.
    // Ideally the Cliff routine should support offset per channel or better make the param a real offset (not the abs value)
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, ReadFromCache, &GetSetVal);
    NomWR2RD_dr = MAX (NomWR2RD_dr, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, ReadFromCache, &GetSetVal);
    NomWR2RD_dd = MAX (NomWR2RD_dd, (UINT8) GetSetVal);

    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, ReadFromCache, &GetSetVal);
    NomRD2WR_dr = MAX (NomRD2WR_dr, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, ReadFromCache, &GetSetVal);
    NomRD2WR_dd = MAX (NomRD2WR_dd, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache, &GetSetVal);
    NomRD2RD_dr = MAX (NomRD2RD_dr, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, ReadFromCache, &GetSetVal);
    NomRD2RD_dd = MAX (NomRD2RD_dd, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, ReadFromCache, &GetSetVal);
    NomWR2WR_dr = MAX (NomWR2WR_dr, (UINT8) GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, ReadFromCache, &GetSetVal);
    NomWR2WR_dd = MAX (NomWR2WR_dd, (UINT8) GetSetVal);

    // Change PCIT to 0xFF
    // This allows proper tRDWR_dg stress without extra PRE/ACT cycles.
    Offset = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
    ScPcit.Data = MrcReadCR (MrcData, Offset);
    ScPcitSave[Channel] = ScPcit;
    ScPcit.Bits.PCIT = 0xFF;
    MrcWriteCR (MrcData, Offset, ScPcit.Data);
  } // for Channel

  if (Outputs->Gear2) {
    Range = 2;
    MinNomWR2WR_dr = MAX (NomWR2WR_dr - Range, 7); // 7 QClks
    MinNomWR2WR_dr = 2 * (DIVIDECEIL (MinNomWR2WR_dr, 2));
  } else {
    MinNomWR2WR_dr = MAX (NomWR2WR_dr - Range, DIVIDECEIL (7, 2)); // 7 QClks in DClks
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (!ChannelOut->ValidRankBitMask) {
      continue;
    }
    // Adjust initial values to be more relaxed so any detected failures are due to the parameter being tested.
    if (RunDR) {
      // Different Rank, Same DIMM
      MrcGetSetLimits (MrcData, GsmMctRDRDdr, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomRD2RD_dr + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, WriteToCache, &GetSetVal);
      MrcGetSetLimits (MrcData, GsmMctWRWRdr, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomWR2WR_dr + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, WriteToCache, &GetSetVal);

      MrcGetSetLimits (MrcData, GsmMctWRRDdr, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomWR2RD_dr + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, WriteToCache, &GetSetVal);
      MrcGetSetLimits (MrcData, GsmMctRDWRdr, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomRD2WR_dr + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, WriteToCache, &GetSetVal);
    }
    if (RunDD) {
      // Different DIMMs
      MrcGetSetLimits (MrcData, GsmMctWRRDdd, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomWR2RD_dd + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, WriteToCache, &GetSetVal);
      MrcGetSetLimits (MrcData, GsmMctRDWRdd, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomRD2WR_dd + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, WriteToCache, &GetSetVal);
      MrcGetSetLimits (MrcData, GsmMctRDRDdd, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomRD2RD_dd + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, WriteToCache, &GetSetVal);
      MrcGetSetLimits (MrcData, GsmMctWRWRdd, NULL, &MaxVal, NULL);
      GetSetVal = MIN ((UINT32) MaxVal, NomWR2WR_dd + RelaxBy);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, WriteToCache, &GetSetVal);
    }
    MrcFlushRegisterCachedData (MrcData);
    // Must update the XARB bubble injector when TAT values change
    SetTcBubbleInjector (MrcData, Channel);
  } // for Channel

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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
              ResultRank,
              RankMask,
              0
              );
    if (Status != mrcSuccess) {
      return mrcTurnAroundTimingError;
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
            ResultRank,
            RankMask,
            GuardBand
            );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTimingError;
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
            ResultRank,
            RankMask,
            GuardBand
            );
  if (Status != mrcSuccess) {
    return mrcTurnAroundTimingError;
  }

  // Restore PCIT value
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist(Outputs, Channel)) {
      continue;
    }
    Offset = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
    MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);
  }

  // Print out the end results of the training step in Table Format
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--- Final TA values ---\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tC%d", Channel);
  }
  for (TaTypeIdx = 0; TaTypeIdx < (sizeof (PrintGroups) / (sizeof (PrintGroups[0]))); TaTypeIdx++) {
    for (GroupIdx = 0; GroupIdx < (sizeof (PrintGroups[0]) / (sizeof (PrintGroups[0][0]))); GroupIdx++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s%s", TaString[TaTypeIdx], TypeStr[GroupIdx]);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        if (!ChannelOut->ValidRankBitMask) {
          continue;
        }
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, PrintGroups[TaTypeIdx][GroupIdx], ReadFromCache, &GetSetVal);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d", (UINT8) GetSetVal);
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
  IN UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
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
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcIntOutput      *MrcIntData;
  MrcStatus         Status;
  MRC_PATTERN_CTL   PatternCtl; // For 8 bit VA, this walks through each WDB pointer ~ 2X
  MRC_BG_BANK_PAIR  BankMappingSave[MAX_CHANNEL][MAX_BANKS];
  INT64             WrRdSg[MAX_CHANNEL];
  INT64             RdWrSg[MAX_CHANNEL];
  UINT32            BERStats[4];  // Track BER results
  UINT32            RankList;
  UINT32            Offset;
  UINT16            Margins[MAX_TESTS_OPT_PARAM_CLIFF][2][2][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];  // Tests X DR/DD x ClkPhases x Ch X Byte
  UINT16            NumCL;  // Number of cachelines per SubSeq
  UINT16            m;
  UINT16            ByteMask;
  UINT16            ByteFailMask[MAX_CHANNEL];  // Per ch mask indicating which bytes have failed
  UINT16            ByteDone;
  INT8              Inc;
  INT8              Off;
  INT8              Index;
  INT8              LastPass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];     // Lass Pass Value for off
  INT8              Begin;
  INT8              End;
  INT8              ChLastPass;
  INT8              ActualGuardBand;
  UINT8             Channel;
  UINT8             SubCh;
  UINT8             ChannelMask;
  UINT8             Byte;
  UINT8             Rank;
  UINT8             ChBitMask;
  UINT8             RankCount;
  UINT8             OrigRankCount;
  UINT8             ChBitMaskdd;
  UINT8             RankMaskCh;
  UINT8             GlobalRankMask;
  UINT8             drddPresent[2]; // [0]: ChBitMask for dr, [1]: ChBitMask for dd
  UINT8             CmdPat;
  UINT8             BMap[9];  // Needed for GetBERMarginByte function
  UINT8             MarginLimit;  // Need to change it to 20%of eye heigth
  UINT8             ResetDDR;
  UINT8             SelfRefresh;
  UINT8             offs[MAX_CHANNEL];
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
  UINT8             ChanSubChanMask;
  BOOLEAN           WriteVrefParam;
  BOOLEAN           DramVref;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           IsDual;
  BOOLEAN           ODT;
  BOOLEAN           PerByte;
  BOOLEAN           NotRankTraining;
  BOOLEAN           FindFirstPass;
#ifdef MRC_DEBUG_PRINT
  INT64             GetSetVal;
  INT8              ChLastPass1[MAX_CHANNEL];
#endif // MRC_DEBUG_PRINT
  UINT8             RepeatInitialTest;
  CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT  CpgcChSeqRankL2PMapping;
  CH0_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT           Cpgc2AddrSize;
//  REUT_CH_SEQ_CFG_0_STRUCT                         ReutChSeqCfg; // @todo <ICL> Update with CPGC 2.0 implementation
//  REUT_CH_SEQ_BASE_ADDR_WRAP_0_STRUCT ReutChSeqBaseAddrWrap;

  Inputs          = &MrcData->Inputs;
  MrcCall         = Inputs->Call.Func;
  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  MrcIntData      = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Status          = mrcSuccess;
  Ddr4            = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4          = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Done            = 0;
  drddPresent[0]  = 0;
  drddPresent[1]  = 0;
  MarginLimit     = 10;  // Drop of X% in margin means failure
  ResetDDR        = 1;
  SelfRefresh     = 0;
  WDBIncRate      = 13;
  NumCL           = (Lpddr4) ? 64 : 128;
  RepeatInitialTest = 4;  // Run initial RTL point 5 times

  MRC_DEBUG_ASSERT (NumTests <= MAX_TESTS_OPT_PARAM_CLIFF, Debug, "ERROR: too many tests passed into TrainDDROptParamCliff()\n");

  PatternCtl.IncRate  = 0;
  PatternCtl.DQPat    = BasicVA;
  PatternCtl.EnableXor = FALSE;
  PatternCtl.PatSource = MrcPatSrcDynamic;
  MrcCall->MrcSetMem ((UINT8 *) ByteFailMask, sizeof (ByteFailMask), 0);
  MrcCall->MrcSetMem (offs, sizeof (offs), 0);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMem ((UINT8 *) BankMappingSave, sizeof (BankMappingSave), 0);
  MrcCall->MrcCopyMem ((UINT8 *) &CpgcAddress, (UINT8 *) &CPGCAddressConst, sizeof (CpgcAddress));
  switch (OptParam) {
  case mcodts:
  case mcodtd:
    CpgcAddress.AddrIncOrder = CPGC20_BANK_2_ROW_COL_2_RANK;
    CpgcAddress.ColSizeBits = 3;
    NumCL           = 32;
    break;

  case rtl:
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

  ControllerOut   = &Outputs->Controller[0];
  GlobalRankMask = Outputs->ValidRankMask & RankMask;

  NotRankTraining = (OptParam == rtl);
  FindFirstPass   = (OptParam == rtl);  // FindFirstPass logic only works for RTL!
  ODT             = (OptParam == rdodtd) || (OptParam == wrodtd) || (OptParam == mcodtd) || (OptParam == mcodts);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nNotRankTraining = %u, ODT = %d\n", NotRankTraining, ODT);

  // Decide which channels need to be run and program NumCachelines and LC
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (ChannelOut->ValidRankBitMask) {
      ChannelMask = MRC_BIT0 << Channel;
      RankMaskCh  = ChannelOut->ValidRankBitMask;
      IsDual      = ((RankMaskCh & 0xC) == 0xC) || ((RankMaskCh & 0x3) == 0x3);

      // Continue if no ranks in this channel
      if ((RankMaskCh & RankMask) == 0) {
        continue;
      }

      if ((OptParamDDType[OptParam] & 0x2) && (ChannelOut->DimmCount == 2)) {
        drddPresent[1] |= ChannelMask; // dd parameter and channel has 2 DIMMs
      }

      if (((OptParamDDType[OptParam] & 0x1) && IsDual) || NotRankTraining) {
        drddPresent[0] |= ChannelMask; // dr parameter and channel has a dual rank
      }

      if (ODT && ((drddPresent[0] & (1 << Channel)) == 0)) {
        // ODT matters when Single rank
        // dr parameter and channel has a dual rank
        drddPresent[0] |= ChannelMask;
      }
    }
  }

  ChBitMask = drddPresent[1] | drddPresent[0]; // Chanel is present if it has either a dr or dd
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "drddPresent[0] = 0x%x, drddPresent[1] = 0x%x, ChBitMask = 0x%x\n",
    drddPresent[0],
    drddPresent[1],
    ChBitMask
    );

  MrcSelectEngines (MrcData, ChBitMask, 0, 0);
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChanSubChanMask = 0x%x\n", ChanSubChanMask);

  // There is nothing to optimize for this parameter
  if ((ChBitMask == 0) || (Stop <= Start)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChBitMask = %d, Start = 0x%x, Stop = 0x%x\n", ChBitMask, Start, Stop);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "No need to optimize TA, OptParam = %d\n", OptParam);
    return (Inputs->ExitOnFailure) ? mrcFail : mrcSuccess;
  }
  // Setup the REUT Test
  if ((OptParam == ddwr2rd) || (OptParam == drwr2rd)) {
    CmdPat = PatWrRdTA;
    Outputs->DQPat  = TurnAroundWR;
    // WrRdSg is a long delay.  Extend RdWrSg to cover the remaining WrRdSg delay so we get WrRdDr properly.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
         continue;
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDsg, ReadFromCache, &WrRdSg[Channel]);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, ReadFromCache, &RdWrSg[Channel]);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, WriteCached,   &WrRdSg[Channel]);
      // Must update the XARB bubble injector when TAT values change
      SetTcBubbleInjector (MrcData, Channel);
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

  // SOE=0, EnCADB=0, EnCKE=0, SubSeqWait=0
  if (OptParam == rtl) {
    SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, NSOE, 0, 0, 8);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }
  } else {
    SetupIOTest (MrcData, ChBitMask, CmdPat, NumCL, LoopCount, &CpgcAddress, NSOE, &PatternCtl, 0, 0, 0);
  }

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

  if ((Outputs->Gear2) && (OptParam != mcodts) && (OptParam != mcodtd) && (OptParam != rtl)) {
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
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MrcCall->MrcSetMem ((UINT8 *) &LastPass[Channel][0], Outputs->SdramCount, (UINT8) (Begin - ActualGuardBand));
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

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut  = &ControllerOut->Channel[Channel];
      RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
      // if nothing for this channel OR No Ranks in this channel
      if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
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

      if (FindFirstPass && (Index == 0)) {
        // We use the current RTL value for the initial test
#ifdef MRC_DEBUG_PRINT
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, rank, RoundTripDelay, ReadFromCache, &GetSetVal);
#endif
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Ch%u Sch0 initial RTL: %u", Channel, (UINT32) GetSetVal);
      } else {
        LoopEnd = (UINT8) ((PerByte) ? Outputs->SdramCount : 1);
        for (Byte = 0; Byte < LoopEnd; Byte++) {
          UpdateTAParamOffset (MrcData, Channel, 3, Byte, OptParam, Off, Update, MRC_PRINTS_ON, RankMaskCh);
        }
        if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
          // Set UpdateHost to TRUE because TA values share the same register
          MrcTatStretch (MrcData, Channel, OptParam, Off - Start, TRUE);
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
      ChBitMaskdd = drddPresent[dd];
      if (ChBitMaskdd == 0) {
        continue;
      }

      if (OptParam != rtl) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (dd == 0) ? "Dual Rank\n" : "Dual Dimm\n");
        // Select Ranks in the correct order based on the test type
        // Need to re-order the ranks based on the value of ddw2r
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ChannelOut  = &ControllerOut->Channel[Channel];
          RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
          if (RankMaskCh == 0) {
            continue; // No Ranks in this channel
          }
          // Initialize variables and read out ordered rank list
          CpgcChSeqRankL2PMapping.Data  = 0;
          RankCount                     = 0;

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
              for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
                if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubCh) == 0) {
                  continue;
                }
                Offset = OFFSET_CALC_CH_SUBCH (
                           CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG,
                           CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, Channel,
                           CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, SubCh);
                Offset += (RankCount / 6) * (CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG - CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG);
                MrcWriteCR (MrcData, Offset, CpgcChSeqRankL2PMapping.Data);
              }
              // Reset RankMapping register
              CpgcChSeqRankL2PMapping.Data = 0;
            }
            Rank = (RankList & 0xF); // Nibble by Nibble
            RankList = (RankList >> 4);
            if (!(RankMaskCh & (1 << Rank))) {
              continue;
            }

            ShiftValue = (RankCount % 6) * CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_WID;
            CpgcChSeqRankL2PMapping.Data |= (Rank << ShiftValue);
            RankCount++;
          }

          if (CpgcChSeqRankL2PMapping.Data != 0) {
            // Program the RankMapping register that did not get programmed in the while loop
            for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
              if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubCh) == 0) {
                continue;
              }
              Offset = OFFSET_CALC_CH_SUBCH (
                        CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG,
                        CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, Channel,
                        CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, SubCh);
              Offset += (RankCount / 6) * (CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG - CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG);
              MrcWriteCR (MrcData, Offset, CpgcChSeqRankL2PMapping.Data);
            }
          }

          for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
            if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubCh) == 0) {
              continue;
            }
            Offset = OFFSET_CALC_CH_SUBCH (
                      CH0_SC0_CR_CPGC2_ADDRESS_SIZE_REG,
                      CH1_SC0_CR_CPGC2_ADDRESS_SIZE_REG, Channel,
                      CH0_SC1_CR_CPGC2_ADDRESS_SIZE_REG, SubCh);
            Cpgc2AddrSize.Data = MrcReadCR (MrcData, Offset);
            OrigRankCount = (UINT8) (Cpgc2AddrSize.Bits.Block_Size_Num_Ranks + 1);
            if (OrigRankCount != RankCount) {
              Cpgc2AddrSize.Bits.Block_Size_Num_Ranks = RankCount - 1;
              MrcWriteCR (MrcData, Offset, Cpgc2AddrSize.Data);
              Cpgc20AdjustNumOfRanks (MrcData, Channel, SubCh, OrigRankCount, RankCount);
            }
          }
        } // for Channel
      } // if not "rtl" param
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
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(ChBitMaskdd & (MRC_BIT0 << Channel))) {
              offs[Channel] = 0;
            } else {
              // Shift all signals in the channel(Clk/Ctl/Cmd/Dq) by v0
              offs[Channel] = v0;
            }
          }
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 0);
          }
        } else if (dd == 1) {
          // For DD
          // Shift Clk/DQ on one DIMM by v0 and Clk/DQ on other DIMM by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          SetCmdMargin (MrcData, ChBitMaskdd, 0x3, WrT, v0, 0, ResetDDR, SelfRefresh, 0);
          SetCmdMargin (MrcData, ChBitMaskdd, 0xC, WrT, -v0, 0, ResetDDR, SelfRefresh, 0);
        } else {
          // For DR
          // Shift Clk/DQ on front side by v0 and Clk/DQ on backside by -v0
          // @todo: CTL picode should be optionally shifted to improve margins
          SetCmdMargin (MrcData, ChBitMaskdd, 0x5, WrT, v0, 0, ResetDDR, SelfRefresh, 0);
          SetCmdMargin (MrcData, ChBitMaskdd, 0xA, WrT, -v0, 0, ResetDDR, SelfRefresh, 0);
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
            MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
          } else {
            MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
          }
          DramVref = (Ddr4 || Lpddr4) && WriteVrefParam;
          // Are we done yet or should we keep testing?
          Done = 1;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(ChBitMaskdd & (MRC_BIT0 << Channel))) {
              continue;
            }

            ChannelOut  = &ControllerOut->Channel[Channel];
            RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
            if (RankMaskCh == 0) {
              continue; // No Ranks in this channel
            }

            // When FindFirstPass is used, all Bytes have to have passed before we stop.
            // We uses ByteFailMask[] to track the passing bytes in this case.
            if (PerByte || FindFirstPass) {
              if (ByteFailMask[Channel] != ByteDone) {
                Done = 0;
              }
            } else {
              if (ByteFailMask[Channel] == 0) {
                Done = 0;
              }
            }
          }

          if (Done) {
            break;
          }

          Status = GetMarginByte (MrcData, Outputs->MarginResult, Param, ResultRank, 0xF);
          if (Status != mrcSuccess) {
            return Status;
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 3d\t", (INT8) v0);
          //if (Outputs->DQPat == TurnAroundWR) MrcInterpreter (MrcData);
          Status = MrcGetBERMarginByte (
                    MrcData,
                    Outputs->MarginResult,
                    ChBitMaskdd,
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

          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            ChannelOut  = &ControllerOut->Channel[Channel];
            RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
            // if nothing for this channel OR No Ranks in this channel
            if (!((MRC_BIT0 << Channel) & ChBitMaskdd) || (RankMaskCh == 0)) {
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
                    (UINT16) MarginByte[ResultType][ResultRank][Channel][Byte][0],
                    (UINT16) MarginByte[ResultType][ResultRank][Channel][Byte][1]
                    );

              if (m < 20) {
                m = 20;
              }
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d", m);

              // If previously failed, this is also a failure unless we are looking for
              // the first passing offset.
              if ((ByteFailMask[Channel] & ByteMask) && !FindFirstPass) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                continue;
              }

              // Check if the first test is failing with zero margin.
              // Stop the test in this case - initial point should be passing.
              if ((Index == 0) && (m == 20)) {
                ByteFailMask[Channel] = ByteDone;
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "#\t");
                continue;
              }

              /* @todo: disable this as it make the results very conservative
              // Byte fails if margin is below MinMarginLimit at any time
              if (m < MinMarginLimit) {
                // If we are looking for pass, continue and do not update LastPass
                if (TRUE == FindFirstPass) {
                  if (Index == 0) {
                    // When training from the most aggressive setting to the conservative setting,
                    // if we fail the first setting we stop.
                    ByteFailMask[Channel] = ByteDone;
                  }
                  UpdateHostMargin = 0;
                } else {
                  ByteFailMask[Channel] |= ByteMask;
                  LastPass[Channel][Byte] = Off - Inc - ActualGuardBand;
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
                    ByteFailMask[Channel] |= ByteMask;
                    LastPass[Channel][Byte] = Off - Inc - ActualGuardBand;
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
                    if ((ByteFailMask[Channel] & ByteMask) != ByteMask) {
                      LastPass[Channel][Byte] = Off - ActualGuardBand;
                      ByteFailMask[Channel] |= ByteMask;
                    }
                  } else {
                    LastPass[Channel][Byte] = Off - ActualGuardBand;
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

          // Stop the test if we fail on the initial setting
          if (Index == 0) {
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              if (ByteFailMask[Channel] != 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%u failed initial value!\n", Channel);
                return mrcFail;
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
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            offs[Channel] = 0;
          }
          // UpdateHost=1
          if (v0 != 0) {
            ShiftCh2Ch (MrcData, RankMask, offs, ResetDDR, SelfRefresh, 1);
          }
        } else {
          SetCmdMargin (MrcData, ChBitMaskdd, RankMask, WrT, 0, 0, ResetDDR, SelfRefresh, 1);
        }
      } // for test0 in ClkShifts[]

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    } // for dd
    if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut  = &ControllerOut->Channel[Channel];
        RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
        // If nothing for this channel OR No Ranks in this channel
        if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
          continue;
        }
        // MrcTatStretch was called with UpdateHost so need to clean back to original values
        MrcTatStretch (MrcData, Channel, OptParam, - (Off - Start), TRUE);
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
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut            = &ControllerOut->Channel[Channel];
    RankMaskCh            = ChannelOut->ValidRankBitMask & RankMask;
    ChLastPass1[Channel]  = End;
    // if nothing for this channel OR No Ranks in this channel
    if (!((1 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
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
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", LastPass[Channel][Byte]);
      if ((Inc == 1) && (ChLastPass1[Channel] > LastPass[Channel][Byte])) {
        ChLastPass1[Channel] = LastPass[Channel][Byte];
      }

      if ((Inc == -1) && (ChLastPass1[Channel] < LastPass[Channel][Byte])) {
        ChLastPass1[Channel] = LastPass[Channel][Byte];
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut  = &ControllerOut->Channel[Channel];
    RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
    // if nothing for this channel OR No Ranks in this channel
    if (!((MRC_BIT0 << Channel) & ChBitMask) || (RankMaskCh == 0)) {
      continue;
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Optimal offset Channel %d = %d\n", Channel, ChLastPass1[Channel]);
  }
#endif // MRC_DEBUG_PRINT
  // Program new value
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }

    ChannelOut  = &ControllerOut->Channel[Channel];
    RankMaskCh  = ChannelOut->ValidRankBitMask & RankMask;
    if (RankMaskCh == 0) {
      continue; // No Ranks in this channel
    }
    // Start with the most aggressive setting
    ChLastPass = End;
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (Update == 0) {
        LastPass[Channel][Byte] = Begin;
      }

      if ((Inc == 1) && (ChLastPass > LastPass[Channel][Byte])) {
        ChLastPass = LastPass[Channel][Byte];
      }

      if ((Inc == -1) && (ChLastPass < LastPass[Channel][Byte])) {
        ChLastPass = LastPass[Channel][Byte];
      }

      if (PerByte) {
        UpdateTAParamOffset (MrcData, Channel, 3, Byte, OptParam, LastPass[Channel][Byte], Update, MRC_PRINTS_OFF, RankMaskCh);
      }
    }

    if (PerByte == FALSE) {
      UpdateTAParamOffset (MrcData, Channel, 3, 0, OptParam, ChLastPass, Update, MRC_PRINTS_OFF, RankMaskCh);
      if ((OptParam == wrodtd) || (OptParam == rdodtd)) {
        MrcTatStretch (MrcData, Channel, OptParam, ChLastPass - Start, TRUE);
      }
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected Offset for channel %d is = %d\n", Channel, ChLastPass);
  }

  if ((OptParam == ddwr2rd) || (OptParam == drwr2rd)) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
         continue;
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, WriteCached,   &RdWrSg[Channel]);
    }
  }
  return Status;
}

/**
  Sets command margins when moving WrT, WrTBox, or WrV
  NOTE: ONLY one, ResetDDR or SelfRefresh can be set inside this function

  @param[in] MrcData         - Include all MRC global data.
  @param[in] ChBitMask       - Bit mask of populated channels
  @param[in] Ranks           - Bit Mask of populated ranks
  @param[in] Param           - Input parameter to update
  @param[in] Value0          - value to be added
  @param[in] Value1          - value to be added
  @param[in] ResetDDR        - Do we reset DDR?
  @param[in] SelfRefresh     - Do we perform Self refresh?
  @param[in] UpdateHost      - Determines if MrcData structure is updated
                             - Used in ShiftDQPIs function to use local delay values or register cache values.

  @retval MrcStatus      - If it succeeds return mrcSuccess
**/
void
SetCmdMargin (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChBitMask,
  IN const UINT8          Ranks,
  IN const UINT8          Param,
  IN const UINT8          Value0,
  IN const UINT8          Value1,
  IN UINT8                ResetDDR,
  IN const UINT8          SelfRefresh,
  IN const UINT8          UpdateHost
  )
{
  MrcControllerOut  *ControllerOut;
  INT64             GetSetVal;
  UINT8             Channel;
  UINT8             RankMaskCh;
  UINT8             Offset;

  ControllerOut = &MrcData->Outputs.Controller[0];

  Offset        = 0;
  if (SelfRefresh && ResetDDR) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "WARNING SelfRefresh OR ResetDDR can be set at once...performing SelfRefresh\n"
      );
    ResetDDR = 0;
  }

  if (SelfRefresh) {
    GetSetVal = 1;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);
  }

  // Walk though all chs and ranks
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (ChBitMask & (MRC_BIT0 << Channel)) {
      // determine which ranks from parameter "Ranks" exist in this channel
      RankMaskCh = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;
      if (RankMaskCh == 0) {
        continue; // No Ranks in this channel
      }
      switch (Param) {
        case WrTBox:
        case WrT:
          ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMaskCh, 3, Value0, UpdateHost);
          if (Param != WrTBox) {
            break;
          }
        // Fall through to WrV if Param is WrTBox.
        case WrV:
          Offset = (Param == WrTBox) ? ((2 * Value1) - 1) * 8 : Value0;
          ChangeMargin (MrcData, WrV, Offset, 0, 0, Channel, RankMaskCh, 0, 0, 0, 0);
          break;

        default:
          return;
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
  @param[in]     Channel    - Channel to update the specified parameter.
  @param[in]     SubchMask  - SubChannel mask to update the specificed parameter.
  @param[in]     Byte       - Byte to update the specified parameter.
  @param[in]     OptParam   - Parameter to update.
  @param[in]     Off        - Value to offset the current setting.
  @param[in]     UpdateHost - Switch to update the host structure with the new value.
  @param[in]     DebugPrint - Switch to enable debug prints.
  @param[in]     RankMask   - Bit mask of Ranks to update.

  @retval Nothing
**/
void
UpdateTAParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN           UINT32         SubchMask,
  IN     const UINT8          Byte,
  IN     const UINT8          OptParam,
  IN     const INT8           Off,
  IN     const UINT8          UpdateHost,
  IN     const UINT8          DebugPrint,
  IN     const UINT8          RankMask
  )
{
  MrcDebug    *Debug;
  MrcOutput   *Outputs;
  INT64       GetSetVal;
  INT64       GetSetValSaved1[MAX_RANK_IN_CHANNEL];
  INT64       GetSetValSaved2[MAX_RANK_IN_CHANNEL];
  INT64       Roundtrip;
  INT64       RtlDelta;
  INT64       FifoDelta;
  INT64       FlybyDelta;
  INT64       CommonFlyby;
  INT64       RxFifoRdEnFlyby;
  UINT32      SubCh;
  UINT8       Rank;
  INT8        New;
  UINT8       GsmModeSingle;  //For parameters that only updates one setting
  UINT8       GsmModeMulti;   //For parameters that updates more than one setting
  UINT32      PrintMode;
  BOOLEAN     TatUpdate;
  BOOLEAN     Ddr4;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  GsmModeMulti  = ForceWriteCached;
  GsmModeSingle = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;
  GetSetVal     = Off;
  TatUpdate     = FALSE;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  PrintMode     = 0;
  if (DebugPrint) {
    GsmModeSingle |= PrintValue;
    GsmModeMulti  |= PrintValue;
  }

  switch (OptParam) {
    case drrd2rd:
      // Different Rank RD 2 RD Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddrd2rd:
      // Different DIMM RD 2 RD Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drwr2wr:
      // Different Rank WR 2 WR Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddwr2wr:
      // Different DIMM WR 2 WR Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drrd2wr:
      // Different Rank RD 2 WR Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddrd2wr:
      // Different DIMM RD 2 WR Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case drwr2rd:
      // Different Rank WR 2 RD Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case ddwr2rd:
      // Different DIMM WR 2 RD Turn Around offsets
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, GsmModeSingle, &GetSetVal);
      TatUpdate = TRUE;
      break;

    case rdodtd:
      // Convert into Register values. 2'b00 = BL/2 + 2 (For Enhanced Channels 10 DCLKs, otherwise 6 DCLKs)
      // @todo: <CNL> Enhance Channel switch.
      GetSetVal  = Off - 6;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtRdDuration, GsmModeSingle, &GetSetVal);
      break;

    case wrodtd:
      // Convert into Register values. 2'b00 = BL/2 + 2 (For Enhanced Channels 10 DCLKs, otherwise 6 DCLKs)
      // @todo: <CNL> Enhance Channel switch.
      GetSetVal  = Off - 6;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtWrDuration, GsmModeSingle, &GetSetVal);
      break;

    case mcodts:
      // MC ODT delay
      if (!UpdateHost) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDelay, ReadFromCache, &GetSetValSaved2[0]);
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDelay, ReadFromCache, &GetSetValSaved1[0]);
      New                   = (INT8) GetSetValSaved1[0] + Off;
      if (New < -4) {
        New = -4; // RcvEnPi[8:6] - 5 qclk Min
      } else if (New > 6) {
        New = 6; // RcvEnPi[8:6] + 5 qclk Max
      }

      GetSetVal             = New;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDelay, GsmModeMulti, &GetSetVal);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDelay, GsmModeMulti, &GetSetVal);
      if (!UpdateHost) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDelay, WriteToCache, &GetSetValSaved1[0]);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDelay, WriteToCache, &GetSetValSaved2[0]);
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (DebugPrint) ? "%d\t" : "", New);
      break;

    case mcodtd:
      // Duration
      if (!UpdateHost) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDuration, ReadFromCache, &GetSetValSaved2[0]);
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDuration, ReadFromCache, &GetSetValSaved1[0]);
      GetSetVal = GetSetValSaved1[0] + Off;

      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDuration, GsmModeMulti, &GetSetVal);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDuration, GsmModeMulti, &GetSetVal);
      if (!UpdateHost) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDuration, WriteToCache, &GetSetValSaved1[0]);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDuration, WriteToCache, &GetSetValSaved2[0]);
      }
      break;

    case rtl:
      // Note: UpdateHost argument is ignored for "rtl" parameter - we always keep CR cache updated to the HW for the below parameters.
      Roundtrip = 0;
      if (Ddr4) {
        SubchMask = 3;
      }
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh) || (((1 << SubCh) & SubchMask) == 0)) {
          continue;
        }
        CommonFlyby = MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MAX;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (RankMask & (1 << Rank)) {
            // When we change Roundtrip, we can compensate with the following:
            //  - READCFGCHx.tCL4RxDqFifoRdEn (tCK) - per SubCh
            //  - RXDQFIFORDENCHACHBx.RxDqFifoRdEnRank0ChADel (UI) - per SubCh / Rank
            if (!Ddr4 || (SubCh == 0)) {  // Use only Subch0 for DDR4
              MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay, ReadFromCache | PrintMode, &Roundtrip);
            }
            RtlDelta = Off - Roundtrip;
            if (Outputs->Gear2) {
              FifoDelta = RtlDelta;
              FlybyDelta = 0;
            } else {
              FifoDelta = (INT32) RtlDelta / 2;
              FlybyDelta = (UINT32) RtlDelta & 1;
              if ((FlybyDelta == 1) && (RtlDelta < 0)) {
                FifoDelta -= 1;
              }
            }
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n--> [R%d C%d Sch%d] RtlDelta: %lld, FifoDelta: %lld, FlyByDelta: %lld\n", Rank, Channel, SubCh, RtlDelta, FifoDelta, FlybyDelta);
            if (!Ddr4 || (SubCh == 0)) {  // Use only Subch0 for DDR4
              MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay,     WriteOffsetCached | PrintMode, &RtlDelta);
            }
            MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, WriteOffsetCached | PrintMode, &FlybyDelta);
            MrcGetSetDdrIoGroupChSch    (MrcData, Channel, SubCh,       RxFifoRdEnTclDelay,   WriteOffsetCached | PrintMode, &FifoDelta);

            MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, ReadFromCache | PrintMode, &RxFifoRdEnFlyby);
            CommonFlyby = MIN (CommonFlyby, RxFifoRdEnFlyby);
          }
        } // for Rank
        // Move the common part of RxFifoFlyby (Subch/Rank) into RxFifo (Subch)
        if ((CommonFlyby > 1) && !Outputs->Gear2) {
          FifoDelta = (INT32) CommonFlyby / 2;
          FlybyDelta = -((INT32) FifoDelta * 2);
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CommonFlyby: %lld, FifoDelta: %lld, FlyByDelta: %lld\n", CommonFlyby, FifoDelta, FlybyDelta);
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (RankMask & (1 << Rank)) {
              MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, WriteOffsetCached | PrintMode, &FlybyDelta);
            }
          }
          MrcGetSetDdrIoGroupChSch    (MrcData, Channel, SubCh, RxFifoRdEnTclDelay,   WriteOffsetCached | PrintMode, &FifoDelta);
        }
      } // for SubCh
      break;

    default:
      break;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    ((OptParam != mcodtd) && (OptParam != mcodts) && DebugPrint) ? "%d\t" : "",
    Off
    );

  if (TatUpdate) {
    // Must update the XARB bubble injector when TAT values change
    SetTcBubbleInjector (MrcData, Channel);
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
  Lpddr         = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
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
      0,
      MRC_PRINTS_ON
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
      0,  // En2D
      MRC_PRINTS_ON
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
      0,  // En2D
      MRC_PRINTS_ON
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
      case (OptTxTco):
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
  MrcOutput                         *Outputs;
  INT64                             RcompOdtUp;
  INT64                             GetSetVal;
  UINT32                            GsModeFlags;
  UINT8                             Channel;
  UINT32                            Byte;

  Outputs                = &MrcData->Outputs;
  GsModeFlags            = (UpdateHost) ? ForceWriteCached : ForceWriteUncached;

  // Update offset in local CR variable
  switch (param) {
    case RdOdt:
      // Disable FixOdt feature before changing this param
      GetSetVal = 0;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocFixOdtD, GsModeFlags, &GetSetVal);
      // Apply Comp Offset to RdOdt
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, DqOdtVref, GsModeFlags, &GetSetVal);
      break;

    case WrDS:
      // Apply Comp Offset to WrDS-DQ
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, GsModeFlags, &GetSetVal);
      break;

    case WrDSCmd:
      // Apply Comp Offset to WrDS-CMD
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, CmdDrvVref, GsModeFlags, &GetSetVal);
      break;

    case WrDSCtl:
      // Apply Comp Offset to WrDS-CTL
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, CtlDrvVref, GsModeFlags, &GetSetVal);
      break;

    case WrDSClk:
      // Apply Comp Offset to WrDS-CLK
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, ClkDrvVref, GsModeFlags, &GetSetVal);
      break;

    case SCompDq:
      // Apply Comp Offset to Scomp-DQ
      GetSetVal = offset & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, TxSlewRate, GsModeFlags, &GetSetVal);
      GetSetVal = (offset >> 4) & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, DqScompPC, GsModeFlags, &GetSetVal);
      break;

    case SCompCmd:
      // Apply Comp Offset to Scomp-CMD
      GetSetVal = offset & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, CmdSlewRate, GsModeFlags, &GetSetVal);
      GetSetVal = (offset >> 4) & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, CmdScompPC, GsModeFlags, &GetSetVal);
      break;

    case SCompCtl:
      // Apply Comp Offset to Scomp-CTL
      GetSetVal = offset & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, CtlSlewRate, GsModeFlags, &GetSetVal);
      GetSetVal = (offset >> 4) & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, CtlScompPC, GsModeFlags, &GetSetVal);
      break;

    case SCompClk:
      // Apply Comp Offset to Scomp-CLK
      GetSetVal = offset & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, ClkSlewRate, GsModeFlags, &GetSetVal);
      GetSetVal = (offset >> 4) & 0xF;
      MrcGetSetDdrIoGroupController0 (MrcData, ClkScompPC, GsModeFlags, &GetSetVal);
      break;

    case DisOdtStatic:
      // disable static read Odt legs
  //    DdrCrCompCtl0.Bits.DisableOdtStatic = offset;
      GetSetVal = offset;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, GsModeFlags, &GetSetVal);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataOdtStaticDis, GsModeFlags, &GetSetVal);
        }
      }
      break;

    default:
      break;
  }
  // Run Compensation
  // Start Comp Engine
  ForceRcomp (MrcData);
  if ((param == RdOdt) && (AjustOdtStatic)) {
    // we check if we close to saturation and try dis/en the static legs
    MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtUp, ReadUncached, &RcompOdtUp);
    if ((RcompOdtUp < 16) || (RcompOdtUp > 48)) {

      // disable/enable static read Odt legs
      GetSetVal = (RcompOdtUp < 16) ? 1 : 0;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, WriteCached, &GetSetVal);

      // Update the Comp Offsets and Host Structure
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataOdtStaticDis, WriteCached, &GetSetVal);
        }
      }

      // Run Compensation
      // Start Comp Engine
      ForceRcomp (MrcData);
    }

  }
  // Return the new comp code
  switch (param) {
    case DisOdtStatic:
    case RdOdt:
      MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtUp, ReadUncached, &RcompOdtUp);
      MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
      // re-Enable FixOdt feature after changing this param
      GetSetVal -= RcompOdtUp;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDqOdtUpDnOff, GsModeFlags, &GetSetVal);
      GetSetVal = 1;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocFixOdtD, GsModeFlags, &GetSetVal);
      return (UINT32) RcompOdtUp;

    case WrDS:
      MrcGetSetDdrIoGroupController0 (MrcData, TxRonUp, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case SCompDq:
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCodeDq, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case WrDSCmd:
      MrcGetSetDdrIoGroupController0 (MrcData, WrDSCodeUpCmd, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case SCompCmd:
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCodeCmd, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case WrDSCtl:
      MrcGetSetDdrIoGroupController0 (MrcData, WrDSCodeUpCtl, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case SCompCtl:
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCodeCtl, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case WrDSClk:
      MrcGetSetDdrIoGroupController0 (MrcData, WrDSCodeUpClk, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    case SCompClk:
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCodeClk, ReadUncached, &GetSetVal);
      return (UINT32) GetSetVal;

    default:
      break;
  }

  return 0;
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
  INT64     Min;
  INT64     Max;
  INT16     CurRcvEn;
  UINT8     Channel;
  UINT8     Byte;
  UINT8     rank;
  INT16     MaxRcvEn;
  INT16     MinRcvEn;
  UINT32    SaWakeUp;
  UINT32    TdqsckPs;
  UINT8     DurationMin;// starting tQCK value for the Duration
  INT8      On;         // SenseAmp / ODT delay
  INT32     Off;        // SenseAmp / ODT duration
  INT32     DqsOff;     // DQS ODT duration
  INT64     GetSetOn;   // SenseAmp / ODT delay
  INT64     GetSetOff;  // SenseAmp / ODT duration
  INT64     GetSetVal;
  INT64     GetSetEn;
  INT64     DqsOdtDelay;
  INT64     DqsOdtDuration;
  BOOLEAN   Lpddr4;

  GetSetEn    = 1;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  TdqsckPs    = (Lpddr4) ? 1200 : 0;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UpdateSampOdtTiming: GuardBand = %d\n", GuardBand);
  MrcGetSetLimits (MrcData, RecEnDelay, &Min, &Max, NULL);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d\tOdtOn\tOdtOff\tSAmpOn\tSAmpOff\tDqsOn\tDqsOff\n", Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MaxRcvEn  = 0;
        MinRcvEn  = (UINT16) Max;

        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (MrcRankInChannelExist (MrcData, rank, Channel)) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
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
        MaxRcvEn = DIVIDECEIL (MaxRcvEn,  64);

        // SENSE AMP CAN ONLY BE ON WHEN ODT IS ON FOR EOS REASONS.
        // On = MinRcvEn - SWakeUp ;

        SaWakeUp = (UINT32) (((64 * MRC_SENSE_AMP_WAKEUP_TIME) + TdqsckPs) / Outputs->UIps); // Convert to PI codes
        // Turn On ODT & Samp at least 2 Qclks before earlier RcvEn Rise
        if (SaWakeUp < 128) {
          SaWakeUp = 128; // at least 2-Qclks
        }

        On = (INT8) ((MinRcvEn - SaWakeUp) / 64) ;
        if (On < -4) {
          On = -4; // RcvEnPi[9:6] - 5 qclk
        } else if (On > 14) {
          On = 14; // RcvEnPi[9:6] + 13 qclk
        }

        // Turn Off Samp/ODT 1 qclk after postamble
        // Program the duration to leave Odt/Samp On
        //      OnBeforeRcvEn   BL+Post  AfterPost   CR Encoding
        if (!Outputs->Gear2) {
          DurationMin = (Lpddr4) ? 19 : 11; //in tQCK
        } else {
          DurationMin = (Lpddr4) ? 11 : 6; //in tQCK
        }

        Off    = (MaxRcvEn - On) + (2 * Outputs->BurstLength + 1) + 1 + GuardBand - DurationMin;
        DqsOff = (MaxRcvEn - On) + Outputs->BurstLength - DurationMin;

        if (Off < 0) {
          Off = 0; // tQCK Min
        } else if (Off > 7) {
          Off = 7; // tQCK Max
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocOdtSampExtEn, WriteCached, &GetSetEn);
        }
        DqsOff = RANGE (DqsOff, 0, 7);

        GetSetOn  = On;
        GetSetOff = Off;
        DqsOdtDelay = On * 2; // DQS ODT Delay is in half QCLK granularity
        if (Lpddr4 && !MrcData->Inputs.IclA0) {
          // LPDDR4 leaker / park mode: DQS ODT should drop in the middle of the burst
          DqsOdtDuration = DqsOff;
        } else {
          DqsOdtDuration = Off;
        }

        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDelay,       WriteToCache, &GetSetOn);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDuration,    WriteToCache, &GetSetOff);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDelay,    WriteToCache, &GetSetOn);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SenseAmpDuration, WriteToCache, &GetSetOff);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McDqsOdtDelay,    WriteToCache, &DqsOdtDelay);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McDqsOdtDuration, WriteToCache, &DqsOdtDuration);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "%d:\t%d\t%d\t%d\t%d\t%d\t%d\n",
          Byte,
          On,
          Off,
          On,
          Off,
          (INT32) DqsOdtDelay,
          (INT32) DqsOdtDuration
        );
      }
    }
  }
  MrcFlushRegisterCachedData(MrcData);

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
  UINT8             Channel;
  UINT8             byte;
  UINT8             rank;
  UINT8             MaxPi;
  INT64             GetSetVal;

  Outputs          = &MrcData->Outputs;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        MaxPi = 0;
        for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
          if (MrcRankInChannelExist (MrcData, rank, Channel)) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, rank, byte, RxDqsPDelay, ReadFromCache, &GetSetVal);
            if (MaxPi < GetSetVal) {
              MaxPi = (UINT8) GetSetVal;
            }

            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, rank, byte, RxDqsNDelay, ReadFromCache, &GetSetVal);
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
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, byte, GsmIocSdllSegmentDisable, WriteCached, &GetSetVal);
      }
    }
  }

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
  IN     const UINT8 *const   offset,
  IN     UINT8                ResetDDR,
  IN     const UINT8          SelfRefresh,
  IN     const UINT8          UpdateHost
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcIntOutput      *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut  *IntCmdTiming;
  MrcStatus         Status;
  INT64             GetSetVal;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMaskCh;
  UINT8             CmdGroup;
  INT32             NewValue;
  INT32             Offset;

  Status        = mrcSuccess;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];

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
    MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    IntCmdTiming = &IntControllerOut->CmdTiming[Channel];
    RankMaskCh = Ranks & ControllerOut->Channel[Channel].ValidRankBitMask;

    if (RankMaskCh == 0) {
      continue;
    }

    Offset = offset[Channel];

    // Shift CLK (this will shift DQ PIs as well)
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMaskCh, 3, Offset, UpdateHost);

    // Shift CTL
    NewValue = 0;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (RankMaskCh & (1 << Rank)) {
        NewValue = (INT32) (IntCmdTiming->CtlPiCode[Rank]) + Offset;
        break;
      }
    }

    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, RankMaskCh, 0, NewValue, UpdateHost);

    // Shift Cmd
    for (CmdGroup = 0; CmdGroup < MAX_COMMAND_GROUPS; CmdGroup++) {
      ShiftPIforCmdTraining (
        MrcData,
        Channel,
        MrcIterationCmd,
        RankMaskCh,
        1 << CmdGroup,
        (INT32) IntCmdTiming->CmdPiCode[CmdGroup] + Offset,
        UpdateHost
        );
    }
  } // for Channel

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
  MrcChannelOut   *ChannelOut;
  UINT8           byte;
  UINT8           rank;
  //UINT8           offset;
  //UINT8           Dimm;
  UINT8           RttLoop;
  UINT8           test;
  UINT8           TestArray[SizeOfTCompOffset];
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
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
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
    // update GRdOdt
    UpdateCompTargetValue (MrcData, RdOdt, BestDimmOptPoint->ODTSet.GRdOdt, UpdateHost);
    BestDimmOptPoint->ODTSet.GRdOdtCode = GetCompCode ( MrcData, RdOdt, 2);

    if (DebugPrint) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "GRdODT aplly is : %d \n",
        CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, FALSE, 0, FALSE, 0, 0)
        );
    }
  }

  // On ULT (1DPC) DIMM ODT is connected to Vdd, so RttNom must be disabled
  // SKL <EA> TODO: what about SKL platforms?
  // Apply Best RTT Points
  if (!SkipDimmOdts) {
    for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank += 2) {
      if (!MrcRankInChannelExist (MrcData, rank, Channel)) {
        continue;
      }
      Ranks = (0x3 << rank) & RankMask;
      if (Ranks == 0) {
        continue;
      }
      for (RttLoop = 0; RttLoop < RttTypeSize; RttLoop++) {
        SetDimmParamValue (
           MrcData,
           Channel,
           Ranks,
           ChannelOut->ValidSubChBitMask,
           BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank / 2].RttType[RttLoop],
           BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank / 2].Rtt[RttLoop],
           UpdateHost
          );
        if (DebugPrint) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%s Channel %d Ranks  0x%X apply is : %d\t\n",
            TOptParamOffsetString[BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop]],
            Channel,
            Ranks,
            CalcDimmImpedance (MrcData, Channel, rank, BestDimmOptPoint->ODTSet.DimmOdt[Channel][rank/2].RttType[RttLoop], FALSE,
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
              if (!(MrcRankInChannelExist (MrcData, rank, Channel) && (Ranks & RankMask))) {
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
            if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
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
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetCompCr;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetCompHost;
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
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasIComp, ReadFromCache, &GetSetVal);
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
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      MrReg = &ChannelOut->Dimm[Rank / 2].Rank[(Rank % 2)].MR[mrMR0];
      MRValue     = MrReg[mrMR1];
      FinalVal[1] = (INT16) ((MRValue >> 1) & 0x1);
    }
  }
  // DIMM ODT Values
  if ((OptParam == OptDimmOdt) || (OptParam == OptDimmOdtWr)) {
    // DIMM ODT Encoding   RttNom[A9,A6,A2]   RttWr[A10, A9] LPDDR - No RttNom
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
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
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", CalcDimmImpedance (MrcData, Channel, FirstRank,
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
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t", TOptParamOffsetString[OptParam[0]]);
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
    if ((Param == WrV) && (Outputs->Frequency > f1867)) {
      Limit += 160;
    }

    if ((Inputs->PowerTrainingMode == MrcTmMargin) && (LimitType == PowerLimit)) {
      Limit += 120;
    }
  }

  if ((DdrType == MRC_DDR_TYPE_DDR4) && (Param == WrV)) {
    Limit /= 2; // DDR4 step is 7.8mV
  }

  if ((Inputs->PowerTrainingMode == MrcTmPower) && (DdrType == MRC_DDR_TYPE_LPDDR4) && (LimitType == UpmLimit)) {
    if (Param == RdV) {
      Limit += 120;
    } else if (Param == RdT) {
      Limit += 80;
    }
  }

  if ((Param == RdT) && (Outputs->Gear2)) {
    // 2:1 ratio for RxDQS in G2
    Limit *= 2;
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
      if (Outputs->Frequency < f1600) {
        Limit = MrcLimits[Index].SaGvLimits[LimitType];
      } else if (Inputs->PowerTrainingMode == MrcTmMargin) {
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
  IN UINT8                Channel,
  IN UINT8                Rank,
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
  // LPDDR4 Parameters
  static const UINT16         Lpddr4OdtDic[7]  = { 0xFFFF, 240, 120, 80, 60, 48, 40 };
  static const UINT16         Lpddr4RonDic[6]  = { 240, 120, 80, 60, 48, 40 };             // MR3 PD-DS ; Note: Index starts from 1 (0 field values is RFU)


  DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister1;
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister2;
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister5;
  UINT8                       MaxLpddrIndex;
  UINT8                       Dimm;
  BOOLEAN                     Ddr4;
  BOOLEAN                     Lpddr4;
  UINT16                      LpddrMr;
  UINT16                      *MR;
  TOdtValueDdr4               *Ddr4OdtTableIndex;
  TOdtValueLpddr4             *Lpddr4OdtTableIndex;
  UINT16                      Impedance = 0xFFFF; // Odt off
  UINT8                       MrIndex;
  UINT8                       MrNum;
  UINT16                      MrValue;

  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Debug       = &Outputs->Debug;
  DdrType     = Outputs->DdrType;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Dimm        = RANK_TO_DIMM_NUMBER(Rank);

  if (GetFromTable) {
    if (Ddr4) {
      Ddr4OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
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
    } else if (Lpddr4) {
      Lpddr4OdtTableIndex = (TOdtValueLpddr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
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
      GetOptDimmParamMrIndex(MrcData, OptParam, &MrIndex, &MrNum);
      MrValue = ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR[MrIndex];
      if (Ddr4) {
        Ddr4ModeRegister2.Data = MrValue;
        Impedance = Override ? OverrideValue : Ddr4RttWrDic[Ddr4ModeRegister2.Bits.DynamicOdt];
      } else { // Lpddr4
        LpddrMr = MrValue & 0x7;
        MaxLpddrIndex = ARRAY_COUNT (Lpddr4OdtDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4OdtDic[RANGE (LpddrMr, 0, MaxLpddrIndex)];
      }
    }
    if (OptParam == OptDimmOdtNom) {
      if (Ddr4) {
        GetOptDimmParamMrIndex(MrcData, OptParam, &MrIndex, &MrNum);
        Ddr4ModeRegister1.Data = MR[MrIndex];
        Impedance = Override ? OverrideValue : Ddr4RttNomDic[Ddr4ModeRegister1.Bits.OdtRttValue];
      }
    }

    if (OptParam == OptDimmOdtPark) {
      if (Ddr4) {
        GetOptDimmParamMrIndex(MrcData, OptParam, &MrIndex, &MrNum);
        Ddr4ModeRegister5.Data = MR[MrIndex];
        Impedance = Override ? OverrideValue : Ddr4RttNomDic[Ddr4ModeRegister5.Bits.RttPark];
      }
    }

    if (OptParam == OptDimmRon) {
      GetOptDimmParamMrIndex(MrcData, OptParam, &MrIndex, &MrNum);
      MrValue = ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2].MR[MrIndex];
      if (Ddr4) {
        Ddr4ModeRegister1.Data = MrValue;
        Impedance = Override ? OverrideValue : Ddr4RonDic[Ddr4ModeRegister1.Bits.ODImpedance];
      } else { // Lpddr4
        LpddrMr = (MrValue >> 3) & 0x7;
        MaxLpddrIndex = ARRAY_COUNT(Lpddr4RonDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4RonDic[RANGE(LpddrMr - 1, 0, MaxLpddrIndex)];
      }
    }

    if (OptParam == OptDimmOdtCA) {
      if (Lpddr4) {
        GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
        LpddrMr = (MR[MrIndex] >> 4) & 0x7;
        MaxLpddrIndex = ARRAY_COUNT (Lpddr4OdtDic) - 1;
        Impedance = Override ? OverrideValue : Lpddr4OdtDic[RANGE(LpddrMr, 0, MaxLpddrIndex)];
      }
    }
  } //end else GetFromTable

  if ((OptParam == OptDimmOdtCA) && Lpddr4) {
    Impedance /= 2;
  }

  return Impedance;
}

/**
  This function returns the Actual Cpu Impedance in Ohms for given OptParam.
  The values will be taken from the host structure, unless override is used.

  @param[in] MrcData        - Pointer to MRC global data.
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
  MrcIntOutput   *IntOutputs;
  MrcChannelOut  *ChannelOut;
  UINT32         Result;
  UINT16         Rext;
  UINT8          StepSize;
  UINT8          RComp;
  UINT8          LegsPerSeg;
  UINT8          RatioR2r;
  UINT32         Rleg;
  UINT8          Segments;
  UINT8          TermFactor;
  UINT16         Divider;
  UINT8          OdtLegsOn;
  UINT8          CurrentComp;
  INT8           VrefOffset;
  INT16          DigiOffset;
  INT64          GetSetVal;
  UINT8          UnsignedData8;
  UINT32         Numerator;
  UINT32         Denomenator;
  UINT16         VddVoltage;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;

  IntOutputs  = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  VddVoltage  = (UINT16)((Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Inputs->MemoryProfile]);
  Numerator   = 0;
  Denomenator = 0;
  DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];

  if (CompOverride) {
    VrefOffset = VrefOverride;
    CurrentComp = CompCode;
  } else {
    CurrentComp = GetCompCode (MrcData, OptParam, 0); // Get comp code up
    if (OptParam == OptRdOdt) {
      MrcGetSetDdrIoGroupController0 (MrcData, DqOdtVref, ReadFromCache, &GetSetVal);
      VrefOffset = (INT8) GetSetVal;
    } else if (OptParam == OptWrDS || OptParam == OptTxEq) {
      MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, ReadFromCache, &GetSetVal);
      VrefOffset = (INT8) GetSetVal;
    } else {
      VrefOffset = 0;
    }
  }

  OdtLegsOn = 1;
  // RatioR2r = 10 * R_DynamicLeg_LSB [ohms] /  r_SingleStaticLeg [ohms]

  RatioR2r = (UINT8) (IntOutputs->ResistanceDynamicLeg * 10 / IntOutputs->ResistanceStaticLeg);
  StepSize = MRC_COMP_VREF_STEP_SIZE;

  if (OptParam == OptRdOdt) {
    LegsPerSeg = 8;   // Number of Static legs per segment
    RComp = 0;        // RCOMP0 controls read DQ ODT
    if (Outputs->OdtMode == MrcOdtModeVtt) {
      Segments    = 1; // in Vtt mode the segment is compensated to the actual ext. resistor
      TermFactor  = 2; // Terminated to VDD/2
    } else {
      Segments    = 2; // in Odt mode we have 1 segment but we treat up & dn as 2
      TermFactor  = 1; // Terminated to VDD
    }
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, ReadFromCache, &GetSetVal);
    OdtLegsOn = GetSetVal ? 0 : 1;
    if (Override) {
      DigiOffset = OffsetOverride;
    } else {
      DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID, 8);
    }
  } else if ((OptParam == OptWrDS) || (OptParam == OptTxEq)) {
    Segments = 2;
    TermFactor = 1; // @todo: LowSupplyEn calculation factor
    // TxEq full drive bits [4:5]
    // A0: ULX - 3, 6, 8, 10  DT - 4, 8, 12, 15
    // B0: ULX - 4, 6, 8, 10  DT - 6, 9, 12, 15
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxEq, ReadFromCache, &GetSetVal);
    UnsignedData8 = (UINT8) GetSetVal;
    LegsPerSeg = ((0x3 & (UnsignedData8 >> 4)) + 2 ) * Segments;
    RComp = 1;  // RCOMP1 controls write drive strength
    if (Override) {
      DigiOffset = OffsetOverride;
    } else { // from host
      if (OptParam == OptWrDS) {
        DigiOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID, 8);
      } else { // OptTxEq
        DigiOffset =  (Inputs->CpuModel == cmICL_ULX_ULT) ? (((0xF & (UnsignedData8)) * 2 + 2) / 3) : (0xF & (UnsignedData8));// in ulx num legs 0-10
      }
    }
  } else {
    return 0;
  }

  // TermFactor is always non-zero.  VrefOffset can be zero.
  // Protect by divide by zero here.
  if (VrefOffset == 0) {
    return 0;
  } else {
    Rext = Inputs->RcompResistor[RComp];
    // Calc global (Comp) value - Normalize according to LowSupEn
    if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Inputs->LowSupplyEnData)) {
      Numerator = Rext * (StepSize * Inputs->VccIomV - VddVoltage * VrefOffset * TermFactor);
      Denomenator = (VddVoltage * VrefOffset * TermFactor);
    } else  {
      Numerator = Rext * (StepSize - (VrefOffset * TermFactor));
      Denomenator = (VrefOffset * TermFactor);
    }



    Result = (UINT16) (Numerator / Denomenator);
    Rleg = Result * (OdtLegsOn * (LegsPerSeg * RatioR2r) + CurrentComp * 10);
  }

  if (OptParam == OptTxEq) { // we calc here the tx relative to global drv value
    DigiOffset = RatioR2r * DigiOffset; // total number of static legs
    if (DigiOffset == 0) {
      Result = 0xFFFF; // Infinite resistance
    } else {
      Result = DIVIDEROUND (Rleg, DigiOffset); // result is for entire buffer
    }
  } else {
    Divider = OdtLegsOn * (LegsPerSeg * RatioR2r)  + 10 * (CurrentComp + DigiOffset);
    if (Divider == 0) {
      Divider = 1;
    }
    Result = Rleg / Divider / Segments;
  }
  return (UINT16) Result;
}

/**
  Calculate Power for the selected Opt param based on

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Channel to work on
  @param[in] Rank        - Rank to work on
  @param[in] Byte        - Byte to work on
  @param[in] OptParam    - The Opt Parameters to work on
  @param[in] Offset      - The corresponded Offsets to work on
  @param[in] OptParamLen - Length of the Optparam list
  @param[in] CurrentComp - The current Comp code for OptParam
  @param[in] ReadHost    - Switch to read current offset and CompCode from Host structure.

  @retval Calc power in mW
**/
MrcStatus
CalcOptPowerByte (
  IN MrcParameters   *MrcData,
  IN MrcPower        *Power,
  IN UINT8           Channel,
  IN UINT8           Rank,
  IN UINT8           Byte,
  IN const UINT8     *OptParam,
  IN INT8            *Offset,
  IN UINT8           OptParamLen,
  IN INT8            CurrentComp,
  IN UINT8           Scale
  )
{
  const MrcInput        *Inputs;
  MrcOutput             *Outputs;
  MrcIntOutput          *IntOutputs;
  MrcChannelOut         *ChannelOut;
  static const UINT16   RxPowerConstuW[][2] = {{1288,900}, {1525, 1105}, {1800, 1180}}; // [Vddq current/Vccio Current][ULX/ULT/ULT(DDR3)]  - 100x [mA]  Per Byte
  static const UINT16   RxPowerScaleSKL[] = {125, 250, 375, 500, 625, 750, 875, 1000, 1125, 1250, 1375, 1500, 1625, 1750, 1875, 2000};
  UINT8                 RxDefault;
  UINT32                CPURXPower;
  UINT16                TxParamVector[MaxTxPowerParam];
  UINT16                RxParamVector[MaxRxPowerParam];
  BOOLEAN               Override;
  UINT8                 Idx;
  MRC_POWER_SYS_CONFIG  SysConfig;
  DimmRttWr             DimmWrOdt;
  INT8                  LocalOffset;
  UINT16                BufferStageDelayPS;
  UINT8                 ScaleRdPwr;
  UINT8                 ScaleWrPwr;
  UINT16                DimmRon;
  BOOLEAN               Ddr4;
  UINT32                VccIO;
  UINT32                Vdd;
  UINT8                 BiasConfig;
  INT64                 GetSetVal;
  UINT8                 NumStages;
  UINT8                 SlewRateCompCells;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;

  Inputs                   = &MrcData->Inputs;
  Outputs                  = &MrcData->Outputs;
  IntOutputs               = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  ChannelOut               = &Outputs->Controller[0].Channel[Channel];
  Ddr4                     = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  VccIO                    = Inputs->VccIomV;
  Vdd                      = Outputs->VddVoltage[Inputs->MemoryProfile];

  DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
  ScaleRdPwr = 60;
  ScaleWrPwr = 40;

  // Tx
  TxParamVector[MbLengthTx] = 1000; // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[MbLengthTx] = RANGE (TxParamVector[MbLengthTx], 800, 2800);

  TxParamVector[SoDimmLenTx] = 200;  // @todo: Mrc inputs [mil's]
  // keep within the simulation range
  TxParamVector[SoDimmLenTx] = RANGE (TxParamVector[SoDimmLenTx], 50, 900);

  Idx = MrcSearchList (OptWrDS, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, ReadFromCache, &GetSetVal);
  TxParamVector[CpuRon]  = CalcCpuImpedance (
                          MrcData,
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

  Idx = MrcSearchList(OptSComp, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  if (Override) {
    LocalOffset = Offset[Idx - 1];
  } else {
    LocalOffset = (INT8) MrcSE ((UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset, DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID, 8);
  }

  // read global cell delay for Tx
  MrcGetSetDdrIoGroupController0 (MrcData, TxSlewRate, ReadFromCache, &GetSetVal);
  SlewRateCompCells = (UINT8) GetSetVal;
  MrcGetSetDdrIoGroupController0 (MrcData, DqScompPC, ReadFromCache, &GetSetVal);
  NumStages = (GetSetVal == ScompTypePhase) ? 2 * (SlewRateCompCells + 1) : (SlewRateCompCells + 1);

  BufferStageDelayPS = DIVIDEROUND (Outputs->Qclkps, NumStages);
  TxParamVector[CpuCellDelay] = BufferStageDelayPS * ((UINT16) MrcPercentPower ((LocalOffset < 0) ? 95 : 105, ABS(LocalOffset))) / 100; // simple linear T-line
  // keep within the simulation range
  TxParamVector[CpuCellDelay] = RANGE (TxParamVector[CpuCellDelay], 10, 100);

  Idx = MrcSearchList(OptTxEq, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, ReadFromCache, &GetSetVal);
  TxParamVector[CpuTxEq]  = CalcCpuImpedance (
                            MrcData,
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
    Idx = MrcSearchList(DimmWrOdtNT, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
    TxParamVector[DimmWrOdtNT]  = MrcGetEffDimmWriteOdt(MrcData, Channel, Rank, 1, FALSE);
    // keep within the simulation range
    TxParamVector[DimmWrOdtNT] = RANGE (TxParamVector[DimmWrOdtNT], 100, 500);
  } else {
    // in LPDDR4 we use entry [3] for Mb_len
    TxParamVector[DimmWrOdtNT] = TxParamVector[MbLengthTx];
  }

  Idx = MrcSearchList(OptDimmOdtWr, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  DimmWrOdt = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, Override, LocalOffset, FALSE);
  if (DimmWrOdt == 0xFFFF) {// DDR4 HiZ
    DimmWrOdt = 0;
  } else if (DimmWrOdt == 0) {// when dynamic odt off the nom is picked
    DimmWrOdt = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom, Override, LocalOffset, FALSE);
  }


  // Rx
  RxParamVector[MbLengthRx]   = 1000; //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[MbLengthRx]   = RANGE (RxParamVector[MbLengthRx], 800, 2800);
  RxParamVector[SoDimmLenRx]  = 200;  //@todo: Mrc inputs [mil's]
  // keep within the simulation range
  RxParamVector[SoDimmLenRx]  = RANGE (RxParamVector[SoDimmLenRx], 50, 900);

  Idx = MrcSearchList(OptRdOdt, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, ReadFromCache, &GetSetVal);
  RxParamVector[CpuOdt]  = CalcCpuImpedance (
                            MrcData,
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

  Idx = MrcSearchList(DimmRdOdtNT, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  RxParamVector[DimmRdOdtNT]  = MrcGetEffDimmWriteOdt(MrcData, Channel, Rank, 1, FALSE);
  // keep within the simulation range
  RxParamVector[DimmRdOdtNT] = RANGE (RxParamVector[DimmRdOdtNT], 60, 500);

  Idx = MrcSearchList(OptDimmRon, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
  DimmRon = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmRon, Override, LocalOffset, FALSE);


  Idx = MrcSearchList(OptRxBias, OptParam, OptParamLen, Offset, &Override, &LocalOffset);
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
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasIComp, ReadFromCache, &GetSetVal);
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
    SetupIOTestCADB (MrcData, Outputs->ValidChBitMask, LoopCount, NSOE, 1, 0);
  } else {
    SetupIOTestBasicVA(MrcData, Outputs->ValidChBitMask, LoopCount, 0, 0, 0,8);  //set test to all channels
  }

  ChBitMask = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
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
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MrcSetDataAndEccErrMsk (MrcData, Channel, 0xFFFFFFFFFFFFFFFFULL, 0xFF);
  }

  // Find MaxMargin for this channel
  MaxMarginV = GetMaxPossibleVrefOffset (MrcData, ParamV);

  //if (MAX_POSSIBLE_TIME < Stop) {
  //  Stop = MAX_POSSIBLE_TIME;
  //}
  //if (-MAX_POSSIBLE_TIME > Start) {
  //  Start = -MAX_POSSIBLE_TIME;
  //}

  if (ParamT == RdT) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (sign = 0; sign < 2; sign++) {
        byteMax[Channel] = (sign) ? ABS(Stop) : ABS(Start);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          byteMax[Channel] = MrcCalcMaxRxMargin (MrcData, ParamT, (UINT8) Channel, FirstRank, Byte, 0, byteMax[Channel]);
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
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      if (ParamT == CmdT) {
        IntCmdTiming  = &IntOutputs->Controller[0].CmdTiming[Channel];
        if (CmdIteration == MrcIterationClock) {
          // the 3 is to select two SubChannels
          ShiftPIforCmdTraining (MrcData, (UINT8) Channel, CmdIteration, localR[Channel], 3, Off, 0);
        }
        if (CmdIteration == MrcIterationCmd) {
          if (CmdGroup >= MAX_COMMAND_GROUPS) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error: CmdGroup out of bounds! %d", CmdGroup);
            return;
          }
          ShiftPIforCmdTraining (MrcData, (UINT8) Channel, CmdIteration, localR[Channel], 1 << CmdGroup, (INT32) IntCmdTiming->CmdPiCode[CmdGroup] + Off, 0);
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
          ShiftPIforCmdTraining (MrcData, (UINT8) Channel, CmdIteration, localR[Channel], localR[Channel], CurrValue + Off, 0);
        }
        MrcResetSequence (MrcData);
      } else {
        for (Byte = 0; Byte < NumBytes; Byte++) {
          Status = ChangeMargin (MrcData, ParamT, Off, 0, 0, (UINT8) Channel, FirstRank, Byte, 0, 1, 0);
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
        if (!MrcChannelExist (Outputs, Channel)) {
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
      if (!MrcChannelExist (Outputs, Channel)) {
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
    if (!MrcChannelExist (Outputs, Channel)) {
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
    Status = ChangeMargin (MrcData, ParamT, 0, 0, 1, 0, 0, 0, 0, 1, 0);
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
  MrcOdtPowerSaving           *OdtPowerSaving;
  UINT8                       Rank;
  UINT8                       Byte;
  UINT8                       Channel;
  UINT8                       TotalRankCount;
  UINT32                      PwrAvgRd;
  UINT32                      PwrAvgWr;
  UINT32                      PwrAvgTotal;

  Outputs         = &MrcData->Outputs;
  OdtPowerSaving  = &Outputs->OdtPowerSavingData;
  TotalRankCount  = 0;
  PwrAvgRd        = 0;
  PwrAvgWr        = 0;
  PwrAvgTotal     = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++){
          // CalcOptPowerByte will sum the bytes to get overall power
          CalcOptPowerByte (MrcData, &PwrChRank[Channel][Rank], Channel, Rank, Byte, NULL, NULL, 0, 0, 10);
        }
        PwrAvgRd += PwrChRank[Channel][Rank].RdPower;
        PwrAvgWr += PwrChRank[Channel][Rank].WrPower;
        PwrAvgTotal += PwrChRank[Channel][Rank].TotalPwr;
        TotalRankCount++;
      }
    }
  }

  if (TotalRankCount == 0) {
    TotalRankCount = 1;  // Prevent divide by 0
  }

  PwrAvgRd    /= TotalRankCount;
  PwrAvgWr    /= TotalRankCount;
  PwrAvgTotal /= TotalRankCount;
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
  UINT8             GlobalParam;
  UINT8             CurrCompVref;
  INT8              NewCompVref;
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
  UINT8             BestVrefOff;
  UINT8             SignBit;
  UINT8             Byte;
  UINT8             Channel;
  UINT8             NumCh;
  UINT8             ReservedCodes;
  INT8              MaxCompVref;
  INT8              MinCompVref;
  UINT8             DqSCompPC;
  UINT8             CurrDqSCompPC;
  INT8              CompCodes[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT8              CompCodesDn[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8             RcompUp;
  UINT8             RcompDn;
  UINT8             SlewRateComp;
  INT64             GetSetVal;
  INT16             Width;
  GSM_GT            Group1;
  GSM_GT            Group2;
  DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DdrCrDataOffsetComp;

  Outputs                   = &MrcData->Outputs;
  Debug                     = &Outputs->Debug;

  DdrCrDataOffsetComp.Data  = 0;
  ReservedCodes             = 3;
  NewComp                   = 0;
  Offset                    = 0;
  SignBit                   = 0;
  DqSCompPC                 = 0;
  CurrDqSCompPC             = 0;
  CurrentCompDn             = 0;
  NewCompDn                 = 0;
  OffsetDn                  = 0;
  RcompUp = RcompDn = SlewRateComp = 0;

  if (Param == OptWrDS) {
    Group1 = TxRonUp;
    Group2 = TxRonDn;
  } else if (Param == OptSComp) {
    Group1 = SCompCodeDq;
    Group2 = SCompCodeDq;
  } else {
    Group1 = CompRcompOdtUp;
    Group2 = CompRcompOdtDn;
  }

  MrcGetSetDdrIoGroupController0 (MrcData, Group1, ReadUncached, &GetSetVal);
  if (Param != OptSComp) {
    RcompUp   = (UINT8) GetSetVal;
    MrcGetSetDdrIoGroupController0 (MrcData, Group2, ReadUncached, &GetSetVal);
    RcompDn   = (UINT8) GetSetVal;
  } else {
    SlewRateComp = (UINT8) GetSetVal;
  }

  switch (Param) {
    case OptWrDS:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      MrcGetSetDdrIoGroupController0 (MrcData, DqDrvVref, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      Width               = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqDrvVref_WID;
      MaxCompVref         = (1 << (Width - 1)) - 1;
      MinCompVref         = (-1) * (1 << (Width - 1));
      GlobalParam         = WrDS;
      break;

    case OptRdOdt:
      CurrentComp         = RcompUp;
      CurrentCompDn       = RcompDn;
      MrcGetSetDdrIoGroupController0 (MrcData, DqOdtVref, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      Width               = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVref_WID;
      MaxCompVref         = (1 << (Width - 1)) - 1;
      MinCompVref         = (-1) * (1 << (Width - 1));
      GlobalParam         = RdOdt;
      break;

    case OptSComp:
      CurrentComp         = SlewRateComp;
      MrcGetSetDdrIoGroupController0 (MrcData, DqScompPC, ReadFromCache, &GetSetVal);
      CurrDqSCompPC       = (UINT8) GetSetVal;
      MrcGetSetDdrIoGroupController0 (MrcData, TxSlewRate, ReadFromCache, &GetSetVal);
      CurrCompVref        = (UINT8) GetSetVal;
      MaxCompVref         = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX;
      MinCompVref         = 4;
      GlobalParam         = SCompDq;
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
    if ((MrcChannelExist (Outputs, Channel))) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DdrCrDataOffsetComp.Data = ChannelOut->DataCompOffset[Byte];
        if (Param == OptWrDS) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvUpCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqDrvDownCompOffset;
          SignBit = 6;
        }

        if (Param == OptRdOdt) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqOdtUpCompOffset;
          OffsetDn  = (UINT8) DdrCrDataOffsetComp.Bits.DqOdtDownCompOffset;
          SignBit = 5;
        }

        if (Param == OptSComp) {
          Offset  = (UINT8) DdrCrDataOffsetComp.Bits.DqSlewRateCompOffset;
          OffsetDn = 0;
          SignBit = 5;
        }

        AvgOffset += (INT8) MrcSE (Offset, SignBit, 8);
        CompCodes[Channel][Byte] = CurrentComp + MrcSE (Offset, SignBit, 8);
        CompCodesDn[Channel][Byte] = CurrentCompDn + MrcSE (OffsetDn, SignBit, 8);
      }
    }
    NumCh++;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s CompUp:%d CompDn:%d CompVref:%d", TOptParamOffsetString[Param], CurrentComp, CurrentCompDn, (INT8) CurrCompVref);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (Outputs, Channel))) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nCh%dByte  ",Channel);
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d:% 3d/",Byte, (INT8) (CompCodes[Channel][Byte] - CurrentComp));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "% 3d\t", (INT8) (CompCodesDn[Channel][Byte] - CurrentCompDn));
      }
    }
  }
  Sign = (AvgOffset < 0) ? -1 : 1;
  // Calculate the average offset and round to the nearest integer.
  AvgOffset = (AvgOffset + Sign * NumCh * ((UINT8) Outputs->SdramCount) / 2) / (NumCh * ((UINT8) Outputs->SdramCount));

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
  DqSCompPC   = CurrDqSCompPC;
  StartDelta  = ABS ((INT8) AvgOffset);
  MinDelta    = StartDelta;
  if (Param == OptSComp) {
    Sign *= -1;
  }

  while (!Done) {
    NewCompVref = CurrCompVref + (Sign * Off);
    if ((MinCompVref > NewCompVref) || (NewCompVref > MaxCompVref)) {
      Done = 1;
    }
    if (Param == OptSComp) {
      if ((NewCompVref + 1) > 16) {
        DqSCompPC = 0;
      }

      NewCompVref = (DqSCompPC << 4) + NewCompVref;
    }
    NewComp   = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, NewCompVref, FALSE, 0);
    NewCompDn = GetCompCode(MrcData, Param, 1); // take care of up/dn
    // Reserve 3 comp codes
    if ((ReservedCodes > NewComp) || (NewComp > (63 - ReservedCodes))) {
      Done = 1;
    }
    if ((ReservedCodes > NewCompDn) || (NewCompDn > (63 - ReservedCodes))) {
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
    if (Param == OptWrDS) {
      MrcGetSetDdrIoGroupController0 (MrcData, TxRonDn, ReadUncached, &GetSetVal);
      NewCompDn  = (UINT8) GetSetVal;
    } else if (Param == OptRdOdt) {
      MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
      NewCompDn  = (UINT8) GetSetVal;
    }
    // Update all bytes with new offset: Offset + code - newcode = +newoffset
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      if ((MrcChannelExist (Outputs, Channel))) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, Param, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          if (Param == OptWrDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          } else if (Param == OptRdOdt) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdOdtDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          }
        }
      }
    }
  } else {
    // Restore CompVref
    if (Param == OptSComp) {
      NewCompVref = (CurrDqSCompPC << 4) + CurrCompVref;
    }

    NewComp = (UINT8) UpdateCompGlobalOffset (MrcData, GlobalParam, (INT8) CurrCompVref, FALSE, UpdateHost);
    if (Param == OptWrDS) {
      MrcGetSetDdrIoGroupController0 (MrcData, TxRonDn, ReadUncached, &GetSetVal);
      NewCompDn  = (UINT8) GetSetVal;
    } else if (Param == OptRdOdt) {
      MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
      NewCompDn  = (UINT8) GetSetVal;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
      if ((MrcChannelExist (Outputs, Channel))) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          UpdateOptParamOffset (MrcData, Channel, 0, Byte, Param, CompCodes[Channel][Byte] - NewComp, UpdateHost);
          if (Param == OptWrDS) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptWrDSDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          } else if (Param == OptRdOdt) {
            UpdateOptParamOffset (MrcData, Channel, 0, Byte, OptRdOdtDn, CompCodesDn[Channel][Byte] - NewCompDn, UpdateHost);
          }
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nParam:%s NewCompUp:%d NewCompDn:%d NewCompVref:%d", TOptParamOffsetString[Param], NewComp, NewCompDn, (INT8) BestVrefOff);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((MrcChannelExist (Outputs, Channel))) {
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
  static const UINT8 ParamList[] = {OptWrDS, OptRdOdt};
  UINT8            Param;

  for (Param = 0; Param < ARRAY_COUNT (ParamList); Param++) {
    OptimizeCompOffset (MrcData, ParamList[Param], 1);
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

  if ((OptParam == OptRdOdt) && (MrcData->Outputs.OdtMode == MrcOdtModeVtt)) {
    // in Vtt mode only odt up is valid
    UpDown = 0;
  }

  ReadReg   = TRUE;
  Read2Regs = TRUE;
  switch (OptParam) {
    case OptWrDS:
    case OptTxEq:
      GroupUp = TxRonUp;
      GroupDn = TxRonDn;
      break;

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

    case OptRdOdt:
      GroupUp = CompRcompOdtUp;
      GroupDn = CompRcompOdtDn;
      break;

    case OptSComp:
      Read2Regs = FALSE;
      GroupUp = SCompCodeDq;
      GroupDn = SCompCodeDq;
      break;

    case OptTxTco:
      Read2Regs = FALSE;
      GroupUp = TxTco;
      GroupDn = TxTco;
      break;

    default:
      ReadReg = FALSE;
      GroupUp = 0;
      GroupDn = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetCompCode(): Invalid OptParam %d\n", OptParam);
      break;
  }

  if (ReadReg) {
    MrcGetSetDdrIoGroupController0 (MrcData, GroupUp, ReadUncached, &GetSetVal);
    UpCode   = (UINT32) GetSetVal;
    if (Read2Regs) {
      MrcGetSetDdrIoGroupController0 (MrcData, GroupDn, ReadUncached, &GetSetVal);
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
   CTT ODT:  2 resistors (up & dn)
   VDDQ ODT: 2 resistors (up & up)
   VTT ODT:  1 resistor (up to VTT)
   VSS ODT:  2 resistors (dn & dn to VSS)

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Param        - COMP Vref parameter (see TGlobalCompOffset).
  @param[in] TargetValue  - Target COMP value in Ohm.
  @param[in] UpdateHost   - Update host struct with the new value or not.

  @retval mrcSuccess  - if Param is a valid COMP Vref parameter
**/
MrcStatus
UpdateCompTargetValue (
  MrcParameters *const MrcData,
  UINT8                Param,
  UINT16               TargetValue,
  BOOLEAN              UpdateHost
  )
{
  MrcDebug  *Debug;
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  UINT32    Numerator;
  UINT32    Denominator;
  INT16     CompVref;
  UINT16    ReferenceR;
  UINT8     NumOfSegments;
  UINT8     CompCode;
  UINT8     RComp;
  BOOLEAN   VttOdt;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  VttOdt  = (Outputs->OdtMode == MrcOdtModeVtt);

  // CmdDrv and CtlDrv is 3 segments
  // DqDrv  and ClkDrv is 2 segments
  // DqOdt is based on ODT mode: 1 for VTT and 2 for the rest.

  // RCOMP0: DQ ODT (read)
  // RCOMP1: DQ  / CLK Ron (drive strength)
  // RCOMP2: CMD / CTL Ron (drive strength)
  switch (Param) {
    case RdOdt:
      NumOfSegments = (VttOdt) ? 1 : 2;
      RComp = 0;
      break;

    case WrDS:
    case WrDSClk:
      NumOfSegments = 2;
      RComp = 1;
      break;

    case WrDSCmd:
    case WrDSCtl:
      NumOfSegments = 3;
      RComp = 2;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Bad Param : %d\n", Param);
      return mrcFail;
  }

  ReferenceR  = DIVIDEROUND (Inputs->RcompResistor[RComp], NumOfSegments);
  Numerator   = MRC_COMP_VREF_STEP_SIZE * ReferenceR;
  Denominator = TargetValue + ReferenceR;
  if (VttOdt && (Param == RdOdt)) {
    // Do multiply by 2 here to optimize to 1 divide which handles rounding.
    Denominator *= 2;
  }
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    if ((Inputs->LowSupplyEnData && ((Param == RdOdt) || (Param == WrDS))) ||
        (Inputs->LowSupplyEnCcc && ((Param == WrDSClk) || (Param == WrDSCmd)))
       ) {
      Numerator   *= Inputs->VccIomV;
      Denominator *= (Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Inputs->MemoryProfile];
    }
  }
  // Used UINT32 to prevent overflow of multiply with large UINT16 numbers.
  // Result should be less than UINT8 Max as register field is smaller than UINT8.
  CompVref = (UINT16) DIVIDEROUND (Numerator, Denominator);

  // Callee handles saturation at Min/Max values.
  CompCode = (UINT8) UpdateCompGlobalOffset (MrcData, Param, CompVref, TRUE, UpdateHost);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%8s: Target value: %3d ReferenceR: %3d VrefOffset: %3d Current Comp code: %3d\n",
    GlobalCompOffsetStr[Param],
    TargetValue,
    ReferenceR,
    CompVref,
    CompCode
    );

  if ((CompCode == 0) || (CompCode == 63)) {
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
  This function is used to train the Tx TCO Comp offset.
  TCO Comp performs training using fixed pattern, in order to avoid optimization of TCO Comp based on ISI / Crosstalk
  In order to leverage for very high margins resulting of fixed pattern, we ignore the power / UPM limits.

  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcTxTcoCompTraining (
  IN MrcParameters *const MrcData
)
{
  MrcOutput *Outputs;
  MrcStatus Status;

  Outputs = &MrcData->Outputs;
  Status = mrcSuccess;

  Status = TxTcoPerBitCompTraining(
            MrcData,
            Outputs->MarginResult,
            Outputs->ValidChBitMask,
            WrTBit, // Per bit
            StaticPattern
            );

  return Status;
}

/**
  This function is used to train the Tx TCO Comp offset for Dqs and Bypass.
  TcoDqsP trained per byte.
  TcoDqsN tainied with bypass training, so it must be train after all Tco trainng done.
  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcTxTcoDqsCompTraining(
  IN MrcParameters *const MrcData
)
{
  static const UINT8  TestList[] = { WrT };
  static const UINT8  Scale[] = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParamP[] = { OptTxTcoDqsP };
  static const UINT8  OptParamN[] = { OptTxTcoDqsN }; // with ByPass
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;


  // Coarse search for Global comp
  Start = OptParamLimitValue(MrcData, OptParamP[0], 0);
  Stop = OptParamLimitValue(MrcData, OptParamP[0], 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParamP,
    ARRAY_COUNT (OptParamP),
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

  // Coarse search for Global comp
  Start = OptParamLimitValue (MrcData, OptParamN[0], 0);
  Stop  = OptParamLimitValue (MrcData, OptParamN[0], 1);

  TrainDDROptParam(
    MrcData,
    &BestOff,
    0x3,
    0xF,
    OptParamN,
    ARRAY_COUNT (OptParamN),
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
  This function is used to train the Tx TCO Comp offset.
  TCO Comp performs training using clock pattern, in order to avoid optimization of TCO Comp based on ISI / Crosstalk

  @param[in] MrcData - Pointer to global MRC data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     Param       - {8:WrTBit}
  @param[in]     PatType     - Type of pattern the will be applied for optimization. Allowed values: [BasicVA, StaticPattern (in our case use Clock pattern)]

  @retval - mrcSuccess
**/
MrcStatus
TxTcoPerBitCompTraining(
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
  IN     UINT8                Param,
  IN     UINT8                PatType
)
{

  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  const MRC_FUNCTION          *MrcCall;
  MrcOutput                   *Outputs;
  MrcChannelOut               *ChannelOut;
  MrcControllerOut            *ControllerOut;
  MrcStatus                   Status;
  UINT8                       Channel;
  UINT8                       Byte;
  UINT8                       paramT;
  INT8                        Start;
  INT8                        Stop;
  UINT8                       Step;
  INT8                        TxTcoVal;
  UINT8                       TxTcoIdx;
  UINT8                       LoopCount;
  UINT8                       ResultType;
  UINT8                       RankMask;
  UINT8                       mode;
  UINT8                       Rank;
  UINT8                       bit;
  UINT8                       MaxMargin;
  INT64                       DqBitDelayMax;
  UINT32                      MarginBitSummary[8][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  UINT32                      marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32                      MarginByteArray[8][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                      BestMargin;
  INT32                       TxTcoBestValue;
  INT64                       GetSetVal;
  UINT8                       FirstRankPerCh[MAX_CHANNEL];
  UINT8                       localR[MAX_CHANNEL];
  UINT8                       BMap[9]; // Need by GetBERMarginByte
  UINT32                      BERStats[4];

  static UINT32 Pattern[8][2] = {
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 },
    { 0xAAAAAAAA, 0x55555555 }
  };

  Inputs = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug = &Outputs->Debug;
  Status = mrcSuccess;
  LoopCount = Outputs->DQPatLC = 10;

  ChBitMask &= Outputs->ValidChBitMask;
  RankMask = Outputs->ValidRankMask;

  MrcCall->MrcSetMem((UINT8 *)BERStats, sizeof(BERStats), 0);
  MrcCall->MrcSetMemDword((UINT32 *)marginbit,sizeof(marginbit) / sizeof(UINT32),0);
  MrcCall->MrcSetMemDword((UINT32 *)MarginBitSummary, sizeof(MarginBitSummary) / sizeof(UINT32), 0);
  MrcCall->MrcSetMemDword((UINT32 *)MarginByteArray, sizeof(MarginByteArray) / sizeof(UINT32), MAX_POSSIBLE_TIME);
  MrcCall->MrcSetMem((UINT8 *)localR, sizeof(localR), 0);
  MrcCall->MrcSetMem((UINT8 *)FirstRankPerCh, sizeof(FirstRankPerCh), 0);

  for (Byte = 0; Byte < ARRAY_COUNT(BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  SetupIOTestStatic(MrcData, ChBitMask, LoopCount, NSOE, 0, 0, 1, Pattern);

  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Enable Clock pattern\n");
  // Coarse search for Global comp
  Start = OptParamLimitValue(MrcData, OptTxTco, 0);
  Stop = OptParamLimitValue(MrcData, OptTxTco, 1);
  Step = 8; // Search Tco range in steps of 8

  if (Param == WrTBit) {
    //paramT = WrTBit;
    paramT = WrT;
    MrcGetSetLimits (MrcData, TxDqBitDelay, NULL, &DqBitDelayMax, NULL);
    MaxMargin = (UINT8) DqBitDelayMax;
  } else {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcWrongInputParameter;
    return Status;
  }

  // #############################################
  // ######    Measure WrT margin per Bit   ######
  // #############################################
   // Stop on all lane fail
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (ChBitMask & (MRC_BIT0 << Channel)) {
      // We enable error checking on all Cachelines and UI's of the Cacheline.
      MrcSetupTestErrCtl(MrcData, Channel, NSOE, 1);
    }
  }

  // Select rank for REUT test
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((0x1 << Channel) & ChBitMask)) {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];
    localR[Channel] = ChannelOut->ValidRankBitMask & RankMask;

    // Use ChBitMask from here down - if ch is set that mean at least 1 rank for testing, also remove ch w/o active ranks
    ChBitMask |= SelectReutRanks(MrcData, Channel, localR[Channel], FALSE, 0);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((0x1 << Rank) & localR[Channel]) {
        FirstRankPerCh[Channel] = Rank;
        break;
      }
    }
  }

  // Get margin per Bit
  Status = GetMarginByte(MrcData, Outputs->MarginResult, paramT, 0, 0xF);
  ResultType = GetMarginResultType(paramT);

  // Search TxTco values
  for (TxTcoVal = Start, TxTcoIdx = 0; TxTcoVal <= Stop; TxTcoVal += Step, TxTcoIdx++) {
    GetSetVal = TxTcoVal;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // Init results per Byte
        MarginByteArray[TxTcoIdx][Channel][Byte][0] = MarginByte[ResultType][FirstRankPerCh[Channel]][Channel][Byte][0];
        MarginByteArray[TxTcoIdx][Channel][Byte][1] = MarginByte[ResultType][FirstRankPerCh[Channel]][Channel][Byte][1];

        for (bit = 0; bit < MAX_BITS; bit++) {
          Status = MrcGetSetDdrIoGroupSocket0(MrcData, Channel, 0, Byte, bit, TxTco, WriteToCache, &GetSetVal);

          // init margin per bit results
          marginbit[Channel][Byte][bit][0] = marginbit[Channel][Byte][bit][1] = MaxMargin;

        } // end of bit
      } // end of byte
    }  // end of channel

    if (Status != mrcSuccess) {
    return Status;
    }

    MrcFlushRegisterCachedData(MrcData);

    mode = 0; // get margin for all ranks

    Status = MrcGetMarginBit(MrcData, ChBitMask, 0xF, marginbit, MarginByteArray[TxTcoIdx], paramT, mode, MaxMargin, MRC_PRINTS_OFF);

    // Store results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (bit = 0; bit < MAX_BITS; bit++) {
          MarginBitSummary[TxTcoIdx][Channel][Byte][bit] = marginbit[Channel][Byte][bit][0] + marginbit[Channel][Byte][bit][1];
        } // end of bit
      } // end of byte
    } // end of channel

  } // end of TxTcoVal

  if (Status != mrcSuccess) {
    return Status;
  }

  // #####################################################
  // ######     Get TxTco optimal value per Bit     ######
  // #####################################################
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      for (bit = 0; bit < MAX_BITS; bit++) {
        TxTcoBestValue = 32;  // default value
        BestMargin = 0;
        for (TxTcoIdx = 0; TxTcoIdx <= (Stop + ABS (Start)) / Step; TxTcoIdx++) {
          if (BestMargin <= MarginBitSummary[TxTcoIdx][Channel][Byte][bit]) {
            BestMargin = MarginBitSummary[TxTcoIdx][Channel][Byte][bit];
            if (BestMargin > MarginBitSummary[0][Channel][Byte][bit]) {  // Compare to default value
              TxTcoBestValue = Start + TxTcoIdx * Step;
            }
          }
        } // TxTco Loop

        GetSetVal = TxTcoBestValue;
        Status = MrcGetSetDdrIoGroupSocket0(MrcData, Channel, 0, Byte, bit, TxTco, WriteToCache | PrintValue, &GetSetVal);
      } // bit loop
    } // Byte loop
  } // Channel loop

  Status = MrcFlushRegisterCachedData(MrcData);

  return Status;
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
    0x3,
    0xF,
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


  SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, 0, 0, 0, 8); // set test to all channels

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

  if ((Param == RdV) || (Param == RdFan2) || (Param == RdFan3) || WriteVrefParam) {
    MaxMargin = GetMaxPossibleVrefOffset (MrcData, Param);
  } else {
    MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
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
  MrcIntOutput      *MrcIntData;
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
  MrcIntData          = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug               = &Outputs->Debug;
  ChannelMask        &= Outputs->ValidChBitMask;
  RankMask           &= Outputs->ValidRankMask;
  ControllerOut       = &Outputs->Controller[0];
  MrcCall             = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (Byte = 0; Byte < ARRAY_COUNT (BMap); Byte++) {
    BMap[Byte] = Byte;
  }
  SetupIOTestBasicVA (MrcData, ChannelMask, LoopCount, 0, 0, 0, 8); // set test to all channels
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
      // Setup REUT Error Counters to count errors per byte lane.
      MrcSetupErrCounterCtl (MrcData, Channel, 0, BMap[Byte], ErrCounterCtlPerByte);
    }
  }
  ReutGlobalCtl.Data = 0;
  ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
  MrcWriteCR (MrcData, MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_REG, ReutGlobalCtl.Data); // Clear errors
  // Run Test
  RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 0, 0);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }
    Results = 0;
    for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        // Read out per byte error results
        MrcGetMiscErrStatus (MrcData, Channel, SubCh, ByteGroupErrStatus, &ErrStatus);
        Results |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
      }
    }
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      continue;
    }
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      // Read Error Count
      MrcGetErrCounterStatus (MrcData, Channel, 0, Byte, ErrCounterCtlPerByte, &ErrCount, &Overflow);
      if (!NoPrint) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d Byte=%d Error Counter:%d\n", Channel, Byte, ErrCount);
      }
    }
  }
}
#endif // #if 0

