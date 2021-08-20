/** @file
  This file implements functions for setting up test control
  registers for CPGC 2.0.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "Cpgc20Patterns.h"
#include "Cpgc20.h"
#include "MrcCpgcOffsets.h"

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
  )
{
  UINT32  Offset;
  UINT32  SubCh;
  BOOLEAN Lpddr4;
  MrcIntOutput                          *MrcIntData;
  CH0_SC0_CR_CPGC_ERR_CTL_STRUCT     Cpgc20ErrCtl;
  CH0_SC0_CR_CPGC_ERR_LNEN_HI_STRUCT Cpgc20ErrChunkMask;


  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Lpddr4 = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4);
  for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
    if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
      continue;
    }
    Offset = MrcGetTestErrCtlOffset (MrcData, Channel, SubCh);
    Cpgc20ErrCtl.Data = MrcReadCR (MrcData, Offset);
    Cpgc20ErrCtl.Bits.ERRCHK_MASK_CACHELINE = CachelineMask;
    Cpgc20ErrCtl.Bits.ERRCHK_MASK_CHUNK = ChunkMask;
    MrcWriteCR (MrcData, Offset, Cpgc20ErrCtl.Data);

    if (Lpddr4) {
      Offset = MrcGetCpgcErrCheckingHighOffset (MrcData, Channel, SubCh);
      Cpgc20ErrChunkMask.Data = ChunkMask;
      MrcWriteCR (MrcData, Offset, Cpgc20ErrChunkMask.Data);
    }
  }
}

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
  )
{
  UINT32  Channel;
  UINT32  Offset;
  UINT32  SubCh;
  UINT32  Word;
  UINT32  MaxEngine;
  UINT32  MaxWords;
  BOOLEAN Lpddr4;
  MrcIntOutput *MrcIntData;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Lpddr4 = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4);
  MaxEngine = MrcIntData->SubChEngCount;
  MaxWords = Lpddr4 ? 1 : 2;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((ChMask >> Channel) & 1) != 1) {
      continue;
    }
    for (SubCh = 0; SubCh < MaxEngine; SubCh++) {
      if (((SubChMask >> SubCh) & 1) != 1) {
        continue;
      }
      for (Word = 0; Word < MaxWords; Word++) {
        if (((WordMask >> Word) & 1) != 1) {
          continue;
        }
        Offset = (Word == 0) ? MrcGetCpgcErrCheckingLowOffset (MrcData, Channel, SubCh) : MrcGetCpgcErrCheckingHighOffset (MrcData, Channel, SubCh);
        MrcWriteCR (MrcData, Offset, ErrMask);
      }
    }
  }
}

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
  )
{
  UINT32                          Offset;
  UINT32                          SubCh;
  UINT8                           ChanSubChanMask;
  MrcIntOutput                    *MrcIntData;
  CH0_SC0_CR_CPGC_ERR_CTL_STRUCT  Cpgc20ErrCtl;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
    if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubCh) == 0) {
        continue;
    }
    Offset = MrcGetTestErrCtlOffset (MrcData, Channel, SubCh);
    Cpgc20ErrCtl.Data = MrcReadCR (MrcData, Offset);
    Cpgc20ErrCtl.Bits.STOP_ON_ERROR_CTL = StopType;
    Cpgc20ErrCtl.Bits.STOP_ON_N = NumOfErr;
    MrcWriteCR (MrcData, Offset, Cpgc20ErrCtl.Data);
  }
}

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
  )
{
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  UINT32            Offset;
  UINT8             MaxChunk;
  CH0_SC0_CR_CPGC_ERR_CNTRCTL_0_STRUCT Cpgc20SubChErrCounterCtl;

  Status  = mrcSuccess;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (ErrControl) {
    // Setup Error Counter Control for all lanes
    case ErrCounterCtlAllLanes:
      if (CounterSelect > 8) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an invalid error counter. Counter: %u\n", CounterSelect);
        Status = mrcWrongInputParameter;
      }
      break;

    // Setup Error Counter Control for particular lane
    // @todo: This always uses counter 0 for that Channel to count the lane.  This does not allow counting multiple lanes at a time, and should be fixed if feature is needed.
    // @todo: Return Error as this mode isn't supported.
    case ErrCounterCtlPerLane:
      if ((CounterSetting > 72) || (CounterSelect > 8)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid lane. Counter: %u, Lane: %u\n", CounterSelect, CounterSetting);
        Status = mrcWrongInputParameter;
      }
      break;

    // Setup Error Counter Control for particular byte
    case ErrCounterCtlPerByte:
      if ((CounterSetting > 8) || (CounterSelect > 8)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid byte. Counter: %u, Byte: %u\n", CounterSelect, CounterSetting);
        Status = mrcWrongInputParameter;
      }
      break;

    // Setup Error Counter Control for particular chunk
    case ErrCounterCtlPerChunk:
      MaxChunk = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 15 : 7;
      if ((CounterSetting > MaxChunk) || (CounterSelect > 8)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid chunk. Counter: %u, Chunk: %u\n", CounterSelect, CounterSetting);
        Status = mrcWrongInputParameter;
      }
      break;

    default:
      Status = mrcWrongInputParameter;
      break;
  }
  if (Status == mrcSuccess) {
    Offset = (OFFSET_CALC_CH_SUBCH (CH0_SC0_CR_CPGC_ERR_CNTRCTL_0_REG, CH1_SC0_CR_CPGC_ERR_CNTRCTL_0_REG, Channel, CH0_SC1_CR_CPGC_ERR_CNTRCTL_0_REG, SubChannel)) +
           ((CH0_SC0_CR_CPGC_ERR_CNTRCTL_1_REG - CH0_SC0_CR_CPGC_ERR_CNTRCTL_0_REG) * CounterSelect);
    Cpgc20SubChErrCounterCtl.Data = 0;
    Cpgc20SubChErrCounterCtl.Bits.COUNTER_POINTER = CounterSetting;
    Cpgc20SubChErrCounterCtl.Bits.COUNTER_CONTROL = ErrControl;
    MrcWriteCR (MrcData, Offset, Cpgc20SubChErrCounterCtl.Data);
  }
  return Status;
}

/**
  This function returns the Error status results for specified MRC_ERR_STATUS_TYPE.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel. For DDR4 subch0 will read the error status of all bytes.
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
  )
{
  MrcOutput                                     *Outputs;
  MrcIntOutput                                  *MrcIntData;
  UINT64                                        Value;
  UINT32                                        Offset;
  UINT32                                        Offset2;
  UINT32                                        CRValue;
  UINT8                                         ChanSubChanMask;
  BOOLEAN                                       EccSupport;
  CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT  CpgcErrByteNthStatus;
  CH0_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT CpgcErrEccChunkRank;

  Outputs         = &MrcData->Outputs;
  EccSupport      = Outputs->EccSupport;
  MrcIntData      = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  Value = 0;
  if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
    return mrcWrongInputParameter;
  }
  if ((Param == ByteGroupErrStatus) || (Param == WdbRdChunkNumStatus) || (Param == NthErrStatus)) {
    Offset = OFFSET_CALC_CH_SUBCH (
              CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG,
              CH1_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG, Channel,
              CH0_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG, SubChannel);
  } else if ((Param == RankErrStatus) || (Param == ChunkErrStatus)) {
    Offset = OFFSET_CALC_CH_SUBCH (
              CH0_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG,
              CH1_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Channel,
              CH0_SC1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, SubChannel);
  } else {
    Offset = 0;
  }
  Offset2 = OFFSET_CALC_CH_SUBCH (
              CH0_SC0_CR_CPGC_ERR_STAT47_REG,
              CH1_SC0_CR_CPGC_ERR_STAT47_REG, Channel,
              CH0_SC1_CR_CPGC_ERR_STAT47_REG, SubChannel);

  CRValue = MrcReadCR (MrcData, Offset);
  CpgcErrByteNthStatus.Data = CRValue;
  CpgcErrEccChunkRank.Data = CRValue;

  switch (Param) {
    case ByteGroupErrStatus:
      Value = CpgcErrByteNthStatus.Bits.BYTEGRP_ERR_STAT;
      if (EccSupport) {
        Value |= (CpgcErrByteNthStatus.Bits.ECCGRP_ERR_STAT << CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_OFF);
      }
      break;

    case RankErrStatus:
      Value = CpgcErrEccChunkRank.Bits.RANK_ERR_STAT;
      break;

    case WdbRdChunkNumStatus:
      Value = CpgcErrByteNthStatus.Bits.RD_CHUNK_NUM_STAT;
      break;

    case NthErrStatus:
      Value = CpgcErrByteNthStatus.Bits.Nth_ERROR;
      break;

    case ChunkErrStatus:
      if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
        Value = MrcReadCR (MrcData, Offset2);  // LP4 chunk error status is in CPGC_ERR_STAT47.LANE_ERR_STAT_HI
      } else {
        Value = CpgcErrEccChunkRank.Bits.CHUNK_ERR_STAT;
      }
//    if (!(Outputs->EnhancedChannelMode)) {
//      if (EccSupport) {
//        Value |= (MrcCall->MrcRightShift64 (Value, (REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_WID - 8)));
//      }
//      Value &= 0xFF;
//    }
      break;

    case AlertErrStatus:
//    Value = ReutSubChErrChunkRankByteNthStatus.Bits.Alert_Error_Status;
//    break;

    case NthErrOverflow:
//    Value = ReutSubChErrChunkRankByteNthStatus.Bits.Nth_Error_Overflow;
//    break;

    default:
      return mrcWrongInputParameter;
  }
  MRC_DEBUG_ASSERT (Buffer != NULL, &MrcData->Outputs.Debug, "%s Null Pointer", gErrString);
  *Buffer = Value;
  return mrcSuccess;
}

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
  )
{
  UINT32  Offset;

  Offset = OFFSET_CALC_CH_SUBCH (
            CH0_SC0_CR_CPGC2_BLOCK_REPEATS_REG,
            CH1_SC0_CR_CPGC2_BLOCK_REPEATS_REG, Channel,
            CH0_SC1_CR_CPGC2_BLOCK_REPEATS_REG, SubCh);
  if (IsGet) {
    *LoopCount = MrcReadCR (MrcData, Offset);
  } else {
    // MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "Cpgc20GetSetLoopCount: ch%d sch%d LoopCount = %d\n", Channel, SubCh, *LoopCount);
    MrcWriteCR (MrcData, Offset, *LoopCount);
  }
}

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
  )
{
  UINT32        RegData;
  UINT32        RegIndex;
  UINT32        Index;
  UINT32        BanksPerReg;
  UINT32        Offset;
  UINT32        CrIncrement;
  UINT32        FieldOffsetStep;
  UINT32        FieldMask;
  UINT32        FieldOffset;
  BOOLEAN       EndOfRegister;

  RegData = 0;

  BanksPerReg = 6;
  Offset = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG, CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG, Channel);
  CrIncrement = CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_REG - CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG;
  FieldOffsetStep = CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_OFF;
  FieldMask = CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_MSK;

  for (Index = 0; Index < Count; Index++) {
    RegIndex      = Index % BanksPerReg;
    FieldOffset   = RegIndex * FieldOffsetStep;
    EndOfRegister = (RegIndex == (BanksPerReg - 1)) || (Index == (Count - 1));
    if (RegIndex == 0) {
      RegData = MrcReadCR (MrcData, Offset);
    }
    if (IsGet) {
      Banks[Index] = (UINT8) ((RegData >> FieldOffset) & FieldMask);
    } else {
      RegData &= ~(FieldMask << FieldOffset);
      RegData |= (Banks[Index] & FieldMask) << FieldOffset;
      // If we're at the end of Banks to write, or we're at the end of the banks in the register,
      // write out the Register data.
      if (EndOfRegister) {
        MrcWriteCR (MrcData, Offset, RegData);
      }
    }
    if (EndOfRegister) {
      // Update the offset to the next register
      Offset += CrIncrement;
    }
  }
}

/**
  This function returns the Bit Group Error status results.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Channel     - Desired Channel.
  @param[in]  SubChannel  - Desired SubChannel. Ignored for DDR4 - we get all bit errors from subch0.
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
Cpgc20GetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Channel,
  IN  UINT32                  SubChannel,
  OUT UINT8                   *Status
  )
{
  MrcOutput     *Outputs;
  UINT32        ErrDataStatus;
  UINT32        Offset1;
  UINT32        Offset2;
  UINT8         SubCh;
  UINT8         SubChBitmask;
  UINT8         Byte;
  UINT8         StatusIndex;
  BOOLEAN       Ddr4;
  CH0_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT CpgcErrEccChunkRank;

  Outputs = &MrcData->Outputs;
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  if (Outputs->EnhancedChannelMode) {
    SubChBitmask = 1 << SubChannel;
  } else {
    SubChBitmask = 0x3;
  }

  Offset1 = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_ERR_STAT03_REG, CH1_SC0_CR_CPGC_ERR_STAT03_REG, Channel);
  Offset2 = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_ERR_STAT47_REG, CH1_SC0_CR_CPGC_ERR_STAT47_REG, Channel);

  MRC_DEBUG_ASSERT (Status != NULL, &Outputs->Debug, "%s Null Pointer", gErrString);

  for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
    if (((SubChBitmask >> SubCh) & 1) != 1) {
      continue;
    }
    Offset1 += ((CH0_SC1_CR_CPGC_ERR_STAT03_REG - CH0_SC0_CR_CPGC_ERR_STAT03_REG) * SubCh);
    ErrDataStatus = MrcReadCR (MrcData, (Ddr4 && SubCh) ? Offset2 : Offset1);
    StatusIndex = 4 * SubCh;

    for (Byte = 0; Byte < 4; Byte++) {
      Status[StatusIndex + Byte] = (ErrDataStatus >> (8 * Byte)) & 0xFF;
    }
  }

  if (Outputs->EccSupport) {
    Offset1 = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, CH1_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Channel);

    CpgcErrEccChunkRank.Data = MrcReadCR (MrcData, Offset1);

    Status[8] = (UINT8) CpgcErrEccChunkRank.Bits.ECC_LANE_ERR_STAT;
  }
}

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
  )
{
  UINT32    Offset;
  UINT32    Value;

  Offset = OFFSET_CALC_CH_SUBCH (
    CH0_SC0_CR_CPGC_ERR_CNTR_0_REG,
    CH1_SC0_CR_CPGC_ERR_CNTR_0_REG, Channel,
    CH0_SC1_CR_CPGC_ERR_CNTR_0_REG, SubCh);
  Offset += (CH0_SC0_CR_CPGC_ERR_CNTR_1_REG - CH0_SC0_CR_CPGC_ERR_CNTR_0_REG) * CounterSelect;
  Value = MrcReadCR (MrcData, Offset);

  MRC_DEBUG_ASSERT ((CounterStatus != NULL) && (Overflow != NULL), &MrcData->Outputs.Debug, "%s Null Pointer", gErrString);

  *CounterStatus = Value;

  Offset = OFFSET_CALC_CH_SUBCH (
    CH0_SC0_CR_CPGC_ERR_CNTR_OV_REG,
    CH1_SC0_CR_CPGC_ERR_CNTR_OV_REG, Channel,
    CH0_SC1_CR_CPGC_ERR_CNTR_OV_REG, SubCh);
  Value = MrcReadCR (MrcData, Offset);

  *Overflow = ((Value >> (CounterSelect % 9)) & 1) == 1;
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT32        Offset;
  CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT  CpgcStatus;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  // We use GLOBAL BIND mode, so program SEQ_CTL on subch 0 only.
  ChanSubChanMask = ChanSubChanMask & 0x05;

  if (CpgcSeqCtl.Bits.START_TEST == 1) {
    // If we are going to start a new test, clear TEST_DONE first
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
        if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
          continue;
        }
        Offset = OFFSET_CALC_CH_SUBCH (
                  CH0_SC0_CR_CPGC_SEQ_STATUS_REG,
                  CH1_SC0_CR_CPGC_SEQ_STATUS_REG, Channel,
                  CH0_SC1_CR_CPGC_SEQ_STATUS_REG, SubChannel);
        CpgcStatus.Data = MrcReadCR (MrcData, Offset);
        if (CpgcStatus.Bits.TEST_DONE == 1) {
          // Clear by writing a '1'
          MrcWriteCR (MrcData, Offset, CpgcStatus.Data);
        }
      }
    }
  } // if START_TEST

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC_SEQ_CTL_REG,
                CH1_SC0_CR_CPGC_SEQ_CTL_REG, Channel,
                CH0_SC1_CR_CPGC_SEQ_CTL_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, CpgcSeqCtl.Data);
    }
  }
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT32        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (CH0_SC0_CR_CADB_CTL_REG, CH1_SC0_CR_CADB_CTL_REG, Channel, CH0_SC1_CR_CADB_CTL_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, CadbControl.Data);
    }
  }
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT32        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CADB_CFG_REG,
                CH1_SC0_CR_CADB_CFG_REG, Channel,
                CH0_SC1_CR_CADB_CFG_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, CadbConfig.Data);
    }
  }
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT32        Channel;
  UINT32        SubChannel;
  UINT32        ChanSubChanMask;
  UINT32        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
        CH0_SC0_CR_CADB_AO_MRSCFG_REG,
        CH1_SC0_CR_CADB_AO_MRSCFG_REG, Channel,
        CH0_SC1_CR_CADB_AO_MRSCFG_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, CadbMrsConfig.Data);
    }
  }
}

/**
  This function checks the value of CADB_STATUS.TEST_DONE bit for all enabled CADB engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData       - Pointer to MRC global data.

  @retval 1 - if all enabled engines are done, otherwise 0
**/
UINT32
Cadb20TestDoneStatus (
  IN  MrcParameters *const  MrcData
  )
{
  MrcIntOutput                    *MrcIntData;
  UINT8                           Channel;
  UINT8                           SubChannel;
  UINT8                           ChanSubChanMask;
  UINT32                          TestDone;
  UINT32                          Offset;
  CH0_SC0_CR_CADB_STATUS_STRUCT   CadbStatus;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  TestDone = 1; // Assume all done

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (CH0_SC0_CR_CADB_STATUS_REG, CH1_SC0_CR_CADB_STATUS_REG, Channel, CH0_SC1_CR_CADB_STATUS_REG, SubChannel);
      CadbStatus.Data = MrcReadCR (MrcData, Offset);
      TestDone &= CadbStatus.Bits.TEST_DONE;
    }
  }
  return TestDone;
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT8         Index;
  UINT32        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  if (NumInstruct > CPGC20_MAX_COMMAND_INSTRUCTION) {
    return mrcFail;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG, CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG, Channel,
        CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_0_REG, SubChannel);
      for (Index = 0; Index < NumInstruct; Index++) {
        MrcWriteCR8 (MrcData, Offset, CmdInstruct[Index].Data);
        Offset += CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_1_REG - CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG;
      }
    }
  }
  return mrcSuccess;
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT8         Index;
  UINT32        Offset;
  UINT32        CtrlOffset;
  CH0_SC0_CR_CPGC2_WAIT_2_START_CONFIG_STRUCT WaitToStartCfg;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG,
                CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG, Channel,
                CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG, SubChannel);
      CtrlOffset = OFFSET_CALC_CH_SUBCH (
                    CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG,
                    CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG, Channel,
                    CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG, SubChannel);
      for (Index = 0; Index < CPGC20_MAX_ALGORITHM_INSTRUCTION; Index++) {
        if (ValidMask & (MRC_BIT0 << Index)) {
          MrcWriteCR8 (MrcData, Offset, AlgoInstruct[Index].Data);
          MrcWriteCR8 (MrcData, CtrlOffset, AlgoInstructControl.Data);
          Offset += CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_1_REG - CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG;
          CtrlOffset += CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_REG - CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG;
        } else {
          break;
        }
      }
      CtrlOffset = OFFSET_CALC_CH_SUBCH (
                    CH0_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG,
                    CH1_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG, Channel,
                    CH0_SC1_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG, SubChannel);
      MrcWriteCR (MrcData, CtrlOffset, AlgoWaitEventControl.Data);

      if (AlgoWaitEventControl.Bits.Wait_Clock_Frequency == CPGC20_NATIVE_DUNIT_FREQ) {
        Offset = OFFSET_CALC_CH_SUBCH (
                  CH0_SC0_CR_CPGC2_WAIT_2_START_CONFIG_REG,
                  CH1_SC0_CR_CPGC2_WAIT_2_START_CONFIG_REG, Channel,
                  CH0_SC1_CR_CPGC2_WAIT_2_START_CONFIG_REG, SubChannel);
        WaitToStartCfg.Data = MrcReadCR (MrcData, Offset);
        WaitToStartCfg.Bits.Clock_Freq = 1;
        MrcWriteCR (MrcData, Offset, WaitToStartCfg.Data);
      }
    }
  }
}

