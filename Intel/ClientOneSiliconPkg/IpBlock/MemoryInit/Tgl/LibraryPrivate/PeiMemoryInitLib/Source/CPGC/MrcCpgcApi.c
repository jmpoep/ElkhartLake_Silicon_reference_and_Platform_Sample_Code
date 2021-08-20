/** @file
  This file implements an interface between the MRC and the different
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
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cadb20ProgramPatGen (MrcData, McChBitMask, Start, PatLen, Pattern);
      break;

    default:
      return mrcFail;
      break;
  }

  return mrcSuccess;
}

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
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      // Program the data rotation -- IncRate if Dynamic, 0 if Static.
      Cpgc20ConfigPgRotation (MrcData, ((PatCtlPtr->PatSource == MrcPatSrcDynamic) ? PatCtlPtr->IncRate : 0));  // No data rotation
      // Disable DC/Invert
      Cpgc20SetPgInvDcEn (MrcData, 0, 0);
      Cpgc20SetPgInvDcCfg (MrcData, Cpgc20InvertMode, 0, FALSE, 0, 0xAA);
      break;

    default:
      return mrcFail;
      break;
  }

  return mrcSuccess;
}

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
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20SetChunkClErrMsk (MrcData, CachelineMask, ChunkMask);
      break;

    default:
      return mrcFail;
  }

  return mrcSuccess;
}

/**
  This function programs the Error Mask for Data and ECC bit lanes.
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
  )
{
  MrcStatus     Status;
  UINT64_STRUCT SubChErrMsk;
  UINT64        DataValue;
  UINT8         EccValue;


  Status = mrcSuccess;

  // Using bitwise complement for Masks as the register fields are enabled when 0 and disabled when 1
  DataValue = ~DataMask;
  EccValue = ~EccMask;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      // We set the entire x64 channel.
      SubChErrMsk.Data = DataValue;
      Cpgc20SetDataErrMsk (MrcData, 0x1, SubChErrMsk.Data32.Low);
      Cpgc20SetDataErrMsk (MrcData, 0x2, SubChErrMsk.Data32.High);
      if (MrcData->Outputs.EccSupport) {
        Cpgc20SetEccErrMsk (MrcData, EccValue);
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

  @param[in]  MrcData    - Pointer to MRC global data.
  @param[in]  LoopCount  - Number of sequence iterations. 0 means infinite test.

  @retval MrcStatus - mrcSuccess if TestEngine is supported, else mrcFail.
**/
MrcStatus
MrcSetLoopcount (
  IN MrcParameters *const  MrcData,
  IN UINT32                LoopCount
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20SetLoopCount (MrcData, &LoopCount);
      break;

    default:
      return mrcFail;
      break;
  }

  return mrcSuccess;
}

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
  )
{
  MrcStatus Status;

  Status = mrcSuccess;
  MrcData->Outputs.ReutStopType = StopType;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20SetupTestErrCtl (MrcData, StopType, NumberOfErrors);
      break;

    default:
      Status = mrcFail;
  }

  return Status;
}

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
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      switch (ErrControlSel) {
        case ErrCounterCtlAllLanes:
          Status = Cpgc20SetupErrCounterCtl (MrcData, 0, ErrControlSel, 0, 0, 0);
          break;

        case ErrCounterCtlPerByte:
//        case ErrCounterCtlPerNibble:
        case ErrCounterCtlPerLane:
        case ErrCounterCtlPerUI:
          Status = Cpgc20SetupErrCounterCtl (MrcData, CounterPointer, ErrControlSel, CounterPointer, 1, CounterUI);
          break;

        default:
          Status = mrcWrongInputParameter;
          break;
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
  @param[in]  Controller  - Desired controller to get ErrStatus
  @param[in]  Channel     - Desired channel to get ErrStatus
  @param[out] Status      - Pointer to array where the lane error status values will be stored.

  @retval Nothing.
**/
void
MrcGetBitGroupErrStatus (
  IN  MrcParameters   *const  MrcData,
  IN  UINT32                  Controller,
  IN  UINT32                  Channel,
  OUT UINT8                   *Status
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20GetBitGroupErrStatus (MrcData, Controller, Channel, Status);
      break;

    default:
      break;
  }
}

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
          Status = Cpgc20GetErrEccChunkRankByteStatus (MrcData, Controller, Channel, Param, Buffer);
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
        Cpgc20GetSetBankMap (MrcData, Controller, Channel, BankList, Length, IsGet);
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
  )
{
  switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      switch (ErrControl) {
        case ErrCounterCtlAllLanes:
          Cpgc20GetErrCounterStatus (MrcData, Controller, Channel, 0, Status, Overflow);
          break;

        case ErrCounterCtlPerByte:
//        case ErrCounterCtlPerNibble:
        case ErrCounterCtlPerLane:
        case ErrCounterCtlPerUI:
          Cpgc20GetErrCounterStatus (MrcData, Controller, Channel, CounterSelect, Status, Overflow);
          break;

        default:
          break;
      }
      break;

    default:
      *Status = 0xFFFFFFFF;
      break;
  }
}

