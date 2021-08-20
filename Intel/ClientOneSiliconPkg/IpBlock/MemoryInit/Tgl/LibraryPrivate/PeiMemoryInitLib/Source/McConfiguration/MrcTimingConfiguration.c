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
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcLpddr5.h"

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
    // MC needs a MAX of (tCKE, tCKELCK, tCKELCS) to be programmed into TC_PWRDN.tCKE
    tCKE    = DIVIDECEIL (tCKE_LPDDR4_FS, tCK);
    tCKELCS = DIVIDECEIL (MRC_LP4_tCKELCS_PS * 1000, tCK); // tCKELCK is the same
    tCKE = MAX (tCKE, tCKELCS);
  } else if (DdrType == MRC_DDR_TYPE_LPDDR5) {
    // tCSPD
    tCKE = DIVIDECEIL (MRC_LP5_tCSPD_MIN, tCK);
    tCKE = MAX (tCKE, MRC_LP5_tCSPD_MIN_NCK);
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
  This function returns the tXP value for the specified frequency in tCK.

  @param[in] DdrType   - DDR type
  @param[in] tCK       - Clock period in femtoseconds.

  @retval The tXP value for the specified frequency.
**/
UINT32
tXPValue (
  IN  MrcDdrType  DdrType,
  IN  UINT32      tCK
  )
{
  UINT32 tXP;
  UINT32 MinCk;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    tXP = DIVIDECEIL (tXP_DDR4_FS, tCK);
  } else {
    //@todo DDR5
    MinCk = (DdrType == MRC_DDR_TYPE_LPDDR4) ? 5 : MRC_LP5_tXP_MIN_NCK;
    tXP = DIVIDECEIL (tXP_LPDDR_FS, tCK);
    tXP = MAX (tXP, MinCk);
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

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - 0-based index to select the Controller.
  @param[in]      Channel     - 0-based index to select the Channel.

  @retval Nothing.

**/
static
void
SetTcPreActOdt (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
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
  UINT32            tRRD;
  UINT32            BlTck;
  UINT32            TckPs;
  BOOLEAN           Lpddr;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           Lpddr5;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  Lpddr       = Outputs->Lpddr;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5      = (DdrType == MRC_DDR_TYPE_LPDDR5);
  TckPs       = Outputs->tCKps;
  BlTck       = Outputs->BurstLength;

  OdtReadDuration   = 0;
  OdtWriteDelay     = 0;
  OdtWriteDuration  = 0;
  tRPab_ext         = 0;
  WriteEarlyOdt     = 0;

  // tWRPRE is = tCWL + BL/2 + tWR
  tWRPRE = Timing->tCWL + Outputs->BurstLength + Timing->tWR;
  // LPDDR adds an addition clock
  // LPDDR5 - 4.10.4 Timing constraints for 8Bank Mode (BL32 only)
  if (Lpddr) {
    tWRPRE++;
  }
  if (Lpddr5) {
    tWRPRE = ((INT32) tWRPRE) * 4;
  }
  tWRPRE = RANGE (tWRPRE, tWRPRE_MIN, tWRPRE_MAX);

  // tRP is equal to tRCD
  tRP = Timing->tRCDtRP;
  if (Lpddr5) {
    tRP = ((INT32) tRP) * 4;
  }
  tRP = RANGE (tRP, tRP_MIN, tRP_MAX);
  if (Lpddr) {
    tRPab_ext = (INT32) (Timing->tRPab) - Timing->tRCDtRP;
    if (Lpddr5) {
      tRPab_ext = ((INT32) tRPab_ext) * 4;
    }
  }

  tRAS = Timing->tRAS;
  if (Lpddr5) {
    tRAS = ((INT32) tRAS) * 4;
  }
  tRAS  = RANGE (tRAS, tRAS_MIN, tRAS_MAX);

  // Table 38, page 150 in LP4 spec from Aug 2017.
  tRDPRE = Timing->tRTP;
  if (Lpddr5) {
    tRDPRE += BlTck;
    tRDPRE = ((INT32) tRDPRE) * 4;
  } else if (Lpddr4) {
    tRDPRE += BlTck / 2;
  }
  tRDPRE  = RANGE (tRDPRE, tRDPRE_MIN, tRDPRE_MAX);

  tPPD = MrcGetPpd (MrcData);
  if (Lpddr5) {
    tPPD = ((INT32) tPPD) * 4;
  }
  tPPD = RANGE (tPPD, tPPD_MIN, tPPD_MAX);

  tFAW = Timing->tFAW;
  if (Lpddr5) {
    tFAW = ((INT32) tFAW) * 4;
  }
  tFAW = RANGE (tFAW, tFAW_MIN, tFAW_MAX);

  // Setup tRRD_sg and tRRD_dg based on DdrType.
  if (Ddr4) {
    tRRDsg = Timing->tRRD_L;
    tRRDdg = Timing->tRRD_S;
  } else {
    tRRD = Timing->tRRD;
    if (Lpddr5) {
      tRRD *= 4;
    }
    tRRDsg = tRRD;
    tRRDdg = tRRD;
  }

  tRRDsg = RANGE (tRRDsg, tRRD_MIN, tRRD_SG_DG_MAX);
  tRRDdg = RANGE (tRRDdg, tRRD_MIN, tRRD_SG_DG_MAX);

  // Derating is 1.875ns for all frequencies LP4. Max value is 4 clocks.
  //@todo - LP5 not defined
  DeratingExt = (Lpddr) ? DIVIDECEIL (DERATE_TIMING_PS, TckPs) : 0;
  DeratingExt = MIN (DeratingExt, 4);

  tCL = Timing->tCL;
  if (Lpddr5) {
    tCL = ((INT32) tCL) * 4;
  }
  tCL   = RANGE (tCL, tCL_MIN, tCL_MAX);

  tCWL  = Timing->tCWL;
  if (Lpddr4) {
    // Timing->tCWL has 1 extra clock because of tDQSS - subtract it here.
    tCWL--;
  } else if (Lpddr5) {
    tCWL = ((INT32) tCWL) * 4;
  }
  tCWL = RANGE (tCWL, tCWL_MIN, tCWL_MAX);

  if (Ddr4) {
    OdtReadDelay = (Timing->tCL >= Timing->tCWL) ? Timing->tCL - Timing->tCWL : 0;
    tAONPD       = tAONPDValue (Timing->tCK);
  } else {
    OdtReadDelay = 0;
    tAONPD = 0;
  }

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRCD,            WriteToCache | PrintValue, &tRP);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRP,             WriteToCache | PrintValue, &tRP);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRPabExt,        WriteToCache | PrintValue, &tRPab_ext);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRAS,            WriteToCache | PrintValue, &tRAS);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDPRE,          WriteToCache | PrintValue, &tRDPRE);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRPRE,          WriteToCache | PrintValue, &tWRPRE);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctFAW,            WriteToCache | PrintValue, &tFAW);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRRDsg,          WriteToCache | PrintValue, &tRRDsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRRDdg,          WriteToCache | PrintValue, &tRRDdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctLpDeratingExt,  WriteToCache | PrintValue, &DeratingExt);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOdtRdDuration,  WriteToCache | PrintValue, &OdtReadDuration);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOdtRdDelay,     WriteToCache | PrintValue, &OdtReadDelay);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOdtWrDuration,  WriteToCache | PrintValue, &OdtWriteDuration);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctOdtWrDelay,     WriteToCache | PrintValue, &OdtWriteDelay);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWrEarlyOdt,     WriteToCache | PrintValue, &WriteEarlyOdt);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCL,             WriteToCache | PrintValue, &tCL);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCWL,            WriteToCache | PrintValue, &tCWL);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctAONPD,          WriteToCache | PrintValue, &tAONPD);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctPPD,            WriteToCache | PrintValue, &tPPD);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  Update XARB_TC_BUBBLE_INJ for the given channel according to the current turnaround values.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Controller  - 0-based index to select the Controller.
  @param[in]      Channel     - 0-based index to select the Channel.

  @retval Nothing.
