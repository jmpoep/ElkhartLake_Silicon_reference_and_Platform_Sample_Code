/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

#ifdef BDAT_SUPPORT
#define TBD                       0
#define CRC_SEED                  0
#define CRC_XOR_MASK              0x1021
#define MAX_UINT8_VALUE           (((1UL) << CHAR_BITS) - 1)
#define HOST_BRIDGE_BUS           0
#define HOST_BRIDGE_DEVICE        0
#define HOST_BRIDGE_FUNCTION      0
#define HOST_BRIDGE_OFFSET_DEVID  0
#define HOST_BRIDGE_OFFSET_REVID  8
#define GetCrc16                  GetDimmCrc


/**
  Finds the window value for the given DQ value and if it is less than the
    current value, then save the end point values.

  @param[in, out] Rank1         - Pointer to the first rank training value (left or low).
  @param[in, out] Rank2         - Pointer to the second rank training value (right or high).
  @param[in, out] CurrentWindow - The current window value.
  @param[in]      Value1        - The first training value (left or low).
  @param[in]      Value2        - The second training value (right or high).

  @retval Nothing.
**/
void
ConvertDq2Rank (
  IN OUT UINT8        *Rank1,
  IN OUT UINT8        *Rank2,
  IN OUT UINT8        *CurrentWindow,
  IN     const UINT8  Value1,
  IN     const UINT8  Value2
  )
{
  UINT8 Window;  // The calculated window value.

  Window = MAX (Value1, Value2) - MIN (Value1, Value2);
  if (Window < *CurrentWindow) {
    *CurrentWindow  = Window;
    *Rank1          = Value1;
    *Rank2          = Value2;
  } // if
  return;
}

