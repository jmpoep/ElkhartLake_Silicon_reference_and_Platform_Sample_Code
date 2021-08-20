/** @file
  This file contains all the MRC general API to the MRC wrapper.

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


#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGeneral.h"
#include "MrcMemoryApi.h"
#include "MrcDdr3.h"
#include "MrcDdr4.h"
#include "MrcLpddr4.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcTimingConfiguration.h"
#include "MrcSchedulerParameters.h"
#include "MrcCpgcApi.h"
#include "MrcGears.h"

GLOBAL_REMOVE_IF_UNREFERENCED const MrcVersion  cVersion[] = {
  #include "MrcVersion.h"
};

// Number of Scrambler Groups
#define MRC_NUM_SCRAM (8)

//
// RCOMP target values for { RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk } - with LPDDR4[X]/DDR4
//
const UINT16 RcompTargetLpddr4[MAX_RCOMP_TARGETS]   = { 80, 40, 40, 40, 30 };
const UINT16 RcompTargetLpddr4x[MAX_RCOMP_TARGETS]  = { 60, 40, 40, 40, 30 };
const UINT16 RcompTargetLpddr5[MAX_RCOMP_TARGETS]   = { 40, 36, 35, 35, 35 };
const UINT16 RcompTargetUDdr4[MAX_RCOMP_TARGETS]    = { 50, 25, 25, 25, 25 };
const UINT16 RcompTargetHDdr4[MAX_RCOMP_TARGETS]    = { 40, 30, 33, 33, 30 };
const UINT16 RcompTargetUDdr5[MAX_RCOMP_TARGETS]    = { 50, 25, 25, 25, 25 };
const MrcFrequency SagvFreqPor[MAX_MRC_DDR_TYPE - 1][MAX_SAGV_POINTS] = {
//     0,     1,     2,     3
  {f2133, f3200, f2933, f2933}, // DDR4
  {    0,     0,     0,     0}, // DDR5
  {f2200, f3200, f4400, f5400}, // LPDDR5
  {f2133, f3200, f4267, f2933}  // LPDDR4
};
const UINT8 SaGvGearPor[MAX_MRC_DDR_TYPE - 1][MAX_SAGV_POINTS] = {
//     0,     1,     2,     3
  {    2,     2,     1,     1}, // DDR4
  {    0,     0,     0,     0}, // DDR5
  {    2,     2,     2,     2}, // LPDDR5
  {    2,     2,     2,     1}  // LPDDR4
};

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
const char TrainEnString[]  = "TrainingEnables";
const char TrainEn2String[] = "TrainingEnables2";
const char ThermEnString[]  = "ThermalEnables";
const char PrintBorder[]    = "*************************************\n";
#endif // MRC_DEBUG_PRINT

// This table is used for LPDDR MR5 decoding
struct {
  UINT8   VendorId;
  UINT16  JedecId;
  char    *VendorName;
} DramVendorList [] = {
  { 1,    0xCE00, "Samsung" },
  { 3,    0xFE02, "Elpida"  },
  { 6,    0xAD00, "Hynix"   },
  { 0xFF, 0x2C00, "Micron"  },
};
/**
  Enable/Disable DLL WeakLock if needed.
  Note: We don't enable it in McConfig because CKE is still low during that step.

  @param[in] MrcData - The MRC general data.
  @param[in]  Enable - BOOLEAN control to enable (if TRUE), or disable (if FALSE) WeakLock.

  @retval None
**/
void
MrcWeaklockEnDis (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              Enable
  )
{
  static const GSM_GT Groups[2] = {GsmIocDllWeakLock, GsmIocDllWeakLock1};
  UINT32          Index;
  UINT32          GsmGtIdx;
  INT64           GetSetVal;
  DLLDDRCOMP_CR_DLLWEAKLOCK_STRUCT  RcompWeakLock;

  GetSetVal = (Enable) ? 1 : 0;
  for (GsmGtIdx = 0; GsmGtIdx < ARRAY_COUNT (Groups); GsmGtIdx++) {
    for (Index = 0; Index < 8; Index++) {
      MrcGetSetStrobe (
        MrcData,
        MRC_IGNORE_ARG,
        MRC_IGNORE_ARG,
        MRC_IGNORE_ARG,
        Index,
        Groups[GsmGtIdx],
        WriteCached,
        &GetSetVal
        );
    }
  }

  RcompWeakLock.Data = MrcReadCR (MrcData, DLLDDRCOMP_CR_DLLWEAKLOCK_REG);
  RcompWeakLock.Bits.DllWeakLock0 = Enable;
  RcompWeakLock.Bits.DllWeakLock1 = Enable;
  MrcWriteCR (MrcData, DLLDDRCOMP_CR_DLLWEAKLOCK_REG, RcompWeakLock.Data);
}

/**
  This function returns the current configuration of Frequency and Gear ratio based on the
  current SAGV point, DDR type, and SAGV input parameters: SaGvFreq, SaGvGear.

  It will update FreqOut and GearOut with the result.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[in]  SaGvPoint - Current operating SAGV point.
  @param[out] FreqOut   - Pointer to return the SAGV point Frequency.
  @param[out] GearOut   - Pointer to return the SAGV point Gear.
**/
VOID
MrcGetSagvConfig (
  IN  MrcParameters *const  MrcData,
  IN  MrcSaGvPoint          SaGvPoint,
  OUT MrcFrequency          *FreqOut,
  OUT BOOLEAN               *GearOut
  )
{
  MrcInput    *Inputs;
  MrcOutput   *Outputs;
  MrcDdrType  DdrType;
#ifdef MRC_DEBUG_PRINT
  MrcDebug    *Debug;
#endif

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
#ifdef MRC_DEBUG_PRINT
  Debug   = &Outputs->Debug;
#endif

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV point %u\n", SaGvPoint);
  if (FreqOut == NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %s is NULL\n", &gErrString, "FreqOut");
  } else {
    if (Inputs->SaGvFreq[SaGvPoint]) {
      *FreqOut = Inputs->SaGvFreq[SaGvPoint];
    } else {
      *FreqOut = SagvFreqPor[DdrType][SaGvPoint];
      MRC_DEBUG_ASSERT (SagvFreqPor[DdrType][SaGvPoint] != 0, Debug, "Invalid SAGV %s: Point %d %s: %d\n", "Freq", SaGvPoint, "Freq", SagvFreqPor[DdrType][SaGvPoint]);
    }
  }

  if (GearOut == NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %s is NULL\n", &gErrString, "GearOut");
  } else {
    if (Inputs->SaGvGear[SaGvPoint]) {
      *GearOut = (Inputs->SaGvGear[SaGvPoint] == 2);
    } else {
      *GearOut = (SaGvGearPor[DdrType][SaGvPoint] == 2);
      MRC_DEBUG_ASSERT (SaGvGearPor[DdrType][SaGvPoint] != 0, Debug, "Invalid SAGV %s: Point %d %s: %d\n", "Gear", SaGvPoint, "Gear", SaGvGearPor[DdrType][SaGvPoint]);
    }
  }
}

/**
  Read LPDDR information from MR5 and MR8 and print to the debug log.
  Also update the Manufacturer's ID in the SPD table, for BIOS Setup and SMBIOS table.

  @param[in] MrcData - include all the MRC general data.

  @retval none
**/
void
ShowLpddrInfo (
  IN  MrcParameters *const MrcData
  )
{
  MrcInput        *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcIntOutput    *MrcIntData;
  MrcSpd          *SpdIn;
  UINT32          Controller;
  UINT32          Channel;
  UINT32          Rank;
  UINT8           MrrResult[4];
  UINT32          MrAddr;
  UINT32          Device;
  UINT32          Index;
  BOOLEAN         VendorFound;
  UINT16          JedecId;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug   = &Outputs->Debug;
  VendorFound = FALSE;
  Index = 0;

  if (Inputs->BootMode != bmCold) {
    // Full deswizzle table is not present on non-cold flows, so cannot parse MR read.
    return;
  }
  // LPDDR: Read MR5 and MR8
  // @todo: <CNL> Update for LP4.
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }

          // MR5 - Manufacturer ID
          MrAddr = 5;
          MrcIssueMrr (MrcData, Controller, Channel, Rank, MrAddr, MrrResult);
          for (Device = 0; Device < sizeof (MrrResult) / sizeof (MrrResult[0]); Device++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDevice[%u]= 0x%02X", Device, MrrResult[Device]);
            VendorFound = FALSE;
            for (Index = 0; Index < sizeof (DramVendorList) / sizeof (DramVendorList[0]); Index++) {
              if (DramVendorList[Index].VendorId == MrrResult[Device]) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %s\n", DramVendorList[Index].VendorName);
                VendorFound = TRUE;
                break;
              }
            }
            if (!VendorFound) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Unknown\n");
            }
          }

          if (VendorFound) {
            // Patch SPD data with vendor ID code.
            // This is consumed by BIOS Setup and SMBIOS Type 17 table creation code.
            // If SAGV enabled, only do this on the last pass: MrcSaGvPoint4.
            if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint == MrcSaGvPoint4)) {
              JedecId = DramVendorList[Index].JedecId;
              SpdIn = &Inputs->Controller[Controller].Channel[Channel].Dimm[dDIMM0].Spd.Data;
              SpdIn->Lpddr.ManufactureInfo.ModuleId.IdCode.Data = JedecId;
              SpdIn->Lpddr.ManufactureInfo.DramIdCode.Data      = JedecId;
            }
          }

#ifdef MRC_DEBUG_PRINT
          // MR8 - I/O Width, Density, Type
          MrAddr = 8;
          MrcIssueMrr (MrcData, Controller, Channel, Rank, MrAddr, MrrResult);
          for (Device = 0; Device < sizeof (MrrResult) / sizeof (MrrResult[0]); Device++) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tDevice[%u]= 0x%02X - %s\n", Device, MrrResult[Device],
              (MRC_BIT6 & MrrResult[Device]) ? "x16" : "x32");
          }
#endif // #ifdef MRC_DEBUG_PRINT
        } // for Rank
      } // for Channel
    } // for Controller
  }
}

