/** @file
  This file include all the MRC common data.

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
#ifndef _MrcCommon_h_
#define _MrcCommon_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcIoControl.h"
#include "McAddress.h"
#include "MrcReset.h"
#include "MrcCrosser.h"
#include "MrcDebugPrint.h"
#include "Cpgc20.h"

///
/// Defines and types.
///

///
/// Convert rank to dimm number
///
#ifndef RANK_TO_DIMM_NUMBER
#define RANK_TO_DIMM_NUMBER(Rank) ((Rank) / 2)
#endif

///
/// Convert DIMM number to a rank bitmask, assuming 2 ranks per DIMM
///
#ifndef DIMM_TO_RANK_MASK
#define DIMM_TO_RANK_MASK(Dimm) (3 << (2 * (Dimm)))
#endif

///
/// Bit operation commands
///
#ifndef MRC_MASK
#define MRC_MASK(offset, width) (((1 << width) - 1) << (offset))
#endif

#ifndef MRC_MASK_NOT
#define MRC_MASK_NOT(offset, width) (~(MRC_MASK (offset, width)))
#endif

#ifndef MRC_CR_UPDATE
#define MRC_CR_UPDATE(Register, Offset, Width, Value) \
        (((Register) & MRC_MASK_NOT (Offset, Width)) | ((Value) << (Offset)))
#endif

#ifndef MRC_CR_DUMP
#define MRC_CR_DUMP(Register, offset, Width)\
        (((Register) & (MRC_MASK(offset, Width))) >> offset)
#endif

#define BER_TARGET              4
#define BER_LOG_TARGET          7             ///< MRC_Log8(BER_TARGET) = 7
#define BER_ERROR_MASK          0xFFFF00FF

/// Self Refresh State Defines
#define MRC_SR_ENTER  (1)
#define MRC_SR_EXIT   (0)

/// Early Read Time Centering 2D Traffic Modes
#define ERTC2D_NORMAL (0)
#define ERTC2D_MPR    (1)

///
/// Cache line size in chunks
///
#define CACHE_LINE_SIZE (8)

///
/// Number of cache lines in WDB
///
#define WDB_NUM_CACHE_LINES (64)

#define OFFSET_CALC_CH(CH0, CH1, CH) (((CH0) + (((CH1) - (CH0)) * (CH))))
#define OFFSET_CALC_CH_SUBCH(CH0, CH1, CH, SUBCH1, SUBCH) (((CH0) + (((CH1) - (CH0)) * (CH)) + (((SUBCH1) - (CH0)) * (SUBCH))))

typedef enum {
  dDIMM0= 0,
  dDIMM1
} MrcDimmType;

typedef enum {
  cCHANNEL0 = 0,
  cCHANNEL1
} MrcChannelType;

typedef enum {
  rRank0    = 0,
  rRank1,
  rRank2,
  rRank3
} MrcRank;

typedef enum {
  ssOne     = 0,
  ssTwo,
  ssThree,
  ssFour
} TSubSequencesNumber;

///
/// Define ECC mode.
///
typedef enum {
  emNoEcc,
  emEccIoActive,
  emEccLogicActive,
  emBothActive
} TEccModes;

///
/// Raw card list
///
typedef enum {
  rcA,
  rcB,
  rcC,
  rcD,
  rcE,
  rcF,
  rcG,
  rcH,
} TRawCard;

///
/// Reut Addressing Parameters
///
typedef enum {
  MrcReutFieldRank,
  MrcReutFieldBank,
  MrcReutFieldRow,
  MrcReutFieldCol,
  MrcReutFieldMax   ///< This must be the last entry in the enum.
} MrcReutField;

typedef enum {
  MrcPatSrcStatic,                ///< Pattern Buffer
  MrcPatSrcDynamic,               ///< LFSR
  MrcPatSrcAllZeroes,             ///< DC zero
  MrcPatSourceMax
} MRC_PAT_SRC_TYPE;

typedef enum {
  BasicVA = 0,                    ///< Use 2 LFSR VicAggressor pattern with rotation of 10 bits
  CADB,                           ///< Do CADB on command/address bus and LMN VA on DQ (power supply noise)
  TurnAround,
  LMNVa,                          ///< Use (LMN aggressor + LFSR Victim) with rotation of 10 bits
  TurnAroundRW,                   ///< Single SSQ test WR-RD and with RankInc 1
  TurnAroundWR,                   ///< Run 8 tests, one for each subsequence with RankIncRate = 1/2/2/2/2/2/2/1
  TurnAroundODT,                  ///< Run 4 tests, one for each subsequence with RankIncRate = 1/2/1/2
  CADBCol,
  CADBRow,
  RdRdTA,                         ///< Run 2 tests, one with Trdrd=4 and one with Trdrd=5
  RdRdTA_All,                     ///< Run 8 tests, Covering tRDRD_sr 4,5,6,7 and tRDRD_dr = Min,+1,+2,+3
  StaticPattern                   ///< We are running a test that uses a static pattern.
} MrcDqPat;

typedef enum {
  NSOE = 0,                       ///< Never Stop On Any Error
  NTHSOE,                         ///< Stop on the Nth Any Lane Error
  ABGSOE,                         ///< Stop on All Byte Groups Error
  ALSOE                           ///< Stop on All Lanes Error
} MRC_TEST_STOP_TYPE;

///
/// CADB commands (Bit 0: WE#, Bit 1: CAS#, Bit 2: RAS#, Bit 3(DDR4-only): ACT#)
///
#define MRS_CMD                             0
#define REF_CMD                             1
#define PRE_CMD                             2
#define ACT_CMD                             3
#define WR_CMD                              4
#define RD_CMD                              5
#define ZQ_CMD                              6
#define NOP_CMD                             7
#if (SUPPORT_DDR4 == SUPPORT)
#define DDR4_MRS_CMD                        8
#define DDR4_REF_CMD                        9
#define DDR4_PRE_CMD                        0xA
#define DDR4_WR_CMD                         0xC
#define DDR4_RD_CMD                         0xD
#define DDR4_ZQ_CMD                         0xE
#define DDR4_NOP_CMD                        0xF
#endif // SUPPORT_DDR4

///
/// REUT Init modes
///
#define Idle_Mode                           0
#define REUT_Testing_Mode                   1
#define MRS_Mode                            2
#define NOP_Mode                            3  ///< Normal Operation Mode

///
/// REUT CmdPattern
///
#define PatWrRd                             0
#define PatWr                               1
#define PatRd                               2
#define PatRdWrTA                           3
#define PatWrRdTA                           4
#define PatODTTA                            5
#define DimmTest                            6
#define PatCADBCol                          7
#define PatCADBRow                          8
#define PatRdEndless                        9
#define PatWrScrub                          10

///
/// REUT Subsequence types
///
#define BRd                                 0
#define BWr                                 1
#define BRdWr                               2
#define BWrRd                               3
#define ORd                                 4
#define OWr                                 5

///
/// WDB Patterns
///
#define BASIC_VA_PATTERN_SPRED_8  0x01010101

///
/// Margin params
///
/**
 1D Margin Types:
  RcvEn:    Shifts just RcvEn.  Only side effect is it may eat into read dq-dqs for first bit of burst.
  RdT:      Shifts read DQS timing, changing where DQ is sampled.
  WrT:      Shifts write DQ timing, margining DQ-DQS timing.
  WrDqsT:   Shifts write DQS timing, margining both DQ-DQS and DQS-CLK timing.
  RdV:      Shifts read Vref voltage for DQ only.
  WrV:      Shifts write Vref voltage for DQ only.
  WrLevel:  Shifts write DQ and DQS timing, margining only DQS-CLK timing.
  WrTBit:   Shifts write DQ per bit timing.
  RdTBit:   Shifts read DQ per bit timing.
  RdVBit:   Shifts read DQ per bit voltage.
  RcvEnaX:  Shifts RcvEn in multiples of 4PI.
  WrTLp4:   Shifts Write DQ as an offset from Write DQS+500ps in multiples of 5 PI Ticks.
  CmdT:     Shifts CMD/CTL timing. Can be implemented as shifting CLK and DATA, instead of multiple CMD / CTL PI's
  CmdV:     Shifts CMD Vref
  RdTN:     Shifts read DQS-N timing, changing where DQ is sampled.
  RdTP:     Shifts read DQS-P timing, changing where DQ is sampled.

 2D Margin Types (Voltage, Time)
  RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
  WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
  RdFan3:  Margins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }

**/
 typedef enum {
  RcvEna = 0,
  RdT,
  WrT,
  WrDqsT,
  RdV,
  WrV,
  WrLevel,
  WrTBox,
  WrTBit,
  RdTBit,
  RdVBit,  ///< 10
  RcvEnaX,
  WrTLp4,
  CmdT,
  CmdV,
  RdFan2 = 16,
  WrFan2 = 17,
  RdFan3 = 32,
  WrFan3 = 33,
  RdTN,
  RdTP,
  MarginTypeMax
} MRC_MarginTypes;

