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
  @param[in]  CachelineMask - Bit Mask of cachelines to enable.
  @param[in]  ChunkMask     - Bit Mask of chunks to enable.

  @retval Nothing
**/
void
Cpgc20SetChunkClErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                CachelineMask,
  IN  UINT32                ChunkMask
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    Offset;
  UINT8     McChMask;
  UINT8     MaxChannel;
  BOOLEAN   Lpddr;
  MC0_CH0_CR_CPGC_ERR_CTL_STRUCT     Cpgc20ErrCtl;
  MC0_CH0_CR_CPGC_ERR_LNEN_HI_STRUCT Cpgc20ErrChunkMask;

  Outputs    = &MrcData->Outputs;
  Lpddr      = Outputs->Lpddr;
  McChMask   = Outputs->McChBitMask;
  MaxChannel = Outputs->MaxChannels;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = MrcGetTestErrCtlOffset (MrcData, Controller, Channel);
      Cpgc20ErrCtl.Data = MrcReadCR (MrcData, Offset);
      Cpgc20ErrCtl.Bits.ERRCHK_MASK_CACHELINE = CachelineMask;
      Cpgc20ErrCtl.Bits.ERRCHK_MASK_CHUNK = ChunkMask;
      MrcWriteCR (MrcData, Offset, Cpgc20ErrCtl.Data);

      if (Lpddr) {
        Offset = MrcGetCpgcErrCheckingHighOffset (MrcData, Controller, Channel);
        Cpgc20ErrChunkMask.Data = ChunkMask;
        MrcWriteCR (MrcData, Offset, Cpgc20ErrChunkMask.Data);
      }
    }
  }
}

/**
  This function programs the masks that enable error checking on the
  requested bytes.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  WordMask      - Which Word (Lower or Upper) to apply ErrMask to.
  @param[in]  ErrMask       - Error Masking Value to apply.

  @retval Nothing
**/
void
Cpgc20SetDataErrMsk (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                WordMask,
  IN  UINT32                ErrMask
  )
{
  MrcOutput *Outputs;
  UINT32    Channel;
  UINT32    Offset;
  UINT32    Controller;
  UINT32    Word;
  UINT32    MaxWords;
  UINT8     McChMask;
  UINT8     MaxChannel;
  BOOLEAN   Lpddr;

  Outputs    = &MrcData->Outputs;
  Lpddr      = Outputs->Lpddr;
  MaxWords   = Lpddr ? 1 : 2;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      for (Word = 0; Word < MaxWords; Word++) {
        if (((WordMask >> Word) & 1) != 1) {
          continue;
        }
        Offset = (Word == 0) ? MrcGetCpgcErrCheckingLowOffset (MrcData, Controller, Channel) : MrcGetCpgcErrCheckingHighOffset (MrcData, Controller, Channel);
        MrcWriteCR (MrcData, Offset, ErrMask);
      }
    }
  }
}

/**
  This function programs the masks that enable ecc error checking on the
  requested bytes.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  EccValue      - Error Masking Value to apply.

  @retval Nothing
**/
void
Cpgc20SetEccErrMsk (
  IN MrcParameters *const MrcData,
  IN UINT32               EccValue
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    Offset;
  UINT8     McChMask;
  UINT8     MaxChannel;
  MC0_CH0_CR_CPGC_ERR_XLNEN_STRUCT Cpgc20EccErrMskRankMask;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = MrcGetEccErrMskRankErrMskOffset (MrcData, Controller, Channel);
      Cpgc20EccErrMskRankMask.Data = MrcReadCR (MrcData, Offset);
      Cpgc20EccErrMskRankMask.Bits.ECC_ERRCHK_MASK = EccValue;
      MrcWriteCR (MrcData, Offset, Cpgc20EccErrMskRankMask.Data);
    }
  }
}

/**
  This function programs the error conditions to stop the CPGC engine on.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  StopType      - Stop type for CPGC engine.
  @param[in]  NumOfErr      - Number of Stop Type errors to wait on before stopping CPGC engine.

  @retval Nothing
**/
void
Cpgc20SetupTestErrCtl (
  IN  MrcParameters       *const  MrcData,
  IN  MRC_TEST_STOP_TYPE          StopType,
  IN  UINT32                      NumOfErr
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT8     McChMask;
  UINT8     MaxChannel;
  UINT32    Offset;
  MC0_CH0_CR_CPGC_ERR_CTL_STRUCT  Cpgc20ErrCtl;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = MrcGetTestErrCtlOffset (MrcData, Controller, Channel);
      Cpgc20ErrCtl.Data = MrcReadCR (MrcData, Offset);
      if (((UINT32) StopType == Cpgc20ErrCtl.Bits.STOP_ON_ERROR_CTL) && (NumOfErr == Cpgc20ErrCtl.Bits.STOP_ON_N)) {
        // Skipping the write as nothing changed
      } else {
        Cpgc20ErrCtl.Bits.STOP_ON_ERROR_CTL = StopType;
        Cpgc20ErrCtl.Bits.STOP_ON_N = NumOfErr;
        MrcWriteCR (MrcData, Offset, Cpgc20ErrCtl.Data);
      }
    }
  }
}

