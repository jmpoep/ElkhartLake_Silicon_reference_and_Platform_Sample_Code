/** @file
  This file defines functions for setting up test control
  registers for CPGC 2.0.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#ifndef _CPGC_20_TEST_CTL_H_
#define _CPGC_20_TEST_CTL_H_
#include "MrcCpgcApi.h"
#include "Cpgc20.h"

/**
  This function programs the masks that enable error checking on the
  requested cachelines and chunks.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  Channel       - 0-based index channel to setup.
  @param[in]  CachelineMask - Bit Mask of cachelines to enable.
  @param[in]  ChunkMask     - Bit Mask of chunks to enable.

  @retval Nothing
**/
void
Cpgc20SetChunkClErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                CachelineMask,
  IN  UINT32                ChunkMask
  );

/**
  This function programs the masks that enable error checking on the
  requested bytes.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  ChMask        - Channel Mask for which Channels to apply to.
  @param[in]  SubChMask     - SubChannel Mask for which SubChannels to apply to.
  @param[in]  WordMask      - Which Word (Lower or Upper) to apply ErrMask to.
  @param[in]  ErrMask       - Error Masking Value to apply.

  @retval Nothing
**/
void
Cpgc20SetDataErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                ChMask,
  IN  UINT32                SubChMask,
  IN  UINT32                WordMask,
  IN  UINT32                ErrMask
  );

/**
  This function programs the error conditions to stop the CPGC engine on.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  Channel       - 0-based index channel to setup.
  @param[in]  StopType      - Stop type for CPGC engine.
  @param[in]  NumOfErr      - Number of Stop Type errors to wait on before stopping CPGC engine.

  @retval Nothing
**/
void
Cpgc20SetupTestErrCtl (
  IN  MrcParameters       *const  MrcData,
  IN  UINT32                      Channel,
  IN  MRC_TEST_STOP_TYPE          StopType,
  IN  UINT32                      NumOfErr
  );

/**
  This function will Setup REUT Error Counters to count errors for specified type.

  @param[in]  MrcData         - Pointer to MRC global data.
  @param[in]  Channel         - 0-based index channel to setup.
  @param[in]  SubChannel      - 0-based index SubChannel to setup. This parameter is valid regardless of Enhanced Channel Mode setting.
  @param[in]  CounterSelect   - Specifies in register which counter to setup. In EnhancedChannelMode, each SubChannel
                                has 4 counters, otherwise each Channel has 9 counters including ECC.
  @param[in]  ErrControl      - Specifies which type of error counter read will be executed.
  @param[in]  CounterSetting  - Specifies in register which Lane/Byte/Chunk to track in specified counter,
                                based on ErrControl value.

  @retval mrcWrongInputParameter if CounterSetting is incorrect for the ErrControl selected, otherwise mrcSuccess.
**/
MrcStatus
Cpgc20SetupErrCounterCtl (
  IN MrcParameters *const      MrcData,
  IN UINT32                    Channel,
  IN UINT32                    SubChannel,
  IN UINT32                    CounterSelect,
  IN MRC_ERR_COUNTER_CTL_TYPE  ErrControl,
  IN UINT32                    CounterSetting
  );

/**
  This function returns the Error status results for specified MRC_ERR_STATUS_TYPE.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel. This parameter is valid regardless of Enhanced Channel Mode setting.
  @param[in]  Param       - Specifies which type of error status read will be executed.
  @param[out] Buffer      - Pointer to buffer which register values will be read into.
                              Error status bits will be returned starting with bit zero.

  @retval Returns mrcWrongInputParameter if Param value is not supported by this function, otherwise mrcSuccess.
**/
MrcStatus
Cpgc20GetErrEccChunkRankByteStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Channel,
  IN  UINT32                  SubChannel,
  IN  MRC_ERR_STATUS_TYPE     Param,
  OUT UINT64          *const  Buffer
  );

/**
  This function accesses the Sequence loop count.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  Channel   - Zero based index of channel to access.
  @param[in]  SubCh     - Zero based index of SubChannel to access.
  @param[in]  IsGet     - If TRUE, action is a get.  Otherwise, action is a set.
  @param[in]  LoopCount - Pointer to variable to store or set.

  @retval Nothing.
**/
void
Cpgc20GetSetLoopCount (
  IN      MrcParameters *const  MrcData,
  IN      UINT32                Channel,
  IN      UINT32                SubCh,
  IN      BOOLEAN               IsGet,
  IN OUT  UINT32  *const        LoopCount
  );

