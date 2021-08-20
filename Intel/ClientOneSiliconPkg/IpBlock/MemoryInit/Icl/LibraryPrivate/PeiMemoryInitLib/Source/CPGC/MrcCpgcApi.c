/** @file
  This file implements an interface between the MRC and the different
  versions of CPGC.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#include "MrcInterface.h"
#include "MrcCpgcOffsets.h"
#include "MrcCommon.h"
#include "MrcCpgcApi.h"
#include "Cpgc20.h"
#include "Cpgc20TestCtl.h"
#include "Cpgc20Patterns.h"

///
/// External Function Definitions
///

/**
  This function will select the engines to enable.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  DataChMask  - Bit mask of Channels to select: 0x1 - Channel 0 Enhanced Channel 0 & 1, 0x2 - Channel 1 Enhanced Channel 0 & 1.
  @param[in]  CmdChMask   - Bit mask of channels to select: 0x1 - Channel 0, 0x2 - Channel 1.
  @param[in]  SubChMask   - Bit mask of SubChannels to select: 0x1 - Subchannel 0, 0x2 - Subchannel 1, rest - all Subchannels

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSelectEngines (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DataChMask,
  IN  UINT32                CmdChMask,
  IN  UINT32                SubChMask
  )
{
  MrcStatus Status;
  Status = mrcSuccess;
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Status = Cpgc20SelectEngines (MrcData, DataChMask, CmdChMask, SubChMask);
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function will program the patterns passed in into the Pattern Generators.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Pattern     - Array of 64-bit patterns.
  @param[in]  PatLen      - Number of Patterns to program.
  @param[in]  Start       - Starting Chunk of pattern programming.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetCadbPgPattern (
  IN  MrcParameters *const  MrcData,
  IN  UINT64_STRUCT         Pattern[CADB_20_MAX_CHUNKS],
  IN  UINT32                PatLen,
  IN  UINT32                Start
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cadb20ProgramPatGen (MrcData, Start, PatLen, Pattern);
      break;

    default:
      return mrcFail;
      break;
  }

  return mrcSuccess;
}

/**
  This function will configure the pattern rotation for dynamic and static patterns.
  It is required to call MrcSelectEngines() before this function is called.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[in]  PatCtlPtr - Pointer to rotation configuration.
  @param[in]  Channel   - Channel specifier for static patterns.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcProgramDataPatternRotation (
  IN  MrcParameters   *const  MrcData,
  IN  MRC_PATTERN_CTL *const  PatCtlPtr,
  IN  UINT32                  Channel
  )
{
  MrcStatus Status;
  UINT16    RotateRate;
  CPGC20_INVERT_DC_MODE  InvertDcMode;

  Status = mrcSuccess;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      RotateRate = 0;     // No data rotation for Static and DC
      if (PatCtlPtr->PatSource == MrcPatSrcDynamic) {
        RotateRate = PatCtlPtr->IncRate;
      }
      if (PatCtlPtr->PatSource == MrcPatSrcAllZeroes) {
        Cpgc20SetPgInvDcEn (MrcData, 0xFFFFFFFFFFFFFFFFULL, 0xFF);  // Enable DC on all lanes, including ECC
        InvertDcMode = Cpgc20DcMode;
      } else {
        Cpgc20ConfigPgRotation (MrcData, RotateRate);
        Cpgc20SetPgInvDcEn (MrcData, 0, 0);                         // Disable DC/Invert
        InvertDcMode = Cpgc20InvertMode;
      }
      Cpgc20SetPgInvDcCfg (MrcData, InvertDcMode, 0, FALSE, 0, 0xAA);
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function programs the Error Mask for Cacheline and UI comparisons.
  A value of 1 enables error checking.

  @param[in]  MrcData       - Pointer to global MRC data.
  @param[in]  Channel       - 0-based index, Channel to configure.
  @param[in]  CachelineMask - Bit mask of cachelines to enable.
  @param[in]  ChunkMask     - Bit mask of chunks to enable.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetChunkAndClErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                CachelineMask,
  IN  UINT32                ChunkMask
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20SetChunkClErrMsk (MrcData, Channel, CachelineMask, ChunkMask);
      break;

    default:
      Status = mrcFail;
  }

  return Status;
}

/**
  This function programs the Error Mask for Data and ECC bit lanes.
  A value of 1 enables error checking for that bit.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[in]  Channel   - 0-based index, Channel to configure.
  @param[in]  DataMask  - Bit mask of Data bits to check.
  @param[in]  EccMask   - Bit mask of ECC bits to check.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetDataAndEccErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT64                DataMask,
  IN  UINT8                 EccMask
  )
{
  MrcStatus     Status;
  UINT64_STRUCT SubChErrMsk;
  UINT32        Offset;
  UINT64        DataValue;
  UINT8         EccValue;
  CH0_SC0_CR_CPGC_ERR_XLNEN_STRUCT Cpgc20EccErrMskRankMask;

  Status = mrcSuccess;

  // Using bitwise complement for Masks as the register fields are enabled when 0 and disabled when 1
  DataValue = ~DataMask;
  EccValue = ~EccMask;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      // We set the entire x64 channel.
      SubChErrMsk.Data = DataValue;
      Cpgc20SetDataErrMsk (MrcData, 1 << Channel, 0x3, 0x1, SubChErrMsk.Data32.Low);
      Cpgc20SetDataErrMsk (MrcData, 1 << Channel, 0x3, 0x2, SubChErrMsk.Data32.High);
      if (MrcData->Outputs.EccSupport) {
        Offset = MrcGetEccErrMskRankErrMskOffset (MrcData, Channel, 0);
        Cpgc20EccErrMskRankMask.Data = MrcReadCR (MrcData, Offset);
        Cpgc20EccErrMskRankMask.Bits.ECC_ERRCHK_MASK = EccValue;
        MrcWriteCR (MrcData, Offset, Cpgc20EccErrMskRankMask.Data);
      }
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function programs the test loop count.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  Channel   - Zero based index of channel to access.
  @param[in]  LoopCount - Number of sequence iterations. 0 means infinite test.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetLoopcount (
  IN MrcParameters *const  MrcData,
  IN UINT32                Channel,
  IN UINT32                LoopCount
  )
{
  MrcIntOutput             *MrcIntData;
  UINT32                   SubCh;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        Cpgc20GetSetLoopCount (MrcData, Channel, SubCh, FALSE, &LoopCount);
      }
      break;

    default:
      return mrcFail;
      break;
  }

  return mrcSuccess;
}

/**
  This function programs the LFSR seeds to the data SubChannels,
  and command channels requested.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  DataChMask  - Bit mask of Channels to select: 0x1 - Channel 0 Enhanced Channel 0 & 1, 0x2 - Channel 1 Enhanced Channel 0 & 1.
  @param[in]  CmdChMask   - Bit mask of channels to select: 0x1 - Channel 0, 0x2 - Channel 1.
  @param[in]  Seeds       - List of seeds to program to the LFSRs.
  @param[in]  Start       - 0-based index specifying which Mux to start program.
  @param[in]  SeedCount   - Number of seeds to program.  The length of parameter "Seeds".

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetLsfrSeeds (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DataChMask,
  IN  UINT32                CmdChMask,
  IN  UINT32        *const  Seeds,
  IN  UINT32                Start,
  IN  UINT32                SeedCount
  )
{
  MrcSelectEngines (MrcData, DataChMask, CmdChMask, 0);
  MrcInitCpgcPgMux (MrcData, Seeds, (UINT8) Start, (UINT8) SeedCount);
  return mrcSuccess;
}

/**
  This function programs the test engine stop condition.

  @param[in]  MrcData         - Pointer to MRC global data.
  @param[in]  Channel         - 0-based index Channel to program.
  @param[in]  StopType        - MRC_TEST_STOP_TYPE: NSOE, NTHSOE, ABGSOE, ALSOE.
  @param[in]  NumberOfErrors  - Number of errors required to stop the test when StopType is NTHSOE.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetupTestErrCtl (
  IN  MrcParameters       *const  MrcData,
  IN  UINT32                      Channel,
  IN  MRC_TEST_STOP_TYPE          StopType,
  IN  UINT32                      NumberOfErrors
  )
{
  MrcStatus Status;

  Status = mrcSuccess;
  MrcData->Outputs.ReutStopType = StopType;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20SetupTestErrCtl (MrcData, Channel, StopType, NumberOfErrors);
      break;

    default:
      Status = mrcFail;
  }

  return Status;
}

/**
  This function will Setup REUT Error Counters to count errors for specified type.

  @param[in]  MrcData           - Include all MRC global data.
  @param[in]  Channel           - Desired Channel.
  @param[in]  SubChannel        - Desired SubChannel. Valid only when ErrControl is ErrCounterCtlAllLanes and Enhanced Channel Mode is enabled.
  @param[in]  CounterSelect     - Specifies in register which Counter to setup. Valid for ErrControl values:
                                  ErrCounterCtlPerLane, ErrCounterCtlPerByte, or ErrCounterCtlPerChunk.
  @param[in]  ErrControl        - Specifies which type of error counter read will be executed.

  @retval mrcWrongInputParameter if ErrControl is an incorrect value, otherwise mrcSuccess.
**/
MrcStatus
MrcSetupErrCounterCtl (
  IN  MrcParameters *const      MrcData,
  IN  UINT32                    Channel,
  IN  UINT32                    SubChannel,
  IN  UINT8                     CounterSelect,
  IN  MRC_ERR_COUNTER_CTL_TYPE  ErrControl
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      if (!MrcSubChannelExist (MrcData, Channel, SubChannel)) {
        Status = mrcWrongInputParameter;
      } else {
        if (MrcData->Outputs.EnhancedChannelMode) {
          // Byte should be [0..3] in enhanced channel mode
          CounterSelect = CounterSelect % 4;
        } else {
          // There is only subch0 in DDR4 mode
          SubChannel = 0;
        }
        switch (ErrControl) {
          case ErrCounterCtlAllLanes:
            Status = Cpgc20SetupErrCounterCtl (MrcData, Channel, SubChannel, 0, ErrControl, 0);
            break;

          case ErrCounterCtlPerByte:
          case ErrCounterCtlPerChunk:
          case ErrCounterCtlPerLane:
            Status = Cpgc20SetupErrCounterCtl (MrcData, Channel, SubChannel, CounterSelect, ErrControl, CounterSelect);
            break;

          default:
            Status = mrcWrongInputParameter;
            break;
        }
      }
      break;

    default:
      Status = mrcFail;
      break;
  }
  return Status;
}