/**
  This function performs final MC/DDRIO configuration after all training steps are done, but before Normal mode.
  - Enable Scrambler
  - Enable ddr4_1dpc feature
  - Enable ECC
  - Enable Weaklock
  - Enable CMD tri-state
  - Enable LPDDR4/X DqsN Park mode

  @param[in, out] MrcData - Include all MRC global data.

  @retval Returns mrcSuccess or failure if DRAM width doesn't match.
**/
MrcStatus
MrcMcActivate (
  IN     MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcDdrType          DdrType;
  INT64               GetSetVal;
  INT64               GetSetDis;
  UINT32              Offset;
  UINT32              Data32;
  UINT32              GeneratedSeed;
  UINT32              i;
  UINT16              SAFE;
  UINT16              NS;
  UINT8               Controller;
  UINT8               Channel;
  UINT32              IpChannel;
#if 0
  MrcIntOutput        *MrcIntData;
  UINT8               Byte;
  UINT8               Rank;
  UINT8               MaxRcvEn;
  UINT8               RcvEnDrift;
  UINT8               RcvEnTurnOff;
  UINT8               RcvEn;
  UINT16              MaxRdDataValid;
  UINT16              RdDataValid;
  INT8                OdtTurnOff;
  INT64               OdtDelay;
  INT64               OdtDuration;
  INT64               RxClkStgNum;
  INT64               RxFifoRdEnRank;
  INT64               LpddrLongOdtEn;
  INT64               OdtSampExtEn;
  INT32               Temp;
  UINT32              SubCh;
  BOOLEAN           Ratio900To1000;
  BOOLEAN           Ratio800To900;
  BOOLEAN           Ratio700To800;
  UINT32            Ratio;
  DDRSCRAM_CR_DDRMISCCONTROL2_STRUCT MiscControl2;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_STRUCT      VccDllFFControl;
#endif
  BOOLEAN             Lpddr;
  DDRSCRAM_CR_DDRSCRAMBLECH0_STRUCT  DdrScramble;
  MC0_CH0_CR_MC_INIT_STATE_STRUCT        McInitState;
  //DDRSCRAM_CR_DDRMISCCONTROL7_STRUCT MiscControl7;
  //MCMISCS_SPINEGATING_STRUCT         McMiscSpineGating;
  //UINT8               DataInvertNibble;
  //BOOLEAN             Vtt;
  //BOOLEAN             Vddq;

#if 0
  MrcIntData    = ((MrcIntOutput *)(MrcData->IntOutputs.Internal));
#endif
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &MrcData->Outputs.Debug;
  DdrType       = Outputs->DdrType;
  GeneratedSeed = 0;
  SAFE          = 0;
  GetSetDis     = 0;
  Lpddr         = Outputs->Lpddr;
  //Vtt           = (Outputs->OdtMode == MrcOdtModeVtt);
  //Vddq          = (Outputs->OdtMode == MrcOdtModeVddq);

  if (Inputs->SafeMode) {
    SAFE = 0xFFFF;
  }
  NS = ~SAFE;

  MrcBeforeNormalModeTestMenu (MrcData);
  // Oem hook before normal mode configuration starts
  MrcInternalCheckPoint (MrcData, OemBeforeNormalMode, NULL);

//#ifndef HSLE_FLAG
  //DataInvertNibble = (Vtt) ? 2 : (Vddq) ? 1 : 0;
//#else
  // HSLE wants the data invert nibble disabled.
//  DataInvertNibble = 0;
//#endif

  //MiscControl7.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG);
  //MiscControl7.Bits.DataInvertNibble = DataInvertNibble;
  //MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, MiscControl7.Data);

  //GetSetVal = DataInvertNibble;
  //MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataInvertNibble, WriteCached, &GetSetVal);

  MrcPrintDimmOdtValues (MrcData);  // Print DIMM ODT table

  if (!Lpddr) {
    MrcSetMrShadows (MrcData);
  }

  // Read LPDDR MR5 and MR8 info
  ShowLpddrInfo (MrcData);

  // Program DllWeaklock bit after training, when CKE is high
  if (Inputs->WeaklockEn && (!Inputs->SafeMode)) {
    MrcWeaklockEnDis (MrcData, MRC_ENABLE);
  }

  GetSetVal = 0;
  MrcGetSetNoScope (MrcData, GsmIocDisDataIdlClkGate, WriteCached, &GetSetVal);

  // Configure DDR4_1DPC performance feature
  MrcConfigureDdr4OneDpc (MrcData);

  // Enable Scrambling
  if ((Inputs->ScramblerSupport == TRUE) && (!Inputs->SafeMode)) {
    DdrScramble.Data          = 0;
    DdrScramble.Bits.ScramEn  = 1;
    DdrScramble.Bits.ClockGateAB = NS;
    DdrScramble.Bits.ClockGateC  = NS;
    DdrScramble.Bits.EnableDbiAB = NS;
    for (i = 0; i < MRC_NUM_SCRAM; i++) {
      MrcCall->MrcGetRandomNumber (&GeneratedSeed);
      DdrScramble.Bits.ScramKey = GeneratedSeed;
      Offset = OFFSET_CALC_CH (DDRSCRAM_CR_DDRSCRAMBLECH0_REG, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, i);
      MrcWriteCR (MrcData, Offset, DdrScramble.Data);
    }
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (MrcData, Controller, Channel))) {
        continue;
      }
      // Enable the command tri state at the end of the training.
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteNoCache, &GetSetDis);
      // Set the MC to ECC mode for all channels if needed.
      if (Outputs->EccSupport == TRUE) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ECC support\n");
        GetSetVal = emBothActive;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccEccMode, WriteNoCache | PrintValue, &GetSetVal);
      }
      // Tell MC that we are in FSP-OP = 1
      if (Lpddr && Inputs->LpFreqSwitch) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MC_INIT_STATE_REG, MC1_CH0_CR_MC_INIT_STATE_REG, Controller, MC0_CH1_CR_MC_INIT_STATE_REG, Channel);
        McInitState.Data = MrcReadCR (MrcData, Offset);
        McInitState.Bits.LPDDR4_current_FSP = 1;
        McInitState.Bits.LPDDR4_current_FSP_tracking = 1;
        MrcWriteCR (MrcData, Offset, McInitState.Data);
      }

      // Program 1x Refresh per technology during cold path.
      IpChannel = LP_IP_CH (Lpddr, Channel);
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        Data32 = RANK_TEMPERATURE_1XREF_DDR4;
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, MC1_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, Controller, MC0_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG, IpChannel);
      } else {
        Data32 = (DdrType == MRC_DDR_TYPE_LPDDR4) ? RANK_TEMPERATURE_1XREF_LPDDR4 : RANK_TEMPERATURE_1XREF_LPDDR5;
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, MC1_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, Controller, MC0_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, IpChannel);
      }
      MrcWriteCR (MrcData, Offset, Data32);
    } // for Channel
  } // for Controller

  UpdateSampOdtTiming (MrcData, (SAFE) ? 10 : 1); // Use guardband of 1, as 0 is too aggressive sometimes

//@todo ICL
#if 0
  // Program RxClkStgNum
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Read from Byte 0 as these should be the same across all bytes.
      MaxRcvEn   = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
          Temp = (INT32) GetSetVal;
          Temp = Temp / 64;
          RcvEn = (UINT8) Temp;
          MaxRcvEn = MAX (MaxRcvEn, RcvEn);
        }
      }
      RcvEnDrift   = (Lpddr) ? (UINT8) ((tDQSCK_DRIFT + Outputs->Qclkps - 1) / Outputs->Qclkps) : 1;
      RcvEnTurnOff = MaxRcvEn + (5 - 6) + 1 + 7 + 3 + 3 + 2 + (2 * RcvEnDrift);
      if (LpddrLongOdtEn == 1) {
        RcvEnTurnOff++;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDelay,     ReadFromCache, &OdtDelay);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, McOdtDuration,  ReadFromCache, &OdtDuration);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxClkStg, ReadFromCache, &RxClkStgNum);

        OdtTurnOff = (INT8) (OdtDelay + OdtDuration + 14);
        OdtTurnOff = MIN (OdtTurnOff, DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX);

        RxClkStgNum = MAX (17, OdtTurnOff);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxClkStg, WriteCached, &RxClkStgNum);
      }
    }
  }
#endif

// @todo TGL
#if 0
  // Calculate the DDRIO RdDataValid per channel/rank and save the max value.
  // This is based on the longest RxFIFO timing in the system.
  MaxRdDataValid = MrcIntData->MaxRdDataValid;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      MrcGetSetMcCh (MrcData, Controller, Channel, RxFifoRdEnTclDelay,      ReadFromCache, &GetSetVal);
      RdDataValid = (UINT16) GetSetVal;
      MrcGetSetMcCh (MrcData, Controller, Channel, RxDqDataValidDclkDelay,  ReadFromCache, &GetSetVal);
      RdDataValid += (UINT16) GetSetVal;

      RxFifoRdEnRank = 0;
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        MrcGetSetMcChRnk (MrcData, Controller, Channel, Rank, RxFifoRdEnFlybyDelay, ReadFromCache, &GetSetVal);
        RxFifoRdEnRank = MAX (GetSetVal, RxFifoRdEnRank);
      } // Rank
      RdDataValid += (UINT16) RxFifoRdEnRank;
      MrcIntData->MaxRdDataValid = MAX (MaxRdDataValid, RdDataValid);
    } // for Channel
  } // for Controller

  // If we're at the last point, or SAGV is not enabled, program the RX Grace counter
  if ((MrcIntData->SaGvPoint == MrcSaGvPointHigh) || (MrcData->Inputs.SaGv != MrcSaGvEnabled)) {
    MiscControl2.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG);
    MiscControl2.Bits.rx_analogen_grace_cnt = MrcIntData->MaxRdDataValid;
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG, MiscControl2.Data);
  }
#endif
  //MrcDccFsmFinalize (MrcData);

  //McMiscSpineGating.Data = MrcReadCR (MrcData, MCMISCS_SPINEGATING_REG);
  //McMiscSpineGating.Bits.EnableSpineGate = 1;
  //MrcWriteCR (MrcData, MCMISCS_SPINEGATING_REG, McMiscSpineGating.Data);

  MrcFlushRegisterCachedData (MrcData);

  // Oem hook when normal mode configuration is done
  MrcInternalCheckPoint (MrcData, OemAfterNormalMode, NULL);

  // Enable Self Refresh
  GetSetVal = 1;
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableSr, WriteNoCache, &GetSetVal);

  return mrcSuccess;
}

/**
  Program MC/CPGC engines to either Normal mode of operation
  or CPGC training mode.

  @param[in] MrcData    - The MRC general data.
  @param[in] NormalMode - TRUE for Normal mode, FALSE for CPGC mode

  @retval Always returns mrcSuccess.
**/
void
MrcSetNormalMode (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              NormalMode
  )
{
  MrcOutput   *Outputs;
  INT64       GetSetVal;
  INT64       CmdStretch;
  UINT32      Channel;
  UINT32      Controller;
  UINT32      Offset;
  BOOLEAN     Lpddr;
  MC0_NORMALMODE_CFG_STRUCT NormalModeCfg;
  MC0_MC_CPGC_CMI_STRUCT    McCpgcCmi;

  Outputs = &MrcData->Outputs;
  Lpddr   = Outputs->Lpddr;
  MrcSetCpgcInitMode (MrcData, !NormalMode);   // Configure the CPGC engines

  GetSetVal = 1;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccBlockXarb, WriteNoCache, &GetSetVal);  // Block XARB when changing normalmode and cadb_enable

  NormalModeCfg.Data = 0;
  NormalModeCfg.Bits.normalmode = NormalMode;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      Offset = OFFSET_CALC_CH (MC0_MC_CPGC_CMI_REG, MC1_MC_CPGC_CMI_REG, Controller);
      McCpgcCmi.Data = MrcReadCR (MrcData, Offset);
      McCpgcCmi.Bits.CPGC_ACTIVE = NormalMode ? 0 : 1;
      MrcWriteCR (MrcData, Offset, McCpgcCmi.Data);
      for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
        if (MrcChannelExist (MrcData, Controller, Channel) && (!IS_MC_SUB_CH (Lpddr, Channel))) {
          // Set bus_retain_on_n_to_1_bubble when N:1 is used and we are in Training mode; otherwise clear it.
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdStretch, ReadUncached, &CmdStretch);
          GetSetVal = (!NormalMode && (CmdStretch == 3)) ? 1 : 0;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccBusRetainOnBubble, WriteNoCache, &GetSetVal);
        }
      }
      Offset = OFFSET_CALC_CH (MC0_NORMALMODE_CFG_REG, MC1_NORMALMODE_CFG_REG, Controller);
      MrcWriteCR (MrcData, Offset, NormalModeCfg.Data);
    }
  }
  GetSetVal = NormalMode ? 0 : 1;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccCpgcInOrder, WriteNoCache, &GetSetVal);

  GetSetVal = 0;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccBlockXarb, WriteNoCache, &GetSetVal);  // Unblock XARB
}

/**
  This function enables Normal Mode and configures the Power Down Modes.
  We also have special flow here for SAGV in S3/Warm boot modes.

  @param[in] MrcData - The MRC general data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcNormalMode (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput      *Inputs;
  INT64               GetSetVal;
  BOOLEAN             SaGvAndSelfRefresh;
  UINT64                  Timeout;
  UINT32                  Controller;
  UINT32                  Offset;
  BOOLEAN                 Flag;
  MC0_STALL_DRAIN_STRUCT  StallDrain;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  // Check if SAGV is enabled and memory is in Self-Refresh right now (Warm reset or S3 resume)
  SaGvAndSelfRefresh = (Inputs->SaGv == MrcSaGvEnabled) && (Inputs->BootMode != bmCold) && (Inputs->BootMode != bmFast);

  MrcSetNormalMode (MrcData, TRUE);

  Flag = FALSE;
  // Poll until STALL_DRAIN_STRUCT.sr_state becomes zero (DDR is not in self-refresh)
  Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    Flag = 0;
    if (MrcControllerExist (MrcData, Controller)) {
      Offset = OFFSET_CALC_CH (MC0_STALL_DRAIN_REG, MC1_STALL_DRAIN_REG, Controller);
      do {
        StallDrain.Data = MrcReadCR (MrcData, Offset);
        Flag            = (StallDrain.Bits.sr_state == 1);
      } while (Flag && (MrcCall->MrcGetCpuTime () < Timeout));
    }
  }

  if (Flag) {
    return mrcFail;
  }

  if (SaGvAndSelfRefresh) {
    // Program DRAM MRs to match the High point
    MrcProgramMrsFsm (MrcData);
  }

  // Configure Power Down CR
  MrcPowerDownConfig (MrcData);

  // Ensure that pure_srx must be cleared so for FSM's to work.
  GetSetVal = 0;
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccPureSrx, WriteNoCache, &GetSetVal);

  return mrcSuccess;
}

/**
  Clear Delta DQS before switching SA GV point

  @param[in] MrcData - include all the MRC general data.
void
MrcClearDeltaDqs (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput                         *Inputs;
  const MRC_FUNCTION                     *MrcCall;
  MrcOutput                              *Outputs;
  MrcDebug                               *Debug;
  UINT32                                 Offset;
  UINT32                                 Timeout;
  UINT8                                  Rank;
  BOOLEAN                                Busy;
  MCMISCS_DELTADQSCOMMON0_STRUCT         DeltaDqsCommon0;
  DDRDATA0CH0_CR_DELTADQSRANK0_STRUCT    DeltaDqsRank;
  DDRSCRAM_CR_DDRMISCCONTROL1_STRUCT     DdrMiscControl1;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;

  Offset = MCMISCS_DELTADQSCOMMON0_REG;
  DeltaDqsCommon0.Data = MrcReadCR (MrcData, Offset);
  if (DeltaDqsCommon0.Bits.Lp4DeltaDQSTrainMode == 1) {
    Timeout = (UINT32) MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Clear Lp4DeltaDQSTrainMode\n");
    DeltaDqsCommon0.Bits.Lp4DeltaDQSTrainMode = 0;
    MrcWriteCR (MrcData, Offset, DeltaDqsCommon0.Data);
#ifdef CTE_FLAG
    MrcWait (MrcData, 25 * MRC_TIMER_1NS);
#else
    MrcWait (MrcData, 5 * MRC_TIMER_1US);
#endif
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Clear DeltaDQS registers\n");
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      Offset = DDRDATA_CR_DELTADQSRANK0_REG +
               ((DDRDATA_CR_DELTADQSRANK1_REG - DDRDATA_CR_DELTADQSRANK0_REG) * Rank);
      if (Rank == 3) {
        Offset += (DDRDATA_CR_DELTADQSRANK1_REG - DDRDATA_CR_DELTADQSRANK0_REG);
      }
      DeltaDqsRank.Data = 0;
      MrcWriteCR (MrcData, Offset, DeltaDqsRank.Data);
    } // for Rank
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Force DeltaDQS update\n");
    Offset = DDRSCRAM_CR_DDRMISCCONTROL1_REG;
    DdrMiscControl1.Data = MrcReadCR (MrcData, Offset);
    DdrMiscControl1.Bits.ForceDeltaDQSUpdate = 1;
    MrcWriteCR (MrcData, Offset, DdrMiscControl1.Data);
    // Wait for DeltaDQS Update to complete
    // Poll on register
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for DeltaDQS Update to complete\n");
    do {
      DdrMiscControl1.Data = MrcReadCR (MrcData, Offset);
      Busy = (DdrMiscControl1.Bits.ForceDeltaDQSUpdate == 1);
    } while (Busy && ((UINT32) MrcCall->MrcGetCpuTime () < Timeout));
    if (Busy) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DeltaDQS Update did not to complete\n", gErrString);
    }
  }
}
**/
MrcStatus
MrcEarlyOverrides (
  IN  MrcParameters *const  MrcData
  )
{
  const MRC_FUNCTION *MrcCall;
  MrcInput           *Inputs;
  MrcDebug           *Debug;
  UINT32             Data32;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &MrcData->Outputs.Debug;

  // Detect if we are running under Simics
  Data32 = MrcCall->MrcMmioRead32 (Inputs->PciEBaseAddress + 0xFC);
  if ((Data32 & 0xFF) == 0x04) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Simics detected (0x%08X)\n", Data32);
    Inputs->SimicsFlag = 1;
    if (Data32 & MRC_BIT16) {  // Disable most of the MRC logging
      Debug->Level = MSG_LEVEL_TIME;
    }
  }

  return mrcSuccess;
}

