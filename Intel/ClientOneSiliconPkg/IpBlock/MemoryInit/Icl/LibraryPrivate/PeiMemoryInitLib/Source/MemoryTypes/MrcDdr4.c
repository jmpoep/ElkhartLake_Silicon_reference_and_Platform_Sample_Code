/** @file
Implementation of DDR4 Specific functions, and constants.

@copyright
INTEL CONFIDENTIAL
Copyright 2017 - 2019 Intel Corporation.

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
JEDEC
**/

#include "MrcDdr4.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcDdrCommon.h"
#include "MrcMcOffsets.h"
#include "MrcMemoryApi.h"
#include "MrcTimingConfiguration.h"

//--------------- DDR4 -----------------------------------------
// DDR4 ODT values are in this order: { RttWr, RttNom, RttPark }
// Note: RttWr   0xFFFF denots Hi-Z
//               0      denotes disabled
//
//       RttPark, RttNom may be disabled by setting 0, there is no Hi-Z value.

//
// Only 1DPC is supported on ULT/ULX
//
GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 MbDdr4OdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,    1DPC 2R
  {{80,0,0},  {80,0,0}},
};

GLOBAL_REMOVE_IF_UNREFERENCED const TOdtValueDdr4 DtDdr4OdtTable[MAX_DIMMS_IN_CHANNEL][oiNotValid] = {
/// 1DPC 1R,     1DPC 2R,     2DPC 1R 1R,    2DPC 1R 2R,      2DPC 2R 1R,      2DPC 2R 2R
  {{80,0,240},  {80,0,240},  {240,48,0},    {240,40,240},    {240,48,120},    {240,120,60}}, // DIMM 0
  {{80,0,240},  {80,0,240},  {240,48,0},    {240,48,240},    {240,40,120},    {240,120,60}}  // DIMM 1
};

/**
  Used to update TxVref for DDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     Channel       - Selecting which Channel to talk to.
  @param[in]     RankMask      - Selecting which Ranks to talk to.
  @param[in]     DeviceMask    - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     VrefType      - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset        - Vref offset value.
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated.
  @param[in]     PdaMode       - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise
**/
MrcStatus
Ddr4SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode,
  IN     BOOLEAN              IsCachedOffsetParam
  )
{
  MrcDebug                     *Debug;
  MrcOutput                    *Outputs;
  MrcChannelOut                *ChannelOut;
  MrcRankOut                   *RankOut;
  UINT16                       *MrPtr;
  UINT16                       OdtWrite;
  UINT8                        VrefCode;
  UINT8                        Rank;
  UINT8                        RankHalf;
  UINT8                        RankMod2;
  UINT8                        Device;
  UINT8                        DeviceCount;
  UINT8                        MrIndex;
  INT32                        CurrentOffset;
  MrcStatus                    Status;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Outputs     = &MrcData->Outputs;
  Status      = mrcSuccess;
  MrIndex     = 0;
  VrefCode    = 0;

  switch (VrefType) {
    case WrV:
        MrIndex = mrMR6;
        break;

      default:
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, VrefType);
        return mrcWrongInputParameter;
  }

  DeviceCount = (PdaMode) ? Outputs->SdramCount : 1;
  DeviceMask  = (PdaMode) ? DeviceMask : 1;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((MrcRankInChannelExist(MrcData, Rank, Channel)) && (RankMask & (1 << Rank))) {
      RankHalf = Rank / 2;
      RankMod2 = Rank % 2;
      RankOut  = &ChannelOut->Dimm[RankHalf].Rank[RankMod2];
      MrPtr    = RankOut->MR;
      if (PdaMode) {
        // Dynamic Odt not supported in PDA - Park <- RttWr for target rank
        OdtWrite = CalcDimmImpedance(MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0, FALSE);
        if (OdtWrite == 0xFFFF) {
          // for setting park to off
          OdtWrite = 0;
        }
        SetDimmParamValue(MrcData, Channel, 1 << Rank, 0, OptDimmOdtPark, OdtWrite, FALSE);
      }
      // Send MR6 sequence using MRH, this is done for each device in PDA mode.
      // MRH will go in/out of PDA mode automatically.
      for (Device = 0; Device < DeviceCount; Device++) {
        if (DeviceMask & (1 << Device)) {

          if (IsCachedOffsetParam) {
            // Offset value -  calculate the new Vref
            if (PdaMode) {
              VrefCode = (UINT8) (RankOut->Ddr4PdaMr6[Device] & 0x7F);
            } else {
              VrefCode = (UINT8) (MrPtr[MrIndex] & 0x7F);
            }
            CurrentOffset = MrcVrefDqToOffsetDdr4(VrefCode);
            CurrentOffset += Offset;
          } else {
            // If IsCachedOffsetParam
            CurrentOffset = Offset;
          }
          MrcSetTxVrefDdr4 (MrcData, Channel, Rank, Device, CurrentOffset, UpdateMrcData, PdaMode);
        }
      }
      if (PdaMode) {
        // Restore RTT_PARK for this rank
        MrcWriteMRS (MrcData, Channel, 1 << Rank, mrMR5, RankOut->MR[mrMR5]);
      }
    }
  }

  return Status;
}

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

  @retval none