/**
  This function will Setup REUT Error Counters to count errors for specified type.

  @param[in]  MrcData         - Pointer to MRC global data.
  @param[in]  CounterPointer  - Specifies in register which counter to setup. Each Channel has 9 counters including ECC.
  @param[in]  ErrControlSel   - Specifies which type of error counter read will be executed.
  @param[in]  CounterSetting  - Specifies in register which Lane/Byte/Chunk to track in specified counter,
                                based on ErrControlSel value.
  @param[in]  CounterScope    - Specifies if the Pointer is used or not.
  @param[in]  CounterUI       - Specifies which UI will be considered when counting errors.
                                  00 - All UI; 01 - Even UI; 10 - Odd UI; 11 - Particular UI (COUNTER_CONTROL_SEL = ErrCounterCtlPerUI)

  @retval mrcWrongInputParameter if CounterSetting is incorrect for the ErrControlSel selected, otherwise mrcSuccess.
**/
MrcStatus
Cpgc20SetupErrCounterCtl (
  IN MrcParameters *const      MrcData,
  IN UINT8                     CounterPointer,
  IN MRC_ERR_COUNTER_CTL_TYPE  ErrControlSel,
  IN UINT32                    CounterSetting,
  IN UINT8                     CounterScope,
  IN UINT8                     CounterUI
  )
{
  MrcStatus                            Status;
  MrcOutput                            *Outputs;
  MrcDebug                             *Debug;
  UINT32                               Offset;
  UINT8                                Controller;
  UINT8                                Channel;
  UINT8                                McChMask;
  UINT8                                MaxChannel;
  MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_STRUCT Cpgc20ErrCounterCtl;

  Status     = mrcSuccess;
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      switch (ErrControlSel) {
        // Setup Error Counter Control for particular lane
        // @todo: This always uses counter 0 for that Channel to count the lane.  This does not allow counting multiple lanes at a time, and should be fixed if feature is needed.
        // @todo: Return Error as this mode isn't supported.
        case ErrCounterCtlPerLane:
          if ((CounterSetting > 72) || (CounterPointer > 8)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid lane. Counter: %u, Lane: %u\n", CounterPointer, CounterSetting);
            Status = mrcWrongInputParameter;
          }
          break;

        // Setup Error Counter Control for particular byte
        case ErrCounterCtlPerByte:
          if (((CounterSetting > 8) || (CounterPointer > 8)) && (MrcByteExist (MrcData, Controller, Channel, CounterPointer))) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid byte. Counter: %u, Byte: %u\n", CounterPointer, CounterSetting);
            Status = mrcWrongInputParameter;
          }
          break;

        // Setup Error Counter Control for particular nibble - used in Server, probably not used in Client
/**
        case ErrCounterCtlPerNibble:
          if ((CounterSetting > 4) || (CounterPointer > 8)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid nibble. Counter: %u, Nibble: %u\n", CounterPointer, CounterSetting);
            Status = mrcWrongInputParameter;
          }
          break;
**/
        // Setup Error Counter Control for particular UI
        case ErrCounterCtlPerUI:
          if (CounterPointer > 8) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to setup an error counter for invalid chunk. Counter: %u\n", CounterPointer);
            Status = mrcWrongInputParameter;
          }
          // Setup Error Counter Control for All Lanes
          break;
        case ErrCounterCtlAllLanes:
          // In ErrCounterCtlAllLanes, COUNTER_CONTROL_SCOPE = 0. In this case, COUNTER_POINTER is unused and COUNTER_CONTROL_SEL is don't care.
          break;
        default:
          Status = mrcWrongInputParameter;
          break;
      }
      if (Status == mrcSuccess) {
        Offset = (OFFSET_CALC_MC_CH (MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG, MC1_CH0_CR_CPGC_ERR_CNTRCTL_0_REG, Controller, MC0_CH1_CR_CPGC_ERR_CNTRCTL_0_REG, Channel)) +
               ((MC0_CH0_CR_CPGC_ERR_CNTRCTL_1_REG - MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG) * CounterPointer);
        Cpgc20ErrCounterCtl.Data = 0;
        Cpgc20ErrCounterCtl.Bits.COUNTER_POINTER       = CounterPointer;
        Cpgc20ErrCounterCtl.Bits.COUNTER_CONTROL_SEL   = ErrControlSel;
        Cpgc20ErrCounterCtl.Bits.COUNTER_CONTROL_SCOPE = CounterScope;
        Cpgc20ErrCounterCtl.Bits.COUNTER_CONTROL_UI    = CounterUI;
        MrcWriteCR (MrcData, Offset, Cpgc20ErrCounterCtl.Data);
      }
    }
  }
  return Status;
}

