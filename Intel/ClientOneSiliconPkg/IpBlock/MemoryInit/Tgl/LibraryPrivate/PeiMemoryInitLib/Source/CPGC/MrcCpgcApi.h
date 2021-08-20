/** @file
  This file declares the interface between the MRC and the different
  versions of CPGC.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _MRC_CPGC_API_H_
#define _MRC_CPGC_API_H_

/// Defines and Enumerations
#define CADB_20_MAX_CHUNKS  (8)
#define MRC_NUM_MUX_SEEDS   (3)
#define MRC_MUX_PB_LENGTH   (24)

typedef enum {
  ErrCounterCtlPerLane = 0,    ///< Indicates Counter Status will count errors for a particular lane
  ErrCounterCtlPerByte,        ///< Indicates Counter Status will count errors for a particular byte group
  ErrCounterCtlPerNibble,      ///< Indicates Counter Status will count errors for a particular nibble
  ErrCounterCtlPerUI,          ///< Indicates Counter Status will count errors for a particular UI
  ErrCounterCtlAllLanes,       ///< Indicates Counter Status will count errors for all lanes
  ErrCounterCtlMax
} MRC_ERR_COUNTER_CTL_TYPE;

typedef enum {
  ByteGroupErrStatus = 0,
  ChunkErrStatus,
  RankErrStatus,
  NthErrStatus,
  NthErrOverflow,
  AlertErrStatus,
  WdbRdChunkNumStatus,
  BitGroupErrStatus,
  EccLaneErrStatus,
  ErrStatusTypeMax
} MRC_ERR_STATUS_TYPE;

///
/// Structs and Types
///
typedef union {
  struct {
    UINT32  CmdAddr : 24; ///<  Bits 0:23
    UINT32  Spare   : 8;  ///<  Bits 24:31
  } Bits;
  struct {
    UINT32  Ma    : 16; ///< Bits 0:15
    UINT32  We_b  : 1;  ///< Bits 16
    UINT32  Cas_b : 1;  ///< Bits 17
    UINT32  Ras_b : 1;  ///< Bits 18
    UINT32  Ba    : 3;  ///< Bits 19:21
    UINT32  Spare : 10; ///< Bits 22:31
  } Ddr3;
  /// Must keep this order for signal definition as assume relationship in SetupCadbVaPat()
  struct {
    UINT32  Ma    : 17; ///< Bits 0:16
    UINT32        : 1;  ///< Bits 17:17
    UINT32  Ba    : 2;  ///< Bits 18:19
    UINT32  Bg    : 2;  ///< Bits 20:21
    UINT32  Act_n : 1;  ///< Bits 22:22
    UINT32  Spare : 9;  ///< Bits 23:31
  } Ddr4;
  struct {
    UINT32  CaLow   : 10; ///< Bits 0:9
    UINT32  CaHigh  : 10; ///< Bits 10:19
    UINT32  Spare   : 12; ///< Bits 20:31
  } Lpddr3;
  struct {
    UINT32  Ca1   : 6;  ///< Bits 0:5   For Selects this is CA 1.  For DeSelects, this is Sub Channel 0
    UINT32  Ca2   : 6;  ///< Bits 6:11  For Selects this is CA 2.  For DeSelects, this is Sub Channel 1
    UINT32  Ca3   : 6;  ///< Bits 12:17 For Selects this is CA 3.  For DeSelects, this is unused.
    UINT32  Ca4   : 6;  ///< Bits 18:23 For Selects this is CA 4.  For DeSelects, this is unused.
    UINT32  Spare : 8;  ///< Bits 24:31
  } Lpddr4;
  struct {
    UINT32  Ca1   : 7;  ///< Bits 0:6   For Selects this is CA 1.  For DeSelects, this is Sub Channel 0
    UINT32  Ca2   : 7;  ///< Bits 7:13  For Selects this is CA 2.  For DeSelects, this is Sub Channel 1
    UINT32  Ca3   : 7;  ///< Bits 14:20 For Selects this is CA 3.  For DeSelects, this is unused.
    UINT32  Ca4   : 7;  ///< Bits 21:27 For Selects this is CA 4.  For DeSelects, this is unused.
    UINT32  Spare : 4;  ///< Bits 28:31
  } Lpddr5;
  UINT32  Data32;
} MRC_CA_MAP_TYPE;

typedef enum {
  MrcLfsr8,
  MrcLfsr15,
  MrcLfsr31,
  MrcLfsr23b, //x23 + x18
  MrcLfsr7,
  MrcLfsr16,
  MrcLfsr23a, //x23 + x21 + x18 + x15 + x7 + x2
  MrcLfsr32,
  MrcLfsrTypeMax
} MRC_PG_LFSR_TYPE;
/// Public Function Declaration

/**
  This function will configure the pattern rotation for dynamic and static patterns.

  @param[in]  MrcData    - Pointer to global MRC data.
  @param[in]  PatCtlPtr  - Pointer to rotation configuration.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcProgramDataPatternRotation (
  IN  MrcParameters   *const  MrcData,
  IN  MRC_PATTERN_CTL *const  PatCtlPtr
  );

/**
This function takes in a generic mapping of CS, CKE, ODT, and Command/Address
signals and converts them to the expected layout of the hardware engine.

@param[in]  MrcData - Pointer to global data structure.
@param[in]  CmdAddr - Union of Command/Address signals per each supported memory technology
@param[in]  Cke     - Bit Mask of Clock Enable signals per sub-channel.
@param[in]  Cs      - Bit Mask of Chip Select signals per sub-channel.
@param[in]  Odt     - Bit Mask of On Die Termination signals.

@retval - MrcStatus: mrcSuccess if successful, otherwise an error status.
**/
MrcStatus
CpgcConvertDdrToCadb(
  IN  MrcParameters     *const  MrcData,
  IN  MRC_CA_MAP_TYPE   *const  CmdAddr,
  IN  UINT8                     Cke[2],
  IN  UINT8                     Cs[2],
  IN  UINT8                     Odt,
  OUT UINT64_STRUCT     *const  CadbVal
);

