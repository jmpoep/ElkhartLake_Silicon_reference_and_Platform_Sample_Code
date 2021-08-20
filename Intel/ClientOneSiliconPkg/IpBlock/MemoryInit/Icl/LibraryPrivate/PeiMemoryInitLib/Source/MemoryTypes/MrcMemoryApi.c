/** @file
Implementation of memory abstraction interface.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#include "MrcInterface.h"
#include "MrcDdrCommon.h"
#include "MrcMemoryApi.h"
#include "MrcMaintenance.h"
#include "MrcDdr4.h"
#include "MrcLpddr4.h"
#include "MrcLpddr4Registers.h"

/**
  This function will return the JEDEC parameter tDQS2DQ Min or Max based on the
  populated memory type.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  IsMin   - TRUE returns the minimum value, FALSE returns the maximum value.
  @param[out] Tdqs2dq - Returned parameter value in Femtoseconds.  If the memory technology does not support the parameter, 0 is returned.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetTdqs2dq (
  IN  MrcParameters *const  MrcData,
  IN  const BOOLEAN         IsMin,
  OUT UINT32                *Tdqs2dq
  )
{
  MrcStatus Status;
  UINT32    lTdqs2dq;

  Status    = mrcSuccess;
  lTdqs2dq  = 0;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      lTdqs2dq = Lpddr4GetTdqs2dq (IsMin);
      break;

    case MRC_DDR_TYPE_DDR4:
      break;

    default:
      Status  = mrcDimmNotSupport;
      break;
  }

  if (Tdqs2dq != NULL) {
    *Tdqs2dq  = lTdqs2dq;
  }

  return Status;
}

/**
  This function will return the center of the range of the JEDEC timing parameter tDQS2DQ based on the
  populated memory type.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[out] Tdqs2dqCenter - Returned parameter value in Femptoseconds.  If the memory technology does not suppor the parameter, 0 is returned.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetTdqs2dqCenter (
  IN  MrcParameters *const  MrcData,
  OUT UINT32                *Tdqs2dqCenter
  )
{
  MrcStatus Status;
  UINT32    lTdqs2dqMax;
  UINT32    lTdqs2dqMin;
  UINT32    lTdqs2dqCenter;

  Status          = mrcSuccess;
  lTdqs2dqCenter  = 0;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      lTdqs2dqMin = Lpddr4GetTdqs2dq (TRUE);
      lTdqs2dqMax = Lpddr4GetTdqs2dq (FALSE);
      lTdqs2dqCenter  = (lTdqs2dqMax + lTdqs2dqMin) / 2;
      break;

    case MRC_DDR_TYPE_DDR4:
      break;

    default:
      Status  = mrcDimmNotSupport;
      break;
  }

  if (Tdqs2dqCenter != NULL) {
    *Tdqs2dqCenter  = lTdqs2dqCenter;
  }

  return Status;
}

/**
  This function will return the JEDEC parameter tDQSCK MIN based on the
  populated memory type.

  @param[in]   MrcData   - Pointer to MRC global data.
  @param[out]  TdqsCkPs  - If TdqsCk is not present on the current memory technology, 0 is returned.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetTdqsckMin (
  IN  MrcParameters *const  MrcData,
  OUT UINT32                *TdqsCkPs
  )
{
  MrcStatus   Status;
  UINT32      TdqsckMin;

  Status    = mrcSuccess;
  TdqsckMin = 0;

  switch (MrcData->Outputs.DdrType) {

    case MRC_DDR_TYPE_LPDDR4:
      TdqsckMin = tDQSCK_MIN_LP4;
      break;

    case MRC_DDR_TYPE_DDR4:
      // TdqsckMin is initialized to 0.  Break the switch without an error message.
      break;

    default:
      Status = mrcDimmNotSupport;
      break;
  }

  if (TdqsCkPs != NULL) {
    *TdqsCkPs = TdqsckMin;
  }

  return Status;
}

/**
  This function determines if the SOC ODT requested is valid for the memory technology.
  If, the requested ODT is not supported, it will return the the closest matching ODT.
  If there is no limitation by the memory technology or the ODT value is supported,
  it will return the requested ODT.

  @param[in]  MrcData - Pointer to the global MRC data
  @param[in]  SocOdt  - The ODT requested by the system

  @retval - Valid ODT value.
**/
UINT16
MrcCheckForSocOdtEnc (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                SocOdt
  )
{
  UINT16  SocOdtRet;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      SocOdtRet = MrcCheckSocOdtLpddr4 (MrcData, SocOdt);
      break;

    default:
      SocOdtRet = SocOdt;
  }

  return SocOdtRet;
}

/**
  This function configures the DRAM final state value before going to Normal Mode.

  @param[in] MrcData - Pointer to global MRC data.

  @retval Nothing.
**/
VOID
MrcDramStateFinalize (
  IN  MrcParameters *const MrcData
  )
{
  const MrcInput                         *Inputs;
  MrcOutput                              *Outputs;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Outputs->Lp4x) && ( Inputs->IclA0)) {
    Lpddr4FspSetStaticMrs (MrcData);
  }
}

