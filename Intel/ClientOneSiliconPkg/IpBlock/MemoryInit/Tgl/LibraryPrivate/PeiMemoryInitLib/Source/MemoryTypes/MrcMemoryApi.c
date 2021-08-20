/** @file
Implementation of memory abstraction interface.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include "MrcDdr3.h"
#include "MrcDdr4.h"
#include "MrcLpddr4.h"
#include "MrcLpddr4Registers.h"
#include "MrcLpddr5.h"

/**
  This function returns the ODTL timing.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Frequency - Current data rate.
  @param[in]  OdtType   - Selects which command ODT type.
  @param[in]  OdtlParam - Determines if this is for ODT On or Off.

  @retval INT8 - ODT impact to the command timing.
**/
INT8
MrcGetOdtlTiming (
  IN  MrcParameters *const  MrcData,
  IN  MrcFrequency          Frequency,
  IN  LPDDR_ODT_TYPE        OdtType,
  IN  LPDDR_ODTL_PARAM      OdtlParam
  )
{
  INT8 RetVal;

  RetVal = 0;
  switch (MrcData->Outputs.DdrType)  {
    case MRC_DDR_TYPE_LPDDR4:
      // Currently LP4 implementation only needs Write ODT
      if (OdtType == LpWrOdt) {
        // LPDDR4 timing. WL Set is statically configured to Set B.
        RetVal = MrcGetOdtlTimingLpddr4 (Frequency, Lp4WlSetB, OdtlParam);
      }
      break;

    case MRC_DDR_TYPE_LPDDR5:
      if (OdtType == LpWrOdt) {
        RetVal = MrcGetWrOdtlLpddr5 (Frequency, OdtlParam);
      } else {
        RetVal = MrcGetNtRdOdtlLpddr5 (Frequency, OdtlParam);
      }
      break;

    default:
      break;
  }

  return RetVal;
}

/**
  This function returns the timing value for Precharge to Precharge delay.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval UINT8 - 0 for unsupported technologies, otherwise the delay in tCK
**/
UINT8
MrcGetPpd (
  IN MrcParameters *const MrcData
  )
{
  UINT8 RetVal;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      RetVal = MRC_LP4_tPPD_ALL_FREQ;
      break;

    case MRC_DDR_TYPE_LPDDR5:
      RetVal = MRC_LP5_tPPD_ALL_FREQ;
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
}

/**
  This function returns the timing value for Read Preamble.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval UINT8 - 0 for unsupported technologies, otherwise the delay in tCK.
**/
UINT8
MrcGetRpre (
  IN MrcParameters *const MrcData
  )
{
  UINT8 RetVal;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR5:
      RetVal = 1;
      break;

    case MRC_DDR_TYPE_LPDDR4:
      RetVal = TRPRE_ALL_FREQ_LP4;
      break;

    case MRC_DDR_TYPE_DDR4:
      RetVal = TRPRE_ALL_FREQ;
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
}

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
    case MRC_DDR_TYPE_LPDDR5:
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
  This function returns tWCKPRE_Static for both Writes and Reads

  @param[in]  MrcData   - Pointer to MRC global data.

  @retval INT8 - Timing in tCK, or 0 if unsupported for the DDR type.
**/
UINT8
MrcGetWckPreStatic (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     RetVal;

  Outputs = &MrcData->Outputs;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR5:
      RetVal = MrcGetWckPreStaticLpddr5 (Outputs->HighFrequency);
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
}

/**
  This function returns tWCKENL_FS for the current DRAM configuration.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval UINT8 - Timing in tCK, or 0 if unsupported.
**/
UINT8
MrcGetWckEnlFs (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     RetVal;

  Outputs = &MrcData->Outputs;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR5:
      RetVal = MrcGetWckEnlFsLpddr5 (Outputs->HighFrequency);
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
}

/**
  This function returns tCKENL_WR for the current DRAM configuration.

  @param[in]  MrcData   - Pointer to MRC global data.

  @retval UINT8 - Timing in tCK, or 0 if unsupported for the DDR type.
**/
UINT8
MrcGetWckPreWrTotal (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     RetVal;

  Outputs = &MrcData->Outputs;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR5:
      RetVal = MrcGetWckPreWrTotalLpddr5 (Outputs->HighFrequency);
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
}

