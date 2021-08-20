/** @file
  This module configures the memory controller timing parameters.

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
#include "MrcTimingConfiguration.h"
#include "MrcDdrCommon.h"
#include "MrcLpddr4.h"

#define tWRRD_LOOPBACK  11

/**
  This function returns the tCKE value for the specified frequency.

  @param[in] DdrType    - DDR type
  @param[in] Frequency  - The memory frequency.
  @param[in] tCK        - DCLK period in femtoseconds.

  @retval The tCKE value for the specified frequency.
**/
static
UINT32
tCKEValue (
  IN MrcDdrType         DdrType,
  IN const MrcFrequency Frequency,
  IN UINT32             tCK
  )
{
  UINT32 tCKE;
  UINT32 tCKELCS;

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    // CNL MC needs a MAX of (tCKE, tCKELCK, tCKELCS) to be programmed into TC_PWRDN.tCKE
    tCKE    = DIVIDECEIL (tCKE_LPDDR4_FS, tCK);
    tCKELCS = DIVIDECEIL (MRC_LP4_tCKELCS_PS * 1000, tCK); // tCKELCK is the same
    tCKE = MAX (tCKE, tCKELCS);
  } else {
    // DDR4
    if (Frequency <= f800) {
      tCKE = TCKE_800;
    } else if (Frequency <= f1067) {
      tCKE = TCKE_1067;
    } else if (Frequency <= f1333) {
      tCKE = TCKE_1333;
    } else if (Frequency <= f1600) {
      tCKE = TCKE_1600;
    } else if (Frequency <= f1867) {
      tCKE = TCKE_1867;
    } else if (Frequency <= f2133) {
      tCKE = TCKE_2133;
    } else if (Frequency <= f2400) {
      tCKE = TCKE_2400;
    } else if (Frequency <= f2667) {
      tCKE = TCKE_2667;
    } else if (Frequency <= f2800) {
      tCKE = TCKE_2800;
    } else if (Frequency <= f2933) {
      tCKE = TCKE_2933;
    } else if (Frequency <= f3000) {
      tCKE = TCKE_3000;
    } else {
      tCKE = TCKE_3200;
    }
  }

  return tCKE;
}

/**
  This function returns the tXPDLL value for the specified frequency.

  @param[in] tCK        - DCLK period in femtoseconds.

  @retval The tXPDLL value for the specified frequency.
**/
static
UINT32
tXPDLLValue (
  IN UINT32  tCK
  )
{
  return DIVIDECEIL (tXPDLL_FS, tCK);
}

/**
  This function returns the tXP value for the specified frequency.

  @param[in] DdrType   - DDR type
  @param[in] Frequency - The memory frequency.
  @param[in] tCK       - DCLK period in femtoseconds.
  @param[in] NMode     - Command mode to lookup.

  @retval The tXP value for the specified frequency.
**/
UINT32
tXPValue (
  IN MrcDdrType         DdrType,
  IN const MrcFrequency Frequency,
  IN UINT32             tCK,
  IN UINT8              NMode
  )
{
  UINT32 tXP;

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    // tXP value for LPDDR4: max(7.5ns, 5nCK)
    tXP = DIVIDECEIL (tXP_LPDDR4_FS, tCK);
    tXP = MAX (tXP, 5);
  } else { // DDR4
    tXP = DIVIDECEIL (tXP_DDR4_FS, tCK);
  }

  return (tXP);
}

/**
  This function returns the tAONPD value for the specified frequency.

  @param[in] tCK       - DCLK period in femtoseconds.

  @retval The tAONPD value for the specified frequency.
**/
static
UINT32
tAONPDValue (
  IN UINT32  tCK
  )
{
  return 30;
}