/**
  This function accesses the Logical to Physical Bank Mapping.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Channel - Zero based index selecting the channel to access.
  @param[in]  Banks   - Pointer to buffer to logical-to-physical bank mapping.
  @param[in]  Count   - Length of the Banks buffer.
  @param[in]  IsGet   - TRUE: Get.  FALSE: Set.

  @retval Nothing.
**/
void
Cpgc20GetSetBankMap (
  IN      MrcParameters *const  MrcData,
  IN      UINT32                Channel,
  IN OUT  UINT8 *const          Banks,
  IN      UINT32                Count,
  IN      BOOLEAN               IsGet
  );

/**
  This function returns the Bit Group Error status results.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel.
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
Cpgc20GetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Channel,
  IN  UINT32                  SubChannel,
  OUT UINT8                   *Status
  );

/**
  This function returns the Error Counter status for specified counter.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  Channel       - Desired Channel.
  @param[in]  SubChannel    - Desired SubChannel.
  @param[in]  CounterSelect - Desired error counter to read from.
  @param[out] CounterStatus - Pointer to buffer where counter status will be held.
  @param[out] Overflow      - Indicates if counter has reached overflow.

  @retval Nothing.
**/
void
Cpgc20GetErrCounterStatus (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                SubCh,
  IN  UINT32                CounterSelect,
  OUT UINT32        *const  CounterStatus,
  OUT BOOLEAN       *const  Overflow
  );

/**
  This function writes to all enabled CPGC SEQ CTL registers (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CpgcSeqCtl    - Data to be written to all CPGC SEQ CTL registers.

  @retval Nothing.
**/
void
Cpgc20ControlRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT       CpgcSeqCtl
  );

/**
  This function writes to all enabled CADB CTL registers (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CadbControl   - Data to be written to all CADB CTL registers.

  @retval Nothing.
**/
void
Cadb20ControlRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  CH0_SC0_CR_CADB_CTL_STRUCT           CadbControl
  );

/**
  This function writes to all enabled CADB CFG registers (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CadbConfig    - Data to be written to all CADB CFG registers.

  @retval Nothing.
**/
void
Cadb20ConfigRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  CH0_SC0_CR_CADB_CFG_STRUCT           CadbConfig
  );

/**
  This function writes to all enabled CADB_AO_MRSCFG registers (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CadbMrsConfig - Data to be written to all CADB_AO_MRSCFG registers.

  @retval Nothing.
**/
void
Cadb20MrsConfigRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  CH0_SC0_CR_CADB_AO_MRSCFG_STRUCT     CadbMrsConfig
  );

/**
  This function checks the value of CADB_STATUS.TEST_DONE bit for all enabled CADB engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.

  @retval 1 - if all enabled engines are done, otherwise 0
**/
UINT32
Cadb20TestDoneStatus (
  IN  MrcParameters *const  MrcData
  );

/**
  This function writes Command Instructions to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData        - Pointer to MRC global data.
  @param[in]  CmdInstruct    - Array of Command Instructions
  @param[in]  NumInstruct    - Number of Instructions

  @retval MrcStatus - mrcSuccess if does not exceed command instruction registers otherwise mrcFail
**/
MrcStatus
Cpgc20CmdInstructWrite (
  IN  MrcParameters *const                           MrcData,
  IN  CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT  *CmdInstruct,
  IN  UINT8                                          NumInstruct
  );

/**
  This function writes Algorithm Instructions to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData               - Pointer to MRC global data.
  @param[in]  AlgoInstruct          - Array of Algorithm Instructions
  @param[in]  AlgoInstructControl   - Algorithm Instruction Control setting to program based on ValidMask
  @param[in]  AlgoWaitEventControl  - Algorithm Wait Event Control setting to program
  @param[in]  ValidMask             - Bit Mask of which Instructions are valid

  @retval Nothing.
**/
void
Cpgc20AlgoInstructWrite (
  IN  MrcParameters *const                                  MrcData,
  IN  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT       *AlgoInstruct,
  IN  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT  AlgoInstructControl,
  IN  CH0_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT  AlgoWaitEventControl,
  IN  UINT8                                                 ValidMask
  );