/**
  This function will override MRC Inputs based on current safe configuration.
  Called if MrcSafeConfig is TRUE.
  These overrides don't depend on DDR type because we don't know it yet.
  Overrides that depend on DDR type will be done during SPD Processing in MrcMcCapabilityPreSpd() below in this file.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcSafeMode (
  IN  MrcParameters *const  MrcData
  )
{
  MrcInput    *Inputs;

  Inputs  = &MrcData->Inputs;

  Inputs->LpDqsOscEn = 0;

  // Done per DDR type in MrcMcCapabilityPreSpd() below in this file
  Inputs->TrainingEnables2.DCC        = 0;
  Inputs->TrainingEnables2.TXTCO      = 0;
  Inputs->TrainingEnables2.CLKTCO     = 0;
  Inputs->TrainingEnables2.CMDSR      = 0;
  Inputs->TrainingEnables2.CMDDSEQ    = 0;
  Inputs->TrainingEnables2.DIMMODTCA  = 0;
  Inputs->TrainingEnables2.TXTCODQS   = 0;
  Inputs->TrainingEnables2.CMDDRUD    = 0;
  Inputs->TrainingEnables2.VCCDLLBP   = 0;
  Inputs->TrainingEnables2.PVTTDNLP   = 0;
  Inputs->TrainingEnables2.RDVREFDC   = 0;
  Inputs->TrainingEnables2.VDDQT      = 0;

  Inputs->TrainingEnables.RDODTT      = 0;
  Inputs->TrainingEnables.WRSRT       = 0;
  Inputs->TrainingEnables.WRDSEQT     = 0;
  Inputs->TrainingEnables.RDEQT       = 0;
  Inputs->TrainingEnables.RDAPT       = 0;
  Inputs->TrainingEnables.RTL         = 0;
  Inputs->TrainingEnables.TAT         = 0;
  Inputs->TrainingEnables.MEMTST      = 0;
  Inputs->TrainingEnables.ALIASCHK    = 0;
  Inputs->TrainingEnables.RMC         = 0;
  Inputs->TrainingEnables.WRDSUDT     = 0;
  Inputs->TrainingEnables.ERDMPRTC2D  = 0;
  Inputs->TrainingEnables.EWRTC2D     = 0;
  Inputs->TrainingEnables.ERDTC2D     = 0;
  Inputs->TrainingEnables.DIMMODTT    = 0;
  Inputs->TrainingEnables.DIMMRONT    = 0;

  return mrcSuccess;
}

/**
  SA GV flow for the cold boot

  @param[in] MrcData - include all the MRC general data.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSaGvSwitch (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcIntOutput        *MrcIntData;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  INT64               GetSetVal;
  UINT64              Timeout;
  UINT32              FreqIndex;
  BOOLEAN             Busy;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  // At this point the MC is in Normal mode with Refreshes enabled
  Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout

  // Save the current point
  GetSetVal = 1;
  FreqIndex = MrcIntData->SaGvPoint;
  MrcGetSetDdrIoGroupFreqIndex (MrcData, FreqIndex, GsmMccSaveFreqPoint, WriteNoCache, &GetSetVal);
  // Poll for acknowledgment
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for SAGV %d point save acknowledge\n", FreqIndex);
  do {
    MrcGetSetDdrIoGroupFreqIndex (MrcData, FreqIndex, GsmMccSaveFreqPoint, ReadNoCache, &GetSetVal);
    Busy = (GetSetVal == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));

  if (Busy) {
    return mrcDeviceBusy;
  }

  return Status;
}

/**
  SA GV flow for the Fixed mode.

  @param[in] MrcData  - include all the MRC general data.
  @param[in] SaGvMode - The SAGV mode to be fixed to.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSetSaGvFixed (
  IN  MrcParameters *const MrcData,
  IN  MrcSaGv              SaGvMode
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcStatus           Status;
  UINT32              Data32;
  UINT32              MailboxStatus;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  MrcCall     = Inputs->Call.Func;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;


  // Set the fixed point via CPU Mailbox
  // Assumption here that MrcSaGv values for FixedLow, FixedMed,
  // and FixedHigh match the CPU_MAILBOX command encoding.
  Data32 = SaGvMode;
  MrcCall->MrcCpuMailboxWrite (MAILBOX_TYPE_PCODE, CPU_MAILBOX_CMD_SAGV_SET_POLICY, Data32, &MailboxStatus);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "CPU_MAILBOX_CMD_SAGV_SET_POLICY %s. MailboxStatus = %Xh\n",
    (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
    MailboxStatus
    );

  return Status;
}

/**
  Energy Performance Gain.

  @param[in]  MrcData - Pointer to the MRC global data structure

  @retval - Status.
**/
MrcStatus
MrcEnergyPerfGain (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus           Status;
  //const MrcInput      *Inputs;
  //MrcIntOutput        *MrcIntData;
  //MrcCpuModel         CpuModel;
  /*
  UINT32              MailboxStatus;
  UINT8               Index;
  UINT16              MilliWatt[2];
  UINT16              Data[2];
  */

  //Inputs   = &MrcData->Inputs;
  //MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  //CpuModel    = Inputs->CpuModel;

  Status  = mrcSuccess;

  //if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    /*
    // If enabled, set up EPG.
    if (Inputs->EpgEnable == 1) {
      for (Index = 0; Index < 2; Index++) {
        // Calculate the 3 parameters (mW):  (Idd3x * Vdd * number of DIMMs present in the system) / 1000.
        MilliWatt[Index] = (UINT16) ((((Index == 0) ? (Inputs->Idd3n) : (Inputs->Idd3p))
            * (Outputs->VddVoltage[Inputs->MemoryProfile]) * (Outputs->Controller[0].Channel[0].DimmCount
            + Outputs->Controller[0].Channel[1].DimmCount)) / 1000);
        // Convert to fixed point 8.8 value.  Integer8.8 = (milliwatts / 1000) * 2^8
        Data[Index] = MilliWatt[Index] * 256 / 1000;
        // Write to mailbox register.
        if (MrcCall->MrcCpuMailboxWrite != NULL) {
          MrcCall->MrcCpuMailboxWrite (MAILBOX_TYPE_PCODE,
            ((Index == 0) ? SET_EPG_BIOS_POWER_OVERHEAD_0_CMD : SET_EPG_BIOS_POWER_OVERHEAD_1_CMD),
            Data[Index], &MailboxStatus);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "SET_EPG_BIOS_POWER_OVERHEAD_%d_CMD %s. Value = %08Xh. MailboxStatus = %Xh\n",
            Index,
            (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
            Data[Index],
            MailboxStatus);
        }  // Write to mailbox register.
      }  // for loop
    }  // EpgEnable
    */
  //}
  return Status;
}

/**
  this function is the last function that call from the MRC core.
    the function set DISB and set the MRC_Done.

  @param[in] MrcData - include all the MRC general data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcDone (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcSaGv             SaGv;
  INT64               GetSetVal;
  UINT64              Timeout;
  UINT32              Controller;
  BOOLEAN             Flag;
  P_COMP_PCU_STRUCT   MCompPcu;

  Inputs  = &MrcData->Inputs;
  Debug   = &MrcData->Outputs.Debug;
  MrcCall = Inputs->Call.Func;
  SaGv    = Inputs->SaGv;

  //if SAGV mode is fixed to one mode
  if ((SaGv != MrcSaGvDisabled) && (SaGv != MrcSaGvEnabled)) {
    MrcSetSaGvFixed (MrcData, SaGv);
  }

  GetSetVal = 1;
  MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);

  // lock the MC and memory map registers.
  McRegistersLock (MrcData);

  MrcGetSetMc (MrcData, 0, GsmMccMrcDone, WriteNoCache, &GetSetVal);

  // Wait for mc_init_done_ack
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Waiting for mc_init_done Acknowledge\n");

  Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
  do {
    Flag = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        MrcGetSetMc (MrcData, Controller, GsmMccMcInitDoneAck, ReadNoCache, &GetSetVal);
      }
      Flag |= (GetSetVal = 0);
    }
  } while (Flag && (MrcCall->MrcGetCpuTime () < Timeout));
  if (Flag) {
    return mrcFail;
  }

  // Enable Periodic Comp with periodic interval = 10uS*2^COMP_INT
  MCompPcu.Data = 0;
  MCompPcu.Bits.COMP_INTERVAL = COMP_INT;
  MrcWriteCR (MrcData, P_COMP_PCU_REG, MCompPcu.Data);

//  MrcWriteCR64 (MrcData, SSKPD_PCU_REG, 1); // We use this register to indicate "MRC done"


  return mrcSuccess;
}

/**
  Print the MRC version to the MRC output device.

  @param[in] Debug   - Pointer to the MRC Debug structure.
  @param[in] Version - The MRC version.

  @retval Nothing.
**/
void
MrcVersionPrint (
  IN MrcParameters     *MrcData,
  IN const MrcVersion  *Version
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcDebug *Debug;

  Debug    = &MrcData->Outputs.Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "*********************************************************************\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Copyright (c) 2011- 2019 Intel Corporation. All rights reserved. **\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Tigerlake memory detection and initialization code.             **\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Major version number is:   %2u                                   **\n", Version->Major);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Minor version number is:   %2u                                   **\n", Version->Minor);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Rev version number is:     %2u                                   **\n", Version->Rev);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "** Build number is:           %2u                                   **\n", Version->Build);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "*********************************************************************\n");
#endif
  return;
}

/**
  This function return the MRC version.

  @param[in] MrcData - Include all MRC global data.
  @param[out] Version - Location to store the MRC version.

  @retval Nothing.
**/
void
MrcVersionGet (
  IN  const MrcParameters *const MrcData,
  OUT MrcVersion *const Version
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;

  if (Version != NULL) {
    Inputs  = &MrcData->Inputs;
    MrcCall = Inputs->Call.Func;
    MrcCall->MrcCopyMem ((UINT8 *) Version, (UINT8 *) &cVersion, sizeof (MrcVersion));
  }
}

