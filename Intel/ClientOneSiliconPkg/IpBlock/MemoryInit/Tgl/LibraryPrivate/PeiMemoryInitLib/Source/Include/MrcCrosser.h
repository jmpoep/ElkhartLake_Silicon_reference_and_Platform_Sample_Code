/** @file
    This file contains all the crosser training algorithm definitions.

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
#ifndef _MrcCrosser_h_
#define _MrcCrosser_h_

//
// Include files
//
#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDdr3.h"
#include "MrcIoControl.h"
#include "MrcReset.h"

#define MAX_BITS_FOR_OFFSET_TRAINING    (MAX_BITS + 1)    ///< for SOT offset training done for 8 bits + DQS bit

///
/// Module Defines
///
#define CROSSER_DISABLE_SQUARED_FUNCTION (0)
#define CROSSER_ENABLE_SQUARED_FUNCTION  (1)
#define CROSSER_MIDDLE_SCALING_1         (1)
#define CROSSER_OPTIMIZE_LOW_POWER       (0)
#define CROSSER_OPTIMIZE_HIGH_POWER      (1)
#define CROSSER_EXCLUDE_END_POINTS       (0)
#define CROSSER_INCLUDE_END_POINTS       (1)

extern const char *GlobalCompOffsetStr[];
extern const char *CompGlobalOffsetParamStr[];

///
/// Enumerations and Structs
///

typedef enum {
  ChessOdd,
  ChessEven,
  FullGrid,
  HalfGrid,
  Random,
  CustomSR,
  Reversed1D
} TGRidModes;

typedef enum {
  RdOdt,
  WrDS,
  WrDSCmd,
  WrDSCtl,
  WrDSClk
} TGlobalCompOffset;

typedef enum {
  RdOdtUp,
  RdOdtDn,
  WrDSUp,
  WrDSDn,
  WrDSCmdUp,
  WrDSCmdDn,
  WrDSCtlUp,
  WrDSCtlDn,
  WrDSClkUp,
  WrDSClkDn,
  SCompDq,
  SCompCmd,
  SCompCtl,
  SCompClk,
  RxLoad,
  DisOdtStatic,
  MaxCompGlobalOffsetParam
} CompGlobalOffsetParam;

typedef enum {
  RdSAmpOfft,
  WrDSOfft,
  RxEqOfft,
  TxEqOfft,
  RdOdtOfft,
  SizeOfTCompOffset
} TCompOffset;

typedef enum {
  rd2rdXtalk,
  rd2wrXtalk,
  wr2wrXtalk,
  wr2rdXtalk,
  AllXtalk
} CrossTalkModes;

typedef enum {
  RttWrOff = 0,
  RttWr60  = 60,
  RttWr120 = 120,
  RttWr240 = 240
} DimmRttWr;

typedef enum {
  RttWr,
  RttNom,
  RttPark,
  RttMaxType
} DimmOdtType;

///
/// These enums index MoreResultsStrings in PrintCalcResultTableCh()
///
typedef enum {
  MrcOptResultBest,
  MrcOptResultGrdBnd,
  MrcOptResultOffSel,
  MrcOptResultScale,
  MrcOptResultMaxPost,
  MrcOptResultMinPost,
  MrcOptResultMax
} MrcOptResultString;

typedef enum {
  ScompTypePhase,
  ScompTypeCycle
} SCompType;

#define MAX_DIMM_OPT_OFF      (50)
#define MAX_OPT_POINTS        (255)
#define MAX_GRID_DIM          (2)
#define MAX_TRADEOFF_TYPES    (MAX_MARGINS_TRADEOFF + 1)
#define MAX_MARGINS_TRADEOFF  (4)

//
// Maximum number of tests in the test list of TrainDDROptParamCliff() routine
//
#define MAX_TESTS_OPT_PARAM_CLIFF (6)

#pragma pack (push, 1)
typedef struct {
  UINT16 EW;
} OptResult;

typedef struct {
  UINT16    Best;
  INT8      GuardBand;
  UINT8     Scale[MAX_TRADEOFF_TYPES];
  UINT32    MaxPost[MAX_TRADEOFF_TYPES];
  UINT32    MinPost[MAX_TRADEOFF_TYPES];
  UINT64    MaxR;
  UINT64    Result[MAX_OPT_POINTS];
  OptResult Margins[MAX_TRADEOFF_TYPES][MAX_OPT_POINTS];
} OptResultsPerByte;

typedef struct {
  UINT8  OptParamLen;
  UINT8  GridMode;
  INT8   Start[MAX_GRID_DIM];
  UINT8  OffLen[MAX_GRID_DIM];
} GridData;

typedef struct {
  INT16     Offset[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16    Margins[MAX_MARGINS_TRADEOFF][MAX_CHANNEL];
  UINT8     TestList[MAX_MARGINS_TRADEOFF][MAX_CHANNEL];
  UINT8     NumTests;
  GridData  GridDataSet;
} OptOffsetChByte;

typedef struct {
  UINT16 Rtt[RttMaxType];
  UINT8 RttType[RttMaxType];
} DimmRtt;

typedef struct {
  DimmRtt DimmOdt[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT16  GRdOdt;
  UINT8   GRdOdtCode;
} DimmOffset;

typedef struct {
  UINT16 RdPower;
  UINT16 WrPower;
  UINT16 TotalPwr;
} MrcPower;

typedef struct {
  DimmOffset      ODTSet;
  MrcPower        PowerCalc;
  UINT16          Test[MAX_TRADEOFF_TYPES][MAX_CHANNEL];
  OptOffsetChByte BestOptOff[SizeOfTCompOffset][1];// support only 1 rank for now
  UINT8           NumTests;
  UINT8           TestList[MAX_MARGINS_TRADEOFF];
  UINT8           OptParamTestList[SizeOfTCompOffset];
  UINT8           OptParamTestListSize;
  UINT16          Points2Trade[MAX_TRADEOFF_TYPES][MAX_CHANNEL];
} DimmOptPoint;
#pragma pack (pop)

/**
  This function implements Sense Amp Offset training.
  SenseAmp/ODT offset cancellation
  Find the best "average" point for Vref Control
  Test Vref point with SampOffset=-7 and Test Vref Point with SampOffset=+7
  Find Vref on per ch/byte basis where -7 samples all 1 and +7 samples all 0

  @param[in,out] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcSenseAmpOffsetTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function looks at the margin values stored in the global data structure and checks
  WrT, WrV, RdT, and RdV to see if they are above the minimum margin required.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess if margins are acceptable.
  @retval Otherwise, mrcRetrain.
**/
MrcStatus
MrcRetrainMarginCheck (
  IN OUT MrcParameters *const MrcData
  );

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
  );