/**
  This function returns the Error status results for specified MRC_ERR_STATUS_TYPE.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Controller  - Desired Memory Controller.
  @param[in]  Channel     - Desired Channel.
  @param[in]  Param       - Specifies which type of error status read will be executed.
  @param[out] Buffer      - Pointer to buffer which register values will be read into.
                              Error status bits will be returned starting with bit zero.

  @retval Returns mrcWrongInputParameter if Param value is not supported by this function, otherwise mrcSuccess.
**/
MrcStatus
Cpgc20GetErrEccChunkRankByteStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Controller,
  IN  UINT32                  Channel,
  IN  MRC_ERR_STATUS_TYPE     Param,
  OUT UINT64          *const  Buffer
  )
{
  const MrcInput                                *Inputs;
  MrcOutput                                     *Outputs;
  UINT64                                        Value;
  UINT32                                        Offset;
  UINT32                                        CRValue;
  UINT8                                         McChMask;
  UINT8                                         MaxChannel;
  BOOLEAN                                       EccSupport;
  MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT  CpgcErrByteNthStatus;
  MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT CpgcErrEccChunkRank;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  EccSupport = Outputs->EccSupport;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  Value = 0;
  if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
    return mrcWrongInputParameter;
  }
  if ((Param == ByteGroupErrStatus) || (Param == WdbRdChunkNumStatus) || (Param == NthErrStatus)) {
    Offset = OFFSET_CALC_MC_CH (
              MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG,
              MC1_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG, Controller,
              MC0_CH1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG, Channel);
  } else if ((Param == RankErrStatus) || (Param == ChunkErrStatus)) {
    Offset = OFFSET_CALC_MC_CH (
              MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG,
              MC1_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Controller,
              MC0_CH1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Channel);
  } else {
    Offset = 0;
  }

  CRValue = MrcReadCR (MrcData, Offset);
  CpgcErrByteNthStatus.Data = CRValue;
  CpgcErrEccChunkRank.Data = CRValue;

  switch (Param) {
    case ByteGroupErrStatus:
      Value = CpgcErrByteNthStatus.Bits.BYTEGRP_ERR_STAT;
      if (EccSupport) {
        Value |= (UINT64) (CpgcErrByteNthStatus.Bits.ECCGRP_ERR_STAT << MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_OFF);
      }
      break;

    case RankErrStatus:
      if (Inputs->UlxUlt) {
        Value = CpgcErrEccChunkRank.Bits.RANK_ERR_STAT;
      } else {
        Value = CpgcErrEccChunkRank.P0Bits.RANK_ERR_STAT;
      }
      break;

    case WdbRdChunkNumStatus:
      Value = CpgcErrByteNthStatus.Bits.RD_CHUNK_NUM_STAT;
      break;

    case NthErrStatus:
      Value = CpgcErrByteNthStatus.Bits.Nth_ERROR;
      break;

    case ChunkErrStatus:
      Value = CpgcErrEccChunkRank.Bits.CHUNK_ERR_STAT;
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

  MRC_DEBUG_ASSERT (Buffer != NULL, &Outputs->Debug, "%s Null Pointer", gErrString);
  *Buffer = Value;
  return mrcSuccess;
}

/**
  This function accesses the Sequence loop count (per McChBitMask).

  @param[in]  MrcData    - Pointer to MRC global data.
  @param[in]  LoopCount  - Pointer to variable to store or set.

  @retval Nothing.
**/
void
Cpgc20SetLoopCount (
  IN      MrcParameters *const  MrcData,
  IN OUT  UINT32  *const        LoopCount
  )
{
  MrcOutput     *Outputs;
  UINT8         Controller;
  UINT8         Channel;
  UINT8         IpChannel;
  UINT8         McChMask;
  UINT8         MaxChannel;
  UINT32        Offset;
  BOOLEAN       Lpddr;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_REG,
                MC1_REQ0_CR_CPGC2_BLOCK_REPEATS_REG, Controller,
                MC0_REQ1_CR_CPGC2_BLOCK_REPEATS_REG, IpChannel);
      // MRC_DEBUG_MSG (Outputs->Debug, MSG_LEVEL_ERROR, "Cpgc20SetLoopCount: mc%d ch%d LoopCount = %d\n", Controller, Channel, *LoopCount);
      MrcWriteCR (MrcData, Offset, *LoopCount);
    }
  }
}