/**
  This function writes Algorithm Instructions to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT8         Index;
  UINT32        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_0_REG, CH1_SC0_CR_CPGC2_DATA_INSTRUCTION_0_REG, Channel,
        CH0_SC1_CR_CPGC2_DATA_INSTRUCTION_0_REG, SubChannel);
      for (Index = 0; Index < CPGC20_MAX_DATA_INSTRUCTION; Index++) {
        if (ValidMask & (MRC_BIT0 << Index)) {
          MrcWriteCR8 (MrcData, Offset, DataInstruct[Index].Data);
          Offset += CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_1_REG - CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_0_REG;
        } else {
          break;
        }
      }
    }
  }
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT8         Index;
  UINT32        Offset;
  CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT  Cpgc2AddrInstruct;
  CH0_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT           Cpgc2AddrSize;
  CH0_SC0_CR_CPGC2_REGION_LOW_ROW_STRUCT         Cpgc2LowRow;
  CH0_SC0_CR_CPGC2_REGION_LOW_COL_STRUCT         Cpgc2LowCol;
//  MrcDebug      *Debug;

//  Debug = &MrcData->Outputs.Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;

//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AddressOrder: %u, AddressDirection: %u, LastValidInstruct: %u\n", AddressOrder, AddressDirection, LastValidInstruct);
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RowStart: %u, RowSizeBits: 0x%x\n", RowStart, RowSizeBits);
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ColStart: %u, ColSizeBits: 0x%x\n", ColStart, ColSizeBits);

  Cpgc2AddrInstruct.Data = 0;
  Cpgc2AddrInstruct.Bits.Address_Order = AddressOrder;
  Cpgc2AddrInstruct.Bits.Address_Direction = AddressDirection;

  Cpgc2LowRow.Data = 0;
  Cpgc2LowRow.Bits.Low_Row = RowStart;

  Cpgc2LowCol.Data = 0;
  Cpgc2LowCol.Bits.Low_Col = ColStart;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG,
                CH1_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG, Channel,
                CH0_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG, SubChannel);
      for (Index = 0; Index < CPGC20_MAX_ADDRESS_INSTRUCTION; Index++) {
        Cpgc2AddrInstruct.Bits.Last = (LastValidInstruct == Index) ? 1 : 0;
        MrcWriteCR8 (MrcData, Offset, Cpgc2AddrInstruct.Data);
        Offset += CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_1_REG - CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG;
        if (LastValidInstruct == Index) {
          break;
        }
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_REGION_LOW_ROW_REG,
                CH1_SC0_CR_CPGC2_REGION_LOW_ROW_REG, Channel,
                CH0_SC1_CR_CPGC2_REGION_LOW_ROW_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, Cpgc2LowRow.Data);

      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_REGION_LOW_COL_REG,
                CH1_SC0_CR_CPGC2_REGION_LOW_COL_REG, Channel,
                CH0_SC1_CR_CPGC2_REGION_LOW_COL_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, Cpgc2LowCol.Data);

      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ADDRESS_SIZE_REG,
                CH1_SC0_CR_CPGC2_ADDRESS_SIZE_REG, Channel,
                CH0_SC1_CR_CPGC2_ADDRESS_SIZE_REG, SubChannel);
      Cpgc2AddrSize.Data = MrcReadCR (MrcData, Offset);
      // Row and Col bit sizes in BlockSize and RegionSize registers are exponential. Bank and Rank are linear "+1".
      Cpgc2AddrSize.Bits.Block_Size_Bits_Row  = EnCADB ? 0 : RowSizeBits; // In command stress we want Row to be updated together with Bank, so block size is zero
      Cpgc2AddrSize.Bits.Block_Size_Bits_Col  = EnCADB ? 2 : ColSizeBits; // In command stress we want Bank / Row update every 4 CLs
      Cpgc2AddrSize.Bits.Region_Size_Bits_Row = RowSizeBits;
      Cpgc2AddrSize.Bits.Region_Size_Bits_Col = ColSizeBits;
      Cpgc2AddrSize.Bits.Block_Size_Num_Banks = (BankSize) ? BankSize - 1 : 0;
      MrcWriteCR (MrcData, Offset, Cpgc2AddrSize.Data);
    }
  }
}

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
  )
{
  MrcDebug          *Debug;
  MrcIntOutput      *MrcIntData;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcDimmOut        *DimmOut;
  UINT8             Channel;
  UINT8             SubChannel;
  UINT8             ChanSubChanMask;
  UINT8             BankCount;
  UINT16            Columns;
  UINT32            Offset;
  UINT32            RowSizeBits;
  UINT32            ColSizeBits;
  UINT32            Burst;
  BOOLEAN           Ddr4;
  MRC_BG_BANK_PAIR  *BankMapping;
  CH0_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT  Cpgc2AddrSize;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      // We want to scrub the whole rank, so get the Bank/Row/Col size from this DIMM on this channel
      DimmOut = &ControllerOut->Channel[Channel].Dimm[RANK_TO_DIMM_NUMBER (Rank)];
      BankCount = DimmOut->BankGroups * DimmOut->Banks;
      RowSizeBits = MrcLog2 (DimmOut->RowSize) - 1;
      ColSizeBits = MrcLog2 (DimmOut->ColumnSize) - 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d SubCh%d R%d RowBits: %d, ColBits: %d, BankCount: %d\n", Channel, SubChannel, Rank, RowSizeBits, ColSizeBits, BankCount);

      // BL=8:  column increment is 2^3 per CL --> 10 - 3 = 7
      // BL=16: column increment is 2^4 per CL --> 10 - 4 = 6
      if (Ddr4) {
        ColSizeBits -= 3;
        Columns = DimmOut->ColumnSize / 8;
      } else { // LPDDR4
        ColSizeBits -= 4;
        Columns = DimmOut->ColumnSize / 16;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ADDRESS_SIZE_REG,
                CH1_SC0_CR_CPGC2_ADDRESS_SIZE_REG, Channel,
                CH0_SC1_CR_CPGC2_ADDRESS_SIZE_REG, SubChannel);
      Cpgc2AddrSize.Data = MrcReadCR (MrcData, Offset);
      // Row and Col bit sizes in BlockSize and RegionSize registers are exponential. Bank and Rank are linear "+1".
      Cpgc2AddrSize.Bits.Block_Size_Bits_Row  = RowSizeBits;
      Cpgc2AddrSize.Bits.Block_Size_Bits_Col  = ColSizeBits;
      Cpgc2AddrSize.Bits.Region_Size_Bits_Row = RowSizeBits;
      Cpgc2AddrSize.Bits.Region_Size_Bits_Col = ColSizeBits;
      Cpgc2AddrSize.Bits.Block_Size_Num_Banks = (BankCount) ? BankCount - 1 : 0;
      MrcWriteCR (MrcData, Offset, Cpgc2AddrSize.Data);

      // Update BASE_REPEATS to match the required number of Writes
      Burst = DimmOut->RowSize * Columns * BankCount;
      Cpgc20BaseRepeatsChSubch (MrcData, Channel, SubChannel, Burst, 1);

      if (Ddr4) {
        // Program Bank Logical to Physical mapping, to allow B2B traffic
        BankMapping = (BankCount == 16) ? Ddr4x8BankMapB2B : Ddr4x16BankMapB2B;
        MrcGetSetBankSequence (MrcData, Channel, BankMapping, BankCount, MRC_SET);
      }
    } // for SubChannel
  } // for Channel
}

/**
  This function sets up Address related registers for CMD stress to all enabled CPGC engines (per MrcIntData->ChSubChMaskEnable).

  @param[in]  MrcData           - Pointer to MRC global data.

  @retval Nothing.
**/
void
Cpgc20AddressSetupCmdStress (
  IN  MrcParameters *const  MrcData
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT32        Offset;
  BOOLEAN       Lpddr4;
  CH0_SC0_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT     AddressPrbsPoly;
  CH0_SC0_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT  BaseAddressControl;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  Lpddr4 = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4);

  AddressPrbsPoly.Data = 0;
  // Keep Address_PRBS_Rank_Poly = 0, we update ranks linearly and disable Rank PRBS
  // Keep Address_PRBS_Bank_Poly = 0, we update banks linearly and disable Bank PRBS
  // @todo How to handle asymmetric configs ? (Rank0 is x8 and Rank2 is x16 - different numer of banks)
  AddressPrbsPoly.Bits.Address_PRBS_Row_Poly    = CPGC_PRBS_14; // LP4 has 14/15/16 row bits, DDR4 has 14/15/16/17 row bits. @todo: Are we missing a stress for row bits 15/16/17 here ? Asymmetric configs are a problem..

  // Both LP4 and DDR4 have 10 column bits.
  // DDR4: BL = 2^3, 10-3=7
  // LP4:  BL = 2^4, 10-4=6
  AddressPrbsPoly.Bits.Address_PRBS_Column_Poly = Lpddr4 ? CPGC_PRBS_6 : CPGC_PRBS_7;

  BaseAddressControl.Data = 0;
  // Keep Addr_Prbs_Rnk_En = 0
  // Keep Addr_Prbs_Bnk_En = 0;
  BaseAddressControl.Bits.Addr_Prbs_Row_En = 1;
  BaseAddressControl.Bits.Addr_Prbs_Col_En = 1;
  BaseAddressControl.Bits.Addr_Prbs_Carry_Mode = 1;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ADDRESS_PRBS_POLY_REG,
                CH1_SC0_CR_CPGC2_ADDRESS_PRBS_POLY_REG, Channel,
                CH0_SC1_CR_CPGC2_ADDRESS_PRBS_POLY_REG, SubChannel);
      MrcWriteCR64 (MrcData, Offset, AddressPrbsPoly.Data);

      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG,
                CH1_SC0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG, Channel,
                CH0_SC1_CR_CPGC2_BASE_ADDRESS_CONTROL_REG, SubChannel);
      MrcWriteCR (MrcData, Offset, BaseAddressControl.Data);
    }
  }
}

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
  )
{
  MrcIntOutput  *MrcIntData;
  UINT8         Channel;
  UINT8         SubChannel;
  UINT8         ChanSubChanMask;
  UINT32        BaseRepeats;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  BaseRepeats = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      BaseRepeats = Cpgc20BaseRepeatsChSubch (MrcData, Channel, SubChannel, Burst, Ranks);
    }
  }
  return BaseRepeats;
}

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
  )
{
  UINT32  Offset;
  UINT32  BaseRepeats;
  CH0_SC0_CR_CPGC2_BASE_REPEATS_STRUCT  Cpgc2BaseRepeats;

  BaseRepeats = Burst * Ranks;
  BaseRepeats -= (BaseRepeats) ? 1 : 0;
  Cpgc2BaseRepeats.Data = 0;
  Cpgc2BaseRepeats.Bits.Base_Repeats = BaseRepeats;
//  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "Cpgc20BaseRepeatsChSubch: Ch%d Subch%d Burst = %d, Ranks = %d --> BaseRepeats = %d\n", Channel, SubChannel, Burst, Ranks, BaseRepeats);
  Offset = OFFSET_CALC_CH_SUBCH (
            CH0_SC0_CR_CPGC2_BASE_REPEATS_REG,
            CH1_SC0_CR_CPGC2_BASE_REPEATS_REG, Channel,
            CH0_SC1_CR_CPGC2_BASE_REPEATS_REG, SubChannel);
  MrcWriteCR (MrcData, Offset, Cpgc2BaseRepeats.Data);

  return BaseRepeats;
}

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
  )
{
  MrcOutput  *Outputs;
  UINT8      Channel;
  UINT8      Byte;
  UINT32     BlockRepeats;
  UINT32     BaseRepeats;

  Outputs = &MrcData->Outputs;

  BlockRepeats = Burst * Ranks;
  // Divide by 0 prevention
  BlockRepeats = MAX (BlockRepeats, 1);
  BlockRepeats = (LoopCount / BlockRepeats);
  BlockRepeats -= (BlockRepeats) ? 1 : 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    MrcSetLoopcount (MrcData, Channel, BlockRepeats);
    BaseRepeats = Cpgc20BaseRepeats (MrcData, Burst, Ranks);
    Cpgc20ConfigPgRotation (MrcData, MrcLog2 (BaseRepeats + 1));
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (MrcByteInChannelExist (MrcData, Channel, Byte)) {
        MrcSetupErrCounterCtl (MrcData, Channel, 0, Byte, ErrCounterCtlPerByte);
      }
    }
  }
}

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
  )
{
  UINT32  Burst;
  UINT32  Offset;
  UINT32  BaseRepeats;
  CH0_SC0_CR_CPGC2_BASE_REPEATS_STRUCT   CpgcBaseRepeats;

  Offset = OFFSET_CALC_CH_SUBCH (
            CH0_SC0_CR_CPGC2_BASE_REPEATS_REG,
            CH1_SC0_CR_CPGC2_BASE_REPEATS_REG, Channel,
            CH0_SC1_CR_CPGC2_BASE_REPEATS_REG, SubChannel);
  CpgcBaseRepeats.Data = MrcReadCR (MrcData, Offset);
  if (OrigRank == 0) {
    OrigRank = 1;  // Divide by 0 prevention
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "%s Cpgc20AdjustNumOfRanks: OrigRank is zero!", gErrString);
  }
  Burst = (CpgcBaseRepeats.Bits.Base_Repeats + 1) / OrigRank;

  BaseRepeats = Cpgc20BaseRepeatsChSubch (MrcData, Channel, SubChannel, Burst, NewRank);
  Cpgc20ConfigPgRotation (MrcData, MrcLog2 (BaseRepeats + 1));
}