**/
void
SetTcBubbleInjector (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
  IN     const UINT32         Channel
  )
{
  INT64       tRDRDsg;
  INT64       tRDRDdg;
  INT64       tRDRDdr;
  INT64       tRDRDdd;
  INT64       tRDWRsg;
  INT64       tRDWRdg;
  INT64       tRDWRdr;
  INT64       tRDWRdd;
  INT64       tWRRDsg;
  INT64       tWRRDdg;
  INT64       tWRRDdr;
  INT64       tWRRDdd;
  INT64       tWRWRsg;
  INT64       tWRWRdg;
  INT64       tWRWRdr;
  INT64       tWRWRdd;
  INT64       MaxValue;
  UINT32      Offset;
  BOOLEAN     Lpddr;
  UINT32      IpChannel;
  MC0_CH0_CR_XARB_TC_BUBBLE_INJ_STRUCT  TcBubbleInj;

  TcBubbleInj.Data = 0;
  Lpddr = MrcData->Outputs.Lpddr;

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, ReadUncached, &tRDRDsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, ReadUncached, &tRDRDdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, ReadUncached, &tRDRDdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, ReadUncached, &tRDRDdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, ReadUncached, &tRDWRsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdg, ReadUncached, &tRDWRdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, ReadUncached, &tRDWRdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, ReadUncached, &tRDWRdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDsg, ReadUncached, &tWRRDsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdg, ReadUncached, &tWRRDdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, ReadUncached, &tWRRDdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, ReadUncached, &tWRRDdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRsg, ReadUncached, &tWRWRsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdg, ReadUncached, &tWRWRdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, ReadUncached, &tWRWRdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, ReadUncached, &tWRWRdd);

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
  MaxValue = MAX (TcBubbleInj.Bits.max_tWRWR, TcBubbleInj.Bits.max_tWRRD);
  TcBubbleInj.Bits.max_tWRRD = (UINT32) RANGE (MaxValue, 4, 145); // Supported range is 4-145
  TcBubbleInj.Bits.max_tWRWR = (UINT32) RANGE (MaxValue, 4,  54); // Supported range is 4-54.

  // MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "C%d_XARB_TC_BUBBLE_INJ = 0x%X\n", Channel, TcBubbleInj.Data);
  // Caller passes system channel.  Need to convert to IP register set.
  IpChannel = LP_IP_CH (Lpddr, Channel);
  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG, MC1_CH0_CR_XARB_TC_BUBBLE_INJ_REG, Controller, MC0_CH1_CR_XARB_TC_BUBBLE_INJ_REG, IpChannel);
  MrcWriteCR (MrcData, Offset, TcBubbleInj.Data);
}