**/
void
MrcSetTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                Rank,
  IN     UINT8                Device,
  IN     INT32                TxVrefOffset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode
  )
{
#if (defined (MRC_MEMORY_API_DEBUG) && (MRC_MEMORY_API_DEBUG == SUPPORT))
  MrcDebug                          *Debug;
#endif
  MrcChannelOut                     *ChannelOut;
  MrcOutput                         *Outputs;
  MrcRankOut                        *RankOut;
  DDR4_MODE_REGISTER_6_STRUCT       Ddr4Mr6;
  UINT8                             Mr6Loop;
  UINT8                             VrefDq;
  UINT8                             ByteLoop;

  Outputs    = &MrcData->Outputs;
#if (defined (MRC_MEMORY_API_DEBUG) && (MRC_MEMORY_API_DEBUG == SUPPORT))
  Debug      = &Outputs->Debug;
#endif
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  RankOut    = &ChannelOut->Dimm[(Rank / 2) % MAX_DIMMS_IN_CHANNEL].Rank[Rank % 2];
  Ddr4Mr6.Data = RankOut->MR[mrMR6];

  VrefDq = MrcOffsetToVrefDqDdr4 (MrcData, TxVrefOffset);
  Ddr4Mr6.Bits.VrefDqTrainingEnable = 1;
  Ddr4Mr6.Bits.VrefDqTrainingRange  = VrefDq >> 6;
  Ddr4Mr6.Bits.VrefDqTrainingValue  = VrefDq & 0x3F;

  for (Mr6Loop = 0; Mr6Loop < 3; Mr6Loop++) {
    if (Mr6Loop == 2) {
      Ddr4Mr6.Bits.VrefDqTrainingEnable = 0;
    }
    if (PdaMode) {
      MRC_API_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PDAmode, Device%d, ", Device);
      MrcDdr4PdaCmd (MrcData, Channel, Rank, Ddr4Mr6.Data, mrMR6, (1 << Device));
    } else {
      MrcWriteMRS (MrcData, Channel, 1 << Rank, mrMR6, Ddr4Mr6.Data);
    }
    MRC_API_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Channel%d, Rank%d, Requested Offset %d, VrefCode 0x%X, Range %d\n", Channel, Rank, TxVrefOffset, Ddr4Mr6.Data);
    MrcWait (MrcData, (tVREF_DQ_PS * MRC_TIMER_1NS) / 1000);
  }
  if (UpdateMrcData) {
    if (PdaMode) {
      RankOut->Ddr4PdaMr6[Device] = Ddr4Mr6.Data8[0];
    }  else {
      RankOut->MR[mrMR6] = Ddr4Mr6.Data;
      // Update the per byte Vref in case needed later
      for (ByteLoop = 0; ByteLoop < Outputs->SdramCount; ByteLoop++) {
        RankOut->Ddr4PdaMr6[ByteLoop] = Ddr4Mr6.Data8[0];
      }
    }
  }
}

/**
  This function Update the Non PDA DDR4 Vref to match the PDA average
  across all bytes (per rank/ch).
  This will allow the use of Non PDA sweep using GetBerMarginByte

  @param[in]     MrcData         - Include all MRC global data.
  @param[in]     RankMask        - ranks to work on

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
UpdatePdaCenter (
  IN     MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcRankOut    *RankOut;
  UINT8         Rank;
  UINT8         Byte;
  UINT8         VrefDq;
  INT32         ByteCenterAvg;
  DDR4_MODE_REGISTER_6_STRUCT Ddr4Mr6;

  Outputs = &MrcData->Outputs;

  if (MrcChannelExist(Outputs, Channel)) {
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist(MrcData, Rank, Channel)) {
        continue;
      }
      if ((1 << Rank) & RankMask) {
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER(Rank)].Rank[Rank % 2];
        ByteCenterAvg = 0;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          ByteCenterAvg += MrcVrefDqToOffsetDdr4(RankOut->Ddr4PdaMr6[Byte] & 0x7F);
        }
        ByteCenterAvg /= Outputs->SdramCount;
        VrefDq = MrcOffsetToVrefDqDdr4(MrcData, ByteCenterAvg);
        Ddr4Mr6.Data = RankOut->MR[mrMR6];
        Ddr4Mr6.Bits.VrefDqTrainingRange = VrefDq >> 6;
        Ddr4Mr6.Bits.VrefDqTrainingValue = VrefDq & 0x3F;
        RankOut->MR[mrMR6] = Ddr4Mr6.Data;
      }
    }
  }

  return mrcSuccess;
}



/**
  DDR4 get available values and the number of possible values of a given DimmOptParam.
  The order of the values returns corresponds to the ascending field values in the MRs as defind by JEDEC

  @param[in]      MrcData               - Include all MRC global data.
  @param[in]      DimmOptParam          - e.g., OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon
  @param[out]     **DimmOptParamVals    - Reference to the pointer of values.
  @param[out]     *NumDimmOptParamVals  - Reference to the number of values.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam, mrcSuccess otherwise
**/
MrcStatus
Ddr4GetDimmOptParamValues (
  IN MrcParameters *const MrcData,
  IN UINT8                DimmOptParam,
  OUT UINT16              **DimmOptParamVals,
  OUT UINT8               *NumDimmOptParamVals
  )
{
  static const UINT16    Ddr4DimmRttWrVals[]      = { 0, 120, 80 };         // DDR4 RttWr Values in Ohms, not included  240, 0xFFFF
  static const UINT16    Ddr4DimmRttNomParkVals[] = { 0, 60, 120, 40, 240, 48, 80, 34 }; // DDR4 RttNom / RttPark Values in Ohms
  static const UINT16    Ddr4DimmRonVals[]        = { 48, 34 };                          // DDR4 Ron (Drive Strength) in Ohms
  MrcDebug               *Debug;
  MrcStatus              Status;

  Debug = &MrcData->Outputs.Debug;
  Status = mrcSuccess;


  switch (DimmOptParam) {
    case OptDimmOdtWr:
      // DIMM RTT_WR
      *DimmOptParamVals    =    (UINT16 *) Ddr4DimmRttWrVals;
      *NumDimmOptParamVals = ARRAY_COUNT (Ddr4DimmRttWrVals);
      break;

      case OptDimmOdtNom:
      case OptDimmOdtPark:
      case OptDimmOdtNomNT:
      case OptDimmOdtParkNT:
        // DIMM RTT_NOM / RTT_PARK
        *DimmOptParamVals    =    (UINT16 *) Ddr4DimmRttNomParkVals;
        *NumDimmOptParamVals = ARRAY_COUNT (Ddr4DimmRttNomParkVals);
        break;

      case OptDimmRon:
        // DIMM RON
        *DimmOptParamVals    =    (UINT16 *) Ddr4DimmRonVals;
        *NumDimmOptParamVals = ARRAY_COUNT (Ddr4DimmRonVals);
        break;

    default:
      *DimmOptParamVals    = (UINT16 *)NULL;
      *NumDimmOptParamVals = 0;
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, DimmOptParam);
      break;
  }

  return Status;

}