/**
  This function set the MRC vertion to MCDECS_SPARE register.
  The function need to be call by the wrapper after MrcStartMemoryConfiguration function where the MC CLK enable.
  The function write:
  Major number to bits 16-23
  Minor number to bits 8-15
  Build number to bits 0 - 7

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
MrcStatus
MrcSetMrcVersion (
  IN     MrcParameters *const MrcData
  )
{
  MrcVersion const         *Version;
  MC0_MRC_REVISION_STRUCT  MrcRevision;

  Version = &MrcData->Outputs.Version;
  MrcRevision.Data = (((UINT32) Version->Major) << 24) |
                     (((UINT32) Version->Minor) << 16) |
                     (((UINT32) Version->Rev)   << 8)  |
                     (((UINT32) Version->Build));

  MrcWriteCR (MrcData, MC0_MRC_REVISION_REG, MrcRevision.Data);
  return mrcSuccess;
}

/**
  This function locks the memory controller and memory map registers.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
McRegistersLock (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput                                 *Inputs;
  const MRC_FUNCTION                             *MrcCall;
  MrcDebug                                       *Debug;
  UINT32                                         Offset;
  UINT32                                         PciEBaseAddress;
  TOM_0_0_0_PCI_STRUCT                           Tom;
  TOLUD_0_0_0_PCI_STRUCT                         Tolud;
  TOUUD_0_0_0_PCI_STRUCT                         Touud;
  BDSM_0_0_0_PCI_STRUCT                          Bdsm;
  BGSM_0_0_0_PCI_STRUCT                          Bgsm;
  GGC_0_0_0_PCI_STRUCT                           Ggc;
  DPR_0_0_0_PCI_STRUCT                           Dpr;

  Debug   = &MrcData->Outputs.Debug;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  PciEBaseAddress = Inputs->PciEBaseAddress;

  // Lock PRMRR.  Convert from MB to Address.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcSetLockPrmrr: 0x%x\n", MrcCall->MrcSetLockPrmrr);
  MrcCall->MrcSetLockPrmrr (MrcCall->MrcLeftShift64 (MrcData->Outputs.MemoryMapData.PrmrrBase, 20), Inputs->PrmrrSize << 20);
  // Lock TME.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcTmeInit: 0x%x\n", MrcCall->MrcTmeInit);
  MrcCall->MrcTmeInit (Inputs->TmeEnable, Inputs->TmeExcludeBase, Inputs->TmeExcludeSize);
  // Lock the memory map registers.
  // Lock TOM.
  Offset        = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOM_0_0_0_PCI_REG);
  Tom.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
  Tom.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Tom.Data32[0]);

  // Lock TOLUD.
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOLUD_0_0_0_PCI_REG);
  Tolud.Data      = MrcCall->MrcMmioRead32 (Offset);
  Tolud.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Tolud.Data);

  // Lock TOUUD.
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOUUD_0_0_0_PCI_REG);
  Touud.Data32[0] = MrcCall->MrcMmioRead32 (Offset);
  Touud.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Touud.Data32[0]);

  // Lock DPR register
  Offset        = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, DPR_0_0_0_PCI_REG);
  Dpr.Data      = MrcCall->MrcMmioRead32 (Offset);
  Dpr.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Dpr.Data);

  // Lock BDSM.
  Offset         = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, BDSM_0_0_0_PCI_REG);
  Bdsm.Data      = MrcCall->MrcMmioRead32 (Offset);
  Bdsm.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Bdsm.Data);

  // Lock BGSM.
  Offset         = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, BGSM_0_0_0_PCI_REG);
  Bgsm.Data      = MrcCall->MrcMmioRead32 (Offset);
  Bgsm.Bits.LOCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Bgsm.Data);

  // Lock GGC.
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, GGC_0_0_0_PCI_REG);
  Ggc.Data        = (UINT16) MrcCall->MrcMmioRead32 (Offset);
  Ggc.Bits.GGCLCK = 1;
  MrcCall->MrcMmioWrite32 (Offset, Ggc.Data);

  // Lock the Ia/Gt exclusion
  MrcCall->MrcSetIaGtImrExclusionLock ();

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMemory map registers are locked\n");

  return;
}

/**
  This function returns the recommended MRC boot mode.

  @param[in] MrcData - The global host structure

  @retval bmWarm if we are in self refresh and the DISB bit is set, otherwise returns bmCold.
**/
MRC_BOOT_MODE
MrcGetBootMode (
  IN MrcParameters * const MrcData
  )
{
  MRC_BOOT_MODE BootMode;
  MrcInput     *Inputs;
  MRC_FUNCTION *MrcCall;
  UINT32       RegisterVal32;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;

//@todo ICL PCH may have changed this
  RegisterVal32 = MrcCall->MrcMmioRead32((UINTN)PCH_PWRM_BASE_ADDRESS + R_PCH_PWRM_GEN_PMCON_A);
  if (((RegisterVal32 & B_PCH_PWRM_GEN_PMCON_A_MEM_SR_MRC) != 0) && ((RegisterVal32 & B_PCH_PWRM_GEN_PMCON_A_DISB_MRC) != 0))  {
    BootMode = bmWarm;
  } else {
    BootMode = bmCold;
  }

  return BootMode;
}

/**
  This function sets the DISB bit in General PM Configuration.

  @param[in] MrcData - The global host structure

  @retval Nothing.
**/
void
MrcSetDISB (
  IN MrcParameters *const MrcData
  )
{
  MrcInput      *Inputs;
  MRC_FUNCTION  *MrcCall;
  UINT32        RegOffset;
  UINT8         RegisterVal;
  UINT8         Rw1cBits;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;

  RegOffset = PCH_PWRM_BASE_ADDRESS + R_PCH_PWRM_GEN_PMCON_A;
  // The bits we care about are between Bit 16-23.  There are many RW/1C bits which we would like to avoid.
  // Thus we will read/write a UINT8 at the register offset +2 Bytes.
  RegOffset += 2;

  RegisterVal = MrcCall->MrcMmioRead8 (RegOffset);

  // Bit 23 is DISB.  So we want to set this.  Bit 23 of the register is bit 7 at RegOffset+2
  RegisterVal |=  MRC_BIT7;

  // Bit 18 and Bit 16 are RW/1C.  So we will set these bits to 0 before writing the register.
  // Bit 18 is Bit 2 of the Byte.
  // Bit 16 is Bit 0 of the Byte.
  Rw1cBits = MRC_BIT0 | MRC_BIT2;
  // Invert the mask so RW/1C bits are 0 and the rest are 1's.  Then AND this with the value to be written.
  Rw1cBits = ~Rw1cBits;
  RegisterVal &= Rw1cBits;

  MrcCall->MrcMmioWrite8 (RegOffset, RegisterVal);
}

/**
  This function resets the DISB bit in General PM Configuration.

  @param[in] MrcData - The global host structure

  @retval Nothing.
**/
void
MrcResetDISB (
  IN MrcParameters *const MrcData
  )
{
  MrcInput      *Inputs;
  MRC_FUNCTION  *MrcCall;
  UINT32        RegOffset;
  UINT8         RegisterVal;
  UINT8         Rw1cBits;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;

  RegOffset = PCH_PWRM_BASE_ADDRESS + R_PCH_PWRM_GEN_PMCON_A;
  // The bits we care about are between Bit 16-23.  There are many RW/1C bits which we would like to avoid.
  // Thus we will read/write a UINT8 at the register offset +2 Bytes.
  RegOffset += 2;

  RegisterVal = MrcCall->MrcMmioRead8 (RegOffset);

  // Bit 18 and Bit 16 are RW/1C.  So we will set these bits to 0 before writing the register.
  // Bit 18 is Bit 2 of the Byte.
  // Bit 16 is Bit 0 of the Byte.
  Rw1cBits = MRC_BIT0 | MRC_BIT2;
  // Bit 23 is DISB.  So we want to clear this.  Bit 23 of the register is bit 7 at RegOffset+2
  Rw1cBits |=  MRC_BIT7;
  // Invert the mask so RW/1C bits and DISB are 0 and the rest are 1's.  Then AND this with the value to be written.
  Rw1cBits = ~Rw1cBits;

  RegisterVal &= Rw1cBits;

  MrcCall->MrcMmioWrite8 (RegOffset, RegisterVal);
}

/**
  This function reads the CAPID0 register and sets the memory controller's capability.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the memory controller's capability has been determined, otherwise returns mrcFail.
**/
MrcStatus
MrcMcCapability (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  MrcDebug                  *Debug;
  const MRC_FUNCTION        *MrcCall;
  MrcSaveData               *Save;
  MrcOutput                 *Outputs;
  MrcControllerOut          *ControllerOut;
  MrcChannelOut             *ChannelOut;
  MrcDimmOut                *DimmOut;
  MrcDdrType                DdrType;
  MrcProfile                Profile;
  UINT8                     MaxChannel;
  UINT32                    DimmCount;
  UINT32                    Max;
  UINT32                    Size;
  UINT32                    ChannelNum;
  UINT32                    DimmNum;
  UINT32                    ChDimmCount;
  UINT32                    Offset;
  UINT16                    NModeMinimum;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;
  BOOLEAN                   Cmd2N;
  BOOLEAN                   UlxUlt;
  BOOLEAN                   Lpddr4;
  BOOLEAN                   Lpddr5;
  BOOLEAN                   Ddr4;
  BOOLEAN                   Ddr5;
  BOOLEAN                   EccSupport;
  BOOLEAN                   IgnoreNonEccDimm;
  const char                *StrDdrType;
  CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  CAPID0_B_0_0_0_PCI_STRUCT Capid0B;
  CAPID0_C_0_0_0_PCI_STRUCT Capid0C;
  CAPID0_E_0_0_0_PCI_STRUCT Capid0E;
  DEVEN_0_0_0_PCI_STRUCT    Deven;

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Save        = &MrcData->Save.Data;
  Debug       = &Outputs->Debug;
  ChDimmCount = MAX_DIMMS_IN_CHANNEL;
  Profile     = Inputs->MemoryProfile;
  DdrType     = Outputs->DdrType;
  UlxUlt      = (Inputs->UlxUlt);
  MaxChannel  = Outputs->MaxChannels;
  Ddr4        = (DdrType == MRC_DDR_TYPE_DDR4);
  Ddr5        = (DdrType == MRC_DDR_TYPE_DDR5);
  Lpddr4      = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5      = (DdrType == MRC_DDR_TYPE_LPDDR5);

  // Obtain the capabilities of the memory controller.
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
  Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_E_0_0_0_PCI_REG);
  Capid0E.Data = MrcCall->MrcMmioRead32 (Offset);

  Save->McCapId.A = Capid0A.Data;
  Save->McCapId.B = Capid0B.Data;
  Save->McCapId.C = Capid0C.Data;
  Save->McCapId.E = Capid0E.Data;

  Offset     = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, DEVEN_0_0_0_PCI_REG);
  Deven.Data = MrcCall->MrcMmioRead32 (Offset);

  // Check that current DDR type is allowed on this CPU
  StrDdrType = NULL;
  if (Lpddr4 && (Capid0C.Bits.LPDDR4_EN == 0)) {
    StrDdrType = gDdrTypeStr[MRC_DDR_TYPE_LPDDR4];
  } else if (Lpddr5 && (Capid0E.Bits.LPDDR5_EN == 0)) {
    StrDdrType = gDdrTypeStr[MRC_DDR_TYPE_LPDDR5];
  } else if (Ddr4 && (Capid0C.Bits.DDR4_EN == 0)) {
    StrDdrType = gDdrTypeStr[MRC_DDR_TYPE_DDR4];
  } else if (Ddr5 && (Capid0E.Bits.DDR5_EN == 0)) {
    StrDdrType = gDdrTypeStr[MRC_DDR_TYPE_DDR5];
  }

  if (StrDdrType != NULL) {
    // MRC detected a memory technology and CAPID value shows the memory tech is not supported by this CPU.
    // e.g. LPDDR4 memory detected but CPU only supports DDR4.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: %s is not supported on this CPU\n", StrDdrType);
    return mrcDimmNotSupport;
  }

  // Determine Vccddq Limit
  Outputs->VccddqLimit = (UINT16) Capid0E.Bits.VDDQ_VOLTAGE_MAX;

  if (!(Lpddr4 || Lpddr5 || Ddr4 || Ddr5)) {
    // MRC detected memory technology besides what is supported by CPU.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: CPU only supports %s or %s or %s or %s; none of which has been detected!\n",
      gDdrTypeStr[MRC_DDR_TYPE_LPDDR4], gDdrTypeStr[MRC_DDR_TYPE_LPDDR5], gDdrTypeStr[MRC_DDR_TYPE_DDR4], gDdrTypeStr[MRC_DDR_TYPE_DDR5]);
    return mrcDimmNotSupport;
  }

  // Determine if the internal graphics engine is supported.
  if ((Capid0A.Bits.IGD == 0) && (Deven.Bits.D2EN > 0)) {
    Outputs->GraphicsStolenSize = Inputs->GraphicsStolenSize;
    Outputs->GraphicsGttSize    = Inputs->GraphicsGttSize;
    Outputs->GtPsmiRegionSize   = Inputs->GtPsmiRegionSize;
  } else {
    Outputs->GraphicsStolenSize = 0;
    Outputs->GraphicsGttSize    = 0;
    Outputs->GtPsmiRegionSize   = 0;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Memory allocated for IGD = %uMB and for GTT = %uMB.\n",
    Outputs->GraphicsStolenSize,
    Outputs->GraphicsGttSize
    );

  // Determine the maximum size of memory per channel, based on CAPID
  switch (Capid0A.Bits.DDRSZ) {
    case tcs64GB:
      Outputs->MrcTotalChannelLimit = (64 * 1024);
      break;

    case tcs8GB:
      Outputs->MrcTotalChannelLimit = (8 * 1024);
      break;

    case tcs4GB:
      Outputs->MrcTotalChannelLimit = (4 * 1024);
      break;

    case tcs2GB:
    default:
      Outputs->MrcTotalChannelLimit = (2 * 1024);
      break;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Maximum size of memory allowed on a channel = %uMB.\n",
    Outputs->MrcTotalChannelLimit
    );

  // Determine how many dimms are supported per channel on this memory controller,
  // based on fuse and how many channels have DIMMs installed.
  DimmCount     = (Capid0A.Bits.DDPCD == 0) ? MAX_DIMMS_IN_CHANNEL : 1;

  if ((Inputs->Force1Dpc == TRUE) || UlxUlt) {
    // Only 1DPC is supported on ULX / ULT platform
    DimmCount = 1;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "Number of channels supported = %u\nNumber of DIMMs per channel supported = %u\n",
    MaxChannel,
    DimmCount
    );

  // Determine the minimum NMode supported on this memory controller.
  NModeMinimum = (Capid0A.Bits.D1NM == 0) ? 1 : 2;

  // Determine the ECC capability of the memory controller.
  IgnoreNonEccDimm = (Capid0A.Bits.FDEE == 0) ? FALSE : TRUE;

  // Set EccSupport flag to TRUE if we must NOT ignore ECC DIMMs
  if (IgnoreNonEccDimm == TRUE) {
    Outputs->EccSupport = TRUE;
    EccSupport = TRUE; // FDEE has presedence over ECCDIS
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ALL DIMMs MUST be ECC capable\n");
  } else {
    EccSupport = ((Capid0A.Bits.ECCDIS > 0) || (Outputs->EccSupport == FALSE)) ? FALSE : TRUE;
  }
  // Now copy ECC and NMode information to the channel and DIMM results.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (MrcData, Controller, Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];
          Cmd2N = (NModeMinimum == 2);
          if ((Inputs->MemoryProfile == STD_PROFILE) && !Outputs->Gear2) {
            // Okay to use Outputs->Frequency here as we don't have frequency switching in DDR4,
            // and LPDDR4 doesn't support stretched commands.
            if ((Ddr4 && (Outputs->Frequency > f2133)) ||
                (Ddr4 && !UlxUlt && (Outputs->Frequency >= f1333))
               ) {
              Cmd2N = TRUE;
            }
          }
          if (Cmd2N) {
            ChannelOut->Timing[Profile].NMode = MAX (2, ChannelOut->Timing[Profile].NMode);
          }
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              DimmOut->Timing[Profile].NMode = ChannelOut->Timing[Profile].NMode;
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "  %s %u/%u/%u NMode = %u\n",
                CcdString,
                Controller,
                Channel,
                Dimm,
                DimmOut->Timing[Profile].NMode
              );
              if (EccSupport == TRUE) {
                if (DimmOut->EccSupport == FALSE) {
                  if (IgnoreNonEccDimm == TRUE) {
                    DimmOut->Status = DIMM_DISABLED;
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_NOTE,
                      "  %s %u/%u/%u Disabling non-ECC capable DIMM\n",
                      CcdString,
                      Controller,
                      Channel,
                      Dimm
                    );
                  } else {
                    Outputs->EccSupport = FALSE; // Final ECCSupport must be disabled if one DIMM is NOT capable
                  }
                }
              } else {
                DimmOut->EccSupport = FALSE;
                Outputs->EccSupport = FALSE; // Final ECCSupport must be disabled if ECCDIS is set
              }
            }
          }
        }
      }
    }
  }

  // Make sure we have the same NMode limit on both channels
  Cmd2N = FALSE;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (ControllerOut->Channel[Channel].Timing[Profile].NMode == 2) {
        Cmd2N = TRUE;
        break;
      }
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ControllerOut->Channel[Channel].Timing[Profile].NMode = (Cmd2N) ? 2 : 1;
    }
  }

  // Update Final SdramCount
  //@todo: Add DDR5
  Outputs->SdramCount =  (Ddr4) ? 8 : 2;
  if (Outputs->EccSupport == TRUE) {
    Outputs->SdramCount++;
  }

  // Determine the size of memory in each channel.
  // Also determine the channel with the largest amount.
  Max = ChannelNum = Outputs->MemoryMapData.TotalPhysicalMemorySize = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        Size        = 0;
        if (MrcChannelExist (MrcData, Controller, Channel)) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              Size += DimmOut->DimmCapacity;
            }
          }

          ChannelOut->Capacity = Size;
          if (Size > Max) {
            Max         = Size;
            ChannelNum  = Channel;
            ChDimmCount = ChannelOut->DimmCount;
          } else if ((Size == Max) && (DimmCount == 1)) {
            // Choose channel with least amount of DIMMs if 2DPC is disabled
            if (ChannelOut->DimmCount < ChDimmCount) {
              ChDimmCount = ChannelOut->DimmCount;
              ChannelNum  = Channel;
            }
          }
        } // ChannelExist

        Outputs->MemoryMapData.TotalPhysicalMemorySize += ChannelOut->Capacity;
        // Program ValidByteMask here
        ChannelOut->ValidByteMask = (1 << Outputs->SdramCount) - 1;
      }
    }
  }

  if (DimmCount == 1) {
    // Determine which DIMMs are supported on this memory controller.
    // If fused for one DIMM per channel, we pick the DIMM in a channel with the most memory.
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          ChannelOut = &ControllerOut->Channel[Channel];
          Max                   = Size = DimmNum = 0;
          if (ChannelOut->Status == CHANNEL_PRESENT) {
            for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
              DimmOut = &ChannelOut->Dimm[Dimm];
              if (DimmOut->Status == DIMM_PRESENT) {
                Size = DimmOut->DimmCapacity;
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%uD%uDimmCapacity = 0x%x\n", Channel, Dimm, DimmOut->DimmCapacity);
                if (Size > Max) {
                  Max     = Size;
                  DimmNum = Dimm;
                }
              }
            }

            for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
              DimmOut = &ChannelOut->Dimm[Dimm];
              if ((DimmOut->Status == DIMM_PRESENT) && (Dimm != DimmNum)) {
                DimmOut->Status = DIMM_DISABLED;
              }
            }

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "Controller configured to one DIMM per channel, we've selected channel %u, Dimm %u.\n",
              Channel,
              DimmNum
              );
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ValidRankBitMask = 0x%x\n", ChannelOut->ValidRankBitMask);
          }
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function reads the CAPID0 register and sets the following values
  according to memory controller's capability and user input:
    Outputs->RefClk
    Outputs->FreqMax
    Outputs->Capable100
    Outputs->MemoryClockMax

  @param[in, out] MrcData - All the MRC global data.

  @retval Always returns mrcSuccess.