/**
  Print DIMM ODT values per DIMM.

  @param[in] MrcData  - Include all MRC global data.

  @retval none
**/
extern
void
MrcPrintDimmOdtValues (
  IN MrcParameters *const MrcData
  );

/**
  This function implements Dimm Ron training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeds return mrcSuccess
**/
extern
MrcStatus
MrcDimmRonTraining (
  IN MrcParameters *const MrcData
  );

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
  );

/**
  This function wrap DimmODTCATraining routine.

  @param[in] MrcData  - Include all MRC global data.
  @retval MrcStatus - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcDimmOdtCaTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function Wrap  DimmODTTraining routine.
  It will enable to control ch/ranks for this training and additional options.

  @param[in] MrcData     - Include all MRC global data.
  @retval MrcStatus      - if it succeed return mrcSuccess
**/
extern
MrcStatus
MrcDimmODTTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function implements Dimm Odt training.
  Optimize Dimm Odt value for performance/power

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeded return mrcSuccess
**/

/**
  This function implements Read Equalization training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
extern
MrcStatus
MrcReadEQTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function implements Write (Transmitter) Equalization training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteEqDsTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function implements Write (Transmitter) Drive Strength Up/Down training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeeds return mrcSuccess
**/
MrcStatus
MrcWriteDsUpDnTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function implements Read Amplifier Power training.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess
**/
extern
MrcStatus
MrcReadAmplifierPower (
  IN MrcParameters *const MrcData
  );

/**
  Returns the index into the array OptResult in the MrcOutput structure.

  @param[in] OptParam - Margin parameter

  @retval One of the following values: RdSAmpOfft(0), WrDSOfft (1), RxEqOfft(2), TxEqOfft (3), RdOdtOfft(4)
**/
extern
UINT8
GetOptResultType(
  IN UINT8 OptParam
  );