/**
  This function writes Data Instructions to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData        - Pointer to MRC global data.
  @param[in]  DataInstruct   - Array of Data Instructions
  @param[in]  ValidMask      - Bit Mask of which Instructions are valid

  @retval Nothing.
**/
void
Cpgc20DataInstructWrite (
  IN  MrcParameters *const                        MrcData,
  IN  CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT  *DataInstruct,
  IN  UINT8                                       ValidMask
  );

/**
  This function sets up Address related registers (ADDRESS_INSTRUCTION, REGION_LOW_ROW, REGION_LOW_COL, ADDRESS_SIZE) to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  AddressOrder      - Address Instruction Order
  @param[in]  AddressDirection  - Address Instruction Direction
  @param[in]  LastValidInstruct - Last Valid Address Instruction
  @param[in]  RowStart          - Starting Row Address
  @param[in]  ColStart          - Starting Column Address
  @param[in]  RowSizeBits       - Memory Region/Block Bits Size for Row
  @param[in]  ColSizeBits       - Memory Region/Block Bits Size for Column
  @param[in]  BankSize          - # of Banks (Base 1 numbering)
  @param[in]  EnCADB            - Set up the address ordering for Command stress

  @retval Nothing.
**/
void
Cpgc20AddressSetup (
  IN  MrcParameters *const            MrcData,
  IN  CPGC20_ADDRESS_INCREMENT_ORDER  AddressOrder,
  IN  CPGC20_ADDRESS_DIRECTION        AddressDirection,
  IN  UINT8                           LastValidInstruct,
  IN  UINT32                          RowStart,
  IN  UINT16                          ColStart,
  IN  UINT8                           RowSizeBits,
  IN  UINT8                           ColSizeBits,
  IN  UINT8                           BankSize,
  IN  UINT8                           EnCADB
  );

/**
  This function sets up ADDRESS_SIZE register per channel according to the Bank/Row/Col size of the given Rank.
  This is used in memory scrubbing.
  The register will be updated on all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  Rank              - Rank to work on

**/
void
Cpgc20AddressSetupScrub (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Rank
  );

/**
  This function sets up Address related registers for CMD stress to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.

  @retval Nothing.
**/
void
Cpgc20AddressSetupCmdStress (
  IN  MrcParameters *const  MrcData
  );

/**
  This function sets up Base Repeats to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  Burst             - Number of Cachelines (Should be power of 2)
  @param[in]  Ranks             - # of Ranks to test

  @retval Value written to CPGC2_BASE_REPEATS.
**/
UINT32
Cpgc20BaseRepeats (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Burst,
  IN  UINT32                Ranks
  );

/**
  This function sets up Base Repeats for a given CPGC engine (per Channel / SubChannel).
  The function doesn't check for ch/subch presence.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Channel     - Channel to work on
  @param[in]  SubChannel  - SubChannel to work on
  @param[in]  Burst       - Number of Cachelines (Should be power of 2)
  @param[in]  Ranks       - # of Ranks to test

  @retval Value written to CPGC2_BASE_REPEATS.
**/
UINT32
Cpgc20BaseRepeatsChSubch (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                SubChannel,
  IN  UINT32                Burst,
  IN  UINT32                Ranks
  );

/**
  This function sets up Registers for Basic Mem Test to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  Burst             - Number of CL transactions per algorithm instruction within 1 BlockRepeat (outer loop)
  @param[in]  LoopCount         - Total # of CL transactions
  @param[in]  Ranks             - # of Ranks

  @retval Nothing.
**/
void
Cpgc20BasicMemTest (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Burst,
  IN  UINT32                LoopCount,
  IN  UINT8                 Ranks
  );

/**
  This function adjusts register settings that are based on # of ranks being tested for the channel/subChannel provided.

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  Channel           - Channel
  @param[in]  SubChannel        - SubChannel
  @param[in]  OrigRank          - Original # of Ranks
  @param[in]  NewRank           - New # of Ranks

  @retval Nothing.
**/
void
Cpgc20AdjustNumOfRanks (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 Channel,
  IN  UINT8                 SubChannel,
  IN  UINT8                 OrigRank,
  IN  UINT8                 NewRank
  );

#endif // _CPGC_20_TEST_CTL_H_