/**
  This function returns the Bit Group Error status results.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel.
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
MrcGetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Channel,
  IN  UINT32                  SubChannel,
  OUT UINT8                   *Status
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20GetBitGroupErrStatus (MrcData, Channel, SubChannel, Status);
      break;

    default:
      break;
  }
}

/**
  This function returns the Error status results of the specified Error Type.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel. This parameter is valid regardless of Enhanced Channel Mode setting.
  @param[in]  Param       - Specifies which type of error status read will be executed.
  @param[out] Buffer      - Pointer to buffer which register values will be read into.
                              Error status bits will be returned starting with bit zero. Logical shifting will not be handled by this function.

  @retval Returns mrcWrongInputParameter if Param value is not supported by this function, otherwise mrcSuccess.
**/
MrcStatus
MrcGetMiscErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Channel,
  IN  UINT32                  SubChannel,
  IN  MRC_ERR_STATUS_TYPE     Param,
  OUT UINT64          *const  Buffer
  )
{
  MrcStatus Status;

  switch (Param) {
    case ByteGroupErrStatus:
    case ChunkErrStatus:
    case RankErrStatus:
    case NthErrStatus:
    case NthErrOverflow:
    case AlertErrStatus:
    case WdbRdChunkNumStatus:
      switch (MrcData->Inputs.TestEngine) {
        case MrcTeCpgc20:
          Status = Cpgc20GetErrEccChunkRankByteStatus (MrcData, Channel, SubChannel, Param, Buffer);
          break;
        default:
          Status = mrcWrongInputParameter;
          break;
      }

    default:
      Status = mrcWrongInputParameter;
      break;
  }
  return Status;
}

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
  @param[in]  Channel     - Zero based index selecting the channel to access.
  @param[in]  L2pBankList - Array of logical-to-physical Bank Mapping.
  @param[in]  Length      - Array length of L2pBankList buffer.
  @param[in]  IsGet       - Boolean; if TRUE, request is a Get, otherwise Set.

  @retval MrcStatus.
