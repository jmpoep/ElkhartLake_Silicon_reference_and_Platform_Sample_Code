/** @file
  This module sets the memory controller refresh parameters.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

  @retval UINT32 - tXSR in tCK or WCK (LP5).
**/
static
UINT32
tXSRGet (
  IN MrcParameters *const MrcData,
  IN MrcTiming *const     Timing
  )
{
  MrcOutput *Outputs;
  UINT32    tXSRVal;
  UINT32    MinCK;
  UINT32    tXSOffset;
  UINT32    tCK;
  BOOLEAN   Lpddr;

  Outputs = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;
  tCK   = Timing->tCK;
  //
  // Units here are in Fempto Seconds.
  // 7.5ns for LP4/5, rest are 10 ns.
  //
  tXSOffset = (Lpddr) ? (7500 * 1000) : (10 * 1000 * 1000);
  tXSOffset = DIVIDECEIL (tXSOffset, tCK);
  MinCK = (Lpddr) ? 2 : 0;
  //
  // Current LPDDR SPD places tRFCab in tRFC entry.
  //
  tXSRVal = Timing->tRFC + tXSOffset;
  tXSRVal = MAX (tXSRVal, MinCK);

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5) {
    // Scale to WCK
    tXSRVal *= 4;
  }

  return tXSRVal;
}

/**
  This function returns the tXSDLL in DCLKs based on DDR Type, and Frequency.
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
    } else if (Frequency <= f2667) {
      tXSDLLVal = tDLLK_DDR4_2667;
    } else if (Frequency <= f2933) {
      tXSDLLVal = tDLLK_DDR4_2933;
    } else {
      tXSDLLVal = tDLLK_DDR4_MAX;
    }
  } else {
    //
    // No DLL in LPDDR4/5.  Use tXSR.
    //
    tXSDLLVal = tXSR;
  }

  return tXSDLLVal;
}

/**
  This function configures refresh parameters:
    tREFI, tRFC, tREFIx9, OREF_RI, tRFCpb

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to configure.

  @retval Nothing.
**/
void
SetTcRfpRftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel
  )
{
  const MrcOutput *Outputs;
  const MrcInput  *Inputs;
  const MrcTiming *TimingOut;
  MrcProfile      Profile;
  INT64           GetSetVal;
  INT64           PbrDisOnHot;
  UINT32          tRefi;
  UINT32          MathTemp;
  BOOLEAN         Lpddr5;

  Inputs    = &MrcData->Inputs;
  Profile   = Inputs->MemoryProfile;
  Outputs   = &MrcData->Outputs;
  TimingOut = &Outputs->Controller[Controller].Channel[Channel].Timing[Profile];
  Lpddr5    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);

  tRefi = (TimingOut->tREFI);
  if (Inputs->SaGv == MrcSaGvEnabled) {
    // Reduce tREFI by a factor .972
    tRefi *= 972;
    tRefi = DIVIDEROUND (tRefi, 1000);
  }
  if (Lpddr5) {
    tRefi *= 4;
  }

  GetSetVal = (tRefi * 89) / (1024 * 10);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctREFIx9, WriteNoCache | PrintValue, &GetSetVal);

  GetSetVal = 0x40;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOrefRi, WriteNoCache | PrintValue, &GetSetVal);

  GetSetVal = tRefi;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctREFI, WriteNoCache | PrintValue, &GetSetVal);

  MathTemp = TimingOut->tRFC;
  if (Lpddr5) {
    MathTemp *= 4;
  }
  GetSetVal = MathTemp;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRFC, WriteNoCache | PrintValue, &GetSetVal);

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
    case MRC_DDR_TYPE_LPDDR5:
      // PBR GetSet field is a disable
      GetSetVal = (Inputs->PerBankRefresh == 0);
      PbrDisOnHot = 1;
      break;

    default:
      PbrDisOnHot = 0;
      GetSetVal = 1;
      break;
  }
  if (Inputs->SafeMode) {
    GetSetVal = 1;
    PbrDisOnHot = 0;
  }
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccPbrDis, WriteNoCache | PrintValue, &GetSetVal);

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccPbrDisOnHot, WriteNoCache | PrintValue, &PbrDisOnHot);

  MathTemp = TimingOut->tRFCpb;
  if (Lpddr5) {
    MathTemp *= 4;
  }
  GetSetVal = MathTemp;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRFCpb, WriteNoCache | PrintValue, &GetSetVal);
}