/**
CADB Select Override Mapping:

CADB_BUF bit    CADB_BUF.field bit    DDR4            LPDDR4 Select   LPDDR4 DeSelect
=====================================================================================
[41]            CADB_BUF.CA [23]                      CA_4th[5]
[40]            CADB_BUF.CA [22]      ACT_n           CA_4th[4]
[39]            CADB_BUF.CA [21]      BG1             CA_4th[3]
[38]            CADB_BUF.CA [20]      BG0             CA_4th[2]
[37]            CADB_BUF.CA [19]      BA1             CA_4th[1]
[36]            CADB_BUF.CA [18]      BA0             CA_4th[0]
[35]            CADB_BUF.CA [17]                      CA_3rd[5]
[34]            CADB_BUF.CA [16]      MA[16]/RAS_n    CA_3rd[4]
[33]            CADB_BUF.CA [15]      MA[15]/CAS_n    CA_3rd[3]
[32]            CADB_BUF.CA [14]      MA[14]/WE_n     CA_3rd[2]
[31]            CADB_BUF.CA [13]      MA[13]          CA_3rd[1]
[30]            CADB_BUF.CA [12]      MA[12]          CA_3rd[0]
[29]            CADB_BUF.CA [11]      MA[11]          CA_2nd[5]
[28]            CADB_BUF.CA [10]      MA[10]          CA_2nd[4]
[27]            CADB_BUF.CA [9]       MA[9]           CA_2nd[3]
[26]            CADB_BUF.CA [8]       MA[8]           CA_2nd[2]
[25]            CADB_BUF.CA [7]       MA[7]           CA_2nd[1]
[24]            CADB_BUF.CA [6]       MA[6]           CA_2nd[0]
[23]            CADB_BUF.CA [5]       MA[5]           CA_1st[5]       CA[5]_subch0
[22]            CADB_BUF.CA [4]       MA[4]           CA_1st[4]       CA[4]_subch0
[21]            CADB_BUF.CA [3]       MA[3]           CA_1st[3]       CA[3]_subch0
[20]            CADB_BUF.CA [2]       MA[2]           CA_1st[2]       CA[2]_subch0
[19]            CADB_BUF.CA [1]       MA[1]           CA_1st[1]       CA[1]_subch0
[18]            CADB_BUF.CA [0]       MA[0]           CA_1st[0]       CA[0]_subch0
[17]            CADB_BUF.PAR          PAR
[16]            CADB_BUF.VAL          Set for all the non-tri-stated CADB chunks!
[15]
[14]            CADB_BUF.CKE [3]      CKE[3]                          CKE[1]_subch1
[13]            CADB_BUF.CKE [2]      CKE[2]                          CKE[0]_subch1
[12]            CADB_BUF.CKE [1]      CKE[1]                          CKE[1]_subch0
[11]            CADB_BUF.CKE [0]      CKE[0]                          CKE[0]_subch0
[10]            CADB_BUF.ODT [3]      ODT[3]                          CS[3]_subch1
[9]             CADB_BUF.ODT [2]      ODT[2]                          CS[2]_subch1
[8]             CADB_BUF.ODT [1]      ODT[1]                          CS[3]_subch0
[7]             CADB_BUF.ODT [0]      ODT[0]                          CS[2]_subch0
[6]
[5]
[4]
[3]             CADB_BUF.CS [3]       CSb[3]                          CS[1]_subch1
[2]             CADB_BUF.CS [2]       CSb[2]                          CS[0]_subch1
[1]             CADB_BUF.CS [1]       CSb[1]                          CS[1]_subch0
[0]             CADB_BUF.CS [0]       CSb[0]                          CS[0]_subch0
**/
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
CpgcConvertDdrToCadb (
  IN  MrcParameters     *const  MrcData,
  IN  MRC_CA_MAP_TYPE   *const  CmdAddr,
  IN  UINT8                     Cke[2],
  IN  UINT8                     Cs[2],
  IN  UINT8                     Odt,
  OUT UINT64_STRUCT     *const  CadbVal
  )
{
  MRC_FUNCTION  *MrcCall;
  MrcStatus     Status;
  MrcDdrType    DdrType;
  UINT64        CadbBits;

  DdrType = MrcData->Outputs.DdrType;
  MrcCall = MrcData->Inputs.Call.Func;
  Status = mrcSuccess;
  CadbBits = 0;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    CadbBits = MrcCall->MrcLeftShift64 (CmdAddr->Ddr4.Ma, CADB_DDR4_MA_0_16_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 (CmdAddr->Ddr4.Ba, CADB_DDR4_BA_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 (CmdAddr->Ddr4.Bg, CADB_DDR4_BG_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 (CmdAddr->Ddr4.Act_n, CADB_DDR4_ACT_N_OFF);
    // We don't use CA Parity pin, no need to stress it
    // CadbBits |= CmdAddr->Ddr4.Par << CADB_DDR4_PAR_OFF;
    CadbBits |= MrcCall->MrcLeftShift64 ((Cke[0] & CADB_DDR4_CKE_CTL_MSK), CADB_DDR4_CKE_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Cs[0] & CADB_DDR4_CKE_CTL_MSK), CADB_DDR4_CS_B_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Odt & CADB_DDR4_CKE_CTL_MSK), CADB_DDR4_ODT_OFF);
  } else if (MrcData->Outputs.Lpddr) {
    if (DdrType == MRC_DDR_TYPE_LPDDR4) {
      CadbBits = CmdAddr->Lpddr4.Ca1 << CADB_LPDDR_CA_OFF;
    } else {
      CadbBits = CmdAddr->Lpddr5.Ca1 << CADB_LPDDR_CA_OFF;
    }
    //    CadbBits |= CmdAddr->Lpddr4.Ca2 << CADB_LPDDR4_CA_2_OFF;
    //    CadbBits |= MrcCall->MrcLeftShift64 (CmdAddr->Lpddr4.Ca3, CADB_LPDDR4_CA_3_OFF);
    //    CadbBits |= MrcCall->MrcLeftShift64 (CmdAddr->Lpddr4.Ca4, CADB_LPDDR4_CA_4_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Cke[0] & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CKE_SC0_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Cke[1] & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CKE_SC1_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Cs[0] & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CS_0_1_SC0_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 ((Cs[1] & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CS_0_1_SC1_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 (((Cs[0] >> 2) & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CS_2_3_SC0_OFF);
    CadbBits |= MrcCall->MrcLeftShift64 (((Cs[1] >> 2) & CADB_LPDDR_CS_CKE_MSK), CADB_LPDDR_CS_2_3_SC1_OFF);
  } else {
    //@todo add DDR5
    Status = mrcDimmNotSupport;
  }
  CadbBits |= MrcCall->MrcLeftShift64 (1, CADB_BUF_VAL_OFF);    // Set VAL bit, otherwise it may be tri-stated

  CadbVal->Data = CadbBits;

  return Status;
}