/**
  This function accesses the Logical to Physical Bank Mapping.

  @param[in]  MrcData    - Pointer to MRC global data.
  @param[in]  Controller - Desired Controller
  @param[in]  Channel    - Desired Channel
  @param[in]  Banks      - Pointer to buffer to logical-to-physical bank mapping.
  @param[in]  Count      - Length of the Banks buffer.
  @param[in]  IsGet      - TRUE: Get.  FALSE: Set.

  @retval Nothing.
**/
void
Cpgc20GetSetBankMap (
  IN      MrcParameters *const  MrcData,
  IN      UINT32                Controller,
  IN      UINT32                Channel,
  IN OUT  UINT8 *const          Banks,
  IN      UINT32                Count,
  IN      BOOLEAN               IsGet
  )
{
  MrcOutput     *Outputs;
  UINT8         McChMask;
  UINT8         MaxChannel;
  UINT32        IpChannel;
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
  BOOLEAN       Lpddr;

  RegData     = 0;
  BanksPerReg = 6;
  Outputs     = &MrcData->Outputs;
  MaxChannel  = Outputs->MaxChannels;
  McChMask    = Outputs->McChBitMask;
  Lpddr       = Outputs->Lpddr;

  if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
    return;
  }
  IpChannel = LP_IP_CH (Lpddr, Channel);
  Offset = OFFSET_CALC_MC_CH (
            MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG,
            MC1_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG, Controller,
            MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG, IpChannel);
  CrIncrement = MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_REG - MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG;
  FieldOffsetStep = MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_OFF;
  FieldMask = MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_MSK;

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
  @param[in]  Controller  - Desired Memory Controller.
  @param[in]  Channel     - Desired Channel.
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
Cpgc20GetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Controller,
  IN  UINT32                  Channel,
  OUT UINT8                   *Status
  )
{
  MrcOutput     *Outputs;
  UINT32        ErrDataStatus03;
  UINT32        Offset1;
  UINT32        Offset2;
  UINT32        ErrDataStatus47;
  UINT8         Byte;
  UINT8         McChMask;
  UINT8         MaxChannel;
  MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT CpgcErrEccChunkRank;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) != 0) {
    Offset1 = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_ERR_STAT03_REG,
                MC1_CH0_CR_CPGC_ERR_STAT03_REG, Controller,
                MC0_CH1_CR_CPGC_ERR_STAT03_REG, Channel);
    Offset2 = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_ERR_STAT47_REG,
                MC1_CH0_CR_CPGC_ERR_STAT47_REG, Controller,
                MC0_CH1_CR_CPGC_ERR_STAT47_REG, Channel);

    MRC_DEBUG_ASSERT (Status != NULL, &Outputs->Debug, "%s Null Pointer", gErrString);

    ErrDataStatus03 = MrcReadCR (MrcData, Offset1);
    ErrDataStatus47 = MrcReadCR (MrcData, Offset2);
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (Byte < 4) {
        Status[Byte] = (ErrDataStatus03 >> (8 * Byte)) & 0xFF;
      } else {
        Status[Byte] = (ErrDataStatus47 >> (8 * (Byte - 4))) & 0xFF;
      }
    }
    if (Outputs->EccSupport) {
      Offset1 = OFFSET_CALC_MC_CH (
                  MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG,
                  MC1_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Controller,
                  MC0_CH1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG, Channel);
      CpgcErrEccChunkRank.Data = MrcReadCR (MrcData, Offset1);
      Status[8] = (UINT8) CpgcErrEccChunkRank.Bits.ECC_LANE_ERR_STAT;
    }
  }
}
/**
  This function returns the Error Counter status for specified counter.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  Controller    - Desired Memory Controller.
  @param[in]  Channel       - Desired Channel.
  @param[in]  CounterSelect - Desired error counter to read from.
  @param[out] CounterStatus - Pointer to buffer where counter status will be held.
  @param[out] Overflow      - Indicates if counter has reached overflow.

  @retval Nothing.
**/
void
Cpgc20GetErrCounterStatus (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Controller,
  IN  UINT32                Channel,
  IN  UINT32                CounterSelect,
  OUT UINT32        *const  CounterStatus,
  OUT BOOLEAN       *const  Overflow
  )
{
  MrcOutput  *Outputs;
  UINT32     Offset;
  UINT32     Value;

  Outputs    = &MrcData->Outputs;

  Offset = OFFSET_CALC_MC_CH (
            MC0_CH0_CR_CPGC_ERR_CNTR_0_REG,
            MC1_CH0_CR_CPGC_ERR_CNTR_0_REG, Controller,
            MC0_CH1_CR_CPGC_ERR_CNTR_0_REG, Channel);
  Offset += (MC0_CH0_CR_CPGC_ERR_CNTR_1_REG - MC0_CH0_CR_CPGC_ERR_CNTR_0_REG) * CounterSelect;
  Value = MrcReadCR (MrcData, Offset);

  MRC_DEBUG_ASSERT ((CounterStatus != NULL) && (Overflow != NULL), &Outputs->Debug, "%s Null Pointer", gErrString);

  *CounterStatus = Value;

  Offset = OFFSET_CALC_MC_CH (
            MC0_CH0_CR_CPGC_ERR_CNTR_OV_REG,
            MC1_CH0_CR_CPGC_ERR_CNTR_OV_REG, Controller,
            MC0_CH1_CR_CPGC_ERR_CNTR_OV_REG, Channel);
  Value = MrcReadCR (MrcData, Offset);

  *Overflow = ((Value >> (CounterSelect % 9)) & 1) == 1;
}

/**
  This function writes to all enabled CPGC SEQ CTL registers.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  McChBitMask   - Memory Controller Channel Bit mask for which registers should be programmed for.
  @param[in]  CpgcSeqCtl    - Data to be written to all CPGC SEQ CTL registers.

  @retval Nothing.
**/
void
Cpgc20ControlRegWrite (
  IN  MrcParameters *const              MrcData,
  IN  UINT8                             McChBitMask,
  IN  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT   CpgcSeqCtl
  )
{
  MrcOutput     *Outputs;
  UINT8         Controller;
  UINT8         Channel;
  UINT8         IpChannel;
  UINT8         MaxChannel;
  UINT32        Offset;
  BOOLEAN       Lpddr;
  MC0_REQ0_CR_CPGC_SEQ_STATUS_STRUCT  CpgcStatus;
  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      if (CpgcSeqCtl.Bits.START_TEST == 1) {
        Offset = OFFSET_CALC_MC_CH (
          MC0_REQ0_CR_CPGC_SEQ_STATUS_REG,
          MC1_REQ0_CR_CPGC_SEQ_STATUS_REG, Controller,
          MC0_REQ1_CR_CPGC_SEQ_STATUS_REG, IpChannel);
        CpgcStatus.Data = MrcReadCR (MrcData, Offset);
        if (CpgcStatus.Bits.TEST_DONE == 1) {
          // Clear by writing a '1'
          MrcWriteCR (MrcData, Offset, CpgcStatus.Data);
        }
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC_SEQ_CTL_REG,
                MC1_REQ0_CR_CPGC_SEQ_CTL_REG, Controller,
                MC0_REQ1_CR_CPGC_SEQ_CTL_REG, IpChannel);

      MrcWriteCR (MrcData, Offset, CpgcSeqCtl.Data);
    }
  }
}

/**
  This function aggregates the status of STOP_TEST bit for all enabled CPGC engines.

  @param[in]  MrcData       - Pointer to MRC global data.

  @retval UINT8 of the aggregated value of STOP_TEST.
**/
UINT8
Cpgc20ControlRegStopBitStatus (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput                       *Outputs;
  UINT8                           Controller;
  UINT8                           Channel;
  UINT8                           IpChannel;
  UINT8                           StopBit;
  UINT8                           McChMask;
  UINT8                           MaxChannel;
  UINT32                          Offset;
  BOOLEAN                         Lpddr;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT CpgcSeqCtl;

  Outputs    = &MrcData->Outputs;
  StopBit    = 0;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC_SEQ_CTL_REG,
                MC1_REQ0_CR_CPGC_SEQ_CTL_REG, Controller,
                MC0_REQ1_CR_CPGC_SEQ_CTL_REG, IpChannel);
      CpgcSeqCtl.Data = MrcReadCR (MrcData, Offset);
      StopBit |= CpgcSeqCtl.Bits.STOP_TEST;
    }
  }
  return StopBit;
}

