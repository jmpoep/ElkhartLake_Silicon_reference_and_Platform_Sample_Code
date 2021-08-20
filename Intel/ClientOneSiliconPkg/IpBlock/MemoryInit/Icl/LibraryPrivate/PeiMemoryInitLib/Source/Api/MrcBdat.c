/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcSpdProcessing.h"
#include "McAddress.h"
#ifndef MRC_MINIBIOS_BUILD
#include "MemoryInit.h"
#else
#include "ConfigBlock.h"
#include "MrcOemPlatform.h"
#endif

#ifdef BDAT_SUPPORT
// Index of signals in the RankResultType0/ByteResultType/LaneResultType
#define RESULTS_RX_DQ_INDEX          0
#define RESULTS_TX_DQ_INDEX          1
#define RESULTS_RX_VREF_INDEX        2
#define RESULTS_TX_VREF_INDEX        3

// Index of signals in the RankResultType1
#define RESULTS_CMD_INDEX            0
#define RESULTS_CMD_VREF_INDEX       1

// Index of signals in the RankResultType3
#define RESULTS_RECEN_INDEX          0
#define RESULTS_WRLVL_INDEX          1

#define LOW_INDEX                    0
#define HIGH_INDEX                   1

#define IO_LEVEL_DDR_LEVEL           1

#define GetCrc16                     GetDimmCrc

/**
  This function print out the RMT column data

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      RmtRows       - The RMT column result.
  @param[in]      ElementNumber - The index of the results.

  @retval  None
**/
VOID
PrintBdatResult (
  IN OUT MrcParameters  *const MrcData,
  IN RMT_RESULT_COLUMNS *RmtRows,
  IN UINT32             ElementNumber
  )
{
  MrcDebug           *Debug;
  RMT_RESULT_COLUMNS *RmtRow;
  UINT8 i;
  UINT8 j;

  RmtRow = &(RmtRows[ElementNumber]);
  Debug  = &MrcData->Outputs.Debug;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "i: %d, Ch: %d Rank: %d Type: %d Lane: %d - [",
    ElementNumber,
    RmtRow->Header.Channel,
    RmtRow->Header.RankA,
    RmtRow->Header.ResultType,
    RmtRow->Header.Lane
    );

  for (i = 0; i < 4; i++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "[");
    for (j = 0; j < 2; j++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %d", RmtRow->Margin[i][j]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "]");
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "]\n");
}

/**
  This function determines the number of rows for the RMT Results

  @param[in, out] MrcData       - Include all MRC global data.

  @retval  The number of RMT Result Rows
**/
UINT32
GetNumberRowsBdatResult (
  IN MrcParameters *const MrcData
  )
{
  const MrcOutput     *Outputs;
  const MrcChannelOut *ChannelOut;          // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;             // Pointer to the DIMM output portion of the MRC global data area.
  UINT32 NumberRows;
  UINT8  BdatTestType;
  UINT8  Controller;
  UINT8  Channel;
  UINT8  SubCh;
  UINT8  SubChMax;
  UINT8  Dimm;
  UINT8  Rank;
  UINT8  DqCnt;
  BOOLEAN EnhancedChannelMode;

  NumberRows  = 0;
  Outputs     = &MrcData->Outputs;
  EnhancedChannelMode = Outputs->EnhancedChannelMode;
  DqCnt       = (EnhancedChannelMode) ? MAX_DQ_IN_SUB_CHANNEL : (Outputs->EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  SubChMax    = (EnhancedChannelMode) ? MAX_SUB_CHANNEL : 1;
  BdatTestType = MrcData->Inputs.BdatTestType;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
                DimmOut = &ChannelOut->Dimm[Dimm];
                if (DimmOut->Status == DIMM_PRESENT) {
                  for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
                    if (BdatTestType == Margin2DType) {
                      NumberRows += MAX_2D_EYE_OFFSETS * 2;
                    } else {
                      // per rank RankResultType0  - RxDqs, TxDq, RxVref and TxVref
                      // per rank RankResultType1  - Cmd, Cmd Vref
                      // per rank RankResultType1  - RecEN, Wrlvl
                      NumberRows += 3;
                      // per bit margin LaneResultType
                      if (BdatTestType == RankMarginToolPerBitType) {
                        NumberRows += DqCnt;
                      }
                    }
                  } // Rank
                } // if Dimm present
              } // Dimm
            } // if SubCh present
          } // SubCh
        } // if Channel present
      } // Channel
    } // if Controller present
  } // Controller

  return NumberRows;
}