/**
  Initialize the memory rank margin area of the RMT_STRUCTURE.

  @param[in] MrcData - The MRC "global data".
  @param[in, out] RmtRankMargin - Pointer to the start of the rank margin information in the RMT table.
  @param[in] RmtDq         - Pointer to the start of the dq margin information in the RMT table.

  @retval Nothing.
**/
void
MrcFillRmtRankMargin (
  IN     MrcParameters              *const MrcData,
  IN OUT BDAT_RANK_MARGIN_STRUCTURE *RmtRankMargin,
  IN     BDAT_DQ_MARGIN_STRUCTURE   *RmtDq
  )
{
  BDAT_DQ_MARGIN_STRUCTURE *RmtDqMargin;         // Pointer to the current DQ margin in the RMT structure.
  UINT8                    Dq;                   // DQ number in the rank.
  UINT8                    DqEnd;
  UINT8                    SmallestWindowRxDq;   // The smallest of the Rx DQ windows.
  UINT8                    SmallestWindowTxDq;   // The smallest of the Tx DQ windows.
  UINT8                    SmallestWindowRxVref; // The smallest of the Rx Vref windows.
  UINT8                    SmallestWindowTxVref; // The smallest of the Tx Vref windows.

  SmallestWindowRxDq   = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowTxDq   = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowRxVref = (UINT8) MAX_UINT8_VALUE;
  SmallestWindowTxVref = (UINT8) MAX_UINT8_VALUE;
  DqEnd                = (MrcData->Outputs.EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  for (Dq = 0; Dq < DqEnd; Dq++) {
    RmtDqMargin = &RmtDq[Dq];
    ConvertDq2Rank (
      &RmtRankMargin->RxDqLeft,
      &RmtRankMargin->RxDqRight,
      &SmallestWindowRxDq,
      RmtDqMargin->RxDqLeft,
      RmtDqMargin->RxDqRight
      );
    ConvertDq2Rank (
      &RmtRankMargin->TxDqLeft,
      &RmtRankMargin->TxDqRight,
      &SmallestWindowTxDq,
      RmtDqMargin->TxDqLeft,
      RmtDqMargin->TxDqRight
      );
    ConvertDq2Rank (
      &RmtRankMargin->RxVrefLow,
      &RmtRankMargin->RxVrefHigh,
      &SmallestWindowRxVref,
      RmtDqMargin->RxVrefLow,
      RmtDqMargin->RxVrefHigh
      );
    ConvertDq2Rank (
      &RmtRankMargin->TxVrefLow,
      &RmtRankMargin->TxVrefHigh,
      &SmallestWindowTxVref,
      RmtDqMargin->TxVrefLow,
      RmtDqMargin->TxVrefHigh
      );
  } // Dq loop
  return;
}

/**
  Initialize the memory DQ area of the RMT_STRUCTURE.

  @param[in, out] RmtDq   - Pointer to the start of the DQ information in the RMT table.
  @param[in] Channel - Specific Channel
  @param[in] Dimm    - Specific Dimm
  @param[in] Rank    - Specific Rank
  @param[in] MrcData - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtDqMargin (
  IN OUT BDAT_DQ_MARGIN_STRUCTURE *RmtDq,
  IN     const UINT8              Controller,
  IN     const UINT8              Channel,
  IN     const UINT8              Dimm,
  IN     const UINT8              Rank,
  IN     MrcParameters            *const MrcData
  )
{
  const MrcOutput          *Outputs;
  const MrcChannelOut      *ChannelOut;
  const MrcDqTimeMargin    *RxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqTimeMargin    *TxDqMargin;      // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin    *RxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  const MrcDqVrefMargin    *TxVrefDqMargin;  // Pointer to the output portion of the MRC global data area.
  BDAT_DQ_MARGIN_STRUCTURE *RmtDqMargin;     // Pointer to the current DQ margin in the RMT structure.
  UINT8                    RankInChannel;
  UINT8                    Sdram;
  UINT8                    Dq;               // DQ number in the rank.
  UINT8                    DqEnd;
  UINT8                    Bit;

  Outputs       = &MrcData->Outputs;
  ChannelOut    = &Outputs->Controller[Controller].Channel[Channel];
  RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
  DqEnd         = (Outputs->EccSupport) ? MAX_DQ : (MAX_DQ - MAX_BITS);
  for (Dq = 0; Dq < DqEnd; Dq++) {
    Sdram                   = Dq / CHAR_BITS;
    Bit                     = Dq % CHAR_BITS;
    RxDqMargin              = &ChannelOut->RxDqPb[RankInChannel][Sdram][Bit];
    TxDqMargin              = &ChannelOut->TxDqPb[RankInChannel][Sdram][Bit];
    RxVrefDqMargin          = &ChannelOut->RxDqVrefPb[RankInChannel][Sdram][Bit];
    TxVrefDqMargin          = &ChannelOut->TxDqVrefPb[RankInChannel][Sdram][Bit];
    RmtDqMargin             = &RmtDq[Dq];
    RmtDqMargin->RxDqLeft   = RxDqMargin->Left;
    RmtDqMargin->RxDqRight  = RxDqMargin->Right;
    RmtDqMargin->TxDqLeft   = TxDqMargin->Left;
    RmtDqMargin->TxDqRight  = TxDqMargin->Right;
    RmtDqMargin->RxVrefLow  = RxVrefDqMargin->Low;
    RmtDqMargin->RxVrefHigh = RxVrefDqMargin->High;
    RmtDqMargin->TxVrefLow  = TxVrefDqMargin->Low;
    RmtDqMargin->TxVrefHigh = TxVrefDqMargin->High;
  } // Dq loop
  return;
}

/**
  Initialize the memory rank training area of the RMT_STRUCTURE.

  @param[in, out] RmtRankTraining - Pointer to the start of the rank training information in the RMT table.
  @param[in] Channel         - Specific Channel
  @param[in] Dimm            - Specific Dimm
  @param[in] Rank            - Specific Rank
  @param[in] MrcData         - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtRankTraining (
  IN OUT BDAT_RANK_TRAINING_STRUCTURE *RmtRankTraining,
  IN     const UINT8                  Controller,
  IN     const UINT8                  Channel,
  IN     const UINT8                  Dimm,
  IN     const UINT8                  Rank,
  IN     MrcParameters                *const MrcData
  )
{
  const MrcOutput     *Outputs;    // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut *ChannelOut; // Pointer to the channel portion of the MRC global data area.
  INT64               GetSetVal;
  UINT8               Index;
  UINT8               RankInChannel;
  UINT8               Sdram;
  UINT8               Strobe;
  GSM_GT              GsmGroup;

  Outputs       = &MrcData->Outputs;
  ChannelOut    = &Outputs->Controller[Controller].Channel[Channel];
  RankInChannel = (Dimm * MAX_RANK_IN_DIMM) + Rank;
  for (Strobe = 0; Strobe < MAX_STROBE; Strobe++) {
    Sdram = Strobe / 2;
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankInChannel, Sdram, RecEnDelay, ReadFromCache, &GetSetVal);
    RmtRankTraining->RecEnDelay[Strobe] = (UINT16) GetSetVal;
    RmtRankTraining->WlDelay[Strobe]    = ChannelOut->WlDelay[RankInChannel][Sdram];

    GsmGroup = (Strobe % 2) ? RxDqsNDelay : RxDqsPDelay;
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankInChannel, Sdram, GsmGroup, ReadFromCache, &GetSetVal);
    RmtRankTraining->RxDqDelay[Strobe]  = (UINT8) GetSetVal;

    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankInChannel, Sdram, TxDqDelay, ReadFromCache, &GetSetVal);
    RmtRankTraining->TxDqDelay[Strobe]  = (((UINT8) (GetSetVal)) >> 6) & 7;
  } // Strobe loop
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, RankInChannel, ClkGrpPi, ReadFromCache, &GetSetVal);
  RmtRankTraining->ClkDelay = (UINT8) GetSetVal;
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, RankInChannel, CtlGrpPi, ReadFromCache, &GetSetVal);
  RmtRankTraining->CtlDelay = (UINT8) GetSetVal;
  for (Index = 0; Index < (sizeof (RmtRankTraining->CmdDelay) / sizeof (RmtRankTraining->CmdDelay[0])); Index++) {
    RmtRankTraining->CmdDelay[Index] = TBD;  // Need to implement code.
  } // Index loop
  MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankInChannel, MRC_IGNORE_ARG, RxFlybyDelay, ReadFromCache, &GetSetVal);
  RmtRankTraining->IoLatency = (UINT8) GetSetVal;
  MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankInChannel, MRC_IGNORE_ARG, RoundTripDelay, ReadFromCache, &GetSetVal);
  RmtRankTraining->Roundtrip = (UINT8) GetSetVal;
  return;
}

/**
  Initialize the memory rank area of the RMT_STRUCTURE.

  @param[in, out] RmtRank  - Pointer to the start of the rank information in the RMT table.
  @param[in] MrcData  - The MRC "global data".
  @param[in] Channel  - Current channel number.
  @param[in] Dimm     - Current dimm number.

  @retval Nothing.
**/
void
MrcFillRmtRankStructure (
  IN OUT BDAT_RANK_STRUCTURE *RmtRank,
  IN     MrcParameters       *const MrcData,
  IN     UINT8               Controller,
  IN     UINT8               Channel,
  IN     UINT8               Dimm
  )
{
  const MrcOutput              *Outputs;          // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut          *ChannelOut;       // Pointer to the DIMM output portion of the MRC global data area.
  const MrcDimmOut             *DimmOut;          // Pointer to the DIMM output portion of the MRC global data area.
  BDAT_RANK_STRUCTURE          *RmtRankLists;     // Pointer to the current rank list in the RMT structure.
  UINT8                        Rank;              // Rank count for sequencing.
  UINT8                        RankInChannel;     // Rank number in a channel.
  UINT8                        MrIndex;           // Mode register index.
  UINT8                        Byte;              // Byte index.

  Outputs    = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
  DimmOut    = &ChannelOut->Dimm[Dimm];
  for (Rank = 0; (Rank < MAX_RANK_IN_DIMM) && (Rank < DimmOut->RankInDimm); Rank++) {
    RmtRankLists                    = &RmtRank[Rank];
    RankInChannel                   = (Dimm * MAX_RANK_IN_DIMM) + Rank;
    RmtRankLists->RankEnabled       = TRUE;
    RmtRankLists->RankMarginEnabled = TRUE;
    RmtRankLists->DqMarginEnabled   = TRUE;
    MrcFillRmtDqMargin (&RmtRankLists->DqMargin[0], Controller, Channel, Dimm, Rank, MrcData);
    MrcFillRmtRankMargin (MrcData, &RmtRankLists->RankMargin, &RmtRankLists->DqMargin[0]);
    MrcFillRmtRankTraining (&RmtRankLists->RankTraining, Controller, Channel, Dimm, Rank, MrcData);
    for (Byte = 0; Byte < MAX_DRAM_DEVICE; Byte++) {
      for (MrIndex = 0; MrIndex < MAX_MODE_REGISTER; MrIndex++) {
        RmtRankLists->RankMRS[Byte].ModeRegister[MrIndex] = DimmOut->Rank[Rank].MR[MrIndex];
      }
    }
    RmtRankLists->RankMargin.CmdLeft      = ChannelOut->Command[RankInChannel].Left;
    RmtRankLists->RankMargin.CmdRight     = ChannelOut->Command[RankInChannel].Right;
    RmtRankLists->RankMargin.CmdVrefLow   = ChannelOut->Command[RankInChannel].Low;
    RmtRankLists->RankMargin.CmdVrefHigh  = ChannelOut->Command[RankInChannel].High;
    RmtRankLists->RankMargin.RecvenLeft   = ChannelOut->ReceiveEnable[RankInChannel].Left;
    RmtRankLists->RankMargin.RecvenRight  = ChannelOut->ReceiveEnable[RankInChannel].Right;
    RmtRankLists->RankMargin.WrLevelLeft  = ChannelOut->WriteLevel[RankInChannel].Left;
    RmtRankLists->RankMargin.WrLevelRight = ChannelOut->WriteLevel[RankInChannel].Right;
  }  // Rank loop
  return;
}

/**
  Initialize the memory dimm area of the RMT_STRUCTURE.

  @param[in, out] RmtDimm - Pointer to the start of the dimm information in the RMT table.
  @param[in] MrcData - The MRC "global data".
  @param[in] Channel - Current channel number.

  @retval Nothing.
**/
void
MrcFillRmtDimmStructure (
  IN OUT BDAT_DIMM_STRUCTURE *RmtDimm,
  IN     MrcParameters       *const MrcData,
  IN     UINT8               Controller,
  IN     UINT8               Channel
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;              // Pointer to the input portion of the MRC global data area.
  const MrcDimmIn     *DimmIn;              // Pointer to the DIMM input portion of the MRC global data area.
  const MrcSpd        *SpdIn;               // Pointer to the SPD input portion of the MRC global data area.
  const MrcOutput     *Outputs;             // Pointer to the output portion of the MRC global data area.
  const MrcChannelOut *ChannelOut;          // Pointer to the channel output portion of the MRC global data area.
  const MrcDimmOut    *DimmOut;             // Pointer to the DIMM output portion of the MRC global data area.
  BDAT_DIMM_STRUCTURE *RmtDimmList;         // Pointer to the current DIMM in the RMT structure.
  BDAT_SPD_STRUCTURE  *RmtSpdList;          // Pointer to the current SPD in the RMT structure.
  UINT8               Dimm;                 // Dimm count for sequencing.

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    DimmOut = &ChannelOut->Dimm[Dimm];
    if (DimmOut->Status == DIMM_PRESENT) {
      RmtDimmList               = &RmtDimm[Dimm];
      RmtSpdList                = &RmtDimmList->SpdBytes;
      DimmIn                    = &Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm];
      SpdIn                     = &DimmIn->Spd.Data;
      RmtDimmList->DimmEnabled  = TRUE;
      MrcCall->MrcCopyMem ((UINT8 *) &RmtSpdList->SpdData[0], (UINT8 *) SpdIn, sizeof (MrcSpd));
      MrcCall->MrcSetMem ((UINT8 *) &RmtSpdList->SpdValid, sizeof (RmtDimmList->SpdBytes.SpdValid), 0xFF);

      //
      // Initialize the memory rank area of the RMT_STRUCTURE.
      //
      MrcFillRmtRankStructure (&RmtDimmList->RankList[0], MrcData, Controller, Channel, Dimm);
    } // end if
  } // Dimm loop
  return;
}