/**
  This function implements Read ODT training and Write DS.
  Optimize Read ODT strength for performance & power.

  @param[in,out] MrcData           - Include all MRC global data.
  @param[in,out] BestOff           - Structure containg the best offest and margins for th Opt param.
  @param[in]     ChannelMask       - Channels to train
  @param[in]     RankMask          - Condenses down the results from multiple ranks
  @param[in]     OptParam          - Defines the OptParam Offsets.
                                    Supported OptParam = [0: WrDS, 1: RdODT, 2: SComp, 3: TComp, 3: TxEq, 4: RxEq,
                                                          5: RxBias, 6: DimmOdt, 7: DimmOdtWr]
  @param[in]     TestList          - List of margin params that will be tested (up to 4)
  @param[in]     NumTests          - The length of TestList.
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
extern
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
  );

/**
  This function implements Read ODT training.
  Optimize Read ODT strength for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeded return mrcSuccess
**/
extern
MrcStatus
MrcReadODTTraining (
  IN MrcParameters *const MrcData
  );

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
extern
void
UpdateOptParamOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN           UINT8          Ranks,
  IN     const UINT8          Byte,
  IN           UINT8          OptParam,
  IN     INT16                Off,
  IN     const UINT8          UpdateHost
  );

/**
  Slightly penalize any Asymmetry in margin

  @param[in] NegEdge - Negative edge of the margin
  @param[in] PosEdge - Positive edge of the margin

  @retval p2p - Width/Height reduced by the asymmetric difference in margin.
**/
extern
UINT16
EffectiveMargin (
  IN const UINT16 NegEdge,
  IN const UINT16 PosEdge
  );

/**
  This function does a running average on Margins in two dimentional fashion.

  @param[in,out] Margins - Margins to average in a 1D array.
  @param[in]     MLen    - Determines the Y-Dimension lengths
  @param[in]     XDim    - Determines the X-Dimension lengths
  @param[in]     XMin    - Used to skip the first elements in the Margin when averaging.
  @param[in]     CScale  - Used to place more weight on the center point.

  @retval Nothing
**/
extern
void
RunningAverage2D (
  IN OUT UINT16    Margins[MAX_OPT_POINTS],
  IN     const UINT8  MLen,
  IN     const UINT8  XDim,
  IN     const UINT8  XMin,
  IN     const UINT8  CScale
  );

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
  IN     MrcParameters      *const MrcData,
  IN OUT UINT16    Margins[2][MAX_OPT_POINTS],
  IN     const UINT8  Test,
  IN     const UINT8  MLen,
  IN     const UINT8  XDim,
  IN     const UINT8  XMin,
  IN     const UINT8  CScale
  );

/**
  This function takes in 2D array of Margins: MarginType / Parameter Index.
  This index to the array represents some arbitrary parameter value that we are optimizing.
  The function will look for up to MAX_TRADEOFF_TYPES entries to optimize on.
  OptResByte will store the results of the optimization, and various other data.

  In addition to optimizing for margin, this function can also optimize for power.
  GoodPowerLimit is an array that sets level where power is more important than margin.
    i.e. Any points where ((Margin[0]>GoodPowerLimit[0]) & (Margin[1]>GoodPowerLimit[1]) & ... )
  To avoid overflow, this function will automatic scale margins to fit in UINT64

  @param[in]     MrcData          - The global MRC data structure.
  @param[in,out] OptResByte       - Structure containing the optimized results.
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
  @param[in]     OptimizationMode - 0:    Return the index that meets GoodPowerLimit and lowest power.
                                    1-99: Return the index that meets GoodPowerLimit and >= % of the Max Optimization result.
                                    >100: Returns the highest Optimization Result.
  @param[in]     GuardBand        - Signed offest to check if margin drop is acceptable.  Save good guardband
                                    in OptResByte.

  @retval Nothing.
**/
extern
void
FindOptimalTradeOff (
  IN     MrcParameters      *const  MrcData,
  IN OUT OptResultsPerByte          *OptResByte,
  IN     UINT16                     *InputMargins,
  IN     UINT8                      MarginsLength,
  IN     UINT8                      LenMargin,
  IN     const UINT8                Scale[MAX_TRADEOFF_TYPES],
  IN     const UINT8                UPMOptimize[MAX_TRADEOFF_TYPES],
  IN     UINT8                      EnSq,
  IN     UINT8                      AveN,
  IN     UINT8                      IncEnds,
  IN     UINT8                      ScaleM,
  IN     UINT16                     GoodPowerLimit[MAX_TRADEOFF_TYPES],
  IN     UINT8                      OptimizationMode,
  IN     INT8                       GuardBand
  );

/**
  This function implements Turn Around Timing training.
  Optimize TA ODT Delay and Duration

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it succeeds return mrcSuccess.
**/
extern
MrcStatus
MrcTurnAroundTiming (
  IN MrcParameters * const MrcData
  );

