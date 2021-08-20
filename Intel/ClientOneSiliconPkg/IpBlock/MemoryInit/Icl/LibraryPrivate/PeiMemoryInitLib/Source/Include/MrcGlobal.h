/** @file
  This file includes all the data structures that the MRC considers "global data".

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _MrcGlobal_h_
#define _MrcGlobal_h_
#include "MrcInterface.h"
#include "McAddress.h"
#pragma pack (push, 1)

///
/// UPM PWR and Retrain Limits
///
#define MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS (9)
#define MRC_NUMBER_OPT_PARAMS_TRAIN        (20)
#define MAX_RCOMP         (3)
#define MAX_RCOMP_TARGETS (5)
/*
  The following is a list of registers that we want to cache.
  // 7 - CRS_ARRAY_ENTRIES
  UINT32        RxControl0 [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        RxControl1 [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        RxControl2 [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        RxControl3 [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        TxTrain    [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        TxPerBitLow[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        TxPerBitHi [MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];

  // 8 - CS_ARRAY_ENTRIES
  UINT32        DataControl0[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl1[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl2[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl3[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl4[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl5[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl6[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32        DataControl7[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];

  // 32 - CHANNEL_ARRAY_ENTRIES
  UINT32        TC_RDRD     [MAX_CHANNEL];
  UINT32        TC_RDWR     [MAX_CHANNEL];
  UINT32        TC_WRRD     [MAX_CHANNEL];
  UINT32        TC_WRWR     [MAX_CHANNEL];
  UINT32        TC_ACT      [MAX_CHANNEL];
  UINT32        TC_ODT      [MAX_CHANNEL];
  UINT32        TC_PRE      [MAX_CHANNEL];
  UINT32        TC_PWRDN    [MAX_CHANNEL];
  UINT32        TC_SRFTP    [MAX_CHANNEL];
  UINT32        TC_ZQCAL    [MAX_CHANNEL];
  UINT32        MAD_INTRA_CH[MAX_CHANNEL];
  UINT32        MAD_DIMM_CH [MAX_CHANNEL];
  UINT32        SC_GS_CFG   [MAX_CHANNEL];
  UINT32        SC_ROUNDTRIP_LATENCY         [MAX_CHANNEL];
  UINT32        DDRCMDA_DDRCRCMDPICODING     [MAX_CHANNEL];
  UINT32        DDRCMDB_DDRCRCMDPICODING     [MAX_CHANNEL];
  UINT32        DDRCKE_DDRCRCTLPICODING      [MAX_CHANNEL];
  UINT32        DDRCTL_DDRCRCTLPICODING      [MAX_CHANNEL];
  UINT32        DDRCTLCLKCKE_DDRCRCTLPICODING[MAX_CHANNEL];
  UINT32        DDRCKE_DDRCRCTLCOMPOFFSET    [MAX_CHANNEL];
  UINT32        DDRCLK_DDRCRCLKCOMPOFFSET    [MAX_CHANNEL];
  UINT32        DDRCTL_DDRCRCTLCOMPOFFSET    [MAX_CHANNEL];
  UINT32        DDRCMDA_DDRCRCMDCOMPOFFSET   [MAX_CHANNEL];
  UINT32        DDRCMDB_DDRCRCMDCOMPOFFSET   [MAX_CHANNEL];
  UINT32        DDRCLK_DDRCRCLKTCOCONTROL0   [MAX_CHANNEL];
  UINT32        DDRCTL_DDRCRCTLTCOCONTROL0   [MAX_CHANNEL];
  UINT32        DDRCMDA_DDRCRCMDTCOCONTROL0  [MAX_CHANNEL];
  UINT32        DDRCMDB_DDRCRCMDTCOCONTROL0  [MAX_CHANNEL];
  UINT32        DDRCKE_DDRCRCMDTCOCONTROL0   [MAX_CHANNEL];
  UINT32        MCMISCS_RXDQFIFORDENCHACHB   [MAX_CHANNEL];
  UINT32        MCMISCS_READCFGCHACHB0       [MAX_CHANNEL];
  UINT32        MCMISCS_WRITECFGCHACHB0      [MAX_CHANNEL];

  // 2 - CHANNEL_SUBCH_ARRAY_ENTRIES
  UINT32        MCMISCS_READCFG [MAX_CHANNEL][MAX_SUB_CHANNEL];
  UINT32        MCMISCS_WRITECFG[MAX_CHANNEL][MAX_SUB_CHANNEL];

  // 2 - ODT_CTL_ENTRIES
  UINT64_STRUCT OdtTiming[MAX_CHANNEL];

  // 17 - SINGLE_ENTRIES
  UINT32        MAD_INTER_CHANNEL;
  UINT32        DDRCRCMDCOMPOFFSET_GLOBAL;
  UINT32        DDRCRCTLCOMPOFFSET_GLOBAL;
  UINT32        DDRCRCLKCOMPOFFSET_GLOBAL;
  UINT32        DDRSCRAM_DDRMISCCONTROL0;
  UINT32        DDRVREF_DDRCRVREFADJUST1;
  UINT32        DDRVREF_DDRCRVREFADJUST3;
  UINT32        DDRPHY_COMP_DDRCRCOMPCTL0;
  UINT32        DDRPHY_COMP_DDRCRCOMPCTL1;
  UINT32        DDRPHY_COMP_DDRCRCOMPCTL2;
  UINT32        DDRPHY_COMP_DDRCRCOMPCTL3;
  UINT32        DDRCRDATACOMP0;
  UINT32        DDRCRCMDCOMP;
  UINT32        DDRCRCTLCOMP;
  UINT32        DDRCRCLKCOMP;
  UINT32        MiscOdtCtrl;
  UINT32        MCMISCS_DCCMAINFSMCONTROL0
*/
#define CHANNEL_RANK_STROBE_CACHE   (MAX_CHANNEL * MAX_RANK_IN_CHANNEL * MAX_SDRAM_IN_DIMM)
#define CHANNEL_STROBE_CACHE        (MAX_CHANNEL * MAX_SDRAM_IN_DIMM)
#define CHANNEL_SUB_CHANNEL_CACHE   (MAX_CHANNEL * MAX_SUB_CHANNEL)
#define CRS_ARRAY_ENTRIES           (7 * CHANNEL_RANK_STROBE_CACHE)
#define CS_ARRAY_ENTRIES            (8 * CHANNEL_STROBE_CACHE)
#define CHANNEL_ARRAY_ENTRIES       (32 * MAX_CHANNEL)
#define CHANNEL_SUBCH_ARRAY_ENTRIES (2 * CHANNEL_SUB_CHANNEL_CACHE)
#define ODT_CTL_ENTRIES             (2 * MAX_CHANNEL)
#define SINGLE_ENTRIES              (17)
#define CACHE_PAD_ENTRIES           (0)