/**
  This function will configure and program the CPGC DPAT Unisequencers.  The PGs must be selected before this call.

  @param[in]  MrcData    - Global MRC data.
  @param[in]  LfsrPoly   - LFSR Polynominal applied to all UNISEQs
  @param[in]  PatCtlPtr  - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in]  Start      - Zero based index which Unisequencer to start programming.
  @param[in]  UsqCount   - Number of Unisequencers to program.

  @retval - Nothing
**/
void
MrcInitUnisequencer (
  IN MrcParameters *const    MrcData,
  IN  MRC_PG_LFSR_TYPE       LfsrPoly,
  IN  MRC_PATTERN_CTL *const PatCtlPtr,
  IN const UINT8             Start,
  IN const UINT8             UsqCount
  )
{
  UINT8   Index;
  UINT8   Stop;

  Stop = Start + UsqCount;
  for (Index = Start; Index < Stop; Index++) {
    switch (MrcData->Inputs.TestEngine) {
    case MrcTeCpgc20:
      Cpgc20DPatUsqCfg (MrcData, LfsrPoly, PatCtlPtr, Index);
      break;
    default:
      break;
    }
  }
}
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
  @todo: Move to GetSet infrastructure.

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
  UINT32      Controller;
  UINT32      Channel;
  UINT32      IpChannel;
  BOOLEAN     Lpddr;
  MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRUCT CpgcSeqCfgA;

  Outputs = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if ((MrcChannelExist (MrcData, Controller, Channel)) && (!(IS_MC_SUB_CH (Lpddr, Channel)))) {
        IpChannel = LP_IP_CH (Lpddr, Channel);
        Offset = MrcGetCpgcSeqCfgOffset (MrcData, Controller, IpChannel);
        CpgcSeqCfgA.Data =  MrcReadCR (MrcData, Offset);
        CpgcSeqCfgA.Bits.INITIALIZATION_MODE = ActiveMode ? CPGC20_ACTIVE_MODE : CPGC20_IDLE_MODE;
        MrcWriteCR (MrcData, Offset, CpgcSeqCfgA.Data);
      }
    }
  }
}