**/
MrcStatus
MrcMcCapabilityPreSpd (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput                *Inputs;
  const MRC_FUNCTION            *MrcCall;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcIntOutput                  *IntOutputs;
  MrcFrequency                  FreqMax;
  MrcRefClkSelect               RefClk;
  MrcClockRatio                 MaxRatio;
  MrcDdrType                    DdrType;
  BOOLEAN                       RefClk100En;
  UINT32                        MaxFreqCap;
  UINT32                        Offset;
  UINT32                        Divisor;
  BOOLEAN                       Lpddr5;
  BOOLEAN                       OverclockCapable;
  CAPID0_A_0_0_0_PCI_STRUCT     Capid0A;
  CAPID0_B_0_0_0_PCI_STRUCT     Capid0B;
  CAPID0_C_0_0_0_PCI_STRUCT     Capid0C;
  CAPID0_E_0_0_0_PCI_STRUCT     Capid0E;
#ifdef MRC_DEBUG_PRINT
  UINT32                        Data32;
#endif

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  IntOutputs = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  DdrType     = Outputs->DdrType;
  Lpddr5      = (DdrType == MRC_DDR_TYPE_LPDDR5);

  // Obtain the capabilities of the memory controller.
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
  Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_E_0_0_0_PCI_REG);
  Capid0E.Data = MrcCall->MrcMmioRead32 (Offset);

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "CAPID0_A: %08Xh\nCAPID0_B: %08Xh\nCAPID0_C: %08Xh\nCAPID0_E: %08Xh\n",
    Capid0A.Data,
    Capid0B.Data,
    Capid0C.Data,
    Capid0E.Data
    );

  // Determine the maximum memory frequency supported and the memory reference clock.
  switch (DdrType) {
    case MRC_DDR_TYPE_LPDDR5:
      MaxFreqCap = Capid0E.Bits.MAX_DATA_RATE_LPDDR5;
      break;

    case MRC_DDR_TYPE_LPDDR4:
      MaxFreqCap = Capid0C.Bits.MAX_DATA_RATE_LPDDR4;
      break;

    case MRC_DDR_TYPE_DDR5:
      MaxFreqCap = Capid0E.Bits.MAX_DATA_RATE_DDR5;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid DDR Type detected. Using Type DDR4\n");
      /*FALLTHROUGH*/
    case MRC_DDR_TYPE_DDR4:
      MaxFreqCap = Capid0C.Bits.MAX_DATA_RATE_DDR4;
      break;
  }
#ifdef MRC_DEBUG_PRINT
  // Print DMFC decoding. 0 means Unlimited
  Data32 = MaxFreqCap * 266666;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DMFC: %u\n", UDIVIDEROUND (Data32, 1000));
#endif

  OverclockCapable = (Capid0A.Bits.DDR_OVERCLOCK > 0) ? TRUE : FALSE;
  RefClk100En      = (BOOLEAN) Capid0B.Bits.PLL_REF100_CFG;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_OVERCLOCK: %d, PLL_REF100_CFG: %d\n", OverclockCapable, RefClk100En);

  // Determine correct RefClk
  RefClk  = Inputs->RefClk;
  if (!RefClk100En) {
    RefClk = MRC_REF_CLOCK_133;
    if (Lpddr5) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "LPDDR5 uses RefClk100 but it is disabled\n");
      return mrcFail;
    }
  } else {
    Outputs->Capable100 = TRUE;
    if (Lpddr5) {
      // Force to RefClk100
      RefClk = MRC_REF_CLOCK_100;
    } else if (OverclockCapable && (Inputs->MemoryProfile == STD_PROFILE)) {
      // If we are using standard memory profile, DIMMS should run at RefClk 133.
      RefClk = MRC_REF_CLOCK_133;
    }
    // Otherwise, we keep what was requested via the input parameter
  }
  Outputs->RefClk = RefClk;

  // Now use the RefClk to determine the Max Ratio/Freq
  // Start by using FreqMax to determine what is the max frequency is based on the RefClk we found.
  // If OverclockCapable is set, this will be our limit.
  FreqMax = (RefClk == MRC_REF_CLOCK_100) ? MAX_FREQ_OC_100 : MAX_FREQ_OC_133;
  Outputs->FreqMax = ((Inputs->FreqMax > fNoInit) && (Inputs->FreqMax < fInvalid)) ? Inputs->FreqMax : FreqMax;

  if ((Inputs->MrcSafeConfig == 1) && (Inputs->FreqMax == fNoInit)) {
    switch (Outputs->DdrType) {
      case MRC_DDR_TYPE_DDR4:
        if (Inputs->SimicsFlag == 1) {
          Outputs->FreqMax = f1600;
        } else {
          Outputs->FreqMax = f2133;
        }
        break;
      case MRC_DDR_TYPE_LPDDR4:
        if (Inputs->SimicsFlag == 1) {
          Outputs->FreqMax = f1600;
        } else {
          Outputs->FreqMax = f2133;
        }
        break;
      case MRC_DDR_TYPE_LPDDR5:
        Outputs->FreqMax = f2200;
        break;
      case MRC_DDR_TYPE_DDR5:
        // @todo DDR5
      default:
        break;
    }
  }

  if (!OverclockCapable) {
    // Use the ratio limit from CAPID to determine the MaxFreq
    MaxRatio = (MrcClockRatio) ((MaxFreqCap == 0) ? CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_MAX : MaxFreqCap);
    // CAPID is using 200/266, while MC_BIOS_REQ is using 100/133, hence double the CAPID value
    MaxRatio *= 2;
    // CAPID is fused base off of 133 ref clk.  So first we will calculate the frequency max, then we will limit
    // it to 100 RefClk if it is selected.  This is done below because we need to know the Gear ratio as well.
    FreqMax  = MrcRatioToFrequency (MrcData, MaxRatio, MRC_REF_CLOCK_133, BCLK_DEFAULT);
  }
  // Now check if the CPU is the limiter of the frequency, and apply that limit over user/DIMM request.
  if (FreqMax < Outputs->FreqMax) {
    Outputs->FreqMax  = FreqMax;
  }

  if (Inputs->SaGv != MrcSaGvDisabled) {
    MrcGetSagvConfig (MrcData, IntOutputs->SaGvPoint, &FreqMax, &Outputs->Gear2);
    Outputs->FreqMax = MIN (FreqMax, Outputs->FreqMax);
  } else {
    // Set Gear by the input parameter if not auto, otherwise default to G1 up to 2133 MHz.
    if (Inputs->GearRatio) {
      Outputs->Gear2 = (Inputs->GearRatio == 2) ? 1 : 0;
    } else {
      // No DIMM is POR below 2133.  Default to G2 based on FreqMax
      Outputs->Gear2 = (Outputs->FreqMax >= 2133) ? 1 : 0;
    }
  }

  if (Outputs->Gear2) {
    Outputs->Gear2Ever = TRUE;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Gear2Ever %d\n", Outputs->Gear2Ever);

  if (RefClk == MRC_REF_CLOCK_100) {
    // FreqMax at this point is still in terms of the 133.  Convert to to 100
    // If we have a gear ratio enabled, the frequency max has to be a ratio of the Gear ratio.
    // I.E.  If Gear2 FreqMax must be an even ratio of 200/266
    Divisor = (100 * ((Outputs->Gear2) ? 2 : 1));
    Outputs->FreqMax /= Divisor;
    Outputs->FreqMax *= Divisor;
  }
  Outputs->MemoryClockMax = ConvertFreq2Clock (MrcData, Outputs->FreqMax);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Outputs->MemoryClockMax: %u, Outputs->FreqMax : %u, Gear%d\n", Outputs->MemoryClockMax, Outputs->FreqMax, Outputs->Gear2 ? 2 : 1);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "The maximum memory frequency allowed is %u, tCK=%ufs\n", Outputs->FreqMax, Outputs->MemoryClockMax);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "%uMHz reference clock is selected\n",
    (Outputs->RefClk == MRC_REF_CLOCK_133) ? 133 : 100
    );

  return mrcSuccess;
}