/**
  This function writes to all enabled CADB CTL registers.

  @param[in]  MrcData      - Pointer to MRC global data.
  @param[in]  McChBitMask  - Memory Controller Channel Bit mask for which registers should be programmed for.
  @param[in]  CadbControl  - Data to be written to all CADB CTL registers.

  @retval Nothing.
**/
void
Cadb20ControlRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  UINT8                                McChBitMask,
  IN  MC0_CH0_CR_CADB_CTL_STRUCT           CadbControl
  )
{
  MrcOutput     *Outputs;
  UINT8         Channel;
  UINT8         Controller;
  UINT32        Offset;
  UINT8         MaxChannel;
  MC0_CH0_CR_CADB_STATUS_STRUCT   CadbStatus;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      if (CadbControl.Bits.START_TEST) {
        // Make sure that the previous test was finished
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_CADB_STATUS_REG, MC1_CH0_CR_CADB_STATUS_REG, Controller, MC0_CH1_CR_CADB_STATUS_REG, Channel);
        CadbStatus.Data = MrcReadCR (MrcData, Offset);
        if (CadbStatus.Bits.TEST_DONE == 1) {
          // Clear by writing a '1'
          MrcWriteCR (MrcData, Offset, CadbStatus.Data);
          CadbStatus.Data = MrcReadCR (MrcData, Offset);
        }
      }
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_CADB_CTL_REG, MC1_CH0_CR_CADB_CTL_REG, Controller, MC0_CH1_CR_CADB_CTL_REG, Channel);
      MrcWriteCR (MrcData, Offset, CadbControl.Data);
    }
  }
}

/**
  This function writes to all enabled CADB CFG registers.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CadbConfig    - Data to be written to all CADB CFG registers.

  @retval Nothing.
**/
void
Cadb20ConfigRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  MC0_CH0_CR_CADB_CFG_STRUCT           CadbConfig
  )
{
  MrcOutput     *Outputs;
  UINT8         Controller;
  UINT8         Channel;
  UINT32        Offset;
  UINT8         McChMask;
  UINT8         MaxChannel;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CADB_CFG_REG,
                MC1_CH0_CR_CADB_CFG_REG, Controller,
                MC0_CH1_CR_CADB_CFG_REG, Channel);
      MrcWriteCR (MrcData, Offset, CadbConfig.Data);
    }
  }
}

/**
  This function writes to all enabled CADB_AO_MRSCFG registers.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  CadbMrsConfig - Data to be written to all CADB_AO_MRSCFG registers.

  @retval Nothing.
**/
void
Cadb20MrsConfigRegWrite (
  IN  MrcParameters *const                 MrcData,
  IN  MC0_CH0_CR_CADB_AO_MRSCFG_STRUCT     CadbMrsConfig
  )
{
  MrcOutput     *Outputs;
  UINT32        Controller;
  UINT32        Channel;
  UINT32        Offset;
  UINT8         McChMask;
  UINT8         MaxChannel;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
        MC0_CH0_CR_CADB_AO_MRSCFG_REG,
        MC1_CH0_CR_CADB_AO_MRSCFG_REG, Controller,
        MC0_CH1_CR_CADB_AO_MRSCFG_REG, Channel);
      MrcWriteCR (MrcData, Offset, CadbMrsConfig.Data);
    }
  }
}

/**
  This function checks the value of CADB_STATUS.TEST_DONE bit for all enabled CADB engines.

  @param[in]  MrcData       - Pointer to MRC global data.

  @retval 1 - if all enabled engines are done, otherwise 0
**/
UINT32
Cadb20TestDoneStatus (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput                       *Outputs;
  UINT8                           Controller;
  UINT8                           Channel;
  UINT8                           McChMask;
  UINT8                           MaxChannel;
  UINT32                          TestDone;
  UINT32                          Offset;
  MC0_CH0_CR_CADB_STATUS_STRUCT   CadbStatus;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  TestDone   = 1; // Assume all done

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_CADB_STATUS_REG, MC1_CH0_CR_CADB_STATUS_REG, Controller, MC0_CH1_CR_CADB_STATUS_REG, Channel);
      CadbStatus.Data = MrcReadCR (MrcData, Offset);
      TestDone &= CadbStatus.Bits.TEST_DONE;
    }
  }
  return TestDone;
}

/**
  This function writes Command Instructions to all enabled CPGC engines.

  @param[in]  MrcData        - Pointer to MRC global data.
  @param[in]  CmdInstruct    - Array of Command Instructions
  @param[in]  NumInstruct    - Number of Instructions

  @retval MrcStatus - mrcSuccess if does not exceed command instruction registers otherwise mrcFail
**/
MrcStatus
Cpgc20CmdInstructWrite (
  IN  MrcParameters *const                            MrcData,
  IN  MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT  *CmdInstruct,
  IN  UINT8                                           NumInstruct
  )
{
  MrcOutput         *Outputs;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             IpChannel;
  UINT8             Index;
  UINT8             McChMask;
  UINT8             MaxChannel;
  UINT32            Offset;
  BOOLEAN           Lpddr;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  if (NumInstruct > CPGC20_MAX_COMMAND_INSTRUCTION) {
    return mrcFail;
  }
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG,
                MC1_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG, Controller,
                MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_0_REG, IpChannel);
      for (Index = 0; Index < NumInstruct; Index++) {
        MrcWriteCR8 (MrcData, Offset, CmdInstruct[Index].Data);
        Offset += MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_1_REG - MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG;
      }
    }
  }
  return mrcSuccess;
}