/**
  This function programs the Error Mask for Cacheline and UI comparisons.
  A value of 1 enables error checking.

  @param[in]  MrcData       - Pointer to global MRC data.
  @param[in]  CachelineMask - Bit mask of cachelines to enable.
  @param[in]  ChunkMask     - Bit mask of chunks to enable.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetChunkAndClErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                CachelineMask,
  IN  UINT32                ChunkMask
  );

/**
  This function programs the Error Mask for Data and ECC bit lanes as per McChBitMask.
  A value of 1 enables error checking for that bit.

  @param[in]  MrcData    - Pointer to global MRC data.
  @param[in]  DataMask   - Bit mask of Data bits to check.
  @param[in]  EccMask    - Bit mask of ECC bits to check.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetDataAndEccErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT64                DataMask,
  IN  UINT8                 EccMask
  );

/**
  This function programs the test loop count.

  @param[in]  MrcData    - Pointer to MRC global data.
  @param[in]  LoopCount  - Number of sequence iterations. 0 means infinite test.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetLoopcount (
  IN MrcParameters *const  MrcData,
  IN UINT32                LoopCount
  );

/**
  This function will program the patterns passed in into the Pattern Generators.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  McChBitMask - Memory Controller Channel Bit mask for which test should be setup for.
  @param[in]  Pattern     - Array of 64-bit patterns.
  @param[in]  PatLen      - Number of Patterns to program.
  @param[in]  Start       - Starting Chunk of pattern programming.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetCadbPgPattern (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 McChBitMask,
  IN  UINT64_STRUCT         Pattern[CADB_20_MAX_CHUNKS],
  IN  UINT32                PatLen,
  IN  UINT32                Start
  );

/**
  This function programs the test engine stop condition.

  @param[in]  MrcData         - Pointer to MRC global data.
  @param[in]  StopType        - MRC_TEST_STOP_TYPE: NSOE, NTHSOE, ABGSOE, ALSOE.
  @param[in]  NumberOfErrors  - Number of errors required to stop the test when StopType is NTHSOE.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetupTestErrCtl (
  IN  MrcParameters       *const  MrcData,
  IN  MRC_TEST_STOP_TYPE          StopType,
  IN  UINT32                      NumberOfErrors
  );

/**
  This function will Setup REUT Error Counters to count errors for specified type.

  @param[in]  MrcData           - Include all MRC global data.
  @param[in]  CounterPointer    - Specifies in register which Counter to setup. Valid for ErrControl values:
                                  ErrCounterCtlPerLane, ErrCounterCtlPerByte, ErrCounterCtlPerNibble, or ErrCounterCtlPerUI.
  @param[in]  ErrControl        - Specifies which type of error counter read will be executed.
  @param[in]  CounterUI         - Specifies which UI will be considered when counting errors.
                                  00 - All UI; 01 - Even UI; 10 - Odd UI; 11 - Particular UI (COUNTER_CONTROL_SEL = ErrCounterCtlPerUI)

  @retval mrcWrongInputParameter if ErrControlSel is an incorrect value, otherwise mrcSuccess.
**/
MrcStatus
MrcSetupErrCounterCtl (
  IN  MrcParameters *const      MrcData,
  IN  UINT8                     CounterPointer,
  IN  MRC_ERR_COUNTER_CTL_TYPE  ErrControlSel,
  IN  UINT8                     CounterUI
  );

/**
  This function returns the Bit Group Error status results.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Controller  - 0-based index selecting Controller to adjust.
  @param[in]  Channel     - 0-based index, Channel to configure.
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
MrcGetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Controller,
  IN  UINT32                  Channel,
  OUT UINT8                   *Status
  );

/**
  This function returns the Error status results of the specified Error Type.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Controller  - Desired Controller.
  @param[in]  Channel     - Desired Channel.
  @param[in]  Param       - Specifies which type of error status read will be executed.
  @param[out] Buffer      - Pointer to buffer which register values will be read into.
                              Error status bits will be returned starting with bit zero. Logical shifting will not be handled by this function.

  @retval Returns mrcWrongInputParameter if Param value is not supported by this function, otherwise mrcSuccess.
**/
MrcStatus
MrcGetMiscErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Controller,
  IN  UINT32                  Channel,
  IN  MRC_ERR_STATUS_TYPE     Param,
  OUT UINT64          *const  Buffer
  );