/**
  This function returns tWCKPRE_total_RD for the current DRAM configuration.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval UINT8 - Timing in tCK, or 0 if unsupported for the DDR type.
**/
UINT8
MrcGetWckPreRdTotal (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput *Outputs;
  UINT8     RetVal;

  Outputs = &MrcData->Outputs;

  switch (Outputs->DdrType) {
    case MRC_DDR_TYPE_LPDDR5:

      RetVal = MrcGetWckPreRdTotalLpddr5 (Outputs->HighFrequency);
      break;

    default:
      RetVal = 0;
      break;
  }

  return RetVal;
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
    case MRC_DDR_TYPE_LPDDR5:
      SocOdtRet = MrcCheckSocOdtLpddr (MrcData, SocOdt);
      break;

    default:
      SocOdtRet = SocOdt;
  }

  return SocOdtRet;
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

    case MRC_DDR_TYPE_LPDDR5:
      lBusWidth = 7;
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
  This function handles calling the correct JEDEC Reset sequence based on DDR Technology.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcJedecReset (
  IN  MrcParameters *MrcData
  )
{
  MrcStatus Status;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
    case MRC_DDR_TYPE_LPDDR5:
      Status = MrcJedecResetLpddr (MrcData);
      break;

    case MRC_DDR_TYPE_DDR4:
      MrcJedecResetDdr4 (MrcData);
      Status = mrcSuccess;
      break;

    default:
      Status = mrcUnsupportedTechnology;
      break;
  }

  return Status;
}

/**
  This function handles calling the correct JEDEC Init sequence based on DDR Technology.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcJedecInit (
  IN  MrcParameters *MrcData
  )
{
  MrcStatus Status;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      Status = MrcJedecInitLpddr4 (MrcData);
      break;

    case MRC_DDR_TYPE_LPDDR5:
      Status = MrcJedecInitLpddr5 (MrcData);
      break;

    case MRC_DDR_TYPE_DDR4:
      Status = MrcJedecInitDdr4 (MrcData);
      break;

    default:
      Status = mrcUnsupportedTechnology;
      break;
  }

  return Status;
}

/**
  Used to update VrefDQ for DDR4/LPDDR4 or VrefCA for LPDDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData             - Include all MRC global data.
  @param[in]     Controller          - Selecting which Controller to talk to.
  @param[in]     Channel             - Selecting which Channel to talk to.
  @param[in]     RankMask            - Selecting which Ranks to talk to.
  @param[in]     DeviceMask          - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     VrefType            - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset              - Vref offset value.
  @param[in]     UpdateMrcData       - Used to decide if Mrc host must be updated.
  @param[in]     PdaMode             - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval Nothing.
**/
void
MrcSetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
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
      Status = Lpddr4SetDramVref (MrcData, Controller, Channel, RankMask, VrefType, Offset, UpdateMrcData, IsCachedOffsetParam);
      break;

    case MRC_DDR_TYPE_DDR4:
      Status = Ddr4SetDramVref (MrcData, Controller, Channel, RankMask, DeviceMask, VrefType, Offset, UpdateMrcData, PdaMode, IsCachedOffsetParam);
      break;

    case MRC_DDR_TYPE_LPDDR5:
      Status = Lpddr5SetDramVref (MrcData, Controller, Channel, RankMask, VrefType, Offset, UpdateMrcData, IsCachedOffsetParam);
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(&Outputs->Debug, MSG_LEVEL_ERROR, "%s ", gUnsupportedTechnology);
      break;
    }

  MRC_DEBUG_ASSERT(Status == mrcSuccess, Debug, "Error Setting DIMM VREF");

}