/**
  This function sets up the following MC Timing
  registers: TC_PRE, TC_ACT, TC_ODT

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.

**/
static
void
SetTcPreActOdt (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcTiming         *Timing;
  MrcDdrType        DdrType;
  INT64             tWRPRE;
  INT64             tRDPRE;
  INT64             tRP;
  INT64             tCWL;
  INT64             tAONPD;
  INT64             tRPab_ext;
  INT64             tRAS;
  INT64             tFAW;
  INT64             tRRDsg;
  INT64             tRRDdg;
  INT64             DeratingExt;
  INT64             tCL;
  INT64             OdtReadDelay;
  INT64             OdtReadDuration;
  INT64             WriteEarlyOdt;
  INT64             OdtWriteDelay;
  INT64             OdtWriteDuration;
  INT64             tPPD;
  UINT32            tCKps;
  UINT8             MinTiming;
  BOOLEAN           IsLpddr4;
  BOOLEAN           IsDdr4;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  IsLpddr4    = (DdrType == MRC_DDR_TYPE_LPDDR4);
  IsDdr4      = (DdrType == MRC_DDR_TYPE_DDR4);
  tCKps       = Outputs->tCKps;

  OdtReadDuration   = 0;
  OdtWriteDelay     = 0;
  OdtWriteDuration  = 0;
  tRPab_ext         = 0;
  WriteEarlyOdt     = 0;
  // tRP is equal to tRCD
  tRP = Timing->tRCDtRP;

  // tWRPRE is = tCWL + BL/2 + tWR
  tWRPRE = Timing->tCWL + Outputs->BurstLength + Timing->tWR;
  tWRPRE = RANGE (tWRPRE, tWRPRE_MIN, tWRPRE_MAX);

  tRP = RANGE (tRP, tRP_MIN, tRP_MAX);
  if (IsLpddr4) {
    tRPab_ext = (INT32) (Timing->tRPab) - tRP;
  }

  tRAS    = RANGE (Timing->tRAS, tRAS_MIN, tRAS_MAX);
  tRDPRE  = RANGE (Timing->tRTP, tRDPRE_MIN, tRDPRE_MAX);
  tPPD    = (IsLpddr4) ? MRC_LP4_tPPD_ALL_FREQ : 0;
  tFAW    = RANGE (Timing->tFAW, tFAW_MIN, tFAW_MAX);

  // Setup tRRD_sg and tRRD_dg based on DdrType.
  if (IsDdr4) {
    tRRDsg = Timing->tRRD_L;
    tRRDdg = Timing->tRRD_S;
  } else {
    tRRDsg = Timing->tRRD;
    tRRDdg = Timing->tRRD;
  }

  tRRDsg = RANGE (tRRDsg, tRRD_MIN, tRRD_SG_MAX);
  tRRDdg = RANGE (tRRDdg, tRRD_MIN, tRRD_DG_MAX);

  // Derating is 1.875ns for all frequencies LP3/4. Max value is 4 clocks.
  DeratingExt = (IsLpddr4) ? DIVIDECEIL (DERATE_TIMING_PS, tCKps) : 0;
  DeratingExt = MIN (DeratingExt, 4);

  tCL   = RANGE (Timing->tCL, tCL_MIN, tCL_MAX);
  tCWL  = Timing->tCWL;

  if (Inputs->LoopBackTest) {
    // Set tCWL = tWRRD_sr + tCL, so that WR data will be in place
    tCWL = tCL + tWRRD_LOOPBACK;
  }

  if (IsLpddr4) {
    // Timing->tCWL has 1 extra clock because of tDQSS - subtract it here.
    tCWL--;
  }

  MinTiming = (IsDdr4) ? tCWL_MIN_DDR4 : tCWL_MIN_LP4;
  tCWL            = RANGE (tCWL, MinTiming, tCWL_MAX);
  OdtReadDelay    = (Timing->tCL >= Timing->tCWL) ? Timing->tCL - Timing->tCWL : 0;
  tAONPD          = tAONPDValue (Timing->tCK);

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRP,             WriteToCache | PrintValue, &tRP);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRPabExt,        WriteToCache | PrintValue, &tRPab_ext);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRAS,            WriteToCache | PrintValue, &tRAS);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDPRE,          WriteToCache | PrintValue, &tRDPRE);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRPRE,          WriteToCache | PrintValue, &tWRPRE);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctFAW,            WriteToCache | PrintValue, &tFAW);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRRDsg,          WriteToCache | PrintValue, &tRRDsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRRDdg,          WriteToCache | PrintValue, &tRRDdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctLpDeratingExt,  WriteToCache | PrintValue, &DeratingExt);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtRdDuration,  WriteToCache | PrintValue, &OdtReadDuration);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtRdDelay,     WriteToCache | PrintValue, &OdtReadDelay);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtWrDuration,  WriteToCache | PrintValue, &OdtWriteDuration);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctOdtWrDelay,     WriteToCache | PrintValue, &OdtWriteDelay);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWrEarlyOdt,     WriteToCache | PrintValue, &WriteEarlyOdt);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCL,             WriteToCache | PrintValue, &tCL);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCWL,            WriteToCache | PrintValue, &tCWL);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctAONPD,          WriteToCache | PrintValue, &tAONPD);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctPPD,            WriteToCache | PrintValue, &tPPD);
  MrcFlushRegisterCachedData (MrcData);
  // Need to program this the same as tRP
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRCDwr,          WriteNoCache | PrintValue, &tRP);
}