/**
  Initialize the memory channel area of the RMT_STRUCTURE.

  @param[in, out] RmtChannel - Pointer to the start of the channel information in the RMT table.
  @param[in] MrcData         - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtChannelStructure (
  IN OUT BDAT_CHANNEL_STRUCTURE *RmtChannel,
  IN     MrcParameters          *const MrcData,
  IN     const UINT8            Controller
  )
{
  const MrcOutput        *Outputs;             // Pointer to the output portion of the MRC global data area.
  BDAT_CHANNEL_STRUCTURE *RmtChannelList;      // Pointer to the current channel in the RMT structure.
  UINT8                  Channel;              // Channel count for sequencing.

  Outputs = &MrcData->Outputs;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (Outputs->Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT) {
      RmtChannelList                  = &RmtChannel[Channel];
      RmtChannelList->ChannelEnabled  = TRUE;
      RmtChannelList->NumDimmSlot     = MAX_DIMMS_IN_CHANNEL;

      //
      // Initialize the memory DIMM area of the RMT_STRUCTURE.
      //
      MrcFillRmtDimmStructure (&RmtChannelList->DimmList[0], MrcData, Controller, Channel);
    } // end if
  } // Channel loop
  return;
}

/**
  Initialize the memory controller area of the RMT_STRUCTURE.

  @param[in, out] RmtController - Pointer to the start of the controller information in the RMT table.
  @param[in] MrcData            - The MRC "global data".

  @retval Nothing.
**/
void
MrcFillRmtControllerStructure (
  IN OUT BDAT_SOCKET_STRUCTURE *RmtController,
  IN     MrcParameters         *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcOutput       *Outputs;
  BDAT_SOCKET_STRUCTURE *RmtControllerList;
  UINT8                 Controller;
  MrcVddSelect          VddVoltage;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  VddVoltage = Outputs->VddVoltage[Inputs->MemoryProfile];
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (Outputs->Controller[Controller].Status == CONTROLLER_PRESENT) {
      RmtControllerList                       = &RmtController[Controller];
      RmtControllerList->ControllerEnabled    = TRUE;
      RmtControllerList->ControllerDeviceId   = Outputs->Controller[Controller].DeviceId;
      RmtControllerList->ControllerRevisionId = Outputs->Controller[Controller].RevisionId;
      RmtControllerList->MemoryFrequency      = (UINT16) (Outputs->Frequency / 10);
      RmtControllerList->MemoryVoltage        = (UINT16) VddVoltage;
      //
      // Step unit = piStep * (tCK / 2048)
      //
      RmtControllerList->PiStep               = (UINT8) PI_STEP;
      RmtControllerList->RecvenStep           = (UINT8) PI_STEP;
      RmtControllerList->WrLevelStep          = (UINT8) PI_STEP;
      if (VddVoltage > 0) {
        //
        // Step unit = __VrefStep * Vdd / 100
        //
        RmtControllerList->RxVrefStep  = (UINT16) RX_VREF (VddVoltage);
        RmtControllerList->TxVrefStep  = (UINT16) TX_VREF (VddVoltage);
        RmtControllerList->CaVrefStep  = (UINT16) CA_VREF (VddVoltage);
      } else {
        RmtControllerList->RxVrefStep  = 0;
        RmtControllerList->TxVrefStep  = 0;
        RmtControllerList->CaVrefStep  = 0;
      }
      //
      // Initialize the memory channel area of the RMT_STRUCTURE.
      //
      MrcFillRmtChannelStructure (&RmtControllerList->ChannelList[0], MrcData, Controller);
    } // Controller loop
  }

  return;
}