/**
  This function sets up the Turnaround timing registers:
  TC_RDRD, TC_RDWR, TC_WRRD and TC_WRWR.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - 0-based index to select the Controller.
  @param[in]      Channel     - 0-based index to select the Channel.

  @retval Nothing.
**/
static
void
SetTcTurnAround (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
  IN     const UINT32         Channel
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcTiming       *Timing;
  MrcFrequency    DdrFreq;
  INT64           tWRRDsg;
  INT64           tWRRDdg;
  INT64           tWRRDdr;
  INT64           tWRRDdd;
  INT64           tRDRDsg;
  INT64           tRDRDdg;
  INT64           tRDRDdr;
  INT64           tRDRDdd;
  INT64           tRDWRsg;
  INT64           tRDWRdg;
  INT64           tRDWRdr;
  INT64           tRDWRdd;
  INT64           tWRWRsg;
  INT64           tWRWRdg;
  INT64           tWRWRdr;
  INT64           tWRWRdd;
  UINT32          TckPs;
  UINT32          WckPs;
  UINT32          Value;
  UINT32          tWTR_L;
  UINT32          tWTR_S;
  UINT32          tCCD_L;
  UINT32          tCCD_S;
  UINT32          tRPRE;
  UINT32          tWPRE;
  UINT32          tDQSCKMax;
  UINT32          GsmMode;
  UINT32          RoundTo;
  UINT16          tCL;
  UINT16          tCWL;
  UINT16          tRPST;
  INT8            tODTLon;
  INT8            tODTLoff;
  UINT8           BurstLength;
  BOOLEAN         Lpddr5;
  BOOLEAN         Lpddr4;
  BOOLEAN         Lpddr;
  BOOLEAN         Ddr4;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  Lpddr5      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr       = Outputs->Lpddr;
  GsmMode     = WriteToCache | PrintValue;
  DdrFreq     = (Lpddr && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;

  // Setup variable parameters that impact the timings set below.
  tRPRE       = MrcGetRpre (MrcData);
  tWPRE       = (Lpddr4) ? TWPRE_ALL_FREQ_LP4 : TWPRE_ALL_FREQ;
  tDQSCKMax   = (Lpddr4) ? tDQSCK_MAX_LP4 : 0;
  tCWL        = Timing->tCWL;
  tCL         = Timing->tCL;
  tODTLon     = MrcGetOdtlTiming (MrcData, DdrFreq, LpWrOdt, LpOdtlOn);
  tODTLoff    = MrcGetOdtlTiming (MrcData, DdrFreq, LpWrOdt, LpOdtlOff);
  BurstLength = Outputs->BurstLength;
  tRPST       = 1; // LPDDR4 Read Post-amble.  Statically set to .05*tCK.
  TckPs       = Outputs->tCKps;
  WckPs       = Outputs->Wckps;

  //-----------------------------------
  // Calculate tRDRD
  //-----------------------------------
  if (Ddr4) {
    // Use tCCD_L for tRDRD_sg
    // Use tCCD_S for tRDRD_dg
    tCCD_L = Timing->tCCD_L;
    tCCD_S = TCCD_ALL_FREQ;
  } else if (Lpddr4) {
    tCCD_S = tCCD_L = MRC_LP4_tCCD_ALL_FREQ;
  } else {
    // LPDDR5
    tCCD_S = tCCD_L = TCCD_ALL_FREQ * 4;
  }

  tRDRDsg = MIN (tCCD_L, tRDRD_MAX);
  tRDRDdg = MIN (tCCD_S, tRDRD_MAX);

  //
  // Calculate tRDRD_dr = BL/2 + max(tRTR, ODT(R,R,DR)) + tRPRE
  //
  Value = BurstLength + 1 + tRPRE;
  if (Lpddr4) {
    // Increase tRDRD_dr from 6 to 7 DCLKs on LPDDR
    Value++;
  } else if (Lpddr5) {
    // [(tWCKDQOmax - tWCKDQOmin)/tWCK + BL/2 + (tRPRE + tRPST - 0.5)] / 4
    // tRPST is 0.5
    Value = MRC_LP5_tWCKDQO_MAX - MRC_LP5_tWCKDQO_MIN;
    Value = DIVIDECEIL (Value, WckPs);
    Value += (BurstLength + tRPRE) * 4;
  }
  // Minimum RDRD DR TA time value.
  if ((Inputs->A0) && (Ddr4) && (Outputs->Gear2) && (Value < tRDRD_DR_MIN)) {
    Value = tRDRD_DR_MIN;
  }
  tRDRDdr = MIN (Value, tRDRD_MAX);

  // Calculate tRDRD_dd = BL/2 + max(tRTR, ODT(R,R,DD)) + tRPRE
  tRDRDdd = MIN (Value + 1, tRDRD_MAX);

  if (Ddr4) {
    // Calculate tRDWR = tCL - tCWL + tCCD + tWPRE + max(tRWSR,ODT(R,W,SR))
    Value = tCL - tCWL + tCCD_S + tWPRE + 2;
    // Add 1 for frequencies above 1067.
    if (DdrFreq > f1067) {
      Value++;
    }

    // Add 1 for frequencies above 1600.
    if (DdrFreq > f1600) {
      Value++;
    }
  } else if (Lpddr4) {
    // tCCD_S value will match "BL / 2" in the TA Calculation.
    // Common components for LP4
    Value = tCL + DIVIDECEIL (tDQSCKMax, TckPs) + tCCD_S + tRPST;
    if (Outputs->DramDqOdtEn) {
      // ODT On  : RL + RU (tDQSCK (max) / tCK) + BL / 2 + tRPST - ODTLon - RD (tODTon, min / tCK) + 1
      Value = Value  - tODTLon - (MRC_LP4_tODT_ON_MIN / TckPs) + 1;
    } else {
      // ODT Off : RL - WL + RU (tDQSCK (max) / tCK) + BL / 2 + tRPST + tWPRE
      Value = Value - tCWL + tWPRE;
    }
  } else {
    // LPDDR5
    // RdWr(tCK) = RL - WL - ODTLon + (tWCKDQO_max - tODTon_min + GB) /tCK + (tWCK2CK_max + BL/2) /4
    Value = MRC_LP5_tWCKDQO_MAX - MRC_LP5_tODT_ON_OFF_MIN + (WckPs / 2);
    Value = DIVIDECEIL (Value, WckPs);
    Value = (tCL - tCWL - tODTLon + BurstLength + 1) * 4;
  }
  tRDWRsg = MIN (Value, tRDWR_MAX);
  tRDWRdg = MIN (Value, tRDWR_MAX);
  // DDR4 tRDWR_dr = tCL-tCWL+tCCD+tWPRE+max(tRWDR,ODT(R,W,DR))
  tRDWRdr = MIN (Value, tRDWR_MAX);
  // DDR4 tRDWR_dd = tCL-tCWL+tCCD+tWPRE+max(tRWDD,ODT(R,W,DD))
  tRDWRdd = MIN (Value + 1, tRDWR_MAX);

  if (Ddr4) {
    tWTR_S = Timing->tWTR_S;
    tWTR_L = Timing->tWTR_L;
  } else {
    tWTR_S = tWTR_L = Timing->tWTR;
  }

  // Calculate tWRRD = tCWL + BL/2 + tWTR + max(tWrCAS2RdCAS_sr,ODT(W,R,SR)).
  Value = Timing->tCWL + BurstLength + tWTR_L;
  if (Lpddr5) {
    Value *= 4;
  } else {
    Value += 2;
  }
  tWRRDsg = MIN (Value, tWRRD_SG_MAX);
  if (Ddr4) {
    Value = Timing->tCWL + BurstLength + tWTR_S + 2;
  }
  tWRRDdg = MIN (Value, tWRRD_DG_MAX);

  if (Lpddr5) {
    // WrRdDr(tCK) = WL - RL + ODTLoff + (tODToff_max - tWCKDQO_min + GB) /tCK - (tWCK2CK_min) / 4
    // tWCK2CK_MIN is -.5 tWCK.  Calculating in pS and converting to WCK.
    Value = (MRC_LP5_tODT_ON_OFF_MAX - MRC_LP5_tWCKDQO_MIN) - (WckPs / 2);
    Value = DIVIDECEIL (Value, WckPs);
    Value += (tCWL - tCL + tODTLoff + 1) * 4;
    tWRRDdr = Value;
  } else {
    // Calculate tWRRD_dr = tCWL - tCL + BL/2 + max(tWRDRDR,ODT(W,R,DR)) + tRPRE
    tWRRDdr = (INT32) (Timing->tCWL) - Timing->tCL + BurstLength + 2 + tRPRE;
  }
  tWRRDdr = RANGE (tWRRDdr, 4, tWRRD_MAX);
  // Calculate tWRRD_dd = tCWL - tCL + BL/2 + max(tWRDRDD,ODT(W,R,DD)) + tRPRE
  tWRRDdd = tWRRDdr;

  //-----------------------------------
  // Calculate tWRWR
  //-----------------------------------
  tWRWRsg = MIN (tCCD_L, tWRWR_MAX);
  tWRWRdg = MIN (tCCD_S, tWRWR_MAX);

  if (Lpddr5) {
    // WrWrDr(tCK) = ODTLoff + (tODToff_max - tWCKDQI_min + GB) /tCK + (0.25 - tWCK2CK_min) / 4
    // (0.25 - tWCK2CK_min) => 0.25 - (-0.5) == 0.75 wCK
    Value = MRC_LP5_tODT_ON_OFF_MAX - MRC_LP5_tWCKDQI_MIN - (WckPs / 4);
    Value = DIVIDECEIL (Value, WckPs);
    Value += (tODTLoff + 1) * 4;
  } else if (Lpddr4 && (Outputs->DramDqOdtEn)) {
    // JEDEC Spec Table Table X3: Time between to ranks should ensure ODT switch doesn't overlap.
    // ODTLoff + RU (tODToff.MAX / tCK) - ODTLon - RD (tODTon.Min / tCK) + Electrical Guardband
    Value = tODTLoff - tODTLon + DIVIDECEIL ((MRC_LP4_tODT_Off_MAX - MRC_LP4_tODT_ON_MIN), TckPs) + 1;
  } else {
    // DDR4, LPDDR4 no ODT
    // Calculate tWRWR_dr = BL/2 + max(tWWDR,ODT(W,W,DR)) + tWPRE
    Value = BurstLength + 2 + tWPRE;
  }
  if ((Inputs->A0) && (Inputs->CpuModel == cmTGL_ULX_ULT) && Ddr4 && Outputs->Gear2 ) {
    Value = MAX (Value, 11);
  }
  tWRWRdr = MIN (Value, tWRWR_MAX);
  // Calculate tWRWR_dd = BL/2 + max(tWWDD,ODT(W,W,DR)) + tWPRE
  tWRWRdd = MIN (Value, tWRWR_MAX);
  if (Lpddr5) {
    // WCK is configured to be 4:1 CK.  Align timings to this.
    RoundTo = 4;
  } else if (Outputs->Gear2) {
    // Cannot do Odd clocks in Gear2.
    RoundTo = 2;
  } else {
    RoundTo = 1;
  }

  if (Outputs->Gear2) {
    tRDRDsg = RoundTo * (DIVIDECEIL ((UINT32) tRDRDsg, RoundTo));
    tRDRDdg = RoundTo * (DIVIDECEIL ((UINT32) tRDRDdg, RoundTo));
    tRDRDdr = RoundTo * (DIVIDECEIL ((UINT32) tRDRDdr, RoundTo));
    tRDRDdd = RoundTo * (DIVIDECEIL ((UINT32) tRDRDdd, RoundTo));
    tRDWRsg = RoundTo * (DIVIDECEIL ((UINT32) tRDWRsg, RoundTo));
    tRDWRdg = RoundTo * (DIVIDECEIL ((UINT32) tRDWRdg, RoundTo));
    tRDWRdr = RoundTo * (DIVIDECEIL ((UINT32) tRDWRdr, RoundTo));
    tRDWRdd = RoundTo * (DIVIDECEIL ((UINT32) tRDWRdd, RoundTo));
    tWRRDsg = RoundTo * (DIVIDECEIL ((UINT32) tWRRDsg, RoundTo));
    tWRRDdg = RoundTo * (DIVIDECEIL ((UINT32) tWRRDdg, RoundTo));
    tWRRDdr = RoundTo * (DIVIDECEIL ((UINT32) tWRRDdr, RoundTo));
    tWRRDdd = RoundTo * (DIVIDECEIL ((UINT32) tWRRDdd, RoundTo));
    tWRWRsg = RoundTo * (DIVIDECEIL ((UINT32) tWRWRsg, RoundTo));
    tWRWRdg = RoundTo * (DIVIDECEIL ((UINT32) tWRWRdg, RoundTo));
    tWRWRdr = RoundTo * (DIVIDECEIL ((UINT32) tWRWRdr, RoundTo));
    tWRWRdd = RoundTo * (DIVIDECEIL ((UINT32) tWRWRdd, RoundTo));
  }

  // Cache Values and write to hardware
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, GsmMode, &tRDRDsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, GsmMode, &tRDRDdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, GsmMode, &tRDRDdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, GsmMode, &tRDRDdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, GsmMode, &tRDWRsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdg, GsmMode, &tRDWRdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, GsmMode, &tRDWRdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, GsmMode, &tRDWRdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDsg, GsmMode, &tWRRDsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdg, GsmMode, &tWRRDdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, GsmMode, &tWRRDdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, GsmMode, &tWRRDdd);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRsg, GsmMode, &tWRWRsg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdg, GsmMode, &tWRWRdg);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, GsmMode, &tWRWRdr);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, GsmMode, &tWRWRdd);
  MrcFlushRegisterCachedData (MrcData);

  // Must update the XARB bubble injector when TAT values change
  SetTcBubbleInjector (MrcData, Controller, Channel);
}