typedef enum {
  OptWrDS = 0,
  OptSComp,
  OptTxTco,
  OptClkTco,
  OptTCompOff,
  OptTxEq,
  OptRdOdt,
  OptRxEq,
  OptRxBias,
  OptRxRComp,
  OptRxCb,
  OptDimmOdt,
  OptDimmOdtWr,
  OptDimmOdtNom,
  OptDimmOdtNomNT,
  OptDimmOdtPark,
  OptDimmOdtParkNT,
  OptDimmOdtComb,
  OptDimmOdtCA,
  OptDimmRon,
  OptWrDSUp,
  OptWrDSDn,
  OptWrDSUpCoarse,
  OptWrDSDnCoarse,
  OptRdOdtUp,
  OptRdOdtDn,
  OptCmdDS,
  OptCtlDS,
  OptClkDS,
  OptRxBiasCb, //param0=RxBias param1=RxCb
  OptTxEqWrDS, //param0=TxEq param1=WrDS
  OptCmdTxEq,
  OptCmdSComp,
  OptCmdSCompOffset,
  OptTxTcoDqsP,
  OptTxTcoDqsN,
  OptDimmSocOdt,
  OptDqDfeMode,
  OptDqDfeDly,
  OptDqDfeCoeff,
  OptDefault
} TOptParamOffset;

typedef enum {
  drrd2rd = 0,
  ddrd2rd,
  drwr2wr,
  ddwr2wr,
  drrd2wr,
  ddrd2wr,
  drwr2rd,
  ddwr2rd,
  rdodtd,
  wrodtd,
  mcodts,
  mcodtd,
  rtl
} TOptParamTAT;

#define RXF_SELECT_RC_100  (6)
#define RXF_SELECT_RC_133  (4)
#define RXF_SELECT_MIN     (0)
#define RXF_SELECT_MAX     (4)
#define RXF_SELECT_MAX_ULT (2)

///
/// Struct Definitions
///
#pragma pack (push, 1)
typedef union {
  struct {
    UINT32 Enable_2x_Refresh                       :  1;  // Bits 0:0
    UINT32 LPDDR_Min_MR4                           :  3;  // Bits 1:3
    UINT32                                         :  27; // Bits 4:30
    UINT32 Lock_Bit                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MrcMailbox2xRefresh;

typedef struct {
  UINT16 Start[MrcReutFieldMax];   ///< (4, uint16)    // Rank, Bank, Row, Col
  UINT16 Stop[MrcReutFieldMax];    ///< (4, uint16)    // Rank, Bank, Row, Col
  UINT8  Order[MrcReutFieldMax];   ///< [4, uint8)     // Rank, Bank, Row, Col
  UINT32 IncRate[MrcReutFieldMax]; ///< (4, unit32)    // Rank, Bank, Row, Col
  UINT16 IncVal[MrcReutFieldMax];  ///< (4, unit16)    // Rank, Bank, Row, Col
} MRC_REUTAddress;

typedef struct {
  CPGC20_ADDRESS_INCREMENT_ORDER  AddrIncOrder;
  CPGC20_ADDRESS_DIRECTION        AddrDirection;
  UINT8                           LastValidAddr; // Number > Max Address Instructions means no Last set
  UINT32                          RowStart;
  UINT16                          ColStart;
  UINT8                           RowSizeBits;
  UINT8                           ColSizeBits;
  UINT8                           BankSize;
} Cpgc20Address;

typedef struct {
  MRC_PAT_SRC_TYPE PatSource;       ///< Defines the source of patterns: Static, Dynamic, All Zeroes (DC)
  UINT16 IncScale;
  UINT16 IncRate;                   ///< How quickly the pattern changes: WDB walks through cachelines, or PG rotates.  This is a linear count.
  UINT8  Start;                     ///< Starting pointer
  UINT8  Stop;                      ///< Stopping pointer
  UINT8  DQPat;                     ///< The Pattern type for the test.  See MrcDqPat.
  BOOLEAN EnableXor;                ///< Enables Xor'ing of pattern sources if available.
} MRC_PATTERN_CTL;

typedef struct {
  UINT8 BankGroup;
  UINT8 Bank;
} MRC_BG_BANK_PAIR; ///< Logical struct of BankGroup and Banks.
#pragma pack (pop)

typedef struct {
  UINT8 TimingType;
  INT8 TimingMargin;
  UINT8 VoltageType;
  INT8 VoltageMargin;
} MarginCheckPoint;

///
/// External Global constants
///
#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
#endif

extern MRC_BG_BANK_PAIR Ddr4RdMprBankL2p[2];
extern MRC_BG_BANK_PAIR Ddr4x8BankMapB2B[MAX_DDR4_x8_BANKS];
extern MRC_BG_BANK_PAIR Ddr4x16BankMapB2B[MAX_DDR4_x16_BANKS];

///
/// MRC common functions
///

/**
  Verify that the indicated socket is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.

  @retval Success if present and enabled, otherwise SocketNotSupported.
**/
extern
MrcStatus
IsSocketPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket
  );

/**
  Verify that the indicated controller is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.

  @retval Success if present and enabled, otherwise ControllerNotSupported.
**/
extern
MrcStatus
IsControllerPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller
  );

/**
  Verify that the indicated channel is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.

  @retval Success if present and enabled, otherwise ChannelNotSupported.
**/
extern
MrcStatus
IsChannelPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel
  );

/**
  Verify that the indicated DIMM is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.

  @retval Success if present and enabled, otherwise DimmNotSupported.
**/
extern
MrcStatus
IsDimmPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm
  );

/**
  Verify that the indicated rank is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.
  @param[in] Rank       - Zero based memory rank number in the DIMM.

  @retval Success if present and enabled, otherwise RankNotSupported.
**/
extern
MrcStatus
IsRankPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm,
  const UINT32                Rank
  );


/**
  Set ideal Dimm Write Vref for DDR4 assuming CPU Ron and Dimm termination.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to setup
  @param[in]      RankBitMask - Rank bit mask to setup
  @param[in]      Byte        - Byte to setup (for PDA mode only)
  @param[in]      CpuRon      - CPU Ron value in Ohm
  @param[in]      OdtWr       - Write DIMM Odt value in Ohm
  @param[in]      DimmOdt     - Equ. DIMM Odt value in Ohm

  @retval none
**/
void
MrcSetIdealTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       RankBitMask,
  UINT8                       Byte,
  UINT32                      CpuRon,
  UINT32                      OdtWr,
  UINT32                      DimmOdt
  );