**/
MrcStatus
MrcGetSetBankSequence (
  IN  MrcParameters *const      MrcData,
  IN  UINT32                    Channel,
  IN  MRC_BG_BANK_PAIR  *const  L2pBankList,
  IN  UINT32                    Length,
  IN  BOOLEAN                   IsGet
  )
{
  MrcInput  *Inputs;
  MrcStatus Status;
  UINT8     BankList[CPGC20_MAX_BANKS_PER_CHANNEL];
  UINT8     Index;
  UINT8     BgOffset;
  UINT8     BankMask;

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;

  switch (Inputs->TestEngine) {
    case MrcTeCpgc20:
      if (Length > CPGC20_MAX_BANKS_PER_CHANNEL) {
        Status = mrcWrongInputParameter;
      } else {
        BgOffset = CPGC20_BANK_GROUP_FIELD_OFFSET;
        BankMask = (1 << BgOffset) - 1;
        if (!IsGet) {
          for (Index = 0; Index < Length; Index++) {
            BankList[Index] = (L2pBankList[Index].BankGroup << BgOffset) | (L2pBankList[Index].Bank);
          }
        }
        Cpgc20GetSetBankMap (MrcData, Channel, BankList, Length, IsGet);
        if (IsGet) {
          for (Index = 0; Index < Length; Index++) {
            L2pBankList[Index].BankGroup = BankList[Index] >> BgOffset;
            L2pBankList[Index].Bank = BankList[Index] & (BankMask);
          }
        }
      }
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function returns the Error Counter status.

  @param[in]  MrcData       - Include all MRC global data.
  @param[in]  Channel       - Desired channel.
  @param[in]  SubChannel    - Desired subchannel. Only valid when ErrControl is ErrCounterCtlAllLanes.
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
  IN  UINT32                    Channel,
  IN  UINT32                    SubChannel,
  IN  UINT8                     CounterSelect,
  IN  MRC_ERR_COUNTER_CTL_TYPE  ErrControl,
  OUT UINT32          *const    Status,
  OUT BOOLEAN         *const    Overflow
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      if (!MrcSubChannelExist (MrcData, Channel, SubChannel)) {
        *Status = 0xFFFFFFFF;
      } else {
        if (MrcData->Outputs.EnhancedChannelMode) {
          // Byte should be [0..3] in enhanced channel mode
          CounterSelect = CounterSelect % 4;
        } else {
          // There is only subch0 in DDR4 mode
          SubChannel = 0;
        }
        switch (ErrControl) {
          case ErrCounterCtlAllLanes:
            Cpgc20GetErrCounterStatus (MrcData, Channel, SubChannel, 0, Status, Overflow);
            break;

          case ErrCounterCtlPerByte:
          case ErrCounterCtlPerChunk:
          case ErrCounterCtlPerLane:
            Cpgc20GetErrCounterStatus (MrcData, Channel, SubChannel, CounterSelect, Status, Overflow);
            break;

          default:
            break;
        }
      }
      break;

    default:
      *Status = 0xFFFFFFFF;
      break;
  }
}