/**
  This function sets up the TC_PWRDN register.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - 0-based index to select the Controller.
  @param[in]      Channel     - 0-based index to select the Channel.

  @retval Nothing.
**/
static
void
SetTcPwrdwn (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
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
  INT64           tCA2CS;
  INT64           tCSL;
  INT64           tCSH;
  UINT32          BurstLength;
  UINT32          TckPs;
  UINT32          tCK;
  UINT32          MrrMrw;
  UINT32          MinVal;
  UINT32          Data32;
  UINT32          Offset;
  UINT32          IpChannel;
  UINT32          tOSCO;
  UINT32          tMRR;
  BOOLEAN         Ddr4;
  BOOLEAN         Lpddr;
  BOOLEAN         Lpddr5;
  BOOLEAN         Lpddr4;
  MC0_CH0_CR_TC_LPDDR4_MISC_STRUCT  TcLpddr4Misc;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[Controller].Channel[Channel];
  Timing      = &ChannelOut->Timing[Inputs->MemoryProfile];
  DdrType     = Outputs->DdrType;
  tCK         = Timing->tCK;
  TckPs       = Outputs->tCKps;
  Lpddr       = Outputs->Lpddr;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5      = (DdrType == MRC_DDR_TYPE_LPDDR5);
  DdrFreq     = (Lpddr && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;
  BurstLength = Outputs->BurstLength;

  Data32 = tCKEValue (DdrType, DdrFreq, tCK);
  if (Lpddr5) {
    // Scale to WCK for Lpddr5
    Data32 *= 4;
  }
  tCKE = RANGE (Data32, tCKE_MIN, tCKE_MAX);

  Data32 = tXPValue (DdrType, tCK);
  if (Lpddr5) {
    Data32 *= 4;
    if (Inputs->A0) {
      Data32 += (Outputs->Gear2) ? 2 : 4;
    }
  }
  tXP = RANGE (Data32, tXP_MIN, tXP_MAX);

  tXPDLL = tXPDLLValue (tCK);
  tXPDLL = RANGE (tXPDLL, tXPDLL_MIN, tXPDLL_MAX);

  if (Lpddr5) {
    // tCMDPD
    Data32 = DIVIDECEIL (MRC_LP5_tCMDPD_MIN, TckPs);
    Data32 = MAX (Data32, MRC_LP5_tCMDPD_MIN_NCK);
    // Scale to WCK
    Data32 *= 4;
    tPRPDEN = Data32;
    if (Inputs->A0) {
      tPRPDEN += 2;
    }
    tPRPDEN = MAX (tPRPDEN, MRC_tPRPDEN_LP5_MIN);
    tPRPDEN -= MRC_tPRPDEN_LP5_MIN;

    // tCSH
    Data32 = DIVIDECEIL (MRC_LP5_tCSH_MIN, TckPs);
    // Scale to WCK
    Data32 *= 4;
    tCSH = Data32;

    // tCSL
    Data32 = DIVIDECEIL (MRC_LP5_tCSL_MIN, TckPs);
    // Scale to WCK
    Data32 *= 4;
    tCSL = Data32;

    // tCA2CS
    Data32 = DIVIDECEIL (MRC_LP5_tCA2CS_PRE_MIN, TckPs);
    Data32 = MAX (Data32, MRC_LP5_tCA2CS_PRE_MIN_NCK);
    Data32 *= 4;
    tCA2CS = Data32;
  } else if (Lpddr4) {
    // LPDDR4 tPRPDEN == tCMDCKE Table 94 JEDEC SPEC.
    // MAX (1.75ns, 3nCK)
    Data32 = DIVIDECEIL (MRC_LP4_tCMDCKE_PS, TckPs);
    Data32 = MAX (Data32, 3);
    // Controller specific - MC enforces minimum 4 tCK
    Data32 = MAX (Data32, MRC_tPRPDEN_LP4_MIN);
    Data32 -= MRC_tPRPDEN_LP4_MIN;
    tPRPDEN = Data32;
  } else {
    // DDR4
    tPRPDEN = (DdrFreq < f2133) ? 1 : 2;
  }
  if ((Inputs->A0) && (Outputs->Gear2) && Ddr4) {
    tPRPDEN = 3;
  }

  // Calculate tRDPDEN = tCL + BL/2 + ((Lp5) ? WCK2CKmax + WCKDQOmax : 1)
  Data32 = Timing->tCL + Outputs->BurstLength;
  if (Lpddr5) {
    // Always in 4:1 mode.  Add in 1/2 tCK for tWCK2CKmax
    Data32 += DIVIDECEIL (MRC_LP5_tWCKDQO_MAX + (TckPs / 2), TckPs);
    // Scale to WCK
    Data32 *= 4;
  } else {
    Data32 += 1;
  }
  if (Lpddr4) {
    Data32 += DIVIDECEIL (tDQSCK_MAX_LP4, TckPs);
  }
  tRDPDEN = Data32;
  tRDPDEN = RANGE (tRDPDEN, tRDPDEN_MIN, tRDPDEN_MAX);

  // Calculate tWRPDEN = tCWL + BL/2 + tWR
  Data32 = Timing->tCWL + Outputs->BurstLength + Timing->tWR;
  if (Lpddr5) {
    // Add in tWCK2CKmax and tWCKDQImax
    Data32 += DIVIDECEIL (MRC_LP5_tWCKDQI_MAX + (TckPs / 2), TckPs);
    // Scale to WCK
    Data32 *= 4;
  }
  tWRPDEN = Data32;
  tWRPDEN = RANGE (tWRPDEN, tWRPDEN_MIN, tWRPDEN_MAX);

  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCKE,    WriteToCache | PrintValue, &tCKE);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctXP,     WriteToCache | PrintValue, &tXP);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctPRPDEN, WriteToCache | PrintValue, &tPRPDEN);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDPDEN, WriteToCache | PrintValue, &tRDPDEN);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRPDEN, WriteToCache | PrintValue, &tWRPDEN);
  if (Lpddr5) {
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCSH,    WriteToCache | PrintValue, &tCSH);
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCSL,    WriteToCache | PrintValue, &tCSL);
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCA2CS,  WriteToCache | PrintValue, &tCA2CS);
  } else {
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctXPDLL,  WriteToCache | PrintValue, &tXPDLL);
  }
  MrcFlushRegisterCachedData (MrcData);

  if (Lpddr) {
    // Delay time from OSC stop to MR18/19 Readout. Value = Max(40ns, (Lpddr5) ? 4tCK : 8tCK)
    // This is the only field in this register, and we only program it once, so no GetSet.
    IpChannel = LP_IP_CH (Lpddr, Channel);
    Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_LPDDR4_MISC_REG, MC1_CH0_CR_TC_LPDDR4_MISC_REG, Controller, MC0_CH1_CR_TC_LPDDR4_MISC_REG, IpChannel);
    TcLpddr4Misc.Data = 0;
    tOSCO = DIVIDECEIL (MRC_LP4_tOSCO_FS, tCK);
    MinVal = (Lpddr5) ? 4 : 8;
    tOSCO = MAX (tOSCO, MinVal);
    if (Lpddr5) {
      tOSCO *= 4;
    }
    tMRR = (Lpddr4) ? 8 : 16; // 4CK for LP5.  4:1 in the constant.
    MrrMrw = Timing->tCL;
    if (Lpddr5) {
      MrrMrw += BurstLength + DIVIDECEIL (MRC_LP5_tWCKDQO_MAX, TckPs) + 2;
      MrrMrw *= 4;
    } else {
      MrrMrw += (BurstLength / 2) + DIVIDECEIL (tDQSCK_MAX_LP4, TckPs) + 3;
    }
    if (Inputs->A0) {
      TcLpddr4Misc.A0Bits.tOSCO = tOSCO;
      TcLpddr4Misc.A0Bits.tMRR = tMRR;
      TcLpddr4Misc.A0Bits.tMRRMRW = MrrMrw;
    } else {
      TcLpddr4Misc.Bits.tOSCO = tOSCO;
      TcLpddr4Misc.Bits.tMRR = tMRR;
      TcLpddr4Misc.Bits.tMRRMRW = MrrMrw;
    }
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
  UINT32      Controller;
  UINT32      Channel;
  BOOLEAN     Lpddr;

  Lpddr = MrcData->Outputs.Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      // Setup TC_PRE, TC_ACT and TC_ODT registers
      SetTcPreActOdt (MrcData, Controller, Channel);
      // Setup turnaround timings
      SetTcTurnAround (MrcData, Controller, Channel);
      // Setup TC_PWRDWN register
      SetTcPwrdwn (MrcData, Controller, Channel);
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
  MrcChannelOut         *ChannelOut;
  UINT32                Controller;
  UINT32                Channel;
  UINT8                 RankMaskCh;
  INT8                  OdtStretch;