/**
  This function is used to calculate Vref or VSwing of a generic voltage divider.
  ReceiverOdt must be non-Zero, or exceptions occurs.
  VSS, the voltage level the PullDown is attached to, is assumed to be 0.

  @param[in]  MrcData         - Pointer to global data structure.
  @param[in]  DriverPullUp    - Used to calculate Vhigh.  Value in Ohms.
  @param[in]  DriverPullDown  - Used to calculate Vlow.  Value in Ohms.
  @param[in]  ReceiverOdt     - Value in Ohms.
  @param[in]  Vdd             - Voltage level PullUp is tied to.  Must be the same unit size as Vtermination.
  @param[in]  Vtermination    - Voltage level ReceiverOdt is tied to.  Must be the same unit size as Vdd.
  @param[in]  IsVref          - Boolean to select Vref or Vswing calculation.

  @retval - Vref in units of Vdd/Vterm
**/
UINT32
MrcCalcGenericVrefOrSwing (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN  UINT32                Vdd,
  IN  UINT32                Vtermination,
  IN  BOOLEAN               IsVref
  );

/**
  This function is used to gather current system parameters to pass to the function,
  which calculates the ideal Read/Write/Command Vref.  It will return the result to the caller.

  @param[in]  MrcData         - Pointer to global data structure.
  @param[in]  DriverPullUp    - Used to calculate Vhigh.  Value in Ohms.
  @param[in]  DriverPullDown  - Used to calculate Vlow.  Value in Ohms.
  @param[in]  ReceiverOdt     - Value in Ohms.
  @param[in]  VrefType        - MRC_MarginTypes: WrV, CmdV, RdV.
  @param[in]  Print           - Boolean switch to print the results and parameters.

  @retval - Vref in units of mV
**/
UINT32
MrcCalcIdealVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN  MRC_MarginTypes       VrefType,
  IN  BOOLEAN               Print
  );

/**
  This function will program the ideal Rx Vref to all the bytes in the Channel.
  Channel here denotes a 64-bit bus.  It will not program Bytes that aren't present,
  in the case of Sub-Channels.

  It has two phases:
    Calculate Vref based on parameters passed to the function.
    Enocde the Vref calculated into the CPU register format and program the register.

  Two parameters are determined inside the function stack:
    Vdd,
    Vtermination

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  Channel   - Channel to program.
  @param[in]  PrintMsg  - Boolean switch to enable debug printing.

  @retval none
**/
VOID
MrcSetIdealRxVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN BOOLEAN                PrintMsg
  );

/**
  Set default CPU Read Vref for DDR4 assuming CPU uses Vddq termination.
  Use default CPU ODT and DIMM Ron values.

  @param[in, out] MrcData      - Include all MRC global data.
  @param[in]      GetFromTable - Get the DIMM ODT parameters from the initial table.
  @param[in]      PrintMsg     - Enable debug prints

  @retval none
**/
extern
void
MrcSetDefaultRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN         GetFromTable,
  IN     BOOLEAN         PrintMsg
  );

/**
  Return the rank mask in channel if rank exist exist.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Rank    - Rank to check.
  @param[in] Channel - Channel to work on.

  @retval Bit mask of Rank requested if the Rank exists in the system.
**/
extern
UINT8
MrcRankInChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT32         Rank,
  IN const UINT32         Channel
  );

/**
  Checks if a given sub-channel is populated in a given channel

  @param[in] MrcData    - Pointer to MRC global data.
  @param[in] Channel    - Channel to work on.
  @param[in] SubChannel - Sub-Channel to work on.

  @retval TRUE if exists, FALSE otherwise.
**/
extern
BOOLEAN
MrcSubChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         SubChannel
  );

/**
  This function checks if the requested byte in the channel exists.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Channel - Channel to check.
  @param[in]  Byte    - Byte to check.

  @retval BOOLEAN - TRUE if exists, FALSE otherwise.
**/
BOOLEAN
MrcByteInChannelExist (
  IN  MrcParameters *const  MrcData,
  IN  const UINT32          Channel,
  IN  const UINT32          Byte
  );

/**
  Return the number of ranks in specific dimm.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Dimm    - Dimm in channel to return.

  @retval The number of ranks in the dimm.
**/
extern
UINT8
MrcGetRankInDimm (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const UINT8          Channel
  );

/**
  Returns whether Channel is or is not present.

  @param[in] Outputs - Pointer to MRC global Output data.
  @param[in] Channel - Channel to test.

  @retval TRUE  - if there is at least one enabled DIMM in the channel.
  @retval FALSE - if there are no enabled DIMMs in the channel.
**/
extern
BOOLEAN
MrcChannelExist (
  IN const MrcOutput *const Outputs,
  IN const UINT32           Channel
  );

/**
  This function disable channel parameters.
  After this function the MRC don't use with the channel.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] ChannelToDisable  - Channel to disable.
  @param[in] SkipDimmCapacity  - Switch to skip setting the DimmCapacity to 0 for the dimms in the channel disabled.

  @retval Nothing
**/
extern
void
MrcChannelDisable (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChannelToDisable,
  IN const UINT8          SkipDimmCapacity
  );

/**
  This function implements the flow to properly switch MC PLL during run time.

  @params[in] MrcData     - Pointer to MRC global data.
  @params[in] NewFreq     - The new frequency to lock MC PLL.
  @params[in] DebugPrint  - Boolean parameter to enable/disable debug messages for the callee.

  @retval MrcStatus - mrcSuccess if frequency is updated properly, otherwise an error status.
**/
MrcStatus
MrcFrequencySwitch (
  IN  MrcParameters *const  MrcData,
  IN  MrcFrequency          NewFreq,
  IN  BOOLEAN               DebugPrint
  );

/**
  Convert the given frequency and reference clock to a clock ratio.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] RefClk    - The memory reference clock.
  @param[in] BClk      - The base system reference clock.

  @retval Returns the memory clock ratio.
**/
extern
MrcClockRatio
MrcFrequencyToRatio (
  IN MrcParameters *const  MrcData,
  IN const MrcFrequency    Frequency,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  );

/**
  Convert the given ratio and reference clocks to a memory frequency.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Ratio   - The memory ratio.
  @param[in] RefClk  - The memory reference clock.
  @param[in] BClk    - The base system reference clock.

  @retval Returns the memory frequency.
**/
extern
MrcFrequency
MrcRatioToFrequency (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  );

/**
  Convert the given ratio and reference clocks to a memory clock.

  @param[in] Ratio  - The memory ratio.
  @param[in] RefClk - The memory reference clock.
  @param[in] BClk   - The base system reference clock.

  @retval Returns the memory clock in femtoseconds.
**/
extern
UINT32
MrcRatioToClock (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
);

/**
  This function determines the number of PI ticks required to cover the delay requested.
  This function will ceiling the result such that the PI tick delay may be greater
  than the requested time.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  TimeFs  - The delay in Femptoseconds to convert to PI ticks.

  @retval UINT32 - The number of PI ticks to reach the delay requested.
**/
UINT32
MrcPicoSec2PiTick (
  IN  MrcParameters *const  MrcData,
  IN  const UINT32          TimeFs
  );

/**
  This function return the DIMM number according to the rank number.

  @param[in] Rank - The requested rank.

  @retval The DIMM number.
**/
extern
UINT8
MrcGetDimmFromRank (
  IN const UINT8 Rank
  );

/**
  This function sets the memory frequency.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] DebugPrint - Enable/disable debug printing

  @retval mrcSuccess on success, mrcFrequencyError on error.
**/
extern
MrcStatus
McFrequencySet (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              DebugPrint
  );

/**
  Returns the extrapolated margin to a fixed # of errors (logT)
  vrefpass is 10x the first passing margin (with no errors) (10x used for int math)
  Errors at vrefpass/10+1 = log1
  Errors at vrefpass/10+2 = logT

  @param[in]      vrefpass      - 10x the first pass margin (w/no errors) (10x used for int match)
  @param[in]      errLog_1      - Errors at vrefpass/10+1
  @param[in]      errLog_2      - Errors at vrefpass/10+2
  @param[in]      errLog_Target - Error target determines extrapolation vs interpolation
  @param[in, out] *berStats     - Used to track interpolation vs extrapolation or if the slope is non-monotonic.
                                  NOTE: target would be Interpolation only

  @retval Interpolated/Extrapolated vref with the scale increased by 10.
**/
extern
UINT32
interpolateVref (
  IN     UINT32  vrefpass,
  IN     UINT32  errLog_1,
  IN     UINT32  errLog_2,
  IN     UINT32  errLog_Target,
  IN OUT UINT32  *berStats
  );