/**
  This function writes Algorithm Instructions to all enabled CPGC engines (per Outputs->McChBitMask).

  @param[in]  MrcData               - Pointer to MRC global data.
  @param[in]  AlgoInstruct          - Array of Algorithm Instructions
  @param[in]  AlgoInstructControl   - Algorithm Instruction Control setting to program based on ValidMask
  @param[in]  AlgoWaitEventControl  - Algorithm Wait Event Control setting to program
  @param[in]  ValidMask             - Bit Mask of which Instructions are valid

  @retval Nothing.
**/
void
Cpgc20AlgoInstructWrite (
  IN  MrcParameters *const                                   MrcData,
  IN  MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT       *AlgoInstruct,
  IN  MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT  AlgoInstructControl,
  IN  MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT  AlgoWaitEventControl,
  IN  UINT8                                                  ValidMask
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  UINT32        Controller;
  UINT32        Channel;
  UINT32        IpChannel;
  UINT32        Offset;
  UINT32        CtrlOffset;
  UINT32        Index;
  UINT8         McChMask;
  UINT8         MaxChannel;
  BOOLEAN       Lpddr;
  MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_STRUCT WaitToStartCfg;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                    MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG,
                    MC1_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG, Controller,
                    MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG, IpChannel);
      CtrlOffset = OFFSET_CALC_MC_CH (
                    MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG,
                    MC1_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG, Controller,
                    MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG, IpChannel);
      for (Index = 0; Index < CPGC20_MAX_ALGORITHM_INSTRUCTION; Index++) {
        if (ValidMask & (MRC_BIT0 << Index)) {
          MrcWriteCR8 (MrcData, Offset, AlgoInstruct[Index].Data);
          MrcWriteCR8 (MrcData, CtrlOffset, AlgoInstructControl.Data);
          Offset += MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_1_REG - MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG;
          CtrlOffset += MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_REG - MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG;
        } else {
          break;
        }
      }
      CtrlOffset = OFFSET_CALC_MC_CH (
                    MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG,
                    MC1_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG, Controller,
                    MC0_REQ1_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG, IpChannel);
      MrcWriteCR (MrcData, CtrlOffset, AlgoWaitEventControl.Data);

      if (AlgoWaitEventControl.Bits.Wait_Clock_Frequency == CPGC20_NATIVE_DUNIT_FREQ) {
        Offset = OFFSET_CALC_MC_CH (
                  MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_REG,
                  MC1_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_REG, Controller,
                  MC0_REQ1_CR_CPGC2_BASE_CLOCK_CONFIG_REG, IpChannel);
        WaitToStartCfg.Data = MrcReadCR (MrcData, Offset);
        if (Inputs->A0) {
          WaitToStartCfg.A0Bits.Clock_Freq = 1;
        } else {
          WaitToStartCfg.Bits.Clock_Freq = 1;
        }
        MrcWriteCR (MrcData, Offset, WaitToStartCfg.Data);
      }
    }
  }
}

/**
  This function writes Algorithm Instructions to all enabled CPGC engines.

  @param[in]  MrcData        - Pointer to MRC global data.
  @param[in]  DataInstruct   - Array of Data Instructions
  @param[in]  ValidMask      - Bit Mask of which Instructions are valid

  @retval Nothing.
**/
void
Cpgc20DataInstructWrite (
  IN  MrcParameters *const                        MrcData,
  IN  MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT *DataInstruct,
  IN  UINT8                                       ValidMask
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    IpChannel;
  UINT32    Index;
  UINT32    Offset;
  UINT8     McChMask;
  UINT8     MaxChannel;
  BOOLEAN   Lpddr;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG,
                MC1_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG, Controller,
                MC0_REQ1_CR_CPGC2_DATA_INSTRUCTION_0_REG, IpChannel);
      for (Index = 0; Index < CPGC20_MAX_DATA_INSTRUCTION; Index++) {
        if (ValidMask & (MRC_BIT0 << Index)) {
          MrcWriteCR8 (MrcData, Offset, DataInstruct[Index].Data);
          Offset += MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_1_REG - MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG;
        } else {
          break;
        }
      }
    }
  }
}