/**
  This function sets or returns the Logical-to-Physical mapping of Banks.  The index to the array
  is the logical address, and the value at that index is the physical address.  This function
  operates on a linear definition of Banks, even though there may be a hierarchy as BankGroup->Bank.
  For system with X Bank Groups and Y Banks per group, the Banks are indexed in the array as:
  (X * Y + Z) where X is the bank group, Y is the total number of banks per group, and Z is the
  target bank belonging to bank group X.

  Example:
    Bank Group 3, Bank 5, 8 Banks per Bank Group -> Index position (3 * 8) + 5 == 29.

  The function will act upon the array bounded by the param Length.
  The Function always starts at Bank 0.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Controller  - Desired Controller.
  @param[in]  Channel     - Desired Channel.
  @param[in]  L2pBankList - Array of logical-to-physical Bank Mapping.
  @param[in]  Length      - Array length of L2pBankList buffer.
  @param[in]  IsGet       - Boolean; if TRUE, request is a Get, otherwise Set.

  @retval MrcStatus.
**/
MrcStatus
MrcGetSetBankSequence (
  IN  MrcParameters *const      MrcData,
  IN  UINT32                    Controller,
  IN  UINT32                    Channel,
  IN  MRC_BG_BANK_PAIR  *const  L2pBankList,
  IN  UINT32                    Length,
  IN  BOOLEAN                   IsGet
  );

/**
  This function returns the Error Counter status.

  @param[in]  MrcData       - Include all MRC global data.
  @param[in]  Controller    - Desired Controller.
  @param[in]  Channel       - Desired Channel.
  @param[in]  CounterSelect - Specifies in register which Counter to setup. Valid for ErrControl values:
                                ErrCounterCtlPerLane, ErrCounterCtlPerByte, or ErrCounterCtlPerChunk.
  @param[in]  ErrControl    - Specifies which type of error counter read will be executed.
  @param[in]  Status        - Pointer to buffer where counter status will be held.
  @param[out] Overflow      - Pointer to variable indicating if Overflow has been reached.

  @retval Nothing.
**/
void
MrcGetErrCounterStatus (
  IN  MrcParameters   *const    MrcData,
  IN  UINT32                    Controller,
  IN  UINT32                    Channel,
  IN  UINT8                     CounterSelect,
  IN  MRC_ERR_COUNTER_CTL_TYPE  ErrControl,
  OUT UINT32          *const    Status,
  OUT BOOLEAN         *const    Overflow
  );

/**
  This function will program the CPGC PGs Mux Seeds.  The PGs must be selected before this call.

  @param[in] MrcData    - Global MRC data.
  @param[in] Seeds      - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR.
  @param[in] Start      - Zero based index which Unisequencer to start programming.
  @param[in] SeedCount  - Number of seeds in the array.

  @retval - Nothing
**/
void
MrcInitCpgcPgMux (
  IN MrcParameters *const MrcData,
  IN const UINT32  *const Seeds,
  IN const UINT8          Start,
  IN const UINT8          SeedCount
  );

/**
  This function will enable or disable CPGC engines on all channels

  @param[in] MrcData    - Global MRC data structure
  @param[in] ActiveMode - If true, enable CPGC engines. If false, set to idle mode.

  @retval - Nothing
**/
extern
void
MrcSetCpgcInitMode (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              ActiveMode
  );

/**
  This function will program the CADB PGs Mux Seeds.  The PGs must be selected before this call.

  @param[in] MrcData   - Global MRC data.
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR.
  @param[in] Start     - Zero based index which Unisequencer to start programming.
  @param[in] SeedCount - Number of seeds in the array.

  @retval - Nothing
**/
void
MrcInitCadbPgMux (
  IN MrcParameters *const MrcData,
  IN const UINT32  *const Seeds,
  IN const UINT8          Start,
  IN const UINT8          SeedCount
  );
/**
This function will configure and program the CPGC DPAT Unisequencers.  The PGs must be selected before this call.

  @param[in]  MrcData    - Global MRC data.
  @param[in]  LfsrPoly   - LFSR Polynominal applied to all UNISEQs
  @param[in]  PatCtlPtr  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in]  Start      - Zero based index which Unisequencer to start programming.
  @param[in]  UsqCount   - Number of Unisequencers in to program.

  @retval - Nothing
**/

void
MrcInitUnisequencer (
  IN MrcParameters *const    MrcData,
  IN MRC_PG_LFSR_TYPE        LfsrPoly,
  IN MRC_PATTERN_CTL *const  PatCtlPtr,
  IN const UINT8             Start,
  IN const UINT8             UsqCount
  );
#endif //_MRC_CPGC_API_H_