/**
  Ddr4 Get the MR value and its corresponding index for a given DIMM Opt Param.
  Value is set by reference to the corresponding pointers.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      OptParam    - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out]     *MrIndex    - Updated Pointer to the MR index.
  @param[out]     *MrNum      - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam, mrcSuccess otherwise
**/
MrcStatus
Ddr4GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;

  Status = mrcSuccess;
  Debug = &MrcData->Outputs.Debug;

  switch (OptDimmParam) {
      // DIMM RON
    case OptDimmRon:
      *MrIndex = mrIndexMR1;
      *MrNum   = mrMR1;
      break;

    case OptDimmOdtWr:
      // DIMM RTT WR
      *MrIndex = mrIndexMR2;
      *MrNum  = mrMR2;
      break;

    case OptDimmOdtPark:
    case OptDimmOdtParkNT:
      // DIMM RTT PARK
      *MrIndex = mrIndexMR5;
      *MrNum = mrMR5;
      break;

    case OptDimmOdtNom:
    case OptDimmOdtNomNT:
      // DIMM RTT PARK
      *MrIndex = mrIndexMR1;
      *MrNum = mrMR1;
      break;

    default:
      // Unsupported paramter
      *MrIndex = 0xFF;
      *MrNum  = 0xFF;
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, OptDimmParam);
      break;
  }

  return Status;
}

/**
  Ddr4 Set DimmParamValue is responsible for performing the concrete set DIMM paramter to value, using
  Per-Technology MR set functions.
  @param[in,out]  MrcData         - Include all MRC global data.
  @param[in,out]  MrData          - Pointer to the MR data to update.
  @param[in]      OptParam        - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[in]      ParamValue      - The actual values (Typically in Ohms)

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                    - MrcStatus of the MR set functions otherwise

**/
MrcStatus
Ddr4SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16        *const MrData,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue
  )
{
  MrcDebug        *Debug;
  MrcStatus       Status;
  DDR4_MODE_REGISTER_1_STRUCT Mr1;
  DDR4_MODE_REGISTER_2_STRUCT Mr2;
  DDR4_MODE_REGISTER_5_STRUCT Mr5;

  Debug = &MrcData->Outputs.Debug;
  Status = mrcSuccess;

  switch (OptParam) {
    case OptDimmRon:
      // DIMM RON
      Mr1.Data = *MrData;
      Mr1 = UpdateOdicValue_DDR4 (MrcData, ParamValue, Mr1);
      *MrData = Mr1.Data;
      break;

    case OptDimmOdtWr:
      // DIMM RTT WR
      Mr2.Data = *MrData;
      Mr2 = UpdateRttWrValue_DDR4 (MrcData, ParamValue, Mr2);
      *MrData = Mr2.Data;
      break;

    case OptDimmOdtNom:
    case OptDimmOdtNomNT:
      // DIMM RTT NOM
      Mr1.Data = *MrData;
      Mr1 = UpdateRttNomValue_DDR4 (MrcData, ParamValue, Mr1);
      *MrData = Mr1.Data;
      break;

    case OptDimmOdtPark:
    case OptDimmOdtParkNT:
      // DIMM RTT PARK
      Mr5.Data = *MrData;
      Mr5 = UpdateRttParkValue_DDR4 (MrcData, ParamValue, Mr5);
      *MrData = Mr5.Data;
      break;

    default:
      // Unsupported paramter
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, OptParam);
      break;
  }

  return Status;
}

/**
  Offset to DDR4 VrefDQ Range/Value (MR6)

  @param[in]  MrcData  - Include all MRC global data.
  @param[in]  Offset   - Value to be converted to actual VrefDQ Range/Value.

  @retval DDR4 VrefDQ Range/Value
**/
UINT8
MrcOffsetToVrefDqDdr4 (
  IN MrcParameters *const MrcData,
  IN INT32                Offset
  )
{
  INT32 VrefDQ;  //Bit6 Range, Bit5:0 Value

  if ((Offset > MAX_POSSIBLE_DDR4_WRITE_VREF) || (Offset < (-1 * (MAX_POSSIBLE_DDR4_WRITE_VREF + 1)))) {
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "%s Invalid Vref Setting %d is out of range [%d:%d]. Clamping\n",
      gErrString, Offset, (-1 * MAX_POSSIBLE_DDR4_WRITE_VREF) - 1, MAX_POSSIBLE_DDR4_WRITE_VREF);
    if (Offset > MAX_POSSIBLE_DDR4_WRITE_VREF) {
      Offset = MAX_POSSIBLE_DDR4_WRITE_VREF;
    } else {
      Offset = (-1 * (MAX_POSSIBLE_DDR4_WRITE_VREF + 1));
    }
  }
  Offset += 13;


  if (Offset < 0) {
    VrefDQ = Offset - 41;
  } else {
    VrefDQ = Offset;
  }

  return (UINT8) (VrefDQ & 0x7F);
}