/**
  This function reads the input data structure and sets the appropriate overrides in the output structure.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the timing overrides have been conpleted.
**/
MrcStatus
MrcSetOverrides (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcDebug      *Debug;
  const UINT16  *RcompTarget;
  MrcDdrType    DdrType;
  MrcFrequency  DdrFreq;
  MrcStatus     Status;
  UINT16        ReqRdOdt;
  UINT16        ValidRdOdt;
  UINT8         Index;
  UINT8         NewMode;
  UINT8         RankMask;
  UINT8         NumRanks;
  BOOLEAN       lDramDqOdtEn;
  BOOLEAN       UlxUlt;
  MrcFrequency  DdrFrequency;
  BOOLEAN       Lpddr4;
  BOOLEAN       Lpddr5;
  BOOLEAN       Ddr4;
  BOOLEAN       Ddr5;
  BOOLEAN       SafeMode;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  DdrType     = Outputs->DdrType;
  UlxUlt      = (Inputs->UlxUlt);
  RankMask    = Outputs->ValidRankMask;
  Status      = mrcSuccess;
  RcompTarget = NULL;

  Outputs->EccSupport      = Inputs->EccSupport != 0;
  Outputs->VddVoltageDone  = FALSE;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5  = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4    = (DdrType == MRC_DDR_TYPE_DDR4);
  Ddr5    = (DdrType == MRC_DDR_TYPE_DDR5);
  DdrFrequency = (Lpddr4 && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;
  SafeMode = (Inputs->SafeMode != 0);
  if (Inputs->DramDqOdt == MrcAuto) {
    switch (DdrType) {
      case MRC_DDR_TYPE_LPDDR4:
        // LPDDR4 we do frequency switching.  If we have this enabled, we need to check HighFrequency.
        // Otherwise, we use Frequency
        DdrFreq = (Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;
        if (DdrFreq == f1067) {
          lDramDqOdtEn = FALSE;
        } else {
          lDramDqOdtEn = TRUE;
        }
        break;

      case MRC_DDR_TYPE_DDR4:
      case MRC_DDR_TYPE_LPDDR5:
      default:  // For non-supported DRAM types, enable DQ ODT
        lDramDqOdtEn = TRUE;
        break;
    }
  } else {
    lDramDqOdtEn = (Inputs->DramDqOdt == MrcEnable) ? TRUE : FALSE;
  }
  Outputs->DramDqOdtEn  = lDramDqOdtEn;

  // Configure RxPath
  if ((Inputs->RxMode != 0xFF) && (Inputs->RxMode < MrcRxModeMax)) {
    NewMode = Inputs->RxMode;
  } else {
    switch (DdrType) {
      case MRC_DDR_TYPE_LPDDR4:
        if (Inputs->SimicsFlag == 1) {
          NewMode = MrcRxModeMatchedP;
        } else {
          NewMode = MrcRxModeUnmatchedRxWRload;
        }
        break;

      case MRC_DDR_TYPE_LPDDR5:
        NewMode = MrcRxModeUnmatchedRxWRload;
        break;

      case MRC_DDR_TYPE_DDR4:
      default:
        NewMode = MrcRxModeMatchedN;
        break;
    }
  }
  Outputs->RxMode = NewMode;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxMode: %s\n", gIoRxModeStr[NewMode]);

  // If RcompResistors are not zero, then user is overriding default termination
  if (Inputs->RcompResistor == 0) {
    Inputs->RcompResistor = 100; // All platform designs default to 100 Ohm.
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Updating Rcomp Resistors: %u\n", Inputs->RcompResistor);
  }

  // Determine RcompTargets based on CPU type and DDR Type
  switch (DdrType) {
    case MRC_DDR_TYPE_DDR4:
      RcompTarget = (UlxUlt) ? RcompTargetUDdr4 : RcompTargetHDdr4;
      break;

    case MRC_DDR_TYPE_LPDDR5:
      RcompTarget = RcompTargetLpddr5;
      break;

    case MRC_DDR_TYPE_LPDDR4:
      RcompTarget = (Outputs->Lp4x) ? RcompTargetLpddr4x : RcompTargetLpddr4;
      break;

    case MRC_DDR_TYPE_DDR5:
      RcompTarget = RcompTargetUDdr5;
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %s: %d\n", gErrString, gUnsupportedTechnology, DdrType);
      Status = mrcFail;
      break;
  }
#ifdef MRC_DEBUG_PRINT
  if ((Inputs->RcompTarget[0] == 0) || (Inputs->RcompTarget[1] == 0) || (Inputs->RcompTarget[2] == 0) ||
      (Inputs->RcompTarget[3] == 0) || (Inputs->RcompTarget[4] == 0)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Updating Rcomp Targets:\n");
  }
#endif // MRC_DEBUG_PRINT
  for (Index = 0; Index < MAX_RCOMP_TARGETS; Index++) {
    if ((Inputs->RcompTarget[Index] == 0) && (RcompTarget != NULL)) {
      Inputs->RcompTarget[Index] = RcompTarget[Index];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " RcompTarget[%s]: %u\n", GlobalCompOffsetStr[Index], Inputs->RcompTarget[Index]);
    }
  }

  // Determine the IO ODT Termination mode:
  //  Technology  DT/HALO(2 DPC)  DT/HALO(1 DPC)  ULX/ULT
  //-----------------------------------------------------
  //  LP5           VSS             VSS             VSS
  //  Lp4           VSS             VSS             VSS
  //  Ddr4          VDDq            VDDq            VTT
  if (Outputs->OdtMode == MrcOdtModeDefault) {
    switch (DdrType) {
      case MRC_DDR_TYPE_DDR4:
      case MRC_DDR_TYPE_DDR5:
        //if (UlxUlt) {
        //  Outputs->OdtMode = MrcOdtModeVtt;
        //} else {
        //  // DT/HALO
        //  Outputs->OdtMode = MrcOdtModeVddq;
        //}
        //if (Inputs->SafeMode) {
        Outputs->OdtMode = MrcOdtModeVddq;
        //}
        break;

      case MRC_DDR_TYPE_LPDDR4:
      case MRC_DDR_TYPE_LPDDR5:
        Outputs->OdtMode = MrcOdtModeVss;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %s: %d\n", gErrString, gUnsupportedTechnology, DdrType);
        Status = mrcFail;
        break;
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRIO ODT Mode: %s\n", gIoOdtModeStr[Outputs->OdtMode]);

  // If we are LPDDR4, we need to check that the request CPU ODT matches one of the MR values for SOC_ODT.
  ReqRdOdt  = Inputs->RcompTarget[RdOdt];
  ValidRdOdt = MrcCheckForSocOdtEnc (MrcData, ReqRdOdt);
  if (ValidRdOdt != ReqRdOdt) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "RdOdt target of %d is not supported by the memory.  Updated to %d.  Please Update RcompTarget[RdOdt] to a correct value\n", ReqRdOdt, ValidRdOdt);
    Inputs->RcompTarget[RdOdt] = ValidRdOdt;
  }

  if (Lpddr5) {
    Inputs->TrainingEnables.ECT = 0;
    Inputs->PowerDownMode = pdmNoPowerDown;
    Inputs->SrefCfgEna = 0;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Disabling ECT, power down, and sref for LP5\n");
  }

  // If we have ECT disabled, set the ECT done flag so Reset Flows will behave normally for LPDDR systems.
  if ((Inputs->TrainingEnables.ECT == 0) || (Inputs->SimicsFlag == 1)) {
    Outputs->LpddrEctDone = TRUE;
  }

  // Assign Vccdq voltage to match DRAM Vddq.
  if (SafeMode) {
    if (Lpddr5) {
      Outputs->VccddqVoltage = VDD_0_80;
    } else {
      Outputs->VccddqVoltage = Outputs->Vdd2Mv;
    }
  } else {
    if (Ddr4) {
      Outputs->VccddqVoltage = VDD_1_20;
    } else if (Ddr5) {
      Outputs->VccddqVoltage = VDD_1_10;
    } else if (Lpddr4) {
      if (DdrFrequency <= 2933) {
        Outputs->VccddqVoltage = VDD_0_60;
      } else if (DdrFrequency <= 3733) {
        Outputs->VccddqVoltage = VDD_0_90;
      } else {
        Outputs->VccddqVoltage = VDD_1_00;
      }
    } else { //Lpddr5
      if (DdrFrequency <= 2400) {
        Outputs->VccddqVoltage = VDD_0_40;
      } else if (DdrFrequency <= 4200) {
        Outputs->VccddqVoltage = VDD_0_60;
      } else if (DdrFrequency <= 5300) {
        Outputs->VccddqVoltage = VDD_0_80;
      } else { //DdrFrequency = 6400
        NumRanks = MrcCountBitsEqOne (RankMask);
        if (NumRanks > 1) {
          Outputs->VccddqVoltage = VDD_1_00;
        } else {
          Outputs->VccddqVoltage = VDD_0_80;
        }
      }
    }
  }
  return Status;
}

/**
  This function get the current value of the sticky scratchpad register.

  @param[in] MrcData - include all the MRC data.

  @retval The current value of the sticky scratchpad register.
**/
UINT64
MrcWmRegGet (
  IN     MrcParameters *const MrcData
  )
{
  return (MrcReadCR64 (MrcData, SSKPD_PCU_REG));
}


/**
  This function fills in the MRS FSM to finalize the SAGV configuration for normal operation.

  @param[in] MrcData - The global host structure

  @retval mrcSuccess.
**/
MrcStatus
MrcSaGvFinal (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput          *Inputs;
  MrcDebug                *Debug;
  MrcOutput               *Outputs;
  const MrcControllerOut  *ControllerOut;
  const MrcChannelOut     *ChannelOut;
  const MrcRankOut        *RankOut;
  MrcDdrType              DdrType;
  MRC_FUNCTION            *MrcCall;
  UINT32                  Controller;
  UINT32                  Channel;
  UINT32                  IpChannel;
  UINT32                  Rank;
  UINT32                  SubCh;
  UINT32                  Offset;
  UINT8                   VrefCode;
  UINT8                   Byte;
  UINT8                   RankMod2;
  BOOLEAN                 FsmSaved;
  BOOLEAN                 SaGv;
  BOOLEAN                 Lpddr4;
  MC0_CH0_CR_LPDDR_MR_CONTENT_STRUCT  LpddrMrContent;
  MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_STRUCT  Mr0Mr1Content;
  MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_STRUCT  Mr2Mr3Content;
  MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_STRUCT  Mr4Mr5Content;
  MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_STRUCT  Mr6Mr7Content;
  MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_STRUCT  Mr6VrefValues;
  MC0_CH0_CR_MRS_FSM_CONTROL_STRUCT MrsFsmControl;
  MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_STRUCT Lpddr4DiscreteMrValue;
#ifdef MRC_DEBUG_PRINT
  UINT8                   Mr;
  static const UINT8      Lpddr4MrIndex[8]   = {mrIndexMR3, mrIndexMR11, mrIndexMR12, mrIndexMR14, mrIndexMR1, mrIndexMR2, mrIndexMR22, mrIndexMR23};
  static const UINT8      Lpddr4MrAddress[8] = {mrMR3, mrMR11, mrMR12, mrMR14, mrMR1, mrMR2, mrMR22, mrMR23};
#endif

  Inputs        = &MrcData->Inputs;
  MrcCall       = MrcData->Inputs.Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  DdrType       = Outputs->DdrType;
  Lpddr4        = (DdrType == MRC_DDR_TYPE_LPDDR4);

  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR5) || (Outputs->DdrType == MRC_DDR_TYPE_DDR5)) {
    return mrcSuccess;
  }

  if (Lpddr4) {
    // Disable high current VRCG mode at the end of the training
    MrcSetFspVrcg (MrcData, ALL_RANK_MASK, LpVrcgNormal, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8);
  }

  MrsFsmControl.Data = 0;
  MrsFsmControl.Bits.do_ZQCL = (Lpddr4) ? 0 : 1;
  SaGv = (Inputs->SaGv == MrcSaGvEnabled);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      FsmSaved = FALSE;
      // In the MC, Channel 1/3 are treated as ranks 2/3.  Convert to MC IP layout:
      // Channel 0/2 -> IpChannel 0/1 SubCh 0
      // Channel 1/3 -> IpChannel 0/1 SubCh 1
      IpChannel = LP_IP_CH (Lpddr4, Channel);
      SubCh     = Channel % 2;
      if (Lpddr4) {
        for (Rank = 0; Rank < MAX_RANK_IN_DIMM; Rank++) {
          RankOut = &ChannelOut->Dimm[dDIMM0].Rank[Rank];
          if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
#ifdef MRC_DEBUG_PRINT
            for (Mr = 0; Mr < ARRAY_COUNT(Lpddr4MrIndex); Mr++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u.R%u.MR[%u] = 0x%04X\n", Controller, Channel, Rank, Lpddr4MrAddress[Mr], RankOut->MR[Lpddr4MrIndex[Mr]]);
            }
#endif
            // The following configuration is per rank configurations.
            Lpddr4DiscreteMrValue.Data = 0;
            Lpddr4DiscreteMrValue.Bits.PDDS     = (RankOut->MR[mrIndexMR3]  >> 3) & 0x7;
            Lpddr4DiscreteMrValue.Bits.DQ_ODT   =  RankOut->MR[mrIndexMR11]       & 0x7;
            Lpddr4DiscreteMrValue.Bits.CA_ODT   = (RankOut->MR[mrIndexMR11] >> 4) & 0x7;
            Lpddr4DiscreteMrValue.Bits.CA_VREF  =  RankOut->MR[mrIndexMR12]       & 0x7F;
            Lpddr4DiscreteMrValue.Bits.DQ_VREF  =  RankOut->MR[mrIndexMR14]       & 0x7F;
            Lpddr4DiscreteMrValue.Bits.CODT     =  RankOut->MR[mrIndexMR22]       & 0x7;
            Offset = OFFSET_CALC4 (
                      MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG, MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG, Controller,
                      MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG, IpChannel,
                      MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG, SubCh,
                      MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG, Rank
                      );
            MrcWriteCR64 (MrcData, Offset, Lpddr4DiscreteMrValue.Data);
            // Choose to use the System Definition for the register mapping instead of IpChannel
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u.R%u: LPDDR4_DISCRETE_MR_VALUES = 0x%016llX\n", Controller, Channel, Rank, Lpddr4DiscreteMrValue.Data);

            // The following items are per MC channel (Common to both Ch 0/1 and 2/3 respectively)
            // Cannot support Ch 1 or 3 only configurations.
            if (!FsmSaved && (!IS_MC_SUB_CH (Lpddr4, Channel))) {
              LpddrMrContent.Data = 0;
              LpddrMrContent.Bits.MR1  = RankOut->MR[mrIndexMR1];
              LpddrMrContent.Bits.MR2  = RankOut->MR[mrIndexMR2];
              LpddrMrContent.Bits.MR3  = RankOut->MR[mrIndexMR3];
              LpddrMrContent.Bits.MR11 = RankOut->MR[mrIndexMR11];
              LpddrMrContent.Bits.MR12 = RankOut->MR[mrIndexMR12];
              LpddrMrContent.Bits.MR13 = RankOut->MR[mrIndexMR13];
              LpddrMrContent.Bits.MR22 = RankOut->MR[mrIndexMR22];
              LpddrMrContent.Bits.MR23 = RankOut->MR[mrIndexMR23];
              Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_LPDDR_MR_CONTENT_REG, MC1_CH0_CR_LPDDR_MR_CONTENT_REG, Controller, MC0_CH1_CR_LPDDR_MR_CONTENT_REG, IpChannel);
              MrcWriteCR64 (MrcData, Offset, LpddrMrContent.Data);
              // Choose to use the System Definition for the register mapping instead of IpChannel
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u: LPDDR_MR_CONTENT = 0x%016llX\n", Controller, Channel, LpddrMrContent.Data);

              MrsFsmControl.Bits.LPDDR_Restore_MR = 0x1FF;
              MrsFsmControl.Bits.LPDDR4_switch_FSP = 1;
              MrsFsmControl.Bits.do_dq_osc_start = (Inputs->LpDqsOscEn) ? 1 : 0;
              MrsFsmControl.Bits.tVREFDQ = DIVIDECEIL (MRC_LP4_tFC_LONG_NS * 1000, Outputs->tCKps);  // tVREFDQ is in tCK units
              FsmSaved = TRUE;
            } // !FsmSaved && !IS_MC_SUB_CH
          } // RankExist
        } // For Rank
      } else {
        // DDR4
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
            RankMod2 = Rank % 2;
            RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2];

            // Per-device registers restore
            Mr6VrefValues.Data = 0;
            for (Byte = 0; Byte < 8; Byte++) { // Only 8 bytes, no place for ECC byte
              VrefCode = RankOut->Ddr4PdaMr6[Byte] & 0x7F;
              Mr6VrefValues.Data |= MrcCall->MrcLeftShift64 ((UINT64) VrefCode, Byte * MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_OFF);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Mc%u.C%u.R%d.S%u: Vref offset = %d (0 = 820mV) Code = 0x%X \n",
                Controller,
                Channel,
                Rank,
                Byte,
                MrcVrefDqToOffsetDdr4 (VrefCode),
                VrefCode
              );
            }
            Offset = OFFSET_CALC3 (
                      MC0_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG, MC1_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG, Controller,
                      MC0_CH1_CR_DDR4_MR6_VREF_VALUES_0_REG, Channel,
                      MC0_CH0_CR_DDR4_MR6_VREF_VALUES_1_REG, Rank
                      );
            MrcWriteCR64 (MrcData, Offset, Mr6VrefValues.Data);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "Mc%u.C%u.R%u: DDR4_MR6_VREF_VALUES = 0x%08X%08X\n",
              Controller,
              Channel,
              Rank,
              Mr6VrefValues.Data32[1],
              Mr6VrefValues.Data32[0]
              );

            if (!FsmSaved) {
              Mr0Mr1Content.Data = 0;
              Mr2Mr3Content.Data = 0;
              Mr4Mr5Content.Data = 0;
              Mr6Mr7Content.Data = 0;
              Mr0Mr1Content.Bits.MR0 = RankOut->MR[0];
              Mr0Mr1Content.Bits.MR1 = RankOut->MR[1];
              Mr2Mr3Content.Bits.MR2 = RankOut->MR[2];
              Mr2Mr3Content.Bits.MR3 = RankOut->MR[3];
              MrsFsmControl.Bits.DDR4_Restore_MR = 0xF; // Restore MR0..MR3

              Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG, MC1_CH0_CR_DDR4_MR0_MR1_CONTENT_REG, Controller, MC0_CH1_CR_DDR4_MR0_MR1_CONTENT_REG, Channel);
              MrcWriteCR (MrcData, Offset, Mr0Mr1Content.Data);

              Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG, MC1_CH0_CR_DDR4_MR2_MR3_CONTENT_REG, Controller, MC0_CH1_CR_DDR4_MR2_MR3_CONTENT_REG, Channel);
              MrcWriteCR (MrcData, Offset, Mr2Mr3Content.Data);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Mc%u.C%u: MR0_MR1_CONTENT = 0x%08X, MR2_MR3_CONTENT = 0x%08X\n",
                Controller,
                Channel,
                Mr0Mr1Content.Data,
                Mr2Mr3Content.Data
                );

              Mr4Mr5Content.Bits.MR4 = RankOut->MR[4];
              Mr4Mr5Content.Bits.MR5 = RankOut->MR[5];
              Mr6Mr7Content.Bits.MR6 = RankOut->MR[6];
              MrsFsmControl.Bits.DDR4_Restore_MR = 0x7F; // Restore MR0..MR6
              MrsFsmControl.Bits.DDR4_Restore_MR6_Per_Device = 1;
              MrsFsmControl.Bits.vref_time_per_byte = 1;
              MrsFsmControl.Bits.tVREFDQ = DIVIDECEIL (tVREF_DQ_PS, Outputs->Dclkps);

              Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG, MC1_CH0_CR_DDR4_MR4_MR5_CONTENT_REG, Controller, MC0_CH1_CR_DDR4_MR4_MR5_CONTENT_REG, Channel);
              MrcWriteCR (MrcData, Offset, Mr4Mr5Content.Data);

              Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG, MC1_CH0_CR_DDR4_MR6_MR7_CONTENT_REG, Controller, MC0_CH1_CR_DDR4_MR6_MR7_CONTENT_REG, Channel);
              MrcWriteCR (MrcData, Offset, Mr6Mr7Content.Data);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "Mc%u.C%u: MR4_MR5_CONTENT = 0x%08X, MR6_MR7_CONTENT = 0x%08X\n",
                Controller,
                Channel,
                Mr4Mr5Content.Data,
                Mr6Mr7Content.Data
                );
              FsmSaved = TRUE;
            } // !FsmSaved
          } // RankExist
        } // Rank
      } // DDR4

      if (SaGv && (!IS_MC_SUB_CH (Lpddr4, Channel))) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MRS_FSM_CONTROL_REG, MC1_CH0_CR_MRS_FSM_CONTROL_REG, Controller, MC0_CH1_CR_MRS_FSM_CONTROL_REG, IpChannel);
        MrcWriteCR64 (MrcData, Offset, MrsFsmControl.Data);
        // Choose to use the System Definition for the register mapping instead of IpChannel
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.C%u: MRS_FSM_CONTROL = 0x%08X\n", Controller, Channel, MrsFsmControl.Data);
      }
    } // for Channel
  } // Controller