/**
  General purpose function to optimize an abritray value, OptParam (see list above)
    OptParam is generally some timing number that impacts performance or power
    Expects that as OptParam gets smaller*, margins are flat until we hit a cliff
    This procedure defines a cliff as a reducution of 4 ticks in eye height/width
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
extern
MrcStatus
TrainDDROptParamCliff (
  IN MrcParameters *const MrcData,
  IN UINT8       OptParam,
  IN const UINT8 TestList[],
  IN UINT8       NumTests,
  IN INT8        Start,
  IN INT8        Stop,
  IN UINT8       LoopCount,
  IN UINT8       Update,
  IN UINT16      MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const INT8  *ClkShifts,
  IN UINT8       NumR2RPhases,
  IN UINT8       rank,
  IN UINT8       RankMask,
  IN UINT8       GuardBand
  );

/**
  Sets commnad margins when moving WrT, WrTBox, or WrV
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
extern
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
  );

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
extern
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
  );

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
extern
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
  );

/**
  This function applies an offset to the global compensation logic.
  Reruns Compensation and returns the new comp value

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in]     param           - Parameter defining the desired global compensation logic
  @param[in]     offset          - Value to apply
  @param[in]     AjustOdtStatic  - Decides if Static ODT will be adjusted for ReadODT param
  @param[in]     UpdateHost      - Desides if MrcData has to be updated

  @retval Returns the new comp value.
**/
extern
UINT32
UpdateCompGlobalOffset (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          offset,
  IN     const BOOLEAN        AjustOdtStatic,
  IN     const BOOLEAN        UpdateHost
  );

/**
  Programs Delay/Duration for the SenseAmp and MCODT based on RcvEn timing
  Provide GuardBand > 0 if needed to be more conservative in timing
  Main goal is to optimize power

  @param[in,out] MrcData   - Include all MRC global data.
  @param[in]     GuardBand - Input parameter with more conservative value

  @retval Nothing
**/
extern
void
UpdateSampOdtTiming(
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          GuardBand
  );

/**
  Turns off unused portions of the slave DLL to save power

  @param[in,out] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
UpdateSlaveDLLLength(
  IN OUT MrcParameters * const MrcData
  );

/**
  Update Internal clocks on setting if needed.

  @param[in,out] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
UpdateInternalClksOn (
  IN OUT MrcParameters *const MrcData
  );

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
extern
MrcStatus
ShiftCh2Ch (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Ranks,
  IN     UINT8                offset[MAX_CONTROLLER][MAX_CHANNEL],
  IN     UINT8                ResetDDR,
  IN     const UINT8          SelfRefresh,
  IN     const UINT8          UpdateHost
  );

/**
  Program DimmOptPoint values on CPU and DIMM sides, such as DIMM ODT, CPU ODT, Ron, Slew Rate, Equalization.

  @param[in, out] MrcData          - Include all MRC global data.
  @param[in]      Channel          - Channel to work on.
  @param[in]      RankMask         - Ranks to update Opt Settings.
  @param[in, out] BestDimmOptPoint - Best DIMM Opt settings used to update hardware
  @param[in, out] RttType          - Which termination to set.
  @param[in]      SkipGRdOdt       - Switch to skip updating CPU ODT
  @param[in]      SkipDimmOdts     - Switch to skip updating DIMM ODT
  @param[in]      SkipBestOffsets  - Switch to skip updating Opt settings
  @param[in]      UpdateHost       - Switch to skip updating MRC host structure

  @retval Nothing
**/
extern
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
  );

/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     Param       - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                8:WrTBit, 9:RdTBit, 10:RdVBit,
                                16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                ONLY RdV is allowed in this function
  @param[in]     EnPerBit    - Option to enable per bit margining
  @param[in]     ResetPerBit - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
extern
MrcStatus
ReadVoltageCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
  IN     UINT8                Param,
  IN     UINT8                EnPerBit,
  IN     UINT8                ResetPerBit,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D
  );