/**
  DDR4 VrefDQ Range/Value (MR6) to Offset

  @param[in]  VrefDQ   - VrefDQ Range/Value to be converted back to corresponding Offset value.

  @retval Offset
**/
INT32
MrcVrefDqToOffsetDdr4 (
  IN UINT8                VrefDQ
  )
{
  INT8  Offset;

  // move to -23 to 50 range
  Offset = (INT8) MrcSE (VrefDQ, 7, 8);
  if (Offset < 0) {
    Offset = Offset + 41;
  }
  if (Offset > 50) {
    Offset = 50;
  } else if (Offset < -23) {
    Offset = -23;
  }
  Offset -= 13; // so offset 0 is middle of range -36 +37

  return (INT32) Offset;
}
/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR0_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          BurstLength,
  IN     const UINT8          ReadBurstType,
  IN     const UINT8          TestMode,
  IN     const UINT8          DllReset
  )
{
  /*
   CAS Latency
  A12 A6 A5 A4 A2 CAS Latency
  0   0  0  0  0   9
  0   0  0  0  1  10
  0   0  0  1  0  11
  0   0  0  1  1  12
  0   0  1  0  0  13
  0   0  1  0  1  14
  0   0  1  1  0  15
  0   0  1  1  1  16
  0   1  0  0  0  18
  0   1  0  0  1  20
  0   1  0  1  0  22
  0   1  0  1  1  24
  0   1  1  0  0  23
  0   1  1  0  1  17
  0   1  1  1  0  19
  0   1  1  1  1  21
  1   0  0  0  0  25
  1   0  0  0  1  26
  1   0  0  1  0  27
  1   0  0  1  1  28
  1   0  1  0  0  29
  1   0  1  0  1  30
  1   0  1  1  0  31
  1   0  1  1  1  32
  1   1  0  0  0  Reserved

  Write recovery and Read to Precharge
  A13 A11 A10 A9 WR(cycles) RTP(cycles)
  0   0   0   0  10          5
  0   0   0   1  12          6
  0   0   1   0  14          7
  0   0   1   1  16          8
  0   1   0   0  18          9
  0   1   0   1  20          10
  0   1   1   0  24          12
  0   1   1   1  22          11
  1   0   0   0  26          13
  1   0   0   1  Reserved    Reserved
  1   0   1   0  Reserved    Reserved
  1   0   1   1  Reserved    Reserved
  1   1   0   0  Reserved    Reserved
  1   1   0   1  Reserved    Reserved
  1   1   1   0  Reserved    Reserved
  1   1   1   1  Reserved    Reserved
*/
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  BOOLEAN                     CasFound;
  UINT32                      Index;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT16                      Cas;
  UINT16                      Wr;
  UINT16                      Rtp;
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  MrcProfile                  Profile;
  DDR4_MODE_REGISTER_0_STRUCT Ddr4ModeRegister;
  static const UINT8           CasMapping[] = { 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 22, 24, 23, 17, 19, 21, 25, 26, 27, 28, 29, 30, 31, 32 };

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Profile       = Inputs->MemoryProfile;
  Status        = mrcSuccess;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut  = &ControllerOut->Channel[Channel];

      Ddr4ModeRegister.Data               = 0;
      Ddr4ModeRegister.Bits.BurstLength   = MIN (BurstLength,   DDR4_MODE_REGISTER_0_BL_MAX);
      Ddr4ModeRegister.Bits.ReadBurstType = MIN (ReadBurstType, DDR4_MODE_REGISTER_0_RBT_MAX);
      Ddr4ModeRegister.Bits.TestMode      = MIN (TestMode,      DDR4_MODE_REGISTER_0_TM_MAX);
      Ddr4ModeRegister.Bits.DllReset      = MIN (DllReset,      DDR4_MODE_REGISTER_0_DLL_MAX);

      Cas         = ChannelOut->Timing[Profile].tCL;
      Wr          = ChannelOut->Timing[Profile].tWR;
      Rtp         = ChannelOut->Timing[Profile].tRTP;

      // Check tWR and tRTP against the spec.
      if ((Rtp < 5) || (Rtp > 13)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Read to Precharge (RTP) value %d is invalid\n", gErrString, Rtp);
        return mrcRtpError;
      }

      if (Rtp * 2 != Wr) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Write recovery (WR) value should be twice the Read to Precharge (RTP) value %d\n", gErrString, Wr, Rtp);
        return mrcWrError;
      }
      // If we pass the two checks above, both RTP and WR are within valid JEDEC ranges:
      // RTP = 5, 6, 7, .. 13
      // WR  = 10, 12, 14, .. 26

      // Convert CAS to jedec ddr4 MR0 encoding, this also checks that tCL is a valid value by the spec.
      CasFound = FALSE;
      for (Index = 0; Index < ARRAY_COUNT (CasMapping); Index++) {
        if ((Cas == CasMapping[Index]) && (Cas != 0)) {
          Ddr4ModeRegister.Bits.CasLatencyLow  = Index & 1;           // MR0[A2]
          Ddr4ModeRegister.Bits.CasLatencyMid  = (Index & 0x0E) >> 1; // MR0[A6:A4]
          Ddr4ModeRegister.Bits.CasLatencyHigh = (Index & 0x10) >> 4; // MR0[A12]
          CasFound = TRUE;
          break;
        }
      }
      if (!CasFound) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s CAS value %d is not valid \n", gErrString, Cas);
        return mrcCasError;
      }

      // convert Wr/RTP to jedec ddr4 values
      Ddr4ModeRegister.Bits.WriteRecoveryAndRTPMsb = 0;
      if (Wr <= 20) {
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP = (Wr - 10) / 2;
      } else if (Wr == 22) {
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP = 7;
      } else if (Wr == 24) {
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP = 6;
      } else { // 26
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTP    = 0;
        Ddr4ModeRegister.Bits.WriteRecoveryAndRTPMsb = 1;
      }

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR0];
          } else {
            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR0] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR0] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 0, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          // Update proper DIMM value
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR0, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance in Ohms
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR1_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Qoff
  )
{
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  TOdtValueDdr4               *OdtTableIndex;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  OdtTableIndex = NULL;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];

      Ddr4ModeRegister.Data                 = 0;
      Ddr4ModeRegister.Bits.DllEnable       = DLLEnable;
      Ddr4ModeRegister.Bits.AdditiveLatency = AdditiveLatency;
      Ddr4ModeRegister.Bits.WriteLeveling   = WlEnable;
      Ddr4ModeRegister.Bits.Qoff            = Qoff;
      Ddr4ModeRegister = UpdateOdicValue_DDR4 (MrcData, Odic, Ddr4ModeRegister);

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR1];
          } else {
            // Get the ODT table index.
            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
            if (OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Cannot find ODT table for C%d Dimm%d\n", gErrString, Channel, Dimm);
              return mrcFail;
            }
            // Set the RttNom value
            Ddr4ModeRegister = UpdateRttNomValue_DDR4 (MrcData, OdtTableIndex->RttNom, Ddr4ModeRegister);
            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR1] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR1] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 1, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          // Update proper DIMM value
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      //
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      //
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR1, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      WriteCRC   - Write CRC Enable bit (A12)

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR2_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          WriteCRC
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  TOdtValueDdr4     *OdtTableIndex;
  UINT8             Channel;
  UINT8             Dimm;
  UINT8             JedecCwlValue;
  UINT16            DimmValue[MAX_DIMMS_IN_CHANNEL];
  MrcStatus         Status;
  MrcProfile        Profile;
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Profile       = Inputs->MemoryProfile;
  Status        = mrcSuccess;

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut                            = &ControllerOut->Channel[Channel];
      Ddr4ModeRegister.Data                 = 0;
      Ddr4ModeRegister.Bits.WriteCrc        = WriteCRC;

      if (ChannelOut->Timing[Profile].tCWL <= 12) {
        // Subtract 9 because of jedec mr2 CWL table 0 = 9 1=10 2=11 3=12
        JedecCwlValue = (UINT8) (ChannelOut->Timing[Profile].tCWL - 9);
      } else {
        JedecCwlValue = (UINT8) ((ChannelOut->Timing[Profile].tCWL - 14) / 2);
        JedecCwlValue |= MRC_BIT2;  //corresponds to MR2[A5] bit
      }
      Ddr4ModeRegister.Bits.CasWriteLatency = JedecCwlValue;

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR2];
          } else {
            // LP ASR: 00b = Manual Normal (0-85C), 01b = Manual Reduced (0-45C), 10b = Manual Extended (0-95C), 11b = Auto
            Ddr4ModeRegister.Bits.LowPowerArraySelfRefresh = 3;

            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
            if (OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Cannot find ODT table for C%d Dimm%d\n", gErrString, Channel, Dimm);
              return mrcFail;
            }
            Ddr4ModeRegister = UpdateRttWrValue_DDR4 (MrcData, OdtTableIndex->RttWr, Ddr4ModeRegister);

            // Must be before the MRC command because of address swizzling bits in SODIMM/UDIMM
            SetTcMr2ShadowReg (MrcData, Channel, Dimm, Ddr4ModeRegister.Data);

            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR2] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR2] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 2, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          // Update proper DIMM value
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR2, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MprPage         - MPR Page Selection bit A0-A1
  @param[in] MprOper         - MPR Operation bit A2
  @param[in] MprReadFormat   - MPR Read Format bit A11-A12
  @param[in] Geardown        - Geardown Mode bit A3
  @param[in] PDA             - Per DRAM Addressability bit A4
  @param[in] TempSensor      - Temperature Sensor Readout bit A5
  @param[in] RefreshRate     - Fine Granularity Refresh Mode bit A6-A8
  @param[in] WriteCMDLatency - Write CMD Latency when DM are enabled bit A9-A10

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR3_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MprPage,
  IN const UINT8          MprOper,
  IN const UINT8          MprReadFormat,
  IN const UINT8          Geardown,
  IN const UINT8          PDA,
  IN const UINT8          TempSensor,
  IN const UINT8          RefreshRate,
  IN const UINT8          WriteCMDLatency
  )
{
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_3_STRUCT Ddr4ModeRegister;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  Ddr4ModeRegister.Data                       = 0;
  Ddr4ModeRegister.Bits.MprPageSelection      = MIN (MprPage, DDR4_MODE_REGISTER_3_MPR_PAGE_MAX);
  Ddr4ModeRegister.Bits.MprOperation          = MIN (MprOper, DDR4_MODE_REGISTER_3_MPR_MAX);
  Ddr4ModeRegister.Bits.MprReadFormat         = MIN (MprReadFormat, DDR4_MODE_REGISTER_3_MPR_READ_MAX);
  Ddr4ModeRegister.Bits.GeardownMode          = MIN (Geardown, DDR4_MODE_REGISTER_3_GM_MAX);
  Ddr4ModeRegister.Bits.PerDramAddressability = MIN (PDA, DDR4_MODE_REGISTER_3_PDA_MAX);
  Ddr4ModeRegister.Bits.TempSensorReadout     = MIN (TempSensor, DDR4_MODE_REGISTER_3_TSR_MAX);
  Ddr4ModeRegister.Bits.RefreshRateMode       = MIN (RefreshRate, DDR4_MODE_REGISTER_3_FGRM_MAX);
  Ddr4ModeRegister.Bits.WriteCmdLatency       = MIN (WriteCMDLatency, DDR4_MODE_REGISTER_3_WCMDL_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR3];
          } else {
            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR3] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR3] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 3, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR3, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR4 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MaxPDMode       - Maximum Power Down Mode bit A1
  @param[in] TempRange       - Temperature Controlled Refresh Range bit A2
  @param[in] TempMode        - Temperature Controlled Refresh Mode bit A3
  @param[in] IntVref         - Internal Vref Monitor bit A4
  @param[in] CS2CALatency    - CS to CMD/ADDR Latency Mode (cycles) bit A6-A8
  @param[in] SelfRefAbort    - Self Refresh Abort bit A9
  @param[in] RdPreaMode      - Read Preamble Training Mode bit A10
  @param[in] RdPrea          - Read Preamble bit A11
  @param[in] WrPrea          - Write Preamble bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR4_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MaxPDMode,
  IN const UINT8          TempRange,
  IN const UINT8          TempMode,
  IN const UINT8          IntVref,
  IN const UINT8          CS2CALatency,
  IN const UINT8          SelfRefAbort,
  IN const UINT8          RdPreaMode,
  IN const UINT8          RdPrea,
  IN const UINT8          WrPrea
  )
{
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_4_STRUCT Ddr4ModeRegister;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  Ddr4ModeRegister.Data                          = 0;
  Ddr4ModeRegister.Bits.MaxPowerDownMode         = MIN (MaxPDMode, DDR4_MODE_REGISTER_4_MAX_PD_MAX);
  Ddr4ModeRegister.Bits.TempRefreshRange         = MIN (TempRange, DDR4_MODE_REGISTER_4_TCRR_MAX);

  // MR4[2] = 0 (Temperature Controlled Refresh Range = Normal)
  // MR4[3] = 1 (Temperature Controlled Refresh Mode = Enabled)
  if ((Outputs->TCRSensitiveHynixDDR4) || (Outputs->TCRSensitiveMicronDDR4)) {
    Ddr4ModeRegister.Bits.TempRefreshMode          = 0;
  } else {
    Ddr4ModeRegister.Bits.TempRefreshMode          = 1;
  }
  Ddr4ModeRegister.Bits.InternalVrefMonitor      = MIN (IntVref, DDR4_MODE_REGISTER_4_IVM_MAX);
  Ddr4ModeRegister.Bits.CstoCmd_AddrLatencyMode  = MIN (CS2CALatency, DDR4_MODE_REGISTER_4_C_CA_LAT_MAX);
  Ddr4ModeRegister.Bits.SelfRefreshAbort         = MIN (SelfRefAbort, DDR4_MODE_REGISTER_4_SRA_MAX);
  Ddr4ModeRegister.Bits.ReadPreambleTrainingMode = MIN (RdPreaMode, DDR4_MODE_REGISTER_4_R_PRE_TM_MAX);
  Ddr4ModeRegister.Bits.ReadPreamble             = MIN (RdPrea, DDR4_MODE_REGISTER_4_R_PRE_MAX);
  Ddr4ModeRegister.Bits.WritePreamble            = MIN (WrPrea, DDR4_MODE_REGISTER_4_W_PRE_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR4];
          } else {
            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR4] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR4] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 4, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR4, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR5 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] CaParityLat     - C/A Parity Latency Mode bit A0-A2
  @param[in] CRCErrClr       - CRC Error Clear bit A3
  @param[in] CaParityErrSts  - C/A Parity Error Status bit A4
  @param[in] OdtBufferPD     - ODT Input Buffer for Power Down bit A5
  @param[in] CaParityPErr    - CA parity Persistent Error bit A9
  @param[in] DataMask        - Data Mask bit A10
  @param[in] WriteDbi        - Write DBI bit A11
  @param[in] ReadDbi         - Read DBI bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR5_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          CaParityLat,
  IN const UINT8          CRCErrClr,
  IN const UINT8          CaParityErrSts,
  IN const UINT8          OdtBufferPD,
  IN const UINT8          CaParityPErr,
  IN const UINT8          DataMask,
  IN const UINT8          WriteDbi,
  IN const UINT8          ReadDbi
  )
{
  const MrcInput              *Inputs;
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  TOdtValueDdr4               *OdtTableIndex;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  UINT16                      RttParkValue;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  Ddr4ModeRegister.Data                            = 0;
  Ddr4ModeRegister.Bits.C_AParityLatencyMode       = MIN (CaParityLat, DDR4_MODE_REGISTER_5_CA_PLM_MAX);
  Ddr4ModeRegister.Bits.CrcErrorClear              = MIN (CRCErrClr, DDR4_MODE_REGISTER_5_CRC_EC_MAX);
  Ddr4ModeRegister.Bits.C_AParityErrorStatus       = MIN (CaParityErrSts, DDR4_MODE_REGISTER_5_CA_PES_MAX);

  // Keep ODT input buffer enabled for DT/Halo (2DPC)
  Ddr4ModeRegister.Bits.OdtInputBufferforPowerDown = (Inputs->CpuModel == cmICL_ULX_ULT) ? 1 : 0;
  Ddr4ModeRegister.Bits.C_AParityPersistentError   = MIN (CaParityPErr, DDR4_MODE_REGISTER_5_CA_PPE_MAX);
  Ddr4ModeRegister.Bits.DataMask                   = MIN (DataMask, DDR4_MODE_REGISTER_5_DATAMASK_MAX);
  Ddr4ModeRegister.Bits.WriteDbi                   = MIN (WriteDbi, DDR4_MODE_REGISTER_5_WRITEDBI_MAX);
  Ddr4ModeRegister.Bits.ReadDbi                    = MIN (ReadDbi, DDR4_MODE_REGISTER_5_READ_DBI_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR5];
          } else {
            OdtTableIndex = (TOdtValueDdr4 *) GetOdtTableIndex (MrcData, Channel, Dimm);
            if (OdtTableIndex == NULL) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Cannot find ODT table for C%d Dimm%d\n", gErrString, Channel, Dimm);
              return mrcFail;
            }
            // RttPark should not be used in VTT mode
            RttParkValue = (Outputs->OdtMode == MrcOdtModeVtt) ? 0 : OdtTableIndex->RttPark;
            Ddr4ModeRegister = UpdateRttParkValue_DDR4 (MrcData, RttParkValue, Ddr4ModeRegister);

            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR5] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR5] = Ddr4ModeRegister.Data;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 5, Channel, Dimm, Ddr4ModeRegister.Data);
          }
          // Update proper DIMM value
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
        }
      }
      // 3rd parameter is really a rank mask of which ranks to send command to.
      // If need it for all possible and present ranks, it should be 0xF.
      Status = MrcWriteMRSAll (MrcData, Channel, 0x0F, mrMR5, DimmValue);
    }
  }
  return Status;
}