/**
  This function returns the size of the BDAT Schema for the specified BDAT Test Type.

  @param[in, out] MrcData           - Include all MRC global data.

  @retval  The size of the BDAT Schema.
**/
UINT32
GetBdatSchemaSize (
  IN MrcParameters *const MrcData
  )
{
  UINT32 BdatSchemaSize;

  if (MrcData->Inputs.BdatTestType == Margin2DType) {
    BdatSchemaSize = sizeof (RESULTS_DATA_HDR) + sizeof (MARGIN_2D_RESULT_METADATA) + (sizeof (MARGIN_2D_RESULT_COLUMNS) * GetNumberRowsBdatResult (MrcData));
  } else {
    BdatSchemaSize = sizeof (RESULTS_DATA_HDR) + sizeof (RMT_RESULT_METADATA) + (sizeof (RMT_RESULT_COLUMNS) * GetNumberRowsBdatResult (MrcData));
  }

  return BdatSchemaSize;
}

/**
  This function fills the RMT schema 6 which defined in the BDAT spec.
  The schema include meta data and columns data sections.

  @param[in, out] MrcData           - Include all MRC global data.
  @param[out]     RmtDataBuffer     - Pointer to data block to fill up the RMT structure.
  @param[in]      RmtDataBufferSize - Size of the RMT data block.
  @param[in]      MsgPrint          - Show debug prints

  @retval  None
**/
VOID
FillRMTBdatStructure (
  IN OUT MrcParameters *const MrcData,
  OUT   VOID           *RmtDataBuffer,
  IN    UINT32          RmtDataBufferSize,
  IN    BOOLEAN         MsgPrint
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  const MrcChannelOut *ChannelOut;       // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcDebugMsgLevel    DebugLevel;
  BASE_RMT_RESULT     *RmtResults;
  RMT_RESULT_COLUMNS  *RmtRow;
  INT32 MaxNumberRows;
  INT32 *ResultElementCount;
  UINT8 Controller;
  UINT8 SystemChannel;
  UINT8 Channel;
  UINT8 SubCh;
  UINT8 SubChMax;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 RankInChannel;     // Rank number in a channel.
  UINT8 Bit;
  UINT8 DqCnt;
  UINT8 Sdram;
  UINT8 Dq;                // DQ number in the rank.
  UINT8 DqStart;
  UINT8 DqStop;
  BOOLEAN EnhancedChannelMode;
  const MrcDqTimeMargin   *RxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqTimeMargin   *TxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin   *RxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin   *TxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  const MrcCommandMargin  *CmdMargin;
  const MrcRecvEnMargin   *RecvEnMargin;
  const MrcWrLevelMargin  *WrLvlMargin;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  DqCnt   = (Outputs->EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  EnhancedChannelMode = (Outputs->EnhancedChannelMode);
  SubChMax = (EnhancedChannelMode) ? MAX_SUB_CHANNEL : 1;

  RmtResults = (BASE_RMT_RESULT*) RmtDataBuffer;
  MrcCall->MrcSetMem ((UINT8*) RmtDataBuffer, RmtDataBufferSize, 0);
  MrcCall->MrcCopyMem ((UINT8*) (&RmtResults->ResultsHeader.MdBlock.MetadataType), (UINT8*) (&gRmtResultMetadataGuid), sizeof (RmtResults->ResultsHeader.MdBlock.MetadataType));
  RmtResults->ResultsHeader.MdBlock.MetadataSize = sizeof (RMT_RESULT_METADATA);
  MrcCall->MrcCopyMem ((UINT8*) (&RmtResults->ResultsHeader.RsBlock.ResultType), (UINT8*) (&gRmtResultColumnsGuid), sizeof (RmtResults->ResultsHeader.RsBlock.ResultType));
  RmtResults->ResultsHeader.RsBlock.ResultElementSize = sizeof (RMT_RESULT_COLUMNS);
  MaxNumberRows = RmtDataBufferSize - sizeof (RESULTS_DATA_HDR) - sizeof (RMT_RESULT_METADATA);
  MaxNumberRows = MaxNumberRows / sizeof (RMT_RESULT_COLUMNS);

  RmtResults->ResultsHeader.RsBlock.ResultCapacity = MaxNumberRows;
  ResultElementCount = &(RmtResults->ResultsHeader.RsBlock.ResultElementCount);
  *ResultElementCount = 0;
  RmtResults->Metadata.EnableCtlAllMargin       = 0;
  RmtResults->Metadata.SinglesBurstLength       = 128;  //  NumCL = 128;
  RmtResults->Metadata.SinglesLoopCount         = (Inputs->RMTLoopCount == 0) ? 17 : Inputs->RMTLoopCount;  //   DqLoopCount  = 17; CmdLoopCount = 17;
  RmtResults->Metadata.TurnaroundsBurstLength   = 0;
  RmtResults->Metadata.TurnaroundsLoopCount     = 0;
  RmtResults->Metadata.ScramblerOverrideMode    = DontTouchScrambler;
  RmtResults->Metadata.PiStepUnit[0]            = 0;
  RmtResults->Metadata.RxVrefStepUnit[0]        = 0;
  RmtResults->Metadata.TxVrefStepUnit[0][0]     = 0;
  RmtResults->Metadata.CmdVrefStepUnit[0][0]    = 0;
  RmtResults->Metadata.MajorVer                 = 1;
  RmtResults->Metadata.MinorVer                 = 0;
  RmtRow = &(RmtResults->Rows[0]);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              SystemChannel = (EnhancedChannelMode) ? (MAX_CHANNEL * Channel) + SubCh : Channel;
              DqStart = (EnhancedChannelMode) ? SubCh * MAX_DQ_IN_SUB_CHANNEL : 0;
              DqStop = (EnhancedChannelMode) ? MAX_DQ_IN_SUB_CHANNEL + DqStart : DqCnt;
              for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
                DimmOut = &ChannelOut->Dimm[Dimm];
                if (DimmOut->Status == DIMM_PRESENT) {
                  for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
                    RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
                    MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d \n", SystemChannel, Dimm, Rank);
                    // Per rank RankResultType0  - RxDqs, TxDq, RxVref and TxVref
                    RmtRow[*ResultElementCount].Header.Controller = Controller;
                    RmtRow[*ResultElementCount].Header.Channel    = SystemChannel;
                    RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                    RmtRow[*ResultElementCount].Header.RankA      = Rank;
                    RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                    RmtRow[*ResultElementCount].Header.ResultType = RankResultType0; //RxDqsdelay, TxDqDelay, RxVref, TxVref

                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]    = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]   = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]    = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]   = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]  = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]  = 0xFF;
                    RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = 0xFF;

                    // Rank margin results are the min value of all DQ lanes.
                    for (Dq = DqStart; Dq < DqStop; Dq++) {
                      Sdram                   = Dq / MAX_BITS;
                      Bit                     = Dq % MAX_BITS;
                      RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
                      TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
                      RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
                      TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];

                      if (RxDqMargin->Left < RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX] = RxDqMargin->Left;
                      }
                      if (RxDqMargin->Right < RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX] = RxDqMargin->Right;
                      }
                      if (TxDqMargin->Left < RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX] = TxDqMargin->Left;
                      }
                      if (TxDqMargin->Right < RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX] = TxDqMargin->Right;
                      }
                      if (RxVrefDqMargin->Low < RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX] = RxVrefDqMargin->Low;
                      }
                      if (RxVrefDqMargin->High < RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = RxVrefDqMargin->High;
                      }
                      if (TxVrefDqMargin->Low < RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX] = TxVrefDqMargin->Low;
                      }
                      if (TxVrefDqMargin->High < RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX]){
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = TxVrefDqMargin->High;
                      }
                    } // Dq loop
                    if (MsgPrint) {
                      PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                    }
                    *ResultElementCount += 1;
                    if (*ResultElementCount > MaxNumberRows) {
                      MRC_DEBUG_MSG (Debug, DebugLevel, "%s Out of space after per rank DQ\n", gErrString);
                      return;
                    }
                    // Per rank RankResultType1  - CmdT, CmdV
                    CmdMargin = &ChannelOut->Command[RankInChannel][SubCh];
                    RmtRow[*ResultElementCount].Header.Controller = Controller;
                    RmtRow[*ResultElementCount].Header.Channel    = SystemChannel;
                    RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                    RmtRow[*ResultElementCount].Header.RankA      = Rank;
                    RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                    RmtRow[*ResultElementCount].Header.ResultType = RankResultType1; // CmdAll, CmdVref, CtlAll
                    RmtRow[*ResultElementCount].Margin[RESULTS_CMD_INDEX][LOW_INDEX]        = CmdMargin->Left;
                    RmtRow[*ResultElementCount].Margin[RESULTS_CMD_INDEX][HIGH_INDEX]       = CmdMargin->Right;
                    RmtRow[*ResultElementCount].Margin[RESULTS_CMD_VREF_INDEX][LOW_INDEX]   = CmdMargin->Low;
                    RmtRow[*ResultElementCount].Margin[RESULTS_CMD_VREF_INDEX][HIGH_INDEX]  = CmdMargin->High;
                    if (MsgPrint) {
                      PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                    }
                    *ResultElementCount += 1;
                    if (*ResultElementCount > MaxNumberRows) {
                      MRC_DEBUG_MSG (Debug, DebugLevel, "%s Out of space after per rank CMD\n", gErrString);
                      return;
                    }

                    // Per rank RankResultType1  - RecEn, Wrlvl
                    RecvEnMargin = &ChannelOut->ReceiveEnable[RankInChannel][SubCh];
                    WrLvlMargin  = &ChannelOut->WriteLevel[RankInChannel][SubCh];
                    RmtRow[*ResultElementCount].Header.Controller = Controller;
                    RmtRow[*ResultElementCount].Header.Channel    = SystemChannel;
                    RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                    RmtRow[*ResultElementCount].Header.RankA      = Rank;
                    RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                    RmtRow[*ResultElementCount].Header.ResultType = RankResultType3; //RecEn and WrLvl
                    RmtRow[*ResultElementCount].Margin[RESULTS_RECEN_INDEX][LOW_INDEX]  = RecvEnMargin->Left;
                    RmtRow[*ResultElementCount].Margin[RESULTS_RECEN_INDEX][HIGH_INDEX] = RecvEnMargin->Right;
                    RmtRow[*ResultElementCount].Margin[RESULTS_WRLVL_INDEX][LOW_INDEX]  = WrLvlMargin->Left;
                    RmtRow[*ResultElementCount].Margin[RESULTS_WRLVL_INDEX][HIGH_INDEX] = WrLvlMargin->Right;
                    if (MsgPrint) {
                      PrintBdatResult (MrcData, RmtRow, *ResultElementCount);
                    }
                    *ResultElementCount += 1;
                    if (*ResultElementCount > MaxNumberRows) {
                      MRC_DEBUG_MSG (Debug, DebugLevel, "%s Out of space after per rank RcvEn/WrLvl\n", gErrString);
                      return;
                    }

                    if (Inputs->BdatTestType == RankMarginToolPerBitType) {
                      for (Dq = DqStart; Dq < DqStop; Dq++) {
                        MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d L: %d\n", SystemChannel, Dimm, Rank, Dq);
                        // per lane LaneResultType  - RxDqs, TxDq, RxVref and TxVref
                        RmtRow[*ResultElementCount].Header.Controller = Controller;
                        RmtRow[*ResultElementCount].Header.Channel    = SystemChannel;
                        RmtRow[*ResultElementCount].Header.DimmA      = Dimm;
                        RmtRow[*ResultElementCount].Header.RankA      = Rank;
                        RmtRow[*ResultElementCount].Header.Lane       = (EnhancedChannelMode) ? Dq % MAX_DQ_IN_SUB_CHANNEL : Dq;
                        RmtRow[*ResultElementCount].Header.IoLevel    = IO_LEVEL_DDR_LEVEL;
                        RmtRow[*ResultElementCount].Header.ResultType = LaneResultType; //RxDqsdelay, TxDqDelay, RxVref, TxVref

                        Sdram                   = Dq / MAX_BITS;
                        Bit                     = Dq % MAX_BITS;
                        RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
                        TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
                        RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
                        TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];

                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][LOW_INDEX]    = RxDqMargin->Left;
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_DQ_INDEX][HIGH_INDEX]   = RxDqMargin->Right;
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][LOW_INDEX]    = TxDqMargin->Left;
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_DQ_INDEX][HIGH_INDEX]   = TxDqMargin->Right;
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][LOW_INDEX]  = RxVrefDqMargin->Low;
                        RmtRow[*ResultElementCount].Margin[RESULTS_RX_VREF_INDEX][HIGH_INDEX] = RxVrefDqMargin->High;
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][LOW_INDEX]  = TxVrefDqMargin->Low;
                        RmtRow[*ResultElementCount].Margin[RESULTS_TX_VREF_INDEX][HIGH_INDEX] = TxVrefDqMargin->High;

                        if (MsgPrint) {
                          PrintBdatResult(MrcData, RmtRow, *ResultElementCount);
                        }
                        *ResultElementCount += 1;
                        if (*ResultElementCount > MaxNumberRows) {
                          MRC_DEBUG_MSG (Debug, DebugLevel, "%s Out of space after per bit DQ\n", gErrString);
                          return;
                        }
                      } // Dq
                    } // RankMarginToolPerBitType
                  } // Rank
                } // if Dimm present
              } // Dimm
            } // if SubCh present
          } // SubCh
        } // if Channel present
      } // Channel
    } // if Controller present
  } // Controller

  RmtResults->Metadata.ResultEleCount = (UINT16) *ResultElementCount;
} // FillBdatStructure