/**
@brief
  Fill the compatible data structure RMT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData      - Constant pointer to the Mrc data structure.
  @param[in, out] MemorySchema - The memory schema to fill.

  @retval Nothing.
**/
MrcStatus
MrcBuildMemorySchema (
  IN OUT MrcParameters              *const MrcData,
  IN OUT BDAT_MEMORY_DATA_STRUCTURE *MemorySchema
  )
{
  static const BDAT_EFI_GUID MemoryGuid = BDAT_MEMORY_DATA_GUID;
  const MrcOutput    *Outputs;
  const MRC_FUNCTION *MrcCall;
  UINT16             NextSchema;

  //
  // Initialize the system area of the RMT_STRUCTURE.
  //
  MrcCall                                        = MrcData->Inputs.Call.Func;
  Outputs                                        = &MrcData->Outputs;
  MemorySchema->RefCodeRevision.Version.Major    = Outputs->Version.Major;
  MemorySchema->RefCodeRevision.Version.Minor    = Outputs->Version.Minor;
  MemorySchema->RefCodeRevision.Version.Revision = Outputs->Version.Rev;
  MemorySchema->RefCodeRevision.Version.Build    = Outputs->Version.Build;
  MemorySchema->MaxController                    = MAX_CONTROLLER;
  MemorySchema->MaxChannel                       = MAX_CHANNEL;
  MemorySchema->MaxDimm                          = MAX_DIMMS_IN_CHANNEL;
  MemorySchema->MaxRankDimm                      = MAX_RANK_IN_DIMM;
  MemorySchema->MaxStrobe                        = MAX_STROBE;
  MemorySchema->MaxDq                            = MAX_DQ;
  MemorySchema->MarginLoopCount                  = Outputs->DQPatLC;
  //
  // Initialize the memory controller area of the RMT_STRUCTURE.
  //
  MrcFillRmtControllerStructure (&MemorySchema->ControllerList[0], MrcData);

  //
  // Initialize the header area of the RMT_STRUCTURE.
  // Ensure that the CRC calculation is the last field initialized.
  //
  if (Outputs->BdatSchemasHob.Pointer != NULL) {
    NextSchema = Outputs->BdatSchemasHob.Pointer->SchemaHobCount;
    Outputs->BdatSchemasHob.Pointer->SchemaHobCount = NextSchema + 1;
    MrcCall->MrcCopyMem ((UINT8 *) &MemorySchema->SchemaHeader.SchemaId, (UINT8 *) &MemoryGuid, sizeof (BDAT_EFI_GUID));
    MrcCall->MrcCopyMem ((UINT8 *) &(Outputs->BdatSchemasHob.Pointer->SchemaHobGuids[NextSchema]), (UINT8 *) &MemoryGuid, sizeof (BDAT_EFI_GUID));
    MemorySchema->SchemaHeader.DataSize = sizeof (BDAT_MEMORY_DATA_STRUCTURE);
    GetCrc16 ((const UINT8 *const) MemorySchema, sizeof (BDAT_MEMORY_DATA_STRUCTURE), &MemorySchema->SchemaHeader.Crc16);
  } else {
    return mrcFail;
  }

  return mrcSuccess;
}