#ifdef MRC_DISABLE_CACHING
#define REGISTER_CACHE_SIZE         1
#define MAX_REGISTER_CACHE_ENTRIES  1
#else
#define MIN_CACHE_ENTRIES_SIZE      1024
#define MIN_CACHE_ENTRIES_MASK      (MIN_CACHE_ENTRIES_SIZE-1)
#define REGISTER_CACHE_SIZE   ( \
  CRS_ARRAY_ENTRIES +           \
  CS_ARRAY_ENTRIES +            \
  CHANNEL_ARRAY_ENTRIES +       \
  CHANNEL_SUBCH_ARRAY_ENTRIES + \
  ODT_CTL_ENTRIES +             \
  SINGLE_ENTRIES +              \
  CACHE_PAD_ENTRIES)
#define MAX_REGISTER_CACHE_ENTRIES ((REGISTER_CACHE_SIZE<MIN_CACHE_ENTRIES_SIZE) ? MIN_CACHE_ENTRIES_SIZE : REGISTER_CACHE_SIZE)
#endif

///
/// Enumerations
///
typedef enum {
  CpuCellDelay,
  CpuRon,
  CpuTxEq,
  DimmWrOdtNT,
  MbLengthTx,
  SoDimmLenTx,
  MaxTxPowerParam
} TxPowerOptParam;

