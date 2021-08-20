/** @file
  This module sets the memory controller refresh parameters.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
///
/// Include files
///
#include "MrcRefreshConfiguration.h"

///
/// Self refresh idle timer value
///
#define SELF_REFRESH_IDLE_COUNT (0x200)

/**
  This function returns the value of tXSR in tCK based on DdrType.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Timing     - Pointer to timing values.
**/
static
UINT32
tXSRGet (
  IN MrcParameters *const MrcData,
  IN MrcTiming *const     Timing
  )
{
  UINT32 tXSRVal;
  UINT32 MinCK;
  UINT32 tXSOffset;
  UINT32 tCK;
  BOOLEAN Lpddr4;

  Lpddr4  = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4);
  tCK     = Timing->tCK;
  //
  // Units here are in Fempto Seconds.
  // 7.5ns for LP4, rest are 10 ns.
  //
  tXSOffset = (Lpddr4) ? (7500 * 1000) : (10 * 1000 * 1000);
  tXSOffset = DIVIDECEIL (tXSOffset, tCK);
  if (Lpddr4) {
    MinCK = 2;
  } else { // DDR4
    MinCK = 0;
  }
  //
  // Current LP3 SPD places tRFCab in tRFC entry.
  //
  tXSRVal = Timing->tRFC + tXSOffset;
  tXSRVal = MAX (tXSRVal, MinCK);

  return tXSRVal;
}

/**
  This function returns the tXSDLL in DCLKs based on DDR Type,
  DDR4 has values per frequency, and LPDDR4 do not have
  a DLL.  From the spec, we must wait tXSR before issuing a command.  Thus,
  we set tXSDLL to tXSR to ensure tXSR before read/write commands.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Frequency  - The memory frequency.
  @param[in] tXSR       - Value of tXSR.
**/
static
UINT32
tXSDLLGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency   Frequency,
  IN const UINT32         tXSR
  )
{
  UINT32  tXSDLLVal;
  MrcDdrType  DdrType;

  DdrType = MrcData->Outputs.DdrType;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    if (Frequency <= f1867) {
      tXSDLLVal = tDLLK_DDR4_1867;
    } else if (Frequency <= f2400) {
      tXSDLLVal = tDLLK_DDR4_2400;
    } else {
      tXSDLLVal = tDLLK_DDR4_MAX;
    }
  } else {
    //
    // No DLL in LPDDR4.  Use tXSR.
    //
    tXSDLLVal = tXSR;
  }

  return tXSDLLVal;
}

/**
  This function configures refresh parameters:
    tREFI, tRFC, tREFIx9, OREF_RI, tRFCpb

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval Nothing.
**/
void
SetTcRfpRftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  const MrcInput  *Inputs;
  MrcTiming       *TimingOut;
  MrcProfile      Profile;
  INT64           GetSetVal;
  UINT32          tRefi;

  Inputs    = &MrcData->Inputs;
  Profile   = Inputs->MemoryProfile;
  TimingOut = &MrcData->Outputs.Controller[0].Channel[Channel].Timing[Profile];

  tRefi = (TimingOut->tREFI);
  if (Inputs->SaGv == MrcSaGvEnabled) {
    // Reduce tREFI by a factor .972
    tRefi *= 972;
    tRefi = DIVIDEROUND (tRefi, 1000);
  }

  //
  // Set LP0 WM and OREF_RI to support high memory BW traffic
  //
  GetSetVal           = (tRefi * 89) / (1024 * 10);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctREFIx9, WriteNoCache | PrintValue, &GetSetVal);

  GetSetVal           = 0x40;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOrefRi, WriteNoCache | PrintValue, &GetSetVal);

  GetSetVal           = tRefi;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctREFI, WriteNoCache | PrintValue, &GetSetVal);
  GetSetVal           = TimingOut->tRFC;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRFC, WriteNoCache | PrintValue, &GetSetVal);

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      // PBR GetSet field is a disable
      GetSetVal = (Inputs->PerBankRefresh == 0);
      break;

    default:
      GetSetVal = 1;
      break;
  }

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccPbrDis, WriteNoCache | PrintValue, &GetSetVal);
  GetSetVal = TimingOut->tRFCpb;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRFCpb, WriteNoCache | PrintValue, &GetSetVal);
}