/**
  This function swaps a subfield, within a 32 bit integer value with the specified value.

  @param[in] CurrentValue - 32 bit input value.
  @param[in] NewValue     - 32 bit New value.
  @param[in] Start        - Subfield start bit.
  @param[in] Length       - Subfield length in bits/

  @retval The updated 32 bit value.
**/
extern
UINT32
MrcBitSwap (
  IN UINT32    CurrentValue,
  IN const UINT32 NewValue,
  IN const UINT8  Start,
  IN const UINT8  Length
  );

/**
  This function returns the maximim Rx margin for a given Channel, Rank(s), and byte.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Test parameter.
  @param[in] Channel   - Channel to calculate max Rx margin.
  @param[in] RankRx    - Rank index.  0xFF causes all ranks to be considered.
  @param[in] Byte      - Byte to check.
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.

  @retval The max Rx margin, either MaxMargin or value from stored margins.
**/
extern
UINT8
MrcCalcMaxRxMargin (
  IN MrcParameters  *const MrcData,
  IN UINT8                 Param,
  IN const UINT8           Channel,
  IN const UINT8           RankRx,
  IN const UINT8           Byte,
  IN const UINT8           Sign,
  IN UINT16                MaxMargin
  );

/**
  This function returns the maximim Vref margin for a given Channel if WrV.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Channel   - Channel to calculate max Tx margin.
  @param[in] RankTx    - Rank Mask for DDR4.
  @param[in] Byte      - Zero based byte number.
  @param[in] Param     - Parameter of Vref to use
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.
  @param[in] Pda       - Use PDA or not.

  @retval The max Vref margin, either MaxMargin or value from stored margins.
**/
extern
UINT8
MrcCalcMaxVrefMargin (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           RankTx,
  IN const UINT8           Byte,
  IN const UINT8           Param,
  IN const UINT8           Sign,
  IN UINT8                 MaxMargin,
  IN BOOLEAN               Pda
  );

/**
  This function determines if a bit lane[0-7] has seen a pass and a fail in each byte for all channels populated.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] chBitmask - Bit mask of channels to consider.
  @param[in] OnePass   - Array of Bit masks marking DQ lanes has had a passing value.
  @param[in] OneFail   - Array of Bit masks marking DQ lanes has had a failing value.

  @retval The AND result of each Channel/byte for OnePass and OneFail.
**/
extern
UINT8
MrcAndBytes (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitmask,
  IN UINT8                OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT8                OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  );

/**
  This function Finds the margin for all channels/all bits. The margin sweep is a parameterized
  Assume REUT test has already been fully setup to run
  This will unscale the results such that future tests start at the correct point
  Uses ChangeMargin function to handle a variety cases (Timing, Voltage, Fan, etc.)

  @param[in]     MrcData    - Include all MRC global data.
  @param[in]     chBitMask  - Channel BIT mask for Channel(s) to work on
  @param[in]     Rank       - Rank to work on
  @param[in,out] marginbit  - used as the return data ( real margin measurement, no 10x)
                              marginbit[ch,byte,bit,sign] = abs(Margin)
                              Note: If param == RdTBit/RdVBit/WrVBit, marginbit is also the starting point
  @param[in,out] marginbyte - provides the starting point on a per byte basis (still 10x)
  @param[in]     param      - defines the margin type
  @param[in]     mode       - allows for different types of modes for margining
                              {Bit0: PhLock (keep all bytes within in ch in phase),
                               Bit1: Ch2Ch Data out of phase (LFSR seed)
                               Bits 15:2: Reserved}
  @param[in]     MaxMargin  - Default Maximum margin
  @param[in]     MsgPrint   - Show debug prints


  @retval mrcSuccess if successful, otherwise it returns an error status.
**/
extern
MrcStatus
MrcGetMarginBit (
  IN     MrcParameters *const MrcData,
  IN     UINT8                chBitMask,
  IN     UINT8                Rank,
  IN OUT UINT32               marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES],
  IN OUT UINT32               marginbyte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                param,
  IN     UINT16               mode,
  IN     UINT8                MaxMargin,
  IN     BOOLEAN              MsgPrint
  );

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
    mode is {Bit0: PhLock (keep all bytes within in ch in phase),
             Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginByte is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData    - The global MrcData
  @param[in,out] marginByte - Data structure with the latest margin results
  @param[in]     chBitmask  - Bit mask of present channels
  @param[in]     RankIn     - Rank to change margins for
  @param[in]     RankRx     - Ranks for Rx margin
  @param[in]     param      - parameter to get margins for
  @param[in]     mode       - allows for different types of modes for margining:
  @param[in]     BMap       - Byte mapping to configure error counter control register
  @param[in]     EnBER      - Enable BER extrapolation calculations
  @param[in]     MaxMargin  - Max Margin allowed for the parameter
  @param[in]     Interior   - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats   - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
MrcGetBERMarginByte (
  IN     MrcParameters * const MrcData,
  IN OUT UINT32          marginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8           chBitmask,
  IN     UINT8           RankIn,
  IN     UINT8           RankRx,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           *BMap,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  );

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
  mode is {Bit0: PhLock (keep all bytes within in ch in phase),
  Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginCh is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData   - The global MrcData
  @param[in,out] marginCh  - Data structure with the latest margin results
  @param[in]     chBitmask - Bit mask of present channels
  @param[in]     RankRx    - Ranks for Rx margin
  @param[in]     RankIn    - Rank to change margins for
  @param[in]     param     - parameter to get margins for
  @param[in]     mode      - allows for different types of modes for margining:
  @param[in]     EnBER     - Enable BER extrapolation calculations
  @param[in]     MaxMargin - Max Margin allowed for the parameter
  @param[in]     Interior  - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
MrcGetBERMarginCh (
  IN     MrcParameters   *MrcData,
  IN     UINT32          marginCh[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN OUT UINT8           chBitmask,
  IN     UINT8           RankRx,
  IN     UINT8           RankIn,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  );

  /**
  Check whether there is errors at Point RdT/RdV or WrT/WrV

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      chBitmask   - Bit mask of present channels
  @param[in]      RankMask    - Bit mask of Ranks to change margins for
  @param[in]      MarginPoint - Margin Point to test

  @retval MrcStatus - mrcSuccess if point successful pass, otherwise returns an error status.
**/
extern
MrcStatus
MrcDataPointTest (
  IN     MrcParameters     *MrcData,
  IN     UINT8             chBitMask,
  IN     UINT8             RankMask,
  IN     MarginCheckPoint  *MarginPoint
  );

/**
  Check whether there is errors at Point CmdT/CmdV

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      chBitmask   - Bit mask of present channels
  @param[in]      RankMask    - Bit mask of Ranks to change margins for
  @param[in]      GroupMask   - Which groups to work on for CLK/CMD/CTL. Up to 4 CMD for LPDDR4.  Up to 5 CMD for DDR4.
  @param[in]      MarginPoint - CMD Margin Point to test

  @retval MrcStatus - mrcSuccess if point successful pass, otherwise returns an error status.
**/
extern
MrcStatus
MrcCmdPointTest (
  IN     MrcParameters    *MrcData,
  IN     UINT8            chBitMask,
  IN     UINT8            RankMask,
  IN     UINT8            GroupMask,
  IN     MarginCheckPoint *MarginPoint
  );

/**
  This function shifts a 32 bit int either positive or negative

  @param[in] Value       - Input value to be shifted
  @param[in] ShiftAmount - Number of bits places to be shifted.

  @retval 0 if ShiftAmount exceeds +/- 31.  Otherwise the updated 32 bit value.
**/
extern
UINT32
MrcBitShift (
  IN const UINT32 Value,
  IN const INT8  ShiftAmount
  );

/**
  This function Sign extends OldMSB to NewMSB Bits (Eg: Bit 6 to Bit 7)

  @param[in] CurrentValue - Input value to be shifted
  @param[in] OldMSB       - The original most significant Bit
  @param[in] NewMSB       - The new most significant bit.

  @retval The updated 8 bit value.
**/
extern
UINT8
MrcSE (
  IN UINT8     CurrentValue,
  IN const UINT8  OldMSB,
  IN const UINT8  NewMSB
  );

/**
  This function calculates the Log base 2 of the value to a maximum of Bits

  @param[in] Value - Input value

  @retval Returns the log base 2 of input value
**/
extern
UINT8
MrcLog2 (
  IN const UINT32 Value
  );

/**
  This function calculates the power of integer numbers.

  @param[in] Value - Input value.
  @param[in] Power -

  @retval Returns power percentage
**/
UINT32
MrcPercentPower (
  IN const UINT32 Value,
  IN  UINT32 Power
  );

/**
  Adjust sense amplifier offset per bit correction.

  @param[in,out] MrcData         - Include all MRC global data.

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
MrcSenseAmpOffsetCorrection(
  IN OUT MrcParameters *const MrcData
);

/**
  This function search for item in a list and return index + 1 or 0 in not found

  @param[in] Param - Param to search for
  @param[in] ParamList - list of Params
  @param[in] ParamLen - Params length
  @param[in] Offset - list of the corresponded Offsets to work on
  @param[out] Override - override indicator
  @param[out] LocalOffset - localoffset
  @retval Returns result
**/
UINT8
MrcSearchList(
  IN           UINT8           Param,
  IN     const UINT8           *ParamList,
  IN     const UINT8           ParamLen,
  IN     const INT8            *Offset,
  OUT          BOOLEAN         *Override,
  OUT          INT8            *LocalOffset
);

/**
  ***** Has Buffer Overflow for 68-71, 544-575, 4352-4607, ... ****
  This function calculates the Log base 8 of the Input parameter using integers

  @param[in] Value - Input value

  @retval Returns 10x the log base 8 of input Value
**/
extern
UINT32
MrcLog8 (
  IN UINT32 Value
  );

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr     - Array to be sorted
  @param[in]     Channel - Channel to sort.
  @param[in]     lenArr  - Length of the array

  @retval Nothing
**/
extern
void
MrcBsortPerChannel (
  IN OUT UINT32   Arr[MAX_CHANNEL][4],
  IN     const UINT8 Channel,
  IN     const UINT8 lenArr
  );

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr    - Array to be sort
  @param[in]     lenArr - Lenght of the array

  @retval Nothing
**/
extern
void
MrcBsort (
  IN OUT UINT32 *const Arr,
  IN     const UINT8   lenArr
  );

/**
  This function calculates the Natural Log of the Input parameter using integers

  @param[in] Input - 100 times a number to get the Natural log from.
                      Max Input Number is 40,000 (without 100x)

  @retval 100 times the actual result. Accurate within +/- 2
**/
extern
UINT32
MrcNaturalLog (
  IN UINT32 Input
  );

/**
  This function calculates the number of bits set to 1 in a 32-bit value.

  @param[in] Input - The value to work on.

  @retval The number of bits set to 1 in Input.
**/
extern
UINT8
MrcCountBitsEqOne (
  IN UINT32 Input
  );

/**
  This function calculates e to the power of of the Input parameter using integers.

  @param[in] Input - 100 times a number to elevate e to.

  @retval 100 times the actual result. Accurate within +/- 2.
**/
extern
UINT32
Mrceexp (
  IN UINT32 Input
  );

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT32
MrcWriteCrMulticast (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  );

/**
  This function writes a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT64
MrcWriteCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT64  Value
  );

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
extern
UINT32
MrcWriteCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  );

/**
  This function writes a 8 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - The value to write.

  @retval The register value.
**/
extern
UINT8
MrcWriteCR8 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT8   Value
  );

/**
  This function reads a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register.
**/
extern
UINT64
MrcReadCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  );

/**
  This function reads a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register
**/
extern
UINT32
MrcReadCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  );