/**
  This function fills the Margin2D.
  The schema include meta data and columns data sections.

  @param[in, out] MrcData           - Include all MRC global data.
  @param[out]     DataBuffer     - Pointer to data block to fill up the Margin2D result structure.
  @param[in]      DataBufferSize - Size of the Margin2D results data block.
  @param[in]      MsgPrint          - Show debug prints

  @retval  None
**/
VOID
FillMargin2DBdatStructure (
  IN OUT MrcParameters *const MrcData,
  OUT   VOID           *DataBuffer,
  IN    UINT32          DataBufferSize,
  IN    BOOLEAN         MsgPrint
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  const MrcChannelOut *ChannelOut;       // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  static const INT16  VrefPointsConst[] = {0, -6, -12, -18, 6, 12, 18};
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcDebugMsgLevel    DebugLevel;
  BASE_MARGIN_2D_RESULT *Margin2DResults;
  MARGIN_2D_RESULT_COLUMNS  *Margin2DRow;
  INT32 MaxNumberRows;
  INT32 *ResultElementCount;
  UINT8 Controller;
  UINT8 SystemChannel;
  UINT8 Channel;
  UINT8 SubCh;
  UINT8 SubChMax;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 RankInChannel;     // Rank number in a channel.
  MARGIN_2D_EYE_TYPE EyeTypeIndex;
  UINT8 OuterOffsetIndex;
  BOOLEAN EnhancedChannelMode;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  EnhancedChannelMode = Outputs->EnhancedChannelMode;
  SubChMax = EnhancedChannelMode ? MAX_SUB_CHANNEL : 1;

  Margin2DResults = (BASE_MARGIN_2D_RESULT*) DataBuffer;
  MrcCall->MrcSetMem ((UINT8*) DataBuffer, DataBufferSize, 0);
  MrcCall->MrcCopyMem ((UINT8*) (&Margin2DResults->ResultsHeader.MdBlock.MetadataType), (UINT8*) (&gMargin2DResultMetadataGuid), sizeof (Margin2DResults->ResultsHeader.MdBlock.MetadataType));
  Margin2DResults->ResultsHeader.MdBlock.MetadataSize = sizeof (MARGIN_2D_RESULT_METADATA);
  MrcCall->MrcCopyMem ((UINT8*) (&Margin2DResults->ResultsHeader.RsBlock.ResultType), (UINT8*) (&gMargin2DResultColumnsGuid), sizeof (Margin2DResults->ResultsHeader.RsBlock.ResultType));
  Margin2DResults->ResultsHeader.RsBlock.ResultElementSize = sizeof (MARGIN_2D_RESULT_COLUMNS);
  MaxNumberRows = DataBufferSize - sizeof (RESULTS_DATA_HDR) - sizeof (MARGIN_2D_RESULT_METADATA);
  MaxNumberRows = MaxNumberRows / sizeof (MARGIN_2D_RESULT_COLUMNS);
  Margin2DResults->ResultsHeader.RsBlock.ResultCapacity = MaxNumberRows;
  ResultElementCount = &(Margin2DResults->ResultsHeader.RsBlock.ResultElementCount);
  *ResultElementCount = 0;
  Margin2DResults->Metadata.BurstLength       = Outputs->NumCL;
  Margin2DResults->Metadata.LoopCount         = 15;
  Margin2DResults->Metadata.MajorVer          = 1;
  Margin2DResults->Metadata.MinorVer          = 0;
  Margin2DRow = &(Margin2DResults->Rows[0]);

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              SystemChannel = (EnhancedChannelMode) ? (MAX_CHANNEL * Channel) + SubCh : Channel;
              //DqStart = (EnhancedChannelMode) ? SubCh * MAX_DQ_IN_SUB_CHANNEL : 0;
              //DqStop = (EnhancedChannelMode) ? MAX_DQ_IN_SUB_CHANNEL + DqStart : DqCnt;
              for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
                DimmOut = &ChannelOut->Dimm[Dimm];
                if (DimmOut->Status == DIMM_PRESENT) {
                  for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
                    RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
                    MRC_DEBUG_MSG (Debug, DebugLevel, "Ch: %d, D: %d R: %d \n", Channel, Dimm, Rank);
                    for (EyeTypeIndex = RxDqsRxVrefEyeType; EyeTypeIndex <= TxDqTxVrefEyeType; EyeTypeIndex++) {
                      for (OuterOffsetIndex = 0; OuterOffsetIndex < MAX_2D_EYE_OFFSETS; OuterOffsetIndex++){
                        Margin2DRow[*ResultElementCount].Controller           = Controller;
                        Margin2DRow[*ResultElementCount].Channel              = SystemChannel;
                        Margin2DRow[*ResultElementCount].Dimm                 = Dimm;
                        Margin2DRow[*ResultElementCount].Rank                 = Rank;
                        Margin2DRow[*ResultElementCount].Lane                 = 0; // We don't collect per lane margin2d data yet
                        Margin2DRow[*ResultElementCount].EyeType              = (UINT8) EyeTypeIndex;
                        Margin2DRow[*ResultElementCount].OuterMarginParamType = (UINT8) VotageMarginParamType;
                        Margin2DRow[*ResultElementCount].OuterOffset          = VrefPointsConst[OuterOffsetIndex];
                        Margin2DRow[*ResultElementCount].LeftMargin           = Outputs->Margin2DResult[EyeTypeIndex][RankInChannel][SystemChannel][OuterOffsetIndex][1];
                        Margin2DRow[*ResultElementCount].RightMargin          = Outputs->Margin2DResult[EyeTypeIndex][RankInChannel][SystemChannel][OuterOffsetIndex][0];
                        MRC_DEBUG_MSG (Debug, DebugLevel, "ElementCount:%d Controller:%d Channel:%d Dimm:%d Rank:%d lane:%d EyeType:%d OuterMarginParamType:%d OuterOffset:%d LeftMargin:%d RightMargin:%d \n",
                          *ResultElementCount,
                          Margin2DRow[*ResultElementCount].Controller,
                          Margin2DRow[*ResultElementCount].Channel,
                          Margin2DRow[*ResultElementCount].Dimm,
                          Margin2DRow[*ResultElementCount].Rank,
                          Margin2DRow[*ResultElementCount].Lane,
                          Margin2DRow[*ResultElementCount].EyeType,
                          Margin2DRow[*ResultElementCount].OuterMarginParamType,
                          Margin2DRow[*ResultElementCount].OuterOffset,
                          Margin2DRow[*ResultElementCount].LeftMargin,
                          Margin2DRow[*ResultElementCount].RightMargin
                          );
                        *ResultElementCount += 1;
                        if (*ResultElementCount > MaxNumberRows) {
                          MRC_DEBUG_MSG (Debug, DebugLevel, "BDAT: Not enough space for Margin2D results after filling row:%d.\n", (*ResultElementCount - 1));
                          return;
                        }
                      } // OuterOffset
                    } // EyeType
                  } // Rank
                } // if Dimm present
              } // Dimm
            } // if SubCh present
          } // SubCh
        } // if Channel present
      } // Channel
    } // if Controller present
  } // Controller

  Margin2DResults->Metadata.ResultEleCount = (UINT16) *ResultElementCount;
} // FillBdatStructure