/**
  This function configures the Self Refresh Timing Parameters for the MC:
  tZQOPER, tXS-offset, tXSDLL, and tMOD.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval Nothing.
**/
static
void
SetTcSrftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32        Channel
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcFrequency  Frequency;
  MrcTiming     *Timing;
  INT64         GetSetVal;
  INT64         tZQOPER;
  INT64         tXSDLL;
  INT64         tMOD;
  UINT32        tXSR;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  Frequency  = ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;
  Timing     = &Outputs->Controller[0].Channel[Channel].Timing[Inputs->MemoryProfile];
  tZQOPER    = tZQOPERGet (MrcData, Frequency);
  tXSR       = tXSRGet (MrcData, Timing);
  tXSDLL     = tXSDLLGet (MrcData, Frequency, tXSR);
  tMOD       = tMODGet (MrcData, Frequency, Timing->tCK);

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctXSDLL,  WriteToCache | PrintValue, &tXSDLL);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctMOD,    WriteToCache | PrintValue, &tMOD);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctZQOPER, WriteToCache | PrintValue, &tZQOPER);
  GetSetVal = tXSR;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctXSR,    WriteNoCache | PrintValue, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  return;
}

/**
  This function returns the tZQOPER value.
  tZQOPER = Defines the period required for ZQCL after SR exit.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval The tZQOPER value.
**/
UINT32
tZQOPERGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency   Frequency
  )
{
  MrcOutput  *Outputs;
  UINT32     tZQOPER;
  MrcDdrType DdrType;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  tZQOPER = 0;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tZQOPER = tZQOPER_DDR4;
  }

  return tZQOPER;
}

/**
  This function returns the tMOD value.
  tMOD = max(24nCK, 15ns) nCK change by the frequency for DDR4

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] tCK       - DCLK period in femtoseconds.

  @retval The tMOD value.
**/
UINT32
tMODGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency   Frequency,
  IN const UINT32         tCK
  )
{
  UINT32      tMOD;
  MrcDdrType  DdrType;

  DdrType = MrcData->Outputs.DdrType;
  tMOD    = MRC_UINT32_MAX;

#if (SUPPORT_DDR4 == SUPPORT)
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tMOD = tMOD_DDR4;
  } else
#endif // SUPPORT_DDR4
  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    tMOD = DIVIDECEIL (tMOD_LPDDR4_FS, tCK);
  }

  return tMOD;
}

/**
  This function returns the LPDDR4 tZQCAL value in DCLKs.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] tCK      - DCLK period in femtoseconds.

  @retval The tZQCAL value.
**/
UINT32
tZQCALGet (
  IN MrcParameters *const MrcData,
  IN UINT32               tCK
  )
{
  UINT32 tZQCAL;

  tZQCAL = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4) ? DIVIDECEIL (tZQCAL_FS, tCK) : 0;

  return tZQCAL;
}

/**
  This function configures the TC-ZQCAL register and its fields tZQCS and tZQCS_PERIOD.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval Nothing.
**/
static
void
SetTcZqCalReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  )
{
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcTiming *Timing;
  INT64     tZQCS;
  INT64     ZQCSPeriod;
  INT64     tZQCAL;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Timing   = &Outputs->Controller[0].Channel[Channel].Timing[Inputs->MemoryProfile];

  tZQCS       = tZQCSGet (MrcData, Timing->tCK);
  ZQCSPeriod = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? ZQCS_PERIOD_LPDDR : ZQCS_PERIOD_DDR4;
  tZQCAL      = tZQCALGet (MrcData, Timing->tCK);

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctZQCAL,      WriteToCache | PrintValue, &tZQCAL);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctZQCS,       WriteToCache | PrintValue, &tZQCS);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctZQCSPeriod, WriteToCache | PrintValue, &ZQCSPeriod);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function returns the tZQCS value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] tCK      - DCLK period in femtoseconds.

  @retval The tZQCS value.