/**
  This function configures the Self Refresh Timing Parameters for the MC:
  tZQOPER, tXS-offset, tXSDLL, and tMOD.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to configure.

  @retval Nothing.
**/
static
void
SetTcSrftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel
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
  Timing     = &Outputs->Controller[Controller].Channel[Channel].Timing[Inputs->MemoryProfile];
  tZQOPER    = tZQOPERGet (MrcData, Frequency);
  tXSR       = tXSRGet (MrcData, Timing);
  tXSDLL     = tXSDLLGet (MrcData, Frequency, tXSR);
  tMOD       = tMODGet (MrcData, Frequency, Timing->tCK);

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctXSDLL,  WriteToCache | PrintValue, &tXSDLL);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctMOD,    WriteToCache | PrintValue, &tMOD);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctZQOPER, WriteToCache | PrintValue, &tZQOPER);
  GetSetVal = tXSR;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctXSR,    WriteToCache | PrintValue, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  return;
}

/**
  This function returns the tZQOPER value.
  tZQOPER = Defines the period required for ZQCL after SR exit.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval UINT32 - tZQOPER in tCK.
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
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tZQOPER = tZQOPER_DDR4;
  } else {
    tZQOPER = 0; // Not used in LP4/LP5
  }

  return tZQOPER;
}

/**
  This function returns the tMOD value.
  tMOD = max(24nCK, 15ns) nCK change by the frequency for DDR4

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] tCK       - DCLK period in femtoseconds.

  @retval UINT32 - Timing in tCK or WCK (LP5).
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
  BOOLEAN     Lpddr;

  DdrType = MrcData->Outputs.DdrType;
  Lpddr = MrcData->Outputs.Lpddr;
  tMOD    = MRC_UINT32_MAX;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tMOD = tMOD_DDR4;
  } else if (Lpddr) {
    tMOD = DIVIDECEIL (tMOD_LPDDR_FS, tCK);
    if (DdrType == MRC_DDR_TYPE_LPDDR5) {
      // Scale to WCK
      tMOD *= 4;
    }
  }

  return tMOD;
}

/**
  This function returns the LPDDR4 tZQCAL value in DCLKs.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] tCK      - DCLK period in femtoseconds.

  @retval UINT32 - Timing in tCK or WCK (LP5).
**/
UINT32
tZQCALGet (
  IN MrcParameters *const MrcData,
  IN UINT32               tCK
  )
{
  const MRC_FUNCTION  *MrcCall;
  UINT64  tZqCalFs;
  UINT32  tZQCAL;

  MrcCall    = MrcData->Inputs.Call.Func;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      tZQCAL = DIVIDECEIL (tZQCAL_FS, tCK);
      break;

    case MRC_DDR_TYPE_LPDDR5:
      tZqCalFs = tZQCAL_LPDDR5_LOAD_16_FS + tCK - 1;
      tZQCAL = (UINT32) MrcCall->MrcDivU64x64 (tZqCalFs, tCK, NULL);
      //tZQCAL *= 4;
      break;

    default:
      tZQCAL = 0;
      break;
  }

  return tZQCAL;
}