typedef enum {
  CpuOdt,
  DimmRdOdtNT,
  MbLengthRx,
  SoDimmLenRx,
  MaxRxPowerParam
} RxPowerOptParam;

typedef enum {
  RefRateLowTempOOS,  // Not safe
  RefRateFourth,      // 4x tREFI - Not safe
  RefRateHalf,        // 2x tREFI
  RefRate1x,          // tREFI
  RefRate2x,          // 1/2 tREFI
  RefRate4x,          // 1/4 tREFI
  RefRate4xDeRateAc,  // 1/4 tREFI de-rate AC timing - Not safe
  RefRateHighTempOOS  // Not safe
} LpddrRefreshRates;

///
/// Structures
///
typedef struct {
  union {
    struct {
      UINT8 Valid   : 1;  // Bits 0:0
      UINT8 Write   : 1;  // Bits 1:1
      UINT8 Size    : 1;  // Bits 2:2
      UINT8 Pending : 1;  // Bits 3:3
      UINT8         : 4;  // Bits 7:4
    } Bits;
    UINT8 Data;
  } Flags;
  UINT16 Offset;
  UINT32 Data;
} REGISTER_CACHE_OFFSET_STRUCT;

typedef union {
  struct {
    UINT32 Frequency :  16;
    UINT32 DdrType   :  2;
    UINT32 RttWr     :  8;
    UINT32 Spare     :  6;
  } Bits;
  UINT32 Data;
} MRC_POWER_SYS_CONFIG;

typedef struct {
  INT32 Intercept;
  INT32 FirstOrder;
  INT32 SecondOrder;
  INT32 Interactions[MaxTxPowerParam];
} MRC_POWER_COEFF;

typedef struct {
  MRC_POWER_SYS_CONFIG  Config;
  UINT32                Intercept0;
  MRC_POWER_COEFF       Coeff[MaxTxPowerParam];
} MRC_RSM_POWER_FORMULA;

typedef struct {
  UINT8  Param;
  UINT16 ParamLimit[MarginLimitMax];
} MrcUpmPwrRetrainLimits;

// @todo: <CNL> MAX_DYNAMIC_FREQ
typedef struct {
  UINT8  Param;
  INT8   Limits[2];         // Start,Stop
  INT8   SaGvLimits[2];     // Start,Stop (low frequency point)
  INT8   MaxPerfLimits[2];  // Start,Stop (DT/Halo - MAX Performance point)
} MrcOptParamsLimits;

extern const MrcUpmPwrRetrainLimits InitialLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS];

typedef union {
  MrcUpmPwrRetrainLimits *Pointer;
  UINT64                 Data;
} MrcUPRLimitPtr;

///
///*****************************************
/// Output related "global data" structures.
///*****************************************
///
/// This data structure contains all the "global data" register cache values.
/// The following are memory controller level definitions.
///
typedef struct {
//  UINT32                       CurrentSequence;
//  UINT32                       NextSequence;
  UINT16                       MaxValid;
  BOOLEAN                      Overflow;
  REGISTER_CACHE_OFFSET_STRUCT Data[MAX_REGISTER_CACHE_ENTRIES];
} MRC_REGISTER_CACHE;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are memory channel level definitions.
///
typedef struct {
  UINT8 ClkPiCode[MAX_RANK_IN_CHANNEL]; ///< Clk Pi Code
  UINT8 CtlPiCode[MAX_RANK_IN_CHANNEL]; ///< Ctl Pi Code
  UINT8 CkePiCode[MAX_RANK_IN_CHANNEL]; ///< Ctl Pi Code
  UINT8 CmdPiCode[MAX_COMMAND_GROUPS];  ///< CmdPiCode CR, per group
} MrcIntCmdTimingOut;