/**
  This function returns the Command/Address bus width per technology type.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[out] BusWidth  - Return variable for the bus width.  0 is return if the technology is not supported.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetCmdBusWidth (
  IN  MrcParameters *const  MrcData,
  OUT UINT8                 *BusWidth
  )
{
  MrcStatus   Status;
  UINT8       lBusWidth;

  Status  = mrcSuccess;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      lBusWidth = 6;
      break;

    case MRC_DDR_TYPE_DDR4:
      lBusWidth = 22;
      break;

    default:
      lBusWidth = 0;
      Status    = mrcDimmNotSupport;
      break;
  }

  if (BusWidth != NULL) {
    *BusWidth = lBusWidth;
  }

  return Status;
}

/**
  Used to update VrefDQ for DDR4/LPDDR4 or VrefCA for LPDDR4.
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

  @retval Nothing.
**/
void
MrcSetDramVref (
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
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcStatus        Status;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      Status = Lpddr4SetDramVref (MrcData, Channel, RankMask, VrefType, Offset, UpdateMrcData, IsCachedOffsetParam);
      break;

    case MRC_DDR_TYPE_DDR4:
      Status = Ddr4SetDramVref (MrcData, Channel, RankMask, DeviceMask, VrefType, Offset, UpdateMrcData, PdaMode, IsCachedOffsetParam);
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(&Outputs->Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
      break;
  }

  MRC_DEBUG_ASSERT(Status == mrcSuccess, Debug, "Error Setting DIMM VREF");
}

/**
  SetDimmParamValue is responsible for performing the concrete set DIMM parameter to value, using
  Per-Technology SetDimmParamValue functions.
  Parameters supported: OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom.
  Function performs the following stages:
  1. Reads cached value.
  2. Programs new value to cache.
  3. Programs MRs via MRH.

  Note Shadow register are defined per Channel. If there is any variation between ranks it will be lost.

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel index to work on.
  @param[in]     Ranks      - Rank mask to be applied to.
  @param[in]     SubChMask  - Sub Channel index to work on.
  @param[in]     OptParam   - Defines the OptParam Offsets.
  @param[in]     ParamValue - The actual values (Typically in Ohms)
  @param[in]     UpdateHost - Decides if MrcData has to be updated

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                    - MrcStatus of the Technology specific SetDimmParamValue functions

**/
MrcStatus
SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                Ranks,
  IN     UINT8                SubChMask,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue,
  IN     UINT8                UpdateHost
  )
{

  MrcOutput      *Outputs;
  MrcInput       *Inputs;
  MrcChannelOut  *ChannelOut;
  UINT16         *MrReg;
  UINT16         MrRegVal;
  MrcStatus      Status;
  UINT8          Rank;
  UINT8          SubCh;
  UINT8          MrIndex;
  UINT8          MrNum;
  UINT16         RankValues[MAX_RANK_IN_CHANNEL];
  const MRC_FUNCTION  *MrcCall;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  ChannelOut    = &Outputs->Controller[0].Channel[Channel];
  MrcCall->MrcSetMem((UINT8 *)RankValues, sizeof(RankValues), 0);

  Status = GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
  if (Status != mrcSuccess) {
    return Status;
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((!MrcRankInChannelExist (MrcData, Rank, Channel)) || ((Ranks &  (MRC_BIT0 << Rank)) == 0)) {
      continue;
    }
    // Extract MR value from host struct
    MrReg = &ChannelOut->Dimm[Rank / 2].Rank[(Rank % 2)].MR[mrMR0];
    MrRegVal = MrReg[MrIndex];
    switch (Outputs->DdrType) {

      case MRC_DDR_TYPE_LPDDR4:
        Status = Lpddr4SetDimmParamValue(MrcData, &MrRegVal, OptParam, ParamValue);
        break;

      case MRC_DDR_TYPE_DDR4:
        Status = Ddr4SetDimmParamValue(MrcData, &MrRegVal, OptParam, ParamValue);
        break;

      default:
        Status = mrcWrongInputParameter;
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
        break;
    }
    if (Status != mrcSuccess) {
      // Skip MR Write in case of incorrect MR Set
      return Status;
    }

    // Program the corresponding value to the MR
    RankValues[Rank] = MrRegVal;
    if (UpdateHost) {
      MrReg[MrIndex] = MrRegVal;
    }
  }

  // Perform MRH operation for LPDDR4 - Send MRW command. For DDR4 MRS Command
  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((!MrcRankInChannelExist (MrcData, Rank, Channel)) || ((Ranks & (1 << Rank)) == 0)) {
          continue;
        }
        for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
          if ((MrcSubChannelExist(MrcData, Channel, SubCh)) && ((SubChMask & (1<<SubCh)) > 0)) {
            Status = MrcIssueMrw (MrcData, Channel, SubCh, Rank, MrNum, RankValues[Rank], FALSE, FALSE, TRUE);
            if (Status != mrcSuccess) {
              // Skip next writes upon failure
              return Status;
            }
          }
        } // for SubCh
      }
      break;

    case MRC_DDR_TYPE_DDR4:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((!MrcRankInChannelExist (MrcData, Rank, Channel)) || ((Ranks & (1 << Rank)) == 0)) {
          continue;
        }
        Status = MrcWriteMRS (MrcData, Channel, 1 << Rank, MrNum, RankValues[Rank]);
        if (Status != mrcSuccess) {
          return Status;  // Skip next writes upon failure
        }
      }
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
      break;
  }

  return Status;
}