/**
  This function configures the TC-ZQCAL register and its fields tZQCS and tZQCS_PERIOD.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to work on.

  @retval Nothing.
**/
static
void
SetTcZqCalReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
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
  Timing   = &Outputs->Controller[Controller].Channel[Channel].Timing[Inputs->MemoryProfile];

  tZQCS       = tZQCSGet (MrcData, Timing->tCK);
  ZQCSPeriod = (Outputs->Lpddr) ? ZQCS_PERIOD_LPDDR : ZQCS_PERIOD_DDR4;
  tZQCAL      = tZQCALGet (MrcData, Timing->tCK);

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctZQCAL,      WriteToCache | PrintValue, &tZQCAL);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctZQCS,       WriteToCache | PrintValue, &tZQCS);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctZQCSPeriod, WriteToCache | PrintValue, &ZQCSPeriod);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function returns the tZQCS value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] tCK      - DCLK period in femtoseconds.

  @retval UINT32 - Value in tCK or WCK (LP5).
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

    case MRC_DDR_TYPE_LPDDR5:
      tZQCS = DIVIDECEIL (tZQLAT_FS, tCK);
      tZQCS = MAX (tZQCS, tZQLAT_LPDDR5_CK_MIN);
      tZQCS *= 4;
      break;

    //@todo: DDR5
    default:
      tZQCS = 0;
      break;
  }
  return tZQCS;
}

/**
  This function configures the TC_MR2_SHADDOW register and its fields.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to work on.
  @param[in] Dimm       - Dimm to work on.
  @param[in] Mr2Value   - The value of MR2 to setup.

  @retval Nothing.
**/
void
SetTcMr2ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel,
  IN const UINT32         Dimm,
  IN UINT32               Mr2Value
  )
{
  MrcDimmOut  *DimmOut;
  INT64       GetSetVal;

  DimmOut = &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm];

  if (DimmOut->SelfRefreshTemp && !DimmOut->AutoSelfRefresh) {
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccSrtAvail, ReadNoCache, &GetSetVal);
    GetSetVal = GetSetVal | ((INT64) (1 << Dimm));
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccSrtAvail, WriteNoCache | PrintValue, &GetSetVal);
  }

  GetSetVal = Mr2Value & 0x3FFF;  // Bits [13:0] of MR2
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccMr2Shadow, WriteNoCache | PrintValue, &GetSetVal);
}


/**
  This function configures the TC_MR4_SHADDOW register and its fields.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to work on.
  @param[in] Mr4Value   - The value of MR4 to setup.

  @retval Nothing.
**/
void
SetTcMr4ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel,
  IN UINT32               Mr4Value
  )
{
  UINT32 Offset;

  //@todo: Update controller based offset.
  Offset = MC0_CH0_CR_TC_MR4_SHADDOW_REG +
          (MC0_CH1_CR_TC_MR4_SHADDOW_REG - MC0_CH0_CR_TC_MR4_SHADDOW_REG) * Channel;
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
  MrcOutput   *Outputs;
  MrcRankOut  *RankOut;
  UINT32      Controller;
  UINT32      Channel;
  UINT32      Rank;
  UINT32      Dimm;
  UINT32      RankMod2;

  Outputs = &MrcData->Outputs;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_DIMM; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          RankMod2 = Rank % 2;
          Dimm     = Rank / MAX_RANK_IN_DIMM;
          RankOut = &Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Rank[RankMod2];
          SetTcMr4ShadowReg (MrcData, Controller, Channel, RankOut->MR[mrMR4]);
          SetTcMr2ShadowReg (MrcData, Controller, Channel, Dimm, RankOut->MR[mrMR2]);
          break;
        }
      } // for Rank
    }
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
  INT64       GetSetVal;
  INT64       SrIdleCount;
  UINT32      Controller;
  UINT32      Channel;
  BOOLEAN     Lpddr;

  Lpddr = MrcData->Outputs.Lpddr;
  SrIdleCount = SELF_REFRESH_IDLE_COUNT;
  GetSetVal = 1;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      SetTcRfpRftpReg (MrcData, Controller, Channel);
      SetTcSrftpReg (MrcData, Controller, Channel);
      SetTcZqCalReg (MrcData, Controller, Channel);

      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccEnRefTypeDisplay, WriteNoCache, &GetSetVal);
    }
    MrcGetSetMc (MrcData, Controller, GsmMctSrIdle, WriteNoCache, &SrIdleCount);
  }
}