/**
@brief
  Fill the compatible data structure RMT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData - Constant pointer to the Mrc data structure which conatins the Rmt structure to fill.

  @retval Nothing.
**/
MrcStatus
MrcFillRmtStructure (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput       *Inputs;
  MrcOutput            *Outputs;
  MrcDebug             *Debug;
  BDAT_MEMORY_DATA_HOB *BdatMemoryHob;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Inputs        = &MrcData->Inputs;
  BdatMemoryHob = Outputs->BdatMemoryHob[0].Pointer;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Inputs->RmtBdatEnable %d\n", (UINT32) (Inputs->RmtBdatEnable));
  if ((Inputs->RmtBdatEnable) && (BdatMemoryHob != NULL)) {
    //
    // Initialize the memory data schema.
    //
    MrcBuildMemorySchema (MrcData, &BdatMemoryHob->MemorySchema);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "BdatMemoryHob->MemorySchema %Xh\n", (UINT32) (&BdatMemoryHob->MemorySchema));
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "BdatMemoryHob->HobGuidType.Header.HobLength %Xh\n",
      (UINT32) (BdatMemoryHob->HobGuidType.Header.HobLength)
      );
//    MrcWriteCR (MrcData, SCRATCHPAD_NCU_2_REG_A0, (UINT32) &(BdatMemoryHob->MemorySchema));
    // @todo: <ICL> Need solution
  }
  return mrcSuccess;
}
#endif // BDAT_SUPPORT