///
/// This data structure contains DDRIO parameters that are clock aligned such that when clock is shifted,
/// these parameters must be shifted as well.  Usage of MRC_UINT16_MAX value means the structure is uninitialized.
///
typedef struct {
  UINT16  RcvEn;
  UINT16  TxDqs;
  UINT16  TxDq;
  BOOLEAN Valid;
} MrcIntClkAlignedParam;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
///
typedef struct {
  MrcIntCmdTimingOut    CmdTiming[MAX_CHANNEL];
  MrcIntClkAlignedParam IntClkAlignedMargins[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT16                CaVref[MAX_CHANNEL];           ///< Specifies CaVref per Channel for DDR4.
  MRC_REGISTER_CACHE    RegisterCache;
  BOOLEAN               MrcRxPbdSaturated[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN               MrcTxPbdSaturated[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
} MrcIntControllerOut;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are Cmd Slew rate data that calculated in DDR Scomp Init step.
///
typedef struct {
  UINT8      BufferSegmentDelayCmd;  ///< BufferSegmentDelay for Cmd
  UINT8      MinChainLengthCmd;    ///< MinChainLenght of Cmd Delay Cells
  UINT8      MaxChainLengthCmd;    ///< MaxChainLenght of Cmd Delay Cells
} MrcCmdSRData;

///
/// The following are system level definitions. All memory controllers in the system are set to these values.
///
typedef struct {
  UINT32                      Size;                         ///< The size of this structure. Must be the first entry in this structure.
  MrcIntControllerOut         Controller[MAX_CONTROLLERS];  ///< Memory controller specific output variables.
  MrcUPRLimitPtr              UpmPwrRetrainLimits;          ///< Pointer to Global UPM/PWR/RETRAIN Limits on the stack the size of MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS
  const MRC_RSM_POWER_FORMULA *SysTxPowerFormula;           ///< Pointer to System Tx Power Formula.
  const MRC_RSM_POWER_FORMULA *SysRxPowerFormula;           ///< Pointer to System Rx Power Formula.
  MrcSaGvPoint                SaGvPoint;                    ///< SA GV point - Low or High
  MrcCmdSRData                CmdSRData;                    ///< Cmd SR data.
  UINT16                      MaxRdDataValid;               ///< Used to track the maximum RdDataValid delay across all Frequency Points, (Sub)Channels, and Ranks.
  BOOLEAN                     SkipZq;                       ///< Skip ZQ Cal in SetupIoTest
  BOOLEAN                     CmdMirrored;                  ///< Current state of Command Mirroring.
  UINT8                       TestStopMode;                 ///< Contains the current test mode for the training engine (MRC_TEST_STOP_TYPE).c
  UINT16                      ResistanceDynamicLeg;         ///< Resistance of a single dynamic leg
  UINT16                      ResistanceStaticLeg;          ///< Resistance of a single static leg
  UINT8                       SubChEngCount;                ///< Number of valid CPGC/CADB engines that exist within each Channel.
  UINT8                       ChSubChMaskEnable;            ///< BitMask of which CPGC/CADB engines to setup. For ICL, this means Bit 0 = Ch0Sub0, Bit 1 = Ch0Sub1, Bit 2 = Ch1Sub0, Bit 3 = Ch1Sub1
  UINT8                       ClkDcc[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_DCC_CLOCK_PI];         ///< Look Up Table for CLK DCC per CLK PI setting
  UINT8                       ClkDccAipCb[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_DCC_CLOCK_PI];    ///< Look Up Table for DccAipCb per CLK PI setting
  UINT8                       DqsDcc[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_DCC_TX_DQS_DQ_PI];       ///< Look Up Table for DQS DCC per DQS PI setting
  UINT8                       DqsDccAipCb[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_DCC_TX_DQS_DQ_PI];  ///< Look Up Table for DqsDccAipCb per DQS PI setting
  BOOLEAN                     ClkDccInit;                   ///< Whether the Look Up Table for CLK DCC is populated with correct data
  BOOLEAN                     DqsDccInit;                   ///< Whether the Look Up Table for DQS DCC is populated with correct data
  UINT32                      LastDccRun;                   ///< Stores the last usage of DCC FSM: DCC_ACTIVE_CLK / DCC_ACTIVE_DATA / DCC_ACTIVE_BOTH
  UINT32                      PeiServices;
} MrcIntOutput;

#pragma pack (pop)
#endif