#ifdef MRC_DEBUG_PRINT
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
        // Skip if this rank is not present on any of the channels
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank %d\tMc0\tMc1", Rank);
      RankMod2 = Rank % 2;
      for (Mr = 0; Mr <= 6; Mr++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMR[%d]:", Mr);
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          ControllerOut = &Outputs->Controller[Controller];
          for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
            ChannelOut = &ControllerOut->Channel[Channel];
            RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2];
            if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
              if (Controller == 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
              }
              continue;
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t0x%04X", RankOut->MR[Mr]);
          } // for Channel
        } // for Controller
      } // for Mr
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    } // for Rank
  } // if DDR4
#endif

  return mrcSuccess;
}

/**
  Gets pointers to functions inside of core.

  @param[in]  MrcData                     - All the MRC global data.
  @param[out] CallChannelExist            - Pointer to the function MrcChannelExist
  @param[out] CallPrintf                  - Pointer to the function MrcPrintf
  @param[out] CallChangeMargin            - Pointer to the function ChangeMargin
  @param[out] CallSignExtend              - Pointer to the function MrcSignExtend
  @param[out] CallShiftPIforCmdTraining   - Pointer to the function ShiftPIforCmdTraining
  @param[out] CallMrcUpdateVref           - Pointer to the function MrcUpdateVref

  @retval Returns mrcSuccess if the function succeeds.
**/
MrcStatus
MrcGetCoreFunction (
  IN const MrcParameters *const MrcData,
  OUT UINTN                    *CallChannelExist,
  OUT UINTN                    *CallPrintf,
  OUT UINTN                    *CallChangeMargin,
  OUT UINTN                    *CallSignExtend,
  OUT UINTN                    *CallShiftPIforCmdTraining,
  OUT UINTN                    *CallMrcUpdateVref
  )
{
  *CallChannelExist            = (UINTN) &MrcChannelExist;
  *CallPrintf                  = (UINTN) &MrcPrintf;
  *CallChangeMargin            = (UINTN) &ChangeMargin;
  *CallSignExtend              = (UINTN) &MrcSE;
  *CallShiftPIforCmdTraining   = (UINTN) &ShiftPIforCmdTraining;
  *CallMrcUpdateVref           = (UINTN) &MrcUpdateVref;
  return (mrcSuccess);
}