#if SUPPORT_SODIMM == SUPPORT
  MrcDimmOut            *DimmOut;
  BOOLEAN               SoDimm;
  UINT8                 Dimm;
  UINT8                 DimmRawCardType[MAX_DIMMS_IN_CHANNEL];
#endif //SUPPORT_SODIMM == SUPPORT

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  // Only DDR4 supports 2DPC.  Return out for other technologies and Ulx/Ult.
  if ((Outputs->DdrType != MRC_DDR_TYPE_DDR4) || (Inputs->UlxUlt)) {
    return;
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || (ChannelOut->DimmCount != 2)) {
        // Skip any channels that do not have 2 DIMMs populated
        continue;
      }

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
      UpdateTAParamOffset (MrcData, Controller, Channel, 0, rdodtd, OdtStretch, 1, 1, RankMaskCh);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Selected RdOdtD Offset for channel %d is = %d\n", Channel, OdtStretch);

    #if SUPPORT_SODIMM == SUPPORT
      if (OdtStretch > 6) {
        MrcTatStretch (MrcData, Controller, Channel, rdodtd, OdtStretch - 6, TRUE);
      } else {
        // @todo Is this needed for ICL?
        // Add 1 for ODT read duration for 2DPC
        UpdateTAParamOffset (MrcData, Controller, Channel, 0, rdodtd, 7, 1, 1, RankMaskCh);
      }
    #endif //SUPPORT_SODIMM == SUPPORT
    }
  }

}