/**
  Wait for at least the given number of nanoseconds.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayNs   - time to wait in [ns], up to 2^32 [ns] = 4.29 seconds

  @retval Nothing
**/
extern
void
MrcWait (
  IN MrcParameters *const MrcData,
  IN UINT32               DelayNs
  );

/**
  This function forces an RCOMP.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
ForceRcomp (
  IN MrcParameters * const MrcData
  );

/**
  This function controls entering and exiting self refresh.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  SelfRef - Boolean selector to enter (1/TRUE) or exit (0/FALSE) Self Refresh.

  @retval MrcStatus - mrcSuccess if we are able to transition to the requested Self Refresh State
                    - mrcFail if we timeout before MC reports we reached the requested Self Refresh state.
**/
MrcStatus
MrcSelfRefreshState (
  IN  MrcParameters *const  MrcData,
  IN  BOOLEAN               SelfRef
  );

/**

  Fill WDB with the given fixed pattern.
  In Enhanced Channel Mode only entry [0] of each chunk will be used (low 32 bit).

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Pattern  - Array of chunks (64 bit), broken into two 32-bit entries (second dimension).
                        Length (first dimension) can be up to WDB size in chunks.

  @retval Nothing
**/
extern
void
WriteFixedPattern (
  IN MrcParameters *const MrcData,
  IN UINT32               Pattern[][2]
  );

/**
  This routine performs the following steps:
    Step 0: Iterate through all VicRots
    Step 1: Create a compressed vector for a given 32 byte cacheline
            Each byte has a value of LFSR0=AA/LFSR1=CC/LFSR2=F0
    Step 2: Expand compressed vector into chunks and 32 bit segments
    Step 3: Program the pattern into the Pattern Generator

  Note: This function requires that MrcSelectEngines() has been called.

  @param[in] MrcData - Include all MRC global data.
  @param[in] vmask   - 32 bit victim mask.  1 indicates this bit should use LFSR0
  @param[in] amask   - 32 bit aggressor mask. 0/1 indicates this bit should use LFSR1/2
  @param[in] VicRot  - Number of times to circular rotate vmask/amask
  @param[in] Start   - Starting entry in the WDB

  @retval Nothing
**/
extern
void
WriteVAPattern (
  IN MrcParameters *const MrcData,
  IN UINT32               amask,
  IN UINT32               vmask,
  IN const UINT8          VicRot,
  IN const UINT16         Start
  );