/**
  Update XARB_TC_BUBBLE_INJ for the given channel according to the current turnaround values.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
void
SetTcBubbleInjector (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  INT64     tRDRDsg;
  INT64     tRDRDdg;
  INT64     tRDRDdr;
  INT64     tRDRDdd;
  INT64     tRDWRsg;
  INT64     tRDWRdg;
  INT64     tRDWRdr;
  INT64     tRDWRdd;
  INT64     tWRRDsg;
  INT64     tWRRDdg;
  INT64     tWRRDdr;
  INT64     tWRRDdd;
  INT64     tWRWRsg;
  INT64     tWRWRdg;
  INT64     tWRWRdr;
  INT64     tWRWRdd;
  INT64     MaxValue;
  UINT32    Offset;
  CH0_CR_XARB_TC_BUBBLE_INJ_STRUCT  TcBubbleInj;

  TcBubbleInj.Data = 0;

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, ReadUncached, &tRDRDsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, ReadUncached, &tRDRDdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadUncached, &tRDRDdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, ReadUncached, &tRDRDdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, ReadUncached, &tRDWRsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdg, ReadUncached, &tRDWRdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, ReadUncached, &tRDWRdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, ReadUncached, &tRDWRdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDsg, ReadUncached, &tWRRDsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdg, ReadUncached, &tWRRDdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, ReadUncached, &tWRRDdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, ReadUncached, &tWRRDdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRsg, ReadUncached, &tWRWRsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdg, ReadUncached, &tWRWRdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, ReadUncached, &tWRWRdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, ReadUncached, &tWRWRdd);

  // tRDRD
  MaxValue = MAX (tRDRDsg,  tRDRDdg);
  MaxValue = MAX (MaxValue, tRDRDdr);
  TcBubbleInj.Bits.max_tRDRD = (UINT32) MAX (MaxValue, tRDRDdd);

  // tRDWR
  MaxValue = MAX (tRDWRsg,  tRDWRdg);
  MaxValue = MAX (MaxValue, tRDWRdr);
  TcBubbleInj.Bits.max_tRDWR = (UINT32) MAX (MaxValue, tRDWRdd);

  // tWRRD
  MaxValue = MAX (tWRRDsg,  tWRRDdg);
  MaxValue = MAX (MaxValue, tWRRDdr);
  TcBubbleInj.Bits.max_tWRRD = (UINT32) MAX (MaxValue, tWRRDdd);

  // tWRWR
  MaxValue = MAX (tWRWRsg,  tWRWRdg);
  MaxValue = MAX (MaxValue, tWRWRdr);
  TcBubbleInj.Bits.max_tWRWR = (UINT32) MAX (MaxValue, tWRWRdd);

  // MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "C%d_XARB_TC_BUBBLE_INJ = 0x%X\n", Channel, TcBubbleInj.Data);
  Offset = OFFSET_CALC_CH (CH0_CR_XARB_TC_BUBBLE_INJ_REG, CH1_CR_XARB_TC_BUBBLE_INJ_REG, Channel);
  MrcWriteCR (MrcData, Offset, TcBubbleInj.Data);
}

/**
  This function sets up the Turnaround timing registers:
  TC_RDRD, TC_RDWR, TC_WRRD and TC_WRWR.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
static
void
SetTcTurnAround (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32        Channel
  )
{
  const MrcInput                *Inputs;
  MrcOutput                     *Outputs;
  MrcChannelOut                 *ChannelOut;
  MrcTiming                     *Timing;
  MrcFrequency                  DdrFreq;
  INT64                         tWRRDsg;
  INT64                         tWRRDdg;
  INT64                         tWRRDdr;
  INT64                         tWRRDdd;
  INT64                         tRDRDsg;
  INT64                         tRDRDdg;
  INT64                         tRDRDdr;
  INT64                         tRDRDdd;
  INT64                         tRDWRsg;
  INT64                         tRDWRdg;
  INT64                         tRDWRdr;
  INT64                         tRDWRdd;
  INT64                         tWRWRsg;
  INT64                         tWRWRdg;
  INT64                         tWRWRdr;
  INT64                         tWRWRdd;
  UINT32                        tCKps;
  UINT32                        Value;
  UINT32                        tWTR_L;
  UINT32                        tWTR_S;
  UINT32                        tCCD_L;
  UINT32                        tCCD_S;
  UINT32                        tRPRE;
  UINT32                        tWPRE;
  UINT32                        GsmMode;
  UINT16                        tCL;
  UINT16                        tCWL;
  UINT16                        tRPST;
  UINT8                         tODTLon;
  UINT8                         tODTLoff;
  UINT8                         BurstLength;
  UINT8                         TatDelta;
  BOOLEAN                       IsLpddr4;
  BOOLEAN                       IsDdr4;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  IsLpddr4    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  IsDdr4      = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  GsmMode     = WriteToCache | PrintValue;
  DdrFreq     = (IsLpddr4 && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;

  // Setup variable parameters that impact the timings set below.
  tRPRE       = (IsLpddr4) ? TRPRE_ALL_FREQ_LP4 : TRPRE_ALL_FREQ;
  tWPRE       = (IsLpddr4) ? TWPRE_ALL_FREQ_LP4 : TWPRE_ALL_FREQ;
  tCWL        = Timing->tCWL;
  tCL         = Timing->tCL;
  tODTLon     = MrcGetOdtlTimingLpddr4 (DdrFreq, Lp4WlSetB, Lp4OdtlOn); // LPDDR4 timing. WL Set is statically configured to Set B.
  tODTLoff    = MrcGetOdtlTimingLpddr4 (DdrFreq, Lp4WlSetB, Lp4OdtlOff); // LPDDR4 timing. WL Set is statically configured to Set B.
  BurstLength = Outputs->BurstLength;
  tRPST       = 1; // LPDDR4 Read Post-amble.  Statically set to .05*tCK.
  tCKps       = Outputs->tCKps;

  if (Inputs->LoopBackTest) {
    // Set tCWL = tWRRD_sr + tCL, so that WR data will be in place
    tCWL = tCL + tWRRD_LOOPBACK;
  }

  //-----------------------------------
  // Calculate tRDRD
  //-----------------------------------
  if (IsDdr4) {
    // Use tCCD_L for tRDRD_sg
    // Use tCCD_S for tRDRD_dg
    tCCD_L = Timing->tCCD_L;
    tCCD_S = TCCD_ALL_FREQ;
  } else { // LPDDR4
    tCCD_S = tCCD_L = MRC_LP4_tCCD_ALL_FREQ;
  }

  tRDRDsg = MIN (tCCD_L, tRDRD_MAX);
  tRDRDdg = MIN (tCCD_S, tRDRD_MAX);

  //
  // Calculate tRDRD_dr = BL/2 + max(tRTR, ODT(R,R,DR)) + tRPRE
  // LPDDR4 also includes a factor of (tDQSCK_min - tDQSCK_max)
  //
  Value = BurstLength + 1 + tRPRE;
  if (IsLpddr4) {
    Value += DIVIDECEIL ((tDQSCK_MAX_LP4 - tDQSCK_MIN_LP4), tCKps);
    Value += Outputs->Gear2 ? 3 : 1;
  } else {
    Value += Outputs->Gear2 ? 2 : 1;
  }

  tRDRDdr = MIN (Value, tRDRD_MAX);

  // Calculate tRDRD_dd = BL/2 + max(tRTR, ODT(R,R,DD)) + tRPRE
  tRDRDdd = MIN (Value + 1, tRDRD_MAX);

  //-----------------------------------
  // Calculate tRDWR = tCL-tCWL+tCCD+tWPRE+max(tRWSR,ODT(R,W,SR))
  // tWPRE - Write Preamble
  //-----------------------------------
  if (IsDdr4) {
    Value = tCL - tCWL + tCCD_S + tWPRE + 2;
    // Add 1 for frequencies above 1067.
    if (DdrFreq > f1067) {
      Value++;
    }

    // Add 1 for frequencies above 1600.
    if (DdrFreq > f1600) {
      Value++;
    }
  } else { // Lpddr4
    // tCCD_S value will match "BL / 2" in the TA Calculation.
    // Common components for LP4
    Value = tCL + DIVIDECEIL (tDQSCK_MAX_LP4, tCKps) + tCCD_S + tRPST;
    if (Outputs->DramDqOdtEn) {
      // ODT On  : RL + RU (tDQSCK (max) / tCK) + BL / 2 + tRPST - ODTLon - RD (tODTon, min / tCK) + 1
      Value = Value  - tODTLon - (MRC_LP4_tODT_ON_MIN / tCKps) + 1;
    } else {
      // ODT Off : RL - WL + RU (tDQSCK (max) / tCK) + BL / 2 + tRPST + tWPRE
      Value = Value - tCWL + tWPRE;
    }
  }
  if (Inputs->LoopBackTest) {
    Value = MAX (Value, 32);    // tRDWR_sr should be at least 32 in loopback test mode, because we relax tRDRD_sr in WRTC
  }

  tRDWRsg = MIN (Value, tRDWR_MAX);
  tRDWRdg = MIN (Value, tRDWR_MAX);

  // Calculate tRDWR_dr = tCL-tCWL+tCCD+tWPRE+max(tRWDR,ODT(R,W,DR))
  tRDWRdr = MIN (Value, tRDWR_MAX);

  // Calculate tRDWR_dd = tCL-tCWL+tCCD+tWPRE+max(tRWDD,ODT(R,W,DD))
  tRDWRdd = MIN (Value + 1, tRDWR_MAX);

  //-----------------------------------
  // Calculate tWRRD = tCWL + BL/2 + tWTR + max(tWrCAS2RdCAS_sr,ODT(W,R,SR)).
  //-----------------------------------
  if (IsDdr4) {
    tWTR_S = Timing->tWTR_S;
    tWTR_L = Timing->tWTR_L;
  } else {
    tWTR_S = tWTR_L = Timing->tWTR;
  }
  Value = Timing->tCWL + BurstLength + tWTR_L + 2;
  tWRRDsg = MIN (Value, tWRRD_SG_MAX);

  Value = Timing->tCWL + BurstLength + tWTR_S + 2;
  tWRRDdg = MIN (Value, tWRRD_DG_MAX);

  if (Inputs->LoopBackTest) {
    tWRRDsg = tWRRDdg = tWRRD_LOOPBACK;  // Decrease WRRD
  }

  // Calculate tWRRD_dr = tCWL - tCL + BL/2 + max(tWRDRDR,ODT(W,R,DR)) + tRPRE
  tWRRDdr = (INT32) (Timing->tCWL) - Timing->tCL + BurstLength + 2 + tRPRE;

  if (IsDdr4 && (DdrFreq >= 2933) && !Outputs->Gear2) {
    // DDR4 Gear1 2933 and above: add one more clock to avoid overlap of WR burst and senseamp enable of the subsequent RD
    tWRRDdr += 1;
  }
  tWRRDdr = MIN (tWRRDdr, tWRRD_MAX);
  tWRRDdr = MAX (tWRRDdr, 4);

  // Calculate tWRRD_dd = tCWL - tCL + BL/2 + max(tWRDRDD,ODT(W,R,DD)) + tRPRE
  tWRRDdd = tWRRDdr;

  //-----------------------------------
  // Calculate tWRWR
  //-----------------------------------
  tWRWRsg = MIN (tCCD_L, tWRWR_MAX);
  tWRWRdg = MIN (tCCD_S, tWRWR_MAX);

  if (IsLpddr4 && (Outputs->DramDqOdtEn)) {
    // JEDEC Spec Table Table X3: Time between to ranks should ensure ODT switch doesn't overlap.
    // ODTLoff + RU (tODToff.MAX / tCK) - ODTLon - RD (tODTon.Min / tCK) + Electrical Guardband
    Value = tODTLoff - tODTLon + DIVIDECEIL ((MRC_LP4_tODT_Off_MAX - MRC_LP4_tODT_ON_MIN), tCKps) + 1;
  } else
  {
    // DDR4, LPDDR4 no ODT
    // Calculate tWRWR_dr = BL/2 + max(tWWDR,ODT(W,W,DR)) + tWPRE
    Value = BurstLength + 2 + tWPRE;
  }
  tWRWRdr = MIN (Value, tWRWR_MAX);

  // Calculate tWRWR_dd = BL/2 + max(tWWDD,ODT(W,W,DR)) + tWPRE
  tWRWRdd = MIN (Value, tWRWR_MAX);

  //-----------------------------------
  // Increase TAT values for safe mode
  //-----------------------------------
  TatDelta = Inputs->TatDelta;
  // Need to keep back-to-back tRDRD for the same rank, for ReadMPR, so don't touch tRDRD_sg/dg
  tRDRDdr += TatDelta;
  tRDRDdd += TatDelta;

  tRDWRsg += TatDelta;
  tRDWRdg += TatDelta;
  tRDWRdr += TatDelta;
  tRDWRdd += TatDelta;

  tWRRDsg += TatDelta;
  tWRRDdg += TatDelta;
  tWRRDdr += TatDelta;
  tWRRDdd += TatDelta;

  tWRWRsg += TatDelta;
  tWRWRdg += TatDelta;
  tWRWRdr += TatDelta;
  tWRWRdd += TatDelta;

  if (Outputs->Gear2) {
    tRDRDsg = 2 * (DIVIDECEIL ((UINT32) tRDRDsg, 2));
    tRDRDdg = 2 * (DIVIDECEIL ((UINT32) tRDRDdg, 2));
    tRDRDdr = 2 * (DIVIDECEIL ((UINT32) tRDRDdr, 2));
    tRDRDdd = 2 * (DIVIDECEIL ((UINT32) tRDRDdd, 2));
    tRDWRsg = 2 * (DIVIDECEIL ((UINT32) tRDWRsg, 2));
    tRDWRdg = 2 * (DIVIDECEIL ((UINT32) tRDWRdg, 2));
    tRDWRdr = 2 * (DIVIDECEIL ((UINT32) tRDWRdr, 2));
    tRDWRdd = 2 * (DIVIDECEIL ((UINT32) tRDWRdd, 2));
    tWRRDsg = 2 * (DIVIDECEIL ((UINT32) tWRRDsg, 2));
    tWRRDdg = 2 * (DIVIDECEIL ((UINT32) tWRRDdg, 2));
    tWRRDdr = 2 * (DIVIDECEIL ((UINT32) tWRRDdr, 2));
    tWRRDdd = 2 * (DIVIDECEIL ((UINT32) tWRRDdd, 2));
    tWRWRsg = 2 * (DIVIDECEIL ((UINT32) tWRWRsg, 2));
    tWRWRdg = 2 * (DIVIDECEIL ((UINT32) tWRWRdg, 2));
    tWRWRdr = 2 * (DIVIDECEIL ((UINT32) tWRWRdr, 2));
    tWRWRdd = 2 * (DIVIDECEIL ((UINT32) tWRWRdd, 2));
  }

  // Cache Values and write to hardware
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, GsmMode, &tRDRDsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, GsmMode, &tRDRDdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, GsmMode, &tRDRDdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, GsmMode, &tRDRDdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, GsmMode, &tRDWRsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdg, GsmMode, &tRDWRdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, GsmMode, &tRDWRdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, GsmMode, &tRDWRdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDsg, GsmMode, &tWRRDsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdg, GsmMode, &tWRRDdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, GsmMode, &tWRRDdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, GsmMode, &tWRRDdd);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRsg, GsmMode, &tWRWRsg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdg, GsmMode, &tWRWRdg);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, GsmMode, &tWRWRdr);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, GsmMode, &tWRWRdd);
  MrcFlushRegisterCachedData (MrcData);

  // Must update the XARB bubble injector when TAT values change
  SetTcBubbleInjector (MrcData, Channel);
}

/**
  This function sets up the TC_PWRDN register.
  Also programs TC_LPDDR4_MISC.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.

  @retval Nothing.
**/
static
void
SetTcPwrdwn (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Channel
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcTiming       *Timing;
  MrcDdrType      DdrType;
  MrcFrequency    DdrFreq;
  INT64           tCKE;
  INT64           tXP;
  INT64           tXPDLL;
  INT64           tPRPDEN;
  INT64           tRDPDEN;
  INT64           tWRPDEN;
  UINT32          tCKps;
  UINT32          tCK;
  UINT32          MinVal;
  UINT32          MaxVal;
  UINT32          Offset;
  BOOLEAN         IsLpddr4;
  CH0_CR_TC_LPDDR4_MISC_STRUCT  TcLpddr4Misc;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  tCK         = Timing->tCK;
  tCKps       = Outputs->tCKps;
  IsLpddr4    = (DdrType == MRC_DDR_TYPE_LPDDR4);
  DdrFreq     = (IsLpddr4 && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;

  tCKE    = tCKEValue (DdrType, DdrFreq, tCK);
  MaxVal  = tCKE_MAX;
  tCKE    = RANGE (tCKE, tCKE_MIN, MaxVal);

  tXP     = tXPValue (DdrType, DdrFreq, tCK, 3);
  MinVal  = tXP_MIN;
  MaxVal  = tXP_MAX;
  tXP     = RANGE (tXP, MinVal, MaxVal);

  tXPDLL = tXPDLLValue (tCK);
  tXPDLL = RANGE (tXPDLL, tXPDLL_MIN, tXPDLL_MAX);

  tPRPDEN = (DdrFreq < f2133) ? 1 : 2;

  // Calculate tRDPDEN = tCL + 1 + BL/2
  tRDPDEN = Timing->tCL + 1 + Outputs->BurstLength;
  if (IsLpddr4) {
    tRDPDEN += DIVIDECEIL (tDQSCK_MAX_LP4, tCKps);
  }
  tRDPDEN = RANGE (tRDPDEN, tRDPDEN_MIN, tRDPDEN_MAX);

  // Calculate tWRPDEN = tCWL + BL/2 + tWR
  tWRPDEN = Timing->tCWL + Outputs->BurstLength + Timing->tWR;
  MaxVal  = tWRPDEN_MAX;
  tWRPDEN = RANGE (tWRPDEN, tWRPDEN_MIN, MaxVal);

  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCKE,    WriteToCache | GSM_PRINT_VAL, &tCKE);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctXP,     WriteToCache | GSM_PRINT_VAL, &tXP);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctXPDLL,  WriteToCache | GSM_PRINT_VAL, &tXPDLL);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctPRPDEN, WriteToCache | GSM_PRINT_VAL, &tPRPDEN);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDPDEN, WriteToCache | GSM_PRINT_VAL, &tRDPDEN);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRPDEN, WriteToCache | GSM_PRINT_VAL, &tWRPDEN);
  MrcFlushRegisterCachedData (MrcData);

  // Delay time from OSC stop to MR18/19 Readout. Value = Max(40ns,8nCK)
  // This is the only field in this register, and we only program it once, so no GetSet.
  if (!Inputs->IclA0) {
    Offset = OFFSET_CALC_CH (CH0_CR_TC_LPDDR4_MISC_REG, CH1_CR_TC_LPDDR4_MISC_REG, Channel);
    TcLpddr4Misc.Data = 0;
    TcLpddr4Misc.Bits.tOSCO = DIVIDECEIL (MRC_LP4_tOSCO_FS, tCK);
    TcLpddr4Misc.Bits.tOSCO += 15;
    MrcWriteCR (MrcData, Offset, TcLpddr4Misc.Data);
  }
}