#ifdef MRC_DEBUG_PRINT
/**
  Prints OptParam values from CRs and Host structure for all ch/Rank/byte as well as
  the Best optimization value (if requested)
  OptWrDS = 0
  OptRdOd = 1
  OptSCom = 2
  OptTComp = 3
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
extern
void
ReadOptParamOffsetSum (
  IN MrcParameters *const MrcData,
  IN UINT8                ChMask,
  IN UINT8                RankMask,
  IN const UINT8          OptParam,
  IN OptOffsetChByte      *OptOff,
  IN BOOLEAN              OptResult
  );

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
extern
void
ReadOptParamOffset (
  IN  MrcParameters *const MrcData,
  OUT INT16                *FinalVal,
  IN  const UINT8          Channel,
  IN  const UINT8          Rank,
  IN  const UINT8          Byte,
  IN  const UINT8          OptParam
  );

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
extern
void
PrintResultTableByte4by24(
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
  );

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
extern
void
  Print2DResultTableChByte (
  IN MrcParameters   *MrcData,
  IN UINT8           Channel,
  IN UINT8           Byte,
  IN OptResultsPerByte    *calcResultSummary,
  IN OptOffsetChByte *BestOff,
  IN UINT8           Param,
  IN UINT8           OffsetsNum,
  IN INT8            *Start,
  IN INT8            *Stop,
  IN const UINT8     *OptParam,
  IN UINT8           *OptParamLen,
  IN UINT16          *PowerLimits,
  IN UINT8           Dim,
  IN UINT16          TestNum,
  IN UINT8           NumTests,
  IN BOOLEAN         noPrint
  );

/**
  This function prints the Optimize margin result table: calcResultSummary.

  @param[in] MrcData           - MRC data structure
  @param[in] calcResultSummary - The data array [MAX_STROBES]
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
extern
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
  );

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
extern
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
  );

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
  );
#endif // MRC_DEBUG_PRINT

/**
  This function returns the UPM or PWR limit value for the specified parameter

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Margin type
  @param[in] LimitType - Type of limit: UpmLimit or PowerLimit

  @retval Returns the UPM or PWR limit
**/
extern
UINT16
MrcGetUpmPwrLimit (
  IN MrcParameters *const MrcData,
  IN UINT8                Param,
  IN UINT8                LimitType
  );

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
  );

/**
  Returns the index into RttType array

  @param[in] OptDimmOdt - DimmOdt type

  @retval One of the following values: RttWr RttNom RttPark

**/
DimmOdtType
GetRttType (
  IN const UINT8 OptDimmOdt
  );

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
  );


/**
  This function fill the input array (e.g array[ch][rank]) with the power calculation
  per rank/ch for current sys. setting.

  @param[in]     MrcData   - MRC data struct;
  @param[in,out] PwrChRank - Array to fill;

  @retval Nothing
**/
extern
void
CalcSysPower (
  IN     MrcParameters *const MrcData,
  IN OUT MrcPower             PwrChRank[MAX_CHANNEL][MAX_RANK_IN_CHANNEL]
  );

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
extern
void
NormalizePowerToMargins (
  IN     MrcParameters   *MrcData,
  IN     void            *Points2calc,
  IN     UINT8           ArrayLength,
  IN     UINT8           LenMargin,
  IN     UINT8           TestListSize
  );

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
extern
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
  );

/**
  This function implements Write Slew Rate training.
  Optimize Write Slew Rate for performance & power

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcWriteSlewRate (
  IN MrcParameters *const MrcData
  );

/**
  This function prints out the Margin eye diagram for ParamT/ParamV.


  @param[in] MrcData      - Include all MRC global data.
  @param[in] Ranks        - Bit mask of Ranks to margin.
  @param[in] ParamT       - Time parameter to margin.
  @param[in] ParamV       - Voltage parameter to margin.
  @param[in] CmdIteration - Whether doing CLK/CMD/CTL (only used with ParamT == CmdT and ParamV == CmdV)
  @param[in] CmdGroupMask - Determines which CmdGrp to use (only used with CmdIteration == MrcIterationCmd)
  @param[in] Start        - Starting point for margining.
  @param[in] Stop         - Stopping point for margining.
  @param[in] Repeats      - Number of times to repeat the test to average out any noise.

  @retval Nothing
**/
extern
void
EyeMargin (
  IN MrcParameters *const MrcData,
  IN UINT8                Ranks,
  IN UINT8                ParamT,
  IN UINT8                ParamV,
  IN UINT8                CmdIteration,
  IN UINT8                CmdGroupMask,
  IN INT8                 Start,
  IN INT8                 Stop,
  IN UINT16               SearchLimits,
  IN UINT8                LoopCount,
  IN UINT8                Repeats
  );