/**
  This function writes the MR6 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] VrefDQValue     - VrefDQ Training Value bit A0-A5
  @param[in] VrefDQRange     - VrefDQ Training Range bit A6
  @param[in] VrefDQEnable    - VrefDQ Training Enable bit A7
  @param[in] TccdL           - tCCD_L bit A10-A12
  @param[in] Restore         - When in RestoreMRs set it to FALSE to propagate the VrefDQEnable input.

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcSetMR6_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          VrefDQValue,
  IN const UINT8          VrefDQRange,
  IN const UINT8          VrefDQEnable,
  IN const UINT8          TccdL,
  IN const BOOLEAN        Restore
  )
{
  MrcDebug                    *Debug;
  MrcOutput                   *Outputs;
  MrcControllerOut            *ControllerOut;
  MrcChannelOut               *ChannelOut;
  UINT16                      DimmValue[MAX_DIMMS_IN_CHANNEL];
  UINT8                       Channel;
  UINT8                       Dimm;
  MrcStatus                   Status;
  DDR4_MODE_REGISTER_6_STRUCT Ddr4ModeRegister;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;

  Ddr4ModeRegister.Data                      = 0;
  Ddr4ModeRegister.Bits.VrefDqTrainingValue  = MIN (VrefDQValue,  DDR4_MODE_REGISTER_6_VrefDQ_V_MAX);
  Ddr4ModeRegister.Bits.VrefDqTrainingRange  = MIN (VrefDQRange,  DDR4_MODE_REGISTER_6_VrefDQ_R_MAX);
  Ddr4ModeRegister.Bits.VrefDqTrainingEnable = MIN (VrefDQEnable, DDR4_MODE_REGISTER_6_VrefDQ_E_MAX);
  Ddr4ModeRegister.Bits.Tccd_l               = MIN (TccdL,        DDR4_MODE_REGISTER_6_tCCD_L_MAX);

  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankInChannelExist (MrcData, Dimm * 2, Channel)) {
          if (Outputs->RestoreMRs) {
            Ddr4ModeRegister.Data = ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR6];
            if (!Restore) { // for Dq Vref propagating
              Ddr4ModeRegister.Bits.VrefDqTrainingEnable = VrefDQEnable;
            }
          } else {
            // save MR value in host struct for subsequent JEDEC init calls
            ChannelOut->Dimm[Dimm].Rank[0].MR[mrMR6] = Ddr4ModeRegister.Data;
            ChannelOut->Dimm[Dimm].Rank[1].MR[mrMR6] = Ddr4ModeRegister.Data;
            if (!Outputs->JedecInitDone) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "MR%d C%u Dimm%u = 0x%X\n", 6, Channel, Dimm, Ddr4ModeRegister.Data);
            }
          }
          DimmValue[Dimm] = Ddr4ModeRegister.Data;
          // 3rd parameter is really a rank mask of which ranks to send command to.
          // If need it for all possible and present ranks, it should be 0xF.
          Status = MrcWriteMRSAll (MrcData, Channel, DIMM_TO_RANK_MASK (Dimm), mrMR6, DimmValue);
        } // if Rank
      } // for Dimm
    } // if channel
  } // for Channel
  return Status;
}

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR2 register

**/
DDR4_MODE_REGISTER_2_STRUCT
UpdateRttWrValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT16                OdtValue,
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister
  )
{
  UINT8 RttValue;

  switch (OdtValue) {
    case 120:
      //
      // RZQ/2
      //
      RttValue = 1;
      break;
    case 240:
      //
      // RZQ/1
      //
      RttValue = 2;
      break;
    case 0xFFFF:
      //
      // Hi-Z
      //
      RttValue = 3;
      break;
    case 80:
      //
      // RZQ/3
      //
      RttValue = 4;
      break;
    default:
      MRC_DEBUG_MSG (
        &MrcData->Outputs.Debug,
        MSG_LEVEL_ERROR,
        "ERROR: unsupported %s value of %u\n",
        gDqOdt,
        OdtValue
        );
      //no break
    case 0:
      //
      // Dynamic ODT Off
      //
      RttValue = 0;
      break;
  }

  Ddr4ModeRegister.Bits.DynamicOdt = RttValue;
  return Ddr4ModeRegister;
}