/**
@brief
  Fill the compatible data structure BDAT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData - Constant pointer to the Mrc data structure which conatins the BDAT structure to fill.

  @retval mrcSuccess if the Hob is created successfully, otherwise mrcFail.
**/
MrcStatus
MrcFillBdatStructure (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput       *Inputs;
  const MRC_FUNCTION   *MrcCall;
  MrcOutput            *Outputs;
  MrcDebug             *Debug;
  MRC_BDAT_SCHEMA_HEADER_STRUCTURE *BdatSchemaHdrPtr;
  EFI_STATUS   Status;
  UINT8        Index;
  UINT16       NextSchema;
  UINT32       BdatSchemaSize;
  UINT16       BdatHobSize;
  UINT8        BdatSchemaType;
#ifdef MRC_DEBUG_PRINT
  const char   RMTSchemaString[]      = "Rmt Schema 6B";
  const char   Margin2DSchemaString[] = "Margin 2D Schema";
  const char   *SchemaTypeString;
#endif // MRC_DEBUG_PRINT


  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;
  BdatSchemaType = Inputs->BdatTestType;

#ifdef MRC_DEBUG_PRINT
  if (BdatSchemaType == Margin2DType) {
    SchemaTypeString = Margin2DSchemaString;
  } else {
    SchemaTypeString = RMTSchemaString;
  }
#endif

  if (Inputs->BdatEnable) {
    // first find the first empty spot
    for (Index = 0; Index < MAX_SCHEMA_LIST_LENGTH; Index++) {
      if (Outputs->BdatMemoryHob[Index].Pointer == NULL) {
        break;
      }
    }

    // Create a HOB to store the BDAT Schema
    if ((Index < MAX_SCHEMA_LIST_LENGTH) && (Outputs->BdatSchemasHob.Pointer != NULL)) {
      BdatSchemaSize = GetBdatSchemaSize (MrcData);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Filling/Saving %s structure of size %d at schema list index:%d\n", SchemaTypeString, BdatSchemaSize, Index);
      BdatHobSize = (UINT16) (BdatSchemaSize + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE) + sizeof (EFI_HOB_GUID_TYPE));
      Status = MrcGetHobForDataStorage (
#ifdef MRC_MINIBIOS_BUILD
                MrcData,
#endif
                (VOID **)&Outputs->BdatMemoryHob[Index].Pointer,
                BdatHobSize,
                &gSsaBiosResultsGuid
                );
      if (Status == EFI_SUCCESS) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s HOB at %08Xh\n", SchemaTypeString, Outputs->BdatMemoryHob[Index]);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s HOB size: %d\n", SchemaTypeString, BdatHobSize);
        NextSchema = Outputs->BdatSchemasHob.Pointer->SchemaHobCount;
        Outputs->BdatSchemasHob.Pointer->SchemaHobCount = NextSchema + 1;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ">SchemaHobCount: %d \n", Outputs->BdatSchemasHob.Pointer->SchemaHobCount);
        MrcCall->MrcCopyMem ((UINT8 *) &(Outputs->BdatSchemasHob.Pointer->SchemaHobGuids[NextSchema]), (UINT8 *) &gSsaBiosResultsGuid, sizeof (EFI_GUID));  // Housekeeping for the list of schema IDs
        BdatSchemaHdrPtr = (MRC_BDAT_SCHEMA_HEADER_STRUCTURE *) &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema);
        MrcCall->MrcCopyMem ((UINT8 *) &BdatSchemaHdrPtr->SchemaId, (UINT8 *) &gSsaBiosResultsGuid, sizeof (EFI_GUID));
        BdatSchemaHdrPtr->DataSize = BdatSchemaSize;
        GetCrc16 ((UINT8 *) BdatSchemaHdrPtr, sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE), &BdatSchemaHdrPtr->Crc16);  // CRC for the schema header section only

        // Fill up the RMT results
        if (BdatSchemaType == Margin2DType) {
          FillMargin2DBdatStructure(
            MrcData,
            ((UINT8 *) &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema)) + sizeof(MRC_BDAT_SCHEMA_HEADER_STRUCTURE),
            BdatSchemaSize,
            TRUE
            );
        } else {
          FillRMTBdatStructure (
            MrcData,
            ((UINT8 *) &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema)) + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE),
            BdatSchemaSize,
            TRUE
            );
        }
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Can't create HOB\n");
        return mrcFail;
      }
    } else {
      if (Index == MAX_SCHEMA_LIST_LENGTH) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "No more room left in BDAT Schema List\n");
      } else if (Outputs->BdatSchemasHob.Pointer == NULL) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BDAT Schema HOB Pointer is NULL!\n");
      }
      return mrcFail;
    }

    MrcWriteCR (MrcData, 0x5430, (UINT32) (Outputs->BdatMemoryHob[Index].Pointer));  // NCDECS_CR_SCRATCHPAD_NCU_2_REG
  } // if Rmt is enabled

  return mrcSuccess;
}
#endif // BDAT_SUPPORT