**/
UINT32
tZQCSGet (
  IN MrcParameters *const MrcData,
  IN UINT32               tCK
  )
{
  UINT32 tZQCS;

  tZQCS = 0;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_DDR4:
      tZQCS = tZQCS_DDR4;
      break;

    case MRC_DDR_TYPE_LPDDR4:
      tZQCS = DIVIDECEIL (tZQLAT_FS, tCK);
      tZQCS = MAX (tZQCS, tZQLAT_LPDDR4_CK_MIN);
      break;

    default:
      tZQCS = 0;
      break;

  }
  return tZQCS;
}

/**
  This function configures the TC_MR2_SHADDOW register and its fields.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - Dimm to work on.
  @param[in] Mr2Value        - The value of MR2 to setup.

  @retval Nothing.
**/
void
SetTcMr2ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         Dimm,
  IN UINT32               Mr2Value
  )
{
  MrcDimmOut                          *DimmOut;
  INT64                               GetSetVal;

  DimmOut = &MrcData->Outputs.Controller[0].Channel[Channel].Dimm[Dimm];

  if (DimmOut->SelfRefreshTemp && !DimmOut->AutoSelfRefresh) {
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSrtAvail, ReadNoCache, &GetSetVal);
    GetSetVal = GetSetVal | ((INT64) (1 << Dimm));
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSrtAvail, WriteNoCache | PrintValue, &GetSetVal);
  }

  GetSetVal = Mr2Value & 0x3FFF;  // Bits [13:0] of MR2
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccMr2Shadow, WriteNoCache | PrintValue, &GetSetVal);
}


/**
  This function configures the TC_MR4_SHADDOW register and its fields.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Mr4Value        - The value of MR4 to setup.

  @retval Nothing.
**/
void
SetTcMr4ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN UINT32               Mr4Value
  )
{
  UINT32                              Offset;

  Offset = CH0_CR_TC_MR4_SHADDOW_REG +
          (CH1_CR_TC_MR4_SHADDOW_REG - CH0_CR_TC_MR4_SHADDOW_REG) * Channel;
  MrcWriteCR (MrcData, Offset, (Mr4Value & 0x3FF3));

}


/**
  This function configures the DDR4 Mr shadow registers.

  @param[in] MrcData         - Include all MRC global data.

  @retval Nothing.
**/
void
MrcSetMrShadows (
  IN MrcParameters *const MrcData
  )
{
  MrcChannelOut    *ChannelOut;
  MrcControllerOut *ControllerOut;
  MrcOutput        *Outputs;
  MrcRankOut       *RankOut;
  UINT32            Channel;
  UINT32            Rank;
  UINT32            Dimm;
  UINT32            RankMod2;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[CONTROLLER_0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_DIMM; Rank++) {
      RankMod2 = Rank % 2;
      Dimm     = Rank / MAX_RANK_IN_DIMM;
      RankOut = &ChannelOut->Dimm[Dimm].Rank[RankMod2];
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        SetTcMr4ShadowReg (MrcData, Channel, RankOut->MR[mrMR4]);
        SetTcMr2ShadowReg (MrcData, Channel, Dimm, RankOut->MR[mrMR2]);
        break;
      }
    } // for Rank
  }

}

/**
  This function executes the refresh configuration process.

  @param[in] MrcData         - Include all MRC global data.

  @retval Nothing.
**/
void
MrcRefreshConfiguration (
  IN MrcParameters *const MrcData
  )
{
  UINT8  Channel;
  INT64  GetSetVal;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      SetTcRfpRftpReg (MrcData, Channel);
      SetTcSrftpReg (MrcData, Channel);
      SetTcZqCalReg (MrcData, Channel);

      GetSetVal = 1;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccEnRefTypeDisplay, WriteNoCache, &GetSetVal);
    }
  }

  GetSetVal = SELF_REFRESH_IDLE_COUNT;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMctSrIdle, WriteNoCache, &GetSetVal);
}