/**
  This function adjusts the relevant TAT when changing Read or Write ODT duration.
  TAT list rdOdt = { drrd2rd, ddrd2rd, drrd2wr, ddrd2wr, srrd2wr_sg, srrd2wr_dg };
  TAT list wrOdt = { drwr2wr, ddwr2wr, drwr2rd, ddwr2rd, srwr2rd_sg, srwr2rd_dg };

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - Controller select.
  @param[in]      Channel     - Channel select.
  @param[in]      OdtType     - rdodtd or wrodtd.
  @param[in]      Offset      - signed offset.
  @param[in]      UpdateHost  - Switch to update the host struct with the new value.

  @retval Nothing.
**/
void
MrcTatStretch (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Controller,
  IN     UINT32               Channel,
  IN     UINT8                OdtType,
  IN     INT8                 Offset,
  IN     BOOLEAN              UpdateHost
  )
{
  INT64   GetSetVal;
  UINT32  GsmMode;

  GsmMode = ForceWriteOffsetUncached;
  if (UpdateHost) {
    GsmMode |= WriteCached;
  }

#if 0 // This code is used for register cache debug only.
#ifdef MRC_DEBUG_PRINT
  GsmMode |= PrintValue;
#endif
#endif

  GetSetVal = Offset;
  //@todo: Optimize using arrays and only one GetSet Call.
  if (OdtType == rdodtd) {
    // Program Different Rank RD 2 RD value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdr, GsmMode, &GetSetVal);

    // Program Different DIMM RD 2 RD value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdd, GsmMode, &GetSetVal);

    // Program Different Rank RD 2 WR value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdr, GsmMode, &GetSetVal);

    // Program Different DIMM RD 2 WR value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdd, GsmMode, &GetSetVal);

    // Program Same Rank RD 2 WR sg value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRsg, GsmMode, &GetSetVal);

    // Program Same Rank RD 2 WR dg value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDWRdg, GsmMode, &GetSetVal);
  } else if (OdtType == wrodtd) {
    // Program Different Rank WR 2 WR value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdr, GsmMode, &GetSetVal);

    // Program Different DIMM WR 2 WR value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRWRdd, GsmMode, &GetSetVal);

    // Program Different Rank WR 2 RD value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdr, GsmMode, &GetSetVal);

    // Program Different DIMM WR 2 RD value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdd, GsmMode, &GetSetVal);

    // Program Same Rank WR 2 RD sg value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDsg, GsmMode, &GetSetVal);

    // Program Same Rank WR 2 RD dg value
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctWRRDdg, GsmMode, &GetSetVal);
  }
  // Must update the XARB bubble injector when TAT values change
  SetTcBubbleInjector (MrcData, Controller, Channel);
}