/**
  This function configures the memory controller timings.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcTimingConfiguration (
  IN MrcParameters *const MrcData
  )
{
  UINT8 Channel;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      // Setup TC_PRE, TC_ACT and TC_ODT registers
      SetTcPreActOdt (MrcData, Channel);
      // Setup turnaround timings
      SetTcTurnAround (MrcData, Channel);
      // Setup TC_PWRDWN register
      SetTcPwrdwn (MrcData, Channel);
    }
  }

  // Check RawCard Types and adjust Read ODT if needed
  RdOdtStretch (MrcData);

  return;
}

/**
  This function sets up the Read ODTD values based on RawCard types and adjusts the tDRRD2RD, tDDRD2RD, tDRRD2WR and tDDRD2WR

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
RdOdtStretch (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug              *Debug;
  const MrcInput        *Inputs;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  UINT8                 Channel;
  UINT8                 ChBitMask;
  UINT8                 RankMaskCh;
  INT8                  OdtStretch;
#if SUPPORT_SODIMM == SUPPORT
  MrcDimmOut            *DimmOut;
  BOOLEAN               SoDimm;
  UINT8                 Dimm;
  UINT8                 DimmRawCardType[MAX_DIMMS_IN_CHANNEL] = {0};
#endif //SUPPORT_SODIMM == SUPPORT

  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  ControllerOut    = &Outputs->Controller[0];

  ChBitMask = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    if (ChannelOut->ValidRankBitMask && (ChannelOut->DimmCount == 2)) {
      ChBitMask |= (MRC_BIT0 << Channel);
    }
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!((MRC_BIT0 << Channel) & ChBitMask)) {
      // Skip any channels that do not have 2 DIMMs populated
      continue;
    }

    ChannelOut    = &ControllerOut->Channel[Channel];
    RankMaskCh = ChannelOut->ValidRankBitMask;
    // Start with the most aggressive setting
    OdtStretch = 6;

#if SUPPORT_SODIMM == SUPPORT
    SoDimm = FALSE;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      if ((DimmOut->ModuleType == SoDimmMemoryPackage) && (SoDimm == FALSE)) {
        SoDimm = TRUE;
      }
      if (SoDimm) {
        DimmRawCardType[Dimm] = DimmOut->ReferenceRawCard;
      }
    }

    if (SoDimm) {
      if ((DimmRawCardType[0] == rcF || DimmRawCardType[1] == rcF)
          && (DimmRawCardType[0] != DimmRawCardType[1])) {
        OdtStretch = 7;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"Rd Odt Stretch F\n");
      }
    }
#endif //SUPPORT_SODIMM == SUPPORT
    // Program Rdodtd value
    UpdateTAParamOffset (MrcData, Channel, 3, 0, rdodtd, OdtStretch, 1, MRC_PRINTS_OFF, RankMaskCh);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected RdOdtD Offset for channel %d is = %d\n", Channel, OdtStretch);

#if SUPPORT_SODIMM == SUPPORT
    if (OdtStretch > 6) {
      MrcTatStretch (MrcData, Channel, rdodtd, OdtStretch - 6, TRUE);
    } else {
      // @todo Is this needed for ICL?
      // Add 1 for ODT read duration for 2DPC
      if (Inputs->CpuModel != cmICL_ULX_ULT) {
        UpdateTAParamOffset (MrcData, Channel, 3, 0, rdodtd, 8, 1, MRC_PRINTS_OFF, RankMaskCh);
      }
    }
#endif //SUPPORT_SODIMM == SUPPORT
  }

}


/**
  This function adjusts the relevant TAT when changing Read or Write ODT duration.
  TAT list rdOdt = { drrd2rd, ddrd2rd, drrd2wr, ddrd2wr, srrd2wr_sg, srrd2wr_dg };
  TAT list wrOdt = { drwr2wr, ddwr2wr, drwr2rd, ddwr2rd, srwr2rd_sg, srwr2rd_dg };

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Channel - Channel select.
  @param[in]      OdtType - rdodtd or wrodtd.
  @param[in]      Offset  - signed offset.
  @param[in]      UpdateHost - Switch to update the host struct with the new value.

  @retval Nothing.
**/
void
MrcTatStretch (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                OdtType,
  IN     INT8                 Offset,
  IN     BOOLEAN              UpdateHost
  )
{
  INT64                 GetSetVal;
  UINT32                GsmMode;

  GsmMode = ForceWriteOffsetUncached;
  if (UpdateHost) {
    GsmMode |= WriteCached;
  }

#if 0 // This code is used for register cache debug only.
#ifdef MRC_DEBUG_PRINT
  GsmMode |= GSM_PRINT_VAL;
#endif
#endif

  GetSetVal = Offset;

  if (OdtType == rdodtd) {
    // Program Different Rank RD 2 RD value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, GsmMode, &GetSetVal);

    // Program Different DIMM RD 2 RD value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, GsmMode, &GetSetVal);

    // Program Different Rank RD 2 WR value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, GsmMode, &GetSetVal);

    // Program Different DIMM RD 2 WR value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, GsmMode, &GetSetVal);

    // Program Same Rank RD 2 WR sg value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRsg, GsmMode, &GetSetVal);

    // Program Same Rank RD 2 WR dg value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdg, GsmMode, &GetSetVal);
  } else if (OdtType == wrodtd) {
    // Program Different Rank WR 2 WR value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, GsmMode, &GetSetVal);

    // Program Different DIMM WR 2 WR value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, GsmMode, &GetSetVal);

    // Program Different Rank WR 2 RD value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, GsmMode, &GetSetVal);

    // Program Different DIMM WR 2 RD value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, GsmMode, &GetSetVal);

    // Program Same Rank WR 2 RD sg value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDsg, GsmMode, &GetSetVal);

    // Program Same Rank WR 2 RD dg value
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdg, GsmMode, &GetSetVal);
  }
  // Must update the XARB bubble injector when TAT values change
  SetTcBubbleInjector (MrcData, Channel);
}