/**
  GetOptDimmParamMrIndex using Technology specific GetOptDimmParamMrIndex functions

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  OptParam  - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out] *MrIndex  - Updated Pointer to the MR index.
  @param[out] *MrNum    - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                      Status of the Technology specific functions otherwise
**/

MrcStatus
GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
  )
{
  MrcOutput  *Outputs;
  MrcDebug   *Debug;
  MrcStatus  Status;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      Status = Lpddr4GetOptDimmParamMrIndex (MrcData, OptDimmParam, MrIndex, MrNum);
      break;

    case MRC_DDR_TYPE_DDR4:
      Status = Ddr4GetOptDimmParamMrIndex (MrcData, OptDimmParam, MrIndex, MrNum);
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
  }

  return Status;
}

/**
  Get an array of the corresponding possible DIMM OptParam values available
  per memory technology.
  Supported DimmOptParams: OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon

  @param[in]  MrcData       - Include all MRC global data.
  @param[in]  DimmOptParam  - OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                      Status of the Technology specific functions otherwise
**/
MrcStatus
GetDimmOptParamValues (
  IN MrcParameters  *const MrcData,
  IN UINT8          DimmOptParam,
  OUT UINT16        **DimmOptParamVals,
  OUT UINT8         *NumDimmOptParamVals
  )

{
  MrcOutput  *Outputs;
//  MrcDebug   *Debug;
  MrcStatus  Status;
  Outputs = &MrcData->Outputs;
//  Debug   = &Outputs->Debug;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      Status = Lpddr4GetDimmOptParamValues (MrcData, DimmOptParam, DimmOptParamVals, NumDimmOptParamVals);
      break;

    default:
    case MRC_DDR_TYPE_DDR4:
      Status = Ddr4GetDimmOptParamValues (MrcData, DimmOptParam, DimmOptParamVals, NumDimmOptParamVals);
      break;

//    default:
//      Status = mrcWrongInputParameter;
//      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
  }

  return Status;
}

/**
  Return the ODT table index for the given Channel / DIMM.

  @param[in] MrcData         - Include all the mrc global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - DIMM to work on.

  @retval Pointer to the relevant ODT structure - (TOdtValue *) or (TOdtValueDdr4 *)
**/
void *
GetOdtTableIndex (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Dimm
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  TOdtIndex     OdtIndex;
  UINT8         RanksInDimm0;
  UINT8         RanksInDimm1;
  BOOLEAN       Ddr4;
  BOOLEAN       Lpddr4;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  DimmOut     = &ChannelOut->Dimm[dDIMM0];
  RanksInDimm0 = DimmOut[dDIMM0].RankInDimm;
  RanksInDimm1 = DimmOut[dDIMM1].RankInDimm;
  OdtIndex    = oiNotValid;

  switch (ChannelOut->DimmCount) {
    case 2:
      //
      // Two dimms per channel.
      //
      if (Lpddr4) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: LPDDR4 2DPC Not Supported\n", gErrString);
      } else {
        if ((RanksInDimm0 == 1) && (RanksInDimm1 == 1)) {
          OdtIndex = oi2DPC1R1R;
        } else if ((RanksInDimm0 == 1) && (RanksInDimm1 == 2)) {
          OdtIndex = oi2DPC1R2R;
        } else if ((RanksInDimm0 == 2) && (RanksInDimm1 == 1)) {
          OdtIndex = oi2DPC2R1R;
        } else if ((RanksInDimm0 == 2) && (RanksInDimm1 == 2)) {
          OdtIndex = oi2DPC2R2R;
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: Invalid 2DPC rank mode\n", gErrString);
        }
      }
      break;

    case 1:
      //
      // One dimm per channel.
      //
      if ((RanksInDimm0 == 1) ||
          ((RanksInDimm1 == 1) && (MAX_DIMMS_IN_CHANNEL > 1))
         ) {
          OdtIndex = oi1DPC1R;
      } else if ((RanksInDimm0 == 2) ||
                 ((RanksInDimm1 == 2) && (MAX_DIMMS_IN_CHANNEL > 1))
                ) {
          OdtIndex = oi1DPC2R;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: Invalid 1DPC rank mode\n", gErrString);
      }
      break;

    default:
      break;
  }

  if (Ddr4) {
    return (OdtIndex == oiNotValid) ? NULL : SelectTable_DDR4 (MrcData, Dimm, OdtIndex);
  } else { // Lpddr4
    return (OdtIndex == oiNotValid) ? NULL : SelectTable_LPDDR4 (MrcData, Dimm, OdtIndex);
  }
}