/**
  Write VA pattern in CADB buffer.

  Note1: CKE, ODT and CS are not used in functional mode and are ignored.
  Note2: This function requires that MrcSelectEngines() has been called.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] VictimSpread - Separation of the Victim Bit.
  @param[in] VictimBit    - The Bit to be the Victim.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
extern
MrcStatus
SetupCadbVaPat (
  IN MrcParameters *const MrcData,
  IN const UINT8          VictimSpread,
  IN const UINT8          VictimBit
  );

/**
  Programs all the key registers to define a CPCG test

  @param[in] MrcData     - Include all MRC global data.
  @param[in] WDBPattern  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in] ChbitMask   - Channel Bit mak for which test should be setup for.
  @param[in] CmdPat      - [0: PatWrRd (Standard Write/Read Loopback),
                            1: PatWr (Write Only),
                            2: PatRd (Read Only),
                            3: PatRdWrTA (ReadWrite Turnarounds),
                            4: PatWrRdTA (WriteRead Turnarounds),
                            5: PatODTTA (ODT Turnaround]
  @param[in] NumCL       - Number of Cache lines
  @param[in] LC          - Exponential Loop Count
  @param[in] CPGCAddress - Structure that stores address related settings
  @param[in] SOE         - [0: Never Stop, 1: Stop on Any Lane, 2: Stop on All Byte, 3: Stop on All Lane]
  @param[in] PatCtlPtr   - Pointer to IncScale, IncRate, start, Stop and Dqpat for pattern.
  @param[in] EnCADB      - Enable test to write random deselect packages on bus to create xtalk/isi
  @param[in] EnCKE       - Enable CKE power down by adding 64
  @param[in] SubSeqWait  - # of Dclks to stall at the end of a sub-sequence

  @retval Nothing
**/
extern
void
SetupIOTest (
  IN MrcParameters *const         MrcData,
  IN const UINT8                  ChbitMask,
  IN const UINT8                  CmdPat,
  IN const UINT32                 NumCL,
  IN const UINT8                  LC,
  IN const Cpgc20Address *const   CpgcAddress,
  IN const MRC_TEST_STOP_TYPE     SOE,
  IN       MRC_PATTERN_CTL *const PatCtlPtr,
  IN const UINT8                  EnCADB,
  IN const UINT8                  EnCKE,
  IN       UINT16                 SubSeqWait
  );

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential number of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestCADB (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  This function sets up a basic victim-aggressor test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential number of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     Spread    - Stopping point of the pattern.

  @retval Nothing
**/
extern
void
SetupIOTestBasicVA (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT8          Spread
  );

/**
  This function sets up a MPR test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
extern
void
SetupIOTestMPR (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
This function sets up a Read test for the given channel mask.

@param[in,out] MrcData   - Pointer to MRC global data.
@param[in]     ChbitMask - Bit masks of channels to enable for the test.
@param[in]     LC        - Exponential umber of loops to run the test.
@param[in]     SOE       - Error handling switch for test.
@param[in]     RdDataPtn - Read Data Pattern in 32bit  (i.e. MPR - LP4:0x0xa5a5a5a5     DDR4:0xAAAAAAAA)

@retval Nothing
**/
void
SetupIOTestCpgcRead (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT32         RdDataPtn
  );

/**
  This function sets up a Clock Pattern test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestClock (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  );

/**
  This function sets up a basic static WR/RD test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential number of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     NumIters  - Desired number of iterations performed on each cacheline.
  @param[in]     Pattern   - Array of chunks (64 bit), broken into two 32-bit entries (second dimension).
                             Length (first dimension) can be up to NUM_DPAT_EXTBUF

  @retval Nothing
**/
extern
void
SetupIOTestStatic (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT16         NumIters,
  IN           UINT32         Pattern[][2]
  );

/**
  This function sets up a WR-only test for the given channel mask, with all-zero data.
  This is used for ECC scrubbing or memory clear.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.

**/
void
SetupIOTestScrub (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask
  );

/**
  Runs one or more REUT tests (based on TestType)

  @param[in] MrcData      - Include all MRC global data.
  @param[in] ChBitMask    - Channel Bit mask for which test should be setup for.
  @param[in] DQPat        - The Pattern type for the test.  See MrcDqPat.
  @param[in] ClearErrors  - Decision to clear or not errors.
  @param[in] Mode         - Allows for different types of modes for margining
                           {Bit0: PhLock (keep all bytes within in ch in phase),
                            Bit1: Ch2Ch Data out of phase (LFSR seed)
                            Bits 15:2: Reserved}

  @retval Returns ch errors
**/
extern
UINT8
RunIOTest (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChBitMask,
  IN const UINT8          DQPat,
  IN const UINT8          ClearErrors,
  IN const UINT16         Mode
  );

/**
  Programs REUT to run on the selected physical ranks.

  @param[in] MrcData           - Pointer to MRC global data.
  @param[in] ch                - Channel to enable.
  @param[in] RankBitMask       - Bit mask of ranks to enable.
  @param[in] SkipRankL2P       - Boolean control over skipping Logical 2 Physical programming for Rank.
  @param[in] RankFeatureEnable - RankFeatureEnable is a bit mask that can enable CKE, Refresh or ZQ
                                 RankFeatureEnable[0] enables Refresh on all non-selected ranks
                                 RankFeatureEnable[1] enables Refresh on all ranks
                                 RankFeatureEnable[2] enables ZQ on all non-selected ranks
                                 RankFeatureEnable[3] enables ZQ on all ranks
                                 RankFeatureEnable[4] enables CKE on all non-selected ranks
                                 RankFeatureEnable[5] enables CKE on all ranks

  @retval Bit mask of channel enabled if rank in the channel exists.
**/
extern
UINT8
SelectReutRanks (
  IN MrcParameters *const MrcData,
  IN const UINT8          ch,
  IN UINT8                RankBitMask,
  IN BOOLEAN              SkipRankL2P,
  IN const UINT8          RankFeatureEnable
  );

/**
  Returns the index into the array MarginResult in the MrcOutput structure.

  @param[in] ParamV - Margin parameter

  @retval One of the following values: LastRxV(0), LastRxT (1), LastTxV(2), LastTxT (3), LastRcvEna (4),
                                       LastWrLevel (5), LastCmdT (6), LastCmdV (7)
**/
extern
UINT8
GetMarginResultType (
  IN const UINT8  ParamV
  );

/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param.
  Searches across all bytes and ranks in RankMask.  Bytes search depend on channel length.
  For Enhanced Channel Mode, Channel margin is stored in the first byte for that channel:
        LPDDR4: SysCh   Ch  Byte
                  0     0   0
                  1     0   4
                  2     1   0
                  3     1   4

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankMask        - Condenses down the results from multiple ranks
  @param[in]     ResultRank      - This rank will keep the results from multiple ranks
  @param[in]     EnhancedChMode  - This parameter controls the margin search and location if we support x32 or x64 channels.

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
extern
MrcStatus
GetMarginCh (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankMask,
  IN     const UINT8          ResultRank,
  IN     const BOOLEAN        EnhancedChMode
  );

/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetPdaMargins (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks
  );

/**
  Use this function to retrieve the last margin results from MrcData

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankIn          - Which rank of the host structure you want the result returned on
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval MarginResult structure has been updated if MrcStatus returns mrcSuccess.
  @retval Otherwise, mrcWrongInputParameter is returned if an incorrect Param is passed in.
**/
extern
MrcStatus
GetMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankIn,
  IN     const UINT8          Ranks
  );

/**
  This function is use to "unscale" the MrcData last margin point
  GetMarginByte will scale the results for FAN margin
  This will unscale the results such that future tests start at the correct point

  @param[in]     MrcData      - Include all MRC global data.
  @param[in,out] MarginResult - Input array to be unscaled.
  @param[in]     Param        - Defines the margin type for proper scale selection.
  @param[in]     Rank         - Which rank of the host structure to work on

  @retval mrcSuccess
**/
extern
MrcStatus
ScaleMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Rank
  );

/**
  This function is used by most margin search functions to change te underlying margin parameter.
  This function allows single search function to be used for different types of margins with minimal impact.
  It provides multiple different parameters, including 2D parameters like Read or Write FAN.
  It can work in either MultiCast or single register mode.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     param         - Includes parameter(s) to change including two dimentional.
  @param[in]     value0        - Selected value to program margin param to
  @param[in]     value1        - Selected value to program margin param to in 2D mode (FAN mode)
  @param[in]     EnMultiCast   - To enable Multicast (broadcast) or single register mode
  @param[in]     channel       - Desired Channel
  @param[in]     rankIn        - Desired Rank - only used for the RxTBit and TxTBit settings and to propagate RdVref
  @param[in]     byte          - Desired byte offset register
  @param[in]     bitIn         - Desired bit offset Mrc data strucure if UpdateMrcData is 1
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated
  @param[in]     SkipWait      - Used to skip wait until all channel are done

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
extern
MrcStatus
ChangeMargin (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          value0,
  IN     const INT32          value1,
  IN     const UINT8          EnMultiCast,
  IN     const UINT8          channel,
  IN     const UINT8          rankIn,
  IN     const UINT16         byte,
  IN     const UINT8          bitIn,
  IN     const UINT8          UpdateMrcData,
  IN     const UINT8          SkipWait
  );

/**
  This procedure returns the minimal required eye height for a given training step.
  This information is subsequently used differently for making decisions, e.g., MRCFailure, PDA writing, etc.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     EarlyCentering - Is Step an Early Training step.

  return MinWidth UINT8
**/
extern
UINT8
GetMinRequiredEyeWidth (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              EarlyCentering
  );