/**
  This function sets up Address related registers (ADDRESS_INSTRUCTION, REGION_LOW_ROW, REGION_LOW_COL, ADDRESS_SIZE) to all enabled CPGC engines.

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
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    IpChannel;
  UINT32    Index;
  UINT32    Offset;
  UINT8     McChMask;
  UINT8     MaxChannel;
  BOOLEAN   Lpddr;
  MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT  Cpgc2AddrInstruct;
  MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_STRUCT           Cpgc2AddrSize;
  MC0_REQ0_CR_CPGC2_REGION_LOW_STRUCT             Cpgc2Low;
//  MrcDebug      *Debug;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;
//  Debug = &Outputs->Debug;

//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AddressOrder: %u, AddressDirection: %u, LastValidInstruct: %u\n", AddressOrder, AddressDirection, LastValidInstruct);
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RowStart: %u, RowSizeBits: 0x%x\n", RowStart, RowSizeBits);
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ColStart: %u, ColSizeBits: 0x%x\n", ColStart, ColSizeBits);
  Cpgc2AddrInstruct.Data = 0;
  Cpgc2AddrInstruct.Bits.Address_Order = AddressOrder;
  Cpgc2AddrInstruct.Bits.Address_Direction = AddressDirection;

  Cpgc2Low.Data = 0;
  Cpgc2Low.Bits.Low_Row = RowStart;
  Cpgc2Low.Bits.Low_Col = ColStart;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG,
                MC1_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG, Controller,
                MC0_REQ1_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG, IpChannel);
      for (Index = 0; Index < CPGC20_MAX_ADDRESS_INSTRUCTION; Index++) {
        Cpgc2AddrInstruct.Bits.Last = (LastValidInstruct == Index) ? 1 : 0;
        MrcWriteCR8 (MrcData, Offset, Cpgc2AddrInstruct.Data);
        Offset += MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_1_REG - MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG;
        if (LastValidInstruct == Index) {
          break;
        }
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_REGION_LOW_REG,
                MC1_REQ0_CR_CPGC2_REGION_LOW_REG, Controller,
                MC0_REQ1_CR_CPGC2_REGION_LOW_REG, IpChannel);
      MrcWriteCR64 (MrcData, Offset, Cpgc2Low.Data);

      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REG,
                MC1_REQ0_CR_CPGC2_ADDRESS_SIZE_REG, Controller,
                MC0_REQ1_CR_CPGC2_ADDRESS_SIZE_REG, IpChannel);
      Cpgc2AddrSize.Data = MrcReadCR64 (MrcData, Offset);
      // Row and Col bit sizes in BlockSize and RegionSize registers are exponential. Bank and Rank are linear "+1".
      Cpgc2AddrSize.Bits.Block_Size_Bits_Row  = EnCADB ? 0 : RowSizeBits; // In command stress we want Row to be updated together with Bank, so block size is zero
      Cpgc2AddrSize.Bits.Block_Size_Bits_Col  = EnCADB ? 2 : ColSizeBits; // In command stress we want Bank / Row update every 4 CLs
      Cpgc2AddrSize.Bits.Region_Size_Bits_Row = RowSizeBits;
      Cpgc2AddrSize.Bits.Region_Size_Bits_Col = ColSizeBits;
      Cpgc2AddrSize.Bits.Block_Size_Max_Bank = (BankSize) ? BankSize - 1 : 0;
      Cpgc2AddrSize.Bits.Region_Size_Max_Bank = Cpgc2AddrSize.Bits.Block_Size_Max_Bank;
      MrcWriteCR64 (MrcData, Offset, Cpgc2AddrSize.Data);
    }
  }
}

/**
  This function sets up Address related registers for CMD stress to all enabled CPGC engines.

  @param[in]  MrcData           - Pointer to MRC global data.

  @retval Nothing.
**/
void
Cpgc20AddressSetupCmdStress (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput     *Outputs;
  UINT8         Controller;
  UINT8         Channel;
  UINT8         IpChannel;
  UINT8         McChMask;
  UINT8         MaxChannel;
  UINT32        Offset;
  BOOLEAN       Lpddr;
  MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT     AddressPrbsPoly;
  MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT  BaseAddressControl;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr      = Outputs->Lpddr;

  AddressPrbsPoly.Data = 0;
  // Keep Address_PRBS_Rank_Poly = 0, we update ranks linearly and disable Rank PRBS
  // Keep Address_PRBS_Bank_Poly = 0, we update banks linearly and disable Bank PRBS
  // @todo How to handle asymmetric configs ? (Rank0 is x8 and Rank2 is x16 - different numer of banks)
  AddressPrbsPoly.Bits.Address_PRBS_Row_Poly    = CPGC_PRBS_14; // LP4 has 14/15/16 row bits, DDR4 has 14/15/16/17 row bits. @todo: Are we missing a stress for row bits 15/16/17 here ? Asymmetric configs are a problem..

  // Both LP4 and DDR4 have 10 column bits.
  // DDR4: BL = 2^3, 10-3=7
  // LP4:  BL = 2^5, 10-5=5
  AddressPrbsPoly.Bits.Address_PRBS_Column_Poly = Lpddr ? CPGC_PRBS_5 : CPGC_PRBS_7;

  BaseAddressControl.Data = 0;
  // Keep Addr_Prbs_Rnk_En = 0
  // Keep Addr_Prbs_Bnk_En = 0;
  BaseAddressControl.Bits.Addr_Prbs_Row_En = 1;
  BaseAddressControl.Bits.Addr_Prbs_Col_En = 1;
  BaseAddressControl.Bits.Addr_Prbs_Carry_Mode = 1;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_REG,
                MC1_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_REG, Controller,
                MC0_REQ1_CR_CPGC2_ADDRESS_PRBS_POLY_REG, IpChannel);
      MrcWriteCR64 (MrcData, Offset, AddressPrbsPoly.Data);

      Offset = OFFSET_CALC_MC_CH (
                MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG,
                MC1_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG, Controller,
                MC0_REQ1_CR_CPGC2_BASE_ADDRESS_CONTROL_REG, IpChannel);
      MrcWriteCR (MrcData, Offset, BaseAddressControl.Data);
    }
  }
}