/**
  Program LPDDR4 FSP-OP and FSP-WR values.
  It will set the ranks specified in the rank mask in all Channels and Controllers populated.
  NOTE:
        Encoding for Vrcg MR field is the same for LPDDR4 and LPDDR5.
          So we only need to pass through the external type defined in MrcMemoryApi.h.
          If this changes, then this function will need to translate between MRC enumeration to MR enumeration.
        FSP points for LPDDR4 and LPDDR5 are integer points.  LPDDR4 supports 2 points, and LPDDR5 supports 3 points.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  RankMask    - Bit mask of Rank's to configure.
  @param[in]  VrcgMode    - VREF Current Generator mode switch.
  @param[in]  FspWePoint  - FSP-WR. Valid Values: LP4 - 0:1; LP5 - 0:2
  @param[in]  FspOpPoint  - FSP-OP. Valid Values: LP4 - 0:1; LP5 - 0:2

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcSetFspVrcg (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 RankMask,
  IN  UINT8                 VrcgMode,
  IN  UINT8                 FspWePoint,
  IN  UINT8                 FspOpPoint
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcStatus     Status;
  MrcDdrType    DdrType;
  UINT32        Controller;
  UINT32        Channel;
  UINT32        Address;
  UINT32        MrIndex;
  UINT32        Delay;
  UINT16        *MrPtr;
  UINT8         Rank;
  BOOLEAN       Lpddr5;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;

  Lpddr5  = (DdrType == MRC_DDR_TYPE_LPDDR5);
  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    Address = mrMR13;
    MrIndex = mrIndexMR13;
  } else if (Lpddr5) {
    Address = mrMR16;
    MrIndex = mrIndexMR16;
  } else {
    return mrcUnsupportedTechnology;
  }
  Status  = mrcSuccess;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((!MrcRankExist (MrcData, Controller, Channel, Rank)) || ((RankMask & (1 << Rank)) == 0)) {
          continue;
        }
        MrPtr = ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR;

        if (Lpddr5) {
          MrcLpddr5SetMr16 (MrcData, FspWePoint, FspOpPoint, MRC_IGNORE_ARG_8, VrcgMode, MRC_IGNORE_ARG_8, &MrPtr[mrIndexMR16]);
        } else {
          MrcLpddr4SetMr13 (MrcData, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, VrcgMode, MRC_IGNORE_ARG_8, FspWePoint, FspOpPoint, &MrPtr[mrIndexMR13]);
        }

        Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, Address, MrPtr[MrIndex], TRUE);
        if (Status != mrcSuccess) {
          return Status;
        }
      } // for Rank
    } // for Channel
  } // for Controller

  if (FspOpPoint != MRC_IGNORE_ARG_8) {
    // When FSP-OP is changed, wait tFC_Long = 250ns
    // This covers for tVRCG_ENABLE/tVRCG_DISABLE as well if needed
    Delay = MRC_LP_tFC_LONG_NS;
    if (Lpddr5) {
      // 4.16.1 Frequency Set Point Update Timing
      // Table 82 - AC Timing Table
      Delay += Outputs->tCKps / 2;
    }
    MrcWait (MrcData, DIVIDECEIL (Delay, MRC_TIMER_1NS));
  } else if (VrcgMode != MRC_IGNORE_ARG_8) {
    // When VRCG mode is changed, wait tVRCG_ENABLE or tVRCG_DISABLE
    if (Lpddr5) {
      Delay = (VrcgMode == LpVrcgNormal) ? MRC_LP5_tVRCG_DISABLE_NS : MRC_LP5_tVRCG_ENABLE_NS;
    } else {
      Delay = (VrcgMode == LpVrcgNormal) ? MRC_LP4_tVRCG_DISABLE_NS : MRC_LP4_tVRCG_ENABLE_NS;
    }
    MrcWait (MrcData, DIVIDECEIL (Delay, MRC_TIMER_1NS));
  }

  return Status;
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
  @param[in]     Controller   Controller index to work.
  @param[in]     Channel    - Channel index to work on.
  @param[in]     Ranks      - Rank mask to be applied to.
  @param[in]     OptParam   - Defines the OptParam Offsets.
  @param[in]     ParamValue - The actual values (Typically in Ohms)
  @param[in]     UpdateHost - Decides if MrcData has to be updated

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                    - MrcStatus of the Technology specific SetDimmParamValue functions

**/
MrcStatus
SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                Ranks,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue,
  IN     UINT8                UpdateHost
  )
{

  MrcOutput      *Outputs;
  MrcInput       *Inputs;
  MrcChannelOut  *ChannelOut;
  UINT16         *MrReg;
  MrcStatus      Status;
  MrcDdrType     DdrType;
  UINT16         MrRegVal;
  UINT8          Rank;
  UINT8          DdrRank;
  UINT8          MrIndex;
  UINT8          MrNum;
  UINT16         RankValues[MAX_RANK_IN_CHANNEL];
  const MRC_FUNCTION  *MrcCall;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  DdrType     = Outputs->DdrType;
  MrcCall->MrcSetMem((UINT8 *)RankValues, sizeof(RankValues), 0);

  Status = GetOptDimmParamMrIndex (MrcData, OptParam, &MrIndex, &MrNum);
  if (Status != mrcSuccess) {
    return Status;
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((!MrcRankExist (MrcData, Controller, Channel, Rank)) || ((Ranks &  (MRC_BIT0 << Rank)) == 0)) {
      continue;
    }
    // Extract MR value from host struct
    DdrRank = (Outputs->Lpddr) ? dDIMM0 : Rank / MAX_RANK_IN_DIMM;
    MrReg = &ChannelOut->Dimm[DdrRank].Rank[(Rank % MAX_RANK_IN_DIMM)].MR[mrMR0];
    MrRegVal = MrReg[MrIndex];
    switch (DdrType) {
      case MRC_DDR_TYPE_LPDDR4:
        Status = Lpddr4SetDimmParamValue (MrcData, &MrRegVal, OptParam, ParamValue);
        break;

      case MRC_DDR_TYPE_DDR4:
        Status = Ddr4SetDimmParamValue (MrcData, &MrRegVal, OptParam, ParamValue);
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
  }// Rank

  // Perform MRH operation for LPDDR4 - Send MRW command. For DDR4 MRS Command
  switch (DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((!MrcRankExist (MrcData, Controller, Channel, Rank)) || ((Ranks & (1 << Rank)) == 0)) {
          continue;
        }
        Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, MrNum, RankValues[Rank], TRUE);
        if (Status != mrcSuccess) {
          // Skip next writes upon failure
          return Status;
        }
      } // rank
      break;

    case MRC_DDR_TYPE_DDR4:
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((!MrcRankExist (MrcData, Controller, Channel, Rank)) || ((Ranks & (1 << Rank)) == 0)) {
          continue;
        }
        Status = MrcWriteMRS (MrcData, Controller, Channel, 1 << Rank, MrNum, RankValues[Rank]);
        if (Status != mrcSuccess) {
          return Status;  // Skip next writes upon failure
        }
      } // rank
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
  Return the ODT table index for the given Controller / Channel / DIMM.

  @param[in] MrcData         - Include all the mrc global data.
  @param[in] Controller      - Controller to work on.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - DIMM to work on.

  @retval Pointer to the relevant ODT structure - or (TOdtValueDdr4 *) or (TOdtValueLpddr4 *)