/**
  This function optimize the digital offsets by reducing the digital
  offset and apply the difference to the global one.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Param      - Parameter defining the desired digital compensation offset.
  @param[in] UpdateHost - Decides if MrcData is to be updated.

  @retval The new comp value.
**/
extern
UINT32
OptimizeCompOffset (
  IN MrcParameters *const MrcData,
  IN const UINT8          Param,
  IN const UINT8          UpdateHost
  );

/**
  This function implements the Write Drive Strength optimization for performance and power.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] ChBitMask  - Channel mask to perform training on the Opt Param test list.
  @param[in] RecenterLC - The loopcount for Write Time recentering.
  @param[in] OptParamLC - The loopcount for training the Opt Param test list.
  @param[in] Recenter   - Switch which determines if the step recenters Write Timing.

  @retval If it succeeds return mrcSuccess
**/
extern
MrcStatus
TrainWriteDriveStrength (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChBitMask,
  IN const UINT8          RecenterLC,
  IN const UINT8          OptParamLC,
  IN const BOOLEAN        Recenter
  );

/**
  This step performs Comp Offset optimization on the param list defined in this function.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess
**/
extern
MrcStatus
MrcOptimizeComp (
  IN MrcParameters *const MrcData
  );

/**
  This function calculates the percent of power saving from the power optimization steps and
  updates the proper registers in the PCU.  To get the correct base line for this calculation,
  this routing needs to run first time early in the training in order to update the MrcStruct
  with the base line.  After the power training steps, it will run again to get the actual
  percent of power saving.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess

**/
extern
MrcStatus
MrcPowerSavingMeter (
  IN MrcParameters *const MrcData
  );

/**
  This function reads the selected comp code.
  In case of comp up/dn we select the value that is closer to saturation (0 or 63).
  Safe assumption is that up/dn codes don't differ by too much.
  So if one of the codes is in the upper range (more than 32), we select MAX of both, otherwise we select MIN of both.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] OptParam - Parameter to read the relevant comp code.
  @param[in] UpDown   - TRUE: use min/max of both Up and Down codes; FALSE: use Up only.

  @retval The selected Comp code
**/
UINT8
GetCompCode (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                OptParam,
  IN     BOOLEAN              UpDown
  );

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
  );

/**
  Returns the Actual DIMM Driver/Odt Impedance in Ohms.
  Note: host structure calculation based.

  @param[in] MrcData       - Pointer to MRC global data.
  @param[in] Controller    - Zero based channel number.
  @param[in] Channel       - Zero based channel number.
  @param[in] Rank          - Zero based rank number.
  @param[in] OptParam      - Param to read.
  @param[in] Override      - Override host read value.
  @param[in] OverrideValue - Value to override.
  @param[in] GetFromTable  - Get the Values from Odt tables

  @retval Returns the DIMM driver impedance value in Ohms
**/
extern
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
  );

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
  );

/**
  This function assign the pointer to the relevant power Coefficient table to the MRC structure
  offset and apply the difference to the global one.

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
  );

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
  );

/**
@todo
**/
MrcStatus
PowerCalcverification (
  MrcParameters *MrcData
  );

/**
@todo
**/
BOOLEAN
GetParamsXYZ (
  IN     MrcParameters *const MrcData,
  IN OUT INT8*                ParamOff,
  IN     const UINT8          OptParamLen,
  IN     const UINT8          GridMode,
  IN     const UINT8          Index,
  IN     const INT8           *Start,
  IN     const UINT8          *ParamOffLen
  );

/**
  This function is used to train the TxDq TCO Comp offset.

  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcTxDqTcoCompTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train the TxDqs TCO Comp offset.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcTxDqsTcoCompTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train the Clk TCO Comp offset.

  @param[in] MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcClkTcoCompTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train Vddq.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcVddqTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train CMD/CTL Drive Strength and Equalization 2D.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcCmdEqDsTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train CMD/CTL Drive Strength Up/Dn 2D.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcCmdDsUpDnTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train CMD/CTL/CLK Slew Rate.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcCmdSlewRate (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train VccDLL Bypass.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcVccDLLBypassTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train RxVref Decap.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcRxVrefDecapTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function is used to train PanicVttDnLp.

  @param[in] MrcData - Pointer to global MRC data.

  @retval mrcSuccess - if it succeed return mrcSuccess
**/
MrcStatus
MrcPanicVttDnLpTraining (
  IN MrcParameters *const MrcData
  );

/**
@todo
**/
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
  );

/**
@todo
**/
void
PointTest (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT8                LoopCount,
  IN     UINT8                NumCL,
  IN     BOOLEAN              NoPrint
  );
#endif // _MrcCrosser_h_