/**
  This function will program the CPGC PGs Mux Seeds.  The PGs must be selected before this call.

  @param[in] MrcData   - Global MRC data.
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR.
  @param[in] Start     - Zero based index which Unisequencer to start programming.
  @param[in] SeedCount - Number of seeds in the array.

  @retval - Nothing
**/
void
MrcInitCpgcPgMux (
  IN MrcParameters *const MrcData,
  IN const UINT32  *const Seeds,
  IN const UINT8          Start,
  IN const UINT8          SeedCount
  )
{
  UINT8   Index;
  UINT8   Stop;

  Stop = Start + SeedCount;
  for (Index = Start; Index < Stop; Index++) {
    switch (MrcData->Inputs.TestEngine) {
      case MrcTeCpgc20:
        Cpgc20LfsrSeed (MrcData, Seeds[Index], Index);
        break;
      default:
        break;
    }
  }
}

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
  )
{
  UINT8   Index;
  UINT8   Stop;

  Stop = Start + SeedCount;
  for (Index = Start; Index < Stop; Index++) {
    switch (MrcData->Inputs.TestEngine) {
      case MrcTeCpgc20:
        Cadb20LfsrSeed (MrcData, Seeds[Index], Index);
        break;

      default:
        break;
    }
  }
}

/**
  This function will enable or disable CPGC engines on all channels.
  @todo <ICL>: Move to GetSet infrastructure.

  @param[in] MrcData    - Global MRC data structure
  @param[in] ActiveMode - If true, enable CPGC engines. If false, set to idle mode.

  @retval - Nothing
**/
void
MrcSetCpgcInitMode (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              ActiveMode
  )
{
  MrcOutput   *Outputs;
  UINT32      Offset;
  UINT8       Channel;
  UINT8       SubCh;
  CH0_SC0_CR_CPGC_SEQ_CFG_A_STRUCT CpgcSeqCfgA;

  Outputs = &MrcData->Outputs;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          Offset = MrcGetCpgcSeqCfgOffset (MrcData, Channel, SubCh);
          CpgcSeqCfgA.Data =  MrcReadCR (MrcData, Offset);
          CpgcSeqCfgA.Bits.INITIALIZATION_MODE = ActiveMode ? CPGC20_ACTIVE_MODE : CPGC20_IDLE_MODE;
          MrcWriteCR (MrcData, Offset, (UINT32) CpgcSeqCfgA.Data);
        }
      }
    }
  }
}