#ifdef MRC_DEBUG_PRINT
/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPrintInputParameters (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug                *Debug;
  const MrcInput          *Inputs;
  const MrcControllerIn   *ControllerIn;
  const MrcChannelIn      *ChannelIn;
  const MrcDimmIn         *DimmIn;
  const MrcTiming         *Timing;
  const TrainingStepsEn   *TrainingSteps;
  const TrainingStepsEn2  *TrainingSteps2;
  const UINT8             *Buffer;
  UINT16                  Line;
  UINT16                  Address;
  UINT16                  Offset;
  UINT8                   Controller;
  UINT8                   Channel;
  UINT8                   Dimm;
  UINT8                   Iteration;
  UINT8                   Bit;
  UINT8                   Byte;
  UINT32                  Index;
  CHAR8                   HexDump[16 * 3 + 16 + 1];
  CHAR8                   *p;
  UINT8                   Data8;

  Inputs  = &MrcData->Inputs;
  Debug   = &MrcData->Outputs.Debug;

  // The following are system level definitions. All memory controllers in the system are set to these values.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Stream: %Xh\n", Debug->Stream);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Debug.Level: %Xh\n", Debug->Level);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "HeapBase: %08Xh\n", Inputs->HeapBase.DataN);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "HeapSize: %u\n", Inputs->HeapSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SerialBuffer: %08Xh\n", Inputs->SerialBuffer.DataN);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SerialBufferSize: %u\nFreqMax: %u\n", Inputs->SerialBufferSize, Inputs->FreqMax);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GearRatio: %u\nRatio: %u\n", Inputs->GearRatio, Inputs->Ratio);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RefClk: %uMHz\n", (Inputs->RefClk == MRC_REF_CLOCK_100) ? 100 : 133);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BClk: %uHz\n", Inputs->BClkFrequency);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MemoryProfile: %Xh\n", Inputs->MemoryProfile);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BoardType: %u\nCmdRanksTerminated: %Xh\n", Inputs->BoardType, Inputs->CmdRanksTerminated);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DqPinsInterleaved: %u\nSeparateCkeDelayDdr4: %u\n", Inputs->DqPinsInterleaved, Inputs->SeparateCkeDelayDdr4);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuModel: %Xh\nCpuStepping: %Xh\n", Inputs->CpuModel, Inputs->CpuStepping);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsStolenSize: %Xh\n", Inputs->GraphicsStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GraphicsGttSize: %Xh\n", Inputs->GraphicsGttSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Iteration: %Xh\n", Inputs->Iteration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddVoltage: %u mV\n", Inputs->VddVoltage);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BootMode: %Xh\n", Inputs->BootMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TxtFlag: %Xh\nSimicsFlag: %Xh\n", Inputs->TxtFlag, Inputs->SimicsFlag);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MobilePlatform: %Xh\n", Inputs->MobilePlatform);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EccSupport: %Xh\nCleanMemory: 0x%X\n", Inputs->EccSupport, Inputs->CleanMemory);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GfxIsVersatileAcceleration: %Xh\n", Inputs->GfxIsVersatileAcceleration);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ScramblerSupport: %Xh\n", Inputs->ScramblerSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RemapEnable: %Xh\n", Inputs->RemapEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PowerDownMode: %Xh\n", Inputs->PowerDownMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PwdwnIdleCounter: %Xh\nDisPgCloseIdleTimeout: %Xh\n", Inputs->PwdwnIdleCounter, Inputs->DisPgCloseIdleTimeout);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RankInterleave: %Xh\n", Inputs->RankInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnhancedInterleave: %Xh\n", Inputs->EnhancedInterleave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "WeaklockEn: %Xh\n", Inputs->WeaklockEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnCmdRate: %Xh\n", Inputs->EnCmdRate);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BaseAddresses\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  PciE: %Xh\n", Inputs->PciEBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  MchBar: %Xh\n", Inputs->MchBarBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Smbus: %Xh\n", Inputs->SmbusBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MeStolenSize: %Xh\n", Inputs->MeStolenSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MmioSize: %Xh\n", Inputs->MmioSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TsegSize: %Xh\n", Inputs->TsegSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IedSize: %Xh\n", Inputs->IedSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DprSize: %Xh\n", Inputs->DprSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PrmrrSize: %Xh\n", Inputs->PrmrrSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VddSettleWaitTime: %Xh\n", Inputs->VddSettleWaitTime);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccIomV: %d\n", Inputs->VccIomV);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RmtPerTask: %d\nTrainTrace: %d\n", Inputs->RmtPerTask, Inputs->TrainTrace);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AutoSelfRefreshSupport: %u\n", Inputs->AutoSelfRefreshSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ExtTemperatureSupport: %u\n", Inputs->ExtTemperatureSupport);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RetrainOnFastFail: %u\nLpDdrDqDqsReTraining (LpDqsOscEn) : %Xh\n",
     Inputs->RetrainOnFastFail, Inputs->LpDqsOscEn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MrcSafeConfig: %Xh\nSafeMode: %Xh\n", Inputs->MrcSafeConfig, Inputs->SafeMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashEnable: %Xh\n", Inputs->ChHashEnable);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashMask: %Xh\n", Inputs->ChHashMask);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ChHashInterleaveBit: %Xh\nPerBankRefresh: %Xh\n", Inputs->ChHashInterleaveBit, Inputs->PerBankRefresh);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ProbelessTrace: %u\n", Inputs->ProbelessTrace);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Force1Dpc: %u\n", Inputs->Force1Dpc);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ForceSingleRank: %u\n", Inputs->ForceSingleRank);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VttCompForVsshi: %u\n", Inputs->VttCompForVsshi);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ddr4OneDpc: %u\nRxMode: %u\n", Inputs->Ddr4OneDpc, Inputs->RxMode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PowerTrainingMode: %s optimization\n", Inputs->PowerTrainingMode ? "margin" : "power");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    MRC TRAINING STEPS     *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  TrainingSteps = &Inputs->TrainingEnables;
  TrainingSteps2 = &Inputs->TrainingEnables2;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.SOT: %u\n", TrainEnString, TrainingSteps->SOT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ERDMPRTC2D: %u\n", TrainEnString, TrainingSteps->ERDMPRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ECT: %u\n", TrainEnString, TrainingSteps->ECT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVET: %u\n", TrainEnString, TrainingSteps->RCVET);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDMPRT: %u\n", TrainEnString, TrainingSteps->RDMPRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.JWRL: %u\n", TrainEnString, TrainingSteps->JWRL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EWRTC2D: %u\n", TrainEnString, TrainingSteps->EWRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ERDTC2D: %u\n", TrainEnString, TrainingSteps->ERDTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC1D: %u\n", TrainEnString, TrainingSteps->WRTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRVC1D: %u\n", TrainEnString, TrainingSteps->WRVC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC1D: %u\n", TrainEnString, TrainingSteps->RDTC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR4MAP: %u\n", Inputs->DDR4MAP);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s2.DIMMODTCAT: %u\n%s.DIMMODTT: %u\n", TrainEnString, TrainingSteps2->DIMMODTCA, TrainEnString, TrainingSteps->DIMMODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.DIMMRONT: %u\n", TrainEnString, TrainingSteps->DIMMRONT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRDSEQT: %u\n", TrainEnString, TrainingSteps->WRDSEQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRDSUDT: %u\n", TrainEnString, TrainingSteps->WRDSUDT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRSRT: %u\n", TrainEnString, TrainingSteps->WRSRT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDODTT: %u\n", TrainEnString, TrainingSteps->RDODTT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDEQT: %u\n", TrainEnString, TrainingSteps->RDEQT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDAPT: %u\n", TrainEnString, TrainingSteps->RDAPT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.CMDVC: %u\n", TrainEnString, TrainingSteps->CMDVC);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRTC2D: %u\n", TrainEnString, TrainingSteps->WRTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDTC2D: %u\n", TrainEnString, TrainingSteps->RDTC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.WRVC2D: %u\n", TrainEnString, TrainingSteps->WRVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDVC2D: %u\n", TrainEnString, TrainingSteps->RDVC2D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.LCT: %u\n", TrainEnString, TrainingSteps->LCT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RTL: %u\n", TrainEnString, TrainingSteps->RTL);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.TAT: %u\n", TrainEnString, TrainingSteps->TAT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMT: %u\n", TrainEnString, TrainingSteps->RMT);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.MEMTST: %u\n", TrainEnString, TrainingSteps->MEMTST);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.ALIASCHK: %u\n", TrainEnString, TrainingSteps->ALIASCHK);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RCVENC1D: %u\n", TrainEnString, TrainingSteps->RCVENC1D);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RMC: %u\n%s.DCC: %u\n", TrainEnString, TrainingSteps->RMC, TrainEn2String, TrainingSteps2->DCC);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDVC1D: %u\n%s.TXTCO: %u\n%s.CLKTCO: %u\n", TrainEn2String, TrainingSteps2->RDVC1D,
                 TrainEn2String, TrainingSteps2->TXTCO, TrainEn2String, TrainingSteps2->CLKTCO);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.CMDSR: %u\n%s.CMDDSEQ: %u\n%s.DIMMODTCA: %u\n%s.TXTCODQS: %u\n", TrainEn2String, TrainingSteps2->CMDSR,
                 TrainEn2String, TrainingSteps2->CMDDSEQ, TrainEn2String, TrainingSteps2->DIMMODTCA, TrainEn2String, TrainingSteps2->TXTCODQS);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.CMDDRUD: %u\n%s.VCCDLLBP: %u\n%s.PVTTDNLP: %u\n", TrainEn2String, TrainingSteps2->CMDDRUD,
                 TrainEn2String, TrainingSteps2->VCCDLLBP, TrainEn2String, TrainingSteps2->PVTTDNLP);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.RDVREFDC: %u\n%s.VDDQT: %u\n%s.RMTBIT: %u\n", TrainEn2String, TrainingSteps2->RDVREFDC, TrainEn2String, TrainingSteps2->VDDQT,
                 TrainEn2String, TrainingSteps2->RMTBIT);
  // SAGV Inputs
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV Inputs\nPoints\tFreq\tGears\n");
  for (Index = 0; Index < MAX_SAGV_POINTS; Index++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t%u\t%u\n", Index, Inputs->SaGvFreq[Index], Inputs->SaGvGear[Index]);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****      MRC TIMING DATA      *****\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Controller[%u] ChannelCount: %Xh\n", Controller, ControllerIn->ChannelCount);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].Status: %Xh\n", Channel, ChannelIn->Status);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel[%u].DimmCount: %Xh\n", Channel, ChannelIn->DimmCount);

      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];
        Timing = &DimmIn->Timing;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u Status: %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->Status);
        if (Inputs->MemoryProfile == USER_PROFILE) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCK    : %u\n", CcdString, Controller, Channel, Dimm, Timing->tCK);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u NMode  : %u\n", CcdString, Controller, Channel, Dimm, Timing->NMode);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCL    : %u\n", CcdString, Controller, Channel, Dimm, Timing->tCL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCWL   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tCWL);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tFAW   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tFAW);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRAS   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tRAS);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRCDtRP: %u\n", CcdString, Controller, Channel, Dimm, Timing->tRCDtRP);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tREFI  : %u\n", CcdString, Controller, Channel, Dimm, Timing->tREFI);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRFC   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tRFC);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRRD   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tRRD);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRTP   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tRTP);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWR    : %u\n", CcdString, Controller, Channel, Dimm, Timing->tWR);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR   : %u\n", CcdString, Controller, Channel, Dimm, Timing->tWTR);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR_L : %u\n", CcdString, Controller, Channel, Dimm, Timing->tWTR_L);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tWTR_S : %u\n", CcdString, Controller, Channel, Dimm, Timing->tWTR_S);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tCCD_L : %u\n", CcdString, Controller, Channel, Dimm, Timing->tCCD_L);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u SpdAddress: %Xh\n", CcdString, Controller, Channel, Dimm, DimmIn->SpdAddress);
        Buffer = (UINT8 *) &DimmIn->Spd.Data;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD:           00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
        for (Line = 0; Line < (sizeof (MrcSpd) / 16); Line++) {
          Address = Line * 16;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " % 4Xh(% 5u): ", Address, Address);
          p = HexDump;
          for (Offset = 0; Offset < 16; Offset++) {
            p += MrcSPrintf (MrcData, p, sizeof (HexDump) - (p - HexDump), "%02X ", Buffer[Address + Offset]) - 1;
          }
          for (Offset = 0; Offset < 16; Offset++) {
            Data8 = Buffer[Address + Offset];
            *p++ = isprint (Data8) ? Data8 : '.';
          }
          *p = '\0';
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\n", HexDump);
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****    THERMAL OVERWRITE    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDn     : %Xh\n",   ThermEnString, Inputs->EnablePwrDn);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.EnablePwrDnLpddr: %Xh\n",   ThermEnString, Inputs->EnablePwrDnLpddr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s.Refresh2X       : %Xh\n",   ThermEnString, Inputs->Refresh2X);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SrefCfgEna      : %Xh\n",      Inputs->SrefCfgEna);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SrefCfgIdleTmr  : %Xh\n",      Inputs->SrefCfgIdleTmr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinDefeat: %Xh\n",      Inputs->ThrtCkeMinDefeat);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinTmr   : %Xh\n",      Inputs->ThrtCkeMinTmr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinDefeatLpddr: %Xh\n", Inputs->ThrtCkeMinDefeatLpddr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ThrtCkeMinTmrLpddr   : %Xh\n", Inputs->ThrtCkeMinTmrLpddr);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*****   DQDQS SWIZZLING    *******\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s", PrintBorder);
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u:", Controller, Channel);
      for (Iteration = 0; Iteration < (sizeof (ChannelIn->DqsMapCpu2Dram) / sizeof (ChannelIn->DqsMapCpu2Dram[0])); Iteration++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", ChannelIn->DqsMapCpu2Dram[Iteration]);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " DqMapCpu2Dram: ");
      for (Byte = 0; Byte < MAX_BYTE_IN_LP_CHANNEL; Byte++) {
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d ", ChannelIn->DqMapCpu2Dram[Byte][Bit]);
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RcompResistor: %u\n",  Inputs->RcompResistor);
  for (Index = 0; Index < MAX_RCOMP_TARGETS; Index++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RcompTarget[%s]: %u\n", GlobalCompOffsetStr[Index], Inputs->RcompTarget[Index]);
  }

  return mrcSuccess;
}

/**
  Print the specified memory to the serial message debug port.

  @param[in] Debug - Serial message debug structure.
  @param[in] Start - The starting address to dump.
  @param[in] Size  - The amount of data in bytes to dump.

  @retval Nothing.
**/
void
MrcPrintMemory (
  IN MrcDebug *const    Debug,
  IN const UINT8 *const Start,
  IN const UINT32       Size
  )
{
  const UINT8  *Address;
  const UINT8  *End;
  UINT32       Line;
  UINT32       Offset;
  union {
    UINT64     Data64[2];
    UINT32     Data32[4];
    UINT16     Data16[8];
    UINT8      Data8[16];
  } Buffer;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "          ");
  for (Offset = 0; Offset < 16; Offset++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%02X ", ((UINTN) Start + Offset) % 16);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  End = Start + Size;
  for (Line = 0; Line < ((Size / 16) + 1); Line++) {
    Address = Start + (Line * 16);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "% 8X: ", Address);
    for (Offset = 0; Offset < 16; Offset++) {
      Buffer.Data8[Offset] = ((Address + Offset) < End) ? Address[Offset] : 0;
    }
    for (Offset = 0; Offset < 16; Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ((Address + Offset) < End) ? "%02X " : "   ", Buffer.Data8[Offset]);
    }
    for (Offset = 0; (Offset < 16) && ((Address + Offset) < End); Offset++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%c", isprint (Buffer.Data8[Offset]) ? Buffer.Data8[Offset] : '.');
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }
  return;
}
#endif