**/
void *
GetOdtTableIndex (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel,
  IN const UINT32         Dimm
  )
{
  void          *RetVal;
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  TOdtIndex     OdtIndex;
  MrcDdrType    DdrType;
  UINT8         RanksInDimm0;
  UINT8         RanksInDimm1;
  BOOLEAN       Ddr4;
  BOOLEAN       Lpddr4;
  BOOLEAN       Lpddr5;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  DdrType     = Outputs->DdrType;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5      = (DdrType == MRC_DDR_TYPE_LPDDR5);
  DimmOut     = &ChannelOut->Dimm[dDIMM0];
  RanksInDimm0 = DimmOut[dDIMM0].RankInDimm;
  RanksInDimm1 = DimmOut[dDIMM1].RankInDimm;
  OdtIndex     = oiNotValid;
  RetVal       = NULL;

  switch (ChannelOut->DimmCount) {
    case 2:
      //
      // Two dimms per channel.
      //
      if (Lpddr4 || Lpddr5) {
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

  if (OdtIndex != oiNotValid) {
    if (Ddr4) {
      RetVal = SelectTable_DDR4 (MrcData, Dimm, OdtIndex);
    } else if (Lpddr4) {
      RetVal = SelectTable_LPDDR4 (MrcData, Dimm, OdtIndex);
    } else if (Lpddr5) {
      RetVal = SelectTable_LPDDR5 (MrcData, Dimm, OdtIndex);
    }
    // @todo: DDR5
  }

  if (RetVal == NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: DDR Type Unsupported: %s\n", gErrString, gDdrTypeStr[DdrType]);
  }
  return RetVal;
}