/**
  This procedure is meant to handle basic timing centering, places strobe in the middle of the data eye,
  for both read and write DQ/DQS using a very robust, linear search algorthim.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     chBitMaskIn    - Channel bit mask.
  @param[in]     param          - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                   8:WrTBit, 9:RdTBit, 10:RdVBit,
                                   16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                   ONLY RdT and WrT are allowed in this function
  @param[in]     ResetPerBit    - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     loopcount      - loop count
  @param[in]     MsgPrint       - Serial debug output message enable.
  @param[in]     EarlyCentering - Execute as early centering routine

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
extern
MrcStatus
DQTimeCentering1D (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          chBitMaskIn,
  IN     const UINT8          param,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          loopcount,
  IN     BOOLEAN              MsgPrint,
  IN     BOOLEAN              EarlyCentering
  );

/**
  This procedure is meant to find the calibration step to be used for Per Bit DeSkew

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in,out] MarginResult   - Margin data from centering
  @param[in]     chBitMaskIn    - Channel bit mask.
  @param[in]     param          - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                   8:WrTBit, 9:RdTBit, 10:RdVBit,
                                   16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                   ONLY RdT is allowed in this function
  @param[in]     loopcount      - loop count

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
extern
MrcStatus
GetPerBitDeSkewStep (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          LoopCount
  );

/**
  This procedure is meant to handle much more complex centering that will use a 2D algorithm to optimize asymetical
  eyes for both timing and voltage margin.

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Margin data from centering
  @param[in]     ChBitMaskIn     - Channel bit mask.
  @param[in]     param           - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                    8:WrTBit, 9:RdTBit, 10:RdVBit,
                                    16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                    ONLY RdT and WrT are allowed in this function
  @param[in]     EnPerBit        - Option to enable per bit margining
  @param[in]     EnRxDutyCycleIn - Phase to center.
  @param[in]     ResetPerBit     - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount       - loop count
  @param[in]     En2D            - Option to only run center at nominal Vref point
  @param[in]     Prints          - Disable/Enable debug prints

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
extern
MrcStatus
DataTimeCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          EnPerBit,
  IN     const UINT8          EnRxDutyCycleIn,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          LoopCount,
  IN     const UINT8          En2D,
  IN     BOOLEAN              Prints
  );

/**
  Subfunction of 2D Timing Centering
  Measures paramV margin across ch/bytes and updates the EH/VrefScale variables

  @param[in]     MrcData   - Include all MRC global data.
  @param[in]     ChBitMask - Channel Bit mak for which test should be setup for.
  @param[in]     rank      - Defines rank to used for MrcData
  @param[in]     ParamV    - Margin parameter
  @param[in]     MaxVScale - Maximum Voltage Scale to use
  @param[in]     BMap      - Byte mapping to configure error counter control register
  @param[in,out] EH        - Structure that stores start, stop and increment details for address
  @param[in,out] VrefScale - Parameter to be updated
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise the function returns an error status.
**/
extern
MrcStatus
DQTimeCenterEH (
  IN     MrcParameters * const MrcData,
  IN     const UINT8           ChBitMask,
  IN     const UINT8           rank,
  IN     const UINT8           ParamV,
  IN     const UINT8           MaxVScale,
  IN     UINT8 * const            BMap,
  IN OUT UINT32                EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32                VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32 * const           BERStats
  );

/**
  This step prints out the key training parameters that are margined by Rank Margin Tool.
  This will allow tracking of current training settings across multiple steps

  @retval Nothing
**/
void
MrcTrainedStateTrace (
  IN  MrcParameters *const  MrcData
  );

/**
  Update the CA/DQ Vref value

  @param[in,out] MrcData             - Include all MRC global data.
  @param[in]     ChannelMask         - Select the Channels to update Vref for.
  @param[in]     RankMask            - Selecting which Rank to talk to (DDR4: WrV and CmdV, LPDDR4: WrV and CmdV)
  @param[in]     DeviceMask          - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     VrefType            - Determines the Vref to change: WrV or CmdV only.
  @param[in]     Offset              - Vref offset value.
  @param[in]     UpdateMrcData       - Used to decide if Mrc host must be updated.
  @param[in]     PDAmode             - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     SkipWait            - Determines if we will wait for vref to settle after writing to register
  @param[in]     IsCachedOffsetParam - Determines if the parameter is an offset (relative to cache) or absolute value.

  @retval Nothing
**/
void
MrcUpdateVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode,
  IN     BOOLEAN              SkipWait,
  IN     BOOLEAN              IsCacheOffset
  );

/**
  This function is used to move CMD/CTL/CLK/CKE PIs during training

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to shift PI for
  @param[in]     Iteration  - Determines which PI to shift:
                              MrcIterationClock = 0
                              MrcIterationCmd   = 1
                              MrcIterationCtl   = 2
  @param[in]     RankMask   - Ranks to work on
  @param[in]     GroupMask  - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in]     NewValue   - value to shift in case of CLK Iteration, New value for all other cases
  @param[in]     UpdateHost - Determines if MrcData structure is updated
                            = 1 set the local valid flag to FALSE
                            = 0 set valid flag is TRUE. uses locally saved DQ/DQS/RecEn delays.

  @retval Nothing
**/
extern
void
ShiftPIforCmdTraining (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Iteration,
  IN     const UINT8          RankMask,
  IN     const UINT8          GroupMask,
  IN     INT32                NewValue,
  IN     const UINT8          UpdateHost
  );

/**
  Shifts RcvEn, WriteLevel and WriteDQS timing for all bytes
  Usually used when moving the clocks on a channel

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to update
  @param[in]     Rank       - Rank to update
  @param[in]     ByteMask   - Bytes to update
  @param[in]     Offset     - value to shift
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
extern
void
ShiftDQPIs (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Rank,
  IN     const UINT32         ByteMask,
  IN     const INT8           Offset,
  IN     const UINT8          UpdateHost
  );

/**
  Returns the Offset for DataTrainFeedback register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset
**/
extern
UINT32
MrcGetOffsetDataTrainFeedback (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Returns the Offset for DataOffsetComp register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset
**/
UINT32
MrcGetOffsetDataOffsetComp (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  );

/**
  Determines if Per-Bit Deskew is needed.  If not, it will disable Per-Bit Deskew.

  @param[in]   MrcData      - The MRC global data.
  @param[in]   MarginResult - Data structure with the latest margin results.
  @param[in]   Param        - Only RdT(1) and WrT(2) are valid.
**/
void
MrcPerBitDeskew (
  IN MrcParameters * const MrcData,
  IN UINT32                MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const UINT8           Param
  );

/**
  Enable / Disable CADB and Deselects on MC (on all populated channels)

  @param[in] MrcData  - The MRC global data.
  @param[in] Enable   - TRUE to enable, FALSE to disable.

  @retval Nothing
**/
void
McCadbEnable (
  IN MrcParameters *const  MrcData,
  IN BOOLEAN               Enable
  );

/**
  Run a short CADB sequence on selected channels

  @param[in] MrcData      - The MRC global data.
  @param[in] ChBitMask    - channels to work on.

  @retval Nothing
**/
extern
void
ShortRunCADB (
  IN MrcParameters * const  MrcData,
  IN UINT8                  ChBitMask
  );


/**
  Get the Rx Bias values

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in, out] RxFselect  - Location to save RxFselect.

  @retval Nothing
**/
extern
void
GetRxFselect (
  IN MrcParameters *const MrcData,
  IN OUT INT8          *RxFselect
  );

/**
  Read 32-bit value from the specified bus/device/function/offset.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Bus      - PCI bus number.
  @param[in] Device   - PCI device number.
  @param[in] Function - PCI function number.
  @param[in] Offset   - PCI address offset.

  @retval 32-bit PCI value.
**/
extern
UINT32
MrcPciRead32 (
  IN const MrcParameters * const MrcData,
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  );

/**
  This function changes the DIMM Voltage to the closest desired voltage without
  going higher. Default wait time is the minimum value of 200us, if more time
  is needed before deassertion of DIMM Reset#, then change the parameter.

  @param[in, out] MrcData            - The MRC "global data" area.
  @param[in]      VddVoltage         - Selects the DDR voltage to use, in mV.
  @param[in, out] VddSettleWaitTime  - Time needed for Vdd to settle after the update

  @retval TRUE if a voltage change occurred, otherwise FALSE.
**/
BOOLEAN
MrcVDDVoltageCheckAndSwitch (
  IN OUT MrcParameters      *MrcData,
  IN     const MrcVddSelect VddVoltage,
  IN OUT UINT32 * const        VddSettleWaitTime
  );


#ifdef MRC_DEBUG_PRINT
/**
  Debug output of MarginResults for specific ResultType

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] ResultType - Margin Result Type.  MAX_RESULT_TYPE prints all parameters.

  @retval Nothing
**/
void
MrcDisplayMarginResultArray (
  IN MrcParameters *MrcData,
  IN UINT8         ResultType
  );
#endif // MRC_DEBUG_PRINT

/**
  Setup for Memory Check like Alias Checking and DDR4 PDA mapping

  @param[in, out] MrcData           - Pointer to MRC global data.
  @param[in, out] ReutAddress       - Pointer to ReutAddress that will be programmed to REUT engine
  @param[in] Rank                   - Rank to setup
  @param[in] NumOfCachelines        - # of Cachelines to write and read to.  0 is a special value that will write the number
                                      of Cachelines that is required to determine Row/Column Aliasing.
  @param[in, out] ReutUninitialized - Pointer of whether ReutAddress Pointer needs initializing or not.

  @retval Nothing
void
MrcMemoryCheckSetup (
  IN OUT MrcParameters *const MrcData,
  IN OUT MRC_REUTAddress      *ReutAddress,
  IN UINT8                    Rank,
  IN UINT8                    NumOfCachelines,
  IN OUT BOOLEAN              *ReutUninitialized
  );
**/

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  );