/**
  This function updates the Rtt value in the MR5 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR5 register

**/
DDR4_MODE_REGISTER_5_STRUCT
UpdateRttParkValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT16                OdtValue,
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister
  )
{
  UINT8 RttValue;

  switch (OdtValue) {
    case 60:
      //
      // RZQ/4
      //
      RttValue = 1;
      break;
    case 120:
      //
      // RZQ/2
      //
      RttValue = 2;
      break;
    case 40:
      //
      // RZQ/6
      //
      RttValue = 3;
      break;
    case 240:
      //
      // RZQ/1
      //
      RttValue = 4;
      break;
    case 48:
      //
      // RZQ/5
      //
      RttValue = 5;
      break;
    case 80:
      //
      // RZQ/3
      //
      RttValue = 6;
      break;
    case 34:
      //
      // RZQ/7
      //
      RttValue = 7;
      break;
    default:
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "ERROR: unsupported odt RttPark value of %u\n", OdtValue);
      //no break
    case 0:
      //
      // RTT_PARK Disable
      //
      RttValue = 0;
      break;
  }

  Ddr4ModeRegister.Bits.RttPark = RttValue;
  return Ddr4ModeRegister;
}

/**
  This function takes the MR1 register value and updates the odt value
  inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/

DDR4_MODE_REGISTER_1_STRUCT
UpdateRttNomValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT16                OdtValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  )
{
  MrcDebug        *Debug;
  UINT8           Value;

  Debug = &MrcData->Outputs.Debug;
  if (OdtValue == 0) {
    //
    // rtt_nom is disable
    //
    Value = 0;
  } else if (OdtValue == 60) {
    //
    // RZQ/4
    //
    Value = 1;
  } else if (OdtValue == 120) {
    //
    // RZQ/2
    //
    Value = 2;
  } else if (OdtValue == 40) {
    //
    // RZQ/6
    //
    Value = 3;
  } else if (OdtValue == 240) {
    //
    // RZQ/1
    //
    Value = 4;
  } else if (OdtValue == 48) {
    //
    // RZQ/5
    //
    Value = 5;
  } else if (OdtValue == 80) {
    //
    // RZQ/3
    //
    Value = 6;
  } else if (OdtValue == 34) {
    //
    // RZQ/7
    //
    Value = 7;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: unsupported odt RttNom value: %d\n", OdtValue);
    Value = 0;
  }

  Ddr4ModeRegister.Bits.OdtRttValue = Value;
  return Ddr4ModeRegister;
}

/**
  This function takes the MR1 register value and updates the ODIC (Output Driver Impedance Control)
  value inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdicValue        - Selected ODIC value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/
DDR4_MODE_REGISTER_1_STRUCT
UpdateOdicValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT16                OdicValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  )
{
  MrcDebug        *Debug;
  UINT8           Value;

  Debug = &MrcData->Outputs.Debug;
  if (OdicValue == 34) {
    //
    // rtt_nom is disable
    //
    Value = DDR4_ODIC_34;
  } else if (OdicValue == 48) {
    //
    // RZQ/4
    //
    Value = DDR4_ODIC_48;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: unsupported ODIC value: %d\n", OdicValue);
    Value = 0;
  }

  Ddr4ModeRegister.Bits.ODImpedance = Value;
  return Ddr4ModeRegister;
}

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueDdr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueDdr4 *
SelectTable_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  )
{
  const MrcInput *Inputs;
  MrcDebug       *Debug;
  MrcOutput      *Outputs;
  TOdtValueDdr4  *OdtTable;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  OdtTable = NULL;

  switch (Inputs->BoardType) {
  case btMobile:
  case btMobileLp4Limit3200:
    if ((OdtIndex >= 2) || (Dimm > 0)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: MbDdr4OdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
      return NULL;
    }
    OdtTable = (TOdtValueDdr4 *) &MbDdr4OdtTable[Dimm][OdtIndex];
    break;

  case btUpServer:
  case btDesktop:
    // @todo: add support for different board topologies - T/daisy chain
    OdtTable = (TOdtValueDdr4 *) &DtDdr4OdtTable[Dimm][OdtIndex];
    break;

  default:
    OdtTable = NULL;
    break;
  }

  return OdtTable;
}