/**
  This function sets up Base Repeats to all enabled CPGC engines.

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
  MrcOutput     *Outputs;
  UINT8         Controller;
  UINT8         Channel;
  UINT8         IpChannel;
  UINT8         McChMask;
  UINT8         MaxChannel;
  UINT32        BaseRepeats;
  BOOLEAN       Lpddr;

  Outputs     = &MrcData->Outputs;
  MaxChannel  = Outputs->MaxChannels;
  McChMask    = Outputs->McChBitMask;
  BaseRepeats = 0;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      BaseRepeats = Cpgc20BaseRepeatsMcCh (MrcData, Controller, IpChannel, Burst, Ranks);
    }
  }
  return BaseRepeats;
}

/**
  This function sets up Base Repeats for a given CPGC engine (per Controller / Channel).
  The function doesn't check for mc/ch presence. Lp Channel taken care of outside of the function in both use cases.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  Controller  - Controller to work on
  @param[in]  Channel     - Channel to work on
  @param[in]  Burst       - Number of Cachelines (Should be power of 2)
  @param[in]  Ranks       - # of Ranks to test

  @retval Value written to CPGC2_BASE_REPEATS.
**/
UINT32
Cpgc20BaseRepeatsMcCh (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Controller,
  IN  UINT32                Channel,
  IN  UINT32                Burst,
  IN  UINT32                Ranks
  )
{
  UINT32    Offset;
  UINT32    BaseRepeats;
  MC0_REQ0_CR_CPGC2_BASE_REPEATS_STRUCT  Cpgc2BaseRepeats;

  BaseRepeats = Burst * Ranks;
  BaseRepeats -= (BaseRepeats) ? 1 : 0;
  Cpgc2BaseRepeats.Data = 0;
  Cpgc2BaseRepeats.Bits.Base_Repeats = BaseRepeats;
//  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "Cpgc20BaseRepeatsMcCh: Mc%d Ch%d Burst = %d, Ranks = %d --> BaseRepeats = %d\n", Controller, Channel, Burst, Ranks, BaseRepeats);
  Offset = OFFSET_CALC_MC_CH (
            MC0_REQ0_CR_CPGC2_BASE_REPEATS_REG,
            MC1_REQ0_CR_CPGC2_BASE_REPEATS_REG, Controller,
            MC0_REQ1_CR_CPGC2_BASE_REPEATS_REG, Channel);
  MrcWriteCR (MrcData, Offset, Cpgc2BaseRepeats.Data);

  return BaseRepeats;
}

/**
  This function sets up Registers for Basic Mem Test to all enabled CPGC engines.

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
  UINT8      Byte;
  UINT32     BlockRepeats;
  UINT32     BaseRepeats;

  Outputs = &MrcData->Outputs;

  BlockRepeats = Burst * Ranks;
  // Divide by 0 prevention
  BlockRepeats = MAX (BlockRepeats, 1);
  BlockRepeats = (LoopCount / BlockRepeats);
  BlockRepeats -= (BlockRepeats) ? 1 : 0;

  MrcSetLoopcount (MrcData, BlockRepeats);
  BaseRepeats = Cpgc20BaseRepeats (MrcData, Burst, Ranks);
  Cpgc20ConfigPgRotation (MrcData, MrcLog2(BaseRepeats + 1));
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    MrcSetupErrCounterCtl (MrcData, Byte, ErrCounterCtlPerByte, 0); //Counts errors per Byte Group, 1 count per UI with an error across all lanes in the Byte Group, all UI
  } // for Byte
}

/**
  This function adjusts register settings that are based on # of ranks being tested for the Controller/Channel provided.

  @param[in]  MrcData           - Pointer to MRC global data.
  @param[in]  Controller        - Controller to work on
  @param[in]  Channel           - Channel to work on
  @param[in]  OrigRank          - Original # of Ranks
  @param[in]  NewRank           - New # of Ranks

  @retval Nothing.
**/
void
Cpgc20AdjustNumOfRanks (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Controller,
  IN  UINT32                Channel,
  IN  UINT8                 OrigRank,
  IN  UINT8                 NewRank
  )
{
  MrcOutput                              *Outputs;
  UINT8                                  McChMask;
  UINT8                                  MaxChannel;
  UINT32                                 IpChannel;
  UINT32                                 Burst;
  UINT32                                 Offset;
  UINT32                                 BaseRepeats;
  BOOLEAN                                Lpddr;
  MC0_REQ0_CR_CPGC2_BASE_REPEATS_STRUCT  CpgcBaseRepeats;

  Outputs    = &MrcData->Outputs;
  MaxChannel = Outputs->MaxChannels;
  McChMask   = Outputs->McChBitMask;
  Lpddr = Outputs->Lpddr;
  if ((MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) || (IS_MC_SUB_CH (Lpddr, Channel))) {
    return;
  }
  IpChannel = LP_IP_CH (Lpddr, Channel);

  Offset = OFFSET_CALC_MC_CH (
            MC0_REQ0_CR_CPGC2_BASE_REPEATS_REG,
            MC1_REQ0_CR_CPGC2_BASE_REPEATS_REG, Controller,
            MC0_REQ1_CR_CPGC2_BASE_REPEATS_REG, IpChannel);
  CpgcBaseRepeats.Data = MrcReadCR (MrcData, Offset);
  if (OrigRank == 0) {
    OrigRank = 1;  // Divide by 0 prevention
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "%s Cpgc20AdjustNumOfRanks: OrigRank is zero!", gErrString);
  }
  Burst = (CpgcBaseRepeats.Bits.Base_Repeats + 1) / OrigRank;
  BaseRepeats = Cpgc20BaseRepeatsMcCh (MrcData, Controller, IpChannel, Burst, NewRank);
  Cpgc20ConfigPgRotation (MrcData, MrcLog2 (BaseRepeats + 1));
}