/**
  Returns the effective Dimm Write ODT.
  Consider the dram tech, Rtt configuration (Wr, Nom, Park) and Normal Odt logic.
  Note : We still have the assumption of same Rtt's for all ranks in a same dimm.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] Channel                - Channel to setup
  @param[in] Rank                   - Rank to setup
  @param[in] OdtType                - OdtType - 0:write 1:read
  @param[in] GetFromTable           - Get the Values from Odt tables

  @retval Value in Ohms
**/
extern
UINT16
MrcGetEffDimmWriteOdt (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       Rank,
  UINT8                       OdtType,
  BOOLEAN                     GetFromTable
  );

/**
  Set default Tx Dimm Vref for DDR4.
  Use default CPU Ron and DIMM Write Odt values.

  @param[in, out] MrcData - Include all MRC global data.

  @retval none
**/
extern
void
MrcSetDefaultTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData
  );

/**
  Set Tx Dimm Vref absolute Value for DDR4.
  Use custom MRC range [-36:+37] where zero offset is 820mV and step is 7.8mV (JEDEC spec).

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      Channel       - Selecting which Channel to talk to
  @param[in]      Rank          - Selecting which Rank to talk to
  @param[in]      Device        - Selecting which Device to talk to (only valid when PDAmode is TRUE)
  @param[in]      TxVrefOffset  - TxVref Offset to set
  @param[in]      UpdateMrcData - update MRC host struct
  @param[in]      PdaMode       - Selecting to use MRH or old method for MRS

  @retval Nothing
**/
extern
void
MrcSetTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                Rank,
  IN     UINT8                Device,
  IN     INT32                TxVrefOffset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode
  );

/**
  Generic routine to perform Linear Centering in different 2D points.
  Re-uses DQTimeCentering1D routine as the linear centering routine.
  Optimize Per channel in the 2D param space.
  Run-Time - about 20nsec for 6 vref points and loopcout of 10

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChBitMask      - Channel bit mask.
  @param[in]     RankBitMask    - Ranks to center.
  @param[in]     Param          - Param to center with linear search.  Uses DQTimeCentering1D (RdT,WrT,WrV,RdV,RcvX).
  @param[in]     Param2D        - The 2D Param to Offset. Use change margin routine
  @param[in]     Points2DMin    - Minimum value of second dimension points to sweep.
  @param[in]     Points2DMax    - Maxmimum value of second dimension points to sweep.
  @param[in]     ParamStepSize  - Step size of second dimension points to sweep.
  @param[in]     LoopCount      - Loop count.
  @param[in]     TestType       - 0: normal reads, 1: Read MPR
  @param[in]     Prints         - Debug prints enable/disable

  @retval MrcStatus - If it successed return mrcSuccess
**/
MrcStatus
EarlyLinearCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     UINT8                RankBitMask,
  IN     UINT8                Param,
  IN     UINT8                Param2D,
  IN     INT16                Points2DMin,
  IN     INT16                Points2DMax,
  IN     UINT8                ParamStepSize,
  IN     UINT8                LoopCount,
  IN     UINT8                TestType,
  IN     BOOLEAN              Prints
  );

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - behavior Type. Currently Profile 1 is supported (DDR3-like)

  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  );

/**
  Get the Other Dimm in Channel.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      RankMask - Rank mask for the current DIMM.

  @retval The other Dimm outside the RankMask.  If no such DIMM, then return current DIMM.
**/
UINT8
MrcGetOtherDimm (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                RankMask
  );

/**
  Get the maximal possible offset for a given Timing Param (e.g., WrT, RdT) and DDR technology.

  @param[in]      MrcData  - Include all MRC global data.
  @param[in]      Param    - Parameter to get the max possible offset for.

  @retval The maximal possible offset
**/
UINT8
GetMaxPossibleTimingOffset (
  IN MrcParameters *const MrcData,
  IN UINT8                Param
  );

/**
  Get the maximal possible offset for a given Param (e.g., WrV, RdV) and DDR technology.

  @param[in]      MrcData  - Include all MRC global data.
  @param[in]      Param    - Parameter to get the max possible offset for.

  @retval UINT8 variable the maximal possible offset.
**/
UINT8
GetMaxPossibleVrefOffset (
  IN MrcParameters *const MrcData,
  IN UINT8                param
  );

/**
  This function checks to see if the margin parameter is a rank based parameter.  These tend to be
  things which are controlled on the DRAM Mode Register side.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Param   - The parameter to check.  Must be from MRC_MarginTypes.

  @retval BOOLEAN - TRUE if it is a rank based margin parameter.  Otherwise FALSE.
**/
BOOLEAN
IsPerRankMarginParam (
  IN MrcParameters *const MrcData,
  IN UINT8                param
  );

/**
  This function will return the rank used to store the results based on the Rank Mask passed in.
  Results will be stored in the first Rank existing in the RankMask.

  @param[in]  MrcData  - Include all MRC global data.
  @param[in]  RankMask - Bit mask of Ranks being margined.

  @retval mrcSuccess
**/
extern
UINT8
GetRankToStoreResults (
  IN      MrcParameters *const MrcData,
  IN      UINT16               RankMask
  );

/**
  Relax RDRD same rank turnarounds on all channels.
  Used during early write training steps to avoid stressing reads.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Relax   - TRUE: relax the TAT values, FALSE: restore original values.
**/
void
MrcRelaxReadToReadSameRank (
  IN  MrcParameters *const MrcData,
  IN BOOLEAN               Relax
  );

/**
  Relax WRWR same rank turnarounds on all channels.
  Used during early Read training steps to avoid stressing write.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Relax   - TRUE: relax the TAT values, FALSE: restore original values.
**/
void
MrcRelaxWriteToWriteSameRank (
  IN  MrcParameters *const MrcData,
  IN BOOLEAN               Relax
);

#endif // _MrcCommon_h_
